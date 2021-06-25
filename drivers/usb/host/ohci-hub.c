<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2004 David Brownell <dbrownell@users.sourceक्रमge.net>
 *
 * This file is licenced under GPL
 */

/*-------------------------------------------------------------------------*/

/*
 * OHCI Root Hub ... the nonsharable stuff
 */

#घोषणा dbg_port(hc,label,num,value) \
	ohci_dbg (hc, \
		"%s roothub.portstatus [%d] " \
		"= 0x%08x%s%s%s%s%s%s%s%s%s%s%s%s\n", \
		label, num, value, \
		(value & RH_PS_PRSC) ? " PRSC" : "", \
		(value & RH_PS_OCIC) ? " OCIC" : "", \
		(value & RH_PS_PSSC) ? " PSSC" : "", \
		(value & RH_PS_PESC) ? " PESC" : "", \
		(value & RH_PS_CSC) ? " CSC" : "", \
		\
		(value & RH_PS_LSDA) ? " LSDA" : "", \
		(value & RH_PS_PPS) ? " PPS" : "", \
		(value & RH_PS_PRS) ? " PRS" : "", \
		(value & RH_PS_POCI) ? " POCI" : "", \
		(value & RH_PS_PSS) ? " PSS" : "", \
		\
		(value & RH_PS_PES) ? " PES" : "", \
		(value & RH_PS_CCS) ? " CCS" : "" \
		);

/*-------------------------------------------------------------------------*/

#घोषणा OHCI_SCHED_ENABLES \
	(OHCI_CTRL_CLE|OHCI_CTRL_BLE|OHCI_CTRL_PLE|OHCI_CTRL_IE)

अटल व्योम update_करोne_list(काष्ठा ohci_hcd *);
अटल व्योम ohci_work(काष्ठा ohci_hcd *);

