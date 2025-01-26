// диалоговый файл №1 на голландку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

    switch (Dialog.CurrentNode)
    {
        case "First time":
            dialog.text = NPCStringReactionRepeat("Что тебе, "+ GetSexPhrase("сын мой","дочь моя") +"?",
                         "Опять ты? Что-то забыл сказать?", ""+ GetSexPhrase("сын мой","дочь моя") +", что тебя гложет, почему ты в который раз за сегодня приходишь ко мне и ничего не говоришь?",
                         "Послушай, " + GetFullName(pchar) + ", если тебе нечего сказать, то и не надо сюда ходить.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да ничего особенного, падре...",
                                               "Да нет, просто так...",
                                               "Сказать нечего, падре...",
                                               "Хорошо, падре...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
//>>>>>>>>>>>>========= Разброс диалогов =====================
			if (pchar.questTemp.State == "Inquisition_toDeSouza")//Квест №2, базар с гл.Инквизитором
			{
                dialog.text = "Добро пожаловать в лоно церкви, "+ GetSexPhrase("сын мой","дочь моя") +".";
    			link.l1 = "Падре, я к вам по приказу сеньора генерал-губернатора...";
    			link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Inquisition_toCuracao")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = "Рад видеть тебя, " + GetFullName(pchar) + ". Ты готов"+ GetSexPhrase("","а") +" отчитаться по заданию?";
        			link.l1 = "Падре, я навестил"+ GetSexPhrase("","а") +" всех, указанных вами людей.";
        			link.l1.go = "Step_S2_12";
        			link.l2 = "Пожалуй, нет еще, монсеньор. Я еще поработаю над этим...";
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = "Ты получил"+ GetSexPhrase("","а") +" задание, "+ GetSexPhrase("сын мой","дочь моя") +". Приступай к выполнению.";
        			link.l1 = "Хорошо, монсеньор...";
        			link.l1.go = "exit";
                }
            }
			if (pchar.questTemp.State == "Inquisition_afterFrancisco")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = "Рад видеть тебя, " + GetFullName(pchar) + ". Ты готов"+ GetSexPhrase("","а") +" отчитаться по заднию?";
        			link.l1 = "Монсеньор, я навестил"+ GetSexPhrase("","а") +" всех указанных вами людей.";
        			link.l1.go = "Step_S2_12";
        			link.l2 = "Пожалуй, нет еще, монсеньор. Я еще поработаю над этим...";
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = "Что случилось, "+ GetSexPhrase("сын мой","дочь моя") +"? Ты нуждаешься в искуплении грехов?";
        			link.l1 = "Нет, монсеньор. Я вернул"+ GetSexPhrase("ся","ась") +" не за этим. Сейчас ко мне подошел некий Франциско де Сан-Агостиньо и соловьиными трелями начал заливать про мораль вашего задания. Он знает, куда я еду, зачем еду. Вы не находите это странным?";
        			link.l1.go = "Step_S2_11";
                }
            }
			if (pchar.questTemp.State == "Inquisition_backAllGood" || pchar.questTemp.State == "Inquisition_backPartGood" || pchar.questTemp.State == "Inquisition_backBad")
			{
                dialog.text = ""+ GetSexPhrase("сын мой","дочь моя") +", ты можешь возвращаться в Гавану. Мне ты больше не нуж"+ GetSexPhrase("ен","на") +"...";
    			link.l1 = "Хорошо, монсеньор.";
    			link.l1.go = "exit";
            }
			if (pchar.questTemp.State == "TakeRockBras_RockTaken")
			{
                dialog.text = "Слушаю тебя, "+ GetSexPhrase("сын мой","дочь моя") +". Зачем пожаловал"+ GetSexPhrase("","а") +"?";
    			link.l1 = "Монсеньор, согласно полученному распоряжению генерал-губернатора Гаваны дона Франсиско Орегон-и-Гаскона, я передаю Святой Инквизиции известного ладрона Рока Бразильца, схваченного мной в жаркой битве у Маракайбо.";
    			link.l1.go = "Step_S3_1";
            }

        break;

