<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * meson-mx-sdio.c - Meson6, Meson8 and Meson8b SDIO/MMC Host Controller
 *
 * Copyright (C) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 * Copyright (C) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>

#घोषणा MESON_MX_SDIO_ARGU					0x00

#घोषणा MESON_MX_SDIO_SEND					0x04
	#घोषणा MESON_MX_SDIO_SEND_COMMAND_INDEX_MASK		GENMASK(7, 0)
	#घोषणा MESON_MX_SDIO_SEND_CMD_RESP_BITS_MASK		GENMASK(15, 8)
	#घोषणा MESON_MX_SDIO_SEND_RESP_WITHOUT_CRC7		BIT(16)
	#घोषणा MESON_MX_SDIO_SEND_RESP_HAS_DATA		BIT(17)
	#घोषणा MESON_MX_SDIO_SEND_RESP_CRC7_FROM_8		BIT(18)
	#घोषणा MESON_MX_SDIO_SEND_CHECK_DAT0_BUSY		BIT(19)
	#घोषणा MESON_MX_SDIO_SEND_DATA				BIT(20)
	#घोषणा MESON_MX_SDIO_SEND_USE_INT_WINDOW		BIT(21)
	#घोषणा MESON_MX_SDIO_SEND_REPEAT_PACKAGE_TIMES_MASK	GENMASK(31, 24)

#घोषणा MESON_MX_SDIO_CONF					0x08
	#घोषणा MESON_MX_SDIO_CONF_CMD_CLK_DIV_SHIFT		0
	#घोषणा MESON_MX_SDIO_CONF_CMD_CLK_DIV_WIDTH		10
	#घोषणा MESON_MX_SDIO_CONF_CMD_DISABLE_CRC		BIT(10)
	#घोषणा MESON_MX_SDIO_CONF_CMD_OUT_AT_POSITIVE_EDGE	BIT(11)
	#घोषणा MESON_MX_SDIO_CONF_CMD_ARGUMENT_BITS_MASK	GENMASK(17, 12)
	#घोषणा MESON_MX_SDIO_CONF_RESP_LATCH_AT_NEGATIVE_EDGE	BIT(18)
	#घोषणा MESON_MX_SDIO_CONF_DATA_LATCH_AT_NEGATIVE_EDGE	BIT(19)
	#घोषणा MESON_MX_SDIO_CONF_BUS_WIDTH			BIT(20)
	#घोषणा MESON_MX_SDIO_CONF_M_ENDIAN_MASK		GENMASK(22, 21)
	#घोषणा MESON_MX_SDIO_CONF_WRITE_NWR_MASK		GENMASK(28, 23)
	#घोषणा MESON_MX_SDIO_CONF_WRITE_CRC_OK_STATUS_MASK	GENMASK(31, 29)

#घोषणा MESON_MX_SDIO_IRQS					0x0c
	#घोषणा MESON_MX_SDIO_IRQS_STATUS_STATE_MACHINE_MASK	GENMASK(3, 0)
	#घोषणा MESON_MX_SDIO_IRQS_CMD_BUSY			BIT(4)
	#घोषणा MESON_MX_SDIO_IRQS_RESP_CRC7_OK			BIT(5)
	#घोषणा MESON_MX_SDIO_IRQS_DATA_READ_CRC16_OK		BIT(6)
	#घोषणा MESON_MX_SDIO_IRQS_DATA_WRITE_CRC16_OK		BIT(7)
	#घोषणा MESON_MX_SDIO_IRQS_IF_INT			BIT(8)
	#घोषणा MESON_MX_SDIO_IRQS_CMD_INT			BIT(9)
	#घोषणा MESON_MX_SDIO_IRQS_STATUS_INFO_MASK		GENMASK(15, 12)
	#घोषणा MESON_MX_SDIO_IRQS_TIMING_OUT_INT		BIT(16)
	#घोषणा MESON_MX_SDIO_IRQS_AMRISC_TIMING_OUT_INT_EN	BIT(17)
	#घोषणा MESON_MX_SDIO_IRQS_ARC_TIMING_OUT_INT_EN	BIT(18)
	#घोषणा MESON_MX_SDIO_IRQS_TIMING_OUT_COUNT_MASK	GENMASK(31, 19)

