<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TS3A227E Autonomous Audio Accessory Detection and Configuration Switch
 *
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/acpi.h>

#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>

#समावेश "ts3a227e.h"

काष्ठा ts3a227e अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_jack *jack;
	bool plugged;
	bool mic_present;
	अचिन्हित पूर्णांक buttons_held;
	पूर्णांक irq;
पूर्ण;

/* Button values to be reported on the jack */
अटल स्थिर पूर्णांक ts3a227e_buttons[] = अणु
	SND_JACK_BTN_0,
	SND_JACK_BTN_1,
	SND_JACK_BTN_2,
	SND_JACK_BTN_3,
पूर्ण;

#घोषणा TS3A227E_NUM_BUTTONS 4
#घोषणा TS3A227E_JACK_MASK (SND_JACK_HEADPHONE | \
			    SND_JACK_MICROPHONE | \
			    SND_JACK_BTN_0 | \
			    SND_JACK_BTN_1 | \
			    SND_JACK_BTN_2 | \
			    SND_JACK_BTN_3)

/* TS3A227E रेजिस्टरs */
#घोषणा TS3A227E_REG_DEVICE_ID		0x00
#घोषणा TS3A227E_REG_INTERRUPT		0x01
#घोषणा TS3A227E_REG_KP_INTERRUPT	0x02
#घोषणा TS3A227E_REG_INTERRUPT_DISABLE	0x03
#घोषणा TS3A227E_REG_SETTING_1		0x04
#घोषणा TS3A227E_REG_SETTING_2		0x05
#घोषणा TS3A227E_REG_SETTING_3		0x06
#घोषणा TS3A227E_REG_SWITCH_CONTROL_1	0x07
#घोषणा TS3A227E_REG_SWITCH_CONTROL_2	0x08
#घोषणा TS3A227E_REG_SWITCH_STATUS_1	0x09
#घोषणा TS3A227E_REG_SWITCH_STATUS_2	0x0a
#घोषणा TS3A227E_REG_ACCESSORY_STATUS	0x0b
#घोषणा TS3A227E_REG_ADC_OUTPUT		0x0c
#घोषणा TS3A227E_REG_KP_THRESHOLD_1	0x0d
#घोषणा TS3A227E_REG_KP_THRESHOLD_2	0x0e
#घोषणा TS3A227E_REG_KP_THRESHOLD_3	0x0f

/* TS3A227E_REG_INTERRUPT 0x01 */
#घोषणा INS_REM_EVENT 0x01
#घोषणा DETECTION_COMPLETE_EVENT 0x02

/* TS3A227E_REG_KP_INTERRUPT 0x02 */
#घोषणा PRESS_MASK(idx) (0x01 << (2 * (idx)))
#घोषणा RELEASE_MASK(idx) (0x02 << (2 * (idx)))

/* TS3A227E_REG_INTERRUPT_DISABLE 0x03 */
#घोषणा INS_REM_INT_DISABLE 0x01
#घोषणा DETECTION_COMPLETE_INT_DISABLE 0x02
#घोषणा ADC_COMPLETE_INT_DISABLE 0x04
#घोषणा INTB_DISABLE 0x08

/* TS3A227E_REG_SETTING_2 0x05 */
#घोषणा KP_ENABLE 0x04

/* TS3A227E_REG_SETTING_3 0x06 */
#घोषणा MICBIAS_SETTING_SFT (3)
#घोषणा MICBIAS_SETTING_MASK (0x7 << MICBIAS_SETTING_SFT)

/* TS3A227E_REG_ACCESSORY_STATUS  0x0b */
#घोषणा TYPE_3_POLE 0x01
#घोषणा TYPE_4_POLE_OMTP 0x02
#घोषणा TYPE_4_POLE_STANDARD 0x04
#घोषणा JACK_INSERTED 0x08
#घोषणा EITHER_MIC_MASK (TYPE_4_POLE_OMTP | TYPE_4_POLE_STANDARD)

अटल स्थिर काष्ठा reg_शेष ts3a227e_reg_शेषs[] = अणु
	अणु TS3A227E_REG_DEVICE_ID, 0x10 पूर्ण,
	अणु TS3A227E_REG_INTERRUPT, 0x00 पूर्ण,
	अणु TS3A227E_REG_KP_INTERRUPT, 0x00 पूर्ण,
	अणु TS3A227E_REG_INTERRUPT_DISABLE, 0x08 पूर्ण,
	अणु TS3A227E_REG_SETTING_1, 0x23 पूर्ण,
	अणु TS3A227E_REG_SETTING_2, 0x00 पूर्ण,
	अणु TS3A227E_REG_SETTING_3, 0x0e पूर्ण,
	अणु TS3A227E_REG_SWITCH_CONTROL_1, 0x00 पूर्ण,
	अणु TS3A227E_REG_SWITCH_CONTROL_2, 0x00 पूर्ण,
	अणु TS3A227E_REG_SWITCH_STATUS_1, 0x0c पूर्ण,
	अणु TS3A227E_REG_SWITCH_STATUS_2, 0x00 पूर्ण,
	अणु TS3A227E_REG_ACCESSORY_STATUS, 0x00 पूर्ण,
	अणु TS3A227E_REG_ADC_OUTPUT, 0x00 पूर्ण,
	अणु TS3A227E_REG_KP_THRESHOLD_1, 0x20 पूर्ण,
	अणु TS3A227E_REG_KP_THRESHOLD_2, 0x40 पूर्ण,
	अणु TS3A227E_REG_KP_THRESHOLD_3, 0x68 पूर्ण,
