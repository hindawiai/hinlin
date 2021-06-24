<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम OLPC XO-1 System Control Interrupts (SCI)
 *
 * Copyright (C) 2010 One Laptop per Child
 * Copyright (C) 2006 Red Hat, Inc.
 * Copyright (C) 2006 Advanced Micro Devices, Inc.
 */

#समावेश <linux/cs5535.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/suspend.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/olpc-ec.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/olpc.h>

#घोषणा DRV_NAME	"olpc-xo1-sci"
#घोषणा PFX		DRV_NAME ": "

अटल अचिन्हित दीर्घ acpi_base;
अटल काष्ठा input_dev *घातer_button_idev;
अटल काष्ठा input_dev *ebook_चयन_idev;
अटल काष्ठा input_dev *lid_चयन_idev;

अटल पूर्णांक sci_irq;

अटल bool lid_खोलो;
अटल bool lid_inverted;
अटल पूर्णांक lid_wake_mode;

क्रमागत lid_wake_modes अणु
	LID_WAKE_ALWAYS,
	LID_WAKE_OPEN,
	LID_WAKE_CLOSE,
पूर्ण;

अटल स्थिर अक्षर * स्थिर lid_wake_mode_names[] = अणु
	[LID_WAKE_ALWAYS] = "always",
	[LID_WAKE_OPEN] = "open",
	[LID_WAKE_CLOSE] = "close",
पूर्ण;

अटल व्योम battery_status_changed(व्योम)
अणु
	काष्ठा घातer_supply *psy = घातer_supply_get_by_name("olpc_battery");

	अगर (psy) अणु
		घातer_supply_changed(psy);
		घातer_supply_put(psy);
	पूर्ण
पूर्ण

अटल व्योम ac_status_changed(व्योम)
अणु
	काष्ठा घातer_supply *psy = घातer_supply_get_by_name("olpc_ac");

	अगर (psy) अणु
		घातer_supply_changed(psy);
		घातer_supply_put(psy);
	पूर्ण
पूर्ण

/* Report current ebook चयन state through input layer */
अटल व्योम send_ebook_state(व्योम)
अणु
	अचिन्हित अक्षर state;

	अगर (olpc_ec_cmd(EC_READ_EB_MODE, शून्य, 0, &state, 1)) अणु
		pr_err(PFX "failed to get ebook state\n");
		वापस;
	पूर्ण

	अगर (!!test_bit(SW_TABLET_MODE, ebook_चयन_idev->sw) == state)
		वापस; /* Nothing new to report. */

	input_report_चयन(ebook_चयन_idev, SW_TABLET_MODE, state);
	input_sync(ebook_चयन_idev);
	pm_wakeup_event(&ebook_चयन_idev->dev, 0);
पूर्ण

अटल व्योम flip_lid_inverter(व्योम)
अणु
	/* gpio is high; invert so we'll get l->h event पूर्णांकerrupt */
	अगर (lid_inverted)
		cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_INPUT_INVERT);
	अन्यथा
		cs5535_gpio_set(OLPC_GPIO_LID, GPIO_INPUT_INVERT);
	lid_inverted = !lid_inverted;
पूर्ण

अटल व्योम detect_lid_state(व्योम)
अणु
	/*
	 * the edge detector hookup on the gpio inमाला_दो on the geode is
	 * odd, to say the least.  See http://dev.laptop.org/ticket/5703
	 * क्रम details, but in a nutshell:  we करोn't use the edge
	 * detectors.  instead, we make use of an anomaly:  with the both
	 * edge detectors turned off, we still get an edge event on a
	 * positive edge transition.  to take advantage of this, we use the
	 * front-end inverter to ensure that that's the edge we're always
	 * going to see next.
	 */

	पूर्णांक state;

	state = cs5535_gpio_isset(OLPC_GPIO_LID, GPIO_READ_BACK);
	lid_खोलो = !state ^ !lid_inverted; /* x ^^ y */
	अगर (!state)
		वापस;

	flip_lid_inverter();
पूर्ण

