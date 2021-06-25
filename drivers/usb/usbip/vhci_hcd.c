<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Nobuo Iwata
 */

#समावेश <linux/init.h>
#समावेश <linux/file.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "usbip_common.h"
#समावेश "vhci.h"

#घोषणा DRIVER_AUTHOR "Takahiro Hirofuchi"
#घोषणा DRIVER_DESC "USB/IP 'Virtual' Host Controller (VHCI) Driver"

/*
 * TODO
 *	- update root hub emulation
 *	- move the emulation code to userland ?
 *		porting to other operating प्रणालीs
 *		minimize kernel code
 *	- add suspend/resume code
 *	- clean up everything
 */

/* See usb gadget dummy hcd */

अटल पूर्णांक vhci_hub_status(काष्ठा usb_hcd *hcd, अक्षर *buff);
अटल पूर्णांक vhci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
			    u16 wIndex, अक्षर *buff, u16 wLength);
अटल पूर्णांक vhci_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
			    gfp_t mem_flags);
अटल पूर्णांक vhci_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status);
अटल पूर्णांक vhci_start(काष्ठा usb_hcd *vhci_hcd);
अटल व्योम vhci_stop(काष्ठा usb_hcd *hcd);
अटल पूर्णांक vhci_get_frame_number(काष्ठा usb_hcd *hcd);

अटल स्थिर अक्षर driver_name[] = "vhci_hcd";
अटल स्थिर अक्षर driver_desc[] = "USB/IP Virtual Host Controller";

पूर्णांक vhci_num_controllers = VHCI_NR_HCS;
काष्ठा vhci *vhcis;

अटल स्थिर अक्षर * स्थिर bit_desc[] = अणु
	"CONNECTION",		/*0*/
	"ENABLE",		/*1*/
	"SUSPEND",		/*2*/
	"OVER_CURRENT",		/*3*/
	"RESET",		/*4*/
	"L1",			/*5*/
	"R6",			/*6*/
	"R7",			/*7*/
	"POWER",		/*8*/
	"LOWSPEED",		/*9*/
	"HIGHSPEED",		/*10*/
	"PORT_TEST",		/*11*/
	"INDICATOR",		/*12*/
	"R13",			/*13*/
	"R14",			/*14*/
	"R15",			/*15*/
	"C_CONNECTION",		/*16*/
	"C_ENABLE",		/*17*/
	"C_SUSPEND",		/*18*/
	"C_OVER_CURRENT",	/*19*/
	"C_RESET",		/*20*/
	"C_L1",			/*21*/
	"R22",			/*22*/
	"R23",			/*23*/
	"R24",			/*24*/
	"R25",			/*25*/
	"R26",			/*26*/
	"R27",			/*27*/
	"R28",			/*28*/
	"R29",			/*29*/
	"R30",			/*30*/
	"R31",			/*31*/
पूर्ण;

अटल स्थिर अक्षर * स्थिर bit_desc_ss[] = अणु
	"CONNECTION",		/*0*/
	"ENABLE",		/*1*/
	"SUSPEND",		/*2*/
	"OVER_CURRENT",		/*3*/
	"RESET",		/*4*/
	"L1",			/*5*/
	"R6",			/*6*/
	"R7",			/*7*/
	"R8",			/*8*/
	"POWER",		/*9*/
	"HIGHSPEED",		/*10*/
	"PORT_TEST",		/*11*/
	"INDICATOR",		/*12*/
	"R13",			/*13*/
	"R14",			/*14*/
	"R15",			/*15*/
	"C_CONNECTION",		/*16*/
	"C_ENABLE",		/*17*/
	"C_SUSPEND",		/*18*/
	"C_OVER_CURRENT",	/*19*/
	"C_RESET",		/*20*/
	"C_BH_RESET",		/*21*/
	"C_LINK_STATE",		/*22*/
	"C_CONFIG_ERROR",	/*23*/
	"R24",			/*24*/
	"R25",			/*25*/
	"R26",			/*26*/
	"R27",			/*27*/
	"R28",			/*28*/
	"R29",			/*29*/
	"R30",			/*30*/
	"R31",			/*31*/
पूर्ण;

अटल व्योम dump_port_status_dअगरf(u32 prev_status, u32 new_status, bool usb3)
अणु
	पूर्णांक i = 0;
	u32 bit = 1;
	स्थिर अक्षर * स्थिर *desc = bit_desc;

	अगर (usb3)
		desc = bit_desc_ss;

	pr_debug("status prev -> new: %08x -> %08x\n", prev_status, new_status);
	जबतक (bit) अणु
		u32 prev = prev_status & bit;
		u32 new = new_status & bit;
		अक्षर change;

		अगर (!prev && new)
			change = '+';
		अन्यथा अगर (prev && !new)
			change = '-';
		अन्यथा
			change = ' ';

		अगर (prev || new) अणु
			pr_debug(" %c%s\n", change, desc[i]);

			अगर (bit == 1) /* USB_PORT_STAT_CONNECTION */
				pr_debug(" %c%s\n", change, "USB_PORT_STAT_SPEED_5GBPS");
		पूर्ण
		bit <<= 1;
		i++;
	पूर्ण
	pr_debug("\n");
पूर्ण

व्योम rh_port_connect(काष्ठा vhci_device *vdev, क्रमागत usb_device_speed speed)
अणु
	काष्ठा vhci_hcd	*vhci_hcd = vdev_to_vhci_hcd(vdev);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	पूर्णांक		rhport = vdev->rhport;
	u32		status;
	अचिन्हित दीर्घ	flags;

	usbip_dbg_vhci_rh("rh_port_connect %d\n", rhport);

	spin_lock_irqsave(&vhci->lock, flags);

	status = vhci_hcd->port_status[rhport];

	status |= USB_PORT_STAT_CONNECTION | (1 << USB_PORT_FEAT_C_CONNECTION);

	चयन (speed) अणु
	हाल USB_SPEED_HIGH:
		status |= USB_PORT_STAT_HIGH_SPEED;
		अवरोध;
	हाल USB_SPEED_LOW:
		status |= USB_PORT_STAT_LOW_SPEED;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	vhci_hcd->port_status[rhport] = status;

	spin_unlock_irqrestore(&vhci->lock, flags);

	usb_hcd_poll_rh_status(vhci_hcd_to_hcd(vhci_hcd));
पूर्ण

अटल व्योम rh_port_disconnect(काष्ठा vhci_device *vdev)
अणु
	काष्ठा vhci_hcd	*vhci_hcd = vdev_to_vhci_hcd(vdev);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	पूर्णांक		rhport = vdev->rhport;
	u32		status;
	अचिन्हित दीर्घ	flags;

	usbip_dbg_vhci_rh("rh_port_disconnect %d\n", rhport);

	spin_lock_irqsave(&vhci->lock, flags);

	status = vhci_hcd->port_status[rhport];

	status &= ~USB_PORT_STAT_CONNECTION;
	status |= (1 << USB_PORT_FEAT_C_CONNECTION);

	vhci_hcd->port_status[rhport] = status;

	spin_unlock_irqrestore(&vhci->lock, flags);
	usb_hcd_poll_rh_status(vhci_hcd_to_hcd(vhci_hcd));
