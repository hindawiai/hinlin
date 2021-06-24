<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common घातer driver क्रम PDAs and phones with one or two बाह्यal
 * घातer supplies (AC/USB) connected to मुख्य and backup batteries,
 * and optional builtin अक्षरger.
 *
 * Copyright तऊ 2007 Anton Vorontsov <cbou@mail.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/usb/otg.h>

अटल अंतरभूत अचिन्हित पूर्णांक get_irq_flags(काष्ठा resource *res)
अणु
	वापस IRQF_SHARED | (res->flags & IRQF_TRIGGER_MASK);
पूर्ण

अटल काष्ठा device *dev;
अटल काष्ठा pda_घातer_pdata *pdata;
अटल काष्ठा resource *ac_irq, *usb_irq;
अटल काष्ठा delayed_work अक्षरger_work;
अटल काष्ठा delayed_work polling_work;
अटल काष्ठा delayed_work supply_work;
अटल पूर्णांक polling;
अटल काष्ठा घातer_supply *pda_psy_ac, *pda_psy_usb;

#अगर IS_ENABLED(CONFIG_USB_PHY)
अटल काष्ठा usb_phy *transceiver;
अटल काष्ठा notअगरier_block otg_nb;
#पूर्ण_अगर

अटल काष्ठा regulator *ac_draw;

क्रमागत अणु
	PDA_PSY_OFFLINE = 0,
	PDA_PSY_ONLINE = 1,
	PDA_PSY_TO_CHANGE,
पूर्ण;
अटल पूर्णांक new_ac_status = -1;
अटल पूर्णांक new_usb_status = -1;
अटल पूर्णांक ac_status = -1;
अटल पूर्णांक usb_status = -1;

अटल पूर्णांक pda_घातer_get_property(काष्ठा घातer_supply *psy,
				  क्रमागत घातer_supply_property psp,
				  जोड़ घातer_supply_propval *val)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		अगर (psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
			val->पूर्णांकval = pdata->is_ac_online ?
				      pdata->is_ac_online() : 0;
		अन्यथा
			val->पूर्णांकval = pdata->is_usb_online ?
				      pdata->is_usb_online() : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property pda_घातer_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल अक्षर *pda_घातer_supplied_to[] = अणु
	"main-battery",
	"backup-battery",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pda_psy_ac_desc = अणु
	.name = "ac",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = pda_घातer_props,
	.num_properties = ARRAY_SIZE(pda_घातer_props),
	.get_property = pda_घातer_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pda_psy_usb_desc = अणु
	.name = "usb",
	.type = POWER_SUPPLY_TYPE_USB,
	.properties = pda_घातer_props,
	.num_properties = ARRAY_SIZE(pda_घातer_props),
	.get_property = pda_घातer_get_property,
पूर्ण;

अटल व्योम update_status(व्योम)
अणु
	अगर (pdata->is_ac_online)
		new_ac_status = !!pdata->is_ac_online();

	अगर (pdata->is_usb_online)
		new_usb_status = !!pdata->is_usb_online();
पूर्ण

अटल व्योम update_अक्षरger(व्योम)
अणु
	अटल पूर्णांक regulator_enabled;
	पूर्णांक max_uA = pdata->ac_max_uA;

	अगर (pdata->set_अक्षरge) अणु
		अगर (new_ac_status > 0) अणु
			dev_dbg(dev, "charger on (AC)\n");
			pdata->set_अक्षरge(PDA_POWER_CHARGE_AC);
		पूर्ण अन्यथा अगर (new_usb_status > 0) अणु
			dev_dbg(dev, "charger on (USB)\n");
			pdata->set_अक्षरge(PDA_POWER_CHARGE_USB);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "charger off\n");
			pdata->set_अक्षरge(0);
		पूर्ण
	पूर्ण अन्यथा अगर (ac_draw) अणु
		अगर (new_ac_status > 0) अणु
			regulator_set_current_limit(ac_draw, max_uA, max_uA);
			अगर (!regulator_enabled) अणु
				dev_dbg(dev, "charger on (AC)\n");
				WARN_ON(regulator_enable(ac_draw));
				regulator_enabled = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (regulator_enabled) अणु
				dev_dbg(dev, "charger off\n");
				WARN_ON(regulator_disable(ac_draw));
				regulator_enabled = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम supply_work_func(काष्ठा work_काष्ठा *work)
