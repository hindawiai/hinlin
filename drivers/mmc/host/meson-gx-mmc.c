<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Amlogic SD/eMMC driver क्रम the GX/S905 family SoCs
 *
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Kevin Hilman <khilman@baylibre.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/pinctrl/consumer.h>

#घोषणा DRIVER_NAME "meson-gx-mmc"

#घोषणा SD_EMMC_CLOCK 0x0
#घोषणा   CLK_DIV_MASK GENMASK(5, 0)
#घोषणा   CLK_SRC_MASK GENMASK(7, 6)
#घोषणा   CLK_CORE_PHASE_MASK GENMASK(9, 8)
#घोषणा   CLK_TX_PHASE_MASK GENMASK(11, 10)
#घोषणा   CLK_RX_PHASE_MASK GENMASK(13, 12)
#घोषणा   CLK_PHASE_0 0
#घोषणा   CLK_PHASE_180 2
#घोषणा   CLK_V2_TX_DELAY_MASK GENMASK(19, 16)
#घोषणा   CLK_V2_RX_DELAY_MASK GENMASK(23, 20)
#घोषणा   CLK_V2_ALWAYS_ON BIT(24)

#घोषणा   CLK_V3_TX_DELAY_MASK GENMASK(21, 16)
#घोषणा   CLK_V3_RX_DELAY_MASK GENMASK(27, 22)
#घोषणा   CLK_V3_ALWAYS_ON BIT(28)

#घोषणा   CLK_TX_DELAY_MASK(h)		(h->data->tx_delay_mask)
#घोषणा   CLK_RX_DELAY_MASK(h)		(h->data->rx_delay_mask)
#घोषणा   CLK_ALWAYS_ON(h)		(h->data->always_on)

#घोषणा SD_EMMC_DELAY 0x4
#घोषणा SD_EMMC_ADJUST 0x8
#घोषणा   ADJUST_ADJ_DELAY_MASK GENMASK(21, 16)
#घोषणा   ADJUST_DS_EN BIT(15)
#घोषणा   ADJUST_ADJ_EN BIT(13)

#घोषणा SD_EMMC_DELAY1 0x4
#घोषणा SD_EMMC_DELAY2 0x8
#घोषणा SD_EMMC_V3_ADJUST 0xc

#घोषणा SD_EMMC_CALOUT 0x10
#घोषणा SD_EMMC_START 0x40
#घोषणा   START_DESC_INIT BIT(0)
#घोषणा   START_DESC_BUSY BIT(1)
#घोषणा   START_DESC_ADDR_MASK GENMASK(31, 2)

#घोषणा SD_EMMC_CFG 0x44
#घोषणा   CFG_BUS_WIDTH_MASK GENMASK(1, 0)
#घोषणा   CFG_BUS_WIDTH_1 0x0
#घोषणा   CFG_BUS_WIDTH_4 0x1
#घोषणा   CFG_BUS_WIDTH_8 0x2
#घोषणा   CFG_DDR BIT(2)
#घोषणा   CFG_BLK_LEN_MASK GENMASK(7, 4)
#घोषणा   CFG_RESP_TIMEOUT_MASK GENMASK(11, 8)
#घोषणा   CFG_RC_CC_MASK GENMASK(15, 12)
#घोषणा   CFG_STOP_CLOCK BIT(22)
#घोषणा   CFG_CLK_ALWAYS_ON BIT(18)
#घोषणा   CFG_CHK_DS BIT(20)
#घोषणा   CFG_AUTO_CLK BIT(23)
#घोषणा   CFG_ERR_ABORT BIT(27)

#घोषणा SD_EMMC_STATUS 0x48
#घोषणा   STATUS_BUSY BIT(31)
#घोषणा   STATUS_DESC_BUSY BIT(30)
#घोषणा   STATUS_DATI GENMASK(23, 16)

#घोषणा SD_EMMC_IRQ_EN 0x4c
#घोषणा   IRQ_RXD_ERR_MASK GENMASK(7, 0)
#घोषणा   IRQ_TXD_ERR BIT(8)
#घोषणा   IRQ_DESC_ERR BIT(9)
#घोषणा   IRQ_RESP_ERR BIT(10)
#घोषणा   IRQ_CRC_ERR \
	(IRQ_RXD_ERR_MASK | IRQ_TXD_ERR | IRQ_DESC_ERR | IRQ_RESP_ERR)
#घोषणा   IRQ_RESP_TIMEOUT BIT(11)
#घोषणा   IRQ_DESC_TIMEOUT BIT(12)
#घोषणा   IRQ_TIMEOUTS \
	(IRQ_RESP_TIMEOUT | IRQ_DESC_TIMEOUT)
#घोषणा   IRQ_END_OF_CHAIN BIT(13)
#घोषणा   IRQ_RESP_STATUS BIT(14)
#घोषणा   IRQ_SDIO BIT(15)
#घोषणा   IRQ_EN_MASK \
	(IRQ_CRC_ERR | IRQ_TIMEOUTS | IRQ_END_OF_CHAIN | IRQ_RESP_STATUS |\
	 IRQ_SDIO)

#घोषणा SD_EMMC_CMD_CFG 0x50
#घोषणा SD_EMMC_CMD_ARG 0x54
#घोषणा SD_EMMC_CMD_DAT 0x58
#घोषणा SD_EMMC_CMD_RSP 0x5c
#घोषणा SD_EMMC_CMD_RSP1 0x60
#घोषणा SD_EMMC_CMD_RSP2 0x64
#घोषणा SD_EMMC_CMD_RSP3 0x68

#घोषणा SD_EMMC_RXD 0x94
#घोषणा SD_EMMC_TXD 0x94
#घोषणा SD_EMMC_LAST_REG SD_EMMC_TXD

#घोषणा SD_EMMC_SRAM_DATA_BUF_LEN 1536
#घोषणा SD_EMMC_SRAM_DATA_BUF_OFF 0x200

