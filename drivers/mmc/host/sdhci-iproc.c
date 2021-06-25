<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*
 * iProc SDHCI platक्रमm driver
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश "sdhci-pltfm.h"

काष्ठा sdhci_iproc_data अणु
	स्थिर काष्ठा sdhci_pltfm_data *pdata;
	u32 caps;
	u32 caps1;
	u32 mmc_caps;
पूर्ण;

काष्ठा sdhci_iproc_host अणु
	स्थिर काष्ठा sdhci_iproc_data *data;
	u32 shaकरोw_cmd;
	u32 shaकरोw_blk;
	bool is_cmd_shaकरोwed;
	bool is_blk_shaकरोwed;
पूर्ण;

#घोषणा REG_OFFSET_IN_BITS(reg) ((reg) << 3 & 0x18)

अटल अंतरभूत u32 sdhci_iproc_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 val = पढ़ोl(host->ioaddr + reg);

	pr_debug("%s: readl [0x%02x] 0x%08x\n",
		 mmc_hostname(host->mmc), reg, val);
	वापस val;
पूर्ण

अटल u16 sdhci_iproc_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_iproc_host *iproc_host = sdhci_pltfm_priv(pltfm_host);
	u32 val;
	u16 word;

	अगर ((reg == SDHCI_TRANSFER_MODE) && iproc_host->is_cmd_shaकरोwed) अणु
		/* Get the saved transfer mode */
		val = iproc_host->shaकरोw_cmd;
	पूर्ण अन्यथा अगर ((reg == SDHCI_BLOCK_SIZE || reg == SDHCI_BLOCK_COUNT) &&
		   iproc_host->is_blk_shaकरोwed) अणु
		/* Get the saved block info */
		val = iproc_host->shaकरोw_blk;
	पूर्ण अन्यथा अणु
		val = sdhci_iproc_पढ़ोl(host, (reg & ~3));
	पूर्ण
	word = val >> REG_OFFSET_IN_BITS(reg) & 0xffff;
	वापस word;
पूर्ण

