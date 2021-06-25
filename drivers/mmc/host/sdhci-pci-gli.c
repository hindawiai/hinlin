<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Genesys Logic, Inc.
 *
 * Authors: Ben Chuang <ben.chuang@genesyslogic.com.tw>
 *
 * Version: v0.9.0 (2019-08-08)
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/pci.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/delay.h>
#समावेश "sdhci.h"
#समावेश "sdhci-pci.h"
#समावेश "cqhci.h"

/*  Genesys Logic extra रेजिस्टरs */
#घोषणा SDHCI_GLI_9750_WT         0x800
#घोषणा   SDHCI_GLI_9750_WT_EN      BIT(0)
#घोषणा   GLI_9750_WT_EN_ON	    0x1
#घोषणा   GLI_9750_WT_EN_OFF	    0x0

#घोषणा SDHCI_GLI_9750_CFG2          0x848
#घोषणा   SDHCI_GLI_9750_CFG2_L1DLY    GENMASK(28, 24)
#घोषणा   GLI_9750_CFG2_L1DLY_VALUE    0x1F

#घोषणा SDHCI_GLI_9750_DRIVING      0x860
#घोषणा   SDHCI_GLI_9750_DRIVING_1    GENMASK(11, 0)
#घोषणा   SDHCI_GLI_9750_DRIVING_2    GENMASK(27, 26)
#घोषणा   GLI_9750_DRIVING_1_VALUE    0xFFF
#घोषणा   GLI_9750_DRIVING_2_VALUE    0x3
#घोषणा   SDHCI_GLI_9750_SEL_1        BIT(29)
#घोषणा   SDHCI_GLI_9750_SEL_2        BIT(31)
#घोषणा   SDHCI_GLI_9750_ALL_RST      (BIT(24)|BIT(25)|BIT(28)|BIT(30))

#घोषणा SDHCI_GLI_9750_PLL	      0x864
#घोषणा   SDHCI_GLI_9750_PLL_LDIV       GENMASK(9, 0)
#घोषणा   SDHCI_GLI_9750_PLL_PDIV       GENMASK(14, 12)
#घोषणा   SDHCI_GLI_9750_PLL_सूची        BIT(15)
#घोषणा   SDHCI_GLI_9750_PLL_TX2_INV    BIT(23)
#घोषणा   SDHCI_GLI_9750_PLL_TX2_DLY    GENMASK(22, 20)
#घोषणा   GLI_9750_PLL_TX2_INV_VALUE    0x1
#घोषणा   GLI_9750_PLL_TX2_DLY_VALUE    0x0
#घोषणा   SDHCI_GLI_9750_PLLSSC_STEP    GENMASK(28, 24)
#घोषणा   SDHCI_GLI_9750_PLLSSC_EN      BIT(31)

#घोषणा SDHCI_GLI_9750_PLLSSC        0x86C
#घोषणा   SDHCI_GLI_9750_PLLSSC_PPM    GENMASK(31, 16)

#घोषणा SDHCI_GLI_9750_SW_CTRL      0x874
#घोषणा   SDHCI_GLI_9750_SW_CTRL_4    GENMASK(7, 6)
#घोषणा   GLI_9750_SW_CTRL_4_VALUE    0x3

#घोषणा SDHCI_GLI_9750_MISC            0x878
#घोषणा   SDHCI_GLI_9750_MISC_TX1_INV    BIT(2)
#घोषणा   SDHCI_GLI_9750_MISC_RX_INV     BIT(3)
#घोषणा   SDHCI_GLI_9750_MISC_TX1_DLY    GENMASK(6, 4)
#घोषणा   GLI_9750_MISC_TX1_INV_VALUE    0x0
#घोषणा   GLI_9750_MISC_RX_INV_ON        0x1
#घोषणा   GLI_9750_MISC_RX_INV_OFF       0x0
#घोषणा   GLI_9750_MISC_RX_INV_VALUE     GLI_9750_MISC_RX_INV_OFF
#घोषणा   GLI_9750_MISC_TX1_DLY_VALUE    0x5

#घोषणा SDHCI_GLI_9750_TUNING_CONTROL	          0x540
#घोषणा   SDHCI_GLI_9750_TUNING_CONTROL_EN          BIT(4)
#घोषणा   GLI_9750_TUNING_CONTROL_EN_ON             0x1
#घोषणा   GLI_9750_TUNING_CONTROL_EN_OFF            0x0
#घोषणा   SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_1    BIT(16)
#घोषणा   SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_2    GENMASK(20, 19)
#घोषणा   GLI_9750_TUNING_CONTROL_GLITCH_1_VALUE    0x1
#घोषणा   GLI_9750_TUNING_CONTROL_GLITCH_2_VALUE    0x2

#घोषणा SDHCI_GLI_9750_TUNING_PARAMETERS           0x544
#घोषणा   SDHCI_GLI_9750_TUNING_PARAMETERS_RX_DLY    GENMASK(2, 0)
#घोषणा   GLI_9750_TUNING_PARAMETERS_RX_DLY_VALUE    0x1

#घोषणा SDHCI_GLI_9763E_CTRL_HS400  0x7

