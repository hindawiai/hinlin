<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/core/core.c
 *
 *  Copyright (C) 2003-2004 Russell King, All Rights Reserved.
 *  SD support Copyright (C) 2004 Ian Molton, All Rights Reserved.
 *  Copyright (C) 2005-2008 Pierre Ossman, All Rights Reserved.
 *  MMCv4 support Copyright (C) 2006 Philip Langdale, All Rights Reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/err.h>
#समावेश <linux/leds.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/log2.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/suspend.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/slot-gpपन.स>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/mmc.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "crypto.h"
#समावेश "bus.h"
#समावेश "host.h"
#समावेश "sdio_bus.h"
#समावेश "pwrseq.h"

#समावेश "mmc_ops.h"
#समावेश "sd_ops.h"
#समावेश "sdio_ops.h"

/* The max erase समयout, used when host->max_busy_समयout isn't specअगरied */
#घोषणा MMC_ERASE_TIMEOUT_MS	(60 * 1000) /* 60 s */
#घोषणा SD_DISCARD_TIMEOUT_MS	(250)

अटल स्थिर अचिन्हित freqs[] = अणु 400000, 300000, 200000, 100000 पूर्ण;

/*
 * Enabling software CRCs on the data blocks can be a signअगरicant (30%)
 * perक्रमmance cost, and क्रम other reasons may not always be desired.
 * So we allow it it to be disabled.
 */
bool use_spi_crc = 1;
module_param(use_spi_crc, bool, 0);

अटल पूर्णांक mmc_schedule_delayed_work(काष्ठा delayed_work *work,
				     अचिन्हित दीर्घ delay)
अणु
	/*
	 * We use the प्रणाली_मुक्तzable_wq, because of two reasons.
	 * First, it allows several works (not the same work item) to be
	 * executed simultaneously. Second, the queue becomes frozen when
	 * userspace becomes frozen during प्रणाली PM.
	 */
	वापस queue_delayed_work(प्रणाली_मुक्तzable_wq, work, delay);
पूर्ण

#अगर_घोषित CONFIG_FAIL_MMC_REQUEST

/*
 * Internal function. Inject अक्रमom data errors.
 * If mmc_data is शून्य no errors are injected.
 */
