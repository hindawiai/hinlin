<शैली गुरु>
/*
   RFCOMM implementation क्रम Linux Bluetooth stack (BlueZ)
   Copyright (C) 2002 Maxim Krasnyansky <maxk@qualcomm.com>
   Copyright (C) 2002 Marcel Holपंचांगann <marcel@holपंचांगann.org>

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

#समावेश <linux/refcount.h>

#अगर_अघोषित __RFCOMM_H
#घोषणा __RFCOMM_H

#घोषणा RFCOMM_CONN_TIMEOUT (HZ * 30)
#घोषणा RFCOMM_DISC_TIMEOUT (HZ * 20)
#घोषणा RFCOMM_AUTH_TIMEOUT (HZ * 25)
#घोषणा RFCOMM_IDLE_TIMEOUT (HZ * 2)

#घोषणा RFCOMM_DEFAULT_MTU	127
#घोषणा RFCOMM_DEFAULT_CREDITS	7

#घोषणा RFCOMM_MAX_CREDITS	40

#घोषणा RFCOMM_SKB_HEAD_RESERVE	8
#घोषणा RFCOMM_SKB_TAIL_RESERVE	2
#घोषणा RFCOMM_SKB_RESERVE  (RFCOMM_SKB_HEAD_RESERVE + RFCOMM_SKB_TAIL_RESERVE)

#घोषणा RFCOMM_SABM	0x2f
#घोषणा RFCOMM_DISC	0x43
#घोषणा RFCOMM_UA	0x63
#घोषणा RFCOMM_DM	0x0f
#घोषणा RFCOMM_UIH	0xef

#घोषणा RFCOMM_TEST	0x08
#घोषणा RFCOMM_FCON	0x28
#घोषणा RFCOMM_FCOFF	0x18
#घोषणा RFCOMM_MSC	0x38
#घोषणा RFCOMM_RPN	0x24
#घोषणा RFCOMM_RLS	0x14
#घोषणा RFCOMM_PN	0x20
#घोषणा RFCOMM_NSC	0x04

#घोषणा RFCOMM_V24_FC	0x02
#घोषणा RFCOMM_V24_RTC	0x04
#घोषणा RFCOMM_V24_RTR	0x08
#घोषणा RFCOMM_V24_IC	0x40
#घोषणा RFCOMM_V24_DV	0x80

#घोषणा RFCOMM_RPN_BR_2400	0x0
#घोषणा RFCOMM_RPN_BR_4800	0x1
#घोषणा RFCOMM_RPN_BR_7200	0x2
#घोषणा RFCOMM_RPN_BR_9600	0x3
#घोषणा RFCOMM_RPN_BR_19200	0x4
#घोषणा RFCOMM_RPN_BR_38400	0x5
#घोषणा RFCOMM_RPN_BR_57600	0x6
#घोषणा RFCOMM_RPN_BR_115200	0x7
#घोषणा RFCOMM_RPN_BR_230400	0x8

#घोषणा RFCOMM_RPN_DATA_5	0x0
#घोषणा RFCOMM_RPN_DATA_6	0x1
#घोषणा RFCOMM_RPN_DATA_7	0x2
#घोषणा RFCOMM_RPN_DATA_8	0x3

#घोषणा RFCOMM_RPN_STOP_1	0
#घोषणा RFCOMM_RPN_STOP_15	1

#घोषणा RFCOMM_RPN_PARITY_NONE	0x0
#घोषणा RFCOMM_RPN_PARITY_ODD	0x1
#घोषणा RFCOMM_RPN_PARITY_EVEN	0x3
#घोषणा RFCOMM_RPN_PARITY_MARK	0x5
#घोषणा RFCOMM_RPN_PARITY_SPACE	0x7

#घोषणा RFCOMM_RPN_FLOW_NONE	0x00

#घोषणा RFCOMM_RPN_XON_CHAR	0x11
#घोषणा RFCOMM_RPN_XOFF_CHAR	0x13

#घोषणा RFCOMM_RPN_PM_BITRATE		0x0001
#घोषणा RFCOMM_RPN_PM_DATA		0x0002
#घोषणा RFCOMM_RPN_PM_STOP		0x0004
#घोषणा RFCOMM_RPN_PM_PARITY		0x0008
#घोषणा RFCOMM_RPN_PM_PARITY_TYPE	0x0010
#घोषणा RFCOMM_RPN_PM_XON		0x0020
#घोषणा RFCOMM_RPN_PM_XOFF		0x0040
#घोषणा RFCOMM_RPN_PM_FLOW		0x3F00

#घोषणा RFCOMM_RPN_PM_ALL		0x3F7F

काष्ठा rfcomm_hdr अणु
	u8 addr;
	u8 ctrl;
	u8 len;    /* Actual size can be 2 bytes */
