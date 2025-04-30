local visible = false

local frames = 0

local testLabel = nil

function Update(frametime)
	frames = frames + 1
	if frames % 100 == 0 then
		ConMsg("scoreboard.lua: Update called")
	end
end

function Special_ShowPanel(new_visibility)
	ConMsg("Type: ", type(new_visibility))
	if new_visibility then
		ConMsg("scoreboard.lua: SETVISIBLE called with true")
	else
		ConMsg("scoreboard.lua: SETVISIBLE called with false")
	end
end

function Init(parent)
	testLabel = vguiPanel.new(parent, "testLabel")
	ConMsg("scoreboard.lua: Init called")
end
