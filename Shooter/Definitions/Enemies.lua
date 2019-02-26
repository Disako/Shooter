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
	hp = 50,
	image = "images\\Stomper.bmp",
	collision = {
		{ 0, 30, 60, 10 },
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
			position.y = position.y + 5
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
heavy = {
	hp = 25,
	image = "images\\Heavy.bmp",
	collision = {
		{ 0, 14, 40, 17 },
		{ 17, 0, 6, 14 },
		{ 15, 31, 10, 9 }
	},
	score = 250,
	movement = function(position)
		if position.y < 200 then
			position.y = position.y + 1
			if position.y == 200 then
				if position.x < 300 then
					position.state = "right"
					position.count = 600 - position.x
				else
					position.state = "left"
					position.count = position.x - 600
				end
			end
		elseif position.state == "left" then
			position.x = position.x - 1
			if position.x <= position.count then
				position.state = "down"
			end
		elseif position.state == "right" then
			position.x = position.x + 1
			if position.x >= position.count then
				position.state = "down"
			end
		else
			position.y = position.y + 1
		end
		return position
	end,
	explodeParticles = {
		{
			image = "images\\explode.bmp",
			frameSize = { 20, 20 },
			count = { 8, 16 },
			center = { 10, 10 },
			positionRadius = { 0, 17 },
			ttl = { 30, 60 },
			speed = { 0, 2 }
		}
	},
	explodeSound = "Sounds\\NFF-cannon.wav",
	explodeVolume = 20,
	spawns = {
		{
			identifier = "laser",
			reload = 200,
			initialState = "normal",
			position = { 1, 30 }
		},
		{
			identifier = "laser",
			reload = 200,
			initialState = "normal",
			position = { 18, 16 }
		},
		{
			identifier = "laser",
			reload = 200,
			initialState = "normal",
			position = { 35, 30 }
		}
	},
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