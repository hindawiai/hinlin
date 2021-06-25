<शैली गुरु>
/*
   CMTP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2002-2003 Marcel Holपंचांगann <marcel@holपंचांगann.org>

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

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/file.h>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <net/sock.h>

#समावेश <linux/isdn/capilli.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश "cmtp.h"

#घोषणा VERSION "1.0"

अटल DECLARE_RWSEM(cmtp_session_sem);
अटल LIST_HEAD(cmtp_session_list);

अटल काष्ठा cmtp_session *__cmtp_get_session(bdaddr_t *bdaddr)
अणु
	काष्ठा cmtp_session *session;

	BT_DBG("");

	list_क्रम_each_entry(session, &cmtp_session_list, list)
		अगर (!bacmp(bdaddr, &session->bdaddr))
			वापस session;

	वापस शून्य;
पूर्ण

अटल व्योम __cmtp_link_session(काष्ठा cmtp_session *session)
अणु
	list_add(&session->list, &cmtp_session_list);
पूर्ण

अटल व्योम __cmtp_unlink_session(काष्ठा cmtp_session *session)
अणु
	list_del(&session->list);
पूर्ण

अटल व्योम __cmtp_copy_session(काष्ठा cmtp_session *session, काष्ठा cmtp_conninfo *ci)
अणु
	u32 valid_flags = BIT(CMTP_LOOPBACK);
	स_रखो(ci, 0, माप(*ci));
	bacpy(&ci->bdaddr, &session->bdaddr);

	ci->flags = session->flags & valid_flags;
	ci->state = session->state;

	ci->num = session->num;
पूर्ण


अटल अंतरभूत पूर्णांक cmtp_alloc_block_id(काष्ठा cmtp_session *session)
अणु
	पूर्णांक i, id = -1;

	क्रम (i = 0; i < 16; i++)
		अगर (!test_and_set_bit(i, &session->blockids)) अणु
			id = i;
			अवरोध;
		पूर्ण

	वापस id;
पूर्ण

अटल अंतरभूत व्योम cmtp_मुक्त_block_id(काष्ठा cmtp_session *session, पूर्णांक id)
अणु
	clear_bit(id, &session->blockids);
पूर्ण

अटल अंतरभूत व्योम cmtp_add_msgpart(काष्ठा cmtp_session *session, पूर्णांक id, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb = session->reassembly[id], *nskb;
	पूर्णांक size;

	BT_DBG("session %p buf %p count %d", session, buf, count);

	size = (skb) ? skb->len + count : count;

	nskb = alloc_skb(size, GFP_ATOMIC);
	अगर (!nskb) अणु
		BT_ERR("Can't allocate memory for CAPI message");
		वापस;
	पूर्ण

	अगर (skb && (skb->len > 0))
		skb_copy_from_linear_data(skb, skb_put(nskb, skb->len), skb->len);

	skb_put_data(nskb, buf, count);

	session->reassembly[id] = nskb;

	kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत पूर्णांक cmtp_recv_frame(काष्ठा cmtp_session *session, काष्ठा sk_buff *skb)
अणु
	__u8 hdr, hdrlen, id;
	__u16 len;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	जबतक (skb->len > 0) अणु
		hdr = skb->data[0];

		चयन (hdr & 0xc0) अणु
		हाल 0x40:
			hdrlen = 2;
			len = skb->data[1];
			अवरोध;
		हाल 0x80:
			hdrlen = 3;
			len = skb->data[1] | (skb->data[2] << 8);
			अवरोध;
		शेष:
			hdrlen = 1;
			len = 0;
			अवरोध;
		पूर्ण

		id = (hdr & 0x3c) >> 2;

		BT_DBG("hdr 0x%02x hdrlen %d len %d id %d", hdr, hdrlen, len, id);

		अगर (hdrlen + len > skb->len) अणु
			BT_ERR("Wrong size or header information in CMTP frame");
			अवरोध;
		पूर्ण

		अगर (len == 0) अणु
			skb_pull(skb, hdrlen);
			जारी;
		पूर्ण

		चयन (hdr & 0x03) अणु
		हाल 0x00:
			cmtp_add_msgpart(session, id, skb->data + hdrlen, len);
			cmtp_recv_capimsg(session, session->reassembly[id]);
			session->reassembly[id] = शून्य;
			अवरोध;
		हाल 0x01:
			cmtp_add_msgpart(session, id, skb->data + hdrlen, len);
			अवरोध;
		शेष:
			kमुक्त_skb(session->reassembly[id]);
			session->reassembly[id] = शून्य;
			अवरोध;
		पूर्ण

		skb_pull(skb, hdrlen + len);
	पूर्ण

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक cmtp_send_frame(काष्ठा cmtp_session *session, अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	काष्ठा socket *sock = session->sock;
	काष्ठा kvec iv = अणु data, len पूर्ण;
	काष्ठा msghdr msg;

	BT_DBG("session %p data %p len %d", session, data, len);

	अगर (!len)
		वापस 0;

	स_रखो(&msg, 0, माप(msg));

	वापस kernel_sendmsg(sock, &msg, &iv, 1, len);
पूर्ण

अटल व्योम cmtp_process_transmit(काष्ठा cmtp_session *session)
अणु
	काष्ठा sk_buff *skb, *nskb;
	अचिन्हित अक्षर *hdr;
	अचिन्हित पूर्णांक size, tail;

	BT_DBG("session %p", session);

	nskb = alloc_skb(session->mtu, GFP_ATOMIC);
	अगर (!nskb) अणु
		BT_ERR("Can't allocate memory for new frame");
		वापस;
	पूर्ण

	जबतक ((skb = skb_dequeue(&session->transmit))) अणु
		काष्ठा cmtp_scb *scb = (व्योम *) skb->cb;

		tail = session->mtu - nskb->len;
		अगर (tail < 5) अणु
			cmtp_send_frame(session, nskb->data, nskb->len);
			skb_trim(nskb, 0);
			tail = session->mtu;
		पूर्ण

		size = min_t(uपूर्णांक, ((tail < 258) ? (tail - 2) : (tail - 3)), skb->len);

		अगर (scb->id < 0) अणु
			scb->id = cmtp_alloc_block_id(session);
			अगर (scb->id < 0) अणु
				skb_queue_head(&session->transmit, skb);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (size < 256) अणु
			hdr = skb_put(nskb, 2);
			hdr[0] = 0x40
				| ((scb->id << 2) & 0x3c)
				| ((skb->len == size) ? 0x00 : 0x01);
			hdr[1] = size;
		पूर्ण अन्यथा अणु
			hdr = skb_put(nskb, 3);
			hdr[0] = 0x80
				| ((scb->id << 2) & 0x3c)
				| ((skb->len == size) ? 0x00 : 0x01);
			hdr[1] = size & 0xff;
			hdr[2] = size >> 8;
		पूर्ण

		skb_copy_from_linear_data(skb, skb_put(nskb, size), size);
		skb_pull(skb, size);

		अगर (skb->len > 0) अणु
			skb_queue_head(&session->transmit, skb);
		पूर्ण अन्यथा अणु
			cmtp_मुक्त_block_id(session, scb->id);
			अगर (scb->data) अणु
				cmtp_send_frame(session, nskb->data, nskb->len);
				skb_trim(nskb, 0);
			पूर्ण
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	cmtp_send_frame(session, nskb->data, nskb->len);

	kमुक्त_skb(nskb);
पूर्ण

अटल पूर्णांक cmtp_session(व्योम *arg)
अणु
	काष्ठा cmtp_session *session = arg;
	काष्ठा sock *sk = session->sock->sk;
	काष्ठा sk_buff *skb;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	BT_DBG("session %p", session);

	set_user_nice(current, -15);

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		अगर (atomic_पढ़ो(&session->terminate))
			अवरोध;
		अगर (sk->sk_state != BT_CONNECTED)
			अवरोध;

		जबतक ((skb = skb_dequeue(&sk->sk_receive_queue))) अणु
			skb_orphan(skb);
			अगर (!skb_linearize(skb))
				cmtp_recv_frame(session, skb);
			अन्यथा
				kमुक्त_skb(skb);
		पूर्ण

		cmtp_process_transmit(session);

		/*
		 * रुको_woken() perक्रमms the necessary memory barriers
		 * क्रम us; see the header comment क्रम this primitive.
		 */
		रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	करोwn_ग_लिखो(&cmtp_session_sem);

	अगर (!(session->flags & BIT(CMTP_LOOPBACK)))
		cmtp_detach_device(session);

	fput(session->sock->file);

	__cmtp_unlink_session(session);

	up_ग_लिखो(&cmtp_session_sem);

	kमुक्त(session);
	module_put_and_निकास(0);
	वापस 0;
