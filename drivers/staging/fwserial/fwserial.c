<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FireWire Serial driver
 *
 * Copyright (C) 2012 Peter Hurley <peter@hurleysoftware.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/rculist.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/bug.h>
#समावेश <linux/uaccess.h>

#समावेश "fwserial.h"

अंतरभूत u64 be32_to_u64(__be32 hi, __be32 lo)
अणु
	वापस ((u64)be32_to_cpu(hi) << 32 | be32_to_cpu(lo));
पूर्ण

#घोषणा LINUX_VENDOR_ID   0xd00d1eU  /* same id used in card root directory   */
#घोषणा FWSERIAL_VERSION  0x00e81cU  /* must be unique within LINUX_VENDOR_ID */

/* configurable options */
अटल पूर्णांक num_ttys = 4;	    /* # of std ttys to create per fw_card    */
				    /* - द्विगुनs as loopback port index       */
अटल bool स्वतः_connect = true;    /* try to VIRT_CABLE to every peer        */
अटल bool create_loop_dev = true; /* create a loopback device क्रम each card */

module_param_named(ttys, num_ttys, पूर्णांक, 0644);
module_param_named(स्वतः, स्वतः_connect, bool, 0644);
module_param_named(loop, create_loop_dev, bool, 0644);

/*
 * Threshold below which the tty is woken क्रम writing
 * - should be equal to WAKEUP_CHARS in drivers/tty/n_tty.c because
 *   even अगर the ग_लिखोr is woken, n_tty_poll() won't set EPOLLOUT until
 *   our fअगरo is below this level
 */
#घोषणा WAKEUP_CHARS             256

/**
 * fwserial_list: list of every fw_serial created क्रम each fw_card
 * See discussion in fwserial_probe.
 */
अटल LIST_HEAD(fwserial_list);
अटल DEFINE_MUTEX(fwserial_list_mutex);

/**
 * port_table: array of tty ports allocated to each fw_card
 *
 * tty ports are allocated during probe when an fw_serial is first
 * created क्रम a given fw_card. Ports are allocated in a contiguous block,
 * each block consisting of 'num_ports' ports.
 */
अटल काष्ठा fwtty_port *port_table[MAX_TOTAL_PORTS];
अटल DEFINE_MUTEX(port_table_lock);
अटल bool port_table_corrupt;
#घोषणा FWTTY_INVALID_INDEX  MAX_TOTAL_PORTS

#घोषणा loop_idx(port)	(((port)->index) / num_ports)
#घोषणा table_idx(loop)	((loop) * num_ports + num_ttys)

/* total # of tty ports created per fw_card */
अटल पूर्णांक num_ports;

/* slab used as pool क्रम काष्ठा fwtty_transactions */
अटल काष्ठा kmem_cache *fwtty_txn_cache;

काष्ठा tty_driver *fwtty_driver;
अटल काष्ठा tty_driver *fwloop_driver;

अटल काष्ठा dentry *fwserial_debugfs;

काष्ठा fwtty_transaction;
प्रकार व्योम (*fwtty_transaction_cb)(काष्ठा fw_card *card, पूर्णांक rcode,
				     व्योम *data, माप_प्रकार length,
				     काष्ठा fwtty_transaction *txn);

काष्ठा fwtty_transaction अणु
	काष्ठा fw_transaction      fw_txn;
	fwtty_transaction_cb       callback;
	काष्ठा fwtty_port	   *port;
	जोड़ अणु
		काष्ठा dma_pending dma_pended;
	पूर्ण;
पूर्ण;

