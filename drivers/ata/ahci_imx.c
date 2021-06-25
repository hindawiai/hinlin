<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * copyright (c) 2013 Freescale Semiconductor, Inc.
 * Freescale IMX AHCI SATA platक्रमm driver
 *
 * based on the AHCI SATA platक्रमm driver by Jeff Garzik and Anton Vorontsov
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/libata.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/thermal.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME "ahci-imx"

क्रमागत अणु
	/* Timer 1-ms Register */
	IMX_TIMER1MS				= 0x00e0,
	/* Port0 PHY Control Register */
	IMX_P0PHYCR				= 0x0178,
	IMX_P0PHYCR_TEST_PDDQ			= 1 << 20,
	IMX_P0PHYCR_CR_READ			= 1 << 19,
	IMX_P0PHYCR_CR_WRITE			= 1 << 18,
	IMX_P0PHYCR_CR_CAP_DATA			= 1 << 17,
	IMX_P0PHYCR_CR_CAP_ADDR			= 1 << 16,
	/* Port0 PHY Status Register */
	IMX_P0PHYSR				= 0x017c,
	IMX_P0PHYSR_CR_ACK			= 1 << 18,
	IMX_P0PHYSR_CR_DATA_OUT			= 0xffff << 0,
	/* Lane0 Output Status Register */
	IMX_LANE0_OUT_STAT			= 0x2003,
	IMX_LANE0_OUT_STAT_RX_PLL_STATE		= 1 << 1,
	/* Clock Reset Register */
	IMX_CLOCK_RESET				= 0x7f3f,
	IMX_CLOCK_RESET_RESET			= 1 << 0,
	/* IMX8QM HSIO AHCI definitions */
	IMX8QM_SATA_PHY_RX_IMPED_RATIO_OFFSET	= 0x03,
	IMX8QM_SATA_PHY_TX_IMPED_RATIO_OFFSET	= 0x09,
	IMX8QM_SATA_PHY_IMPED_RATIO_85OHM	= 0x6c,
	IMX8QM_LPCG_PHYX2_OFFSET		= 0x00000,
	IMX8QM_CSR_PHYX2_OFFSET			= 0x90000,
	IMX8QM_CSR_PHYX1_OFFSET			= 0xa0000,
	IMX8QM_CSR_PHYX_STTS0_OFFSET		= 0x4,
	IMX8QM_CSR_PCIEA_OFFSET			= 0xb0000,
	IMX8QM_CSR_PCIEB_OFFSET			= 0xc0000,
	IMX8QM_CSR_SATA_OFFSET			= 0xd0000,
	IMX8QM_CSR_PCIE_CTRL2_OFFSET		= 0x8,
	IMX8QM_CSR_MISC_OFFSET			= 0xe0000,

	IMX8QM_LPCG_PHYX2_PCLK0_MASK		= (0x3 << 16),
	IMX8QM_LPCG_PHYX2_PCLK1_MASK		= (0x3 << 20),
	IMX8QM_PHY_APB_RSTN_0			= BIT(0),
	IMX8QM_PHY_MODE_SATA			= BIT(19),
	IMX8QM_PHY_MODE_MASK			= (0xf << 17),
	IMX8QM_PHY_PIPE_RSTN_0			= BIT(24),
	IMX8QM_PHY_PIPE_RSTN_OVERRIDE_0		= BIT(25),
	IMX8QM_PHY_PIPE_RSTN_1			= BIT(26),
	IMX8QM_PHY_PIPE_RSTN_OVERRIDE_1		= BIT(27),
	IMX8QM_STTS0_LANE0_TX_PLL_LOCK		= BIT(4),
	IMX8QM_MISC_IOB_RXENA			= BIT(0),
	IMX8QM_MISC_IOB_TXENA			= BIT(1),
	IMX8QM_MISC_PHYX1_EPCS_SEL		= BIT(12),
	IMX8QM_MISC_CLKREQN_OUT_OVERRIDE_1	= BIT(24),
	IMX8QM_MISC_CLKREQN_OUT_OVERRIDE_0	= BIT(25),
	IMX8QM_MISC_CLKREQN_IN_OVERRIDE_1	= BIT(28),
	IMX8QM_MISC_CLKREQN_IN_OVERRIDE_0	= BIT(29),
	IMX8QM_SATA_CTRL_RESET_N		= BIT(12),
	IMX8QM_SATA_CTRL_EPCS_PHYRESET_N	= BIT(7),
	IMX8QM_CTRL_BUTTON_RST_N		= BIT(21),
	IMX8QM_CTRL_POWER_UP_RST_N		= BIT(23),
	IMX8QM_CTRL_LTSSM_ENABLE		= BIT(4),
पूर्ण;

क्रमागत ahci_imx_type अणु
	AHCI_IMX53,
	AHCI_IMX6Q,
	AHCI_IMX6QP,
	AHCI_IMX8QM,
पूर्ण;

काष्ठा imx_ahci_priv अणु
	काष्ठा platक्रमm_device *ahci_pdev;
	क्रमागत ahci_imx_type type;
	काष्ठा clk *sata_clk;
	काष्ठा clk *sata_ref_clk;
	काष्ठा clk *ahb_clk;
	काष्ठा clk *epcs_tx_clk;
	काष्ठा clk *epcs_rx_clk;
	काष्ठा clk *phy_apbclk;
	काष्ठा clk *phy_pclk0;
	काष्ठा clk *phy_pclk1;
	व्योम __iomem *phy_base;
	काष्ठा gpio_desc *clkreq_gpiod;
	काष्ठा regmap *gpr;
	bool no_device;
	bool first_समय;
	u32 phy_params;
	u32 imped_ratio;
पूर्ण;

अटल पूर्णांक ahci_imx_hotplug;
module_param_named(hotplug, ahci_imx_hotplug, पूर्णांक, 0644);
MODULE_PARM_DESC(hotplug, "AHCI IMX hot-plug support (0=Don't support, 1=support)");

अटल व्योम ahci_imx_host_stop(काष्ठा ata_host *host);

अटल पूर्णांक imx_phy_crbit_निश्चित(व्योम __iomem *mmio, u32 bit, bool निश्चित)
अणु
	पूर्णांक समयout = 10;
	u32 crval;
	u32 srval;

	/* Assert or deनिश्चित the bit */
	crval = पढ़ोl(mmio + IMX_P0PHYCR);
	अगर (निश्चित)
		crval |= bit;
	अन्यथा
		crval &= ~bit;
	ग_लिखोl(crval, mmio + IMX_P0PHYCR);

	/* Wait क्रम the cr_ack संकेत */
	करो अणु
		srval = पढ़ोl(mmio + IMX_P0PHYSR);
		अगर ((निश्चित ? srval : ~srval) & IMX_P0PHYSR_CR_ACK)
			अवरोध;
		usleep_range(100, 200);
	पूर्ण जबतक (--समयout);

	वापस समयout ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक imx_phy_reg_addressing(u16 addr, व्योम __iomem *mmio)
