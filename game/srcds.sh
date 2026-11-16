#!/bin/bash

# figure out the absolute path to the script being run a bit
# non-obvious, the ${0%/*} pulls the path out of $0, cd's into the
# specified directory, then uses $PWD to figure out where that
# directory lives - and all this in a subshell, so we don't affect
# $PWD

EXEC_NAME=$(basename "$0" .sh)
GAMEROOT=$(cd "${0%/*}" && echo $PWD)

plat_dir=linux64
plat_suffix=_linux64

# and launch the game
cd "$GAMEROOT"

######

# find the TF2 dedicated server, same as the launcher does
TF_PATH=""
GAME_ARGS=(-game "$GAMEROOT/p4ss")

args=("$@")
for (( i = 0; i < ${#args[@]}; i++ )); do
	case "${args[i]}" in
		-tf_path) TF_PATH="${args[i + 1]}" ;;
		-game) GAME_ARGS=() ;;
	esac
done

if [ -z "$TF_PATH" ]; then
	for path in . "../Team Fortress 2 Dedicated Server" ../tf2ds ../tf2_ds "../Team Fortress 2" ../tf2; do
		if [ -f "$path/bin/$plat_dir/dedicated_srv.so" ]; then
			TF_PATH="$path"
			break
		fi
	done
fi

# prepend the TF2 dedicated server lib path to LD_LIBRARY_PATH
export LD_LIBRARY_PATH="${TF_PATH}/bin/$plat_dir":$LD_LIBRARY_PATH

if [ -z $GAMEEXE ]; then
	GAMEEXE="${EXEC_NAME}"$plat_suffix
fi

ulimit -n 2048

# Enable path match if we are running with loose files
if [ -f pathmatch.inf ]; then
	export ENABLE_PATHMATCH=1
fi

# Do the following for strace:
# 	GAME_DEBUGGER="strace -f -o strace.log"

STATUS=42
while [ $STATUS -eq 42 ]; do
	if [ "${GAME_DEBUGGER}" == "gdb" ] || [ "${GAME_DEBUGGER}" == "cgdb" ]; then
		ARGSFILE=$(mktemp $USER.$EXEC_NAME.gdb.XXXX)
		echo b main > "$ARGSFILE"

		# Set the LD_PRELOAD varname in the debugger, and unset the global version. This makes it so that
		#   gameoverlayrenderer.so and the other preload objects aren't loaded in our debugger's process.
		echo set env LD_PRELOAD=$LD_PRELOAD >> "$ARGSFILE"
		echo show env LD_PRELOAD >> "$ARGSFILE"
		unset LD_PRELOAD

		echo run $@ "${GAME_ARGS[@]}" >> "$ARGSFILE"
		echo show args >> "$ARGSFILE"
		${GAME_DEBUGGER} "${GAMEROOT}"/${GAMEEXE} -x "$ARGSFILE"
		rm "$ARGSFILE"
	else
		${GAME_DEBUGGER} "${GAMEROOT}"/${GAMEEXE} "$@" "${GAME_ARGS[@]}"
	fi
	STATUS=$?
done

exit $STATUS
