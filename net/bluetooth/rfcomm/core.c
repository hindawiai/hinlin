<शैली गुरु>
/*
   RFCOMM implementation क्रम Linux Bluetooth stack (BlueZ).
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

/*
 * Bluetooth RFCOMM core.
 */

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>
#समावेश <net/bluetooth/rfcomm.h>

#घोषणा VERSION "1.11"

अटल bool disable_cfc;
अटल bool l2cap_erपंचांग;
अटल पूर्णांक channel_mtu = -1;

अटल काष्ठा task_काष्ठा *rfcomm_thपढ़ो;

अटल DEFINE_MUTEX(rfcomm_mutex);
#घोषणा rfcomm_lock()	mutex_lock(&rfcomm_mutex)
#घोषणा rfcomm_unlock()	mutex_unlock(&rfcomm_mutex)


अटल LIST_HEAD(session_list);

अटल पूर्णांक rfcomm_send_frame(काष्ठा rfcomm_session *s, u8 *data, पूर्णांक len);
अटल पूर्णांक rfcomm_send_sabm(काष्ठा rfcomm_session *s, u8 dlci);
अटल पूर्णांक rfcomm_send_disc(काष्ठा rfcomm_session *s, u8 dlci);
अटल पूर्णांक rfcomm_queue_disc(काष्ठा rfcomm_dlc *d);
अटल पूर्णांक rfcomm_send_nsc(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 type);
अटल पूर्णांक rfcomm_send_pn(काष्ठा rfcomm_session *s, पूर्णांक cr, काष्ठा rfcomm_dlc *d);
अटल पूर्णांक rfcomm_send_msc(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 dlci, u8 v24_sig);
अटल पूर्णांक rfcomm_send_test(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 *pattern, पूर्णांक len);
अटल पूर्णांक rfcomm_send_credits(काष्ठा rfcomm_session *s, u8 addr, u8 credits);
अटल व्योम rfcomm_make_uih(काष्ठा sk_buff *skb, u8 addr);

अटल व्योम rfcomm_process_connect(काष्ठा rfcomm_session *s);

अटल काष्ठा rfcomm_session *rfcomm_session_create(bdaddr_t *src,
							bdaddr_t *dst,
							u8 sec_level,
							पूर्णांक *err);
अटल काष्ठा rfcomm_session *rfcomm_session_get(bdaddr_t *src, bdaddr_t *dst);
अटल काष्ठा rfcomm_session *rfcomm_session_del(काष्ठा rfcomm_session *s);

/* ---- RFCOMM frame parsing macros ---- */
#घोषणा __get_dlci(b)     ((b & 0xfc) >> 2)
#घोषणा __get_type(b)     ((b & 0xef))

#घोषणा __test_ea(b)      ((b & 0x01))
#घोषणा __test_cr(b)      (!!(b & 0x02))
#घोषणा __test_pf(b)      (!!(b & 0x10))

#घोषणा __session_dir(s)  ((s)->initiator ? 0x00 : 0x01)

#घोषणा __addr(cr, dlci)       (((dlci & 0x3f) << 2) | (cr << 1) | 0x01)
#घोषणा __ctrl(type, pf)       (((type & 0xef) | (pf << 4)))
#घोषणा __dlci(dir, chn)       (((chn & 0x1f) << 1) | dir)
#घोषणा __srv_channel(dlci)    (dlci >> 1)

#घोषणा __len8(len)       (((len) << 1) | 1)
#घोषणा __len16(len)      ((len) << 1)

/* MCC macros */
#घोषणा __mcc_type(cr, type)   (((type << 2) | (cr << 1) | 0x01))
#घोषणा __get_mcc_type(b) ((b & 0xfc) >> 2)
#घोषणा __get_mcc_len(b)  ((b & 0xfe) >> 1)

/* RPN macros */
#घोषणा __rpn_line_settings(data, stop, parity)  ((data & 0x3) | ((stop & 0x1) << 2) | ((parity & 0x7) << 3))
#घोषणा __get_rpn_data_bits(line) ((line) & 0x3)
#घोषणा __get_rpn_stop_bits(line) (((line) >> 2) & 0x1)
#घोषणा __get_rpn_parity(line)    (((line) >> 3) & 0x7)

अटल DECLARE_WAIT_QUEUE_HEAD(rfcomm_wq);

अटल व्योम rfcomm_schedule(व्योम)
अणु
	wake_up_all(&rfcomm_wq);
पूर्ण

/* ---- RFCOMM FCS computation ---- */

/* reversed, 8-bit, poly=0x07 */
अटल अचिन्हित अक्षर rfcomm_crc_table[256] = अणु
	0x00, 0x91, 0xe3, 0x72, 0x07, 0x96, 0xe4, 0x75,
	0x0e, 0x9f, 0xed, 0x7c, 0x09, 0x98, 0xea, 0x7b,
	0x1c, 0x8d, 0xff, 0x6e, 0x1b, 0x8a, 0xf8, 0x69,
	0x12, 0x83, 0xf1, 0x60, 0x15, 0x84, 0xf6, 0x67,

	0x38, 0xa9, 0xdb, 0x4a, 0x3f, 0xae, 0xdc, 0x4d,
	0x36, 0xa7, 0xd5, 0x44, 0x31, 0xa0, 0xd2, 0x43,
	0x24, 0xb5, 0xc7, 0x56, 0x23, 0xb2, 0xc0, 0x51,
	0x2a, 0xbb, 0xc9, 0x58, 0x2d, 0xbc, 0xce, 0x5f,

	0x70, 0xe1, 0x93, 0x02, 0x77, 0xe6, 0x94, 0x05,
	0x7e, 0xef, 0x9d, 0x0c, 0x79, 0xe8, 0x9a, 0x0b,
	0x6c, 0xfd, 0x8f, 0x1e, 0x6b, 0xfa, 0x88, 0x19,
	0x62, 0xf3, 0x81, 0x10, 0x65, 0xf4, 0x86, 0x17,

	0x48, 0xd9, 0xab, 0x3a, 0x4f, 0xde, 0xac, 0x3d,
	0x46, 0xd7, 0xa5, 0x34, 0x41, 0xd0, 0xa2, 0x33,
	0x54, 0xc5, 0xb7, 0x26, 0x53, 0xc2, 0xb0, 0x21,
	0x5a, 0xcb, 0xb9, 0x28, 0x5d, 0xcc, 0xbe, 0x2f,

	0xe0, 0x71, 0x03, 0x92, 0xe7, 0x76, 0x04, 0x95,
	0xee, 0x7f, 0x0d, 0x9c, 0xe9, 0x78, 0x0a, 0x9b,
	0xfc, 0x6d, 0x1f, 0x8e, 0xfb, 0x6a, 0x18, 0x89,
	0xf2, 0x63, 0x11, 0x80, 0xf5, 0x64, 0x16, 0x87,

	0xd8, 0x49, 0x3b, 0xaa, 0xdf, 0x4e, 0x3c, 0xad,
	0xd6, 0x47, 0x35, 0xa4, 0xd1, 0x40, 0x32, 0xa3,
	0xc4, 0x55, 0x27, 0xb6, 0xc3, 0x52, 0x20, 0xb1,
	0xca, 0x5b, 0x29, 0xb8, 0xcd, 0x5c, 0x2e, 0xbf,

	0x90, 0x01, 0x73, 0xe2, 0x97, 0x06, 0x74, 0xe5,
	0x9e, 0x0f, 0x7d, 0xec, 0x99, 0x08, 0x7a, 0xeb,
	0x8c, 0x1d, 0x6f, 0xfe, 0x8b, 0x1a, 0x68, 0xf9,
	0x82, 0x13, 0x61, 0xf0, 0x85, 0x14, 0x66, 0xf7,

	0xa8, 0x39, 0x4b, 0xda, 0xaf, 0x3e, 0x4c, 0xdd,
	0xa6, 0x37, 0x45, 0xd4, 0xa1, 0x30, 0x42, 0xd3,
	0xb4, 0x25, 0x57, 0xc6, 0xb3, 0x22, 0x50, 0xc1,
	0xba, 0x2b, 0x59, 0xc8, 0xbd, 0x2c, 0x5e, 0xcf
पूर्ण;

/* CRC on 2 bytes */
#घोषणा __crc(data) (rfcomm_crc_table[rfcomm_crc_table[0xff ^ data[0]] ^ data[1]])

/* FCS on 2 bytes */
अटल अंतरभूत u8 __fcs(u8 *data)
अणु
	वापस 0xff - __crc(data);
पूर्ण

/* FCS on 3 bytes */
अटल अंतरभूत u8 __fcs2(u8 *data)
अणु
	वापस 0xff - rfcomm_crc_table[__crc(data) ^ data[2]];
पूर्ण

/* Check FCS */
अटल अंतरभूत पूर्णांक __check_fcs(u8 *data, पूर्णांक type, u8 fcs)
अणु
	u8 f = __crc(data);

	अगर (type != RFCOMM_UIH)
		f = rfcomm_crc_table[f ^ data[2]];

	वापस rfcomm_crc_table[f ^ fcs] != 0xcf;
पूर्ण

/* ---- L2CAP callbacks ---- */
अटल व्योम rfcomm_l2state_change(काष्ठा sock *sk)
अणु
	BT_DBG("%p state %d", sk, sk->sk_state);
	rfcomm_schedule();
पूर्ण

अटल व्योम rfcomm_l2data_पढ़ोy(काष्ठा sock *sk)
अणु
	BT_DBG("%p", sk);
	rfcomm_schedule();
पूर्ण

