<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB hub driver.
 *
 * (C) Copyright 1999 Linus Torvalds
 * (C) Copyright 1999 Johannes Erdfelt
 * (C) Copyright 1999 Gregory P. Smith
 * (C) Copyright 2001 Brad Hards (bhards@bigpond.net.au)
 *
 * Released under the GPLv2 only.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/completion.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/kcov.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/usb.h>
#समावेश <linux/usbdevice_fs.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/quirks.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/kobject.h>

#समावेश <linux/bitfield.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "hub.h"
#समावेश "otg_productlist.h"

#घोषणा USB_VENDOR_GENESYS_LOGIC		0x05e3
#घोषणा USB_VENDOR_SMSC				0x0424
#घोषणा USB_PRODUCT_USB5534B			0x5534
#घोषणा USB_VENDOR_CYPRESS			0x04b4
#घोषणा USB_PRODUCT_CY7C65632			0x6570
#घोषणा HUB_QUIRK_CHECK_PORT_AUTOSUSPEND	0x01
#घोषणा HUB_QUIRK_DISABLE_AUTOSUSPEND		0x02

#घोषणा USB_TP_TRANSMISSION_DELAY	40	/* ns */
#घोषणा USB_TP_TRANSMISSION_DELAY_MAX	65535	/* ns */

/* Protect काष्ठा usb_device->state and ->children members
 * Note: Both are also रक्षित by ->dev.sem, except that ->state can
 * change to USB_STATE_NOTATTACHED even when the semaphore isn't held. */
अटल DEFINE_SPINLOCK(device_state_lock);

/* workqueue to process hub events */
अटल काष्ठा workqueue_काष्ठा *hub_wq;
अटल व्योम hub_event(काष्ठा work_काष्ठा *work);

/* synchronize hub-port add/हटाओ and peering operations */
DEFINE_MUTEX(usb_port_peer_mutex);

/* cycle leds on hubs that aren't blinking क्रम attention */
अटल bool blinkenlights;
module_param(blinkenlights, bool, S_IRUGO);
MODULE_PARM_DESC(blinkenlights, "true to cycle leds on hubs");

/*
 * Device SATA8000 FW1.0 from DATAST0R Technology Corp requires about
 * 10 seconds to send reply क्रम the initial 64-byte descriptor request.
 */
/* define initial 64-byte descriptor request समयout in milliseconds */
अटल पूर्णांक initial_descriptor_समयout = USB_CTRL_GET_TIMEOUT;
module_param(initial_descriptor_समयout, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(initial_descriptor_समयout,
		"initial 64-byte descriptor request timeout in milliseconds "
		"(default 5000 - 5.0 seconds)");

/*
 * As of 2.6.10 we पूर्णांकroduce a new USB device initialization scheme which
 * बंदly resembles the way Winकरोws works.  Hopefully it will be compatible
 * with a wider range of devices than the old scheme.  However some previously
 * working devices may start giving rise to "device not accepting address"
 * errors; अगर that happens the user can try the old scheme by adjusting the
 * following module parameters.
 *
 * For maximum flexibility there are two boolean parameters to control the
 * hub driver's behavior.  On the first initialization attempt, अगर the
 * "old_scheme_first" parameter is set then the old scheme will be used,
 * otherwise the new scheme is used.  If that fails and "use_both_schemes"
 * is set, then the driver will make another attempt, using the other scheme.
 */
अटल bool old_scheme_first;
module_param(old_scheme_first, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(old_scheme_first,
		 "start with the old device initialization scheme");

अटल bool use_both_schemes = true;
module_param(use_both_schemes, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(use_both_schemes,
		"try the other device initialization scheme if the "
		"first one fails");

/* Mutual exclusion क्रम EHCI CF initialization.  This पूर्णांकerferes with
 * port reset on some companion controllers.
 */
DECLARE_RWSEM(ehci_cf_port_reset_rwsem);
EXPORT_SYMBOL_GPL(ehci_cf_port_reset_rwsem);

#घोषणा HUB_DEBOUNCE_TIMEOUT	2000
#घोषणा HUB_DEBOUNCE_STEP	  25
#घोषणा HUB_DEBOUNCE_STABLE	 100

अटल व्योम hub_release(काष्ठा kref *kref);
अटल पूर्णांक usb_reset_and_verअगरy_device(काष्ठा usb_device *udev);
अटल पूर्णांक hub_port_disable(काष्ठा usb_hub *hub, पूर्णांक port1, पूर्णांक set_state);
अटल bool hub_port_warm_reset_required(काष्ठा usb_hub *hub, पूर्णांक port1,
		u16 portstatus);

अटल अंतरभूत अक्षर *portspeed(काष्ठा usb_hub *hub, पूर्णांक portstatus)
अणु
	अगर (hub_is_superspeedplus(hub->hdev))
		वापस "10.0 Gb/s";
	अगर (hub_is_superspeed(hub->hdev))
		वापस "5.0 Gb/s";
	अगर (portstatus & USB_PORT_STAT_HIGH_SPEED)
		वापस "480 Mb/s";
	अन्यथा अगर (portstatus & USB_PORT_STAT_LOW_SPEED)
		वापस "1.5 Mb/s";
	अन्यथा
		वापस "12 Mb/s";
पूर्ण

/* Note that hdev or one of its children must be locked! */
काष्ठा usb_hub *usb_hub_to_काष्ठा_hub(काष्ठा usb_device *hdev)
अणु
	अगर (!hdev || !hdev->actconfig || !hdev->maxchild)
		वापस शून्य;
	वापस usb_get_पूर्णांकfdata(hdev->actconfig->पूर्णांकerface[0]);
पूर्ण

पूर्णांक usb_device_supports_lpm(काष्ठा usb_device *udev)
अणु
	/* Some devices have trouble with LPM */
	अगर (udev->quirks & USB_QUIRK_NO_LPM)
		वापस 0;

	/* USB 2.1 (and greater) devices indicate LPM support through
	 * their USB 2.0 Extended Capabilities BOS descriptor.
	 */
	अगर (udev->speed == USB_SPEED_HIGH || udev->speed == USB_SPEED_FULL) अणु
		अगर (udev->bos->ext_cap &&
			(USB_LPM_SUPPORT &
			 le32_to_cpu(udev->bos->ext_cap->bmAttributes)))
			वापस 1;
		वापस 0;
	पूर्ण

	/*
	 * According to the USB 3.0 spec, all USB 3.0 devices must support LPM.
	 * However, there are some that करोn't, and they set the U1/U2 निकास
	 * latencies to zero.
	 */
	अगर (!udev->bos->ss_cap) अणु
		dev_info(&udev->dev, "No LPM exit latency info found, disabling LPM.\n");
		वापस 0;
	पूर्ण

	अगर (udev->bos->ss_cap->bU1devExitLat == 0 &&
			udev->bos->ss_cap->bU2DevExitLat == 0) अणु
		अगर (udev->parent)
			dev_info(&udev->dev, "LPM exit latency is zeroed, disabling LPM.\n");
		अन्यथा
			dev_info(&udev->dev, "We don't know the algorithms for LPM for this host, disabling LPM.\n");
		वापस 0;
	पूर्ण

	अगर (!udev->parent || udev->parent->lpm_capable)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Set the Maximum Exit Latency (MEL) क्रम the host to initiate a transition from
 * either U1 or U2.
 */
अटल व्योम usb_set_lpm_mel(काष्ठा usb_device *udev,
		काष्ठा usb3_lpm_parameters *udev_lpm_params,
		अचिन्हित पूर्णांक udev_निकास_latency,
		काष्ठा usb_hub *hub,
		काष्ठा usb3_lpm_parameters *hub_lpm_params,
		अचिन्हित पूर्णांक hub_निकास_latency)
अणु
	अचिन्हित पूर्णांक total_mel;
	अचिन्हित पूर्णांक device_mel;
	अचिन्हित पूर्णांक hub_mel;

	/*
	 * Calculate the समय it takes to transition all links from the roothub
	 * to the parent hub पूर्णांकo U0.  The parent hub must then decode the
	 * packet (hub header decode latency) to figure out which port it was
	 * bound क्रम.
	 *
	 * The Hub Header decode latency is expressed in 0.1us पूर्णांकervals (0x1
	 * means 0.1us).  Multiply that by 100 to get nanoseconds.
	 */
	total_mel = hub_lpm_params->mel +
		(hub->descriptor->u.ss.bHubHdrDecLat * 100);

	/*
	 * How दीर्घ will it take to transition the करोwnstream hub's port पूर्णांकo
	 * U0?  The greater of either the hub निकास latency or the device निकास
	 * latency.
	 *
	 * The BOS U1/U2 निकास latencies are expressed in 1us पूर्णांकervals.
	 * Multiply that by 1000 to get nanoseconds.
	 */
	device_mel = udev_निकास_latency * 1000;
	hub_mel = hub_निकास_latency * 1000;
	अगर (device_mel > hub_mel)
		total_mel += device_mel;
	अन्यथा
		total_mel += hub_mel;

	udev_lpm_params->mel = total_mel;
पूर्ण

/*
 * Set the maximum Device to Host Exit Latency (PEL) क्रम the device to initiate
 * a transition from either U1 or U2.
 */
अटल व्योम usb_set_lpm_pel(काष्ठा usb_device *udev,
		काष्ठा usb3_lpm_parameters *udev_lpm_params,
		अचिन्हित पूर्णांक udev_निकास_latency,
		काष्ठा usb_hub *hub,
		काष्ठा usb3_lpm_parameters *hub_lpm_params,
		अचिन्हित पूर्णांक hub_निकास_latency,
		अचिन्हित पूर्णांक port_to_port_निकास_latency)
अणु
	अचिन्हित पूर्णांक first_link_pel;
	अचिन्हित पूर्णांक hub_pel;

	/*
	 * First, the device sends an LFPS to transition the link between the
	 * device and the parent hub पूर्णांकo U0.  The निकास latency is the bigger of
	 * the device निकास latency or the hub निकास latency.
	 */
	अगर (udev_निकास_latency > hub_निकास_latency)
		first_link_pel = udev_निकास_latency * 1000;
	अन्यथा
		first_link_pel = hub_निकास_latency * 1000;

	/*
	 * When the hub starts to receive the LFPS, there is a slight delay क्रम
	 * it to figure out that one of the ports is sending an LFPS.  Then it
	 * will क्रमward the LFPS to its upstream link.  The निकास latency is the
	 * delay, plus the PEL that we calculated क्रम this hub.
	 */
	hub_pel = port_to_port_निकास_latency * 1000 + hub_lpm_params->pel;

	/*
	 * According to figure C-7 in the USB 3.0 spec, the PEL क्रम this device
	 * is the greater of the two निकास latencies.
	 */
	अगर (first_link_pel > hub_pel)
		udev_lpm_params->pel = first_link_pel;
	अन्यथा
		udev_lpm_params->pel = hub_pel;
पूर्ण

/*
 * Set the System Exit Latency (SEL) to indicate the total worst-हाल समय from
 * when a device initiates a transition to U0, until when it will receive the
 * first packet from the host controller.
 *
 * Section C.1.5.1 describes the four components to this:
 *  - t1: device PEL
 *  - t2: समय क्रम the ERDY to make it from the device to the host.
 *  - t3: a host-specअगरic delay to process the ERDY.
 *  - t4: समय क्रम the packet to make it from the host to the device.
 *
 * t3 is specअगरic to both the xHCI host and the platक्रमm the host is पूर्णांकegrated
 * पूर्णांकo.  The Intel HW folks have said it's negligible, FIXME अगर a dअगरferent
 * venकरोr says otherwise.
 */
अटल व्योम usb_set_lpm_sel(काष्ठा usb_device *udev,
		काष्ठा usb3_lpm_parameters *udev_lpm_params)
अणु
	काष्ठा usb_device *parent;
	अचिन्हित पूर्णांक num_hubs;
	अचिन्हित पूर्णांक total_sel;

	/* t1 = device PEL */
	total_sel = udev_lpm_params->pel;
	/* How many बाह्यal hubs are in between the device & the root port. */
	क्रम (parent = udev->parent, num_hubs = 0; parent->parent;
			parent = parent->parent)
		num_hubs++;
	/* t2 = 2.1us + 250ns * (num_hubs - 1) */
	अगर (num_hubs > 0)
		total_sel += 2100 + 250 * (num_hubs - 1);

	/* t4 = 250ns * num_hubs */
	total_sel += 250 * num_hubs;

	udev_lpm_params->sel = total_sel;
पूर्ण

अटल व्योम usb_set_lpm_parameters(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub;
	अचिन्हित पूर्णांक port_to_port_delay;
	अचिन्हित पूर्णांक udev_u1_del;
	अचिन्हित पूर्णांक udev_u2_del;
	अचिन्हित पूर्णांक hub_u1_del;
	अचिन्हित पूर्णांक hub_u2_del;

	अगर (!udev->lpm_capable || udev->speed < USB_SPEED_SUPER)
		वापस;

	hub = usb_hub_to_काष्ठा_hub(udev->parent);
	/* It करोesn't take समय to transition the roothub पूर्णांकo U0, since it
	 * करोesn't have an upstream link.
	 */
	अगर (!hub)
		वापस;

	udev_u1_del = udev->bos->ss_cap->bU1devExitLat;
	udev_u2_del = le16_to_cpu(udev->bos->ss_cap->bU2DevExitLat);
	hub_u1_del = udev->parent->bos->ss_cap->bU1devExitLat;
	hub_u2_del = le16_to_cpu(udev->parent->bos->ss_cap->bU2DevExitLat);

	usb_set_lpm_mel(udev, &udev->u1_params, udev_u1_del,
			hub, &udev->parent->u1_params, hub_u1_del);

	usb_set_lpm_mel(udev, &udev->u2_params, udev_u2_del,
			hub, &udev->parent->u2_params, hub_u2_del);

	/*
	 * Appendix C, section C.2.2.2, says that there is a slight delay from
	 * when the parent hub notices the करोwnstream port is trying to
	 * transition to U0 to when the hub initiates a U0 transition on its
	 * upstream port.  The section says the delays are tPort2PortU1EL and
	 * tPort2PortU2EL, but it करोesn't define what they are.
	 *
	 * The hub chapter, sections 10.4.2.4 and 10.4.2.5 seem to be talking
	 * about the same delays.  Use the maximum delay calculations from those
	 * sections.  For U1, it's tHubPort2PortExitLat, which is 1us max.  For
	 * U2, it's tHubPort2PortExitLat + U2DevExitLat - U1DevExitLat.  I
	 * assume the device निकास latencies they are talking about are the hub
	 * निकास latencies.
	 *
	 * What करो we करो अगर the U2 निकास latency is less than the U1 निकास
	 * latency?  It's possible, although not likely...
	 */
	port_to_port_delay = 1;

	usb_set_lpm_pel(udev, &udev->u1_params, udev_u1_del,
			hub, &udev->parent->u1_params, hub_u1_del,
			port_to_port_delay);

	अगर (hub_u2_del > hub_u1_del)
		port_to_port_delay = 1 + hub_u2_del - hub_u1_del;
	अन्यथा
		port_to_port_delay = 1 + hub_u1_del;

	usb_set_lpm_pel(udev, &udev->u2_params, udev_u2_del,
			hub, &udev->parent->u2_params, hub_u2_del,
			port_to_port_delay);

	/* Now that we've got PEL, calculate SEL. */
	usb_set_lpm_sel(udev, &udev->u1_params);
	usb_set_lpm_sel(udev, &udev->u2_params);
पूर्ण

/* USB 2.0 spec Section 11.24.4.5 */
अटल पूर्णांक get_hub_descriptor(काष्ठा usb_device *hdev,
		काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक i, ret, size;
	अचिन्हित dtype;

	अगर (hub_is_superspeed(hdev)) अणु
		dtype = USB_DT_SS_HUB;
		size = USB_DT_SS_HUB_SIZE;
	पूर्ण अन्यथा अणु
		dtype = USB_DT_HUB;
		size = माप(काष्ठा usb_hub_descriptor);
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		ret = usb_control_msg(hdev, usb_rcvctrlpipe(hdev, 0),
			USB_REQ_GET_DESCRIPTOR, USB_सूची_IN | USB_RT_HUB,
			dtype << 8, 0, desc, size,
			USB_CTRL_GET_TIMEOUT);
		अगर (hub_is_superspeed(hdev)) अणु
			अगर (ret == size)
				वापस ret;
		पूर्ण अन्यथा अगर (ret >= USB_DT_HUB_NONVAR_SIZE + 2) अणु
			/* Make sure we have the DeviceRemovable field. */
			size = USB_DT_HUB_NONVAR_SIZE + desc->bNbrPorts / 8 + 1;
			अगर (ret < size)
				वापस -EMSGSIZE;
			वापस ret;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * USB 2.0 spec Section 11.24.2.1
 */
अटल पूर्णांक clear_hub_feature(काष्ठा usb_device *hdev, पूर्णांक feature)
अणु
	वापस usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
		USB_REQ_CLEAR_FEATURE, USB_RT_HUB, feature, 0, शून्य, 0, 1000);
पूर्ण

/*
 * USB 2.0 spec Section 11.24.2.2
 */
पूर्णांक usb_clear_port_feature(काष्ठा usb_device *hdev, पूर्णांक port1, पूर्णांक feature)
अणु
	वापस usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
		USB_REQ_CLEAR_FEATURE, USB_RT_PORT, feature, port1,
		शून्य, 0, 1000);
पूर्ण

/*
 * USB 2.0 spec Section 11.24.2.13
 */
अटल पूर्णांक set_port_feature(काष्ठा usb_device *hdev, पूर्णांक port1, पूर्णांक feature)
अणु
	वापस usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
		USB_REQ_SET_FEATURE, USB_RT_PORT, feature, port1,
		शून्य, 0, 1000);
पूर्ण

अटल अक्षर *to_led_name(पूर्णांक selector)
अणु
	चयन (selector) अणु
	हाल HUB_LED_AMBER:
		वापस "amber";
	हाल HUB_LED_GREEN:
		वापस "green";
	हाल HUB_LED_OFF:
		वापस "off";
	हाल HUB_LED_AUTO:
		वापस "auto";
	शेष:
		वापस "??";
	पूर्ण
पूर्ण

/*
 * USB 2.0 spec Section 11.24.2.7.1.10 and table 11-7
 * क्रम info about using port indicators
 */
अटल व्योम set_port_led(काष्ठा usb_hub *hub, पूर्णांक port1, पूर्णांक selector)
अणु
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	पूर्णांक status;

	status = set_port_feature(hub->hdev, (selector << 8) | port1,
			USB_PORT_FEAT_INDICATOR);
	dev_dbg(&port_dev->dev, "indicator %s status %d\n",
		to_led_name(selector), status);
पूर्ण

#घोषणा	LED_CYCLE_PERIOD	((2*HZ)/3)

अटल व्योम led_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_hub		*hub =
		container_of(work, काष्ठा usb_hub, leds.work);
	काष्ठा usb_device	*hdev = hub->hdev;
	अचिन्हित		i;
	अचिन्हित		changed = 0;
	पूर्णांक			cursor = -1;

	अगर (hdev->state != USB_STATE_CONFIGURED || hub->quiescing)
		वापस;

	क्रम (i = 0; i < hdev->maxchild; i++) अणु
		अचिन्हित	selector, mode;

		/* 30%-50% duty cycle */

		चयन (hub->indicator[i]) अणु
		/* cycle marker */
		हाल INDICATOR_CYCLE:
			cursor = i;
			selector = HUB_LED_AUTO;
			mode = INDICATOR_AUTO;
			अवरोध;
		/* blinking green = sw attention */
		हाल INDICATOR_GREEN_BLINK:
			selector = HUB_LED_GREEN;
			mode = INDICATOR_GREEN_BLINK_OFF;
			अवरोध;
		हाल INDICATOR_GREEN_BLINK_OFF:
			selector = HUB_LED_OFF;
			mode = INDICATOR_GREEN_BLINK;
			अवरोध;
		/* blinking amber = hw attention */
		हाल INDICATOR_AMBER_BLINK:
			selector = HUB_LED_AMBER;
			mode = INDICATOR_AMBER_BLINK_OFF;
			अवरोध;
		हाल INDICATOR_AMBER_BLINK_OFF:
			selector = HUB_LED_OFF;
			mode = INDICATOR_AMBER_BLINK;
			अवरोध;
		/* blink green/amber = reserved */
		हाल INDICATOR_ALT_BLINK:
			selector = HUB_LED_GREEN;
			mode = INDICATOR_ALT_BLINK_OFF;
			अवरोध;
		हाल INDICATOR_ALT_BLINK_OFF:
			selector = HUB_LED_AMBER;
			mode = INDICATOR_ALT_BLINK;
			अवरोध;
		शेष:
			जारी;
		पूर्ण
		अगर (selector != HUB_LED_AUTO)
			changed = 1;
		set_port_led(hub, i + 1, selector);
		hub->indicator[i] = mode;
	पूर्ण
	अगर (!changed && blinkenlights) अणु
		cursor++;
		cursor %= hdev->maxchild;
		set_port_led(hub, cursor + 1, HUB_LED_GREEN);
		hub->indicator[cursor] = INDICATOR_CYCLE;
		changed++;
	पूर्ण
	अगर (changed)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				&hub->leds, LED_CYCLE_PERIOD);
पूर्ण

/* use a लघु समयout क्रम hub/port status fetches */
#घोषणा	USB_STS_TIMEOUT		1000
#घोषणा	USB_STS_RETRIES		5

/*
 * USB 2.0 spec Section 11.24.2.6
 */
अटल पूर्णांक get_hub_status(काष्ठा usb_device *hdev,
		काष्ठा usb_hub_status *data)
अणु
	पूर्णांक i, status = -ETIMEDOUT;

	क्रम (i = 0; i < USB_STS_RETRIES &&
			(status == -ETIMEDOUT || status == -EPIPE); i++) अणु
		status = usb_control_msg(hdev, usb_rcvctrlpipe(hdev, 0),
			USB_REQ_GET_STATUS, USB_सूची_IN | USB_RT_HUB, 0, 0,
			data, माप(*data), USB_STS_TIMEOUT);
	पूर्ण
	वापस status;
पूर्ण

/*
 * USB 2.0 spec Section 11.24.2.7
 * USB 3.1 takes पूर्णांकo use the wValue and wLength fields, spec Section 10.16.2.6
 */
अटल पूर्णांक get_port_status(काष्ठा usb_device *hdev, पूर्णांक port1,
			   व्योम *data, u16 value, u16 length)
अणु
	पूर्णांक i, status = -ETIMEDOUT;

	क्रम (i = 0; i < USB_STS_RETRIES &&
			(status == -ETIMEDOUT || status == -EPIPE); i++) अणु
		status = usb_control_msg(hdev, usb_rcvctrlpipe(hdev, 0),
			USB_REQ_GET_STATUS, USB_सूची_IN | USB_RT_PORT, value,
			port1, data, length, USB_STS_TIMEOUT);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक hub_ext_port_status(काष्ठा usb_hub *hub, पूर्णांक port1, पूर्णांक type,
			       u16 *status, u16 *change, u32 *ext_status)
अणु
	पूर्णांक ret;
	पूर्णांक len = 4;

	अगर (type != HUB_PORT_STATUS)
		len = 8;

	mutex_lock(&hub->status_mutex);
	ret = get_port_status(hub->hdev, port1, &hub->status->port, type, len);
	अगर (ret < len) अणु
		अगर (ret != -ENODEV)
			dev_err(hub->पूर्णांकfdev,
				"%s failed (err = %d)\n", __func__, ret);
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण अन्यथा अणु
		*status = le16_to_cpu(hub->status->port.wPortStatus);
		*change = le16_to_cpu(hub->status->port.wPortChange);
		अगर (type != HUB_PORT_STATUS && ext_status)
			*ext_status = le32_to_cpu(
				hub->status->port.dwExtPortStatus);
		ret = 0;
	पूर्ण
	mutex_unlock(&hub->status_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक hub_port_status(काष्ठा usb_hub *hub, पूर्णांक port1,
		u16 *status, u16 *change)
अणु
	वापस hub_ext_port_status(hub, port1, HUB_PORT_STATUS,
				   status, change, शून्य);
पूर्ण

अटल व्योम hub_resubmit_irq_urb(काष्ठा usb_hub *hub)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status;

	spin_lock_irqsave(&hub->irq_urb_lock, flags);

	अगर (hub->quiescing) अणु
		spin_unlock_irqrestore(&hub->irq_urb_lock, flags);
		वापस;
	पूर्ण

	status = usb_submit_urb(hub->urb, GFP_ATOMIC);
	अगर (status && status != -ENODEV && status != -EPERM &&
	    status != -ESHUTDOWN) अणु
		dev_err(hub->पूर्णांकfdev, "resubmit --> %d\n", status);
		mod_समयr(&hub->irq_urb_retry, jअगरfies + HZ);
	पूर्ण

	spin_unlock_irqrestore(&hub->irq_urb_lock, flags);
पूर्ण

अटल व्योम hub_retry_irq_urb(काष्ठा समयr_list *t)
अणु
	काष्ठा usb_hub *hub = from_समयr(hub, t, irq_urb_retry);

	hub_resubmit_irq_urb(hub);
पूर्ण


अटल व्योम kick_hub_wq(काष्ठा usb_hub *hub)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	अगर (hub->disconnected || work_pending(&hub->events))
		वापस;

	/*
	 * Suppress स्वतःsuspend until the event is proceed.
	 *
	 * Be careful and make sure that the symmetric operation is
	 * always called. We are here only when there is no pending
	 * work क्रम this hub. Thereक्रमe put the पूर्णांकerface either when
	 * the new work is called or when it is canceled.
	 */
	पूर्णांकf = to_usb_पूर्णांकerface(hub->पूर्णांकfdev);
	usb_स्वतःpm_get_पूर्णांकerface_no_resume(पूर्णांकf);
	kref_get(&hub->kref);

	अगर (queue_work(hub_wq, &hub->events))
		वापस;

	/* the work has alपढ़ोy been scheduled */
	usb_स्वतःpm_put_पूर्णांकerface_async(पूर्णांकf);
	kref_put(&hub->kref, hub_release);
पूर्ण

व्योम usb_kick_hub_wq(काष्ठा usb_device *hdev)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);

	अगर (hub)
		kick_hub_wq(hub);
पूर्ण

/*
 * Let the USB core know that a USB 3.0 device has sent a Function Wake Device
 * Notअगरication, which indicates it had initiated remote wakeup.
 *
 * USB 3.0 hubs करो not report the port link state change from U3 to U0 when the
 * device initiates resume, so the USB core will not receive notice of the
 * resume through the normal hub पूर्णांकerrupt URB.
 */
व्योम usb_wakeup_notअगरication(काष्ठा usb_device *hdev,
		अचिन्हित पूर्णांक portnum)
अणु
	काष्ठा usb_hub *hub;
	काष्ठा usb_port *port_dev;

	अगर (!hdev)
		वापस;

	hub = usb_hub_to_काष्ठा_hub(hdev);
	अगर (hub) अणु
		port_dev = hub->ports[portnum - 1];
		अगर (port_dev && port_dev->child)
			pm_wakeup_event(&port_dev->child->dev, 0);

		set_bit(portnum, hub->wakeup_bits);
		kick_hub_wq(hub);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_wakeup_notअगरication);

/* completion function, fires on port status changes and various faults */
अटल व्योम hub_irq(काष्ठा urb *urb)
अणु
	काष्ठा usb_hub *hub = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित i;
	अचिन्हित दीर्घ bits;

	चयन (status) अणु
	हाल -ENOENT:		/* synchronous unlink */
	हाल -ECONNRESET:	/* async unlink */
	हाल -ESHUTDOWN:	/* hardware going away */
		वापस;

	शेष:		/* presumably an error */
		/* Cause a hub reset after 10 consecutive errors */
		dev_dbg(hub->पूर्णांकfdev, "transfer --> %d\n", status);
		अगर ((++hub->nerrors < 10) || hub->error)
			जाओ resubmit;
		hub->error = status;
		fallthrough;

	/* let hub_wq handle things */
	हाल 0:			/* we got data:  port status changed */
		bits = 0;
		क्रम (i = 0; i < urb->actual_length; ++i)
			bits |= ((अचिन्हित दीर्घ) ((*hub->buffer)[i]))
					<< (i*8);
		hub->event_bits[0] = bits;
		अवरोध;
	पूर्ण

	hub->nerrors = 0;

	/* Something happened, let hub_wq figure it out */
	kick_hub_wq(hub);

resubmit:
	hub_resubmit_irq_urb(hub);
पूर्ण

/* USB 2.0 spec Section 11.24.2.3 */
अटल अंतरभूत पूर्णांक
hub_clear_tt_buffer(काष्ठा usb_device *hdev, u16 devinfo, u16 tt)
अणु
	/* Need to clear both directions क्रम control ep */
	अगर (((devinfo >> 11) & USB_ENDPOINT_XFERTYPE_MASK) ==
			USB_ENDPOINT_XFER_CONTROL) अणु
		पूर्णांक status = usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
				HUB_CLEAR_TT_BUFFER, USB_RT_PORT,
				devinfo ^ 0x8000, tt, शून्य, 0, 1000);
		अगर (status)
			वापस status;
	पूर्ण
	वापस usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
			       HUB_CLEAR_TT_BUFFER, USB_RT_PORT, devinfo,
			       tt, शून्य, 0, 1000);
