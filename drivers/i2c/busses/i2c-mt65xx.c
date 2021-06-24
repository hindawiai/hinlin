<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Xuकरोng Chen <xuकरोng.chen@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#घोषणा I2C_RS_TRANSFER			(1 << 4)
#घोषणा I2C_ARB_LOST			(1 << 3)
#घोषणा I2C_HS_NACKERR			(1 << 2)
#घोषणा I2C_ACKERR			(1 << 1)
#घोषणा I2C_TRANSAC_COMP		(1 << 0)
#घोषणा I2C_TRANSAC_START		(1 << 0)
#घोषणा I2C_RS_MUL_CNFG			(1 << 15)
#घोषणा I2C_RS_MUL_TRIG			(1 << 14)
#घोषणा I2C_DCM_DISABLE			0x0000
#घोषणा I2C_IO_CONFIG_OPEN_DRAIN	0x0003
#घोषणा I2C_IO_CONFIG_PUSH_PULL		0x0000
#घोषणा I2C_SOFT_RST			0x0001
#घोषणा I2C_HANDSHAKE_RST		0x0020
#घोषणा I2C_FIFO_ADDR_CLR		0x0001
#घोषणा I2C_DELAY_LEN			0x0002
#घोषणा I2C_TIME_CLR_VALUE		0x0000
#घोषणा I2C_TIME_DEFAULT_VALUE		0x0003
#घोषणा I2C_WRRD_TRANAC_VALUE		0x0002
#घोषणा I2C_RD_TRANAC_VALUE		0x0001
#घोषणा I2C_SCL_MIS_COMP_VALUE		0x0000
#घोषणा I2C_CHN_CLR_FLAG		0x0000

#घोषणा I2C_DMA_CON_TX			0x0000
#घोषणा I2C_DMA_CON_RX			0x0001
#घोषणा I2C_DMA_ASYNC_MODE		0x0004
#घोषणा I2C_DMA_SKIP_CONFIG		0x0010
#घोषणा I2C_DMA_सूची_CHANGE		0x0200
#घोषणा I2C_DMA_START_EN		0x0001
#घोषणा I2C_DMA_INT_FLAG_NONE		0x0000
#घोषणा I2C_DMA_CLR_FLAG		0x0000
#घोषणा I2C_DMA_WARM_RST		0x0001
#घोषणा I2C_DMA_HARD_RST		0x0002
#घोषणा I2C_DMA_HANDSHAKE_RST		0x0004

#घोषणा MAX_SAMPLE_CNT_DIV		8
#घोषणा MAX_STEP_CNT_DIV		64
#घोषणा MAX_CLOCK_DIV			256
#घोषणा MAX_HS_STEP_CNT_DIV		8
#घोषणा I2C_STANDARD_MODE_BUFFER	(1000 / 2)
#घोषणा I2C_FAST_MODE_BUFFER		(300 / 2)
#घोषणा I2C_FAST_MODE_PLUS_BUFFER	(20 / 2)

#घोषणा I2C_CONTROL_RS                  (0x1 << 1)
#घोषणा I2C_CONTROL_DMA_EN              (0x1 << 2)
#घोषणा I2C_CONTROL_CLK_EXT_EN          (0x1 << 3)
#घोषणा I2C_CONTROL_सूची_CHANGE          (0x1 << 4)
#घोषणा I2C_CONTROL_ACKERR_DET_EN       (0x1 << 5)
#घोषणा I2C_CONTROL_TRANSFER_LEN_CHANGE (0x1 << 6)
#घोषणा I2C_CONTROL_DMAACK_EN           (0x1 << 8)
#घोषणा I2C_CONTROL_ASYNC_MODE          (0x1 << 9)
#घोषणा I2C_CONTROL_WRAPPER             (0x1 << 0)

#घोषणा I2C_DRV_NAME		"i2c-mt65xx"

क्रमागत DMA_REGS_OFFSET अणु
	OFFSET_INT_FLAG = 0x0,
	OFFSET_INT_EN = 0x04,
	OFFSET_EN = 0x08,
	OFFSET_RST = 0x0c,
	OFFSET_CON = 0x18,
	OFFSET_TX_MEM_ADDR = 0x1c,
	OFFSET_RX_MEM_ADDR = 0x20,
	OFFSET_TX_LEN = 0x24,
	OFFSET_RX_LEN = 0x28,
	OFFSET_TX_4G_MODE = 0x54,
	OFFSET_RX_4G_MODE = 0x58,
पूर्ण;

क्रमागत i2c_trans_st_rs अणु
	I2C_TRANS_STOP = 0,
	I2C_TRANS_REPEATED_START,
पूर्ण;

क्रमागत mtk_trans_op अणु
	I2C_MASTER_WR = 1,
	I2C_MASTER_RD,
	I2C_MASTER_WRRD,
पूर्ण;

क्रमागत I2C_REGS_OFFSET अणु
	OFFSET_DATA_PORT,
	OFFSET_SLAVE_ADDR,
	OFFSET_INTR_MASK,
	OFFSET_INTR_STAT,
	OFFSET_CONTROL,
	OFFSET_TRANSFER_LEN,
	OFFSET_TRANSAC_LEN,
	OFFSET_DELAY_LEN,
	OFFSET_TIMING,
	OFFSET_START,
	OFFSET_EXT_CONF,
	OFFSET_FIFO_STAT,
	OFFSET_FIFO_THRESH,
	OFFSET_FIFO_ADDR_CLR,
	OFFSET_IO_CONFIG,
	OFFSET_RSV_DEBUG,
	OFFSET_HS,
	OFFSET_SOFTRESET,
	OFFSET_DCM_EN,
	OFFSET_PATH_सूची,
	OFFSET_DEBUGSTAT,
	OFFSET_DEBUGCTRL,
	OFFSET_TRANSFER_LEN_AUX,
	OFFSET_CLOCK_DIV,
	OFFSET_LTIMING,
	OFFSET_SCL_HIGH_LOW_RATIO,
	OFFSET_HS_SCL_HIGH_LOW_RATIO,
	OFFSET_SCL_MIS_COMP_POINT,
	OFFSET_STA_STO_AC_TIMING,
	OFFSET_HS_STA_STO_AC_TIMING,
	OFFSET_SDA_TIMING,
पूर्ण;

अटल स्थिर u16 mt_i2c_regs_v1[] = अणु
	[OFFSET_DATA_PORT] = 0x0,
	[OFFSET_SLAVE_ADDR] = 0x4,
	[OFFSET_INTR_MASK] = 0x8,
	[OFFSET_INTR_STAT] = 0xc,
	[OFFSET_CONTROL] = 0x10,
	[OFFSET_TRANSFER_LEN] = 0x14,
	[OFFSET_TRANSAC_LEN] = 0x18,
	[OFFSET_DELAY_LEN] = 0x1c,
	[OFFSET_TIMING] = 0x20,
	[OFFSET_START] = 0x24,
	[OFFSET_EXT_CONF] = 0x28,
	[OFFSET_FIFO_STAT] = 0x30,
	[OFFSET_FIFO_THRESH] = 0x34,
	[OFFSET_FIFO_ADDR_CLR] = 0x38,
	[OFFSET_IO_CONFIG] = 0x40,
	[OFFSET_RSV_DEBUG] = 0x44,
	[OFFSET_HS] = 0x48,
	[OFFSET_SOFTRESET] = 0x50,
	[OFFSET_DCM_EN] = 0x54,
	[OFFSET_PATH_सूची] = 0x60,
	[OFFSET_DEBUGSTAT] = 0x64,
	[OFFSET_DEBUGCTRL] = 0x68,
	[OFFSET_TRANSFER_LEN_AUX] = 0x6c,
	[OFFSET_CLOCK_DIV] = 0x70,
	[OFFSET_SCL_HIGH_LOW_RATIO] = 0x74,
	[OFFSET_HS_SCL_HIGH_LOW_RATIO] = 0x78,
	[OFFSET_SCL_MIS_COMP_POINT] = 0x7C,
	[OFFSET_STA_STO_AC_TIMING] = 0x80,
	[OFFSET_HS_STA_STO_AC_TIMING] = 0x84,
	[OFFSET_SDA_TIMING] = 0x88,
