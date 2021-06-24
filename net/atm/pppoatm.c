<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* net/aपंचांग/pppoaपंचांग.c - RFC2364 PPP over ATM/AAL5 */

/* Copyright 1999-2000 by Mitchell Blank Jr */
/* Based on clip.c; 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
/* And on ppp_async.c; Copyright 1999 Paul Mackerras */
/* And help from Jens Axboe */

/*
 *
 * This driver provides the encapsulation and framing क्रम sending
 * and receiving PPP frames in ATM AAL5 PDUs.
 */

/*
 * One लघुcoming of this driver is that it करोes not comply with
 * section 8 of RFC2364 - we are supposed to detect a change
 * in encapsulation and immediately पात the connection (in order
 * to aव्योम a black-hole being created अगर our peer loses state
 * and changes encapsulation unilaterally.  However, since the
 * ppp_generic layer actually करोes the decapsulation, we need
 * a way of notअगरying it when we _think_ there might be a problem)
 * There's two हालs:
 *   1.	LLC-encapsulation was missing when it was enabled.  In
 *	this हाल, we should tell the upper layer "tear करोwn
 *	this session अगर this skb looks ok to you"
 *   2.	LLC-encapsulation was present when it was disabled.  Then
 *	we need to tell the upper layer "this packet may be
 *	ok, but अगर its in error tear करोwn the session"
 * These hooks are not yet available in ppp_generic
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/capability.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/aपंचांगppp.h>

#समावेश "common.h"

क्रमागत pppoaपंचांग_encaps अणु
	e_स्वतःdetect = PPPOATM_ENCAPS_AUTODETECT,
	e_vc = PPPOATM_ENCAPS_VC,
	e_llc = PPPOATM_ENCAPS_LLC,
पूर्ण;

काष्ठा pppoaपंचांग_vcc अणु
	काष्ठा aपंचांग_vcc	*aपंचांगvcc;	/* VCC descriptor */
	व्योम (*old_push)(काष्ठा aपंचांग_vcc *, काष्ठा sk_buff *);
	व्योम (*old_pop)(काष्ठा aपंचांग_vcc *, काष्ठा sk_buff *);
	व्योम (*old_release_cb)(काष्ठा aपंचांग_vcc *);
	काष्ठा module *old_owner;
					/* keep old push/pop क्रम detaching */
	क्रमागत pppoaपंचांग_encaps encaps;
	atomic_t inflight;
	अचिन्हित दीर्घ blocked;
	पूर्णांक flags;			/* SC_COMP_PROT - compress protocol */
	काष्ठा ppp_channel chan;	/* पूर्णांकerface to generic ppp layer */
	काष्ठा tasklet_काष्ठा wakeup_tasklet;
पूर्ण;

/*
 * We want to allow two packets in the queue. The one that's currently in
 * flight, and *one* queued up पढ़ोy क्रम the ATM device to send immediately
 * from its TX करोne IRQ. We want to be able to use atomic_inc_not_zero(), so
 * inflight == -2 represents an empty queue, -1 one packet, and zero means
 * there are two packets in the queue.
 */
#घोषणा NONE_INFLIGHT -2

#घोषणा BLOCKED 0

/*
 * Header used क्रम LLC Encapsulated PPP (4 bytes) followed by the LCP protocol
 * ID (0xC021) used in स्वतःdetection
 */
अटल स्थिर अचिन्हित अक्षर pppllc[6] = अणु 0xFE, 0xFE, 0x03, 0xCF, 0xC0, 0x21 पूर्ण;
#घोषणा LLC_LEN		(4)

