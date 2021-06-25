<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Open Host Controller Interface (OHCI) driver क्रम USB.
 *
 * Maपूर्णांकainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2004 David Brownell <dbrownell@users.sourceक्रमge.net>
 *
 * [ Initialisation is based on Linus'  ]
 * [ uhci code and gregs ohci fragments ]
 * [ (C) Copyright 1999 Linus Torvalds  ]
 * [ (C) Copyright 1999 Gregory P. Smith]
 *
 *
 * OHCI is the मुख्य "non-Intel/VIA" standard क्रम USB 1.1 host controller
 * पूर्णांकerfaces (though some non-x86 Intel chips use it).  It supports
 * smarter hardware than UHCI.  A करोwnload link क्रम the spec available
 * through the https://www.usb.org website.
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/genभाग.स>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/byteorder.h>


#घोषणा DRIVER_AUTHOR "Roman Weissgaerber, David Brownell"
#घोषणा DRIVER_DESC "USB 1.1 'Open' Host Controller (OHCI) Driver"

/*-------------------------------------------------------------------------*/

/* For initializing controller (mask in an HCFS mode too) */
#घोषणा	OHCI_CONTROL_INIT	OHCI_CTRL_CBSR
#घोषणा	OHCI_INTR_INIT \
		(OHCI_INTR_MIE | OHCI_INTR_RHSC | OHCI_INTR_UE \
		| OHCI_INTR_RD | OHCI_INTR_WDH)

#अगर_घोषित __hppa__
/* On PA-RISC, PDC can leave IR set incorrectly; ignore it there. */
#घोषणा	IR_DISABLE
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP
/* OMAP करोesn't support IR (no SMM; not needed) */
#घोषणा	IR_DISABLE
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल स्थिर अक्षर	hcd_name [] = "ohci_hcd";

#घोषणा	STATECHANGE_DELAY	msecs_to_jअगरfies(300)
#घोषणा	IO_WATCHDOG_DELAY	msecs_to_jअगरfies(275)
#घोषणा	IO_WATCHDOG_OFF		0xffffff00

#समावेश "ohci.h"
#समावेश "pci-quirks.h"

अटल व्योम ohci_dump(काष्ठा ohci_hcd *ohci);
अटल व्योम ohci_stop(काष्ठा usb_hcd *hcd);
अटल व्योम io_watchकरोg_func(काष्ठा समयr_list *t);

#समावेश "ohci-hub.c"
#समावेश "ohci-dbg.c"
#समावेश "ohci-mem.c"
#समावेश "ohci-q.c"


/*
 * On architectures with edge-triggered पूर्णांकerrupts we must never वापस
 * IRQ_NONE.
 */
#अगर defined(CONFIG_SA1111)  /* ... or other edge-triggered प्रणालीs */
#घोषणा IRQ_NOTMINE	IRQ_HANDLED
#अन्यथा
#घोषणा IRQ_NOTMINE	IRQ_NONE
#पूर्ण_अगर


/* Some boards misreport घातer चयनing/overcurrent */
अटल bool distrust_firmware;
module_param (distrust_firmware, bool, 0);
MODULE_PARM_DESC (distrust_firmware,
	"true to distrust firmware power/overcurrent setup");

/* Some boards leave IR set wrongly, since they fail BIOS/SMM handshakes */
अटल bool no_handshake;
module_param (no_handshake, bool, 0);
MODULE_PARM_DESC (no_handshake, "true (not default) disables BIOS handshake");

/*-------------------------------------------------------------------------*/

अटल पूर्णांक number_of_tds(काष्ठा urb *urb)
अणु
	पूर्णांक			len, i, num, this_sg_len;
	काष्ठा scatterlist	*sg;

	len = urb->transfer_buffer_length;
	i = urb->num_mapped_sgs;

	अगर (len > 0 && i > 0) अणु		/* Scatter-gather transfer */
		num = 0;
		sg = urb->sg;
		क्रम (;;) अणु
			this_sg_len = min_t(पूर्णांक, sg_dma_len(sg), len);
			num += DIV_ROUND_UP(this_sg_len, 4096);
			len -= this_sg_len;
			अगर (--i <= 0 || len <= 0)
				अवरोध;
			sg = sg_next(sg);
		पूर्ण

	पूर्ण अन्यथा अणु			/* Non-SG transfer */
		/* one TD क्रम every 4096 Bytes (could be up to 8K) */
		num = DIV_ROUND_UP(len, 4096);
	पूर्ण
	वापस num;
पूर्ण

/*
 * queue up an urb क्रम anything except the root hub
 */
अटल पूर्णांक ohci_urb_enqueue (
	काष्ठा usb_hcd	*hcd,
	काष्ठा urb	*urb,
	gfp_t		mem_flags
) अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);
	काष्ठा ed	*ed;
	urb_priv_t	*urb_priv;
	अचिन्हित पूर्णांक	pipe = urb->pipe;
	पूर्णांक		i, size = 0;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		retval = 0;

	/* every endpoपूर्णांक has a ed, locate and maybe (re)initialize it */
	ed = ed_get(ohci, urb->ep, urb->dev, pipe, urb->पूर्णांकerval);
	अगर (! ed)
		वापस -ENOMEM;

	/* क्रम the निजी part of the URB we need the number of TDs (size) */
	चयन (ed->type) अणु
		हाल PIPE_CONTROL:
			/* td_submit_urb() करोesn't yet handle these */
			अगर (urb->transfer_buffer_length > 4096)
				वापस -EMSGSIZE;

			/* 1 TD क्रम setup, 1 क्रम ACK, plus ... */
			size = 2;
			fallthrough;
		// हाल PIPE_INTERRUPT:
		// हाल PIPE_BULK:
		शेष:
			size += number_of_tds(urb);
			/* maybe a zero-length packet to wrap it up */
			अगर (size == 0)
				size++;
			अन्यथा अगर ((urb->transfer_flags & URB_ZERO_PACKET) != 0
				&& (urb->transfer_buffer_length
					% usb_maxpacket (urb->dev, pipe,
						usb_pipeout (pipe))) == 0)
				size++;
			अवरोध;
		हाल PIPE_ISOCHRONOUS: /* number of packets from URB */
			size = urb->number_of_packets;
			अवरोध;
	पूर्ण

	/* allocate the निजी part of the URB */
	urb_priv = kzalloc (माप (urb_priv_t) + size * माप (काष्ठा td *),
			mem_flags);
	अगर (!urb_priv)
		वापस -ENOMEM;
	INIT_LIST_HEAD (&urb_priv->pending);
	urb_priv->length = size;
	urb_priv->ed = ed;

	/* allocate the TDs (deferring hash chain updates) */
	क्रम (i = 0; i < size; i++) अणु
		urb_priv->td [i] = td_alloc (ohci, mem_flags);
		अगर (!urb_priv->td [i]) अणु
			urb_priv->length = i;
			urb_मुक्त_priv (ohci, urb_priv);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	spin_lock_irqsave (&ohci->lock, flags);

	/* करोn't submit to a dead HC */
	अगर (!HCD_HW_ACCESSIBLE(hcd)) अणु
		retval = -ENODEV;
		जाओ fail;
	पूर्ण
	अगर (ohci->rh_state != OHCI_RH_RUNNING) अणु
		retval = -ENODEV;
		जाओ fail;
	पूर्ण
	retval = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (retval)
		जाओ fail;

	/* schedule the ed अगर needed */
	अगर (ed->state == ED_IDLE) अणु
		retval = ed_schedule (ohci, ed);
		अगर (retval < 0) अणु
			usb_hcd_unlink_urb_from_ep(hcd, urb);
			जाओ fail;
		पूर्ण

		/* Start up the I/O watchकरोg समयr, अगर it's not running */
		अगर (ohci->prev_frame_no == IO_WATCHDOG_OFF &&
				list_empty(&ohci->eds_in_use) &&
				!(ohci->flags & OHCI_QUIRK_QEMU)) अणु
			ohci->prev_frame_no = ohci_frame_no(ohci);
			mod_समयr(&ohci->io_watchकरोg,
					jअगरfies + IO_WATCHDOG_DELAY);
		पूर्ण
		list_add(&ed->in_use_list, &ohci->eds_in_use);

		अगर (ed->type == PIPE_ISOCHRONOUS) अणु
			u16	frame = ohci_frame_no(ohci);

			/* delay a few frames beक्रमe the first TD */
			frame += max_t (u16, 8, ed->पूर्णांकerval);
			frame &= ~(ed->पूर्णांकerval - 1);
			frame |= ed->branch;
			urb->start_frame = frame;
			ed->last_iso = frame + ed->पूर्णांकerval * (size - 1);
		पूर्ण
	पूर्ण अन्यथा अगर (ed->type == PIPE_ISOCHRONOUS) अणु
		u16	next = ohci_frame_no(ohci) + 1;
		u16	frame = ed->last_iso + ed->पूर्णांकerval;
		u16	length = ed->पूर्णांकerval * (size - 1);

		/* Behind the scheduling threshold? */
		अगर (unlikely(tick_beक्रमe(frame, next))) अणु

			/* URB_ISO_ASAP: Round up to the first available slot */
			अगर (urb->transfer_flags & URB_ISO_ASAP) अणु
				frame += (next - frame + ed->पूर्णांकerval - 1) &
						-ed->पूर्णांकerval;

			/*
			 * Not ASAP: Use the next slot in the stream,
			 * no matter what.
			 */
			पूर्ण अन्यथा अणु
				/*
				 * Some OHCI hardware करोesn't handle late TDs
				 * correctly.  After retiring them it proceeds
				 * to the next ED instead of the next TD.
				 * Thereक्रमe we have to omit the late TDs
				 * entirely.
				 */
				urb_priv->td_cnt = DIV_ROUND_UP(
						(u16) (next - frame),
						ed->पूर्णांकerval);
				अगर (urb_priv->td_cnt >= urb_priv->length) अणु
					++urb_priv->td_cnt;	/* Mark it */
					ohci_dbg(ohci, "iso underrun %p (%u+%u < %u)\n",
							urb, frame, length,
							next);
				पूर्ण
			पूर्ण
		पूर्ण
		urb->start_frame = frame;
		ed->last_iso = frame + length;
	पूर्ण

	/* fill the TDs and link them to the ed; and
	 * enable that part of the schedule, अगर needed
	 * and update count of queued periodic urbs
	 */
	urb->hcpriv = urb_priv;
	td_submit_urb (ohci, urb);

