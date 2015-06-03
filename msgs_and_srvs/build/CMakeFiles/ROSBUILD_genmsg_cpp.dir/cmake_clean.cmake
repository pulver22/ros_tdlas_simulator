FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/msgs_and_srvs/msg"
  "../src/msgs_and_srvs/srv"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/msgs_and_srvs/readings.h"
  "../msg_gen/cpp/include/msgs_and_srvs/SourceLoc.h"
  "../msg_gen/cpp/include/msgs_and_srvs/ChemicalValue.h"
  "../msg_gen/cpp/include/msgs_and_srvs/odor.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