#घोषणा SD_EMMC_CFG_BLK_SIZE 512 /* पूर्णांकernal buffer max: 512 bytes */
#घोषणा SD_EMMC_CFG_RESP_TIMEOUT 256 /* in घड़ी cycles */
#घोषणा SD_EMMC_CMD_TIMEOUT 1024 /* in ms */
#घोषणा SD_EMMC_CMD_TIMEOUT_DATA 4096 /* in ms */
#घोषणा SD_EMMC_CFG_CMD_GAP 16 /* in घड़ी cycles */
#घोषणा SD_EMMC_DESC_BUF_LEN PAGE_SIZE

#घोषणा SD_EMMC_PRE_REQ_DONE BIT(0)
#घोषणा SD_EMMC_DESC_CHAIN_MODE BIT(1)

#घोषणा MUX_CLK_NUM_PARENTS 2

काष्ठा meson_mmc_data अणु
	अचिन्हित पूर्णांक tx_delay_mask;
	अचिन्हित पूर्णांक rx_delay_mask;
	अचिन्हित पूर्णांक always_on;
	अचिन्हित पूर्णांक adjust;
पूर्ण;

काष्ठा sd_emmc_desc अणु
	u32 cmd_cfg;
	u32 cmd_arg;
	u32 cmd_data;
	u32 cmd_resp;
पूर्ण;

काष्ठा meson_host अणु
	काष्ठा	device		*dev;
	काष्ठा	meson_mmc_data *data;
	काष्ठा	mmc_host	*mmc;
	काष्ठा	mmc_command	*cmd;

	व्योम __iomem *regs;
	काष्ठा clk *core_clk;
	काष्ठा clk *mux_clk;
	काष्ठा clk *mmc_clk;
	अचिन्हित दीर्घ req_rate;
	bool ddr;

	bool dram_access_quirk;

	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_clk_gate;

	अचिन्हित पूर्णांक bounce_buf_size;
	व्योम *bounce_buf;
	dma_addr_t bounce_dma_addr;
	काष्ठा sd_emmc_desc *descs;
	dma_addr_t descs_dma_addr;

	पूर्णांक irq;

	bool vqmmc_enabled;
पूर्ण;

#घोषणा CMD_CFG_LENGTH_MASK GENMASK(8, 0)
#घोषणा CMD_CFG_BLOCK_MODE BIT(9)
#घोषणा CMD_CFG_R1B BIT(10)
#घोषणा CMD_CFG_END_OF_CHAIN BIT(11)
#घोषणा CMD_CFG_TIMEOUT_MASK GENMASK(15, 12)
#घोषणा CMD_CFG_NO_RESP BIT(16)
#घोषणा CMD_CFG_NO_CMD BIT(17)
#घोषणा CMD_CFG_DATA_IO BIT(18)
#घोषणा CMD_CFG_DATA_WR BIT(19)
#घोषणा CMD_CFG_RESP_NOCRC BIT(20)
#घोषणा CMD_CFG_RESP_128 BIT(21)
#घोषणा CMD_CFG_RESP_NUM BIT(22)
#घोषणा CMD_CFG_DATA_NUM BIT(23)
#घोषणा CMD_CFG_CMD_INDEX_MASK GENMASK(29, 24)
#घोषणा CMD_CFG_ERROR BIT(30)
#घोषणा CMD_CFG_OWNER BIT(31)

#घोषणा CMD_DATA_MASK GENMASK(31, 2)
#घोषणा CMD_DATA_BIG_ENDIAN BIT(1)
#घोषणा CMD_DATA_SRAM BIT(0)
#घोषणा CMD_RESP_MASK GENMASK(31, 1)
#घोषणा CMD_RESP_SRAM BIT(0)

अटल अचिन्हित पूर्णांक meson_mmc_get_समयout_msecs(काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक समयout = data->समयout_ns / NSEC_PER_MSEC;

	अगर (!समयout)
		वापस SD_EMMC_CMD_TIMEOUT_DATA;

	समयout = roundup_घात_of_two(समयout);

	वापस min(समयout, 32768U); /* max. 2^15 ms */
पूर्ण

अटल काष्ठा mmc_command *meson_mmc_get_next_command(काष्ठा mmc_command *cmd)
अणु
	अगर (cmd->opcode == MMC_SET_BLOCK_COUNT && !cmd->error)
		वापस cmd->mrq->cmd;
	अन्यथा अगर (mmc_op_multi(cmd->opcode) &&
		 (!cmd->mrq->sbc || cmd->error || cmd->data->error))
		वापस cmd->mrq->stop;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम meson_mmc_get_transfer_mode(काष्ठा mmc_host *mmc,
					काष्ठा mmc_request *mrq)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	/*
	 * When Controller DMA cannot directly access DDR memory, disable
	 * support क्रम Chain Mode to directly use the पूर्णांकernal SRAM using
	 * the bounce buffer mode.
	 */
	अगर (host->dram_access_quirk)
		वापस;

	/* SD_IO_RW_EXTENDED (CMD53) can also use block mode under the hood */
	अगर (data->blocks > 1 || mrq->cmd->opcode == SD_IO_RW_EXTENDED) अणु
		/*
		 * In block mode DMA descriptor क्रमmat, "length" field indicates
		 * number of blocks and there is no way to pass DMA size that
		 * is not multiple of SDIO block size, making it impossible to
		 * tie more than one memory buffer with single SDIO block.
		 * Block mode sg buffer size should be aligned with SDIO block
		 * size, otherwise chain mode could not be used.
		 */
		क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
			अगर (sg->length % data->blksz) अणु
				dev_warn_once(mmc_dev(mmc),
					      "unaligned sg len %u blksize %u, disabling descriptor DMA for transfer\n",
					      sg->length, data->blksz);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
		/* check क्रम 8 byte alignment */
		अगर (sg->offset % 8) अणु
			dev_warn_once(mmc_dev(mmc),
				      "unaligned sg offset %u, disabling descriptor DMA for transfer\n",
				      sg->offset);
			वापस;
		पूर्ण
	पूर्ण

	data->host_cookie |= SD_EMMC_DESC_CHAIN_MODE;
पूर्ण

अटल अंतरभूत bool meson_mmc_desc_chain_mode(स्थिर काष्ठा mmc_data *data)
अणु
	वापस data->host_cookie & SD_EMMC_DESC_CHAIN_MODE;
पूर्ण

अटल अंतरभूत bool meson_mmc_bounce_buf_पढ़ो(स्थिर काष्ठा mmc_data *data)
अणु
	वापस data && data->flags & MMC_DATA_READ &&
	       !meson_mmc_desc_chain_mode(data);
पूर्ण

अटल व्योम meson_mmc_pre_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data)
		वापस;

	meson_mmc_get_transfer_mode(mmc, mrq);
	data->host_cookie |= SD_EMMC_PRE_REQ_DONE;

	अगर (!meson_mmc_desc_chain_mode(data))
		वापस;

	data->sg_count = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_len,
                                   mmc_get_dma_dir(data));
	अगर (!data->sg_count)
		dev_err(mmc_dev(mmc), "dma_map_sg failed");
