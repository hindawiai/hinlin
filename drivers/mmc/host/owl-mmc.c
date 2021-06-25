<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Actions Semi Owl SoCs SD/MMC driver
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Copyright (c) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 *
 * TODO: SDIO support
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>

/*
 * SDC रेजिस्टरs
 */
#घोषणा OWL_REG_SD_EN			0x0000
#घोषणा OWL_REG_SD_CTL			0x0004
#घोषणा OWL_REG_SD_STATE		0x0008
#घोषणा OWL_REG_SD_CMD			0x000c
#घोषणा OWL_REG_SD_ARG			0x0010
#घोषणा OWL_REG_SD_RSPBUF0		0x0014
#घोषणा OWL_REG_SD_RSPBUF1		0x0018
#घोषणा OWL_REG_SD_RSPBUF2		0x001c
#घोषणा OWL_REG_SD_RSPBUF3		0x0020
#घोषणा OWL_REG_SD_RSPBUF4		0x0024
#घोषणा OWL_REG_SD_DAT			0x0028
#घोषणा OWL_REG_SD_BLK_SIZE		0x002c
#घोषणा OWL_REG_SD_BLK_NUM		0x0030
#घोषणा OWL_REG_SD_BUF_SIZE		0x0034

/* SD_EN Bits */
#घोषणा OWL_SD_EN_RANE			BIT(31)
#घोषणा OWL_SD_EN_RAN_SEED(x)		(((x) & 0x3f) << 24)
#घोषणा OWL_SD_EN_S18EN			BIT(12)
#घोषणा OWL_SD_EN_RESE			BIT(10)
#घोषणा OWL_SD_EN_DAT1_S		BIT(9)
#घोषणा OWL_SD_EN_CLK_S			BIT(8)
#घोषणा OWL_SD_ENABLE			BIT(7)
#घोषणा OWL_SD_EN_BSEL			BIT(6)
#घोषणा OWL_SD_EN_SDIOEN		BIT(3)
#घोषणा OWL_SD_EN_DDREN			BIT(2)
#घोषणा OWL_SD_EN_DATAWID(x)		(((x) & 0x3) << 0)

/* SD_CTL Bits */
#घोषणा OWL_SD_CTL_TOUTEN		BIT(31)
#घोषणा OWL_SD_CTL_TOUTCNT(x)		(((x) & 0x7f) << 24)
#घोषणा OWL_SD_CTL_DELAY_MSK		GENMASK(23, 16)
#घोषणा OWL_SD_CTL_RDELAY(x)		(((x) & 0xf) << 20)
#घोषणा OWL_SD_CTL_WDELAY(x)		(((x) & 0xf) << 16)
#घोषणा OWL_SD_CTL_CMDLEN		BIT(13)
#घोषणा OWL_SD_CTL_SCC			BIT(12)
#घोषणा OWL_SD_CTL_TCN(x)		(((x) & 0xf) << 8)
#घोषणा OWL_SD_CTL_TS			BIT(7)
#घोषणा OWL_SD_CTL_LBE			BIT(6)
#घोषणा OWL_SD_CTL_C7EN			BIT(5)
#घोषणा OWL_SD_CTL_TM(x)		(((x) & 0xf) << 0)

#घोषणा OWL_SD_DELAY_LOW_CLK		0x0f
#घोषणा OWL_SD_DELAY_MID_CLK		0x0a
#घोषणा OWL_SD_DELAY_HIGH_CLK		0x09
#घोषणा OWL_SD_RDELAY_DDR50		0x0a
#घोषणा OWL_SD_WDELAY_DDR50		0x08

