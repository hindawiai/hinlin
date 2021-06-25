<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale eSDHC i.MX controller driver क्रम the platक्रमm bus.
 *
 * derived from the OF-version.
 *
 * Copyright (c) 2010 Pengutronix e.K.
 *   Author: Wolfram Sang <kernel@pengutronix.de>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_data/mmc-esdhc-imx.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "sdhci-pltfm.h"
#समावेश "sdhci-esdhc.h"
#समावेश "cqhci.h"

#घोषणा ESDHC_SYS_CTRL_DTOCV_MASK	0x0f
#घोषणा	ESDHC_CTRL_D3CD			0x08
#घोषणा ESDHC_BURST_LEN_EN_INCR		(1 << 27)
/* VENDOR SPEC रेजिस्टर */
#घोषणा ESDHC_VENDOR_SPEC		0xc0
#घोषणा  ESDHC_VENDOR_SPEC_SDIO_QUIRK	(1 << 1)
#घोषणा  ESDHC_VENDOR_SPEC_VSELECT	(1 << 1)
#घोषणा  ESDHC_VENDOR_SPEC_FRC_SDCLK_ON	(1 << 8)
#घोषणा ESDHC_DEBUG_SEL_AND_STATUS_REG		0xc2
#घोषणा ESDHC_DEBUG_SEL_REG			0xc3
#घोषणा ESDHC_DEBUG_SEL_MASK			0xf
#घोषणा ESDHC_DEBUG_SEL_CMD_STATE		1
#घोषणा ESDHC_DEBUG_SEL_DATA_STATE		2
#घोषणा ESDHC_DEBUG_SEL_TRANS_STATE		3
#घोषणा ESDHC_DEBUG_SEL_DMA_STATE		4
#घोषणा ESDHC_DEBUG_SEL_ADMA_STATE		5
#घोषणा ESDHC_DEBUG_SEL_FIFO_STATE		6
#घोषणा ESDHC_DEBUG_SEL_ASYNC_FIFO_STATE	7
#घोषणा ESDHC_WTMK_LVL			0x44
#घोषणा  ESDHC_WTMK_DEFAULT_VAL		0x10401040
#घोषणा  ESDHC_WTMK_LVL_RD_WML_MASK	0x000000FF
#घोषणा  ESDHC_WTMK_LVL_RD_WML_SHIFT	0
#घोषणा  ESDHC_WTMK_LVL_WR_WML_MASK	0x00FF0000
#घोषणा  ESDHC_WTMK_LVL_WR_WML_SHIFT	16
#घोषणा  ESDHC_WTMK_LVL_WML_VAL_DEF	64
#घोषणा  ESDHC_WTMK_LVL_WML_VAL_MAX	128
#घोषणा ESDHC_MIX_CTRL			0x48
#घोषणा  ESDHC_MIX_CTRL_DDREN		(1 << 3)
#घोषणा  ESDHC_MIX_CTRL_AC23EN		(1 << 7)
#घोषणा  ESDHC_MIX_CTRL_EXE_TUNE	(1 << 22)
#घोषणा  ESDHC_MIX_CTRL_SMPCLK_SEL	(1 << 23)
#घोषणा  ESDHC_MIX_CTRL_AUTO_TUNE_EN	(1 << 24)
#घोषणा  ESDHC_MIX_CTRL_FBCLK_SEL	(1 << 25)
#घोषणा  ESDHC_MIX_CTRL_HS400_EN	(1 << 26)
#घोषणा  ESDHC_MIX_CTRL_HS400_ES_EN	(1 << 27)
/* Bits 3 and 6 are not SDHCI standard definitions */
#घोषणा  ESDHC_MIX_CTRL_SDHCI_MASK	0xb7
/* Tuning bits */
#घोषणा  ESDHC_MIX_CTRL_TUNING_MASK	0x03c00000

/* dll control रेजिस्टर */
#घोषणा ESDHC_DLL_CTRL			0x60
#घोषणा ESDHC_DLL_OVERRIDE_VAL_SHIFT	9
#घोषणा ESDHC_DLL_OVERRIDE_EN_SHIFT	8

/* tune control रेजिस्टर */
#घोषणा ESDHC_TUNE_CTRL_STATUS		0x68
#घोषणा  ESDHC_TUNE_CTRL_STEP		1
#घोषणा  ESDHC_TUNE_CTRL_MIN		0
#घोषणा  ESDHC_TUNE_CTRL_MAX		((1 << 7) - 1)

/* strobe dll रेजिस्टर */
#घोषणा ESDHC_STROBE_DLL_CTRL		0x70
#घोषणा ESDHC_STROBE_DLL_CTRL_ENABLE	(1 << 0)
#घोषणा ESDHC_STROBE_DLL_CTRL_RESET	(1 << 1)
#घोषणा ESDHC_STROBE_DLL_CTRL_SLV_DLY_TARGET_DEFAULT	0x7
#घोषणा ESDHC_STROBE_DLL_CTRL_SLV_DLY_TARGET_SHIFT	3
#घोषणा ESDHC_STROBE_DLL_CTRL_SLV_UPDATE_INT_DEFAULT	(4 << 20)

#घोषणा ESDHC_STROBE_DLL_STATUS		0x74
#घोषणा ESDHC_STROBE_DLL_STS_REF_LOCK	(1 << 1)
#घोषणा ESDHC_STROBE_DLL_STS_SLV_LOCK	0x1

#घोषणा ESDHC_VEND_SPEC2		0xc8
#घोषणा ESDHC_VEND_SPEC2_EN_BUSY_IRQ	(1 << 8)

#घोषणा ESDHC_TUNING_CTRL		0xcc
#घोषणा ESDHC_STD_TUNING_EN		(1 << 24)
/* NOTE: the minimum valid tuning start tap क्रम mx6sl is 1 */
#घोषणा ESDHC_TUNING_START_TAP_DEFAULT	0x1
#घोषणा ESDHC_TUNING_START_TAP_MASK	0x7f
#घोषणा ESDHC_TUNING_CMD_CRC_CHECK_DISABLE	(1 << 7)
#घोषणा ESDHC_TUNING_STEP_MASK		0x00070000
#घोषणा ESDHC_TUNING_STEP_SHIFT		16

/* pinctrl state */
#घोषणा ESDHC_PINCTRL_STATE_100MHZ	"state_100mhz"
#घोषणा ESDHC_PINCTRL_STATE_200MHZ	"state_200mhz"

/*
 * Our पूर्णांकerpretation of the SDHCI_HOST_CONTROL रेजिस्टर
 */
#घोषणा ESDHC_CTRL_4BITBUS		(0x1 << 1)
#घोषणा ESDHC_CTRL_8BITBUS		(0x2 << 1)
#घोषणा ESDHC_CTRL_BUSWIDTH_MASK	(0x3 << 1)

/*
 * There is an INT DMA ERR mismatch between eSDHC and STD SDHC SPEC:
 * Bit25 is used in STD SPEC, and is reserved in fsl eSDHC design,
 * but bit28 is used as the INT DMA ERR in fsl eSDHC design.
 * Define this macro DMA error INT क्रम fsl eSDHC
 */
#घोषणा ESDHC_INT_VENDOR_SPEC_DMA_ERR	(1 << 28)

/* the address offset of CQHCI */
#घोषणा ESDHC_CQHCI_ADDR_OFFSET		0x100

/*
 * The CMDTYPE of the CMD रेजिस्टर (offset 0xE) should be set to
 * "11" when the STOP CMD12 is issued on imx53 to पात one
 * खोलो ended multi-blk IO. Otherwise the TC INT wouldn't
 * be generated.
 * In exact block transfer, the controller करोesn't complete the
 * operations स्वतःmatically as required at the end of the
 * transfer and reमुख्यs on hold अगर the पात command is not sent.
 * As a result, the TC flag is not निश्चितed and SW received समयout
 * exception. Bit1 of Venकरोr Spec रेजिस्टर is used to fix it.
 */
#घोषणा ESDHC_FLAG_MULTIBLK_NO_INT	BIT(1)
/*
 * The flag tells that the ESDHC controller is an USDHC block that is
 * पूर्णांकegrated on the i.MX6 series.
 */
#घोषणा ESDHC_FLAG_USDHC		BIT(3)
/* The IP supports manual tuning process */
#घोषणा ESDHC_FLAG_MAN_TUNING		BIT(4)
/* The IP supports standard tuning process */
#घोषणा ESDHC_FLAG_STD_TUNING		BIT(5)
/* The IP has SDHCI_CAPABILITIES_1 रेजिस्टर */
#घोषणा ESDHC_FLAG_HAVE_CAP1		BIT(6)
/*
 * The IP has erratum ERR004536
 * uSDHC: ADMA Length Mismatch Error occurs अगर the AHB पढ़ो access is slow,
 * when पढ़ोing data from the card
 * This flag is also set क्रम i.MX25 and i.MX35 in order to get
 * SDHCI_QUIRK_BROKEN_ADMA, but क्रम dअगरferent reasons (ADMA capability bits).
 */
#घोषणा ESDHC_FLAG_ERR004536		BIT(7)
/* The IP supports HS200 mode */
#घोषणा ESDHC_FLAG_HS200		BIT(8)
/* The IP supports HS400 mode */
#घोषणा ESDHC_FLAG_HS400		BIT(9)
/*
 * The IP has errata ERR010450
 * uSDHC: Due to the I/O timing limit, क्रम SDR mode, SD card घड़ी can't
 * exceed 150MHz, क्रम DDR mode, SD card घड़ी can't exceed 45MHz.
 */
