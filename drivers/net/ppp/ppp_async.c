<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PPP async serial channel driver क्रम Linux.
 *
 * Copyright 1999 Paul Mackerras.
 *
 * This driver provides the encapsulation and framing क्रम sending
 * and receiving PPP frames over async serial lines.  It relies on
 * the generic PPP layer to give it frames to send and to process
 * received frames.  It implements the PPP line discipline.
 *
 * Part of the code in this driver was inspired by the old async-only
 * PPP driver, written by Michael Callahan and Al Longyear, and
 * subsequently hacked by Paul Mackerras.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tty.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/माला.स>

#घोषणा PPP_VERSION	"2.4.2"

#घोषणा Oबफ_मानE	4096

/* Structure क्रम storing local state. */
काष्ठा asyncppp अणु
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	state;
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
	पूर्णांक		tpkt_pos;
	u16		tfcs;
	अचिन्हित अक्षर	*optr;
	अचिन्हित अक्षर	*olim;
	अचिन्हित दीर्घ	last_xmit;

	काष्ठा sk_buff	*rpkt;
	पूर्णांक		lcp_fcs;
	काष्ठा sk_buff_head rqueue;

	काष्ठा tasklet_काष्ठा tsk;

	refcount_t	refcnt;
	काष्ठा completion dead;
	काष्ठा ppp_channel chan;	/* पूर्णांकerface to generic ppp layer */
	अचिन्हित अक्षर	obuf[Oबफ_मानE];
पूर्ण;

/* Bit numbers in xmit_flags */
#घोषणा XMIT_WAKEUP	0
#घोषणा XMIT_FULL	1
#घोषणा XMIT_BUSY	2

/* State bits */
#घोषणा SC_TOSS		1
#घोषणा SC_ESCAPE	2
#घोषणा SC_PREV_ERROR	4

/* Bits in rbits */
#घोषणा SC_RCV_BITS	(SC_RCV_B7_1|SC_RCV_B7_0|SC_RCV_ODDP|SC_RCV_EVNP)

अटल पूर्णांक flag_समय = HZ;
module_param(flag_समय, पूर्णांक, 0);
MODULE_PARM_DESC(flag_समय, "ppp_async: interval between flagged packets (in clock ticks)");
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_PPP);

/*
 * Prototypes.
 */
अटल पूर्णांक ppp_async_encode(काष्ठा asyncppp *ap);
अटल पूर्णांक ppp_async_send(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb);
अटल पूर्णांक ppp_async_push(काष्ठा asyncppp *ap);
अटल व्योम ppp_async_flush_output(काष्ठा asyncppp *ap);
अटल व्योम ppp_async_input(काष्ठा asyncppp *ap, स्थिर अचिन्हित अक्षर *buf,
			    अक्षर *flags, पूर्णांक count);
अटल पूर्णांक ppp_async_ioctl(काष्ठा ppp_channel *chan, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg);
अटल व्योम ppp_async_process(काष्ठा tasklet_काष्ठा *t);

अटल व्योम async_lcp_peek(काष्ठा asyncppp *ap, अचिन्हित अक्षर *data,
			   पूर्णांक len, पूर्णांक inbound);

अटल स्थिर काष्ठा ppp_channel_ops async_ops = अणु
	.start_xmit = ppp_async_send,
	.ioctl      = ppp_async_ioctl,
पूर्ण;

/*
 * Routines implementing the PPP line discipline.
 */

/*
 * We have a potential race on dereferencing tty->disc_data,
 * because the tty layer provides no locking at all - thus one
 * cpu could be running ppp_asynctty_receive जबतक another
 * calls ppp_asynctty_बंद, which zeroes tty->disc_data and
 * मुक्तs the memory that ppp_asynctty_receive is using.  The best
 * way to fix this is to use a rwlock in the tty काष्ठा, but क्रम now
 * we use a single global rwlock क्रम all ttys in ppp line discipline.
 *
 * FIXME: this is no दीर्घer true. The _बंद path क्रम the ldisc is
 * now guaranteed to be sane.
 */
अटल DEFINE_RWLOCK(disc_data_lock);

