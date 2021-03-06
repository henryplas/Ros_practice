// Generated by gencpp from file ros_essentials_cpp/AddTwoInts.msg
// DO NOT EDIT!


#ifndef ROS_ESSENTIALS_CPP_MESSAGE_ADDTWOINTS_H
#define ROS_ESSENTIALS_CPP_MESSAGE_ADDTWOINTS_H

#include <ros/service_traits.h>


#include <ros_essentials_cpp/AddTwoIntsRequest.h>
#include <ros_essentials_cpp/AddTwoIntsResponse.h>


namespace ros_essentials_cpp
{

struct AddTwoInts
{

typedef AddTwoIntsRequest Request;
typedef AddTwoIntsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct AddTwoInts
} // namespace ros_essentials_cpp


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::ros_essentials_cpp::AddTwoInts > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ::ros_essentials_cpp::AddTwoInts&) { return value(); }
};

template<>
struct DataType< ::ros_essentials_cpp::AddTwoInts > {
  static const char* value()
  {
    return "ros_essentials_cpp/AddTwoInts";
  }

  static const char* value(const ::ros_essentials_cpp::AddTwoInts&) { return value(); }
};


// service_traits::MD5Sum< ::ros_essentials_cpp::AddTwoIntsRequest> should match
// service_traits::MD5Sum< ::ros_essentials_cpp::AddTwoInts >
template<>
struct MD5Sum< ::ros_essentials_cpp::AddTwoIntsRequest>
{
  static const char* value()
  {
    return MD5Sum< ::ros_essentials_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::ros_essentials_cpp::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::ros_essentials_cpp::AddTwoIntsRequest> should match
// service_traits::DataType< ::ros_essentials_cpp::AddTwoInts >
template<>
struct DataType< ::ros_essentials_cpp::AddTwoIntsRequest>
{
  static const char* value()
  {
    return DataType< ::ros_essentials_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::ros_essentials_cpp::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::ros_essentials_cpp::AddTwoIntsResponse> should match
// service_traits::MD5Sum< ::ros_essentials_cpp::AddTwoInts >
template<>
struct MD5Sum< ::ros_essentials_cpp::AddTwoIntsResponse>
{
  static const char* value()
  {
    return MD5Sum< ::ros_essentials_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::ros_essentials_cpp::AddTwoIntsResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::ros_essentials_cpp::AddTwoIntsResponse> should match
// service_traits::DataType< ::ros_essentials_cpp::AddTwoInts >
template<>
struct DataType< ::ros_essentials_cpp::AddTwoIntsResponse>
{
  static const char* value()
  {
    return DataType< ::ros_essentials_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::ros_essentials_cpp::AddTwoIntsResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // ROS_ESSENTIALS_CPP_MESSAGE_ADDTWOINTS_H
