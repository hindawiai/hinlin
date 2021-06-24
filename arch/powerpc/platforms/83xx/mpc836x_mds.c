<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Li Yang <LeoLi@मुक्तscale.com>
 *	   Yin Olivia <Hong-hua.Yin@मुक्तscale.com>
 *
 * Description:
 * MPC8360E MDS board specअगरic routines.
 *
 * Changelog:
 * Jun 21, 2006	Initial version
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश "mpc83xx.h"

#अघोषित DEBUG
#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc836x_mds_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;
	u8 __iomem *bcsr_regs = शून्य;

	mpc83xx_setup_arch();

	/* Map BCSR area */
	np = of_find_node_by_name(शून्य, "bcsr");
	अगर (np) अणु
		काष्ठा resource res;

		of_address_to_resource(np, 0, &res);
		bcsr_regs = ioremap(res.start, resource_size(&res));
		of_node_put(np);
	पूर्ण

#अगर_घोषित CONFIG_QUICC_ENGINE
	अगर ((np = of_find_node_by_name(शून्य, "par_io")) != शून्य) अणु
		par_io_init(np);
		of_node_put(np);

		क्रम_each_node_by_name(np, "ucc")
			par_io_of_config(np);
#अगर_घोषित CONFIG_QE_USB
		/* Must fixup Par IO beक्रमe QE GPIO chips are रेजिस्टरed. */
		par_io_config_pin(1,  2, 1, 0, 3, 0); /* USBOE  */
		par_io_config_pin(1,  3, 1, 0, 3, 0); /* USBTP  */
		par_io_config_pin(1,  8, 1, 0, 1, 0); /* USBTN  */
		par_io_config_pin(1, 10, 2, 0, 3, 0); /* USBRXD */
		par_io_config_pin(1,  9, 2, 1, 3, 0); /* USBRP  */
		par_io_config_pin(1, 11, 2, 1, 3, 0); /* USBRN  */
		par_io_config_pin(2, 20, 2, 0, 1, 0); /* CLK21  */
#पूर्ण_अगर /* CONFIG_QE_USB */
	पूर्ण

	अगर ((np = of_find_compatible_node(शून्य, "network", "ucc_geth"))
			!= शून्य)अणु
		uपूर्णांक svid;

		/* Reset the Ethernet PHY */
#घोषणा BCSR9_GETHRST 0x20
		clrbits8(&bcsr_regs[9], BCSR9_GETHRST);
		udelay(1000);
		setbits8(&bcsr_regs[9], BCSR9_GETHRST);

		/* handle mpc8360ea rev.2.1 erratum 2: RGMII Timing */
		svid = mfspr(SPRN_SVR);
		अगर (svid == 0x80480021) अणु
			व्योम __iomem *immap;

			immap = ioremap(get_immrbase() + 0x14a8, 8);

			/*
			 * IMMR + 0x14A8[4:5] = 11 (clk delay क्रम UCC 2)
			 * IMMR + 0x14A8[18:19] = 11 (clk delay क्रम UCC 1)
			 */
			setbits32(immap, 0x0c003000);

			/*
			 * IMMR + 0x14AC[20:27] = 10101010
			 * (data delay क्रम both UCC's)
			 */
			clrsetbits_be32(immap + 4, 0xff0, 0xaa0);

			iounmap(immap);
		पूर्ण

		iounmap(bcsr_regs);
		of_node_put(np);
	पूर्ण
#पूर्ण_अगर				/* CONFIG_QUICC_ENGINE */
पूर्ण

machine_device_initcall(mpc836x_mds, mpc83xx_declare_of_platक्रमm_devices);

#अगर_घोषित CONFIG_QE_USB
अटल पूर्णांक __init mpc836x_usb_cfg(व्योम)
अणु
	u8 __iomem *bcsr;
	काष्ठा device_node *np;
	स्थिर अक्षर *mode;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc8360mds-bcsr");
	अगर (!np)
		वापस -ENODEV;

	bcsr = of_iomap(np, 0);
	of_node_put(np);
	अगर (!bcsr)
		वापस -ENOMEM;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc8323-qe-usb");
	अगर (!np) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

#घोषणा BCSR8_TSEC1M_MASK	(0x3 << 6)
#घोषणा BCSR8_TSEC1M_RGMII	(0x0 << 6)
#घोषणा BCSR8_TSEC2M_MASK	(0x3 << 4)
#घोषणा BCSR8_TSEC2M_RGMII	(0x0 << 4)
	/*
	 * Default is GMII (2), but we should set it to RGMII (0) अगर we use
	 * USB (Eth PHY is in RGMII mode anyway).
	 */
	clrsetbits_8(&bcsr[8], BCSR8_TSEC1M_MASK | BCSR8_TSEC2M_MASK,
			       BCSR8_TSEC1M_RGMII | BCSR8_TSEC2M_RGMII);

#घोषणा BCSR13_USBMASK	0x0f
#घोषणा BCSR13_nUSBEN	0x08 /* 1 - Disable, 0 - Enable			*/
#घोषणा BCSR13_USBSPEED	0x04 /* 1 - Full, 0 - Low			*/
#घोषणा BCSR13_USBMODE	0x02 /* 1 - Host, 0 - Function			*/
#घोषणा BCSR13_nUSBVCC	0x01 /* 1 - माला_लो VBUS, 0 - supplies VBUS 	*/

	clrsetbits_8(&bcsr[13], BCSR13_USBMASK, BCSR13_USBSPEED);

	mode = of_get_property(np, "mode", शून्य);
	अगर (mode && !म_भेद(mode, "peripheral")) अणु
		setbits8(&bcsr[13], BCSR13_nUSBVCC);
		qe_usb_घड़ी_set(QE_CLK21, 48000000);
	पूर्ण अन्यथा अणु
		setbits8(&bcsr[13], BCSR13_USBMODE);
	पूर्ण

	of_node_put(np);
err:
	iounmap(bcsr);
	वापस ret;
पूर्ण
machine_arch_initcall(mpc836x_mds, mpc836x_usb_cfg);
#पूर्ण_अगर /* CONFIG_QE_USB */

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc836x_mds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MPC836xMDS");
पूर्ण

define_machine(mpc836x_mds) अणु
	.name		= "MPC836x MDS",
	.probe		= mpc836x_mds_probe,
	.setup_arch	= mpc836x_mds_setup_arch,
	.discover_phbs  = mpc83xx_setup_pci,
	.init_IRQ	= mpc83xx_ipic_init_IRQ,
	.get_irq	= ipic_get_irq,
	.restart	= mpc83xx_restart,
	.समय_init	= mpc83xx_समय_init,
	.calibrate_decr	= generic_calibrate_decr,
	.progress	= udbg_progress,
पूर्ण;
