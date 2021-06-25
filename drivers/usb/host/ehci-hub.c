<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2001-2004 by David Brownell
 */

/* this file is part of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * EHCI Root Hub ... the nonsharable stuff
 *
 * Registers करोn't need cpu_to_le32, that happens transparently
 */

/*-------------------------------------------------------------------------*/

#घोषणा	PORT_WAKE_BITS	(PORT_WKOC_E|PORT_WKDISC_E|PORT_WKCONN_E)

#अगर_घोषित	CONFIG_PM

अटल व्योम unlink_empty_async_suspended(काष्ठा ehci_hcd *ehci);

अटल पूर्णांक persist_enabled_on_companion(काष्ठा usb_device *udev, व्योम *unused)
अणु
	वापस !udev->maxchild && udev->persist_enabled &&
		udev->bus->root_hub->speed < USB_SPEED_HIGH;
पूर्ण

/* After a घातer loss, ports that were owned by the companion must be
 * reset so that the companion can still own them.
 */
अटल व्योम ehci_hanकरोver_companion_ports(काष्ठा ehci_hcd *ehci)
अणु
	u32 __iomem	*reg;
	u32		status;
	पूर्णांक		port;
	__le32		buf;
	काष्ठा usb_hcd	*hcd = ehci_to_hcd(ehci);

	अगर (!ehci->owned_ports)
		वापस;

	/*
	 * USB 1.1 devices are mostly HIDs, which करोn't need to persist across
	 * suspends. If we ensure that none of our companion's devices have
	 * persist_enabled (by looking through all USB 1.1 buses in the प्रणाली),
	 * we can skip this and aव्योम slowing resume करोwn. Devices without
	 * persist will just get reक्रमागतerated लघुly after resume anyway.
	 */
	अगर (!usb_क्रम_each_dev(शून्य, persist_enabled_on_companion))
		वापस;

	/* Make sure the ports are घातered */
	port = HCS_N_PORTS(ehci->hcs_params);
	जबतक (port--) अणु
		अगर (test_bit(port, &ehci->owned_ports)) अणु
			reg = &ehci->regs->port_status[port];
			status = ehci_पढ़ोl(ehci, reg) & ~PORT_RWC_BITS;
			अगर (!(status & PORT_POWER))
				ehci_port_घातer(ehci, port, true);
		पूर्ण
	पूर्ण

	/* Give the connections some समय to appear */
	msleep(20);

	spin_lock_irq(&ehci->lock);
	port = HCS_N_PORTS(ehci->hcs_params);
	जबतक (port--) अणु
		अगर (test_bit(port, &ehci->owned_ports)) अणु
			reg = &ehci->regs->port_status[port];
			status = ehci_पढ़ोl(ehci, reg) & ~PORT_RWC_BITS;

			/* Port alपढ़ोy owned by companion? */
			अगर (status & PORT_OWNER)
				clear_bit(port, &ehci->owned_ports);
			अन्यथा अगर (test_bit(port, &ehci->companion_ports))
				ehci_ग_लिखोl(ehci, status & ~PORT_PE, reg);
			अन्यथा अणु
				spin_unlock_irq(&ehci->lock);
				ehci_hub_control(hcd, SetPortFeature,
						USB_PORT_FEAT_RESET, port + 1,
						शून्य, 0);
				spin_lock_irq(&ehci->lock);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ehci->lock);

	अगर (!ehci->owned_ports)
		वापस;
	msleep(90);		/* Wait क्रम resets to complete */

	spin_lock_irq(&ehci->lock);
	port = HCS_N_PORTS(ehci->hcs_params);
	जबतक (port--) अणु
		अगर (test_bit(port, &ehci->owned_ports)) अणु
			spin_unlock_irq(&ehci->lock);
			ehci_hub_control(hcd, GetPortStatus,
					0, port + 1,
					(अक्षर *) &buf, माप(buf));
			spin_lock_irq(&ehci->lock);

			/* The companion should now own the port,
			 * but अगर something went wrong the port must not
			 * reमुख्य enabled.
			 */
			reg = &ehci->regs->port_status[port];
			status = ehci_पढ़ोl(ehci, reg) & ~PORT_RWC_BITS;
			अगर (status & PORT_OWNER)
				ehci_ग_लिखोl(ehci, status | PORT_CSC, reg);
			अन्यथा अणु
				ehci_dbg(ehci, "failed handover port %d: %x\n",
						port + 1, status);
				ehci_ग_लिखोl(ehci, status & ~PORT_PE, reg);
			पूर्ण
		पूर्ण
	पूर्ण

	ehci->owned_ports = 0;
	spin_unlock_irq(&ehci->lock);
पूर्ण

अटल पूर्णांक ehci_port_change(काष्ठा ehci_hcd *ehci)
अणु
	पूर्णांक i = HCS_N_PORTS(ehci->hcs_params);

	/* First check अगर the controller indicates a change event */

	अगर (ehci_पढ़ोl(ehci, &ehci->regs->status) & STS_PCD)
		वापस 1;

	/*
	 * Not all controllers appear to update this जबतक going from D3 to D0,
	 * so check the inभागidual port status रेजिस्टरs as well
	 */

	जबतक (i--)
		अगर (ehci_पढ़ोl(ehci, &ehci->regs->port_status[i]) & PORT_CSC)
			वापस 1;

	वापस 0;
पूर्ण

व्योम ehci_adjust_port_wakeup_flags(काष्ठा ehci_hcd *ehci,
		bool suspending, bool करो_wakeup)
