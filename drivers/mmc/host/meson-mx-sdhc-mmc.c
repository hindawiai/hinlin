<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson6/Meson8/Meson8b/Meson8m2 SDHC MMC host controller driver.
 *
 * Copyright (C) 2020 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/types.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश "meson-mx-sdhc.h"

#घोषणा MESON_SDHC_NUM_BULK_CLKS				4
#घोषणा MESON_SDHC_MAX_BLK_SIZE					512
#घोषणा MESON_SDHC_NUM_TUNING_TRIES				10

#घोषणा MESON_SDHC_WAIT_CMD_READY_SLEEP_US			1
#घोषणा MESON_SDHC_WAIT_CMD_READY_TIMEOUT_US			100000
#घोषणा MESON_SDHC_WAIT_BEFORE_SEND_SLEEP_US			1
#घोषणा MESON_SDHC_WAIT_BEFORE_SEND_TIMEOUT_US			200

काष्ठा meson_mx_sdhc_data अणु
	व्योम		(*init_hw)(काष्ठा mmc_host *mmc);
	व्योम		(*set_pdma)(काष्ठा mmc_host *mmc);
	व्योम		(*रुको_beक्रमe_send)(काष्ठा mmc_host *mmc);
	bool		hardware_flush_all_cmds;
पूर्ण;

काष्ठा meson_mx_sdhc_host अणु
	काष्ठा mmc_host			*mmc;

	काष्ठा mmc_request		*mrq;
	काष्ठा mmc_command		*cmd;
	पूर्णांक				error;

	काष्ठा regmap			*regmap;

	काष्ठा clk			*pclk;
	काष्ठा clk			*sd_clk;
	काष्ठा clk_bulk_data		bulk_clks[MESON_SDHC_NUM_BULK_CLKS];
	bool				bulk_clks_enabled;

	स्थिर काष्ठा meson_mx_sdhc_data	*platक्रमm;
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson_mx_sdhc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = MESON_SDHC_CLK2,
पूर्ण;

अटल व्योम meson_mx_sdhc_hw_reset(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_SRST, MESON_SDHC_SRST_MAIN_CTRL |
		     MESON_SDHC_SRST_RXFIFO | MESON_SDHC_SRST_TXFIFO |
		     MESON_SDHC_SRST_DPHY_RX | MESON_SDHC_SRST_DPHY_TX |
		     MESON_SDHC_SRST_DMA_IF);
	usleep_range(10, 100);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_SRST, 0);
	usleep_range(10, 100);
पूर्ण

