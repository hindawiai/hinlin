<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ebony board specअगरic routines
 *
 * Matt Porter <mporter@kernel.crashing.org>
 * Copyright 2002-2005 MontaVista Software Inc.
 *
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 * Copyright (c) 2003-2005 Zultys Technologies
 *
 * Rewritten and ported to the merged घातerpc tree:
 * Copyright 2007 David Gibson <dwg@au1.ibm.com>, IBM Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/uic.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc4xx.h>

अटल स्थिर काष्ठा of_device_id ebony_of_bus[] __initस्थिर = अणु
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणु .compatible = "ibm,ebc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init ebony_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, ebony_of_bus, शून्य);
	of_instantiate_rtc();

	वापस 0;
पूर्ण
machine_device_initcall(ebony, ebony_device_probe);

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init ebony_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("ibm,ebony"))
		वापस 0;

	pci_set_flags(PCI_REASSIGN_ALL_RSRC);

	वापस 1;
पूर्ण

define_machine(ebony) अणु
	.name			= "Ebony",
	.probe			= ebony_probe,
	.progress		= udbg_progress,
	.init_IRQ		= uic_init_tree,
	.get_irq		= uic_get_irq,
	.restart		= ppc4xx_reset_प्रणाली,
	.calibrate_decr		= generic_calibrate_decr,
पूर्ण;
