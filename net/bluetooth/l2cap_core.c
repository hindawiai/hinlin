<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated
   Copyright (C) 2009-2010 Gustavo F. Paकरोvan <gustavo@paकरोvan.org>
   Copyright (C) 2010 Google Inc.
   Copyright (C) 2011 ProFUSION Embedded Systems
   Copyright (c) 2012 Code Aurora Forum.  All rights reserved.

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

/* Bluetooth L2CAP core. */

#समावेश <linux/module.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/crc16.h>
#समावेश <linux/filter.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश "smp.h"
#समावेश "a2mp.h"
#समावेश "amp.h"

#घोषणा LE_FLOWCTL_MAX_CREDITS 65535

bool disable_erपंचांग;
bool enable_ecred;

अटल u32 l2cap_feat_mask = L2CAP_FEAT_FIXED_CHAN | L2CAP_FEAT_UCD;

अटल LIST_HEAD(chan_list);
अटल DEFINE_RWLOCK(chan_list_lock);

अटल काष्ठा sk_buff *l2cap_build_cmd(काष्ठा l2cap_conn *conn,
				       u8 code, u8 ident, u16 dlen, व्योम *data);
अटल व्योम l2cap_send_cmd(काष्ठा l2cap_conn *conn, u8 ident, u8 code, u16 len,
			   व्योम *data);
अटल पूर्णांक l2cap_build_conf_req(काष्ठा l2cap_chan *chan, व्योम *data, माप_प्रकार data_size);
अटल व्योम l2cap_send_disconn_req(काष्ठा l2cap_chan *chan, पूर्णांक err);

अटल व्योम l2cap_tx(काष्ठा l2cap_chan *chan, काष्ठा l2cap_ctrl *control,
		     काष्ठा sk_buff_head *skbs, u8 event);

अटल अंतरभूत u8 bdaddr_type(u8 link_type, u8 bdaddr_type)
अणु
	अगर (link_type == LE_LINK) अणु
		अगर (bdaddr_type == ADDR_LE_DEV_PUBLIC)
			वापस BDADDR_LE_PUBLIC;
		अन्यथा
			वापस BDADDR_LE_RANDOM;
	पूर्ण

	वापस BDADDR_BREDR;
पूर्ण

अटल अंतरभूत u8 bdaddr_src_type(काष्ठा hci_conn *hcon)
अणु
	वापस bdaddr_type(hcon->type, hcon->src_type);
पूर्ण

अटल अंतरभूत u8 bdaddr_dst_type(काष्ठा hci_conn *hcon)
अणु
	वापस bdaddr_type(hcon->type, hcon->dst_type);
पूर्ण

/* ---- L2CAP channels ---- */

अटल काष्ठा l2cap_chan *__l2cap_get_chan_by_dcid(काष्ठा l2cap_conn *conn,
						   u16 cid)
अणु
	काष्ठा l2cap_chan *c;

	list_क्रम_each_entry(c, &conn->chan_l, list) अणु
		अगर (c->dcid == cid)
			वापस c;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा l2cap_chan *__l2cap_get_chan_by_scid(काष्ठा l2cap_conn *conn,
						   u16 cid)
अणु
	काष्ठा l2cap_chan *c;

	list_क्रम_each_entry(c, &conn->chan_l, list) अणु
		अगर (c->scid == cid)
			वापस c;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Find channel with given SCID.
 * Returns locked channel. */
अटल काष्ठा l2cap_chan *l2cap_get_chan_by_scid(काष्ठा l2cap_conn *conn,
						 u16 cid)
अणु
	काष्ठा l2cap_chan *c;

	mutex_lock(&conn->chan_lock);
	c = __l2cap_get_chan_by_scid(conn, cid);
	अगर (c)
		l2cap_chan_lock(c);
	mutex_unlock(&conn->chan_lock);

	वापस c;
पूर्ण

/* Find channel with given DCID.
 * Returns locked channel.
 */
अटल काष्ठा l2cap_chan *l2cap_get_chan_by_dcid(काष्ठा l2cap_conn *conn,
						 u16 cid)
अणु
	काष्ठा l2cap_chan *c;

	mutex_lock(&conn->chan_lock);
	c = __l2cap_get_chan_by_dcid(conn, cid);
	अगर (c)
		l2cap_chan_lock(c);
	mutex_unlock(&conn->chan_lock);

	वापस c;
पूर्ण

अटल काष्ठा l2cap_chan *__l2cap_get_chan_by_ident(काष्ठा l2cap_conn *conn,
						    u8 ident)
अणु
	काष्ठा l2cap_chan *c;

	list_क्रम_each_entry(c, &conn->chan_l, list) अणु
		अगर (c->ident == ident)
			वापस c;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा l2cap_chan *l2cap_get_chan_by_ident(काष्ठा l2cap_conn *conn,
						  u8 ident)
अणु
	काष्ठा l2cap_chan *c;

	mutex_lock(&conn->chan_lock);
	c = __l2cap_get_chan_by_ident(conn, ident);
	अगर (c)
		l2cap_chan_lock(c);
	mutex_unlock(&conn->chan_lock);

	वापस c;
पूर्ण

अटल काष्ठा l2cap_chan *__l2cap_global_chan_by_addr(__le16 psm, bdaddr_t *src,
						      u8 src_type)
अणु
	काष्ठा l2cap_chan *c;

	list_क्रम_each_entry(c, &chan_list, global_l) अणु
		अगर (src_type == BDADDR_BREDR && c->src_type != BDADDR_BREDR)
			जारी;

		अगर (src_type != BDADDR_BREDR && c->src_type == BDADDR_BREDR)
			जारी;

		अगर (c->sport == psm && !bacmp(&c->src, src))
			वापस c;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक l2cap_add_psm(काष्ठा l2cap_chan *chan, bdaddr_t *src, __le16 psm)
अणु
	पूर्णांक err;

	ग_लिखो_lock(&chan_list_lock);

	अगर (psm && __l2cap_global_chan_by_addr(psm, src, chan->src_type)) अणु
		err = -EADDRINUSE;
		जाओ करोne;
	पूर्ण

	अगर (psm) अणु
		chan->psm = psm;
		chan->sport = psm;
		err = 0;
	पूर्ण अन्यथा अणु
		u16 p, start, end, incr;

		अगर (chan->src_type == BDADDR_BREDR) अणु
			start = L2CAP_PSM_DYN_START;
			end = L2CAP_PSM_AUTO_END;
			incr = 2;
		पूर्ण अन्यथा अणु
			start = L2CAP_PSM_LE_DYN_START;
			end = L2CAP_PSM_LE_DYN_END;
			incr = 1;
		पूर्ण

		err = -EINVAL;
		क्रम (p = start; p <= end; p += incr)
			अगर (!__l2cap_global_chan_by_addr(cpu_to_le16(p), src,
							 chan->src_type)) अणु
				chan->psm   = cpu_to_le16(p);
				chan->sport = cpu_to_le16(p);
				err = 0;
				अवरोध;
			पूर्ण
	पूर्ण

करोne:
	ग_लिखो_unlock(&chan_list_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(l2cap_add_psm);

पूर्णांक l2cap_add_scid(काष्ठा l2cap_chan *chan,  __u16 scid)
अणु
	ग_लिखो_lock(&chan_list_lock);

	/* Override the शेषs (which are क्रम conn-oriented) */
	chan->omtu = L2CAP_DEFAULT_MTU;
	chan->chan_type = L2CAP_CHAN_FIXED;

	chan->scid = scid;

	ग_लिखो_unlock(&chan_list_lock);

	वापस 0;
पूर्ण

अटल u16 l2cap_alloc_cid(काष्ठा l2cap_conn *conn)
अणु
	u16 cid, dyn_end;

	अगर (conn->hcon->type == LE_LINK)
		dyn_end = L2CAP_CID_LE_DYN_END;
	अन्यथा
		dyn_end = L2CAP_CID_DYN_END;

	क्रम (cid = L2CAP_CID_DYN_START; cid <= dyn_end; cid++) अणु
		अगर (!__l2cap_get_chan_by_scid(conn, cid))
			वापस cid;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम l2cap_state_change(काष्ठा l2cap_chan *chan, पूर्णांक state)
अणु
	BT_DBG("chan %p %s -> %s", chan, state_to_string(chan->state),
	       state_to_string(state));

	chan->state = state;
	chan->ops->state_change(chan, state, 0);
पूर्ण

अटल अंतरभूत व्योम l2cap_state_change_and_error(काष्ठा l2cap_chan *chan,
						पूर्णांक state, पूर्णांक err)
अणु
	chan->state = state;
	chan->ops->state_change(chan, chan->state, err);
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_set_err(काष्ठा l2cap_chan *chan, पूर्णांक err)
अणु
	chan->ops->state_change(chan, chan->state, err);
पूर्ण

अटल व्योम __set_retrans_समयr(काष्ठा l2cap_chan *chan)
अणु
	अगर (!delayed_work_pending(&chan->monitor_समयr) &&
	    chan->retrans_समयout) अणु
		l2cap_set_समयr(chan, &chan->retrans_समयr,
				msecs_to_jअगरfies(chan->retrans_समयout));
	पूर्ण
पूर्ण

अटल व्योम __set_monitor_समयr(काष्ठा l2cap_chan *chan)
अणु
	__clear_retrans_समयr(chan);
	अगर (chan->monitor_समयout) अणु
		l2cap_set_समयr(chan, &chan->monitor_समयr,
				msecs_to_jअगरfies(chan->monitor_समयout));
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *l2cap_erपंचांग_seq_in_queue(काष्ठा sk_buff_head *head,
					       u16 seq)
अणु
	काष्ठा sk_buff *skb;

	skb_queue_walk(head, skb) अणु
		अगर (bt_cb(skb)->l2cap.txseq == seq)
			वापस skb;
	पूर्ण

	वापस शून्य;
पूर्ण

/* ---- L2CAP sequence number lists ---- */

/* For ERTM, ordered lists of sequence numbers must be tracked क्रम
 * SREJ requests that are received and क्रम frames that are to be
 * retransmitted. These seq_list functions implement a singly-linked
 * list in an array, where membership in the list can also be checked
 * in स्थिरant समय. Items can also be added to the tail of the list
 * and हटाओd from the head in स्थिरant समय, without further memory
 * allocs or मुक्तs.
 */

अटल पूर्णांक l2cap_seq_list_init(काष्ठा l2cap_seq_list *seq_list, u16 size)
अणु
	माप_प्रकार alloc_size, i;

	/* Allocated size is a घातer of 2 to map sequence numbers
	 * (which may be up to 14 bits) in to a smaller array that is
	 * sized क्रम the negotiated ERTM transmit winकरोws.
	 */
	alloc_size = roundup_घात_of_two(size);

	seq_list->list = kदो_स्मृति_array(alloc_size, माप(u16), GFP_KERNEL);
	अगर (!seq_list->list)
		वापस -ENOMEM;

	seq_list->mask = alloc_size - 1;
	seq_list->head = L2CAP_SEQ_LIST_CLEAR;
	seq_list->tail = L2CAP_SEQ_LIST_CLEAR;
	क्रम (i = 0; i < alloc_size; i++)
		seq_list->list[i] = L2CAP_SEQ_LIST_CLEAR;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम l2cap_seq_list_मुक्त(काष्ठा l2cap_seq_list *seq_list)
अणु
	kमुक्त(seq_list->list);
पूर्ण

अटल अंतरभूत bool l2cap_seq_list_contains(काष्ठा l2cap_seq_list *seq_list,
					   u16 seq)
अणु
	/* Constant-समय check क्रम list membership */
	वापस seq_list->list[seq & seq_list->mask] != L2CAP_SEQ_LIST_CLEAR;
पूर्ण

अटल अंतरभूत u16 l2cap_seq_list_pop(काष्ठा l2cap_seq_list *seq_list)
अणु
	u16 seq = seq_list->head;
	u16 mask = seq_list->mask;

	seq_list->head = seq_list->list[seq & mask];
	seq_list->list[seq & mask] = L2CAP_SEQ_LIST_CLEAR;

	अगर (seq_list->head == L2CAP_SEQ_LIST_TAIL) अणु
		seq_list->head = L2CAP_SEQ_LIST_CLEAR;
		seq_list->tail = L2CAP_SEQ_LIST_CLEAR;
	पूर्ण

	वापस seq;
पूर्ण

अटल व्योम l2cap_seq_list_clear(काष्ठा l2cap_seq_list *seq_list)
अणु
	u16 i;

	अगर (seq_list->head == L2CAP_SEQ_LIST_CLEAR)
		वापस;

	क्रम (i = 0; i <= seq_list->mask; i++)
		seq_list->list[i] = L2CAP_SEQ_LIST_CLEAR;

	seq_list->head = L2CAP_SEQ_LIST_CLEAR;
	seq_list->tail = L2CAP_SEQ_LIST_CLEAR;
पूर्ण

अटल व्योम l2cap_seq_list_append(काष्ठा l2cap_seq_list *seq_list, u16 seq)
अणु
	u16 mask = seq_list->mask;

	/* All appends happen in स्थिरant समय */

	अगर (seq_list->list[seq & mask] != L2CAP_SEQ_LIST_CLEAR)
		वापस;

	अगर (seq_list->tail == L2CAP_SEQ_LIST_CLEAR)
		seq_list->head = seq;
	अन्यथा
		seq_list->list[seq_list->tail & mask] = seq;

	seq_list->tail = seq;
	seq_list->list[seq & mask] = L2CAP_SEQ_LIST_TAIL;
पूर्ण

अटल व्योम l2cap_chan_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2cap_chan *chan = container_of(work, काष्ठा l2cap_chan,
					       chan_समयr.work);
	काष्ठा l2cap_conn *conn = chan->conn;
	पूर्णांक reason;

	BT_DBG("chan %p state %s", chan, state_to_string(chan->state));

	mutex_lock(&conn->chan_lock);
	/* __set_chan_समयr() calls l2cap_chan_hold(chan) जबतक scheduling
	 * this work. No need to call l2cap_chan_hold(chan) here again.
	 */
	l2cap_chan_lock(chan);

	अगर (chan->state == BT_CONNECTED || chan->state == BT_CONFIG)
		reason = ECONNREFUSED;
	अन्यथा अगर (chan->state == BT_CONNECT &&
		 chan->sec_level != BT_SECURITY_SDP)
		reason = ECONNREFUSED;
	अन्यथा
		reason = ETIMEDOUT;

	l2cap_chan_बंद(chan, reason);

	chan->ops->बंद(chan);

	l2cap_chan_unlock(chan);
	l2cap_chan_put(chan);

	mutex_unlock(&conn->chan_lock);
पूर्ण

काष्ठा l2cap_chan *l2cap_chan_create(व्योम)
अणु
	काष्ठा l2cap_chan *chan;

	chan = kzalloc(माप(*chan), GFP_ATOMIC);
	अगर (!chan)
		वापस शून्य;

	skb_queue_head_init(&chan->tx_q);
	skb_queue_head_init(&chan->srej_q);
	mutex_init(&chan->lock);

	/* Set शेष lock nesting level */
	atomic_set(&chan->nesting, L2CAP_NESTING_NORMAL);

	ग_लिखो_lock(&chan_list_lock);
	list_add(&chan->global_l, &chan_list);
	ग_लिखो_unlock(&chan_list_lock);

	INIT_DELAYED_WORK(&chan->chan_समयr, l2cap_chan_समयout);

	chan->state = BT_OPEN;

	kref_init(&chan->kref);

	/* This flag is cleared in l2cap_chan_पढ़ोy() */
	set_bit(CONF_NOT_COMPLETE, &chan->conf_state);

	BT_DBG("chan %p", chan);

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(l2cap_chan_create);

अटल व्योम l2cap_chan_destroy(काष्ठा kref *kref)
अणु
	काष्ठा l2cap_chan *chan = container_of(kref, काष्ठा l2cap_chan, kref);

	BT_DBG("chan %p", chan);

	ग_लिखो_lock(&chan_list_lock);
	list_del(&chan->global_l);
	ग_लिखो_unlock(&chan_list_lock);

	kमुक्त(chan);
पूर्ण

व्योम l2cap_chan_hold(काष्ठा l2cap_chan *c)
अणु
	BT_DBG("chan %p orig refcnt %u", c, kref_पढ़ो(&c->kref));

	kref_get(&c->kref);
पूर्ण

व्योम l2cap_chan_put(काष्ठा l2cap_chan *c)
अणु
	BT_DBG("chan %p orig refcnt %u", c, kref_पढ़ो(&c->kref));

	kref_put(&c->kref, l2cap_chan_destroy);
पूर्ण
EXPORT_SYMBOL_GPL(l2cap_chan_put);

व्योम l2cap_chan_set_शेषs(काष्ठा l2cap_chan *chan)
अणु
	chan->fcs  = L2CAP_FCS_CRC16;
	chan->max_tx = L2CAP_DEFAULT_MAX_TX;
	chan->tx_win = L2CAP_DEFAULT_TX_WINDOW;
	chan->tx_win_max = L2CAP_DEFAULT_TX_WINDOW;
	chan->remote_max_tx = chan->max_tx;
	chan->remote_tx_win = chan->tx_win;
	chan->ack_win = L2CAP_DEFAULT_TX_WINDOW;
	chan->sec_level = BT_SECURITY_LOW;
	chan->flush_to = L2CAP_DEFAULT_FLUSH_TO;
	chan->retrans_समयout = L2CAP_DEFAULT_RETRANS_TO;
	chan->monitor_समयout = L2CAP_DEFAULT_MONITOR_TO;

	chan->conf_state = 0;
	set_bit(CONF_NOT_COMPLETE, &chan->conf_state);

	set_bit(FLAG_FORCE_ACTIVE, &chan->flags);
पूर्ण
EXPORT_SYMBOL_GPL(l2cap_chan_set_शेषs);

अटल व्योम l2cap_le_flowctl_init(काष्ठा l2cap_chan *chan, u16 tx_credits)
अणु
	chan->sdu = शून्य;
	chan->sdu_last_frag = शून्य;
	chan->sdu_len = 0;
	chan->tx_credits = tx_credits;
	/* Derive MPS from connection MTU to stop HCI fragmentation */
	chan->mps = min_t(u16, chan->imtu, chan->conn->mtu - L2CAP_HDR_SIZE);
	/* Give enough credits क्रम a full packet */
	chan->rx_credits = (chan->imtu / chan->mps) + 1;

	skb_queue_head_init(&chan->tx_q);
पूर्ण

अटल व्योम l2cap_ecred_init(काष्ठा l2cap_chan *chan, u16 tx_credits)
अणु
	l2cap_le_flowctl_init(chan, tx_credits);

	/* L2CAP implementations shall support a minimum MPS of 64 octets */
	अगर (chan->mps < L2CAP_ECRED_MIN_MPS) अणु
		chan->mps = L2CAP_ECRED_MIN_MPS;
		chan->rx_credits = (chan->imtu / chan->mps) + 1;
	पूर्ण
पूर्ण

व्योम __l2cap_chan_add(काष्ठा l2cap_conn *conn, काष्ठा l2cap_chan *chan)
अणु
	BT_DBG("conn %p, psm 0x%2.2x, dcid 0x%4.4x", conn,
	       __le16_to_cpu(chan->psm), chan->dcid);

	conn->disc_reason = HCI_ERROR_REMOTE_USER_TERM;

	chan->conn = conn;

	चयन (chan->chan_type) अणु
	हाल L2CAP_CHAN_CONN_ORIENTED:
		/* Alloc CID क्रम connection-oriented socket */
		chan->scid = l2cap_alloc_cid(conn);
		अगर (conn->hcon->type == ACL_LINK)
			chan->omtu = L2CAP_DEFAULT_MTU;
		अवरोध;

	हाल L2CAP_CHAN_CONN_LESS:
		/* Connectionless socket */
		chan->scid = L2CAP_CID_CONN_LESS;
		chan->dcid = L2CAP_CID_CONN_LESS;
		chan->omtu = L2CAP_DEFAULT_MTU;
		अवरोध;

	हाल L2CAP_CHAN_FIXED:
		/* Caller will set CID and CID specअगरic MTU values */
		अवरोध;

	शेष:
		/* Raw socket can send/recv संकेतling messages only */
		chan->scid = L2CAP_CID_SIGNALING;
		chan->dcid = L2CAP_CID_SIGNALING;
		chan->omtu = L2CAP_DEFAULT_MTU;
	पूर्ण

	chan->local_id		= L2CAP_BESTEFFORT_ID;
	chan->local_stype	= L2CAP_SERV_BESTEFFORT;
	chan->local_msdu	= L2CAP_DEFAULT_MAX_SDU_SIZE;
	chan->local_sdu_iसमय	= L2CAP_DEFAULT_SDU_ITIME;
	chan->local_acc_lat	= L2CAP_DEFAULT_ACC_LAT;
	chan->local_flush_to	= L2CAP_EFS_DEFAULT_FLUSH_TO;

	l2cap_chan_hold(chan);

	/* Only keep a reference क्रम fixed channels अगर they requested it */
	अगर (chan->chan_type != L2CAP_CHAN_FIXED ||
	    test_bit(FLAG_HOLD_HCI_CONN, &chan->flags))
		hci_conn_hold(conn->hcon);

	list_add(&chan->list, &conn->chan_l);
पूर्ण

व्योम l2cap_chan_add(काष्ठा l2cap_conn *conn, काष्ठा l2cap_chan *chan)
अणु
	mutex_lock(&conn->chan_lock);
	__l2cap_chan_add(conn, chan);
	mutex_unlock(&conn->chan_lock);
पूर्ण

व्योम l2cap_chan_del(काष्ठा l2cap_chan *chan, पूर्णांक err)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;

	__clear_chan_समयr(chan);

	BT_DBG("chan %p, conn %p, err %d, state %s", chan, conn, err,
	       state_to_string(chan->state));

	chan->ops->tearकरोwn(chan, err);

	अगर (conn) अणु
		काष्ठा amp_mgr *mgr = conn->hcon->amp_mgr;
		/* Delete from channel list */
		list_del(&chan->list);

		l2cap_chan_put(chan);

		chan->conn = शून्य;

		/* Reference was only held क्रम non-fixed channels or
		 * fixed channels that explicitly requested it using the
		 * FLAG_HOLD_HCI_CONN flag.
		 */
		अगर (chan->chan_type != L2CAP_CHAN_FIXED ||
		    test_bit(FLAG_HOLD_HCI_CONN, &chan->flags))
			hci_conn_drop(conn->hcon);

		अगर (mgr && mgr->bredr_chan == chan)
			mgr->bredr_chan = शून्य;
	पूर्ण

	अगर (chan->hs_hchan) अणु
		काष्ठा hci_chan *hs_hchan = chan->hs_hchan;

		BT_DBG("chan %p disconnect hs_hchan %p", chan, hs_hchan);
		amp_disconnect_logical_link(hs_hchan);
	पूर्ण

	अगर (test_bit(CONF_NOT_COMPLETE, &chan->conf_state))
		वापस;

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_BASIC:
		अवरोध;

	हाल L2CAP_MODE_LE_FLOWCTL:
	हाल L2CAP_MODE_EXT_FLOWCTL:
		skb_queue_purge(&chan->tx_q);
		अवरोध;

	हाल L2CAP_MODE_ERTM:
		__clear_retrans_समयr(chan);
		__clear_monitor_समयr(chan);
		__clear_ack_समयr(chan);

		skb_queue_purge(&chan->srej_q);

		l2cap_seq_list_मुक्त(&chan->srej_list);
		l2cap_seq_list_मुक्त(&chan->retrans_list);
		fallthrough;

	हाल L2CAP_MODE_STREAMING:
		skb_queue_purge(&chan->tx_q);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(l2cap_chan_del);

अटल व्योम __l2cap_chan_list(काष्ठा l2cap_conn *conn, l2cap_chan_func_t func,
			      व्योम *data)
अणु
	काष्ठा l2cap_chan *chan;

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		func(chan, data);
	पूर्ण
पूर्ण

व्योम l2cap_chan_list(काष्ठा l2cap_conn *conn, l2cap_chan_func_t func,
		     व्योम *data)
अणु
	अगर (!conn)
		वापस;

	mutex_lock(&conn->chan_lock);
	__l2cap_chan_list(conn, func, data);
	mutex_unlock(&conn->chan_lock);
पूर्ण

EXPORT_SYMBOL_GPL(l2cap_chan_list);

अटल व्योम l2cap_conn_update_id_addr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2cap_conn *conn = container_of(work, काष्ठा l2cap_conn,
					       id_addr_update_work);
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_chan *chan;

	mutex_lock(&conn->chan_lock);

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		l2cap_chan_lock(chan);
		bacpy(&chan->dst, &hcon->dst);
		chan->dst_type = bdaddr_dst_type(hcon);
		l2cap_chan_unlock(chan);
	पूर्ण

	mutex_unlock(&conn->chan_lock);
पूर्ण

अटल व्योम l2cap_chan_le_connect_reject(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_le_conn_rsp rsp;
	u16 result;

	अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags))
		result = L2CAP_CR_LE_AUTHORIZATION;
	अन्यथा
		result = L2CAP_CR_LE_BAD_PSM;

	l2cap_state_change(chan, BT_DISCONN);

	rsp.dcid    = cpu_to_le16(chan->scid);
	rsp.mtu     = cpu_to_le16(chan->imtu);
	rsp.mps     = cpu_to_le16(chan->mps);
	rsp.credits = cpu_to_le16(chan->rx_credits);
	rsp.result  = cpu_to_le16(result);

	l2cap_send_cmd(conn, chan->ident, L2CAP_LE_CONN_RSP, माप(rsp),
		       &rsp);
पूर्ण

अटल व्योम l2cap_chan_ecred_connect_reject(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_ecred_conn_rsp rsp;
	u16 result;

	अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags))
		result = L2CAP_CR_LE_AUTHORIZATION;
	अन्यथा
		result = L2CAP_CR_LE_BAD_PSM;

	l2cap_state_change(chan, BT_DISCONN);

	स_रखो(&rsp, 0, माप(rsp));

	rsp.result  = cpu_to_le16(result);

	l2cap_send_cmd(conn, chan->ident, L2CAP_LE_CONN_RSP, माप(rsp),
		       &rsp);
पूर्ण

अटल व्योम l2cap_chan_connect_reject(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_conn_rsp rsp;
	u16 result;

	अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags))
		result = L2CAP_CR_SEC_BLOCK;
	अन्यथा
		result = L2CAP_CR_BAD_PSM;

	l2cap_state_change(chan, BT_DISCONN);

	rsp.scid   = cpu_to_le16(chan->dcid);
	rsp.dcid   = cpu_to_le16(chan->scid);
	rsp.result = cpu_to_le16(result);
	rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);

	l2cap_send_cmd(conn, chan->ident, L2CAP_CONN_RSP, माप(rsp), &rsp);
पूर्ण

व्योम l2cap_chan_बंद(काष्ठा l2cap_chan *chan, पूर्णांक reason)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;

	BT_DBG("chan %p state %s", chan, state_to_string(chan->state));

	चयन (chan->state) अणु
	हाल BT_LISTEN:
		chan->ops->tearकरोwn(chan, 0);
		अवरोध;

	हाल BT_CONNECTED:
	हाल BT_CONFIG:
		अगर (chan->chan_type == L2CAP_CHAN_CONN_ORIENTED) अणु
			__set_chan_समयr(chan, chan->ops->get_sndसमयo(chan));
			l2cap_send_disconn_req(chan, reason);
		पूर्ण अन्यथा
			l2cap_chan_del(chan, reason);
		अवरोध;

	हाल BT_CONNECT2:
		अगर (chan->chan_type == L2CAP_CHAN_CONN_ORIENTED) अणु
			अगर (conn->hcon->type == ACL_LINK)
				l2cap_chan_connect_reject(chan);
			अन्यथा अगर (conn->hcon->type == LE_LINK) अणु
				चयन (chan->mode) अणु
				हाल L2CAP_MODE_LE_FLOWCTL:
					l2cap_chan_le_connect_reject(chan);
					अवरोध;
				हाल L2CAP_MODE_EXT_FLOWCTL:
					l2cap_chan_ecred_connect_reject(chan);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		l2cap_chan_del(chan, reason);
		अवरोध;

	हाल BT_CONNECT:
	हाल BT_DISCONN:
		l2cap_chan_del(chan, reason);
		अवरोध;

	शेष:
		chan->ops->tearकरोwn(chan, 0);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(l2cap_chan_बंद);

अटल अंतरभूत u8 l2cap_get_auth_type(काष्ठा l2cap_chan *chan)
अणु
	चयन (chan->chan_type) अणु
	हाल L2CAP_CHAN_RAW:
		चयन (chan->sec_level) अणु
		हाल BT_SECURITY_HIGH:
		हाल BT_SECURITY_FIPS:
			वापस HCI_AT_DEDICATED_BONDING_MITM;
		हाल BT_SECURITY_MEDIUM:
			वापस HCI_AT_DEDICATED_BONDING;
		शेष:
			वापस HCI_AT_NO_BONDING;
		पूर्ण
		अवरोध;
	हाल L2CAP_CHAN_CONN_LESS:
		अगर (chan->psm == cpu_to_le16(L2CAP_PSM_3DSP)) अणु
			अगर (chan->sec_level == BT_SECURITY_LOW)
				chan->sec_level = BT_SECURITY_SDP;
		पूर्ण
		अगर (chan->sec_level == BT_SECURITY_HIGH ||
		    chan->sec_level == BT_SECURITY_FIPS)
			वापस HCI_AT_NO_BONDING_MITM;
		अन्यथा
			वापस HCI_AT_NO_BONDING;
		अवरोध;
	हाल L2CAP_CHAN_CONN_ORIENTED:
		अगर (chan->psm == cpu_to_le16(L2CAP_PSM_SDP)) अणु
			अगर (chan->sec_level == BT_SECURITY_LOW)
				chan->sec_level = BT_SECURITY_SDP;

			अगर (chan->sec_level == BT_SECURITY_HIGH ||
			    chan->sec_level == BT_SECURITY_FIPS)
				वापस HCI_AT_NO_BONDING_MITM;
			अन्यथा
				वापस HCI_AT_NO_BONDING;
		पूर्ण
		fallthrough;

	शेष:
		चयन (chan->sec_level) अणु
		हाल BT_SECURITY_HIGH:
		हाल BT_SECURITY_FIPS:
			वापस HCI_AT_GENERAL_BONDING_MITM;
		हाल BT_SECURITY_MEDIUM:
			वापस HCI_AT_GENERAL_BONDING;
		शेष:
			वापस HCI_AT_NO_BONDING;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/* Service level security */
पूर्णांक l2cap_chan_check_security(काष्ठा l2cap_chan *chan, bool initiator)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	__u8 auth_type;

	अगर (conn->hcon->type == LE_LINK)
		वापस smp_conn_security(conn->hcon, chan->sec_level);

	auth_type = l2cap_get_auth_type(chan);

	वापस hci_conn_security(conn->hcon, chan->sec_level, auth_type,
				 initiator);
पूर्ण

अटल u8 l2cap_get_ident(काष्ठा l2cap_conn *conn)
अणु
	u8 id;

	/* Get next available identअगरicator.
	 *    1 - 128 are used by kernel.
	 *  129 - 199 are reserved.
	 *  200 - 254 are used by utilities like l2ping, etc.
	 */

	mutex_lock(&conn->ident_lock);

	अगर (++conn->tx_ident > 128)
		conn->tx_ident = 1;

	id = conn->tx_ident;

	mutex_unlock(&conn->ident_lock);

	वापस id;
पूर्ण

अटल व्योम l2cap_send_cmd(काष्ठा l2cap_conn *conn, u8 ident, u8 code, u16 len,
			   व्योम *data)
अणु
	काष्ठा sk_buff *skb = l2cap_build_cmd(conn, code, ident, len, data);
	u8 flags;

	BT_DBG("code 0x%2.2x", code);

	अगर (!skb)
		वापस;

	/* Use NO_FLUSH अगर supported or we have an LE link (which करोes
	 * not support स्वतः-flushing packets) */
	अगर (lmp_no_flush_capable(conn->hcon->hdev) ||
	    conn->hcon->type == LE_LINK)
		flags = ACL_START_NO_FLUSH;
	अन्यथा
		flags = ACL_START;

	bt_cb(skb)->क्रमce_active = BT_POWER_FORCE_ACTIVE_ON;
	skb->priority = HCI_PRIO_MAX;

	hci_send_acl(conn->hchan, skb, flags);
पूर्ण

अटल bool __chan_is_moving(काष्ठा l2cap_chan *chan)
अणु
	वापस chan->move_state != L2CAP_MOVE_STABLE &&
	       chan->move_state != L2CAP_MOVE_WAIT_PREPARE;
पूर्ण

