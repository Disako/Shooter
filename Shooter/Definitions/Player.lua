player = {
	image = "images\\Ship.bmp",
	collision = {
		{ 29, 20, 22, 37 },
		{ 14, 46, 15, 22 },
		{ 51, 46, 15, 22 }
	},
	weapons = {
		{
			identifier = "basicBullet",
			reload = 10,
			initialState = "normal",
			position = { 37, 0 }
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