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

#अगर_अघोषित __BLUETOOTH_H
#घोषणा __BLUETOOTH_H

#समावेश <linux/poll.h>
#समावेश <net/sock.h>
#समावेश <linux/seq_file.h>

#घोषणा BT_SUBSYS_VERSION	2
#घोषणा BT_SUBSYS_REVISION	22

#अगर_अघोषित AF_BLUETOOTH
#घोषणा AF_BLUETOOTH	31
#घोषणा PF_BLUETOOTH	AF_BLUETOOTH
#पूर्ण_अगर

/* Bluetooth versions */
#घोषणा BLUETOOTH_VER_1_1	1
#घोषणा BLUETOOTH_VER_1_2	2
#घोषणा BLUETOOTH_VER_2_0	3
#घोषणा BLUETOOTH_VER_2_1	4
#घोषणा BLUETOOTH_VER_4_0	6

/* Reserv क्रम core and drivers use */
#घोषणा BT_SKB_RESERVE	8

#घोषणा BTPROTO_L2CAP	0
#घोषणा BTPROTO_HCI	1
#घोषणा BTPROTO_SCO	2
#घोषणा BTPROTO_RFCOMM	3
#घोषणा BTPROTO_BNEP	4
#घोषणा BTPROTO_CMTP	5
#घोषणा BTPROTO_HIDP	6
#घोषणा BTPROTO_AVDTP	7

#घोषणा SOL_HCI		0
#घोषणा SOL_L2CAP	6
#घोषणा SOL_SCO		17
#घोषणा SOL_RFCOMM	18

#घोषणा BT_SECURITY	4
काष्ठा bt_security अणु
	__u8 level;
	__u8 key_size;
पूर्ण;
#घोषणा BT_SECURITY_SDP		0
#घोषणा BT_SECURITY_LOW		1
#घोषणा BT_SECURITY_MEDIUM	2
#घोषणा BT_SECURITY_HIGH	3
#घोषणा BT_SECURITY_FIPS	4

#घोषणा BT_DEFER_SETUP	7

#घोषणा BT_FLUSHABLE	8

#घोषणा BT_FLUSHABLE_OFF	0
#घोषणा BT_FLUSHABLE_ON		1

#घोषणा BT_POWER	9
काष्ठा bt_घातer अणु
	__u8 क्रमce_active;
पूर्ण;
#घोषणा BT_POWER_FORCE_ACTIVE_OFF 0
#घोषणा BT_POWER_FORCE_ACTIVE_ON  1

#घोषणा BT_CHANNEL_POLICY	10

/* BR/EDR only (शेष policy)
 *   AMP controllers cannot be used.
 *   Channel move requests from the remote device are denied.
 *   If the L2CAP channel is currently using AMP, move the channel to BR/EDR.
 */
#घोषणा BT_CHANNEL_POLICY_BREDR_ONLY		0

/* BR/EDR Preferred
 *   Allow use of AMP controllers.
 *   If the L2CAP channel is currently on AMP, move it to BR/EDR.
 *   Channel move requests from the remote device are allowed.
 */
#घोषणा BT_CHANNEL_POLICY_BREDR_PREFERRED	1

/* AMP Preferred
 *   Allow use of AMP controllers
 *   If the L2CAP channel is currently on BR/EDR and AMP controller
 *     resources are available, initiate a channel move to AMP.
 *   Channel move requests from the remote device are allowed.
 *   If the L2CAP socket has not been connected yet, try to create
 *     and configure the channel directly on an AMP controller rather
 *     than BR/EDR.
 */
#घोषणा BT_CHANNEL_POLICY_AMP_PREFERRED		2

#घोषणा BT_VOICE		11
काष्ठा bt_voice अणु
	__u16 setting;
पूर्ण;

#घोषणा BT_VOICE_TRANSPARENT			0x0003
#घोषणा BT_VOICE_CVSD_16BIT			0x0060

#घोषणा BT_SNDMTU		12
#घोषणा BT_RCVMTU		13
#घोषणा BT_PHY			14

