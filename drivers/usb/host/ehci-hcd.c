<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Enhanced Host Controller Interface (EHCI) driver क्रम USB.
 *
 * Maपूर्णांकainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * Copyright (c) 2000-2004 by David Brownell
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>

#अगर defined(CONFIG_PPC_PS3)
#समावेश <यंत्र/firmware.h>
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/*
 * EHCI hc_driver implementation ... experimental, incomplete.
 * Based on the final 1.0 रेजिस्टर पूर्णांकerface specअगरication.
 *
 * USB 2.0 shows up in upcoming www.pcmcia.org technology.
 * First was PCMCIA, like ISA; then CardBus, which is PCI.
 * Next comes "CardBay", using USB 2.0 संकेतs.
 *
 * Contains additional contributions by Brad Hards, Rory Bolt, and others.
 * Special thanks to Intel and VIA क्रम providing host controllers to
 * test this driver on, and Cypress (including In-System Design) क्रम
 * providing early devices क्रम those host controllers to talk to!
 */

#घोषणा DRIVER_AUTHOR "David Brownell"
#घोषणा DRIVER_DESC "USB 2.0 'Enhanced' Host Controller (EHCI) Driver"

अटल स्थिर अक्षर	hcd_name [] = "ehci_hcd";


#अघोषित EHCI_URB_TRACE

/* magic numbers that can affect प्रणाली perक्रमmance */
#घोषणा	EHCI_TUNE_CERR		3	/* 0-3 qtd retries; 0 == करोn't stop */
#घोषणा	EHCI_TUNE_RL_HS		4	/* nak throttle; see 4.9 */
#घोषणा	EHCI_TUNE_RL_TT		0
#घोषणा	EHCI_TUNE_MULT_HS	1	/* 1-3 transactions/uframe; 4.10.3 */
#घोषणा	EHCI_TUNE_MULT_TT	1
/*
 * Some drivers think it's safe to schedule isochronous transfers more than
 * 256 ms पूर्णांकo the future (partly as a result of an old bug in the scheduling
 * code).  In an attempt to aव्योम trouble, we will use a minimum scheduling
 * length of 512 frames instead of 256.
 */
#घोषणा	EHCI_TUNE_FLS		1	/* (medium) 512-frame schedule */