अटल व्योम l2cap_करो_send(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_conn *hcon = chan->conn->hcon;
	u16 flags;

	BT_DBG("chan %p, skb %p len %d priority %u", chan, skb, skb->len,
	       skb->priority);

	अगर (chan->hs_hcon && !__chan_is_moving(chan)) अणु
		अगर (chan->hs_hchan)
			hci_send_acl(chan->hs_hchan, skb, ACL_COMPLETE);
		अन्यथा
			kमुक्त_skb(skb);

		वापस;
	पूर्ण

	/* Use NO_FLUSH क्रम LE links (where this is the only option) or
	 * अगर the BR/EDR link supports it and flushing has not been
	 * explicitly requested (through FLAG_FLUSHABLE).
	 */
	अगर (hcon->type == LE_LINK ||
	    (!test_bit(FLAG_FLUSHABLE, &chan->flags) &&
	     lmp_no_flush_capable(hcon->hdev)))
		flags = ACL_START_NO_FLUSH;
	अन्यथा
		flags = ACL_START;

	bt_cb(skb)->क्रमce_active = test_bit(FLAG_FORCE_ACTIVE, &chan->flags);
	hci_send_acl(chan->conn->hchan, skb, flags);
पूर्ण

अटल व्योम __unpack_enhanced_control(u16 enh, काष्ठा l2cap_ctrl *control)
अणु
	control->reqseq = (enh & L2CAP_CTRL_REQSEQ) >> L2CAP_CTRL_REQSEQ_SHIFT;
	control->final = (enh & L2CAP_CTRL_FINAL) >> L2CAP_CTRL_FINAL_SHIFT;

	अगर (enh & L2CAP_CTRL_FRAME_TYPE) अणु
		/* S-Frame */
		control->sframe = 1;
		control->poll = (enh & L2CAP_CTRL_POLL) >> L2CAP_CTRL_POLL_SHIFT;
		control->super = (enh & L2CAP_CTRL_SUPERVISE) >> L2CAP_CTRL_SUPER_SHIFT;

		control->sar = 0;
		control->txseq = 0;
	पूर्ण अन्यथा अणु
		/* I-Frame */
		control->sframe = 0;
		control->sar = (enh & L2CAP_CTRL_SAR) >> L2CAP_CTRL_SAR_SHIFT;
		control->txseq = (enh & L2CAP_CTRL_TXSEQ) >> L2CAP_CTRL_TXSEQ_SHIFT;

		control->poll = 0;
		control->super = 0;
	पूर्ण
पूर्ण

अटल व्योम __unpack_extended_control(u32 ext, काष्ठा l2cap_ctrl *control)
अणु
	control->reqseq = (ext & L2CAP_EXT_CTRL_REQSEQ) >> L2CAP_EXT_CTRL_REQSEQ_SHIFT;
	control->final = (ext & L2CAP_EXT_CTRL_FINAL) >> L2CAP_EXT_CTRL_FINAL_SHIFT;

	अगर (ext & L2CAP_EXT_CTRL_FRAME_TYPE) अणु
		/* S-Frame */
		control->sframe = 1;
		control->poll = (ext & L2CAP_EXT_CTRL_POLL) >> L2CAP_EXT_CTRL_POLL_SHIFT;
		control->super = (ext & L2CAP_EXT_CTRL_SUPERVISE) >> L2CAP_EXT_CTRL_SUPER_SHIFT;

		control->sar = 0;
		control->txseq = 0;
	पूर्ण अन्यथा अणु
		/* I-Frame */
		control->sframe = 0;
		control->sar = (ext & L2CAP_EXT_CTRL_SAR) >> L2CAP_EXT_CTRL_SAR_SHIFT;
		control->txseq = (ext & L2CAP_EXT_CTRL_TXSEQ) >> L2CAP_EXT_CTRL_TXSEQ_SHIFT;

		control->poll = 0;
		control->super = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __unpack_control(काष्ठा l2cap_chan *chan,
				    काष्ठा sk_buff *skb)
अणु
	अगर (test_bit(FLAG_EXT_CTRL, &chan->flags)) अणु
		__unpack_extended_control(get_unaligned_le32(skb->data),
					  &bt_cb(skb)->l2cap);
		skb_pull(skb, L2CAP_EXT_CTRL_SIZE);
	पूर्ण अन्यथा अणु
		__unpack_enhanced_control(get_unaligned_le16(skb->data),
					  &bt_cb(skb)->l2cap);
		skb_pull(skb, L2CAP_ENH_CTRL_SIZE);
	पूर्ण
पूर्ण

अटल u32 __pack_extended_control(काष्ठा l2cap_ctrl *control)
अणु
	u32 packed;

	packed = control->reqseq << L2CAP_EXT_CTRL_REQSEQ_SHIFT;
	packed |= control->final << L2CAP_EXT_CTRL_FINAL_SHIFT;

	अगर (control->sframe) अणु
		packed |= control->poll << L2CAP_EXT_CTRL_POLL_SHIFT;
		packed |= control->super << L2CAP_EXT_CTRL_SUPER_SHIFT;
		packed |= L2CAP_EXT_CTRL_FRAME_TYPE;
	पूर्ण अन्यथा अणु
		packed |= control->sar << L2CAP_EXT_CTRL_SAR_SHIFT;
		packed |= control->txseq << L2CAP_EXT_CTRL_TXSEQ_SHIFT;
	पूर्ण

	वापस packed;
पूर्ण

अटल u16 __pack_enhanced_control(काष्ठा l2cap_ctrl *control)
अणु
	u16 packed;

	packed = control->reqseq << L2CAP_CTRL_REQSEQ_SHIFT;
	packed |= control->final << L2CAP_CTRL_FINAL_SHIFT;

	अगर (control->sframe) अणु
		packed |= control->poll << L2CAP_CTRL_POLL_SHIFT;
		packed |= control->super << L2CAP_CTRL_SUPER_SHIFT;
		packed |= L2CAP_CTRL_FRAME_TYPE;
	पूर्ण अन्यथा अणु
		packed |= control->sar << L2CAP_CTRL_SAR_SHIFT;
		packed |= control->txseq << L2CAP_CTRL_TXSEQ_SHIFT;
	पूर्ण

	वापस packed;
पूर्ण

अटल अंतरभूत व्योम __pack_control(काष्ठा l2cap_chan *chan,
				  काष्ठा l2cap_ctrl *control,
				  काष्ठा sk_buff *skb)
अणु
	अगर (test_bit(FLAG_EXT_CTRL, &chan->flags)) अणु
		put_unaligned_le32(__pack_extended_control(control),
				   skb->data + L2CAP_HDR_SIZE);
	पूर्ण अन्यथा अणु
		put_unaligned_le16(__pack_enhanced_control(control),
				   skb->data + L2CAP_HDR_SIZE);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __erपंचांग_hdr_size(काष्ठा l2cap_chan *chan)
अणु
	अगर (test_bit(FLAG_EXT_CTRL, &chan->flags))
		वापस L2CAP_EXT_HDR_SIZE;
	अन्यथा
		वापस L2CAP_ENH_HDR_SIZE;
पूर्ण

अटल काष्ठा sk_buff *l2cap_create_sframe_pdu(काष्ठा l2cap_chan *chan,
					       u32 control)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा l2cap_hdr *lh;
	पूर्णांक hlen = __erपंचांग_hdr_size(chan);

	अगर (chan->fcs == L2CAP_FCS_CRC16)
		hlen += L2CAP_FCS_SIZE;

	skb = bt_skb_alloc(hlen, GFP_KERNEL);

	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	lh = skb_put(skb, L2CAP_HDR_SIZE);
	lh->len = cpu_to_le16(hlen - L2CAP_HDR_SIZE);
	lh->cid = cpu_to_le16(chan->dcid);

	अगर (test_bit(FLAG_EXT_CTRL, &chan->flags))
		put_unaligned_le32(control, skb_put(skb, L2CAP_EXT_CTRL_SIZE));
	अन्यथा
		put_unaligned_le16(control, skb_put(skb, L2CAP_ENH_CTRL_SIZE));

	अगर (chan->fcs == L2CAP_FCS_CRC16) अणु
		u16 fcs = crc16(0, (u8 *)skb->data, skb->len);
		put_unaligned_le16(fcs, skb_put(skb, L2CAP_FCS_SIZE));
	पूर्ण

	skb->priority = HCI_PRIO_MAX;
	वापस skb;
पूर्ण

अटल व्योम l2cap_send_sframe(काष्ठा l2cap_chan *chan,
			      काष्ठा l2cap_ctrl *control)
अणु
	काष्ठा sk_buff *skb;
	u32 control_field;

	BT_DBG("chan %p, control %p", chan, control);

	अगर (!control->sframe)
		वापस;

	अगर (__chan_is_moving(chan))
		वापस;

	अगर (test_and_clear_bit(CONN_SEND_FBIT, &chan->conn_state) &&
	    !control->poll)
		control->final = 1;

	अगर (control->super == L2CAP_SUPER_RR)
		clear_bit(CONN_RNR_SENT, &chan->conn_state);
	अन्यथा अगर (control->super == L2CAP_SUPER_RNR)
		set_bit(CONN_RNR_SENT, &chan->conn_state);

	अगर (control->super != L2CAP_SUPER_SREJ) अणु
		chan->last_acked_seq = control->reqseq;
		__clear_ack_समयr(chan);
	पूर्ण

	BT_DBG("reqseq %d, final %d, poll %d, super %d", control->reqseq,
	       control->final, control->poll, control->super);

	अगर (test_bit(FLAG_EXT_CTRL, &chan->flags))
		control_field = __pack_extended_control(control);
	अन्यथा
		control_field = __pack_enhanced_control(control);

	skb = l2cap_create_sframe_pdu(chan, control_field);
	अगर (!IS_ERR(skb))
		l2cap_करो_send(chan, skb);
पूर्ण

अटल व्योम l2cap_send_rr_or_rnr(काष्ठा l2cap_chan *chan, bool poll)
अणु
	काष्ठा l2cap_ctrl control;

	BT_DBG("chan %p, poll %d", chan, poll);

	स_रखो(&control, 0, माप(control));
	control.sframe = 1;
	control.poll = poll;

	अगर (test_bit(CONN_LOCAL_BUSY, &chan->conn_state))
		control.super = L2CAP_SUPER_RNR;
	अन्यथा
		control.super = L2CAP_SUPER_RR;

	control.reqseq = chan->buffer_seq;
	l2cap_send_sframe(chan, &control);
पूर्ण

अटल अंतरभूत पूर्णांक __l2cap_no_conn_pending(काष्ठा l2cap_chan *chan)
अणु
	अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED)
		वापस true;

	वापस !test_bit(CONF_CONNECT_PEND, &chan->conf_state);
पूर्ण

अटल bool __amp_capable(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा hci_dev *hdev;
	bool amp_available = false;

	अगर (!(conn->local_fixed_chan & L2CAP_FC_A2MP))
		वापस false;

	अगर (!(conn->remote_fixed_chan & L2CAP_FC_A2MP))
		वापस false;

	पढ़ो_lock(&hci_dev_list_lock);
	list_क्रम_each_entry(hdev, &hci_dev_list, list) अणु
		अगर (hdev->amp_type != AMP_TYPE_BREDR &&
		    test_bit(HCI_UP, &hdev->flags)) अणु
			amp_available = true;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&hci_dev_list_lock);

	अगर (chan->chan_policy == BT_CHANNEL_POLICY_AMP_PREFERRED)
		वापस amp_available;

	वापस false;
पूर्ण

अटल bool l2cap_check_efs(काष्ठा l2cap_chan *chan)
अणु
	/* Check EFS parameters */
	वापस true;
पूर्ण

