<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/ata/ahci_tegra.c
 *
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Mikko Perttunen <mperttunen@nvidia.com>
 */

#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/pmc.h>

#समावेश "ahci.h"

#घोषणा DRV_NAME "tegra-ahci"

#घोषणा SATA_CONFIGURATION_0				0x180
#घोषणा SATA_CONFIGURATION_0_EN_FPCI			BIT(0)
#घोषणा SATA_CONFIGURATION_0_CLK_OVERRIDE			BIT(31)

#घोषणा SCFG_OFFSET					0x1000

#घोषणा T_SATA0_CFG_1					0x04
#घोषणा T_SATA0_CFG_1_IO_SPACE				BIT(0)
#घोषणा T_SATA0_CFG_1_MEMORY_SPACE			BIT(1)
#घोषणा T_SATA0_CFG_1_BUS_MASTER			BIT(2)
#घोषणा T_SATA0_CFG_1_SERR				BIT(8)

#घोषणा T_SATA0_CFG_9					0x24
#घोषणा T_SATA0_CFG_9_BASE_ADDRESS			0x40020000

#घोषणा SATA_FPCI_BAR5					0x94
#घोषणा SATA_FPCI_BAR5_START_MASK			(0xfffffff << 4)
#घोषणा SATA_FPCI_BAR5_START				(0x0040020 << 4)
#घोषणा SATA_FPCI_BAR5_ACCESS_TYPE			(0x1)

#घोषणा SATA_INTR_MASK					0x188
#घोषणा SATA_INTR_MASK_IP_INT_MASK			BIT(16)

#घोषणा T_SATA0_CFG_35					0x94
#घोषणा T_SATA0_CFG_35_IDP_INDEX_MASK			(0x7ff << 2)
#घोषणा T_SATA0_CFG_35_IDP_INDEX			(0x2a << 2)

#घोषणा T_SATA0_AHCI_IDP1				0x98
#घोषणा T_SATA0_AHCI_IDP1_DATA				(0x400040)

#घोषणा T_SATA0_CFG_PHY_1				0x12c
#घोषणा T_SATA0_CFG_PHY_1_PADS_IDDQ_EN			BIT(23)
#घोषणा T_SATA0_CFG_PHY_1_PAD_PLL_IDDQ_EN		BIT(22)

#घोषणा T_SATA0_NVOOB                                   0x114
#घोषणा T_SATA0_NVOOB_SQUELCH_FILTER_MODE_MASK          (0x3 << 24)
#घोषणा T_SATA0_NVOOB_SQUELCH_FILTER_MODE               (0x1 << 24)
#घोषणा T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH_MASK        (0x3 << 26)
#घोषणा T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH             (0x3 << 26)

#घोषणा T_SATA_CFG_PHY_0                                0x120
#घोषणा T_SATA_CFG_PHY_0_USE_7BIT_ALIGN_DET_FOR_SPD     BIT(11)
#घोषणा T_SATA_CFG_PHY_0_MASK_SQUELCH                   BIT(24)

#घोषणा T_SATA0_CFG2NVOOB_2				0x134
#घोषणा T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW_MASK	(0x1ff << 18)
#घोषणा T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW	(0xc << 18)

#घोषणा T_SATA0_AHCI_HBA_CAP_BKDR			0x300
#घोषणा T_SATA0_AHCI_HBA_CAP_BKDR_PARTIAL_ST_CAP	BIT(13)
#घोषणा T_SATA0_AHCI_HBA_CAP_BKDR_SLUMBER_ST_CAP	BIT(14)
#घोषणा T_SATA0_AHCI_HBA_CAP_BKDR_SALP			BIT(26)
#घोषणा T_SATA0_AHCI_HBA_CAP_BKDR_SUPP_PM		BIT(17)
#घोषणा T_SATA0_AHCI_HBA_CAP_BKDR_SNCQ			BIT(30)

#घोषणा T_SATA0_BKDOOR_CC				0x4a4
#घोषणा T_SATA0_BKDOOR_CC_CLASS_CODE_MASK		(0xffff << 16)
#घोषणा T_SATA0_BKDOOR_CC_CLASS_CODE			(0x0106 << 16)
#घोषणा T_SATA0_BKDOOR_CC_PROG_IF_MASK			(0xff << 8)
#घोषणा T_SATA0_BKDOOR_CC_PROG_IF			(0x01 << 8)