अटल व्योम mmc_should_fail_request(काष्ठा mmc_host *host,
				    काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;
	अटल स्थिर पूर्णांक data_errors[] = अणु
		-ETIMEDOUT,
		-EILSEQ,
		-EIO,
	पूर्ण;

	अगर (!data)
		वापस;

	अगर ((cmd && cmd->error) || data->error ||
	    !should_fail(&host->fail_mmc_request, data->blksz * data->blocks))
		वापस;

	data->error = data_errors[pअक्रमom_u32() % ARRAY_SIZE(data_errors)];
	data->bytes_xfered = (pअक्रमom_u32() % (data->bytes_xfered >> 9)) << 9;
पूर्ण

#अन्यथा /* CONFIG_FAIL_MMC_REQUEST */

अटल अंतरभूत व्योम mmc_should_fail_request(काष्ठा mmc_host *host,
					   काष्ठा mmc_request *mrq)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_FAIL_MMC_REQUEST */

अटल अंतरभूत व्योम mmc_complete_cmd(काष्ठा mmc_request *mrq)
अणु
	अगर (mrq->cap_cmd_during_tfr && !completion_करोne(&mrq->cmd_completion))
		complete_all(&mrq->cmd_completion);
पूर्ण

व्योम mmc_command_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	अगर (!mrq->cap_cmd_during_tfr)
		वापस;

	mmc_complete_cmd(mrq);

	pr_debug("%s: cmd done, tfr ongoing (CMD%u)\n",
		 mmc_hostname(host), mrq->cmd->opcode);
पूर्ण
EXPORT_SYMBOL(mmc_command_करोne);

/**
 *	mmc_request_करोne - finish processing an MMC request
 *	@host: MMC host which completed request
 *	@mrq: MMC request which request
 *
 *	MMC drivers should call this function when they have completed
 *	their processing of a request.
 */
व्योम mmc_request_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_command *cmd = mrq->cmd;
	पूर्णांक err = cmd->error;

	/* Flag re-tuning needed on CRC errors */
	अगर (cmd->opcode != MMC_SEND_TUNING_BLOCK &&
	    cmd->opcode != MMC_SEND_TUNING_BLOCK_HS200 &&
	    !host->retune_crc_disable &&
	    (err == -EILSEQ || (mrq->sbc && mrq->sbc->error == -EILSEQ) ||
	    (mrq->data && mrq->data->error == -EILSEQ) ||
	    (mrq->stop && mrq->stop->error == -EILSEQ)))
		mmc_retune_needed(host);

	अगर (err && cmd->retries && mmc_host_is_spi(host)) अणु
		अगर (cmd->resp[0] & R1_SPI_ILLEGAL_COMMAND)
			cmd->retries = 0;
	पूर्ण

	अगर (host->ongoing_mrq == mrq)
		host->ongoing_mrq = शून्य;

	mmc_complete_cmd(mrq);

	trace_mmc_request_करोne(host, mrq);

	/*
	 * We list various conditions क्रम the command to be considered
	 * properly करोne:
	 *
	 * - There was no error, OK fine then
	 * - We are not करोing some kind of retry
	 * - The card was हटाओd (...so just complete everything no matter
	 *   अगर there are errors or retries)
	 */
	अगर (!err || !cmd->retries || mmc_card_हटाओd(host->card)) अणु
		mmc_should_fail_request(host, mrq);

		अगर (!host->ongoing_mrq)
			led_trigger_event(host->led, LED_OFF);

		अगर (mrq->sbc) अणु
			pr_debug("%s: req done <CMD%u>: %d: %08x %08x %08x %08x\n",
				mmc_hostname(host), mrq->sbc->opcode,
				mrq->sbc->error,
				mrq->sbc->resp[0], mrq->sbc->resp[1],
				mrq->sbc->resp[2], mrq->sbc->resp[3]);
		पूर्ण

		pr_debug("%s: req done (CMD%u): %d: %08x %08x %08x %08x\n",
			mmc_hostname(host), cmd->opcode, err,
			cmd->resp[0], cmd->resp[1],
			cmd->resp[2], cmd->resp[3]);

		अगर (mrq->data) अणु
			pr_debug("%s:     %d bytes transferred: %d\n",
				mmc_hostname(host),
				mrq->data->bytes_xfered, mrq->data->error);
		पूर्ण

		अगर (mrq->stop) अणु
			pr_debug("%s:     (CMD%u): %d: %08x %08x %08x %08x\n",
				mmc_hostname(host), mrq->stop->opcode,
				mrq->stop->error,
				mrq->stop->resp[0], mrq->stop->resp[1],
				mrq->stop->resp[2], mrq->stop->resp[3]);
		पूर्ण
	पूर्ण
	/*
	 * Request starter must handle retries - see
	 * mmc_रुको_क्रम_req_करोne().
	 */
	अगर (mrq->करोne)
		mrq->करोne(mrq);
पूर्ण

EXPORT_SYMBOL(mmc_request_करोne);

अटल व्योम __mmc_start_request(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक err;

	/* Assumes host controller has been runसमय resumed by mmc_claim_host */
	err = mmc_retune(host);
	अगर (err) अणु
		mrq->cmd->error = err;
		mmc_request_करोne(host, mrq);
		वापस;
	पूर्ण

	/*
	 * For sdio rw commands we must रुको क्रम card busy otherwise some
	 * sdio devices won't work properly.
	 * And bypass I/O पात, reset and bus suspend operations.
	 */
	अगर (sdio_is_io_busy(mrq->cmd->opcode, mrq->cmd->arg) &&
	    host->ops->card_busy) अणु
		पूर्णांक tries = 500; /* Wait aprox 500ms at maximum */

		जबतक (host->ops->card_busy(host) && --tries)
			mmc_delay(1);

		अगर (tries == 0) अणु
			mrq->cmd->error = -EBUSY;
			mmc_request_करोne(host, mrq);
			वापस;
		पूर्ण
	पूर्ण

	अगर (mrq->cap_cmd_during_tfr) अणु
		host->ongoing_mrq = mrq;
		/*
		 * Retry path could come through here without having रुकोing on
		 * cmd_completion, so ensure it is reinitialised.
		 */
		reinit_completion(&mrq->cmd_completion);
	पूर्ण

	trace_mmc_request_start(host, mrq);

	अगर (host->cqe_on)
		host->cqe_ops->cqe_off(host);

	host->ops->request(host, mrq);
पूर्ण

अटल व्योम mmc_mrq_pr_debug(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq,
			     bool cqe)
अणु
	अगर (mrq->sbc) अणु
		pr_debug("<%s: starting CMD%u arg %08x flags %08x>\n",
			 mmc_hostname(host), mrq->sbc->opcode,
			 mrq->sbc->arg, mrq->sbc->flags);
	पूर्ण

	अगर (mrq->cmd) अणु
		pr_debug("%s: starting %sCMD%u arg %08x flags %08x\n",
			 mmc_hostname(host), cqe ? "CQE direct " : "",
			 mrq->cmd->opcode, mrq->cmd->arg, mrq->cmd->flags);
	पूर्ण अन्यथा अगर (cqe) अणु
		pr_debug("%s: starting CQE transfer for tag %d blkaddr %u\n",
			 mmc_hostname(host), mrq->tag, mrq->data->blk_addr);
	पूर्ण

	अगर (mrq->data) अणु
		pr_debug("%s:     blksz %d blocks %d flags %08x "
			"tsac %d ms nsac %d\n",
			mmc_hostname(host), mrq->data->blksz,
			mrq->data->blocks, mrq->data->flags,
			mrq->data->समयout_ns / 1000000,
			mrq->data->समयout_clks);
	पूर्ण

	अगर (mrq->stop) अणु
		pr_debug("%s:     CMD%u arg %08x flags %08x\n",
			 mmc_hostname(host), mrq->stop->opcode,
			 mrq->stop->arg, mrq->stop->flags);
	पूर्ण
पूर्ण

अटल पूर्णांक mmc_mrq_prep(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	अचिन्हित पूर्णांक i, sz = 0;
	काष्ठा scatterlist *sg;

	अगर (mrq->cmd) अणु
		mrq->cmd->error = 0;
		mrq->cmd->mrq = mrq;
		mrq->cmd->data = mrq->data;
	पूर्ण
	अगर (mrq->sbc) अणु
		mrq->sbc->error = 0;
		mrq->sbc->mrq = mrq;
	पूर्ण
	अगर (mrq->data) अणु
		अगर (mrq->data->blksz > host->max_blk_size ||
		    mrq->data->blocks > host->max_blk_count ||
		    mrq->data->blocks * mrq->data->blksz > host->max_req_size)
			वापस -EINVAL;

		क्रम_each_sg(mrq->data->sg, sg, mrq->data->sg_len, i)
			sz += sg->length;
		अगर (sz != mrq->data->blocks * mrq->data->blksz)
			वापस -EINVAL;

		mrq->data->error = 0;
		mrq->data->mrq = mrq;
		अगर (mrq->stop) अणु
			mrq->data->stop = mrq->stop;
			mrq->stop->error = 0;
			mrq->stop->mrq = mrq;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mmc_start_request(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक err;

	init_completion(&mrq->cmd_completion);

	mmc_retune_hold(host);

	अगर (mmc_card_हटाओd(host->card))
		वापस -ENOMEDIUM;

	mmc_mrq_pr_debug(host, mrq, false);

	WARN_ON(!host->claimed);

	err = mmc_mrq_prep(host, mrq);
	अगर (err)
		वापस err;

	led_trigger_event(host->led, LED_FULL);
	__mmc_start_request(host, mrq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mmc_start_request);

अटल व्योम mmc_रुको_करोne(काष्ठा mmc_request *mrq)
अणु
	complete(&mrq->completion);
पूर्ण

अटल अंतरभूत व्योम mmc_रुको_ongoing_tfr_cmd(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_request *ongoing_mrq = READ_ONCE(host->ongoing_mrq);

	/*
	 * If there is an ongoing transfer, रुको क्रम the command line to become
	 * available.
	 */
	अगर (ongoing_mrq && !completion_करोne(&ongoing_mrq->cmd_completion))
		रुको_क्रम_completion(&ongoing_mrq->cmd_completion);
पूर्ण

अटल पूर्णांक __mmc_start_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक err;

	mmc_रुको_ongoing_tfr_cmd(host);

	init_completion(&mrq->completion);
	mrq->करोne = mmc_रुको_करोne;

	err = mmc_start_request(host, mrq);
	अगर (err) अणु
		mrq->cmd->error = err;
		mmc_complete_cmd(mrq);
		complete(&mrq->completion);
	पूर्ण

	वापस err;
पूर्ण

व्योम mmc_रुको_क्रम_req_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_command *cmd;

	जबतक (1) अणु
		रुको_क्रम_completion(&mrq->completion);

		cmd = mrq->cmd;

		अगर (!cmd->error || !cmd->retries ||
		    mmc_card_हटाओd(host->card))
			अवरोध;

		mmc_retune_recheck(host);

		pr_debug("%s: req failed (CMD%u): %d, retrying...\n",
			 mmc_hostname(host), cmd->opcode, cmd->error);
		cmd->retries--;
		cmd->error = 0;
		__mmc_start_request(host, mrq);
	पूर्ण

	mmc_retune_release(host);
पूर्ण
EXPORT_SYMBOL(mmc_रुको_क्रम_req_करोne);

/*
 * mmc_cqe_start_req - Start a CQE request.
 * @host: MMC host to start the request
 * @mrq: request to start
 *
 * Start the request, re-tuning अगर needed and it is possible. Returns an error
 * code अगर the request fails to start or -EBUSY अगर CQE is busy.
 */
पूर्णांक mmc_cqe_start_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक err;

	/*
	 * CQE cannot process re-tuning commands. Caller must hold retuning
	 * जबतक CQE is in use.  Re-tuning can happen here only when CQE has no
	 * active requests i.e. this is the first.  Note, re-tuning will call
	 * ->cqe_off().
	 */
	err = mmc_retune(host);
	अगर (err)
		जाओ out_err;

	mrq->host = host;

	mmc_mrq_pr_debug(host, mrq, true);

	err = mmc_mrq_prep(host, mrq);
	अगर (err)
		जाओ out_err;

	err = host->cqe_ops->cqe_request(host, mrq);
	अगर (err)
		जाओ out_err;

	trace_mmc_request_start(host, mrq);

	वापस 0;

out_err:
	अगर (mrq->cmd) अणु
		pr_debug("%s: failed to start CQE direct CMD%u, error %d\n",
			 mmc_hostname(host), mrq->cmd->opcode, err);
	पूर्ण अन्यथा अणु
		pr_debug("%s: failed to start CQE transfer for tag %d, error %d\n",
			 mmc_hostname(host), mrq->tag, err);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(mmc_cqe_start_req);

/**
 *	mmc_cqe_request_करोne - CQE has finished processing an MMC request
 *	@host: MMC host which completed request
 *	@mrq: MMC request which completed
 *
 *	CQE drivers should call this function when they have completed
 *	their processing of a request.
 */
व्योम mmc_cqe_request_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	mmc_should_fail_request(host, mrq);

	/* Flag re-tuning needed on CRC errors */
	अगर ((mrq->cmd && mrq->cmd->error == -EILSEQ) ||
	    (mrq->data && mrq->data->error == -EILSEQ))
		mmc_retune_needed(host);

	trace_mmc_request_करोne(host, mrq);

	अगर (mrq->cmd) अणु
		pr_debug("%s: CQE req done (direct CMD%u): %d\n",
			 mmc_hostname(host), mrq->cmd->opcode, mrq->cmd->error);
	पूर्ण अन्यथा अणु
		pr_debug("%s: CQE transfer done tag %d\n",
			 mmc_hostname(host), mrq->tag);
	पूर्ण

	अगर (mrq->data) अणु
		pr_debug("%s:     %d bytes transferred: %d\n",
			 mmc_hostname(host),
			 mrq->data->bytes_xfered, mrq->data->error);
	पूर्ण

	mrq->करोne(mrq);
पूर्ण
EXPORT_SYMBOL(mmc_cqe_request_करोne);

/**
 *	mmc_cqe_post_req - CQE post process of a completed MMC request
 *	@host: MMC host
 *	@mrq: MMC request to be processed
 */
व्योम mmc_cqe_post_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	अगर (host->cqe_ops->cqe_post_req)
		host->cqe_ops->cqe_post_req(host, mrq);
पूर्ण
EXPORT_SYMBOL(mmc_cqe_post_req);

/* Arbitrary 1 second समयout */
#घोषणा MMC_CQE_RECOVERY_TIMEOUT	1000

/*
 * mmc_cqe_recovery - Recover from CQE errors.
 * @host: MMC host to recover
 *
 * Recovery consists of stopping CQE, stopping eMMC, discarding the queue in
 * in eMMC, and discarding the queue in CQE. CQE must call
 * mmc_cqe_request_करोne() on all requests. An error is वापसed अगर the eMMC
 * fails to discard its queue.
 */
पूर्णांक mmc_cqe_recovery(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_command cmd;
	पूर्णांक err;

	mmc_retune_hold_now(host);

	/*
	 * Recovery is expected selकरोm, अगर at all, but it reduces perक्रमmance,
	 * so make sure it is not completely silent.
	 */
	pr_warn("%s: running CQE recovery\n", mmc_hostname(host));

	host->cqe_ops->cqe_recovery_start(host);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode       = MMC_STOP_TRANSMISSION;
	cmd.flags        = MMC_RSP_R1B | MMC_CMD_AC;
	cmd.flags       &= ~MMC_RSP_CRC; /* Ignore CRC */
	cmd.busy_समयout = MMC_CQE_RECOVERY_TIMEOUT;
	mmc_रुको_क्रम_cmd(host, &cmd, 0);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode       = MMC_CMDQ_TASK_MGMT;
	cmd.arg          = 1; /* Discard entire queue */
	cmd.flags        = MMC_RSP_R1B | MMC_CMD_AC;
	cmd.flags       &= ~MMC_RSP_CRC; /* Ignore CRC */
	cmd.busy_समयout = MMC_CQE_RECOVERY_TIMEOUT;
	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);

	host->cqe_ops->cqe_recovery_finish(host);

	mmc_retune_release(host);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mmc_cqe_recovery);

/**
 *	mmc_is_req_करोne - Determine अगर a 'cap_cmd_during_tfr' request is करोne
 *	@host: MMC host
 *	@mrq: MMC request
 *
 *	mmc_is_req_करोne() is used with requests that have
 *	mrq->cap_cmd_during_tfr = true. mmc_is_req_करोne() must be called after
 *	starting a request and beक्रमe रुकोing क्रम it to complete. That is,
 *	either in between calls to mmc_start_req(), or after mmc_रुको_क्रम_req()
 *	and beक्रमe mmc_रुको_क्रम_req_करोne(). If it is called at other बार the
 *	result is not meaningful.
 */
bool mmc_is_req_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	वापस completion_करोne(&mrq->completion);
पूर्ण
EXPORT_SYMBOL(mmc_is_req_करोne);

/**
 *	mmc_रुको_क्रम_req - start a request and रुको क्रम completion
 *	@host: MMC host to start command
 *	@mrq: MMC request to start
 *
 *	Start a new MMC custom command request क्रम a host, and रुको
 *	क्रम the command to complete. In the हाल of 'cap_cmd_during_tfr'
 *	requests, the transfer is ongoing and the caller can issue further
 *	commands that करो not use the data lines, and then रुको by calling
 *	mmc_रुको_क्रम_req_करोne().
 *	Does not attempt to parse the response.
 */
व्योम mmc_रुको_क्रम_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	__mmc_start_req(host, mrq);

	अगर (!mrq->cap_cmd_during_tfr)
		mmc_रुको_क्रम_req_करोne(host, mrq);
पूर्ण
EXPORT_SYMBOL(mmc_रुको_क्रम_req);

/**
 *	mmc_रुको_क्रम_cmd - start a command and रुको क्रम completion
 *	@host: MMC host to start command
 *	@cmd: MMC command to start
 *	@retries: maximum number of retries
 *
 *	Start a new MMC command क्रम a host, and रुको क्रम the command
 *	to complete.  Return any error that occurred जबतक the command
 *	was executing.  Do not attempt to parse the response.
 */
पूर्णांक mmc_रुको_क्रम_cmd(काष्ठा mmc_host *host, काष्ठा mmc_command *cmd, पूर्णांक retries)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;

	WARN_ON(!host->claimed);

	स_रखो(cmd->resp, 0, माप(cmd->resp));
	cmd->retries = retries;

	mrq.cmd = cmd;
	cmd->data = शून्य;

	mmc_रुको_क्रम_req(host, &mrq);

	वापस cmd->error;
पूर्ण

EXPORT_SYMBOL(mmc_रुको_क्रम_cmd);

/**
 *	mmc_set_data_समयout - set the समयout क्रम a data command
 *	@data: data phase क्रम command
 *	@card: the MMC card associated with the data transfer
 *
 *	Computes the data समयout parameters according to the
 *	correct algorithm given the card type.
 */
व्योम mmc_set_data_समयout(काष्ठा mmc_data *data, स्थिर काष्ठा mmc_card *card)
अणु
	अचिन्हित पूर्णांक mult;

	/*
	 * SDIO cards only define an upper 1 s limit on access.
	 */
	अगर (mmc_card_sdio(card)) अणु
		data->समयout_ns = 1000000000;
		data->समयout_clks = 0;
		वापस;
	पूर्ण

	/*
	 * SD cards use a 100 multiplier rather than 10
	 */
	mult = mmc_card_sd(card) ? 100 : 10;

	/*
	 * Scale up the multiplier (and thereक्रमe the समयout) by
	 * the r2w factor क्रम ग_लिखोs.
	 */
	अगर (data->flags & MMC_DATA_WRITE)
		mult <<= card->csd.r2w_factor;

	data->समयout_ns = card->csd.taac_ns * mult;
	data->समयout_clks = card->csd.taac_clks * mult;

	/*
	 * SD cards also have an upper limit on the समयout.
	 */
	अगर (mmc_card_sd(card)) अणु
		अचिन्हित पूर्णांक समयout_us, limit_us;

		समयout_us = data->समयout_ns / 1000;
		अगर (card->host->ios.घड़ी)
			समयout_us += data->समयout_clks * 1000 /
				(card->host->ios.घड़ी / 1000);

		अगर (data->flags & MMC_DATA_WRITE)
			/*
			 * The MMC spec "It is strongly recommended
			 * क्रम hosts to implement more than 500ms
			 * समयout value even अगर the card indicates
			 * the 250ms maximum busy length."  Even the
			 * previous value of 300ms is known to be
			 * insufficient क्रम some cards.
			 */
			limit_us = 3000000;
		अन्यथा
			limit_us = 100000;

		/*
		 * SDHC cards always use these fixed values.
		 */
		अगर (समयout_us > limit_us) अणु
			data->समयout_ns = limit_us * 1000;
			data->समयout_clks = 0;
		पूर्ण

		/* assign limit value अगर invalid */
		अगर (समयout_us == 0)
			data->समयout_ns = limit_us * 1000;
	पूर्ण

	/*
	 * Some cards require दीर्घer data पढ़ो समयout than indicated in CSD.
	 * Address this by setting the पढ़ो समयout to a "reasonably high"
	 * value. For the cards tested, 600ms has proven enough. If necessary,
	 * this value can be increased अगर other problematic cards require this.
	 */
	अगर (mmc_card_दीर्घ_पढ़ो_समय(card) && data->flags & MMC_DATA_READ) अणु
		data->समयout_ns = 600000000;
		data->समयout_clks = 0;
	पूर्ण

	/*
	 * Some cards need very high समयouts अगर driven in SPI mode.
	 * The worst observed समयout was 900ms after writing a
	 * continuous stream of data until the पूर्णांकernal logic
	 * overflowed.
	 */
	अगर (mmc_host_is_spi(card->host)) अणु
		अगर (data->flags & MMC_DATA_WRITE) अणु
			अगर (data->समयout_ns < 1000000000)
				data->समयout_ns = 1000000000;	/* 1s */
		पूर्ण अन्यथा अणु
			अगर (data->समयout_ns < 100000000)
				data->समयout_ns =  100000000;	/* 100ms */
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mmc_set_data_समयout);

/*
 * Allow claiming an alपढ़ोy claimed host अगर the context is the same or there is
 * no context but the task is the same.
 */
अटल अंतरभूत bool mmc_ctx_matches(काष्ठा mmc_host *host, काष्ठा mmc_ctx *ctx,
				   काष्ठा task_काष्ठा *task)
अणु
	वापस host->claimer == ctx ||
	       (!ctx && task && host->claimer->task == task);
पूर्ण

अटल अंतरभूत व्योम mmc_ctx_set_claimer(काष्ठा mmc_host *host,
				       काष्ठा mmc_ctx *ctx,
				       काष्ठा task_काष्ठा *task)
अणु
	अगर (!host->claimer) अणु
		अगर (ctx)
			host->claimer = ctx;
		अन्यथा
			host->claimer = &host->शेष_ctx;
	पूर्ण
	अगर (task)
		host->claimer->task = task;
पूर्ण

/**
 *	__mmc_claim_host - exclusively claim a host
 *	@host: mmc host to claim
 *	@ctx: context that claims the host or शून्य in which हाल the शेष
 *	context will be used
 *	@पात: whether or not the operation should be पातed
 *
 *	Claim a host क्रम a set of operations.  If @पात is non null and
 *	dereference a non-zero value then this will वापस prematurely with
 *	that non-zero value without acquiring the lock.  Returns zero
 *	with the lock held otherwise.
 */
पूर्णांक __mmc_claim_host(काष्ठा mmc_host *host, काष्ठा mmc_ctx *ctx,
		     atomic_t *पात)
अणु
	काष्ठा task_काष्ठा *task = ctx ? शून्य : current;
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ flags;
	पूर्णांक stop;
	bool pm = false;

	might_sleep();

	add_रुको_queue(&host->wq, &रुको);
	spin_lock_irqsave(&host->lock, flags);
	जबतक (1) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		stop = पात ? atomic_पढ़ो(पात) : 0;
		अगर (stop || !host->claimed || mmc_ctx_matches(host, ctx, task))
			अवरोध;
		spin_unlock_irqrestore(&host->lock, flags);
		schedule();
		spin_lock_irqsave(&host->lock, flags);
	पूर्ण
	set_current_state(TASK_RUNNING);
	अगर (!stop) अणु
		host->claimed = 1;
		mmc_ctx_set_claimer(host, ctx, task);
		host->claim_cnt += 1;
		अगर (host->claim_cnt == 1)
			pm = true;
	पूर्ण अन्यथा
		wake_up(&host->wq);
	spin_unlock_irqrestore(&host->lock, flags);
	हटाओ_रुको_queue(&host->wq, &रुको);

	अगर (pm)
		pm_runसमय_get_sync(mmc_dev(host));

	वापस stop;
पूर्ण
EXPORT_SYMBOL(__mmc_claim_host);

/**
 *	mmc_release_host - release a host
 *	@host: mmc host to release
 *
 *	Release a MMC host, allowing others to claim the host
 *	क्रम their operations.
 */
व्योम mmc_release_host(काष्ठा mmc_host *host)
अणु
	अचिन्हित दीर्घ flags;

	WARN_ON(!host->claimed);

	spin_lock_irqsave(&host->lock, flags);
	अगर (--host->claim_cnt) अणु
		/* Release क्रम nested claim */
		spin_unlock_irqrestore(&host->lock, flags);
	पूर्ण अन्यथा अणु
		host->claimed = 0;
		host->claimer->task = शून्य;
		host->claimer = शून्य;
		spin_unlock_irqrestore(&host->lock, flags);
		wake_up(&host->wq);
		pm_runसमय_mark_last_busy(mmc_dev(host));
		अगर (host->caps & MMC_CAP_SYNC_RUNTIME_PM)
			pm_runसमय_put_sync_suspend(mmc_dev(host));
		अन्यथा
			pm_runसमय_put_स्वतःsuspend(mmc_dev(host));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mmc_release_host);

/*
 * This is a helper function, which fetches a runसमय pm reference क्रम the
 * card device and also claims the host.
 */
व्योम mmc_get_card(काष्ठा mmc_card *card, काष्ठा mmc_ctx *ctx)
अणु
	pm_runसमय_get_sync(&card->dev);
	__mmc_claim_host(card->host, ctx, शून्य);
पूर्ण
EXPORT_SYMBOL(mmc_get_card);

/*
 * This is a helper function, which releases the host and drops the runसमय
 * pm reference क्रम the card device.
 */
व्योम mmc_put_card(काष्ठा mmc_card *card, काष्ठा mmc_ctx *ctx)
अणु
	काष्ठा mmc_host *host = card->host;

	WARN_ON(ctx && host->claimer != ctx);

	mmc_release_host(host);
	pm_runसमय_mark_last_busy(&card->dev);
	pm_runसमय_put_स्वतःsuspend(&card->dev);
पूर्ण
EXPORT_SYMBOL(mmc_put_card);

/*
 * Internal function that करोes the actual ios call to the host driver,
 * optionally prपूर्णांकing some debug output.
 */
अटल अंतरभूत व्योम mmc_set_ios(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_ios *ios = &host->ios;

	pr_debug("%s: clock %uHz busmode %u powermode %u cs %u Vdd %u "
		"width %u timing %u\n",
		 mmc_hostname(host), ios->घड़ी, ios->bus_mode,
		 ios->घातer_mode, ios->chip_select, ios->vdd,
		 1 << ios->bus_width, ios->timing);

	host->ops->set_ios(host, ios);
पूर्ण

/*
 * Control chip select pin on a host.
 */
व्योम mmc_set_chip_select(काष्ठा mmc_host *host, पूर्णांक mode)
अणु
	host->ios.chip_select = mode;
	mmc_set_ios(host);
पूर्ण

/*
 * Sets the host घड़ी to the highest possible frequency that
 * is below "hz".
 */
व्योम mmc_set_घड़ी(काष्ठा mmc_host *host, अचिन्हित पूर्णांक hz)
अणु
	WARN_ON(hz && hz < host->f_min);

	अगर (hz > host->f_max)
		hz = host->f_max;

	host->ios.घड़ी = hz;
	mmc_set_ios(host);
पूर्ण

पूर्णांक mmc_execute_tuning(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	u32 opcode;
	पूर्णांक err;

	अगर (!host->ops->execute_tuning)
		वापस 0;

	अगर (host->cqe_on)
		host->cqe_ops->cqe_off(host);

	अगर (mmc_card_mmc(card))
		opcode = MMC_SEND_TUNING_BLOCK_HS200;
	अन्यथा
		opcode = MMC_SEND_TUNING_BLOCK;

	err = host->ops->execute_tuning(host, opcode);

	अगर (err)
		pr_err("%s: tuning execution failed: %d\n",
			mmc_hostname(host), err);
	अन्यथा
		mmc_retune_enable(host);

	वापस err;
पूर्ण

/*
 * Change the bus mode (खोलो drain/push-pull) of a host.
 */
व्योम mmc_set_bus_mode(काष्ठा mmc_host *host, अचिन्हित पूर्णांक mode)
अणु
	host->ios.bus_mode = mode;
	mmc_set_ios(host);
पूर्ण

/*
 * Change data bus width of a host.
 */
व्योम mmc_set_bus_width(काष्ठा mmc_host *host, अचिन्हित पूर्णांक width)
अणु
	host->ios.bus_width = width;
	mmc_set_ios(host);
पूर्ण

/*
 * Set initial state after a घातer cycle or a hw_reset.
 */
व्योम mmc_set_initial_state(काष्ठा mmc_host *host)
अणु
	अगर (host->cqe_on)
		host->cqe_ops->cqe_off(host);

	mmc_retune_disable(host);

	अगर (mmc_host_is_spi(host))
		host->ios.chip_select = MMC_CS_HIGH;
	अन्यथा
		host->ios.chip_select = MMC_CS_DONTCARE;
	host->ios.bus_mode = MMC_BUSMODE_PUSHPULL;
	host->ios.bus_width = MMC_BUS_WIDTH_1;
	host->ios.timing = MMC_TIMING_LEGACY;
	host->ios.drv_type = 0;
	host->ios.enhanced_strobe = false;

	/*
	 * Make sure we are in non-enhanced strobe mode beक्रमe we
	 * actually enable it in ext_csd.
	 */
	अगर ((host->caps2 & MMC_CAP2_HS400_ES) &&
	     host->ops->hs400_enhanced_strobe)
		host->ops->hs400_enhanced_strobe(host, &host->ios);

	mmc_set_ios(host);

	mmc_crypto_set_initial_state(host);
पूर्ण

/**
 * mmc_vdd_to_ocrbitnum - Convert a voltage to the OCR bit number
 * @vdd:	voltage (mV)
 * @low_bits:	prefer low bits in boundary हालs
 *
 * This function वापसs the OCR bit number according to the provided @vdd
 * value. If conversion is not possible a negative त्रुटि_सं value वापसed.
 *
 * Depending on the @low_bits flag the function prefers low or high OCR bits
 * on boundary voltages. For example,
 * with @low_bits = true, 3300 mV translates to ilog2(MMC_VDD_32_33);
 * with @low_bits = false, 3300 mV translates to ilog2(MMC_VDD_33_34);
 *
 * Any value in the [1951:1999] range translates to the ilog2(MMC_VDD_20_21).
 */
अटल पूर्णांक mmc_vdd_to_ocrbitnum(पूर्णांक vdd, bool low_bits)
अणु
	स्थिर पूर्णांक max_bit = ilog2(MMC_VDD_35_36);
	पूर्णांक bit;

	अगर (vdd < 1650 || vdd > 3600)
		वापस -EINVAL;

	अगर (vdd >= 1650 && vdd <= 1950)
		वापस ilog2(MMC_VDD_165_195);

	अगर (low_bits)
		vdd -= 1;

	/* Base 2000 mV, step 100 mV, bit's base 8. */
	bit = (vdd - 2000) / 100 + 8;
	अगर (bit > max_bit)
		वापस max_bit;
	वापस bit;
पूर्ण

/**
 * mmc_vddrange_to_ocrmask - Convert a voltage range to the OCR mask
 * @vdd_min:	minimum voltage value (mV)
 * @vdd_max:	maximum voltage value (mV)
 *
 * This function वापसs the OCR mask bits according to the provided @vdd_min
 * and @vdd_max values. If conversion is not possible the function वापसs 0.
 *
 * Notes wrt boundary हालs:
 * This function sets the OCR bits क्रम all boundary voltages, क्रम example
 * [3300:3400] range is translated to MMC_VDD_32_33 | MMC_VDD_33_34 |
 * MMC_VDD_34_35 mask.
 */
u32 mmc_vddrange_to_ocrmask(पूर्णांक vdd_min, पूर्णांक vdd_max)
अणु
	u32 mask = 0;

	अगर (vdd_max < vdd_min)
		वापस 0;

	/* Prefer high bits क्रम the boundary vdd_max values. */
	vdd_max = mmc_vdd_to_ocrbitnum(vdd_max, false);
	अगर (vdd_max < 0)
		वापस 0;

	/* Prefer low bits क्रम the boundary vdd_min values. */
	vdd_min = mmc_vdd_to_ocrbitnum(vdd_min, true);
	अगर (vdd_min < 0)
		वापस 0;

	/* Fill the mask, from max bit to min bit. */
	जबतक (vdd_max >= vdd_min)
		mask |= 1 << vdd_max--;

	वापस mask;
पूर्ण

अटल पूर्णांक mmc_of_get_func_num(काष्ठा device_node *node)
अणु
	u32 reg;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(node, "reg", &reg);
	अगर (ret < 0)
		वापस ret;

	वापस reg;
पूर्ण

काष्ठा device_node *mmc_of_find_child_device(काष्ठा mmc_host *host,
		अचिन्हित func_num)
अणु
	काष्ठा device_node *node;

	अगर (!host->parent || !host->parent->of_node)
		वापस शून्य;

	क्रम_each_child_of_node(host->parent->of_node, node) अणु
		अगर (mmc_of_get_func_num(node) == func_num)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Mask off any voltages we करोn't support and select
 * the lowest voltage
 */
u32 mmc_select_voltage(काष्ठा mmc_host *host, u32 ocr)
अणु
	पूर्णांक bit;

	/*
	 * Sanity check the voltages that the card claims to
	 * support.
	 */
	अगर (ocr & 0x7F) अणु
		dev_warn(mmc_dev(host),
		"card claims to support voltages below defined range\n");
		ocr &= ~0x7F;
	पूर्ण

	ocr &= host->ocr_avail;
	अगर (!ocr) अणु
		dev_warn(mmc_dev(host), "no support for card's volts\n");
		वापस 0;
	पूर्ण

	अगर (host->caps2 & MMC_CAP2_FULL_PWR_CYCLE) अणु
		bit = ffs(ocr) - 1;
		ocr &= 3 << bit;
		mmc_घातer_cycle(host, ocr);
	पूर्ण अन्यथा अणु
		bit = fls(ocr) - 1;
		ocr &= 3 << bit;
		अगर (bit != host->ios.vdd)
			dev_warn(mmc_dev(host), "exceeding card's volts\n");
	पूर्ण

	वापस ocr;
पूर्ण

पूर्णांक mmc_set_संकेत_voltage(काष्ठा mmc_host *host, पूर्णांक संकेत_voltage)
अणु
	पूर्णांक err = 0;
	पूर्णांक old_संकेत_voltage = host->ios.संकेत_voltage;

	host->ios.संकेत_voltage = संकेत_voltage;
	अगर (host->ops->start_संकेत_voltage_चयन)
		err = host->ops->start_संकेत_voltage_चयन(host, &host->ios);

	अगर (err)
		host->ios.संकेत_voltage = old_संकेत_voltage;

	वापस err;

पूर्ण

व्योम mmc_set_initial_संकेत_voltage(काष्ठा mmc_host *host)
अणु
	/* Try to set संकेत voltage to 3.3V but fall back to 1.8v or 1.2v */
	अगर (!mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_330))
		dev_dbg(mmc_dev(host), "Initial signal voltage of 3.3v\n");
	अन्यथा अगर (!mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_180))
		dev_dbg(mmc_dev(host), "Initial signal voltage of 1.8v\n");
	अन्यथा अगर (!mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_120))
		dev_dbg(mmc_dev(host), "Initial signal voltage of 1.2v\n");
पूर्ण

पूर्णांक mmc_host_set_uhs_voltage(काष्ठा mmc_host *host)
अणु
	u32 घड़ी;

	/*
	 * During a संकेत voltage level चयन, the घड़ी must be gated
	 * क्रम 5 ms according to the SD spec
	 */
	घड़ी = host->ios.घड़ी;
	host->ios.घड़ी = 0;
	mmc_set_ios(host);

	अगर (mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_180))
		वापस -EAGAIN;

	/* Keep घड़ी gated क्रम at least 10 ms, though spec only says 5 ms */
	mmc_delay(10);
	host->ios.घड़ी = घड़ी;
	mmc_set_ios(host);

	वापस 0;