पूर्ण;

अटल स्थिर u16 mt_i2c_regs_v2[] = अणु
	[OFFSET_DATA_PORT] = 0x0,
	[OFFSET_SLAVE_ADDR] = 0x4,
	[OFFSET_INTR_MASK] = 0x8,
	[OFFSET_INTR_STAT] = 0xc,
	[OFFSET_CONTROL] = 0x10,
	[OFFSET_TRANSFER_LEN] = 0x14,
	[OFFSET_TRANSAC_LEN] = 0x18,
	[OFFSET_DELAY_LEN] = 0x1c,
	[OFFSET_TIMING] = 0x20,
	[OFFSET_START] = 0x24,
	[OFFSET_EXT_CONF] = 0x28,
	[OFFSET_LTIMING] = 0x2c,
	[OFFSET_HS] = 0x30,
	[OFFSET_IO_CONFIG] = 0x34,
	[OFFSET_FIFO_ADDR_CLR] = 0x38,
	[OFFSET_SDA_TIMING] = 0x3c,
	[OFFSET_TRANSFER_LEN_AUX] = 0x44,
	[OFFSET_CLOCK_DIV] = 0x48,
	[OFFSET_SOFTRESET] = 0x50,
	[OFFSET_SCL_MIS_COMP_POINT] = 0x90,
	[OFFSET_DEBUGSTAT] = 0xe0,
	[OFFSET_DEBUGCTRL] = 0xe8,
	[OFFSET_FIFO_STAT] = 0xf4,
	[OFFSET_FIFO_THRESH] = 0xf8,
	[OFFSET_DCM_EN] = 0xf88,
पूर्ण;

काष्ठा mtk_i2c_compatible अणु
	स्थिर काष्ठा i2c_adapter_quirks *quirks;
	स्थिर u16 *regs;
	अचिन्हित अक्षर pmic_i2c: 1;
	अचिन्हित अक्षर dcm: 1;
	अचिन्हित अक्षर स्वतः_restart: 1;
	अचिन्हित अक्षर aux_len_reg: 1;
	अचिन्हित अक्षर timing_adjust: 1;
	अचिन्हित अक्षर dma_sync: 1;
	अचिन्हित अक्षर ltiming_adjust: 1;
	अचिन्हित अक्षर apdma_sync: 1;
	अचिन्हित अक्षर max_dma_support;
पूर्ण;

काष्ठा mtk_i2c_ac_timing अणु
	u16 htiming;
	u16 ltiming;
	u16 hs;
	u16 ext;
	u16 पूर्णांकer_clk_भाग;
	u16 scl_hl_ratio;
	u16 hs_scl_hl_ratio;
	u16 sta_stop;
	u16 hs_sta_stop;
	u16 sda_timing;
पूर्ण;

काष्ठा mtk_i2c अणु
	काष्ठा i2c_adapter adap;	/* i2c host adapter */
	काष्ठा device *dev;
	काष्ठा completion msg_complete;
	काष्ठा i2c_timings timing_info;

	/* set in i2c probe */
	व्योम __iomem *base;		/* i2c base addr */
	व्योम __iomem *pdmabase;		/* dma base address*/
	काष्ठा clk *clk_मुख्य;		/* मुख्य घड़ी क्रम i2c bus */
	काष्ठा clk *clk_dma;		/* DMA घड़ी क्रम i2c via DMA */
	काष्ठा clk *clk_pmic;		/* PMIC घड़ी क्रम i2c from PMIC */
	काष्ठा clk *clk_arb;		/* Arbitrator घड़ी क्रम i2c */
	bool have_pmic;			/* can use i2c pins from PMIC */
	bool use_push_pull;		/* IO config push-pull mode */

	u16 irq_stat;			/* पूर्णांकerrupt status */
	अचिन्हित पूर्णांक clk_src_भाग;
	अचिन्हित पूर्णांक speed_hz;		/* The speed in transfer */
	क्रमागत mtk_trans_op op;
	u16 timing_reg;
	u16 high_speed_reg;
	u16 ltiming_reg;
	अचिन्हित अक्षर स्वतः_restart;
	bool ignore_restart_irq;
	काष्ठा mtk_i2c_ac_timing ac_timing;
	स्थिर काष्ठा mtk_i2c_compatible *dev_comp;
पूर्ण;

/**
 * काष्ठा i2c_spec_values:
 * @min_low_ns: min LOW period of the SCL घड़ी
 * @min_su_sta_ns: min set-up समय क्रम a repeated START condition
 * @max_hd_dat_ns: max data hold समय
 * @min_su_dat_ns: min data set-up समय
 */
काष्ठा i2c_spec_values अणु
	अचिन्हित पूर्णांक min_low_ns;
	अचिन्हित पूर्णांक min_su_sta_ns;
	अचिन्हित पूर्णांक max_hd_dat_ns;
	अचिन्हित पूर्णांक min_su_dat_ns;
पूर्ण;

अटल स्थिर काष्ठा i2c_spec_values standard_mode_spec = अणु
	.min_low_ns = 4700 + I2C_STANDARD_MODE_BUFFER,
	.min_su_sta_ns = 4700 + I2C_STANDARD_MODE_BUFFER,
	.max_hd_dat_ns = 3450 - I2C_STANDARD_MODE_BUFFER,
	.min_su_dat_ns = 250 + I2C_STANDARD_MODE_BUFFER,
पूर्ण;

अटल स्थिर काष्ठा i2c_spec_values fast_mode_spec = अणु
	.min_low_ns = 1300 + I2C_FAST_MODE_BUFFER,
	.min_su_sta_ns = 600 + I2C_FAST_MODE_BUFFER,
	.max_hd_dat_ns = 900 - I2C_FAST_MODE_BUFFER,
	.min_su_dat_ns = 100 + I2C_FAST_MODE_BUFFER,
पूर्ण;

अटल स्थिर काष्ठा i2c_spec_values fast_mode_plus_spec = अणु
	.min_low_ns = 500 + I2C_FAST_MODE_PLUS_BUFFER,
	.min_su_sta_ns = 260 + I2C_FAST_MODE_PLUS_BUFFER,
	.max_hd_dat_ns = 400 - I2C_FAST_MODE_PLUS_BUFFER,
	.min_su_dat_ns = 50 + I2C_FAST_MODE_PLUS_BUFFER,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks mt6577_i2c_quirks = अणु
	.flags = I2C_AQ_COMB_WRITE_THEN_READ,
	.max_num_msgs = 1,
	.max_ग_लिखो_len = 255,
	.max_पढ़ो_len = 255,
	.max_comb_1st_msg_len = 255,
	.max_comb_2nd_msg_len = 31,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks mt7622_i2c_quirks = अणु
	.max_num_msgs = 255,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks mt8183_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