#घोषणा T_SATA0_CFG_SATA				0x54c
#घोषणा T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN		BIT(12)

#घोषणा T_SATA0_CFG_MISC				0x550

#घोषणा T_SATA0_INDEX					0x680

#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN1			0x690
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_MASK		0xff
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT		0
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_MASK		(0xff << 8)
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT	8

#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN2			0x694
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_MASK		0xff
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_SHIFT		0
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_MASK		(0xff << 12)
#घोषणा T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_SHIFT	12

#घोषणा T_SATA0_CHX_PHY_CTRL2				0x69c
#घोषणा T_SATA0_CHX_PHY_CTRL2_CDR_CNTL_GEN1		0x23

#घोषणा T_SATA0_CHX_PHY_CTRL11				0x6d0
#घोषणा T_SATA0_CHX_PHY_CTRL11_GEN2_RX_EQ		(0x2800 << 16)

#घोषणा T_SATA0_CHX_PHY_CTRL17_0			0x6e8
#घोषणा T_SATA0_CHX_PHY_CTRL17_0_RX_EQ_CTRL_L_GEN1	0x55010000
#घोषणा T_SATA0_CHX_PHY_CTRL18_0			0x6ec
#घोषणा T_SATA0_CHX_PHY_CTRL18_0_RX_EQ_CTRL_L_GEN2	0x55010000
#घोषणा T_SATA0_CHX_PHY_CTRL20_0			0x6f4
#घोषणा T_SATA0_CHX_PHY_CTRL20_0_RX_EQ_CTRL_H_GEN1	0x1
#घोषणा T_SATA0_CHX_PHY_CTRL21_0			0x6f8
#घोषणा T_SATA0_CHX_PHY_CTRL21_0_RX_EQ_CTRL_H_GEN2	0x1

/* AUX Registers */
#घोषणा SATA_AUX_MISC_CNTL_1_0				0x8
#घोषणा SATA_AUX_MISC_CNTL_1_0_DEVSLP_OVERRIDE		BIT(17)
#घोषणा SATA_AUX_MISC_CNTL_1_0_SDS_SUPPORT		BIT(13)
#घोषणा SATA_AUX_MISC_CNTL_1_0_DESO_SUPPORT		BIT(15)

#घोषणा SATA_AUX_RX_STAT_INT_0				0xc
#घोषणा SATA_AUX_RX_STAT_INT_0_SATA_DEVSLP		BIT(7)

#घोषणा SATA_AUX_SPARE_CFG0_0				0x18
#घोषणा SATA_AUX_SPARE_CFG0_0_MDAT_TIMER_AFTER_PG_VALID	BIT(14)

#घोषणा FUSE_SATA_CALIB					0x124
#घोषणा FUSE_SATA_CALIB_MASK				0x3

काष्ठा sata_pad_calibration अणु
	u8 gen1_tx_amp;
	u8 gen1_tx_peak;
	u8 gen2_tx_amp;
	u8 gen2_tx_peak;
पूर्ण;

अटल स्थिर काष्ठा sata_pad_calibration tegra124_pad_calibration[] = अणु
	अणु0x18, 0x04, 0x18, 0x0aपूर्ण,
	अणु0x0e, 0x04, 0x14, 0x0aपूर्ण,
	अणु0x0e, 0x07, 0x1a, 0x0eपूर्ण,
	अणु0x14, 0x0e, 0x1a, 0x0eपूर्ण,
पूर्ण;

काष्ठा tegra_ahci_ops अणु
	पूर्णांक (*init)(काष्ठा ahci_host_priv *hpriv);
पूर्ण;

काष्ठा tegra_ahci_regs अणु
	अचिन्हित पूर्णांक nvoob_comma_cnt_mask;
	अचिन्हित पूर्णांक nvoob_comma_cnt_val;
पूर्ण;

काष्ठा tegra_ahci_soc अणु
	स्थिर अक्षर *स्थिर		*supply_names;
	u32				num_supplies;
	bool				supports_devslp;
	bool				has_sata_oob_rst;
	स्थिर काष्ठा tegra_ahci_ops	*ops;
	स्थिर काष्ठा tegra_ahci_regs	*regs;