पूर्ण

पूर्णांक cmtp_add_connection(काष्ठा cmtp_connadd_req *req, काष्ठा socket *sock)
अणु
	u32 valid_flags = BIT(CMTP_LOOPBACK);
	काष्ठा cmtp_session *session, *s;
	पूर्णांक i, err;

	BT_DBG("");

	अगर (!l2cap_is_socket(sock))
		वापस -EBADFD;

	अगर (req->flags & ~valid_flags)
		वापस -EINVAL;

	session = kzalloc(माप(काष्ठा cmtp_session), GFP_KERNEL);
	अगर (!session)
		वापस -ENOMEM;

	करोwn_ग_लिखो(&cmtp_session_sem);

	s = __cmtp_get_session(&l2cap_pi(sock->sk)->chan->dst);
	अगर (s && s->state == BT_CONNECTED) अणु
		err = -EEXIST;
		जाओ failed;
	पूर्ण

	bacpy(&session->bdaddr, &l2cap_pi(sock->sk)->chan->dst);

	session->mtu = min_t(uपूर्णांक, l2cap_pi(sock->sk)->chan->omtu,
					l2cap_pi(sock->sk)->chan->imtu);

	BT_DBG("mtu %d", session->mtu);

	प्र_लिखो(session->name, "%pMR", &session->bdaddr);

	session->sock  = sock;
	session->state = BT_CONFIG;

	init_रुकोqueue_head(&session->रुको);

	session->msgnum = CMTP_INITIAL_MSGNUM;

	INIT_LIST_HEAD(&session->applications);

	skb_queue_head_init(&session->transmit);

	क्रम (i = 0; i < 16; i++)
		session->reassembly[i] = शून्य;

	session->flags = req->flags;

	__cmtp_link_session(session);

	__module_get(THIS_MODULE);
	session->task = kthपढ़ो_run(cmtp_session, session, "kcmtpd_ctr_%d",
								session->num);
	अगर (IS_ERR(session->task)) अणु
		module_put(THIS_MODULE);
		err = PTR_ERR(session->task);
		जाओ unlink;
	पूर्ण

	अगर (!(session->flags & BIT(CMTP_LOOPBACK))) अणु
		err = cmtp_attach_device(session);
		अगर (err < 0) अणु
			atomic_inc(&session->terminate);
			wake_up_पूर्णांकerruptible(sk_sleep(session->sock->sk));
			up_ग_लिखो(&cmtp_session_sem);
			वापस err;
		पूर्ण
	पूर्ण

	up_ग_लिखो(&cmtp_session_sem);
	वापस 0;