पूर्ण;

अटल स्थिर काष्ठा mtk_i2c_compatible mt2712_compat = अणु
	.regs = mt_i2c_regs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.स्वतः_restart = 1,
	.aux_len_reg = 1,
	.timing_adjust = 1,
	.dma_sync = 0,
	.ltiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_support = 33,
पूर्ण;

अटल स्थिर काष्ठा mtk_i2c_compatible mt6577_compat = अणु
	.quirks = &mt6577_i2c_quirks,
	.regs = mt_i2c_regs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.स्वतः_restart = 0,
	.aux_len_reg = 0,
	.timing_adjust = 0,
	.dma_sync = 0,
	.ltiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_support = 32,
पूर्ण;

अटल स्थिर काष्ठा mtk_i2c_compatible mt6589_compat = अणु
	.quirks = &mt6577_i2c_quirks,
	.regs = mt_i2c_regs_v1,
	.pmic_i2c = 1,
	.dcm = 0,
	.स्वतः_restart = 0,
	.aux_len_reg = 0,
	.timing_adjust = 0,
	.dma_sync = 0,
	.ltiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_support = 32,
पूर्ण;

अटल स्थिर काष्ठा mtk_i2c_compatible mt7622_compat = अणु
	.quirks = &mt7622_i2c_quirks,
	.regs = mt_i2c_regs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.स्वतः_restart = 1,
	.aux_len_reg = 1,
	.timing_adjust = 0,
	.dma_sync = 0,
	.ltiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_support = 32,
पूर्ण;

अटल स्थिर काष्ठा mtk_i2c_compatible mt8173_compat = अणु
	.regs = mt_i2c_regs_v1,
	.pmic_i2c = 0,
	.dcm = 1,
	.स्वतः_restart = 1,
	.aux_len_reg = 1,
	.timing_adjust = 0,
	.dma_sync = 0,
	.ltiming_adjust = 0,
	.apdma_sync = 0,
	.max_dma_support = 33,
पूर्ण;

अटल स्थिर काष्ठा mtk_i2c_compatible mt8183_compat = अणु
	.quirks = &mt8183_i2c_quirks,
	.regs = mt_i2c_regs_v2,
	.pmic_i2c = 0,
	.dcm = 0,
	.स्वतः_restart = 1,
	.aux_len_reg = 1,
	.timing_adjust = 1,
	.dma_sync = 1,
	.ltiming_adjust = 1,
	.apdma_sync = 0,
	.max_dma_support = 33,
पूर्ण;

अटल स्थिर काष्ठा mtk_i2c_compatible mt8192_compat = अणु
	.quirks = &mt8183_i2c_quirks,
	.regs = mt_i2c_regs_v2,
	.pmic_i2c = 0,
	.dcm = 0,
	.स्वतः_restart = 1,
	.aux_len_reg = 1,
	.timing_adjust = 1,
	.dma_sync = 1,
	.ltiming_adjust = 1,
	.apdma_sync = 1,
	.max_dma_support = 36,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_i2c_of_match[] = अणु
	अणु .compatible = "mediatek,mt2712-i2c", .data = &mt2712_compat पूर्ण,
	अणु .compatible = "mediatek,mt6577-i2c", .data = &mt6577_compat पूर्ण,
	अणु .compatible = "mediatek,mt6589-i2c", .data = &mt6589_compat पूर्ण,
	अणु .compatible = "mediatek,mt7622-i2c", .data = &mt7622_compat पूर्ण,
	अणु .compatible = "mediatek,mt8173-i2c", .data = &mt8173_compat पूर्ण,
	अणु .compatible = "mediatek,mt8183-i2c", .data = &mt8183_compat पूर्ण,
	अणु .compatible = "mediatek,mt8192-i2c", .data = &mt8192_compat पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_i2c_of_match);

अटल u16 mtk_i2c_पढ़ोw(काष्ठा mtk_i2c *i2c, क्रमागत I2C_REGS_OFFSET reg)
अणु
	वापस पढ़ोw(i2c->base + i2c->dev_comp->regs[reg]);
पूर्ण

अटल व्योम mtk_i2c_ग_लिखोw(काष्ठा mtk_i2c *i2c, u16 val,
			   क्रमागत I2C_REGS_OFFSET reg)
अणु
	ग_लिखोw(val, i2c->base + i2c->dev_comp->regs[reg]);
पूर्ण

अटल पूर्णांक mtk_i2c_घड़ी_enable(काष्ठा mtk_i2c *i2c)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(i2c->clk_dma);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(i2c->clk_मुख्य);
	अगर (ret)
		जाओ err_मुख्य;

	अगर (i2c->have_pmic) अणु
		ret = clk_prepare_enable(i2c->clk_pmic);
		अगर (ret)
			जाओ err_pmic;
	पूर्ण

	अगर (i2c->clk_arb) अणु
		ret = clk_prepare_enable(i2c->clk_arb);
		अगर (ret)
			जाओ err_arb;
	पूर्ण

	वापस 0;

err_arb:
	अगर (i2c->have_pmic)
		clk_disable_unprepare(i2c->clk_pmic);
err_pmic:
	clk_disable_unprepare(i2c->clk_मुख्य);
err_मुख्य:
	clk_disable_unprepare(i2c->clk_dma);

	वापस ret;
पूर्ण

अटल व्योम mtk_i2c_घड़ी_disable(काष्ठा mtk_i2c *i2c)
अणु
	अगर (i2c->clk_arb)
		clk_disable_unprepare(i2c->clk_arb);

	अगर (i2c->have_pmic)
		clk_disable_unprepare(i2c->clk_pmic);

	clk_disable_unprepare(i2c->clk_मुख्य);
	clk_disable_unprepare(i2c->clk_dma);
पूर्ण