/* Initial IRQ latency:  faster than hw शेष */
अटल पूर्णांक log2_irq_thresh = 0;		// 0 to 6
module_param (log2_irq_thresh, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC (log2_irq_thresh, "log2 IRQ latency, 1-64 microframes");

/* initial park setting:  slower than hw शेष */
अटल अचिन्हित park = 0;
module_param (park, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC (park, "park setting; 1-3 back-to-back async packets");

/* क्रम flakey hardware, ignore overcurrent indicators */
अटल bool ignore_oc;
module_param (ignore_oc, bool, S_IRUGO);
MODULE_PARM_DESC (ignore_oc, "ignore bogus hardware overcurrent indications");

#घोषणा	INTR_MASK (STS_IAA | STS_FATAL | STS_PCD | STS_ERR | STS_INT)

/*-------------------------------------------------------------------------*/

#समावेश "ehci.h"
#समावेश "pci-quirks.h"

अटल व्योम compute_tt_budget(u8 budget_table[EHCI_BANDWIDTH_SIZE],
		काष्ठा ehci_tt *tt);

/*
 * The MosChip MCS9990 controller updates its microframe counter
 * a little beक्रमe the frame counter, and occasionally we will पढ़ो
 * the invalid पूर्णांकermediate value.  Aव्योम problems by checking the
 * microframe number (the low-order 3 bits); अगर they are 0 then
 * re-पढ़ो the रेजिस्टर to get the correct value.
 */
अटल अचिन्हित ehci_moschip_पढ़ो_frame_index(काष्ठा ehci_hcd *ehci)
अणु
	अचिन्हित uf;

	uf = ehci_पढ़ोl(ehci, &ehci->regs->frame_index);
	अगर (unlikely((uf & 7) == 0))
		uf = ehci_पढ़ोl(ehci, &ehci->regs->frame_index);
	वापस uf;
पूर्ण

अटल अंतरभूत अचिन्हित ehci_पढ़ो_frame_index(काष्ठा ehci_hcd *ehci)
अणु
	अगर (ehci->frame_index_bug)
		वापस ehci_moschip_पढ़ो_frame_index(ehci);
	वापस ehci_पढ़ोl(ehci, &ehci->regs->frame_index);
पूर्ण

#समावेश "ehci-dbg.c"

/*-------------------------------------------------------------------------*/

/*
 * ehci_handshake - spin पढ़ोing hc until handshake completes or fails
 * @ptr: address of hc रेजिस्टर to be पढ़ो
 * @mask: bits to look at in result of पढ़ो
 * @करोne: value of those bits when handshake succeeds
 * @usec: समयout in microseconds
 *
 * Returns negative त्रुटि_सं, or zero on success
 *
 * Success happens when the "mask" bits have the specअगरied value (hardware
 * handshake करोne).  There are two failure modes:  "usec" have passed (major
 * hardware flakeout), or the रेजिस्टर पढ़ोs as all-ones (hardware हटाओd).
 *
 * That last failure should_only happen in हालs like physical cardbus eject
 * beक्रमe driver shutकरोwn. But it also seems to be caused by bugs in cardbus
 * bridge shutकरोwn:  shutting करोwn the bridge beक्रमe the devices using it.
 */
पूर्णांक ehci_handshake(काष्ठा ehci_hcd *ehci, व्योम __iomem *ptr,
		   u32 mask, u32 करोne, पूर्णांक usec)
अणु
	u32	result;

	करो अणु
		result = ehci_पढ़ोl(ehci, ptr);
		अगर (result == ~(u32)0)		/* card हटाओd */
			वापस -ENODEV;
		result &= mask;
		अगर (result == करोne)
			वापस 0;
		udelay (1);
		usec--;
	पूर्ण जबतक (usec > 0);
	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL_GPL(ehci_handshake);

/* check TDI/ARC silicon is in host mode */
अटल पूर्णांक tdi_in_host_mode (काष्ठा ehci_hcd *ehci)
अणु
	u32		पंचांगp;

	पंचांगp = ehci_पढ़ोl(ehci, &ehci->regs->usbmode);
	वापस (पंचांगp & 3) == USBMODE_CM_HC;
पूर्ण

/*
 * Force HC to halt state from unknown (EHCI spec section 2.3).
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
अटल पूर्णांक ehci_halt (काष्ठा ehci_hcd *ehci)
अणु
	u32	temp;

	spin_lock_irq(&ehci->lock);

	/* disable any irqs left enabled by previous code */
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->पूर्णांकr_enable);

	अगर (ehci_is_TDI(ehci) && !tdi_in_host_mode(ehci)) अणु
		spin_unlock_irq(&ehci->lock);
		वापस 0;
	पूर्ण

	/*
	 * This routine माला_लो called during probe beक्रमe ehci->command
	 * has been initialized, so we can't rely on its value.
	 */
	ehci->command &= ~CMD_RUN;
	temp = ehci_पढ़ोl(ehci, &ehci->regs->command);
	temp &= ~(CMD_RUN | CMD_IAAD);
	ehci_ग_लिखोl(ehci, temp, &ehci->regs->command);

	spin_unlock_irq(&ehci->lock);
	synchronize_irq(ehci_to_hcd(ehci)->irq);

	वापस ehci_handshake(ehci, &ehci->regs->status,
			  STS_HALT, STS_HALT, 16 * 125);
पूर्ण

/* put TDI/ARC silicon पूर्णांकo EHCI mode */
अटल व्योम tdi_reset (काष्ठा ehci_hcd *ehci)
अणु
	u32		पंचांगp;

	पंचांगp = ehci_पढ़ोl(ehci, &ehci->regs->usbmode);
	पंचांगp |= USBMODE_CM_HC;
	/* The शेष byte access to MMR space is LE after
	 * controller reset. Set the required endian mode
	 * क्रम transfer buffers to match the host microprocessor
	 */
	अगर (ehci_big_endian_mmio(ehci))
		पंचांगp |= USBMODE_BE;
	ehci_ग_लिखोl(ehci, पंचांगp, &ehci->regs->usbmode);
पूर्ण

/*
 * Reset a non-running (STS_HALT == 1) controller.
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
पूर्णांक ehci_reset(काष्ठा ehci_hcd *ehci)
अणु
	पूर्णांक	retval;
	u32	command = ehci_पढ़ोl(ehci, &ehci->regs->command);

	/* If the EHCI debug controller is active, special care must be
	 * taken beक्रमe and after a host controller reset */
	अगर (ehci->debug && !dbgp_reset_prep(ehci_to_hcd(ehci)))
		ehci->debug = शून्य;

	command |= CMD_RESET;
	dbg_cmd (ehci, "reset", command);
	ehci_ग_लिखोl(ehci, command, &ehci->regs->command);
	ehci->rh_state = EHCI_RH_HALTED;
	ehci->next_statechange = jअगरfies;
	retval = ehci_handshake(ehci, &ehci->regs->command,
			    CMD_RESET, 0, 250 * 1000);

	अगर (ehci->has_hostpc) अणु
		ehci_ग_लिखोl(ehci, USBMODE_EX_HC | USBMODE_EX_VBPS,
				&ehci->regs->usbmode_ex);
		ehci_ग_लिखोl(ehci, TXFIFO_DEFAULT, &ehci->regs->txfill_tuning);
	पूर्ण
	अगर (retval)
		वापस retval;

	अगर (ehci_is_TDI(ehci))
		tdi_reset (ehci);

	अगर (ehci->debug)
		dbgp_बाह्यal_startup(ehci_to_hcd(ehci));

	ehci->port_c_suspend = ehci->suspended_ports =
			ehci->resuming_ports = 0;
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(ehci_reset);

/*
 * Idle the controller (turn off the schedules).
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
अटल व्योम ehci_quiesce (काष्ठा ehci_hcd *ehci)
अणु
	u32	temp;

	अगर (ehci->rh_state != EHCI_RH_RUNNING)
		वापस;

	/* रुको क्रम any schedule enables/disables to take effect */
	temp = (ehci->command << 10) & (STS_ASS | STS_PSS);
	ehci_handshake(ehci, &ehci->regs->status, STS_ASS | STS_PSS, temp,
			16 * 125);

	/* then disable anything that's still active */
	spin_lock_irq(&ehci->lock);
	ehci->command &= ~(CMD_ASE | CMD_PSE);
	ehci_ग_लिखोl(ehci, ehci->command, &ehci->regs->command);
	spin_unlock_irq(&ehci->lock);

	/* hardware can take 16 microframes to turn off ... */
	ehci_handshake(ehci, &ehci->regs->status, STS_ASS | STS_PSS, 0,
			16 * 125);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम end_iaa_cycle(काष्ठा ehci_hcd *ehci);
अटल व्योम end_unlink_async(काष्ठा ehci_hcd *ehci);
अटल व्योम unlink_empty_async(काष्ठा ehci_hcd *ehci);
अटल व्योम ehci_work(काष्ठा ehci_hcd *ehci);
अटल व्योम start_unlink_पूर्णांकr(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh);
अटल व्योम end_unlink_पूर्णांकr(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh);
अटल पूर्णांक ehci_port_घातer(काष्ठा ehci_hcd *ehci, पूर्णांक portnum, bool enable);

#समावेश "ehci-timer.c"
#समावेश "ehci-hub.c"
#समावेश "ehci-mem.c"
#समावेश "ehci-q.c"
#समावेश "ehci-sched.c"
#समावेश "ehci-sysfs.c"

/*-------------------------------------------------------------------------*/

/* On some प्रणालीs, leaving remote wakeup enabled prevents प्रणाली shutकरोwn.
 * The firmware seems to think that घातering off is a wakeup event!
 * This routine turns off remote wakeup and everything अन्यथा, on all ports.
 */
अटल व्योम ehci_turn_off_all_ports(काष्ठा ehci_hcd *ehci)
अणु
	पूर्णांक	port = HCS_N_PORTS(ehci->hcs_params);

	जबतक (port--) अणु
		spin_unlock_irq(&ehci->lock);
		ehci_port_घातer(ehci, port, false);
		spin_lock_irq(&ehci->lock);
		ehci_ग_लिखोl(ehci, PORT_RWC_BITS,
				&ehci->regs->port_status[port]);
	पूर्ण
पूर्ण

/*
 * Halt HC, turn off all ports, and let the BIOS use the companion controllers.
 * Must be called with पूर्णांकerrupts enabled and the lock not held.
 */
अटल व्योम ehci_silence_controller(काष्ठा ehci_hcd *ehci)
अणु
	ehci_halt(ehci);

	spin_lock_irq(&ehci->lock);
	ehci->rh_state = EHCI_RH_HALTED;
	ehci_turn_off_all_ports(ehci);

	/* make BIOS/etc use companion controller during reboot */
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->configured_flag);

	/* unblock posted ग_लिखोs */
	ehci_पढ़ोl(ehci, &ehci->regs->configured_flag);
	spin_unlock_irq(&ehci->lock);