अणु
	u32 crval = addr;
	पूर्णांक ret;

	/* Supply the address on cr_data_in */
	ग_लिखोl(crval, mmio + IMX_P0PHYCR);

	/* Assert the cr_cap_addr संकेत */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_CAP_ADDR, true);
	अगर (ret)
		वापस ret;

	/* Deनिश्चित cr_cap_addr */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_CAP_ADDR, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_phy_reg_ग_लिखो(u16 val, व्योम __iomem *mmio)
अणु
	u32 crval = val;
	पूर्णांक ret;

	/* Supply the data on cr_data_in */
	ग_लिखोl(crval, mmio + IMX_P0PHYCR);

	/* Assert the cr_cap_data संकेत */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_CAP_DATA, true);
	अगर (ret)
		वापस ret;

	/* Deनिश्चित cr_cap_data */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_CAP_DATA, false);
	अगर (ret)
		वापस ret;

	अगर (val & IMX_CLOCK_RESET_RESET) अणु
		/*
		 * In हाल we're resetting the phy, it's unable to acknowledge,
		 * so we वापस immediately here.
		 */
		crval |= IMX_P0PHYCR_CR_WRITE;
		ग_लिखोl(crval, mmio + IMX_P0PHYCR);
		जाओ out;
	पूर्ण

	/* Assert the cr_ग_लिखो संकेत */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_WRITE, true);
	अगर (ret)
		वापस ret;

	/* Deनिश्चित cr_ग_लिखो */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_WRITE, false);
	अगर (ret)
		वापस ret;

out:
	वापस 0;
पूर्ण

अटल पूर्णांक imx_phy_reg_पढ़ो(u16 *val, व्योम __iomem *mmio)
अणु
	पूर्णांक ret;

	/* Assert the cr_पढ़ो संकेत */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_READ, true);
	अगर (ret)
		वापस ret;

	/* Capture the data from cr_data_out[] */
	*val = पढ़ोl(mmio + IMX_P0PHYSR) & IMX_P0PHYSR_CR_DATA_OUT;

	/* Deनिश्चित cr_पढ़ो */
	ret = imx_phy_crbit_निश्चित(mmio, IMX_P0PHYCR_CR_READ, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_sata_phy_reset(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा imx_ahci_priv *imxpriv = hpriv->plat_data;
	व्योम __iomem *mmio = hpriv->mmio;
	पूर्णांक समयout = 10;
	u16 val;
	पूर्णांक ret;

	अगर (imxpriv->type == AHCI_IMX6QP) अणु
		/* 6qp adds the sata reset mechanism, use it क्रम 6qp sata */
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR5,
				   IMX6Q_GPR5_SATA_SW_PD, 0);

		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR5,
				   IMX6Q_GPR5_SATA_SW_RST, 0);
		udelay(50);
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR5,
				   IMX6Q_GPR5_SATA_SW_RST,
				   IMX6Q_GPR5_SATA_SW_RST);
		वापस 0;
	पूर्ण

	/* Reset SATA PHY by setting RESET bit of PHY रेजिस्टर CLOCK_RESET */
	ret = imx_phy_reg_addressing(IMX_CLOCK_RESET, mmio);
	अगर (ret)
		वापस ret;
	ret = imx_phy_reg_ग_लिखो(IMX_CLOCK_RESET_RESET, mmio);
	अगर (ret)
		वापस ret;

	/* Wait क्रम PHY RX_PLL to be stable */
	करो अणु
		usleep_range(100, 200);
		ret = imx_phy_reg_addressing(IMX_LANE0_OUT_STAT, mmio);
		अगर (ret)
			वापस ret;
		ret = imx_phy_reg_पढ़ो(&val, mmio);
		अगर (ret)
			वापस ret;
		अगर (val & IMX_LANE0_OUT_STAT_RX_PLL_STATE)
			अवरोध;
	पूर्ण जबतक (--समयout);

	वापस समयout ? 0 : -ETIMEDOUT;
पूर्ण

क्रमागत अणु
	/* SATA PHY Register */
	SATA_PHY_CR_CLOCK_CRCMP_LT_LIMIT = 0x0001,
	SATA_PHY_CR_CLOCK_DAC_CTL = 0x0008,
	SATA_PHY_CR_CLOCK_RTUNE_CTL = 0x0009,
	SATA_PHY_CR_CLOCK_ADC_OUT = 0x000A,
	SATA_PHY_CR_CLOCK_MPLL_TST = 0x0017,
पूर्ण;

अटल पूर्णांक पढ़ो_adc_sum(व्योम *dev, u16 rtune_ctl_reg, व्योम __iomem * mmio)
अणु
	u16 adc_out_reg, पढ़ो_sum;
	u32 index, पढ़ो_attempt;
	स्थिर u32 attempt_limit = 200;

	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_RTUNE_CTL, mmio);
	imx_phy_reg_ग_लिखो(rtune_ctl_reg, mmio);

	/* two dummy पढ़ो */
	index = 0;
	पढ़ो_attempt = 0;
	adc_out_reg = 0;
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_ADC_OUT, mmio);
	जबतक (index < 2) अणु
		imx_phy_reg_पढ़ो(&adc_out_reg, mmio);
		/* check अगर valid */
		अगर (adc_out_reg & 0x400)
			index++;

		पढ़ो_attempt++;
		अगर (पढ़ो_attempt > attempt_limit) अणु
			dev_err(dev, "Read REG more than %d times!\n",
				attempt_limit);
			अवरोध;
		पूर्ण
	पूर्ण

	index = 0;
	पढ़ो_attempt = 0;
	पढ़ो_sum = 0;
	जबतक (index < 80) अणु
		imx_phy_reg_पढ़ो(&adc_out_reg, mmio);
		अगर (adc_out_reg & 0x400) अणु
			पढ़ो_sum = पढ़ो_sum + (adc_out_reg & 0x3FF);
			index++;
		पूर्ण
		पढ़ो_attempt++;
		अगर (पढ़ो_attempt > attempt_limit) अणु
			dev_err(dev, "Read REG more than %d times!\n",
				attempt_limit);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Use the U32 to make 1000 precision */
	वापस (पढ़ो_sum * 1000) / 80;
पूर्ण

