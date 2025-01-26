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
				dialog.text = "Новые лица! Это радует, а то кроме этих ужасных штормов и развлечений-то никаких нет. Меня зовут " + GetFullName(npchar) + ", и я счастлив первым приветствовать вас в Городе!";
				link.l1 = "Спасибо за теплый прием, хотя мое прибытие оказалось несколько подмоченным!.. Меня зовут капитан " + GetFullName(pchar) + ".";
				link.l1.go = "FT_1";
			}
			else
			{
				dialog.text = "Что вы хотели, "+ GetSexPhrase("месье","мадемуазель") +"?";
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
		case "FT_1":
			dialog.text = "Капитан, похоже, что вы единственн"+ GetSexPhrase("ый","ая") +" выживш"+ GetSexPhrase("ий","ая") +" в этом шторме. Мне очень жаль...";
			link.l1 = "Мне тоже... Что это за место, дружище?";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "Это Город Потерянных Кораблей.";
			link.l1 = "А не Остров Справедливости?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Хм, нет... Хотя, вы знаете, говорят, что бытовало одно время такое название. Но те времена я уже не застал.";
			link.l1 = "Понятно...";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Ну что же, считаю своим долгом, так сказать, просветить вас относительно нашего Города.";
			link.l1 = "С удовольствием и благодарностью выслушаю все, что вы скажете.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Первое, что вам нужно сделать по прибытии сюда - это получить гражданство Города. Для этого вам нужно явиться к адмиралу Города, Чаду Капперу.";
			link.l1 = "Чаду Капперу?.. Это имя мне кажется знакомым...";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Вспоминать будете потом, сначала дослушайте... Так вот, Чад Каппер - глава Города. Должность эта выборная, так что он пришел к власти, так сказать, демократическим путем. В его обязанности входит следить за исполнением Закона...";
			link.l1 = "...собирать налоги...";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Какие налоги? Здесь нет налогов, никто ничего ему не платит, за исключением первичного взноса...";
			link.l1 = "Нет налогов?!! Вот это да! А ведь и вправду - Остров Справедливости...";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "Ну, может и так... Продолжу. К адмиралу на регистрацию нужно явиться как можно быстрей. Сейчас шторм, поэтому народу на палубах маловато. Но как только он закончится - Каппер сам вас найдет в любом случае. И я советую не тянуть с регистрацией.";
			link.l1 = "Хорошо, это я понял"+ GetSexPhrase("","а") +". И когда, по вашему мнению, закончится этот шторм?";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Завтра к вечеру точно все успокоится. Шторм уже пошел на убыль.";
			link.l1 = "Ясно. Что еще мне нужно знать?";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "Адмирал расскажет вам о Законе, по которому мы все живем, более подробно, но я могу в двух словах описать его постулаты.";
			link.l1 = "Очень интересно!";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "Значит, запрещено убивать граждан, воровать у них, разбирать корабли для постройки чего-либо, чтобы уплыть отсюда...";
			link.l1 = "Стоп! Это значит, что я не смогу отсюда свалить?!";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "Конечно, нет! Это запрещено Законом!.. Вы знаете, я бы не хотел углубляться в эти темы, это не мое дело. Идите к адмиралу, он вам все расскажет.";
			link.l1 = "И где он находится?";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "На варшипе 'Сан Августин'. Отсюда это довольно далеко, к варшипу ведет мост... Извините, но точней объяснить я не могу, так как вы не знаете ориентиров. Ищите 'Сан Августин'!";
			link.l1 = "Понятно... Послушайте, вы не знали человека по имени Тизер Дэн?";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "Нет, это имя мне незнакомо.";
			link.l1 = "Ага, ясно... Ну что же, спасибо вам за информацию.";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "Не за что. Я всегда к вашим услугам, "+ GetSexPhrase("сэр","мисс") +"... Погодите, я чуть не забыл жизненно важную информацию!";
			link.l1 = "Очень приятно это слышать.";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = "Ни за что не заходите внутрь барка 'Сан-Габриль' и галеона 'Веласко'! Галеон 'Веласко' - это корабль, на котором мы сейчас стоим...";
			link.l1 = "А почему?";
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = "Вас убьют. Эти корабли принадлежат кланам 'Нарвал' и 'Каспер'. По ним можно ходить, но спускаться вниз нельзя!";
			link.l1 = "Хм, ну что же, понятно. Буду иметь в виду. Спасибо еще раз за теплый прием.";
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			AddQuestRecord("ISS_MainLine", "1");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "ла"));
			LAi_SetLSCoutTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
			dialog.text = LinkRandPhrase("Да ты вор"+ GetSexPhrase("","овка") +"!!! Нарушение Закона Города!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!", "Милиция! Грабят!!! Держи "+ GetSexPhrase("его","ее") +", он"+ GetSexPhrase("","а") +" нарушил"+ GetSexPhrase("","а") +" Закон!");
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
				dialog.text = NPCharSexPhrase(NPChar, "Осторожнее на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием наизготовку. Это меня пугает...");
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
				Link.l2 = "Спасибо, я лучше сам"+ GetSexPhrase("","а") +" поищу.";
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
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "Этот город... откуда он взялся?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "Вы сами давно здесь живете?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "Много людей погибает здесь?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4") && CheckCharacterItem(pchar, "keyQuestLSC"))
			{
				link.l4 = "Послушайте, вы не знаете, что такое Диффиндур?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "Что у вас в Городе имеется интересного? Кроме резиденции Чада Каппера, разумеется...";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6"))
			{
				link.l6 = "Как бы мне здесь сориентироваться?..";
				link.l6.go = "ansewer_6";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "Кто-то говорит, что это естественное образование, странным образом притягивающее корабли, а кто-то уверен, что это место проклято и будет только расти за счет новых и новых крушений... Трудно сказать, трудно выделить истину из общей массы сплетен и фантазий.";
			link.l1 = "Ну, а вы как считаете?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "Важно ли мое мнение? Конечно, не больше и не меньше, чем мнения других.";
			link.l1 = "И все же?..";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "Оглянитесь вокруг, прислушайтесь... Вы можете слышать их голоса, стоны и крики тысяч погибших моряков эхом отдаются в вас, в каждом из нас. Проходя по палубе, вы можете уловить едва заметные звуки, но при должном внимании к ним понимаешь, что это ни что иное, как отголоски тех дней, когда корабль бороздил морские просторы.";
			link.l1 = "Что это значит?";
			link.l1.go = "ansewer_1_3";
		break;
		case "ansewer_1_3":
			dialog.text = "Город сдерживает не только нас, капитан. Он пленит души и время, он может обмануть вечность.";
			link.l1 = "А я по глупости своей думал"+ GetSexPhrase("","а") +", что это Чад Каппер сдерживает нас...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "Нет, около трех месяцев. Был ночной бой с пиратами, которые захватили огромный военный корабль. Наш капитан был из разряда отчаянных безумцев, а потому и вступил в заведомо проигрышное сражение на бриге. Разумеется, первым же бортовым залпом линкор смёл все живое и не очень с нашей палубы, включая капитана и половину офицеров.\n"+
				"Ничего подобного мне переживать еще не приходилось, я бросился на палубу и едва смог пробраться туда сквозь обломки рангоута и клочья снастей... Это зрелище ни с чем не сравнимо, капитан. Хотя, вы, наверное, знаете, что уж я\n"+
				"В общем, не желая дожидаться следующего залпа, который, несомненно, угробил бы меня, оставшихся матросов и вообще весь корабль, я бросился за борт и, доплыв до ближайшего обломка достаточной величины, уцепился за него. Потом, наверное, потерял сознание – не помню, но... уже к утру я был здесь.";
			link.l1 = "Захватывающе...";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "Еще бы! Так дух захватило, что я чуть в штаны не наложил... Но все уже позади, а мне тут и вовсе нравится. Спокойно, тихо, интересно.";
			link.l1 = "Я смотрю, вы не один такой.";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "Конечно. Зачем сопротивляться? Сперва - да, все кажется враждебным, хочется убраться подальше от этого чертового места, но... потом все образуется, поверьте мне. Вы привыкнете, как и все мы.";
			link.l1 = "Не уверен"+ GetSexPhrase("","а") +", что мне нравится эта идея с привыканием.";
			link.l1.go = "ansewer_2_3";
		break;
		case "ansewer_2_3":
			dialog.text = "А я не уверен, что вас кто-то спросит. Не я первый, не я последний скажу вам, что лучше сразу позабыть все то, что было с вами раньше. Начинайте новую жизнь! Вот увидите, здесь очень даже ничего.";
			link.l1 = "Благодарю за совет, мистер " + npchar.lastname + ".";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "Более чем. Но еще больше прибывает в последнее время.";
			link.l1 = "В последнее время? Почему?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "Не знаю точно, но, похоже, о Городе стало известно в большом мире.";
			link.l1 = "Хм, я слышал"+ GetSexPhrase("","а") +" не один раз слухи о каком-то Острове Справедливости. Наверное, о Городе речь и шла...";
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = "Может быть. Однако, если это так, то каким образом слухи достигли городов Большой земли?";
			link.l1 = "Хе, не знаю. Но очень хочу узнать...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "Диффиндур? Хм... Может быть, это один из здешних кораблей, флейт 'Фернандо Диффиндур'?";
			link.l1 = "Что за флейт?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "Полузатонувший корабль, он треснул пополам и держится каким-то чудом на рифе. Там никто не живет - слишком опасно.";
			link.l1 = "А где он находится?";
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = "Точно на другой стороне Города. А вообще, поговорил"+ GetSexPhrase("","а") +" бы ты на эту тему с хозяином таверны, он здесь знает все.";
			link.l1 = "У вас и таверна есть?";
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = "И таверна, и церковь, и магазин - все как у людей в обычном городе! Есть еще ростовщик по имени Августо Брамс, но с ним стоит вести себя поосторожней...";
			link.l1 = "Хо, уже лучше!";
			link.l1.go = "int_quests";
			//AddQuestRecord("ISS_MainLine", "2");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
		break;
		case "ansewer_5":
			dialog.text = "Здесь есть все, что есть в обычном городе - церковь, таверна, магазин. Есть человек, ссужающий деньги. Но я скажу я вам - наиглупейшее это занятие здесь.";
			link.l1 = "Почему?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "В Городе столько золота, что никакой практической ценности оно не имеет. Люди собирают его скорее по привычке, нежели в надежде его использовать.";
			link.l1 = "Я не пойму, деньги здесь никому не нужны?";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "Да нет же, почему? Деньги - и здесь деньги. Но только они не так нужны, как на Большой земле... В общем, сами потом поймете.";
			link.l1 = "Хм, пока не понимаю, но надеюсь, что дойдет...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = "Сначала будет сложно, но вы быстро разберетесь, что к чему.";
			link.l1 = "М-да, обнадеживающее заявление... Ну, а карта Города имеется?";
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = "Имеется, я даже видел одну такую.";
			link.l1 = "Вот! И где вы ее видели?";
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = "В магазине у Эрика Йоста, что на галеоне 'Эсмеральда'.";
			link.l1 = "Понял"+ GetSexPhrase("","а") +", спасибо.";
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("Что именно, позвольте вас спросить?", 
				"Вы уже спрашивали об этом.", 
				"Уже спрашивали...",
                "Вы уже спрашивали меня об этих товарах. Ничего я не знаю!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Бомбы, картечь, провиант, лекарства, порох, оружие...", 
				"Да... Извините, запамятовал"+ GetSexPhrase("","а") +".",
                "А-а, ну да.", 
				"Понял"+ GetSexPhrase("","а") +", понял"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "Понятно. Непонятно, зачем это вам. Ну да ладно\nКартечь с бомбами лучше просить у хозяек кораблей, у них этого добра навалом. А вот оружие и порох - у адмирала.";
			link.l1 = "И он даст?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "Не знаю. У него и спрашивайте.";
			link.l1 = "Ясно. Спасибо вам огромное.";
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = "Команду на корабль?";
			link.l1 ="Да.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "И что, он у вас есть в наличии?";
			link.l1 = "Имеется.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "Вот так новости... Я согласен!";
			link.l1 = "Отлично! Тогда немедленно отправляйтесь на 'Сан Габриэль'. Хенрик Ведекер переправит вас на мой корвет.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "Хорошо, я так и сделаю. Вещи только быстренько соберу - и могу отчаливать.";
			link.l1 = "Не задерживайтесь.";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
