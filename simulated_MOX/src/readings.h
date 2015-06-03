/* Auto-generated by genmsg_cpp for file /home/ali/ros_workspace/odor_simulation/msgs_and_srvs/msg/readings.msg */
#ifndef MSGS_AND_SRVS_MESSAGE_READINGS_H
#define MSGS_AND_SRVS_MESSAGE_READINGS_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace msgs_and_srvs
{
template <class ContainerAllocator>
struct readings_ {
  typedef readings_<ContainerAllocator> Type;

  readings_()
  : r0_id(0.0)
  , r0_x(0.0)
  , r0_y(0.0)
  , r0_z(0.0)
  , r0_val(0.0)
  , r1_id(0.0)
  , r1_x(0.0)
  , r1_y(0.0)
  , r1_z(0.0)
  , r1_val(0.0)
  , r2_id(0.0)
  , r2_x(0.0)
  , r2_y(0.0)
  , r2_z(0.0)
  , r2_val(0.0)
  , r0_con(0.0)
  , r1_con(0.0)
  , r2_con(0.0)
  {
  }

  readings_(const ContainerAllocator& _alloc)
  : r0_id(0.0)
  , r0_x(0.0)
  , r0_y(0.0)
  , r0_z(0.0)
  , r0_val(0.0)
  , r1_id(0.0)
  , r1_x(0.0)
  , r1_y(0.0)
  , r1_z(0.0)
  , r1_val(0.0)
  , r2_id(0.0)
  , r2_x(0.0)
  , r2_y(0.0)
  , r2_z(0.0)
  , r2_val(0.0)
  , r0_con(0.0)
  , r1_con(0.0)
  , r2_con(0.0)
  {
  }

  typedef double _r0_id_type;
  double r0_id;

  typedef double _r0_x_type;
  double r0_x;

  typedef double _r0_y_type;
  double r0_y;

  typedef double _r0_z_type;
  double r0_z;

  typedef double _r0_val_type;
  double r0_val;

  typedef double _r1_id_type;
  double r1_id;

  typedef double _r1_x_type;
  double r1_x;

  typedef double _r1_y_type;
  double r1_y;

  typedef double _r1_z_type;
  double r1_z;

  typedef double _r1_val_type;
  double r1_val;

  typedef double _r2_id_type;
  double r2_id;

  typedef double _r2_x_type;
  double r2_x;

  typedef double _r2_y_type;
  double r2_y;

  typedef double _r2_z_type;
  double r2_z;

  typedef double _r2_val_type;
  double r2_val;

  typedef double _r0_con_type;
  double r0_con;

  typedef double _r1_con_type;
  double r1_con;

  typedef double _r2_con_type;
  double r2_con;


  typedef boost::shared_ptr< ::msgs_and_srvs::readings_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::msgs_and_srvs::readings_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct readings
typedef  ::msgs_and_srvs::readings_<std::allocator<void> > readings;

typedef boost::shared_ptr< ::msgs_and_srvs::readings> readingsPtr;
typedef boost::shared_ptr< ::msgs_and_srvs::readings const> readingsConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::msgs_and_srvs::readings_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::msgs_and_srvs::readings_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace msgs_and_srvs

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::msgs_and_srvs::readings_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::msgs_and_srvs::readings_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::msgs_and_srvs::readings_<ContainerAllocator> > {
  static const char* value() 
  {
    return "430fcebc758b34df5ca08669cef51d20";
  }

  static const char* value(const  ::msgs_and_srvs::readings_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x430fcebc758b34dfULL;
  static const uint64_t static_value2 = 0x5ca08669cef51d20ULL;
};

template<class ContainerAllocator>
struct DataType< ::msgs_and_srvs::readings_<ContainerAllocator> > {
  static const char* value() 
  {
    return "msgs_and_srvs/readings";
  }

  static const char* value(const  ::msgs_and_srvs::readings_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::msgs_and_srvs::readings_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64 r0_id\n\
float64 r0_x\n\
float64 r0_y\n\
float64 r0_z\n\
float64 r0_val\n\
float64 r1_id\n\
float64 r1_x\n\
float64 r1_y\n\
float64 r1_z\n\
float64 r1_val\n\
float64 r2_id\n\
float64 r2_x\n\
float64 r2_y\n\
float64 r2_z\n\
float64 r2_val\n\
float64 r0_con\n\
float64 r1_con\n\
float64 r2_con\n\
\n\
";
  }

  static const char* value(const  ::msgs_and_srvs::readings_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::msgs_and_srvs::readings_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::msgs_and_srvs::readings_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.r0_id);
    stream.next(m.r0_x);
    stream.next(m.r0_y);
    stream.next(m.r0_z);
    stream.next(m.r0_val);
    stream.next(m.r1_id);
    stream.next(m.r1_x);
    stream.next(m.r1_y);
    stream.next(m.r1_z);
    stream.next(m.r1_val);
    stream.next(m.r2_id);
    stream.next(m.r2_x);
    stream.next(m.r2_y);
    stream.next(m.r2_z);
    stream.next(m.r2_val);
    stream.next(m.r0_con);
    stream.next(m.r1_con);
    stream.next(m.r2_con);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct readings_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::msgs_and_srvs::readings_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::msgs_and_srvs::readings_<ContainerAllocator> & v) 
  {
    s << indent << "r0_id: ";
    Printer<double>::stream(s, indent + "  ", v.r0_id);
    s << indent << "r0_x: ";
    Printer<double>::stream(s, indent + "  ", v.r0_x);
    s << indent << "r0_y: ";
    Printer<double>::stream(s, indent + "  ", v.r0_y);
    s << indent << "r0_z: ";
    Printer<double>::stream(s, indent + "  ", v.r0_z);
    s << indent << "r0_val: ";
    Printer<double>::stream(s, indent + "  ", v.r0_val);
    s << indent << "r1_id: ";
    Printer<double>::stream(s, indent + "  ", v.r1_id);
    s << indent << "r1_x: ";
    Printer<double>::stream(s, indent + "  ", v.r1_x);
    s << indent << "r1_y: ";
    Printer<double>::stream(s, indent + "  ", v.r1_y);
    s << indent << "r1_z: ";
    Printer<double>::stream(s, indent + "  ", v.r1_z);
    s << indent << "r1_val: ";
    Printer<double>::stream(s, indent + "  ", v.r1_val);
    s << indent << "r2_id: ";
    Printer<double>::stream(s, indent + "  ", v.r2_id);
    s << indent << "r2_x: ";
    Printer<double>::stream(s, indent + "  ", v.r2_x);
    s << indent << "r2_y: ";
    Printer<double>::stream(s, indent + "  ", v.r2_y);
    s << indent << "r2_z: ";
    Printer<double>::stream(s, indent + "  ", v.r2_z);
    s << indent << "r2_val: ";
    Printer<double>::stream(s, indent + "  ", v.r2_val);
    s << indent << "r0_con: ";
    Printer<double>::stream(s, indent + "  ", v.r0_con);
    s << indent << "r1_con: ";
    Printer<double>::stream(s, indent + "  ", v.r1_con);
    s << indent << "r2_con: ";
    Printer<double>::stream(s, indent + "  ", v.r2_con);
  }
};


} // namespace message_operations
} // namespace ros

#endif // MSGS_AND_SRVS_MESSAGE_READINGS_H
