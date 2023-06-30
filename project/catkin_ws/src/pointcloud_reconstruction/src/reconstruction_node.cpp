#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/surface/mls.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/features/normal_3d.h>

ros::Publisher pub;

void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& msg) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*msg, *cloud);

    // 估计点云法线
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setInputCloud(cloud);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
    ne.setSearchMethod(tree);
    ne.setKSearch(20);
    ne.compute(*normals);

    // 将点云和法线合并为 PointCloud<PointNormal>
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);

    // 三维重建
    pcl::PolygonMesh::Ptr reconstructed_mesh(new pcl::PolygonMesh);
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    gp3.setInputCloud(cloud_with_normals);  // 设置输入点云为带法线的点云
    gp3.setSearchRadius(0.25);
    gp3.setMu(2.5);
    gp3.setMaximumNearestNeighbors(100);
    gp3.setMaximumSurfaceAngle(M_PI / 4);
    gp3.setMinimumAngle(M_PI / 18);
    gp3.setMaximumAngle(2 * M_PI / 3);
    gp3.setNormalConsistency(false);
    gp3.reconstruct(*reconstructed_mesh);

    // 将网格保存为PLY文件
    pcl::io::savePLYFileBinary("/home/ubuntu/reconstructed_mesh.ply", *reconstructed_mesh);

    // 加载PLY文件并转换为PointCloud<pcl::PointXYZ>
    pcl::PointCloud<pcl::PointXYZ>::Ptr reconstructed_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPLYFile("/home/ubuntu/reconstructed_mesh.ply", *reconstructed_cloud);

    // 发布三维重建结果
    sensor_msgs::PointCloud2 output;
    pcl::toROSMsg(*reconstructed_cloud, output);
    output.header = msg->header;
    pub.publish(output);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "reconstruction_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/rslidar_points", 1, pointCloudCallback);
    pub = nh.advertise<sensor_msgs::PointCloud2>("/reconstructed_cloud", 1);

    ros::spin();

    return 0;
}
