<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/9p/trans_fd.c
 *
 * Fd transport layer.  Includes deprecated socket layer.
 *
 *  Copyright (C) 2006 by Russ Cox <rsc@swtch.com>
 *  Copyright (C) 2004-2005 by Latchesar Ionkov <lucho@ionkov.net>
 *  Copyright (C) 2004-2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 1997-2002 by Ron Minnich <rminnich@sarnoff.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/un.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/inet.h>
#समावेश <linux/idr.h>
#समावेश <linux/file.h>
#समावेश <linux/parser.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>
#समावेश <net/9p/transport.h>

#समावेश <linux/syscalls.h> /* समाप्तme */

#घोषणा P9_PORT 564
#घोषणा MAX_SOCK_BUF (64*1024)
#घोषणा MAXPOLLWADDR	2

अटल काष्ठा p9_trans_module p9_tcp_trans;
अटल काष्ठा p9_trans_module p9_fd_trans;

/**
 * काष्ठा p9_fd_opts - per-transport options
 * @rfd: file descriptor क्रम पढ़ोing (trans=fd)
 * @wfd: file descriptor क्रम writing (trans=fd)
 * @port: port to connect to (trans=tcp)
 * @privport: port is privileged
 */

काष्ठा p9_fd_opts अणु
	पूर्णांक rfd;
	पूर्णांक wfd;
	u16 port;
	bool privport;
पूर्ण;

/*
  * Option Parsing (code inspired by NFS code)
  *  - a little lazy - parse all fd-transport options
  */

क्रमागत अणु
	/* Options that take पूर्णांकeger arguments */
	Opt_port, Opt_rfdno, Opt_wfdno, Opt_err,
	/* Options that take no arguments */
	Opt_privport,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_port, "port=%u"पूर्ण,
	अणुOpt_rfdno, "rfdno=%u"पूर्ण,
	अणुOpt_wfdno, "wfdno=%u"पूर्ण,
	अणुOpt_privport, "privport"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

क्रमागत अणु
	Rworksched = 1,		/* पढ़ो work scheduled or running */
	Rpending = 2,		/* can पढ़ो */
	Wworksched = 4,		/* ग_लिखो work scheduled or running */
	Wpending = 8,		/* can ग_लिखो */
पूर्ण;

काष्ठा p9_poll_रुको अणु
	काष्ठा p9_conn *conn;
	रुको_queue_entry_t रुको;
	रुको_queue_head_t *रुको_addr;
पूर्ण;

/**
 * काष्ठा p9_conn - fd mux connection state inक्रमmation
 * @mux_list: list link क्रम mux to manage multiple connections (?)
 * @client: reference to client instance क्रम this connection
 * @err: error state
 * @req_list: accounting क्रम requests which have been sent
 * @unsent_req_list: accounting क्रम requests that haven't been sent
 * @rreq: पढ़ो request
 * @wreq: ग_लिखो request
 * @req: current request being processed (अगर any)
 * @पंचांगp_buf: temporary buffer to पढ़ो in header
 * @rc: temporary fcall क्रम पढ़ोing current frame
 * @wpos: ग_लिखो position क्रम current frame
 * @wsize: amount of data to ग_लिखो क्रम current frame
 * @wbuf: current ग_लिखो buffer
 * @poll_pending_link: pending links to be polled per conn
 * @poll_रुको: array of रुको_q's क्रम various worker thपढ़ोs
 * @pt: poll state
 * @rq: current पढ़ो work
 * @wq: current ग_लिखो work
 * @wsched: ????
 *
 */

काष्ठा p9_conn अणु
	काष्ठा list_head mux_list;
	काष्ठा p9_client *client;
	पूर्णांक err;
	काष्ठा list_head req_list;
	काष्ठा list_head unsent_req_list;
	काष्ठा p9_req_t *rreq;
	काष्ठा p9_req_t *wreq;
	अक्षर पंचांगp_buf[7];
	काष्ठा p9_fcall rc;
	पूर्णांक wpos;
	पूर्णांक wsize;
	अक्षर *wbuf;
	काष्ठा list_head poll_pending_link;
	काष्ठा p9_poll_रुको poll_रुको[MAXPOLLWADDR];
	poll_table pt;
	काष्ठा work_काष्ठा rq;
	काष्ठा work_काष्ठा wq;
	अचिन्हित दीर्घ wsched;
पूर्ण;

/**
 * काष्ठा p9_trans_fd - transport state
 * @rd: reference to file to पढ़ो from
 * @wr: reference of file to ग_लिखो to
 * @conn: connection state reference
 *
 */

काष्ठा p9_trans_fd अणु
	काष्ठा file *rd;
	काष्ठा file *wr;
	काष्ठा p9_conn conn;
पूर्ण;

अटल व्योम p9_poll_workfn(काष्ठा work_काष्ठा *work);