पूर्ण

/* ehci_shutकरोwn kick in क्रम silicon on any bus (not just pci, etc).
 * This क्रमcibly disables dma and IRQs, helping kexec and other हालs
 * where the next प्रणाली software may expect clean state.
 */
अटल व्योम ehci_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd	*ehci = hcd_to_ehci(hcd);

	/**
	 * Protect the प्रणाली from crashing at प्रणाली shutकरोwn in हालs where
	 * usb host is not added yet from OTG controller driver.
	 * As ehci_setup() not करोne yet, so stop accessing रेजिस्टरs or
	 * variables initialized in ehci_setup()
	 */
	अगर (!ehci->sbrn)
		वापस;

	spin_lock_irq(&ehci->lock);
	ehci->shutकरोwn = true;
	ehci->rh_state = EHCI_RH_STOPPING;
	ehci->enabled_hrसमयr_events = 0;
	spin_unlock_irq(&ehci->lock);

	ehci_silence_controller(ehci);

	hrसमयr_cancel(&ehci->hrसमयr);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * ehci_work is called from some पूर्णांकerrupts, समयrs, and so on.
 * it calls driver completion functions, after dropping ehci->lock.
 */
अटल व्योम ehci_work (काष्ठा ehci_hcd *ehci)
अणु
	/* another CPU may drop ehci->lock during a schedule scan जबतक
	 * it reports urb completions.  this flag guards against bogus
	 * attempts at re-entrant schedule scanning.
	 */
	अगर (ehci->scanning) अणु
		ehci->need_rescan = true;
		वापस;
	पूर्ण
	ehci->scanning = true;

 rescan:
	ehci->need_rescan = false;
	अगर (ehci->async_count)
		scan_async(ehci);
	अगर (ehci->पूर्णांकr_count > 0)
		scan_पूर्णांकr(ehci);
	अगर (ehci->isoc_count > 0)
		scan_isoc(ehci);
	अगर (ehci->need_rescan)
		जाओ rescan;
	ehci->scanning = false;

	/* the IO watchकरोg guards against hardware or driver bugs that
	 * misplace IRQs, and should let us run completely without IRQs.
	 * such lossage has been observed on both VT6202 and VT8235.
	 */
	turn_on_io_watchकरोg(ehci);
पूर्ण

/*
 * Called when the ehci_hcd module is हटाओd.
 */
अटल व्योम ehci_stop (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);

	ehci_dbg (ehci, "stop\n");

	/* no more पूर्णांकerrupts ... */

	spin_lock_irq(&ehci->lock);
	ehci->enabled_hrसमयr_events = 0;
	spin_unlock_irq(&ehci->lock);

	ehci_quiesce(ehci);
	ehci_silence_controller(ehci);
	ehci_reset (ehci);

	hrसमयr_cancel(&ehci->hrसमयr);
	हटाओ_sysfs_files(ehci);
	हटाओ_debug_files (ehci);

	/* root hub is shut करोwn separately (first, when possible) */
	spin_lock_irq (&ehci->lock);
	end_मुक्त_itds(ehci);
	spin_unlock_irq (&ehci->lock);
	ehci_mem_cleanup (ehci);

	अगर (ehci->amd_pll_fix == 1)
		usb_amd_dev_put();

	dbg_status (ehci, "ehci_stop completed",
		    ehci_पढ़ोl(ehci, &ehci->regs->status));
पूर्ण

