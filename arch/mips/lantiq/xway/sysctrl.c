<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2011-2012 John Crispin <john@phrozen.org>
 *  Copyright (C) 2013-2015 Lantiq Beteiligungs-GmbH & Co.KG
 */

#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>

#समावेश <lantiq_soc.h>

#समावेश "../clk.h"
#समावेश "../prom.h"

/* घड़ी control रेजिस्टर क्रम legacy */
#घोषणा CGU_IFCCR	0x0018
#घोषणा CGU_IFCCR_VR9	0x0024
/* प्रणाली घड़ी रेजिस्टर क्रम legacy */
#घोषणा CGU_SYS		0x0010
/* pci control रेजिस्टर */
#घोषणा CGU_PCICR	0x0034
#घोषणा CGU_PCICR_VR9	0x0038
/* ephy configuration रेजिस्टर */
#घोषणा CGU_EPHY	0x10

/* Legacy PMU रेजिस्टर क्रम ar9, ase, danube */
/* घातer control रेजिस्टर */
#घोषणा PMU_PWDCR	0x1C
/* घातer status रेजिस्टर */
#घोषणा PMU_PWDSR	0x20
/* घातer control रेजिस्टर */
#घोषणा PMU_PWDCR1	0x24
/* घातer status रेजिस्टर */
#घोषणा PMU_PWDSR1	0x28
/* घातer control रेजिस्टर */
#घोषणा PWDCR(x) ((x) ? (PMU_PWDCR1) : (PMU_PWDCR))
/* घातer status रेजिस्टर */
#घोषणा PWDSR(x) ((x) ? (PMU_PWDSR1) : (PMU_PWDSR))


/* PMU रेजिस्टर क्रम ar10 and grx390 */

/* First रेजिस्टर set */
#घोषणा PMU_CLK_SR	0x20 /* status */
#घोषणा PMU_CLK_CR_A	0x24 /* Enable */
#घोषणा PMU_CLK_CR_B	0x28 /* Disable */
/* Second रेजिस्टर set */
#घोषणा PMU_CLK_SR1	0x30 /* status */
#घोषणा PMU_CLK_CR1_A	0x34 /* Enable */
#घोषणा PMU_CLK_CR1_B	0x38 /* Disable */
/* Third रेजिस्टर set */
#घोषणा PMU_ANA_SR	0x40 /* status */
#घोषणा PMU_ANA_CR_A	0x44 /* Enable */
#घोषणा PMU_ANA_CR_B	0x48 /* Disable */

/* Status */
अटल u32 pmu_clk_sr[] = अणु
	PMU_CLK_SR,
	PMU_CLK_SR1,
	PMU_ANA_SR,
पूर्ण;

/* Enable */
अटल u32 pmu_clk_cr_a[] = अणु
	PMU_CLK_CR_A,
	PMU_CLK_CR1_A,
	PMU_ANA_CR_A,
पूर्ण;

/* Disable */
अटल u32 pmu_clk_cr_b[] = अणु
	PMU_CLK_CR_B,
	PMU_CLK_CR1_B,
	PMU_ANA_CR_B,
पूर्ण;

#घोषणा PWDCR_EN_XRX(x)		(pmu_clk_cr_a[(x)])
#घोषणा PWDCR_DIS_XRX(x)	(pmu_clk_cr_b[(x)])
#घोषणा PWDSR_XRX(x)		(pmu_clk_sr[(x)])