#घोषणा ESDHC_FLAG_ERR010450		BIT(10)
/* The IP supports HS400ES mode */
#घोषणा ESDHC_FLAG_HS400_ES		BIT(11)
/* The IP has Host Controller Interface क्रम Command Queuing */
#घोषणा ESDHC_FLAG_CQHCI		BIT(12)
/* need request pmqos during low घातer */
#घोषणा ESDHC_FLAG_PMQOS		BIT(13)
/* The IP state got lost in low घातer mode */
#घोषणा ESDHC_FLAG_STATE_LOST_IN_LPMODE		BIT(14)
/* The IP lost घड़ी rate in PM_RUNTIME */
#घोषणा ESDHC_FLAG_CLK_RATE_LOST_IN_PM_RUNTIME	BIT(15)
/*
 * The IP करो not support the ACMD23 feature completely when use ADMA mode.
 * In ADMA mode, it only use the 16 bit block count of the रेजिस्टर 0x4
 * (BLOCK_ATT) as the CMD23's argument क्रम ACMD23 mode, which means it will
 * ignore the upper 16 bit of the CMD23's argument. This will block the reliable
 * ग_लिखो operation in RPMB, because RPMB reliable ग_लिखो need to set the bit31
 * of the CMD23's argument.
 * imx6qpdl/imx6sx/imx6sl/imx7d has this limitation only क्रम ADMA mode, SDMA
 * करो not has this limitation. so when these SoC use ADMA mode, it need to
 * disable the ACMD23 feature.
 */
#घोषणा ESDHC_FLAG_BROKEN_AUTO_CMD23	BIT(16)

काष्ठा esdhc_soc_data अणु
	u32 flags;
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data esdhc_imx25_data = अणु
	.flags = ESDHC_FLAG_ERR004536,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data esdhc_imx35_data = अणु
	.flags = ESDHC_FLAG_ERR004536,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data esdhc_imx51_data = अणु
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data esdhc_imx53_data = अणु
	.flags = ESDHC_FLAG_MULTIBLK_NO_INT,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data usdhc_imx6q_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_MAN_TUNING
			| ESDHC_FLAG_BROKEN_AUTO_CMD23,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data usdhc_imx6sl_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_ERR004536
			| ESDHC_FLAG_HS200
			| ESDHC_FLAG_BROKEN_AUTO_CMD23,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data usdhc_imx6sll_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_HS200
			| ESDHC_FLAG_HS400
			| ESDHC_FLAG_STATE_LOST_IN_LPMODE,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data usdhc_imx6sx_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_HS200
			| ESDHC_FLAG_STATE_LOST_IN_LPMODE
			| ESDHC_FLAG_BROKEN_AUTO_CMD23,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data usdhc_imx6ull_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_HS200
			| ESDHC_FLAG_ERR010450
			| ESDHC_FLAG_STATE_LOST_IN_LPMODE,
पूर्ण;

अटल स्थिर काष्ठा esdhc_soc_data usdhc_imx7d_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_HS200
			| ESDHC_FLAG_HS400
			| ESDHC_FLAG_STATE_LOST_IN_LPMODE
			| ESDHC_FLAG_BROKEN_AUTO_CMD23,
पूर्ण;

अटल काष्ठा esdhc_soc_data usdhc_imx7ulp_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_HS200
			| ESDHC_FLAG_PMQOS | ESDHC_FLAG_HS400
			| ESDHC_FLAG_STATE_LOST_IN_LPMODE,
पूर्ण;

अटल काष्ठा esdhc_soc_data usdhc_imx8qxp_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_HS200
			| ESDHC_FLAG_HS400 | ESDHC_FLAG_HS400_ES
			| ESDHC_FLAG_CQHCI
			| ESDHC_FLAG_STATE_LOST_IN_LPMODE
			| ESDHC_FLAG_CLK_RATE_LOST_IN_PM_RUNTIME,
पूर्ण;

अटल काष्ठा esdhc_soc_data usdhc_imx8mm_data = अणु
	.flags = ESDHC_FLAG_USDHC | ESDHC_FLAG_STD_TUNING
			| ESDHC_FLAG_HAVE_CAP1 | ESDHC_FLAG_HS200
			| ESDHC_FLAG_HS400 | ESDHC_FLAG_HS400_ES
			| ESDHC_FLAG_CQHCI
			| ESDHC_FLAG_STATE_LOST_IN_LPMODE,
पूर्ण;

काष्ठा pltfm_imx_data अणु
	u32 scratchpad;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_100mhz;
	काष्ठा pinctrl_state *pins_200mhz;
	स्थिर काष्ठा esdhc_soc_data *socdata;
	काष्ठा esdhc_platक्रमm_data boarddata;
	काष्ठा clk *clk_ipg;
	काष्ठा clk *clk_ahb;
	काष्ठा clk *clk_per;
	अचिन्हित पूर्णांक actual_घड़ी;
	क्रमागत अणु
		NO_CMD_PENDING,      /* no multiblock command pending */
		MULTIBLK_IN_PROCESS, /* exact multiblock cmd in process */
		WAIT_FOR_INT,        /* sent CMD12, रुकोing क्रम response INT */
	पूर्ण multiblock_status;
	u32 is_ddr;
	काष्ठा pm_qos_request pm_qos_req;
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_esdhc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx25-esdhc", .data = &esdhc_imx25_data, पूर्ण,
	अणु .compatible = "fsl,imx35-esdhc", .data = &esdhc_imx35_data, पूर्ण,
	अणु .compatible = "fsl,imx51-esdhc", .data = &esdhc_imx51_data, पूर्ण,
	अणु .compatible = "fsl,imx53-esdhc", .data = &esdhc_imx53_data, पूर्ण,
	अणु .compatible = "fsl,imx6sx-usdhc", .data = &usdhc_imx6sx_data, पूर्ण,
	अणु .compatible = "fsl,imx6sl-usdhc", .data = &usdhc_imx6sl_data, पूर्ण,
	अणु .compatible = "fsl,imx6sll-usdhc", .data = &usdhc_imx6sll_data, पूर्ण,
	अणु .compatible = "fsl,imx6q-usdhc", .data = &usdhc_imx6q_data, पूर्ण,
	अणु .compatible = "fsl,imx6ull-usdhc", .data = &usdhc_imx6ull_data, पूर्ण,
	अणु .compatible = "fsl,imx7d-usdhc", .data = &usdhc_imx7d_data, पूर्ण,
	अणु .compatible = "fsl,imx7ulp-usdhc", .data = &usdhc_imx7ulp_data, पूर्ण,
	अणु .compatible = "fsl,imx8qxp-usdhc", .data = &usdhc_imx8qxp_data, पूर्ण,
	अणु .compatible = "fsl,imx8mm-usdhc", .data = &usdhc_imx8mm_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_esdhc_dt_ids);

अटल अंतरभूत पूर्णांक is_imx25_esdhc(काष्ठा pltfm_imx_data *data)
अणु
	वापस data->socdata == &esdhc_imx25_data;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx53_esdhc(काष्ठा pltfm_imx_data *data)
अणु
	वापस data->socdata == &esdhc_imx53_data;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx6q_usdhc(काष्ठा pltfm_imx_data *data)
अणु
	वापस data->socdata == &usdhc_imx6q_data;
पूर्ण

अटल अंतरभूत पूर्णांक esdhc_is_usdhc(काष्ठा pltfm_imx_data *data)
अणु
	वापस !!(data->socdata->flags & ESDHC_FLAG_USDHC);
पूर्ण

अटल अंतरभूत व्योम esdhc_clrset_le(काष्ठा sdhci_host *host, u32 mask, u32 val, पूर्णांक reg)
अणु
	व्योम __iomem *base = host->ioaddr + (reg & ~0x3);
	u32 shअगरt = (reg & 0x3) * 8;

	ग_लिखोl(((पढ़ोl(base) & ~(mask << shअगरt)) | (val << shअगरt)), base);
पूर्ण