पूर्ण

अटल व्योम meson_mmc_post_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
			       पूर्णांक err)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (data && meson_mmc_desc_chain_mode(data) && data->sg_count)
		dma_unmap_sg(mmc_dev(mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
पूर्ण

/*
 * Gating the घड़ी on this controller is tricky.  It seems the mmc घड़ी
 * is also used by the controller.  It may crash during some operation अगर the
 * घड़ी is stopped.  The safest thing to करो, whenever possible, is to keep
 * घड़ी running at stop it at the pad using the pinmux.
 */
अटल व्योम meson_mmc_clk_gate(काष्ठा meson_host *host)
अणु
	u32 cfg;

	अगर (host->pins_clk_gate) अणु
		pinctrl_select_state(host->pinctrl, host->pins_clk_gate);
	पूर्ण अन्यथा अणु
		/*
		 * If the pinmux is not provided - शेष to the classic and
		 * unsafe method
		 */
		cfg = पढ़ोl(host->regs + SD_EMMC_CFG);
		cfg |= CFG_STOP_CLOCK;
		ग_लिखोl(cfg, host->regs + SD_EMMC_CFG);
	पूर्ण
पूर्ण

अटल व्योम meson_mmc_clk_ungate(काष्ठा meson_host *host)
अणु
	u32 cfg;

	अगर (host->pins_clk_gate)
		pinctrl_select_शेष_state(host->dev);

	/* Make sure the घड़ी is not stopped in the controller */
	cfg = पढ़ोl(host->regs + SD_EMMC_CFG);
	cfg &= ~CFG_STOP_CLOCK;
	ग_लिखोl(cfg, host->regs + SD_EMMC_CFG);
पूर्ण

अटल पूर्णांक meson_mmc_clk_set(काष्ठा meson_host *host, अचिन्हित दीर्घ rate,
			     bool ddr)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret;
	u32 cfg;

	/* Same request - bail-out */
	अगर (host->ddr == ddr && host->req_rate == rate)
		वापस 0;

	/* stop घड़ी */
	meson_mmc_clk_gate(host);
	host->req_rate = 0;
	mmc->actual_घड़ी = 0;

	/* वापस with घड़ी being stopped */
	अगर (!rate)
		वापस 0;

	/* Stop the घड़ी during rate change to aव्योम glitches */
	cfg = पढ़ोl(host->regs + SD_EMMC_CFG);
	cfg |= CFG_STOP_CLOCK;
	ग_लिखोl(cfg, host->regs + SD_EMMC_CFG);

	अगर (ddr) अणु
		/* DDR modes require higher module घड़ी */
		rate <<= 1;
		cfg |= CFG_DDR;
	पूर्ण अन्यथा अणु
		cfg &= ~CFG_DDR;
	पूर्ण
	ग_लिखोl(cfg, host->regs + SD_EMMC_CFG);
	host->ddr = ddr;

	ret = clk_set_rate(host->mmc_clk, rate);
	अगर (ret) अणु
		dev_err(host->dev, "Unable to set cfg_div_clk to %lu. ret=%d\n",
			rate, ret);
		वापस ret;
	पूर्ण

	host->req_rate = rate;
	mmc->actual_घड़ी = clk_get_rate(host->mmc_clk);

	/* We should report the real output frequency of the controller */
	अगर (ddr) अणु
		host->req_rate >>= 1;
		mmc->actual_घड़ी >>= 1;
	पूर्ण

	dev_dbg(host->dev, "clk rate: %u Hz\n", mmc->actual_घड़ी);
	अगर (rate != mmc->actual_घड़ी)
		dev_dbg(host->dev, "requested rate was %lu\n", rate);

	/* (re)start घड़ी */
	meson_mmc_clk_ungate(host);

	वापस 0;
पूर्ण

/*
 * The SD/eMMC IP block has an पूर्णांकernal mux and भागider used क्रम
 * generating the MMC घड़ी.  Use the घड़ी framework to create and
 * manage these घड़ीs.
 */
अटल पूर्णांक meson_mmc_clk_init(काष्ठा meson_host *host)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_mux *mux;
	काष्ठा clk_भागider *भाग;
	अक्षर clk_name[32];
	पूर्णांक i, ret = 0;
	स्थिर अक्षर *mux_parent_names[MUX_CLK_NUM_PARENTS];
	स्थिर अक्षर *clk_parent[1];
	u32 clk_reg;

	/* init SD_EMMC_CLOCK to sane शेषs w/min घड़ी rate */
	clk_reg = CLK_ALWAYS_ON(host);
	clk_reg |= CLK_DIV_MASK;
	clk_reg |= FIELD_PREP(CLK_CORE_PHASE_MASK, CLK_PHASE_180);
	clk_reg |= FIELD_PREP(CLK_TX_PHASE_MASK, CLK_PHASE_0);
	clk_reg |= FIELD_PREP(CLK_RX_PHASE_MASK, CLK_PHASE_0);
	ग_लिखोl(clk_reg, host->regs + SD_EMMC_CLOCK);

	/* get the mux parents */
	क्रम (i = 0; i < MUX_CLK_NUM_PARENTS; i++) अणु
		काष्ठा clk *clk;
		अक्षर name[16];

		snम_लिखो(name, माप(name), "clkin%d", i);
		clk = devm_clk_get(host->dev, name);
		अगर (IS_ERR(clk))
			वापस dev_err_probe(host->dev, PTR_ERR(clk),
					     "Missing clock %s\n", name);

		mux_parent_names[i] = __clk_get_name(clk);
	पूर्ण

	/* create the mux */
	mux = devm_kzalloc(host->dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	snम_लिखो(clk_name, माप(clk_name), "%s#mux", dev_name(host->dev));
	init.name = clk_name;
	init.ops = &clk_mux_ops;
	init.flags = 0;
	init.parent_names = mux_parent_names;
	init.num_parents = MUX_CLK_NUM_PARENTS;

	mux->reg = host->regs + SD_EMMC_CLOCK;
	mux->shअगरt = __ffs(CLK_SRC_MASK);
	mux->mask = CLK_SRC_MASK >> mux->shअगरt;
	mux->hw.init = &init;

	host->mux_clk = devm_clk_रेजिस्टर(host->dev, &mux->hw);
	अगर (WARN_ON(IS_ERR(host->mux_clk)))
		वापस PTR_ERR(host->mux_clk);

	/* create the भागider */
	भाग = devm_kzalloc(host->dev, माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस -ENOMEM;

	snम_लिखो(clk_name, माप(clk_name), "%s#div", dev_name(host->dev));
	init.name = clk_name;
	init.ops = &clk_भागider_ops;
	init.flags = CLK_SET_RATE_PARENT;
	clk_parent[0] = __clk_get_name(host->mux_clk);
	init.parent_names = clk_parent;
	init.num_parents = 1;

	भाग->reg = host->regs + SD_EMMC_CLOCK;
	भाग->shअगरt = __ffs(CLK_DIV_MASK);
	भाग->width = __builtin_popcountl(CLK_DIV_MASK);
	भाग->hw.init = &init;
	भाग->flags = CLK_DIVIDER_ONE_BASED;

	host->mmc_clk = devm_clk_रेजिस्टर(host->dev, &भाग->hw);
	अगर (WARN_ON(IS_ERR(host->mmc_clk)))
		वापस PTR_ERR(host->mmc_clk);

	/* init SD_EMMC_CLOCK to sane शेषs w/min घड़ी rate */
	host->mmc->f_min = clk_round_rate(host->mmc_clk, 400000);
	ret = clk_set_rate(host->mmc_clk, host->mmc->f_min);
	अगर (ret)
		वापस ret;

	वापस clk_prepare_enable(host->mmc_clk);
पूर्ण

अटल व्योम meson_mmc_disable_resampling(काष्ठा meson_host *host)
अणु
	अचिन्हित पूर्णांक val = पढ़ोl(host->regs + host->data->adjust);

	val &= ~ADJUST_ADJ_EN;
	ग_लिखोl(val, host->regs + host->data->adjust);
पूर्ण

अटल व्योम meson_mmc_reset_resampling(काष्ठा meson_host *host)
अणु
	अचिन्हित पूर्णांक val;

	meson_mmc_disable_resampling(host);

	val = पढ़ोl(host->regs + host->data->adjust);
	val &= ~ADJUST_ADJ_DELAY_MASK;
	ग_लिखोl(val, host->regs + host->data->adjust);
पूर्ण

अटल पूर्णांक meson_mmc_resampling_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	अचिन्हित पूर्णांक val, dly, max_dly, i;
	पूर्णांक ret;

	/* Resampling is करोne using the source घड़ी */
	max_dly = DIV_ROUND_UP(clk_get_rate(host->mux_clk),
			       clk_get_rate(host->mmc_clk));

	val = पढ़ोl(host->regs + host->data->adjust);
	val |= ADJUST_ADJ_EN;
	ग_लिखोl(val, host->regs + host->data->adjust);

	अगर (mmc_करोing_retune(mmc))
		dly = FIELD_GET(ADJUST_ADJ_DELAY_MASK, val) + 1;
	अन्यथा
		dly = 0;

	क्रम (i = 0; i < max_dly; i++) अणु
		val &= ~ADJUST_ADJ_DELAY_MASK;
		val |= FIELD_PREP(ADJUST_ADJ_DELAY_MASK, (dly + i) % max_dly);
		ग_लिखोl(val, host->regs + host->data->adjust);

		ret = mmc_send_tuning(mmc, opcode, शून्य);
		अगर (!ret) अणु
			dev_dbg(mmc_dev(mmc), "resampling delay: %u\n",
				(dly + i) % max_dly);
			वापस 0;
		पूर्ण
	पूर्ण

	meson_mmc_reset_resampling(host);
	वापस -EIO;
पूर्ण

अटल पूर्णांक meson_mmc_prepare_ios_घड़ी(काष्ठा meson_host *host,
				       काष्ठा mmc_ios *ios)
अणु
	bool ddr;

	चयन (ios->timing) अणु
	हाल MMC_TIMING_MMC_DDR52:
	हाल MMC_TIMING_UHS_DDR50:
		ddr = true;
		अवरोध;

	शेष:
		ddr = false;
		अवरोध;
	पूर्ण

	वापस meson_mmc_clk_set(host, ios->घड़ी, ddr);
पूर्ण

अटल व्योम meson_mmc_check_resampling(काष्ठा meson_host *host,
				       काष्ठा mmc_ios *ios)
अणु
	चयन (ios->timing) अणु
	हाल MMC_TIMING_LEGACY:
	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
	हाल MMC_TIMING_MMC_DDR52:
		meson_mmc_disable_resampling(host);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम meson_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	u32 bus_width, val;
	पूर्णांक err;

	/*
	 * GPIO regulator, only controls चयनing between 1v8 and
	 * 3v3, करोesn't support MMC_POWER_OFF, MMC_POWER_ON.
	 */
	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		अगर (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled) अणु
			regulator_disable(mmc->supply.vqmmc);
			host->vqmmc_enabled = false;
		पूर्ण

		अवरोध;

	हाल MMC_POWER_UP:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);

		अवरोध;

	हाल MMC_POWER_ON:
		अगर (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) अणु
			पूर्णांक ret = regulator_enable(mmc->supply.vqmmc);

			अगर (ret < 0)
				dev_err(host->dev,
					"failed to enable vqmmc regulator\n");
			अन्यथा
				host->vqmmc_enabled = true;
		पूर्ण

		अवरोध;
	पूर्ण

	/* Bus width */
	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		bus_width = CFG_BUS_WIDTH_1;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		bus_width = CFG_BUS_WIDTH_4;
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		bus_width = CFG_BUS_WIDTH_8;
		अवरोध;
	शेष:
		dev_err(host->dev, "Invalid ios->bus_width: %u.  Setting to 4.\n",
			ios->bus_width);
		bus_width = CFG_BUS_WIDTH_4;
	पूर्ण

	val = पढ़ोl(host->regs + SD_EMMC_CFG);
	val &= ~CFG_BUS_WIDTH_MASK;
	val |= FIELD_PREP(CFG_BUS_WIDTH_MASK, bus_width);
	ग_लिखोl(val, host->regs + SD_EMMC_CFG);

	meson_mmc_check_resampling(host, ios);
	err = meson_mmc_prepare_ios_घड़ी(host, ios);
	अगर (err)
		dev_err(host->dev, "Failed to set clock: %d\n,", err);

	dev_dbg(host->dev, "SD_EMMC_CFG:  0x%08x\n", val);
पूर्ण

अटल व्योम meson_mmc_request_करोne(काष्ठा mmc_host *mmc,
				   काष्ठा mmc_request *mrq)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);

	host->cmd = शून्य;
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम meson_mmc_set_blksz(काष्ठा mmc_host *mmc, अचिन्हित पूर्णांक blksz)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	u32 cfg, blksz_old;

	cfg = पढ़ोl(host->regs + SD_EMMC_CFG);
	blksz_old = FIELD_GET(CFG_BLK_LEN_MASK, cfg);

	अगर (!is_घातer_of_2(blksz))
		dev_err(host->dev, "blksz %u is not a power of 2\n", blksz);

	blksz = ilog2(blksz);

	/* check अगर block-size matches, अगर not update */
	अगर (blksz == blksz_old)
		वापस;

	dev_dbg(host->dev, "%s: update blk_len %d -> %d\n", __func__,
		blksz_old, blksz);

	cfg &= ~CFG_BLK_LEN_MASK;
	cfg |= FIELD_PREP(CFG_BLK_LEN_MASK, blksz);
	ग_लिखोl(cfg, host->regs + SD_EMMC_CFG);
पूर्ण

अटल व्योम meson_mmc_set_response_bits(काष्ठा mmc_command *cmd, u32 *cmd_cfg)
अणु
	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136)
			*cmd_cfg |= CMD_CFG_RESP_128;
		*cmd_cfg |= CMD_CFG_RESP_NUM;

		अगर (!(cmd->flags & MMC_RSP_CRC))
			*cmd_cfg |= CMD_CFG_RESP_NOCRC;

		अगर (cmd->flags & MMC_RSP_BUSY)
			*cmd_cfg |= CMD_CFG_R1B;
	पूर्ण अन्यथा अणु
		*cmd_cfg |= CMD_CFG_NO_RESP;
	पूर्ण
पूर्ण

अटल व्योम meson_mmc_desc_chain_transfer(काष्ठा mmc_host *mmc, u32 cmd_cfg)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	काष्ठा sd_emmc_desc *desc = host->descs;
	काष्ठा mmc_data *data = host->cmd->data;
	काष्ठा scatterlist *sg;
	u32 start;
	पूर्णांक i;

	अगर (data->flags & MMC_DATA_WRITE)
		cmd_cfg |= CMD_CFG_DATA_WR;

	अगर (data->blocks > 1) अणु
		cmd_cfg |= CMD_CFG_BLOCK_MODE;
		meson_mmc_set_blksz(mmc, data->blksz);
	पूर्ण

	क्रम_each_sg(data->sg, sg, data->sg_count, i) अणु
		अचिन्हित पूर्णांक len = sg_dma_len(sg);

		अगर (data->blocks > 1)
			len /= data->blksz;

		desc[i].cmd_cfg = cmd_cfg;
		desc[i].cmd_cfg |= FIELD_PREP(CMD_CFG_LENGTH_MASK, len);
		अगर (i > 0)
			desc[i].cmd_cfg |= CMD_CFG_NO_CMD;
		desc[i].cmd_arg = host->cmd->arg;
		desc[i].cmd_resp = 0;
		desc[i].cmd_data = sg_dma_address(sg);
	पूर्ण
	desc[data->sg_count - 1].cmd_cfg |= CMD_CFG_END_OF_CHAIN;

	dma_wmb(); /* ensure descriptor is written beक्रमe kicked */
	start = host->descs_dma_addr | START_DESC_BUSY;
	ग_लिखोl(start, host->regs + SD_EMMC_START);
पूर्ण

अटल व्योम meson_mmc_start_cmd(काष्ठा mmc_host *mmc, काष्ठा mmc_command *cmd)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = cmd->data;
	u32 cmd_cfg = 0, cmd_data = 0;
	अचिन्हित पूर्णांक xfer_bytes = 0;

	/* Setup descriptors */
	dma_rmb();

	host->cmd = cmd;

	cmd_cfg |= FIELD_PREP(CMD_CFG_CMD_INDEX_MASK, cmd->opcode);
	cmd_cfg |= CMD_CFG_OWNER;  /* owned by CPU */
	cmd_cfg |= CMD_CFG_ERROR; /* stop in हाल of error */

	meson_mmc_set_response_bits(cmd, &cmd_cfg);

	/* data? */
	अगर (data) अणु
		data->bytes_xfered = 0;
		cmd_cfg |= CMD_CFG_DATA_IO;
		cmd_cfg |= FIELD_PREP(CMD_CFG_TIMEOUT_MASK,
				      ilog2(meson_mmc_get_समयout_msecs(data)));

		अगर (meson_mmc_desc_chain_mode(data)) अणु
			meson_mmc_desc_chain_transfer(mmc, cmd_cfg);
			वापस;
		पूर्ण

		अगर (data->blocks > 1) अणु
			cmd_cfg |= CMD_CFG_BLOCK_MODE;
			cmd_cfg |= FIELD_PREP(CMD_CFG_LENGTH_MASK,
					      data->blocks);
			meson_mmc_set_blksz(mmc, data->blksz);
		पूर्ण अन्यथा अणु
			cmd_cfg |= FIELD_PREP(CMD_CFG_LENGTH_MASK, data->blksz);
		पूर्ण

		xfer_bytes = data->blksz * data->blocks;
		अगर (data->flags & MMC_DATA_WRITE) अणु
			cmd_cfg |= CMD_CFG_DATA_WR;
			WARN_ON(xfer_bytes > host->bounce_buf_size);
			sg_copy_to_buffer(data->sg, data->sg_len,
					  host->bounce_buf, xfer_bytes);
			dma_wmb();
		पूर्ण

		cmd_data = host->bounce_dma_addr & CMD_DATA_MASK;
	पूर्ण अन्यथा अणु
		cmd_cfg |= FIELD_PREP(CMD_CFG_TIMEOUT_MASK,
				      ilog2(SD_EMMC_CMD_TIMEOUT));
	पूर्ण

	/* Last descriptor */
	cmd_cfg |= CMD_CFG_END_OF_CHAIN;
	ग_लिखोl(cmd_cfg, host->regs + SD_EMMC_CMD_CFG);
	ग_लिखोl(cmd_data, host->regs + SD_EMMC_CMD_DAT);
	ग_लिखोl(0, host->regs + SD_EMMC_CMD_RSP);
	wmb(); /* ensure descriptor is written beक्रमe kicked */
	ग_लिखोl(cmd->arg, host->regs + SD_EMMC_CMD_ARG);
पूर्ण

अटल व्योम meson_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	bool needs_pre_post_req = mrq->data &&
			!(mrq->data->host_cookie & SD_EMMC_PRE_REQ_DONE);

	अगर (needs_pre_post_req) अणु
		meson_mmc_get_transfer_mode(mmc, mrq);
		अगर (!meson_mmc_desc_chain_mode(mrq->data))
			needs_pre_post_req = false;
	पूर्ण

	अगर (needs_pre_post_req)
		meson_mmc_pre_req(mmc, mrq);

	/* Stop execution */
	ग_लिखोl(0, host->regs + SD_EMMC_START);

	meson_mmc_start_cmd(mmc, mrq->sbc ?: mrq->cmd);

	अगर (needs_pre_post_req)
		meson_mmc_post_req(mmc, mrq, 0);
पूर्ण

अटल व्योम meson_mmc_पढ़ो_resp(काष्ठा mmc_host *mmc, काष्ठा mmc_command *cmd)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);

	अगर (cmd->flags & MMC_RSP_136) अणु
		cmd->resp[0] = पढ़ोl(host->regs + SD_EMMC_CMD_RSP3);
		cmd->resp[1] = पढ़ोl(host->regs + SD_EMMC_CMD_RSP2);
		cmd->resp[2] = पढ़ोl(host->regs + SD_EMMC_CMD_RSP1);
		cmd->resp[3] = पढ़ोl(host->regs + SD_EMMC_CMD_RSP);
	पूर्ण अन्यथा अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		cmd->resp[0] = पढ़ोl(host->regs + SD_EMMC_CMD_RSP);
	पूर्ण