अटल पूर्णांक rfcomm_l2sock_create(काष्ठा socket **sock)
अणु
	पूर्णांक err;

	BT_DBG("");

	err = sock_create_kern(&init_net, PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP, sock);
	अगर (!err) अणु
		काष्ठा sock *sk = (*sock)->sk;
		sk->sk_data_पढ़ोy   = rfcomm_l2data_पढ़ोy;
		sk->sk_state_change = rfcomm_l2state_change;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_check_security(काष्ठा rfcomm_dlc *d)
अणु
	काष्ठा sock *sk = d->session->sock->sk;
	काष्ठा l2cap_conn *conn = l2cap_pi(sk)->chan->conn;

	__u8 auth_type;

	चयन (d->sec_level) अणु
	हाल BT_SECURITY_HIGH:
	हाल BT_SECURITY_FIPS:
		auth_type = HCI_AT_GENERAL_BONDING_MITM;
		अवरोध;
	हाल BT_SECURITY_MEDIUM:
		auth_type = HCI_AT_GENERAL_BONDING;
		अवरोध;
	शेष:
		auth_type = HCI_AT_NO_BONDING;
		अवरोध;
	पूर्ण

	वापस hci_conn_security(conn->hcon, d->sec_level, auth_type,
				 d->out);
पूर्ण

अटल व्योम rfcomm_session_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा rfcomm_session *s = from_समयr(s, t, समयr);

	BT_DBG("session %p state %ld", s, s->state);

	set_bit(RFCOMM_TIMED_OUT, &s->flags);
	rfcomm_schedule();
पूर्ण

अटल व्योम rfcomm_session_set_समयr(काष्ठा rfcomm_session *s, दीर्घ समयout)
अणु
	BT_DBG("session %p state %ld timeout %ld", s, s->state, समयout);

	mod_समयr(&s->समयr, jअगरfies + समयout);
पूर्ण

अटल व्योम rfcomm_session_clear_समयr(काष्ठा rfcomm_session *s)
अणु
	BT_DBG("session %p state %ld", s, s->state);

	del_समयr_sync(&s->समयr);
पूर्ण

/* ---- RFCOMM DLCs ---- */
अटल व्योम rfcomm_dlc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा rfcomm_dlc *d = from_समयr(d, t, समयr);

	BT_DBG("dlc %p state %ld", d, d->state);

	set_bit(RFCOMM_TIMED_OUT, &d->flags);
	rfcomm_dlc_put(d);
	rfcomm_schedule();
पूर्ण

अटल व्योम rfcomm_dlc_set_समयr(काष्ठा rfcomm_dlc *d, दीर्घ समयout)
अणु
	BT_DBG("dlc %p state %ld timeout %ld", d, d->state, समयout);

	अगर (!mod_समयr(&d->समयr, jअगरfies + समयout))
		rfcomm_dlc_hold(d);
पूर्ण

अटल व्योम rfcomm_dlc_clear_समयr(काष्ठा rfcomm_dlc *d)
अणु
	BT_DBG("dlc %p state %ld", d, d->state);

	अगर (del_समयr(&d->समयr))
		rfcomm_dlc_put(d);
पूर्ण

अटल व्योम rfcomm_dlc_clear_state(काष्ठा rfcomm_dlc *d)
अणु
	BT_DBG("%p", d);

	d->state      = BT_OPEN;
	d->flags      = 0;
	d->mscex      = 0;
	d->sec_level  = BT_SECURITY_LOW;
	d->mtu        = RFCOMM_DEFAULT_MTU;
	d->v24_sig    = RFCOMM_V24_RTC | RFCOMM_V24_RTR | RFCOMM_V24_DV;

	d->cfc        = RFCOMM_CFC_DISABLED;
	d->rx_credits = RFCOMM_DEFAULT_CREDITS;
पूर्ण

काष्ठा rfcomm_dlc *rfcomm_dlc_alloc(gfp_t prio)
अणु
	काष्ठा rfcomm_dlc *d = kzalloc(माप(*d), prio);

	अगर (!d)
		वापस शून्य;

	समयr_setup(&d->समयr, rfcomm_dlc_समयout, 0);

	skb_queue_head_init(&d->tx_queue);
	mutex_init(&d->lock);
	refcount_set(&d->refcnt, 1);

	rfcomm_dlc_clear_state(d);

	BT_DBG("%p", d);

	वापस d;
पूर्ण

व्योम rfcomm_dlc_मुक्त(काष्ठा rfcomm_dlc *d)
अणु
	BT_DBG("%p", d);

	skb_queue_purge(&d->tx_queue);
	kमुक्त(d);
पूर्ण

अटल व्योम rfcomm_dlc_link(काष्ठा rfcomm_session *s, काष्ठा rfcomm_dlc *d)
अणु
	BT_DBG("dlc %p session %p", d, s);

	rfcomm_session_clear_समयr(s);
	rfcomm_dlc_hold(d);
	list_add(&d->list, &s->dlcs);
	d->session = s;
पूर्ण

अटल व्योम rfcomm_dlc_unlink(काष्ठा rfcomm_dlc *d)
अणु
	काष्ठा rfcomm_session *s = d->session;

	BT_DBG("dlc %p refcnt %d session %p", d, refcount_पढ़ो(&d->refcnt), s);

	list_del(&d->list);
	d->session = शून्य;
	rfcomm_dlc_put(d);

	अगर (list_empty(&s->dlcs))
		rfcomm_session_set_समयr(s, RFCOMM_IDLE_TIMEOUT);
पूर्ण