#घोषणा SDHCI_GLI_9763E_HS400_ES_REG      0x52C
#घोषणा   SDHCI_GLI_9763E_HS400_ES_BIT      BIT(8)

#घोषणा PCIE_GLI_9763E_VHS	 0x884
#घोषणा   GLI_9763E_VHS_REV	   GENMASK(19, 16)
#घोषणा   GLI_9763E_VHS_REV_R      0x0
#घोषणा   GLI_9763E_VHS_REV_M      0x1
#घोषणा   GLI_9763E_VHS_REV_W      0x2
#घोषणा PCIE_GLI_9763E_MB	 0x888
#घोषणा   GLI_9763E_MB_CMDQ_OFF	   BIT(19)
#घोषणा   GLI_9763E_MB_ERP_ON      BIT(7)
#घोषणा PCIE_GLI_9763E_SCR	 0x8E0
#घोषणा   GLI_9763E_SCR_AXI_REQ	   BIT(9)

#घोषणा PCIE_GLI_9763E_CFG2      0x8A4
#घोषणा   GLI_9763E_CFG2_L1DLY     GENMASK(28, 19)
#घोषणा   GLI_9763E_CFG2_L1DLY_MID 0x50

#घोषणा PCIE_GLI_9763E_MMC_CTRL  0x960
#घोषणा   GLI_9763E_HS400_SLOW     BIT(3)

#घोषणा PCIE_GLI_9763E_CLKRXDLY  0x934
#घोषणा   GLI_9763E_HS400_RXDLY    GENMASK(31, 28)
#घोषणा   GLI_9763E_HS400_RXDLY_5  0x5

#घोषणा SDHCI_GLI_9763E_CQE_BASE_ADDR	 0x200
#घोषणा GLI_9763E_CQE_TRNS_MODE	   (SDHCI_TRNS_MULTI | \
				    SDHCI_TRNS_BLK_CNT_EN | \
				    SDHCI_TRNS_DMA)

#घोषणा PCI_GLI_9755_WT       0x800
#घोषणा   PCI_GLI_9755_WT_EN    BIT(0)
#घोषणा   GLI_9755_WT_EN_ON     0x1
#घोषणा   GLI_9755_WT_EN_OFF    0x0

#घोषणा PCI_GLI_9755_PECONF   0x44
#घोषणा   PCI_GLI_9755_LFCLK    GENMASK(14, 12)
#घोषणा   PCI_GLI_9755_DMACLK   BIT(29)

#घोषणा PCI_GLI_9755_CFG2          0x48
#घोषणा   PCI_GLI_9755_CFG2_L1DLY    GENMASK(28, 24)
#घोषणा   GLI_9755_CFG2_L1DLY_VALUE  0x1F

#घोषणा PCI_GLI_9755_PLL            0x64
#घोषणा   PCI_GLI_9755_PLL_LDIV       GENMASK(9, 0)
#घोषणा   PCI_GLI_9755_PLL_PDIV       GENMASK(14, 12)
#घोषणा   PCI_GLI_9755_PLL_सूची        BIT(15)
#घोषणा   PCI_GLI_9755_PLLSSC_STEP    GENMASK(28, 24)
#घोषणा   PCI_GLI_9755_PLLSSC_EN      BIT(31)

#घोषणा PCI_GLI_9755_PLLSSC        0x68
#घोषणा   PCI_GLI_9755_PLLSSC_PPM    GENMASK(15, 0)

#घोषणा PCI_GLI_9755_SerDes  0x70
#घोषणा PCI_GLI_9755_SCP_DIS   BIT(19)

#घोषणा GLI_MAX_TUNING_LOOP 40

/* Genesys Logic chipset */
अटल अंतरभूत व्योम gl9750_wt_on(काष्ठा sdhci_host *host)
अणु
	u32 wt_value;
	u32 wt_enable;

	wt_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_WT);
	wt_enable = FIELD_GET(SDHCI_GLI_9750_WT_EN, wt_value);

	अगर (wt_enable == GLI_9750_WT_EN_ON)
		वापस;

	wt_value &= ~SDHCI_GLI_9750_WT_EN;
	wt_value |= FIELD_PREP(SDHCI_GLI_9750_WT_EN, GLI_9750_WT_EN_ON);

	sdhci_ग_लिखोl(host, wt_value, SDHCI_GLI_9750_WT);
पूर्ण

अटल अंतरभूत व्योम gl9750_wt_off(काष्ठा sdhci_host *host)
अणु
	u32 wt_value;
	u32 wt_enable;

	wt_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_WT);
	wt_enable = FIELD_GET(SDHCI_GLI_9750_WT_EN, wt_value);

	अगर (wt_enable == GLI_9750_WT_EN_OFF)
		वापस;

	wt_value &= ~SDHCI_GLI_9750_WT_EN;
	wt_value |= FIELD_PREP(SDHCI_GLI_9750_WT_EN, GLI_9750_WT_EN_OFF);

	sdhci_ग_लिखोl(host, wt_value, SDHCI_GLI_9750_WT);
पूर्ण

