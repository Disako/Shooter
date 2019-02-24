player = {
	image = "images\\Ship.bmp",
	levelCollision = {
		{
			{ 17, 16, 6, 12 }
		},
		{
			{ 4, 9, 8, 24 },
			{ 28, 9, 8, 24 },
			{ 13, 16, 14, 18 }
		},
		{
			{ 4, 9, 8, 24 },
			{ 28, 9, 8, 24 },
			{ 13, 16, 14, 18 }
		},
		{
			{ 4, 9, 8, 24 },
			{ 28, 9, 8, 24 },
			{ 13, 16, 14, 18 }
		}
	},
	frameSize = { 40, 40 },
	weapons = {
		{
			identifier = "basicBullet",
			reload = 20,
			initialState = "normal",
			position = { 17, 15 },
			fireSound = "Sounds\\NFF-laser.wav",
			fireVolume = 10,
			minLevel = 1,
			maxLevel = 3
		},
		{
			identifier = "basicBullet",
			reload = 20,
			initialState = "left",
			position = { 0, 15 },
			minLevel = 2,
			maxLevel = 4
		},
		{
			identifier = "basicBullet",
			reload = 20,
			initialState = "right",
			position = { 34, 15 },
			minLevel = 2,
			maxLevel = 4
		}
	},
	maxLevel = 4,
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
		if position.state == "normal" then
			position.y = position.y - 10
		elseif position.state == "left" then 
			position.y = position.y - 8
			position.x = position.x - 6
		elseif position.state == "right" then
			position.y = position.y - 8
			position.x = position.x + 6
		end
		return position;
	end
}
upgrader = {
	image = "images\\Upgrader.bmp",
	frameSize = { 20, 20 },
	collision = { { 0, 5, 20, 15 } },
	movement = function(position)
		position.count = position.count + 1
		if position.count >= 6 then
			position.count = 0
			position.frame = position.frame + 1
		end
		position.y = position.y - 1
		return position
	end
}