/* one-समय init, only क्रम memory state */
अटल पूर्णांक ehci_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	u32			temp;
	पूर्णांक			retval;
	u32			hcc_params;
	काष्ठा ehci_qh_hw	*hw;

	spin_lock_init(&ehci->lock);

	/*
	 * keep io watchकरोg by शेष, those good HCDs could turn off it later
	 */
	ehci->need_io_watchकरोg = 1;

	hrसमयr_init(&ehci->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	ehci->hrसमयr.function = ehci_hrसमयr_func;
	ehci->next_hrसमयr_event = EHCI_HRTIMER_NO_EVENT;

	hcc_params = ehci_पढ़ोl(ehci, &ehci->caps->hcc_params);

	/*
	 * by शेष set standard 80% (== 100 usec/uframe) max periodic
	 * bandwidth as required by USB 2.0
	 */
	ehci->uframe_periodic_max = 100;

	/*
	 * hw शेष: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update अगर hcc_params allows.
	 */
	ehci->periodic_size = DEFAULT_I_TDPS;
	INIT_LIST_HEAD(&ehci->async_unlink);
	INIT_LIST_HEAD(&ehci->async_idle);
	INIT_LIST_HEAD(&ehci->पूर्णांकr_unlink_रुको);
	INIT_LIST_HEAD(&ehci->पूर्णांकr_unlink);
	INIT_LIST_HEAD(&ehci->पूर्णांकr_qh_list);
	INIT_LIST_HEAD(&ehci->cached_itd_list);
	INIT_LIST_HEAD(&ehci->cached_sitd_list);
	INIT_LIST_HEAD(&ehci->tt_list);

	अगर (HCC_PGM_FRAMELISTLEN(hcc_params)) अणु
		/* periodic schedule size can be smaller than शेष */
		चयन (EHCI_TUNE_FLS) अणु
		हाल 0: ehci->periodic_size = 1024; अवरोध;
		हाल 1: ehci->periodic_size = 512; अवरोध;
		हाल 2: ehci->periodic_size = 256; अवरोध;
		शेष:	BUG();
		पूर्ण
	पूर्ण
	अगर ((retval = ehci_mem_init(ehci, GFP_KERNEL)) < 0)
		वापस retval;

	/* controllers may cache some of the periodic schedule ... */
	अगर (HCC_ISOC_CACHE(hcc_params))		// full frame cache
		ehci->i_thresh = 0;
	अन्यथा					// N microframes cached
		ehci->i_thresh = 2 + HCC_ISOC_THRES(hcc_params);

	/*
	 * dedicate a qh क्रम the async ring head, since we couldn't unlink
	 * a 'real' qh without stopping the async schedule [4.8].  use it
	 * as the 'reclamation list head' too.
	 * its dummy is used in hw_alt_next of many tds, to prevent the qh
	 * from स्वतःmatically advancing to the next td after लघु पढ़ोs.
	 */
	ehci->async->qh_next.qh = शून्य;
	hw = ehci->async->hw;
	hw->hw_next = QH_NEXT(ehci, ehci->async->qh_dma);
	hw->hw_info1 = cpu_to_hc32(ehci, QH_HEAD);
#अगर defined(CONFIG_PPC_PS3)
	hw->hw_info1 |= cpu_to_hc32(ehci, QH_INACTIVATE);
#पूर्ण_अगर
	hw->hw_token = cpu_to_hc32(ehci, QTD_STS_HALT);
	hw->hw_qtd_next = EHCI_LIST_END(ehci);
	ehci->async->qh_state = QH_STATE_LINKED;
	hw->hw_alt_next = QTD_NEXT(ehci, ehci->async->dummy->qtd_dma);

	/* clear पूर्णांकerrupt enables, set irq latency */
	अगर (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
	temp = 1 << (16 + log2_irq_thresh);
	अगर (HCC_PER_PORT_CHANGE_EVENT(hcc_params)) अणु
		ehci->has_ppcd = 1;
		ehci_dbg(ehci, "enable per-port change event\n");
		temp |= CMD_PPCEE;
	पूर्ण
	अगर (HCC_CANPARK(hcc_params)) अणु
		/* HW शेष park == 3, on hardware that supports it (like
		 * NVidia and ALI silicon), maximizes throughput on the async
		 * schedule by aव्योमing QH fetches between transfers.
		 *
		 * With fast usb storage devices and NForce2, "park" seems to
		 * make problems:  throughput reduction (!), data errors...
		 */
		अगर (park) अणु
			park = min(park, (अचिन्हित) 3);
			temp |= CMD_PARK;
			temp |= park << 8;
		पूर्ण
		ehci_dbg(ehci, "park %d\n", park);
	पूर्ण
	अगर (HCC_PGM_FRAMELISTLEN(hcc_params)) अणु
		/* periodic schedule size can be smaller than शेष */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FLS << 2);
	पूर्ण
	ehci->command = temp;

	/* Accept arbitrarily दीर्घ scatter-gather lists */
	अगर (!hcd->localmem_pool)
		hcd->self.sg_tablesize = ~0;

	/* Prepare क्रम unlinking active QHs */
	ehci->old_current = ~0;
	वापस 0;
पूर्ण

/* start HC running; it's halted, ehci_init() has been run (once) */
अटल पूर्णांक ehci_run (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			temp;
	u32			hcc_params;
	पूर्णांक			rc;

	hcd->uses_new_polling = 1;

	/* EHCI spec section 4.1 */

	ehci_ग_लिखोl(ehci, ehci->periodic_dma, &ehci->regs->frame_list);
	ehci_ग_लिखोl(ehci, (u32)ehci->async->qh_dma, &ehci->regs->async_next);

	/*
	 * hcc_params controls whether ehci->regs->segment must (!!!)
	 * be used; it स्थिरrains QH/ITD/SITD and QTD locations.
	 * dma_pool consistent memory always uses segment zero.
	 * streaming mappings क्रम I/O buffers, like pci_map_single(),
	 * can वापस segments above 4GB, अगर the device allows.
	 *
	 * NOTE:  the dma mask is visible through dev->dma_mask, so
	 * drivers can pass this info aदीर्घ ... like NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so क्रमth.  It's पढ़ोonly to all
	 * host side drivers though.
	 */
	hcc_params = ehci_पढ़ोl(ehci, &ehci->caps->hcc_params);
	अगर (HCC_64BIT_ADDR(hcc_params)) अणु
		ehci_ग_लिखोl(ehci, 0, &ehci->regs->segment);
#अगर 0
// this is deeply broken on almost all architectures
		अगर (!dma_set_mask(hcd->self.controller, DMA_BIT_MASK(64)))
			ehci_info(ehci, "enabled 64bit DMA\n");
#पूर्ण_अगर
	पूर्ण


	// Philips, Intel, and maybe others need CMD_RUN beक्रमe the
	// root hub will detect new devices (why?); NEC करोesn't
	ehci->command &= ~(CMD_LRESET|CMD_IAAD|CMD_PSE|CMD_ASE|CMD_RESET);
	ehci->command |= CMD_RUN;
	ehci_ग_लिखोl(ehci, ehci->command, &ehci->regs->command);
	dbg_cmd (ehci, "init", ehci->command);

	/*
	 * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
	 * are explicitly handed to companion controller(s), so no TT is
	 * involved with the root hub.  (Except where one is पूर्णांकegrated,
	 * and there's no companion controller unless maybe क्रम USB OTG.)
	 *
	 * Turning on the CF flag will transfer ownership of all ports
	 * from the companions to the EHCI controller.  If any of the
	 * companions are in the middle of a port reset at the समय, it
	 * could cause trouble.  Write-locking ehci_cf_port_reset_rwsem
	 * guarantees that no resets are in progress.  After we set CF,
	 * a लघु delay lets the hardware catch up; new resets shouldn't
	 * be started beक्रमe the port चयनing actions could complete.
	 */
	करोwn_ग_लिखो(&ehci_cf_port_reset_rwsem);
	ehci->rh_state = EHCI_RH_RUNNING;
	ehci_ग_लिखोl(ehci, FLAG_CF, &ehci->regs->configured_flag);

	/* Wait until HC become operational */
	ehci_पढ़ोl(ehci, &ehci->regs->command);	/* unblock posted ग_लिखोs */
	msleep(5);
	rc = ehci_handshake(ehci, &ehci->regs->status, STS_HALT, 0, 100 * 1000);

	up_ग_लिखो(&ehci_cf_port_reset_rwsem);

	अगर (rc) अणु
		ehci_err(ehci, "USB %x.%x, controller refused to start: %d\n",
			 ((ehci->sbrn & 0xf0)>>4), (ehci->sbrn & 0x0f), rc);
		वापस rc;
	पूर्ण

	ehci->last_periodic_enable = kसमय_get_real();

	temp = HC_VERSION(ehci, ehci_पढ़ोl(ehci, &ehci->caps->hc_capbase));
	ehci_info (ehci,
		"USB %x.%x started, EHCI %x.%02x%s\n",
		((ehci->sbrn & 0xf0)>>4), (ehci->sbrn & 0x0f),
		temp >> 8, temp & 0xff,
		(ignore_oc || ehci->spurious_oc) ? ", overcurrent ignored" : "");

	ehci_ग_लिखोl(ehci, INTR_MASK,
		    &ehci->regs->पूर्णांकr_enable); /* Turn On Interrupts */

	/* GRR this is run-once init(), being करोne every समय the HC starts.
	 * So दीर्घ as they're part of class devices, we can't करो it init()
	 * since the class device isn't created that early.
	 */
	create_debug_files(ehci);
	create_sysfs_files(ehci);

	वापस 0;
पूर्ण

पूर्णांक ehci_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	पूर्णांक retval;

	ehci->regs = (व्योम __iomem *)ehci->caps +
	    HC_LENGTH(ehci, ehci_पढ़ोl(ehci, &ehci->caps->hc_capbase));
	dbg_hcs_params(ehci, "reset");
	dbg_hcc_params(ehci, "reset");

	/* cache this पढ़ोonly data; minimize chip पढ़ोs */
	ehci->hcs_params = ehci_पढ़ोl(ehci, &ehci->caps->hcs_params);

	ehci->sbrn = HCD_USB2;

	/* data काष्ठाure init */
	retval = ehci_init(hcd);
	अगर (retval)
		वापस retval;

	retval = ehci_halt(ehci);
	अगर (retval) अणु
		ehci_mem_cleanup(ehci);
		वापस retval;
	पूर्ण

	ehci_reset(ehci);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ehci_setup);

/*-------------------------------------------------------------------------*/

अटल irqवापस_t ehci_irq (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			status, masked_status, pcd_status = 0, cmd;
	पूर्णांक			bh;

	spin_lock(&ehci->lock);

	status = ehci_पढ़ोl(ehci, &ehci->regs->status);

	/* e.g. cardbus physical eject */
	अगर (status == ~(u32) 0) अणु
		ehci_dbg (ehci, "device removed\n");
		जाओ dead;
	पूर्ण

	/*
	 * We करोn't use STS_FLR, but some controllers don't like it to
	 * reमुख्य on, so mask it out aदीर्घ with the other status bits.
	 */
	masked_status = status & (INTR_MASK | STS_FLR);

	/* Shared IRQ? */
	अगर (!masked_status || unlikely(ehci->rh_state == EHCI_RH_HALTED)) अणु
		spin_unlock(&ehci->lock);
		वापस IRQ_NONE;
	पूर्ण

	/* clear (just) पूर्णांकerrupts */
	ehci_ग_लिखोl(ehci, masked_status, &ehci->regs->status);
	cmd = ehci_पढ़ोl(ehci, &ehci->regs->command);
	bh = 0;

	/* normal [4.15.1.2] or error [4.15.1.1] completion */
	अगर (likely ((status & (STS_INT|STS_ERR)) != 0)) अणु
		अगर (likely ((status & STS_ERR) == 0))
			INCR(ehci->stats.normal);
		अन्यथा
			INCR(ehci->stats.error);
		bh = 1;
	पूर्ण

	/* complete the unlinking of some qh [4.15.2.3] */
	अगर (status & STS_IAA) अणु

		/* Turn off the IAA watchकरोg */
		ehci->enabled_hrसमयr_events &= ~BIT(EHCI_HRTIMER_IAA_WATCHDOG);

		/*
		 * Mild optimization: Allow another IAAD to reset the
		 * hrसमयr, अगर one occurs beक्रमe the next expiration.
		 * In theory we could always cancel the hrसमयr, but
		 * tests show that about half the समय it will be reset
		 * क्रम some other event anyway.
		 */
		अगर (ehci->next_hrसमयr_event == EHCI_HRTIMER_IAA_WATCHDOG)
			++ehci->next_hrसमयr_event;

		/* guard against (alleged) silicon errata */
		अगर (cmd & CMD_IAAD)
			ehci_dbg(ehci, "IAA with IAAD still set?\n");
		अगर (ehci->iaa_in_progress)
			INCR(ehci->stats.iaa);
		end_iaa_cycle(ehci);
	पूर्ण

	/* remote wakeup [4.3.1] */
	अगर (status & STS_PCD) अणु
		अचिन्हित	i = HCS_N_PORTS (ehci->hcs_params);
		u32		ppcd = ~0;

		/* kick root hub later */
		pcd_status = status;

		/* resume root hub? */
		अगर (ehci->rh_state == EHCI_RH_SUSPENDED)
			usb_hcd_resume_root_hub(hcd);

		/* get per-port change detect bits */
		अगर (ehci->has_ppcd)
			ppcd = status >> 16;

		जबतक (i--) अणु
			पूर्णांक pstatus;

			/* leverage per-port change bits feature */
			अगर (!(ppcd & (1 << i)))
				जारी;
			pstatus = ehci_पढ़ोl(ehci,
					 &ehci->regs->port_status[i]);

			अगर (pstatus & PORT_OWNER)
				जारी;
			अगर (!(test_bit(i, &ehci->suspended_ports) &&
					((pstatus & PORT_RESUME) ||
						!(pstatus & PORT_SUSPEND)) &&
					(pstatus & PORT_PE) &&
					ehci->reset_करोne[i] == 0))
				जारी;

			/* start USB_RESUME_TIMEOUT msec resume संकेतing from
			 * this port, and make hub_wq collect
			 * PORT_STAT_C_SUSPEND to stop that संकेतing.
			 */
			ehci->reset_करोne[i] = jअगरfies +
				msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			set_bit(i, &ehci->resuming_ports);
			ehci_dbg (ehci, "port %d remote wakeup\n", i + 1);
			usb_hcd_start_port_resume(&hcd->self, i);
			mod_समयr(&hcd->rh_समयr, ehci->reset_करोne[i]);
		पूर्ण
	पूर्ण

	/* PCI errors [4.15.2.4] */
	अगर (unlikely ((status & STS_FATAL) != 0)) अणु
		ehci_err(ehci, "fatal error\n");
		dbg_cmd(ehci, "fatal", cmd);
		dbg_status(ehci, "fatal", status);
dead:
		usb_hc_died(hcd);

		/* Don't let the controller करो anything more */
		ehci->shutकरोwn = true;
		ehci->rh_state = EHCI_RH_STOPPING;
		ehci->command &= ~(CMD_RUN | CMD_ASE | CMD_PSE);
		ehci_ग_लिखोl(ehci, ehci->command, &ehci->regs->command);
		ehci_ग_लिखोl(ehci, 0, &ehci->regs->पूर्णांकr_enable);
		ehci_handle_controller_death(ehci);

		/* Handle completions when the controller stops */
		bh = 0;
	पूर्ण

	अगर (bh)
		ehci_work (ehci);
	spin_unlock(&ehci->lock);
	अगर (pcd_status)
		usb_hcd_poll_rh_status(hcd);
	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * non-error वापसs are a promise to giveback() the urb later
 * we drop ownership so next owner (or urb unlink) can get it
 *
 * urb + dev is in hcd.self.controller.urb_list
 * we're queueing TDs onto software and hardware lists
 *
 * hcd-specअगरic init क्रम hcpriv hasn't been करोne yet
 *
 * NOTE:  control, bulk, and पूर्णांकerrupt share the same code to append TDs
 * to a (possibly active) QH, and the same QH scanning code.
 */
अटल पूर्णांक ehci_urb_enqueue (
	काष्ठा usb_hcd	*hcd,
	काष्ठा urb	*urb,
	gfp_t		mem_flags
) अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	काष्ठा list_head	qtd_list;

	INIT_LIST_HEAD (&qtd_list);

	चयन (usb_pipetype (urb->pipe)) अणु
	हाल PIPE_CONTROL:
		/* qh_completions() code करोesn't handle all the fault हालs
		 * in multi-TD control transfers.  Even 1KB is rare anyway.
		 */
		अगर (urb->transfer_buffer_length > (16 * 1024))
			वापस -EMSGSIZE;
		fallthrough;
	/* हाल PIPE_BULK: */
	शेष:
		अगर (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
			वापस -ENOMEM;
		वापस submit_async(ehci, urb, &qtd_list, mem_flags);

	हाल PIPE_INTERRUPT:
		अगर (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
			वापस -ENOMEM;
		वापस पूर्णांकr_submit(ehci, urb, &qtd_list, mem_flags);

	हाल PIPE_ISOCHRONOUS:
		अगर (urb->dev->speed == USB_SPEED_HIGH)
			वापस itd_submit (ehci, urb, mem_flags);
		अन्यथा
			वापस sitd_submit (ehci, urb, mem_flags);
	पूर्ण
पूर्ण

/* हटाओ from hardware lists
 * completions normally happen asynchronously
 */

अटल पूर्णांक ehci_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	काष्ठा ehci_qh		*qh;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			rc;

	spin_lock_irqsave (&ehci->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ करोne;

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
		/*
		 * We करोn't expedite dequeue क्रम isochronous URBs.
		 * Just रुको until they complete normally or their
		 * समय slot expires.
		 */
	पूर्ण अन्यथा अणु
		qh = (काष्ठा ehci_qh *) urb->hcpriv;
		qh->unlink_reason |= QH_UNLINK_REQUESTED;
		चयन (qh->qh_state) अणु
		हाल QH_STATE_LINKED:
			अगर (usb_pipetype(urb->pipe) == PIPE_INTERRUPT)
				start_unlink_पूर्णांकr(ehci, qh);
			अन्यथा
				start_unlink_async(ehci, qh);
			अवरोध;
		हाल QH_STATE_COMPLETING:
			qh->dequeue_during_giveback = 1;
			अवरोध;
		हाल QH_STATE_UNLINK:
		हाल QH_STATE_UNLINK_WAIT:
			/* alपढ़ोy started */
			अवरोध;
		हाल QH_STATE_IDLE:
			/* QH might be रुकोing क्रम a Clear-TT-Buffer */
			qh_completions(ehci, qh);
			अवरोध;
		पूर्ण
	पूर्ण
करोne:
	spin_unlock_irqrestore (&ehci->lock, flags);
	वापस rc;
पूर्ण

/*-------------------------------------------------------------------------*/

// bulk qh holds the data toggle

अटल व्योम
ehci_endpoपूर्णांक_disable (काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	अचिन्हित दीर्घ		flags;
	काष्ठा ehci_qh		*qh;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs क्रम this any more */

rescan:
	spin_lock_irqsave (&ehci->lock, flags);
	qh = ep->hcpriv;
	अगर (!qh)
		जाओ करोne;

	/* endpoपूर्णांकs can be iso streams.  क्रम now, we करोn't
	 * accelerate iso completions ... so spin a जबतक.
	 */
	अगर (qh->hw == शून्य) अणु
		काष्ठा ehci_iso_stream	*stream = ep->hcpriv;

		अगर (!list_empty(&stream->td_list))
			जाओ idle_समयout;

		/* BUG_ON(!list_empty(&stream->मुक्त_list)); */
		reserve_release_iso_bandwidth(ehci, stream, -1);
		kमुक्त(stream);
		जाओ करोne;
	पूर्ण

	qh->unlink_reason |= QH_UNLINK_REQUESTED;
	चयन (qh->qh_state) अणु
	हाल QH_STATE_LINKED:
		अगर (list_empty(&qh->qtd_list))
			qh->unlink_reason |= QH_UNLINK_QUEUE_EMPTY;
		अन्यथा
			WARN_ON(1);
		अगर (usb_endpoपूर्णांक_type(&ep->desc) != USB_ENDPOINT_XFER_INT)
			start_unlink_async(ehci, qh);
		अन्यथा
			start_unlink_पूर्णांकr(ehci, qh);
		fallthrough;
	हाल QH_STATE_COMPLETING:	/* alपढ़ोy in unlinking */
	हाल QH_STATE_UNLINK:		/* रुको क्रम hw to finish? */
	हाल QH_STATE_UNLINK_WAIT:
idle_समयout:
		spin_unlock_irqrestore (&ehci->lock, flags);
		schedule_समयout_unपूर्णांकerruptible(1);
		जाओ rescan;
	हाल QH_STATE_IDLE:		/* fully unlinked */
		अगर (qh->clearing_tt)
			जाओ idle_समयout;
		अगर (list_empty (&qh->qtd_list)) अणु
			अगर (qh->ps.bw_uperiod)
				reserve_release_पूर्णांकr_bandwidth(ehci, qh, -1);
			qh_destroy(ehci, qh);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  just leak this memory.
		 */
		ehci_err (ehci, "qh %p (#%02x) state %d%s\n",
			qh, ep->desc.bEndpoपूर्णांकAddress, qh->qh_state,
			list_empty (&qh->qtd_list) ? "" : "(has tds)");
		अवरोध;
	पूर्ण
 करोne:
	ep->hcpriv = शून्य;
	spin_unlock_irqrestore (&ehci->lock, flags);
पूर्ण

अटल व्योम
ehci_endpoपूर्णांक_reset(काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	काष्ठा ehci_qh		*qh;
	पूर्णांक			eptype = usb_endpoपूर्णांक_type(&ep->desc);
	पूर्णांक			epnum = usb_endpoपूर्णांक_num(&ep->desc);
	पूर्णांक			is_out = usb_endpoपूर्णांक_dir_out(&ep->desc);
	अचिन्हित दीर्घ		flags;

	अगर (eptype != USB_ENDPOINT_XFER_BULK && eptype != USB_ENDPOINT_XFER_INT)
		वापस;

	spin_lock_irqsave(&ehci->lock, flags);
	qh = ep->hcpriv;

	/* For Bulk and Interrupt endpoपूर्णांकs we मुख्यtain the toggle state
	 * in the hardware; the toggle bits in udev aren't used at all.
	 * When an endpoपूर्णांक is reset by usb_clear_halt() we must reset
	 * the toggle bit in the QH.
	 */
	अगर (qh) अणु
		अगर (!list_empty(&qh->qtd_list)) अणु
			WARN_ONCE(1, "clear_halt for a busy endpoint\n");
		पूर्ण अन्यथा अणु
			/* The toggle value in the QH can't be updated
			 * जबतक the QH is active.  Unlink it now;
			 * re-linking will call qh_refresh().
			 */
			usb_settoggle(qh->ps.udev, epnum, is_out, 0);
			qh->unlink_reason |= QH_UNLINK_REQUESTED;
			अगर (eptype == USB_ENDPOINT_XFER_BULK)
				start_unlink_async(ehci, qh);
			अन्यथा
				start_unlink_पूर्णांकr(ehci, qh);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ehci->lock, flags);
पूर्ण

अटल पूर्णांक ehci_get_frame (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	वापस (ehci_पढ़ो_frame_index(ehci) >> 3) % ehci->periodic_size;
पूर्ण

/*-------------------------------------------------------------------------*/

/* Device addition and removal */

अटल व्योम ehci_हटाओ_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);

	spin_lock_irq(&ehci->lock);
	drop_tt(udev);
	spin_unlock_irq(&ehci->lock);
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_PM

/* suspend/resume, section 4.3 */

/* These routines handle the generic parts of controller suspend/resume */

पूर्णांक ehci_suspend(काष्ठा usb_hcd *hcd, bool करो_wakeup)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);

	अगर (समय_beक्रमe(jअगरfies, ehci->next_statechange))
		msleep(10);

	/*
	 * Root hub was alपढ़ोy suspended.  Disable IRQ emission and
	 * mark HW unaccessible.  The PM and USB cores make sure that
	 * the root hub is either suspended or stopped.
	 */
	ehci_prepare_ports_क्रम_controller_suspend(ehci, करो_wakeup);

	spin_lock_irq(&ehci->lock);
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->पूर्णांकr_enable);
	(व्योम) ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable);

	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	spin_unlock_irq(&ehci->lock);

	synchronize_irq(hcd->irq);

	/* Check क्रम race with a wakeup request */
	अगर (करो_wakeup && HCD_WAKEUP_PENDING(hcd)) अणु
		ehci_resume(hcd, false);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ehci_suspend);

/* Returns 0 अगर घातer was preserved, 1 अगर घातer was lost */
पूर्णांक ehci_resume(काष्ठा usb_hcd *hcd, bool क्रमce_reset)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);

	अगर (समय_beक्रमe(jअगरfies, ehci->next_statechange))
		msleep(100);

	/* Mark hardware accessible again as we are back to full घातer by now */
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	अगर (ehci->shutकरोwn)
		वापस 0;		/* Controller is dead */

	/*
	 * If CF is still set and reset isn't क्रमced
	 * then we मुख्यtained suspend घातer.
	 * Just unकरो the effect of ehci_suspend().
	 */
	अगर (ehci_पढ़ोl(ehci, &ehci->regs->configured_flag) == FLAG_CF &&
			!क्रमce_reset) अणु
		पूर्णांक	mask = INTR_MASK;

		ehci_prepare_ports_क्रम_controller_resume(ehci);

		spin_lock_irq(&ehci->lock);
		अगर (ehci->shutकरोwn)
			जाओ skip;

		अगर (!hcd->self.root_hub->करो_remote_wakeup)
			mask &= ~STS_PCD;
		ehci_ग_लिखोl(ehci, mask, &ehci->regs->पूर्णांकr_enable);
		ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable);
 skip:
		spin_unlock_irq(&ehci->lock);
		वापस 0;
	पूर्ण

	/*
	 * Else reset, to cope with घातer loss or resume from hibernation
	 * having let the firmware kick in during reboot.
	 */
	usb_root_hub_lost_घातer(hcd->self.root_hub);
	(व्योम) ehci_halt(ehci);
	(व्योम) ehci_reset(ehci);

	spin_lock_irq(&ehci->lock);
	अगर (ehci->shutकरोwn)
		जाओ skip;

	ehci_ग_लिखोl(ehci, ehci->command, &ehci->regs->command);
	ehci_ग_लिखोl(ehci, FLAG_CF, &ehci->regs->configured_flag);
	ehci_पढ़ोl(ehci, &ehci->regs->command);	/* unblock posted ग_लिखोs */

	ehci->rh_state = EHCI_RH_SUSPENDED;
	spin_unlock_irq(&ehci->lock);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ehci_resume);

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/*
 * Generic काष्ठाure: This माला_लो copied क्रम platक्रमm drivers so that
 * inभागidual entries can be overridden as needed.
 */