पूर्ण

/*
 * क्रमागतeration blocks hub_wq क्रम a दीर्घ समय. we use keventd instead, since
 * दीर्घ blocking there is the exception, not the rule.  accordingly, HCDs
 * talking to TTs must queue control transfers (not just bulk and iso), so
 * both can talk to the same hub concurrently.
 */
अटल व्योम hub_tt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_hub		*hub =
		container_of(work, काष्ठा usb_hub, tt.clear_work);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&hub->tt.lock, flags);
	जबतक (!list_empty(&hub->tt.clear_list)) अणु
		काष्ठा list_head	*next;
		काष्ठा usb_tt_clear	*clear;
		काष्ठा usb_device	*hdev = hub->hdev;
		स्थिर काष्ठा hc_driver	*drv;
		पूर्णांक			status;

		next = hub->tt.clear_list.next;
		clear = list_entry(next, काष्ठा usb_tt_clear, clear_list);
		list_del(&clear->clear_list);

		/* drop lock so HCD can concurrently report other TT errors */
		spin_unlock_irqrestore(&hub->tt.lock, flags);
		status = hub_clear_tt_buffer(hdev, clear->devinfo, clear->tt);
		अगर (status && status != -ENODEV)
			dev_err(&hdev->dev,
				"clear tt %d (%04x) error %d\n",
				clear->tt, clear->devinfo, status);

		/* Tell the HCD, even अगर the operation failed */
		drv = clear->hcd->driver;
		अगर (drv->clear_tt_buffer_complete)
			(drv->clear_tt_buffer_complete)(clear->hcd, clear->ep);

		kमुक्त(clear);
		spin_lock_irqsave(&hub->tt.lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&hub->tt.lock, flags);
पूर्ण

/**
 * usb_hub_set_port_घातer - control hub port's घातer state
 * @hdev: USB device beदीर्घing to the usb hub
 * @hub: target hub
 * @port1: port index
 * @set: expected status
 *
 * call this function to control port's घातer via setting or
 * clearing the port's PORT_POWER feature.
 *
 * Return: 0 अगर successful. A negative error code otherwise.
 */
पूर्णांक usb_hub_set_port_घातer(काष्ठा usb_device *hdev, काष्ठा usb_hub *hub,
			   पूर्णांक port1, bool set)
अणु
	पूर्णांक ret;

	अगर (set)
		ret = set_port_feature(hdev, port1, USB_PORT_FEAT_POWER);
	अन्यथा
		ret = usb_clear_port_feature(hdev, port1, USB_PORT_FEAT_POWER);

	अगर (ret)
		वापस ret;

	अगर (set)
		set_bit(port1, hub->घातer_bits);
	अन्यथा
		clear_bit(port1, hub->घातer_bits);
	वापस 0;
पूर्ण

/**
 * usb_hub_clear_tt_buffer - clear control/bulk TT state in high speed hub
 * @urb: an URB associated with the failed or incomplete split transaction
 *
 * High speed HCDs use this to tell the hub driver that some split control or
 * bulk transaction failed in a way that requires clearing पूर्णांकernal state of
 * a transaction translator.  This is normally detected (and reported) from
 * पूर्णांकerrupt context.
 *
 * It may not be possible क्रम that hub to handle additional full (or low)
 * speed transactions until that state is fully cleared out.
 *
 * Return: 0 अगर successful. A negative error code otherwise.
 */
पूर्णांक usb_hub_clear_tt_buffer(काष्ठा urb *urb)
अणु
	काष्ठा usb_device	*udev = urb->dev;
	पूर्णांक			pipe = urb->pipe;
	काष्ठा usb_tt		*tt = udev->tt;
	अचिन्हित दीर्घ		flags;
	काष्ठा usb_tt_clear	*clear;

	/* we've got to cope with an arbitrary number of pending TT clears,
	 * since each TT has "at least two" buffers that can need it (and
	 * there can be many TTs per hub).  even अगर they're uncommon.
	 */
	clear = kदो_स्मृति(माप *clear, GFP_ATOMIC);
	अगर (clear == शून्य) अणु
		dev_err(&udev->dev, "can't save CLEAR_TT_BUFFER state\n");
		/* FIXME recover somehow ... RESET_TT? */
		वापस -ENOMEM;
	पूर्ण

	/* info that CLEAR_TT_BUFFER needs */
	clear->tt = tt->multi ? udev->ttport : 1;
	clear->devinfo = usb_pipeendpoपूर्णांक (pipe);
	clear->devinfo |= ((u16)udev->devaddr) << 4;
	clear->devinfo |= usb_pipecontrol(pipe)
			? (USB_ENDPOINT_XFER_CONTROL << 11)
			: (USB_ENDPOINT_XFER_BULK << 11);
	अगर (usb_pipein(pipe))
		clear->devinfo |= 1 << 15;

	/* info क्रम completion callback */
	clear->hcd = bus_to_hcd(udev->bus);
	clear->ep = urb->ep;

	/* tell keventd to clear state क्रम this TT */
	spin_lock_irqsave(&tt->lock, flags);
	list_add_tail(&clear->clear_list, &tt->clear_list);
	schedule_work(&tt->clear_work);
	spin_unlock_irqrestore(&tt->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hub_clear_tt_buffer);

अटल व्योम hub_घातer_on(काष्ठा usb_hub *hub, bool करो_delay)
अणु
	पूर्णांक port1;

	/* Enable घातer on each port.  Some hubs have reserved values
	 * of LPSM (> 2) in their descriptors, even though they are
	 * USB 2.0 hubs.  Some hubs करो not implement port-घातer चयनing
	 * but only emulate it.  In all हालs, the ports won't work
	 * unless we send these messages to the hub.
	 */
	अगर (hub_is_port_घातer_चयनable(hub))
		dev_dbg(hub->पूर्णांकfdev, "enabling power on all ports\n");
	अन्यथा
		dev_dbg(hub->पूर्णांकfdev, "trying to enable port power on "
				"non-switchable hub\n");
	क्रम (port1 = 1; port1 <= hub->hdev->maxchild; port1++)
		अगर (test_bit(port1, hub->घातer_bits))
			set_port_feature(hub->hdev, port1, USB_PORT_FEAT_POWER);
		अन्यथा
			usb_clear_port_feature(hub->hdev, port1,
						USB_PORT_FEAT_POWER);
	अगर (करो_delay)
		msleep(hub_घातer_on_good_delay(hub));
पूर्ण

अटल पूर्णांक hub_hub_status(काष्ठा usb_hub *hub,
		u16 *status, u16 *change)
अणु
	पूर्णांक ret;

	mutex_lock(&hub->status_mutex);
	ret = get_hub_status(hub->hdev, &hub->status->hub);
	अगर (ret < 0) अणु
		अगर (ret != -ENODEV)
			dev_err(hub->पूर्णांकfdev,
				"%s failed (err = %d)\n", __func__, ret);
	पूर्ण अन्यथा अणु
		*status = le16_to_cpu(hub->status->hub.wHubStatus);
		*change = le16_to_cpu(hub->status->hub.wHubChange);
		ret = 0;
	पूर्ण
	mutex_unlock(&hub->status_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक hub_set_port_link_state(काष्ठा usb_hub *hub, पूर्णांक port1,
			अचिन्हित पूर्णांक link_status)
अणु
	वापस set_port_feature(hub->hdev,
			port1 | (link_status << 3),
			USB_PORT_FEAT_LINK_STATE);
पूर्ण

/*
 * Disable a port and mark a logical connect-change event, so that some
 * समय later hub_wq will disconnect() any existing usb_device on the port
 * and will re-क्रमागतerate अगर there actually is a device attached.
 */
अटल व्योम hub_port_logical_disconnect(काष्ठा usb_hub *hub, पूर्णांक port1)
अणु
	dev_dbg(&hub->ports[port1 - 1]->dev, "logical disconnect\n");
	hub_port_disable(hub, port1, 1);

	/* FIXME let caller ask to घातer करोwn the port:
	 *  - some devices won't क्रमागतerate without a VBUS घातer cycle
	 *  - SRP saves घातer that way
	 *  - ... new call, TBD ...
	 * That's easy अगर this hub can चयन घातer per-port, and
	 * hub_wq reactivates the port later (समयr, SRP, etc).
	 * Powerकरोwn must be optional, because of reset/DFU.
	 */

	set_bit(port1, hub->change_bits);
	kick_hub_wq(hub);
पूर्ण

/**
 * usb_हटाओ_device - disable a device's port on its parent hub
 * @udev: device to be disabled and हटाओd
 * Context: @udev locked, must be able to sleep.
 *
 * After @udev's port has been disabled, hub_wq is notअगरied and it will
 * see that the device has been disconnected.  When the device is
 * physically unplugged and something is plugged in, the events will
 * be received and processed normally.
 *
 * Return: 0 अगर successful. A negative error code otherwise.
 */
पूर्णांक usb_हटाओ_device(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक ret;

	अगर (!udev->parent)	/* Can't हटाओ a root hub */
		वापस -EINVAL;
	hub = usb_hub_to_काष्ठा_hub(udev->parent);
	पूर्णांकf = to_usb_पूर्णांकerface(hub->पूर्णांकfdev);

	ret = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	set_bit(udev->portnum, hub->हटाओd_bits);
	hub_port_logical_disconnect(hub, udev->portnum);
	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
	वापस 0;
पूर्ण

क्रमागत hub_activation_type अणु
	HUB_INIT, HUB_INIT2, HUB_INIT3,		/* INITs must come first */
	HUB_POST_RESET, HUB_RESUME, HUB_RESET_RESUME,
पूर्ण;

अटल व्योम hub_init_func2(काष्ठा work_काष्ठा *ws);
अटल व्योम hub_init_func3(काष्ठा work_काष्ठा *ws);

अटल व्योम hub_activate(काष्ठा usb_hub *hub, क्रमागत hub_activation_type type)
अणु
	काष्ठा usb_device *hdev = hub->hdev;
	काष्ठा usb_hcd *hcd;
	पूर्णांक ret;
	पूर्णांक port1;
	पूर्णांक status;
	bool need_debounce_delay = false;
	अचिन्हित delay;

	/* Continue a partial initialization */
	अगर (type == HUB_INIT2 || type == HUB_INIT3) अणु
		device_lock(&hdev->dev);

		/* Was the hub disconnected जबतक we were रुकोing? */
		अगर (hub->disconnected)
			जाओ disconnected;
		अगर (type == HUB_INIT2)
			जाओ init2;
		जाओ init3;
	पूर्ण
	kref_get(&hub->kref);

	/* The superspeed hub except क्रम root hub has to use Hub Depth
	 * value as an offset पूर्णांकo the route string to locate the bits
	 * it uses to determine the करोwnstream port number. So hub driver
	 * should send a set hub depth request to superspeed hub after
	 * the superspeed hub is set configuration in initialization or
	 * reset procedure.
	 *
	 * After a resume, port घातer should still be on.
	 * For any other type of activation, turn it on.
	 */
	अगर (type != HUB_RESUME) अणु
		अगर (hdev->parent && hub_is_superspeed(hdev)) अणु
			ret = usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
					HUB_SET_DEPTH, USB_RT_HUB,
					hdev->level - 1, 0, शून्य, 0,
					USB_CTRL_SET_TIMEOUT);
			अगर (ret < 0)
				dev_err(hub->पूर्णांकfdev,
						"set hub depth failed\n");
		पूर्ण

		/* Speed up प्रणाली boot by using a delayed_work क्रम the
		 * hub's initial घातer-up delays.  This is pretty awkward
		 * and the implementation looks like a home-brewed sort of
		 * बनाओ_लाँघ/दीर्घ_लाँघ, but it saves at least 100 ms क्रम each
		 * root hub (assuming usbcore is compiled पूर्णांकo the kernel
		 * rather than as a module).  It adds up.
		 *
		 * This can't be करोne क्रम HUB_RESUME or HUB_RESET_RESUME
		 * because क्रम those activation types the ports have to be
		 * operational when we वापस.  In theory this could be करोne
		 * क्रम HUB_POST_RESET, but it's easier not to.
		 */
		अगर (type == HUB_INIT) अणु
			delay = hub_घातer_on_good_delay(hub);

			hub_घातer_on(hub, false);
			INIT_DELAYED_WORK(&hub->init_work, hub_init_func2);
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					&hub->init_work,
					msecs_to_jअगरfies(delay));

			/* Suppress स्वतःsuspend until init is करोne */
			usb_स्वतःpm_get_पूर्णांकerface_no_resume(
					to_usb_पूर्णांकerface(hub->पूर्णांकfdev));
			वापस;		/* Continues at init2: below */
		पूर्ण अन्यथा अगर (type == HUB_RESET_RESUME) अणु
			/* The पूर्णांकernal host controller state क्रम the hub device
			 * may be gone after a host घातer loss on प्रणाली resume.
			 * Update the device's info so the HW knows it's a hub.
			 */
			hcd = bus_to_hcd(hdev->bus);
			अगर (hcd->driver->update_hub_device) अणु
				ret = hcd->driver->update_hub_device(hcd, hdev,
						&hub->tt, GFP_NOIO);
				अगर (ret < 0) अणु
					dev_err(hub->पूर्णांकfdev,
						"Host not accepting hub info update\n");
					dev_err(hub->पूर्णांकfdev,
						"LS/FS devices and hubs may not work under this hub\n");
				पूर्ण
			पूर्ण
			hub_घातer_on(hub, true);
		पूर्ण अन्यथा अणु
			hub_घातer_on(hub, true);
		पूर्ण
	पूर्ण
 init2:

	/*
	 * Check each port and set hub->change_bits to let hub_wq know
	 * which ports need attention.
	 */
	क्रम (port1 = 1; port1 <= hdev->maxchild; ++port1) अणु
		काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
		काष्ठा usb_device *udev = port_dev->child;
		u16 portstatus, portchange;

		portstatus = portchange = 0;
		status = hub_port_status(hub, port1, &portstatus, &portchange);
		अगर (status)
			जाओ पात;

		अगर (udev || (portstatus & USB_PORT_STAT_CONNECTION))
			dev_dbg(&port_dev->dev, "status %04x change %04x\n",
					portstatus, portchange);

		/*
		 * After anything other than HUB_RESUME (i.e., initialization
		 * or any sort of reset), every port should be disabled.
		 * Unconnected ports should likewise be disabled (paranoia),
		 * and so should ports क्रम which we have no usb_device.
		 */
		अगर ((portstatus & USB_PORT_STAT_ENABLE) && (
				type != HUB_RESUME ||
				!(portstatus & USB_PORT_STAT_CONNECTION) ||
				!udev ||
				udev->state == USB_STATE_NOTATTACHED)) अणु
			/*
			 * USB3 protocol ports will स्वतःmatically transition
			 * to Enabled state when detect an USB3.0 device attach.
			 * Do not disable USB3 protocol ports, just pretend
			 * घातer was lost
			 */
			portstatus &= ~USB_PORT_STAT_ENABLE;
			अगर (!hub_is_superspeed(hdev))
				usb_clear_port_feature(hdev, port1,
						   USB_PORT_FEAT_ENABLE);
		पूर्ण

		/* Make sure a warm-reset request is handled by port_event */
		अगर (type == HUB_RESUME &&
		    hub_port_warm_reset_required(hub, port1, portstatus))
			set_bit(port1, hub->event_bits);

		/*
		 * Add debounce अगर USB3 link is in polling/link training state.
		 * Link will स्वतःmatically transition to Enabled state after
		 * link training completes.
		 */
		अगर (hub_is_superspeed(hdev) &&
		    ((portstatus & USB_PORT_STAT_LINK_STATE) ==
						USB_SS_PORT_LS_POLLING))
			need_debounce_delay = true;

		/* Clear status-change flags; we'll debounce later */
		अगर (portchange & USB_PORT_STAT_C_CONNECTION) अणु
			need_debounce_delay = true;
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_CONNECTION);
		पूर्ण
		अगर (portchange & USB_PORT_STAT_C_ENABLE) अणु
			need_debounce_delay = true;
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_ENABLE);
		पूर्ण
		अगर (portchange & USB_PORT_STAT_C_RESET) अणु
			need_debounce_delay = true;
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_RESET);
		पूर्ण
		अगर ((portchange & USB_PORT_STAT_C_BH_RESET) &&
				hub_is_superspeed(hub->hdev)) अणु
			need_debounce_delay = true;
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_BH_PORT_RESET);
		पूर्ण
		/* We can क्रमget about a "removed" device when there's a
		 * physical disconnect or the connect status changes.
		 */
		अगर (!(portstatus & USB_PORT_STAT_CONNECTION) ||
				(portchange & USB_PORT_STAT_C_CONNECTION))
			clear_bit(port1, hub->हटाओd_bits);

		अगर (!udev || udev->state == USB_STATE_NOTATTACHED) अणु
			/* Tell hub_wq to disconnect the device or
			 * check क्रम a new connection or over current condition.
			 * Based on USB2.0 Spec Section 11.12.5,
			 * C_PORT_OVER_CURRENT could be set जबतक
			 * PORT_OVER_CURRENT is not. So check क्रम any of them.
			 */
			अगर (udev || (portstatus & USB_PORT_STAT_CONNECTION) ||
			    (portchange & USB_PORT_STAT_C_CONNECTION) ||
			    (portstatus & USB_PORT_STAT_OVERCURRENT) ||
			    (portchange & USB_PORT_STAT_C_OVERCURRENT))
				set_bit(port1, hub->change_bits);

		पूर्ण अन्यथा अगर (portstatus & USB_PORT_STAT_ENABLE) अणु
			bool port_resumed = (portstatus &
					USB_PORT_STAT_LINK_STATE) ==
				USB_SS_PORT_LS_U0;
			/* The घातer session apparently survived the resume.
			 * If there was an overcurrent or suspend change
			 * (i.e., remote wakeup request), have hub_wq
			 * take care of it.  Look at the port link state
			 * क्रम USB 3.0 hubs, since they करोn't have a suspend
			 * change bit, and they करोn't set the port link change
			 * bit on device-initiated resume.
			 */
			अगर (portchange || (hub_is_superspeed(hub->hdev) &&
						port_resumed))
				set_bit(port1, hub->change_bits);

		पूर्ण अन्यथा अगर (udev->persist_enabled) अणु
#अगर_घोषित CONFIG_PM
			udev->reset_resume = 1;
#पूर्ण_अगर
			/* Don't set the change_bits when the device
			 * was घातered off.
			 */
			अगर (test_bit(port1, hub->घातer_bits))
				set_bit(port1, hub->change_bits);

		पूर्ण अन्यथा अणु
			/* The घातer session is gone; tell hub_wq */
			usb_set_device_state(udev, USB_STATE_NOTATTACHED);
			set_bit(port1, hub->change_bits);
		पूर्ण
	पूर्ण

	/* If no port-status-change flags were set, we करोn't need any
	 * debouncing.  If flags were set we can try to debounce the
	 * ports all at once right now, instead of letting hub_wq करो them
	 * one at a समय later on.
	 *
	 * If any port-status changes करो occur during this delay, hub_wq
	 * will see them later and handle them normally.
	 */
	अगर (need_debounce_delay) अणु
		delay = HUB_DEBOUNCE_STABLE;

		/* Don't करो a दीर्घ sleep inside a workqueue routine */
		अगर (type == HUB_INIT2) अणु
			INIT_DELAYED_WORK(&hub->init_work, hub_init_func3);
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					&hub->init_work,
					msecs_to_jअगरfies(delay));
			device_unlock(&hdev->dev);
			वापस;		/* Continues at init3: below */
		पूर्ण अन्यथा अणु
			msleep(delay);
		पूर्ण
	पूर्ण
 init3:
	hub->quiescing = 0;

	status = usb_submit_urb(hub->urb, GFP_NOIO);
	अगर (status < 0)
		dev_err(hub->पूर्णांकfdev, "activate --> %d\n", status);
	अगर (hub->has_indicators && blinkenlights)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				&hub->leds, LED_CYCLE_PERIOD);

	/* Scan all ports that need attention */
	kick_hub_wq(hub);
 पात:
	अगर (type == HUB_INIT2 || type == HUB_INIT3) अणु
		/* Allow स्वतःsuspend अगर it was suppressed */
 disconnected:
		usb_स्वतःpm_put_पूर्णांकerface_async(to_usb_पूर्णांकerface(hub->पूर्णांकfdev));
		device_unlock(&hdev->dev);
	पूर्ण

	kref_put(&hub->kref, hub_release);
पूर्ण

/* Implement the continuations क्रम the delays above */
अटल व्योम hub_init_func2(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा usb_hub *hub = container_of(ws, काष्ठा usb_hub, init_work.work);

	hub_activate(hub, HUB_INIT2);
पूर्ण

अटल व्योम hub_init_func3(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा usb_hub *hub = container_of(ws, काष्ठा usb_hub, init_work.work);

	hub_activate(hub, HUB_INIT3);
पूर्ण

क्रमागत hub_quiescing_type अणु
	HUB_DISCONNECT, HUB_PRE_RESET, HUB_SUSPEND
पूर्ण;

अटल व्योम hub_quiesce(काष्ठा usb_hub *hub, क्रमागत hub_quiescing_type type)
अणु
	काष्ठा usb_device *hdev = hub->hdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* hub_wq and related activity won't re-trigger */
	spin_lock_irqsave(&hub->irq_urb_lock, flags);
	hub->quiescing = 1;
	spin_unlock_irqrestore(&hub->irq_urb_lock, flags);

	अगर (type != HUB_SUSPEND) अणु
		/* Disconnect all the children */
		क्रम (i = 0; i < hdev->maxchild; ++i) अणु
			अगर (hub->ports[i]->child)
				usb_disconnect(&hub->ports[i]->child);
		पूर्ण
	पूर्ण

	/* Stop hub_wq and related activity */
	del_समयr_sync(&hub->irq_urb_retry);
	usb_समाप्त_urb(hub->urb);
	अगर (hub->has_indicators)
		cancel_delayed_work_sync(&hub->leds);
	अगर (hub->tt.hub)
		flush_work(&hub->tt.clear_work);
पूर्ण

अटल व्योम hub_pm_barrier_क्रम_all_ports(काष्ठा usb_hub *hub)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hub->hdev->maxchild; ++i)
		pm_runसमय_barrier(&hub->ports[i]->dev);
पूर्ण

/* caller has locked the hub device */
अटल पूर्णांक hub_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_hub *hub = usb_get_पूर्णांकfdata(पूर्णांकf);

	hub_quiesce(hub, HUB_PRE_RESET);
	hub->in_reset = 1;
	hub_pm_barrier_क्रम_all_ports(hub);
	वापस 0;
पूर्ण

/* caller has locked the hub device */
अटल पूर्णांक hub_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_hub *hub = usb_get_पूर्णांकfdata(पूर्णांकf);

	hub->in_reset = 0;
	hub_pm_barrier_क्रम_all_ports(hub);
	hub_activate(hub, HUB_POST_RESET);
	वापस 0;
पूर्ण

अटल पूर्णांक hub_configure(काष्ठा usb_hub *hub,
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा usb_device *hdev = hub->hdev;
	काष्ठा device *hub_dev = hub->पूर्णांकfdev;
	u16 hubstatus, hubchange;
	u16 wHubCharacteristics;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक maxp, ret, i;
	अक्षर *message = "out of memory";
	अचिन्हित unit_load;
	अचिन्हित full_load;
	अचिन्हित maxchild;

	hub->buffer = kदो_स्मृति(माप(*hub->buffer), GFP_KERNEL);
	अगर (!hub->buffer) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	hub->status = kदो_स्मृति(माप(*hub->status), GFP_KERNEL);
	अगर (!hub->status) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	mutex_init(&hub->status_mutex);

	hub->descriptor = kzalloc(माप(*hub->descriptor), GFP_KERNEL);
	अगर (!hub->descriptor) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* Request the entire hub descriptor.
	 * hub->descriptor can handle USB_MAXCHILDREN ports,
	 * but a (non-SS) hub can/will वापस fewer bytes here.
	 */
	ret = get_hub_descriptor(hdev, hub->descriptor);
	अगर (ret < 0) अणु
		message = "can't read hub descriptor";
		जाओ fail;
	पूर्ण

	maxchild = USB_MAXCHILDREN;
	अगर (hub_is_superspeed(hdev))
		maxchild = min_t(अचिन्हित, maxchild, USB_SS_MAXPORTS);

	अगर (hub->descriptor->bNbrPorts > maxchild) अणु
		message = "hub has too many ports!";
		ret = -ENODEV;
		जाओ fail;
	पूर्ण अन्यथा अगर (hub->descriptor->bNbrPorts == 0) अणु
		message = "hub doesn't have any ports!";
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	/*
	 * Accumulate wHubDelay + 40ns क्रम every hub in the tree of devices.
	 * The resulting value will be used क्रम SetIsochDelay() request.
	 */
	अगर (hub_is_superspeed(hdev) || hub_is_superspeedplus(hdev)) अणु
		u32 delay = __le16_to_cpu(hub->descriptor->u.ss.wHubDelay);

		अगर (hdev->parent)
			delay += hdev->parent->hub_delay;

		delay += USB_TP_TRANSMISSION_DELAY;
		hdev->hub_delay = min_t(u32, delay, USB_TP_TRANSMISSION_DELAY_MAX);
	पूर्ण

	maxchild = hub->descriptor->bNbrPorts;
	dev_info(hub_dev, "%d port%s detected\n", maxchild,
			(maxchild == 1) ? "" : "s");

	hub->ports = kसुस्मृति(maxchild, माप(काष्ठा usb_port *), GFP_KERNEL);
	अगर (!hub->ports) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	wHubCharacteristics = le16_to_cpu(hub->descriptor->wHubCharacteristics);
	अगर (hub_is_superspeed(hdev)) अणु
		unit_load = 150;
		full_load = 900;
	पूर्ण अन्यथा अणु
		unit_load = 100;
		full_load = 500;
	पूर्ण

	/* FIXME क्रम USB 3.0, skip क्रम now */
	अगर ((wHubCharacteristics & HUB_CHAR_COMPOUND) &&
			!(hub_is_superspeed(hdev))) अणु
		अक्षर	portstr[USB_MAXCHILDREN + 1];

		क्रम (i = 0; i < maxchild; i++)
			portstr[i] = hub->descriptor->u.hs.DeviceRemovable
				    [((i + 1) / 8)] & (1 << ((i + 1) % 8))
				? 'F' : 'R';
		portstr[maxchild] = 0;
		dev_dbg(hub_dev, "compound device; port removable status: %s\n", portstr);
	पूर्ण अन्यथा
		dev_dbg(hub_dev, "standalone hub\n");

	चयन (wHubCharacteristics & HUB_CHAR_LPSM) अणु
	हाल HUB_CHAR_COMMON_LPSM:
		dev_dbg(hub_dev, "ganged power switching\n");
		अवरोध;
	हाल HUB_CHAR_INDV_PORT_LPSM:
		dev_dbg(hub_dev, "individual port power switching\n");
		अवरोध;
	हाल HUB_CHAR_NO_LPSM:
	हाल HUB_CHAR_LPSM:
		dev_dbg(hub_dev, "no power switching (usb 1.0)\n");
		अवरोध;
	पूर्ण

	चयन (wHubCharacteristics & HUB_CHAR_OCPM) अणु
	हाल HUB_CHAR_COMMON_OCPM:
		dev_dbg(hub_dev, "global over-current protection\n");
		अवरोध;
	हाल HUB_CHAR_INDV_PORT_OCPM:
		dev_dbg(hub_dev, "individual port over-current protection\n");
		अवरोध;
	हाल HUB_CHAR_NO_OCPM:
	हाल HUB_CHAR_OCPM:
		dev_dbg(hub_dev, "no over-current protection\n");
		अवरोध;
	पूर्ण

	spin_lock_init(&hub->tt.lock);
	INIT_LIST_HEAD(&hub->tt.clear_list);
	INIT_WORK(&hub->tt.clear_work, hub_tt_work);
	चयन (hdev->descriptor.bDeviceProtocol) अणु
	हाल USB_HUB_PR_FS:
		अवरोध;
	हाल USB_HUB_PR_HS_SINGLE_TT:
		dev_dbg(hub_dev, "Single TT\n");
		hub->tt.hub = hdev;
		अवरोध;
	हाल USB_HUB_PR_HS_MULTI_TT:
		ret = usb_set_पूर्णांकerface(hdev, 0, 1);
		अगर (ret == 0) अणु
			dev_dbg(hub_dev, "TT per port\n");
			hub->tt.multi = 1;
		पूर्ण अन्यथा
			dev_err(hub_dev, "Using single TT (err %d)\n",
				ret);
		hub->tt.hub = hdev;
		अवरोध;
	हाल USB_HUB_PR_SS:
		/* USB 3.0 hubs करोn't have a TT */
		अवरोध;
	शेष:
		dev_dbg(hub_dev, "Unrecognized hub protocol %d\n",
			hdev->descriptor.bDeviceProtocol);
		अवरोध;
	पूर्ण

	/* Note 8 FS bit बार == (8 bits / 12000000 bps) ~= 666ns */
	चयन (wHubCharacteristics & HUB_CHAR_TTTT) अणु
	हाल HUB_TTTT_8_BITS:
		अगर (hdev->descriptor.bDeviceProtocol != 0) अणु
			hub->tt.think_समय = 666;
			dev_dbg(hub_dev, "TT requires at most %d "
					"FS bit times (%d ns)\n",
				8, hub->tt.think_समय);
		पूर्ण
		अवरोध;
	हाल HUB_TTTT_16_BITS:
		hub->tt.think_समय = 666 * 2;
		dev_dbg(hub_dev, "TT requires at most %d "
				"FS bit times (%d ns)\n",
			16, hub->tt.think_समय);
		अवरोध;
	हाल HUB_TTTT_24_BITS:
		hub->tt.think_समय = 666 * 3;
		dev_dbg(hub_dev, "TT requires at most %d "
				"FS bit times (%d ns)\n",
			24, hub->tt.think_समय);
		अवरोध;
	हाल HUB_TTTT_32_BITS:
		hub->tt.think_समय = 666 * 4;
		dev_dbg(hub_dev, "TT requires at most %d "
				"FS bit times (%d ns)\n",
			32, hub->tt.think_समय);
		अवरोध;
	पूर्ण

	/* probe() zeroes hub->indicator[] */
	अगर (wHubCharacteristics & HUB_CHAR_PORTIND) अणु
		hub->has_indicators = 1;
		dev_dbg(hub_dev, "Port indicators are supported\n");
	पूर्ण

	dev_dbg(hub_dev, "power on to power good time: %dms\n",
		hub->descriptor->bPwrOn2PwrGood * 2);

	/* घातer budgeting mostly matters with bus-घातered hubs,
	 * and battery-घातered root hubs (may provide just 8 mA).
	 */
	ret = usb_get_std_status(hdev, USB_RECIP_DEVICE, 0, &hubstatus);
	अगर (ret) अणु
		message = "can't get hub status";
		जाओ fail;
	पूर्ण
	hcd = bus_to_hcd(hdev->bus);
	अगर (hdev == hdev->bus->root_hub) अणु
		अगर (hcd->घातer_budget > 0)
			hdev->bus_mA = hcd->घातer_budget;
		अन्यथा
			hdev->bus_mA = full_load * maxchild;
		अगर (hdev->bus_mA >= full_load)
			hub->mA_per_port = full_load;
		अन्यथा अणु
			hub->mA_per_port = hdev->bus_mA;
			hub->limited_घातer = 1;
		पूर्ण
	पूर्ण अन्यथा अगर ((hubstatus & (1 << USB_DEVICE_SELF_POWERED)) == 0) अणु
		पूर्णांक reमुख्यing = hdev->bus_mA -
			hub->descriptor->bHubContrCurrent;

		dev_dbg(hub_dev, "hub controller current requirement: %dmA\n",
			hub->descriptor->bHubContrCurrent);
		hub->limited_घातer = 1;

		अगर (reमुख्यing < maxchild * unit_load)
			dev_warn(hub_dev,
					"insufficient power available "
					"to use all downstream ports\n");
		hub->mA_per_port = unit_load;	/* 7.2.1 */

	पूर्ण अन्यथा अणु	/* Self-घातered बाह्यal hub */
		/* FIXME: What about battery-घातered बाह्यal hubs that
		 * provide less current per port? */
		hub->mA_per_port = full_load;
	पूर्ण
	अगर (hub->mA_per_port < full_load)
		dev_dbg(hub_dev, "%umA bus power budget for each child\n",
				hub->mA_per_port);

	ret = hub_hub_status(hub, &hubstatus, &hubchange);
	अगर (ret < 0) अणु
		message = "can't get hub status";
		जाओ fail;
	पूर्ण

	/* local घातer status reports aren't always correct */
	अगर (hdev->actconfig->desc.bmAttributes & USB_CONFIG_ATT_SELFPOWER)
		dev_dbg(hub_dev, "local power source is %s\n",
			(hubstatus & HUB_STATUS_LOCAL_POWER)
			? "lost (inactive)" : "good");

	अगर ((wHubCharacteristics & HUB_CHAR_OCPM) == 0)
		dev_dbg(hub_dev, "%sover-current condition exists\n",
			(hubstatus & HUB_STATUS_OVERCURRENT) ? "" : "no ");

	/* set up the पूर्णांकerrupt endpoपूर्णांक
	 * We use the EP's maxpacket size instead of (PORTS+1+7)/8
	 * bytes as USB2.0[11.12.3] says because some hubs are known
	 * to send more data (and thus cause overflow). For root hubs,
	 * maxpktsize is defined in hcd.c's fake endpoपूर्णांक descriptors
	 * to be big enough क्रम at least USB_MAXCHILDREN ports. */
	pipe = usb_rcvपूर्णांकpipe(hdev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(hdev, pipe, usb_pipeout(pipe));

	अगर (maxp > माप(*hub->buffer))
		maxp = माप(*hub->buffer);

	hub->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!hub->urb) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	usb_fill_पूर्णांक_urb(hub->urb, hdev, pipe, *hub->buffer, maxp, hub_irq,
		hub, endpoपूर्णांक->bInterval);

	/* maybe cycle the hub leds */
	अगर (hub->has_indicators && blinkenlights)
		hub->indicator[0] = INDICATOR_CYCLE;

	mutex_lock(&usb_port_peer_mutex);
	क्रम (i = 0; i < maxchild; i++) अणु
		ret = usb_hub_create_port_device(hub, i + 1);
		अगर (ret < 0) अणु
			dev_err(hub->पूर्णांकfdev,
				"couldn't create port%d device.\n", i + 1);
			अवरोध;
		पूर्ण
	पूर्ण
	hdev->maxchild = i;
	क्रम (i = 0; i < hdev->maxchild; i++) अणु
		काष्ठा usb_port *port_dev = hub->ports[i];

		pm_runसमय_put(&port_dev->dev);
	पूर्ण

	mutex_unlock(&usb_port_peer_mutex);
	अगर (ret < 0)
		जाओ fail;

	/* Update the HCD's पूर्णांकernal representation of this hub beक्रमe hub_wq
	 * starts getting port status changes क्रम devices under the hub.
	 */
	अगर (hcd->driver->update_hub_device) अणु
		ret = hcd->driver->update_hub_device(hcd, hdev,
				&hub->tt, GFP_KERNEL);
		अगर (ret < 0) अणु
			message = "can't update HCD hub info";
			जाओ fail;
		पूर्ण
	पूर्ण

	usb_hub_adjust_deviceremovable(hdev, hub->descriptor);

	hub_activate(hub, HUB_INIT);
	वापस 0;

fail:
	dev_err(hub_dev, "config failed, %s (err %d)\n",
			message, ret);
	/* hub_disconnect() मुक्तs urb and descriptor */
	वापस ret;
पूर्ण

अटल व्योम hub_release(काष्ठा kref *kref)
अणु
	काष्ठा usb_hub *hub = container_of(kref, काष्ठा usb_hub, kref);

	usb_put_dev(hub->hdev);
	usb_put_पूर्णांकf(to_usb_पूर्णांकerface(hub->पूर्णांकfdev));
	kमुक्त(hub);
पूर्ण

अटल अचिन्हित highspeed_hubs;

अटल व्योम hub_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_hub *hub = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक port1;

	/*
	 * Stop adding new hub events. We करो not want to block here and thus
	 * will not try to हटाओ any pending work item.
	 */
	hub->disconnected = 1;

	/* Disconnect all children and quiesce the hub */
	hub->error = 0;
	hub_quiesce(hub, HUB_DISCONNECT);

	mutex_lock(&usb_port_peer_mutex);

	/* Aव्योम races with recursively_mark_NOTATTACHED() */
	spin_lock_irq(&device_state_lock);
	port1 = hdev->maxchild;
	hdev->maxchild = 0;
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	spin_unlock_irq(&device_state_lock);

	क्रम (; port1 > 0; --port1)
		usb_hub_हटाओ_port_device(hub, port1);

	mutex_unlock(&usb_port_peer_mutex);

	अगर (hub->hdev->speed == USB_SPEED_HIGH)
		highspeed_hubs--;

	usb_मुक्त_urb(hub->urb);
	kमुक्त(hub->ports);
	kमुक्त(hub->descriptor);
	kमुक्त(hub->status);
	kमुक्त(hub->buffer);

	pm_suspend_ignore_children(&पूर्णांकf->dev, false);

	अगर (hub->quirk_disable_स्वतःsuspend)
		usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);

	kref_put(&hub->kref, hub_release);
पूर्ण

अटल bool hub_descriptor_is_sane(काष्ठा usb_host_पूर्णांकerface *desc)
अणु
	/* Some hubs have a subclass of 1, which AFAICT according to the */
	/*  specs is not defined, but it works */
	अगर (desc->desc.bInterfaceSubClass != 0 &&
	    desc->desc.bInterfaceSubClass != 1)
		वापस false;

	/* Multiple endpoपूर्णांकs? What kind of mutant ninja-hub is this? */
	अगर (desc->desc.bNumEndpoपूर्णांकs != 1)
		वापस false;

	/* If the first endpoपूर्णांक is not पूर्णांकerrupt IN, we'd better punt! */
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(&desc->endpoपूर्णांक[0].desc))
		वापस false;

        वापस true;
