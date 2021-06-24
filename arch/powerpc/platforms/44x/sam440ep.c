<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sam440ep board specअगरic routines based off bamboo.c code
 * original copyrights below
 *
 * Wade Farnsworth <wfarnsworth@mvista.com>
 * Copyright 2004 MontaVista Software Inc.
 *
 * Rewritten and ported to the merged घातerpc tree:
 * Josh Boyer <jwboyer@linux.vnet.ibm.com>
 * Copyright 2007 IBM Corporation
 *
 * Modअगरied from bamboo.c क्रम sam440ep:
 * Copyright 2008 Giuseppe Coviello <gicoviello@gmail.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/uic.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc4xx.h>
#समावेश <linux/i2c.h>

अटल स्थिर काष्ठा of_device_id sam440ep_of_bus[] __initस्थिर = अणु
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणु .compatible = "ibm,ebc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init sam440ep_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, sam440ep_of_bus, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(sam440ep, sam440ep_device_probe);

अटल पूर्णांक __init sam440ep_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("acube,sam440ep"))
		वापस 0;

	pci_set_flags(PCI_REASSIGN_ALL_RSRC);

	वापस 1;
पूर्ण

define_machine(sam440ep) अणु
	.name 			= "Sam440ep",
	.probe 			= sam440ep_probe,
	.progress 		= udbg_progress,
	.init_IRQ 		= uic_init_tree,
	.get_irq 		= uic_get_irq,
	.restart		= ppc4xx_reset_प्रणाली,
	.calibrate_decr 	= generic_calibrate_decr,
पूर्ण;

अटल काष्ठा i2c_board_info sam440ep_rtc_info = अणु
	.type = "m41st85",
	.addr = 0x68,
	.irq = -1,
पूर्ण;

अटल पूर्णांक __init sam440ep_setup_rtc(व्योम)
अणु
	वापस i2c_रेजिस्टर_board_info(0, &sam440ep_rtc_info, 1);
पूर्ण
machine_device_initcall(sam440ep, sam440ep_setup_rtc);
