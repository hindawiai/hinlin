<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/core/mmc_ops.h
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"
#समावेश "mmc_ops.h"

#घोषणा MMC_BKOPS_TIMEOUT_MS		(120 * 1000) /* 120s */
#घोषणा MMC_CACHE_FLUSH_TIMEOUT_MS	(30 * 1000) /* 30s */
#घोषणा MMC_SANITIZE_TIMEOUT_MS		(240 * 1000) /* 240s */

अटल स्थिर u8 tuning_blk_pattern_4bit[] = अणु
	0xff, 0x0f, 0xff, 0x00, 0xff, 0xcc, 0xc3, 0xcc,
	0xc3, 0x3c, 0xcc, 0xff, 0xfe, 0xff, 0xfe, 0xef,
	0xff, 0xdf, 0xff, 0xdd, 0xff, 0xfb, 0xff, 0xfb,
	0xbf, 0xff, 0x7f, 0xff, 0x77, 0xf7, 0xbd, 0xef,
	0xff, 0xf0, 0xff, 0xf0, 0x0f, 0xfc, 0xcc, 0x3c,
	0xcc, 0x33, 0xcc, 0xcf, 0xff, 0xef, 0xff, 0xee,
	0xff, 0xfd, 0xff, 0xfd, 0xdf, 0xff, 0xbf, 0xff,
	0xbb, 0xff, 0xf7, 0xff, 0xf7, 0x7f, 0x7b, 0xde,
पूर्ण;

अटल स्थिर u8 tuning_blk_pattern_8bit[] = अणु
	0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
	0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc, 0xcc,
	0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff, 0xff,
	0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee, 0xff,
	0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd, 0xdd,
	0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff, 0xbb,
	0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff,
	0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee, 0xff,
	0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00,
	0x00, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc,
	0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff,
	0xff, 0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee,
	0xff, 0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd,
	0xdd, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff,
	0xbb, 0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff,
	0xff, 0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee,
पूर्ण;

पूर्णांक __mmc_send_status(काष्ठा mmc_card *card, u32 *status, अचिन्हित पूर्णांक retries)
अणु
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;

	cmd.opcode = MMC_SEND_STATUS;
	अगर (!mmc_host_is_spi(card->host))
		cmd.arg = card->rca << 16;
	cmd.flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_रुको_क्रम_cmd(card->host, &cmd, retries);
	अगर (err)
		वापस err;

	/* NOTE: callers are required to understand the dअगरference
	 * between "native" and SPI क्रमmat status words!
	 */
	अगर (status)
		*status = cmd.resp[0];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__mmc_send_status);

पूर्णांक mmc_send_status(काष्ठा mmc_card *card, u32 *status)
अणु
	वापस __mmc_send_status(card, status, MMC_CMD_RETRIES);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_send_status);

