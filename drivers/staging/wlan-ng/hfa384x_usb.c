<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/prism2/driver/hfa384x_usb.c
 *
 * Functions that talk to the USB variant of the Intersil hfa384x MAC
 *
 * Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * linux-wlan
 *
 *   The contents of this file are subject to the Mozilla Public
 *   License Version 1.1 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.mozilla.org/MPL/
 *
 *   Software distributed under the License is distributed on an "AS
 *   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *   implied. See the License क्रम the specअगरic language governing
 *   rights and limitations under the License.
 *
 *   Alternatively, the contents of this file may be used under the
 *   terms of the GNU Public License version 2 (the "GPL"), in which
 *   हाल the provisions of the GPL are applicable instead of the
 *   above.  If you wish to allow the use of your version of this file
 *   only under the terms of the GPL and not to allow others to use
 *   your version of this file under the MPL, indicate your decision
 *   by deleting the provisions above and replace them with the notice
 *   and other provisions required by the GPL.  If you करो not delete
 *   the provisions above, a recipient may use your version of this
 *   file under either the MPL or the GPL.
 *
 * --------------------------------------------------------------------
 *
 * Inquiries regarding the linux-wlan Open Source project can be
 * made directly to:
 *
 * AbsoluteValue Systems Inc.
 * info@linux-wlan.com
 * http://www.linux-wlan.com
 *
 * --------------------------------------------------------------------
 *
 * Portions of the development of this software were funded by
 * Intersil Corporation as part of PRISM(R) chipset product development.
 *
 * --------------------------------------------------------------------
 *
 * This file implements functions that correspond to the prism2/hfa384x
 * 802.11 MAC hardware and firmware host पूर्णांकerface.
 *
 * The functions can be considered to represent several levels of
 * असलtraction.  The lowest level functions are simply C-callable wrappers
 * around the रेजिस्टर accesses.  The next higher level represents C-callable
 * prism2 API functions that match the Intersil करोcumentation as बंदly
 * as is reasonable.  The next higher layer implements common sequences
 * of invocations of the API layer (e.g. ग_लिखो to bap, followed by cmd).
 *
 * Common sequences:
 * hfa384x_drvr_xxx	Highest level असलtractions provided by the
 *			hfa384x code.  They are driver defined wrappers
 *			क्रम common sequences.  These functions generally
 *			use the services of the lower levels.
 *
 * hfa384x_drvr_xxxconfig  An example of the drvr level असलtraction. These
 *			functions are wrappers क्रम the RID get/set
 *			sequence. They call copy_[to|from]_bap() and
 *			cmd_access(). These functions operate on the
 *			RIDs and buffers without validation. The caller
 *			is responsible क्रम that.
 *
 * API wrapper functions:
 * hfa384x_cmd_xxx	functions that provide access to the f/w commands.
 *			The function arguments correspond to each command
 *			argument, even command arguments that get packed
 *			पूर्णांकo single रेजिस्टरs.  These functions _just_
 *			issue the command by setting the cmd/parm regs
 *			& पढ़ोing the status/resp regs.  Additional
 *			activities required to fully use a command
 *			(पढ़ो/ग_लिखो from/to bap, get/set पूर्णांक status etc.)
 *			are implemented separately.  Think of these as
 *			C-callable prism2 commands.
 *
 * Lowest Layer Functions:
 * hfa384x_करोcmd_xxx	These functions implement the sequence required
 *			to issue any prism2 command.  Primarily used by the
 *			hfa384x_cmd_xxx functions.
 *
 * hfa384x_bap_xxx	BAP पढ़ो/ग_लिखो access functions.
 *			Note: we usually use BAP0 क्रम non-पूर्णांकerrupt context
 *			 and BAP1 क्रम पूर्णांकerrupt context.
 *
 * hfa384x_dl_xxx	करोwnload related functions.
 *
 * Driver State Issues:
 * Note that there are two pairs of functions that manage the
 * 'initialized' and 'running' states of the hw/MAC combo.  The four
 * functions are create(), destroy(), start(), and stop().  create()
 * sets up the data काष्ठाures required to support the hfa384x_*
 * functions and destroy() cleans them up.  The start() function माला_लो
 * the actual hardware running and enables the पूर्णांकerrupts.  The stop()
 * function shuts the hardware करोwn.  The sequence should be:
 * create()
 * start()
 *  .
 *  .  Do पूर्णांकeresting things w/ the hardware
 *  .
 * stop()
 * destroy()
 *
 * Note that destroy() can be called without calling stop() first.
 * --------------------------------------------------------------------
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/byteorder/generic.h>

#समावेश "p80211types.h"
#समावेश "p80211hdr.h"
#समावेश "p80211mgmt.h"
#समावेश "p80211conv.h"
#समावेश "p80211msg.h"
#समावेश "p80211netdev.h"
#समावेश "p80211req.h"
#समावेश "p80211metadef.h"
#समावेश "p80211metastruct.h"
#समावेश "hfa384x.h"
#समावेश "prism2mgmt.h"

क्रमागत cmd_mode अणु
	DOWAIT = 0,
	DOASYNC
पूर्ण;

#घोषणा THROTTLE_JIFFIES	(HZ / 8)
#घोषणा URB_ASYNC_UNLINK 0
#घोषणा USB_QUEUE_BULK 0

#घोषणा ROUNDUP64(a) (((a) + 63) & ~63)

#अगर_घोषित DEBUG_USB
अटल व्योम dbprपूर्णांक_urb(काष्ठा urb *urb);
#पूर्ण_अगर

अटल व्योम hfa384x_पूर्णांक_rxmonitor(काष्ठा wlandevice *wlandev,
				  काष्ठा hfa384x_usb_rxfrm *rxfrm);

अटल व्योम hfa384x_usb_defer(काष्ठा work_काष्ठा *data);

अटल पूर्णांक submit_rx_urb(काष्ठा hfa384x *hw, gfp_t flags);

अटल पूर्णांक submit_tx_urb(काष्ठा hfa384x *hw, काष्ठा urb *tx_urb, gfp_t flags);

/*---------------------------------------------------*/
/* Callbacks */
अटल व्योम hfa384x_usbout_callback(काष्ठा urb *urb);
अटल व्योम hfa384x_ctlxout_callback(काष्ठा urb *urb);
अटल व्योम hfa384x_usbin_callback(काष्ठा urb *urb);

अटल व्योम
hfa384x_usbin_txcompl(काष्ठा wlandevice *wlandev, जोड़ hfa384x_usbin *usbin);

अटल व्योम hfa384x_usbin_rx(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb);

अटल व्योम hfa384x_usbin_info(काष्ठा wlandevice *wlandev,
			       जोड़ hfa384x_usbin *usbin);

अटल व्योम hfa384x_usbin_ctlx(काष्ठा hfa384x *hw, जोड़ hfa384x_usbin *usbin,
			       पूर्णांक urb_status);

/*---------------------------------------------------*/
/* Functions to support the prism2 usb command queue */

अटल व्योम hfa384x_usbctlxq_run(काष्ठा hfa384x *hw);

अटल व्योम hfa384x_usbctlx_reqसमयrfn(काष्ठा समयr_list *t);

अटल व्योम hfa384x_usbctlx_respसमयrfn(काष्ठा समयr_list *t);

अटल व्योम hfa384x_usb_throttlefn(काष्ठा समयr_list *t);

अटल व्योम hfa384x_usbctlx_completion_task(काष्ठा tasklet_काष्ठा *t);

अटल व्योम hfa384x_usbctlx_reaper_task(काष्ठा tasklet_काष्ठा *t);

अटल पूर्णांक hfa384x_usbctlx_submit(काष्ठा hfa384x *hw,
				  काष्ठा hfa384x_usbctlx *ctlx);

अटल व्योम unlocked_usbctlx_complete(काष्ठा hfa384x *hw,
				      काष्ठा hfa384x_usbctlx *ctlx);

काष्ठा usbctlx_completor अणु
	पूर्णांक (*complete)(काष्ठा usbctlx_completor *completor);
पूर्ण;

अटल पूर्णांक
hfa384x_usbctlx_complete_sync(काष्ठा hfa384x *hw,
			      काष्ठा hfa384x_usbctlx *ctlx,
			      काष्ठा usbctlx_completor *completor);

अटल पूर्णांक
unlocked_usbctlx_cancel_async(काष्ठा hfa384x *hw, काष्ठा hfa384x_usbctlx *ctlx);

अटल व्योम hfa384x_cb_status(काष्ठा hfa384x *hw,
			      स्थिर काष्ठा hfa384x_usbctlx *ctlx);

अटल पूर्णांक
usbctlx_get_status(स्थिर काष्ठा hfa384x_usb_statusresp *cmdresp,
		   काष्ठा hfa384x_cmdresult *result);

अटल व्योम
usbctlx_get_rridresult(स्थिर काष्ठा hfa384x_usb_rridresp *rridresp,
		       काष्ठा hfa384x_rridresult *result);

/*---------------------------------------------------*/
/* Low level req/resp CTLX क्रमmatters and submitters */
अटल अंतरभूत पूर्णांक
hfa384x_करोcmd(काष्ठा hfa384x *hw,
	      काष्ठा hfa384x_metacmd *cmd);

अटल पूर्णांक
hfa384x_करोrrid(काष्ठा hfa384x *hw,
	       क्रमागत cmd_mode mode,
	       u16 rid,
	       व्योम *riddata,
	       अचिन्हित पूर्णांक riddatalen,
	       ctlx_cmdcb_t cmdcb, ctlx_usercb_t usercb, व्योम *usercb_data);

अटल पूर्णांक
hfa384x_करोwrid(काष्ठा hfa384x *hw,
	       क्रमागत cmd_mode mode,
	       u16 rid,
	       व्योम *riddata,
	       अचिन्हित पूर्णांक riddatalen,
	       ctlx_cmdcb_t cmdcb, ctlx_usercb_t usercb, व्योम *usercb_data);

अटल पूर्णांक
hfa384x_करोrmem(काष्ठा hfa384x *hw,
	       u16 page,
	       u16 offset,
	       व्योम *data,
	       अचिन्हित पूर्णांक len);

अटल पूर्णांक
hfa384x_करोwmem(काष्ठा hfa384x *hw,
	       u16 page,
	       u16 offset,
	       व्योम *data,
	       अचिन्हित पूर्णांक len);

अटल पूर्णांक hfa384x_isgood_pdrcode(u16 pdrcode);

अटल अंतरभूत स्थिर अक्षर *ctlxstr(क्रमागत ctlx_state s)
अणु
	अटल स्थिर अक्षर * स्थिर ctlx_str[] = अणु
		"Initial state",
		"Complete",
		"Request failed",
		"Request pending",
		"Request packet submitted",
		"Request packet completed",
		"Response packet completed"
	पूर्ण;

	वापस ctlx_str[s];
पूर्ण;

अटल अंतरभूत काष्ठा hfa384x_usbctlx *get_active_ctlx(काष्ठा hfa384x *hw)
अणु
	वापस list_entry(hw->ctlxq.active.next, काष्ठा hfa384x_usbctlx, list);
पूर्ण

#अगर_घोषित DEBUG_USB
व्योम dbprपूर्णांक_urb(काष्ठा urb *urb)
अणु
	pr_debug("urb->pipe=0x%08x\n", urb->pipe);
	pr_debug("urb->status=0x%08x\n", urb->status);
	pr_debug("urb->transfer_flags=0x%08x\n", urb->transfer_flags);
	pr_debug("urb->transfer_buffer=0x%08x\n",
		 (अचिन्हित पूर्णांक)urb->transfer_buffer);
	pr_debug("urb->transfer_buffer_length=0x%08x\n",
		 urb->transfer_buffer_length);
	pr_debug("urb->actual_length=0x%08x\n", urb->actual_length);
	pr_debug("urb->setup_packet(ctl)=0x%08x\n",
		 (अचिन्हित पूर्णांक)urb->setup_packet);
	pr_debug("urb->start_frame(iso/irq)=0x%08x\n", urb->start_frame);
	pr_debug("urb->interval(irq)=0x%08x\n", urb->पूर्णांकerval);
	pr_debug("urb->error_count(iso)=0x%08x\n", urb->error_count);
	pr_debug("urb->context=0x%08x\n", (अचिन्हित पूर्णांक)urb->context);
	pr_debug("urb->complete=0x%08x\n", (अचिन्हित पूर्णांक)urb->complete);
पूर्ण
#पूर्ण_अगर

/*----------------------------------------------------------------
 * submit_rx_urb
 *
 * Listen क्रम input data on the BULK-IN pipe. If the pipe has
 * stalled then schedule it to be reset.
 *
 * Arguments:
 *	hw		device काष्ठा
 *	memflags	memory allocation flags
 *
 * Returns:
 *	error code from submission
 *
 * Call context:
 *	Any
 *----------------------------------------------------------------
 */
अटल पूर्णांक submit_rx_urb(काष्ठा hfa384x *hw, gfp_t memflags)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक result;

	skb = dev_alloc_skb(माप(जोड़ hfa384x_usbin));
	अगर (!skb) अणु
		result = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Post the IN urb */
	usb_fill_bulk_urb(&hw->rx_urb, hw->usb,
			  hw->endp_in,
			  skb->data, माप(जोड़ hfa384x_usbin),
			  hfa384x_usbin_callback, hw->wlandev);

	hw->rx_urb_skb = skb;

	result = -ENOLINK;
	अगर (!hw->wlandev->hwहटाओd &&
	    !test_bit(WORK_RX_HALT, &hw->usb_flags)) अणु
		result = usb_submit_urb(&hw->rx_urb, memflags);

		/* Check whether we need to reset the RX pipe */
		अगर (result == -EPIPE) अणु
			netdev_warn(hw->wlandev->netdev,
				    "%s rx pipe stalled: requesting reset\n",
				    hw->wlandev->netdev->name);
			अगर (!test_and_set_bit(WORK_RX_HALT, &hw->usb_flags))
				schedule_work(&hw->usb_work);
		पूर्ण
	पूर्ण

	/* Don't leak memory अगर anything should go wrong */
	अगर (result != 0) अणु
		dev_kमुक्त_skb(skb);
		hw->rx_urb_skb = शून्य;
	पूर्ण

करोne:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * submit_tx_urb
 *
 * Prepares and submits the URB of transmitted data. If the
 * submission fails then it will schedule the output pipe to
 * be reset.
 *
 * Arguments:
 *	hw		device काष्ठा
 *	tx_urb		URB of data क्रम transmission
 *	memflags	memory allocation flags
 *
 * Returns:
 *	error code from submission
 *
 * Call context:
 *	Any
 *----------------------------------------------------------------
 */