#घोषणा BT_PHY_BR_1M_1SLOT	0x00000001
#घोषणा BT_PHY_BR_1M_3SLOT	0x00000002
#घोषणा BT_PHY_BR_1M_5SLOT	0x00000004
#घोषणा BT_PHY_EDR_2M_1SLOT	0x00000008
#घोषणा BT_PHY_EDR_2M_3SLOT	0x00000010
#घोषणा BT_PHY_EDR_2M_5SLOT	0x00000020
#घोषणा BT_PHY_EDR_3M_1SLOT	0x00000040
#घोषणा BT_PHY_EDR_3M_3SLOT	0x00000080
#घोषणा BT_PHY_EDR_3M_5SLOT	0x00000100
#घोषणा BT_PHY_LE_1M_TX		0x00000200
#घोषणा BT_PHY_LE_1M_RX		0x00000400
#घोषणा BT_PHY_LE_2M_TX		0x00000800
#घोषणा BT_PHY_LE_2M_RX		0x00001000
#घोषणा BT_PHY_LE_CODED_TX	0x00002000
#घोषणा BT_PHY_LE_CODED_RX	0x00004000

#घोषणा BT_MODE			15

#घोषणा BT_MODE_BASIC		0x00
#घोषणा BT_MODE_ERTM		0x01
#घोषणा BT_MODE_STREAMING	0x02
#घोषणा BT_MODE_LE_FLOWCTL	0x03
#घोषणा BT_MODE_EXT_FLOWCTL	0x04

#घोषणा BT_PKT_STATUS          16

#घोषणा BT_SCM_PKT_STATUS	0x03

__म_लिखो(1, 2)
व्योम bt_info(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2)
व्योम bt_warn(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2)
व्योम bt_err(स्थिर अक्षर *fmt, ...);
#अगर IS_ENABLED(CONFIG_BT_FEATURE_DEBUG)
व्योम bt_dbg_set(bool enable);
bool bt_dbg_get(व्योम);
__म_लिखो(1, 2)
व्योम bt_dbg(स्थिर अक्षर *fmt, ...);
#पूर्ण_अगर
__म_लिखो(1, 2)
व्योम bt_warn_ratelimited(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2)
व्योम bt_err_ratelimited(स्थिर अक्षर *fmt, ...);

#घोषणा BT_INFO(fmt, ...)	bt_info(fmt "\n", ##__VA_ARGS__)
#घोषणा BT_WARN(fmt, ...)	bt_warn(fmt "\n", ##__VA_ARGS__)
#घोषणा BT_ERR(fmt, ...)	bt_err(fmt "\n", ##__VA_ARGS__)