अटल DEFINE_SPINLOCK(p9_poll_lock);
अटल LIST_HEAD(p9_poll_pending_list);
अटल DECLARE_WORK(p9_poll_work, p9_poll_workfn);

अटल अचिन्हित पूर्णांक p9_ipport_resv_min = P9_DEF_MIN_RESVPORT;
अटल अचिन्हित पूर्णांक p9_ipport_resv_max = P9_DEF_MAX_RESVPORT;

अटल व्योम p9_mux_poll_stop(काष्ठा p9_conn *m)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(m->poll_रुको); i++) अणु
		काष्ठा p9_poll_रुको *pरुको = &m->poll_रुको[i];

		अगर (pरुको->रुको_addr) अणु
			हटाओ_रुको_queue(pरुको->रुको_addr, &pरुको->रुको);
			pरुको->रुको_addr = शून्य;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&p9_poll_lock, flags);
	list_del_init(&m->poll_pending_link);
	spin_unlock_irqrestore(&p9_poll_lock, flags);

	flush_work(&p9_poll_work);
पूर्ण

/**
 * p9_conn_cancel - cancel all pending requests with error
 * @m: mux data
 * @err: error code
 *
 */

अटल व्योम p9_conn_cancel(काष्ठा p9_conn *m, पूर्णांक err)
अणु
	काष्ठा p9_req_t *req, *rपंचांगp;
	LIST_HEAD(cancel_list);

	p9_debug(P9_DEBUG_ERROR, "mux %p err %d\n", m, err);

	spin_lock(&m->client->lock);

	अगर (m->err) अणु
		spin_unlock(&m->client->lock);
		वापस;
	पूर्ण

	m->err = err;

	list_क्रम_each_entry_safe(req, rपंचांगp, &m->req_list, req_list) अणु
		list_move(&req->req_list, &cancel_list);
	पूर्ण
	list_क्रम_each_entry_safe(req, rपंचांगp, &m->unsent_req_list, req_list) अणु
		list_move(&req->req_list, &cancel_list);
	पूर्ण

	list_क्रम_each_entry_safe(req, rपंचांगp, &cancel_list, req_list) अणु
		p9_debug(P9_DEBUG_ERROR, "call back req %p\n", req);
		list_del(&req->req_list);
		अगर (!req->t_err)
			req->t_err = err;
		p9_client_cb(m->client, req, REQ_STATUS_ERROR);
	पूर्ण
	spin_unlock(&m->client->lock);
पूर्ण

अटल __poll_t
p9_fd_poll(काष्ठा p9_client *client, काष्ठा poll_table_काष्ठा *pt, पूर्णांक *err)
अणु
	__poll_t ret;
	काष्ठा p9_trans_fd *ts = शून्य;

	अगर (client && client->status == Connected)
		ts = client->trans;

	अगर (!ts) अणु
		अगर (err)
			*err = -EREMOTEIO;
		वापस EPOLLERR;
	पूर्ण

	ret = vfs_poll(ts->rd, pt);
	अगर (ts->rd != ts->wr)
		ret = (ret & ~EPOLLOUT) | (vfs_poll(ts->wr, pt) & ~EPOLLIN);
	वापस ret;
पूर्ण

/**
 * p9_fd_पढ़ो- पढ़ो from a fd
 * @client: client instance
 * @v: buffer to receive data पूर्णांकo
 * @len: size of receive buffer
 *
 */

