<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale Lite5200 board support
 *
 * Written by: Grant Likely <grant.likely@secretlab.ca>
 *
 * Copyright (C) Secret Lab Technologies Ltd. 2006. All rights reserved.
 * Copyright 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Description:
 */

#अघोषित DEBUG

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/initrd.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpc52xx.h>

/* ************************************************************************
 *
 * Setup the architecture
 *
 */

/* mpc5200 device tree match tables */
अटल स्थिर काष्ठा of_device_id mpc5200_cdm_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-cdm", पूर्ण,
	अणु .compatible = "mpc5200-cdm", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id mpc5200_gpio_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5200-gpio", पूर्ण,
	अणु .compatible = "mpc5200-gpio", पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Fix घड़ी configuration.
 *
 * Firmware is supposed to be responsible क्रम this.  If you are creating a
 * new board port, करो *NOT* duplicate this code.  Fix your boot firmware
 * to set it correctly in the first place
 */
अटल व्योम __init
lite5200_fix_घड़ी_config(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा mpc52xx_cdm  __iomem *cdm;
	/* Map zones */
	np = of_find_matching_node(शून्य, mpc5200_cdm_ids);
	cdm = of_iomap(np, 0);
	of_node_put(np);
	अगर (!cdm) अणु
		prपूर्णांकk(KERN_ERR "%s() failed; expect abnormal behaviour\n",
		       __func__);
		वापस;
	पूर्ण

	/* Use पूर्णांकernal 48 Mhz */
	out_8(&cdm->ext_48mhz_en, 0x00);
	out_8(&cdm->fd_enable, 0x01);
	अगर (in_be32(&cdm->rstcfg) & 0x40)	/* Assumes 33Mhz घड़ी */
		out_be16(&cdm->fd_counters, 0x0001);
	अन्यथा
		out_be16(&cdm->fd_counters, 0x5555);

	/* Unmap the regs */
	iounmap(cdm);
पूर्ण

/*
 * Fix setting of port_config रेजिस्टर.
 *
 * Firmware is supposed to be responsible क्रम this.  If you are creating a
 * new board port, करो *NOT* duplicate this code.  Fix your boot firmware
 * to set it correctly in the first place
 */
अटल व्योम __init
lite5200_fix_port_config(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा mpc52xx_gpio __iomem *gpio;
	u32 port_config;

	np = of_find_matching_node(शून्य, mpc5200_gpio_ids);
	gpio = of_iomap(np, 0);
	of_node_put(np);
	अगर (!gpio) अणु
		prपूर्णांकk(KERN_ERR "%s() failed. expect abnormal behavior\n",
		       __func__);
		वापस;
	पूर्ण

	/* Set port config */
	port_config = in_be32(&gpio->port_config);

	port_config &= ~0x00800000;	/* 48Mhz पूर्णांकernal, pin is GPIO	*/

	port_config &= ~0x00007000;	/* USB port : Dअगरferential mode	*/
	port_config |=  0x00001000;	/*            USB 1 only	*/

	port_config &= ~0x03000000;	/* ATA CS is on csb_4/5		*/
	port_config |=  0x01000000;

	pr_debug("port_config: old:%x new:%x\n",
	         in_be32(&gpio->port_config), port_config);
	out_be32(&gpio->port_config, port_config);

	/* Unmap zone */
	iounmap(gpio);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम lite5200_suspend_prepare(व्योम __iomem *mbar)
अणु
	u8 pin = 1;	/* GPIO_WKUP_1 (GPIO_PSC2_4) */
	u8 level = 0;	/* wakeup on low level */
	mpc52xx_set_wakeup_gpio(pin, level);

	/*
	 * घातer करोwn usb port
	 * this needs to be called beक्रमe of-ohci suspend code
	 */

	/* set ports to "power switched" and "powered at the same time"
	 * USB Rh descriptor A: NPS = 0, PSM = 0 */
	out_be32(mbar + 0x1048, in_be32(mbar + 0x1048) & ~0x300);
	/* USB Rh status: LPS = 1 - turn off घातer */
	out_be32(mbar + 0x1050, 0x00000001);
पूर्ण

अटल व्योम lite5200_resume_finish(व्योम __iomem *mbar)
अणु
	/* USB Rh status: LPSC = 1 - turn on घातer */
	out_be32(mbar + 0x1050, 0x00010000);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init lite5200_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("lite5200_setup_arch()", 0);

	/* Map important रेजिस्टरs from the पूर्णांकernal memory map */
	mpc52xx_map_common_devices();

	/* Some mpc5200 & mpc5200b related configuration */
	mpc5200_setup_xlb_arbiter();

	/* Fix things that firmware should have करोne. */
	lite5200_fix_घड़ी_config();
	lite5200_fix_port_config();

#अगर_घोषित CONFIG_PM
	mpc52xx_suspend.board_suspend_prepare = lite5200_suspend_prepare;
	mpc52xx_suspend.board_resume_finish = lite5200_resume_finish;
	lite5200_pm_init();
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर * स्थिर board[] __initस्थिर = अणु
	"fsl,lite5200",
	"fsl,lite5200b",
	शून्य,
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init lite5200_probe(व्योम)
अणु
	वापस of_device_compatible_match(of_root, board);
पूर्ण

define_machine(lite5200) अणु
	.name 		= "lite5200",
	.probe 		= lite5200_probe,
	.setup_arch 	= lite5200_setup_arch,
	.discover_phbs	= mpc52xx_setup_pci,
	.init		= mpc52xx_declare_of_platक्रमm_devices,
	.init_IRQ 	= mpc52xx_init_irq,
	.get_irq 	= mpc52xx_get_irq,
	.restart	= mpc52xx_restart,
	.calibrate_decr	= generic_calibrate_decr,
पूर्ण;