अटल पूर्णांक submit_tx_urb(काष्ठा hfa384x *hw, काष्ठा urb *tx_urb, gfp_t memflags)
अणु
	काष्ठा net_device *netdev = hw->wlandev->netdev;
	पूर्णांक result;

	result = -ENOLINK;
	अगर (netअगर_running(netdev)) अणु
		अगर (!hw->wlandev->hwहटाओd &&
		    !test_bit(WORK_TX_HALT, &hw->usb_flags)) अणु
			result = usb_submit_urb(tx_urb, memflags);

			/* Test whether we need to reset the TX pipe */
			अगर (result == -EPIPE) अणु
				netdev_warn(hw->wlandev->netdev,
					    "%s tx pipe stalled: requesting reset\n",
					    netdev->name);
				set_bit(WORK_TX_HALT, &hw->usb_flags);
				schedule_work(&hw->usb_work);
			पूर्ण अन्यथा अगर (result == 0) अणु
				netअगर_stop_queue(netdev);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa394x_usb_defer
 *
 * There are some things that the USB stack cannot करो जबतक
 * in पूर्णांकerrupt context, so we arrange this function to run
 * in process context.
 *
 * Arguments:
 *	hw	device काष्ठाure
 *
 * Returns:
 *	nothing
 *
 * Call context:
 *	process (by design)
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usb_defer(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा hfa384x *hw = container_of(data, काष्ठा hfa384x, usb_work);
	काष्ठा net_device *netdev = hw->wlandev->netdev;

	/* Don't bother trying to reset anything अगर the plug
	 * has been pulled ...
	 */
	अगर (hw->wlandev->hwहटाओd)
		वापस;

	/* Reception has stopped: try to reset the input pipe */
	अगर (test_bit(WORK_RX_HALT, &hw->usb_flags)) अणु
		पूर्णांक ret;

		usb_समाप्त_urb(&hw->rx_urb); /* Cannot be holding spinlock! */

		ret = usb_clear_halt(hw->usb, hw->endp_in);
		अगर (ret != 0) अणु
			netdev_err(hw->wlandev->netdev,
				   "Failed to clear rx pipe for %s: err=%d\n",
				   netdev->name, ret);
		पूर्ण अन्यथा अणु
			netdev_info(hw->wlandev->netdev, "%s rx pipe reset complete.\n",
				    netdev->name);
			clear_bit(WORK_RX_HALT, &hw->usb_flags);
			set_bit(WORK_RX_RESUME, &hw->usb_flags);
		पूर्ण
	पूर्ण

	/* Resume receiving data back from the device. */
	अगर (test_bit(WORK_RX_RESUME, &hw->usb_flags)) अणु
		पूर्णांक ret;

		ret = submit_rx_urb(hw, GFP_KERNEL);
		अगर (ret != 0) अणु
			netdev_err(hw->wlandev->netdev,
				   "Failed to resume %s rx pipe.\n",
				   netdev->name);
		पूर्ण अन्यथा अणु
			clear_bit(WORK_RX_RESUME, &hw->usb_flags);
		पूर्ण
	पूर्ण

	/* Transmission has stopped: try to reset the output pipe */
	अगर (test_bit(WORK_TX_HALT, &hw->usb_flags)) अणु
		पूर्णांक ret;

		usb_समाप्त_urb(&hw->tx_urb);
		ret = usb_clear_halt(hw->usb, hw->endp_out);
		अगर (ret != 0) अणु
			netdev_err(hw->wlandev->netdev,
				   "Failed to clear tx pipe for %s: err=%d\n",
				   netdev->name, ret);
		पूर्ण अन्यथा अणु
			netdev_info(hw->wlandev->netdev, "%s tx pipe reset complete.\n",
				    netdev->name);
			clear_bit(WORK_TX_HALT, &hw->usb_flags);
			set_bit(WORK_TX_RESUME, &hw->usb_flags);

			/* Stopping the BULK-OUT pipe also blocked
			 * us from sending any more CTLX URBs, so
			 * we need to re-run our queue ...
			 */
			hfa384x_usbctlxq_run(hw);
		पूर्ण
	पूर्ण

	/* Resume transmitting. */
	अगर (test_and_clear_bit(WORK_TX_RESUME, &hw->usb_flags))
		netअगर_wake_queue(hw->wlandev->netdev);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_create
 *
 * Sets up the काष्ठा hfa384x data काष्ठाure क्रम use.  Note this
 * करोes _not_ initialize the actual hardware, just the data काष्ठाures
 * we use to keep track of its state.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	irq		device irq number
 *	iobase		i/o base address क्रम रेजिस्टर access
 *	membase		memory base address क्रम रेजिस्टर access
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
व्योम hfa384x_create(काष्ठा hfa384x *hw, काष्ठा usb_device *usb)
अणु
	hw->usb = usb;

	/* Set up the रुकोq */
	init_रुकोqueue_head(&hw->cmdq);

	/* Initialize the command queue */
	spin_lock_init(&hw->ctlxq.lock);
	INIT_LIST_HEAD(&hw->ctlxq.pending);
	INIT_LIST_HEAD(&hw->ctlxq.active);
	INIT_LIST_HEAD(&hw->ctlxq.completing);
	INIT_LIST_HEAD(&hw->ctlxq.reapable);

	/* Initialize the authentication queue */
	skb_queue_head_init(&hw->authq);

	tasklet_setup(&hw->reaper_bh, hfa384x_usbctlx_reaper_task);
	tasklet_setup(&hw->completion_bh, hfa384x_usbctlx_completion_task);
	INIT_WORK(&hw->link_bh, prism2sta_processing_defer);
	INIT_WORK(&hw->usb_work, hfa384x_usb_defer);

	समयr_setup(&hw->throttle, hfa384x_usb_throttlefn, 0);

	समयr_setup(&hw->respसमयr, hfa384x_usbctlx_respसमयrfn, 0);

	समयr_setup(&hw->reqसमयr, hfa384x_usbctlx_reqसमयrfn, 0);

	usb_init_urb(&hw->rx_urb);
	usb_init_urb(&hw->tx_urb);
	usb_init_urb(&hw->ctlx_urb);

	hw->link_status = HFA384x_LINK_NOTCONNECTED;
	hw->state = HFA384x_STATE_INIT;

	INIT_WORK(&hw->commsqual_bh, prism2sta_commsqual_defer);
	समयr_setup(&hw->commsqual_समयr, prism2sta_commsqual_समयr, 0);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_destroy
 *
 * Partner to hfa384x_create().  This function cleans up the hw
 * काष्ठाure so that it can be मुक्तd by the caller using a simple
 * kमुक्त.  Currently, this function is just a placeholder.  If, at some
 * poपूर्णांक in the future, an hw in the 'shutdown' state requires a 'deep'
 * kमुक्त, this is where it should be करोne.  Note that अगर this function
 * is called on a _running_ hw काष्ठाure, the drvr_stop() function is
 * called.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *
 * Returns:
 *	nothing, this function is not allowed to fail.
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
व्योम hfa384x_destroy(काष्ठा hfa384x *hw)
अणु
	काष्ठा sk_buff *skb;

	अगर (hw->state == HFA384x_STATE_RUNNING)
		hfa384x_drvr_stop(hw);
	hw->state = HFA384x_STATE_PREINIT;

	kमुक्त(hw->scanresults);
	hw->scanresults = शून्य;

	/* Now to clean out the auth queue */
	जबतक ((skb = skb_dequeue(&hw->authq)))
		dev_kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा hfa384x_usbctlx *usbctlx_alloc(व्योम)
अणु
	काष्ठा hfa384x_usbctlx *ctlx;

	ctlx = kzalloc(माप(*ctlx),
		       in_पूर्णांकerrupt() ? GFP_ATOMIC : GFP_KERNEL);
	अगर (ctlx)
		init_completion(&ctlx->करोne);

	वापस ctlx;
पूर्ण

अटल पूर्णांक
usbctlx_get_status(स्थिर काष्ठा hfa384x_usb_statusresp *cmdresp,
		   काष्ठा hfa384x_cmdresult *result)
अणु
	result->status = le16_to_cpu(cmdresp->status);
	result->resp0 = le16_to_cpu(cmdresp->resp0);
	result->resp1 = le16_to_cpu(cmdresp->resp1);
	result->resp2 = le16_to_cpu(cmdresp->resp2);

	pr_debug("cmdresult:status=0x%04x resp0=0x%04x resp1=0x%04x resp2=0x%04x\n",
		 result->status, result->resp0, result->resp1, result->resp2);

	वापस result->status & HFA384x_STATUS_RESULT;
पूर्ण

अटल व्योम
usbctlx_get_rridresult(स्थिर काष्ठा hfa384x_usb_rridresp *rridresp,
		       काष्ठा hfa384x_rridresult *result)
अणु
	result->rid = le16_to_cpu(rridresp->rid);
	result->riddata = rridresp->data;
	result->riddata_len = ((le16_to_cpu(rridresp->frmlen) - 1) * 2);
पूर्ण

/*----------------------------------------------------------------
 * Completor object:
 * This completor must be passed to hfa384x_usbctlx_complete_sync()
 * when processing a CTLX that वापसs a काष्ठा hfa384x_cmdresult काष्ठाure.
 *----------------------------------------------------------------
 */
काष्ठा usbctlx_cmd_completor अणु
	काष्ठा usbctlx_completor head;

	स्थिर काष्ठा hfa384x_usb_statusresp *cmdresp;
	काष्ठा hfa384x_cmdresult *result;
पूर्ण;

अटल अंतरभूत पूर्णांक usbctlx_cmd_completor_fn(काष्ठा usbctlx_completor *head)
अणु
	काष्ठा usbctlx_cmd_completor *complete;

	complete = (काष्ठा usbctlx_cmd_completor *)head;
	वापस usbctlx_get_status(complete->cmdresp, complete->result);
पूर्ण

अटल अंतरभूत काष्ठा usbctlx_completor *
init_cmd_completor(काष्ठा usbctlx_cmd_completor *completor,
		   स्थिर काष्ठा hfa384x_usb_statusresp *cmdresp,
		   काष्ठा hfa384x_cmdresult *result)
अणु
	completor->head.complete = usbctlx_cmd_completor_fn;
	completor->cmdresp = cmdresp;
	completor->result = result;
	वापस &completor->head;
पूर्ण

/*----------------------------------------------------------------
 * Completor object:
 * This completor must be passed to hfa384x_usbctlx_complete_sync()
 * when processing a CTLX that पढ़ोs a RID.
 *----------------------------------------------------------------
 */
काष्ठा usbctlx_rrid_completor अणु
	काष्ठा usbctlx_completor head;

	स्थिर काष्ठा hfa384x_usb_rridresp *rridresp;
	व्योम *riddata;
	अचिन्हित पूर्णांक riddatalen;
पूर्ण;

अटल पूर्णांक usbctlx_rrid_completor_fn(काष्ठा usbctlx_completor *head)
अणु
	काष्ठा usbctlx_rrid_completor *complete;
	काष्ठा hfa384x_rridresult rridresult;

	complete = (काष्ठा usbctlx_rrid_completor *)head;
	usbctlx_get_rridresult(complete->rridresp, &rridresult);

	/* Validate the length, note body len calculation in bytes */
	अगर (rridresult.riddata_len != complete->riddatalen) अणु
		pr_warn("RID len mismatch, rid=0x%04x hlen=%d fwlen=%d\n",
			rridresult.rid,
			complete->riddatalen, rridresult.riddata_len);
		वापस -ENODATA;
	पूर्ण

	स_नकल(complete->riddata, rridresult.riddata, complete->riddatalen);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा usbctlx_completor *
init_rrid_completor(काष्ठा usbctlx_rrid_completor *completor,
		    स्थिर काष्ठा hfa384x_usb_rridresp *rridresp,
		    व्योम *riddata,
		    अचिन्हित पूर्णांक riddatalen)
अणु
	completor->head.complete = usbctlx_rrid_completor_fn;
	completor->rridresp = rridresp;
	completor->riddata = riddata;
	completor->riddatalen = riddatalen;
	वापस &completor->head;
पूर्ण

/*----------------------------------------------------------------
 * Completor object:
 * Interprets the results of a synchronous RID-ग_लिखो
 *----------------------------------------------------------------
 */
#घोषणा init_wrid_completor  init_cmd_completor

/*----------------------------------------------------------------
 * Completor object:
 * Interprets the results of a synchronous memory-ग_लिखो
 *----------------------------------------------------------------
 */
#घोषणा init_wmem_completor  init_cmd_completor

/*----------------------------------------------------------------
 * Completor object:
 * Interprets the results of a synchronous memory-पढ़ो
 *----------------------------------------------------------------
 */
काष्ठा usbctlx_rmem_completor अणु
	काष्ठा usbctlx_completor head;

	स्थिर काष्ठा hfa384x_usb_rmemresp *rmemresp;
	व्योम *data;
	अचिन्हित पूर्णांक len;
पूर्ण;

अटल पूर्णांक usbctlx_rmem_completor_fn(काष्ठा usbctlx_completor *head)
अणु
	काष्ठा usbctlx_rmem_completor *complete =
		(काष्ठा usbctlx_rmem_completor *)head;

	pr_debug("rmemresp:len=%d\n", complete->rmemresp->frmlen);
	स_नकल(complete->data, complete->rmemresp->data, complete->len);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा usbctlx_completor *
init_rmem_completor(काष्ठा usbctlx_rmem_completor *completor,
		    काष्ठा hfa384x_usb_rmemresp *rmemresp,
		    व्योम *data,
		    अचिन्हित पूर्णांक len)
अणु
	completor->head.complete = usbctlx_rmem_completor_fn;
	completor->rmemresp = rmemresp;
	completor->data = data;
	completor->len = len;
	वापस &completor->head;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_cb_status
 *
 * Ctlx_complete handler क्रम async CMD type control exchanges.
 * mark the hw काष्ठा as such.
 *
 * Note: If the handling is changed here, it should probably be
 *       changed in करोcmd as well.
 *
 * Arguments:
 *	hw		hw काष्ठा
 *	ctlx		completed CTLX
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_cb_status(काष्ठा hfa384x *hw,
			      स्थिर काष्ठा hfa384x_usbctlx *ctlx)
अणु
	अगर (ctlx->usercb) अणु
		काष्ठा hfa384x_cmdresult cmdresult;

		अगर (ctlx->state != CTLX_COMPLETE) अणु
			स_रखो(&cmdresult, 0, माप(cmdresult));
			cmdresult.status =
			    HFA384x_STATUS_RESULT_SET(HFA384x_CMD_ERR);
		पूर्ण अन्यथा अणु
			usbctlx_get_status(&ctlx->inbuf.cmdresp, &cmdresult);
		पूर्ण

		ctlx->usercb(hw, &cmdresult, ctlx->usercb_data);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_cmd_initialize
 *
 * Issues the initialize command and sets the hw->state based
 * on the result.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_cmd_initialize(काष्ठा hfa384x *hw)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;
	काष्ठा hfa384x_metacmd cmd;

	cmd.cmd = HFA384x_CMDCODE_INIT;
	cmd.parm0 = 0;
	cmd.parm1 = 0;
	cmd.parm2 = 0;

	result = hfa384x_करोcmd(hw, &cmd);

	pr_debug("cmdresp.init: status=0x%04x, resp0=0x%04x, resp1=0x%04x, resp2=0x%04x\n",
		 cmd.result.status,
		 cmd.result.resp0, cmd.result.resp1, cmd.result.resp2);
	अगर (result == 0) अणु
		क्रम (i = 0; i < HFA384x_NUMPORTS_MAX; i++)
			hw->port_enabled[i] = 0;
	पूर्ण

	hw->link_status = HFA384x_LINK_NOTCONNECTED;

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_cmd_disable
 *
 * Issues the disable command to stop communications on one of
 * the MACs 'ports'.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	macport		MAC port number (host order)
 *
 * Returns:
 *	0		success
 *	>0		f/w reported failure - f/w status code
 *	<0		driver reported error (समयout|bad arg)
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_cmd_disable(काष्ठा hfa384x *hw, u16 macport)
अणु
	काष्ठा hfa384x_metacmd cmd;

	cmd.cmd = HFA384x_CMD_CMDCODE_SET(HFA384x_CMDCODE_DISABLE) |
	    HFA384x_CMD_MACPORT_SET(macport);
	cmd.parm0 = 0;
	cmd.parm1 = 0;
	cmd.parm2 = 0;

	वापस hfa384x_करोcmd(hw, &cmd);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_cmd_enable
 *
 * Issues the enable command to enable communications on one of
 * the MACs 'ports'.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	macport		MAC port number
 *
 * Returns:
 *	0		success
 *	>0		f/w reported failure - f/w status code
 *	<0		driver reported error (समयout|bad arg)
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_cmd_enable(काष्ठा hfa384x *hw, u16 macport)
अणु
	काष्ठा hfa384x_metacmd cmd;

	cmd.cmd = HFA384x_CMD_CMDCODE_SET(HFA384x_CMDCODE_ENABLE) |
	    HFA384x_CMD_MACPORT_SET(macport);
	cmd.parm0 = 0;
	cmd.parm1 = 0;
	cmd.parm2 = 0;

	वापस hfa384x_करोcmd(hw, &cmd);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_cmd_monitor
 *
 * Enables the 'monitor mode' of the MAC.  Here's the description of
 * monitor mode that I've received thus far:
 *
 *  "The "monitor mode" of operation is that the MAC passes all
 *  frames क्रम which the PLCP checks are correct. All received
 *  MPDUs are passed to the host with MAC Port = 7, with a
 *  receive status of good, FCS error, or undecryptable. Passing
 *  certain MPDUs is a violation of the 802.11 standard, but useful
 *  क्रम a debugging tool."  Normal communication is not possible
 *  जबतक monitor mode is enabled.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	enable		a code (0x0b|0x0f) that enables/disables
 *			monitor mode. (host order)
 *
 * Returns:
 *	0		success
 *	>0		f/w reported failure - f/w status code
 *	<0		driver reported error (समयout|bad arg)
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_cmd_monitor(काष्ठा hfa384x *hw, u16 enable)
अणु
	काष्ठा hfa384x_metacmd cmd;

	cmd.cmd = HFA384x_CMD_CMDCODE_SET(HFA384x_CMDCODE_MONITOR) |
	    HFA384x_CMD_AINFO_SET(enable);
	cmd.parm0 = 0;
	cmd.parm1 = 0;
	cmd.parm2 = 0;

	वापस hfa384x_करोcmd(hw, &cmd);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_cmd_करोwnload
 *
 * Sets the controls क्रम the MAC controller code/data करोwnload
 * process.  The arguments set the mode and address associated
 * with a करोwnload.  Note that the aux रेजिस्टरs should be enabled
 * prior to setting one of the करोwnload enable modes.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	mode		0 - Disable programming and begin code exec
 *			1 - Enable अस्थिर mem programming
 *			2 - Enable non-अस्थिर mem programming
 *			3 - Program non-अस्थिर section from NV करोwnload
 *			    buffer.
 *			(host order)
 *	lowaddr
 *	highaddr	For mode 1, sets the high & low order bits of
 *			the "destination address".  This address will be
 *			the execution start address when करोwnload is
 *			subsequently disabled.
 *			For mode 2, sets the high & low order bits of
 *			the destination in NV ram.
 *			For modes 0 & 3, should be zero. (host order)
 *			NOTE: these are CMD क्रमmat.
 *	codelen		Length of the data to ग_लिखो in mode 2,
 *			zero otherwise. (host order)
 *
 * Returns:
 *	0		success
 *	>0		f/w reported failure - f/w status code
 *	<0		driver reported error (समयout|bad arg)
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_cmd_करोwnload(काष्ठा hfa384x *hw, u16 mode, u16 lowaddr,
			 u16 highaddr, u16 codelen)
अणु
	काष्ठा hfa384x_metacmd cmd;

	pr_debug("mode=%d, lowaddr=0x%04x, highaddr=0x%04x, codelen=%d\n",
		 mode, lowaddr, highaddr, codelen);

	cmd.cmd = (HFA384x_CMD_CMDCODE_SET(HFA384x_CMDCODE_DOWNLD) |
		   HFA384x_CMD_PROGMODE_SET(mode));

	cmd.parm0 = lowaddr;
	cmd.parm1 = highaddr;
	cmd.parm2 = codelen;

	वापस hfa384x_करोcmd(hw, &cmd);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_corereset
 *
 * Perक्रमm a reset of the hfa38xx MAC core.  We assume that the hw
 * काष्ठाure is in its "created" state.  That is, it is initialized
 * with proper values.  Note that अगर a reset is करोne after the
 * device has been active क्रम aजबतक, the caller might have to clean
 * up some leftover cruft in the hw काष्ठाure.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	holdसमय	how दीर्घ (in ms) to hold the reset
 *	settleसमय	how दीर्घ (in ms) to रुको after releasing
 *			the reset
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_corereset(काष्ठा hfa384x *hw, पूर्णांक holdसमय,
		      पूर्णांक settleसमय, पूर्णांक genesis)
अणु
	पूर्णांक result;

	result = usb_reset_device(hw->usb);
	अगर (result < 0) अणु
		netdev_err(hw->wlandev->netdev, "usb_reset_device() failed, result=%d.\n",
			   result);
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbctlx_complete_sync
 *
 * Waits क्रम a synchronous CTLX object to complete,
 * and then handles the response.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	ctlx		CTLX ptr
 *	completor	functor object to decide what to
 *			करो with the CTLX's result.
 *
 * Returns:
 *	0		Success
 *	-ERESTARTSYS	Interrupted by a संकेत
 *	-EIO		CTLX failed
 *	-ENODEV		Adapter was unplugged
 *	???		Result from completor
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
अटल पूर्णांक hfa384x_usbctlx_complete_sync(काष्ठा hfa384x *hw,
					 काष्ठा hfa384x_usbctlx *ctlx,
					 काष्ठा usbctlx_completor *completor)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	result = रुको_क्रम_completion_पूर्णांकerruptible(&ctlx->करोne);

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/*
	 * We can only handle the CTLX अगर the USB disconnect
	 * function has not run yet ...
	 */
cleanup:
	अगर (hw->wlandev->hwहटाओd) अणु
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		result = -ENODEV;
	पूर्ण अन्यथा अगर (result != 0) अणु
		पूर्णांक runqueue = 0;

		/*
		 * We were probably पूर्णांकerrupted, so delete
		 * this CTLX asynchronously, समाप्त the समयrs
		 * and the URB, and then start the next
		 * pending CTLX.
		 *
		 * NOTE: We can only delete the समयrs and
		 *       the URB अगर this CTLX is active.
		 */
		अगर (ctlx == get_active_ctlx(hw)) अणु
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

			del_singleshot_समयr_sync(&hw->reqसमयr);
			del_singleshot_समयr_sync(&hw->respसमयr);
			hw->req_समयr_करोne = 1;
			hw->resp_समयr_करोne = 1;
			usb_समाप्त_urb(&hw->ctlx_urb);

			spin_lock_irqsave(&hw->ctlxq.lock, flags);

			runqueue = 1;

			/*
			 * This scenario is so unlikely that I'm
			 * happy with a grubby "goto" solution ...
			 */
			अगर (hw->wlandev->hwहटाओd)
				जाओ cleanup;
		पूर्ण

		/*
		 * The completion task will send this CTLX
		 * to the reaper the next समय it runs. We
		 * are no दीर्घer in a hurry.
		 */
		ctlx->reapable = 1;
		ctlx->state = CTLX_REQ_FAILED;
		list_move_tail(&ctlx->list, &hw->ctlxq.completing);

		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

		अगर (runqueue)
			hfa384x_usbctlxq_run(hw);
	पूर्ण अन्यथा अणु
		अगर (ctlx->state == CTLX_COMPLETE) अणु
			result = completor->complete(completor);
		पूर्ण अन्यथा अणु
			netdev_warn(hw->wlandev->netdev, "CTLX[%d] error: state(%s)\n",
				    le16_to_cpu(ctlx->outbuf.type),
				    ctlxstr(ctlx->state));
			result = -EIO;
		पूर्ण

		list_del(&ctlx->list);
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		kमुक्त(ctlx);
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_करोcmd
 *
 * Conकाष्ठाs a command CTLX and submits it.
 *
 * NOTE: Any changes to the 'post-submit' code in this function
 *       need to be carried over to hfa384x_cbcmd() since the handling
 *       is भवly identical.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *       cmd             cmd काष्ठाure.  Includes all arguments and result
 *                       data poपूर्णांकs.  All in host order. in host order
 *
 * Returns:
 *	0		success
 *	-EIO		CTLX failure
 *	-ERESTARTSYS	Awakened on संकेत
 *	>0		command indicated error, Status and Resp0-2 are
 *			in hw काष्ठाure.
 *
 * Side effects:
 *
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
अटल अंतरभूत पूर्णांक
hfa384x_करोcmd(काष्ठा hfa384x *hw,
	      काष्ठा hfa384x_metacmd *cmd)
अणु
	पूर्णांक result;
	काष्ठा hfa384x_usbctlx *ctlx;

	ctlx = usbctlx_alloc();
	अगर (!ctlx) अणु
		result = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Initialize the command */
	ctlx->outbuf.cmdreq.type = cpu_to_le16(HFA384x_USB_CMDREQ);
	ctlx->outbuf.cmdreq.cmd = cpu_to_le16(cmd->cmd);
	ctlx->outbuf.cmdreq.parm0 = cpu_to_le16(cmd->parm0);
	ctlx->outbuf.cmdreq.parm1 = cpu_to_le16(cmd->parm1);
	ctlx->outbuf.cmdreq.parm2 = cpu_to_le16(cmd->parm2);

	ctlx->outbufsize = माप(ctlx->outbuf.cmdreq);

	pr_debug("cmdreq: cmd=0x%04x parm0=0x%04x parm1=0x%04x parm2=0x%04x\n",
		 cmd->cmd, cmd->parm0, cmd->parm1, cmd->parm2);

	ctlx->reapable = DOWAIT;
	ctlx->cmdcb = शून्य;
	ctlx->usercb = शून्य;
	ctlx->usercb_data = शून्य;

	result = hfa384x_usbctlx_submit(hw, ctlx);
	अगर (result != 0) अणु
		kमुक्त(ctlx);
	पूर्ण अन्यथा अणु
		काष्ठा usbctlx_cmd_completor cmd_completor;
		काष्ठा usbctlx_completor *completor;

		completor = init_cmd_completor(&cmd_completor,
					       &ctlx->inbuf.cmdresp,
					       &cmd->result);

		result = hfa384x_usbctlx_complete_sync(hw, ctlx, completor);
	पूर्ण

करोne:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_करोrrid
 *
 * Conकाष्ठाs a पढ़ो rid CTLX and issues it.
 *
 * NOTE: Any changes to the 'post-submit' code in this function
 *       need to be carried over to hfa384x_cbrrid() since the handling
 *       is भवly identical.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	mode		DOWAIT or DOASYNC
 *	rid		Read RID number (host order)
 *	riddata		Caller supplied buffer that MAC क्रमmatted RID.data
 *			record will be written to क्रम DOWAIT calls. Should
 *			be शून्य क्रम DOASYNC calls.
 *	riddatalen	Buffer length क्रम DOWAIT calls. Zero क्रम DOASYNC calls.
 *	cmdcb		command callback क्रम async calls, शून्य क्रम DOWAIT calls
 *	usercb		user callback क्रम async calls, शून्य क्रम DOWAIT calls
 *	usercb_data	user supplied data poपूर्णांकer क्रम async calls, शून्य
 *			क्रम DOWAIT calls
 *
 * Returns:
 *	0		success
 *	-EIO		CTLX failure
 *	-ERESTARTSYS	Awakened on संकेत
 *	-ENODATA	riddatalen != macdatalen
 *	>0		command indicated error, Status and Resp0-2 are
 *			in hw काष्ठाure.
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt (DOASYNC)
 *	process (DOWAIT or DOASYNC)
 *----------------------------------------------------------------
 */
अटल पूर्णांक
hfa384x_करोrrid(काष्ठा hfa384x *hw,
	       क्रमागत cmd_mode mode,
	       u16 rid,
	       व्योम *riddata,
	       अचिन्हित पूर्णांक riddatalen,
	       ctlx_cmdcb_t cmdcb, ctlx_usercb_t usercb, व्योम *usercb_data)
अणु
	पूर्णांक result;
	काष्ठा hfa384x_usbctlx *ctlx;

	ctlx = usbctlx_alloc();
	अगर (!ctlx) अणु
		result = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Initialize the command */
	ctlx->outbuf.rridreq.type = cpu_to_le16(HFA384x_USB_RRIDREQ);
	ctlx->outbuf.rridreq.frmlen =
	    cpu_to_le16(माप(ctlx->outbuf.rridreq.rid));
	ctlx->outbuf.rridreq.rid = cpu_to_le16(rid);

	ctlx->outbufsize = माप(ctlx->outbuf.rridreq);

	ctlx->reapable = mode;
	ctlx->cmdcb = cmdcb;
	ctlx->usercb = usercb;
	ctlx->usercb_data = usercb_data;

	/* Submit the CTLX */
	result = hfa384x_usbctlx_submit(hw, ctlx);
	अगर (result != 0) अणु
		kमुक्त(ctlx);
	पूर्ण अन्यथा अगर (mode == DOWAIT) अणु
		काष्ठा usbctlx_rrid_completor completor;

		result =
		    hfa384x_usbctlx_complete_sync(hw, ctlx,
						  init_rrid_completor
						  (&completor,
						   &ctlx->inbuf.rridresp,
						   riddata, riddatalen));
	पूर्ण

करोne:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_करोwrid
 *
 * Conकाष्ठाs a ग_लिखो rid CTLX and issues it.
 *
 * NOTE: Any changes to the 'post-submit' code in this function
 *       need to be carried over to hfa384x_cbwrid() since the handling
 *       is भवly identical.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	क्रमागत cmd_mode	DOWAIT or DOASYNC
 *	rid		RID code
 *	riddata		Data portion of RID क्रमmatted क्रम MAC
 *	riddatalen	Length of the data portion in bytes
 *       cmdcb           command callback क्रम async calls, शून्य क्रम DOWAIT calls
 *	usercb		user callback क्रम async calls, शून्य क्रम DOWAIT calls
 *	usercb_data	user supplied data poपूर्णांकer क्रम async calls
 *
 * Returns:
 *	0		success
 *	-ETIMEDOUT	समयd out रुकोing क्रम रेजिस्टर पढ़ोy or
 *			command completion
 *	>0		command indicated error, Status and Resp0-2 are
 *			in hw काष्ठाure.
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt (DOASYNC)
 *	process (DOWAIT or DOASYNC)
 *----------------------------------------------------------------
 */
अटल पूर्णांक
hfa384x_करोwrid(काष्ठा hfa384x *hw,
	       क्रमागत cmd_mode mode,
	       u16 rid,
	       व्योम *riddata,
	       अचिन्हित पूर्णांक riddatalen,
	       ctlx_cmdcb_t cmdcb, ctlx_usercb_t usercb, व्योम *usercb_data)
अणु
	पूर्णांक result;
	काष्ठा hfa384x_usbctlx *ctlx;

	ctlx = usbctlx_alloc();
	अगर (!ctlx) अणु
		result = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Initialize the command */
	ctlx->outbuf.wridreq.type = cpu_to_le16(HFA384x_USB_WRIDREQ);
	ctlx->outbuf.wridreq.frmlen = cpu_to_le16((माप
						   (ctlx->outbuf.wridreq.rid) +
						   riddatalen + 1) / 2);
	ctlx->outbuf.wridreq.rid = cpu_to_le16(rid);
	स_नकल(ctlx->outbuf.wridreq.data, riddata, riddatalen);

	ctlx->outbufsize = माप(ctlx->outbuf.wridreq.type) +
	    माप(ctlx->outbuf.wridreq.frmlen) +
	    माप(ctlx->outbuf.wridreq.rid) + riddatalen;

	ctlx->reapable = mode;
	ctlx->cmdcb = cmdcb;
	ctlx->usercb = usercb;
	ctlx->usercb_data = usercb_data;

	/* Submit the CTLX */
	result = hfa384x_usbctlx_submit(hw, ctlx);
	अगर (result != 0) अणु
		kमुक्त(ctlx);
	पूर्ण अन्यथा अगर (mode == DOWAIT) अणु
		काष्ठा usbctlx_cmd_completor completor;
		काष्ठा hfa384x_cmdresult wridresult;

		result = hfa384x_usbctlx_complete_sync(hw,
						       ctlx,
						       init_wrid_completor
						       (&completor,
							&ctlx->inbuf.wridresp,
							&wridresult));
	पूर्ण

करोne:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_करोrmem
 *
 * Conकाष्ठाs a पढ़ोmem CTLX and issues it.
 *
 * NOTE: Any changes to the 'post-submit' code in this function
 *       need to be carried over to hfa384x_cbrmem() since the handling
 *       is भवly identical.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	page		MAC address space page (CMD क्रमmat)
 *	offset		MAC address space offset
 *	data		Ptr to data buffer to receive पढ़ो
 *	len		Length of the data to पढ़ो (max == 2048)
 *
 * Returns:
 *	0		success
 *	-ETIMEDOUT	समयd out रुकोing क्रम रेजिस्टर पढ़ोy or
 *			command completion
 *	>0		command indicated error, Status and Resp0-2 are
 *			in hw काष्ठाure.
 *
 * Side effects:
 *
 * Call context:
 *	process (DOWAIT)
 *----------------------------------------------------------------
 */
अटल पूर्णांक
hfa384x_करोrmem(काष्ठा hfa384x *hw,
	       u16 page,
	       u16 offset,
	       व्योम *data,
	       अचिन्हित पूर्णांक len)
अणु
	पूर्णांक result;
	काष्ठा hfa384x_usbctlx *ctlx;

	ctlx = usbctlx_alloc();
	अगर (!ctlx) अणु
		result = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Initialize the command */
	ctlx->outbuf.rmemreq.type = cpu_to_le16(HFA384x_USB_RMEMREQ);
	ctlx->outbuf.rmemreq.frmlen =
	    cpu_to_le16(माप(ctlx->outbuf.rmemreq.offset) +
			माप(ctlx->outbuf.rmemreq.page) + len);
	ctlx->outbuf.rmemreq.offset = cpu_to_le16(offset);
	ctlx->outbuf.rmemreq.page = cpu_to_le16(page);

	ctlx->outbufsize = माप(ctlx->outbuf.rmemreq);

	pr_debug("type=0x%04x frmlen=%d offset=0x%04x page=0x%04x\n",
		 ctlx->outbuf.rmemreq.type,
		 ctlx->outbuf.rmemreq.frmlen,
		 ctlx->outbuf.rmemreq.offset, ctlx->outbuf.rmemreq.page);

	pr_debug("pktsize=%zd\n", ROUNDUP64(माप(ctlx->outbuf.rmemreq)));

	ctlx->reapable = DOWAIT;
	ctlx->cmdcb = शून्य;
	ctlx->usercb = शून्य;
	ctlx->usercb_data = शून्य;

	result = hfa384x_usbctlx_submit(hw, ctlx);
	अगर (result != 0) अणु
		kमुक्त(ctlx);
	पूर्ण अन्यथा अणु
		काष्ठा usbctlx_rmem_completor completor;

		result =
		    hfa384x_usbctlx_complete_sync(hw, ctlx,
						  init_rmem_completor
						  (&completor,
						   &ctlx->inbuf.rmemresp, data,
						   len));
	पूर्ण

करोne:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_करोwmem
 *
 * Conकाष्ठाs a ग_लिखोmem CTLX and issues it.
 *
 * NOTE: Any changes to the 'post-submit' code in this function
 *       need to be carried over to hfa384x_cbwmem() since the handling
 *       is भवly identical.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	page		MAC address space page (CMD क्रमmat)
 *	offset		MAC address space offset
 *	data		Ptr to data buffer containing ग_लिखो data
 *	len		Length of the data to पढ़ो (max == 2048)
 *
 * Returns:
 *	0		success
 *	-ETIMEDOUT	समयd out रुकोing क्रम रेजिस्टर पढ़ोy or
 *			command completion
 *	>0		command indicated error, Status and Resp0-2 are
 *			in hw काष्ठाure.
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt (DOWAIT)
 *	process (DOWAIT)
 *----------------------------------------------------------------
 */
अटल पूर्णांक
hfa384x_करोwmem(काष्ठा hfa384x *hw,
	       u16 page,
	       u16 offset,
	       व्योम *data,
	       अचिन्हित पूर्णांक len)
अणु
	पूर्णांक result;
	काष्ठा hfa384x_usbctlx *ctlx;

	pr_debug("page=0x%04x offset=0x%04x len=%d\n", page, offset, len);

	ctlx = usbctlx_alloc();
	अगर (!ctlx) अणु
		result = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Initialize the command */
	ctlx->outbuf.wmemreq.type = cpu_to_le16(HFA384x_USB_WMEMREQ);
	ctlx->outbuf.wmemreq.frmlen =
	    cpu_to_le16(माप(ctlx->outbuf.wmemreq.offset) +
			माप(ctlx->outbuf.wmemreq.page) + len);
	ctlx->outbuf.wmemreq.offset = cpu_to_le16(offset);
	ctlx->outbuf.wmemreq.page = cpu_to_le16(page);
	स_नकल(ctlx->outbuf.wmemreq.data, data, len);

	ctlx->outbufsize = माप(ctlx->outbuf.wmemreq.type) +
	    माप(ctlx->outbuf.wmemreq.frmlen) +
	    माप(ctlx->outbuf.wmemreq.offset) +
	    माप(ctlx->outbuf.wmemreq.page) + len;

	ctlx->reapable = DOWAIT;
	ctlx->cmdcb = शून्य;
	ctlx->usercb = शून्य;
	ctlx->usercb_data = शून्य;

	result = hfa384x_usbctlx_submit(hw, ctlx);
	अगर (result != 0) अणु
		kमुक्त(ctlx);
	पूर्ण अन्यथा अणु
		काष्ठा usbctlx_cmd_completor completor;
		काष्ठा hfa384x_cmdresult wmemresult;

		result = hfa384x_usbctlx_complete_sync(hw,
						       ctlx,
						       init_wmem_completor
						       (&completor,
							&ctlx->inbuf.wmemresp,
							&wmemresult));
	पूर्ण

करोne:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_disable
 *
 * Issues the disable command to stop communications on one of
 * the MACs 'ports'.  Only macport 0 is valid  क्रम stations.
 * APs may also disable macports 1-6.  Only ports that have been
 * previously enabled may be disabled.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	macport		MAC port number (host order)
 *
 * Returns:
 *	0		success
 *	>0		f/w reported failure - f/w status code
 *	<0		driver reported error (समयout|bad arg)
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_disable(काष्ठा hfa384x *hw, u16 macport)
अणु
	पूर्णांक result = 0;

	अगर ((!hw->isap && macport != 0) ||
	    (hw->isap && !(macport <= HFA384x_PORTID_MAX)) ||
	    !(hw->port_enabled[macport])) अणु
		result = -EINVAL;
	पूर्ण अन्यथा अणु
		result = hfa384x_cmd_disable(hw, macport);
		अगर (result == 0)
			hw->port_enabled[macport] = 0;
	पूर्ण
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_enable
 *
 * Issues the enable command to enable communications on one of
 * the MACs 'ports'.  Only macport 0 is valid  क्रम stations.
 * APs may also enable macports 1-6.  Only ports that are currently
 * disabled may be enabled.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	macport		MAC port number
 *
 * Returns:
 *	0		success
 *	>0		f/w reported failure - f/w status code
 *	<0		driver reported error (समयout|bad arg)
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_enable(काष्ठा hfa384x *hw, u16 macport)
अणु
	पूर्णांक result = 0;

	अगर ((!hw->isap && macport != 0) ||
	    (hw->isap && !(macport <= HFA384x_PORTID_MAX)) ||
	    (hw->port_enabled[macport])) अणु
		result = -EINVAL;
	पूर्ण अन्यथा अणु
		result = hfa384x_cmd_enable(hw, macport);
		अगर (result == 0)
			hw->port_enabled[macport] = 1;
	पूर्ण
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_flashdl_enable
 *
 * Begins the flash करोwnload state.  Checks to see that we're not
 * alपढ़ोy in a करोwnload state and that a port isn't enabled.
 * Sets the करोwnload state and retrieves the flash करोwnload
 * buffer location, buffer size, and समयout length.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_flashdl_enable(काष्ठा hfa384x *hw)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;

	/* Check that a port isn't active */
	क्रम (i = 0; i < HFA384x_PORTID_MAX; i++) अणु
		अगर (hw->port_enabled[i]) अणु
			pr_debug("called when port enabled.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check that we're not alपढ़ोy in a करोwnload state */
	अगर (hw->dlstate != HFA384x_DLSTATE_DISABLED)
		वापस -EINVAL;

	/* Retrieve the buffer loc&size and समयout */
	result = hfa384x_drvr_अ_लोonfig(hw, HFA384x_RID_DOWNLOADBUFFER,
					&hw->bufinfo, माप(hw->bufinfo));
	अगर (result)
		वापस result;

	le16_to_cpus(&hw->bufinfo.page);
	le16_to_cpus(&hw->bufinfo.offset);
	le16_to_cpus(&hw->bufinfo.len);
	result = hfa384x_drvr_अ_लोonfig16(hw, HFA384x_RID_MAXLOADTIME,
					  &hw->dlसमयout);
	अगर (result)
		वापस result;

	le16_to_cpus(&hw->dlसमयout);

	pr_debug("flashdl_enable\n");

	hw->dlstate = HFA384x_DLSTATE_FLASHENABLED;

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_flashdl_disable
 *
 * Ends the flash करोwnload state.  Note that this will cause the MAC
 * firmware to restart.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_flashdl_disable(काष्ठा hfa384x *hw)
अणु
	/* Check that we're alपढ़ोy in the करोwnload state */
	अगर (hw->dlstate != HFA384x_DLSTATE_FLASHENABLED)
		वापस -EINVAL;

	pr_debug("flashdl_enable\n");

	/* There isn't much we can do at this point, so I don't */
	/*  bother  w/ the वापस value */
	hfa384x_cmd_करोwnload(hw, HFA384x_PROGMODE_DISABLE, 0, 0, 0);
	hw->dlstate = HFA384x_DLSTATE_DISABLED;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_flashdl_ग_लिखो
 *
 * Perक्रमms a FLASH करोwnload of a chunk of data. First checks to see
 * that we're in the FLASH करोwnload state, then sets the करोwnload
 * mode, uses the aux functions to 1) copy the data to the flash
 * buffer, 2) sets the करोwnload 'write flash' mode, 3) पढ़ोback and
 * compare.  Lather rinse, repeat as many बार an necessary to get
 * all the given data पूर्णांकo flash.
 * When all data has been written using this function (possibly
 * repeatedly), call drvr_flashdl_disable() to end the करोwnload state
 * and restart the MAC.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	daddr		Card address to ग_लिखो to. (host order)
 *	buf		Ptr to data to ग_लिखो.
 *	len		Length of data (host order).
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_flashdl_ग_लिखो(काष्ठा hfa384x *hw, u32 daddr,
			       व्योम *buf, u32 len)
