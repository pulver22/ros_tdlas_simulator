FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/msgs_and_srvs/msg"
  "../src/msgs_and_srvs/srv"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/msgs_and_srvs/msg/__init__.py"
  "../src/msgs_and_srvs/msg/_readings.py"
  "../src/msgs_and_srvs/msg/_SourceLoc.py"
  "../src/msgs_and_srvs/msg/_ChemicalValue.py"
  "../src/msgs_and_srvs/msg/_odor.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
