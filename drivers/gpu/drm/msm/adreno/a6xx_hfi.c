<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017-2018 The Linux Foundation. All rights reserved. */

#समावेश <linux/completion.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/list.h>

#समावेश "a6xx_gmu.h"
#समावेश "a6xx_gmu.xml.h"
#समावेश "a6xx_gpu.h"

#घोषणा HFI_MSG_ID(val) [val] = #val

अटल स्थिर अक्षर * स्थिर a6xx_hfi_msg_id[] = अणु
	HFI_MSG_ID(HFI_H2F_MSG_INIT),
	HFI_MSG_ID(HFI_H2F_MSG_FW_VERSION),
	HFI_MSG_ID(HFI_H2F_MSG_BW_TABLE),
	HFI_MSG_ID(HFI_H2F_MSG_PERF_TABLE),
	HFI_MSG_ID(HFI_H2F_MSG_TEST),
	HFI_MSG_ID(HFI_H2F_MSG_START),
	HFI_MSG_ID(HFI_H2F_MSG_CORE_FW_START),
	HFI_MSG_ID(HFI_H2F_MSG_GX_BW_PERF_VOTE),
	HFI_MSG_ID(HFI_H2F_MSG_PREPARE_SLUMBER),
पूर्ण;

अटल पूर्णांक a6xx_hfi_queue_पढ़ो(काष्ठा a6xx_gmu *gmu,
	काष्ठा a6xx_hfi_queue *queue, u32 *data, u32 dwords)
अणु
	काष्ठा a6xx_hfi_queue_header *header = queue->header;
	u32 i, hdr, index = header->पढ़ो_index;

	अगर (header->पढ़ो_index == header->ग_लिखो_index) अणु
		header->rx_request = 1;
		वापस 0;
	पूर्ण

	hdr = queue->data[index];

	/*
	 * If we are to assume that the GMU firmware is in fact a rational actor
	 * and is programmed to not send us a larger response than we expect
	 * then we can also assume that अगर the header size is unexpectedly large
	 * that it is due to memory corruption and/or hardware failure. In this
	 * हाल the only reasonable course of action is to BUG() to help harden
	 * the failure.
	 */

	BUG_ON(HFI_HEADER_SIZE(hdr) > dwords);

	क्रम (i = 0; i < HFI_HEADER_SIZE(hdr); i++) अणु
		data[i] = queue->data[index];
		index = (index + 1) % header->size;
	पूर्ण

	अगर (!gmu->legacy)
		index = ALIGN(index, 4) % header->size;

	header->पढ़ो_index = index;
	वापस HFI_HEADER_SIZE(hdr);
पूर्ण

अटल पूर्णांक a6xx_hfi_queue_ग_लिखो(काष्ठा a6xx_gmu *gmu,
	काष्ठा a6xx_hfi_queue *queue, u32 *data, u32 dwords)
अणु
	काष्ठा a6xx_hfi_queue_header *header = queue->header;
	u32 i, space, index = header->ग_लिखो_index;

	spin_lock(&queue->lock);

	space = CIRC_SPACE(header->ग_लिखो_index, header->पढ़ो_index,
		header->size);
	अगर (space < dwords) अणु
		header->dropped++;
		spin_unlock(&queue->lock);
		वापस -ENOSPC;
	पूर्ण

	क्रम (i = 0; i < dwords; i++) अणु
		queue->data[index] = data[i];
		index = (index + 1) % header->size;
	पूर्ण

	/* Cookअगरy any non used data at the end of the ग_लिखो buffer */
	अगर (!gmu->legacy) अणु
		क्रम (; index % 4; index = (index + 1) % header->size)
			queue->data[index] = 0xfafafafa;
	पूर्ण

	header->ग_लिखो_index = index;
	spin_unlock(&queue->lock);

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET, 0x01);
	वापस 0;
पूर्ण

अटल पूर्णांक a6xx_hfi_रुको_क्रम_ack(काष्ठा a6xx_gmu *gmu, u32 id, u32 seqnum,
		u32 *payload, u32 payload_size)