पूर्ण

#घोषणा PORT_C_MASK				\
	((USB_PORT_STAT_C_CONNECTION		\
	  | USB_PORT_STAT_C_ENABLE		\
	  | USB_PORT_STAT_C_SUSPEND		\
	  | USB_PORT_STAT_C_OVERCURRENT		\
	  | USB_PORT_STAT_C_RESET) << 16)

/*
 * Returns 0 अगर the status hasn't changed, or the number of bytes in buf.
 * Ports are 0-indexed from the HCD poपूर्णांक of view,
 * and 1-indexed from the USB core poपूर्णांकer of view.
 *
 * @buf: a biपंचांगap to show which port status has been changed.
 *  bit  0: reserved
 *  bit  1: the status of port 0 has been changed.
 *  bit  2: the status of port 1 has been changed.
 *  ...
 */
अटल पूर्णांक vhci_hub_status(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा vhci_hcd	*vhci_hcd = hcd_to_vhci_hcd(hcd);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	पूर्णांक		retval = DIV_ROUND_UP(VHCI_HC_PORTS + 1, 8);
	पूर्णांक		rhport;
	पूर्णांक		changed = 0;
	अचिन्हित दीर्घ	flags;

	स_रखो(buf, 0, retval);

	spin_lock_irqsave(&vhci->lock, flags);
	अगर (!HCD_HW_ACCESSIBLE(hcd)) अणु
		usbip_dbg_vhci_rh("hw accessible flag not on?\n");
		जाओ करोne;
	पूर्ण

	/* check pseuकरो status रेजिस्टर क्रम each port */
	क्रम (rhport = 0; rhport < VHCI_HC_PORTS; rhport++) अणु
		अगर ((vhci_hcd->port_status[rhport] & PORT_C_MASK)) अणु
			/* The status of a port has been changed, */
			usbip_dbg_vhci_rh("port %d status changed\n", rhport);

			buf[(rhport + 1) / 8] |= 1 << (rhport + 1) % 8;
			changed = 1;
		पूर्ण
	पूर्ण

	अगर ((hcd->state == HC_STATE_SUSPENDED) && (changed == 1))
		usb_hcd_resume_root_hub(hcd);

करोne:
	spin_unlock_irqrestore(&vhci->lock, flags);
	वापस changed ? retval : 0;
पूर्ण

/* usb 3.0 root hub device descriptor */
अटल काष्ठा अणु
	काष्ठा usb_bos_descriptor bos;
	काष्ठा usb_ss_cap_descriptor ss_cap;
पूर्ण __packed usb3_bos_desc = अणु

	.bos = अणु
		.bLength		= USB_DT_BOS_SIZE,
		.bDescriptorType	= USB_DT_BOS,
		.wTotalLength		= cpu_to_le16(माप(usb3_bos_desc)),
		.bNumDeviceCaps		= 1,
	पूर्ण,
	.ss_cap = अणु
		.bLength		= USB_DT_USB_SS_CAP_SIZE,
		.bDescriptorType	= USB_DT_DEVICE_CAPABILITY,
		.bDevCapabilityType	= USB_SS_CAP_TYPE,
		.wSpeedSupported	= cpu_to_le16(USB_5GBPS_OPERATION),
		.bFunctionalitySupport	= ilog2(USB_5GBPS_OPERATION),
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम
ss_hub_descriptor(काष्ठा usb_hub_descriptor *desc)
अणु
	स_रखो(desc, 0, माप *desc);
	desc->bDescriptorType = USB_DT_SS_HUB;
	desc->bDescLength = 12;
	desc->wHubCharacteristics = cpu_to_le16(
		HUB_CHAR_INDV_PORT_LPSM | HUB_CHAR_COMMON_OCPM);
	desc->bNbrPorts = VHCI_HC_PORTS;
	desc->u.ss.bHubHdrDecLat = 0x04; /* Worst हाल: 0.4 micro sec*/
	desc->u.ss.DeviceRemovable = 0xffff;
पूर्ण

अटल अंतरभूत व्योम hub_descriptor(काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक width;

	स_रखो(desc, 0, माप(*desc));
	desc->bDescriptorType = USB_DT_HUB;
	desc->wHubCharacteristics = cpu_to_le16(
		HUB_CHAR_INDV_PORT_LPSM | HUB_CHAR_COMMON_OCPM);

	desc->bNbrPorts = VHCI_HC_PORTS;
	BUILD_BUG_ON(VHCI_HC_PORTS > USB_MAXCHILDREN);
	width = desc->bNbrPorts / 8 + 1;
	desc->bDescLength = USB_DT_HUB_NONVAR_SIZE + 2 * width;
	स_रखो(&desc->u.hs.DeviceRemovable[0], 0, width);
	स_रखो(&desc->u.hs.DeviceRemovable[width], 0xff, width);
पूर्ण

अटल पूर्णांक vhci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
			    u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा vhci_hcd	*vhci_hcd;
	काष्ठा vhci	*vhci;
	पूर्णांक             retval = 0;
	पूर्णांक		rhport = -1;
	अचिन्हित दीर्घ	flags;
	bool invalid_rhport = false;

	u32 prev_port_status[VHCI_HC_PORTS];

	अगर (!HCD_HW_ACCESSIBLE(hcd))
		वापस -ETIMEDOUT;

	/*
	 * NOTE:
	 * wIndex (bits 0-7) shows the port number and begins from 1?
	 */
	wIndex = ((__u8)(wIndex & 0x00ff));
	usbip_dbg_vhci_rh("typeReq %x wValue %x wIndex %x\n", typeReq, wValue,
			  wIndex);

	/*
	 * wIndex can be 0 क्रम some request types (typeReq). rhport is
	 * in valid range when wIndex >= 1 and < VHCI_HC_PORTS.
	 *
	 * Reference port_status[] only with valid rhport when
	 * invalid_rhport is false.
	 */
	अगर (wIndex < 1 || wIndex > VHCI_HC_PORTS) अणु
		invalid_rhport = true;
		अगर (wIndex > VHCI_HC_PORTS)
			pr_err("invalid port number %d\n", wIndex);
	पूर्ण अन्यथा
		rhport = wIndex - 1;

	vhci_hcd = hcd_to_vhci_hcd(hcd);
	vhci = vhci_hcd->vhci;

	spin_lock_irqsave(&vhci->lock, flags);

	/* store old status and compare now and old later */
	अगर (usbip_dbg_flag_vhci_rh) अणु
		अगर (!invalid_rhport)
			स_नकल(prev_port_status, vhci_hcd->port_status,
				माप(prev_port_status));
	पूर्ण

	चयन (typeReq) अणु
	हाल ClearHubFeature:
		usbip_dbg_vhci_rh(" ClearHubFeature\n");
		अवरोध;
	हाल ClearPortFeature:
		अगर (invalid_rhport) अणु
			pr_err("invalid port number %d\n", wIndex);
			जाओ error;
		पूर्ण
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (hcd->speed == HCD_USB3) अणु
				pr_err(" ClearPortFeature: USB_PORT_FEAT_SUSPEND req not "
				       "supported for USB 3.0 roothub\n");
				जाओ error;
			पूर्ण
			usbip_dbg_vhci_rh(
				" ClearPortFeature: USB_PORT_FEAT_SUSPEND\n");
			अगर (vhci_hcd->port_status[rhport] & USB_PORT_STAT_SUSPEND) अणु
				/* 20msec संकेतing */
				vhci_hcd->resuming = 1;
				vhci_hcd->re_समयout = jअगरfies + msecs_to_jअगरfies(20);
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			usbip_dbg_vhci_rh(
				" ClearPortFeature: USB_PORT_FEAT_POWER\n");
			अगर (hcd->speed == HCD_USB3)
				vhci_hcd->port_status[rhport] &= ~USB_SS_PORT_STAT_POWER;
			अन्यथा
				vhci_hcd->port_status[rhport] &= ~USB_PORT_STAT_POWER;
			अवरोध;
		शेष:
			usbip_dbg_vhci_rh(" ClearPortFeature: default %x\n",
					  wValue);
			अगर (wValue >= 32)
				जाओ error;
			vhci_hcd->port_status[rhport] &= ~(1 << wValue);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		usbip_dbg_vhci_rh(" GetHubDescriptor\n");
		अगर (hcd->speed == HCD_USB3 &&
				(wLength < USB_DT_SS_HUB_SIZE ||
				 wValue != (USB_DT_SS_HUB << 8))) अणु
			pr_err("Wrong hub descriptor type for USB 3.0 roothub.\n");
			जाओ error;
		पूर्ण
		अगर (hcd->speed == HCD_USB3)
			ss_hub_descriptor((काष्ठा usb_hub_descriptor *) buf);
		अन्यथा
			hub_descriptor((काष्ठा usb_hub_descriptor *) buf);
		अवरोध;
	हाल DeviceRequest | USB_REQ_GET_DESCRIPTOR:
		अगर (hcd->speed != HCD_USB3)
			जाओ error;

		अगर ((wValue >> 8) != USB_DT_BOS)
			जाओ error;

		स_नकल(buf, &usb3_bos_desc, माप(usb3_bos_desc));
		retval = माप(usb3_bos_desc);
		अवरोध;
	हाल GetHubStatus:
		usbip_dbg_vhci_rh(" GetHubStatus\n");
		*(__le32 *) buf = cpu_to_le32(0);
		अवरोध;
	हाल GetPortStatus:
		usbip_dbg_vhci_rh(" GetPortStatus port %x\n", wIndex);
		अगर (invalid_rhport) अणु
			pr_err("invalid port number %d\n", wIndex);
			retval = -EPIPE;
			जाओ error;
		पूर्ण

		/* we करो not care about resume. */

		/* whoever resets or resumes must GetPortStatus to
		 * complete it!!
		 */
		अगर (vhci_hcd->resuming && समय_after(jअगरfies, vhci_hcd->re_समयout)) अणु
			vhci_hcd->port_status[rhport] |= (1 << USB_PORT_FEAT_C_SUSPEND);
			vhci_hcd->port_status[rhport] &= ~(1 << USB_PORT_FEAT_SUSPEND);
			vhci_hcd->resuming = 0;
			vhci_hcd->re_समयout = 0;
		पूर्ण

		अगर ((vhci_hcd->port_status[rhport] & (1 << USB_PORT_FEAT_RESET)) !=
		    0 && समय_after(jअगरfies, vhci_hcd->re_समयout)) अणु
			vhci_hcd->port_status[rhport] |= (1 << USB_PORT_FEAT_C_RESET);
			vhci_hcd->port_status[rhport] &= ~(1 << USB_PORT_FEAT_RESET);
			vhci_hcd->re_समयout = 0;

			अगर (vhci_hcd->vdev[rhport].ud.status ==
			    VDEV_ST_NOTASSIGNED) अणु
				usbip_dbg_vhci_rh(
					" enable rhport %d (status %u)\n",
					rhport,
					vhci_hcd->vdev[rhport].ud.status);
				vhci_hcd->port_status[rhport] |=
					USB_PORT_STAT_ENABLE;
			पूर्ण

			अगर (hcd->speed < HCD_USB3) अणु
				चयन (vhci_hcd->vdev[rhport].speed) अणु
				हाल USB_SPEED_HIGH:
					vhci_hcd->port_status[rhport] |=
					      USB_PORT_STAT_HIGH_SPEED;
					अवरोध;
				हाल USB_SPEED_LOW:
					vhci_hcd->port_status[rhport] |=
						USB_PORT_STAT_LOW_SPEED;
					अवरोध;
				शेष:
					pr_err("vhci_device speed not set\n");
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		((__le16 *) buf)[0] = cpu_to_le16(vhci_hcd->port_status[rhport]);
		((__le16 *) buf)[1] =
			cpu_to_le16(vhci_hcd->port_status[rhport] >> 16);

		usbip_dbg_vhci_rh(" GetPortStatus bye %x %x\n", ((u16 *)buf)[0],
				  ((u16 *)buf)[1]);
		अवरोध;
	हाल SetHubFeature:
		usbip_dbg_vhci_rh(" SetHubFeature\n");
		retval = -EPIPE;
		अवरोध;
	हाल SetPortFeature:
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_LINK_STATE:
			usbip_dbg_vhci_rh(
				" SetPortFeature: USB_PORT_FEAT_LINK_STATE\n");
			अगर (hcd->speed != HCD_USB3) अणु
				pr_err("USB_PORT_FEAT_LINK_STATE req not "
				       "supported for USB 2.0 roothub\n");
				जाओ error;
			पूर्ण
			/*
			 * Since this is dummy we करोn't have an actual link so
			 * there is nothing to करो क्रम the SET_LINK_STATE cmd
			 */
			अवरोध;
		हाल USB_PORT_FEAT_U1_TIMEOUT:
			usbip_dbg_vhci_rh(
				" SetPortFeature: USB_PORT_FEAT_U1_TIMEOUT\n");
			fallthrough;
		हाल USB_PORT_FEAT_U2_TIMEOUT:
			usbip_dbg_vhci_rh(
				" SetPortFeature: USB_PORT_FEAT_U2_TIMEOUT\n");
			/* TODO: add suspend/resume support! */
			अगर (hcd->speed != HCD_USB3) अणु
				pr_err("USB_PORT_FEAT_U1/2_TIMEOUT req not "
				       "supported for USB 2.0 roothub\n");
				जाओ error;
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			usbip_dbg_vhci_rh(
				" SetPortFeature: USB_PORT_FEAT_SUSPEND\n");
			/* Applicable only क्रम USB2.0 hub */
			अगर (hcd->speed == HCD_USB3) अणु
				pr_err("USB_PORT_FEAT_SUSPEND req not "
				       "supported for USB 3.0 roothub\n");
				जाओ error;
			पूर्ण

			अगर (invalid_rhport) अणु
				pr_err("invalid port number %d\n", wIndex);
				जाओ error;
			पूर्ण

			vhci_hcd->port_status[rhport] |= USB_PORT_STAT_SUSPEND;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			usbip_dbg_vhci_rh(
				" SetPortFeature: USB_PORT_FEAT_POWER\n");
			अगर (invalid_rhport) अणु
				pr_err("invalid port number %d\n", wIndex);
				जाओ error;
			पूर्ण
			अगर (hcd->speed == HCD_USB3)
				vhci_hcd->port_status[rhport] |= USB_SS_PORT_STAT_POWER;
			अन्यथा
				vhci_hcd->port_status[rhport] |= USB_PORT_STAT_POWER;
			अवरोध;
		हाल USB_PORT_FEAT_BH_PORT_RESET:
			usbip_dbg_vhci_rh(
				" SetPortFeature: USB_PORT_FEAT_BH_PORT_RESET\n");
			अगर (invalid_rhport) अणु
				pr_err("invalid port number %d\n", wIndex);
				जाओ error;
			पूर्ण
			/* Applicable only क्रम USB3.0 hub */
			अगर (hcd->speed != HCD_USB3) अणु
				pr_err("USB_PORT_FEAT_BH_PORT_RESET req not "
				       "supported for USB 2.0 roothub\n");
				जाओ error;
			पूर्ण
			fallthrough;
		हाल USB_PORT_FEAT_RESET:
			usbip_dbg_vhci_rh(
				" SetPortFeature: USB_PORT_FEAT_RESET\n");
			अगर (invalid_rhport) अणु
				pr_err("invalid port number %d\n", wIndex);
				जाओ error;
			पूर्ण
			/* अगर it's alपढ़ोy enabled, disable */
			अगर (hcd->speed == HCD_USB3) अणु
				vhci_hcd->port_status[rhport] = 0;
				vhci_hcd->port_status[rhport] =
					(USB_SS_PORT_STAT_POWER |
					 USB_PORT_STAT_CONNECTION |
					 USB_PORT_STAT_RESET);
			पूर्ण अन्यथा अगर (vhci_hcd->port_status[rhport] & USB_PORT_STAT_ENABLE) अणु
				vhci_hcd->port_status[rhport] &= ~(USB_PORT_STAT_ENABLE
					| USB_PORT_STAT_LOW_SPEED
					| USB_PORT_STAT_HIGH_SPEED);
			पूर्ण

			/* 50msec reset संकेतing */
			vhci_hcd->re_समयout = jअगरfies + msecs_to_jअगरfies(50);
			fallthrough;
		शेष:
			usbip_dbg_vhci_rh(" SetPortFeature: default %d\n",
					  wValue);
			अगर (invalid_rhport) अणु
				pr_err("invalid port number %d\n", wIndex);
				जाओ error;
			पूर्ण
			अगर (wValue >= 32)
				जाओ error;
			अगर (hcd->speed == HCD_USB3) अणु
				अगर ((vhci_hcd->port_status[rhport] &
				     USB_SS_PORT_STAT_POWER) != 0) अणु
					vhci_hcd->port_status[rhport] |= (1 << wValue);
				पूर्ण
			पूर्ण अन्यथा
				अगर ((vhci_hcd->port_status[rhport] &
				     USB_PORT_STAT_POWER) != 0) अणु
					vhci_hcd->port_status[rhport] |= (1 << wValue);
				पूर्ण
		पूर्ण
		अवरोध;
	हाल GetPortErrorCount:
		usbip_dbg_vhci_rh(" GetPortErrorCount\n");
		अगर (hcd->speed != HCD_USB3) अणु
			pr_err("GetPortErrorCount req not "
			       "supported for USB 2.0 roothub\n");
			जाओ error;
		पूर्ण
		/* We'll always वापस 0 since this is a dummy hub */
		*(__le32 *) buf = cpu_to_le32(0);
		अवरोध;
	हाल SetHubDepth:
		usbip_dbg_vhci_rh(" SetHubDepth\n");
		अगर (hcd->speed != HCD_USB3) अणु
			pr_err("SetHubDepth req not supported for "
			       "USB 2.0 roothub\n");
			जाओ error;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("default hub control req: %04x v%04x i%04x l%d\n",
			typeReq, wValue, wIndex, wLength);
error:
		/* "protocol stall" on error */
		retval = -EPIPE;
	पूर्ण

	अगर (usbip_dbg_flag_vhci_rh) अणु
		pr_debug("port %d\n", rhport);
		/* Only dump valid port status */
		अगर (!invalid_rhport) अणु
			dump_port_status_dअगरf(prev_port_status[rhport],
					      vhci_hcd->port_status[rhport],
					      hcd->speed == HCD_USB3);
		पूर्ण
	पूर्ण
	usbip_dbg_vhci_rh(" bye\n");

	spin_unlock_irqrestore(&vhci->lock, flags);

	अगर (!invalid_rhport &&
	    (vhci_hcd->port_status[rhport] & PORT_C_MASK) != 0) अणु
		usb_hcd_poll_rh_status(hcd);
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम vhci_tx_urb(काष्ठा urb *urb, काष्ठा vhci_device *vdev)
अणु
	काष्ठा vhci_priv *priv;
	काष्ठा vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	अचिन्हित दीर्घ flags;

	priv = kzalloc(माप(काष्ठा vhci_priv), GFP_ATOMIC);
	अगर (!priv) अणु
		usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_MALLOC);
		वापस;
	पूर्ण

	spin_lock_irqsave(&vdev->priv_lock, flags);

	priv->seqnum = atomic_inc_वापस(&vhci_hcd->seqnum);
	अगर (priv->seqnum == 0xffff)
		dev_info(&urb->dev->dev, "seqnum max\n");

	priv->vdev = vdev;
	priv->urb = urb;

	urb->hcpriv = (व्योम *) priv;

	list_add_tail(&priv->list, &vdev->priv_tx);

	wake_up(&vdev->रुकोq_tx);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);