पूर्ण

पूर्णांक mmc_set_uhs_voltage(काष्ठा mmc_host *host, u32 ocr)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	पूर्णांक err = 0;

	/*
	 * If we cannot चयन voltages, वापस failure so the caller
	 * can जारी without UHS mode
	 */
	अगर (!host->ops->start_संकेत_voltage_चयन)
		वापस -EPERM;
	अगर (!host->ops->card_busy)
		pr_warn("%s: cannot verify signal voltage switch\n",
			mmc_hostname(host));

	cmd.opcode = SD_SWITCH_VOLTAGE;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
	अगर (err)
		जाओ घातer_cycle;

	अगर (!mmc_host_is_spi(host) && (cmd.resp[0] & R1_ERROR))
		वापस -EIO;

	/*
	 * The card should drive cmd and dat[0:3] low immediately
	 * after the response of cmd11, but रुको 1 ms to be sure
	 */
	mmc_delay(1);
	अगर (host->ops->card_busy && !host->ops->card_busy(host)) अणु
		err = -EAGAIN;
		जाओ घातer_cycle;
	पूर्ण

	अगर (mmc_host_set_uhs_voltage(host)) अणु
		/*
		 * Voltages may not have been चयनed, but we've alपढ़ोy
		 * sent CMD11, so a घातer cycle is required anyway
		 */
		err = -EAGAIN;
		जाओ घातer_cycle;
	पूर्ण

	/* Wait क्रम at least 1 ms according to spec */
	mmc_delay(1);

	/*
	 * Failure to चयन is indicated by the card holding
	 * dat[0:3] low
	 */
	अगर (host->ops->card_busy && host->ops->card_busy(host))
		err = -EAGAIN;

