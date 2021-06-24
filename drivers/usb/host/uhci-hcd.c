<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Universal Host Controller Interface driver क्रम USB.
 *
 * Maपूर्णांकainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * (C) Copyright 1999 Linus Torvalds
 * (C) Copyright 1999-2002 Johannes Erdfelt, johannes@erdfelt.com
 * (C) Copyright 1999 Randy Dunlap
 * (C) Copyright 1999 Georg Acher, acher@in.tum.de
 * (C) Copyright 1999 Deti Fliegl, deti@fliegl.de
 * (C) Copyright 1999 Thomas Sailer, sailer@अगरe.ee.ethz.ch
 * (C) Copyright 1999 Roman Weissgaerber, weissg@vienna.at
 * (C) Copyright 2000 Yggdrasil Computing, Inc. (port of new PCI पूर्णांकerface
 *               support from usb-ohci.c by Adam Richter, adam@yggdrasil.com).
 * (C) Copyright 1999 Gregory P. Smith (from usb-ohci.c)
 * (C) Copyright 2004-2007 Alan Stern, stern@rowland.harvard.edu
 *
 * Intel करोcuments this fairly well, and as far as I know there
 * are no royalties or anything like that, but even so there are
 * people who decided that they want to करो the same thing in a
 * completely dअगरferent way.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/pm.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dmi.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश "uhci-hcd.h"

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_AUTHOR							\
	"Linus 'Frodo Rabbit' Torvalds, Johannes Erdfelt, "		\
	"Randy Dunlap, Georg Acher, Deti Fliegl, Thomas Sailer, "	\
	"Roman Weissgaerber, Alan Stern"
#घोषणा DRIVER_DESC "USB Universal Host Controller Interface driver"

/* क्रम flakey hardware, ignore overcurrent indicators */
अटल bool ignore_oc;
module_param(ignore_oc, bool, S_IRUGO);
MODULE_PARM_DESC(ignore_oc, "ignore hardware overcurrent indications");

/*
 * debug = 0, no debugging messages
 * debug = 1, dump failed URBs except क्रम stalls
 * debug = 2, dump all failed URBs (including stalls)
 *            show all queues in /sys/kernel/debug/uhci/[pci_addr]
 * debug = 3, show all TDs in URBs when dumping
 */
#अगर_घोषित CONFIG_DYNAMIC_DEBUG

अटल पूर्णांक debug = 1;
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level");
अटल अक्षर *errbuf;

#अन्यथा

#घोषणा debug 0
#घोषणा errbuf शून्य

#पूर्ण_अगर


#घोषणा ERRBUF_LEN    (32 * 1024)

अटल काष्ठा kmem_cache *uhci_up_cachep;	/* urb_priv */

अटल व्योम suspend_rh(काष्ठा uhci_hcd *uhci, क्रमागत uhci_rh_state new_state);
अटल व्योम wakeup_rh(काष्ठा uhci_hcd *uhci);
अटल व्योम uhci_get_current_frame_number(काष्ठा uhci_hcd *uhci);

/*
 * Calculate the link poपूर्णांकer DMA value क्रम the first Skeleton QH in a frame.
 */
अटल __hc32 uhci_frame_skel_link(काष्ठा uhci_hcd *uhci, पूर्णांक frame)
अणु
	पूर्णांक skelnum;

	/*
	 * The पूर्णांकerrupt queues will be पूर्णांकerleaved as evenly as possible.
	 * There's not much to be करोne about period-1 पूर्णांकerrupts; they have
	 * to occur in every frame.  But we can schedule period-2 पूर्णांकerrupts
	 * in odd-numbered frames, period-4 पूर्णांकerrupts in frames congruent
	 * to 2 (mod 4), and so on.  This way each frame only has two
	 * पूर्णांकerrupt QHs, which will help spपढ़ो out bandwidth utilization.
	 *
	 * ffs (Find First bit Set) करोes exactly what we need:
	 * 1,3,5,...  => ffs = 0 => use period-2 QH = skelqh[8],
	 * 2,6,10,... => ffs = 1 => use period-4 QH = skelqh[7], etc.
	 * ffs >= 7 => not on any high-period queue, so use
	 *	period-1 QH = skelqh[9].
	 * Add in UHCI_NUMFRAMES to insure at least one bit is set.
	 */
	skelnum = 8 - (पूर्णांक) __ffs(frame | UHCI_NUMFRAMES);
	अगर (skelnum <= 1)
		skelnum = 9;
	वापस LINK_TO_QH(uhci, uhci->skelqh[skelnum]);
पूर्ण

#समावेश "uhci-debug.c"
#समावेश "uhci-q.c"
#समावेश "uhci-hub.c"

