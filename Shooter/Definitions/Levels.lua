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
		location = { 300, 400 }
	},
	{
		action = "backgroundObj",
		type = "smallStar",
		probability = 10,
		fill = 480 * 4
	},
	{
		action = "backgroundObj",
		type = "bigStar",
		probability = 5,
		fill = 480 * 2
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