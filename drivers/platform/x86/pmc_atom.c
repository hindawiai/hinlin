<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Atom SOC Power Management Controller Driver
 * Copyright (c) 2014, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/x86/clk-pmc-atom.h>
#समावेश <linux/platक्रमm_data/x86/pmc_atom.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>

काष्ठा pmc_bit_map अणु
	स्थिर अक्षर *name;
	u32 bit_mask;
पूर्ण;

काष्ठा pmc_reg_map अणु
	स्थिर काष्ठा pmc_bit_map *d3_sts_0;
	स्थिर काष्ठा pmc_bit_map *d3_sts_1;
	स्थिर काष्ठा pmc_bit_map *func_dis;
	स्थिर काष्ठा pmc_bit_map *func_dis_2;
	स्थिर काष्ठा pmc_bit_map *pss;
पूर्ण;

काष्ठा pmc_data अणु
	स्थिर काष्ठा pmc_reg_map *map;
	स्थिर काष्ठा pmc_clk *clks;
पूर्ण;

काष्ठा pmc_dev अणु
	u32 base_addr;
	व्योम __iomem *regmap;
	स्थिर काष्ठा pmc_reg_map *map;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dbgfs_dir;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
	bool init;
पूर्ण;

अटल काष्ठा pmc_dev pmc_device;
अटल u32 acpi_base_addr;

