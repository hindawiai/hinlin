<शैली गुरु>
/*
 * Copyright (c) 2008, 2009, 2010 QLogic Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/moduleparam.h>

#समावेश "qib.h"

अटल अचिन्हित qib_hol_समयout_ms = 3000;
module_param_named(hol_समयout_ms, qib_hol_समयout_ms, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(hol_समयout_ms,
		 "duration of user app suspension after link failure");

अचिन्हित qib_sdma_fetch_arb = 1;
module_param_named(fetch_arb, qib_sdma_fetch_arb, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(fetch_arb, "IBA7220: change SDMA descriptor arbitration");

/**
 * qib_disarm_piobufs - cancel a range of PIO buffers
 * @dd: the qlogic_ib device
 * @first: the first PIO buffer to cancel
 * @cnt: the number of PIO buffers to cancel
 *
 * Cancel a range of PIO buffers. Used at user process बंद,
 * in हाल it died जबतक writing to a PIO buffer.
 */
व्योम qib_disarm_piobufs(काष्ठा qib_devdata *dd, अचिन्हित first, अचिन्हित cnt)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित i;
	अचिन्हित last;

	last = first + cnt;
	spin_lock_irqsave(&dd->pioavail_lock, flags);
	क्रम (i = first; i < last; i++) अणु
		__clear_bit(i, dd->pio_need_disarm);
		dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_BUF(i));
	पूर्ण
	spin_unlock_irqrestore(&dd->pioavail_lock, flags);
पूर्ण

/*
 * This is called by a user process when it sees the DISARM_BUFS event
 * bit is set.
 */
पूर्णांक qib_disarm_piobufs_अगरneeded(काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	अचिन्हित i;
	अचिन्हित last;
	अचिन्हित n = 0;

	last = rcd->pio_base + rcd->piocnt;
	/*
	 * Don't need uctxt_lock here, since user has called in to us.
	 * Clear at start in हाल more पूर्णांकerrupts set bits जबतक we
	 * are disarming
	 */
	अगर (rcd->user_event_mask) अणु
		/*
		 * subctxt_cnt is 0 अगर not shared, so करो base
		 * separately, first, then reमुख्यing subctxt, अगर any
		 */
		clear_bit(_QIB_EVENT_DISARM_BUFS_BIT, &rcd->user_event_mask[0]);
		क्रम (i = 1; i < rcd->subctxt_cnt; i++)
			clear_bit(_QIB_EVENT_DISARM_BUFS_BIT,
				  &rcd->user_event_mask[i]);
	पूर्ण
	spin_lock_irq(&dd->pioavail_lock);
	क्रम (i = rcd->pio_base; i < last; i++) अणु
		अगर (__test_and_clear_bit(i, dd->pio_need_disarm)) अणु
			n++;
			dd->f_sendctrl(rcd->ppd, QIB_SENDCTRL_DISARM_BUF(i));
		पूर्ण
	पूर्ण
	spin_unlock_irq(&dd->pioavail_lock);
	वापस 0;
पूर्ण

अटल काष्ठा qib_pportdata *is_sdma_buf(काष्ठा qib_devdata *dd, अचिन्हित i)
अणु
	काष्ठा qib_pportdata *ppd;
	अचिन्हित pidx;

	क्रम (pidx = 0; pidx < dd->num_pports; pidx++) अणु
		ppd = dd->pport + pidx;
		अगर (i >= ppd->sdma_state.first_sendbuf &&
		    i < ppd->sdma_state.last_sendbuf)
			वापस ppd;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Return true अगर send buffer is being used by a user context.
 * Sets  _QIB_EVENT_DISARM_BUFS_BIT in user_event_mask as a side effect
 */
अटल पूर्णांक find_ctxt(काष्ठा qib_devdata *dd, अचिन्हित bufn)
अणु
	काष्ठा qib_ctxtdata *rcd;
	अचिन्हित ctxt;
	पूर्णांक ret = 0;

	spin_lock(&dd->uctxt_lock);
	क्रम (ctxt = dd->first_user_ctxt; ctxt < dd->cfgctxts; ctxt++) अणु
		rcd = dd->rcd[ctxt];
		अगर (!rcd || bufn < rcd->pio_base ||
		    bufn >= rcd->pio_base + rcd->piocnt)
			जारी;
		अगर (rcd->user_event_mask) अणु
			पूर्णांक i;
			/*
			 * subctxt_cnt is 0 अगर not shared, so करो base
			 * separately, first, then reमुख्यing subctxt, अगर any
			 */
			set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
				&rcd->user_event_mask[0]);
			क्रम (i = 1; i < rcd->subctxt_cnt; i++)
				set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
					&rcd->user_event_mask[i]);
		पूर्ण
		ret = 1;
		अवरोध;
	पूर्ण
	spin_unlock(&dd->uctxt_lock);

	वापस ret;
