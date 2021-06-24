<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
 * sपंचांगmac HW Interface Handling
 */

#समावेश "common.h"
#समावेश "stmmac.h"
#समावेश "stmmac_ptp.h"

अटल u32 sपंचांगmac_get_id(काष्ठा sपंचांगmac_priv *priv, u32 id_reg)
अणु
	u32 reg = पढ़ोl(priv->ioaddr + id_reg);

	अगर (!reg) अणु
		dev_info(priv->device, "Version ID not available\n");
		वापस 0x0;
	पूर्ण

	dev_info(priv->device, "User ID: 0x%x, Synopsys ID: 0x%x\n",
			(अचिन्हित पूर्णांक)(reg & GENMASK(15, 8)) >> 8,
			(अचिन्हित पूर्णांक)(reg & GENMASK(7, 0)));
	वापस reg & GENMASK(7, 0);
पूर्ण

अटल u32 sपंचांगmac_get_dev_id(काष्ठा sपंचांगmac_priv *priv, u32 id_reg)
अणु
	u32 reg = पढ़ोl(priv->ioaddr + id_reg);

	अगर (!reg) अणु
		dev_info(priv->device, "Version ID not available\n");
		वापस 0x0;
	पूर्ण

	वापस (reg & GENMASK(15, 8)) >> 8;
पूर्ण

