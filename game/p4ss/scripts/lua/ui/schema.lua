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

--- @class vguiPanel
vguiPanel = {
	--- Construct a new Panel.
	--- @param parent vguiPanel?
	--- @param name string?
	--- @return vguiPanel
	new = function(parent, name) end,

	--- Set this panel visible. (will be rendered on the next frame)
	---@param self vguiPanel
	---@param visible any
	SetVisible = function(self, visible) end,

	--- Set this panel's position.
	--- @param self vguiPanel
	--- @param x number
	--- @param y number
	SetPos = function(self, x, y) end,

	--- Set this panel's size.
	--- @param self vguiPanel
	--- @param x number
	--- @param y number
	SetSize = function(self, x, y) end,

	--- Get the parent panel of this panel.
	--- @param self vguiPanel
	--- @param x number
	--- @param y number
	--- @return vguiPanel?
	GetParent = function(self, x, y) end,
}

--- @class vguiLabel : vguiPanel
vguiLabel = {
	--- Construct a new Label.
	--- @param parent vguiPanel
	--- @param name string
	--- @param initialText string
	--- @return vguiLabel
	new = function(parent, name, initialText) end,
	SetTextLocalized = function(self, text) end,
}
