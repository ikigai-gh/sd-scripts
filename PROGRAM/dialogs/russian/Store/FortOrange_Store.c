// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Некоторое время тому назад, находясь у меня в магазине, вы пытались задать какой-то вопрос...", "За сегодня третий вопрос. Мне торговать надо, а не пустые разговоры вести...",
                          "Опять вопросы? Может лучше торговлей займемся?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Да, точно, пытал"+ GetSexPhrase("ся","ась") +"... Находясь в магазине...",
                      "Да уж, действительно в третий раз...", "Хм, может и поторгуем...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "TakeFoodCuracao_toOrangeStore": //Голландская линейка, квест №2, доставка продовольствия из форта Оранж.
                    link.l2 = "У меня распоряжение коменданта форта для вас.";
                    link.l2.go = "Step_H2_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;

        case "Step_H2_1":
			dialog.text = NPCStringReactionRepeat("Верно, данное распоряжение мной получено. Давайте рассчитаемся по тем ценам, о которых у нас была речь, "+ GetSexPhrase("минхер","госпожа") +".",
                         "Опять вы, очень хорошо. Давайте продолжим нашу особенную сделку.",
                         "Снова наш"+ GetSexPhrase("","а") +" брав"+ GetSexPhrase("ый капитан","ая девушка") +"! Прекрасно. Давайте продожим...",
                         "Капитан, рад вас видеть по тому же поводу. Ну, давайте продолжим торговлю по этой специальной партии товара.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Давайте приступим к торговле.", "Давайте продолжим...",
                      "Давайте...", "Эх, не надо иронизировать, прошу вас. "+ GetSexPhrase("Самому","Самой") +" надоело уже все это до смерти..." , npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
         case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
            dialog.text = "Кхе-кхе, рад вас видеть в добром здравии, капитан. Да еще после такой бойни!";
            link.l2 = "Хм, да уж, заварушка была что надо...";
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = "Я имел с вами дела, капитан, и теперь вижу, что вы не только торговать горазды. А эти англичане долго теперь к нам не сунутся... Спасибо, "+ GetSexPhrase("минхер","госпожа") +", от всей души спасибо.";
			link.l1 = "Да не за что, торгуй дальше.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);
}