fail:
	अगर (retval)
		urb_मुक्त_priv (ohci, urb_priv);
	spin_unlock_irqrestore (&ohci->lock, flags);
	वापस retval;
पूर्ण

/*
 * decouple the URB from the HC queues (TDs, urb_priv).
 * reporting is always करोne
 * asynchronously, and we might be dealing with an urb that's
 * partially transferred, or an ED with other urbs being unlinked.
 */
अटल पूर्णांक ohci_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci (hcd);
	अचिन्हित दीर्घ		flags;
	पूर्णांक			rc;
	urb_priv_t		*urb_priv;

	spin_lock_irqsave (&ohci->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc == 0) अणु

		/* Unless an IRQ completed the unlink जबतक it was being
		 * handed to us, flag it क्रम unlink and giveback, and क्रमce
		 * some upcoming INTR_SF to call finish_unlinks()
		 */
		urb_priv = urb->hcpriv;
		अगर (urb_priv->ed->state == ED_OPER)
			start_ed_unlink(ohci, urb_priv->ed);

		अगर (ohci->rh_state != OHCI_RH_RUNNING) अणु
			/* With HC dead, we can clean up right away */
			ohci_work(ohci);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore (&ohci->lock, flags);
	वापस rc;
पूर्ण

/*-------------------------------------------------------------------------*/

/* मुक्तs config/altsetting state क्रम endpoपूर्णांकs,
 * including ED memory, dummy TD, and bulk/पूर्णांकr data toggle
 */