पूर्ण;

काष्ठा tegra_ahci_priv अणु
	काष्ठा platक्रमm_device	   *pdev;
	व्योम __iomem		   *sata_regs;
	व्योम __iomem		   *sata_aux_regs;
	काष्ठा reset_control	   *sata_rst;
	काष्ठा reset_control	   *sata_oob_rst;
	काष्ठा reset_control	   *sata_cold_rst;
	/* Needs special handling, cannot use ahci_platक्रमm */
	काष्ठा clk		   *sata_clk;
	काष्ठा regulator_bulk_data *supplies;
	स्थिर काष्ठा tegra_ahci_soc *soc;
पूर्ण;

अटल व्योम tegra_ahci_handle_quirks(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा tegra_ahci_priv *tegra = hpriv->plat_data;
	u32 val;

	अगर (tegra->sata_aux_regs && !tegra->soc->supports_devslp) अणु
		val = पढ़ोl(tegra->sata_aux_regs + SATA_AUX_MISC_CNTL_1_0);
		val &= ~SATA_AUX_MISC_CNTL_1_0_SDS_SUPPORT;
		ग_लिखोl(val, tegra->sata_aux_regs + SATA_AUX_MISC_CNTL_1_0);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra124_ahci_init(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा tegra_ahci_priv *tegra = hpriv->plat_data;
	काष्ठा sata_pad_calibration calib;
	पूर्णांक ret;
	u32 val;

	/* Pad calibration */
	ret = tegra_fuse_पढ़ोl(FUSE_SATA_CALIB, &val);
	अगर (ret)
		वापस ret;

	calib = tegra124_pad_calibration[val & FUSE_SATA_CALIB_MASK];

	ग_लिखोl(BIT(0), tegra->sata_regs + SCFG_OFFSET + T_SATA0_INDEX);

	val = पढ़ोl(tegra->sata_regs +
		    SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN1);
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_MASK;
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_MASK;
	val |= calib.gen1_tx_amp << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT;
	val |= calib.gen1_tx_peak << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET +
	       T_SATA0_CHX_PHY_CTRL1_GEN1);

	val = पढ़ोl(tegra->sata_regs +
		    SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN2);
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_MASK;
	val &= ~T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_MASK;
	val |= calib.gen2_tx_amp << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT;
	val |= calib.gen2_tx_peak << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET +
	       T_SATA0_CHX_PHY_CTRL1_GEN2);

	ग_लिखोl(T_SATA0_CHX_PHY_CTRL11_GEN2_RX_EQ,
	       tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL11);
	ग_लिखोl(T_SATA0_CHX_PHY_CTRL2_CDR_CNTL_GEN1,
	       tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL2);

	ग_लिखोl(0, tegra->sata_regs + SCFG_OFFSET + T_SATA0_INDEX);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_ahci_घातer_on(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा tegra_ahci_priv *tegra = hpriv->plat_data;
	पूर्णांक ret;

	ret = regulator_bulk_enable(tegra->soc->num_supplies,
				    tegra->supplies);
	अगर (ret)
		वापस ret;

	अगर (!tegra->pdev->dev.pm_करोमुख्य) अणु
		ret = tegra_घातergate_sequence_घातer_up(TEGRA_POWERGATE_SATA,
							tegra->sata_clk,
							tegra->sata_rst);
		अगर (ret)
			जाओ disable_regulators;
	पूर्ण

	reset_control_निश्चित(tegra->sata_oob_rst);
	reset_control_निश्चित(tegra->sata_cold_rst);

	ret = ahci_platक्रमm_enable_resources(hpriv);
	अगर (ret)
		जाओ disable_घातer;

	reset_control_deनिश्चित(tegra->sata_cold_rst);
	reset_control_deनिश्चित(tegra->sata_oob_rst);

	वापस 0;

disable_घातer:
	clk_disable_unprepare(tegra->sata_clk);

	अगर (!tegra->pdev->dev.pm_करोमुख्य)
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_SATA);

disable_regulators:
	regulator_bulk_disable(tegra->soc->num_supplies, tegra->supplies);

	वापस ret;
पूर्ण

