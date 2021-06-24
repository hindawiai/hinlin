<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MUSB OTG driver भव root hub support
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "musb_core.h"

व्योम musb_host_finish_resume(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा musb *musb;
	अचिन्हित दीर्घ flags;
	u8 घातer;

	musb = container_of(work, काष्ठा musb, finish_resume_work.work);

	spin_lock_irqsave(&musb->lock, flags);

	घातer = musb_पढ़ोb(musb->mregs, MUSB_POWER);
	घातer &= ~MUSB_POWER_RESUME;
	musb_dbg(musb, "root port resume stopped, power %02x", घातer);
	musb_ग_लिखोb(musb->mregs, MUSB_POWER, घातer);

	/*
	 * ISSUE:  DaVinci (RTL 1.300) disconnects after
	 * resume of high speed peripherals (but not full
	 * speed ones).
	 */
	musb->is_active = 1;
	musb->port1_status &= ~(USB_PORT_STAT_SUSPEND | MUSB_PORT_STAT_RESUME);
	musb->port1_status |= USB_PORT_STAT_C_SUSPEND << 16;
	usb_hcd_poll_rh_status(musb->hcd);
	/* NOTE: it might really be A_WAIT_BCON ... */
	musb->xceiv->otg->state = OTG_STATE_A_HOST;

	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

पूर्णांक musb_port_suspend(काष्ठा musb *musb, bool करो_suspend)
अणु
	काष्ठा usb_otg	*otg = musb->xceiv->otg;
	u8		घातer;
	व्योम __iomem	*mbase = musb->mregs;

	अगर (!is_host_active(musb))
		वापस 0;

	/* NOTE:  this करोesn't necessarily put PHY पूर्णांकo low घातer mode,
	 * turning off its घड़ी; that's a function of PHY पूर्णांकegration and
	 * MUSB_POWER_ENSUSPEND.  PHY may need a घड़ी (sigh) to detect
	 * SE0 changing to connect (J) or wakeup (K) states.
	 */
	घातer = musb_पढ़ोb(mbase, MUSB_POWER);
	अगर (करो_suspend) अणु
		पूर्णांक retries = 10000;

		अगर (घातer & MUSB_POWER_RESUME)
			वापस -EBUSY;

		अगर (!(घातer & MUSB_POWER_SUSPENDM)) अणु
			घातer |= MUSB_POWER_SUSPENDM;
			musb_ग_लिखोb(mbase, MUSB_POWER, घातer);

			/* Needed क्रम OPT A tests */
			घातer = musb_पढ़ोb(mbase, MUSB_POWER);
			जबतक (घातer & MUSB_POWER_SUSPENDM) अणु
				घातer = musb_पढ़ोb(mbase, MUSB_POWER);
				अगर (retries-- < 1)
					अवरोध;
			पूर्ण
		पूर्ण

		musb_dbg(musb, "Root port suspended, power %02x", घातer);

		musb->port1_status |= USB_PORT_STAT_SUSPEND;
		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_HOST:
			musb->xceiv->otg->state = OTG_STATE_A_SUSPEND;
			musb->is_active = otg->host->b_hnp_enable;
			अगर (musb->is_active)
				mod_समयr(&musb->otg_समयr, jअगरfies
					+ msecs_to_jअगरfies(
						OTG_TIME_A_AIDL_BDIS));
			musb_platक्रमm_try_idle(musb, 0);
			अवरोध;
		हाल OTG_STATE_B_HOST:
			musb->xceiv->otg->state = OTG_STATE_B_WAIT_ACON;
			musb->is_active = otg->host->b_hnp_enable;
			musb_platक्रमm_try_idle(musb, 0);
			अवरोध;
		शेष:
			musb_dbg(musb, "bogus rh suspend? %s",
				usb_otg_state_string(musb->xceiv->otg->state));
		पूर्ण
	पूर्ण अन्यथा अगर (घातer & MUSB_POWER_SUSPENDM) अणु
		घातer &= ~MUSB_POWER_SUSPENDM;
		घातer |= MUSB_POWER_RESUME;
		musb_ग_लिखोb(mbase, MUSB_POWER, घातer);

		musb_dbg(musb, "Root port resuming, power %02x", घातer);

		musb->port1_status |= MUSB_PORT_STAT_RESUME;
		schedule_delayed_work(&musb->finish_resume_work,
				      msecs_to_jअगरfies(USB_RESUME_TIMEOUT));
	पूर्ण
	वापस 0;
पूर्ण

व्योम musb_port_reset(काष्ठा musb *musb, bool करो_reset)
अणु
	u8		घातer;
	व्योम __iomem	*mbase = musb->mregs;

	अगर (musb->xceiv->otg->state == OTG_STATE_B_IDLE) अणु
		musb_dbg(musb, "HNP: Returning from HNP; no hub reset from b_idle");
		musb->port1_status &= ~USB_PORT_STAT_RESET;
		वापस;
	पूर्ण

	अगर (!is_host_active(musb))
		वापस;

	/* NOTE:  caller guarantees it will turn off the reset when
	 * the appropriate amount of समय has passed
	 */
	घातer = musb_पढ़ोb(mbase, MUSB_POWER);
	अगर (करो_reset) अणु
		/*
		 * If RESUME is set, we must make sure it stays minimum 20 ms.
		 * Then we must clear RESUME and रुको a bit to let musb start
		 * generating SOFs. If we करोn't करो this, OPT HS A 6.8 tests
		 * fail with "Error! Did not receive an SOF beक्रमe suspend
		 * detected".
		 */
		अगर (घातer &  MUSB_POWER_RESUME) अणु
			दीर्घ reमुख्य = (अचिन्हित दीर्घ) musb->rh_समयr - jअगरfies;

			अगर (musb->rh_समयr > 0 && reमुख्य > 0) अणु
				/* take पूर्णांकo account the minimum delay after resume */
				schedule_delayed_work(
					&musb->deनिश्चित_reset_work, reमुख्य);
				वापस;
			पूर्ण

			musb_ग_लिखोb(mbase, MUSB_POWER,
				    घातer & ~MUSB_POWER_RESUME);

			/* Give the core 1 ms to clear MUSB_POWER_RESUME */
			schedule_delayed_work(&musb->deनिश्चित_reset_work,
					      msecs_to_jअगरfies(1));
			वापस;
		पूर्ण

		घातer &= 0xf0;
		musb_ग_लिखोb(mbase, MUSB_POWER,
				घातer | MUSB_POWER_RESET);

		musb->port1_status |= USB_PORT_STAT_RESET;
		musb->port1_status &= ~USB_PORT_STAT_ENABLE;
		schedule_delayed_work(&musb->deनिश्चित_reset_work,
				      msecs_to_jअगरfies(50));
	पूर्ण अन्यथा अणु
		musb_dbg(musb, "root port reset stopped");
		musb_platक्रमm_pre_root_reset_end(musb);
		musb_ग_लिखोb(mbase, MUSB_POWER,
				घातer & ~MUSB_POWER_RESET);
		musb_platक्रमm_post_root_reset_end(musb);

		घातer = musb_पढ़ोb(mbase, MUSB_POWER);
		अगर (घातer & MUSB_POWER_HSMODE) अणु
			musb_dbg(musb, "high-speed device connected");
			musb->port1_status |= USB_PORT_STAT_HIGH_SPEED;
		पूर्ण

		musb->port1_status &= ~USB_PORT_STAT_RESET;
		musb->port1_status |= USB_PORT_STAT_ENABLE
					| (USB_PORT_STAT_C_RESET << 16)
					| (USB_PORT_STAT_C_ENABLE << 16);
		usb_hcd_poll_rh_status(musb->hcd);

		musb->vbuserr_retry = VBUSERR_RETRY_COUNT;
	पूर्ण
पूर्ण

व्योम musb_root_disconnect(काष्ठा musb *musb)
अणु
	काष्ठा usb_otg	*otg = musb->xceiv->otg;

	musb->port1_status = USB_PORT_STAT_POWER
			| (USB_PORT_STAT_C_CONNECTION << 16);

	usb_hcd_poll_rh_status(musb->hcd);
	musb->is_active = 0;

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_SUSPEND:
		अगर (otg->host->b_hnp_enable) अणु
			musb->xceiv->otg->state = OTG_STATE_A_PERIPHERAL;
			musb->g.is_a_peripheral = 1;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल OTG_STATE_A_HOST:
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
		musb->is_active = 0;
		अवरोध;
	हाल OTG_STATE_A_WAIT_VFALL:
		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		अवरोध;
	शेष:
		musb_dbg(musb, "host disconnect (%s)",
			usb_otg_state_string(musb->xceiv->otg->state));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(musb_root_disconnect);


/*---------------------------------------------------------------------*/

/* Caller may or may not hold musb->lock */
पूर्णांक musb_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा musb	*musb = hcd_to_musb(hcd);
	पूर्णांक		retval = 0;

	/* called in_irq() via usb_hcd_poll_rh_status() */
	अगर (musb->port1_status & 0xffff0000) अणु
		*buf = 0x02;
		retval = 1;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक musb_has_gadget(काष्ठा musb *musb)
अणु
	/*
	 * In host-only mode we start a connection right away. In OTG mode
	 * we have to रुको until we loaded a gadget. We करोn't really need a
	 * gadget अगर we operate as a host but we should not start a session
	 * as a device without a gadget or अन्यथा we explode.
	 */
#अगर_घोषित CONFIG_USB_MUSB_HOST
	वापस 1;
#अन्यथा
	वापस musb->port_mode == MUSB_HOST;
#पूर्ण_अगर
पूर्ण

पूर्णांक musb_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength)
अणु
	काष्ठा musb	*musb = hcd_to_musb(hcd);
	u32		temp;
	पूर्णांक		retval = 0;
	अचिन्हित दीर्घ	flags;
	bool		start_musb = false;

	spin_lock_irqsave(&musb->lock, flags);

	अगर (unlikely(!HCD_HW_ACCESSIBLE(hcd))) अणु
		spin_unlock_irqrestore(&musb->lock, flags);
		वापस -ESHUTDOWN;
	पूर्ण

	/* hub features:  always zero, setting is a NOP
	 * port features: reported, someबार updated when host is active
	 * no indicators
	 */
	चयन (typeReq) अणु
	हाल ClearHubFeature:
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर ((wIndex & 0xff) != 1)
			जाओ error;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			musb_port_suspend(musb, false);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (!hcd->self.is_b_host)
				musb_platक्रमm_set_vbus(musb, 0);
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
		हाल USB_PORT_FEAT_C_ENABLE:
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
		हाल USB_PORT_FEAT_C_RESET:
		हाल USB_PORT_FEAT_C_SUSPEND:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		musb_dbg(musb, "clear feature %d", wValue);
		musb->port1_status &= ~(1 << wValue);
		अवरोध;
	हाल GetHubDescriptor:
		अणु
		काष्ठा usb_hub_descriptor *desc = (व्योम *)buf;

		desc->bDescLength = 9;
		desc->bDescriptorType = USB_DT_HUB;
		desc->bNbrPorts = 1;
		desc->wHubCharacteristics = cpu_to_le16(
			HUB_CHAR_INDV_PORT_LPSM /* per-port घातer चयनing */
			| HUB_CHAR_NO_OCPM	/* no overcurrent reporting */
			);
		desc->bPwrOn2PwrGood = 5;	/* msec/2 */
		desc->bHubContrCurrent = 0;

		/* workaround bogus काष्ठा definition */
		desc->u.hs.DeviceRemovable[0] = 0x02;	/* port 1 */
		desc->u.hs.DeviceRemovable[1] = 0xff;
		पूर्ण
		अवरोध;
	हाल GetHubStatus:
		temp = 0;
		*(__le32 *) buf = cpu_to_le32(temp);
		अवरोध;
	हाल GetPortStatus:
		अगर (wIndex != 1)
			जाओ error;

		put_unaligned(cpu_to_le32(musb->port1_status
					& ~MUSB_PORT_STAT_RESUME),
				(__le32 *) buf);

		/* port change status is more पूर्णांकeresting */
		musb_dbg(musb, "port status %08x", musb->port1_status);
		अवरोध;
	हाल SetPortFeature:
		अगर ((wIndex & 0xff) != 1)
			जाओ error;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_POWER:
			/* NOTE: this controller has a strange state machine
			 * that involves "requesting sessions" according to
			 * magic side effects from incompletely-described
			 * rules about startup...
			 *
			 * This call is what really starts the host mode; be
			 * very careful about side effects अगर you reorder any
			 * initialization logic, e.g. क्रम OTG, or change any
			 * logic relating to VBUS घातer-up.
			 */
			अगर (!hcd->self.is_b_host && musb_has_gadget(musb))
				start_musb = true;
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			musb_port_reset(musb, true);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			musb_port_suspend(musb, true);
			अवरोध;
		हाल USB_PORT_FEAT_TEST:
			अगर (unlikely(is_host_active(musb)))
				जाओ error;

			wIndex >>= 8;
			चयन (wIndex) अणु
			हाल USB_TEST_J:
				pr_debug("USB_TEST_J\n");
				temp = MUSB_TEST_J;
				अवरोध;
			हाल USB_TEST_K:
				pr_debug("USB_TEST_K\n");
				temp = MUSB_TEST_K;
				अवरोध;
			हाल USB_TEST_SE0_NAK:
				pr_debug("USB_TEST_SE0_NAK\n");
				temp = MUSB_TEST_SE0_NAK;
				अवरोध;
			हाल USB_TEST_PACKET:
				pr_debug("USB_TEST_PACKET\n");
				temp = MUSB_TEST_PACKET;
				musb_load_testpacket(musb);
				अवरोध;
			हाल USB_TEST_FORCE_ENABLE:
				pr_debug("USB_TEST_FORCE_ENABLE\n");
				temp = MUSB_TEST_FORCE_HOST
					| MUSB_TEST_FORCE_HS;

				musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL,
						MUSB_DEVCTL_SESSION);
				अवरोध;
			हाल 6:
				pr_debug("TEST_FIFO_ACCESS\n");
				temp = MUSB_TEST_FIFO_ACCESS;
				अवरोध;
			शेष:
				जाओ error;
			पूर्ण
			musb_ग_लिखोb(musb->mregs, MUSB_TESTMODE, temp);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		musb_dbg(musb, "set feature %d", wValue);
		musb->port1_status |= 1 << wValue;
		अवरोध;

	शेष:
error:
		/* "protocol stall" on error */
		retval = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&musb->lock, flags);

	अगर (start_musb)
		musb_start(musb);

	वापस retval;
पूर्ण