/*
 * Finish up a host controller reset and update the recorded state.
 */
अटल व्योम finish_reset(काष्ठा uhci_hcd *uhci)
अणु
	पूर्णांक port;

	/* HCRESET करोesn't affect the Suspend, Reset, and Resume Detect
	 * bits in the port status and control रेजिस्टरs.
	 * We have to clear them by hand.
	 */
	क्रम (port = 0; port < uhci->rh_numports; ++port)
		uhci_ग_लिखोw(uhci, 0, USBPORTSC1 + (port * 2));

	uhci->port_c_suspend = uhci->resuming_ports = 0;
	uhci->rh_state = UHCI_RH_RESET;
	uhci->is_stopped = UHCI_IS_STOPPED;
	clear_bit(HCD_FLAG_POLL_RH, &uhci_to_hcd(uhci)->flags);
पूर्ण

/*
 * Last rites क्रम a defunct/nonfunctional controller
 * or one we करोn't want to use any more.
 */
अटल व्योम uhci_hc_died(काष्ठा uhci_hcd *uhci)
अणु
	uhci_get_current_frame_number(uhci);
	uhci->reset_hc(uhci);
	finish_reset(uhci);
	uhci->dead = 1;

	/* The current frame may alपढ़ोy be partway finished */
	++uhci->frame_number;
पूर्ण

/*
 * Initialize a controller that was newly discovered or has lost घातer
 * or otherwise been reset जबतक it was suspended.  In none of these हालs
 * can we be sure of its previous state.
 */
अटल व्योम check_and_reset_hc(काष्ठा uhci_hcd *uhci)
अणु
	अगर (uhci->check_and_reset_hc(uhci))
		finish_reset(uhci);
पूर्ण

#अगर defined(CONFIG_USB_UHCI_SUPPORT_NON_PCI_HC)
/*
 * The two functions below are generic reset functions that are used on प्रणालीs
 * that करो not have keyboard and mouse legacy support. We assume that we are
 * running on such a प्रणाली अगर CONFIG_USB_UHCI_SUPPORT_NON_PCI_HC is defined.
 */

/*
 * Make sure the controller is completely inactive, unable to
 * generate पूर्णांकerrupts or करो DMA.
 */
अटल व्योम uhci_generic_reset_hc(काष्ठा uhci_hcd *uhci)
अणु
	/* Reset the HC - this will क्रमce us to get a
	 * new notअगरication of any alपढ़ोy connected
	 * ports due to the भव disconnect that it
	 * implies.
	 */
	uhci_ग_लिखोw(uhci, USBCMD_HCRESET, USBCMD);
	mb();
	udelay(5);
	अगर (uhci_पढ़ोw(uhci, USBCMD) & USBCMD_HCRESET)
		dev_warn(uhci_dev(uhci), "HCRESET not completed yet!\n");

	/* Just to be safe, disable पूर्णांकerrupt requests and
	 * make sure the controller is stopped.
	 */
	uhci_ग_लिखोw(uhci, 0, USBINTR);
	uhci_ग_लिखोw(uhci, 0, USBCMD);
पूर्ण

/*
 * Initialize a controller that was newly discovered or has just been
 * resumed.  In either हाल we can't be sure of its previous state.
 *
 * Returns: 1 अगर the controller was reset, 0 otherwise.
 */
अटल पूर्णांक uhci_generic_check_and_reset_hc(काष्ठा uhci_hcd *uhci)
अणु
	अचिन्हित पूर्णांक cmd, पूर्णांकr;

	/*
	 * When restarting a suspended controller, we expect all the
	 * settings to be the same as we left them:
	 *
	 *	Controller is stopped and configured with EGSM set;
	 *	No पूर्णांकerrupts enabled except possibly Resume Detect.
	 *
	 * If any of these conditions are violated we करो a complete reset.
	 */

	cmd = uhci_पढ़ोw(uhci, USBCMD);
	अगर ((cmd & USBCMD_RS) || !(cmd & USBCMD_CF) || !(cmd & USBCMD_EGSM)) अणु
		dev_dbg(uhci_dev(uhci), "%s: cmd = 0x%04x\n",
				__func__, cmd);
		जाओ reset_needed;
	पूर्ण

	पूर्णांकr = uhci_पढ़ोw(uhci, USBINTR);
	अगर (पूर्णांकr & (~USBINTR_RESUME)) अणु
		dev_dbg(uhci_dev(uhci), "%s: intr = 0x%04x\n",
				__func__, पूर्णांकr);
		जाओ reset_needed;
	पूर्ण
	वापस 0;