अणु
	अगर (ac_status == PDA_PSY_TO_CHANGE) अणु
		ac_status = new_ac_status;
		घातer_supply_changed(pda_psy_ac);
	पूर्ण

	अगर (usb_status == PDA_PSY_TO_CHANGE) अणु
		usb_status = new_usb_status;
		घातer_supply_changed(pda_psy_usb);
	पूर्ण
पूर्ण

अटल व्योम psy_changed(व्योम)
अणु
	update_अक्षरger();

	/*
	 * Okay, अक्षरger set. Now रुको a bit beक्रमe notअगरying supplicants,
	 * अक्षरge घातer should stabilize.
	 */
	cancel_delayed_work(&supply_work);
	schedule_delayed_work(&supply_work,
			      msecs_to_jअगरfies(pdata->रुको_क्रम_अक्षरger));
पूर्ण

अटल व्योम अक्षरger_work_func(काष्ठा work_काष्ठा *work)
अणु
	update_status();
	psy_changed();
पूर्ण

अटल irqवापस_t घातer_changed_isr(पूर्णांक irq, व्योम *घातer_supply)
अणु
	अगर (घातer_supply == pda_psy_ac)
		ac_status = PDA_PSY_TO_CHANGE;
	अन्यथा अगर (घातer_supply == pda_psy_usb)
		usb_status = PDA_PSY_TO_CHANGE;
	अन्यथा
		वापस IRQ_NONE;

	/*
	 * Wait a bit beक्रमe पढ़ोing ac/usb line status and setting अक्षरger,
	 * because ac/usb status पढ़ोings may lag from irq.
	 */
	cancel_delayed_work(&अक्षरger_work);
	schedule_delayed_work(&अक्षरger_work,
			      msecs_to_jअगरfies(pdata->रुको_क्रम_status));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम polling_work_func(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक changed = 0;

	dev_dbg(dev, "polling...\n");

	update_status();

	अगर (!ac_irq && new_ac_status != ac_status) अणु
		ac_status = PDA_PSY_TO_CHANGE;
		changed = 1;
	पूर्ण

	अगर (!usb_irq && new_usb_status != usb_status) अणु
		usb_status = PDA_PSY_TO_CHANGE;
		changed = 1;
	पूर्ण

	अगर (changed)
		psy_changed();

	cancel_delayed_work(&polling_work);
	schedule_delayed_work(&polling_work,
			      msecs_to_jअगरfies(pdata->polling_पूर्णांकerval));
पूर्ण

#अगर IS_ENABLED(CONFIG_USB_PHY)
अटल पूर्णांक otg_is_usb_online(व्योम)
अणु
	वापस (transceiver->last_event == USB_EVENT_VBUS ||
		transceiver->last_event == USB_EVENT_ENUMERATED);
पूर्ण

अटल पूर्णांक otg_is_ac_online(व्योम)
अणु
	वापस (transceiver->last_event == USB_EVENT_CHARGER);
पूर्ण

अटल पूर्णांक otg_handle_notअगरication(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *unused)
अणु
	चयन (event) अणु
	हाल USB_EVENT_CHARGER:
		ac_status = PDA_PSY_TO_CHANGE;
		अवरोध;
	हाल USB_EVENT_VBUS:
	हाल USB_EVENT_ENUMERATED:
		usb_status = PDA_PSY_TO_CHANGE;
		अवरोध;
	हाल USB_EVENT_NONE:
		ac_status = PDA_PSY_TO_CHANGE;
		usb_status = PDA_PSY_TO_CHANGE;
		अवरोध;
	शेष:
		वापस NOTIFY_OK;
	पूर्ण

	/*
	 * Wait a bit beक्रमe पढ़ोing ac/usb line status and setting अक्षरger,
	 * because ac/usb status पढ़ोings may lag from irq.
	 */
	cancel_delayed_work(&अक्षरger_work);
	schedule_delayed_work(&अक्षरger_work,
			      msecs_to_jअगरfies(pdata->रुको_क्रम_status));

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pda_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक ret = 0;

	dev = &pdev->dev;

	अगर (pdev->id != -1) अणु
		dev_err(dev, "it's meaningless to register several "
			"pda_powers; use id = -1\n");
		ret = -EINVAL;
		जाओ wrongid;
	पूर्ण

	pdata = pdev->dev.platक्रमm_data;

	अगर (pdata->init) अणु
		ret = pdata->init(dev);
		अगर (ret < 0)
			जाओ init_failed;
	पूर्ण

	ac_draw = regulator_get(dev, "ac_draw");
	अगर (IS_ERR(ac_draw)) अणु
		dev_dbg(dev, "couldn't get ac_draw regulator\n");
		ac_draw = शून्य;
	पूर्ण

	update_status();
	update_अक्षरger();

	अगर (!pdata->रुको_क्रम_status)
		pdata->रुको_क्रम_status = 500;

	अगर (!pdata->रुको_क्रम_अक्षरger)
		pdata->रुको_क्रम_अक्षरger = 500;

	अगर (!pdata->polling_पूर्णांकerval)
		pdata->polling_पूर्णांकerval = 2000;

	अगर (!pdata->ac_max_uA)
		pdata->ac_max_uA = 500000;

	INIT_DELAYED_WORK(&अक्षरger_work, अक्षरger_work_func);
	INIT_DELAYED_WORK(&supply_work, supply_work_func);

	ac_irq = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "ac");
	usb_irq = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "usb");

	अगर (pdata->supplied_to) अणु
		psy_cfg.supplied_to = pdata->supplied_to;
		psy_cfg.num_supplicants = pdata->num_supplicants;
	पूर्ण अन्यथा अणु
		psy_cfg.supplied_to = pda_घातer_supplied_to;
		psy_cfg.num_supplicants = ARRAY_SIZE(pda_घातer_supplied_to);
	पूर्ण

