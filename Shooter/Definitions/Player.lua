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
			reload = 20,
			initialState = "normal",
			position = { 17, 15 },
			fireSound = "Sounds\\NFF-laser.wav",
			fireVolume = 10
		}
	},
	explodeSound = "Sounds\\NFF-cannon.wav",
	explodeVolume = 20,
	explodeParticles = {
		{
			image = "images\\explode.bmp",
			frameSize = { 20, 20 },
			count = { 6, 10 },
			center = { 10, 10 },
			positionRadius = { 0, 17 },
			ttl = { 30, 60 },
			speed = { 0, 2 }
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