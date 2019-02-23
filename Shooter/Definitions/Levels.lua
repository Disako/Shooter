level1={
	{
		action = "music",
		file = "music\\BoxCat_Games_-_25_-_Victory.mp3",
		volume = 100,
		fade = 1000
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