#अगर_घोषित	CONFIG_PM
अटल पूर्णांक ohci_rh_suspend (काष्ठा ohci_hcd *ohci, पूर्णांक स्वतःstop)
__releases(ohci->lock)
__acquires(ohci->lock)
अणु
	पूर्णांक			status = 0;

	ohci->hc_control = ohci_पढ़ोl (ohci, &ohci->regs->control);
	चयन (ohci->hc_control & OHCI_CTRL_HCFS) अणु
	हाल OHCI_USB_RESUME:
		ohci_dbg (ohci, "resume/suspend?\n");
		ohci->hc_control &= ~OHCI_CTRL_HCFS;
		ohci->hc_control |= OHCI_USB_RESET;
		ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
		(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
		fallthrough;
	हाल OHCI_USB_RESET:
		status = -EBUSY;
		ohci_dbg (ohci, "needs reinit!\n");
		जाओ करोne;
	हाल OHCI_USB_SUSPEND:
		अगर (!ohci->स्वतःstop) अणु
			ohci_dbg (ohci, "already suspended\n");
			जाओ करोne;
		पूर्ण
	पूर्ण
	ohci_dbg (ohci, "%s root hub\n",
			स्वतःstop ? "auto-stop" : "suspend");

	/* First stop any processing */
	अगर (!स्वतःstop && (ohci->hc_control & OHCI_SCHED_ENABLES)) अणु
		ohci->hc_control &= ~OHCI_SCHED_ENABLES;
		ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
		ohci->hc_control = ohci_पढ़ोl (ohci, &ohci->regs->control);
		ohci_ग_लिखोl (ohci, OHCI_INTR_SF, &ohci->regs->पूर्णांकrstatus);

		/* sched disables take effect on the next frame,
		 * then the last WDH could take 6+ msec
		 */
		ohci_dbg (ohci, "stopping schedules ...\n");
		ohci->स्वतःstop = 0;
		spin_unlock_irq (&ohci->lock);
		msleep (8);
		spin_lock_irq (&ohci->lock);
	पूर्ण
	update_करोne_list(ohci);
	ohci_work(ohci);

	/*
	 * Some controllers करोn't handle "global" suspend properly अगर
	 * there are unsuspended ports.  For these controllers, put all
	 * the enabled ports पूर्णांकo suspend beक्रमe suspending the root hub.
	 */
	अगर (ohci->flags & OHCI_QUIRK_GLOBAL_SUSPEND) अणु
		__hc32 __iomem	*portstat = ohci->regs->roothub.portstatus;
		पूर्णांक		i;
		अचिन्हित	temp;

		क्रम (i = 0; i < ohci->num_ports; (++i, ++portstat)) अणु
			temp = ohci_पढ़ोl(ohci, portstat);
			अगर ((temp & (RH_PS_PES | RH_PS_PSS)) ==
					RH_PS_PES)
				ohci_ग_लिखोl(ohci, RH_PS_PSS, portstat);
		पूर्ण
	पूर्ण

	/* maybe resume can wake root hub */
	अगर (ohci_to_hcd(ohci)->self.root_hub->करो_remote_wakeup || स्वतःstop) अणु
		ohci->hc_control |= OHCI_CTRL_RWE;
	पूर्ण अन्यथा अणु
		ohci_ग_लिखोl(ohci, OHCI_INTR_RHSC | OHCI_INTR_RD,
				&ohci->regs->पूर्णांकrdisable);
		ohci->hc_control &= ~OHCI_CTRL_RWE;
	पूर्ण

	/* Suspend hub ... this is the "global (to this bus) suspend" mode,
	 * which करोesn't imply ports will first be inभागidually suspended.
	 */
	ohci->hc_control &= ~OHCI_CTRL_HCFS;
	ohci->hc_control |= OHCI_USB_SUSPEND;
	ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
	(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);

	/* no resumes until devices finish suspending */
	अगर (!स्वतःstop) अणु
		ohci->next_statechange = jअगरfies + msecs_to_jअगरfies (5);
		ohci->स्वतःstop = 0;
		ohci->rh_state = OHCI_RH_SUSPENDED;
	पूर्ण

करोne:
	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा ed *find_head (काष्ठा ed *ed)
अणु
	/* क्रम bulk and control lists */
	जबतक (ed->ed_prev)
		ed = ed->ed_prev;
	वापस ed;
पूर्ण

/* caller has locked the root hub */
अटल पूर्णांक ohci_rh_resume (काष्ठा ohci_hcd *ohci)
__releases(ohci->lock)
__acquires(ohci->lock)
अणु
	काष्ठा usb_hcd		*hcd = ohci_to_hcd (ohci);
	u32			temp, enables;
	पूर्णांक			status = -EINPROGRESS;
	पूर्णांक			स्वतःstopped = ohci->स्वतःstop;

	ohci->स्वतःstop = 0;
	ohci->hc_control = ohci_पढ़ोl (ohci, &ohci->regs->control);

	अगर (ohci->hc_control & (OHCI_CTRL_IR | OHCI_SCHED_ENABLES)) अणु
		/* this can happen after resuming a swsusp snapshot */
		अगर (ohci->rh_state != OHCI_RH_RUNNING) अणु
			ohci_dbg (ohci, "BIOS/SMM active, control %03x\n",
					ohci->hc_control);
			status = -EBUSY;
		/* this happens when pmcore resumes HC then root */
		पूर्ण अन्यथा अणु
			ohci_dbg (ohci, "duplicate resume\n");
			status = 0;
		पूर्ण
	पूर्ण अन्यथा चयन (ohci->hc_control & OHCI_CTRL_HCFS) अणु
	हाल OHCI_USB_SUSPEND:
		ohci->hc_control &= ~(OHCI_CTRL_HCFS|OHCI_SCHED_ENABLES);
		ohci->hc_control |= OHCI_USB_RESUME;
		ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
		(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
		ohci_dbg (ohci, "%s root hub\n",
				स्वतःstopped ? "auto-start" : "resume");
		अवरोध;
	हाल OHCI_USB_RESUME:
		/* HCFS changes someसमय after INTR_RD */
		ohci_dbg(ohci, "%swakeup root hub\n",
				स्वतःstopped ? "auto-" : "");
		अवरोध;
	हाल OHCI_USB_OPER:
		/* this can happen after resuming a swsusp snapshot */
		ohci_dbg (ohci, "snapshot resume? reinit\n");
		status = -EBUSY;
		अवरोध;
	शेष:		/* RESET, we lost घातer */
		ohci_dbg (ohci, "lost power\n");
		status = -EBUSY;
	पूर्ण
	अगर (status == -EBUSY) अणु
		अगर (!स्वतःstopped) अणु
			spin_unlock_irq (&ohci->lock);
			status = ohci_restart (ohci);

			usb_root_hub_lost_घातer(hcd->self.root_hub);

			spin_lock_irq (&ohci->lock);
		पूर्ण
		वापस status;
	पूर्ण
	अगर (status != -EINPROGRESS)
		वापस status;
	अगर (स्वतःstopped)
		जाओ skip_resume;
	spin_unlock_irq (&ohci->lock);

	/* Some controllers (lucent erratum) need extra-दीर्घ delays */
	msleep (20 /* usb 11.5.1.10 */ + 12 /* 32 msec counter */ + 1);

	temp = ohci_पढ़ोl (ohci, &ohci->regs->control);
	temp &= OHCI_CTRL_HCFS;
	अगर (temp != OHCI_USB_RESUME) अणु
		ohci_err (ohci, "controller won't resume\n");
		spin_lock_irq(&ohci->lock);
		वापस -EBUSY;
	पूर्ण

	/* disable old schedule state, reinit from scratch */
	ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_controlhead);
	ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_controlcurrent);
	ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_bulkhead);
	ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_bulkcurrent);
	ohci_ग_लिखोl (ohci, 0, &ohci->regs->ed_periodcurrent);
	ohci_ग_लिखोl (ohci, (u32) ohci->hcca_dma, &ohci->regs->hcca);

	/* Someबार PCI D3 suspend trashes frame timings ... */
	periodic_reinit (ohci);

	/*
	 * The following code is executed with ohci->lock held and
	 * irqs disabled अगर and only अगर स्वतःstopped is true.  This
	 * will cause sparse to warn about a "context imbalance".
	 */