पूर्ण

अटल irqवापस_t meson_mmc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा meson_host *host = dev_id;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_data *data;
	u32 irq_en, status, raw_status;
	irqवापस_t ret = IRQ_NONE;

	irq_en = पढ़ोl(host->regs + SD_EMMC_IRQ_EN);
	raw_status = पढ़ोl(host->regs + SD_EMMC_STATUS);
	status = raw_status & irq_en;

	अगर (!status) अणु
		dev_dbg(host->dev,
			"Unexpected IRQ! irq_en 0x%08x - status 0x%08x\n",
			 irq_en, raw_status);
		वापस IRQ_NONE;
	पूर्ण

	अगर (WARN_ON(!host) || WARN_ON(!host->cmd))
		वापस IRQ_NONE;

	/* ack all उठाओd पूर्णांकerrupts */
	ग_लिखोl(status, host->regs + SD_EMMC_STATUS);

	cmd = host->cmd;
	data = cmd->data;
	cmd->error = 0;
	अगर (status & IRQ_CRC_ERR) अणु
		dev_dbg(host->dev, "CRC Error - status 0x%08x\n", status);
		cmd->error = -EILSEQ;
		ret = IRQ_WAKE_THREAD;
		जाओ out;
	पूर्ण

	अगर (status & IRQ_TIMEOUTS) अणु
		dev_dbg(host->dev, "Timeout - status 0x%08x\n", status);
		cmd->error = -ETIMEDOUT;
		ret = IRQ_WAKE_THREAD;
		जाओ out;
	पूर्ण

	meson_mmc_पढ़ो_resp(host->mmc, cmd);

	अगर (status & IRQ_SDIO) अणु
		dev_dbg(host->dev, "IRQ: SDIO TODO.\n");
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status & (IRQ_END_OF_CHAIN | IRQ_RESP_STATUS)) अणु
		अगर (data && !cmd->error)
			data->bytes_xfered = data->blksz * data->blocks;
		अगर (meson_mmc_bounce_buf_पढ़ो(data) ||
		    meson_mmc_get_next_command(cmd))
			ret = IRQ_WAKE_THREAD;
		अन्यथा
			ret = IRQ_HANDLED;
	पूर्ण