#घोषणा DRIVER_NAME "sdhci-esdhc-imx"
#घोषणा ESDHC_IMX_DUMP(f, x...) \
	pr_err("%s: " DRIVER_NAME ": " f, mmc_hostname(host->mmc), ## x)
अटल व्योम esdhc_dump_debug_regs(काष्ठा sdhci_host *host)
अणु
	पूर्णांक i;
	अक्षर *debug_status[7] = अणु
				 "cmd debug status",
				 "data debug status",
				 "trans debug status",
				 "dma debug status",
				 "adma debug status",
				 "fifo debug status",
				 "async fifo debug status"
	पूर्ण;

	ESDHC_IMX_DUMP("========= ESDHC IMX DEBUG STATUS DUMP =========\n");
	क्रम (i = 0; i < 7; i++) अणु
		esdhc_clrset_le(host, ESDHC_DEBUG_SEL_MASK,
			ESDHC_DEBUG_SEL_CMD_STATE + i, ESDHC_DEBUG_SEL_REG);
		ESDHC_IMX_DUMP("%s:  0x%04x\n", debug_status[i],
			पढ़ोw(host->ioaddr + ESDHC_DEBUG_SEL_AND_STATUS_REG));
	पूर्ण

	esdhc_clrset_le(host, ESDHC_DEBUG_SEL_MASK, 0, ESDHC_DEBUG_SEL_REG);

पूर्ण

अटल अंतरभूत व्योम esdhc_रुको_क्रम_card_घड़ी_gate_off(काष्ठा sdhci_host *host)
अणु
	u32 present_state;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(host->ioaddr + ESDHC_PRSSTAT, present_state,
				(present_state & ESDHC_CLOCK_GATE_OFF), 2, 100);
	अगर (ret == -ETIMEDOUT)
		dev_warn(mmc_dev(host->mmc), "%s: card clock still not gate off in 100us!.\n", __func__);
पूर्ण

अटल u32 esdhc_पढ़ोl_le(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 val = पढ़ोl(host->ioaddr + reg);

	अगर (unlikely(reg == SDHCI_PRESENT_STATE)) अणु
		u32 fsl_prss = val;
		/* save the least 20 bits */
		val = fsl_prss & 0x000FFFFF;
		/* move dat[0-3] bits */
		val |= (fsl_prss & 0x0F000000) >> 4;
		/* move cmd line bit */
		val |= (fsl_prss & 0x00800000) << 1;
	पूर्ण

	अगर (unlikely(reg == SDHCI_CAPABILITIES)) अणु
		/* ignore bit[0-15] as it stores cap_1 रेजिस्टर val क्रम mx6sl */
		अगर (imx_data->socdata->flags & ESDHC_FLAG_HAVE_CAP1)
			val &= 0xffff0000;

		/* In FSL esdhc IC module, only bit20 is used to indicate the
		 * ADMA2 capability of esdhc, but this bit is messed up on
		 * some SOCs (e.g. on MX25, MX35 this bit is set, but they
		 * करोn't actually support ADMA2). So set the BROKEN_ADMA
		 * quirk on MX25/35 platक्रमms.
		 */

		अगर (val & SDHCI_CAN_DO_ADMA1) अणु
			val &= ~SDHCI_CAN_DO_ADMA1;
			val |= SDHCI_CAN_DO_ADMA2;
		पूर्ण
	पूर्ण

	अगर (unlikely(reg == SDHCI_CAPABILITIES_1)) अणु
		अगर (esdhc_is_usdhc(imx_data)) अणु
			अगर (imx_data->socdata->flags & ESDHC_FLAG_HAVE_CAP1)
				val = पढ़ोl(host->ioaddr + SDHCI_CAPABILITIES) & 0xFFFF;
			अन्यथा
				/* imx6q/dl करोes not have cap_1 रेजिस्टर, fake one */
				val = SDHCI_SUPPORT_DDR50 | SDHCI_SUPPORT_SDR104
					| SDHCI_SUPPORT_SDR50
					| SDHCI_USE_SDR50_TUNING
					| FIELD_PREP(SDHCI_RETUNING_MODE_MASK,
						     SDHCI_TUNING_MODE_3);

			अगर (imx_data->socdata->flags & ESDHC_FLAG_HS400)
				val |= SDHCI_SUPPORT_HS400;

			/*
			 * Do not advertise faster UHS modes अगर there are no
			 * pinctrl states क्रम 100MHz/200MHz.
			 */
			अगर (IS_ERR_OR_शून्य(imx_data->pins_100mhz))
				val &= ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_DDR50);
			अगर (IS_ERR_OR_शून्य(imx_data->pins_200mhz))
				val &= ~(SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_HS400);
		पूर्ण
	पूर्ण

	अगर (unlikely(reg == SDHCI_MAX_CURRENT) && esdhc_is_usdhc(imx_data)) अणु
		val = 0;
		val |= FIELD_PREP(SDHCI_MAX_CURRENT_330_MASK, 0xFF);
		val |= FIELD_PREP(SDHCI_MAX_CURRENT_300_MASK, 0xFF);
		val |= FIELD_PREP(SDHCI_MAX_CURRENT_180_MASK, 0xFF);
	पूर्ण

	अगर (unlikely(reg == SDHCI_INT_STATUS)) अणु
		अगर (val & ESDHC_INT_VENDOR_SPEC_DMA_ERR) अणु
			val &= ~ESDHC_INT_VENDOR_SPEC_DMA_ERR;
			val |= SDHCI_INT_ADMA_ERROR;
		पूर्ण

		/*
		 * mask off the पूर्णांकerrupt we get in response to the manually
		 * sent CMD12
		 */
		अगर ((imx_data->multiblock_status == WAIT_FOR_INT) &&
		    ((val & SDHCI_INT_RESPONSE) == SDHCI_INT_RESPONSE)) अणु
			val &= ~SDHCI_INT_RESPONSE;
			ग_लिखोl(SDHCI_INT_RESPONSE, host->ioaddr +
						   SDHCI_INT_STATUS);
			imx_data->multiblock_status = NO_CMD_PENDING;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम esdhc_ग_लिखोl_le(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 data;

	अगर (unlikely(reg == SDHCI_INT_ENABLE || reg == SDHCI_SIGNAL_ENABLE ||
			reg == SDHCI_INT_STATUS)) अणु
		अगर ((val & SDHCI_INT_CARD_INT) && !esdhc_is_usdhc(imx_data)) अणु
			/*
			 * Clear and then set D3CD bit to aव्योम missing the
			 * card पूर्णांकerrupt. This is an eSDHC controller problem
			 * so we need to apply the following workaround: clear
			 * and set D3CD bit will make eSDHC re-sample the card
			 * पूर्णांकerrupt. In हाल a card पूर्णांकerrupt was lost,
			 * re-sample it by the following steps.
			 */
			data = पढ़ोl(host->ioaddr + SDHCI_HOST_CONTROL);
			data &= ~ESDHC_CTRL_D3CD;
			ग_लिखोl(data, host->ioaddr + SDHCI_HOST_CONTROL);
			data |= ESDHC_CTRL_D3CD;
			ग_लिखोl(data, host->ioaddr + SDHCI_HOST_CONTROL);
		पूर्ण

		अगर (val & SDHCI_INT_ADMA_ERROR) अणु
			val &= ~SDHCI_INT_ADMA_ERROR;
			val |= ESDHC_INT_VENDOR_SPEC_DMA_ERR;
		पूर्ण
	पूर्ण

	अगर (unlikely((imx_data->socdata->flags & ESDHC_FLAG_MULTIBLK_NO_INT)
				&& (reg == SDHCI_INT_STATUS)
				&& (val & SDHCI_INT_DATA_END))) अणु
			u32 v;
			v = पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC);
			v &= ~ESDHC_VENDOR_SPEC_SDIO_QUIRK;
			ग_लिखोl(v, host->ioaddr + ESDHC_VENDOR_SPEC);

			अगर (imx_data->multiblock_status == MULTIBLK_IN_PROCESS)
			अणु
				/* send a manual CMD12 with RESPTYP=none */
				data = MMC_STOP_TRANSMISSION << 24 |
				       SDHCI_CMD_ABORTCMD << 16;
				ग_लिखोl(data, host->ioaddr + SDHCI_TRANSFER_MODE);
				imx_data->multiblock_status = WAIT_FOR_INT;
			पूर्ण
	पूर्ण

	ग_लिखोl(val, host->ioaddr + reg);
पूर्ण

अटल u16 esdhc_पढ़ोw_le(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u16 ret = 0;
	u32 val;

	अगर (unlikely(reg == SDHCI_HOST_VERSION)) अणु
		reg ^= 2;
		अगर (esdhc_is_usdhc(imx_data)) अणु
			/*
			 * The usdhc रेजिस्टर वापसs a wrong host version.
			 * Correct it here.
			 */
			वापस SDHCI_SPEC_300;
		पूर्ण
	पूर्ण

	अगर (unlikely(reg == SDHCI_HOST_CONTROL2)) अणु
		val = पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC);
		अगर (val & ESDHC_VENDOR_SPEC_VSELECT)
			ret |= SDHCI_CTRL_VDD_180;

		अगर (esdhc_is_usdhc(imx_data)) अणु
			अगर (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING)
				val = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
			अन्यथा अगर (imx_data->socdata->flags & ESDHC_FLAG_STD_TUNING)
				/* the std tuning bits is in ACMD12_ERR क्रम imx6sl */
				val = पढ़ोl(host->ioaddr + SDHCI_AUTO_CMD_STATUS);
		पूर्ण

		अगर (val & ESDHC_MIX_CTRL_EXE_TUNE)
			ret |= SDHCI_CTRL_EXEC_TUNING;
		अगर (val & ESDHC_MIX_CTRL_SMPCLK_SEL)
			ret |= SDHCI_CTRL_TUNED_CLK;

		ret &= ~SDHCI_CTRL_PRESET_VAL_ENABLE;

		वापस ret;
	पूर्ण

	अगर (unlikely(reg == SDHCI_TRANSFER_MODE)) अणु
		अगर (esdhc_is_usdhc(imx_data)) अणु
			u32 m = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
			ret = m & ESDHC_MIX_CTRL_SDHCI_MASK;
			/* Swap AC23 bit */
			अगर (m & ESDHC_MIX_CTRL_AC23EN) अणु
				ret &= ~ESDHC_MIX_CTRL_AC23EN;
				ret |= SDHCI_TRNS_AUTO_CMD23;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = पढ़ोw(host->ioaddr + SDHCI_TRANSFER_MODE);
		पूर्ण

		वापस ret;
	पूर्ण

	वापस पढ़ोw(host->ioaddr + reg);
पूर्ण

अटल व्योम esdhc_ग_लिखोw_le(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 new_val = 0;

	चयन (reg) अणु
	हाल SDHCI_CLOCK_CONTROL:
		new_val = पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC);
		अगर (val & SDHCI_CLOCK_CARD_EN)
			new_val |= ESDHC_VENDOR_SPEC_FRC_SDCLK_ON;
		अन्यथा
			new_val &= ~ESDHC_VENDOR_SPEC_FRC_SDCLK_ON;
		ग_लिखोl(new_val, host->ioaddr + ESDHC_VENDOR_SPEC);
		अगर (!(new_val & ESDHC_VENDOR_SPEC_FRC_SDCLK_ON))
			esdhc_रुको_क्रम_card_घड़ी_gate_off(host);
		वापस;
	हाल SDHCI_HOST_CONTROL2:
		new_val = पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC);
		अगर (val & SDHCI_CTRL_VDD_180)
			new_val |= ESDHC_VENDOR_SPEC_VSELECT;
		अन्यथा
			new_val &= ~ESDHC_VENDOR_SPEC_VSELECT;
		ग_लिखोl(new_val, host->ioaddr + ESDHC_VENDOR_SPEC);
		अगर (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING) अणु
			new_val = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
			अगर (val & SDHCI_CTRL_TUNED_CLK) अणु
				new_val |= ESDHC_MIX_CTRL_SMPCLK_SEL;
				new_val |= ESDHC_MIX_CTRL_AUTO_TUNE_EN;
			पूर्ण अन्यथा अणु
				new_val &= ~ESDHC_MIX_CTRL_SMPCLK_SEL;
				new_val &= ~ESDHC_MIX_CTRL_AUTO_TUNE_EN;
			पूर्ण
			ग_लिखोl(new_val , host->ioaddr + ESDHC_MIX_CTRL);
		पूर्ण अन्यथा अगर (imx_data->socdata->flags & ESDHC_FLAG_STD_TUNING) अणु
			u32 v = पढ़ोl(host->ioaddr + SDHCI_AUTO_CMD_STATUS);
			u32 m = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
			अगर (val & SDHCI_CTRL_TUNED_CLK) अणु
				v |= ESDHC_MIX_CTRL_SMPCLK_SEL;
			पूर्ण अन्यथा अणु
				v &= ~ESDHC_MIX_CTRL_SMPCLK_SEL;
				m &= ~ESDHC_MIX_CTRL_FBCLK_SEL;
				m &= ~ESDHC_MIX_CTRL_AUTO_TUNE_EN;
			पूर्ण

			अगर (val & SDHCI_CTRL_EXEC_TUNING) अणु
				v |= ESDHC_MIX_CTRL_EXE_TUNE;
				m |= ESDHC_MIX_CTRL_FBCLK_SEL;
				m |= ESDHC_MIX_CTRL_AUTO_TUNE_EN;
			पूर्ण अन्यथा अणु
				v &= ~ESDHC_MIX_CTRL_EXE_TUNE;
			पूर्ण

			ग_लिखोl(v, host->ioaddr + SDHCI_AUTO_CMD_STATUS);
			ग_लिखोl(m, host->ioaddr + ESDHC_MIX_CTRL);
		पूर्ण
		वापस;
	हाल SDHCI_TRANSFER_MODE:
		अगर ((imx_data->socdata->flags & ESDHC_FLAG_MULTIBLK_NO_INT)
				&& (host->cmd->opcode == SD_IO_RW_EXTENDED)
				&& (host->cmd->data->blocks > 1)
				&& (host->cmd->data->flags & MMC_DATA_READ)) अणु
			u32 v;
			v = पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC);
			v |= ESDHC_VENDOR_SPEC_SDIO_QUIRK;
			ग_लिखोl(v, host->ioaddr + ESDHC_VENDOR_SPEC);
		पूर्ण

		अगर (esdhc_is_usdhc(imx_data)) अणु
			u32 wml;
			u32 m = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
			/* Swap AC23 bit */
			अगर (val & SDHCI_TRNS_AUTO_CMD23) अणु
				val &= ~SDHCI_TRNS_AUTO_CMD23;
				val |= ESDHC_MIX_CTRL_AC23EN;
			पूर्ण
			m = val | (m & ~ESDHC_MIX_CTRL_SDHCI_MASK);
			ग_लिखोl(m, host->ioaddr + ESDHC_MIX_CTRL);

			/* Set watermark levels क्रम PIO access to maximum value
			 * (128 words) to accommodate full 512 bytes buffer.
			 * For DMA access restore the levels to शेष value.
			 */
			m = पढ़ोl(host->ioaddr + ESDHC_WTMK_LVL);
			अगर (val & SDHCI_TRNS_DMA) अणु
				wml = ESDHC_WTMK_LVL_WML_VAL_DEF;
			पूर्ण अन्यथा अणु
				u8 ctrl;
				wml = ESDHC_WTMK_LVL_WML_VAL_MAX;

				/*
				 * Since alपढ़ोy disable DMA mode, so also need
				 * to clear the DMASEL. Otherwise, क्रम standard
				 * tuning, when send tuning command, usdhc will
				 * still prefetch the ADMA script from wrong
				 * DMA address, then we will see IOMMU report
				 * some error which show lack of TLB mapping.
				 */
				ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
				ctrl &= ~SDHCI_CTRL_DMA_MASK;
				sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
			पूर्ण
			m &= ~(ESDHC_WTMK_LVL_RD_WML_MASK |
			       ESDHC_WTMK_LVL_WR_WML_MASK);
			m |= (wml << ESDHC_WTMK_LVL_RD_WML_SHIFT) |
			     (wml << ESDHC_WTMK_LVL_WR_WML_SHIFT);
			ग_लिखोl(m, host->ioaddr + ESDHC_WTMK_LVL);
		पूर्ण अन्यथा अणु
			/*
			 * Postpone this ग_लिखो, we must करो it together with a
			 * command ग_लिखो that is करोwn below.
			 */
			imx_data->scratchpad = val;
		पूर्ण
		वापस;
	हाल SDHCI_COMMAND:
		अगर (host->cmd->opcode == MMC_STOP_TRANSMISSION)
			val |= SDHCI_CMD_ABORTCMD;

		अगर ((host->cmd->opcode == MMC_SET_BLOCK_COUNT) &&
		    (imx_data->socdata->flags & ESDHC_FLAG_MULTIBLK_NO_INT))
			imx_data->multiblock_status = MULTIBLK_IN_PROCESS;

		अगर (esdhc_is_usdhc(imx_data))
			ग_लिखोl(val << 16,
			       host->ioaddr + SDHCI_TRANSFER_MODE);
		अन्यथा
			ग_लिखोl(val << 16 | imx_data->scratchpad,
			       host->ioaddr + SDHCI_TRANSFER_MODE);
		वापस;
	हाल SDHCI_BLOCK_SIZE:
		val &= ~SDHCI_MAKE_BLKSZ(0x7, 0);
		अवरोध;
	पूर्ण
	esdhc_clrset_le(host, 0xffff, val, reg);
