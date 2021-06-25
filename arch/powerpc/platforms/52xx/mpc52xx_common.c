<शैली गुरु>
/*
 *
 * Utility functions क्रम the Freescale MPC52xx.
 *
 * Copyright (C) 2006 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#अघोषित DEBUG

#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/export.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpc52xx.h>

/* MPC5200 device tree match tables */
अटल स्थिर काष्ठा of_device_id mpc52xx_xlb_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-xlb", पूर्ण,
	अणु .compatible = "mpc5200-xlb", पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा of_device_id mpc52xx_bus_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-immr", पूर्ण,
	अणु .compatible = "fsl,mpc5200b-immr", पूर्ण,
	अणु .compatible = "simple-bus", पूर्ण,

	/* depreciated matches; shouldn't be used in new device trees */
	अणु .compatible = "fsl,lpb", पूर्ण,
	अणु .type = "builtin", .compatible = "mpc5200", पूर्ण, /* efika */
	अणु .type = "soc", .compatible = "mpc5200", पूर्ण, /* lite5200 */
	अणुपूर्ण
पूर्ण;

/*
 * This variable is mapped in mpc52xx_map_wdt() and used in mpc52xx_restart().
 * Permanent mapping is required because mpc52xx_restart() can be called
 * from पूर्णांकerrupt context जबतक node mapping (which calls ioremap())
 * cannot be used at such poपूर्णांक.
 */
अटल DEFINE_SPINLOCK(mpc52xx_lock);
अटल काष्ठा mpc52xx_gpt __iomem *mpc52xx_wdt;
अटल काष्ठा mpc52xx_cdm __iomem *mpc52xx_cdm;

/*
 * Configure the XLB arbiter settings to match what Linux expects.
 */
