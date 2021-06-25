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
 * (C) Copyright 2004 Alan Stern, stern@rowland.harvard.edu
 */

अटल स्थिर __u8 root_hub_hub_des[] =
अणु
	0x09,			/*  __u8  bLength; */
	USB_DT_HUB,		/*  __u8  bDescriptorType; Hub-descriptor */
	0x02,			/*  __u8  bNbrPorts; */
	HUB_CHAR_NO_LPSM |	/* __u16  wHubCharacteristics; */
		HUB_CHAR_INDV_PORT_OCPM, /* (per-port OC, no घातer चयनing) */
	0x00,
	0x01,			/*  __u8  bPwrOn2pwrGood; 2ms */
	0x00,			/*  __u8  bHubContrCurrent; 0 mA */
	0x00,			/*  __u8  DeviceRemovable; *** 7 Ports max */
	0xff			/*  __u8  PortPwrCtrlMask; *** 7 ports max */
पूर्ण;

#घोषणा	UHCI_RH_MAXCHILD	7

/* must ग_लिखो as zeroes */
#घोषणा WZ_BITS		(USBPORTSC_RES2 | USBPORTSC_RES3 | USBPORTSC_RES4)

/* status change bits:  nonzero ग_लिखोs will clear */
#घोषणा RWC_BITS	(USBPORTSC_OCC | USBPORTSC_PEC | USBPORTSC_CSC)

/* suspend/resume bits: port suspended or port resuming */
#घोषणा SUSPEND_BITS	(USBPORTSC_SUSP | USBPORTSC_RD)

/* A port that either is connected or has a changed-bit set will prevent
 * us from AUTO_STOPPING.
 */
अटल पूर्णांक any_ports_active(काष्ठा uhci_hcd *uhci)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < uhci->rh_numports; ++port) अणु
		अगर ((uhci_पढ़ोw(uhci, USBPORTSC1 + port * 2) &
				(USBPORTSC_CCS | RWC_BITS)) ||
				test_bit(port, &uhci->port_c_suspend))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_hub_status_data(काष्ठा uhci_hcd *uhci, अक्षर *buf)
अणु
	पूर्णांक port;
	पूर्णांक mask = RWC_BITS;

	/* Some boards (both VIA and Intel apparently) report bogus
	 * overcurrent indications, causing massive log spam unless
	 * we completely ignore them.  This करोesn't seem to be a problem
	 * with the chipset so much as with the way it is connected on
	 * the motherboard; अगर the overcurrent input is left to भग्न
	 * then it may स्थिरantly रेजिस्टर false positives. */
	अगर (ignore_oc)
		mask &= ~USBPORTSC_OCC;

	*buf = 0;
	क्रम (port = 0; port < uhci->rh_numports; ++port) अणु
		अगर ((uhci_पढ़ोw(uhci, USBPORTSC1 + port * 2) & mask) ||
				test_bit(port, &uhci->port_c_suspend))
			*buf |= (1 << (port + 1));
	पूर्ण
	वापस !!*buf;
पूर्ण

#घोषणा CLR_RH_PORTSTAT(x) \
	status = uhci_पढ़ोw(uhci, port_addr);	\
	status &= ~(RWC_BITS|WZ_BITS); \
	status &= ~(x); \
	status |= RWC_BITS & (x); \
	uhci_ग_लिखोw(uhci, status, port_addr)

#घोषणा SET_RH_PORTSTAT(x) \
	status = uhci_पढ़ोw(uhci, port_addr);	\
	status |= (x); \
	status &= ~(RWC_BITS|WZ_BITS); \
	uhci_ग_लिखोw(uhci, status, port_addr)

/* UHCI controllers करोn't स्वतःmatically stop resume संकेतling after 20 msec,
 * so we have to poll and check समयouts in order to take care of it.
 */
अटल व्योम uhci_finish_suspend(काष्ठा uhci_hcd *uhci, पूर्णांक port,
		अचिन्हित दीर्घ port_addr)
अणु
	पूर्णांक status;
	पूर्णांक i;

	अगर (uhci_पढ़ोw(uhci, port_addr) & SUSPEND_BITS) अणु
		CLR_RH_PORTSTAT(SUSPEND_BITS);
		अगर (test_bit(port, &uhci->resuming_ports))
			set_bit(port, &uhci->port_c_suspend);

		/* The controller won't actually turn off the RD bit until
		 * it has had a chance to send a low-speed EOP sequence,
		 * which is supposed to take 3 bit बार (= 2 microseconds).
		 * Experiments show that some controllers take दीर्घer, so
		 * we'll poll क्रम completion. */
		क्रम (i = 0; i < 10; ++i) अणु
			अगर (!(uhci_पढ़ोw(uhci, port_addr) & SUSPEND_BITS))
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण
	clear_bit(port, &uhci->resuming_ports);
	usb_hcd_end_port_resume(&uhci_to_hcd(uhci)->self, port);
पूर्ण

/* Wait क्रम the UHCI controller in HP's iLO2 server management chip.
 * It can take up to 250 us to finish a reset and set the CSC bit.
 */