अटल अंतरभूत काष्ठा pppoaपंचांग_vcc *aपंचांगvcc_to_pvcc(स्थिर काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	वापस (काष्ठा pppoaपंचांग_vcc *) (aपंचांगvcc->user_back);
पूर्ण

अटल अंतरभूत काष्ठा pppoaपंचांग_vcc *chan_to_pvcc(स्थिर काष्ठा ppp_channel *chan)
अणु
	वापस (काष्ठा pppoaपंचांग_vcc *) (chan->निजी);
पूर्ण

/*
 * We can't करो this directly from our _pop handler, since the ppp code
 * करोesn't want to be called in पूर्णांकerrupt context, so we करो it from
 * a tasklet
 */
अटल व्योम pppoaपंचांग_wakeup_sender(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा pppoaपंचांग_vcc *pvcc = from_tasklet(pvcc, t, wakeup_tasklet);

	ppp_output_wakeup(&pvcc->chan);
पूर्ण

अटल व्योम pppoaपंचांग_release_cb(काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	काष्ठा pppoaपंचांग_vcc *pvcc = aपंचांगvcc_to_pvcc(aपंचांगvcc);

	/*
	 * As in pppoaपंचांग_pop(), it's safe to clear the BLOCKED bit here because
	 * the wakeup *can't* race with pppoaपंचांग_send(). They both hold the PPP
	 * channel's ->करोwnl lock. And the potential race with *setting* it,
	 * which leads to the द्विगुन-check dance in pppoaपंचांग_may_send(), करोesn't
	 * exist here. In the sock_owned_by_user() हाल in pppoaपंचांग_send(), we
	 * set the BLOCKED bit जबतक the socket is still locked. We know that
	 * ->release_cb() can't be called until that's करोne.
	 */
	अगर (test_and_clear_bit(BLOCKED, &pvcc->blocked))
		tasklet_schedule(&pvcc->wakeup_tasklet);
	अगर (pvcc->old_release_cb)
		pvcc->old_release_cb(aपंचांगvcc);
पूर्ण
/*
 * This माला_लो called every समय the ATM card has finished sending our
 * skb.  The ->old_pop will take care up normal aपंचांग flow control,
 * but we also need to wake up the device अगर we blocked it
 */
अटल व्योम pppoaपंचांग_pop(काष्ठा aपंचांग_vcc *aपंचांगvcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा pppoaपंचांग_vcc *pvcc = aपंचांगvcc_to_pvcc(aपंचांगvcc);

	pvcc->old_pop(aपंचांगvcc, skb);
	atomic_dec(&pvcc->inflight);

	/*
	 * We always used to run the wakeup tasklet unconditionally here, क्रम
	 * fear of race conditions where we clear the BLOCKED flag just as we
	 * refuse another packet in pppoaपंचांग_send(). This was quite inefficient.
	 *
	 * In fact it's OK. The PPP core will only ever call pppoaपंचांग_send()
	 * जबतक holding the channel->करोwnl lock. And ppp_output_wakeup() as
	 * called by the tasklet will *also* grab that lock. So even अगर another
	 * CPU is in pppoaपंचांग_send() right now, the tasklet isn't going to race
	 * with it. The wakeup *will* happen after the other CPU is safely out
	 * of pppoaपंचांग_send() again.
	 *
	 * So अगर the CPU in pppoaपंचांग_send() has alपढ़ोy set the BLOCKED bit and
	 * it about to वापस, that's fine. We trigger a wakeup which will
	 * happen later. And अगर the CPU in pppoaपंचांग_send() *hasn't* set the
	 * BLOCKED bit yet, that's fine too because of the द्विगुन check in
	 * pppoaपंचांग_may_send() which is commented there.
	 */
	अगर (test_and_clear_bit(BLOCKED, &pvcc->blocked))
		tasklet_schedule(&pvcc->wakeup_tasklet);
पूर्ण

/*
 * Unbind from PPP - currently we only करो this when closing the socket,
 * but we could put this पूर्णांकo an ioctl अगर need be
 */
अटल व्योम pppoaपंचांग_unassign_vcc(काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	काष्ठा pppoaपंचांग_vcc *pvcc;
	pvcc = aपंचांगvcc_to_pvcc(aपंचांगvcc);
	aपंचांगvcc->push = pvcc->old_push;
	aपंचांगvcc->pop = pvcc->old_pop;
	aपंचांगvcc->release_cb = pvcc->old_release_cb;
	tasklet_समाप्त(&pvcc->wakeup_tasklet);
	ppp_unरेजिस्टर_channel(&pvcc->chan);
	aपंचांगvcc->user_back = शून्य;
	kमुक्त(pvcc);
पूर्ण

/* Called when an AAL5 PDU comes in */
अटल व्योम pppoaपंचांग_push(काष्ठा aपंचांग_vcc *aपंचांगvcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा pppoaपंचांग_vcc *pvcc = aपंचांगvcc_to_pvcc(aपंचांगvcc);
	pr_debug("\n");
	अगर (skb == शून्य) अणु			/* VCC was बंदd */
		काष्ठा module *module;

		pr_debug("removing ATMPPP VCC %p\n", pvcc);
		module = pvcc->old_owner;
		pppoaपंचांग_unassign_vcc(aपंचांगvcc);
		aपंचांगvcc->push(aपंचांगvcc, शून्य);	/* Pass aदीर्घ bad news */
		module_put(module);
		वापस;
	पूर्ण
	aपंचांग_वापस(aपंचांगvcc, skb->truesize);
	चयन (pvcc->encaps) अणु
	हाल e_llc:
		अगर (skb->len < LLC_LEN ||
		    स_भेद(skb->data, pppllc, LLC_LEN))
			जाओ error;
		skb_pull(skb, LLC_LEN);
		अवरोध;
	हाल e_स्वतःdetect:
		अगर (pvcc->chan.ppp == शून्य) अणु	/* Not bound yet! */
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
		अगर (skb->len >= माप(pppllc) &&
		    !स_भेद(skb->data, pppllc, माप(pppllc))) अणु
			pvcc->encaps = e_llc;
			skb_pull(skb, LLC_LEN);
			अवरोध;
		पूर्ण
		अगर (skb->len >= (माप(pppllc) - LLC_LEN) &&
		    !स_भेद(skb->data, &pppllc[LLC_LEN],
		    माप(pppllc) - LLC_LEN)) अणु
			pvcc->encaps = e_vc;
			pvcc->chan.mtu += LLC_LEN;
			अवरोध;
		पूर्ण
		pr_debug("Couldn't autodetect yet (skb: %6ph)\n", skb->data);
		जाओ error;
	हाल e_vc:
		अवरोध;
	पूर्ण
	ppp_input(&pvcc->chan, skb);
	वापस;

error:
	kमुक्त_skb(skb);
	ppp_input_error(&pvcc->chan, 0);
पूर्ण

अटल पूर्णांक pppoaपंचांग_may_send(काष्ठा pppoaपंचांग_vcc *pvcc, पूर्णांक size)
अणु
	/*
	 * It's not clear that we need to bother with using aपंचांग_may_send()
	 * to check we करोn't exceed sk->sk_sndbuf. If userspace sets a
	 * value of sk_sndbuf which is lower than the MTU, we're going to
	 * block क्रम ever. But the code always did that beक्रमe we पूर्णांकroduced
	 * the packet count limit, so...
	 */
	अगर (aपंचांग_may_send(pvcc->aपंचांगvcc, size) &&
	    atomic_inc_not_zero(&pvcc->inflight))
		वापस 1;

	/*
	 * We use test_and_set_bit() rather than set_bit() here because
	 * we need to ensure there's a memory barrier after it. The bit
	 * *must* be set beक्रमe we करो the atomic_inc() on pvcc->inflight.
	 * There's no smp_mb__after_set_bit(), so it's this or abuse
	 * smp_mb__after_atomic().
	 */
	test_and_set_bit(BLOCKED, &pvcc->blocked);

	/*
	 * We may have raced with pppoaपंचांग_pop(). If it ran क्रम the
	 * last packet in the queue, *just* beक्रमe we set the BLOCKED
	 * bit, then it might never run again and the channel could
	 * reमुख्य permanently blocked. Cope with that race by checking
	 * *again*. If it did run in that winकरोw, we'll have space on
	 * the queue now and can वापस success. It's harmless to leave
	 * the BLOCKED flag set, since it's only used as a trigger to
	 * run the wakeup tasklet. Another wakeup will never hurt.
	 * If pppoaपंचांग_pop() is running but hasn't got as far as making
	 * space on the queue yet, then it hasn't checked the BLOCKED
	 * flag yet either, so we're safe in that case too. It'll issue
	 * an "immediate" wakeup... where "immediate" actually involves
	 * taking the PPP channel's ->करोwnl lock, which is held by the
	 * code path that calls pppoaपंचांग_send(), and is thus going to
	 * रुको क्रम us to finish.
	 */
	अगर (aपंचांग_may_send(pvcc->aपंचांगvcc, size) &&
	    atomic_inc_not_zero(&pvcc->inflight))
		वापस 1;

	वापस 0;
पूर्ण
/*
 * Called by the ppp_generic.c to send a packet - वापसs true अगर packet
 * was accepted.  If we वापस false, then it's our job to call
 * ppp_output_wakeup(chan) when we're feeling more up to it.
 * Note that in the ENOMEM हाल (as opposed to the !aपंचांग_may_send हाल)
 * we should really drop the packet, but the generic layer करोesn't
 * support this yet.  We just वापस 'DROP_PACKET' which we actually define
 * as success, just to be clear what we're really करोing.
 */
#घोषणा DROP_PACKET 1
अटल पूर्णांक pppoaपंचांग_send(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा pppoaपंचांग_vcc *pvcc = chan_to_pvcc(chan);
	काष्ठा aपंचांग_vcc *vcc;
	पूर्णांक ret;

	ATM_SKB(skb)->vcc = pvcc->aपंचांगvcc;
	pr_debug("(skb=0x%p, vcc=0x%p)\n", skb, pvcc->aपंचांगvcc);
	अगर (skb->data[0] == '\0' && (pvcc->flags & SC_COMP_PROT))
		(व्योम) skb_pull(skb, 1);

	vcc = ATM_SKB(skb)->vcc;
	bh_lock_sock(sk_aपंचांग(vcc));
	अगर (sock_owned_by_user(sk_aपंचांग(vcc))) अणु
		/*
		 * Needs to happen (and be flushed, hence test_and_) beक्रमe we unlock
		 * the socket. It needs to be seen by the समय our ->release_cb माला_लो
		 * called.
		 */
		test_and_set_bit(BLOCKED, &pvcc->blocked);
		जाओ nospace;
	पूर्ण
	अगर (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    test_bit(ATM_VF_CLOSE, &vcc->flags) ||
	    !test_bit(ATM_VF_READY, &vcc->flags)) अणु
		bh_unlock_sock(sk_aपंचांग(vcc));
		kमुक्त_skb(skb);
		वापस DROP_PACKET;
	पूर्ण

	चयन (pvcc->encaps) अणु		/* LLC encapsulation needed */
	हाल e_llc:
		अगर (skb_headroom(skb) < LLC_LEN) अणु
			काष्ठा sk_buff *n;
			n = skb_पुनः_स्मृति_headroom(skb, LLC_LEN);
			अगर (n != शून्य &&
			    !pppoaपंचांग_may_send(pvcc, n->truesize)) अणु
				kमुक्त_skb(n);
				जाओ nospace;
			पूर्ण
			consume_skb(skb);
			skb = n;
			अगर (skb == शून्य) अणु
				bh_unlock_sock(sk_aपंचांग(vcc));
				वापस DROP_PACKET;
			पूर्ण
		पूर्ण अन्यथा अगर (!pppoaपंचांग_may_send(pvcc, skb->truesize))
			जाओ nospace;
		स_नकल(skb_push(skb, LLC_LEN), pppllc, LLC_LEN);
		अवरोध;
	हाल e_vc:
		अगर (!pppoaपंचांग_may_send(pvcc, skb->truesize))
			जाओ nospace;
		अवरोध;
	हाल e_स्वतःdetect:
		bh_unlock_sock(sk_aपंचांग(vcc));
		pr_debug("Trying to send without setting encaps!\n");
		kमुक्त_skb(skb);
		वापस 1;
	पूर्ण

	aपंचांग_account_tx(vcc, skb);
	pr_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n",
		 skb, ATM_SKB(skb)->vcc, ATM_SKB(skb)->vcc->dev);
	ret = ATM_SKB(skb)->vcc->send(ATM_SKB(skb)->vcc, skb)
	    ? DROP_PACKET : 1;
	bh_unlock_sock(sk_aपंचांग(vcc));
	वापस ret;
nospace:
	bh_unlock_sock(sk_aपंचांग(vcc));
	/*
	 * We करोn't have space to send this SKB now, but we might have
	 * alपढ़ोy applied SC_COMP_PROT compression, so may need to unकरो
	 */
	अगर ((pvcc->flags & SC_COMP_PROT) && skb_headroom(skb) > 0 &&
	    skb->data[-1] == '\0')
		(व्योम) skb_push(skb, 1);
	वापस 0;
पूर्ण

/* This handles ioctls sent to the /dev/ppp पूर्णांकerface */
अटल पूर्णांक pppoaपंचांग_devppp_ioctl(काष्ठा ppp_channel *chan, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल PPPIOCGFLAGS:
		वापस put_user(chan_to_pvcc(chan)->flags, (पूर्णांक __user *) arg)
		    ? -EFAULT : 0;
	हाल PPPIOCSFLAGS:
		वापस get_user(chan_to_pvcc(chan)->flags, (पूर्णांक __user *) arg)
		    ? -EFAULT : 0;
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल स्थिर काष्ठा ppp_channel_ops pppoaपंचांग_ops = अणु
	.start_xmit = pppoaपंचांग_send,
	.ioctl = pppoaपंचांग_devppp_ioctl,
पूर्ण;

अटल पूर्णांक pppoaपंचांग_assign_vcc(काष्ठा aपंचांग_vcc *aपंचांगvcc, व्योम __user *arg)
अणु
	काष्ठा aपंचांग_backend_ppp be;
	काष्ठा pppoaपंचांग_vcc *pvcc;
	पूर्णांक err;

	अगर (copy_from_user(&be, arg, माप be))
		वापस -EFAULT;
	अगर (be.encaps != PPPOATM_ENCAPS_AUTODETECT &&
	    be.encaps != PPPOATM_ENCAPS_VC && be.encaps != PPPOATM_ENCAPS_LLC)
		वापस -EINVAL;
	pvcc = kzalloc(माप(*pvcc), GFP_KERNEL);
	अगर (pvcc == शून्य)
		वापस -ENOMEM;
	pvcc->aपंचांगvcc = aपंचांगvcc;

	/* Maximum is zero, so that we can use atomic_inc_not_zero() */
	atomic_set(&pvcc->inflight, NONE_INFLIGHT);
	pvcc->old_push = aपंचांगvcc->push;
	pvcc->old_pop = aपंचांगvcc->pop;
	pvcc->old_owner = aपंचांगvcc->owner;
	pvcc->old_release_cb = aपंचांगvcc->release_cb;
	pvcc->encaps = (क्रमागत pppoaपंचांग_encaps) be.encaps;
	pvcc->chan.निजी = pvcc;
	pvcc->chan.ops = &pppoaपंचांग_ops;
	pvcc->chan.mtu = aपंचांगvcc->qos.txtp.max_sdu - PPP_HDRLEN -
	    (be.encaps == e_vc ? 0 : LLC_LEN);
	tasklet_setup(&pvcc->wakeup_tasklet, pppoaपंचांग_wakeup_sender);
	err = ppp_रेजिस्टर_channel(&pvcc->chan);
	अगर (err != 0) अणु
		kमुक्त(pvcc);
		वापस err;
	पूर्ण
	aपंचांगvcc->user_back = pvcc;
	aपंचांगvcc->push = pppoaपंचांग_push;
	aपंचांगvcc->pop = pppoaपंचांग_pop;
	aपंचांगvcc->release_cb = pppoaपंचांग_release_cb;
	__module_get(THIS_MODULE);
	aपंचांगvcc->owner = THIS_MODULE;

	/* re-process everything received between connection setup and
	   backend setup */
	vcc_process_recv_queue(aपंचांगvcc);
	वापस 0;
पूर्ण

/*
 * This handles ioctls actually perक्रमmed on our vcc - we must वापस
 * -ENOIOCTLCMD क्रम any unrecognized ioctl
 */
अटल पूर्णांक pppoaपंचांग_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg)
अणु
	काष्ठा aपंचांग_vcc *aपंचांगvcc = ATM_SD(sock);
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (cmd != ATM_SETBACKEND && aपंचांगvcc->push != pppoaपंचांग_push)
		वापस -ENOIOCTLCMD;
	चयन (cmd) अणु
	हाल ATM_SETBACKEND: अणु
		aपंचांग_backend_t b;
		अगर (get_user(b, (aपंचांग_backend_t __user *) argp))
			वापस -EFAULT;
		अगर (b != ATM_BACKEND_PPP)
			वापस -ENOIOCTLCMD;
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (sock->state != SS_CONNECTED)
			वापस -EINVAL;
		वापस pppoaपंचांग_assign_vcc(aपंचांगvcc, argp);
		पूर्ण
	हाल PPPIOCGCHAN:
		वापस put_user(ppp_channel_index(&aपंचांगvcc_to_pvcc(aपंचांगvcc)->
		    chan), (पूर्णांक __user *) argp) ? -EFAULT : 0;
	हाल PPPIOCGUNIT:
		वापस put_user(ppp_unit_number(&aपंचांगvcc_to_pvcc(aपंचांगvcc)->
		    chan), (पूर्णांक __user *) argp) ? -EFAULT : 0;
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

अटल काष्ठा aपंचांग_ioctl pppoaपंचांग_ioctl_ops = अणु
	.owner	= THIS_MODULE,
	.ioctl	= pppoaपंचांग_ioctl,
पूर्ण;

अटल पूर्णांक __init pppoaपंचांग_init(व्योम)
अणु
	रेजिस्टर_aपंचांग_ioctl(&pppoaपंचांग_ioctl_ops);
	वापस 0;
पूर्ण

अटल व्योम __निकास pppoaपंचांग_निकास(व्योम)
अणु
	deरेजिस्टर_aपंचांग_ioctl(&pppoaपंचांग_ioctl_ops);
पूर्ण

module_init(pppoaपंचांग_init);
module_निकास(pppoaपंचांग_निकास);

MODULE_AUTHOR("Mitchell Blank Jr <mitch@sfgoth.com>");
MODULE_DESCRIPTION("RFC2364 PPP over ATM/AAL5");
MODULE_LICENSE("GPL");