पूर्ण

अटल पूर्णांक hub_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *desc;
	काष्ठा usb_device *hdev;
	काष्ठा usb_hub *hub;

	desc = पूर्णांकf->cur_altsetting;
	hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	/*
	 * Set शेष स्वतःsuspend delay as 0 to speedup bus suspend,
	 * based on the below considerations:
	 *
	 * - Unlike other drivers, the hub driver करोes not rely on the
	 *   स्वतःsuspend delay to provide enough समय to handle a wakeup
	 *   event, and the submitted status URB is just to check future
	 *   change on hub करोwnstream ports, so it is safe to करो it.
	 *
	 * - The patch might cause one or more स्वतः supend/resume क्रम
	 *   below very rare devices when they are plugged पूर्णांकo hub
	 *   first समय:
	 *
	 *   	devices having trouble initializing, and disconnect
	 *   	themselves from the bus and then reconnect a second
	 *   	or so later
	 *
	 *   	devices just क्रम करोwnloading firmware, and disconnects
	 *   	themselves after completing it
	 *
	 *   For these quite rare devices, their drivers may change the
	 *   स्वतःsuspend delay of their parent hub in the probe() to one
	 *   appropriate value to aव्योम the subtle problem अगर someone
	 *   करोes care it.
	 *
	 * - The patch may cause one or more स्वतः suspend/resume on
	 *   hub during running 'lsusb', but it is probably too
	 *   infrequent to worry about.
	 *
	 * - Change स्वतःsuspend delay of hub can aव्योम unnecessary स्वतः
	 *   suspend समयr क्रम hub, also may decrease घातer consumption
	 *   of USB bus.
	 *
	 * - If user has indicated to prevent स्वतःsuspend by passing
	 *   usbcore.स्वतःsuspend = -1 then keep स्वतःsuspend disabled.
	 */
#अगर_घोषित CONFIG_PM
	अगर (hdev->dev.घातer.स्वतःsuspend_delay >= 0)
		pm_runसमय_set_स्वतःsuspend_delay(&hdev->dev, 0);
#पूर्ण_अगर

	/*
	 * Hubs have proper suspend/resume support, except क्रम root hubs
	 * where the controller driver करोesn't have bus_suspend and
	 * bus_resume methods.
	 */
	अगर (hdev->parent) अणु		/* normal device */
		usb_enable_स्वतःsuspend(hdev);
	पूर्ण अन्यथा अणु			/* root hub */
		स्थिर काष्ठा hc_driver *drv = bus_to_hcd(hdev->bus)->driver;

		अगर (drv->bus_suspend && drv->bus_resume)
			usb_enable_स्वतःsuspend(hdev);
	पूर्ण

	अगर (hdev->level == MAX_TOPO_LEVEL) अणु
		dev_err(&पूर्णांकf->dev,
			"Unsupported bus topology: hub nested too deep\n");
		वापस -E2BIG;
	पूर्ण

#अगर_घोषित	CONFIG_USB_OTG_DISABLE_EXTERNAL_HUB
	अगर (hdev->parent) अणु
		dev_warn(&पूर्णांकf->dev, "ignoring external hub\n");
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर

	अगर (!hub_descriptor_is_sane(desc)) अणु
		dev_err(&पूर्णांकf->dev, "bad descriptor, ignoring hub\n");
		वापस -EIO;
	पूर्ण

	/* We found a hub */
	dev_info(&पूर्णांकf->dev, "USB hub found\n");

	hub = kzalloc(माप(*hub), GFP_KERNEL);
	अगर (!hub)
		वापस -ENOMEM;

	kref_init(&hub->kref);
	hub->पूर्णांकfdev = &पूर्णांकf->dev;
	hub->hdev = hdev;
	INIT_DELAYED_WORK(&hub->leds, led_work);
	INIT_DELAYED_WORK(&hub->init_work, शून्य);
	INIT_WORK(&hub->events, hub_event);
	spin_lock_init(&hub->irq_urb_lock);
	समयr_setup(&hub->irq_urb_retry, hub_retry_irq_urb, 0);
	usb_get_पूर्णांकf(पूर्णांकf);
	usb_get_dev(hdev);

	usb_set_पूर्णांकfdata(पूर्णांकf, hub);
	पूर्णांकf->needs_remote_wakeup = 1;
	pm_suspend_ignore_children(&पूर्णांकf->dev, true);

	अगर (hdev->speed == USB_SPEED_HIGH)
		highspeed_hubs++;

	अगर (id->driver_info & HUB_QUIRK_CHECK_PORT_AUTOSUSPEND)
		hub->quirk_check_port_स्वतः_suspend = 1;

	अगर (id->driver_info & HUB_QUIRK_DISABLE_AUTOSUSPEND) अणु
		hub->quirk_disable_स्वतःsuspend = 1;
		usb_स्वतःpm_get_पूर्णांकerface_no_resume(पूर्णांकf);
	पूर्ण

	अगर (hub_configure(hub, &desc->endpoपूर्णांक[0].desc) >= 0)
		वापस 0;

	hub_disconnect(पूर्णांकf);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
hub_ioctl(काष्ठा usb_पूर्णांकerface *पूर्णांकf, अचिन्हित पूर्णांक code, व्योम *user_data)
अणु
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);

	/* निश्चित अगरno == 0 (part of hub spec) */
	चयन (code) अणु
	हाल USBDEVFS_HUB_PORTINFO: अणु
		काष्ठा usbdevfs_hub_portinfo *info = user_data;
		पूर्णांक i;

		spin_lock_irq(&device_state_lock);
		अगर (hdev->devnum <= 0)
			info->nports = 0;
		अन्यथा अणु
			info->nports = hdev->maxchild;
			क्रम (i = 0; i < info->nports; i++) अणु
				अगर (hub->ports[i]->child == शून्य)
					info->port[i] = 0;
				अन्यथा
					info->port[i] =
						hub->ports[i]->child->devnum;
			पूर्ण
		पूर्ण
		spin_unlock_irq(&device_state_lock);

		वापस info->nports + 1;
		पूर्ण

	शेष:
		वापस -ENOSYS;
	पूर्ण
पूर्ण

/*
 * Allow user programs to claim ports on a hub.  When a device is attached
 * to one of these "claimed" ports, the program will "own" the device.
 */
अटल पूर्णांक find_port_owner(काष्ठा usb_device *hdev, अचिन्हित port1,
		काष्ठा usb_dev_state ***pघातner)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);

	अगर (hdev->state == USB_STATE_NOTATTACHED)
		वापस -ENODEV;
	अगर (port1 == 0 || port1 > hdev->maxchild)
		वापस -EINVAL;

	/* Devices not managed by the hub driver
	 * will always have maxchild equal to 0.
	 */
	*pघातner = &(hub->ports[port1 - 1]->port_owner);
	वापस 0;
पूर्ण

/* In the following three functions, the caller must hold hdev's lock */
पूर्णांक usb_hub_claim_port(काष्ठा usb_device *hdev, अचिन्हित port1,
		       काष्ठा usb_dev_state *owner)
अणु
	पूर्णांक rc;
	काष्ठा usb_dev_state **घातner;

	rc = find_port_owner(hdev, port1, &घातner);
	अगर (rc)
		वापस rc;
	अगर (*घातner)
		वापस -EBUSY;
	*घातner = owner;
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hub_claim_port);

पूर्णांक usb_hub_release_port(काष्ठा usb_device *hdev, अचिन्हित port1,
			 काष्ठा usb_dev_state *owner)
अणु
	पूर्णांक rc;
	काष्ठा usb_dev_state **घातner;

	rc = find_port_owner(hdev, port1, &घातner);
	अगर (rc)
		वापस rc;
	अगर (*घातner != owner)
		वापस -ENOENT;
	*घातner = शून्य;
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hub_release_port);

व्योम usb_hub_release_all_ports(काष्ठा usb_device *hdev, काष्ठा usb_dev_state *owner)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);
	पूर्णांक n;

	क्रम (n = 0; n < hdev->maxchild; n++) अणु
		अगर (hub->ports[n]->port_owner == owner)
			hub->ports[n]->port_owner = शून्य;
	पूर्ण

पूर्ण