अटल व्योम gli_set_9750(काष्ठा sdhci_host *host)
अणु
	u32 driving_value;
	u32 pll_value;
	u32 sw_ctrl_value;
	u32 misc_value;
	u32 parameter_value;
	u32 control_value;
	u16 ctrl2;

	gl9750_wt_on(host);

	driving_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_DRIVING);
	pll_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_PLL);
	sw_ctrl_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_SW_CTRL);
	misc_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_MISC);
	parameter_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_TUNING_PARAMETERS);
	control_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_TUNING_CONTROL);

	driving_value &= ~(SDHCI_GLI_9750_DRIVING_1);
	driving_value &= ~(SDHCI_GLI_9750_DRIVING_2);
	driving_value |= FIELD_PREP(SDHCI_GLI_9750_DRIVING_1,
				    GLI_9750_DRIVING_1_VALUE);
	driving_value |= FIELD_PREP(SDHCI_GLI_9750_DRIVING_2,
				    GLI_9750_DRIVING_2_VALUE);
	driving_value &= ~(SDHCI_GLI_9750_SEL_1|SDHCI_GLI_9750_SEL_2|SDHCI_GLI_9750_ALL_RST);
	driving_value |= SDHCI_GLI_9750_SEL_2;
	sdhci_ग_लिखोl(host, driving_value, SDHCI_GLI_9750_DRIVING);

	sw_ctrl_value &= ~SDHCI_GLI_9750_SW_CTRL_4;
	sw_ctrl_value |= FIELD_PREP(SDHCI_GLI_9750_SW_CTRL_4,
				    GLI_9750_SW_CTRL_4_VALUE);
	sdhci_ग_लिखोl(host, sw_ctrl_value, SDHCI_GLI_9750_SW_CTRL);

	/* reset the tuning flow after reinit and beक्रमe starting tuning */
	pll_value &= ~SDHCI_GLI_9750_PLL_TX2_INV;
	pll_value &= ~SDHCI_GLI_9750_PLL_TX2_DLY;
	pll_value |= FIELD_PREP(SDHCI_GLI_9750_PLL_TX2_INV,
				GLI_9750_PLL_TX2_INV_VALUE);
	pll_value |= FIELD_PREP(SDHCI_GLI_9750_PLL_TX2_DLY,
				GLI_9750_PLL_TX2_DLY_VALUE);

	misc_value &= ~SDHCI_GLI_9750_MISC_TX1_INV;
	misc_value &= ~SDHCI_GLI_9750_MISC_RX_INV;
	misc_value &= ~SDHCI_GLI_9750_MISC_TX1_DLY;
	misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_TX1_INV,
				 GLI_9750_MISC_TX1_INV_VALUE);
	misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_RX_INV,
				 GLI_9750_MISC_RX_INV_VALUE);
	misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_TX1_DLY,
				 GLI_9750_MISC_TX1_DLY_VALUE);

	parameter_value &= ~SDHCI_GLI_9750_TUNING_PARAMETERS_RX_DLY;
	parameter_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_PARAMETERS_RX_DLY,
				      GLI_9750_TUNING_PARAMETERS_RX_DLY_VALUE);

	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_1;
	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_2;
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_1,
				    GLI_9750_TUNING_CONTROL_GLITCH_1_VALUE);
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_GLITCH_2,
				    GLI_9750_TUNING_CONTROL_GLITCH_2_VALUE);

	sdhci_ग_लिखोl(host, pll_value, SDHCI_GLI_9750_PLL);
	sdhci_ग_लिखोl(host, misc_value, SDHCI_GLI_9750_MISC);

	/* disable tuned clk */
	ctrl2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	ctrl2 &= ~SDHCI_CTRL_TUNED_CLK;
	sdhci_ग_लिखोw(host, ctrl2, SDHCI_HOST_CONTROL2);

	/* enable tuning parameters control */
	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_EN;
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_EN,
				    GLI_9750_TUNING_CONTROL_EN_ON);
	sdhci_ग_लिखोl(host, control_value, SDHCI_GLI_9750_TUNING_CONTROL);

	/* ग_लिखो tuning parameters */
	sdhci_ग_लिखोl(host, parameter_value, SDHCI_GLI_9750_TUNING_PARAMETERS);

	/* disable tuning parameters control */
	control_value &= ~SDHCI_GLI_9750_TUNING_CONTROL_EN;
	control_value |= FIELD_PREP(SDHCI_GLI_9750_TUNING_CONTROL_EN,
				    GLI_9750_TUNING_CONTROL_EN_OFF);
	sdhci_ग_लिखोl(host, control_value, SDHCI_GLI_9750_TUNING_CONTROL);

	/* clear tuned clk */
	ctrl2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	ctrl2 &= ~SDHCI_CTRL_TUNED_CLK;
	sdhci_ग_लिखोw(host, ctrl2, SDHCI_HOST_CONTROL2);

	gl9750_wt_off(host);
पूर्ण

अटल व्योम gli_set_9750_rx_inv(काष्ठा sdhci_host *host, bool b)
अणु
	u32 misc_value;

	gl9750_wt_on(host);

	misc_value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_MISC);
	misc_value &= ~SDHCI_GLI_9750_MISC_RX_INV;
	अगर (b) अणु
		misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_RX_INV,
					 GLI_9750_MISC_RX_INV_ON);
	पूर्ण अन्यथा अणु
		misc_value |= FIELD_PREP(SDHCI_GLI_9750_MISC_RX_INV,
					 GLI_9750_MISC_RX_INV_OFF);
	पूर्ण
	sdhci_ग_लिखोl(host, misc_value, SDHCI_GLI_9750_MISC);

	gl9750_wt_off(host);