पूर्ण

/*
 * Disarm a set of send buffers.  If the buffer might be actively being
 * written to, mark the buffer to be disarmed later when it is not being
 * written to.
 *
 * This should only be called from the IRQ error handler.
 */
व्योम qib_disarm_piobufs_set(काष्ठा qib_devdata *dd, अचिन्हित दीर्घ *mask,
			    अचिन्हित cnt)
अणु
	काष्ठा qib_pportdata *ppd, *pppd[QIB_MAX_IB_PORTS];
	अचिन्हित i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < dd->num_pports; i++)
		pppd[i] = शून्य;

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (!test_bit(i, mask))
			जारी;
		/*
		 * If the buffer is owned by the DMA hardware,
		 * reset the DMA engine.
		 */
		ppd = is_sdma_buf(dd, i);
		अगर (ppd) अणु
			pppd[ppd->port] = ppd;
			जारी;
		पूर्ण
		/*
		 * If the kernel is writing the buffer or the buffer is
		 * owned by a user process, we can't clear it yet.
		 */
		spin_lock_irqsave(&dd->pioavail_lock, flags);
		अगर (test_bit(i, dd->pio_writing) ||
		    (!test_bit(i << 1, dd->pioavailkernel) &&
		     find_ctxt(dd, i))) अणु
			__set_bit(i, dd->pio_need_disarm);
		पूर्ण अन्यथा अणु
			dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_BUF(i));
		पूर्ण
		spin_unlock_irqrestore(&dd->pioavail_lock, flags);
	पूर्ण

	/* करो cancel_sends once per port that had sdma piobufs in error */
	क्रम (i = 0; i < dd->num_pports; i++)
		अगर (pppd[i])
			qib_cancel_sends(pppd[i]);
पूर्ण

/**
 * update_send_bufs - update shaकरोw copy of the PIO availability map
 * @dd: the qlogic_ib device
 *
 * called whenever our local copy indicates we have run out of send buffers
 */
अटल व्योम update_send_bufs(काष्ठा qib_devdata *dd)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित i;
	स्थिर अचिन्हित piobregs = dd->pioavregs;

	/*
	 * If the generation (check) bits have changed, then we update the
	 * busy bit क्रम the corresponding PIO buffer.  This algorithm will
	 * modअगरy positions to the value they alपढ़ोy have in some हालs
	 * (i.e., no change), but it's faster than changing only the bits
	 * that have changed.
	 *
	 * We would like to करो this atomicly, to aव्योम spinlocks in the
	 * critical send path, but that's not really possible, given the
	 * type of changes, and that this routine could be called on
	 * multiple cpu's simultaneously, so we lock in this routine only,
	 * to aव्योम conflicting updates; all we change is the shaकरोw, and
	 * it's a single 64 bit memory location, so by definition the update
	 * is atomic in terms of what other cpu's can see in testing the
	 * bits.  The spin_lock overhead isn't too bad, since it only
	 * happens when all buffers are in use, so only cpu overhead, not
	 * latency or bandwidth is affected.
	 */
	अगर (!dd->pioavailregs_dma)
		वापस;
	spin_lock_irqsave(&dd->pioavail_lock, flags);
	क्रम (i = 0; i < piobregs; i++) अणु
		u64 pchbusy, pchg, piov, pnew;

		piov = le64_to_cpu(dd->pioavailregs_dma[i]);
		pchg = dd->pioavailkernel[i] &
			~(dd->pioavailshaकरोw[i] ^ piov);
		pchbusy = pchg << QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT;
		अगर (pchg && (pchbusy & dd->pioavailshaकरोw[i])) अणु
			pnew = dd->pioavailshaकरोw[i] & ~pchbusy;
			pnew |= piov & pchbusy;
			dd->pioavailshaकरोw[i] = pnew;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dd->pioavail_lock, flags);
