spinner = {
	hp = 1,
	image = "images\\Spinner.bmp",
	frameSize = { 20, 20 },
	initialFrame = 0,
	collision = {
		{ 0, 0, 20, 20 }
	},
	score = 100,
	spawns = {
		{
			identifier = "laser",
			reload = 120,
			initialState = "normal",
			position = { 8, 10 }
		}
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
	end,
	explodeParticles = {
		{
			image = "images\\explode.bmp",
			frameSize = { 20, 20 },
			count = { 3, 5 },
			center = { 0, 0 },
			positionRadius = { 0, 7 },
			ttl = { 30, 60 },
			speed = { 0, 2 }
		}
	},
	explodeSound = "Sounds\\NFF-cannon.wav",
	explodeVolume = 20,
}
stomper = {
	hp = 10,
	image = "images\\Stomper.bmp",
	collision = {
		{ 0, 30, 120, 10 },
		{ 20, 0, 20, 30}
	},
	score = 500,
	initialFrame = 0,
	frameSize = { 60, 40 },
	movement = function(position)
		if position.y < 100 then
			position.y = position.y + 1
			if position.y < 33 then
				position.frame = 0
			elseif position.y< 67 then
				position.frame =  1
			else
				position.frame = 2
			end
		else
			position.y = position.y + 10
			position.frame = 3
		end
		return position
	end,
	explodeParticles = {
		{
			image = "images\\explode.bmp",
			frameSize = { 20, 20 },
			count = { 8, 16 },
			center = { 20, 10 },
			positionRadius = { 0, 17 },
			ttl = { 30, 60 },
			speed = { 0, 2 }
		}
	},
	explodeSound = "Sounds\\NFF-cannon.wav",
	explodeVolume = 20,
}
laser = {
	hp = 1,
	image = "images\\Laser.bmp",
	collision = {
		{ 0, 0, 4, 10 }
	},
	immune = true,
	movement = function(position)
		position.y = position.y + 5
		return position
	end
}