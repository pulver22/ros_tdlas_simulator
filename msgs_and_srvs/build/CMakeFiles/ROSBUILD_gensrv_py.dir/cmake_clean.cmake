FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/msgs_and_srvs/msg"
  "../src/msgs_and_srvs/srv"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/msgs_and_srvs/srv/__init__.py"
  "../src/msgs_and_srvs/srv/_ChamicalValue11.py"
  "../src/msgs_and_srvs/srv/_SensorPosition.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
