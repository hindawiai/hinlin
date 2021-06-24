<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006-2010, 2012-2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Author: Andy Fleming <afleming@मुक्तscale.com>
 *
 * Based on 83xx/mpc8360e_pb.c by:
 *	   Li Yang <LeoLi@मुक्तscale.com>
 *	   Yin Olivia <Hong-hua.Yin@मुक्तscale.com>
 *
 * Description:
 * MPC85xx MDS board specअगरic routines.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/initrd.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/memblock.h>
#समावेश <linux/fsl/guts.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/irq.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश "smp.h"

#समावेश "mpc85xx.h"

#अघोषित DEBUG
#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

#अगर IS_BUILTIN(CONFIG_PHYLIB)

#घोषणा MV88E1111_SCR	0x10
#घोषणा MV88E1111_SCR_125CLK	0x0010
अटल पूर्णांक mpc8568_fixup_125_घड़ी(काष्ठा phy_device *phydev)
अणु
	पूर्णांक scr;
	पूर्णांक err;

	/* Workaround क्रम the 125 CLK Toggle */
	scr = phy_पढ़ो(phydev, MV88E1111_SCR);

	अगर (scr < 0)
		वापस scr;

	err = phy_ग_लिखो(phydev, MV88E1111_SCR, scr & ~(MV88E1111_SCR_125CLK));

	अगर (err)
		वापस err;

	err = phy_ग_लिखो(phydev, MII_BMCR, BMCR_RESET);

	अगर (err)
		वापस err;

	scr = phy_पढ़ो(phydev, MV88E1111_SCR);

	अगर (scr < 0)
		वापस scr;

	err = phy_ग_लिखो(phydev, MV88E1111_SCR, scr | 0x0008);

	वापस err;
पूर्ण

अटल पूर्णांक mpc8568_mds_phy_fixups(काष्ठा phy_device *phydev)
अणु
	पूर्णांक temp;
	पूर्णांक err;

	/* Errata */
	err = phy_ग_लिखो(phydev,29, 0x0006);

	अगर (err)
		वापस err;

	temp = phy_पढ़ो(phydev, 30);

	अगर (temp < 0)
		वापस temp;

	temp = (temp & (~0x8000)) | 0x4000;
	err = phy_ग_लिखो(phydev,30, temp);

	अगर (err)
		वापस err;

	err = phy_ग_लिखो(phydev,29, 0x000a);

	अगर (err)
		वापस err;

	temp = phy_पढ़ो(phydev, 30);

	अगर (temp < 0)
		वापस temp;

	temp = phy_पढ़ो(phydev, 30);

	अगर (temp < 0)
		वापस temp;

	temp &= ~0x0020;

	err = phy_ग_लिखो(phydev,30,temp);

	अगर (err)
		वापस err;

	/* Disable स्वतःmatic MDI/MDIX selection */
	temp = phy_पढ़ो(phydev, 16);

	अगर (temp < 0)
		वापस temp;

	temp &= ~0x0060;
	err = phy_ग_लिखो(phydev,16,temp);

	वापस err;
पूर्ण

#पूर्ण_अगर

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
#अगर_घोषित CONFIG_QUICC_ENGINE
अटल व्योम __init mpc85xx_mds_reset_ucc_phys(व्योम)
अणु
	काष्ठा device_node *np;
	अटल u8 __iomem *bcsr_regs;

	/* Map BCSR area */
	np = of_find_node_by_name(शून्य, "bcsr");
	अगर (!np)
		वापस;

	bcsr_regs = of_iomap(np, 0);
	of_node_put(np);
	अगर (!bcsr_regs)
		वापस;

	अगर (machine_is(mpc8568_mds)) अणु