अटल व्योम meson_mx_sdhc_clear_fअगरo(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	u32 stat;

	regmap_पढ़ो(host->regmap, MESON_SDHC_STAT, &stat);
	अगर (!FIELD_GET(MESON_SDHC_STAT_RXFIFO_CNT, stat) &&
	    !FIELD_GET(MESON_SDHC_STAT_TXFIFO_CNT, stat))
		वापस;

	regmap_ग_लिखो(host->regmap, MESON_SDHC_SRST, MESON_SDHC_SRST_RXFIFO |
		     MESON_SDHC_SRST_TXFIFO | MESON_SDHC_SRST_MAIN_CTRL);
	udelay(5);

	regmap_पढ़ो(host->regmap, MESON_SDHC_STAT, &stat);
	अगर (FIELD_GET(MESON_SDHC_STAT_RXFIFO_CNT, stat) ||
	    FIELD_GET(MESON_SDHC_STAT_TXFIFO_CNT, stat))
		dev_warn(mmc_dev(host->mmc),
			 "Failed to clear FIFOs, RX: %lu, TX: %lu\n",
			 FIELD_GET(MESON_SDHC_STAT_RXFIFO_CNT, stat),
			 FIELD_GET(MESON_SDHC_STAT_TXFIFO_CNT, stat));
पूर्ण

अटल व्योम meson_mx_sdhc_रुको_cmd_पढ़ोy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	u32 stat, esta;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(host->regmap, MESON_SDHC_STAT, stat,
				       !(stat & MESON_SDHC_STAT_CMD_BUSY),
				       MESON_SDHC_WAIT_CMD_READY_SLEEP_US,
				       MESON_SDHC_WAIT_CMD_READY_TIMEOUT_US);
	अगर (ret) अणु
		dev_warn(mmc_dev(mmc),
			 "Failed to poll for CMD_BUSY while processing CMD%d\n",
			 host->cmd->opcode);
		meson_mx_sdhc_hw_reset(mmc);
	पूर्ण

	ret = regmap_पढ़ो_poll_समयout(host->regmap, MESON_SDHC_ESTA, esta,
				       !(esta & MESON_SDHC_ESTA_11_13),
				       MESON_SDHC_WAIT_CMD_READY_SLEEP_US,
				       MESON_SDHC_WAIT_CMD_READY_TIMEOUT_US);
	अगर (ret) अणु
		dev_warn(mmc_dev(mmc),
			 "Failed to poll for ESTA[13:11] while processing CMD%d\n",
			 host->cmd->opcode);
		meson_mx_sdhc_hw_reset(mmc);
	पूर्ण
पूर्ण

अटल व्योम meson_mx_sdhc_start_cmd(काष्ठा mmc_host *mmc,
				    काष्ठा mmc_command *cmd)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	u32 ictl, send;
	पूर्णांक pack_len;

	host->cmd = cmd;

	ictl = MESON_SDHC_ICTL_DATA_TIMEOUT | MESON_SDHC_ICTL_DATA_ERR_CRC |
	       MESON_SDHC_ICTL_RXFIFO_FULL | MESON_SDHC_ICTL_TXFIFO_EMPTY |
	       MESON_SDHC_ICTL_RESP_TIMEOUT | MESON_SDHC_ICTL_RESP_ERR_CRC;

	send = FIELD_PREP(MESON_SDHC_SEND_CMD_INDEX, cmd->opcode);

	अगर (cmd->data) अणु
		send |= MESON_SDHC_SEND_CMD_HAS_DATA;
		send |= FIELD_PREP(MESON_SDHC_SEND_TOTAL_PACK,
				   cmd->data->blocks - 1);

		अगर (cmd->data->blksz < MESON_SDHC_MAX_BLK_SIZE)
			pack_len = cmd->data->blksz;
		अन्यथा
			pack_len = 0;

		अगर (cmd->data->flags & MMC_DATA_WRITE)
			send |= MESON_SDHC_SEND_DATA_सूची;

		/*
		 * If command with no data, just रुको response करोne
		 * पूर्णांकerrupt(पूर्णांक[0]), and अगर command with data transfer, just
		 * रुको dma करोne पूर्णांकerrupt(पूर्णांक[11]), करोn't need care about
		 * dat0 busy or not.
		 */
		अगर (host->platक्रमm->hardware_flush_all_cmds ||
		    cmd->data->flags & MMC_DATA_WRITE)
			/* hardware flush: */
			ictl |= MESON_SDHC_ICTL_DMA_DONE;
		अन्यथा
			/* software flush: */
			ictl |= MESON_SDHC_ICTL_DATA_XFER_OK;
	पूर्ण अन्यथा अणु
		pack_len = 0;

		ictl |= MESON_SDHC_ICTL_RESP_OK;
	पूर्ण

	अगर (cmd->opcode == MMC_STOP_TRANSMISSION)
		send |= MESON_SDHC_SEND_DATA_STOP;

	अगर (cmd->flags & MMC_RSP_PRESENT)
		send |= MESON_SDHC_SEND_CMD_HAS_RESP;

	अगर (cmd->flags & MMC_RSP_136) अणु
		send |= MESON_SDHC_SEND_RESP_LEN;
		send |= MESON_SDHC_SEND_RESP_NO_CRC;
	पूर्ण

	अगर (!(cmd->flags & MMC_RSP_CRC))
		send |= MESON_SDHC_SEND_RESP_NO_CRC;

	अगर (cmd->flags & MMC_RSP_BUSY)
		send |= MESON_SDHC_SEND_R1B;

	/* enable the new IRQs and mask all pending ones */
	regmap_ग_लिखो(host->regmap, MESON_SDHC_ICTL, ictl);
	regmap_ग_लिखो(host->regmap, MESON_SDHC_ISTA, MESON_SDHC_ISTA_ALL_IRQS);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_ARGU, cmd->arg);

	regmap_update_bits(host->regmap, MESON_SDHC_CTRL,
			   MESON_SDHC_CTRL_PACK_LEN,
			   FIELD_PREP(MESON_SDHC_CTRL_PACK_LEN, pack_len));

	अगर (cmd->data)
		regmap_ग_लिखो(host->regmap, MESON_SDHC_ADDR,
			     sg_dma_address(cmd->data->sg));

	meson_mx_sdhc_रुको_cmd_पढ़ोy(mmc);

	अगर (cmd->data)
		host->platक्रमm->set_pdma(mmc);

	अगर (host->platक्रमm->रुको_beक्रमe_send)
		host->platक्रमm->रुको_beक्रमe_send(mmc);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_SEND, send);