अटल पूर्णांक _mmc_select_card(काष्ठा mmc_host *host, काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;

	cmd.opcode = MMC_SELECT_CARD;

	अगर (card) अणु
		cmd.arg = card->rca << 16;
		cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;
	पूर्ण अन्यथा अणु
		cmd.arg = 0;
		cmd.flags = MMC_RSP_NONE | MMC_CMD_AC;
	पूर्ण

	वापस mmc_रुको_क्रम_cmd(host, &cmd, MMC_CMD_RETRIES);
पूर्ण

पूर्णांक mmc_select_card(काष्ठा mmc_card *card)
अणु

	वापस _mmc_select_card(card->host, card);
पूर्ण

पूर्णांक mmc_deselect_cards(काष्ठा mmc_host *host)
अणु
	वापस _mmc_select_card(host, शून्य);
पूर्ण

/*
 * Write the value specअगरied in the device tree or board code पूर्णांकo the optional
 * 16 bit Driver Stage Register. This can be used to tune उठाओ/fall बार and
 * drive strength of the DAT and CMD outमाला_दो. The actual meaning of a given
 * value is hardware dependant.
 * The presence of the DSR रेजिस्टर can be determined from the CSD रेजिस्टर,
 * bit 76.
 */
पूर्णांक mmc_set_dsr(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;

	cmd.opcode = MMC_SET_DSR;

	cmd.arg = (host->dsr << 16) | 0xffff;
	cmd.flags = MMC_RSP_NONE | MMC_CMD_AC;

	वापस mmc_रुको_क्रम_cmd(host, &cmd, MMC_CMD_RETRIES);
पूर्ण

पूर्णांक mmc_go_idle(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;

	/*
	 * Non-SPI hosts need to prevent chipselect going active during
	 * GO_IDLE; that would put chips पूर्णांकo SPI mode.  Remind them of
	 * that in हाल of hardware that won't pull up DAT3/nCS otherwise.
	 *
	 * SPI hosts ignore ios.chip_select; it's managed according to
	 * rules that must accommodate non-MMC slaves which this layer
	 * won't even know about.
	 */
	अगर (!mmc_host_is_spi(host)) अणु
		mmc_set_chip_select(host, MMC_CS_HIGH);
		mmc_delay(1);
	पूर्ण

	cmd.opcode = MMC_GO_IDLE_STATE;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_NONE | MMC_CMD_BC;

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);

	mmc_delay(1);

	अगर (!mmc_host_is_spi(host)) अणु
		mmc_set_chip_select(host, MMC_CS_DONTCARE);
		mmc_delay(1);
	पूर्ण

	host->use_spi_crc = 0;

	वापस err;
पूर्ण

पूर्णांक mmc_send_op_cond(काष्ठा mmc_host *host, u32 ocr, u32 *rocr)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक i, err = 0;

	cmd.opcode = MMC_SEND_OP_COND;
	cmd.arg = mmc_host_is_spi(host) ? 0 : ocr;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R3 | MMC_CMD_BCR;

	क्रम (i = 100; i; i--) अणु
		err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
		अगर (err)
			अवरोध;

		/* रुको until reset completes */
		अगर (mmc_host_is_spi(host)) अणु
			अगर (!(cmd.resp[0] & R1_SPI_IDLE))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (cmd.resp[0] & MMC_CARD_BUSY)
				अवरोध;
		पूर्ण

		err = -ETIMEDOUT;

		mmc_delay(10);

		/*
		 * According to eMMC specअगरication v5.1 section 6.4.3, we
		 * should issue CMD1 repeatedly in the idle state until
		 * the eMMC is पढ़ोy. Otherwise some eMMC devices seem to enter
		 * the inactive mode after mmc_init_card() issued CMD0 when
		 * the eMMC device is busy.
		 */
		अगर (!ocr && !mmc_host_is_spi(host))
			cmd.arg = cmd.resp[0] | BIT(30);
	पूर्ण

	अगर (rocr && !mmc_host_is_spi(host))
		*rocr = cmd.resp[0];

	वापस err;
पूर्ण

पूर्णांक mmc_set_relative_addr(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;

	cmd.opcode = MMC_SET_RELATIVE_ADDR;
	cmd.arg = card->rca << 16;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

	वापस mmc_रुको_क्रम_cmd(card->host, &cmd, MMC_CMD_RETRIES);
पूर्ण

अटल पूर्णांक
mmc_send_cxd_native(काष्ठा mmc_host *host, u32 arg, u32 *cxd, पूर्णांक opcode)
अणु
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;

	cmd.opcode = opcode;
	cmd.arg = arg;
	cmd.flags = MMC_RSP_R2 | MMC_CMD_AC;

	err = mmc_रुको_क्रम_cmd(host, &cmd, MMC_CMD_RETRIES);
	अगर (err)
		वापस err;

	स_नकल(cxd, cmd.resp, माप(u32) * 4);

	वापस 0;
पूर्ण

/*
 * NOTE: व्योम *buf, caller क्रम the buf is required to use DMA-capable
 * buffer or on-stack buffer (with some overhead in callee).
 */
अटल पूर्णांक
mmc_send_cxd_data(काष्ठा mmc_card *card, काष्ठा mmc_host *host,
		u32 opcode, व्योम *buf, अचिन्हित len)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा scatterlist sg;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = opcode;
	cmd.arg = 0;

	/* NOTE HACK:  the MMC_RSP_SPI_R1 is always correct here, but we
	 * rely on callers to never use this with "native" calls क्रम पढ़ोing
	 * CSD or CID.  Native versions of those commands use the R2 type,
	 * not R1 plus a data block.
	 */
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = len;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, buf, len);

	अगर (opcode == MMC_SEND_CSD || opcode == MMC_SEND_CID) अणु
		/*
		 * The spec states that CSR and CID accesses have a समयout
		 * of 64 घड़ी cycles.
		 */
		data.समयout_ns = 0;
		data.समयout_clks = 64;
	पूर्ण अन्यथा
		mmc_set_data_समयout(&data, card);

	mmc_रुको_क्रम_req(host, &mrq);

	अगर (cmd.error)
		वापस cmd.error;
	अगर (data.error)
		वापस data.error;

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_spi_send_cxd(काष्ठा mmc_host *host, u32 *cxd, u32 opcode)
अणु
	पूर्णांक ret, i;
	__be32 *cxd_पंचांगp;

	cxd_पंचांगp = kzalloc(16, GFP_KERNEL);
	अगर (!cxd_पंचांगp)
		वापस -ENOMEM;

	ret = mmc_send_cxd_data(शून्य, host, opcode, cxd_पंचांगp, 16);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < 4; i++)
		cxd[i] = be32_to_cpu(cxd_पंचांगp[i]);

err:
	kमुक्त(cxd_पंचांगp);
	वापस ret;
पूर्ण

पूर्णांक mmc_send_csd(काष्ठा mmc_card *card, u32 *csd)
अणु
	अगर (mmc_host_is_spi(card->host))
		वापस mmc_spi_send_cxd(card->host, csd, MMC_SEND_CSD);

	वापस mmc_send_cxd_native(card->host, card->rca << 16,	csd,
				MMC_SEND_CSD);
पूर्ण

पूर्णांक mmc_send_cid(काष्ठा mmc_host *host, u32 *cid)
अणु
	अगर (mmc_host_is_spi(host))
		वापस mmc_spi_send_cxd(host, cid, MMC_SEND_CID);

	वापस mmc_send_cxd_native(host, 0, cid, MMC_ALL_SEND_CID);
पूर्ण

पूर्णांक mmc_get_ext_csd(काष्ठा mmc_card *card, u8 **new_ext_csd)
अणु
	पूर्णांक err;
	u8 *ext_csd;

	अगर (!card || !new_ext_csd)
		वापस -EINVAL;

	अगर (!mmc_can_ext_csd(card))
		वापस -EOPNOTSUPP;

	/*
	 * As the ext_csd is so large and mostly unused, we करोn't store the
	 * raw block in mmc_card.
	 */
	ext_csd = kzalloc(512, GFP_KERNEL);
	अगर (!ext_csd)
		वापस -ENOMEM;

	err = mmc_send_cxd_data(card, card->host, MMC_SEND_EXT_CSD, ext_csd,
				512);
	अगर (err)
		kमुक्त(ext_csd);
	अन्यथा
		*new_ext_csd = ext_csd;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_get_ext_csd);