#घोषणा MESON_MX_SDIO_IRQC					0x10
	#घोषणा MESON_MX_SDIO_IRQC_ARC_IF_INT_EN		BIT(3)
	#घोषणा MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN		BIT(4)
	#घोषणा MESON_MX_SDIO_IRQC_IF_CONFIG_MASK		GENMASK(7, 6)
	#घोषणा MESON_MX_SDIO_IRQC_FORCE_DATA_CLK		BIT(8)
	#घोषणा MESON_MX_SDIO_IRQC_FORCE_DATA_CMD		BIT(9)
	#घोषणा MESON_MX_SDIO_IRQC_FORCE_DATA_DAT_MASK		GENMASK(13, 10)
	#घोषणा MESON_MX_SDIO_IRQC_SOFT_RESET			BIT(15)
	#घोषणा MESON_MX_SDIO_IRQC_FORCE_HALT			BIT(30)
	#घोषणा MESON_MX_SDIO_IRQC_HALT_HOLE			BIT(31)

#घोषणा MESON_MX_SDIO_MULT					0x14
	#घोषणा MESON_MX_SDIO_MULT_PORT_SEL_MASK		GENMASK(1, 0)
	#घोषणा MESON_MX_SDIO_MULT_MEMORY_STICK_ENABLE		BIT(2)
	#घोषणा MESON_MX_SDIO_MULT_MEMORY_STICK_SCLK_ALWAYS	BIT(3)
	#घोषणा MESON_MX_SDIO_MULT_STREAM_ENABLE		BIT(4)
	#घोषणा MESON_MX_SDIO_MULT_STREAM_8BITS_MODE		BIT(5)
	#घोषणा MESON_MX_SDIO_MULT_WR_RD_OUT_INDEX		BIT(8)
	#घोषणा MESON_MX_SDIO_MULT_DAT0_DAT1_SWAPPED		BIT(10)
	#घोषणा MESON_MX_SDIO_MULT_DAT1_DAT0_SWAPPED		BIT(11)
	#घोषणा MESON_MX_SDIO_MULT_RESP_READ_INDEX_MASK		GENMASK(15, 12)

#घोषणा MESON_MX_SDIO_ADDR					0x18

#घोषणा MESON_MX_SDIO_EXT					0x1c
	#घोषणा MESON_MX_SDIO_EXT_DATA_RW_NUMBER_MASK		GENMASK(29, 16)

#घोषणा MESON_MX_SDIO_BOUNCE_REQ_SIZE				(128 * 1024)
#घोषणा MESON_MX_SDIO_RESPONSE_CRC16_BITS			(16 - 1)
#घोषणा MESON_MX_SDIO_MAX_SLOTS					3

काष्ठा meson_mx_mmc_host अणु
	काष्ठा device			*controller_dev;

	काष्ठा clk			*parent_clk;
	काष्ठा clk			*core_clk;
	काष्ठा clk_भागider		cfg_भाग;
	काष्ठा clk			*cfg_भाग_clk;
	काष्ठा clk_fixed_factor		fixed_factor;
	काष्ठा clk			*fixed_factor_clk;

	व्योम __iomem			*base;
	पूर्णांक				irq;
	spinlock_t			irq_lock;

	काष्ठा समयr_list		cmd_समयout;

	अचिन्हित पूर्णांक			slot_id;
	काष्ठा mmc_host			*mmc;

	काष्ठा mmc_request		*mrq;
	काष्ठा mmc_command		*cmd;
	पूर्णांक				error;
पूर्ण;

अटल व्योम meson_mx_mmc_mask_bits(काष्ठा mmc_host *mmc, अक्षर reg, u32 mask,
				   u32 val)
