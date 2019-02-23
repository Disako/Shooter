spinner = {
	hp = 1,
	image = "images\\Spinner.bmp",
	frameSize = { 20, 20 },
	initialFrame = 0,
	collision = {
		{ 0, 0, 20, 20 }
	},
	movement = function(position)
		if position.state == "right" then position.x = position.x + 1 else position.x = position.x - 1 end
		position.y = position.y + 1
		position.count = position.count + 1
		if position.count == 10 then
			position.count = 0
			if position.state == "right" then position.frame = position.frame + 1 else position.frame = position.frame - 1 end
		end
		return position
	end
}