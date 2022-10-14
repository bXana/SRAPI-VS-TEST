-- GalaxyVisualGenerator ver. 1.0.
-- Author: bAnXZ
-- Rus Description:
-- Произвольно устанавливает иные модели планет и звезд, и фоны

-- Функция на проверку наличия элемента в таблице
local function ElementChecker( Table, Elem )
	for _, Element in ipairs( Table ) do
		if Element == Elem then
			return true
		end
	end
	return false
end

-- Загруженные фоны, модели планет и звезд
local LoadedFonts, LoadedPlanets, LoadedStars = {}, {}, {}

-- Получаем информацию загруженных моделей, фонов
-- Проходим по каждой звезде отдельно
for _, Star in ipairs( Galaxy:Stars() ) do
	local FonImage  = Star:FonImage()
	local StarModel = Star:VisualModel() 
	-- Если в таблице нет данного фона, значит добавляем его
	if not ElementChecker( LoadedFonts, FonImage ) then
		table.insert( LoadedFonts, FonImage )
	end
	
	-- Если в таблице нет данной модели звезды - добавляем
	if not ElementChecker( LoadedStars, StarModel ) then
		table.insert( LoadedStars, StarModel )
	end
	
	-- Проходим по всем планетам системы
	for __, Planet in ipairs( Star:Planets() ) do
		local PlanetModel = Planet:VisualModel()
		-- Если в таблице нет данной модели планеты, - добавляем
		if not ElementChecker( LoadedPlanets, PlanetModel ) then
			table.insert( LoadedPlanets, PlanetModel )
		end
	end
end

-- Рандомизируем вид галактики
math.randomseed( os.time() )

for _, Star in ipairs( Galaxy:Stars() ) do
	-- Устанавливаем новый фон системы
	Star:SetFonImage( LoadedFonts[ math.random( 1, #LoadedFonts ) ] )
	-- Устанавливаем новую модель звезды
	Star:SetVisualModel( LoadedStars[ math.random( 1, #LoadedStars ) ] )
	
	-- Проходим по каждой планете системы
	for __, Planet in ipairs( Star:Planets() ) do
		-- Устанавливаем новую модель планеты
		Planet:SetVisualModel( LoadedPlanets[ math.random( 1, #LoadedPlanets ) ] )
	end
end