पूर्ण __packed;

काष्ठा rfcomm_cmd अणु
	u8 addr;
	u8 ctrl;
	u8 len;
	u8 fcs;
पूर्ण __packed;

काष्ठा rfcomm_mcc अणु
	u8 type;
	u8 len;
पूर्ण __packed;

काष्ठा rfcomm_pn अणु
	u8  dlci;
	u8  flow_ctrl;
	u8  priority;
	u8  ack_समयr;
	__le16 mtu;
	u8  max_retrans;
	u8  credits;
पूर्ण __packed;

काष्ठा rfcomm_rpn अणु
	u8  dlci;
	u8  bit_rate;
	u8  line_settings;
	u8  flow_ctrl;
	u8  xon_अक्षर;
	u8  xoff_अक्षर;
	__le16 param_mask;
पूर्ण __packed;

काष्ठा rfcomm_rls अणु
	u8  dlci;
	u8  status;
पूर्ण __packed;

काष्ठा rfcomm_msc अणु
	u8  dlci;
	u8  v24_sig;
पूर्ण __packed;

/* ---- Core काष्ठाures, flags etc ---- */

काष्ठा rfcomm_session अणु
	काष्ठा list_head list;
	काष्ठा socket   *sock;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ    state;
	अचिन्हित दीर्घ    flags;
	पूर्णांक              initiator;

	/* Default DLC parameters */
	पूर्णांक    cfc;
	uपूर्णांक   mtu;

	काष्ठा list_head dlcs;
पूर्ण;

काष्ठा rfcomm_dlc अणु
	काष्ठा list_head      list;
	काष्ठा rfcomm_session *session;
	काष्ठा sk_buff_head   tx_queue;
	काष्ठा समयr_list     समयr;

	काष्ठा mutex  lock;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ flags;
	refcount_t    refcnt;
	u8            dlci;
	u8            addr;
	u8            priority;
	u8            v24_sig;
	u8            remote_v24_sig;
	u8            mscex;
	u8            out;
	u8            sec_level;
	u8            role_चयन;
	u32           defer_setup;

	uपूर्णांक          mtu;
	uपूर्णांक          cfc;
	uपूर्णांक          rx_credits;
	uपूर्णांक          tx_credits;

	व्योम          *owner;

	व्योम (*data_पढ़ोy)(काष्ठा rfcomm_dlc *d, काष्ठा sk_buff *skb);
	व्योम (*state_change)(काष्ठा rfcomm_dlc *d, पूर्णांक err);
	व्योम (*modem_status)(काष्ठा rfcomm_dlc *d, u8 v24_sig);
पूर्ण;

/* DLC and session flags */
#घोषणा RFCOMM_RX_THROTTLED 0
#घोषणा RFCOMM_TX_THROTTLED 1
#घोषणा RFCOMM_TIMED_OUT    2
#घोषणा RFCOMM_MSC_PENDING  3
#घोषणा RFCOMM_SEC_PENDING  4
#घोषणा RFCOMM_AUTH_PENDING 5
#घोषणा RFCOMM_AUTH_ACCEPT  6
#घोषणा RFCOMM_AUTH_REJECT  7
#घोषणा RFCOMM_DEFER_SETUP  8
#घोषणा RFCOMM_ENC_DROP     9

