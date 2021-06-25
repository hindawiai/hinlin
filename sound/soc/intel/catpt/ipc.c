<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश <linux/irqवापस.h>
#समावेश "core.h"
#समावेश "messages.h"
#समावेश "registers.h"
#समावेश "trace.h"

#घोषणा CATPT_IPC_TIMEOUT_MS	300

व्योम catpt_ipc_init(काष्ठा catpt_ipc *ipc, काष्ठा device *dev)
अणु
	ipc->dev = dev;
	ipc->पढ़ोy = false;
	ipc->शेष_समयout = CATPT_IPC_TIMEOUT_MS;
	init_completion(&ipc->करोne_completion);
	init_completion(&ipc->busy_completion);
	spin_lock_init(&ipc->lock);
	mutex_init(&ipc->mutex);
पूर्ण

अटल पूर्णांक catpt_ipc_arm(काष्ठा catpt_ipc *ipc, काष्ठा catpt_fw_पढ़ोy *config)
अणु
	/*
	 * Both tx and rx are put पूर्णांकo and received from outbox. Inbox is
	 * only used क्रम notअगरications where payload size is known upfront,
	 * thus no separate buffer is allocated क्रम it.
	 */
	ipc->rx.data = devm_kzalloc(ipc->dev, config->outbox_size, GFP_KERNEL);
	अगर (!ipc->rx.data)
		वापस -ENOMEM;

	स_नकल(&ipc->config, config, माप(*config));
	ipc->पढ़ोy = true;

	वापस 0;
पूर्ण

अटल व्योम catpt_ipc_msg_init(काष्ठा catpt_ipc *ipc,
			       काष्ठा catpt_ipc_msg *reply)
अणु
	lockdep_निश्चित_held(&ipc->lock);

	ipc->rx.header = 0;
	ipc->rx.size = reply ? reply->size : 0;
	reinit_completion(&ipc->करोne_completion);
	reinit_completion(&ipc->busy_completion);
पूर्ण

अटल व्योम catpt_dsp_send_tx(काष्ठा catpt_dev *cdev,
			      स्थिर काष्ठा catpt_ipc_msg *tx)
अणु
	u32 header = tx->header | CATPT_IPCC_BUSY;

	trace_catpt_ipc_request(header);
	trace_catpt_ipc_payload(tx->data, tx->size);

	स_नकल_toio(catpt_outbox_addr(cdev), tx->data, tx->size);
	catpt_ग_लिखोl_shim(cdev, IPCC, header);
पूर्ण

अटल पूर्णांक catpt_रुको_msg_completion(काष्ठा catpt_dev *cdev, पूर्णांक समयout)
अणु
	काष्ठा catpt_ipc *ipc = &cdev->ipc;
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&ipc->करोne_completion,
					  msecs_to_jअगरfies(समयout));
	अगर (!ret)
		वापस -ETIMEDOUT;
	अगर (ipc->rx.rsp.status != CATPT_REPLY_PENDING)
		वापस 0;

	/* रुको क्रम delayed reply */
	ret = रुको_क्रम_completion_समयout(&ipc->busy_completion,
					  msecs_to_jअगरfies(समयout));
	वापस ret ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक catpt_dsp_करो_send_msg(काष्ठा catpt_dev *cdev,
				 काष्ठा catpt_ipc_msg request,
				 काष्ठा catpt_ipc_msg *reply, पूर्णांक समयout)
अणु
	काष्ठा catpt_ipc *ipc = &cdev->ipc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!ipc->पढ़ोy)
		वापस -EPERM;
	अगर (request.size > ipc->config.outbox_size ||
	    (reply && reply->size > ipc->config.outbox_size))
		वापस -EINVAL;

	spin_lock_irqsave(&ipc->lock, flags);
	catpt_ipc_msg_init(ipc, reply);
	catpt_dsp_send_tx(cdev, &request);
	spin_unlock_irqrestore(&ipc->lock, flags);

	ret = catpt_रुको_msg_completion(cdev, समयout);
	अगर (ret) अणु
		dev_crit(cdev->dev, "communication severed: %d, rebooting dsp..\n",
			 ret);
		ipc->पढ़ोy = false;
		/* TODO: attempt recovery */
		वापस ret;
	पूर्ण

	ret = ipc->rx.rsp.status;
	अगर (reply) अणु
		reply->header = ipc->rx.header;

		अगर (!ret && reply->data)
			स_नकल(reply->data, ipc->rx.data, reply->size);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक catpt_dsp_send_msg_समयout(काष्ठा catpt_dev *cdev,
			       काष्ठा catpt_ipc_msg request,
			       काष्ठा catpt_ipc_msg *reply, पूर्णांक समयout)
अणु
	काष्ठा catpt_ipc *ipc = &cdev->ipc;
	पूर्णांक ret;

	mutex_lock(&ipc->mutex);
	ret = catpt_dsp_करो_send_msg(cdev, request, reply, समयout);
	mutex_unlock(&ipc->mutex);

	वापस ret;
पूर्ण

पूर्णांक catpt_dsp_send_msg(काष्ठा catpt_dev *cdev, काष्ठा catpt_ipc_msg request,
		       काष्ठा catpt_ipc_msg *reply)
अणु
	वापस catpt_dsp_send_msg_समयout(cdev, request, reply,
					  cdev->ipc.शेष_समयout);
पूर्ण

