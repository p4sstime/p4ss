--- Called every frame.
--- @param frametime number
function Update(frametime) end

--- Called once on Lua initialization.
--- @param parent vguiPanel
function Init(parent)
	ConMsg("Hello, world from Lua!")
end