पूर्ण

अटल पूर्णांक __sdhci_execute_tuning_9750(काष्ठा sdhci_host *host, u32 opcode)
अणु
	पूर्णांक i;
	पूर्णांक rx_inv;

	क्रम (rx_inv = 0; rx_inv < 2; rx_inv++) अणु
		gli_set_9750_rx_inv(host, !!rx_inv);
		sdhci_start_tuning(host);

		क्रम (i = 0; i < GLI_MAX_TUNING_LOOP; i++) अणु
			u16 ctrl;

			sdhci_send_tuning(host, opcode);

			अगर (!host->tuning_करोne) अणु
				sdhci_पात_tuning(host, opcode);
				अवरोध;
			पूर्ण

			ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
			अगर (!(ctrl & SDHCI_CTRL_EXEC_TUNING)) अणु
				अगर (ctrl & SDHCI_CTRL_TUNED_CLK)
					वापस 0; /* Success! */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!host->tuning_करोne) अणु
		pr_info("%s: Tuning timeout, falling back to fixed sampling clock\n",
			mmc_hostname(host->mmc));
		वापस -ETIMEDOUT;
	पूर्ण

	pr_info("%s: Tuning failed, falling back to fixed sampling clock\n",
		mmc_hostname(host->mmc));
	sdhci_reset_tuning(host);

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक gl9750_execute_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	host->mmc->retune_period = 0;
	अगर (host->tuning_mode == SDHCI_TUNING_MODE_1)
		host->mmc->retune_period = host->tuning_count;

	gli_set_9750(host);
	host->tuning_err = __sdhci_execute_tuning_9750(host, opcode);
	sdhci_end_tuning(host);

	वापस 0;
पूर्ण

अटल व्योम gl9750_disable_ssc_pll(काष्ठा sdhci_host *host)
अणु
	u32 pll;

	gl9750_wt_on(host);
	pll = sdhci_पढ़ोl(host, SDHCI_GLI_9750_PLL);
	pll &= ~(SDHCI_GLI_9750_PLL_सूची | SDHCI_GLI_9750_PLLSSC_EN);
	sdhci_ग_लिखोl(host, pll, SDHCI_GLI_9750_PLL);
	gl9750_wt_off(host);
पूर्ण

अटल व्योम gl9750_set_pll(काष्ठा sdhci_host *host, u8 dir, u16 द_भाग, u8 pभाग)
अणु
	u32 pll;

	gl9750_wt_on(host);
	pll = sdhci_पढ़ोl(host, SDHCI_GLI_9750_PLL);
	pll &= ~(SDHCI_GLI_9750_PLL_LDIV |
		 SDHCI_GLI_9750_PLL_PDIV |
		 SDHCI_GLI_9750_PLL_सूची);
	pll |= FIELD_PREP(SDHCI_GLI_9750_PLL_LDIV, द_भाग) |
	       FIELD_PREP(SDHCI_GLI_9750_PLL_PDIV, pभाग) |
	       FIELD_PREP(SDHCI_GLI_9750_PLL_सूची, dir);
	sdhci_ग_लिखोl(host, pll, SDHCI_GLI_9750_PLL);
	gl9750_wt_off(host);

	/* रुको क्रम pll stable */
	mdelay(1);
पूर्ण

अटल व्योम gl9750_set_ssc(काष्ठा sdhci_host *host, u8 enable, u8 step, u16 ppm)
अणु
	u32 pll;
	u32 ssc;

	gl9750_wt_on(host);
	pll = sdhci_पढ़ोl(host, SDHCI_GLI_9750_PLL);
	ssc = sdhci_पढ़ोl(host, SDHCI_GLI_9750_PLLSSC);
	pll &= ~(SDHCI_GLI_9750_PLLSSC_STEP |
		 SDHCI_GLI_9750_PLLSSC_EN);
	ssc &= ~SDHCI_GLI_9750_PLLSSC_PPM;
	pll |= FIELD_PREP(SDHCI_GLI_9750_PLLSSC_STEP, step) |
	       FIELD_PREP(SDHCI_GLI_9750_PLLSSC_EN, enable);
	ssc |= FIELD_PREP(SDHCI_GLI_9750_PLLSSC_PPM, ppm);
	sdhci_ग_लिखोl(host, ssc, SDHCI_GLI_9750_PLLSSC);
	sdhci_ग_लिखोl(host, pll, SDHCI_GLI_9750_PLL);
	gl9750_wt_off(host);
पूर्ण

अटल व्योम gl9750_set_ssc_pll_205mhz(काष्ठा sdhci_host *host)
अणु
	/* set pll to 205MHz and enable ssc */
	gl9750_set_ssc(host, 0x1, 0x1F, 0xFFE7);
	gl9750_set_pll(host, 0x1, 0x246, 0x0);
पूर्ण