/* घड़ी gates that we can en/disable */
#घोषणा PMU_USB0_P	BIT(0)
#घोषणा PMU_ASE_SDIO	BIT(2) /* ASE special */
#घोषणा PMU_PCI		BIT(4)
#घोषणा PMU_DMA		BIT(5)
#घोषणा PMU_USB0	BIT(6)
#घोषणा PMU_ASC0	BIT(7)
#घोषणा PMU_EPHY	BIT(7)	/* ase */
#घोषणा PMU_USIF	BIT(7) /* from vr9 until grx390 */
#घोषणा PMU_SPI		BIT(8)
#घोषणा PMU_DFE		BIT(9)
#घोषणा PMU_EBU		BIT(10)
#घोषणा PMU_STP		BIT(11)
#घोषणा PMU_GPT		BIT(12)
#घोषणा PMU_AHBS	BIT(13) /* vr9 */
#घोषणा PMU_FPI		BIT(14)
#घोषणा PMU_AHBM	BIT(15)
#घोषणा PMU_SDIO	BIT(16) /* danube, ar9, vr9 */
#घोषणा PMU_ASC1	BIT(17)
#घोषणा PMU_PPE_QSB	BIT(18)
#घोषणा PMU_PPE_SLL01	BIT(19)
#घोषणा PMU_DEU		BIT(20)
#घोषणा PMU_PPE_TC	BIT(21)
#घोषणा PMU_PPE_EMA	BIT(22)
#घोषणा PMU_PPE_DPLUM	BIT(23)
#घोषणा PMU_PPE_DP	BIT(23)
#घोषणा PMU_PPE_DPLUS	BIT(24)
#घोषणा PMU_USB1_P	BIT(26)
#घोषणा PMU_GPHY3	BIT(26) /* grx390 */
#घोषणा PMU_USB1	BIT(27)
#घोषणा PMU_SWITCH	BIT(28)
#घोषणा PMU_PPE_TOP	BIT(29)
#घोषणा PMU_GPHY0	BIT(29) /* ar10, xrx390 */
#घोषणा PMU_GPHY	BIT(30)
#घोषणा PMU_GPHY1	BIT(30) /* ar10, xrx390 */
#घोषणा PMU_PCIE_CLK	BIT(31)
#घोषणा PMU_GPHY2	BIT(31) /* ar10, xrx390 */

#घोषणा PMU1_PCIE_PHY	BIT(0)	/* vr9-specअगरic,moved in ar10/grx390 */
#घोषणा PMU1_PCIE_CTL	BIT(1)
#घोषणा PMU1_PCIE_PDI	BIT(4)
#घोषणा PMU1_PCIE_MSI	BIT(5)
#घोषणा PMU1_CKE	BIT(6)
#घोषणा PMU1_PCIE1_CTL	BIT(17)
#घोषणा PMU1_PCIE1_PDI	BIT(20)
#घोषणा PMU1_PCIE1_MSI	BIT(21)
#घोषणा PMU1_PCIE2_CTL	BIT(25)
#घोषणा PMU1_PCIE2_PDI	BIT(26)
#घोषणा PMU1_PCIE2_MSI	BIT(27)

#घोषणा PMU_ANALOG_USB0_P	BIT(0)
#घोषणा PMU_ANALOG_USB1_P	BIT(1)
#घोषणा PMU_ANALOG_PCIE0_P	BIT(8)
#घोषणा PMU_ANALOG_PCIE1_P	BIT(9)
#घोषणा PMU_ANALOG_PCIE2_P	BIT(10)
#घोषणा PMU_ANALOG_DSL_AFE	BIT(16)
#घोषणा PMU_ANALOG_DCDC_2V5	BIT(17)
#घोषणा PMU_ANALOG_DCDC_1VX	BIT(18)
#घोषणा PMU_ANALOG_DCDC_1V0	BIT(19)

#घोषणा pmu_w32(x, y)	ltq_w32((x), pmu_membase + (y))
#घोषणा pmu_r32(x)	ltq_r32(pmu_membase + (x))

अटल व्योम __iomem *pmu_membase;
व्योम __iomem *ltq_cgu_membase;
व्योम __iomem *ltq_ebu_membase;

अटल u32 अगरccr = CGU_IFCCR;
अटल u32 pcicr = CGU_PCICR;

अटल DEFINE_SPINLOCK(g_pmu_lock);

/* legacy function kept alive to ease clkdev transition */
व्योम ltq_pmu_enable(अचिन्हित पूर्णांक module)
अणु
	पूर्णांक retry = 1000000;

	spin_lock(&g_pmu_lock);
	pmu_w32(pmu_r32(PMU_PWDCR) & ~module, PMU_PWDCR);
	करो अणुपूर्ण जबतक (--retry && (pmu_r32(PMU_PWDSR) & module));
	spin_unlock(&g_pmu_lock);

	अगर (!retry)
		panic("activating PMU module failed!");
पूर्ण
EXPORT_SYMBOL(ltq_pmu_enable);