/* The caller must hold udev's lock */
bool usb_device_is_owned(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub;

	अगर (udev->state == USB_STATE_NOTATTACHED || !udev->parent)
		वापस false;
	hub = usb_hub_to_काष्ठा_hub(udev->parent);
	वापस !!hub->ports[udev->portnum - 1]->port_owner;
पूर्ण

अटल व्योम recursively_mark_NOTATTACHED(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(udev);
	पूर्णांक i;

	क्रम (i = 0; i < udev->maxchild; ++i) अणु
		अगर (hub->ports[i]->child)
			recursively_mark_NOTATTACHED(hub->ports[i]->child);
	पूर्ण
	अगर (udev->state == USB_STATE_SUSPENDED)
		udev->active_duration -= jअगरfies;
	udev->state = USB_STATE_NOTATTACHED;
पूर्ण

/**
 * usb_set_device_state - change a device's current state (usbcore, hcds)
 * @udev: poपूर्णांकer to device whose state should be changed
 * @new_state: new state value to be stored
 *
 * udev->state is _not_ fully रक्षित by the device lock.  Although
 * most transitions are made only जबतक holding the lock, the state can
 * can change to USB_STATE_NOTATTACHED at almost any समय.  This
 * is so that devices can be marked as disconnected as soon as possible,
 * without having to रुको क्रम any semaphores to be released.  As a result,
 * all changes to any device's state must be रक्षित by the
 * device_state_lock spinlock.
 *
 * Once a device has been added to the device tree, all changes to its state
 * should be made using this routine.  The state should _not_ be set directly.
 *
 * If udev->state is alपढ़ोy USB_STATE_NOTATTACHED then no change is made.
 * Otherwise udev->state is set to new_state, and अगर new_state is
 * USB_STATE_NOTATTACHED then all of udev's descendants' states are also set
 * to USB_STATE_NOTATTACHED.
 */
व्योम usb_set_device_state(काष्ठा usb_device *udev,
		क्रमागत usb_device_state new_state)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक wakeup = -1;

	spin_lock_irqsave(&device_state_lock, flags);
	अगर (udev->state == USB_STATE_NOTATTACHED)
		;	/* करो nothing */
	अन्यथा अगर (new_state != USB_STATE_NOTATTACHED) अणु

		/* root hub wakeup capabilities are managed out-of-band
		 * and may involve silicon errata ... ignore them here.
		 */
		अगर (udev->parent) अणु
			अगर (udev->state == USB_STATE_SUSPENDED
					|| new_state == USB_STATE_SUSPENDED)
				;	/* No change to wakeup settings */
			अन्यथा अगर (new_state == USB_STATE_CONFIGURED)
				wakeup = (udev->quirks &
					USB_QUIRK_IGNORE_REMOTE_WAKEUP) ? 0 :
					udev->actconfig->desc.bmAttributes &
					USB_CONFIG_ATT_WAKEUP;
			अन्यथा
				wakeup = 0;
		पूर्ण
		अगर (udev->state == USB_STATE_SUSPENDED &&
			new_state != USB_STATE_SUSPENDED)
			udev->active_duration -= jअगरfies;
		अन्यथा अगर (new_state == USB_STATE_SUSPENDED &&
				udev->state != USB_STATE_SUSPENDED)
			udev->active_duration += jअगरfies;
		udev->state = new_state;
	पूर्ण अन्यथा
		recursively_mark_NOTATTACHED(udev);
	spin_unlock_irqrestore(&device_state_lock, flags);
	अगर (wakeup >= 0)
		device_set_wakeup_capable(&udev->dev, wakeup);
पूर्ण
EXPORT_SYMBOL_GPL(usb_set_device_state);

/*
 * Choose a device number.
 *
 * Device numbers are used as filenames in usbfs.  On USB-1.1 and
 * USB-2.0 buses they are also used as device addresses, however on
 * USB-3.0 buses the address is asचिन्हित by the controller hardware
 * and it usually is not the same as the device number.
 *
 * WUSB devices are simple: they have no hubs behind, so the mapping
 * device <-> भव port number becomes 1:1. Why? to simplअगरy the
 * lअगरe of the device connection logic in
 * drivers/usb/wusbcore/devconnect.c. When we करो the initial secret
 * handshake we need to assign a temporary address in the unauthorized
 * space. For simplicity we use the first भव port number found to
 * be मुक्त [drivers/usb/wusbcore/devconnect.c:wusbhc_devconnect_ack()]
 * and that becomes it's address [X < 128] or its unauthorized address
 * [X | 0x80].
 *
 * We add 1 as an offset to the one-based USB-stack port number
 * (zero-based wusb भव port index) क्रम two reasons: (a) dev addr
 * 0 is reserved by USB क्रम शेष address; (b) Linux's USB stack
 * uses always #1 क्रम the root hub of the controller. So USB stack's
 * port #1, which is wusb भव-port #0 has address #2.
 *
 * Devices connected under xHCI are not as simple.  The host controller
 * supports भवization, so the hardware assigns device addresses and
 * the HCD must setup data काष्ठाures beक्रमe issuing a set address
 * command to the hardware.
 */
अटल व्योम choose_devnum(काष्ठा usb_device *udev)
अणु
	पूर्णांक		devnum;
	काष्ठा usb_bus	*bus = udev->bus;

	/* be safe when more hub events are proceed in parallel */
	mutex_lock(&bus->devnum_next_mutex);
	अगर (udev->wusb) अणु
		devnum = udev->portnum + 1;
		BUG_ON(test_bit(devnum, bus->devmap.devicemap));
	पूर्ण अन्यथा अणु
		/* Try to allocate the next devnum beginning at
		 * bus->devnum_next. */
		devnum = find_next_zero_bit(bus->devmap.devicemap, 128,
					    bus->devnum_next);
		अगर (devnum >= 128)
			devnum = find_next_zero_bit(bus->devmap.devicemap,
						    128, 1);
		bus->devnum_next = (devnum >= 127 ? 1 : devnum + 1);
	पूर्ण
	अगर (devnum < 128) अणु
		set_bit(devnum, bus->devmap.devicemap);
		udev->devnum = devnum;
	पूर्ण
	mutex_unlock(&bus->devnum_next_mutex);
पूर्ण

अटल व्योम release_devnum(काष्ठा usb_device *udev)
अणु
	अगर (udev->devnum > 0) अणु
		clear_bit(udev->devnum, udev->bus->devmap.devicemap);
		udev->devnum = -1;
	पूर्ण
पूर्ण

अटल व्योम update_devnum(काष्ठा usb_device *udev, पूर्णांक devnum)
अणु
	/* The address क्रम a WUSB device is managed by wusbcore. */
	अगर (!udev->wusb)
		udev->devnum = devnum;
	अगर (!udev->devaddr)
		udev->devaddr = (u8)devnum;
पूर्ण

अटल व्योम hub_मुक्त_dev(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	/* Root hubs aren't real devices, so don't मुक्त HCD resources */
	अगर (hcd->driver->मुक्त_dev && udev->parent)
		hcd->driver->मुक्त_dev(hcd, udev);
पूर्ण

अटल व्योम hub_disconnect_children(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(udev);
	पूर्णांक i;

	/* Free up all the children beक्रमe we हटाओ this device */
	क्रम (i = 0; i < udev->maxchild; i++) अणु
		अगर (hub->ports[i]->child)
			usb_disconnect(&hub->ports[i]->child);
	पूर्ण
पूर्ण

/**
 * usb_disconnect - disconnect a device (usbcore-पूर्णांकernal)
 * @pdev: poपूर्णांकer to device being disconnected
 *
 * Context: task context, might sleep
 *
 * Something got disconnected. Get rid of it and all of its children.
 *
 * If *pdev is a normal device then the parent hub must alपढ़ोy be locked.
 * If *pdev is a root hub then the caller must hold the usb_bus_idr_lock,
 * which protects the set of root hubs as well as the list of buses.
 *
 * Only hub drivers (including भव root hub drivers क्रम host
 * controllers) should ever call this.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 */
व्योम usb_disconnect(काष्ठा usb_device **pdev)
अणु
	काष्ठा usb_port *port_dev = शून्य;
	काष्ठा usb_device *udev = *pdev;
	काष्ठा usb_hub *hub = शून्य;
	पूर्णांक port1 = 1;

	/* mark the device as inactive, so any further urb submissions क्रम
	 * this device (and any of its children) will fail immediately.
	 * this quiesces everything except pending urbs.
	 */
	usb_set_device_state(udev, USB_STATE_NOTATTACHED);
	dev_info(&udev->dev, "USB disconnect, device number %d\n",
			udev->devnum);

	/*
	 * Ensure that the pm runसमय code knows that the USB device
	 * is in the process of being disconnected.
	 */
	pm_runसमय_barrier(&udev->dev);

	usb_lock_device(udev);

	hub_disconnect_children(udev);

	/* deallocate hcd/hardware state ... nuking all pending urbs and
	 * cleaning up all state associated with the current configuration
	 * so that the hardware is now fully quiesced.
	 */
	dev_dbg(&udev->dev, "unregistering device\n");
	usb_disable_device(udev, 0);
	usb_hcd_synchronize_unlinks(udev);

	अगर (udev->parent) अणु
		port1 = udev->portnum;
		hub = usb_hub_to_काष्ठा_hub(udev->parent);
		port_dev = hub->ports[port1 - 1];

		sysfs_हटाओ_link(&udev->dev.kobj, "port");
		sysfs_हटाओ_link(&port_dev->dev.kobj, "device");

		/*
		 * As usb_port_runसमय_resume() de-references udev, make
		 * sure no resumes occur during removal
		 */
		अगर (!test_and_set_bit(port1, hub->child_usage_bits))
			pm_runसमय_get_sync(&port_dev->dev);
	पूर्ण

	usb_हटाओ_ep_devs(&udev->ep0);
	usb_unlock_device(udev);

	/* Unरेजिस्टर the device.  The device driver is responsible
	 * क्रम de-configuring the device and invoking the हटाओ-device
	 * notअगरier chain (used by usbfs and possibly others).
	 */
	device_del(&udev->dev);

	/* Free the device number and delete the parent's children[]
	 * (or root_hub) poपूर्णांकer.
	 */
	release_devnum(udev);

	/* Aव्योम races with recursively_mark_NOTATTACHED() */
	spin_lock_irq(&device_state_lock);
	*pdev = शून्य;
	spin_unlock_irq(&device_state_lock);

	अगर (port_dev && test_and_clear_bit(port1, hub->child_usage_bits))
		pm_runसमय_put(&port_dev->dev);

	hub_मुक्त_dev(udev);

	put_device(&udev->dev);
पूर्ण

#अगर_घोषित CONFIG_USB_ANNOUNCE_NEW_DEVICES
अटल व्योम show_string(काष्ठा usb_device *udev, अक्षर *id, अक्षर *string)
अणु
	अगर (!string)
		वापस;
	dev_info(&udev->dev, "%s: %s\n", id, string);
पूर्ण

अटल व्योम announce_device(काष्ठा usb_device *udev)
अणु
	u16 bcdDevice = le16_to_cpu(udev->descriptor.bcdDevice);

	dev_info(&udev->dev,
		"New USB device found, idVendor=%04x, idProduct=%04x, bcdDevice=%2x.%02x\n",
		le16_to_cpu(udev->descriptor.idVenकरोr),
		le16_to_cpu(udev->descriptor.idProduct),
		bcdDevice >> 8, bcdDevice & 0xff);
	dev_info(&udev->dev,
		"New USB device strings: Mfr=%d, Product=%d, SerialNumber=%d\n",
		udev->descriptor.iManufacturer,
		udev->descriptor.iProduct,
		udev->descriptor.iSerialNumber);
	show_string(udev, "Product", udev->product);
	show_string(udev, "Manufacturer", udev->manufacturer);
	show_string(udev, "SerialNumber", udev->serial);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम announce_device(काष्ठा usb_device *udev) अणु पूर्ण
#पूर्ण_अगर


/**
 * usb_क्रमागतerate_device_otg - FIXME (usbcore-पूर्णांकernal)
 * @udev: newly addressed device (in ADDRESS state)
 *
 * Finish क्रमागतeration क्रम On-The-Go devices
 *
 * Return: 0 अगर successful. A negative error code otherwise.
 */
अटल पूर्णांक usb_क्रमागतerate_device_otg(काष्ठा usb_device *udev)
अणु
	पूर्णांक err = 0;

#अगर_घोषित	CONFIG_USB_OTG
	/*
	 * OTG-aware devices on OTG-capable root hubs may be able to use SRP,
	 * to wake us after we've घातered off VBUS; and HNP, चयनing roles
	 * "host" to "peripheral".  The OTG descriptor helps figure this out.
	 */
	अगर (!udev->bus->is_b_host
			&& udev->config
			&& udev->parent == udev->bus->root_hub) अणु
		काष्ठा usb_otg_descriptor	*desc = शून्य;
		काष्ठा usb_bus			*bus = udev->bus;
		अचिन्हित			port1 = udev->portnum;

		/* descriptor may appear anywhere in config */
		err = __usb_get_extra_descriptor(udev->rawdescriptors[0],
				le16_to_cpu(udev->config[0].desc.wTotalLength),
				USB_DT_OTG, (व्योम **) &desc, माप(*desc));
		अगर (err || !(desc->bmAttributes & USB_OTG_HNP))
			वापस 0;

		dev_info(&udev->dev, "Dual-Role OTG device on %sHNP port\n",
					(port1 == bus->otg_port) ? "" : "non-");

		/* enable HNP beक्रमe suspend, it's simpler */
		अगर (port1 == bus->otg_port) अणु
			bus->b_hnp_enable = 1;
			err = usb_control_msg(udev,
				usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE, 0,
				USB_DEVICE_B_HNP_ENABLE,
				0, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);
			अगर (err < 0) अणु
				/*
				 * OTG MESSAGE: report errors here,
				 * customize to match your product.
				 */
				dev_err(&udev->dev, "can't set HNP mode: %d\n",
									err);
				bus->b_hnp_enable = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (desc->bLength == माप
				(काष्ठा usb_otg_descriptor)) अणु
			/* Set a_alt_hnp_support क्रम legacy otg device */
			err = usb_control_msg(udev,
				usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE, 0,
				USB_DEVICE_A_ALT_HNP_SUPPORT,
				0, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);
			अगर (err < 0)
				dev_err(&udev->dev,
					"set a_alt_hnp_support failed: %d\n",
					err);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस err;
पूर्ण


/**
 * usb_क्रमागतerate_device - Read device configs/पूर्णांकfs/otg (usbcore-पूर्णांकernal)
 * @udev: newly addressed device (in ADDRESS state)
 *
 * This is only called by usb_new_device() and usb_authorize_device()
 * and FIXME -- all comments that apply to them apply here wrt to
 * environment.
 *
 * If the device is WUSB and not authorized, we करोn't attempt to पढ़ो
 * the string descriptors, as they will be errored out by the device
 * until it has been authorized.
 *
 * Return: 0 अगर successful. A negative error code otherwise.
 */
अटल पूर्णांक usb_क्रमागतerate_device(काष्ठा usb_device *udev)
अणु
	पूर्णांक err;
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	अगर (udev->config == शून्य) अणु
		err = usb_get_configuration(udev);
		अगर (err < 0) अणु
			अगर (err != -ENODEV)
				dev_err(&udev->dev, "can't read configurations, error %d\n",
						err);
			वापस err;
		पूर्ण
	पूर्ण

	/* पढ़ो the standard strings and cache them अगर present */
	udev->product = usb_cache_string(udev, udev->descriptor.iProduct);
	udev->manufacturer = usb_cache_string(udev,
					      udev->descriptor.iManufacturer);
	udev->serial = usb_cache_string(udev, udev->descriptor.iSerialNumber);

	err = usb_क्रमागतerate_device_otg(udev);
	अगर (err < 0)
		वापस err;

	अगर (IS_ENABLED(CONFIG_USB_OTG_PRODUCTLIST) && hcd->tpl_support &&
		!is_targeted(udev)) अणु
		/* Maybe it can talk to us, though we can't talk to it.
		 * (Includes HNP test device.)
		 */
		अगर (IS_ENABLED(CONFIG_USB_OTG) && (udev->bus->b_hnp_enable
			|| udev->bus->is_b_host)) अणु
			err = usb_port_suspend(udev, PMSG_AUTO_SUSPEND);
			अगर (err < 0)
				dev_dbg(&udev->dev, "HNP fail, %d\n", err);
		पूर्ण
		वापस -ENOTSUPP;
	पूर्ण

	usb_detect_पूर्णांकerface_quirks(udev);

	वापस 0;
पूर्ण

अटल व्योम set_usb_port_removable(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_device *hdev = udev->parent;
	काष्ठा usb_hub *hub;
	u8 port = udev->portnum;
	u16 wHubCharacteristics;
	bool removable = true;

	अगर (!hdev)
		वापस;

	hub = usb_hub_to_काष्ठा_hub(udev->parent);

	/*
	 * If the platक्रमm firmware has provided inक्रमmation about a port,
	 * use that to determine whether it's removable.
	 */
	चयन (hub->ports[udev->portnum - 1]->connect_type) अणु
	हाल USB_PORT_CONNECT_TYPE_HOT_PLUG:
		udev->removable = USB_DEVICE_REMOVABLE;
		वापस;
	हाल USB_PORT_CONNECT_TYPE_HARD_WIRED:
	हाल USB_PORT_NOT_USED:
		udev->removable = USB_DEVICE_FIXED;
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Otherwise, check whether the hub knows whether a port is removable
	 * or not
	 */
	wHubCharacteristics = le16_to_cpu(hub->descriptor->wHubCharacteristics);

	अगर (!(wHubCharacteristics & HUB_CHAR_COMPOUND))
		वापस;

	अगर (hub_is_superspeed(hdev)) अणु
		अगर (le16_to_cpu(hub->descriptor->u.ss.DeviceRemovable)
				& (1 << port))
			removable = false;
	पूर्ण अन्यथा अणु
		अगर (hub->descriptor->u.hs.DeviceRemovable[port / 8] & (1 << (port % 8)))
			removable = false;
	पूर्ण

	अगर (removable)
		udev->removable = USB_DEVICE_REMOVABLE;
	अन्यथा
		udev->removable = USB_DEVICE_FIXED;

पूर्ण

/**
 * usb_new_device - perक्रमm initial device setup (usbcore-पूर्णांकernal)
 * @udev: newly addressed device (in ADDRESS state)
 *
 * This is called with devices which have been detected but not fully
 * क्रमागतerated.  The device descriptor is available, but not descriptors
 * क्रम any device configuration.  The caller must have locked either
 * the parent hub (अगर udev is a normal device) or अन्यथा the
 * usb_bus_idr_lock (अगर udev is a root hub).  The parent's poपूर्णांकer to
 * udev has alपढ़ोy been installed, but udev is not yet visible through
 * sysfs or other fileप्रणाली code.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 *
 * Only the hub driver or root-hub registrar should ever call this.
 *
 * Return: Whether the device is configured properly or not. Zero अगर the
 * पूर्णांकerface was रेजिस्टरed with the driver core; अन्यथा a negative त्रुटि_सं
 * value.
 *
 */
पूर्णांक usb_new_device(काष्ठा usb_device *udev)
अणु
	पूर्णांक err;

	अगर (udev->parent) अणु
		/* Initialize non-root-hub device wakeup to disabled;
		 * device (un)configuration controls wakeup capable
		 * sysfs घातer/wakeup controls wakeup enabled/disabled
		 */
		device_init_wakeup(&udev->dev, 0);
	पूर्ण

	/* Tell the runसमय-PM framework the device is active */
	pm_runसमय_set_active(&udev->dev);
	pm_runसमय_get_noresume(&udev->dev);
	pm_runसमय_use_स्वतःsuspend(&udev->dev);
	pm_runसमय_enable(&udev->dev);

	/* By शेष, क्रमbid स्वतःsuspend क्रम all devices.  It will be
	 * allowed क्रम hubs during binding.
	 */
	usb_disable_स्वतःsuspend(udev);

	err = usb_क्रमागतerate_device(udev);	/* Read descriptors */
	अगर (err < 0)
		जाओ fail;
	dev_dbg(&udev->dev, "udev %d, busnum %d, minor = %d\n",
			udev->devnum, udev->bus->busnum,
			(((udev->bus->busnum-1) * 128) + (udev->devnum-1)));
	/* export the usbdev device-node क्रम libusb */
	udev->dev.devt = MKDEV(USB_DEVICE_MAJOR,
			(((udev->bus->busnum-1) * 128) + (udev->devnum-1)));

	/* Tell the world! */
	announce_device(udev);

	अगर (udev->serial)
		add_device_अक्रमomness(udev->serial, म_माप(udev->serial));
	अगर (udev->product)
		add_device_अक्रमomness(udev->product, म_माप(udev->product));
	अगर (udev->manufacturer)
		add_device_अक्रमomness(udev->manufacturer,
				      म_माप(udev->manufacturer));

	device_enable_async_suspend(&udev->dev);

	/* check whether the hub or firmware marks this port as non-removable */
	अगर (udev->parent)
		set_usb_port_removable(udev);

	/* Register the device.  The device driver is responsible
	 * क्रम configuring the device and invoking the add-device
	 * notअगरier chain (used by usbfs and possibly others).
	 */
	err = device_add(&udev->dev);
	अगर (err) अणु
		dev_err(&udev->dev, "can't device_add, error %d\n", err);
		जाओ fail;
	पूर्ण

	/* Create link files between child device and usb port device. */
	अगर (udev->parent) अणु
		काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(udev->parent);
		पूर्णांक port1 = udev->portnum;
		काष्ठा usb_port	*port_dev = hub->ports[port1 - 1];

		err = sysfs_create_link(&udev->dev.kobj,
				&port_dev->dev.kobj, "port");
		अगर (err)
			जाओ fail;

		err = sysfs_create_link(&port_dev->dev.kobj,
				&udev->dev.kobj, "device");
		अगर (err) अणु
			sysfs_हटाओ_link(&udev->dev.kobj, "port");
			जाओ fail;
		पूर्ण

		अगर (!test_and_set_bit(port1, hub->child_usage_bits))
			pm_runसमय_get_sync(&port_dev->dev);
	पूर्ण

	(व्योम) usb_create_ep_devs(&udev->dev, &udev->ep0, udev);
	usb_mark_last_busy(udev);
	pm_runसमय_put_sync_स्वतःsuspend(&udev->dev);
	वापस err;

fail:
	usb_set_device_state(udev, USB_STATE_NOTATTACHED);
	pm_runसमय_disable(&udev->dev);
	pm_runसमय_set_suspended(&udev->dev);
	वापस err;
पूर्ण


/**
 * usb_deauthorize_device - deauthorize a device (usbcore-पूर्णांकernal)
 * @usb_dev: USB device
 *
 * Move the USB device to a very basic state where पूर्णांकerfaces are disabled
 * and the device is in fact unconfigured and unusable.
 *
 * We share a lock (that we have) with device_del(), so we need to
 * defer its call.
 *
 * Return: 0.
 */
पूर्णांक usb_deauthorize_device(काष्ठा usb_device *usb_dev)
अणु
	usb_lock_device(usb_dev);
	अगर (usb_dev->authorized == 0)
		जाओ out_unauthorized;

	usb_dev->authorized = 0;
	usb_set_configuration(usb_dev, -1);

out_unauthorized:
	usb_unlock_device(usb_dev);
	वापस 0;
पूर्ण


पूर्णांक usb_authorize_device(काष्ठा usb_device *usb_dev)
अणु
	पूर्णांक result = 0, c;

	usb_lock_device(usb_dev);
	अगर (usb_dev->authorized == 1)
		जाओ out_authorized;

	result = usb_स्वतःresume_device(usb_dev);
	अगर (result < 0) अणु
		dev_err(&usb_dev->dev,
			"can't autoresume for authorization: %d\n", result);
		जाओ error_स्वतःresume;
	पूर्ण

	अगर (usb_dev->wusb) अणु
		result = usb_get_device_descriptor(usb_dev, माप(usb_dev->descriptor));
		अगर (result < 0) अणु
			dev_err(&usb_dev->dev, "can't re-read device descriptor for "
				"authorization: %d\n", result);
			जाओ error_device_descriptor;
		पूर्ण
	पूर्ण

	usb_dev->authorized = 1;
	/* Choose and set the configuration.  This रेजिस्टरs the पूर्णांकerfaces
	 * with the driver core and lets पूर्णांकerface drivers bind to them.
	 */
	c = usb_choose_configuration(usb_dev);
	अगर (c >= 0) अणु
		result = usb_set_configuration(usb_dev, c);
		अगर (result) अणु
			dev_err(&usb_dev->dev,
				"can't set config #%d, error %d\n", c, result);
			/* This need not be fatal.  The user can try to
			 * set other configurations. */
		पूर्ण
	पूर्ण
	dev_info(&usb_dev->dev, "authorized to connect\n");

error_device_descriptor:
	usb_स्वतःsuspend_device(usb_dev);
error_स्वतःresume:
out_authorized:
	usb_unlock_device(usb_dev);	/* complements locktree */
	वापस result;
पूर्ण

/**
 * get_port_ssp_rate - Match the extended port status to SSP rate
 * @hdev: The hub device
 * @ext_portstatus: extended port status
 *
 * Match the extended port status speed id to the SuperSpeed Plus sublink speed
 * capability attributes. Base on the number of connected lanes and speed,
 * वापस the corresponding क्रमागत usb_ssp_rate.
 */
अटल क्रमागत usb_ssp_rate get_port_ssp_rate(काष्ठा usb_device *hdev,
					   u32 ext_portstatus)
अणु
	काष्ठा usb_ssp_cap_descriptor *ssp_cap = hdev->bos->ssp_cap;
	u32 attr;
	u8 speed_id;
	u8 ssac;
	u8 lanes;
	पूर्णांक i;

	अगर (!ssp_cap)
		जाओ out;

	speed_id = ext_portstatus & USB_EXT_PORT_STAT_RX_SPEED_ID;
	lanes = USB_EXT_PORT_RX_LANES(ext_portstatus) + 1;

	ssac = le32_to_cpu(ssp_cap->bmAttributes) &
		USB_SSP_SUBLINK_SPEED_ATTRIBS;

	क्रम (i = 0; i <= ssac; i++) अणु
		u8 ssid;

		attr = le32_to_cpu(ssp_cap->bmSublinkSpeedAttr[i]);
		ssid = FIELD_GET(USB_SSP_SUBLINK_SPEED_SSID, attr);
		अगर (speed_id == ssid) अणु
			u16 mantissa;
			u8 lse;
			u8 type;

			/*
			 * Note: currently asymmetric lane types are only
			 * applicable क्रम SSIC operate in SuperSpeed protocol
			 */
			type = FIELD_GET(USB_SSP_SUBLINK_SPEED_ST, attr);
			अगर (type == USB_SSP_SUBLINK_SPEED_ST_ASYM_RX ||
			    type == USB_SSP_SUBLINK_SPEED_ST_ASYM_TX)
				जाओ out;

			अगर (FIELD_GET(USB_SSP_SUBLINK_SPEED_LP, attr) !=
			    USB_SSP_SUBLINK_SPEED_LP_SSP)
				जाओ out;

			lse = FIELD_GET(USB_SSP_SUBLINK_SPEED_LSE, attr);
			mantissa = FIELD_GET(USB_SSP_SUBLINK_SPEED_LSM, attr);

			/* Convert to Gbps */
			क्रम (; lse < USB_SSP_SUBLINK_SPEED_LSE_GBPS; lse++)
				mantissa /= 1000;

			अगर (mantissa >= 10 && lanes == 1)
				वापस USB_SSP_GEN_2x1;

			अगर (mantissa >= 10 && lanes == 2)
				वापस USB_SSP_GEN_2x2;

			अगर (mantissa >= 5 && lanes == 2)
				वापस USB_SSP_GEN_1x2;

			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस USB_SSP_GEN_UNKNOWN;
पूर्ण

/* Returns 1 अगर @hub is a WUSB root hub, 0 otherwise */
अटल अचिन्हित hub_is_wusb(काष्ठा usb_hub *hub)
अणु
	काष्ठा usb_hcd *hcd;
	अगर (hub->hdev->parent != शून्य)  /* not a root hub? */
		वापस 0;
	hcd = bus_to_hcd(hub->hdev->bus);
	वापस hcd->wireless;
पूर्ण


#अगर_घोषित CONFIG_USB_FEW_INIT_RETRIES
#घोषणा PORT_RESET_TRIES	2
#घोषणा SET_ADDRESS_TRIES	1
#घोषणा GET_DESCRIPTOR_TRIES	1
#घोषणा GET_MAXPACKET0_TRIES	1
#घोषणा PORT_INIT_TRIES		4

#अन्यथा
#घोषणा PORT_RESET_TRIES	5
#घोषणा SET_ADDRESS_TRIES	2
#घोषणा GET_DESCRIPTOR_TRIES	2
#घोषणा GET_MAXPACKET0_TRIES	3
#घोषणा PORT_INIT_TRIES		4
#पूर्ण_अगर	/* CONFIG_USB_FEW_INIT_RETRIES */

#घोषणा HUB_ROOT_RESET_TIME	60	/* बार are in msec */
#घोषणा HUB_SHORT_RESET_TIME	10
#घोषणा HUB_BH_RESET_TIME	50
#घोषणा HUB_LONG_RESET_TIME	200
#घोषणा HUB_RESET_TIMEOUT	800

अटल bool use_new_scheme(काष्ठा usb_device *udev, पूर्णांक retry,
			   काष्ठा usb_port *port_dev)
अणु
	पूर्णांक old_scheme_first_port =
		(port_dev->quirks & USB_PORT_QUIRK_OLD_SCHEME) ||
		old_scheme_first;

	/*
	 * "New scheme" क्रमागतeration causes an extra state transition to be
	 * exposed to an xhci host and causes USB3 devices to receive control
	 * commands in the शेष state.  This has been seen to cause
	 * क्रमागतeration failures, so disable this क्रमागतeration scheme क्रम USB3
	 * devices.
	 */
	अगर (udev->speed >= USB_SPEED_SUPER)
		वापस false;

	/*
	 * If use_both_schemes is set, use the first scheme (whichever
	 * it is) क्रम the larger half of the retries, then use the other
	 * scheme.  Otherwise, use the first scheme क्रम all the retries.
	 */
	अगर (use_both_schemes && retry >= (PORT_INIT_TRIES + 1) / 2)
		वापस old_scheme_first_port;	/* Second half */
	वापस !old_scheme_first_port;		/* First half or all */
पूर्ण

/* Is a USB 3.0 port in the Inactive or Compliance Mode state?
 * Port warm reset is required to recover
 */
अटल bool hub_port_warm_reset_required(काष्ठा usb_hub *hub, पूर्णांक port1,
		u16 portstatus)
अणु
	u16 link_state;

	अगर (!hub_is_superspeed(hub->hdev))
		वापस false;

	अगर (test_bit(port1, hub->warm_reset_bits))
		वापस true;

	link_state = portstatus & USB_PORT_STAT_LINK_STATE;
	वापस link_state == USB_SS_PORT_LS_SS_INACTIVE
		|| link_state == USB_SS_PORT_LS_COMP_MOD;
पूर्ण

अटल पूर्णांक hub_port_रुको_reset(काष्ठा usb_hub *hub, पूर्णांक port1,
			काष्ठा usb_device *udev, अचिन्हित पूर्णांक delay, bool warm)
अणु
	पूर्णांक delay_समय, ret;
	u16 portstatus;
	u16 portchange;
	u32 ext_portstatus = 0;

	क्रम (delay_समय = 0;
			delay_समय < HUB_RESET_TIMEOUT;
			delay_समय += delay) अणु
		/* रुको to give the device a chance to reset */
		msleep(delay);

		/* पढ़ो and decode port status */
		अगर (hub_is_superspeedplus(hub->hdev))
			ret = hub_ext_port_status(hub, port1,
						  HUB_EXT_PORT_STATUS,
						  &portstatus, &portchange,
						  &ext_portstatus);
		अन्यथा
			ret = hub_port_status(hub, port1, &portstatus,
					      &portchange);
		अगर (ret < 0)
			वापस ret;

		/*
		 * The port state is unknown until the reset completes.
		 *
		 * On top of that, some chips may require additional समय
		 * to re-establish a connection after the reset is complete,
		 * so also रुको क्रम the connection to be re-established.
		 */
		अगर (!(portstatus & USB_PORT_STAT_RESET) &&
		    (portstatus & USB_PORT_STAT_CONNECTION))
			अवरोध;

		/* चयन to the दीर्घ delay after two लघु delay failures */
		अगर (delay_समय >= 2 * HUB_SHORT_RESET_TIME)
			delay = HUB_LONG_RESET_TIME;

		dev_dbg(&hub->ports[port1 - 1]->dev,
				"not %sreset yet, waiting %dms\n",
				warm ? "warm " : "", delay);
	पूर्ण

	अगर ((portstatus & USB_PORT_STAT_RESET))
		वापस -EBUSY;

	अगर (hub_port_warm_reset_required(hub, port1, portstatus))
		वापस -ENOTCONN;

	/* Device went away? */
	अगर (!(portstatus & USB_PORT_STAT_CONNECTION))
		वापस -ENOTCONN;

	/* Retry अगर connect change is set but status is still connected.
	 * A USB 3.0 connection may bounce अगर multiple warm resets were issued,
	 * but the device may have successfully re-connected. Ignore it.
	 */
	अगर (!hub_is_superspeed(hub->hdev) &&
	    (portchange & USB_PORT_STAT_C_CONNECTION)) अणु
		usb_clear_port_feature(hub->hdev, port1,
				       USB_PORT_FEAT_C_CONNECTION);
		वापस -EAGAIN;
	पूर्ण

	अगर (!(portstatus & USB_PORT_STAT_ENABLE))
		वापस -EBUSY;

	अगर (!udev)
		वापस 0;

	अगर (hub_is_superspeedplus(hub->hdev)) अणु
		/* extended portstatus Rx and Tx lane count are zero based */
		udev->rx_lanes = USB_EXT_PORT_RX_LANES(ext_portstatus) + 1;
		udev->tx_lanes = USB_EXT_PORT_TX_LANES(ext_portstatus) + 1;
		udev->ssp_rate = get_port_ssp_rate(hub->hdev, ext_portstatus);
	पूर्ण अन्यथा अणु
		udev->rx_lanes = 1;
		udev->tx_lanes = 1;
		udev->ssp_rate = USB_SSP_GEN_UNKNOWN;
	पूर्ण
	अगर (hub_is_wusb(hub))
		udev->speed = USB_SPEED_WIRELESS;
	अन्यथा अगर (udev->ssp_rate != USB_SSP_GEN_UNKNOWN)
		udev->speed = USB_SPEED_SUPER_PLUS;
	अन्यथा अगर (hub_is_superspeed(hub->hdev))
		udev->speed = USB_SPEED_SUPER;
	अन्यथा अगर (portstatus & USB_PORT_STAT_HIGH_SPEED)
		udev->speed = USB_SPEED_HIGH;
	अन्यथा अगर (portstatus & USB_PORT_STAT_LOW_SPEED)
		udev->speed = USB_SPEED_LOW;
	अन्यथा
		udev->speed = USB_SPEED_FULL;
	वापस 0;
पूर्ण

/* Handle port reset and port warm(BH) reset (क्रम USB3 protocol ports) */
अटल पूर्णांक hub_port_reset(काष्ठा usb_hub *hub, पूर्णांक port1,
			काष्ठा usb_device *udev, अचिन्हित पूर्णांक delay, bool warm)
अणु
	पूर्णांक i, status;
	u16 portchange, portstatus;
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	पूर्णांक reset_recovery_समय;

	अगर (!hub_is_superspeed(hub->hdev)) अणु
		अगर (warm) अणु
			dev_err(hub->पूर्णांकfdev, "only USB3 hub support "
						"warm reset\n");
			वापस -EINVAL;
		पूर्ण
		/* Block EHCI CF initialization during the port reset.
		 * Some companion controllers करोn't like it when they mix.
		 */
		करोwn_पढ़ो(&ehci_cf_port_reset_rwsem);
	पूर्ण अन्यथा अगर (!warm) अणु
		/*
		 * If the caller hasn't explicitly requested a warm reset,
		 * द्विगुन check and see अगर one is needed.
		 */
		अगर (hub_port_status(hub, port1, &portstatus, &portchange) == 0)
			अगर (hub_port_warm_reset_required(hub, port1,
							portstatus))
				warm = true;
	पूर्ण
	clear_bit(port1, hub->warm_reset_bits);

	/* Reset the port */
	क्रम (i = 0; i < PORT_RESET_TRIES; i++) अणु
		status = set_port_feature(hub->hdev, port1, (warm ?
					USB_PORT_FEAT_BH_PORT_RESET :
					USB_PORT_FEAT_RESET));
		अगर (status == -ENODEV) अणु
			;	/* The hub is gone */
		पूर्ण अन्यथा अगर (status) अणु
			dev_err(&port_dev->dev,
					"cannot %sreset (err = %d)\n",
					warm ? "warm " : "", status);
		पूर्ण अन्यथा अणु
			status = hub_port_रुको_reset(hub, port1, udev, delay,
								warm);
			अगर (status && status != -ENOTCONN && status != -ENODEV)
				dev_dbg(hub->पूर्णांकfdev,
						"port_wait_reset: err = %d\n",
						status);
		पूर्ण

		/* Check क्रम disconnect or reset */
		अगर (status == 0 || status == -ENOTCONN || status == -ENODEV) अणु
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_RESET);

			अगर (!hub_is_superspeed(hub->hdev))
				जाओ करोne;

			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_BH_PORT_RESET);
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_PORT_LINK_STATE);

			अगर (udev)
				usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_CONNECTION);

			/*
			 * If a USB 3.0 device migrates from reset to an error
			 * state, re-issue the warm reset.
			 */
			अगर (hub_port_status(hub, port1,
					&portstatus, &portchange) < 0)
				जाओ करोne;

			अगर (!hub_port_warm_reset_required(hub, port1,
					portstatus))
				जाओ करोne;

			/*
			 * If the port is in SS.Inactive or Compliance Mode, the
			 * hot or warm reset failed.  Try another warm reset.
			 */
			अगर (!warm) अणु
				dev_dbg(&port_dev->dev,
						"hot reset failed, warm reset\n");
				warm = true;
			पूर्ण
		पूर्ण

		dev_dbg(&port_dev->dev,
				"not enabled, trying %sreset again...\n",
				warm ? "warm " : "");
		delay = HUB_LONG_RESET_TIME;
	पूर्ण

	dev_err(&port_dev->dev, "Cannot enable. Maybe the USB cable is bad?\n");

करोne:
	अगर (status == 0) अणु
		अगर (port_dev->quirks & USB_PORT_QUIRK_FAST_ENUM)
			usleep_range(10000, 12000);
		अन्यथा अणु
			/* TRSTRCY = 10 ms; plus some extra */
			reset_recovery_समय = 10 + 40;

			/* Hub needs extra delay after resetting its port. */
			अगर (hub->hdev->quirks & USB_QUIRK_HUB_SLOW_RESET)
				reset_recovery_समय += 100;

			msleep(reset_recovery_समय);
		पूर्ण

		अगर (udev) अणु
			काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

			update_devnum(udev, 0);
			/* The xHC may think the device is alपढ़ोy reset,
			 * so ignore the status.
			 */
			अगर (hcd->driver->reset_device)
				hcd->driver->reset_device(hcd, udev);

			usb_set_device_state(udev, USB_STATE_DEFAULT);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (udev)
			usb_set_device_state(udev, USB_STATE_NOTATTACHED);
	पूर्ण

	अगर (!hub_is_superspeed(hub->hdev))
		up_पढ़ो(&ehci_cf_port_reset_rwsem);

	वापस status;
पूर्ण

/* Check अगर a port is घातer on */
अटल पूर्णांक port_is_घातer_on(काष्ठा usb_hub *hub, अचिन्हित portstatus)
अणु
	पूर्णांक ret = 0;

	अगर (hub_is_superspeed(hub->hdev)) अणु
		अगर (portstatus & USB_SS_PORT_STAT_POWER)
			ret = 1;
	पूर्ण अन्यथा अणु
		अगर (portstatus & USB_PORT_STAT_POWER)
			ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम usb_lock_port(काष्ठा usb_port *port_dev)
		__acquires(&port_dev->status_lock)
अणु
	mutex_lock(&port_dev->status_lock);
	__acquire(&port_dev->status_lock);
पूर्ण

अटल व्योम usb_unlock_port(काष्ठा usb_port *port_dev)
		__releases(&port_dev->status_lock)
अणु
	mutex_unlock(&port_dev->status_lock);
	__release(&port_dev->status_lock);
पूर्ण

#अगर_घोषित	CONFIG_PM

/* Check अगर a port is suspended(USB2.0 port) or in U3 state(USB3.0 port) */
अटल पूर्णांक port_is_suspended(काष्ठा usb_hub *hub, अचिन्हित portstatus)
अणु
	पूर्णांक ret = 0;

	अगर (hub_is_superspeed(hub->hdev)) अणु
		अगर ((portstatus & USB_PORT_STAT_LINK_STATE)
				== USB_SS_PORT_LS_U3)
			ret = 1;
	पूर्ण अन्यथा अणु
		अगर (portstatus & USB_PORT_STAT_SUSPEND)
			ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

/* Determine whether the device on a port is पढ़ोy क्रम a normal resume,
 * is पढ़ोy क्रम a reset-resume, or should be disconnected.
 */
अटल पूर्णांक check_port_resume_type(काष्ठा usb_device *udev,
		काष्ठा usb_hub *hub, पूर्णांक port1,
		पूर्णांक status, u16 portchange, u16 portstatus)
अणु
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	पूर्णांक retries = 3;

 retry:
	/* Is a warm reset needed to recover the connection? */
	अगर (status == 0 && udev->reset_resume
		&& hub_port_warm_reset_required(hub, port1, portstatus)) अणु
		/* pass */;
	पूर्ण
	/* Is the device still present? */
	अन्यथा अगर (status || port_is_suspended(hub, portstatus) ||
			!port_is_घातer_on(hub, portstatus)) अणु
		अगर (status >= 0)
			status = -ENODEV;
	पूर्ण अन्यथा अगर (!(portstatus & USB_PORT_STAT_CONNECTION)) अणु
		अगर (retries--) अणु
			usleep_range(200, 300);
			status = hub_port_status(hub, port1, &portstatus,
							     &portchange);
			जाओ retry;
		पूर्ण
		status = -ENODEV;
	पूर्ण

	/* Can't do a normal resume if the port isn't enabled,
	 * so try a reset-resume instead.
	 */
	अन्यथा अगर (!(portstatus & USB_PORT_STAT_ENABLE) && !udev->reset_resume) अणु
		अगर (udev->persist_enabled)
			udev->reset_resume = 1;
		अन्यथा
			status = -ENODEV;
	पूर्ण

	अगर (status) अणु
		dev_dbg(&port_dev->dev, "status %04x.%04x after resume, %d\n",
				portchange, portstatus, status);
	पूर्ण अन्यथा अगर (udev->reset_resume) अणु

		/* Late port hanकरोff can set status-change bits */
		अगर (portchange & USB_PORT_STAT_C_CONNECTION)
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_CONNECTION);
		अगर (portchange & USB_PORT_STAT_C_ENABLE)
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_ENABLE);

		/*
		 * Whatever made this reset-resume necessary may have
		 * turned on the port1 bit in hub->change_bits.  But after
		 * a successful reset-resume we want the bit to be clear;
		 * अगर it was on it would indicate that something happened
		 * following the reset-resume.
		 */
		clear_bit(port1, hub->change_bits);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक usb_disable_lपंचांग(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	/* Check अगर the roothub and device supports LTM. */
	अगर (!usb_device_supports_lपंचांग(hcd->self.root_hub) ||
			!usb_device_supports_lपंचांग(udev))
		वापस 0;

	/* Clear Feature LTM Enable can only be sent अगर the device is
	 * configured.
	 */
	अगर (!udev->actconfig)
		वापस 0;

	वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			USB_REQ_CLEAR_FEATURE, USB_RECIP_DEVICE,
			USB_DEVICE_LTM_ENABLE, 0, शून्य, 0,
			USB_CTRL_SET_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(usb_disable_lपंचांग);

व्योम usb_enable_lपंचांग(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	/* Check अगर the roothub and device supports LTM. */
	अगर (!usb_device_supports_lपंचांग(hcd->self.root_hub) ||
			!usb_device_supports_lपंचांग(udev))
		वापस;

	/* Set Feature LTM Enable can only be sent अगर the device is
	 * configured.
	 */
	अगर (!udev->actconfig)
		वापस;

	usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			USB_REQ_SET_FEATURE, USB_RECIP_DEVICE,
			USB_DEVICE_LTM_ENABLE, 0, शून्य, 0,
			USB_CTRL_SET_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(usb_enable_lपंचांग);

/*
 * usb_enable_remote_wakeup - enable remote wakeup क्रम a device
 * @udev: target device
 *
 * For USB-2 devices: Set the device's remote wakeup feature.
 *
 * For USB-3 devices: Assume there's only one function on the device and
 * enable remote wake क्रम the first पूर्णांकerface.  FIXME अगर the पूर्णांकerface
 * association descriptor shows there's more than one function.
 */
अटल पूर्णांक usb_enable_remote_wakeup(काष्ठा usb_device *udev)
अणु
	अगर (udev->speed < USB_SPEED_SUPER)
		वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE, USB_RECIP_DEVICE,
				USB_DEVICE_REMOTE_WAKEUP, 0, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);
	अन्यथा
		वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE, USB_RECIP_INTERFACE,
				USB_INTRF_FUNC_SUSPEND,
				USB_INTRF_FUNC_SUSPEND_RW |
					USB_INTRF_FUNC_SUSPEND_LP,
				शून्य, 0, USB_CTRL_SET_TIMEOUT);