अणु
	पूर्णांक		port;
	u32		temp;

	/* If remote wakeup is enabled क्रम the root hub but disabled
	 * क्रम the controller, we must adjust all the port wakeup flags
	 * when the controller is suspended or resumed.  In all other
	 * हालs they करोn't need to be changed.
	 */
	अगर (!ehci_to_hcd(ehci)->self.root_hub->करो_remote_wakeup || करो_wakeup)
		वापस;

	spin_lock_irq(&ehci->lock);

	/* clear phy low-घातer mode beक्रमe changing wakeup flags */
	अगर (ehci->has_tdi_phy_lpm) अणु
		port = HCS_N_PORTS(ehci->hcs_params);
		जबतक (port--) अणु
			u32 __iomem	*hostpc_reg = &ehci->regs->hostpc[port];

			temp = ehci_पढ़ोl(ehci, hostpc_reg);
			ehci_ग_लिखोl(ehci, temp & ~HOSTPC_PHCD, hostpc_reg);
		पूर्ण
		spin_unlock_irq(&ehci->lock);
		msleep(5);
		spin_lock_irq(&ehci->lock);
	पूर्ण

	port = HCS_N_PORTS(ehci->hcs_params);
	जबतक (port--) अणु
		u32 __iomem	*reg = &ehci->regs->port_status[port];
		u32		t1 = ehci_पढ़ोl(ehci, reg) & ~PORT_RWC_BITS;
		u32		t2 = t1 & ~PORT_WAKE_BITS;

		/* If we are suspending the controller, clear the flags.
		 * If we are resuming the controller, set the wakeup flags.
		 */
		अगर (!suspending) अणु
			अगर (t1 & PORT_CONNECT)
				t2 |= PORT_WKOC_E | PORT_WKDISC_E;
			अन्यथा
				t2 |= PORT_WKOC_E | PORT_WKCONN_E;
		पूर्ण
		ehci_ग_लिखोl(ehci, t2, reg);
	पूर्ण

	/* enter phy low-घातer mode again */
	अगर (ehci->has_tdi_phy_lpm) अणु
		port = HCS_N_PORTS(ehci->hcs_params);
		जबतक (port--) अणु
			u32 __iomem	*hostpc_reg = &ehci->regs->hostpc[port];

			temp = ehci_पढ़ोl(ehci, hostpc_reg);
			ehci_ग_लिखोl(ehci, temp | HOSTPC_PHCD, hostpc_reg);
		पूर्ण
	पूर्ण

	/* Does the root hub have a port wakeup pending? */
	अगर (!suspending && ehci_port_change(ehci))
		usb_hcd_resume_root_hub(ehci_to_hcd(ehci));

	spin_unlock_irq(&ehci->lock);
पूर्ण
EXPORT_SYMBOL_GPL(ehci_adjust_port_wakeup_flags);

अटल पूर्णांक ehci_bus_suspend (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	पूर्णांक			port;
	पूर्णांक			mask;
	पूर्णांक			changed;
	bool			fs_idle_delay;

	ehci_dbg(ehci, "suspend root hub\n");

	अगर (समय_beक्रमe (jअगरfies, ehci->next_statechange))
		msleep(5);

	/* stop the schedules */
	ehci_quiesce(ehci);

	spin_lock_irq (&ehci->lock);
	अगर (ehci->rh_state < EHCI_RH_RUNNING)
		जाओ करोne;

	/* Once the controller is stopped, port resumes that are alपढ़ोy
	 * in progress won't complete.  Hence अगर remote wakeup is enabled
	 * क्रम the root hub and any ports are in the middle of a resume or
	 * remote wakeup, we must fail the suspend.
	 */
	अगर (hcd->self.root_hub->करो_remote_wakeup) अणु
		अगर (ehci->resuming_ports) अणु
			spin_unlock_irq(&ehci->lock);
			ehci_dbg(ehci, "suspend failed because a port is resuming\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Unlike other USB host controller types, EHCI करोesn't have
	 * any notion of "global" or bus-wide suspend.  The driver has
	 * to manually suspend all the active unsuspended ports, and
	 * then manually resume them in the bus_resume() routine.
	 */
	ehci->bus_suspended = 0;
	ehci->owned_ports = 0;
	changed = 0;
	fs_idle_delay = false;
	port = HCS_N_PORTS(ehci->hcs_params);
	जबतक (port--) अणु
		u32 __iomem	*reg = &ehci->regs->port_status [port];
		u32		t1 = ehci_पढ़ोl(ehci, reg) & ~PORT_RWC_BITS;
		u32		t2 = t1 & ~PORT_WAKE_BITS;

		/* keep track of which ports we suspend */
		अगर (t1 & PORT_OWNER)
			set_bit(port, &ehci->owned_ports);
		अन्यथा अगर ((t1 & PORT_PE) && !(t1 & PORT_SUSPEND)) अणु
			t2 |= PORT_SUSPEND;
			set_bit(port, &ehci->bus_suspended);
		पूर्ण

		/* enable remote wakeup on all ports, अगर told to करो so */
		अगर (hcd->self.root_hub->करो_remote_wakeup) अणु
			/* only enable appropriate wake bits, otherwise the
			 * hardware can not go phy low घातer mode. If a race
			 * condition happens here(connection change during bits
			 * set), the port change detection will finally fix it.
			 */
			अगर (t1 & PORT_CONNECT)
				t2 |= PORT_WKOC_E | PORT_WKDISC_E;
			अन्यथा
				t2 |= PORT_WKOC_E | PORT_WKCONN_E;
		पूर्ण

		अगर (t1 != t2) अणु
			/*
			 * On some controllers, Wake-On-Disconnect will
			 * generate false wakeup संकेतs until the bus
			 * चयनes over to full-speed idle.  For their
			 * sake, add a delay अगर we need one.
			 */
			अगर ((t2 & PORT_WKDISC_E) &&
					ehci_port_speed(ehci, t2) ==
						USB_PORT_STAT_HIGH_SPEED)
				fs_idle_delay = true;
			ehci_ग_लिखोl(ehci, t2, reg);
			changed = 1;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ehci->lock);

	अगर (changed && ehci_has_fsl_susp_errata(ehci))
		/*
		 * Wait क्रम at least 10 millisecondes to ensure the controller
		 * enter the suspend status beक्रमe initiating a port resume
		 * using the Force Port Resume bit (Not-EHCI compatible).
		 */
		usleep_range(10000, 20000);

	अगर ((changed && ehci->has_tdi_phy_lpm) || fs_idle_delay) अणु
		/*
		 * Wait क्रम HCD to enter low-घातer mode or क्रम the bus
		 * to चयन to full-speed idle.
		 */
		usleep_range(5000, 5500);
	पूर्ण

	अगर (changed && ehci->has_tdi_phy_lpm) अणु
		spin_lock_irq(&ehci->lock);
		port = HCS_N_PORTS(ehci->hcs_params);
		जबतक (port--) अणु
			u32 __iomem	*hostpc_reg = &ehci->regs->hostpc[port];
			u32		t3;

			t3 = ehci_पढ़ोl(ehci, hostpc_reg);
			ehci_ग_लिखोl(ehci, t3 | HOSTPC_PHCD, hostpc_reg);
			t3 = ehci_पढ़ोl(ehci, hostpc_reg);
			ehci_dbg(ehci, "Port %d phy low-power mode %s\n",
					port, (t3 & HOSTPC_PHCD) ?
					"succeeded" : "failed");
		पूर्ण
		spin_unlock_irq(&ehci->lock);
	पूर्ण

	/* Apparently some devices need a >= 1-uframe delay here */
	अगर (ehci->bus_suspended)
		udelay(150);

	/* turn off now-idle HC */
	ehci_halt (ehci);

	spin_lock_irq(&ehci->lock);
	अगर (ehci->enabled_hrसमयr_events & BIT(EHCI_HRTIMER_POLL_DEAD))
		ehci_handle_controller_death(ehci);
	अगर (ehci->rh_state != EHCI_RH_RUNNING)
		जाओ करोne;
	ehci->rh_state = EHCI_RH_SUSPENDED;

	unlink_empty_async_suspended(ehci);

	/* Some Synopsys controllers mistakenly leave IAA turned on */
	ehci_ग_लिखोl(ehci, STS_IAA, &ehci->regs->status);

	/* Any IAA cycle that started beक्रमe the suspend is now invalid */
	end_iaa_cycle(ehci);
	ehci_handle_start_पूर्णांकr_unlinks(ehci);
	ehci_handle_पूर्णांकr_unlinks(ehci);
	end_मुक्त_itds(ehci);

	/* allow remote wakeup */
	mask = INTR_MASK;
	अगर (!hcd->self.root_hub->करो_remote_wakeup)
		mask &= ~STS_PCD;
	ehci_ग_लिखोl(ehci, mask, &ehci->regs->पूर्णांकr_enable);
	ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable);

 करोne:
	ehci->next_statechange = jअगरfies + msecs_to_jअगरfies(10);
	ehci->enabled_hrसमयr_events = 0;
	ehci->next_hrसमयr_event = EHCI_HRTIMER_NO_EVENT;
	spin_unlock_irq (&ehci->lock);

	hrसमयr_cancel(&ehci->hrसमयr);
	वापस 0;