//<<<<<<<<<<<<===== Разброс диалогов  =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Задания Инквизиции. Квест №2 **********************************
 		case "Step_S2_1":
			dialog.text = "Я знаю, "+ GetSexPhrase("сын мой","дочь моя") +", знаю. Я ждал тебя. Итак, о твоей миссии.\n"+
                          "Есть несколько людей, живущих в темноте, и мы пока не в силах помочь им прозреть. Это флорентийские негоцианты Джоао Ильхайо, Йозеф Нунен де Фонкесао, и Яков Лопез де Фонсека. Нам удалось выяснить, что они попали под влияние еретического учения Янсения.\n"+
                          "Души приверженцев секты янсенистов мы освобождаем от нечестивых уз путем сожжения их тел на костре. Но они не ценят этого, не ценят спасения своей души, которые мы им даем...";
			link.l1 = "Простите, монсеньор, у меня есть вопрос. Если вы, конечно, разрешите его задать.";
			link.l1.go = "Step_S2_2";
		break;
 		case "Step_S2_2":
			dialog.text = "Спрашивай, "+ GetSexPhrase("сын мой","дочь моя") +".";
			link.l1 = "Я слышал"+ GetSexPhrase("","а") +", что янсенисты веруют во Христа точно так же, как и католики. Зачем же их сжигать, если они такие же христиане?";
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = "Янсений извратил догмы Церкви, мы имеем разногласия в вопросе примирения существования свободной человеческой воли и необходимости божественной благодати, без участия которой невозможно спасение человека.";
			link.l1 = "А прийти к согласию, то есть разрешить разногласия путем переговоров, никак не удается?";
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = "Это невозможно, "+ GetSexPhrase("сын мой","дочь моя") +". Враги Церкви только и ждут того, чтобы увести заблудшие души от Пастыря своего. Никому не позволено трактовать постулаты христианской веры произвольно, а тем более подвергать их сомнению. Никому!\n"+
                          "К тому же, янсенисты запятнали себя преступлением, которому никогда не будет прощения. Около двадцати лет назад, один из первых последователей этой секты Самуэль Кохэно выкрал древние церковные документы из наших архивов в Севилье!";
			link.l1 = "Вот это да! Всегда полагал"+ GetSexPhrase("","а") +", что Святая Инквизиция безупречна. Как же такое могло случиться?";
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			dialog.text = "С помощью врага рода человеческого, "+ GetSexPhrase("сын мой","дочь моя") +"! Мы противостоим его козням каждую минуту, но порой он одерживает верх над кем-то из наших братьев. Так случилось и в этот раз, наш севильский архивариус пал жертвой смертного греха - алчности...";
			link.l1 = "Он во всем сознался?";
			link.l1.go = "Step_S2_6";
		break;
 		case "Step_S2_6":
			dialog.text = "Сознался, раскаялся и очистил свою душу, как же иначе? Мы рады, что сумели помочь ему. Уверен, что Господь принял его душу...";
			link.l1 = "Аминь... Так в чем же будет заключаться мое задание?";
			link.l1.go = "Step_S2_7";
		break;
 		case "Step_S2_7":
			dialog.text = "Вам нужно навестить бежавших негоциантов с определенной целью.";
			link.l1 = "А вам известно, где они сейчас находятся?";
			link.l1.go = "Step_S2_8";
		break;
 		case "Step_S2_8":
			dialog.text = "Конечно, "+ GetSexPhrase("сын мой","дочь моя") +". Сначала они бежали в Нидерланды, но там не прижились - ересь кальвинистов очень ревнива к другой ереси.\n"+
                          "Затем они выехали в Новый Свет, и сейчас организовали сектантскую общину на острове Кюрасао. Ваша задача заключается в том, чтобы данные негоцианты, кстати, очень богатые люди, купили прощение Папы.\n"+
                          "Индульгенция будет стоить 50 тысяч с каждого. И если они откажутся, то ради вящей Славы Божьей, я даю разрешение на крайние меры.";
			link.l1 = "С каждого по 50 тысяч, и в случае неповиновения я могу делать с ними все, что угодно. Я правильно понял"+ GetSexPhrase("","а") +"?";
			link.l1.go = "Step_S2_9";
		break;
 		case "Step_S2_9":
			dialog.text = "Да, "+ GetSexPhrase("сын мой","дочь моя") +", ты все правильно понял"+ GetSexPhrase("","а") +"...";
			link.l1 = "Но разве 50 тысяч способны искупить грехи янсенистов перед Господом?";
			link.l1.go = "Step_S2_10";
		break;
 		case "Step_S2_10":
			dialog.text = "Нет, конечно. Но мы должны с чего-то начинать. Нам нужно обратить их взор к Господу, этим вы и займетесь. Вам все понятно, вы готовы к выполнению миссии?";
			link.l1 = "Да, монсеньор, приступаю немедленно!!";
			link.l1.go = "exit";
    		pchar.questTemp.State = "Inquisition_toCuracao";
            AddQuestRecord("Spa_Line_2_Inquisition", "2");
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1 = "location";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1.location = "Santiago_town";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition = "Inquisition_MeetFrancisco";
		break;
 		case "Step_S2_11":
			dialog.text = "Спасибо за предупреждение, "+ GetSexPhrase("сын мой","дочь моя") +". Излишняя мягкотелость по отношению к еретикам приводит только к увеличению страданий их душ. Я позабочусь о Франциско, он больше не будет тебе докучать. Возьми это в знак признательности. Полагаю, тебе это пригодится...";
			link.l1 = "Спасибо, святой отец.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_toCuracao";
            GiveItem2Character(pchar,"DeSouzaCross");
		break;
 		case "Step_S2_12":
			dialog.text = "И каковы результаты, "+ GetSexPhrase("сын мой","дочь моя") +"?";
			link.l1 = "Мне не удалось получить деньги ни с одного из этих людей.";
			link.l1.go = "Step_S2_NotMoney";
            if (pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = "Деньги мне удалось получить только с Йозефа Нунена де Фонкесао, ростовщика Кюрасао.";
    			link.l1.go = "Step_S2_OnlyUsurer";
            }
            if (pchar.questTemp.State.Store == "Ok")
            {
    			link.l1 = "Деньги мне удалось получить только с Джоао Ильхайо, хозяина магазина в Кюрасао, и его компаньона Якова Лопез де Фонсека.";
    			link.l1.go = "Step_S2_OnlyStore";
            }
            if (pchar.questTemp.State.Store == "Ok" && pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = "Задние выполнено полностью, святой отец. Деньги мне удалось получить со всех троих указанных вами янсенистов.";
    			link.l1.go = "Step_S2_All";
            }
		break;
 		case "Step_S2_NotMoney":
			dialog.text = "Твои слова ввергли в печаль мою душу... Ты не смог"+ GetSexPhrase("","ла") +" выполнить простейшего задания.";
			link.l1 = "Святой отец, я старал"+ GetSexPhrase("ся","ась") +" изо всех сил...";
			link.l1.go = "Step_S2_13";
		break;
 		case "Step_S2_13":
			dialog.text = "Я понимаю, старание - величашая добродетель людская... Ступай в Гавану, "+ GetSexPhrase("сын мой","дочь моя") +", ты мне больше не нуж"+ GetSexPhrase("ен","на") +"...";
			link.l1 = "Хорошо, монсеньор. Прощайте...";
			link.l1.go = "exit";
            pchar.questTemp.State = "Inquisition_backBad";
            AddQuestRecord("Spa_Line_2_Inquisition", "15");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
		break;
 		case "Step_S2_OnlyUsurer":
            if (sti(pchar.money) >= 50000)
            {
                dialog.text = "Ну что же, частично выполненное задание - это хорошо, "+ GetSexPhrase("сын мой","дочь моя") +"... Но могло быть и лучше.";
    			link.l1 = "Святой отец, я старал"+ GetSexPhrase("ся","ась") +" изо всех сил...";
    			link.l1.go = "Step_S2_14";
            }
            else
            {
                dialog.text = "Э-э-э, задание выполнено, а где же 50 тысяч? Ступай, "+ GetSexPhrase("сын мой","дочь моя") +", и приходи с деньгами для отчета по заданию.";
    			link.l1 = "Прошу прощения, монсеньор, забыл"+ GetSexPhrase("","а") +" на корабле. Я мигом...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyUsurer";
            }
		break;
 		case "Step_S2_14":
			dialog.text = "Ну, ладно, ладно... Итак, давай посчитаем. Согласно установлению Папской канцелярии, взыскание денег с должника приравнивается к нахождению клада. Нашедшему клад причитается от 20 до 30 процентов от его стоимости по рыночной цене, в зависимости от ценности клада.\n"+
                          "С вырученных денег взимается церковная десятина - 10 процентов, именно поэтому она десятиной и называется, хе-хе. Итого твоя награда составляет... составляет... 9 тысяч пиастров. Получи, "+ GetSexPhrase("сын мой","дочь моя") +", распишись - и можешь быть свобод"+ GetSexPhrase("ен","на") +".";
			link.l1 = "Спасибо, монсеньор. Прощайте...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "Подождите, монсеньор. У меня еще кое-что есть для вас...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -41000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_OnlyStore":
            if (sti(pchar.money) >= 100000)
            {
                dialog.text = "Ну что же, частично выполненное задание - это хорошо, "+ GetSexPhrase("сын мой","дочь моя") +"... Но могло быть и лучше.";
    			link.l1 = "Святой отец, я старал"+ GetSexPhrase("ся","ась") +" изо всех сил...";
    			link.l1.go = "Step_S2_15";
            }
            else
            {
                dialog.text = "Э-э-э, задание выполнено, а где же 100 тысяч? Ступай, "+ GetSexPhrase("сын мой","дочь моя") +", и приходи с деньгами для отчета по заданию.";
    			link.l1 = "Прошу прощения, монсеньор, забыл"+ GetSexPhrase("","а") +" на корабле. Я мигом...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyStore";
            }
		break;
 		case "Step_S2_15":
			dialog.text = "Ну, ладно, ладно... Итак, давай посчитаем. Согласно установлению Папской канцелярии, взыскание денег с должника приравнивается к нахождению клада. Нашедшему клад причитается от 20 до 30 процентов от его стоимости по рыночной цене, в зависимости от ценности клада.\n"+
                          "С вырученных денег взимается церковная десятина - 10 процентов, именно поэтому она десятиной и называется, хе-хе. Итого твою награда составляет... составляет... 18 тысяч пиастров. Получи, "+ GetSexPhrase("сын мой","дочь моя") +", распишись - и можешь быть свобод"+ GetSexPhrase("ен","на") +".";
			link.l1 = "Спасибо, монсеньор. Прощайте...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "Подождите, падре. У меня еще кое-что есть для вас...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -82000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_All":
            if (sti(pchar.money) >= 150000)
            {
                dialog.text = "Прекрасно, "+ GetSexPhrase("сын мой","дочь моя") +"! 150 тысяч - значительный вклад в дело нашего Ордена. Мы благодарны тебе...";
    			link.l1 = "Святой отец, я старал"+ GetSexPhrase("ся","ась") +" изо всех сил...";
    			link.l1.go = "Step_S2_16";
            }
            else
            {
                dialog.text = "Э-э-э, задание выполнено, а где же 150 тысяч? Ступай, "+ GetSexPhrase("сын мой","дочь моя") +", и приходи с деньгами для отчета по заданию.";
    			link.l1 = "Прошу прощения, монесеньор, забыл"+ GetSexPhrase("","а") +" на корабле. Я мигом...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_All";
            }
		break;
 		case "Step_S2_16":
			dialog.text = "Ну, ладно, ладно... Итак, давай посчитаем. Согласно установлению Папской канцелярии, взыскание денег с должника приравнивается к нахождению клада. Нашедшему клад причитается от 20 до 30 процентов от его стоимости по рыночной цене, в зависимости от ценности клада.\n"+
                          "С вырученных денег взимается церковная десятина - 10 процентов, именно поэтому она десятиной и называется, хе-хе. Итого твою награда составляет... составляет... 27 тысяч пиастров. Получи, "+ GetSexPhrase("сын мой","дочь моя") +", распишись - и можешь быть свобод"+ GetSexPhrase("ен","на") +".";
			link.l1 = "Спасибо, монсеньор. Прощайте...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "Подождите, монсеньор. У меня еще кое-что есть для вас...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backAllGood";
			AddMoneyToCharacter(pchar, -123000);
			AddQuestRecord("Spa_Line_2_Inquisition", "17");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_17":
			dialog.text = "И что же это такое, "+ GetSexPhrase("сын мой","дочь моя") +"?";
			link.l1 = "Святой отец, помнится, вы мне рассказывали о неком Самуэле Кохэно, который выкрал древние церковные документы из ваших архивов в Севилье...";
			link.l1.go = "Step_S2_18";
		break;
 		case "Step_S2_18":
			dialog.text = "Было такое, и что?";
			link.l1 = "А не выкрал ли он некое Евангелие одного из Первопрестольных Апостолов, но не самого достойного, скорей наоборот...";
			link.l1.go = "Step_S2_19";
		break;
 		case "Step_S2_19":
			dialog.text = "Об этом запрещено даже говорить! Но ты продолжай, "+ GetSexPhrase("сын мой","дочь моя") +", ибо очень меня удивил"+ GetSexPhrase("","а") +"...";
			link.l1 = "Так вот, монсеньор, я наш"+ GetSexPhrase("ел","ла") +" эту книгу. Вот она.";
			link.l1.go = "Step_S2_20";
		break;
 		case "Step_S2_20":
			dialog.text = "Святая Богородица, Матерь Божья!!! О такой удаче мы даже и мечтать не могли! Только и думали о том, где появится этот еретический пасквиль и что будем предпринимать в связи с этим.\n"+
                          "Какой груз с плеч долой!.. "+ GetSexPhrase("сын мой","дочь моя") +", в награду за такой поступок я отпускаю тебе все грехи и еще три авансом!";
			link.l1 = "Я искренне рад"+ GetSexPhrase("","а") +", что сумел"+ GetSexPhrase("","а") +" помочь вам, святой отец...";
			link.l1.go = "Step_S2_21";
			TakeItemFromCharacter(pchar, "Bible");
		break;
 		case "Step_S2_21":
			dialog.text = "Это еще не все, "+ GetSexPhrase("сын мой","дочь моя") +". В знак признательности за содеянные заслуги Святая Инквизиция дарует тебе вот этот великолепный защитный доспех, инкрустированный золотом.\n"+
                          "Однако ценность этой кирасы - не в инкрустации. Ее истинная ценность - в величайшей надежности, что тебе и нужно более всего, как я полагаю...";
			link.l1 = "Именно так, падре. Своей шкурой я как-то дорожу... Ну что же, спасибо и за это. А теперь позвольте откланяться, святой отец.";
			link.l1.go = "Step_S2_22";
		break;
 		case "Step_S2_22":
			dialog.text = "Да, да, кончено. Я тоже побегу, отпишу о радостной новости в Севилью!";
			link.l1 = "Прощайте, монсеньор.";
			link.l1.go = "exit";
            GiveItem2Character(pchar, "cirass5");
		break;
