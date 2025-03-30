---@meta

---@description The UI module.
UI = {
	---@class UI.Panel
	Panel = {
		---@description Creates a new panel.
		---@return UI.Panel #The new panel.
		new = function() end,

		---@type UI.Panel|nil
		---@description The parent of the panel.
		Parent = nil,

		--- @type function
		--- @param self UI.Panel
		--- @param child UI.Panel The child panel to render.
		--- @description Renders a child on this panel.
		RenderChild = function(self, child) end,
	},
	---@description Gets an item by its VGUI name.
	---@param className string The VGUI name of the item to get.
	---@return UI.Panel #The item with the specified class name.
	GetItemByClassName = function(className) end,
}