/* SATA AHCI temperature monitor */
अटल पूर्णांक sata_ahci_पढ़ो_temperature(व्योम *dev, पूर्णांक *temp)
अणु
	u16 mpll_test_reg, rtune_ctl_reg, dac_ctl_reg, पढ़ो_sum;
	u32 str1, str2, str3, str4;
	पूर्णांक m1, m2, a;
	काष्ठा ahci_host_priv *hpriv = dev_get_drvdata(dev);
	व्योम __iomem *mmio = hpriv->mmio;

	/* check rd-wr to reg */
	पढ़ो_sum = 0;
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_CRCMP_LT_LIMIT, mmio);
	imx_phy_reg_ग_लिखो(पढ़ो_sum, mmio);
	imx_phy_reg_पढ़ो(&पढ़ो_sum, mmio);
	अगर ((पढ़ो_sum & 0xffff) != 0)
		dev_err(dev, "Read/Write REG error, 0x%x!\n", पढ़ो_sum);

	imx_phy_reg_ग_लिखो(0x5A5A, mmio);
	imx_phy_reg_पढ़ो(&पढ़ो_sum, mmio);
	अगर ((पढ़ो_sum & 0xffff) != 0x5A5A)
		dev_err(dev, "Read/Write REG error, 0x%x!\n", पढ़ो_sum);

	imx_phy_reg_ग_लिखो(0x1234, mmio);
	imx_phy_reg_पढ़ो(&पढ़ो_sum, mmio);
	अगर ((पढ़ो_sum & 0xffff) != 0x1234)
		dev_err(dev, "Read/Write REG error, 0x%x!\n", पढ़ो_sum);

	/* start temperature test */
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_MPLL_TST, mmio);
	imx_phy_reg_पढ़ो(&mpll_test_reg, mmio);
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_RTUNE_CTL, mmio);
	imx_phy_reg_पढ़ो(&rtune_ctl_reg, mmio);
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_DAC_CTL, mmio);
	imx_phy_reg_पढ़ो(&dac_ctl_reg, mmio);

	/* mpll_tst.meas_iv   ([12:2]) */
	str1 = (mpll_test_reg >> 2) & 0x7FF;
	/* rtune_ctl.mode     ([1:0]) */
	str2 = (rtune_ctl_reg) & 0x3;
	/* dac_ctl.dac_mode   ([14:12]) */
	str3 = (dac_ctl_reg >> 12)  & 0x7;
	/* rtune_ctl.sel_atbp ([4]) */
	str4 = (rtune_ctl_reg >> 4);

	/* Calculate the m1 */
	/* mpll_tst.meas_iv */
	mpll_test_reg = (mpll_test_reg & 0xE03) | (512) << 2;
	/* rtune_ctl.mode */
	rtune_ctl_reg = (rtune_ctl_reg & 0xFFC) | (1);
	/* dac_ctl.dac_mode */
	dac_ctl_reg = (dac_ctl_reg & 0x8FF) | (4) << 12;
	/* rtune_ctl.sel_atbp */
	rtune_ctl_reg = (rtune_ctl_reg & 0xFEF) | (0) << 4;
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_MPLL_TST, mmio);
	imx_phy_reg_ग_लिखो(mpll_test_reg, mmio);
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_DAC_CTL, mmio);
	imx_phy_reg_ग_लिखो(dac_ctl_reg, mmio);
	m1 = पढ़ो_adc_sum(dev, rtune_ctl_reg, mmio);

	/* Calculate the m2 */
	/* rtune_ctl.sel_atbp */
	rtune_ctl_reg = (rtune_ctl_reg & 0xFEF) | (1) << 4;
	m2 = पढ़ो_adc_sum(dev, rtune_ctl_reg, mmio);

	/* restore the status  */
	/* mpll_tst.meas_iv */
	mpll_test_reg = (mpll_test_reg & 0xE03) | (str1) << 2;
	/* rtune_ctl.mode */
	rtune_ctl_reg = (rtune_ctl_reg & 0xFFC) | (str2);
	/* dac_ctl.dac_mode */
	dac_ctl_reg = (dac_ctl_reg & 0x8FF) | (str3) << 12;
	/* rtune_ctl.sel_atbp */
	rtune_ctl_reg = (rtune_ctl_reg & 0xFEF) | (str4) << 4;

	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_MPLL_TST, mmio);
	imx_phy_reg_ग_लिखो(mpll_test_reg, mmio);
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_DAC_CTL, mmio);
	imx_phy_reg_ग_लिखो(dac_ctl_reg, mmio);
	imx_phy_reg_addressing(SATA_PHY_CR_CLOCK_RTUNE_CTL, mmio);
	imx_phy_reg_ग_लिखो(rtune_ctl_reg, mmio);

	/* Compute temperature */
	अगर (!(m2 / 1000))
		m2 = 1000;
	a = (m2 - m1) / (m2/1000);
	*temp = ((-559) * a * a) / 1000 + (1379) * a + (-458000);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sata_ahci_show_temp(काष्ठा device *dev,
				   काष्ठा device_attribute *da,
				   अक्षर *buf)
अणु
	अचिन्हित पूर्णांक temp = 0;
	पूर्णांक err;

	err = sata_ahci_पढ़ो_temperature(dev, &temp);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", temp);
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops fsl_sata_ahci_of_thermal_ops = अणु
	.get_temp = sata_ahci_पढ़ो_temperature,
पूर्ण;

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, sata_ahci_show_temp, शून्य, 0);

अटल काष्ठा attribute *fsl_sata_ahci_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(fsl_sata_ahci);