पूर्ण


/* caller has locked the root hub, and should reset/reinit on error */
अटल पूर्णांक ehci_bus_resume (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			temp;
	u32			घातer_okay;
	पूर्णांक			i;
	अचिन्हित दीर्घ		resume_needed = 0;

	अगर (समय_beक्रमe (jअगरfies, ehci->next_statechange))
		msleep(5);
	spin_lock_irq (&ehci->lock);
	अगर (!HCD_HW_ACCESSIBLE(hcd) || ehci->shutकरोwn)
		जाओ shutकरोwn;

	अगर (unlikely(ehci->debug)) अणु
		अगर (!dbgp_reset_prep(hcd))
			ehci->debug = शून्य;
		अन्यथा
			dbgp_बाह्यal_startup(hcd);
	पूर्ण

	/* Ideally and we've got a real resume here, and no port's घातer
	 * was lost.  (For PCI, that means Vaux was मुख्यtained.)  But we
	 * could instead be restoring a swsusp snapshot -- so that BIOS was
	 * the last user of the controller, not reset/pm hardware keeping
	 * state we gave to it.
	 */
	घातer_okay = ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable);
	ehci_dbg(ehci, "resume root hub%s\n",
			घातer_okay ? "" : " after power loss");

	/* at least some APM implementations will try to deliver
	 * IRQs right away, so delay them until we're पढ़ोy.
	 */
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->पूर्णांकr_enable);

	/* re-init operational रेजिस्टरs */
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->segment);
	ehci_ग_लिखोl(ehci, ehci->periodic_dma, &ehci->regs->frame_list);
	ehci_ग_लिखोl(ehci, (u32) ehci->async->qh_dma, &ehci->regs->async_next);

	/* restore CMD_RUN, framelist size, and irq threshold */
	ehci->command |= CMD_RUN;
	ehci_ग_लिखोl(ehci, ehci->command, &ehci->regs->command);
	ehci->rh_state = EHCI_RH_RUNNING;

	/*
	 * According to Bugzilla #8190, the port status क्रम some controllers
	 * will be wrong without a delay. At their wrong status, the port
	 * is enabled, but not suspended neither resumed.
	 */
	i = HCS_N_PORTS(ehci->hcs_params);
	जबतक (i--) अणु
		temp = ehci_पढ़ोl(ehci, &ehci->regs->port_status[i]);
		अगर ((temp & PORT_PE) &&
				!(temp & (PORT_SUSPEND | PORT_RESUME))) अणु
			ehci_dbg(ehci, "Port status(0x%x) is wrong\n", temp);
			spin_unlock_irq(&ehci->lock);
			msleep(8);
			spin_lock_irq(&ehci->lock);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ehci->shutकरोwn)
		जाओ shutकरोwn;

	/* clear phy low-घातer mode beक्रमe resume */
	अगर (ehci->bus_suspended && ehci->has_tdi_phy_lpm) अणु
		i = HCS_N_PORTS(ehci->hcs_params);
		जबतक (i--) अणु
			अगर (test_bit(i, &ehci->bus_suspended)) अणु
				u32 __iomem	*hostpc_reg =
							&ehci->regs->hostpc[i];

				temp = ehci_पढ़ोl(ehci, hostpc_reg);
				ehci_ग_लिखोl(ehci, temp & ~HOSTPC_PHCD,
						hostpc_reg);
			पूर्ण
		पूर्ण
		spin_unlock_irq(&ehci->lock);
		msleep(5);
		spin_lock_irq(&ehci->lock);
		अगर (ehci->shutकरोwn)
			जाओ shutकरोwn;
	पूर्ण

	/* manually resume the ports we suspended during bus_suspend() */
	i = HCS_N_PORTS (ehci->hcs_params);
	जबतक (i--) अणु
		temp = ehci_पढ़ोl(ehci, &ehci->regs->port_status [i]);
		temp &= ~(PORT_RWC_BITS | PORT_WAKE_BITS);
		अगर (test_bit(i, &ehci->bus_suspended) &&
				(temp & PORT_SUSPEND)) अणु
			temp |= PORT_RESUME;
			set_bit(i, &resume_needed);
		पूर्ण
		ehci_ग_लिखोl(ehci, temp, &ehci->regs->port_status [i]);
	पूर्ण

	/*
	 * msleep क्रम USB_RESUME_TIMEOUT ms only अगर code is trying to resume
	 * port
	 */
	अगर (resume_needed) अणु
		spin_unlock_irq(&ehci->lock);
		msleep(USB_RESUME_TIMEOUT);
		spin_lock_irq(&ehci->lock);
		अगर (ehci->shutकरोwn)
			जाओ shutकरोwn;
	पूर्ण

	i = HCS_N_PORTS (ehci->hcs_params);
	जबतक (i--) अणु
		temp = ehci_पढ़ोl(ehci, &ehci->regs->port_status [i]);
		अगर (test_bit(i, &resume_needed)) अणु
			temp &= ~(PORT_RWC_BITS | PORT_SUSPEND | PORT_RESUME);
			ehci_ग_लिखोl(ehci, temp, &ehci->regs->port_status [i]);
		पूर्ण
	पूर्ण

	ehci->next_statechange = jअगरfies + msecs_to_jअगरfies(5);
	spin_unlock_irq(&ehci->lock);

	ehci_hanकरोver_companion_ports(ehci);

	/* Now we can safely re-enable irqs */
	spin_lock_irq(&ehci->lock);
	अगर (ehci->shutकरोwn)
		जाओ shutकरोwn;
	ehci_ग_लिखोl(ehci, INTR_MASK, &ehci->regs->पूर्णांकr_enable);
	(व्योम) ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable);
	spin_unlock_irq(&ehci->lock);

	वापस 0;

 shutकरोwn:
	spin_unlock_irq(&ehci->lock);
	वापस -ESHUTDOWN;