पूर्णांक mmc_spi_पढ़ो_ocr(काष्ठा mmc_host *host, पूर्णांक highcap, u32 *ocrp)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक err;

	cmd.opcode = MMC_SPI_READ_OCR;
	cmd.arg = highcap ? (1 << 30) : 0;
	cmd.flags = MMC_RSP_SPI_R3;

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);

	*ocrp = cmd.resp[1];
	वापस err;
पूर्ण

पूर्णांक mmc_spi_set_crc(काष्ठा mmc_host *host, पूर्णांक use_crc)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक err;

	cmd.opcode = MMC_SPI_CRC_ON_OFF;
	cmd.flags = MMC_RSP_SPI_R1;
	cmd.arg = use_crc;

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
	अगर (!err)
		host->use_spi_crc = use_crc;
	वापस err;
पूर्ण

अटल पूर्णांक mmc_चयन_status_error(काष्ठा mmc_host *host, u32 status)
अणु
	अगर (mmc_host_is_spi(host)) अणु
		अगर (status & R1_SPI_ILLEGAL_COMMAND)
			वापस -EBADMSG;
	पूर्ण अन्यथा अणु
		अगर (R1_STATUS(status))
			pr_warn("%s: unexpected status %#x after switch\n",
				mmc_hostname(host), status);
		अगर (status & R1_SWITCH_ERROR)
			वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

/* Caller must hold re-tuning */
पूर्णांक mmc_चयन_status(काष्ठा mmc_card *card, bool crc_err_fatal)
अणु
	u32 status;
	पूर्णांक err;

	err = mmc_send_status(card, &status);
	अगर (!crc_err_fatal && err == -EILSEQ)
		वापस 0;
	अगर (err)
		वापस err;

	वापस mmc_चयन_status_error(card->host, status);