अणु
	काष्ठा meson_mx_mmc_host *host = mmc_priv(mmc);
	u32 regval;

	regval = पढ़ोl(host->base + reg);
	regval &= ~mask;
	regval |= (val & mask);

	ग_लिखोl(regval, host->base + reg);
पूर्ण

अटल व्योम meson_mx_mmc_soft_reset(काष्ठा meson_mx_mmc_host *host)
अणु
	ग_लिखोl(MESON_MX_SDIO_IRQC_SOFT_RESET, host->base + MESON_MX_SDIO_IRQC);
	udelay(2);
पूर्ण

अटल काष्ठा mmc_command *meson_mx_mmc_get_next_cmd(काष्ठा mmc_command *cmd)
अणु
	अगर (cmd->opcode == MMC_SET_BLOCK_COUNT && !cmd->error)
		वापस cmd->mrq->cmd;
	अन्यथा अगर (mmc_op_multi(cmd->opcode) &&
		 (!cmd->mrq->sbc || cmd->error || cmd->data->error))
		वापस cmd->mrq->stop;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम meson_mx_mmc_start_cmd(काष्ठा mmc_host *mmc,
				   काष्ठा mmc_command *cmd)
अणु
	काष्ठा meson_mx_mmc_host *host = mmc_priv(mmc);
	अचिन्हित पूर्णांक pack_size;
	अचिन्हित दीर्घ irqflags, समयout;
	u32 mult, send = 0, ext = 0;

	host->cmd = cmd;

	अगर (cmd->busy_समयout)
		समयout = msecs_to_jअगरfies(cmd->busy_समयout);
	अन्यथा
		समयout = msecs_to_jअगरfies(1000);

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_R1:
	हाल MMC_RSP_R1B:
	हाल MMC_RSP_R3:
		/* 7 (CMD) + 32 (response) + 7 (CRC) -1 */
		send |= FIELD_PREP(MESON_MX_SDIO_SEND_CMD_RESP_BITS_MASK, 45);
		अवरोध;
	हाल MMC_RSP_R2:
		/* 7 (CMD) + 120 (response) + 7 (CRC) -1 */
		send |= FIELD_PREP(MESON_MX_SDIO_SEND_CMD_RESP_BITS_MASK, 133);
		send |= MESON_MX_SDIO_SEND_RESP_CRC7_FROM_8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!(cmd->flags & MMC_RSP_CRC))
		send |= MESON_MX_SDIO_SEND_RESP_WITHOUT_CRC7;

	अगर (cmd->flags & MMC_RSP_BUSY)
		send |= MESON_MX_SDIO_SEND_CHECK_DAT0_BUSY;

	अगर (cmd->data) अणु
		send |= FIELD_PREP(MESON_MX_SDIO_SEND_REPEAT_PACKAGE_TIMES_MASK,
				   (cmd->data->blocks - 1));

		pack_size = cmd->data->blksz * BITS_PER_BYTE;
		अगर (mmc->ios.bus_width == MMC_BUS_WIDTH_4)
			pack_size += MESON_MX_SDIO_RESPONSE_CRC16_BITS * 4;
		अन्यथा
			pack_size += MESON_MX_SDIO_RESPONSE_CRC16_BITS * 1;

		ext |= FIELD_PREP(MESON_MX_SDIO_EXT_DATA_RW_NUMBER_MASK,
				  pack_size);

		अगर (cmd->data->flags & MMC_DATA_WRITE)
			send |= MESON_MX_SDIO_SEND_DATA;
		अन्यथा
			send |= MESON_MX_SDIO_SEND_RESP_HAS_DATA;

		cmd->data->bytes_xfered = 0;
	पूर्ण

	send |= FIELD_PREP(MESON_MX_SDIO_SEND_COMMAND_INDEX_MASK,
			   (0x40 | cmd->opcode));

	spin_lock_irqsave(&host->irq_lock, irqflags);

	mult = पढ़ोl(host->base + MESON_MX_SDIO_MULT);
	mult &= ~MESON_MX_SDIO_MULT_PORT_SEL_MASK;
	mult |= FIELD_PREP(MESON_MX_SDIO_MULT_PORT_SEL_MASK, host->slot_id);
	mult |= BIT(31);
	ग_लिखोl(mult, host->base + MESON_MX_SDIO_MULT);

	/* enable the CMD करोne पूर्णांकerrupt */
	meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_IRQC,
			       MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN,
			       MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN);

	/* clear pending पूर्णांकerrupts */
	meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_IRQS,
			       MESON_MX_SDIO_IRQS_CMD_INT,
			       MESON_MX_SDIO_IRQS_CMD_INT);

	ग_लिखोl(cmd->arg, host->base + MESON_MX_SDIO_ARGU);
	ग_लिखोl(ext, host->base + MESON_MX_SDIO_EXT);
	ग_लिखोl(send, host->base + MESON_MX_SDIO_SEND);

	spin_unlock_irqrestore(&host->irq_lock, irqflags);

	mod_समयr(&host->cmd_समयout, jअगरfies + समयout);