पूर्ण

अटल पूर्णांक vhci_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, gfp_t mem_flags)
अणु
	काष्ठा vhci_hcd *vhci_hcd = hcd_to_vhci_hcd(hcd);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	काष्ठा device *dev = &urb->dev->dev;
	u8 portnum = urb->dev->portnum;
	पूर्णांक ret = 0;
	काष्ठा vhci_device *vdev;
	अचिन्हित दीर्घ flags;

	अगर (portnum > VHCI_HC_PORTS) अणु
		pr_err("invalid port number %d\n", portnum);
		वापस -ENODEV;
	पूर्ण
	vdev = &vhci_hcd->vdev[portnum-1];

	अगर (!urb->transfer_buffer && !urb->num_sgs &&
	     urb->transfer_buffer_length) अणु
		dev_dbg(dev, "Null URB transfer buffer\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&vhci->lock, flags);

	अगर (urb->status != -EINPROGRESS) अणु
		dev_err(dev, "URB already unlinked!, status %d\n", urb->status);
		spin_unlock_irqrestore(&vhci->lock, flags);
		वापस urb->status;
	पूर्ण

	/* refuse enqueue क्रम dead connection */
	spin_lock(&vdev->ud.lock);
	अगर (vdev->ud.status == VDEV_ST_शून्य ||
	    vdev->ud.status == VDEV_ST_ERROR) अणु
		dev_err(dev, "enqueue for inactive port %d\n", vdev->rhport);
		spin_unlock(&vdev->ud.lock);
		spin_unlock_irqrestore(&vhci->lock, flags);
		वापस -ENODEV;
	पूर्ण
	spin_unlock(&vdev->ud.lock);

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (ret)
		जाओ no_need_unlink;

	/*
	 * The क्रमागतeration process is as follows;
	 *
	 *  1. Get_Descriptor request to DevAddrs(0) EndPoपूर्णांक(0)
	 *     to get max packet length of शेष pipe
	 *
	 *  2. Set_Address request to DevAddr(0) EndPoपूर्णांक(0)
	 *
	 */
	अगर (usb_pipedevice(urb->pipe) == 0) अणु
		__u8 type = usb_pipetype(urb->pipe);
		काष्ठा usb_ctrlrequest *ctrlreq =
			(काष्ठा usb_ctrlrequest *) urb->setup_packet;

		अगर (type != PIPE_CONTROL || !ctrlreq) अणु
			dev_err(dev, "invalid request to devnum 0\n");
			ret = -EINVAL;
			जाओ no_need_xmit;
		पूर्ण

		चयन (ctrlreq->bRequest) अणु
		हाल USB_REQ_SET_ADDRESS:
			/* set_address may come when a device is reset */
			dev_info(dev, "SetAddress Request (%d) to port %d\n",
				 ctrlreq->wValue, vdev->rhport);

			usb_put_dev(vdev->udev);
			vdev->udev = usb_get_dev(urb->dev);

			spin_lock(&vdev->ud.lock);
			vdev->ud.status = VDEV_ST_USED;
			spin_unlock(&vdev->ud.lock);

			अगर (urb->status == -EINPROGRESS) अणु
				/* This request is successfully completed. */
				/* If not -EINPROGRESS, possibly unlinked. */
				urb->status = 0;
			पूर्ण

			जाओ no_need_xmit;

		हाल USB_REQ_GET_DESCRIPTOR:
			अगर (ctrlreq->wValue == cpu_to_le16(USB_DT_DEVICE << 8))
				usbip_dbg_vhci_hc(
					"Not yet?:Get_Descriptor to device 0 (get max pipe size)\n");

			usb_put_dev(vdev->udev);
			vdev->udev = usb_get_dev(urb->dev);
			जाओ out;

		शेष:
			/* NOT REACHED */
			dev_err(dev,
				"invalid request to devnum 0 bRequest %u, wValue %u\n",
				ctrlreq->bRequest,
				ctrlreq->wValue);
			ret =  -EINVAL;
			जाओ no_need_xmit;
		पूर्ण

	पूर्ण

out:
	vhci_tx_urb(urb, vdev);
	spin_unlock_irqrestore(&vhci->lock, flags);

	वापस 0;

no_need_xmit:
	usb_hcd_unlink_urb_from_ep(hcd, urb);
no_need_unlink:
	spin_unlock_irqrestore(&vhci->lock, flags);
	अगर (!ret) अणु
		/* usb_hcd_giveback_urb() should be called with
		 * irqs disabled
		 */
		local_irq_disable();
		usb_hcd_giveback_urb(hcd, urb, urb->status);
		local_irq_enable();
	पूर्ण
	वापस ret;
पूर्ण

/*
 * vhci_rx gives back the urb after receiving the reply of the urb.  If an
 * unlink pdu is sent or not, vhci_rx receives a normal वापस pdu and gives
 * back its urb. For the driver unlinking the urb, the content of the urb is
 * not important, but the calling to its completion handler is important; the
 * completion of unlinking is notअगरied by the completion handler.
 *
 *
 * CLIENT SIDE
 *
 * - When vhci_hcd receives RET_SUBMIT,
 *
 *	- हाल 1a). the urb of the pdu is not unlinking.
 *		- normal हाल
 *		=> just give back the urb
 *
 *	- हाल 1b). the urb of the pdu is unlinking.
 *		- usbip.ko will वापस a reply of the unlinking request.
 *		=> give back the urb now and go to हाल 2b).
 *
 * - When vhci_hcd receives RET_UNLINK,
 *
 *	- हाल 2a). a submit request is still pending in vhci_hcd.
 *		- urb was really pending in usbip.ko and urb_unlink_urb() was
 *		  completed there.
 *		=> मुक्त a pending submit request
 *		=> notअगरy unlink completeness by giving back the urb
 *
 *	- हाल 2b). a submit request is *not* pending in vhci_hcd.
 *		- urb was alपढ़ोy given back to the core driver.
 *		=> करो not give back the urb
 *
 *
 * SERVER SIDE
 *
 * - When usbip receives CMD_UNLINK,
 *
 *	- हाल 3a). the urb of the unlink request is now in submission.
 *		=> करो usb_unlink_urb().
 *		=> after the unlink is completed, send RET_UNLINK.
 *
 *	- हाल 3b). the urb of the unlink request is not in submission.
 *		- may be alपढ़ोy completed or never be received
 *		=> send RET_UNLINK
 *
 */
अटल पूर्णांक vhci_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा vhci_hcd *vhci_hcd = hcd_to_vhci_hcd(hcd);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	काष्ठा vhci_priv *priv;
	काष्ठा vhci_device *vdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vhci->lock, flags);

	priv = urb->hcpriv;
	अगर (!priv) अणु
		/* URB was never linked! or will be soon given back by
		 * vhci_rx. */
		spin_unlock_irqrestore(&vhci->lock, flags);
		वापस -EIDRM;
	पूर्ण

	अणु
		पूर्णांक ret = 0;

		ret = usb_hcd_check_unlink_urb(hcd, urb, status);
		अगर (ret) अणु
			spin_unlock_irqrestore(&vhci->lock, flags);
			वापस ret;
		पूर्ण
	पूर्ण

	 /* send unlink request here? */
	vdev = priv->vdev;

	अगर (!vdev->ud.tcp_socket) अणु
		/* tcp connection is बंदd */
		spin_lock(&vdev->priv_lock);

		list_del(&priv->list);
		kमुक्त(priv);
		urb->hcpriv = शून्य;

		spin_unlock(&vdev->priv_lock);

		/*
		 * If tcp connection is alive, we have sent CMD_UNLINK.
		 * vhci_rx will receive RET_UNLINK and give back the URB.
		 * Otherwise, we give back it here.
		 */
		usb_hcd_unlink_urb_from_ep(hcd, urb);

		spin_unlock_irqrestore(&vhci->lock, flags);
		usb_hcd_giveback_urb(hcd, urb, urb->status);
		spin_lock_irqsave(&vhci->lock, flags);

	पूर्ण अन्यथा अणु
		/* tcp connection is alive */
		काष्ठा vhci_unlink *unlink;

		spin_lock(&vdev->priv_lock);

		/* setup CMD_UNLINK pdu */
		unlink = kzalloc(माप(काष्ठा vhci_unlink), GFP_ATOMIC);
		अगर (!unlink) अणु
			spin_unlock(&vdev->priv_lock);
			spin_unlock_irqrestore(&vhci->lock, flags);
			usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_MALLOC);
			वापस -ENOMEM;
		पूर्ण

		unlink->seqnum = atomic_inc_वापस(&vhci_hcd->seqnum);
		अगर (unlink->seqnum == 0xffff)
			pr_info("seqnum max\n");

		unlink->unlink_seqnum = priv->seqnum;

		/* send cmd_unlink and try to cancel the pending URB in the
		 * peer */
		list_add_tail(&unlink->list, &vdev->unlink_tx);
		wake_up(&vdev->रुकोq_tx);

		spin_unlock(&vdev->priv_lock);
	पूर्ण

	spin_unlock_irqrestore(&vhci->lock, flags);

	usbip_dbg_vhci_hc("leave\n");
	वापस 0;