अटल व्योम mtk_i2c_init_hw(काष्ठा mtk_i2c *i2c)
अणु
	u16 control_reg;
	u16 पूर्णांकr_stat_reg;

	mtk_i2c_ग_लिखोw(i2c, I2C_CHN_CLR_FLAG, OFFSET_START);
	पूर्णांकr_stat_reg = mtk_i2c_पढ़ोw(i2c, OFFSET_INTR_STAT);
	mtk_i2c_ग_लिखोw(i2c, पूर्णांकr_stat_reg, OFFSET_INTR_STAT);

	अगर (i2c->dev_comp->apdma_sync) अणु
		ग_लिखोl(I2C_DMA_WARM_RST, i2c->pdmabase + OFFSET_RST);
		udelay(10);
		ग_लिखोl(I2C_DMA_CLR_FLAG, i2c->pdmabase + OFFSET_RST);
		udelay(10);
		ग_लिखोl(I2C_DMA_HANDSHAKE_RST | I2C_DMA_HARD_RST,
		       i2c->pdmabase + OFFSET_RST);
		mtk_i2c_ग_लिखोw(i2c, I2C_HANDSHAKE_RST | I2C_SOFT_RST,
			       OFFSET_SOFTRESET);
		udelay(10);
		ग_लिखोl(I2C_DMA_CLR_FLAG, i2c->pdmabase + OFFSET_RST);
		mtk_i2c_ग_लिखोw(i2c, I2C_CHN_CLR_FLAG, OFFSET_SOFTRESET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(I2C_DMA_HARD_RST, i2c->pdmabase + OFFSET_RST);
		udelay(50);
		ग_लिखोl(I2C_DMA_CLR_FLAG, i2c->pdmabase + OFFSET_RST);
		mtk_i2c_ग_लिखोw(i2c, I2C_SOFT_RST, OFFSET_SOFTRESET);
	पूर्ण

	/* Set ioconfig */
	अगर (i2c->use_push_pull)
		mtk_i2c_ग_लिखोw(i2c, I2C_IO_CONFIG_PUSH_PULL, OFFSET_IO_CONFIG);
	अन्यथा
		mtk_i2c_ग_लिखोw(i2c, I2C_IO_CONFIG_OPEN_DRAIN, OFFSET_IO_CONFIG);

	अगर (i2c->dev_comp->dcm)
		mtk_i2c_ग_लिखोw(i2c, I2C_DCM_DISABLE, OFFSET_DCM_EN);

	mtk_i2c_ग_लिखोw(i2c, i2c->timing_reg, OFFSET_TIMING);
	mtk_i2c_ग_लिखोw(i2c, i2c->high_speed_reg, OFFSET_HS);
	अगर (i2c->dev_comp->ltiming_adjust)
		mtk_i2c_ग_लिखोw(i2c, i2c->ltiming_reg, OFFSET_LTIMING);

	अगर (i2c->dev_comp->timing_adjust) अणु
		mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.ext, OFFSET_EXT_CONF);
		mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.पूर्णांकer_clk_भाग,
			       OFFSET_CLOCK_DIV);
		mtk_i2c_ग_लिखोw(i2c, I2C_SCL_MIS_COMP_VALUE,
			       OFFSET_SCL_MIS_COMP_POINT);
		mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.sda_timing,
			       OFFSET_SDA_TIMING);

		अगर (i2c->dev_comp->ltiming_adjust) अणु
			mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.htiming,
				       OFFSET_TIMING);
			mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.hs, OFFSET_HS);
			mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.ltiming,
				       OFFSET_LTIMING);
		पूर्ण अन्यथा अणु
			mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.scl_hl_ratio,
				       OFFSET_SCL_HIGH_LOW_RATIO);
			mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.hs_scl_hl_ratio,
				       OFFSET_HS_SCL_HIGH_LOW_RATIO);
			mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.sta_stop,
				       OFFSET_STA_STO_AC_TIMING);
			mtk_i2c_ग_लिखोw(i2c, i2c->ac_timing.hs_sta_stop,
				       OFFSET_HS_STA_STO_AC_TIMING);
		पूर्ण
	पूर्ण

	/* If use i2c pin from PMIC mt6397 side, need set PATH_सूची first */
	अगर (i2c->have_pmic)
		mtk_i2c_ग_लिखोw(i2c, I2C_CONTROL_WRAPPER, OFFSET_PATH_सूची);

	control_reg = I2C_CONTROL_ACKERR_DET_EN |
		      I2C_CONTROL_CLK_EXT_EN | I2C_CONTROL_DMA_EN;
	अगर (i2c->dev_comp->dma_sync)
		control_reg |= I2C_CONTROL_DMAACK_EN | I2C_CONTROL_ASYNC_MODE;

	mtk_i2c_ग_लिखोw(i2c, control_reg, OFFSET_CONTROL);
	mtk_i2c_ग_लिखोw(i2c, I2C_DELAY_LEN, OFFSET_DELAY_LEN);
पूर्ण

अटल स्थिर काष्ठा i2c_spec_values *mtk_i2c_get_spec(अचिन्हित पूर्णांक speed)
अणु
	अगर (speed <= I2C_MAX_STANDARD_MODE_FREQ)
		वापस &standard_mode_spec;
	अन्यथा अगर (speed <= I2C_MAX_FAST_MODE_FREQ)
		वापस &fast_mode_spec;
	अन्यथा
		वापस &fast_mode_plus_spec;
पूर्ण

अटल पूर्णांक mtk_i2c_max_step_cnt(अचिन्हित पूर्णांक target_speed)
अणु
	अगर (target_speed > I2C_MAX_FAST_MODE_PLUS_FREQ)
		वापस MAX_HS_STEP_CNT_DIV;
	अन्यथा
		वापस MAX_STEP_CNT_DIV;
पूर्ण

/*
 * Check and Calculate i2c ac-timing
 *
 * Hardware design:
 * sample_ns = (1000000000 * (sample_cnt + 1)) / clk_src
 * xxx_cnt_भाग =  spec->min_xxx_ns / sample_ns
 *
 * Sample_ns is rounded करोwn क्रम xxx_cnt_भाग would be greater
 * than the smallest spec.
 * The sda_timing is chosen as the middle value between
 * the largest and smallest.
 */
अटल पूर्णांक mtk_i2c_check_ac_timing(काष्ठा mtk_i2c *i2c,
				   अचिन्हित पूर्णांक clk_src,
				   अचिन्हित पूर्णांक check_speed,
				   अचिन्हित पूर्णांक step_cnt,
				   अचिन्हित पूर्णांक sample_cnt)