पूर्ण

/*
 * usb_disable_remote_wakeup - disable remote wakeup क्रम a device
 * @udev: target device
 *
 * For USB-2 devices: Clear the device's remote wakeup feature.
 *
 * For USB-3 devices: Assume there's only one function on the device and
 * disable remote wake क्रम the first पूर्णांकerface.  FIXME अगर the पूर्णांकerface
 * association descriptor shows there's more than one function.
 */
अटल पूर्णांक usb_disable_remote_wakeup(काष्ठा usb_device *udev)
अणु
	अगर (udev->speed < USB_SPEED_SUPER)
		वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_CLEAR_FEATURE, USB_RECIP_DEVICE,
				USB_DEVICE_REMOTE_WAKEUP, 0, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);
	अन्यथा
		वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE, USB_RECIP_INTERFACE,
				USB_INTRF_FUNC_SUSPEND,	0, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);
पूर्ण

/* Count of wakeup-enabled devices at or below udev */
अचिन्हित usb_wakeup_enabled_descendants(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(udev);

	वापस udev->करो_remote_wakeup +
			(hub ? hub->wakeup_enabled_descendants : 0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_wakeup_enabled_descendants);

/*
 * usb_port_suspend - suspend a usb device's upstream port
 * @udev: device that's no दीर्घer in active use, not a root hub
 * Context: must be able to sleep; device not locked; pm locks held
 *
 * Suspends a USB device that isn't in active use, conserving घातer.
 * Devices may wake out of a suspend, अगर anything important happens,
 * using the remote wakeup mechanism.  They may also be taken out of
 * suspend by the host, using usb_port_resume().  It's also routine
 * to disconnect devices जबतक they are suspended.
 *
 * This only affects the USB hardware क्रम a device; its पूर्णांकerfaces
 * (and, क्रम hubs, child devices) must alपढ़ोy have been suspended.
 *
 * Selective port suspend reduces घातer; most suspended devices draw
 * less than 500 uA.  It's also used in OTG, aदीर्घ with remote wakeup.
 * All devices below the suspended port are also suspended.
 *
 * Devices leave suspend state when the host wakes them up.  Some devices
 * also support "remote wakeup", where the device can activate the USB
 * tree above them to deliver data, such as a keypress or packet.  In
 * some हालs, this wakes the USB host.
 *
 * Suspending OTG devices may trigger HNP, अगर that's been enabled
 * between a pair of dual-role devices.  That will change roles, such
 * as from A-Host to A-Peripheral or from B-Host back to B-Peripheral.
 *
 * Devices on USB hub ports have only one "suspend" state, corresponding
 * to ACPI D2, "may cause the device to lose some context".
 * State transitions include:
 *
 *   - suspend, resume ... when the VBUS घातer link stays live
 *   - suspend, disconnect ... VBUS lost
 *
 * Once VBUS drop अवरोधs the circuit, the port it's using has to go through
 * normal re-क्रमागतeration procedures, starting with enabling VBUS घातer.
 * Other than re-initializing the hub (plug/unplug, except क्रम root hubs),
 * Linux (2.6) currently has NO mechanisms to initiate that:  no hub_wq
 * समयr, no SRP, no requests through sysfs.
 *
 * If Runसमय PM isn't enabled or used, non-SuperSpeed devices may not get
 * suspended until their bus goes पूर्णांकo global suspend (i.e., the root
 * hub is suspended).  Nevertheless, we change @udev->state to
 * USB_STATE_SUSPENDED as this is the device's "logical" state.  The actual
 * upstream port setting is stored in @udev->port_is_suspended.
 *
 * Returns 0 on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_port_suspend(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	काष्ठा usb_hub	*hub = usb_hub_to_काष्ठा_hub(udev->parent);
	काष्ठा usb_port *port_dev = hub->ports[udev->portnum - 1];
	पूर्णांक		port1 = udev->portnum;
	पूर्णांक		status;
	bool		really_suspend = true;

	usb_lock_port(port_dev);

	/* enable remote wakeup when appropriate; this lets the device
	 * wake up the upstream hub (including maybe the root hub).
	 *
	 * NOTE:  OTG devices may issue remote wakeup (or SRP) even when
	 * we करोn't explicitly enable it here.
	 */
	अगर (udev->करो_remote_wakeup) अणु
		status = usb_enable_remote_wakeup(udev);
		अगर (status) अणु
			dev_dbg(&udev->dev, "won't remote wakeup, status %d\n",
					status);
			/* bail अगर स्वतःsuspend is requested */
			अगर (PMSG_IS_AUTO(msg))
				जाओ err_wakeup;
		पूर्ण
	पूर्ण

	/* disable USB2 hardware LPM */
	usb_disable_usb2_hardware_lpm(udev);

	अगर (usb_disable_lपंचांग(udev)) अणु
		dev_err(&udev->dev, "Failed to disable LTM before suspend\n");
		status = -ENOMEM;
		अगर (PMSG_IS_AUTO(msg))
			जाओ err_lपंचांग;
	पूर्ण

	/* see 7.1.7.6 */
	अगर (hub_is_superspeed(hub->hdev))
		status = hub_set_port_link_state(hub, port1, USB_SS_PORT_LS_U3);

	/*
	 * For प्रणाली suspend, we करो not need to enable the suspend feature
	 * on inभागidual USB-2 ports.  The devices will स्वतःmatically go
	 * पूर्णांकo suspend a few ms after the root hub stops sending packets.
	 * The USB 2.0 spec calls this "global suspend".
	 *
	 * However, many USB hubs have a bug: They करोn't relay wakeup requests
	 * from a करोwnstream port अगर the port's suspend feature isn't on.
	 * Thereक्रमe we will turn on the suspend feature अगर udev or any of its
	 * descendants is enabled क्रम remote wakeup.
	 */
	अन्यथा अगर (PMSG_IS_AUTO(msg) || usb_wakeup_enabled_descendants(udev) > 0)
		status = set_port_feature(hub->hdev, port1,
				USB_PORT_FEAT_SUSPEND);
	अन्यथा अणु
		really_suspend = false;
		status = 0;
	पूर्ण
	अगर (status) अणु
		dev_dbg(&port_dev->dev, "can't suspend, status %d\n", status);

		/* Try to enable USB3 LTM again */
		usb_enable_lपंचांग(udev);
 err_lपंचांग:
		/* Try to enable USB2 hardware LPM again */
		usb_enable_usb2_hardware_lpm(udev);

		अगर (udev->करो_remote_wakeup)
			(व्योम) usb_disable_remote_wakeup(udev);
 err_wakeup:

		/* System sleep transitions should never fail */
		अगर (!PMSG_IS_AUTO(msg))
			status = 0;
	पूर्ण अन्यथा अणु
		dev_dbg(&udev->dev, "usb %ssuspend, wakeup %d\n",
				(PMSG_IS_AUTO(msg) ? "auto-" : ""),
				udev->करो_remote_wakeup);
		अगर (really_suspend) अणु
			udev->port_is_suspended = 1;

			/* device has up to 10 msec to fully suspend */
			msleep(10);
		पूर्ण
		usb_set_device_state(udev, USB_STATE_SUSPENDED);
	पूर्ण

	अगर (status == 0 && !udev->करो_remote_wakeup && udev->persist_enabled
			&& test_and_clear_bit(port1, hub->child_usage_bits))
		pm_runसमय_put_sync(&port_dev->dev);

	usb_mark_last_busy(hub->hdev);

	usb_unlock_port(port_dev);
	वापस status;
पूर्ण

/*
 * If the USB "suspend" state is in use (rather than "global suspend"),
 * many devices will be inभागidually taken out of suspend state using
 * special "resume" संकेतing.  This routine kicks in लघुly after
 * hardware resume संकेतing is finished, either because of selective
 * resume (by host) or remote wakeup (by device) ... now see what changed
 * in the tree that's rooted at this device.
 *
 * If @udev->reset_resume is set then the device is reset beक्रमe the
 * status check is करोne.
 */
अटल पूर्णांक finish_port_resume(काष्ठा usb_device *udev)
अणु
	पूर्णांक	status = 0;
	u16	devstatus = 0;

	/* caller owns the udev device lock */
	dev_dbg(&udev->dev, "%s\n",
		udev->reset_resume ? "finish reset-resume" : "finish resume");

	/* usb ch9 identअगरies four variants of SUSPENDED, based on what
	 * state the device resumes to.  Linux currently won't see the
	 * first two on the host side; they'd be inside hub_port_init()
	 * during many समयouts, but hub_wq can't suspend until later.
	 */
	usb_set_device_state(udev, udev->actconfig
			? USB_STATE_CONFIGURED
			: USB_STATE_ADDRESS);

	/* 10.5.4.5 says not to reset a suspended port अगर the attached
	 * device is enabled क्रम remote wakeup.  Hence the reset
	 * operation is carried out here, after the port has been
	 * resumed.
	 */
	अगर (udev->reset_resume) अणु
		/*
		 * If the device morphs or चयनes modes when it is reset,
		 * we करोn't want to perform a reset-resume.  We'll fail the
		 * resume, which will cause a logical disconnect, and then
		 * the device will be rediscovered.
		 */
 retry_reset_resume:
		अगर (udev->quirks & USB_QUIRK_RESET)
			status = -ENODEV;
		अन्यथा
			status = usb_reset_and_verअगरy_device(udev);
	पूर्ण

	/* 10.5.4.5 says be sure devices in the tree are still there.
	 * For now let's assume the device didn't go crazy on resume,
	 * and device drivers will know about any resume quirks.
	 */
	अगर (status == 0) अणु
		devstatus = 0;
		status = usb_get_std_status(udev, USB_RECIP_DEVICE, 0, &devstatus);

		/* If a normal resume failed, try करोing a reset-resume */
		अगर (status && !udev->reset_resume && udev->persist_enabled) अणु
			dev_dbg(&udev->dev, "retry with reset-resume\n");
			udev->reset_resume = 1;
			जाओ retry_reset_resume;
		पूर्ण
	पूर्ण

	अगर (status) अणु
		dev_dbg(&udev->dev, "gone after usb resume? status %d\n",
				status);
	/*
	 * There are a few quirky devices which violate the standard
	 * by claiming to have remote wakeup enabled after a reset,
	 * which crash अगर the feature is cleared, hence check क्रम
	 * udev->reset_resume
	 */
	पूर्ण अन्यथा अगर (udev->actconfig && !udev->reset_resume) अणु
		अगर (udev->speed < USB_SPEED_SUPER) अणु
			अगर (devstatus & (1 << USB_DEVICE_REMOTE_WAKEUP))
				status = usb_disable_remote_wakeup(udev);
		पूर्ण अन्यथा अणु
			status = usb_get_std_status(udev, USB_RECIP_INTERFACE, 0,
					&devstatus);
			अगर (!status && devstatus & (USB_INTRF_STAT_FUNC_RW_CAP
					| USB_INTRF_STAT_FUNC_RW))
				status = usb_disable_remote_wakeup(udev);
		पूर्ण

		अगर (status)
			dev_dbg(&udev->dev,
				"disable remote wakeup, status %d\n",
				status);
		status = 0;
	पूर्ण
	वापस status;
पूर्ण

/*
 * There are some SS USB devices which take दीर्घer समय क्रम link training.
 * XHCI specs 4.19.4 says that when Link training is successful, port
 * sets CCS bit to 1. So अगर SW पढ़ोs port status beक्रमe successful link
 * training, then it will not find device to be present.
 * USB Analyzer log with such buggy devices show that in some हालs
 * device चयन on the RX termination after दीर्घ delay of host enabling
 * the VBUS. In few other हालs it has been seen that device fails to
 * negotiate link training in first attempt. It has been
 * reported till now that few devices take as दीर्घ as 2000 ms to train
 * the link after host enabling its VBUS and termination. Following
 * routine implements a 2000 ms समयout क्रम link training. If in a हाल
 * link trains beक्रमe समयout, loop will निकास earlier.
 *
 * There are also some 2.0 hard drive based devices and 3.0 thumb
 * drives that, when plugged पूर्णांकo a 2.0 only port, take a दीर्घ
 * समय to set CCS after VBUS enable.
 *
 * FIXME: If a device was connected beक्रमe suspend, but was हटाओd
 * जबतक प्रणाली was asleep, then the loop in the following routine will
 * only निकास at समयout.
 *
 * This routine should only be called when persist is enabled.
 */
अटल पूर्णांक रुको_क्रम_connected(काष्ठा usb_device *udev,
		काष्ठा usb_hub *hub, पूर्णांक *port1,
		u16 *portchange, u16 *portstatus)
अणु
	पूर्णांक status = 0, delay_ms = 0;

	जबतक (delay_ms < 2000) अणु
		अगर (status || *portstatus & USB_PORT_STAT_CONNECTION)
			अवरोध;
		अगर (!port_is_घातer_on(hub, *portstatus)) अणु
			status = -ENODEV;
			अवरोध;
		पूर्ण
		msleep(20);
		delay_ms += 20;
		status = hub_port_status(hub, *port1, portstatus, portchange);
	पूर्ण
	dev_dbg(&udev->dev, "Waited %dms for CONNECT\n", delay_ms);
	वापस status;
पूर्ण

/*
 * usb_port_resume - re-activate a suspended usb device's upstream port
 * @udev: device to re-activate, not a root hub
 * Context: must be able to sleep; device not locked; pm locks held
 *
 * This will re-activate the suspended device, increasing घातer usage
 * जबतक letting drivers communicate again with its endpoपूर्णांकs.
 * USB resume explicitly guarantees that the घातer session between
 * the host and the device is the same as it was when the device
 * suspended.
 *
 * If @udev->reset_resume is set then this routine won't check that the
 * port is still enabled.  Furthermore, finish_port_resume() above will
 * reset @udev.  The end result is that a broken घातer session can be
 * recovered and @udev will appear to persist across a loss of VBUS घातer.
 *
 * For example, अगर a host controller करोesn't मुख्यtain VBUS suspend current
 * during a प्रणाली sleep or is reset when the प्रणाली wakes up, all the USB
 * घातer sessions below it will be broken.  This is especially troublesome
 * क्रम mass-storage devices containing mounted fileप्रणालीs, since the
 * device will appear to have disconnected and all the memory mappings
 * to it will be lost.  Using the USB_PERSIST facility, the device can be
 * made to appear as अगर it had not disconnected.
 *
 * This facility can be dangerous.  Although usb_reset_and_verअगरy_device() makes
 * every efक्रमt to insure that the same device is present after the
 * reset as beक्रमe, it cannot provide a 100% guarantee.  Furthermore it's
 * quite possible क्रम a device to reमुख्य unaltered but its media to be
 * changed.  If the user replaces a flash memory card जबतक the प्रणाली is
 * asleep, he will have only himself to blame when the fileप्रणाली on the
 * new card is corrupted and the प्रणाली crashes.
 *
 * Returns 0 on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_port_resume(काष्ठा usb_device *udev, pm_message_t msg)
अणु
	काष्ठा usb_hub	*hub = usb_hub_to_काष्ठा_hub(udev->parent);
	काष्ठा usb_port *port_dev = hub->ports[udev->portnum  - 1];
	पूर्णांक		port1 = udev->portnum;
	पूर्णांक		status;
	u16		portchange, portstatus;

	अगर (!test_and_set_bit(port1, hub->child_usage_bits)) अणु
		status = pm_runसमय_resume_and_get(&port_dev->dev);
		अगर (status < 0) अणु
			dev_dbg(&udev->dev, "can't resume usb port, status %d\n",
					status);
			वापस status;
		पूर्ण
	पूर्ण

	usb_lock_port(port_dev);

	/* Skip the initial Clear-Suspend step क्रम a remote wakeup */
	status = hub_port_status(hub, port1, &portstatus, &portchange);
	अगर (status == 0 && !port_is_suspended(hub, portstatus)) अणु
		अगर (portchange & USB_PORT_STAT_C_SUSPEND)
			pm_wakeup_event(&udev->dev, 0);
		जाओ SuspendCleared;
	पूर्ण

	/* see 7.1.7.7; affects घातer usage, but not budgeting */
	अगर (hub_is_superspeed(hub->hdev))
		status = hub_set_port_link_state(hub, port1, USB_SS_PORT_LS_U0);
	अन्यथा
		status = usb_clear_port_feature(hub->hdev,
				port1, USB_PORT_FEAT_SUSPEND);
	अगर (status) अणु
		dev_dbg(&port_dev->dev, "can't resume, status %d\n", status);
	पूर्ण अन्यथा अणु
		/* drive resume क्रम USB_RESUME_TIMEOUT msec */
		dev_dbg(&udev->dev, "usb %sresume\n",
				(PMSG_IS_AUTO(msg) ? "auto-" : ""));
		msleep(USB_RESUME_TIMEOUT);

		/* Virtual root hubs can trigger on GET_PORT_STATUS to
		 * stop resume संकेतing.  Then finish the resume
		 * sequence.
		 */
		status = hub_port_status(hub, port1, &portstatus, &portchange);
	पूर्ण

 SuspendCleared:
	अगर (status == 0) अणु
		udev->port_is_suspended = 0;
		अगर (hub_is_superspeed(hub->hdev)) अणु
			अगर (portchange & USB_PORT_STAT_C_LINK_STATE)
				usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_PORT_LINK_STATE);
		पूर्ण अन्यथा अणु
			अगर (portchange & USB_PORT_STAT_C_SUSPEND)
				usb_clear_port_feature(hub->hdev, port1,
						USB_PORT_FEAT_C_SUSPEND);
		पूर्ण

		/* TRSMRCY = 10 msec */
		msleep(10);
	पूर्ण

	अगर (udev->persist_enabled)
		status = रुको_क्रम_connected(udev, hub, &port1, &portchange,
				&portstatus);

	status = check_port_resume_type(udev,
			hub, port1, status, portchange, portstatus);
	अगर (status == 0)
		status = finish_port_resume(udev);
	अगर (status < 0) अणु
		dev_dbg(&udev->dev, "can't resume, status %d\n", status);
		hub_port_logical_disconnect(hub, port1);
	पूर्ण अन्यथा  अणु
		/* Try to enable USB2 hardware LPM */
		usb_enable_usb2_hardware_lpm(udev);

		/* Try to enable USB3 LTM */
		usb_enable_lपंचांग(udev);
	पूर्ण

	usb_unlock_port(port_dev);

	वापस status;
पूर्ण

पूर्णांक usb_remote_wakeup(काष्ठा usb_device *udev)
अणु
	पूर्णांक	status = 0;

	usb_lock_device(udev);
	अगर (udev->state == USB_STATE_SUSPENDED) अणु
		dev_dbg(&udev->dev, "usb %sresume\n", "wakeup-");
		status = usb_स्वतःresume_device(udev);
		अगर (status == 0) अणु
			/* Let the drivers करो their thing, then... */
			usb_स्वतःsuspend_device(udev);
		पूर्ण
	पूर्ण
	usb_unlock_device(udev);
	वापस status;
पूर्ण

/* Returns 1 अगर there was a remote wakeup and a connect status change. */
अटल पूर्णांक hub_handle_remote_wakeup(काष्ठा usb_hub *hub, अचिन्हित पूर्णांक port,
		u16 portstatus, u16 portchange)
		__must_hold(&port_dev->status_lock)
अणु
	काष्ठा usb_port *port_dev = hub->ports[port - 1];
	काष्ठा usb_device *hdev;
	काष्ठा usb_device *udev;
	पूर्णांक connect_change = 0;
	u16 link_state;
	पूर्णांक ret;

	hdev = hub->hdev;
	udev = port_dev->child;
	अगर (!hub_is_superspeed(hdev)) अणु
		अगर (!(portchange & USB_PORT_STAT_C_SUSPEND))
			वापस 0;
		usb_clear_port_feature(hdev, port, USB_PORT_FEAT_C_SUSPEND);
	पूर्ण अन्यथा अणु
		link_state = portstatus & USB_PORT_STAT_LINK_STATE;
		अगर (!udev || udev->state != USB_STATE_SUSPENDED ||
				(link_state != USB_SS_PORT_LS_U0 &&
				 link_state != USB_SS_PORT_LS_U1 &&
				 link_state != USB_SS_PORT_LS_U2))
			वापस 0;
	पूर्ण

	अगर (udev) अणु
		/* TRSMRCY = 10 msec */
		msleep(10);

		usb_unlock_port(port_dev);
		ret = usb_remote_wakeup(udev);
		usb_lock_port(port_dev);
		अगर (ret < 0)
			connect_change = 1;
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
		hub_port_disable(hub, port, 1);
	पूर्ण
	dev_dbg(&port_dev->dev, "resume, status %d\n", ret);
	वापस connect_change;
पूर्ण

अटल पूर्णांक check_ports_changed(काष्ठा usb_hub *hub)
अणु
	पूर्णांक port1;

	क्रम (port1 = 1; port1 <= hub->hdev->maxchild; ++port1) अणु
		u16 portstatus, portchange;
		पूर्णांक status;

		status = hub_port_status(hub, port1, &portstatus, &portchange);
		अगर (!status && portchange)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hub_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t msg)
अणु
	काष्ठा usb_hub		*hub = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device	*hdev = hub->hdev;
	अचिन्हित		port1;

	/*
	 * Warn अगर children aren't alपढ़ोy suspended.
	 * Also, add up the number of wakeup-enabled descendants.
	 */
	hub->wakeup_enabled_descendants = 0;
	क्रम (port1 = 1; port1 <= hdev->maxchild; port1++) अणु
		काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
		काष्ठा usb_device *udev = port_dev->child;

		अगर (udev && udev->can_submit) अणु
			dev_warn(&port_dev->dev, "device %s not suspended yet\n",
					dev_name(&udev->dev));
			अगर (PMSG_IS_AUTO(msg))
				वापस -EBUSY;
		पूर्ण
		अगर (udev)
			hub->wakeup_enabled_descendants +=
					usb_wakeup_enabled_descendants(udev);
	पूर्ण

	अगर (hdev->करो_remote_wakeup && hub->quirk_check_port_स्वतः_suspend) अणु
		/* check अगर there are changes pending on hub ports */
		अगर (check_ports_changed(hub)) अणु
			अगर (PMSG_IS_AUTO(msg))
				वापस -EBUSY;
			pm_wakeup_event(&hdev->dev, 2000);
		पूर्ण
	पूर्ण

	अगर (hub_is_superspeed(hdev) && hdev->करो_remote_wakeup) अणु
		/* Enable hub to send remote wakeup क्रम all ports. */
		क्रम (port1 = 1; port1 <= hdev->maxchild; port1++) अणु
			set_port_feature(hdev,
					 port1 |
					 USB_PORT_FEAT_REMOTE_WAKE_CONNECT |
					 USB_PORT_FEAT_REMOTE_WAKE_DISCONNECT |
					 USB_PORT_FEAT_REMOTE_WAKE_OVER_CURRENT,
					 USB_PORT_FEAT_REMOTE_WAKE_MASK);
		पूर्ण
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "%s\n", __func__);

	/* stop hub_wq and related activity */
	hub_quiesce(hub, HUB_SUSPEND);
	वापस 0;
पूर्ण

