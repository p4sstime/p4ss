---@type vguiPanel
local testLabel = nil

function Update(frametime)
	-- frames = frames + 1
	-- if frames % 100 == 0 then
	-- 	ConMsg("scoreboard.lua: Update called")
	-- end
end

function Special_ShowPanel(new_visibility)
	testLabel:SetVisible(new_visibility)
end

function Init(parent)
	testLabel = vguiLabel.new(parent, "testLabel", "wtv")
	testLabel.text = "avg is fat and gay!"
	testLabel:SizeToContents()
	ConMsg("scoreboard.lua: Init called")
end
