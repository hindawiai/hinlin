<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AB8500 प्रणाली control driver
 *
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Mattias Nilsson <mattias.i.nilsson@stericsson.com> क्रम ST Ericsson.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/reboot.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/mfd/abx500/ab8500-sysctrl.h>

/* RtcCtrl bits */
#घोषणा AB8500_ALARM_MIN_LOW  0x08
#घोषणा AB8500_ALARM_MIN_MID 0x09
#घोषणा RTC_CTRL 0x0B
#घोषणा RTC_ALARM_ENABLE 0x4

अटल काष्ठा device *sysctrl_dev;

अटल व्योम ab8500_घातer_off(व्योम)
अणु
	sigset_t old;
	sigset_t all;
	अटल स्थिर अक्षर * स्थिर pss[] = अणु"ab8500_ac", "pm2301", "ab8500_usb"पूर्ण;
	पूर्णांक i;
	bool अक्षरger_present = false;
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *psy;
	पूर्णांक ret;

	अगर (sysctrl_dev == शून्य) अणु
		pr_err("%s: sysctrl not initialized\n", __func__);
		वापस;
	पूर्ण

	/*
	 * If we have a अक्षरger connected and we're घातering off,
	 * reboot पूर्णांकo अक्षरge-only mode.
	 */

	क्रम (i = 0; i < ARRAY_SIZE(pss); i++) अणु
		psy = घातer_supply_get_by_name(pss[i]);
		अगर (!psy)
			जारी;

		ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_ONLINE,
				&val);
		घातer_supply_put(psy);

		अगर (!ret && val.पूर्णांकval) अणु
			अक्षरger_present = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!अक्षरger_present)
		जाओ shutकरोwn;

	/* Check अगर battery is known */
	psy = घातer_supply_get_by_name("ab8500_btemp");
	अगर (psy) अणु
		ret = घातer_supply_get_property(psy,
				POWER_SUPPLY_PROP_TECHNOLOGY, &val);
		अगर (!ret && val.पूर्णांकval != POWER_SUPPLY_TECHNOLOGY_UNKNOWN) अणु
			pr_info("Charger '%s' is connected with known battery",
				pss[i]);
			pr_info(" - Rebooting.\n");
			machine_restart("charging");
		पूर्ण
		घातer_supply_put(psy);
	पूर्ण

shutकरोwn:
	sigfillset(&all);

	अगर (!sigprocmask(SIG_BLOCK, &all, &old)) अणु
		(व्योम)ab8500_sysctrl_set(AB8500_STW4500CTRL1,
					 AB8500_STW4500CTRL1_SWOFF |
					 AB8500_STW4500CTRL1_SWRESET4500N);
		(व्योम)sigprocmask(SIG_SETMASK, &old, शून्य);
	पूर्ण
पूर्ण

अटल अंतरभूत bool valid_bank(u8 bank)
अणु
	वापस ((bank == AB8500_SYS_CTRL1_BLOCK) ||
		(bank == AB8500_SYS_CTRL2_BLOCK));
पूर्ण

पूर्णांक ab8500_sysctrl_पढ़ो(u16 reg, u8 *value)
अणु
	u8 bank;

	अगर (sysctrl_dev == शून्य)
		वापस -EPROBE_DEFER;

	bank = (reg >> 8);
	अगर (!valid_bank(bank))
		वापस -EINVAL;

	वापस abx500_get_रेजिस्टर_पूर्णांकerruptible(sysctrl_dev, bank,
		(u8)(reg & 0xFF), value);
पूर्ण
EXPORT_SYMBOL(ab8500_sysctrl_पढ़ो);

पूर्णांक ab8500_sysctrl_ग_लिखो(u16 reg, u8 mask, u8 value)
अणु
	u8 bank;

	अगर (sysctrl_dev == शून्य)
		वापस -EPROBE_DEFER;

	bank = (reg >> 8);
	अगर (!valid_bank(bank)) अणु
		pr_err("invalid bank\n");
		वापस -EINVAL;
	पूर्ण

	वापस abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(sysctrl_dev, bank,
		(u8)(reg & 0xFF), mask, value);
पूर्ण
EXPORT_SYMBOL(ab8500_sysctrl_ग_लिखो);

अटल पूर्णांक ab8500_sysctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	sysctrl_dev = &pdev->dev;

	अगर (!pm_घातer_off)
		pm_घातer_off = ab8500_घातer_off;

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_sysctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sysctrl_dev = शून्य;

	अगर (pm_घातer_off == ab8500_घातer_off)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ab8500_sysctrl_match[] = अणु
	अणु .compatible = "stericsson,ab8500-sysctrl", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ab8500_sysctrl_driver = अणु
	.driver = अणु
		.name = "ab8500-sysctrl",
		.of_match_table = ab8500_sysctrl_match,
	पूर्ण,
	.probe = ab8500_sysctrl_probe,
	.हटाओ = ab8500_sysctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init ab8500_sysctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ab8500_sysctrl_driver);
पूर्ण
arch_initcall(ab8500_sysctrl_init);