/* Report wakeup requests from the ports of a resuming root hub */
अटल व्योम report_wakeup_requests(काष्ठा usb_hub *hub)
अणु
	काष्ठा usb_device	*hdev = hub->hdev;
	काष्ठा usb_device	*udev;
	काष्ठा usb_hcd		*hcd;
	अचिन्हित दीर्घ		resuming_ports;
	पूर्णांक			i;

	अगर (hdev->parent)
		वापस;		/* Not a root hub */

	hcd = bus_to_hcd(hdev->bus);
	अगर (hcd->driver->get_resuming_ports) अणु

		/*
		 * The get_resuming_ports() method वापसs a biपंचांगap (origin 0)
		 * of ports which have started wakeup संकेतing but have not
		 * yet finished resuming.  During प्रणाली resume we will
		 * resume all the enabled ports, regardless of any wakeup
		 * संकेतs, which means the wakeup requests would be lost.
		 * To prevent this, report them to the PM core here.
		 */
		resuming_ports = hcd->driver->get_resuming_ports(hcd);
		क्रम (i = 0; i < hdev->maxchild; ++i) अणु
			अगर (test_bit(i, &resuming_ports)) अणु
				udev = hub->ports[i]->child;
				अगर (udev)
					pm_wakeup_event(&udev->dev, 0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hub_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_hub *hub = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_dbg(&पूर्णांकf->dev, "%s\n", __func__);
	hub_activate(hub, HUB_RESUME);

	/*
	 * This should be called only क्रम प्रणाली resume, not runसमय resume.
	 * We can't tell the dअगरference here, so some wakeup requests will be
	 * reported at the wrong समय or more than once.  This shouldn't
	 * matter much, so दीर्घ as they करो get reported.
	 */
	report_wakeup_requests(hub);
	वापस 0;
पूर्ण

अटल पूर्णांक hub_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_hub *hub = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_dbg(&पूर्णांकf->dev, "%s\n", __func__);
	hub_activate(hub, HUB_RESET_RESUME);
	वापस 0;
पूर्ण

/**
 * usb_root_hub_lost_घातer - called by HCD अगर the root hub lost Vbus घातer
 * @rhdev: काष्ठा usb_device क्रम the root hub
 *
 * The USB host controller driver calls this function when its root hub
 * is resumed and Vbus घातer has been पूर्णांकerrupted or the controller
 * has been reset.  The routine marks @rhdev as having lost घातer.
 * When the hub driver is resumed it will take notice and carry out
 * घातer-session recovery क्रम all the "USB-PERSIST"-enabled child devices;
 * the others will be disconnected.
 */
व्योम usb_root_hub_lost_घातer(काष्ठा usb_device *rhdev)
अणु
	dev_notice(&rhdev->dev, "root hub lost power or was reset\n");
	rhdev->reset_resume = 1;
पूर्ण
EXPORT_SYMBOL_GPL(usb_root_hub_lost_घातer);

अटल स्थिर अक्षर * स्थिर usb3_lpm_names[]  = अणु
	"U0",
	"U1",
	"U2",
	"U3",
पूर्ण;

/*
 * Send a Set SEL control transfer to the device, prior to enabling
 * device-initiated U1 or U2.  This lets the device know the निकास latencies from
 * the समय the device initiates a U1 or U2 निकास, to the समय it will receive a
 * packet from the host.
 *
 * This function will fail अगर the SEL or PEL values क्रम udev are greater than
 * the maximum allowed values क्रम the link state to be enabled.
 */
अटल पूर्णांक usb_req_set_sel(काष्ठा usb_device *udev, क्रमागत usb3_link_state state)
अणु
	काष्ठा usb_set_sel_req *sel_values;
	अचिन्हित दीर्घ दीर्घ u1_sel;
	अचिन्हित दीर्घ दीर्घ u1_pel;
	अचिन्हित दीर्घ दीर्घ u2_sel;
	अचिन्हित दीर्घ दीर्घ u2_pel;
	पूर्णांक ret;

	अगर (udev->state != USB_STATE_CONFIGURED)
		वापस 0;

	/* Convert SEL and PEL stored in ns to us */
	u1_sel = DIV_ROUND_UP(udev->u1_params.sel, 1000);
	u1_pel = DIV_ROUND_UP(udev->u1_params.pel, 1000);
	u2_sel = DIV_ROUND_UP(udev->u2_params.sel, 1000);
	u2_pel = DIV_ROUND_UP(udev->u2_params.pel, 1000);

	/*
	 * Make sure that the calculated SEL and PEL values क्रम the link
	 * state we're enabling aren't bigger than the max SEL/PEL
	 * value that will fit in the SET SEL control transfer.
	 * Otherwise the device would get an incorrect idea of the निकास
	 * latency क्रम the link state, and could start a device-initiated
	 * U1/U2 when the निकास latencies are too high.
	 */
	अगर ((state == USB3_LPM_U1 &&
				(u1_sel > USB3_LPM_MAX_U1_SEL_PEL ||
				 u1_pel > USB3_LPM_MAX_U1_SEL_PEL)) ||
			(state == USB3_LPM_U2 &&
			 (u2_sel > USB3_LPM_MAX_U2_SEL_PEL ||
			  u2_pel > USB3_LPM_MAX_U2_SEL_PEL))) अणु
		dev_dbg(&udev->dev, "Device-initiated %s disabled due to long SEL %llu us or PEL %llu us\n",
				usb3_lpm_names[state], u1_sel, u1_pel);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If we're enabling device-initiated LPM क्रम one link state,
	 * but the other link state has a too high SEL or PEL value,
	 * just set those values to the max in the Set SEL request.
	 */
	अगर (u1_sel > USB3_LPM_MAX_U1_SEL_PEL)
		u1_sel = USB3_LPM_MAX_U1_SEL_PEL;

	अगर (u1_pel > USB3_LPM_MAX_U1_SEL_PEL)
		u1_pel = USB3_LPM_MAX_U1_SEL_PEL;

	अगर (u2_sel > USB3_LPM_MAX_U2_SEL_PEL)
		u2_sel = USB3_LPM_MAX_U2_SEL_PEL;

	अगर (u2_pel > USB3_LPM_MAX_U2_SEL_PEL)
		u2_pel = USB3_LPM_MAX_U2_SEL_PEL;

	/*
	 * usb_enable_lpm() can be called as part of a failed device reset,
	 * which may be initiated by an error path of a mass storage driver.
	 * Thereक्रमe, use GFP_NOIO.
	 */
	sel_values = kदो_स्मृति(माप *(sel_values), GFP_NOIO);
	अगर (!sel_values)
		वापस -ENOMEM;

	sel_values->u1_sel = u1_sel;
	sel_values->u1_pel = u1_pel;
	sel_values->u2_sel = cpu_to_le16(u2_sel);
	sel_values->u2_pel = cpu_to_le16(u2_pel);

	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			USB_REQ_SET_SEL,
			USB_RECIP_DEVICE,
			0, 0,
			sel_values, माप *(sel_values),
			USB_CTRL_SET_TIMEOUT);
	kमुक्त(sel_values);
	वापस ret;
पूर्ण

/*
 * Enable or disable device-initiated U1 or U2 transitions.
 */
अटल पूर्णांक usb_set_device_initiated_lpm(काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state, bool enable)
अणु
	पूर्णांक ret;
	पूर्णांक feature;

	चयन (state) अणु
	हाल USB3_LPM_U1:
		feature = USB_DEVICE_U1_ENABLE;
		अवरोध;
	हाल USB3_LPM_U2:
		feature = USB_DEVICE_U2_ENABLE;
		अवरोध;
	शेष:
		dev_warn(&udev->dev, "%s: Can't %s non-U1 or U2 state.\n",
				__func__, enable ? "enable" : "disable");
		वापस -EINVAL;
	पूर्ण

	अगर (udev->state != USB_STATE_CONFIGURED) अणु
		dev_dbg(&udev->dev, "%s: Can't %s %s state "
				"for unconfigured device.\n",
				__func__, enable ? "enable" : "disable",
				usb3_lpm_names[state]);
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		/*
		 * Now send the control transfer to enable device-initiated LPM
		 * क्रम either U1 or U2.
		 */
		ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE,
				USB_RECIP_DEVICE,
				feature,
				0, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);
	पूर्ण अन्यथा अणु
		ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_CLEAR_FEATURE,
				USB_RECIP_DEVICE,
				feature,
				0, शून्य, 0,
				USB_CTRL_SET_TIMEOUT);
	पूर्ण
	अगर (ret < 0) अणु
		dev_warn(&udev->dev, "%s of device-initiated %s failed.\n",
				enable ? "Enable" : "Disable",
				usb3_lpm_names[state]);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usb_set_lpm_समयout(काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state, पूर्णांक समयout)
अणु
	पूर्णांक ret;
	पूर्णांक feature;

	चयन (state) अणु
	हाल USB3_LPM_U1:
		feature = USB_PORT_FEAT_U1_TIMEOUT;
		अवरोध;
	हाल USB3_LPM_U2:
		feature = USB_PORT_FEAT_U2_TIMEOUT;
		अवरोध;
	शेष:
		dev_warn(&udev->dev, "%s: Can't set timeout for non-U1 or U2 state.\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (state == USB3_LPM_U1 && समयout > USB3_LPM_U1_MAX_TIMEOUT &&
			समयout != USB3_LPM_DEVICE_INITIATED) अणु
		dev_warn(&udev->dev, "Failed to set %s timeout to 0x%x, "
				"which is a reserved value.\n",
				usb3_lpm_names[state], समयout);
		वापस -EINVAL;
	पूर्ण

	ret = set_port_feature(udev->parent,
			USB_PORT_LPM_TIMEOUT(समयout) | udev->portnum,
			feature);
	अगर (ret < 0) अणु
		dev_warn(&udev->dev, "Failed to set %s timeout to 0x%x,"
				"error code %i\n", usb3_lpm_names[state],
				समयout, ret);
		वापस -EBUSY;
	पूर्ण
	अगर (state == USB3_LPM_U1)
		udev->u1_params.समयout = समयout;
	अन्यथा
		udev->u2_params.समयout = समयout;
	वापस 0;
पूर्ण

/*
 * Enable the hub-initiated U1/U2 idle समयouts, and enable device-initiated
 * U1/U2 entry.
 *
 * We will attempt to enable U1 or U2, but there are no guarantees that the
 * control transfers to set the hub समयout or enable device-initiated U1/U2
 * will be successful.
 *
 * If the control transfer to enable device-initiated U1/U2 entry fails, then
 * hub-initiated U1/U2 will be disabled.
 *
 * If we cannot set the parent hub U1/U2 समयout, we attempt to let the xHCI
 * driver know about it.  If that call fails, it should be harmless, and just
 * take up more slightly more bus bandwidth क्रम unnecessary U1/U2 निकास latency.
 */
अटल व्योम usb_enable_link_state(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state)
अणु
	पूर्णांक समयout, ret;
	__u8 u1_mel = udev->bos->ss_cap->bU1devExitLat;
	__le16 u2_mel = udev->bos->ss_cap->bU2DevExitLat;

	/* If the device says it करोesn't have *any* निकास latency to come out of
	 * U1 or U2, it's probably lying.  Assume it doesn't implement that link
	 * state.
	 */
	अगर ((state == USB3_LPM_U1 && u1_mel == 0) ||
			(state == USB3_LPM_U2 && u2_mel == 0))
		वापस;

	/*
	 * First, let the device know about the निकास latencies
	 * associated with the link state we're about to enable.
	 */
	ret = usb_req_set_sel(udev, state);
	अगर (ret < 0) अणु
		dev_warn(&udev->dev, "Set SEL for device-initiated %s failed.\n",
				usb3_lpm_names[state]);
		वापस;
	पूर्ण

	/* We allow the host controller to set the U1/U2 समयout पूर्णांकernally
	 * first, so that it can change its schedule to account क्रम the
	 * additional latency to send data to a device in a lower घातer
	 * link state.
	 */
	समयout = hcd->driver->enable_usb3_lpm_समयout(hcd, udev, state);

	/* xHCI host controller करोesn't want to enable this LPM state. */
	अगर (समयout == 0)
		वापस;

	अगर (समयout < 0) अणु
		dev_warn(&udev->dev, "Could not enable %s link state, "
				"xHCI error %i.\n", usb3_lpm_names[state],
				समयout);
		वापस;
	पूर्ण

	अगर (usb_set_lpm_समयout(udev, state, समयout)) अणु
		/* If we can't set the parent hub U1/U2 समयout,
		 * device-initiated LPM won't be allowed either, so let the xHCI
		 * host know that this link state won't be enabled.
		 */
		hcd->driver->disable_usb3_lpm_समयout(hcd, udev, state);
		वापस;
	पूर्ण

	/* Only a configured device will accept the Set Feature
	 * U1/U2_ENABLE
	 */
	अगर (udev->actconfig &&
	    usb_set_device_initiated_lpm(udev, state, true) == 0) अणु
		अगर (state == USB3_LPM_U1)
			udev->usb3_lpm_u1_enabled = 1;
		अन्यथा अगर (state == USB3_LPM_U2)
			udev->usb3_lpm_u2_enabled = 1;
	पूर्ण अन्यथा अणु
		/* Don't request U1/U2 entry अगर the device
		 * cannot transition to U1/U2.
		 */
		usb_set_lpm_समयout(udev, state, 0);
		hcd->driver->disable_usb3_lpm_समयout(hcd, udev, state);
	पूर्ण
पूर्ण

/*
 * Disable the hub-initiated U1/U2 idle समयouts, and disable device-initiated
 * U1/U2 entry.
 *
 * If this function वापसs -EBUSY, the parent hub will still allow U1/U2 entry.
 * If zero is वापसed, the parent will not allow the link to go पूर्णांकo U1/U2.
 *
 * If zero is वापसed, device-initiated U1/U2 entry may still be enabled, but
 * it won't have an effect on the bus link state because the parent hub will
 * still disallow device-initiated U1/U2 entry.
 *
 * If zero is वापसed, the xHCI host controller may still think U1/U2 entry is
 * possible.  The result will be slightly more bus bandwidth will be taken up
 * (to account क्रम U1/U2 निकास latency), but it should be harmless.
 */
