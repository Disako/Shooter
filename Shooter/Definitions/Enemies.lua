spinner = {
	hp = 1,
	image = "images\\Spinner.bmp",
	collision = {
		{ 29, 23, 22, 37 },
		{ 14, 14, 15, 22 },
		{ 51, 14, 15, 22 }
	},
	movement = function(position)
		if position.state == "right" then position.x = position.x + 1 else position.x = position.x - 1 end
		position.y = position.y + 1
		return position;
	end
}