पूर्ण

अटल अचिन्हित दीर्घ ehci_get_resuming_ports(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);

	वापस ehci->resuming_ports;
पूर्ण

#अन्यथा

#घोषणा ehci_bus_suspend	शून्य
#घोषणा ehci_bus_resume		शून्य
#घोषणा ehci_get_resuming_ports	शून्य

#पूर्ण_अगर	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

/*
 * Sets the owner of a port
 */
अटल व्योम set_owner(काष्ठा ehci_hcd *ehci, पूर्णांक portnum, पूर्णांक new_owner)
अणु
	u32 __iomem		*status_reg;
	u32			port_status;
	पूर्णांक 			try;

	status_reg = &ehci->regs->port_status[portnum];

	/*
	 * The controller won't set the OWNER bit अगर the port is
	 * enabled, so this loop will someबार require at least two
	 * iterations: one to disable the port and one to set OWNER.
	 */
	क्रम (try = 4; try > 0; --try) अणु
		spin_lock_irq(&ehci->lock);
		port_status = ehci_पढ़ोl(ehci, status_reg);
		अगर ((port_status & PORT_OWNER) == new_owner
				|| (port_status & (PORT_OWNER | PORT_CONNECT))
					== 0)
			try = 0;
		अन्यथा अणु
			port_status ^= PORT_OWNER;
			port_status &= ~(PORT_PE | PORT_RWC_BITS);
			ehci_ग_लिखोl(ehci, port_status, status_reg);
		पूर्ण
		spin_unlock_irq(&ehci->lock);
		अगर (try > 1)
			msleep(5);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक check_reset_complete (
	काष्ठा ehci_hcd	*ehci,
	पूर्णांक		index,
	u32 __iomem	*status_reg,
	पूर्णांक		port_status
) अणु
	अगर (!(port_status & PORT_CONNECT))
		वापस port_status;

	/* अगर reset finished and it's still not enabled -- hanकरोff */
	अगर (!(port_status & PORT_PE)) अणु

		/* with पूर्णांकegrated TT, there's nobody to hand it to! */
		अगर (ehci_is_TDI(ehci)) अणु
			ehci_dbg (ehci,
				"Failed to enable port %d on root hub TT\n",
				index+1);
			वापस port_status;
		पूर्ण

		ehci_dbg (ehci, "port %d full speed --> companion\n",
			index + 1);

		// what happens अगर HCS_N_CC(params) == 0 ?
		port_status |= PORT_OWNER;
		port_status &= ~PORT_RWC_BITS;
		ehci_ग_लिखोl(ehci, port_status, status_reg);

		/* ensure 440EPX ohci controller state is operational */
		अगर (ehci->has_amcc_usb23)
			set_ohci_hcfs(ehci, 1);
	पूर्ण अन्यथा अणु
		ehci_dbg(ehci, "port %d reset complete, port enabled\n",
			index + 1);
		/* ensure 440EPx ohci controller state is suspended */
		अगर (ehci->has_amcc_usb23)
			set_ohci_hcfs(ehci, 0);
	पूर्ण

	वापस port_status;
पूर्ण

/*-------------------------------------------------------------------------*/


/* build "status change" packet (one or two bytes) from HC रेजिस्टरs */