पूर्ण

अटल व्योम meson_mx_mmc_request_करोne(काष्ठा meson_mx_mmc_host *host)
अणु
	काष्ठा mmc_request *mrq;

	mrq = host->mrq;

	अगर (host->cmd->error)
		meson_mx_mmc_soft_reset(host);

	host->mrq = शून्य;
	host->cmd = शून्य;

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम meson_mx_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा meson_mx_mmc_host *host = mmc_priv(mmc);
	अचिन्हित लघु vdd = ios->vdd;
	अचिन्हित दीर्घ clk_rate = ios->घड़ी;

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_CONF,
				       MESON_MX_SDIO_CONF_BUS_WIDTH, 0);
		अवरोध;

	हाल MMC_BUS_WIDTH_4:
		meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_CONF,
				       MESON_MX_SDIO_CONF_BUS_WIDTH,
				       MESON_MX_SDIO_CONF_BUS_WIDTH);
		अवरोध;

	हाल MMC_BUS_WIDTH_8:
	शेष:
		dev_err(mmc_dev(mmc), "unsupported bus width: %d\n",
			ios->bus_width);
		host->error = -EINVAL;
		वापस;
	पूर्ण

	host->error = clk_set_rate(host->cfg_भाग_clk, ios->घड़ी);
	अगर (host->error) अणु
		dev_warn(mmc_dev(mmc),
				"failed to set MMC clock to %lu: %d\n",
				clk_rate, host->error);
		वापस;
	पूर्ण

	mmc->actual_घड़ी = clk_get_rate(host->cfg_भाग_clk);

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
	पूर्ण
पूर्ण

