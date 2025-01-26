// boal 08/04/06 общий диалог верфи
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm;
	
	ref rRealShip;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "Master_Ship";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			
			if (CheckChit() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("Вот уж не думал, что встречу Бога еще на этом свете... Хотя это как посмотреть: если прищуриться, то видно отражение мошенника на мониторе. Проваливай!","У-у-у, кого я вижу! Да это же ломовых дел мастер! А мне тут ломать нечего, убирайся, не то стражу кликну!"), RandPhraseSimple("Скажи, мил человек, только честно: тебе хочется поиграть, или всенепременно выиграть? Хотя честности от тебя дождешься не раньше, чем наш губернатор обедню петухом пропоет... Скатертью дорога, ломщик!","Фу ты, ну ты, никак сам губернатор Калифорнии пожаловал! Ой, нет, это же Терминатор...нет! Не Терминатор, а махинатор, ха-ха-ха! Проваливай, клоун."));
            		link.l1 = LinkRandPhrase("Эх, не дают читерам жить спокойно. Даже отсюда гонят.","Ты чего взъелся? Я лишь чуть-чуть игру ломанул... ладно-ладно, ухожу.","Хех! А мне говорили - против лома нет приема...");
            		link.l1.go = "exit";
					break;
                }
			NextDiag.TempNode = "First time";
			
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("Эй, доктор Блад! " + TimeGreeting() + ".",
                                    "Рад видеть Вас, Питер Блад.",
                                    "Хорошо, что Вы заглянули ко мне, " + GetFullName(pchar) + ". Как поживает полковник Бишоп?");
                Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
                {
                    Link.l2 = "Мне нужно помочь одному... моему другу попасть в Порто Белло.";
    				Link.l2.go = "Blood_Shipyard1";
                }
				break;
            }
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = TimeGreeting() + "! Я "+ GetFullName(NPChar) + ", владелец этой верфи.";
				Link.l1 = "Рад"+ GetSexPhrase("","а") +" знакомству. Я капитан " + GetFullName(Pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				//--->> квест украсть чертеж на верфи
				//дача квеста
				if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questShipyardsMap") > 7 && !CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 25)
				{
					dialog.text = "Послушайте, у меня есть к вам одно важное дело. Надеюсь, сумеете мне помочь...";					
					link.l1 = "Давайте послушаем, что за дело.";
					link.l1.go = "ShipyardsMap_1";
					SaveCurrentNpcQuestDateParam(npchar, "questShipyardsMap");
					break;
				}
				//<<--- квест украсть чертеж на верфи			
				
				dialog.Text = pcharrepphrase("А, это опять ты? Ну да ладно, деньги не пахнут.",
                                        TimeGreeting() + ", чем я могу помочь вам, " + GetAddress_Form(NPChar) + "?");
				Link.l1 = pcharrepphrase("Вот-вот, я плачу - ты делаешь.",
                                        "Нужно воспользоваться услугами верфи.");
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "Мне нужны орудия на корабль.";
					link.l11.go = "Cannons";
				}	
			    link.l12 = "Хочу изменить внешний вид парусов.";
			    link.l12.go = "SailsGerald";
				Link.l2 = "Я только хочу поговорить.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о делах финансовых.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
				//--> квест Аззи.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = "Слушай, у меня есть одна штука - жестянка. Мне нужно аккуратненько ее вскрыть. Сможешь сделать это? Я заплачу.";
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- на квест Аззи.
				//проверка выполнения квеста украсть чертеж на верфи
				if (CheckCharacterItem(pchar, "ShipyardsMap") && CheckAttribute(pchar, "questTemp.different.ShipyardsMap.Id") && pchar.questTemp.different.ShipyardsMap.Id == npchar.id)
				{				
					link.l6 = "Я выполнил"+ GetSexPhrase("","а") +" ваше поручение. Чертеж из верфи " + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + " у меня.";
					link.l6.go = "ShipyardsMapOk_1";
				}
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "Я по поводу вашей дочери...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "Мне нужно идти.";
				Link.l9.go = "exit";
			}
		break;
		
		case "Meeting":
				dialog.Text = "Хорошо, я рад встрече с новым клиентом. Моя верфь к вашим услугам.";
				Link.l1 = "Великолепно, " + GetFullName(NPChar) + ". Давайте посмотрим то, что вы можете мне предложить.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Мне нужны орудия на корабль.";
					link.l13.go = "Cannons";
				}	
				link.l12 = "Хочу изменить внешний вид парусов.";
			    link.l12.go = "SailsGerald";
				Link.l2 = "Я только хочу поговорить.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о делах финансовых.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
				//--> квест Аззи.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = "Слушай, у меня есть одна штука - жестянка. Мне нужно аккуратненько ее вскрыть. Сможешь сделать это? Я заплачу.";
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- на квест Аззи.
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "Я по поводу вашей дочери...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Что вы можете сказать о владельце этих документов?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Я долж"+ GetSexPhrase("ен","на") +" идти. Благодарю вас.";
				Link.l11.go = "exit";
		break;
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Дайте-ка взглянуть ! Нет, таковой у меня не был. Думаю, Вам стоит зайти к начальнику порта.";
				link.l1 = "Несомненно....";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Дайте-ка взглянуть, капитан! Ага! Это же судовые документы моего хорошего друга, можно сказать, самого любимого клиента. Я уверен, он будет несказанно рад находке, и даже выплатит премиальные.";
				sTemp = sTemp + "Думаю, что могу Вам предложить " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " золотых от его имени";
				dialog.text = sTemp;
				link.l1	= "Пожалуй, не стоит ...";
				link.l1.go = "exit";
				link.l2 = "Благодарю, " + GetFullName(NPChar) + "! Передавайте поклон Вашему другу.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("","а"));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её...\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим...\nДа... я обещал вознаграждение тому, кто её вернёт - примите пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть "+ GetSexPhrase("тот капитан, который привез","та девушка, которая привезла") +", моего блудного сына с молодой невестой?";
				link.l1 = "Да, это я помог"+ GetSexPhrase("","ла") +" им сбежать.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "А-а, явил"+ GetSexPhrase("ся, благодетель","ась, благодетельница") +". Небось награды ждёшь?";
				link.l1 = "Ну, не то, чтобы награды, но благодарность услышать не мешало бы.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Я очень вам благодарен, что не оставили моё чадо в затруднительном положении и помогли ему с честью выйти из столь щекотливой ситуации. Разрешите отблагодарить вас, как могу. Примите эту скромную сумму и подарок от меня лично.";
			link.l1 = "Благодарю вас, мне было приятно помогать этим молодым людям.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Какая благодарность?! за что благодарность?! Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
			link.l1 = "Хм, значит вы не верите в искренние чувства?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодёжи в таких делах потакать, да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
			link.l1 = "Что ж, и вам не хворать...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "shipyard":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Perl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Perl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Сменить цвет парусов стоит " +
				              FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE))+
							  ", поставить новый герб стоит " +
							  FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) +
							  ", цена смены типа парусины зависит от материала.";
							  
			    link.l1 = "Выбрать новый цвет.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Изобразить новый герб.";
			    link.l2.go = "SailsGeraldChoose";
			    
				// Паруса ЛГ
				if(!CheckForFlyingDuchmanSails(PChar))
				{
					link.l3 = "Изменить материал парусов."; // Материал изменить нельзя, если стоят паруса ЛГ
					link.l3.go = "SailsTypeChoose";
					link.l4 = "Я хочу установить устрашающие паруса, как на легендарном корабле-призраке!";
					link.l4.go = "FlyingDutchmanSails";
				}
				else
				{
					link.l4 = "Я хочу убрать устрашающие паруса.";
					link.l4.go = "FlyingDutchmanSails_Clear";
				}
				
			    Link.l9 = "Я передумал"+ GetSexPhrase("","а") +".";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Pearl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		
		// Warship 16.06.09 Паруса ЛГ
		case "FlyingDutchmanSails":
			if(iShipClass < 4)
			{
				iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
				dialog.text = "Да, я как раз придумал интересную геометрию паруса: он напоминает рваный, чтобы книппели и ядра наносили меньший ущерб. Его, кстати, можно пошить из ненового сукна. Думаю, для вашего корабля такой комплект будет стоить " + FindRussianMoneyString(iSumm) + ".";
				
				if(sti(PChar.money) >= iSumm)
				{
					Link.l1 = "Отлично! Меня это устраивает.";
					Link.l1.go = "FlyingDutchmanSails_SetDuchman";
				}
				
				Link.l2 = "Какая несуразная цена! Забудьте об этом.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "На Вашем судне такие паруса будут выглядеть потешно. Подыщите более внушительный корабль...";
				Link.l1 = "Буду искать, куда деваться-то...";
				Link.l1.go = "exit";
			}
		break;
		
		case "FlyingDutchmanSails_SetDuchman":
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
			
			AddMoneyToCharacter(PChar, -iSumm);
			
			dialog.text = "Замечательно. Все сделаем в лучшем виде.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
			
			SetShipSailsFromFile(PChar, "ships/parus_common_torn.tga"); // Паруса ЛГ
			
			WaitDate("", 0, 0, 0, 1, 30);
		break;
		
		// Убрать паруса ЛГ
		case "FlyingDutchmanSails_Clear":
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
			
			dialog.text = "Ну, убрать так убрать. Это обойдется тебе в " + FindRussianMoneyString(iSumm) + ".";
			
			if(sti(PChar.money) >= iSumm)
			{
				Link.l1 = "Отлично! Меня это устраивает.";
				Link.l1.go = "FlyingDutchmanSails_SetNormal";
			}
			
			Link.l2 = "Какая несуразная цена! Забудьте об этом.";
			Link.l2.go = "exit";
		break;
		
		case "FlyingDutchmanSails_SetNormal":
			rRealShip = GetRealShip(sti(PChar.Ship.Type));
			
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
			
			AddMoneyToCharacter(PChar, -iSumm);
			
			dialog.text = "Замечательно. Все сделаем в лучшем виде.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
			
			DeleteAttribute(rRealShip, "EmblemedSails.normalTex")
			
			WaitDate("", 0, 0, 0, 1, 30);
		break;
		
		case "SailsTypeChoose":
			dialog.text = "Какой новый тип парусины ставим? У тебя сейчас паруса из материала '" + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) + "'.";

            Link.l1 = GetSailsType(1) + ".";
			Link.l1.go = "SailsTypeChooseIDX_1";
			Link.l2 = GetSailsType(2)  + ".";
			Link.l2.go = "SailsTypeChooseIDX_2";
			Link.l3 = GetSailsType(3)  + ".";
			Link.l3.go = "SailsTypeChooseIDX_3";
			
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
			
		    Link.l99 = "Я передумал"+ GetSexPhrase("","а") +".";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "У тебя сейчас паруса из материала '" + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) +
			              "', ты выбрал"+ GetSexPhrase("","а") +" тип ткани '"+ GetSailsType(sti(NPChar.SailsTypeChooseIDX))+
						  "'. Стоимость замены " + FindRussianMoneyString(sti(NPChar.SailsTypeMoney)) +". Меняем?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "Да.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "Нет.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "Замечательно! Все сделаем в лучшем виде.";
		    Link.l9 = "Спасибо.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "Какой цвет ставим? Цена " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = SailsColors[i].name;
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "Я передумал"+ GetSexPhrase("","а") +".";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Приходи, когда деньги будут.";
			    Link.l9 = "Хорошо.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "Договорились. Красим паруса в "+ GetStrSmallRegister(SailsColors[sti(NPChar.SailsColorIdx)].name) +" цвет.";
		    Link.l9 = "Спасибо.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "К сожалению, на твой корабль нельзя установить герб.";
				    Link.l9 = "Жаль.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Приходи, когда деньги будут.";
			    Link.l9 = "Хорошо.";
				Link.l9.go = "exit";	
			}
		break;
		
		// квест украсть чертеж на верфи
		case "ShipyardsMap_1":
			dialog.text = "Мне нужно раздобыть один важный чертеж. Очень важный чертеж...";
			link.l1 = "Хм. Что за чертеж и где его взять?";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			pchar.questTemp.different = "ShipyardsMap";
			pchar.questTemp.different.ShipyardsMap = "toTarget";
			pchar.questTemp.different.ShipyardsMap.Id = npchar.id; //квестодатель
			pchar.questTemp.different.ShipyardsMap.city = findShipyardCity(npchar);
			pchar.questTemp.different.ShipyardsMap.what = LinkRandPhrase("корвета", "флейта", "фрегата");
			pchar.questTemp.different.ShipyardsMap.chance = rand(5); //ценность чертежа
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = false; //не будет драки на складе
			}
			else
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = true; //будет драка на складе
			}
			pchar.questTemp.different.ShipyardsMap.sklad = rand(3)+1; //сколько денег попросят на складе за открытие двери
			pchar.questTemp.different.ShipyardsMap.fightQty = 2 + rand(3); //количество бойцов на верфи
			dialog.text = "Мне стало известно, что на верфи " + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + " ведется постройка новейшего " + pchar.questTemp.different.ShipyardsMap.what + ". Мне нужен чертеж, по которым ведутся работы.";
			link.l1 = "И что я долж"+ GetSexPhrase("ен","на") +" сделать?";
			link.l1.go = "ShipyardsMap_3";
		break;
		case "ShipyardsMap_3":
			dialog.text = "Привезти его мне. Проблема заключается в том, что чертеж, ввиду его ценности, постоянно находится на виду у хозяина верфи. А если быть точным - на его столе.";
			link.l1 = "И что вы предлагаете?";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Хм, я предлагаю доставить чертеж мне. Как вы это сделаете - ваши проблемы. За эту работу я готов щедро заплатить, хотя многое будет зависеть от действительной ценности заложенной в чертеже информации.";
			link.l1 = "Как это понять?";
			link.l1.go = "ShipyardsMap_5";
		break;
		case "ShipyardsMap_5":
			dialog.text = "Если проект имеет новые технологические решения, о которых мне неизвестно, то сумма будет достаточно велика. В обратном случае размер гонорара будет невысок... Ну что, вы согласны взяться за это дело?";
			link.l1 = "Нет, мне это неинтересно. Доставка 'кота в мешке' кажется мне неблагодарной работой.";
			link.l1.go = "ShipyardsMap_disagree";
			link.l2 = "Думаю, мне стоит этим заняться. Берусь!";
			link.l2.go = "ShipyardsMap_agree";
		break;

		case "ShipyardsMap_disagree":
			dialog.text = "Хм, ну что же, очень жаль.";
			link.l1 = "Мне тоже...";
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		case "ShipyardsMap_agree":
			dialog.text = "Ну что же, тогда удачи вам. Я буду ждать вас с результатами. В сроках вы никак не ограничены.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			sld = ItemsFromID("ShipyardsMap");
			sld.shown = true;
			sld.startLocation = pchar.questTemp.different.ShipyardsMap.city + "_Shipyard";
			sld.startLocator = "item1";
			sld.ShipName = pchar.questTemp.different.ShipyardsMap.what;
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "1");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Dat"));
			AddQuestUserData("ShipyardsMap", "sShip", pchar.questTemp.different.ShipyardsMap.what);
		break;

		case "Allarm":
			dialog.text = "Ах ты паршив"+ GetSexPhrase("ец","ка") +"! Ты что же это делаешь?! Ну, держись, проучу тебя как следует. А ну, ребята, хватайте топоры!";
			link.l1 = "Топоры?..";
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			AddCharacterExpToSkill(pchar, "FencingLight", 10);
			AddCharacterExpToSkill(pchar, "Fencing", 10);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 10);
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=sti(pchar.questTemp.different.ShipyardsMap.fightQty); i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "Allarm_1":
			dialog.text = "Ты что, угрожать мне вздумал"+ GetSexPhrase("","а") +"?! А ну, ребята, хватайте топоры!";
			link.l1 = "Топоры?..";
			link.l1.go = "fight";
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "ShipyardsMapOk_1":
			sTemp = pchar.questTemp.different.ShipyardsMap.what;
			dialog.text = "Отлично! Ну, давайте посмотрим, что же это за хваленый " + strcut(sTemp, 0, strlen(sTemp)-2) + "...";
			link.l1 = "Смотрите.";
			link.l1.go = "ShipyardsMapOk_2";
		break;
		
		case "ShipyardsMapOk_2":
			TakeItemFromCharacter(pchar, "ShipyardsMap");
			switch (sti(pchar.questTemp.different.ShipyardsMap.chance))
			{
				case 0:
				dialog.text = "Так-так... Хм, вынужден вас огорчить. Ничего полезного я для себя не вижу. Вы, кажется, вообще не то прихватили.";
				link.l1 = "Вы заказывали то, что лежало на столе. Именно это я вам и принес"+ GetSexPhrase("","ла") +". Я же не разбираюсь в этих чертежах!";
				link.l1.go = "ShipyardsMapOk_3";
				break;
				case 1:
					dialog.text = "Да, этот чертеж имеет определенную ценность. Я готов заплатить вам за него " + FindRussianMoneyString(1500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ". Оплату произведу серебряными слитками. Не возражаете?";
					link.l1 = "Нет, конечно! Прекрасно!";
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "jewelry17", makeint(1500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)/100));
				break;
				case 2:
					dialog.text = "Да, этот чертеж имеет определенную ценность. Я готов заплатить вам за него " + FindRussianMoneyString(3000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ". Оплату произведу золотыми слитками. Не возражаете?";
					link.l1 = "Нет, конечно! Прекрасно!";
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "jewelry5", makeint(3000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)/200));
				break;
				case 3:
					dialog.text = "Да, этот чертеж имеет определенную ценность. Я готов заплатить вам за него " + FindRussianMoneyString(4500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ".";
					link.l1 = "Прекрасно!";
					link.l1.go = "ShipyardsMapOk_5";
					AddMoneyToCharacter(pchar, 4500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L));
				break;
				case 4:
					dialog.text = "Да, этот чертеж имеет значительную ценность. Я готов заплатить вам за него " + FindRussianMoneyString(6000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ".";
					link.l1 = "Прекрасно!";
					link.l1.go = "ShipyardsMapOk_5";
					AddMoneyToCharacter(pchar, 6000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L));
				break;
				case 5:
					dialog.text = "О! Это очень, очень ценный чертеж! Я готов заплатить вам за него 60 000 золотом. Оплату произведу кредитными сундуками. Не возражаете?";
					link.l1 = "Нет, конечно! Прекрасно!";
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "chest", 4);
				break;
			}
		break;

		case "ShipyardsMapOk_3":
			dialog.text = "Увы, за это я вообще ничего не могу заплатить. Извините, но эта бумага мне не нужна.";
			link.l1 = "Хм, я не считаю ваш поступок честным, но дебошей устраивать не буду.";
			link.l1.go = "ShipyardsMapOk_4";
			link.l2 = "Отдавай мои деньги! Иначе пущу кровь!";
			link.l2.go = "Allarm_1";
		break;
		case "ShipyardsMapOk_4":
			dialog.text = "Поймите меня правильно, вы могли спокойно взять это где-нибудь на свалке. Этот чертеж ничего не стоит.";
			link.l1 = "Я вас понял"+ GetSexPhrase("","а") +"...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "3");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("ShipyardsMap");
		break;

		case "ShipyardsMapOk_5":
			dialog.text = "Извольте получить. Спасибо вам за проделанную работу.";
			link.l1 = "Да не за что...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			ChangeCharacterReputation(pchar, 5);
			AddQuestRecord("ShipyardsMap", "4");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("ShipyardsMap");
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		
        ////////////////////////////////////////////////homo линейка Блада/////////////////////////////////////////
        case "Blood_Shipyard1":
			dialog.text = "Кхм, ну, это зависит от того, кто ваш друг и зачем ему нужно в Порто Белло, доктор.";
			link.l1 = "Этот... мой друг, он... то есть, она - красивая барышня... хм, позабыл ее имя - оно такое незапоминающееся..";
			link.l1.go = "Blood_Shipyard2";
			link.l2 = "Мой дорогой друг - флибустьер, давеча потерявший свое судно при атаке на военный фрегат.";
			link.l2.go = "Blood_Shipyard3";
			link.l3 = "Вы о нем слышали. Он капер... называет себя Роландо Пицарро - гроза Семи Морей и прочая, прочая...";
			link.l3.go = "Blood_Shipyard4";
		break;
		
		case "Blood_Shipyard2":
			dialog.text = "Барышня? Ваш друг, который на самом деле барышня, с невыразительным именем, хочет попасть в Порто Белло? Вы меня разыгрываете, доктор?..";
			link.l1 = "И в мыслях не было, сэр! Я всего лишь, кхм, пытаюсь помочь. Ну, ему... ей, я имею в виду. Другу. Да.";
			link.l1.go = "Blood_Shipyard5";

		break;
		case "Blood_Shipyard3":
			dialog.text = "И где же это случилось?";
			link.l1 = "Это было... эхх, якорь мне в ...! Забудь.";
			link.l1.go = "exit";
			CloseQuestHeader("PirateQuest");
			Pchar.questTemp.CapBloodLine.ShipForJack = false;

		break;
        case "Blood_Shipyard4":
			dialog.text = "Вы хотите сказать, бывший капер... не так ли?";
			link.l1 = "Э-э-э... ну, да... бывший. Вы его знаете?";
			link.l1.go = "Blood_Shipyard6";
		break;
		
        case "Blood_Shipyard5":
			dialog.text = "Что ж, я вам поверю на этот раз. Где-то в городе находится человек по имени Джон Майнер. Поговорите с ним, он только что купил у меня корвет.";
			link.l1 = "Премного благодарен. ";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;
		
        case "Blood_Shipyard6":
			dialog.text = "Как вы правильно подметили, я о нем слышал. Не знаю, кем был Роландо Пицарро до того, как объявился в Береговом Братстве. Но я хорошо помню его судно 'Танцующий с Волками'. Красивое название, и красивое судно... было.";
			link.l1 = "Что?! Он ни словом об этом не обмолвился... ну, в нашей с ним беседе.";
			link.l1.go = "Blood_Shipyard7";
		break;
		
        case "Blood_Shipyard7":
			dialog.text = "Теперь он не распускает язык - жизнь его проучила. Захватив пару богатых призов, он начал рваться в верхушку Братства, пытаясь подсидеть самого Моргана. Ну, знаете - эта идея Шарповской Либертании и все прочее. Говорил он много и красиво, и, само собой, нашлись люди, которые поверили в эти бредни и пошли за ним... Кто ж знал, что все так обернется...";
			link.l1 = "Его предали?.. был бунт?";
			link.l1.go = "Blood_Shipyard8";
		break;
		
        case "Blood_Shipyard8":
			dialog.text = "Нет - всё случилось гораздо банальнее... Прямо как в жизни. Никакой Либертании Пицарро создавать не собирался - просто хотел сесть в красивое кресло в собственном особняке в Порт Рояле и смотреть, как трясутся и лебезят перед ним молодые каперы. Ну, знаете - это вечное желание карать и миловать на свое усмотрение, раздавать чины или свинцовый талер в сердце... Ну и, конечно - признание... этого мы все хотим, не так ли?\nТолько вот суть его была раскрыта. Морган вообще хотел повесить его тут же - слышали, наверное - он бунтовщиков на дух не переносит. Вот и Пицарро схватили тепленьким прямо в каюте, как только Морган получил все доказательства.";
			link.l1 = "Очень познавательная история. Надо будет предложить её какому-нибудь романисту. Но, что насчет корабля для этого, гм... правдолюбца?";
			link.l1.go = "Blood_Shipyard9";
			link.l2 = "А как Роландо удалось спастись?";
			link.l2.go = "Blood_Shipyard10";
		break;
		
        case "Blood_Shipyard9":
			dialog.text = "Найди в городе человека по имени Джон Майнер, он только что приобрёл корвет. Думаю, пассажир до Порто Белло будет ему не лишним.";
			link.l1 = "Премного благодарен. ";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;
		
        case "Blood_Shipyard10":
			dialog.text = "Обычно у Моргана суд короткий - не дольше, чем горит порох на полке его пистолета. Но, что-то с этим 'народным любимцем' он протянул... вот и сбежал Пицарро к испанцам. Прямо из-под носа у адмирала ускользнул, подтвердив, что Лис существо не только хитрое, но и вёрткое.";
			link.l1 = "Хм-м, а как же он провел адмирала Берегового Братства? Ну, вдруг пригодится на будущее.";
			link.l1.go = "Blood_Shipyard11";
		break;
		
        case "Blood_Shipyard11":
			dialog.text = "Вряд ли вам подойдет этот способ, но, если желаете - он просидел в тюрьме Порт Рояла три дня и три ночи, а потом кто-то из подельников умудрился передать ему женское платье. И некая леди Тэйлор преспокойно покинула форт, отчитавшись перед комендантом о том, что её возлюбленного Пицарро содержат вполне достойно.\nДалее эта леди села на корабль в порту... и лис сбежал из клетки. Сбежал, а потом объявился вновь. Да только вот цену ему в Братстве уже поняли, и даже Адмирал его больше не ищет... не хочет, видимо, руки марать.";
			link.l1 = "Итак, сдавать его властям, как я понимаю, смысла нет, поскольку его никто не ищет. Весьма поучительно. Но как мне спровадить его в Порто Белло?";
			link.l1.go = "Blood_Shipyard12";
		break;
		
        case "Blood_Shipyard12":
			dialog.text = "Вам нужен капитан Майнер, Джон Майнер - он занимается снаряжением только что приобретённого корвета. Поищите его в городе.";
			link.l1 = "Премного благодарен.";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "3");
		break;

	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	switch (_type)
	{
	    case 1 : return "Пенька";  break;
	    case 2 : return "Лён";     break;
	    case 3 : return "Хлопок";  break;
	}
	return "Пенька";
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

// Warship Ghdjthrf на паруса ЛГ
bool CheckForFlyingDuchmanSails(ref _char)
{
	ref realShip;
	int shipType = sti(_char.Ship.Type);
	
	if(shipType == SHIP_NOTUSED) return false;

	realShip = GetRealShip(shipType);

	if(CheckAttribute(realShip, "EmblemedSails.normalTex") && realShip.EmblemedSails.normalTex == "ships/parus_common_torn.tga")
	{
		return true;
	}

	return false;
}