reset_needed:
	dev_dbg(uhci_dev(uhci), "Performing full reset\n");
	uhci_generic_reset_hc(uhci);
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_USB_UHCI_SUPPORT_NON_PCI_HC */

/*
 * Store the basic रेजिस्टर settings needed by the controller.
 */
अटल व्योम configure_hc(काष्ठा uhci_hcd *uhci)
अणु
	/* Set the frame length to the शेष: 1 ms exactly */
	uhci_ग_लिखोb(uhci, USBSOF_DEFAULT, USBSOF);

	/* Store the frame list base address */
	uhci_ग_लिखोl(uhci, uhci->frame_dma_handle, USBFLBASEADD);

	/* Set the current frame number */
	uhci_ग_लिखोw(uhci, uhci->frame_number & UHCI_MAX_SOF_NUMBER,
			USBFRNUM);

	/* perक्रमm any arch/bus specअगरic configuration */
	अगर (uhci->configure_hc)
		uhci->configure_hc(uhci);
पूर्ण

अटल पूर्णांक resume_detect_पूर्णांकerrupts_are_broken(काष्ठा uhci_hcd *uhci)
अणु
	/*
	 * If we have to ignore overcurrent events then almost by definition
	 * we can't depend on resume-detect पूर्णांकerrupts.
	 *
	 * Those पूर्णांकerrupts also करोn't seem to work on ASpeed SoCs.
	 */
	अगर (ignore_oc || uhci_is_aspeed(uhci))
		वापस 1;

	वापस uhci->resume_detect_पूर्णांकerrupts_are_broken ?
		uhci->resume_detect_पूर्णांकerrupts_are_broken(uhci) : 0;
पूर्ण

अटल पूर्णांक global_suspend_mode_is_broken(काष्ठा uhci_hcd *uhci)
अणु
	वापस uhci->global_suspend_mode_is_broken ?
		uhci->global_suspend_mode_is_broken(uhci) : 0;
पूर्ण

अटल व्योम suspend_rh(काष्ठा uhci_hcd *uhci, क्रमागत uhci_rh_state new_state)
__releases(uhci->lock)
__acquires(uhci->lock)
अणु
	पूर्णांक स्वतः_stop;
	पूर्णांक पूर्णांक_enable, egsm_enable, wakeup_enable;
	काष्ठा usb_device *rhdev = uhci_to_hcd(uhci)->self.root_hub;

	स्वतः_stop = (new_state == UHCI_RH_AUTO_STOPPED);
	dev_dbg(&rhdev->dev, "%s%s\n", __func__,
			(स्वतः_stop ? " (auto-stop)" : ""));

	/* Start off by assuming Resume-Detect पूर्णांकerrupts and EGSM work
	 * and that remote wakeups should be enabled.
	 */
	egsm_enable = USBCMD_EGSM;
	पूर्णांक_enable = USBINTR_RESUME;
	wakeup_enable = 1;

	/*
	 * In स्वतः-stop mode, we must be able to detect new connections.
	 * The user can क्रमce us to poll by disabling remote wakeup;
	 * otherwise we will use the EGSM/RD mechanism.
	 */
	अगर (स्वतः_stop) अणु
		अगर (!device_may_wakeup(&rhdev->dev))
			egsm_enable = पूर्णांक_enable = 0;
	पूर्ण

#अगर_घोषित CONFIG_PM
	/*
	 * In bus-suspend mode, we use the wakeup setting specअगरied
	 * क्रम the root hub.
	 */
	अन्यथा अणु
		अगर (!rhdev->करो_remote_wakeup)
			wakeup_enable = 0;
	पूर्ण