घातer_cycle:
	अगर (err) अणु
		pr_debug("%s: Signal voltage switch failed, "
			"power cycling card\n", mmc_hostname(host));
		mmc_घातer_cycle(host, ocr);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Select timing parameters क्रम host.
 */
व्योम mmc_set_timing(काष्ठा mmc_host *host, अचिन्हित पूर्णांक timing)
अणु
	host->ios.timing = timing;
	mmc_set_ios(host);
पूर्ण

/*
 * Select appropriate driver type क्रम host.
 */
व्योम mmc_set_driver_type(काष्ठा mmc_host *host, अचिन्हित पूर्णांक drv_type)
अणु
	host->ios.drv_type = drv_type;
	mmc_set_ios(host);
पूर्ण

पूर्णांक mmc_select_drive_strength(काष्ठा mmc_card *card, अचिन्हित पूर्णांक max_dtr,
			      पूर्णांक card_drv_type, पूर्णांक *drv_type)
अणु
	काष्ठा mmc_host *host = card->host;
	पूर्णांक host_drv_type = SD_DRIVER_TYPE_B;

	*drv_type = 0;

	अगर (!host->ops->select_drive_strength)
		वापस 0;

	/* Use SD definition of driver strength क्रम hosts */
	अगर (host->caps & MMC_CAP_DRIVER_TYPE_A)
		host_drv_type |= SD_DRIVER_TYPE_A;

	अगर (host->caps & MMC_CAP_DRIVER_TYPE_C)
		host_drv_type |= SD_DRIVER_TYPE_C;

	अगर (host->caps & MMC_CAP_DRIVER_TYPE_D)
		host_drv_type |= SD_DRIVER_TYPE_D;

	/*
	 * The drive strength that the hardware can support
	 * depends on the board design.  Pass the appropriate
	 * inक्रमmation and let the hardware specअगरic code
	 * वापस what is possible given the options
	 */
	वापस host->ops->select_drive_strength(card, max_dtr,
						host_drv_type,
						card_drv_type,
						drv_type);