#अगर IS_ENABLED(CONFIG_USB_PHY)
	transceiver = usb_get_phy(USB_PHY_TYPE_USB2);
	अगर (!IS_ERR_OR_शून्य(transceiver)) अणु
		अगर (!pdata->is_usb_online)
			pdata->is_usb_online = otg_is_usb_online;
		अगर (!pdata->is_ac_online)
			pdata->is_ac_online = otg_is_ac_online;
	पूर्ण
#पूर्ण_अगर

	अगर (pdata->is_ac_online) अणु
		pda_psy_ac = घातer_supply_रेजिस्टर(&pdev->dev,
						   &pda_psy_ac_desc, &psy_cfg);
		अगर (IS_ERR(pda_psy_ac)) अणु
			dev_err(dev, "failed to register %s power supply\n",
				pda_psy_ac_desc.name);
			ret = PTR_ERR(pda_psy_ac);
			जाओ ac_supply_failed;
		पूर्ण

		अगर (ac_irq) अणु
			ret = request_irq(ac_irq->start, घातer_changed_isr,
					  get_irq_flags(ac_irq), ac_irq->name,
					  pda_psy_ac);
			अगर (ret) अणु
				dev_err(dev, "request ac irq failed\n");
				जाओ ac_irq_failed;
			पूर्ण
		पूर्ण अन्यथा अणु
			polling = 1;
		पूर्ण
	पूर्ण

	अगर (pdata->is_usb_online) अणु
		pda_psy_usb = घातer_supply_रेजिस्टर(&pdev->dev,
						    &pda_psy_usb_desc,
						    &psy_cfg);
		अगर (IS_ERR(pda_psy_usb)) अणु
			dev_err(dev, "failed to register %s power supply\n",
				pda_psy_usb_desc.name);
			ret = PTR_ERR(pda_psy_usb);
			जाओ usb_supply_failed;
		पूर्ण

		अगर (usb_irq) अणु
			ret = request_irq(usb_irq->start, घातer_changed_isr,
					  get_irq_flags(usb_irq),
					  usb_irq->name, pda_psy_usb);
			अगर (ret) अणु
				dev_err(dev, "request usb irq failed\n");
				जाओ usb_irq_failed;
			पूर्ण
		पूर्ण अन्यथा अणु
			polling = 1;
		पूर्ण
	पूर्ण

#अगर IS_ENABLED(CONFIG_USB_PHY)
	अगर (!IS_ERR_OR_शून्य(transceiver) && pdata->use_otg_notअगरier) अणु
		otg_nb.notअगरier_call = otg_handle_notअगरication;
		ret = usb_रेजिस्टर_notअगरier(transceiver, &otg_nb);
		अगर (ret) अणु
			dev_err(dev, "failure to register otg notifier\n");
			जाओ otg_reg_notअगरier_failed;
		पूर्ण
		polling = 0;
	पूर्ण