unlink:
	__cmtp_unlink_session(session);

failed:
	up_ग_लिखो(&cmtp_session_sem);
	kमुक्त(session);
	वापस err;
पूर्ण

पूर्णांक cmtp_del_connection(काष्ठा cmtp_conndel_req *req)
अणु
	u32 valid_flags = 0;
	काष्ठा cmtp_session *session;
	पूर्णांक err = 0;

	BT_DBG("");

	अगर (req->flags & ~valid_flags)
		वापस -EINVAL;

	करोwn_पढ़ो(&cmtp_session_sem);

	session = __cmtp_get_session(&req->bdaddr);
	अगर (session) अणु
		/* Flush the transmit queue */
		skb_queue_purge(&session->transmit);

		/* Stop session thपढ़ो */
		atomic_inc(&session->terminate);

		/*
		 * See the comment preceding the call to रुको_woken()
		 * in cmtp_session().
		 */
		wake_up_पूर्णांकerruptible(sk_sleep(session->sock->sk));
	पूर्ण अन्यथा
		err = -ENOENT;

	up_पढ़ो(&cmtp_session_sem);
	वापस err;
पूर्ण

पूर्णांक cmtp_get_connlist(काष्ठा cmtp_connlist_req *req)
अणु
	काष्ठा cmtp_session *session;
	पूर्णांक err = 0, n = 0;

	BT_DBG("");

	करोwn_पढ़ो(&cmtp_session_sem);

	list_क्रम_each_entry(session, &cmtp_session_list, list) अणु
		काष्ठा cmtp_conninfo ci;

		__cmtp_copy_session(session, &ci);

		अगर (copy_to_user(req->ci, &ci, माप(ci))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (++n >= req->cnum)
			अवरोध;

		req->ci++;
	पूर्ण
	req->cnum = n;

	up_पढ़ो(&cmtp_session_sem);
	वापस err;
पूर्ण

पूर्णांक cmtp_get_conninfo(काष्ठा cmtp_conninfo *ci)
अणु
	काष्ठा cmtp_session *session;
	पूर्णांक err = 0;

	करोwn_पढ़ो(&cmtp_session_sem);

	session = __cmtp_get_session(&ci->bdaddr);
	अगर (session)
		__cmtp_copy_session(session, ci);
	अन्यथा
		err = -ENOENT;

	up_पढ़ो(&cmtp_session_sem);
	वापस err;
पूर्ण


अटल पूर्णांक __init cmtp_init(व्योम)
अणु
	BT_INFO("CMTP (CAPI Emulation) ver %s", VERSION);

	cmtp_init_sockets();

	वापस 0;
पूर्ण

अटल व्योम __निकास cmtp_निकास(व्योम)
अणु
	cmtp_cleanup_sockets();
पूर्ण

module_init(cmtp_init);
module_निकास(cmtp_निकास);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth CMTP ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("bt-proto-5");
