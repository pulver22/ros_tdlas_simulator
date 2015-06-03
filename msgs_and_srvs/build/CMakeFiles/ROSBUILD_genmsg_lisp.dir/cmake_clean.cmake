FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/msgs_and_srvs/msg"
  "../src/msgs_and_srvs/srv"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/readings.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_readings.lisp"
  "../msg_gen/lisp/SourceLoc.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_SourceLoc.lisp"
  "../msg_gen/lisp/ChemicalValue.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_ChemicalValue.lisp"
  "../msg_gen/lisp/odor.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_odor.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