अटल पूर्णांक
ehci_hub_status_data (काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा ehci_hcd	*ehci = hcd_to_ehci (hcd);
	u32		temp, status;
	u32		mask;
	पूर्णांक		ports, i, retval = 1;
	अचिन्हित दीर्घ	flags;
	u32		ppcd = ~0;

	/* init status to no-changes */
	buf [0] = 0;
	ports = HCS_N_PORTS (ehci->hcs_params);
	अगर (ports > 7) अणु
		buf [1] = 0;
		retval++;
	पूर्ण

	/* Inक्रमm the core about resumes-in-progress by वापसing
	 * a non-zero value even अगर there are no status changes.
	 */
	status = ehci->resuming_ports;

	/* Some boards (mostly VIA?) report bogus overcurrent indications,
	 * causing massive log spam unless we completely ignore them.  It
	 * may be relevant that VIA VT8235 controllers, where PORT_POWER is
	 * always set, seem to clear PORT_OCC and PORT_CSC when writing to
	 * PORT_POWER; that's surprising, but maybe within-spec.
	 */
	अगर (!ignore_oc && !ehci->spurious_oc)
		mask = PORT_CSC | PORT_PEC | PORT_OCC;
	अन्यथा
		mask = PORT_CSC | PORT_PEC;
	// PORT_RESUME from hardware ~= PORT_STAT_C_SUSPEND

	/* no hub change reports (bit 0) क्रम now (घातer, ...) */

	/* port N changes (bit N)? */
	spin_lock_irqsave (&ehci->lock, flags);

	/* get per-port change detect bits */
	अगर (ehci->has_ppcd)
		ppcd = ehci_पढ़ोl(ehci, &ehci->regs->status) >> 16;

	क्रम (i = 0; i < ports; i++) अणु
		/* leverage per-port change bits feature */
		अगर (ppcd & (1 << i))
			temp = ehci_पढ़ोl(ehci, &ehci->regs->port_status[i]);
		अन्यथा
			temp = 0;

		/*
		 * Return status inक्रमmation even क्रम ports with OWNER set.
		 * Otherwise hub_wq wouldn't see the disconnect event when a
		 * high-speed device is चयनed over to the companion
		 * controller by the user.
		 */

		अगर ((temp & mask) != 0 || test_bit(i, &ehci->port_c_suspend)
				|| (ehci->reset_करोne[i] && समय_after_eq(
					jअगरfies, ehci->reset_करोne[i]))) अणु
			अगर (i < 7)
			    buf [0] |= 1 << (i + 1);
			अन्यथा
			    buf [1] |= 1 << (i - 7);
			status = STS_PCD;
		पूर्ण
	पूर्ण

	/* If a resume is in progress, make sure it can finish */
	अगर (ehci->resuming_ports)
		mod_समयr(&hcd->rh_समयr, jअगरfies + msecs_to_jअगरfies(25));

	spin_unlock_irqrestore (&ehci->lock, flags);
	वापस status ? retval : 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम
ehci_hub_descriptor (
	काष्ठा ehci_hcd			*ehci,
	काष्ठा usb_hub_descriptor	*desc
) अणु
	पूर्णांक		ports = HCS_N_PORTS (ehci->hcs_params);
	u16		temp;

	desc->bDescriptorType = USB_DT_HUB;
	desc->bPwrOn2PwrGood = 10;	/* ehci 1.0, 2.3.9 says 20ms max */
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 1 + (ports / 8);
	desc->bDescLength = 7 + 2 * temp;

	/* two biपंचांगaps:  ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	स_रखो(&desc->u.hs.DeviceRemovable[0], 0, temp);
	स_रखो(&desc->u.hs.DeviceRemovable[temp], 0xff, temp);

	temp = HUB_CHAR_INDV_PORT_OCPM;	/* per-port overcurrent reporting */
	अगर (HCS_PPC (ehci->hcs_params))
		temp |= HUB_CHAR_INDV_PORT_LPSM; /* per-port घातer control */
	अन्यथा
		temp |= HUB_CHAR_NO_LPSM; /* no घातer चयनing */
#अगर 0
// re-enable when we support USB_PORT_FEAT_INDICATOR below.
	अगर (HCS_INDICATOR (ehci->hcs_params))
		temp |= HUB_CHAR_PORTIND; /* per-port indicators (LEDs) */
#पूर्ण_अगर
	desc->wHubCharacteristics = cpu_to_le16(temp);
पूर्ण

/*-------------------------------------------------------------------------*/
#अगर_घोषित CONFIG_USB_HCD_TEST_MODE

#घोषणा EHSET_TEST_SINGLE_STEP_SET_FEATURE 0x06

अटल व्योम usb_ehset_completion(काष्ठा urb *urb)
अणु
	काष्ठा completion  *करोne = urb->context;

	complete(करोne);
पूर्ण
अटल पूर्णांक submit_single_step_set_feature(
	काष्ठा usb_hcd	*hcd,
	काष्ठा urb	*urb,
	पूर्णांक		is_setup
);

/*
 * Allocate and initialize a control URB. This request will be used by the
 * EHSET SINGLE_STEP_SET_FEATURE test in which the DATA and STATUS stages
 * of the GetDescriptor request are sent 15 seconds after the SETUP stage.
 * Return शून्य अगर failed.
 */
अटल काष्ठा urb *request_single_step_set_feature_urb(
	काष्ठा usb_device	*udev,
	व्योम			*dr,
	व्योम			*buf,
	काष्ठा completion	*करोne
) अणु
	काष्ठा urb *urb;
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);
	काष्ठा usb_host_endpoपूर्णांक *ep;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस शून्य;

	urb->pipe = usb_rcvctrlpipe(udev, 0);
	ep = (usb_pipein(urb->pipe) ? udev->ep_in : udev->ep_out)
				[usb_pipeendpoपूर्णांक(urb->pipe)];
	अगर (!ep) अणु
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण

	urb->ep = ep;
	urb->dev = udev;
	urb->setup_packet = (व्योम *)dr;
	urb->transfer_buffer = buf;
	urb->transfer_buffer_length = USB_DT_DEVICE_SIZE;
	urb->complete = usb_ehset_completion;
	urb->status = -EINPROGRESS;
	urb->actual_length = 0;
	urb->transfer_flags = URB_सूची_IN;
	usb_get_urb(urb);
	atomic_inc(&urb->use_count);
	atomic_inc(&urb->dev->urbnum);
	urb->setup_dma = dma_map_single(
			hcd->self.sysdev,
			urb->setup_packet,
			माप(काष्ठा usb_ctrlrequest),
			DMA_TO_DEVICE);
	urb->transfer_dma = dma_map_single(
			hcd->self.sysdev,
			urb->transfer_buffer,
			urb->transfer_buffer_length,
			DMA_FROM_DEVICE);
	urb->context = करोne;
	वापस urb;
पूर्ण

अटल पूर्णांक ehset_single_step_set_feature(काष्ठा usb_hcd *hcd, पूर्णांक port)
अणु
	पूर्णांक retval = -ENOMEM;
	काष्ठा usb_ctrlrequest *dr;
	काष्ठा urb *urb;
	काष्ठा usb_device *udev;
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	काष्ठा usb_device_descriptor *buf;
	DECLARE_COMPLETION_ONSTACK(करोne);

	/* Obtain udev of the rhub's child port */
	udev = usb_hub_find_child(hcd->self.root_hub, port);
	अगर (!udev) अणु
		ehci_err(ehci, "No device attached to the RootHub\n");
		वापस -ENODEV;
	पूर्ण
	buf = kदो_स्मृति(USB_DT_DEVICE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	dr = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_KERNEL);
	अगर (!dr) अणु
		kमुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	/* Fill Setup packet क्रम GetDescriptor */
	dr->bRequestType = USB_सूची_IN;
	dr->bRequest = USB_REQ_GET_DESCRIPTOR;
	dr->wValue = cpu_to_le16(USB_DT_DEVICE << 8);
	dr->wIndex = 0;
	dr->wLength = cpu_to_le16(USB_DT_DEVICE_SIZE);
	urb = request_single_step_set_feature_urb(udev, dr, buf, &करोne);
	अगर (!urb)
		जाओ cleanup;

	/* Submit just the SETUP stage */
	retval = submit_single_step_set_feature(hcd, urb, 1);
	अगर (retval)
		जाओ out1;
	अगर (!रुको_क्रम_completion_समयout(&करोne, msecs_to_jअगरfies(2000))) अणु
		usb_समाप्त_urb(urb);
		retval = -ETIMEDOUT;
		ehci_err(ehci, "%s SETUP stage timed out on ep0\n", __func__);
		जाओ out1;
	पूर्ण
	msleep(15 * 1000);

	/* Complete reमुख्यing DATA and STATUS stages using the same URB */
	urb->status = -EINPROGRESS;
	usb_get_urb(urb);
	atomic_inc(&urb->use_count);
	atomic_inc(&urb->dev->urbnum);
	retval = submit_single_step_set_feature(hcd, urb, 0);
	अगर (!retval && !रुको_क्रम_completion_समयout(&करोne,
						msecs_to_jअगरfies(2000))) अणु
		usb_समाप्त_urb(urb);
		retval = -ETIMEDOUT;
		ehci_err(ehci, "%s IN stage timed out on ep0\n", __func__);
	पूर्ण