व्योम l2cap_send_conn_req(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_conn_req req;

	req.scid = cpu_to_le16(chan->scid);
	req.psm  = chan->psm;

	chan->ident = l2cap_get_ident(conn);

	set_bit(CONF_CONNECT_PEND, &chan->conf_state);

	l2cap_send_cmd(conn, chan->ident, L2CAP_CONN_REQ, माप(req), &req);
पूर्ण

अटल व्योम l2cap_send_create_chan_req(काष्ठा l2cap_chan *chan, u8 amp_id)
अणु
	काष्ठा l2cap_create_chan_req req;
	req.scid = cpu_to_le16(chan->scid);
	req.psm  = chan->psm;
	req.amp_id = amp_id;

	chan->ident = l2cap_get_ident(chan->conn);

	l2cap_send_cmd(chan->conn, chan->ident, L2CAP_CREATE_CHAN_REQ,
		       माप(req), &req);
पूर्ण

अटल व्योम l2cap_move_setup(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sk_buff *skb;

	BT_DBG("chan %p", chan);

	अगर (chan->mode != L2CAP_MODE_ERTM)
		वापस;

	__clear_retrans_समयr(chan);
	__clear_monitor_समयr(chan);
	__clear_ack_समयr(chan);

	chan->retry_count = 0;
	skb_queue_walk(&chan->tx_q, skb) अणु
		अगर (bt_cb(skb)->l2cap.retries)
			bt_cb(skb)->l2cap.retries = 1;
		अन्यथा
			अवरोध;
	पूर्ण

	chan->expected_tx_seq = chan->buffer_seq;

	clear_bit(CONN_REJ_ACT, &chan->conn_state);
	clear_bit(CONN_SREJ_ACT, &chan->conn_state);
	l2cap_seq_list_clear(&chan->retrans_list);
	l2cap_seq_list_clear(&chan->srej_list);
	skb_queue_purge(&chan->srej_q);

	chan->tx_state = L2CAP_TX_STATE_XMIT;
	chan->rx_state = L2CAP_RX_STATE_MOVE;

	set_bit(CONN_REMOTE_BUSY, &chan->conn_state);
पूर्ण

अटल व्योम l2cap_move_करोne(काष्ठा l2cap_chan *chan)
अणु
	u8 move_role = chan->move_role;
	BT_DBG("chan %p", chan);

	chan->move_state = L2CAP_MOVE_STABLE;
	chan->move_role = L2CAP_MOVE_ROLE_NONE;

	अगर (chan->mode != L2CAP_MODE_ERTM)
		वापस;

	चयन (move_role) अणु
	हाल L2CAP_MOVE_ROLE_INITIATOR:
		l2cap_tx(chan, शून्य, शून्य, L2CAP_EV_EXPLICIT_POLL);
		chan->rx_state = L2CAP_RX_STATE_WAIT_F;
		अवरोध;
	हाल L2CAP_MOVE_ROLE_RESPONDER:
		chan->rx_state = L2CAP_RX_STATE_WAIT_P;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम l2cap_chan_पढ़ोy(काष्ठा l2cap_chan *chan)
अणु
	/* The channel may have alपढ़ोy been flagged as connected in
	 * हाल of receiving data beक्रमe the L2CAP info req/rsp
	 * procedure is complete.
	 */
	अगर (chan->state == BT_CONNECTED)
		वापस;

	/* This clears all conf flags, including CONF_NOT_COMPLETE */
	chan->conf_state = 0;
	__clear_chan_समयr(chan);

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_LE_FLOWCTL:
	हाल L2CAP_MODE_EXT_FLOWCTL:
		अगर (!chan->tx_credits)
			chan->ops->suspend(chan);
		अवरोध;
	पूर्ण

	chan->state = BT_CONNECTED;

	chan->ops->पढ़ोy(chan);
पूर्ण

अटल व्योम l2cap_le_connect(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_le_conn_req req;

	अगर (test_and_set_bit(FLAG_LE_CONN_REQ_SENT, &chan->flags))
		वापस;

	अगर (!chan->imtu)
		chan->imtu = chan->conn->mtu;

	l2cap_le_flowctl_init(chan, 0);

	req.psm     = chan->psm;
	req.scid    = cpu_to_le16(chan->scid);
	req.mtu     = cpu_to_le16(chan->imtu);
	req.mps     = cpu_to_le16(chan->mps);
	req.credits = cpu_to_le16(chan->rx_credits);

	chan->ident = l2cap_get_ident(conn);

	l2cap_send_cmd(conn, chan->ident, L2CAP_LE_CONN_REQ,
		       माप(req), &req);
पूर्ण

काष्ठा l2cap_ecred_conn_data अणु
	काष्ठा अणु
		काष्ठा l2cap_ecred_conn_req req;
		__le16 scid[5];
	पूर्ण __packed pdu;
	काष्ठा l2cap_chan *chan;
	काष्ठा pid *pid;
	पूर्णांक count;
पूर्ण;

अटल व्योम l2cap_ecred_defer_connect(काष्ठा l2cap_chan *chan, व्योम *data)
अणु
	काष्ठा l2cap_ecred_conn_data *conn = data;
	काष्ठा pid *pid;

	अगर (chan == conn->chan)
		वापस;

	अगर (!test_and_clear_bit(FLAG_DEFER_SETUP, &chan->flags))
		वापस;

	pid = chan->ops->get_peer_pid(chan);

	/* Only add deferred channels with the same PID/PSM */
	अगर (conn->pid != pid || chan->psm != conn->chan->psm || chan->ident ||
	    chan->mode != L2CAP_MODE_EXT_FLOWCTL || chan->state != BT_CONNECT)
		वापस;

	अगर (test_and_set_bit(FLAG_ECRED_CONN_REQ_SENT, &chan->flags))
		वापस;

	l2cap_ecred_init(chan, 0);

	/* Set the same ident so we can match on the rsp */
	chan->ident = conn->chan->ident;

	/* Include all channels deferred */
	conn->pdu.scid[conn->count] = cpu_to_le16(chan->scid);

	conn->count++;
पूर्ण

अटल व्योम l2cap_ecred_connect(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_ecred_conn_data data;

	अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags))
		वापस;

	अगर (test_and_set_bit(FLAG_ECRED_CONN_REQ_SENT, &chan->flags))
		वापस;

	l2cap_ecred_init(chan, 0);

	data.pdu.req.psm     = chan->psm;
	data.pdu.req.mtu     = cpu_to_le16(chan->imtu);
	data.pdu.req.mps     = cpu_to_le16(chan->mps);
	data.pdu.req.credits = cpu_to_le16(chan->rx_credits);
	data.pdu.scid[0]     = cpu_to_le16(chan->scid);

	chan->ident = l2cap_get_ident(conn);
	data.pid = chan->ops->get_peer_pid(chan);

	data.count = 1;
	data.chan = chan;
	data.pid = chan->ops->get_peer_pid(chan);

	__l2cap_chan_list(conn, l2cap_ecred_defer_connect, &data);

	l2cap_send_cmd(conn, chan->ident, L2CAP_ECRED_CONN_REQ,
		       माप(data.pdu.req) + data.count * माप(__le16),
		       &data.pdu);
पूर्ण

अटल व्योम l2cap_le_start(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;

	अगर (!smp_conn_security(conn->hcon, chan->sec_level))
		वापस;

	अगर (!chan->psm) अणु
		l2cap_chan_पढ़ोy(chan);
		वापस;
	पूर्ण

	अगर (chan->state == BT_CONNECT) अणु
		अगर (chan->mode == L2CAP_MODE_EXT_FLOWCTL)
			l2cap_ecred_connect(chan);
		अन्यथा
			l2cap_le_connect(chan);
	पूर्ण
पूर्ण

अटल व्योम l2cap_start_connection(काष्ठा l2cap_chan *chan)
अणु
	अगर (__amp_capable(chan)) अणु
		BT_DBG("chan %p AMP capable: discover AMPs", chan);
		a2mp_discover_amp(chan);
	पूर्ण अन्यथा अगर (chan->conn->hcon->type == LE_LINK) अणु
		l2cap_le_start(chan);
	पूर्ण अन्यथा अणु
		l2cap_send_conn_req(chan);
	पूर्ण
पूर्ण

अटल व्योम l2cap_request_info(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा l2cap_info_req req;

	अगर (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT)
		वापस;

	req.type = cpu_to_le16(L2CAP_IT_FEAT_MASK);

	conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_SENT;
	conn->info_ident = l2cap_get_ident(conn);

	schedule_delayed_work(&conn->info_समयr, L2CAP_INFO_TIMEOUT);

	l2cap_send_cmd(conn, conn->info_ident, L2CAP_INFO_REQ,
		       माप(req), &req);
पूर्ण

अटल bool l2cap_check_enc_key_size(काष्ठा hci_conn *hcon)
अणु
	/* The minimum encryption key size needs to be enक्रमced by the
	 * host stack beक्रमe establishing any L2CAP connections. The
	 * specअगरication in theory allows a minimum of 1, but to align
	 * BR/EDR and LE transports, a minimum of 7 is chosen.
	 *
	 * This check might also be called क्रम unencrypted connections
	 * that have no key size requirements. Ensure that the link is
	 * actually encrypted beक्रमe enक्रमcing a key size.
	 */
	पूर्णांक min_key_size = hcon->hdev->min_enc_key_size;

	/* On FIPS security level, key size must be 16 bytes */
	अगर (hcon->sec_level == BT_SECURITY_FIPS)
		min_key_size = 16;

	वापस (!test_bit(HCI_CONN_ENCRYPT, &hcon->flags) ||
		hcon->enc_key_size >= min_key_size);
पूर्ण

अटल व्योम l2cap_करो_start(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;

	अगर (conn->hcon->type == LE_LINK) अणु
		l2cap_le_start(chan);
		वापस;
	पूर्ण

	अगर (!(conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT)) अणु
		l2cap_request_info(conn);
		वापस;
	पूर्ण

	अगर (!(conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_DONE))
		वापस;

	अगर (!l2cap_chan_check_security(chan, true) ||
	    !__l2cap_no_conn_pending(chan))
		वापस;

	अगर (l2cap_check_enc_key_size(conn->hcon))
		l2cap_start_connection(chan);
	अन्यथा
		__set_chan_समयr(chan, L2CAP_DISC_TIMEOUT);
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_mode_supported(__u8 mode, __u32 feat_mask)
अणु
	u32 local_feat_mask = l2cap_feat_mask;
	अगर (!disable_erपंचांग)
		local_feat_mask |= L2CAP_FEAT_ERTM | L2CAP_FEAT_STREAMING;

	चयन (mode) अणु
	हाल L2CAP_MODE_ERTM:
		वापस L2CAP_FEAT_ERTM & feat_mask & local_feat_mask;
	हाल L2CAP_MODE_STREAMING:
		वापस L2CAP_FEAT_STREAMING & feat_mask & local_feat_mask;
	शेष:
		वापस 0x00;
	पूर्ण
पूर्ण

अटल व्योम l2cap_send_disconn_req(काष्ठा l2cap_chan *chan, पूर्णांक err)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_disconn_req req;

	अगर (!conn)
		वापस;

	अगर (chan->mode == L2CAP_MODE_ERTM && chan->state == BT_CONNECTED) अणु
		__clear_retrans_समयr(chan);
		__clear_monitor_समयr(chan);
		__clear_ack_समयr(chan);
	पूर्ण

	अगर (chan->scid == L2CAP_CID_A2MP) अणु
		l2cap_state_change(chan, BT_DISCONN);
		वापस;
	पूर्ण

	req.dcid = cpu_to_le16(chan->dcid);
	req.scid = cpu_to_le16(chan->scid);
	l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_DISCONN_REQ,
		       माप(req), &req);

	l2cap_state_change_and_error(chan, BT_DISCONN, err);
पूर्ण

/* ---- L2CAP connections ---- */
अटल व्योम l2cap_conn_start(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा l2cap_chan *chan, *पंचांगp;

	BT_DBG("conn %p", conn);

	mutex_lock(&conn->chan_lock);

	list_क्रम_each_entry_safe(chan, पंचांगp, &conn->chan_l, list) अणु
		l2cap_chan_lock(chan);

		अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED) अणु
			l2cap_chan_पढ़ोy(chan);
			l2cap_chan_unlock(chan);
			जारी;
		पूर्ण

		अगर (chan->state == BT_CONNECT) अणु
			अगर (!l2cap_chan_check_security(chan, true) ||
			    !__l2cap_no_conn_pending(chan)) अणु
				l2cap_chan_unlock(chan);
				जारी;
			पूर्ण

			अगर (!l2cap_mode_supported(chan->mode, conn->feat_mask)
			    && test_bit(CONF_STATE2_DEVICE,
					&chan->conf_state)) अणु
				l2cap_chan_बंद(chan, ECONNRESET);
				l2cap_chan_unlock(chan);
				जारी;
			पूर्ण

			अगर (l2cap_check_enc_key_size(conn->hcon))
				l2cap_start_connection(chan);
			अन्यथा
				l2cap_chan_बंद(chan, ECONNREFUSED);

		पूर्ण अन्यथा अगर (chan->state == BT_CONNECT2) अणु
			काष्ठा l2cap_conn_rsp rsp;
			अक्षर buf[128];
			rsp.scid = cpu_to_le16(chan->dcid);
			rsp.dcid = cpu_to_le16(chan->scid);

			अगर (l2cap_chan_check_security(chan, false)) अणु
				अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags)) अणु
					rsp.result = cpu_to_le16(L2CAP_CR_PEND);
					rsp.status = cpu_to_le16(L2CAP_CS_AUTHOR_PEND);
					chan->ops->defer(chan);

				पूर्ण अन्यथा अणु
					l2cap_state_change(chan, BT_CONFIG);
					rsp.result = cpu_to_le16(L2CAP_CR_SUCCESS);
					rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
				पूर्ण
			पूर्ण अन्यथा अणु
				rsp.result = cpu_to_le16(L2CAP_CR_PEND);
				rsp.status = cpu_to_le16(L2CAP_CS_AUTHEN_PEND);
			पूर्ण

			l2cap_send_cmd(conn, chan->ident, L2CAP_CONN_RSP,
				       माप(rsp), &rsp);

			अगर (test_bit(CONF_REQ_SENT, &chan->conf_state) ||
			    rsp.result != L2CAP_CR_SUCCESS) अणु
				l2cap_chan_unlock(chan);
				जारी;
			पूर्ण

			set_bit(CONF_REQ_SENT, &chan->conf_state);
			l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
				       l2cap_build_conf_req(chan, buf, माप(buf)), buf);
			chan->num_conf_req++;
		पूर्ण

		l2cap_chan_unlock(chan);
	पूर्ण

	mutex_unlock(&conn->chan_lock);
पूर्ण

अटल व्योम l2cap_le_conn_पढ़ोy(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा hci_dev *hdev = hcon->hdev;

	BT_DBG("%s conn %p", hdev->name, conn);

	/* For outgoing pairing which करोesn't necessarily have an
	 * associated socket (e.g. mgmt_pair_device).
	 */
	अगर (hcon->out)
		smp_conn_security(hcon, hcon->pending_sec_level);

	/* For LE slave connections, make sure the connection पूर्णांकerval
	 * is in the range of the minimum and maximum पूर्णांकerval that has
	 * been configured क्रम this connection. If not, then trigger
	 * the connection update procedure.
	 */
	अगर (hcon->role == HCI_ROLE_SLAVE &&
	    (hcon->le_conn_पूर्णांकerval < hcon->le_conn_min_पूर्णांकerval ||
	     hcon->le_conn_पूर्णांकerval > hcon->le_conn_max_पूर्णांकerval)) अणु
		काष्ठा l2cap_conn_param_update_req req;

		req.min = cpu_to_le16(hcon->le_conn_min_पूर्णांकerval);
		req.max = cpu_to_le16(hcon->le_conn_max_पूर्णांकerval);
		req.latency = cpu_to_le16(hcon->le_conn_latency);
		req.to_multiplier = cpu_to_le16(hcon->le_supv_समयout);

		l2cap_send_cmd(conn, l2cap_get_ident(conn),
			       L2CAP_CONN_PARAM_UPDATE_REQ, माप(req), &req);
	पूर्ण
पूर्ण

अटल व्योम l2cap_conn_पढ़ोy(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा l2cap_chan *chan;
	काष्ठा hci_conn *hcon = conn->hcon;

	BT_DBG("conn %p", conn);

	अगर (hcon->type == ACL_LINK)
		l2cap_request_info(conn);

	mutex_lock(&conn->chan_lock);

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु

		l2cap_chan_lock(chan);

		अगर (chan->scid == L2CAP_CID_A2MP) अणु
			l2cap_chan_unlock(chan);
			जारी;
		पूर्ण

		अगर (hcon->type == LE_LINK) अणु
			l2cap_le_start(chan);
		पूर्ण अन्यथा अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED) अणु
			अगर (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_DONE)
				l2cap_chan_पढ़ोy(chan);
		पूर्ण अन्यथा अगर (chan->state == BT_CONNECT) अणु
			l2cap_करो_start(chan);
		पूर्ण

		l2cap_chan_unlock(chan);
	पूर्ण

	mutex_unlock(&conn->chan_lock);

	अगर (hcon->type == LE_LINK)
		l2cap_le_conn_पढ़ोy(conn);

	queue_work(hcon->hdev->workqueue, &conn->pending_rx_work);
पूर्ण

/* Notअगरy sockets that we cannot guaranty reliability anymore */
अटल व्योम l2cap_conn_unreliable(काष्ठा l2cap_conn *conn, पूर्णांक err)
अणु
	काष्ठा l2cap_chan *chan;

	BT_DBG("conn %p", conn);

	mutex_lock(&conn->chan_lock);

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		अगर (test_bit(FLAG_FORCE_RELIABLE, &chan->flags))
			l2cap_chan_set_err(chan, err);
	पूर्ण

	mutex_unlock(&conn->chan_lock);
पूर्ण

अटल व्योम l2cap_info_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2cap_conn *conn = container_of(work, काष्ठा l2cap_conn,
					       info_समयr.work);

	conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_DONE;
	conn->info_ident = 0;

	l2cap_conn_start(conn);
पूर्ण

/*
 * l2cap_user
 * External modules can रेजिस्टर l2cap_user objects on l2cap_conn. The ->probe
 * callback is called during registration. The ->हटाओ callback is called
 * during unregistration.
 * An l2cap_user object can either be explicitly unरेजिस्टरed or when the
 * underlying l2cap_conn object is deleted. This guarantees that l2cap->hcon,
 * l2cap->hchan, .. are valid as दीर्घ as the हटाओ callback hasn't been called.
 * External modules must own a reference to the l2cap_conn object अगर they पूर्णांकend
 * to call l2cap_unरेजिस्टर_user(). The l2cap_conn object might get destroyed at
 * any समय अगर they करोn't.
 */

पूर्णांक l2cap_रेजिस्टर_user(काष्ठा l2cap_conn *conn, काष्ठा l2cap_user *user)
अणु
	काष्ठा hci_dev *hdev = conn->hcon->hdev;
	पूर्णांक ret;

	/* We need to check whether l2cap_conn is रेजिस्टरed. If it is not, we
	 * must not रेजिस्टर the l2cap_user. l2cap_conn_del() is unरेजिस्टरs
	 * l2cap_conn objects, but करोesn't provide its own locking. Instead, it
	 * relies on the parent hci_conn object to be locked. This itself relies
	 * on the hci_dev object to be locked. So we must lock the hci device
	 * here, too. */

	hci_dev_lock(hdev);

	अगर (!list_empty(&user->list)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* conn->hchan is शून्य after l2cap_conn_del() was called */
	अगर (!conn->hchan) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	ret = user->probe(conn, user);
	अगर (ret)
		जाओ out_unlock;

	list_add(&user->list, &conn->users);
	ret = 0;

out_unlock:
	hci_dev_unlock(hdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(l2cap_रेजिस्टर_user);

व्योम l2cap_unरेजिस्टर_user(काष्ठा l2cap_conn *conn, काष्ठा l2cap_user *user)
अणु
	काष्ठा hci_dev *hdev = conn->hcon->hdev;

	hci_dev_lock(hdev);

	अगर (list_empty(&user->list))
		जाओ out_unlock;

	list_del_init(&user->list);
	user->हटाओ(conn, user);

out_unlock:
	hci_dev_unlock(hdev);
पूर्ण
EXPORT_SYMBOL(l2cap_unरेजिस्टर_user);

अटल व्योम l2cap_unरेजिस्टर_all_users(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा l2cap_user *user;

	जबतक (!list_empty(&conn->users)) अणु
		user = list_first_entry(&conn->users, काष्ठा l2cap_user, list);
		list_del_init(&user->list);
		user->हटाओ(conn, user);
	पूर्ण
पूर्ण

अटल व्योम l2cap_conn_del(काष्ठा hci_conn *hcon, पूर्णांक err)
अणु
	काष्ठा l2cap_conn *conn = hcon->l2cap_data;
	काष्ठा l2cap_chan *chan, *l;

	अगर (!conn)
		वापस;

	BT_DBG("hcon %p conn %p, err %d", hcon, conn, err);

	kमुक्त_skb(conn->rx_skb);

	skb_queue_purge(&conn->pending_rx);

	/* We can not call flush_work(&conn->pending_rx_work) here since we
	 * might block अगर we are running on a worker from the same workqueue
	 * pending_rx_work is रुकोing on.
	 */
	अगर (work_pending(&conn->pending_rx_work))
		cancel_work_sync(&conn->pending_rx_work);

	अगर (work_pending(&conn->id_addr_update_work))
		cancel_work_sync(&conn->id_addr_update_work);

	l2cap_unरेजिस्टर_all_users(conn);

	/* Force the connection to be immediately dropped */
	hcon->disc_समयout = 0;

	mutex_lock(&conn->chan_lock);

	/* Kill channels */
	list_क्रम_each_entry_safe(chan, l, &conn->chan_l, list) अणु
		l2cap_chan_hold(chan);
		l2cap_chan_lock(chan);

		l2cap_chan_del(chan, err);

		chan->ops->बंद(chan);

		l2cap_chan_unlock(chan);
		l2cap_chan_put(chan);
	पूर्ण

	mutex_unlock(&conn->chan_lock);

	hci_chan_del(conn->hchan);

	अगर (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT)
		cancel_delayed_work_sync(&conn->info_समयr);

	hcon->l2cap_data = शून्य;
	conn->hchan = शून्य;
	l2cap_conn_put(conn);
पूर्ण

अटल व्योम l2cap_conn_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा l2cap_conn *conn = container_of(ref, काष्ठा l2cap_conn, ref);

	hci_conn_put(conn->hcon);
	kमुक्त(conn);
पूर्ण

काष्ठा l2cap_conn *l2cap_conn_get(काष्ठा l2cap_conn *conn)
अणु
	kref_get(&conn->ref);
	वापस conn;
पूर्ण
EXPORT_SYMBOL(l2cap_conn_get);

व्योम l2cap_conn_put(काष्ठा l2cap_conn *conn)
अणु
	kref_put(&conn->ref, l2cap_conn_मुक्त);
पूर्ण
EXPORT_SYMBOL(l2cap_conn_put);

/* ---- Socket पूर्णांकerface ---- */

/* Find socket with psm and source / destination bdaddr.
 * Returns बंदst match.
 */
अटल काष्ठा l2cap_chan *l2cap_global_chan_by_psm(पूर्णांक state, __le16 psm,
						   bdaddr_t *src,
						   bdaddr_t *dst,
						   u8 link_type)
अणु
	काष्ठा l2cap_chan *c, *c1 = शून्य;

	पढ़ो_lock(&chan_list_lock);

	list_क्रम_each_entry(c, &chan_list, global_l) अणु
		अगर (state && c->state != state)
			जारी;

		अगर (link_type == ACL_LINK && c->src_type != BDADDR_BREDR)
			जारी;

		अगर (link_type == LE_LINK && c->src_type == BDADDR_BREDR)
			जारी;

		अगर (c->psm == psm) अणु
			पूर्णांक src_match, dst_match;
			पूर्णांक src_any, dst_any;

			/* Exact match. */
			src_match = !bacmp(&c->src, src);
			dst_match = !bacmp(&c->dst, dst);
			अगर (src_match && dst_match) अणु
				l2cap_chan_hold(c);
				पढ़ो_unlock(&chan_list_lock);
				वापस c;
			पूर्ण

			/* Closest match */
			src_any = !bacmp(&c->src, BDADDR_ANY);
			dst_any = !bacmp(&c->dst, BDADDR_ANY);
			अगर ((src_match && dst_any) || (src_any && dst_match) ||
			    (src_any && dst_any))
				c1 = c;
		पूर्ण
	पूर्ण

	अगर (c1)
		l2cap_chan_hold(c1);

	पढ़ो_unlock(&chan_list_lock);

	वापस c1;
पूर्ण

अटल व्योम l2cap_monitor_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2cap_chan *chan = container_of(work, काष्ठा l2cap_chan,
					       monitor_समयr.work);

	BT_DBG("chan %p", chan);

	l2cap_chan_lock(chan);

	अगर (!chan->conn) अणु
		l2cap_chan_unlock(chan);
		l2cap_chan_put(chan);
		वापस;
	पूर्ण

	l2cap_tx(chan, शून्य, शून्य, L2CAP_EV_MONITOR_TO);

	l2cap_chan_unlock(chan);
	l2cap_chan_put(chan);
पूर्ण

अटल व्योम l2cap_retrans_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2cap_chan *chan = container_of(work, काष्ठा l2cap_chan,
					       retrans_समयr.work);

	BT_DBG("chan %p", chan);

	l2cap_chan_lock(chan);

	अगर (!chan->conn) अणु
		l2cap_chan_unlock(chan);
		l2cap_chan_put(chan);
		वापस;
	पूर्ण

	l2cap_tx(chan, शून्य, शून्य, L2CAP_EV_RETRANS_TO);
	l2cap_chan_unlock(chan);
	l2cap_chan_put(chan);
पूर्ण

अटल व्योम l2cap_streaming_send(काष्ठा l2cap_chan *chan,
				 काष्ठा sk_buff_head *skbs)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा l2cap_ctrl *control;

	BT_DBG("chan %p, skbs %p", chan, skbs);

	अगर (__chan_is_moving(chan))
		वापस;

	skb_queue_splice_tail_init(skbs, &chan->tx_q);

	जबतक (!skb_queue_empty(&chan->tx_q)) अणु

		skb = skb_dequeue(&chan->tx_q);

		bt_cb(skb)->l2cap.retries = 1;
		control = &bt_cb(skb)->l2cap;

		control->reqseq = 0;
		control->txseq = chan->next_tx_seq;

		__pack_control(chan, control, skb);

		अगर (chan->fcs == L2CAP_FCS_CRC16) अणु
			u16 fcs = crc16(0, (u8 *) skb->data, skb->len);
			put_unaligned_le16(fcs, skb_put(skb, L2CAP_FCS_SIZE));
		पूर्ण

		l2cap_करो_send(chan, skb);

		BT_DBG("Sent txseq %u", control->txseq);

		chan->next_tx_seq = __next_seq(chan, chan->next_tx_seq);
		chan->frames_sent++;
	पूर्ण
पूर्ण

अटल पूर्णांक l2cap_erपंचांग_send(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sk_buff *skb, *tx_skb;
	काष्ठा l2cap_ctrl *control;
	पूर्णांक sent = 0;

	BT_DBG("chan %p", chan);

	अगर (chan->state != BT_CONNECTED)
		वापस -ENOTCONN;

	अगर (test_bit(CONN_REMOTE_BUSY, &chan->conn_state))
		वापस 0;

	अगर (__chan_is_moving(chan))
		वापस 0;

	जबतक (chan->tx_send_head &&
	       chan->unacked_frames < chan->remote_tx_win &&
	       chan->tx_state == L2CAP_TX_STATE_XMIT) अणु

		skb = chan->tx_send_head;

		bt_cb(skb)->l2cap.retries = 1;
		control = &bt_cb(skb)->l2cap;

		अगर (test_and_clear_bit(CONN_SEND_FBIT, &chan->conn_state))
			control->final = 1;

		control->reqseq = chan->buffer_seq;
		chan->last_acked_seq = chan->buffer_seq;
		control->txseq = chan->next_tx_seq;

		__pack_control(chan, control, skb);

		अगर (chan->fcs == L2CAP_FCS_CRC16) अणु
			u16 fcs = crc16(0, (u8 *) skb->data, skb->len);
			put_unaligned_le16(fcs, skb_put(skb, L2CAP_FCS_SIZE));
		पूर्ण

		/* Clone after data has been modअगरied. Data is assumed to be
		   पढ़ो-only (क्रम locking purposes) on cloned sk_buffs.
		 */
		tx_skb = skb_clone(skb, GFP_KERNEL);

		अगर (!tx_skb)
			अवरोध;

		__set_retrans_समयr(chan);

		chan->next_tx_seq = __next_seq(chan, chan->next_tx_seq);
		chan->unacked_frames++;
		chan->frames_sent++;
		sent++;

		अगर (skb_queue_is_last(&chan->tx_q, skb))
			chan->tx_send_head = शून्य;
		अन्यथा
			chan->tx_send_head = skb_queue_next(&chan->tx_q, skb);

		l2cap_करो_send(chan, tx_skb);
		BT_DBG("Sent txseq %u", control->txseq);
	पूर्ण

	BT_DBG("Sent %d, %u unacked, %u in ERTM queue", sent,
	       chan->unacked_frames, skb_queue_len(&chan->tx_q));

	वापस sent;
पूर्ण

अटल व्योम l2cap_erपंचांग_resend(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_ctrl control;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *tx_skb;
	u16 seq;

	BT_DBG("chan %p", chan);

	अगर (test_bit(CONN_REMOTE_BUSY, &chan->conn_state))
		वापस;

	अगर (__chan_is_moving(chan))
		वापस;

	जबतक (chan->retrans_list.head != L2CAP_SEQ_LIST_CLEAR) अणु
		seq = l2cap_seq_list_pop(&chan->retrans_list);

		skb = l2cap_erपंचांग_seq_in_queue(&chan->tx_q, seq);
		अगर (!skb) अणु
			BT_DBG("Error: Can't retransmit seq %d, frame missing",
			       seq);
			जारी;
		पूर्ण

		bt_cb(skb)->l2cap.retries++;
		control = bt_cb(skb)->l2cap;

		अगर (chan->max_tx != 0 &&
		    bt_cb(skb)->l2cap.retries > chan->max_tx) अणु
			BT_DBG("Retry limit exceeded (%d)", chan->max_tx);
			l2cap_send_disconn_req(chan, ECONNRESET);
			l2cap_seq_list_clear(&chan->retrans_list);
			अवरोध;
		पूर्ण

		control.reqseq = chan->buffer_seq;
		अगर (test_and_clear_bit(CONN_SEND_FBIT, &chan->conn_state))
			control.final = 1;
		अन्यथा
			control.final = 0;

		अगर (skb_cloned(skb)) अणु
			/* Cloned sk_buffs are पढ़ो-only, so we need a
			 * ग_लिखोable copy
			 */
			tx_skb = skb_copy(skb, GFP_KERNEL);
		पूर्ण अन्यथा अणु
			tx_skb = skb_clone(skb, GFP_KERNEL);
		पूर्ण

		अगर (!tx_skb) अणु
			l2cap_seq_list_clear(&chan->retrans_list);
			अवरोध;
		पूर्ण

		/* Update skb contents */
		अगर (test_bit(FLAG_EXT_CTRL, &chan->flags)) अणु
			put_unaligned_le32(__pack_extended_control(&control),
					   tx_skb->data + L2CAP_HDR_SIZE);
		पूर्ण अन्यथा अणु
			put_unaligned_le16(__pack_enhanced_control(&control),
					   tx_skb->data + L2CAP_HDR_SIZE);
		पूर्ण

		/* Update FCS */
		अगर (chan->fcs == L2CAP_FCS_CRC16) अणु
			u16 fcs = crc16(0, (u8 *) tx_skb->data,
					tx_skb->len - L2CAP_FCS_SIZE);
			put_unaligned_le16(fcs, skb_tail_poपूर्णांकer(tx_skb) -
						L2CAP_FCS_SIZE);
		पूर्ण

		l2cap_करो_send(chan, tx_skb);

		BT_DBG("Resent txseq %d", control.txseq);

		chan->last_acked_seq = chan->buffer_seq;
	पूर्ण
पूर्ण

अटल व्योम l2cap_retransmit(काष्ठा l2cap_chan *chan,
			     काष्ठा l2cap_ctrl *control)
अणु
	BT_DBG("chan %p, control %p", chan, control);

	l2cap_seq_list_append(&chan->retrans_list, control->reqseq);
	l2cap_erपंचांग_resend(chan);
पूर्ण

अटल व्योम l2cap_retransmit_all(काष्ठा l2cap_chan *chan,
				 काष्ठा l2cap_ctrl *control)
अणु
	काष्ठा sk_buff *skb;

	BT_DBG("chan %p, control %p", chan, control);

	अगर (control->poll)
		set_bit(CONN_SEND_FBIT, &chan->conn_state);

	l2cap_seq_list_clear(&chan->retrans_list);

	अगर (test_bit(CONN_REMOTE_BUSY, &chan->conn_state))
		वापस;

	अगर (chan->unacked_frames) अणु
		skb_queue_walk(&chan->tx_q, skb) अणु
			अगर (bt_cb(skb)->l2cap.txseq == control->reqseq ||
			    skb == chan->tx_send_head)
				अवरोध;
		पूर्ण

		skb_queue_walk_from(&chan->tx_q, skb) अणु
			अगर (skb == chan->tx_send_head)
				अवरोध;

			l2cap_seq_list_append(&chan->retrans_list,
					      bt_cb(skb)->l2cap.txseq);
		पूर्ण

		l2cap_erपंचांग_resend(chan);
	पूर्ण
पूर्ण

अटल व्योम l2cap_send_ack(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_ctrl control;
	u16 frames_to_ack = __seq_offset(chan, chan->buffer_seq,
					 chan->last_acked_seq);
	पूर्णांक threshold;

	BT_DBG("chan %p last_acked_seq %d buffer_seq %d",
	       chan, chan->last_acked_seq, chan->buffer_seq);

	स_रखो(&control, 0, माप(control));
	control.sframe = 1;

	अगर (test_bit(CONN_LOCAL_BUSY, &chan->conn_state) &&
	    chan->rx_state == L2CAP_RX_STATE_RECV) अणु
		__clear_ack_समयr(chan);
		control.super = L2CAP_SUPER_RNR;
		control.reqseq = chan->buffer_seq;
		l2cap_send_sframe(chan, &control);
	पूर्ण अन्यथा अणु
		अगर (!test_bit(CONN_REMOTE_BUSY, &chan->conn_state)) अणु
			l2cap_erपंचांग_send(chan);
			/* If any i-frames were sent, they included an ack */
			अगर (chan->buffer_seq == chan->last_acked_seq)
				frames_to_ack = 0;
		पूर्ण

		/* Ack now अगर the winकरोw is 3/4ths full.
		 * Calculate without mul or भाग
		 */
		threshold = chan->ack_win;
		threshold += threshold << 1;
		threshold >>= 2;

		BT_DBG("frames_to_ack %u, threshold %d", frames_to_ack,
		       threshold);

		अगर (frames_to_ack >= threshold) अणु
			__clear_ack_समयr(chan);
			control.super = L2CAP_SUPER_RR;
			control.reqseq = chan->buffer_seq;
			l2cap_send_sframe(chan, &control);
			frames_to_ack = 0;
		पूर्ण

		अगर (frames_to_ack)
			__set_ack_समयr(chan);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_skbuff_fromiovec(काष्ठा l2cap_chan *chan,
					 काष्ठा msghdr *msg, पूर्णांक len,
					 पूर्णांक count, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा sk_buff **frag;
	पूर्णांक sent = 0;

	अगर (!copy_from_iter_full(skb_put(skb, count), count, &msg->msg_iter))
		वापस -EFAULT;

	sent += count;
	len  -= count;

	/* Continuation fragments (no L2CAP header) */
	frag = &skb_shinfo(skb)->frag_list;
	जबतक (len) अणु
		काष्ठा sk_buff *पंचांगp;

		count = min_t(अचिन्हित पूर्णांक, conn->mtu, len);

		पंचांगp = chan->ops->alloc_skb(chan, 0, count,
					   msg->msg_flags & MSG_DONTWAIT);
		अगर (IS_ERR(पंचांगp))
			वापस PTR_ERR(पंचांगp);

		*frag = पंचांगp;

		अगर (!copy_from_iter_full(skb_put(*frag, count), count,
				   &msg->msg_iter))
			वापस -EFAULT;

		sent += count;
		len  -= count;

		skb->len += (*frag)->len;
		skb->data_len += (*frag)->len;

		frag = &(*frag)->next;
	पूर्ण

	वापस sent;
पूर्ण

अटल काष्ठा sk_buff *l2cap_create_connless_pdu(काष्ठा l2cap_chan *chan,
						 काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा sk_buff *skb;
	पूर्णांक err, count, hlen = L2CAP_HDR_SIZE + L2CAP_PSMLEN_SIZE;
	काष्ठा l2cap_hdr *lh;

	BT_DBG("chan %p psm 0x%2.2x len %zu", chan,
	       __le16_to_cpu(chan->psm), len);

	count = min_t(अचिन्हित पूर्णांक, (conn->mtu - hlen), len);

	skb = chan->ops->alloc_skb(chan, hlen, count,
				   msg->msg_flags & MSG_DONTWAIT);
	अगर (IS_ERR(skb))
		वापस skb;

	/* Create L2CAP header */
	lh = skb_put(skb, L2CAP_HDR_SIZE);
	lh->cid = cpu_to_le16(chan->dcid);
	lh->len = cpu_to_le16(len + L2CAP_PSMLEN_SIZE);
	put_unaligned(chan->psm, (__le16 *) skb_put(skb, L2CAP_PSMLEN_SIZE));

	err = l2cap_skbuff_fromiovec(chan, msg, len, count, skb);
	अगर (unlikely(err < 0)) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(err);
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *l2cap_create_basic_pdu(काष्ठा l2cap_chan *chan,
					      काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा sk_buff *skb;
	पूर्णांक err, count;
	काष्ठा l2cap_hdr *lh;

	BT_DBG("chan %p len %zu", chan, len);

	count = min_t(अचिन्हित पूर्णांक, (conn->mtu - L2CAP_HDR_SIZE), len);

	skb = chan->ops->alloc_skb(chan, L2CAP_HDR_SIZE, count,
				   msg->msg_flags & MSG_DONTWAIT);
	अगर (IS_ERR(skb))
		वापस skb;

	/* Create L2CAP header */
	lh = skb_put(skb, L2CAP_HDR_SIZE);
	lh->cid = cpu_to_le16(chan->dcid);
	lh->len = cpu_to_le16(len);

	err = l2cap_skbuff_fromiovec(chan, msg, len, count, skb);
	अगर (unlikely(err < 0)) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(err);
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *l2cap_create_अगरrame_pdu(काष्ठा l2cap_chan *chan,
					       काष्ठा msghdr *msg, माप_प्रकार len,
					       u16 sdulen)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा sk_buff *skb;
	पूर्णांक err, count, hlen;
	काष्ठा l2cap_hdr *lh;

	BT_DBG("chan %p len %zu", chan, len);

	अगर (!conn)
		वापस ERR_PTR(-ENOTCONN);

	hlen = __erपंचांग_hdr_size(chan);

	अगर (sdulen)
		hlen += L2CAP_SDULEN_SIZE;

	अगर (chan->fcs == L2CAP_FCS_CRC16)
		hlen += L2CAP_FCS_SIZE;

	count = min_t(अचिन्हित पूर्णांक, (conn->mtu - hlen), len);

	skb = chan->ops->alloc_skb(chan, hlen, count,
				   msg->msg_flags & MSG_DONTWAIT);
	अगर (IS_ERR(skb))
		वापस skb;

	/* Create L2CAP header */
	lh = skb_put(skb, L2CAP_HDR_SIZE);
	lh->cid = cpu_to_le16(chan->dcid);
	lh->len = cpu_to_le16(len + (hlen - L2CAP_HDR_SIZE));

	/* Control header is populated later */
	अगर (test_bit(FLAG_EXT_CTRL, &chan->flags))
		put_unaligned_le32(0, skb_put(skb, L2CAP_EXT_CTRL_SIZE));
	अन्यथा
		put_unaligned_le16(0, skb_put(skb, L2CAP_ENH_CTRL_SIZE));

	अगर (sdulen)
		put_unaligned_le16(sdulen, skb_put(skb, L2CAP_SDULEN_SIZE));

	err = l2cap_skbuff_fromiovec(chan, msg, len, count, skb);
	अगर (unlikely(err < 0)) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(err);
	पूर्ण

	bt_cb(skb)->l2cap.fcs = chan->fcs;
	bt_cb(skb)->l2cap.retries = 0;
	वापस skb;
पूर्ण

अटल पूर्णांक l2cap_segment_sdu(काष्ठा l2cap_chan *chan,
			     काष्ठा sk_buff_head *seg_queue,
			     काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sk_buff *skb;
	u16 sdu_len;
	माप_प्रकार pdu_len;
	u8 sar;

	BT_DBG("chan %p, msg %p, len %zu", chan, msg, len);

	/* It is critical that ERTM PDUs fit in a single HCI fragment,
	 * so fragmented skbs are not used.  The HCI layer's handling
	 * of fragmented skbs is not compatible with ERTM's queueing.
	 */

	/* PDU size is derived from the HCI MTU */
	pdu_len = chan->conn->mtu;

	/* Constrain PDU size क्रम BR/EDR connections */
	अगर (!chan->hs_hcon)
		pdu_len = min_t(माप_प्रकार, pdu_len, L2CAP_BREDR_MAX_PAYLOAD);

	/* Adjust क्रम largest possible L2CAP overhead. */
	अगर (chan->fcs)
		pdu_len -= L2CAP_FCS_SIZE;

	pdu_len -= __erपंचांग_hdr_size(chan);

	/* Remote device may have requested smaller PDUs */
	pdu_len = min_t(माप_प्रकार, pdu_len, chan->remote_mps);

	अगर (len <= pdu_len) अणु
		sar = L2CAP_SAR_UNSEGMENTED;
		sdu_len = 0;
		pdu_len = len;
	पूर्ण अन्यथा अणु
		sar = L2CAP_SAR_START;
		sdu_len = len;
	पूर्ण

	जबतक (len > 0) अणु
		skb = l2cap_create_अगरrame_pdu(chan, msg, pdu_len, sdu_len);

		अगर (IS_ERR(skb)) अणु
			__skb_queue_purge(seg_queue);
			वापस PTR_ERR(skb);
		पूर्ण

		bt_cb(skb)->l2cap.sar = sar;
		__skb_queue_tail(seg_queue, skb);

		len -= pdu_len;
		अगर (sdu_len)
			sdu_len = 0;

		अगर (len <= pdu_len) अणु
			sar = L2CAP_SAR_END;
			pdu_len = len;
		पूर्ण अन्यथा अणु
			sar = L2CAP_SAR_CONTINUE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *l2cap_create_le_flowctl_pdu(काष्ठा l2cap_chan *chan,
						   काष्ठा msghdr *msg,
						   माप_प्रकार len, u16 sdulen)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा sk_buff *skb;
	पूर्णांक err, count, hlen;
	काष्ठा l2cap_hdr *lh;

	BT_DBG("chan %p len %zu", chan, len);

	अगर (!conn)
		वापस ERR_PTR(-ENOTCONN);

	hlen = L2CAP_HDR_SIZE;

	अगर (sdulen)
		hlen += L2CAP_SDULEN_SIZE;

	count = min_t(अचिन्हित पूर्णांक, (conn->mtu - hlen), len);

	skb = chan->ops->alloc_skb(chan, hlen, count,
				   msg->msg_flags & MSG_DONTWAIT);
	अगर (IS_ERR(skb))
		वापस skb;

	/* Create L2CAP header */
	lh = skb_put(skb, L2CAP_HDR_SIZE);
	lh->cid = cpu_to_le16(chan->dcid);
	lh->len = cpu_to_le16(len + (hlen - L2CAP_HDR_SIZE));

	अगर (sdulen)
		put_unaligned_le16(sdulen, skb_put(skb, L2CAP_SDULEN_SIZE));

	err = l2cap_skbuff_fromiovec(chan, msg, len, count, skb);
	अगर (unlikely(err < 0)) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(err);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक l2cap_segment_le_sdu(काष्ठा l2cap_chan *chan,
				काष्ठा sk_buff_head *seg_queue,
				काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sk_buff *skb;
	माप_प्रकार pdu_len;
	u16 sdu_len;

	BT_DBG("chan %p, msg %p, len %zu", chan, msg, len);

	sdu_len = len;
	pdu_len = chan->remote_mps - L2CAP_SDULEN_SIZE;

	जबतक (len > 0) अणु
		अगर (len <= pdu_len)
			pdu_len = len;

		skb = l2cap_create_le_flowctl_pdu(chan, msg, pdu_len, sdu_len);
		अगर (IS_ERR(skb)) अणु
			__skb_queue_purge(seg_queue);
			वापस PTR_ERR(skb);
		पूर्ण

		__skb_queue_tail(seg_queue, skb);

		len -= pdu_len;

		अगर (sdu_len) अणु
			sdu_len = 0;
			pdu_len += L2CAP_SDULEN_SIZE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम l2cap_le_flowctl_send(काष्ठा l2cap_chan *chan)
अणु
	पूर्णांक sent = 0;

	BT_DBG("chan %p", chan);

	जबतक (chan->tx_credits && !skb_queue_empty(&chan->tx_q)) अणु
		l2cap_करो_send(chan, skb_dequeue(&chan->tx_q));
		chan->tx_credits--;
		sent++;
	पूर्ण

	BT_DBG("Sent %d credits %u queued %u", sent, chan->tx_credits,
	       skb_queue_len(&chan->tx_q));
पूर्ण

पूर्णांक l2cap_chan_send(काष्ठा l2cap_chan *chan, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;
	काष्ठा sk_buff_head seg_queue;

	अगर (!chan->conn)
		वापस -ENOTCONN;

	/* Connectionless channel */
	अगर (chan->chan_type == L2CAP_CHAN_CONN_LESS) अणु
		skb = l2cap_create_connless_pdu(chan, msg, len);
		अगर (IS_ERR(skb))
			वापस PTR_ERR(skb);

		/* Channel lock is released beक्रमe requesting new skb and then
		 * reacquired thus we need to recheck channel state.
		 */
		अगर (chan->state != BT_CONNECTED) अणु
			kमुक्त_skb(skb);
			वापस -ENOTCONN;
		पूर्ण

		l2cap_करो_send(chan, skb);
		वापस len;
	पूर्ण

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_LE_FLOWCTL:
	हाल L2CAP_MODE_EXT_FLOWCTL:
		/* Check outgoing MTU */
		अगर (len > chan->omtu)
			वापस -EMSGSIZE;

		__skb_queue_head_init(&seg_queue);

		err = l2cap_segment_le_sdu(chan, &seg_queue, msg, len);

		अगर (chan->state != BT_CONNECTED) अणु
			__skb_queue_purge(&seg_queue);
			err = -ENOTCONN;
		पूर्ण

		अगर (err)
			वापस err;

		skb_queue_splice_tail_init(&seg_queue, &chan->tx_q);

		l2cap_le_flowctl_send(chan);

		अगर (!chan->tx_credits)
			chan->ops->suspend(chan);

		err = len;

		अवरोध;

	हाल L2CAP_MODE_BASIC:
		/* Check outgoing MTU */
		अगर (len > chan->omtu)
			वापस -EMSGSIZE;

		/* Create a basic PDU */
		skb = l2cap_create_basic_pdu(chan, msg, len);
		अगर (IS_ERR(skb))
			वापस PTR_ERR(skb);

		/* Channel lock is released beक्रमe requesting new skb and then
		 * reacquired thus we need to recheck channel state.
		 */
		अगर (chan->state != BT_CONNECTED) अणु
			kमुक्त_skb(skb);
			वापस -ENOTCONN;
		पूर्ण

		l2cap_करो_send(chan, skb);
		err = len;
		अवरोध;

	हाल L2CAP_MODE_ERTM:
	हाल L2CAP_MODE_STREAMING:
		/* Check outgoing MTU */
		अगर (len > chan->omtu) अणु
			err = -EMSGSIZE;
			अवरोध;
		पूर्ण

		__skb_queue_head_init(&seg_queue);

		/* Do segmentation beक्रमe calling in to the state machine,
		 * since it's possible to block जबतक रुकोing क्रम memory
		 * allocation.
		 */
		err = l2cap_segment_sdu(chan, &seg_queue, msg, len);

		/* The channel could have been बंदd जबतक segmenting,
		 * check that it is still connected.
		 */
		अगर (chan->state != BT_CONNECTED) अणु
			__skb_queue_purge(&seg_queue);
			err = -ENOTCONN;
		पूर्ण

		अगर (err)
			अवरोध;

		अगर (chan->mode == L2CAP_MODE_ERTM)
			l2cap_tx(chan, शून्य, &seg_queue, L2CAP_EV_DATA_REQUEST);
		अन्यथा
			l2cap_streaming_send(chan, &seg_queue);

		err = len;

		/* If the skbs were not queued क्रम sending, they'll still be in
		 * seg_queue and need to be purged.
		 */
		__skb_queue_purge(&seg_queue);
		अवरोध;

	शेष:
		BT_DBG("bad state %1.1x", chan->mode);
		err = -EBADFD;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(l2cap_chan_send);

अटल व्योम l2cap_send_srej(काष्ठा l2cap_chan *chan, u16 txseq)
अणु
	काष्ठा l2cap_ctrl control;
	u16 seq;

	BT_DBG("chan %p, txseq %u", chan, txseq);

	स_रखो(&control, 0, माप(control));
	control.sframe = 1;
	control.super = L2CAP_SUPER_SREJ;

	क्रम (seq = chan->expected_tx_seq; seq != txseq;
	     seq = __next_seq(chan, seq)) अणु
		अगर (!l2cap_erपंचांग_seq_in_queue(&chan->srej_q, seq)) अणु
			control.reqseq = seq;
			l2cap_send_sframe(chan, &control);
			l2cap_seq_list_append(&chan->srej_list, seq);
		पूर्ण
	पूर्ण

	chan->expected_tx_seq = __next_seq(chan, txseq);
पूर्ण

अटल व्योम l2cap_send_srej_tail(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_ctrl control;

	BT_DBG("chan %p", chan);

	अगर (chan->srej_list.tail == L2CAP_SEQ_LIST_CLEAR)
		वापस;

	स_रखो(&control, 0, माप(control));
	control.sframe = 1;
	control.super = L2CAP_SUPER_SREJ;
	control.reqseq = chan->srej_list.tail;
	l2cap_send_sframe(chan, &control);
पूर्ण

अटल व्योम l2cap_send_srej_list(काष्ठा l2cap_chan *chan, u16 txseq)
अणु
	काष्ठा l2cap_ctrl control;
	u16 initial_head;
	u16 seq;

	BT_DBG("chan %p, txseq %u", chan, txseq);

	स_रखो(&control, 0, माप(control));
	control.sframe = 1;
	control.super = L2CAP_SUPER_SREJ;

	/* Capture initial list head to allow only one pass through the list. */
	initial_head = chan->srej_list.head;

	करो अणु
		seq = l2cap_seq_list_pop(&chan->srej_list);
		अगर (seq == txseq || seq == L2CAP_SEQ_LIST_CLEAR)
			अवरोध;

		control.reqseq = seq;
		l2cap_send_sframe(chan, &control);
		l2cap_seq_list_append(&chan->srej_list, seq);
	पूर्ण जबतक (chan->srej_list.head != initial_head);
पूर्ण

अटल व्योम l2cap_process_reqseq(काष्ठा l2cap_chan *chan, u16 reqseq)
अणु
	काष्ठा sk_buff *acked_skb;
	u16 ackseq;

	BT_DBG("chan %p, reqseq %u", chan, reqseq);

	अगर (chan->unacked_frames == 0 || reqseq == chan->expected_ack_seq)
		वापस;

	BT_DBG("expected_ack_seq %u, unacked_frames %u",
	       chan->expected_ack_seq, chan->unacked_frames);

	क्रम (ackseq = chan->expected_ack_seq; ackseq != reqseq;
	     ackseq = __next_seq(chan, ackseq)) अणु

		acked_skb = l2cap_erपंचांग_seq_in_queue(&chan->tx_q, ackseq);
		अगर (acked_skb) अणु
			skb_unlink(acked_skb, &chan->tx_q);
			kमुक्त_skb(acked_skb);
			chan->unacked_frames--;
		पूर्ण
	पूर्ण

	chan->expected_ack_seq = reqseq;

	अगर (chan->unacked_frames == 0)
		__clear_retrans_समयr(chan);

	BT_DBG("unacked_frames %u", chan->unacked_frames);
पूर्ण

अटल व्योम l2cap_पात_rx_srej_sent(काष्ठा l2cap_chan *chan)
अणु
	BT_DBG("chan %p", chan);

	chan->expected_tx_seq = chan->buffer_seq;
	l2cap_seq_list_clear(&chan->srej_list);
	skb_queue_purge(&chan->srej_q);
	chan->rx_state = L2CAP_RX_STATE_RECV;
पूर्ण

अटल व्योम l2cap_tx_state_xmit(काष्ठा l2cap_chan *chan,
				काष्ठा l2cap_ctrl *control,
				काष्ठा sk_buff_head *skbs, u8 event)
अणु
	BT_DBG("chan %p, control %p, skbs %p, event %d", chan, control, skbs,
	       event);

	चयन (event) अणु
	हाल L2CAP_EV_DATA_REQUEST:
		अगर (chan->tx_send_head == शून्य)
			chan->tx_send_head = skb_peek(skbs);

		skb_queue_splice_tail_init(skbs, &chan->tx_q);
		l2cap_erपंचांग_send(chan);
		अवरोध;
	हाल L2CAP_EV_LOCAL_BUSY_DETECTED:
		BT_DBG("Enter LOCAL_BUSY");
		set_bit(CONN_LOCAL_BUSY, &chan->conn_state);

		अगर (chan->rx_state == L2CAP_RX_STATE_SREJ_SENT) अणु
			/* The SREJ_SENT state must be पातed अगर we are to
			 * enter the LOCAL_BUSY state.
			 */
			l2cap_पात_rx_srej_sent(chan);
		पूर्ण

		l2cap_send_ack(chan);

		अवरोध;
	हाल L2CAP_EV_LOCAL_BUSY_CLEAR:
		BT_DBG("Exit LOCAL_BUSY");
		clear_bit(CONN_LOCAL_BUSY, &chan->conn_state);

		अगर (test_bit(CONN_RNR_SENT, &chan->conn_state)) अणु
			काष्ठा l2cap_ctrl local_control;

			स_रखो(&local_control, 0, माप(local_control));
			local_control.sframe = 1;
			local_control.super = L2CAP_SUPER_RR;
			local_control.poll = 1;
			local_control.reqseq = chan->buffer_seq;
			l2cap_send_sframe(chan, &local_control);

			chan->retry_count = 1;
			__set_monitor_समयr(chan);
			chan->tx_state = L2CAP_TX_STATE_WAIT_F;
		पूर्ण
		अवरोध;
	हाल L2CAP_EV_RECV_REQSEQ_AND_FBIT:
		l2cap_process_reqseq(chan, control->reqseq);
		अवरोध;
	हाल L2CAP_EV_EXPLICIT_POLL:
		l2cap_send_rr_or_rnr(chan, 1);
		chan->retry_count = 1;
		__set_monitor_समयr(chan);
		__clear_ack_समयr(chan);
		chan->tx_state = L2CAP_TX_STATE_WAIT_F;
		अवरोध;
	हाल L2CAP_EV_RETRANS_TO:
		l2cap_send_rr_or_rnr(chan, 1);
		chan->retry_count = 1;
		__set_monitor_समयr(chan);
		chan->tx_state = L2CAP_TX_STATE_WAIT_F;
		अवरोध;
	हाल L2CAP_EV_RECV_FBIT:
		/* Nothing to process */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम l2cap_tx_state_रुको_f(काष्ठा l2cap_chan *chan,
				  काष्ठा l2cap_ctrl *control,
				  काष्ठा sk_buff_head *skbs, u8 event)
अणु
	BT_DBG("chan %p, control %p, skbs %p, event %d", chan, control, skbs,
	       event);

	चयन (event) अणु
	हाल L2CAP_EV_DATA_REQUEST:
		अगर (chan->tx_send_head == शून्य)
			chan->tx_send_head = skb_peek(skbs);
		/* Queue data, but करोn't send. */
		skb_queue_splice_tail_init(skbs, &chan->tx_q);
		अवरोध;
	हाल L2CAP_EV_LOCAL_BUSY_DETECTED:
		BT_DBG("Enter LOCAL_BUSY");
		set_bit(CONN_LOCAL_BUSY, &chan->conn_state);

		अगर (chan->rx_state == L2CAP_RX_STATE_SREJ_SENT) अणु
			/* The SREJ_SENT state must be पातed अगर we are to
			 * enter the LOCAL_BUSY state.
			 */
			l2cap_पात_rx_srej_sent(chan);
		पूर्ण

		l2cap_send_ack(chan);

		अवरोध;
	हाल L2CAP_EV_LOCAL_BUSY_CLEAR:
		BT_DBG("Exit LOCAL_BUSY");
		clear_bit(CONN_LOCAL_BUSY, &chan->conn_state);

		अगर (test_bit(CONN_RNR_SENT, &chan->conn_state)) अणु
			काष्ठा l2cap_ctrl local_control;
			स_रखो(&local_control, 0, माप(local_control));
			local_control.sframe = 1;
			local_control.super = L2CAP_SUPER_RR;
			local_control.poll = 1;
			local_control.reqseq = chan->buffer_seq;
			l2cap_send_sframe(chan, &local_control);

			chan->retry_count = 1;
			__set_monitor_समयr(chan);
			chan->tx_state = L2CAP_TX_STATE_WAIT_F;
		पूर्ण
		अवरोध;
	हाल L2CAP_EV_RECV_REQSEQ_AND_FBIT:
		l2cap_process_reqseq(chan, control->reqseq);
		fallthrough;

	हाल L2CAP_EV_RECV_FBIT:
		अगर (control && control->final) अणु
			__clear_monitor_समयr(chan);
			अगर (chan->unacked_frames > 0)
				__set_retrans_समयr(chan);
			chan->retry_count = 0;
			chan->tx_state = L2CAP_TX_STATE_XMIT;
			BT_DBG("recv fbit tx_state 0x2.2%x", chan->tx_state);
		पूर्ण
		अवरोध;
	हाल L2CAP_EV_EXPLICIT_POLL:
		/* Ignore */
		अवरोध;
	हाल L2CAP_EV_MONITOR_TO:
		अगर (chan->max_tx == 0 || chan->retry_count < chan->max_tx) अणु
			l2cap_send_rr_or_rnr(chan, 1);
			__set_monitor_समयr(chan);
			chan->retry_count++;
		पूर्ण अन्यथा अणु
			l2cap_send_disconn_req(chan, ECONNABORTED);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम l2cap_tx(काष्ठा l2cap_chan *chan, काष्ठा l2cap_ctrl *control,
		     काष्ठा sk_buff_head *skbs, u8 event)
अणु
	BT_DBG("chan %p, control %p, skbs %p, event %d, state %d",
	       chan, control, skbs, event, chan->tx_state);

	चयन (chan->tx_state) अणु
	हाल L2CAP_TX_STATE_XMIT:
		l2cap_tx_state_xmit(chan, control, skbs, event);
		अवरोध;
	हाल L2CAP_TX_STATE_WAIT_F:
		l2cap_tx_state_रुको_f(chan, control, skbs, event);
		अवरोध;
	शेष:
		/* Ignore event */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम l2cap_pass_to_tx(काष्ठा l2cap_chan *chan,
			     काष्ठा l2cap_ctrl *control)
अणु
	BT_DBG("chan %p, control %p", chan, control);
	l2cap_tx(chan, control, शून्य, L2CAP_EV_RECV_REQSEQ_AND_FBIT);
पूर्ण

अटल व्योम l2cap_pass_to_tx_fbit(काष्ठा l2cap_chan *chan,
				  काष्ठा l2cap_ctrl *control)
अणु
	BT_DBG("chan %p, control %p", chan, control);
	l2cap_tx(chan, control, शून्य, L2CAP_EV_RECV_FBIT);
पूर्ण

/* Copy frame to all raw sockets on that connection */
अटल व्योम l2cap_raw_recv(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा l2cap_chan *chan;

	BT_DBG("conn %p", conn);

	mutex_lock(&conn->chan_lock);

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		अगर (chan->chan_type != L2CAP_CHAN_RAW)
			जारी;

		/* Don't send frame to the channel it came from */
		अगर (bt_cb(skb)->l2cap.chan == chan)
			जारी;

		nskb = skb_clone(skb, GFP_KERNEL);
		अगर (!nskb)
			जारी;
		अगर (chan->ops->recv(chan, nskb))
			kमुक्त_skb(nskb);
	पूर्ण

	mutex_unlock(&conn->chan_lock);
पूर्ण

/* ---- L2CAP संकेतling commands ---- */
अटल काष्ठा sk_buff *l2cap_build_cmd(काष्ठा l2cap_conn *conn, u8 code,
				       u8 ident, u16 dlen, व्योम *data)
अणु
	काष्ठा sk_buff *skb, **frag;
	काष्ठा l2cap_cmd_hdr *cmd;
	काष्ठा l2cap_hdr *lh;
	पूर्णांक len, count;

	BT_DBG("conn %p, code 0x%2.2x, ident 0x%2.2x, len %u",
	       conn, code, ident, dlen);

	अगर (conn->mtu < L2CAP_HDR_SIZE + L2CAP_CMD_HDR_SIZE)
		वापस शून्य;

	len = L2CAP_HDR_SIZE + L2CAP_CMD_HDR_SIZE + dlen;
	count = min_t(अचिन्हित पूर्णांक, conn->mtu, len);

	skb = bt_skb_alloc(count, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	lh = skb_put(skb, L2CAP_HDR_SIZE);
	lh->len = cpu_to_le16(L2CAP_CMD_HDR_SIZE + dlen);

	अगर (conn->hcon->type == LE_LINK)
		lh->cid = cpu_to_le16(L2CAP_CID_LE_SIGNALING);
	अन्यथा
		lh->cid = cpu_to_le16(L2CAP_CID_SIGNALING);

	cmd = skb_put(skb, L2CAP_CMD_HDR_SIZE);
	cmd->code  = code;
	cmd->ident = ident;
	cmd->len   = cpu_to_le16(dlen);

	अगर (dlen) अणु
		count -= L2CAP_HDR_SIZE + L2CAP_CMD_HDR_SIZE;
		skb_put_data(skb, data, count);
		data += count;
	पूर्ण

	len -= skb->len;

	/* Continuation fragments (no L2CAP header) */
	frag = &skb_shinfo(skb)->frag_list;
	जबतक (len) अणु
		count = min_t(अचिन्हित पूर्णांक, conn->mtu, len);

		*frag = bt_skb_alloc(count, GFP_KERNEL);
		अगर (!*frag)
			जाओ fail;

		skb_put_data(*frag, data, count);

		len  -= count;
		data += count;

		frag = &(*frag)->next;
	पूर्ण

	वापस skb;

fail:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_get_conf_opt(व्योम **ptr, पूर्णांक *type, पूर्णांक *olen,
				     अचिन्हित दीर्घ *val)
अणु
	काष्ठा l2cap_conf_opt *opt = *ptr;
	पूर्णांक len;

	len = L2CAP_CONF_OPT_SIZE + opt->len;
	*ptr += len;

	*type = opt->type;
	*olen = opt->len;

	चयन (opt->len) अणु
	हाल 1:
		*val = *((u8 *) opt->val);
		अवरोध;

	हाल 2:
		*val = get_unaligned_le16(opt->val);
		अवरोध;

	हाल 4:
		*val = get_unaligned_le32(opt->val);
		अवरोध;

	शेष:
		*val = (अचिन्हित दीर्घ) opt->val;
		अवरोध;
	पूर्ण

	BT_DBG("type 0x%2.2x len %u val 0x%lx", *type, opt->len, *val);
	वापस len;
पूर्ण

अटल व्योम l2cap_add_conf_opt(व्योम **ptr, u8 type, u8 len, अचिन्हित दीर्घ val, माप_प्रकार size)
अणु
	काष्ठा l2cap_conf_opt *opt = *ptr;

	BT_DBG("type 0x%2.2x len %u val 0x%lx", type, len, val);

	अगर (size < L2CAP_CONF_OPT_SIZE + len)
		वापस;

	opt->type = type;
	opt->len  = len;

	चयन (len) अणु
	हाल 1:
		*((u8 *) opt->val)  = val;
		अवरोध;

	हाल 2:
		put_unaligned_le16(val, opt->val);
		अवरोध;

	हाल 4:
		put_unaligned_le32(val, opt->val);
		अवरोध;

	शेष:
		स_नकल(opt->val, (व्योम *) val, len);
		अवरोध;
	पूर्ण

	*ptr += L2CAP_CONF_OPT_SIZE + len;
पूर्ण

अटल व्योम l2cap_add_opt_efs(व्योम **ptr, काष्ठा l2cap_chan *chan, माप_प्रकार size)
अणु
	काष्ठा l2cap_conf_efs efs;

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_ERTM:
		efs.id		= chan->local_id;
		efs.stype	= chan->local_stype;
		efs.msdu	= cpu_to_le16(chan->local_msdu);
		efs.sdu_iसमय	= cpu_to_le32(chan->local_sdu_iसमय);
		efs.acc_lat	= cpu_to_le32(L2CAP_DEFAULT_ACC_LAT);
		efs.flush_to	= cpu_to_le32(L2CAP_EFS_DEFAULT_FLUSH_TO);
		अवरोध;

	हाल L2CAP_MODE_STREAMING:
		efs.id		= 1;
		efs.stype	= L2CAP_SERV_BESTEFFORT;
		efs.msdu	= cpu_to_le16(chan->local_msdu);
		efs.sdu_iसमय	= cpu_to_le32(chan->local_sdu_iसमय);
		efs.acc_lat	= 0;
		efs.flush_to	= 0;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	l2cap_add_conf_opt(ptr, L2CAP_CONF_EFS, माप(efs),
			   (अचिन्हित दीर्घ) &efs, size);
पूर्ण

अटल व्योम l2cap_ack_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2cap_chan *chan = container_of(work, काष्ठा l2cap_chan,
					       ack_समयr.work);
	u16 frames_to_ack;

	BT_DBG("chan %p", chan);

	l2cap_chan_lock(chan);

	frames_to_ack = __seq_offset(chan, chan->buffer_seq,
				     chan->last_acked_seq);

	अगर (frames_to_ack)
		l2cap_send_rr_or_rnr(chan, 0);

	l2cap_chan_unlock(chan);
	l2cap_chan_put(chan);
पूर्ण

पूर्णांक l2cap_erपंचांग_init(काष्ठा l2cap_chan *chan)
अणु
	पूर्णांक err;

	chan->next_tx_seq = 0;
	chan->expected_tx_seq = 0;
	chan->expected_ack_seq = 0;
	chan->unacked_frames = 0;
	chan->buffer_seq = 0;
	chan->frames_sent = 0;
	chan->last_acked_seq = 0;
	chan->sdu = शून्य;
	chan->sdu_last_frag = शून्य;
	chan->sdu_len = 0;

	skb_queue_head_init(&chan->tx_q);

	chan->local_amp_id = AMP_ID_BREDR;
	chan->move_id = AMP_ID_BREDR;
	chan->move_state = L2CAP_MOVE_STABLE;
	chan->move_role = L2CAP_MOVE_ROLE_NONE;

	अगर (chan->mode != L2CAP_MODE_ERTM)
		वापस 0;

	chan->rx_state = L2CAP_RX_STATE_RECV;
	chan->tx_state = L2CAP_TX_STATE_XMIT;

	INIT_DELAYED_WORK(&chan->retrans_समयr, l2cap_retrans_समयout);
	INIT_DELAYED_WORK(&chan->monitor_समयr, l2cap_monitor_समयout);
	INIT_DELAYED_WORK(&chan->ack_समयr, l2cap_ack_समयout);

	skb_queue_head_init(&chan->srej_q);

	err = l2cap_seq_list_init(&chan->srej_list, chan->tx_win);
	अगर (err < 0)
		वापस err;

	err = l2cap_seq_list_init(&chan->retrans_list, chan->remote_tx_win);
	अगर (err < 0)
		l2cap_seq_list_मुक्त(&chan->srej_list);

	वापस err;
पूर्ण

अटल अंतरभूत __u8 l2cap_select_mode(__u8 mode, __u16 remote_feat_mask)
अणु
	चयन (mode) अणु
	हाल L2CAP_MODE_STREAMING:
	हाल L2CAP_MODE_ERTM:
		अगर (l2cap_mode_supported(mode, remote_feat_mask))
			वापस mode;
		fallthrough;
	शेष:
		वापस L2CAP_MODE_BASIC;
	पूर्ण
पूर्ण

अटल अंतरभूत bool __l2cap_ews_supported(काष्ठा l2cap_conn *conn)
अणु
	वापस ((conn->local_fixed_chan & L2CAP_FC_A2MP) &&
		(conn->feat_mask & L2CAP_FEAT_EXT_WINDOW));
पूर्ण

अटल अंतरभूत bool __l2cap_efs_supported(काष्ठा l2cap_conn *conn)
अणु
	वापस ((conn->local_fixed_chan & L2CAP_FC_A2MP) &&
		(conn->feat_mask & L2CAP_FEAT_EXT_FLOW));
पूर्ण

अटल व्योम __l2cap_set_erपंचांग_समयouts(काष्ठा l2cap_chan *chan,
				      काष्ठा l2cap_conf_rfc *rfc)
अणु
	अगर (chan->local_amp_id != AMP_ID_BREDR && chan->hs_hcon) अणु
		u64 erपंचांग_to = chan->hs_hcon->hdev->amp_be_flush_to;

		/* Class 1 devices have must have ERTM समयouts
		 * exceeding the Link Supervision Timeout.  The
		 * शेष Link Supervision Timeout क्रम AMP
		 * controllers is 10 seconds.
		 *
		 * Class 1 devices use 0xffffffff क्रम their
		 * best-efक्रमt flush समयout, so the clamping logic
		 * will result in a समयout that meets the above
		 * requirement.  ERTM समयouts are 16-bit values, so
		 * the maximum समयout is 65.535 seconds.
		 */

		/* Convert समयout to milliseconds and round */
		erपंचांग_to = DIV_ROUND_UP_ULL(erपंचांग_to, 1000);

		/* This is the recommended क्रमmula क्रम class 2 devices
		 * that start ERTM समयrs when packets are sent to the
		 * controller.
		 */
		erपंचांग_to = 3 * erपंचांग_to + 500;

		अगर (erपंचांग_to > 0xffff)
			erपंचांग_to = 0xffff;

		rfc->retrans_समयout = cpu_to_le16((u16) erपंचांग_to);
		rfc->monitor_समयout = rfc->retrans_समयout;
	पूर्ण अन्यथा अणु
		rfc->retrans_समयout = cpu_to_le16(L2CAP_DEFAULT_RETRANS_TO);
		rfc->monitor_समयout = cpu_to_le16(L2CAP_DEFAULT_MONITOR_TO);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम l2cap_txwin_setup(काष्ठा l2cap_chan *chan)
अणु
	अगर (chan->tx_win > L2CAP_DEFAULT_TX_WINDOW &&
	    __l2cap_ews_supported(chan->conn)) अणु
		/* use extended control field */
		set_bit(FLAG_EXT_CTRL, &chan->flags);
		chan->tx_win_max = L2CAP_DEFAULT_EXT_WINDOW;
	पूर्ण अन्यथा अणु
		chan->tx_win = min_t(u16, chan->tx_win,
				     L2CAP_DEFAULT_TX_WINDOW);
		chan->tx_win_max = L2CAP_DEFAULT_TX_WINDOW;
	पूर्ण
	chan->ack_win = chan->tx_win;
पूर्ण

अटल व्योम l2cap_mtu_स्वतः(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा hci_conn *conn = chan->conn->hcon;

	chan->imtu = L2CAP_DEFAULT_MIN_MTU;

	/* The 2-DH1 packet has between 2 and 56 inक्रमmation bytes
	 * (including the 2-byte payload header)
	 */
	अगर (!(conn->pkt_type & HCI_2DH1))
		chan->imtu = 54;

	/* The 3-DH1 packet has between 2 and 85 inक्रमmation bytes
	 * (including the 2-byte payload header)
	 */
	अगर (!(conn->pkt_type & HCI_3DH1))
		chan->imtu = 83;

	/* The 2-DH3 packet has between 2 and 369 inक्रमmation bytes
	 * (including the 2-byte payload header)
	 */
	अगर (!(conn->pkt_type & HCI_2DH3))
		chan->imtu = 367;

	/* The 3-DH3 packet has between 2 and 554 inक्रमmation bytes
	 * (including the 2-byte payload header)
	 */
	अगर (!(conn->pkt_type & HCI_3DH3))
		chan->imtu = 552;

	/* The 2-DH5 packet has between 2 and 681 inक्रमmation bytes
	 * (including the 2-byte payload header)
	 */
	अगर (!(conn->pkt_type & HCI_2DH5))
		chan->imtu = 679;

	/* The 3-DH5 packet has between 2 and 1023 inक्रमmation bytes
	 * (including the 2-byte payload header)
	 */
	अगर (!(conn->pkt_type & HCI_3DH5))
		chan->imtu = 1021;
पूर्ण

अटल पूर्णांक l2cap_build_conf_req(काष्ठा l2cap_chan *chan, व्योम *data, माप_प्रकार data_size)
अणु
	काष्ठा l2cap_conf_req *req = data;
	काष्ठा l2cap_conf_rfc rfc = अणु .mode = chan->mode पूर्ण;
	व्योम *ptr = req->data;
	व्योम *endptr = data + data_size;
	u16 size;

	BT_DBG("chan %p", chan);

	अगर (chan->num_conf_req || chan->num_conf_rsp)
		जाओ करोne;

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_STREAMING:
	हाल L2CAP_MODE_ERTM:
		अगर (test_bit(CONF_STATE2_DEVICE, &chan->conf_state))
			अवरोध;

		अगर (__l2cap_efs_supported(chan->conn))
			set_bit(FLAG_EFS_ENABLE, &chan->flags);

		fallthrough;
	शेष:
		chan->mode = l2cap_select_mode(rfc.mode, chan->conn->feat_mask);
		अवरोध;
	पूर्ण

करोne:
	अगर (chan->imtu != L2CAP_DEFAULT_MTU) अणु
		अगर (!chan->imtu)
			l2cap_mtu_स्वतः(chan);
		l2cap_add_conf_opt(&ptr, L2CAP_CONF_MTU, 2, chan->imtu,
				   endptr - ptr);
	पूर्ण

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_BASIC:
		अगर (disable_erपंचांग)
			अवरोध;

		अगर (!(chan->conn->feat_mask & L2CAP_FEAT_ERTM) &&
		    !(chan->conn->feat_mask & L2CAP_FEAT_STREAMING))
			अवरोध;

		rfc.mode            = L2CAP_MODE_BASIC;
		rfc.txwin_size      = 0;
		rfc.max_transmit    = 0;
		rfc.retrans_समयout = 0;
		rfc.monitor_समयout = 0;
		rfc.max_pdu_size    = 0;

		l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC, माप(rfc),
				   (अचिन्हित दीर्घ) &rfc, endptr - ptr);
		अवरोध;

	हाल L2CAP_MODE_ERTM:
		rfc.mode            = L2CAP_MODE_ERTM;
		rfc.max_transmit    = chan->max_tx;

		__l2cap_set_erपंचांग_समयouts(chan, &rfc);

		size = min_t(u16, L2CAP_DEFAULT_MAX_PDU_SIZE, chan->conn->mtu -
			     L2CAP_EXT_HDR_SIZE - L2CAP_SDULEN_SIZE -
			     L2CAP_FCS_SIZE);
		rfc.max_pdu_size = cpu_to_le16(size);

		l2cap_txwin_setup(chan);

		rfc.txwin_size = min_t(u16, chan->tx_win,
				       L2CAP_DEFAULT_TX_WINDOW);

		l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC, माप(rfc),
				   (अचिन्हित दीर्घ) &rfc, endptr - ptr);

		अगर (test_bit(FLAG_EFS_ENABLE, &chan->flags))
			l2cap_add_opt_efs(&ptr, chan, endptr - ptr);

		अगर (test_bit(FLAG_EXT_CTRL, &chan->flags))
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_EWS, 2,
					   chan->tx_win, endptr - ptr);

		अगर (chan->conn->feat_mask & L2CAP_FEAT_FCS)
			अगर (chan->fcs == L2CAP_FCS_NONE ||
			    test_bit(CONF_RECV_NO_FCS, &chan->conf_state)) अणु
				chan->fcs = L2CAP_FCS_NONE;
				l2cap_add_conf_opt(&ptr, L2CAP_CONF_FCS, 1,
						   chan->fcs, endptr - ptr);
			पूर्ण
		अवरोध;

	हाल L2CAP_MODE_STREAMING:
		l2cap_txwin_setup(chan);
		rfc.mode            = L2CAP_MODE_STREAMING;
		rfc.txwin_size      = 0;
		rfc.max_transmit    = 0;
		rfc.retrans_समयout = 0;
		rfc.monitor_समयout = 0;

		size = min_t(u16, L2CAP_DEFAULT_MAX_PDU_SIZE, chan->conn->mtu -
			     L2CAP_EXT_HDR_SIZE - L2CAP_SDULEN_SIZE -
			     L2CAP_FCS_SIZE);
		rfc.max_pdu_size = cpu_to_le16(size);

		l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC, माप(rfc),
				   (अचिन्हित दीर्घ) &rfc, endptr - ptr);

		अगर (test_bit(FLAG_EFS_ENABLE, &chan->flags))
			l2cap_add_opt_efs(&ptr, chan, endptr - ptr);

		अगर (chan->conn->feat_mask & L2CAP_FEAT_FCS)
			अगर (chan->fcs == L2CAP_FCS_NONE ||
			    test_bit(CONF_RECV_NO_FCS, &chan->conf_state)) अणु
				chan->fcs = L2CAP_FCS_NONE;
				l2cap_add_conf_opt(&ptr, L2CAP_CONF_FCS, 1,
						   chan->fcs, endptr - ptr);
			पूर्ण
		अवरोध;
	पूर्ण

	req->dcid  = cpu_to_le16(chan->dcid);
	req->flags = cpu_to_le16(0);

	वापस ptr - data;
पूर्ण

अटल पूर्णांक l2cap_parse_conf_req(काष्ठा l2cap_chan *chan, व्योम *data, माप_प्रकार data_size)
अणु
	काष्ठा l2cap_conf_rsp *rsp = data;
	व्योम *ptr = rsp->data;
	व्योम *endptr = data + data_size;
	व्योम *req = chan->conf_req;
	पूर्णांक len = chan->conf_len;
	पूर्णांक type, hपूर्णांक, olen;
	अचिन्हित दीर्घ val;
	काष्ठा l2cap_conf_rfc rfc = अणु .mode = L2CAP_MODE_BASIC पूर्ण;
	काष्ठा l2cap_conf_efs efs;
	u8 remote_efs = 0;
	u16 mtu = L2CAP_DEFAULT_MTU;
	u16 result = L2CAP_CONF_SUCCESS;
	u16 size;

	BT_DBG("chan %p", chan);

	जबतक (len >= L2CAP_CONF_OPT_SIZE) अणु
		len -= l2cap_get_conf_opt(&req, &type, &olen, &val);
		अगर (len < 0)
			अवरोध;

		hपूर्णांक  = type & L2CAP_CONF_HINT;
		type &= L2CAP_CONF_MASK;

		चयन (type) अणु
		हाल L2CAP_CONF_MTU:
			अगर (olen != 2)
				अवरोध;
			mtu = val;
			अवरोध;

		हाल L2CAP_CONF_FLUSH_TO:
			अगर (olen != 2)
				अवरोध;
			chan->flush_to = val;
			अवरोध;

		हाल L2CAP_CONF_QOS:
			अवरोध;

		हाल L2CAP_CONF_RFC:
			अगर (olen != माप(rfc))
				अवरोध;
			स_नकल(&rfc, (व्योम *) val, olen);
			अवरोध;

		हाल L2CAP_CONF_FCS:
			अगर (olen != 1)
				अवरोध;
			अगर (val == L2CAP_FCS_NONE)
				set_bit(CONF_RECV_NO_FCS, &chan->conf_state);
			अवरोध;

		हाल L2CAP_CONF_EFS:
			अगर (olen != माप(efs))
				अवरोध;
			remote_efs = 1;
			स_नकल(&efs, (व्योम *) val, olen);
			अवरोध;

		हाल L2CAP_CONF_EWS:
			अगर (olen != 2)
				अवरोध;
			अगर (!(chan->conn->local_fixed_chan & L2CAP_FC_A2MP))
				वापस -ECONNREFUSED;
			set_bit(FLAG_EXT_CTRL, &chan->flags);
			set_bit(CONF_EWS_RECV, &chan->conf_state);
			chan->tx_win_max = L2CAP_DEFAULT_EXT_WINDOW;
			chan->remote_tx_win = val;
			अवरोध;

		शेष:
			अगर (hपूर्णांक)
				अवरोध;
			result = L2CAP_CONF_UNKNOWN;
			l2cap_add_conf_opt(&ptr, (u8)type, माप(u8), type, endptr - ptr);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (chan->num_conf_rsp || chan->num_conf_req > 1)
		जाओ करोne;

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_STREAMING:
	हाल L2CAP_MODE_ERTM:
		अगर (!test_bit(CONF_STATE2_DEVICE, &chan->conf_state)) अणु
			chan->mode = l2cap_select_mode(rfc.mode,
						       chan->conn->feat_mask);
			अवरोध;
		पूर्ण

		अगर (remote_efs) अणु
			अगर (__l2cap_efs_supported(chan->conn))
				set_bit(FLAG_EFS_ENABLE, &chan->flags);
			अन्यथा
				वापस -ECONNREFUSED;
		पूर्ण

		अगर (chan->mode != rfc.mode)
			वापस -ECONNREFUSED;

		अवरोध;
	पूर्ण

करोne:
	अगर (chan->mode != rfc.mode) अणु
		result = L2CAP_CONF_UNACCEPT;
		rfc.mode = chan->mode;

		अगर (chan->num_conf_rsp == 1)
			वापस -ECONNREFUSED;

		l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC, माप(rfc),
				   (अचिन्हित दीर्घ) &rfc, endptr - ptr);
	पूर्ण

	अगर (result == L2CAP_CONF_SUCCESS) अणु
		/* Configure output options and let the other side know
		 * which ones we करोn't like. */

		अगर (mtu < L2CAP_DEFAULT_MIN_MTU)
			result = L2CAP_CONF_UNACCEPT;
		अन्यथा अणु
			chan->omtu = mtu;
			set_bit(CONF_MTU_DONE, &chan->conf_state);
		पूर्ण
		l2cap_add_conf_opt(&ptr, L2CAP_CONF_MTU, 2, chan->omtu, endptr - ptr);

		अगर (remote_efs) अणु
			अगर (chan->local_stype != L2CAP_SERV_NOTRAFIC &&
			    efs.stype != L2CAP_SERV_NOTRAFIC &&
			    efs.stype != chan->local_stype) अणु

				result = L2CAP_CONF_UNACCEPT;

				अगर (chan->num_conf_req >= 1)
					वापस -ECONNREFUSED;

				l2cap_add_conf_opt(&ptr, L2CAP_CONF_EFS,
						   माप(efs),
						   (अचिन्हित दीर्घ) &efs, endptr - ptr);
			पूर्ण अन्यथा अणु
				/* Send PENDING Conf Rsp */
				result = L2CAP_CONF_PENDING;
				set_bit(CONF_LOC_CONF_PEND, &chan->conf_state);
			पूर्ण
		पूर्ण

		चयन (rfc.mode) अणु
		हाल L2CAP_MODE_BASIC:
			chan->fcs = L2CAP_FCS_NONE;
			set_bit(CONF_MODE_DONE, &chan->conf_state);
			अवरोध;

		हाल L2CAP_MODE_ERTM:
			अगर (!test_bit(CONF_EWS_RECV, &chan->conf_state))
				chan->remote_tx_win = rfc.txwin_size;
			अन्यथा
				rfc.txwin_size = L2CAP_DEFAULT_TX_WINDOW;

			chan->remote_max_tx = rfc.max_transmit;

			size = min_t(u16, le16_to_cpu(rfc.max_pdu_size),
				     chan->conn->mtu - L2CAP_EXT_HDR_SIZE -
				     L2CAP_SDULEN_SIZE - L2CAP_FCS_SIZE);
			rfc.max_pdu_size = cpu_to_le16(size);
			chan->remote_mps = size;

			__l2cap_set_erपंचांग_समयouts(chan, &rfc);

			set_bit(CONF_MODE_DONE, &chan->conf_state);

			l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC,
					   माप(rfc), (अचिन्हित दीर्घ) &rfc, endptr - ptr);

			अगर (test_bit(FLAG_EFS_ENABLE, &chan->flags)) अणु
				chan->remote_id = efs.id;
				chan->remote_stype = efs.stype;
				chan->remote_msdu = le16_to_cpu(efs.msdu);
				chan->remote_flush_to =
					le32_to_cpu(efs.flush_to);
				chan->remote_acc_lat =
					le32_to_cpu(efs.acc_lat);
				chan->remote_sdu_iसमय =
					le32_to_cpu(efs.sdu_iसमय);
				l2cap_add_conf_opt(&ptr, L2CAP_CONF_EFS,
						   माप(efs),
						   (अचिन्हित दीर्घ) &efs, endptr - ptr);
			पूर्ण
			अवरोध;

		हाल L2CAP_MODE_STREAMING:
			size = min_t(u16, le16_to_cpu(rfc.max_pdu_size),
				     chan->conn->mtu - L2CAP_EXT_HDR_SIZE -
				     L2CAP_SDULEN_SIZE - L2CAP_FCS_SIZE);
			rfc.max_pdu_size = cpu_to_le16(size);
			chan->remote_mps = size;

			set_bit(CONF_MODE_DONE, &chan->conf_state);

			l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC, माप(rfc),
					   (अचिन्हित दीर्घ) &rfc, endptr - ptr);

			अवरोध;

		शेष:
			result = L2CAP_CONF_UNACCEPT;

			स_रखो(&rfc, 0, माप(rfc));
			rfc.mode = chan->mode;
		पूर्ण

		अगर (result == L2CAP_CONF_SUCCESS)
			set_bit(CONF_OUTPUT_DONE, &chan->conf_state);
	पूर्ण
	rsp->scid   = cpu_to_le16(chan->dcid);
	rsp->result = cpu_to_le16(result);
	rsp->flags  = cpu_to_le16(0);

	वापस ptr - data;
पूर्ण

अटल पूर्णांक l2cap_parse_conf_rsp(काष्ठा l2cap_chan *chan, व्योम *rsp, पूर्णांक len,
				व्योम *data, माप_प्रकार size, u16 *result)
अणु
	काष्ठा l2cap_conf_req *req = data;
	व्योम *ptr = req->data;
	व्योम *endptr = data + size;
	पूर्णांक type, olen;
	अचिन्हित दीर्घ val;
	काष्ठा l2cap_conf_rfc rfc = अणु .mode = L2CAP_MODE_BASIC पूर्ण;
	काष्ठा l2cap_conf_efs efs;

	BT_DBG("chan %p, rsp %p, len %d, req %p", chan, rsp, len, data);

	जबतक (len >= L2CAP_CONF_OPT_SIZE) अणु
		len -= l2cap_get_conf_opt(&rsp, &type, &olen, &val);
		अगर (len < 0)
			अवरोध;

		चयन (type) अणु
		हाल L2CAP_CONF_MTU:
			अगर (olen != 2)
				अवरोध;
			अगर (val < L2CAP_DEFAULT_MIN_MTU) अणु
				*result = L2CAP_CONF_UNACCEPT;
				chan->imtu = L2CAP_DEFAULT_MIN_MTU;
			पूर्ण अन्यथा
				chan->imtu = val;
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_MTU, 2, chan->imtu,
					   endptr - ptr);
			अवरोध;

		हाल L2CAP_CONF_FLUSH_TO:
			अगर (olen != 2)
				अवरोध;
			chan->flush_to = val;
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_FLUSH_TO, 2,
					   chan->flush_to, endptr - ptr);
			अवरोध;

		हाल L2CAP_CONF_RFC:
			अगर (olen != माप(rfc))
				अवरोध;
			स_नकल(&rfc, (व्योम *)val, olen);
			अगर (test_bit(CONF_STATE2_DEVICE, &chan->conf_state) &&
			    rfc.mode != chan->mode)
				वापस -ECONNREFUSED;
			chan->fcs = 0;
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC, माप(rfc),
					   (अचिन्हित दीर्घ) &rfc, endptr - ptr);
			अवरोध;

		हाल L2CAP_CONF_EWS:
			अगर (olen != 2)
				अवरोध;
			chan->ack_win = min_t(u16, val, chan->ack_win);
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_EWS, 2,
					   chan->tx_win, endptr - ptr);
			अवरोध;

		हाल L2CAP_CONF_EFS:
			अगर (olen != माप(efs))
				अवरोध;
			स_नकल(&efs, (व्योम *)val, olen);
			अगर (chan->local_stype != L2CAP_SERV_NOTRAFIC &&
			    efs.stype != L2CAP_SERV_NOTRAFIC &&
			    efs.stype != chan->local_stype)
				वापस -ECONNREFUSED;
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_EFS, माप(efs),
					   (अचिन्हित दीर्घ) &efs, endptr - ptr);
			अवरोध;

		हाल L2CAP_CONF_FCS:
			अगर (olen != 1)
				अवरोध;
			अगर (*result == L2CAP_CONF_PENDING)
				अगर (val == L2CAP_FCS_NONE)
					set_bit(CONF_RECV_NO_FCS,
						&chan->conf_state);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (chan->mode == L2CAP_MODE_BASIC && chan->mode != rfc.mode)
		वापस -ECONNREFUSED;

	chan->mode = rfc.mode;

	अगर (*result == L2CAP_CONF_SUCCESS || *result == L2CAP_CONF_PENDING) अणु
		चयन (rfc.mode) अणु
		हाल L2CAP_MODE_ERTM:
			chan->retrans_समयout = le16_to_cpu(rfc.retrans_समयout);
			chan->monitor_समयout = le16_to_cpu(rfc.monitor_समयout);
			chan->mps    = le16_to_cpu(rfc.max_pdu_size);
			अगर (!test_bit(FLAG_EXT_CTRL, &chan->flags))
				chan->ack_win = min_t(u16, chan->ack_win,
						      rfc.txwin_size);

			अगर (test_bit(FLAG_EFS_ENABLE, &chan->flags)) अणु
				chan->local_msdu = le16_to_cpu(efs.msdu);
				chan->local_sdu_iसमय =
					le32_to_cpu(efs.sdu_iसमय);
				chan->local_acc_lat = le32_to_cpu(efs.acc_lat);
				chan->local_flush_to =
					le32_to_cpu(efs.flush_to);
			पूर्ण
			अवरोध;

		हाल L2CAP_MODE_STREAMING:
			chan->mps    = le16_to_cpu(rfc.max_pdu_size);
		पूर्ण
	पूर्ण

	req->dcid   = cpu_to_le16(chan->dcid);
	req->flags  = cpu_to_le16(0);

	वापस ptr - data;
पूर्ण

अटल पूर्णांक l2cap_build_conf_rsp(काष्ठा l2cap_chan *chan, व्योम *data,
				u16 result, u16 flags)
अणु
	काष्ठा l2cap_conf_rsp *rsp = data;
	व्योम *ptr = rsp->data;

	BT_DBG("chan %p", chan);

	rsp->scid   = cpu_to_le16(chan->dcid);
	rsp->result = cpu_to_le16(result);
	rsp->flags  = cpu_to_le16(flags);

	वापस ptr - data;
पूर्ण

व्योम __l2cap_le_connect_rsp_defer(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_le_conn_rsp rsp;
	काष्ठा l2cap_conn *conn = chan->conn;

	BT_DBG("chan %p", chan);

	rsp.dcid    = cpu_to_le16(chan->scid);
	rsp.mtu     = cpu_to_le16(chan->imtu);
	rsp.mps     = cpu_to_le16(chan->mps);
	rsp.credits = cpu_to_le16(chan->rx_credits);
	rsp.result  = cpu_to_le16(L2CAP_CR_LE_SUCCESS);

	l2cap_send_cmd(conn, chan->ident, L2CAP_LE_CONN_RSP, माप(rsp),
		       &rsp);
पूर्ण

व्योम __l2cap_ecred_conn_rsp_defer(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा अणु
		काष्ठा l2cap_ecred_conn_rsp rsp;
		__le16 dcid[5];
	पूर्ण __packed pdu;
	काष्ठा l2cap_conn *conn = chan->conn;
	u16 ident = chan->ident;
	पूर्णांक i = 0;

	अगर (!ident)
		वापस;

	BT_DBG("chan %p ident %d", chan, ident);

	pdu.rsp.mtu     = cpu_to_le16(chan->imtu);
	pdu.rsp.mps     = cpu_to_le16(chan->mps);
	pdu.rsp.credits = cpu_to_le16(chan->rx_credits);
	pdu.rsp.result  = cpu_to_le16(L2CAP_CR_LE_SUCCESS);

	mutex_lock(&conn->chan_lock);

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		अगर (chan->ident != ident)
			जारी;

		/* Reset ident so only one response is sent */
		chan->ident = 0;

		/* Include all channels pending with the same ident */
		pdu.dcid[i++] = cpu_to_le16(chan->scid);
	पूर्ण

	mutex_unlock(&conn->chan_lock);

	l2cap_send_cmd(conn, ident, L2CAP_ECRED_CONN_RSP,
			माप(pdu.rsp) + i * माप(__le16), &pdu);
पूर्ण

व्योम __l2cap_connect_rsp_defer(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn_rsp rsp;
	काष्ठा l2cap_conn *conn = chan->conn;
	u8 buf[128];
	u8 rsp_code;

	rsp.scid   = cpu_to_le16(chan->dcid);
	rsp.dcid   = cpu_to_le16(chan->scid);
	rsp.result = cpu_to_le16(L2CAP_CR_SUCCESS);
	rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);

	अगर (chan->hs_hcon)
		rsp_code = L2CAP_CREATE_CHAN_RSP;
	अन्यथा
		rsp_code = L2CAP_CONN_RSP;

	BT_DBG("chan %p rsp_code %u", chan, rsp_code);

	l2cap_send_cmd(conn, chan->ident, rsp_code, माप(rsp), &rsp);

	अगर (test_and_set_bit(CONF_REQ_SENT, &chan->conf_state))
		वापस;

	l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
		       l2cap_build_conf_req(chan, buf, माप(buf)), buf);
	chan->num_conf_req++;
पूर्ण

अटल व्योम l2cap_conf_rfc_get(काष्ठा l2cap_chan *chan, व्योम *rsp, पूर्णांक len)
अणु
	पूर्णांक type, olen;
	अचिन्हित दीर्घ val;
	/* Use sane शेष values in हाल a misbehaving remote device
	 * did not send an RFC or extended winकरोw size option.
	 */
	u16 txwin_ext = chan->ack_win;
	काष्ठा l2cap_conf_rfc rfc = अणु
		.mode = chan->mode,
		.retrans_समयout = cpu_to_le16(L2CAP_DEFAULT_RETRANS_TO),
		.monitor_समयout = cpu_to_le16(L2CAP_DEFAULT_MONITOR_TO),
		.max_pdu_size = cpu_to_le16(chan->imtu),
		.txwin_size = min_t(u16, chan->ack_win, L2CAP_DEFAULT_TX_WINDOW),
	पूर्ण;

	BT_DBG("chan %p, rsp %p, len %d", chan, rsp, len);

	अगर ((chan->mode != L2CAP_MODE_ERTM) && (chan->mode != L2CAP_MODE_STREAMING))
		वापस;

	जबतक (len >= L2CAP_CONF_OPT_SIZE) अणु
		len -= l2cap_get_conf_opt(&rsp, &type, &olen, &val);
		अगर (len < 0)
			अवरोध;

		चयन (type) अणु
		हाल L2CAP_CONF_RFC:
			अगर (olen != माप(rfc))
				अवरोध;
			स_नकल(&rfc, (व्योम *)val, olen);
			अवरोध;
		हाल L2CAP_CONF_EWS:
			अगर (olen != 2)
				अवरोध;
			txwin_ext = val;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (rfc.mode) अणु
	हाल L2CAP_MODE_ERTM:
		chan->retrans_समयout = le16_to_cpu(rfc.retrans_समयout);
		chan->monitor_समयout = le16_to_cpu(rfc.monitor_समयout);
		chan->mps = le16_to_cpu(rfc.max_pdu_size);
		अगर (test_bit(FLAG_EXT_CTRL, &chan->flags))
			chan->ack_win = min_t(u16, chan->ack_win, txwin_ext);
		अन्यथा
			chan->ack_win = min_t(u16, chan->ack_win,
					      rfc.txwin_size);
		अवरोध;
	हाल L2CAP_MODE_STREAMING:
		chan->mps    = le16_to_cpu(rfc.max_pdu_size);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_command_rej(काष्ठा l2cap_conn *conn,
				    काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				    u8 *data)
अणु
	काष्ठा l2cap_cmd_rej_unk *rej = (काष्ठा l2cap_cmd_rej_unk *) data;

	अगर (cmd_len < माप(*rej))
		वापस -EPROTO;

	अगर (rej->reason != L2CAP_REJ_NOT_UNDERSTOOD)
		वापस 0;

	अगर ((conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT) &&
	    cmd->ident == conn->info_ident) अणु
		cancel_delayed_work(&conn->info_समयr);

		conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_DONE;
		conn->info_ident = 0;

		l2cap_conn_start(conn);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा l2cap_chan *l2cap_connect(काष्ठा l2cap_conn *conn,
					काष्ठा l2cap_cmd_hdr *cmd,
					u8 *data, u8 rsp_code, u8 amp_id)
अणु
	काष्ठा l2cap_conn_req *req = (काष्ठा l2cap_conn_req *) data;
	काष्ठा l2cap_conn_rsp rsp;
	काष्ठा l2cap_chan *chan = शून्य, *pchan;
	पूर्णांक result, status = L2CAP_CS_NO_INFO;

	u16 dcid = 0, scid = __le16_to_cpu(req->scid);
	__le16 psm = req->psm;

	BT_DBG("psm 0x%2.2x scid 0x%4.4x", __le16_to_cpu(psm), scid);

	/* Check अगर we have socket listening on psm */
	pchan = l2cap_global_chan_by_psm(BT_LISTEN, psm, &conn->hcon->src,
					 &conn->hcon->dst, ACL_LINK);
	अगर (!pchan) अणु
		result = L2CAP_CR_BAD_PSM;
		जाओ sendresp;
	पूर्ण

	mutex_lock(&conn->chan_lock);
	l2cap_chan_lock(pchan);

	/* Check अगर the ACL is secure enough (अगर not SDP) */
	अगर (psm != cpu_to_le16(L2CAP_PSM_SDP) &&
	    !hci_conn_check_link_mode(conn->hcon)) अणु
		conn->disc_reason = HCI_ERROR_AUTH_FAILURE;
		result = L2CAP_CR_SEC_BLOCK;
		जाओ response;
	पूर्ण

	result = L2CAP_CR_NO_MEM;

	/* Check क्रम valid dynamic CID range (as per Erratum 3253) */
	अगर (scid < L2CAP_CID_DYN_START || scid > L2CAP_CID_DYN_END) अणु
		result = L2CAP_CR_INVALID_SCID;
		जाओ response;
	पूर्ण

	/* Check अगर we alपढ़ोy have channel with that dcid */
	अगर (__l2cap_get_chan_by_dcid(conn, scid)) अणु
		result = L2CAP_CR_SCID_IN_USE;
		जाओ response;
	पूर्ण

	chan = pchan->ops->new_connection(pchan);
	अगर (!chan)
		जाओ response;

	/* For certain devices (ex: HID mouse), support क्रम authentication,
	 * pairing and bonding is optional. For such devices, inorder to aव्योम
	 * the ACL alive क्रम too दीर्घ after L2CAP disconnection, reset the ACL
	 * disc_समयout back to HCI_DISCONN_TIMEOUT during L2CAP connect.
	 */
	conn->hcon->disc_समयout = HCI_DISCONN_TIMEOUT;

	bacpy(&chan->src, &conn->hcon->src);
	bacpy(&chan->dst, &conn->hcon->dst);
	chan->src_type = bdaddr_src_type(conn->hcon);
	chan->dst_type = bdaddr_dst_type(conn->hcon);
	chan->psm  = psm;
	chan->dcid = scid;
	chan->local_amp_id = amp_id;

	__l2cap_chan_add(conn, chan);

	dcid = chan->scid;

	__set_chan_समयr(chan, chan->ops->get_sndसमयo(chan));

	chan->ident = cmd->ident;

	अगर (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_DONE) अणु
		अगर (l2cap_chan_check_security(chan, false)) अणु
			अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags)) अणु
				l2cap_state_change(chan, BT_CONNECT2);
				result = L2CAP_CR_PEND;
				status = L2CAP_CS_AUTHOR_PEND;
				chan->ops->defer(chan);
			पूर्ण अन्यथा अणु
				/* Force pending result क्रम AMP controllers.
				 * The connection will succeed after the
				 * physical link is up.
				 */
				अगर (amp_id == AMP_ID_BREDR) अणु
					l2cap_state_change(chan, BT_CONFIG);
					result = L2CAP_CR_SUCCESS;
				पूर्ण अन्यथा अणु
					l2cap_state_change(chan, BT_CONNECT2);
					result = L2CAP_CR_PEND;
				पूर्ण
				status = L2CAP_CS_NO_INFO;
			पूर्ण
		पूर्ण अन्यथा अणु
			l2cap_state_change(chan, BT_CONNECT2);
			result = L2CAP_CR_PEND;
			status = L2CAP_CS_AUTHEN_PEND;
		पूर्ण
	पूर्ण अन्यथा अणु
		l2cap_state_change(chan, BT_CONNECT2);
		result = L2CAP_CR_PEND;
		status = L2CAP_CS_NO_INFO;
	पूर्ण

response:
	l2cap_chan_unlock(pchan);
	mutex_unlock(&conn->chan_lock);
	l2cap_chan_put(pchan);

sendresp:
	rsp.scid   = cpu_to_le16(scid);
	rsp.dcid   = cpu_to_le16(dcid);
	rsp.result = cpu_to_le16(result);
	rsp.status = cpu_to_le16(status);
	l2cap_send_cmd(conn, cmd->ident, rsp_code, माप(rsp), &rsp);

	अगर (result == L2CAP_CR_PEND && status == L2CAP_CS_NO_INFO) अणु
		काष्ठा l2cap_info_req info;
		info.type = cpu_to_le16(L2CAP_IT_FEAT_MASK);

		conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_SENT;
		conn->info_ident = l2cap_get_ident(conn);

		schedule_delayed_work(&conn->info_समयr, L2CAP_INFO_TIMEOUT);

		l2cap_send_cmd(conn, conn->info_ident, L2CAP_INFO_REQ,
			       माप(info), &info);
	पूर्ण

	अगर (chan && !test_bit(CONF_REQ_SENT, &chan->conf_state) &&
	    result == L2CAP_CR_SUCCESS) अणु
		u8 buf[128];
		set_bit(CONF_REQ_SENT, &chan->conf_state);
		l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
			       l2cap_build_conf_req(chan, buf, माप(buf)), buf);
		chan->num_conf_req++;
	पूर्ण

	वापस chan;
पूर्ण

अटल पूर्णांक l2cap_connect_req(काष्ठा l2cap_conn *conn,
			     काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len, u8 *data)
अणु
	काष्ठा hci_dev *hdev = conn->hcon->hdev;
	काष्ठा hci_conn *hcon = conn->hcon;

	अगर (cmd_len < माप(काष्ठा l2cap_conn_req))
		वापस -EPROTO;

	hci_dev_lock(hdev);
	अगर (hci_dev_test_flag(hdev, HCI_MGMT) &&
	    !test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &hcon->flags))
		mgmt_device_connected(hdev, hcon, 0, शून्य, 0);
	hci_dev_unlock(hdev);

	l2cap_connect(conn, cmd, data, L2CAP_CONN_RSP, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_connect_create_rsp(काष्ठा l2cap_conn *conn,
				    काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				    u8 *data)
अणु
	काष्ठा l2cap_conn_rsp *rsp = (काष्ठा l2cap_conn_rsp *) data;
	u16 scid, dcid, result, status;
	काष्ठा l2cap_chan *chan;
	u8 req[128];
	पूर्णांक err;

	अगर (cmd_len < माप(*rsp))
		वापस -EPROTO;

	scid   = __le16_to_cpu(rsp->scid);
	dcid   = __le16_to_cpu(rsp->dcid);
	result = __le16_to_cpu(rsp->result);
	status = __le16_to_cpu(rsp->status);

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x result 0x%2.2x status 0x%2.2x",
	       dcid, scid, result, status);

	mutex_lock(&conn->chan_lock);

	अगर (scid) अणु
		chan = __l2cap_get_chan_by_scid(conn, scid);
		अगर (!chan) अणु
			err = -EBADSLT;
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		chan = __l2cap_get_chan_by_ident(conn, cmd->ident);
		अगर (!chan) अणु
			err = -EBADSLT;
			जाओ unlock;
		पूर्ण
	पूर्ण

	err = 0;

	l2cap_chan_lock(chan);

	चयन (result) अणु
	हाल L2CAP_CR_SUCCESS:
		l2cap_state_change(chan, BT_CONFIG);
		chan->ident = 0;
		chan->dcid = dcid;
		clear_bit(CONF_CONNECT_PEND, &chan->conf_state);

		अगर (test_and_set_bit(CONF_REQ_SENT, &chan->conf_state))
			अवरोध;

		l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
			       l2cap_build_conf_req(chan, req, माप(req)), req);
		chan->num_conf_req++;
		अवरोध;

	हाल L2CAP_CR_PEND:
		set_bit(CONF_CONNECT_PEND, &chan->conf_state);
		अवरोध;

	शेष:
		l2cap_chan_del(chan, ECONNREFUSED);
		अवरोध;
	पूर्ण

	l2cap_chan_unlock(chan);

unlock:
	mutex_unlock(&conn->chan_lock);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम set_शेष_fcs(काष्ठा l2cap_chan *chan)
अणु
	/* FCS is enabled only in ERTM or streaming mode, अगर one or both
	 * sides request it.
	 */
	अगर (chan->mode != L2CAP_MODE_ERTM && chan->mode != L2CAP_MODE_STREAMING)
		chan->fcs = L2CAP_FCS_NONE;
	अन्यथा अगर (!test_bit(CONF_RECV_NO_FCS, &chan->conf_state))
		chan->fcs = L2CAP_FCS_CRC16;
पूर्ण

अटल व्योम l2cap_send_efs_conf_rsp(काष्ठा l2cap_chan *chan, व्योम *data,
				    u8 ident, u16 flags)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;

	BT_DBG("conn %p chan %p ident %d flags 0x%4.4x", conn, chan, ident,
	       flags);

	clear_bit(CONF_LOC_CONF_PEND, &chan->conf_state);
	set_bit(CONF_OUTPUT_DONE, &chan->conf_state);

	l2cap_send_cmd(conn, ident, L2CAP_CONF_RSP,
		       l2cap_build_conf_rsp(chan, data,
					    L2CAP_CONF_SUCCESS, flags), data);
पूर्ण

अटल व्योम cmd_reject_invalid_cid(काष्ठा l2cap_conn *conn, u8 ident,
				   u16 scid, u16 dcid)
अणु
	काष्ठा l2cap_cmd_rej_cid rej;

	rej.reason = cpu_to_le16(L2CAP_REJ_INVALID_CID);
	rej.scid = __cpu_to_le16(scid);
	rej.dcid = __cpu_to_le16(dcid);

	l2cap_send_cmd(conn, ident, L2CAP_COMMAND_REJ, माप(rej), &rej);
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_config_req(काष्ठा l2cap_conn *conn,
				   काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
अणु
	काष्ठा l2cap_conf_req *req = (काष्ठा l2cap_conf_req *) data;
	u16 dcid, flags;
	u8 rsp[64];
	काष्ठा l2cap_chan *chan;
	पूर्णांक len, err = 0;

	अगर (cmd_len < माप(*req))
		वापस -EPROTO;

	dcid  = __le16_to_cpu(req->dcid);
	flags = __le16_to_cpu(req->flags);

	BT_DBG("dcid 0x%4.4x flags 0x%2.2x", dcid, flags);

	chan = l2cap_get_chan_by_scid(conn, dcid);
	अगर (!chan) अणु
		cmd_reject_invalid_cid(conn, cmd->ident, dcid, 0);
		वापस 0;
	पूर्ण

	अगर (chan->state != BT_CONFIG && chan->state != BT_CONNECT2 &&
	    chan->state != BT_CONNECTED) अणु
		cmd_reject_invalid_cid(conn, cmd->ident, chan->scid,
				       chan->dcid);
		जाओ unlock;
	पूर्ण

	/* Reject अगर config buffer is too small. */
	len = cmd_len - माप(*req);
	अगर (chan->conf_len + len > माप(chan->conf_req)) अणु
		l2cap_send_cmd(conn, cmd->ident, L2CAP_CONF_RSP,
			       l2cap_build_conf_rsp(chan, rsp,
			       L2CAP_CONF_REJECT, flags), rsp);
		जाओ unlock;
	पूर्ण

	/* Store config. */
	स_नकल(chan->conf_req + chan->conf_len, req->data, len);
	chan->conf_len += len;

	अगर (flags & L2CAP_CONF_FLAG_CONTINUATION) अणु
		/* Incomplete config. Send empty response. */
		l2cap_send_cmd(conn, cmd->ident, L2CAP_CONF_RSP,
			       l2cap_build_conf_rsp(chan, rsp,
			       L2CAP_CONF_SUCCESS, flags), rsp);
		जाओ unlock;
	पूर्ण

	/* Complete config. */
	len = l2cap_parse_conf_req(chan, rsp, माप(rsp));
	अगर (len < 0) अणु
		l2cap_send_disconn_req(chan, ECONNRESET);
		जाओ unlock;
	पूर्ण

	chan->ident = cmd->ident;
	l2cap_send_cmd(conn, cmd->ident, L2CAP_CONF_RSP, len, rsp);
	chan->num_conf_rsp++;

	/* Reset config buffer. */
	chan->conf_len = 0;

	अगर (!test_bit(CONF_OUTPUT_DONE, &chan->conf_state))
		जाओ unlock;

	अगर (test_bit(CONF_INPUT_DONE, &chan->conf_state)) अणु
		set_शेष_fcs(chan);

		अगर (chan->mode == L2CAP_MODE_ERTM ||
		    chan->mode == L2CAP_MODE_STREAMING)
			err = l2cap_erपंचांग_init(chan);

		अगर (err < 0)
			l2cap_send_disconn_req(chan, -err);
		अन्यथा
			l2cap_chan_पढ़ोy(chan);

		जाओ unlock;
	पूर्ण

	अगर (!test_and_set_bit(CONF_REQ_SENT, &chan->conf_state)) अणु
		u8 buf[64];
		l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
			       l2cap_build_conf_req(chan, buf, माप(buf)), buf);
		chan->num_conf_req++;
	पूर्ण

	/* Got Conf Rsp PENDING from remote side and assume we sent
	   Conf Rsp PENDING in the code above */
	अगर (test_bit(CONF_REM_CONF_PEND, &chan->conf_state) &&
	    test_bit(CONF_LOC_CONF_PEND, &chan->conf_state)) अणु

		/* check compatibility */

		/* Send rsp क्रम BR/EDR channel */
		अगर (!chan->hs_hcon)
			l2cap_send_efs_conf_rsp(chan, rsp, cmd->ident, flags);
		अन्यथा
			chan->ident = cmd->ident;
	पूर्ण

unlock:
	l2cap_chan_unlock(chan);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_config_rsp(काष्ठा l2cap_conn *conn,
				   काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
अणु
	काष्ठा l2cap_conf_rsp *rsp = (काष्ठा l2cap_conf_rsp *)data;
	u16 scid, flags, result;
	काष्ठा l2cap_chan *chan;
	पूर्णांक len = cmd_len - माप(*rsp);
	पूर्णांक err = 0;

	अगर (cmd_len < माप(*rsp))
		वापस -EPROTO;

	scid   = __le16_to_cpu(rsp->scid);
	flags  = __le16_to_cpu(rsp->flags);
	result = __le16_to_cpu(rsp->result);

	BT_DBG("scid 0x%4.4x flags 0x%2.2x result 0x%2.2x len %d", scid, flags,
	       result, len);

	chan = l2cap_get_chan_by_scid(conn, scid);
	अगर (!chan)
		वापस 0;

	चयन (result) अणु
	हाल L2CAP_CONF_SUCCESS:
		l2cap_conf_rfc_get(chan, rsp->data, len);
		clear_bit(CONF_REM_CONF_PEND, &chan->conf_state);
		अवरोध;

	हाल L2CAP_CONF_PENDING:
		set_bit(CONF_REM_CONF_PEND, &chan->conf_state);

		अगर (test_bit(CONF_LOC_CONF_PEND, &chan->conf_state)) अणु
			अक्षर buf[64];

			len = l2cap_parse_conf_rsp(chan, rsp->data, len,
						   buf, माप(buf), &result);
			अगर (len < 0) अणु
				l2cap_send_disconn_req(chan, ECONNRESET);
				जाओ करोne;
			पूर्ण

			अगर (!chan->hs_hcon) अणु
				l2cap_send_efs_conf_rsp(chan, buf, cmd->ident,
							0);
			पूर्ण अन्यथा अणु
				अगर (l2cap_check_efs(chan)) अणु
					amp_create_logical_link(chan);
					chan->ident = cmd->ident;
				पूर्ण
			पूर्ण
		पूर्ण
		जाओ करोne;

	हाल L2CAP_CONF_UNKNOWN:
	हाल L2CAP_CONF_UNACCEPT:
		अगर (chan->num_conf_rsp <= L2CAP_CONF_MAX_CONF_RSP) अणु
			अक्षर req[64];

			अगर (len > माप(req) - माप(काष्ठा l2cap_conf_req)) अणु
				l2cap_send_disconn_req(chan, ECONNRESET);
				जाओ करोne;
			पूर्ण

			/* throw out any old stored conf requests */
			result = L2CAP_CONF_SUCCESS;
			len = l2cap_parse_conf_rsp(chan, rsp->data, len,
						   req, माप(req), &result);
			अगर (len < 0) अणु
				l2cap_send_disconn_req(chan, ECONNRESET);
				जाओ करोne;
			पूर्ण

			l2cap_send_cmd(conn, l2cap_get_ident(conn),
				       L2CAP_CONF_REQ, len, req);
			chan->num_conf_req++;
			अगर (result != L2CAP_CONF_SUCCESS)
				जाओ करोne;
			अवरोध;
		पूर्ण
		fallthrough;

	शेष:
		l2cap_chan_set_err(chan, ECONNRESET);

		__set_chan_समयr(chan, L2CAP_DISC_REJ_TIMEOUT);
		l2cap_send_disconn_req(chan, ECONNRESET);
		जाओ करोne;
	पूर्ण

	अगर (flags & L2CAP_CONF_FLAG_CONTINUATION)
		जाओ करोne;

	set_bit(CONF_INPUT_DONE, &chan->conf_state);

	अगर (test_bit(CONF_OUTPUT_DONE, &chan->conf_state)) अणु
		set_शेष_fcs(chan);

		अगर (chan->mode == L2CAP_MODE_ERTM ||
		    chan->mode == L2CAP_MODE_STREAMING)
			err = l2cap_erपंचांग_init(chan);

		अगर (err < 0)
			l2cap_send_disconn_req(chan, -err);
		अन्यथा
			l2cap_chan_पढ़ोy(chan);
	पूर्ण

करोne:
	l2cap_chan_unlock(chan);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_disconnect_req(काष्ठा l2cap_conn *conn,
				       काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
अणु
	काष्ठा l2cap_disconn_req *req = (काष्ठा l2cap_disconn_req *) data;
	काष्ठा l2cap_disconn_rsp rsp;
	u16 dcid, scid;
	काष्ठा l2cap_chan *chan;

	अगर (cmd_len != माप(*req))
		वापस -EPROTO;

	scid = __le16_to_cpu(req->scid);
	dcid = __le16_to_cpu(req->dcid);

	BT_DBG("scid 0x%4.4x dcid 0x%4.4x", scid, dcid);

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_scid(conn, dcid);
	अगर (!chan) अणु
		mutex_unlock(&conn->chan_lock);
		cmd_reject_invalid_cid(conn, cmd->ident, dcid, scid);
		वापस 0;
	पूर्ण

	l2cap_chan_hold(chan);
	l2cap_chan_lock(chan);

	rsp.dcid = cpu_to_le16(chan->scid);
	rsp.scid = cpu_to_le16(chan->dcid);
	l2cap_send_cmd(conn, cmd->ident, L2CAP_DISCONN_RSP, माप(rsp), &rsp);

	chan->ops->set_shutकरोwn(chan);

	l2cap_chan_del(chan, ECONNRESET);

	chan->ops->बंद(chan);

	l2cap_chan_unlock(chan);
	l2cap_chan_put(chan);

	mutex_unlock(&conn->chan_lock);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_disconnect_rsp(काष्ठा l2cap_conn *conn,
				       काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
अणु
	काष्ठा l2cap_disconn_rsp *rsp = (काष्ठा l2cap_disconn_rsp *) data;
	u16 dcid, scid;
	काष्ठा l2cap_chan *chan;

	अगर (cmd_len != माप(*rsp))
		वापस -EPROTO;

	scid = __le16_to_cpu(rsp->scid);
	dcid = __le16_to_cpu(rsp->dcid);

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x", dcid, scid);

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_scid(conn, scid);
	अगर (!chan) अणु
		mutex_unlock(&conn->chan_lock);
		वापस 0;
	पूर्ण

	l2cap_chan_hold(chan);
	l2cap_chan_lock(chan);

	अगर (chan->state != BT_DISCONN) अणु
		l2cap_chan_unlock(chan);
		l2cap_chan_put(chan);
		mutex_unlock(&conn->chan_lock);
		वापस 0;
	पूर्ण

	l2cap_chan_del(chan, 0);

	chan->ops->बंद(chan);

	l2cap_chan_unlock(chan);
	l2cap_chan_put(chan);

	mutex_unlock(&conn->chan_lock);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_inक्रमmation_req(काष्ठा l2cap_conn *conn,
					काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
					u8 *data)
अणु
	काष्ठा l2cap_info_req *req = (काष्ठा l2cap_info_req *) data;
	u16 type;

	अगर (cmd_len != माप(*req))
		वापस -EPROTO;

	type = __le16_to_cpu(req->type);

	BT_DBG("type 0x%4.4x", type);

	अगर (type == L2CAP_IT_FEAT_MASK) अणु
		u8 buf[8];
		u32 feat_mask = l2cap_feat_mask;
		काष्ठा l2cap_info_rsp *rsp = (काष्ठा l2cap_info_rsp *) buf;
		rsp->type   = cpu_to_le16(L2CAP_IT_FEAT_MASK);
		rsp->result = cpu_to_le16(L2CAP_IR_SUCCESS);
		अगर (!disable_erपंचांग)
			feat_mask |= L2CAP_FEAT_ERTM | L2CAP_FEAT_STREAMING
				| L2CAP_FEAT_FCS;
		अगर (conn->local_fixed_chan & L2CAP_FC_A2MP)
			feat_mask |= L2CAP_FEAT_EXT_FLOW
				| L2CAP_FEAT_EXT_WINDOW;

		put_unaligned_le32(feat_mask, rsp->data);
		l2cap_send_cmd(conn, cmd->ident, L2CAP_INFO_RSP, माप(buf),
			       buf);
	पूर्ण अन्यथा अगर (type == L2CAP_IT_FIXED_CHAN) अणु
		u8 buf[12];
		काष्ठा l2cap_info_rsp *rsp = (काष्ठा l2cap_info_rsp *) buf;

		rsp->type   = cpu_to_le16(L2CAP_IT_FIXED_CHAN);
		rsp->result = cpu_to_le16(L2CAP_IR_SUCCESS);
		rsp->data[0] = conn->local_fixed_chan;
		स_रखो(rsp->data + 1, 0, 7);
		l2cap_send_cmd(conn, cmd->ident, L2CAP_INFO_RSP, माप(buf),
			       buf);
	पूर्ण अन्यथा अणु
		काष्ठा l2cap_info_rsp rsp;
		rsp.type   = cpu_to_le16(type);
		rsp.result = cpu_to_le16(L2CAP_IR_NOTSUPP);
		l2cap_send_cmd(conn, cmd->ident, L2CAP_INFO_RSP, माप(rsp),
			       &rsp);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_inक्रमmation_rsp(काष्ठा l2cap_conn *conn,
					काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
					u8 *data)
अणु
	काष्ठा l2cap_info_rsp *rsp = (काष्ठा l2cap_info_rsp *) data;
	u16 type, result;

	अगर (cmd_len < माप(*rsp))
		वापस -EPROTO;

	type   = __le16_to_cpu(rsp->type);
	result = __le16_to_cpu(rsp->result);

	BT_DBG("type 0x%4.4x result 0x%2.2x", type, result);

	/* L2CAP Info req/rsp are unbound to channels, add extra checks */
	अगर (cmd->ident != conn->info_ident ||
	    conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_DONE)
		वापस 0;

	cancel_delayed_work(&conn->info_समयr);

	अगर (result != L2CAP_IR_SUCCESS) अणु
		conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_DONE;
		conn->info_ident = 0;

		l2cap_conn_start(conn);

		वापस 0;
	पूर्ण

	चयन (type) अणु
	हाल L2CAP_IT_FEAT_MASK:
		conn->feat_mask = get_unaligned_le32(rsp->data);

		अगर (conn->feat_mask & L2CAP_FEAT_FIXED_CHAN) अणु
			काष्ठा l2cap_info_req req;
			req.type = cpu_to_le16(L2CAP_IT_FIXED_CHAN);

			conn->info_ident = l2cap_get_ident(conn);

			l2cap_send_cmd(conn, conn->info_ident,
				       L2CAP_INFO_REQ, माप(req), &req);
		पूर्ण अन्यथा अणु
			conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_DONE;
			conn->info_ident = 0;

			l2cap_conn_start(conn);
		पूर्ण
		अवरोध;

	हाल L2CAP_IT_FIXED_CHAN:
		conn->remote_fixed_chan = rsp->data[0];
		conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_DONE;
		conn->info_ident = 0;

		l2cap_conn_start(conn);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_create_channel_req(काष्ठा l2cap_conn *conn,
				    काष्ठा l2cap_cmd_hdr *cmd,
				    u16 cmd_len, व्योम *data)
अणु
	काष्ठा l2cap_create_chan_req *req = data;
	काष्ठा l2cap_create_chan_rsp rsp;
	काष्ठा l2cap_chan *chan;
	काष्ठा hci_dev *hdev;
	u16 psm, scid;

	अगर (cmd_len != माप(*req))
		वापस -EPROTO;

	अगर (!(conn->local_fixed_chan & L2CAP_FC_A2MP))
		वापस -EINVAL;

	psm = le16_to_cpu(req->psm);
	scid = le16_to_cpu(req->scid);

	BT_DBG("psm 0x%2.2x, scid 0x%4.4x, amp_id %d", psm, scid, req->amp_id);

	/* For controller id 0 make BR/EDR connection */
	अगर (req->amp_id == AMP_ID_BREDR) अणु
		l2cap_connect(conn, cmd, data, L2CAP_CREATE_CHAN_RSP,
			      req->amp_id);
		वापस 0;
	पूर्ण

	/* Validate AMP controller id */
	hdev = hci_dev_get(req->amp_id);
	अगर (!hdev)
		जाओ error;

	अगर (hdev->dev_type != HCI_AMP || !test_bit(HCI_UP, &hdev->flags)) अणु
		hci_dev_put(hdev);
		जाओ error;
	पूर्ण

	chan = l2cap_connect(conn, cmd, data, L2CAP_CREATE_CHAN_RSP,
			     req->amp_id);
	अगर (chan) अणु
		काष्ठा amp_mgr *mgr = conn->hcon->amp_mgr;
		काष्ठा hci_conn *hs_hcon;

		hs_hcon = hci_conn_hash_lookup_ba(hdev, AMP_LINK,
						  &conn->hcon->dst);
		अगर (!hs_hcon) अणु
			hci_dev_put(hdev);
			cmd_reject_invalid_cid(conn, cmd->ident, chan->scid,
					       chan->dcid);
			वापस 0;
		पूर्ण

		BT_DBG("mgr %p bredr_chan %p hs_hcon %p", mgr, chan, hs_hcon);

		mgr->bredr_chan = chan;
		chan->hs_hcon = hs_hcon;
		chan->fcs = L2CAP_FCS_NONE;
		conn->mtu = hdev->block_mtu;
	पूर्ण

	hci_dev_put(hdev);

	वापस 0;

error:
	rsp.dcid = 0;
	rsp.scid = cpu_to_le16(scid);
	rsp.result = cpu_to_le16(L2CAP_CR_BAD_AMP);
	rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);

	l2cap_send_cmd(conn, cmd->ident, L2CAP_CREATE_CHAN_RSP,
		       माप(rsp), &rsp);

	वापस 0;
पूर्ण

अटल व्योम l2cap_send_move_chan_req(काष्ठा l2cap_chan *chan, u8 dest_amp_id)
अणु
	काष्ठा l2cap_move_chan_req req;
	u8 ident;

	BT_DBG("chan %p, dest_amp_id %d", chan, dest_amp_id);

	ident = l2cap_get_ident(chan->conn);
	chan->ident = ident;

	req.icid = cpu_to_le16(chan->scid);
	req.dest_amp_id = dest_amp_id;

	l2cap_send_cmd(chan->conn, ident, L2CAP_MOVE_CHAN_REQ, माप(req),
		       &req);

	__set_chan_समयr(chan, L2CAP_MOVE_TIMEOUT);
पूर्ण

अटल व्योम l2cap_send_move_chan_rsp(काष्ठा l2cap_chan *chan, u16 result)
अणु
	काष्ठा l2cap_move_chan_rsp rsp;

	BT_DBG("chan %p, result 0x%4.4x", chan, result);

	rsp.icid = cpu_to_le16(chan->dcid);
	rsp.result = cpu_to_le16(result);

	l2cap_send_cmd(chan->conn, chan->ident, L2CAP_MOVE_CHAN_RSP,
		       माप(rsp), &rsp);
पूर्ण

अटल व्योम l2cap_send_move_chan_cfm(काष्ठा l2cap_chan *chan, u16 result)
अणु
	काष्ठा l2cap_move_chan_cfm cfm;

	BT_DBG("chan %p, result 0x%4.4x", chan, result);

	chan->ident = l2cap_get_ident(chan->conn);

	cfm.icid = cpu_to_le16(chan->scid);
	cfm.result = cpu_to_le16(result);

	l2cap_send_cmd(chan->conn, chan->ident, L2CAP_MOVE_CHAN_CFM,
		       माप(cfm), &cfm);

	__set_chan_समयr(chan, L2CAP_MOVE_TIMEOUT);
पूर्ण

अटल व्योम l2cap_send_move_chan_cfm_icid(काष्ठा l2cap_conn *conn, u16 icid)
अणु
	काष्ठा l2cap_move_chan_cfm cfm;

	BT_DBG("conn %p, icid 0x%4.4x", conn, icid);

	cfm.icid = cpu_to_le16(icid);
	cfm.result = cpu_to_le16(L2CAP_MC_UNCONFIRMED);

	l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_MOVE_CHAN_CFM,
		       माप(cfm), &cfm);
पूर्ण

अटल व्योम l2cap_send_move_chan_cfm_rsp(काष्ठा l2cap_conn *conn, u8 ident,
					 u16 icid)
अणु
	काष्ठा l2cap_move_chan_cfm_rsp rsp;

	BT_DBG("icid 0x%4.4x", icid);

	rsp.icid = cpu_to_le16(icid);
	l2cap_send_cmd(conn, ident, L2CAP_MOVE_CHAN_CFM_RSP, माप(rsp), &rsp);
पूर्ण

अटल व्योम __release_logical_link(काष्ठा l2cap_chan *chan)
अणु
	chan->hs_hchan = शून्य;
	chan->hs_hcon = शून्य;

	/* Placeholder - release the logical link */
पूर्ण

अटल व्योम l2cap_logical_fail(काष्ठा l2cap_chan *chan)
अणु
	/* Logical link setup failed */
	अगर (chan->state != BT_CONNECTED) अणु
		/* Create channel failure, disconnect */
		l2cap_send_disconn_req(chan, ECONNRESET);
		वापस;
	पूर्ण

	चयन (chan->move_role) अणु
	हाल L2CAP_MOVE_ROLE_RESPONDER:
		l2cap_move_करोne(chan);
		l2cap_send_move_chan_rsp(chan, L2CAP_MR_NOT_SUPP);
		अवरोध;
	हाल L2CAP_MOVE_ROLE_INITIATOR:
		अगर (chan->move_state == L2CAP_MOVE_WAIT_LOGICAL_COMP ||
		    chan->move_state == L2CAP_MOVE_WAIT_LOGICAL_CFM) अणु
			/* Remote has only sent pending or
			 * success responses, clean up
			 */
			l2cap_move_करोne(chan);
		पूर्ण

		/* Other amp move states imply that the move
		 * has alपढ़ोy पातed
		 */
		l2cap_send_move_chan_cfm(chan, L2CAP_MC_UNCONFIRMED);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम l2cap_logical_finish_create(काष्ठा l2cap_chan *chan,
					काष्ठा hci_chan *hchan)
अणु
	काष्ठा l2cap_conf_rsp rsp;

	chan->hs_hchan = hchan;
	chan->hs_hcon->l2cap_data = chan->conn;

	l2cap_send_efs_conf_rsp(chan, &rsp, chan->ident, 0);

	अगर (test_bit(CONF_INPUT_DONE, &chan->conf_state)) अणु
		पूर्णांक err;

		set_शेष_fcs(chan);

		err = l2cap_erपंचांग_init(chan);
		अगर (err < 0)
			l2cap_send_disconn_req(chan, -err);
		अन्यथा
			l2cap_chan_पढ़ोy(chan);
	पूर्ण
पूर्ण

अटल व्योम l2cap_logical_finish_move(काष्ठा l2cap_chan *chan,
				      काष्ठा hci_chan *hchan)
अणु
	chan->hs_hcon = hchan->conn;
	chan->hs_hcon->l2cap_data = chan->conn;

	BT_DBG("move_state %d", chan->move_state);

	चयन (chan->move_state) अणु
	हाल L2CAP_MOVE_WAIT_LOGICAL_COMP:
		/* Move confirm will be sent after a success
		 * response is received
		 */
		chan->move_state = L2CAP_MOVE_WAIT_RSP_SUCCESS;
		अवरोध;
	हाल L2CAP_MOVE_WAIT_LOGICAL_CFM:
		अगर (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) अणु
			chan->move_state = L2CAP_MOVE_WAIT_LOCAL_BUSY;
		पूर्ण अन्यथा अगर (chan->move_role == L2CAP_MOVE_ROLE_INITIATOR) अणु
			chan->move_state = L2CAP_MOVE_WAIT_CONFIRM_RSP;
			l2cap_send_move_chan_cfm(chan, L2CAP_MC_CONFIRMED);
		पूर्ण अन्यथा अगर (chan->move_role == L2CAP_MOVE_ROLE_RESPONDER) अणु
			chan->move_state = L2CAP_MOVE_WAIT_CONFIRM;
			l2cap_send_move_chan_rsp(chan, L2CAP_MR_SUCCESS);
		पूर्ण
		अवरोध;
	शेष:
		/* Move was not in expected state, मुक्त the channel */
		__release_logical_link(chan);

		chan->move_state = L2CAP_MOVE_STABLE;
	पूर्ण
पूर्ण

/* Call with chan locked */
व्योम l2cap_logical_cfm(काष्ठा l2cap_chan *chan, काष्ठा hci_chan *hchan,
		       u8 status)
अणु
	BT_DBG("chan %p, hchan %p, status %d", chan, hchan, status);

	अगर (status) अणु
		l2cap_logical_fail(chan);
		__release_logical_link(chan);
		वापस;
	पूर्ण

	अगर (chan->state != BT_CONNECTED) अणु
		/* Ignore logical link अगर channel is on BR/EDR */
		अगर (chan->local_amp_id != AMP_ID_BREDR)
			l2cap_logical_finish_create(chan, hchan);
	पूर्ण अन्यथा अणु
		l2cap_logical_finish_move(chan, hchan);
	पूर्ण
पूर्ण

व्योम l2cap_move_start(काष्ठा l2cap_chan *chan)
अणु
	BT_DBG("chan %p", chan);

	अगर (chan->local_amp_id == AMP_ID_BREDR) अणु
		अगर (chan->chan_policy != BT_CHANNEL_POLICY_AMP_PREFERRED)
			वापस;
		chan->move_role = L2CAP_MOVE_ROLE_INITIATOR;
		chan->move_state = L2CAP_MOVE_WAIT_PREPARE;
		/* Placeholder - start physical link setup */
	पूर्ण अन्यथा अणु
		chan->move_role = L2CAP_MOVE_ROLE_INITIATOR;
		chan->move_state = L2CAP_MOVE_WAIT_RSP_SUCCESS;
		chan->move_id = 0;
		l2cap_move_setup(chan);
		l2cap_send_move_chan_req(chan, 0);
	पूर्ण
पूर्ण

अटल व्योम l2cap_करो_create(काष्ठा l2cap_chan *chan, पूर्णांक result,
			    u8 local_amp_id, u8 remote_amp_id)
अणु
	BT_DBG("chan %p state %s %u -> %u", chan, state_to_string(chan->state),
	       local_amp_id, remote_amp_id);

	chan->fcs = L2CAP_FCS_NONE;

	/* Outgoing channel on AMP */
	अगर (chan->state == BT_CONNECT) अणु
		अगर (result == L2CAP_CR_SUCCESS) अणु
			chan->local_amp_id = local_amp_id;
			l2cap_send_create_chan_req(chan, remote_amp_id);
		पूर्ण अन्यथा अणु
			/* Revert to BR/EDR connect */
			l2cap_send_conn_req(chan);
		पूर्ण

		वापस;
	पूर्ण

	/* Incoming channel on AMP */
	अगर (__l2cap_no_conn_pending(chan)) अणु
		काष्ठा l2cap_conn_rsp rsp;
		अक्षर buf[128];
		rsp.scid = cpu_to_le16(chan->dcid);
		rsp.dcid = cpu_to_le16(chan->scid);

		अगर (result == L2CAP_CR_SUCCESS) अणु
			/* Send successful response */
			rsp.result = cpu_to_le16(L2CAP_CR_SUCCESS);
			rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
		पूर्ण अन्यथा अणु
			/* Send negative response */
			rsp.result = cpu_to_le16(L2CAP_CR_NO_MEM);
			rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
		पूर्ण

		l2cap_send_cmd(chan->conn, chan->ident, L2CAP_CREATE_CHAN_RSP,
			       माप(rsp), &rsp);

		अगर (result == L2CAP_CR_SUCCESS) अणु
			l2cap_state_change(chan, BT_CONFIG);
			set_bit(CONF_REQ_SENT, &chan->conf_state);
			l2cap_send_cmd(chan->conn, l2cap_get_ident(chan->conn),
				       L2CAP_CONF_REQ,
				       l2cap_build_conf_req(chan, buf, माप(buf)), buf);
			chan->num_conf_req++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम l2cap_करो_move_initiate(काष्ठा l2cap_chan *chan, u8 local_amp_id,
				   u8 remote_amp_id)
अणु
	l2cap_move_setup(chan);
	chan->move_id = local_amp_id;
	chan->move_state = L2CAP_MOVE_WAIT_RSP;

	l2cap_send_move_chan_req(chan, remote_amp_id);
पूर्ण

अटल व्योम l2cap_करो_move_respond(काष्ठा l2cap_chan *chan, पूर्णांक result)
अणु
	काष्ठा hci_chan *hchan = शून्य;

	/* Placeholder - get hci_chan क्रम logical link */

	अगर (hchan) अणु
		अगर (hchan->state == BT_CONNECTED) अणु
			/* Logical link is पढ़ोy to go */
			chan->hs_hcon = hchan->conn;
			chan->hs_hcon->l2cap_data = chan->conn;
			chan->move_state = L2CAP_MOVE_WAIT_CONFIRM;
			l2cap_send_move_chan_rsp(chan, L2CAP_MR_SUCCESS);

			l2cap_logical_cfm(chan, hchan, L2CAP_MR_SUCCESS);
		पूर्ण अन्यथा अणु
			/* Wait क्रम logical link to be पढ़ोy */
			chan->move_state = L2CAP_MOVE_WAIT_LOGICAL_CFM;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Logical link not available */
		l2cap_send_move_chan_rsp(chan, L2CAP_MR_NOT_ALLOWED);
	पूर्ण
पूर्ण

अटल व्योम l2cap_करो_move_cancel(काष्ठा l2cap_chan *chan, पूर्णांक result)
अणु
	अगर (chan->move_role == L2CAP_MOVE_ROLE_RESPONDER) अणु
		u8 rsp_result;
		अगर (result == -EINVAL)
			rsp_result = L2CAP_MR_BAD_ID;
		अन्यथा
			rsp_result = L2CAP_MR_NOT_ALLOWED;

		l2cap_send_move_chan_rsp(chan, rsp_result);
	पूर्ण

	chan->move_role = L2CAP_MOVE_ROLE_NONE;
	chan->move_state = L2CAP_MOVE_STABLE;

	/* Restart data transmission */
	l2cap_erपंचांग_send(chan);
पूर्ण

/* Invoke with locked chan */
व्योम __l2cap_physical_cfm(काष्ठा l2cap_chan *chan, पूर्णांक result)
अणु
	u8 local_amp_id = chan->local_amp_id;
	u8 remote_amp_id = chan->remote_amp_id;

	BT_DBG("chan %p, result %d, local_amp_id %d, remote_amp_id %d",
	       chan, result, local_amp_id, remote_amp_id);

	अगर (chan->state == BT_DISCONN || chan->state == BT_CLOSED)
		वापस;

	अगर (chan->state != BT_CONNECTED) अणु
		l2cap_करो_create(chan, result, local_amp_id, remote_amp_id);
	पूर्ण अन्यथा अगर (result != L2CAP_MR_SUCCESS) अणु
		l2cap_करो_move_cancel(chan, result);
	पूर्ण अन्यथा अणु
		चयन (chan->move_role) अणु
		हाल L2CAP_MOVE_ROLE_INITIATOR:
			l2cap_करो_move_initiate(chan, local_amp_id,
					       remote_amp_id);
			अवरोध;
		हाल L2CAP_MOVE_ROLE_RESPONDER:
			l2cap_करो_move_respond(chan, result);
			अवरोध;
		शेष:
			l2cap_करो_move_cancel(chan, result);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_move_channel_req(काष्ठा l2cap_conn *conn,
					 काष्ठा l2cap_cmd_hdr *cmd,
					 u16 cmd_len, व्योम *data)
अणु
	काष्ठा l2cap_move_chan_req *req = data;
	काष्ठा l2cap_move_chan_rsp rsp;
	काष्ठा l2cap_chan *chan;
	u16 icid = 0;
	u16 result = L2CAP_MR_NOT_ALLOWED;

	अगर (cmd_len != माप(*req))
		वापस -EPROTO;

	icid = le16_to_cpu(req->icid);

	BT_DBG("icid 0x%4.4x, dest_amp_id %d", icid, req->dest_amp_id);

	अगर (!(conn->local_fixed_chan & L2CAP_FC_A2MP))
		वापस -EINVAL;

	chan = l2cap_get_chan_by_dcid(conn, icid);
	अगर (!chan) अणु
		rsp.icid = cpu_to_le16(icid);
		rsp.result = cpu_to_le16(L2CAP_MR_NOT_ALLOWED);
		l2cap_send_cmd(conn, cmd->ident, L2CAP_MOVE_CHAN_RSP,
			       माप(rsp), &rsp);
		वापस 0;
	पूर्ण

	chan->ident = cmd->ident;

	अगर (chan->scid < L2CAP_CID_DYN_START ||
	    chan->chan_policy == BT_CHANNEL_POLICY_BREDR_ONLY ||
	    (chan->mode != L2CAP_MODE_ERTM &&
	     chan->mode != L2CAP_MODE_STREAMING)) अणु
		result = L2CAP_MR_NOT_ALLOWED;
		जाओ send_move_response;
	पूर्ण

	अगर (chan->local_amp_id == req->dest_amp_id) अणु
		result = L2CAP_MR_SAME_ID;
		जाओ send_move_response;
	पूर्ण

	अगर (req->dest_amp_id != AMP_ID_BREDR) अणु
		काष्ठा hci_dev *hdev;
		hdev = hci_dev_get(req->dest_amp_id);
		अगर (!hdev || hdev->dev_type != HCI_AMP ||
		    !test_bit(HCI_UP, &hdev->flags)) अणु
			अगर (hdev)
				hci_dev_put(hdev);

			result = L2CAP_MR_BAD_ID;
			जाओ send_move_response;
		पूर्ण
		hci_dev_put(hdev);
	पूर्ण

	/* Detect a move collision.  Only send a collision response
	 * अगर this side has "lost", otherwise proceed with the move.
	 * The winner has the larger bd_addr.
	 */
	अगर ((__chan_is_moving(chan) ||
	     chan->move_role != L2CAP_MOVE_ROLE_NONE) &&
	    bacmp(&conn->hcon->src, &conn->hcon->dst) > 0) अणु
		result = L2CAP_MR_COLLISION;
		जाओ send_move_response;
	पूर्ण

	chan->move_role = L2CAP_MOVE_ROLE_RESPONDER;
	l2cap_move_setup(chan);
	chan->move_id = req->dest_amp_id;

	अगर (req->dest_amp_id == AMP_ID_BREDR) अणु
		/* Moving to BR/EDR */
		अगर (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) अणु
			chan->move_state = L2CAP_MOVE_WAIT_LOCAL_BUSY;
			result = L2CAP_MR_PEND;
		पूर्ण अन्यथा अणु
			chan->move_state = L2CAP_MOVE_WAIT_CONFIRM;
			result = L2CAP_MR_SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अणु
		chan->move_state = L2CAP_MOVE_WAIT_PREPARE;
		/* Placeholder - uncomment when amp functions are available */
		/*amp_accept_physical(chan, req->dest_amp_id);*/
		result = L2CAP_MR_PEND;
	पूर्ण

send_move_response:
	l2cap_send_move_chan_rsp(chan, result);

	l2cap_chan_unlock(chan);

	वापस 0;
पूर्ण

अटल व्योम l2cap_move_जारी(काष्ठा l2cap_conn *conn, u16 icid, u16 result)
अणु
	काष्ठा l2cap_chan *chan;
	काष्ठा hci_chan *hchan = शून्य;

	chan = l2cap_get_chan_by_scid(conn, icid);
	अगर (!chan) अणु
		l2cap_send_move_chan_cfm_icid(conn, icid);
		वापस;
	पूर्ण

	__clear_chan_समयr(chan);
	अगर (result == L2CAP_MR_PEND)
		__set_chan_समयr(chan, L2CAP_MOVE_ERTX_TIMEOUT);

	चयन (chan->move_state) अणु
	हाल L2CAP_MOVE_WAIT_LOGICAL_COMP:
		/* Move confirm will be sent when logical link
		 * is complete.
		 */
		chan->move_state = L2CAP_MOVE_WAIT_LOGICAL_CFM;
		अवरोध;
	हाल L2CAP_MOVE_WAIT_RSP_SUCCESS:
		अगर (result == L2CAP_MR_PEND) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (test_bit(CONN_LOCAL_BUSY,
				    &chan->conn_state)) अणु
			chan->move_state = L2CAP_MOVE_WAIT_LOCAL_BUSY;
		पूर्ण अन्यथा अणु
			/* Logical link is up or moving to BR/EDR,
			 * proceed with move
			 */
			chan->move_state = L2CAP_MOVE_WAIT_CONFIRM_RSP;
			l2cap_send_move_chan_cfm(chan, L2CAP_MC_CONFIRMED);
		पूर्ण
		अवरोध;
	हाल L2CAP_MOVE_WAIT_RSP:
		/* Moving to AMP */
		अगर (result == L2CAP_MR_SUCCESS) अणु
			/* Remote is पढ़ोy, send confirm immediately
			 * after logical link is पढ़ोy
			 */
			chan->move_state = L2CAP_MOVE_WAIT_LOGICAL_CFM;
		पूर्ण अन्यथा अणु
			/* Both logical link and move success
			 * are required to confirm
			 */
			chan->move_state = L2CAP_MOVE_WAIT_LOGICAL_COMP;
		पूर्ण

		/* Placeholder - get hci_chan क्रम logical link */
		अगर (!hchan) अणु
			/* Logical link not available */
			l2cap_send_move_chan_cfm(chan, L2CAP_MC_UNCONFIRMED);
			अवरोध;
		पूर्ण

		/* If the logical link is not yet connected, करो not
		 * send confirmation.
		 */
		अगर (hchan->state != BT_CONNECTED)
			अवरोध;

		/* Logical link is alपढ़ोy पढ़ोy to go */

		chan->hs_hcon = hchan->conn;
		chan->hs_hcon->l2cap_data = chan->conn;

		अगर (result == L2CAP_MR_SUCCESS) अणु
			/* Can confirm now */
			l2cap_send_move_chan_cfm(chan, L2CAP_MC_CONFIRMED);
		पूर्ण अन्यथा अणु
			/* Now only need move success
			 * to confirm
			 */
			chan->move_state = L2CAP_MOVE_WAIT_RSP_SUCCESS;
		पूर्ण

		l2cap_logical_cfm(chan, hchan, L2CAP_MR_SUCCESS);
		अवरोध;
	शेष:
		/* Any other amp move state means the move failed. */
		chan->move_id = chan->local_amp_id;
		l2cap_move_करोne(chan);
		l2cap_send_move_chan_cfm(chan, L2CAP_MC_UNCONFIRMED);
	पूर्ण

	l2cap_chan_unlock(chan);
पूर्ण

अटल व्योम l2cap_move_fail(काष्ठा l2cap_conn *conn, u8 ident, u16 icid,
			    u16 result)
अणु
	काष्ठा l2cap_chan *chan;

	chan = l2cap_get_chan_by_ident(conn, ident);
	अगर (!chan) अणु
		/* Could not locate channel, icid is best guess */
		l2cap_send_move_chan_cfm_icid(conn, icid);
		वापस;
	पूर्ण

	__clear_chan_समयr(chan);

	अगर (chan->move_role == L2CAP_MOVE_ROLE_INITIATOR) अणु
		अगर (result == L2CAP_MR_COLLISION) अणु
			chan->move_role = L2CAP_MOVE_ROLE_RESPONDER;
		पूर्ण अन्यथा अणु
			/* Cleanup - cancel move */
			chan->move_id = chan->local_amp_id;
			l2cap_move_करोne(chan);
		पूर्ण
	पूर्ण

	l2cap_send_move_chan_cfm(chan, L2CAP_MC_UNCONFIRMED);

	l2cap_chan_unlock(chan);
पूर्ण

अटल पूर्णांक l2cap_move_channel_rsp(काष्ठा l2cap_conn *conn,
				  काष्ठा l2cap_cmd_hdr *cmd,
				  u16 cmd_len, व्योम *data)
अणु
	काष्ठा l2cap_move_chan_rsp *rsp = data;
	u16 icid, result;

	अगर (cmd_len != माप(*rsp))
		वापस -EPROTO;

	icid = le16_to_cpu(rsp->icid);
	result = le16_to_cpu(rsp->result);

	BT_DBG("icid 0x%4.4x, result 0x%4.4x", icid, result);

	अगर (result == L2CAP_MR_SUCCESS || result == L2CAP_MR_PEND)
		l2cap_move_जारी(conn, icid, result);
	अन्यथा
		l2cap_move_fail(conn, cmd->ident, icid, result);

	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_move_channel_confirm(काष्ठा l2cap_conn *conn,
				      काष्ठा l2cap_cmd_hdr *cmd,
				      u16 cmd_len, व्योम *data)
अणु
	काष्ठा l2cap_move_chan_cfm *cfm = data;
	काष्ठा l2cap_chan *chan;
	u16 icid, result;

	अगर (cmd_len != माप(*cfm))
		वापस -EPROTO;

	icid = le16_to_cpu(cfm->icid);
	result = le16_to_cpu(cfm->result);

	BT_DBG("icid 0x%4.4x, result 0x%4.4x", icid, result);

	chan = l2cap_get_chan_by_dcid(conn, icid);
	अगर (!chan) अणु
		/* Spec requires a response even अगर the icid was not found */
		l2cap_send_move_chan_cfm_rsp(conn, cmd->ident, icid);
		वापस 0;
	पूर्ण

	अगर (chan->move_state == L2CAP_MOVE_WAIT_CONFIRM) अणु
		अगर (result == L2CAP_MC_CONFIRMED) अणु
			chan->local_amp_id = chan->move_id;
			अगर (chan->local_amp_id == AMP_ID_BREDR)
				__release_logical_link(chan);
		पूर्ण अन्यथा अणु
			chan->move_id = chan->local_amp_id;
		पूर्ण

		l2cap_move_करोne(chan);
	पूर्ण

	l2cap_send_move_chan_cfm_rsp(conn, cmd->ident, icid);

	l2cap_chan_unlock(chan);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_move_channel_confirm_rsp(काष्ठा l2cap_conn *conn,
						 काष्ठा l2cap_cmd_hdr *cmd,
						 u16 cmd_len, व्योम *data)
अणु
	काष्ठा l2cap_move_chan_cfm_rsp *rsp = data;
	काष्ठा l2cap_chan *chan;
	u16 icid;

	अगर (cmd_len != माप(*rsp))
		वापस -EPROTO;

	icid = le16_to_cpu(rsp->icid);

	BT_DBG("icid 0x%4.4x", icid);

	chan = l2cap_get_chan_by_scid(conn, icid);
	अगर (!chan)
		वापस 0;

	__clear_chan_समयr(chan);

	अगर (chan->move_state == L2CAP_MOVE_WAIT_CONFIRM_RSP) अणु
		chan->local_amp_id = chan->move_id;

		अगर (chan->local_amp_id == AMP_ID_BREDR && chan->hs_hchan)
			__release_logical_link(chan);

		l2cap_move_करोne(chan);
	पूर्ण

	l2cap_chan_unlock(chan);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_conn_param_update_req(काष्ठा l2cap_conn *conn,
					      काष्ठा l2cap_cmd_hdr *cmd,
					      u16 cmd_len, u8 *data)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_conn_param_update_req *req;
	काष्ठा l2cap_conn_param_update_rsp rsp;
	u16 min, max, latency, to_multiplier;
	पूर्णांक err;

	अगर (hcon->role != HCI_ROLE_MASTER)
		वापस -EINVAL;

	अगर (cmd_len != माप(काष्ठा l2cap_conn_param_update_req))
		वापस -EPROTO;

	req = (काष्ठा l2cap_conn_param_update_req *) data;
	min		= __le16_to_cpu(req->min);
	max		= __le16_to_cpu(req->max);
	latency		= __le16_to_cpu(req->latency);
	to_multiplier	= __le16_to_cpu(req->to_multiplier);

	BT_DBG("min 0x%4.4x max 0x%4.4x latency: 0x%4.4x Timeout: 0x%4.4x",
	       min, max, latency, to_multiplier);

	स_रखो(&rsp, 0, माप(rsp));

	err = hci_check_conn_params(min, max, latency, to_multiplier);
	अगर (err)
		rsp.result = cpu_to_le16(L2CAP_CONN_PARAM_REJECTED);
	अन्यथा
		rsp.result = cpu_to_le16(L2CAP_CONN_PARAM_ACCEPTED);

	l2cap_send_cmd(conn, cmd->ident, L2CAP_CONN_PARAM_UPDATE_RSP,
		       माप(rsp), &rsp);

	अगर (!err) अणु
		u8 store_hपूर्णांक;

		store_hपूर्णांक = hci_le_conn_update(hcon, min, max, latency,
						to_multiplier);
		mgmt_new_conn_param(hcon->hdev, &hcon->dst, hcon->dst_type,
				    store_hपूर्णांक, min, max, latency,
				    to_multiplier);

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_le_connect_rsp(काष्ठा l2cap_conn *conn,
				काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				u8 *data)
अणु
	काष्ठा l2cap_le_conn_rsp *rsp = (काष्ठा l2cap_le_conn_rsp *) data;
	काष्ठा hci_conn *hcon = conn->hcon;
	u16 dcid, mtu, mps, credits, result;
	काष्ठा l2cap_chan *chan;
	पूर्णांक err, sec_level;

	अगर (cmd_len < माप(*rsp))
		वापस -EPROTO;

	dcid    = __le16_to_cpu(rsp->dcid);
	mtu     = __le16_to_cpu(rsp->mtu);
	mps     = __le16_to_cpu(rsp->mps);
	credits = __le16_to_cpu(rsp->credits);
	result  = __le16_to_cpu(rsp->result);

	अगर (result == L2CAP_CR_LE_SUCCESS && (mtu < 23 || mps < 23 ||
					   dcid < L2CAP_CID_DYN_START ||
					   dcid > L2CAP_CID_LE_DYN_END))
		वापस -EPROTO;

	BT_DBG("dcid 0x%4.4x mtu %u mps %u credits %u result 0x%2.2x",
	       dcid, mtu, mps, credits, result);

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_ident(conn, cmd->ident);
	अगर (!chan) अणु
		err = -EBADSLT;
		जाओ unlock;
	पूर्ण

	err = 0;

	l2cap_chan_lock(chan);

	चयन (result) अणु
	हाल L2CAP_CR_LE_SUCCESS:
		अगर (__l2cap_get_chan_by_dcid(conn, dcid)) अणु
			err = -EBADSLT;
			अवरोध;
		पूर्ण

		chan->ident = 0;
		chan->dcid = dcid;
		chan->omtu = mtu;
		chan->remote_mps = mps;
		chan->tx_credits = credits;
		l2cap_chan_पढ़ोy(chan);
		अवरोध;

	हाल L2CAP_CR_LE_AUTHENTICATION:
	हाल L2CAP_CR_LE_ENCRYPTION:
		/* If we alपढ़ोy have MITM protection we can't करो
		 * anything.
		 */
		अगर (hcon->sec_level > BT_SECURITY_MEDIUM) अणु
			l2cap_chan_del(chan, ECONNREFUSED);
			अवरोध;
		पूर्ण

		sec_level = hcon->sec_level + 1;
		अगर (chan->sec_level < sec_level)
			chan->sec_level = sec_level;

		/* We'll need to send a new Connect Request */
		clear_bit(FLAG_LE_CONN_REQ_SENT, &chan->flags);

		smp_conn_security(hcon, chan->sec_level);
		अवरोध;

	शेष:
		l2cap_chan_del(chan, ECONNREFUSED);
		अवरोध;
	पूर्ण

	l2cap_chan_unlock(chan);

unlock:
	mutex_unlock(&conn->chan_lock);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_bredr_sig_cmd(काष्ठा l2cap_conn *conn,
				      काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				      u8 *data)
अणु
	पूर्णांक err = 0;

	चयन (cmd->code) अणु
	हाल L2CAP_COMMAND_REJ:
		l2cap_command_rej(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_CONN_REQ:
		err = l2cap_connect_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_CONN_RSP:
	हाल L2CAP_CREATE_CHAN_RSP:
		l2cap_connect_create_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_CONF_REQ:
		err = l2cap_config_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_CONF_RSP:
		l2cap_config_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_DISCONN_REQ:
		err = l2cap_disconnect_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_DISCONN_RSP:
		l2cap_disconnect_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_ECHO_REQ:
		l2cap_send_cmd(conn, cmd->ident, L2CAP_ECHO_RSP, cmd_len, data);
		अवरोध;

	हाल L2CAP_ECHO_RSP:
		अवरोध;

	हाल L2CAP_INFO_REQ:
		err = l2cap_inक्रमmation_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_INFO_RSP:
		l2cap_inक्रमmation_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_CREATE_CHAN_REQ:
		err = l2cap_create_channel_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_MOVE_CHAN_REQ:
		err = l2cap_move_channel_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_MOVE_CHAN_RSP:
		l2cap_move_channel_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_MOVE_CHAN_CFM:
		err = l2cap_move_channel_confirm(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_MOVE_CHAN_CFM_RSP:
		l2cap_move_channel_confirm_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	शेष:
		BT_ERR("Unknown BR/EDR signaling command 0x%2.2x", cmd->code);
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_le_connect_req(काष्ठा l2cap_conn *conn,
				काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				u8 *data)
अणु
	काष्ठा l2cap_le_conn_req *req = (काष्ठा l2cap_le_conn_req *) data;
	काष्ठा l2cap_le_conn_rsp rsp;
	काष्ठा l2cap_chan *chan, *pchan;
	u16 dcid, scid, credits, mtu, mps;
	__le16 psm;
	u8 result;

	अगर (cmd_len != माप(*req))
		वापस -EPROTO;

	scid = __le16_to_cpu(req->scid);
	mtu  = __le16_to_cpu(req->mtu);
	mps  = __le16_to_cpu(req->mps);
	psm  = req->psm;
	dcid = 0;
	credits = 0;

	अगर (mtu < 23 || mps < 23)
		वापस -EPROTO;

	BT_DBG("psm 0x%2.2x scid 0x%4.4x mtu %u mps %u", __le16_to_cpu(psm),
	       scid, mtu, mps);

	/* Check अगर we have socket listening on psm */
	pchan = l2cap_global_chan_by_psm(BT_LISTEN, psm, &conn->hcon->src,
					 &conn->hcon->dst, LE_LINK);
	अगर (!pchan) अणु
		result = L2CAP_CR_LE_BAD_PSM;
		chan = शून्य;
		जाओ response;
	पूर्ण

	mutex_lock(&conn->chan_lock);
	l2cap_chan_lock(pchan);

	अगर (!smp_sufficient_security(conn->hcon, pchan->sec_level,
				     SMP_ALLOW_STK)) अणु
		result = L2CAP_CR_LE_AUTHENTICATION;
		chan = शून्य;
		जाओ response_unlock;
	पूर्ण

	/* Check क्रम valid dynamic CID range */
	अगर (scid < L2CAP_CID_DYN_START || scid > L2CAP_CID_LE_DYN_END) अणु
		result = L2CAP_CR_LE_INVALID_SCID;
		chan = शून्य;
		जाओ response_unlock;
	पूर्ण

	/* Check अगर we alपढ़ोy have channel with that dcid */
	अगर (__l2cap_get_chan_by_dcid(conn, scid)) अणु
		result = L2CAP_CR_LE_SCID_IN_USE;
		chan = शून्य;
		जाओ response_unlock;
	पूर्ण

	chan = pchan->ops->new_connection(pchan);
	अगर (!chan) अणु
		result = L2CAP_CR_LE_NO_MEM;
		जाओ response_unlock;
	पूर्ण

	bacpy(&chan->src, &conn->hcon->src);
	bacpy(&chan->dst, &conn->hcon->dst);
	chan->src_type = bdaddr_src_type(conn->hcon);
	chan->dst_type = bdaddr_dst_type(conn->hcon);
	chan->psm  = psm;
	chan->dcid = scid;
	chan->omtu = mtu;
	chan->remote_mps = mps;

	__l2cap_chan_add(conn, chan);

	l2cap_le_flowctl_init(chan, __le16_to_cpu(req->credits));

	dcid = chan->scid;
	credits = chan->rx_credits;

	__set_chan_समयr(chan, chan->ops->get_sndसमयo(chan));

	chan->ident = cmd->ident;

	अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags)) अणु
		l2cap_state_change(chan, BT_CONNECT2);
		/* The following result value is actually not defined
		 * क्रम LE CoC but we use it to let the function know
		 * that it should bail out after करोing its cleanup
		 * instead of sending a response.
		 */
		result = L2CAP_CR_PEND;
		chan->ops->defer(chan);
	पूर्ण अन्यथा अणु
		l2cap_chan_पढ़ोy(chan);
		result = L2CAP_CR_LE_SUCCESS;
	पूर्ण

response_unlock:
	l2cap_chan_unlock(pchan);
	mutex_unlock(&conn->chan_lock);
	l2cap_chan_put(pchan);

	अगर (result == L2CAP_CR_PEND)
		वापस 0;

response:
	अगर (chan) अणु
		rsp.mtu = cpu_to_le16(chan->imtu);
		rsp.mps = cpu_to_le16(chan->mps);
	पूर्ण अन्यथा अणु
		rsp.mtu = 0;
		rsp.mps = 0;
	पूर्ण

	rsp.dcid    = cpu_to_le16(dcid);
	rsp.credits = cpu_to_le16(credits);
	rsp.result  = cpu_to_le16(result);

	l2cap_send_cmd(conn, cmd->ident, L2CAP_LE_CONN_RSP, माप(rsp), &rsp);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_le_credits(काष्ठा l2cap_conn *conn,
				   काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
अणु
	काष्ठा l2cap_le_credits *pkt;
	काष्ठा l2cap_chan *chan;
	u16 cid, credits, max_credits;

	अगर (cmd_len != माप(*pkt))
		वापस -EPROTO;

	pkt = (काष्ठा l2cap_le_credits *) data;
	cid	= __le16_to_cpu(pkt->cid);
	credits	= __le16_to_cpu(pkt->credits);

	BT_DBG("cid 0x%4.4x credits 0x%4.4x", cid, credits);

	chan = l2cap_get_chan_by_dcid(conn, cid);
	अगर (!chan)
		वापस -EBADSLT;

	max_credits = LE_FLOWCTL_MAX_CREDITS - chan->tx_credits;
	अगर (credits > max_credits) अणु
		BT_ERR("LE credits overflow");
		l2cap_send_disconn_req(chan, ECONNRESET);
		l2cap_chan_unlock(chan);

		/* Return 0 so that we करोn't trigger an unnecessary
		 * command reject packet.
		 */
		वापस 0;
	पूर्ण

	chan->tx_credits += credits;

	/* Resume sending */
	l2cap_le_flowctl_send(chan);

	अगर (chan->tx_credits)
		chan->ops->resume(chan);

	l2cap_chan_unlock(chan);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_ecred_conn_req(काष्ठा l2cap_conn *conn,
				       काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
अणु
	काष्ठा l2cap_ecred_conn_req *req = (व्योम *) data;
	काष्ठा अणु
		काष्ठा l2cap_ecred_conn_rsp rsp;
		__le16 dcid[L2CAP_ECRED_MAX_CID];
	पूर्ण __packed pdu;
	काष्ठा l2cap_chan *chan, *pchan;
	u16 mtu, mps;
	__le16 psm;
	u8 result, len = 0;
	पूर्णांक i, num_scid;
	bool defer = false;

	अगर (!enable_ecred)
		वापस -EINVAL;

	अगर (cmd_len < माप(*req) || (cmd_len - माप(*req)) % माप(u16)) अणु
		result = L2CAP_CR_LE_INVALID_PARAMS;
		जाओ response;
	पूर्ण

	cmd_len -= माप(*req);
	num_scid = cmd_len / माप(u16);

	अगर (num_scid > ARRAY_SIZE(pdu.dcid)) अणु
		result = L2CAP_CR_LE_INVALID_PARAMS;
		जाओ response;
	पूर्ण

	mtu  = __le16_to_cpu(req->mtu);
	mps  = __le16_to_cpu(req->mps);

	अगर (mtu < L2CAP_ECRED_MIN_MTU || mps < L2CAP_ECRED_MIN_MPS) अणु
		result = L2CAP_CR_LE_UNACCEPT_PARAMS;
		जाओ response;
	पूर्ण

	psm  = req->psm;

	BT_DBG("psm 0x%2.2x mtu %u mps %u", __le16_to_cpu(psm), mtu, mps);

	स_रखो(&pdu, 0, माप(pdu));

	/* Check अगर we have socket listening on psm */
	pchan = l2cap_global_chan_by_psm(BT_LISTEN, psm, &conn->hcon->src,
					 &conn->hcon->dst, LE_LINK);
	अगर (!pchan) अणु
		result = L2CAP_CR_LE_BAD_PSM;
		जाओ response;
	पूर्ण

	mutex_lock(&conn->chan_lock);
	l2cap_chan_lock(pchan);

	अगर (!smp_sufficient_security(conn->hcon, pchan->sec_level,
				     SMP_ALLOW_STK)) अणु
		result = L2CAP_CR_LE_AUTHENTICATION;
		जाओ unlock;
	पूर्ण

	result = L2CAP_CR_LE_SUCCESS;

	क्रम (i = 0; i < num_scid; i++) अणु
		u16 scid = __le16_to_cpu(req->scid[i]);

		BT_DBG("scid[%d] 0x%4.4x", i, scid);

		pdu.dcid[i] = 0x0000;
		len += माप(*pdu.dcid);

		/* Check क्रम valid dynamic CID range */
		अगर (scid < L2CAP_CID_DYN_START || scid > L2CAP_CID_LE_DYN_END) अणु
			result = L2CAP_CR_LE_INVALID_SCID;
			जारी;
		पूर्ण

		/* Check अगर we alपढ़ोy have channel with that dcid */
		अगर (__l2cap_get_chan_by_dcid(conn, scid)) अणु
			result = L2CAP_CR_LE_SCID_IN_USE;
			जारी;
		पूर्ण

		chan = pchan->ops->new_connection(pchan);
		अगर (!chan) अणु
			result = L2CAP_CR_LE_NO_MEM;
			जारी;
		पूर्ण

		bacpy(&chan->src, &conn->hcon->src);
		bacpy(&chan->dst, &conn->hcon->dst);
		chan->src_type = bdaddr_src_type(conn->hcon);
		chan->dst_type = bdaddr_dst_type(conn->hcon);
		chan->psm  = psm;
		chan->dcid = scid;
		chan->omtu = mtu;
		chan->remote_mps = mps;

		__l2cap_chan_add(conn, chan);

		l2cap_ecred_init(chan, __le16_to_cpu(req->credits));

		/* Init response */
		अगर (!pdu.rsp.credits) अणु
			pdu.rsp.mtu = cpu_to_le16(chan->imtu);
			pdu.rsp.mps = cpu_to_le16(chan->mps);
			pdu.rsp.credits = cpu_to_le16(chan->rx_credits);
		पूर्ण

		pdu.dcid[i] = cpu_to_le16(chan->scid);

		__set_chan_समयr(chan, chan->ops->get_sndसमयo(chan));

		chan->ident = cmd->ident;

		अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags)) अणु
			l2cap_state_change(chan, BT_CONNECT2);
			defer = true;
			chan->ops->defer(chan);
		पूर्ण अन्यथा अणु
			l2cap_chan_पढ़ोy(chan);
		पूर्ण
	पूर्ण

unlock:
	l2cap_chan_unlock(pchan);
	mutex_unlock(&conn->chan_lock);
	l2cap_chan_put(pchan);

response:
	pdu.rsp.result = cpu_to_le16(result);

	अगर (defer)
		वापस 0;

	l2cap_send_cmd(conn, cmd->ident, L2CAP_ECRED_CONN_RSP,
		       माप(pdu.rsp) + len, &pdu);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_ecred_conn_rsp(काष्ठा l2cap_conn *conn,
				       काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
अणु
	काष्ठा l2cap_ecred_conn_rsp *rsp = (व्योम *) data;
	काष्ठा hci_conn *hcon = conn->hcon;
	u16 mtu, mps, credits, result;
	काष्ठा l2cap_chan *chan;
	पूर्णांक err = 0, sec_level;
	पूर्णांक i = 0;

	अगर (cmd_len < माप(*rsp))
		वापस -EPROTO;

	mtu     = __le16_to_cpu(rsp->mtu);
	mps     = __le16_to_cpu(rsp->mps);
	credits = __le16_to_cpu(rsp->credits);
	result  = __le16_to_cpu(rsp->result);

	BT_DBG("mtu %u mps %u credits %u result 0x%4.4x", mtu, mps, credits,
	       result);

	mutex_lock(&conn->chan_lock);

	cmd_len -= माप(*rsp);

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		u16 dcid;

		अगर (chan->ident != cmd->ident ||
		    chan->mode != L2CAP_MODE_EXT_FLOWCTL ||
		    chan->state == BT_CONNECTED)
			जारी;

		l2cap_chan_lock(chan);

		/* Check that there is a dcid क्रम each pending channel */
		अगर (cmd_len < माप(dcid)) अणु
			l2cap_chan_del(chan, ECONNREFUSED);
			l2cap_chan_unlock(chan);
			जारी;
		पूर्ण

		dcid = __le16_to_cpu(rsp->dcid[i++]);
		cmd_len -= माप(u16);

		BT_DBG("dcid[%d] 0x%4.4x", i, dcid);

		/* Check अगर dcid is alपढ़ोy in use */
		अगर (dcid && __l2cap_get_chan_by_dcid(conn, dcid)) अणु
			/* If a device receives a
			 * L2CAP_CREDIT_BASED_CONNECTION_RSP packet with an
			 * alपढ़ोy-asचिन्हित Destination CID, then both the
			 * original channel and the new channel shall be
			 * immediately discarded and not used.
			 */
			l2cap_chan_del(chan, ECONNREFUSED);
			l2cap_chan_unlock(chan);
			chan = __l2cap_get_chan_by_dcid(conn, dcid);
			l2cap_chan_lock(chan);
			l2cap_chan_del(chan, ECONNRESET);
			l2cap_chan_unlock(chan);
			जारी;
		पूर्ण

		चयन (result) अणु
		हाल L2CAP_CR_LE_AUTHENTICATION:
		हाल L2CAP_CR_LE_ENCRYPTION:
			/* If we alपढ़ोy have MITM protection we can't करो
			 * anything.
			 */
			अगर (hcon->sec_level > BT_SECURITY_MEDIUM) अणु
				l2cap_chan_del(chan, ECONNREFUSED);
				अवरोध;
			पूर्ण

			sec_level = hcon->sec_level + 1;
			अगर (chan->sec_level < sec_level)
				chan->sec_level = sec_level;

			/* We'll need to send a new Connect Request */
			clear_bit(FLAG_ECRED_CONN_REQ_SENT, &chan->flags);

			smp_conn_security(hcon, chan->sec_level);
			अवरोध;

		हाल L2CAP_CR_LE_BAD_PSM:
			l2cap_chan_del(chan, ECONNREFUSED);
			अवरोध;

		शेष:
			/* If dcid was not set it means channels was refused */
			अगर (!dcid) अणु
				l2cap_chan_del(chan, ECONNREFUSED);
				अवरोध;
			पूर्ण

			chan->ident = 0;
			chan->dcid = dcid;
			chan->omtu = mtu;
			chan->remote_mps = mps;
			chan->tx_credits = credits;
			l2cap_chan_पढ़ोy(chan);
			अवरोध;
		पूर्ण

		l2cap_chan_unlock(chan);
	पूर्ण

	mutex_unlock(&conn->chan_lock);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_ecred_reconf_req(काष्ठा l2cap_conn *conn,
					 काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
					 u8 *data)
अणु
	काष्ठा l2cap_ecred_reconf_req *req = (व्योम *) data;
	काष्ठा l2cap_ecred_reconf_rsp rsp;
	u16 mtu, mps, result;
	काष्ठा l2cap_chan *chan;
	पूर्णांक i, num_scid;

	अगर (!enable_ecred)
		वापस -EINVAL;

	अगर (cmd_len < माप(*req) || cmd_len - माप(*req) % माप(u16)) अणु
		result = L2CAP_CR_LE_INVALID_PARAMS;
		जाओ respond;
	पूर्ण

	mtu = __le16_to_cpu(req->mtu);
	mps = __le16_to_cpu(req->mps);

	BT_DBG("mtu %u mps %u", mtu, mps);

	अगर (mtu < L2CAP_ECRED_MIN_MTU) अणु
		result = L2CAP_RECONF_INVALID_MTU;
		जाओ respond;
	पूर्ण

	अगर (mps < L2CAP_ECRED_MIN_MPS) अणु
		result = L2CAP_RECONF_INVALID_MPS;
		जाओ respond;
	पूर्ण

	cmd_len -= माप(*req);
	num_scid = cmd_len / माप(u16);
	result = L2CAP_RECONF_SUCCESS;

	क्रम (i = 0; i < num_scid; i++) अणु
		u16 scid;

		scid = __le16_to_cpu(req->scid[i]);
		अगर (!scid)
			वापस -EPROTO;

		chan = __l2cap_get_chan_by_dcid(conn, scid);
		अगर (!chan)
			जारी;

		/* If the MTU value is decreased क्रम any of the included
		 * channels, then the receiver shall disconnect all
		 * included channels.
		 */
		अगर (chan->omtu > mtu) अणु
			BT_ERR("chan %p decreased MTU %u -> %u", chan,
			       chan->omtu, mtu);
			result = L2CAP_RECONF_INVALID_MTU;
		पूर्ण

		chan->omtu = mtu;
		chan->remote_mps = mps;
	पूर्ण

respond:
	rsp.result = cpu_to_le16(result);

	l2cap_send_cmd(conn, cmd->ident, L2CAP_ECRED_RECONF_RSP, माप(rsp),
		       &rsp);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_ecred_reconf_rsp(काष्ठा l2cap_conn *conn,
					 काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
					 u8 *data)
अणु
	काष्ठा l2cap_chan *chan;
	काष्ठा l2cap_ecred_conn_rsp *rsp = (व्योम *) data;
	u16 result;

	अगर (cmd_len < माप(*rsp))
		वापस -EPROTO;

	result = __le16_to_cpu(rsp->result);

	BT_DBG("result 0x%4.4x", rsp->result);

	अगर (!result)
		वापस 0;

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		अगर (chan->ident != cmd->ident)
			जारी;

		l2cap_chan_del(chan, ECONNRESET);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_le_command_rej(काष्ठा l2cap_conn *conn,
				       काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
अणु
	काष्ठा l2cap_cmd_rej_unk *rej = (काष्ठा l2cap_cmd_rej_unk *) data;
	काष्ठा l2cap_chan *chan;

	अगर (cmd_len < माप(*rej))
		वापस -EPROTO;

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_ident(conn, cmd->ident);
	अगर (!chan)
		जाओ करोne;

	l2cap_chan_lock(chan);
	l2cap_chan_del(chan, ECONNREFUSED);
	l2cap_chan_unlock(chan);

करोne:
	mutex_unlock(&conn->chan_lock);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_le_sig_cmd(काष्ठा l2cap_conn *conn,
				   काष्ठा l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
अणु
	पूर्णांक err = 0;

	चयन (cmd->code) अणु
	हाल L2CAP_COMMAND_REJ:
		l2cap_le_command_rej(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_CONN_PARAM_UPDATE_REQ:
		err = l2cap_conn_param_update_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_CONN_PARAM_UPDATE_RSP:
		अवरोध;

	हाल L2CAP_LE_CONN_RSP:
		l2cap_le_connect_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_LE_CONN_REQ:
		err = l2cap_le_connect_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_LE_CREDITS:
		err = l2cap_le_credits(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_ECRED_CONN_REQ:
		err = l2cap_ecred_conn_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_ECRED_CONN_RSP:
		err = l2cap_ecred_conn_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_ECRED_RECONF_REQ:
		err = l2cap_ecred_reconf_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_ECRED_RECONF_RSP:
		err = l2cap_ecred_reconf_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_DISCONN_REQ:
		err = l2cap_disconnect_req(conn, cmd, cmd_len, data);
		अवरोध;

	हाल L2CAP_DISCONN_RSP:
		l2cap_disconnect_rsp(conn, cmd, cmd_len, data);
		अवरोध;

	शेष:
		BT_ERR("Unknown LE signaling command 0x%2.2x", cmd->code);
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत व्योम l2cap_le_sig_channel(काष्ठा l2cap_conn *conn,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_cmd_hdr *cmd;
	u16 len;
	पूर्णांक err;

	अगर (hcon->type != LE_LINK)
		जाओ drop;

	अगर (skb->len < L2CAP_CMD_HDR_SIZE)
		जाओ drop;

	cmd = (व्योम *) skb->data;
	skb_pull(skb, L2CAP_CMD_HDR_SIZE);

	len = le16_to_cpu(cmd->len);

	BT_DBG("code 0x%2.2x len %d id 0x%2.2x", cmd->code, len, cmd->ident);

	अगर (len != skb->len || !cmd->ident) अणु
		BT_DBG("corrupted command");
		जाओ drop;
	पूर्ण

	err = l2cap_le_sig_cmd(conn, cmd, len, skb->data);
	अगर (err) अणु
		काष्ठा l2cap_cmd_rej_unk rej;

		BT_ERR("Wrong link type (%d)", err);

		rej.reason = cpu_to_le16(L2CAP_REJ_NOT_UNDERSTOOD);
		l2cap_send_cmd(conn, cmd->ident, L2CAP_COMMAND_REJ,
			       माप(rej), &rej);
	पूर्ण

drop:
	kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत व्योम l2cap_sig_channel(काष्ठा l2cap_conn *conn,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_cmd_hdr *cmd;
	पूर्णांक err;

	l2cap_raw_recv(conn, skb);

	अगर (hcon->type != ACL_LINK)
		जाओ drop;

	जबतक (skb->len >= L2CAP_CMD_HDR_SIZE) अणु
		u16 len;

		cmd = (व्योम *) skb->data;
		skb_pull(skb, L2CAP_CMD_HDR_SIZE);

		len = le16_to_cpu(cmd->len);

		BT_DBG("code 0x%2.2x len %d id 0x%2.2x", cmd->code, len,
		       cmd->ident);

		अगर (len > skb->len || !cmd->ident) अणु
			BT_DBG("corrupted command");
			अवरोध;
		पूर्ण

		err = l2cap_bredr_sig_cmd(conn, cmd, len, skb->data);
		अगर (err) अणु
			काष्ठा l2cap_cmd_rej_unk rej;

			BT_ERR("Wrong link type (%d)", err);

			rej.reason = cpu_to_le16(L2CAP_REJ_NOT_UNDERSTOOD);
			l2cap_send_cmd(conn, cmd->ident, L2CAP_COMMAND_REJ,
				       माप(rej), &rej);
		पूर्ण

		skb_pull(skb, len);
	पूर्ण

drop:
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक l2cap_check_fcs(काष्ठा l2cap_chan *chan,  काष्ठा sk_buff *skb)
अणु
	u16 our_fcs, rcv_fcs;
	पूर्णांक hdr_size;

	अगर (test_bit(FLAG_EXT_CTRL, &chan->flags))
		hdr_size = L2CAP_EXT_HDR_SIZE;
	अन्यथा
		hdr_size = L2CAP_ENH_HDR_SIZE;

	अगर (chan->fcs == L2CAP_FCS_CRC16) अणु
		skb_trim(skb, skb->len - L2CAP_FCS_SIZE);
		rcv_fcs = get_unaligned_le16(skb->data + skb->len);
		our_fcs = crc16(0, skb->data - hdr_size, skb->len + hdr_size);

		अगर (our_fcs != rcv_fcs)
			वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम l2cap_send_i_or_rr_or_rnr(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_ctrl control;

	BT_DBG("chan %p", chan);

	स_रखो(&control, 0, माप(control));
	control.sframe = 1;
	control.final = 1;
	control.reqseq = chan->buffer_seq;
	set_bit(CONN_SEND_FBIT, &chan->conn_state);

	अगर (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) अणु
		control.super = L2CAP_SUPER_RNR;
		l2cap_send_sframe(chan, &control);
	पूर्ण

	अगर (test_and_clear_bit(CONN_REMOTE_BUSY, &chan->conn_state) &&
	    chan->unacked_frames > 0)
		__set_retrans_समयr(chan);

	/* Send pending अगरrames */
	l2cap_erपंचांग_send(chan);

	अगर (!test_bit(CONN_LOCAL_BUSY, &chan->conn_state) &&
	    test_bit(CONN_SEND_FBIT, &chan->conn_state)) अणु
		/* F-bit wasn't sent in an s-frame or i-frame yet, so
		 * send it now.
		 */
		control.super = L2CAP_SUPER_RR;
		l2cap_send_sframe(chan, &control);
	पूर्ण
पूर्ण

अटल व्योम append_skb_frag(काष्ठा sk_buff *skb, काष्ठा sk_buff *new_frag,
			    काष्ठा sk_buff **last_frag)
अणु
	/* skb->len reflects data in skb as well as all fragments
	 * skb->data_len reflects only data in fragments
	 */
	अगर (!skb_has_frag_list(skb))
		skb_shinfo(skb)->frag_list = new_frag;

	new_frag->next = शून्य;

	(*last_frag)->next = new_frag;
	*last_frag = new_frag;

	skb->len += new_frag->len;
	skb->data_len += new_frag->len;
	skb->truesize += new_frag->truesize;
पूर्ण

अटल पूर्णांक l2cap_reassemble_sdu(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb,
				काष्ठा l2cap_ctrl *control)
अणु
	पूर्णांक err = -EINVAL;

	चयन (control->sar) अणु
	हाल L2CAP_SAR_UNSEGMENTED:
		अगर (chan->sdu)
			अवरोध;

		err = chan->ops->recv(chan, skb);
		अवरोध;

	हाल L2CAP_SAR_START:
		अगर (chan->sdu)
			अवरोध;

		अगर (!pskb_may_pull(skb, L2CAP_SDULEN_SIZE))
			अवरोध;

		chan->sdu_len = get_unaligned_le16(skb->data);
		skb_pull(skb, L2CAP_SDULEN_SIZE);

		अगर (chan->sdu_len > chan->imtu) अणु
			err = -EMSGSIZE;
			अवरोध;
		पूर्ण

		अगर (skb->len >= chan->sdu_len)
			अवरोध;

		chan->sdu = skb;
		chan->sdu_last_frag = skb;

		skb = शून्य;
		err = 0;
		अवरोध;

	हाल L2CAP_SAR_CONTINUE:
		अगर (!chan->sdu)
			अवरोध;

		append_skb_frag(chan->sdu, skb,
				&chan->sdu_last_frag);
		skb = शून्य;

		अगर (chan->sdu->len >= chan->sdu_len)
			अवरोध;

		err = 0;
		अवरोध;

	हाल L2CAP_SAR_END:
		अगर (!chan->sdu)
			अवरोध;

		append_skb_frag(chan->sdu, skb,
				&chan->sdu_last_frag);
		skb = शून्य;

		अगर (chan->sdu->len != chan->sdu_len)
			अवरोध;

		err = chan->ops->recv(chan, chan->sdu);

		अगर (!err) अणु
			/* Reassembly complete */
			chan->sdu = शून्य;
			chan->sdu_last_frag = शून्य;
			chan->sdu_len = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (err) अणु
		kमुक्त_skb(skb);
		kमुक्त_skb(chan->sdu);
		chan->sdu = शून्य;
		chan->sdu_last_frag = शून्य;
		chan->sdu_len = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_resegment(काष्ठा l2cap_chan *chan)
अणु
	/* Placeholder */
	वापस 0;
पूर्ण

व्योम l2cap_chan_busy(काष्ठा l2cap_chan *chan, पूर्णांक busy)
अणु
	u8 event;

	अगर (chan->mode != L2CAP_MODE_ERTM)
		वापस;

	event = busy ? L2CAP_EV_LOCAL_BUSY_DETECTED : L2CAP_EV_LOCAL_BUSY_CLEAR;
	l2cap_tx(chan, शून्य, शून्य, event);
पूर्ण

अटल पूर्णांक l2cap_rx_queued_अगरrames(काष्ठा l2cap_chan *chan)
अणु
	पूर्णांक err = 0;
	/* Pass sequential frames to l2cap_reassemble_sdu()
	 * until a gap is encountered.
	 */

	BT_DBG("chan %p", chan);

	जबतक (!test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) अणु
		काष्ठा sk_buff *skb;
		BT_DBG("Searching for skb with txseq %d (queue len %d)",
		       chan->buffer_seq, skb_queue_len(&chan->srej_q));

		skb = l2cap_erपंचांग_seq_in_queue(&chan->srej_q, chan->buffer_seq);

		अगर (!skb)
			अवरोध;

		skb_unlink(skb, &chan->srej_q);
		chan->buffer_seq = __next_seq(chan, chan->buffer_seq);
		err = l2cap_reassemble_sdu(chan, skb, &bt_cb(skb)->l2cap);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (skb_queue_empty(&chan->srej_q)) अणु
		chan->rx_state = L2CAP_RX_STATE_RECV;
		l2cap_send_ack(chan);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम l2cap_handle_srej(काष्ठा l2cap_chan *chan,
			      काष्ठा l2cap_ctrl *control)
अणु
	काष्ठा sk_buff *skb;

	BT_DBG("chan %p, control %p", chan, control);

	अगर (control->reqseq == chan->next_tx_seq) अणु
		BT_DBG("Invalid reqseq %d, disconnecting", control->reqseq);
		l2cap_send_disconn_req(chan, ECONNRESET);
		वापस;
	पूर्ण

	skb = l2cap_erपंचांग_seq_in_queue(&chan->tx_q, control->reqseq);

	अगर (skb == शून्य) अणु
		BT_DBG("Seq %d not available for retransmission",
		       control->reqseq);
		वापस;
	पूर्ण

	अगर (chan->max_tx != 0 && bt_cb(skb)->l2cap.retries >= chan->max_tx) अणु
		BT_DBG("Retry limit exceeded (%d)", chan->max_tx);
		l2cap_send_disconn_req(chan, ECONNRESET);
		वापस;
	पूर्ण

	clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

	अगर (control->poll) अणु
		l2cap_pass_to_tx(chan, control);

		set_bit(CONN_SEND_FBIT, &chan->conn_state);
		l2cap_retransmit(chan, control);
		l2cap_erपंचांग_send(chan);

		अगर (chan->tx_state == L2CAP_TX_STATE_WAIT_F) अणु
			set_bit(CONN_SREJ_ACT, &chan->conn_state);
			chan->srej_save_reqseq = control->reqseq;
		पूर्ण
	पूर्ण अन्यथा अणु
		l2cap_pass_to_tx_fbit(chan, control);

		अगर (control->final) अणु
			अगर (chan->srej_save_reqseq != control->reqseq ||
			    !test_and_clear_bit(CONN_SREJ_ACT,
						&chan->conn_state))
				l2cap_retransmit(chan, control);
		पूर्ण अन्यथा अणु
			l2cap_retransmit(chan, control);
			अगर (chan->tx_state == L2CAP_TX_STATE_WAIT_F) अणु
				set_bit(CONN_SREJ_ACT, &chan->conn_state);
				chan->srej_save_reqseq = control->reqseq;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम l2cap_handle_rej(काष्ठा l2cap_chan *chan,
			     काष्ठा l2cap_ctrl *control)
अणु
	काष्ठा sk_buff *skb;

	BT_DBG("chan %p, control %p", chan, control);

	अगर (control->reqseq == chan->next_tx_seq) अणु
		BT_DBG("Invalid reqseq %d, disconnecting", control->reqseq);
		l2cap_send_disconn_req(chan, ECONNRESET);
		वापस;
	पूर्ण

	skb = l2cap_erपंचांग_seq_in_queue(&chan->tx_q, control->reqseq);

	अगर (chan->max_tx && skb &&
	    bt_cb(skb)->l2cap.retries >= chan->max_tx) अणु
		BT_DBG("Retry limit exceeded (%d)", chan->max_tx);
		l2cap_send_disconn_req(chan, ECONNRESET);
		वापस;
	पूर्ण

	clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

	l2cap_pass_to_tx(chan, control);

	अगर (control->final) अणु
		अगर (!test_and_clear_bit(CONN_REJ_ACT, &chan->conn_state))
			l2cap_retransmit_all(chan, control);
	पूर्ण अन्यथा अणु
		l2cap_retransmit_all(chan, control);
		l2cap_erपंचांग_send(chan);
		अगर (chan->tx_state == L2CAP_TX_STATE_WAIT_F)
			set_bit(CONN_REJ_ACT, &chan->conn_state);
	पूर्ण
पूर्ण

अटल u8 l2cap_classअगरy_txseq(काष्ठा l2cap_chan *chan, u16 txseq)
अणु
	BT_DBG("chan %p, txseq %d", chan, txseq);

	BT_DBG("last_acked_seq %d, expected_tx_seq %d", chan->last_acked_seq,
	       chan->expected_tx_seq);

	अगर (chan->rx_state == L2CAP_RX_STATE_SREJ_SENT) अणु
		अगर (__seq_offset(chan, txseq, chan->last_acked_seq) >=
		    chan->tx_win) अणु
			/* See notes below regarding "double poll" and
			 * invalid packets.
			 */
			अगर (chan->tx_win <= ((chan->tx_win_max + 1) >> 1)) अणु
				BT_DBG("Invalid/Ignore - after SREJ");
				वापस L2CAP_TXSEQ_INVALID_IGNORE;
			पूर्ण अन्यथा अणु
				BT_DBG("Invalid - in window after SREJ sent");
				वापस L2CAP_TXSEQ_INVALID;
			पूर्ण
		पूर्ण

		अगर (chan->srej_list.head == txseq) अणु
			BT_DBG("Expected SREJ");
			वापस L2CAP_TXSEQ_EXPECTED_SREJ;
		पूर्ण

		अगर (l2cap_erपंचांग_seq_in_queue(&chan->srej_q, txseq)) अणु
			BT_DBG("Duplicate SREJ - txseq already stored");
			वापस L2CAP_TXSEQ_DUPLICATE_SREJ;
		पूर्ण

		अगर (l2cap_seq_list_contains(&chan->srej_list, txseq)) अणु
			BT_DBG("Unexpected SREJ - not requested");
			वापस L2CAP_TXSEQ_UNEXPECTED_SREJ;
		पूर्ण
	पूर्ण

	अगर (chan->expected_tx_seq == txseq) अणु
		अगर (__seq_offset(chan, txseq, chan->last_acked_seq) >=
		    chan->tx_win) अणु
			BT_DBG("Invalid - txseq outside tx window");
			वापस L2CAP_TXSEQ_INVALID;
		पूर्ण अन्यथा अणु
			BT_DBG("Expected");
			वापस L2CAP_TXSEQ_EXPECTED;
		पूर्ण
	पूर्ण

	अगर (__seq_offset(chan, txseq, chan->last_acked_seq) <
	    __seq_offset(chan, chan->expected_tx_seq, chan->last_acked_seq)) अणु
		BT_DBG("Duplicate - expected_tx_seq later than txseq");
		वापस L2CAP_TXSEQ_DUPLICATE;
	पूर्ण

	अगर (__seq_offset(chan, txseq, chan->last_acked_seq) >= chan->tx_win) अणु
		/* A source of invalid packets is a "double poll" condition,
		 * where delays cause us to send multiple poll packets.  If
		 * the remote stack receives and processes both polls,
		 * sequence numbers can wrap around in such a way that a
		 * resent frame has a sequence number that looks like new data
		 * with a sequence gap.  This would trigger an erroneous SREJ
		 * request.
		 *
		 * Fortunately, this is impossible with a tx winकरोw that's
		 * less than half of the maximum sequence number, which allows
		 * invalid frames to be safely ignored.
		 *
		 * With tx winकरोw sizes greater than half of the tx winकरोw
		 * maximum, the frame is invalid and cannot be ignored.  This
		 * causes a disconnect.
		 */

		अगर (chan->tx_win <= ((chan->tx_win_max + 1) >> 1)) अणु
			BT_DBG("Invalid/Ignore - txseq outside tx window");
			वापस L2CAP_TXSEQ_INVALID_IGNORE;
		पूर्ण अन्यथा अणु
			BT_DBG("Invalid - txseq outside tx window");
			वापस L2CAP_TXSEQ_INVALID;
		पूर्ण
	पूर्ण अन्यथा अणु
		BT_DBG("Unexpected - txseq indicates missing frames");
		वापस L2CAP_TXSEQ_UNEXPECTED;
	पूर्ण
पूर्ण

अटल पूर्णांक l2cap_rx_state_recv(काष्ठा l2cap_chan *chan,
			       काष्ठा l2cap_ctrl *control,
			       काष्ठा sk_buff *skb, u8 event)
अणु
	पूर्णांक err = 0;
	bool skb_in_use = false;

	BT_DBG("chan %p, control %p, skb %p, event %d", chan, control, skb,
	       event);

	चयन (event) अणु
	हाल L2CAP_EV_RECV_IFRAME:
		चयन (l2cap_classअगरy_txseq(chan, control->txseq)) अणु
		हाल L2CAP_TXSEQ_EXPECTED:
			l2cap_pass_to_tx(chan, control);

			अगर (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) अणु
				BT_DBG("Busy, discarding expected seq %d",
				       control->txseq);
				अवरोध;
			पूर्ण

			chan->expected_tx_seq = __next_seq(chan,
							   control->txseq);

			chan->buffer_seq = chan->expected_tx_seq;
			skb_in_use = true;

			err = l2cap_reassemble_sdu(chan, skb, control);
			अगर (err)
				अवरोध;

			अगर (control->final) अणु
				अगर (!test_and_clear_bit(CONN_REJ_ACT,
							&chan->conn_state)) अणु
					control->final = 0;
					l2cap_retransmit_all(chan, control);
					l2cap_erपंचांग_send(chan);
				पूर्ण
			पूर्ण

			अगर (!test_bit(CONN_LOCAL_BUSY, &chan->conn_state))
				l2cap_send_ack(chan);
			अवरोध;
		हाल L2CAP_TXSEQ_UNEXPECTED:
			l2cap_pass_to_tx(chan, control);

			/* Can't issue SREJ frames in the local busy state.
			 * Drop this frame, it will be seen as missing
			 * when local busy is निकासed.
			 */
			अगर (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) अणु
				BT_DBG("Busy, discarding unexpected seq %d",
				       control->txseq);
				अवरोध;
			पूर्ण

			/* There was a gap in the sequence, so an SREJ
			 * must be sent क्रम each missing frame.  The
			 * current frame is stored क्रम later use.
			 */
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			clear_bit(CONN_SREJ_ACT, &chan->conn_state);
			l2cap_seq_list_clear(&chan->srej_list);
			l2cap_send_srej(chan, control->txseq);

			chan->rx_state = L2CAP_RX_STATE_SREJ_SENT;
			अवरोध;
		हाल L2CAP_TXSEQ_DUPLICATE:
			l2cap_pass_to_tx(chan, control);
			अवरोध;
		हाल L2CAP_TXSEQ_INVALID_IGNORE:
			अवरोध;
		हाल L2CAP_TXSEQ_INVALID:
		शेष:
			l2cap_send_disconn_req(chan, ECONNRESET);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल L2CAP_EV_RECV_RR:
		l2cap_pass_to_tx(chan, control);
		अगर (control->final) अणु
			clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

			अगर (!test_and_clear_bit(CONN_REJ_ACT, &chan->conn_state) &&
			    !__chan_is_moving(chan)) अणु
				control->final = 0;
				l2cap_retransmit_all(chan, control);
			पूर्ण

			l2cap_erपंचांग_send(chan);
		पूर्ण अन्यथा अगर (control->poll) अणु
			l2cap_send_i_or_rr_or_rnr(chan);
		पूर्ण अन्यथा अणु
			अगर (test_and_clear_bit(CONN_REMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_frames)
				__set_retrans_समयr(chan);

			l2cap_erपंचांग_send(chan);
		पूर्ण
		अवरोध;
	हाल L2CAP_EV_RECV_RNR:
		set_bit(CONN_REMOTE_BUSY, &chan->conn_state);
		l2cap_pass_to_tx(chan, control);
		अगर (control && control->poll) अणु
			set_bit(CONN_SEND_FBIT, &chan->conn_state);
			l2cap_send_rr_or_rnr(chan, 0);
		पूर्ण
		__clear_retrans_समयr(chan);
		l2cap_seq_list_clear(&chan->retrans_list);
		अवरोध;
	हाल L2CAP_EV_RECV_REJ:
		l2cap_handle_rej(chan, control);
		अवरोध;
	हाल L2CAP_EV_RECV_SREJ:
		l2cap_handle_srej(chan, control);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (skb && !skb_in_use) अणु
		BT_DBG("Freeing %p", skb);
		kमुक्त_skb(skb);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_rx_state_srej_sent(काष्ठा l2cap_chan *chan,
				    काष्ठा l2cap_ctrl *control,
				    काष्ठा sk_buff *skb, u8 event)
अणु
	पूर्णांक err = 0;
	u16 txseq = control->txseq;
	bool skb_in_use = false;

	BT_DBG("chan %p, control %p, skb %p, event %d", chan, control, skb,
	       event);

	चयन (event) अणु
	हाल L2CAP_EV_RECV_IFRAME:
		चयन (l2cap_classअगरy_txseq(chan, txseq)) अणु
		हाल L2CAP_TXSEQ_EXPECTED:
			/* Keep frame क्रम reassembly later */
			l2cap_pass_to_tx(chan, control);
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			chan->expected_tx_seq = __next_seq(chan, txseq);
			अवरोध;
		हाल L2CAP_TXSEQ_EXPECTED_SREJ:
			l2cap_seq_list_pop(&chan->srej_list);

			l2cap_pass_to_tx(chan, control);
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			err = l2cap_rx_queued_अगरrames(chan);
			अगर (err)
				अवरोध;

			अवरोध;
		हाल L2CAP_TXSEQ_UNEXPECTED:
			/* Got a frame that can't be reassembled yet.
			 * Save it क्रम later, and send SREJs to cover
			 * the missing frames.
			 */
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			l2cap_pass_to_tx(chan, control);
			l2cap_send_srej(chan, control->txseq);
			अवरोध;
		हाल L2CAP_TXSEQ_UNEXPECTED_SREJ:
			/* This frame was requested with an SREJ, but
			 * some expected retransmitted frames are
			 * missing.  Request retransmission of missing
			 * SREJ'd frames.
			 */
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			l2cap_pass_to_tx(chan, control);
			l2cap_send_srej_list(chan, control->txseq);
			अवरोध;
		हाल L2CAP_TXSEQ_DUPLICATE_SREJ:
			/* We've alपढ़ोy queued this frame.  Drop this copy. */
			l2cap_pass_to_tx(chan, control);
			अवरोध;
		हाल L2CAP_TXSEQ_DUPLICATE:
			/* Expecting a later sequence number, so this frame
			 * was alपढ़ोy received.  Ignore it completely.
			 */
			अवरोध;
		हाल L2CAP_TXSEQ_INVALID_IGNORE:
			अवरोध;
		हाल L2CAP_TXSEQ_INVALID:
		शेष:
			l2cap_send_disconn_req(chan, ECONNRESET);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल L2CAP_EV_RECV_RR:
		l2cap_pass_to_tx(chan, control);
		अगर (control->final) अणु
			clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

			अगर (!test_and_clear_bit(CONN_REJ_ACT,
						&chan->conn_state)) अणु
				control->final = 0;
				l2cap_retransmit_all(chan, control);
			पूर्ण

			l2cap_erपंचांग_send(chan);
		पूर्ण अन्यथा अगर (control->poll) अणु
			अगर (test_and_clear_bit(CONN_REMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_frames) अणु
				__set_retrans_समयr(chan);
			पूर्ण

			set_bit(CONN_SEND_FBIT, &chan->conn_state);
			l2cap_send_srej_tail(chan);
		पूर्ण अन्यथा अणु
			अगर (test_and_clear_bit(CONN_REMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_frames)
				__set_retrans_समयr(chan);

			l2cap_send_ack(chan);
		पूर्ण
		अवरोध;
	हाल L2CAP_EV_RECV_RNR:
		set_bit(CONN_REMOTE_BUSY, &chan->conn_state);
		l2cap_pass_to_tx(chan, control);
		अगर (control->poll) अणु
			l2cap_send_srej_tail(chan);
		पूर्ण अन्यथा अणु
			काष्ठा l2cap_ctrl rr_control;
			स_रखो(&rr_control, 0, माप(rr_control));
			rr_control.sframe = 1;
			rr_control.super = L2CAP_SUPER_RR;
			rr_control.reqseq = chan->buffer_seq;
			l2cap_send_sframe(chan, &rr_control);
		पूर्ण

		अवरोध;
	हाल L2CAP_EV_RECV_REJ:
		l2cap_handle_rej(chan, control);
		अवरोध;
	हाल L2CAP_EV_RECV_SREJ:
		l2cap_handle_srej(chan, control);
		अवरोध;
	पूर्ण

	अगर (skb && !skb_in_use) अणु
		BT_DBG("Freeing %p", skb);
		kमुक्त_skb(skb);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_finish_move(काष्ठा l2cap_chan *chan)
अणु
	BT_DBG("chan %p", chan);

	chan->rx_state = L2CAP_RX_STATE_RECV;

	अगर (chan->hs_hcon)
		chan->conn->mtu = chan->hs_hcon->hdev->block_mtu;
	अन्यथा
		chan->conn->mtu = chan->conn->hcon->hdev->acl_mtu;

	वापस l2cap_resegment(chan);
पूर्ण

अटल पूर्णांक l2cap_rx_state_रुको_p(काष्ठा l2cap_chan *chan,
				 काष्ठा l2cap_ctrl *control,
				 काष्ठा sk_buff *skb, u8 event)
अणु
	पूर्णांक err;

	BT_DBG("chan %p, control %p, skb %p, event %d", chan, control, skb,
	       event);

	अगर (!control->poll)
		वापस -EPROTO;

	l2cap_process_reqseq(chan, control->reqseq);

	अगर (!skb_queue_empty(&chan->tx_q))
		chan->tx_send_head = skb_peek(&chan->tx_q);
	अन्यथा
		chan->tx_send_head = शून्य;

	/* Rewind next_tx_seq to the poपूर्णांक expected
	 * by the receiver.
	 */
	chan->next_tx_seq = control->reqseq;
	chan->unacked_frames = 0;

	err = l2cap_finish_move(chan);
	अगर (err)
		वापस err;

	set_bit(CONN_SEND_FBIT, &chan->conn_state);
	l2cap_send_i_or_rr_or_rnr(chan);

	अगर (event == L2CAP_EV_RECV_IFRAME)
		वापस -EPROTO;

	वापस l2cap_rx_state_recv(chan, control, शून्य, event);
पूर्ण

अटल पूर्णांक l2cap_rx_state_रुको_f(काष्ठा l2cap_chan *chan,
				 काष्ठा l2cap_ctrl *control,
				 काष्ठा sk_buff *skb, u8 event)
अणु
	पूर्णांक err;

	अगर (!control->final)
		वापस -EPROTO;

	clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

	chan->rx_state = L2CAP_RX_STATE_RECV;
	l2cap_process_reqseq(chan, control->reqseq);

	अगर (!skb_queue_empty(&chan->tx_q))
		chan->tx_send_head = skb_peek(&chan->tx_q);
	अन्यथा
		chan->tx_send_head = शून्य;

	/* Rewind next_tx_seq to the poपूर्णांक expected
	 * by the receiver.
	 */
	chan->next_tx_seq = control->reqseq;
	chan->unacked_frames = 0;

	अगर (chan->hs_hcon)
		chan->conn->mtu = chan->hs_hcon->hdev->block_mtu;
	अन्यथा
		chan->conn->mtu = chan->conn->hcon->hdev->acl_mtu;

	err = l2cap_resegment(chan);

	अगर (!err)
		err = l2cap_rx_state_recv(chan, control, skb, event);

	वापस err;
पूर्ण

अटल bool __valid_reqseq(काष्ठा l2cap_chan *chan, u16 reqseq)
अणु
	/* Make sure reqseq is क्रम a packet that has been sent but not acked */
	u16 unacked;

	unacked = __seq_offset(chan, chan->next_tx_seq, chan->expected_ack_seq);
	वापस __seq_offset(chan, chan->next_tx_seq, reqseq) <= unacked;
पूर्ण

अटल पूर्णांक l2cap_rx(काष्ठा l2cap_chan *chan, काष्ठा l2cap_ctrl *control,
		    काष्ठा sk_buff *skb, u8 event)
अणु
	पूर्णांक err = 0;

	BT_DBG("chan %p, control %p, skb %p, event %d, state %d", chan,
	       control, skb, event, chan->rx_state);

	अगर (__valid_reqseq(chan, control->reqseq)) अणु
		चयन (chan->rx_state) अणु
		हाल L2CAP_RX_STATE_RECV:
			err = l2cap_rx_state_recv(chan, control, skb, event);
			अवरोध;
		हाल L2CAP_RX_STATE_SREJ_SENT:
			err = l2cap_rx_state_srej_sent(chan, control, skb,
						       event);
			अवरोध;
		हाल L2CAP_RX_STATE_WAIT_P:
			err = l2cap_rx_state_रुको_p(chan, control, skb, event);
			अवरोध;
		हाल L2CAP_RX_STATE_WAIT_F:
			err = l2cap_rx_state_रुको_f(chan, control, skb, event);
			अवरोध;
		शेष:
			/* shut it करोwn */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		BT_DBG("Invalid reqseq %d (next_tx_seq %d, expected_ack_seq %d",
		       control->reqseq, chan->next_tx_seq,
		       chan->expected_ack_seq);
		l2cap_send_disconn_req(chan, ECONNRESET);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_stream_rx(काष्ठा l2cap_chan *chan, काष्ठा l2cap_ctrl *control,
			   काष्ठा sk_buff *skb)
अणु
	BT_DBG("chan %p, control %p, skb %p, state %d", chan, control, skb,
	       chan->rx_state);

	अगर (l2cap_classअगरy_txseq(chan, control->txseq) ==
	    L2CAP_TXSEQ_EXPECTED) अणु
		l2cap_pass_to_tx(chan, control);

		BT_DBG("buffer_seq %u->%u", chan->buffer_seq,
		       __next_seq(chan, chan->buffer_seq));

		chan->buffer_seq = __next_seq(chan, chan->buffer_seq);

		l2cap_reassemble_sdu(chan, skb, control);
	पूर्ण अन्यथा अणु
		अगर (chan->sdu) अणु
			kमुक्त_skb(chan->sdu);
			chan->sdu = शून्य;
		पूर्ण
		chan->sdu_last_frag = शून्य;
		chan->sdu_len = 0;

		अगर (skb) अणु
			BT_DBG("Freeing %p", skb);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	chan->last_acked_seq = control->txseq;
	chan->expected_tx_seq = __next_seq(chan, control->txseq);

	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_data_rcv(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2cap_ctrl *control = &bt_cb(skb)->l2cap;
	u16 len;
	u8 event;

	__unpack_control(chan, skb);

	len = skb->len;

	/*
	 * We can just drop the corrupted I-frame here.
	 * Receiver will miss it and start proper recovery
	 * procedures and ask क्रम retransmission.
	 */
	अगर (l2cap_check_fcs(chan, skb))
		जाओ drop;

	अगर (!control->sframe && control->sar == L2CAP_SAR_START)
		len -= L2CAP_SDULEN_SIZE;

	अगर (chan->fcs == L2CAP_FCS_CRC16)
		len -= L2CAP_FCS_SIZE;

	अगर (len > chan->mps) अणु
		l2cap_send_disconn_req(chan, ECONNRESET);
		जाओ drop;
	पूर्ण

	अगर (chan->ops->filter) अणु
		अगर (chan->ops->filter(chan, skb))
			जाओ drop;
	पूर्ण

	अगर (!control->sframe) अणु
		पूर्णांक err;

		BT_DBG("iframe sar %d, reqseq %d, final %d, txseq %d",
		       control->sar, control->reqseq, control->final,
		       control->txseq);

		/* Validate F-bit - F=0 always valid, F=1 only
		 * valid in TX WAIT_F
		 */
		अगर (control->final && chan->tx_state != L2CAP_TX_STATE_WAIT_F)
			जाओ drop;

		अगर (chan->mode != L2CAP_MODE_STREAMING) अणु
			event = L2CAP_EV_RECV_IFRAME;
			err = l2cap_rx(chan, control, skb, event);
		पूर्ण अन्यथा अणु
			err = l2cap_stream_rx(chan, control, skb);
		पूर्ण

		अगर (err)
			l2cap_send_disconn_req(chan, ECONNRESET);
	पूर्ण अन्यथा अणु
		स्थिर u8 rx_func_to_event[4] = अणु
			L2CAP_EV_RECV_RR, L2CAP_EV_RECV_REJ,
			L2CAP_EV_RECV_RNR, L2CAP_EV_RECV_SREJ
		पूर्ण;

		/* Only I-frames are expected in streaming mode */
		अगर (chan->mode == L2CAP_MODE_STREAMING)
			जाओ drop;

		BT_DBG("sframe reqseq %d, final %d, poll %d, super %d",
		       control->reqseq, control->final, control->poll,
		       control->super);

		अगर (len != 0) अणु
			BT_ERR("Trailing bytes: %d in sframe", len);
			l2cap_send_disconn_req(chan, ECONNRESET);
			जाओ drop;
		पूर्ण

		/* Validate F and P bits */
		अगर (control->final && (control->poll ||
				       chan->tx_state != L2CAP_TX_STATE_WAIT_F))
			जाओ drop;

		event = rx_func_to_event[control->super];
		अगर (l2cap_rx(chan, control, skb, event))
			l2cap_send_disconn_req(chan, ECONNRESET);
	पूर्ण

	वापस 0;

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम l2cap_chan_le_send_credits(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा l2cap_le_credits pkt;
	u16 वापस_credits;

	वापस_credits = (chan->imtu / chan->mps) + 1;

	अगर (chan->rx_credits >= वापस_credits)
		वापस;

	वापस_credits -= chan->rx_credits;

	BT_DBG("chan %p returning %u credits to sender", chan, वापस_credits);

	chan->rx_credits += वापस_credits;

	pkt.cid     = cpu_to_le16(chan->scid);
	pkt.credits = cpu_to_le16(वापस_credits);

	chan->ident = l2cap_get_ident(conn);

	l2cap_send_cmd(conn, chan->ident, L2CAP_LE_CREDITS, माप(pkt), &pkt);
पूर्ण

अटल पूर्णांक l2cap_ecred_recv(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	BT_DBG("SDU reassemble complete: chan %p skb->len %u", chan, skb->len);

	/* Wait recv to confirm reception beक्रमe updating the credits */
	err = chan->ops->recv(chan, skb);

	/* Update credits whenever an SDU is received */
	l2cap_chan_le_send_credits(chan);

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_ecred_data_rcv(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	अगर (!chan->rx_credits) अणु
		BT_ERR("No credits to receive LE L2CAP data");
		l2cap_send_disconn_req(chan, ECONNRESET);
		वापस -ENOBUFS;
	पूर्ण

	अगर (chan->imtu < skb->len) अणु
		BT_ERR("Too big LE L2CAP PDU");
		वापस -ENOBUFS;
	पूर्ण

	chan->rx_credits--;
	BT_DBG("rx_credits %u -> %u", chan->rx_credits + 1, chan->rx_credits);

	/* Update अगर remote had run out of credits, this should only happens
	 * अगर the remote is not using the entire MPS.
	 */
	अगर (!chan->rx_credits)
		l2cap_chan_le_send_credits(chan);

	err = 0;

	अगर (!chan->sdu) अणु
		u16 sdu_len;

		sdu_len = get_unaligned_le16(skb->data);
		skb_pull(skb, L2CAP_SDULEN_SIZE);

		BT_DBG("Start of new SDU. sdu_len %u skb->len %u imtu %u",
		       sdu_len, skb->len, chan->imtu);

		अगर (sdu_len > chan->imtu) अणु
			BT_ERR("Too big LE L2CAP SDU length received");
			err = -EMSGSIZE;
			जाओ failed;
		पूर्ण

		अगर (skb->len > sdu_len) अणु
			BT_ERR("Too much LE L2CAP data received");
			err = -EINVAL;
			जाओ failed;
		पूर्ण

		अगर (skb->len == sdu_len)
			वापस l2cap_ecred_recv(chan, skb);

		chan->sdu = skb;
		chan->sdu_len = sdu_len;
		chan->sdu_last_frag = skb;

		/* Detect अगर remote is not able to use the selected MPS */
		अगर (skb->len + L2CAP_SDULEN_SIZE < chan->mps) अणु
			u16 mps_len = skb->len + L2CAP_SDULEN_SIZE;

			/* Adjust the number of credits */
			BT_DBG("chan->mps %u -> %u", chan->mps, mps_len);
			chan->mps = mps_len;
			l2cap_chan_le_send_credits(chan);
		पूर्ण

		वापस 0;
	पूर्ण

	BT_DBG("SDU fragment. chan->sdu->len %u skb->len %u chan->sdu_len %u",
	       chan->sdu->len, skb->len, chan->sdu_len);

	अगर (chan->sdu->len + skb->len > chan->sdu_len) अणु
		BT_ERR("Too much LE L2CAP data received");
		err = -EINVAL;
		जाओ failed;
	पूर्ण

	append_skb_frag(chan->sdu, skb, &chan->sdu_last_frag);
	skb = शून्य;

	अगर (chan->sdu->len == chan->sdu_len) अणु
		err = l2cap_ecred_recv(chan, chan->sdu);
		अगर (!err) अणु
			chan->sdu = शून्य;
			chan->sdu_last_frag = शून्य;
			chan->sdu_len = 0;
		पूर्ण
	पूर्ण

failed:
	अगर (err) अणु
		kमुक्त_skb(skb);
		kमुक्त_skb(chan->sdu);
		chan->sdu = शून्य;
		chan->sdu_last_frag = शून्य;
		chan->sdu_len = 0;
	पूर्ण

	/* We can't वापस an error here since we took care of the skb
	 * मुक्तing पूर्णांकernally. An error वापस would cause the caller to
	 * करो a द्विगुन-मुक्त of the skb.
	 */
	वापस 0;
पूर्ण

अटल व्योम l2cap_data_channel(काष्ठा l2cap_conn *conn, u16 cid,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा l2cap_chan *chan;

	chan = l2cap_get_chan_by_scid(conn, cid);
	अगर (!chan) अणु
		अगर (cid == L2CAP_CID_A2MP) अणु
			chan = a2mp_channel_create(conn, skb);
			अगर (!chan) अणु
				kमुक्त_skb(skb);
				वापस;
			पूर्ण

			l2cap_chan_lock(chan);
		पूर्ण अन्यथा अणु
			BT_DBG("unknown cid 0x%4.4x", cid);
			/* Drop packet and वापस */
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण

	BT_DBG("chan %p, len %d", chan, skb->len);

	/* If we receive data on a fixed channel beक्रमe the info req/rsp
	 * procedure is करोne simply assume that the channel is supported
	 * and mark it as पढ़ोy.
	 */
	अगर (chan->chan_type == L2CAP_CHAN_FIXED)
		l2cap_chan_पढ़ोy(chan);

	अगर (chan->state != BT_CONNECTED)
		जाओ drop;

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_LE_FLOWCTL:
	हाल L2CAP_MODE_EXT_FLOWCTL:
		अगर (l2cap_ecred_data_rcv(chan, skb) < 0)
			जाओ drop;

		जाओ करोne;

	हाल L2CAP_MODE_BASIC:
		/* If socket recv buffers overflows we drop data here
		 * which is *bad* because L2CAP has to be reliable.
		 * But we करोn't have any other choice. L2CAP doesn't
		 * provide flow control mechanism. */

		अगर (chan->imtu < skb->len) अणु
			BT_ERR("Dropping L2CAP data: receive buffer overflow");
			जाओ drop;
		पूर्ण

		अगर (!chan->ops->recv(chan, skb))
			जाओ करोne;
		अवरोध;

	हाल L2CAP_MODE_ERTM:
	हाल L2CAP_MODE_STREAMING:
		l2cap_data_rcv(chan, skb);
		जाओ करोne;

	शेष:
		BT_DBG("chan %p: bad mode 0x%2.2x", chan, chan->mode);
		अवरोध;
	पूर्ण

drop:
	kमुक्त_skb(skb);

करोne:
	l2cap_chan_unlock(chan);
पूर्ण

अटल व्योम l2cap_conless_channel(काष्ठा l2cap_conn *conn, __le16 psm,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_conn *hcon = conn->hcon;
	काष्ठा l2cap_chan *chan;

	अगर (hcon->type != ACL_LINK)
		जाओ मुक्त_skb;

	chan = l2cap_global_chan_by_psm(0, psm, &hcon->src, &hcon->dst,
					ACL_LINK);
	अगर (!chan)
		जाओ मुक्त_skb;

	BT_DBG("chan %p, len %d", chan, skb->len);

	अगर (chan->state != BT_BOUND && chan->state != BT_CONNECTED)
		जाओ drop;

	अगर (chan->imtu < skb->len)
		जाओ drop;

	/* Store remote BD_ADDR and PSM क्रम msg_name */
	bacpy(&bt_cb(skb)->l2cap.bdaddr, &hcon->dst);
	bt_cb(skb)->l2cap.psm = psm;

	अगर (!chan->ops->recv(chan, skb)) अणु
		l2cap_chan_put(chan);
		वापस;
	पूर्ण

drop:
	l2cap_chan_put(chan);
मुक्त_skb:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम l2cap_recv_frame(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2cap_hdr *lh = (व्योम *) skb->data;
	काष्ठा hci_conn *hcon = conn->hcon;
	u16 cid, len;
	__le16 psm;

	अगर (hcon->state != BT_CONNECTED) अणु
		BT_DBG("queueing pending rx skb");
		skb_queue_tail(&conn->pending_rx, skb);
		वापस;
	पूर्ण

	skb_pull(skb, L2CAP_HDR_SIZE);
	cid = __le16_to_cpu(lh->cid);
	len = __le16_to_cpu(lh->len);

	अगर (len != skb->len) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* Since we can't actively block incoming LE connections we must
	 * at least ensure that we ignore incoming data from them.
	 */
	अगर (hcon->type == LE_LINK &&
	    hci_bdaddr_list_lookup(&hcon->hdev->blacklist, &hcon->dst,
				   bdaddr_dst_type(hcon))) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	BT_DBG("len %d, cid 0x%4.4x", len, cid);

	चयन (cid) अणु
	हाल L2CAP_CID_SIGNALING:
		l2cap_sig_channel(conn, skb);
		अवरोध;

	हाल L2CAP_CID_CONN_LESS:
		psm = get_unaligned((__le16 *) skb->data);
		skb_pull(skb, L2CAP_PSMLEN_SIZE);
		l2cap_conless_channel(conn, psm, skb);
		अवरोध;

	हाल L2CAP_CID_LE_SIGNALING:
		l2cap_le_sig_channel(conn, skb);
		अवरोध;

	शेष:
		l2cap_data_channel(conn, cid, skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम process_pending_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2cap_conn *conn = container_of(work, काष्ठा l2cap_conn,
					       pending_rx_work);
	काष्ठा sk_buff *skb;

	BT_DBG("");

	जबतक ((skb = skb_dequeue(&conn->pending_rx)))
		l2cap_recv_frame(conn, skb);
पूर्ण

अटल काष्ठा l2cap_conn *l2cap_conn_add(काष्ठा hci_conn *hcon)
अणु
	काष्ठा l2cap_conn *conn = hcon->l2cap_data;
	काष्ठा hci_chan *hchan;

	अगर (conn)
		वापस conn;

	hchan = hci_chan_create(hcon);
	अगर (!hchan)
		वापस शून्य;

	conn = kzalloc(माप(*conn), GFP_KERNEL);
	अगर (!conn) अणु
		hci_chan_del(hchan);
		वापस शून्य;
	पूर्ण

	kref_init(&conn->ref);
	hcon->l2cap_data = conn;
	conn->hcon = hci_conn_get(hcon);
	conn->hchan = hchan;

	BT_DBG("hcon %p conn %p hchan %p", hcon, conn, hchan);

	चयन (hcon->type) अणु
	हाल LE_LINK:
		अगर (hcon->hdev->le_mtu) अणु
			conn->mtu = hcon->hdev->le_mtu;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		conn->mtu = hcon->hdev->acl_mtu;
		अवरोध;
	पूर्ण

	conn->feat_mask = 0;

	conn->local_fixed_chan = L2CAP_FC_SIG_BREDR | L2CAP_FC_CONNLESS;

	अगर (hcon->type == ACL_LINK &&
	    hci_dev_test_flag(hcon->hdev, HCI_HS_ENABLED))
		conn->local_fixed_chan |= L2CAP_FC_A2MP;

	अगर (hci_dev_test_flag(hcon->hdev, HCI_LE_ENABLED) &&
	    (bredr_sc_enabled(hcon->hdev) ||
	     hci_dev_test_flag(hcon->hdev, HCI_FORCE_BREDR_SMP)))
		conn->local_fixed_chan |= L2CAP_FC_SMP_BREDR;

	mutex_init(&conn->ident_lock);
	mutex_init(&conn->chan_lock);

	INIT_LIST_HEAD(&conn->chan_l);
	INIT_LIST_HEAD(&conn->users);

	INIT_DELAYED_WORK(&conn->info_समयr, l2cap_info_समयout);

	skb_queue_head_init(&conn->pending_rx);
	INIT_WORK(&conn->pending_rx_work, process_pending_rx);
	INIT_WORK(&conn->id_addr_update_work, l2cap_conn_update_id_addr);

	conn->disc_reason = HCI_ERROR_REMOTE_USER_TERM;

	वापस conn;
पूर्ण

अटल bool is_valid_psm(u16 psm, u8 dst_type)
अणु
	अगर (!psm)
		वापस false;

	अगर (bdaddr_type_is_le(dst_type))
		वापस (psm <= 0x00ff);

	/* PSM must be odd and lsb of upper byte must be 0 */
	वापस ((psm & 0x0101) == 0x0001);
पूर्ण

काष्ठा l2cap_chan_data अणु
	काष्ठा l2cap_chan *chan;
	काष्ठा pid *pid;
	पूर्णांक count;
पूर्ण;

अटल व्योम l2cap_chan_by_pid(काष्ठा l2cap_chan *chan, व्योम *data)
अणु
	काष्ठा l2cap_chan_data *d = data;
	काष्ठा pid *pid;

	अगर (chan == d->chan)
		वापस;

	अगर (!test_bit(FLAG_DEFER_SETUP, &chan->flags))
		वापस;

	pid = chan->ops->get_peer_pid(chan);

	/* Only count deferred channels with the same PID/PSM */
	अगर (d->pid != pid || chan->psm != d->chan->psm || chan->ident ||
	    chan->mode != L2CAP_MODE_EXT_FLOWCTL || chan->state != BT_CONNECT)
		वापस;

	d->count++;
पूर्ण

पूर्णांक l2cap_chan_connect(काष्ठा l2cap_chan *chan, __le16 psm, u16 cid,
		       bdaddr_t *dst, u8 dst_type)
अणु
	काष्ठा l2cap_conn *conn;
	काष्ठा hci_conn *hcon;
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	BT_DBG("%pMR -> %pMR (type %u) psm 0x%4.4x mode 0x%2.2x", &chan->src,
	       dst, dst_type, __le16_to_cpu(psm), chan->mode);

	hdev = hci_get_route(dst, &chan->src, chan->src_type);
	अगर (!hdev)
		वापस -EHOSTUNREACH;

	hci_dev_lock(hdev);

	अगर (!is_valid_psm(__le16_to_cpu(psm), dst_type) && !cid &&
	    chan->chan_type != L2CAP_CHAN_RAW) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (chan->chan_type == L2CAP_CHAN_CONN_ORIENTED && !psm) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (chan->chan_type == L2CAP_CHAN_FIXED && !cid) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_BASIC:
		अवरोध;
	हाल L2CAP_MODE_LE_FLOWCTL:
		अवरोध;
	हाल L2CAP_MODE_EXT_FLOWCTL:
		अगर (!enable_ecred) अणु
			err = -EOPNOTSUPP;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल L2CAP_MODE_ERTM:
	हाल L2CAP_MODE_STREAMING:
		अगर (!disable_erपंचांग)
			अवरोध;
		fallthrough;
	शेष:
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	चयन (chan->state) अणु
	हाल BT_CONNECT:
	हाल BT_CONNECT2:
	हाल BT_CONFIG:
		/* Alपढ़ोy connecting */
		err = 0;
		जाओ करोne;

	हाल BT_CONNECTED:
		/* Alपढ़ोy connected */
		err = -EISCONN;
		जाओ करोne;

	हाल BT_OPEN:
	हाल BT_BOUND:
		/* Can connect */
		अवरोध;

	शेष:
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	/* Set destination address and psm */
	bacpy(&chan->dst, dst);
	chan->dst_type = dst_type;

	chan->psm = psm;
	chan->dcid = cid;

	अगर (bdaddr_type_is_le(dst_type)) अणु
		/* Convert from L2CAP channel address type to HCI address type
		 */
		अगर (dst_type == BDADDR_LE_PUBLIC)
			dst_type = ADDR_LE_DEV_PUBLIC;
		अन्यथा
			dst_type = ADDR_LE_DEV_RANDOM;

		अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING))
			hcon = hci_connect_le(hdev, dst, dst_type,
					      chan->sec_level,
					      HCI_LE_CONN_TIMEOUT,
					      HCI_ROLE_SLAVE, शून्य);
		अन्यथा
			hcon = hci_connect_le_scan(hdev, dst, dst_type,
						   chan->sec_level,
						   HCI_LE_CONN_TIMEOUT,
						   CONN_REASON_L2CAP_CHAN);

	पूर्ण अन्यथा अणु
		u8 auth_type = l2cap_get_auth_type(chan);
		hcon = hci_connect_acl(hdev, dst, chan->sec_level, auth_type,
				       CONN_REASON_L2CAP_CHAN);
	पूर्ण

	अगर (IS_ERR(hcon)) अणु
		err = PTR_ERR(hcon);
		जाओ करोne;
	पूर्ण

	conn = l2cap_conn_add(hcon);
	अगर (!conn) अणु
		hci_conn_drop(hcon);
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	अगर (chan->mode == L2CAP_MODE_EXT_FLOWCTL) अणु
		काष्ठा l2cap_chan_data data;

		data.chan = chan;
		data.pid = chan->ops->get_peer_pid(chan);
		data.count = 1;

		l2cap_chan_list(conn, l2cap_chan_by_pid, &data);

		/* Check अगर there isn't too many channels being connected */
		अगर (data.count > L2CAP_ECRED_CONN_SCID_MAX) अणु
			hci_conn_drop(hcon);
			err = -EPROTO;
			जाओ करोne;
		पूर्ण
	पूर्ण

	mutex_lock(&conn->chan_lock);
	l2cap_chan_lock(chan);

	अगर (cid && __l2cap_get_chan_by_dcid(conn, cid)) अणु
		hci_conn_drop(hcon);
		err = -EBUSY;
		जाओ chan_unlock;
	पूर्ण

	/* Update source addr of the socket */
	bacpy(&chan->src, &hcon->src);
	chan->src_type = bdaddr_src_type(hcon);

	__l2cap_chan_add(conn, chan);

	/* l2cap_chan_add takes its own ref so we can drop this one */
	hci_conn_drop(hcon);

	l2cap_state_change(chan, BT_CONNECT);
	__set_chan_समयr(chan, chan->ops->get_sndसमयo(chan));

	/* Release chan->sport so that it can be reused by other
	 * sockets (as it's only used क्रम listening sockets).
	 */
	ग_लिखो_lock(&chan_list_lock);
	chan->sport = 0;
	ग_लिखो_unlock(&chan_list_lock);

	अगर (hcon->state == BT_CONNECTED) अणु
		अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED) अणु
			__clear_chan_समयr(chan);
			अगर (l2cap_chan_check_security(chan, true))
				l2cap_state_change(chan, BT_CONNECTED);
		पूर्ण अन्यथा
			l2cap_करो_start(chan);
	पूर्ण

	err = 0;

chan_unlock:
	l2cap_chan_unlock(chan);
	mutex_unlock(&conn->chan_lock);
करोne:
	hci_dev_unlock(hdev);
	hci_dev_put(hdev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(l2cap_chan_connect);

अटल व्योम l2cap_ecred_reconfigure(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा अणु
		काष्ठा l2cap_ecred_reconf_req req;
		__le16 scid;
	पूर्ण pdu;

	pdu.req.mtu = cpu_to_le16(chan->imtu);
	pdu.req.mps = cpu_to_le16(chan->mps);
	pdu.scid    = cpu_to_le16(chan->scid);

	chan->ident = l2cap_get_ident(conn);

	l2cap_send_cmd(conn, chan->ident, L2CAP_ECRED_RECONF_REQ,
		       माप(pdu), &pdu);
पूर्ण

पूर्णांक l2cap_chan_reconfigure(काष्ठा l2cap_chan *chan, __u16 mtu)
अणु
	अगर (chan->imtu > mtu)
		वापस -EINVAL;

	BT_DBG("chan %p mtu 0x%4.4x", chan, mtu);

	chan->imtu = mtu;

	l2cap_ecred_reconfigure(chan);

	वापस 0;
पूर्ण

/* ---- L2CAP पूर्णांकerface with lower layer (HCI) ---- */

पूर्णांक l2cap_connect_ind(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr)
अणु
	पूर्णांक exact = 0, lm1 = 0, lm2 = 0;
	काष्ठा l2cap_chan *c;

	BT_DBG("hdev %s, bdaddr %pMR", hdev->name, bdaddr);

	/* Find listening sockets and check their link_mode */
	पढ़ो_lock(&chan_list_lock);
	list_क्रम_each_entry(c, &chan_list, global_l) अणु
		अगर (c->state != BT_LISTEN)
			जारी;

		अगर (!bacmp(&c->src, &hdev->bdaddr)) अणु
			lm1 |= HCI_LM_ACCEPT;
			अगर (test_bit(FLAG_ROLE_SWITCH, &c->flags))
				lm1 |= HCI_LM_MASTER;
			exact++;
		पूर्ण अन्यथा अगर (!bacmp(&c->src, BDADDR_ANY)) अणु
			lm2 |= HCI_LM_ACCEPT;
			अगर (test_bit(FLAG_ROLE_SWITCH, &c->flags))
				lm2 |= HCI_LM_MASTER;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&chan_list_lock);

	वापस exact ? lm1 : lm2;
पूर्ण

/* Find the next fixed channel in BT_LISTEN state, जारी iteration
 * from an existing channel in the list or from the beginning of the
 * global list (by passing शून्य as first parameter).
 */
अटल काष्ठा l2cap_chan *l2cap_global_fixed_chan(काष्ठा l2cap_chan *c,
						  काष्ठा hci_conn *hcon)
अणु
	u8 src_type = bdaddr_src_type(hcon);

	पढ़ो_lock(&chan_list_lock);

	अगर (c)
		c = list_next_entry(c, global_l);
	अन्यथा
		c = list_entry(chan_list.next, typeof(*c), global_l);

	list_क्रम_each_entry_from(c, &chan_list, global_l) अणु
		अगर (c->chan_type != L2CAP_CHAN_FIXED)
			जारी;
		अगर (c->state != BT_LISTEN)
			जारी;
		अगर (bacmp(&c->src, &hcon->src) && bacmp(&c->src, BDADDR_ANY))
			जारी;
		अगर (src_type != c->src_type)
			जारी;

		l2cap_chan_hold(c);
		पढ़ो_unlock(&chan_list_lock);
		वापस c;
	पूर्ण

	पढ़ो_unlock(&chan_list_lock);

	वापस शून्य;
पूर्ण

अटल व्योम l2cap_connect_cfm(काष्ठा hci_conn *hcon, u8 status)
अणु
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा l2cap_conn *conn;
	काष्ठा l2cap_chan *pchan;
	u8 dst_type;

	अगर (hcon->type != ACL_LINK && hcon->type != LE_LINK)
		वापस;

	BT_DBG("hcon %p bdaddr %pMR status %d", hcon, &hcon->dst, status);

	अगर (status) अणु
		l2cap_conn_del(hcon, bt_to_त्रुटि_सं(status));
		वापस;
	पूर्ण

	conn = l2cap_conn_add(hcon);
	अगर (!conn)
		वापस;

	dst_type = bdaddr_dst_type(hcon);

	/* If device is blocked, करो not create channels क्रम it */
	अगर (hci_bdaddr_list_lookup(&hdev->blacklist, &hcon->dst, dst_type))
		वापस;

	/* Find fixed channels and notअगरy them of the new connection. We
	 * use multiple inभागidual lookups, continuing each समय where
	 * we left off, because the list lock would prevent calling the
	 * potentially sleeping l2cap_chan_lock() function.
	 */
	pchan = l2cap_global_fixed_chan(शून्य, hcon);
	जबतक (pchan) अणु
		काष्ठा l2cap_chan *chan, *next;

		/* Client fixed channels should override server ones */
		अगर (__l2cap_get_chan_by_dcid(conn, pchan->scid))
			जाओ next;

		l2cap_chan_lock(pchan);
		chan = pchan->ops->new_connection(pchan);
		अगर (chan) अणु
			bacpy(&chan->src, &hcon->src);
			bacpy(&chan->dst, &hcon->dst);
			chan->src_type = bdaddr_src_type(hcon);
			chan->dst_type = dst_type;

			__l2cap_chan_add(conn, chan);
		पूर्ण

		l2cap_chan_unlock(pchan);
next:
		next = l2cap_global_fixed_chan(pchan, hcon);
		l2cap_chan_put(pchan);
		pchan = next;
	पूर्ण

	l2cap_conn_पढ़ोy(conn);
पूर्ण

पूर्णांक l2cap_disconn_ind(काष्ठा hci_conn *hcon)
अणु
	काष्ठा l2cap_conn *conn = hcon->l2cap_data;

	BT_DBG("hcon %p", hcon);

	अगर (!conn)
		वापस HCI_ERROR_REMOTE_USER_TERM;
	वापस conn->disc_reason;
पूर्ण

अटल व्योम l2cap_disconn_cfm(काष्ठा hci_conn *hcon, u8 reason)
अणु
	अगर (hcon->type != ACL_LINK && hcon->type != LE_LINK)
		वापस;

	BT_DBG("hcon %p reason %d", hcon, reason);

	l2cap_conn_del(hcon, bt_to_त्रुटि_सं(reason));
पूर्ण

अटल अंतरभूत व्योम l2cap_check_encryption(काष्ठा l2cap_chan *chan, u8 encrypt)
अणु
	अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED)
		वापस;

	अगर (encrypt == 0x00) अणु
		अगर (chan->sec_level == BT_SECURITY_MEDIUM) अणु
			__set_chan_समयr(chan, L2CAP_ENC_TIMEOUT);
		पूर्ण अन्यथा अगर (chan->sec_level == BT_SECURITY_HIGH ||
			   chan->sec_level == BT_SECURITY_FIPS)
			l2cap_chan_बंद(chan, ECONNREFUSED);
	पूर्ण अन्यथा अणु
		अगर (chan->sec_level == BT_SECURITY_MEDIUM)
			__clear_chan_समयr(chan);
	पूर्ण
पूर्ण

अटल व्योम l2cap_security_cfm(काष्ठा hci_conn *hcon, u8 status, u8 encrypt)
अणु
	काष्ठा l2cap_conn *conn = hcon->l2cap_data;
	काष्ठा l2cap_chan *chan;

	अगर (!conn)
		वापस;

	BT_DBG("conn %p status 0x%2.2x encrypt %u", conn, status, encrypt);

	mutex_lock(&conn->chan_lock);

	list_क्रम_each_entry(chan, &conn->chan_l, list) अणु
		l2cap_chan_lock(chan);

		BT_DBG("chan %p scid 0x%4.4x state %s", chan, chan->scid,
		       state_to_string(chan->state));

		अगर (chan->scid == L2CAP_CID_A2MP) अणु
			l2cap_chan_unlock(chan);
			जारी;
		पूर्ण

		अगर (!status && encrypt)
			chan->sec_level = hcon->sec_level;

		अगर (!__l2cap_no_conn_pending(chan)) अणु
			l2cap_chan_unlock(chan);
			जारी;
		पूर्ण

		अगर (!status && (chan->state == BT_CONNECTED ||
				chan->state == BT_CONFIG)) अणु
			chan->ops->resume(chan);
			l2cap_check_encryption(chan, encrypt);
			l2cap_chan_unlock(chan);
			जारी;
		पूर्ण

		अगर (chan->state == BT_CONNECT) अणु
			अगर (!status && l2cap_check_enc_key_size(hcon))
				l2cap_start_connection(chan);
			अन्यथा
				__set_chan_समयr(chan, L2CAP_DISC_TIMEOUT);
		पूर्ण अन्यथा अगर (chan->state == BT_CONNECT2 &&
			   !(chan->mode == L2CAP_MODE_EXT_FLOWCTL ||
			     chan->mode == L2CAP_MODE_LE_FLOWCTL)) अणु
			काष्ठा l2cap_conn_rsp rsp;
			__u16 res, stat;

			अगर (!status && l2cap_check_enc_key_size(hcon)) अणु
				अगर (test_bit(FLAG_DEFER_SETUP, &chan->flags)) अणु
					res = L2CAP_CR_PEND;
					stat = L2CAP_CS_AUTHOR_PEND;
					chan->ops->defer(chan);
				पूर्ण अन्यथा अणु
					l2cap_state_change(chan, BT_CONFIG);
					res = L2CAP_CR_SUCCESS;
					stat = L2CAP_CS_NO_INFO;
				पूर्ण
			पूर्ण अन्यथा अणु
				l2cap_state_change(chan, BT_DISCONN);
				__set_chan_समयr(chan, L2CAP_DISC_TIMEOUT);
				res = L2CAP_CR_SEC_BLOCK;
				stat = L2CAP_CS_NO_INFO;
			पूर्ण

			rsp.scid   = cpu_to_le16(chan->dcid);
			rsp.dcid   = cpu_to_le16(chan->scid);
			rsp.result = cpu_to_le16(res);
			rsp.status = cpu_to_le16(stat);
			l2cap_send_cmd(conn, chan->ident, L2CAP_CONN_RSP,
				       माप(rsp), &rsp);

			अगर (!test_bit(CONF_REQ_SENT, &chan->conf_state) &&
			    res == L2CAP_CR_SUCCESS) अणु
				अक्षर buf[128];
				set_bit(CONF_REQ_SENT, &chan->conf_state);
				l2cap_send_cmd(conn, l2cap_get_ident(conn),
					       L2CAP_CONF_REQ,
					       l2cap_build_conf_req(chan, buf, माप(buf)),
					       buf);
				chan->num_conf_req++;
			पूर्ण
		पूर्ण

		l2cap_chan_unlock(chan);
	पूर्ण

	mutex_unlock(&conn->chan_lock);
पूर्ण

/* Append fragment पूर्णांकo frame respecting the maximum len of rx_skb */
अटल पूर्णांक l2cap_recv_frag(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb,
			   u16 len)
अणु
	अगर (!conn->rx_skb) अणु
		/* Allocate skb क्रम the complete frame (with header) */
		conn->rx_skb = bt_skb_alloc(len, GFP_KERNEL);
		अगर (!conn->rx_skb)
			वापस -ENOMEM;
		/* Init rx_len */
		conn->rx_len = len;
	पूर्ण

	/* Copy as much as the rx_skb can hold */
	len = min_t(u16, len, skb->len);
	skb_copy_from_linear_data(skb, skb_put(conn->rx_skb, len), len);
	skb_pull(skb, len);
	conn->rx_len -= len;

	वापस len;
पूर्ण

अटल पूर्णांक l2cap_recv_len(काष्ठा l2cap_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *rx_skb;
	पूर्णांक len;

	/* Append just enough to complete the header */
	len = l2cap_recv_frag(conn, skb, L2CAP_LEN_SIZE - conn->rx_skb->len);

	/* If header could not be पढ़ो just जारी */
	अगर (len < 0 || conn->rx_skb->len < L2CAP_LEN_SIZE)
		वापस len;

	rx_skb = conn->rx_skb;
	len = get_unaligned_le16(rx_skb->data);

	/* Check अगर rx_skb has enough space to received all fragments */
	अगर (len + (L2CAP_HDR_SIZE - L2CAP_LEN_SIZE) <= skb_tailroom(rx_skb)) अणु
		/* Update expected len */
		conn->rx_len = len + (L2CAP_HDR_SIZE - L2CAP_LEN_SIZE);
		वापस L2CAP_LEN_SIZE;
	पूर्ण

	/* Reset conn->rx_skb since it will need to be पुनः_स्मृतिated in order to
	 * fit all fragments.
	 */
	conn->rx_skb = शून्य;

	/* Reallocates rx_skb using the exact expected length */
	len = l2cap_recv_frag(conn, rx_skb,
			      len + (L2CAP_HDR_SIZE - L2CAP_LEN_SIZE));
	kमुक्त_skb(rx_skb);

	वापस len;
पूर्ण

अटल व्योम l2cap_recv_reset(काष्ठा l2cap_conn *conn)
अणु
	kमुक्त_skb(conn->rx_skb);
	conn->rx_skb = शून्य;
	conn->rx_len = 0;
पूर्ण

व्योम l2cap_recv_acldata(काष्ठा hci_conn *hcon, काष्ठा sk_buff *skb, u16 flags)
अणु
	काष्ठा l2cap_conn *conn = hcon->l2cap_data;
	पूर्णांक len;

	/* For AMP controller करो not create l2cap conn */
	अगर (!conn && hcon->hdev->dev_type != HCI_PRIMARY)
		जाओ drop;

	अगर (!conn)
		conn = l2cap_conn_add(hcon);

	अगर (!conn)
		जाओ drop;

	BT_DBG("conn %p len %u flags 0x%x", conn, skb->len, flags);

	चयन (flags) अणु
	हाल ACL_START:
	हाल ACL_START_NO_FLUSH:
	हाल ACL_COMPLETE:
		अगर (conn->rx_skb) अणु
			BT_ERR("Unexpected start frame (len %d)", skb->len);
			l2cap_recv_reset(conn);
			l2cap_conn_unreliable(conn, ECOMM);
		पूर्ण

		/* Start fragment may not contain the L2CAP length so just
		 * copy the initial byte when that happens and use conn->mtu as
		 * expected length.
		 */
		अगर (skb->len < L2CAP_LEN_SIZE) अणु
			अगर (l2cap_recv_frag(conn, skb, conn->mtu) < 0)
				जाओ drop;
			वापस;
		पूर्ण

		len = get_unaligned_le16(skb->data) + L2CAP_HDR_SIZE;

		अगर (len == skb->len) अणु
			/* Complete frame received */
			l2cap_recv_frame(conn, skb);
			वापस;
		पूर्ण

		BT_DBG("Start: total len %d, frag len %u", len, skb->len);

		अगर (skb->len > len) अणु
			BT_ERR("Frame is too long (len %u, expected len %d)",
			       skb->len, len);
			l2cap_conn_unreliable(conn, ECOMM);
			जाओ drop;
		पूर्ण

		/* Append fragment पूर्णांकo frame (with header) */
		अगर (l2cap_recv_frag(conn, skb, len) < 0)
			जाओ drop;

		अवरोध;

	हाल ACL_CONT:
		BT_DBG("Cont: frag len %u (expecting %u)", skb->len, conn->rx_len);

		अगर (!conn->rx_skb) अणु
			BT_ERR("Unexpected continuation frame (len %d)", skb->len);
			l2cap_conn_unreliable(conn, ECOMM);
			जाओ drop;
		पूर्ण

		/* Complete the L2CAP length अगर it has not been पढ़ो */
		अगर (conn->rx_skb->len < L2CAP_LEN_SIZE) अणु
			अगर (l2cap_recv_len(conn, skb) < 0) अणु
				l2cap_conn_unreliable(conn, ECOMM);
				जाओ drop;
			पूर्ण

			/* Header still could not be पढ़ो just जारी */
			अगर (conn->rx_skb->len < L2CAP_LEN_SIZE)
				वापस;
		पूर्ण

		अगर (skb->len > conn->rx_len) अणु
			BT_ERR("Fragment is too long (len %u, expected %u)",
			       skb->len, conn->rx_len);
			l2cap_recv_reset(conn);
			l2cap_conn_unreliable(conn, ECOMM);
			जाओ drop;
		पूर्ण

		/* Append fragment पूर्णांकo frame (with header) */
		l2cap_recv_frag(conn, skb, skb->len);

		अगर (!conn->rx_len) अणु
			/* Complete frame received. l2cap_recv_frame
			 * takes ownership of the skb so set the global
			 * rx_skb poपूर्णांकer to शून्य first.
			 */
			काष्ठा sk_buff *rx_skb = conn->rx_skb;
			conn->rx_skb = शून्य;
			l2cap_recv_frame(conn, rx_skb);
		पूर्ण
		अवरोध;
	पूर्ण

drop:
	kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा hci_cb l2cap_cb = अणु
	.name		= "L2CAP",
	.connect_cfm	= l2cap_connect_cfm,
	.disconn_cfm	= l2cap_disconn_cfm,
	.security_cfm	= l2cap_security_cfm,
पूर्ण;

अटल पूर्णांक l2cap_debugfs_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा l2cap_chan *c;

	पढ़ो_lock(&chan_list_lock);

	list_क्रम_each_entry(c, &chan_list, global_l) अणु
		seq_म_लिखो(f, "%pMR (%u) %pMR (%u) %d %d 0x%4.4x 0x%4.4x %d %d %d %d\n",
			   &c->src, c->src_type, &c->dst, c->dst_type,
			   c->state, __le16_to_cpu(c->psm),
			   c->scid, c->dcid, c->imtu, c->omtu,
			   c->sec_level, c->mode);
	पूर्ण

	पढ़ो_unlock(&chan_list_lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(l2cap_debugfs);

अटल काष्ठा dentry *l2cap_debugfs;

पूर्णांक __init l2cap_init(व्योम)
अणु
	पूर्णांक err;

	err = l2cap_init_sockets();
	अगर (err < 0)
		वापस err;

	hci_रेजिस्टर_cb(&l2cap_cb);

	अगर (IS_ERR_OR_शून्य(bt_debugfs))
		वापस 0;

	l2cap_debugfs = debugfs_create_file("l2cap", 0444, bt_debugfs,
					    शून्य, &l2cap_debugfs_fops);

	वापस 0;
पूर्ण

व्योम l2cap_निकास(व्योम)
अणु
	debugfs_हटाओ(l2cap_debugfs);
	hci_unरेजिस्टर_cb(&l2cap_cb);
	l2cap_cleanup_sockets();
पूर्ण

module_param(disable_erपंचांग, bool, 0644);
MODULE_PARM_DESC(disable_erपंचांग, "Disable enhanced retransmission mode");

module_param(enable_ecred, bool, 0644);
MODULE_PARM_DESC(enable_ecred, "Enable enhanced credit flow control mode");
