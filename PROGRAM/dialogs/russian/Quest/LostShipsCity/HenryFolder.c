#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";			
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text =  TimeGreeting() + ", капитан " + pchar.lastname + ". Поздравляю с прибытием в Город! Шторм скоро уляжется, тогда вы сможете здесь освоиться получше.";
					link.l1 = "А почему вы думаете, что он скоро уляжется?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = TimeGreeting() + ", капитан " + pchar.lastname + ".";
					link.l1 = "Мы знакомы?";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "Чем я могу вам помочь, "+ GetSexPhrase("сэр","мисс") +"?";
				link.l1 = "Послушайте, я ищу одного человека. Не знаете, где он сейчас?";
				link.l1.go = "SeekCitizen";
				link.l2 = "Хочу задать вам вопрос.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", 
					"Что нового в Городе?", "Эх, с удовольствием послушал"+ GetSexPhrase("","а") +" бы последние сплетни...");
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "Послушайте, я ищу некоторые товары.";
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "Знаете, я набираю команду, чтобы уйти отсюда. Предлагаю вам идти со мной.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "Ничего...";
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = "Хм, ну это не первый мой шторм здесь, в Городе. Поэтому могу сказать более или менее точно, что шторм уляжется завтра к вечеру. " + GetFullName(npchar) + " к вашим услугам!";
			link.l1 = "Спасибо. Расскажите, дружище, если это не тайна, как вы сюда попали.";
			link.l1.go = "FT_5";
		break;
		case "FT_1":
			dialog.text = "Нет, что вы. Просто мне уже довелось слышать о вас.";
			link.l1 = "А вот мне о вас, увы, слышать не довелось.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Ничего удивительного! " + GetFullName(npchar) + " к вашим услугам. Чем могу помочь?";
			link.l1 = "Да вот, знакомлюсь с людьми, адаптируюсь... о Городе узнаю.";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "О городе, хм... И как вам Город?";
			link.l1 = "Ну, город довольно интересный.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Не то слово, капитан! Этот город уникален.";
			link.l1 = "А вы как сюда попали?";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Моя история, пожалуй, самая наискучнейшая из всех. Может быть, это потому что мне лень приукрашивать ее. К тому же, мне никто не верит.";
			link.l1 = "Так что случилось?";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Я буквально сам отправился сюда, капитан. Только и всего.";
			link.l1 = "Сам? Вы намеренно отправились сюда?! Тогда мы с вами коллеги! И что вас привело сюда?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Слух прошел, капитан. Я первым сообразил, что это не просто пьяная байка, и решил отправиться сюда. Я нанял капитана с командой, собрал все сведения, обзавелся сомнительной картой... но все получилось куда проще.\n"+
				"Ночью безо всяких на то причин, без штормов и бурь, ветер разогнал нас до двадцати узлов, если я правильно помню слова капитана – сам я не мореплаватель вовсе. Мы некоторое время радовались, а после на полном ходу врезались в этот город...";
			link.l1 = "Врезались?!";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Да, именно так – наш корабль тут неподалеку, он стал частью этого города. Кроме того, выжило достаточно много народу, что очень редко бывает. Вы не представляете, как на нас смотрел Каппер – клянусь богом, эта встряска даже его заставила подпрыгнуть и напрудить в панталоны!";
			link.l1 = "Я бы не сказал"+ GetSexPhrase("","а") +", что эта история скучна.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Кому как, но я бы предпочел бурю, а не глупое крушение.";
			link.l1 = "Что ж, я рад"+ GetSexPhrase("","а") +" был"+ GetSexPhrase("","а") +" познакомиться. Спасибо за историю.";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "Не за что, капитан. Будем знакомы.";
			link.l1 = "Всего хорошего.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи е"+ GetSexPhrase("го","е") +", он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумали?! Теперь граждане и милиция порвут тебя, как старую тряпку!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал"+ GetSexPhrase("","а") +" оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как три мушкетера, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это "+ GetSexPhrase("серьезному мужчине","девушке") +"...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","тут всякие") +" ходят передо мной с оружием наизготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		//ищем человека
		case "SeekCitizen":
			dialog.text = "А кого вы ищете?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "Я не понимаю, о ком вы говорите. Мне нужно знать имя и фамилию этого человека.";
				Link.l1 = "Понятно. Давайте я еще попробую назвать.";
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = "Спасибо, я лучше сам поищу.";
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "Так это же я!";
					link.l1 = "Надо же, точно на вас выш"+ GetSexPhrase("ел","ла") +"!";
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", вы о нем говорите?";
					Link.l1 = "Да-да, точно, это он.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "Нет, не о нем. Давайте еще раз назову.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", вы о ней говорите?";
					Link.l1 = "Ага, именно о ней.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "Нет, не о ней. Послушайте, давайте я еще раз попробую назвать.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "Знаете, не хочу я больше ни о ком спрашивать. До свидания.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "Тогда назовите еще раз имя и фамилию.";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = LinkRandPhrase("Не знаю, давно его не видел.", "Черт его знает, где он...", "Не видел его уже прилично, так что не ведаю.");
					link.l1 = RandPhraseSimple("Понятно.", "Жаль...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Не видел ее уже довольно давно, сожалею.", "Понятия не имею, где она сейчас.", "Хм, я не знаю, где она может сейчас быть.");
					link.l1 = RandPhraseSimple("Ясно.", "Жаль...");
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")  
					{						
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = LinkRandPhrase("Он здесь, на этом корабле. Ищите внимательней.", "Ха, так он здесь, на этом корабле!", "Он на этом корабле, странно, что вы еще не увидели его.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищите его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Так он здесь, " + npchar.quest.seekIdx.where + ". Смотрите внимательней.", "Так ведь он здесь, среди нас!", "Куда вы смотрите? Он же здесь ошивается.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел его совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил его " + npchar.quest.seekIdx.where + ". Так что ищите его там.", "Насколько я знаю, сейчас он находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам.", "Спасибо вам!");
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")  
					{						
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = LinkRandPhrase("Она здесь, на этом корабле. Ищите внимательней.", "Ха, так она здесь, на этом корабле!", "Она на этом корабле, странно, что вы еще не увидели ее.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил ее " + npchar.quest.seekIdx.where + ". Мы даже поговорили.", "Насколько я знаю, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("Так она здесь, " + npchar.quest.seekIdx.where + ". Смотрите внимательней.", "Так ведь она здесь, среди нас!", "Куда вы смотрите? Она же где-то здесь ходит.");
						}
						else
						{
							dialog.text = LinkRandPhrase("Я видел ее совсем недавно " + npchar.quest.seekIdx.where + ".", "Недавно встретил ее " + npchar.quest.seekIdx.where + ". Мы даже поговорили с ней.", "Насколько я знаю, сейчас она находится " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("Ага, понятно. Спасибо вам, "+GetAddress_FormToNPC(NPChar)+".", "Спасибо вам!");
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = "Внимательно вас слушаю, "+ GetSexPhrase("дружище","мисс") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "Как вообще здесь с погодой?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Почему это место не интересует представителей власти национальных держав? Оно никому не принадлежит?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Не подскажете, куда бы схоронить добро на время?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Все знают Закон и беспрекословно ему следуют?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = "Слушай, давно ты сюда попал?";
				link.l5.go = "ansewer_5";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = "Да нормально. Штормы - явление довольно редкое, в основном здесь солнечно и безветренно.";
			link.l1 = "Это радует.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = "Смешно, ха, действительно... никому.";
			link.l1 = "И никто не пытался городом завладеть?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Конечно, нет. Никто о нем ничего не знает на Большой земле. Слухи разве что ходят у нищих об Острове Справедливости... Но кто это серьезно воспримет?";
			link.l1 = "Это точно.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Сундуки, "+ GetSexPhrase("друг","мисс") +", сундуки... их тут хватает. Но в чужие соваться не стоит – только общие открывай, если сможешь, конечно.";
			link.l1 = "Как понять?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Здесь нет сундуков без ключей, "+ GetSexPhrase("приятель","" + pchar.name + "") +". Все открывается только ключами. И учти, что кроме тебя еще куча народу, у кого такие ключи имеются. Если хочешь что-нибудь надежно спрятать, то нужно искать сундук где-нибудь за Городом, куда плыть нужно...";
			link.l1 = "Ага, понятно...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Ха, да неважно, знают они его или нет!.. Нарушения жестоко караются, и Каппера не интересует, усвоили ли вы наш Закон с первого раза.";
			link.l1 = "Да, я так и подозревал"+ GetSexPhrase("","а") +".";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = "Прилично уже, так сказать...";
			link.l1 = "Это сколько?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "Около пяти лет.";
			link.l1 = "Ха, да ты старожил! Наверное, еще раньше покойного Хилла Брюннера стал гражданином Города.";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "Нет, не раньше.";
			link.l1 = "Понятно... Слушай, а ты не знаешь еще кого-нибудь из старых жителей города?";
			link.l1.go = "ansewer_5_3";
		break;
		case "ansewer_5_3":
			dialog.text = "А зачем тебе?";
			link.l1 = "Да так, надо по одному небольшому делу...";
			link.l1.go = "ansewer_5_4";
		break;
		case "ansewer_5_4":
			dialog.text = "Ну, не хочешь говорить - не надо. А на свой вопрос ты сам"+ GetSexPhrase("","а") +" и ответил"+ GetSexPhrase("","а") +". Ищи старых жителей...";
			link.l1 = "Как понять?";
			link.l1.go = "ansewer_5_5";
		break;
		case "ansewer_5_5":
			dialog.text = "Как хочешь, так и понимай.";
			link.l1 = "М-да... Ну ладно, спасибо и на этом.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Простите, я не пойму, о чем речь.", 
				"Вы уже спрашивали об этом.", 
				"Уже спрашивали...",
                "Вы уже спрашивали меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Мне нужны бомбы, картечь, провиант, лекарства, порох, оружие...", 
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.", 
				"Понял, понял...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "А-а, понятно... Ничем не могу вам помочь. Хотя...";
			link.l1 = "Что?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Бомбы и картечь можно поискать у хозяек домов. Это далеко не самые ценные предметы в Городе.";
			link.l1 = "Ясно, спасибо.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("Идти с вами? Вот так предложение!", 
				"Мы уже говорили об этом.", 
				"Это уже обсуждено, второй раз повторяю.",
                "Хватит, утомил"+ GetSexPhrase("","а") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Я жду ответа.", 
				"Да... Извини, запамятовал"+ GetSexPhrase("","а") +".",
                "Как знаешь...", 
				"Ну, ладно...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;		
		case "SeekCrew_1":
			dialog.text = "Пожалуй, откажусь. Мне здесь нравится!";
			link.l1 = "Не надоело еще?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Нет, не надоело. Здесь есть все, что нужно для жизни. И приобретается все это без усилий.";
			link.l1 = "Может, вас образумит надвигающийся шторм? Дело в том, что он разрушит Город.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "А откуда вы знаете?";
			link.l1 = "Знаю наверняка, вы уже поверьте мне.";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "Извините, не верю...";
			link.l1 = "Ну, как знаете.";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
