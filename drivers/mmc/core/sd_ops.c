<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/core/sd_ops.h
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/scatterlist.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>

#समावेश "core.h"
#समावेश "sd_ops.h"

पूर्णांक mmc_app_cmd(काष्ठा mmc_host *host, काष्ठा mmc_card *card)
अणु
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;

	अगर (WARN_ON(card && card->host != host))
		वापस -EINVAL;

	cmd.opcode = MMC_APP_CMD;

	अगर (card) अणु
		cmd.arg = card->rca << 16;
		cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	पूर्ण अन्यथा अणु
		cmd.arg = 0;
		cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_BCR;
	पूर्ण

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
	अगर (err)
		वापस err;

	/* Check that card supported application commands */
	अगर (!mmc_host_is_spi(host) && !(cmd.resp[0] & R1_APP_CMD))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_app_cmd);

अटल पूर्णांक mmc_रुको_क्रम_app_cmd(काष्ठा mmc_host *host, काष्ठा mmc_card *card,
				काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	पूर्णांक i, err = -EIO;

	/*
	 * We have to resend MMC_APP_CMD क्रम each attempt so
	 * we cannot use the retries field in mmc_command.
	 */
	क्रम (i = 0; i <= MMC_CMD_RETRIES; i++) अणु
		err = mmc_app_cmd(host, card);
		अगर (err) अणु
			/* no poपूर्णांक in retrying; no APP commands allowed */
			अगर (mmc_host_is_spi(host)) अणु
				अगर (cmd->resp[0] & R1_SPI_ILLEGAL_COMMAND)
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		स_रखो(&mrq, 0, माप(काष्ठा mmc_request));

		स_रखो(cmd->resp, 0, माप(cmd->resp));
		cmd->retries = 0;

		mrq.cmd = cmd;
		cmd->data = शून्य;

		mmc_रुको_क्रम_req(host, &mrq);

		err = cmd->error;
		अगर (!cmd->error)
			अवरोध;

		/* no poपूर्णांक in retrying illegal APP commands */
		अगर (mmc_host_is_spi(host)) अणु
			अगर (cmd->resp[0] & R1_SPI_ILLEGAL_COMMAND)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mmc_app_set_bus_width(काष्ठा mmc_card *card, पूर्णांक width)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;

	cmd.opcode = SD_APP_SET_BUS_WIDTH;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

	चयन (width) अणु
	हाल MMC_BUS_WIDTH_1:
		cmd.arg = SD_BUS_WIDTH_1;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		cmd.arg = SD_BUS_WIDTH_4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mmc_रुको_क्रम_app_cmd(card->host, card, &cmd);
पूर्ण

पूर्णांक mmc_send_app_op_cond(काष्ठा mmc_host *host, u32 ocr, u32 *rocr)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक i, err = 0;

	cmd.opcode = SD_APP_OP_COND;
	अगर (mmc_host_is_spi(host))
		cmd.arg = ocr & (1 << 30); /* SPI only defines one bit */
	अन्यथा
		cmd.arg = ocr;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R3 | MMC_CMD_BCR;

	क्रम (i = 100; i; i--) अणु
		err = mmc_रुको_क्रम_app_cmd(host, शून्य, &cmd);
		अगर (err)
			अवरोध;

		/* अगर we're just probing, करो a single pass */
		अगर (ocr == 0)
			अवरोध;

		/* otherwise रुको until reset completes */
		अगर (mmc_host_is_spi(host)) अणु
			अगर (!(cmd.resp[0] & R1_SPI_IDLE))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (cmd.resp[0] & MMC_CARD_BUSY)
				अवरोध;
		पूर्ण

		err = -ETIMEDOUT;

		mmc_delay(10);
	पूर्ण

	अगर (!i)
		pr_err("%s: card never left busy state\n", mmc_hostname(host));

	अगर (rocr && !mmc_host_is_spi(host))
		*rocr = cmd.resp[0];

	वापस err;
पूर्ण

अटल पूर्णांक __mmc_send_अगर_cond(काष्ठा mmc_host *host, u32 ocr, u8 pcie_bits,
			      u32 *resp)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक err;
	अटल स्थिर u8 test_pattern = 0xAA;
	u8 result_pattern;

	/*
	 * To support SD 2.0 cards, we must always invoke SD_SEND_IF_COND
	 * beक्रमe SD_APP_OP_COND. This command will harmlessly fail क्रम
	 * SD 1.0 cards.
	 */
	cmd.opcode = SD_SEND_IF_COND;
	cmd.arg = ((ocr & 0xFF8000) != 0) << 8 | pcie_bits << 8 | test_pattern;
	cmd.flags = MMC_RSP_SPI_R7 | MMC_RSP_R7 | MMC_CMD_BCR;

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
	अगर (err)
		वापस err;

	अगर (mmc_host_is_spi(host))
		result_pattern = cmd.resp[1] & 0xFF;
	अन्यथा
		result_pattern = cmd.resp[0] & 0xFF;

	अगर (result_pattern != test_pattern)
		वापस -EIO;

	अगर (resp)
		*resp = cmd.resp[0];

	वापस 0;
पूर्ण

पूर्णांक mmc_send_अगर_cond(काष्ठा mmc_host *host, u32 ocr)
अणु
	वापस __mmc_send_अगर_cond(host, ocr, 0, शून्य);
पूर्ण

पूर्णांक mmc_send_अगर_cond_pcie(काष्ठा mmc_host *host, u32 ocr)
अणु
	u32 resp = 0;
	u8 pcie_bits = 0;
	पूर्णांक ret;

	अगर (host->caps2 & MMC_CAP2_SD_EXP) अणु
		/* Probe card क्रम SD express support via PCIe. */
		pcie_bits = 0x10;
		अगर (host->caps2 & MMC_CAP2_SD_EXP_1_2V)
			/* Probe also क्रम 1.2V support. */
			pcie_bits = 0x30;
	पूर्ण

	ret = __mmc_send_अगर_cond(host, ocr, pcie_bits, &resp);
	अगर (ret)
		वापस 0;

	/* Continue with the SD express init, अगर the card supports it. */
	resp &= 0x3000;
	अगर (pcie_bits && resp) अणु
		अगर (resp == 0x3000)
			host->ios.timing = MMC_TIMING_SD_EXP_1_2V;
		अन्यथा
			host->ios.timing = MMC_TIMING_SD_EXP;

		/*
		 * According to the spec the घड़ी shall also be gated, but
		 * let's leave this to the host driver क्रम more flexibility.
		 */
		वापस host->ops->init_sd_express(host, &host->ios);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mmc_send_relative_addr(काष्ठा mmc_host *host, अचिन्हित पूर्णांक *rca)
अणु
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;

	cmd.opcode = SD_SEND_RELATIVE_ADDR;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R6 | MMC_CMD_BCR;

	err = mmc_रुको_क्रम_cmd(host, &cmd, MMC_CMD_RETRIES);
	अगर (err)
		वापस err;

	*rca = cmd.resp[0] >> 16;

	वापस 0;
पूर्ण

पूर्णांक mmc_app_send_scr(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा scatterlist sg;
	__be32 *scr;

	/* NOTE: caller guarantees scr is heap-allocated */

	err = mmc_app_cmd(card->host, card);
	अगर (err)
		वापस err;

	/* dma onto stack is unsafe/nonportable, but callers to this
	 * routine normally provide temporary on-stack buffers ...
	 */
	scr = kदो_स्मृति(माप(card->raw_scr), GFP_KERNEL);
	अगर (!scr)
		वापस -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_APP_SEND_SCR;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 8;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, scr, 8);

	mmc_set_data_समयout(&data, card);

	mmc_रुको_क्रम_req(card->host, &mrq);

	card->raw_scr[0] = be32_to_cpu(scr[0]);
	card->raw_scr[1] = be32_to_cpu(scr[1]);

	kमुक्त(scr);

	अगर (cmd.error)
		वापस cmd.error;
	अगर (data.error)
		वापस data.error;

	वापस 0;
पूर्ण

पूर्णांक mmc_sd_चयन(काष्ठा mmc_card *card, पूर्णांक mode, पूर्णांक group,
	u8 value, u8 *resp)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा scatterlist sg;

	/* NOTE: caller guarantees resp is heap-allocated */

	mode = !!mode;
	value &= 0xF;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_SWITCH;
	cmd.arg = mode << 31 | 0x00FFFFFF;
	cmd.arg &= ~(0xF << (group * 4));
	cmd.arg |= value << (group * 4);
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, resp, 64);

	mmc_set_data_समयout(&data, card);

	mmc_रुको_क्रम_req(card->host, &mrq);

	अगर (cmd.error)
		वापस cmd.error;
	अगर (data.error)
		वापस data.error;

	वापस 0;
पूर्ण

पूर्णांक mmc_app_sd_status(काष्ठा mmc_card *card, व्योम *ssr)
अणु
	पूर्णांक err;
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा scatterlist sg;

	/* NOTE: caller guarantees ssr is heap-allocated */

	err = mmc_app_cmd(card->host, card);
	अगर (err)
		वापस err;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_APP_SD_STATUS;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, ssr, 64);

	mmc_set_data_समयout(&data, card);

	mmc_रुको_क्रम_req(card->host, &mrq);

	अगर (cmd.error)
		वापस cmd.error;
	अगर (data.error)
		वापस data.error;

	वापस 0;
पूर्ण