पूर्ण

अटल पूर्णांक mmc_busy_status(काष्ठा mmc_card *card, bool retry_crc_err,
			   क्रमागत mmc_busy_cmd busy_cmd, bool *busy)
अणु
	काष्ठा mmc_host *host = card->host;
	u32 status = 0;
	पूर्णांक err;

	अगर (host->ops->card_busy) अणु
		*busy = host->ops->card_busy(host);
		वापस 0;
	पूर्ण

	err = mmc_send_status(card, &status);
	अगर (retry_crc_err && err == -EILSEQ) अणु
		*busy = true;
		वापस 0;
	पूर्ण
	अगर (err)
		वापस err;

	चयन (busy_cmd) अणु
	हाल MMC_BUSY_CMD6:
		err = mmc_चयन_status_error(card->host, status);
		अवरोध;
	हाल MMC_BUSY_ERASE:
		err = R1_STATUS(status) ? -EIO : 0;
		अवरोध;
	हाल MMC_BUSY_HPI:
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	अगर (err)
		वापस err;

	*busy = !mmc_पढ़ोy_क्रम_data(status);
	वापस 0;
पूर्ण

अटल पूर्णांक __mmc_poll_क्रम_busy(काष्ठा mmc_card *card, अचिन्हित पूर्णांक समयout_ms,
			       bool send_status, bool retry_crc_err,
			       क्रमागत mmc_busy_cmd busy_cmd)
