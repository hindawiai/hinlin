<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

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

/* Bluetooth HCI sockets. */
#समावेश <linux/compat.h>
#समावेश <linux/export.h>
#समावेश <linux/utsname.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/hci_mon.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "mgmt_util.h"

अटल LIST_HEAD(mgmt_chan_list);
अटल DEFINE_MUTEX(mgmt_chan_list_lock);

अटल DEFINE_IDA(sock_cookie_ida);

अटल atomic_t monitor_promisc = ATOMIC_INIT(0);

/* ----- HCI socket पूर्णांकerface ----- */

/* Socket info */
#घोषणा hci_pi(sk) ((काष्ठा hci_pinfo *) sk)

काष्ठा hci_pinfo अणु
	काष्ठा bt_sock    bt;
	काष्ठा hci_dev    *hdev;
	काष्ठा hci_filter filter;
	__u8              cmsg_mask;
	अचिन्हित लघु    channel;
	अचिन्हित दीर्घ     flags;
	__u32             cookie;
	अक्षर              comm[TASK_COMM_LEN];
पूर्ण;

व्योम hci_sock_set_flag(काष्ठा sock *sk, पूर्णांक nr)
अणु
	set_bit(nr, &hci_pi(sk)->flags);
पूर्ण

व्योम hci_sock_clear_flag(काष्ठा sock *sk, पूर्णांक nr)
अणु
	clear_bit(nr, &hci_pi(sk)->flags);
पूर्ण

पूर्णांक hci_sock_test_flag(काष्ठा sock *sk, पूर्णांक nr)
अणु
	वापस test_bit(nr, &hci_pi(sk)->flags);
पूर्ण

अचिन्हित लघु hci_sock_get_channel(काष्ठा sock *sk)
अणु
	वापस hci_pi(sk)->channel;
पूर्ण

u32 hci_sock_get_cookie(काष्ठा sock *sk)
अणु
	वापस hci_pi(sk)->cookie;
पूर्ण

अटल bool hci_sock_gen_cookie(काष्ठा sock *sk)
अणु
	पूर्णांक id = hci_pi(sk)->cookie;

	अगर (!id) अणु
		id = ida_simple_get(&sock_cookie_ida, 1, 0, GFP_KERNEL);
		अगर (id < 0)
			id = 0xffffffff;

		hci_pi(sk)->cookie = id;
		get_task_comm(hci_pi(sk)->comm, current);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hci_sock_मुक्त_cookie(काष्ठा sock *sk)
अणु
	पूर्णांक id = hci_pi(sk)->cookie;

	अगर (id) अणु
		hci_pi(sk)->cookie = 0xffffffff;
		ida_simple_हटाओ(&sock_cookie_ida, id);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक hci_test_bit(पूर्णांक nr, स्थिर व्योम *addr)
अणु
	वापस *((स्थिर __u32 *) addr + (nr >> 5)) & ((__u32) 1 << (nr & 31));
पूर्ण

/* Security filter */
#घोषणा HCI_Sभग्न_उच्च_OGF  5

काष्ठा hci_sec_filter अणु
	__u32 type_mask;
	__u32 event_mask[2];
	__u32 ocf_mask[HCI_Sभग्न_उच्च_OGF + 1][4];
पूर्ण;

अटल स्थिर काष्ठा hci_sec_filter hci_sec_filter = अणु
	/* Packet types */
	0x10,
	/* Events */
	अणु 0x1000d9fe, 0x0000b00c पूर्ण,
	/* Commands */
	अणु
		अणु 0x0 पूर्ण,
		/* OGF_LINK_CTL */
		अणु 0xbe000006, 0x00000001, 0x00000000, 0x00 पूर्ण,
		/* OGF_LINK_POLICY */
		अणु 0x00005200, 0x00000000, 0x00000000, 0x00 पूर्ण,
		/* OGF_HOST_CTL */
		अणु 0xaab00200, 0x2b402aaa, 0x05220154, 0x00 पूर्ण,
		/* OGF_INFO_PARAM */
		अणु 0x000002be, 0x00000000, 0x00000000, 0x00 पूर्ण,
		/* OGF_STATUS_PARAM */
		अणु 0x000000ea, 0x00000000, 0x00000000, 0x00 पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा bt_sock_list hci_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(hci_sk_list.lock)
पूर्ण;