skip_resume:
	/* पूर्णांकerrupts might have been disabled */
	ohci_ग_लिखोl (ohci, OHCI_INTR_INIT, &ohci->regs->पूर्णांकrenable);
	अगर (ohci->ed_rm_list)
		ohci_ग_लिखोl (ohci, OHCI_INTR_SF, &ohci->regs->पूर्णांकrenable);

	/* Then re-enable operations */
	ohci_ग_लिखोl (ohci, OHCI_USB_OPER, &ohci->regs->control);
	(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
	अगर (!स्वतःstopped)
		msleep (3);

	temp = ohci->hc_control;
	temp &= OHCI_CTRL_RWC;
	temp |= OHCI_CONTROL_INIT | OHCI_USB_OPER;
	ohci->hc_control = temp;
	ohci_ग_लिखोl (ohci, temp, &ohci->regs->control);
	(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);

	/* TRSMRCY */
	अगर (!स्वतःstopped) अणु
		msleep (10);
		spin_lock_irq (&ohci->lock);
	पूर्ण
	/* now ohci->lock is always held and irqs are always disabled */

	/* keep it alive क्रम more than ~5x suspend + resume costs */
	ohci->next_statechange = jअगरfies + STATECHANGE_DELAY;

	/* maybe turn schedules back on */
	enables = 0;
	temp = 0;
	अगर (!ohci->ed_rm_list) अणु
		अगर (ohci->ed_controltail) अणु
			ohci_ग_लिखोl (ohci,
					find_head (ohci->ed_controltail)->dma,
					&ohci->regs->ed_controlhead);
			enables |= OHCI_CTRL_CLE;
			temp |= OHCI_CLF;
		पूर्ण
		अगर (ohci->ed_bulktail) अणु
			ohci_ग_लिखोl (ohci, find_head (ohci->ed_bulktail)->dma,
				&ohci->regs->ed_bulkhead);
			enables |= OHCI_CTRL_BLE;
			temp |= OHCI_BLF;
		पूर्ण
	पूर्ण
	अगर (hcd->self.bandwidth_isoc_reqs || hcd->self.bandwidth_पूर्णांक_reqs)
		enables |= OHCI_CTRL_PLE|OHCI_CTRL_IE;
	अगर (enables) अणु
		ohci_dbg (ohci, "restarting schedules ... %08x\n", enables);
		ohci->hc_control |= enables;
		ohci_ग_लिखोl (ohci, ohci->hc_control, &ohci->regs->control);
		अगर (temp)
			ohci_ग_लिखोl (ohci, temp, &ohci->regs->cmdstatus);
		(व्योम) ohci_पढ़ोl (ohci, &ohci->regs->control);
	पूर्ण

	ohci->rh_state = OHCI_RH_RUNNING;
	वापस 0;
पूर्ण

अटल पूर्णांक ohci_bus_suspend (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci (hcd);
	पूर्णांक			rc;

	spin_lock_irq (&ohci->lock);

	अगर (unlikely(!HCD_HW_ACCESSIBLE(hcd)))
		rc = -ESHUTDOWN;
	अन्यथा
		rc = ohci_rh_suspend (ohci, 0);
	spin_unlock_irq (&ohci->lock);

	अगर (rc == 0) अणु
		del_समयr_sync(&ohci->io_watchकरोg);
		ohci->prev_frame_no = IO_WATCHDOG_OFF;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक ohci_bus_resume (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci (hcd);
	पूर्णांक			rc;

	अगर (समय_beक्रमe (jअगरfies, ohci->next_statechange))
		msleep(5);

	spin_lock_irq (&ohci->lock);

	अगर (unlikely(!HCD_HW_ACCESSIBLE(hcd)))
		rc = -ESHUTDOWN;
	अन्यथा
		rc = ohci_rh_resume (ohci);
	spin_unlock_irq (&ohci->lock);

	/* poll until we know a device is connected or we स्वतःstop */
	अगर (rc == 0)
		usb_hcd_poll_rh_status(hcd);
	वापस rc;
पूर्ण

/* Carry out polling-, स्वतःstop-, and स्वतःresume-related state changes */
अटल पूर्णांक ohci_root_hub_state_changes(काष्ठा ohci_hcd *ohci, पूर्णांक changed,
		पूर्णांक any_connected, पूर्णांक rhsc_status)
अणु
	पूर्णांक	poll_rh = 1;
	पूर्णांक	rhsc_enable;

	/* Some broken controllers never turn off RHSC in the पूर्णांकerrupt
	 * status रेजिस्टर.  For their sake we won't re-enable RHSC
	 * पूर्णांकerrupts अगर the पूर्णांकerrupt bit is alपढ़ोy active.
	 */
	rhsc_enable = ohci_पढ़ोl(ohci, &ohci->regs->पूर्णांकrenable) &
			OHCI_INTR_RHSC;

	चयन (ohci->hc_control & OHCI_CTRL_HCFS) अणु
	हाल OHCI_USB_OPER:
		/* If no status changes are pending, enable RHSC पूर्णांकerrupts. */
		अगर (!rhsc_enable && !rhsc_status && !changed) अणु
			rhsc_enable = OHCI_INTR_RHSC;
			ohci_ग_लिखोl(ohci, rhsc_enable, &ohci->regs->पूर्णांकrenable);
		पूर्ण

		/* Keep on polling until we know a device is connected
		 * and RHSC is enabled, or until we स्वतःstop.
		 */
		अगर (!ohci->स्वतःstop) अणु
			अगर (any_connected ||
					!device_may_wakeup(&ohci_to_hcd(ohci)
						->self.root_hub->dev)) अणु
				अगर (rhsc_enable)
					poll_rh = 0;
			पूर्ण अन्यथा अणु
				ohci->स्वतःstop = 1;
				ohci->next_statechange = jअगरfies + HZ;
			पूर्ण

		/* अगर no devices have been attached क्रम one second, स्वतःstop */
		पूर्ण अन्यथा अणु
			अगर (changed || any_connected) अणु
				ohci->स्वतःstop = 0;
				ohci->next_statechange = jअगरfies +
						STATECHANGE_DELAY;
			पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies,
						ohci->next_statechange)
					&& !ohci->ed_rm_list
					&& !(ohci->hc_control &
						OHCI_SCHED_ENABLES)) अणु
				ohci_rh_suspend(ohci, 1);
				अगर (rhsc_enable)
					poll_rh = 0;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल OHCI_USB_SUSPEND:
	हाल OHCI_USB_RESUME:
		/* अगर there is a port change, स्वतःstart or ask to be resumed */
		अगर (changed) अणु
			अगर (ohci->स्वतःstop)
				ohci_rh_resume(ohci);
			अन्यथा
				usb_hcd_resume_root_hub(ohci_to_hcd(ohci));

		/* If remote wakeup is disabled, stop polling */
		पूर्ण अन्यथा अगर (!ohci->स्वतःstop &&
				!ohci_to_hcd(ohci)->self.root_hub->
					करो_remote_wakeup) अणु
			poll_rh = 0;

		पूर्ण अन्यथा अणु
			/* If no status changes are pending,
			 * enable RHSC पूर्णांकerrupts
			 */
			अगर (!rhsc_enable && !rhsc_status) अणु
				rhsc_enable = OHCI_INTR_RHSC;
				ohci_ग_लिखोl(ohci, rhsc_enable,
						&ohci->regs->पूर्णांकrenable);
			पूर्ण
			/* Keep polling until RHSC is enabled */
			अगर (rhsc_enable)
				poll_rh = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस poll_rh;
पूर्ण

#अन्यथा	/* CONFIG_PM */

अटल अंतरभूत पूर्णांक ohci_rh_resume(काष्ठा ohci_hcd *ohci)
अणु
	वापस 0;
पूर्ण

/* Carry out polling-related state changes.
 * स्वतःstop isn't used when CONFIG_PM is turned off.
 */
अटल पूर्णांक ohci_root_hub_state_changes(काष्ठा ohci_hcd *ohci, पूर्णांक changed,
		पूर्णांक any_connected, पूर्णांक rhsc_status)
अणु
	/* If RHSC is enabled, करोn't poll */
	अगर (ohci_पढ़ोl(ohci, &ohci->regs->पूर्णांकrenable) & OHCI_INTR_RHSC)
		वापस 0;

	/* If status changes are pending, जारी polling.
	 * Conversely, अगर no status changes are pending but the RHSC
	 * status bit was set, then RHSC may be broken so जारी polling.
	 */
	अगर (changed || rhsc_status)
		वापस 1;

	/* It's safe to re-enable RHSC पूर्णांकerrupts */
	ohci_ग_लिखोl(ohci, OHCI_INTR_RHSC, &ohci->regs->पूर्णांकrenable);
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

/* build "status change" packet (one or two bytes) from HC रेजिस्टरs */

पूर्णांक ohci_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);
	पूर्णांक		i, changed = 0, length = 1;
	पूर्णांक		any_connected = 0;
	पूर्णांक		rhsc_status;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave (&ohci->lock, flags);
	अगर (!HCD_HW_ACCESSIBLE(hcd))
		जाओ करोne;

	/* unकरोcumented erratum seen on at least rev D */
	अगर ((ohci->flags & OHCI_QUIRK_AMD756)
			&& (roothub_a (ohci) & RH_A_NDP) > MAX_ROOT_PORTS) अणु
		ohci_warn (ohci, "bogus NDP, rereads as NDP=%d\n",
			  ohci_पढ़ोl (ohci, &ohci->regs->roothub.a) & RH_A_NDP);
		/* retry later; "should not happen" */
		जाओ करोne;
	पूर्ण

	/* init status */
	अगर (roothub_status (ohci) & (RH_HS_LPSC | RH_HS_OCIC))
		buf [0] = changed = 1;
	अन्यथा
		buf [0] = 0;
	अगर (ohci->num_ports > 7) अणु
		buf [1] = 0;
		length++;
	पूर्ण

	/* Clear the RHSC status flag beक्रमe पढ़ोing the port statuses */
	ohci_ग_लिखोl(ohci, OHCI_INTR_RHSC, &ohci->regs->पूर्णांकrstatus);
	rhsc_status = ohci_पढ़ोl(ohci, &ohci->regs->पूर्णांकrstatus) &
			OHCI_INTR_RHSC;

	/* look at each port */
	क्रम (i = 0; i < ohci->num_ports; i++) अणु
		u32	status = roothub_portstatus (ohci, i);

		/* can't स्वतःstop अगर ports are connected */
		any_connected |= (status & RH_PS_CCS);

		अगर (status & (RH_PS_CSC | RH_PS_PESC | RH_PS_PSSC
				| RH_PS_OCIC | RH_PS_PRSC)) अणु
			changed = 1;
			अगर (i < 7)
			    buf [0] |= 1 << (i + 1);
			अन्यथा
			    buf [1] |= 1 << (i - 7);
		पूर्ण
	पूर्ण

	अगर (ohci_root_hub_state_changes(ohci, changed,
			any_connected, rhsc_status))
		set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	अन्यथा
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);


