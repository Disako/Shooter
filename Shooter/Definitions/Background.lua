smallStar = {
	image = "images\\SmallStar.bmp",
	x = {-4, 639 },
	y = {-5, -5 },
	fillX = {-4, 639 },
	fillY = { -5, 479 },
	fillMultiplier = 4 * 480,
	movement = function(position)
		position.count = position.count + 1
		if position.count == 4 then
			position.y = position.y + 1
			position.count = 0
		end
		return position
	end
}
bigStar = {
	image = "images\\BigStar.bmp",
	x = {-6, 639 },
	y = {-7, -7 },
	fillX = {-6, 639 },
	fillY = { -7, 479 },
	fillMultiplier = 2 * 480,
	movement = function(position)
		position.count = position.count + 1
		if position.count == 2 then
			position.y = position.y + 1
			position.count = 0
		end
		return position
	end
}