अटल u8 sdhci_iproc_पढ़ोb(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 val = sdhci_iproc_पढ़ोl(host, (reg & ~3));
	u8 byte = val >> REG_OFFSET_IN_BITS(reg) & 0xff;
	वापस byte;
पूर्ण

अटल अंतरभूत व्योम sdhci_iproc_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	pr_debug("%s: writel [0x%02x] 0x%08x\n",
		 mmc_hostname(host->mmc), reg, val);

	ग_लिखोl(val, host->ioaddr + reg);

	अगर (host->घड़ी <= 400000) अणु
		/* Round up to micro-second four SD घड़ी delay */
		अगर (host->घड़ी)
			udelay((4 * 1000000 + host->घड़ी - 1) / host->घड़ी);
		अन्यथा
			udelay(10);
	पूर्ण
पूर्ण

/*
 * The Arasan has a bugette whereby it may lose the content of successive
 * ग_लिखोs to the same रेजिस्टर that are within two SD-card घड़ी cycles of
 * each other (a घड़ी करोमुख्य crossing problem). The data
 * रेजिस्टर करोes not have this problem, which is just as well - otherwise we'd
 * have to nobble the DMA engine too.
 *
 * This wouldn't be a problem with the code except that we can only ग_लिखो the
 * controller with 32-bit ग_लिखोs.  So two dअगरferent 16-bit रेजिस्टरs are
 * written back to back creates the problem.
 *
 * In reality, this only happens when SDHCI_BLOCK_SIZE and SDHCI_BLOCK_COUNT
 * are written followed by SDHCI_TRANSFER_MODE and SDHCI_COMMAND.
 * The BLOCK_SIZE and BLOCK_COUNT are meaningless until a command issued so
 * the work around can be further optimized. We can keep shaकरोw values of
 * BLOCK_SIZE, BLOCK_COUNT, and TRANSFER_MODE until a COMMAND is issued.
 * Then, ग_लिखो the BLOCK_SIZE+BLOCK_COUNT in a single 32-bit ग_लिखो followed
 * by the TRANSFER+COMMAND in another 32-bit ग_लिखो.
 */
अटल व्योम sdhci_iproc_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_iproc_host *iproc_host = sdhci_pltfm_priv(pltfm_host);
	u32 word_shअगरt = REG_OFFSET_IN_BITS(reg);
	u32 mask = 0xffff << word_shअगरt;
	u32 oldval, newval;

	अगर (reg == SDHCI_COMMAND) अणु
		/* Write the block now as we are issuing a command */
		अगर (iproc_host->is_blk_shaकरोwed) अणु
			sdhci_iproc_ग_लिखोl(host, iproc_host->shaकरोw_blk,
				SDHCI_BLOCK_SIZE);
			iproc_host->is_blk_shaकरोwed = false;
		पूर्ण
		oldval = iproc_host->shaकरोw_cmd;
		iproc_host->is_cmd_shaकरोwed = false;
	पूर्ण अन्यथा अगर ((reg == SDHCI_BLOCK_SIZE || reg == SDHCI_BLOCK_COUNT) &&
		   iproc_host->is_blk_shaकरोwed) अणु
		/* Block size and count are stored in shaकरोw reg */
		oldval = iproc_host->shaकरोw_blk;
	पूर्ण अन्यथा अणु
		/* Read reg, all other रेजिस्टरs are not shaकरोwed */
		oldval = sdhci_iproc_पढ़ोl(host, (reg & ~3));
	पूर्ण
	newval = (oldval & ~mask) | (val << word_shअगरt);

	अगर (reg == SDHCI_TRANSFER_MODE) अणु
		/* Save the transfer mode until the command is issued */
		iproc_host->shaकरोw_cmd = newval;
		iproc_host->is_cmd_shaकरोwed = true;
	पूर्ण अन्यथा अगर (reg == SDHCI_BLOCK_SIZE || reg == SDHCI_BLOCK_COUNT) अणु
		/* Save the block info until the command is issued */
		iproc_host->shaकरोw_blk = newval;
		iproc_host->is_blk_shaकरोwed = true;
	पूर्ण अन्यथा अणु
		/* Command or other regular 32-bit ग_लिखो */
		sdhci_iproc_ग_लिखोl(host, newval, reg & ~3);
	पूर्ण
पूर्ण

अटल व्योम sdhci_iproc_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	u32 oldval = sdhci_iproc_पढ़ोl(host, (reg & ~3));
	u32 byte_shअगरt = REG_OFFSET_IN_BITS(reg);
	u32 mask = 0xff << byte_shअगरt;
	u32 newval = (oldval & ~mask) | (val << byte_shअगरt);

	sdhci_iproc_ग_लिखोl(host, newval, reg & ~3);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_iproc_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	अगर (pltfm_host->clk)
		वापस sdhci_pltfm_clk_get_max_घड़ी(host);
	अन्यथा
		वापस pltfm_host->घड़ी;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_iproc_ops = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.get_max_घड़ी = sdhci_iproc_get_max_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_iproc_32only_ops = अणु
	.पढ़ो_l = sdhci_iproc_पढ़ोl,
	.पढ़ो_w = sdhci_iproc_पढ़ोw,
	.पढ़ो_b = sdhci_iproc_पढ़ोb,
	.ग_लिखो_l = sdhci_iproc_ग_लिखोl,
	.ग_लिखो_w = sdhci_iproc_ग_लिखोw,
	.ग_लिखो_b = sdhci_iproc_ग_लिखोb,
	.set_घड़ी = sdhci_set_घड़ी,
	.get_max_घड़ी = sdhci_iproc_get_max_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_iproc_cygnus_pltfm_data = अणु
	.quirks = SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_NO_HISPD_BIT,
	.quirks2 = SDHCI_QUIRK2_ACMD23_BROKEN | SDHCI_QUIRK2_HOST_OFF_CARD_ON,
	.ops = &sdhci_iproc_32only_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_iproc_data iproc_cygnus_data = अणु
	.pdata = &sdhci_iproc_cygnus_pltfm_data,
	.caps = ((0x1 << SDHCI_MAX_BLOCK_SHIFT)
			& SDHCI_MAX_BLOCK_MASK) |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_VDD_180 |
		SDHCI_CAN_DO_SUSPEND |
		SDHCI_CAN_DO_HISPD |
		SDHCI_CAN_DO_ADMA2 |
		SDHCI_CAN_DO_SDMA,
	.caps1 = SDHCI_DRIVER_TYPE_C |
		 SDHCI_DRIVER_TYPE_D |
		 SDHCI_SUPPORT_DDR50,
	.mmc_caps = MMC_CAP_1_8V_DDR,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_iproc_pltfm_data = अणु
	.quirks = SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12 |
		  SDHCI_QUIRK_NO_HISPD_BIT,
	.quirks2 = SDHCI_QUIRK2_ACMD23_BROKEN,
	.ops = &sdhci_iproc_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_iproc_data iproc_data = अणु
	.pdata = &sdhci_iproc_pltfm_data,
	.caps = ((0x1 << SDHCI_MAX_BLOCK_SHIFT)
			& SDHCI_MAX_BLOCK_MASK) |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_VDD_180 |
		SDHCI_CAN_DO_SUSPEND |
		SDHCI_CAN_DO_HISPD |
		SDHCI_CAN_DO_ADMA2 |
		SDHCI_CAN_DO_SDMA,
	.caps1 = SDHCI_DRIVER_TYPE_C |
		 SDHCI_DRIVER_TYPE_D |
		 SDHCI_SUPPORT_DDR50,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_bcm2835_pltfm_data = अणु
	.quirks = SDHCI_QUIRK_BROKEN_CARD_DETECTION |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_MISSING_CAPS |
		  SDHCI_QUIRK_NO_HISPD_BIT,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops = &sdhci_iproc_32only_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_iproc_data bcm2835_data = अणु
	.pdata = &sdhci_bcm2835_pltfm_data,
	.caps = ((0x1 << SDHCI_MAX_BLOCK_SHIFT)
			& SDHCI_MAX_BLOCK_MASK) |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_DO_HISPD,
	.caps1 = SDHCI_DRIVER_TYPE_A |
		 SDHCI_DRIVER_TYPE_C,
	.mmc_caps = 0x00000000,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_iproc_bcm2711_ops = अणु
	.पढ़ो_l = sdhci_iproc_पढ़ोl,
	.पढ़ो_w = sdhci_iproc_पढ़ोw,
	.पढ़ो_b = sdhci_iproc_पढ़ोb,
	.ग_लिखो_l = sdhci_iproc_ग_लिखोl,
	.ग_लिखो_w = sdhci_iproc_ग_लिखोw,
	.ग_लिखो_b = sdhci_iproc_ग_लिखोb,
	.set_घड़ी = sdhci_set_घड़ी,
	.set_घातer = sdhci_set_घातer_and_bus_voltage,
	.get_max_घड़ी = sdhci_iproc_get_max_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_bcm2711_pltfm_data = अणु
	.quirks = SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12,
	.ops = &sdhci_iproc_bcm2711_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_iproc_data bcm2711_data = अणु
	.pdata = &sdhci_bcm2711_pltfm_data,
	.mmc_caps = MMC_CAP_3_3V_DDR,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_iproc_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-sdhci", .data = &bcm2835_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-emmc2", .data = &bcm2711_data पूर्ण,
	अणु .compatible = "brcm,sdhci-iproc-cygnus", .data = &iproc_cygnus_dataपूर्ण,
	अणु .compatible = "brcm,sdhci-iproc", .data = &iproc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_iproc_of_match);