अटल स्थिर काष्ठा pmc_clk byt_clks[] = अणु
	अणु
		.name = "xtal",
		.freq = 25000000,
		.parent_name = शून्य,
	पूर्ण,
	अणु
		.name = "pll",
		.freq = 19200000,
		.parent_name = "xtal",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmc_clk cht_clks[] = अणु
	अणु
		.name = "xtal",
		.freq = 19200000,
		.parent_name = शून्य,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map d3_sts_0_map[] = अणु
	अणु"LPSS1_F0_DMA",	BIT_LPSS1_F0_DMAपूर्ण,
	अणु"LPSS1_F1_PWM1",	BIT_LPSS1_F1_PWM1पूर्ण,
	अणु"LPSS1_F2_PWM2",	BIT_LPSS1_F2_PWM2पूर्ण,
	अणु"LPSS1_F3_HSUART1",	BIT_LPSS1_F3_HSUART1पूर्ण,
	अणु"LPSS1_F4_HSUART2",	BIT_LPSS1_F4_HSUART2पूर्ण,
	अणु"LPSS1_F5_SPI",	BIT_LPSS1_F5_SPIपूर्ण,
	अणु"LPSS1_F6_Reserved",	BIT_LPSS1_F6_XXXपूर्ण,
	अणु"LPSS1_F7_Reserved",	BIT_LPSS1_F7_XXXपूर्ण,
	अणु"SCC_EMMC",		BIT_SCC_EMMCपूर्ण,
	अणु"SCC_SDIO",		BIT_SCC_SDIOपूर्ण,
	अणु"SCC_SDCARD",		BIT_SCC_SDCARDपूर्ण,
	अणु"SCC_MIPI",		BIT_SCC_MIPIपूर्ण,
	अणु"HDA",			BIT_HDAपूर्ण,
	अणु"LPE",			BIT_LPEपूर्ण,
	अणु"OTG",			BIT_OTGपूर्ण,
	अणु"USH",			BIT_USHपूर्ण,
	अणु"GBE",			BIT_GBEपूर्ण,
	अणु"SATA",		BIT_SATAपूर्ण,
	अणु"USB_EHCI",		BIT_USB_EHCIपूर्ण,
	अणु"SEC",			BIT_SECपूर्ण,
	अणु"PCIE_PORT0",		BIT_PCIE_PORT0पूर्ण,
	अणु"PCIE_PORT1",		BIT_PCIE_PORT1पूर्ण,
	अणु"PCIE_PORT2",		BIT_PCIE_PORT2पूर्ण,
	अणु"PCIE_PORT3",		BIT_PCIE_PORT3पूर्ण,
	अणु"LPSS2_F0_DMA",	BIT_LPSS2_F0_DMAपूर्ण,
	अणु"LPSS2_F1_I2C1",	BIT_LPSS2_F1_I2C1पूर्ण,
	अणु"LPSS2_F2_I2C2",	BIT_LPSS2_F2_I2C2पूर्ण,
	अणु"LPSS2_F3_I2C3",	BIT_LPSS2_F3_I2C3पूर्ण,
	अणु"LPSS2_F3_I2C4",	BIT_LPSS2_F4_I2C4पूर्ण,
	अणु"LPSS2_F5_I2C5",	BIT_LPSS2_F5_I2C5पूर्ण,
	अणु"LPSS2_F6_I2C6",	BIT_LPSS2_F6_I2C6पूर्ण,
	अणु"LPSS2_F7_I2C7",	BIT_LPSS2_F7_I2C7पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pmc_bit_map byt_d3_sts_1_map[] = अणु
	अणु"SMB",			BIT_SMBपूर्ण,
	अणु"OTG_SS_PHY",		BIT_OTG_SS_PHYपूर्ण,
	अणु"USH_SS_PHY",		BIT_USH_SS_PHYपूर्ण,
	अणु"DFX",			BIT_DFXपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pmc_bit_map cht_d3_sts_1_map[] = अणु
	अणु"SMB",			BIT_SMBपूर्ण,
	अणु"GMM",			BIT_STS_GMMपूर्ण,
	अणु"ISH",			BIT_STS_ISHपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pmc_bit_map cht_func_dis_2_map[] = अणु
	अणु"SMB",			BIT_SMBपूर्ण,
	अणु"GMM",			BIT_FD_GMMपूर्ण,
	अणु"ISH",			BIT_FD_ISHपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map byt_pss_map[] = अणु
	अणु"GBE",			PMC_PSS_BIT_GBEपूर्ण,
	अणु"SATA",		PMC_PSS_BIT_SATAपूर्ण,
	अणु"HDA",			PMC_PSS_BIT_HDAपूर्ण,
	अणु"SEC",			PMC_PSS_BIT_SECपूर्ण,
	अणु"PCIE",		PMC_PSS_BIT_PCIEपूर्ण,
	अणु"LPSS",		PMC_PSS_BIT_LPSSपूर्ण,
	अणु"LPE",			PMC_PSS_BIT_LPEपूर्ण,
	अणु"DFX",			PMC_PSS_BIT_DFXपूर्ण,
	अणु"USH_CTRL",		PMC_PSS_BIT_USH_CTRLपूर्ण,
	अणु"USH_SUS",		PMC_PSS_BIT_USH_SUSपूर्ण,
	अणु"USH_VCCS",		PMC_PSS_BIT_USH_VCCSपूर्ण,
	अणु"USH_VCCA",		PMC_PSS_BIT_USH_VCCAपूर्ण,
	अणु"OTG_CTRL",		PMC_PSS_BIT_OTG_CTRLपूर्ण,
	अणु"OTG_VCCS",		PMC_PSS_BIT_OTG_VCCSपूर्ण,
	अणु"OTG_VCCA_CLK",	PMC_PSS_BIT_OTG_VCCA_CLKपूर्ण,
	अणु"OTG_VCCA",		PMC_PSS_BIT_OTG_VCCAपूर्ण,
	अणु"USB",			PMC_PSS_BIT_USBपूर्ण,
	अणु"USB_SUS",		PMC_PSS_BIT_USB_SUSपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmc_bit_map cht_pss_map[] = अणु
	अणु"SATA",		PMC_PSS_BIT_SATAपूर्ण,
	अणु"HDA",			PMC_PSS_BIT_HDAपूर्ण,
	अणु"SEC",			PMC_PSS_BIT_SECपूर्ण,
	अणु"PCIE",		PMC_PSS_BIT_PCIEपूर्ण,
	अणु"LPSS",		PMC_PSS_BIT_LPSSपूर्ण,
	अणु"LPE",			PMC_PSS_BIT_LPEपूर्ण,
	अणु"UFS",			PMC_PSS_BIT_CHT_UFSपूर्ण,
	अणु"UXD",			PMC_PSS_BIT_CHT_UXDपूर्ण,
	अणु"UXD_FD",		PMC_PSS_BIT_CHT_UXD_FDपूर्ण,
	अणु"UX_ENG",		PMC_PSS_BIT_CHT_UX_ENGपूर्ण,
	अणु"USB_SUS",		PMC_PSS_BIT_CHT_USB_SUSपूर्ण,
	अणु"GMM",			PMC_PSS_BIT_CHT_GMMपूर्ण,
	अणु"ISH",			PMC_PSS_BIT_CHT_ISHपूर्ण,
	अणु"DFX_MASTER",		PMC_PSS_BIT_CHT_DFX_MASTERपूर्ण,
	अणु"DFX_CLUSTER1",	PMC_PSS_BIT_CHT_DFX_CLUSTER1पूर्ण,
	अणु"DFX_CLUSTER2",	PMC_PSS_BIT_CHT_DFX_CLUSTER2पूर्ण,
	अणु"DFX_CLUSTER3",	PMC_PSS_BIT_CHT_DFX_CLUSTER3पूर्ण,
	अणु"DFX_CLUSTER4",	PMC_PSS_BIT_CHT_DFX_CLUSTER4पूर्ण,
	अणु"DFX_CLUSTER5",	PMC_PSS_BIT_CHT_DFX_CLUSTER5पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmc_reg_map byt_reg_map = अणु
	.d3_sts_0	= d3_sts_0_map,
	.d3_sts_1	= byt_d3_sts_1_map,
	.func_dis	= d3_sts_0_map,
	.func_dis_2	= byt_d3_sts_1_map,
	.pss		= byt_pss_map,