/* SD_STATE Bits */
#घोषणा OWL_SD_STATE_DAT1BS		BIT(18)
#घोषणा OWL_SD_STATE_SDIOB_P		BIT(17)
#घोषणा OWL_SD_STATE_SDIOB_EN		BIT(16)
#घोषणा OWL_SD_STATE_TOUTE		BIT(15)
#घोषणा OWL_SD_STATE_BAEP		BIT(14)
#घोषणा OWL_SD_STATE_MEMRDY		BIT(12)
#घोषणा OWL_SD_STATE_CMDS		BIT(11)
#घोषणा OWL_SD_STATE_DAT1AS		BIT(10)
#घोषणा OWL_SD_STATE_SDIOA_P		BIT(9)
#घोषणा OWL_SD_STATE_SDIOA_EN		BIT(8)
#घोषणा OWL_SD_STATE_DAT0S		BIT(7)
#घोषणा OWL_SD_STATE_TEIE		BIT(6)
#घोषणा OWL_SD_STATE_TEI		BIT(5)
#घोषणा OWL_SD_STATE_CLNR		BIT(4)
#घोषणा OWL_SD_STATE_CLC		BIT(3)
#घोषणा OWL_SD_STATE_WC16ER		BIT(2)
#घोषणा OWL_SD_STATE_RC16ER		BIT(1)
#घोषणा OWL_SD_STATE_CRC7ER		BIT(0)

#घोषणा OWL_CMD_TIMEOUT_MS		30000

काष्ठा owl_mmc_host अणु
	काष्ठा device *dev;
	काष्ठा reset_control *reset;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा completion sdc_complete;
	spinlock_t lock;
	पूर्णांक irq;
	u32 घड़ी;
	bool ddr_50;

	क्रमागत dma_data_direction dma_dir;
	काष्ठा dma_chan *dma;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_slave_config dma_cfg;
	काष्ठा completion dma_complete;

	काष्ठा mmc_host	*mmc;
	काष्ठा mmc_request *mrq;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_data	*data;
पूर्ण;

अटल व्योम owl_mmc_update_reg(व्योम __iomem *reg, अचिन्हित पूर्णांक val, bool state)
अणु
	अचिन्हित पूर्णांक regval;

	regval = पढ़ोl(reg);

	अगर (state)
		regval |= val;
	अन्यथा
		regval &= ~val;

	ग_लिखोl(regval, reg);
पूर्ण