out:
	अगर (cmd->error) अणु
		/* Stop desc in हाल of errors */
		u32 start = पढ़ोl(host->regs + SD_EMMC_START);

		start &= ~START_DESC_BUSY;
		ग_लिखोl(start, host->regs + SD_EMMC_START);
	पूर्ण

	अगर (ret == IRQ_HANDLED)
		meson_mmc_request_करोne(host->mmc, cmd->mrq);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_mmc_रुको_desc_stop(काष्ठा meson_host *host)
अणु
	u32 status;

	/*
	 * It may someबार take a जबतक क्रम it to actually halt. Here, we
	 * are giving it 5ms to comply
	 *
	 * If we करोn't confirm the descriptor is stopped, it might उठाओ new
	 * IRQs after we have called mmc_request_करोne() which is bad.
	 */

	वापस पढ़ोl_poll_समयout(host->regs + SD_EMMC_STATUS, status,
				  !(status & (STATUS_BUSY | STATUS_DESC_BUSY)),
				  100, 5000);
पूर्ण

अटल irqवापस_t meson_mmc_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा meson_host *host = dev_id;
	काष्ठा mmc_command *next_cmd, *cmd = host->cmd;
	काष्ठा mmc_data *data;
	अचिन्हित पूर्णांक xfer_bytes;

	अगर (WARN_ON(!cmd))
		वापस IRQ_NONE;

	अगर (cmd->error) अणु
		meson_mmc_रुको_desc_stop(host);
		meson_mmc_request_करोne(host->mmc, cmd->mrq);

		वापस IRQ_HANDLED;
	पूर्ण

	data = cmd->data;
	अगर (meson_mmc_bounce_buf_पढ़ो(data)) अणु
		xfer_bytes = data->blksz * data->blocks;
		WARN_ON(xfer_bytes > host->bounce_buf_size);
		sg_copy_from_buffer(data->sg, data->sg_len,
				    host->bounce_buf, xfer_bytes);
	पूर्ण

	next_cmd = meson_mmc_get_next_command(cmd);
	अगर (next_cmd)
		meson_mmc_start_cmd(host->mmc, next_cmd);
	अन्यथा
		meson_mmc_request_करोne(host->mmc, cmd->mrq);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * NOTE: we only need this until the GPIO/pinctrl driver can handle
 * पूर्णांकerrupts.  For now, the MMC core will use this क्रम polling.
 */
