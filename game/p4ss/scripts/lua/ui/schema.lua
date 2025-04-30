---@meta
--- This file is not a Lua script. It is a description of available globals
--- for LSPs and IDEs to provide autocompletion and type checking.
--- It is not loaded by the game.

--- Send an informational message to the console.
ConMsg = function(...) end
--- Send a warning message to the console.
ConWarn = function(...) end

--- Error out of the current function and log to the console.
--- @param reason any
--- @param level integer?
error = function(reason, level) end

--- @class Panel
--- @field parent Panel?
--- @field visible boolean
vguiPanel = {
	--- Construct a new Panel.
	--- @param parent Panel?
	--- @param name string?
	new = function(parent, name) end,

	--- Set this panel visible. (will be rendered on the next frame)
	---@param self Panel
	---@param visible any
	SetVisible = function(self, visible) end,

	--- Set this panel's position.
	--- @param self Panel
	--- @param x number
	--- @param y number
	SetPos = function(self, x, y) end,

	--- Set this panel's size.
	--- @param self Panel
	--- @param x number
	--- @param y number
	SetSize = function(self, x, y) end,

	--- Get the parent panel of this panel.
	--- @param self Panel
	--- @param x number
	--- @param y number
	--- @return Panel?
	GetParent = function(self, x, y) end,
}