पूर्ण

/*
 * Debugging code and stats updates अगर no pio buffers available.
 */
अटल noअंतरभूत व्योम no_send_bufs(काष्ठा qib_devdata *dd)
अणु
	dd->upd_pio_shaकरोw = 1;

	/* not atomic, but अगर we lose a stat count in a जबतक, that's OK */
	qib_stats.sps_nopiobufs++;
पूर्ण

/*
 * Common code क्रम normal driver send buffer allocation, and reserved
 * allocation.
 *
 * Do appropriate marking as busy, etc.
 * Returns buffer poपूर्णांकer अगर one is found, otherwise शून्य.
 */
u32 __iomem *qib_माला_लोendbuf_range(काष्ठा qib_devdata *dd, u32 *pbufnum,
				  u32 first, u32 last)
अणु
	अचिन्हित i, j, updated = 0;
	अचिन्हित nbufs;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *shaकरोw = dd->pioavailshaकरोw;
	u32 __iomem *buf;

	अगर (!(dd->flags & QIB_PRESENT))
		वापस शून्य;

	nbufs = last - first + 1; /* number in range to check */
	अगर (dd->upd_pio_shaकरोw) अणु
update_shaकरोw:
		/*
		 * Minor optimization.  If we had no buffers on last call,
		 * start out by करोing the update; जारी and करो scan even
		 * अगर no buffers were updated, to be paranoid.
		 */
		update_send_bufs(dd);
		updated++;
	पूर्ण
	i = first;
	/*
	 * While test_and_set_bit() is atomic, we करो that and then the
	 * change_bit(), and the pair is not.  See अगर this is the cause
	 * of the reमुख्यing armlaunch errors.
	 */
	spin_lock_irqsave(&dd->pioavail_lock, flags);
	अगर (dd->last_pio >= first && dd->last_pio <= last)
		i = dd->last_pio + 1;
	अगर (!first)
		/* adjust to min possible  */
		nbufs = last - dd->min_kernel_pio + 1;
	क्रम (j = 0; j < nbufs; j++, i++) अणु
		अगर (i > last)
			i = !first ? dd->min_kernel_pio : first;
		अगर (__test_and_set_bit((2 * i) + 1, shaकरोw))
			जारी;
		/* flip generation bit */
		__change_bit(2 * i, shaकरोw);
		/* remember that the buffer can be written to now */
		__set_bit(i, dd->pio_writing);
		अगर (!first && first != last) /* first == last on VL15, aव्योम */
			dd->last_pio = i;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dd->pioavail_lock, flags);

	अगर (j == nbufs) अणु
		अगर (!updated)
			/*
			 * First समय through; shaकरोw exhausted, but may be
			 * buffers available, try an update and then rescan.
			 */
			जाओ update_shaकरोw;
		no_send_bufs(dd);
		buf = शून्य;
	पूर्ण अन्यथा अणु
		अगर (i < dd->piobcnt2k)
			buf = (u32 __iomem *)(dd->pio2kbase +
				i * dd->palign);
		अन्यथा अगर (i < dd->piobcnt2k + dd->piobcnt4k || !dd->piovl15base)
			buf = (u32 __iomem *)(dd->pio4kbase +
				(i - dd->piobcnt2k) * dd->align4k);
		अन्यथा
			buf = (u32 __iomem *)(dd->piovl15base +
				(i - (dd->piobcnt2k + dd->piobcnt4k)) *
				dd->align4k);
		अगर (pbufnum)
			*pbufnum = i;
		dd->upd_pio_shaकरोw = 0;
	पूर्ण

	वापस buf;
पूर्ण

/*
 * Record that the caller is finished writing to the buffer so we करोn't
 * disarm it जबतक it is being written and disarm it now अगर needed.
 */
