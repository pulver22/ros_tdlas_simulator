FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/msgs_and_srvs/msg"
  "../src/msgs_and_srvs/srv"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "../srv_gen/lisp/ChamicalValue11.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_ChamicalValue11.lisp"
  "../srv_gen/lisp/SensorPosition.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_SensorPosition.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