अटल पूर्णांक usb_disable_link_state(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state)
अणु
	चयन (state) अणु
	हाल USB3_LPM_U1:
	हाल USB3_LPM_U2:
		अवरोध;
	शेष:
		dev_warn(&udev->dev, "%s: Can't disable non-U1 or U2 state.\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (usb_set_lpm_समयout(udev, state, 0))
		वापस -EBUSY;

	usb_set_device_initiated_lpm(udev, state, false);

	अगर (hcd->driver->disable_usb3_lpm_समयout(hcd, udev, state))
		dev_warn(&udev->dev, "Could not disable xHCI %s timeout, "
				"bus schedule bandwidth may be impacted.\n",
				usb3_lpm_names[state]);

	/* As soon as usb_set_lpm_समयout(0) वापस 0, hub initiated LPM
	 * is disabled. Hub will disallows link to enter U1/U2 as well,
	 * even device is initiating LPM. Hence LPM is disabled अगर hub LPM
	 * समयout set to 0, no matter device-initiated LPM is disabled or
	 * not.
	 */
	अगर (state == USB3_LPM_U1)
		udev->usb3_lpm_u1_enabled = 0;
	अन्यथा अगर (state == USB3_LPM_U2)
		udev->usb3_lpm_u2_enabled = 0;

	वापस 0;
पूर्ण

/*
 * Disable hub-initiated and device-initiated U1 and U2 entry.
 * Caller must own the bandwidth_mutex.
 *
 * This will call usb_enable_lpm() on failure, which will decrement
 * lpm_disable_count, and will re-enable LPM अगर lpm_disable_count reaches zero.
 */
पूर्णांक usb_disable_lpm(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd;

	अगर (!udev || !udev->parent ||
			udev->speed < USB_SPEED_SUPER ||
			!udev->lpm_capable ||
			udev->state < USB_STATE_CONFIGURED)
		वापस 0;

	hcd = bus_to_hcd(udev->bus);
	अगर (!hcd || !hcd->driver->disable_usb3_lpm_समयout)
		वापस 0;

	udev->lpm_disable_count++;
	अगर ((udev->u1_params.समयout == 0 && udev->u2_params.समयout == 0))
		वापस 0;

	/* If LPM is enabled, attempt to disable it. */
	अगर (usb_disable_link_state(hcd, udev, USB3_LPM_U1))
		जाओ enable_lpm;
	अगर (usb_disable_link_state(hcd, udev, USB3_LPM_U2))
		जाओ enable_lpm;

	वापस 0;

enable_lpm:
	usb_enable_lpm(udev);
	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL_GPL(usb_disable_lpm);

/* Grab the bandwidth_mutex beक्रमe calling usb_disable_lpm() */
पूर्णांक usb_unlocked_disable_lpm(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);
	पूर्णांक ret;

	अगर (!hcd)
		वापस -EINVAL;

	mutex_lock(hcd->bandwidth_mutex);
	ret = usb_disable_lpm(udev);
	mutex_unlock(hcd->bandwidth_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_unlocked_disable_lpm);

/*
 * Attempt to enable device-initiated and hub-initiated U1 and U2 entry.  The
 * xHCI host policy may prevent U1 or U2 from being enabled.
 *
 * Other callers may have disabled link PM, so U1 and U2 entry will be disabled
 * until the lpm_disable_count drops to zero.  Caller must own the
 * bandwidth_mutex.
 */
व्योम usb_enable_lpm(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा usb_hub *hub;
	काष्ठा usb_port *port_dev;

	अगर (!udev || !udev->parent ||
			udev->speed < USB_SPEED_SUPER ||
			!udev->lpm_capable ||
			udev->state < USB_STATE_CONFIGURED)
		वापस;

	udev->lpm_disable_count--;
	hcd = bus_to_hcd(udev->bus);
	/* Double check that we can both enable and disable LPM.
	 * Device must be configured to accept set feature U1/U2 समयout.
	 */
	अगर (!hcd || !hcd->driver->enable_usb3_lpm_समयout ||
			!hcd->driver->disable_usb3_lpm_समयout)
		वापस;

	अगर (udev->lpm_disable_count > 0)
		वापस;

	hub = usb_hub_to_काष्ठा_hub(udev->parent);
	अगर (!hub)
		वापस;

	port_dev = hub->ports[udev->portnum - 1];

	अगर (port_dev->usb3_lpm_u1_permit)
		usb_enable_link_state(hcd, udev, USB3_LPM_U1);

	अगर (port_dev->usb3_lpm_u2_permit)
		usb_enable_link_state(hcd, udev, USB3_LPM_U2);
पूर्ण
EXPORT_SYMBOL_GPL(usb_enable_lpm);

/* Grab the bandwidth_mutex beक्रमe calling usb_enable_lpm() */
व्योम usb_unlocked_enable_lpm(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	अगर (!hcd)
		वापस;

	mutex_lock(hcd->bandwidth_mutex);
	usb_enable_lpm(udev);
	mutex_unlock(hcd->bandwidth_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(usb_unlocked_enable_lpm);

/* usb3 devices use U3 क्रम disabled, make sure remote wakeup is disabled */
अटल व्योम hub_usb3_port_prepare_disable(काष्ठा usb_hub *hub,
					  काष्ठा usb_port *port_dev)
अणु
	काष्ठा usb_device *udev = port_dev->child;
	पूर्णांक ret;

	अगर (udev && udev->port_is_suspended && udev->करो_remote_wakeup) अणु
		ret = hub_set_port_link_state(hub, port_dev->portnum,
					      USB_SS_PORT_LS_U0);
		अगर (!ret) अणु
			msleep(USB_RESUME_TIMEOUT);
			ret = usb_disable_remote_wakeup(udev);
		पूर्ण
		अगर (ret)
			dev_warn(&udev->dev,
				 "Port disable: can't disable remote wake\n");
		udev->करो_remote_wakeup = 0;
	पूर्ण
पूर्ण

#अन्यथा	/* CONFIG_PM */

#घोषणा hub_suspend		शून्य
#घोषणा hub_resume		शून्य
#घोषणा hub_reset_resume	शून्य

अटल अंतरभूत व्योम hub_usb3_port_prepare_disable(काष्ठा usb_hub *hub,
						 काष्ठा usb_port *port_dev) अणु पूर्ण

पूर्णांक usb_disable_lpm(काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_disable_lpm);

व्योम usb_enable_lpm(काष्ठा usb_device *udev) अणु पूर्ण
EXPORT_SYMBOL_GPL(usb_enable_lpm);

पूर्णांक usb_unlocked_disable_lpm(काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_unlocked_disable_lpm);

व्योम usb_unlocked_enable_lpm(काष्ठा usb_device *udev) अणु पूर्ण
EXPORT_SYMBOL_GPL(usb_unlocked_enable_lpm);

पूर्णांक usb_disable_lपंचांग(काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_disable_lपंचांग);

व्योम usb_enable_lपंचांग(काष्ठा usb_device *udev) अणु पूर्ण
EXPORT_SYMBOL_GPL(usb_enable_lपंचांग);

अटल पूर्णांक hub_handle_remote_wakeup(काष्ठा usb_hub *hub, अचिन्हित पूर्णांक port,
		u16 portstatus, u16 portchange)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */

/*
 * USB-3 करोes not have a similar link state as USB-2 that will aव्योम negotiating
 * a connection with a plugged-in cable but will संकेत the host when the cable
 * is unplugged. Disable remote wake and set link state to U3 क्रम USB-3 devices
 */
अटल पूर्णांक hub_port_disable(काष्ठा usb_hub *hub, पूर्णांक port1, पूर्णांक set_state)
अणु
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	काष्ठा usb_device *hdev = hub->hdev;
	पूर्णांक ret = 0;

	अगर (!hub->error) अणु
		अगर (hub_is_superspeed(hub->hdev)) अणु
			hub_usb3_port_prepare_disable(hub, port_dev);
			ret = hub_set_port_link_state(hub, port_dev->portnum,
						      USB_SS_PORT_LS_U3);
		पूर्ण अन्यथा अणु
			ret = usb_clear_port_feature(hdev, port1,
					USB_PORT_FEAT_ENABLE);
		पूर्ण
	पूर्ण
	अगर (port_dev->child && set_state)
		usb_set_device_state(port_dev->child, USB_STATE_NOTATTACHED);
	अगर (ret && ret != -ENODEV)
		dev_err(&port_dev->dev, "cannot disable (err = %d)\n", ret);
	वापस ret;
पूर्ण

/*
 * usb_port_disable - disable a usb device's upstream port
 * @udev: device to disable
 * Context: @udev locked, must be able to sleep.
 *
 * Disables a USB device that isn't in active use.
 */
पूर्णांक usb_port_disable(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(udev->parent);

	वापस hub_port_disable(hub, udev->portnum, 0);
पूर्ण

/* USB 2.0 spec, 7.1.7.3 / fig 7-29:
 *
 * Between connect detection and reset संकेतing there must be a delay
 * of 100ms at least क्रम debounce and घातer-settling.  The corresponding
 * समयr shall restart whenever the करोwnstream port detects a disconnect.
 *
 * Apparently there are some bluetooth and irda-करोngles and a number of
 * low-speed devices क्रम which this debounce period may last over a second.
 * Not covered by the spec - but easy to deal with.
 *
 * This implementation uses a 1500ms total debounce समयout; अगर the
 * connection isn't stable by then it वापसs -ETIMEDOUT.  It checks
 * every 25ms क्रम transient disconnects.  When the port status has been
 * unchanged क्रम 100ms it वापसs the port status.
 */
पूर्णांक hub_port_debounce(काष्ठा usb_hub *hub, पूर्णांक port1, bool must_be_connected)
अणु
	पूर्णांक ret;
	u16 portchange, portstatus;
	अचिन्हित connection = 0xffff;
	पूर्णांक total_समय, stable_समय = 0;
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];

	क्रम (total_समय = 0; ; total_समय += HUB_DEBOUNCE_STEP) अणु
		ret = hub_port_status(hub, port1, &portstatus, &portchange);
		अगर (ret < 0)
			वापस ret;

		अगर (!(portchange & USB_PORT_STAT_C_CONNECTION) &&
		     (portstatus & USB_PORT_STAT_CONNECTION) == connection) अणु
			अगर (!must_be_connected ||
			     (connection == USB_PORT_STAT_CONNECTION))
				stable_समय += HUB_DEBOUNCE_STEP;
			अगर (stable_समय >= HUB_DEBOUNCE_STABLE)
				अवरोध;
		पूर्ण अन्यथा अणु
			stable_समय = 0;
			connection = portstatus & USB_PORT_STAT_CONNECTION;
		पूर्ण

		अगर (portchange & USB_PORT_STAT_C_CONNECTION) अणु
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_CONNECTION);
		पूर्ण

		अगर (total_समय >= HUB_DEBOUNCE_TIMEOUT)
			अवरोध;
		msleep(HUB_DEBOUNCE_STEP);
	पूर्ण

	dev_dbg(&port_dev->dev, "debounce total %dms stable %dms status 0x%x\n",
			total_समय, stable_समय, portstatus);

	अगर (stable_समय < HUB_DEBOUNCE_STABLE)
		वापस -ETIMEDOUT;
	वापस portstatus;
पूर्ण

व्योम usb_ep0_reinit(काष्ठा usb_device *udev)
अणु
	usb_disable_endpoपूर्णांक(udev, 0 + USB_सूची_IN, true);
	usb_disable_endpoपूर्णांक(udev, 0 + USB_सूची_OUT, true);
	usb_enable_endpoपूर्णांक(udev, &udev->ep0, true);
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep0_reinit);

#घोषणा usb_sndaddr0pipe()	(PIPE_CONTROL << 30)
#घोषणा usb_rcvaddr0pipe()	((PIPE_CONTROL << 30) | USB_सूची_IN)

अटल पूर्णांक hub_set_address(काष्ठा usb_device *udev, पूर्णांक devnum)
अणु
	पूर्णांक retval;
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	/*
	 * The host controller will choose the device address,
	 * instead of the core having chosen it earlier
	 */
	अगर (!hcd->driver->address_device && devnum <= 1)
		वापस -EINVAL;
	अगर (udev->state == USB_STATE_ADDRESS)
		वापस 0;
	अगर (udev->state != USB_STATE_DEFAULT)
		वापस -EINVAL;
	अगर (hcd->driver->address_device)
		retval = hcd->driver->address_device(hcd, udev);
	अन्यथा
		retval = usb_control_msg(udev, usb_sndaddr0pipe(),
				USB_REQ_SET_ADDRESS, 0, devnum, 0,
				शून्य, 0, USB_CTRL_SET_TIMEOUT);
	अगर (retval == 0) अणु
		update_devnum(udev, devnum);
		/* Device now using proper address. */
		usb_set_device_state(udev, USB_STATE_ADDRESS);
		usb_ep0_reinit(udev);
	पूर्ण
	वापस retval;
पूर्ण

/*
 * There are reports of USB 3.0 devices that say they support USB 2.0 Link PM
 * when they're plugged into a USB 2.0 port, but they don't work when LPM is
 * enabled.
 *
 * Only enable USB 2.0 Link PM अगर the port is पूर्णांकernal (hardwired), or the
 * device says it supports the new USB 2.0 Link PM errata by setting the BESL
 * support bit in the BOS descriptor.
 */
अटल व्योम hub_set_initial_usb2_lpm_policy(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(udev->parent);
	पूर्णांक connect_type = USB_PORT_CONNECT_TYPE_UNKNOWN;

	अगर (!udev->usb2_hw_lpm_capable || !udev->bos)
		वापस;

	अगर (hub)
		connect_type = hub->ports[udev->portnum - 1]->connect_type;

	अगर ((udev->bos->ext_cap->bmAttributes & cpu_to_le32(USB_BESL_SUPPORT)) ||
			connect_type == USB_PORT_CONNECT_TYPE_HARD_WIRED) अणु
		udev->usb2_hw_lpm_allowed = 1;
		usb_enable_usb2_hardware_lpm(udev);
	पूर्ण
पूर्ण

अटल पूर्णांक hub_enable_device(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	अगर (!hcd->driver->enable_device)
		वापस 0;
	अगर (udev->state == USB_STATE_ADDRESS)
		वापस 0;
	अगर (udev->state != USB_STATE_DEFAULT)
		वापस -EINVAL;

	वापस hcd->driver->enable_device(hcd, udev);
पूर्ण

/* Reset device, (re)assign address, get device descriptor.
 * Device connection must be stable, no more debouncing needed.
 * Returns device in USB_STATE_ADDRESS, except on error.
 *
 * If this is called क्रम an alपढ़ोy-existing device (as part of
 * usb_reset_and_verअगरy_device), the caller must own the device lock and
 * the port lock.  For a newly detected device that is not accessible
 * through any global poपूर्णांकers, it's not necessary to lock the device,
 * but it is still necessary to lock the port.
 */
अटल पूर्णांक
hub_port_init(काष्ठा usb_hub *hub, काष्ठा usb_device *udev, पूर्णांक port1,
		पूर्णांक retry_counter)
अणु
	काष्ठा usb_device	*hdev = hub->hdev;
	काष्ठा usb_hcd		*hcd = bus_to_hcd(hdev->bus);
	काष्ठा usb_port		*port_dev = hub->ports[port1 - 1];
	पूर्णांक			retries, operations, retval, i;
	अचिन्हित		delay = HUB_SHORT_RESET_TIME;
	क्रमागत usb_device_speed	oldspeed = udev->speed;
	स्थिर अक्षर		*speed;
	पूर्णांक			devnum = udev->devnum;
	स्थिर अक्षर		*driver_name;
	bool			करो_new_scheme;

	/* root hub ports have a slightly दीर्घer reset period
	 * (from USB 2.0 spec, section 7.1.7.5)
	 */
	अगर (!hdev->parent) अणु
		delay = HUB_ROOT_RESET_TIME;
		अगर (port1 == hdev->bus->otg_port)
			hdev->bus->b_hnp_enable = 0;
	पूर्ण

	/* Some low speed devices have problems with the quick delay, so */
	/*  be a bit pessimistic with those devices. RHbug #23670 */
	अगर (oldspeed == USB_SPEED_LOW)
		delay = HUB_LONG_RESET_TIME;

	mutex_lock(hcd->address0_mutex);

	/* Reset the device; full speed may morph to high speed */
	/* FIXME a USB 2.0 device may morph पूर्णांकo SuperSpeed on reset. */
	retval = hub_port_reset(hub, port1, udev, delay, false);
	अगर (retval < 0)		/* error or disconnect */
		जाओ fail;
	/* success, speed is known */

	retval = -ENODEV;

	/* Don't allow speed changes at reset, except usb 3.0 to faster */
	अगर (oldspeed != USB_SPEED_UNKNOWN && oldspeed != udev->speed &&
	    !(oldspeed == USB_SPEED_SUPER && udev->speed > oldspeed)) अणु
		dev_dbg(&udev->dev, "device reset changed speed!\n");
		जाओ fail;
	पूर्ण
	oldspeed = udev->speed;

	/* USB 2.0 section 5.5.3 talks about ep0 maxpacket ...
	 * it's fixed size except क्रम full speed devices.
	 * For Wireless USB devices, ep0 max packet is always 512 (tho
	 * reported as 0xff in the device descriptor). WUSB1.0[4.8.1].
	 */
	चयन (udev->speed) अणु
	हाल USB_SPEED_SUPER_PLUS:
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_WIRELESS:	/* fixed at 512 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(512);
		अवरोध;
	हाल USB_SPEED_HIGH:		/* fixed at 64 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(64);
		अवरोध;
	हाल USB_SPEED_FULL:		/* 8, 16, 32, or 64 */
		/* to determine the ep0 maxpacket size, try to पढ़ो
		 * the device descriptor to get bMaxPacketSize0 and
		 * then correct our initial guess.
		 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(64);
		अवरोध;
	हाल USB_SPEED_LOW:		/* fixed at 8 */
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(8);
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण

	अगर (udev->speed == USB_SPEED_WIRELESS)
		speed = "variable speed Wireless";
	अन्यथा
		speed = usb_speed_string(udev->speed);

	/*
	 * The controller driver may be शून्य अगर the controller device
	 * is the middle device between platक्रमm device and roothub.
	 * This middle device may not need a device driver due to
	 * all hardware control can be at platक्रमm device driver, this
	 * platक्रमm device is usually a dual-role USB controller device.
	 */
	अगर (udev->bus->controller->driver)
		driver_name = udev->bus->controller->driver->name;
	अन्यथा
		driver_name = udev->bus->sysdev->driver->name;

	अगर (udev->speed < USB_SPEED_SUPER)
		dev_info(&udev->dev,
				"%s %s USB device number %d using %s\n",
				(udev->config) ? "reset" : "new", speed,
				devnum, driver_name);

	/* Set up TT records, अगर needed  */
	अगर (hdev->tt) अणु
		udev->tt = hdev->tt;
		udev->ttport = hdev->ttport;
	पूर्ण अन्यथा अगर (udev->speed != USB_SPEED_HIGH
			&& hdev->speed == USB_SPEED_HIGH) अणु
		अगर (!hub->tt.hub) अणु
			dev_err(&udev->dev, "parent hub has no TT\n");
			retval = -EINVAL;
			जाओ fail;
		पूर्ण
		udev->tt = &hub->tt;
		udev->ttport = port1;
	पूर्ण

	/* Why पूर्णांकerleave GET_DESCRIPTOR and SET_ADDRESS this way?
	 * Because device hardware and firmware is someबार buggy in
	 * this area, and this is how Linux has करोne it क्रम ages.
	 * Change it cautiously.
	 *
	 * NOTE:  If use_new_scheme() is true we will start by issuing
	 * a 64-byte GET_DESCRIPTOR request.  This is what Winकरोws करोes,
	 * so it may help with some non-standards-compliant devices.
	 * Otherwise we start with SET_ADDRESS and then try to पढ़ो the
	 * first 8 bytes of the device descriptor to get the ep0 maxpacket
	 * value.
	 */
	करो_new_scheme = use_new_scheme(udev, retry_counter, port_dev);

	क्रम (retries = 0; retries < GET_DESCRIPTOR_TRIES; (++retries, msleep(100))) अणु
		अगर (करो_new_scheme) अणु
			काष्ठा usb_device_descriptor *buf;
			पूर्णांक r = 0;

			retval = hub_enable_device(udev);
			अगर (retval < 0) अणु
				dev_err(&udev->dev,
					"hub failed to enable device, error %d\n",
					retval);
				जाओ fail;
			पूर्ण

#घोषणा GET_DESCRIPTOR_बफ_मानE	64
			buf = kदो_स्मृति(GET_DESCRIPTOR_बफ_मानE, GFP_NOIO);
			अगर (!buf) अणु
				retval = -ENOMEM;
				जारी;
			पूर्ण

			/* Retry on all errors; some devices are flakey.
			 * 255 is क्रम WUSB devices, we actually need to use
			 * 512 (WUSB1.0[4.8.1]).
			 */
			क्रम (operations = 0; operations < GET_MAXPACKET0_TRIES;
					++operations) अणु
				buf->bMaxPacketSize0 = 0;
				r = usb_control_msg(udev, usb_rcvaddr0pipe(),
					USB_REQ_GET_DESCRIPTOR, USB_सूची_IN,
					USB_DT_DEVICE << 8, 0,
					buf, GET_DESCRIPTOR_बफ_मानE,
					initial_descriptor_समयout);
				चयन (buf->bMaxPacketSize0) अणु
				हाल 8: हाल 16: हाल 32: हाल 64: हाल 255:
					अगर (buf->bDescriptorType ==
							USB_DT_DEVICE) अणु
						r = 0;
						अवरोध;
					पूर्ण
					fallthrough;
				शेष:
					अगर (r == 0)
						r = -EPROTO;
					अवरोध;
				पूर्ण
				/*
				 * Some devices समय out अगर they are घातered on
				 * when alपढ़ोy connected. They need a second
				 * reset. But only on the first attempt,
				 * lest we get पूर्णांकo a समय out/reset loop
				 */
				अगर (r == 0 || (r == -ETIMEDOUT &&
						retries == 0 &&
						udev->speed > USB_SPEED_FULL))
					अवरोध;
			पूर्ण
			udev->descriptor.bMaxPacketSize0 =
					buf->bMaxPacketSize0;
			kमुक्त(buf);

			retval = hub_port_reset(hub, port1, udev, delay, false);
			अगर (retval < 0)		/* error or disconnect */
				जाओ fail;
			अगर (oldspeed != udev->speed) अणु
				dev_dbg(&udev->dev,
					"device reset changed speed!\n");
				retval = -ENODEV;
				जाओ fail;
			पूर्ण
			अगर (r) अणु
				अगर (r != -ENODEV)
					dev_err(&udev->dev, "device descriptor read/64, error %d\n",
							r);
				retval = -EMSGSIZE;
				जारी;
			पूर्ण
#अघोषित GET_DESCRIPTOR_बफ_मानE
		पूर्ण

		/*
		 * If device is WUSB, we alपढ़ोy asचिन्हित an
		 * unauthorized address in the Connect Ack sequence;
		 * authorization will assign the final address.
		 */
		अगर (udev->wusb == 0) अणु
			क्रम (operations = 0; operations < SET_ADDRESS_TRIES; ++operations) अणु
				retval = hub_set_address(udev, devnum);
				अगर (retval >= 0)
					अवरोध;
				msleep(200);
			पूर्ण
			अगर (retval < 0) अणु
				अगर (retval != -ENODEV)
					dev_err(&udev->dev, "device not accepting address %d, error %d\n",
							devnum, retval);
				जाओ fail;
			पूर्ण
			अगर (udev->speed >= USB_SPEED_SUPER) अणु
				devnum = udev->devnum;
				dev_info(&udev->dev,
						"%s SuperSpeed%s%s USB device number %d using %s\n",
						(udev->config) ? "reset" : "new",
					 (udev->speed == USB_SPEED_SUPER_PLUS) ?
							" Plus" : "",
					 (udev->ssp_rate == USB_SSP_GEN_2x2) ?
							" Gen 2x2" :
					 (udev->ssp_rate == USB_SSP_GEN_2x1) ?
							" Gen 2x1" :
					 (udev->ssp_rate == USB_SSP_GEN_1x2) ?
							" Gen 1x2" : "",
					 devnum, driver_name);
			पूर्ण

			/* cope with hardware quirkiness:
			 *  - let SET_ADDRESS settle, some device hardware wants it
			 *  - पढ़ो ep0 maxpacket even क्रम high and low speed,
			 */
			msleep(10);
			अगर (करो_new_scheme)
				अवरोध;
		पूर्ण

		retval = usb_get_device_descriptor(udev, 8);
		अगर (retval < 8) अणु
			अगर (retval != -ENODEV)
				dev_err(&udev->dev,
					"device descriptor read/8, error %d\n",
					retval);
			अगर (retval >= 0)
				retval = -EMSGSIZE;
		पूर्ण अन्यथा अणु
			u32 delay;

			retval = 0;

			delay = udev->parent->hub_delay;
			udev->hub_delay = min_t(u32, delay,
						USB_TP_TRANSMISSION_DELAY_MAX);
			retval = usb_set_isoch_delay(udev);
			अगर (retval) अणु
				dev_dbg(&udev->dev,
					"Failed set isoch delay, error %d\n",
					retval);
				retval = 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (retval)
		जाओ fail;

	/*
	 * Some superspeed devices have finished the link training process
	 * and attached to a superspeed hub port, but the device descriptor
	 * got from those devices show they aren't superspeed devices. Warm
	 * reset the port attached by the devices can fix them.
	 */
	अगर ((udev->speed >= USB_SPEED_SUPER) &&
			(le16_to_cpu(udev->descriptor.bcdUSB) < 0x0300)) अणु
		dev_err(&udev->dev, "got a wrong device descriptor, "
				"warm reset device\n");
		hub_port_reset(hub, port1, udev,
				HUB_BH_RESET_TIME, true);
		retval = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (udev->descriptor.bMaxPacketSize0 == 0xff ||
			udev->speed >= USB_SPEED_SUPER)
		i = 512;
	अन्यथा
		i = udev->descriptor.bMaxPacketSize0;
	अगर (usb_endpoपूर्णांक_maxp(&udev->ep0.desc) != i) अणु
		अगर (udev->speed == USB_SPEED_LOW ||
				!(i == 8 || i == 16 || i == 32 || i == 64)) अणु
			dev_err(&udev->dev, "Invalid ep0 maxpacket: %d\n", i);
			retval = -EMSGSIZE;
			जाओ fail;
		पूर्ण
		अगर (udev->speed == USB_SPEED_FULL)
			dev_dbg(&udev->dev, "ep0 maxpacket = %d\n", i);
		अन्यथा
			dev_warn(&udev->dev, "Using ep0 maxpacket: %d\n", i);
		udev->ep0.desc.wMaxPacketSize = cpu_to_le16(i);
		usb_ep0_reinit(udev);
	पूर्ण

	retval = usb_get_device_descriptor(udev, USB_DT_DEVICE_SIZE);
	अगर (retval < (चिन्हित)माप(udev->descriptor)) अणु
		अगर (retval != -ENODEV)
			dev_err(&udev->dev, "device descriptor read/all, error %d\n",
					retval);
		अगर (retval >= 0)
			retval = -ENOMSG;
		जाओ fail;
	पूर्ण

	usb_detect_quirks(udev);

	अगर (udev->wusb == 0 && le16_to_cpu(udev->descriptor.bcdUSB) >= 0x0201) अणु
		retval = usb_get_bos_descriptor(udev);
		अगर (!retval) अणु
			udev->lpm_capable = usb_device_supports_lpm(udev);
			usb_set_lpm_parameters(udev);
		पूर्ण
	पूर्ण

	retval = 0;
	/* notअगरy HCD that we have a device connected and addressed */
	अगर (hcd->driver->update_device)
		hcd->driver->update_device(hcd, udev);
	hub_set_initial_usb2_lpm_policy(udev);
fail:
	अगर (retval) अणु
		hub_port_disable(hub, port1, 0);
		update_devnum(udev, devnum);	/* क्रम disconnect processing */
	पूर्ण
	mutex_unlock(hcd->address0_mutex);
	वापस retval;
पूर्ण

अटल व्योम
check_highspeed(काष्ठा usb_hub *hub, काष्ठा usb_device *udev, पूर्णांक port1)
अणु
	काष्ठा usb_qualअगरier_descriptor	*qual;
	पूर्णांक				status;

	अगर (udev->quirks & USB_QUIRK_DEVICE_QUALIFIER)
		वापस;

	qual = kदो_स्मृति(माप *qual, GFP_KERNEL);
	अगर (qual == शून्य)
		वापस;

	status = usb_get_descriptor(udev, USB_DT_DEVICE_QUALIFIER, 0,
			qual, माप *qual);
	अगर (status == माप *qual) अणु
		dev_info(&udev->dev, "not running at top speed; "
			"connect to a high speed hub\n");
		/* hub LEDs are probably harder to miss than syslog */
		अगर (hub->has_indicators) अणु
			hub->indicator[port1-1] = INDICATOR_GREEN_BLINK;
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					&hub->leds, 0);
		पूर्ण
	पूर्ण
	kमुक्त(qual);
पूर्ण

अटल अचिन्हित
hub_घातer_reमुख्यing(काष्ठा usb_hub *hub)
अणु
	काष्ठा usb_device *hdev = hub->hdev;
	पूर्णांक reमुख्यing;
	पूर्णांक port1;

	अगर (!hub->limited_घातer)
		वापस 0;

	reमुख्यing = hdev->bus_mA - hub->descriptor->bHubContrCurrent;
	क्रम (port1 = 1; port1 <= hdev->maxchild; ++port1) अणु
		काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
		काष्ठा usb_device *udev = port_dev->child;
		अचिन्हित unit_load;
		पूर्णांक delta;

		अगर (!udev)
			जारी;
		अगर (hub_is_superspeed(udev))
			unit_load = 150;
		अन्यथा
			unit_load = 100;

		/*
		 * Unconfigured devices may not use more than one unit load,
		 * or 8mA क्रम OTG ports
		 */
		अगर (udev->actconfig)
			delta = usb_get_max_घातer(udev, udev->actconfig);
		अन्यथा अगर (port1 != udev->bus->otg_port || hdev->parent)
			delta = unit_load;
		अन्यथा
			delta = 8;
		अगर (delta > hub->mA_per_port)
			dev_warn(&port_dev->dev, "%dmA is over %umA budget!\n",
					delta, hub->mA_per_port);
		reमुख्यing -= delta;
	पूर्ण
	अगर (reमुख्यing < 0) अणु
		dev_warn(hub->पूर्णांकfdev, "%dmA over power budget!\n",
			-reमुख्यing);
		reमुख्यing = 0;
	पूर्ण
	वापस reमुख्यing;
पूर्ण


अटल पूर्णांक descriptors_changed(काष्ठा usb_device *udev,
		काष्ठा usb_device_descriptor *old_device_descriptor,
		काष्ठा usb_host_bos *old_bos)
अणु
	पूर्णांक		changed = 0;
	अचिन्हित	index;
	अचिन्हित	serial_len = 0;
	अचिन्हित	len;
	अचिन्हित	old_length;
	पूर्णांक		length;
	अक्षर		*buf;

	अगर (स_भेद(&udev->descriptor, old_device_descriptor,
			माप(*old_device_descriptor)) != 0)
		वापस 1;

	अगर ((old_bos && !udev->bos) || (!old_bos && udev->bos))
		वापस 1;
	अगर (udev->bos) अणु
		len = le16_to_cpu(udev->bos->desc->wTotalLength);
		अगर (len != le16_to_cpu(old_bos->desc->wTotalLength))
			वापस 1;
		अगर (स_भेद(udev->bos->desc, old_bos->desc, len))
			वापस 1;
	पूर्ण

	/* Since the idVenकरोr, idProduct, and bcdDevice values in the
	 * device descriptor haven't changed, we will assume the
	 * Manufacturer and Product strings haven't changed either.
	 * But the SerialNumber string could be dअगरferent (e.g., a
	 * dअगरferent flash card of the same bअक्रम).
	 */
	अगर (udev->serial)
		serial_len = म_माप(udev->serial) + 1;

	len = serial_len;
	क्रम (index = 0; index < udev->descriptor.bNumConfigurations; index++) अणु
		old_length = le16_to_cpu(udev->config[index].desc.wTotalLength);
		len = max(len, old_length);
	पूर्ण

	buf = kदो_स्मृति(len, GFP_NOIO);
	अगर (!buf)
		/* assume the worst */
		वापस 1;

	क्रम (index = 0; index < udev->descriptor.bNumConfigurations; index++) अणु
		old_length = le16_to_cpu(udev->config[index].desc.wTotalLength);
		length = usb_get_descriptor(udev, USB_DT_CONFIG, index, buf,
				old_length);
		अगर (length != old_length) अणु
			dev_dbg(&udev->dev, "config index %d, error %d\n",
					index, length);
			changed = 1;
			अवरोध;
		पूर्ण
		अगर (स_भेद(buf, udev->rawdescriptors[index], old_length)
				!= 0) अणु
			dev_dbg(&udev->dev, "config index %d changed (#%d)\n",
				index,
				((काष्ठा usb_config_descriptor *) buf)->
					bConfigurationValue);
			changed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!changed && serial_len) अणु
		length = usb_string(udev, udev->descriptor.iSerialNumber,
				buf, serial_len);
		अगर (length + 1 != serial_len) अणु
			dev_dbg(&udev->dev, "serial string error %d\n",
					length);
			changed = 1;
		पूर्ण अन्यथा अगर (स_भेद(buf, udev->serial, length) != 0) अणु
			dev_dbg(&udev->dev, "serial string changed\n");
			changed = 1;
		पूर्ण
	पूर्ण

	kमुक्त(buf);
	वापस changed;
पूर्ण

अटल व्योम hub_port_connect(काष्ठा usb_hub *hub, पूर्णांक port1, u16 portstatus,
		u16 portchange)
अणु
	पूर्णांक status = -ENODEV;
	पूर्णांक i;
	अचिन्हित unit_load;
	काष्ठा usb_device *hdev = hub->hdev;
	काष्ठा usb_hcd *hcd = bus_to_hcd(hdev->bus);
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	काष्ठा usb_device *udev = port_dev->child;
	अटल पूर्णांक unreliable_port = -1;

	/* Disconnect any existing devices under this port */
	अगर (udev) अणु
		अगर (hcd->usb_phy && !hdev->parent)
			usb_phy_notअगरy_disconnect(hcd->usb_phy, udev->speed);
		usb_disconnect(&port_dev->child);
	पूर्ण

	/* We can क्रमget about a "removed" device when there's a physical
	 * disconnect or the connect status changes.
	 */
	अगर (!(portstatus & USB_PORT_STAT_CONNECTION) ||
			(portchange & USB_PORT_STAT_C_CONNECTION))
		clear_bit(port1, hub->हटाओd_bits);

	अगर (portchange & (USB_PORT_STAT_C_CONNECTION |
				USB_PORT_STAT_C_ENABLE)) अणु
		status = hub_port_debounce_be_stable(hub, port1);
		अगर (status < 0) अणु
			अगर (status != -ENODEV &&
				port1 != unreliable_port &&
				prपूर्णांकk_ratelimit())
				dev_err(&port_dev->dev, "connect-debounce failed\n");
			portstatus &= ~USB_PORT_STAT_CONNECTION;
			unreliable_port = port1;
		पूर्ण अन्यथा अणु
			portstatus = status;
		पूर्ण
	पूर्ण

	/* Return now अगर debouncing failed or nothing is connected or
	 * the device was "removed".
	 */
	अगर (!(portstatus & USB_PORT_STAT_CONNECTION) ||
			test_bit(port1, hub->हटाओd_bits)) अणु

		/*
		 * maybe चयन घातer back on (e.g. root hub was reset)
		 * but only अगर the port isn't owned by someone अन्यथा.
		 */
		अगर (hub_is_port_घातer_चयनable(hub)
				&& !port_is_घातer_on(hub, portstatus)
				&& !port_dev->port_owner)
			set_port_feature(hdev, port1, USB_PORT_FEAT_POWER);

		अगर (portstatus & USB_PORT_STAT_ENABLE)
			जाओ करोne;
		वापस;
	पूर्ण
	अगर (hub_is_superspeed(hub->hdev))
		unit_load = 150;
	अन्यथा
		unit_load = 100;

	status = 0;
	क्रम (i = 0; i < PORT_INIT_TRIES; i++) अणु

		/* पुनः_स्मृतिate क्रम each attempt, since references
		 * to the previous one can escape in various ways
		 */
		udev = usb_alloc_dev(hdev, hdev->bus, port1);
		अगर (!udev) अणु
			dev_err(&port_dev->dev,
					"couldn't allocate usb_device\n");
			जाओ करोne;
		पूर्ण

		usb_set_device_state(udev, USB_STATE_POWERED);
		udev->bus_mA = hub->mA_per_port;
		udev->level = hdev->level + 1;
		udev->wusb = hub_is_wusb(hub);

		/* Devices connected to SuperSpeed hubs are USB 3.0 or later */
		अगर (hub_is_superspeed(hub->hdev))
			udev->speed = USB_SPEED_SUPER;
		अन्यथा
			udev->speed = USB_SPEED_UNKNOWN;

		choose_devnum(udev);
		अगर (udev->devnum <= 0) अणु
			status = -ENOTCONN;	/* Don't retry */
			जाओ loop;
		पूर्ण

		/* reset (non-USB 3.0 devices) and get descriptor */
		usb_lock_port(port_dev);
		status = hub_port_init(hub, udev, port1, i);
		usb_unlock_port(port_dev);
		अगर (status < 0)
			जाओ loop;

		अगर (udev->quirks & USB_QUIRK_DELAY_INIT)
			msleep(2000);

		/* consecutive bus-घातered hubs aren't reliable; they can
		 * violate the voltage drop budget.  अगर the new child has
		 * a "powered" LED, users should notice we didn't enable it
		 * (without पढ़ोing syslog), even without per-port LEDs
		 * on the parent.
		 */
		अगर (udev->descriptor.bDeviceClass == USB_CLASS_HUB
				&& udev->bus_mA <= unit_load) अणु
			u16	devstat;

			status = usb_get_std_status(udev, USB_RECIP_DEVICE, 0,
					&devstat);
			अगर (status) अणु
				dev_dbg(&udev->dev, "get status %d ?\n", status);
				जाओ loop_disable;
			पूर्ण
			अगर ((devstat & (1 << USB_DEVICE_SELF_POWERED)) == 0) अणु
				dev_err(&udev->dev,
					"can't connect bus-powered hub "
					"to this port\n");
				अगर (hub->has_indicators) अणु
					hub->indicator[port1-1] =
						INDICATOR_AMBER_BLINK;
					queue_delayed_work(
						प्रणाली_घातer_efficient_wq,
						&hub->leds, 0);
				पूर्ण
				status = -ENOTCONN;	/* Don't retry */
				जाओ loop_disable;
			पूर्ण
		पूर्ण

		/* check क्रम devices running slower than they could */
		अगर (le16_to_cpu(udev->descriptor.bcdUSB) >= 0x0200
				&& udev->speed == USB_SPEED_FULL
				&& highspeed_hubs != 0)
			check_highspeed(hub, udev, port1);

		/* Store the parent's children[] poपूर्णांकer.  At this poपूर्णांक
		 * udev becomes globally accessible, although presumably
		 * no one will look at it until hdev is unlocked.
		 */
		status = 0;

		mutex_lock(&usb_port_peer_mutex);

		/* We mustn't add new devices अगर the parent hub has
		 * been disconnected; we would race with the
		 * recursively_mark_NOTATTACHED() routine.
		 */
		spin_lock_irq(&device_state_lock);
		अगर (hdev->state == USB_STATE_NOTATTACHED)
			status = -ENOTCONN;
		अन्यथा
			port_dev->child = udev;
		spin_unlock_irq(&device_state_lock);
		mutex_unlock(&usb_port_peer_mutex);

		/* Run it through the hoops (find a driver, etc) */
		अगर (!status) अणु
			status = usb_new_device(udev);
			अगर (status) अणु
				mutex_lock(&usb_port_peer_mutex);
				spin_lock_irq(&device_state_lock);
				port_dev->child = शून्य;
				spin_unlock_irq(&device_state_lock);
				mutex_unlock(&usb_port_peer_mutex);
			पूर्ण अन्यथा अणु
				अगर (hcd->usb_phy && !hdev->parent)
					usb_phy_notअगरy_connect(hcd->usb_phy,
							udev->speed);
			पूर्ण
		पूर्ण

		अगर (status)
			जाओ loop_disable;

		status = hub_घातer_reमुख्यing(hub);
		अगर (status)
			dev_dbg(hub->पूर्णांकfdev, "%dmA power budget left\n", status);

		वापस;

loop_disable:
		hub_port_disable(hub, port1, 1);
loop:
		usb_ep0_reinit(udev);
		release_devnum(udev);
		hub_मुक्त_dev(udev);
		usb_put_dev(udev);
		अगर ((status == -ENOTCONN) || (status == -ENOTSUPP))
			अवरोध;

		/* When halfway through our retry count, घातer-cycle the port */
		अगर (i == (PORT_INIT_TRIES - 1) / 2) अणु
			dev_info(&port_dev->dev, "attempt power cycle\n");
			usb_hub_set_port_घातer(hdev, hub, port1, false);
			msleep(2 * hub_घातer_on_good_delay(hub));
			usb_hub_set_port_घातer(hdev, hub, port1, true);
			msleep(hub_घातer_on_good_delay(hub));
		पूर्ण
	पूर्ण
	अगर (hub->hdev->parent ||
			!hcd->driver->port_handed_over ||
			!(hcd->driver->port_handed_over)(hcd, port1)) अणु
		अगर (status != -ENOTCONN && status != -ENODEV)
			dev_err(&port_dev->dev,
					"unable to enumerate USB device\n");
	पूर्ण

करोne:
	hub_port_disable(hub, port1, 1);
	अगर (hcd->driver->relinquish_port && !hub->hdev->parent) अणु
		अगर (status != -ENOTCONN && status != -ENODEV)
			hcd->driver->relinquish_port(hcd, port1);
	पूर्ण
पूर्ण

/* Handle physical or logical connection change events.
 * This routine is called when:
 *	a port connection-change occurs;
 *	a port enable-change occurs (often caused by EMI);
 *	usb_reset_and_verअगरy_device() encounters changed descriptors (as from
 *		a firmware करोwnload)
 * caller alपढ़ोy locked the hub
 */
अटल व्योम hub_port_connect_change(काष्ठा usb_hub *hub, पूर्णांक port1,
					u16 portstatus, u16 portchange)
		__must_hold(&port_dev->status_lock)
अणु
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	काष्ठा usb_device *udev = port_dev->child;
	काष्ठा usb_device_descriptor descriptor;
	पूर्णांक status = -ENODEV;
	पूर्णांक retval;

	dev_dbg(&port_dev->dev, "status %04x, change %04x, %s\n", portstatus,
			portchange, portspeed(hub, portstatus));

	अगर (hub->has_indicators) अणु
		set_port_led(hub, port1, HUB_LED_AUTO);
		hub->indicator[port1-1] = INDICATOR_AUTO;
	पूर्ण

#अगर_घोषित	CONFIG_USB_OTG
	/* during HNP, करोn't repeat the debounce */
	अगर (hub->hdev->bus->is_b_host)
		portchange &= ~(USB_PORT_STAT_C_CONNECTION |
				USB_PORT_STAT_C_ENABLE);
#पूर्ण_अगर

	/* Try to resuscitate an existing device */
	अगर ((portstatus & USB_PORT_STAT_CONNECTION) && udev &&
			udev->state != USB_STATE_NOTATTACHED) अणु
		अगर (portstatus & USB_PORT_STAT_ENABLE) अणु
			/*
			 * USB-3 connections are initialized स्वतःmatically by
			 * the hostcontroller hardware. Thereक्रमe check क्रम
			 * changed device descriptors beक्रमe resuscitating the
			 * device.
			 */
			descriptor = udev->descriptor;
			retval = usb_get_device_descriptor(udev,
					माप(udev->descriptor));
			अगर (retval < 0) अणु
				dev_dbg(&udev->dev,
						"can't read device descriptor %d\n",
						retval);
			पूर्ण अन्यथा अणु
				अगर (descriptors_changed(udev, &descriptor,
						udev->bos)) अणु
					dev_dbg(&udev->dev,
							"device descriptor has changed\n");
					/* क्रम disconnect() calls */
					udev->descriptor = descriptor;
				पूर्ण अन्यथा अणु
					status = 0; /* Nothing to करो */
				पूर्ण
			पूर्ण
#अगर_घोषित CONFIG_PM
		पूर्ण अन्यथा अगर (udev->state == USB_STATE_SUSPENDED &&
				udev->persist_enabled) अणु
			/* For a suspended device, treat this as a
			 * remote wakeup event.
			 */
			usb_unlock_port(port_dev);
			status = usb_remote_wakeup(udev);
			usb_lock_port(port_dev);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			/* Don't resuscitate */;
		पूर्ण
	पूर्ण
	clear_bit(port1, hub->change_bits);

	/* successfully revalidated the connection */
	अगर (status == 0)
		वापस;

	usb_unlock_port(port_dev);
	hub_port_connect(hub, port1, portstatus, portchange);
	usb_lock_port(port_dev);
पूर्ण

/* Handle notअगरying userspace about hub over-current events */
अटल व्योम port_over_current_notअगरy(काष्ठा usb_port *port_dev)
अणु
	अक्षर *envp[3];
	काष्ठा device *hub_dev;
	अक्षर *port_dev_path;

	sysfs_notअगरy(&port_dev->dev.kobj, शून्य, "over_current_count");

	hub_dev = port_dev->dev.parent;

	अगर (!hub_dev)
		वापस;

	port_dev_path = kobject_get_path(&port_dev->dev.kobj, GFP_KERNEL);
	अगर (!port_dev_path)
		वापस;

	envp[0] = kaप्र_लिखो(GFP_KERNEL, "OVER_CURRENT_PORT=%s", port_dev_path);
	अगर (!envp[0])
		जाओ निकास_path;

	envp[1] = kaप्र_लिखो(GFP_KERNEL, "OVER_CURRENT_COUNT=%u",
			port_dev->over_current_count);
	अगर (!envp[1])
		जाओ निकास;

	envp[2] = शून्य;
	kobject_uevent_env(&hub_dev->kobj, KOBJ_CHANGE, envp);

	kमुक्त(envp[1]);
निकास:
	kमुक्त(envp[0]);
निकास_path:
	kमुक्त(port_dev_path);
पूर्ण

अटल व्योम port_event(काष्ठा usb_hub *hub, पूर्णांक port1)
		__must_hold(&port_dev->status_lock)
अणु
	पूर्णांक connect_change;
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	काष्ठा usb_device *udev = port_dev->child;
	काष्ठा usb_device *hdev = hub->hdev;
	u16 portstatus, portchange;

	connect_change = test_bit(port1, hub->change_bits);
	clear_bit(port1, hub->event_bits);
	clear_bit(port1, hub->wakeup_bits);

	अगर (hub_port_status(hub, port1, &portstatus, &portchange) < 0)
		वापस;

	अगर (portchange & USB_PORT_STAT_C_CONNECTION) अणु
		usb_clear_port_feature(hdev, port1, USB_PORT_FEAT_C_CONNECTION);
		connect_change = 1;
	पूर्ण

	अगर (portchange & USB_PORT_STAT_C_ENABLE) अणु
		अगर (!connect_change)
			dev_dbg(&port_dev->dev, "enable change, status %08x\n",
					portstatus);
		usb_clear_port_feature(hdev, port1, USB_PORT_FEAT_C_ENABLE);

		/*
		 * EM पूर्णांकerference someबार causes badly shielded USB devices
		 * to be shutकरोwn by the hub, this hack enables them again.
		 * Works at least with mouse driver.
		 */
		अगर (!(portstatus & USB_PORT_STAT_ENABLE)
		    && !connect_change && udev) अणु
			dev_err(&port_dev->dev, "disabled by hub (EMI?), re-enabling...\n");
			connect_change = 1;
		पूर्ण
	पूर्ण

	अगर (portchange & USB_PORT_STAT_C_OVERCURRENT) अणु
		u16 status = 0, unused;
		port_dev->over_current_count++;
		port_over_current_notअगरy(port_dev);

		dev_dbg(&port_dev->dev, "over-current change #%u\n",
			port_dev->over_current_count);
		usb_clear_port_feature(hdev, port1,
				USB_PORT_FEAT_C_OVER_CURRENT);
		msleep(100);	/* Cool करोwn */
		hub_घातer_on(hub, true);
		hub_port_status(hub, port1, &status, &unused);
		अगर (status & USB_PORT_STAT_OVERCURRENT)
			dev_err(&port_dev->dev, "over-current condition\n");
	पूर्ण

	अगर (portchange & USB_PORT_STAT_C_RESET) अणु
		dev_dbg(&port_dev->dev, "reset change\n");
		usb_clear_port_feature(hdev, port1, USB_PORT_FEAT_C_RESET);
	पूर्ण
	अगर ((portchange & USB_PORT_STAT_C_BH_RESET)
	    && hub_is_superspeed(hdev)) अणु
		dev_dbg(&port_dev->dev, "warm reset change\n");
		usb_clear_port_feature(hdev, port1,
				USB_PORT_FEAT_C_BH_PORT_RESET);
	पूर्ण
	अगर (portchange & USB_PORT_STAT_C_LINK_STATE) अणु
		dev_dbg(&port_dev->dev, "link state change\n");
		usb_clear_port_feature(hdev, port1,
				USB_PORT_FEAT_C_PORT_LINK_STATE);
	पूर्ण
	अगर (portchange & USB_PORT_STAT_C_CONFIG_ERROR) अणु
		dev_warn(&port_dev->dev, "config error\n");
		usb_clear_port_feature(hdev, port1,
				USB_PORT_FEAT_C_PORT_CONFIG_ERROR);
	पूर्ण

	/* skip port actions that require the port to be घातered on */
	अगर (!pm_runसमय_active(&port_dev->dev))
		वापस;

	अगर (hub_handle_remote_wakeup(hub, port1, portstatus, portchange))
		connect_change = 1;

	/*
	 * Warm reset a USB3 protocol port अगर it's in
	 * SS.Inactive state.
	 */
	अगर (hub_port_warm_reset_required(hub, port1, portstatus)) अणु
		dev_dbg(&port_dev->dev, "do warm reset\n");
		अगर (!udev || !(portstatus & USB_PORT_STAT_CONNECTION)
				|| udev->state == USB_STATE_NOTATTACHED) अणु
			अगर (hub_port_reset(hub, port1, शून्य,
					HUB_BH_RESET_TIME, true) < 0)
				hub_port_disable(hub, port1, 1);
		पूर्ण अन्यथा अणु
			usb_unlock_port(port_dev);
			usb_lock_device(udev);
			usb_reset_device(udev);
			usb_unlock_device(udev);
			usb_lock_port(port_dev);
			connect_change = 0;
		पूर्ण
	पूर्ण

	अगर (connect_change)
		hub_port_connect_change(hub, port1, portstatus, portchange);
पूर्ण

अटल व्योम hub_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_device *hdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_hub *hub;
	काष्ठा device *hub_dev;
	u16 hubstatus;
	u16 hubchange;
	पूर्णांक i, ret;

	hub = container_of(work, काष्ठा usb_hub, events);
	hdev = hub->hdev;
	hub_dev = hub->पूर्णांकfdev;
	पूर्णांकf = to_usb_पूर्णांकerface(hub_dev);

	kcov_remote_start_usb((u64)hdev->bus->busnum);

	dev_dbg(hub_dev, "state %d ports %d chg %04x evt %04x\n",
			hdev->state, hdev->maxchild,
			/* NOTE: expects max 15 ports... */
			(u16) hub->change_bits[0],
			(u16) hub->event_bits[0]);

	/* Lock the device, then check to see अगर we were
	 * disconnected जबतक रुकोing क्रम the lock to succeed. */
	usb_lock_device(hdev);
	अगर (unlikely(hub->disconnected))
		जाओ out_hdev_lock;

	/* If the hub has died, clean up after it */
	अगर (hdev->state == USB_STATE_NOTATTACHED) अणु
		hub->error = -ENODEV;
		hub_quiesce(hub, HUB_DISCONNECT);
		जाओ out_hdev_lock;
	पूर्ण

	/* Autoresume */
	ret = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (ret) अणु
		dev_dbg(hub_dev, "Can't autoresume: %d\n", ret);
		जाओ out_hdev_lock;
	पूर्ण

	/* If this is an inactive hub, करो nothing */
	अगर (hub->quiescing)
		जाओ out_स्वतःpm;

	अगर (hub->error) अणु
		dev_dbg(hub_dev, "resetting for error %d\n", hub->error);

		ret = usb_reset_device(hdev);
		अगर (ret) अणु
			dev_dbg(hub_dev, "error resetting hub: %d\n", ret);
			जाओ out_स्वतःpm;
		पूर्ण

		hub->nerrors = 0;
		hub->error = 0;
	पूर्ण

	/* deal with port status changes */
	क्रम (i = 1; i <= hdev->maxchild; i++) अणु
		काष्ठा usb_port *port_dev = hub->ports[i - 1];

		अगर (test_bit(i, hub->event_bits)
				|| test_bit(i, hub->change_bits)
				|| test_bit(i, hub->wakeup_bits)) अणु
			/*
			 * The get_noresume and barrier ensure that अगर
			 * the port was in the process of resuming, we
			 * flush that work and keep the port active क्रम
			 * the duration of the port_event().  However,
			 * अगर the port is runसमय pm suspended
			 * (घातered-off), we leave it in that state, run
			 * an abbreviated port_event(), and move on.
			 */
			pm_runसमय_get_noresume(&port_dev->dev);
			pm_runसमय_barrier(&port_dev->dev);
			usb_lock_port(port_dev);
			port_event(hub, i);
			usb_unlock_port(port_dev);
			pm_runसमय_put_sync(&port_dev->dev);
		पूर्ण
	पूर्ण

	/* deal with hub status changes */
	अगर (test_and_clear_bit(0, hub->event_bits) == 0)
		;	/* करो nothing */
	अन्यथा अगर (hub_hub_status(hub, &hubstatus, &hubchange) < 0)
		dev_err(hub_dev, "get_hub_status failed\n");
	अन्यथा अणु
		अगर (hubchange & HUB_CHANGE_LOCAL_POWER) अणु
			dev_dbg(hub_dev, "power change\n");
			clear_hub_feature(hdev, C_HUB_LOCAL_POWER);
			अगर (hubstatus & HUB_STATUS_LOCAL_POWER)
				/* FIXME: Is this always true? */
				hub->limited_घातer = 1;
			अन्यथा
				hub->limited_घातer = 0;
		पूर्ण
		अगर (hubchange & HUB_CHANGE_OVERCURRENT) अणु
			u16 status = 0;
			u16 unused;

			dev_dbg(hub_dev, "over-current change\n");
			clear_hub_feature(hdev, C_HUB_OVER_CURRENT);
			msleep(500);	/* Cool करोwn */
			hub_घातer_on(hub, true);
			hub_hub_status(hub, &status, &unused);
			अगर (status & HUB_STATUS_OVERCURRENT)
				dev_err(hub_dev, "over-current condition\n");
		पूर्ण
	पूर्ण

out_स्वतःpm:
	/* Balance the usb_स्वतःpm_get_पूर्णांकerface() above */
	usb_स्वतःpm_put_पूर्णांकerface_no_suspend(पूर्णांकf);
out_hdev_lock:
	usb_unlock_device(hdev);

	/* Balance the stuff in kick_hub_wq() and allow स्वतःsuspend */
	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
	kref_put(&hub->kref, hub_release);

	kcov_remote_stop();
पूर्ण

अटल स्थिर काष्ठा usb_device_id hub_id_table[] = अणु
    अणु .match_flags = USB_DEVICE_ID_MATCH_VENDOR
                   | USB_DEVICE_ID_MATCH_PRODUCT
                   | USB_DEVICE_ID_MATCH_INT_CLASS,
      .idVenकरोr = USB_VENDOR_SMSC,
      .idProduct = USB_PRODUCT_USB5534B,
      .bInterfaceClass = USB_CLASS_HUB,
      .driver_info = HUB_QUIRK_DISABLE_AUTOSUSPENDपूर्ण,
    अणु .match_flags = USB_DEVICE_ID_MATCH_VENDOR
                   | USB_DEVICE_ID_MATCH_PRODUCT,
      .idVenकरोr = USB_VENDOR_CYPRESS,
      .idProduct = USB_PRODUCT_CY7C65632,
      .driver_info = HUB_QUIRK_DISABLE_AUTOSUSPENDपूर्ण,
    अणु .match_flags = USB_DEVICE_ID_MATCH_VENDOR
			| USB_DEVICE_ID_MATCH_INT_CLASS,
      .idVenकरोr = USB_VENDOR_GENESYS_LOGIC,
      .bInterfaceClass = USB_CLASS_HUB,
      .driver_info = HUB_QUIRK_CHECK_PORT_AUTOSUSPENDपूर्ण,
    अणु .match_flags = USB_DEVICE_ID_MATCH_DEV_CLASS,
      .bDeviceClass = USB_CLASS_HUBपूर्ण,
    अणु .match_flags = USB_DEVICE_ID_MATCH_INT_CLASS,
      .bInterfaceClass = USB_CLASS_HUBपूर्ण,
    अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, hub_id_table);

अटल काष्ठा usb_driver hub_driver = अणु
	.name =		"hub",
	.probe =	hub_probe,
	.disconnect =	hub_disconnect,
	.suspend =	hub_suspend,
	.resume =	hub_resume,
	.reset_resume =	hub_reset_resume,
	.pre_reset =	hub_pre_reset,
	.post_reset =	hub_post_reset,
	.unlocked_ioctl = hub_ioctl,
	.id_table =	hub_id_table,
	.supports_स्वतःsuspend =	1,
पूर्ण;

पूर्णांक usb_hub_init(व्योम)
अणु
	अगर (usb_रेजिस्टर(&hub_driver) < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: can't register hub driver\n",
			usbcore_name);
		वापस -1;
	पूर्ण

	/*
	 * The workqueue needs to be मुक्तzable to aव्योम पूर्णांकerfering with
	 * USB-PERSIST port hanकरोver. Otherwise it might see that a full-speed
	 * device was gone beक्रमe the EHCI controller had handed its port
	 * over to the companion full-speed controller.
	 */
	hub_wq = alloc_workqueue("usb_hub_wq", WQ_FREEZABLE, 0);
	अगर (hub_wq)
		वापस 0;

	/* Fall through अगर kernel_thपढ़ो failed */
	usb_deरेजिस्टर(&hub_driver);
	pr_err("%s: can't allocate workqueue for usb hub\n", usbcore_name);

	वापस -1;
पूर्ण

व्योम usb_hub_cleanup(व्योम)
अणु
	destroy_workqueue(hub_wq);

	/*
	 * Hub resources are मुक्तd क्रम us by usb_deरेजिस्टर. It calls
	 * usb_driver_purge on every device which in turn calls that
	 * devices disconnect function अगर it is using this driver.
	 * The hub_disconnect function takes care of releasing the
	 * inभागidual hub resources. -greg
	 */
	usb_deरेजिस्टर(&hub_driver);
पूर्ण /* usb_hub_cleanup() */

/**
 * usb_reset_and_verअगरy_device - perक्रमm a USB port reset to reinitialize a device
 * @udev: device to reset (not in SUSPENDED or NOTATTACHED state)
 *
 * WARNING - करोn't use this routine to reset a composite device
 * (one with multiple पूर्णांकerfaces owned by separate drivers)!
 * Use usb_reset_device() instead.
 *
 * Do a port reset, reassign the device's address, and establish its
 * क्रमmer operating configuration.  If the reset fails, or the device's
 * descriptors change from their values beक्रमe the reset, or the original
 * configuration and altsettings cannot be restored, a flag will be set
 * telling hub_wq to pretend the device has been disconnected and then
 * re-connected.  All drivers will be unbound, and the device will be
 * re-क्रमागतerated and probed all over again.
 *
 * Return: 0 अगर the reset succeeded, -ENODEV अगर the device has been
 * flagged क्रम logical disconnection, or some other negative error code
 * अगर the reset wasn't even attempted.
 *
 * Note:
 * The caller must own the device lock and the port lock, the latter is
 * taken by usb_reset_device().  For example, it's safe to use
 * usb_reset_device() from a driver probe() routine after करोwnloading
 * new firmware.  For calls that might not occur during probe(), drivers
 * should lock the device using usb_lock_device_क्रम_reset().
 *
 * Locking exception: This routine may also be called from within an
 * स्वतःresume handler.  Such usage won't conflict with other tasks
 * holding the device lock because these tasks should always call
 * usb_स्वतःpm_resume_device(), thereby preventing any unwanted
 * स्वतःresume.  The स्वतःresume handler is expected to have alपढ़ोy
 * acquired the port lock beक्रमe calling this routine.
 */
अटल पूर्णांक usb_reset_and_verअगरy_device(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_device		*parent_hdev = udev->parent;
	काष्ठा usb_hub			*parent_hub;
	काष्ठा usb_hcd			*hcd = bus_to_hcd(udev->bus);
	काष्ठा usb_device_descriptor	descriptor = udev->descriptor;
	काष्ठा usb_host_bos		*bos;
	पूर्णांक				i, j, ret = 0;
	पूर्णांक				port1 = udev->portnum;

	अगर (udev->state == USB_STATE_NOTATTACHED ||
			udev->state == USB_STATE_SUSPENDED) अणु
		dev_dbg(&udev->dev, "device reset not allowed in state %d\n",
				udev->state);
		वापस -EINVAL;
	पूर्ण

	अगर (!parent_hdev)
		वापस -EISसूची;

	parent_hub = usb_hub_to_काष्ठा_hub(parent_hdev);

	/* Disable USB2 hardware LPM.
	 * It will be re-enabled by the क्रमागतeration process.
	 */
	usb_disable_usb2_hardware_lpm(udev);

	/* Disable LPM जबतक we reset the device and reinstall the alt settings.
	 * Device-initiated LPM, and प्रणाली निकास latency settings are cleared
	 * when the device is reset, so we have to set them up again.
	 */
	ret = usb_unlocked_disable_lpm(udev);
	अगर (ret) अणु
		dev_err(&udev->dev, "%s Failed to disable LPM\n", __func__);
		जाओ re_क्रमागतerate_no_bos;
	पूर्ण

	bos = udev->bos;
	udev->bos = शून्य;

	क्रम (i = 0; i < PORT_INIT_TRIES; ++i) अणु

		/* ep0 maxpacket size may change; let the HCD know about it.
		 * Other endpoपूर्णांकs will be handled by re-क्रमागतeration. */
		usb_ep0_reinit(udev);
		ret = hub_port_init(parent_hub, udev, port1, i);
		अगर (ret >= 0 || ret == -ENOTCONN || ret == -ENODEV)
			अवरोध;
	पूर्ण

	अगर (ret < 0)
		जाओ re_क्रमागतerate;

	/* Device might have changed firmware (DFU or similar) */
	अगर (descriptors_changed(udev, &descriptor, bos)) अणु
		dev_info(&udev->dev, "device firmware changed\n");
		udev->descriptor = descriptor;	/* क्रम disconnect() calls */
		जाओ re_क्रमागतerate;
	पूर्ण

	/* Restore the device's previous configuration */
	अगर (!udev->actconfig)
		जाओ करोne;

	mutex_lock(hcd->bandwidth_mutex);
	ret = usb_hcd_alloc_bandwidth(udev, udev->actconfig, शून्य, शून्य);
	अगर (ret < 0) अणु
		dev_warn(&udev->dev,
				"Busted HC?  Not enough HCD resources for "
				"old configuration.\n");
		mutex_unlock(hcd->bandwidth_mutex);
		जाओ re_क्रमागतerate;
	पूर्ण
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			USB_REQ_SET_CONFIGURATION, 0,
			udev->actconfig->desc.bConfigurationValue, 0,
			शून्य, 0, USB_CTRL_SET_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(&udev->dev,
			"can't restore configuration #%d (error=%d)\n",
			udev->actconfig->desc.bConfigurationValue, ret);
		mutex_unlock(hcd->bandwidth_mutex);
		जाओ re_क्रमागतerate;
	पूर्ण
	mutex_unlock(hcd->bandwidth_mutex);
	usb_set_device_state(udev, USB_STATE_CONFIGURED);

	/* Put पूर्णांकerfaces back पूर्णांकo the same altsettings as beक्रमe.
	 * Don't bother to send the Set-Interface request क्रम पूर्णांकerfaces
	 * that were alपढ़ोy in altsetting 0; besides being unnecessary,
	 * many devices can't handle it.  Instead just reset the host-side
	 * endpoपूर्णांक state.
	 */
	क्रम (i = 0; i < udev->actconfig->desc.bNumInterfaces; i++) अणु
		काष्ठा usb_host_config *config = udev->actconfig;
		काष्ठा usb_पूर्णांकerface *पूर्णांकf = config->पूर्णांकerface[i];
		काष्ठा usb_पूर्णांकerface_descriptor *desc;

		desc = &पूर्णांकf->cur_altsetting->desc;
		अगर (desc->bAlternateSetting == 0) अणु
			usb_disable_पूर्णांकerface(udev, पूर्णांकf, true);
			usb_enable_पूर्णांकerface(udev, पूर्णांकf, true);
			ret = 0;
		पूर्ण अन्यथा अणु
			/* Let the bandwidth allocation function know that this
			 * device has been reset, and it will have to use
			 * alternate setting 0 as the current alternate setting.
			 */
			पूर्णांकf->resetting_device = 1;
			ret = usb_set_पूर्णांकerface(udev, desc->bInterfaceNumber,
					desc->bAlternateSetting);
			पूर्णांकf->resetting_device = 0;
		पूर्ण
		अगर (ret < 0) अणु
			dev_err(&udev->dev, "failed to restore interface %d "
				"altsetting %d (error=%d)\n",
				desc->bInterfaceNumber,
				desc->bAlternateSetting,
				ret);
			जाओ re_क्रमागतerate;
		पूर्ण
		/* Resetting also मुक्तs any allocated streams */
		क्रम (j = 0; j < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; j++)
			पूर्णांकf->cur_altsetting->endpoपूर्णांक[j].streams = 0;
	पूर्ण

करोne:
	/* Now that the alt settings are re-installed, enable LTM and LPM. */
	usb_enable_usb2_hardware_lpm(udev);
	usb_unlocked_enable_lpm(udev);
	usb_enable_lपंचांग(udev);
	usb_release_bos_descriptor(udev);
	udev->bos = bos;
	वापस 0;

re_क्रमागतerate:
	usb_release_bos_descriptor(udev);
	udev->bos = bos;
re_क्रमागतerate_no_bos:
	/* LPM state करोesn't matter when we're about to destroy the device. */
	hub_port_logical_disconnect(parent_hub, port1);
	वापस -ENODEV;
पूर्ण

/**
 * usb_reset_device - warn पूर्णांकerface drivers and perक्रमm a USB port reset
 * @udev: device to reset (not in NOTATTACHED state)
 *
 * Warns all drivers bound to रेजिस्टरed पूर्णांकerfaces (using their pre_reset
 * method), perक्रमms the port reset, and then lets the drivers know that
 * the reset is over (using their post_reset method).
 *
 * Return: The same as क्रम usb_reset_and_verअगरy_device().
 *
 * Note:
 * The caller must own the device lock.  For example, it's safe to use
 * this from a driver probe() routine after करोwnloading new firmware.
 * For calls that might not occur during probe(), drivers should lock
 * the device using usb_lock_device_क्रम_reset().
 *
 * If an पूर्णांकerface is currently being probed or disconnected, we assume
 * its driver knows how to handle resets.  For all other पूर्णांकerfaces,
 * अगर the driver करोesn't have pre_reset and post_reset methods then
 * we attempt to unbind it and rebind afterward.
 */
पूर्णांक usb_reset_device(काष्ठा usb_device *udev)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित पूर्णांक noio_flag;
	काष्ठा usb_port *port_dev;
	काष्ठा usb_host_config *config = udev->actconfig;
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(udev->parent);

	अगर (udev->state == USB_STATE_NOTATTACHED) अणु
		dev_dbg(&udev->dev, "device reset not allowed in state %d\n",
				udev->state);
		वापस -EINVAL;
	पूर्ण

	अगर (!udev->parent) अणु
		/* this requires hcd-specअगरic logic; see ohci_restart() */
		dev_dbg(&udev->dev, "%s for root hub!\n", __func__);
		वापस -EISसूची;
	पूर्ण

	port_dev = hub->ports[udev->portnum - 1];

	/*
	 * Don't allocate memory with GFP_KERNEL in current
	 * context to aव्योम possible deadlock अगर usb mass
	 * storage पूर्णांकerface or usbnet पूर्णांकerface(iSCSI हाल)
	 * is included in current configuration. The easist
	 * approach is to करो it क्रम every device reset,
	 * because the device 'memalloc_noio' flag may have
	 * not been set beक्रमe reseting the usb device.
	 */
	noio_flag = meदो_स्मृति_noio_save();

	/* Prevent स्वतःsuspend during the reset */
	usb_स्वतःresume_device(udev);

	अगर (config) अणु
		क्रम (i = 0; i < config->desc.bNumInterfaces; ++i) अणु
			काष्ठा usb_पूर्णांकerface *cपूर्णांकf = config->पूर्णांकerface[i];
			काष्ठा usb_driver *drv;
			पूर्णांक unbind = 0;

			अगर (cपूर्णांकf->dev.driver) अणु
				drv = to_usb_driver(cपूर्णांकf->dev.driver);
				अगर (drv->pre_reset && drv->post_reset)
					unbind = (drv->pre_reset)(cपूर्णांकf);
				अन्यथा अगर (cपूर्णांकf->condition ==
						USB_INTERFACE_BOUND)
					unbind = 1;
				अगर (unbind)
					usb_क्रमced_unbind_पूर्णांकf(cपूर्णांकf);
			पूर्ण
		पूर्ण
	पूर्ण

	usb_lock_port(port_dev);
	ret = usb_reset_and_verअगरy_device(udev);
	usb_unlock_port(port_dev);

	अगर (config) अणु
		क्रम (i = config->desc.bNumInterfaces - 1; i >= 0; --i) अणु
			काष्ठा usb_पूर्णांकerface *cपूर्णांकf = config->पूर्णांकerface[i];
			काष्ठा usb_driver *drv;
			पूर्णांक rebind = cपूर्णांकf->needs_binding;

			अगर (!rebind && cपूर्णांकf->dev.driver) अणु
				drv = to_usb_driver(cपूर्णांकf->dev.driver);
				अगर (drv->post_reset)
					rebind = (drv->post_reset)(cपूर्णांकf);
				अन्यथा अगर (cपूर्णांकf->condition ==
						USB_INTERFACE_BOUND)
					rebind = 1;
				अगर (rebind)
					cपूर्णांकf->needs_binding = 1;
			पूर्ण
		पूर्ण

		/* If the reset failed, hub_wq will unbind drivers later */
		अगर (ret == 0)
			usb_unbind_and_rebind_marked_पूर्णांकerfaces(udev);
	पूर्ण

	usb_स्वतःsuspend_device(udev);
	meदो_स्मृति_noio_restore(noio_flag);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_reset_device);


/**
 * usb_queue_reset_device - Reset a USB device from an atomic context
 * @अगरace: USB पूर्णांकerface beदीर्घing to the device to reset
 *
 * This function can be used to reset a USB device from an atomic
 * context, where usb_reset_device() won't work (as it blocks).
 *
 * Doing a reset via this method is functionally equivalent to calling
 * usb_reset_device(), except क्रम the fact that it is delayed to a
 * workqueue. This means that any drivers bound to other पूर्णांकerfaces
 * might be unbound, as well as users from usbfs in user space.
 *
 * Corner हालs:
 *
 * - Scheduling two resets at the same समय from two dअगरferent drivers
 *   attached to two dअगरferent पूर्णांकerfaces of the same device is
 *   possible; depending on how the driver attached to each पूर्णांकerface
 *   handles ->pre_reset(), the second reset might happen or not.
 *
 * - If the reset is delayed so दीर्घ that the पूर्णांकerface is unbound from
 *   its driver, the reset will be skipped.
 *
 * - This function can be called during .probe().  It can also be called
 *   during .disconnect(), but करोing so is poपूर्णांकless because the reset
 *   will not occur.  If you really want to reset the device during
 *   .disconnect(), call usb_reset_device() directly -- but watch out
 *   क्रम nested unbinding issues!
 */
व्योम usb_queue_reset_device(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	अगर (schedule_work(&अगरace->reset_ws))
		usb_get_पूर्णांकf(अगरace);
पूर्ण
EXPORT_SYMBOL_GPL(usb_queue_reset_device);

/**
 * usb_hub_find_child - Get the poपूर्णांकer of child device
 * attached to the port which is specअगरied by @port1.
 * @hdev: USB device beदीर्घing to the usb hub
 * @port1: port num to indicate which port the child device
 *	is attached to.
 *
 * USB drivers call this function to get hub's child device
 * poपूर्णांकer.
 *
 * Return: %शून्य अगर input param is invalid and
 * child's usb_device poपूर्णांकer अगर non-शून्य.
 */
काष्ठा usb_device *usb_hub_find_child(काष्ठा usb_device *hdev,
		पूर्णांक port1)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);

	अगर (port1 < 1 || port1 > hdev->maxchild)
		वापस शून्य;
	वापस hub->ports[port1 - 1]->child;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hub_find_child);

व्योम usb_hub_adjust_deviceremovable(काष्ठा usb_device *hdev,
		काष्ठा usb_hub_descriptor *desc)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);
	क्रमागत usb_port_connect_type connect_type;
	पूर्णांक i;

	अगर (!hub)
		वापस;

	अगर (!hub_is_superspeed(hdev)) अणु
		क्रम (i = 1; i <= hdev->maxchild; i++) अणु
			काष्ठा usb_port *port_dev = hub->ports[i - 1];

			connect_type = port_dev->connect_type;
			अगर (connect_type == USB_PORT_CONNECT_TYPE_HARD_WIRED) अणु
				u8 mask = 1 << (i%8);

				अगर (!(desc->u.hs.DeviceRemovable[i/8] & mask)) अणु
					dev_dbg(&port_dev->dev, "DeviceRemovable is changed to 1 according to platform information.\n");
					desc->u.hs.DeviceRemovable[i/8]	|= mask;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		u16 port_removable = le16_to_cpu(desc->u.ss.DeviceRemovable);

		क्रम (i = 1; i <= hdev->maxchild; i++) अणु
			काष्ठा usb_port *port_dev = hub->ports[i - 1];

			connect_type = port_dev->connect_type;
			अगर (connect_type == USB_PORT_CONNECT_TYPE_HARD_WIRED) अणु
				u16 mask = 1 << i;

				अगर (!(port_removable & mask)) अणु
					dev_dbg(&port_dev->dev, "DeviceRemovable is changed to 1 according to platform information.\n");
					port_removable |= mask;
				पूर्ण
			पूर्ण
		पूर्ण

		desc->u.ss.DeviceRemovable = cpu_to_le16(port_removable);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI
/**
 * usb_get_hub_port_acpi_handle - Get the usb port's acpi handle
 * @hdev: USB device beदीर्घing to the usb hub
 * @port1: port num of the port
 *
 * Return: Port's acpi handle अगर successful, %शून्य अगर params are
 * invalid.
 */
acpi_handle usb_get_hub_port_acpi_handle(काष्ठा usb_device *hdev,
	पूर्णांक port1)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);

	अगर (!hub)
		वापस शून्य;

	वापस ACPI_HANDLE(&hub->ports[port1 - 1]->dev);
पूर्ण
#पूर्ण_अगर