व्योम qib_sendbuf_करोne(काष्ठा qib_devdata *dd, अचिन्हित n)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->pioavail_lock, flags);
	__clear_bit(n, dd->pio_writing);
	अगर (__test_and_clear_bit(n, dd->pio_need_disarm))
		dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_BUF(n));
	spin_unlock_irqrestore(&dd->pioavail_lock, flags);
पूर्ण

/**
 * qib_chg_pioavailkernel - change which send buffers are available क्रम kernel
 * @dd: the qlogic_ib device
 * @start: the starting send buffer number
 * @len: the number of send buffers
 * @avail: true अगर the buffers are available क्रम kernel use, false otherwise
 * @rcd: the context poपूर्णांकer
 */
व्योम qib_chg_pioavailkernel(काष्ठा qib_devdata *dd, अचिन्हित start,
	अचिन्हित len, u32 avail, काष्ठा qib_ctxtdata *rcd)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित end;
	अचिन्हित ostart = start;

	/* There are two bits per send buffer (busy and generation) */
	start *= 2;
	end = start + len * 2;

	spin_lock_irqsave(&dd->pioavail_lock, flags);
	/* Set or clear the busy bit in the shaकरोw. */
	जबतक (start < end) अणु
		अगर (avail) अणु
			अचिन्हित दीर्घ dma;
			पूर्णांक i;

			/*
			 * The BUSY bit will never be set, because we disarm
			 * the user buffers beक्रमe we hand them back to the
			 * kernel.  We करो have to make sure the generation
			 * bit is set correctly in shaकरोw, since it could
			 * have changed many बार जबतक allocated to user.
			 * We can't use the biपंचांगap functions on the full
			 * dma array because it is always little-endian, so
			 * we have to flip to host-order first.
			 * BITS_PER_LONG is slightly wrong, since it's
			 * always 64 bits per रेजिस्टर in chip...
			 * We only work on 64 bit kernels, so that's OK.
			 */
			i = start / BITS_PER_LONG;
			__clear_bit(QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT + start,
				    dd->pioavailshaकरोw);
			dma = (अचिन्हित दीर्घ)
				le64_to_cpu(dd->pioavailregs_dma[i]);
			अगर (test_bit((QLOGIC_IB_SENDPIOAVAIL_CHECK_SHIFT +
				      start) % BITS_PER_LONG, &dma))
				__set_bit(QLOGIC_IB_SENDPIOAVAIL_CHECK_SHIFT +
					  start, dd->pioavailshaकरोw);
			अन्यथा
				__clear_bit(QLOGIC_IB_SENDPIOAVAIL_CHECK_SHIFT
					    + start, dd->pioavailshaकरोw);
			__set_bit(start, dd->pioavailkernel);
			अगर ((start >> 1) < dd->min_kernel_pio)
				dd->min_kernel_pio = start >> 1;
		पूर्ण अन्यथा अणु
			__set_bit(start + QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT,
				  dd->pioavailshaकरोw);
			__clear_bit(start, dd->pioavailkernel);
			अगर ((start >> 1) > dd->min_kernel_pio)
				dd->min_kernel_pio = start >> 1;
		पूर्ण
		start += 2;
	पूर्ण

	अगर (dd->min_kernel_pio > 0 && dd->last_pio < dd->min_kernel_pio - 1)
		dd->last_pio = dd->min_kernel_pio - 1;
	spin_unlock_irqrestore(&dd->pioavail_lock, flags);

	dd->f_txchk_change(dd, ostart, len, avail, rcd);
पूर्ण

/*
 * Flush all sends that might be in the पढ़ोy to send state, as well as any
 * that are in the process of being sent.  Used whenever we need to be
 * sure the send side is idle.  Cleans up all buffer state by canceling
 * all pio buffers, and issuing an पात, which cleans up anything in the
 * launch fअगरo.  The cancel is superfluous on some chip versions, but
 * it's safer to always करो it.
 * PIOAvail bits are updated by the chip as अगर a normal send had happened.
 */