अटल bool is_filtered_packet(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_filter *flt;
	पूर्णांक flt_type, flt_event;

	/* Apply filter */
	flt = &hci_pi(sk)->filter;

	flt_type = hci_skb_pkt_type(skb) & HCI_FLT_TYPE_BITS;

	अगर (!test_bit(flt_type, &flt->type_mask))
		वापस true;

	/* Extra filter क्रम event packets only */
	अगर (hci_skb_pkt_type(skb) != HCI_EVENT_PKT)
		वापस false;

	flt_event = (*(__u8 *)skb->data & HCI_FLT_EVENT_BITS);

	अगर (!hci_test_bit(flt_event, &flt->event_mask))
		वापस true;

	/* Check filter only when opcode is set */
	अगर (!flt->opcode)
		वापस false;

	अगर (flt_event == HCI_EV_CMD_COMPLETE &&
	    flt->opcode != get_unaligned((__le16 *)(skb->data + 3)))
		वापस true;

	अगर (flt_event == HCI_EV_CMD_STATUS &&
	    flt->opcode != get_unaligned((__le16 *)(skb->data + 4)))
		वापस true;

	वापस false;
पूर्ण

/* Send frame to RAW socket */
व्योम hci_send_to_sock(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk;
	काष्ठा sk_buff *skb_copy = शून्य;

	BT_DBG("hdev %p len %d", hdev, skb->len);

	पढ़ो_lock(&hci_sk_list.lock);

	sk_क्रम_each(sk, &hci_sk_list.head) अणु
		काष्ठा sk_buff *nskb;

		अगर (sk->sk_state != BT_BOUND || hci_pi(sk)->hdev != hdev)
			जारी;

		/* Don't send frame to the socket it came from */
		अगर (skb->sk == sk)
			जारी;

		अगर (hci_pi(sk)->channel == HCI_CHANNEL_RAW) अणु
			अगर (hci_skb_pkt_type(skb) != HCI_COMMAND_PKT &&
			    hci_skb_pkt_type(skb) != HCI_EVENT_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ACLDATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT)
				जारी;
			अगर (is_filtered_packet(sk, skb))
				जारी;
		पूर्ण अन्यथा अगर (hci_pi(sk)->channel == HCI_CHANNEL_USER) अणु
			अगर (!bt_cb(skb)->incoming)
				जारी;
			अगर (hci_skb_pkt_type(skb) != HCI_EVENT_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ACLDATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT)
				जारी;
		पूर्ण अन्यथा अणु
			/* Don't send frame to other channel types */
			जारी;
		पूर्ण

		अगर (!skb_copy) अणु
			/* Create a निजी copy with headroom */
			skb_copy = __pskb_copy_fclone(skb, 1, GFP_ATOMIC, true);
			अगर (!skb_copy)
				जारी;

			/* Put type byte beक्रमe the data */
			स_नकल(skb_push(skb_copy, 1), &hci_skb_pkt_type(skb), 1);
		पूर्ण

		nskb = skb_clone(skb_copy, GFP_ATOMIC);
		अगर (!nskb)
			जारी;

		अगर (sock_queue_rcv_skb(sk, nskb))
			kमुक्त_skb(nskb);
	पूर्ण

	पढ़ो_unlock(&hci_sk_list.lock);

	kमुक्त_skb(skb_copy);
पूर्ण

/* Send frame to sockets with specअगरic channel */
अटल व्योम __hci_send_to_channel(अचिन्हित लघु channel, काष्ठा sk_buff *skb,
				  पूर्णांक flag, काष्ठा sock *skip_sk)
अणु
	काष्ठा sock *sk;

	BT_DBG("channel %u len %d", channel, skb->len);

	sk_क्रम_each(sk, &hci_sk_list.head) अणु
		काष्ठा sk_buff *nskb;

		/* Ignore socket without the flag set */
		अगर (!hci_sock_test_flag(sk, flag))
			जारी;

		/* Skip the original socket */
		अगर (sk == skip_sk)
			जारी;

		अगर (sk->sk_state != BT_BOUND)
			जारी;

		अगर (hci_pi(sk)->channel != channel)
			जारी;

		nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (!nskb)
			जारी;

		अगर (sock_queue_rcv_skb(sk, nskb))
			kमुक्त_skb(nskb);
	पूर्ण

पूर्ण

व्योम hci_send_to_channel(अचिन्हित लघु channel, काष्ठा sk_buff *skb,
			 पूर्णांक flag, काष्ठा sock *skip_sk)
अणु
	पढ़ो_lock(&hci_sk_list.lock);
	__hci_send_to_channel(channel, skb, flag, skip_sk);
	पढ़ो_unlock(&hci_sk_list.lock);
पूर्ण

/* Send frame to monitor socket */
व्योम hci_send_to_monitor(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skb_copy = शून्य;
	काष्ठा hci_mon_hdr *hdr;
	__le16 opcode;

	अगर (!atomic_पढ़ो(&monitor_promisc))
		वापस;

	BT_DBG("hdev %p len %d", hdev, skb->len);

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		opcode = cpu_to_le16(HCI_MON_COMMAND_PKT);
		अवरोध;
	हाल HCI_EVENT_PKT:
		opcode = cpu_to_le16(HCI_MON_EVENT_PKT);
		अवरोध;
	हाल HCI_ACLDATA_PKT:
		अगर (bt_cb(skb)->incoming)
			opcode = cpu_to_le16(HCI_MON_ACL_RX_PKT);
		अन्यथा
			opcode = cpu_to_le16(HCI_MON_ACL_TX_PKT);
		अवरोध;
	हाल HCI_SCODATA_PKT:
		अगर (bt_cb(skb)->incoming)
			opcode = cpu_to_le16(HCI_MON_SCO_RX_PKT);
		अन्यथा
			opcode = cpu_to_le16(HCI_MON_SCO_TX_PKT);
		अवरोध;
	हाल HCI_ISODATA_PKT:
		अगर (bt_cb(skb)->incoming)
			opcode = cpu_to_le16(HCI_MON_ISO_RX_PKT);
		अन्यथा
			opcode = cpu_to_le16(HCI_MON_ISO_TX_PKT);
		अवरोध;
	हाल HCI_DIAG_PKT:
		opcode = cpu_to_le16(HCI_MON_VENDOR_DIAG);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* Create a निजी copy with headroom */
	skb_copy = __pskb_copy_fclone(skb, HCI_MON_HDR_SIZE, GFP_ATOMIC, true);
	अगर (!skb_copy)
		वापस;

	/* Put header beक्रमe the data */
	hdr = skb_push(skb_copy, HCI_MON_HDR_SIZE);
	hdr->opcode = opcode;
	hdr->index = cpu_to_le16(hdev->id);
	hdr->len = cpu_to_le16(skb->len);

	hci_send_to_channel(HCI_CHANNEL_MONITOR, skb_copy,
			    HCI_SOCK_TRUSTED, शून्य);
	kमुक्त_skb(skb_copy);
पूर्ण

व्योम hci_send_monitor_ctrl_event(काष्ठा hci_dev *hdev, u16 event,
				 व्योम *data, u16 data_len, kसमय_प्रकार tstamp,
				 पूर्णांक flag, काष्ठा sock *skip_sk)
अणु
	काष्ठा sock *sk;
	__le16 index;

	अगर (hdev)
		index = cpu_to_le16(hdev->id);
	अन्यथा
		index = cpu_to_le16(MGMT_INDEX_NONE);

	पढ़ो_lock(&hci_sk_list.lock);

	sk_क्रम_each(sk, &hci_sk_list.head) अणु
		काष्ठा hci_mon_hdr *hdr;
		काष्ठा sk_buff *skb;

		अगर (hci_pi(sk)->channel != HCI_CHANNEL_CONTROL)
			जारी;

		/* Ignore socket without the flag set */
		अगर (!hci_sock_test_flag(sk, flag))
			जारी;

		/* Skip the original socket */
		अगर (sk == skip_sk)
			जारी;

		skb = bt_skb_alloc(6 + data_len, GFP_ATOMIC);
		अगर (!skb)
			जारी;

		put_unaligned_le32(hci_pi(sk)->cookie, skb_put(skb, 4));
		put_unaligned_le16(event, skb_put(skb, 2));

		अगर (data)
			skb_put_data(skb, data, data_len);

		skb->tstamp = tstamp;

		hdr = skb_push(skb, HCI_MON_HDR_SIZE);
		hdr->opcode = cpu_to_le16(HCI_MON_CTRL_EVENT);
		hdr->index = index;
		hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

		__hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
				      HCI_SOCK_TRUSTED, शून्य);
		kमुक्त_skb(skb);
	पूर्ण

	पढ़ो_unlock(&hci_sk_list.lock);
पूर्ण

अटल काष्ठा sk_buff *create_monitor_event(काष्ठा hci_dev *hdev, पूर्णांक event)
अणु
	काष्ठा hci_mon_hdr *hdr;
	काष्ठा hci_mon_new_index *ni;
	काष्ठा hci_mon_index_info *ii;
	काष्ठा sk_buff *skb;
	__le16 opcode;

	चयन (event) अणु
	हाल HCI_DEV_REG:
		skb = bt_skb_alloc(HCI_MON_NEW_INDEX_SIZE, GFP_ATOMIC);
		अगर (!skb)
			वापस शून्य;

		ni = skb_put(skb, HCI_MON_NEW_INDEX_SIZE);
		ni->type = hdev->dev_type;
		ni->bus = hdev->bus;
		bacpy(&ni->bdaddr, &hdev->bdaddr);
		स_नकल(ni->name, hdev->name, 8);

		opcode = cpu_to_le16(HCI_MON_NEW_INDEX);
		अवरोध;

	हाल HCI_DEV_UNREG:
		skb = bt_skb_alloc(0, GFP_ATOMIC);
		अगर (!skb)
			वापस शून्य;

		opcode = cpu_to_le16(HCI_MON_DEL_INDEX);
		अवरोध;

	हाल HCI_DEV_SETUP:
		अगर (hdev->manufacturer == 0xffff)
			वापस शून्य;
		fallthrough;

	हाल HCI_DEV_UP:
		skb = bt_skb_alloc(HCI_MON_INDEX_INFO_SIZE, GFP_ATOMIC);
		अगर (!skb)
			वापस शून्य;

		ii = skb_put(skb, HCI_MON_INDEX_INFO_SIZE);
		bacpy(&ii->bdaddr, &hdev->bdaddr);
		ii->manufacturer = cpu_to_le16(hdev->manufacturer);

		opcode = cpu_to_le16(HCI_MON_INDEX_INFO);
		अवरोध;

	हाल HCI_DEV_OPEN:
		skb = bt_skb_alloc(0, GFP_ATOMIC);
		अगर (!skb)
			वापस शून्य;

		opcode = cpu_to_le16(HCI_MON_OPEN_INDEX);
		अवरोध;

	हाल HCI_DEV_CLOSE:
		skb = bt_skb_alloc(0, GFP_ATOMIC);
		अगर (!skb)
			वापस शून्य;

		opcode = cpu_to_le16(HCI_MON_CLOSE_INDEX);
		अवरोध;

	शेष:
		वापस शून्य;
	पूर्ण

	__net_बारtamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = opcode;
	hdr->index = cpu_to_le16(hdev->id);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *create_monitor_ctrl_खोलो(काष्ठा sock *sk)
अणु
	काष्ठा hci_mon_hdr *hdr;
	काष्ठा sk_buff *skb;
	u16 क्रमmat;
	u8 ver[3];
	u32 flags;

	/* No message needed when cookie is not present */
	अगर (!hci_pi(sk)->cookie)
		वापस शून्य;

	चयन (hci_pi(sk)->channel) अणु
	हाल HCI_CHANNEL_RAW:
		क्रमmat = 0x0000;
		ver[0] = BT_SUBSYS_VERSION;
		put_unaligned_le16(BT_SUBSYS_REVISION, ver + 1);
		अवरोध;
	हाल HCI_CHANNEL_USER:
		क्रमmat = 0x0001;
		ver[0] = BT_SUBSYS_VERSION;
		put_unaligned_le16(BT_SUBSYS_REVISION, ver + 1);
		अवरोध;
	हाल HCI_CHANNEL_CONTROL:
		क्रमmat = 0x0002;
		mgmt_fill_version_info(ver);
		अवरोध;
	शेष:
		/* No message क्रम unsupported क्रमmat */
		वापस शून्य;
	पूर्ण

	skb = bt_skb_alloc(14 + TASK_COMM_LEN , GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	flags = hci_sock_test_flag(sk, HCI_SOCK_TRUSTED) ? 0x1 : 0x0;

	put_unaligned_le32(hci_pi(sk)->cookie, skb_put(skb, 4));
	put_unaligned_le16(क्रमmat, skb_put(skb, 2));
	skb_put_data(skb, ver, माप(ver));
	put_unaligned_le32(flags, skb_put(skb, 4));
	skb_put_u8(skb, TASK_COMM_LEN);
	skb_put_data(skb, hci_pi(sk)->comm, TASK_COMM_LEN);

	__net_बारtamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = cpu_to_le16(HCI_MON_CTRL_OPEN);
	अगर (hci_pi(sk)->hdev)
		hdr->index = cpu_to_le16(hci_pi(sk)->hdev->id);
	अन्यथा
		hdr->index = cpu_to_le16(HCI_DEV_NONE);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *create_monitor_ctrl_बंद(काष्ठा sock *sk)
अणु
	काष्ठा hci_mon_hdr *hdr;
	काष्ठा sk_buff *skb;

	/* No message needed when cookie is not present */
	अगर (!hci_pi(sk)->cookie)
		वापस शून्य;

	चयन (hci_pi(sk)->channel) अणु
	हाल HCI_CHANNEL_RAW:
	हाल HCI_CHANNEL_USER:
	हाल HCI_CHANNEL_CONTROL:
		अवरोध;
	शेष:
		/* No message क्रम unsupported क्रमmat */
		वापस शून्य;
	पूर्ण

	skb = bt_skb_alloc(4, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	put_unaligned_le32(hci_pi(sk)->cookie, skb_put(skb, 4));

	__net_बारtamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = cpu_to_le16(HCI_MON_CTRL_CLOSE);
	अगर (hci_pi(sk)->hdev)
		hdr->index = cpu_to_le16(hci_pi(sk)->hdev->id);
	अन्यथा
		hdr->index = cpu_to_le16(HCI_DEV_NONE);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *create_monitor_ctrl_command(काष्ठा sock *sk, u16 index,
						   u16 opcode, u16 len,
						   स्थिर व्योम *buf)
अणु
	काष्ठा hci_mon_hdr *hdr;
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(6 + len, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	put_unaligned_le32(hci_pi(sk)->cookie, skb_put(skb, 4));
	put_unaligned_le16(opcode, skb_put(skb, 2));

	अगर (buf)
		skb_put_data(skb, buf, len);

	__net_बारtamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = cpu_to_le16(HCI_MON_CTRL_COMMAND);
	hdr->index = cpu_to_le16(index);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	वापस skb;
पूर्ण

अटल व्योम __म_लिखो(2, 3)
send_monitor_note(काष्ठा sock *sk, स्थिर अक्षर *fmt, ...)
अणु
	माप_प्रकार len;
	काष्ठा hci_mon_hdr *hdr;
	काष्ठा sk_buff *skb;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	len = vsnम_लिखो(शून्य, 0, fmt, args);
	बहु_पूर्ण(args);

	skb = bt_skb_alloc(len + 1, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	बहु_शुरू(args, fmt);
	भम_लिखो(skb_put(skb, len), fmt, args);
	*(u8 *)skb_put(skb, 1) = 0;
	बहु_पूर्ण(args);

	__net_बारtamp(skb);

	hdr = (व्योम *)skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = cpu_to_le16(HCI_MON_SYSTEM_NOTE);
	hdr->index = cpu_to_le16(HCI_DEV_NONE);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	अगर (sock_queue_rcv_skb(sk, skb))
		kमुक्त_skb(skb);
पूर्ण

अटल व्योम send_monitor_replay(काष्ठा sock *sk)
अणु
	काष्ठा hci_dev *hdev;

	पढ़ो_lock(&hci_dev_list_lock);

	list_क्रम_each_entry(hdev, &hci_dev_list, list) अणु
		काष्ठा sk_buff *skb;

		skb = create_monitor_event(hdev, HCI_DEV_REG);
		अगर (!skb)
			जारी;

		अगर (sock_queue_rcv_skb(sk, skb))
			kमुक्त_skb(skb);

		अगर (!test_bit(HCI_RUNNING, &hdev->flags))
			जारी;

		skb = create_monitor_event(hdev, HCI_DEV_OPEN);
		अगर (!skb)
			जारी;

		अगर (sock_queue_rcv_skb(sk, skb))
			kमुक्त_skb(skb);

		अगर (test_bit(HCI_UP, &hdev->flags))
			skb = create_monitor_event(hdev, HCI_DEV_UP);
		अन्यथा अगर (hci_dev_test_flag(hdev, HCI_SETUP))
			skb = create_monitor_event(hdev, HCI_DEV_SETUP);
		अन्यथा
			skb = शून्य;

		अगर (skb) अणु
			अगर (sock_queue_rcv_skb(sk, skb))
				kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&hci_dev_list_lock);
पूर्ण

अटल व्योम send_monitor_control_replay(काष्ठा sock *mon_sk)
अणु
	काष्ठा sock *sk;

	पढ़ो_lock(&hci_sk_list.lock);

	sk_क्रम_each(sk, &hci_sk_list.head) अणु
		काष्ठा sk_buff *skb;

		skb = create_monitor_ctrl_खोलो(sk);
		अगर (!skb)
			जारी;

		अगर (sock_queue_rcv_skb(mon_sk, skb))
			kमुक्त_skb(skb);
	पूर्ण

	पढ़ो_unlock(&hci_sk_list.lock);
पूर्ण

/* Generate पूर्णांकernal stack event */
अटल व्योम hci_si_event(काष्ठा hci_dev *hdev, पूर्णांक type, पूर्णांक dlen, व्योम *data)
अणु
	काष्ठा hci_event_hdr *hdr;
	काष्ठा hci_ev_stack_पूर्णांकernal *ev;
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(HCI_EVENT_HDR_SIZE + माप(*ev) + dlen, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	hdr = skb_put(skb, HCI_EVENT_HDR_SIZE);
	hdr->evt  = HCI_EV_STACK_INTERNAL;
	hdr->plen = माप(*ev) + dlen;

	ev = skb_put(skb, माप(*ev) + dlen);
	ev->type = type;
	स_नकल(ev->data, data, dlen);

	bt_cb(skb)->incoming = 1;
	__net_बारtamp(skb);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
	hci_send_to_sock(hdev, skb);
	kमुक्त_skb(skb);
पूर्ण

व्योम hci_sock_dev_event(काष्ठा hci_dev *hdev, पूर्णांक event)
अणु
	BT_DBG("hdev %s event %d", hdev->name, event);

	अगर (atomic_पढ़ो(&monitor_promisc)) अणु
		काष्ठा sk_buff *skb;

		/* Send event to monitor */
		skb = create_monitor_event(hdev, event);
		अगर (skb) अणु
			hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
					    HCI_SOCK_TRUSTED, शून्य);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	अगर (event <= HCI_DEV_DOWN) अणु
		काष्ठा hci_ev_si_device ev;

		/* Send event to sockets */
		ev.event  = event;
		ev.dev_id = hdev->id;
		hci_si_event(शून्य, HCI_EV_SI_DEVICE, माप(ev), &ev);
	पूर्ण

	अगर (event == HCI_DEV_UNREG) अणु
		काष्ठा sock *sk;

		/* Detach sockets from device */
		पढ़ो_lock(&hci_sk_list.lock);
		sk_क्रम_each(sk, &hci_sk_list.head) अणु
			lock_sock(sk);
			अगर (hci_pi(sk)->hdev == hdev) अणु
				hci_pi(sk)->hdev = शून्य;
				sk->sk_err = EPIPE;
				sk->sk_state = BT_OPEN;
				sk->sk_state_change(sk);

				hci_dev_put(hdev);
			पूर्ण
			release_sock(sk);
		पूर्ण
		पढ़ो_unlock(&hci_sk_list.lock);
	पूर्ण
पूर्ण

अटल काष्ठा hci_mgmt_chan *__hci_mgmt_chan_find(अचिन्हित लघु channel)
अणु
	काष्ठा hci_mgmt_chan *c;

	list_क्रम_each_entry(c, &mgmt_chan_list, list) अणु
		अगर (c->channel == channel)
			वापस c;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hci_mgmt_chan *hci_mgmt_chan_find(अचिन्हित लघु channel)
अणु
	काष्ठा hci_mgmt_chan *c;

	mutex_lock(&mgmt_chan_list_lock);
	c = __hci_mgmt_chan_find(channel);
	mutex_unlock(&mgmt_chan_list_lock);

	वापस c;
पूर्ण

पूर्णांक hci_mgmt_chan_रेजिस्टर(काष्ठा hci_mgmt_chan *c)
अणु
	अगर (c->channel < HCI_CHANNEL_CONTROL)
		वापस -EINVAL;

	mutex_lock(&mgmt_chan_list_lock);
	अगर (__hci_mgmt_chan_find(c->channel)) अणु
		mutex_unlock(&mgmt_chan_list_lock);
		वापस -EALREADY;
	पूर्ण

	list_add_tail(&c->list, &mgmt_chan_list);

	mutex_unlock(&mgmt_chan_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_mgmt_chan_रेजिस्टर);

व्योम hci_mgmt_chan_unरेजिस्टर(काष्ठा hci_mgmt_chan *c)
अणु
	mutex_lock(&mgmt_chan_list_lock);
	list_del(&c->list);
	mutex_unlock(&mgmt_chan_list_lock);
पूर्ण
EXPORT_SYMBOL(hci_mgmt_chan_unरेजिस्टर);

अटल पूर्णांक hci_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा hci_dev *hdev;
	काष्ठा sk_buff *skb;

	BT_DBG("sock %p sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	lock_sock(sk);

	चयन (hci_pi(sk)->channel) अणु
	हाल HCI_CHANNEL_MONITOR:
		atomic_dec(&monitor_promisc);
		अवरोध;
	हाल HCI_CHANNEL_RAW:
	हाल HCI_CHANNEL_USER:
	हाल HCI_CHANNEL_CONTROL:
		/* Send event to monitor */
		skb = create_monitor_ctrl_बंद(sk);
		अगर (skb) अणु
			hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
					    HCI_SOCK_TRUSTED, शून्य);
			kमुक्त_skb(skb);
		पूर्ण

		hci_sock_मुक्त_cookie(sk);
		अवरोध;
	पूर्ण

	bt_sock_unlink(&hci_sk_list, sk);

	hdev = hci_pi(sk)->hdev;
	अगर (hdev) अणु
		अगर (hci_pi(sk)->channel == HCI_CHANNEL_USER) अणु
			/* When releasing a user channel exclusive access,
			 * call hci_dev_करो_बंद directly instead of calling
			 * hci_dev_बंद to ensure the exclusive access will
			 * be released and the controller brought back करोwn.
			 *
			 * The checking of HCI_AUTO_OFF is not needed in this
			 * हाल since it will have been cleared alपढ़ोy when
			 * खोलोing the user channel.
			 */
			hci_dev_करो_बंद(hdev);
			hci_dev_clear_flag(hdev, HCI_USER_CHANNEL);
			mgmt_index_added(hdev);
		पूर्ण

		atomic_dec(&hdev->promisc);
		hci_dev_put(hdev);
	पूर्ण

	sock_orphan(sk);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_ग_लिखो_queue);

	release_sock(sk);
	sock_put(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक hci_sock_blacklist_add(काष्ठा hci_dev *hdev, व्योम __user *arg)
अणु
	bdaddr_t bdaddr;
	पूर्णांक err;

	अगर (copy_from_user(&bdaddr, arg, माप(bdaddr)))
		वापस -EFAULT;

	hci_dev_lock(hdev);

	err = hci_bdaddr_list_add(&hdev->blacklist, &bdaddr, BDADDR_BREDR);

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक hci_sock_blacklist_del(काष्ठा hci_dev *hdev, व्योम __user *arg)
अणु
	bdaddr_t bdaddr;
	पूर्णांक err;

	अगर (copy_from_user(&bdaddr, arg, माप(bdaddr)))
		वापस -EFAULT;

	hci_dev_lock(hdev);

	err = hci_bdaddr_list_del(&hdev->blacklist, &bdaddr, BDADDR_BREDR);

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

/* Ioctls that require bound socket */
अटल पूर्णांक hci_sock_bound_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा hci_dev *hdev = hci_pi(sk)->hdev;

	अगर (!hdev)
		वापस -EBADFD;

	अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL))
		वापस -EBUSY;

	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED))
		वापस -EOPNOTSUPP;

	अगर (hdev->dev_type != HCI_PRIMARY)
		वापस -EOPNOTSUPP;

	चयन (cmd) अणु
	हाल HCISETRAW:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस -EOPNOTSUPP;

	हाल HCIGETCONNINFO:
		वापस hci_get_conn_info(hdev, (व्योम __user *)arg);

	हाल HCIGETAUTHINFO:
		वापस hci_get_auth_info(hdev, (व्योम __user *)arg);

	हाल HCIBLOCKADDR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस hci_sock_blacklist_add(hdev, (व्योम __user *)arg);

	हाल HCIUNBLOCKADDR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस hci_sock_blacklist_del(hdev, (व्योम __user *)arg);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल पूर्णांक hci_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	BT_DBG("cmd %x arg %lx", cmd, arg);

	lock_sock(sk);

	अगर (hci_pi(sk)->channel != HCI_CHANNEL_RAW) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	/* When calling an ioctl on an unbound raw socket, then ensure
	 * that the monitor माला_लो inक्रमmed. Ensure that the resulting event
	 * is only send once by checking अगर the cookie exists or not. The
	 * socket cookie will be only ever generated once क्रम the lअगरeसमय
	 * of a given socket.
	 */
	अगर (hci_sock_gen_cookie(sk)) अणु
		काष्ठा sk_buff *skb;

		अगर (capable(CAP_NET_ADMIN))
			hci_sock_set_flag(sk, HCI_SOCK_TRUSTED);

		/* Send event to monitor */
		skb = create_monitor_ctrl_खोलो(sk);
		अगर (skb) अणु
			hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
					    HCI_SOCK_TRUSTED, शून्य);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	release_sock(sk);

	चयन (cmd) अणु
	हाल HCIGETDEVLIST:
		वापस hci_get_dev_list(argp);

	हाल HCIGETDEVINFO:
		वापस hci_get_dev_info(argp);

	हाल HCIGETCONNLIST:
		वापस hci_get_conn_list(argp);

	हाल HCIDEVUP:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस hci_dev_खोलो(arg);

	हाल HCIDEVDOWN:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस hci_dev_बंद(arg);

	हाल HCIDEVRESET:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस hci_dev_reset(arg);

	हाल HCIDEVRESTAT:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस hci_dev_reset_stat(arg);

	हाल HCISETSCAN:
	हाल HCISETAUTH:
	हाल HCISETENCRYPT:
	हाल HCISETPTYPE:
	हाल HCISETLINKPOL:
	हाल HCISETLINKMODE:
	हाल HCISETACLMTU:
	हाल HCISETSCOMTU:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस hci_dev_cmd(cmd, argp);

	हाल HCIINQUIRY:
		वापस hci_inquiry(argp);
	पूर्ण

	lock_sock(sk);

	err = hci_sock_bound_ioctl(sk, cmd, arg);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक hci_sock_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल HCIDEVUP:
	हाल HCIDEVDOWN:
	हाल HCIDEVRESET:
	हाल HCIDEVRESTAT:
		वापस hci_sock_ioctl(sock, cmd, arg);
	पूर्ण

	वापस hci_sock_ioctl(sock, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hci_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			 पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_hci haddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा hci_dev *hdev = शून्य;
	काष्ठा sk_buff *skb;
	पूर्णांक len, err = 0;

	BT_DBG("sock %p sk %p", sock, sk);

	अगर (!addr)
		वापस -EINVAL;

	स_रखो(&haddr, 0, माप(haddr));
	len = min_t(अचिन्हित पूर्णांक, माप(haddr), addr_len);
	स_नकल(&haddr, addr, len);

	अगर (haddr.hci_family != AF_BLUETOOTH)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (sk->sk_state == BT_BOUND) अणु
		err = -EALREADY;
		जाओ करोne;
	पूर्ण

	चयन (haddr.hci_channel) अणु
	हाल HCI_CHANNEL_RAW:
		अगर (hci_pi(sk)->hdev) अणु
			err = -EALREADY;
			जाओ करोne;
		पूर्ण

		अगर (haddr.hci_dev != HCI_DEV_NONE) अणु
			hdev = hci_dev_get(haddr.hci_dev);
			अगर (!hdev) अणु
				err = -ENODEV;
				जाओ करोne;
			पूर्ण

			atomic_inc(&hdev->promisc);
		पूर्ण

		hci_pi(sk)->channel = haddr.hci_channel;

		अगर (!hci_sock_gen_cookie(sk)) अणु
			/* In the हाल when a cookie has alपढ़ोy been asचिन्हित,
			 * then there has been alपढ़ोy an ioctl issued against
			 * an unbound socket and with that triggerd an खोलो
			 * notअगरication. Send a बंद notअगरication first to
			 * allow the state transition to bounded.
			 */
			skb = create_monitor_ctrl_बंद(sk);
			अगर (skb) अणु
				hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
						    HCI_SOCK_TRUSTED, शून्य);
				kमुक्त_skb(skb);
			पूर्ण
		पूर्ण

		अगर (capable(CAP_NET_ADMIN))
			hci_sock_set_flag(sk, HCI_SOCK_TRUSTED);

		hci_pi(sk)->hdev = hdev;

		/* Send event to monitor */
		skb = create_monitor_ctrl_खोलो(sk);
		अगर (skb) अणु
			hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
					    HCI_SOCK_TRUSTED, शून्य);
			kमुक्त_skb(skb);
		पूर्ण
		अवरोध;

	हाल HCI_CHANNEL_USER:
		अगर (hci_pi(sk)->hdev) अणु
			err = -EALREADY;
			जाओ करोne;
		पूर्ण

		अगर (haddr.hci_dev == HCI_DEV_NONE) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (!capable(CAP_NET_ADMIN)) अणु
			err = -EPERM;
			जाओ करोne;
		पूर्ण

		hdev = hci_dev_get(haddr.hci_dev);
		अगर (!hdev) अणु
			err = -ENODEV;
			जाओ करोne;
		पूर्ण

		अगर (test_bit(HCI_INIT, &hdev->flags) ||
		    hci_dev_test_flag(hdev, HCI_SETUP) ||
		    hci_dev_test_flag(hdev, HCI_CONFIG) ||
		    (!hci_dev_test_flag(hdev, HCI_AUTO_OFF) &&
		     test_bit(HCI_UP, &hdev->flags))) अणु
			err = -EBUSY;
			hci_dev_put(hdev);
			जाओ करोne;
		पूर्ण

		अगर (hci_dev_test_and_set_flag(hdev, HCI_USER_CHANNEL)) अणु
			err = -EUSERS;
			hci_dev_put(hdev);
			जाओ करोne;
		पूर्ण

		mgmt_index_हटाओd(hdev);

		err = hci_dev_खोलो(hdev->id);
		अगर (err) अणु
			अगर (err == -EALREADY) अणु
				/* In हाल the transport is alपढ़ोy up and
				 * running, clear the error here.
				 *
				 * This can happen when खोलोing a user
				 * channel and HCI_AUTO_OFF grace period
				 * is still active.
				 */
				err = 0;
			पूर्ण अन्यथा अणु
				hci_dev_clear_flag(hdev, HCI_USER_CHANNEL);
				mgmt_index_added(hdev);
				hci_dev_put(hdev);
				जाओ करोne;
			पूर्ण
		पूर्ण

		hci_pi(sk)->channel = haddr.hci_channel;

		अगर (!hci_sock_gen_cookie(sk)) अणु
			/* In the हाल when a cookie has alपढ़ोy been asचिन्हित,
			 * this socket will transition from a raw socket पूर्णांकo
			 * a user channel socket. For a clean transition, send
			 * the बंद notअगरication first.
			 */
			skb = create_monitor_ctrl_बंद(sk);
			अगर (skb) अणु
				hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
						    HCI_SOCK_TRUSTED, शून्य);
				kमुक्त_skb(skb);
			पूर्ण
		पूर्ण

		/* The user channel is restricted to CAP_NET_ADMIN
		 * capabilities and with that implicitly trusted.
		 */
		hci_sock_set_flag(sk, HCI_SOCK_TRUSTED);

		hci_pi(sk)->hdev = hdev;

		/* Send event to monitor */
		skb = create_monitor_ctrl_खोलो(sk);
		अगर (skb) अणु
			hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
					    HCI_SOCK_TRUSTED, शून्य);
			kमुक्त_skb(skb);
		पूर्ण

		atomic_inc(&hdev->promisc);
		अवरोध;

	हाल HCI_CHANNEL_MONITOR:
		अगर (haddr.hci_dev != HCI_DEV_NONE) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (!capable(CAP_NET_RAW)) अणु
			err = -EPERM;
			जाओ करोne;
		पूर्ण

		hci_pi(sk)->channel = haddr.hci_channel;

		/* The monitor पूर्णांकerface is restricted to CAP_NET_RAW
		 * capabilities and with that implicitly trusted.
		 */
		hci_sock_set_flag(sk, HCI_SOCK_TRUSTED);

		send_monitor_note(sk, "Linux version %s (%s)",
				  init_utsname()->release,
				  init_utsname()->machine);
		send_monitor_note(sk, "Bluetooth subsystem version %u.%u",
				  BT_SUBSYS_VERSION, BT_SUBSYS_REVISION);
		send_monitor_replay(sk);
		send_monitor_control_replay(sk);

		atomic_inc(&monitor_promisc);
		अवरोध;

	हाल HCI_CHANNEL_LOGGING:
		अगर (haddr.hci_dev != HCI_DEV_NONE) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (!capable(CAP_NET_ADMIN)) अणु
			err = -EPERM;
			जाओ करोne;
		पूर्ण

		hci_pi(sk)->channel = haddr.hci_channel;
		अवरोध;

	शेष:
		अगर (!hci_mgmt_chan_find(haddr.hci_channel)) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (haddr.hci_dev != HCI_DEV_NONE) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण

		/* Users with CAP_NET_ADMIN capabilities are allowed
		 * access to all management commands and events. For
		 * untrusted users the पूर्णांकerface is restricted and
		 * also only untrusted events are sent.
		 */
		अगर (capable(CAP_NET_ADMIN))
			hci_sock_set_flag(sk, HCI_SOCK_TRUSTED);

		hci_pi(sk)->channel = haddr.hci_channel;

		/* At the moment the index and unconfigured index events
		 * are enabled unconditionally. Setting them on each
		 * socket when binding keeps this functionality. They
		 * however might be cleared later and then sending of these
		 * events will be disabled, but that is then पूर्णांकentional.
		 *
		 * This also enables generic events that are safe to be
		 * received by untrusted users. Example क्रम such events
		 * are changes to settings, class of device, name etc.
		 */
		अगर (hci_pi(sk)->channel == HCI_CHANNEL_CONTROL) अणु
			अगर (!hci_sock_gen_cookie(sk)) अणु
				/* In the हाल when a cookie has alपढ़ोy been
				 * asचिन्हित, this socket will transtion from
				 * a raw socket पूर्णांकo a control socket. To
				 * allow क्रम a clean transtion, send the
				 * बंद notअगरication first.
				 */
				skb = create_monitor_ctrl_बंद(sk);
				अगर (skb) अणु
					hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
							    HCI_SOCK_TRUSTED, शून्य);
					kमुक्त_skb(skb);
				पूर्ण
			पूर्ण

			/* Send event to monitor */
			skb = create_monitor_ctrl_खोलो(sk);
			अगर (skb) अणु
				hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
						    HCI_SOCK_TRUSTED, शून्य);
				kमुक्त_skb(skb);
			पूर्ण

			hci_sock_set_flag(sk, HCI_MGMT_INDEX_EVENTS);
			hci_sock_set_flag(sk, HCI_MGMT_UNCONF_INDEX_EVENTS);
			hci_sock_set_flag(sk, HCI_MGMT_OPTION_EVENTS);
			hci_sock_set_flag(sk, HCI_MGMT_SETTING_EVENTS);
			hci_sock_set_flag(sk, HCI_MGMT_DEV_CLASS_EVENTS);
			hci_sock_set_flag(sk, HCI_MGMT_LOCAL_NAME_EVENTS);
		पूर्ण
		अवरोध;
	पूर्ण

	sk->sk_state = BT_BOUND;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक hci_sock_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			    पूर्णांक peer)