अटल काष्ठा rfcomm_dlc *rfcomm_dlc_get(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	काष्ठा rfcomm_dlc *d;

	list_क्रम_each_entry(d, &s->dlcs, list)
		अगर (d->dlci == dlci)
			वापस d;

	वापस शून्य;
पूर्ण

अटल पूर्णांक rfcomm_check_channel(u8 channel)
अणु
	वापस channel < 1 || channel > 30;
पूर्ण

अटल पूर्णांक __rfcomm_dlc_खोलो(काष्ठा rfcomm_dlc *d, bdaddr_t *src, bdaddr_t *dst, u8 channel)
अणु
	काष्ठा rfcomm_session *s;
	पूर्णांक err = 0;
	u8 dlci;

	BT_DBG("dlc %p state %ld %pMR -> %pMR channel %d",
	       d, d->state, src, dst, channel);

	अगर (rfcomm_check_channel(channel))
		वापस -EINVAL;

	अगर (d->state != BT_OPEN && d->state != BT_CLOSED)
		वापस 0;

	s = rfcomm_session_get(src, dst);
	अगर (!s) अणु
		s = rfcomm_session_create(src, dst, d->sec_level, &err);
		अगर (!s)
			वापस err;
	पूर्ण

	dlci = __dlci(__session_dir(s), channel);

	/* Check अगर DLCI alपढ़ोy exists */
	अगर (rfcomm_dlc_get(s, dlci))
		वापस -EBUSY;

	rfcomm_dlc_clear_state(d);

	d->dlci     = dlci;
	d->addr     = __addr(s->initiator, dlci);
	d->priority = 7;

	d->state = BT_CONFIG;
	rfcomm_dlc_link(s, d);

	d->out = 1;

	d->mtu = s->mtu;
	d->cfc = (s->cfc == RFCOMM_CFC_UNKNOWN) ? 0 : s->cfc;

	अगर (s->state == BT_CONNECTED) अणु
		अगर (rfcomm_check_security(d))
			rfcomm_send_pn(s, 1, d);
		अन्यथा
			set_bit(RFCOMM_AUTH_PENDING, &d->flags);
	पूर्ण

	rfcomm_dlc_set_समयr(d, RFCOMM_CONN_TIMEOUT);

	वापस 0;
पूर्ण

पूर्णांक rfcomm_dlc_खोलो(काष्ठा rfcomm_dlc *d, bdaddr_t *src, bdaddr_t *dst, u8 channel)
अणु
	पूर्णांक r;

	rfcomm_lock();

	r = __rfcomm_dlc_खोलो(d, src, dst, channel);

	rfcomm_unlock();
	वापस r;
पूर्ण

अटल व्योम __rfcomm_dlc_disconn(काष्ठा rfcomm_dlc *d)
अणु
	काष्ठा rfcomm_session *s = d->session;

	d->state = BT_DISCONN;
	अगर (skb_queue_empty(&d->tx_queue)) अणु
		rfcomm_send_disc(s, d->dlci);
		rfcomm_dlc_set_समयr(d, RFCOMM_DISC_TIMEOUT);
	पूर्ण अन्यथा अणु
		rfcomm_queue_disc(d);
		rfcomm_dlc_set_समयr(d, RFCOMM_DISC_TIMEOUT * 2);
	पूर्ण
पूर्ण

अटल पूर्णांक __rfcomm_dlc_बंद(काष्ठा rfcomm_dlc *d, पूर्णांक err)
अणु
	काष्ठा rfcomm_session *s = d->session;
	अगर (!s)
		वापस 0;

	BT_DBG("dlc %p state %ld dlci %d err %d session %p",
			d, d->state, d->dlci, err, s);

	चयन (d->state) अणु
	हाल BT_CONNECT:
	हाल BT_CONFIG:
	हाल BT_OPEN:
	हाल BT_CONNECT2:
		अगर (test_and_clear_bit(RFCOMM_DEFER_SETUP, &d->flags)) अणु
			set_bit(RFCOMM_AUTH_REJECT, &d->flags);
			rfcomm_schedule();
			वापस 0;
		पूर्ण
	पूर्ण

	चयन (d->state) अणु
	हाल BT_CONNECT:
	हाल BT_CONNECTED:
		__rfcomm_dlc_disconn(d);
		अवरोध;

	हाल BT_CONFIG:
		अगर (s->state != BT_BOUND) अणु
			__rfcomm_dlc_disconn(d);
			अवरोध;
		पूर्ण
		/* अगर closing a dlc in a session that hasn't been started,
		 * just बंद and unlink the dlc
		 */
		fallthrough;

	शेष:
		rfcomm_dlc_clear_समयr(d);

		rfcomm_dlc_lock(d);
		d->state = BT_CLOSED;
		d->state_change(d, err);
		rfcomm_dlc_unlock(d);

		skb_queue_purge(&d->tx_queue);
		rfcomm_dlc_unlink(d);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rfcomm_dlc_बंद(काष्ठा rfcomm_dlc *d, पूर्णांक err)
अणु
	पूर्णांक r = 0;
	काष्ठा rfcomm_dlc *d_list;
	काष्ठा rfcomm_session *s, *s_list;

	BT_DBG("dlc %p state %ld dlci %d err %d", d, d->state, d->dlci, err);

	rfcomm_lock();

	s = d->session;
	अगर (!s)
		जाओ no_session;

	/* after रुकोing on the mutex check the session still exists
	 * then check the dlc still exists
	 */
	list_क्रम_each_entry(s_list, &session_list, list) अणु
		अगर (s_list == s) अणु
			list_क्रम_each_entry(d_list, &s->dlcs, list) अणु
				अगर (d_list == d) अणु
					r = __rfcomm_dlc_बंद(d, err);
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

no_session:
	rfcomm_unlock();
	वापस r;
पूर्ण

काष्ठा rfcomm_dlc *rfcomm_dlc_exists(bdaddr_t *src, bdaddr_t *dst, u8 channel)
अणु
	काष्ठा rfcomm_session *s;
	काष्ठा rfcomm_dlc *dlc = शून्य;
	u8 dlci;

	अगर (rfcomm_check_channel(channel))
		वापस ERR_PTR(-EINVAL);

	rfcomm_lock();
	s = rfcomm_session_get(src, dst);
	अगर (s) अणु
		dlci = __dlci(__session_dir(s), channel);
		dlc = rfcomm_dlc_get(s, dlci);
	पूर्ण
	rfcomm_unlock();
	वापस dlc;
पूर्ण

पूर्णांक rfcomm_dlc_send(काष्ठा rfcomm_dlc *d, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = skb->len;

	अगर (d->state != BT_CONNECTED)
		वापस -ENOTCONN;

	BT_DBG("dlc %p mtu %d len %d", d, d->mtu, len);

	अगर (len > d->mtu)
		वापस -EINVAL;

	rfcomm_make_uih(skb, d->addr);
	skb_queue_tail(&d->tx_queue, skb);

	अगर (!test_bit(RFCOMM_TX_THROTTLED, &d->flags))
		rfcomm_schedule();
	वापस len;
पूर्ण

व्योम rfcomm_dlc_send_noerror(काष्ठा rfcomm_dlc *d, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = skb->len;

	BT_DBG("dlc %p mtu %d len %d", d, d->mtu, len);

	rfcomm_make_uih(skb, d->addr);
	skb_queue_tail(&d->tx_queue, skb);

	अगर (d->state == BT_CONNECTED &&
	    !test_bit(RFCOMM_TX_THROTTLED, &d->flags))
		rfcomm_schedule();
पूर्ण

व्योम __rfcomm_dlc_throttle(काष्ठा rfcomm_dlc *d)
अणु
	BT_DBG("dlc %p state %ld", d, d->state);

	अगर (!d->cfc) अणु
		d->v24_sig |= RFCOMM_V24_FC;
		set_bit(RFCOMM_MSC_PENDING, &d->flags);
	पूर्ण
	rfcomm_schedule();
पूर्ण

व्योम __rfcomm_dlc_unthrottle(काष्ठा rfcomm_dlc *d)
अणु
	BT_DBG("dlc %p state %ld", d, d->state);

	अगर (!d->cfc) अणु
		d->v24_sig &= ~RFCOMM_V24_FC;
		set_bit(RFCOMM_MSC_PENDING, &d->flags);
	पूर्ण
	rfcomm_schedule();
पूर्ण

/*
   Set/get modem status functions use _local_ status i.e. what we report
   to the other side.
   Remote status is provided by dlc->modem_status() callback.
 */
पूर्णांक rfcomm_dlc_set_modem_status(काष्ठा rfcomm_dlc *d, u8 v24_sig)
अणु
	BT_DBG("dlc %p state %ld v24_sig 0x%x",
			d, d->state, v24_sig);

	अगर (test_bit(RFCOMM_RX_THROTTLED, &d->flags))
		v24_sig |= RFCOMM_V24_FC;
	अन्यथा
		v24_sig &= ~RFCOMM_V24_FC;

	d->v24_sig = v24_sig;

	अगर (!test_and_set_bit(RFCOMM_MSC_PENDING, &d->flags))
		rfcomm_schedule();

	वापस 0;
पूर्ण

पूर्णांक rfcomm_dlc_get_modem_status(काष्ठा rfcomm_dlc *d, u8 *v24_sig)
अणु
	BT_DBG("dlc %p state %ld v24_sig 0x%x",
			d, d->state, d->v24_sig);

	*v24_sig = d->v24_sig;
	वापस 0;
पूर्ण

/* ---- RFCOMM sessions ---- */
अटल काष्ठा rfcomm_session *rfcomm_session_add(काष्ठा socket *sock, पूर्णांक state)
अणु
	काष्ठा rfcomm_session *s = kzalloc(माप(*s), GFP_KERNEL);

	अगर (!s)
		वापस शून्य;

	BT_DBG("session %p sock %p", s, sock);

	समयr_setup(&s->समयr, rfcomm_session_समयout, 0);

	INIT_LIST_HEAD(&s->dlcs);
	s->state = state;
	s->sock  = sock;

	s->mtu = RFCOMM_DEFAULT_MTU;
	s->cfc = disable_cfc ? RFCOMM_CFC_DISABLED : RFCOMM_CFC_UNKNOWN;

	/* Do not increment module usage count क्रम listening sessions.
	 * Otherwise we won't be able to unload the module. */
	अगर (state != BT_LISTEN)
		अगर (!try_module_get(THIS_MODULE)) अणु
			kमुक्त(s);
			वापस शून्य;
		पूर्ण

	list_add(&s->list, &session_list);

	वापस s;
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_session_del(काष्ठा rfcomm_session *s)
अणु
	पूर्णांक state = s->state;

	BT_DBG("session %p state %ld", s, s->state);

	list_del(&s->list);

	rfcomm_session_clear_समयr(s);
	sock_release(s->sock);
	kमुक्त(s);

	अगर (state != BT_LISTEN)
		module_put(THIS_MODULE);

	वापस शून्य;
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_session_get(bdaddr_t *src, bdaddr_t *dst)
अणु
	काष्ठा rfcomm_session *s, *n;
	काष्ठा l2cap_chan *chan;
	list_क्रम_each_entry_safe(s, n, &session_list, list) अणु
		chan = l2cap_pi(s->sock->sk)->chan;

		अगर ((!bacmp(src, BDADDR_ANY) || !bacmp(&chan->src, src)) &&
		    !bacmp(&chan->dst, dst))
			वापस s;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_session_बंद(काष्ठा rfcomm_session *s,
						   पूर्णांक err)
अणु
	काष्ठा rfcomm_dlc *d, *n;

	s->state = BT_CLOSED;

	BT_DBG("session %p state %ld err %d", s, s->state, err);

	/* Close all dlcs */
	list_क्रम_each_entry_safe(d, n, &s->dlcs, list) अणु
		d->state = BT_CLOSED;
		__rfcomm_dlc_बंद(d, err);
	पूर्ण

	rfcomm_session_clear_समयr(s);
	वापस rfcomm_session_del(s);
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_session_create(bdaddr_t *src,
							bdaddr_t *dst,
							u8 sec_level,
							पूर्णांक *err)
अणु
	काष्ठा rfcomm_session *s = शून्य;
	काष्ठा sockaddr_l2 addr;
	काष्ठा socket *sock;
	काष्ठा sock *sk;

	BT_DBG("%pMR -> %pMR", src, dst);

	*err = rfcomm_l2sock_create(&sock);
	अगर (*err < 0)
		वापस शून्य;

	bacpy(&addr.l2_bdaddr, src);
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_psm    = 0;
	addr.l2_cid    = 0;
	addr.l2_bdaddr_type = BDADDR_BREDR;
	*err = kernel_bind(sock, (काष्ठा sockaddr *) &addr, माप(addr));
	अगर (*err < 0)
		जाओ failed;

	/* Set L2CAP options */
	sk = sock->sk;
	lock_sock(sk);
	/* Set MTU to 0 so L2CAP can स्वतः select the MTU */
	l2cap_pi(sk)->chan->imtu = 0;
	l2cap_pi(sk)->chan->sec_level = sec_level;
	अगर (l2cap_erपंचांग)
		l2cap_pi(sk)->chan->mode = L2CAP_MODE_ERTM;
	release_sock(sk);

	s = rfcomm_session_add(sock, BT_BOUND);
	अगर (!s) अणु
		*err = -ENOMEM;
		जाओ failed;
	पूर्ण

	s->initiator = 1;

	bacpy(&addr.l2_bdaddr, dst);
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_psm    = cpu_to_le16(L2CAP_PSM_RFCOMM);
	addr.l2_cid    = 0;
	addr.l2_bdaddr_type = BDADDR_BREDR;
	*err = kernel_connect(sock, (काष्ठा sockaddr *) &addr, माप(addr), O_NONBLOCK);
	अगर (*err == 0 || *err == -EINPROGRESS)
		वापस s;

	वापस rfcomm_session_del(s);

failed:
	sock_release(sock);
	वापस शून्य;
पूर्ण

व्योम rfcomm_session_getaddr(काष्ठा rfcomm_session *s, bdaddr_t *src, bdaddr_t *dst)
अणु
	काष्ठा l2cap_chan *chan = l2cap_pi(s->sock->sk)->chan;
	अगर (src)
		bacpy(src, &chan->src);
	अगर (dst)
		bacpy(dst, &chan->dst);
पूर्ण

/* ---- RFCOMM frame sending ---- */
अटल पूर्णांक rfcomm_send_frame(काष्ठा rfcomm_session *s, u8 *data, पूर्णांक len)
अणु
	काष्ठा kvec iv = अणु data, len पूर्ण;
	काष्ठा msghdr msg;

	BT_DBG("session %p len %d", s, len);

	स_रखो(&msg, 0, माप(msg));

	वापस kernel_sendmsg(s->sock, &msg, &iv, 1, len);
पूर्ण

अटल पूर्णांक rfcomm_send_cmd(काष्ठा rfcomm_session *s, काष्ठा rfcomm_cmd *cmd)
अणु
	BT_DBG("%p cmd %u", s, cmd->ctrl);

	वापस rfcomm_send_frame(s, (व्योम *) cmd, माप(*cmd));
पूर्ण

अटल पूर्णांक rfcomm_send_sabm(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	काष्ठा rfcomm_cmd cmd;

	BT_DBG("%p dlci %d", s, dlci);

	cmd.addr = __addr(s->initiator, dlci);
	cmd.ctrl = __ctrl(RFCOMM_SABM, 1);
	cmd.len  = __len8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	वापस rfcomm_send_cmd(s, &cmd);
पूर्ण

अटल पूर्णांक rfcomm_send_ua(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	काष्ठा rfcomm_cmd cmd;

	BT_DBG("%p dlci %d", s, dlci);

	cmd.addr = __addr(!s->initiator, dlci);
	cmd.ctrl = __ctrl(RFCOMM_UA, 1);
	cmd.len  = __len8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	वापस rfcomm_send_cmd(s, &cmd);
पूर्ण

अटल पूर्णांक rfcomm_send_disc(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	काष्ठा rfcomm_cmd cmd;

	BT_DBG("%p dlci %d", s, dlci);

	cmd.addr = __addr(s->initiator, dlci);
	cmd.ctrl = __ctrl(RFCOMM_DISC, 1);
	cmd.len  = __len8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	वापस rfcomm_send_cmd(s, &cmd);
पूर्ण

अटल पूर्णांक rfcomm_queue_disc(काष्ठा rfcomm_dlc *d)
अणु
	काष्ठा rfcomm_cmd *cmd;
	काष्ठा sk_buff *skb;

	BT_DBG("dlc %p dlci %d", d, d->dlci);

	skb = alloc_skb(माप(*cmd), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = __skb_put(skb, माप(*cmd));
	cmd->addr = d->addr;
	cmd->ctrl = __ctrl(RFCOMM_DISC, 1);
	cmd->len  = __len8(0);
	cmd->fcs  = __fcs2((u8 *) cmd);

	skb_queue_tail(&d->tx_queue, skb);
	rfcomm_schedule();
	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_send_dm(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	काष्ठा rfcomm_cmd cmd;

	BT_DBG("%p dlci %d", s, dlci);

	cmd.addr = __addr(!s->initiator, dlci);
	cmd.ctrl = __ctrl(RFCOMM_DM, 1);
	cmd.len  = __len8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	वापस rfcomm_send_cmd(s, &cmd);
पूर्ण

अटल पूर्णांक rfcomm_send_nsc(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 type)
अणु
	काष्ठा rfcomm_hdr *hdr;
	काष्ठा rfcomm_mcc *mcc;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d type %d", s, cr, type);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(माप(*mcc) + 1);

	mcc = (व्योम *) ptr; ptr += माप(*mcc);
	mcc->type = __mcc_type(0, RFCOMM_NSC);
	mcc->len  = __len8(1);

	/* Type that we didn't like */
	*ptr = __mcc_type(cr, type); ptr++;

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

अटल पूर्णांक rfcomm_send_pn(काष्ठा rfcomm_session *s, पूर्णांक cr, काष्ठा rfcomm_dlc *d)
अणु
	काष्ठा rfcomm_hdr *hdr;
	काष्ठा rfcomm_mcc *mcc;
	काष्ठा rfcomm_pn  *pn;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d dlci %d mtu %d", s, cr, d->dlci, d->mtu);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(माप(*mcc) + माप(*pn));

	mcc = (व्योम *) ptr; ptr += माप(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_PN);
	mcc->len  = __len8(माप(*pn));

	pn = (व्योम *) ptr; ptr += माप(*pn);
	pn->dlci        = d->dlci;
	pn->priority    = d->priority;
	pn->ack_समयr   = 0;
	pn->max_retrans = 0;

	अगर (s->cfc) अणु
		pn->flow_ctrl = cr ? 0xf0 : 0xe0;
		pn->credits = RFCOMM_DEFAULT_CREDITS;
	पूर्ण अन्यथा अणु
		pn->flow_ctrl = 0;
		pn->credits   = 0;
	पूर्ण

	अगर (cr && channel_mtu >= 0)
		pn->mtu = cpu_to_le16(channel_mtu);
	अन्यथा
		pn->mtu = cpu_to_le16(d->mtu);

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

पूर्णांक rfcomm_send_rpn(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 dlci,
			u8 bit_rate, u8 data_bits, u8 stop_bits,
			u8 parity, u8 flow_ctrl_settings,
			u8 xon_अक्षर, u8 xoff_अक्षर, u16 param_mask)
अणु
	काष्ठा rfcomm_hdr *hdr;
	काष्ठा rfcomm_mcc *mcc;
	काष्ठा rfcomm_rpn *rpn;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d dlci %d bit_r 0x%x data_b 0x%x stop_b 0x%x parity 0x%x"
			" flwc_s 0x%x xon_c 0x%x xoff_c 0x%x p_mask 0x%x",
		s, cr, dlci, bit_rate, data_bits, stop_bits, parity,
		flow_ctrl_settings, xon_अक्षर, xoff_अक्षर, param_mask);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(माप(*mcc) + माप(*rpn));

	mcc = (व्योम *) ptr; ptr += माप(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_RPN);
	mcc->len  = __len8(माप(*rpn));

	rpn = (व्योम *) ptr; ptr += माप(*rpn);
	rpn->dlci          = __addr(1, dlci);
	rpn->bit_rate      = bit_rate;
	rpn->line_settings = __rpn_line_settings(data_bits, stop_bits, parity);
	rpn->flow_ctrl     = flow_ctrl_settings;
	rpn->xon_अक्षर      = xon_अक्षर;
	rpn->xoff_अक्षर     = xoff_अक्षर;
	rpn->param_mask    = cpu_to_le16(param_mask);

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

अटल पूर्णांक rfcomm_send_rls(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 dlci, u8 status)
अणु
	काष्ठा rfcomm_hdr *hdr;
	काष्ठा rfcomm_mcc *mcc;
	काष्ठा rfcomm_rls *rls;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d status 0x%x", s, cr, status);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(माप(*mcc) + माप(*rls));

	mcc = (व्योम *) ptr; ptr += माप(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_RLS);
	mcc->len  = __len8(माप(*rls));

	rls = (व्योम *) ptr; ptr += माप(*rls);
	rls->dlci   = __addr(1, dlci);
	rls->status = status;

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

अटल पूर्णांक rfcomm_send_msc(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 dlci, u8 v24_sig)
अणु
	काष्ठा rfcomm_hdr *hdr;
	काष्ठा rfcomm_mcc *mcc;
	काष्ठा rfcomm_msc *msc;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d v24 0x%x", s, cr, v24_sig);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(माप(*mcc) + माप(*msc));

	mcc = (व्योम *) ptr; ptr += माप(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_MSC);
	mcc->len  = __len8(माप(*msc));

	msc = (व्योम *) ptr; ptr += माप(*msc);
	msc->dlci    = __addr(1, dlci);
	msc->v24_sig = v24_sig | 0x01;

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

अटल पूर्णांक rfcomm_send_fcoff(काष्ठा rfcomm_session *s, पूर्णांक cr)
अणु
	काष्ठा rfcomm_hdr *hdr;
	काष्ठा rfcomm_mcc *mcc;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d", s, cr);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(माप(*mcc));

	mcc = (व्योम *) ptr; ptr += माप(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_FCOFF);
	mcc->len  = __len8(0);

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

अटल पूर्णांक rfcomm_send_fcon(काष्ठा rfcomm_session *s, पूर्णांक cr)
अणु
	काष्ठा rfcomm_hdr *hdr;
	काष्ठा rfcomm_mcc *mcc;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d", s, cr);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(माप(*mcc));

	mcc = (व्योम *) ptr; ptr += माप(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_FCON);
	mcc->len  = __len8(0);

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

अटल पूर्णांक rfcomm_send_test(काष्ठा rfcomm_session *s, पूर्णांक cr, u8 *pattern, पूर्णांक len)
अणु
	काष्ठा socket *sock = s->sock;
	काष्ठा kvec iv[3];
	काष्ठा msghdr msg;
	अचिन्हित अक्षर hdr[5], crc[1];

	अगर (len > 125)
		वापस -EINVAL;

	BT_DBG("%p cr %d", s, cr);

	hdr[0] = __addr(s->initiator, 0);
	hdr[1] = __ctrl(RFCOMM_UIH, 0);
	hdr[2] = 0x01 | ((len + 2) << 1);
	hdr[3] = 0x01 | ((cr & 0x01) << 1) | (RFCOMM_TEST << 2);
	hdr[4] = 0x01 | (len << 1);

	crc[0] = __fcs(hdr);

	iv[0].iov_base = hdr;
	iv[0].iov_len  = 5;
	iv[1].iov_base = pattern;
	iv[1].iov_len  = len;
	iv[2].iov_base = crc;
	iv[2].iov_len  = 1;

	स_रखो(&msg, 0, माप(msg));

	वापस kernel_sendmsg(sock, &msg, iv, 3, 6 + len);
पूर्ण

अटल पूर्णांक rfcomm_send_credits(काष्ठा rfcomm_session *s, u8 addr, u8 credits)
अणु
	काष्ठा rfcomm_hdr *hdr;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p addr %d credits %d", s, addr, credits);

	hdr = (व्योम *) ptr; ptr += माप(*hdr);
	hdr->addr = addr;
	hdr->ctrl = __ctrl(RFCOMM_UIH, 1);
	hdr->len  = __len8(0);

	*ptr = credits; ptr++;

	*ptr = __fcs(buf); ptr++;

	वापस rfcomm_send_frame(s, buf, ptr - buf);
पूर्ण

अटल व्योम rfcomm_make_uih(काष्ठा sk_buff *skb, u8 addr)
अणु
	काष्ठा rfcomm_hdr *hdr;
	पूर्णांक len = skb->len;
	u8 *crc;

	अगर (len > 127) अणु
		hdr = skb_push(skb, 4);
		put_unaligned(cpu_to_le16(__len16(len)), (__le16 *) &hdr->len);
	पूर्ण अन्यथा अणु
		hdr = skb_push(skb, 3);
		hdr->len = __len8(len);
	पूर्ण
	hdr->addr = addr;
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);

	crc = skb_put(skb, 1);
	*crc = __fcs((व्योम *) hdr);
पूर्ण

/* ---- RFCOMM frame reception ---- */
अटल काष्ठा rfcomm_session *rfcomm_recv_ua(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	अगर (dlci) अणु
		/* Data channel */
		काष्ठा rfcomm_dlc *d = rfcomm_dlc_get(s, dlci);
		अगर (!d) अणु
			rfcomm_send_dm(s, dlci);
			वापस s;
		पूर्ण

		चयन (d->state) अणु
		हाल BT_CONNECT:
			rfcomm_dlc_clear_समयr(d);

			rfcomm_dlc_lock(d);
			d->state = BT_CONNECTED;
			d->state_change(d, 0);
			rfcomm_dlc_unlock(d);

			rfcomm_send_msc(s, 1, dlci, d->v24_sig);
			अवरोध;

		हाल BT_DISCONN:
			d->state = BT_CLOSED;
			__rfcomm_dlc_बंद(d, 0);

			अगर (list_empty(&s->dlcs)) अणु
				s->state = BT_DISCONN;
				rfcomm_send_disc(s, 0);
				rfcomm_session_clear_समयr(s);
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Control channel */
		चयन (s->state) अणु
		हाल BT_CONNECT:
			s->state = BT_CONNECTED;
			rfcomm_process_connect(s);
			अवरोध;

		हाल BT_DISCONN:
			s = rfcomm_session_बंद(s, ECONNRESET);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस s;
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_recv_dm(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	पूर्णांक err = 0;

	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	अगर (dlci) अणु
		/* Data DLC */
		काष्ठा rfcomm_dlc *d = rfcomm_dlc_get(s, dlci);
		अगर (d) अणु
			अगर (d->state == BT_CONNECT || d->state == BT_CONFIG)
				err = ECONNREFUSED;
			अन्यथा
				err = ECONNRESET;

			d->state = BT_CLOSED;
			__rfcomm_dlc_बंद(d, err);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (s->state == BT_CONNECT)
			err = ECONNREFUSED;
		अन्यथा
			err = ECONNRESET;

		s = rfcomm_session_बंद(s, err);
	पूर्ण
	वापस s;
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_recv_disc(काष्ठा rfcomm_session *s,
					       u8 dlci)
अणु
	पूर्णांक err = 0;

	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	अगर (dlci) अणु
		काष्ठा rfcomm_dlc *d = rfcomm_dlc_get(s, dlci);
		अगर (d) अणु
			rfcomm_send_ua(s, dlci);

			अगर (d->state == BT_CONNECT || d->state == BT_CONFIG)
				err = ECONNREFUSED;
			अन्यथा
				err = ECONNRESET;

			d->state = BT_CLOSED;
			__rfcomm_dlc_बंद(d, err);
		पूर्ण अन्यथा
			rfcomm_send_dm(s, dlci);

	पूर्ण अन्यथा अणु
		rfcomm_send_ua(s, 0);

		अगर (s->state == BT_CONNECT)
			err = ECONNREFUSED;
		अन्यथा
			err = ECONNRESET;

		s = rfcomm_session_बंद(s, err);
	पूर्ण
	वापस s;
पूर्ण

व्योम rfcomm_dlc_accept(काष्ठा rfcomm_dlc *d)
अणु
	काष्ठा sock *sk = d->session->sock->sk;
	काष्ठा l2cap_conn *conn = l2cap_pi(sk)->chan->conn;

	BT_DBG("dlc %p", d);

	rfcomm_send_ua(d->session, d->dlci);

	rfcomm_dlc_clear_समयr(d);

	rfcomm_dlc_lock(d);
	d->state = BT_CONNECTED;
	d->state_change(d, 0);
	rfcomm_dlc_unlock(d);

	अगर (d->role_चयन)
		hci_conn_चयन_role(conn->hcon, 0x00);

	rfcomm_send_msc(d->session, 1, d->dlci, d->v24_sig);
पूर्ण

अटल व्योम rfcomm_check_accept(काष्ठा rfcomm_dlc *d)
अणु
	अगर (rfcomm_check_security(d)) अणु
		अगर (d->defer_setup) अणु
			set_bit(RFCOMM_DEFER_SETUP, &d->flags);
			rfcomm_dlc_set_समयr(d, RFCOMM_AUTH_TIMEOUT);

			rfcomm_dlc_lock(d);
			d->state = BT_CONNECT2;
			d->state_change(d, 0);
			rfcomm_dlc_unlock(d);
		पूर्ण अन्यथा
			rfcomm_dlc_accept(d);
	पूर्ण अन्यथा अणु
		set_bit(RFCOMM_AUTH_PENDING, &d->flags);
		rfcomm_dlc_set_समयr(d, RFCOMM_AUTH_TIMEOUT);
	पूर्ण
पूर्ण

अटल पूर्णांक rfcomm_recv_sabm(काष्ठा rfcomm_session *s, u8 dlci)
अणु
	काष्ठा rfcomm_dlc *d;
	u8 channel;

	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	अगर (!dlci) अणु
		rfcomm_send_ua(s, 0);

		अगर (s->state == BT_OPEN) अणु
			s->state = BT_CONNECTED;
			rfcomm_process_connect(s);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Check अगर DLC exists */
	d = rfcomm_dlc_get(s, dlci);
	अगर (d) अणु
		अगर (d->state == BT_OPEN) अणु
			/* DLC was previously खोलोed by PN request */
			rfcomm_check_accept(d);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Notअगरy socket layer about incoming connection */
	channel = __srv_channel(dlci);
	अगर (rfcomm_connect_ind(s, channel, &d)) अणु
		d->dlci = dlci;
		d->addr = __addr(s->initiator, dlci);
		rfcomm_dlc_link(s, d);

		rfcomm_check_accept(d);
	पूर्ण अन्यथा अणु
		rfcomm_send_dm(s, dlci);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_apply_pn(काष्ठा rfcomm_dlc *d, पूर्णांक cr, काष्ठा rfcomm_pn *pn)
अणु
	काष्ठा rfcomm_session *s = d->session;

	BT_DBG("dlc %p state %ld dlci %d mtu %d fc 0x%x credits %d",
			d, d->state, d->dlci, pn->mtu, pn->flow_ctrl, pn->credits);

	अगर ((pn->flow_ctrl == 0xf0 && s->cfc != RFCOMM_CFC_DISABLED) ||
						pn->flow_ctrl == 0xe0) अणु
		d->cfc = RFCOMM_CFC_ENABLED;
		d->tx_credits = pn->credits;
	पूर्ण अन्यथा अणु
		d->cfc = RFCOMM_CFC_DISABLED;
		set_bit(RFCOMM_TX_THROTTLED, &d->flags);
	पूर्ण

	अगर (s->cfc == RFCOMM_CFC_UNKNOWN)
		s->cfc = d->cfc;

	d->priority = pn->priority;

	d->mtu = __le16_to_cpu(pn->mtu);

	अगर (cr && d->mtu > s->mtu)
		d->mtu = s->mtu;

	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_recv_pn(काष्ठा rfcomm_session *s, पूर्णांक cr, काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_pn *pn = (व्योम *) skb->data;
	काष्ठा rfcomm_dlc *d;
	u8 dlci = pn->dlci;

	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	अगर (!dlci)
		वापस 0;

	d = rfcomm_dlc_get(s, dlci);
	अगर (d) अणु
		अगर (cr) अणु
			/* PN request */
			rfcomm_apply_pn(d, cr, pn);
			rfcomm_send_pn(s, 0, d);
		पूर्ण अन्यथा अणु
			/* PN response */
			चयन (d->state) अणु
			हाल BT_CONFIG:
				rfcomm_apply_pn(d, cr, pn);

				d->state = BT_CONNECT;
				rfcomm_send_sabm(s, d->dlci);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 channel = __srv_channel(dlci);

		अगर (!cr)
			वापस 0;

		/* PN request क्रम non existing DLC.
		 * Assume incoming connection. */
		अगर (rfcomm_connect_ind(s, channel, &d)) अणु
			d->dlci = dlci;
			d->addr = __addr(s->initiator, dlci);
			rfcomm_dlc_link(s, d);

			rfcomm_apply_pn(d, cr, pn);

			d->state = BT_OPEN;
			rfcomm_send_pn(s, 0, d);
		पूर्ण अन्यथा अणु
			rfcomm_send_dm(s, dlci);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_recv_rpn(काष्ठा rfcomm_session *s, पूर्णांक cr, पूर्णांक len, काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_rpn *rpn = (व्योम *) skb->data;
	u8 dlci = __get_dlci(rpn->dlci);

	u8 bit_rate  = 0;
	u8 data_bits = 0;
	u8 stop_bits = 0;
	u8 parity    = 0;
	u8 flow_ctrl = 0;
	u8 xon_अक्षर  = 0;
	u8 xoff_अक्षर = 0;
	u16 rpn_mask = RFCOMM_RPN_PM_ALL;

	BT_DBG("dlci %d cr %d len 0x%x bitr 0x%x line 0x%x flow 0x%x xonc 0x%x xoffc 0x%x pm 0x%x",
		dlci, cr, len, rpn->bit_rate, rpn->line_settings, rpn->flow_ctrl,
		rpn->xon_अक्षर, rpn->xoff_अक्षर, rpn->param_mask);

	अगर (!cr)
		वापस 0;

	अगर (len == 1) अणु
		/* This is a request, वापस शेष (according to ETSI TS 07.10) settings */
		bit_rate  = RFCOMM_RPN_BR_9600;
		data_bits = RFCOMM_RPN_DATA_8;
		stop_bits = RFCOMM_RPN_STOP_1;
		parity    = RFCOMM_RPN_PARITY_NONE;
		flow_ctrl = RFCOMM_RPN_FLOW_NONE;
		xon_अक्षर  = RFCOMM_RPN_XON_CHAR;
		xoff_अक्षर = RFCOMM_RPN_XOFF_CHAR;
		जाओ rpn_out;
	पूर्ण

	/* Check क्रम sane values, ignore/accept bit_rate, 8 bits, 1 stop bit,
	 * no parity, no flow control lines, normal XON/XOFF अक्षरs */

	अगर (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_BITRATE)) अणु
		bit_rate = rpn->bit_rate;
		अगर (bit_rate > RFCOMM_RPN_BR_230400) अणु
			BT_DBG("RPN bit rate mismatch 0x%x", bit_rate);
			bit_rate = RFCOMM_RPN_BR_9600;
			rpn_mask ^= RFCOMM_RPN_PM_BITRATE;
		पूर्ण
	पूर्ण

	अगर (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_DATA)) अणु
		data_bits = __get_rpn_data_bits(rpn->line_settings);
		अगर (data_bits != RFCOMM_RPN_DATA_8) अणु
			BT_DBG("RPN data bits mismatch 0x%x", data_bits);
			data_bits = RFCOMM_RPN_DATA_8;
			rpn_mask ^= RFCOMM_RPN_PM_DATA;
		पूर्ण
	पूर्ण

	अगर (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_STOP)) अणु
		stop_bits = __get_rpn_stop_bits(rpn->line_settings);
		अगर (stop_bits != RFCOMM_RPN_STOP_1) अणु
			BT_DBG("RPN stop bits mismatch 0x%x", stop_bits);
			stop_bits = RFCOMM_RPN_STOP_1;
			rpn_mask ^= RFCOMM_RPN_PM_STOP;
		पूर्ण
	पूर्ण

	अगर (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_PARITY)) अणु
		parity = __get_rpn_parity(rpn->line_settings);
		अगर (parity != RFCOMM_RPN_PARITY_NONE) अणु
			BT_DBG("RPN parity mismatch 0x%x", parity);
			parity = RFCOMM_RPN_PARITY_NONE;
			rpn_mask ^= RFCOMM_RPN_PM_PARITY;
		पूर्ण
	पूर्ण

	अगर (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_FLOW)) अणु
		flow_ctrl = rpn->flow_ctrl;
		अगर (flow_ctrl != RFCOMM_RPN_FLOW_NONE) अणु
			BT_DBG("RPN flow ctrl mismatch 0x%x", flow_ctrl);
			flow_ctrl = RFCOMM_RPN_FLOW_NONE;
			rpn_mask ^= RFCOMM_RPN_PM_FLOW;
		पूर्ण
	पूर्ण

	अगर (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_XON)) अणु
		xon_अक्षर = rpn->xon_अक्षर;
		अगर (xon_अक्षर != RFCOMM_RPN_XON_CHAR) अणु
			BT_DBG("RPN XON char mismatch 0x%x", xon_अक्षर);
			xon_अक्षर = RFCOMM_RPN_XON_CHAR;
			rpn_mask ^= RFCOMM_RPN_PM_XON;
		पूर्ण
	पूर्ण

	अगर (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_XOFF)) अणु
		xoff_अक्षर = rpn->xoff_अक्षर;
		अगर (xoff_अक्षर != RFCOMM_RPN_XOFF_CHAR) अणु
			BT_DBG("RPN XOFF char mismatch 0x%x", xoff_अक्षर);
			xoff_अक्षर = RFCOMM_RPN_XOFF_CHAR;
			rpn_mask ^= RFCOMM_RPN_PM_XOFF;
		पूर्ण
	पूर्ण

rpn_out:
	rfcomm_send_rpn(s, 0, dlci, bit_rate, data_bits, stop_bits,
			parity, flow_ctrl, xon_अक्षर, xoff_अक्षर, rpn_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_recv_rls(काष्ठा rfcomm_session *s, पूर्णांक cr, काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_rls *rls = (व्योम *) skb->data;
	u8 dlci = __get_dlci(rls->dlci);

	BT_DBG("dlci %d cr %d status 0x%x", dlci, cr, rls->status);

	अगर (!cr)
		वापस 0;

	/* We should probably करो something with this inक्रमmation here. But
	 * क्रम now it's sufficient just to reply -- Bluetooth 1.1 says it's
	 * mandatory to recognise and respond to RLS */

	rfcomm_send_rls(s, 0, dlci, rls->status);

	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_recv_msc(काष्ठा rfcomm_session *s, पूर्णांक cr, काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_msc *msc = (व्योम *) skb->data;
	काष्ठा rfcomm_dlc *d;
	u8 dlci = __get_dlci(msc->dlci);

	BT_DBG("dlci %d cr %d v24 0x%x", dlci, cr, msc->v24_sig);

	d = rfcomm_dlc_get(s, dlci);
	अगर (!d)
		वापस 0;

	अगर (cr) अणु
		अगर (msc->v24_sig & RFCOMM_V24_FC && !d->cfc)
			set_bit(RFCOMM_TX_THROTTLED, &d->flags);
		अन्यथा
			clear_bit(RFCOMM_TX_THROTTLED, &d->flags);

		rfcomm_dlc_lock(d);

		d->remote_v24_sig = msc->v24_sig;

		अगर (d->modem_status)
			d->modem_status(d, msc->v24_sig);

		rfcomm_dlc_unlock(d);

		rfcomm_send_msc(s, 0, dlci, msc->v24_sig);

		d->mscex |= RFCOMM_MSCEX_RX;
	पूर्ण अन्यथा
		d->mscex |= RFCOMM_MSCEX_TX;

	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_recv_mcc(काष्ठा rfcomm_session *s, काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_mcc *mcc = (व्योम *) skb->data;
	u8 type, cr, len;

	cr   = __test_cr(mcc->type);
	type = __get_mcc_type(mcc->type);
	len  = __get_mcc_len(mcc->len);

	BT_DBG("%p type 0x%x cr %d", s, type, cr);

	skb_pull(skb, 2);

	चयन (type) अणु
	हाल RFCOMM_PN:
		rfcomm_recv_pn(s, cr, skb);
		अवरोध;

	हाल RFCOMM_RPN:
		rfcomm_recv_rpn(s, cr, len, skb);
		अवरोध;

	हाल RFCOMM_RLS:
		rfcomm_recv_rls(s, cr, skb);
		अवरोध;

	हाल RFCOMM_MSC:
		rfcomm_recv_msc(s, cr, skb);
		अवरोध;

	हाल RFCOMM_FCOFF:
		अगर (cr) अणु
			set_bit(RFCOMM_TX_THROTTLED, &s->flags);
			rfcomm_send_fcoff(s, 0);
		पूर्ण
		अवरोध;

	हाल RFCOMM_FCON:
		अगर (cr) अणु
			clear_bit(RFCOMM_TX_THROTTLED, &s->flags);
			rfcomm_send_fcon(s, 0);
		पूर्ण
		अवरोध;

	हाल RFCOMM_TEST:
		अगर (cr)
			rfcomm_send_test(s, 0, skb->data, skb->len);
		अवरोध;

	हाल RFCOMM_NSC:
		अवरोध;

	शेष:
		BT_ERR("Unknown control type 0x%02x", type);
		rfcomm_send_nsc(s, cr, type);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_recv_data(काष्ठा rfcomm_session *s, u8 dlci, पूर्णांक pf, काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_dlc *d;

	BT_DBG("session %p state %ld dlci %d pf %d", s, s->state, dlci, pf);

	d = rfcomm_dlc_get(s, dlci);
	अगर (!d) अणु
		rfcomm_send_dm(s, dlci);
		जाओ drop;
	पूर्ण

	अगर (pf && d->cfc) अणु
		u8 credits = *(u8 *) skb->data; skb_pull(skb, 1);

		d->tx_credits += credits;
		अगर (d->tx_credits)
			clear_bit(RFCOMM_TX_THROTTLED, &d->flags);
	पूर्ण

	अगर (skb->len && d->state == BT_CONNECTED) अणु
		rfcomm_dlc_lock(d);
		d->rx_credits--;
		d->data_पढ़ोy(d, skb);
		rfcomm_dlc_unlock(d);
		वापस 0;
	पूर्ण

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_recv_frame(काष्ठा rfcomm_session *s,
						काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_hdr *hdr = (व्योम *) skb->data;
	u8 type, dlci, fcs;

	अगर (!s) अणु
		/* no session, so मुक्त socket data */
		kमुक्त_skb(skb);
		वापस s;
	पूर्ण

	dlci = __get_dlci(hdr->addr);
	type = __get_type(hdr->ctrl);

	/* Trim FCS */
	skb->len--; skb->tail--;
	fcs = *(u8 *)skb_tail_poपूर्णांकer(skb);

	अगर (__check_fcs(skb->data, type, fcs)) अणु
		BT_ERR("bad checksum in packet");
		kमुक्त_skb(skb);
		वापस s;
	पूर्ण

	अगर (__test_ea(hdr->len))
		skb_pull(skb, 3);
	अन्यथा
		skb_pull(skb, 4);

	चयन (type) अणु
	हाल RFCOMM_SABM:
		अगर (__test_pf(hdr->ctrl))
			rfcomm_recv_sabm(s, dlci);
		अवरोध;

	हाल RFCOMM_DISC:
		अगर (__test_pf(hdr->ctrl))
			s = rfcomm_recv_disc(s, dlci);
		अवरोध;

	हाल RFCOMM_UA:
		अगर (__test_pf(hdr->ctrl))
			s = rfcomm_recv_ua(s, dlci);
		अवरोध;

	हाल RFCOMM_DM:
		s = rfcomm_recv_dm(s, dlci);
		अवरोध;

	हाल RFCOMM_UIH:
		अगर (dlci) अणु
			rfcomm_recv_data(s, dlci, __test_pf(hdr->ctrl), skb);
			वापस s;
		पूर्ण
		rfcomm_recv_mcc(s, skb);
		अवरोध;

	शेष:
		BT_ERR("Unknown packet type 0x%02x", type);
		अवरोध;
	पूर्ण
	kमुक्त_skb(skb);
	वापस s;
पूर्ण

/* ---- Connection and data processing ---- */

अटल व्योम rfcomm_process_connect(काष्ठा rfcomm_session *s)
अणु
	काष्ठा rfcomm_dlc *d, *n;

	BT_DBG("session %p state %ld", s, s->state);

	list_क्रम_each_entry_safe(d, n, &s->dlcs, list) अणु
		अगर (d->state == BT_CONFIG) अणु
			d->mtu = s->mtu;
			अगर (rfcomm_check_security(d)) अणु
				rfcomm_send_pn(s, 1, d);
			पूर्ण अन्यथा अणु
				set_bit(RFCOMM_AUTH_PENDING, &d->flags);
				rfcomm_dlc_set_समयr(d, RFCOMM_AUTH_TIMEOUT);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Send data queued क्रम the DLC.
 * Return number of frames left in the queue.
 */
अटल पूर्णांक rfcomm_process_tx(काष्ठा rfcomm_dlc *d)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	BT_DBG("dlc %p state %ld cfc %d rx_credits %d tx_credits %d",
			d, d->state, d->cfc, d->rx_credits, d->tx_credits);

	/* Send pending MSC */
	अगर (test_and_clear_bit(RFCOMM_MSC_PENDING, &d->flags))
		rfcomm_send_msc(d->session, 1, d->dlci, d->v24_sig);

	अगर (d->cfc) अणु
		/* CFC enabled.
		 * Give them some credits */
		अगर (!test_bit(RFCOMM_RX_THROTTLED, &d->flags) &&
				d->rx_credits <= (d->cfc >> 2)) अणु
			rfcomm_send_credits(d->session, d->addr, d->cfc - d->rx_credits);
			d->rx_credits = d->cfc;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* CFC disabled.
		 * Give ourselves some credits */
		d->tx_credits = 5;
	पूर्ण

	अगर (test_bit(RFCOMM_TX_THROTTLED, &d->flags))
		वापस skb_queue_len(&d->tx_queue);

	जबतक (d->tx_credits && (skb = skb_dequeue(&d->tx_queue))) अणु
		err = rfcomm_send_frame(d->session, skb->data, skb->len);
		अगर (err < 0) अणु
			skb_queue_head(&d->tx_queue, skb);
			अवरोध;
		पूर्ण
		kमुक्त_skb(skb);
		d->tx_credits--;
	पूर्ण

	अगर (d->cfc && !d->tx_credits) अणु
		/* We're out of TX credits.
		 * Set TX_THROTTLED flag to aव्योम unnesary wakeups by dlc_send. */
		set_bit(RFCOMM_TX_THROTTLED, &d->flags);
	पूर्ण

	वापस skb_queue_len(&d->tx_queue);
पूर्ण

अटल व्योम rfcomm_process_dlcs(काष्ठा rfcomm_session *s)
अणु
	काष्ठा rfcomm_dlc *d, *n;

	BT_DBG("session %p state %ld", s, s->state);

	list_क्रम_each_entry_safe(d, n, &s->dlcs, list) अणु
		अगर (test_bit(RFCOMM_TIMED_OUT, &d->flags)) अणु
			__rfcomm_dlc_बंद(d, ETIMEDOUT);
			जारी;
		पूर्ण

		अगर (test_bit(RFCOMM_ENC_DROP, &d->flags)) अणु
			__rfcomm_dlc_बंद(d, ECONNREFUSED);
			जारी;
		पूर्ण

		अगर (test_and_clear_bit(RFCOMM_AUTH_ACCEPT, &d->flags)) अणु
			rfcomm_dlc_clear_समयr(d);
			अगर (d->out) अणु
				rfcomm_send_pn(s, 1, d);
				rfcomm_dlc_set_समयr(d, RFCOMM_CONN_TIMEOUT);
			पूर्ण अन्यथा अणु
				अगर (d->defer_setup) अणु
					set_bit(RFCOMM_DEFER_SETUP, &d->flags);
					rfcomm_dlc_set_समयr(d, RFCOMM_AUTH_TIMEOUT);

					rfcomm_dlc_lock(d);
					d->state = BT_CONNECT2;
					d->state_change(d, 0);
					rfcomm_dlc_unlock(d);
				पूर्ण अन्यथा
					rfcomm_dlc_accept(d);
			पूर्ण
			जारी;
		पूर्ण अन्यथा अगर (test_and_clear_bit(RFCOMM_AUTH_REJECT, &d->flags)) अणु
			rfcomm_dlc_clear_समयr(d);
			अगर (!d->out)
				rfcomm_send_dm(s, d->dlci);
			अन्यथा
				d->state = BT_CLOSED;
			__rfcomm_dlc_बंद(d, ECONNREFUSED);
			जारी;
		पूर्ण

		अगर (test_bit(RFCOMM_SEC_PENDING, &d->flags))
			जारी;

		अगर (test_bit(RFCOMM_TX_THROTTLED, &s->flags))
			जारी;

		अगर ((d->state == BT_CONNECTED || d->state == BT_DISCONN) &&
						d->mscex == RFCOMM_MSCEX_OK)
			rfcomm_process_tx(d);
	पूर्ण
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_process_rx(काष्ठा rfcomm_session *s)
अणु
	काष्ठा socket *sock = s->sock;
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;

	BT_DBG("session %p state %ld qlen %d", s, s->state, skb_queue_len(&sk->sk_receive_queue));

	/* Get data directly from socket receive queue without copying it. */
	जबतक ((skb = skb_dequeue(&sk->sk_receive_queue))) अणु
		skb_orphan(skb);
		अगर (!skb_linearize(skb)) अणु
			s = rfcomm_recv_frame(s, skb);
			अगर (!s)
				अवरोध;
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	अगर (s && (sk->sk_state == BT_CLOSED))
		s = rfcomm_session_बंद(s, sk->sk_err);

	वापस s;
पूर्ण

अटल व्योम rfcomm_accept_connection(काष्ठा rfcomm_session *s)
अणु
	काष्ठा socket *sock = s->sock, *nsock;
	पूर्णांक err;

	/* Fast check क्रम a new connection.
	 * Aव्योमs unnesesary socket allocations. */
	अगर (list_empty(&bt_sk(sock->sk)->accept_q))
		वापस;

	BT_DBG("session %p", s);

	err = kernel_accept(sock, &nsock, O_NONBLOCK);
	अगर (err < 0)
		वापस;

	/* Set our callbacks */
	nsock->sk->sk_data_पढ़ोy   = rfcomm_l2data_पढ़ोy;
	nsock->sk->sk_state_change = rfcomm_l2state_change;

	s = rfcomm_session_add(nsock, BT_OPEN);
	अगर (s) अणु
		/* We should adjust MTU on incoming sessions.
		 * L2CAP MTU minus UIH header and FCS. */
		s->mtu = min(l2cap_pi(nsock->sk)->chan->omtu,
				l2cap_pi(nsock->sk)->chan->imtu) - 5;

		rfcomm_schedule();
	पूर्ण अन्यथा
		sock_release(nsock);
पूर्ण

अटल काष्ठा rfcomm_session *rfcomm_check_connection(काष्ठा rfcomm_session *s)
अणु
	काष्ठा sock *sk = s->sock->sk;

	BT_DBG("%p state %ld", s, s->state);

	चयन (sk->sk_state) अणु
	हाल BT_CONNECTED:
		s->state = BT_CONNECT;

		/* We can adjust MTU on outgoing sessions.
		 * L2CAP MTU minus UIH header and FCS. */
		s->mtu = min(l2cap_pi(sk)->chan->omtu, l2cap_pi(sk)->chan->imtu) - 5;

		rfcomm_send_sabm(s, 0);
		अवरोध;

	हाल BT_CLOSED:
		s = rfcomm_session_बंद(s, sk->sk_err);
		अवरोध;
	पूर्ण
	वापस s;
पूर्ण

अटल व्योम rfcomm_process_sessions(व्योम)
अणु
	काष्ठा rfcomm_session *s, *n;

	rfcomm_lock();

	list_क्रम_each_entry_safe(s, n, &session_list, list) अणु
		अगर (test_and_clear_bit(RFCOMM_TIMED_OUT, &s->flags)) अणु
			s->state = BT_DISCONN;
			rfcomm_send_disc(s, 0);
			जारी;
		पूर्ण

		चयन (s->state) अणु
		हाल BT_LISTEN:
			rfcomm_accept_connection(s);
			जारी;

		हाल BT_BOUND:
			s = rfcomm_check_connection(s);
			अवरोध;

		शेष:
			s = rfcomm_process_rx(s);
			अवरोध;
		पूर्ण

		अगर (s)
			rfcomm_process_dlcs(s);
	पूर्ण

	rfcomm_unlock();
पूर्ण

अटल पूर्णांक rfcomm_add_listener(bdaddr_t *ba)
अणु
	काष्ठा sockaddr_l2 addr;
	काष्ठा socket *sock;
	काष्ठा sock *sk;
	काष्ठा rfcomm_session *s;
	पूर्णांक    err = 0;

	/* Create socket */
	err = rfcomm_l2sock_create(&sock);
	अगर (err < 0) अणु
		BT_ERR("Create socket failed %d", err);
		वापस err;
	पूर्ण

	/* Bind socket */
	bacpy(&addr.l2_bdaddr, ba);
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_psm    = cpu_to_le16(L2CAP_PSM_RFCOMM);
	addr.l2_cid    = 0;
	addr.l2_bdaddr_type = BDADDR_BREDR;
	err = kernel_bind(sock, (काष्ठा sockaddr *) &addr, माप(addr));
	अगर (err < 0) अणु
		BT_ERR("Bind failed %d", err);
		जाओ failed;
	पूर्ण

	/* Set L2CAP options */
	sk = sock->sk;
	lock_sock(sk);
	/* Set MTU to 0 so L2CAP can स्वतः select the MTU */
	l2cap_pi(sk)->chan->imtu = 0;
	release_sock(sk);

	/* Start listening on the socket */
	err = kernel_listen(sock, 10);
	अगर (err) अणु
		BT_ERR("Listen failed %d", err);
		जाओ failed;
	पूर्ण

	/* Add listening session */
	s = rfcomm_session_add(sock, BT_LISTEN);
	अगर (!s) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	वापस 0;
failed:
	sock_release(sock);
	वापस err;
पूर्ण

अटल व्योम rfcomm_समाप्त_listener(व्योम)
अणु
	काष्ठा rfcomm_session *s, *n;

	BT_DBG("");

	list_क्रम_each_entry_safe(s, n, &session_list, list)
		rfcomm_session_del(s);
पूर्ण

अटल पूर्णांक rfcomm_run(व्योम *unused)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	BT_DBG("");

	set_user_nice(current, -10);

	rfcomm_add_listener(BDADDR_ANY);

	add_रुको_queue(&rfcomm_wq, &रुको);
	जबतक (!kthपढ़ो_should_stop()) अणु

		/* Process stuff */
		rfcomm_process_sessions();

		रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(&rfcomm_wq, &रुको);

	rfcomm_समाप्त_listener();

	वापस 0;
पूर्ण

अटल व्योम rfcomm_security_cfm(काष्ठा hci_conn *conn, u8 status, u8 encrypt)
अणु
	काष्ठा rfcomm_session *s;
	काष्ठा rfcomm_dlc *d, *n;

	BT_DBG("conn %p status 0x%02x encrypt 0x%02x", conn, status, encrypt);

	s = rfcomm_session_get(&conn->hdev->bdaddr, &conn->dst);
	अगर (!s)
		वापस;

	list_क्रम_each_entry_safe(d, n, &s->dlcs, list) अणु
		अगर (test_and_clear_bit(RFCOMM_SEC_PENDING, &d->flags)) अणु
			rfcomm_dlc_clear_समयr(d);
			अगर (status || encrypt == 0x00) अणु
				set_bit(RFCOMM_ENC_DROP, &d->flags);
				जारी;
			पूर्ण
		पूर्ण

		अगर (d->state == BT_CONNECTED && !status && encrypt == 0x00) अणु
			अगर (d->sec_level == BT_SECURITY_MEDIUM) अणु
				set_bit(RFCOMM_SEC_PENDING, &d->flags);
				rfcomm_dlc_set_समयr(d, RFCOMM_AUTH_TIMEOUT);
				जारी;
			पूर्ण अन्यथा अगर (d->sec_level == BT_SECURITY_HIGH ||
				   d->sec_level == BT_SECURITY_FIPS) अणु
				set_bit(RFCOMM_ENC_DROP, &d->flags);
				जारी;
			पूर्ण
		पूर्ण

		अगर (!test_and_clear_bit(RFCOMM_AUTH_PENDING, &d->flags))
			जारी;

		अगर (!status && hci_conn_check_secure(conn, d->sec_level))
			set_bit(RFCOMM_AUTH_ACCEPT, &d->flags);
		अन्यथा
			set_bit(RFCOMM_AUTH_REJECT, &d->flags);
	पूर्ण

	rfcomm_schedule();
पूर्ण

अटल काष्ठा hci_cb rfcomm_cb = अणु
	.name		= "RFCOMM",
	.security_cfm	= rfcomm_security_cfm
पूर्ण;

अटल पूर्णांक rfcomm_dlc_debugfs_show(काष्ठा seq_file *f, व्योम *x)
अणु
	काष्ठा rfcomm_session *s;

	rfcomm_lock();

	list_क्रम_each_entry(s, &session_list, list) अणु
		काष्ठा l2cap_chan *chan = l2cap_pi(s->sock->sk)->chan;
		काष्ठा rfcomm_dlc *d;
		list_क्रम_each_entry(d, &s->dlcs, list) अणु
			seq_म_लिखो(f, "%pMR %pMR %ld %d %d %d %d\n",
				   &chan->src, &chan->dst,
				   d->state, d->dlci, d->mtu,
				   d->rx_credits, d->tx_credits);
		पूर्ण
	पूर्ण

	rfcomm_unlock();

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rfcomm_dlc_debugfs);

अटल काष्ठा dentry *rfcomm_dlc_debugfs;

/* ---- Initialization ---- */
अटल पूर्णांक __init rfcomm_init(व्योम)
अणु
	पूर्णांक err;

	hci_रेजिस्टर_cb(&rfcomm_cb);

	rfcomm_thपढ़ो = kthपढ़ो_run(rfcomm_run, शून्य, "krfcommd");
	अगर (IS_ERR(rfcomm_thपढ़ो)) अणु
		err = PTR_ERR(rfcomm_thपढ़ो);
		जाओ unरेजिस्टर;
	पूर्ण

	err = rfcomm_init_ttys();
	अगर (err < 0)
		जाओ stop;

	err = rfcomm_init_sockets();
	अगर (err < 0)
		जाओ cleanup;

	BT_INFO("RFCOMM ver %s", VERSION);

	अगर (IS_ERR_OR_शून्य(bt_debugfs))
		वापस 0;

	rfcomm_dlc_debugfs = debugfs_create_file("rfcomm_dlc", 0444,
						 bt_debugfs, शून्य,
						 &rfcomm_dlc_debugfs_fops);

	वापस 0;

cleanup:
	rfcomm_cleanup_ttys();

stop:
	kthपढ़ो_stop(rfcomm_thपढ़ो);

unरेजिस्टर:
	hci_unरेजिस्टर_cb(&rfcomm_cb);

	वापस err;
पूर्ण

अटल व्योम __निकास rfcomm_निकास(व्योम)
अणु
	debugfs_हटाओ(rfcomm_dlc_debugfs);

	hci_unरेजिस्टर_cb(&rfcomm_cb);

	kthपढ़ो_stop(rfcomm_thपढ़ो);

	rfcomm_cleanup_ttys();

	rfcomm_cleanup_sockets();
पूर्ण

module_init(rfcomm_init);
module_निकास(rfcomm_निकास);

module_param(disable_cfc, bool, 0644);
MODULE_PARM_DESC(disable_cfc, "Disable credit based flow control");

module_param(channel_mtu, पूर्णांक, 0644);
MODULE_PARM_DESC(channel_mtu, "Default MTU for the RFCOMM channel");

module_param(l2cap_erपंचांग, bool, 0644);
MODULE_PARM_DESC(l2cap_erपंचांग, "Use L2CAP ERTM mode for connection");

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth RFCOMM ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("bt-proto-3");