/* legacy function kept alive to ease clkdev transition */
व्योम ltq_pmu_disable(अचिन्हित पूर्णांक module)
अणु
	पूर्णांक retry = 1000000;

	spin_lock(&g_pmu_lock);
	pmu_w32(pmu_r32(PMU_PWDCR) | module, PMU_PWDCR);
	करो अणुपूर्ण जबतक (--retry && (!(pmu_r32(PMU_PWDSR) & module)));
	spin_unlock(&g_pmu_lock);

	अगर (!retry)
		pr_warn("deactivating PMU module failed!");
पूर्ण
EXPORT_SYMBOL(ltq_pmu_disable);

/* enable a hw घड़ी */
अटल पूर्णांक cgu_enable(काष्ठा clk *clk)
अणु
	ltq_cgu_w32(ltq_cgu_r32(अगरccr) | clk->bits, अगरccr);
	वापस 0;
पूर्ण

/* disable a hw घड़ी */
अटल व्योम cgu_disable(काष्ठा clk *clk)
अणु
	ltq_cgu_w32(ltq_cgu_r32(अगरccr) & ~clk->bits, अगरccr);
पूर्ण

/* enable a घड़ी gate */
अटल पूर्णांक pmu_enable(काष्ठा clk *clk)
अणु
	पूर्णांक retry = 1000000;

	अगर (of_machine_is_compatible("lantiq,ar10")
	    || of_machine_is_compatible("lantiq,grx390")) अणु
		pmu_w32(clk->bits, PWDCR_EN_XRX(clk->module));
		करो अणुपूर्ण जबतक (--retry &&
			     (!(pmu_r32(PWDSR_XRX(clk->module)) & clk->bits)));

	पूर्ण अन्यथा अणु
		spin_lock(&g_pmu_lock);
		pmu_w32(pmu_r32(PWDCR(clk->module)) & ~clk->bits,
				PWDCR(clk->module));
		करो अणुपूर्ण जबतक (--retry &&
			     (pmu_r32(PWDSR(clk->module)) & clk->bits));
		spin_unlock(&g_pmu_lock);
	पूर्ण

	अगर (!retry)
		panic("activating PMU module failed!");

	वापस 0;
पूर्ण

/* disable a घड़ी gate */
अटल व्योम pmu_disable(काष्ठा clk *clk)
अणु
	पूर्णांक retry = 1000000;

	अगर (of_machine_is_compatible("lantiq,ar10")
	    || of_machine_is_compatible("lantiq,grx390")) अणु
		pmu_w32(clk->bits, PWDCR_DIS_XRX(clk->module));
		करो अणुपूर्ण जबतक (--retry &&
			     (pmu_r32(PWDSR_XRX(clk->module)) & clk->bits));
	पूर्ण अन्यथा अणु
		spin_lock(&g_pmu_lock);
		pmu_w32(pmu_r32(PWDCR(clk->module)) | clk->bits,
				PWDCR(clk->module));
		करो अणुपूर्ण जबतक (--retry &&
			     (!(pmu_r32(PWDSR(clk->module)) & clk->bits)));
		spin_unlock(&g_pmu_lock);
	पूर्ण

	अगर (!retry)
		pr_warn("deactivating PMU module failed!");
पूर्ण

/* the pci enable helper */
अटल पूर्णांक pci_enable(काष्ठा clk *clk)
अणु
	अचिन्हित पूर्णांक val = ltq_cgu_r32(अगरccr);
	/* set bus घड़ी speed */
	अगर (of_machine_is_compatible("lantiq,ar9") ||
			of_machine_is_compatible("lantiq,vr9")) अणु
		val &= ~0x1f00000;
		अगर (clk->rate == CLOCK_33M)
			val |= 0xe00000;
		अन्यथा
			val |= 0x700000; /* 62.5M */
	पूर्ण अन्यथा अणु
		val &= ~0xf00000;
		अगर (clk->rate == CLOCK_33M)
			val |= 0x800000;
		अन्यथा
			val |= 0x400000; /* 62.5M */
	पूर्ण
	ltq_cgu_w32(val, अगरccr);
	pmu_enable(clk);
	वापस 0;
पूर्ण