//********************************* Захват Рока Бразильца. Квест №3 **********************************
 		case "Step_S3_1":
            if (CheckPassengerInCharacter(pchar, "RockBrasilian"))
            {
    			dialog.text = "Великолепная работа, "+ GetSexPhrase("сын мой","дочь моя") +"! Я в восхищении!";
    			link.l1 = "Могу сказать без ложной скромности - схватить мерзавца было нелегко. Для этого мне пришлось взять на абордаж корвет, битком набитый пиратским сбродом из Тортуги.";
    			link.l1.go = "Step_S3_2";
            }
            else
            {
    			dialog.text = "Однако, у тебя в трюме его нет! "+ GetSexPhrase("сын мой","дочь моя") +", иди и приведи мне Рока Бразильца.";
    			link.l1 = "Хорошо, монсеньор...";
    			link.l1.go = "exit";
            }
		break;
 		case "Step_S3_2":
			dialog.text = "Ну что же, прикажите доставить этого ладрона ко мне немедленно, мне не терпится начать следствие. И прошу вас зайти также к генерал-губернатору.";
			link.l1 = "Хорошо, монсеньор.";
			link.l1.go = "exit";
			NPChar.LifeDay = 10;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			AddQuestRecord("Spa_Line_3_RockBrasilian", "6");
			pchar.questTemp.State = "TakeRockBras_RockGiven";
			sld = characterFromId("RockBrasilian");
			ReleasePrisoner(sld);
     	    sld.LifeDay = 0; // уберем нпс
		break;

    }
}