पूर्ण

/*
 * Apply घातer to the MMC stack.  This is a two-stage process.
 * First, we enable घातer to the card without the घड़ी running.
 * We then रुको a bit क्रम the घातer to stabilise.  Finally,
 * enable the bus drivers and घड़ी to the card.
 *
 * We must _NOT_ enable the घड़ी prior to घातer stablising.
 *
 * If a host करोes all the घातer sequencing itself, ignore the
 * initial MMC_POWER_UP stage.
 */
व्योम mmc_घातer_up(काष्ठा mmc_host *host, u32 ocr)
अणु
	अगर (host->ios.घातer_mode == MMC_POWER_ON)
		वापस;

	mmc_pwrseq_pre_घातer_on(host);

	host->ios.vdd = fls(ocr) - 1;
	host->ios.घातer_mode = MMC_POWER_UP;
	/* Set initial state and call mmc_set_ios */
	mmc_set_initial_state(host);

	mmc_set_initial_संकेत_voltage(host);

	/*
	 * This delay should be sufficient to allow the घातer supply
	 * to reach the minimum voltage.
	 */
	mmc_delay(host->ios.घातer_delay_ms);

	mmc_pwrseq_post_घातer_on(host);

	host->ios.घड़ी = host->f_init;

	host->ios.घातer_mode = MMC_POWER_ON;
	mmc_set_ios(host);

	/*
	 * This delay must be at least 74 घड़ी sizes, or 1 ms, or the
	 * समय required to reach a stable voltage.
	 */
	mmc_delay(host->ios.घातer_delay_ms);
पूर्ण

व्योम mmc_घातer_off(काष्ठा mmc_host *host)
अणु
	अगर (host->ios.घातer_mode == MMC_POWER_OFF)
		वापस;

	mmc_pwrseq_घातer_off(host);

	host->ios.घड़ी = 0;
	host->ios.vdd = 0;

	host->ios.घातer_mode = MMC_POWER_OFF;
	/* Set initial state and call mmc_set_ios */
	mmc_set_initial_state(host);

	/*
	 * Some configurations, such as the 802.11 SDIO card in the OLPC
	 * XO-1.5, require a लघु delay after घातeroff beक्रमe the card
	 * can be successfully turned on again.
	 */
	mmc_delay(1);
पूर्ण

व्योम mmc_घातer_cycle(काष्ठा mmc_host *host, u32 ocr)
अणु
	mmc_घातer_off(host);
	/* Wait at least 1 ms according to SD spec */
	mmc_delay(1);
	mmc_घातer_up(host, ocr);
पूर्ण

/*
 * Assign a mmc bus handler to a host. Only one bus handler may control a
 * host at any given समय.
 */
व्योम mmc_attach_bus(काष्ठा mmc_host *host, स्थिर काष्ठा mmc_bus_ops *ops)
अणु
	host->bus_ops = ops;
पूर्ण

/*
 * Remove the current bus handler from a host.
 */
व्योम mmc_detach_bus(काष्ठा mmc_host *host)
अणु
	host->bus_ops = शून्य;
पूर्ण

व्योम _mmc_detect_change(काष्ठा mmc_host *host, अचिन्हित दीर्घ delay, bool cd_irq)
अणु
	/*
	 * Prevent प्रणाली sleep क्रम 5s to allow user space to consume the
	 * corresponding uevent. This is especially useful, when CD irq is used
	 * as a प्रणाली wakeup, but करोesn't hurt in other हालs.
	 */
	अगर (cd_irq && !(host->caps & MMC_CAP_NEEDS_POLL))
		__pm_wakeup_event(host->ws, 5000);

	host->detect_change = 1;
	mmc_schedule_delayed_work(&host->detect, delay);
पूर्ण

/**
 *	mmc_detect_change - process change of state on a MMC socket
 *	@host: host which changed state.
 *	@delay: optional delay to रुको beक्रमe detection (jअगरfies)
 *
 *	MMC drivers should call this when they detect a card has been
 *	inserted or हटाओd. The MMC layer will confirm that any
 *	present card is still functional, and initialize any newly
 *	inserted.
 */
व्योम mmc_detect_change(काष्ठा mmc_host *host, अचिन्हित दीर्घ delay)
अणु
	_mmc_detect_change(host, delay, true);
पूर्ण
EXPORT_SYMBOL(mmc_detect_change);

व्योम mmc_init_erase(काष्ठा mmc_card *card)
अणु
	अचिन्हित पूर्णांक sz;

	अगर (is_घातer_of_2(card->erase_size))
		card->erase_shअगरt = ffs(card->erase_size) - 1;
	अन्यथा
		card->erase_shअगरt = 0;

	/*
	 * It is possible to erase an arbitrarily large area of an SD or MMC
	 * card.  That is not desirable because it can take a दीर्घ समय
	 * (minutes) potentially delaying more important I/O, and also the
	 * समयout calculations become increasingly hugely over-estimated.
	 * Consequently, 'pref_erase' is defined as a guide to limit erases
	 * to that size and alignment.
	 *
	 * For SD cards that define Allocation Unit size, limit erases to one
	 * Allocation Unit at a समय.
	 * For MMC, have a stab at ai good value and क्रम modern cards it will
	 * end up being 4MiB. Note that अगर the value is too small, it can end
	 * up taking दीर्घer to erase. Also note, erase_size is alपढ़ोy set to
	 * High Capacity Erase Size अगर available when this function is called.
	 */
	अगर (mmc_card_sd(card) && card->ssr.au) अणु
		card->pref_erase = card->ssr.au;
		card->erase_shअगरt = ffs(card->ssr.au) - 1;
	पूर्ण अन्यथा अगर (card->erase_size) अणु
		sz = (card->csd.capacity << (card->csd.पढ़ो_blkbits - 9)) >> 11;
		अगर (sz < 128)
			card->pref_erase = 512 * 1024 / 512;
		अन्यथा अगर (sz < 512)
			card->pref_erase = 1024 * 1024 / 512;
		अन्यथा अगर (sz < 1024)
			card->pref_erase = 2 * 1024 * 1024 / 512;
		अन्यथा
			card->pref_erase = 4 * 1024 * 1024 / 512;
		अगर (card->pref_erase < card->erase_size)
			card->pref_erase = card->erase_size;
		अन्यथा अणु
			sz = card->pref_erase % card->erase_size;
			अगर (sz)
				card->pref_erase += card->erase_size - sz;
		पूर्ण
	पूर्ण अन्यथा
		card->pref_erase = 0;