अटल काष्ठा asyncppp *ap_get(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा asyncppp *ap;

	पढ़ो_lock(&disc_data_lock);
	ap = tty->disc_data;
	अगर (ap != शून्य)
		refcount_inc(&ap->refcnt);
	पढ़ो_unlock(&disc_data_lock);
	वापस ap;
पूर्ण

अटल व्योम ap_put(काष्ठा asyncppp *ap)
अणु
	अगर (refcount_dec_and_test(&ap->refcnt))
		complete(&ap->dead);
पूर्ण

/*
 * Called when a tty is put पूर्णांकo PPP line discipline. Called in process
 * context.
 */
अटल पूर्णांक
ppp_asynctty_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा asyncppp *ap;
	पूर्णांक err;
	पूर्णांक speed;

	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;

	err = -ENOMEM;
	ap = kzalloc(माप(*ap), GFP_KERNEL);
	अगर (!ap)
		जाओ out;

	/* initialize the asyncppp काष्ठाure */
	ap->tty = tty;
	ap->mru = PPP_MRU;
	spin_lock_init(&ap->xmit_lock);
	spin_lock_init(&ap->recv_lock);
	ap->xaccm[0] = ~0U;
	ap->xaccm[3] = 0x60000000U;
	ap->raccm = ~0U;
	ap->optr = ap->obuf;
	ap->olim = ap->obuf;
	ap->lcp_fcs = -1;

	skb_queue_head_init(&ap->rqueue);
	tasklet_setup(&ap->tsk, ppp_async_process);

	refcount_set(&ap->refcnt, 1);
	init_completion(&ap->dead);

	ap->chan.निजी = ap;
	ap->chan.ops = &async_ops;
	ap->chan.mtu = PPP_MRU;
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
 * executing in any of the other ppp_asynctty_* routines to
 * finish beक्रमe we can call ppp_unरेजिस्टर_channel and मुक्त
 * the asyncppp काष्ठा.  This routine must be called from
 * process context, not पूर्णांकerrupt or softirq context.
 */
अटल व्योम
ppp_asynctty_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा asyncppp *ap;

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
	 * our channel ops (i.e. ppp_async_send/ioctl) are in progress
	 * by the समय it वापसs.
	 */
	अगर (!refcount_dec_and_test(&ap->refcnt))
		रुको_क्रम_completion(&ap->dead);
	tasklet_समाप्त(&ap->tsk);

	ppp_unरेजिस्टर_channel(&ap->chan);
	kमुक्त_skb(ap->rpkt);
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
अटल पूर्णांक ppp_asynctty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	ppp_asynctty_बंद(tty);
	वापस 0;
पूर्ण

/*
 * Read करोes nothing - no data is ever available this way.
 * Pppd पढ़ोs and ग_लिखोs packets via /dev/ppp instead.
 */
अटल sमाप_प्रकार
ppp_asynctty_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
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
ppp_asynctty_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		   स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count)
अणु
	वापस -EAGAIN;
पूर्ण

/*
 * Called in process context only. May be re-entered by multiple
 * ioctl calling thपढ़ोs.
 */

अटल पूर्णांक
ppp_asynctty_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा asyncppp *ap = ap_get(tty);
	पूर्णांक err, val;
	पूर्णांक __user *p = (पूर्णांक __user *)arg;

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
			ppp_async_flush_output(ap);
		err = n_tty_ioctl_helper(tty, file, cmd, arg);
		अवरोध;

	हाल FIONREAD:
		val = 0;
		अगर (put_user(val, p))
			अवरोध;
		err = 0;
		अवरोध;

	शेष:
		/* Try the various mode ioctls */
		err = tty_mode_ioctl(tty, file, cmd, arg);
	पूर्ण

	ap_put(ap);
	वापस err;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t
ppp_asynctty_poll(काष्ठा tty_काष्ठा *tty, काष्ठा file *file, poll_table *रुको)
अणु
	वापस 0;
पूर्ण

/* May sleep, करोn't call from पूर्णांकerrupt level or with पूर्णांकerrupts disabled */
अटल व्योम
ppp_asynctty_receive(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
		  अक्षर *cflags, पूर्णांक count)
अणु
	काष्ठा asyncppp *ap = ap_get(tty);
	अचिन्हित दीर्घ flags;

	अगर (!ap)
		वापस;
	spin_lock_irqsave(&ap->recv_lock, flags);
	ppp_async_input(ap, buf, cflags, count);
	spin_unlock_irqrestore(&ap->recv_lock, flags);
	अगर (!skb_queue_empty(&ap->rqueue))
		tasklet_schedule(&ap->tsk);
	ap_put(ap);
	tty_unthrottle(tty);