अणु
	स्थिर काष्ठा i2c_spec_values *spec;
	अचिन्हित पूर्णांक su_sta_cnt, low_cnt, high_cnt, max_step_cnt;
	अचिन्हित पूर्णांक sda_max, sda_min, clk_ns, max_sta_cnt = 0x3f;
	अचिन्हित पूर्णांक sample_ns = भाग_u64(1000000000ULL * (sample_cnt + 1),
					 clk_src);

	अगर (!i2c->dev_comp->timing_adjust)
		वापस 0;

	अगर (i2c->dev_comp->ltiming_adjust)
		max_sta_cnt = 0x100;

	spec = mtk_i2c_get_spec(check_speed);

	अगर (i2c->dev_comp->ltiming_adjust)
		clk_ns = 1000000000 / clk_src;
	अन्यथा
		clk_ns = sample_ns / 2;

	su_sta_cnt = DIV_ROUND_UP(spec->min_su_sta_ns +
				  i2c->timing_info.scl_पूर्णांक_delay_ns, clk_ns);
	अगर (su_sta_cnt > max_sta_cnt)
		वापस -1;

	low_cnt = DIV_ROUND_UP(spec->min_low_ns, sample_ns);
	max_step_cnt = mtk_i2c_max_step_cnt(check_speed);
	अगर ((2 * step_cnt) > low_cnt && low_cnt < max_step_cnt) अणु
		अगर (low_cnt > step_cnt) अणु
			high_cnt = 2 * step_cnt - low_cnt;
		पूर्ण अन्यथा अणु
			high_cnt = step_cnt;
			low_cnt = step_cnt;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -2;
	पूर्ण

	sda_max = spec->max_hd_dat_ns / sample_ns;
	अगर (sda_max > low_cnt)
		sda_max = 0;

	sda_min = DIV_ROUND_UP(spec->min_su_dat_ns, sample_ns);
	अगर (sda_min < low_cnt)
		sda_min = 0;

	अगर (sda_min > sda_max)
		वापस -3;

	अगर (check_speed > I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
		अगर (i2c->dev_comp->ltiming_adjust) अणु
			i2c->ac_timing.hs = I2C_TIME_DEFAULT_VALUE |
				(sample_cnt << 12) | (high_cnt << 8);
			i2c->ac_timing.ltiming &= ~GENMASK(15, 9);
			i2c->ac_timing.ltiming |= (sample_cnt << 12) |
				(low_cnt << 9);
			i2c->ac_timing.ext &= ~GENMASK(7, 1);
			i2c->ac_timing.ext |= (su_sta_cnt << 1) | (1 << 0);
		पूर्ण अन्यथा अणु
			i2c->ac_timing.hs_scl_hl_ratio = (1 << 12) |
				(high_cnt << 6) | low_cnt;
			i2c->ac_timing.hs_sta_stop = (su_sta_cnt << 8) |
				su_sta_cnt;
		पूर्ण
		i2c->ac_timing.sda_timing &= ~GENMASK(11, 6);
		i2c->ac_timing.sda_timing |= (1 << 12) |
			((sda_max + sda_min) / 2) << 6;
	पूर्ण अन्यथा अणु
		अगर (i2c->dev_comp->ltiming_adjust) अणु
			i2c->ac_timing.htiming = (sample_cnt << 8) | (high_cnt);
			i2c->ac_timing.ltiming = (sample_cnt << 6) | (low_cnt);
			i2c->ac_timing.ext = (su_sta_cnt << 8) | (1 << 0);
		पूर्ण अन्यथा अणु
			i2c->ac_timing.scl_hl_ratio = (1 << 12) |
				(high_cnt << 6) | low_cnt;
			i2c->ac_timing.sta_stop = (su_sta_cnt << 8) |
				su_sta_cnt;
		पूर्ण

		i2c->ac_timing.sda_timing = (1 << 12) |
			(sda_max + sda_min) / 2;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Calculate i2c port speed
 *
 * Hardware design:
 * i2c_bus_freq = parent_clk / (घड़ी_भाग * 2 * sample_cnt * step_cnt)
 * घड़ी_भाग: fixed in hardware, but may be various in dअगरferent SoCs
 *
 * The calculation want to pick the highest bus frequency that is still
 * less than or equal to i2c->speed_hz. The calculation try to get
 * sample_cnt and step_cn
 */
अटल पूर्णांक mtk_i2c_calculate_speed(काष्ठा mtk_i2c *i2c, अचिन्हित पूर्णांक clk_src,
				   अचिन्हित पूर्णांक target_speed,
				   अचिन्हित पूर्णांक *timing_step_cnt,
				   अचिन्हित पूर्णांक *timing_sample_cnt)
अणु
	अचिन्हित पूर्णांक step_cnt;
	अचिन्हित पूर्णांक sample_cnt;
	अचिन्हित पूर्णांक max_step_cnt;
	अचिन्हित पूर्णांक base_sample_cnt = MAX_SAMPLE_CNT_DIV;
	अचिन्हित पूर्णांक base_step_cnt;
	अचिन्हित पूर्णांक opt_भाग;
	अचिन्हित पूर्णांक best_mul;
	अचिन्हित पूर्णांक cnt_mul;
	पूर्णांक ret = -EINVAL;

	अगर (target_speed > I2C_MAX_HIGH_SPEED_MODE_FREQ)
		target_speed = I2C_MAX_HIGH_SPEED_MODE_FREQ;

	max_step_cnt = mtk_i2c_max_step_cnt(target_speed);
	base_step_cnt = max_step_cnt;
	/* Find the best combination */
	opt_भाग = DIV_ROUND_UP(clk_src >> 1, target_speed);
	best_mul = MAX_SAMPLE_CNT_DIV * max_step_cnt;

	/* Search क्रम the best pair (sample_cnt, step_cnt) with
	 * 0 < sample_cnt < MAX_SAMPLE_CNT_DIV
	 * 0 < step_cnt < max_step_cnt
	 * sample_cnt * step_cnt >= opt_भाग
	 * optimizing क्रम sample_cnt * step_cnt being minimal
	 */
	क्रम (sample_cnt = 1; sample_cnt <= MAX_SAMPLE_CNT_DIV; sample_cnt++) अणु
		step_cnt = DIV_ROUND_UP(opt_भाग, sample_cnt);
		cnt_mul = step_cnt * sample_cnt;
		अगर (step_cnt > max_step_cnt)
			जारी;

		अगर (cnt_mul < best_mul) अणु
			ret = mtk_i2c_check_ac_timing(i2c, clk_src,
				target_speed, step_cnt - 1, sample_cnt - 1);
			अगर (ret)
				जारी;

			best_mul = cnt_mul;
			base_sample_cnt = sample_cnt;
			base_step_cnt = step_cnt;
			अगर (best_mul == opt_भाग)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस -EINVAL;

	sample_cnt = base_sample_cnt;
	step_cnt = base_step_cnt;

	अगर ((clk_src / (2 * sample_cnt * step_cnt)) > target_speed) अणु
		/* In this हाल, hardware can't support such
		 * low i2c_bus_freq
		 */
		dev_dbg(i2c->dev, "Unsupported speed (%uhz)\n",	target_speed);
		वापस -EINVAL;
	पूर्ण

	*timing_step_cnt = step_cnt - 1;
	*timing_sample_cnt = sample_cnt - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_i2c_set_speed(काष्ठा mtk_i2c *i2c, अचिन्हित पूर्णांक parent_clk)
अणु
	अचिन्हित पूर्णांक clk_src;
	अचिन्हित पूर्णांक step_cnt;
	अचिन्हित पूर्णांक sample_cnt;
	अचिन्हित पूर्णांक l_step_cnt;
	अचिन्हित पूर्णांक l_sample_cnt;
	अचिन्हित पूर्णांक target_speed;
	अचिन्हित पूर्णांक clk_भाग;
	अचिन्हित पूर्णांक max_clk_भाग;
	पूर्णांक ret;

	target_speed = i2c->speed_hz;
	parent_clk /= i2c->clk_src_भाग;

	अगर (i2c->dev_comp->timing_adjust)
		max_clk_भाग = MAX_CLOCK_DIV;
	अन्यथा
		max_clk_भाग = 1;

	क्रम (clk_भाग = 1; clk_भाग <= max_clk_भाग; clk_भाग++) अणु
		clk_src = parent_clk / clk_भाग;

		अगर (target_speed > I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
			/* Set master code speed रेजिस्टर */
			ret = mtk_i2c_calculate_speed(i2c, clk_src,
						      I2C_MAX_FAST_MODE_FREQ,
						      &l_step_cnt,
						      &l_sample_cnt);
			अगर (ret < 0)
				जारी;

			i2c->timing_reg = (l_sample_cnt << 8) | l_step_cnt;

			/* Set the high speed mode रेजिस्टर */
			ret = mtk_i2c_calculate_speed(i2c, clk_src,
						      target_speed, &step_cnt,
						      &sample_cnt);
			अगर (ret < 0)
				जारी;

			i2c->high_speed_reg = I2C_TIME_DEFAULT_VALUE |
					(sample_cnt << 12) | (step_cnt << 8);

			अगर (i2c->dev_comp->ltiming_adjust)
				i2c->ltiming_reg =
					(l_sample_cnt << 6) | l_step_cnt |
					(sample_cnt << 12) | (step_cnt << 9);
		पूर्ण अन्यथा अणु
			ret = mtk_i2c_calculate_speed(i2c, clk_src,
						      target_speed, &l_step_cnt,
						      &l_sample_cnt);
			अगर (ret < 0)
				जारी;

			i2c->timing_reg = (l_sample_cnt << 8) | l_step_cnt;

			/* Disable the high speed transaction */
			i2c->high_speed_reg = I2C_TIME_CLR_VALUE;

			अगर (i2c->dev_comp->ltiming_adjust)
				i2c->ltiming_reg =
					(l_sample_cnt << 6) | l_step_cnt;
		पूर्ण

		अवरोध;
	पूर्ण

	i2c->ac_timing.पूर्णांकer_clk_भाग = clk_भाग - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_i2c_करो_transfer(काष्ठा mtk_i2c *i2c, काष्ठा i2c_msg *msgs,
			       पूर्णांक num, पूर्णांक left_num)
अणु
	u16 addr_reg;
	u16 start_reg;
	u16 control_reg;
	u16 restart_flag = 0;
	u16 dma_sync = 0;
	u32 reg_4g_mode;
	u8 *dma_rd_buf = शून्य;
	u8 *dma_wr_buf = शून्य;
	dma_addr_t rpaddr = 0;
	dma_addr_t wpaddr = 0;
	पूर्णांक ret;

	i2c->irq_stat = 0;

	अगर (i2c->स्वतः_restart)
		restart_flag = I2C_RS_TRANSFER;

	reinit_completion(&i2c->msg_complete);

	control_reg = mtk_i2c_पढ़ोw(i2c, OFFSET_CONTROL) &
			~(I2C_CONTROL_सूची_CHANGE | I2C_CONTROL_RS);
	अगर ((i2c->speed_hz > I2C_MAX_FAST_MODE_PLUS_FREQ) || (left_num >= 1))
		control_reg |= I2C_CONTROL_RS;

	अगर (i2c->op == I2C_MASTER_WRRD)
		control_reg |= I2C_CONTROL_सूची_CHANGE | I2C_CONTROL_RS;

	mtk_i2c_ग_लिखोw(i2c, control_reg, OFFSET_CONTROL);

	addr_reg = i2c_8bit_addr_from_msg(msgs);
	mtk_i2c_ग_लिखोw(i2c, addr_reg, OFFSET_SLAVE_ADDR);

	/* Clear पूर्णांकerrupt status */
	mtk_i2c_ग_लिखोw(i2c, restart_flag | I2C_HS_NACKERR | I2C_ACKERR |
			    I2C_ARB_LOST | I2C_TRANSAC_COMP, OFFSET_INTR_STAT);

	mtk_i2c_ग_लिखोw(i2c, I2C_FIFO_ADDR_CLR, OFFSET_FIFO_ADDR_CLR);

	/* Enable पूर्णांकerrupt */
	mtk_i2c_ग_लिखोw(i2c, restart_flag | I2C_HS_NACKERR | I2C_ACKERR |
			    I2C_ARB_LOST | I2C_TRANSAC_COMP, OFFSET_INTR_MASK);

	/* Set transfer and transaction len */
	अगर (i2c->op == I2C_MASTER_WRRD) अणु
		अगर (i2c->dev_comp->aux_len_reg) अणु
			mtk_i2c_ग_लिखोw(i2c, msgs->len, OFFSET_TRANSFER_LEN);
			mtk_i2c_ग_लिखोw(i2c, (msgs + 1)->len,
					    OFFSET_TRANSFER_LEN_AUX);
		पूर्ण अन्यथा अणु
			mtk_i2c_ग_लिखोw(i2c, msgs->len | ((msgs + 1)->len) << 8,
					    OFFSET_TRANSFER_LEN);
		पूर्ण
		mtk_i2c_ग_लिखोw(i2c, I2C_WRRD_TRANAC_VALUE, OFFSET_TRANSAC_LEN);
	पूर्ण अन्यथा अणु
		mtk_i2c_ग_लिखोw(i2c, msgs->len, OFFSET_TRANSFER_LEN);
		mtk_i2c_ग_लिखोw(i2c, num, OFFSET_TRANSAC_LEN);
	पूर्ण

	अगर (i2c->dev_comp->apdma_sync) अणु
		dma_sync = I2C_DMA_SKIP_CONFIG | I2C_DMA_ASYNC_MODE;
		अगर (i2c->op == I2C_MASTER_WRRD)
			dma_sync |= I2C_DMA_सूची_CHANGE;
	पूर्ण

	/* Prepare buffer data to start transfer */
	अगर (i2c->op == I2C_MASTER_RD) अणु
		ग_लिखोl(I2C_DMA_INT_FLAG_NONE, i2c->pdmabase + OFFSET_INT_FLAG);
		ग_लिखोl(I2C_DMA_CON_RX | dma_sync, i2c->pdmabase + OFFSET_CON);

		dma_rd_buf = i2c_get_dma_safe_msg_buf(msgs, 1);
		अगर (!dma_rd_buf)
			वापस -ENOMEM;

		rpaddr = dma_map_single(i2c->dev, dma_rd_buf,
					msgs->len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(i2c->dev, rpaddr)) अणु
			i2c_put_dma_safe_msg_buf(dma_rd_buf, msgs, false);

			वापस -ENOMEM;
		पूर्ण

		अगर (i2c->dev_comp->max_dma_support > 32) अणु
			reg_4g_mode = upper_32_bits(rpaddr);
			ग_लिखोl(reg_4g_mode, i2c->pdmabase + OFFSET_RX_4G_MODE);
		पूर्ण

		ग_लिखोl((u32)rpaddr, i2c->pdmabase + OFFSET_RX_MEM_ADDR);
		ग_लिखोl(msgs->len, i2c->pdmabase + OFFSET_RX_LEN);
	पूर्ण अन्यथा अगर (i2c->op == I2C_MASTER_WR) अणु
		ग_लिखोl(I2C_DMA_INT_FLAG_NONE, i2c->pdmabase + OFFSET_INT_FLAG);
		ग_लिखोl(I2C_DMA_CON_TX | dma_sync, i2c->pdmabase + OFFSET_CON);

		dma_wr_buf = i2c_get_dma_safe_msg_buf(msgs, 1);
		अगर (!dma_wr_buf)
			वापस -ENOMEM;

		wpaddr = dma_map_single(i2c->dev, dma_wr_buf,
					msgs->len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(i2c->dev, wpaddr)) अणु
			i2c_put_dma_safe_msg_buf(dma_wr_buf, msgs, false);

			वापस -ENOMEM;
		पूर्ण

		अगर (i2c->dev_comp->max_dma_support > 32) अणु
			reg_4g_mode = upper_32_bits(wpaddr);
			ग_लिखोl(reg_4g_mode, i2c->pdmabase + OFFSET_TX_4G_MODE);
		पूर्ण

		ग_लिखोl((u32)wpaddr, i2c->pdmabase + OFFSET_TX_MEM_ADDR);
		ग_लिखोl(msgs->len, i2c->pdmabase + OFFSET_TX_LEN);
	पूर्ण अन्यथा अणु
		ग_लिखोl(I2C_DMA_CLR_FLAG, i2c->pdmabase + OFFSET_INT_FLAG);
		ग_लिखोl(I2C_DMA_CLR_FLAG | dma_sync, i2c->pdmabase + OFFSET_CON);

		dma_wr_buf = i2c_get_dma_safe_msg_buf(msgs, 1);
		अगर (!dma_wr_buf)
			वापस -ENOMEM;

		wpaddr = dma_map_single(i2c->dev, dma_wr_buf,
					msgs->len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(i2c->dev, wpaddr)) अणु
			i2c_put_dma_safe_msg_buf(dma_wr_buf, msgs, false);

			वापस -ENOMEM;
		पूर्ण

		dma_rd_buf = i2c_get_dma_safe_msg_buf((msgs + 1), 1);
		अगर (!dma_rd_buf) अणु
			dma_unmap_single(i2c->dev, wpaddr,
					 msgs->len, DMA_TO_DEVICE);

			i2c_put_dma_safe_msg_buf(dma_wr_buf, msgs, false);

			वापस -ENOMEM;
		पूर्ण

		rpaddr = dma_map_single(i2c->dev, dma_rd_buf,
					(msgs + 1)->len,
					DMA_FROM_DEVICE);
		अगर (dma_mapping_error(i2c->dev, rpaddr)) अणु
			dma_unmap_single(i2c->dev, wpaddr,
					 msgs->len, DMA_TO_DEVICE);

			i2c_put_dma_safe_msg_buf(dma_wr_buf, msgs, false);
			i2c_put_dma_safe_msg_buf(dma_rd_buf, (msgs + 1), false);

			वापस -ENOMEM;
		पूर्ण

		अगर (i2c->dev_comp->max_dma_support > 32) अणु
			reg_4g_mode = upper_32_bits(wpaddr);
			ग_लिखोl(reg_4g_mode, i2c->pdmabase + OFFSET_TX_4G_MODE);

			reg_4g_mode = upper_32_bits(rpaddr);
			ग_लिखोl(reg_4g_mode, i2c->pdmabase + OFFSET_RX_4G_MODE);
		पूर्ण

		ग_लिखोl((u32)wpaddr, i2c->pdmabase + OFFSET_TX_MEM_ADDR);
		ग_लिखोl((u32)rpaddr, i2c->pdmabase + OFFSET_RX_MEM_ADDR);
		ग_लिखोl(msgs->len, i2c->pdmabase + OFFSET_TX_LEN);
		ग_लिखोl((msgs + 1)->len, i2c->pdmabase + OFFSET_RX_LEN);
	पूर्ण

	ग_लिखोl(I2C_DMA_START_EN, i2c->pdmabase + OFFSET_EN);

	अगर (!i2c->स्वतः_restart) अणु
		start_reg = I2C_TRANSAC_START;
	पूर्ण अन्यथा अणु
		start_reg = I2C_TRANSAC_START | I2C_RS_MUL_TRIG;
		अगर (left_num >= 1)
			start_reg |= I2C_RS_MUL_CNFG;
	पूर्ण
	mtk_i2c_ग_लिखोw(i2c, start_reg, OFFSET_START);

	ret = रुको_क्रम_completion_समयout(&i2c->msg_complete,
					  i2c->adap.समयout);

	/* Clear पूर्णांकerrupt mask */
	mtk_i2c_ग_लिखोw(i2c, ~(restart_flag | I2C_HS_NACKERR | I2C_ACKERR |
			    I2C_ARB_LOST | I2C_TRANSAC_COMP), OFFSET_INTR_MASK);

	अगर (i2c->op == I2C_MASTER_WR) अणु
		dma_unmap_single(i2c->dev, wpaddr,
				 msgs->len, DMA_TO_DEVICE);

		i2c_put_dma_safe_msg_buf(dma_wr_buf, msgs, true);
	पूर्ण अन्यथा अगर (i2c->op == I2C_MASTER_RD) अणु
		dma_unmap_single(i2c->dev, rpaddr,
				 msgs->len, DMA_FROM_DEVICE);

		i2c_put_dma_safe_msg_buf(dma_rd_buf, msgs, true);
	पूर्ण अन्यथा अणु
		dma_unmap_single(i2c->dev, wpaddr, msgs->len,
				 DMA_TO_DEVICE);
		dma_unmap_single(i2c->dev, rpaddr, (msgs + 1)->len,
				 DMA_FROM_DEVICE);

		i2c_put_dma_safe_msg_buf(dma_wr_buf, msgs, true);
		i2c_put_dma_safe_msg_buf(dma_rd_buf, (msgs + 1), true);
	पूर्ण

	अगर (ret == 0) अणु
		dev_dbg(i2c->dev, "addr: %x, transfer timeout\n", msgs->addr);
		mtk_i2c_init_hw(i2c);
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (i2c->irq_stat & (I2C_HS_NACKERR | I2C_ACKERR)) अणु
		dev_dbg(i2c->dev, "addr: %x, transfer ACK error\n", msgs->addr);
		mtk_i2c_init_hw(i2c);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_i2c_transfer(काष्ठा i2c_adapter *adap,
			    काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	पूर्णांक ret;
	पूर्णांक left_num = num;
	काष्ठा mtk_i2c *i2c = i2c_get_adapdata(adap);

	ret = mtk_i2c_घड़ी_enable(i2c);
	अगर (ret)
		वापस ret;

	i2c->स्वतः_restart = i2c->dev_comp->स्वतः_restart;

	/* checking अगर we can skip restart and optimize using WRRD mode */
	अगर (i2c->स्वतः_restart && num == 2) अणु
		अगर (!(msgs[0].flags & I2C_M_RD) && (msgs[1].flags & I2C_M_RD) &&
		    msgs[0].addr == msgs[1].addr) अणु
			i2c->स्वतः_restart = 0;
		पूर्ण
	पूर्ण

	अगर (i2c->स्वतः_restart && num >= 2 &&
		i2c->speed_hz > I2C_MAX_FAST_MODE_PLUS_FREQ)
		/* ignore the first restart irq after the master code,
		 * otherwise the first transfer will be discarded.
		 */
		i2c->ignore_restart_irq = true;
	अन्यथा
		i2c->ignore_restart_irq = false;

	जबतक (left_num--) अणु
		अगर (!msgs->buf) अणु
			dev_dbg(i2c->dev, "data buffer is NULL.\n");
			ret = -EINVAL;
			जाओ err_निकास;
		पूर्ण

		अगर (msgs->flags & I2C_M_RD)
			i2c->op = I2C_MASTER_RD;
		अन्यथा
			i2c->op = I2C_MASTER_WR;

		अगर (!i2c->स्वतः_restart) अणु
			अगर (num > 1) अणु
				/* combined two messages पूर्णांकo one transaction */
				i2c->op = I2C_MASTER_WRRD;
				left_num--;
			पूर्ण
		पूर्ण

		/* always use DMA mode. */
		ret = mtk_i2c_करो_transfer(i2c, msgs, num, left_num);
		अगर (ret < 0)
			जाओ err_निकास;

		msgs++;
	पूर्ण
	/* the वापस value is number of executed messages */
	ret = num;

err_निकास:
	mtk_i2c_घड़ी_disable(i2c);
	वापस ret;
पूर्ण

अटल irqवापस_t mtk_i2c_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा mtk_i2c *i2c = dev_id;
	u16 restart_flag = 0;
	u16 पूर्णांकr_stat;

	अगर (i2c->स्वतः_restart)
		restart_flag = I2C_RS_TRANSFER;

	पूर्णांकr_stat = mtk_i2c_पढ़ोw(i2c, OFFSET_INTR_STAT);
	mtk_i2c_ग_लिखोw(i2c, पूर्णांकr_stat, OFFSET_INTR_STAT);

	/*
	 * when occurs ack error, i2c controller generate two पूर्णांकerrupts
	 * first is the ack error पूर्णांकerrupt, then the complete पूर्णांकerrupt
	 * i2c->irq_stat need keep the two पूर्णांकerrupt value.
	 */
	i2c->irq_stat |= पूर्णांकr_stat;

	अगर (i2c->ignore_restart_irq && (i2c->irq_stat & restart_flag)) अणु
		i2c->ignore_restart_irq = false;
		i2c->irq_stat = 0;
		mtk_i2c_ग_लिखोw(i2c, I2C_RS_MUL_CNFG | I2C_RS_MUL_TRIG |
				    I2C_TRANSAC_START, OFFSET_START);
	पूर्ण अन्यथा अणु
		अगर (i2c->irq_stat & (I2C_TRANSAC_COMP | restart_flag))
			complete(&i2c->msg_complete);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 mtk_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	अगर (i2c_check_quirks(adap, I2C_AQ_NO_ZERO_LEN))
		वापस I2C_FUNC_I2C |
			(I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);
	अन्यथा
		वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mtk_i2c_algorithm = अणु
	.master_xfer = mtk_i2c_transfer,
	.functionality = mtk_i2c_functionality,
पूर्ण;

अटल पूर्णांक mtk_i2c_parse_dt(काष्ठा device_node *np, काष्ठा mtk_i2c *i2c)
अणु
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "clock-frequency", &i2c->speed_hz);
	अगर (ret < 0)
		i2c->speed_hz = I2C_MAX_STANDARD_MODE_FREQ;

	ret = of_property_पढ़ो_u32(np, "clock-div", &i2c->clk_src_भाग);
	अगर (ret < 0)
		वापस ret;

	अगर (i2c->clk_src_भाग == 0)
		वापस -EINVAL;

	i2c->have_pmic = of_property_पढ़ो_bool(np, "mediatek,have-pmic");
	i2c->use_push_pull =
		of_property_पढ़ो_bool(np, "mediatek,use-push-pull");

	i2c_parse_fw_timings(i2c->dev, &i2c->timing_info, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा mtk_i2c *i2c;
	काष्ठा clk *clk;
	काष्ठा resource *res;
	पूर्णांक irq;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	i2c->pdmabase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2c->pdmabase))
		वापस PTR_ERR(i2c->pdmabase);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	init_completion(&i2c->msg_complete);

	i2c->dev_comp = of_device_get_match_data(&pdev->dev);
	i2c->adap.dev.of_node = pdev->dev.of_node;
	i2c->dev = &pdev->dev;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &mtk_i2c_algorithm;
	i2c->adap.quirks = i2c->dev_comp->quirks;
	i2c->adap.समयout = 2 * HZ;
	i2c->adap.retries = 1;

	ret = mtk_i2c_parse_dt(pdev->dev.of_node, i2c);
	अगर (ret)
		वापस -EINVAL;

	अगर (i2c->have_pmic && !i2c->dev_comp->pmic_i2c)
		वापस -EINVAL;

	i2c->clk_मुख्य = devm_clk_get(&pdev->dev, "main");
	अगर (IS_ERR(i2c->clk_मुख्य)) अणु
		dev_err(&pdev->dev, "cannot get main clock\n");
		वापस PTR_ERR(i2c->clk_मुख्य);
	पूर्ण

	i2c->clk_dma = devm_clk_get(&pdev->dev, "dma");
	अगर (IS_ERR(i2c->clk_dma)) अणु
		dev_err(&pdev->dev, "cannot get dma clock\n");
		वापस PTR_ERR(i2c->clk_dma);
	पूर्ण

	i2c->clk_arb = devm_clk_get(&pdev->dev, "arb");
	अगर (IS_ERR(i2c->clk_arb))
		i2c->clk_arb = शून्य;

	clk = i2c->clk_मुख्य;
	अगर (i2c->have_pmic) अणु
		i2c->clk_pmic = devm_clk_get(&pdev->dev, "pmic");
		अगर (IS_ERR(i2c->clk_pmic)) अणु
			dev_err(&pdev->dev, "cannot get pmic clock\n");
			वापस PTR_ERR(i2c->clk_pmic);
		पूर्ण
		clk = i2c->clk_pmic;
	पूर्ण

	strlcpy(i2c->adap.name, I2C_DRV_NAME, माप(i2c->adap.name));

	ret = mtk_i2c_set_speed(i2c, clk_get_rate(clk));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to set the speed.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (i2c->dev_comp->max_dma_support > 32) अणु
		ret = dma_set_mask(&pdev->dev,
				DMA_BIT_MASK(i2c->dev_comp->max_dma_support));
		अगर (ret) अणु
			dev_err(&pdev->dev, "dma_set_mask return error.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = mtk_i2c_घड़ी_enable(i2c);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clock enable failed!\n");
		वापस ret;
	पूर्ण
	mtk_i2c_init_hw(i2c);
	mtk_i2c_घड़ी_disable(i2c);

	ret = devm_request_irq(&pdev->dev, irq, mtk_i2c_irq,
			       IRQF_NO_SUSPEND | IRQF_TRIGGER_NONE,
			       I2C_DRV_NAME, i2c);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Request I2C IRQ %d fail\n", irq);
		वापस ret;
	पूर्ण

	i2c_set_adapdata(&i2c->adap, i2c);
	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, i2c);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_i2c_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा mtk_i2c *i2c = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&i2c->adap);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_i2c_resume_noirq(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा mtk_i2c *i2c = dev_get_drvdata(dev);

	ret = mtk_i2c_घड़ी_enable(i2c);
	अगर (ret) अणु
		dev_err(dev, "clock enable failed!\n");
		वापस ret;
	पूर्ण

	mtk_i2c_init_hw(i2c);

	mtk_i2c_घड़ी_disable(i2c);

	i2c_mark_adapter_resumed(&i2c->adap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mtk_i2c_pm = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(mtk_i2c_suspend_noirq,
				      mtk_i2c_resume_noirq)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_i2c_driver = अणु
	.probe = mtk_i2c_probe,
	.हटाओ = mtk_i2c_हटाओ,
	.driver = अणु
		.name = I2C_DRV_NAME,
		.pm = &mtk_i2c_pm,
		.of_match_table = of_match_ptr(mtk_i2c_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_i2c_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek I2C Bus Driver");
MODULE_AUTHOR("Xudong Chen <xudong.chen@mediatek.com>");