/* enable the बाह्यal घड़ी as a source */
अटल पूर्णांक pci_ext_enable(काष्ठा clk *clk)
अणु
	ltq_cgu_w32(ltq_cgu_r32(अगरccr) & ~(1 << 16), अगरccr);
	ltq_cgu_w32((1 << 30), pcicr);
	वापस 0;
पूर्ण

/* disable the बाह्यal घड़ी as a source */
अटल व्योम pci_ext_disable(काष्ठा clk *clk)
अणु
	ltq_cgu_w32(ltq_cgu_r32(अगरccr) | (1 << 16), अगरccr);
	ltq_cgu_w32((1 << 31) | (1 << 30), pcicr);
पूर्ण

/* enable a घड़ीout source */
अटल पूर्णांक clkout_enable(काष्ठा clk *clk)
अणु
	पूर्णांक i;

	/* get the correct rate */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (clk->rates[i] == clk->rate) अणु
			पूर्णांक shअगरt = 14 - (2 * clk->module);
			पूर्णांक enable = 7 - clk->module;
			अचिन्हित पूर्णांक val = ltq_cgu_r32(अगरccr);

			val &= ~(3 << shअगरt);
			val |= i << shअगरt;
			val |= enable;
			ltq_cgu_w32(val, अगरccr);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/* manage the घड़ी gates via PMU */
अटल व्योम clkdev_add_pmu(स्थिर अक्षर *dev, स्थिर अक्षर *con, bool deactivate,
			   अचिन्हित पूर्णांक module, अचिन्हित पूर्णांक bits)
अणु
	काष्ठा clk *clk = kzalloc(माप(काष्ठा clk), GFP_KERNEL);

	clk->cl.dev_id = dev;
	clk->cl.con_id = con;
	clk->cl.clk = clk;
	clk->enable = pmu_enable;
	clk->disable = pmu_disable;
	clk->module = module;
	clk->bits = bits;
	अगर (deactivate) अणु
		/*
		 * Disable it during the initialization. Module should enable
		 * when used
		 */
		pmu_disable(clk);
	पूर्ण
	clkdev_add(&clk->cl);
पूर्ण

/* manage the घड़ी generator */
अटल व्योम clkdev_add_cgu(स्थिर अक्षर *dev, स्थिर अक्षर *con,
					अचिन्हित पूर्णांक bits)
अणु
	काष्ठा clk *clk = kzalloc(माप(काष्ठा clk), GFP_KERNEL);

	clk->cl.dev_id = dev;
	clk->cl.con_id = con;
	clk->cl.clk = clk;
	clk->enable = cgu_enable;
	clk->disable = cgu_disable;
	clk->bits = bits;
	clkdev_add(&clk->cl);
पूर्ण

/* pci needs its own enable function as the setup is a bit more complex */
अटल अचिन्हित दीर्घ valid_pci_rates[] = अणुCLOCK_33M, CLOCK_62_5M, 0पूर्ण;

अटल व्योम clkdev_add_pci(व्योम)
अणु
	काष्ठा clk *clk = kzalloc(माप(काष्ठा clk), GFP_KERNEL);
	काष्ठा clk *clk_ext = kzalloc(माप(काष्ठा clk), GFP_KERNEL);

	/* मुख्य pci घड़ी */
	clk->cl.dev_id = "17000000.pci";
	clk->cl.con_id = शून्य;
	clk->cl.clk = clk;
	clk->rate = CLOCK_33M;
	clk->rates = valid_pci_rates;
	clk->enable = pci_enable;
	clk->disable = pmu_disable;
	clk->module = 0;
	clk->bits = PMU_PCI;
	clkdev_add(&clk->cl);

	/* use पूर्णांकernal/बाह्यal bus घड़ी */
	clk_ext->cl.dev_id = "17000000.pci";
	clk_ext->cl.con_id = "external";
	clk_ext->cl.clk = clk_ext;
	clk_ext->enable = pci_ext_enable;
	clk_ext->disable = pci_ext_disable;
	clkdev_add(&clk_ext->cl);
पूर्ण