अटल पूर्णांक meson_mx_mmc_map_dma(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक dma_len;
	काष्ठा scatterlist *sg;

	अगर (!data)
		वापस 0;

	sg = data->sg;
	अगर (sg->offset & 3 || sg->length & 3) अणु
		dev_err(mmc_dev(mmc),
			"unaligned scatterlist: offset %x length %d\n",
			sg->offset, sg->length);
		वापस -EINVAL;
	पूर्ण

	dma_len = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
	अगर (dma_len <= 0) अणु
		dev_err(mmc_dev(mmc), "dma_map_sg failed\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_mx_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा meson_mx_mmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd = mrq->cmd;

	अगर (!host->error)
		host->error = meson_mx_mmc_map_dma(mmc, mrq);

	अगर (host->error) अणु
		cmd->error = host->error;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	host->mrq = mrq;

	अगर (mrq->data)
		ग_लिखोl(sg_dma_address(mrq->data->sg),
		       host->base + MESON_MX_SDIO_ADDR);

	अगर (mrq->sbc)
		meson_mx_mmc_start_cmd(mmc, mrq->sbc);
	अन्यथा
		meson_mx_mmc_start_cmd(mmc, mrq->cmd);
पूर्ण

अटल व्योम meson_mx_mmc_पढ़ो_response(काष्ठा mmc_host *mmc,
				       काष्ठा mmc_command *cmd)
अणु
	काष्ठा meson_mx_mmc_host *host = mmc_priv(mmc);
	u32 mult;
	पूर्णांक i, resp[4];

	mult = पढ़ोl(host->base + MESON_MX_SDIO_MULT);
	mult |= MESON_MX_SDIO_MULT_WR_RD_OUT_INDEX;
	mult &= ~MESON_MX_SDIO_MULT_RESP_READ_INDEX_MASK;
	mult |= FIELD_PREP(MESON_MX_SDIO_MULT_RESP_READ_INDEX_MASK, 0);
	ग_लिखोl(mult, host->base + MESON_MX_SDIO_MULT);

	अगर (cmd->flags & MMC_RSP_136) अणु
		क्रम (i = 0; i <= 3; i++)
			resp[3 - i] = पढ़ोl(host->base + MESON_MX_SDIO_ARGU);
		cmd->resp[0] = (resp[0] << 8) | ((resp[1] >> 24) & 0xff);
		cmd->resp[1] = (resp[1] << 8) | ((resp[2] >> 24) & 0xff);
		cmd->resp[2] = (resp[2] << 8) | ((resp[3] >> 24) & 0xff);
		cmd->resp[3] = (resp[3] << 8);
	पूर्ण अन्यथा अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		cmd->resp[0] = पढ़ोl(host->base + MESON_MX_SDIO_ARGU);
	पूर्ण
पूर्ण

अटल irqवापस_t meson_mx_mmc_process_cmd_irq(काष्ठा meson_mx_mmc_host *host,
						u32 irqs, u32 send)
अणु
	काष्ठा mmc_command *cmd = host->cmd;

	/*
	 * NOTE: even though it shouldn't happen we someबार get command
	 * पूर्णांकerrupts twice (at least this is what it looks like). Ideally
	 * we find out why this happens and warn here as soon as it occurs.
	 */
	अगर (!cmd)
		वापस IRQ_HANDLED;

	cmd->error = 0;
	meson_mx_mmc_पढ़ो_response(host->mmc, cmd);

	अगर (cmd->data) अणु
		अगर (!((irqs & MESON_MX_SDIO_IRQS_DATA_READ_CRC16_OK) ||
		      (irqs & MESON_MX_SDIO_IRQS_DATA_WRITE_CRC16_OK)))
			cmd->error = -EILSEQ;
	पूर्ण अन्यथा अणु
		अगर (!((irqs & MESON_MX_SDIO_IRQS_RESP_CRC7_OK) ||
		      (send & MESON_MX_SDIO_SEND_RESP_WITHOUT_CRC7)))
			cmd->error = -EILSEQ;
	पूर्ण

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t meson_mx_mmc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_mx_mmc_host *host = (व्योम *) data;
	u32 irqs, send;
	irqवापस_t ret;

	spin_lock(&host->irq_lock);

	irqs = पढ़ोl(host->base + MESON_MX_SDIO_IRQS);
	send = पढ़ोl(host->base + MESON_MX_SDIO_SEND);

	अगर (irqs & MESON_MX_SDIO_IRQS_CMD_INT)
		ret = meson_mx_mmc_process_cmd_irq(host, irqs, send);
	अन्यथा
		ret = IRQ_HANDLED;

	/* finally ACK all pending पूर्णांकerrupts */
	ग_लिखोl(irqs, host->base + MESON_MX_SDIO_IRQS);

	spin_unlock(&host->irq_lock);

	वापस ret;
पूर्ण

अटल irqवापस_t meson_mx_mmc_irq_thपढ़ो(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा meson_mx_mmc_host *host = (व्योम *) irq_data;
	काष्ठा mmc_command *cmd = host->cmd, *next_cmd;

	अगर (WARN_ON(!cmd))
		वापस IRQ_HANDLED;

	del_समयr_sync(&host->cmd_समयout);

	अगर (cmd->data) अणु
		dma_unmap_sg(mmc_dev(host->mmc), cmd->data->sg,
				cmd->data->sg_len,
				mmc_get_dma_dir(cmd->data));

		cmd->data->bytes_xfered = cmd->data->blksz * cmd->data->blocks;
	पूर्ण

	next_cmd = meson_mx_mmc_get_next_cmd(cmd);
	अगर (next_cmd)
		meson_mx_mmc_start_cmd(host->mmc, next_cmd);
	अन्यथा
		meson_mx_mmc_request_करोne(host);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम meson_mx_mmc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा meson_mx_mmc_host *host = from_समयr(host, t, cmd_समयout);
	अचिन्हित दीर्घ irqflags;
	u32 irqc;

	spin_lock_irqsave(&host->irq_lock, irqflags);

	/* disable the CMD पूर्णांकerrupt */
	irqc = पढ़ोl(host->base + MESON_MX_SDIO_IRQC);
	irqc &= ~MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN;
	ग_लिखोl(irqc, host->base + MESON_MX_SDIO_IRQC);

	spin_unlock_irqrestore(&host->irq_lock, irqflags);

	/*
	 * skip the समयout handling अगर the पूर्णांकerrupt handler alपढ़ोy processed
	 * the command.
	 */
	अगर (!host->cmd)
		वापस;

	dev_dbg(mmc_dev(host->mmc),
		"Timeout on CMD%u (IRQS = 0x%08x, ARGU = 0x%08x)\n",
		host->cmd->opcode, पढ़ोl(host->base + MESON_MX_SDIO_IRQS),
		पढ़ोl(host->base + MESON_MX_SDIO_ARGU));

	host->cmd->error = -ETIMEDOUT;

	meson_mx_mmc_request_करोne(host);
पूर्ण

अटल काष्ठा mmc_host_ops meson_mx_mmc_ops = अणु
	.request		= meson_mx_mmc_request,
	.set_ios		= meson_mx_mmc_set_ios,
	.get_cd			= mmc_gpio_get_cd,
	.get_ro			= mmc_gpio_get_ro,
पूर्ण;

अटल काष्ठा platक्रमm_device *meson_mx_mmc_slot_pdev(काष्ठा device *parent)
अणु
	काष्ठा device_node *slot_node;
	काष्ठा platक्रमm_device *pdev;

	/*
	 * TODO: the MMC core framework currently करोes not support
	 * controllers with multiple slots properly. So we only रेजिस्टर
	 * the first slot क्रम now
	 */
	slot_node = of_get_compatible_child(parent->of_node, "mmc-slot");
	अगर (!slot_node) अणु
		dev_warn(parent, "no 'mmc-slot' sub-node found\n");
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	pdev = of_platक्रमm_device_create(slot_node, शून्य, parent);
	of_node_put(slot_node);

	वापस pdev;
पूर्ण

अटल पूर्णांक meson_mx_mmc_add_host(काष्ठा meson_mx_mmc_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा device *slot_dev = mmc_dev(mmc);
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(slot_dev->of_node, "reg", &host->slot_id)) अणु
		dev_err(slot_dev, "missing 'reg' property\n");
		वापस -EINVAL;
	पूर्ण

	अगर (host->slot_id >= MESON_MX_SDIO_MAX_SLOTS) अणु
		dev_err(slot_dev, "invalid 'reg' property value %d\n",
			host->slot_id);
		वापस -EINVAL;
	पूर्ण

	/* Get regulators and the supported OCR mask */
	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		वापस ret;

	mmc->max_req_size = MESON_MX_SDIO_BOUNCE_REQ_SIZE;
	mmc->max_seg_size = mmc->max_req_size;
	mmc->max_blk_count =
		FIELD_GET(MESON_MX_SDIO_SEND_REPEAT_PACKAGE_TIMES_MASK,
			  0xffffffff);
	mmc->max_blk_size = FIELD_GET(MESON_MX_SDIO_EXT_DATA_RW_NUMBER_MASK,
				      0xffffffff);
	mmc->max_blk_size -= (4 * MESON_MX_SDIO_RESPONSE_CRC16_BITS);
	mmc->max_blk_size /= BITS_PER_BYTE;

	/* Get the min and max supported घड़ी rates */
	mmc->f_min = clk_round_rate(host->cfg_भाग_clk, 1);
	mmc->f_max = clk_round_rate(host->cfg_भाग_clk,
				    clk_get_rate(host->parent_clk));

	mmc->caps |= MMC_CAP_CMD23 | MMC_CAP_WAIT_WHILE_BUSY;
	mmc->ops = &meson_mx_mmc_ops;

	ret = mmc_of_parse(mmc);
	अगर (ret)
		वापस ret;

	ret = mmc_add_host(mmc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_mx_mmc_रेजिस्टर_clks(काष्ठा meson_mx_mmc_host *host)
अणु
	काष्ठा clk_init_data init;
	स्थिर अक्षर *clk_भाग_parent, *clk_fixed_factor_parent;

	clk_fixed_factor_parent = __clk_get_name(host->parent_clk);
	init.name = devm_kaप्र_लिखो(host->controller_dev, GFP_KERNEL,
				   "%s#fixed_factor",
				   dev_name(host->controller_dev));
	अगर (!init.name)
		वापस -ENOMEM;

	init.ops = &clk_fixed_factor_ops;
	init.flags = 0;
	init.parent_names = &clk_fixed_factor_parent;
	init.num_parents = 1;
	host->fixed_factor.भाग = 2;
	host->fixed_factor.mult = 1;
	host->fixed_factor.hw.init = &init;

	host->fixed_factor_clk = devm_clk_रेजिस्टर(host->controller_dev,
						 &host->fixed_factor.hw);
	अगर (WARN_ON(IS_ERR(host->fixed_factor_clk)))
		वापस PTR_ERR(host->fixed_factor_clk);

	clk_भाग_parent = __clk_get_name(host->fixed_factor_clk);
	init.name = devm_kaप्र_लिखो(host->controller_dev, GFP_KERNEL,
				   "%s#div", dev_name(host->controller_dev));
	अगर (!init.name)
		वापस -ENOMEM;

	init.ops = &clk_भागider_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = &clk_भाग_parent;
	init.num_parents = 1;
	host->cfg_भाग.reg = host->base + MESON_MX_SDIO_CONF;
	host->cfg_भाग.shअगरt = MESON_MX_SDIO_CONF_CMD_CLK_DIV_SHIFT;
	host->cfg_भाग.width = MESON_MX_SDIO_CONF_CMD_CLK_DIV_WIDTH;
	host->cfg_भाग.hw.init = &init;
	host->cfg_भाग.flags = CLK_DIVIDER_ALLOW_ZERO;

	host->cfg_भाग_clk = devm_clk_रेजिस्टर(host->controller_dev,
					      &host->cfg_भाग.hw);
	अगर (WARN_ON(IS_ERR(host->cfg_भाग_clk)))
		वापस PTR_ERR(host->cfg_भाग_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_mx_mmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *slot_pdev;
	काष्ठा mmc_host *mmc;
	काष्ठा meson_mx_mmc_host *host;
	पूर्णांक ret, irq;
	u32 conf;

	slot_pdev = meson_mx_mmc_slot_pdev(&pdev->dev);
	अगर (!slot_pdev)
		वापस -ENODEV;
	अन्यथा अगर (IS_ERR(slot_pdev))
		वापस PTR_ERR(slot_pdev);

	mmc = mmc_alloc_host(माप(*host), &slot_pdev->dev);
	अगर (!mmc) अणु
		ret = -ENOMEM;
		जाओ error_unरेजिस्टर_slot_pdev;
	पूर्ण

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->controller_dev = &pdev->dev;

	spin_lock_init(&host->irq_lock);
	समयr_setup(&host->cmd_समयout, meson_mx_mmc_समयout, 0);

	platक्रमm_set_drvdata(pdev, host);

	host->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		जाओ error_मुक्त_mmc;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_thपढ़ोed_irq(host->controller_dev, irq,
					meson_mx_mmc_irq,
					meson_mx_mmc_irq_thपढ़ो, IRQF_ONESHOT,
					शून्य, host);
	अगर (ret)
		जाओ error_मुक्त_mmc;

	host->core_clk = devm_clk_get(host->controller_dev, "core");
	अगर (IS_ERR(host->core_clk)) अणु
		ret = PTR_ERR(host->core_clk);
		जाओ error_मुक्त_mmc;
	पूर्ण

	host->parent_clk = devm_clk_get(host->controller_dev, "clkin");
	अगर (IS_ERR(host->parent_clk)) अणु
		ret = PTR_ERR(host->parent_clk);
		जाओ error_मुक्त_mmc;
	पूर्ण

	ret = meson_mx_mmc_रेजिस्टर_clks(host);
	अगर (ret)
		जाओ error_मुक्त_mmc;

	ret = clk_prepare_enable(host->core_clk);
	अगर (ret) अणु
		dev_err(host->controller_dev, "Failed to enable core clock\n");
		जाओ error_मुक्त_mmc;
	पूर्ण

	ret = clk_prepare_enable(host->cfg_भाग_clk);
	अगर (ret) अणु
		dev_err(host->controller_dev, "Failed to enable MMC clock\n");
		जाओ error_disable_core_clk;
	पूर्ण

	conf = 0;
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_CMD_ARGUMENT_BITS_MASK, 39);
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_M_ENDIAN_MASK, 0x3);
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_WRITE_NWR_MASK, 0x2);
	conf |= FIELD_PREP(MESON_MX_SDIO_CONF_WRITE_CRC_OK_STATUS_MASK, 0x2);
	ग_लिखोl(conf, host->base + MESON_MX_SDIO_CONF);

	meson_mx_mmc_soft_reset(host);

	ret = meson_mx_mmc_add_host(host);
	अगर (ret)
		जाओ error_disable_clks;

	वापस 0;

error_disable_clks:
	clk_disable_unprepare(host->cfg_भाग_clk);
error_disable_core_clk:
	clk_disable_unprepare(host->core_clk);
error_मुक्त_mmc:
	mmc_मुक्त_host(mmc);
error_unरेजिस्टर_slot_pdev:
	of_platक्रमm_device_destroy(&slot_pdev->dev, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक meson_mx_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_mx_mmc_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा device *slot_dev = mmc_dev(host->mmc);

	del_समयr_sync(&host->cmd_समयout);

	mmc_हटाओ_host(host->mmc);

	of_platक्रमm_device_destroy(slot_dev, शून्य);

	clk_disable_unprepare(host->cfg_भाग_clk);
	clk_disable_unprepare(host->core_clk);

	mmc_मुक्त_host(host->mmc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_mx_mmc_of_match[] = अणु
	अणु .compatible = "amlogic,meson8-sdio", पूर्ण,
	अणु .compatible = "amlogic,meson8b-sdio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_mx_mmc_of_match);

अटल काष्ठा platक्रमm_driver meson_mx_mmc_driver = अणु
	.probe   = meson_mx_mmc_probe,
	.हटाओ  = meson_mx_mmc_हटाओ,
	.driver  = अणु
		.name = "meson-mx-sdio",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(meson_mx_mmc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_mx_mmc_driver);

MODULE_DESCRIPTION("Meson6, Meson8 and Meson8b SDIO/MMC Host Driver");
MODULE_AUTHOR("Carlo Caione <carlo@endlessm.com>");
MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_LICENSE("GPL v2");