अटल व्योम रुको_क्रम_HP(काष्ठा uhci_hcd *uhci, अचिन्हित दीर्घ port_addr)
अणु
	पूर्णांक i;

	क्रम (i = 10; i < 250; i += 10) अणु
		अगर (uhci_पढ़ोw(uhci, port_addr) & USBPORTSC_CSC)
			वापस;
		udelay(10);
	पूर्ण
	/* Log a warning? */
पूर्ण

अटल व्योम uhci_check_ports(काष्ठा uhci_hcd *uhci)
अणु
	अचिन्हित पूर्णांक port;
	अचिन्हित दीर्घ port_addr;
	पूर्णांक status;

	क्रम (port = 0; port < uhci->rh_numports; ++port) अणु
		port_addr = USBPORTSC1 + 2 * port;
		status = uhci_पढ़ोw(uhci, port_addr);
		अगर (unlikely(status & USBPORTSC_PR)) अणु
			अगर (समय_after_eq(jअगरfies, uhci->ports_समयout)) अणु
				CLR_RH_PORTSTAT(USBPORTSC_PR);
				udelay(10);

				/* HP's server management chip requires
				 * a दीर्घer delay. */
				अगर (uhci->रुको_क्रम_hp)
					रुको_क्रम_HP(uhci, port_addr);

				/* If the port was enabled beक्रमe, turning
				 * reset on caused a port enable change.
				 * Turning reset off causes a port connect
				 * status change.  Clear these changes. */
				CLR_RH_PORTSTAT(USBPORTSC_CSC | USBPORTSC_PEC);
				SET_RH_PORTSTAT(USBPORTSC_PE);
			पूर्ण
		पूर्ण
		अगर (unlikely(status & USBPORTSC_RD)) अणु
			अगर (!test_bit(port, &uhci->resuming_ports)) अणु

				/* Port received a wakeup request */
				set_bit(port, &uhci->resuming_ports);
				uhci->ports_समयout = jअगरfies +
					msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
				usb_hcd_start_port_resume(
						&uhci_to_hcd(uhci)->self, port);

				/* Make sure we see the port again
				 * after the resuming period is over. */
				mod_समयr(&uhci_to_hcd(uhci)->rh_समयr,
						uhci->ports_समयout);
			पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies,
						uhci->ports_समयout)) अणु
				uhci_finish_suspend(uhci, port, port_addr);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक uhci_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक status = 0;

	spin_lock_irqsave(&uhci->lock, flags);

	uhci_scan_schedule(uhci);
	अगर (!HCD_HW_ACCESSIBLE(hcd) || uhci->dead)
		जाओ करोne;
	uhci_check_ports(uhci);

	status = get_hub_status_data(uhci, buf);

	चयन (uhci->rh_state) अणु
	    हाल UHCI_RH_SUSPENDED:
		/* अगर port change, ask to be resumed */
		अगर (status || uhci->resuming_ports) अणु
			status = 1;
			usb_hcd_resume_root_hub(hcd);
		पूर्ण
		अवरोध;

	    हाल UHCI_RH_AUTO_STOPPED:
		/* अगर port change, स्वतः start */
		अगर (status)
			wakeup_rh(uhci);
		अवरोध;

	    हाल UHCI_RH_RUNNING:
		/* are any devices attached? */
		अगर (!any_ports_active(uhci)) अणु
			uhci->rh_state = UHCI_RH_RUNNING_NODEVS;
			uhci->स्वतः_stop_समय = jअगरfies + HZ;
		पूर्ण
		अवरोध;

	    हाल UHCI_RH_RUNNING_NODEVS:
		/* स्वतः-stop अगर nothing connected क्रम 1 second */
		अगर (any_ports_active(uhci))
			uhci->rh_state = UHCI_RH_RUNNING;
		अन्यथा अगर (समय_after_eq(jअगरfies, uhci->स्वतः_stop_समय) &&
				!uhci->रुको_क्रम_hp)
			suspend_rh(uhci, UHCI_RH_AUTO_STOPPED);
		अवरोध;

	    शेष:
		अवरोध;
	पूर्ण

करोne:
	spin_unlock_irqrestore(&uhci->lock, flags);
	वापस status;
पूर्ण