अणु
	काष्ठा mmc_host *host = card->host;
	पूर्णांक err;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक udelay = 32, udelay_max = 32768;
	bool expired = false;
	bool busy = false;

	/*
	 * In हालs when not allowed to poll by using CMD13 or because we aren't
	 * capable of polling by using ->card_busy(), then rely on रुकोing the
	 * stated समयout to be sufficient.
	 */
	अगर (!send_status && !host->ops->card_busy) अणु
		mmc_delay(समयout_ms);
		वापस 0;
	पूर्ण

	समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms) + 1;
	करो अणु
		/*
		 * Due to the possibility of being preempted जबतक polling,
		 * check the expiration समय first.
		 */
		expired = समय_after(jअगरfies, समयout);

		err = mmc_busy_status(card, retry_crc_err, busy_cmd, &busy);
		अगर (err)
			वापस err;

		/* Timeout अगर the device still reमुख्यs busy. */
		अगर (expired && busy) अणु
			pr_err("%s: Card stuck being busy! %s\n",
				mmc_hostname(host), __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		/* Throttle the polling rate to aव्योम hogging the CPU. */
		अगर (busy) अणु
			usleep_range(udelay, udelay * 2);
			अगर (udelay < udelay_max)
				udelay *= 2;
		पूर्ण
	पूर्ण जबतक (busy);

	वापस 0;
पूर्ण

पूर्णांक mmc_poll_क्रम_busy(काष्ठा mmc_card *card, अचिन्हित पूर्णांक समयout_ms,
		      क्रमागत mmc_busy_cmd busy_cmd)
अणु
	वापस __mmc_poll_क्रम_busy(card, समयout_ms, true, false, busy_cmd);
पूर्ण

/**
 *	__mmc_चयन - modअगरy EXT_CSD रेजिस्टर
 *	@card: the MMC card associated with the data transfer
 *	@set: cmd set values
 *	@index: EXT_CSD रेजिस्टर index
 *	@value: value to program पूर्णांकo EXT_CSD रेजिस्टर
 *	@समयout_ms: समयout (ms) क्रम operation perक्रमmed by रेजिस्टर ग_लिखो,
 *                   समयout of zero implies maximum possible समयout
 *	@timing: new timing to change to
 *	@send_status: send status cmd to poll क्रम busy
 *	@retry_crc_err: retry when CRC errors when polling with CMD13 क्रम busy
 *	@retries: number of retries
 *
 *	Modअगरies the EXT_CSD रेजिस्टर क्रम selected card.
 */
पूर्णांक __mmc_चयन(काष्ठा mmc_card *card, u8 set, u8 index, u8 value,
		अचिन्हित पूर्णांक समयout_ms, अचिन्हित अक्षर timing,
		bool send_status, bool retry_crc_err, अचिन्हित पूर्णांक retries)
अणु
	काष्ठा mmc_host *host = card->host;
	पूर्णांक err;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	bool use_r1b_resp = true;
	अचिन्हित अक्षर old_timing = host->ios.timing;

	mmc_retune_hold(host);

	अगर (!समयout_ms) अणु
		pr_warn("%s: unspecified timeout for CMD6 - use generic\n",
			mmc_hostname(host));
		समयout_ms = card->ext_csd.generic_cmd6_समय;
	पूर्ण

	/*
	 * If the max_busy_समयout of the host is specअगरied, make sure it's
	 * enough to fit the used समयout_ms. In हाल it's not, let's inकाष्ठा
	 * the host to aव्योम HW busy detection, by converting to a R1 response
	 * instead of a R1B. Note, some hosts requires R1B, which also means
	 * they are on their own when it comes to deal with the busy समयout.
	 */
	अगर (!(host->caps & MMC_CAP_NEED_RSP_BUSY) && host->max_busy_समयout &&
	    (समयout_ms > host->max_busy_समयout))
		use_r1b_resp = false;

	cmd.opcode = MMC_SWITCH;
	cmd.arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
		  (index << 16) |
		  (value << 8) |
		  set;
	cmd.flags = MMC_CMD_AC;
	अगर (use_r1b_resp) अणु
		cmd.flags |= MMC_RSP_SPI_R1B | MMC_RSP_R1B;
		cmd.busy_समयout = समयout_ms;
	पूर्ण अन्यथा अणु
		cmd.flags |= MMC_RSP_SPI_R1 | MMC_RSP_R1;
	पूर्ण

	err = mmc_रुको_क्रम_cmd(host, &cmd, retries);
	अगर (err)
		जाओ out;

	/*If SPI or used HW busy detection above, then we करोn't need to poll. */
	अगर (((host->caps & MMC_CAP_WAIT_WHILE_BUSY) && use_r1b_resp) ||
		mmc_host_is_spi(host))
		जाओ out_tim;

	/* Let's try to poll to find out when the command is completed. */
	err = __mmc_poll_क्रम_busy(card, समयout_ms, send_status, retry_crc_err,
				  MMC_BUSY_CMD6);
	अगर (err)
		जाओ out;

out_tim:
	/* Switch to new timing beक्रमe check चयन status. */
	अगर (timing)
		mmc_set_timing(host, timing);

	अगर (send_status) अणु
		err = mmc_चयन_status(card, true);
		अगर (err && timing)
			mmc_set_timing(host, old_timing);
	पूर्ण
out:
	mmc_retune_release(host);

	वापस err;
पूर्ण

पूर्णांक mmc_चयन(काष्ठा mmc_card *card, u8 set, u8 index, u8 value,
		अचिन्हित पूर्णांक समयout_ms)
अणु
	वापस __mmc_चयन(card, set, index, value, समयout_ms, 0,
			    true, false, MMC_CMD_RETRIES);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_चयन);

पूर्णांक mmc_send_tuning(काष्ठा mmc_host *host, u32 opcode, पूर्णांक *cmd_error)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा scatterlist sg;
	काष्ठा mmc_ios *ios = &host->ios;
	स्थिर u8 *tuning_block_pattern;
	पूर्णांक size, err = 0;
	u8 *data_buf;

	अगर (ios->bus_width == MMC_BUS_WIDTH_8) अणु
		tuning_block_pattern = tuning_blk_pattern_8bit;
		size = माप(tuning_blk_pattern_8bit);
	पूर्ण अन्यथा अगर (ios->bus_width == MMC_BUS_WIDTH_4) अणु
		tuning_block_pattern = tuning_blk_pattern_4bit;
		size = माप(tuning_blk_pattern_4bit);
	पूर्ण अन्यथा
		वापस -EINVAL;

	data_buf = kzalloc(size, GFP_KERNEL);
	अगर (!data_buf)
		वापस -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = opcode;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = size;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;

	/*
	 * According to the tuning specs, Tuning process
	 * is normally लघुer 40 executions of CMD19,
	 * and समयout value should be लघुer than 150 ms
	 */
	data.समयout_ns = 150 * NSEC_PER_MSEC;

	data.sg = &sg;
	data.sg_len = 1;
	sg_init_one(&sg, data_buf, size);

	mmc_रुको_क्रम_req(host, &mrq);

	अगर (cmd_error)
		*cmd_error = cmd.error;

	अगर (cmd.error) अणु
		err = cmd.error;
		जाओ out;
	पूर्ण

	अगर (data.error) अणु
		err = data.error;
		जाओ out;
	पूर्ण

	अगर (स_भेद(data_buf, tuning_block_pattern, size))
		err = -EIO;

