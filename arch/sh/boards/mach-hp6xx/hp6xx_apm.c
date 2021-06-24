<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bios-less APM driver क्रम hp680
 *
 * Copyright 2005 (c) Andriy Skulysh <askulysh@gmail.com>
 * Copyright 2008 (c) Kristoffer Ericson <kristoffer.ericson@gmail.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/apm-emulation.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/adc.h>
#समावेश <mach/hp6xx.h>

/* percentage values */
#घोषणा APM_CRITICAL			10
#घोषणा APM_LOW				30

/* resonably sane values */
#घोषणा HP680_BATTERY_MAX		898
#घोषणा HP680_BATTERY_MIN		486
#घोषणा HP680_BATTERY_AC_ON		1023

#घोषणा MODNAME "hp6x0_apm"

#घोषणा PGDR	0xa400012c

अटल व्योम hp6x0_apm_get_घातer_status(काष्ठा apm_घातer_info *info)
अणु
	पूर्णांक battery, backup, अक्षरging, percentage;
	u8 pgdr;

	battery		= adc_single(ADC_CHANNEL_BATTERY);
	backup		= adc_single(ADC_CHANNEL_BACKUP);
	अक्षरging	= adc_single(ADC_CHANNEL_CHARGE);

	percentage = 100 * (battery - HP680_BATTERY_MIN) /
			   (HP680_BATTERY_MAX - HP680_BATTERY_MIN);

	/* % of full battery */
	info->battery_lअगरe = percentage;

	/* We want our estimates in minutes */
	info->units = 0;

	/* Extremely(!!) rough estimate, we will replace this with a datalist later on */
	info->समय = (2 * battery);

	info->ac_line_status = (battery > HP680_BATTERY_AC_ON) ?
			 APM_AC_ONLINE : APM_AC_OFFLINE;

	pgdr = __raw_पढ़ोb(PGDR);
	अगर (pgdr & PGDR_MAIN_BATTERY_OUT) अणु
		info->battery_status	= APM_BATTERY_STATUS_NOT_PRESENT;
		info->battery_flag	= 0x80;
	पूर्ण अन्यथा अगर (अक्षरging < 8) अणु
		info->battery_status	= APM_BATTERY_STATUS_CHARGING;
		info->battery_flag	= 0x08;
		info->ac_line_status	= 0x01;
	पूर्ण अन्यथा अगर (percentage <= APM_CRITICAL) अणु
		info->battery_status	= APM_BATTERY_STATUS_CRITICAL;
		info->battery_flag	= 0x04;
	पूर्ण अन्यथा अगर (percentage <= APM_LOW) अणु
		info->battery_status	= APM_BATTERY_STATUS_LOW;
		info->battery_flag	= 0x02;
	पूर्ण अन्यथा अणु
		info->battery_status	= APM_BATTERY_STATUS_HIGH;
		info->battery_flag	= 0x01;
	पूर्ण
पूर्ण

अटल irqवापस_t hp6x0_apm_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	अगर (!APM_DISABLED)
		apm_queue_event(APM_USER_SUSPEND);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init hp6x0_apm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = request_irq(HP680_BTN_IRQ, hp6x0_apm_पूर्णांकerrupt,
			  0, MODNAME, शून्य);
	अगर (unlikely(ret < 0)) अणु
		prपूर्णांकk(KERN_ERR MODNAME ": IRQ %d request failed\n",
		       HP680_BTN_IRQ);
		वापस ret;
	पूर्ण

	apm_get_घातer_status = hp6x0_apm_get_घातer_status;

	वापस ret;
पूर्ण

अटल व्योम __निकास hp6x0_apm_निकास(व्योम)
अणु
	मुक्त_irq(HP680_BTN_IRQ, 0);
पूर्ण

module_init(hp6x0_apm_init);
module_निकास(hp6x0_apm_निकास);

MODULE_AUTHOR("Adriy Skulysh");
MODULE_DESCRIPTION("hp6xx Advanced Power Management");
MODULE_LICENSE("GPL");
