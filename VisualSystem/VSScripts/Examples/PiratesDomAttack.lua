-- Pirates Dominator Attack ver. 1.0.
-- Author : bAnXZ
-- Rus Description:
-- Анализирует ситуацию в галактике, и даёт приказ пиратам начать атаку на системы доминаторов

math.randomseed( os.time() )

local PirateSystems, DominatorSystems = {}, {}

for _, Star in ipairs( Galaxy:Stars() ) do
	local StarFraction = Star:Fraction()
	if StarFraction == 1 then
		table.insert( DominatorSystems, Star )
	elseif StarFraction == 2 then
		table.insert( PirateSystems, Star )
	end
end

for _, PirateSystem in ipairs( PirateSystems ) do
	local TargetSystem = DominatorSystems[ math.random( 1, #DominatorSystems ) ]
	for __, Ship in ipairs( PirateSystem:Ships() ) do
		if Ship:Type() == 3 then
			Ship:Jump( TargetSystem, true )
		end
	end
end