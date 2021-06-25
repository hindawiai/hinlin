<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "hfi.h"
#समावेश "common.h"
#समावेश "sdma.h"

#घोषणा LINK_UP_DELAY  500  /* in microseconds */

अटल व्योम set_mgmt_allowed(काष्ठा hfi1_pportdata *ppd)
अणु
	u32 frame;
	काष्ठा hfi1_devdata *dd = ppd->dd;

	अगर (ppd->neighbor_type == NEIGHBOR_TYPE_HFI) अणु
		ppd->mgmt_allowed = 1;
	पूर्ण अन्यथा अणु
		पढ़ो_8051_config(dd, REMOTE_LNI_INFO, GENERAL_CONFIG, &frame);
		ppd->mgmt_allowed = (frame >> MGMT_ALLOWED_SHIFT)
		& MGMT_ALLOWED_MASK;
	पूर्ण
पूर्ण

/*
 * Our neighbor has indicated that we are allowed to act as a fabric
 * manager, so place the full management partition key in the second
 * (0-based) pkey array position. Note that we should alपढ़ोy have
 * the limited management partition key in array element 1, and also
 * that the port is not yet up when add_full_mgmt_pkey() is invoked.
 */
अटल व्योम add_full_mgmt_pkey(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;

	/* Sanity check - ppd->pkeys[2] should be 0, or alपढ़ोy initialized */
	अगर (!((ppd->pkeys[2] == 0) || (ppd->pkeys[2] == FULL_MGMT_P_KEY)))
		dd_dev_warn(dd, "%s pkey[2] already set to 0x%x, resetting it to 0x%x\n",
			    __func__, ppd->pkeys[2], FULL_MGMT_P_KEY);
	ppd->pkeys[2] = FULL_MGMT_P_KEY;
	(व्योम)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_PKEYS, 0);
	hfi1_event_pkey_change(ppd->dd, ppd->port);
पूर्ण

/**
 * क्रमmat_hwmsg - क्रमmat a single hwerror message
 * @msg: message buffer
 * @msgl: length of message buffer
 * @hwmsg: message to add to message buffer
 */
अटल व्योम क्रमmat_hwmsg(अक्षर *msg, माप_प्रकार msgl, स्थिर अक्षर *hwmsg)
अणु
	strlcat(msg, "[", msgl);
	strlcat(msg, hwmsg, msgl);
	strlcat(msg, "]", msgl);
पूर्ण

/**
 * hfi1_क्रमmat_hwerrors - क्रमmat hardware error messages क्रम display
 * @hwerrs: hardware errors bit vector
 * @hwerrmsgs: hardware error descriptions
 * @nhwerrmsgs: number of hwerrmsgs
 * @msg: message buffer
 * @msgl: message buffer length
 */
व्योम hfi1_क्रमmat_hwerrors(u64 hwerrs, स्थिर काष्ठा hfi1_hwerror_msgs *hwerrmsgs,
			  माप_प्रकार nhwerrmsgs, अक्षर *msg, माप_प्रकार msgl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nhwerrmsgs; i++)
		अगर (hwerrs & hwerrmsgs[i].mask)
			क्रमmat_hwmsg(msg, msgl, hwerrmsgs[i].msg);
पूर्ण

अटल व्योम संकेत_ib_event(काष्ठा hfi1_pportdata *ppd, क्रमागत ib_event_type ev)
अणु
	काष्ठा ib_event event;
	काष्ठा hfi1_devdata *dd = ppd->dd;

	/*
	 * Only call ib_dispatch_event() अगर the IB device has been
	 * रेजिस्टरed.  HFI1_INITED is set अगरf the driver has successfully
	 * रेजिस्टरed with the IB core.
	 */
	अगर (!(dd->flags & HFI1_INITTED))
		वापस;
	event.device = &dd->verbs_dev.rdi.ibdev;
	event.element.port_num = ppd->port;
	event.event = ev;
	ib_dispatch_event(&event);
पूर्ण

/**
 * handle_linkup_change - finish linkup/करोwn state changes
 * @dd: valid device
 * @linkup: link state inक्रमmation
 *
 * Handle a linkup or link करोwn notअगरication.
 * The HW needs समय to finish its link up state change. Give it that chance.
 *
 * This is called outside an पूर्णांकerrupt.
 *
 */