करोne:
	spin_unlock_irqrestore (&ohci->lock, flags);

	वापस changed ? length : 0;
पूर्ण
EXPORT_SYMBOL_GPL(ohci_hub_status_data);

/*-------------------------------------------------------------------------*/

अटल व्योम
ohci_hub_descriptor (
	काष्ठा ohci_hcd			*ohci,
	काष्ठा usb_hub_descriptor	*desc
) अणु
	u32		rh = roothub_a (ohci);
	u16		temp;

	desc->bDescriptorType = USB_DT_HUB;
	desc->bPwrOn2PwrGood = (rh & RH_A_POTPGT) >> 24;
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ohci->num_ports;
	temp = 1 + (ohci->num_ports / 8);
	desc->bDescLength = 7 + 2 * temp;

	temp = HUB_CHAR_COMMON_LPSM | HUB_CHAR_COMMON_OCPM;
	अगर (rh & RH_A_NPS)		/* no घातer चयनing? */
		temp |= HUB_CHAR_NO_LPSM;
	अगर (rh & RH_A_PSM)		/* per-port घातer चयनing? */
		temp |= HUB_CHAR_INDV_PORT_LPSM;
	अगर (rh & RH_A_NOCP)		/* no overcurrent reporting? */
		temp |= HUB_CHAR_NO_OCPM;
	अन्यथा अगर (rh & RH_A_OCPM)	/* per-port overcurrent reporting? */
		temp |= HUB_CHAR_INDV_PORT_OCPM;
	desc->wHubCharacteristics = cpu_to_le16(temp);

	/* ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	rh = roothub_b (ohci);
	स_रखो(desc->u.hs.DeviceRemovable, 0xff,
			माप(desc->u.hs.DeviceRemovable));
	desc->u.hs.DeviceRemovable[0] = rh & RH_B_DR;
	अगर (ohci->num_ports > 7) अणु
		desc->u.hs.DeviceRemovable[1] = (rh & RH_B_DR) >> 8;
		desc->u.hs.DeviceRemovable[2] = 0xff;
	पूर्ण अन्यथा
		desc->u.hs.DeviceRemovable[1] = 0xff;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_USB_OTG

अटल पूर्णांक ohci_start_port_reset (काष्ठा usb_hcd *hcd, अचिन्हित port)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);
	u32			status;

	अगर (!port)
		वापस -EINVAL;
	port--;

	/* start port reset beक्रमe HNP protocol बार out */
	status = ohci_पढ़ोl(ohci, &ohci->regs->roothub.portstatus [port]);
	अगर (!(status & RH_PS_CCS))
		वापस -ENODEV;

	/* hub_wq will finish the reset later */
	ohci_ग_लिखोl(ohci, RH_PS_PRS, &ohci->regs->roothub.portstatus [port]);
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा	ohci_start_port_reset		शून्य

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/