/* Report current lid चयन state through input layer */
अटल व्योम send_lid_state(व्योम)
अणु
	अगर (!!test_bit(SW_LID, lid_चयन_idev->sw) == !lid_खोलो)
		वापस; /* Nothing new to report. */

	input_report_चयन(lid_चयन_idev, SW_LID, !lid_खोलो);
	input_sync(lid_चयन_idev);
	pm_wakeup_event(&lid_चयन_idev->dev, 0);
पूर्ण

अटल sमाप_प्रकार lid_wake_mode_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *mode = lid_wake_mode_names[lid_wake_mode];
	वापस प्र_लिखो(buf, "%s\n", mode);
पूर्ण
अटल sमाप_प्रकार lid_wake_mode_set(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(lid_wake_mode_names); i++) अणु
		स्थिर अक्षर *mode = lid_wake_mode_names[i];
		अगर (म_माप(mode) != count || strnहालcmp(mode, buf, count))
			जारी;

		lid_wake_mode = i;
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR(lid_wake_mode, S_IWUSR | S_IRUGO, lid_wake_mode_show,
		   lid_wake_mode_set);

अटल काष्ठा attribute *lid_attrs[] = अणु
	&dev_attr_lid_wake_mode.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(lid);

/*
 * Process all items in the EC's SCI queue.
 *
 * This is handled in a workqueue because olpc_ec_cmd can be slow (and
 * can even समयout).
 *
 * If propagate_events is false, the queue is drained without events being
 * generated क्रम the पूर्णांकerrupts.
 */
अटल व्योम process_sci_queue(bool propagate_events)
अणु
	पूर्णांक r;
	u16 data;

	करो अणु
		r = olpc_ec_sci_query(&data);
		अगर (r || !data)
			अवरोध;

		pr_debug(PFX "SCI 0x%x received\n", data);

		चयन (data) अणु
		हाल EC_SCI_SRC_BATERR:
		हाल EC_SCI_SRC_BATSOC:
		हाल EC_SCI_SRC_BATTERY:
		हाल EC_SCI_SRC_BATCRIT:
			battery_status_changed();
			अवरोध;
		हाल EC_SCI_SRC_ACPWR:
			ac_status_changed();
			अवरोध;
		पूर्ण

		अगर (data == EC_SCI_SRC_EBOOK && propagate_events)
			send_ebook_state();
	पूर्ण जबतक (data);

	अगर (r)
		pr_err(PFX "Failed to clear SCI queue");
पूर्ण

अटल व्योम process_sci_queue_work(काष्ठा work_काष्ठा *work)
अणु
	process_sci_queue(true);
पूर्ण

अटल DECLARE_WORK(sci_work, process_sci_queue_work);