पूर्ण

अटल व्योम vhci_device_unlink_cleanup(काष्ठा vhci_device *vdev)
अणु
	काष्ठा vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	काष्ठा usb_hcd *hcd = vhci_hcd_to_hcd(vhci_hcd);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	काष्ठा vhci_unlink *unlink, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vhci->lock, flags);
	spin_lock(&vdev->priv_lock);

	list_क्रम_each_entry_safe(unlink, पंचांगp, &vdev->unlink_tx, list) अणु
		pr_info("unlink cleanup tx %lu\n", unlink->unlink_seqnum);
		list_del(&unlink->list);
		kमुक्त(unlink);
	पूर्ण

	जबतक (!list_empty(&vdev->unlink_rx)) अणु
		काष्ठा urb *urb;

		unlink = list_first_entry(&vdev->unlink_rx, काष्ठा vhci_unlink,
			list);

		/* give back URB of unanswered unlink request */
		pr_info("unlink cleanup rx %lu\n", unlink->unlink_seqnum);

		urb = pickup_urb_and_मुक्त_priv(vdev, unlink->unlink_seqnum);
		अगर (!urb) अणु
			pr_info("the urb (seqnum %lu) was already given back\n",
				unlink->unlink_seqnum);
			list_del(&unlink->list);
			kमुक्त(unlink);
			जारी;
		पूर्ण

		urb->status = -ENODEV;

		usb_hcd_unlink_urb_from_ep(hcd, urb);

		list_del(&unlink->list);

		spin_unlock(&vdev->priv_lock);
		spin_unlock_irqrestore(&vhci->lock, flags);

		usb_hcd_giveback_urb(hcd, urb, urb->status);

		spin_lock_irqsave(&vhci->lock, flags);
		spin_lock(&vdev->priv_lock);

		kमुक्त(unlink);
	पूर्ण

	spin_unlock(&vdev->priv_lock);
	spin_unlock_irqrestore(&vhci->lock, flags);
