<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SD/MMC Greybus driver.
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"

काष्ठा gb_sdio_host अणु
	काष्ठा gb_connection	*connection;
	काष्ठा gbphy_device	*gbphy_dev;
	काष्ठा mmc_host		*mmc;
	काष्ठा mmc_request	*mrq;
	काष्ठा mutex		lock;	/* lock क्रम this host */
	माप_प्रकार			data_max;
	spinlock_t		xfer;	/* lock to cancel ongoing transfer */
	bool			xfer_stop;
	काष्ठा workqueue_काष्ठा	*mrq_workqueue;
	काष्ठा work_काष्ठा	mrqwork;
	u8			queued_events;
	bool			हटाओd;
	bool			card_present;
	bool			पढ़ो_only;
पूर्ण;

#घोषणा GB_SDIO_RSP_R1_R5_R6_R7	(GB_SDIO_RSP_PRESENT | GB_SDIO_RSP_CRC | \
				 GB_SDIO_RSP_OPCODE)
#घोषणा GB_SDIO_RSP_R3_R4	(GB_SDIO_RSP_PRESENT)
#घोषणा GB_SDIO_RSP_R2		(GB_SDIO_RSP_PRESENT | GB_SDIO_RSP_CRC | \
				 GB_SDIO_RSP_136)
#घोषणा GB_SDIO_RSP_R1B		(GB_SDIO_RSP_PRESENT | GB_SDIO_RSP_CRC | \
				 GB_SDIO_RSP_OPCODE | GB_SDIO_RSP_BUSY)

/* kernel vdd starts at 0x80 and we need to translate to greybus ones 0x01 */
#घोषणा GB_SDIO_VDD_SHIFT	8

#अगर_अघोषित MMC_CAP2_CORE_RUNTIME_PM
#घोषणा MMC_CAP2_CORE_RUNTIME_PM	0
#पूर्ण_अगर

अटल अंतरभूत bool single_op(काष्ठा mmc_command *cmd)
अणु
	u32 opcode = cmd->opcode;

	वापस opcode == MMC_WRITE_BLOCK ||
	       opcode == MMC_READ_SINGLE_BLOCK;
पूर्ण

अटल व्योम _gb_sdio_set_host_caps(काष्ठा gb_sdio_host *host, u32 r)
अणु
	u32 caps = 0;
	u32 caps2 = 0;

	caps = ((r & GB_SDIO_CAP_NONREMOVABLE) ? MMC_CAP_NONREMOVABLE : 0) |
		((r & GB_SDIO_CAP_4_BIT_DATA) ? MMC_CAP_4_BIT_DATA : 0) |
		((r & GB_SDIO_CAP_8_BIT_DATA) ? MMC_CAP_8_BIT_DATA : 0) |
		((r & GB_SDIO_CAP_MMC_HS) ? MMC_CAP_MMC_HIGHSPEED : 0) |
		((r & GB_SDIO_CAP_SD_HS) ? MMC_CAP_SD_HIGHSPEED : 0) |
		((r & GB_SDIO_CAP_1_2V_DDR) ? MMC_CAP_1_2V_DDR : 0) |
		((r & GB_SDIO_CAP_1_8V_DDR) ? MMC_CAP_1_8V_DDR : 0) |
		((r & GB_SDIO_CAP_POWER_OFF_CARD) ? MMC_CAP_POWER_OFF_CARD : 0) |
		((r & GB_SDIO_CAP_UHS_SDR12) ? MMC_CAP_UHS_SDR12 : 0) |
		((r & GB_SDIO_CAP_UHS_SDR25) ? MMC_CAP_UHS_SDR25 : 0) |
		((r & GB_SDIO_CAP_UHS_SDR50) ? MMC_CAP_UHS_SDR50 : 0) |
		((r & GB_SDIO_CAP_UHS_SDR104) ? MMC_CAP_UHS_SDR104 : 0) |
		((r & GB_SDIO_CAP_UHS_DDR50) ? MMC_CAP_UHS_DDR50 : 0) |
		((r & GB_SDIO_CAP_DRIVER_TYPE_A) ? MMC_CAP_DRIVER_TYPE_A : 0) |
		((r & GB_SDIO_CAP_DRIVER_TYPE_C) ? MMC_CAP_DRIVER_TYPE_C : 0) |
		((r & GB_SDIO_CAP_DRIVER_TYPE_D) ? MMC_CAP_DRIVER_TYPE_D : 0);

	caps2 = ((r & GB_SDIO_CAP_HS200_1_2V) ? MMC_CAP2_HS200_1_2V_SDR : 0) |
		((r & GB_SDIO_CAP_HS400_1_2V) ? MMC_CAP2_HS400_1_2V : 0) |
		((r & GB_SDIO_CAP_HS400_1_8V) ? MMC_CAP2_HS400_1_8V : 0) |
		((r & GB_SDIO_CAP_HS200_1_8V) ? MMC_CAP2_HS200_1_8V_SDR : 0);

	host->mmc->caps = caps;
	host->mmc->caps2 = caps2 | MMC_CAP2_CORE_RUNTIME_PM;

	अगर (caps & MMC_CAP_NONREMOVABLE)
		host->card_present = true;
