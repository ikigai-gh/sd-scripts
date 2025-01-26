// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "У вас в городе не появлялся такой Франсуа Гонтьер? Мне он очень нужен.";
                link.l1.go = "Jamaica_ratF_1";
            }
		break;

        case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
            dialog.text = "Да, скажу я вам, такой лихой бойни я не видел на своем веку...";
            link.l2 = "Ловко почикали английских псов, а?";
            link.l2.go = "Step_H4_1";
        break;
        
        case "Step_H4_1":
			dialog.text = "Да чего уж тут скажешь, "+ GetSexPhrase("минхер","госпожа") +". Ловчее не бывает. Огромное вам спасибо!";
			link.l1 = "Да не за что.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Jamaica_ratF_1":
			dialog.text = "Появлялся. Снимал у меня комнату несколько дней. Пренеприятнейший тип, я вам скажу. И кроме того, с манией преследования - вечно озирался и всего опасался, как параноик. Не тебя ли он так боялся?";
			link.l1 = "Нет, не меня. А вообще у каперов врагов много, сам знаешь. Так где его найти? Мы с ним договорились вместе на дело пойти, а он как сквозь землю провалился!";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "Ушел в море на своем корабле. А куда - не знаю. Он мне не докладывал.";
			link.l1 = "Эх, жаль! Где ж я теперь его искать буду?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "Не знаю, "+ GetSexPhrase("дружище","мэм") +". Знал - подсказал бы.";
			link.l1 = "Ладно, все понятно. Пойду, у кого еще поспрашиваю...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