पूर्ण

/*
 * The important thing is that only one context begins cleanup.
 * This is why error handling and cleanup become simple.
 * We करो not want to consider race condition as possible.
 */
अटल व्योम vhci_shutकरोwn_connection(काष्ठा usbip_device *ud)
अणु
	काष्ठा vhci_device *vdev = container_of(ud, काष्ठा vhci_device, ud);

	/* need this? see stub_dev.c */
	अगर (ud->tcp_socket) अणु
		pr_debug("shutdown tcp_socket %d\n", ud->sockfd);
		kernel_sock_shutकरोwn(ud->tcp_socket, SHUT_RDWR);
	पूर्ण

	/* समाप्त thपढ़ोs related to this sdev */
	अगर (vdev->ud.tcp_rx) अणु
		kthपढ़ो_stop_put(vdev->ud.tcp_rx);
		vdev->ud.tcp_rx = शून्य;
	पूर्ण
	अगर (vdev->ud.tcp_tx) अणु
		kthपढ़ो_stop_put(vdev->ud.tcp_tx);
		vdev->ud.tcp_tx = शून्य;
	पूर्ण
	pr_info("stop threads\n");

	/* active connection is बंदd */
	अगर (vdev->ud.tcp_socket) अणु
		sockfd_put(vdev->ud.tcp_socket);
		vdev->ud.tcp_socket = शून्य;
		vdev->ud.sockfd = -1;
	पूर्ण
	pr_info("release socket\n");

	vhci_device_unlink_cleanup(vdev);

	/*
	 * rh_port_disconnect() is a trigger of ...
	 *   usb_disable_device():
	 *	disable all the endpoपूर्णांकs क्रम a USB device.
	 *   usb_disable_endpoपूर्णांक():
	 *	disable endpoपूर्णांकs. pending urbs are unlinked(dequeued).
	 *
	 * NOTE: After calling rh_port_disconnect(), the USB device drivers of a
	 * detached device should release used urbs in a cleanup function (i.e.
	 * xxx_disconnect()). Thereक्रमe, vhci_hcd करोes not need to release
	 * pushed urbs and their निजी data in this function.
	 *
	 * NOTE: vhci_dequeue() must be considered carefully. When shutting करोwn
	 * a connection, vhci_shutकरोwn_connection() expects vhci_dequeue()
	 * gives back pushed urbs and मुक्तs their निजी data by request of
	 * the cleanup function of a USB driver. When unlinking a urb with an
	 * active connection, vhci_dequeue() करोes not give back the urb which
	 * is actually given back by vhci_rx after receiving its वापस pdu.
	 *
	 */
	rh_port_disconnect(vdev);

	pr_info("disconnect device\n");