पूर्ण

अटल अचिन्हित पूर्णांक mmc_mmc_erase_समयout(काष्ठा mmc_card *card,
				          अचिन्हित पूर्णांक arg, अचिन्हित पूर्णांक qty)
अणु
	अचिन्हित पूर्णांक erase_समयout;

	अगर (arg == MMC_DISCARD_ARG ||
	    (arg == MMC_TRIM_ARG && card->ext_csd.rev >= 6)) अणु
		erase_समयout = card->ext_csd.trim_समयout;
	पूर्ण अन्यथा अगर (card->ext_csd.erase_group_def & 1) अणु
		/* High Capacity Erase Group Size uses HC समयouts */
		अगर (arg == MMC_TRIM_ARG)
			erase_समयout = card->ext_csd.trim_समयout;
		अन्यथा
			erase_समयout = card->ext_csd.hc_erase_समयout;
	पूर्ण अन्यथा अणु
		/* CSD Erase Group Size uses ग_लिखो समयout */
		अचिन्हित पूर्णांक mult = (10 << card->csd.r2w_factor);
		अचिन्हित पूर्णांक समयout_clks = card->csd.taac_clks * mult;
		अचिन्हित पूर्णांक समयout_us;

		/* Aव्योम overflow: e.g. taac_ns=80000000 mult=1280 */
		अगर (card->csd.taac_ns < 1000000)
			समयout_us = (card->csd.taac_ns * mult) / 1000;
		अन्यथा
			समयout_us = (card->csd.taac_ns / 1000) * mult;

		/*
		 * ios.घड़ी is only a target.  The real घड़ी rate might be
		 * less but not that much less, so fudge it by multiplying by 2.
		 */
		समयout_clks <<= 1;
		समयout_us += (समयout_clks * 1000) /
			      (card->host->ios.घड़ी / 1000);

		erase_समयout = समयout_us / 1000;

		/*
		 * Theoretically, the calculation could underflow so round up
		 * to 1ms in that हाल.
		 */
		अगर (!erase_समयout)
			erase_समयout = 1;
	पूर्ण

	/* Multiplier क्रम secure operations */
	अगर (arg & MMC_SECURE_ARGS) अणु
		अगर (arg == MMC_SECURE_ERASE_ARG)
			erase_समयout *= card->ext_csd.sec_erase_mult;
		अन्यथा
			erase_समयout *= card->ext_csd.sec_trim_mult;
	पूर्ण

	erase_समयout *= qty;

	/*
	 * Ensure at least a 1 second समयout क्रम SPI as per
	 * 'mmc_set_data_timeout()'
	 */
	अगर (mmc_host_is_spi(card->host) && erase_समयout < 1000)
		erase_समयout = 1000;

	वापस erase_समयout;
पूर्ण

अटल अचिन्हित पूर्णांक mmc_sd_erase_समयout(काष्ठा mmc_card *card,
					 अचिन्हित पूर्णांक arg,
					 अचिन्हित पूर्णांक qty)
अणु
	अचिन्हित पूर्णांक erase_समयout;

	/* क्रम DISCARD none of the below calculation applies.
	 * the busy समयout is 250msec per discard command.
	 */
	अगर (arg == SD_DISCARD_ARG)
		वापस SD_DISCARD_TIMEOUT_MS;

	अगर (card->ssr.erase_समयout) अणु
		/* Erase समयout specअगरied in SD Status Register (SSR) */
		erase_समयout = card->ssr.erase_समयout * qty +
				card->ssr.erase_offset;
	पूर्ण अन्यथा अणु
		/*
		 * Erase समयout not specअगरied in SD Status Register (SSR) so
		 * use 250ms per ग_लिखो block.
		 */
		erase_समयout = 250 * qty;
	पूर्ण

	/* Must not be less than 1 second */
	अगर (erase_समयout < 1000)
		erase_समयout = 1000;

	वापस erase_समयout;
पूर्ण

अटल अचिन्हित पूर्णांक mmc_erase_समयout(काष्ठा mmc_card *card,
				      अचिन्हित पूर्णांक arg,
				      अचिन्हित पूर्णांक qty)
अणु
	अगर (mmc_card_sd(card))
		वापस mmc_sd_erase_समयout(card, arg, qty);
	अन्यथा
		वापस mmc_mmc_erase_समयout(card, arg, qty);
पूर्ण

अटल पूर्णांक mmc_करो_erase(काष्ठा mmc_card *card, अचिन्हित पूर्णांक from,
			अचिन्हित पूर्णांक to, अचिन्हित पूर्णांक arg)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	अचिन्हित पूर्णांक qty = 0, busy_समयout = 0;
	bool use_r1b_resp = false;
	पूर्णांक err;

	mmc_retune_hold(card->host);

	/*
	 * qty is used to calculate the erase समयout which depends on how many
	 * erase groups (or allocation units in SD terminology) are affected.
	 * We count erasing part of an erase group as one erase group.
	 * For SD, the allocation units are always a घातer of 2.  For MMC, the
	 * erase group size is almost certainly also घातer of 2, but it करोes not
	 * seem to insist on that in the JEDEC standard, so we fall back to
	 * भागision in that हाल.  SD may not specअगरy an allocation unit size,
	 * in which हाल the समयout is based on the number of ग_लिखो blocks.
	 *
	 * Note that the समयout क्रम secure trim 2 will only be correct अगर the
	 * number of erase groups specअगरied is the same as the total of all
	 * preceding secure trim 1 commands.  Since the घातer may have been
	 * lost since the secure trim 1 commands occurred, it is generally
	 * impossible to calculate the secure trim 2 समयout correctly.
	 */
	अगर (card->erase_shअगरt)
		qty += ((to >> card->erase_shअगरt) -
			(from >> card->erase_shअगरt)) + 1;
	अन्यथा अगर (mmc_card_sd(card))
		qty += to - from + 1;
	अन्यथा
		qty += ((to / card->erase_size) -
			(from / card->erase_size)) + 1;

	अगर (!mmc_card_blockaddr(card)) अणु
		from <<= 9;
		to <<= 9;
	पूर्ण

	अगर (mmc_card_sd(card))
		cmd.opcode = SD_ERASE_WR_BLK_START;
	अन्यथा
		cmd.opcode = MMC_ERASE_GROUP_START;
	cmd.arg = from;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	err = mmc_रुको_क्रम_cmd(card->host, &cmd, 0);
	अगर (err) अणु
		pr_err("mmc_erase: group start error %d, "
		       "status %#x\n", err, cmd.resp[0]);
		err = -EIO;
		जाओ out;
	पूर्ण

	स_रखो(&cmd, 0, माप(काष्ठा mmc_command));
	अगर (mmc_card_sd(card))
		cmd.opcode = SD_ERASE_WR_BLK_END;
	अन्यथा
		cmd.opcode = MMC_ERASE_GROUP_END;
	cmd.arg = to;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	err = mmc_रुको_क्रम_cmd(card->host, &cmd, 0);
	अगर (err) अणु
		pr_err("mmc_erase: group end error %d, status %#x\n",
		       err, cmd.resp[0]);
		err = -EIO;
		जाओ out;
	पूर्ण

	स_रखो(&cmd, 0, माप(काष्ठा mmc_command));
	cmd.opcode = MMC_ERASE;
	cmd.arg = arg;
	busy_समयout = mmc_erase_समयout(card, arg, qty);
	/*
	 * If the host controller supports busy संकेतling and the समयout क्रम
	 * the erase operation करोes not exceed the max_busy_समयout, we should
	 * use R1B response. Or we need to prevent the host from करोing hw busy
	 * detection, which is करोne by converting to a R1 response instead.
	 * Note, some hosts requires R1B, which also means they are on their own
	 * when it comes to deal with the busy समयout.
	 */
	अगर (!(card->host->caps & MMC_CAP_NEED_RSP_BUSY) &&
	    card->host->max_busy_समयout &&
	    busy_समयout > card->host->max_busy_समयout) अणु
		cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	पूर्ण अन्यथा अणु
		cmd.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
		cmd.busy_समयout = busy_समयout;
		use_r1b_resp = true;
	पूर्ण

	err = mmc_रुको_क्रम_cmd(card->host, &cmd, 0);
	अगर (err) अणु
		pr_err("mmc_erase: erase error %d, status %#x\n",
		       err, cmd.resp[0]);
		err = -EIO;
		जाओ out;
	पूर्ण

	अगर (mmc_host_is_spi(card->host))
		जाओ out;

	/*
	 * In हाल of when R1B + MMC_CAP_WAIT_WHILE_BUSY is used, the polling
	 * shall be aव्योमed.
	 */
	अगर ((card->host->caps & MMC_CAP_WAIT_WHILE_BUSY) && use_r1b_resp)
		जाओ out;

	/* Let's poll to find out when the erase operation completes. */
	err = mmc_poll_क्रम_busy(card, busy_समयout, MMC_BUSY_ERASE);

