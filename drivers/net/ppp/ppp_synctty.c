<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PPP synchronous tty channel driver क्रम Linux.
 *
 * This is a ppp channel driver that can be used with tty device drivers
 * that are frame oriented, such as synchronous HDLC devices.
 *
 * Complete PPP frames without encoding/decoding are exchanged between
 * the channel driver and the device driver.
 *
 * The async map IOCTL codes are implemented to keep the user mode
 * applications happy अगर they call them. Synchronous PPP करोes not use
 * the async maps.
 *
 * Copyright 1999 Paul Mackerras.
 *
 * Also touched by the grubby hands of Paul Fulghum paulkf@microgate.com
 *
 * This driver provides the encapsulation and framing क्रम sending
 * and receiving PPP frames over sync serial lines.  It relies on
 * the generic PPP layer to give it frames to send and to process
 * received frames.  It implements the PPP line discipline.
 *
 * Part of the code in this driver was inspired by the old async-only
 * PPP driver, written by Michael Callahan and Al Longyear, and
 * subsequently hacked by Paul Mackerras.
 *
 * ==खाताVERSION 20040616==
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tty.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/uaccess.h>

#घोषणा PPP_VERSION	"2.4.2"

/* Structure क्रम storing local state. */
काष्ठा syncppp अणु
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	rbits;
	पूर्णांक		mru;
	spinlock_t	xmit_lock;
	spinlock_t	recv_lock;
	अचिन्हित दीर्घ	xmit_flags;
	u32		xaccm[8];
	u32		raccm;
	अचिन्हित पूर्णांक	bytes_sent;
	अचिन्हित पूर्णांक	bytes_rcvd;

	काष्ठा sk_buff	*tpkt;
	अचिन्हित दीर्घ	last_xmit;

	काष्ठा sk_buff_head rqueue;

	काष्ठा tasklet_काष्ठा tsk;

	refcount_t	refcnt;
	काष्ठा completion dead_cmp;
	काष्ठा ppp_channel chan;	/* पूर्णांकerface to generic ppp layer */
पूर्ण;

/* Bit numbers in xmit_flags */
#घोषणा XMIT_WAKEUP	0
#घोषणा XMIT_FULL	1

/* Bits in rbits */
#घोषणा SC_RCV_BITS	(SC_RCV_B7_1|SC_RCV_B7_0|SC_RCV_ODDP|SC_RCV_EVNP)

#घोषणा PPPSYNC_MAX_RQLEN	32	/* arbitrary */

/*
 * Prototypes.
 */
अटल काष्ठा sk_buff* ppp_sync_txmunge(काष्ठा syncppp *ap, काष्ठा sk_buff *);
अटल पूर्णांक ppp_sync_send(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb);
अटल पूर्णांक ppp_sync_ioctl(काष्ठा ppp_channel *chan, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg);
अटल व्योम ppp_sync_process(काष्ठा tasklet_काष्ठा *t);
अटल पूर्णांक ppp_sync_push(काष्ठा syncppp *ap);
अटल व्योम ppp_sync_flush_output(काष्ठा syncppp *ap);
अटल व्योम ppp_sync_input(काष्ठा syncppp *ap, स्थिर अचिन्हित अक्षर *buf,
			   अक्षर *flags, पूर्णांक count);

अटल स्थिर काष्ठा ppp_channel_ops sync_ops = अणु
	.start_xmit = ppp_sync_send,
	.ioctl      = ppp_sync_ioctl,
पूर्ण;

/*
 * Utility procedure to prपूर्णांक a buffer in hex/ascii
 */
अटल व्योम
ppp_prपूर्णांक_buffer (स्थिर अक्षर *name, स्थिर __u8 *buf, पूर्णांक count)
अणु
	अगर (name != शून्य)
		prपूर्णांकk(KERN_DEBUG "ppp_synctty: %s, count = %d\n", name, count);

	prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_NONE, buf, count);
पूर्ण