अटल पूर्णांक p9_fd_पढ़ो(काष्ठा p9_client *client, व्योम *v, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा p9_trans_fd *ts = शून्य;
	loff_t pos;

	अगर (client && client->status != Disconnected)
		ts = client->trans;

	अगर (!ts)
		वापस -EREMOTEIO;

	अगर (!(ts->rd->f_flags & O_NONBLOCK))
		p9_debug(P9_DEBUG_ERROR, "blocking read ...\n");

	pos = ts->rd->f_pos;
	ret = kernel_पढ़ो(ts->rd, v, len, &pos);
	अगर (ret <= 0 && ret != -ERESTARTSYS && ret != -EAGAIN)
		client->status = Disconnected;
	वापस ret;
पूर्ण

/**
 * p9_पढ़ो_work - called when there is some data to be पढ़ो from a transport
 * @work: container of work to be करोne
 *
 */

अटल व्योम p9_पढ़ो_work(काष्ठा work_काष्ठा *work)
अणु
	__poll_t n;
	पूर्णांक err;
	काष्ठा p9_conn *m;

	m = container_of(work, काष्ठा p9_conn, rq);

	अगर (m->err < 0)
		वापस;

	p9_debug(P9_DEBUG_TRANS, "start mux %p pos %zd\n", m, m->rc.offset);

	अगर (!m->rc.sdata) अणु
		m->rc.sdata = m->पंचांगp_buf;
		m->rc.offset = 0;
		m->rc.capacity = 7; /* start by पढ़ोing header */
	पूर्ण

	clear_bit(Rpending, &m->wsched);
	p9_debug(P9_DEBUG_TRANS, "read mux %p pos %zd size: %zd = %zd\n",
		 m, m->rc.offset, m->rc.capacity,
		 m->rc.capacity - m->rc.offset);
	err = p9_fd_पढ़ो(m->client, m->rc.sdata + m->rc.offset,
			 m->rc.capacity - m->rc.offset);
	p9_debug(P9_DEBUG_TRANS, "mux %p got %d bytes\n", m, err);
	अगर (err == -EAGAIN)
		जाओ end_clear;

	अगर (err <= 0)
		जाओ error;

	m->rc.offset += err;

	/* header पढ़ो in */
	अगर ((!m->rreq) && (m->rc.offset == m->rc.capacity)) अणु
		p9_debug(P9_DEBUG_TRANS, "got new header\n");

		/* Header size */
		m->rc.size = 7;
		err = p9_parse_header(&m->rc, &m->rc.size, शून्य, शून्य, 0);
		अगर (err) अणु
			p9_debug(P9_DEBUG_ERROR,
				 "error parsing header: %d\n", err);
			जाओ error;
		पूर्ण

		अगर (m->rc.size >= m->client->msize) अणु
			p9_debug(P9_DEBUG_ERROR,
				 "requested packet size too big: %d\n",
				 m->rc.size);
			err = -EIO;
			जाओ error;
		पूर्ण

		p9_debug(P9_DEBUG_TRANS,
			 "mux %p pkt: size: %d bytes tag: %d\n",
			 m, m->rc.size, m->rc.tag);

		m->rreq = p9_tag_lookup(m->client, m->rc.tag);
		अगर (!m->rreq || (m->rreq->status != REQ_STATUS_SENT)) अणु
			p9_debug(P9_DEBUG_ERROR, "Unexpected packet tag %d\n",
				 m->rc.tag);
			err = -EIO;
			जाओ error;
		पूर्ण

		अगर (!m->rreq->rc.sdata) अणु
			p9_debug(P9_DEBUG_ERROR,
				 "No recv fcall for tag %d (req %p), disconnecting!\n",
				 m->rc.tag, m->rreq);
			m->rreq = शून्य;
			err = -EIO;
			जाओ error;
		पूर्ण
		m->rc.sdata = m->rreq->rc.sdata;
		स_नकल(m->rc.sdata, m->पंचांगp_buf, m->rc.capacity);
		m->rc.capacity = m->rc.size;
	पूर्ण

	/* packet is पढ़ो in
	 * not an अन्यथा because some packets (like clunk) have no payload
	 */
	अगर ((m->rreq) && (m->rc.offset == m->rc.capacity)) अणु
		p9_debug(P9_DEBUG_TRANS, "got new packet\n");
		m->rreq->rc.size = m->rc.offset;
		spin_lock(&m->client->lock);
		अगर (m->rreq->status == REQ_STATUS_SENT) अणु
			list_del(&m->rreq->req_list);
			p9_client_cb(m->client, m->rreq, REQ_STATUS_RCVD);
		पूर्ण अन्यथा अगर (m->rreq->status == REQ_STATUS_FLSHD) अणु
			/* Ignore replies associated with a cancelled request. */
			p9_debug(P9_DEBUG_TRANS,
				 "Ignore replies associated with a cancelled request\n");
		पूर्ण अन्यथा अणु
			spin_unlock(&m->client->lock);
			p9_debug(P9_DEBUG_ERROR,
				 "Request tag %d errored out while we were reading the reply\n",
				 m->rc.tag);
			err = -EIO;
			जाओ error;
		पूर्ण
		spin_unlock(&m->client->lock);
		m->rc.sdata = शून्य;
		m->rc.offset = 0;
		m->rc.capacity = 0;
		p9_req_put(m->rreq);
		m->rreq = शून्य;
	पूर्ण

end_clear:
	clear_bit(Rworksched, &m->wsched);

	अगर (!list_empty(&m->req_list)) अणु
		अगर (test_and_clear_bit(Rpending, &m->wsched))
			n = EPOLLIN;
		अन्यथा
			n = p9_fd_poll(m->client, शून्य, शून्य);

		अगर ((n & EPOLLIN) && !test_and_set_bit(Rworksched, &m->wsched)) अणु
			p9_debug(P9_DEBUG_TRANS, "sched read work %p\n", m);
			schedule_work(&m->rq);
		पूर्ण
	पूर्ण

	वापस;
error:
	p9_conn_cancel(m, err);
	clear_bit(Rworksched, &m->wsched);
पूर्ण

/**
 * p9_fd_ग_लिखो - ग_लिखो to a socket
 * @client: client instance
 * @v: buffer to send data from
 * @len: size of send buffer
 *
 */

अटल पूर्णांक p9_fd_ग_लिखो(काष्ठा p9_client *client, व्योम *v, पूर्णांक len)
अणु
	sमाप_प्रकार ret;
	काष्ठा p9_trans_fd *ts = शून्य;

	अगर (client && client->status != Disconnected)
		ts = client->trans;

	अगर (!ts)
		वापस -EREMOTEIO;

	अगर (!(ts->wr->f_flags & O_NONBLOCK))
		p9_debug(P9_DEBUG_ERROR, "blocking write ...\n");

	ret = kernel_ग_लिखो(ts->wr, v, len, &ts->wr->f_pos);
	अगर (ret <= 0 && ret != -ERESTARTSYS && ret != -EAGAIN)
		client->status = Disconnected;
	वापस ret;
पूर्ण

/**
 * p9_ग_लिखो_work - called when a transport can send some data
 * @work: container क्रम work to be करोne
 *
 */

अटल व्योम p9_ग_लिखो_work(काष्ठा work_काष्ठा *work)
अणु
	__poll_t n;
	पूर्णांक err;
	काष्ठा p9_conn *m;
	काष्ठा p9_req_t *req;

	m = container_of(work, काष्ठा p9_conn, wq);

	अगर (m->err < 0) अणु
		clear_bit(Wworksched, &m->wsched);
		वापस;
	पूर्ण

	अगर (!m->wsize) अणु
		spin_lock(&m->client->lock);
		अगर (list_empty(&m->unsent_req_list)) अणु
			clear_bit(Wworksched, &m->wsched);
			spin_unlock(&m->client->lock);
			वापस;
		पूर्ण

		req = list_entry(m->unsent_req_list.next, काष्ठा p9_req_t,
			       req_list);
		req->status = REQ_STATUS_SENT;
		p9_debug(P9_DEBUG_TRANS, "move req %p\n", req);
		list_move_tail(&req->req_list, &m->req_list);

		m->wbuf = req->tc.sdata;
		m->wsize = req->tc.size;
		m->wpos = 0;
		p9_req_get(req);
		m->wreq = req;
		spin_unlock(&m->client->lock);
	पूर्ण

	p9_debug(P9_DEBUG_TRANS, "mux %p pos %d size %d\n",
		 m, m->wpos, m->wsize);
	clear_bit(Wpending, &m->wsched);
	err = p9_fd_ग_लिखो(m->client, m->wbuf + m->wpos, m->wsize - m->wpos);
	p9_debug(P9_DEBUG_TRANS, "mux %p sent %d bytes\n", m, err);
	अगर (err == -EAGAIN)
		जाओ end_clear;


	अगर (err < 0)
		जाओ error;
	अन्यथा अगर (err == 0) अणु
		err = -EREMOTEIO;
		जाओ error;
	पूर्ण

	m->wpos += err;
	अगर (m->wpos == m->wsize) अणु
		m->wpos = m->wsize = 0;
		p9_req_put(m->wreq);
		m->wreq = शून्य;
	पूर्ण

end_clear:
	clear_bit(Wworksched, &m->wsched);

	अगर (m->wsize || !list_empty(&m->unsent_req_list)) अणु
		अगर (test_and_clear_bit(Wpending, &m->wsched))
			n = EPOLLOUT;
		अन्यथा
			n = p9_fd_poll(m->client, शून्य, शून्य);

		अगर ((n & EPOLLOUT) &&
		   !test_and_set_bit(Wworksched, &m->wsched)) अणु
			p9_debug(P9_DEBUG_TRANS, "sched write work %p\n", m);
			schedule_work(&m->wq);
		पूर्ण
	पूर्ण

	वापस;

error:
	p9_conn_cancel(m, err);
	clear_bit(Wworksched, &m->wsched);
पूर्ण

अटल पूर्णांक p9_pollwake(रुको_queue_entry_t *रुको, अचिन्हित पूर्णांक mode, पूर्णांक sync, व्योम *key)
अणु
	काष्ठा p9_poll_रुको *pरुको =
		container_of(रुको, काष्ठा p9_poll_रुको, रुको);
	काष्ठा p9_conn *m = pरुको->conn;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p9_poll_lock, flags);
	अगर (list_empty(&m->poll_pending_link))
		list_add_tail(&m->poll_pending_link, &p9_poll_pending_list);
	spin_unlock_irqrestore(&p9_poll_lock, flags);

	schedule_work(&p9_poll_work);
	वापस 1;