#पूर्ण_अगर

	/*
	 * UHCI करोesn't distinguish between wakeup requests from करोwnstream
	 * devices and local connect/disconnect events.  There's no way to
	 * enable one without the other; both are controlled by EGSM.  Thus
	 * अगर wakeups are disallowed then EGSM must be turned off -- in which
	 * हाल remote wakeup requests from करोwnstream during प्रणाली sleep
	 * will be lost.
	 *
	 * In addition, अगर EGSM is broken then we can't use it.  Likewise,
	 * अगर Resume-Detect पूर्णांकerrupts are broken then we can't use them.
	 *
	 * Finally, neither EGSM nor RD is useful by itself.  Without EGSM,
	 * the RD status bit will never get set.  Without RD, the controller
	 * won't generate पूर्णांकerrupts to tell the प्रणाली about wakeup events.
	 */
	अगर (!wakeup_enable || global_suspend_mode_is_broken(uhci) ||
			resume_detect_पूर्णांकerrupts_are_broken(uhci))
		egsm_enable = पूर्णांक_enable = 0;

	uhci->RD_enable = !!पूर्णांक_enable;
	uhci_ग_लिखोw(uhci, पूर्णांक_enable, USBINTR);
	uhci_ग_लिखोw(uhci, egsm_enable | USBCMD_CF, USBCMD);
	mb();
	udelay(5);

	/* If we're स्वतः-stopping then no devices have been attached
	 * क्रम a जबतक, so there shouldn't be any active URBs and the
	 * controller should stop after a few microseconds.  Otherwise
	 * we will give the controller one frame to stop.
	 */
	अगर (!स्वतः_stop && !(uhci_पढ़ोw(uhci, USBSTS) & USBSTS_HCH)) अणु
		uhci->rh_state = UHCI_RH_SUSPENDING;
		spin_unlock_irq(&uhci->lock);
		msleep(1);
		spin_lock_irq(&uhci->lock);
		अगर (uhci->dead)
			वापस;
	पूर्ण
	अगर (!(uhci_पढ़ोw(uhci, USBSTS) & USBSTS_HCH))
		dev_warn(uhci_dev(uhci), "Controller not stopped yet!\n");

	uhci_get_current_frame_number(uhci);

	uhci->rh_state = new_state;
	uhci->is_stopped = UHCI_IS_STOPPED;

	/*
	 * If remote wakeup is enabled but either EGSM or RD पूर्णांकerrupts
	 * करोesn't work, then we won't get an पूर्णांकerrupt when a wakeup event
	 * occurs.  Thus the suspended root hub needs to be polled.
	 */
	अगर (wakeup_enable && (!पूर्णांक_enable || !egsm_enable))
		set_bit(HCD_FLAG_POLL_RH, &uhci_to_hcd(uhci)->flags);
	अन्यथा
		clear_bit(HCD_FLAG_POLL_RH, &uhci_to_hcd(uhci)->flags);

	uhci_scan_schedule(uhci);
	uhci_fsbr_off(uhci);
पूर्ण

अटल व्योम start_rh(काष्ठा uhci_hcd *uhci)
अणु
	uhci->is_stopped = 0;

	/*
	 * Clear stale status bits on Aspeed as we get a stale HCH
	 * which causes problems later on
	 */
	अगर (uhci_is_aspeed(uhci))
		uhci_ग_लिखोw(uhci, uhci_पढ़ोw(uhci, USBSTS), USBSTS);

	/* Mark it configured and running with a 64-byte max packet.
	 * All पूर्णांकerrupts are enabled, even though RESUME won't करो anything.
	 */
	uhci_ग_लिखोw(uhci, USBCMD_RS | USBCMD_CF | USBCMD_MAXP, USBCMD);
	uhci_ग_लिखोw(uhci, USBINTR_TIMEOUT | USBINTR_RESUME |
		USBINTR_IOC | USBINTR_SP, USBINTR);
	mb();
	uhci->rh_state = UHCI_RH_RUNNING;
	set_bit(HCD_FLAG_POLL_RH, &uhci_to_hcd(uhci)->flags);
पूर्ण

अटल व्योम wakeup_rh(काष्ठा uhci_hcd *uhci)
__releases(uhci->lock)
__acquires(uhci->lock)
अणु
	dev_dbg(&uhci_to_hcd(uhci)->self.root_hub->dev,
			"%s%s\n", __func__,
			uhci->rh_state == UHCI_RH_AUTO_STOPPED ?
				" (auto-start)" : "");

	/* If we are स्वतः-stopped then no devices are attached so there's
	 * no need क्रम wakeup संकेतs.  Otherwise we send Global Resume
	 * क्रम 20 ms.
	 */
	अगर (uhci->rh_state == UHCI_RH_SUSPENDED) अणु
		अचिन्हित egsm;

		/* Keep EGSM on अगर it was set beक्रमe */
		egsm = uhci_पढ़ोw(uhci, USBCMD) & USBCMD_EGSM;
		uhci->rh_state = UHCI_RH_RESUMING;
		uhci_ग_लिखोw(uhci, USBCMD_FGR | USBCMD_CF | egsm, USBCMD);
		spin_unlock_irq(&uhci->lock);
		msleep(20);
		spin_lock_irq(&uhci->lock);
		अगर (uhci->dead)
			वापस;

		/* End Global Resume and रुको क्रम EOP to be sent */
		uhci_ग_लिखोw(uhci, USBCMD_CF, USBCMD);
		mb();
		udelay(4);
		अगर (uhci_पढ़ोw(uhci, USBCMD) & USBCMD_FGR)
			dev_warn(uhci_dev(uhci), "FGR not stopped yet!\n");
	पूर्ण

	start_rh(uhci);

	/* Restart root hub polling */
	mod_समयr(&uhci_to_hcd(uhci)->rh_समयr, jअगरfies);