अटल पूर्णांक meson_mmc_get_cd(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक status = mmc_gpio_get_cd(mmc);

	अगर (status == -ENOSYS)
		वापस 1; /* assume present */

	वापस status;
पूर्ण

अटल व्योम meson_mmc_cfg_init(काष्ठा meson_host *host)
अणु
	u32 cfg = 0;

	cfg |= FIELD_PREP(CFG_RESP_TIMEOUT_MASK,
			  ilog2(SD_EMMC_CFG_RESP_TIMEOUT));
	cfg |= FIELD_PREP(CFG_RC_CC_MASK, ilog2(SD_EMMC_CFG_CMD_GAP));
	cfg |= FIELD_PREP(CFG_BLK_LEN_MASK, ilog2(SD_EMMC_CFG_BLK_SIZE));

	/* पात chain on R/W errors */
	cfg |= CFG_ERR_ABORT;

	ग_लिखोl(cfg, host->regs + SD_EMMC_CFG);
पूर्ण

अटल पूर्णांक meson_mmc_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_host *host = mmc_priv(mmc);
	u32 regval;

	regval = पढ़ोl(host->regs + SD_EMMC_STATUS);

	/* We are only पूर्णांकerrested in lines 0 to 3, so mask the other ones */
	वापस !(FIELD_GET(STATUS_DATI, regval) & 0xf);
पूर्ण

अटल पूर्णांक meson_mmc_voltage_चयन(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	पूर्णांक ret;

	/* vqmmc regulator is available */
	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		/*
		 * The usual amlogic setup uses a GPIO to चयन from one
		 * regulator to the other. While the voltage ramp up is
		 * pretty fast, care must be taken when चयनing from 3.3v
		 * to 1.8v. Please make sure the regulator framework is aware
		 * of your own regulator स्थिरraपूर्णांकs
		 */
		ret = mmc_regulator_set_vqmmc(mmc, ios);
		वापस ret < 0 ? ret : 0;
	पूर्ण

	/* no vqmmc regulator, assume fixed regulator at 3/3.3V */
	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops meson_mmc_ops = अणु
	.request	= meson_mmc_request,
	.set_ios	= meson_mmc_set_ios,
	.get_cd         = meson_mmc_get_cd,
	.pre_req	= meson_mmc_pre_req,
	.post_req	= meson_mmc_post_req,
	.execute_tuning = meson_mmc_resampling_tuning,
	.card_busy	= meson_mmc_card_busy,
	.start_संकेत_voltage_चयन = meson_mmc_voltage_चयन,
पूर्ण;

अटल पूर्णांक meson_mmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा meson_host *host;
	काष्ठा mmc_host *mmc;
	पूर्णांक ret;

	mmc = mmc_alloc_host(माप(काष्ठा meson_host), &pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;
	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, host);

	/* The G12A SDIO Controller needs an SRAM bounce buffer */
	host->dram_access_quirk = device_property_पढ़ो_bool(&pdev->dev,
					"amlogic,dram-access-quirk");

	/* Get regulators and the supported OCR mask */
	host->vqmmc_enabled = false;
	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		जाओ मुक्त_host;

	ret = mmc_of_parse(mmc);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_warn(&pdev->dev, "error parsing DT: %d\n", ret);
		जाओ मुक्त_host;
	पूर्ण

	host->data = (काष्ठा meson_mmc_data *)
		of_device_get_match_data(&pdev->dev);
	अगर (!host->data) अणु
		ret = -EINVAL;
		जाओ मुक्त_host;
	पूर्ण

	ret = device_reset_optional(&pdev->dev);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret, "device reset failed\n");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->regs)) अणु
		ret = PTR_ERR(host->regs);
		जाओ मुक्त_host;
	पूर्ण

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq <= 0) अणु
		ret = -EINVAL;
		जाओ मुक्त_host;
	पूर्ण

	host->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(host->pinctrl)) अणु
		ret = PTR_ERR(host->pinctrl);
		जाओ मुक्त_host;
	पूर्ण

	host->pins_clk_gate = pinctrl_lookup_state(host->pinctrl,
						   "clk-gate");
	अगर (IS_ERR(host->pins_clk_gate)) अणु
		dev_warn(&pdev->dev,
			 "can't get clk-gate pinctrl, using clk_stop bit\n");
		host->pins_clk_gate = शून्य;
	पूर्ण

	host->core_clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(host->core_clk)) अणु
		ret = PTR_ERR(host->core_clk);
		जाओ मुक्त_host;
	पूर्ण

	ret = clk_prepare_enable(host->core_clk);
	अगर (ret)
		जाओ मुक्त_host;

	ret = meson_mmc_clk_init(host);
	अगर (ret)
		जाओ err_core_clk;

	/* set config to sane शेष */
	meson_mmc_cfg_init(host);

	/* Stop execution */
	ग_लिखोl(0, host->regs + SD_EMMC_START);

	/* clear, ack and enable पूर्णांकerrupts */
	ग_लिखोl(0, host->regs + SD_EMMC_IRQ_EN);
	ग_लिखोl(IRQ_CRC_ERR | IRQ_TIMEOUTS | IRQ_END_OF_CHAIN,
	       host->regs + SD_EMMC_STATUS);
	ग_लिखोl(IRQ_CRC_ERR | IRQ_TIMEOUTS | IRQ_END_OF_CHAIN,
	       host->regs + SD_EMMC_IRQ_EN);

	ret = request_thपढ़ोed_irq(host->irq, meson_mmc_irq,
				   meson_mmc_irq_thपढ़ो, IRQF_ONESHOT,
				   dev_name(&pdev->dev), host);
	अगर (ret)
		जाओ err_init_clk;

	mmc->caps |= MMC_CAP_CMD23;
	अगर (host->dram_access_quirk) अणु
		/* Limit segments to 1 due to low available sram memory */
		mmc->max_segs = 1;
		/* Limit to the available sram memory */
		mmc->max_blk_count = SD_EMMC_SRAM_DATA_BUF_LEN /
				     mmc->max_blk_size;
	पूर्ण अन्यथा अणु
		mmc->max_blk_count = CMD_CFG_LENGTH_MASK;
		mmc->max_segs = SD_EMMC_DESC_BUF_LEN /
				माप(काष्ठा sd_emmc_desc);
	पूर्ण
	mmc->max_req_size = mmc->max_blk_count * mmc->max_blk_size;
	mmc->max_seg_size = mmc->max_req_size;

	/*
	 * At the moment, we करोn't know how to reliably enable HS400.
	 * From the dअगरferent datasheets, it is not even clear अगर this mode
	 * is officially supported by any of the SoCs
	 */
	mmc->caps2 &= ~MMC_CAP2_HS400;

	अगर (host->dram_access_quirk) अणु
		/*
		 * The MMC Controller embeds 1,5KiB of पूर्णांकernal SRAM
		 * that can be used to be used as bounce buffer.
		 * In the हाल of the G12A SDIO controller, use these
		 * instead of the DDR memory
		 */
		host->bounce_buf_size = SD_EMMC_SRAM_DATA_BUF_LEN;
		host->bounce_buf = host->regs + SD_EMMC_SRAM_DATA_BUF_OFF;
		host->bounce_dma_addr = res->start + SD_EMMC_SRAM_DATA_BUF_OFF;
	पूर्ण अन्यथा अणु
		/* data bounce buffer */
		host->bounce_buf_size = mmc->max_req_size;
		host->bounce_buf =
			dma_alloc_coherent(host->dev, host->bounce_buf_size,
					   &host->bounce_dma_addr, GFP_KERNEL);
		अगर (host->bounce_buf == शून्य) अणु
			dev_err(host->dev, "Unable to map allocate DMA bounce buffer.\n");
			ret = -ENOMEM;
			जाओ err_मुक्त_irq;
		पूर्ण
	पूर्ण

	host->descs = dma_alloc_coherent(host->dev, SD_EMMC_DESC_BUF_LEN,
		      &host->descs_dma_addr, GFP_KERNEL);
	अगर (!host->descs) अणु
		dev_err(host->dev, "Allocating descriptor DMA buffer failed\n");
		ret = -ENOMEM;
		जाओ err_bounce_buf;
	पूर्ण

	mmc->ops = &meson_mmc_ops;
	mmc_add_host(mmc);

	वापस 0;