अटल स्थिर काष्ठा hc_driver ehci_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"EHCI Host Controller",
	.hcd_priv_size =	माप(काष्ठा ehci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ehci_irq,
	.flags =		HCD_MEMORY | HCD_DMA | HCD_USB2 | HCD_BH,

	/*
	 * basic lअगरecycle operations
	 */
	.reset =		ehci_setup,
	.start =		ehci_run,
	.stop =			ehci_stop,
	.shutकरोwn =		ehci_shutकरोwn,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ehci_urb_enqueue,
	.urb_dequeue =		ehci_urb_dequeue,
	.endpoपूर्णांक_disable =	ehci_endpoपूर्णांक_disable,
	.endpoपूर्णांक_reset =	ehci_endpoपूर्णांक_reset,
	.clear_tt_buffer_complete =	ehci_clear_tt_buffer_complete,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ehci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	ehci_hub_status_data,
	.hub_control =		ehci_hub_control,
	.bus_suspend =		ehci_bus_suspend,
	.bus_resume =		ehci_bus_resume,
	.relinquish_port =	ehci_relinquish_port,
	.port_handed_over =	ehci_port_handed_over,
	.get_resuming_ports =	ehci_get_resuming_ports,

	/*
	 * device support
	 */
	.मुक्त_dev =		ehci_हटाओ_device,
पूर्ण;

व्योम ehci_init_driver(काष्ठा hc_driver *drv,
		स्थिर काष्ठा ehci_driver_overrides *over)
अणु
	/* Copy the generic table to drv and then apply the overrides */
	*drv = ehci_hc_driver;

	अगर (over) अणु
		drv->hcd_priv_size += over->extra_priv_size;
		अगर (over->reset)
			drv->reset = over->reset;
		अगर (over->port_घातer)
			drv->port_घातer = over->port_घातer;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ehci_init_driver);