पूर्ण

अटल u8 esdhc_पढ़ोb_le(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u8 ret;
	u32 val;

	चयन (reg) अणु
	हाल SDHCI_HOST_CONTROL:
		val = पढ़ोl(host->ioaddr + reg);

		ret = val & SDHCI_CTRL_LED;
		ret |= (val >> 5) & SDHCI_CTRL_DMA_MASK;
		ret |= (val & ESDHC_CTRL_4BITBUS);
		ret |= (val & ESDHC_CTRL_8BITBUS) << 3;
		वापस ret;
	पूर्ण

	वापस पढ़ोb(host->ioaddr + reg);
पूर्ण

अटल व्योम esdhc_ग_लिखोb_le(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 new_val = 0;
	u32 mask;

	चयन (reg) अणु
	हाल SDHCI_POWER_CONTROL:
		/*
		 * FSL put some DMA bits here
		 * If your board has a regulator, code should be here
		 */
		वापस;
	हाल SDHCI_HOST_CONTROL:
		/* FSL messed up here, so we need to manually compose it. */
		new_val = val & SDHCI_CTRL_LED;
		/* ensure the endianness */
		new_val |= ESDHC_HOST_CONTROL_LE;
		/* bits 8&9 are reserved on mx25 */
		अगर (!is_imx25_esdhc(imx_data)) अणु
			/* DMA mode bits are shअगरted */
			new_val |= (val & SDHCI_CTRL_DMA_MASK) << 5;
		पूर्ण

		/*
		 * Do not touch buswidth bits here. This is करोne in
		 * esdhc_pltfm_bus_width.
		 * Do not touch the D3CD bit either which is used क्रम the
		 * SDIO पूर्णांकerrupt erratum workaround.
		 */
		mask = 0xffff & ~(ESDHC_CTRL_BUSWIDTH_MASK | ESDHC_CTRL_D3CD);

		esdhc_clrset_le(host, mask, new_val, reg);
		वापस;
	हाल SDHCI_SOFTWARE_RESET:
		अगर (val & SDHCI_RESET_DATA)
			new_val = पढ़ोl(host->ioaddr + SDHCI_HOST_CONTROL);
		अवरोध;
	पूर्ण
	esdhc_clrset_le(host, 0xff, val, reg);

	अगर (reg == SDHCI_SOFTWARE_RESET) अणु
		अगर (val & SDHCI_RESET_ALL) अणु
			/*
			 * The esdhc has a design violation to SDHC spec which
			 * tells that software reset should not affect card
			 * detection circuit. But esdhc clears its SYSCTL
			 * रेजिस्टर bits [0..2] during the software reset. This
			 * will stop those घड़ीs that card detection circuit
			 * relies on. To work around it, we turn the घड़ीs on
			 * back to keep card detection circuit functional.
			 */
			esdhc_clrset_le(host, 0x7, 0x7, ESDHC_SYSTEM_CONTROL);
			/*
			 * The reset on usdhc fails to clear MIX_CTRL रेजिस्टर.
			 * Do it manually here.
			 */
			अगर (esdhc_is_usdhc(imx_data)) अणु
				/*
				 * the tuning bits should be kept during reset
				 */
				new_val = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
				ग_लिखोl(new_val & ESDHC_MIX_CTRL_TUNING_MASK,
						host->ioaddr + ESDHC_MIX_CTRL);
				imx_data->is_ddr = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (val & SDHCI_RESET_DATA) अणु
			/*
			 * The eSDHC DAT line software reset clears at least the
			 * data transfer width on i.MX25, so make sure that the
			 * Host Control रेजिस्टर is unaffected.
			 */
			esdhc_clrset_le(host, 0xff, new_val,
					SDHCI_HOST_CONTROL);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_pltfm_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस pltfm_host->घड़ी;
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_pltfm_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस pltfm_host->घड़ी / 256 / 16;
पूर्ण

अटल अंतरभूत व्योम esdhc_pltfm_set_घड़ी(काष्ठा sdhci_host *host,
					 अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित पूर्णांक host_घड़ी = pltfm_host->घड़ी;
	पूर्णांक ddr_pre_भाग = imx_data->is_ddr ? 2 : 1;
	पूर्णांक pre_भाग = 1;
	पूर्णांक भाग = 1;
	पूर्णांक ret;
	u32 temp, val;

	अगर (esdhc_is_usdhc(imx_data)) अणु
		val = पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC);
		ग_लिखोl(val & ~ESDHC_VENDOR_SPEC_FRC_SDCLK_ON,
			host->ioaddr + ESDHC_VENDOR_SPEC);
		esdhc_रुको_क्रम_card_घड़ी_gate_off(host);
	पूर्ण

	अगर (घड़ी == 0) अणु
		host->mmc->actual_घड़ी = 0;
		वापस;
	पूर्ण

	/* For i.MX53 eSDHCv3, SYSCTL.SDCLKFS may not be set to 0. */
	अगर (is_imx53_esdhc(imx_data)) अणु
		/*
		 * According to the i.MX53 reference manual, अगर DLLCTRL[10] can
		 * be set, then the controller is eSDHCv3, अन्यथा it is eSDHCv2.
		 */
		val = पढ़ोl(host->ioaddr + ESDHC_DLL_CTRL);
		ग_लिखोl(val | BIT(10), host->ioaddr + ESDHC_DLL_CTRL);
		temp = पढ़ोl(host->ioaddr + ESDHC_DLL_CTRL);
		ग_लिखोl(val, host->ioaddr + ESDHC_DLL_CTRL);
		अगर (temp & BIT(10))
			pre_भाग = 2;
	पूर्ण

	temp = sdhci_पढ़ोl(host, ESDHC_SYSTEM_CONTROL);
	temp &= ~(ESDHC_CLOCK_IPGEN | ESDHC_CLOCK_HCKEN | ESDHC_CLOCK_PEREN
		| ESDHC_CLOCK_MASK);
	sdhci_ग_लिखोl(host, temp, ESDHC_SYSTEM_CONTROL);

	अगर (imx_data->socdata->flags & ESDHC_FLAG_ERR010450) अणु
		अचिन्हित पूर्णांक max_घड़ी;

		max_घड़ी = imx_data->is_ddr ? 45000000 : 150000000;

		घड़ी = min(घड़ी, max_घड़ी);
	पूर्ण

	जबतक (host_घड़ी / (16 * pre_भाग * ddr_pre_भाग) > घड़ी &&
			pre_भाग < 256)
		pre_भाग *= 2;

	जबतक (host_घड़ी / (भाग * pre_भाग * ddr_pre_भाग) > घड़ी && भाग < 16)
		भाग++;

	host->mmc->actual_घड़ी = host_घड़ी / (भाग * pre_भाग * ddr_pre_भाग);
	dev_dbg(mmc_dev(host->mmc), "desired SD clock: %d, actual: %d\n",
		घड़ी, host->mmc->actual_घड़ी);

	pre_भाग >>= 1;
	भाग--;

	temp = sdhci_पढ़ोl(host, ESDHC_SYSTEM_CONTROL);
	temp |= (ESDHC_CLOCK_IPGEN | ESDHC_CLOCK_HCKEN | ESDHC_CLOCK_PEREN
		| (भाग << ESDHC_DIVIDER_SHIFT)
		| (pre_भाग << ESDHC_PREDIV_SHIFT));
	sdhci_ग_लिखोl(host, temp, ESDHC_SYSTEM_CONTROL);

	/* need to रुको the bit 3 of the PRSSTAT to be set, make sure card घड़ी is stable */
	ret = पढ़ोl_poll_समयout(host->ioaddr + ESDHC_PRSSTAT, temp,
				(temp & ESDHC_CLOCK_STABLE), 2, 100);
	अगर (ret == -ETIMEDOUT)
		dev_warn(mmc_dev(host->mmc), "card clock still not stable in 100us!.\n");

	अगर (esdhc_is_usdhc(imx_data)) अणु
		val = पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC);
		ग_लिखोl(val | ESDHC_VENDOR_SPEC_FRC_SDCLK_ON,
			host->ioaddr + ESDHC_VENDOR_SPEC);
	पूर्ण

पूर्ण

अटल अचिन्हित पूर्णांक esdhc_pltfm_get_ro(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	काष्ठा esdhc_platक्रमm_data *boarddata = &imx_data->boarddata;

	चयन (boarddata->wp_type) अणु
	हाल ESDHC_WP_GPIO:
		वापस mmc_gpio_get_ro(host->mmc);
	हाल ESDHC_WP_CONTROLLER:
		वापस !(पढ़ोl(host->ioaddr + SDHCI_PRESENT_STATE) &
			       SDHCI_WRITE_PROTECT);
	हाल ESDHC_WP_NONE:
		अवरोध;
	पूर्ण

	वापस -ENOSYS;
पूर्ण

अटल व्योम esdhc_pltfm_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	u32 ctrl;

	चयन (width) अणु
	हाल MMC_BUS_WIDTH_8:
		ctrl = ESDHC_CTRL_8BITBUS;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		ctrl = ESDHC_CTRL_4BITBUS;
		अवरोध;
	शेष:
		ctrl = 0;
		अवरोध;
	पूर्ण

	esdhc_clrset_le(host, ESDHC_CTRL_BUSWIDTH_MASK, ctrl,
			SDHCI_HOST_CONTROL);
पूर्ण

अटल पूर्णांक usdhc_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	/*
	 * i.MX uSDHC पूर्णांकernally alपढ़ोy uses a fixed optimized timing क्रम
	 * DDR50, normally करोes not require tuning क्रम DDR50 mode.
	 */
	अगर (host->timing == MMC_TIMING_UHS_DDR50)
		वापस 0;

	वापस sdhci_execute_tuning(mmc, opcode);
पूर्ण

अटल व्योम esdhc_prepare_tuning(काष्ठा sdhci_host *host, u32 val)
अणु
	u32 reg;
	u8 sw_rst;
	पूर्णांक ret;

	/* FIXME: delay a bit क्रम card to be पढ़ोy क्रम next tuning due to errors */
	mdelay(1);

	/* IC suggest to reset USDHC beक्रमe every tuning command */
	esdhc_clrset_le(host, 0xff, SDHCI_RESET_ALL, SDHCI_SOFTWARE_RESET);
	ret = पढ़ोb_poll_समयout(host->ioaddr + SDHCI_SOFTWARE_RESET, sw_rst,
				!(sw_rst & SDHCI_RESET_ALL), 10, 100);
	अगर (ret == -ETIMEDOUT)
		dev_warn(mmc_dev(host->mmc),
		"warning! RESET_ALL never complete before sending tuning command\n");

	reg = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
	reg |= ESDHC_MIX_CTRL_EXE_TUNE | ESDHC_MIX_CTRL_SMPCLK_SEL |
			ESDHC_MIX_CTRL_FBCLK_SEL;
	ग_लिखोl(reg, host->ioaddr + ESDHC_MIX_CTRL);
	ग_लिखोl(val << 8, host->ioaddr + ESDHC_TUNE_CTRL_STATUS);
	dev_dbg(mmc_dev(host->mmc),
		"tuning with delay 0x%x ESDHC_TUNE_CTRL_STATUS 0x%x\n",
			val, पढ़ोl(host->ioaddr + ESDHC_TUNE_CTRL_STATUS));
पूर्ण

अटल व्योम esdhc_post_tuning(काष्ठा sdhci_host *host)
अणु
	u32 reg;

	reg = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
	reg &= ~ESDHC_MIX_CTRL_EXE_TUNE;
	reg |= ESDHC_MIX_CTRL_AUTO_TUNE_EN;
	ग_लिखोl(reg, host->ioaddr + ESDHC_MIX_CTRL);
पूर्ण

अटल पूर्णांक esdhc_executing_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	पूर्णांक min, max, avg, ret;

	/* find the mininum delay first which can pass tuning */
	min = ESDHC_TUNE_CTRL_MIN;
	जबतक (min < ESDHC_TUNE_CTRL_MAX) अणु
		esdhc_prepare_tuning(host, min);
		अगर (!mmc_send_tuning(host->mmc, opcode, शून्य))
			अवरोध;
		min += ESDHC_TUNE_CTRL_STEP;
	पूर्ण

	/* find the maxinum delay which can not pass tuning */
	max = min + ESDHC_TUNE_CTRL_STEP;
	जबतक (max < ESDHC_TUNE_CTRL_MAX) अणु
		esdhc_prepare_tuning(host, max);
		अगर (mmc_send_tuning(host->mmc, opcode, शून्य)) अणु
			max -= ESDHC_TUNE_CTRL_STEP;
			अवरोध;
		पूर्ण
		max += ESDHC_TUNE_CTRL_STEP;
	पूर्ण

	/* use average delay to get the best timing */
	avg = (min + max) / 2;
	esdhc_prepare_tuning(host, avg);
	ret = mmc_send_tuning(host->mmc, opcode, शून्य);
	esdhc_post_tuning(host);

	dev_dbg(mmc_dev(host->mmc), "tuning %s at 0x%x ret %d\n",
		ret ? "failed" : "passed", avg, ret);

	वापस ret;
पूर्ण

अटल व्योम esdhc_hs400_enhanced_strobe(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 m;

	m = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
	अगर (ios->enhanced_strobe)
		m |= ESDHC_MIX_CTRL_HS400_ES_EN;
	अन्यथा
		m &= ~ESDHC_MIX_CTRL_HS400_ES_EN;
	ग_लिखोl(m, host->ioaddr + ESDHC_MIX_CTRL);
पूर्ण

अटल पूर्णांक esdhc_change_pinstate(काष्ठा sdhci_host *host,
						अचिन्हित पूर्णांक uhs)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	काष्ठा pinctrl_state *pinctrl;

	dev_dbg(mmc_dev(host->mmc), "change pinctrl state for uhs %d\n", uhs);

	अगर (IS_ERR(imx_data->pinctrl) ||
		IS_ERR(imx_data->pins_100mhz) ||
		IS_ERR(imx_data->pins_200mhz))
		वापस -EINVAL;

	चयन (uhs) अणु
	हाल MMC_TIMING_UHS_SDR50:
	हाल MMC_TIMING_UHS_DDR50:
		pinctrl = imx_data->pins_100mhz;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
	हाल MMC_TIMING_MMC_HS400:
		pinctrl = imx_data->pins_200mhz;
		अवरोध;
	शेष:
		/* back to शेष state क्रम other legacy timing */
		वापस pinctrl_select_शेष_state(mmc_dev(host->mmc));
	पूर्ण

	वापस pinctrl_select_state(imx_data->pinctrl, pinctrl);
पूर्ण

/*
 * For HS400 eMMC, there is a data_strobe line. This संकेत is generated
 * by the device and used क्रम data output and CRC status response output
 * in HS400 mode. The frequency of this संकेत follows the frequency of
 * CLK generated by host. The host receives the data which is aligned to the
 * edge of data_strobe line. Due to the समय delay between CLK line and
 * data_strobe line, अगर the delay समय is larger than one घड़ी cycle,
 * then CLK and data_strobe line will be misaligned, पढ़ो error shows up.
 */
अटल व्योम esdhc_set_strobe_dll(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 strobe_delay;
	u32 v;
	पूर्णांक ret;

	/* disable घड़ी beक्रमe enabling strobe dll */
	ग_लिखोl(पढ़ोl(host->ioaddr + ESDHC_VENDOR_SPEC) &
		~ESDHC_VENDOR_SPEC_FRC_SDCLK_ON,
		host->ioaddr + ESDHC_VENDOR_SPEC);
	esdhc_रुको_क्रम_card_घड़ी_gate_off(host);

	/* क्रमce a reset on strobe dll */
	ग_लिखोl(ESDHC_STROBE_DLL_CTRL_RESET,
		host->ioaddr + ESDHC_STROBE_DLL_CTRL);
	/* clear the reset bit on strobe dll beक्रमe any setting */
	ग_लिखोl(0, host->ioaddr + ESDHC_STROBE_DLL_CTRL);

	/*
	 * enable strobe dll ctrl and adjust the delay target
	 * क्रम the uSDHC loopback पढ़ो घड़ी
	 */
	अगर (imx_data->boarddata.strobe_dll_delay_target)
		strobe_delay = imx_data->boarddata.strobe_dll_delay_target;
	अन्यथा
		strobe_delay = ESDHC_STROBE_DLL_CTRL_SLV_DLY_TARGET_DEFAULT;
	v = ESDHC_STROBE_DLL_CTRL_ENABLE |
		ESDHC_STROBE_DLL_CTRL_SLV_UPDATE_INT_DEFAULT |
		(strobe_delay << ESDHC_STROBE_DLL_CTRL_SLV_DLY_TARGET_SHIFT);
	ग_लिखोl(v, host->ioaddr + ESDHC_STROBE_DLL_CTRL);

	/* रुको max 50us to get the REF/SLV lock */
	ret = पढ़ोl_poll_समयout(host->ioaddr + ESDHC_STROBE_DLL_STATUS, v,
		((v & ESDHC_STROBE_DLL_STS_REF_LOCK) && (v & ESDHC_STROBE_DLL_STS_SLV_LOCK)), 1, 50);
	अगर (ret == -ETIMEDOUT)
		dev_warn(mmc_dev(host->mmc),
		"warning! HS400 strobe DLL status REF/SLV not lock in 50us, STROBE DLL status is %x!\n", v);
पूर्ण

अटल व्योम esdhc_reset_tuning(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	u32 ctrl;

	/* Reset the tuning circuit */
	अगर (esdhc_is_usdhc(imx_data)) अणु
		अगर (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING) अणु
			ctrl = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
			ctrl &= ~ESDHC_MIX_CTRL_SMPCLK_SEL;
			ctrl &= ~ESDHC_MIX_CTRL_FBCLK_SEL;
			ग_लिखोl(ctrl, host->ioaddr + ESDHC_MIX_CTRL);
			ग_लिखोl(0, host->ioaddr + ESDHC_TUNE_CTRL_STATUS);
		पूर्ण अन्यथा अगर (imx_data->socdata->flags & ESDHC_FLAG_STD_TUNING) अणु
			ctrl = पढ़ोl(host->ioaddr + SDHCI_AUTO_CMD_STATUS);
			ctrl &= ~ESDHC_MIX_CTRL_SMPCLK_SEL;
			ग_लिखोl(ctrl, host->ioaddr + SDHCI_AUTO_CMD_STATUS);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esdhc_set_uhs_संकेतing(काष्ठा sdhci_host *host, अचिन्हित timing)
अणु
	u32 m;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	काष्ठा esdhc_platक्रमm_data *boarddata = &imx_data->boarddata;

	/* disable ddr mode and disable HS400 mode */
	m = पढ़ोl(host->ioaddr + ESDHC_MIX_CTRL);
	m &= ~(ESDHC_MIX_CTRL_DDREN | ESDHC_MIX_CTRL_HS400_EN);
	imx_data->is_ddr = 0;

	चयन (timing) अणु
	हाल MMC_TIMING_UHS_SDR12:
	हाल MMC_TIMING_UHS_SDR25:
	हाल MMC_TIMING_UHS_SDR50:
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_MMC_HS200:
		ग_लिखोl(m, host->ioaddr + ESDHC_MIX_CTRL);
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		m |= ESDHC_MIX_CTRL_DDREN;
		ग_लिखोl(m, host->ioaddr + ESDHC_MIX_CTRL);
		imx_data->is_ddr = 1;
		अगर (boarddata->delay_line) अणु
			u32 v;
			v = boarddata->delay_line <<
				ESDHC_DLL_OVERRIDE_VAL_SHIFT |
				(1 << ESDHC_DLL_OVERRIDE_EN_SHIFT);
			अगर (is_imx53_esdhc(imx_data))
				v <<= 1;
			ग_लिखोl(v, host->ioaddr + ESDHC_DLL_CTRL);
		पूर्ण
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		m |= ESDHC_MIX_CTRL_DDREN | ESDHC_MIX_CTRL_HS400_EN;
		ग_लिखोl(m, host->ioaddr + ESDHC_MIX_CTRL);
		imx_data->is_ddr = 1;
		/* update घड़ी after enable DDR क्रम strobe DLL lock */
		host->ops->set_घड़ी(host, host->घड़ी);
		esdhc_set_strobe_dll(host);
		अवरोध;
	हाल MMC_TIMING_LEGACY:
	शेष:
		esdhc_reset_tuning(host);
		अवरोध;
	पूर्ण

	esdhc_change_pinstate(host, timing);
पूर्ण

अटल व्योम esdhc_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	sdhci_reset(host, mask);

	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_get_max_समयout_count(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);

	/* Doc Erratum: the uSDHC actual maximum समयout count is 1 << 29 */
	वापस esdhc_is_usdhc(imx_data) ? 1 << 29 : 1 << 27;
पूर्ण

अटल व्योम esdhc_set_समयout(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);

	/* use maximum समयout counter */
	esdhc_clrset_le(host, ESDHC_SYS_CTRL_DTOCV_MASK,
			esdhc_is_usdhc(imx_data) ? 0xF : 0xE,
			SDHCI_TIMEOUT_CONTROL);
पूर्ण

अटल u32 esdhc_cqhci_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);

	वापस 0;
पूर्ण

अटल काष्ठा sdhci_ops sdhci_esdhc_ops = अणु
	.पढ़ो_l = esdhc_पढ़ोl_le,
	.पढ़ो_w = esdhc_पढ़ोw_le,
	.पढ़ो_b = esdhc_पढ़ोb_le,
	.ग_लिखो_l = esdhc_ग_लिखोl_le,
	.ग_लिखो_w = esdhc_ग_लिखोw_le,
	.ग_लिखो_b = esdhc_ग_लिखोb_le,
	.set_घड़ी = esdhc_pltfm_set_घड़ी,
	.get_max_घड़ी = esdhc_pltfm_get_max_घड़ी,
	.get_min_घड़ी = esdhc_pltfm_get_min_घड़ी,
	.get_max_समयout_count = esdhc_get_max_समयout_count,
	.get_ro = esdhc_pltfm_get_ro,
	.set_समयout = esdhc_set_समयout,
	.set_bus_width = esdhc_pltfm_set_bus_width,
	.set_uhs_संकेतing = esdhc_set_uhs_संकेतing,
	.reset = esdhc_reset,
	.irq = esdhc_cqhci_irq,
	.dump_venकरोr_regs = esdhc_dump_debug_regs,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_esdhc_imx_pdata = अणु
	.quirks = ESDHC_DEFAULT_QUIRKS | SDHCI_QUIRK_NO_HISPD_BIT
			| SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC
			| SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC
			| SDHCI_QUIRK_BROKEN_CARD_DETECTION,
	.ops = &sdhci_esdhc_ops,
पूर्ण;

अटल व्योम sdhci_esdhc_imx_hwinit(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	काष्ठा cqhci_host *cq_host = host->mmc->cqe_निजी;
	पूर्णांक पंचांगp;

	अगर (esdhc_is_usdhc(imx_data)) अणु
		/*
		 * The imx6q ROM code will change the शेष watermark
		 * level setting to something insane.  Change it back here.
		 */
		ग_लिखोl(ESDHC_WTMK_DEFAULT_VAL, host->ioaddr + ESDHC_WTMK_LVL);

		/*
		 * ROM code will change the bit burst_length_enable setting
		 * to zero अगर this usdhc is chosen to boot प्रणाली. Change
		 * it back here, otherwise it will impact the perक्रमmance a
		 * lot. This bit is used to enable/disable the burst length
		 * क्रम the बाह्यal AHB2AXI bridge. It's useful especially
		 * क्रम INCR transfer because without burst length indicator,
		 * the AHB2AXI bridge करोes not know the burst length in
		 * advance. And without burst length indicator, AHB INCR
		 * transfer can only be converted to singles on the AXI side.
		 */
		ग_लिखोl(पढ़ोl(host->ioaddr + SDHCI_HOST_CONTROL)
			| ESDHC_BURST_LEN_EN_INCR,
			host->ioaddr + SDHCI_HOST_CONTROL);

		/*
		 * erratum ESDHC_FLAG_ERR004536 fix क्रम MX6Q TO1.2 and MX6DL
		 * TO1.1, it's harmless क्रम MX6SL
		 */
		ग_लिखोl(पढ़ोl(host->ioaddr + 0x6c) & ~BIT(7),
			host->ioaddr + 0x6c);

		/* disable DLL_CTRL delay line settings */
		ग_लिखोl(0x0, host->ioaddr + ESDHC_DLL_CTRL);

		/*
		 * For the हाल of command with busy, अगर set the bit
		 * ESDHC_VEND_SPEC2_EN_BUSY_IRQ, USDHC will generate a
		 * transfer complete पूर्णांकerrupt when busy is deनिश्चितed.
		 * When CQHCI use DCMD to send a CMD need R1b respons,
		 * CQHCI require to set ESDHC_VEND_SPEC2_EN_BUSY_IRQ,
		 * otherwise DCMD will always meet समयout रुकोing क्रम
		 * hardware पूर्णांकerrupt issue.
		 */
		अगर (imx_data->socdata->flags & ESDHC_FLAG_CQHCI) अणु
			पंचांगp = पढ़ोl(host->ioaddr + ESDHC_VEND_SPEC2);
			पंचांगp |= ESDHC_VEND_SPEC2_EN_BUSY_IRQ;
			ग_लिखोl(पंचांगp, host->ioaddr + ESDHC_VEND_SPEC2);

			host->quirks &= ~SDHCI_QUIRK_NO_BUSY_IRQ;
		पूर्ण

		अगर (imx_data->socdata->flags & ESDHC_FLAG_STD_TUNING) अणु
			पंचांगp = पढ़ोl(host->ioaddr + ESDHC_TUNING_CTRL);
			पंचांगp |= ESDHC_STD_TUNING_EN |
				ESDHC_TUNING_START_TAP_DEFAULT;
			अगर (imx_data->boarddata.tuning_start_tap) अणु
				पंचांगp &= ~ESDHC_TUNING_START_TAP_MASK;
				पंचांगp |= imx_data->boarddata.tuning_start_tap;
			पूर्ण

			अगर (imx_data->boarddata.tuning_step) अणु
				पंचांगp &= ~ESDHC_TUNING_STEP_MASK;
				पंचांगp |= imx_data->boarddata.tuning_step
					<< ESDHC_TUNING_STEP_SHIFT;
			पूर्ण

			/* Disable the CMD CRC check क्रम tuning, अगर not, need to
			 * add some delay after every tuning command, because
			 * hardware standard tuning logic will directly go to next
			 * step once it detect the CMD CRC error, will not रुको क्रम
			 * the card side to finally send out the tuning data, trigger
			 * the buffer पढ़ो पढ़ोy पूर्णांकerrupt immediately. If usdhc send
			 * the next tuning command some eMMC card will stuck, can't
			 * response, block the tuning procedure or the first command
			 * after the whole tuning procedure always can't get any response.
			 */
			पंचांगp |= ESDHC_TUNING_CMD_CRC_CHECK_DISABLE;
			ग_लिखोl(पंचांगp, host->ioaddr + ESDHC_TUNING_CTRL);
		पूर्ण अन्यथा अगर (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING) अणु
			/*
			 * ESDHC_STD_TUNING_EN may be configed in bootloader
			 * or ROM code, so clear this bit here to make sure
			 * the manual tuning can work.
			 */
			पंचांगp = पढ़ोl(host->ioaddr + ESDHC_TUNING_CTRL);
			पंचांगp &= ~ESDHC_STD_TUNING_EN;
			ग_लिखोl(पंचांगp, host->ioaddr + ESDHC_TUNING_CTRL);
		पूर्ण

		/*
		 * On i.MX8MM, we are running Dual Linux OS, with 1st Linux using SD Card
		 * as rootfs storage, 2nd Linux using eMMC as rootfs storage. We let the
		 * the 1st linux configure घातer/घड़ी क्रम the 2nd Linux.
		 *
		 * When the 2nd Linux is booting पूर्णांकo rootfs stage, we let the 1st Linux
		 * to destroy the 2nd linux, then restart the 2nd linux, we met SDHCI dump.
		 * After we clear the pending पूर्णांकerrupt and halt CQCTL, issue gone.
		 */
		अगर (cq_host) अणु
			पंचांगp = cqhci_पढ़ोl(cq_host, CQHCI_IS);
			cqhci_ग_लिखोl(cq_host, पंचांगp, CQHCI_IS);
			cqhci_ग_लिखोl(cq_host, CQHCI_HALT, CQHCI_CTL);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esdhc_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u32 reg;
	u16 mode;
	पूर्णांक count = 10;

	/*
	 * CQE माला_लो stuck अगर it sees Buffer Read Enable bit set, which can be
	 * the हाल after tuning, so ensure the buffer is drained.
	 */
	reg = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
	जबतक (reg & SDHCI_DATA_AVAILABLE) अणु
		sdhci_पढ़ोl(host, SDHCI_BUFFER);
		reg = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
		अगर (count-- == 0) अणु
			dev_warn(mmc_dev(host->mmc),
				"CQE may get stuck because the Buffer Read Enable bit is set\n");
			अवरोध;
		पूर्ण
		mdelay(1);
	पूर्ण

	/*
	 * Runसमय resume will reset the entire host controller, which
	 * will also clear the DMAEN/BCEN of रेजिस्टर ESDHC_MIX_CTRL.
	 * Here set DMAEN and BCEN when enable CMDQ.
	 */
	mode = sdhci_पढ़ोw(host, SDHCI_TRANSFER_MODE);
	अगर (host->flags & SDHCI_REQ_USE_DMA)
		mode |= SDHCI_TRNS_DMA;
	अगर (!(host->quirks2 & SDHCI_QUIRK2_SUPPORT_SINGLE))
		mode |= SDHCI_TRNS_BLK_CNT_EN;
	sdhci_ग_लिखोw(host, mode, SDHCI_TRANSFER_MODE);

	/*
	 * Though Runसमय resume reset the entire host controller,
	 * but करो not impact the CQHCI side, need to clear the
	 * HALT bit, aव्योम CQHCI stuck in the first request when
	 * प्रणाली resume back.
	 */
	cqhci_ग_लिखोl(cq_host, 0, CQHCI_CTL);
	अगर (cqhci_पढ़ोl(cq_host, CQHCI_CTL) && CQHCI_HALT)
		dev_err(mmc_dev(host->mmc),
			"failed to exit halt state when enable CQE\n");


	sdhci_cqe_enable(mmc);
पूर्ण

अटल व्योम esdhc_sdhci_dumpregs(काष्ठा mmc_host *mmc)
अणु
	sdhci_dumpregs(mmc_priv(mmc));
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops esdhc_cqhci_ops = अणु
	.enable		= esdhc_cqe_enable,
	.disable	= sdhci_cqe_disable,
	.dumpregs	= esdhc_sdhci_dumpregs,
पूर्ण;

अटल पूर्णांक
sdhci_esdhc_imx_probe_dt(काष्ठा platक्रमm_device *pdev,
			 काष्ठा sdhci_host *host,
			 काष्ठा pltfm_imx_data *imx_data)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा esdhc_platक्रमm_data *boarddata = &imx_data->boarddata;
	पूर्णांक ret;

	अगर (of_get_property(np, "fsl,wp-controller", शून्य))
		boarddata->wp_type = ESDHC_WP_CONTROLLER;

	/*
	 * If we have this property, then activate WP check.
	 * Retrieveing and requesting the actual WP GPIO will happen
	 * in the call to mmc_of_parse().
	 */
	अगर (of_property_पढ़ो_bool(np, "wp-gpios"))
		boarddata->wp_type = ESDHC_WP_GPIO;

	of_property_पढ़ो_u32(np, "fsl,tuning-step", &boarddata->tuning_step);
	of_property_पढ़ो_u32(np, "fsl,tuning-start-tap",
			     &boarddata->tuning_start_tap);

	of_property_पढ़ो_u32(np, "fsl,strobe-dll-delay-target",
				&boarddata->strobe_dll_delay_target);
	अगर (of_find_property(np, "no-1-8-v", शून्य))
		host->quirks2 |= SDHCI_QUIRK2_NO_1_8_V;

	अगर (of_property_पढ़ो_u32(np, "fsl,delay-line", &boarddata->delay_line))
		boarddata->delay_line = 0;

	mmc_of_parse_voltage(host->mmc, &host->ocr_mask);

	अगर (esdhc_is_usdhc(imx_data) && !IS_ERR(imx_data->pinctrl)) अणु
		imx_data->pins_100mhz = pinctrl_lookup_state(imx_data->pinctrl,
						ESDHC_PINCTRL_STATE_100MHZ);
		imx_data->pins_200mhz = pinctrl_lookup_state(imx_data->pinctrl,
						ESDHC_PINCTRL_STATE_200MHZ);
	पूर्ण

	/* call to generic mmc_of_parse to support additional capabilities */
	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		वापस ret;

	अगर (mmc_gpio_get_cd(host->mmc) >= 0)
		host->quirks &= ~SDHCI_QUIRK_BROKEN_CARD_DETECTION;

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_esdhc_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_host *host;
	काष्ठा cqhci_host *cq_host;
	पूर्णांक err;
	काष्ठा pltfm_imx_data *imx_data;

	host = sdhci_pltfm_init(pdev, &sdhci_esdhc_imx_pdata,
				माप(*imx_data));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);

	imx_data = sdhci_pltfm_priv(pltfm_host);

	imx_data->socdata = device_get_match_data(&pdev->dev);

	अगर (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		cpu_latency_qos_add_request(&imx_data->pm_qos_req, 0);

	imx_data->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(imx_data->clk_ipg)) अणु
		err = PTR_ERR(imx_data->clk_ipg);
		जाओ मुक्त_sdhci;
	पूर्ण

	imx_data->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(imx_data->clk_ahb)) अणु
		err = PTR_ERR(imx_data->clk_ahb);
		जाओ मुक्त_sdhci;
	पूर्ण

	imx_data->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(imx_data->clk_per)) अणु
		err = PTR_ERR(imx_data->clk_per);
		जाओ मुक्त_sdhci;
	पूर्ण

	pltfm_host->clk = imx_data->clk_per;
	pltfm_host->घड़ी = clk_get_rate(pltfm_host->clk);
	err = clk_prepare_enable(imx_data->clk_per);
	अगर (err)
		जाओ मुक्त_sdhci;
	err = clk_prepare_enable(imx_data->clk_ipg);
	अगर (err)
		जाओ disable_per_clk;
	err = clk_prepare_enable(imx_data->clk_ahb);
	अगर (err)
		जाओ disable_ipg_clk;

	imx_data->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(imx_data->pinctrl))
		dev_warn(mmc_dev(host->mmc), "could not get pinctrl\n");

	अगर (esdhc_is_usdhc(imx_data)) अणु
		host->quirks2 |= SDHCI_QUIRK2_PRESET_VALUE_BROKEN;
		host->mmc->caps |= MMC_CAP_1_8V_DDR | MMC_CAP_3_3V_DDR;

		/* GPIO CD can be set as a wakeup source */
		host->mmc->caps |= MMC_CAP_CD_WAKE;

		अगर (!(imx_data->socdata->flags & ESDHC_FLAG_HS200))
			host->quirks2 |= SDHCI_QUIRK2_BROKEN_HS200;

		/* clear tuning bits in हाल ROM has set it alपढ़ोy */
		ग_लिखोl(0x0, host->ioaddr + ESDHC_MIX_CTRL);
		ग_लिखोl(0x0, host->ioaddr + SDHCI_AUTO_CMD_STATUS);
		ग_लिखोl(0x0, host->ioaddr + ESDHC_TUNE_CTRL_STATUS);

		/*
		 * Link usdhc specअगरic mmc_host_ops execute_tuning function,
		 * to replace the standard one in sdhci_ops.
		 */
		host->mmc_host_ops.execute_tuning = usdhc_execute_tuning;
	पूर्ण

	अगर (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING)
		sdhci_esdhc_ops.platक्रमm_execute_tuning =
					esdhc_executing_tuning;

	अगर (imx_data->socdata->flags & ESDHC_FLAG_ERR004536)
		host->quirks |= SDHCI_QUIRK_BROKEN_ADMA;

	अगर (imx_data->socdata->flags & ESDHC_FLAG_HS400)
		host->quirks2 |= SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400;

	अगर (imx_data->socdata->flags & ESDHC_FLAG_BROKEN_AUTO_CMD23)
		host->quirks2 |= SDHCI_QUIRK2_ACMD23_BROKEN;

	अगर (imx_data->socdata->flags & ESDHC_FLAG_HS400_ES) अणु
		host->mmc->caps2 |= MMC_CAP2_HS400_ES;
		host->mmc_host_ops.hs400_enhanced_strobe =
					esdhc_hs400_enhanced_strobe;
	पूर्ण

	अगर (imx_data->socdata->flags & ESDHC_FLAG_CQHCI) अणु
		host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;
		cq_host = devm_kzalloc(&pdev->dev, माप(*cq_host), GFP_KERNEL);
		अगर (!cq_host) अणु
			err = -ENOMEM;
			जाओ disable_ahb_clk;
		पूर्ण

		cq_host->mmio = host->ioaddr + ESDHC_CQHCI_ADDR_OFFSET;
		cq_host->ops = &esdhc_cqhci_ops;

		err = cqhci_init(cq_host, host->mmc, false);
		अगर (err)
			जाओ disable_ahb_clk;
	पूर्ण

	err = sdhci_esdhc_imx_probe_dt(pdev, host, imx_data);
	अगर (err)
		जाओ disable_ahb_clk;

	sdhci_esdhc_imx_hwinit(host);

	err = sdhci_add_host(host);
	अगर (err)
		जाओ disable_ahb_clk;

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;

disable_ahb_clk:
	clk_disable_unprepare(imx_data->clk_ahb);
disable_ipg_clk:
	clk_disable_unprepare(imx_data->clk_ipg);
disable_per_clk:
	clk_disable_unprepare(imx_data->clk_per);
मुक्त_sdhci:
	अगर (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		cpu_latency_qos_हटाओ_request(&imx_data->pm_qos_req);
	sdhci_pltfm_मुक्त(pdev);
	वापस err;
पूर्ण

अटल पूर्णांक sdhci_esdhc_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक dead;

	pm_runसमय_get_sync(&pdev->dev);
	dead = (पढ़ोl(host->ioaddr + SDHCI_INT_STATUS) == 0xffffffff);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	sdhci_हटाओ_host(host, dead);

	clk_disable_unprepare(imx_data->clk_per);
	clk_disable_unprepare(imx_data->clk_ipg);
	clk_disable_unprepare(imx_data->clk_ahb);

	अगर (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		cpu_latency_qos_हटाओ_request(&imx_data->pm_qos_req);

	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_esdhc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	अगर (host->mmc->caps2 & MMC_CAP2_CQE) अणु
		ret = cqhci_suspend(host->mmc);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((imx_data->socdata->flags & ESDHC_FLAG_STATE_LOST_IN_LPMODE) &&
		(host->tuning_mode != SDHCI_TUNING_MODE_1)) अणु
		mmc_retune_समयr_stop(host->mmc);
		mmc_retune_needed(host->mmc);
	पूर्ण

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	ret = sdhci_suspend_host(host);
	अगर (ret)
		वापस ret;

	ret = pinctrl_pm_select_sleep_state(dev);
	अगर (ret)
		वापस ret;

	ret = mmc_gpio_set_cd_wake(host->mmc, true);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_esdhc_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;

	/* re-initialize hw state in हाल it's lost in low घातer mode */
	sdhci_esdhc_imx_hwinit(host);

	ret = sdhci_resume_host(host);
	अगर (ret)
		वापस ret;

	अगर (host->mmc->caps2 & MMC_CAP2_CQE)
		ret = cqhci_resume(host->mmc);

	अगर (!ret)
		ret = mmc_gpio_set_cd_wake(host->mmc, false);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdhci_esdhc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	अगर (host->mmc->caps2 & MMC_CAP2_CQE) अणु
		ret = cqhci_suspend(host->mmc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sdhci_runसमय_suspend_host(host);
	अगर (ret)
		वापस ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	imx_data->actual_घड़ी = host->mmc->actual_घड़ी;
	esdhc_pltfm_set_घड़ी(host, 0);
	clk_disable_unprepare(imx_data->clk_per);
	clk_disable_unprepare(imx_data->clk_ipg);
	clk_disable_unprepare(imx_data->clk_ahb);

	अगर (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		cpu_latency_qos_हटाओ_request(&imx_data->pm_qos_req);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_esdhc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक err;

	अगर (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		cpu_latency_qos_add_request(&imx_data->pm_qos_req, 0);

	अगर (imx_data->socdata->flags & ESDHC_FLAG_CLK_RATE_LOST_IN_PM_RUNTIME)
		clk_set_rate(imx_data->clk_per, pltfm_host->घड़ी);

	err = clk_prepare_enable(imx_data->clk_ahb);
	अगर (err)
		जाओ हटाओ_pm_qos_request;

	err = clk_prepare_enable(imx_data->clk_per);
	अगर (err)
		जाओ disable_ahb_clk;

	err = clk_prepare_enable(imx_data->clk_ipg);
	अगर (err)
		जाओ disable_per_clk;

	esdhc_pltfm_set_घड़ी(host, imx_data->actual_घड़ी);

	err = sdhci_runसमय_resume_host(host, 0);
	अगर (err)
		जाओ disable_ipg_clk;

	अगर (host->mmc->caps2 & MMC_CAP2_CQE)
		err = cqhci_resume(host->mmc);

	वापस err;

disable_ipg_clk:
	clk_disable_unprepare(imx_data->clk_ipg);
disable_per_clk:
	clk_disable_unprepare(imx_data->clk_per);
disable_ahb_clk:
	clk_disable_unprepare(imx_data->clk_ahb);
हटाओ_pm_qos_request:
	अगर (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		cpu_latency_qos_हटाओ_request(&imx_data->pm_qos_req);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sdhci_esdhc_pmops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_esdhc_suspend, sdhci_esdhc_resume)
	SET_RUNTIME_PM_OPS(sdhci_esdhc_runसमय_suspend,
				sdhci_esdhc_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sdhci_esdhc_imx_driver = अणु
	.driver		= अणु
		.name	= "sdhci-esdhc-imx",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = imx_esdhc_dt_ids,
		.pm	= &sdhci_esdhc_pmops,
	पूर्ण,
	.probe		= sdhci_esdhc_imx_probe,
	.हटाओ		= sdhci_esdhc_imx_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_esdhc_imx_driver);

MODULE_DESCRIPTION("SDHCI driver for Freescale i.MX eSDHC");
MODULE_AUTHOR("Wolfram Sang <kernel@pengutronix.de>");
MODULE_LICENSE("GPL v2");