/*
 * Routines implementing the synchronous PPP line discipline.
 */

/*
 * We have a potential race on dereferencing tty->disc_data,
 * because the tty layer provides no locking at all - thus one
 * cpu could be running ppp_synctty_receive जबतक another
 * calls ppp_synctty_बंद, which zeroes tty->disc_data and
 * मुक्तs the memory that ppp_synctty_receive is using.  The best
 * way to fix this is to use a rwlock in the tty काष्ठा, but क्रम now
 * we use a single global rwlock क्रम all ttys in ppp line discipline.
 *
 * FIXME: Fixed in tty_io nowadays.
 */
अटल DEFINE_RWLOCK(disc_data_lock);

अटल काष्ठा syncppp *sp_get(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा syncppp *ap;

	पढ़ो_lock(&disc_data_lock);
	ap = tty->disc_data;
	अगर (ap != शून्य)
		refcount_inc(&ap->refcnt);
	पढ़ो_unlock(&disc_data_lock);
	वापस ap;
पूर्ण

अटल व्योम sp_put(काष्ठा syncppp *ap)
अणु
	अगर (refcount_dec_and_test(&ap->refcnt))
		complete(&ap->dead_cmp);
पूर्ण

/*
 * Called when a tty is put पूर्णांकo sync-PPP line discipline.
 */
अटल पूर्णांक
ppp_sync_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा syncppp *ap;
	पूर्णांक err;
	पूर्णांक speed;

	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;

	ap = kzalloc(माप(*ap), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!ap)
		जाओ out;

	/* initialize the syncppp काष्ठाure */
	ap->tty = tty;
	ap->mru = PPP_MRU;
	spin_lock_init(&ap->xmit_lock);
	spin_lock_init(&ap->recv_lock);
	ap->xaccm[0] = ~0U;
	ap->xaccm[3] = 0x60000000U;
	ap->raccm = ~0U;

	skb_queue_head_init(&ap->rqueue);
	tasklet_setup(&ap->tsk, ppp_sync_process);

	refcount_set(&ap->refcnt, 1);
	init_completion(&ap->dead_cmp);

	ap->chan.निजी = ap;
	ap->chan.ops = &sync_ops;
	ap->chan.mtu = PPP_MRU;
	ap->chan.hdrlen = 2;	/* क्रम A/C bytes */
	speed = tty_get_baud_rate(tty);
	ap->chan.speed = speed;
	err = ppp_रेजिस्टर_channel(&ap->chan);
	अगर (err)
		जाओ out_मुक्त;

	tty->disc_data = ap;
	tty->receive_room = 65536;
	वापस 0;

 out_मुक्त:
	kमुक्त(ap);
 out:
	वापस err;
पूर्ण

/*
 * Called when the tty is put पूर्णांकo another line discipline
 * or it hangs up.  We have to रुको क्रम any cpu currently
 * executing in any of the other ppp_synctty_* routines to
 * finish beक्रमe we can call ppp_unरेजिस्टर_channel and मुक्त
 * the syncppp काष्ठा.  This routine must be called from
 * process context, not पूर्णांकerrupt or softirq context.
 */
अटल व्योम
ppp_sync_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा syncppp *ap;

	ग_लिखो_lock_irq(&disc_data_lock);
	ap = tty->disc_data;
	tty->disc_data = शून्य;
	ग_लिखो_unlock_irq(&disc_data_lock);
	अगर (!ap)
		वापस;

	/*
	 * We have now ensured that nobody can start using ap from now
	 * on, but we have to रुको क्रम all existing users to finish.
	 * Note that ppp_unरेजिस्टर_channel ensures that no calls to
	 * our channel ops (i.e. ppp_sync_send/ioctl) are in progress
	 * by the समय it वापसs.
	 */
	अगर (!refcount_dec_and_test(&ap->refcnt))
		रुको_क्रम_completion(&ap->dead_cmp);
	tasklet_समाप्त(&ap->tsk);

	ppp_unरेजिस्टर_channel(&ap->chan);
	skb_queue_purge(&ap->rqueue);
	kमुक्त_skb(ap->tpkt);
	kमुक्त(ap);
पूर्ण

/*
 * Called on tty hangup in process context.
 *
 * Wait क्रम I/O to driver to complete and unरेजिस्टर PPP channel.
 * This is alपढ़ोy करोne by the बंद routine, so just call that.
 */
अटल पूर्णांक ppp_sync_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	ppp_sync_बंद(tty);
	वापस 0;
पूर्ण

/*
 * Read करोes nothing - no data is ever available this way.
 * Pppd पढ़ोs and ग_लिखोs packets via /dev/ppp instead.
 */
अटल sमाप_प्रकार
ppp_sync_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
	      अचिन्हित अक्षर *buf, माप_प्रकार count,
	      व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	वापस -EAGAIN;
पूर्ण

/*
 * Write on the tty करोes nothing, the packets all come in
 * from the ppp generic stuff.
 */
अटल sमाप_प्रकार
ppp_sync_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count)
अणु
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक
ppp_synctty_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा syncppp *ap = sp_get(tty);
	पूर्णांक __user *p = (पूर्णांक __user *)arg;
	पूर्णांक err, val;

	अगर (!ap)
		वापस -ENXIO;
	err = -EFAULT;
	चयन (cmd) अणु
	हाल PPPIOCGCHAN:
		err = -EFAULT;
		अगर (put_user(ppp_channel_index(&ap->chan), p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGUNIT:
		err = -EFAULT;
		अगर (put_user(ppp_unit_number(&ap->chan), p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल TCFLSH:
		/* flush our buffers and the serial port's buffer */
		अगर (arg == TCIOFLUSH || arg == TCOFLUSH)
			ppp_sync_flush_output(ap);
		err = n_tty_ioctl_helper(tty, file, cmd, arg);
		अवरोध;

	हाल FIONREAD:
		val = 0;
		अगर (put_user(val, p))
			अवरोध;
		err = 0;
		अवरोध;

	शेष:
		err = tty_mode_ioctl(tty, file, cmd, arg);
		अवरोध;
	पूर्ण

	sp_put(ap);
	वापस err;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t
ppp_sync_poll(काष्ठा tty_काष्ठा *tty, काष्ठा file *file, poll_table *रुको)
अणु
	वापस 0;
पूर्ण

/* May sleep, करोn't call from पूर्णांकerrupt level or with पूर्णांकerrupts disabled */
अटल व्योम
ppp_sync_receive(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
		  अक्षर *cflags, पूर्णांक count)
अणु
	काष्ठा syncppp *ap = sp_get(tty);
	अचिन्हित दीर्घ flags;

	अगर (!ap)
		वापस;
	spin_lock_irqsave(&ap->recv_lock, flags);
	ppp_sync_input(ap, buf, cflags, count);
	spin_unlock_irqrestore(&ap->recv_lock, flags);
	अगर (!skb_queue_empty(&ap->rqueue))
		tasklet_schedule(&ap->tsk);
	sp_put(ap);
	tty_unthrottle(tty);
पूर्ण

अटल व्योम
ppp_sync_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा syncppp *ap = sp_get(tty);

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	अगर (!ap)
		वापस;
	set_bit(XMIT_WAKEUP, &ap->xmit_flags);
	tasklet_schedule(&ap->tsk);
	sp_put(ap);
पूर्ण


अटल काष्ठा tty_ldisc_ops ppp_sync_ldisc = अणु
	.owner	= THIS_MODULE,
	.name	= "pppsync",
	.खोलो	= ppp_sync_खोलो,
	.बंद	= ppp_sync_बंद,
	.hangup	= ppp_sync_hangup,
	.पढ़ो	= ppp_sync_पढ़ो,
	.ग_लिखो	= ppp_sync_ग_लिखो,
	.ioctl	= ppp_synctty_ioctl,
	.poll	= ppp_sync_poll,
	.receive_buf = ppp_sync_receive,
	.ग_लिखो_wakeup = ppp_sync_wakeup,
पूर्ण;

अटल पूर्णांक __init
ppp_sync_init(व्योम)
अणु
	पूर्णांक err;

	err = tty_रेजिस्टर_ldisc(N_SYNC_PPP, &ppp_sync_ldisc);
	अगर (err != 0)
		prपूर्णांकk(KERN_ERR "PPP_sync: error %d registering line disc.\n",
		       err);
	वापस err;
पूर्ण

/*
 * The following routines provide the PPP channel पूर्णांकerface.
 */
अटल पूर्णांक
ppp_sync_ioctl(काष्ठा ppp_channel *chan, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा syncppp *ap = chan->निजी;
	पूर्णांक err, val;
	u32 accm[8];
	व्योम __user *argp = (व्योम __user *)arg;
	u32 __user *p = argp;

	err = -EFAULT;
	चयन (cmd) अणु
	हाल PPPIOCGFLAGS:
		val = ap->flags | ap->rbits;
		अगर (put_user(val, (पूर्णांक __user *) argp))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSFLAGS:
		अगर (get_user(val, (पूर्णांक __user *) argp))
			अवरोध;
		ap->flags = val & ~SC_RCV_BITS;
		spin_lock_irq(&ap->recv_lock);
		ap->rbits = val & SC_RCV_BITS;
		spin_unlock_irq(&ap->recv_lock);
		err = 0;
		अवरोध;

	हाल PPPIOCGASYNCMAP:
		अगर (put_user(ap->xaccm[0], p))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSASYNCMAP:
		अगर (get_user(ap->xaccm[0], p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGRASYNCMAP:
		अगर (put_user(ap->raccm, p))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSRASYNCMAP:
		अगर (get_user(ap->raccm, p))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGXASYNCMAP:
		अगर (copy_to_user(argp, ap->xaccm, माप(ap->xaccm)))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSXASYNCMAP:
		अगर (copy_from_user(accm, argp, माप(accm)))
			अवरोध;
		accm[2] &= ~0x40000000U;	/* can't escape 0x5e */
		accm[3] |= 0x60000000U;		/* must escape 0x7d, 0x7e */
		स_नकल(ap->xaccm, accm, माप(ap->xaccm));
		err = 0;
		अवरोध;

	हाल PPPIOCGMRU:
		अगर (put_user(ap->mru, (पूर्णांक __user *) argp))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSMRU:
		अगर (get_user(val, (पूर्णांक __user *) argp))
			अवरोध;
		अगर (val < PPP_MRU)
			val = PPP_MRU;
		ap->mru = val;
		err = 0;
		अवरोध;

	शेष:
		err = -ENOTTY;
	पूर्ण
	वापस err;
पूर्ण

/*
 * This is called at softirq level to deliver received packets
 * to the ppp_generic code, and to tell the ppp_generic code
 * अगर we can accept more output now.
 */
अटल व्योम ppp_sync_process(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा syncppp *ap = from_tasklet(ap, t, tsk);
	काष्ठा sk_buff *skb;

	/* process received packets */
	जबतक ((skb = skb_dequeue(&ap->rqueue)) != शून्य) अणु
		अगर (skb->len == 0) अणु
			/* zero length buffers indicate error */
			ppp_input_error(&ap->chan, 0);
			kमुक्त_skb(skb);
		पूर्ण
		अन्यथा
			ppp_input(&ap->chan, skb);
	पूर्ण

	/* try to push more stuff out */
	अगर (test_bit(XMIT_WAKEUP, &ap->xmit_flags) && ppp_sync_push(ap))
		ppp_output_wakeup(&ap->chan);
पूर्ण

/*
 * Procedures क्रम encapsulation and framing.
 */

अटल काष्ठा sk_buff*
ppp_sync_txmunge(काष्ठा syncppp *ap, काष्ठा sk_buff *skb)
अणु
	पूर्णांक proto;
	अचिन्हित अक्षर *data;
	पूर्णांक islcp;

	data  = skb->data;
	proto = get_unaligned_be16(data);

	/* LCP packets with codes between 1 (configure-request)
	 * and 7 (code-reject) must be sent as though no options
	 * have been negotiated.
	 */
	islcp = proto == PPP_LCP && 1 <= data[2] && data[2] <= 7;

	/* compress protocol field अगर option enabled */
	अगर (data[0] == 0 && (ap->flags & SC_COMP_PROT) && !islcp)
		skb_pull(skb,1);

	/* prepend address/control fields अगर necessary */
	अगर ((ap->flags & SC_COMP_AC) == 0 || islcp) अणु
		अगर (skb_headroom(skb) < 2) अणु
			काष्ठा sk_buff *npkt = dev_alloc_skb(skb->len + 2);
			अगर (npkt == शून्य) अणु
				kमुक्त_skb(skb);
				वापस शून्य;
			पूर्ण
			skb_reserve(npkt,2);
			skb_copy_from_linear_data(skb,
				      skb_put(npkt, skb->len), skb->len);
			consume_skb(skb);
			skb = npkt;
		पूर्ण
		skb_push(skb,2);
		skb->data[0] = PPP_ALLSTATIONS;
		skb->data[1] = PPP_UI;
	पूर्ण

	ap->last_xmit = jअगरfies;

	अगर (skb && ap->flags & SC_LOG_OUTPKT)
		ppp_prपूर्णांक_buffer ("send buffer", skb->data, skb->len);

	वापस skb;
पूर्ण

/*
 * Transmit-side routines.
 */

/*
 * Send a packet to the peer over an sync tty line.
 * Returns 1 अगरf the packet was accepted.
 * If the packet was not accepted, we will call ppp_output_wakeup
 * at some later समय.
 */
अटल पूर्णांक
ppp_sync_send(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा syncppp *ap = chan->निजी;

	ppp_sync_push(ap);

	अगर (test_and_set_bit(XMIT_FULL, &ap->xmit_flags))
		वापस 0;	/* alपढ़ोy full */
	skb = ppp_sync_txmunge(ap, skb);
	अगर (skb != शून्य)
		ap->tpkt = skb;
	अन्यथा
		clear_bit(XMIT_FULL, &ap->xmit_flags);

	ppp_sync_push(ap);
	वापस 1;
पूर्ण

/*
 * Push as much data as possible out to the tty.
 */
अटल पूर्णांक
ppp_sync_push(काष्ठा syncppp *ap)
अणु
	पूर्णांक sent, करोne = 0;
	काष्ठा tty_काष्ठा *tty = ap->tty;
	पूर्णांक tty_stuffed = 0;

	अगर (!spin_trylock_bh(&ap->xmit_lock))
		वापस 0;
	क्रम (;;) अणु
		अगर (test_and_clear_bit(XMIT_WAKEUP, &ap->xmit_flags))
			tty_stuffed = 0;
		अगर (!tty_stuffed && ap->tpkt) अणु
			set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
			sent = tty->ops->ग_लिखो(tty, ap->tpkt->data, ap->tpkt->len);
			अगर (sent < 0)
				जाओ flush;	/* error, e.g. loss of CD */
			अगर (sent < ap->tpkt->len) अणु
				tty_stuffed = 1;
			पूर्ण अन्यथा अणु
				consume_skb(ap->tpkt);
				ap->tpkt = शून्य;
				clear_bit(XMIT_FULL, &ap->xmit_flags);
				करोne = 1;
			पूर्ण
			जारी;
		पूर्ण
		/* haven't made any progress */
		spin_unlock_bh(&ap->xmit_lock);
		अगर (!(test_bit(XMIT_WAKEUP, &ap->xmit_flags) ||
		      (!tty_stuffed && ap->tpkt)))
			अवरोध;
		अगर (!spin_trylock_bh(&ap->xmit_lock))
			अवरोध;
	पूर्ण
	वापस करोne;

flush:
	अगर (ap->tpkt) अणु
		kमुक्त_skb(ap->tpkt);
		ap->tpkt = शून्य;
		clear_bit(XMIT_FULL, &ap->xmit_flags);
		करोne = 1;
	पूर्ण
	spin_unlock_bh(&ap->xmit_lock);
	वापस करोne;
पूर्ण

/*
 * Flush output from our पूर्णांकernal buffers.
 * Called क्रम the TCFLSH ioctl.
 */
अटल व्योम
ppp_sync_flush_output(काष्ठा syncppp *ap)
अणु
	पूर्णांक करोne = 0;

	spin_lock_bh(&ap->xmit_lock);
	अगर (ap->tpkt != शून्य) अणु
		kमुक्त_skb(ap->tpkt);
		ap->tpkt = शून्य;
		clear_bit(XMIT_FULL, &ap->xmit_flags);
		करोne = 1;
	पूर्ण
	spin_unlock_bh(&ap->xmit_lock);
	अगर (करोne)
		ppp_output_wakeup(&ap->chan);
पूर्ण

/*
 * Receive-side routines.
 */

/* called when the tty driver has data क्रम us.
 *
 * Data is frame oriented: each call to ppp_sync_input is considered
 * a whole frame. If the 1st flag byte is non-zero then the whole
 * frame is considered to be in error and is tossed.
 */
अटल व्योम
ppp_sync_input(काष्ठा syncppp *ap, स्थिर अचिन्हित अक्षर *buf,
		अक्षर *flags, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *p;

	अगर (count == 0)
		वापस;

	अगर (ap->flags & SC_LOG_INPKT)
		ppp_prपूर्णांक_buffer ("receive buffer", buf, count);

	/* stuff the अक्षरs in the skb */
	skb = dev_alloc_skb(ap->mru + PPP_HDRLEN + 2);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "PPPsync: no memory (input pkt)\n");
		जाओ err;
	पूर्ण
	/* Try to get the payload 4-byte aligned */
	अगर (buf[0] != PPP_ALLSTATIONS)
		skb_reserve(skb, 2 + (buf[0] & 1));

	अगर (flags && *flags) अणु
		/* error flag set, ignore frame */
		जाओ err;
	पूर्ण अन्यथा अगर (count > skb_tailroom(skb)) अणु
		/* packet overflowed MRU */
		जाओ err;
	पूर्ण

	skb_put_data(skb, buf, count);

	/* strip address/control field अगर present */
	p = skb->data;
	अगर (p[0] == PPP_ALLSTATIONS && p[1] == PPP_UI) अणु
		/* chop off address/control */
		अगर (skb->len < 3)
			जाओ err;
		p = skb_pull(skb, 2);
	पूर्ण

	/* PPP packet length should be >= 2 bytes when protocol field is not
	 * compressed.
	 */
	अगर (!(p[0] & 0x01) && skb->len < 2)
		जाओ err;

	/* queue the frame to be processed */
	skb_queue_tail(&ap->rqueue, skb);
	वापस;

err:
	/* queue zero length packet as error indication */
	अगर (skb || (skb = dev_alloc_skb(0))) अणु
		skb_trim(skb, 0);
		skb_queue_tail(&ap->rqueue, skb);
	पूर्ण
पूर्ण

अटल व्योम __निकास
ppp_sync_cleanup(व्योम)
अणु
	अगर (tty_unरेजिस्टर_ldisc(N_SYNC_PPP) != 0)
		prपूर्णांकk(KERN_ERR "failed to unregister Sync PPP line discipline\n");
पूर्ण

module_init(ppp_sync_init);
module_निकास(ppp_sync_cleanup);
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_SYNC_PPP);