#अगर IS_ENABLED(CONFIG_BT_FEATURE_DEBUG)
#घोषणा BT_DBG(fmt, ...)	bt_dbg(fmt "\n", ##__VA_ARGS__)
#अन्यथा
#घोषणा BT_DBG(fmt, ...)	pr_debug(fmt "\n", ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा bt_dev_info(hdev, fmt, ...)				\
	BT_INFO("%s: " fmt, (hdev)->name, ##__VA_ARGS__)
#घोषणा bt_dev_warn(hdev, fmt, ...)				\
	BT_WARN("%s: " fmt, (hdev)->name, ##__VA_ARGS__)
#घोषणा bt_dev_err(hdev, fmt, ...)				\
	BT_ERR("%s: " fmt, (hdev)->name, ##__VA_ARGS__)
#घोषणा bt_dev_dbg(hdev, fmt, ...)				\
	BT_DBG("%s: " fmt, (hdev)->name, ##__VA_ARGS__)

#घोषणा bt_dev_warn_ratelimited(hdev, fmt, ...)			\
	bt_warn_ratelimited("%s: " fmt, (hdev)->name, ##__VA_ARGS__)
#घोषणा bt_dev_err_ratelimited(hdev, fmt, ...)			\
	bt_err_ratelimited("%s: " fmt, (hdev)->name, ##__VA_ARGS__)

/* Connection and socket states */
क्रमागत अणु
	BT_CONNECTED = 1, /* Equal to TCP_ESTABLISHED to make net code happy */
	BT_OPEN,
	BT_BOUND,
	BT_LISTEN,
	BT_CONNECT,
	BT_CONNECT2,
	BT_CONFIG,
	BT_DISCONN,
	BT_CLOSED
पूर्ण;

/* If unused will be हटाओd by compiler */
अटल अंतरभूत स्थिर अक्षर *state_to_string(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल BT_CONNECTED:
		वापस "BT_CONNECTED";
	हाल BT_OPEN:
		वापस "BT_OPEN";
	हाल BT_BOUND:
		वापस "BT_BOUND";
	हाल BT_LISTEN:
		वापस "BT_LISTEN";
	हाल BT_CONNECT:
		वापस "BT_CONNECT";
	हाल BT_CONNECT2:
		वापस "BT_CONNECT2";
	हाल BT_CONFIG:
		वापस "BT_CONFIG";
	हाल BT_DISCONN:
		वापस "BT_DISCONN";
	हाल BT_CLOSED:
		वापस "BT_CLOSED";
	पूर्ण

	वापस "invalid state";
पूर्ण

/* BD Address */
प्रकार काष्ठा अणु
	__u8 b[6];
पूर्ण __packed bdaddr_t;

/* BD Address type */
#घोषणा BDADDR_BREDR		0x00
#घोषणा BDADDR_LE_PUBLIC	0x01
#घोषणा BDADDR_LE_RANDOM	0x02

अटल अंतरभूत bool bdaddr_type_is_valid(u8 type)
अणु
	चयन (type) अणु
	हाल BDADDR_BREDR:
	हाल BDADDR_LE_PUBLIC:
	हाल BDADDR_LE_RANDOM:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool bdaddr_type_is_le(u8 type)
अणु
	चयन (type) अणु
	हाल BDADDR_LE_PUBLIC:
	हाल BDADDR_LE_RANDOM:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा BDADDR_ANY  (&(bdaddr_t) अणुअणु0, 0, 0, 0, 0, 0पूर्णपूर्ण)
#घोषणा BDADDR_NONE (&(bdaddr_t) अणुअणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्णपूर्ण)

/* Copy, swap, convert BD Address */
अटल अंतरभूत पूर्णांक bacmp(स्थिर bdaddr_t *ba1, स्थिर bdaddr_t *ba2)
अणु
	वापस स_भेद(ba1, ba2, माप(bdaddr_t));
पूर्ण
अटल अंतरभूत व्योम bacpy(bdaddr_t *dst, स्थिर bdaddr_t *src)
अणु
	स_नकल(dst, src, माप(bdaddr_t));
पूर्ण

व्योम baswap(bdaddr_t *dst, स्थिर bdaddr_t *src);

/* Common socket काष्ठाures and functions */

#घोषणा bt_sk(__sk) ((काष्ठा bt_sock *) __sk)

काष्ठा bt_sock अणु
	काष्ठा sock sk;
	काष्ठा list_head accept_q;
	काष्ठा sock *parent;
	अचिन्हित दीर्घ flags;
	व्योम (*skb_msg_name)(काष्ठा sk_buff *, व्योम *, पूर्णांक *);
	व्योम (*skb_put_cmsg)(काष्ठा sk_buff *, काष्ठा msghdr *, काष्ठा sock *);
पूर्ण;

क्रमागत अणु
	BT_SK_DEFER_SETUP,
	BT_SK_SUSPEND,
पूर्ण;

काष्ठा bt_sock_list अणु
	काष्ठा hlist_head head;
	rwlock_t          lock;
#अगर_घोषित CONFIG_PROC_FS
        पूर्णांक (* custom_seq_show)(काष्ठा seq_file *, व्योम *);
#पूर्ण_अगर
पूर्ण;

पूर्णांक  bt_sock_रेजिस्टर(पूर्णांक proto, स्थिर काष्ठा net_proto_family *ops);
व्योम bt_sock_unरेजिस्टर(पूर्णांक proto);
व्योम bt_sock_link(काष्ठा bt_sock_list *l, काष्ठा sock *s);
व्योम bt_sock_unlink(काष्ठा bt_sock_list *l, काष्ठा sock *s);
पूर्णांक  bt_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		     पूर्णांक flags);
पूर्णांक  bt_sock_stream_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार len, पूर्णांक flags);
__poll_t bt_sock_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको);
पूर्णांक  bt_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक  bt_sock_रुको_state(काष्ठा sock *sk, पूर्णांक state, अचिन्हित दीर्घ समयo);
पूर्णांक  bt_sock_रुको_पढ़ोy(काष्ठा sock *sk, अचिन्हित दीर्घ flags);

व्योम bt_accept_enqueue(काष्ठा sock *parent, काष्ठा sock *sk, bool bh);
व्योम bt_accept_unlink(काष्ठा sock *sk);
काष्ठा sock *bt_accept_dequeue(काष्ठा sock *parent, काष्ठा socket *newsock);

/* Skb helpers */
काष्ठा l2cap_ctrl अणु
	u8	sframe:1,
		poll:1,
		final:1,
		fcs:1,
		sar:2,
		super:2;

	u16	reqseq;
	u16	txseq;
	u8	retries;
	__le16  psm;
	bdaddr_t bdaddr;
	काष्ठा l2cap_chan *chan;
पूर्ण;

काष्ठा sco_ctrl अणु
	u8	pkt_status;
पूर्ण;

काष्ठा hci_dev;

प्रकार व्योम (*hci_req_complete_t)(काष्ठा hci_dev *hdev, u8 status, u16 opcode);
प्रकार व्योम (*hci_req_complete_skb_t)(काष्ठा hci_dev *hdev, u8 status,
				       u16 opcode, काष्ठा sk_buff *skb);

#घोषणा HCI_REQ_START	BIT(0)
#घोषणा HCI_REQ_SKB	BIT(1)

काष्ठा hci_ctrl अणु
	u16 opcode;
	u8 req_flags;
	u8 req_event;
	जोड़ अणु
		hci_req_complete_t req_complete;
		hci_req_complete_skb_t req_complete_skb;
	पूर्ण;
पूर्ण;

काष्ठा bt_skb_cb अणु
	u8 pkt_type;
	u8 क्रमce_active;
	u16 expect;
	u8 incoming:1;
	जोड़ अणु
		काष्ठा l2cap_ctrl l2cap;
		काष्ठा sco_ctrl sco;
		काष्ठा hci_ctrl hci;
	पूर्ण;
पूर्ण;
#घोषणा bt_cb(skb) ((काष्ठा bt_skb_cb *)((skb)->cb))

#घोषणा hci_skb_pkt_type(skb) bt_cb((skb))->pkt_type
#घोषणा hci_skb_expect(skb) bt_cb((skb))->expect
#घोषणा hci_skb_opcode(skb) bt_cb((skb))->hci.opcode

अटल अंतरभूत काष्ठा sk_buff *bt_skb_alloc(अचिन्हित पूर्णांक len, gfp_t how)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len + BT_SKB_RESERVE, how);
	अगर (skb)
		skb_reserve(skb, BT_SKB_RESERVE);
	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *bt_skb_send_alloc(काष्ठा sock *sk,
					अचिन्हित दीर्घ len, पूर्णांक nb, पूर्णांक *err)
अणु
	काष्ठा sk_buff *skb;

	skb = sock_alloc_send_skb(sk, len + BT_SKB_RESERVE, nb, err);
	अगर (skb)
		skb_reserve(skb, BT_SKB_RESERVE);

	अगर (!skb && *err)
		वापस शून्य;

	*err = sock_error(sk);
	अगर (*err)
		जाओ out;

	अगर (sk->sk_shutकरोwn) अणु
		*err = -ECONNRESET;
		जाओ out;
	पूर्ण

	वापस skb;

out:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

पूर्णांक bt_to_त्रुटि_सं(u16 code);

व्योम hci_sock_set_flag(काष्ठा sock *sk, पूर्णांक nr);
व्योम hci_sock_clear_flag(काष्ठा sock *sk, पूर्णांक nr);
पूर्णांक hci_sock_test_flag(काष्ठा sock *sk, पूर्णांक nr);
अचिन्हित लघु hci_sock_get_channel(काष्ठा sock *sk);
u32 hci_sock_get_cookie(काष्ठा sock *sk);

पूर्णांक hci_sock_init(व्योम);
व्योम hci_sock_cleanup(व्योम);

पूर्णांक bt_sysfs_init(व्योम);
व्योम bt_sysfs_cleanup(व्योम);

पूर्णांक bt_procfs_init(काष्ठा net *net, स्थिर अक्षर *name,
		   काष्ठा bt_sock_list *sk_list,
		   पूर्णांक (*seq_show)(काष्ठा seq_file *, व्योम *));
व्योम bt_procfs_cleanup(काष्ठा net *net, स्थिर अक्षर *name);

बाह्य काष्ठा dentry *bt_debugfs;

पूर्णांक l2cap_init(व्योम);
व्योम l2cap_निकास(व्योम);

#अगर IS_ENABLED(CONFIG_BT_BREDR)
पूर्णांक sco_init(व्योम);
व्योम sco_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक sco_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sco_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक mgmt_init(व्योम);
व्योम mgmt_निकास(व्योम);

व्योम bt_sock_reclassअगरy_lock(काष्ठा sock *sk, पूर्णांक proto);

#पूर्ण_अगर /* __BLUETOOTH_H */