अणु
	पूर्णांक result = 0;
	u32 dlbufaddr;
	पूर्णांक nburns;
	u32 burnlen;
	u32 burndaddr;
	u16 burnlo;
	u16 burnhi;
	पूर्णांक nग_लिखोs;
	u8 *ग_लिखोbuf;
	u16 ग_लिखोpage;
	u16 ग_लिखोoffset;
	u32 ग_लिखोlen;
	पूर्णांक i;
	पूर्णांक j;

	pr_debug("daddr=0x%08x len=%d\n", daddr, len);

	/* Check that we're in the flash करोwnload state */
	अगर (hw->dlstate != HFA384x_DLSTATE_FLASHENABLED)
		वापस -EINVAL;

	netdev_info(hw->wlandev->netdev,
		    "Download %d bytes to flash @0x%06x\n", len, daddr);

	/* Convert to flat address क्रम arithmetic */
	/* NOTE: dlbuffer RID stores the address in AUX क्रमmat */
	dlbufaddr =
	    HFA384x_ADDR_AUX_MKFLAT(hw->bufinfo.page, hw->bufinfo.offset);
	pr_debug("dlbuf.page=0x%04x dlbuf.offset=0x%04x dlbufaddr=0x%08x\n",
		 hw->bufinfo.page, hw->bufinfo.offset, dlbufaddr);
	/* Calculations to determine how many fills of the dlbuffer to करो
	 * and how many USB wmemreq's to करो क्रम each fill.  At this poपूर्णांक
	 * in समय, the dlbuffer size and the wmemreq size are the same.
	 * Thereक्रमe, nग_लिखोs should always be 1.  The extra complनिकासy
	 * here is a hedge against future changes.
	 */

	/* Figure out how many बार to करो the flash programming */
	nburns = len / hw->bufinfo.len;
	nburns += (len % hw->bufinfo.len) ? 1 : 0;

	/* For each flash program cycle, how many USB wmemreq's are needed? */
	nग_लिखोs = hw->bufinfo.len / HFA384x_USB_RWMEM_MAXLEN;
	nग_लिखोs += (hw->bufinfo.len % HFA384x_USB_RWMEM_MAXLEN) ? 1 : 0;

	/* For each burn */
	क्रम (i = 0; i < nburns; i++) अणु
		/* Get the dest address and len */
		burnlen = (len - (hw->bufinfo.len * i)) > hw->bufinfo.len ?
		    hw->bufinfo.len : (len - (hw->bufinfo.len * i));
		burndaddr = daddr + (hw->bufinfo.len * i);
		burnlo = HFA384x_ADDR_CMD_MKOFF(burndaddr);
		burnhi = HFA384x_ADDR_CMD_MKPAGE(burndaddr);

		netdev_info(hw->wlandev->netdev, "Writing %d bytes to flash @0x%06x\n",
			    burnlen, burndaddr);

		/* Set the करोwnload mode */
		result = hfa384x_cmd_करोwnload(hw, HFA384x_PROGMODE_NV,
					      burnlo, burnhi, burnlen);
		अगर (result) अणु
			netdev_err(hw->wlandev->netdev,
				   "download(NV,lo=%x,hi=%x,len=%x) cmd failed, result=%d. Aborting d/l\n",
				   burnlo, burnhi, burnlen, result);
			जाओ निकास_proc;
		पूर्ण

		/* copy the data to the flash करोwnload buffer */
		क्रम (j = 0; j < nग_लिखोs; j++) अणु
			ग_लिखोbuf = buf +
			    (i * hw->bufinfo.len) +
			    (j * HFA384x_USB_RWMEM_MAXLEN);

			ग_लिखोpage = HFA384x_ADDR_CMD_MKPAGE(dlbufaddr +
						(j * HFA384x_USB_RWMEM_MAXLEN));
			ग_लिखोoffset = HFA384x_ADDR_CMD_MKOFF(dlbufaddr +
						(j * HFA384x_USB_RWMEM_MAXLEN));

			ग_लिखोlen = burnlen - (j * HFA384x_USB_RWMEM_MAXLEN);
			ग_लिखोlen = ग_लिखोlen > HFA384x_USB_RWMEM_MAXLEN ?
			    HFA384x_USB_RWMEM_MAXLEN : ग_लिखोlen;

			result = hfa384x_करोwmem(hw,
						ग_लिखोpage,
						ग_लिखोoffset,
						ग_लिखोbuf, ग_लिखोlen);
		पूर्ण

		/* set the करोwnload 'write flash' mode */
		result = hfa384x_cmd_करोwnload(hw,
					      HFA384x_PROGMODE_NVWRITE,
					      0, 0, 0);
		अगर (result) अणु
			netdev_err(hw->wlandev->netdev,
				   "download(NVWRITE,lo=%x,hi=%x,len=%x) cmd failed, result=%d. Aborting d/l\n",
				   burnlo, burnhi, burnlen, result);
			जाओ निकास_proc;
		पूर्ण

		/* TODO: We really should करो a पढ़ोback and compare. */
	पूर्ण

