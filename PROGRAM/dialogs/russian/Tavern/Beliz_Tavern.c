// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = "Задавайте свои вопросы, "+ GetSexPhrase("сеньор","сеньорита") +".";
				link.l1 = "Я "+ GetSexPhrase("слышал","слышала") +", недавно вы сумели захватить Рока Бразильца, того самого пирата!";
				link.l1.go = "Step_F7_1";
			}	
		break;
//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("Да, верно, было дело. Неслыханная удача, скажу я вам, "+ GetSexPhrase("сеньор","сеньорита") +".", "Вы уже спрашивали меня о Бразильце.", 
				          "Опять о Бразильце?", "Ну сколько можно об этих пиратах, давайте о другом поговорим...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Что верно - то верно... И что с ним сделали? Небось удавили тут же.", ""+ GetSexPhrase("Спрашивал","Спрашивала") +"? Ну да, наверное...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +", извини...", "Можно и о другом...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = "Что вы, "+ GetSexPhrase("сеньор","сеньорита") +". Привезли и показали всем желающим. А потом уже отдали святым отцам...";
			link.l1 = "А святым отцам-то он зачем?";
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = "Хех, "+ GetSexPhrase("сеньор","сеньорита") +", это же не исповедники. Те святые отцы - воинствующие монахи! Инквизиция...";
			link.l1 = "У-у-у, дело ясное. Ну что же, спасибо тебе, друг.";
			link.l1.go = "exit";
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

