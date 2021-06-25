<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ppa8548 setup and early boot code.
 *
 * Copyright 2009 Prodrive B.V..
 *
 * By Stef van Os (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Based on the SBC8548 support - Copyright 2007 Wind River Systems Inc.
 * Based on the MPC8548CDS support - Copyright 2005 Freescale Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>

#समावेश <sysdev/fsl_soc.h>

अटल व्योम __init ppa8548_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init ppa8548_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("ppa8548_setup_arch()", 0);
पूर्ण

अटल व्योम ppa8548_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक32_t svid, phid1;

	svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: Prodrive B.V.\n");
	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_म_लिखो(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .name = "soc", पूर्ण,
	अणु .type = "soc", पूर्ण,
	अणु .compatible = "simple-bus", पूर्ण,
	अणु .compatible = "gianfar", पूर्ण,
	अणु .compatible = "fsl,srio", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(ppa8548, declare_of_platक्रमm_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init ppa8548_probe(व्योम)
अणु
	वापस of_machine_is_compatible("ppa8548");
पूर्ण

define_machine(ppa8548) अणु
	.name		= "ppa8548",
	.probe		= ppa8548_probe,
	.setup_arch	= ppa8548_setup_arch,
	.init_IRQ	= ppa8548_pic_init,
	.show_cpuinfo	= ppa8548_show_cpuinfo,
	.get_irq	= mpic_get_irq,
	.calibrate_decr = generic_calibrate_decr,
	.progress	= udbg_progress,
पूर्ण;