अटल पूर्णांक imx8_sata_enable(काष्ठा ahci_host_priv *hpriv)
अणु
	u32 val, reg;
	पूर्णांक i, ret;
	काष्ठा imx_ahci_priv *imxpriv = hpriv->plat_data;
	काष्ठा device *dev = &imxpriv->ahci_pdev->dev;

	/* configure the hsio क्रम sata */
	ret = clk_prepare_enable(imxpriv->phy_pclk0);
	अगर (ret < 0) अणु
		dev_err(dev, "can't enable phy_pclk0.\n");
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(imxpriv->phy_pclk1);
	अगर (ret < 0) अणु
		dev_err(dev, "can't enable phy_pclk1.\n");
		जाओ disable_phy_pclk0;
	पूर्ण
	ret = clk_prepare_enable(imxpriv->epcs_tx_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "can't enable epcs_tx_clk.\n");
		जाओ disable_phy_pclk1;
	पूर्ण
	ret = clk_prepare_enable(imxpriv->epcs_rx_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "can't enable epcs_rx_clk.\n");
		जाओ disable_epcs_tx_clk;
	पूर्ण
	ret = clk_prepare_enable(imxpriv->phy_apbclk);
	अगर (ret < 0) अणु
		dev_err(dev, "can't enable phy_apbclk.\n");
		जाओ disable_epcs_rx_clk;
	पूर्ण
	/* Configure PHYx2 PIPE_RSTN */
	regmap_पढ़ो(imxpriv->gpr, IMX8QM_CSR_PCIEA_OFFSET +
			IMX8QM_CSR_PCIE_CTRL2_OFFSET, &val);
	अगर ((val & IMX8QM_CTRL_LTSSM_ENABLE) == 0) अणु
		/* The link of the PCIEA of HSIO is करोwn */
		regmap_update_bits(imxpriv->gpr,
				IMX8QM_CSR_PHYX2_OFFSET,
				IMX8QM_PHY_PIPE_RSTN_0 |
				IMX8QM_PHY_PIPE_RSTN_OVERRIDE_0,
				IMX8QM_PHY_PIPE_RSTN_0 |
				IMX8QM_PHY_PIPE_RSTN_OVERRIDE_0);
	पूर्ण
	regmap_पढ़ो(imxpriv->gpr, IMX8QM_CSR_PCIEB_OFFSET +
			IMX8QM_CSR_PCIE_CTRL2_OFFSET, &reg);
	अगर ((reg & IMX8QM_CTRL_LTSSM_ENABLE) == 0) अणु
		/* The link of the PCIEB of HSIO is करोwn */
		regmap_update_bits(imxpriv->gpr,
				IMX8QM_CSR_PHYX2_OFFSET,
				IMX8QM_PHY_PIPE_RSTN_1 |
				IMX8QM_PHY_PIPE_RSTN_OVERRIDE_1,
				IMX8QM_PHY_PIPE_RSTN_1 |
				IMX8QM_PHY_PIPE_RSTN_OVERRIDE_1);
	पूर्ण
	अगर (((reg | val) & IMX8QM_CTRL_LTSSM_ENABLE) == 0) अणु
		/* The links of both PCIA and PCIEB of HSIO are करोwn */
		regmap_update_bits(imxpriv->gpr,
				IMX8QM_LPCG_PHYX2_OFFSET,
				IMX8QM_LPCG_PHYX2_PCLK0_MASK |
				IMX8QM_LPCG_PHYX2_PCLK1_MASK,
				0);
	पूर्ण

	/* set PWR_RST and BT_RST of csr_pciea */
	val = IMX8QM_CSR_PCIEA_OFFSET + IMX8QM_CSR_PCIE_CTRL2_OFFSET;
	regmap_update_bits(imxpriv->gpr,
			val,
			IMX8QM_CTRL_BUTTON_RST_N,
			IMX8QM_CTRL_BUTTON_RST_N);
	regmap_update_bits(imxpriv->gpr,
			val,
			IMX8QM_CTRL_POWER_UP_RST_N,
			IMX8QM_CTRL_POWER_UP_RST_N);

	/* PHYX1_MODE to SATA */
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_PHYX1_OFFSET,
			IMX8QM_PHY_MODE_MASK,
			IMX8QM_PHY_MODE_SATA);

	/*
	 * BIT0 RXENA 1, BIT1 TXENA 0
	 * BIT12 PHY_X1_EPCS_SEL 1.
	 */
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_MISC_OFFSET,
			IMX8QM_MISC_IOB_RXENA,
			IMX8QM_MISC_IOB_RXENA);
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_MISC_OFFSET,
			IMX8QM_MISC_IOB_TXENA,
			0);
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_MISC_OFFSET,
			IMX8QM_MISC_PHYX1_EPCS_SEL,
			IMX8QM_MISC_PHYX1_EPCS_SEL);
	/*
	 * It is possible, क्रम PCIe and SATA are sharing
	 * the same घड़ी source, HPLL or बाह्यal oscillator.
	 * When PCIe is in low घातer modes (L1.X or L2 etc),
	 * the घड़ी source can be turned off. In this हाल,
	 * अगर this घड़ी source is required to be toggling by
	 * SATA, then SATA functions will be abnormal.
	 * Set the override here to aव्योम it.
	 */
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_MISC_OFFSET,
			IMX8QM_MISC_CLKREQN_OUT_OVERRIDE_1 |
			IMX8QM_MISC_CLKREQN_OUT_OVERRIDE_0 |
			IMX8QM_MISC_CLKREQN_IN_OVERRIDE_1 |
			IMX8QM_MISC_CLKREQN_IN_OVERRIDE_0,
			IMX8QM_MISC_CLKREQN_OUT_OVERRIDE_1 |
			IMX8QM_MISC_CLKREQN_OUT_OVERRIDE_0 |
			IMX8QM_MISC_CLKREQN_IN_OVERRIDE_1 |
			IMX8QM_MISC_CLKREQN_IN_OVERRIDE_0);

	/* clear PHY RST, then set it */
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_SATA_OFFSET,
			IMX8QM_SATA_CTRL_EPCS_PHYRESET_N,
			0);

	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_SATA_OFFSET,
			IMX8QM_SATA_CTRL_EPCS_PHYRESET_N,
			IMX8QM_SATA_CTRL_EPCS_PHYRESET_N);

	/* CTRL RST: SET -> delay 1 us -> CLEAR -> SET */
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_SATA_OFFSET,
			IMX8QM_SATA_CTRL_RESET_N,
			IMX8QM_SATA_CTRL_RESET_N);
	udelay(1);
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_SATA_OFFSET,
			IMX8QM_SATA_CTRL_RESET_N,
			0);
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_SATA_OFFSET,
			IMX8QM_SATA_CTRL_RESET_N,
			IMX8QM_SATA_CTRL_RESET_N);

	/* APB reset */
	regmap_update_bits(imxpriv->gpr,
			IMX8QM_CSR_PHYX1_OFFSET,
			IMX8QM_PHY_APB_RSTN_0,
			IMX8QM_PHY_APB_RSTN_0);

	क्रम (i = 0; i < 100; i++) अणु
		reg = IMX8QM_CSR_PHYX1_OFFSET +
			IMX8QM_CSR_PHYX_STTS0_OFFSET;
		regmap_पढ़ो(imxpriv->gpr, reg, &val);
		val &= IMX8QM_STTS0_LANE0_TX_PLL_LOCK;
		अगर (val == IMX8QM_STTS0_LANE0_TX_PLL_LOCK)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (val != IMX8QM_STTS0_LANE0_TX_PLL_LOCK) अणु
		dev_err(dev, "TX PLL of the PHY is not locked\n");
		ret = -ENODEV;
	पूर्ण अन्यथा अणु
		ग_लिखोb(imxpriv->imped_ratio, imxpriv->phy_base +
				IMX8QM_SATA_PHY_RX_IMPED_RATIO_OFFSET);
		ग_लिखोb(imxpriv->imped_ratio, imxpriv->phy_base +
				IMX8QM_SATA_PHY_TX_IMPED_RATIO_OFFSET);
		reg = पढ़ोb(imxpriv->phy_base +
				IMX8QM_SATA_PHY_RX_IMPED_RATIO_OFFSET);
		अगर (unlikely(reg != imxpriv->imped_ratio))
			dev_info(dev, "Can't set PHY RX impedance ratio.\n");
		reg = पढ़ोb(imxpriv->phy_base +
				IMX8QM_SATA_PHY_TX_IMPED_RATIO_OFFSET);
		अगर (unlikely(reg != imxpriv->imped_ratio))
			dev_info(dev, "Can't set PHY TX impedance ratio.\n");
		usleep_range(50, 100);

		/*
		 * To reduce the घातer consumption, gate off
		 * the PHY clks
		 */
		clk_disable_unprepare(imxpriv->phy_apbclk);
		clk_disable_unprepare(imxpriv->phy_pclk1);
		clk_disable_unprepare(imxpriv->phy_pclk0);
		वापस ret;
	पूर्ण

	clk_disable_unprepare(imxpriv->phy_apbclk);