#घोषणा BCSR_UCC1_GETH_EN	(0x1 << 7)
#घोषणा BCSR_UCC2_GETH_EN	(0x1 << 7)
#घोषणा BCSR_UCC1_MODE_MSK	(0x3 << 4)
#घोषणा BCSR_UCC2_MODE_MSK	(0x3 << 0)

		/* Turn off UCC1 & UCC2 */
		clrbits8(&bcsr_regs[8], BCSR_UCC1_GETH_EN);
		clrbits8(&bcsr_regs[9], BCSR_UCC2_GETH_EN);

		/* Mode is RGMII, all bits clear */
		clrbits8(&bcsr_regs[11], BCSR_UCC1_MODE_MSK |
					 BCSR_UCC2_MODE_MSK);

		/* Turn UCC1 & UCC2 on */
		setbits8(&bcsr_regs[8], BCSR_UCC1_GETH_EN);
		setbits8(&bcsr_regs[9], BCSR_UCC2_GETH_EN);
	पूर्ण अन्यथा अगर (machine_is(mpc8569_mds)) अणु
#घोषणा BCSR7_UCC12_GETHnRST	(0x1 << 2)
#घोषणा BCSR8_UEM_MARVELL_RST	(0x1 << 1)
#घोषणा BCSR_UCC_RGMII		(0x1 << 6)
#घोषणा BCSR_UCC_RTBI		(0x1 << 5)
		/*
		 * U-Boot mangles पूर्णांकerrupt polarity क्रम Marvell PHYs,
		 * so reset built-in and UEM Marvell PHYs, this माला_दो
		 * the PHYs पूर्णांकo their normal state.
		 */
		clrbits8(&bcsr_regs[7], BCSR7_UCC12_GETHnRST);
		setbits8(&bcsr_regs[8], BCSR8_UEM_MARVELL_RST);

		setbits8(&bcsr_regs[7], BCSR7_UCC12_GETHnRST);
		clrbits8(&bcsr_regs[8], BCSR8_UEM_MARVELL_RST);

		क्रम_each_compatible_node(np, "network", "ucc_geth") अणु
			स्थिर अचिन्हित पूर्णांक *prop;
			पूर्णांक ucc_num;

			prop = of_get_property(np, "cell-index", शून्य);
			अगर (prop == शून्य)
				जारी;

			ucc_num = *prop - 1;

			prop = of_get_property(np, "phy-connection-type", शून्य);
			अगर (prop == शून्य)
				जारी;

			अगर (म_भेद("rtbi", (स्थिर अक्षर *)prop) == 0)
				clrsetbits_8(&bcsr_regs[7 + ucc_num],
					BCSR_UCC_RGMII, BCSR_UCC_RTBI);
		पूर्ण
	पूर्ण अन्यथा अगर (machine_is(p1021_mds)) अणु
#घोषणा BCSR11_ENET_MICRST     (0x1 << 5)
		/* Reset Micrel PHY */
		clrbits8(&bcsr_regs[11], BCSR11_ENET_MICRST);
		setbits8(&bcsr_regs[11], BCSR11_ENET_MICRST);
	पूर्ण

	iounmap(bcsr_regs);
पूर्ण

अटल व्योम __init mpc85xx_mds_qe_init(व्योम)
अणु
	काष्ठा device_node *np;

	mpc85xx_qe_par_io_init();
	mpc85xx_mds_reset_ucc_phys();

	अगर (machine_is(p1021_mds)) अणु

		काष्ठा ccsr_guts __iomem *guts;

		np = of_find_node_by_name(शून्य, "global-utilities");
		अगर (np) अणु
			guts = of_iomap(np, 0);
			अगर (!guts)
				pr_err("mpc85xx-rdb: could not map global utilities register\n");
			अन्यथाअणु
			/* P1021 has pins muxed क्रम QE and other functions. To
			 * enable QE UEC mode, we need to set bit QE0 क्रम UCC1
			 * in Eth mode, QE0 and QE3 क्रम UCC5 in Eth mode, QE9
			 * and QE12 क्रम QE MII management संकेतs in PMUXCR
			 * रेजिस्टर.
			 */
				setbits32(&guts->pmuxcr, MPC85xx_PMUXCR_QE(0) |
						  MPC85xx_PMUXCR_QE(3) |
						  MPC85xx_PMUXCR_QE(9) |
						  MPC85xx_PMUXCR_QE(12));
				iounmap(guts);
			पूर्ण
			of_node_put(np);
		पूर्ण

	पूर्ण
