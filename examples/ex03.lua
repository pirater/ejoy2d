local ej = require "ejoy2d"
local pack = require "ejoy2d.simplepackage"
local fw = require "ejoy2d.framework"
local particle = require "ejoy2d.particle"

pack.load {
	pattern = fw.WorkDir..[[examples/asset/?]],
	"sample",
}
particle.preload(fw.WorkDir.."examples/asset/particle")

local ps = particle.new("ps")

local obj = ej.sprite("sample","cannon")
local turret = obj.turret

local obj2 = ej.sprite("sample","mine")
obj2.resource.frame = 70
obj2.label.text = "Hello World"

local game = {}

function game.update()
	turret.frame = turret.frame + 3
	obj2.frame = obj2.frame + 1

	ps:update(0.0333,0,0)
end

local pos = {x = 70, y= 400, scale = 0.8}
local pos2 = { x = 270, y = 400 }
local pos3 = {x = -160, y = -300}

function game.drawframe()
	obj:draw(pos)
	obj2:draw(pos2)

	ps:draw(pos3)
end

function game.touch(what, x, y)
end

ej.start(game)