disable_epcs_rx_clk:
	clk_disable_unprepare(imxpriv->epcs_rx_clk);
disable_epcs_tx_clk:
	clk_disable_unprepare(imxpriv->epcs_tx_clk);
disable_phy_pclk1:
	clk_disable_unprepare(imxpriv->phy_pclk1);
disable_phy_pclk0:
	clk_disable_unprepare(imxpriv->phy_pclk0);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_sata_enable(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा imx_ahci_priv *imxpriv = hpriv->plat_data;
	काष्ठा device *dev = &imxpriv->ahci_pdev->dev;
	पूर्णांक ret;

	अगर (imxpriv->no_device)
		वापस 0;

	ret = ahci_platक्रमm_enable_regulators(hpriv);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(imxpriv->sata_ref_clk);
	अगर (ret < 0)
		जाओ disable_regulator;

	अगर (imxpriv->type == AHCI_IMX6Q || imxpriv->type == AHCI_IMX6QP) अणु
		/*
		 * set PHY Paremeters, two steps to configure the GPR13,
		 * one ग_लिखो क्रम rest of parameters, mask of first ग_लिखो
		 * is 0x07ffffff, and the other one ग_लिखो क्रम setting
		 * the mpll_clk_en.
		 */
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR13,
				   IMX6Q_GPR13_SATA_RX_EQ_VAL_MASK |
				   IMX6Q_GPR13_SATA_RX_LOS_LVL_MASK |
				   IMX6Q_GPR13_SATA_RX_DPLL_MODE_MASK |
				   IMX6Q_GPR13_SATA_SPD_MODE_MASK |
				   IMX6Q_GPR13_SATA_MPLL_SS_EN |
				   IMX6Q_GPR13_SATA_TX_ATTEN_MASK |
				   IMX6Q_GPR13_SATA_TX_BOOST_MASK |
				   IMX6Q_GPR13_SATA_TX_LVL_MASK |
				   IMX6Q_GPR13_SATA_MPLL_CLK_EN |
				   IMX6Q_GPR13_SATA_TX_EDGE_RATE,
				   imxpriv->phy_params);
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR13,
				   IMX6Q_GPR13_SATA_MPLL_CLK_EN,
				   IMX6Q_GPR13_SATA_MPLL_CLK_EN);

		usleep_range(100, 200);

		ret = imx_sata_phy_reset(hpriv);
		अगर (ret) अणु
			dev_err(dev, "failed to reset phy: %d\n", ret);
			जाओ disable_clk;
		पूर्ण
	पूर्ण अन्यथा अगर (imxpriv->type == AHCI_IMX8QM) अणु
		ret = imx8_sata_enable(hpriv);
	पूर्ण

	usleep_range(1000, 2000);

	वापस 0;

disable_clk:
	clk_disable_unprepare(imxpriv->sata_ref_clk);
disable_regulator:
	ahci_platक्रमm_disable_regulators(hpriv);

	वापस ret;
पूर्ण

अटल व्योम imx_sata_disable(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा imx_ahci_priv *imxpriv = hpriv->plat_data;

	अगर (imxpriv->no_device)
		वापस;

	चयन (imxpriv->type) अणु
	हाल AHCI_IMX6QP:
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR5,
				   IMX6Q_GPR5_SATA_SW_PD,
				   IMX6Q_GPR5_SATA_SW_PD);
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR13,
				   IMX6Q_GPR13_SATA_MPLL_CLK_EN,
				   !IMX6Q_GPR13_SATA_MPLL_CLK_EN);
		अवरोध;

	हाल AHCI_IMX6Q:
		regmap_update_bits(imxpriv->gpr, IOMUXC_GPR13,
				   IMX6Q_GPR13_SATA_MPLL_CLK_EN,
				   !IMX6Q_GPR13_SATA_MPLL_CLK_EN);
		अवरोध;

	हाल AHCI_IMX8QM:
		clk_disable_unprepare(imxpriv->epcs_rx_clk);
		clk_disable_unprepare(imxpriv->epcs_tx_clk);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	clk_disable_unprepare(imxpriv->sata_ref_clk);

	ahci_platक्रमm_disable_regulators(hpriv);
पूर्ण

