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
	explodeVolume = 20
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