/*-------------------------------------------------------------------------*/

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR (DRIVER_AUTHOR);
MODULE_LICENSE ("GPL");

#अगर_घोषित CONFIG_USB_EHCI_SH
#समावेश "ehci-sh.c"
#घोषणा PLATFORM_DRIVER		ehci_hcd_sh_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PS3
#समावेश "ehci-ps3.c"
#घोषणा	PS3_SYSTEM_BUS_DRIVER	ps3_ehci_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_EHCI_HCD_PPC_OF
#समावेश "ehci-ppc-of.c"
#घोषणा OF_PLATFORM_DRIVER	ehci_hcd_ppc_of_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_XPS_USB_HCD_XILINX
#समावेश "ehci-xilinx-of.c"
#घोषणा XILINX_OF_PLATFORM_DRIVER	ehci_hcd_xilinx_of_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_EHCI_HCD_PMC_MSP
#समावेश "ehci-pmcmsp.c"
#घोषणा	PLATFORM_DRIVER		ehci_hcd_msp_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARC_LEON
#समावेश "ehci-grlib.c"
#घोषणा PLATFORM_DRIVER		ehci_grlib_driver
#पूर्ण_अगर

अटल पूर्णांक __init ehci_hcd_init(व्योम)
अणु
	पूर्णांक retval = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "%s: " DRIVER_DESC "\n", hcd_name);
	set_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
	अगर (test_bit(USB_UHCI_LOADED, &usb_hcds_loaded) ||
			test_bit(USB_OHCI_LOADED, &usb_hcds_loaded))
		prपूर्णांकk(KERN_WARNING "Warning! ehci_hcd should always be loaded"
				" before uhci_hcd and ohci_hcd, not after\n");

	pr_debug("%s: block sizes: qh %zd qtd %zd itd %zd sitd %zd\n",
		 hcd_name,
		 माप(काष्ठा ehci_qh), माप(काष्ठा ehci_qtd),
		 माप(काष्ठा ehci_itd), माप(काष्ठा ehci_sitd));