अणु
	काष्ठा a6xx_hfi_queue *queue = &gmu->queues[HFI_RESPONSE_QUEUE];
	u32 val;
	पूर्णांक ret;

	/* Wait क्रम a response */
	ret = gmu_poll_समयout(gmu, REG_A6XX_GMU_GMU2HOST_INTR_INFO, val,
		val & A6XX_GMU_GMU2HOST_INTR_INFO_MSGQ, 100, 5000);

	अगर (ret) अणु
		DRM_DEV_ERROR(gmu->dev,
			"Message %s id %d timed out waiting for response\n",
			a6xx_hfi_msg_id[id], seqnum);
		वापस -ETIMEDOUT;
	पूर्ण

	/* Clear the पूर्णांकerrupt */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_CLR,
		A6XX_GMU_GMU2HOST_INTR_INFO_MSGQ);

	क्रम (;;) अणु
		काष्ठा a6xx_hfi_msg_response resp;

		/* Get the next packet */
		ret = a6xx_hfi_queue_पढ़ो(gmu, queue, (u32 *) &resp,
			माप(resp) >> 2);

		/* If the queue is empty our response never made it */
		अगर (!ret) अणु
			DRM_DEV_ERROR(gmu->dev,
				"The HFI response queue is unexpectedly empty\n");

			वापस -ENOENT;
		पूर्ण

		अगर (HFI_HEADER_ID(resp.header) == HFI_F2H_MSG_ERROR) अणु
			काष्ठा a6xx_hfi_msg_error *error =
				(काष्ठा a6xx_hfi_msg_error *) &resp;

			DRM_DEV_ERROR(gmu->dev, "GMU firmware error %d\n",
				error->code);
			जारी;
		पूर्ण

		अगर (seqnum != HFI_HEADER_SEQNUM(resp.ret_header)) अणु
			DRM_DEV_ERROR(gmu->dev,
				"Unexpected message id %d on the response queue\n",
				HFI_HEADER_SEQNUM(resp.ret_header));
			जारी;
		पूर्ण

		अगर (resp.error) अणु
			DRM_DEV_ERROR(gmu->dev,
				"Message %s id %d returned error %d\n",
				a6xx_hfi_msg_id[id], seqnum, resp.error);
			वापस -EINVAL;
		पूर्ण

		/* All is well, copy over the buffer */
		अगर (payload && payload_size)
			स_नकल(payload, resp.payload,
				min_t(u32, payload_size, माप(resp.payload)));

		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक a6xx_hfi_send_msg(काष्ठा a6xx_gmu *gmu, पूर्णांक id,
		व्योम *data, u32 size, u32 *payload, u32 payload_size)
अणु
	काष्ठा a6xx_hfi_queue *queue = &gmu->queues[HFI_COMMAND_QUEUE];
	पूर्णांक ret, dwords = size >> 2;
	u32 seqnum;

	seqnum = atomic_inc_वापस(&queue->seqnum) % 0xfff;

	/* First dword of the message is the message header - fill it in */
	*((u32 *) data) = (seqnum << 20) | (HFI_MSG_CMD << 16) |
		(dwords << 8) | id;

	ret = a6xx_hfi_queue_ग_लिखो(gmu, queue, data, dwords);
	अगर (ret) अणु
		DRM_DEV_ERROR(gmu->dev, "Unable to send message %s id %d\n",
			a6xx_hfi_msg_id[id], seqnum);
		वापस ret;
	पूर्ण

	वापस a6xx_hfi_रुको_क्रम_ack(gmu, id, seqnum, payload, payload_size);
पूर्ण

अटल पूर्णांक a6xx_hfi_send_gmu_init(काष्ठा a6xx_gmu *gmu, पूर्णांक boot_state)
अणु
	काष्ठा a6xx_hfi_msg_gmu_init_cmd msg = अणु 0 पूर्ण;

	msg.dbg_buffer_addr = (u32) gmu->debug.iova;
	msg.dbg_buffer_size = (u32) gmu->debug.size;
	msg.boot_state = boot_state;

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_INIT, &msg, माप(msg),
		शून्य, 0);
पूर्ण

अटल पूर्णांक a6xx_hfi_get_fw_version(काष्ठा a6xx_gmu *gmu, u32 *version)
अणु
	काष्ठा a6xx_hfi_msg_fw_version msg = अणु 0 पूर्ण;

	/* Currently supporting version 1.1 */
	msg.supported_version = (1 << 28) | (1 << 16);

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_FW_VERSION, &msg, माप(msg),
		version, माप(*version));
पूर्ण

अटल पूर्णांक a6xx_hfi_send_perf_table_v1(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_hfi_msg_perf_table_v1 msg = अणु 0 पूर्ण;
	पूर्णांक i;

	msg.num_gpu_levels = gmu->nr_gpu_freqs;
	msg.num_gmu_levels = gmu->nr_gmu_freqs;

	क्रम (i = 0; i < gmu->nr_gpu_freqs; i++) अणु
		msg.gx_votes[i].vote = gmu->gx_arc_votes[i];
		msg.gx_votes[i].freq = gmu->gpu_freqs[i] / 1000;
	पूर्ण

	क्रम (i = 0; i < gmu->nr_gmu_freqs; i++) अणु
		msg.cx_votes[i].vote = gmu->cx_arc_votes[i];
		msg.cx_votes[i].freq = gmu->gmu_freqs[i] / 1000;
	पूर्ण

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_PERF_TABLE, &msg, माप(msg),
		शून्य, 0);
