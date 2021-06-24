<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//	    Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//	    Rander Wang <अक्रमer.wang@पूर्णांकel.com>
//          Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम generic Intel audio DSP HDA IP
 */

#समावेश "../ops.h"
#समावेश "hda.h"

अटल व्योम hda_dsp_ipc_host_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/*
	 * tell DSP cmd is करोne - clear busy
	 * पूर्णांकerrupt and send reply msg to dsp
	 */
	snd_sof_dsp_update_bits_क्रमced(sdev, HDA_DSP_BAR,
				       HDA_DSP_REG_HIPCT,
				       HDA_DSP_REG_HIPCT_BUSY,
				       HDA_DSP_REG_HIPCT_BUSY);

	/* unmask BUSY पूर्णांकerrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
				HDA_DSP_REG_HIPCCTL,
				HDA_DSP_REG_HIPCCTL_BUSY,
				HDA_DSP_REG_HIPCCTL_BUSY);
पूर्ण

अटल व्योम hda_dsp_ipc_dsp_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/*
	 * set DONE bit - tell DSP we have received the reply msg
	 * from DSP, and processed it, करोn't send more reply to host
	 */
	snd_sof_dsp_update_bits_क्रमced(sdev, HDA_DSP_BAR,
				       HDA_DSP_REG_HIPCIE,
				       HDA_DSP_REG_HIPCIE_DONE,
				       HDA_DSP_REG_HIPCIE_DONE);

	/* unmask Done पूर्णांकerrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
				HDA_DSP_REG_HIPCCTL,
				HDA_DSP_REG_HIPCCTL_DONE,
				HDA_DSP_REG_HIPCCTL_DONE);
पूर्ण

पूर्णांक hda_dsp_ipc_send_msg(काष्ठा snd_sof_dev *sdev, काष्ठा snd_sof_ipc_msg *msg)
अणु
	/* send IPC message to DSP */
	sof_mailbox_ग_लिखो(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCI,
			  HDA_DSP_REG_HIPCI_BUSY);

	वापस 0;
पूर्ण

