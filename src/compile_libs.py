#!/usr/bin/env python3
###
# Created by Lucy. A Utility to compile libs depending on the platform.
###

import os
import sys
import shutil
import platform

script_directory = os.path.dirname(os.path.realpath(__file__))
uname = platform.uname()
is_64bit = uname.machine == "x86_64"
is_linux = uname.system == "Linux"
is_windows = uname.system == "Windows"

LUAJIT_DIR = "thirdparty/luajit"

def cmd_or_error(cmd: str):
	exit_code = os.system(cmd)
	if exit_code == 2 and cmd.startswith("make"):
		raise KeyboardInterrupt()
	elif not exit_code == 0:
		raise Exception(cmd + " failed: code " + str(exit_code))
	

def compile_lua_jit():
	print("### Compiling LuaJIT ###")
	# cd into the directory of this file
	os.chdir(script_directory)
	# Get the platform

	os.chdir(LUAJIT_DIR)
	out_lib_name: str = ""
	try:
		if is_linux:
			cmd_or_error("make amalg")
			out_lib_name = "libluajit.a"
		elif is_windows:
			cmd_or_error("%ProgramFiles%\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat" "&&" "msvcbuild.bat")
			out_lib_name = "luajit.lib"
	except Exception as e:
		print("Error while compiling LuaJIT: " + str(e))
		sys.exit(1)

	
	# Copy the lib to the lib directory
	os.chdir(script_directory)
	target_dir = "./lib/public/"
	target_name = ""
	if is_linux and is_64bit:
		target_name = "linux64"
	elif is_linux and not is_64bit:
		target_name = "linux32"
	elif is_windows and is_64bit:
		target_name = "x64"
	elif is_windows and not is_64bit:
		target_name = "x86"
	else:
		print("Platform not supported")
		sys.exit(1)
	
	target_dir += target_name + "/"
	
	os.makedirs(target_dir, exist_ok=True)
	# Copy the lib in a platform agnostic way
	shutil.copyfile(LUAJIT_DIR + "/src/" + out_lib_name, target_dir + out_lib_name)


if __name__ == "__main__":
	if is_linux or is_windows:
		print(
		"######### \n"
		"##### Running " + uname.system + " lib build process\n"
		"#########"
		)
	else:
		print("Platform not supported: " + uname.system)
		sys.exit(1)
	compile_lua_jit()