out:
	kमुक्त(data_buf);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_send_tuning);

पूर्णांक mmc_पात_tuning(काष्ठा mmc_host *host, u32 opcode)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;

	/*
	 * eMMC specअगरication specअगरies that CMD12 can be used to stop a tuning
	 * command, but SD specअगरication करोes not, so करो nothing unless it is
	 * eMMC.
	 */
	अगर (opcode != MMC_SEND_TUNING_BLOCK_HS200)
		वापस 0;

	cmd.opcode = MMC_STOP_TRANSMISSION;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;

	/*
	 * For drivers that override R1 to R1b, set an arbitrary समयout based
	 * on the tuning समयout i.e. 150ms.
	 */
	cmd.busy_समयout = 150;

	वापस mmc_रुको_क्रम_cmd(host, &cmd, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_पात_tuning);

अटल पूर्णांक
mmc_send_bus_test(काष्ठा mmc_card *card, काष्ठा mmc_host *host, u8 opcode,
		  u8 len)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;
	काष्ठा scatterlist sg;
	u8 *data_buf;
	u8 *test_buf;
	पूर्णांक i, err;
	अटल u8 testdata_8bit[8] = अणु 0x55, 0xaa, 0, 0, 0, 0, 0, 0 पूर्ण;
	अटल u8 testdata_4bit[4] = अणु 0x5a, 0, 0, 0 पूर्ण;

	/* dma onto stack is unsafe/nonportable, but callers to this
	 * routine normally provide temporary on-stack buffers ...
	 */
	data_buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!data_buf)
		वापस -ENOMEM;

	अगर (len == 8)
		test_buf = testdata_8bit;
	अन्यथा अगर (len == 4)
		test_buf = testdata_4bit;
	अन्यथा अणु
		pr_err("%s: Invalid bus_width %d\n",
		       mmc_hostname(host), len);
		kमुक्त(data_buf);
		वापस -EINVAL;
	पूर्ण

	अगर (opcode == MMC_BUS_TEST_W)
		स_नकल(data_buf, test_buf, len);

	mrq.cmd = &cmd;
	mrq.data = &data;
	cmd.opcode = opcode;
	cmd.arg = 0;

	/* NOTE HACK:  the MMC_RSP_SPI_R1 is always correct here, but we
	 * rely on callers to never use this with "native" calls क्रम पढ़ोing
	 * CSD or CID.  Native versions of those commands use the R2 type,
	 * not R1 plus a data block.
	 */
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = len;
	data.blocks = 1;
	अगर (opcode == MMC_BUS_TEST_R)
		data.flags = MMC_DATA_READ;
	अन्यथा
		data.flags = MMC_DATA_WRITE;

	data.sg = &sg;
	data.sg_len = 1;
	mmc_set_data_समयout(&data, card);
	sg_init_one(&sg, data_buf, len);
	mmc_रुको_क्रम_req(host, &mrq);
	err = 0;
	अगर (opcode == MMC_BUS_TEST_R) अणु
		क्रम (i = 0; i < len / 4; i++)
			अगर ((test_buf[i] ^ data_buf[i]) != 0xff) अणु
				err = -EIO;
				अवरोध;
			पूर्ण
	पूर्ण
	kमुक्त(data_buf);

	अगर (cmd.error)
		वापस cmd.error;
	अगर (data.error)
		वापस data.error;

	वापस err;
पूर्ण