पूर्ण

अटल पूर्णांक a6xx_hfi_send_perf_table(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_hfi_msg_perf_table msg = अणु 0 पूर्ण;
	पूर्णांक i;

	msg.num_gpu_levels = gmu->nr_gpu_freqs;
	msg.num_gmu_levels = gmu->nr_gmu_freqs;

	क्रम (i = 0; i < gmu->nr_gpu_freqs; i++) अणु
		msg.gx_votes[i].vote = gmu->gx_arc_votes[i];
		msg.gx_votes[i].acd = 0xffffffff;
		msg.gx_votes[i].freq = gmu->gpu_freqs[i] / 1000;
	पूर्ण

	क्रम (i = 0; i < gmu->nr_gmu_freqs; i++) अणु
		msg.cx_votes[i].vote = gmu->cx_arc_votes[i];
		msg.cx_votes[i].freq = gmu->gmu_freqs[i] / 1000;
	पूर्ण

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_PERF_TABLE, &msg, माप(msg),
		शून्य, 0);
पूर्ण

अटल व्योम a618_build_bw_table(काष्ठा a6xx_hfi_msg_bw_table *msg)
अणु
	/* Send a single "off" entry since the 618 GMU करोesn't करो bus scaling */
	msg->bw_level_num = 1;

	msg->ddr_cmds_num = 3;
	msg->ddr_रुको_biपंचांगask = 0x01;

	msg->ddr_cmds_addrs[0] = 0x50000;
	msg->ddr_cmds_addrs[1] = 0x5003c;
	msg->ddr_cmds_addrs[2] = 0x5000c;

	msg->ddr_cmds_data[0][0] =  0x40000000;
	msg->ddr_cmds_data[0][1] =  0x40000000;
	msg->ddr_cmds_data[0][2] =  0x40000000;

	/*
	 * These are the CX (CNOC) votes - these are used by the GMU but the
	 * votes are known and fixed क्रम the target
	 */
	msg->cnoc_cmds_num = 1;
	msg->cnoc_रुको_biपंचांगask = 0x01;

	msg->cnoc_cmds_addrs[0] = 0x5007c;
	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[1][0] =  0x60000001;
पूर्ण

अटल व्योम a640_build_bw_table(काष्ठा a6xx_hfi_msg_bw_table *msg)
अणु
	/*
	 * Send a single "off" entry just to get things running
	 * TODO: bus scaling
	 */
	msg->bw_level_num = 1;

	msg->ddr_cmds_num = 3;
	msg->ddr_रुको_biपंचांगask = 0x01;

	msg->ddr_cmds_addrs[0] = 0x50000;
	msg->ddr_cmds_addrs[1] = 0x5003c;
	msg->ddr_cmds_addrs[2] = 0x5000c;

	msg->ddr_cmds_data[0][0] =  0x40000000;
	msg->ddr_cmds_data[0][1] =  0x40000000;
	msg->ddr_cmds_data[0][2] =  0x40000000;

	/*
	 * These are the CX (CNOC) votes - these are used by the GMU but the
	 * votes are known and fixed क्रम the target
	 */
	msg->cnoc_cmds_num = 3;
	msg->cnoc_रुको_biपंचांगask = 0x01;

	msg->cnoc_cmds_addrs[0] = 0x50034;
	msg->cnoc_cmds_addrs[1] = 0x5007c;
	msg->cnoc_cmds_addrs[2] = 0x5004c;

	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[0][1] =  0x00000000;
	msg->cnoc_cmds_data[0][2] =  0x40000000;

	msg->cnoc_cmds_data[1][0] =  0x60000001;
	msg->cnoc_cmds_data[1][1] =  0x20000001;
	msg->cnoc_cmds_data[1][2] =  0x60000001;
पूर्ण