पूर्ण

/**
 * p9_pollरुको - add poll task to the रुको queue
 * @filp: file poपूर्णांकer being polled
 * @रुको_address: रुको_q to block on
 * @p: poll state
 *
 * called by files poll operation to add v9fs-poll task to files रुको queue
 */

अटल व्योम
p9_pollरुको(काष्ठा file *filp, रुको_queue_head_t *रुको_address, poll_table *p)
अणु
	काष्ठा p9_conn *m = container_of(p, काष्ठा p9_conn, pt);
	काष्ठा p9_poll_रुको *pरुको = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(m->poll_रुको); i++) अणु
		अगर (m->poll_रुको[i].रुको_addr == शून्य) अणु
			pरुको = &m->poll_रुको[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pरुको) अणु
		p9_debug(P9_DEBUG_ERROR, "not enough wait_address slots\n");
		वापस;
	पूर्ण

	pरुको->conn = m;
	pरुको->रुको_addr = रुको_address;
	init_रुकोqueue_func_entry(&pरुको->रुको, p9_pollwake);
	add_रुको_queue(रुको_address, &pरुको->रुको);
पूर्ण

/**
 * p9_conn_create - initialize the per-session mux data
 * @client: client instance
 *
 * Note: Creates the polling task अगर this is the first session.
 */