#अगर_घोषित CONFIG_DYNAMIC_DEBUG
	ehci_debug_root = debugfs_create_dir("ehci", usb_debug_root);
#पूर्ण_अगर

#अगर_घोषित PLATFORM_DRIVER
	retval = platक्रमm_driver_रेजिस्टर(&PLATFORM_DRIVER);
	अगर (retval < 0)
		जाओ clean0;
#पूर्ण_अगर

#अगर_घोषित PS3_SYSTEM_BUS_DRIVER
	retval = ps3_ehci_driver_रेजिस्टर(&PS3_SYSTEM_BUS_DRIVER);
	अगर (retval < 0)
		जाओ clean2;
#पूर्ण_अगर

#अगर_घोषित OF_PLATFORM_DRIVER
	retval = platक्रमm_driver_रेजिस्टर(&OF_PLATFORM_DRIVER);
	अगर (retval < 0)
		जाओ clean3;
#पूर्ण_अगर

#अगर_घोषित XILINX_OF_PLATFORM_DRIVER
	retval = platक्रमm_driver_रेजिस्टर(&XILINX_OF_PLATFORM_DRIVER);
	अगर (retval < 0)
		जाओ clean4;
#पूर्ण_अगर
	वापस retval;

#अगर_घोषित XILINX_OF_PLATFORM_DRIVER
	/* platक्रमm_driver_unरेजिस्टर(&XILINX_OF_PLATFORM_DRIVER); */