अणु
	काष्ठा sockaddr_hci *haddr = (काष्ठा sockaddr_hci *)addr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा hci_dev *hdev;
	पूर्णांक err = 0;

	BT_DBG("sock %p sk %p", sock, sk);

	अगर (peer)
		वापस -EOPNOTSUPP;

	lock_sock(sk);

	hdev = hci_pi(sk)->hdev;
	अगर (!hdev) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	haddr->hci_family = AF_BLUETOOTH;
	haddr->hci_dev    = hdev->id;
	haddr->hci_channel= hci_pi(sk)->channel;
	err = माप(*haddr);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल व्योम hci_sock_cmsg(काष्ठा sock *sk, काष्ठा msghdr *msg,
			  काष्ठा sk_buff *skb)
अणु
	__u8 mask = hci_pi(sk)->cmsg_mask;

	अगर (mask & HCI_CMSG_सूची) अणु
		पूर्णांक incoming = bt_cb(skb)->incoming;
		put_cmsg(msg, SOL_HCI, HCI_CMSG_सूची, माप(incoming),
			 &incoming);
	पूर्ण

	अगर (mask & HCI_CMSG_TSTAMP) अणु
#अगर_घोषित CONFIG_COMPAT
		काष्ठा old_समयval32 ctv;
#पूर्ण_अगर
		काष्ठा __kernel_old_समयval tv;
		व्योम *data;
		पूर्णांक len;

		skb_get_बारtamp(skb, &tv);

		data = &tv;
		len = माप(tv);