/* size of वापसed buffer is part of USB spec */
अटल पूर्णांक uhci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
			u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	पूर्णांक status, lstatus, retval = 0;
	अचिन्हित पूर्णांक port = wIndex - 1;
	अचिन्हित दीर्घ port_addr = USBPORTSC1 + 2 * port;
	u16 wPortChange, wPortStatus;
	अचिन्हित दीर्घ flags;

	अगर (!HCD_HW_ACCESSIBLE(hcd) || uhci->dead)
		वापस -ETIMEDOUT;

	spin_lock_irqsave(&uhci->lock, flags);
	चयन (typeReq) अणु

	हाल GetHubStatus:
		*(__le32 *)buf = cpu_to_le32(0);
		retval = 4; /* hub घातer */
		अवरोध;
	हाल GetPortStatus:
		अगर (port >= uhci->rh_numports)
			जाओ err;

		uhci_check_ports(uhci);
		status = uhci_पढ़ोw(uhci, port_addr);

		/* Intel controllers report the OverCurrent bit active on.
		 * VIA controllers report it active off, so we'll adjust the
		 * bit value.  (It's not standardized in the UHCI spec.)
		 */
		अगर (uhci->oc_low)
			status ^= USBPORTSC_OC;

		/* UHCI करोesn't support C_RESET (always false) */
		wPortChange = lstatus = 0;
		अगर (status & USBPORTSC_CSC)
			wPortChange |= USB_PORT_STAT_C_CONNECTION;
		अगर (status & USBPORTSC_PEC)
			wPortChange |= USB_PORT_STAT_C_ENABLE;
		अगर ((status & USBPORTSC_OCC) && !ignore_oc)
			wPortChange |= USB_PORT_STAT_C_OVERCURRENT;

		अगर (test_bit(port, &uhci->port_c_suspend)) अणु
			wPortChange |= USB_PORT_STAT_C_SUSPEND;
			lstatus |= 1;
		पूर्ण
		अगर (test_bit(port, &uhci->resuming_ports))
			lstatus |= 4;

		/* UHCI has no घातer चयनing (always on) */
		wPortStatus = USB_PORT_STAT_POWER;
		अगर (status & USBPORTSC_CCS)
			wPortStatus |= USB_PORT_STAT_CONNECTION;
		अगर (status & USBPORTSC_PE) अणु
			wPortStatus |= USB_PORT_STAT_ENABLE;
			अगर (status & SUSPEND_BITS)
				wPortStatus |= USB_PORT_STAT_SUSPEND;
		पूर्ण
		अगर (status & USBPORTSC_OC)
			wPortStatus |= USB_PORT_STAT_OVERCURRENT;
		अगर (status & USBPORTSC_PR)
			wPortStatus |= USB_PORT_STAT_RESET;
		अगर (status & USBPORTSC_LSDA)
			wPortStatus |= USB_PORT_STAT_LOW_SPEED;

		अगर (wPortChange)
			dev_dbg(uhci_dev(uhci), "port %d portsc %04x,%02x\n",
					wIndex, status, lstatus);

		*(__le16 *)buf = cpu_to_le16(wPortStatus);
		*(__le16 *)(buf + 2) = cpu_to_le16(wPortChange);
		retval = 4;
		अवरोध;
	हाल SetHubFeature:		/* We करोn't implement these */
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			अवरोध;
		शेष:
			जाओ err;
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		अगर (port >= uhci->rh_numports)
			जाओ err;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			SET_RH_PORTSTAT(USBPORTSC_SUSP);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			SET_RH_PORTSTAT(USBPORTSC_PR);

			/* Reset terminates Resume संकेतling */
			uhci_finish_suspend(uhci, port, port_addr);

			/* USB v2.0 7.1.7.5 */
			uhci->ports_समयout = jअगरfies +
				msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			/* UHCI has no घातer चयनing */
			अवरोध;
		शेष:
			जाओ err;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (port >= uhci->rh_numports)
			जाओ err;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			CLR_RH_PORTSTAT(USBPORTSC_PE);

			/* Disable terminates Resume संकेतling */
			uhci_finish_suspend(uhci, port, port_addr);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			CLR_RH_PORTSTAT(USBPORTSC_PEC);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (!(uhci_पढ़ोw(uhci, port_addr) & USBPORTSC_SUSP)) अणु

				/* Make certain the port isn't suspended */
				uhci_finish_suspend(uhci, port, port_addr);
			पूर्ण अन्यथा अगर (!test_and_set_bit(port,
						&uhci->resuming_ports)) अणु
				SET_RH_PORTSTAT(USBPORTSC_RD);

				/* The controller won't allow RD to be set
				 * अगर the port is disabled.  When this happens
				 * just skip the Resume संकेतling.
				 */
				अगर (!(uhci_पढ़ोw(uhci, port_addr) &
						USBPORTSC_RD))
					uhci_finish_suspend(uhci, port,
							port_addr);
				अन्यथा
					/* USB v2.0 7.1.7.7 */
					uhci->ports_समयout = jअगरfies +
						msecs_to_jअगरfies(20);
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			clear_bit(port, &uhci->port_c_suspend);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			/* UHCI has no घातer चयनing */
			जाओ err;
		हाल USB_PORT_FEAT_C_CONNECTION:
			CLR_RH_PORTSTAT(USBPORTSC_CSC);
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			CLR_RH_PORTSTAT(USBPORTSC_OCC);
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			/* this driver won't report these */
			अवरोध;
		शेष:
			जाओ err;
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		retval = min_t(अचिन्हित पूर्णांक, माप(root_hub_hub_des), wLength);
		स_नकल(buf, root_hub_hub_des, retval);
		अगर (retval > 2)
			buf[2] = uhci->rh_numports;
		अवरोध;
	शेष:
err:
		retval = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&uhci->lock, flags);

	वापस retval;
पूर्ण