अटल व्योम
catpt_dsp_notअगरy_stream(काष्ठा catpt_dev *cdev, जोड़ catpt_notअगरy_msg msg)
अणु
	काष्ठा catpt_stream_runसमय *stream;
	काष्ठा catpt_notअगरy_position pos;
	काष्ठा catpt_notअगरy_glitch glitch;

	stream = catpt_stream_find(cdev, msg.stream_hw_id);
	अगर (!stream) अणु
		dev_warn(cdev->dev, "notify %d for non-existent stream %d\n",
			 msg.notअगरy_reason, msg.stream_hw_id);
		वापस;
	पूर्ण

	चयन (msg.notअगरy_reason) अणु
	हाल CATPT_NOTIFY_POSITION_CHANGED:
		स_नकल_fromio(&pos, catpt_inbox_addr(cdev), माप(pos));
		trace_catpt_ipc_payload((u8 *)&pos, माप(pos));

		catpt_stream_update_position(cdev, stream, &pos);
		अवरोध;

	हाल CATPT_NOTIFY_GLITCH_OCCURRED:
		स_नकल_fromio(&glitch, catpt_inbox_addr(cdev), माप(glitch));
		trace_catpt_ipc_payload((u8 *)&glitch, माप(glitch));

		dev_warn(cdev->dev, "glitch %d at pos: 0x%08llx, wp: 0x%08x\n",
			 glitch.type, glitch.presentation_pos,
			 glitch.ग_लिखो_pos);
		अवरोध;

	शेष:
		dev_warn(cdev->dev, "unknown notification: %d received\n",
			 msg.notअगरy_reason);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम catpt_dsp_copy_rx(काष्ठा catpt_dev *cdev, u32 header)
अणु
	काष्ठा catpt_ipc *ipc = &cdev->ipc;

	ipc->rx.header = header;
	अगर (ipc->rx.rsp.status != CATPT_REPLY_SUCCESS)
		वापस;

	स_नकल_fromio(ipc->rx.data, catpt_outbox_addr(cdev), ipc->rx.size);
	trace_catpt_ipc_payload(ipc->rx.data, ipc->rx.size);
पूर्ण

अटल व्योम catpt_dsp_process_response(काष्ठा catpt_dev *cdev, u32 header)
अणु
	जोड़ catpt_notअगरy_msg msg = CATPT_MSG(header);
	काष्ठा catpt_ipc *ipc = &cdev->ipc;

	अगर (msg.fw_पढ़ोy) अणु
		काष्ठा catpt_fw_पढ़ोy config;
		/* to fit 32b header original address is shअगरted right by 3 */
		u32 off = msg.mailbox_address << 3;

		स_नकल_fromio(&config, cdev->lpe_ba + off, माप(config));
		trace_catpt_ipc_payload((u8 *)&config, माप(config));

		catpt_ipc_arm(ipc, &config);
		complete(&cdev->fw_पढ़ोy);
		वापस;
	पूर्ण

	चयन (msg.global_msg_type) अणु
	हाल CATPT_GLB_REQUEST_CORE_DUMP:
		dev_err(cdev->dev, "ADSP device coredump received\n");
		ipc->पढ़ोy = false;
		catpt_coredump(cdev);
		/* TODO: attempt recovery */
		अवरोध;

	हाल CATPT_GLB_STREAM_MESSAGE:
		चयन (msg.stream_msg_type) अणु
		हाल CATPT_STRM_NOTIFICATION:
			catpt_dsp_notअगरy_stream(cdev, msg);
			अवरोध;
		शेष:
			catpt_dsp_copy_rx(cdev, header);
			/* संकेत completion of delayed reply */
			complete(&ipc->busy_completion);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		dev_warn(cdev->dev, "unknown response: %d received\n",
			 msg.global_msg_type);
		अवरोध;
	पूर्ण
पूर्ण

irqवापस_t catpt_dsp_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा catpt_dev *cdev = dev_id;
	u32 ipcd;

	ipcd = catpt_पढ़ोl_shim(cdev, IPCD);
	trace_catpt_ipc_notअगरy(ipcd);

	/* ensure there is delayed reply or notअगरication to process */
	अगर (!(ipcd & CATPT_IPCD_BUSY))
		वापस IRQ_NONE;

	catpt_dsp_process_response(cdev, ipcd);

	/* tell DSP processing is completed */
	catpt_updatel_shim(cdev, IPCD, CATPT_IPCD_BUSY | CATPT_IPCD_DONE,
			   CATPT_IPCD_DONE);
	/* unmask dsp BUSY पूर्णांकerrupt */
	catpt_updatel_shim(cdev, IMC, CATPT_IMC_IPCDB, 0);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t catpt_dsp_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा catpt_dev *cdev = dev_id;
	irqवापस_t ret = IRQ_NONE;
	u32 isc, ipcc;

	isc = catpt_पढ़ोl_shim(cdev, ISC);
	trace_catpt_irq(isc);

	/* immediate reply */
	अगर (isc & CATPT_ISC_IPCCD) अणु
		/* mask host DONE पूर्णांकerrupt */
		catpt_updatel_shim(cdev, IMC, CATPT_IMC_IPCCD, CATPT_IMC_IPCCD);

		ipcc = catpt_पढ़ोl_shim(cdev, IPCC);
		trace_catpt_ipc_reply(ipcc);
		catpt_dsp_copy_rx(cdev, ipcc);
		complete(&cdev->ipc.करोne_completion);

		/* tell DSP processing is completed */
		catpt_updatel_shim(cdev, IPCC, CATPT_IPCC_DONE, 0);
		/* unmask host DONE पूर्णांकerrupt */
		catpt_updatel_shim(cdev, IMC, CATPT_IMC_IPCCD, 0);
		ret = IRQ_HANDLED;
	पूर्ण

	/* delayed reply or notअगरication */
	अगर (isc & CATPT_ISC_IPCDB) अणु
		/* mask dsp BUSY पूर्णांकerrupt */
		catpt_updatel_shim(cdev, IMC, CATPT_IMC_IPCDB, CATPT_IMC_IPCDB);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण
