#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */

#include <fstream>
#include <string>

std::string read_datafile(std::string message_filename){

  // data_*byte.txt??std::string bytedata????????? 
  
  std::ifstream ifs(message_filename.c_str());
  if(ifs.fail()) {
	std::cerr << "data_*byte.txt do not exist.\n";
	exit(0);
  }

  std::string bytedata;
  getline(ifs, bytedata);

  return bytedata;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);

  int count = 0;

  std::string bytedata = read_datafile("/home/algo/Desktop/ros2_simple/src/simple_test_talker/src/byte_data/data_1Mbyte.txt");
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << bytedata << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());


    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
