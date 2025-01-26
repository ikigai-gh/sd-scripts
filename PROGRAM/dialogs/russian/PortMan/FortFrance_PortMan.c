// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = "Я ищу Эдварда Лоу, он к вам не заходил?";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_noMoney")
			{
				link.l1 = "Я наш"+ GetSexPhrase("ел","ла") +" деньги!";
				link.l1.go = "PL_Q3_7";
			}
		break;
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("Эдвард Лоу? Заходил, в это время у меня один французский капер был, так он к нему, пассажиром, напросился.", 
				"Мы уже говорили на эту тему!", 
				"Прекратите немедленно повторять одно и то же.",
                "Хм, утомил"+ GetSexPhrase("","а") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("А вы знаете, куда этот капер направлялся?", 
				"Да, я помню.",
                "Хорошо...", 
				"Понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = "Знать-то знаю, но вы понимаете, - разглашать такие сведения я не имею права...";
			link.l1 = "Но мне очень нужно его найти! У меня к нему дело высокой важности!";
			link.l1.go = "PL_Q3_out";
			link.l2 = "Дело в том, что я дальн"+ GetSexPhrase("ий","яя") +" родственни"+ GetSexPhrase("к","ца") +" Эдварда Лоу, и спешу сообщить ему о болезни матери. Вы же, как порядочный человек, не допустите, чтобы из-за бюрократической буквы сын не сумел проститься с умирающей...";
			link.l2.go = "PL_Q3_3";
		break;

		case "PL_Q3_out":
			dialog.text = "Ищите...";
			link.l1 = "А-а-ать, дьявол!..";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "6");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.piratesLine = "KillLoy_notFound";
			QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
		break;
		case "PL_Q3_3":
			if (GetCharacterSkill(pchar, "Sneak") >= 60 || GetCharacterSPECIAL(pchar, "Charisma") > 6)
			{
				dialog.text = "Да, это большая трагедия, я вам помогу. Капер направлялся на Бермуды.";
				link.l1 = "Огромное вам спасибо! Вы даже не представляете, что для меня сделали! Спасибо.";
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "7");
				pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			}
			else
			{
				dialog.text = "Ну да, конечно. Мне тут все рассказывают сказки про бедных родственников, про умирающих матушек, а я должен всем верить! Нет уж, придумайте что-нибудь другое.";
				link.l1 = "Может быть, небольшое пожертвование в фонд реконструкции здания Портового Управления поможет нам обойти этот неприятный пункт в вашем уставе?";
				link.l1.go = "PL_Q3_4";
			}
		break;
		case "PL_Q3_4":
			dialog.text = "М-м-м... Ну что ж, раз уж вы настаиваете, то сумма в 15 тысяч могла бы компенсировать мои моральные издержки от нарушения правил...";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Какие проблемы?! Вот ваш гонорар.";
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				link.l1 = "Хм, у меня нет сейчас с собой такой суммы!";
				link.l1.go = "PL_Q3_6";
			}
		break;
		case "PL_Q3_5":
			dialog.text = "Тот капер отправился на Бермуды...";
			link.l1 = "Понял"+ GetSexPhrase("","а") +". Спасибо за искреннее участие в наших семейных проблемах. Прощайте.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "7_1");
			pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			AddMoneyToCharacter(pchar, -15000);
		break;
		case "PL_Q3_6":
			dialog.text = "Значит, вам придется ее раздобыть. Не волнуйтесь, я подожду...";
			link.l1 = "Гм, ну ладно. Я раздобуду деньги!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "8");
			pchar.questTemp.piratesLine = "KillLoy_noMoney";
		break;
		case "PL_Q3_7":
			if (sti(pchar.money) >= 15000)
			{
				dialog.text = "Очень хорошо!";
				link.l1 = "Вот ваши 15 тысяч. Говорит все, что знаете.";
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				dialog.text = "Гм, вы что, меня за идиота держите? Ступайте за деньгами!";
				link.l1 = "Дьявол!!";
				link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