व्योम qib_cancel_sends(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा qib_ctxtdata *rcd;
	अचिन्हित दीर्घ flags;
	अचिन्हित ctxt;
	अचिन्हित i;
	अचिन्हित last;

	/*
	 * Tell PSM to disarm buffers again beक्रमe trying to reuse them.
	 * We need to be sure the rcd करोesn't change out from under us
	 * जबतक we करो so.  We hold the two locks sequentially.  We might
	 * needlessly set some need_disarm bits as a result, अगर the
	 * context is बंदd after we release the uctxt_lock, but that's
	 * fairly benign, and safer than nesting the locks.
	 */
	क्रम (ctxt = dd->first_user_ctxt; ctxt < dd->cfgctxts; ctxt++) अणु
		spin_lock_irqsave(&dd->uctxt_lock, flags);
		rcd = dd->rcd[ctxt];
		अगर (rcd && rcd->ppd == ppd) अणु
			last = rcd->pio_base + rcd->piocnt;
			अगर (rcd->user_event_mask) अणु
				/*
				 * subctxt_cnt is 0 अगर not shared, so करो base
				 * separately, first, then reमुख्यing subctxt,
				 * अगर any
				 */
				set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
					&rcd->user_event_mask[0]);
				क्रम (i = 1; i < rcd->subctxt_cnt; i++)
					set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
						&rcd->user_event_mask[i]);
			पूर्ण
			i = rcd->pio_base;
			spin_unlock_irqrestore(&dd->uctxt_lock, flags);
			spin_lock_irqsave(&dd->pioavail_lock, flags);
			क्रम (; i < last; i++)
				__set_bit(i, dd->pio_need_disarm);
			spin_unlock_irqrestore(&dd->pioavail_lock, flags);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&dd->uctxt_lock, flags);
	पूर्ण

	अगर (!(dd->flags & QIB_HAS_SEND_DMA))
		dd->f_sendctrl(ppd, QIB_SENDCTRL_DISARM_ALL |
				    QIB_SENDCTRL_FLUSH);
पूर्ण

/*
 * Force an update of in-memory copy of the pioavail रेजिस्टरs, when
 * needed क्रम any of a variety of reasons.
 * If alपढ़ोy off, this routine is a nop, on the assumption that the
 * caller (or set of callers) will "do the right thing".
 * This is a per-device operation, so just the first port.
 */
व्योम qib_क्रमce_pio_avail_update(काष्ठा qib_devdata *dd)
अणु
	dd->f_sendctrl(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
पूर्ण

व्योम qib_hol_करोwn(काष्ठा qib_pportdata *ppd)
अणु
	/*
	 * Cancel sends when the link goes DOWN so that we aren't करोing it
	 * at INIT when we might be trying to send SMI packets.
	 */
	अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG))
		qib_cancel_sends(ppd);
पूर्ण

/*
 * Link is at INIT.
 * We start the HoL समयr so we can detect stuck packets blocking SMP replies.
 * Timer may alपढ़ोy be running, so use mod_समयr, not add_समयr.
 */
व्योम qib_hol_init(काष्ठा qib_pportdata *ppd)
अणु
	अगर (ppd->hol_state != QIB_HOL_INIT) अणु
		ppd->hol_state = QIB_HOL_INIT;
		mod_समयr(&ppd->hol_समयr,
			  jअगरfies + msecs_to_jअगरfies(qib_hol_समयout_ms));
	पूर्ण
पूर्ण

/*
 * Link is up, जारी any user processes, and ensure समयr
 * is a nop, अगर running.  Let समयr keep running, अगर set; it
 * will nop when it sees the link is up.
 */
व्योम qib_hol_up(काष्ठा qib_pportdata *ppd)
अणु
	ppd->hol_state = QIB_HOL_UP;
पूर्ण

/*
 * This is only called via the समयr.
 */
व्योम qib_hol_event(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_pportdata *ppd = from_समयr(ppd, t, hol_समयr);

	/* If hardware error, etc, skip. */
	अगर (!(ppd->dd->flags & QIB_INITTED))
		वापस;

	अगर (ppd->hol_state != QIB_HOL_UP) अणु
		/*
		 * Try to flush sends in हाल a stuck packet is blocking
		 * SMP replies.
		 */
		qib_hol_करोwn(ppd);
		mod_समयr(&ppd->hol_समयr,
			  jअगरfies + msecs_to_jअगरfies(qib_hol_समयout_ms));
	पूर्ण
पूर्ण