अटल व्योम
ohci_endpoपूर्णांक_disable (काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci (hcd);
	अचिन्हित दीर्घ		flags;
	काष्ठा ed		*ed = ep->hcpriv;
	अचिन्हित		limit = 1000;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs क्रम this any more */

	अगर (!ed)
		वापस;

rescan:
	spin_lock_irqsave (&ohci->lock, flags);

	अगर (ohci->rh_state != OHCI_RH_RUNNING) अणु
sanitize:
		ed->state = ED_IDLE;
		ohci_work(ohci);
	पूर्ण

	चयन (ed->state) अणु
	हाल ED_UNLINK:		/* रुको क्रम hw to finish? */
		/* major IRQ delivery trouble loses INTR_SF too... */
		अगर (limit-- == 0) अणु
			ohci_warn(ohci, "ED unlink timeout\n");
			जाओ sanitize;
		पूर्ण
		spin_unlock_irqrestore (&ohci->lock, flags);
		schedule_समयout_unपूर्णांकerruptible(1);
		जाओ rescan;
	हाल ED_IDLE:		/* fully unlinked */
		अगर (list_empty (&ed->td_list)) अणु
			td_मुक्त (ohci, ed->dummy);
			ed_मुक्त (ohci, ed);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  can't recover; must leak ed.
		 */
		ohci_err (ohci, "leak ed %p (#%02x) state %d%s\n",
			ed, ep->desc.bEndpoपूर्णांकAddress, ed->state,
			list_empty (&ed->td_list) ? "" : " (has tds)");
		td_मुक्त (ohci, ed->dummy);
		अवरोध;
	पूर्ण
	ep->hcpriv = शून्य;
	spin_unlock_irqrestore (&ohci->lock, flags);
पूर्ण

अटल पूर्णांक ohci_get_frame (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci (hcd);

	वापस ohci_frame_no(ohci);
पूर्ण

अटल व्योम ohci_usb_reset (काष्ठा ohci_hcd *ohci)
अणु
	ohci->hc_control = ohci_पढ़ोl (ohci, &ohci->regs->control);
	ohci->hc_control &= OHCI_CTRL_RWC;
	ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
	ohci->rh_state = OHCI_RH_HALTED;
पूर्ण

/* ohci_shutकरोwn क्रमcibly disables IRQs and DMA, helping kexec and
 * other हालs where the next software may expect clean state from the
 * "firmware".  this is bus-neutral, unlike shutकरोwn() methods.
 */
अटल व्योम _ohci_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd *ohci;

	ohci = hcd_to_ohci (hcd);
	ohci_ग_लिखोl(ohci, (u32) ~0, &ohci->regs->पूर्णांकrdisable);

	/* Software reset, after which the controller goes पूर्णांकo SUSPEND */
	ohci_ग_लिखोl(ohci, OHCI_HCR, &ohci->regs->cmdstatus);
	ohci_पढ़ोl(ohci, &ohci->regs->cmdstatus);	/* flush the ग_लिखोs */
	udelay(10);

	ohci_ग_लिखोl(ohci, ohci->fmपूर्णांकerval, &ohci->regs->fmपूर्णांकerval);
	ohci->rh_state = OHCI_RH_HALTED;
पूर्ण

अटल व्योम ohci_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ohci->lock, flags);
	_ohci_shutकरोwn(hcd);
	spin_unlock_irqrestore(&ohci->lock, flags);
पूर्ण

/*-------------------------------------------------------------------------*
 * HC functions
 *-------------------------------------------------------------------------*/

/* init memory, and kick BIOS/SMM off */

अटल पूर्णांक ohci_init (काष्ठा ohci_hcd *ohci)
अणु
	पूर्णांक ret;
	काष्ठा usb_hcd *hcd = ohci_to_hcd(ohci);

	/* Accept arbitrarily दीर्घ scatter-gather lists */
	अगर (!hcd->localmem_pool)
		hcd->self.sg_tablesize = ~0;

	अगर (distrust_firmware)
		ohci->flags |= OHCI_QUIRK_HUB_POWER;

	ohci->rh_state = OHCI_RH_HALTED;
	ohci->regs = hcd->regs;

	/* REVISIT this BIOS handshake is now moved पूर्णांकo PCI "quirks", and
	 * was never needed क्रम most non-PCI प्रणालीs ... हटाओ the code?
	 */

#अगर_अघोषित IR_DISABLE
	/* SMM owns the HC?  not क्रम दीर्घ! */
	अगर (!no_handshake && ohci_पढ़ोl (ohci,
					&ohci->regs->control) & OHCI_CTRL_IR) अणु
		u32 temp;

		ohci_dbg (ohci, "USB HC TakeOver from BIOS/SMM\n");

		/* this समयout is arbitrary.  we make it दीर्घ, so प्रणालीs
		 * depending on usb keyboards may be usable even अगर the
		 * BIOS/SMM code seems pretty broken.
		 */
		temp = 500;	/* arbitrary: five seconds */

		ohci_ग_लिखोl (ohci, OHCI_INTR_OC, &ohci->regs->पूर्णांकrenable);
		ohci_ग_लिखोl (ohci, OHCI_OCR, &ohci->regs->cmdstatus);
		जबतक (ohci_पढ़ोl (ohci, &ohci->regs->control) & OHCI_CTRL_IR) अणु
			msleep (10);
			अगर (--temp == 0) अणु
				ohci_err (ohci, "USB HC takeover failed!"
					"  (BIOS/SMM bug)\n");
				वापस -EBUSY;
			पूर्ण
		पूर्ण
		ohci_usb_reset (ohci);
	पूर्ण
#पूर्ण_अगर

	/* Disable HC पूर्णांकerrupts */
	ohci_ग_लिखोl (ohci, OHCI_INTR_MIE, &ohci->regs->पूर्णांकrdisable);

	/* flush the ग_लिखोs, and save key bits like RWC */
	अगर (ohci_पढ़ोl (ohci, &ohci->regs->control) & OHCI_CTRL_RWC)
		ohci->hc_control |= OHCI_CTRL_RWC;

	/* Read the number of ports unless overridden */
	अगर (ohci->num_ports == 0)
		ohci->num_ports = roothub_a(ohci) & RH_A_NDP;

	अगर (ohci->hcca)
		वापस 0;

	समयr_setup(&ohci->io_watchकरोg, io_watchकरोg_func, 0);
	ohci->prev_frame_no = IO_WATCHDOG_OFF;

	अगर (hcd->localmem_pool)
		ohci->hcca = gen_pool_dma_alloc_align(hcd->localmem_pool,
						माप(*ohci->hcca),
						&ohci->hcca_dma, 256);
	अन्यथा
		ohci->hcca = dma_alloc_coherent(hcd->self.controller,
						माप(*ohci->hcca),
						&ohci->hcca_dma,
						GFP_KERNEL);
	अगर (!ohci->hcca)
		वापस -ENOMEM;

	अगर ((ret = ohci_mem_init (ohci)) < 0)
		ohci_stop (hcd);
	अन्यथा अणु
		create_debug_files (ohci);
	पूर्ण

	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/

/* Start an OHCI controller, set the BUS operational
 * resets USB and controller
 * enable पूर्णांकerrupts
 */
अटल पूर्णांक ohci_run (काष्ठा ohci_hcd *ohci)
अणु
	u32			mask, val;
	पूर्णांक			first = ohci->fmपूर्णांकerval == 0;
	काष्ठा usb_hcd		*hcd = ohci_to_hcd(ohci);

	ohci->rh_state = OHCI_RH_HALTED;

	/* boot firmware should have set this up (5.1.1.3.1) */
	अगर (first) अणु

		val = ohci_पढ़ोl (ohci, &ohci->regs->fmपूर्णांकerval);
		ohci->fmपूर्णांकerval = val & 0x3fff;
		अगर (ohci->fmपूर्णांकerval != FI)
			ohci_dbg (ohci, "fminterval delta %d\n",
				ohci->fmपूर्णांकerval - FI);
		ohci->fmपूर्णांकerval |= FSMP (ohci->fmपूर्णांकerval) << 16;
		/* also: घातer/overcurrent flags in roothub.a */
	पूर्ण

	/* Reset USB nearly "by the book".  RemoteWakeupConnected has
	 * to be checked in हाल boot firmware (BIOS/SMM/...) has set up
	 * wakeup in a way the bus isn't aware of (e.g., legacy PCI PM).
	 * If the bus glue detected wakeup capability then it should
	 * alपढ़ोy be enabled; अगर so we'll just enable it again.
	 */
	अगर ((ohci->hc_control & OHCI_CTRL_RWC) != 0)
		device_set_wakeup_capable(hcd->self.controller, 1);

	चयन (ohci->hc_control & OHCI_CTRL_HCFS) अणु
	हाल OHCI_USB_OPER:
		val = 0;
		अवरोध;
	हाल OHCI_USB_SUSPEND:
	हाल OHCI_USB_RESUME:
		ohci->hc_control &= OHCI_CTRL_RWC;
		ohci->hc_control |= OHCI_USB_RESUME;
		val = 10 /* msec रुको */;
		अवरोध;
	// हाल OHCI_USB_RESET:
	शेष:
		ohci->hc_control &= OHCI_CTRL_RWC;
		ohci->hc_control |= OHCI_USB_RESET;
		val = 50 /* msec रुको */;
		अवरोध;
	पूर्ण
	ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
	// flush the ग_लिखोs
	(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
	msleep(val);

	स_रखो (ohci->hcca, 0, माप (काष्ठा ohci_hcca));

	/* 2msec समयlimit here means no irqs/preempt */
	spin_lock_irq (&ohci->lock);

retry:
	/* HC Reset requires max 10 us delay */
	ohci_ग_लिखोl (ohci, OHCI_HCR,  &ohci->regs->cmdstatus);
	val = 30;	/* ... allow extra समय */
	जबतक ((ohci_पढ़ोl (ohci, &ohci->regs->cmdstatus) & OHCI_HCR) != 0) अणु
		अगर (--val == 0) अणु
			spin_unlock_irq (&ohci->lock);
			ohci_err (ohci, "USB HC reset timed out!\n");
			वापस -1;
		पूर्ण
		udelay (1);
	पूर्ण

	/* now we're in the SUSPEND state ... must go OPERATIONAL
	 * within 2msec अन्यथा HC enters RESUME
	 *
	 * ... but some hardware won't init fmInterval "by the book"
	 * (SiS, OPTi ...), so reset again instead.  SiS करोesn't need
	 * this अगर we ग_लिखो fmInterval after we're OPERATIONAL.
	 * Unclear about ALi, ServerWorks, and others ... this could
	 * easily be a दीर्घstanding bug in chip init on Linux.
	 */
	अगर (ohci->flags & OHCI_QUIRK_INITRESET) अणु
		ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
		// flush those ग_लिखोs
		(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
	पूर्ण

	/* Tell the controller where the control and bulk lists are
	 * The lists are empty now. */
	ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_controlhead);
	ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_bulkhead);

	/* a reset clears this */
	ohci_ग_लिखोl (ohci, (u32) ohci->hcca_dma, &ohci->regs->hcca);

	periodic_reinit (ohci);

	/* some OHCI implementations are finicky about how they init.
	 * bogus values here mean not even क्रमागतeration could work.
	 */
	अगर ((ohci_पढ़ोl (ohci, &ohci->regs->fmपूर्णांकerval) & 0x3fff0000) == 0
			|| !ohci_पढ़ोl (ohci, &ohci->regs->periodicstart)) अणु
		अगर (!(ohci->flags & OHCI_QUIRK_INITRESET)) अणु
			ohci->flags |= OHCI_QUIRK_INITRESET;
			ohci_dbg (ohci, "enabling initreset quirk\n");
			जाओ retry;
		पूर्ण
		spin_unlock_irq (&ohci->lock);
		ohci_err (ohci, "init err (%08x %04x)\n",
			ohci_पढ़ोl (ohci, &ohci->regs->fmपूर्णांकerval),
			ohci_पढ़ोl (ohci, &ohci->regs->periodicstart));
		वापस -EOVERFLOW;
	पूर्ण

	/* use rhsc irqs after hub_wq is allocated */
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	hcd->uses_new_polling = 1;

	/* start controller operations */
	ohci->hc_control &= OHCI_CTRL_RWC;
	ohci->hc_control |= OHCI_CONTROL_INIT | OHCI_USB_OPER;
	ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
	ohci->rh_state = OHCI_RH_RUNNING;

	/* wake on ConnectStatusChange, matching बाह्यal hubs */
	ohci_ग_लिखोl (ohci, RH_HS_DRWE, &ohci->regs->roothub.status);

	/* Choose the पूर्णांकerrupts we care about now, others later on demand */
	mask = OHCI_INTR_INIT;
	ohci_ग_लिखोl (ohci, ~0, &ohci->regs->पूर्णांकrstatus);
	ohci_ग_लिखोl (ohci, mask, &ohci->regs->पूर्णांकrenable);

	/* handle root hub init quirks ... */
	val = roothub_a (ohci);
	/* Configure क्रम per-port over-current protection by शेष */
	val &= ~RH_A_NOCP;
	val |= RH_A_OCPM;
	अगर (ohci->flags & OHCI_QUIRK_SUPERIO) अणु
		/* NSC 87560 and maybe others.
		 * Ganged घातer चयनing, no over-current protection.
		 */
		val |= RH_A_NOCP;
		val &= ~(RH_A_POTPGT | RH_A_NPS | RH_A_PSM | RH_A_OCPM);
	पूर्ण अन्यथा अगर ((ohci->flags & OHCI_QUIRK_AMD756) ||
			(ohci->flags & OHCI_QUIRK_HUB_POWER)) अणु
		/* hub घातer always on; required क्रम AMD-756 and some
		 * Mac platक्रमms.
		 */
		val |= RH_A_NPS;
	पूर्ण
	ohci_ग_लिखोl(ohci, val, &ohci->regs->roothub.a);

	ohci_ग_लिखोl (ohci, RH_HS_LPSC, &ohci->regs->roothub.status);
	ohci_ग_लिखोl (ohci, (val & RH_A_NPS) ? 0 : RH_B_PPCM,
						&ohci->regs->roothub.b);
	// flush those ग_लिखोs
	(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);

	ohci->next_statechange = jअगरfies + STATECHANGE_DELAY;
	spin_unlock_irq (&ohci->lock);

	// POTPGT delay is bits 24-31, in 2 ms units.
	mdelay ((val >> 23) & 0x1fe);

	ohci_dump(ohci);

	वापस 0;
पूर्ण

/* ohci_setup routine क्रम generic controller initialization */

पूर्णांक ohci_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci(hcd);

	ohci_hcd_init(ohci);
	
	वापस ohci_init(ohci);
पूर्ण
EXPORT_SYMBOL_GPL(ohci_setup);

/* ohci_start routine क्रम generic controller start of all OHCI bus glue */
अटल पूर्णांक ohci_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci(hcd);
	पूर्णांक	ret;

	ret = ohci_run(ohci);
	अगर (ret < 0) अणु
		ohci_err(ohci, "can't start\n");
		ohci_stop(hcd);
	पूर्ण
	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Some OHCI controllers are known to lose track of completed TDs.  They
 * करोn't add the TDs to the hardware करोne queue, which means we never see
 * them as being completed.
 *
 * This watchकरोg routine checks क्रम such problems.  Without some way to
 * tell when those TDs have completed, we would never take their EDs off
 * the unlink list.  As a result, URBs could never be dequeued and
 * endpoपूर्णांकs could never be released.
 */
अटल व्योम io_watchकरोg_func(काष्ठा समयr_list *t)
अणु
	काष्ठा ohci_hcd	*ohci = from_समयr(ohci, t, io_watchकरोg);
	bool		takeback_all_pending = false;
	u32		status;
	u32		head;
	काष्ठा ed	*ed;
	काष्ठा td	*td, *td_start, *td_next;
	अचिन्हित	frame_no, prev_frame_no = IO_WATCHDOG_OFF;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&ohci->lock, flags);

	/*
	 * One way to lose track of completed TDs is अगर the controller
	 * never ग_लिखोs back the करोne queue head.  If it hasn't been
	 * written back since the last समय this function ran and अगर it
	 * was non-empty at that समय, something is badly wrong with the
	 * hardware.
	 */
	status = ohci_पढ़ोl(ohci, &ohci->regs->पूर्णांकrstatus);
	अगर (!(status & OHCI_INTR_WDH) && ohci->wdh_cnt == ohci->prev_wdh_cnt) अणु
		अगर (ohci->prev_करोnehead) अणु
			ohci_err(ohci, "HcDoneHead not written back; disabled\n");
 died:
			usb_hc_died(ohci_to_hcd(ohci));
			ohci_dump(ohci);
			_ohci_shutकरोwn(ohci_to_hcd(ohci));
			जाओ करोne;
		पूर्ण अन्यथा अणु
			/* No ग_लिखो back because the करोne queue was empty */
			takeback_all_pending = true;
		पूर्ण
	पूर्ण

	/* Check every ED which might have pending TDs */
	list_क्रम_each_entry(ed, &ohci->eds_in_use, in_use_list) अणु
		अगर (ed->pending_td) अणु
			अगर (takeback_all_pending ||
					OKAY_TO_TAKEBACK(ohci, ed)) अणु
				अचिन्हित पंचांगp = hc32_to_cpu(ohci, ed->hwINFO);

				ohci_dbg(ohci, "takeback pending TD for dev %d ep 0x%x\n",
						0x007f & पंचांगp,
						(0x000f & (पंचांगp >> 7)) +
							((पंचांगp & ED_IN) >> 5));
				add_to_करोne_list(ohci, ed->pending_td);
			पूर्ण
		पूर्ण

		/* Starting from the latest pending TD, */
		td = ed->pending_td;

		/* or the last TD on the करोne list, */
		अगर (!td) अणु
			list_क्रम_each_entry(td_next, &ed->td_list, td_list) अणु
				अगर (!td_next->next_dl_td)
					अवरोध;
				td = td_next;
			पूर्ण
		पूर्ण

		/* find the last TD processed by the controller. */
		head = hc32_to_cpu(ohci, READ_ONCE(ed->hwHeadP)) & TD_MASK;
		td_start = td;
		td_next = list_prepare_entry(td, &ed->td_list, td_list);
		list_क्रम_each_entry_जारी(td_next, &ed->td_list, td_list) अणु
			अगर (head == (u32) td_next->td_dma)
				अवरोध;
			td = td_next;	/* head poपूर्णांकer has passed this TD */
		पूर्ण
		अगर (td != td_start) अणु
			/*
			 * In हाल a WDH cycle is in progress, we will रुको
			 * क्रम the next two cycles to complete beक्रमe assuming
			 * this TD will never get on the करोne queue.
			 */
			ed->takeback_wdh_cnt = ohci->wdh_cnt + 2;
			ed->pending_td = td;
		पूर्ण
	पूर्ण

	ohci_work(ohci);

	अगर (ohci->rh_state == OHCI_RH_RUNNING) अणु

		/*
		 * Someबार a controller just stops working.  We can tell
		 * by checking that the frame counter has advanced since
		 * the last समय we ran.
		 *
		 * But be careful: Some controllers violate the spec by
		 * stopping their frame counter when no ports are active.
		 */
		frame_no = ohci_frame_no(ohci);
		अगर (frame_no == ohci->prev_frame_no) अणु
			पूर्णांक		active_cnt = 0;
			पूर्णांक		i;
			अचिन्हित	पंचांगp;

			क्रम (i = 0; i < ohci->num_ports; ++i) अणु
				पंचांगp = roothub_portstatus(ohci, i);
				/* Enabled and not suspended? */
				अगर ((पंचांगp & RH_PS_PES) && !(पंचांगp & RH_PS_PSS))
					++active_cnt;
			पूर्ण

			अगर (active_cnt > 0) अणु
				ohci_err(ohci, "frame counter not updating; disabled\n");
				जाओ died;
			पूर्ण
		पूर्ण
		अगर (!list_empty(&ohci->eds_in_use)) अणु
			prev_frame_no = frame_no;
			ohci->prev_wdh_cnt = ohci->wdh_cnt;
			ohci->prev_करोnehead = ohci_पढ़ोl(ohci,
					&ohci->regs->करोnehead);
			mod_समयr(&ohci->io_watchकरोg,
					jअगरfies + IO_WATCHDOG_DELAY);
		पूर्ण
	पूर्ण

 करोne:
	ohci->prev_frame_no = prev_frame_no;
	spin_unlock_irqrestore(&ohci->lock, flags);