err_bounce_buf:
	अगर (!host->dram_access_quirk)
		dma_मुक्त_coherent(host->dev, host->bounce_buf_size,
				  host->bounce_buf, host->bounce_dma_addr);
err_मुक्त_irq:
	मुक्त_irq(host->irq, host);
err_init_clk:
	clk_disable_unprepare(host->mmc_clk);
err_core_clk:
	clk_disable_unprepare(host->core_clk);
मुक्त_host:
	mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल पूर्णांक meson_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_host *host = dev_get_drvdata(&pdev->dev);

	mmc_हटाओ_host(host->mmc);

	/* disable पूर्णांकerrupts */
	ग_लिखोl(0, host->regs + SD_EMMC_IRQ_EN);
	मुक्त_irq(host->irq, host);

	dma_मुक्त_coherent(host->dev, SD_EMMC_DESC_BUF_LEN,
			  host->descs, host->descs_dma_addr);

	अगर (!host->dram_access_quirk)
		dma_मुक्त_coherent(host->dev, host->bounce_buf_size,
				  host->bounce_buf, host->bounce_dma_addr);

	clk_disable_unprepare(host->mmc_clk);
	clk_disable_unprepare(host->core_clk);

	mmc_मुक्त_host(host->mmc);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा meson_mmc_data meson_gx_data = अणु
	.tx_delay_mask	= CLK_V2_TX_DELAY_MASK,
	.rx_delay_mask	= CLK_V2_RX_DELAY_MASK,
	.always_on	= CLK_V2_ALWAYS_ON,
	.adjust		= SD_EMMC_ADJUST,