अटल व्योम sdhci_gl9750_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा mmc_ios *ios = &host->mmc->ios;
	u16 clk;

	host->mmc->actual_घड़ी = 0;

	gl9750_disable_ssc_pll(host);
	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	clk = sdhci_calc_clk(host, घड़ी, &host->mmc->actual_घड़ी);
	अगर (घड़ी == 200000000 && ios->timing == MMC_TIMING_UHS_SDR104) अणु
		host->mmc->actual_घड़ी = 205000000;
		gl9750_set_ssc_pll_205mhz(host);
	पूर्ण

	sdhci_enable_clk(host, clk);
पूर्ण

अटल व्योम gl9750_hw_setting(काष्ठा sdhci_host *host)
अणु
	u32 value;

	gl9750_wt_on(host);

	value = sdhci_पढ़ोl(host, SDHCI_GLI_9750_CFG2);
	value &= ~SDHCI_GLI_9750_CFG2_L1DLY;
	/* set ASPM L1 entry delay to 7.9us */
	value |= FIELD_PREP(SDHCI_GLI_9750_CFG2_L1DLY,
			    GLI_9750_CFG2_L1DLY_VALUE);
	sdhci_ग_लिखोl(host, value, SDHCI_GLI_9750_CFG2);

	gl9750_wt_off(host);
पूर्ण

अटल व्योम gli_pcie_enable_msi(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक ret;

	ret = pci_alloc_irq_vectors(slot->chip->pdev, 1, 1,
				    PCI_IRQ_MSI | PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		pr_warn("%s: enable PCI MSI failed, error=%d\n",
		       mmc_hostname(slot->host->mmc), ret);
		वापस;
	पूर्ण

	slot->host->irq = pci_irq_vector(slot->chip->pdev, 0);
पूर्ण

अटल अंतरभूत व्योम gl9755_wt_on(काष्ठा pci_dev *pdev)
अणु
	u32 wt_value;
	u32 wt_enable;

	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_WT, &wt_value);
	wt_enable = FIELD_GET(PCI_GLI_9755_WT_EN, wt_value);

	अगर (wt_enable == GLI_9755_WT_EN_ON)
		वापस;

	wt_value &= ~PCI_GLI_9755_WT_EN;
	wt_value |= FIELD_PREP(PCI_GLI_9755_WT_EN, GLI_9755_WT_EN_ON);

	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_WT, wt_value);
पूर्ण

अटल अंतरभूत व्योम gl9755_wt_off(काष्ठा pci_dev *pdev)
अणु
	u32 wt_value;
	u32 wt_enable;

	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_WT, &wt_value);
	wt_enable = FIELD_GET(PCI_GLI_9755_WT_EN, wt_value);

	अगर (wt_enable == GLI_9755_WT_EN_OFF)
		वापस;

	wt_value &= ~PCI_GLI_9755_WT_EN;
	wt_value |= FIELD_PREP(PCI_GLI_9755_WT_EN, GLI_9755_WT_EN_OFF);

	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_WT, wt_value);
पूर्ण

अटल व्योम gl9755_disable_ssc_pll(काष्ठा pci_dev *pdev)
अणु
	u32 pll;

	gl9755_wt_on(pdev);
	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_PLL, &pll);
	pll &= ~(PCI_GLI_9755_PLL_सूची | PCI_GLI_9755_PLLSSC_EN);
	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_PLL, pll);
	gl9755_wt_off(pdev);
पूर्ण

अटल व्योम gl9755_set_pll(काष्ठा pci_dev *pdev, u8 dir, u16 द_भाग, u8 pभाग)
अणु
	u32 pll;

	gl9755_wt_on(pdev);
	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_PLL, &pll);
	pll &= ~(PCI_GLI_9755_PLL_LDIV |
		 PCI_GLI_9755_PLL_PDIV |
		 PCI_GLI_9755_PLL_सूची);
	pll |= FIELD_PREP(PCI_GLI_9755_PLL_LDIV, द_भाग) |
	       FIELD_PREP(PCI_GLI_9755_PLL_PDIV, pभाग) |
	       FIELD_PREP(PCI_GLI_9755_PLL_सूची, dir);
	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_PLL, pll);
	gl9755_wt_off(pdev);

	/* रुको क्रम pll stable */
	mdelay(1);
पूर्ण

अटल व्योम gl9755_set_ssc(काष्ठा pci_dev *pdev, u8 enable, u8 step, u16 ppm)
अणु
	u32 pll;
	u32 ssc;

	gl9755_wt_on(pdev);
	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_PLL, &pll);
	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_PLLSSC, &ssc);
	pll &= ~(PCI_GLI_9755_PLLSSC_STEP |
		 PCI_GLI_9755_PLLSSC_EN);
	ssc &= ~PCI_GLI_9755_PLLSSC_PPM;
	pll |= FIELD_PREP(PCI_GLI_9755_PLLSSC_STEP, step) |
	       FIELD_PREP(PCI_GLI_9755_PLLSSC_EN, enable);
	ssc |= FIELD_PREP(PCI_GLI_9755_PLLSSC_PPM, ppm);
	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_PLLSSC, ssc);
	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_PLL, pll);
	gl9755_wt_off(pdev);