व्योम hda_dsp_ipc_get_reply(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_ipc_msg *msg = sdev->msg;
	काष्ठा sof_ipc_reply reply;
	काष्ठा sof_ipc_cmd_hdr *hdr;
	पूर्णांक ret = 0;

	/*
	 * Someबार, there is unexpected reply ipc arriving. The reply
	 * ipc beदीर्घs to none of the ipcs sent from driver.
	 * In this हाल, the driver must ignore the ipc.
	 */
	अगर (!msg) अणु
		dev_warn(sdev->dev, "unexpected ipc interrupt raised!\n");
		वापस;
	पूर्ण

	hdr = msg->msg_data;
	अगर (hdr->cmd == (SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_CTX_SAVE) ||
	    hdr->cmd == (SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_GATE)) अणु
		/*
		 * memory winकरोws are घातered off beक्रमe sending IPC reply,
		 * so we can't पढ़ो the mailbox क्रम CTX_SAVE and PM_GATE
		 * replies.
		 */
		reply.error = 0;
		reply.hdr.cmd = SOF_IPC_GLB_REPLY;
		reply.hdr.size = माप(reply);
		स_नकल(msg->reply_data, &reply, माप(reply));
		जाओ out;
	पूर्ण

	/* get IPC reply from DSP in the mailbox */
	sof_mailbox_पढ़ो(sdev, sdev->host_box.offset, &reply,
			 माप(reply));

	अगर (reply.error < 0) अणु
		स_नकल(msg->reply_data, &reply, माप(reply));
		ret = reply.error;
	पूर्ण अन्यथा अणु
		/* reply correct size ? */
		अगर (reply.hdr.size != msg->reply_size &&
			/* getter payload is never known upfront */
			!(reply.hdr.cmd & SOF_IPC_GLB_PROBE)) अणु
			dev_err(sdev->dev, "error: reply expected %zu got %u bytes\n",
				msg->reply_size, reply.hdr.size);
			ret = -EINVAL;
		पूर्ण

		/* पढ़ो the message */
		अगर (msg->reply_size > 0)
			sof_mailbox_पढ़ो(sdev, sdev->host_box.offset,
					 msg->reply_data, msg->reply_size);
	पूर्ण

out:
	msg->reply_error = ret;

पूर्ण

/* IPC handler thपढ़ो */
irqवापस_t hda_dsp_ipc_irq_thपढ़ो(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	u32 hipci;
	u32 hipcie;
	u32 hipct;
	u32 hipcte;
	u32 msg;
	u32 msg_ext;
	bool ipc_irq = false;

	/* पढ़ो IPC status */
	hipcie = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
				  HDA_DSP_REG_HIPCIE);
	hipct = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCT);
	hipci = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCI);
	hipcte = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCTE);

	/* is this a reply message from the DSP */
	अगर (hipcie & HDA_DSP_REG_HIPCIE_DONE) अणु
		msg = hipci & HDA_DSP_REG_HIPCI_MSG_MASK;
		msg_ext = hipcie & HDA_DSP_REG_HIPCIE_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware response, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* mask Done पूर्णांकerrupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
					HDA_DSP_REG_HIPCCTL,
					HDA_DSP_REG_HIPCCTL_DONE, 0);

		/*
		 * Make sure the पूर्णांकerrupt thपढ़ो cannot be preempted between
		 * waking up the sender and re-enabling the पूर्णांकerrupt. Also
		 * protect against a theoretical race with sof_ipc_tx_message():
		 * अगर the DSP is fast enough to receive an IPC message, reply to
		 * it, and the host पूर्णांकerrupt processing calls this function on
		 * a dअगरferent core from the one, where the sending is taking
		 * place, the message might not yet be marked as expecting a
		 * reply.
		 */
		spin_lock_irq(&sdev->ipc_lock);

		/* handle immediate reply from DSP core */
		hda_dsp_ipc_get_reply(sdev);
		snd_sof_ipc_reply(sdev, msg);

		/* set the करोne bit */
		hda_dsp_ipc_dsp_करोne(sdev);

		spin_unlock_irq(&sdev->ipc_lock);

		ipc_irq = true;
	पूर्ण

	/* is this a new message from DSP */
	अगर (hipct & HDA_DSP_REG_HIPCT_BUSY) अणु
		msg = hipct & HDA_DSP_REG_HIPCT_MSG_MASK;
		msg_ext = hipcte & HDA_DSP_REG_HIPCTE_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware initiated, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* mask BUSY पूर्णांकerrupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
					HDA_DSP_REG_HIPCCTL,
					HDA_DSP_REG_HIPCCTL_BUSY, 0);

		/* handle messages from DSP */
		अगर ((hipct & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) अणु
			/* this is a PANIC message !! */
			snd_sof_dsp_panic(sdev, HDA_DSP_PANIC_OFFSET(msg_ext));
		पूर्ण अन्यथा अणु
			/* normal message - process normally */
			snd_sof_ipc_msgs_rx(sdev);
		पूर्ण

		hda_dsp_ipc_host_करोne(sdev);

		ipc_irq = true;
	पूर्ण

	अगर (!ipc_irq) अणु
		/*
		 * This पूर्णांकerrupt is not shared so no need to वापस IRQ_NONE.
		 */
		dev_dbg_ratelimited(sdev->dev,
				    "nothing to do in IPC IRQ thread\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Check अगर an IPC IRQ occurred */
bool hda_dsp_check_ipc_irq(काष्ठा snd_sof_dev *sdev)
अणु
	bool ret = false;
	u32 irq_status;

	/* store status */
	irq_status = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIS);
	dev_vdbg(sdev->dev, "irq handler: irq_status:0x%x\n", irq_status);

	/* invalid message ? */
	अगर (irq_status == 0xffffffff)
		जाओ out;

	/* IPC message ? */
	अगर (irq_status & HDA_DSP_ADSPIS_IPC)
		ret = true;

out:
	वापस ret;
पूर्ण

पूर्णांक hda_dsp_ipc_get_mailbox_offset(काष्ठा snd_sof_dev *sdev)
अणु
	वापस HDA_DSP_MBOX_UPLINK_OFFSET;
पूर्ण

पूर्णांक hda_dsp_ipc_get_winकरोw_offset(काष्ठा snd_sof_dev *sdev, u32 id)
अणु
	वापस SRAM_WINDOW_OFFSET(id);
पूर्ण

व्योम hda_ipc_msg_data(काष्ठा snd_sof_dev *sdev,
		      काष्ठा snd_pcm_substream *substream,
		      व्योम *p, माप_प्रकार sz)
अणु
	अगर (!substream || !sdev->stream_box.size) अणु
		sof_mailbox_पढ़ो(sdev, sdev->dsp_box.offset, p, sz);
	पूर्ण अन्यथा अणु
		काष्ठा hdac_stream *hstream = substream->runसमय->निजी_data;
		काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;

		hda_stream = container_of(hstream,
					  काष्ठा sof_पूर्णांकel_hda_stream,
					  hda_stream.hstream);

		/* The stream might alपढ़ोy be बंदd */
		अगर (hstream)
			sof_mailbox_पढ़ो(sdev, hda_stream->stream.posn_offset,
					 p, sz);
	पूर्ण
पूर्ण

पूर्णांक hda_ipc_pcm_params(काष्ठा snd_sof_dev *sdev,
		       काष्ठा snd_pcm_substream *substream,
		       स्थिर काष्ठा sof_ipc_pcm_params_reply *reply)
अणु
	काष्ठा hdac_stream *hstream = substream->runसमय->निजी_data;
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;
	/* validate offset */
	माप_प्रकार posn_offset = reply->posn_offset;

	hda_stream = container_of(hstream, काष्ठा sof_पूर्णांकel_hda_stream,
				  hda_stream.hstream);

	/* check क्रम unaligned offset or overflow */
	अगर (posn_offset > sdev->stream_box.size ||
	    posn_offset % माप(काष्ठा sof_ipc_stream_posn) != 0)
		वापस -EINVAL;

	hda_stream->stream.posn_offset = sdev->stream_box.offset + posn_offset;

	dev_dbg(sdev->dev, "pcm: stream dir %d, posn mailbox offset is %zu",
		substream->stream, hda_stream->stream.posn_offset);

	वापस 0;
पूर्ण