पूर्ण;

अटल स्थिर काष्ठा meson_mmc_data meson_axg_data = अणु
	.tx_delay_mask	= CLK_V3_TX_DELAY_MASK,
	.rx_delay_mask	= CLK_V3_RX_DELAY_MASK,
	.always_on	= CLK_V3_ALWAYS_ON,
	.adjust		= SD_EMMC_V3_ADJUST,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_mmc_of_match[] = अणु
	अणु .compatible = "amlogic,meson-gx-mmc",		.data = &meson_gx_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxbb-mmc", 	.data = &meson_gx_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxl-mmc",	.data = &meson_gx_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxm-mmc",	.data = &meson_gx_data पूर्ण,
	अणु .compatible = "amlogic,meson-axg-mmc",	.data = &meson_axg_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_mmc_of_match);

अटल काष्ठा platक्रमm_driver meson_mmc_driver = अणु
	.probe		= meson_mmc_probe,
	.हटाओ		= meson_mmc_हटाओ,
	.driver		= अणु
		.name = DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = meson_mmc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_mmc_driver);

MODULE_DESCRIPTION("Amlogic S905*/GX*/AXG SD/eMMC driver");
MODULE_AUTHOR("Kevin Hilman <khilman@baylibre.com>");
MODULE_LICENSE("GPL v2");