अटल irqवापस_t xo1_sci_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	u32 sts;
	u32 gpe;

	sts = inl(acpi_base + CS5536_PM1_STS);
	outl(sts | 0xffff, acpi_base + CS5536_PM1_STS);

	gpe = inl(acpi_base + CS5536_PM_GPE0_STS);
	outl(0xffffffff, acpi_base + CS5536_PM_GPE0_STS);

	dev_dbg(&pdev->dev, "sts %x gpe %x\n", sts, gpe);

	अगर (sts & CS5536_PWRBTN_FLAG) अणु
		अगर (!(sts & CS5536_WAK_FLAG)) अणु
			/* Only report घातer button input when it was pressed
			 * during regular operation (as opposed to when it
			 * was used to wake the प्रणाली). */
			input_report_key(घातer_button_idev, KEY_POWER, 1);
			input_sync(घातer_button_idev);
			input_report_key(घातer_button_idev, KEY_POWER, 0);
			input_sync(घातer_button_idev);
		पूर्ण
		/* Report the wakeup event in all हालs. */
		pm_wakeup_event(&घातer_button_idev->dev, 0);
	पूर्ण

	अगर ((sts & (CS5536_RTC_FLAG | CS5536_WAK_FLAG)) ==
			(CS5536_RTC_FLAG | CS5536_WAK_FLAG)) अणु
		/* When the प्रणाली is woken by the RTC alarm, report the
		 * event on the rtc device. */
		काष्ठा device *rtc = bus_find_device_by_name(
			&platक्रमm_bus_type, शून्य, "rtc_cmos");
		अगर (rtc) अणु
			pm_wakeup_event(rtc, 0);
			put_device(rtc);
		पूर्ण
	पूर्ण

	अगर (gpe & CS5536_GPIOM7_PME_FLAG) अणु /* EC GPIO */
		cs5535_gpio_set(OLPC_GPIO_ECSCI, GPIO_NEGATIVE_EDGE_STS);
		schedule_work(&sci_work);
	पूर्ण

	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_POSITIVE_EDGE_STS);
	detect_lid_state();
	send_lid_state();

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xo1_sci_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	अगर (device_may_wakeup(&घातer_button_idev->dev))
		olpc_xo1_pm_wakeup_set(CS5536_PM_PWRBTN);
	अन्यथा
		olpc_xo1_pm_wakeup_clear(CS5536_PM_PWRBTN);

	अगर (device_may_wakeup(&ebook_चयन_idev->dev))
		olpc_ec_wakeup_set(EC_SCI_SRC_EBOOK);
	अन्यथा
		olpc_ec_wakeup_clear(EC_SCI_SRC_EBOOK);

	अगर (!device_may_wakeup(&lid_चयन_idev->dev)) अणु
		cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);
	पूर्ण अन्यथा अगर ((lid_खोलो && lid_wake_mode == LID_WAKE_OPEN) ||
		   (!lid_खोलो && lid_wake_mode == LID_WAKE_CLOSE)) अणु
		flip_lid_inverter();

		/* we may have just caused an event */
		cs5535_gpio_set(OLPC_GPIO_LID, GPIO_NEGATIVE_EDGE_STS);
		cs5535_gpio_set(OLPC_GPIO_LID, GPIO_POSITIVE_EDGE_STS);

		cs5535_gpio_set(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xo1_sci_resume(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * We करोn't know what may have happened जबतक we were asleep.
	 * Reestablish our lid setup so we're sure to catch all transitions.
	 */
	detect_lid_state();
	send_lid_state();
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);

	/* Enable all EC events */
	olpc_ec_mask_ग_लिखो(EC_SCI_SRC_ALL);

	/* Power/battery status might have changed too */
	battery_status_changed();
	ac_status_changed();
	वापस 0;
पूर्ण

अटल पूर्णांक setup_sci_पूर्णांकerrupt(काष्ठा platक्रमm_device *pdev)
अणु
	u32 lo, hi;
	u32 sts;
	पूर्णांक r;

	rdmsr(0x51400020, lo, hi);
	sci_irq = (lo >> 20) & 15;

	अगर (sci_irq) अणु
		dev_info(&pdev->dev, "SCI is mapped to IRQ %d\n", sci_irq);
	पूर्ण अन्यथा अणु
		/* Zero means masked */
		dev_info(&pdev->dev, "SCI unmapped. Mapping to IRQ 3\n");
		sci_irq = 3;
		lo |= 0x00300000;
		wrmsrl(0x51400020, lo);
	पूर्ण

	/* Select level triggered in PIC */
	अगर (sci_irq < 8) अणु
		lo = inb(CS5536_PIC_INT_SEL1);
		lo |= 1 << sci_irq;
		outb(lo, CS5536_PIC_INT_SEL1);
	पूर्ण अन्यथा अणु
		lo = inb(CS5536_PIC_INT_SEL2);
		lo |= 1 << (sci_irq - 8);
		outb(lo, CS5536_PIC_INT_SEL2);
	पूर्ण

	/* Enable पूर्णांकeresting SCI events, and clear pending पूर्णांकerrupts */
	sts = inl(acpi_base + CS5536_PM1_STS);
	outl(((CS5536_PM_PWRBTN | CS5536_PM_RTC) << 16) | 0xffff,
	     acpi_base + CS5536_PM1_STS);

	r = request_irq(sci_irq, xo1_sci_पूर्णांकr, 0, DRV_NAME, pdev);
	अगर (r)
		dev_err(&pdev->dev, "can't request interrupt\n");

	वापस r;
पूर्ण

अटल पूर्णांक setup_ec_sci(व्योम)
अणु
	पूर्णांक r;

	r = gpio_request(OLPC_GPIO_ECSCI, "OLPC-ECSCI");
	अगर (r)
		वापस r;

	gpio_direction_input(OLPC_GPIO_ECSCI);

	/* Clear pending EC SCI events */
	cs5535_gpio_set(OLPC_GPIO_ECSCI, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_ECSCI, GPIO_POSITIVE_EDGE_STS);

	/*
	 * Enable EC SCI events, and map them to both a PME and the SCI
	 * पूर्णांकerrupt.
	 *
	 * Ordinarily, in addition to functioning as GPIOs, Geode GPIOs can
	 * be mapped to regular पूर्णांकerrupts *or* Geode-specअगरic Power
	 * Management Events (PMEs) - events that bring the प्रणाली out of
	 * suspend. In this हाल, we want both of those things - the प्रणाली
	 * wakeup, *and* the ability to get an पूर्णांकerrupt when an event occurs.
	 *
	 * To achieve this, we map the GPIO to a PME, and then we use one
	 * of the many generic knobs on the CS5535 PIC to additionally map the
	 * PME to the regular SCI पूर्णांकerrupt line.
	 */
	cs5535_gpio_set(OLPC_GPIO_ECSCI, GPIO_EVENTS_ENABLE);

	/* Set the SCI to cause a PME event on group 7 */
	cs5535_gpio_setup_event(OLPC_GPIO_ECSCI, 7, 1);

	/* And have group 7 also fire the SCI पूर्णांकerrupt */
	cs5535_pic_unreqz_select_high(7, sci_irq);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_ec_sci(व्योम)
अणु
	gpio_मुक्त(OLPC_GPIO_ECSCI);
पूर्ण

अटल पूर्णांक setup_lid_events(व्योम)
अणु
	पूर्णांक r;

	r = gpio_request(OLPC_GPIO_LID, "OLPC-LID");
	अगर (r)
		वापस r;

	gpio_direction_input(OLPC_GPIO_LID);

	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_INPUT_INVERT);
	lid_inverted = 0;

	/* Clear edge detection and event enable क्रम now */
	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);
	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_NEGATIVE_EDGE_EN);
	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_POSITIVE_EDGE_EN);
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_POSITIVE_EDGE_STS);

	/* Set the LID to cause an PME event on group 6 */
	cs5535_gpio_setup_event(OLPC_GPIO_LID, 6, 1);

	/* Set PME group 6 to fire the SCI पूर्णांकerrupt */
	cs5535_gpio_set_irq(6, sci_irq);

	/* Enable the event */
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_lid_events(व्योम)
अणु
	gpio_मुक्त(OLPC_GPIO_LID);