व्योम __init
mpc5200_setup_xlb_arbiter(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा mpc52xx_xlb  __iomem *xlb;

	np = of_find_matching_node(शून्य, mpc52xx_xlb_ids);
	xlb = of_iomap(np, 0);
	of_node_put(np);
	अगर (!xlb) अणु
		prपूर्णांकk(KERN_ERR __खाता__ ": "
			"Error mapping XLB in mpc52xx_setup_cpu(). "
			"Expect some abnormal behavior\n");
		वापस;
	पूर्ण

	/* Configure the XLB Arbiter priorities */
	out_be32(&xlb->master_pri_enable, 0xff);
	out_be32(&xlb->master_priority, 0x11111111);

	/*
	 * Disable XLB pipelining
	 * (cfr errate 292. We could करो this only just beक्रमe ATA PIO
	 *  transaction and re-enable it afterwards ...)
	 * Not needed on MPC5200B.
	 */
	अगर ((mfspr(SPRN_SVR) & MPC5200_SVR_MASK) == MPC5200_SVR)
		out_be32(&xlb->config, in_be32(&xlb->config) | MPC52xx_XLB_CFG_PLDIS);

	iounmap(xlb);
पूर्ण

/*
 * This variable is mapped in mpc52xx_map_common_devices and
 * used in mpc5200_psc_ac97_gpio_reset().
 */
अटल DEFINE_SPINLOCK(gpio_lock);
काष्ठा mpc52xx_gpio __iomem *simple_gpio;
काष्ठा mpc52xx_gpio_wkup __iomem *wkup_gpio;

/**
 * mpc52xx_declare_of_platक्रमm_devices: रेजिस्टर पूर्णांकernal devices and children
 *					of the localplus bus to the of_platक्रमm
 *					bus.
 */
व्योम __init mpc52xx_declare_of_platक्रमm_devices(व्योम)
अणु
	/* Find all the 'platform' devices and रेजिस्टर them. */
	अगर (of_platक्रमm_populate(शून्य, mpc52xx_bus_ids, शून्य, शून्य))
		pr_err(__खाता__ ": Error while populating devices from DT\n");
पूर्ण

/*
 * match tables used by mpc52xx_map_common_devices()
 */
अटल स्थिर काष्ठा of_device_id mpc52xx_gpt_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-gpt", पूर्ण,
	अणु .compatible = "mpc5200-gpt", पूर्ण, /* old */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा of_device_id mpc52xx_cdm_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-cdm", पूर्ण,
	अणु .compatible = "mpc5200-cdm", पूर्ण, /* old */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा of_device_id mpc52xx_gpio_simple[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-gpio", पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा of_device_id mpc52xx_gpio_wkup[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-gpio-wkup", पूर्ण,
	अणुपूर्ण
पूर्ण;


/**
 * mpc52xx_map_common_devices: iomap devices required by common code
 */
व्योम __init
mpc52xx_map_common_devices(व्योम)
अणु
	काष्ठा device_node *np;

	/* mpc52xx_wdt is mapped here and used in mpc52xx_restart,
	 * possibly from a पूर्णांकerrupt context. wdt is only implement
	 * on a gpt0, so check has-wdt property beक्रमe mapping.
	 */
	क्रम_each_matching_node(np, mpc52xx_gpt_ids) अणु
		अगर (of_get_property(np, "fsl,has-wdt", शून्य) ||
		    of_get_property(np, "has-wdt", शून्य)) अणु
			mpc52xx_wdt = of_iomap(np, 0);
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Clock Distribution Module, used by PSC घड़ी setting function */
	np = of_find_matching_node(शून्य, mpc52xx_cdm_ids);
	mpc52xx_cdm = of_iomap(np, 0);
	of_node_put(np);

	/* simple_gpio रेजिस्टरs */
	np = of_find_matching_node(शून्य, mpc52xx_gpio_simple);
	simple_gpio = of_iomap(np, 0);
	of_node_put(np);

	/* wkup_gpio रेजिस्टरs */
	np = of_find_matching_node(शून्य, mpc52xx_gpio_wkup);
	wkup_gpio = of_iomap(np, 0);
	of_node_put(np);
पूर्ण

/**
 * mpc52xx_set_psc_clkभाग: Set घड़ी भागider in the CDM क्रम PSC ports
 *
 * @psc_id: id of psc port; must be 1,2,3 or 6
 * @clkभाग: घड़ी भागider value to put पूर्णांकo CDM PSC रेजिस्टर.
 */
पूर्णांक mpc52xx_set_psc_clkभाग(पूर्णांक psc_id, पूर्णांक clkभाग)
अणु
	अचिन्हित दीर्घ flags;
	u16 __iomem *reg;
	u32 val;
	u32 mask;
	u32 mclken_भाग;

	अगर (!mpc52xx_cdm)
		वापस -ENODEV;

	mclken_भाग = 0x8000 | (clkभाग & 0x1FF);
	चयन (psc_id) अणु
	हाल 1: reg = &mpc52xx_cdm->mclken_भाग_psc1; mask = 0x20; अवरोध;
	हाल 2: reg = &mpc52xx_cdm->mclken_भाग_psc2; mask = 0x40; अवरोध;
	हाल 3: reg = &mpc52xx_cdm->mclken_भाग_psc3; mask = 0x80; अवरोध;
	हाल 6: reg = &mpc52xx_cdm->mclken_भाग_psc6; mask = 0x10; अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	/* Set the rate and enable the घड़ी */
	spin_lock_irqsave(&mpc52xx_lock, flags);
	out_be16(reg, mclken_भाग);
	val = in_be32(&mpc52xx_cdm->clk_enables);
	out_be32(&mpc52xx_cdm->clk_enables, val | mask);
	spin_unlock_irqrestore(&mpc52xx_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpc52xx_set_psc_clkभाग);

/**
 * mpc52xx_get_xtal_freq - Get SYS_XTAL_IN frequency क्रम a device
 *
 * @node: device node
 *
 * Returns the frequency of the बाह्यal oscillator घड़ी connected
 * to the SYS_XTAL_IN pin, or 0 अगर it cannot be determined.
 */
अचिन्हित पूर्णांक mpc52xx_get_xtal_freq(काष्ठा device_node *node)
अणु
	u32 val;
	अचिन्हित पूर्णांक freq;

	अगर (!mpc52xx_cdm)
		वापस 0;

	freq = mpc5xxx_get_bus_frequency(node);
	अगर (!freq)
		वापस 0;

	अगर (in_8(&mpc52xx_cdm->ipb_clk_sel) & 0x1)
		freq *= 2;

	val  = in_be32(&mpc52xx_cdm->rstcfg);
	अगर (val & (1 << 5))
		freq *= 8;
	अन्यथा
		freq *= 4;
	अगर (val & (1 << 6))
		freq /= 12;
	अन्यथा
		freq /= 16;

	वापस freq;
पूर्ण
EXPORT_SYMBOL(mpc52xx_get_xtal_freq);

/**
 * mpc52xx_restart: ppc_md->restart hook क्रम mpc5200 using the watchकरोg समयr
 */
व्योम __noवापस mpc52xx_restart(अक्षर *cmd)
अणु
	local_irq_disable();

	/* Turn on the watchकरोg and रुको क्रम it to expire.
	 * It effectively करोes a reset. */
	अगर (mpc52xx_wdt) अणु
		out_be32(&mpc52xx_wdt->mode, 0x00000000);
		out_be32(&mpc52xx_wdt->count, 0x000000ff);
		out_be32(&mpc52xx_wdt->mode, 0x00009004);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR __खाता__ ": "
			"mpc52xx_restart: Can't access wdt. "
			"Restart impossible, system halted.\n");

	जबतक (1);
पूर्ण

#घोषणा PSC1_RESET     0x1
#घोषणा PSC1_SYNC      0x4
#घोषणा PSC1_SDATA_OUT 0x1
#घोषणा PSC2_RESET     0x2
#घोषणा PSC2_SYNC      (0x4<<4)
#घोषणा PSC2_SDATA_OUT (0x1<<4)
#घोषणा MPC52xx_GPIO_PSC1_MASK 0x7
#घोषणा MPC52xx_GPIO_PSC2_MASK (0x7<<4)

/**
 * mpc5200_psc_ac97_gpio_reset: Use gpio pins to reset the ac97 bus
 *
 * @psc: psc number to reset (only psc 1 and 2 support ac97)
 */
पूर्णांक mpc5200_psc_ac97_gpio_reset(पूर्णांक psc_number)
अणु
	अचिन्हित दीर्घ flags;
	u32 gpio;
	u32 mux;
	पूर्णांक out;
	पूर्णांक reset;
	पूर्णांक sync;

	अगर ((!simple_gpio) || (!wkup_gpio))
		वापस -ENODEV;

	चयन (psc_number) अणु
	हाल 0:
		reset   = PSC1_RESET;           /* AC97_1_RES */
		sync    = PSC1_SYNC;            /* AC97_1_SYNC */
		out     = PSC1_SDATA_OUT;       /* AC97_1_SDATA_OUT */
		gpio    = MPC52xx_GPIO_PSC1_MASK;
		अवरोध;
	हाल 1:
		reset   = PSC2_RESET;           /* AC97_2_RES */
		sync    = PSC2_SYNC;            /* AC97_2_SYNC */
		out     = PSC2_SDATA_OUT;       /* AC97_2_SDATA_OUT */
		gpio    = MPC52xx_GPIO_PSC2_MASK;
		अवरोध;
	शेष:
		pr_err(__खाता__ ": Unable to determine PSC, no ac97 "
		       "cold-reset will be performed\n");
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&gpio_lock, flags);

	/* Reconfiure pin-muxing to gpio */
	mux = in_be32(&simple_gpio->port_config);
	out_be32(&simple_gpio->port_config, mux & (~gpio));

	/* enable gpio pins क्रम output */
	setbits8(&wkup_gpio->wkup_gpioe, reset);
	setbits32(&simple_gpio->simple_gpioe, sync | out);

	setbits8(&wkup_gpio->wkup_ddr, reset);
	setbits32(&simple_gpio->simple_ddr, sync | out);

	/* Assert cold reset */
	clrbits32(&simple_gpio->simple_dvo, sync | out);
	clrbits8(&wkup_gpio->wkup_dvo, reset);

	/* रुको क्रम 1 us */
	udelay(1);

	/* Deनिश्चित reset */
	setbits8(&wkup_gpio->wkup_dvo, reset);

	/* रुको at least 200ns */
	/* 7 ~= (200ns * समयbase) / ns2sec */
	__delay(7);

	/* Restore pin-muxing */
	out_be32(&simple_gpio->port_config, mux);

	spin_unlock_irqrestore(&gpio_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpc5200_psc_ac97_gpio_reset);