clean4:
#पूर्ण_अगर
#अगर_घोषित OF_PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&OF_PLATFORM_DRIVER);
clean3:
#पूर्ण_अगर
#अगर_घोषित PS3_SYSTEM_BUS_DRIVER
	ps3_ehci_driver_unरेजिस्टर(&PS3_SYSTEM_BUS_DRIVER);
clean2:
#पूर्ण_अगर
#अगर_घोषित PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&PLATFORM_DRIVER);
clean0:
#पूर्ण_अगर
#अगर_घोषित CONFIG_DYNAMIC_DEBUG
	debugfs_हटाओ(ehci_debug_root);
	ehci_debug_root = शून्य;
#पूर्ण_अगर
	clear_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
	वापस retval;
पूर्ण
module_init(ehci_hcd_init);

अटल व्योम __निकास ehci_hcd_cleanup(व्योम)
अणु
#अगर_घोषित XILINX_OF_PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&XILINX_OF_PLATFORM_DRIVER);
#पूर्ण_अगर
#अगर_घोषित OF_PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&OF_PLATFORM_DRIVER);
#पूर्ण_अगर
#अगर_घोषित PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&PLATFORM_DRIVER);
#पूर्ण_अगर
#अगर_घोषित PS3_SYSTEM_BUS_DRIVER
	ps3_ehci_driver_unरेजिस्टर(&PS3_SYSTEM_BUS_DRIVER);
#पूर्ण_अगर
#अगर_घोषित CONFIG_DYNAMIC_DEBUG
	debugfs_हटाओ(ehci_debug_root);
#पूर्ण_अगर
	clear_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
पूर्ण
module_निकास(ehci_hcd_cleanup);