अटल व्योम tegra_ahci_घातer_off(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा tegra_ahci_priv *tegra = hpriv->plat_data;

	ahci_platक्रमm_disable_resources(hpriv);

	reset_control_निश्चित(tegra->sata_rst);
	reset_control_निश्चित(tegra->sata_oob_rst);
	reset_control_निश्चित(tegra->sata_cold_rst);

	clk_disable_unprepare(tegra->sata_clk);
	अगर (!tegra->pdev->dev.pm_करोमुख्य)
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_SATA);

	regulator_bulk_disable(tegra->soc->num_supplies, tegra->supplies);
पूर्ण

अटल पूर्णांक tegra_ahci_controller_init(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा tegra_ahci_priv *tegra = hpriv->plat_data;
	पूर्णांक ret;
	u32 val;

	ret = tegra_ahci_घातer_on(hpriv);
	अगर (ret) अणु
		dev_err(&tegra->pdev->dev,
			"failed to power on AHCI controller: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Program the following SATA IPFS रेजिस्टरs to allow SW accesses to
	 * SATA's MMIO रेजिस्टर range.
	 */
	val = पढ़ोl(tegra->sata_regs + SATA_FPCI_BAR5);
	val &= ~(SATA_FPCI_BAR5_START_MASK | SATA_FPCI_BAR5_ACCESS_TYPE);
	val |= SATA_FPCI_BAR5_START | SATA_FPCI_BAR5_ACCESS_TYPE;
	ग_लिखोl(val, tegra->sata_regs + SATA_FPCI_BAR5);

	/* Program the following SATA IPFS रेजिस्टर to enable the SATA */
	val = पढ़ोl(tegra->sata_regs + SATA_CONFIGURATION_0);
	val |= SATA_CONFIGURATION_0_EN_FPCI;
	ग_लिखोl(val, tegra->sata_regs + SATA_CONFIGURATION_0);

	/* Electrical settings क्रम better link stability */
	val = T_SATA0_CHX_PHY_CTRL17_0_RX_EQ_CTRL_L_GEN1;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL17_0);
	val = T_SATA0_CHX_PHY_CTRL18_0_RX_EQ_CTRL_L_GEN2;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL18_0);
	val = T_SATA0_CHX_PHY_CTRL20_0_RX_EQ_CTRL_H_GEN1;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL20_0);
	val = T_SATA0_CHX_PHY_CTRL21_0_RX_EQ_CTRL_H_GEN2;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL21_0);

	/* For SQUELCH Filter & Gen3 drive getting detected as Gen1 drive */

	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA_CFG_PHY_0);
	val |= T_SATA_CFG_PHY_0_MASK_SQUELCH;
	val &= ~T_SATA_CFG_PHY_0_USE_7BIT_ALIGN_DET_FOR_SPD;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA_CFG_PHY_0);

	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_NVOOB);
	val &= ~(tegra->soc->regs->nvoob_comma_cnt_mask |
		 T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH_MASK |
		 T_SATA0_NVOOB_SQUELCH_FILTER_MODE_MASK);
	val |= (tegra->soc->regs->nvoob_comma_cnt_val |
		T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH |
		T_SATA0_NVOOB_SQUELCH_FILTER_MODE);
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_NVOOB);

	/*
	 * Change CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW from 83.3 ns to 58.8ns
	 */
	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG2NVOOB_2);
	val &= ~T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW_MASK;
	val |= T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG2NVOOB_2);

	अगर (tegra->soc->ops && tegra->soc->ops->init)
		tegra->soc->ops->init(hpriv);

	/*
	 * Program the following SATA configuration रेजिस्टरs to
	 * initialize SATA
	 */
	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_1);
	val |= (T_SATA0_CFG_1_IO_SPACE | T_SATA0_CFG_1_MEMORY_SPACE |
		T_SATA0_CFG_1_BUS_MASTER | T_SATA0_CFG_1_SERR);
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_1);
	val = T_SATA0_CFG_9_BASE_ADDRESS;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_9);

	/* Program Class Code and Programming पूर्णांकerface क्रम SATA */
	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);
	val |= T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);

	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_BKDOOR_CC);
	val &=
	    ~(T_SATA0_BKDOOR_CC_CLASS_CODE_MASK |
	      T_SATA0_BKDOOR_CC_PROG_IF_MASK);
	val |= T_SATA0_BKDOOR_CC_CLASS_CODE | T_SATA0_BKDOOR_CC_PROG_IF;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_BKDOOR_CC);

	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);
	val &= ~T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);

	/* Enabling LPM capabilities through Backकरोor Programming */
	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_AHCI_HBA_CAP_BKDR);
	val |= (T_SATA0_AHCI_HBA_CAP_BKDR_PARTIAL_ST_CAP |
		T_SATA0_AHCI_HBA_CAP_BKDR_SLUMBER_ST_CAP |
		T_SATA0_AHCI_HBA_CAP_BKDR_SALP |
		T_SATA0_AHCI_HBA_CAP_BKDR_SUPP_PM);
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_AHCI_HBA_CAP_BKDR);

	/* SATA Second Level Clock Gating configuration
	 * Enabling Gating of Tx/Rx घड़ीs and driving Pad IDDQ and Lane
	 * IDDQ Signals
	 */
	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_35);
	val &= ~T_SATA0_CFG_35_IDP_INDEX_MASK;
	val |= T_SATA0_CFG_35_IDP_INDEX;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_35);

	val = T_SATA0_AHCI_IDP1_DATA;
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_AHCI_IDP1);

	val = पढ़ोl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_PHY_1);
	val |= (T_SATA0_CFG_PHY_1_PADS_IDDQ_EN |
		T_SATA0_CFG_PHY_1_PAD_PLL_IDDQ_EN);
	ग_लिखोl(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_PHY_1);

	/* Enabling IPFS Clock Gating */
	val = पढ़ोl(tegra->sata_regs + SATA_CONFIGURATION_0);
	val &= ~SATA_CONFIGURATION_0_CLK_OVERRIDE;
	ग_लिखोl(val, tegra->sata_regs + SATA_CONFIGURATION_0);

	tegra_ahci_handle_quirks(hpriv);

	/* Unmask SATA पूर्णांकerrupts */

	val = पढ़ोl(tegra->sata_regs + SATA_INTR_MASK);
	val |= SATA_INTR_MASK_IP_INT_MASK;
	ग_लिखोl(val, tegra->sata_regs + SATA_INTR_MASK);

	वापस 0;