#घोषणा to_device(a, b)			(a->b)
#घोषणा fwtty_err(p, fmt, ...)						\
	dev_err(to_device(p, device), fmt, ##__VA_ARGS__)
#घोषणा fwtty_info(p, fmt, ...)						\
	dev_info(to_device(p, device), fmt, ##__VA_ARGS__)
#घोषणा fwtty_notice(p, fmt, ...)					\
	dev_notice(to_device(p, device), fmt, ##__VA_ARGS__)
#घोषणा fwtty_dbg(p, fmt, ...)						\
	dev_dbg(to_device(p, device), "%s: " fmt, __func__, ##__VA_ARGS__)
#घोषणा fwtty_err_ratelimited(p, fmt, ...)				\
	dev_err_ratelimited(to_device(p, device), fmt, ##__VA_ARGS__)

#अगर_घोषित DEBUG
अटल अंतरभूत व्योम debug_लघु_ग_लिखो(काष्ठा fwtty_port *port, पूर्णांक c, पूर्णांक n)
अणु
	पूर्णांक avail;

	अगर (n < c) अणु
		spin_lock_bh(&port->lock);
		avail = dma_fअगरo_avail(&port->tx_fअगरo);
		spin_unlock_bh(&port->lock);
		fwtty_dbg(port, "short write: avail:%d req:%d wrote:%d\n",
			  avail, c, n);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा debug_लघु_ग_लिखो(port, c, n)
#पूर्ण_अगर

अटल काष्ठा fwtty_peer *__fwserial_peer_by_node_id(काष्ठा fw_card *card,
						     पूर्णांक generation, पूर्णांक id);

#अगर_घोषित FWTTY_PROFILING

अटल व्योम fwtty_profile_fअगरo(काष्ठा fwtty_port *port, अचिन्हित पूर्णांक *stat)
अणु
	spin_lock_bh(&port->lock);
	fwtty_profile_data(stat, dma_fअगरo_avail(&port->tx_fअगरo));
	spin_unlock_bh(&port->lock);
पूर्ण

अटल व्योम fwtty_dump_profile(काष्ठा seq_file *m, काष्ठा stats *stats)
अणु
	/* क्रम each stat, prपूर्णांक sum of 0 to 2^k, then inभागidually */
	पूर्णांक k = 4;
	अचिन्हित पूर्णांक sum;
	पूर्णांक j;
	अक्षर t[10];

	snम_लिखो(t, 10, "< %d", 1 << k);
	seq_म_लिखो(m, "\n%14s  %6s", " ", t);
	क्रम (j = k + 1; j < DISTRIBUTION_MAX_INDEX; ++j)
		seq_म_लिखो(m, "%6d", 1 << j);

	++k;
	क्रम (j = 0, sum = 0; j <= k; ++j)
		sum += stats->पढ़ोs[j];
	seq_म_लिखो(m, "\n%14s: %6d", "reads", sum);
	क्रम (j = k + 1; j <= DISTRIBUTION_MAX_INDEX; ++j)
		seq_म_लिखो(m, "%6d", stats->पढ़ोs[j]);

	क्रम (j = 0, sum = 0; j <= k; ++j)
		sum += stats->ग_लिखोs[j];
	seq_म_लिखो(m, "\n%14s: %6d", "writes", sum);
	क्रम (j = k + 1; j <= DISTRIBUTION_MAX_INDEX; ++j)
		seq_म_लिखो(m, "%6d", stats->ग_लिखोs[j]);

	क्रम (j = 0, sum = 0; j <= k; ++j)
		sum += stats->txns[j];
	seq_म_लिखो(m, "\n%14s: %6d", "txns", sum);
	क्रम (j = k + 1; j <= DISTRIBUTION_MAX_INDEX; ++j)
		seq_म_लिखो(m, "%6d", stats->txns[j]);

	क्रम (j = 0, sum = 0; j <= k; ++j)
		sum += stats->unthrottle[j];
	seq_म_लिखो(m, "\n%14s: %6d", "avail @ unthr", sum);
	क्रम (j = k + 1; j <= DISTRIBUTION_MAX_INDEX; ++j)
		seq_म_लिखो(m, "%6d", stats->unthrottle[j]);
पूर्ण

#अन्यथा
#घोषणा fwtty_profile_fअगरo(port, stat)
#घोषणा fwtty_dump_profile(m, stats)
#पूर्ण_अगर

/*
 * Returns the max receive packet size क्रम the given node
 * Devices which are OHCI v1.0/ v1.1/ v1.2-draft or RFC 2734 compliant
 * are required by specअगरication to support max_rec of 8 (512 bytes) or more.
 */
अटल अंतरभूत पूर्णांक device_max_receive(काष्ठा fw_device *fw_device)
अणु
	/* see IEEE 1394-2008 table 8-8 */
	वापस min(2 << fw_device->max_rec, 4096);
पूर्ण

अटल व्योम fwtty_log_tx_error(काष्ठा fwtty_port *port, पूर्णांक rcode)
अणु
	चयन (rcode) अणु
	हाल RCODE_SEND_ERROR:
		fwtty_err_ratelimited(port, "card busy\n");
		अवरोध;
	हाल RCODE_ADDRESS_ERROR:
		fwtty_err_ratelimited(port, "bad unit addr or write length\n");
		अवरोध;
	हाल RCODE_DATA_ERROR:
		fwtty_err_ratelimited(port, "failed rx\n");
		अवरोध;
	हाल RCODE_NO_ACK:
		fwtty_err_ratelimited(port, "missing ack\n");
		अवरोध;
	हाल RCODE_BUSY:
		fwtty_err_ratelimited(port, "remote busy\n");
		अवरोध;
	शेष:
		fwtty_err_ratelimited(port, "failed tx: %d\n", rcode);
	पूर्ण
पूर्ण

अटल व्योम fwtty_common_callback(काष्ठा fw_card *card, पूर्णांक rcode,
				  व्योम *payload, माप_प्रकार len, व्योम *cb_data)
अणु
	काष्ठा fwtty_transaction *txn = cb_data;
	काष्ठा fwtty_port *port = txn->port;

	अगर (port && rcode != RCODE_COMPLETE)
		fwtty_log_tx_error(port, rcode);
	अगर (txn->callback)
		txn->callback(card, rcode, payload, len, txn);
	kmem_cache_मुक्त(fwtty_txn_cache, txn);
पूर्ण

अटल पूर्णांक fwtty_send_data_async(काष्ठा fwtty_peer *peer, पूर्णांक tcode,
				 अचिन्हित दीर्घ दीर्घ addr, व्योम *payload,
				 माप_प्रकार len, fwtty_transaction_cb callback,
				 काष्ठा fwtty_port *port)
अणु
	काष्ठा fwtty_transaction *txn;
	पूर्णांक generation;

	txn = kmem_cache_alloc(fwtty_txn_cache, GFP_ATOMIC);
	अगर (!txn)
		वापस -ENOMEM;

	txn->callback = callback;
	txn->port = port;

	generation = peer->generation;
	smp_rmb();
	fw_send_request(peer->serial->card, &txn->fw_txn, tcode,
			peer->node_id, generation, peer->speed, addr, payload,
			len, fwtty_common_callback, txn);
	वापस 0;
पूर्ण

अटल व्योम fwtty_send_txn_async(काष्ठा fwtty_peer *peer,
				 काष्ठा fwtty_transaction *txn, पूर्णांक tcode,
				 अचिन्हित दीर्घ दीर्घ addr, व्योम *payload,
				 माप_प्रकार len, fwtty_transaction_cb callback,
				 काष्ठा fwtty_port *port)
अणु
	पूर्णांक generation;

	txn->callback = callback;
	txn->port = port;

	generation = peer->generation;
	smp_rmb();
	fw_send_request(peer->serial->card, &txn->fw_txn, tcode,
			peer->node_id, generation, peer->speed, addr, payload,
			len, fwtty_common_callback, txn);
पूर्ण

अटल व्योम __fwtty_restart_tx(काष्ठा fwtty_port *port)
अणु
	पूर्णांक len, avail;

	len = dma_fअगरo_out_level(&port->tx_fअगरo);
	अगर (len)
		schedule_delayed_work(&port->drain, 0);
	avail = dma_fअगरo_avail(&port->tx_fअगरo);

	fwtty_dbg(port, "fifo len: %d avail: %d\n", len, avail);
पूर्ण

अटल व्योम fwtty_restart_tx(काष्ठा fwtty_port *port)
अणु
	spin_lock_bh(&port->lock);
	__fwtty_restart_tx(port);
	spin_unlock_bh(&port->lock);
पूर्ण

/**
 * fwtty_update_port_status - decodes & dispatches line status changes
 *
 * Note: in loopback, the port->lock is being held. Only use functions that
 * करोn't attempt to reclaim the port->lock.
 */
अटल व्योम fwtty_update_port_status(काष्ठा fwtty_port *port,
				     अचिन्हित पूर्णांक status)
अणु
	अचिन्हित पूर्णांक delta;
	काष्ठा tty_काष्ठा *tty;

	/* simulated LSR/MSR status from remote */
	status &= ~MCTRL_MASK;
	delta = (port->mstatus ^ status) & ~MCTRL_MASK;
	delta &= ~(status & TIOCM_RNG);
	port->mstatus = status;

	अगर (delta & TIOCM_RNG)
		++port->icount.rng;
	अगर (delta & TIOCM_DSR)
		++port->icount.dsr;
	अगर (delta & TIOCM_CAR)
		++port->icount.dcd;
	अगर (delta & TIOCM_CTS)
		++port->icount.cts;

	fwtty_dbg(port, "status: %x delta: %x\n", status, delta);

	अगर (delta & TIOCM_CAR) अणु
		tty = tty_port_tty_get(&port->port);
		अगर (tty && !C_CLOCAL(tty)) अणु
			अगर (status & TIOCM_CAR)
				wake_up_पूर्णांकerruptible(&port->port.खोलो_रुको);
			अन्यथा
				schedule_work(&port->hangup);
		पूर्ण
		tty_kref_put(tty);
	पूर्ण

	अगर (delta & TIOCM_CTS) अणु
		tty = tty_port_tty_get(&port->port);
		अगर (tty && C_CRTSCTS(tty)) अणु
			अगर (tty->hw_stopped) अणु
				अगर (status & TIOCM_CTS) अणु
					tty->hw_stopped = 0;
					अगर (port->loopback)
						__fwtty_restart_tx(port);
					अन्यथा
						fwtty_restart_tx(port);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (~status & TIOCM_CTS)
					tty->hw_stopped = 1;
			पूर्ण
		पूर्ण
		tty_kref_put(tty);

	पूर्ण अन्यथा अगर (delta & OOB_TX_THROTTLE) अणु
		tty = tty_port_tty_get(&port->port);
		अगर (tty) अणु
			अगर (tty->hw_stopped) अणु
				अगर (~status & OOB_TX_THROTTLE) अणु
					tty->hw_stopped = 0;
					अगर (port->loopback)
						__fwtty_restart_tx(port);
					अन्यथा
						fwtty_restart_tx(port);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (status & OOB_TX_THROTTLE)
					tty->hw_stopped = 1;
			पूर्ण
		पूर्ण
		tty_kref_put(tty);
	पूर्ण

	अगर (delta & (UART_LSR_BI << 24)) अणु
		अगर (status & (UART_LSR_BI << 24)) अणु
			port->अवरोध_last = jअगरfies;
			schedule_delayed_work(&port->emit_अवरोधs, 0);
		पूर्ण अन्यथा अणु
			/* run emit_अवरोधs one last समय (अगर pending) */
			mod_delayed_work(प्रणाली_wq, &port->emit_अवरोधs, 0);
		पूर्ण
	पूर्ण

	अगर (delta & (TIOCM_DSR | TIOCM_CAR | TIOCM_CTS | TIOCM_RNG))
		wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
पूर्ण

/**
 * __fwtty_port_line_status - generate 'line status' क्रम indicated port
 *
 * This function वापसs a remote 'MSR' state based on the local 'MCR' state,
 * as अगर a null modem cable was attached. The actual status is a mangling
 * of TIOCM_* bits suitable क्रम sending to a peer's status_addr.
 *
 * Note: caller must be holding port lock
 */
अटल अचिन्हित पूर्णांक __fwtty_port_line_status(काष्ठा fwtty_port *port)
अणु
	अचिन्हित पूर्णांक status = 0;

	/* TODO: add module param to tie RNG to DTR as well */

	अगर (port->mctrl & TIOCM_DTR)
		status |= TIOCM_DSR | TIOCM_CAR;
	अगर (port->mctrl & TIOCM_RTS)
		status |= TIOCM_CTS;
	अगर (port->mctrl & OOB_RX_THROTTLE)
		status |= OOB_TX_THROTTLE;
	/* emulate BRK as add'l line status */
	अगर (port->अवरोध_ctl)
		status |= UART_LSR_BI << 24;

	वापस status;
पूर्ण

/**
 * __fwtty_ग_लिखो_port_status - send the port line status to peer
 *
 * Note: caller must be holding the port lock.
 */
अटल पूर्णांक __fwtty_ग_लिखो_port_status(काष्ठा fwtty_port *port)
अणु
	काष्ठा fwtty_peer *peer;
	पूर्णांक err = -ENOENT;
	अचिन्हित पूर्णांक status = __fwtty_port_line_status(port);

	rcu_पढ़ो_lock();
	peer = rcu_dereference(port->peer);
	अगर (peer) अणु
		err = fwtty_send_data_async(peer, TCODE_WRITE_QUADLET_REQUEST,
					    peer->status_addr, &status,
					    माप(status), शून्य, port);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

/**
 * fwtty_ग_लिखो_port_status - same as above but locked by port lock
 */
अटल पूर्णांक fwtty_ग_लिखो_port_status(काष्ठा fwtty_port *port)
अणु
	पूर्णांक err;

	spin_lock_bh(&port->lock);
	err = __fwtty_ग_लिखो_port_status(port);
	spin_unlock_bh(&port->lock);
	वापस err;
पूर्ण

अटल व्योम fwtty_throttle_port(काष्ठा fwtty_port *port)
अणु
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित पूर्णांक old;

	tty = tty_port_tty_get(&port->port);
	अगर (!tty)
		वापस;

	spin_lock_bh(&port->lock);

	old = port->mctrl;
	port->mctrl |= OOB_RX_THROTTLE;
	अगर (C_CRTSCTS(tty))
		port->mctrl &= ~TIOCM_RTS;
	अगर (~old & OOB_RX_THROTTLE)
		__fwtty_ग_लिखो_port_status(port);

	spin_unlock_bh(&port->lock);

	tty_kref_put(tty);
पूर्ण

/**
 * fwtty_करो_hangup - रुको क्रम ldisc to deliver all pending rx; only then hangup
 *
 * When the remote has finished tx, and all in-flight rx has been received and
 * pushed to the flip buffer, the remote may बंद its device. This will
 * drop DTR on the remote which will drop carrier here. Typically, the tty is
 * hung up when carrier is dropped or lost.
 *
 * However, there is a race between the hang up and the line discipline
 * delivering its data to the पढ़ोer. A hangup will cause the ldisc to flush
 * (ie., clear) the पढ़ो buffer and flip buffer. Because of firewire's
 * relatively high throughput, the ldisc frequently lags well behind the driver,
 * resulting in lost data (which has alपढ़ोy been received and written to
 * the flip buffer) when the remote बंदs its end.
 *
 * Unक्रमtunately, since the flip buffer offers no direct method क्रम determining
 * अगर it holds data, ensuring the ldisc has delivered all data is problematic.
 */

/* FIXME: drop this workaround when __tty_hangup रुकोs क्रम ldisc completion */
अटल व्योम fwtty_करो_hangup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fwtty_port *port = to_port(work, hangup);
	काष्ठा tty_काष्ठा *tty;

	schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(50));

	tty = tty_port_tty_get(&port->port);
	अगर (tty)
		tty_vhangup(tty);
	tty_kref_put(tty);
पूर्ण

अटल व्योम fwtty_emit_अवरोधs(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fwtty_port *port = to_port(to_delayed_work(work), emit_अवरोधs);
	अटल स्थिर अक्षर buf[16];
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ elapsed = now - port->अवरोध_last;
	पूर्णांक n, t, c, brk = 0;

	/* generate अवरोधs at the line rate (but at least 1) */
	n = (elapsed * port->cps) / HZ + 1;
	port->अवरोध_last = now;

	fwtty_dbg(port, "sending %d brks\n", n);

	जबतक (n) अणु
		t = min(n, 16);
		c = tty_insert_flip_string_fixed_flag(&port->port, buf,
						      TTY_BREAK, t);
		n -= c;
		brk += c;
		अगर (c < t)
			अवरोध;
	पूर्ण
	tty_flip_buffer_push(&port->port);

	अगर (port->mstatus & (UART_LSR_BI << 24))
		schedule_delayed_work(&port->emit_अवरोधs, FREQ_BREAKS);
	port->icount.brk += brk;
पूर्ण

अटल पूर्णांक fwtty_rx(काष्ठा fwtty_port *port, अचिन्हित अक्षर *data, माप_प्रकार len)
अणु
	पूर्णांक c, n = len;
	अचिन्हित पूर्णांक lsr;
	पूर्णांक err = 0;

	fwtty_dbg(port, "%d\n", n);
	fwtty_profile_data(port->stats.पढ़ोs, n);

	अगर (port->ग_लिखो_only) अणु
		n = 0;
		जाओ out;
	पूर्ण

	/* disregard अवरोध status; अवरोधs are generated by emit_अवरोधs work */
	lsr = (port->mstatus >> 24) & ~UART_LSR_BI;

	अगर (port->overrun)
		lsr |= UART_LSR_OE;

	अगर (lsr & UART_LSR_OE)
		++port->icount.overrun;

	lsr &= port->status_mask;
	अगर (lsr & ~port->ignore_mask & UART_LSR_OE) अणु
		अगर (!tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN)) अणु
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
	port->overrun = false;

	अगर (lsr & port->ignore_mask & ~UART_LSR_OE) अणु
		/* TODO: करोn't drop SAK and Magic SysRq here */
		n = 0;
		जाओ out;
	पूर्ण

	c = tty_insert_flip_string_fixed_flag(&port->port, data, TTY_NORMAL, n);
	अगर (c > 0)
		tty_flip_buffer_push(&port->port);
	n -= c;

	अगर (n) अणु
		port->overrun = true;
		err = -EIO;
		fwtty_err_ratelimited(port, "flip buffer overrun\n");

	पूर्ण अन्यथा अणु
		/* throttle the sender अगर reमुख्यing flip buffer space has
		 * reached high watermark to aव्योम losing data which may be
		 * in-flight. Since the AR request context is 32k, that much
		 * data may have _alपढ़ोy_ been acked.
		 */
		अगर (tty_buffer_space_avail(&port->port) < HIGH_WATERMARK)
			fwtty_throttle_port(port);
	पूर्ण

out:
	port->icount.rx += len;
	port->stats.lost += n;
	वापस err;
पूर्ण

/**
 * fwtty_port_handler - bus address handler क्रम port पढ़ोs/ग_लिखोs
 * @parameters: fw_address_callback_t as specअगरied by firewire core पूर्णांकerface
 *
 * This handler is responsible क्रम handling inbound पढ़ो/ग_लिखो dma from remotes.
 */
अटल व्योम fwtty_port_handler(काष्ठा fw_card *card,
			       काष्ठा fw_request *request,
			       पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			       पूर्णांक generation,
			       अचिन्हित दीर्घ दीर्घ addr,
			       व्योम *data, माप_प्रकार len,
			       व्योम *callback_data)
अणु
	काष्ठा fwtty_port *port = callback_data;
	काष्ठा fwtty_peer *peer;
	पूर्णांक err;
	पूर्णांक rcode;

	/* Only accept rx from the peer भव-cabled to this port */
	rcu_पढ़ो_lock();
	peer = __fwserial_peer_by_node_id(card, generation, source);
	rcu_पढ़ो_unlock();
	अगर (!peer || peer != rcu_access_poपूर्णांकer(port->peer)) अणु
		rcode = RCODE_ADDRESS_ERROR;
		fwtty_err_ratelimited(port, "ignoring unauthenticated data\n");
		जाओ respond;
	पूर्ण

	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
		अगर (addr != port->rx_handler.offset || len != 4) अणु
			rcode = RCODE_ADDRESS_ERROR;
		पूर्ण अन्यथा अणु
			fwtty_update_port_status(port, *(अचिन्हित पूर्णांक *)data);
			rcode = RCODE_COMPLETE;
		पूर्ण
		अवरोध;

	हाल TCODE_WRITE_BLOCK_REQUEST:
		अगर (addr != port->rx_handler.offset + 4 ||
		    len > port->rx_handler.length - 4) अणु
			rcode = RCODE_ADDRESS_ERROR;
		पूर्ण अन्यथा अणु
			err = fwtty_rx(port, data, len);
			चयन (err) अणु
			हाल 0:
				rcode = RCODE_COMPLETE;
				अवरोध;
			हाल -EIO:
				rcode = RCODE_DATA_ERROR;
				अवरोध;
			शेष:
				rcode = RCODE_CONFLICT_ERROR;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		rcode = RCODE_TYPE_ERROR;
	पूर्ण

respond:
	fw_send_response(card, request, rcode);
पूर्ण

/**
 * fwtty_tx_complete - callback क्रम tx dma
 * @data: ignored, has no meaning क्रम ग_लिखो txns
 * @length: ignored, has no meaning क्रम ग_लिखो txns
 *
 * The ग_लिखोr must be woken here अगर the fअगरo has been emptied because it
 * may have slept अगर अक्षरs_in_buffer was != 0
 */
अटल व्योम fwtty_tx_complete(काष्ठा fw_card *card, पूर्णांक rcode,
			      व्योम *data, माप_प्रकार length,
			      काष्ठा fwtty_transaction *txn)
अणु
	काष्ठा fwtty_port *port = txn->port;
	पूर्णांक len;

	fwtty_dbg(port, "rcode: %d\n", rcode);

	चयन (rcode) अणु
	हाल RCODE_COMPLETE:
		spin_lock_bh(&port->lock);
		dma_fअगरo_out_complete(&port->tx_fअगरo, &txn->dma_pended);
		len = dma_fअगरo_level(&port->tx_fअगरo);
		spin_unlock_bh(&port->lock);

		port->icount.tx += txn->dma_pended.len;
		अवरोध;

	शेष:
		/* TODO: implement retries */
		spin_lock_bh(&port->lock);
		dma_fअगरo_out_complete(&port->tx_fअगरo, &txn->dma_pended);
		len = dma_fअगरo_level(&port->tx_fअगरo);
		spin_unlock_bh(&port->lock);

		port->stats.dropped += txn->dma_pended.len;
	पूर्ण

	अगर (len < WAKEUP_CHARS)
		tty_port_tty_wakeup(&port->port);
पूर्ण

अटल पूर्णांक fwtty_tx(काष्ठा fwtty_port *port, bool drain)
अणु
	काष्ठा fwtty_peer *peer;
	काष्ठा fwtty_transaction *txn;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक n, len;

	tty = tty_port_tty_get(&port->port);
	अगर (!tty)
		वापस -ENOENT;

	rcu_पढ़ो_lock();
	peer = rcu_dereference(port->peer);
	अगर (!peer) अणु
		n = -EIO;
		जाओ out;
	पूर्ण

	अगर (test_and_set_bit(IN_TX, &port->flags)) अणु
		n = -EALREADY;
		जाओ out;
	पूर्ण

	/* try to ग_लिखो as many dma transactions out as possible */
	n = -EAGAIN;
	जबतक (!tty->stopped && !tty->hw_stopped &&
	       !test_bit(STOP_TX, &port->flags)) अणु
		txn = kmem_cache_alloc(fwtty_txn_cache, GFP_ATOMIC);
		अगर (!txn) अणु
			n = -ENOMEM;
			अवरोध;
		पूर्ण

		spin_lock_bh(&port->lock);
		n = dma_fअगरo_out_pend(&port->tx_fअगरo, &txn->dma_pended);
		spin_unlock_bh(&port->lock);

		fwtty_dbg(port, "out: %u rem: %d\n", txn->dma_pended.len, n);

		अगर (n < 0) अणु
			kmem_cache_मुक्त(fwtty_txn_cache, txn);
			अगर (n == -EAGAIN) अणु
				++port->stats.tx_stall;
			पूर्ण अन्यथा अगर (n == -ENODATA) अणु
				fwtty_profile_data(port->stats.txns, 0);
			पूर्ण अन्यथा अणु
				++port->stats.fअगरo_errs;
				fwtty_err_ratelimited(port, "fifo err: %d\n",
						      n);
			पूर्ण
			अवरोध;
		पूर्ण

		fwtty_profile_data(port->stats.txns, txn->dma_pended.len);

		fwtty_send_txn_async(peer, txn, TCODE_WRITE_BLOCK_REQUEST,
				     peer->fअगरo_addr, txn->dma_pended.data,
				     txn->dma_pended.len, fwtty_tx_complete,
				     port);
		++port->stats.sent;

		/*
		 * Stop tx अगर the 'last view' of the fअगरo is empty or अगर
		 * this is the ग_लिखोr and there's not enough data to bother
		 */
		अगर (n == 0 || (!drain && n < WRITER_MINIMUM))
			अवरोध;
	पूर्ण

	अगर (n >= 0 || n == -EAGAIN || n == -ENOMEM || n == -ENODATA) अणु
		spin_lock_bh(&port->lock);
		len = dma_fअगरo_out_level(&port->tx_fअगरo);
		अगर (len) अणु
			अचिन्हित दीर्घ delay = (n == -ENOMEM) ? HZ : 1;

			schedule_delayed_work(&port->drain, delay);
		पूर्ण
		len = dma_fअगरo_level(&port->tx_fअगरo);
		spin_unlock_bh(&port->lock);

		/* wakeup the ग_लिखोr */
		अगर (drain && len < WAKEUP_CHARS)
			tty_wakeup(tty);
	पूर्ण

	clear_bit(IN_TX, &port->flags);
	wake_up_पूर्णांकerruptible(&port->रुको_tx);

out:
	rcu_पढ़ो_unlock();
	tty_kref_put(tty);
	वापस n;
पूर्ण

अटल व्योम fwtty_drain_tx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fwtty_port *port = to_port(to_delayed_work(work), drain);

	fwtty_tx(port, true);
पूर्ण

अटल व्योम fwtty_ग_लिखो_xअक्षर(काष्ठा fwtty_port *port, अक्षर ch)
अणु
	काष्ठा fwtty_peer *peer;

	++port->stats.xअक्षरs;

	fwtty_dbg(port, "%02x\n", ch);

	rcu_पढ़ो_lock();
	peer = rcu_dereference(port->peer);
	अगर (peer) अणु
		fwtty_send_data_async(peer, TCODE_WRITE_BLOCK_REQUEST,
				      peer->fअगरo_addr, &ch, माप(ch),
				      शून्य, port);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा fwtty_port *fwtty_port_get(अचिन्हित पूर्णांक index)
अणु
	काष्ठा fwtty_port *port;

	अगर (index >= MAX_TOTAL_PORTS)
		वापस शून्य;

	mutex_lock(&port_table_lock);
	port = port_table[index];
	अगर (port)
		kref_get(&port->serial->kref);
	mutex_unlock(&port_table_lock);
	वापस port;
पूर्ण

अटल पूर्णांक fwtty_ports_add(काष्ठा fw_serial *serial)
अणु
	पूर्णांक err = -EBUSY;
	पूर्णांक i, j;

	अगर (port_table_corrupt)
		वापस err;

	mutex_lock(&port_table_lock);
	क्रम (i = 0; i + num_ports <= MAX_TOTAL_PORTS; i += num_ports) अणु
		अगर (!port_table[i]) अणु
			क्रम (j = 0; j < num_ports; ++i, ++j) अणु
				serial->ports[j]->index = i;
				port_table[i] = serial->ports[j];
			पूर्ण
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&port_table_lock);
	वापस err;
पूर्ण

अटल व्योम fwserial_destroy(काष्ठा kref *kref)
अणु
	काष्ठा fw_serial *serial = to_serial(kref, kref);
	काष्ठा fwtty_port **ports = serial->ports;
	पूर्णांक j, i = ports[0]->index;

	synchronize_rcu();

	mutex_lock(&port_table_lock);
	क्रम (j = 0; j < num_ports; ++i, ++j) अणु
		port_table_corrupt |= port_table[i] != ports[j];
		WARN_ONCE(port_table_corrupt, "port_table[%d]: %p != ports[%d]: %p",
			  i, port_table[i], j, ports[j]);

		port_table[i] = शून्य;
	पूर्ण
	mutex_unlock(&port_table_lock);

	क्रम (j = 0; j < num_ports; ++j) अणु
		fw_core_हटाओ_address_handler(&ports[j]->rx_handler);
		tty_port_destroy(&ports[j]->port);
		kमुक्त(ports[j]);
	पूर्ण
	kमुक्त(serial);
पूर्ण

अटल व्योम fwtty_port_put(काष्ठा fwtty_port *port)
अणु
	kref_put(&port->serial->kref, fwserial_destroy);
पूर्ण

अटल व्योम fwtty_port_dtr_rts(काष्ठा tty_port *tty_port, पूर्णांक on)
अणु
	काष्ठा fwtty_port *port = to_port(tty_port, port);

	fwtty_dbg(port, "on/off: %d\n", on);

	spin_lock_bh(&port->lock);
	/* Don't change carrier state अगर this is a console */
	अगर (!port->port.console) अणु
		अगर (on)
			port->mctrl |= TIOCM_DTR | TIOCM_RTS;
		अन्यथा
			port->mctrl &= ~(TIOCM_DTR | TIOCM_RTS);
	पूर्ण

	__fwtty_ग_लिखो_port_status(port);
	spin_unlock_bh(&port->lock);
पूर्ण

/**
 * fwtty_port_carrier_उठाओd: required tty_port operation
 *
 * This port operation is polled after a tty has been खोलोed and is रुकोing क्रम
 * carrier detect -- see drivers/tty/tty_port:tty_port_block_til_पढ़ोy().
 */
अटल पूर्णांक fwtty_port_carrier_उठाओd(काष्ठा tty_port *tty_port)
अणु
	काष्ठा fwtty_port *port = to_port(tty_port, port);
	पूर्णांक rc;

	rc = (port->mstatus & TIOCM_CAR);

	fwtty_dbg(port, "%d\n", rc);

	वापस rc;
पूर्ण

अटल अचिन्हित पूर्णांक set_termios(काष्ठा fwtty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित पूर्णांक baud, frame;

	baud = tty_termios_baud_rate(&tty->termios);
	tty_termios_encode_baud_rate(&tty->termios, baud, baud);

	/* compute bit count of 2 frames */
	frame = 12 + ((C_CSTOPB(tty)) ? 4 : 2) + ((C_PARENB(tty)) ? 2 : 0);

	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
		frame -= (C_CSTOPB(tty)) ? 1 : 0;
		अवरोध;
	हाल CS6:
		frame += 2;
		अवरोध;
	हाल CS7:
		frame += 4;
		अवरोध;
	हाल CS8:
		frame += 6;
		अवरोध;
	पूर्ण

	port->cps = (baud << 1) / frame;

	port->status_mask = UART_LSR_OE;
	अगर (_I_FLAG(tty, BRKINT | PARMRK))
		port->status_mask |= UART_LSR_BI;

	port->ignore_mask = 0;
	अगर (I_IGNBRK(tty)) अणु
		port->ignore_mask |= UART_LSR_BI;
		अगर (I_IGNPAR(tty))
			port->ignore_mask |= UART_LSR_OE;
	पूर्ण

	port->ग_लिखो_only = !C_CREAD(tty);

	/* turn off echo and newline xlat अगर loopback */
	अगर (port->loopback) अणु
		tty->termios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHOKE |
					  ECHONL | ECHOPRT | ECHOCTL);
		tty->termios.c_oflag &= ~ONLCR;
	पूर्ण

	वापस baud;
पूर्ण

अटल पूर्णांक fwtty_port_activate(काष्ठा tty_port *tty_port,
			       काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = to_port(tty_port, port);
	अचिन्हित पूर्णांक baud;
	पूर्णांक err;

	set_bit(TTY_IO_ERROR, &tty->flags);

	err = dma_fअगरo_alloc(&port->tx_fअगरo, FWTTY_PORT_TXFIFO_LEN,
			     cache_line_size(),
			     port->max_payload,
			     FWTTY_PORT_MAX_PEND_DMA,
			     GFP_KERNEL);
	अगर (err)
		वापस err;

	spin_lock_bh(&port->lock);

	baud = set_termios(port, tty);

	/* अगर console, करोn't change carrier state */
	अगर (!port->port.console) अणु
		port->mctrl = 0;
		अगर (baud != 0)
			port->mctrl = TIOCM_DTR | TIOCM_RTS;
	पूर्ण

	अगर (C_CRTSCTS(tty) && ~port->mstatus & TIOCM_CTS)
		tty->hw_stopped = 1;

	__fwtty_ग_लिखो_port_status(port);
	spin_unlock_bh(&port->lock);

	clear_bit(TTY_IO_ERROR, &tty->flags);

	वापस 0;
पूर्ण

/**
 * fwtty_port_shutकरोwn
 *
 * Note: the tty port core ensures this is not the console and
 * manages TTY_IO_ERROR properly
 */
अटल व्योम fwtty_port_shutकरोwn(काष्ठा tty_port *tty_port)
अणु
	काष्ठा fwtty_port *port = to_port(tty_port, port);

	/* TODO: cancel outstanding transactions */

	cancel_delayed_work_sync(&port->emit_अवरोधs);
	cancel_delayed_work_sync(&port->drain);

	spin_lock_bh(&port->lock);
	port->flags = 0;
	port->अवरोध_ctl = 0;
	port->overrun = 0;
	__fwtty_ग_लिखो_port_status(port);
	dma_fअगरo_मुक्त(&port->tx_fअगरo);
	spin_unlock_bh(&port->lock);
पूर्ण

अटल पूर्णांक fwtty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *fp)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	वापस tty_port_खोलो(&port->port, tty, fp);
पूर्ण

अटल व्योम fwtty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *fp)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	tty_port_बंद(&port->port, tty, fp);
पूर्ण

अटल व्योम fwtty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	tty_port_hangup(&port->port);
पूर्ण

अटल व्योम fwtty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	tty->driver_data = शून्य;
	fwtty_port_put(port);
पूर्ण

अटल पूर्णांक fwtty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = fwtty_port_get(tty->index);
	पूर्णांक err;

	err = tty_standard_install(driver, tty);
	अगर (!err)
		tty->driver_data = port;
	अन्यथा
		fwtty_port_put(port);
	वापस err;
पूर्ण

अटल पूर्णांक fwloop_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = fwtty_port_get(table_idx(tty->index));
	पूर्णांक err;

	err = tty_standard_install(driver, tty);
	अगर (!err)
		tty->driver_data = port;
	अन्यथा
		fwtty_port_put(port);
	वापस err;
पूर्ण

अटल पूर्णांक fwtty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक c)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	पूर्णांक n, len;

	fwtty_dbg(port, "%d\n", c);
	fwtty_profile_data(port->stats.ग_लिखोs, c);

	spin_lock_bh(&port->lock);
	n = dma_fअगरo_in(&port->tx_fअगरo, buf, c);
	len = dma_fअगरo_out_level(&port->tx_fअगरo);
	अगर (len < DRAIN_THRESHOLD)
		schedule_delayed_work(&port->drain, 1);
	spin_unlock_bh(&port->lock);

	अगर (len >= DRAIN_THRESHOLD)
		fwtty_tx(port, false);

	debug_लघु_ग_लिखो(port, c, n);

	वापस (n < 0) ? 0 : n;
पूर्ण

अटल पूर्णांक fwtty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	पूर्णांक n;

	spin_lock_bh(&port->lock);
	n = dma_fअगरo_avail(&port->tx_fअगरo);
	spin_unlock_bh(&port->lock);

	fwtty_dbg(port, "%d\n", n);

	वापस n;
पूर्ण

अटल पूर्णांक fwtty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	पूर्णांक n;

	spin_lock_bh(&port->lock);
	n = dma_fअगरo_level(&port->tx_fअगरo);
	spin_unlock_bh(&port->lock);

	fwtty_dbg(port, "%d\n", n);

	वापस n;
पूर्ण

अटल व्योम fwtty_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	fwtty_dbg(port, "%02x\n", ch);

	fwtty_ग_लिखो_xअक्षर(port, ch);
पूर्ण

अटल व्योम fwtty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	/*
	 * Ignore throttling (but not unthrottling).
	 * It only makes sense to throttle when data will no दीर्घer be
	 * accepted by the tty flip buffer. For example, it is
	 * possible क्रम received data to overflow the tty buffer दीर्घ
	 * beक्रमe the line discipline ever has a chance to throttle the driver.
	 * Additionally, the driver may have alपढ़ोy completed the I/O
	 * but the tty buffer is still emptying, so the line discipline is
	 * throttling and unthrottling nothing.
	 */

	++port->stats.throttled;
पूर्ण

अटल व्योम fwtty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	fwtty_dbg(port, "CRTSCTS: %d\n", C_CRTSCTS(tty) != 0);

	fwtty_profile_fअगरo(port, port->stats.unthrottle);

	spin_lock_bh(&port->lock);
	port->mctrl &= ~OOB_RX_THROTTLE;
	अगर (C_CRTSCTS(tty))
		port->mctrl |= TIOCM_RTS;
	__fwtty_ग_लिखो_port_status(port);
	spin_unlock_bh(&port->lock);
पूर्ण

अटल पूर्णांक check_msr_delta(काष्ठा fwtty_port *port, अचिन्हित दीर्घ mask,
			   काष्ठा async_icount *prev)
अणु
	काष्ठा async_icount now;
	पूर्णांक delta;

	now = port->icount;

	delta = ((mask & TIOCM_RNG && prev->rng != now.rng) ||
		 (mask & TIOCM_DSR && prev->dsr != now.dsr) ||
		 (mask & TIOCM_CAR && prev->dcd != now.dcd) ||
		 (mask & TIOCM_CTS && prev->cts != now.cts));

	*prev = now;

	वापस delta;
पूर्ण

अटल पूर्णांक रुको_msr_change(काष्ठा fwtty_port *port, अचिन्हित दीर्घ mask)
अणु
	काष्ठा async_icount prev;

	prev = port->icount;

	वापस रुको_event_पूर्णांकerruptible(port->port.delta_msr_रुको,
					check_msr_delta(port, mask, &prev));
पूर्ण

अटल पूर्णांक get_serial_info(काष्ठा tty_काष्ठा *tty,
			   काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	mutex_lock(&port->port.mutex);
	ss->line = port->index;
	ss->baud_base = 400000000;
	ss->बंद_delay = jअगरfies_to_msecs(port->port.बंद_delay) / 10;
	ss->closing_रुको = 3000;
	mutex_unlock(&port->port.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक set_serial_info(काष्ठा tty_काष्ठा *tty,
			   काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	अचिन्हित पूर्णांक cdelay;

	cdelay = msecs_to_jअगरfies(ss->बंद_delay * 10);

	mutex_lock(&port->port.mutex);
	अगर (!capable(CAP_SYS_ADMIN)) अणु
		अगर (cdelay != port->port.बंद_delay ||
		    ((ss->flags & ~ASYNC_USR_MASK) !=
		     (port->port.flags & ~ASYNC_USR_MASK))) अणु
			mutex_unlock(&port->port.mutex);
			वापस -EPERM;
		पूर्ण
	पूर्ण
	port->port.बंद_delay = cdelay;
	mutex_unlock(&port->port.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक fwtty_ioctl(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल TIOCMIWAIT:
		err = रुको_msr_change(port, arg);
		अवरोध;

	शेष:
		err = -ENOIOCTLCMD;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम fwtty_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	अचिन्हित पूर्णांक baud;

	spin_lock_bh(&port->lock);
	baud = set_termios(port, tty);

	अगर ((baud == 0) && (old->c_cflag & CBAUD)) अणु
		port->mctrl &= ~(TIOCM_DTR | TIOCM_RTS);
	पूर्ण अन्यथा अगर ((baud != 0) && !(old->c_cflag & CBAUD)) अणु
		अगर (C_CRTSCTS(tty) || !tty_throttled(tty))
			port->mctrl |= TIOCM_DTR | TIOCM_RTS;
		अन्यथा
			port->mctrl |= TIOCM_DTR;
	पूर्ण
	__fwtty_ग_लिखो_port_status(port);
	spin_unlock_bh(&port->lock);

	अगर (old->c_cflag & CRTSCTS) अणु
		अगर (!C_CRTSCTS(tty)) अणु
			tty->hw_stopped = 0;
			fwtty_restart_tx(port);
		पूर्ण
	पूर्ण अन्यथा अगर (C_CRTSCTS(tty) && ~port->mstatus & TIOCM_CTS) अणु
		tty->hw_stopped = 1;
	पूर्ण
पूर्ण

/**
 * fwtty_अवरोध_ctl - start/stop sending अवरोधs
 *
 * Signals the remote to start or stop generating simulated अवरोधs.
 * First, stop dequeueing from the fअगरo and रुको क्रम ग_लिखोr/drain to leave tx
 * beक्रमe संकेतling the अवरोध line status. This guarantees any pending rx will
 * be queued to the line discipline beक्रमe अवरोध is simulated on the remote.
 * Conversely, turning off अवरोध_ctl requires संकेतling the line status change,
 * then enabling tx.
 */
अटल पूर्णांक fwtty_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	दीर्घ ret;

	fwtty_dbg(port, "%d\n", state);

	अगर (state == -1) अणु
		set_bit(STOP_TX, &port->flags);
		ret = रुको_event_पूर्णांकerruptible_समयout(port->रुको_tx,
						       !test_bit(IN_TX, &port->flags),
						       10);
		अगर (ret == 0 || ret == -ERESTARTSYS) अणु
			clear_bit(STOP_TX, &port->flags);
			fwtty_restart_tx(port);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	spin_lock_bh(&port->lock);
	port->अवरोध_ctl = (state == -1);
	__fwtty_ग_लिखो_port_status(port);
	spin_unlock_bh(&port->lock);

	अगर (state == 0) अणु
		spin_lock_bh(&port->lock);
		dma_fअगरo_reset(&port->tx_fअगरo);
		clear_bit(STOP_TX, &port->flags);
		spin_unlock_bh(&port->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fwtty_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	अचिन्हित पूर्णांक tiocm;

	spin_lock_bh(&port->lock);
	tiocm = (port->mctrl & MCTRL_MASK) | (port->mstatus & ~MCTRL_MASK);
	spin_unlock_bh(&port->lock);

	fwtty_dbg(port, "%x\n", tiocm);

	वापस tiocm;
पूर्ण

अटल पूर्णांक fwtty_tiocmset(काष्ठा tty_काष्ठा *tty,
			  अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;

	fwtty_dbg(port, "set: %x clear: %x\n", set, clear);

	/* TODO: simulate loopback अगर TIOCM_LOOP set */

	spin_lock_bh(&port->lock);
	port->mctrl &= ~(clear & MCTRL_MASK & 0xffff);
	port->mctrl |= set & MCTRL_MASK & 0xffff;
	__fwtty_ग_लिखो_port_status(port);
	spin_unlock_bh(&port->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक fwtty_get_icount(काष्ठा tty_काष्ठा *tty,
			    काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा fwtty_port *port = tty->driver_data;
	काष्ठा stats stats;

	स_नकल(&stats, &port->stats, माप(stats));
	अगर (port->port.console)
		(*port->fwcon_ops->stats)(&stats, port->con_data);

	icount->cts = port->icount.cts;
	icount->dsr = port->icount.dsr;
	icount->rng = port->icount.rng;
	icount->dcd = port->icount.dcd;
	icount->rx  = port->icount.rx;
	icount->tx  = port->icount.tx + stats.xअक्षरs;
	icount->frame   = port->icount.frame;
	icount->overrun = port->icount.overrun;
	icount->parity  = port->icount.parity;
	icount->brk     = port->icount.brk;
	icount->buf_overrun = port->icount.overrun;
	वापस 0;
पूर्ण

अटल व्योम fwtty_proc_show_port(काष्ठा seq_file *m, काष्ठा fwtty_port *port)
अणु
	काष्ठा stats stats;

	स_नकल(&stats, &port->stats, माप(stats));
	अगर (port->port.console)
		(*port->fwcon_ops->stats)(&stats, port->con_data);

	seq_म_लिखो(m, " addr:%012llx tx:%d rx:%d", port->rx_handler.offset,
		   port->icount.tx + stats.xअक्षरs, port->icount.rx);
	seq_म_लिखो(m, " cts:%d dsr:%d rng:%d dcd:%d", port->icount.cts,
		   port->icount.dsr, port->icount.rng, port->icount.dcd);
	seq_म_लिखो(m, " fe:%d oe:%d pe:%d brk:%d", port->icount.frame,
		   port->icount.overrun, port->icount.parity, port->icount.brk);
पूर्ण

अटल व्योम fwtty_debugfs_show_port(काष्ठा seq_file *m, काष्ठा fwtty_port *port)
अणु
	काष्ठा stats stats;

	स_नकल(&stats, &port->stats, माप(stats));
	अगर (port->port.console)
		(*port->fwcon_ops->stats)(&stats, port->con_data);

	seq_म_लिखो(m, " dr:%d st:%d err:%d lost:%d", stats.dropped,
		   stats.tx_stall, stats.fअगरo_errs, stats.lost);
	seq_म_लिखो(m, " pkts:%d thr:%d", stats.sent, stats.throttled);

	अगर (port->port.console) अणु
		seq_माला_दो(m, "\n    ");
		(*port->fwcon_ops->proc_show)(m, port->con_data);
	पूर्ण

	fwtty_dump_profile(m, &port->stats);
पूर्ण

अटल व्योम fwtty_debugfs_show_peer(काष्ठा seq_file *m, काष्ठा fwtty_peer *peer)
अणु
	पूर्णांक generation = peer->generation;

	smp_rmb();
	seq_म_लिखो(m, " %s:", dev_name(&peer->unit->device));
	seq_म_लिखो(m, " node:%04x gen:%d", peer->node_id, generation);
	seq_म_लिखो(m, " sp:%d max:%d guid:%016llx", peer->speed,
		   peer->max_payload, (अचिन्हित दीर्घ दीर्घ)peer->guid);
	seq_म_लिखो(m, " mgmt:%012llx", (अचिन्हित दीर्घ दीर्घ)peer->mgmt_addr);
	seq_म_लिखो(m, " addr:%012llx", (अचिन्हित दीर्घ दीर्घ)peer->status_addr);
	seq_अ_दो(m, '\n');
पूर्ण

अटल पूर्णांक fwtty_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा fwtty_port *port;
	पूर्णांक i;

	seq_माला_दो(m, "fwserinfo: 1.0 driver: 1.0\n");
	क्रम (i = 0; i < MAX_TOTAL_PORTS && (port = fwtty_port_get(i)); ++i) अणु
		seq_म_लिखो(m, "%2d:", i);
		अगर (capable(CAP_SYS_ADMIN))
			fwtty_proc_show_port(m, port);
		fwtty_port_put(port);
		seq_माला_दो(m, "\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fwtty_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा fw_serial *serial = m->निजी;
	काष्ठा fwtty_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < num_ports; ++i) अणु
		port = fwtty_port_get(serial->ports[i]->index);
		अगर (port) अणु
			seq_म_लिखो(m, "%2d:", port->index);
			fwtty_proc_show_port(m, port);
			fwtty_debugfs_show_port(m, port);
			fwtty_port_put(port);
			seq_माला_दो(m, "\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(fwtty_stats);

अटल पूर्णांक fwtty_peers_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा fw_serial *serial = m->निजी;
	काष्ठा fwtty_peer *peer;

	rcu_पढ़ो_lock();
	seq_म_लिखो(m, "card: %s  guid: %016llx\n",
		   dev_name(serial->card->device),
		   (अचिन्हित दीर्घ दीर्घ)serial->card->guid);
	list_क्रम_each_entry_rcu(peer, &serial->peer_list, list)
		fwtty_debugfs_show_peer(m, peer);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(fwtty_peers);

अटल स्थिर काष्ठा tty_port_operations fwtty_port_ops = अणु
	.dtr_rts =		fwtty_port_dtr_rts,
	.carrier_उठाओd =	fwtty_port_carrier_उठाओd,
	.shutकरोwn =		fwtty_port_shutकरोwn,
	.activate =		fwtty_port_activate,
पूर्ण;

अटल स्थिर काष्ठा tty_operations fwtty_ops = अणु
	.खोलो =			fwtty_खोलो,
	.बंद =		fwtty_बंद,
	.hangup =		fwtty_hangup,
	.cleanup =		fwtty_cleanup,
	.install =		fwtty_install,
	.ग_लिखो =		fwtty_ग_लिखो,
	.ग_लिखो_room =		fwtty_ग_लिखो_room,
	.अक्षरs_in_buffer =	fwtty_अक्षरs_in_buffer,
	.send_xअक्षर =           fwtty_send_xअक्षर,
	.throttle =             fwtty_throttle,
	.unthrottle =           fwtty_unthrottle,
	.ioctl =		fwtty_ioctl,
	.set_termios =		fwtty_set_termios,
	.अवरोध_ctl =		fwtty_अवरोध_ctl,
	.tiocmget =		fwtty_tiocmget,
	.tiocmset =		fwtty_tiocmset,
	.get_icount =		fwtty_get_icount,
	.set_serial =		set_serial_info,
	.get_serial =		get_serial_info,
	.proc_show =		fwtty_proc_show,
पूर्ण;

अटल स्थिर काष्ठा tty_operations fwloop_ops = अणु
	.खोलो =			fwtty_खोलो,
	.बंद =		fwtty_बंद,
	.hangup =		fwtty_hangup,
	.cleanup =		fwtty_cleanup,
	.install =		fwloop_install,
	.ग_लिखो =		fwtty_ग_लिखो,
	.ग_लिखो_room =		fwtty_ग_लिखो_room,
	.अक्षरs_in_buffer =	fwtty_अक्षरs_in_buffer,
	.send_xअक्षर =           fwtty_send_xअक्षर,
	.throttle =             fwtty_throttle,
	.unthrottle =           fwtty_unthrottle,
	.ioctl =		fwtty_ioctl,
	.set_termios =		fwtty_set_termios,
	.अवरोध_ctl =		fwtty_अवरोध_ctl,
	.tiocmget =		fwtty_tiocmget,
	.tiocmset =		fwtty_tiocmset,
	.get_icount =		fwtty_get_icount,
	.set_serial =		set_serial_info,
	.get_serial =		get_serial_info,
पूर्ण;

अटल अंतरभूत पूर्णांक mgmt_pkt_expected_len(__be16 code)
अणु
	अटल स्थिर काष्ठा fwserial_mgmt_pkt pkt;

	चयन (be16_to_cpu(code)) अणु
	हाल FWSC_VIRT_CABLE_PLUG:
		वापस माप(pkt.hdr) + माप(pkt.plug_req);

	हाल FWSC_VIRT_CABLE_PLUG_RSP:  /* | FWSC_RSP_OK */
		वापस माप(pkt.hdr) + माप(pkt.plug_rsp);

	हाल FWSC_VIRT_CABLE_UNPLUG:
	हाल FWSC_VIRT_CABLE_UNPLUG_RSP:
	हाल FWSC_VIRT_CABLE_PLUG_RSP | FWSC_RSP_NACK:
	हाल FWSC_VIRT_CABLE_UNPLUG_RSP | FWSC_RSP_NACK:
		वापस माप(pkt.hdr);

	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fill_plug_params(काष्ठा virt_plug_params *params,
				    काष्ठा fwtty_port *port)
अणु
	u64 status_addr = port->rx_handler.offset;
	u64 fअगरo_addr = port->rx_handler.offset + 4;
	माप_प्रकार fअगरo_len = port->rx_handler.length - 4;

	params->status_hi = cpu_to_be32(status_addr >> 32);
	params->status_lo = cpu_to_be32(status_addr);
	params->fअगरo_hi = cpu_to_be32(fअगरo_addr >> 32);
	params->fअगरo_lo = cpu_to_be32(fअगरo_addr);
	params->fअगरo_len = cpu_to_be32(fअगरo_len);
पूर्ण

अटल अंतरभूत व्योम fill_plug_req(काष्ठा fwserial_mgmt_pkt *pkt,
				 काष्ठा fwtty_port *port)
अणु
	pkt->hdr.code = cpu_to_be16(FWSC_VIRT_CABLE_PLUG);
	pkt->hdr.len = cpu_to_be16(mgmt_pkt_expected_len(pkt->hdr.code));
	fill_plug_params(&pkt->plug_req, port);
पूर्ण

अटल अंतरभूत व्योम fill_plug_rsp_ok(काष्ठा fwserial_mgmt_pkt *pkt,
				    काष्ठा fwtty_port *port)
अणु
	pkt->hdr.code = cpu_to_be16(FWSC_VIRT_CABLE_PLUG_RSP);
	pkt->hdr.len = cpu_to_be16(mgmt_pkt_expected_len(pkt->hdr.code));
	fill_plug_params(&pkt->plug_rsp, port);
पूर्ण

अटल अंतरभूत व्योम fill_plug_rsp_nack(काष्ठा fwserial_mgmt_pkt *pkt)
अणु
	pkt->hdr.code = cpu_to_be16(FWSC_VIRT_CABLE_PLUG_RSP | FWSC_RSP_NACK);
	pkt->hdr.len = cpu_to_be16(mgmt_pkt_expected_len(pkt->hdr.code));
पूर्ण

अटल अंतरभूत व्योम fill_unplug_rsp_nack(काष्ठा fwserial_mgmt_pkt *pkt)
अणु
	pkt->hdr.code = cpu_to_be16(FWSC_VIRT_CABLE_UNPLUG_RSP | FWSC_RSP_NACK);
	pkt->hdr.len = cpu_to_be16(mgmt_pkt_expected_len(pkt->hdr.code));
पूर्ण

अटल अंतरभूत व्योम fill_unplug_rsp_ok(काष्ठा fwserial_mgmt_pkt *pkt)
अणु
	pkt->hdr.code = cpu_to_be16(FWSC_VIRT_CABLE_UNPLUG_RSP);
	pkt->hdr.len = cpu_to_be16(mgmt_pkt_expected_len(pkt->hdr.code));
पूर्ण

अटल व्योम fwserial_virt_plug_complete(काष्ठा fwtty_peer *peer,
					काष्ठा virt_plug_params *params)
अणु
	काष्ठा fwtty_port *port = peer->port;

	peer->status_addr = be32_to_u64(params->status_hi, params->status_lo);
	peer->fअगरo_addr = be32_to_u64(params->fअगरo_hi, params->fअगरo_lo);
	peer->fअगरo_len = be32_to_cpu(params->fअगरo_len);
	peer_set_state(peer, FWPS_ATTACHED);

	/* reconfigure tx_fअगरo optimally क्रम this peer */
	spin_lock_bh(&port->lock);
	port->max_payload = min(peer->max_payload, peer->fअगरo_len);
	dma_fअगरo_change_tx_limit(&port->tx_fअगरo, port->max_payload);
	spin_unlock_bh(&peer->port->lock);

	अगर (port->port.console && port->fwcon_ops->notअगरy)
		(*port->fwcon_ops->notअगरy)(FWCON_NOTIFY_ATTACH, port->con_data);

	fwtty_info(&peer->unit, "peer (guid:%016llx) connected on %s\n",
		   (अचिन्हित दीर्घ दीर्घ)peer->guid, dev_name(port->device));
पूर्ण

अटल अंतरभूत पूर्णांक fwserial_send_mgmt_sync(काष्ठा fwtty_peer *peer,
					  काष्ठा fwserial_mgmt_pkt *pkt)
अणु
	पूर्णांक generation;
	पूर्णांक rcode, tries = 5;

	करो अणु
		generation = peer->generation;
		smp_rmb();

		rcode = fw_run_transaction(peer->serial->card,
					   TCODE_WRITE_BLOCK_REQUEST,
					   peer->node_id,
					   generation, peer->speed,
					   peer->mgmt_addr,
					   pkt, be16_to_cpu(pkt->hdr.len));
		अगर (rcode == RCODE_BUSY || rcode == RCODE_SEND_ERROR ||
		    rcode == RCODE_GENERATION) अणु
			fwtty_dbg(&peer->unit, "mgmt write error: %d\n", rcode);
			जारी;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण जबतक (--tries > 0);
	वापस rcode;
पूर्ण

/**
 * fwserial_claim_port - attempt to claim port @ index क्रम peer
 *
 * Returns ptr to claimed port or error code (as ERR_PTR())
 * Can sleep - must be called from process context
 */
अटल काष्ठा fwtty_port *fwserial_claim_port(काष्ठा fwtty_peer *peer,
					      पूर्णांक index)
अणु
	काष्ठा fwtty_port *port;

	अगर (index < 0 || index >= num_ports)
		वापस ERR_PTR(-EINVAL);

	/* must guarantee that previous port releases have completed */
	synchronize_rcu();

	port = peer->serial->ports[index];
	spin_lock_bh(&port->lock);
	अगर (!rcu_access_poपूर्णांकer(port->peer))
		rcu_assign_poपूर्णांकer(port->peer, peer);
	अन्यथा
		port = ERR_PTR(-EBUSY);
	spin_unlock_bh(&port->lock);

	वापस port;
पूर्ण

/**
 * fwserial_find_port - find avail port and claim क्रम peer
 *
 * Returns ptr to claimed port or शून्य अगर none avail
 * Can sleep - must be called from process context
 */
अटल काष्ठा fwtty_port *fwserial_find_port(काष्ठा fwtty_peer *peer)
अणु
	काष्ठा fwtty_port **ports = peer->serial->ports;
	पूर्णांक i;

	/* must guarantee that previous port releases have completed */
	synchronize_rcu();

	/* TODO: implement optional GUID-to-specअगरic port # matching */

	/* find an unattached port (but not the loopback port, अगर present) */
	क्रम (i = 0; i < num_ttys; ++i) अणु
		spin_lock_bh(&ports[i]->lock);
		अगर (!ports[i]->peer) अणु
			/* claim port */
			rcu_assign_poपूर्णांकer(ports[i]->peer, peer);
			spin_unlock_bh(&ports[i]->lock);
			वापस ports[i];
		पूर्ण
		spin_unlock_bh(&ports[i]->lock);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम fwserial_release_port(काष्ठा fwtty_port *port, bool reset)
अणु
	/* drop carrier (and all other line status) */
	अगर (reset)
		fwtty_update_port_status(port, 0);

	spin_lock_bh(&port->lock);

	/* reset dma fअगरo max transmission size back to S100 */
	port->max_payload = link_speed_to_max_payload(SCODE_100);
	dma_fअगरo_change_tx_limit(&port->tx_fअगरo, port->max_payload);

	RCU_INIT_POINTER(port->peer, शून्य);
	spin_unlock_bh(&port->lock);

	अगर (port->port.console && port->fwcon_ops->notअगरy)
		(*port->fwcon_ops->notअगरy)(FWCON_NOTIFY_DETACH, port->con_data);
पूर्ण

अटल व्योम fwserial_plug_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा fwtty_peer *peer = from_समयr(peer, t, समयr);
	काष्ठा fwtty_port *port;

	spin_lock_bh(&peer->lock);
	अगर (peer->state != FWPS_PLUG_PENDING) अणु
		spin_unlock_bh(&peer->lock);
		वापस;
	पूर्ण

	port = peer_revert_state(peer);
	spin_unlock_bh(&peer->lock);

	अगर (port)
		fwserial_release_port(port, false);
पूर्ण

/**
 * fwserial_connect_peer - initiate भव cable with peer
 *
 * Returns 0 अगर VIRT_CABLE_PLUG request was successfully sent,
 * otherwise error code.  Must be called from process context.
 */
अटल पूर्णांक fwserial_connect_peer(काष्ठा fwtty_peer *peer)
अणु
	काष्ठा fwtty_port *port;
	काष्ठा fwserial_mgmt_pkt *pkt;
	पूर्णांक err, rcode;

	pkt = kदो_स्मृति(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	port = fwserial_find_port(peer);
	अगर (!port) अणु
		fwtty_err(&peer->unit, "avail ports in use\n");
		err = -EBUSY;
		जाओ मुक्त_pkt;
	पूर्ण

	spin_lock_bh(&peer->lock);

	/* only initiate VIRT_CABLE_PLUG अगर peer is currently not attached */
	अगर (peer->state != FWPS_NOT_ATTACHED) अणु
		err = -EBUSY;
		जाओ release_port;
	पूर्ण

	peer->port = port;
	peer_set_state(peer, FWPS_PLUG_PENDING);

	fill_plug_req(pkt, peer->port);

	mod_समयr(&peer->समयr, jअगरfies + VIRT_CABLE_PLUG_TIMEOUT);
	spin_unlock_bh(&peer->lock);

	rcode = fwserial_send_mgmt_sync(peer, pkt);

	spin_lock_bh(&peer->lock);
	अगर (peer->state == FWPS_PLUG_PENDING && rcode != RCODE_COMPLETE) अणु
		अगर (rcode == RCODE_CONFLICT_ERROR)
			err = -EAGAIN;
		अन्यथा
			err = -EIO;
		जाओ cancel_समयr;
	पूर्ण
	spin_unlock_bh(&peer->lock);

	kमुक्त(pkt);
	वापस 0;

cancel_समयr:
	del_समयr(&peer->समयr);
	peer_revert_state(peer);
release_port:
	spin_unlock_bh(&peer->lock);
	fwserial_release_port(port, false);
मुक्त_pkt:
	kमुक्त(pkt);
	वापस err;
पूर्ण

/**
 * fwserial_बंद_port -
 * HUP the tty (अगर the tty exists) and unरेजिस्टर the tty device.
 * Only used by the unit driver upon unit removal to disconnect and
 * cleanup all attached ports
 *
 * The port reference is put by fwtty_cleanup (अगर a reference was
 * ever taken).
 */
अटल व्योम fwserial_बंद_port(काष्ठा tty_driver *driver,
				काष्ठा fwtty_port *port)
अणु
	काष्ठा tty_काष्ठा *tty;

	mutex_lock(&port->port.mutex);
	tty = tty_port_tty_get(&port->port);
	अगर (tty) अणु
		tty_vhangup(tty);
		tty_kref_put(tty);
	पूर्ण
	mutex_unlock(&port->port.mutex);

	अगर (driver == fwloop_driver)
		tty_unरेजिस्टर_device(driver, loop_idx(port));
	अन्यथा
		tty_unरेजिस्टर_device(driver, port->index);
पूर्ण

/**
 * fwserial_lookup - finds first fw_serial associated with card
 * @card: fw_card to match
 *
 * NB: caller must be holding fwserial_list_mutex
 */
अटल काष्ठा fw_serial *fwserial_lookup(काष्ठा fw_card *card)
अणु
	काष्ठा fw_serial *serial;

	list_क्रम_each_entry(serial, &fwserial_list, list) अणु
		अगर (card == serial->card)
			वापस serial;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __fwserial_lookup_rcu - finds first fw_serial associated with card
 * @card: fw_card to match
 *
 * NB: caller must be inside rcu_पढ़ो_lock() section
 */
अटल काष्ठा fw_serial *__fwserial_lookup_rcu(काष्ठा fw_card *card)
अणु
	काष्ठा fw_serial *serial;

	list_क्रम_each_entry_rcu(serial, &fwserial_list, list) अणु
		अगर (card == serial->card)
			वापस serial;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __fwserial_peer_by_node_id - finds a peer matching the given generation + id
 *
 * If a matching peer could not be found क्रम the specअगरied generation/node id,
 * this could be because:
 * a) the generation has changed and one of the nodes hasn't updated yet
 * b) the remote node has created its remote unit device beक्रमe this
 *    local node has created its corresponding remote unit device
 * In either हाल, the remote node should retry
 *
 * Note: caller must be in rcu_पढ़ो_lock() section
 */
अटल काष्ठा fwtty_peer *__fwserial_peer_by_node_id(काष्ठा fw_card *card,
						     पूर्णांक generation, पूर्णांक id)
अणु
	काष्ठा fw_serial *serial;
	काष्ठा fwtty_peer *peer;

	serial = __fwserial_lookup_rcu(card);
	अगर (!serial) अणु
		/*
		 * Something is very wrong - there should be a matching
		 * fw_serial काष्ठाure क्रम every fw_card. Maybe the remote node
		 * has created its remote unit device beक्रमe this driver has
		 * been probed क्रम any unit devices...
		 */
		fwtty_err(card, "unknown card (guid %016llx)\n",
			  (अचिन्हित दीर्घ दीर्घ)card->guid);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry_rcu(peer, &serial->peer_list, list) अणु
		पूर्णांक g = peer->generation;

		smp_rmb();
		अगर (generation == g && id == peer->node_id)
			वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम __dump_peer_list(काष्ठा fw_card *card)
अणु
	काष्ठा fw_serial *serial;
	काष्ठा fwtty_peer *peer;

	serial = __fwserial_lookup_rcu(card);
	अगर (!serial)
		वापस;

	list_क्रम_each_entry_rcu(peer, &serial->peer_list, list) अणु
		पूर्णांक g = peer->generation;

		smp_rmb();
		fwtty_dbg(card, "peer(%d:%x) guid: %016llx\n",
			  g, peer->node_id, (अचिन्हित दीर्घ दीर्घ)peer->guid);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा __dump_peer_list(s)
#पूर्ण_अगर

अटल व्योम fwserial_स्वतः_connect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fwtty_peer *peer = to_peer(to_delayed_work(work), connect);
	पूर्णांक err;

	err = fwserial_connect_peer(peer);
	अगर (err == -EAGAIN && ++peer->connect_retries < MAX_CONNECT_RETRIES)
		schedule_delayed_work(&peer->connect, CONNECT_RETRY_DELAY);
पूर्ण

अटल व्योम fwserial_peer_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fwtty_peer *peer = to_peer(work, work);

	peer->workfn(work);
पूर्ण

/**
 * fwserial_add_peer - add a newly probed 'serial' unit device as a 'peer'
 * @serial: aggregate representing the specअगरic fw_card to add the peer to
 * @unit: 'peer' to create and add to peer_list of serial
 *
 * Adds a 'peer' (ie, a local or remote 'serial' unit device) to the list of
 * peers क्रम a specअगरic fw_card. Optionally, स्वतः-attach this peer to an
 * available tty port. This function is called either directly or indirectly
 * as a result of a 'serial' unit device being created & probed.
 *
 * Note: this function is serialized with fwserial_हटाओ_peer() by the
 * fwserial_list_mutex held in fwserial_probe().
 *
 * A 1:1 correspondence between an fw_unit and an fwtty_peer is मुख्यtained
 * via the dev_set_drvdata() क्रम the device of the fw_unit.
 */
अटल पूर्णांक fwserial_add_peer(काष्ठा fw_serial *serial, काष्ठा fw_unit *unit)
अणु
	काष्ठा device *dev = &unit->device;
	काष्ठा fw_device  *parent = fw_parent_device(unit);
	काष्ठा fwtty_peer *peer;
	काष्ठा fw_csr_iterator ci;
	पूर्णांक key, val;
	पूर्णांक generation;

	peer = kzalloc(माप(*peer), GFP_KERNEL);
	अगर (!peer)
		वापस -ENOMEM;

	peer_set_state(peer, FWPS_NOT_ATTACHED);

	dev_set_drvdata(dev, peer);
	peer->unit = unit;
	peer->guid = (u64)parent->config_rom[3] << 32 | parent->config_rom[4];
	peer->speed = parent->max_speed;
	peer->max_payload = min(device_max_receive(parent),
				link_speed_to_max_payload(peer->speed));

	generation = parent->generation;
	smp_rmb();
	peer->node_id = parent->node_id;
	smp_wmb();
	peer->generation = generation;

	/* retrieve the mgmt bus addr from the unit directory */
	fw_csr_iterator_init(&ci, unit->directory);
	जबतक (fw_csr_iterator_next(&ci, &key, &val)) अणु
		अगर (key == (CSR_OFFSET | CSR_DEPENDENT_INFO)) अणु
			peer->mgmt_addr = CSR_REGISTER_BASE + 4 * val;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (peer->mgmt_addr == 0ULL) अणु
		/*
		 * No mgmt address effectively disables VIRT_CABLE_PLUG -
		 * this peer will not be able to attach to a remote
		 */
		peer_set_state(peer, FWPS_NO_MGMT_ADDR);
	पूर्ण

	spin_lock_init(&peer->lock);
	peer->port = शून्य;

	समयr_setup(&peer->समयr, fwserial_plug_समयout, 0);
	INIT_WORK(&peer->work, fwserial_peer_workfn);
	INIT_DELAYED_WORK(&peer->connect, fwserial_स्वतः_connect);

	/* associate peer with specअगरic fw_card */
	peer->serial = serial;
	list_add_rcu(&peer->list, &serial->peer_list);

	fwtty_info(&peer->unit, "peer added (guid:%016llx)\n",
		   (अचिन्हित दीर्घ दीर्घ)peer->guid);

	/* identअगरy the local unit & virt cable to loopback port */
	अगर (parent->is_local) अणु
		serial->self = peer;
		अगर (create_loop_dev) अणु
			काष्ठा fwtty_port *port;

			port = fwserial_claim_port(peer, num_ttys);
			अगर (!IS_ERR(port)) अणु
				काष्ठा virt_plug_params params;

				spin_lock_bh(&peer->lock);
				peer->port = port;
				fill_plug_params(&params, port);
				fwserial_virt_plug_complete(peer, &params);
				spin_unlock_bh(&peer->lock);

				fwtty_ग_लिखो_port_status(port);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (स्वतः_connect) अणु
		/* स्वतः-attach to remote units only (अगर policy allows) */
		schedule_delayed_work(&peer->connect, 1);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fwserial_हटाओ_peer - हटाओ a 'serial' unit device as a 'peer'
 *
 * Remove a 'peer' from its list of peers. This function is only
 * called by fwserial_हटाओ() on bus removal of the unit device.
 *
 * Note: this function is serialized with fwserial_add_peer() by the
 * fwserial_list_mutex held in fwserial_हटाओ().
 */
अटल व्योम fwserial_हटाओ_peer(काष्ठा fwtty_peer *peer)
अणु
	काष्ठा fwtty_port *port;

	spin_lock_bh(&peer->lock);
	peer_set_state(peer, FWPS_GONE);
	spin_unlock_bh(&peer->lock);

	cancel_delayed_work_sync(&peer->connect);
	cancel_work_sync(&peer->work);

	spin_lock_bh(&peer->lock);
	/* अगर this unit is the local unit, clear link */
	अगर (peer == peer->serial->self)
		peer->serial->self = शून्य;

	/* cancel the request समयout समयr (अगर running) */
	del_समयr(&peer->समयr);

	port = peer->port;
	peer->port = शून्य;

	list_del_rcu(&peer->list);

	fwtty_info(&peer->unit, "peer removed (guid:%016llx)\n",
		   (अचिन्हित दीर्घ दीर्घ)peer->guid);

	spin_unlock_bh(&peer->lock);

	अगर (port)
		fwserial_release_port(port, true);

	synchronize_rcu();
	kमुक्त(peer);
पूर्ण

/**
 * fwserial_create - init everything to create TTYs क्रम a specअगरic fw_card
 * @unit: fw_unit क्रम first 'serial' unit device probed क्रम this fw_card
 *
 * This function inits the aggregate काष्ठाure (an fw_serial instance)
 * used to manage the TTY ports रेजिस्टरed by a specअगरic fw_card. Also, the
 * unit device is added as the first 'peer'.
 *
 * This unit device may represent a local unit device (as specअगरied by the
 * config ROM unit directory) or it may represent a remote unit device
 * (as specअगरied by the पढ़ोing of the remote node's config ROM).
 *
 * Returns 0 to indicate "ownership" of the unit device, or a negative त्रुटि_सं
 * value to indicate which error.
 */
अटल पूर्णांक fwserial_create(काष्ठा fw_unit *unit)
अणु
	काष्ठा fw_device *parent = fw_parent_device(unit);
	काष्ठा fw_card *card = parent->card;
	काष्ठा fw_serial *serial;
	काष्ठा fwtty_port *port;
	काष्ठा device *tty_dev;
	पूर्णांक i, j;
	पूर्णांक err;

	serial = kzalloc(माप(*serial), GFP_KERNEL);
	अगर (!serial)
		वापस -ENOMEM;

	kref_init(&serial->kref);
	serial->card = card;
	INIT_LIST_HEAD(&serial->peer_list);

	क्रम (i = 0; i < num_ports; ++i) अणु
		port = kzalloc(माप(*port), GFP_KERNEL);
		अगर (!port) अणु
			err = -ENOMEM;
			जाओ मुक्त_ports;
		पूर्ण
		tty_port_init(&port->port);
		port->index = FWTTY_INVALID_INDEX;
		port->port.ops = &fwtty_port_ops;
		port->serial = serial;
		tty_buffer_set_limit(&port->port, 128 * 1024);

		spin_lock_init(&port->lock);
		INIT_DELAYED_WORK(&port->drain, fwtty_drain_tx);
		INIT_DELAYED_WORK(&port->emit_अवरोधs, fwtty_emit_अवरोधs);
		INIT_WORK(&port->hangup, fwtty_करो_hangup);
		init_रुकोqueue_head(&port->रुको_tx);
		port->max_payload = link_speed_to_max_payload(SCODE_100);
		dma_fअगरo_init(&port->tx_fअगरo);

		RCU_INIT_POINTER(port->peer, शून्य);
		serial->ports[i] = port;

		/* get unique bus addr region क्रम port's status & recv fअगरo */
		port->rx_handler.length = FWTTY_PORT_RXFIFO_LEN + 4;
		port->rx_handler.address_callback = fwtty_port_handler;
		port->rx_handler.callback_data = port;
		/*
		 * XXX: use custom memory region above cpu physical memory addrs
		 * this will ease porting to 64-bit firewire adapters
		 */
		err = fw_core_add_address_handler(&port->rx_handler,
						  &fw_high_memory_region);
		अगर (err) अणु
			tty_port_destroy(&port->port);
			kमुक्त(port);
			जाओ मुक्त_ports;
		पूर्ण
	पूर्ण
	/* preserve i क्रम error cleanup */

	err = fwtty_ports_add(serial);
	अगर (err) अणु
		fwtty_err(&unit, "no space in port table\n");
		जाओ मुक्त_ports;
	पूर्ण

	क्रम (j = 0; j < num_ttys; ++j) अणु
		tty_dev = tty_port_रेजिस्टर_device(&serial->ports[j]->port,
						   fwtty_driver,
						   serial->ports[j]->index,
						   card->device);
		अगर (IS_ERR(tty_dev)) अणु
			err = PTR_ERR(tty_dev);
			fwtty_err(&unit, "register tty device error (%d)\n",
				  err);
			जाओ unरेजिस्टर_ttys;
		पूर्ण

		serial->ports[j]->device = tty_dev;
	पूर्ण
	/* preserve j क्रम error cleanup */

	अगर (create_loop_dev) अणु
		काष्ठा device *loop_dev;

		loop_dev = tty_port_रेजिस्टर_device(&serial->ports[j]->port,
						    fwloop_driver,
						    loop_idx(serial->ports[j]),
						    card->device);
		अगर (IS_ERR(loop_dev)) अणु
			err = PTR_ERR(loop_dev);
			fwtty_err(&unit, "create loop device failed (%d)\n",
				  err);
			जाओ unरेजिस्टर_ttys;
		पूर्ण
		serial->ports[j]->device = loop_dev;
		serial->ports[j]->loopback = true;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(fwserial_debugfs)) अणु
		serial->debugfs = debugfs_create_dir(dev_name(&unit->device),
						     fwserial_debugfs);
		अगर (!IS_ERR_OR_शून्य(serial->debugfs)) अणु
			debugfs_create_file("peers", 0444, serial->debugfs,
					    serial, &fwtty_peers_fops);
			debugfs_create_file("stats", 0444, serial->debugfs,
					    serial, &fwtty_stats_fops);
		पूर्ण
	पूर्ण

	list_add_rcu(&serial->list, &fwserial_list);

	fwtty_notice(&unit, "TTY over FireWire on device %s (guid %016llx)\n",
		     dev_name(card->device), (अचिन्हित दीर्घ दीर्घ)card->guid);

	err = fwserial_add_peer(serial, unit);
	अगर (!err)
		वापस 0;

	fwtty_err(&unit, "unable to add peer unit device (%d)\n", err);

	/* fall-through to error processing */
	debugfs_हटाओ_recursive(serial->debugfs);

	list_del_rcu(&serial->list);
	अगर (create_loop_dev)
		tty_unरेजिस्टर_device(fwloop_driver,
				      loop_idx(serial->ports[j]));
unरेजिस्टर_ttys:
	क्रम (--j; j >= 0; --j)
		tty_unरेजिस्टर_device(fwtty_driver, serial->ports[j]->index);
	kref_put(&serial->kref, fwserial_destroy);
	वापस err;

मुक्त_ports:
	क्रम (--i; i >= 0; --i) अणु
		fw_core_हटाओ_address_handler(&serial->ports[i]->rx_handler);
		tty_port_destroy(&serial->ports[i]->port);
		kमुक्त(serial->ports[i]);
	पूर्ण
	kमुक्त(serial);
	वापस err;
पूर्ण

/**
 * fwserial_probe: bus probe function क्रम firewire 'serial' unit devices
 *
 * A 'serial' unit device is created and probed as a result of:
 * - declaring a ieee1394 bus id table क्रम 'devices' matching a fabricated
 *   'serial' unit specअगरier id
 * - adding a unit directory to the config ROM(s) क्रम a 'serial' unit
 *
 * The firewire core रेजिस्टरs unit devices by क्रमागतerating unit directories
 * of a node's config ROM after पढ़ोing the config ROM when a new node is
 * added to the bus topology after a bus reset.
 *
 * The practical implications of this are:
 * - this probe is called क्रम both local and remote nodes that have a 'serial'
 *   unit directory in their config ROM (that matches the specअगरiers in
 *   fwserial_id_table).
 * - no specअगरic order is enक्रमced क्रम local vs. remote unit devices
 *
 * This unit driver copes with the lack of specअगरic order in the same way the
 * firewire net driver करोes -- each probe, क्रम either a local or remote unit
 * device, is treated as a 'peer' (has a काष्ठा fwtty_peer instance) and the
 * first peer created क्रम a given fw_card (tracked by the global fwserial_list)
 * creates the underlying TTYs (aggregated in a fw_serial instance).
 *
 * NB: an early attempt to dअगरferentiate local & remote unit devices by creating
 *     peers only क्रम remote units and fw_serial instances (with their
 *     associated TTY devices) only क्रम local units was discarded. Managing
 *     the peer lअगरeबार on device removal proved too complicated.
 *
 * fwserial_probe/fwserial_हटाओ are effectively serialized by the
 * fwserial_list_mutex. This is necessary because the addition of the first peer
 * क्रम a given fw_card will trigger the creation of the fw_serial क्रम that
 * fw_card, which must not simultaneously contend with the removal of the
 * last peer क्रम a given fw_card triggering the deकाष्ठाion of the same
 * fw_serial क्रम the same fw_card.
 */
अटल पूर्णांक fwserial_probe(काष्ठा fw_unit *unit,
			  स्थिर काष्ठा ieee1394_device_id *id)
अणु
	काष्ठा fw_serial *serial;
	पूर्णांक err;

	mutex_lock(&fwserial_list_mutex);
	serial = fwserial_lookup(fw_parent_device(unit)->card);
	अगर (!serial)
		err = fwserial_create(unit);
	अन्यथा
		err = fwserial_add_peer(serial, unit);
	mutex_unlock(&fwserial_list_mutex);
	वापस err;
पूर्ण

/**
 * fwserial_हटाओ: bus removal function क्रम firewire 'serial' unit devices
 *
 * The corresponding 'peer' क्रम this unit device is हटाओd from the list of
 * peers क्रम the associated fw_serial (which has a 1:1 correspondence with a
 * specअगरic fw_card). If this is the last peer being हटाओd, then trigger
 * the deकाष्ठाion of the underlying TTYs.
 */
अटल व्योम fwserial_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा fwtty_peer *peer = dev_get_drvdata(&unit->device);
	काष्ठा fw_serial *serial = peer->serial;
	पूर्णांक i;

	mutex_lock(&fwserial_list_mutex);
	fwserial_हटाओ_peer(peer);

	अगर (list_empty(&serial->peer_list)) अणु
		/* unlink from the fwserial_list here */
		list_del_rcu(&serial->list);

		debugfs_हटाओ_recursive(serial->debugfs);

		क्रम (i = 0; i < num_ttys; ++i)
			fwserial_बंद_port(fwtty_driver, serial->ports[i]);
		अगर (create_loop_dev)
			fwserial_बंद_port(fwloop_driver, serial->ports[i]);
		kref_put(&serial->kref, fwserial_destroy);
	पूर्ण
	mutex_unlock(&fwserial_list_mutex);
पूर्ण

/**
 * fwserial_update: bus update function क्रम 'firewire' serial unit devices
 *
 * Updates the new node_id and bus generation क्रम this peer. Note that locking
 * is unnecessary; but careful memory barrier usage is important to enक्रमce the
 * load and store order of generation & node_id.
 *
 * The fw-core orders the ग_लिखो of node_id beक्रमe generation in the parent
 * fw_device to ensure that a stale node_id cannot be used with a current
 * bus generation. So the generation value must be पढ़ो beक्रमe the node_id.
 *
 * In turn, this orders the ग_लिखो of node_id beक्रमe generation in the peer to
 * also ensure a stale node_id cannot be used with a current bus generation.
 */
अटल व्योम fwserial_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा fw_device *parent = fw_parent_device(unit);
	काष्ठा fwtty_peer *peer = dev_get_drvdata(&unit->device);
	पूर्णांक generation;

	generation = parent->generation;
	smp_rmb();
	peer->node_id = parent->node_id;
	smp_wmb();
	peer->generation = generation;
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id fwserial_id_table[] = अणु
	अणु
		.match_flags  = IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.specअगरier_id = LINUX_VENDOR_ID,
		.version      = FWSERIAL_VERSION,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा fw_driver fwserial_driver = अणु
	.driver = अणु
		.owner  = THIS_MODULE,
		.name   = KBUILD_MODNAME,
		.bus    = &fw_bus_type,
	पूर्ण,
	.probe    = fwserial_probe,
	.update   = fwserial_update,
	.हटाओ   = fwserial_हटाओ,
	.id_table = fwserial_id_table,
पूर्ण;

#घोषणा FW_UNIT_SPECIFIER(id)	((CSR_SPECIFIER_ID << 24) | (id))
#घोषणा FW_UNIT_VERSION(ver)	((CSR_VERSION << 24) | (ver))
#घोषणा FW_UNIT_ADDRESS(ofs)	(((CSR_OFFSET | CSR_DEPENDENT_INFO) << 24)  \
				 | (((ofs) - CSR_REGISTER_BASE) >> 2))
/* XXX: config ROM definitons could be improved with semi-स्वतःmated offset
 * and length calculation
 */
#घोषणा FW_ROM_LEN(quads)	((quads) << 16)
#घोषणा FW_ROM_DESCRIPTOR(ofs)	(((CSR_LEAF | CSR_DESCRIPTOR) << 24) | (ofs))

काष्ठा fwserial_unit_directory_data अणु
	u32	len_crc;
	u32	unit_specअगरier;
	u32	unit_sw_version;
	u32	unit_addr_offset;
	u32	desc1_ofs;
	u32	desc1_len_crc;
	u32	desc1_data[5];
पूर्ण __packed;

अटल काष्ठा fwserial_unit_directory_data fwserial_unit_directory_data = अणु
	.len_crc = FW_ROM_LEN(4),
	.unit_specअगरier = FW_UNIT_SPECIFIER(LINUX_VENDOR_ID),
	.unit_sw_version = FW_UNIT_VERSION(FWSERIAL_VERSION),
	.desc1_ofs = FW_ROM_DESCRIPTOR(1),
	.desc1_len_crc = FW_ROM_LEN(5),
	.desc1_data = अणु
		0x00000000,			/*   type = text            */
		0x00000000,			/*   enc = ASCII, lang EN   */
		0x4c696e75,			/* 'Linux TTY'              */
		0x78205454,
		0x59000000,
	पूर्ण,
पूर्ण;

अटल काष्ठा fw_descriptor fwserial_unit_directory = अणु
	.length = माप(fwserial_unit_directory_data) / माप(u32),
	.key    = (CSR_सूचीECTORY | CSR_UNIT) << 24,
	.data   = (u32 *)&fwserial_unit_directory_data,
पूर्ण;

/*
 * The management address is in the unit space region but above other known
 * address users (to keep wild ग_लिखोs from causing havoc)
 */
अटल स्थिर काष्ठा fw_address_region fwserial_mgmt_addr_region = अणु
	.start = CSR_REGISTER_BASE + 0x1e0000ULL,
	.end = 0x1000000000000ULL,
पूर्ण;

अटल काष्ठा fw_address_handler fwserial_mgmt_addr_handler;

/**
 * fwserial_handle_plug_req - handle VIRT_CABLE_PLUG request work
 * @work: ptr to peer->work
 *
 * Attempts to complete the VIRT_CABLE_PLUG handshake sequence क्रम this peer.
 *
 * This checks क्रम a collided request-- ie, that a VIRT_CABLE_PLUG request was
 * alपढ़ोy sent to this peer. If so, the collision is resolved by comparing
 * guid values; the loser sends the plug response.
 *
 * Note: अगर an error prevents a response, करोn't करो anything -- the
 * remote will समयout its request.
 */
अटल व्योम fwserial_handle_plug_req(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fwtty_peer *peer = to_peer(work, work);
	काष्ठा virt_plug_params *plug_req = &peer->work_params.plug_req;
	काष्ठा fwtty_port *port;
	काष्ठा fwserial_mgmt_pkt *pkt;
	पूर्णांक rcode;

	pkt = kदो_स्मृति(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस;

	port = fwserial_find_port(peer);

	spin_lock_bh(&peer->lock);

	चयन (peer->state) अणु
	हाल FWPS_NOT_ATTACHED:
		अगर (!port) अणु
			fwtty_err(&peer->unit, "no more ports avail\n");
			fill_plug_rsp_nack(pkt);
		पूर्ण अन्यथा अणु
			peer->port = port;
			fill_plug_rsp_ok(pkt, peer->port);
			peer_set_state(peer, FWPS_PLUG_RESPONDING);
			/* करोn't release claimed port */
			port = शून्य;
		पूर्ण
		अवरोध;

	हाल FWPS_PLUG_PENDING:
		अगर (peer->serial->card->guid > peer->guid)
			जाओ cleanup;

		/* We lost - hijack the alपढ़ोy-claimed port and send ok */
		del_समयr(&peer->समयr);
		fill_plug_rsp_ok(pkt, peer->port);
		peer_set_state(peer, FWPS_PLUG_RESPONDING);
		अवरोध;

	शेष:
		fill_plug_rsp_nack(pkt);
	पूर्ण

	spin_unlock_bh(&peer->lock);
	अगर (port)
		fwserial_release_port(port, false);

	rcode = fwserial_send_mgmt_sync(peer, pkt);

	spin_lock_bh(&peer->lock);
	अगर (peer->state == FWPS_PLUG_RESPONDING) अणु
		अगर (rcode == RCODE_COMPLETE) अणु
			काष्ठा fwtty_port *पंचांगp = peer->port;

			fwserial_virt_plug_complete(peer, plug_req);
			spin_unlock_bh(&peer->lock);

			fwtty_ग_लिखो_port_status(पंचांगp);
			spin_lock_bh(&peer->lock);
		पूर्ण अन्यथा अणु
			fwtty_err(&peer->unit, "PLUG_RSP error (%d)\n", rcode);
			port = peer_revert_state(peer);
		पूर्ण
	पूर्ण
cleanup:
	spin_unlock_bh(&peer->lock);
	अगर (port)
		fwserial_release_port(port, false);
	kमुक्त(pkt);
पूर्ण

अटल व्योम fwserial_handle_unplug_req(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fwtty_peer *peer = to_peer(work, work);
	काष्ठा fwtty_port *port = शून्य;
	काष्ठा fwserial_mgmt_pkt *pkt;
	पूर्णांक rcode;

	pkt = kदो_स्मृति(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस;

	spin_lock_bh(&peer->lock);

	चयन (peer->state) अणु
	हाल FWPS_ATTACHED:
		fill_unplug_rsp_ok(pkt);
		peer_set_state(peer, FWPS_UNPLUG_RESPONDING);
		अवरोध;

	हाल FWPS_UNPLUG_PENDING:
		अगर (peer->serial->card->guid > peer->guid)
			जाओ cleanup;

		/* We lost - send unplug rsp */
		del_समयr(&peer->समयr);
		fill_unplug_rsp_ok(pkt);
		peer_set_state(peer, FWPS_UNPLUG_RESPONDING);
		अवरोध;

	शेष:
		fill_unplug_rsp_nack(pkt);
	पूर्ण

	spin_unlock_bh(&peer->lock);

	rcode = fwserial_send_mgmt_sync(peer, pkt);

	spin_lock_bh(&peer->lock);
	अगर (peer->state == FWPS_UNPLUG_RESPONDING) अणु
		अगर (rcode != RCODE_COMPLETE)
			fwtty_err(&peer->unit, "UNPLUG_RSP error (%d)\n",
				  rcode);
		port = peer_revert_state(peer);
	पूर्ण
cleanup:
	spin_unlock_bh(&peer->lock);
	अगर (port)
		fwserial_release_port(port, true);
	kमुक्त(pkt);
पूर्ण

अटल पूर्णांक fwserial_parse_mgmt_ग_लिखो(काष्ठा fwtty_peer *peer,
				     काष्ठा fwserial_mgmt_pkt *pkt,
				     अचिन्हित दीर्घ दीर्घ addr,
				     माप_प्रकार len)
अणु
	काष्ठा fwtty_port *port = शून्य;
	bool reset = false;
	पूर्णांक rcode;

	अगर (addr != fwserial_mgmt_addr_handler.offset || len < माप(pkt->hdr))
		वापस RCODE_ADDRESS_ERROR;

	अगर (len != be16_to_cpu(pkt->hdr.len) ||
	    len != mgmt_pkt_expected_len(pkt->hdr.code))
		वापस RCODE_DATA_ERROR;

	spin_lock_bh(&peer->lock);
	अगर (peer->state == FWPS_GONE) अणु
		/*
		 * This should never happen - it would mean that the
		 * remote unit that just wrote this transaction was
		 * alपढ़ोy हटाओd from the bus -- and the removal was
		 * processed beक्रमe we rec'd this transaction
		 */
		fwtty_err(&peer->unit, "peer already removed\n");
		spin_unlock_bh(&peer->lock);
		वापस RCODE_ADDRESS_ERROR;
	पूर्ण

	rcode = RCODE_COMPLETE;

	fwtty_dbg(&peer->unit, "mgmt: hdr.code: %04x\n", pkt->hdr.code);

	चयन (be16_to_cpu(pkt->hdr.code) & FWSC_CODE_MASK) अणु
	हाल FWSC_VIRT_CABLE_PLUG:
		अगर (work_pending(&peer->work)) अणु
			fwtty_err(&peer->unit, "plug req: busy\n");
			rcode = RCODE_CONFLICT_ERROR;

		पूर्ण अन्यथा अणु
			peer->work_params.plug_req = pkt->plug_req;
			peer->workfn = fwserial_handle_plug_req;
			queue_work(प्रणाली_unbound_wq, &peer->work);
		पूर्ण
		अवरोध;

	हाल FWSC_VIRT_CABLE_PLUG_RSP:
		अगर (peer->state != FWPS_PLUG_PENDING) अणु
			rcode = RCODE_CONFLICT_ERROR;

		पूर्ण अन्यथा अगर (be16_to_cpu(pkt->hdr.code) & FWSC_RSP_NACK) अणु
			fwtty_notice(&peer->unit, "NACK plug rsp\n");
			port = peer_revert_state(peer);

		पूर्ण अन्यथा अणु
			काष्ठा fwtty_port *पंचांगp = peer->port;

			fwserial_virt_plug_complete(peer, &pkt->plug_rsp);
			spin_unlock_bh(&peer->lock);

			fwtty_ग_लिखो_port_status(पंचांगp);
			spin_lock_bh(&peer->lock);
		पूर्ण
		अवरोध;

	हाल FWSC_VIRT_CABLE_UNPLUG:
		अगर (work_pending(&peer->work)) अणु
			fwtty_err(&peer->unit, "unplug req: busy\n");
			rcode = RCODE_CONFLICT_ERROR;
		पूर्ण अन्यथा अणु
			peer->workfn = fwserial_handle_unplug_req;
			queue_work(प्रणाली_unbound_wq, &peer->work);
		पूर्ण
		अवरोध;

	हाल FWSC_VIRT_CABLE_UNPLUG_RSP:
		अगर (peer->state != FWPS_UNPLUG_PENDING) अणु
			rcode = RCODE_CONFLICT_ERROR;
		पूर्ण अन्यथा अणु
			अगर (be16_to_cpu(pkt->hdr.code) & FWSC_RSP_NACK)
				fwtty_notice(&peer->unit, "NACK unplug?\n");
			port = peer_revert_state(peer);
			reset = true;
		पूर्ण
		अवरोध;

	शेष:
		fwtty_err(&peer->unit, "unknown mgmt code %d\n",
			  be16_to_cpu(pkt->hdr.code));
		rcode = RCODE_DATA_ERROR;
	पूर्ण
	spin_unlock_bh(&peer->lock);

	अगर (port)
		fwserial_release_port(port, reset);

	वापस rcode;
पूर्ण

/**
 * fwserial_mgmt_handler: bus address handler क्रम mgmt requests
 * @parameters: fw_address_callback_t as specअगरied by firewire core पूर्णांकerface
 *
 * This handler is responsible क्रम handling भव cable requests from remotes
 * क्रम all cards.
 */
अटल व्योम fwserial_mgmt_handler(काष्ठा fw_card *card,
				  काष्ठा fw_request *request,
				  पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
				  पूर्णांक generation,
				  अचिन्हित दीर्घ दीर्घ addr,
				  व्योम *data, माप_प्रकार len,
				  व्योम *callback_data)
अणु
	काष्ठा fwserial_mgmt_pkt *pkt = data;
	काष्ठा fwtty_peer *peer;
	पूर्णांक rcode;

	rcu_पढ़ो_lock();
	peer = __fwserial_peer_by_node_id(card, generation, source);
	अगर (!peer) अणु
		fwtty_dbg(card, "peer(%d:%x) not found\n", generation, source);
		__dump_peer_list(card);
		rcode = RCODE_CONFLICT_ERROR;

	पूर्ण अन्यथा अणु
		चयन (tcode) अणु
		हाल TCODE_WRITE_BLOCK_REQUEST:
			rcode = fwserial_parse_mgmt_ग_लिखो(peer, pkt, addr, len);
			अवरोध;

		शेष:
			rcode = RCODE_TYPE_ERROR;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	fw_send_response(card, request, rcode);
पूर्ण

अटल पूर्णांक __init fwserial_init(व्योम)
अणु
	पूर्णांक err, num_loops = !!(create_loop_dev);

	/* XXX: placeholder क्रम a "firewire" debugfs node */
	fwserial_debugfs = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	/* num_ttys/num_ports must not be set above the अटल alloc avail */
	अगर (num_ttys + num_loops > MAX_CARD_PORTS)
		num_ttys = MAX_CARD_PORTS - num_loops;

	num_ports = num_ttys + num_loops;

	fwtty_driver = tty_alloc_driver(MAX_TOTAL_PORTS, TTY_DRIVER_REAL_RAW
					| TTY_DRIVER_DYNAMIC_DEV);
	अगर (IS_ERR(fwtty_driver)) अणु
		err = PTR_ERR(fwtty_driver);
		जाओ हटाओ_debugfs;
	पूर्ण

	fwtty_driver->driver_name	= KBUILD_MODNAME;
	fwtty_driver->name		= tty_dev_name;
	fwtty_driver->major		= 0;
	fwtty_driver->minor_start	= 0;
	fwtty_driver->type		= TTY_DRIVER_TYPE_SERIAL;
	fwtty_driver->subtype		= SERIAL_TYPE_NORMAL;
	fwtty_driver->init_termios	    = tty_std_termios;
	fwtty_driver->init_termios.c_cflag  |= CLOCAL;
	tty_set_operations(fwtty_driver, &fwtty_ops);

	err = tty_रेजिस्टर_driver(fwtty_driver);
	अगर (err) अणु
		pr_err("register tty driver failed (%d)\n", err);
		जाओ put_tty;
	पूर्ण

	अगर (create_loop_dev) अणु
		fwloop_driver = tty_alloc_driver(MAX_TOTAL_PORTS / num_ports,
						 TTY_DRIVER_REAL_RAW
						 | TTY_DRIVER_DYNAMIC_DEV);
		अगर (IS_ERR(fwloop_driver)) अणु
			err = PTR_ERR(fwloop_driver);
			जाओ unरेजिस्टर_driver;
		पूर्ण

		fwloop_driver->driver_name	= KBUILD_MODNAME "_loop";
		fwloop_driver->name		= loop_dev_name;
		fwloop_driver->major		= 0;
		fwloop_driver->minor_start	= 0;
		fwloop_driver->type		= TTY_DRIVER_TYPE_SERIAL;
		fwloop_driver->subtype		= SERIAL_TYPE_NORMAL;
		fwloop_driver->init_termios	    = tty_std_termios;
		fwloop_driver->init_termios.c_cflag  |= CLOCAL;
		tty_set_operations(fwloop_driver, &fwloop_ops);

		err = tty_रेजिस्टर_driver(fwloop_driver);
		अगर (err) अणु
			pr_err("register loop driver failed (%d)\n", err);
			जाओ put_loop;
		पूर्ण
	पूर्ण

	fwtty_txn_cache = kmem_cache_create("fwtty_txn_cache",
					    माप(काष्ठा fwtty_transaction),
					    0, 0, शून्य);
	अगर (!fwtty_txn_cache) अणु
		err = -ENOMEM;
		जाओ unरेजिस्टर_loop;
	पूर्ण

	/*
	 * Ideally, this address handler would be रेजिस्टरed per local node
	 * (rather than the same handler क्रम all local nodes). However,
	 * since the firewire core requires the config rom descriptor *beक्रमe*
	 * the local unit device(s) are created, a single management handler
	 * must suffice क्रम all local serial units.
	 */
	fwserial_mgmt_addr_handler.length = माप(काष्ठा fwserial_mgmt_pkt);
	fwserial_mgmt_addr_handler.address_callback = fwserial_mgmt_handler;

	err = fw_core_add_address_handler(&fwserial_mgmt_addr_handler,
					  &fwserial_mgmt_addr_region);
	अगर (err) अणु
		pr_err("add management handler failed (%d)\n", err);
		जाओ destroy_cache;
	पूर्ण

	fwserial_unit_directory_data.unit_addr_offset =
		FW_UNIT_ADDRESS(fwserial_mgmt_addr_handler.offset);
	err = fw_core_add_descriptor(&fwserial_unit_directory);
	अगर (err) अणु
		pr_err("add unit descriptor failed (%d)\n", err);
		जाओ हटाओ_handler;
	पूर्ण

	err = driver_रेजिस्टर(&fwserial_driver.driver);
	अगर (err) अणु
		pr_err("register fwserial driver failed (%d)\n", err);
		जाओ हटाओ_descriptor;
	पूर्ण

	वापस 0;

हटाओ_descriptor:
	fw_core_हटाओ_descriptor(&fwserial_unit_directory);
हटाओ_handler:
	fw_core_हटाओ_address_handler(&fwserial_mgmt_addr_handler);
destroy_cache:
	kmem_cache_destroy(fwtty_txn_cache);
unरेजिस्टर_loop:
	अगर (create_loop_dev)
		tty_unरेजिस्टर_driver(fwloop_driver);
put_loop:
	अगर (create_loop_dev)
		put_tty_driver(fwloop_driver);
unरेजिस्टर_driver:
	tty_unरेजिस्टर_driver(fwtty_driver);
put_tty:
	put_tty_driver(fwtty_driver);
हटाओ_debugfs:
	debugfs_हटाओ_recursive(fwserial_debugfs);

	वापस err;
पूर्ण

अटल व्योम __निकास fwserial_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&fwserial_driver.driver);
	fw_core_हटाओ_descriptor(&fwserial_unit_directory);
	fw_core_हटाओ_address_handler(&fwserial_mgmt_addr_handler);
	kmem_cache_destroy(fwtty_txn_cache);
	अगर (create_loop_dev) अणु
		tty_unरेजिस्टर_driver(fwloop_driver);
		put_tty_driver(fwloop_driver);
	पूर्ण
	tty_unरेजिस्टर_driver(fwtty_driver);
	put_tty_driver(fwtty_driver);
	debugfs_हटाओ_recursive(fwserial_debugfs);
पूर्ण

module_init(fwserial_init);
module_निकास(fwserial_निकास);

MODULE_AUTHOR("Peter Hurley (peter@hurleysoftware.com)");
MODULE_DESCRIPTION("FireWire Serial TTY Driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(ieee1394, fwserial_id_table);
MODULE_PARM_DESC(ttys, "Number of ttys to create for each local firewire node");
MODULE_PARM_DESC(स्वतः, "Auto-connect a tty to each firewire node discovered");
MODULE_PARM_DESC(loop, "Create a loopback device, fwloop<n>, with ttys");