पूर्णांक mmc_bus_test(काष्ठा mmc_card *card, u8 bus_width)
अणु
	पूर्णांक width;

	अगर (bus_width == MMC_BUS_WIDTH_8)
		width = 8;
	अन्यथा अगर (bus_width == MMC_BUS_WIDTH_4)
		width = 4;
	अन्यथा अगर (bus_width == MMC_BUS_WIDTH_1)
		वापस 0; /* no need क्रम test */
	अन्यथा
		वापस -EINVAL;

	/*
	 * Ignore errors from BUS_TEST_W.  BUS_TEST_R will fail अगर there
	 * is a problem.  This improves chances that the test will work.
	 */
	mmc_send_bus_test(card, card->host, MMC_BUS_TEST_W, width);
	वापस mmc_send_bus_test(card, card->host, MMC_BUS_TEST_R, width);
पूर्ण

अटल पूर्णांक mmc_send_hpi_cmd(काष्ठा mmc_card *card)
अणु
	अचिन्हित पूर्णांक busy_समयout_ms = card->ext_csd.out_of_पूर्णांक_समय;
	काष्ठा mmc_host *host = card->host;
	bool use_r1b_resp = true;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक err;

	cmd.opcode = card->ext_csd.hpi_cmd;
	cmd.arg = card->rca << 16 | 1;

	/*
	 * Make sure the host's max_busy_समयout fit the needed समयout क्रम HPI.
	 * In हाल it करोesn't, let's inकाष्ठा the host to aव्योम HW busy
	 * detection, by using a R1 response instead of R1B.
	 */
	अगर (host->max_busy_समयout && busy_समयout_ms > host->max_busy_समयout)
		use_r1b_resp = false;

	अगर (cmd.opcode == MMC_STOP_TRANSMISSION && use_r1b_resp) अणु
		cmd.flags = MMC_RSP_R1B | MMC_CMD_AC;
		cmd.busy_समयout = busy_समयout_ms;
	पूर्ण अन्यथा अणु
		cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;
		use_r1b_resp = false;
	पूर्ण

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
	अगर (err) अणु
		pr_warn("%s: HPI error %d. Command response %#x\n",
			mmc_hostname(host), err, cmd.resp[0]);
		वापस err;
	पूर्ण

	/* No need to poll when using HW busy detection. */
	अगर (host->caps & MMC_CAP_WAIT_WHILE_BUSY && use_r1b_resp)
		वापस 0;

	/* Let's poll to find out when the HPI request completes. */
	वापस mmc_poll_क्रम_busy(card, busy_समयout_ms, MMC_BUSY_HPI);
पूर्ण

/**
 *	mmc_पूर्णांकerrupt_hpi - Issue क्रम High priority Interrupt
 *	@card: the MMC card associated with the HPI transfer
 *
 *	Issued High Priority Interrupt, and check क्रम card status
 *	until out-of prg-state.
 */