व्योम handle_linkup_change(काष्ठा hfi1_devdata *dd, u32 linkup)
अणु
	काष्ठा hfi1_pportdata *ppd = &dd->pport[0];
	क्रमागत ib_event_type ev;

	अगर (!(ppd->linkup ^ !!linkup))
		वापस;	/* no change, nothing to करो */

	अगर (linkup) अणु
		/*
		 * Quick linkup and all link up on the simulator करोes not
		 * trigger or implement:
		 *	- VerअगरyCap पूर्णांकerrupt
		 *	- VerअगरyCap frames
		 * But rather moves directly to LinkUp.
		 *
		 * Do the work of the VerअगरyCap पूर्णांकerrupt handler,
		 * handle_verअगरy_cap(), but करो not try moving the state to
		 * LinkUp as we are alपढ़ोy there.
		 *
		 * NOTE: This uses this device's vAU, vCU, and vl15_init क्रम
		 * the remote values.  Both sides must be using the values.
		 */
		अगर (quick_linkup || dd->icode == ICODE_FUNCTIONAL_SIMULATOR) अणु
			set_up_vau(dd, dd->vau);
			set_up_vl15(dd, dd->vl15_init);
			assign_remote_cm_au_table(dd, dd->vcu);
		पूर्ण

		ppd->neighbor_guid =
			पढ़ो_csr(dd, DC_DC8051_STS_REMOTE_GUID);
		ppd->neighbor_type =
			पढ़ो_csr(dd, DC_DC8051_STS_REMOTE_NODE_TYPE) &
				 DC_DC8051_STS_REMOTE_NODE_TYPE_VAL_MASK;
		ppd->neighbor_port_number =
			पढ़ो_csr(dd, DC_DC8051_STS_REMOTE_PORT_NO) &
				 DC_DC8051_STS_REMOTE_PORT_NO_VAL_SMASK;
		ppd->neighbor_fm_security =
			पढ़ो_csr(dd, DC_DC8051_STS_REMOTE_FM_SECURITY) &
				 DC_DC8051_STS_LOCAL_FM_SECURITY_DISABLED_MASK;
		dd_dev_info(dd,
			    "Neighbor Guid %llx, Type %d, Port Num %d\n",
			    ppd->neighbor_guid, ppd->neighbor_type,
			    ppd->neighbor_port_number);

		/* HW needs LINK_UP_DELAY to settle, give it that chance */
		udelay(LINK_UP_DELAY);

		/*
		 * 'MgmtAllowed' inक्रमmation, which is exchanged during
		 * LNI, is available at this poपूर्णांक.
		 */
		set_mgmt_allowed(ppd);

		अगर (ppd->mgmt_allowed)
			add_full_mgmt_pkey(ppd);

		/* physical link went up */
		ppd->linkup = 1;
		ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE);

		/* link widths are not available until the link is fully up */
		get_linkup_link_widths(ppd);

	पूर्ण अन्यथा अणु
		/* physical link went करोwn */
		ppd->linkup = 0;

		/* clear HW details of the previous connection */
		ppd->actual_vls_operational = 0;
		reset_link_credits(dd);

		/* मुक्तze after a link करोwn to guarantee a clean egress */
		start_मुक्तze_handling(ppd, FREEZE_SELF | FREEZE_LINK_DOWN);

		ev = IB_EVENT_PORT_ERR;

		hfi1_set_uevent_bits(ppd, _HFI1_EVENT_LINKDOWN_BIT);

		/* अगर we are करोwn, the neighbor is करोwn */
		ppd->neighbor_normal = 0;

		/* notअगरy IB of the link change */
		संकेत_ib_event(ppd, ev);
	पूर्ण
पूर्ण

/*
 * Handle receive or urgent पूर्णांकerrupts क्रम user contexts.  This means a user
 * process was रुकोing क्रम a packet to arrive, and didn't want to poll.
 */
व्योम handle_user_पूर्णांकerrupt(काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	अगर (biपंचांगap_empty(rcd->in_use_ctxts, HFI1_MAX_SHARED_CTXTS))
		जाओ करोne;

	अगर (test_and_clear_bit(HFI1_CTXT_WAITING_RCV, &rcd->event_flags)) अणु
		wake_up_पूर्णांकerruptible(&rcd->रुको);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_INTRAVAIL_DIS, rcd);
	पूर्ण अन्यथा अगर (test_and_clear_bit(HFI1_CTXT_WAITING_URG,
							&rcd->event_flags)) अणु
		rcd->urgent++;
		wake_up_पूर्णांकerruptible(&rcd->रुको);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);
पूर्ण
