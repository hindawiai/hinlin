<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	elanfreq:	cpufreq driver क्रम the AMD ELAN family
 *
 *	(c) Copyright 2002 Robert Schwebel <r.schwebel@pengutronix.de>
 *
 *	Parts of this code are (c) Sven Geggus <sven@geggus.net>
 *
 *      All Rights Reserved.
 *
 *	2002-02-13: - initial revision क्रम 2.4.18-pre9 by Robert Schwebel
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <linux/delay.h>
#समावेश <linux/cpufreq.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/msr.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>

#घोषणा REG_CSCIR 0x22		/* Chip Setup and Control Index Register    */
#घोषणा REG_CSCDR 0x23		/* Chip Setup and Control Data  Register    */

/* Module parameter */
अटल पूर्णांक max_freq;

काष्ठा s_elan_multiplier अणु
	पूर्णांक घड़ी;		/* frequency in kHz                         */
	पूर्णांक val40h;		/* PMU Force Mode रेजिस्टर                  */
	पूर्णांक val80h;		/* CPU Clock Speed Register                 */
पूर्ण;

/*
 * It is important that the frequencies
 * are listed in ascending order here!
 */
अटल काष्ठा s_elan_multiplier elan_multiplier[] = अणु
	अणु1000,	0x02,	0x18पूर्ण,
	अणु2000,	0x02,	0x10पूर्ण,
	अणु4000,	0x02,	0x08पूर्ण,
	अणु8000,	0x00,	0x00पूर्ण,
	अणु16000,	0x00,	0x02पूर्ण,
	अणु33000,	0x00,	0x04पूर्ण,
	अणु66000,	0x01,	0x04पूर्ण,
	अणु99000,	0x01,	0x05पूर्ण
पूर्ण;

अटल काष्ठा cpufreq_frequency_table elanfreq_table[] = अणु
	अणु0, 0,	1000पूर्ण,
	अणु0, 1,	2000पूर्ण,
	अणु0, 2,	4000पूर्ण,
	अणु0, 3,	8000पूर्ण,
	अणु0, 4,	16000पूर्ण,
	अणु0, 5,	33000पूर्ण,
	अणु0, 6,	66000पूर्ण,
	अणु0, 7,	99000पूर्ण,
	अणु0, 0,	CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;


/**
 *	elanfreq_get_cpu_frequency: determine current cpu speed
 *
 *	Finds out at which frequency the CPU of the Elan SOC runs
 *	at the moment. Frequencies from 1 to 33 MHz are generated
 *	the normal way, 66 and 99 MHz are called "Hyperspeed Mode"
 *	and have the rest of the chip running with 33 MHz.
 */

अटल अचिन्हित पूर्णांक elanfreq_get_cpu_frequency(अचिन्हित पूर्णांक cpu)
अणु
	u8 घड़ीspeed_reg;    /* Clock Speed Register */

	local_irq_disable();
	outb_p(0x80, REG_CSCIR);
	घड़ीspeed_reg = inb_p(REG_CSCDR);
	local_irq_enable();

	अगर ((घड़ीspeed_reg & 0xE0) == 0xE0)
		वापस 0;

	/* Are we in CPU घड़ी multiplied mode (66/99 MHz)? */
	अगर ((घड़ीspeed_reg & 0xE0) == 0xC0) अणु
		अगर ((घड़ीspeed_reg & 0x01) == 0)
			वापस 66000;
		अन्यथा
			वापस 99000;
	पूर्ण

	/* 33 MHz is not 32 MHz... */
	अगर ((घड़ीspeed_reg & 0xE0) == 0xA0)
		वापस 33000;

	वापस (1<<((घड़ीspeed_reg & 0xE0) >> 5)) * 1000;
पूर्ण


अटल पूर्णांक elanfreq_target(काष्ठा cpufreq_policy *policy,
			    अचिन्हित पूर्णांक state)