पूर्ण

अटल u32 _gb_sdio_get_host_ocr(u32 ocr)
अणु
	वापस (((ocr & GB_SDIO_VDD_165_195) ? MMC_VDD_165_195 : 0) |
		((ocr & GB_SDIO_VDD_20_21) ? MMC_VDD_20_21 : 0) |
		((ocr & GB_SDIO_VDD_21_22) ? MMC_VDD_21_22 : 0) |
		((ocr & GB_SDIO_VDD_22_23) ? MMC_VDD_22_23 : 0) |
		((ocr & GB_SDIO_VDD_23_24) ? MMC_VDD_23_24 : 0) |
		((ocr & GB_SDIO_VDD_24_25) ? MMC_VDD_24_25 : 0) |
		((ocr & GB_SDIO_VDD_25_26) ? MMC_VDD_25_26 : 0) |
		((ocr & GB_SDIO_VDD_26_27) ? MMC_VDD_26_27 : 0) |
		((ocr & GB_SDIO_VDD_27_28) ? MMC_VDD_27_28 : 0) |
		((ocr & GB_SDIO_VDD_28_29) ? MMC_VDD_28_29 : 0) |
		((ocr & GB_SDIO_VDD_29_30) ? MMC_VDD_29_30 : 0) |
		((ocr & GB_SDIO_VDD_30_31) ? MMC_VDD_30_31 : 0) |
		((ocr & GB_SDIO_VDD_31_32) ? MMC_VDD_31_32 : 0) |
		((ocr & GB_SDIO_VDD_32_33) ? MMC_VDD_32_33 : 0) |
		((ocr & GB_SDIO_VDD_33_34) ? MMC_VDD_33_34 : 0) |
		((ocr & GB_SDIO_VDD_34_35) ? MMC_VDD_34_35 : 0) |
		((ocr & GB_SDIO_VDD_35_36) ? MMC_VDD_35_36 : 0)
		);
पूर्ण

अटल पूर्णांक gb_sdio_get_caps(काष्ठा gb_sdio_host *host)
अणु
	काष्ठा gb_sdio_get_caps_response response;
	काष्ठा mmc_host *mmc = host->mmc;
	u16 data_max;
	u32 blksz;
	u32 ocr;
	u32 r;
	पूर्णांक ret;

	ret = gb_operation_sync(host->connection, GB_SDIO_TYPE_GET_CAPABILITIES,
				शून्य, 0, &response, माप(response));
	अगर (ret < 0)
		वापस ret;
	r = le32_to_cpu(response.caps);

	_gb_sdio_set_host_caps(host, r);

	/* get the max block size that could fit our payload */
	data_max = gb_operation_get_payload_size_max(host->connection);
	data_max = min(data_max - माप(काष्ठा gb_sdio_transfer_request),
		       data_max - माप(काष्ठा gb_sdio_transfer_response));

	blksz = min_t(u16, le16_to_cpu(response.max_blk_size), data_max);
	blksz = max_t(u32, 512, blksz);

	mmc->max_blk_size = roundकरोwn_घात_of_two(blksz);
	mmc->max_blk_count = le16_to_cpu(response.max_blk_count);
	host->data_max = data_max;

	/* get ocr supported values */
	ocr = _gb_sdio_get_host_ocr(le32_to_cpu(response.ocr));
	mmc->ocr_avail = ocr;
	mmc->ocr_avail_sdio = mmc->ocr_avail;
	mmc->ocr_avail_sd = mmc->ocr_avail;
	mmc->ocr_avail_mmc = mmc->ocr_avail;

	/* get frequency range values */
	mmc->f_min = le32_to_cpu(response.f_min);
	mmc->f_max = le32_to_cpu(response.f_max);

	वापस 0;
