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
		},
		{
			identifier = "missile",
			reload = 50,
			position = { 2, 20 },
			minLevel = 3,
			maxLevel = 4,
			fireSound = "Sounds\\NFF-leap-out-02.wav"
		},
		{
			identifier = "missile",
			reload = 50,
			position = { 30, 20 },
			minLevel = 3,
			maxLevel = 4
		},
		{
			identifier = "obliterate",
			reload = 1,
			position = { 18, -465 },
			minLevel = 4,
			maxLevel = 4,
			fireSound = "Sounds\\NFF-magic-whip.wav",
			fireVolume = 50,
			soundFrequency = 20
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
		return position
	end
}
missile = {
	image = "images\\Missile.bmp",
	collision = { { 0, 0, 8, 10 } },
	frameSize = { 8, 10 },
	damage = 3,
	movement = function(position)
		if position.count < 120 then
			position.count = position.count + 1
		end
		position.y = position.y - math.floor(position.count / 24) - 1
		position.frame = position.frame + 1
		return position
	end
}
obliterate = {
	image = "images\\obliterate.bmp",
	collision = { { 0, 0, 4, 480 } },
	damage = 1,
	movement = function(position)
		if position.count == 0 then position.count = 1 else position.x = 1000 end
		return position
	end
}
upgrader = {
	image = "images\\Upgrader.bmp",
	frameSize = { 20, 20 },
	collision = { { 0, 5, 20, 15 } },
	movement = function(position)
		position.count = position.count + 1
		if position.count % 10 == 0 then
			position.frame = position.frame + 1
		end
		if position.state == "left" then
			position.x = 310 - math.floor(math.cos(math.rad(position.count / 3)) * 200)
		else
			position.x = 310 + math.floor(math.cos(math.rad(position.count / 3)) * 200)
		end
		position.y = 480 - math.floor(math.sin(math.rad(position.count / 3)) * 150)	
		return position
	end
}