पूर्ण

अटल पूर्णांक setup_घातer_button(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक r;

	घातer_button_idev = input_allocate_device();
	अगर (!घातer_button_idev)
		वापस -ENOMEM;

	घातer_button_idev->name = "Power Button";
	घातer_button_idev->phys = DRV_NAME "/input0";
	set_bit(EV_KEY, घातer_button_idev->evbit);
	set_bit(KEY_POWER, घातer_button_idev->keybit);

	घातer_button_idev->dev.parent = &pdev->dev;
	device_init_wakeup(&घातer_button_idev->dev, 1);

	r = input_रेजिस्टर_device(घातer_button_idev);
	अगर (r) अणु
		dev_err(&pdev->dev, "failed to register power button: %d\n", r);
		input_मुक्त_device(घातer_button_idev);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम मुक्त_घातer_button(व्योम)
अणु
	input_unरेजिस्टर_device(घातer_button_idev);
पूर्ण

अटल पूर्णांक setup_ebook_चयन(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक r;

	ebook_चयन_idev = input_allocate_device();
	अगर (!ebook_चयन_idev)
		वापस -ENOMEM;

	ebook_चयन_idev->name = "EBook Switch";
	ebook_चयन_idev->phys = DRV_NAME "/input1";
	set_bit(EV_SW, ebook_चयन_idev->evbit);
	set_bit(SW_TABLET_MODE, ebook_चयन_idev->swbit);

	ebook_चयन_idev->dev.parent = &pdev->dev;
	device_set_wakeup_capable(&ebook_चयन_idev->dev, true);

	r = input_रेजिस्टर_device(ebook_चयन_idev);
	अगर (r) अणु
		dev_err(&pdev->dev, "failed to register ebook switch: %d\n", r);
		input_मुक्त_device(ebook_चयन_idev);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम मुक्त_ebook_चयन(व्योम)
अणु
	input_unरेजिस्टर_device(ebook_चयन_idev);
पूर्ण

अटल पूर्णांक setup_lid_चयन(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक r;

	lid_चयन_idev = input_allocate_device();
	अगर (!lid_चयन_idev)
		वापस -ENOMEM;

	lid_चयन_idev->name = "Lid Switch";
	lid_चयन_idev->phys = DRV_NAME "/input2";
	set_bit(EV_SW, lid_चयन_idev->evbit);
	set_bit(SW_LID, lid_चयन_idev->swbit);

	lid_चयन_idev->dev.parent = &pdev->dev;
	device_set_wakeup_capable(&lid_चयन_idev->dev, true);

	r = input_रेजिस्टर_device(lid_चयन_idev);
	अगर (r) अणु
		dev_err(&pdev->dev, "failed to register lid switch: %d\n", r);
		जाओ err_रेजिस्टर;
	पूर्ण

	वापस 0;

err_रेजिस्टर:
	input_मुक्त_device(lid_चयन_idev);
	वापस r;
पूर्ण

अटल व्योम मुक्त_lid_चयन(व्योम)
अणु
	input_unरेजिस्टर_device(lid_चयन_idev);
पूर्ण

अटल पूर्णांक xo1_sci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक r;

	/* करोn't run on non-XOs */
	अगर (!machine_is_olpc())
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		वापस -EIO;
	पूर्ण
	acpi_base = res->start;

	r = setup_घातer_button(pdev);
	अगर (r)
		वापस r;

	r = setup_ebook_चयन(pdev);
	अगर (r)
		जाओ err_ebook;

	r = setup_lid_चयन(pdev);
	अगर (r)
		जाओ err_lid;

	r = setup_lid_events();
	अगर (r)
		जाओ err_lidevt;

	r = setup_ec_sci();
	अगर (r)
		जाओ err_ecsci;

	/* Enable PME generation क्रम EC-generated events */
	outl(CS5536_GPIOM6_PME_EN | CS5536_GPIOM7_PME_EN,
		acpi_base + CS5536_PM_GPE0_EN);

	/* Clear pending events */
	outl(0xffffffff, acpi_base + CS5536_PM_GPE0_STS);
	process_sci_queue(false);

	/* Initial sync */
	send_ebook_state();
	detect_lid_state();
	send_lid_state();

	r = setup_sci_पूर्णांकerrupt(pdev);
	अगर (r)
		जाओ err_sci;

	/* Enable all EC events */
	olpc_ec_mask_ग_लिखो(EC_SCI_SRC_ALL);

	वापस r;

err_sci:
	मुक्त_ec_sci();
err_ecsci:
	मुक्त_lid_events();
err_lidevt:
	मुक्त_lid_चयन();
err_lid:
	मुक्त_ebook_चयन();
err_ebook:
	मुक्त_घातer_button();
	वापस r;
पूर्ण

अटल पूर्णांक xo1_sci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	मुक्त_irq(sci_irq, pdev);
	cancel_work_sync(&sci_work);
	मुक्त_ec_sci();
	मुक्त_lid_events();
	मुक्त_lid_चयन();
	मुक्त_ebook_चयन();
	मुक्त_घातer_button();
	acpi_base = 0;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xo1_sci_driver = अणु
	.driver = अणु
		.name = "olpc-xo1-sci-acpi",
		.dev_groups = lid_groups,
	पूर्ण,
	.probe = xo1_sci_probe,
	.हटाओ = xo1_sci_हटाओ,
	.suspend = xo1_sci_suspend,
	.resume = xo1_sci_resume,
पूर्ण;

अटल पूर्णांक __init xo1_sci_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&xo1_sci_driver);
पूर्ण
arch_initcall(xo1_sci_init);