पूर्ण;

अटल स्थिर काष्ठा pmc_reg_map cht_reg_map = अणु
	.d3_sts_0	= d3_sts_0_map,
	.d3_sts_1	= cht_d3_sts_1_map,
	.func_dis	= d3_sts_0_map,
	.func_dis_2	= cht_func_dis_2_map,
	.pss		= cht_pss_map,
पूर्ण;

अटल स्थिर काष्ठा pmc_data byt_data = अणु
	.map = &byt_reg_map,
	.clks = byt_clks,
पूर्ण;

अटल स्थिर काष्ठा pmc_data cht_data = अणु
	.map = &cht_reg_map,
	.clks = cht_clks,
पूर्ण;

अटल अंतरभूत u32 pmc_reg_पढ़ो(काष्ठा pmc_dev *pmc, पूर्णांक reg_offset)
अणु
	वापस पढ़ोl(pmc->regmap + reg_offset);
पूर्ण

अटल अंतरभूत व्योम pmc_reg_ग_लिखो(काष्ठा pmc_dev *pmc, पूर्णांक reg_offset, u32 val)
अणु
	ग_लिखोl(val, pmc->regmap + reg_offset);
पूर्ण

पूर्णांक pmc_atom_पढ़ो(पूर्णांक offset, u32 *value)
अणु
	काष्ठा pmc_dev *pmc = &pmc_device;

	अगर (!pmc->init)
		वापस -ENODEV;

	*value = pmc_reg_पढ़ो(pmc, offset);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmc_atom_पढ़ो);

पूर्णांक pmc_atom_ग_लिखो(पूर्णांक offset, u32 value)
अणु
	काष्ठा pmc_dev *pmc = &pmc_device;

	अगर (!pmc->init)
		वापस -ENODEV;

	pmc_reg_ग_लिखो(pmc, offset, value);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmc_atom_ग_लिखो);