पूर्ण

/* an पूर्णांकerrupt happens */

अटल irqवापस_t ohci_irq (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci (hcd);
	काष्ठा ohci_regs __iomem *regs = ohci->regs;
	पूर्णांक			पूर्णांकs;

	/* Read पूर्णांकerrupt status (and flush pending ग_लिखोs).  We ignore the
	 * optimization of checking the LSB of hcca->करोne_head; it करोesn't
	 * work on all प्रणालीs (edge triggering क्रम OHCI can be a factor).
	 */
	पूर्णांकs = ohci_पढ़ोl(ohci, &regs->पूर्णांकrstatus);

	/* Check क्रम an all 1's result which is a typical consequence
	 * of dead, unघड़ीed, or unplugged (CardBus...) devices
	 */
	अगर (पूर्णांकs == ~(u32)0) अणु
		ohci->rh_state = OHCI_RH_HALTED;
		ohci_dbg (ohci, "device removed!\n");
		usb_hc_died(hcd);
		वापस IRQ_HANDLED;
	पूर्ण

	/* We only care about पूर्णांकerrupts that are enabled */
	पूर्णांकs &= ohci_पढ़ोl(ohci, &regs->पूर्णांकrenable);

	/* पूर्णांकerrupt क्रम some other device? */
	अगर (पूर्णांकs == 0 || unlikely(ohci->rh_state == OHCI_RH_HALTED))
		वापस IRQ_NOTMINE;

	अगर (पूर्णांकs & OHCI_INTR_UE) अणु
		// e.g. due to PCI Master/Target Abort
		अगर (quirk_nec(ohci)) अणु
			/* Workaround क्रम a silicon bug in some NEC chips used
			 * in Apple's PowerBooks. Adapted from Darwin code.
			 */
			ohci_err (ohci, "OHCI Unrecoverable Error, scheduling NEC chip restart\n");

			ohci_ग_लिखोl (ohci, OHCI_INTR_UE, &regs->पूर्णांकrdisable);

			schedule_work (&ohci->nec_work);
		पूर्ण अन्यथा अणु
			ohci_err (ohci, "OHCI Unrecoverable Error, disabled\n");
			ohci->rh_state = OHCI_RH_HALTED;
			usb_hc_died(hcd);
		पूर्ण

		ohci_dump(ohci);
		ohci_usb_reset (ohci);
	पूर्ण

	अगर (पूर्णांकs & OHCI_INTR_RHSC) अणु
		ohci_dbg(ohci, "rhsc\n");
		ohci->next_statechange = jअगरfies + STATECHANGE_DELAY;
		ohci_ग_लिखोl(ohci, OHCI_INTR_RD | OHCI_INTR_RHSC,
				&regs->पूर्णांकrstatus);

		/* NOTE: Venकरोrs didn't always make the same implementation
		 * choices क्रम RHSC.  Many followed the spec; RHSC triggers
		 * on an edge, like setting and maybe clearing a port status
		 * change bit.  With others it's level-triggered, active
		 * until hub_wq clears all the port status change bits.  We'll
		 * always disable it here and rely on polling until hub_wq
		 * re-enables it.
		 */
		ohci_ग_लिखोl(ohci, OHCI_INTR_RHSC, &regs->पूर्णांकrdisable);
		usb_hcd_poll_rh_status(hcd);
	पूर्ण

	/* For connect and disconnect events, we expect the controller
	 * to turn on RHSC aदीर्घ with RD.  But क्रम remote wakeup events
	 * this might not happen.
	 */
	अन्यथा अगर (पूर्णांकs & OHCI_INTR_RD) अणु
		ohci_dbg(ohci, "resume detect\n");
		ohci_ग_लिखोl(ohci, OHCI_INTR_RD, &regs->पूर्णांकrstatus);
		set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
		अगर (ohci->स्वतःstop) अणु
			spin_lock (&ohci->lock);
			ohci_rh_resume (ohci);
			spin_unlock (&ohci->lock);
		पूर्ण अन्यथा
			usb_hcd_resume_root_hub(hcd);
	पूर्ण

	spin_lock(&ohci->lock);
	अगर (पूर्णांकs & OHCI_INTR_WDH)
		update_करोne_list(ohci);

	/* could track INTR_SO to reduce available PCI/... bandwidth */

	/* handle any pending URB/ED unlinks, leaving INTR_SF enabled
	 * when there's still unlinking to be करोne (next frame).
	 */
	ohci_work(ohci);
	अगर ((पूर्णांकs & OHCI_INTR_SF) != 0 && !ohci->ed_rm_list
			&& ohci->rh_state == OHCI_RH_RUNNING)
		ohci_ग_लिखोl (ohci, OHCI_INTR_SF, &regs->पूर्णांकrdisable);

	अगर (ohci->rh_state == OHCI_RH_RUNNING) अणु
		ohci_ग_लिखोl (ohci, पूर्णांकs, &regs->पूर्णांकrstatus);
		अगर (पूर्णांकs & OHCI_INTR_WDH)
			++ohci->wdh_cnt;

		ohci_ग_लिखोl (ohci, OHCI_INTR_MIE, &regs->पूर्णांकrenable);
		// flush those ग_लिखोs
		(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
	पूर्ण
	spin_unlock(&ohci->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम ohci_stop (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci (hcd);

	ohci_dump(ohci);

	अगर (quirk_nec(ohci))
		flush_work(&ohci->nec_work);
	del_समयr_sync(&ohci->io_watchकरोg);
	ohci->prev_frame_no = IO_WATCHDOG_OFF;

	ohci_ग_लिखोl (ohci, OHCI_INTR_MIE, &ohci->regs->पूर्णांकrdisable);
	ohci_usb_reset(ohci);
	मुक्त_irq(hcd->irq, hcd);
	hcd->irq = 0;

	अगर (quirk_amdiso(ohci))
		usb_amd_dev_put();

	हटाओ_debug_files (ohci);
	ohci_mem_cleanup (ohci);
	अगर (ohci->hcca) अणु
		अगर (hcd->localmem_pool)
			gen_pool_मुक्त(hcd->localmem_pool,
				      (अचिन्हित दीर्घ)ohci->hcca,
				      माप(*ohci->hcca));
		अन्यथा
			dma_मुक्त_coherent(hcd->self.controller,
					  माप(*ohci->hcca),
					  ohci->hcca, ohci->hcca_dma);
		ohci->hcca = शून्य;
		ohci->hcca_dma = 0;
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर defined(CONFIG_PM) || defined(CONFIG_USB_PCI)

/* must not be called from पूर्णांकerrupt context */
पूर्णांक ohci_restart(काष्ठा ohci_hcd *ohci)
अणु
	पूर्णांक temp;
	पूर्णांक i;
	काष्ठा urb_priv *priv;

	ohci_init(ohci);
	spin_lock_irq(&ohci->lock);
	ohci->rh_state = OHCI_RH_HALTED;

	/* Recycle any "live" eds/tds (and urbs). */
	अगर (!list_empty (&ohci->pending))
		ohci_dbg(ohci, "abort schedule...\n");
	list_क्रम_each_entry (priv, &ohci->pending, pending) अणु
		काष्ठा urb	*urb = priv->td[0]->urb;
		काष्ठा ed	*ed = priv->ed;

		चयन (ed->state) अणु
		हाल ED_OPER:
			ed->state = ED_UNLINK;
			ed->hwINFO |= cpu_to_hc32(ohci, ED_DEQUEUE);
			ed_deschedule (ohci, ed);

			ed->ed_next = ohci->ed_rm_list;
			ed->ed_prev = शून्य;
			ohci->ed_rm_list = ed;
			fallthrough;
		हाल ED_UNLINK:
			अवरोध;
		शेष:
			ohci_dbg(ohci, "bogus ed %p state %d\n",
					ed, ed->state);
		पूर्ण

		अगर (!urb->unlinked)
			urb->unlinked = -ESHUTDOWN;
	पूर्ण
	ohci_work(ohci);
	spin_unlock_irq(&ohci->lock);

	/* paranoia, in हाल that didn't work: */

	/* empty the पूर्णांकerrupt branches */
	क्रम (i = 0; i < NUM_INTS; i++) ohci->load [i] = 0;
	क्रम (i = 0; i < NUM_INTS; i++) ohci->hcca->पूर्णांक_table [i] = 0;

	/* no EDs to हटाओ */
	ohci->ed_rm_list = शून्य;

	/* empty control and bulk lists */
	ohci->ed_controltail = शून्य;
	ohci->ed_bulktail    = शून्य;

	अगर ((temp = ohci_run (ohci)) < 0) अणु
		ohci_err (ohci, "can't restart, %d\n", temp);
		वापस temp;
	पूर्ण
	ohci_dbg(ohci, "restart complete\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ohci_restart);

#पूर्ण_अगर

#अगर_घोषित CONFIG_PM

पूर्णांक ohci_suspend(काष्ठा usb_hcd *hcd, bool करो_wakeup)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);
	अचिन्हित दीर्घ	flags;
	पूर्णांक		rc = 0;

	/* Disable irq emission and mark HW unaccessible. Use
	 * the spinlock to properly synchronize with possible pending
	 * RH suspend or resume activity.
	 */
	spin_lock_irqsave (&ohci->lock, flags);
	ohci_ग_लिखोl(ohci, OHCI_INTR_MIE, &ohci->regs->पूर्णांकrdisable);
	(व्योम)ohci_पढ़ोl(ohci, &ohci->regs->पूर्णांकrdisable);

	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	spin_unlock_irqrestore (&ohci->lock, flags);

	synchronize_irq(hcd->irq);

	अगर (करो_wakeup && HCD_WAKEUP_PENDING(hcd)) अणु
		ohci_resume(hcd, false);
		rc = -EBUSY;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ohci_suspend);


पूर्णांक ohci_resume(काष्ठा usb_hcd *hcd, bool hibernated)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci(hcd);
	पूर्णांक			port;
	bool			need_reinit = false;

	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	/* Make sure resume from hibernation re-क्रमागतerates everything */
	अगर (hibernated)
		ohci_usb_reset(ohci);

	/* See अगर the controller is alपढ़ोy running or has been reset */
	ohci->hc_control = ohci_पढ़ोl(ohci, &ohci->regs->control);
	अगर (ohci->hc_control & (OHCI_CTRL_IR | OHCI_SCHED_ENABLES)) अणु
		need_reinit = true;
	पूर्ण अन्यथा अणु
		चयन (ohci->hc_control & OHCI_CTRL_HCFS) अणु
		हाल OHCI_USB_OPER:
		हाल OHCI_USB_RESET:
			need_reinit = true;
		पूर्ण
	पूर्ण

	/* If needed, reinitialize and suspend the root hub */
	अगर (need_reinit) अणु
		spin_lock_irq(&ohci->lock);
		ohci_rh_resume(ohci);
		ohci_rh_suspend(ohci, 0);
		spin_unlock_irq(&ohci->lock);
	पूर्ण

	/* Normally just turn on port घातer and enable पूर्णांकerrupts */
	अन्यथा अणु
		ohci_dbg(ohci, "powerup ports\n");
		क्रम (port = 0; port < ohci->num_ports; port++)
			ohci_ग_लिखोl(ohci, RH_PS_PPS,
					&ohci->regs->roothub.portstatus[port]);

		ohci_ग_लिखोl(ohci, OHCI_INTR_MIE, &ohci->regs->पूर्णांकrenable);
		ohci_पढ़ोl(ohci, &ohci->regs->पूर्णांकrenable);
		msleep(20);
	पूर्ण

	usb_hcd_resume_root_hub(hcd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ohci_resume);

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/*
 * Generic काष्ठाure: This माला_लो copied क्रम platक्रमm drivers so that
 * inभागidual entries can be overridden as needed.
 */

अटल स्थिर काष्ठा hc_driver ohci_hc_driver = अणु
	.description =          hcd_name,
	.product_desc =         "OHCI Host Controller",
	.hcd_priv_size =        माप(काष्ठा ohci_hcd),

	/*
	 * generic hardware linkage
	*/
	.irq =                  ohci_irq,
	.flags =                HCD_MEMORY | HCD_DMA | HCD_USB11,

	/*
	* basic lअगरecycle operations
	*/
	.reset =                ohci_setup,
	.start =                ohci_start,
	.stop =                 ohci_stop,
	.shutकरोwn =             ohci_shutकरोwn,

	/*
	 * managing i/o requests and associated device resources
	*/
	.urb_enqueue =          ohci_urb_enqueue,
	.urb_dequeue =          ohci_urb_dequeue,
	.endpoपूर्णांक_disable =     ohci_endpoपूर्णांक_disable,

	/*
	* scheduling support
	*/
	.get_frame_number =     ohci_get_frame,

	/*
	* root hub support
	*/
	.hub_status_data =      ohci_hub_status_data,
	.hub_control =          ohci_hub_control,
#अगर_घोषित CONFIG_PM
	.bus_suspend =          ohci_bus_suspend,
	.bus_resume =           ohci_bus_resume,
#पूर्ण_अगर
	.start_port_reset =	ohci_start_port_reset,
पूर्ण;

व्योम ohci_init_driver(काष्ठा hc_driver *drv,
		स्थिर काष्ठा ohci_driver_overrides *over)
अणु
	/* Copy the generic table to drv and then apply the overrides */
	*drv = ohci_hc_driver;

	अगर (over) अणु
		drv->product_desc = over->product_desc;
		drv->hcd_priv_size += over->extra_priv_size;
		अगर (over->reset)
			drv->reset = over->reset;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ohci_init_driver);

/*-------------------------------------------------------------------------*/

MODULE_AUTHOR (DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE ("GPL");

#अगर defined(CONFIG_ARCH_SA1100) && defined(CONFIG_SA1111)
#समावेश "ohci-sa1111.c"
#घोषणा SA1111_DRIVER		ohci_hcd_sa1111_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_OHCI_HCD_PPC_OF
#समावेश "ohci-ppc-of.c"
#घोषणा OF_PLATFORM_DRIVER	ohci_hcd_ppc_of_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PS3
#समावेश "ohci-ps3.c"
#घोषणा PS3_SYSTEM_BUS_DRIVER	ps3_ohci_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_MFD_SM501
#समावेश "ohci-sm501.c"
#घोषणा SM501_OHCI_DRIVER	ohci_hcd_sm501_driver
#पूर्ण_अगर

#अगर_घोषित CONFIG_MFD_TC6393XB
#समावेश "ohci-tmio.c"
#घोषणा TMIO_OHCI_DRIVER	ohci_hcd_पंचांगio_driver
#पूर्ण_अगर

अटल पूर्णांक __init ohci_hcd_mod_init(व्योम)
अणु
	पूर्णांक retval = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "%s: " DRIVER_DESC "\n", hcd_name);
	pr_debug ("%s: block sizes: ed %zd td %zd\n", hcd_name,
		माप (काष्ठा ed), माप (काष्ठा td));
	set_bit(USB_OHCI_LOADED, &usb_hcds_loaded);

	ohci_debug_root = debugfs_create_dir("ohci", usb_debug_root);

#अगर_घोषित PS3_SYSTEM_BUS_DRIVER
	retval = ps3_ohci_driver_रेजिस्टर(&PS3_SYSTEM_BUS_DRIVER);
	अगर (retval < 0)
		जाओ error_ps3;
#पूर्ण_अगर

#अगर_घोषित OF_PLATFORM_DRIVER
	retval = platक्रमm_driver_रेजिस्टर(&OF_PLATFORM_DRIVER);
	अगर (retval < 0)
		जाओ error_of_platक्रमm;
#पूर्ण_अगर

#अगर_घोषित SA1111_DRIVER
	retval = sa1111_driver_रेजिस्टर(&SA1111_DRIVER);
	अगर (retval < 0)
		जाओ error_sa1111;
#पूर्ण_अगर

#अगर_घोषित SM501_OHCI_DRIVER
	retval = platक्रमm_driver_रेजिस्टर(&SM501_OHCI_DRIVER);
	अगर (retval < 0)
		जाओ error_sm501;
#पूर्ण_अगर

#अगर_घोषित TMIO_OHCI_DRIVER
	retval = platक्रमm_driver_रेजिस्टर(&TMIO_OHCI_DRIVER);
	अगर (retval < 0)
		जाओ error_पंचांगio;
#पूर्ण_अगर

	वापस retval;

	/* Error path */
#अगर_घोषित TMIO_OHCI_DRIVER
	platक्रमm_driver_unरेजिस्टर(&TMIO_OHCI_DRIVER);
 error_पंचांगio:
#पूर्ण_अगर
#अगर_घोषित SM501_OHCI_DRIVER
	platक्रमm_driver_unरेजिस्टर(&SM501_OHCI_DRIVER);
 error_sm501:
#पूर्ण_अगर
#अगर_घोषित SA1111_DRIVER
	sa1111_driver_unरेजिस्टर(&SA1111_DRIVER);
 error_sa1111:
#पूर्ण_अगर
#अगर_घोषित OF_PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&OF_PLATFORM_DRIVER);
 error_of_platक्रमm:
#पूर्ण_अगर
#अगर_घोषित PS3_SYSTEM_BUS_DRIVER
	ps3_ohci_driver_unरेजिस्टर(&PS3_SYSTEM_BUS_DRIVER);
 error_ps3:
#पूर्ण_अगर
	debugfs_हटाओ(ohci_debug_root);
	ohci_debug_root = शून्य;

	clear_bit(USB_OHCI_LOADED, &usb_hcds_loaded);
	वापस retval;
पूर्ण
module_init(ohci_hcd_mod_init);

अटल व्योम __निकास ohci_hcd_mod_निकास(व्योम)
अणु
#अगर_घोषित TMIO_OHCI_DRIVER
	platक्रमm_driver_unरेजिस्टर(&TMIO_OHCI_DRIVER);
#पूर्ण_अगर
#अगर_घोषित SM501_OHCI_DRIVER
	platक्रमm_driver_unरेजिस्टर(&SM501_OHCI_DRIVER);
#पूर्ण_अगर
#अगर_घोषित SA1111_DRIVER
	sa1111_driver_unरेजिस्टर(&SA1111_DRIVER);
#पूर्ण_अगर
#अगर_घोषित OF_PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&OF_PLATFORM_DRIVER);
#पूर्ण_अगर
#अगर_घोषित PS3_SYSTEM_BUS_DRIVER
	ps3_ohci_driver_unरेजिस्टर(&PS3_SYSTEM_BUS_DRIVER);
#पूर्ण_अगर
	debugfs_हटाओ(ohci_debug_root);
	clear_bit(USB_OHCI_LOADED, &usb_hcds_loaded);
पूर्ण
module_निकास(ohci_hcd_mod_निकास);