/* Scheduling flags and events */
#घोषणा RFCOMM_SCHED_WAKEUP 31

/* MSC exchange flags */
#घोषणा RFCOMM_MSCEX_TX     1
#घोषणा RFCOMM_MSCEX_RX     2
#घोषणा RFCOMM_MSCEX_OK     (RFCOMM_MSCEX_TX + RFCOMM_MSCEX_RX)

/* CFC states */
#घोषणा RFCOMM_CFC_UNKNOWN  -1
#घोषणा RFCOMM_CFC_DISABLED 0
#घोषणा RFCOMM_CFC_ENABLED  RFCOMM_MAX_CREDITS

/* ---- RFCOMM SEND RPN ---- */
पूर्णांक rfcomm_send_rpn(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 dlci,
			u8 bit_rate, u8 data_bits, u8 stop_bits,
			u8 parity, u8 flow_ctrl_settings,
			u8 xon_अक्षर, u8 xoff_अक्षर, u16 param_mask);

/* ---- RFCOMM DLCs (channels) ---- */
काष्ठा rfcomm_dlc *rfcomm_dlc_alloc(gfp_t prio);
व्योम rfcomm_dlc_मुक्त(काष्ठा rfcomm_dlc *d);
पूर्णांक  rfcomm_dlc_खोलो(काष्ठा rfcomm_dlc *d, bdaddr_t *src, bdaddr_t *dst,
								u8 channel);
पूर्णांक  rfcomm_dlc_बंद(काष्ठा rfcomm_dlc *d, पूर्णांक reason);
पूर्णांक  rfcomm_dlc_send(काष्ठा rfcomm_dlc *d, काष्ठा sk_buff *skb);
व्योम rfcomm_dlc_send_noerror(काष्ठा rfcomm_dlc *d, काष्ठा sk_buff *skb);
पूर्णांक  rfcomm_dlc_set_modem_status(काष्ठा rfcomm_dlc *d, u8 v24_sig);
पूर्णांक  rfcomm_dlc_get_modem_status(काष्ठा rfcomm_dlc *d, u8 *v24_sig);
व्योम rfcomm_dlc_accept(काष्ठा rfcomm_dlc *d);
काष्ठा rfcomm_dlc *rfcomm_dlc_exists(bdaddr_t *src, bdaddr_t *dst, u8 channel);

#घोषणा rfcomm_dlc_lock(d)     mutex_lock(&d->lock)
#घोषणा rfcomm_dlc_unlock(d)   mutex_unlock(&d->lock)

अटल अंतरभूत व्योम rfcomm_dlc_hold(काष्ठा rfcomm_dlc *d)
अणु
	refcount_inc(&d->refcnt);
पूर्ण

अटल अंतरभूत व्योम rfcomm_dlc_put(काष्ठा rfcomm_dlc *d)
अणु
	अगर (refcount_dec_and_test(&d->refcnt))
		rfcomm_dlc_मुक्त(d);
पूर्ण

व्योम __rfcomm_dlc_throttle(काष्ठा rfcomm_dlc *d);
व्योम __rfcomm_dlc_unthrottle(काष्ठा rfcomm_dlc *d);

अटल अंतरभूत व्योम rfcomm_dlc_throttle(काष्ठा rfcomm_dlc *d)
अणु
	अगर (!test_and_set_bit(RFCOMM_RX_THROTTLED, &d->flags))
		__rfcomm_dlc_throttle(d);
पूर्ण

अटल अंतरभूत व्योम rfcomm_dlc_unthrottle(काष्ठा rfcomm_dlc *d)
अणु
	अगर (test_and_clear_bit(RFCOMM_RX_THROTTLED, &d->flags))
		__rfcomm_dlc_unthrottle(d);
पूर्ण

