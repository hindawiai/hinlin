<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux

   Copyright (C) 2015  Intel Corporation

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/hci_mon.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "mgmt_util.h"

अटल काष्ठा sk_buff *create_monitor_ctrl_event(__le16 index, u32 cookie,
						 u16 opcode, u16 len, व्योम *buf)
अणु
	काष्ठा hci_mon_hdr *hdr;
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(6 + len, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	put_unaligned_le32(cookie, skb_put(skb, 4));
	put_unaligned_le16(opcode, skb_put(skb, 2));

	अगर (buf)
		skb_put_data(skb, buf, len);

	__net_बारtamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = cpu_to_le16(HCI_MON_CTRL_EVENT);
	hdr->index = index;
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	वापस skb;
पूर्ण

पूर्णांक mgmt_send_event(u16 event, काष्ठा hci_dev *hdev, अचिन्हित लघु channel,
		    व्योम *data, u16 data_len, पूर्णांक flag, काष्ठा sock *skip_sk)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mgmt_hdr *hdr;

	skb = alloc_skb(माप(*hdr) + data_len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(*hdr));
	hdr->opcode = cpu_to_le16(event);
	अगर (hdev)
		hdr->index = cpu_to_le16(hdev->id);
	अन्यथा
		hdr->index = cpu_to_le16(MGMT_INDEX_NONE);
	hdr->len = cpu_to_le16(data_len);

	अगर (data)
		skb_put_data(skb, data, data_len);

	/* Time stamp */
	__net_बारtamp(skb);

	hci_send_to_channel(channel, skb, flag, skip_sk);

	अगर (channel == HCI_CHANNEL_CONTROL)
		hci_send_monitor_ctrl_event(hdev, event, data, data_len,
					    skb_get_kसमय(skb), flag, skip_sk);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

पूर्णांक mgmt_cmd_status(काष्ठा sock *sk, u16 index, u16 cmd, u8 status)
अणु
	काष्ठा sk_buff *skb, *mskb;
	काष्ठा mgmt_hdr *hdr;
	काष्ठा mgmt_ev_cmd_status *ev;
	पूर्णांक err;

	BT_DBG("sock %p, index %u, cmd %u, status %u", sk, index, cmd, status);

	skb = alloc_skb(माप(*hdr) + माप(*ev), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(*hdr));

	hdr->opcode = cpu_to_le16(MGMT_EV_CMD_STATUS);
	hdr->index = cpu_to_le16(index);
	hdr->len = cpu_to_le16(माप(*ev));

	ev = skb_put(skb, माप(*ev));
	ev->status = status;
	ev->opcode = cpu_to_le16(cmd);

	mskb = create_monitor_ctrl_event(hdr->index, hci_sock_get_cookie(sk),
					 MGMT_EV_CMD_STATUS, माप(*ev), ev);
	अगर (mskb)
		skb->tstamp = mskb->tstamp;
	अन्यथा
		__net_बारtamp(skb);

	err = sock_queue_rcv_skb(sk, skb);
	अगर (err < 0)
		kमुक्त_skb(skb);

	अगर (mskb) अणु
		hci_send_to_channel(HCI_CHANNEL_MONITOR, mskb,
				    HCI_SOCK_TRUSTED, शून्य);
		kमुक्त_skb(mskb);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mgmt_cmd_complete(काष्ठा sock *sk, u16 index, u16 cmd, u8 status,
		      व्योम *rp, माप_प्रकार rp_len)
अणु
	काष्ठा sk_buff *skb, *mskb;
	काष्ठा mgmt_hdr *hdr;
	काष्ठा mgmt_ev_cmd_complete *ev;
	पूर्णांक err;

	BT_DBG("sock %p", sk);

	skb = alloc_skb(माप(*hdr) + माप(*ev) + rp_len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(*hdr));

	hdr->opcode = cpu_to_le16(MGMT_EV_CMD_COMPLETE);
	hdr->index = cpu_to_le16(index);
	hdr->len = cpu_to_le16(माप(*ev) + rp_len);

	ev = skb_put(skb, माप(*ev) + rp_len);
	ev->opcode = cpu_to_le16(cmd);
	ev->status = status;

	अगर (rp)
		स_नकल(ev->data, rp, rp_len);

	mskb = create_monitor_ctrl_event(hdr->index, hci_sock_get_cookie(sk),
					 MGMT_EV_CMD_COMPLETE,
					 माप(*ev) + rp_len, ev);
	अगर (mskb)
		skb->tstamp = mskb->tstamp;
	अन्यथा
		__net_बारtamp(skb);

	err = sock_queue_rcv_skb(sk, skb);
	अगर (err < 0)
		kमुक्त_skb(skb);

	अगर (mskb) अणु
		hci_send_to_channel(HCI_CHANNEL_MONITOR, mskb,
				    HCI_SOCK_TRUSTED, शून्य);
		kमुक्त_skb(mskb);
	पूर्ण

	वापस err;
पूर्ण

काष्ठा mgmt_pending_cmd *mgmt_pending_find(अचिन्हित लघु channel, u16 opcode,
					   काष्ठा hci_dev *hdev)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	list_क्रम_each_entry(cmd, &hdev->mgmt_pending, list) अणु
		अगर (hci_sock_get_channel(cmd->sk) != channel)
			जारी;
		अगर (cmd->opcode == opcode)
			वापस cmd;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा mgmt_pending_cmd *mgmt_pending_find_data(अचिन्हित लघु channel,
						u16 opcode,
						काष्ठा hci_dev *hdev,
						स्थिर व्योम *data)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	list_क्रम_each_entry(cmd, &hdev->mgmt_pending, list) अणु
		अगर (cmd->user_data != data)
			जारी;
		अगर (cmd->opcode == opcode)
			वापस cmd;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम mgmt_pending_क्रमeach(u16 opcode, काष्ठा hci_dev *hdev,
			  व्योम (*cb)(काष्ठा mgmt_pending_cmd *cmd, व्योम *data),
			  व्योम *data)
अणु
	काष्ठा mgmt_pending_cmd *cmd, *पंचांगp;

	list_क्रम_each_entry_safe(cmd, पंचांगp, &hdev->mgmt_pending, list) अणु
		अगर (opcode > 0 && cmd->opcode != opcode)
			जारी;

		cb(cmd, data);
	पूर्ण
पूर्ण

काष्ठा mgmt_pending_cmd *mgmt_pending_add(काष्ठा sock *sk, u16 opcode,
					  काष्ठा hci_dev *hdev,
					  व्योम *data, u16 len)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस शून्य;

	cmd->opcode = opcode;
	cmd->index = hdev->id;

	cmd->param = kmemdup(data, len, GFP_KERNEL);
	अगर (!cmd->param) अणु
		kमुक्त(cmd);
		वापस शून्य;
	पूर्ण

	cmd->param_len = len;

	cmd->sk = sk;
	sock_hold(sk);

	list_add(&cmd->list, &hdev->mgmt_pending);

	वापस cmd;
पूर्ण

व्योम mgmt_pending_मुक्त(काष्ठा mgmt_pending_cmd *cmd)
अणु
	sock_put(cmd->sk);
	kमुक्त(cmd->param);
	kमुक्त(cmd);
पूर्ण

व्योम mgmt_pending_हटाओ(काष्ठा mgmt_pending_cmd *cmd)
अणु
	list_del(&cmd->list);
	mgmt_pending_मुक्त(cmd);
पूर्ण