अटल व्योम ahci_imx_error_handler(काष्ठा ata_port *ap)
अणु
	u32 reg_val;
	काष्ठा ata_device *dev;
	काष्ठा ata_host *host = dev_get_drvdata(ap->dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	काष्ठा imx_ahci_priv *imxpriv = hpriv->plat_data;

	ahci_error_handler(ap);

	अगर (!(imxpriv->first_समय) || ahci_imx_hotplug)
		वापस;

	imxpriv->first_समय = false;

	ata_क्रम_each_dev(dev, &ap->link, ENABLED)
		वापस;
	/*
	 * Disable link to save घातer.  An imx ahci port can't be recovered
	 * without full reset once the pddq mode is enabled making it
	 * impossible to use as part of libata LPM.
	 */
	reg_val = पढ़ोl(mmio + IMX_P0PHYCR);
	ग_लिखोl(reg_val | IMX_P0PHYCR_TEST_PDDQ, mmio + IMX_P0PHYCR);
	imx_sata_disable(hpriv);
	imxpriv->no_device = true;

	dev_info(ap->dev, "no device found, disabling link.\n");
	dev_info(ap->dev, "pass " MODULE_PARAM_PREFIX ".hotplug=1 to enable hotplug\n");
पूर्ण

अटल पूर्णांक ahci_imx_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
		       अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_host *host = dev_get_drvdata(ap->dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा imx_ahci_priv *imxpriv = hpriv->plat_data;
	पूर्णांक ret;

	अगर (imxpriv->type == AHCI_IMX53)
		ret = ahci_pmp_retry_srst_ops.softreset(link, class, deadline);
	अन्यथा
		ret = ahci_ops.softreset(link, class, deadline);

	वापस ret;
पूर्ण

अटल काष्ठा ata_port_operations ahci_imx_ops = अणु
	.inherits	= &ahci_ops,
	.host_stop	= ahci_imx_host_stop,
	.error_handler	= ahci_imx_error_handler,
	.softreset	= ahci_imx_softreset,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_imx_port_info = अणु
	.flags		= AHCI_FLAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_imx_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_ahci_of_match[] = अणु
	अणु .compatible = "fsl,imx53-ahci", .data = (व्योम *)AHCI_IMX53 पूर्ण,
	अणु .compatible = "fsl,imx6q-ahci", .data = (व्योम *)AHCI_IMX6Q पूर्ण,
	अणु .compatible = "fsl,imx6qp-ahci", .data = (व्योम *)AHCI_IMX6QP पूर्ण,
	अणु .compatible = "fsl,imx8qm-ahci", .data = (व्योम *)AHCI_IMX8QM पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_ahci_of_match);

काष्ठा reg_value अणु
	u32 of_value;
	u32 reg_value;
पूर्ण;

काष्ठा reg_property अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा reg_value *values;
	माप_प्रकार num_values;
	u32 def_value;
	u32 set_value;
पूर्ण;

अटल स्थिर काष्ठा reg_value gpr13_tx_level[] = अणु
	अणु  937, IMX6Q_GPR13_SATA_TX_LVL_0_937_V पूर्ण,
	अणु  947, IMX6Q_GPR13_SATA_TX_LVL_0_947_V पूर्ण,
	अणु  957, IMX6Q_GPR13_SATA_TX_LVL_0_957_V पूर्ण,
	अणु  966, IMX6Q_GPR13_SATA_TX_LVL_0_966_V पूर्ण,
	अणु  976, IMX6Q_GPR13_SATA_TX_LVL_0_976_V पूर्ण,
	अणु  986, IMX6Q_GPR13_SATA_TX_LVL_0_986_V पूर्ण,
	अणु  996, IMX6Q_GPR13_SATA_TX_LVL_0_996_V पूर्ण,
	अणु 1005, IMX6Q_GPR13_SATA_TX_LVL_1_005_V पूर्ण,
	अणु 1015, IMX6Q_GPR13_SATA_TX_LVL_1_015_V पूर्ण,
	अणु 1025, IMX6Q_GPR13_SATA_TX_LVL_1_025_V पूर्ण,
	अणु 1035, IMX6Q_GPR13_SATA_TX_LVL_1_035_V पूर्ण,
	अणु 1045, IMX6Q_GPR13_SATA_TX_LVL_1_045_V पूर्ण,
	अणु 1054, IMX6Q_GPR13_SATA_TX_LVL_1_054_V पूर्ण,
	अणु 1064, IMX6Q_GPR13_SATA_TX_LVL_1_064_V पूर्ण,
	अणु 1074, IMX6Q_GPR13_SATA_TX_LVL_1_074_V पूर्ण,
	अणु 1084, IMX6Q_GPR13_SATA_TX_LVL_1_084_V पूर्ण,
	अणु 1094, IMX6Q_GPR13_SATA_TX_LVL_1_094_V पूर्ण,
	अणु 1104, IMX6Q_GPR13_SATA_TX_LVL_1_104_V पूर्ण,
	अणु 1113, IMX6Q_GPR13_SATA_TX_LVL_1_113_V पूर्ण,
	अणु 1123, IMX6Q_GPR13_SATA_TX_LVL_1_123_V पूर्ण,
	अणु 1133, IMX6Q_GPR13_SATA_TX_LVL_1_133_V पूर्ण,
	अणु 1143, IMX6Q_GPR13_SATA_TX_LVL_1_143_V पूर्ण,
	अणु 1152, IMX6Q_GPR13_SATA_TX_LVL_1_152_V पूर्ण,
	अणु 1162, IMX6Q_GPR13_SATA_TX_LVL_1_162_V पूर्ण,
	अणु 1172, IMX6Q_GPR13_SATA_TX_LVL_1_172_V पूर्ण,
	अणु 1182, IMX6Q_GPR13_SATA_TX_LVL_1_182_V पूर्ण,
	अणु 1191, IMX6Q_GPR13_SATA_TX_LVL_1_191_V पूर्ण,
	अणु 1201, IMX6Q_GPR13_SATA_TX_LVL_1_201_V पूर्ण,
	अणु 1211, IMX6Q_GPR13_SATA_TX_LVL_1_211_V पूर्ण,
	अणु 1221, IMX6Q_GPR13_SATA_TX_LVL_1_221_V पूर्ण,
	अणु 1230, IMX6Q_GPR13_SATA_TX_LVL_1_230_V पूर्ण,
	अणु 1240, IMX6Q_GPR13_SATA_TX_LVL_1_240_V पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_value gpr13_tx_boost[] = अणु
	अणु    0, IMX6Q_GPR13_SATA_TX_BOOST_0_00_DB पूर्ण,
	अणु  370, IMX6Q_GPR13_SATA_TX_BOOST_0_37_DB पूर्ण,
	अणु  740, IMX6Q_GPR13_SATA_TX_BOOST_0_74_DB पूर्ण,
	अणु 1110, IMX6Q_GPR13_SATA_TX_BOOST_1_11_DB पूर्ण,
	अणु 1480, IMX6Q_GPR13_SATA_TX_BOOST_1_48_DB पूर्ण,
	अणु 1850, IMX6Q_GPR13_SATA_TX_BOOST_1_85_DB पूर्ण,
	अणु 2220, IMX6Q_GPR13_SATA_TX_BOOST_2_22_DB पूर्ण,
	अणु 2590, IMX6Q_GPR13_SATA_TX_BOOST_2_59_DB पूर्ण,
	अणु 2960, IMX6Q_GPR13_SATA_TX_BOOST_2_96_DB पूर्ण,
	अणु 3330, IMX6Q_GPR13_SATA_TX_BOOST_3_33_DB पूर्ण,
	अणु 3700, IMX6Q_GPR13_SATA_TX_BOOST_3_70_DB पूर्ण,
	अणु 4070, IMX6Q_GPR13_SATA_TX_BOOST_4_07_DB पूर्ण,
	अणु 4440, IMX6Q_GPR13_SATA_TX_BOOST_4_44_DB पूर्ण,
	अणु 4810, IMX6Q_GPR13_SATA_TX_BOOST_4_81_DB पूर्ण,
	अणु 5280, IMX6Q_GPR13_SATA_TX_BOOST_5_28_DB पूर्ण,
	अणु 5750, IMX6Q_GPR13_SATA_TX_BOOST_5_75_DB पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_value gpr13_tx_atten[] = अणु
	अणु  8, IMX6Q_GPR13_SATA_TX_ATTEN_8_16 पूर्ण,
	अणु  9, IMX6Q_GPR13_SATA_TX_ATTEN_9_16 पूर्ण,
	अणु 10, IMX6Q_GPR13_SATA_TX_ATTEN_10_16 पूर्ण,
	अणु 12, IMX6Q_GPR13_SATA_TX_ATTEN_12_16 पूर्ण,
	अणु 14, IMX6Q_GPR13_SATA_TX_ATTEN_14_16 पूर्ण,
	अणु 16, IMX6Q_GPR13_SATA_TX_ATTEN_16_16 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value gpr13_rx_eq[] = अणु
	अणु  500, IMX6Q_GPR13_SATA_RX_EQ_VAL_0_5_DB पूर्ण,
	अणु 1000, IMX6Q_GPR13_SATA_RX_EQ_VAL_1_0_DB पूर्ण,
	अणु 1500, IMX6Q_GPR13_SATA_RX_EQ_VAL_1_5_DB पूर्ण,
	अणु 2000, IMX6Q_GPR13_SATA_RX_EQ_VAL_2_0_DB पूर्ण,
	अणु 2500, IMX6Q_GPR13_SATA_RX_EQ_VAL_2_5_DB पूर्ण,
	अणु 3000, IMX6Q_GPR13_SATA_RX_EQ_VAL_3_0_DB पूर्ण,
	अणु 3500, IMX6Q_GPR13_SATA_RX_EQ_VAL_3_5_DB पूर्ण,
	अणु 4000, IMX6Q_GPR13_SATA_RX_EQ_VAL_4_0_DB पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_property gpr13_props[] = अणु
	अणु
		.name = "fsl,transmit-level-mV",
		.values = gpr13_tx_level,
		.num_values = ARRAY_SIZE(gpr13_tx_level),
		.def_value = IMX6Q_GPR13_SATA_TX_LVL_1_025_V,
	पूर्ण, अणु
		.name = "fsl,transmit-boost-mdB",
		.values = gpr13_tx_boost,
		.num_values = ARRAY_SIZE(gpr13_tx_boost),
		.def_value = IMX6Q_GPR13_SATA_TX_BOOST_3_33_DB,
	पूर्ण, अणु
		.name = "fsl,transmit-atten-16ths",
		.values = gpr13_tx_atten,
		.num_values = ARRAY_SIZE(gpr13_tx_atten),
		.def_value = IMX6Q_GPR13_SATA_TX_ATTEN_9_16,
	पूर्ण, अणु
		.name = "fsl,receive-eq-mdB",
		.values = gpr13_rx_eq,
		.num_values = ARRAY_SIZE(gpr13_rx_eq),
		.def_value = IMX6Q_GPR13_SATA_RX_EQ_VAL_3_0_DB,
	पूर्ण, अणु
		.name = "fsl,no-spread-spectrum",
		.def_value = IMX6Q_GPR13_SATA_MPLL_SS_EN,
		.set_value = 0,
	पूर्ण,
पूर्ण;

अटल u32 imx_ahci_parse_props(काष्ठा device *dev,
				स्थिर काष्ठा reg_property *prop, माप_प्रकार num)
अणु
	काष्ठा device_node *np = dev->of_node;
	u32 reg_value = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < num; i++, prop++) अणु
		u32 of_val;

		अगर (prop->num_values == 0) अणु
			अगर (of_property_पढ़ो_bool(np, prop->name))
				reg_value |= prop->set_value;
			अन्यथा
				reg_value |= prop->def_value;
			जारी;
		पूर्ण

		अगर (of_property_पढ़ो_u32(np, prop->name, &of_val)) अणु
			dev_info(dev, "%s not specified, using %08x\n",
				prop->name, prop->def_value);
			reg_value |= prop->def_value;
			जारी;
		पूर्ण

		क्रम (j = 0; j < prop->num_values; j++) अणु
			अगर (prop->values[j].of_value == of_val) अणु
				dev_info(dev, "%s value %u, using %08x\n",
					prop->name, of_val, prop->values[j].reg_value);
				reg_value |= prop->values[j].reg_value;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (j == prop->num_values) अणु
			dev_err(dev, "DT property %s is not a valid value\n",
				prop->name);
			reg_value |= prop->def_value;
		पूर्ण
	पूर्ण

	वापस reg_value;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक imx8_sata_probe(काष्ठा device *dev, काष्ठा imx_ahci_priv *imxpriv)