पूर्ण;

अटल bool ts3a227e_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TS3A227E_REG_DEVICE_ID ... TS3A227E_REG_KP_THRESHOLD_3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ts3a227e_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TS3A227E_REG_INTERRUPT_DISABLE ... TS3A227E_REG_SWITCH_CONTROL_2:
	हाल TS3A227E_REG_KP_THRESHOLD_1 ... TS3A227E_REG_KP_THRESHOLD_3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ts3a227e_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TS3A227E_REG_INTERRUPT ... TS3A227E_REG_INTERRUPT_DISABLE:
	हाल TS3A227E_REG_SETTING_2:
	हाल TS3A227E_REG_SWITCH_STATUS_1 ... TS3A227E_REG_ADC_OUTPUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम ts3a227e_jack_report(काष्ठा ts3a227e *ts3a227e)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक report = 0;

	अगर (!ts3a227e->jack)
		वापस;

	अगर (ts3a227e->plugged)
		report = SND_JACK_HEADPHONE;
	अगर (ts3a227e->mic_present)
		report |= SND_JACK_MICROPHONE;
	क्रम (i = 0; i < TS3A227E_NUM_BUTTONS; i++) अणु
		अगर (ts3a227e->buttons_held & (1 << i))
			report |= ts3a227e_buttons[i];
	पूर्ण
	snd_soc_jack_report(ts3a227e->jack, report, TS3A227E_JACK_MASK);
पूर्ण