पूर्ण

अटल व्योम vhci_device_reset(काष्ठा usbip_device *ud)
अणु
	काष्ठा vhci_device *vdev = container_of(ud, काष्ठा vhci_device, ud);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ud->lock, flags);

	vdev->speed  = 0;
	vdev->devid  = 0;

	usb_put_dev(vdev->udev);
	vdev->udev = शून्य;

	अगर (ud->tcp_socket) अणु
		sockfd_put(ud->tcp_socket);
		ud->tcp_socket = शून्य;
		ud->sockfd = -1;
	पूर्ण
	ud->status = VDEV_ST_शून्य;

	spin_unlock_irqrestore(&ud->lock, flags);
पूर्ण

अटल व्योम vhci_device_unusable(काष्ठा usbip_device *ud)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ud->lock, flags);
	ud->status = VDEV_ST_ERROR;
	spin_unlock_irqrestore(&ud->lock, flags);
पूर्ण

अटल व्योम vhci_device_init(काष्ठा vhci_device *vdev)
अणु
	स_रखो(vdev, 0, माप(काष्ठा vhci_device));

	vdev->ud.side   = USBIP_VHCI;
	vdev->ud.status = VDEV_ST_शून्य;
	spin_lock_init(&vdev->ud.lock);
	mutex_init(&vdev->ud.sysfs_lock);

	INIT_LIST_HEAD(&vdev->priv_rx);
	INIT_LIST_HEAD(&vdev->priv_tx);
	INIT_LIST_HEAD(&vdev->unlink_tx);
	INIT_LIST_HEAD(&vdev->unlink_rx);
	spin_lock_init(&vdev->priv_lock);

	init_रुकोqueue_head(&vdev->रुकोq_tx);

	vdev->ud.eh_ops.shutकरोwn = vhci_shutकरोwn_connection;
	vdev->ud.eh_ops.reset = vhci_device_reset;
	vdev->ud.eh_ops.unusable = vhci_device_unusable;

	usbip_start_eh(&vdev->ud);
पूर्ण