अटल व्योम p9_conn_create(काष्ठा p9_client *client)
अणु
	__poll_t n;
	काष्ठा p9_trans_fd *ts = client->trans;
	काष्ठा p9_conn *m = &ts->conn;

	p9_debug(P9_DEBUG_TRANS, "client %p msize %d\n", client, client->msize);

	INIT_LIST_HEAD(&m->mux_list);
	m->client = client;

	INIT_LIST_HEAD(&m->req_list);
	INIT_LIST_HEAD(&m->unsent_req_list);
	INIT_WORK(&m->rq, p9_पढ़ो_work);
	INIT_WORK(&m->wq, p9_ग_लिखो_work);
	INIT_LIST_HEAD(&m->poll_pending_link);
	init_poll_funcptr(&m->pt, p9_pollरुको);

	n = p9_fd_poll(client, &m->pt, शून्य);
	अगर (n & EPOLLIN) अणु
		p9_debug(P9_DEBUG_TRANS, "mux %p can read\n", m);
		set_bit(Rpending, &m->wsched);
	पूर्ण

	अगर (n & EPOLLOUT) अणु
		p9_debug(P9_DEBUG_TRANS, "mux %p can write\n", m);
		set_bit(Wpending, &m->wsched);
	पूर्ण
पूर्ण

/**
 * p9_poll_mux - polls a mux and schedules पढ़ो or ग_लिखो works अगर necessary
 * @m: connection to poll
 *
 */

अटल व्योम p9_poll_mux(काष्ठा p9_conn *m)
अणु
	__poll_t n;
	पूर्णांक err = -ECONNRESET;

	अगर (m->err < 0)
		वापस;

	n = p9_fd_poll(m->client, शून्य, &err);
	अगर (n & (EPOLLERR | EPOLLHUP | EPOLLNVAL)) अणु
		p9_debug(P9_DEBUG_TRANS, "error mux %p err %d\n", m, n);
		p9_conn_cancel(m, err);
	पूर्ण

	अगर (n & EPOLLIN) अणु
		set_bit(Rpending, &m->wsched);
		p9_debug(P9_DEBUG_TRANS, "mux %p can read\n", m);
		अगर (!test_and_set_bit(Rworksched, &m->wsched)) अणु
			p9_debug(P9_DEBUG_TRANS, "sched read work %p\n", m);
			schedule_work(&m->rq);
		पूर्ण
	पूर्ण

	अगर (n & EPOLLOUT) अणु
		set_bit(Wpending, &m->wsched);
		p9_debug(P9_DEBUG_TRANS, "mux %p can write\n", m);
		अगर ((m->wsize || !list_empty(&m->unsent_req_list)) &&
		    !test_and_set_bit(Wworksched, &m->wsched)) अणु
			p9_debug(P9_DEBUG_TRANS, "sched write work %p\n", m);
			schedule_work(&m->wq);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * p9_fd_request - send 9P request
 * The function can sleep until the request is scheduled क्रम sending.
 * The function can be पूर्णांकerrupted. Return from the function is not
 * a guarantee that the request is sent successfully.
 *
 * @client: client instance
 * @req: request to be sent
 *
 */

