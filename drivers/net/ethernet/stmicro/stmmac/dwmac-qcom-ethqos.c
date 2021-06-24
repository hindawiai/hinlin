<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018-19, Linaro Limited

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

#घोषणा RGMII_IO_MACRO_CONFIG		0x0
#घोषणा SDCC_HC_REG_DLL_CONFIG		0x4
#घोषणा SDCC_HC_REG_DDR_CONFIG		0xC
#घोषणा SDCC_HC_REG_DLL_CONFIG2		0x10
#घोषणा SDC4_STATUS			0x14
#घोषणा SDCC_USR_CTL			0x18
#घोषणा RGMII_IO_MACRO_CONFIG2		0x1C
#घोषणा RGMII_IO_MACRO_DEBUG1		0x20
#घोषणा EMAC_SYSTEM_LOW_POWER_DEBUG	0x28

/* RGMII_IO_MACRO_CONFIG fields */
#घोषणा RGMII_CONFIG_FUNC_CLK_EN		BIT(30)
#घोषणा RGMII_CONFIG_POS_NEG_DATA_SEL		BIT(23)
#घोषणा RGMII_CONFIG_GPIO_CFG_RX_INT		GENMASK(21, 20)
#घोषणा RGMII_CONFIG_GPIO_CFG_TX_INT		GENMASK(19, 17)
#घोषणा RGMII_CONFIG_MAX_SPD_PRG_9		GENMASK(16, 8)
#घोषणा RGMII_CONFIG_MAX_SPD_PRG_2		GENMASK(7, 6)
#घोषणा RGMII_CONFIG_INTF_SEL			GENMASK(5, 4)
#घोषणा RGMII_CONFIG_BYPASS_TX_ID_EN		BIT(3)
#घोषणा RGMII_CONFIG_LOOPBACK_EN		BIT(2)
#घोषणा RGMII_CONFIG_PROG_SWAP			BIT(1)
#घोषणा RGMII_CONFIG_DDR_MODE			BIT(0)

/* SDCC_HC_REG_DLL_CONFIG fields */
#घोषणा SDCC_DLL_CONFIG_DLL_RST			BIT(30)
#घोषणा SDCC_DLL_CONFIG_PDN			BIT(29)
#घोषणा SDCC_DLL_CONFIG_MCLK_FREQ		GENMASK(26, 24)
#घोषणा SDCC_DLL_CONFIG_CDR_SELEXT		GENMASK(23, 20)
#घोषणा SDCC_DLL_CONFIG_CDR_EXT_EN		BIT(19)
#घोषणा SDCC_DLL_CONFIG_CK_OUT_EN		BIT(18)
#घोषणा SDCC_DLL_CONFIG_CDR_EN			BIT(17)
#घोषणा SDCC_DLL_CONFIG_DLL_EN			BIT(16)
#घोषणा SDCC_DLL_MCLK_GATING_EN			BIT(5)
#घोषणा SDCC_DLL_CDR_FINE_PHASE			GENMASK(3, 2)

/* SDCC_HC_REG_DDR_CONFIG fields */
#घोषणा SDCC_DDR_CONFIG_PRG_DLY_EN		BIT(31)
#घोषणा SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY	GENMASK(26, 21)
#घोषणा SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_CODE	GENMASK(29, 27)
#घोषणा SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_EN	BIT(30)
#घोषणा SDCC_DDR_CONFIG_PRG_RCLK_DLY		GENMASK(8, 0)

/* SDCC_HC_REG_DLL_CONFIG2 fields */
#घोषणा SDCC_DLL_CONFIG2_DLL_CLOCK_DIS		BIT(21)
#घोषणा SDCC_DLL_CONFIG2_MCLK_FREQ_CALC		GENMASK(17, 10)
#घोषणा SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SEL	GENMASK(3, 2)
#घोषणा SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SW	BIT(1)
#घोषणा SDCC_DLL_CONFIG2_DDR_CAL_EN		BIT(0)

