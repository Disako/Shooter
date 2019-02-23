level1={
	{
		action = "spawn",
		enemy = "spinner",
		location = { 0, -80 },
		state = "right"
	},
	{
		action = "wait",
		frames = 60
	},
	{
		action = "spawn",
		enemy = "spinner",
		location = { 560, -80 },
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