#commonapi-generator-linux-x86_64 --dest src-gen --skel [*.fidl list]
 '../tool/commonapi_core_generator/commonapi-core-generator-linux-x86_64' -dest ../src-gen -sk ModuleXXX.fidl
#commonapi-someip-generator-linux-x86_64 --dest src-gen [*.fdepl list]
'../tool/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64' -dest ../src-gen  -ll verbose ModuleXXX-SomeIP.fdepl