/* See usb 7.1.7.5:  root hubs must issue at least 50 msec reset संकेतing,
 * not necessarily continuous ... to guard against resume संकेतing.
 */
#घोषणा	PORT_RESET_MSEC		50

/* this समयr value might be venकरोr-specअगरic ... */
#घोषणा	PORT_RESET_HW_MSEC	10

/* wrap-aware logic morphed from <linux/jअगरfies.h> */
#घोषणा tick_beक्रमe(t1,t2) ((s16)(((s16)(t1))-((s16)(t2))) < 0)

/* called from some task, normally hub_wq */
अटल अंतरभूत पूर्णांक root_port_reset (काष्ठा ohci_hcd *ohci, अचिन्हित port)
अणु
	__hc32 __iomem *portstat = &ohci->regs->roothub.portstatus [port];
	u32	temp = 0;
	u16	now = ohci_पढ़ोl(ohci, &ohci->regs->fmnumber);
	u16	reset_करोne = now + PORT_RESET_MSEC;
	पूर्णांक	limit_1 = DIV_ROUND_UP(PORT_RESET_MSEC, PORT_RESET_HW_MSEC);

	/* build a "continuous enough" reset संकेत, with up to
	 * 3msec gap between pulses.  scheduler HZ==100 must work;
	 * this might need to be deadline-scheduled.
	 */
	करो अणु
		पूर्णांक limit_2;

		/* spin until any current reset finishes */
		limit_2 = PORT_RESET_HW_MSEC * 2;
		जबतक (--limit_2 >= 0) अणु
			temp = ohci_पढ़ोl (ohci, portstat);
			/* handle e.g. CardBus eject */
			अगर (temp == ~(u32)0)
				वापस -ESHUTDOWN;
			अगर (!(temp & RH_PS_PRS))
				अवरोध;
			udelay (500);
		पूर्ण

		/* समयout (a hardware error) has been observed when
		 * EHCI sets CF जबतक this driver is resetting a port;
		 * presumably other disconnect paths might करो it too.
		 */
		अगर (limit_2 < 0) अणु
			ohci_dbg(ohci,
				"port[%d] reset timeout, stat %08x\n",
				port, temp);
			अवरोध;
		पूर्ण

		अगर (!(temp & RH_PS_CCS))
			अवरोध;
		अगर (temp & RH_PS_PRSC)
			ohci_ग_लिखोl (ohci, RH_PS_PRSC, portstat);

		/* start the next reset, sleep till it's probably करोne */
		ohci_ग_लिखोl (ohci, RH_PS_PRS, portstat);
		msleep(PORT_RESET_HW_MSEC);
		now = ohci_पढ़ोl(ohci, &ohci->regs->fmnumber);
	पूर्ण जबतक (tick_beक्रमe(now, reset_करोne) && --limit_1 >= 0);

	/* caller synchronizes using PRSC ... and handles PRS
	 * still being set when this वापसs.
	 */

	वापस 0;