पूर्ण

#अन्यथा
अटल व्योम __init mpc85xx_mds_qe_init(व्योम) अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_QUICC_ENGINE */

अटल व्योम __init mpc85xx_mds_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mpc85xx_mds_setup_arch()", 0);

	mpc85xx_smp_init();

	mpc85xx_mds_qe_init();

	fsl_pci_assign_primary();

	swiotlb_detect_4g();
पूर्ण

#अगर IS_BUILTIN(CONFIG_PHYLIB)

अटल पूर्णांक __init board_fixups(व्योम)
अणु
	अक्षर phy_id[20];
	अक्षर *compstrs[2] = अणु"fsl,gianfar-mdio", "fsl,ucc-mdio"पूर्ण;
	काष्ठा device_node *mdio;
	काष्ठा resource res;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(compstrs); i++) अणु
		mdio = of_find_compatible_node(शून्य, शून्य, compstrs[i]);

		of_address_to_resource(mdio, 0, &res);
		snम_लिखो(phy_id, माप(phy_id), "%llx:%02x",
			(अचिन्हित दीर्घ दीर्घ)res.start, 1);

		phy_रेजिस्टर_fixup_क्रम_id(phy_id, mpc8568_fixup_125_घड़ी);
		phy_रेजिस्टर_fixup_क्रम_id(phy_id, mpc8568_mds_phy_fixups);

		/* Register a workaround क्रम errata */
		snम_लिखो(phy_id, माप(phy_id), "%llx:%02x",
			(अचिन्हित दीर्घ दीर्घ)res.start, 7);
		phy_रेजिस्टर_fixup_क्रम_id(phy_id, mpc8568_mds_phy_fixups);

		of_node_put(mdio);
	पूर्ण

	वापस 0;
पूर्ण

machine_arch_initcall(mpc8568_mds, board_fixups);
machine_arch_initcall(mpc8569_mds, board_fixups);

#पूर्ण_अगर

अटल पूर्णांक __init mpc85xx_publish_devices(व्योम)
अणु
	वापस mpc85xx_common_publish_devices();
पूर्ण

machine_arch_initcall(mpc8568_mds, mpc85xx_publish_devices);
machine_arch_initcall(mpc8569_mds, mpc85xx_publish_devices);
machine_arch_initcall(p1021_mds, mpc85xx_common_publish_devices);

अटल व्योम __init mpc85xx_mds_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
			MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);

	mpic_init(mpic);
पूर्ण

अटल पूर्णांक __init mpc85xx_mds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MPC85xxMDS");
पूर्ण

define_machine(mpc8568_mds) अणु
	.name		= "MPC8568 MDS",
	.probe		= mpc85xx_mds_probe,
	.setup_arch	= mpc85xx_mds_setup_arch,
	.init_IRQ	= mpc85xx_mds_pic_init,
	.get_irq	= mpic_get_irq,
	.calibrate_decr	= generic_calibrate_decr,
	.progress	= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init mpc8569_mds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,MPC8569EMDS");
पूर्ण

define_machine(mpc8569_mds) अणु
	.name		= "MPC8569 MDS",
	.probe		= mpc8569_mds_probe,
	.setup_arch	= mpc85xx_mds_setup_arch,
	.init_IRQ	= mpc85xx_mds_pic_init,
	.get_irq	= mpic_get_irq,
	.calibrate_decr	= generic_calibrate_decr,
	.progress	= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init p1021_mds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1021MDS");

पूर्ण

define_machine(p1021_mds) अणु
	.name		= "P1021 MDS",
	.probe		= p1021_mds_probe,
	.setup_arch	= mpc85xx_mds_setup_arch,
	.init_IRQ	= mpc85xx_mds_pic_init,
	.get_irq	= mpic_get_irq,
	.calibrate_decr	= generic_calibrate_decr,
	.progress	= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
पूर्ण;