पूर्ण

अटल व्योम tegra_ahci_controller_deinit(काष्ठा ahci_host_priv *hpriv)
अणु
	tegra_ahci_घातer_off(hpriv);
पूर्ण

अटल व्योम tegra_ahci_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;

	tegra_ahci_controller_deinit(hpriv);
पूर्ण

अटल काष्ठा ata_port_operations ahci_tegra_port_ops = अणु
	.inherits	= &ahci_ops,
	.host_stop	= tegra_ahci_host_stop,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_tegra_port_info = अणु
	.flags		= AHCI_FLAG_COMMON | ATA_FLAG_NO_DIPM,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_tegra_port_ops,
पूर्ण;

अटल स्थिर अक्षर *स्थिर tegra124_supply_names[] = अणु
	"avdd", "hvdd", "vddio", "target-5v", "target-12v"
पूर्ण;

अटल स्थिर काष्ठा tegra_ahci_ops tegra124_ahci_ops = अणु
	.init = tegra124_ahci_init,
पूर्ण;

अटल स्थिर काष्ठा tegra_ahci_regs tegra124_ahci_regs = अणु
	.nvoob_comma_cnt_mask = GENMASK(30, 28),
	.nvoob_comma_cnt_val = (7 << 28),
पूर्ण;

अटल स्थिर काष्ठा tegra_ahci_soc tegra124_ahci_soc = अणु
	.supply_names = tegra124_supply_names,
	.num_supplies = ARRAY_SIZE(tegra124_supply_names),
	.supports_devslp = false,
	.has_sata_oob_rst = true,
	.ops = &tegra124_ahci_ops,
	.regs = &tegra124_ahci_regs,
पूर्ण;

अटल स्थिर काष्ठा tegra_ahci_soc tegra210_ahci_soc = अणु
	.supports_devslp = false,
	.has_sata_oob_rst = true,
	.regs = &tegra124_ahci_regs,
पूर्ण;

अटल स्थिर काष्ठा tegra_ahci_regs tegra186_ahci_regs = अणु
	.nvoob_comma_cnt_mask = GENMASK(23, 16),
	.nvoob_comma_cnt_val = (7 << 16),