निकास_proc:

	/* Leave the firmware in the 'post-prog' mode.  flashdl_disable will */
	/*  actually disable programming mode.  Remember, that will cause the */
	/*  the firmware to effectively reset itself. */

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_अ_लोonfig
 *
 * Perक्रमms the sequence necessary to पढ़ो a config/info item.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	rid		config/info record id (host order)
 *	buf		host side record buffer.  Upon वापस it will
 *			contain the body portion of the record (minus the
 *			RID and len).
 *	len		buffer length (in bytes, should match record length)
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *	-ENODATA	length mismatch between argument and retrieved
 *			record.
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_अ_लोonfig(काष्ठा hfa384x *hw, u16 rid, व्योम *buf, u16 len)
अणु
	वापस hfa384x_करोrrid(hw, DOWAIT, rid, buf, len, शून्य, शून्य, शून्य);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_setconfig_async
 *
 * Perक्रमms the sequence necessary to ग_लिखो a config/info item.
 *
 * Arguments:
 *       hw              device काष्ठाure
 *       rid             config/info record id (in host order)
 *       buf             host side record buffer
 *       len             buffer length (in bytes)
 *       usercb          completion callback
 *       usercb_data     completion callback argument
 *
 * Returns:
 *       0               success
 *       >0              f/w reported error - f/w status code
 *       <0              driver reported error
 *
 * Side effects:
 *
 * Call context:
 *       process
 *----------------------------------------------------------------
 */