अटल पूर्णांक mmc_पूर्णांकerrupt_hpi(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;
	u32 status;

	अगर (!card->ext_csd.hpi_en) अणु
		pr_info("%s: HPI enable bit unset\n", mmc_hostname(card->host));
		वापस 1;
	पूर्ण

	err = mmc_send_status(card, &status);
	अगर (err) अणु
		pr_err("%s: Get card status fail\n", mmc_hostname(card->host));
		जाओ out;
	पूर्ण

	चयन (R1_CURRENT_STATE(status)) अणु
	हाल R1_STATE_IDLE:
	हाल R1_STATE_READY:
	हाल R1_STATE_STBY:
	हाल R1_STATE_TRAN:
		/*
		 * In idle and transfer states, HPI is not needed and the caller
		 * can issue the next पूर्णांकended command immediately
		 */
		जाओ out;
	हाल R1_STATE_PRG:
		अवरोध;
	शेष:
		/* In all other states, it's illegal to issue HPI */
		pr_debug("%s: HPI cannot be sent. Card state=%d\n",
			mmc_hostname(card->host), R1_CURRENT_STATE(status));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = mmc_send_hpi_cmd(card);
out:
	वापस err;
पूर्ण

पूर्णांक mmc_can_ext_csd(काष्ठा mmc_card *card)
अणु
	वापस (card && card->csd.mmca_vsn > CSD_SPEC_VER_3);
पूर्ण

अटल पूर्णांक mmc_पढ़ो_bkops_status(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;
	u8 *ext_csd;

	err = mmc_get_ext_csd(card, &ext_csd);
	अगर (err)
		वापस err;

	card->ext_csd.raw_bkops_status = ext_csd[EXT_CSD_BKOPS_STATUS];
	card->ext_csd.raw_exception_status = ext_csd[EXT_CSD_EXP_EVENTS_STATUS];
	kमुक्त(ext_csd);
	वापस 0;
पूर्ण

/**
 *	mmc_run_bkops - Run BKOPS क्रम supported cards
 *	@card: MMC card to run BKOPS क्रम
 *
 *	Run background operations synchronously क्रम cards having manual BKOPS
 *	enabled and in हाल it reports urgent BKOPS level.
*/
व्योम mmc_run_bkops(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;

	अगर (!card->ext_csd.man_bkops_en)
		वापस;

	err = mmc_पढ़ो_bkops_status(card);
	अगर (err) अणु
		pr_err("%s: Failed to read bkops status: %d\n",
		       mmc_hostname(card->host), err);
		वापस;
	पूर्ण

	अगर (!card->ext_csd.raw_bkops_status ||
	    card->ext_csd.raw_bkops_status < EXT_CSD_BKOPS_LEVEL_2)
		वापस;

	mmc_retune_hold(card->host);

	/*
	 * For urgent BKOPS status, LEVEL_2 and higher, let's execute
	 * synchronously. Future wise, we may consider to start BKOPS, क्रम less
	 * urgent levels by using an asynchronous background task, when idle.
	 */
	err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			 EXT_CSD_BKOPS_START, 1, MMC_BKOPS_TIMEOUT_MS);
	अगर (err)
		pr_warn("%s: Error %d starting bkops\n",
			mmc_hostname(card->host), err);

	mmc_retune_release(card->host);
पूर्ण
EXPORT_SYMBOL(mmc_run_bkops);

/*
 * Flush the cache to the non-अस्थिर storage.
 */
पूर्णांक mmc_flush_cache(काष्ठा mmc_card *card)
अणु
	पूर्णांक err = 0;

	अगर (mmc_cache_enabled(card->host)) अणु
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_FLUSH_CACHE, 1,
				 MMC_CACHE_FLUSH_TIMEOUT_MS);
		अगर (err)
			pr_err("%s: cache flush error %d\n",
					mmc_hostname(card->host), err);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(mmc_flush_cache);

अटल पूर्णांक mmc_cmdq_चयन(काष्ठा mmc_card *card, bool enable)
अणु
	u8 val = enable ? EXT_CSD_CMDQ_MODE_ENABLED : 0;
	पूर्णांक err;

	अगर (!card->ext_csd.cmdq_support)
		वापस -EOPNOTSUPP;

	err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_CMDQ_MODE_EN,
			 val, card->ext_csd.generic_cmd6_समय);
	अगर (!err)
		card->ext_csd.cmdq_en = enable;

	वापस err;
पूर्ण

पूर्णांक mmc_cmdq_enable(काष्ठा mmc_card *card)
अणु
	वापस mmc_cmdq_चयन(card, true);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_cmdq_enable);

पूर्णांक mmc_cmdq_disable(काष्ठा mmc_card *card)
अणु
	वापस mmc_cmdq_चयन(card, false);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_cmdq_disable);

पूर्णांक mmc_sanitize(काष्ठा mmc_card *card, अचिन्हित पूर्णांक समयout_ms)
अणु
	काष्ठा mmc_host *host = card->host;
	पूर्णांक err;

	अगर (!mmc_can_sanitize(card)) अणु
		pr_warn("%s: Sanitize not supported\n", mmc_hostname(host));
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!समयout_ms)
		समयout_ms = MMC_SANITIZE_TIMEOUT_MS;

	pr_debug("%s: Sanitize in progress...\n", mmc_hostname(host));

	mmc_retune_hold(host);

	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_SANITIZE_START,
			   1, समयout_ms, 0, true, false, 0);
	अगर (err)
		pr_err("%s: Sanitize failed err=%d\n", mmc_hostname(host), err);

	/*
	 * If the sanitize operation समयd out, the card is probably still busy
	 * in the R1_STATE_PRG. Rather than जारी to रुको, let's try to पात
	 * it with a HPI command to get back पूर्णांकo R1_STATE_TRAN.
	 */
	अगर (err == -ETIMEDOUT && !mmc_पूर्णांकerrupt_hpi(card))
		pr_warn("%s: Sanitize aborted\n", mmc_hostname(host));

	mmc_retune_release(host);

	pr_debug("%s: Sanitize completed\n", mmc_hostname(host));
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_sanitize);
