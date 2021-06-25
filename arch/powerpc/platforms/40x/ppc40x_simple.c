<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic PowerPC 40x platक्रमm support
 *
 * Copyright 2008 IBM Corporation
 *
 * This implements simple platक्रमm support क्रम PowerPC 44x chips.  This is
 * mostly used क्रम eval boards or other simple and "generic" 44x boards.  If
 * your board has custom functions or hardware, then you will likely want to
 * implement your own board.c file to accommodate it.
 */

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc4xx.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/uic.h>

#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>

अटल स्थिर काष्ठा of_device_id ppc40x_of_bus[] __initस्थिर = अणु
	अणु .compatible = "ibm,plb3", पूर्ण,
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणु .compatible = "ibm,ebc", पूर्ण,
	अणु .compatible = "simple-bus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init ppc40x_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, ppc40x_of_bus, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(ppc40x_simple, ppc40x_device_probe);

/* This is the list of boards that can be supported by this simple
 * platक्रमm code.  This करोes _not_ mean the boards are compatible,
 * as they most certainly are not from a device tree perspective.
 * However, their dअगरferences are handled by the device tree and the
 * drivers and thereक्रमe they करोn't need custom board support files.
 *
 * Again, अगर your board needs to करो things dअगरferently then create a
 * board.c file क्रम it rather than adding it to this list.
 */
अटल स्थिर अक्षर * स्थिर board[] __initस्थिर = अणु
	"amcc,acadia",
	"amcc,haleakala",
	"amcc,kilauea",
	"amcc,makalu",
	"apm,klondike",
	"est,hotfoot",
	"plathome,obs600",
	शून्य
पूर्ण;

अटल पूर्णांक __init ppc40x_probe(व्योम)
अणु
	अगर (of_device_compatible_match(of_root, board)) अणु
		pci_set_flags(PCI_REASSIGN_ALL_RSRC);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

define_machine(ppc40x_simple) अणु
	.name = "PowerPC 40x Platform",
	.probe = ppc40x_probe,
	.progress = udbg_progress,
	.init_IRQ = uic_init_tree,
	.get_irq = uic_get_irq,
	.restart = ppc4xx_reset_प्रणाली,
	.calibrate_decr = generic_calibrate_decr,
पूर्ण;
