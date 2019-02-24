startUp={
	{
		action = "music",
		file = "music\\BoxCat_Games_-_25_-_Victory.mp3",
		volume = 100,
		fade = 1000
	},
	{
		action = "player",
		player = "player",
		level = 2,
		location = { 300, 400 }
	},
	{
		action = "backgroundObj",
		type = "smallStar",
		probability = 10,
		fill = true
	},
	{
		action = "backgroundObj",
		type = "bigStar",
		probability = 5,
		fill = true
	},
	{
		action = "level",
		level = "level1"
	}
}
level1={
	{
		action = "spawn",
		enemy = "spinner",
		location = { 0, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 600, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 40, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 560, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 80, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 520, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 300
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 290, -40 }
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "upgrade",
		upgrader = "upgrader",
		location = { 110, 480 },
		state = "left"
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 310, -20 },
		state = "left"
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 310, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 270, -20 },
		state = "left"
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 350, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 230, -20 },
		state = "left"
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 390, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 300
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 460, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 460, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 460, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 460, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 460, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 0, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 600, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 40, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 560, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 80, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 520, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "upgrade",
		upgrader = "upgrader",
		location = { 510, 480 },
		state = "right"
	},
	{
		action = "wait",
		frames = 300
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 140, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 140, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 140, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "heavy",
		location = { 140, -40 }
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 0, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 600, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 40, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 560, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 80, -20 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 520, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 100
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 290, -40 }
	},
	{
		action = "wait",
		frames = 20
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 200, -40 }
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 380, -40 }
	},
	{
		action = "wait",
		frames = 20
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 110, -40 }
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 470, -40 }
	},
	{
		action = "wait",
		frames = 20
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 20, -40 }
	},
	{
		action = "spawn",
		enemy = "stomper",
		location = { 560, -40 }
	},
	{
		action = "wait",
		frames = 100
	},
}