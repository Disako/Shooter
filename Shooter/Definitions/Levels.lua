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
		location = { 560, -20 },
		state = "left"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "level",
		level = "level1"
	}
}