अटल व्योम ts3a227e_new_jack_state(काष्ठा ts3a227e *ts3a227e, अचिन्हित acc_reg)
अणु
	bool plugged, mic_present;

	plugged = !!(acc_reg & JACK_INSERTED);
	mic_present = plugged && !!(acc_reg & EITHER_MIC_MASK);

	ts3a227e->plugged = plugged;

	अगर (mic_present != ts3a227e->mic_present) अणु
		ts3a227e->mic_present = mic_present;
		ts3a227e->buttons_held = 0;
		अगर (mic_present) अणु
			/* Enable key press detection. */
			regmap_update_bits(ts3a227e->regmap,
					   TS3A227E_REG_SETTING_2,
					   KP_ENABLE, KP_ENABLE);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t ts3a227e_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ts3a227e *ts3a227e = (काष्ठा ts3a227e *)data;
	काष्ठा regmap *regmap = ts3a227e->regmap;
	अचिन्हित पूर्णांक पूर्णांक_reg, kp_पूर्णांक_reg, acc_reg, i;
	काष्ठा device *dev = ts3a227e->dev;
	पूर्णांक ret;

	/* Check क्रम plug/unplug. */
	ret = regmap_पढ़ो(regmap, TS3A227E_REG_INTERRUPT, &पूर्णांक_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to clear interrupt ret=%d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	अगर (पूर्णांक_reg & (DETECTION_COMPLETE_EVENT | INS_REM_EVENT)) अणु
		regmap_पढ़ो(regmap, TS3A227E_REG_ACCESSORY_STATUS, &acc_reg);
		ts3a227e_new_jack_state(ts3a227e, acc_reg);
	पूर्ण

	/* Report any key events. */
	ret = regmap_पढ़ो(regmap, TS3A227E_REG_KP_INTERRUPT, &kp_पूर्णांक_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to clear key interrupt ret=%d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	क्रम (i = 0; i < TS3A227E_NUM_BUTTONS; i++) अणु
		अगर (kp_पूर्णांक_reg & PRESS_MASK(i))
			ts3a227e->buttons_held |= (1 << i);
		अगर (kp_पूर्णांक_reg & RELEASE_MASK(i))
			ts3a227e->buttons_held &= ~(1 << i);
	पूर्ण

	ts3a227e_jack_report(ts3a227e);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ts3a227e_enable_jack_detect - Specअगरy a jack क्रम event reporting
 *
 * @component:  component to रेजिस्टर the jack with
 * @jack: jack to use to report headset and button events on
 *
 * After this function has been called the headset insert/हटाओ and button
 * events 0-3 will be routed to the given jack.  Jack can be null to stop
 * reporting.
 */
पूर्णांक ts3a227e_enable_jack_detect(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा ts3a227e *ts3a227e = snd_soc_component_get_drvdata(component);

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	ts3a227e->jack = jack;
	ts3a227e_jack_report(ts3a227e);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ts3a227e_enable_jack_detect);

अटल काष्ठा snd_soc_component_driver ts3a227e_soc_driver;

अटल स्थिर काष्ठा regmap_config ts3a227e_regmap_config = अणु
	.val_bits = 8,
	.reg_bits = 8,

	.max_रेजिस्टर = TS3A227E_REG_KP_THRESHOLD_3,
	.पढ़ोable_reg = ts3a227e_पढ़ोable_reg,
	.ग_लिखोable_reg = ts3a227e_ग_लिखोable_reg,
	.अस्थिर_reg = ts3a227e_अस्थिर_reg,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = ts3a227e_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ts3a227e_reg_शेषs),
पूर्ण;

अटल पूर्णांक ts3a227e_parse_device_property(काष्ठा ts3a227e *ts3a227e,
				काष्ठा device *dev)
अणु
	u32 micbias;
	पूर्णांक err;

	err = device_property_पढ़ो_u32(dev, "ti,micbias", &micbias);
	अगर (!err) अणु
		regmap_update_bits(ts3a227e->regmap, TS3A227E_REG_SETTING_3,
			MICBIAS_SETTING_MASK,
			(micbias & 0x07) << MICBIAS_SETTING_SFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ts3a227e_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ts3a227e *ts3a227e;
	काष्ठा device *dev = &i2c->dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक acc_reg;

	ts3a227e = devm_kzalloc(&i2c->dev, माप(*ts3a227e), GFP_KERNEL);
	अगर (ts3a227e == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, ts3a227e);
	ts3a227e->dev = dev;
	ts3a227e->irq = i2c->irq;

	ts3a227e->regmap = devm_regmap_init_i2c(i2c, &ts3a227e_regmap_config);
	अगर (IS_ERR(ts3a227e->regmap))
		वापस PTR_ERR(ts3a227e->regmap);

	ret = ts3a227e_parse_device_property(ts3a227e, dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to parse device property: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, i2c->irq, शून्य, ts3a227e_पूर्णांकerrupt,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"TS3A227E", ts3a227e);
	अगर (ret) अणु
		dev_err(dev, "Cannot request irq %d (%d)\n", i2c->irq, ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &ts3a227e_soc_driver,
					      शून्य, 0);
	अगर (ret)
		वापस ret;

	/* Enable पूर्णांकerrupts except क्रम ADC complete. */
	regmap_update_bits(ts3a227e->regmap, TS3A227E_REG_INTERRUPT_DISABLE,
			   INTB_DISABLE | ADC_COMPLETE_INT_DISABLE,
			   ADC_COMPLETE_INT_DISABLE);

	/* Read jack status because chip might not trigger पूर्णांकerrupt at boot. */
	regmap_पढ़ो(ts3a227e->regmap, TS3A227E_REG_ACCESSORY_STATUS, &acc_reg);
	ts3a227e_new_jack_state(ts3a227e, acc_reg);
	ts3a227e_jack_report(ts3a227e);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ts3a227e_suspend(काष्ठा device *dev)
अणु
	काष्ठा ts3a227e *ts3a227e = dev_get_drvdata(dev);

	dev_dbg(ts3a227e->dev, "suspend disable irq\n");
	disable_irq(ts3a227e->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक ts3a227e_resume(काष्ठा device *dev)
अणु
	काष्ठा ts3a227e *ts3a227e = dev_get_drvdata(dev);

	dev_dbg(ts3a227e->dev, "resume enable irq\n");
	enable_irq(ts3a227e->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops ts3a227e_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ts3a227e_suspend, ts3a227e_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ts3a227e_i2c_ids[] = अणु
	अणु "ts3a227e", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ts3a227e_i2c_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ts3a227e_of_match[] = अणु
	अणु .compatible = "ti,ts3a227e", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ts3a227e_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा acpi_device_id ts3a227e_acpi_match[] = अणु
	अणु "104C227E", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ts3a227e_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ts3a227e_driver = अणु
	.driver = अणु
		.name = "ts3a227e",
		.pm = &ts3a227e_pm,
		.of_match_table = of_match_ptr(ts3a227e_of_match),
		.acpi_match_table = ACPI_PTR(ts3a227e_acpi_match),
	पूर्ण,
	.probe = ts3a227e_i2c_probe,
	.id_table = ts3a227e_i2c_ids,
पूर्ण;
module_i2c_driver(ts3a227e_driver);

MODULE_DESCRIPTION("ASoC ts3a227e driver");
MODULE_AUTHOR("Dylan Reid <dgreid@chromium.org>");
MODULE_LICENSE("GPL v2");