/* ---- RFCOMM sessions ---- */
व्योम   rfcomm_session_getaddr(काष्ठा rfcomm_session *s, bdaddr_t *src,
								bdaddr_t *dst);

/* ---- RFCOMM sockets ---- */
काष्ठा sockaddr_rc अणु
	sa_family_t	rc_family;
	bdaddr_t	rc_bdaddr;
	u8		rc_channel;
पूर्ण;

#घोषणा RFCOMM_CONNINFO	0x02
काष्ठा rfcomm_conninfo अणु
	__u16 hci_handle;
	__u8  dev_class[3];
पूर्ण;

#घोषणा RFCOMM_LM	0x03
#घोषणा RFCOMM_LM_MASTER	0x0001
#घोषणा RFCOMM_LM_AUTH		0x0002
#घोषणा RFCOMM_LM_ENCRYPT	0x0004
#घोषणा RFCOMM_LM_TRUSTED	0x0008
#घोषणा RFCOMM_LM_RELIABLE	0x0010
#घोषणा RFCOMM_LM_SECURE	0x0020
#घोषणा RFCOMM_LM_FIPS		0x0040

#घोषणा rfcomm_pi(sk) ((काष्ठा rfcomm_pinfo *) sk)

काष्ठा rfcomm_pinfo अणु
	काष्ठा bt_sock bt;
	bdaddr_t src;
	bdaddr_t dst;
	काष्ठा rfcomm_dlc   *dlc;
	u8     channel;
	u8     sec_level;
	u8     role_चयन;
पूर्ण;

पूर्णांक  rfcomm_init_sockets(व्योम);
व्योम rfcomm_cleanup_sockets(व्योम);

पूर्णांक  rfcomm_connect_ind(काष्ठा rfcomm_session *s, u8 channel,
							काष्ठा rfcomm_dlc **d);

/* ---- RFCOMM TTY ---- */
#घोषणा RFCOMM_MAX_DEV  256

#घोषणा RFCOMMCREATEDEV		_IOW('R', 200, पूर्णांक)
#घोषणा RFCOMMRELEASEDEV	_IOW('R', 201, पूर्णांक)
#घोषणा RFCOMMGETDEVLIST	_IOR('R', 210, पूर्णांक)
#घोषणा RFCOMMGETDEVINFO	_IOR('R', 211, पूर्णांक)
#घोषणा RFCOMMSTEALDLC		_IOW('R', 220, पूर्णांक)

/* rfcomm_dev.flags bit definitions */
#घोषणा RFCOMM_REUSE_DLC      0
#घोषणा RFCOMM_RELEASE_ONHUP  1
#घोषणा RFCOMM_HANGUP_NOW     2
#घोषणा RFCOMM_TTY_ATTACHED   3
#घोषणा RFCOMM_DEFUNCT_BIT4   4	  /* करोn't reuse this bit - userspace visible */

/* rfcomm_dev.status bit definitions */
#घोषणा RFCOMM_DEV_RELEASED   0
#घोषणा RFCOMM_TTY_OWNED      1

काष्ठा rfcomm_dev_req अणु
	s16      dev_id;
	u32      flags;
	bdaddr_t src;
	bdaddr_t dst;
	u8       channel;
पूर्ण;

काष्ठा rfcomm_dev_info अणु
	s16      id;
	u32      flags;
	u16      state;
	bdaddr_t src;
	bdaddr_t dst;
	u8       channel;
पूर्ण;

काष्ठा rfcomm_dev_list_req अणु
	u16      dev_num;
	काष्ठा   rfcomm_dev_info dev_info[];
पूर्ण;

पूर्णांक  rfcomm_dev_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, व्योम __user *arg);

#अगर_घोषित CONFIG_BT_RFCOMM_TTY
पूर्णांक  rfcomm_init_ttys(व्योम);
व्योम rfcomm_cleanup_ttys(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक rfcomm_init_ttys(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम rfcomm_cleanup_ttys(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __RFCOMM_H */