/* SDC4_STATUS bits */
#घोषणा SDC4_STATUS_DLL_LOCK			BIT(7)

/* RGMII_IO_MACRO_CONFIG2 fields */
#घोषणा RGMII_CONFIG2_RSVD_CONFIG15		GENMASK(31, 17)
#घोषणा RGMII_CONFIG2_RGMII_CLK_SEL_CFG		BIT(16)
#घोषणा RGMII_CONFIG2_TX_TO_RX_LOOPBACK_EN	BIT(13)
#घोषणा RGMII_CONFIG2_CLK_DIVIDE_SEL		BIT(12)
#घोषणा RGMII_CONFIG2_RX_PROG_SWAP		BIT(7)
#घोषणा RGMII_CONFIG2_DATA_DIVIDE_CLK_SEL	BIT(6)
#घोषणा RGMII_CONFIG2_TX_CLK_PHASE_SHIFT_EN	BIT(5)

काष्ठा ethqos_emac_por अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक value;
पूर्ण;

काष्ठा ethqos_emac_driver_data अणु
	स्थिर काष्ठा ethqos_emac_por *por;
	अचिन्हित पूर्णांक num_por;
पूर्ण;

काष्ठा qcom_ethqos अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *rgmii_base;

	अचिन्हित पूर्णांक rgmii_clk_rate;
	काष्ठा clk *rgmii_clk;
	अचिन्हित पूर्णांक speed;

	स्थिर काष्ठा ethqos_emac_por *por;
	अचिन्हित पूर्णांक num_por;
पूर्ण;

