<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/mpc837x_mds.c
 *
 * Copyright (C) 2007 Freescale Semiconductor, Inc. All rights reserved.
 *
 * MPC837x MDS board specअगरic routines
 */

#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/prom.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc83xx.h"

#घोषणा BCSR12_USB_SER_MASK	0x8a
#घोषणा BCSR12_USB_SER_PIN	0x80
#घोषणा BCSR12_USB_SER_DEVICE	0x02

अटल पूर्णांक mpc837xmds_usb_cfg(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर व्योम *phy_type, *mode;
	व्योम __iomem *bcsr_regs = शून्य;
	u8 bcsr12;
	पूर्णांक ret;

	ret = mpc837x_usb_cfg();
	अगर (ret)
		वापस ret;
	/* Map BCSR area */
	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc837xmds-bcsr");
	अगर (np) अणु
		bcsr_regs = of_iomap(np, 0);
		of_node_put(np);
	पूर्ण
	अगर (!bcsr_regs)
		वापस -1;

	np = of_find_node_by_name(शून्य, "usb");
	अगर (!np) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	phy_type = of_get_property(np, "phy_type", शून्य);
	अगर (phy_type && !म_भेद(phy_type, "ulpi")) अणु
		clrbits8(bcsr_regs + 12, BCSR12_USB_SER_PIN);
	पूर्ण अन्यथा अगर (phy_type && !म_भेद(phy_type, "serial")) अणु
		mode = of_get_property(np, "dr_mode", शून्य);
		bcsr12 = in_8(bcsr_regs + 12) & ~BCSR12_USB_SER_MASK;
		bcsr12 |= BCSR12_USB_SER_PIN;
		अगर (mode && !म_भेद(mode, "peripheral"))
			bcsr12 |= BCSR12_USB_SER_DEVICE;
		out_8(bcsr_regs + 12, bcsr12);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "USB DR: unsupported PHY\n");
	पूर्ण

	of_node_put(np);
out:
	iounmap(bcsr_regs);
	वापस ret;
पूर्ण

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc837x_mds_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();
	mpc837xmds_usb_cfg();
पूर्ण

machine_device_initcall(mpc837x_mds, mpc83xx_declare_of_platक्रमm_devices);

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc837x_mds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,mpc837xmds");
पूर्ण

define_machine(mpc837x_mds) अणु
	.name			= "MPC837x MDS",
	.probe			= mpc837x_mds_probe,
	.setup_arch		= mpc837x_mds_setup_arch,
	.discover_phbs  	= mpc83xx_setup_pci,
	.init_IRQ		= mpc83xx_ipic_init_IRQ,
	.get_irq		= ipic_get_irq,
	.restart		= mpc83xx_restart,
	.समय_init		= mpc83xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