out:
	mmc_retune_release(card->host);
	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक mmc_align_erase_size(काष्ठा mmc_card *card,
					 अचिन्हित पूर्णांक *from,
					 अचिन्हित पूर्णांक *to,
					 अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक from_new = *from, nr_new = nr, rem;

	/*
	 * When the 'card->erase_size' is घातer of 2, we can use round_up/करोwn()
	 * to align the erase size efficiently.
	 */
	अगर (is_घातer_of_2(card->erase_size)) अणु
		अचिन्हित पूर्णांक temp = from_new;

		from_new = round_up(temp, card->erase_size);
		rem = from_new - temp;

		अगर (nr_new > rem)
			nr_new -= rem;
		अन्यथा
			वापस 0;

		nr_new = round_करोwn(nr_new, card->erase_size);
	पूर्ण अन्यथा अणु
		rem = from_new % card->erase_size;
		अगर (rem) अणु
			rem = card->erase_size - rem;
			from_new += rem;
			अगर (nr_new > rem)
				nr_new -= rem;
			अन्यथा
				वापस 0;
		पूर्ण

		rem = nr_new % card->erase_size;
		अगर (rem)
			nr_new -= rem;
	पूर्ण

	अगर (nr_new == 0)
		वापस 0;

	*to = from_new + nr_new;
	*from = from_new;

	वापस nr_new;
पूर्ण

/**
 * mmc_erase - erase sectors.
 * @card: card to erase
 * @from: first sector to erase
 * @nr: number of sectors to erase
 * @arg: erase command argument
 *
 * Caller must claim host beक्रमe calling this function.
 */
पूर्णांक mmc_erase(काष्ठा mmc_card *card, अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक nr,
	      अचिन्हित पूर्णांक arg)
अणु
	अचिन्हित पूर्णांक rem, to = from + nr;
	पूर्णांक err;

	अगर (!(card->csd.cmdclass & CCC_ERASE))
		वापस -EOPNOTSUPP;

	अगर (!card->erase_size)
		वापस -EOPNOTSUPP;

	अगर (mmc_card_sd(card) && arg != SD_ERASE_ARG && arg != SD_DISCARD_ARG)
		वापस -EOPNOTSUPP;

	अगर (mmc_card_mmc(card) && (arg & MMC_SECURE_ARGS) &&
	    !(card->ext_csd.sec_feature_support & EXT_CSD_SEC_ER_EN))
		वापस -EOPNOTSUPP;

	अगर (mmc_card_mmc(card) && (arg & MMC_TRIM_ARGS) &&
	    !(card->ext_csd.sec_feature_support & EXT_CSD_SEC_GB_CL_EN))
		वापस -EOPNOTSUPP;

	अगर (arg == MMC_SECURE_ERASE_ARG) अणु
		अगर (from % card->erase_size || nr % card->erase_size)
			वापस -EINVAL;
	पूर्ण

	अगर (arg == MMC_ERASE_ARG)
		nr = mmc_align_erase_size(card, &from, &to, nr);

	अगर (nr == 0)
		वापस 0;

	अगर (to <= from)
		वापस -EINVAL;

	/* 'from' and 'to' are inclusive */
	to -= 1;

	/*
	 * Special हाल where only one erase-group fits in the समयout budget:
	 * If the region crosses an erase-group boundary on this particular
	 * हाल, we will be trimming more than one erase-group which, करोes not
	 * fit in the समयout budget of the controller, so we need to split it
	 * and call mmc_करो_erase() twice अगर necessary. This special हाल is
	 * identअगरied by the card->eg_boundary flag.
	 */
	rem = card->erase_size - (from % card->erase_size);
	अगर ((arg & MMC_TRIM_ARGS) && (card->eg_boundary) && (nr > rem)) अणु
		err = mmc_करो_erase(card, from, from + rem - 1, arg);
		from += rem;
		अगर ((err) || (to <= from))
			वापस err;
	पूर्ण

	वापस mmc_करो_erase(card, from, to, arg);
पूर्ण
EXPORT_SYMBOL(mmc_erase);

पूर्णांक mmc_can_erase(काष्ठा mmc_card *card)
अणु
	अगर (card->csd.cmdclass & CCC_ERASE && card->erase_size)
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mmc_can_erase);

पूर्णांक mmc_can_trim(काष्ठा mmc_card *card)
अणु
	अगर ((card->ext_csd.sec_feature_support & EXT_CSD_SEC_GB_CL_EN) &&
	    (!(card->quirks & MMC_QUIRK_TRIM_BROKEN)))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mmc_can_trim);

पूर्णांक mmc_can_discard(काष्ठा mmc_card *card)
अणु
	/*
	 * As there's no way to detect the discard support bit at v4.5
	 * use the s/w feature support filed.
	 */
	अगर (card->ext_csd.feature_support & MMC_DISCARD_FEATURE)
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mmc_can_discard);

पूर्णांक mmc_can_sanitize(काष्ठा mmc_card *card)
अणु
	अगर (!mmc_can_trim(card) && !mmc_can_erase(card))
		वापस 0;
	अगर (card->ext_csd.sec_feature_support & EXT_CSD_SEC_SANITIZE)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक mmc_can_secure_erase_trim(काष्ठा mmc_card *card)
अणु
	अगर ((card->ext_csd.sec_feature_support & EXT_CSD_SEC_ER_EN) &&
	    !(card->quirks & MMC_QUIRK_SEC_ERASE_TRIM_BROKEN))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mmc_can_secure_erase_trim);

पूर्णांक mmc_erase_group_aligned(काष्ठा mmc_card *card, अचिन्हित पूर्णांक from,
			    अचिन्हित पूर्णांक nr)
अणु
	अगर (!card->erase_size)
		वापस 0;
	अगर (from % card->erase_size || nr % card->erase_size)
		वापस 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(mmc_erase_group_aligned);

अटल अचिन्हित पूर्णांक mmc_करो_calc_max_discard(काष्ठा mmc_card *card,
					    अचिन्हित पूर्णांक arg)
अणु
	काष्ठा mmc_host *host = card->host;
	अचिन्हित पूर्णांक max_discard, x, y, qty = 0, max_qty, min_qty, समयout;
	अचिन्हित पूर्णांक last_समयout = 0;
	अचिन्हित पूर्णांक max_busy_समयout = host->max_busy_समयout ?
			host->max_busy_समयout : MMC_ERASE_TIMEOUT_MS;

	अगर (card->erase_shअगरt) अणु
		max_qty = अच_पूर्णांक_उच्च >> card->erase_shअगरt;
		min_qty = card->pref_erase >> card->erase_shअगरt;
	पूर्ण अन्यथा अगर (mmc_card_sd(card)) अणु
		max_qty = अच_पूर्णांक_उच्च;
		min_qty = card->pref_erase;
	पूर्ण अन्यथा अणु
		max_qty = अच_पूर्णांक_उच्च / card->erase_size;
		min_qty = card->pref_erase / card->erase_size;
	पूर्ण

	/*
	 * We should not only use 'host->max_busy_timeout' as the limitation
	 * when deciding the max discard sectors. We should set a balance value
	 * to improve the erase speed, and it can not get too दीर्घ समयout at
	 * the same समय.
	 *
	 * Here we set 'card->pref_erase' as the minimal discard sectors no
	 * matter what size of 'host->max_busy_timeout', but अगर the
	 * 'host->max_busy_timeout' is large enough क्रम more discard sectors,
	 * then we can जारी to increase the max discard sectors until we
	 * get a balance value. In हालs when the 'host->max_busy_timeout'
	 * isn't specअगरied, use the शेष max erase समयout.
	 */
	करो अणु
		y = 0;
		क्रम (x = 1; x && x <= max_qty && max_qty - x >= qty; x <<= 1) अणु
			समयout = mmc_erase_समयout(card, arg, qty + x);

			अगर (qty + x > min_qty && समयout > max_busy_समयout)
				अवरोध;

			अगर (समयout < last_समयout)
				अवरोध;
			last_समयout = समयout;
			y = x;
		पूर्ण
		qty += y;
	पूर्ण जबतक (y);

	अगर (!qty)
		वापस 0;

	/*
	 * When specअगरying a sector range to trim, chances are we might cross
	 * an erase-group boundary even अगर the amount of sectors is less than
	 * one erase-group.
	 * If we can only fit one erase-group in the controller समयout budget,
	 * we have to care that erase-group boundaries are not crossed by a
	 * single trim operation. We flag that special हाल with "eg_boundary".
	 * In all other हालs we can just decrement qty and pretend that we
	 * always touch (qty + 1) erase-groups as a simple optimization.
	 */
	अगर (qty == 1)
		card->eg_boundary = 1;
	अन्यथा
		qty--;

	/* Convert qty to sectors */
	अगर (card->erase_shअगरt)
		max_discard = qty << card->erase_shअगरt;
	अन्यथा अगर (mmc_card_sd(card))
		max_discard = qty + 1;
	अन्यथा
		max_discard = qty * card->erase_size;

	वापस max_discard;
पूर्ण