अटल पूर्णांक p9_fd_request(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	__poll_t n;
	काष्ठा p9_trans_fd *ts = client->trans;
	काष्ठा p9_conn *m = &ts->conn;

	p9_debug(P9_DEBUG_TRANS, "mux %p task %p tcall %p id %d\n",
		 m, current, &req->tc, req->tc.id);
	अगर (m->err < 0)
		वापस m->err;

	spin_lock(&client->lock);
	req->status = REQ_STATUS_UNSENT;
	list_add_tail(&req->req_list, &m->unsent_req_list);
	spin_unlock(&client->lock);

	अगर (test_and_clear_bit(Wpending, &m->wsched))
		n = EPOLLOUT;
	अन्यथा
		n = p9_fd_poll(m->client, शून्य, शून्य);

	अगर (n & EPOLLOUT && !test_and_set_bit(Wworksched, &m->wsched))
		schedule_work(&m->wq);

	वापस 0;
पूर्ण

अटल पूर्णांक p9_fd_cancel(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	पूर्णांक ret = 1;

	p9_debug(P9_DEBUG_TRANS, "client %p req %p\n", client, req);

	spin_lock(&client->lock);

	अगर (req->status == REQ_STATUS_UNSENT) अणु
		list_del(&req->req_list);
		req->status = REQ_STATUS_FLSHD;
		p9_req_put(req);
		ret = 0;
	पूर्ण
	spin_unlock(&client->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक p9_fd_cancelled(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	p9_debug(P9_DEBUG_TRANS, "client %p req %p\n", client, req);

	spin_lock(&client->lock);
	/* Ignore cancelled request अगर message has been received
	 * beक्रमe lock.
	 */
	अगर (req->status == REQ_STATUS_RCVD) अणु
		spin_unlock(&client->lock);
		वापस 0;
	पूर्ण

	/* we haven't received a response क्रम oldreq,
	 * हटाओ it from the list.
	 */
	list_del(&req->req_list);
	req->status = REQ_STATUS_FLSHD;
	spin_unlock(&client->lock);
	p9_req_put(req);

	वापस 0;
पूर्ण

अटल पूर्णांक p9_fd_show_options(काष्ठा seq_file *m, काष्ठा p9_client *clnt)
अणु
	अगर (clnt->trans_mod == &p9_tcp_trans) अणु
		अगर (clnt->trans_opts.tcp.port != P9_PORT)
			seq_म_लिखो(m, ",port=%u", clnt->trans_opts.tcp.port);
	पूर्ण अन्यथा अगर (clnt->trans_mod == &p9_fd_trans) अणु
		अगर (clnt->trans_opts.fd.rfd != ~0)
			seq_म_लिखो(m, ",rfd=%u", clnt->trans_opts.fd.rfd);
		अगर (clnt->trans_opts.fd.wfd != ~0)
			seq_म_लिखो(m, ",wfd=%u", clnt->trans_opts.fd.wfd);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * parse_opts - parse mount options पूर्णांकo p9_fd_opts काष्ठाure
 * @params: options string passed from mount
 * @opts: fd transport-specअगरic काष्ठाure to parse options पूर्णांकo
 *
 * Returns 0 upon success, -ERRNO upon failure
 */

अटल पूर्णांक parse_opts(अक्षर *params, काष्ठा p9_fd_opts *opts)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	अक्षर *options, *पंचांगp_options;

	opts->port = P9_PORT;
	opts->rfd = ~0;
	opts->wfd = ~0;
	opts->privport = false;

	अगर (!params)
		वापस 0;

	पंचांगp_options = kstrdup(params, GFP_KERNEL);
	अगर (!पंचांगp_options) अणु
		p9_debug(P9_DEBUG_ERROR,
			 "failed to allocate copy of option string\n");
		वापस -ENOMEM;
	पूर्ण
	options = पंचांगp_options;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;
		पूर्णांक r;
		अगर (!*p)
			जारी;
		token = match_token(p, tokens, args);
		अगर ((token != Opt_err) && (token != Opt_privport)) अणु
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				जारी;
			पूर्ण
		पूर्ण
		चयन (token) अणु
		हाल Opt_port:
			opts->port = option;
			अवरोध;
		हाल Opt_rfdno:
			opts->rfd = option;
			अवरोध;
		हाल Opt_wfdno:
			opts->wfd = option;
			अवरोध;
		हाल Opt_privport:
			opts->privport = true;
			अवरोध;
		शेष:
			जारी;
		पूर्ण
	पूर्ण

	kमुक्त(पंचांगp_options);
	वापस 0;
पूर्ण

अटल पूर्णांक p9_fd_खोलो(काष्ठा p9_client *client, पूर्णांक rfd, पूर्णांक wfd)
अणु
	काष्ठा p9_trans_fd *ts = kzalloc(माप(काष्ठा p9_trans_fd),
					   GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->rd = fget(rfd);
	अगर (!ts->rd)
		जाओ out_मुक्त_ts;
	अगर (!(ts->rd->f_mode & FMODE_READ))
		जाओ out_put_rd;
	ts->wr = fget(wfd);
	अगर (!ts->wr)
		जाओ out_put_rd;
	अगर (!(ts->wr->f_mode & FMODE_WRITE))
		जाओ out_put_wr;

	client->trans = ts;
	client->status = Connected;

	वापस 0;

out_put_wr:
	fput(ts->wr);
out_put_rd:
	fput(ts->rd);
out_मुक्त_ts:
	kमुक्त(ts);
	वापस -EIO;
पूर्ण

अटल पूर्णांक p9_socket_खोलो(काष्ठा p9_client *client, काष्ठा socket *csocket)
अणु
	काष्ठा p9_trans_fd *p;
	काष्ठा file *file;

	p = kzalloc(माप(काष्ठा p9_trans_fd), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	csocket->sk->sk_allocation = GFP_NOIO;
	file = sock_alloc_file(csocket, 0, शून्य);
	अगर (IS_ERR(file)) अणु
		pr_err("%s (%d): failed to map fd\n",
		       __func__, task_pid_nr(current));
		kमुक्त(p);
		वापस PTR_ERR(file);
	पूर्ण

	get_file(file);
	p->wr = p->rd = file;
	client->trans = p;
	client->status = Connected;

	p->rd->f_flags |= O_NONBLOCK;

	p9_conn_create(client);
	वापस 0;
पूर्ण

/**
 * p9_conn_destroy - cancels all pending requests of mux
 * @m: mux to destroy
 *
 */

अटल व्योम p9_conn_destroy(काष्ठा p9_conn *m)
अणु
	p9_debug(P9_DEBUG_TRANS, "mux %p prev %p next %p\n",
		 m, m->mux_list.prev, m->mux_list.next);

	p9_mux_poll_stop(m);
	cancel_work_sync(&m->rq);
	अगर (m->rreq) अणु
		p9_req_put(m->rreq);
		m->rreq = शून्य;
	पूर्ण
	cancel_work_sync(&m->wq);
	अगर (m->wreq) अणु
		p9_req_put(m->wreq);
		m->wreq = शून्य;
	पूर्ण

	p9_conn_cancel(m, -ECONNRESET);

	m->client = शून्य;
पूर्ण

/**
 * p9_fd_बंद - shutकरोwn file descriptor transport
 * @client: client instance
 *
 */

अटल व्योम p9_fd_बंद(काष्ठा p9_client *client)
अणु
	काष्ठा p9_trans_fd *ts;

	अगर (!client)
		वापस;

	ts = client->trans;
	अगर (!ts)
		वापस;

	client->status = Disconnected;

	p9_conn_destroy(&ts->conn);

	अगर (ts->rd)
		fput(ts->rd);
	अगर (ts->wr)
		fput(ts->wr);

	kमुक्त(ts);
पूर्ण

/*
 * stolen from NFS - maybe should be made a generic function?
 */
अटल अंतरभूत पूर्णांक valid_ipaddr4(स्थिर अक्षर *buf)
अणु
	पूर्णांक rc, count, in[4];

	rc = माला_पूछो(buf, "%d.%d.%d.%d", &in[0], &in[1], &in[2], &in[3]);
	अगर (rc != 4)
		वापस -EINVAL;
	क्रम (count = 0; count < 4; count++) अणु
		अगर (in[count] > 255)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक p9_bind_privport(काष्ठा socket *sock)
अणु
	काष्ठा sockaddr_in cl;
	पूर्णांक port, err = -EINVAL;

	स_रखो(&cl, 0, माप(cl));
	cl.sin_family = AF_INET;
	cl.sin_addr.s_addr = htonl(INADDR_ANY);
	क्रम (port = p9_ipport_resv_max; port >= p9_ipport_resv_min; port--) अणु
		cl.sin_port = htons((uलघु)port);
		err = kernel_bind(sock, (काष्ठा sockaddr *)&cl, माप(cl));
		अगर (err != -EADDRINUSE)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण


अटल पूर्णांक
p9_fd_create_tcp(काष्ठा p9_client *client, स्थिर अक्षर *addr, अक्षर *args)
अणु
	पूर्णांक err;
	काष्ठा socket *csocket;
	काष्ठा sockaddr_in sin_server;
	काष्ठा p9_fd_opts opts;

	err = parse_opts(args, &opts);
	अगर (err < 0)
		वापस err;

	अगर (addr == शून्य || valid_ipaddr4(addr) < 0)
		वापस -EINVAL;

	csocket = शून्य;

	client->trans_opts.tcp.port = opts.port;
	client->trans_opts.tcp.privport = opts.privport;
	sin_server.sin_family = AF_INET;
	sin_server.sin_addr.s_addr = in_aton(addr);
	sin_server.sin_port = htons(opts.port);
	err = __sock_create(current->nsproxy->net_ns, PF_INET,
			    SOCK_STREAM, IPPROTO_TCP, &csocket, 1);
	अगर (err) अणु
		pr_err("%s (%d): problem creating socket\n",
		       __func__, task_pid_nr(current));
		वापस err;
	पूर्ण

	अगर (opts.privport) अणु
		err = p9_bind_privport(csocket);
		अगर (err < 0) अणु
			pr_err("%s (%d): problem binding to privport\n",
			       __func__, task_pid_nr(current));
			sock_release(csocket);
			वापस err;
		पूर्ण
	पूर्ण

	err = csocket->ops->connect(csocket,
				    (काष्ठा sockaddr *)&sin_server,
				    माप(काष्ठा sockaddr_in), 0);
	अगर (err < 0) अणु
		pr_err("%s (%d): problem connecting socket to %s\n",
		       __func__, task_pid_nr(current), addr);
		sock_release(csocket);
		वापस err;
	पूर्ण

	वापस p9_socket_खोलो(client, csocket);
पूर्ण

अटल पूर्णांक
p9_fd_create_unix(काष्ठा p9_client *client, स्थिर अक्षर *addr, अक्षर *args)
अणु
	पूर्णांक err;
	काष्ठा socket *csocket;
	काष्ठा sockaddr_un sun_server;

	csocket = शून्य;

	अगर (!addr || !म_माप(addr))
		वापस -EINVAL;

	अगर (म_माप(addr) >= UNIX_PATH_MAX) अणु
		pr_err("%s (%d): address too long: %s\n",
		       __func__, task_pid_nr(current), addr);
		वापस -ENAMETOOLONG;
	पूर्ण

	sun_server.sun_family = PF_UNIX;
	म_नकल(sun_server.sun_path, addr);
	err = __sock_create(current->nsproxy->net_ns, PF_UNIX,
			    SOCK_STREAM, 0, &csocket, 1);
	अगर (err < 0) अणु
		pr_err("%s (%d): problem creating socket\n",
		       __func__, task_pid_nr(current));

		वापस err;
	पूर्ण
	err = csocket->ops->connect(csocket, (काष्ठा sockaddr *)&sun_server,
			माप(काष्ठा sockaddr_un) - 1, 0);
	अगर (err < 0) अणु
		pr_err("%s (%d): problem connecting socket: %s: %d\n",
		       __func__, task_pid_nr(current), addr, err);
		sock_release(csocket);
		वापस err;
	पूर्ण

	वापस p9_socket_खोलो(client, csocket);
पूर्ण

अटल पूर्णांक
p9_fd_create(काष्ठा p9_client *client, स्थिर अक्षर *addr, अक्षर *args)
अणु
	पूर्णांक err;
	काष्ठा p9_fd_opts opts;

	parse_opts(args, &opts);
	client->trans_opts.fd.rfd = opts.rfd;
	client->trans_opts.fd.wfd = opts.wfd;

	अगर (opts.rfd == ~0 || opts.wfd == ~0) अणु
		pr_err("Insufficient options for proto=fd\n");
		वापस -ENOPROTOOPT;
	पूर्ण

	err = p9_fd_खोलो(client, opts.rfd, opts.wfd);
	अगर (err < 0)
		वापस err;

	p9_conn_create(client);

	वापस 0;
पूर्ण

अटल काष्ठा p9_trans_module p9_tcp_trans = अणु
	.name = "tcp",
	.maxsize = MAX_SOCK_BUF,
	.def = 0,
	.create = p9_fd_create_tcp,
	.बंद = p9_fd_बंद,
	.request = p9_fd_request,
	.cancel = p9_fd_cancel,
	.cancelled = p9_fd_cancelled,
	.show_options = p9_fd_show_options,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा p9_trans_module p9_unix_trans = अणु
	.name = "unix",
	.maxsize = MAX_SOCK_BUF,
	.def = 0,
	.create = p9_fd_create_unix,
	.बंद = p9_fd_बंद,
	.request = p9_fd_request,
	.cancel = p9_fd_cancel,
	.cancelled = p9_fd_cancelled,
	.show_options = p9_fd_show_options,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा p9_trans_module p9_fd_trans = अणु
	.name = "fd",
	.maxsize = MAX_SOCK_BUF,
	.def = 0,
	.create = p9_fd_create,
	.बंद = p9_fd_बंद,
	.request = p9_fd_request,
	.cancel = p9_fd_cancel,
	.cancelled = p9_fd_cancelled,
	.show_options = p9_fd_show_options,
	.owner = THIS_MODULE,
पूर्ण;

/**
 * p9_poll_workfn - poll worker thपढ़ो
 * @work: work queue
 *
 * polls all v9fs transports क्रम new events and queues the appropriate
 * work to the work queue
 *
 */

अटल व्योम p9_poll_workfn(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;

	p9_debug(P9_DEBUG_TRANS, "start %p\n", current);

	spin_lock_irqsave(&p9_poll_lock, flags);
	जबतक (!list_empty(&p9_poll_pending_list)) अणु
		काष्ठा p9_conn *conn = list_first_entry(&p9_poll_pending_list,
							काष्ठा p9_conn,
							poll_pending_link);
		list_del_init(&conn->poll_pending_link);
		spin_unlock_irqrestore(&p9_poll_lock, flags);

		p9_poll_mux(conn);

		spin_lock_irqsave(&p9_poll_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&p9_poll_lock, flags);

	p9_debug(P9_DEBUG_TRANS, "finish\n");
पूर्ण

पूर्णांक p9_trans_fd_init(व्योम)
अणु
	v9fs_रेजिस्टर_trans(&p9_tcp_trans);
	v9fs_रेजिस्टर_trans(&p9_unix_trans);
	v9fs_रेजिस्टर_trans(&p9_fd_trans);

	वापस 0;
पूर्ण

व्योम p9_trans_fd_निकास(व्योम)
अणु
	flush_work(&p9_poll_work);
	v9fs_unरेजिस्टर_trans(&p9_tcp_trans);
	v9fs_unरेजिस्टर_trans(&p9_unix_trans);
	v9fs_unरेजिस्टर_trans(&p9_fd_trans);
पूर्ण
