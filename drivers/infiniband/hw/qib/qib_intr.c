<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008, 2009, 2010 QLogic Corporation.
 * All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश "qib.h"
#समावेश "qib_common.h"

/**
 * qib_क्रमmat_hwmsg - क्रमmat a single hwerror message
 * @msg: message buffer
 * @msgl: length of message buffer
 * @hwmsg: message to add to message buffer
 */
अटल व्योम qib_क्रमmat_hwmsg(अक्षर *msg, माप_प्रकार msgl, स्थिर अक्षर *hwmsg)
अणु
	strlcat(msg, "[", msgl);
	strlcat(msg, hwmsg, msgl);
	strlcat(msg, "]", msgl);
पूर्ण

/**
 * qib_क्रमmat_hwerrors - क्रमmat hardware error messages क्रम display
 * @hwerrs: hardware errors bit vector
 * @hwerrmsgs: hardware error descriptions
 * @nhwerrmsgs: number of hwerrmsgs
 * @msg: message buffer
 * @msgl: message buffer length
 */
व्योम qib_क्रमmat_hwerrors(u64 hwerrs, स्थिर काष्ठा qib_hwerror_msgs *hwerrmsgs,
			 माप_प्रकार nhwerrmsgs, अक्षर *msg, माप_प्रकार msgl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nhwerrmsgs; i++)
		अगर (hwerrs & hwerrmsgs[i].mask)
			qib_क्रमmat_hwmsg(msg, msgl, hwerrmsgs[i].msg);
पूर्ण

अटल व्योम संकेत_ib_event(काष्ठा qib_pportdata *ppd, क्रमागत ib_event_type ev)
अणु
	काष्ठा ib_event event;
	काष्ठा qib_devdata *dd = ppd->dd;

	event.device = &dd->verbs_dev.rdi.ibdev;
	event.element.port_num = ppd->port;
	event.event = ev;
	ib_dispatch_event(&event);
पूर्ण

व्योम qib_handle_e_ibstatuschanged(काष्ठा qib_pportdata *ppd, u64 ibcs)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;
	u32 lstate;
	u8 ltstate;
	क्रमागत ib_event_type ev = 0;

	lstate = dd->f_iblink_state(ibcs); /* linkstate */
	ltstate = dd->f_ibphys_portstate(ibcs);

	/*
	 * If linkstate transitions पूर्णांकo INIT from any of the various करोwn
	 * states, or अगर it transitions from any of the up (INIT or better)
	 * states पूर्णांकo any of the करोwn states (except link recovery), then
	 * call the chip-specअगरic code to take appropriate actions.
	 *
	 * ppd->lflags could be 0 अगर this is the first समय the पूर्णांकerrupt
	 * handlers has been called but the link is alपढ़ोy up.
	 */
	अगर (lstate >= IB_PORT_INIT &&
	    (!ppd->lflags || (ppd->lflags & QIBL_LINKDOWN)) &&
	    ltstate == IB_PHYSPORTSTATE_LINKUP) अणु
		/* transitioned to UP */
		अगर (dd->f_ib_upकरोwn(ppd, 1, ibcs))
			जाओ skip_ibchange; /* chip-code handled */
	पूर्ण अन्यथा अगर (ppd->lflags & (QIBL_LINKINIT | QIBL_LINKARMED |
		   QIBL_LINKACTIVE | QIBL_IB_FORCE_NOTIFY)) अणु
		अगर (ltstate != IB_PHYSPORTSTATE_LINKUP &&
		    ltstate <= IB_PHYSPORTSTATE_CFG_TRAIN &&
		    dd->f_ib_upकरोwn(ppd, 0, ibcs))
			जाओ skip_ibchange; /* chip-code handled */
		qib_set_uevent_bits(ppd, _QIB_EVENT_LINKDOWN_BIT);
	पूर्ण

	अगर (lstate != IB_PORT_DOWN) अणु
		/* lstate is INIT, ARMED, or ACTIVE */
		अगर (lstate != IB_PORT_ACTIVE) अणु
			*ppd->statusp &= ~QIB_STATUS_IB_READY;
			अगर (ppd->lflags & QIBL_LINKACTIVE)
				ev = IB_EVENT_PORT_ERR;
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			अगर (lstate == IB_PORT_ARMED) अणु
				ppd->lflags |= QIBL_LINKARMED | QIBL_LINKV;
				ppd->lflags &= ~(QIBL_LINKINIT |
					QIBL_LINKDOWN | QIBL_LINKACTIVE);
			पूर्ण अन्यथा अणु
				ppd->lflags |= QIBL_LINKINIT | QIBL_LINKV;
				ppd->lflags &= ~(QIBL_LINKARMED |
					QIBL_LINKDOWN | QIBL_LINKACTIVE);
			पूर्ण
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
			/* start a 75msec समयr to clear symbol errors */
			mod_समयr(&ppd->symerr_clear_समयr,
				  msecs_to_jअगरfies(75));
		पूर्ण अन्यथा अगर (ltstate == IB_PHYSPORTSTATE_LINKUP &&
			   !(ppd->lflags & QIBL_LINKACTIVE)) अणु
			/* active, but not active defered */
			qib_hol_up(ppd); /* useful only क्रम 6120 now */
			*ppd->statusp |=
				QIB_STATUS_IB_READY | QIB_STATUS_IB_CONF;
			qib_clear_symerror_on_linkup(&ppd->symerr_clear_समयr);
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags |= QIBL_LINKACTIVE | QIBL_LINKV;
			ppd->lflags &= ~(QIBL_LINKINIT |
				QIBL_LINKDOWN | QIBL_LINKARMED);
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
			अगर (dd->flags & QIB_HAS_SEND_DMA)
				qib_sdma_process_event(ppd,
					qib_sdma_event_e30_go_running);
			ev = IB_EVENT_PORT_ACTIVE;
			dd->f_setextled(ppd, 1);
		पूर्ण
	पूर्ण अन्यथा अणु /* करोwn */
		अगर (ppd->lflags & QIBL_LINKACTIVE)
			ev = IB_EVENT_PORT_ERR;
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_LINKDOWN | QIBL_LINKV;
		ppd->lflags &= ~(QIBL_LINKINIT |
				 QIBL_LINKACTIVE | QIBL_LINKARMED);
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		*ppd->statusp &= ~QIB_STATUS_IB_READY;
	पूर्ण