अटल पूर्णांक hcd_name_to_id(स्थिर अक्षर *name)
अणु
	अक्षर *c;
	दीर्घ val;
	पूर्णांक ret;

	c = म_अक्षर(name, '.');
	अगर (c == शून्य)
		वापस 0;

	ret = kम_से_दीर्घ(c+1, 10, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

अटल पूर्णांक vhci_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा vhci *vhci = *((व्योम **)dev_get_platdata(hcd->self.controller));
	अगर (usb_hcd_is_primary_hcd(hcd)) अणु
		vhci->vhci_hcd_hs = hcd_to_vhci_hcd(hcd);
		vhci->vhci_hcd_hs->vhci = vhci;
		/*
		 * Mark the first roothub as being USB 2.0.
		 * The USB 3.0 roothub will be रेजिस्टरed later by
		 * vhci_hcd_probe()
		 */
		hcd->speed = HCD_USB2;
		hcd->self.root_hub->speed = USB_SPEED_HIGH;
	पूर्ण अन्यथा अणु
		vhci->vhci_hcd_ss = hcd_to_vhci_hcd(hcd);
		vhci->vhci_hcd_ss->vhci = vhci;
		hcd->speed = HCD_USB3;
		hcd->self.root_hub->speed = USB_SPEED_SUPER;
	पूर्ण

	/*
	 * Support SG.
	 * sg_tablesize is an arbitrary value to alleviate memory pressure
	 * on the host.
	 */
	hcd->self.sg_tablesize = 32;
	hcd->self.no_sg_स्थिरraपूर्णांक = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक vhci_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा vhci_hcd *vhci_hcd = hcd_to_vhci_hcd(hcd);
	पूर्णांक id, rhport;
	पूर्णांक err;

	usbip_dbg_vhci_hc("enter vhci_start\n");

	अगर (usb_hcd_is_primary_hcd(hcd))
		spin_lock_init(&vhci_hcd->vhci->lock);

	/* initialize निजी data of usb_hcd */

	क्रम (rhport = 0; rhport < VHCI_HC_PORTS; rhport++) अणु
		काष्ठा vhci_device *vdev = &vhci_hcd->vdev[rhport];

		vhci_device_init(vdev);
		vdev->rhport = rhport;
	पूर्ण

	atomic_set(&vhci_hcd->seqnum, 0);

	hcd->घातer_budget = 0; /* no limit */
	hcd->uses_new_polling = 1;

#अगर_घोषित CONFIG_USB_OTG
	hcd->self.otg_port = 1;
#पूर्ण_अगर

	id = hcd_name_to_id(hcd_name(hcd));
	अगर (id < 0) अणु
		pr_err("invalid vhci name %s\n", hcd_name(hcd));
		वापस -EINVAL;
	पूर्ण

	/* vhci_hcd is now पढ़ोy to be controlled through sysfs */
	अगर (id == 0 && usb_hcd_is_primary_hcd(hcd)) अणु
		err = vhci_init_attr_group();
		अगर (err) अणु
			dev_err(hcd_dev(hcd), "init attr group failed, err = %d\n", err);
			वापस err;
		पूर्ण
		err = sysfs_create_group(&hcd_dev(hcd)->kobj, &vhci_attr_group);
		अगर (err) अणु
			dev_err(hcd_dev(hcd), "create sysfs files failed, err = %d\n", err);
			vhci_finish_attr_group();
			वापस err;
		पूर्ण
		pr_info("created sysfs %s\n", hcd_name(hcd));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vhci_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा vhci_hcd *vhci_hcd = hcd_to_vhci_hcd(hcd);
	पूर्णांक id, rhport;

	usbip_dbg_vhci_hc("stop VHCI controller\n");

	/* 1. हटाओ the userland पूर्णांकerface of vhci_hcd */
	id = hcd_name_to_id(hcd_name(hcd));
	अगर (id == 0 && usb_hcd_is_primary_hcd(hcd)) अणु
		sysfs_हटाओ_group(&hcd_dev(hcd)->kobj, &vhci_attr_group);
		vhci_finish_attr_group();
	पूर्ण

	/* 2. shutकरोwn all the ports of vhci_hcd */
	क्रम (rhport = 0; rhport < VHCI_HC_PORTS; rhport++) अणु
		काष्ठा vhci_device *vdev = &vhci_hcd->vdev[rhport];

		usbip_event_add(&vdev->ud, VDEV_EVENT_REMOVED);
		usbip_stop_eh(&vdev->ud);
	पूर्ण
पूर्ण

अटल पूर्णांक vhci_get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	dev_err_ratelimited(&hcd->self.root_hub->dev, "Not yet implemented\n");
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

/* FIXME: suspend/resume */
अटल पूर्णांक vhci_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा vhci *vhci = *((व्योम **)dev_get_platdata(hcd->self.controller));
	अचिन्हित दीर्घ flags;

	dev_dbg(&hcd->self.root_hub->dev, "%s\n", __func__);

	spin_lock_irqsave(&vhci->lock, flags);
	hcd->state = HC_STATE_SUSPENDED;
	spin_unlock_irqrestore(&vhci->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vhci_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा vhci *vhci = *((व्योम **)dev_get_platdata(hcd->self.controller));
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	dev_dbg(&hcd->self.root_hub->dev, "%s\n", __func__);

	spin_lock_irqsave(&vhci->lock, flags);
	अगर (!HCD_HW_ACCESSIBLE(hcd))
		rc = -ESHUTDOWN;
	अन्यथा
		hcd->state = HC_STATE_RUNNING;
	spin_unlock_irqrestore(&vhci->lock, flags);

	वापस rc;
पूर्ण

#अन्यथा

#घोषणा vhci_bus_suspend      शून्य
#घोषणा vhci_bus_resume       शून्य
#पूर्ण_अगर

/* Change a group of bulk endpoपूर्णांकs to support multiple stream IDs */
अटल पूर्णांक vhci_alloc_streams(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
	काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
	अचिन्हित पूर्णांक num_streams, gfp_t mem_flags)
अणु
	dev_dbg(&hcd->self.root_hub->dev, "vhci_alloc_streams not implemented\n");
	वापस 0;
पूर्ण

/* Reverts a group of bulk endpoपूर्णांकs back to not using stream IDs. */
अटल पूर्णांक vhci_मुक्त_streams(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
	काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
	gfp_t mem_flags)
अणु
	dev_dbg(&hcd->self.root_hub->dev, "vhci_free_streams not implemented\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hc_driver vhci_hc_driver = अणु
	.description	= driver_name,
	.product_desc	= driver_desc,
	.hcd_priv_size	= माप(काष्ठा vhci_hcd),

	.flags		= HCD_USB3 | HCD_SHARED,

	.reset		= vhci_setup,
	.start		= vhci_start,
	.stop		= vhci_stop,

	.urb_enqueue	= vhci_urb_enqueue,
	.urb_dequeue	= vhci_urb_dequeue,

	.get_frame_number = vhci_get_frame_number,

	.hub_status_data = vhci_hub_status,
	.hub_control    = vhci_hub_control,
	.bus_suspend	= vhci_bus_suspend,
	.bus_resume	= vhci_bus_resume,

	.alloc_streams	= vhci_alloc_streams,
	.मुक्त_streams	= vhci_मुक्त_streams,
पूर्ण;

अटल पूर्णांक vhci_hcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vhci             *vhci = *((व्योम **)dev_get_platdata(&pdev->dev));
	काष्ठा usb_hcd		*hcd_hs;
	काष्ठा usb_hcd		*hcd_ss;
	पूर्णांक			ret;

	usbip_dbg_vhci_hc("name %s id %d\n", pdev->name, pdev->id);

	/*
	 * Allocate and initialize hcd.
	 * Our निजी data is also allocated स्वतःmatically.
	 */
	hcd_hs = usb_create_hcd(&vhci_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd_hs) अणु
		pr_err("create primary hcd failed\n");
		वापस -ENOMEM;
	पूर्ण
	hcd_hs->has_tt = 1;

	/*
	 * Finish generic HCD काष्ठाure initialization and रेजिस्टर.
	 * Call the driver's reset() and start() routines.
	 */
	ret = usb_add_hcd(hcd_hs, 0, 0);
	अगर (ret != 0) अणु
		pr_err("usb_add_hcd hs failed %d\n", ret);
		जाओ put_usb2_hcd;
	पूर्ण

	hcd_ss = usb_create_shared_hcd(&vhci_hc_driver, &pdev->dev,
				       dev_name(&pdev->dev), hcd_hs);
	अगर (!hcd_ss) अणु
		ret = -ENOMEM;
		pr_err("create shared hcd failed\n");
		जाओ हटाओ_usb2_hcd;
	पूर्ण

	ret = usb_add_hcd(hcd_ss, 0, 0);
	अगर (ret) अणु
		pr_err("usb_add_hcd ss failed %d\n", ret);
		जाओ put_usb3_hcd;
	पूर्ण

	usbip_dbg_vhci_hc("bye\n");
	वापस 0;

put_usb3_hcd:
	usb_put_hcd(hcd_ss);
हटाओ_usb2_hcd:
	usb_हटाओ_hcd(hcd_hs);
put_usb2_hcd:
	usb_put_hcd(hcd_hs);
	vhci->vhci_hcd_hs = शून्य;
	vhci->vhci_hcd_ss = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक vhci_hcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vhci *vhci = *((व्योम **)dev_get_platdata(&pdev->dev));

	/*
	 * Disconnects the root hub,
	 * then reverses the effects of usb_add_hcd(),
	 * invoking the HCD's stop() methods.
	 */
	usb_हटाओ_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_ss));
	usb_put_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_ss));

	usb_हटाओ_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_hs));
	usb_put_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_hs));

	vhci->vhci_hcd_hs = शून्य;
	vhci->vhci_hcd_ss = शून्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