पूर्ण

अटल व्योम _gb_queue_event(काष्ठा gb_sdio_host *host, u8 event)
अणु
	अगर (event & GB_SDIO_CARD_INSERTED)
		host->queued_events &= ~GB_SDIO_CARD_REMOVED;
	अन्यथा अगर (event & GB_SDIO_CARD_REMOVED)
		host->queued_events &= ~GB_SDIO_CARD_INSERTED;

	host->queued_events |= event;
पूर्ण

अटल पूर्णांक _gb_sdio_process_events(काष्ठा gb_sdio_host *host, u8 event)
अणु
	u8 state_changed = 0;

	अगर (event & GB_SDIO_CARD_INSERTED) अणु
		अगर (host->mmc->caps & MMC_CAP_NONREMOVABLE)
			वापस 0;
		अगर (host->card_present)
			वापस 0;
		host->card_present = true;
		state_changed = 1;
	पूर्ण

	अगर (event & GB_SDIO_CARD_REMOVED) अणु
		अगर (host->mmc->caps & MMC_CAP_NONREMOVABLE)
			वापस 0;
		अगर (!(host->card_present))
			वापस 0;
		host->card_present = false;
		state_changed = 1;
	पूर्ण

	अगर (event & GB_SDIO_WP)
		host->पढ़ो_only = true;

	अगर (state_changed) अणु
		dev_info(mmc_dev(host->mmc), "card %s now event\n",
			 (host->card_present ?  "inserted" : "removed"));
		mmc_detect_change(host->mmc, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_sdio_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_sdio_host *host = gb_connection_get_data(op->connection);
	काष्ठा gb_message *request;
	काष्ठा gb_sdio_event_request *payload;
	u8 type = op->type;
	पूर्णांक ret =  0;
	u8 event;

	अगर (type != GB_SDIO_TYPE_EVENT) अणु
		dev_err(mmc_dev(host->mmc),
			"unsupported unsolicited event: %u\n", type);
		वापस -EINVAL;
	पूर्ण

	request = op->request;

	अगर (request->payload_size < माप(*payload)) अणु
		dev_err(mmc_dev(host->mmc), "wrong event size received (%zu < %zu)\n",
			request->payload_size, माप(*payload));
		वापस -EINVAL;
	पूर्ण

	payload = request->payload;
	event = payload->event;

	अगर (host->हटाओd)
		_gb_queue_event(host, event);
	अन्यथा
		ret = _gb_sdio_process_events(host, event);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_sdio_set_ios(काष्ठा gb_sdio_host *host,
			   काष्ठा gb_sdio_set_ios_request *request)
अणु
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(host->gbphy_dev);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(host->connection, GB_SDIO_TYPE_SET_IOS, request,
				माप(*request), शून्य, 0);

	gbphy_runसमय_put_स्वतःsuspend(host->gbphy_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक _gb_sdio_send(काष्ठा gb_sdio_host *host, काष्ठा mmc_data *data,
			 माप_प्रकार len, u16 nblocks, off_t skip)
अणु
	काष्ठा gb_sdio_transfer_request *request;
	काष्ठा gb_sdio_transfer_response *response;
	काष्ठा gb_operation *operation;
	काष्ठा scatterlist *sg = data->sg;
	अचिन्हित पूर्णांक sg_len = data->sg_len;
	माप_प्रकार copied;
	u16 send_blksz;
	u16 send_blocks;
	पूर्णांक ret;

	WARN_ON(len > host->data_max);

	operation = gb_operation_create(host->connection, GB_SDIO_TYPE_TRANSFER,
					len + माप(*request),
					माप(*response), GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	request = operation->request->payload;
	request->data_flags = data->flags >> 8;
	request->data_blocks = cpu_to_le16(nblocks);
	request->data_blksz = cpu_to_le16(data->blksz);

	copied = sg_pcopy_to_buffer(sg, sg_len, &request->data[0], len, skip);

	अगर (copied != len) अणु
		ret = -EINVAL;
		जाओ err_put_operation;
	पूर्ण

	ret = gb_operation_request_send_sync(operation);
	अगर (ret < 0)
		जाओ err_put_operation;

	response = operation->response->payload;

	send_blocks = le16_to_cpu(response->data_blocks);
	send_blksz = le16_to_cpu(response->data_blksz);

	अगर (len != send_blksz * send_blocks) अणु
		dev_err(mmc_dev(host->mmc), "send: size received: %zu != %d\n",
			len, send_blksz * send_blocks);
		ret = -EINVAL;
	पूर्ण

err_put_operation:
	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल पूर्णांक _gb_sdio_recv(काष्ठा gb_sdio_host *host, काष्ठा mmc_data *data,
			 माप_प्रकार len, u16 nblocks, off_t skip)
अणु
	काष्ठा gb_sdio_transfer_request *request;
	काष्ठा gb_sdio_transfer_response *response;
	काष्ठा gb_operation *operation;
	काष्ठा scatterlist *sg = data->sg;
	अचिन्हित पूर्णांक sg_len = data->sg_len;
	माप_प्रकार copied;
	u16 recv_blksz;
	u16 recv_blocks;
	पूर्णांक ret;

	WARN_ON(len > host->data_max);

	operation = gb_operation_create(host->connection, GB_SDIO_TYPE_TRANSFER,
					माप(*request),
					len + माप(*response), GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	request = operation->request->payload;
	request->data_flags = data->flags >> 8;
	request->data_blocks = cpu_to_le16(nblocks);
	request->data_blksz = cpu_to_le16(data->blksz);

	ret = gb_operation_request_send_sync(operation);
	अगर (ret < 0)
		जाओ err_put_operation;

	response = operation->response->payload;
	recv_blocks = le16_to_cpu(response->data_blocks);
	recv_blksz = le16_to_cpu(response->data_blksz);

	अगर (len != recv_blksz * recv_blocks) अणु
		dev_err(mmc_dev(host->mmc), "recv: size received: %d != %zu\n",
			recv_blksz * recv_blocks, len);
		ret = -EINVAL;
		जाओ err_put_operation;
	पूर्ण

	copied = sg_pcopy_from_buffer(sg, sg_len, &response->data[0], len,
				      skip);
	अगर (copied != len)
		ret = -EINVAL;

err_put_operation:
	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_sdio_transfer(काष्ठा gb_sdio_host *host, काष्ठा mmc_data *data)
अणु
	माप_प्रकार left, len;
	off_t skip = 0;
	पूर्णांक ret = 0;
	u16 nblocks;

	अगर (single_op(data->mrq->cmd) && data->blocks > 1) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	left = data->blksz * data->blocks;

	जबतक (left) अणु
		/* check is a stop transmission is pending */
		spin_lock(&host->xfer);
		अगर (host->xfer_stop) अणु
			host->xfer_stop = false;
			spin_unlock(&host->xfer);
			ret = -EINTR;
			जाओ out;
		पूर्ण
		spin_unlock(&host->xfer);
		len = min(left, host->data_max);
		nblocks = len / data->blksz;
		len = nblocks * data->blksz;

		अगर (data->flags & MMC_DATA_READ) अणु
			ret = _gb_sdio_recv(host, data, len, nblocks, skip);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अणु
			ret = _gb_sdio_send(host, data, len, nblocks, skip);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
		data->bytes_xfered += len;
		left -= len;
		skip += len;
	पूर्ण

out:
	data->error = ret;
	वापस ret;
पूर्ण

अटल पूर्णांक gb_sdio_command(काष्ठा gb_sdio_host *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा gb_sdio_command_request request = अणु0पूर्ण;
	काष्ठा gb_sdio_command_response response;
	काष्ठा mmc_data *data = host->mrq->data;
	अचिन्हित पूर्णांक समयout_ms;
	u8 cmd_flags;
	u8 cmd_type;
	पूर्णांक i;
	पूर्णांक ret;

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		cmd_flags = GB_SDIO_RSP_NONE;
		अवरोध;
	हाल MMC_RSP_R1:
		cmd_flags = GB_SDIO_RSP_R1_R5_R6_R7;
		अवरोध;
	हाल MMC_RSP_R1B:
		cmd_flags = GB_SDIO_RSP_R1B;
		अवरोध;
	हाल MMC_RSP_R2:
		cmd_flags = GB_SDIO_RSP_R2;
		अवरोध;
	हाल MMC_RSP_R3:
		cmd_flags = GB_SDIO_RSP_R3_R4;
		अवरोध;
	शेष:
		dev_err(mmc_dev(host->mmc), "cmd flag invalid 0x%04x\n",
			mmc_resp_type(cmd));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (mmc_cmd_type(cmd)) अणु
	हाल MMC_CMD_BC:
		cmd_type = GB_SDIO_CMD_BC;
		अवरोध;
	हाल MMC_CMD_BCR:
		cmd_type = GB_SDIO_CMD_BCR;
		अवरोध;
	हाल MMC_CMD_AC:
		cmd_type = GB_SDIO_CMD_AC;
		अवरोध;
	हाल MMC_CMD_ADTC:
		cmd_type = GB_SDIO_CMD_ADTC;
		अवरोध;
	शेष:
		dev_err(mmc_dev(host->mmc), "cmd type invalid 0x%04x\n",
			mmc_cmd_type(cmd));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	request.cmd = cmd->opcode;
	request.cmd_flags = cmd_flags;
	request.cmd_type = cmd_type;
	request.cmd_arg = cpu_to_le32(cmd->arg);
	/* some controllers need to know at command समय data details */
	अगर (data) अणु
		request.data_blocks = cpu_to_le16(data->blocks);
		request.data_blksz = cpu_to_le16(data->blksz);
	पूर्ण

	समयout_ms = cmd->busy_समयout ? cmd->busy_समयout :
		GB_OPERATION_TIMEOUT_DEFAULT;

	ret = gb_operation_sync_समयout(host->connection, GB_SDIO_TYPE_COMMAND,
					&request, माप(request), &response,
					माप(response), समयout_ms);
	अगर (ret < 0)
		जाओ out;

	/* no response expected */
	अगर (cmd_flags == GB_SDIO_RSP_NONE)
		जाओ out;

	/* दीर्घ response expected */
	अगर (cmd_flags & GB_SDIO_RSP_R2)
		क्रम (i = 0; i < 4; i++)
			cmd->resp[i] = le32_to_cpu(response.resp[i]);
	अन्यथा
		cmd->resp[0] = le32_to_cpu(response.resp[0]);

out:
	cmd->error = ret;
	वापस ret;
पूर्ण

अटल व्योम gb_sdio_mrq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gb_sdio_host *host;
	काष्ठा mmc_request *mrq;
	पूर्णांक ret;

	host = container_of(work, काष्ठा gb_sdio_host, mrqwork);

	ret = gbphy_runसमय_get_sync(host->gbphy_dev);
	अगर (ret)
		वापस;

	mutex_lock(&host->lock);
	mrq = host->mrq;
	अगर (!mrq) अणु
		mutex_unlock(&host->lock);
		gbphy_runसमय_put_स्वतःsuspend(host->gbphy_dev);
		dev_err(mmc_dev(host->mmc), "mmc request is NULL");
		वापस;
	पूर्ण

	अगर (host->हटाओd) अणु
		mrq->cmd->error = -ESHUTDOWN;
		जाओ करोne;
	पूर्ण

	अगर (mrq->sbc) अणु
		ret = gb_sdio_command(host, mrq->sbc);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	ret = gb_sdio_command(host, mrq->cmd);
	अगर (ret < 0)
		जाओ करोne;

	अगर (mrq->data) अणु
		ret = gb_sdio_transfer(host, mrq->data);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	अगर (mrq->stop) अणु
		ret = gb_sdio_command(host, mrq->stop);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

करोne:
	host->mrq = शून्य;
	mutex_unlock(&host->lock);
	mmc_request_करोne(host->mmc, mrq);
	gbphy_runसमय_put_स्वतःsuspend(host->gbphy_dev);
पूर्ण

अटल व्योम gb_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा gb_sdio_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd = mrq->cmd;

	/* Check अगर it is a cancel to ongoing transfer */
	अगर (cmd->opcode == MMC_STOP_TRANSMISSION) अणु
		spin_lock(&host->xfer);
		host->xfer_stop = true;
		spin_unlock(&host->xfer);
	पूर्ण

	mutex_lock(&host->lock);

	WARN_ON(host->mrq);
	host->mrq = mrq;

	अगर (host->हटाओd) अणु
		mrq->cmd->error = -ESHUTDOWN;
		जाओ out;
	पूर्ण
	अगर (!host->card_present) अणु
		mrq->cmd->error = -ENOMEDIUM;
		जाओ out;
	पूर्ण

	queue_work(host->mrq_workqueue, &host->mrqwork);

	mutex_unlock(&host->lock);
	वापस;

out:
	host->mrq = शून्य;
	mutex_unlock(&host->lock);
	mmc_request_करोne(mmc, mrq);
पूर्ण

अटल व्योम gb_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा gb_sdio_host *host = mmc_priv(mmc);
	काष्ठा gb_sdio_set_ios_request request;
	पूर्णांक ret;
	u8 घातer_mode;
	u8 bus_width;
	u8 timing;
	u8 संकेत_voltage;
	u8 drv_type;
	u32 vdd = 0;

	mutex_lock(&host->lock);
	request.घड़ी = cpu_to_le32(ios->घड़ी);

	अगर (ios->vdd)
		vdd = 1 << (ios->vdd - GB_SDIO_VDD_SHIFT);
	request.vdd = cpu_to_le32(vdd);

	request.bus_mode = ios->bus_mode == MMC_BUSMODE_OPENDRAIN ?
			    GB_SDIO_BUSMODE_OPENDRAIN :
			    GB_SDIO_BUSMODE_PUSHPULL;

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
	शेष:
		घातer_mode = GB_SDIO_POWER_OFF;
		अवरोध;
	हाल MMC_POWER_UP:
		घातer_mode = GB_SDIO_POWER_UP;
		अवरोध;
	हाल MMC_POWER_ON:
		घातer_mode = GB_SDIO_POWER_ON;
		अवरोध;
	हाल MMC_POWER_UNDEFINED:
		घातer_mode = GB_SDIO_POWER_UNDEFINED;
		अवरोध;
	पूर्ण
	request.घातer_mode = घातer_mode;

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		bus_width = GB_SDIO_BUS_WIDTH_1;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
	शेष:
		bus_width = GB_SDIO_BUS_WIDTH_4;
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		bus_width = GB_SDIO_BUS_WIDTH_8;
		अवरोध;
	पूर्ण
	request.bus_width = bus_width;

	चयन (ios->timing) अणु
	हाल MMC_TIMING_LEGACY:
	शेष:
		timing = GB_SDIO_TIMING_LEGACY;
		अवरोध;
	हाल MMC_TIMING_MMC_HS:
		timing = GB_SDIO_TIMING_MMC_HS;
		अवरोध;
	हाल MMC_TIMING_SD_HS:
		timing = GB_SDIO_TIMING_SD_HS;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR12:
		timing = GB_SDIO_TIMING_UHS_SDR12;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR25:
		timing = GB_SDIO_TIMING_UHS_SDR25;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		timing = GB_SDIO_TIMING_UHS_SDR50;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
		timing = GB_SDIO_TIMING_UHS_SDR104;
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
		timing = GB_SDIO_TIMING_UHS_DDR50;
		अवरोध;
	हाल MMC_TIMING_MMC_DDR52:
		timing = GB_SDIO_TIMING_MMC_DDR52;
		अवरोध;
	हाल MMC_TIMING_MMC_HS200:
		timing = GB_SDIO_TIMING_MMC_HS200;
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		timing = GB_SDIO_TIMING_MMC_HS400;
		अवरोध;
	पूर्ण
	request.timing = timing;

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		संकेत_voltage = GB_SDIO_SIGNAL_VOLTAGE_330;
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
	शेष:
		संकेत_voltage = GB_SDIO_SIGNAL_VOLTAGE_180;
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_120:
		संकेत_voltage = GB_SDIO_SIGNAL_VOLTAGE_120;
		अवरोध;
	पूर्ण
	request.संकेत_voltage = संकेत_voltage;

	चयन (ios->drv_type) अणु
	हाल MMC_SET_DRIVER_TYPE_A:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_A;
		अवरोध;
	हाल MMC_SET_DRIVER_TYPE_C:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_C;
		अवरोध;
	हाल MMC_SET_DRIVER_TYPE_D:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_D;
		अवरोध;
	हाल MMC_SET_DRIVER_TYPE_B:
	शेष:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_B;
		अवरोध;
	पूर्ण
	request.drv_type = drv_type;

	ret = gb_sdio_set_ios(host, &request);
	अगर (ret < 0)
		जाओ out;

	स_नकल(&mmc->ios, ios, माप(mmc->ios));

out:
	mutex_unlock(&host->lock);
पूर्ण

अटल पूर्णांक gb_mmc_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा gb_sdio_host *host = mmc_priv(mmc);

	mutex_lock(&host->lock);
	अगर (host->हटाओd) अणु
		mutex_unlock(&host->lock);
		वापस -ESHUTDOWN;
	पूर्ण
	mutex_unlock(&host->lock);

	वापस host->पढ़ो_only;
पूर्ण

अटल पूर्णांक gb_mmc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा gb_sdio_host *host = mmc_priv(mmc);

	mutex_lock(&host->lock);
	अगर (host->हटाओd) अणु
		mutex_unlock(&host->lock);
		वापस -ESHUTDOWN;
	पूर्ण
	mutex_unlock(&host->lock);

	वापस host->card_present;
पूर्ण

अटल पूर्णांक gb_mmc_चयन_voltage(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops gb_sdio_ops = अणु
	.request	= gb_mmc_request,
	.set_ios	= gb_mmc_set_ios,
	.get_ro		= gb_mmc_get_ro,
	.get_cd		= gb_mmc_get_cd,
	.start_संकेत_voltage_चयन	= gb_mmc_चयन_voltage,
पूर्ण;

अटल पूर्णांक gb_sdio_probe(काष्ठा gbphy_device *gbphy_dev,
			 स्थिर काष्ठा gbphy_device_id *id)
अणु
	काष्ठा gb_connection *connection;
	काष्ठा mmc_host *mmc;
	काष्ठा gb_sdio_host *host;
	पूर्णांक ret = 0;

	mmc = mmc_alloc_host(माप(*host), &gbphy_dev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  gb_sdio_request_handler);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ निकास_mmc_मुक्त;
	पूर्ण

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->हटाओd = true;

	host->connection = connection;
	gb_connection_set_data(connection, host);
	host->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, host);

	ret = gb_connection_enable_tx(connection);
	अगर (ret)
		जाओ निकास_connection_destroy;

	ret = gb_sdio_get_caps(host);
	अगर (ret < 0)
		जाओ निकास_connection_disable;

	mmc->ops = &gb_sdio_ops;

	mmc->max_segs = host->mmc->max_blk_count;

	/* क्रम now we make a map 1:1 between max request and segment size */
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_seg_size = mmc->max_req_size;

	mutex_init(&host->lock);
	spin_lock_init(&host->xfer);
	host->mrq_workqueue = alloc_workqueue("mmc-%s", 0, 1,
					      dev_name(&gbphy_dev->dev));
	अगर (!host->mrq_workqueue) अणु
		ret = -ENOMEM;
		जाओ निकास_connection_disable;
	पूर्ण
	INIT_WORK(&host->mrqwork, gb_sdio_mrq_work);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ निकास_wq_destroy;

	ret = mmc_add_host(mmc);
	अगर (ret < 0)
		जाओ निकास_wq_destroy;
	host->हटाओd = false;
	ret = _gb_sdio_process_events(host, host->queued_events);
	host->queued_events = 0;

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);

	वापस ret;

निकास_wq_destroy:
	destroy_workqueue(host->mrq_workqueue);
निकास_connection_disable:
	gb_connection_disable(connection);
निकास_connection_destroy:
	gb_connection_destroy(connection);
निकास_mmc_मुक्त:
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल व्योम gb_sdio_हटाओ(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा gb_sdio_host *host = gb_gbphy_get_data(gbphy_dev);
	काष्ठा gb_connection *connection = host->connection;
	काष्ठा mmc_host *mmc;
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		gbphy_runसमय_get_noresume(gbphy_dev);

	mutex_lock(&host->lock);
	host->हटाओd = true;
	mmc = host->mmc;
	gb_connection_set_data(connection, शून्य);
	mutex_unlock(&host->lock);

	flush_workqueue(host->mrq_workqueue);
	destroy_workqueue(host->mrq_workqueue);
	gb_connection_disable_rx(connection);
	mmc_हटाओ_host(mmc);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	mmc_मुक्त_host(mmc);
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id gb_sdio_id_table[] = अणु
	अणु GBPHY_PROTOCOL(GREYBUS_PROTOCOL_SDIO) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(gbphy, gb_sdio_id_table);

अटल काष्ठा gbphy_driver sdio_driver = अणु
	.name		= "sdio",
	.probe		= gb_sdio_probe,
	.हटाओ		= gb_sdio_हटाओ,
	.id_table	= gb_sdio_id_table,
पूर्ण;

module_gbphy_driver(sdio_driver);
MODULE_LICENSE("GPL v2");