/* xway socs can generate घड़ीs on gpio pins */
अटल अचिन्हित दीर्घ valid_clkout_rates[4][5] = अणु
	अणुCLOCK_32_768K, CLOCK_1_536M, CLOCK_2_5M, CLOCK_12M, 0पूर्ण,
	अणुCLOCK_40M, CLOCK_12M, CLOCK_24M, CLOCK_48M, 0पूर्ण,
	अणुCLOCK_25M, CLOCK_40M, CLOCK_30M, CLOCK_60M, 0पूर्ण,
	अणुCLOCK_12M, CLOCK_50M, CLOCK_32_768K, CLOCK_25M, 0पूर्ण,
पूर्ण;

अटल व्योम clkdev_add_clkout(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा clk *clk;
		अक्षर *name;

		name = kzalloc(माप("clkout0"), GFP_KERNEL);
		प्र_लिखो(name, "clkout%d", i);

		clk = kzalloc(माप(काष्ठा clk), GFP_KERNEL);
		clk->cl.dev_id = "1f103000.cgu";
		clk->cl.con_id = name;
		clk->cl.clk = clk;
		clk->rate = 0;
		clk->rates = valid_clkout_rates[i];
		clk->enable = clkout_enable;
		clk->module = i;
		clkdev_add(&clk->cl);
	पूर्ण
पूर्ण

/* bring up all रेजिस्टर ranges that we need क्रम basic प्रणाली control */
व्योम __init ltq_soc_init(व्योम)
अणु
	काष्ठा resource res_pmu, res_cgu, res_ebu;
	काष्ठा device_node *np_pmu =
			of_find_compatible_node(शून्य, शून्य, "lantiq,pmu-xway");
	काष्ठा device_node *np_cgu =
			of_find_compatible_node(शून्य, शून्य, "lantiq,cgu-xway");
	काष्ठा device_node *np_ebu =
			of_find_compatible_node(शून्य, शून्य, "lantiq,ebu-xway");

	/* check अगर all the core रेजिस्टर ranges are available */
	अगर (!np_pmu || !np_cgu || !np_ebu)
		panic("Failed to load core nodes from devicetree");

	अगर (of_address_to_resource(np_pmu, 0, &res_pmu) ||
			of_address_to_resource(np_cgu, 0, &res_cgu) ||
			of_address_to_resource(np_ebu, 0, &res_ebu))
		panic("Failed to get core resources");

	अगर (!request_mem_region(res_pmu.start, resource_size(&res_pmu),
				res_pmu.name) ||
		!request_mem_region(res_cgu.start, resource_size(&res_cgu),
				res_cgu.name) ||
		!request_mem_region(res_ebu.start, resource_size(&res_ebu),
				res_ebu.name))
		pr_err("Failed to request core resources");

	pmu_membase = ioremap(res_pmu.start, resource_size(&res_pmu));
	ltq_cgu_membase = ioremap(res_cgu.start,
						resource_size(&res_cgu));
	ltq_ebu_membase = ioremap(res_ebu.start,
						resource_size(&res_ebu));
	अगर (!pmu_membase || !ltq_cgu_membase || !ltq_ebu_membase)
		panic("Failed to remap core resources");

	/* make sure to unprotect the memory region where flash is located */
	ltq_ebu_w32(ltq_ebu_r32(LTQ_EBU_BUSCON0) & ~EBU_WRDIS, LTQ_EBU_BUSCON0);

	/* add our generic xway घड़ीs */
	clkdev_add_pmu("10000000.fpi", शून्य, 0, 0, PMU_FPI);
	clkdev_add_pmu("1e100a00.gptu", शून्य, 1, 0, PMU_GPT);
	clkdev_add_pmu("1e100bb0.stp", शून्य, 1, 0, PMU_STP);
	clkdev_add_pmu("1e100c00.serial", शून्य, 0, 0, PMU_ASC1);
	clkdev_add_pmu("1e104100.dma", शून्य, 1, 0, PMU_DMA);
	clkdev_add_pmu("1e100800.spi", शून्य, 1, 0, PMU_SPI);
	clkdev_add_pmu("1e105300.ebu", शून्य, 0, 0, PMU_EBU);
	clkdev_add_clkout();

	/* add the soc dependent घड़ीs */
	अगर (of_machine_is_compatible("lantiq,vr9")) अणु
		अगरccr = CGU_IFCCR_VR9;
		pcicr = CGU_PCICR_VR9;
	पूर्ण अन्यथा अणु
		clkdev_add_pmu("1e180000.etop", शून्य, 1, 0, PMU_PPE);
	पूर्ण

	अगर (!of_machine_is_compatible("lantiq,ase"))
		clkdev_add_pci();

	अगर (of_machine_is_compatible("lantiq,grx390") ||
	    of_machine_is_compatible("lantiq,ar10")) अणु
		clkdev_add_pmu("1e108000.switch", "gphy0", 0, 0, PMU_GPHY0);
		clkdev_add_pmu("1e108000.switch", "gphy1", 0, 0, PMU_GPHY1);
		clkdev_add_pmu("1e108000.switch", "gphy2", 0, 0, PMU_GPHY2);
		clkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 2, PMU_ANALOG_USB0_P);
		clkdev_add_pmu("1f203034.usb2-phy", "phy", 1, 2, PMU_ANALOG_USB1_P);
		/* rc 0 */
		clkdev_add_pmu("1f106800.phy", "phy", 1, 2, PMU_ANALOG_PCIE0_P);
		clkdev_add_pmu("1d900000.pcie", "msi", 1, 1, PMU1_PCIE_MSI);
		clkdev_add_pmu("1f106800.phy", "pdi", 1, 1, PMU1_PCIE_PDI);
		clkdev_add_pmu("1d900000.pcie", "ctl", 1, 1, PMU1_PCIE_CTL);
		/* rc 1 */
		clkdev_add_pmu("1f700400.phy", "phy", 1, 2, PMU_ANALOG_PCIE1_P);
		clkdev_add_pmu("19000000.pcie", "msi", 1, 1, PMU1_PCIE1_MSI);
		clkdev_add_pmu("1f700400.phy", "pdi", 1, 1, PMU1_PCIE1_PDI);
		clkdev_add_pmu("19000000.pcie", "ctl", 1, 1, PMU1_PCIE1_CTL);
	पूर्ण

	अगर (of_machine_is_compatible("lantiq,ase")) अणु
		अगर (ltq_cgu_r32(CGU_SYS) & (1 << 5))
			clkdev_add_अटल(CLOCK_266M, CLOCK_133M,
						CLOCK_133M, CLOCK_266M);
		अन्यथा
			clkdev_add_अटल(CLOCK_133M, CLOCK_133M,
						CLOCK_133M, CLOCK_133M);
		clkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0);
		clkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		clkdev_add_pmu("1e180000.etop", "ppe", 1, 0, PMU_PPE);
		clkdev_add_cgu("1e180000.etop", "ephycgu", CGU_EPHY);
		clkdev_add_pmu("1e180000.etop", "ephy", 1, 0, PMU_EPHY);
		clkdev_add_pmu("1e103000.sdio", शून्य, 1, 0, PMU_ASE_SDIO);
		clkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
	पूर्ण अन्यथा अगर (of_machine_is_compatible("lantiq,grx390")) अणु
		clkdev_add_अटल(ltq_grx390_cpu_hz(), ltq_grx390_fpi_hz(),
				  ltq_grx390_fpi_hz(), ltq_grx390_pp32_hz());
		clkdev_add_pmu("1e108000.switch", "gphy3", 0, 0, PMU_GPHY3);
		clkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0);
		clkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1);
		/* rc 2 */
		clkdev_add_pmu("1f106a00.pcie", "phy", 1, 2, PMU_ANALOG_PCIE2_P);
		clkdev_add_pmu("1a800000.pcie", "msi", 1, 1, PMU1_PCIE2_MSI);
		clkdev_add_pmu("1f106a00.pcie", "pdi", 1, 1, PMU1_PCIE2_PDI);
		clkdev_add_pmu("1a800000.pcie", "ctl", 1, 1, PMU1_PCIE2_CTL);
		clkdev_add_pmu("1e10b308.eth", शून्य, 0, 0, PMU_SWITCH | PMU_PPE_DP);
		clkdev_add_pmu("1da00000.usif", "NULL", 1, 0, PMU_USIF);
		clkdev_add_pmu("1e103100.deu", शून्य, 1, 0, PMU_DEU);
	पूर्ण अन्यथा अगर (of_machine_is_compatible("lantiq,ar10")) अणु
		clkdev_add_अटल(ltq_ar10_cpu_hz(), ltq_ar10_fpi_hz(),
				  ltq_ar10_fpi_hz(), ltq_ar10_pp32_hz());
		clkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0);
		clkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1);
		clkdev_add_pmu("1e10b308.eth", शून्य, 0, 0, PMU_SWITCH |
			       PMU_PPE_DP | PMU_PPE_TC);
		clkdev_add_pmu("1da00000.usif", "NULL", 1, 0, PMU_USIF);
		clkdev_add_pmu("1e103100.deu", शून्य, 1, 0, PMU_DEU);
		clkdev_add_pmu("1e116000.mei", "afe", 1, 2, PMU_ANALOG_DSL_AFE);
		clkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
	पूर्ण अन्यथा अगर (of_machine_is_compatible("lantiq,vr9")) अणु
		clkdev_add_अटल(ltq_vr9_cpu_hz(), ltq_vr9_fpi_hz(),
				ltq_vr9_fpi_hz(), ltq_vr9_pp32_hz());
		clkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		clkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0 | PMU_AHBM);
		clkdev_add_pmu("1f203034.usb2-phy", "phy", 1, 0, PMU_USB1_P);
		clkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1 | PMU_AHBM);
		clkdev_add_pmu("1f106800.phy", "phy", 1, 1, PMU1_PCIE_PHY);
		clkdev_add_pmu("1d900000.pcie", "bus", 1, 0, PMU_PCIE_CLK);
		clkdev_add_pmu("1d900000.pcie", "msi", 1, 1, PMU1_PCIE_MSI);
		clkdev_add_pmu("1f106800.phy", "pdi", 1, 1, PMU1_PCIE_PDI);
		clkdev_add_pmu("1d900000.pcie", "ctl", 1, 1, PMU1_PCIE_CTL);
		clkdev_add_pmu(शून्य, "ahb", 1, 0, PMU_AHBM | PMU_AHBS);

		clkdev_add_pmu("1da00000.usif", "NULL", 1, 0, PMU_USIF);
		clkdev_add_pmu("1e10b308.eth", शून्य, 0, 0,
				PMU_SWITCH | PMU_PPE_DPLUS | PMU_PPE_DPLUM |
				PMU_PPE_EMA | PMU_PPE_TC | PMU_PPE_SLL01 |
				PMU_PPE_QSB | PMU_PPE_TOP);
		clkdev_add_pmu("1e108000.switch", "gphy0", 0, 0, PMU_GPHY);
		clkdev_add_pmu("1e108000.switch", "gphy1", 0, 0, PMU_GPHY);
		clkdev_add_pmu("1e103000.sdio", शून्य, 1, 0, PMU_SDIO);
		clkdev_add_pmu("1e103100.deu", शून्य, 1, 0, PMU_DEU);
		clkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
	पूर्ण अन्यथा अगर (of_machine_is_compatible("lantiq,ar9")) अणु
		clkdev_add_अटल(ltq_ar9_cpu_hz(), ltq_ar9_fpi_hz(),
				ltq_ar9_fpi_hz(), CLOCK_250M);
		clkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		clkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0 | PMU_AHBM);
		clkdev_add_pmu("1f203034.usb2-phy", "phy", 1, 0, PMU_USB1_P);
		clkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1 | PMU_AHBM);
		clkdev_add_pmu("1e180000.etop", "switch", 1, 0, PMU_SWITCH);
		clkdev_add_pmu("1e103000.sdio", शून्य, 1, 0, PMU_SDIO);
		clkdev_add_pmu("1e103100.deu", शून्य, 1, 0, PMU_DEU);
		clkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
		clkdev_add_pmu("1e100400.serial", शून्य, 1, 0, PMU_ASC0);
	पूर्ण अन्यथा अणु
		clkdev_add_अटल(ltq_danube_cpu_hz(), ltq_danube_fpi_hz(),
				ltq_danube_fpi_hz(), ltq_danube_pp32_hz());
		clkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0 | PMU_AHBM);
		clkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		clkdev_add_pmu("1e103000.sdio", शून्य, 1, 0, PMU_SDIO);
		clkdev_add_pmu("1e103100.deu", शून्य, 1, 0, PMU_DEU);
		clkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
		clkdev_add_pmu("1e100400.serial", शून्य, 1, 0, PMU_ASC0);
	पूर्ण
पूर्ण