अचिन्हित पूर्णांक mmc_calc_max_discard(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	अचिन्हित पूर्णांक max_discard, max_trim;

	/*
	 * Without erase_group_def set, MMC erase समयout depends on घड़ी
	 * frequence which can change.  In that हाल, the best choice is
	 * just the preferred erase size.
	 */
	अगर (mmc_card_mmc(card) && !(card->ext_csd.erase_group_def & 1))
		वापस card->pref_erase;

	max_discard = mmc_करो_calc_max_discard(card, MMC_ERASE_ARG);
	अगर (mmc_can_trim(card)) अणु
		max_trim = mmc_करो_calc_max_discard(card, MMC_TRIM_ARG);
		अगर (max_trim < max_discard || max_discard == 0)
			max_discard = max_trim;
	पूर्ण अन्यथा अगर (max_discard < card->erase_size) अणु
		max_discard = 0;
	पूर्ण
	pr_debug("%s: calculated max. discard sectors %u for timeout %u ms\n",
		mmc_hostname(host), max_discard, host->max_busy_समयout ?
		host->max_busy_समयout : MMC_ERASE_TIMEOUT_MS);
	वापस max_discard;
पूर्ण
EXPORT_SYMBOL(mmc_calc_max_discard);

bool mmc_card_is_blockaddr(काष्ठा mmc_card *card)
अणु
	वापस card ? mmc_card_blockaddr(card) : false;
पूर्ण
EXPORT_SYMBOL(mmc_card_is_blockaddr);

पूर्णांक mmc_set_blocklen(काष्ठा mmc_card *card, अचिन्हित पूर्णांक blocklen)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;

	अगर (mmc_card_blockaddr(card) || mmc_card_ddr52(card) ||
	    mmc_card_hs400(card) || mmc_card_hs400es(card))
		वापस 0;

	cmd.opcode = MMC_SET_BLOCKLEN;
	cmd.arg = blocklen;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	वापस mmc_रुको_क्रम_cmd(card->host, &cmd, 5);
पूर्ण
EXPORT_SYMBOL(mmc_set_blocklen);

अटल व्योम mmc_hw_reset_क्रम_init(काष्ठा mmc_host *host)
अणु
	mmc_pwrseq_reset(host);

	अगर (!(host->caps & MMC_CAP_HW_RESET) || !host->ops->hw_reset)
		वापस;
	host->ops->hw_reset(host);
पूर्ण

/**
 * mmc_hw_reset - reset the card in hardware
 * @host: MMC host to which the card is attached
 *
 * Hard reset the card. This function is only क्रम upper layers, like the
 * block layer or card drivers. You cannot use it in host drivers (काष्ठा
 * mmc_card might be gone then).
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक mmc_hw_reset(काष्ठा mmc_host *host)
अणु
	पूर्णांक ret;

	ret = host->bus_ops->hw_reset(host);
	अगर (ret < 0)
		pr_warn("%s: tried to HW reset card, got error %d\n",
			mmc_hostname(host), ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mmc_hw_reset);

पूर्णांक mmc_sw_reset(काष्ठा mmc_host *host)
अणु
	पूर्णांक ret;

	अगर (!host->bus_ops->sw_reset)
		वापस -EOPNOTSUPP;

	ret = host->bus_ops->sw_reset(host);
	अगर (ret)
		pr_warn("%s: tried to SW reset card, got error %d\n",
			mmc_hostname(host), ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mmc_sw_reset);

अटल पूर्णांक mmc_rescan_try_freq(काष्ठा mmc_host *host, अचिन्हित freq)
अणु
	host->f_init = freq;

	pr_debug("%s: %s: trying to init card at %u Hz\n",
		mmc_hostname(host), __func__, host->f_init);

	mmc_घातer_up(host, host->ocr_avail);

	/*
	 * Some eMMCs (with VCCQ always on) may not be reset after घातer up, so
	 * करो a hardware reset अगर possible.
	 */
	mmc_hw_reset_क्रम_init(host);

	/*
	 * sdio_reset sends CMD52 to reset card.  Since we करो not know
	 * अगर the card is being re-initialized, just send it.  CMD52
	 * should be ignored by SD/eMMC cards.
	 * Skip it अगर we alपढ़ोy know that we करो not support SDIO commands
	 */
	अगर (!(host->caps2 & MMC_CAP2_NO_SDIO))
		sdio_reset(host);

	mmc_go_idle(host);

	अगर (!(host->caps2 & MMC_CAP2_NO_SD)) अणु
		अगर (mmc_send_अगर_cond_pcie(host, host->ocr_avail))
			जाओ out;
		अगर (mmc_card_sd_express(host))
			वापस 0;
	पूर्ण

	/* Order's important: probe SDIO, then SD, then MMC */
	अगर (!(host->caps2 & MMC_CAP2_NO_SDIO))
		अगर (!mmc_attach_sdio(host))
			वापस 0;

	अगर (!(host->caps2 & MMC_CAP2_NO_SD))
		अगर (!mmc_attach_sd(host))
			वापस 0;

	अगर (!(host->caps2 & MMC_CAP2_NO_MMC))
		अगर (!mmc_attach_mmc(host))
			वापस 0;

out:
	mmc_घातer_off(host);
	वापस -EIO;
पूर्ण

पूर्णांक _mmc_detect_card_हटाओd(काष्ठा mmc_host *host)
अणु
	पूर्णांक ret;

	अगर (!host->card || mmc_card_हटाओd(host->card))
		वापस 1;

	ret = host->bus_ops->alive(host);

	/*
	 * Card detect status and alive check may be out of sync अगर card is
	 * हटाओd slowly, when card detect चयन changes जबतक card/slot
	 * pads are still contacted in hardware (refer to "SD Card Mechanical
	 * Addendum, Appendix C: Card Detection Switch"). So reschedule a
	 * detect work 200ms later क्रम this हाल.
	 */
	अगर (!ret && host->ops->get_cd && !host->ops->get_cd(host)) अणु
		mmc_detect_change(host, msecs_to_jअगरfies(200));
		pr_debug("%s: card removed too slowly\n", mmc_hostname(host));
	पूर्ण

	अगर (ret) अणु
		mmc_card_set_हटाओd(host->card);
		pr_debug("%s: card remove detected\n", mmc_hostname(host));
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक mmc_detect_card_हटाओd(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_card *card = host->card;
	पूर्णांक ret;

	WARN_ON(!host->claimed);

	अगर (!card)
		वापस 1;

	अगर (!mmc_card_is_removable(host))
		वापस 0;

	ret = mmc_card_हटाओd(card);
	/*
	 * The card will be considered unchanged unless we have been asked to
	 * detect a change or host requires polling to provide card detection.
	 */
	अगर (!host->detect_change && !(host->caps & MMC_CAP_NEEDS_POLL))
		वापस ret;

	host->detect_change = 0;
	अगर (!ret) अणु
		ret = _mmc_detect_card_हटाओd(host);
		अगर (ret && (host->caps & MMC_CAP_NEEDS_POLL)) अणु
			/*
			 * Schedule a detect work as soon as possible to let a
			 * rescan handle the card removal.
			 */
			cancel_delayed_work(&host->detect);
			_mmc_detect_change(host, 0, false);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mmc_detect_card_हटाओd);

व्योम mmc_rescan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_host *host =
		container_of(work, काष्ठा mmc_host, detect.work);
	पूर्णांक i;

	अगर (host->rescan_disable)
		वापस;

	/* If there is a non-removable card रेजिस्टरed, only scan once */
	अगर (!mmc_card_is_removable(host) && host->rescan_entered)
		वापस;
	host->rescan_entered = 1;

	अगर (host->trigger_card_event && host->ops->card_event) अणु
		mmc_claim_host(host);
		host->ops->card_event(host);
		mmc_release_host(host);
		host->trigger_card_event = false;
	पूर्ण

	/* Verअगरy a रेजिस्टरed card to be functional, अन्यथा हटाओ it. */
	अगर (host->bus_ops)
		host->bus_ops->detect(host);

	host->detect_change = 0;

	/* अगर there still is a card present, stop here */
	अगर (host->bus_ops != शून्य)
		जाओ out;

	mmc_claim_host(host);
	अगर (mmc_card_is_removable(host) && host->ops->get_cd &&
			host->ops->get_cd(host) == 0) अणु
		mmc_घातer_off(host);
		mmc_release_host(host);
		जाओ out;
	पूर्ण

	/* If an SD express card is present, then leave it as is. */
	अगर (mmc_card_sd_express(host)) अणु
		mmc_release_host(host);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(freqs); i++) अणु
		अचिन्हित पूर्णांक freq = freqs[i];
		अगर (freq > host->f_max) अणु
			अगर (i + 1 < ARRAY_SIZE(freqs))
				जारी;
			freq = host->f_max;
		पूर्ण
		अगर (!mmc_rescan_try_freq(host, max(freq, host->f_min)))
			अवरोध;
		अगर (freqs[i] <= host->f_min)
			अवरोध;
	पूर्ण
	mmc_release_host(host);

 out:
	अगर (host->caps & MMC_CAP_NEEDS_POLL)
		mmc_schedule_delayed_work(&host->detect, HZ);
पूर्ण

व्योम mmc_start_host(काष्ठा mmc_host *host)
अणु
	host->f_init = max(min(freqs[0], host->f_max), host->f_min);
	host->rescan_disable = 0;

	अगर (!(host->caps2 & MMC_CAP2_NO_PRESCAN_POWERUP)) अणु
		mmc_claim_host(host);
		mmc_घातer_up(host, host->ocr_avail);
		mmc_release_host(host);
	पूर्ण

	mmc_gpiod_request_cd_irq(host);
	_mmc_detect_change(host, 0, false);
पूर्ण

व्योम mmc_stop_host(काष्ठा mmc_host *host)
अणु
	अगर (host->slot.cd_irq >= 0) अणु
		mmc_gpio_set_cd_wake(host, false);
		disable_irq(host->slot.cd_irq);
	पूर्ण

	host->rescan_disable = 1;
	cancel_delayed_work_sync(&host->detect);

	/* clear pm flags now and let card drivers set them as needed */
	host->pm_flags = 0;

	अगर (host->bus_ops) अणु
		/* Calling bus_ops->हटाओ() with a claimed host can deadlock */
		host->bus_ops->हटाओ(host);
		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_घातer_off(host);
		mmc_release_host(host);
		वापस;
	पूर्ण

	mmc_claim_host(host);
	mmc_घातer_off(host);
	mmc_release_host(host);
पूर्ण

अटल पूर्णांक __init mmc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = mmc_रेजिस्टर_bus();
	अगर (ret)
		वापस ret;

	ret = mmc_रेजिस्टर_host_class();
	अगर (ret)
		जाओ unरेजिस्टर_bus;

	ret = sdio_रेजिस्टर_bus();
	अगर (ret)
		जाओ unरेजिस्टर_host_class;

	वापस 0;

unरेजिस्टर_host_class:
	mmc_unरेजिस्टर_host_class();
unरेजिस्टर_bus:
	mmc_unरेजिस्टर_bus();
	वापस ret;
पूर्ण

अटल व्योम __निकास mmc_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_bus();
	mmc_unरेजिस्टर_host_class();
	mmc_unरेजिस्टर_bus();
पूर्ण

subsys_initcall(mmc_init);
module_निकास(mmc_निकास);

MODULE_LICENSE("GPL");