पूर्ण

अटल व्योम
ppp_asynctty_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा asyncppp *ap = ap_get(tty);

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	अगर (!ap)
		वापस;
	set_bit(XMIT_WAKEUP, &ap->xmit_flags);
	tasklet_schedule(&ap->tsk);
	ap_put(ap);
पूर्ण


अटल काष्ठा tty_ldisc_ops ppp_ldisc = अणु
	.owner  = THIS_MODULE,
	.name	= "ppp",
	.खोलो	= ppp_asynctty_खोलो,
	.बंद	= ppp_asynctty_बंद,
	.hangup	= ppp_asynctty_hangup,
	.पढ़ो	= ppp_asynctty_पढ़ो,
	.ग_लिखो	= ppp_asynctty_ग_लिखो,
	.ioctl	= ppp_asynctty_ioctl,
	.poll	= ppp_asynctty_poll,
	.receive_buf = ppp_asynctty_receive,
	.ग_लिखो_wakeup = ppp_asynctty_wakeup,
पूर्ण;

अटल पूर्णांक __init
ppp_async_init(व्योम)
अणु
	पूर्णांक err;

	err = tty_रेजिस्टर_ldisc(N_PPP, &ppp_ldisc);
	अगर (err != 0)
		prपूर्णांकk(KERN_ERR "PPP_async: error %d registering line disc.\n",
		       err);
	वापस err;
पूर्ण

/*
 * The following routines provide the PPP channel पूर्णांकerface.
 */