अटल पूर्णांक rgmii_पढ़ोl(काष्ठा qcom_ethqos *ethqos, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(ethqos->rgmii_base + offset);
पूर्ण

अटल व्योम rgmii_ग_लिखोl(काष्ठा qcom_ethqos *ethqos,
			 पूर्णांक value, अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, ethqos->rgmii_base + offset);
पूर्ण

अटल व्योम rgmii_updatel(काष्ठा qcom_ethqos *ethqos,
			  पूर्णांक mask, पूर्णांक val, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक temp;

	temp =  rgmii_पढ़ोl(ethqos, offset);
	temp = (temp & ~(mask)) | val;
	rgmii_ग_लिखोl(ethqos, temp, offset);
पूर्ण

अटल व्योम rgmii_dump(काष्ठा qcom_ethqos *ethqos)
अणु
	dev_dbg(&ethqos->pdev->dev, "Rgmii register dump\n");
	dev_dbg(&ethqos->pdev->dev, "RGMII_IO_MACRO_CONFIG: %x\n",
		rgmii_पढ़ोl(ethqos, RGMII_IO_MACRO_CONFIG));
	dev_dbg(&ethqos->pdev->dev, "SDCC_HC_REG_DLL_CONFIG: %x\n",
		rgmii_पढ़ोl(ethqos, SDCC_HC_REG_DLL_CONFIG));
	dev_dbg(&ethqos->pdev->dev, "SDCC_HC_REG_DDR_CONFIG: %x\n",
		rgmii_पढ़ोl(ethqos, SDCC_HC_REG_DDR_CONFIG));
	dev_dbg(&ethqos->pdev->dev, "SDCC_HC_REG_DLL_CONFIG2: %x\n",
		rgmii_पढ़ोl(ethqos, SDCC_HC_REG_DLL_CONFIG2));
	dev_dbg(&ethqos->pdev->dev, "SDC4_STATUS: %x\n",
		rgmii_पढ़ोl(ethqos, SDC4_STATUS));
	dev_dbg(&ethqos->pdev->dev, "SDCC_USR_CTL: %x\n",
		rgmii_पढ़ोl(ethqos, SDCC_USR_CTL));
	dev_dbg(&ethqos->pdev->dev, "RGMII_IO_MACRO_CONFIG2: %x\n",
		rgmii_पढ़ोl(ethqos, RGMII_IO_MACRO_CONFIG2));
	dev_dbg(&ethqos->pdev->dev, "RGMII_IO_MACRO_DEBUG1: %x\n",
		rgmii_पढ़ोl(ethqos, RGMII_IO_MACRO_DEBUG1));
	dev_dbg(&ethqos->pdev->dev, "EMAC_SYSTEM_LOW_POWER_DEBUG: %x\n",
		rgmii_पढ़ोl(ethqos, EMAC_SYSTEM_LOW_POWER_DEBUG));
पूर्ण

/* Clock rates */
#घोषणा RGMII_1000_NOM_CLK_FREQ			(250 * 1000 * 1000UL)
#घोषणा RGMII_ID_MODE_100_LOW_SVS_CLK_FREQ	 (50 * 1000 * 1000UL)
#घोषणा RGMII_ID_MODE_10_LOW_SVS_CLK_FREQ	  (5 * 1000 * 1000UL)

अटल व्योम
ethqos_update_rgmii_clk(काष्ठा qcom_ethqos *ethqos, अचिन्हित पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_1000:
		ethqos->rgmii_clk_rate =  RGMII_1000_NOM_CLK_FREQ;
		अवरोध;

	हाल SPEED_100:
		ethqos->rgmii_clk_rate =  RGMII_ID_MODE_100_LOW_SVS_CLK_FREQ;
		अवरोध;

	हाल SPEED_10:
		ethqos->rgmii_clk_rate =  RGMII_ID_MODE_10_LOW_SVS_CLK_FREQ;
		अवरोध;
	पूर्ण

	clk_set_rate(ethqos->rgmii_clk, ethqos->rgmii_clk_rate);
पूर्ण

अटल व्योम ethqos_set_func_clk_en(काष्ठा qcom_ethqos *ethqos)
अणु
	rgmii_updatel(ethqos, RGMII_CONFIG_FUNC_CLK_EN,
		      RGMII_CONFIG_FUNC_CLK_EN, RGMII_IO_MACRO_CONFIG);
पूर्ण

अटल स्थिर काष्ठा ethqos_emac_por emac_v2_3_0_por[] = अणु
	अणु .offset = RGMII_IO_MACRO_CONFIG,	.value = 0x00C01343 पूर्ण,
	अणु .offset = SDCC_HC_REG_DLL_CONFIG,	.value = 0x2004642C पूर्ण,
	अणु .offset = SDCC_HC_REG_DDR_CONFIG,	.value = 0x00000000 पूर्ण,
	अणु .offset = SDCC_HC_REG_DLL_CONFIG2,	.value = 0x00200000 पूर्ण,
	अणु .offset = SDCC_USR_CTL,		.value = 0x00010800 पूर्ण,
	अणु .offset = RGMII_IO_MACRO_CONFIG2,	.value = 0x00002060 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ethqos_emac_driver_data emac_v2_3_0_data = अणु
	.por = emac_v2_3_0_por,
	.num_por = ARRAY_SIZE(emac_v2_3_0_por),
पूर्ण;

अटल पूर्णांक ethqos_dll_configure(काष्ठा qcom_ethqos *ethqos)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक retry = 1000;

	/* Set CDR_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CDR_EN,
		      SDCC_DLL_CONFIG_CDR_EN, SDCC_HC_REG_DLL_CONFIG);

	/* Set CDR_EXT_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CDR_EXT_EN,
		      SDCC_DLL_CONFIG_CDR_EXT_EN, SDCC_HC_REG_DLL_CONFIG);

	/* Clear CK_OUT_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CK_OUT_EN,
		      0, SDCC_HC_REG_DLL_CONFIG);

	/* Set DLL_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_EN,
		      SDCC_DLL_CONFIG_DLL_EN, SDCC_HC_REG_DLL_CONFIG);

	rgmii_updatel(ethqos, SDCC_DLL_MCLK_GATING_EN,
		      0, SDCC_HC_REG_DLL_CONFIG);

	rgmii_updatel(ethqos, SDCC_DLL_CDR_FINE_PHASE,
		      0, SDCC_HC_REG_DLL_CONFIG);

	/* Wait क्रम CK_OUT_EN clear */
	करो अणु
		val = rgmii_पढ़ोl(ethqos, SDCC_HC_REG_DLL_CONFIG);
		val &= SDCC_DLL_CONFIG_CK_OUT_EN;
		अगर (!val)
			अवरोध;
		mdelay(1);
		retry--;
	पूर्ण जबतक (retry > 0);
	अगर (!retry)
		dev_err(&ethqos->pdev->dev, "Clear CK_OUT_EN timedout\n");

	/* Set CK_OUT_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CK_OUT_EN,
		      SDCC_DLL_CONFIG_CK_OUT_EN, SDCC_HC_REG_DLL_CONFIG);

	/* Wait क्रम CK_OUT_EN set */
	retry = 1000;
	करो अणु
		val = rgmii_पढ़ोl(ethqos, SDCC_HC_REG_DLL_CONFIG);
		val &= SDCC_DLL_CONFIG_CK_OUT_EN;
		अगर (val)
			अवरोध;
		mdelay(1);
		retry--;
	पूर्ण जबतक (retry > 0);
	अगर (!retry)
		dev_err(&ethqos->pdev->dev, "Set CK_OUT_EN timedout\n");

	/* Set DDR_CAL_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DDR_CAL_EN,
		      SDCC_DLL_CONFIG2_DDR_CAL_EN, SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DLL_CLOCK_DIS,
		      0, SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_MCLK_FREQ_CALC,
		      0x1A << 10, SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SEL,
		      BIT(2), SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SW,
		      SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SW,
		      SDCC_HC_REG_DLL_CONFIG2);

	वापस 0;
पूर्ण

अटल पूर्णांक ethqos_rgmii_macro_init(काष्ठा qcom_ethqos *ethqos)
अणु
	/* Disable loopback mode */
	rgmii_updatel(ethqos, RGMII_CONFIG2_TX_TO_RX_LOOPBACK_EN,
		      0, RGMII_IO_MACRO_CONFIG2);

	/* Select RGMII, ग_लिखो 0 to पूर्णांकerface select */
	rgmii_updatel(ethqos, RGMII_CONFIG_INTF_SEL,
		      0, RGMII_IO_MACRO_CONFIG);

	चयन (ethqos->speed) अणु
	हाल SPEED_1000:
		rgmii_updatel(ethqos, RGMII_CONFIG_DDR_MODE,
			      RGMII_CONFIG_DDR_MODE, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_BYPASS_TX_ID_EN,
			      0, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_POS_NEG_DATA_SEL,
			      RGMII_CONFIG_POS_NEG_DATA_SEL,
			      RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_PROG_SWAP,
			      RGMII_CONFIG_PROG_SWAP, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG2_DATA_DIVIDE_CLK_SEL,
			      0, RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG2_TX_CLK_PHASE_SHIFT_EN,
			      RGMII_CONFIG2_TX_CLK_PHASE_SHIFT_EN,
			      RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG2_RSVD_CONFIG15,
			      0, RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG2_RX_PROG_SWAP,
			      RGMII_CONFIG2_RX_PROG_SWAP,
			      RGMII_IO_MACRO_CONFIG2);

		/* Set PRG_RCLK_DLY to 57 क्रम 1.8 ns delay */
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_PRG_RCLK_DLY,
			      57, SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_PRG_DLY_EN,
			      SDCC_DDR_CONFIG_PRG_DLY_EN,
			      SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_LOOPBACK_EN,
			      RGMII_CONFIG_LOOPBACK_EN, RGMII_IO_MACRO_CONFIG);
		अवरोध;

	हाल SPEED_100:
		rgmii_updatel(ethqos, RGMII_CONFIG_DDR_MODE,
			      RGMII_CONFIG_DDR_MODE, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_BYPASS_TX_ID_EN,
			      RGMII_CONFIG_BYPASS_TX_ID_EN,
			      RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_POS_NEG_DATA_SEL,
			      0, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_PROG_SWAP,
			      0, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG2_DATA_DIVIDE_CLK_SEL,
			      0, RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG2_TX_CLK_PHASE_SHIFT_EN,
			      RGMII_CONFIG2_TX_CLK_PHASE_SHIFT_EN,
			      RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG_MAX_SPD_PRG_2,
			      BIT(6), RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG2_RSVD_CONFIG15,
			      0, RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG2_RX_PROG_SWAP,
			      0, RGMII_IO_MACRO_CONFIG2);
		/* Write 0x5 to PRG_RCLK_DLY_CODE */
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_CODE,
			      (BIT(29) | BIT(27)), SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY,
			      SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY,
			      SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_EN,
			      SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_EN,
			      SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_LOOPBACK_EN,
			      RGMII_CONFIG_LOOPBACK_EN, RGMII_IO_MACRO_CONFIG);
		अवरोध;

	हाल SPEED_10:
		rgmii_updatel(ethqos, RGMII_CONFIG_DDR_MODE,
			      RGMII_CONFIG_DDR_MODE, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_BYPASS_TX_ID_EN,
			      RGMII_CONFIG_BYPASS_TX_ID_EN,
			      RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_POS_NEG_DATA_SEL,
			      0, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_PROG_SWAP,
			      0, RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG2_DATA_DIVIDE_CLK_SEL,
			      0, RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG2_TX_CLK_PHASE_SHIFT_EN,
			      0, RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG_MAX_SPD_PRG_9,
			      BIT(12) | GENMASK(9, 8),
			      RGMII_IO_MACRO_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG2_RSVD_CONFIG15,
			      0, RGMII_IO_MACRO_CONFIG2);
		rgmii_updatel(ethqos, RGMII_CONFIG2_RX_PROG_SWAP,
			      0, RGMII_IO_MACRO_CONFIG2);
		/* Write 0x5 to PRG_RCLK_DLY_CODE */
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_CODE,
			      (BIT(29) | BIT(27)), SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY,
			      SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY,
			      SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_EN,
			      SDCC_DDR_CONFIG_EXT_PRG_RCLK_DLY_EN,
			      SDCC_HC_REG_DDR_CONFIG);
		rgmii_updatel(ethqos, RGMII_CONFIG_LOOPBACK_EN,
			      RGMII_CONFIG_LOOPBACK_EN, RGMII_IO_MACRO_CONFIG);
		अवरोध;
	शेष:
		dev_err(&ethqos->pdev->dev,
			"Invalid speed %d\n", ethqos->speed);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ethqos_configure(काष्ठा qcom_ethqos *ethqos)