पूर्ण;

अटल स्थिर काष्ठा tegra_ahci_soc tegra186_ahci_soc = अणु
	.supports_devslp = false,
	.has_sata_oob_rst = false,
	.regs = &tegra186_ahci_regs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_ahci_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra124-ahci",
		.data = &tegra124_ahci_soc
	पूर्ण,
	अणु
		.compatible = "nvidia,tegra210-ahci",
		.data = &tegra210_ahci_soc
	पूर्ण,
	अणु
		.compatible = "nvidia,tegra186-ahci",
		.data = &tegra186_ahci_soc
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_ahci_of_match);

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक tegra_ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा tegra_ahci_priv *tegra;
	काष्ठा resource *res;
	पूर्णांक ret;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	tegra = devm_kzalloc(&pdev->dev, माप(*tegra), GFP_KERNEL);
	अगर (!tegra)
		वापस -ENOMEM;

	hpriv->plat_data = tegra;

	tegra->pdev = pdev;
	tegra->soc = of_device_get_match_data(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	tegra->sata_regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(tegra->sata_regs))
		वापस PTR_ERR(tegra->sata_regs);

	/*
	 * AUX रेजिस्टरs is optional.
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (res) अणु
		tegra->sata_aux_regs = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(tegra->sata_aux_regs))
			वापस PTR_ERR(tegra->sata_aux_regs);
	पूर्ण

	tegra->sata_rst = devm_reset_control_get(&pdev->dev, "sata");
	अगर (IS_ERR(tegra->sata_rst)) अणु
		dev_err(&pdev->dev, "Failed to get sata reset\n");
		वापस PTR_ERR(tegra->sata_rst);
	पूर्ण

	अगर (tegra->soc->has_sata_oob_rst) अणु
		tegra->sata_oob_rst = devm_reset_control_get(&pdev->dev,
							     "sata-oob");
		अगर (IS_ERR(tegra->sata_oob_rst)) अणु
			dev_err(&pdev->dev, "Failed to get sata-oob reset\n");
			वापस PTR_ERR(tegra->sata_oob_rst);
		पूर्ण
	पूर्ण

	tegra->sata_cold_rst = devm_reset_control_get(&pdev->dev, "sata-cold");
	अगर (IS_ERR(tegra->sata_cold_rst)) अणु
		dev_err(&pdev->dev, "Failed to get sata-cold reset\n");
		वापस PTR_ERR(tegra->sata_cold_rst);
	पूर्ण

	tegra->sata_clk = devm_clk_get(&pdev->dev, "sata");
	अगर (IS_ERR(tegra->sata_clk)) अणु
		dev_err(&pdev->dev, "Failed to get sata clock\n");
		वापस PTR_ERR(tegra->sata_clk);
	पूर्ण

	tegra->supplies = devm_kसुस्मृति(&pdev->dev,
				       tegra->soc->num_supplies,
				       माप(*tegra->supplies), GFP_KERNEL);
	अगर (!tegra->supplies)
		वापस -ENOMEM;

	regulator_bulk_set_supply_names(tegra->supplies,
					tegra->soc->supply_names,
					tegra->soc->num_supplies);

	ret = devm_regulator_bulk_get(&pdev->dev,
				      tegra->soc->num_supplies,
				      tegra->supplies);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to get regulators\n");
		वापस ret;
	पूर्ण

	ret = tegra_ahci_controller_init(hpriv);
	अगर (ret)
		वापस ret;

	ret = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_tegra_port_info,
				      &ahci_platक्रमm_sht);
	अगर (ret)
		जाओ deinit_controller;

	वापस 0;

deinit_controller:
	tegra_ahci_controller_deinit(hpriv);

	वापस ret;
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_ahci_driver = अणु
	.probe = tegra_ahci_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = tegra_ahci_of_match,
	पूर्ण,
	/* LP0 suspend support not implemented */
पूर्ण;
module_platक्रमm_driver(tegra_ahci_driver);

MODULE_AUTHOR("Mikko Perttunen <mperttunen@nvidia.com>");
MODULE_DESCRIPTION("Tegra AHCI SATA driver");
MODULE_LICENSE("GPL v2");