#अगर_घोषित CONFIG_COMPAT
		अगर (!COMPAT_USE_64BIT_TIME &&
		    (msg->msg_flags & MSG_CMSG_COMPAT)) अणु
			ctv.tv_sec = tv.tv_sec;
			ctv.tv_usec = tv.tv_usec;
			data = &ctv;
			len = माप(ctv);
		पूर्ण
#पूर्ण_अगर

		put_cmsg(msg, SOL_HCI, HCI_CMSG_TSTAMP, len, data);
	पूर्ण
पूर्ण

अटल पूर्णांक hci_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार len, पूर्णांक flags)
अणु
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक copied, err;
	अचिन्हित पूर्णांक skblen;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	अगर (hci_pi(sk)->channel == HCI_CHANNEL_LOGGING)
		वापस -EOPNOTSUPP;

	अगर (sk->sk_state == BT_CLOSED)
		वापस 0;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		वापस err;

	skblen = skb->len;
	copied = skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	skb_reset_transport_header(skb);
	err = skb_copy_datagram_msg(skb, 0, msg, copied);

	चयन (hci_pi(sk)->channel) अणु
	हाल HCI_CHANNEL_RAW:
		hci_sock_cmsg(sk, msg, skb);
		अवरोध;
	हाल HCI_CHANNEL_USER:
	हाल HCI_CHANNEL_MONITOR:
		sock_recv_बारtamp(msg, sk, skb);
		अवरोध;
	शेष:
		अगर (hci_mgmt_chan_find(hci_pi(sk)->channel))
			sock_recv_बारtamp(msg, sk, skb);
		अवरोध;
	पूर्ण

	skb_मुक्त_datagram(sk, skb);

	अगर (flags & MSG_TRUNC)
		copied = skblen;

	वापस err ? : copied;