अटल व्योम sपंचांगmac_dwmac_mode_quirk(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा mac_device_info *mac = priv->hw;

	अगर (priv->chain_mode) अणु
		dev_info(priv->device, "Chain mode enabled\n");
		priv->mode = STMMAC_CHAIN_MODE;
		mac->mode = &chain_mode_ops;
	पूर्ण अन्यथा अणु
		dev_info(priv->device, "Ring mode enabled\n");
		priv->mode = STMMAC_RING_MODE;
		mac->mode = &ring_mode_ops;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_dwmac1_quirks(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा mac_device_info *mac = priv->hw;

	अगर (priv->plat->enh_desc) अणु
		dev_info(priv->device, "Enhanced/Alternate descriptors\n");

		/* GMAC older than 3.50 has no extended descriptors */
		अगर (priv->synopsys_id >= DWMAC_CORE_3_50) अणु
			dev_info(priv->device, "Enabled extended descriptors\n");
			priv->extend_desc = 1;
		पूर्ण अन्यथा अणु
			dev_warn(priv->device, "Extended descriptors not supported\n");
		पूर्ण

		mac->desc = &enh_desc_ops;
	पूर्ण अन्यथा अणु
		dev_info(priv->device, "Normal descriptors\n");
		mac->desc = &ndesc_ops;
	पूर्ण

	sपंचांगmac_dwmac_mode_quirk(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_dwmac4_quirks(काष्ठा sपंचांगmac_priv *priv)
अणु
	sपंचांगmac_dwmac_mode_quirk(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_dwxlgmac_quirks(काष्ठा sपंचांगmac_priv *priv)
अणु
	priv->hw->xlgmac = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_hwअगर_entry अणु
	bool gmac;
	bool gmac4;
	bool xgmac;
	u32 min_id;
	u32 dev_id;
	स्थिर काष्ठा sपंचांगmac_regs_off regs;
	स्थिर व्योम *desc;
	स्थिर व्योम *dma;
	स्थिर व्योम *mac;
	स्थिर व्योम *hwबारtamp;
	स्थिर व्योम *mode;
	स्थिर व्योम *tc;
	स्थिर व्योम *mmc;
	पूर्णांक (*setup)(काष्ठा sपंचांगmac_priv *priv);
	पूर्णांक (*quirks)(काष्ठा sपंचांगmac_priv *priv);
पूर्ण sपंचांगmac_hw[] = अणु
	/* NOTE: New HW versions shall go to the end of this table */
	अणु
		.gmac = false,
		.gmac4 = false,
		.xgmac = false,
		.min_id = 0,
		.regs = अणु
			.ptp_off = PTP_GMAC3_X_OFFSET,
			.mmc_off = MMC_GMAC3_X_OFFSET,
		पूर्ण,
		.desc = शून्य,
		.dma = &dwmac100_dma_ops,
		.mac = &dwmac100_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = शून्य,
		.tc = शून्य,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac100_setup,
		.quirks = sपंचांगmac_dwmac1_quirks,
	पूर्ण, अणु
		.gmac = true,
		.gmac4 = false,
		.xgmac = false,
		.min_id = 0,
		.regs = अणु
			.ptp_off = PTP_GMAC3_X_OFFSET,
			.mmc_off = MMC_GMAC3_X_OFFSET,
		पूर्ण,
		.desc = शून्य,
		.dma = &dwmac1000_dma_ops,
		.mac = &dwmac1000_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = शून्य,
		.tc = शून्य,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac1000_setup,
		.quirks = sपंचांगmac_dwmac1_quirks,
	पूर्ण, अणु
		.gmac = false,
		.gmac4 = true,
		.xgmac = false,
		.min_id = 0,
		.regs = अणु
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
		पूर्ण,
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac4_dma_ops,
		.mac = &dwmac4_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = शून्य,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac4_setup,
		.quirks = sपंचांगmac_dwmac4_quirks,
	पूर्ण, अणु
		.gmac = false,
		.gmac4 = true,
		.xgmac = false,
		.min_id = DWMAC_CORE_4_00,
		.regs = अणु
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
		पूर्ण,
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac4_dma_ops,
		.mac = &dwmac410_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = &dwmac4_ring_mode_ops,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac4_setup,
		.quirks = शून्य,
	पूर्ण, अणु
		.gmac = false,
		.gmac4 = true,
		.xgmac = false,
		.min_id = DWMAC_CORE_4_10,
		.regs = अणु
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
		पूर्ण,
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac410_dma_ops,
		.mac = &dwmac410_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = &dwmac4_ring_mode_ops,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac4_setup,
		.quirks = शून्य,
	पूर्ण, अणु
		.gmac = false,
		.gmac4 = true,
		.xgmac = false,
		.min_id = DWMAC_CORE_5_10,
		.regs = अणु
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
		पूर्ण,
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac410_dma_ops,
		.mac = &dwmac510_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = &dwmac4_ring_mode_ops,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac4_setup,
		.quirks = शून्य,
	पूर्ण, अणु
		.gmac = false,
		.gmac4 = false,
		.xgmac = true,
		.min_id = DWXGMAC_CORE_2_10,
		.dev_id = DWXGMAC_ID,
		.regs = अणु
			.ptp_off = PTP_XGMAC_OFFSET,
			.mmc_off = MMC_XGMAC_OFFSET,
		पूर्ण,
		.desc = &dwxgmac210_desc_ops,
		.dma = &dwxgmac210_dma_ops,
		.mac = &dwxgmac210_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = शून्य,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwxgmac_mmc_ops,
		.setup = dwxgmac2_setup,
		.quirks = शून्य,
	पूर्ण, अणु
		.gmac = false,
		.gmac4 = false,
		.xgmac = true,
		.min_id = DWXLGMAC_CORE_2_00,
		.dev_id = DWXLGMAC_ID,
		.regs = अणु
			.ptp_off = PTP_XGMAC_OFFSET,
			.mmc_off = MMC_XGMAC_OFFSET,
		पूर्ण,
		.desc = &dwxgmac210_desc_ops,
		.dma = &dwxgmac210_dma_ops,
		.mac = &dwxlgmac2_ops,
		.hwबारtamp = &sपंचांगmac_ptp,
		.mode = शून्य,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwxgmac_mmc_ops,
		.setup = dwxlgmac2_setup,
		.quirks = sपंचांगmac_dwxlgmac_quirks,
	पूर्ण,
पूर्ण;

पूर्णांक sपंचांगmac_hwअगर_init(काष्ठा sपंचांगmac_priv *priv)
अणु
	bool needs_xgmac = priv->plat->has_xgmac;
	bool needs_gmac4 = priv->plat->has_gmac4;
	bool needs_gmac = priv->plat->has_gmac;
	स्थिर काष्ठा sपंचांगmac_hwअगर_entry *entry;
	काष्ठा mac_device_info *mac;
	bool needs_setup = true;
	u32 id, dev_id = 0;
	पूर्णांक i, ret;

	अगर (needs_gmac) अणु
		id = sपंचांगmac_get_id(priv, GMAC_VERSION);
	पूर्ण अन्यथा अगर (needs_gmac4 || needs_xgmac) अणु
		id = sपंचांगmac_get_id(priv, GMAC4_VERSION);
		अगर (needs_xgmac)
			dev_id = sपंचांगmac_get_dev_id(priv, GMAC4_VERSION);
	पूर्ण अन्यथा अणु
		id = 0;
	पूर्ण

	/* Save ID क्रम later use */
	priv->synopsys_id = id;

	/* Lets assume some safe values first */
	priv->ptpaddr = priv->ioaddr +
		(needs_gmac4 ? PTP_GMAC4_OFFSET : PTP_GMAC3_X_OFFSET);
	priv->mmcaddr = priv->ioaddr +
		(needs_gmac4 ? MMC_GMAC4_OFFSET : MMC_GMAC3_X_OFFSET);

	/* Check क्रम HW specअगरic setup first */
	अगर (priv->plat->setup) अणु
		mac = priv->plat->setup(priv);
		needs_setup = false;
	पूर्ण अन्यथा अणु
		mac = devm_kzalloc(priv->device, माप(*mac), GFP_KERNEL);
	पूर्ण

	अगर (!mac)
		वापस -ENOMEM;

	/* Fallback to generic HW */
	क्रम (i = ARRAY_SIZE(sपंचांगmac_hw) - 1; i >= 0; i--) अणु
		entry = &sपंचांगmac_hw[i];

		अगर (needs_gmac ^ entry->gmac)
			जारी;
		अगर (needs_gmac4 ^ entry->gmac4)
			जारी;
		अगर (needs_xgmac ^ entry->xgmac)
			जारी;
		/* Use synopsys_id var because some setups can override this */
		अगर (priv->synopsys_id < entry->min_id)
			जारी;
		अगर (needs_xgmac && (dev_id ^ entry->dev_id))
			जारी;

		/* Only use generic HW helpers अगर needed */
		mac->desc = mac->desc ? : entry->desc;
		mac->dma = mac->dma ? : entry->dma;
		mac->mac = mac->mac ? : entry->mac;
		mac->ptp = mac->ptp ? : entry->hwबारtamp;
		mac->mode = mac->mode ? : entry->mode;
		mac->tc = mac->tc ? : entry->tc;
		mac->mmc = mac->mmc ? : entry->mmc;

		priv->hw = mac;
		priv->ptpaddr = priv->ioaddr + entry->regs.ptp_off;
		priv->mmcaddr = priv->ioaddr + entry->regs.mmc_off;

		/* Entry found */
		अगर (needs_setup) अणु
			ret = entry->setup(priv);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* Save quirks, अगर needed क्रम posterior use */
		priv->hwअगर_quirks = entry->quirks;
		वापस 0;
	पूर्ण

	dev_err(priv->device, "Failed to find HW IF (id=0x%x, gmac=%d/%d)\n",
			id, needs_gmac, needs_gmac4);
	वापस -EINVAL;
पूर्ण