अटल पूर्णांक
ppp_async_ioctl(काष्ठा ppp_channel *chan, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा asyncppp *ap = chan->निजी;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक err, val;
	u32 accm[8];

	err = -EFAULT;
	चयन (cmd) अणु
	हाल PPPIOCGFLAGS:
		val = ap->flags | ap->rbits;
		अगर (put_user(val, p))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSFLAGS:
		अगर (get_user(val, p))
			अवरोध;
		ap->flags = val & ~SC_RCV_BITS;
		spin_lock_irq(&ap->recv_lock);
		ap->rbits = val & SC_RCV_BITS;
		spin_unlock_irq(&ap->recv_lock);
		err = 0;
		अवरोध;

	हाल PPPIOCGASYNCMAP:
		अगर (put_user(ap->xaccm[0], (u32 __user *)argp))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSASYNCMAP:
		अगर (get_user(ap->xaccm[0], (u32 __user *)argp))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCGRASYNCMAP:
		अगर (put_user(ap->raccm, (u32 __user *)argp))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSRASYNCMAP:
		अगर (get_user(ap->raccm, (u32 __user *)argp))
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
		अगर (put_user(ap->mru, p))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSMRU:
		अगर (get_user(val, p))
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
अटल व्योम ppp_async_process(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा asyncppp *ap = from_tasklet(ap, t, tsk);
	काष्ठा sk_buff *skb;

	/* process received packets */
	जबतक ((skb = skb_dequeue(&ap->rqueue)) != शून्य) अणु
		अगर (skb->cb[0])
			ppp_input_error(&ap->chan, 0);
		ppp_input(&ap->chan, skb);
	पूर्ण

	/* try to push more stuff out */
	अगर (test_bit(XMIT_WAKEUP, &ap->xmit_flags) && ppp_async_push(ap))
		ppp_output_wakeup(&ap->chan);
पूर्ण

/*
 * Procedures क्रम encapsulation and framing.
 */

/*
 * Procedure to encode the data क्रम async serial transmission.
 * Does octet stuffing (escaping), माला_दो the address/control bytes
 * on अगर A/C compression is disabled, and करोes protocol compression.
 * Assumes ap->tpkt != 0 on entry.
 * Returns 1 अगर we finished the current frame, 0 otherwise.
 */

#घोषणा PUT_BYTE(ap, buf, c, islcp)	करो अणु		\
	अगर ((islcp && c < 0x20) || (ap->xaccm[c >> 5] & (1 << (c & 0x1f)))) अणु\
		*buf++ = PPP_ESCAPE;			\
		*buf++ = c ^ PPP_TRANS;			\
	पूर्ण अन्यथा						\
		*buf++ = c;				\
पूर्ण जबतक (0)

अटल पूर्णांक
ppp_async_encode(काष्ठा asyncppp *ap)
अणु
	पूर्णांक fcs, i, count, c, proto;
	अचिन्हित अक्षर *buf, *buflim;
	अचिन्हित अक्षर *data;
	पूर्णांक islcp;

	buf = ap->obuf;
	ap->olim = buf;
	ap->optr = buf;
	i = ap->tpkt_pos;
	data = ap->tpkt->data;
	count = ap->tpkt->len;
	fcs = ap->tfcs;
	proto = get_unaligned_be16(data);

	/*
	 * LCP packets with code values between 1 (configure-reqest)
	 * and 7 (code-reject) must be sent as though no options
	 * had been negotiated.
	 */
	islcp = proto == PPP_LCP && 1 <= data[2] && data[2] <= 7;

	अगर (i == 0) अणु
		अगर (islcp)
			async_lcp_peek(ap, data, count, 0);

		/*
		 * Start of a new packet - insert the leading FLAG
		 * अक्षरacter अगर necessary.
		 */
		अगर (islcp || flag_समय == 0 ||
		    समय_after_eq(jअगरfies, ap->last_xmit + flag_समय))
			*buf++ = PPP_FLAG;
		ap->last_xmit = jअगरfies;
		fcs = PPP_INITFCS;

		/*
		 * Put in the address/control bytes अगर necessary
		 */
		अगर ((ap->flags & SC_COMP_AC) == 0 || islcp) अणु
			PUT_BYTE(ap, buf, 0xff, islcp);
			fcs = PPP_FCS(fcs, 0xff);
			PUT_BYTE(ap, buf, 0x03, islcp);
			fcs = PPP_FCS(fcs, 0x03);
		पूर्ण
	पूर्ण

	/*
	 * Once we put in the last byte, we need to put in the FCS
	 * and closing flag, so make sure there is at least 7 bytes
	 * of मुक्त space in the output buffer.
	 */
	buflim = ap->obuf + Oबफ_मानE - 6;
	जबतक (i < count && buf < buflim) अणु
		c = data[i++];
		अगर (i == 1 && c == 0 && (ap->flags & SC_COMP_PROT))
			जारी;	/* compress protocol field */
		fcs = PPP_FCS(fcs, c);
		PUT_BYTE(ap, buf, c, islcp);
	पूर्ण

	अगर (i < count) अणु
		/*
		 * Remember where we are up to in this packet.
		 */
		ap->olim = buf;
		ap->tpkt_pos = i;
		ap->tfcs = fcs;
		वापस 0;
	पूर्ण

	/*
	 * We have finished the packet.  Add the FCS and flag.
	 */
	fcs = ~fcs;
	c = fcs & 0xff;
	PUT_BYTE(ap, buf, c, islcp);
	c = (fcs >> 8) & 0xff;
	PUT_BYTE(ap, buf, c, islcp);
	*buf++ = PPP_FLAG;
	ap->olim = buf;

	consume_skb(ap->tpkt);
	ap->tpkt = शून्य;
	वापस 1;
पूर्ण

/*
 * Transmit-side routines.
 */

/*
 * Send a packet to the peer over an async tty line.
 * Returns 1 अगरf the packet was accepted.
 * If the packet was not accepted, we will call ppp_output_wakeup
 * at some later समय.
 */
अटल पूर्णांक
ppp_async_send(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा asyncppp *ap = chan->निजी;

	ppp_async_push(ap);

	अगर (test_and_set_bit(XMIT_FULL, &ap->xmit_flags))
		वापस 0;	/* alपढ़ोy full */
	ap->tpkt = skb;
	ap->tpkt_pos = 0;

	ppp_async_push(ap);
	वापस 1;
पूर्ण

/*
 * Push as much data as possible out to the tty.
 */
अटल पूर्णांक
ppp_async_push(काष्ठा asyncppp *ap)
अणु
	पूर्णांक avail, sent, करोne = 0;
	काष्ठा tty_काष्ठा *tty = ap->tty;
	पूर्णांक tty_stuffed = 0;

	/*
	 * We can get called recursively here अगर the tty ग_लिखो
	 * function calls our wakeup function.  This can happen
	 * क्रम example on a pty with both the master and slave
	 * set to PPP line discipline.
	 * We use the XMIT_BUSY bit to detect this and get out,
	 * leaving the XMIT_WAKEUP bit set to tell the other
	 * instance that it may now be able to ग_लिखो more now.
	 */
	अगर (test_and_set_bit(XMIT_BUSY, &ap->xmit_flags))
		वापस 0;
	spin_lock_bh(&ap->xmit_lock);
	क्रम (;;) अणु
		अगर (test_and_clear_bit(XMIT_WAKEUP, &ap->xmit_flags))
			tty_stuffed = 0;
		अगर (!tty_stuffed && ap->optr < ap->olim) अणु
			avail = ap->olim - ap->optr;
			set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
			sent = tty->ops->ग_लिखो(tty, ap->optr, avail);
			अगर (sent < 0)
				जाओ flush;	/* error, e.g. loss of CD */
			ap->optr += sent;
			अगर (sent < avail)
				tty_stuffed = 1;
			जारी;
		पूर्ण
		अगर (ap->optr >= ap->olim && ap->tpkt) अणु
			अगर (ppp_async_encode(ap)) अणु
				/* finished processing ap->tpkt */
				clear_bit(XMIT_FULL, &ap->xmit_flags);
				करोne = 1;
			पूर्ण
			जारी;
		पूर्ण
		/*
		 * We haven't made any progress this समय around.
		 * Clear XMIT_BUSY to let other callers in, but
		 * after करोing so we have to check अगर anyone set
		 * XMIT_WAKEUP since we last checked it.  If they
		 * did, we should try again to set XMIT_BUSY and go
		 * around again in हाल XMIT_BUSY was still set when
		 * the other caller tried.
		 */
		clear_bit(XMIT_BUSY, &ap->xmit_flags);
		/* any more work to करो? अगर not, निकास the loop */
		अगर (!(test_bit(XMIT_WAKEUP, &ap->xmit_flags) ||
		      (!tty_stuffed && ap->tpkt)))
			अवरोध;
		/* more work to करो, see अगर we can करो it now */
		अगर (test_and_set_bit(XMIT_BUSY, &ap->xmit_flags))
			अवरोध;
	पूर्ण
	spin_unlock_bh(&ap->xmit_lock);
	वापस करोne;

flush:
	clear_bit(XMIT_BUSY, &ap->xmit_flags);
	अगर (ap->tpkt) अणु
		kमुक्त_skb(ap->tpkt);
		ap->tpkt = शून्य;
		clear_bit(XMIT_FULL, &ap->xmit_flags);
		करोne = 1;
	पूर्ण
	ap->optr = ap->olim;
	spin_unlock_bh(&ap->xmit_lock);
	वापस करोne;
पूर्ण

/*
 * Flush output from our पूर्णांकernal buffers.
 * Called क्रम the TCFLSH ioctl. Can be entered in parallel
 * but this is covered by the xmit_lock.
 */
अटल व्योम
ppp_async_flush_output(काष्ठा asyncppp *ap)
अणु
	पूर्णांक करोne = 0;

	spin_lock_bh(&ap->xmit_lock);
	ap->optr = ap->olim;
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

/* see how many ordinary अक्षरs there are at the start of buf */
अटल अंतरभूत पूर्णांक
scan_ordinary(काष्ठा asyncppp *ap, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i, c;

	क्रम (i = 0; i < count; ++i) अणु
		c = buf[i];
		अगर (c == PPP_ESCAPE || c == PPP_FLAG ||
		    (c < 0x20 && (ap->raccm & (1 << c)) != 0))
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

/* called when a flag is seen - करो end-of-packet processing */
अटल व्योम
process_input_packet(काष्ठा asyncppp *ap)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *p;
	अचिन्हित पूर्णांक len, fcs;

	skb = ap->rpkt;
	अगर (ap->state & (SC_TOSS | SC_ESCAPE))
		जाओ err;

	अगर (skb == शून्य)
		वापस;		/* 0-length packet */

	/* check the FCS */
	p = skb->data;
	len = skb->len;
	अगर (len < 3)
		जाओ err;	/* too लघु */
	fcs = PPP_INITFCS;
	क्रम (; len > 0; --len)
		fcs = PPP_FCS(fcs, *p++);
	अगर (fcs != PPP_GOODFCS)
		जाओ err;	/* bad FCS */
	skb_trim(skb, skb->len - 2);

	/* check क्रम address/control and protocol compression */
	p = skb->data;
	अगर (p[0] == PPP_ALLSTATIONS) अणु
		/* chop off address/control */
		अगर (p[1] != PPP_UI || skb->len < 3)
			जाओ err;
		p = skb_pull(skb, 2);
	पूर्ण

	/* If protocol field is not compressed, it can be LCP packet */
	अगर (!(p[0] & 0x01)) अणु
		अचिन्हित पूर्णांक proto;

		अगर (skb->len < 2)
			जाओ err;
		proto = (p[0] << 8) + p[1];
		अगर (proto == PPP_LCP)
			async_lcp_peek(ap, p, skb->len, 1);
	पूर्ण

	/* queue the frame to be processed */
	skb->cb[0] = ap->state;
	skb_queue_tail(&ap->rqueue, skb);
	ap->rpkt = शून्य;
	ap->state = 0;
	वापस;

 err:
	/* frame had an error, remember that, reset SC_TOSS & SC_ESCAPE */
	ap->state = SC_PREV_ERROR;
	अगर (skb) अणु
		/* make skb appear as freshly allocated */
		skb_trim(skb, 0);
		skb_reserve(skb, - skb_headroom(skb));
	पूर्ण
पूर्ण

/* Called when the tty driver has data क्रम us. Runs parallel with the
   other ldisc functions but will not be re-entered */

अटल व्योम
ppp_async_input(काष्ठा asyncppp *ap, स्थिर अचिन्हित अक्षर *buf,
		अक्षर *flags, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक c, i, j, n, s, f;
	अचिन्हित अक्षर *sp;

	/* update bits used क्रम 8-bit cleanness detection */
	अगर (~ap->rbits & SC_RCV_BITS) अणु
		s = 0;
		क्रम (i = 0; i < count; ++i) अणु
			c = buf[i];
			अगर (flags && flags[i] != 0)
				जारी;
			s |= (c & 0x80)? SC_RCV_B7_1: SC_RCV_B7_0;
			c = ((c >> 4) ^ c) & 0xf;
			s |= (0x6996 & (1 << c))? SC_RCV_ODDP: SC_RCV_EVNP;
		पूर्ण
		ap->rbits |= s;
	पूर्ण

	जबतक (count > 0) अणु
		/* scan through and see how many अक्षरs we can करो in bulk */
		अगर ((ap->state & SC_ESCAPE) && buf[0] == PPP_ESCAPE)
			n = 1;
		अन्यथा
			n = scan_ordinary(ap, buf, count);

		f = 0;
		अगर (flags && (ap->state & SC_TOSS) == 0) अणु
			/* check the flags to see अगर any अक्षर had an error */
			क्रम (j = 0; j < n; ++j)
				अगर ((f = flags[j]) != 0)
					अवरोध;
		पूर्ण
		अगर (f != 0) अणु
			/* start tossing */
			ap->state |= SC_TOSS;

		पूर्ण अन्यथा अगर (n > 0 && (ap->state & SC_TOSS) == 0) अणु
			/* stuff the अक्षरs in the skb */
			skb = ap->rpkt;
			अगर (!skb) अणु
				skb = dev_alloc_skb(ap->mru + PPP_HDRLEN + 2);
				अगर (!skb)
					जाओ nomem;
				ap->rpkt = skb;
			पूर्ण
			अगर (skb->len == 0) अणु
				/* Try to get the payload 4-byte aligned.
				 * This should match the
				 * PPP_ALLSTATIONS/PPP_UI/compressed tests in
				 * process_input_packet, but we करो not have
				 * enough अक्षरs here to test buf[1] and buf[2].
				 */
				अगर (buf[0] != PPP_ALLSTATIONS)
					skb_reserve(skb, 2 + (buf[0] & 1));
			पूर्ण
			अगर (n > skb_tailroom(skb)) अणु
				/* packet overflowed MRU */
				ap->state |= SC_TOSS;
			पूर्ण अन्यथा अणु
				sp = skb_put_data(skb, buf, n);
				अगर (ap->state & SC_ESCAPE) अणु
					sp[0] ^= PPP_TRANS;
					ap->state &= ~SC_ESCAPE;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (n >= count)
			अवरोध;

		c = buf[n];
		अगर (flags != शून्य && flags[n] != 0) अणु
			ap->state |= SC_TOSS;
		पूर्ण अन्यथा अगर (c == PPP_FLAG) अणु
			process_input_packet(ap);
		पूर्ण अन्यथा अगर (c == PPP_ESCAPE) अणु
			ap->state |= SC_ESCAPE;
		पूर्ण अन्यथा अगर (I_IXON(ap->tty)) अणु
			अगर (c == START_CHAR(ap->tty))
				start_tty(ap->tty);
			अन्यथा अगर (c == STOP_CHAR(ap->tty))
				stop_tty(ap->tty);
		पूर्ण
		/* otherwise it's a अक्षर in the recv ACCM */
		++n;

		buf += n;
		अगर (flags)
			flags += n;
		count -= n;
	पूर्ण
	वापस;

 nomem:
	prपूर्णांकk(KERN_ERR "PPPasync: no memory (input pkt)\n");
	ap->state |= SC_TOSS;
पूर्ण

/*
 * We look at LCP frames going past so that we can notice
 * and react to the LCP configure-ack from the peer.
 * In the situation where the peer has been sent a configure-ack
 * alपढ़ोy, LCP is up once it has sent its configure-ack
 * so the immediately following packet can be sent with the
 * configured LCP options.  This allows us to process the following
 * packet correctly without pppd needing to respond quickly.
 *
 * We only respond to the received configure-ack अगर we have just
 * sent a configure-request, and the configure-ack contains the
 * same data (this is checked using a 16-bit crc of the data).
 */
#घोषणा CONFREQ		1	/* LCP code field values */
#घोषणा CONFACK		2
#घोषणा LCP_MRU		1	/* LCP option numbers */
#घोषणा LCP_ASYNCMAP	2

अटल व्योम async_lcp_peek(काष्ठा asyncppp *ap, अचिन्हित अक्षर *data,
			   पूर्णांक len, पूर्णांक inbound)
अणु
	पूर्णांक dlen, fcs, i, code;
	u32 val;

	data += 2;		/* skip protocol bytes */
	len -= 2;
	अगर (len < 4)		/* 4 = code, ID, length */
		वापस;
	code = data[0];
	अगर (code != CONFACK && code != CONFREQ)
		वापस;
	dlen = get_unaligned_be16(data + 2);
	अगर (len < dlen)
		वापस;		/* packet got truncated or length is bogus */

	अगर (code == (inbound? CONFACK: CONFREQ)) अणु
		/*
		 * sent confreq or received confack:
		 * calculate the crc of the data from the ID field on.
		 */
		fcs = PPP_INITFCS;
		क्रम (i = 1; i < dlen; ++i)
			fcs = PPP_FCS(fcs, data[i]);

		अगर (!inbound) अणु
			/* outbound confreq - remember the crc क्रम later */
			ap->lcp_fcs = fcs;
			वापस;
		पूर्ण

		/* received confack, check the crc */
		fcs ^= ap->lcp_fcs;
		ap->lcp_fcs = -1;
		अगर (fcs != 0)
			वापस;
	पूर्ण अन्यथा अगर (inbound)
		वापस;	/* not पूर्णांकerested in received confreq */

	/* process the options in the confack */
	data += 4;
	dlen -= 4;
	/* data[0] is code, data[1] is length */
	जबतक (dlen >= 2 && dlen >= data[1] && data[1] >= 2) अणु
		चयन (data[0]) अणु
		हाल LCP_MRU:
			val = get_unaligned_be16(data + 2);
			अगर (inbound)
				ap->mru = val;
			अन्यथा
				ap->chan.mtu = val;
			अवरोध;
		हाल LCP_ASYNCMAP:
			val = get_unaligned_be32(data + 2);
			अगर (inbound)
				ap->raccm = val;
			अन्यथा
				ap->xaccm[0] = val;
			अवरोध;
		पूर्ण
		dlen -= data[1];
		data += data[1];
	पूर्ण
पूर्ण

अटल व्योम __निकास ppp_async_cleanup(व्योम)
अणु
	अगर (tty_unरेजिस्टर_ldisc(N_PPP) != 0)
		prपूर्णांकk(KERN_ERR "failed to unregister PPP line discipline\n");
पूर्ण

module_init(ppp_async_init);
module_निकास(ppp_async_cleanup);