पूर्ण

अटल व्योम gl9755_set_ssc_pll_205mhz(काष्ठा pci_dev *pdev)
अणु
	/* set pll to 205MHz and enable ssc */
	gl9755_set_ssc(pdev, 0x1, 0x1F, 0xFFE7);
	gl9755_set_pll(pdev, 0x1, 0x246, 0x0);
पूर्ण

अटल व्योम sdhci_gl9755_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा mmc_ios *ios = &host->mmc->ios;
	काष्ठा pci_dev *pdev;
	u16 clk;

	pdev = slot->chip->pdev;
	host->mmc->actual_घड़ी = 0;

	gl9755_disable_ssc_pll(pdev);
	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	clk = sdhci_calc_clk(host, घड़ी, &host->mmc->actual_घड़ी);
	अगर (घड़ी == 200000000 && ios->timing == MMC_TIMING_UHS_SDR104) अणु
		host->mmc->actual_घड़ी = 205000000;
		gl9755_set_ssc_pll_205mhz(pdev);
	पूर्ण

	sdhci_enable_clk(host, clk);
पूर्ण

अटल व्योम gl9755_hw_setting(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा pci_dev *pdev = slot->chip->pdev;
	u32 value;

	gl9755_wt_on(pdev);

	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_PECONF, &value);
	value &= ~PCI_GLI_9755_LFCLK;
	value &= ~PCI_GLI_9755_DMACLK;
	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_PECONF, value);

	/* enable लघु circuit protection */
	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_SerDes, &value);
	value &= ~PCI_GLI_9755_SCP_DIS;
	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_SerDes, value);

	pci_पढ़ो_config_dword(pdev, PCI_GLI_9755_CFG2, &value);
	value &= ~PCI_GLI_9755_CFG2_L1DLY;
	/* set ASPM L1 entry delay to 7.9us */
	value |= FIELD_PREP(PCI_GLI_9755_CFG2_L1DLY,
			    GLI_9755_CFG2_L1DLY_VALUE);
	pci_ग_लिखो_config_dword(pdev, PCI_GLI_9755_CFG2, value);

	gl9755_wt_off(pdev);
पूर्ण