अणु
	काष्ठा resource *phy_res;
	काष्ठा platक्रमm_device *pdev = imxpriv->ahci_pdev;
	काष्ठा device_node *np = dev->of_node;

	अगर (of_property_पढ़ो_u32(np, "fsl,phy-imp", &imxpriv->imped_ratio))
		imxpriv->imped_ratio = IMX8QM_SATA_PHY_IMPED_RATIO_85OHM;
	phy_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	अगर (phy_res) अणु
		imxpriv->phy_base = devm_ioremap(dev, phy_res->start,
					resource_size(phy_res));
		अगर (!imxpriv->phy_base) अणु
			dev_err(dev, "error with ioremap\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "missing *phy* reg region.\n");
		वापस -ENOMEM;
	पूर्ण
	imxpriv->gpr =
		 syscon_regmap_lookup_by_phandle(np, "hsio");
	अगर (IS_ERR(imxpriv->gpr)) अणु
		dev_err(dev, "unable to find gpr registers\n");
		वापस PTR_ERR(imxpriv->gpr);
	पूर्ण

	imxpriv->epcs_tx_clk = devm_clk_get(dev, "epcs_tx");
	अगर (IS_ERR(imxpriv->epcs_tx_clk)) अणु
		dev_err(dev, "can't get epcs_tx_clk clock.\n");
		वापस PTR_ERR(imxpriv->epcs_tx_clk);
	पूर्ण
	imxpriv->epcs_rx_clk = devm_clk_get(dev, "epcs_rx");
	अगर (IS_ERR(imxpriv->epcs_rx_clk)) अणु
		dev_err(dev, "can't get epcs_rx_clk clock.\n");
		वापस PTR_ERR(imxpriv->epcs_rx_clk);
	पूर्ण
	imxpriv->phy_pclk0 = devm_clk_get(dev, "phy_pclk0");
	अगर (IS_ERR(imxpriv->phy_pclk0)) अणु
		dev_err(dev, "can't get phy_pclk0 clock.\n");
		वापस PTR_ERR(imxpriv->phy_pclk0);
	पूर्ण
	imxpriv->phy_pclk1 = devm_clk_get(dev, "phy_pclk1");
	अगर (IS_ERR(imxpriv->phy_pclk1)) अणु
		dev_err(dev, "can't get phy_pclk1 clock.\n");
		वापस PTR_ERR(imxpriv->phy_pclk1);
	पूर्ण
	imxpriv->phy_apbclk = devm_clk_get(dev, "phy_apbclk");
	अगर (IS_ERR(imxpriv->phy_apbclk)) अणु
		dev_err(dev, "can't get phy_apbclk clock.\n");
		वापस PTR_ERR(imxpriv->phy_apbclk);
	पूर्ण

	/* Fetch GPIO, then enable the बाह्यal OSC */
	imxpriv->clkreq_gpiod = devm_gpiod_get_optional(dev, "clkreq",
				GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(imxpriv->clkreq_gpiod))
		वापस PTR_ERR(imxpriv->clkreq_gpiod);
	अगर (imxpriv->clkreq_gpiod)
		gpiod_set_consumer_name(imxpriv->clkreq_gpiod, "SATA CLKREQ");

	वापस 0;
पूर्ण

अटल पूर्णांक imx_ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा imx_ahci_priv *imxpriv;
	अचिन्हित पूर्णांक reg_val;
	पूर्णांक ret;

	of_id = of_match_device(imx_ahci_of_match, dev);
	अगर (!of_id)
		वापस -EINVAL;

	imxpriv = devm_kzalloc(dev, माप(*imxpriv), GFP_KERNEL);
	अगर (!imxpriv)
		वापस -ENOMEM;

	imxpriv->ahci_pdev = pdev;
	imxpriv->no_device = false;
	imxpriv->first_समय = true;
	imxpriv->type = (क्रमागत ahci_imx_type)of_id->data;

	imxpriv->sata_clk = devm_clk_get(dev, "sata");
	अगर (IS_ERR(imxpriv->sata_clk)) अणु
		dev_err(dev, "can't get sata clock.\n");
		वापस PTR_ERR(imxpriv->sata_clk);
	पूर्ण

	imxpriv->sata_ref_clk = devm_clk_get(dev, "sata_ref");
	अगर (IS_ERR(imxpriv->sata_ref_clk)) अणु
		dev_err(dev, "can't get sata_ref clock.\n");
		वापस PTR_ERR(imxpriv->sata_ref_clk);
	पूर्ण

	imxpriv->ahb_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(imxpriv->ahb_clk)) अणु
		dev_err(dev, "can't get ahb clock.\n");
		वापस PTR_ERR(imxpriv->ahb_clk);
	पूर्ण

	अगर (imxpriv->type == AHCI_IMX6Q || imxpriv->type == AHCI_IMX6QP) अणु
		u32 reg_value;

		imxpriv->gpr = syscon_regmap_lookup_by_compatible(
							"fsl,imx6q-iomuxc-gpr");
		अगर (IS_ERR(imxpriv->gpr)) अणु
			dev_err(dev,
				"failed to find fsl,imx6q-iomux-gpr regmap\n");
			वापस PTR_ERR(imxpriv->gpr);
		पूर्ण

		reg_value = imx_ahci_parse_props(dev, gpr13_props,
						 ARRAY_SIZE(gpr13_props));

		imxpriv->phy_params =
				   IMX6Q_GPR13_SATA_RX_LOS_LVL_SATA2M |
				   IMX6Q_GPR13_SATA_RX_DPLL_MODE_2P_4F |
				   IMX6Q_GPR13_SATA_SPD_MODE_3P0G |
				   reg_value;
	पूर्ण अन्यथा अगर (imxpriv->type == AHCI_IMX8QM) अणु
		ret =  imx8_sata_probe(dev, imxpriv);
		अगर (ret)
			वापस ret;
	पूर्ण

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	hpriv->plat_data = imxpriv;

	ret = clk_prepare_enable(imxpriv->sata_clk);
	अगर (ret)
		वापस ret;

	अगर (imxpriv->type == AHCI_IMX53 &&
	    IS_ENABLED(CONFIG_HWMON)) अणु
		/* Add the temperature monitor */
		काष्ठा device *hwmon_dev;

		hwmon_dev =
			devm_hwmon_device_रेजिस्टर_with_groups(dev,
							"sata_ahci",
							hpriv,
							fsl_sata_ahci_groups);
		अगर (IS_ERR(hwmon_dev)) अणु
			ret = PTR_ERR(hwmon_dev);
			जाओ disable_clk;
		पूर्ण
		devm_thermal_zone_of_sensor_रेजिस्टर(hwmon_dev, 0, hwmon_dev,
					     &fsl_sata_ahci_of_thermal_ops);
		dev_info(dev, "%s: sensor 'sata_ahci'\n", dev_name(hwmon_dev));
	पूर्ण

	ret = imx_sata_enable(hpriv);
	अगर (ret)
		जाओ disable_clk;

	/*
	 * Configure the HWINIT bits of the HOST_CAP and HOST_PORTS_IMPL,
	 * and IP venकरोr specअगरic रेजिस्टर IMX_TIMER1MS.
	 * Configure CAP_SSS (support stagered spin up).
	 * Implement the port0.
	 * Get the ahb घड़ी rate, and configure the TIMER1MS रेजिस्टर.
	 */
	reg_val = पढ़ोl(hpriv->mmio + HOST_CAP);
	अगर (!(reg_val & HOST_CAP_SSS)) अणु
		reg_val |= HOST_CAP_SSS;
		ग_लिखोl(reg_val, hpriv->mmio + HOST_CAP);
	पूर्ण
	reg_val = पढ़ोl(hpriv->mmio + HOST_PORTS_IMPL);
	अगर (!(reg_val & 0x1)) अणु
		reg_val |= 0x1;
		ग_लिखोl(reg_val, hpriv->mmio + HOST_PORTS_IMPL);
	पूर्ण

	reg_val = clk_get_rate(imxpriv->ahb_clk) / 1000;
	ग_लिखोl(reg_val, hpriv->mmio + IMX_TIMER1MS);

	ret = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_imx_port_info,
				      &ahci_platक्रमm_sht);
	अगर (ret)
		जाओ disable_sata;

	वापस 0;

disable_sata:
	imx_sata_disable(hpriv);
disable_clk:
	clk_disable_unprepare(imxpriv->sata_clk);
	वापस ret;
पूर्ण

अटल व्योम ahci_imx_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा imx_ahci_priv *imxpriv = hpriv->plat_data;

	imx_sata_disable(hpriv);
	clk_disable_unprepare(imxpriv->sata_clk);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक imx_ahci_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक ret;

	ret = ahci_platक्रमm_suspend_host(dev);
	अगर (ret)
		वापस ret;

	imx_sata_disable(hpriv);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_ahci_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक ret;

	ret = imx_sata_enable(hpriv);
	अगर (ret)
		वापस ret;

	वापस ahci_platक्रमm_resume_host(dev);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ahci_imx_pm_ops, imx_ahci_suspend, imx_ahci_resume);

अटल काष्ठा platक्रमm_driver imx_ahci_driver = अणु
	.probe = imx_ahci_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = imx_ahci_of_match,
		.pm = &ahci_imx_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_ahci_driver);

MODULE_DESCRIPTION("Freescale i.MX AHCI SATA platform driver");
MODULE_AUTHOR("Richard Zhu <Hong-Xing.Zhu@freescale.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ahci:imx");
