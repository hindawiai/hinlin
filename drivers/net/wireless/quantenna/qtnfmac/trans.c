<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "commands.h"
#समावेश "event.h"
#समावेश "bus.h"

#घोषणा QTNF_DEF_SYNC_CMD_TIMEOUT	(5 * HZ)

पूर्णांक qtnf_trans_send_cmd_with_resp(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *cmd_skb,
				  काष्ठा sk_buff **response_skb)
अणु
	काष्ठा qtnf_cmd_ctl_node *ctl_node = &bus->trans.curr_cmd;
	काष्ठा qlink_cmd *cmd = (व्योम *)cmd_skb->data;
	पूर्णांक ret = 0;
	दीर्घ status;
	bool resp_not_handled = true;
	काष्ठा sk_buff *resp_skb = शून्य;

	अगर (unlikely(!response_skb)) अणु
		dev_kमुक्त_skb(cmd_skb);
		वापस -EFAULT;
	पूर्ण

	spin_lock(&ctl_node->resp_lock);
	ctl_node->seq_num++;
	cmd->seq_num = cpu_to_le16(ctl_node->seq_num);
	WARN(ctl_node->resp_skb, "qtnfmac: response skb not empty\n");
	ctl_node->रुकोing_क्रम_resp = true;
	spin_unlock(&ctl_node->resp_lock);

	ret = qtnf_bus_control_tx(bus, cmd_skb);
	dev_kमुक्त_skb(cmd_skb);

	अगर (unlikely(ret))
		जाओ out;

	status = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
						&ctl_node->cmd_resp_completion,
						QTNF_DEF_SYNC_CMD_TIMEOUT);

	spin_lock(&ctl_node->resp_lock);
	resp_not_handled = ctl_node->रुकोing_क्रम_resp;
	resp_skb = ctl_node->resp_skb;
	ctl_node->resp_skb = शून्य;
	ctl_node->रुकोing_क्रम_resp = false;
	spin_unlock(&ctl_node->resp_lock);

	अगर (unlikely(status <= 0)) अणु
		अगर (status == 0) अणु
			ret = -ETIMEDOUT;
			pr_err("response timeout\n");
		पूर्ण अन्यथा अणु
			ret = -EINTR;
			pr_debug("interrupted\n");
		पूर्ण
	पूर्ण

	अगर (unlikely(!resp_skb || resp_not_handled)) अणु
		अगर (!ret)
			ret = -EFAULT;

		जाओ out;
	पूर्ण

	ret = 0;
	*response_skb = resp_skb;

out:
	अगर (unlikely(resp_skb && resp_not_handled))
		dev_kमुक्त_skb(resp_skb);

	वापस ret;
पूर्ण

अटल व्योम qtnf_trans_संकेत_cmdresp(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb)
अणु
	काष्ठा qtnf_cmd_ctl_node *ctl_node = &bus->trans.curr_cmd;
	स्थिर काष्ठा qlink_resp *resp = (स्थिर काष्ठा qlink_resp *)skb->data;
	स्थिर u16 recvd_seq_num = le16_to_cpu(resp->seq_num);

	spin_lock(&ctl_node->resp_lock);

	अगर (unlikely(!ctl_node->रुकोing_क्रम_resp)) अणु
		pr_err("unexpected response\n");
		जाओ out_err;
	पूर्ण

	अगर (unlikely(recvd_seq_num != ctl_node->seq_num)) अणु
		pr_err("seq num mismatch\n");
		जाओ out_err;
	पूर्ण

	ctl_node->resp_skb = skb;
	ctl_node->रुकोing_क्रम_resp = false;

	spin_unlock(&ctl_node->resp_lock);

	complete(&ctl_node->cmd_resp_completion);
	वापस;

out_err:
	spin_unlock(&ctl_node->resp_lock);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक qtnf_trans_event_enqueue(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb)
अणु
	काष्ठा qtnf_qlink_transport *trans = &bus->trans;

	अगर (likely(skb_queue_len(&trans->event_queue) <
		   trans->event_queue_max_len)) अणु
		skb_queue_tail(&trans->event_queue, skb);
		queue_work(bus->workqueue, &bus->event_work);
	पूर्ण अन्यथा अणु
		pr_warn("event dropped due to queue overflow\n");
		dev_kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम qtnf_trans_init(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_qlink_transport *trans = &bus->trans;

	init_completion(&trans->curr_cmd.cmd_resp_completion);
	spin_lock_init(&trans->curr_cmd.resp_lock);

	spin_lock(&trans->curr_cmd.resp_lock);
	trans->curr_cmd.seq_num = 0;
	trans->curr_cmd.रुकोing_क्रम_resp = false;
	trans->curr_cmd.resp_skb = शून्य;
	spin_unlock(&trans->curr_cmd.resp_lock);

	/* Init event handling related fields */
	skb_queue_head_init(&trans->event_queue);
	trans->event_queue_max_len = QTNF_MAX_EVENT_QUEUE_LEN;
पूर्ण

अटल व्योम qtnf_trans_मुक्त_events(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा sk_buff_head *event_queue = &bus->trans.event_queue;
	काष्ठा sk_buff *current_event_skb = skb_dequeue(event_queue);

	जबतक (current_event_skb) अणु
		dev_kमुक्त_skb_any(current_event_skb);
		current_event_skb = skb_dequeue(event_queue);
	पूर्ण
पूर्ण

व्योम qtnf_trans_मुक्त(काष्ठा qtnf_bus *bus)
अणु
	अगर (!bus) अणु
		pr_err("invalid bus pointer\n");
		वापस;
	पूर्ण

	qtnf_trans_मुक्त_events(bus);
पूर्ण

पूर्णांक qtnf_trans_handle_rx_ctl_packet(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा qlink_msg_header *header = (व्योम *)skb->data;
	पूर्णांक ret = -1;

	अगर (unlikely(skb->len < माप(*header))) अणु
		pr_warn("packet is too small: %u\n", skb->len);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(skb->len != le16_to_cpu(header->len))) अणु
		pr_warn("cmd reply length mismatch: %u != %u\n",
			skb->len, le16_to_cpu(header->len));
		dev_kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण

	चयन (le16_to_cpu(header->type)) अणु
	हाल QLINK_MSG_TYPE_CMDRSP:
		अगर (unlikely(skb->len < माप(काष्ठा qlink_cmd))) अणु
			pr_warn("cmd reply too short: %u\n", skb->len);
			dev_kमुक्त_skb(skb);
			अवरोध;
		पूर्ण

		qtnf_trans_संकेत_cmdresp(bus, skb);
		अवरोध;
	हाल QLINK_MSG_TYPE_EVENT:
		अगर (unlikely(skb->len < माप(काष्ठा qlink_event))) अणु
			pr_warn("event too short: %u\n", skb->len);
			dev_kमुक्त_skb(skb);
			अवरोध;
		पूर्ण

		ret = qtnf_trans_event_enqueue(bus, skb);
		अवरोध;
	शेष:
		pr_warn("unknown packet type: %x\n", le16_to_cpu(header->type));
		dev_kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(qtnf_trans_handle_rx_ctl_packet);