अटल व्योम pmc_घातer_off(व्योम)
अणु
	u16	pm1_cnt_port;
	u32	pm1_cnt_value;

	pr_info("Preparing to enter system sleep state S5\n");

	pm1_cnt_port = acpi_base_addr + PM1_CNT;

	pm1_cnt_value = inl(pm1_cnt_port);
	pm1_cnt_value &= SLEEP_TYPE_MASK;
	pm1_cnt_value |= SLEEP_TYPE_S5;
	pm1_cnt_value |= SLEEP_ENABLE;

	outl(pm1_cnt_value, pm1_cnt_port);
पूर्ण

अटल व्योम pmc_hw_reg_setup(काष्ठा pmc_dev *pmc)
अणु
	/*
	 * Disable PMC S0IX_WAKE_EN events coming from:
	 * - LPC घड़ी run
	 * - GPIO_SUS ored dedicated IRQs
	 * - GPIO_SCORE ored dedicated IRQs
	 * - GPIO_SUS shared IRQ
	 * - GPIO_SCORE shared IRQ
	 */
	pmc_reg_ग_लिखो(pmc, PMC_S0IX_WAKE_EN, (u32)PMC_WAKE_EN_SETTING);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम pmc_dev_state_prपूर्णांक(काष्ठा seq_file *s, पूर्णांक reg_index,
				u32 sts, स्थिर काष्ठा pmc_bit_map *sts_map,
				u32 fd, स्थिर काष्ठा pmc_bit_map *fd_map)
अणु
	पूर्णांक offset = PMC_REG_BIT_WIDTH * reg_index;
	पूर्णांक index;

	क्रम (index = 0; sts_map[index].name; index++) अणु
		seq_म_लिखो(s, "Dev: %-2d - %-32s\tState: %s [%s]\n",
			offset + index, sts_map[index].name,
			fd_map[index].bit_mask & fd ?  "Disabled" : "Enabled ",
			sts_map[index].bit_mask & sts ?  "D3" : "D0");
	पूर्ण
पूर्ण

अटल पूर्णांक pmc_dev_state_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmc = s->निजी;
	स्थिर काष्ठा pmc_reg_map *m = pmc->map;
	u32 func_dis, func_dis_2;
	u32 d3_sts_0, d3_sts_1;

	func_dis = pmc_reg_पढ़ो(pmc, PMC_FUNC_DIS);
	func_dis_2 = pmc_reg_पढ़ो(pmc, PMC_FUNC_DIS_2);
	d3_sts_0 = pmc_reg_पढ़ो(pmc, PMC_D3_STS_0);
	d3_sts_1 = pmc_reg_पढ़ो(pmc, PMC_D3_STS_1);

	/* Low part */
	pmc_dev_state_prपूर्णांक(s, 0, d3_sts_0, m->d3_sts_0, func_dis, m->func_dis);

	/* High part */
	pmc_dev_state_prपूर्णांक(s, 1, d3_sts_1, m->d3_sts_1, func_dis_2, m->func_dis_2);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pmc_dev_state);

अटल पूर्णांक pmc_pss_state_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmc = s->निजी;
	स्थिर काष्ठा pmc_bit_map *map = pmc->map->pss;
	u32 pss = pmc_reg_पढ़ो(pmc, PMC_PSS);
	पूर्णांक index;

	क्रम (index = 0; map[index].name; index++) अणु
		seq_म_लिखो(s, "Island: %-2d - %-32s\tState: %s\n",
			index, map[index].name,
			map[index].bit_mask & pss ? "Off" : "On");
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pmc_pss_state);

अटल पूर्णांक pmc_sleep_पंचांगr_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा pmc_dev *pmc = s->निजी;
	u64 s0ir_पंचांगr, s0i1_पंचांगr, s0i2_पंचांगr, s0i3_पंचांगr, s0_पंचांगr;

	s0ir_पंचांगr = (u64)pmc_reg_पढ़ो(pmc, PMC_S0IR_TMR) << PMC_TMR_SHIFT;
	s0i1_पंचांगr = (u64)pmc_reg_पढ़ो(pmc, PMC_S0I1_TMR) << PMC_TMR_SHIFT;
	s0i2_पंचांगr = (u64)pmc_reg_पढ़ो(pmc, PMC_S0I2_TMR) << PMC_TMR_SHIFT;
	s0i3_पंचांगr = (u64)pmc_reg_पढ़ो(pmc, PMC_S0I3_TMR) << PMC_TMR_SHIFT;
	s0_पंचांगr = (u64)pmc_reg_पढ़ो(pmc, PMC_S0_TMR) << PMC_TMR_SHIFT;

	seq_म_लिखो(s, "S0IR Residency:\t%lldus\n", s0ir_पंचांगr);
	seq_म_लिखो(s, "S0I1 Residency:\t%lldus\n", s0i1_पंचांगr);
	seq_म_लिखो(s, "S0I2 Residency:\t%lldus\n", s0i2_पंचांगr);
	seq_म_लिखो(s, "S0I3 Residency:\t%lldus\n", s0i3_पंचांगr);
	seq_म_लिखो(s, "S0   Residency:\t%lldus\n", s0_पंचांगr);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pmc_sleep_पंचांगr);

अटल व्योम pmc_dbgfs_रेजिस्टर(काष्ठा pmc_dev *pmc)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("pmc_atom", शून्य);

	pmc->dbgfs_dir = dir;

	debugfs_create_file("dev_state", S_IFREG | S_IRUGO, dir, pmc,
			    &pmc_dev_state_fops);
	debugfs_create_file("pss_state", S_IFREG | S_IRUGO, dir, pmc,
			    &pmc_pss_state_fops);
	debugfs_create_file("sleep_state", S_IFREG | S_IRUGO, dir, pmc,
			    &pmc_sleep_पंचांगr_fops);