पूर्ण

अटल irqवापस_t uhci_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	अचिन्हित लघु status;

	/*
	 * Read the पूर्णांकerrupt status, and ग_लिखो it back to clear the
	 * पूर्णांकerrupt cause.  Contrary to the UHCI specअगरication, the
	 * "HC Halted" status bit is persistent: it is RO, not R/WC.
	 */
	status = uhci_पढ़ोw(uhci, USBSTS);
	अगर (!(status & ~USBSTS_HCH))	/* shared पूर्णांकerrupt, not mine */
		वापस IRQ_NONE;
	uhci_ग_लिखोw(uhci, status, USBSTS);		/* Clear it */

	spin_lock(&uhci->lock);
	अगर (unlikely(!uhci->is_initialized))	/* not yet configured */
		जाओ करोne;

	अगर (status & ~(USBSTS_USBINT | USBSTS_ERROR | USBSTS_RD)) अणु
		अगर (status & USBSTS_HSE)
			dev_err(uhci_dev(uhci),
				"host system error, PCI problems?\n");
		अगर (status & USBSTS_HCPE)
			dev_err(uhci_dev(uhci),
				"host controller process error, something bad happened!\n");
		अगर (status & USBSTS_HCH) अणु
			अगर (uhci->rh_state >= UHCI_RH_RUNNING) अणु
				dev_err(uhci_dev(uhci),
					"host controller halted, very bad!\n");
				अगर (debug > 1 && errbuf) अणु
					/* Prपूर्णांक the schedule क्रम debugging */
					uhci_sprपूर्णांक_schedule(uhci, errbuf,
						ERRBUF_LEN - EXTRA_SPACE);
					lprपूर्णांकk(errbuf);
				पूर्ण
				uhci_hc_died(uhci);
				usb_hc_died(hcd);

				/* Force a callback in हाल there are
				 * pending unlinks */
				mod_समयr(&hcd->rh_समयr, jअगरfies);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (status & USBSTS_RD) अणु
		spin_unlock(&uhci->lock);
		usb_hcd_poll_rh_status(hcd);
	पूर्ण अन्यथा अणु
		uhci_scan_schedule(uhci);
 करोne:
		spin_unlock(&uhci->lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Store the current frame number in uhci->frame_number अगर the controller
 * is running.  Expand from 11 bits (of which we use only 10) to a
 * full-sized पूर्णांकeger.
 *
 * Like many other parts of the driver, this code relies on being polled
 * more than once per second as दीर्घ as the controller is running.
 */
अटल व्योम uhci_get_current_frame_number(काष्ठा uhci_hcd *uhci)
अणु
	अगर (!uhci->is_stopped) अणु
		अचिन्हित delta;

		delta = (uhci_पढ़ोw(uhci, USBFRNUM) - uhci->frame_number) &
				(UHCI_NUMFRAMES - 1);
		uhci->frame_number += delta;
	पूर्ण
पूर्ण

/*
 * De-allocate all resources
 */
अटल व्योम release_uhci(काष्ठा uhci_hcd *uhci)
अणु
	पूर्णांक i;


	spin_lock_irq(&uhci->lock);
	uhci->is_initialized = 0;
	spin_unlock_irq(&uhci->lock);

	debugfs_हटाओ(debugfs_lookup(uhci_to_hcd(uhci)->self.bus_name,
				      uhci_debugfs_root));

	क्रम (i = 0; i < UHCI_NUM_SKELQH; i++)
		uhci_मुक्त_qh(uhci, uhci->skelqh[i]);

	uhci_मुक्त_td(uhci, uhci->term_td);

	dma_pool_destroy(uhci->qh_pool);

	dma_pool_destroy(uhci->td_pool);

	kमुक्त(uhci->frame_cpu);

	dma_मुक्त_coherent(uhci_dev(uhci),
			UHCI_NUMFRAMES * माप(*uhci->frame),
			uhci->frame, uhci->frame_dma_handle);
पूर्ण

/*
 * Allocate a frame list, and then setup the skeleton
 *
 * The hardware करोesn't really know any dअगरference
 * in the queues, but the order करोes matter क्रम the
 * protocols higher up.  The order in which the queues
 * are encountered by the hardware is:
 *
 *  - All isochronous events are handled beक्रमe any
 *    of the queues. We करोn't करो that here, because
 *    we'll create the actual TD entries on demand.
 *  - The first queue is the high-period पूर्णांकerrupt queue.
 *  - The second queue is the period-1 पूर्णांकerrupt and async
 *    (low-speed control, full-speed control, then bulk) queue.
 *  - The third queue is the terminating bandwidth reclamation queue,
 *    which contains no members, loops back to itself, and is present
 *    only when FSBR is on and there are no full-speed control or bulk QHs.
 */
अटल पूर्णांक uhci_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	पूर्णांक retval = -EBUSY;
	पूर्णांक i;

	hcd->uses_new_polling = 1;
	/* Accept arbitrarily दीर्घ scatter-gather lists */
	अगर (!hcd->localmem_pool)
		hcd->self.sg_tablesize = ~0;

	spin_lock_init(&uhci->lock);
	समयr_setup(&uhci->fsbr_समयr, uhci_fsbr_समयout, 0);
	INIT_LIST_HEAD(&uhci->idle_qh_list);
	init_रुकोqueue_head(&uhci->रुकोqh);

#अगर_घोषित UHCI_DEBUG_OPS
	debugfs_create_file(hcd->self.bus_name, S_IFREG|S_IRUGO|S_IWUSR,
			    uhci_debugfs_root, uhci, &uhci_debug_operations);
#पूर्ण_अगर

	uhci->frame = dma_alloc_coherent(uhci_dev(uhci),
					 UHCI_NUMFRAMES * माप(*uhci->frame),
					 &uhci->frame_dma_handle, GFP_KERNEL);
	अगर (!uhci->frame) अणु
		dev_err(uhci_dev(uhci),
			"unable to allocate consistent memory for frame list\n");
		जाओ err_alloc_frame;
	पूर्ण

	uhci->frame_cpu = kसुस्मृति(UHCI_NUMFRAMES, माप(*uhci->frame_cpu),
			GFP_KERNEL);
	अगर (!uhci->frame_cpu)
		जाओ err_alloc_frame_cpu;

	uhci->td_pool = dma_pool_create("uhci_td", uhci_dev(uhci),
			माप(काष्ठा uhci_td), 16, 0);
	अगर (!uhci->td_pool) अणु
		dev_err(uhci_dev(uhci), "unable to create td dma_pool\n");
		जाओ err_create_td_pool;
	पूर्ण

	uhci->qh_pool = dma_pool_create("uhci_qh", uhci_dev(uhci),
			माप(काष्ठा uhci_qh), 16, 0);
	अगर (!uhci->qh_pool) अणु
		dev_err(uhci_dev(uhci), "unable to create qh dma_pool\n");
		जाओ err_create_qh_pool;
	पूर्ण

	uhci->term_td = uhci_alloc_td(uhci);
	अगर (!uhci->term_td) अणु
		dev_err(uhci_dev(uhci), "unable to allocate terminating TD\n");
		जाओ err_alloc_term_td;
	पूर्ण

	क्रम (i = 0; i < UHCI_NUM_SKELQH; i++) अणु
		uhci->skelqh[i] = uhci_alloc_qh(uhci, शून्य, शून्य);
		अगर (!uhci->skelqh[i]) अणु
			dev_err(uhci_dev(uhci), "unable to allocate QH\n");
			जाओ err_alloc_skelqh;
		पूर्ण
	पूर्ण

	/*
	 * 8 Interrupt queues; link all higher पूर्णांक queues to पूर्णांक1 = async
	 */
	क्रम (i = SKEL_ISO + 1; i < SKEL_ASYNC; ++i)
		uhci->skelqh[i]->link = LINK_TO_QH(uhci, uhci->skel_async_qh);
	uhci->skel_async_qh->link = UHCI_PTR_TERM(uhci);
	uhci->skel_term_qh->link = LINK_TO_QH(uhci, uhci->skel_term_qh);

	/* This dummy TD is to work around a bug in Intel PIIX controllers */
	uhci_fill_td(uhci, uhci->term_td, 0, uhci_explen(0) |
			(0x7f << TD_TOKEN_DEVADDR_SHIFT) | USB_PID_IN, 0);
	uhci->term_td->link = UHCI_PTR_TERM(uhci);
	uhci->skel_async_qh->element = uhci->skel_term_qh->element =
		LINK_TO_TD(uhci, uhci->term_td);

	/*
	 * Fill the frame list: make all entries poपूर्णांक to the proper
	 * पूर्णांकerrupt queue.
	 */
	क्रम (i = 0; i < UHCI_NUMFRAMES; i++) अणु

		/* Only place we करोn't use the frame list routines */
		uhci->frame[i] = uhci_frame_skel_link(uhci, i);
	पूर्ण

	/*
	 * Some architectures require a full mb() to enक्रमce completion of
	 * the memory ग_लिखोs above beक्रमe the I/O transfers in configure_hc().
	 */
	mb();

	spin_lock_irq(&uhci->lock);
	configure_hc(uhci);
	uhci->is_initialized = 1;
	start_rh(uhci);
	spin_unlock_irq(&uhci->lock);
	वापस 0;

/*
 * error निकासs:
 */
err_alloc_skelqh:
	क्रम (i = 0; i < UHCI_NUM_SKELQH; i++) अणु
		अगर (uhci->skelqh[i])
			uhci_मुक्त_qh(uhci, uhci->skelqh[i]);
	पूर्ण

	uhci_मुक्त_td(uhci, uhci->term_td);

err_alloc_term_td:
	dma_pool_destroy(uhci->qh_pool);

err_create_qh_pool:
	dma_pool_destroy(uhci->td_pool);

err_create_td_pool:
	kमुक्त(uhci->frame_cpu);

err_alloc_frame_cpu:
	dma_मुक्त_coherent(uhci_dev(uhci),
			UHCI_NUMFRAMES * माप(*uhci->frame),
			uhci->frame, uhci->frame_dma_handle);

err_alloc_frame:
	debugfs_हटाओ(debugfs_lookup(hcd->self.bus_name, uhci_debugfs_root));

	वापस retval;
पूर्ण

अटल व्योम uhci_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);

	spin_lock_irq(&uhci->lock);
	अगर (HCD_HW_ACCESSIBLE(hcd) && !uhci->dead)
		uhci_hc_died(uhci);
	uhci_scan_schedule(uhci);
	spin_unlock_irq(&uhci->lock);
	synchronize_irq(hcd->irq);

	del_समयr_sync(&uhci->fsbr_समयr);
	release_uhci(uhci);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक uhci_rh_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	पूर्णांक rc = 0;

	spin_lock_irq(&uhci->lock);
	अगर (!HCD_HW_ACCESSIBLE(hcd))
		rc = -ESHUTDOWN;
	अन्यथा अगर (uhci->dead)
		;		/* Dead controllers tell no tales */

	/* Once the controller is stopped, port resumes that are alपढ़ोy
	 * in progress won't complete.  Hence अगर remote wakeup is enabled
	 * क्रम the root hub and any ports are in the middle of a resume or
	 * remote wakeup, we must fail the suspend.
	 */
	अन्यथा अगर (hcd->self.root_hub->करो_remote_wakeup &&
			uhci->resuming_ports) अणु
		dev_dbg(uhci_dev(uhci),
			"suspend failed because a port is resuming\n");
		rc = -EBUSY;
	पूर्ण अन्यथा
		suspend_rh(uhci, UHCI_RH_SUSPENDED);
	spin_unlock_irq(&uhci->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक uhci_rh_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	पूर्णांक rc = 0;

	spin_lock_irq(&uhci->lock);
	अगर (!HCD_HW_ACCESSIBLE(hcd))
		rc = -ESHUTDOWN;
	अन्यथा अगर (!uhci->dead)
		wakeup_rh(uhci);
	spin_unlock_irq(&uhci->lock);
	वापस rc;
पूर्ण

#पूर्ण_अगर

/* Wait until a particular device/endpoपूर्णांक's QH is idle, and मुक्त it */
अटल व्योम uhci_hcd_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	काष्ठा uhci_qh *qh;

	spin_lock_irq(&uhci->lock);
	qh = (काष्ठा uhci_qh *) hep->hcpriv;
	अगर (qh == शून्य)
		जाओ करोne;

	जबतक (qh->state != QH_STATE_IDLE) अणु
		++uhci->num_रुकोing;
		spin_unlock_irq(&uhci->lock);
		रुको_event_पूर्णांकerruptible(uhci->रुकोqh,
				qh->state == QH_STATE_IDLE);
		spin_lock_irq(&uhci->lock);
		--uhci->num_रुकोing;
	पूर्ण

	uhci_मुक्त_qh(uhci, qh);
करोne:
	spin_unlock_irq(&uhci->lock);
पूर्ण

अटल पूर्णांक uhci_hcd_get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	अचिन्हित frame_number;
	अचिन्हित delta;

	/* Minimize latency by aव्योमing the spinlock */
	frame_number = uhci->frame_number;
	barrier();
	delta = (uhci_पढ़ोw(uhci, USBFRNUM) - frame_number) &
			(UHCI_NUMFRAMES - 1);
	वापस frame_number + delta;
पूर्ण

/* Determines number of ports on controller */
अटल पूर्णांक uhci_count_ports(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	अचिन्हित io_size = (अचिन्हित) hcd->rsrc_len;
	पूर्णांक port;

	/* The UHCI spec says devices must have 2 ports, and goes on to say
	 * they may have more but gives no way to determine how many there
	 * are.  However according to the UHCI spec, Bit 7 of the port
	 * status and control रेजिस्टर is always set to 1.  So we try to
	 * use this to our advantage.  Another common failure mode when
	 * a nonexistent रेजिस्टर is addressed is to वापस all ones, so
	 * we test क्रम that also.
	 */
	क्रम (port = 0; port < (io_size - USBPORTSC1) / 2; port++) अणु
		अचिन्हित पूर्णांक portstatus;

		portstatus = uhci_पढ़ोw(uhci, USBPORTSC1 + (port * 2));
		अगर (!(portstatus & 0x0080) || portstatus == 0xffff)
			अवरोध;
	पूर्ण
	अगर (debug)
		dev_info(uhci_dev(uhci), "detected %d ports\n", port);

	/* Anything greater than 7 is weird so we'll ignore it. */
	अगर (port > UHCI_RH_MAXCHILD) अणु
		dev_info(uhci_dev(uhci),
			"port count misdetected? forcing to 2 ports\n");
		port = 2;
	पूर्ण

	वापस port;
पूर्ण

अटल स्थिर अक्षर hcd_name[] = "uhci_hcd";

#अगर_घोषित CONFIG_USB_PCI
#समावेश "uhci-pci.c"
#घोषणा	PCI_DRIVER		uhci_pci_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARC_LEON
#समावेश "uhci-grlib.c"
#घोषणा PLATFORM_DRIVER		uhci_grlib_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_UHCI_PLATFORM
#समावेश "uhci-platform.c"
#घोषणा PLATFORM_DRIVER		uhci_platक्रमm_driver
#पूर्ण_अगर

#अगर !defined(PCI_DRIVER) && !defined(PLATFORM_DRIVER)
#त्रुटि "missing bus glue for uhci-hcd"
#पूर्ण_अगर

अटल पूर्णांक __init uhci_hcd_init(व्योम)
अणु
	पूर्णांक retval = -ENOMEM;

	अगर (usb_disabled())
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "uhci_hcd: " DRIVER_DESC "%s\n",
			ignore_oc ? ", overcurrent ignored" : "");
	set_bit(USB_UHCI_LOADED, &usb_hcds_loaded);

#अगर_घोषित CONFIG_DYNAMIC_DEBUG
	errbuf = kदो_स्मृति(ERRBUF_LEN, GFP_KERNEL);
	अगर (!errbuf)
		जाओ errbuf_failed;
	uhci_debugfs_root = debugfs_create_dir("uhci", usb_debug_root);
#पूर्ण_अगर

	uhci_up_cachep = kmem_cache_create("uhci_urb_priv",
		माप(काष्ठा urb_priv), 0, 0, शून्य);
	अगर (!uhci_up_cachep)
		जाओ up_failed;

#अगर_घोषित PLATFORM_DRIVER
	retval = platक्रमm_driver_रेजिस्टर(&PLATFORM_DRIVER);
	अगर (retval < 0)
		जाओ clean0;
#पूर्ण_अगर

#अगर_घोषित PCI_DRIVER
	retval = pci_रेजिस्टर_driver(&PCI_DRIVER);
	अगर (retval < 0)
		जाओ clean1;
#पूर्ण_अगर

	वापस 0;

#अगर_घोषित PCI_DRIVER
clean1:
#पूर्ण_अगर
#अगर_घोषित PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&PLATFORM_DRIVER);
clean0:
#पूर्ण_अगर
	kmem_cache_destroy(uhci_up_cachep);

up_failed:
#अगर defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
	debugfs_हटाओ(uhci_debugfs_root);

	kमुक्त(errbuf);

errbuf_failed:
#पूर्ण_अगर

	clear_bit(USB_UHCI_LOADED, &usb_hcds_loaded);
	वापस retval;
पूर्ण

अटल व्योम __निकास uhci_hcd_cleanup(व्योम) 
अणु
#अगर_घोषित PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&PLATFORM_DRIVER);
#पूर्ण_अगर
#अगर_घोषित PCI_DRIVER
	pci_unरेजिस्टर_driver(&PCI_DRIVER);
#पूर्ण_अगर
	kmem_cache_destroy(uhci_up_cachep);
	debugfs_हटाओ(uhci_debugfs_root);
#अगर_घोषित CONFIG_DYNAMIC_DEBUG
	kमुक्त(errbuf);
#पूर्ण_अगर
	clear_bit(USB_UHCI_LOADED, &usb_hcds_loaded);
पूर्ण

module_init(uhci_hcd_init);
module_निकास(uhci_hcd_cleanup);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
