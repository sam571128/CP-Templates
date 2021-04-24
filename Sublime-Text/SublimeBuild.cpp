//This is the build file script for sublime-text, rename it as XXX.sublime_build 

{
"cmd": ["g++", "-std=c++17", "$file", "-o", "${file_path}/${file_base_name}"],
"file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
"working_dir": "${file_path}",
"selector": "source.c, source.c++, source.cxx, source.cpp",
"variants":
[
{
"name": "Run",
"cmd": ["bash", "-c","g++ -std=c++17 '${file}' -I . -o '${file_path}/${file_base_name}' && gnome-terminal -- bash -c \"ulimit -s unlimited; '${file_path}/${file_base_name}'; read;exit; exec bash\""]
}
]
}