#अगर_घोषित CONFIG_ACPI
/*
 * This is a duplicate of bcm2835_(pltfrm_)data without caps quirks
 * which are provided by the ACPI table.
 */
अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_bcm_arasan_data = अणु
	.quirks = SDHCI_QUIRK_BROKEN_CARD_DETECTION |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_NO_HISPD_BIT,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops = &sdhci_iproc_32only_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_iproc_data bcm_arasan_data = अणु
	.pdata = &sdhci_bcm_arasan_data,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id sdhci_iproc_acpi_ids[] = अणु
	अणु .id = "BRCM5871", .driver_data = (kernel_uदीर्घ_t)&iproc_cygnus_data पूर्ण,
	अणु .id = "BRCM5872", .driver_data = (kernel_uदीर्घ_t)&iproc_data पूर्ण,
	अणु .id = "BCM2847",  .driver_data = (kernel_uदीर्घ_t)&bcm_arasan_data पूर्ण,
	अणु .id = "BRCME88C", .driver_data = (kernel_uदीर्घ_t)&bcm2711_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sdhci_iproc_acpi_ids);
#पूर्ण_अगर

अटल पूर्णांक sdhci_iproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा sdhci_iproc_data *iproc_data = शून्य;
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_iproc_host *iproc_host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	पूर्णांक ret;

	iproc_data = device_get_match_data(dev);
	अगर (!iproc_data)
		वापस -ENODEV;

	host = sdhci_pltfm_init(pdev, iproc_data->pdata, माप(*iproc_host));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	iproc_host = sdhci_pltfm_priv(pltfm_host);

	iproc_host->data = iproc_data;

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err;

	sdhci_get_property(pdev);

	host->mmc->caps |= iproc_host->data->mmc_caps;

	अगर (dev->of_node) अणु
		pltfm_host->clk = devm_clk_get(dev, शून्य);
		अगर (IS_ERR(pltfm_host->clk)) अणु
			ret = PTR_ERR(pltfm_host->clk);
			जाओ err;
		पूर्ण
		ret = clk_prepare_enable(pltfm_host->clk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable host clk\n");
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (iproc_host->data->pdata->quirks & SDHCI_QUIRK_MISSING_CAPS) अणु
		host->caps = iproc_host->data->caps;
		host->caps1 = iproc_host->data->caps1;
	पूर्ण

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_clk;

	वापस 0;

err_clk:
	अगर (dev->of_node)
		clk_disable_unprepare(pltfm_host->clk);
err:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_iproc_driver = अणु
	.driver = अणु
		.name = "sdhci-iproc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_iproc_of_match,
		.acpi_match_table = ACPI_PTR(sdhci_iproc_acpi_ids),
		.pm = &sdhci_pltfm_pmops,
	पूर्ण,
	.probe = sdhci_iproc_probe,
	.हटाओ = sdhci_pltfm_unरेजिस्टर,
पूर्ण;
module_platक्रमm_driver(sdhci_iproc_driver);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("IPROC SDHCI driver");
MODULE_LICENSE("GPL v2");