पूर्ण

अटल पूर्णांक hci_mgmt_cmd(काष्ठा hci_mgmt_chan *chan, काष्ठा sock *sk,
			काष्ठा msghdr *msg, माप_प्रकार msglen)
अणु
	व्योम *buf;
	u8 *cp;
	काष्ठा mgmt_hdr *hdr;
	u16 opcode, index, len;
	काष्ठा hci_dev *hdev = शून्य;
	स्थिर काष्ठा hci_mgmt_handler *handler;
	bool var_len, no_hdev;
	पूर्णांक err;

	BT_DBG("got %zu bytes", msglen);

	अगर (msglen < माप(*hdr))
		वापस -EINVAL;

	buf = kदो_स्मृति(msglen, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (स_नकल_from_msg(buf, msg, msglen)) अणु
		err = -EFAULT;
		जाओ करोne;
	पूर्ण

	hdr = buf;
	opcode = __le16_to_cpu(hdr->opcode);
	index = __le16_to_cpu(hdr->index);
	len = __le16_to_cpu(hdr->len);

	अगर (len != msglen - माप(*hdr)) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (chan->channel == HCI_CHANNEL_CONTROL) अणु
		काष्ठा sk_buff *skb;

		/* Send event to monitor */
		skb = create_monitor_ctrl_command(sk, index, opcode, len,
						  buf + माप(*hdr));
		अगर (skb) अणु
			hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
					    HCI_SOCK_TRUSTED, शून्य);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	अगर (opcode >= chan->handler_count ||
	    chan->handlers[opcode].func == शून्य) अणु
		BT_DBG("Unknown op %u", opcode);
		err = mgmt_cmd_status(sk, index, opcode,
				      MGMT_STATUS_UNKNOWN_COMMAND);
		जाओ करोne;
	पूर्ण

	handler = &chan->handlers[opcode];

	अगर (!hci_sock_test_flag(sk, HCI_SOCK_TRUSTED) &&
	    !(handler->flags & HCI_MGMT_UNTRUSTED)) अणु
		err = mgmt_cmd_status(sk, index, opcode,
				      MGMT_STATUS_PERMISSION_DENIED);
		जाओ करोne;
	पूर्ण

	अगर (index != MGMT_INDEX_NONE) अणु
		hdev = hci_dev_get(index);
		अगर (!hdev) अणु
			err = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVALID_INDEX);
			जाओ करोne;
		पूर्ण

		अगर (hci_dev_test_flag(hdev, HCI_SETUP) ||
		    hci_dev_test_flag(hdev, HCI_CONFIG) ||
		    hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
			err = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVALID_INDEX);
			जाओ करोne;
		पूर्ण

		अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED) &&
		    !(handler->flags & HCI_MGMT_UNCONFIGURED)) अणु
			err = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVALID_INDEX);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (!(handler->flags & HCI_MGMT_HDEV_OPTIONAL)) अणु
		no_hdev = (handler->flags & HCI_MGMT_NO_HDEV);
		अगर (no_hdev != !hdev) अणु
			err = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVALID_INDEX);
			जाओ करोne;
		पूर्ण
	पूर्ण

	var_len = (handler->flags & HCI_MGMT_VAR_LEN);
	अगर ((var_len && len < handler->data_len) ||
	    (!var_len && len != handler->data_len)) अणु
		err = mgmt_cmd_status(sk, index, opcode,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ करोne;
	पूर्ण

	अगर (hdev && chan->hdev_init)
		chan->hdev_init(sk, hdev);

	cp = buf + माप(*hdr);

	err = handler->func(sk, hdev, cp, len);
	अगर (err < 0)
		जाओ करोne;

	err = msglen;

करोne:
	अगर (hdev)
		hci_dev_put(hdev);

	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक hci_logging_frame(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len)
अणु
	काष्ठा hci_mon_hdr *hdr;
	काष्ठा sk_buff *skb;
	काष्ठा hci_dev *hdev;
	u16 index;
	पूर्णांक err;

	/* The logging frame consists at minimum of the standard header,
	 * the priority byte, the ident length byte and at least one string
	 * terminator NUL byte. Anything लघुer are invalid packets.
	 */
	अगर (len < माप(*hdr) + 3)
		वापस -EINVAL;

	skb = bt_skb_send_alloc(sk, len, msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		वापस err;

	अगर (स_नकल_from_msg(skb_put(skb, len), msg, len)) अणु
		err = -EFAULT;
		जाओ drop;
	पूर्ण

	hdr = (व्योम *)skb->data;

	अगर (__le16_to_cpu(hdr->len) != len - माप(*hdr)) अणु
		err = -EINVAL;
		जाओ drop;
	पूर्ण

	अगर (__le16_to_cpu(hdr->opcode) == 0x0000) अणु
		__u8 priority = skb->data[माप(*hdr)];
		__u8 ident_len = skb->data[माप(*hdr) + 1];

		/* Only the priorities 0-7 are valid and with that any other
		 * value results in an invalid packet.
		 *
		 * The priority byte is followed by an ident length byte and
		 * the NUL terminated ident string. Check that the ident
		 * length is not overflowing the packet and also that the
		 * ident string itself is NUL terminated. In हाल the ident
		 * length is zero, the length value actually द्विगुनs as NUL
		 * terminator identअगरier.
		 *
		 * The message follows the ident string (अगर present) and
		 * must be NUL terminated. Otherwise it is not a valid packet.
		 */
		अगर (priority > 7 || skb->data[len - 1] != 0x00 ||
		    ident_len > len - माप(*hdr) - 3 ||
		    skb->data[माप(*hdr) + ident_len + 1] != 0x00) अणु
			err = -EINVAL;
			जाओ drop;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ drop;
	पूर्ण

	index = __le16_to_cpu(hdr->index);

	अगर (index != MGMT_INDEX_NONE) अणु
		hdev = hci_dev_get(index);
		अगर (!hdev) अणु
			err = -ENODEV;
			जाओ drop;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdev = शून्य;
	पूर्ण

	hdr->opcode = cpu_to_le16(HCI_MON_USER_LOGGING);

	hci_send_to_channel(HCI_CHANNEL_MONITOR, skb, HCI_SOCK_TRUSTED, शून्य);
	err = len;

	अगर (hdev)
		hci_dev_put(hdev);

drop:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक hci_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा hci_mgmt_chan *chan;
	काष्ठा hci_dev *hdev;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	BT_DBG("sock %p sk %p", sock, sk);

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	अगर (msg->msg_flags & ~(MSG_DONTWAIT|MSG_NOSIGNAL|MSG_ERRQUEUE|
			       MSG_CMSG_COMPAT))
		वापस -EINVAL;

	अगर (len < 4 || len > HCI_MAX_FRAME_SIZE)
		वापस -EINVAL;

	lock_sock(sk);

	चयन (hci_pi(sk)->channel) अणु
	हाल HCI_CHANNEL_RAW:
	हाल HCI_CHANNEL_USER:
		अवरोध;
	हाल HCI_CHANNEL_MONITOR:
		err = -EOPNOTSUPP;
		जाओ करोne;
	हाल HCI_CHANNEL_LOGGING:
		err = hci_logging_frame(sk, msg, len);
		जाओ करोne;
	शेष:
		mutex_lock(&mgmt_chan_list_lock);
		chan = __hci_mgmt_chan_find(hci_pi(sk)->channel);
		अगर (chan)
			err = hci_mgmt_cmd(chan, sk, msg, len);
		अन्यथा
			err = -EINVAL;

		mutex_unlock(&mgmt_chan_list_lock);
		जाओ करोne;
	पूर्ण

	hdev = hci_pi(sk)->hdev;
	अगर (!hdev) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (!test_bit(HCI_UP, &hdev->flags)) अणु
		err = -ENETDOWN;
		जाओ करोne;
	पूर्ण

	skb = bt_skb_send_alloc(sk, len, msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		जाओ करोne;

	अगर (स_नकल_from_msg(skb_put(skb, len), msg, len)) अणु
		err = -EFAULT;
		जाओ drop;
	पूर्ण

	hci_skb_pkt_type(skb) = skb->data[0];
	skb_pull(skb, 1);

	अगर (hci_pi(sk)->channel == HCI_CHANNEL_USER) अणु
		/* No permission check is needed क्रम user channel
		 * since that माला_लो enक्रमced when binding the socket.
		 *
		 * However check that the packet type is valid.
		 */
		अगर (hci_skb_pkt_type(skb) != HCI_COMMAND_PKT &&
		    hci_skb_pkt_type(skb) != HCI_ACLDATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT) अणु
			err = -EINVAL;
			जाओ drop;
		पूर्ण

		skb_queue_tail(&hdev->raw_q, skb);
		queue_work(hdev->workqueue, &hdev->tx_work);
	पूर्ण अन्यथा अगर (hci_skb_pkt_type(skb) == HCI_COMMAND_PKT) अणु
		u16 opcode = get_unaligned_le16(skb->data);
		u16 ogf = hci_opcode_ogf(opcode);
		u16 ocf = hci_opcode_ocf(opcode);

		अगर (((ogf > HCI_Sभग्न_उच्च_OGF) ||
		     !hci_test_bit(ocf & HCI_FLT_OCF_BITS,
				   &hci_sec_filter.ocf_mask[ogf])) &&
		    !capable(CAP_NET_RAW)) अणु
			err = -EPERM;
			जाओ drop;
		पूर्ण

		/* Since the opcode has alपढ़ोy been extracted here, store
		 * a copy of the value क्रम later use by the drivers.
		 */
		hci_skb_opcode(skb) = opcode;

		अगर (ogf == 0x3f) अणु
			skb_queue_tail(&hdev->raw_q, skb);
			queue_work(hdev->workqueue, &hdev->tx_work);
		पूर्ण अन्यथा अणु
			/* Stand-alone HCI commands must be flagged as
			 * single-command requests.
			 */
			bt_cb(skb)->hci.req_flags |= HCI_REQ_START;

			skb_queue_tail(&hdev->cmd_q, skb);
			queue_work(hdev->workqueue, &hdev->cmd_work);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!capable(CAP_NET_RAW)) अणु
			err = -EPERM;
			जाओ drop;
		पूर्ण

		अगर (hci_skb_pkt_type(skb) != HCI_ACLDATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT) अणु
			err = -EINVAL;
			जाओ drop;
		पूर्ण

		skb_queue_tail(&hdev->raw_q, skb);
		queue_work(hdev->workqueue, &hdev->tx_work);
	पूर्ण

	err = len;

करोne:
	release_sock(sk);
	वापस err;

drop:
	kमुक्त_skb(skb);
	जाओ करोne;
पूर्ण

अटल पूर्णांक hci_sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hci_ufilter uf = अणु .opcode = 0 पूर्ण;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0, opt = 0;

	BT_DBG("sk %p, opt %d", sk, optname);

	अगर (level != SOL_HCI)
		वापस -ENOPROTOOPT;

	lock_sock(sk);

	अगर (hci_pi(sk)->channel != HCI_CHANNEL_RAW) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	चयन (optname) अणु
	हाल HCI_DATA_सूची:
		अगर (copy_from_sockptr(&opt, optval, माप(opt))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt)
			hci_pi(sk)->cmsg_mask |= HCI_CMSG_सूची;
		अन्यथा
			hci_pi(sk)->cmsg_mask &= ~HCI_CMSG_सूची;
		अवरोध;

	हाल HCI_TIME_STAMP:
		अगर (copy_from_sockptr(&opt, optval, माप(opt))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt)
			hci_pi(sk)->cmsg_mask |= HCI_CMSG_TSTAMP;
		अन्यथा
			hci_pi(sk)->cmsg_mask &= ~HCI_CMSG_TSTAMP;
		अवरोध;

	हाल HCI_FILTER:
		अणु
			काष्ठा hci_filter *f = &hci_pi(sk)->filter;

			uf.type_mask = f->type_mask;
			uf.opcode    = f->opcode;
			uf.event_mask[0] = *((u32 *) f->event_mask + 0);
			uf.event_mask[1] = *((u32 *) f->event_mask + 1);
		पूर्ण

		len = min_t(अचिन्हित पूर्णांक, len, माप(uf));
		अगर (copy_from_sockptr(&uf, optval, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (!capable(CAP_NET_RAW)) अणु
			uf.type_mask &= hci_sec_filter.type_mask;
			uf.event_mask[0] &= *((u32 *) hci_sec_filter.event_mask + 0);
			uf.event_mask[1] &= *((u32 *) hci_sec_filter.event_mask + 1);
		पूर्ण

		अणु
			काष्ठा hci_filter *f = &hci_pi(sk)->filter;

			f->type_mask = uf.type_mask;
			f->opcode    = uf.opcode;
			*((u32 *) f->event_mask + 0) = uf.event_mask[0];
			*((u32 *) f->event_mask + 1) = uf.event_mask[1];
		पूर्ण
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक hci_sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा hci_ufilter uf;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक len, opt, err = 0;

	BT_DBG("sk %p, opt %d", sk, optname);

	अगर (level != SOL_HCI)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	lock_sock(sk);

	अगर (hci_pi(sk)->channel != HCI_CHANNEL_RAW) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	चयन (optname) अणु
	हाल HCI_DATA_सूची:
		अगर (hci_pi(sk)->cmsg_mask & HCI_CMSG_सूची)
			opt = 1;
		अन्यथा
			opt = 0;

		अगर (put_user(opt, optval))
			err = -EFAULT;
		अवरोध;

	हाल HCI_TIME_STAMP:
		अगर (hci_pi(sk)->cmsg_mask & HCI_CMSG_TSTAMP)
			opt = 1;
		अन्यथा
			opt = 0;

		अगर (put_user(opt, optval))
			err = -EFAULT;
		अवरोध;

	हाल HCI_FILTER:
		अणु
			काष्ठा hci_filter *f = &hci_pi(sk)->filter;

			स_रखो(&uf, 0, माप(uf));
			uf.type_mask = f->type_mask;
			uf.opcode    = f->opcode;
			uf.event_mask[0] = *((u32 *) f->event_mask + 0);
			uf.event_mask[1] = *((u32 *) f->event_mask + 1);
		पूर्ण

		len = min_t(अचिन्हित पूर्णांक, len, माप(uf));
		अगर (copy_to_user(optval, &uf, len))
			err = -EFAULT;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proto_ops hci_sock_ops = अणु
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.release	= hci_sock_release,
	.bind		= hci_sock_bind,
	.getname	= hci_sock_getname,
	.sendmsg	= hci_sock_sendmsg,
	.recvmsg	= hci_sock_recvmsg,
	.ioctl		= hci_sock_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= hci_sock_compat_ioctl,
#पूर्ण_अगर
	.poll		= datagram_poll,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.setsockopt	= hci_sock_setsockopt,
	.माला_लोockopt	= hci_sock_माला_लोockopt,
	.connect	= sock_no_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.mmap		= sock_no_mmap
पूर्ण;

अटल काष्ठा proto hci_sk_proto = अणु
	.name		= "HCI",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा hci_pinfo)
पूर्ण;

अटल पूर्णांक hci_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			   पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	BT_DBG("sock %p", sock);

	अगर (sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;

	sock->ops = &hci_sock_ops;

	sk = sk_alloc(net, PF_BLUETOOTH, GFP_ATOMIC, &hci_sk_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = protocol;

	sock->state = SS_UNCONNECTED;
	sk->sk_state = BT_OPEN;

	bt_sock_link(&hci_sk_list, sk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family hci_sock_family_ops = अणु
	.family	= PF_BLUETOOTH,
	.owner	= THIS_MODULE,
	.create	= hci_sock_create,
पूर्ण;

पूर्णांक __init hci_sock_init(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा sockaddr_hci) > माप(काष्ठा sockaddr));

	err = proto_रेजिस्टर(&hci_sk_proto, 0);
	अगर (err < 0)
		वापस err;

	err = bt_sock_रेजिस्टर(BTPROTO_HCI, &hci_sock_family_ops);
	अगर (err < 0) अणु
		BT_ERR("HCI socket registration failed");
		जाओ error;
	पूर्ण

	err = bt_procfs_init(&init_net, "hci", &hci_sk_list, शून्य);
	अगर (err < 0) अणु
		BT_ERR("Failed to create HCI proc file");
		bt_sock_unरेजिस्टर(BTPROTO_HCI);
		जाओ error;
	पूर्ण

	BT_INFO("HCI socket layer initialized");

	वापस 0;

error:
	proto_unरेजिस्टर(&hci_sk_proto);
	वापस err;
पूर्ण

व्योम hci_sock_cleanup(व्योम)
अणु
	bt_procfs_cleanup(&init_net, "hci");
	bt_sock_unरेजिस्टर(BTPROTO_HCI);
	proto_unरेजिस्टर(&hci_sk_proto);
पूर्ण
