player = {
	image = "images\\Ship.bmp",
	collision = {
		{ 4, 9, 8, 24 },
		{ 28, 9, 8, 24 },
		{ 13, 16, 14, 18 }
	},
	weapons = {
		{
			identifier = "basicBullet",
			reload = 10,
			initialState = "normal",
			position = { 19, 15 }
		}
	}
}
basicBullet = {
	image = "images\\BasicBullet.bmp",
	collision = {
		{ 0, 0, 6, 6 }
	},
	damage = 1,
	movement = function(position)
		position.y = position.y - 10
		return position;
	end
}