पूर्ण

पूर्णांक ohci_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength
) अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);
	पूर्णांक		ports = ohci->num_ports;
	u32		temp;
	पूर्णांक		retval = 0;

	अगर (unlikely(!HCD_HW_ACCESSIBLE(hcd)))
		वापस -ESHUTDOWN;

	चयन (typeReq) अणु
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
			ohci_ग_लिखोl (ohci, RH_HS_OCIC,
					&ohci->regs->roothub.status);
			अवरोध;
		हाल C_HUB_LOCAL_POWER:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			temp = RH_PS_CCS;
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			temp = RH_PS_PESC;
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			temp = RH_PS_POCI;
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			temp = RH_PS_PSSC;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			temp = RH_PS_LSDA;
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			temp = RH_PS_CSC;
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			temp = RH_PS_OCIC;
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			temp = RH_PS_PRSC;
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		ohci_ग_लिखोl (ohci, temp,
				&ohci->regs->roothub.portstatus [wIndex]);
		// ohci_पढ़ोl (ohci, &ohci->regs->roothub.portstatus [wIndex]);
		अवरोध;
	हाल GetHubDescriptor:
		ohci_hub_descriptor (ohci, (काष्ठा usb_hub_descriptor *) buf);
		अवरोध;
	हाल GetHubStatus:
		temp = roothub_status (ohci) & ~(RH_HS_CRWE | RH_HS_DRWE);
		put_unaligned_le32(temp, buf);
		अवरोध;
	हाल GetPortStatus:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = roothub_portstatus (ohci, wIndex);
		put_unaligned_le32(temp, buf);

		अगर (*(u16*)(buf+2))	/* only अगर wPortChange is पूर्णांकeresting */
			dbg_port(ohci, "GetStatus", wIndex, temp);
		अवरोध;
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
			// FIXME:  this can be cleared, yes?
		हाल C_HUB_LOCAL_POWER:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
#अगर_घोषित	CONFIG_USB_OTG
			अगर (hcd->self.otg_port == (wIndex + 1)
					&& hcd->self.b_hnp_enable)
				ohci->start_hnp(ohci);
			अन्यथा
#पूर्ण_अगर
			ohci_ग_लिखोl (ohci, RH_PS_PSS,
				&ohci->regs->roothub.portstatus [wIndex]);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			ohci_ग_लिखोl (ohci, RH_PS_PPS,
				&ohci->regs->roothub.portstatus [wIndex]);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			retval = root_port_reset (ohci, wIndex);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;

	शेष:
error:
		/* "protocol stall" on error */
		retval = -EPIPE;
	पूर्ण
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(ohci_hub_control);