/* what should happen क्रम USB/IP under suspend/resume? */
अटल पूर्णांक vhci_hcd_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा vhci *vhci;
	पूर्णांक rhport;
	पूर्णांक connected = 0;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	hcd = platक्रमm_get_drvdata(pdev);
	अगर (!hcd)
		वापस 0;

	vhci = *((व्योम **)dev_get_platdata(hcd->self.controller));

	spin_lock_irqsave(&vhci->lock, flags);

	क्रम (rhport = 0; rhport < VHCI_HC_PORTS; rhport++) अणु
		अगर (vhci->vhci_hcd_hs->port_status[rhport] &
		    USB_PORT_STAT_CONNECTION)
			connected += 1;

		अगर (vhci->vhci_hcd_ss->port_status[rhport] &
		    USB_PORT_STAT_CONNECTION)
			connected += 1;
	पूर्ण

	spin_unlock_irqrestore(&vhci->lock, flags);

	अगर (connected > 0) अणु
		dev_info(&pdev->dev,
			 "We have %d active connection%s. Do not suspend.\n",
			 connected, (connected == 1 ? "" : "s"));
		ret =  -EBUSY;
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "suspend vhci_hcd");
		clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vhci_hcd_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	hcd = platक्रमm_get_drvdata(pdev);
	अगर (!hcd)
		वापस 0;
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	usb_hcd_poll_rh_status(hcd);

	वापस 0;
पूर्ण

#अन्यथा

#घोषणा vhci_hcd_suspend	शून्य
#घोषणा vhci_hcd_resume		शून्य

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver vhci_driver = अणु
	.probe	= vhci_hcd_probe,
	.हटाओ	= vhci_hcd_हटाओ,
	.suspend = vhci_hcd_suspend,
	.resume	= vhci_hcd_resume,
	.driver	= अणु
		.name = driver_name,
	पूर्ण,
पूर्ण;

अटल व्योम del_platक्रमm_devices(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक i;

	क्रम (i = 0; i < vhci_num_controllers; i++) अणु
		pdev = vhcis[i].pdev;
		अगर (pdev != शून्य)
			platक्रमm_device_unरेजिस्टर(pdev);
		vhcis[i].pdev = शून्य;
	पूर्ण
	sysfs_हटाओ_link(&platक्रमm_bus.kobj, driver_name);
पूर्ण

अटल पूर्णांक __init vhci_hcd_init(व्योम)
अणु
	पूर्णांक i, ret;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (vhci_num_controllers < 1)
		vhci_num_controllers = 1;

	vhcis = kसुस्मृति(vhci_num_controllers, माप(काष्ठा vhci), GFP_KERNEL);
	अगर (vhcis == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < vhci_num_controllers; i++) अणु
		vhcis[i].pdev = platक्रमm_device_alloc(driver_name, i);
		अगर (!vhcis[i].pdev) अणु
			i--;
			जबतक (i >= 0)
				platक्रमm_device_put(vhcis[i--].pdev);
			ret = -ENOMEM;
			जाओ err_device_alloc;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < vhci_num_controllers; i++) अणु
		व्योम *vhci = &vhcis[i];
		ret = platक्रमm_device_add_data(vhcis[i].pdev, &vhci, माप(व्योम *));
		अगर (ret)
			जाओ err_driver_रेजिस्टर;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&vhci_driver);
	अगर (ret)
		जाओ err_driver_रेजिस्टर;

	क्रम (i = 0; i < vhci_num_controllers; i++) अणु
		ret = platक्रमm_device_add(vhcis[i].pdev);
		अगर (ret < 0) अणु
			i--;
			जबतक (i >= 0)
				platक्रमm_device_del(vhcis[i--].pdev);
			जाओ err_add_hcd;
		पूर्ण
	पूर्ण

	वापस ret;

err_add_hcd:
	platक्रमm_driver_unरेजिस्टर(&vhci_driver);
err_driver_रेजिस्टर:
	क्रम (i = 0; i < vhci_num_controllers; i++)
		platक्रमm_device_put(vhcis[i].pdev);
err_device_alloc:
	kमुक्त(vhcis);
	वापस ret;
पूर्ण

अटल व्योम __निकास vhci_hcd_निकास(व्योम)
अणु
	del_platक्रमm_devices();
	platक्रमm_driver_unरेजिस्टर(&vhci_driver);
	kमुक्त(vhcis);
पूर्ण

module_init(vhci_hcd_init);
module_निकास(vhci_hcd_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
