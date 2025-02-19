void InitBaseCannons_CalcSpeedV0(ref rCannon, float fFireRange)
{
	rCannon.FireRange = fFireRange;
	rCannon.SpeedV0 = sqrt(fFireRange * 9.81 / sin( 2.0 * MakeFloat(rCannon.FireAngMax)) );
}

void InitCannons()
{
	ref rCannon;
	
    makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS8]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber8";
	rCannon.picture = "cannons1";
	rCannon.Sound = "cannon_fire_culverine_8";
	rCannon.caliber = 8;
	rCannon.ReloadTime = 18;
	rCannon.Cost = 150;
	rCannon.Weight = 3;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 0.7;
	rCannon.hp = 25.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,350.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS12]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber12";
	rCannon.picture = "cannons1";
	rCannon.Sound = "cannon_fire_culverine_12";
	rCannon.caliber = 12;
	rCannon.ReloadTime = 30;
	rCannon.Cost = 250;
	rCannon.Weight = 7;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 1.0;
	rCannon.hp = 40.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,450.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS16]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber16";
	rCannon.picture = "cannons2";
	rCannon.Sound = "cannon_fire_culverine_16";
	rCannon.caliber = 16;
	rCannon.ReloadTime = 45;
	rCannon.Cost = 350;
	rCannon.Weight = 10;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 2.0;
	rCannon.hp = 45.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,550.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS24]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.name = "caliber24";
	rCannon.picture = "cannons3";
	rCannon.Sound = "cannon_fire_culverine_24";
	rCannon.caliber = 24;
	rCannon.ReloadTime = 60;
	rCannon.Cost = 450;
	rCannon.Weight = 15;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 3.0;
	rCannon.hp = 50.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,650.0);

    makeref(rCannon,Cannon[CANNON_TYPE_CULVERINE_LBS32]);
	rCannon.type = CANNON_NAME_CULVERINE;
	rCannon.caliber = 32;
	rCannon.name = "caliber32";
	rCannon.picture = "cannons4";
	rCannon.Sound = "cannon_fire_culverine_32";
	rCannon.ReloadTime = 75;
	rCannon.Cost = 650;
	rCannon.Weight = 20;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 4.0;
	//rCannon.TradeOff = true;
	rCannon.hp = 55.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,750.0);
	
    makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS8]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber8";
	rCannon.picture = "cannons5";
	rCannon.Sound = "cannon_fire_cannon_8";
	rCannon.caliber = 8;
	rCannon.ReloadTime = 10;
	rCannon.Cost = 100;
	rCannon.Weight = 2;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 1.0;
	rCannon.hp = 30.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,300.0);
	
	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS12]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber12";
	rCannon.picture = "cannons5";
	rCannon.Sound = "cannon_fire_cannon_12";
	rCannon.caliber = 12;
	rCannon.ReloadTime = 20;
	rCannon.Cost = 150;
	rCannon.Weight = 6;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 1.5;
	rCannon.hp = 45.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,350.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS16]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber16";
	rCannon.picture = "cannons6";
	rCannon.Sound = "cannon_fire_cannon_16";
	rCannon.caliber = 16;
	rCannon.ReloadTime = 30;
	rCannon.Cost = 250;
	rCannon.Weight = 8;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 2.5;
	rCannon.hp = 50.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,450.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS24]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.name = "caliber24";
	rCannon.picture = "cannons7";
	rCannon.Sound = "cannon_fire_cannon_24";
	rCannon.caliber = 24;
	rCannon.ReloadTime = 40;
	rCannon.Weight = 12;
	rCannon.Cost = 350;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 4.0;
	rCannon.hp = 55.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,550.0);

	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS32]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.caliber = 32;
	rCannon.name = "caliber32";
	rCannon.picture = "cannons8";
	rCannon.Sound = "cannon_fire_cannon_32";
	rCannon.ReloadTime = 50;
	rCannon.Cost = 550;
	rCannon.Weight = 16;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 5.0;
	//rCannon.TradeOff = true;
	rCannon.hp = 60.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,650.0);
	
	/*makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS36]);
	rCannon.type = CANNON_NAME_SPECIAL_CANNON;
	rCannon.caliber = 36;
	rCannon.name = "caliber36";
	rCannon.picture = "cannons10";
	rCannon.Sound = "fort_cannon_fire";
	rCannon.ReloadTime = 120;
	rCannon.Cost = 500;
	rCannon.Weight = 90;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 8.0;
	rCannon.TradeOff = true;
	rCannon.hp = 65.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,800.0);    */
	
	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS42]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.caliber = 42;
	rCannon.name = "caliber42";
	rCannon.picture = "cannons11";
	rCannon.Sound = "cannon_fire_cannon_42";
	rCannon.ReloadTime = 60;
	rCannon.Cost = 850;
	rCannon.Weight = 22;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 6.0;
	rCannon.TradeOff = true;
	rCannon.hp = 70.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,800.0);
	
	makeref(rCannon,Cannon[CANNON_TYPE_CANNON_LBS48]);
	rCannon.type = CANNON_NAME_CANNON;
	rCannon.caliber = 48;
	rCannon.name = "caliber48";
	rCannon.picture = "cannons12";
	rCannon.Sound = "cannon_fire_cannon_48";
	rCannon.ReloadTime = 50;
	rCannon.Cost = 1000;
	rCannon.Weight = 30;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.DamageMultiply = 10.0;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.TradeOff = true;
	rCannon.hp = 80.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,1600.0);

	/*makeref(rCannon,Cannon[CANNON_TYPE_MORTAR]);
	rCannon.type = CANNON_NAME_MORTAR;
	rCannon.caliber = 92;
	rCannon.name = "caliber92";
	rCannon.picture = "cannons13";
	rCannon.Sound = "fort_cannon_fire";
	rCannon.ReloadTime = 240;
	rCannon.Cost = 2000;
	rCannon.Weight = 160;
	rCannon.FireAngMax = 0.80;
	rCannon.FireAngMin = -0.35;
	rCannon.DamageMultiply = 25.0;
	rCannon.TimeSpeedMultiply = 0.8;
	rCannon.BigBall = 1;
	rCannon.SizeMultiply = 5.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.TradeOff = true;
	rCannon.hp = 80.0;
	InitBaseCannons_CalcSpeedV0(&rCannon,650.0);    */
}