अटल व्योम a650_build_bw_table(काष्ठा a6xx_hfi_msg_bw_table *msg)
अणु
	/*
	 * Send a single "off" entry just to get things running
	 * TODO: bus scaling
	 */
	msg->bw_level_num = 1;

	msg->ddr_cmds_num = 3;
	msg->ddr_रुको_biपंचांगask = 0x01;

	msg->ddr_cmds_addrs[0] = 0x50000;
	msg->ddr_cmds_addrs[1] = 0x50004;
	msg->ddr_cmds_addrs[2] = 0x5007c;

	msg->ddr_cmds_data[0][0] =  0x40000000;
	msg->ddr_cmds_data[0][1] =  0x40000000;
	msg->ddr_cmds_data[0][2] =  0x40000000;

	/*
	 * These are the CX (CNOC) votes - these are used by the GMU but the
	 * votes are known and fixed क्रम the target
	 */
	msg->cnoc_cmds_num = 1;
	msg->cnoc_रुको_biपंचांगask = 0x01;

	msg->cnoc_cmds_addrs[0] = 0x500a4;
	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[1][0] =  0x60000001;
पूर्ण

अटल व्योम a6xx_build_bw_table(काष्ठा a6xx_hfi_msg_bw_table *msg)
अणु
	/* Send a single "off" entry since the 630 GMU करोesn't करो bus scaling */
	msg->bw_level_num = 1;

	msg->ddr_cmds_num = 3;
	msg->ddr_रुको_biपंचांगask = 0x07;

	msg->ddr_cmds_addrs[0] = 0x50000;
	msg->ddr_cmds_addrs[1] = 0x5005c;
	msg->ddr_cmds_addrs[2] = 0x5000c;

	msg->ddr_cmds_data[0][0] =  0x40000000;
	msg->ddr_cmds_data[0][1] =  0x40000000;
	msg->ddr_cmds_data[0][2] =  0x40000000;

	/*
	 * These are the CX (CNOC) votes.  This is used but the values क्रम the
	 * sdm845 GMU are known and fixed so we can hard code them.
	 */

	msg->cnoc_cmds_num = 3;
	msg->cnoc_रुको_biपंचांगask = 0x05;

	msg->cnoc_cmds_addrs[0] = 0x50034;
	msg->cnoc_cmds_addrs[1] = 0x5007c;
	msg->cnoc_cmds_addrs[2] = 0x5004c;

	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[0][1] =  0x00000000;
	msg->cnoc_cmds_data[0][2] =  0x40000000;

	msg->cnoc_cmds_data[1][0] =  0x60000001;
	msg->cnoc_cmds_data[1][1] =  0x20000001;
	msg->cnoc_cmds_data[1][2] =  0x60000001;
पूर्ण


अटल पूर्णांक a6xx_hfi_send_bw_table(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_hfi_msg_bw_table msg = अणु 0 पूर्ण;
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;

	अगर (adreno_is_a618(adreno_gpu))
		a618_build_bw_table(&msg);
	अन्यथा अगर (adreno_is_a640(adreno_gpu))
		a640_build_bw_table(&msg);
	अन्यथा अगर (adreno_is_a650(adreno_gpu))
		a650_build_bw_table(&msg);
	अन्यथा
		a6xx_build_bw_table(&msg);

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_BW_TABLE, &msg, माप(msg),
		शून्य, 0);
पूर्ण

अटल पूर्णांक a6xx_hfi_send_test(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_hfi_msg_test msg = अणु 0 पूर्ण;

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_TEST, &msg, माप(msg),
		शून्य, 0);
पूर्ण

अटल पूर्णांक a6xx_hfi_send_start(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_hfi_msg_start msg = अणु 0 पूर्ण;

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_START, &msg, माप(msg),
		शून्य, 0);
पूर्ण

अटल पूर्णांक a6xx_hfi_send_core_fw_start(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_hfi_msg_core_fw_start msg = अणु 0 पूर्ण;

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_CORE_FW_START, &msg,
		माप(msg), शून्य, 0);
पूर्ण

पूर्णांक a6xx_hfi_set_freq(काष्ठा a6xx_gmu *gmu, पूर्णांक index)
अणु
	काष्ठा a6xx_hfi_gx_bw_perf_vote_cmd msg = अणु 0 पूर्ण;

	msg.ack_type = 1; /* blocking */
	msg.freq = index;
	msg.bw = 0; /* TODO: bus scaling */

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_GX_BW_PERF_VOTE, &msg,
		माप(msg), शून्य, 0);
पूर्ण

पूर्णांक a6xx_hfi_send_prep_slumber(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_hfi_prep_slumber_cmd msg = अणु 0 पूर्ण;

	/* TODO: should freq and bw fields be non-zero ? */

	वापस a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_PREPARE_SLUMBER, &msg,
		माप(msg), शून्य, 0);
पूर्ण

अटल पूर्णांक a6xx_hfi_start_v1(काष्ठा a6xx_gmu *gmu, पूर्णांक boot_state)
अणु
	पूर्णांक ret;

	ret = a6xx_hfi_send_gmu_init(gmu, boot_state);
	अगर (ret)
		वापस ret;

	ret = a6xx_hfi_get_fw_version(gmu, शून्य);
	अगर (ret)
		वापस ret;

	/*
	 * We have to get exchange version numbers per the sequence but at this
	 * poपूर्णांक th kernel driver करोesn't need to know the exact version of
	 * the GMU firmware
	 */

	ret = a6xx_hfi_send_perf_table_v1(gmu);
	अगर (ret)
		वापस ret;

	ret = a6xx_hfi_send_bw_table(gmu);
	अगर (ret)
		वापस ret;

	/*
	 * Let the GMU know that there won't be any more HFI messages until next
	 * boot
	 */
	a6xx_hfi_send_test(gmu);

	वापस 0;
पूर्ण

पूर्णांक a6xx_hfi_start(काष्ठा a6xx_gmu *gmu, पूर्णांक boot_state)
अणु
	पूर्णांक ret;

	अगर (gmu->legacy)
		वापस a6xx_hfi_start_v1(gmu, boot_state);


	ret = a6xx_hfi_send_perf_table(gmu);
	अगर (ret)
		वापस ret;

	ret = a6xx_hfi_send_bw_table(gmu);
	अगर (ret)
		वापस ret;

	ret = a6xx_hfi_send_core_fw_start(gmu);
	अगर (ret)
		वापस ret;

	/*
	 * Downstream driver sends this in its "a6xx_hw_init" equivalent,
	 * but seems to be no harm in sending it here
	 */
	ret = a6xx_hfi_send_start(gmu);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

व्योम a6xx_hfi_stop(काष्ठा a6xx_gmu *gmu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gmu->queues); i++) अणु
		काष्ठा a6xx_hfi_queue *queue = &gmu->queues[i];

		अगर (!queue->header)
			जारी;

		अगर (queue->header->पढ़ो_index != queue->header->ग_लिखो_index)
			DRM_DEV_ERROR(gmu->dev, "HFI queue %d is not empty\n", i);

		queue->header->पढ़ो_index = 0;
		queue->header->ग_लिखो_index = 0;
	पूर्ण
पूर्ण

अटल व्योम a6xx_hfi_queue_init(काष्ठा a6xx_hfi_queue *queue,
		काष्ठा a6xx_hfi_queue_header *header, व्योम *virt, u64 iova,
		u32 id)
अणु
	spin_lock_init(&queue->lock);
	queue->header = header;
	queue->data = virt;
	atomic_set(&queue->seqnum, 0);

	/* Set up the shared memory header */
	header->iova = iova;
	header->type =  10 << 8 | id;
	header->status = 1;
	header->size = SZ_4K >> 2;
	header->msg_size = 0;
	header->dropped = 0;
	header->rx_watermark = 1;
	header->tx_watermark = 1;
	header->rx_request = 1;
	header->tx_request = 0;
	header->पढ़ो_index = 0;
	header->ग_लिखो_index = 0;
पूर्ण

व्योम a6xx_hfi_init(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_gmu_bo *hfi = &gmu->hfi;
	काष्ठा a6xx_hfi_queue_table_header *table = hfi->virt;
	काष्ठा a6xx_hfi_queue_header *headers = hfi->virt + माप(*table);
	u64 offset;
	पूर्णांक table_size;

	/*
	 * The table size is the size of the table header plus all of the queue
	 * headers
	 */
	table_size = माप(*table);
	table_size += (ARRAY_SIZE(gmu->queues) *
		माप(काष्ठा a6xx_hfi_queue_header));

	table->version = 0;
	table->size = table_size;
	/* First queue header is located immediately after the table header */
	table->qhdr0_offset = माप(*table) >> 2;
	table->qhdr_size = माप(काष्ठा a6xx_hfi_queue_header) >> 2;
	table->num_queues = ARRAY_SIZE(gmu->queues);
	table->active_queues = ARRAY_SIZE(gmu->queues);

	/* Command queue */
	offset = SZ_4K;
	a6xx_hfi_queue_init(&gmu->queues[0], &headers[0], hfi->virt + offset,
		hfi->iova + offset, 0);

	/* GMU response queue */
	offset += SZ_4K;
	a6xx_hfi_queue_init(&gmu->queues[1], &headers[1], hfi->virt + offset,
		hfi->iova + offset, gmu->legacy ? 4 : 1);
पूर्ण