अटल पूर्णांक gli_probe_slot_gl9750(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा sdhci_host *host = slot->host;

	gl9750_hw_setting(host);
	gli_pcie_enable_msi(slot);
	slot->host->mmc->caps2 |= MMC_CAP2_NO_SDIO;
	sdhci_enable_v4_mode(host);

	वापस 0;
पूर्ण

अटल पूर्णांक gli_probe_slot_gl9755(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा sdhci_host *host = slot->host;

	gl9755_hw_setting(slot);
	gli_pcie_enable_msi(slot);
	slot->host->mmc->caps2 |= MMC_CAP2_NO_SDIO;
	sdhci_enable_v4_mode(host);

	वापस 0;
पूर्ण

अटल व्योम sdhci_gli_voltage_चयन(काष्ठा sdhci_host *host)
अणु
	/*
	 * According to Section 3.6.1 संकेत voltage चयन procedure in
	 * SD Host Controller Simplअगरied Spec. 4.20, steps 6~8 are as
	 * follows:
	 * (6) Set 1.8V Signal Enable in the Host Control 2 रेजिस्टर.
	 * (7) Wait 5ms. 1.8V voltage regulator shall be stable within this
	 *     period.
	 * (8) If 1.8V Signal Enable is cleared by Host Controller, go to
	 *     step (12).
	 *
	 * Wait 5ms after set 1.8V संकेत enable in Host Control 2 रेजिस्टर
	 * to ensure 1.8V संकेत enable bit is set by GL9750/GL9755.
	 *
	 * ...however, the controller in the NUC10i3FNK4 (a 9755) requires
	 * slightly दीर्घer than 5ms beक्रमe the control रेजिस्टर reports that
	 * 1.8V is पढ़ोy, and far दीर्घer still beक्रमe the card will actually
	 * work reliably.
	 */
	usleep_range(100000, 110000);
पूर्ण

अटल व्योम sdhci_gl9750_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	sdhci_reset(host, mask);
	gli_set_9750(host);
पूर्ण

अटल u32 sdhci_gl9750_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 value;

	value = पढ़ोl(host->ioaddr + reg);
	अगर (unlikely(reg == SDHCI_MAX_CURRENT && !(value & 0xff)))
		value |= 0xc8;

	वापस value;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_pci_gli_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा sdhci_pci_slot *slot = chip->slots[0];

	pci_मुक्त_irq_vectors(slot->chip->pdev);
	gli_pcie_enable_msi(slot);

	वापस sdhci_pci_resume_host(chip);
पूर्ण

अटल पूर्णांक sdhci_cqhci_gli_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा sdhci_pci_slot *slot = chip->slots[0];
	पूर्णांक ret;

	ret = sdhci_pci_gli_resume(chip);
	अगर (ret)
		वापस ret;

	वापस cqhci_resume(slot->host->mmc);
पूर्ण

अटल पूर्णांक sdhci_cqhci_gli_suspend(काष्ठा sdhci_pci_chip *chip)
अणु
	काष्ठा sdhci_pci_slot *slot = chip->slots[0];
	पूर्णांक ret;

	ret = cqhci_suspend(slot->host->mmc);
	अगर (ret)
		वापस ret;

	वापस sdhci_suspend_host(slot->host);
पूर्ण
#पूर्ण_अगर

अटल व्योम gl9763e_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
					  काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 val;

	val = sdhci_पढ़ोl(host, SDHCI_GLI_9763E_HS400_ES_REG);
	अगर (ios->enhanced_strobe)
		val |= SDHCI_GLI_9763E_HS400_ES_BIT;
	अन्यथा
		val &= ~SDHCI_GLI_9763E_HS400_ES_BIT;

	sdhci_ग_लिखोl(host, val, SDHCI_GLI_9763E_HS400_ES_REG);
पूर्ण

अटल व्योम sdhci_set_gl9763e_संकेतing(काष्ठा sdhci_host *host,
					अचिन्हित पूर्णांक timing)
अणु
	u16 ctrl_2;

	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	अगर (timing == MMC_TIMING_MMC_HS200)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
	अन्यथा अगर (timing == MMC_TIMING_MMC_HS)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
	अन्यथा अगर (timing == MMC_TIMING_MMC_DDR52)
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
	अन्यथा अगर (timing == MMC_TIMING_MMC_HS400)
		ctrl_2 |= SDHCI_GLI_9763E_CTRL_HS400;

	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
पूर्ण

अटल व्योम sdhci_gl9763e_dumpregs(काष्ठा mmc_host *mmc)
अणु
	sdhci_dumpregs(mmc_priv(mmc));
पूर्ण

अटल व्योम sdhci_gl9763e_cqe_pre_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u32 value;

	value = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
	value |= CQHCI_ENABLE;
	cqhci_ग_लिखोl(cq_host, value, CQHCI_CFG);
पूर्ण

अटल व्योम sdhci_gl9763e_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	sdhci_ग_लिखोw(host, GLI_9763E_CQE_TRNS_MODE, SDHCI_TRANSFER_MODE);
	sdhci_cqe_enable(mmc);
पूर्ण

अटल u32 sdhci_gl9763e_cqhci_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);

	वापस 0;
पूर्ण

अटल व्योम sdhci_gl9763e_cqe_post_disable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u32 value;

	value = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
	value &= ~CQHCI_ENABLE;
	cqhci_ग_लिखोl(cq_host, value, CQHCI_CFG);
	sdhci_ग_लिखोw(host, 0x0, SDHCI_TRANSFER_MODE);
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops sdhci_gl9763e_cqhci_ops = अणु
	.enable         = sdhci_gl9763e_cqe_enable,
	.disable        = sdhci_cqe_disable,
	.dumpregs       = sdhci_gl9763e_dumpregs,
	.pre_enable     = sdhci_gl9763e_cqe_pre_enable,
	.post_disable   = sdhci_gl9763e_cqe_post_disable,
पूर्ण;

अटल पूर्णांक gl9763e_add_host(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा device *dev = &slot->chip->pdev->dev;
	काष्ठा sdhci_host *host = slot->host;
	काष्ठा cqhci_host *cq_host;
	bool dma64;
	पूर्णांक ret;

	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	cq_host = devm_kzalloc(dev, माप(*cq_host), GFP_KERNEL);
	अगर (!cq_host) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	cq_host->mmio = host->ioaddr + SDHCI_GLI_9763E_CQE_BASE_ADDR;
	cq_host->ops = &sdhci_gl9763e_cqhci_ops;

	dma64 = host->flags & SDHCI_USE_64_BIT_DMA;
	अगर (dma64)
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	ret = cqhci_init(cq_host, host->mmc, dma64);
	अगर (ret)
		जाओ cleanup;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ cleanup;

	वापस 0;

cleanup:
	sdhci_cleanup_host(host);
	वापस ret;
पूर्ण

अटल व्योम sdhci_gl9763e_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	अगर ((host->mmc->caps2 & MMC_CAP2_CQE) && (mask & SDHCI_RESET_ALL) &&
	    host->mmc->cqe_निजी)
		cqhci_deactivate(host->mmc);
	sdhci_reset(host, mask);
पूर्ण

अटल व्योम gli_set_gl9763e(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा pci_dev *pdev = slot->chip->pdev;
	u32 value;

	pci_पढ़ो_config_dword(pdev, PCIE_GLI_9763E_VHS, &value);
	value &= ~GLI_9763E_VHS_REV;
	value |= FIELD_PREP(GLI_9763E_VHS_REV, GLI_9763E_VHS_REV_W);
	pci_ग_लिखो_config_dword(pdev, PCIE_GLI_9763E_VHS, value);

	pci_पढ़ो_config_dword(pdev, PCIE_GLI_9763E_SCR, &value);
	value |= GLI_9763E_SCR_AXI_REQ;
	pci_ग_लिखो_config_dword(pdev, PCIE_GLI_9763E_SCR, value);

	pci_पढ़ो_config_dword(pdev, PCIE_GLI_9763E_MMC_CTRL, &value);
	value &= ~GLI_9763E_HS400_SLOW;
	pci_ग_लिखो_config_dword(pdev, PCIE_GLI_9763E_MMC_CTRL, value);

	pci_पढ़ो_config_dword(pdev, PCIE_GLI_9763E_CFG2, &value);
	value &= ~GLI_9763E_CFG2_L1DLY;
	/* set ASPM L1 entry delay to 20us */
	value |= FIELD_PREP(GLI_9763E_CFG2_L1DLY, GLI_9763E_CFG2_L1DLY_MID);
	pci_ग_लिखो_config_dword(pdev, PCIE_GLI_9763E_CFG2, value);

	pci_पढ़ो_config_dword(pdev, PCIE_GLI_9763E_CLKRXDLY, &value);
	value &= ~GLI_9763E_HS400_RXDLY;
	value |= FIELD_PREP(GLI_9763E_HS400_RXDLY, GLI_9763E_HS400_RXDLY_5);
	pci_ग_लिखो_config_dword(pdev, PCIE_GLI_9763E_CLKRXDLY, value);

	pci_पढ़ो_config_dword(pdev, PCIE_GLI_9763E_VHS, &value);
	value &= ~GLI_9763E_VHS_REV;
	value |= FIELD_PREP(GLI_9763E_VHS_REV, GLI_9763E_VHS_REV_R);
	pci_ग_लिखो_config_dword(pdev, PCIE_GLI_9763E_VHS, value);
पूर्ण

अटल पूर्णांक gli_probe_slot_gl9763e(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा pci_dev *pdev = slot->chip->pdev;
	काष्ठा sdhci_host *host = slot->host;
	u32 value;

	host->mmc->caps |= MMC_CAP_8_BIT_DATA |
			   MMC_CAP_1_8V_DDR |
			   MMC_CAP_NONREMOVABLE;
	host->mmc->caps2 |= MMC_CAP2_HS200_1_8V_SDR |
			    MMC_CAP2_HS400_1_8V |
			    MMC_CAP2_HS400_ES |
			    MMC_CAP2_NO_SDIO |
			    MMC_CAP2_NO_SD;

	pci_पढ़ो_config_dword(pdev, PCIE_GLI_9763E_MB, &value);
	अगर (!(value & GLI_9763E_MB_CMDQ_OFF))
		अगर (value & GLI_9763E_MB_ERP_ON)
			host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;

	gli_pcie_enable_msi(slot);
	host->mmc_host_ops.hs400_enhanced_strobe =
					gl9763e_hs400_enhanced_strobe;
	gli_set_gl9763e(slot);
	sdhci_enable_v4_mode(host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_gl9755_ops = अणु
	.set_घड़ी		= sdhci_gl9755_set_घड़ी,
	.enable_dma		= sdhci_pci_enable_dma,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= sdhci_reset,
	.set_uhs_संकेतing	= sdhci_set_uhs_संकेतing,
	.voltage_चयन		= sdhci_gli_voltage_चयन,
पूर्ण;

स्थिर काष्ठा sdhci_pci_fixes sdhci_gl9755 = अणु
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.quirks2	= SDHCI_QUIRK2_BROKEN_DDR50,
	.probe_slot	= gli_probe_slot_gl9755,
	.ops            = &sdhci_gl9755_ops,
#अगर_घोषित CONFIG_PM_SLEEP
	.resume         = sdhci_pci_gli_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_gl9750_ops = अणु
	.पढ़ो_l                 = sdhci_gl9750_पढ़ोl,
	.set_घड़ी		= sdhci_gl9750_set_घड़ी,
	.enable_dma		= sdhci_pci_enable_dma,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= sdhci_gl9750_reset,
	.set_uhs_संकेतing	= sdhci_set_uhs_संकेतing,
	.voltage_चयन		= sdhci_gli_voltage_चयन,
	.platक्रमm_execute_tuning = gl9750_execute_tuning,
पूर्ण;

स्थिर काष्ठा sdhci_pci_fixes sdhci_gl9750 = अणु
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.quirks2	= SDHCI_QUIRK2_BROKEN_DDR50,
	.probe_slot	= gli_probe_slot_gl9750,
	.ops            = &sdhci_gl9750_ops,
#अगर_घोषित CONFIG_PM_SLEEP
	.resume         = sdhci_pci_gli_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_gl9763e_ops = अणु
	.set_घड़ी		= sdhci_set_घड़ी,
	.enable_dma		= sdhci_pci_enable_dma,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= sdhci_gl9763e_reset,
	.set_uhs_संकेतing	= sdhci_set_gl9763e_संकेतing,
	.voltage_चयन		= sdhci_gli_voltage_चयन,
	.irq                    = sdhci_gl9763e_cqhci_irq,
पूर्ण;

स्थिर काष्ठा sdhci_pci_fixes sdhci_gl9763e = अणु
	.quirks		= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.probe_slot	= gli_probe_slot_gl9763e,
	.ops            = &sdhci_gl9763e_ops,
#अगर_घोषित CONFIG_PM_SLEEP
	.resume		= sdhci_cqhci_gli_resume,
	.suspend	= sdhci_cqhci_gli_suspend,
#पूर्ण_अगर
	.add_host       = gl9763e_add_host,
पूर्ण;