skip_ibchange:
	ppd->lastibcstat = ibcs;
	अगर (ev)
		संकेत_ib_event(ppd, ev);
पूर्ण

व्योम qib_clear_symerror_on_linkup(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_pportdata *ppd = from_समयr(ppd, t, symerr_clear_समयr);

	अगर (ppd->lflags & QIBL_LINKACTIVE)
		वापस;

	ppd->ibport_data.z_symbol_error_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBSYMBOLERR);
पूर्ण

/*
 * Handle receive पूर्णांकerrupts क्रम user ctxts; this means a user
 * process was रुकोing क्रम a packet to arrive, and didn't want
 * to poll.
 */
व्योम qib_handle_urcv(काष्ठा qib_devdata *dd, u64 ctxtr)
अणु
	काष्ठा qib_ctxtdata *rcd;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	क्रम (i = dd->first_user_ctxt; dd->rcd && i < dd->cfgctxts; i++) अणु
		अगर (!(ctxtr & (1ULL << i)))
			जारी;
		rcd = dd->rcd[i];
		अगर (!rcd || !rcd->cnt)
			जारी;

		अगर (test_and_clear_bit(QIB_CTXT_WAITING_RCV, &rcd->flag)) अणु
			wake_up_पूर्णांकerruptible(&rcd->रुको);
			dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_INTRAVAIL_DIS,
				      rcd->ctxt);
		पूर्ण अन्यथा अगर (test_and_clear_bit(QIB_CTXT_WAITING_URG,
					      &rcd->flag)) अणु
			rcd->urgent++;
			wake_up_पूर्णांकerruptible(&rcd->रुको);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);
पूर्ण

व्योम qib_bad_पूर्णांकrstatus(काष्ठा qib_devdata *dd)
अणु
	अटल पूर्णांक allbits;

	/* separate routine, क्रम better optimization of qib_पूर्णांकr() */

	/*
	 * We prपूर्णांक the message and disable पूर्णांकerrupts, in hope of
	 * having a better chance of debugging the problem.
	 */
	qib_dev_err(dd,
		"Read of chip interrupt status failed disabling interrupts\n");
	अगर (allbits++) अणु
		/* disable पूर्णांकerrupt delivery, something is very wrong */
		अगर (allbits == 2)
			dd->f_set_पूर्णांकr_state(dd, 0);
		अगर (allbits == 3) अणु
			qib_dev_err(dd,
				"2nd bad interrupt status, unregistering interrupts\n");
			dd->flags |= QIB_BADINTR;
			dd->flags &= ~QIB_INITTED;
			dd->f_मुक्त_irq(dd);
		पूर्ण
	पूर्ण
पूर्ण
