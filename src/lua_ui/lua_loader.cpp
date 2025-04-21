#include "cbase.h"
#include "lua_loader.h"

const char* loader_text = R""(
local fake_env = {}

local env = {}
env.print = print -- whitelist safe functions
env.coroutine = {
	create = coroutine.create,
	resume = coroutine.resume,
	yield = coroutine.yield,
	status = coroutine.status,
	wrap = coroutine.wrap,
	running = coroutine.running,
}
env._ENV = "PASS Fortress Lua UI"
env._G = env

setmetatable(fake_env, { __index = env })
-- Add any other safe functions/modules here

function LOAD(code, filename)
	local chunk, err = load(code, filename, "t", fake_env)
	if not chunk then
		return nil, err
	end

	local ok, exec_err = pcall(chunk)
	if not ok then
		return nil, exec_err
	end

	return fake_env -- return the sandboxed environment containing Init, Update, etc.
end
)"";