अणु
	/*
	 * Access to the Elan's पूर्णांकernal रेजिस्टरs is indexed via
	 * 0x22: Chip Setup & Control Register Index Register (CSCI)
	 * 0x23: Chip Setup & Control Register Data  Register (CSCD)
	 *
	 */

	/*
	 * 0x40 is the Power Management Unit's Force Mode Register.
	 * Bit 6 enables Hyperspeed Mode (66/100 MHz core frequency)
	 */

	local_irq_disable();
	outb_p(0x40, REG_CSCIR);		/* Disable hyperspeed mode */
	outb_p(0x00, REG_CSCDR);
	local_irq_enable();		/* रुको till पूर्णांकernal pipelines and */
	udelay(1000);			/* buffers have cleaned up          */

	local_irq_disable();

	/* now, set the CPU घड़ी speed रेजिस्टर (0x80) */
	outb_p(0x80, REG_CSCIR);
	outb_p(elan_multiplier[state].val80h, REG_CSCDR);

	/* now, the hyperspeed bit in PMU Force Mode Register (0x40) */
	outb_p(0x40, REG_CSCIR);
	outb_p(elan_multiplier[state].val40h, REG_CSCDR);
	udelay(10000);
	local_irq_enable();

	वापस 0;
पूर्ण
/*
 *	Module init and निकास code
 */

अटल पूर्णांक elanfreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	काष्ठा cpufreq_frequency_table *pos;

	/* capability check */
	अगर ((c->x86_venकरोr != X86_VENDOR_AMD) ||
	    (c->x86 != 4) || (c->x86_model != 10))
		वापस -ENODEV;

	/* max freq */
	अगर (!max_freq)
		max_freq = elanfreq_get_cpu_frequency(0);

	/* table init */
	cpufreq_क्रम_each_entry(pos, elanfreq_table)
		अगर (pos->frequency > max_freq)
			pos->frequency = CPUFREQ_ENTRY_INVALID;

	policy->freq_table = elanfreq_table;
	वापस 0;
पूर्ण


#अगर_अघोषित MODULE
/**
 * elanfreq_setup - elanfreq command line parameter parsing
 *
 * elanfreq command line parameter.  Use:
 *  elanfreq=66000
 * to set the maximum CPU frequency to 66 MHz. Note that in
 * हाल you करो not give this boot parameter, the maximum
 * frequency will fall back to _current_ CPU frequency which
 * might be lower. If you build this as a module, use the
 * max_freq module parameter instead.
 */
अटल पूर्णांक __init elanfreq_setup(अक्षर *str)
अणु
	max_freq = simple_म_से_अदीर्घ(str, &str, 0);
	pr_warn("You're using the deprecated elanfreq command line option. Use elanfreq.max_freq instead, please!\n");
	वापस 1;
पूर्ण
__setup("elanfreq=", elanfreq_setup);
#पूर्ण_अगर


अटल काष्ठा cpufreq_driver elanfreq_driver = अणु
	.get		= elanfreq_get_cpu_frequency,
	.flags		= CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= elanfreq_target,
	.init		= elanfreq_cpu_init,
	.name		= "elanfreq",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id elan_id[] = अणु
	X86_MATCH_VENDOR_FAM_MODEL(AMD, 4, 10, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, elan_id);

अटल पूर्णांक __init elanfreq_init(व्योम)
अणु
	अगर (!x86_match_cpu(elan_id))
		वापस -ENODEV;
	वापस cpufreq_रेजिस्टर_driver(&elanfreq_driver);
पूर्ण


अटल व्योम __निकास elanfreq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&elanfreq_driver);
पूर्ण


module_param(max_freq, पूर्णांक, 0444);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert Schwebel <r.schwebel@pengutronix.de>, "
		"Sven Geggus <sven@geggus.net>");
MODULE_DESCRIPTION("cpufreq driver for AMD's Elan CPUs");

module_init(elanfreq_init);
module_निकास(elanfreq_निकास);