#पूर्ण_अगर

	अगर (polling) अणु
		dev_dbg(dev, "will poll for status\n");
		INIT_DELAYED_WORK(&polling_work, polling_work_func);
		cancel_delayed_work(&polling_work);
		schedule_delayed_work(&polling_work,
				      msecs_to_jअगरfies(pdata->polling_पूर्णांकerval));
	पूर्ण

	अगर (ac_irq || usb_irq)
		device_init_wakeup(&pdev->dev, 1);

	वापस 0;

#अगर IS_ENABLED(CONFIG_USB_PHY)
otg_reg_notअगरier_failed:
	अगर (pdata->is_usb_online && usb_irq)
		मुक्त_irq(usb_irq->start, pda_psy_usb);
#पूर्ण_अगर
usb_irq_failed:
	अगर (pdata->is_usb_online)
		घातer_supply_unरेजिस्टर(pda_psy_usb);
usb_supply_failed:
	अगर (pdata->is_ac_online && ac_irq)
		मुक्त_irq(ac_irq->start, pda_psy_ac);
#अगर IS_ENABLED(CONFIG_USB_PHY)
	अगर (!IS_ERR_OR_शून्य(transceiver))
		usb_put_phy(transceiver);
#पूर्ण_अगर
ac_irq_failed:
	अगर (pdata->is_ac_online)
		घातer_supply_unरेजिस्टर(pda_psy_ac);
ac_supply_failed:
	अगर (ac_draw) अणु
		regulator_put(ac_draw);
		ac_draw = शून्य;
	पूर्ण
	अगर (pdata->निकास)
		pdata->निकास(dev);
init_failed:
wrongid:
	वापस ret;
पूर्ण

अटल पूर्णांक pda_घातer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
#अगर IS_ENABLED(CONFIG_USB_PHY)
	अगर (!IS_ERR_OR_शून्य(transceiver) && pdata->use_otg_notअगरier)
		usb_unरेजिस्टर_notअगरier(transceiver, &otg_nb);
#पूर्ण_अगर
	अगर (pdata->is_usb_online && usb_irq)
		मुक्त_irq(usb_irq->start, pda_psy_usb);
	अगर (pdata->is_ac_online && ac_irq)
		मुक्त_irq(ac_irq->start, pda_psy_ac);

	अगर (polling)
		cancel_delayed_work_sync(&polling_work);
	cancel_delayed_work_sync(&अक्षरger_work);
	cancel_delayed_work_sync(&supply_work);

	अगर (pdata->is_usb_online)
		घातer_supply_unरेजिस्टर(pda_psy_usb);
	अगर (pdata->is_ac_online)
		घातer_supply_unरेजिस्टर(pda_psy_ac);
#अगर IS_ENABLED(CONFIG_USB_PHY)
	अगर (!IS_ERR_OR_शून्य(transceiver))
		usb_put_phy(transceiver);
#पूर्ण_अगर
	अगर (ac_draw) अणु
		regulator_put(ac_draw);
		ac_draw = शून्य;
	पूर्ण
	अगर (pdata->निकास)
		pdata->निकास(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ac_wakeup_enabled;
अटल पूर्णांक usb_wakeup_enabled;

अटल पूर्णांक pda_घातer_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	अगर (pdata->suspend) अणु
		पूर्णांक ret = pdata->suspend(state);

		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (ac_irq)
			ac_wakeup_enabled = !enable_irq_wake(ac_irq->start);
		अगर (usb_irq)
			usb_wakeup_enabled = !enable_irq_wake(usb_irq->start);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pda_घातer_resume(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (usb_irq && usb_wakeup_enabled)
			disable_irq_wake(usb_irq->start);
		अगर (ac_irq && ac_wakeup_enabled)
			disable_irq_wake(ac_irq->start);
	पूर्ण

	अगर (pdata->resume)
		वापस pdata->resume();

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा pda_घातer_suspend शून्य
#घोषणा pda_घातer_resume शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver pda_घातer_pdrv = अणु
	.driver = अणु
		.name = "pda-power",
	पूर्ण,
	.probe = pda_घातer_probe,
	.हटाओ = pda_घातer_हटाओ,
	.suspend = pda_घातer_suspend,
	.resume = pda_घातer_resume,
पूर्ण;

module_platक्रमm_driver(pda_घातer_pdrv);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Vorontsov <cbou@mail.ru>");
MODULE_ALIAS("platform:pda-power");
