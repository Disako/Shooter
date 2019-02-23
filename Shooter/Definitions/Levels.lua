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