out1:
	usb_मुक्त_urb(urb);
cleanup:
	kमुक्त(dr);
	kमुक्त(buf);
	वापस retval;
पूर्ण
#पूर्ण_अगर /* CONFIG_USB_HCD_TEST_MODE */
/*-------------------------------------------------------------------------*/

पूर्णांक ehci_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength
) अणु
	काष्ठा ehci_hcd	*ehci = hcd_to_ehci (hcd);
	पूर्णांक		ports = HCS_N_PORTS (ehci->hcs_params);
	u32 __iomem	*status_reg, *hostpc_reg;
	u32		temp, temp1, status;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		retval = 0;
	अचिन्हित	selector;

	/*
	 * Aव्योम underflow जबतक calculating (wIndex & 0xff) - 1.
	 * The compiler might deduce that wIndex can never be 0 and then
	 * optimize away the tests क्रम !wIndex below.
	 */
	temp = wIndex & 0xff;
	temp -= (temp > 0);
	status_reg = &ehci->regs->port_status[temp];
	hostpc_reg = &ehci->regs->hostpc[temp];

	/*
	 * FIXME:  support SetPortFeatures USB_PORT_FEAT_INDICATOR.
	 * HCS_INDICATOR may say we can change LEDs to off/amber/green.
	 * (track current state ourselves) ... blink क्रम diagnostics,
	 * घातer, "this is the one", etc.  EHCI spec supports this.
	 */

	spin_lock_irqsave (&ehci->lock, flags);
	चयन (typeReq) अणु
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = ehci_पढ़ोl(ehci, status_reg);
		temp &= ~PORT_RWC_BITS;

		/*
		 * Even अगर OWNER is set, so the port is owned by the
		 * companion controller, hub_wq needs to be able to clear
		 * the port-change status bits (especially
		 * USB_PORT_STAT_C_CONNECTION).
		 */

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			ehci_ग_लिखोl(ehci, temp & ~PORT_PE, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			ehci_ग_लिखोl(ehci, temp | PORT_PEC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (temp & PORT_RESET)
				जाओ error;
			अगर (ehci->no_selective_suspend)
				अवरोध;
#अगर_घोषित CONFIG_USB_OTG
			अगर ((hcd->self.otg_port == (wIndex + 1))
			    && hcd->self.b_hnp_enable) अणु
				otg_start_hnp(hcd->usb_phy->otg);
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			अगर (!(temp & PORT_SUSPEND))
				अवरोध;
			अगर ((temp & PORT_PE) == 0)
				जाओ error;

			/* clear phy low-घातer mode beक्रमe resume */
			अगर (ehci->has_tdi_phy_lpm) अणु
				temp1 = ehci_पढ़ोl(ehci, hostpc_reg);
				ehci_ग_लिखोl(ehci, temp1 & ~HOSTPC_PHCD,
						hostpc_reg);
				spin_unlock_irqrestore(&ehci->lock, flags);
				msleep(5);/* रुको to leave low-घातer mode */
				spin_lock_irqsave(&ehci->lock, flags);
			पूर्ण
			/* resume संकेतing क्रम 20 msec */
			temp &= ~PORT_WAKE_BITS;
			ehci_ग_लिखोl(ehci, temp | PORT_RESUME, status_reg);
			ehci->reset_करोne[wIndex] = jअगरfies
					+ msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			set_bit(wIndex, &ehci->resuming_ports);
			usb_hcd_start_port_resume(&hcd->self, wIndex);
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			clear_bit(wIndex, &ehci->port_c_suspend);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (HCS_PPC(ehci->hcs_params)) अणु
				spin_unlock_irqrestore(&ehci->lock, flags);
				ehci_port_घातer(ehci, wIndex, false);
				spin_lock_irqsave(&ehci->lock, flags);
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			ehci_ग_लिखोl(ehci, temp | PORT_CSC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			ehci_ग_लिखोl(ehci, temp | PORT_OCC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			/* GetPortStatus clears reset */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		ehci_पढ़ोl(ehci, &ehci->regs->command);	/* unblock posted ग_लिखो */
		अवरोध;
	हाल GetHubDescriptor:
		ehci_hub_descriptor (ehci, (काष्ठा usb_hub_descriptor *)
			buf);
		अवरोध;
	हाल GetHubStatus:
		/* no hub-wide feature/status flags */
		स_रखो (buf, 0, 4);
		//cpu_to_le32s ((u32 *) buf);
		अवरोध;
	हाल GetPortStatus:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		status = 0;
		temp = ehci_पढ़ोl(ehci, status_reg);

		// wPortChange bits
		अगर (temp & PORT_CSC)
			status |= USB_PORT_STAT_C_CONNECTION << 16;
		अगर (temp & PORT_PEC)
			status |= USB_PORT_STAT_C_ENABLE << 16;

		अगर ((temp & PORT_OCC) && (!ignore_oc && !ehci->spurious_oc))अणु
			status |= USB_PORT_STAT_C_OVERCURRENT << 16;

			/*
			 * Hubs should disable port घातer on over-current.
			 * However, not all EHCI implementations करो this
			 * स्वतःmatically, even अगर they _करो_ support per-port
			 * घातer चयनing; they're allowed to just limit the
			 * current.  hub_wq will turn the घातer back on.
			 */
			अगर (((temp & PORT_OC) || (ehci->need_oc_pp_cycle))
					&& HCS_PPC(ehci->hcs_params)) अणु
				spin_unlock_irqrestore(&ehci->lock, flags);
				ehci_port_घातer(ehci, wIndex, false);
				spin_lock_irqsave(&ehci->lock, flags);
				temp = ehci_पढ़ोl(ehci, status_reg);
			पूर्ण
		पूर्ण

		/* no reset or resume pending */
		अगर (!ehci->reset_करोne[wIndex]) अणु

			/* Remote Wakeup received? */
			अगर (temp & PORT_RESUME) अणु
				/* resume संकेतing क्रम 20 msec */
				ehci->reset_करोne[wIndex] = jअगरfies
						+ msecs_to_jअगरfies(20);
				usb_hcd_start_port_resume(&hcd->self, wIndex);
				set_bit(wIndex, &ehci->resuming_ports);
				/* check the port again */
				mod_समयr(&ehci_to_hcd(ehci)->rh_समयr,
						ehci->reset_करोne[wIndex]);
			पूर्ण

		/* reset or resume not yet complete */
		पूर्ण अन्यथा अगर (!समय_after_eq(jअगरfies, ehci->reset_करोne[wIndex])) अणु
			;	/* रुको until it is complete */

		/* resume completed */
		पूर्ण अन्यथा अगर (test_bit(wIndex, &ehci->resuming_ports)) अणु
			clear_bit(wIndex, &ehci->suspended_ports);
			set_bit(wIndex, &ehci->port_c_suspend);
			ehci->reset_करोne[wIndex] = 0;
			usb_hcd_end_port_resume(&hcd->self, wIndex);

			/* stop resume संकेतing */
			temp &= ~(PORT_RWC_BITS | PORT_SUSPEND | PORT_RESUME);
			ehci_ग_लिखोl(ehci, temp, status_reg);
			clear_bit(wIndex, &ehci->resuming_ports);
			retval = ehci_handshake(ehci, status_reg,
					PORT_RESUME, 0, 2000 /* 2msec */);
			अगर (retval != 0) अणु
				ehci_err(ehci, "port %d resume error %d\n",
						wIndex + 1, retval);
				जाओ error;
			पूर्ण
			temp = ehci_पढ़ोl(ehci, status_reg);

		/* whoever resets must GetPortStatus to complete it!! */
		पूर्ण अन्यथा अणु
			status |= USB_PORT_STAT_C_RESET << 16;
			ehci->reset_करोne [wIndex] = 0;

			/* क्रमce reset to complete */
			ehci_ग_लिखोl(ehci, temp & ~(PORT_RWC_BITS | PORT_RESET),
					status_reg);
			/* REVISIT:  some hardware needs 550+ usec to clear
			 * this bit; seems too दीर्घ to spin routinely...
			 */
			retval = ehci_handshake(ehci, status_reg,
					PORT_RESET, 0, 1000);
			अगर (retval != 0) अणु
				ehci_err (ehci, "port %d reset error %d\n",
					wIndex + 1, retval);
				जाओ error;
			पूर्ण

			/* see what we found out */
			temp = check_reset_complete (ehci, wIndex, status_reg,
					ehci_पढ़ोl(ehci, status_reg));
		पूर्ण

		/* transfer dedicated ports to the companion hc */
		अगर ((temp & PORT_CONNECT) &&
				test_bit(wIndex, &ehci->companion_ports)) अणु
			temp &= ~PORT_RWC_BITS;
			temp |= PORT_OWNER;
			ehci_ग_लिखोl(ehci, temp, status_reg);
			ehci_dbg(ehci, "port %d --> companion\n", wIndex + 1);
			temp = ehci_पढ़ोl(ehci, status_reg);
		पूर्ण

		/*
		 * Even अगर OWNER is set, there's no harm letting hub_wq
		 * see the wPortStatus values (they should all be 0 except
		 * क्रम PORT_POWER anyway).
		 */

		अगर (temp & PORT_CONNECT) अणु
			status |= USB_PORT_STAT_CONNECTION;
			// status may be from पूर्णांकegrated TT
			अगर (ehci->has_hostpc) अणु
				temp1 = ehci_पढ़ोl(ehci, hostpc_reg);
				status |= ehci_port_speed(ehci, temp1);
			पूर्ण अन्यथा
				status |= ehci_port_speed(ehci, temp);
		पूर्ण
		अगर (temp & PORT_PE)
			status |= USB_PORT_STAT_ENABLE;

		/* maybe the port was unsuspended without our knowledge */
		अगर (temp & (PORT_SUSPEND|PORT_RESUME)) अणु
			status |= USB_PORT_STAT_SUSPEND;
		पूर्ण अन्यथा अगर (test_bit(wIndex, &ehci->suspended_ports)) अणु
			clear_bit(wIndex, &ehci->suspended_ports);
			clear_bit(wIndex, &ehci->resuming_ports);
			ehci->reset_करोne[wIndex] = 0;
			अगर (temp & PORT_PE)
				set_bit(wIndex, &ehci->port_c_suspend);
			usb_hcd_end_port_resume(&hcd->self, wIndex);
		पूर्ण

		अगर (temp & PORT_OC)
			status |= USB_PORT_STAT_OVERCURRENT;
		अगर (temp & PORT_RESET)
			status |= USB_PORT_STAT_RESET;
		अगर (temp & PORT_POWER)
			status |= USB_PORT_STAT_POWER;
		अगर (test_bit(wIndex, &ehci->port_c_suspend))
			status |= USB_PORT_STAT_C_SUSPEND << 16;

		अगर (status & ~0xffff)	/* only अगर wPortChange is पूर्णांकeresting */
			dbg_port(ehci, "GetStatus", wIndex + 1, temp);
		put_unaligned_le32(status, buf);
		अवरोध;
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		selector = wIndex >> 8;
		wIndex &= 0xff;
		अगर (unlikely(ehci->debug)) अणु
			/* If the debug port is active any port
			 * feature requests should get denied */
			अगर (wIndex == HCS_DEBUG_PORT(ehci->hcs_params) &&
			    (पढ़ोl(&ehci->debug->control) & DBGP_ENABLED)) अणु
				retval = -ENODEV;
				जाओ error_निकास;
			पूर्ण
		पूर्ण
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = ehci_पढ़ोl(ehci, status_reg);
		अगर (temp & PORT_OWNER)
			अवरोध;

		temp &= ~PORT_RWC_BITS;
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (ehci->no_selective_suspend)
				अवरोध;
			अगर ((temp & PORT_PE) == 0
					|| (temp & PORT_RESET) != 0)
				जाओ error;

			/* After above check the port must be connected.
			 * Set appropriate bit thus could put phy पूर्णांकo low घातer
			 * mode अगर we have tdi_phy_lpm feature
			 */
			temp &= ~PORT_WKCONN_E;
			temp |= PORT_WKDISC_E | PORT_WKOC_E;
			ehci_ग_लिखोl(ehci, temp | PORT_SUSPEND, status_reg);
			अगर (ehci->has_tdi_phy_lpm) अणु
				spin_unlock_irqrestore(&ehci->lock, flags);
				msleep(5);/* 5ms क्रम HCD enter low pwr mode */
				spin_lock_irqsave(&ehci->lock, flags);
				temp1 = ehci_पढ़ोl(ehci, hostpc_reg);
				ehci_ग_लिखोl(ehci, temp1 | HOSTPC_PHCD,
					hostpc_reg);
				temp1 = ehci_पढ़ोl(ehci, hostpc_reg);
				ehci_dbg(ehci, "Port%d phy low pwr mode %s\n",
					wIndex, (temp1 & HOSTPC_PHCD) ?
					"succeeded" : "failed");
			पूर्ण
			अगर (ehci_has_fsl_susp_errata(ehci)) अणु
				/* 10ms क्रम HCD enter suspend */
				spin_unlock_irqrestore(&ehci->lock, flags);
				usleep_range(10000, 20000);
				spin_lock_irqsave(&ehci->lock, flags);
			पूर्ण
			set_bit(wIndex, &ehci->suspended_ports);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (HCS_PPC(ehci->hcs_params)) अणु
				spin_unlock_irqrestore(&ehci->lock, flags);
				ehci_port_घातer(ehci, wIndex, true);
				spin_lock_irqsave(&ehci->lock, flags);
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			अगर (temp & (PORT_SUSPEND|PORT_RESUME))
				जाओ error;
			/* line status bits may report this as low speed,
			 * which can be fine अगर this root hub has a
			 * transaction translator built in.
			 */
			अगर ((temp & (PORT_PE|PORT_CONNECT)) == PORT_CONNECT
					&& !ehci_is_TDI(ehci)
					&& PORT_USB11 (temp)) अणु
				ehci_dbg (ehci,
					"port %d low speed --> companion\n",
					wIndex + 1);
				temp |= PORT_OWNER;
			पूर्ण अन्यथा अणु
				temp |= PORT_RESET;
				temp &= ~PORT_PE;

				/*
				 * caller must रुको, then call GetPortStatus
				 * usb 2.0 spec says 50 ms resets on root
				 */
				ehci->reset_करोne [wIndex] = jअगरfies
						+ msecs_to_jअगरfies (50);

				/*
				 * Force full-speed connect क्रम FSL high-speed
				 * erratum; disable HS Chirp by setting PFSC bit
				 */
				अगर (ehci_has_fsl_hs_errata(ehci))
					temp |= (1 << PORTSC_FSL_PFSC);
			पूर्ण
			ehci_ग_लिखोl(ehci, temp, status_reg);
			अवरोध;

		/* For करोwnstream facing ports (these):  one hub port is put
		 * पूर्णांकo test mode according to USB2 11.24.2.13, then the hub
		 * must be reset (which क्रम root hub now means rmmod+modprobe,
		 * or अन्यथा प्रणाली reboot).  See EHCI 2.3.9 and 4.14 क्रम info
		 * about the EHCI-specअगरic stuff.
		 */
		हाल USB_PORT_FEAT_TEST:
#अगर_घोषित CONFIG_USB_HCD_TEST_MODE
			अगर (selector == EHSET_TEST_SINGLE_STEP_SET_FEATURE) अणु
				spin_unlock_irqrestore(&ehci->lock, flags);
				retval = ehset_single_step_set_feature(hcd,
								wIndex + 1);
				spin_lock_irqsave(&ehci->lock, flags);
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			अगर (!selector || selector > 5)
				जाओ error;
			spin_unlock_irqrestore(&ehci->lock, flags);
			ehci_quiesce(ehci);
			spin_lock_irqsave(&ehci->lock, flags);

			/* Put all enabled ports पूर्णांकo suspend */
			जबतक (ports--) अणु
				u32 __iomem *sreg =
						&ehci->regs->port_status[ports];

				temp = ehci_पढ़ोl(ehci, sreg) & ~PORT_RWC_BITS;
				अगर (temp & PORT_PE)
					ehci_ग_लिखोl(ehci, temp | PORT_SUSPEND,
							sreg);
			पूर्ण

			spin_unlock_irqrestore(&ehci->lock, flags);
			ehci_halt(ehci);
			spin_lock_irqsave(&ehci->lock, flags);

			temp = ehci_पढ़ोl(ehci, status_reg);
			temp |= selector << 16;
			ehci_ग_लिखोl(ehci, temp, status_reg);
			अवरोध;

		शेष:
			जाओ error;
		पूर्ण
		ehci_पढ़ोl(ehci, &ehci->regs->command);	/* unblock posted ग_लिखोs */
		अवरोध;

	शेष:
error:
		/* "stall" on error */
		retval = -EPIPE;
	पूर्ण
error_निकास:
	spin_unlock_irqrestore (&ehci->lock, flags);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(ehci_hub_control);

अटल व्योम ehci_relinquish_port(काष्ठा usb_hcd *hcd, पूर्णांक portnum)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);

	अगर (ehci_is_TDI(ehci))
		वापस;
	set_owner(ehci, --portnum, PORT_OWNER);
पूर्ण

अटल पूर्णांक ehci_port_handed_over(काष्ठा usb_hcd *hcd, पूर्णांक portnum)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	u32 __iomem		*reg;

	अगर (ehci_is_TDI(ehci))
		वापस 0;
	reg = &ehci->regs->port_status[portnum - 1];
	वापस ehci_पढ़ोl(ehci, reg) & PORT_OWNER;
पूर्ण

अटल पूर्णांक ehci_port_घातer(काष्ठा ehci_hcd *ehci, पूर्णांक portnum, bool enable)
अणु
	काष्ठा usb_hcd *hcd = ehci_to_hcd(ehci);
	u32 __iomem *status_reg = &ehci->regs->port_status[portnum];
	u32 temp = ehci_पढ़ोl(ehci, status_reg) & ~PORT_RWC_BITS;

	अगर (enable)
		ehci_ग_लिखोl(ehci, temp | PORT_POWER, status_reg);
	अन्यथा
		ehci_ग_लिखोl(ehci, temp & ~PORT_POWER, status_reg);

	अगर (hcd->driver->port_घातer)
		hcd->driver->port_घातer(hcd, portnum, enable);

	वापस 0;
पूर्ण