अटल irqवापस_t owl_irq_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा owl_mmc_host *owl_host = devid;
	u32 state;

	spin_lock(&owl_host->lock);

	state = पढ़ोl(owl_host->base + OWL_REG_SD_STATE);
	अगर (state & OWL_SD_STATE_TEI) अणु
		state = पढ़ोl(owl_host->base + OWL_REG_SD_STATE);
		state |= OWL_SD_STATE_TEI;
		ग_लिखोl(state, owl_host->base + OWL_REG_SD_STATE);
		complete(&owl_host->sdc_complete);
	पूर्ण

	spin_unlock(&owl_host->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम owl_mmc_finish_request(काष्ठा owl_mmc_host *owl_host)
अणु
	काष्ठा mmc_request *mrq = owl_host->mrq;
	काष्ठा mmc_data *data = mrq->data;

	/* Should never be शून्य */
	WARN_ON(!mrq);

	owl_host->mrq = शून्य;

	अगर (data)
		dma_unmap_sg(owl_host->dma->device->dev, data->sg, data->sg_len,
			     owl_host->dma_dir);

	/* Finally finish request */
	mmc_request_करोne(owl_host->mmc, mrq);
पूर्ण

अटल व्योम owl_mmc_send_cmd(काष्ठा owl_mmc_host *owl_host,
			     काष्ठा mmc_command *cmd,
			     काष्ठा mmc_data *data)
अणु
	अचिन्हित दीर्घ समयout;
	u32 mode, state, resp[2];
	u32 cmd_rsp_mask = 0;

	init_completion(&owl_host->sdc_complete);

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		mode = OWL_SD_CTL_TM(0);
		अवरोध;

	हाल MMC_RSP_R1:
		अगर (data) अणु
			अगर (data->flags & MMC_DATA_READ)
				mode = OWL_SD_CTL_TM(4);
			अन्यथा
				mode = OWL_SD_CTL_TM(5);
		पूर्ण अन्यथा अणु
			mode = OWL_SD_CTL_TM(1);
		पूर्ण
		cmd_rsp_mask = OWL_SD_STATE_CLNR | OWL_SD_STATE_CRC7ER;

		अवरोध;

	हाल MMC_RSP_R1B:
		mode = OWL_SD_CTL_TM(3);
		cmd_rsp_mask = OWL_SD_STATE_CLNR | OWL_SD_STATE_CRC7ER;
		अवरोध;

	हाल MMC_RSP_R2:
		mode = OWL_SD_CTL_TM(2);
		cmd_rsp_mask = OWL_SD_STATE_CLNR | OWL_SD_STATE_CRC7ER;
		अवरोध;

	हाल MMC_RSP_R3:
		mode = OWL_SD_CTL_TM(1);
		cmd_rsp_mask = OWL_SD_STATE_CLNR;
		अवरोध;

	शेष:
		dev_warn(owl_host->dev, "Unknown MMC command\n");
		cmd->error = -EINVAL;
		वापस;
	पूर्ण

	/* Keep current WDELAY and RDELAY */
	mode |= (पढ़ोl(owl_host->base + OWL_REG_SD_CTL) & (0xff << 16));

	/* Start to send corresponding command type */
	ग_लिखोl(cmd->arg, owl_host->base + OWL_REG_SD_ARG);
	ग_लिखोl(cmd->opcode, owl_host->base + OWL_REG_SD_CMD);

	/* Set LBE to send clk at the end of last पढ़ो block */
	अगर (data) अणु
		mode |= (OWL_SD_CTL_TS | OWL_SD_CTL_LBE | 0x64000000);
	पूर्ण अन्यथा अणु
		mode &= ~(OWL_SD_CTL_TOUTEN | OWL_SD_CTL_LBE);
		mode |= OWL_SD_CTL_TS;
	पूर्ण

	owl_host->cmd = cmd;

	/* Start transfer */
	ग_लिखोl(mode, owl_host->base + OWL_REG_SD_CTL);

	अगर (data)
		वापस;

	समयout = msecs_to_jअगरfies(cmd->busy_समयout ? cmd->busy_समयout :
		OWL_CMD_TIMEOUT_MS);

	अगर (!रुको_क्रम_completion_समयout(&owl_host->sdc_complete, समयout)) अणु
		dev_err(owl_host->dev, "CMD interrupt timeout\n");
		cmd->error = -ETIMEDOUT;
		वापस;
	पूर्ण

	state = पढ़ोl(owl_host->base + OWL_REG_SD_STATE);
	अगर (mmc_resp_type(cmd) & MMC_RSP_PRESENT) अणु
		अगर (cmd_rsp_mask & state) अणु
			अगर (state & OWL_SD_STATE_CLNR) अणु
				dev_err(owl_host->dev, "Error CMD_NO_RSP\n");
				cmd->error = -EILSEQ;
				वापस;
			पूर्ण

			अगर (state & OWL_SD_STATE_CRC7ER) अणु
				dev_err(owl_host->dev, "Error CMD_RSP_CRC\n");
				cmd->error = -EILSEQ;
				वापस;
			पूर्ण
		पूर्ण

		अगर (mmc_resp_type(cmd) & MMC_RSP_136) अणु
			cmd->resp[3] = पढ़ोl(owl_host->base + OWL_REG_SD_RSPBUF0);
			cmd->resp[2] = पढ़ोl(owl_host->base + OWL_REG_SD_RSPBUF1);
			cmd->resp[1] = पढ़ोl(owl_host->base + OWL_REG_SD_RSPBUF2);
			cmd->resp[0] = पढ़ोl(owl_host->base + OWL_REG_SD_RSPBUF3);
		पूर्ण अन्यथा अणु
			resp[0] = पढ़ोl(owl_host->base + OWL_REG_SD_RSPBUF0);
			resp[1] = पढ़ोl(owl_host->base + OWL_REG_SD_RSPBUF1);
			cmd->resp[0] = resp[1] << 24 | resp[0] >> 8;
			cmd->resp[1] = resp[1] >> 8;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम owl_mmc_dma_complete(व्योम *param)
अणु
	काष्ठा owl_mmc_host *owl_host = param;
	काष्ठा mmc_data *data = owl_host->data;

	अगर (data)
		complete(&owl_host->dma_complete);
पूर्ण

अटल पूर्णांक owl_mmc_prepare_data(काष्ठा owl_mmc_host *owl_host,
				काष्ठा mmc_data *data)
अणु
	u32 total;

	owl_mmc_update_reg(owl_host->base + OWL_REG_SD_EN, OWL_SD_EN_BSEL,
			   true);
	ग_लिखोl(data->blocks, owl_host->base + OWL_REG_SD_BLK_NUM);
	ग_लिखोl(data->blksz, owl_host->base + OWL_REG_SD_BLK_SIZE);
	total = data->blksz * data->blocks;

	अगर (total < 512)
		ग_लिखोl(total, owl_host->base + OWL_REG_SD_BUF_SIZE);
	अन्यथा
		ग_लिखोl(512, owl_host->base + OWL_REG_SD_BUF_SIZE);

	अगर (data->flags & MMC_DATA_WRITE) अणु
		owl_host->dma_dir = DMA_TO_DEVICE;
		owl_host->dma_cfg.direction = DMA_MEM_TO_DEV;
	पूर्ण अन्यथा अणु
		owl_host->dma_dir = DMA_FROM_DEVICE;
		owl_host->dma_cfg.direction = DMA_DEV_TO_MEM;
	पूर्ण

	dma_map_sg(owl_host->dma->device->dev, data->sg,
		   data->sg_len, owl_host->dma_dir);

	dmaengine_slave_config(owl_host->dma, &owl_host->dma_cfg);
	owl_host->desc = dmaengine_prep_slave_sg(owl_host->dma, data->sg,
						 data->sg_len,
						 owl_host->dma_cfg.direction,
						 DMA_PREP_INTERRUPT |
						 DMA_CTRL_ACK);
	अगर (!owl_host->desc) अणु
		dev_err(owl_host->dev, "Can't prepare slave sg\n");
		वापस -EBUSY;
	पूर्ण

	owl_host->data = data;

	owl_host->desc->callback = owl_mmc_dma_complete;
	owl_host->desc->callback_param = (व्योम *)owl_host;
	data->error = 0;

	वापस 0;
पूर्ण

अटल व्योम owl_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा owl_mmc_host *owl_host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक ret;

	owl_host->mrq = mrq;
	अगर (mrq->data) अणु
		ret = owl_mmc_prepare_data(owl_host, data);
		अगर (ret < 0) अणु
			data->error = ret;
			जाओ err_out;
		पूर्ण

		init_completion(&owl_host->dma_complete);
		dmaengine_submit(owl_host->desc);
		dma_async_issue_pending(owl_host->dma);
	पूर्ण

	owl_mmc_send_cmd(owl_host, mrq->cmd, data);

	अगर (data) अणु
		अगर (!रुको_क्रम_completion_समयout(&owl_host->sdc_complete,
						 10 * HZ)) अणु
			dev_err(owl_host->dev, "CMD interrupt timeout\n");
			mrq->cmd->error = -ETIMEDOUT;
			dmaengine_terminate_all(owl_host->dma);
			जाओ err_out;
		पूर्ण

		अगर (!रुको_क्रम_completion_समयout(&owl_host->dma_complete,
						 5 * HZ)) अणु
			dev_err(owl_host->dev, "DMA interrupt timeout\n");
			mrq->cmd->error = -ETIMEDOUT;
			dmaengine_terminate_all(owl_host->dma);
			जाओ err_out;
		पूर्ण

		अगर (data->stop)
			owl_mmc_send_cmd(owl_host, data->stop, शून्य);

		data->bytes_xfered = data->blocks * data->blksz;
	पूर्ण

err_out:
	owl_mmc_finish_request(owl_host);
पूर्ण

अटल पूर्णांक owl_mmc_set_clk_rate(काष्ठा owl_mmc_host *owl_host,
				अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक ret;
	u32 reg;

	reg = पढ़ोl(owl_host->base + OWL_REG_SD_CTL);
	reg &= ~OWL_SD_CTL_DELAY_MSK;

	/* Set RDELAY and WDELAY based on the घड़ी */
	अगर (rate <= 1000000) अणु
		ग_लिखोl(reg | OWL_SD_CTL_RDELAY(OWL_SD_DELAY_LOW_CLK) |
		       OWL_SD_CTL_WDELAY(OWL_SD_DELAY_LOW_CLK),
		       owl_host->base + OWL_REG_SD_CTL);
	पूर्ण अन्यथा अगर ((rate > 1000000) && (rate <= 26000000)) अणु
		ग_लिखोl(reg | OWL_SD_CTL_RDELAY(OWL_SD_DELAY_MID_CLK) |
		       OWL_SD_CTL_WDELAY(OWL_SD_DELAY_MID_CLK),
		       owl_host->base + OWL_REG_SD_CTL);
	पूर्ण अन्यथा अगर ((rate > 26000000) && (rate <= 52000000) && !owl_host->ddr_50) अणु
		ग_लिखोl(reg | OWL_SD_CTL_RDELAY(OWL_SD_DELAY_HIGH_CLK) |
		       OWL_SD_CTL_WDELAY(OWL_SD_DELAY_HIGH_CLK),
		       owl_host->base + OWL_REG_SD_CTL);
	/* DDR50 mode has special delay chain */
	पूर्ण अन्यथा अगर ((rate > 26000000) && (rate <= 52000000) && owl_host->ddr_50) अणु
		ग_लिखोl(reg | OWL_SD_CTL_RDELAY(OWL_SD_RDELAY_DDR50) |
		       OWL_SD_CTL_WDELAY(OWL_SD_WDELAY_DDR50),
		       owl_host->base + OWL_REG_SD_CTL);
	पूर्ण अन्यथा अणु
		dev_err(owl_host->dev, "SD clock rate not supported\n");
		वापस -EINVAL;
	पूर्ण

	clk_rate = clk_round_rate(owl_host->clk, rate << 1);
	ret = clk_set_rate(owl_host->clk, clk_rate);

	वापस ret;
पूर्ण

अटल व्योम owl_mmc_set_clk(काष्ठा owl_mmc_host *owl_host, काष्ठा mmc_ios *ios)
अणु
	अगर (!ios->घड़ी)
		वापस;

	owl_host->घड़ी = ios->घड़ी;
	owl_mmc_set_clk_rate(owl_host, ios->घड़ी);
पूर्ण

अटल व्योम owl_mmc_set_bus_width(काष्ठा owl_mmc_host *owl_host,
				  काष्ठा mmc_ios *ios)
अणु
	u32 reg;

	reg = पढ़ोl(owl_host->base + OWL_REG_SD_EN);
	reg &= ~0x03;
	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		reg |= OWL_SD_EN_DATAWID(1);
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		reg |= OWL_SD_EN_DATAWID(2);
		अवरोध;
	पूर्ण

	ग_लिखोl(reg, owl_host->base + OWL_REG_SD_EN);
पूर्ण

अटल व्योम owl_mmc_ctr_reset(काष्ठा owl_mmc_host *owl_host)
अणु
	reset_control_निश्चित(owl_host->reset);
	udelay(20);
	reset_control_deनिश्चित(owl_host->reset);
पूर्ण

अटल व्योम owl_mmc_घातer_on(काष्ठा owl_mmc_host *owl_host)
अणु
	u32 mode;

	init_completion(&owl_host->sdc_complete);

	/* Enable transfer end IRQ */
	owl_mmc_update_reg(owl_host->base + OWL_REG_SD_STATE,
		       OWL_SD_STATE_TEIE, true);

	/* Send init clk */
	mode = (पढ़ोl(owl_host->base + OWL_REG_SD_CTL) & (0xff << 16));
	mode |= OWL_SD_CTL_TS | OWL_SD_CTL_TCN(5) | OWL_SD_CTL_TM(8);
	ग_लिखोl(mode, owl_host->base + OWL_REG_SD_CTL);

	अगर (!रुको_क्रम_completion_समयout(&owl_host->sdc_complete, HZ)) अणु
		dev_err(owl_host->dev, "CMD interrupt timeout\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम owl_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा owl_mmc_host *owl_host = mmc_priv(mmc);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_UP:
		dev_dbg(owl_host->dev, "Powering card up\n");

		/* Reset the SDC controller to clear all previous states */
		owl_mmc_ctr_reset(owl_host);
		clk_prepare_enable(owl_host->clk);
		ग_लिखोl(OWL_SD_ENABLE | OWL_SD_EN_RESE,
		       owl_host->base + OWL_REG_SD_EN);

		अवरोध;

	हाल MMC_POWER_ON:
		dev_dbg(owl_host->dev, "Powering card on\n");
		owl_mmc_घातer_on(owl_host);

		अवरोध;

	हाल MMC_POWER_OFF:
		dev_dbg(owl_host->dev, "Powering card off\n");
		clk_disable_unprepare(owl_host->clk);

		वापस;

	शेष:
		dev_dbg(owl_host->dev, "Ignoring unknown card power state\n");
		अवरोध;
	पूर्ण

	अगर (ios->घड़ी != owl_host->घड़ी)
		owl_mmc_set_clk(owl_host, ios);

	owl_mmc_set_bus_width(owl_host, ios);

	/* Enable DDR mode अगर requested */
	अगर (ios->timing == MMC_TIMING_UHS_DDR50) अणु
		owl_host->ddr_50 = true;
		owl_mmc_update_reg(owl_host->base + OWL_REG_SD_EN,
			       OWL_SD_EN_DDREN, true);
	पूर्ण अन्यथा अणु
		owl_host->ddr_50 = false;
	पूर्ण
पूर्ण

अटल पूर्णांक owl_mmc_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
					       काष्ठा mmc_ios *ios)
अणु
	काष्ठा owl_mmc_host *owl_host = mmc_priv(mmc);

	/* It is enough to change the pad ctrl bit क्रम voltage चयन */
	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		owl_mmc_update_reg(owl_host->base + OWL_REG_SD_EN,
			       OWL_SD_EN_S18EN, false);
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
		owl_mmc_update_reg(owl_host->base + OWL_REG_SD_EN,
			       OWL_SD_EN_S18EN, true);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops owl_mmc_ops = अणु
	.request	= owl_mmc_request,
	.set_ios	= owl_mmc_set_ios,
	.get_ro		= mmc_gpio_get_ro,
	.get_cd		= mmc_gpio_get_cd,
	.start_संकेत_voltage_चयन = owl_mmc_start_संकेत_voltage_चयन,
पूर्ण;

अटल पूर्णांक owl_mmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा owl_mmc_host *owl_host;
	काष्ठा mmc_host *mmc;
	काष्ठा resource *res;
	पूर्णांक ret;

	mmc = mmc_alloc_host(माप(काष्ठा owl_mmc_host), &pdev->dev);
	अगर (!mmc) अणु
		dev_err(&pdev->dev, "mmc alloc host failed\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(pdev, mmc);

	owl_host = mmc_priv(mmc);
	owl_host->dev = &pdev->dev;
	owl_host->mmc = mmc;
	spin_lock_init(&owl_host->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	owl_host->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(owl_host->base)) अणु
		ret = PTR_ERR(owl_host->base);
		जाओ err_मुक्त_host;
	पूर्ण

	owl_host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(owl_host->clk)) अणु
		dev_err(&pdev->dev, "No clock defined\n");
		ret = PTR_ERR(owl_host->clk);
		जाओ err_मुक्त_host;
	पूर्ण

	owl_host->reset = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(owl_host->reset)) अणु
		dev_err(&pdev->dev, "Could not get reset control\n");
		ret = PTR_ERR(owl_host->reset);
		जाओ err_मुक्त_host;
	पूर्ण

	mmc->ops		= &owl_mmc_ops;
	mmc->max_blk_count	= 512;
	mmc->max_blk_size	= 512;
	mmc->max_segs		= 256;
	mmc->max_seg_size	= 262144;
	mmc->max_req_size	= 262144;
	/* 100kHz ~ 52MHz */
	mmc->f_min		= 100000;
	mmc->f_max		= 52000000;
	mmc->caps	       |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
				  MMC_CAP_4_BIT_DATA;
	mmc->caps2		= (MMC_CAP2_BOOTPART_NOACC | MMC_CAP2_NO_SDIO);
	mmc->ocr_avail		= MMC_VDD_32_33 | MMC_VDD_33_34 |
				  MMC_VDD_165_195;

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ err_मुक्त_host;

	pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
	owl_host->dma = dma_request_chan(&pdev->dev, "mmc");
	अगर (IS_ERR(owl_host->dma)) अणु
		dev_err(owl_host->dev, "Failed to get external DMA channel.\n");
		ret = PTR_ERR(owl_host->dma);
		जाओ err_मुक्त_host;
	पूर्ण

	dev_info(&pdev->dev, "Using %s for DMA transfers\n",
		 dma_chan_name(owl_host->dma));

	owl_host->dma_cfg.src_addr = res->start + OWL_REG_SD_DAT;
	owl_host->dma_cfg.dst_addr = res->start + OWL_REG_SD_DAT;
	owl_host->dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	owl_host->dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	owl_host->dma_cfg.device_fc = false;

	owl_host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (owl_host->irq < 0) अणु
		ret = -EINVAL;
		जाओ err_release_channel;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, owl_host->irq, owl_irq_handler,
			       0, dev_name(&pdev->dev), owl_host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq %d\n",
			owl_host->irq);
		जाओ err_release_channel;
	पूर्ण

	ret = mmc_add_host(mmc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add host\n");
		जाओ err_release_channel;
	पूर्ण

	dev_dbg(&pdev->dev, "Owl MMC Controller Initialized\n");

	वापस 0;

err_release_channel:
	dma_release_channel(owl_host->dma);
err_मुक्त_host:
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक owl_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host	*mmc = platक्रमm_get_drvdata(pdev);
	काष्ठा owl_mmc_host *owl_host = mmc_priv(mmc);

	mmc_हटाओ_host(mmc);
	disable_irq(owl_host->irq);
	dma_release_channel(owl_host->dma);
	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id owl_mmc_of_match[] = अणु
	अणु.compatible = "actions,owl-mmc",पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, owl_mmc_of_match);

अटल काष्ठा platक्रमm_driver owl_mmc_driver = अणु
	.driver = अणु
		.name	= "owl_mmc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = owl_mmc_of_match,
	पूर्ण,
	.probe		= owl_mmc_probe,
	.हटाओ		= owl_mmc_हटाओ,
पूर्ण;
module_platक्रमm_driver(owl_mmc_driver);

MODULE_DESCRIPTION("Actions Semi Owl SoCs SD/MMC Driver");
MODULE_AUTHOR("Actions Semi");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_LICENSE("GPL");
