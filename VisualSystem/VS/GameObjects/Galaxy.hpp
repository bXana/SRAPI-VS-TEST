///////////////////////////////////////
//		GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Galaxy API
///////////////////////////////////////

#ifndef _GALAXY_HPP_
#define _GALAXY_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "GameObject.hpp"
#include "Star.hpp"
#include "Sector.hpp"

// Стандартные настройки галактики
// Лимит значний [ 0, 9 ]
struct SGalaxySettings
{
	// Крутость пиратов
	Byte Pirates;	 // 0
	// Разброс цен
	Byte Values;	 // 1 
	// Учёные
	Byte Science;	 // 2
	// Поломки
	Byte Breakdowns; // 3
	// Оборудование
	Byte Equipment;  // 4
	// Задания
	Byte Tasks;		 // 5
	// Черные дыры
	Byte BlackHoles; // 6
	// Удача
	Byte Luck;		 // 7

};

// Тонкая настройка
struct SAdjustmentSettings
{
	public:
		Bool IronWill; // Железная воля
		// Включена ли тонкая настройка
		// Если выключена, ни одна из дополнительных настроек работать не будет
		Bool AdvancedSettings; 

		// Формула: ( Value * 6,25 + 50 ) = ProcentValue

		// Оснащение доминаторов
		// ByteValue * 6,25 + 50 = Procent Value
		Byte DominatorEquipmentRatio;
		// Агрессивность доминаторов
		Byte DominatorAggressiveRatio;
		// Частота респавна доминаторов
		Byte DominatorRespawnRateRatio;
		// Агрессивность пиратского клана
		Byte PirateClanAggressiveRatio;
		// Агрессивность коалиции
		Byte CoalitionAggressiveRatio;
		// Количество астероидов в системе
		Byte AsteroidsRatio;
		// Урон звезды
		Byte StarDamageRatio;
		// Бонус к стартовым технологиям 0-255
		Byte TechLvlBonus;
		// Соотношение числа акриновых вещей
		Byte ShopAkrinCount;
		// Коэффициент выпадения нодов
		Byte DominatorNodeDropRatio;
		// Ценность оборудования в аркадном бою
		Byte EquipmentValueInHyperRatio;
		// Ценность оборудования в обычном пространстве
		Byte EquipmentValueInSpaceRatio; 
		// Соотношение аграрных планет
		Byte GalaxyAgrarPlanetsCount;
		// Соотношение планет со смешанной экономикой
		Byte GalaxyMixedPlanetsCount;
		// Соотношение индустриальных планет
		Byte GalaxyIndustrialPlanetsCount;
		// Количество дополнительных рейнджеров
		Byte AdditionalRangersCount;
		// Хп кораблей в гипере
		Byte ShipHPInHyperRatio;
		// Урон кораблей в гипере
		Byte ShipDamageInHyperRatio;
		// Лимит предметов в системе после чего они расстреливаются
		Byte StarItemsLimit;
		// Рандомные события
		Bool UseRandom;
		// Возможность чинить ГТУ без ограничений
		Bool InteractWithAllItems;
		// Строить станции в центре системы
		Bool BuildStationsInCenter;
		// Вдали игрока станции сражаются как всегда, а не пропускают выстрелы
		Bool StationsFight;
		// Корпуса из перезагрузки
		Bool UseOldShips;
		// Спавн без опыта
		Bool SpawnWithoutExperience;
		// Боты атакуют друг друга в гипере
		Bool BotsAttackAllInHyper;
		// Доминаторы используют оружие только своей серии
		Bool DominatorsUseOwnWeapons;
		// Стартовая система в центре
		Bool HomeSystemInCenter;
		// Боты стреляют ракетами/торпедами с максимальной дистанции
		Bool BotsUseRocketsOnMaxDistance;
		// Добавить гипер перелёты
		Bool FlyInHyper;
		// Продажа нодов на пиратских станциях
		Bool BuyNodesOnPirateBase;
		// Боты покупают оборудование только на планетах и базах
		Bool BotsBuyEquipment;
		// Станции обновляют оборудование из своего магазина
		Bool StationsBuyEquipment;
		// Использование нескольких артефактов.
		Bool UseSameArtefacts;
		// Размер корпусов 
		Byte ShipSizeFlag;
		// Смена оборудования в аркадном бою
		Bool ChangeEquipmentInHyper;
		// Использование линейной формулы расчёта скорости
		Bool UseOldSpeedCalculation;
		// Использование акринового бонуса на каждую ракету, а не на залп в среднем
		Bool UseRocketAkrinFlag;
};

class C_GALAXY : public C_OBJECT
{ 
		friend CSpaceRangersAPI;
		friend C_HIDDEN_PLANET;
		
		static void* GetLocalPlayer_;
	public:
		// Корабль игрока
		void SR_API Player( C_SHIP* pShip );

		// Количество секторов в галактике
		UInt	  SR_API SectorsCount( void );
		C_SECTOR* SR_API Sector( const UInt SectorNumber );

		// Количество систем в галактике
		UInt    SR_API StarsCount( void );
		C_STAR* SR_API Star( const UInt StarNumber );

		// Возвращает текущий ход
		UInt SR_API CurrentDay( void );

		// Возвращает/устанавливает информацию тонкой настройки
		void SR_API AdjustmentSettings( SAdjustmentSettings* Settings );
		void SR_API SetAdjustmentSettings( const SAdjustmentSettings* Settings );

		// Возвращает/устанавливает настройки галактики
		void SR_API Settings( SGalaxySettings* Settings_ );
		void SR_API SetSettings( SGalaxySettings* Settings_ );
};


#endif