पूर्ण
#अन्यथा
अटल व्योम pmc_dbgfs_रेजिस्टर(काष्ठा pmc_dev *pmc)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/*
 * Some प्रणालीs need one or more of their pmc_plt_clks to be
 * marked as critical.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id critclk_प्रणालीs[] = अणु
	अणु
		/* pmc_plt_clk0 is used क्रम an बाह्यal HSIC USB HUB */
		.ident = "MPL CEC1x",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MPL AG"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CEC10 Family"),
		पूर्ण,
	पूर्ण,
	अणु
		/* pmc_plt_clk0 - 3 are used क्रम the 4 ethernet controllers */
		.ident = "Lex 3I380D",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Lex BayTrail"),
			DMI_MATCH(DMI_PRODUCT_NAME, "3I380D"),
		पूर्ण,
	पूर्ण,
	अणु
		/* pmc_plt_clk* - are used क्रम ethernet controllers */
		.ident = "Lex 2I385SW",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Lex BayTrail"),
			DMI_MATCH(DMI_PRODUCT_NAME, "2I385SW"),
		पूर्ण,
	पूर्ण,
	अणु
		/* pmc_plt_clk* - are used क्रम ethernet controllers */
		.ident = "Beckhoff Baytrail",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Beckhoff Automation"),
			DMI_MATCH(DMI_PRODUCT_FAMILY, "CBxx63"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "SIMATIC IPC227E",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SIEMENS AG"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "6ES7647-8B"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "SIMATIC IPC277E",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SIEMENS AG"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "6AV7882-0"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "CONNECT X300",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SIEMENS AG"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "A5E45074588"),
		पूर्ण,
	पूर्ण,

	अणु /*sentinel*/ पूर्ण
पूर्ण;

अटल पूर्णांक pmc_setup_clks(काष्ठा pci_dev *pdev, व्योम __iomem *pmc_regmap,
			  स्थिर काष्ठा pmc_data *pmc_data)
अणु
	काष्ठा platक्रमm_device *clkdev;
	काष्ठा pmc_clk_data *clk_data;
	स्थिर काष्ठा dmi_प्रणाली_id *d = dmi_first_match(critclk_प्रणालीs);

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->base = pmc_regmap; /* offset is added by client */
	clk_data->clks = pmc_data->clks;
	अगर (d) अणु
		clk_data->critical = true;
		pr_info("%s critclks quirk enabled\n", d->ident);
	पूर्ण

	clkdev = platक्रमm_device_रेजिस्टर_data(&pdev->dev, "clk-pmc-atom",
					       PLATFORM_DEVID_NONE,
					       clk_data, माप(*clk_data));
	अगर (IS_ERR(clkdev)) अणु
		kमुक्त(clk_data);
		वापस PTR_ERR(clkdev);
	पूर्ण

	kमुक्त(clk_data);

	वापस 0;
पूर्ण

अटल पूर्णांक pmc_setup_dev(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा pmc_dev *pmc = &pmc_device;
	स्थिर काष्ठा pmc_data *data = (काष्ठा pmc_data *)ent->driver_data;
	स्थिर काष्ठा pmc_reg_map *map = data->map;
	पूर्णांक ret;

	/* Obtain ACPI base address */
	pci_पढ़ो_config_dword(pdev, ACPI_BASE_ADDR_OFFSET, &acpi_base_addr);
	acpi_base_addr &= ACPI_BASE_ADDR_MASK;

	/* Install घातer off function */
	अगर (acpi_base_addr != 0 && pm_घातer_off == शून्य)
		pm_घातer_off = pmc_घातer_off;

	pci_पढ़ो_config_dword(pdev, PMC_BASE_ADDR_OFFSET, &pmc->base_addr);
	pmc->base_addr &= PMC_BASE_ADDR_MASK;

	pmc->regmap = ioremap(pmc->base_addr, PMC_MMIO_REG_LEN);
	अगर (!pmc->regmap) अणु
		dev_err(&pdev->dev, "error: ioremap failed\n");
		वापस -ENOMEM;
	पूर्ण

	pmc->map = map;

	/* PMC hardware रेजिस्टरs setup */
	pmc_hw_reg_setup(pmc);

	pmc_dbgfs_रेजिस्टर(pmc);

	/* Register platक्रमm घड़ीs - PMC_PLT_CLK [0..5] */
	ret = pmc_setup_clks(pdev, pmc->regmap, data);
	अगर (ret)
		dev_warn(&pdev->dev, "platform clocks register failed: %d\n",
			 ret);

	pmc->init = true;
	वापस ret;
पूर्ण

/*
 * Data क्रम PCI driver पूर्णांकerface
 *
 * used by pci_match_id() call below.
 */
अटल स्थिर काष्ठा pci_device_id pmc_pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_VLV_PMC), (kernel_uदीर्घ_t)&byt_data पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_CHT_PMC), (kernel_uदीर्घ_t)&cht_data पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल पूर्णांक __init pmc_atom_init(व्योम)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	स्थिर काष्ठा pci_device_id *ent;

	/* We look क्रम our device - PCU PMC
	 * we assume that there is max. one device.
	 *
	 * We can't use plain pci_driver mechanism,
	 * as the device is really a multiple function device,
	 * मुख्य driver that binds to the pci_device is lpc_ich
	 * and have to find & bind to the device this way.
	 */
	क्रम_each_pci_dev(pdev) अणु
		ent = pci_match_id(pmc_pci_ids, pdev);
		अगर (ent)
			वापस pmc_setup_dev(pdev, ent);
	पूर्ण
	/* Device not found. */
	वापस -ENODEV;
पूर्ण

device_initcall(pmc_atom_init);

/*
MODULE_AUTHOR("Aubrey Li <aubrey.li@linux.intel.com>");
MODULE_DESCRIPTION("Intel Atom SOC Power Management Controller Interface");
MODULE_LICENSE("GPL v2");
*/