पूर्णांक
hfa384x_drvr_setconfig_async(काष्ठा hfa384x *hw,
			     u16 rid,
			     व्योम *buf,
			     u16 len, ctlx_usercb_t usercb, व्योम *usercb_data)
अणु
	वापस hfa384x_करोwrid(hw, DOASYNC, rid, buf, len, hfa384x_cb_status,
			      usercb, usercb_data);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_ramdl_disable
 *
 * Ends the ram करोwnload state.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_ramdl_disable(काष्ठा hfa384x *hw)
अणु
	/* Check that we're alपढ़ोy in the करोwnload state */
	अगर (hw->dlstate != HFA384x_DLSTATE_RAMENABLED)
		वापस -EINVAL;

	pr_debug("ramdl_disable()\n");

	/* There isn't much we can do at this point, so I don't */
	/*  bother  w/ the वापस value */
	hfa384x_cmd_करोwnload(hw, HFA384x_PROGMODE_DISABLE, 0, 0, 0);
	hw->dlstate = HFA384x_DLSTATE_DISABLED;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_ramdl_enable
 *
 * Begins the ram करोwnload state.  Checks to see that we're not
 * alपढ़ोy in a करोwnload state and that a port isn't enabled.
 * Sets the करोwnload state and calls cmd_करोwnload with the
 * ENABLE_VOLATILE subcommand and the exeaddr argument.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	exeaddr		the card execution address that will be
 *                       jumped to when ramdl_disable() is called
 *			(host order).
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_ramdl_enable(काष्ठा hfa384x *hw, u32 exeaddr)
अणु
	पूर्णांक result = 0;
	u16 lowaddr;
	u16 hiaddr;
	पूर्णांक i;

	/* Check that a port isn't active */
	क्रम (i = 0; i < HFA384x_PORTID_MAX; i++) अणु
		अगर (hw->port_enabled[i]) अणु
			netdev_err(hw->wlandev->netdev,
				   "Can't download with a macport enabled.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check that we're not alपढ़ोy in a करोwnload state */
	अगर (hw->dlstate != HFA384x_DLSTATE_DISABLED) अणु
		netdev_err(hw->wlandev->netdev,
			   "Download state not disabled.\n");
		वापस -EINVAL;
	पूर्ण

	pr_debug("ramdl_enable, exeaddr=0x%08x\n", exeaddr);

	/* Call the करोwnload(1,addr) function */
	lowaddr = HFA384x_ADDR_CMD_MKOFF(exeaddr);
	hiaddr = HFA384x_ADDR_CMD_MKPAGE(exeaddr);

	result = hfa384x_cmd_करोwnload(hw, HFA384x_PROGMODE_RAM,
				      lowaddr, hiaddr, 0);

	अगर (result == 0) अणु
		/* Set the करोwnload state */
		hw->dlstate = HFA384x_DLSTATE_RAMENABLED;
	पूर्ण अन्यथा अणु
		pr_debug("cmd_download(0x%04x, 0x%04x) failed, result=%d.\n",
			 lowaddr, hiaddr, result);
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_ramdl_ग_लिखो
 *
 * Perक्रमms a RAM करोwnload of a chunk of data. First checks to see
 * that we're in the RAM करोwnload state, then uses the [पढ़ो|ग_लिखो]mem USB
 * commands to 1) copy the data, 2) पढ़ोback and compare.  The करोwnload
 * state is unaffected.  When all data has been written using
 * this function, call drvr_ramdl_disable() to end the करोwnload state
 * and restart the MAC.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	daddr		Card address to ग_लिखो to. (host order)
 *	buf		Ptr to data to ग_लिखो.
 *	len		Length of data (host order).
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_ramdl_ग_लिखो(काष्ठा hfa384x *hw, u32 daddr, व्योम *buf, u32 len)
अणु
	पूर्णांक result = 0;
	पूर्णांक nग_लिखोs;
	u8 *data = buf;
	पूर्णांक i;
	u32 curraddr;
	u16 currpage;
	u16 curroffset;
	u16 currlen;

	/* Check that we're in the ram करोwnload state */
	अगर (hw->dlstate != HFA384x_DLSTATE_RAMENABLED)
		वापस -EINVAL;

	netdev_info(hw->wlandev->netdev, "Writing %d bytes to ram @0x%06x\n",
		    len, daddr);

	/* How many करोwmem calls?  */
	nग_लिखोs = len / HFA384x_USB_RWMEM_MAXLEN;
	nग_लिखोs += len % HFA384x_USB_RWMEM_MAXLEN ? 1 : 0;

	/* Do blocking wmem's */
	क्रम (i = 0; i < nग_लिखोs; i++) अणु
		/* make address args */
		curraddr = daddr + (i * HFA384x_USB_RWMEM_MAXLEN);
		currpage = HFA384x_ADDR_CMD_MKPAGE(curraddr);
		curroffset = HFA384x_ADDR_CMD_MKOFF(curraddr);
		currlen = len - (i * HFA384x_USB_RWMEM_MAXLEN);
		अगर (currlen > HFA384x_USB_RWMEM_MAXLEN)
			currlen = HFA384x_USB_RWMEM_MAXLEN;

		/* Do blocking ctlx */
		result = hfa384x_करोwmem(hw,
					currpage,
					curroffset,
					data + (i * HFA384x_USB_RWMEM_MAXLEN),
					currlen);

		अगर (result)
			अवरोध;

		/* TODO: We really should have a पढ़ोback. */
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_पढ़ोpda
 *
 * Perक्रमms the sequence to पढ़ो the PDA space.  Note there is no
 * drvr_ग_लिखोpda() function.  Writing a PDA is
 * generally implemented by a calling component via calls to
 * cmd_करोwnload and writing to the flash करोwnload buffer via the
 * aux regs.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	buf		buffer to store PDA in
 *	len		buffer length
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *	-ETIMEDOUT	समयout रुकोing क्रम the cmd regs to become
 *			available, or रुकोing क्रम the control reg
 *			to indicate the Aux port is enabled.
 *	-ENODATA	the buffer करोes NOT contain a valid PDA.
 *			Either the card PDA is bad, or the auxdata
 *			पढ़ोs are giving us garbage.
 *
 *
 * Side effects:
 *
 * Call context:
 *	process or non-card पूर्णांकerrupt.
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_पढ़ोpda(काष्ठा hfa384x *hw, व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक result = 0;
	__le16 *pda = buf;
	पूर्णांक pdaok = 0;
	पूर्णांक morepdrs = 1;
	पूर्णांक currpdr = 0;	/* word offset of the current pdr */
	माप_प्रकार i;
	u16 pdrlen;		/* pdr length in bytes, host order */
	u16 pdrcode;		/* pdr code, host order */
	u16 currpage;
	u16 curroffset;
	काष्ठा pdaloc अणु
		u32 cardaddr;
		u16 auxctl;
	पूर्ण pdaloc[] = अणु
		अणु
		HFA3842_PDA_BASE, 0पूर्ण, अणु
		HFA3841_PDA_BASE, 0पूर्ण, अणु
		HFA3841_PDA_BOGUS_BASE, 0पूर्ण
	पूर्ण;

	/* Read the pda from each known address.  */
	क्रम (i = 0; i < ARRAY_SIZE(pdaloc); i++) अणु
		/* Make address */
		currpage = HFA384x_ADDR_CMD_MKPAGE(pdaloc[i].cardaddr);
		curroffset = HFA384x_ADDR_CMD_MKOFF(pdaloc[i].cardaddr);

		/* units of bytes */
		result = hfa384x_करोrmem(hw, currpage, curroffset, buf,
					len);

		अगर (result) अणु
			netdev_warn(hw->wlandev->netdev,
				    "Read from index %zd failed, continuing\n",
				    i);
			जारी;
		पूर्ण

		/* Test क्रम garbage */
		pdaok = 1;	/* initially assume good */
		morepdrs = 1;
		जबतक (pdaok && morepdrs) अणु
			pdrlen = le16_to_cpu(pda[currpdr]) * 2;
			pdrcode = le16_to_cpu(pda[currpdr + 1]);
			/* Test the record length */
			अगर (pdrlen > HFA384x_PDR_LEN_MAX || pdrlen == 0) अणु
				netdev_err(hw->wlandev->netdev,
					   "pdrlen invalid=%d\n", pdrlen);
				pdaok = 0;
				अवरोध;
			पूर्ण
			/* Test the code */
			अगर (!hfa384x_isgood_pdrcode(pdrcode)) अणु
				netdev_err(hw->wlandev->netdev, "pdrcode invalid=%d\n",
					   pdrcode);
				pdaok = 0;
				अवरोध;
			पूर्ण
			/* Test क्रम completion */
			अगर (pdrcode == HFA384x_PDR_END_OF_PDA)
				morepdrs = 0;

			/* Move to the next pdr (अगर necessary) */
			अगर (morepdrs) अणु
				/* note the access to pda[], need words here */
				currpdr += le16_to_cpu(pda[currpdr]) + 1;
			पूर्ण
		पूर्ण
		अगर (pdaok) अणु
			netdev_info(hw->wlandev->netdev,
				    "PDA Read from 0x%08x in %s space.\n",
				    pdaloc[i].cardaddr,
				    pdaloc[i].auxctl == 0 ? "EXTDS" :
				    pdaloc[i].auxctl == 1 ? "NV" :
				    pdaloc[i].auxctl == 2 ? "PHY" :
				    pdaloc[i].auxctl == 3 ? "ICSRAM" :
				    "<bogus auxctl>");
			अवरोध;
		पूर्ण
	पूर्ण
	result = pdaok ? 0 : -ENODATA;

	अगर (result)
		pr_debug("Failure: pda is not okay\n");

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_setconfig
 *
 * Perक्रमms the sequence necessary to ग_लिखो a config/info item.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	rid		config/info record id (in host order)
 *	buf		host side record buffer
 *	len		buffer length (in bytes)
 *
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_setconfig(काष्ठा hfa384x *hw, u16 rid, व्योम *buf, u16 len)
अणु
	वापस hfa384x_करोwrid(hw, DOWAIT, rid, buf, len, शून्य, शून्य, शून्य);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_start
 *
 * Issues the MAC initialize command, sets up some data काष्ठाures,
 * and enables the पूर्णांकerrupts.  After this function completes, the
 * low-level stuff should be पढ़ोy क्रम any/all commands.
 *
 * Arguments:
 *	hw		device काष्ठाure
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_start(काष्ठा hfa384x *hw)
अणु
	पूर्णांक result, result1, result2;
	u16 status;

	might_sleep();

	/* Clear endpoपूर्णांक stalls - but only करो this अगर the endpoपूर्णांक
	 * is showing a stall status. Some prism2 cards seem to behave
	 * badly अगर a clear_halt is called when the endpoपूर्णांक is alपढ़ोy
	 * ok
	 */
	result =
	    usb_get_std_status(hw->usb, USB_RECIP_ENDPOINT, hw->endp_in,
			       &status);
	अगर (result < 0) अणु
		netdev_err(hw->wlandev->netdev, "Cannot get bulk in endpoint status.\n");
		जाओ करोne;
	पूर्ण
	अगर ((status == 1) && usb_clear_halt(hw->usb, hw->endp_in))
		netdev_err(hw->wlandev->netdev, "Failed to reset bulk in endpoint.\n");

	result =
	    usb_get_std_status(hw->usb, USB_RECIP_ENDPOINT, hw->endp_out,
			       &status);
	अगर (result < 0) अणु
		netdev_err(hw->wlandev->netdev, "Cannot get bulk out endpoint status.\n");
		जाओ करोne;
	पूर्ण
	अगर ((status == 1) && usb_clear_halt(hw->usb, hw->endp_out))
		netdev_err(hw->wlandev->netdev, "Failed to reset bulk out endpoint.\n");

	/* Synchronous unlink, in हाल we're trying to restart the driver */
	usb_समाप्त_urb(&hw->rx_urb);

	/* Post the IN urb */
	result = submit_rx_urb(hw, GFP_KERNEL);
	अगर (result != 0) अणु
		netdev_err(hw->wlandev->netdev,
			   "Fatal, failed to submit RX URB, result=%d\n",
			   result);
		जाओ करोne;
	पूर्ण

	/* Call initialize twice, with a 1 second sleep in between.
	 * This is a nasty work-around since many prism2 cards seem to
	 * need समय to settle after an init from cold. The second
	 * call to initialize in theory is not necessary - but we call
	 * it anyway as a द्विगुन insurance policy:
	 * 1) If the first init should fail, the second may well succeed
	 *    and the card can still be used
	 * 2) It helps ensures all is well with the card after the first
	 *    init and settle समय.
	 */
	result1 = hfa384x_cmd_initialize(hw);
	msleep(1000);
	result = hfa384x_cmd_initialize(hw);
	result2 = result;
	अगर (result1 != 0) अणु
		अगर (result2 != 0) अणु
			netdev_err(hw->wlandev->netdev,
				   "cmd_initialize() failed on two attempts, results %d and %d\n",
				   result1, result2);
			usb_समाप्त_urb(&hw->rx_urb);
			जाओ करोne;
		पूर्ण अन्यथा अणु
			pr_debug("First cmd_initialize() failed (result %d),\n",
				 result1);
			pr_debug("but second attempt succeeded. All should be ok\n");
		पूर्ण
	पूर्ण अन्यथा अगर (result2 != 0) अणु
		netdev_warn(hw->wlandev->netdev, "First cmd_initialize() succeeded, but second attempt failed (result=%d)\n",
			    result2);
		netdev_warn(hw->wlandev->netdev,
			    "Most likely the card will be functional\n");
		जाओ करोne;
	पूर्ण

	hw->state = HFA384x_STATE_RUNNING;

करोne:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_stop
 *
 * Shuts करोwn the MAC to the poपूर्णांक where it is safe to unload the
 * driver.  Any subप्रणाली that may be holding a data or function
 * ptr पूर्णांकo the driver must be cleared/deinitialized.
 *
 * Arguments:
 *	hw		device काष्ठाure
 * Returns:
 *	0		success
 *	>0		f/w reported error - f/w status code
 *	<0		driver reported error
 *
 * Side effects:
 *
 * Call context:
 *	process
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_stop(काष्ठा hfa384x *hw)
अणु
	पूर्णांक i;

	might_sleep();

	/* There's no need क्रम spinlocks here. The USB "disconnect"
	 * function sets this "removed" flag and then calls us.
	 */
	अगर (!hw->wlandev->hwहटाओd) अणु
		/* Call initialize to leave the MAC in its 'reset' state */
		hfa384x_cmd_initialize(hw);

		/* Cancel the rxurb */
		usb_समाप्त_urb(&hw->rx_urb);
	पूर्ण

	hw->link_status = HFA384x_LINK_NOTCONNECTED;
	hw->state = HFA384x_STATE_INIT;

	del_समयr_sync(&hw->commsqual_समयr);

	/* Clear all the port status */
	क्रम (i = 0; i < HFA384x_NUMPORTS_MAX; i++)
		hw->port_enabled[i] = 0;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_drvr_txframe
 *
 * Takes a frame from prism2sta and queues it क्रम transmission.
 *
 * Arguments:
 *	hw		device काष्ठाure
 *	skb		packet buffer काष्ठा.  Contains an 802.11
 *			data frame.
 *       p80211_hdr      poपूर्णांकs to the 802.11 header क्रम the packet.
 * Returns:
 *	0		Success and more buffs available
 *	1		Success but no more buffs
 *	2		Allocation failure
 *	4		Buffer full or queue busy
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
पूर्णांक hfa384x_drvr_txframe(काष्ठा hfa384x *hw, काष्ठा sk_buff *skb,
			 जोड़ p80211_hdr *p80211_hdr,
			 काष्ठा p80211_metawep *p80211_wep)
अणु
	पूर्णांक usbpktlen = माप(काष्ठा hfa384x_tx_frame);
	पूर्णांक result;
	पूर्णांक ret;
	अक्षर *ptr;

	अगर (hw->tx_urb.status == -EINPROGRESS) अणु
		netdev_warn(hw->wlandev->netdev, "TX URB already in use\n");
		result = 3;
		जाओ निकास;
	पूर्ण

	/* Build Tx frame काष्ठाure */
	/* Set up the control field */
	स_रखो(&hw->txbuff.txfrm.desc, 0, माप(hw->txbuff.txfrm.desc));

	/* Setup the usb type field */
	hw->txbuff.type = cpu_to_le16(HFA384x_USB_TXFRM);

	/* Set up the sw_support field to identअगरy this frame */
	hw->txbuff.txfrm.desc.sw_support = 0x0123;

/* Tx complete and Tx exception disable per dleach.  Might be causing
 * buf depletion
 */
/* #घोषणा DOEXC  SLP -- करोboth अवरोधs horribly under load, करोexc less so. */
#अगर defined(DOBOTH)
	hw->txbuff.txfrm.desc.tx_control =
	    HFA384x_TX_MACPORT_SET(0) | HFA384x_TX_STRUCTYPE_SET(1) |
	    HFA384x_TX_TXEX_SET(1) | HFA384x_TX_TXOK_SET(1);
#या_अगर defined(DOEXC)
	hw->txbuff.txfrm.desc.tx_control =
	    HFA384x_TX_MACPORT_SET(0) | HFA384x_TX_STRUCTYPE_SET(1) |
	    HFA384x_TX_TXEX_SET(1) | HFA384x_TX_TXOK_SET(0);
#अन्यथा
	hw->txbuff.txfrm.desc.tx_control =
	    HFA384x_TX_MACPORT_SET(0) | HFA384x_TX_STRUCTYPE_SET(1) |
	    HFA384x_TX_TXEX_SET(0) | HFA384x_TX_TXOK_SET(0);
#पूर्ण_अगर
	cpu_to_le16s(&hw->txbuff.txfrm.desc.tx_control);

	/* copy the header over to the txdesc */
	स_नकल(&hw->txbuff.txfrm.desc.frame_control, p80211_hdr,
	       माप(जोड़ p80211_hdr));

	/* अगर we're using host WEP, increase size by IV+ICV */
	अगर (p80211_wep->data) अणु
		hw->txbuff.txfrm.desc.data_len = cpu_to_le16(skb->len + 8);
		usbpktlen += 8;
	पूर्ण अन्यथा अणु
		hw->txbuff.txfrm.desc.data_len = cpu_to_le16(skb->len);
	पूर्ण

	usbpktlen += skb->len;

	/* copy over the WEP IV अगर we are using host WEP */
	ptr = hw->txbuff.txfrm.data;
	अगर (p80211_wep->data) अणु
		स_नकल(ptr, p80211_wep->iv, माप(p80211_wep->iv));
		ptr += माप(p80211_wep->iv);
		स_नकल(ptr, p80211_wep->data, skb->len);
	पूर्ण अन्यथा अणु
		स_नकल(ptr, skb->data, skb->len);
	पूर्ण
	/* copy over the packet data */
	ptr += skb->len;

	/* copy over the WEP ICV अगर we are using host WEP */
	अगर (p80211_wep->data)
		स_नकल(ptr, p80211_wep->icv, माप(p80211_wep->icv));

	/* Send the USB packet */
	usb_fill_bulk_urb(&hw->tx_urb, hw->usb,
			  hw->endp_out,
			  &hw->txbuff, ROUNDUP64(usbpktlen),
			  hfa384x_usbout_callback, hw->wlandev);
	hw->tx_urb.transfer_flags |= USB_QUEUE_BULK;

	result = 1;
	ret = submit_tx_urb(hw, &hw->tx_urb, GFP_ATOMIC);
	अगर (ret != 0) अणु
		netdev_err(hw->wlandev->netdev,
			   "submit_tx_urb() failed, error=%d\n", ret);
		result = 3;
	पूर्ण

निकास:
	वापस result;
पूर्ण

व्योम hfa384x_tx_समयout(काष्ठा wlandevice *wlandev)
अणु
	काष्ठा hfa384x *hw = wlandev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	अगर (!hw->wlandev->hwहटाओd) अणु
		पूर्णांक sched;

		sched = !test_and_set_bit(WORK_TX_HALT, &hw->usb_flags);
		sched |= !test_and_set_bit(WORK_RX_HALT, &hw->usb_flags);
		अगर (sched)
			schedule_work(&hw->usb_work);
	पूर्ण

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbctlx_reaper_task
 *
 * Tasklet to delete dead CTLX objects
 *
 * Arguments:
 *	data	ptr to a काष्ठा hfa384x
 *
 * Returns:
 *
 * Call context:
 *	Interrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbctlx_reaper_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा hfa384x *hw = from_tasklet(hw, t, reaper_bh);
	काष्ठा hfa384x_usbctlx *ctlx, *temp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/* This list is guaranteed to be empty अगर someone
	 * has unplugged the adapter.
	 */
	list_क्रम_each_entry_safe(ctlx, temp, &hw->ctlxq.reapable, list) अणु
		list_del(&ctlx->list);
		kमुक्त(ctlx);
	पूर्ण

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbctlx_completion_task
 *
 * Tasklet to call completion handlers क्रम वापसed CTLXs
 *
 * Arguments:
 *	data	ptr to काष्ठा hfa384x
 *
 * Returns:
 *	Nothing
 *
 * Call context:
 *	Interrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbctlx_completion_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा hfa384x *hw = from_tasklet(hw, t, completion_bh);
	काष्ठा hfa384x_usbctlx *ctlx, *temp;
	अचिन्हित दीर्घ flags;

	पूर्णांक reap = 0;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/* This list is guaranteed to be empty अगर someone
	 * has unplugged the adapter ...
	 */
	list_क्रम_each_entry_safe(ctlx, temp, &hw->ctlxq.completing, list) अणु
		/* Call the completion function that this
		 * command was asचिन्हित, assuming it has one.
		 */
		अगर (ctlx->cmdcb) अणु
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
			ctlx->cmdcb(hw, ctlx);
			spin_lock_irqsave(&hw->ctlxq.lock, flags);

			/* Make sure we करोn't try and complete
			 * this CTLX more than once!
			 */
			ctlx->cmdcb = शून्य;

			/* Did someone yank the adapter out
			 * जबतक our list was (briefly) unlocked?
			 */
			अगर (hw->wlandev->hwहटाओd) अणु
				reap = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * "Reapable" CTLXs are ones which करोn't have any
		 * thपढ़ोs रुकोing क्रम them to die. Hence they must
		 * be delivered to The Reaper!
		 */
		अगर (ctlx->reapable) अणु
			/* Move the CTLX off the "completing" list (hopefully)
			 * on to the "reapable" list where the reaper task
			 * can find it. And "reapable" means that this CTLX
			 * isn't sitting on a रुको-queue somewhere.
			 */
			list_move_tail(&ctlx->list, &hw->ctlxq.reapable);
			reap = 1;
		पूर्ण

		complete(&ctlx->करोne);
	पूर्ण
	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

	अगर (reap)
		tasklet_schedule(&hw->reaper_bh);
पूर्ण

/*----------------------------------------------------------------
 * unlocked_usbctlx_cancel_async
 *
 * Mark the CTLX dead asynchronously, and ensure that the
 * next command on the queue is run afterwards.
 *
 * Arguments:
 *	hw	ptr to the काष्ठा hfa384x काष्ठाure
 *	ctlx	ptr to a CTLX काष्ठाure
 *
 * Returns:
 *	0	the CTLX's URB is inactive
 * -EINPROGRESS	the URB is currently being unlinked
 *
 * Call context:
 *	Either process or पूर्णांकerrupt, but presumably पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल पूर्णांक unlocked_usbctlx_cancel_async(काष्ठा hfa384x *hw,
					 काष्ठा hfa384x_usbctlx *ctlx)
अणु
	पूर्णांक ret;

	/*
	 * Try to delete the URB containing our request packet.
	 * If we succeed, then its completion handler will be
	 * called with a status of -ECONNRESET.
	 */
	hw->ctlx_urb.transfer_flags |= URB_ASYNC_UNLINK;
	ret = usb_unlink_urb(&hw->ctlx_urb);

	अगर (ret != -EINPROGRESS) अणु
		/*
		 * The OUT URB had either alपढ़ोy completed
		 * or was still in the pending queue, so the
		 * URB's completion function will not be called.
		 * We will have to complete the CTLX ourselves.
		 */
		ctlx->state = CTLX_REQ_FAILED;
		unlocked_usbctlx_complete(hw, ctlx);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*----------------------------------------------------------------
 * unlocked_usbctlx_complete
 *
 * A CTLX has completed.  It may have been successful, it may not
 * have been. At this poपूर्णांक, the CTLX should be quiescent.  The URBs
 * aren't active and the समयrs should have been stopped.
 *
 * The CTLX is migrated to the "completing" queue, and the completing
 * tasklet is scheduled.
 *
 * Arguments:
 *	hw		ptr to a काष्ठा hfa384x काष्ठाure
 *	ctlx		ptr to a ctlx काष्ठाure
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	Either, assume पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम unlocked_usbctlx_complete(काष्ठा hfa384x *hw,
				      काष्ठा hfa384x_usbctlx *ctlx)
अणु
	/* Timers have been stopped, and ctlx should be in
	 * a terminal state. Retire it from the "active"
	 * queue.
	 */
	list_move_tail(&ctlx->list, &hw->ctlxq.completing);
	tasklet_schedule(&hw->completion_bh);

	चयन (ctlx->state) अणु
	हाल CTLX_COMPLETE:
	हाल CTLX_REQ_FAILED:
		/* This are the correct terminating states. */
		अवरोध;

	शेष:
		netdev_err(hw->wlandev->netdev, "CTLX[%d] not in a terminating state(%s)\n",
			   le16_to_cpu(ctlx->outbuf.type),
			   ctlxstr(ctlx->state));
		अवरोध;
	पूर्ण			/* चयन */
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbctlxq_run
 *
 * Checks to see अगर the head item is running.  If not, starts it.
 *
 * Arguments:
 *	hw	ptr to काष्ठा hfa384x
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	any
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbctlxq_run(काष्ठा hfa384x *hw)
अणु
	अचिन्हित दीर्घ flags;

	/* acquire lock */
	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/* Only one active CTLX at any one समय, because there's no
	 * other (reliable) way to match the response URB to the
	 * correct CTLX.
	 *
	 * Don't touch any of these CTLXs अगर the hardware
	 * has been हटाओd or the USB subप्रणाली is stalled.
	 */
	अगर (!list_empty(&hw->ctlxq.active) ||
	    test_bit(WORK_TX_HALT, &hw->usb_flags) || hw->wlandev->hwहटाओd)
		जाओ unlock;

	जबतक (!list_empty(&hw->ctlxq.pending)) अणु
		काष्ठा hfa384x_usbctlx *head;
		पूर्णांक result;

		/* This is the first pending command */
		head = list_entry(hw->ctlxq.pending.next,
				  काष्ठा hfa384x_usbctlx, list);

		/* We need to split this off to aव्योम a race condition */
		list_move_tail(&head->list, &hw->ctlxq.active);

		/* Fill the out packet */
		usb_fill_bulk_urb(&hw->ctlx_urb, hw->usb,
				  hw->endp_out,
				  &head->outbuf, ROUNDUP64(head->outbufsize),
				  hfa384x_ctlxout_callback, hw);
		hw->ctlx_urb.transfer_flags |= USB_QUEUE_BULK;

		/* Now submit the URB and update the CTLX's state */
		result = usb_submit_urb(&hw->ctlx_urb, GFP_ATOMIC);
		अगर (result == 0) अणु
			/* This CTLX is now running on the active queue */
			head->state = CTLX_REQ_SUBMITTED;

			/* Start the OUT रुको समयr */
			hw->req_समयr_करोne = 0;
			hw->reqसमयr.expires = jअगरfies + HZ;
			add_समयr(&hw->reqसमयr);

			/* Start the IN रुको समयr */
			hw->resp_समयr_करोne = 0;
			hw->respसमयr.expires = jअगरfies + 2 * HZ;
			add_समयr(&hw->respसमयr);

			अवरोध;
		पूर्ण

		अगर (result == -EPIPE) अणु
			/* The OUT pipe needs resetting, so put
			 * this CTLX back in the "pending" queue
			 * and schedule a reset ...
			 */
			netdev_warn(hw->wlandev->netdev,
				    "%s tx pipe stalled: requesting reset\n",
				    hw->wlandev->netdev->name);
			list_move(&head->list, &hw->ctlxq.pending);
			set_bit(WORK_TX_HALT, &hw->usb_flags);
			schedule_work(&hw->usb_work);
			अवरोध;
		पूर्ण

		अगर (result == -ESHUTDOWN) अणु
			netdev_warn(hw->wlandev->netdev, "%s urb shutdown!\n",
				    hw->wlandev->netdev->name);
			अवरोध;
		पूर्ण

		netdev_err(hw->wlandev->netdev, "Failed to submit CTLX[%d]: error=%d\n",
			   le16_to_cpu(head->outbuf.type), result);
		unlocked_usbctlx_complete(hw, head);
	पूर्ण			/* जबतक */

unlock:
	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbin_callback
 *
 * Callback क्रम URBs on the BULKIN endpoपूर्णांक.
 *
 * Arguments:
 *	urb		ptr to the completed urb
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbin_callback(काष्ठा urb *urb)
अणु
	काष्ठा wlandevice *wlandev = urb->context;
	काष्ठा hfa384x *hw;
	जोड़ hfa384x_usbin *usbin;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक result;
	पूर्णांक urb_status;
	u16 type;

	क्रमागत USBIN_ACTION अणु
		HANDLE,
		RESUBMIT,
		ABORT
	पूर्ण action;

	अगर (!wlandev || !wlandev->netdev || wlandev->hwहटाओd)
		जाओ निकास;

	hw = wlandev->priv;
	अगर (!hw)
		जाओ निकास;

	skb = hw->rx_urb_skb;
	अगर (!skb || (skb->data != urb->transfer_buffer)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	hw->rx_urb_skb = शून्य;

	/* Check क्रम error conditions within the URB */
	चयन (urb->status) अणु
	हाल 0:
		action = HANDLE;

		/* Check क्रम लघु packet */
		अगर (urb->actual_length == 0) अणु
			wlandev->netdev->stats.rx_errors++;
			wlandev->netdev->stats.rx_length_errors++;
			action = RESUBMIT;
		पूर्ण
		अवरोध;

	हाल -EPIPE:
		netdev_warn(hw->wlandev->netdev, "%s rx pipe stalled: requesting reset\n",
			    wlandev->netdev->name);
		अगर (!test_and_set_bit(WORK_RX_HALT, &hw->usb_flags))
			schedule_work(&hw->usb_work);
		wlandev->netdev->stats.rx_errors++;
		action = ABORT;
		अवरोध;

	हाल -EILSEQ:
	हाल -ETIMEDOUT:
	हाल -EPROTO:
		अगर (!test_and_set_bit(THROTTLE_RX, &hw->usb_flags) &&
		    !समयr_pending(&hw->throttle)) अणु
			mod_समयr(&hw->throttle, jअगरfies + THROTTLE_JIFFIES);
		पूर्ण
		wlandev->netdev->stats.rx_errors++;
		action = ABORT;
		अवरोध;

	हाल -EOVERFLOW:
		wlandev->netdev->stats.rx_over_errors++;
		action = RESUBMIT;
		अवरोध;

	हाल -ENODEV:
	हाल -ESHUTDOWN:
		pr_debug("status=%d, device removed.\n", urb->status);
		action = ABORT;
		अवरोध;

	हाल -ENOENT:
	हाल -ECONNRESET:
		pr_debug("status=%d, urb explicitly unlinked.\n", urb->status);
		action = ABORT;
		अवरोध;

	शेष:
		pr_debug("urb status=%d, transfer flags=0x%x\n",
			 urb->status, urb->transfer_flags);
		wlandev->netdev->stats.rx_errors++;
		action = RESUBMIT;
		अवरोध;
	पूर्ण

	/* Save values from the RX URB beक्रमe reposting overग_लिखोs it. */
	urb_status = urb->status;
	usbin = (जोड़ hfa384x_usbin *)urb->transfer_buffer;

	अगर (action != ABORT) अणु
		/* Repost the RX URB */
		result = submit_rx_urb(hw, GFP_ATOMIC);

		अगर (result != 0) अणु
			netdev_err(hw->wlandev->netdev,
				   "Fatal, failed to resubmit rx_urb. error=%d\n",
				   result);
		पूर्ण
	पूर्ण

	/* Handle any USB-IN packet */
	/* Note: the check of the sw_support field, the type field करोesn't
	 *       have bit 12 set like the करोcs suggest.
	 */
	type = le16_to_cpu(usbin->type);
	अगर (HFA384x_USB_ISRXFRM(type)) अणु
		अगर (action == HANDLE) अणु
			अगर (usbin->txfrm.desc.sw_support == 0x0123) अणु
				hfa384x_usbin_txcompl(wlandev, usbin);
			पूर्ण अन्यथा अणु
				skb_put(skb, माप(*usbin));
				hfa384x_usbin_rx(wlandev, skb);
				skb = शून्य;
			पूर्ण
		पूर्ण
		जाओ निकास;
	पूर्ण
	अगर (HFA384x_USB_ISTXFRM(type)) अणु
		अगर (action == HANDLE)
			hfa384x_usbin_txcompl(wlandev, usbin);
		जाओ निकास;
	पूर्ण
	चयन (type) अणु
	हाल HFA384x_USB_INFOFRM:
		अगर (action == ABORT)
			जाओ निकास;
		अगर (action == HANDLE)
			hfa384x_usbin_info(wlandev, usbin);
		अवरोध;

	हाल HFA384x_USB_CMDRESP:
	हाल HFA384x_USB_WRIDRESP:
	हाल HFA384x_USB_RRIDRESP:
	हाल HFA384x_USB_WMEMRESP:
	हाल HFA384x_USB_RMEMRESP:
		/* ALWAYS, ALWAYS, ALWAYS handle this CTLX!!!! */
		hfa384x_usbin_ctlx(hw, usbin, urb_status);
		अवरोध;

	हाल HFA384x_USB_BUFAVAIL:
		pr_debug("Received BUFAVAIL packet, frmlen=%d\n",
			 usbin->bufavail.frmlen);
		अवरोध;

	हाल HFA384x_USB_ERROR:
		pr_debug("Received USB_ERROR packet, errortype=%d\n",
			 usbin->usberror.errortype);
		अवरोध;

	शेष:
		pr_debug("Unrecognized USBIN packet, type=%x, status=%d\n",
			 usbin->type, urb_status);
		अवरोध;
	पूर्ण			/* चयन */

निकास:

	अगर (skb)
		dev_kमुक्त_skb(skb);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbin_ctlx
 *
 * We've received a URB containing a Prism2 "response" message.
 * This message needs to be matched up with a CTLX on the active
 * queue and our state updated accordingly.
 *
 * Arguments:
 *	hw		ptr to काष्ठा hfa384x
 *	usbin		ptr to USB IN packet
 *	urb_status	status of this Bulk-In URB
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbin_ctlx(काष्ठा hfa384x *hw, जोड़ hfa384x_usbin *usbin,
			       पूर्णांक urb_status)
अणु
	काष्ठा hfa384x_usbctlx *ctlx;
	पूर्णांक run_queue = 0;
	अचिन्हित दीर्घ flags;

retry:
	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/* There can be only one CTLX on the active queue
	 * at any one समय, and this is the CTLX that the
	 * समयrs are रुकोing क्रम.
	 */
	अगर (list_empty(&hw->ctlxq.active))
		जाओ unlock;

	/* Remove the "response timeout". It's possible that
	 * we are alपढ़ोy too late, and that the समयout is
	 * alपढ़ोy running. And that's just too bad क्रम us,
	 * because we could lose our CTLX from the active
	 * queue here ...
	 */
	अगर (del_समयr(&hw->respसमयr) == 0) अणु
		अगर (hw->resp_समयr_करोne == 0) अणु
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अणु
		hw->resp_समयr_करोne = 1;
	पूर्ण

	ctlx = get_active_ctlx(hw);

	अगर (urb_status != 0) अणु
		/*
		 * Bad CTLX, so get rid of it. But we only
		 * हटाओ it from the active queue अगर we're no
		 * दीर्घer expecting the OUT URB to complete.
		 */
		अगर (unlocked_usbctlx_cancel_async(hw, ctlx) == 0)
			run_queue = 1;
	पूर्ण अन्यथा अणु
		स्थिर __le16 पूर्णांकype = (usbin->type & ~cpu_to_le16(0x8000));

		/*
		 * Check that our message is what we're expecting ...
		 */
		अगर (ctlx->outbuf.type != पूर्णांकype) अणु
			netdev_warn(hw->wlandev->netdev,
				    "Expected IN[%d], received IN[%d] - ignored.\n",
				    le16_to_cpu(ctlx->outbuf.type),
				    le16_to_cpu(पूर्णांकype));
			जाओ unlock;
		पूर्ण

		/* This URB has succeeded, so grab the data ... */
		स_नकल(&ctlx->inbuf, usbin, माप(ctlx->inbuf));

		चयन (ctlx->state) अणु
		हाल CTLX_REQ_SUBMITTED:
			/*
			 * We have received our response URB beक्रमe
			 * our request has been acknowledged. Odd,
			 * but our OUT URB is still alive...
			 */
			pr_debug("Causality violation: please reboot Universe\n");
			ctlx->state = CTLX_RESP_COMPLETE;
			अवरोध;

		हाल CTLX_REQ_COMPLETE:
			/*
			 * This is the usual path: our request
			 * has alपढ़ोy been acknowledged, and
			 * now we have received the reply too.
			 */
			ctlx->state = CTLX_COMPLETE;
			unlocked_usbctlx_complete(hw, ctlx);
			run_queue = 1;
			अवरोध;

		शेष:
			/*
			 * Throw this CTLX away ...
			 */
			netdev_err(hw->wlandev->netdev,
				   "Matched IN URB, CTLX[%d] in invalid state(%s). Discarded.\n",
				   le16_to_cpu(ctlx->outbuf.type),
				   ctlxstr(ctlx->state));
			अगर (unlocked_usbctlx_cancel_async(hw, ctlx) == 0)
				run_queue = 1;
			अवरोध;
		पूर्ण		/* चयन */
	पूर्ण

unlock:
	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

	अगर (run_queue)
		hfa384x_usbctlxq_run(hw);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbin_txcompl
 *
 * At this poपूर्णांक we have the results of a previous transmit.
 *
 * Arguments:
 *	wlandev		wlan device
 *	usbin		ptr to the usb transfer buffer
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbin_txcompl(काष्ठा wlandevice *wlandev,
				  जोड़ hfa384x_usbin *usbin)
अणु
	u16 status;

	status = le16_to_cpu(usbin->type); /* yeah I know it says type... */

	/* Was there an error? */
	अगर (HFA384x_TXSTATUS_ISERROR(status))
		prism2sta_ev_txexc(wlandev, status);
	अन्यथा
		prism2sta_ev_tx(wlandev, status);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbin_rx
 *
 * At this poपूर्णांक we have a successful received a rx frame packet.
 *
 * Arguments:
 *	wlandev		wlan device
 *	usbin		ptr to the usb transfer buffer
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbin_rx(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb)
अणु
	जोड़ hfa384x_usbin *usbin = (जोड़ hfa384x_usbin *)skb->data;
	काष्ठा hfa384x *hw = wlandev->priv;
	पूर्णांक hdrlen;
	काष्ठा p80211_rxmeta *rxmeta;
	u16 data_len;
	u16 fc;
	u16 status;

	/* Byte order convert once up front. */
	le16_to_cpus(&usbin->rxfrm.desc.status);
	le32_to_cpus(&usbin->rxfrm.desc.समय);

	/* Now handle frame based on port# */
	status = HFA384x_RXSTATUS_MACPORT_GET(usbin->rxfrm.desc.status);

	चयन (status) अणु
	हाल 0:
		fc = le16_to_cpu(usbin->rxfrm.desc.frame_control);

		/* If exclude and we receive an unencrypted, drop it */
		अगर ((wlandev->hostwep & HOSTWEP_EXCLUDEUNENCRYPTED) &&
		    !WLAN_GET_FC_ISWEP(fc)) अणु
			अवरोध;
		पूर्ण

		data_len = le16_to_cpu(usbin->rxfrm.desc.data_len);

		/* How much header data करो we have? */
		hdrlen = p80211_headerlen(fc);

		/* Pull off the descriptor */
		skb_pull(skb, माप(काष्ठा hfa384x_rx_frame));

		/* Now shunt the header block up against the data block
		 * with an "overlapping" copy
		 */
		स_हटाओ(skb_push(skb, hdrlen),
			&usbin->rxfrm.desc.frame_control, hdrlen);

		skb->dev = wlandev->netdev;

		/* And set the frame length properly */
		skb_trim(skb, data_len + hdrlen);

		/* The prism2 series करोes not वापस the CRC */
		स_रखो(skb_put(skb, WLAN_CRC_LEN), 0xff, WLAN_CRC_LEN);

		skb_reset_mac_header(skb);

		/* Attach the rxmeta, set some stuff */
		p80211skb_rxmeta_attach(wlandev, skb);
		rxmeta = p80211skb_rxmeta(skb);
		rxmeta->maस_समय = usbin->rxfrm.desc.समय;
		rxmeta->rxrate = usbin->rxfrm.desc.rate;
		rxmeta->संकेत = usbin->rxfrm.desc.संकेत - hw->dbmadjust;
		rxmeta->noise = usbin->rxfrm.desc.silence - hw->dbmadjust;

		p80211netdev_rx(wlandev, skb);

		अवरोध;

	हाल 7:
		अगर (!HFA384x_RXSTATUS_ISFCSERR(usbin->rxfrm.desc.status)) अणु
			/* Copy to wlansnअगर skb */
			hfa384x_पूर्णांक_rxmonitor(wlandev, &usbin->rxfrm);
			dev_kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			pr_debug("Received monitor frame: FCSerr set\n");
		पूर्ण
		अवरोध;

	शेष:
		netdev_warn(hw->wlandev->netdev,
			    "Received frame on unsupported port=%d\n",
			    status);
		अवरोध;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_पूर्णांक_rxmonitor
 *
 * Helper function क्रम पूर्णांक_rx.  Handles monitor frames.
 * Note that this function allocates space क्रम the FCS and sets it
 * to 0xffffffff.  The hfa384x करोesn't give us the FCS value but the
 * higher layers expect it.  0xffffffff is used as a flag to indicate
 * the FCS is bogus.
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	rxfrm		rx descriptor पढ़ो from card in पूर्णांक_rx
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *	Allocates an skb and passes it up via the PF_PACKET पूर्णांकerface.
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_पूर्णांक_rxmonitor(काष्ठा wlandevice *wlandev,
				  काष्ठा hfa384x_usb_rxfrm *rxfrm)
अणु
	काष्ठा hfa384x_rx_frame *rxdesc = &rxfrm->desc;
	अचिन्हित पूर्णांक hdrlen = 0;
	अचिन्हित पूर्णांक datalen = 0;
	अचिन्हित पूर्णांक skblen = 0;
	u8 *datap;
	u16 fc;
	काष्ठा sk_buff *skb;
	काष्ठा hfa384x *hw = wlandev->priv;

	/* Remember the status, समय, and data_len fields are in host order */
	/* Figure out how big the frame is */
	fc = le16_to_cpu(rxdesc->frame_control);
	hdrlen = p80211_headerlen(fc);
	datalen = le16_to_cpu(rxdesc->data_len);

	/* Allocate an ind message+framesize skb */
	skblen = माप(काष्ठा p80211_caphdr) + hdrlen + datalen + WLAN_CRC_LEN;

	/* sanity check the length */
	अगर (skblen >
	    (माप(काष्ठा p80211_caphdr) +
	     WLAN_HDR_A4_LEN + WLAN_DATA_MAXLEN + WLAN_CRC_LEN)) अणु
		pr_debug("overlen frm: len=%zd\n",
			 skblen - माप(काष्ठा p80211_caphdr));

		वापस;
	पूर्ण

	skb = dev_alloc_skb(skblen);
	अगर (!skb)
		वापस;

	/* only prepend the prism header अगर in the right mode */
	अगर ((wlandev->netdev->type == ARPHRD_IEEE80211_PRISM) &&
	    (hw->snअगरfhdr != 0)) अणु
		काष्ठा p80211_caphdr *caphdr;
		/* The NEW header क्रमmat! */
		datap = skb_put(skb, माप(काष्ठा p80211_caphdr));
		caphdr = (काष्ठा p80211_caphdr *)datap;

		caphdr->version = htonl(P80211CAPTURE_VERSION);
		caphdr->length = htonl(माप(काष्ठा p80211_caphdr));
		caphdr->maस_समय = __cpu_to_be64(rxdesc->समय * 1000);
		caphdr->hostसमय = __cpu_to_be64(jअगरfies);
		caphdr->phytype = htonl(4);	/* dss_करोt11_b */
		caphdr->channel = htonl(hw->snअगरf_channel);
		caphdr->datarate = htonl(rxdesc->rate);
		caphdr->antenna = htonl(0);	/* unknown */
		caphdr->priority = htonl(0);	/* unknown */
		caphdr->ssi_type = htonl(3);	/* rssi_raw */
		caphdr->ssi_संकेत = htonl(rxdesc->संकेत);
		caphdr->ssi_noise = htonl(rxdesc->silence);
		caphdr->preamble = htonl(0);	/* unknown */
		caphdr->encoding = htonl(1);	/* cck */
	पूर्ण

	/* Copy the 802.11 header to the skb
	 * (ctl frames may be less than a full header)
	 */
	skb_put_data(skb, &rxdesc->frame_control, hdrlen);

	/* If any, copy the data from the card to the skb */
	अगर (datalen > 0) अणु
		datap = skb_put_data(skb, rxfrm->data, datalen);

		/* check क्रम unencrypted stuff अगर WEP bit set. */
		अगर (*(datap - hdrlen + 1) & 0x40)	/* wep set */
			अगर ((*(datap) == 0xaa) && (*(datap + 1) == 0xaa))
				/* clear wep; it's the 802.2 header! */
				*(datap - hdrlen + 1) &= 0xbf;
	पूर्ण

	अगर (hw->snअगरf_fcs) अणु
		/* Set the FCS */
		datap = skb_put(skb, WLAN_CRC_LEN);
		स_रखो(datap, 0xff, WLAN_CRC_LEN);
	पूर्ण

	/* pass it back up */
	p80211netdev_rx(wlandev, skb);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbin_info
 *
 * At this poपूर्णांक we have a successful received a Prism2 info frame.
 *
 * Arguments:
 *	wlandev		wlan device
 *	usbin		ptr to the usb transfer buffer
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbin_info(काष्ठा wlandevice *wlandev,
			       जोड़ hfa384x_usbin *usbin)
अणु
	le16_to_cpus(&usbin->infofrm.info.framelen);
	prism2sta_ev_info(wlandev, &usbin->infofrm.info);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbout_callback
 *
 * Callback क्रम URBs on the BULKOUT endpoपूर्णांक.
 *
 * Arguments:
 *	urb		ptr to the completed urb
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbout_callback(काष्ठा urb *urb)
अणु
	काष्ठा wlandevice *wlandev = urb->context;

#अगर_घोषित DEBUG_USB
	dbprपूर्णांक_urb(urb);
#पूर्ण_अगर

	अगर (wlandev && wlandev->netdev) अणु
		चयन (urb->status) अणु
		हाल 0:
			prism2sta_ev_alloc(wlandev);
			अवरोध;

		हाल -EPIPE: अणु
			काष्ठा hfa384x *hw = wlandev->priv;

			netdev_warn(hw->wlandev->netdev,
				    "%s tx pipe stalled: requesting reset\n",
				    wlandev->netdev->name);
			अगर (!test_and_set_bit(WORK_TX_HALT, &hw->usb_flags))
				schedule_work(&hw->usb_work);
			wlandev->netdev->stats.tx_errors++;
			अवरोध;
		पूर्ण

		हाल -EPROTO:
		हाल -ETIMEDOUT:
		हाल -EILSEQ: अणु
			काष्ठा hfa384x *hw = wlandev->priv;

			अगर (!test_and_set_bit(THROTTLE_TX, &hw->usb_flags) &&
			    !समयr_pending(&hw->throttle)) अणु
				mod_समयr(&hw->throttle,
					  jअगरfies + THROTTLE_JIFFIES);
			पूर्ण
			wlandev->netdev->stats.tx_errors++;
			netअगर_stop_queue(wlandev->netdev);
			अवरोध;
		पूर्ण

		हाल -ENOENT:
		हाल -ESHUTDOWN:
			/* Ignorable errors */
			अवरोध;

		शेष:
			netdev_info(wlandev->netdev, "unknown urb->status=%d\n",
				    urb->status);
			wlandev->netdev->stats.tx_errors++;
			अवरोध;
		पूर्ण		/* चयन */
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_ctlxout_callback
 *
 * Callback क्रम control data on the BULKOUT endpoपूर्णांक.
 *
 * Arguments:
 *	urb		ptr to the completed urb
 *
 * Returns:
 * nothing
 *
 * Side effects:
 *
 * Call context:
 * पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_ctlxout_callback(काष्ठा urb *urb)
अणु
	काष्ठा hfa384x *hw = urb->context;
	पूर्णांक delete_respसमयr = 0;
	पूर्णांक समयr_ok = 1;
	पूर्णांक run_queue = 0;
	काष्ठा hfa384x_usbctlx *ctlx;
	अचिन्हित दीर्घ flags;

	pr_debug("urb->status=%d\n", urb->status);
#अगर_घोषित DEBUG_USB
	dbprपूर्णांक_urb(urb);
#पूर्ण_अगर
	अगर ((urb->status == -ESHUTDOWN) ||
	    (urb->status == -ENODEV) || !hw)
		वापस;

retry:
	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/*
	 * Only one CTLX at a समय on the "active" list, and
	 * none at all अगर we are unplugged. However, we can
	 * rely on the disconnect function to clean everything
	 * up अगर someone unplugged the adapter.
	 */
	अगर (list_empty(&hw->ctlxq.active)) अणु
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		वापस;
	पूर्ण

	/*
	 * Having something on the "active" queue means
	 * that we have समयrs to worry about ...
	 */
	अगर (del_समयr(&hw->reqसमयr) == 0) अणु
		अगर (hw->req_समयr_करोne == 0) अणु
			/*
			 * This समयr was actually running जबतक we
			 * were trying to delete it. Let it terminate
			 * gracefully instead.
			 */
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अणु
		hw->req_समयr_करोne = 1;
	पूर्ण

	ctlx = get_active_ctlx(hw);

	अगर (urb->status == 0) अणु
		/* Request portion of a CTLX is successful */
		चयन (ctlx->state) अणु
		हाल CTLX_REQ_SUBMITTED:
			/* This OUT-ACK received beक्रमe IN */
			ctlx->state = CTLX_REQ_COMPLETE;
			अवरोध;

		हाल CTLX_RESP_COMPLETE:
			/* IN alपढ़ोy received beक्रमe this OUT-ACK,
			 * so this command must now be complete.
			 */
			ctlx->state = CTLX_COMPLETE;
			unlocked_usbctlx_complete(hw, ctlx);
			run_queue = 1;
			अवरोध;

		शेष:
			/* This is NOT a valid CTLX "success" state! */
			netdev_err(hw->wlandev->netdev,
				   "Illegal CTLX[%d] success state(%s, %d) in OUT URB\n",
				   le16_to_cpu(ctlx->outbuf.type),
				   ctlxstr(ctlx->state), urb->status);
			अवरोध;
		पूर्ण		/* चयन */
	पूर्ण अन्यथा अणु
		/* If the pipe has stalled then we need to reset it */
		अगर ((urb->status == -EPIPE) &&
		    !test_and_set_bit(WORK_TX_HALT, &hw->usb_flags)) अणु
			netdev_warn(hw->wlandev->netdev,
				    "%s tx pipe stalled: requesting reset\n",
				    hw->wlandev->netdev->name);
			schedule_work(&hw->usb_work);
		पूर्ण

		/* If someone cancels the OUT URB then its status
		 * should be either -ECONNRESET or -ENOENT.
		 */
		ctlx->state = CTLX_REQ_FAILED;
		unlocked_usbctlx_complete(hw, ctlx);
		delete_respसमयr = 1;
		run_queue = 1;
	पूर्ण

delresp:
	अगर (delete_respसमयr) अणु
		समयr_ok = del_समयr(&hw->respसमयr);
		अगर (समयr_ok != 0)
			hw->resp_समयr_करोne = 1;
	पूर्ण

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

	अगर (!समयr_ok && (hw->resp_समयr_करोne == 0)) अणु
		spin_lock_irqsave(&hw->ctlxq.lock, flags);
		जाओ delresp;
	पूर्ण

	अगर (run_queue)
		hfa384x_usbctlxq_run(hw);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbctlx_reqसमयrfn
 *
 * Timer response function क्रम CTLX request समयouts.  If this
 * function is called, it means that the callback क्रम the OUT
 * URB containing a Prism2.x XXX_Request was never called.
 *
 * Arguments:
 *	data		a ptr to the काष्ठा hfa384x
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbctlx_reqसमयrfn(काष्ठा समयr_list *t)
अणु
	काष्ठा hfa384x *hw = from_समयr(hw, t, reqसमयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	hw->req_समयr_करोne = 1;

	/* Removing the hardware स्वतःmatically empties
	 * the active list ...
	 */
	अगर (!list_empty(&hw->ctlxq.active)) अणु
		/*
		 * We must ensure that our URB is हटाओd from
		 * the प्रणाली, अगर it hasn't alपढ़ोy expired.
		 */
		hw->ctlx_urb.transfer_flags |= URB_ASYNC_UNLINK;
		अगर (usb_unlink_urb(&hw->ctlx_urb) == -EINPROGRESS) अणु
			काष्ठा hfa384x_usbctlx *ctlx = get_active_ctlx(hw);

			ctlx->state = CTLX_REQ_FAILED;

			/* This URB was active, but has now been
			 * cancelled. It will now have a status of
			 * -ECONNRESET in the callback function.
			 *
			 * We are cancelling this CTLX, so we're
			 * not going to need to रुको क्रम a response.
			 * The URB's callback function will check
			 * that this समयr is truly dead.
			 */
			अगर (del_समयr(&hw->respसमयr) != 0)
				hw->resp_समयr_करोne = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbctlx_respसमयrfn
 *
 * Timer response function क्रम CTLX response समयouts.  If this
 * function is called, it means that the callback क्रम the IN
 * URB containing a Prism2.x XXX_Response was never called.
 *
 * Arguments:
 *	data		a ptr to the काष्ठा hfa384x
 *
 * Returns:
 *	nothing
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usbctlx_respसमयrfn(काष्ठा समयr_list *t)
अणु
	काष्ठा hfa384x *hw = from_समयr(hw, t, respसमयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	hw->resp_समयr_करोne = 1;

	/* The active list will be empty अगर the
	 * adapter has been unplugged ...
	 */
	अगर (!list_empty(&hw->ctlxq.active)) अणु
		काष्ठा hfa384x_usbctlx *ctlx = get_active_ctlx(hw);

		अगर (unlocked_usbctlx_cancel_async(hw, ctlx) == 0) अणु
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
			hfa384x_usbctlxq_run(hw);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usb_throttlefn
 *
 *
 * Arguments:
 *	data	ptr to hw
 *
 * Returns:
 *	Nothing
 *
 * Side effects:
 *
 * Call context:
 *	Interrupt
 *----------------------------------------------------------------
 */
अटल व्योम hfa384x_usb_throttlefn(काष्ठा समयr_list *t)
अणु
	काष्ठा hfa384x *hw = from_समयr(hw, t, throttle);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/*
	 * We need to check BOTH the RX and the TX throttle controls,
	 * so we use the bitwise OR instead of the logical OR.
	 */
	pr_debug("flags=0x%lx\n", hw->usb_flags);
	अगर (!hw->wlandev->hwहटाओd &&
	    ((test_and_clear_bit(THROTTLE_RX, &hw->usb_flags) &&
	      !test_and_set_bit(WORK_RX_RESUME, &hw->usb_flags)) |
	     (test_and_clear_bit(THROTTLE_TX, &hw->usb_flags) &&
	      !test_and_set_bit(WORK_TX_RESUME, &hw->usb_flags))
	    )) अणु
		schedule_work(&hw->usb_work);
	पूर्ण

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_usbctlx_submit
 *
 * Called from the करोxxx functions to submit a CTLX to the queue
 *
 * Arguments:
 *	hw		ptr to the hw काष्ठा
 *	ctlx		ctlx काष्ठाure to enqueue
 *
 * Returns:
 *	-ENODEV अगर the adapter is unplugged
 *	0
 *
 * Side effects:
 *
 * Call context:
 *	process or पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल पूर्णांक hfa384x_usbctlx_submit(काष्ठा hfa384x *hw,
				  काष्ठा hfa384x_usbctlx *ctlx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	अगर (hw->wlandev->hwहटाओd) अणु
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		वापस -ENODEV;
	पूर्ण

	ctlx->state = CTLX_PENDING;
	list_add_tail(&ctlx->list, &hw->ctlxq.pending);
	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
	hfa384x_usbctlxq_run(hw);

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * hfa384x_isgood_pdrcore
 *
 * Quick check of PDR codes.
 *
 * Arguments:
 *	pdrcode		PDR code number (host order)
 *
 * Returns:
 *	zero		not good.
 *	one		is good.
 *
 * Side effects:
 *
 * Call context:
 *----------------------------------------------------------------
 */
अटल पूर्णांक hfa384x_isgood_pdrcode(u16 pdrcode)
अणु
	चयन (pdrcode) अणु
	हाल HFA384x_PDR_END_OF_PDA:
	हाल HFA384x_PDR_PCB_PARTNUM:
	हाल HFA384x_PDR_PDAVER:
	हाल HFA384x_PDR_NIC_SERIAL:
	हाल HFA384x_PDR_MKK_MEASUREMENTS:
	हाल HFA384x_PDR_NIC_RAMSIZE:
	हाल HFA384x_PDR_MFISUPRANGE:
	हाल HFA384x_PDR_CFISUPRANGE:
	हाल HFA384x_PDR_NICID:
	हाल HFA384x_PDR_MAC_ADDRESS:
	हाल HFA384x_PDR_REGDOMAIN:
	हाल HFA384x_PDR_ALLOWED_CHANNEL:
	हाल HFA384x_PDR_DEFAULT_CHANNEL:
	हाल HFA384x_PDR_TEMPTYPE:
	हाल HFA384x_PDR_IFR_SETTING:
	हाल HFA384x_PDR_RFR_SETTING:
	हाल HFA384x_PDR_HFA3861_BASELINE:
	हाल HFA384x_PDR_HFA3861_SHADOW:
	हाल HFA384x_PDR_HFA3861_IFRF:
	हाल HFA384x_PDR_HFA3861_CHCALSP:
	हाल HFA384x_PDR_HFA3861_CHCALI:
	हाल HFA384x_PDR_3842_NIC_CONFIG:
	हाल HFA384x_PDR_USB_ID:
	हाल HFA384x_PDR_PCI_ID:
	हाल HFA384x_PDR_PCI_IFCONF:
	हाल HFA384x_PDR_PCI_PMCONF:
	हाल HFA384x_PDR_RFENRGY:
	हाल HFA384x_PDR_HFA3861_MANF_TESTSP:
	हाल HFA384x_PDR_HFA3861_MANF_TESTI:
		/* code is OK */
		वापस 1;
	शेष:
		अगर (pdrcode < 0x1000) अणु
			/* code is OK, but we करोn't know exactly what it is */
			pr_debug("Encountered unknown PDR#=0x%04x, assuming it's ok.\n",
				 pdrcode);
			वापस 1;
		पूर्ण
		अवरोध;
	पूर्ण
	/* bad code */
	pr_debug("Encountered unknown PDR#=0x%04x, (>=0x1000), assuming it's bad.\n",
		 pdrcode);
	वापस 0;
पूर्ण