अणु
	अस्थिर अचिन्हित पूर्णांक dll_lock;
	अचिन्हित पूर्णांक i, retry = 1000;

	/* Reset to POR values and enable clk */
	क्रम (i = 0; i < ethqos->num_por; i++)
		rgmii_ग_लिखोl(ethqos, ethqos->por[i].value,
			     ethqos->por[i].offset);
	ethqos_set_func_clk_en(ethqos);

	/* Initialize the DLL first */

	/* Set DLL_RST */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_RST,
		      SDCC_DLL_CONFIG_DLL_RST, SDCC_HC_REG_DLL_CONFIG);

	/* Set PDN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_PDN,
		      SDCC_DLL_CONFIG_PDN, SDCC_HC_REG_DLL_CONFIG);

	/* Clear DLL_RST */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_RST, 0,
		      SDCC_HC_REG_DLL_CONFIG);

	/* Clear PDN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_PDN, 0,
		      SDCC_HC_REG_DLL_CONFIG);

	अगर (ethqos->speed != SPEED_100 && ethqos->speed != SPEED_10) अणु
		/* Set DLL_EN */
		rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_EN,
			      SDCC_DLL_CONFIG_DLL_EN, SDCC_HC_REG_DLL_CONFIG);

		/* Set CK_OUT_EN */
		rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CK_OUT_EN,
			      SDCC_DLL_CONFIG_CK_OUT_EN,
			      SDCC_HC_REG_DLL_CONFIG);

		/* Set USR_CTL bit 26 with mask of 3 bits */
		rgmii_updatel(ethqos, GENMASK(26, 24), BIT(26), SDCC_USR_CTL);

		/* रुको क्रम DLL LOCK */
		करो अणु
			mdelay(1);
			dll_lock = rgmii_पढ़ोl(ethqos, SDC4_STATUS);
			अगर (dll_lock & SDC4_STATUS_DLL_LOCK)
				अवरोध;
			retry--;
		पूर्ण जबतक (retry > 0);
		अगर (!retry)
			dev_err(&ethqos->pdev->dev,
				"Timeout while waiting for DLL lock\n");
	पूर्ण

	अगर (ethqos->speed == SPEED_1000)
		ethqos_dll_configure(ethqos);

	ethqos_rgmii_macro_init(ethqos);

	वापस 0;