पूर्ण

अटल व्योम meson_mx_sdhc_disable_clks(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);

	अगर (!host->bulk_clks_enabled)
		वापस;

	clk_bulk_disable_unprepare(MESON_SDHC_NUM_BULK_CLKS, host->bulk_clks);

	host->bulk_clks_enabled = false;
पूर्ण

अटल पूर्णांक meson_mx_sdhc_enable_clks(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	पूर्णांक ret;

	अगर (host->bulk_clks_enabled)
		वापस 0;

	ret = clk_bulk_prepare_enable(MESON_SDHC_NUM_BULK_CLKS,
				      host->bulk_clks);
	अगर (ret)
		वापस ret;

	host->bulk_clks_enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_mx_sdhc_set_clk(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	u32 rx_clk_phase;
	पूर्णांक ret;

	meson_mx_sdhc_disable_clks(mmc);

	अगर (ios->घड़ी) अणु
		ret = clk_set_rate(host->sd_clk, ios->घड़ी);
		अगर (ret) अणु
			dev_warn(mmc_dev(mmc),
				 "Failed to set MMC clock to %uHz: %d\n",
				 ios->घड़ी, host->error);
			वापस ret;
		पूर्ण

		ret = meson_mx_sdhc_enable_clks(mmc);
		अगर (ret)
			वापस ret;

		mmc->actual_घड़ी = clk_get_rate(host->sd_clk);

		/*
		 * according to Amlogic the following latching poपूर्णांकs are
		 * selected with empirical values, there is no (known) क्रमmula
		 * to calculate these.
		 */
		अगर (mmc->actual_घड़ी > 100000000) अणु
			rx_clk_phase = 1;
		पूर्ण अन्यथा अगर (mmc->actual_घड़ी > 45000000) अणु
			अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
				rx_clk_phase = 15;
			अन्यथा
				rx_clk_phase = 11;
		पूर्ण अन्यथा अगर (mmc->actual_घड़ी >= 25000000) अणु
			rx_clk_phase = 15;
		पूर्ण अन्यथा अगर (mmc->actual_घड़ी > 5000000) अणु
			rx_clk_phase = 23;
		पूर्ण अन्यथा अगर (mmc->actual_घड़ी > 1000000) अणु
			rx_clk_phase = 55;
		पूर्ण अन्यथा अणु
			rx_clk_phase = 1061;
		पूर्ण

		regmap_update_bits(host->regmap, MESON_SDHC_CLK2,
				   MESON_SDHC_CLK2_RX_CLK_PHASE,
				   FIELD_PREP(MESON_SDHC_CLK2_RX_CLK_PHASE,
					      rx_clk_phase));
	पूर्ण अन्यथा अणु
		mmc->actual_घड़ी = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_mx_sdhc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	अचिन्हित लघु vdd = ios->vdd;

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		vdd = 0;
		fallthrough;

	हाल MMC_POWER_UP:
		अगर (!IS_ERR(mmc->supply.vmmc)) अणु
			host->error = mmc_regulator_set_ocr(mmc,
							    mmc->supply.vmmc,
							    vdd);
			अगर (host->error)
				वापस;
		पूर्ण

		अवरोध;

	हाल MMC_POWER_ON:
		अवरोध;
	पूर्ण

	host->error = meson_mx_sdhc_set_clk(mmc, ios);
	अगर (host->error)
		वापस;

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		regmap_update_bits(host->regmap, MESON_SDHC_CTRL,
				   MESON_SDHC_CTRL_DAT_TYPE,
				   FIELD_PREP(MESON_SDHC_CTRL_DAT_TYPE, 0));
		अवरोध;

	हाल MMC_BUS_WIDTH_4:
		regmap_update_bits(host->regmap, MESON_SDHC_CTRL,
				   MESON_SDHC_CTRL_DAT_TYPE,
				   FIELD_PREP(MESON_SDHC_CTRL_DAT_TYPE, 1));
		अवरोध;

	हाल MMC_BUS_WIDTH_8:
		regmap_update_bits(host->regmap, MESON_SDHC_CTRL,
				   MESON_SDHC_CTRL_DAT_TYPE,
				   FIELD_PREP(MESON_SDHC_CTRL_DAT_TYPE, 2));
		अवरोध;

	शेष:
		dev_err(mmc_dev(mmc), "unsupported bus width: %d\n",
			ios->bus_width);
		host->error = -EINVAL;
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक meson_mx_sdhc_map_dma(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक dma_len;

	अगर (!data)
		वापस 0;

	dma_len = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
	अगर (dma_len <= 0) अणु
		dev_err(mmc_dev(mmc), "dma_map_sg failed\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_mx_sdhc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd = mrq->cmd;

	अगर (!host->error)
		host->error = meson_mx_sdhc_map_dma(mmc, mrq);

	अगर (host->error) अणु
		cmd->error = host->error;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	host->mrq = mrq;

	meson_mx_sdhc_start_cmd(mmc, mrq->cmd);
पूर्ण

अटल पूर्णांक meson_mx_sdhc_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	u32 stat;

	regmap_पढ़ो(host->regmap, MESON_SDHC_STAT, &stat);
	वापस FIELD_GET(MESON_SDHC_STAT_DAT3_0, stat) == 0;
पूर्ण

अटल bool meson_mx_sdhc_tuning_poपूर्णांक_matches(काष्ठा mmc_host *mmc,
					       u32 opcode)
अणु
	अचिन्हित पूर्णांक i, num_matches = 0;
	पूर्णांक ret;

	क्रम (i = 0; i < MESON_SDHC_NUM_TUNING_TRIES; i++) अणु
		ret = mmc_send_tuning(mmc, opcode, शून्य);
		अगर (!ret)
			num_matches++;
	पूर्ण

	वापस num_matches == MESON_SDHC_NUM_TUNING_TRIES;
पूर्ण

अटल पूर्णांक meson_mx_sdhc_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	पूर्णांक भाग, start, len, best_start, best_len;
	पूर्णांक curr_phase, old_phase, new_phase;
	u32 val;

	len = 0;
	start = 0;
	best_len = 0;

	regmap_पढ़ो(host->regmap, MESON_SDHC_CLK2, &val);
	old_phase = FIELD_GET(MESON_SDHC_CLK2_RX_CLK_PHASE, val);

	regmap_पढ़ो(host->regmap, MESON_SDHC_CLKC, &val);
	भाग = FIELD_GET(MESON_SDHC_CLKC_CLK_DIV, val);

	क्रम (curr_phase = 0; curr_phase <= भाग; curr_phase++) अणु
		regmap_update_bits(host->regmap, MESON_SDHC_CLK2,
				   MESON_SDHC_CLK2_RX_CLK_PHASE,
				   FIELD_PREP(MESON_SDHC_CLK2_RX_CLK_PHASE,
					      curr_phase));

		अगर (meson_mx_sdhc_tuning_poपूर्णांक_matches(mmc, opcode)) अणु
			अगर (!len) अणु
				start = curr_phase;

				dev_dbg(mmc_dev(mmc),
					"New RX phase window starts at %u\n",
					start);
			पूर्ण

			len++;
		पूर्ण अन्यथा अणु
			अगर (len > best_len) अणु
				best_start = start;
				best_len = len;

				dev_dbg(mmc_dev(mmc),
					"New best RX phase window: %u - %u\n",
					best_start, best_start + best_len);
			पूर्ण

			/* reset the current winकरोw */
			len = 0;
		पूर्ण
	पूर्ण

	अगर (len > best_len)
		/* the last winकरोw is the best (or possibly only) winकरोw */
		new_phase = start + (len / 2);
	अन्यथा अगर (best_len)
		/* there was a better winकरोw than the last */
		new_phase = best_start + (best_len / 2);
	अन्यथा
		/* no winकरोw was found at all, reset to the original phase */
		new_phase = old_phase;

	regmap_update_bits(host->regmap, MESON_SDHC_CLK2,
			   MESON_SDHC_CLK2_RX_CLK_PHASE,
			   FIELD_PREP(MESON_SDHC_CLK2_RX_CLK_PHASE,
				      new_phase));

	अगर (!len && !best_len)
		वापस -EIO;

	dev_dbg(mmc_dev(mmc), "Tuned RX clock phase to %u\n", new_phase);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops meson_mx_sdhc_ops = अणु
	.hw_reset			= meson_mx_sdhc_hw_reset,
	.request			= meson_mx_sdhc_request,
	.set_ios			= meson_mx_sdhc_set_ios,
	.card_busy			= meson_mx_sdhc_card_busy,
	.execute_tuning			= meson_mx_sdhc_execute_tuning,
	.get_cd				= mmc_gpio_get_cd,
	.get_ro				= mmc_gpio_get_ro,
पूर्ण;

अटल व्योम meson_mx_sdhc_request_करोne(काष्ठा meson_mx_sdhc_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_host *mmc = host->mmc;

	/* disable पूर्णांकerrupts and mask all pending ones */
	regmap_update_bits(host->regmap, MESON_SDHC_ICTL,
			   MESON_SDHC_ICTL_ALL_IRQS, 0);
	regmap_update_bits(host->regmap, MESON_SDHC_ISTA,
			   MESON_SDHC_ISTA_ALL_IRQS, MESON_SDHC_ISTA_ALL_IRQS);

	host->mrq = शून्य;
	host->cmd = शून्य;

	mmc_request_करोne(mmc, mrq);
पूर्ण

अटल u32 meson_mx_sdhc_पढ़ो_response(काष्ठा meson_mx_sdhc_host *host, u8 idx)
अणु
	u32 val;

	regmap_update_bits(host->regmap, MESON_SDHC_PDMA,
			   MESON_SDHC_PDMA_DMA_MODE, 0);

	regmap_update_bits(host->regmap, MESON_SDHC_PDMA,
			   MESON_SDHC_PDMA_PIO_RDRESP,
			   FIELD_PREP(MESON_SDHC_PDMA_PIO_RDRESP, idx));

	regmap_पढ़ो(host->regmap, MESON_SDHC_ARGU, &val);

	वापस val;
पूर्ण

अटल irqवापस_t meson_mx_sdhc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_mx_sdhc_host *host = data;
	काष्ठा mmc_command *cmd = host->cmd;
	u32 ictl, ista;

	regmap_पढ़ो(host->regmap, MESON_SDHC_ICTL, &ictl);
	regmap_पढ़ो(host->regmap, MESON_SDHC_ISTA, &ista);

	अगर (!(ictl & ista))
		वापस IRQ_NONE;

	अगर (ista & MESON_SDHC_ISTA_RXFIFO_FULL ||
	    ista & MESON_SDHC_ISTA_TXFIFO_EMPTY)
		cmd->error = -EIO;
	अन्यथा अगर (ista & MESON_SDHC_ISTA_RESP_ERR_CRC)
		cmd->error = -EILSEQ;
	अन्यथा अगर (ista & MESON_SDHC_ISTA_RESP_TIMEOUT)
		cmd->error = -ETIMEDOUT;

	अगर (cmd->data) अणु
		अगर (ista & MESON_SDHC_ISTA_DATA_ERR_CRC)
			cmd->data->error = -EILSEQ;
		अन्यथा अगर (ista & MESON_SDHC_ISTA_DATA_TIMEOUT)
			cmd->data->error = -ETIMEDOUT;
	पूर्ण

	अगर (cmd->error || (cmd->data && cmd->data->error))
		dev_dbg(mmc_dev(host->mmc), "CMD%d error, ISTA: 0x%08x\n",
			cmd->opcode, ista);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t meson_mx_sdhc_irq_thपढ़ो(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा meson_mx_sdhc_host *host = irq_data;
	काष्ठा mmc_command *cmd;
	u32 val;

	cmd = host->cmd;
	अगर (WARN_ON(!cmd))
		वापस IRQ_HANDLED;

	अगर (cmd->data && !cmd->data->error) अणु
		अगर (!host->platक्रमm->hardware_flush_all_cmds &&
		    cmd->data->flags & MMC_DATA_READ) अणु
			meson_mx_sdhc_रुको_cmd_पढ़ोy(host->mmc);

			/*
			 * If MESON_SDHC_PDMA_RXFIFO_MANUAL_FLUSH was
			 * previously 0x1 then it has to be set to 0x3. If it
			 * was 0x0 beक्रमe then it has to be set to 0x2. Without
			 * this पढ़ोing SD cards someबार transfers garbage,
			 * which results in cards not being detected due to:
			 *   unrecognised SCR काष्ठाure version <अक्रमom number>
			 */
			val = FIELD_PREP(MESON_SDHC_PDMA_RXFIFO_MANUAL_FLUSH,
					 2);
			regmap_update_bits(host->regmap, MESON_SDHC_PDMA, val,
					   val);
		पूर्ण

		dma_unmap_sg(mmc_dev(host->mmc), cmd->data->sg,
			     cmd->data->sg_len, mmc_get_dma_dir(cmd->data));

		cmd->data->bytes_xfered = cmd->data->blksz * cmd->data->blocks;
	पूर्ण

	meson_mx_sdhc_रुको_cmd_पढ़ोy(host->mmc);

	अगर (cmd->flags & MMC_RSP_136) अणु
		cmd->resp[0] = meson_mx_sdhc_पढ़ो_response(host, 4);
		cmd->resp[1] = meson_mx_sdhc_पढ़ो_response(host, 3);
		cmd->resp[2] = meson_mx_sdhc_पढ़ो_response(host, 2);
		cmd->resp[3] = meson_mx_sdhc_पढ़ो_response(host, 1);
	पूर्ण अन्यथा अणु
		cmd->resp[0] = meson_mx_sdhc_पढ़ो_response(host, 0);
	पूर्ण

	अगर (cmd->error == -EIO || cmd->error == -ETIMEDOUT)
		meson_mx_sdhc_hw_reset(host->mmc);
	अन्यथा अगर (cmd->data)
		/*
		 * Clear the FIFOs after completing data transfers to prevent
		 * corrupting data on ग_लिखो access. It's not clear why this is
		 * needed (क्रम पढ़ोs and ग_लिखोs), but it mimics what the BSP
		 * kernel did.
		 */
		meson_mx_sdhc_clear_fअगरo(host->mmc);

	meson_mx_sdhc_request_करोne(host);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम meson_mx_sdhc_init_hw_meson8(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_MISC,
		     FIELD_PREP(MESON_SDHC_MISC_TXSTART_THRES, 7) |
		     FIELD_PREP(MESON_SDHC_MISC_WCRC_ERR_PATT, 5) |
		     FIELD_PREP(MESON_SDHC_MISC_WCRC_OK_PATT, 2));

	regmap_ग_लिखो(host->regmap, MESON_SDHC_ENHC,
		     FIELD_PREP(MESON_SDHC_ENHC_RXFIFO_TH, 63) |
		     MESON_SDHC_ENHC_MESON6_DMA_WR_RESP |
		     FIELD_PREP(MESON_SDHC_ENHC_MESON6_RX_TIMEOUT, 255) |
		     FIELD_PREP(MESON_SDHC_ENHC_SDIO_IRQ_PERIOD, 12));
पूर्ण;

अटल व्योम meson_mx_sdhc_set_pdma_meson8(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);

	अगर (host->cmd->data->flags & MMC_DATA_WRITE)
		regmap_update_bits(host->regmap, MESON_SDHC_PDMA,
				   MESON_SDHC_PDMA_DMA_MODE |
				   MESON_SDHC_PDMA_RD_BURST |
				   MESON_SDHC_PDMA_TXFIFO_FILL,
				   MESON_SDHC_PDMA_DMA_MODE |
				   FIELD_PREP(MESON_SDHC_PDMA_RD_BURST, 31) |
				   MESON_SDHC_PDMA_TXFIFO_FILL);
	अन्यथा
		regmap_update_bits(host->regmap, MESON_SDHC_PDMA,
				   MESON_SDHC_PDMA_DMA_MODE |
				   MESON_SDHC_PDMA_RXFIFO_MANUAL_FLUSH,
				   MESON_SDHC_PDMA_DMA_MODE |
				   FIELD_PREP(MESON_SDHC_PDMA_RXFIFO_MANUAL_FLUSH,
					      1));

	अगर (host->cmd->data->flags & MMC_DATA_WRITE)
		regmap_update_bits(host->regmap, MESON_SDHC_PDMA,
				   MESON_SDHC_PDMA_RD_BURST,
				   FIELD_PREP(MESON_SDHC_PDMA_RD_BURST, 15));
पूर्ण

अटल व्योम meson_mx_sdhc_रुको_beक्रमe_send_meson8(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(host->regmap, MESON_SDHC_ESTA, val,
				       val == 0,
				       MESON_SDHC_WAIT_BEFORE_SEND_SLEEP_US,
				       MESON_SDHC_WAIT_BEFORE_SEND_TIMEOUT_US);
	अगर (ret)
		dev_warn(mmc_dev(mmc),
			 "Failed to wait for ESTA to clear: 0x%08x\n", val);

	अगर (host->cmd->data && host->cmd->data->flags & MMC_DATA_WRITE) अणु
		ret = regmap_पढ़ो_poll_समयout(host->regmap, MESON_SDHC_STAT,
					val, val & MESON_SDHC_STAT_TXFIFO_CNT,
					MESON_SDHC_WAIT_BEFORE_SEND_SLEEP_US,
					MESON_SDHC_WAIT_BEFORE_SEND_TIMEOUT_US);
		अगर (ret)
			dev_warn(mmc_dev(mmc),
				 "Failed to wait for TX FIFO to fill\n");
	पूर्ण
पूर्ण

अटल व्योम meson_mx_sdhc_init_hw_meson8m2(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_MISC,
		     FIELD_PREP(MESON_SDHC_MISC_TXSTART_THRES, 6) |
		     FIELD_PREP(MESON_SDHC_MISC_WCRC_ERR_PATT, 5) |
		     FIELD_PREP(MESON_SDHC_MISC_WCRC_OK_PATT, 2));

	regmap_ग_लिखो(host->regmap, MESON_SDHC_ENHC,
		     FIELD_PREP(MESON_SDHC_ENHC_RXFIFO_TH, 64) |
		     FIELD_PREP(MESON_SDHC_ENHC_MESON8M2_DEBUG, 1) |
		     MESON_SDHC_ENHC_MESON8M2_WRRSP_MODE |
		     FIELD_PREP(MESON_SDHC_ENHC_SDIO_IRQ_PERIOD, 12));
पूर्ण

अटल व्योम meson_mx_sdhc_set_pdma_meson8m2(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);

	regmap_update_bits(host->regmap, MESON_SDHC_PDMA,
			   MESON_SDHC_PDMA_DMA_MODE, MESON_SDHC_PDMA_DMA_MODE);
पूर्ण

अटल व्योम meson_mx_sdhc_init_hw(काष्ठा mmc_host *mmc)
अणु
	काष्ठा meson_mx_sdhc_host *host = mmc_priv(mmc);

	meson_mx_sdhc_hw_reset(mmc);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_CTRL,
		     FIELD_PREP(MESON_SDHC_CTRL_RX_PERIOD, 0xf) |
		     FIELD_PREP(MESON_SDHC_CTRL_RX_TIMEOUT, 0x7f) |
		     FIELD_PREP(MESON_SDHC_CTRL_RX_ENDIAN, 0x7) |
		     FIELD_PREP(MESON_SDHC_CTRL_TX_ENDIAN, 0x7));

	/*
	 * start with a valid भागider and enable the memory (un-setting
	 * MESON_SDHC_CLKC_MEM_PWR_OFF).
	 */
	regmap_ग_लिखो(host->regmap, MESON_SDHC_CLKC, MESON_SDHC_CLKC_CLK_DIV);

	regmap_ग_लिखो(host->regmap, MESON_SDHC_CLK2,
		     FIELD_PREP(MESON_SDHC_CLK2_SD_CLK_PHASE, 1));

	regmap_ग_लिखो(host->regmap, MESON_SDHC_PDMA,
		     MESON_SDHC_PDMA_DMA_URGENT |
		     FIELD_PREP(MESON_SDHC_PDMA_WR_BURST, 7) |
		     FIELD_PREP(MESON_SDHC_PDMA_TXFIFO_TH, 49) |
		     FIELD_PREP(MESON_SDHC_PDMA_RD_BURST, 15) |
		     FIELD_PREP(MESON_SDHC_PDMA_RXFIFO_TH, 7));

	/* some initialization bits depend on the SoC: */
	host->platक्रमm->init_hw(mmc);

	/* disable and mask all पूर्णांकerrupts: */
	regmap_ग_लिखो(host->regmap, MESON_SDHC_ICTL, 0);
	regmap_ग_लिखो(host->regmap, MESON_SDHC_ISTA, MESON_SDHC_ISTA_ALL_IRQS);
पूर्ण

अटल पूर्णांक meson_mx_sdhc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_mx_sdhc_host *host;
	काष्ठा mmc_host *mmc;
	व्योम __iomem *base;
	पूर्णांक ret, irq;

	mmc = mmc_alloc_host(माप(*host), dev);
	अगर (!mmc)
		वापस -ENOMEM;

	ret = devm_add_action_or_reset(dev, (व्योम(*)(व्योम *))mmc_मुक्त_host,
				       mmc);
	अगर (ret) अणु
		dev_err(dev, "Failed to register mmc_free_host action\n");
		वापस ret;
	पूर्ण

	host = mmc_priv(mmc);
	host->mmc = mmc;

	platक्रमm_set_drvdata(pdev, host);

	host->platक्रमm = device_get_match_data(dev);
	अगर (!host->platक्रमm)
		वापस -EINVAL;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	host->regmap = devm_regmap_init_mmio(dev, base,
					     &meson_mx_sdhc_regmap_config);
	अगर (IS_ERR(host->regmap))
		वापस PTR_ERR(host->regmap);

	host->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(host->pclk))
		वापस PTR_ERR(host->pclk);

	/* accessing any रेजिस्टर requires the module घड़ी to be enabled: */
	ret = clk_prepare_enable(host->pclk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable 'pclk' clock\n");
		वापस ret;
	पूर्ण

	meson_mx_sdhc_init_hw(mmc);

	ret = meson_mx_sdhc_रेजिस्टर_clkc(dev, base, host->bulk_clks);
	अगर (ret)
		जाओ err_disable_pclk;

	host->sd_clk = host->bulk_clks[1].clk;

	/* Get regulators and the supported OCR mask */
	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		जाओ err_disable_pclk;

	mmc->max_req_size = SZ_128K;
	mmc->max_seg_size = mmc->max_req_size;
	mmc->max_blk_count = FIELD_GET(MESON_SDHC_SEND_TOTAL_PACK, ~0);
	mmc->max_blk_size = MESON_SDHC_MAX_BLK_SIZE;
	mmc->max_busy_समयout = 30 * MSEC_PER_SEC;
	mmc->f_min = clk_round_rate(host->sd_clk, 1);
	mmc->f_max = clk_round_rate(host->sd_clk, अच_दीर्घ_उच्च);
	mmc->max_current_180 = 300;
	mmc->max_current_330 = 300;
	mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY | MMC_CAP_HW_RESET;
	mmc->ops = &meson_mx_sdhc_ops;

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ err_disable_pclk;

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_thपढ़ोed_irq(dev, irq, meson_mx_sdhc_irq,
					meson_mx_sdhc_irq_thपढ़ो, IRQF_ONESHOT,
					शून्य, host);
	अगर (ret)
		जाओ err_disable_pclk;

	ret = mmc_add_host(mmc);
	अगर (ret)
		जाओ err_disable_pclk;

	वापस 0;

err_disable_pclk:
	clk_disable_unprepare(host->pclk);
	वापस ret;
पूर्ण

अटल पूर्णांक meson_mx_sdhc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_mx_sdhc_host *host = platक्रमm_get_drvdata(pdev);

	mmc_हटाओ_host(host->mmc);

	meson_mx_sdhc_disable_clks(host->mmc);

	clk_disable_unprepare(host->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा meson_mx_sdhc_data meson_mx_sdhc_data_meson8 = अणु
	.init_hw			= meson_mx_sdhc_init_hw_meson8,
	.set_pdma			= meson_mx_sdhc_set_pdma_meson8,
	.रुको_beक्रमe_send		= meson_mx_sdhc_रुको_beक्रमe_send_meson8,
	.hardware_flush_all_cmds	= false,
पूर्ण;

अटल स्थिर काष्ठा meson_mx_sdhc_data meson_mx_sdhc_data_meson8m2 = अणु
	.init_hw			= meson_mx_sdhc_init_hw_meson8m2,
	.set_pdma			= meson_mx_sdhc_set_pdma_meson8m2,
	.hardware_flush_all_cmds	= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_mx_sdhc_of_match[] = अणु
	अणु
		.compatible = "amlogic,meson8-sdhc",
		.data = &meson_mx_sdhc_data_meson8
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8b-sdhc",
		.data = &meson_mx_sdhc_data_meson8
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8m2-sdhc",
		.data = &meson_mx_sdhc_data_meson8m2
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_mx_sdhc_of_match);

अटल काष्ठा platक्रमm_driver meson_mx_sdhc_driver = अणु
	.probe   = meson_mx_sdhc_probe,
	.हटाओ  = meson_mx_sdhc_हटाओ,
	.driver  = अणु
		.name = "meson-mx-sdhc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(meson_mx_sdhc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_mx_sdhc_driver);

MODULE_DESCRIPTION("Meson6, Meson8, Meson8b and Meson8m2 SDHC Host Driver");
MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_LICENSE("GPL v2");