पूर्ण

अटल व्योम ethqos_fix_mac_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा qcom_ethqos *ethqos = priv;

	ethqos->speed = speed;
	ethqos_update_rgmii_clk(ethqos, speed);
	ethqos_configure(ethqos);
पूर्ण

अटल पूर्णांक qcom_ethqos_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	स्थिर काष्ठा ethqos_emac_driver_data *data;
	काष्ठा qcom_ethqos *ethqos;
	काष्ठा resource *res;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat)) अणु
		dev_err(&pdev->dev, "dt configuration failed\n");
		वापस PTR_ERR(plat_dat);
	पूर्ण

	ethqos = devm_kzalloc(&pdev->dev, माप(*ethqos), GFP_KERNEL);
	अगर (!ethqos) अणु
		ret = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	ethqos->pdev = pdev;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rgmii");
	ethqos->rgmii_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ethqos->rgmii_base)) अणु
		ret = PTR_ERR(ethqos->rgmii_base);
		जाओ err_mem;
	पूर्ण

	data = of_device_get_match_data(&pdev->dev);
	ethqos->por = data->por;
	ethqos->num_por = data->num_por;

	ethqos->rgmii_clk = devm_clk_get(&pdev->dev, "rgmii");
	अगर (IS_ERR(ethqos->rgmii_clk)) अणु
		ret = PTR_ERR(ethqos->rgmii_clk);
		जाओ err_mem;
	पूर्ण

	ret = clk_prepare_enable(ethqos->rgmii_clk);
	अगर (ret)
		जाओ err_mem;

	ethqos->speed = SPEED_1000;
	ethqos_update_rgmii_clk(ethqos, SPEED_1000);
	ethqos_set_func_clk_en(ethqos);

	plat_dat->bsp_priv = ethqos;
	plat_dat->fix_mac_speed = ethqos_fix_mac_speed;
	plat_dat->has_gmac4 = 1;
	plat_dat->pmt = 1;
	plat_dat->tso_en = of_property_पढ़ो_bool(np, "snps,tso");

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_clk;

	rgmii_dump(ethqos);

	वापस ret;

err_clk:
	clk_disable_unprepare(ethqos->rgmii_clk);

err_mem:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_ethqos_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_ethqos *ethqos;
	पूर्णांक ret;

	ethqos = get_sपंचांगmac_bsp_priv(&pdev->dev);
	अगर (!ethqos)
		वापस -ENODEV;

	ret = sपंचांगmac_pltfr_हटाओ(pdev);
	clk_disable_unprepare(ethqos->rgmii_clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_ethqos_match[] = अणु
	अणु .compatible = "qcom,qcs404-ethqos", .data = &emac_v2_3_0_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_ethqos_match);

अटल काष्ठा platक्रमm_driver qcom_ethqos_driver = अणु
	.probe  = qcom_ethqos_probe,
	.हटाओ = qcom_ethqos_हटाओ,
	.driver = अणु
		.name           = "qcom-ethqos",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = of_match_ptr(qcom_ethqos_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_ethqos_driver);

MODULE_DESCRIPTION("Qualcomm ETHQOS driver");
MODULE_LICENSE("GPL v2");
