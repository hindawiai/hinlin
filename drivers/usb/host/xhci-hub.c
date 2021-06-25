<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */


#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/bitfield.h>

#समावेश "xhci.h"
#समावेश "xhci-trace.h"

#घोषणा	PORT_WAKE_BITS	(PORT_WKOC_E | PORT_WKDISC_E | PORT_WKCONN_E)
#घोषणा	PORT_RWC_BITS	(PORT_CSC | PORT_PEC | PORT_WRC | PORT_OCC | \
			 PORT_RC | PORT_PLC | PORT_PE)

/* Default sublink speed attribute of each lane */
अटल u32 ssp_cap_शेष_ssa[] = अणु
	0x00050034, /* USB 3.0 SS Gen1x1 id:4 symmetric rx 5Gbps */
	0x000500b4, /* USB 3.0 SS Gen1x1 id:4 symmetric tx 5Gbps */
	0x000a4035, /* USB 3.1 SSP Gen2x1 id:5 symmetric rx 10Gbps */
	0x000a40b5, /* USB 3.1 SSP Gen2x1 id:5 symmetric tx 10Gbps */
	0x00054036, /* USB 3.2 SSP Gen1x2 id:6 symmetric rx 5Gbps */
	0x000540b6, /* USB 3.2 SSP Gen1x2 id:6 symmetric tx 5Gbps */
	0x000a4037, /* USB 3.2 SSP Gen2x2 id:7 symmetric rx 10Gbps */
	0x000a40b7, /* USB 3.2 SSP Gen2x2 id:7 symmetric tx 10Gbps */
पूर्ण;

अटल पूर्णांक xhci_create_usb3x_bos_desc(काष्ठा xhci_hcd *xhci, अक्षर *buf,
				      u16 wLength)
अणु
	काष्ठा usb_bos_descriptor	*bos;
	काष्ठा usb_ss_cap_descriptor	*ss_cap;
	काष्ठा usb_ssp_cap_descriptor	*ssp_cap;
	काष्ठा xhci_port_cap		*port_cap = शून्य;
	u16				bcdUSB;
	u32				reg;
	u32				min_rate = 0;
	u8				min_ssid;
	u8				ssac;
	u8				ssic;
	पूर्णांक				offset;
	पूर्णांक				i;

	/* BOS descriptor */
	bos = (काष्ठा usb_bos_descriptor *)buf;
	bos->bLength = USB_DT_BOS_SIZE;
	bos->bDescriptorType = USB_DT_BOS;
	bos->wTotalLength = cpu_to_le16(USB_DT_BOS_SIZE +
					USB_DT_USB_SS_CAP_SIZE);
	bos->bNumDeviceCaps = 1;

	/* Create the descriptor क्रम port with the highest revision */
	क्रम (i = 0; i < xhci->num_port_caps; i++) अणु
		u8 major = xhci->port_caps[i].maj_rev;
		u8 minor = xhci->port_caps[i].min_rev;
		u16 rev = (major << 8) | minor;

		अगर (i == 0 || bcdUSB < rev) अणु
			bcdUSB = rev;
			port_cap = &xhci->port_caps[i];
		पूर्ण
	पूर्ण

	अगर (bcdUSB >= 0x0310) अणु
		अगर (port_cap->psi_count) अणु
			u8 num_sym_ssa = 0;

			क्रम (i = 0; i < port_cap->psi_count; i++) अणु
				अगर ((port_cap->psi[i] & PLT_MASK) == PLT_SYM)
					num_sym_ssa++;
			पूर्ण

			ssac = port_cap->psi_count + num_sym_ssa - 1;
			ssic = port_cap->psi_uid_count - 1;
		पूर्ण अन्यथा अणु
			अगर (bcdUSB >= 0x0320)
				ssac = 7;
			अन्यथा
				ssac = 3;

			ssic = (ssac + 1) / 2 - 1;
		पूर्ण

		bos->bNumDeviceCaps++;
		bos->wTotalLength = cpu_to_le16(USB_DT_BOS_SIZE +
						USB_DT_USB_SS_CAP_SIZE +
						USB_DT_USB_SSP_CAP_SIZE(ssac));
	पूर्ण

	अगर (wLength < USB_DT_BOS_SIZE + USB_DT_USB_SS_CAP_SIZE)
		वापस wLength;

	/* SuperSpeed USB Device Capability */
	ss_cap = (काष्ठा usb_ss_cap_descriptor *)&buf[USB_DT_BOS_SIZE];
	ss_cap->bLength = USB_DT_USB_SS_CAP_SIZE;
	ss_cap->bDescriptorType = USB_DT_DEVICE_CAPABILITY;
	ss_cap->bDevCapabilityType = USB_SS_CAP_TYPE;
	ss_cap->bmAttributes = 0; /* set later */
	ss_cap->wSpeedSupported = cpu_to_le16(USB_5GBPS_OPERATION);
	ss_cap->bFunctionalitySupport = USB_LOW_SPEED_OPERATION;
	ss_cap->bU1devExitLat = 0; /* set later */
	ss_cap->bU2DevExitLat = 0; /* set later */

	reg = पढ़ोl(&xhci->cap_regs->hcc_params);
	अगर (HCC_LTC(reg))
		ss_cap->bmAttributes |= USB_LTM_SUPPORT;

	अगर ((xhci->quirks & XHCI_LPM_SUPPORT)) अणु
		reg = पढ़ोl(&xhci->cap_regs->hcs_params3);
		ss_cap->bU1devExitLat = HCS_U1_LATENCY(reg);
		ss_cap->bU2DevExitLat = cpu_to_le16(HCS_U2_LATENCY(reg));
	पूर्ण

	अगर (wLength < le16_to_cpu(bos->wTotalLength))
		वापस wLength;

	अगर (bcdUSB < 0x0310)
		वापस le16_to_cpu(bos->wTotalLength);

	ssp_cap = (काष्ठा usb_ssp_cap_descriptor *)&buf[USB_DT_BOS_SIZE +
		USB_DT_USB_SS_CAP_SIZE];
	ssp_cap->bLength = USB_DT_USB_SSP_CAP_SIZE(ssac);
	ssp_cap->bDescriptorType = USB_DT_DEVICE_CAPABILITY;
	ssp_cap->bDevCapabilityType = USB_SSP_CAP_TYPE;
	ssp_cap->bReserved = 0;
	ssp_cap->wReserved = 0;
	ssp_cap->bmAttributes =
		cpu_to_le32(FIELD_PREP(USB_SSP_SUBLINK_SPEED_ATTRIBS, ssac) |
			    FIELD_PREP(USB_SSP_SUBLINK_SPEED_IDS, ssic));

	अगर (!port_cap->psi_count) अणु
		क्रम (i = 0; i < ssac + 1; i++)
			ssp_cap->bmSublinkSpeedAttr[i] =
				cpu_to_le32(ssp_cap_शेष_ssa[i]);

		min_ssid = 4;
		जाओ out;
	पूर्ण

	offset = 0;
	क्रम (i = 0; i < port_cap->psi_count; i++) अणु
		u32 psi;
		u32 attr;
		u8 ssid;
		u8 lp;
		u8 lse;
		u8 psie;
		u16 lane_mantissa;
		u16 psim;
		u16 plt;

		psi = port_cap->psi[i];
		ssid = XHCI_EXT_PORT_PSIV(psi);
		lp = XHCI_EXT_PORT_LP(psi);
		psie = XHCI_EXT_PORT_PSIE(psi);
		psim = XHCI_EXT_PORT_PSIM(psi);
		plt = psi & PLT_MASK;

		lse = psie;
		lane_mantissa = psim;

		/* Shअगरt to Gbps and set SSP Link Protocol अगर 10Gpbs */
		क्रम (; psie < USB_SSP_SUBLINK_SPEED_LSE_GBPS; psie++)
			psim /= 1000;

		अगर (!min_rate || psim < min_rate) अणु
			min_ssid = ssid;
			min_rate = psim;
		पूर्ण

		/* Some host controllers करोn't set the link protocol क्रम SSP */
		अगर (psim >= 10)
			lp = USB_SSP_SUBLINK_SPEED_LP_SSP;

		/*
		 * PSIM and PSIE represent the total speed of PSI. The BOS
		 * descriptor SSP sublink speed attribute lane mantissa
		 * describes the lane speed. E.g. PSIM and PSIE क्रम gen2x2
		 * is 20Gbps, but the BOS descriptor lane speed mantissa is
		 * 10Gbps. Check and modअगरy the mantissa value to match the
		 * lane speed.
		 */
		अगर (bcdUSB == 0x0320 && plt == PLT_SYM) अणु
			/*
			 * The PSI dword क्रम gen1x2 and gen2x1 share the same
			 * values. But the lane speed क्रम gen1x2 is 5Gbps जबतक
			 * gen2x1 is 10Gbps. If the previous PSI dword SSID is
			 * 5 and the PSIE and PSIM match with SSID 6, let's
			 * assume that the controller follows the शेष speed
			 * id with SSID 6 क्रम gen1x2.
			 */
			अगर (ssid == 6 && psie == 3 && psim == 10 && i) अणु
				u32 prev = port_cap->psi[i - 1];

				अगर ((prev & PLT_MASK) == PLT_SYM &&
				    XHCI_EXT_PORT_PSIV(prev) == 5 &&
				    XHCI_EXT_PORT_PSIE(prev) == 3 &&
				    XHCI_EXT_PORT_PSIM(prev) == 10) अणु
					lse = USB_SSP_SUBLINK_SPEED_LSE_GBPS;
					lane_mantissa = 5;
				पूर्ण
			पूर्ण

			अगर (psie == 3 && psim > 10) अणु
				lse = USB_SSP_SUBLINK_SPEED_LSE_GBPS;
				lane_mantissa = 10;
			पूर्ण
		पूर्ण

		attr = (FIELD_PREP(USB_SSP_SUBLINK_SPEED_SSID, ssid) |
			FIELD_PREP(USB_SSP_SUBLINK_SPEED_LP, lp) |
			FIELD_PREP(USB_SSP_SUBLINK_SPEED_LSE, lse) |
			FIELD_PREP(USB_SSP_SUBLINK_SPEED_LSM, lane_mantissa));

		चयन (plt) अणु
		हाल PLT_SYM:
			attr |= FIELD_PREP(USB_SSP_SUBLINK_SPEED_ST,
					   USB_SSP_SUBLINK_SPEED_ST_SYM_RX);
			ssp_cap->bmSublinkSpeedAttr[offset++] = cpu_to_le32(attr);

			attr &= ~USB_SSP_SUBLINK_SPEED_ST;
			attr |= FIELD_PREP(USB_SSP_SUBLINK_SPEED_ST,
					   USB_SSP_SUBLINK_SPEED_ST_SYM_TX);
			ssp_cap->bmSublinkSpeedAttr[offset++] = cpu_to_le32(attr);
			अवरोध;
		हाल PLT_ASYM_RX:
			attr |= FIELD_PREP(USB_SSP_SUBLINK_SPEED_ST,
					   USB_SSP_SUBLINK_SPEED_ST_ASYM_RX);
			ssp_cap->bmSublinkSpeedAttr[offset++] = cpu_to_le32(attr);
			अवरोध;
		हाल PLT_ASYM_TX:
			attr |= FIELD_PREP(USB_SSP_SUBLINK_SPEED_ST,
					   USB_SSP_SUBLINK_SPEED_ST_ASYM_TX);
			ssp_cap->bmSublinkSpeedAttr[offset++] = cpu_to_le32(attr);
			अवरोध;
		पूर्ण
	पूर्ण
out:
	ssp_cap->wFunctionalitySupport =
		cpu_to_le16(FIELD_PREP(USB_SSP_MIN_SUBLINK_SPEED_ATTRIBUTE_ID,
				       min_ssid) |
			    FIELD_PREP(USB_SSP_MIN_RX_LANE_COUNT, 1) |
			    FIELD_PREP(USB_SSP_MIN_TX_LANE_COUNT, 1));

	वापस le16_to_cpu(bos->wTotalLength);
पूर्ण

अटल व्योम xhci_common_hub_descriptor(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_hub_descriptor *desc, पूर्णांक ports)
अणु
	u16 temp;

	desc->bPwrOn2PwrGood = 10;	/* xhci section 5.4.9 says 20ms max */
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 0;
	/* Bits 1:0 - support per-port घातer चयनing, or घातer always on */
	अगर (HCC_PPC(xhci->hcc_params))
		temp |= HUB_CHAR_INDV_PORT_LPSM;
	अन्यथा
		temp |= HUB_CHAR_NO_LPSM;
	/* Bit  2 - root hubs are not part of a compound device */
	/* Bits 4:3 - inभागidual port over current protection */
	temp |= HUB_CHAR_INDV_PORT_OCPM;
	/* Bits 6:5 - no TTs in root ports */
	/* Bit  7 - no port indicators */
	desc->wHubCharacteristics = cpu_to_le16(temp);
पूर्ण

/* Fill in the USB 2.0 roothub descriptor */
अटल व्योम xhci_usb2_hub_descriptor(काष्ठा usb_hcd *hcd, काष्ठा xhci_hcd *xhci,
		काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक ports;
	u16 temp;
	__u8 port_removable[(USB_MAXCHILDREN + 1 + 7) / 8];
	u32 portsc;
	अचिन्हित पूर्णांक i;
	काष्ठा xhci_hub *rhub;

	rhub = &xhci->usb2_rhub;
	ports = rhub->num_ports;
	xhci_common_hub_descriptor(xhci, desc, ports);
	desc->bDescriptorType = USB_DT_HUB;
	temp = 1 + (ports / 8);
	desc->bDescLength = USB_DT_HUB_NONVAR_SIZE + 2 * temp;

	/* The Device Removable bits are reported on a byte granularity.
	 * If the port करोesn't exist within that byte, the bit is set to 0.
	 */
	स_रखो(port_removable, 0, माप(port_removable));
	क्रम (i = 0; i < ports; i++) अणु
		portsc = पढ़ोl(rhub->ports[i]->addr);
		/* If a device is removable, PORTSC reports a 0, same as in the
		 * hub descriptor DeviceRemovable bits.
		 */
		अगर (portsc & PORT_DEV_REMOVE)
			/* This math is hairy because bit 0 of DeviceRemovable
			 * is reserved, and bit 1 is क्रम port 1, etc.
			 */
			port_removable[(i + 1) / 8] |= 1 << ((i + 1) % 8);
	पूर्ण

	/* ch11.h defines a hub descriptor that has room क्रम USB_MAXCHILDREN
	 * ports on it.  The USB 2.0 specअगरication says that there are two
	 * variable length fields at the end of the hub descriptor:
	 * DeviceRemovable and PortPwrCtrlMask.  But since we can have less than
	 * USB_MAXCHILDREN ports, we may need to use the DeviceRemovable array
	 * to set PortPwrCtrlMask bits.  PortPwrCtrlMask must always be set to
	 * 0xFF, so we initialize the both arrays (DeviceRemovable and
	 * PortPwrCtrlMask) to 0xFF.  Then we set the DeviceRemovable क्रम each
	 * set of ports that actually exist.
	 */
	स_रखो(desc->u.hs.DeviceRemovable, 0xff,
			माप(desc->u.hs.DeviceRemovable));
	स_रखो(desc->u.hs.PortPwrCtrlMask, 0xff,
			माप(desc->u.hs.PortPwrCtrlMask));

	क्रम (i = 0; i < (ports + 1 + 7) / 8; i++)
		स_रखो(&desc->u.hs.DeviceRemovable[i], port_removable[i],
				माप(__u8));
पूर्ण

/* Fill in the USB 3.0 roothub descriptor */
अटल व्योम xhci_usb3_hub_descriptor(काष्ठा usb_hcd *hcd, काष्ठा xhci_hcd *xhci,
		काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक ports;
	u16 port_removable;
	u32 portsc;
	अचिन्हित पूर्णांक i;
	काष्ठा xhci_hub *rhub;

	rhub = &xhci->usb3_rhub;
	ports = rhub->num_ports;
	xhci_common_hub_descriptor(xhci, desc, ports);
	desc->bDescriptorType = USB_DT_SS_HUB;
	desc->bDescLength = USB_DT_SS_HUB_SIZE;

	/* header decode latency should be zero क्रम roothubs,
	 * see section 4.23.5.2.
	 */
	desc->u.ss.bHubHdrDecLat = 0;
	desc->u.ss.wHubDelay = 0;

	port_removable = 0;
	/* bit 0 is reserved, bit 1 is क्रम port 1, etc. */
	क्रम (i = 0; i < ports; i++) अणु
		portsc = पढ़ोl(rhub->ports[i]->addr);
		अगर (portsc & PORT_DEV_REMOVE)
			port_removable |= 1 << (i + 1);
	पूर्ण

	desc->u.ss.DeviceRemovable = cpu_to_le16(port_removable);
पूर्ण

अटल व्योम xhci_hub_descriptor(काष्ठा usb_hcd *hcd, काष्ठा xhci_hcd *xhci,
		काष्ठा usb_hub_descriptor *desc)
अणु

	अगर (hcd->speed >= HCD_USB3)
		xhci_usb3_hub_descriptor(hcd, xhci, desc);
	अन्यथा
		xhci_usb2_hub_descriptor(hcd, xhci, desc);

पूर्ण

अटल अचिन्हित पूर्णांक xhci_port_speed(अचिन्हित पूर्णांक port_status)
अणु
	अगर (DEV_LOWSPEED(port_status))
		वापस USB_PORT_STAT_LOW_SPEED;
	अगर (DEV_HIGHSPEED(port_status))
		वापस USB_PORT_STAT_HIGH_SPEED;
	/*
	 * FIXME: Yes, we should check क्रम full speed, but the core uses that as
	 * a शेष in portspeed() in usb/core/hub.c (which is the only place
	 * USB_PORT_STAT_*_SPEED is used).
	 */
	वापस 0;
पूर्ण

/*
 * These bits are Read Only (RO) and should be saved and written to the
 * रेजिस्टरs: 0, 3, 10:13, 30
 * connect status, over-current status, port speed, and device removable.
 * connect status and port speed are also sticky - meaning they're in
 * the AUX well and they aren't changed by a hot, warm, or cold reset.
 */
#घोषणा	XHCI_PORT_RO	((1<<0) | (1<<3) | (0xf<<10) | (1<<30))
/*
 * These bits are RW; writing a 0 clears the bit, writing a 1 sets the bit:
 * bits 5:8, 9, 14:15, 25:27
 * link state, port घातer, port indicator state, "wake on" enable state
 */
#घोषणा XHCI_PORT_RWS	((0xf<<5) | (1<<9) | (0x3<<14) | (0x7<<25))
/*
 * These bits are RW; writing a 1 sets the bit, writing a 0 has no effect:
 * bit 4 (port reset)
 */
#घोषणा	XHCI_PORT_RW1S	((1<<4))
/*
 * These bits are RW; writing a 1 clears the bit, writing a 0 has no effect:
 * bits 1, 17, 18, 19, 20, 21, 22, 23
 * port enable/disable, and
 * change bits: connect, PED, warm port reset changed (reserved zero क्रम USB 2.0 ports),
 * over-current, reset, link state, and L1 change
 */
#घोषणा XHCI_PORT_RW1CS	((1<<1) | (0x7f<<17))
/*
 * Bit 16 is RW, and writing a '1' to it causes the link state control to be
 * latched in
 */
#घोषणा	XHCI_PORT_RW	((1<<16))
/*
 * These bits are Reserved Zero (RsvdZ) and zero should be written to them:
 * bits 2, 24, 28:31
 */
#घोषणा	XHCI_PORT_RZ	((1<<2) | (1<<24) | (0xf<<28))

/*
 * Given a port state, this function वापसs a value that would result in the
 * port being in the same state, अगर the value was written to the port status
 * control रेजिस्टर.
 * Save Read Only (RO) bits and save पढ़ो/ग_लिखो bits where
 * writing a 0 clears the bit and writing a 1 sets the bit (RWS).
 * For all other types (RW1S, RW1CS, RW, and RZ), writing a '0' has no effect.
 */
u32 xhci_port_state_to_neutral(u32 state)
अणु
	/* Save पढ़ो-only status and port state */
	वापस (state & XHCI_PORT_RO) | (state & XHCI_PORT_RWS);
पूर्ण

/*
 * find slot id based on port number.
 * @port: The one-based port number from one of the two split roothubs.
 */
पूर्णांक xhci_find_slot_id_by_port(काष्ठा usb_hcd *hcd, काष्ठा xhci_hcd *xhci,
		u16 port)
अणु
	पूर्णांक slot_id;
	पूर्णांक i;
	क्रमागत usb_device_speed speed;

	slot_id = 0;
	क्रम (i = 0; i < MAX_HC_SLOTS; i++) अणु
		अगर (!xhci->devs[i] || !xhci->devs[i]->udev)
			जारी;
		speed = xhci->devs[i]->udev->speed;
		अगर (((speed >= USB_SPEED_SUPER) == (hcd->speed >= HCD_USB3))
				&& xhci->devs[i]->fake_port == port) अणु
			slot_id = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस slot_id;
पूर्ण

/*
 * Stop device
 * It issues stop endpoपूर्णांक command क्रम EP 0 to 30. And रुको the last command
 * to complete.
 * suspend will set to 1, अगर suspend bit need to set in command.
 */
अटल पूर्णांक xhci_stop_device(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id, पूर्णांक suspend)
अणु
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_command *cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	पूर्णांक i;

	ret = 0;
	virt_dev = xhci->devs[slot_id];
	अगर (!virt_dev)
		वापस -ENODEV;

	trace_xhci_stop_device(virt_dev);

	cmd = xhci_alloc_command(xhci, true, GFP_NOIO);
	अगर (!cmd)
		वापस -ENOMEM;

	spin_lock_irqsave(&xhci->lock, flags);
	क्रम (i = LAST_EP_INDEX; i > 0; i--) अणु
		अगर (virt_dev->eps[i].ring && virt_dev->eps[i].ring->dequeue) अणु
			काष्ठा xhci_ep_ctx *ep_ctx;
			काष्ठा xhci_command *command;

			ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->out_ctx, i);

			/* Check ep is running, required by AMD SNPS 3.1 xHC */
			अगर (GET_EP_CTX_STATE(ep_ctx) != EP_STATE_RUNNING)
				जारी;

			command = xhci_alloc_command(xhci, false, GFP_NOWAIT);
			अगर (!command) अणु
				spin_unlock_irqrestore(&xhci->lock, flags);
				ret = -ENOMEM;
				जाओ cmd_cleanup;
			पूर्ण

			ret = xhci_queue_stop_endpoपूर्णांक(xhci, command, slot_id,
						       i, suspend);
			अगर (ret) अणु
				spin_unlock_irqrestore(&xhci->lock, flags);
				xhci_मुक्त_command(xhci, command);
				जाओ cmd_cleanup;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = xhci_queue_stop_endpoपूर्णांक(xhci, cmd, slot_id, 0, suspend);
	अगर (ret) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		जाओ cmd_cleanup;
	पूर्ण

	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Wait क्रम last stop endpoपूर्णांक command to finish */
	रुको_क्रम_completion(cmd->completion);

	अगर (cmd->status == COMP_COMMAND_ABORTED ||
	    cmd->status == COMP_COMMAND_RING_STOPPED) अणु
		xhci_warn(xhci, "Timeout while waiting for stop endpoint command\n");
		ret = -ETIME;
	पूर्ण

cmd_cleanup:
	xhci_मुक्त_command(xhci, cmd);
	वापस ret;
पूर्ण

/*
 * Ring device, it rings the all करोorbells unconditionally.
 */
व्योम xhci_ring_device(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	पूर्णांक i, s;
	काष्ठा xhci_virt_ep *ep;

	क्रम (i = 0; i < LAST_EP_INDEX + 1; i++) अणु
		ep = &xhci->devs[slot_id]->eps[i];

		अगर (ep->ep_state & EP_HAS_STREAMS) अणु
			क्रम (s = 1; s < ep->stream_info->num_streams; s++)
				xhci_ring_ep_करोorbell(xhci, slot_id, i, s);
		पूर्ण अन्यथा अगर (ep->ring && ep->ring->dequeue) अणु
			xhci_ring_ep_करोorbell(xhci, slot_id, i, 0);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल व्योम xhci_disable_port(काष्ठा usb_hcd *hcd, काष्ठा xhci_hcd *xhci,
		u16 wIndex, __le32 __iomem *addr, u32 port_status)
अणु
	/* Don't allow the USB core to disable SuperSpeed ports. */
	अगर (hcd->speed >= HCD_USB3) अणु
		xhci_dbg(xhci, "Ignoring request to disable "
				"SuperSpeed port.\n");
		वापस;
	पूर्ण

	अगर (xhci->quirks & XHCI_BROKEN_PORT_PED) अणु
		xhci_dbg(xhci,
			 "Broken Port Enabled/Disabled, ignoring port disable request.\n");
		वापस;
	पूर्ण

	/* Write 1 to disable the port */
	ग_लिखोl(port_status | PORT_PE, addr);
	port_status = पढ़ोl(addr);
	xhci_dbg(xhci, "disable port %d-%d, portsc: 0x%x\n",
		 hcd->self.busnum, wIndex + 1, port_status);
पूर्ण

अटल व्योम xhci_clear_port_change_bit(काष्ठा xhci_hcd *xhci, u16 wValue,
		u16 wIndex, __le32 __iomem *addr, u32 port_status)
अणु
	अक्षर *port_change_bit;
	u32 status;

	चयन (wValue) अणु
	हाल USB_PORT_FEAT_C_RESET:
		status = PORT_RC;
		port_change_bit = "reset";
		अवरोध;
	हाल USB_PORT_FEAT_C_BH_PORT_RESET:
		status = PORT_WRC;
		port_change_bit = "warm(BH) reset";
		अवरोध;
	हाल USB_PORT_FEAT_C_CONNECTION:
		status = PORT_CSC;
		port_change_bit = "connect";
		अवरोध;
	हाल USB_PORT_FEAT_C_OVER_CURRENT:
		status = PORT_OCC;
		port_change_bit = "over-current";
		अवरोध;
	हाल USB_PORT_FEAT_C_ENABLE:
		status = PORT_PEC;
		port_change_bit = "enable/disable";
		अवरोध;
	हाल USB_PORT_FEAT_C_SUSPEND:
		status = PORT_PLC;
		port_change_bit = "suspend/resume";
		अवरोध;
	हाल USB_PORT_FEAT_C_PORT_LINK_STATE:
		status = PORT_PLC;
		port_change_bit = "link state";
		अवरोध;
	हाल USB_PORT_FEAT_C_PORT_CONFIG_ERROR:
		status = PORT_CEC;
		port_change_bit = "config error";
		अवरोध;
	शेष:
		/* Should never happen */
		वापस;
	पूर्ण
	/* Change bits are all ग_लिखो 1 to clear */
	ग_लिखोl(port_status | status, addr);
	port_status = पढ़ोl(addr);

	xhci_dbg(xhci, "clear port%d %s change, portsc: 0x%x\n",
		 wIndex + 1, port_change_bit, port_status);
पूर्ण

काष्ठा xhci_hub *xhci_get_rhub(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);

	अगर (hcd->speed >= HCD_USB3)
		वापस &xhci->usb3_rhub;
	वापस &xhci->usb2_rhub;
पूर्ण

/*
 * xhci_set_port_घातer() must be called with xhci->lock held.
 * It will release and re-aquire the lock जबतक calling ACPI
 * method.
 */
अटल व्योम xhci_set_port_घातer(काष्ठा xhci_hcd *xhci, काष्ठा usb_hcd *hcd,
				u16 index, bool on, अचिन्हित दीर्घ *flags)
	__must_hold(&xhci->lock)
अणु
	काष्ठा xhci_hub *rhub;
	काष्ठा xhci_port *port;
	u32 temp;

	rhub = xhci_get_rhub(hcd);
	port = rhub->ports[index];
	temp = पढ़ोl(port->addr);

	xhci_dbg(xhci, "set port power %d-%d %s, portsc: 0x%x\n",
		 hcd->self.busnum, index + 1, on ? "ON" : "OFF", temp);

	temp = xhci_port_state_to_neutral(temp);

	अगर (on) अणु
		/* Power on */
		ग_लिखोl(temp | PORT_POWER, port->addr);
		पढ़ोl(port->addr);
	पूर्ण अन्यथा अणु
		/* Power off */
		ग_लिखोl(temp & ~PORT_POWER, port->addr);
	पूर्ण

	spin_unlock_irqrestore(&xhci->lock, *flags);
	temp = usb_acpi_घातer_manageable(hcd->self.root_hub,
					index);
	अगर (temp)
		usb_acpi_set_घातer_state(hcd->self.root_hub,
			index, on);
	spin_lock_irqsave(&xhci->lock, *flags);
पूर्ण

अटल व्योम xhci_port_set_test_mode(काष्ठा xhci_hcd *xhci,
	u16 test_mode, u16 wIndex)
अणु
	u32 temp;
	काष्ठा xhci_port *port;

	/* xhci only supports test mode क्रम usb2 ports */
	port = xhci->usb2_rhub.ports[wIndex];
	temp = पढ़ोl(port->addr + PORTPMSC);
	temp |= test_mode << PORT_TEST_MODE_SHIFT;
	ग_लिखोl(temp, port->addr + PORTPMSC);
	xhci->test_mode = test_mode;
	अगर (test_mode == USB_TEST_FORCE_ENABLE)
		xhci_start(xhci);
पूर्ण

अटल पूर्णांक xhci_enter_test_mode(काष्ठा xhci_hcd *xhci,
				u16 test_mode, u16 wIndex, अचिन्हित दीर्घ *flags)
	__must_hold(&xhci->lock)
अणु
	पूर्णांक i, retval;

	/* Disable all Device Slots */
	xhci_dbg(xhci, "Disable all slots\n");
	spin_unlock_irqrestore(&xhci->lock, *flags);
	क्रम (i = 1; i <= HCS_MAX_SLOTS(xhci->hcs_params1); i++) अणु
		अगर (!xhci->devs[i])
			जारी;

		retval = xhci_disable_slot(xhci, i);
		अगर (retval)
			xhci_err(xhci, "Failed to disable slot %d, %d. Enter test mode anyway\n",
				 i, retval);
	पूर्ण
	spin_lock_irqsave(&xhci->lock, *flags);
	/* Put all ports to the Disable state by clear PP */
	xhci_dbg(xhci, "Disable all port (PP = 0)\n");
	/* Power off USB3 ports*/
	क्रम (i = 0; i < xhci->usb3_rhub.num_ports; i++)
		xhci_set_port_घातer(xhci, xhci->shared_hcd, i, false, flags);
	/* Power off USB2 ports*/
	क्रम (i = 0; i < xhci->usb2_rhub.num_ports; i++)
		xhci_set_port_घातer(xhci, xhci->मुख्य_hcd, i, false, flags);
	/* Stop the controller */
	xhci_dbg(xhci, "Stop controller\n");
	retval = xhci_halt(xhci);
	अगर (retval)
		वापस retval;
	/* Disable runसमय PM क्रम test mode */
	pm_runसमय_क्रमbid(xhci_to_hcd(xhci)->self.controller);
	/* Set PORTPMSC.PTC field to enter selected test mode */
	/* Port is selected by wIndex. port_id = wIndex + 1 */
	xhci_dbg(xhci, "Enter Test Mode: %d, Port_id=%d\n",
					test_mode, wIndex + 1);
	xhci_port_set_test_mode(xhci, test_mode, wIndex);
	वापस retval;
पूर्ण

अटल पूर्णांक xhci_निकास_test_mode(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक retval;

	अगर (!xhci->test_mode) अणु
		xhci_err(xhci, "Not in test mode, do nothing.\n");
		वापस 0;
	पूर्ण
	अगर (xhci->test_mode == USB_TEST_FORCE_ENABLE &&
		!(xhci->xhc_state & XHCI_STATE_HALTED)) अणु
		retval = xhci_halt(xhci);
		अगर (retval)
			वापस retval;
	पूर्ण
	pm_runसमय_allow(xhci_to_hcd(xhci)->self.controller);
	xhci->test_mode = 0;
	वापस xhci_reset(xhci);
पूर्ण

व्योम xhci_set_link_state(काष्ठा xhci_hcd *xhci, काष्ठा xhci_port *port,
			 u32 link_state)
अणु
	u32 temp;
	u32 portsc;

	portsc = पढ़ोl(port->addr);
	temp = xhci_port_state_to_neutral(portsc);
	temp &= ~PORT_PLS_MASK;
	temp |= PORT_LINK_STROBE | link_state;
	ग_लिखोl(temp, port->addr);

	xhci_dbg(xhci, "Set port %d-%d link state, portsc: 0x%x, write 0x%x",
		 port->rhub->hcd->self.busnum, port->hcd_portnum + 1,
		 portsc, temp);
पूर्ण

अटल व्योम xhci_set_remote_wake_mask(काष्ठा xhci_hcd *xhci,
				      काष्ठा xhci_port *port, u16 wake_mask)
अणु
	u32 temp;

	temp = पढ़ोl(port->addr);
	temp = xhci_port_state_to_neutral(temp);

	अगर (wake_mask & USB_PORT_FEAT_REMOTE_WAKE_CONNECT)
		temp |= PORT_WKCONN_E;
	अन्यथा
		temp &= ~PORT_WKCONN_E;

	अगर (wake_mask & USB_PORT_FEAT_REMOTE_WAKE_DISCONNECT)
		temp |= PORT_WKDISC_E;
	अन्यथा
		temp &= ~PORT_WKDISC_E;

	अगर (wake_mask & USB_PORT_FEAT_REMOTE_WAKE_OVER_CURRENT)
		temp |= PORT_WKOC_E;
	अन्यथा
		temp &= ~PORT_WKOC_E;

	ग_लिखोl(temp, port->addr);
पूर्ण

/* Test and clear port RWC bit */
व्योम xhci_test_and_clear_bit(काष्ठा xhci_hcd *xhci, काष्ठा xhci_port *port,
			     u32 port_bit)
अणु
	u32 temp;

	temp = पढ़ोl(port->addr);
	अगर (temp & port_bit) अणु
		temp = xhci_port_state_to_neutral(temp);
		temp |= port_bit;
		ग_लिखोl(temp, port->addr);
	पूर्ण
पूर्ण

/* Updates Link Status क्रम super Speed port */
अटल व्योम xhci_hub_report_usb3_link_state(काष्ठा xhci_hcd *xhci,
		u32 *status, u32 status_reg)
अणु
	u32 pls = status_reg & PORT_PLS_MASK;

	/* When the CAS bit is set then warm reset
	 * should be perक्रमmed on port
	 */
	अगर (status_reg & PORT_CAS) अणु
		/* The CAS bit can be set जबतक the port is
		 * in any link state.
		 * Only roothubs have CAS bit, so we
		 * pretend to be in compliance mode
		 * unless we're alपढ़ोy in compliance
		 * or the inactive state.
		 */
		अगर (pls != USB_SS_PORT_LS_COMP_MOD &&
		    pls != USB_SS_PORT_LS_SS_INACTIVE) अणु
			pls = USB_SS_PORT_LS_COMP_MOD;
		पूर्ण
		/* Return also connection bit -
		 * hub state machine resets port
		 * when this bit is set.
		 */
		pls |= USB_PORT_STAT_CONNECTION;
	पूर्ण अन्यथा अणु
		/*
		 * Resume state is an xHCI पूर्णांकernal state.  Do not report it to
		 * usb core, instead, pretend to be U3, thus usb core knows
		 * it's not पढ़ोy क्रम transfer.
		 */
		अगर (pls == XDEV_RESUME) अणु
			*status |= USB_SS_PORT_LS_U3;
			वापस;
		पूर्ण

		/*
		 * If CAS bit isn't set but the Port is alपढ़ोy at
		 * Compliance Mode, fake a connection so the USB core
		 * notices the Compliance state and resets the port.
		 * This resolves an issue generated by the SN65LVPE502CP
		 * in which someबार the port enters compliance mode
		 * caused by a delay on the host-device negotiation.
		 */
		अगर ((xhci->quirks & XHCI_COMP_MODE_QUIRK) &&
				(pls == USB_SS_PORT_LS_COMP_MOD))
			pls |= USB_PORT_STAT_CONNECTION;
	पूर्ण

	/* update status field */
	*status |= pls;
पूर्ण

/*
 * Function क्रम Compliance Mode Quirk.
 *
 * This Function verअगरies अगर all xhc USB3 ports have entered U0, अगर so,
 * the compliance mode समयr is deleted. A port won't enter
 * compliance mode अगर it has previously entered U0.
 */
अटल व्योम xhci_del_comp_mod_समयr(काष्ठा xhci_hcd *xhci, u32 status,
				    u16 wIndex)
अणु
	u32 all_ports_seen_u0 = ((1 << xhci->usb3_rhub.num_ports) - 1);
	bool port_in_u0 = ((status & PORT_PLS_MASK) == XDEV_U0);

	अगर (!(xhci->quirks & XHCI_COMP_MODE_QUIRK))
		वापस;

	अगर ((xhci->port_status_u0 != all_ports_seen_u0) && port_in_u0) अणु
		xhci->port_status_u0 |= 1 << wIndex;
		अगर (xhci->port_status_u0 == all_ports_seen_u0) अणु
			del_समयr_sync(&xhci->comp_mode_recovery_समयr);
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"All USB3 ports have entered U0 already!");
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Compliance Mode Recovery Timer Deleted.");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_handle_usb2_port_link_resume(काष्ठा xhci_port *port,
					     u32 *status, u32 portsc,
					     अचिन्हित दीर्घ *flags)
अणु
	काष्ठा xhci_bus_state *bus_state;
	काष्ठा xhci_hcd	*xhci;
	काष्ठा usb_hcd *hcd;
	पूर्णांक slot_id;
	u32 wIndex;

	hcd = port->rhub->hcd;
	bus_state = &port->rhub->bus_state;
	xhci = hcd_to_xhci(hcd);
	wIndex = port->hcd_portnum;

	अगर ((portsc & PORT_RESET) || !(portsc & PORT_PE)) अणु
		*status = 0xffffffff;
		वापस -EINVAL;
	पूर्ण
	/* did port event handler alपढ़ोy start resume timing? */
	अगर (!bus_state->resume_करोne[wIndex]) अणु
		/* If not, maybe we are in a host initated resume? */
		अगर (test_bit(wIndex, &bus_state->resuming_ports)) अणु
			/* Host initated resume करोesn't समय the resume
			 * संकेतling using resume_करोne[].
			 * It manually sets RESUME state, sleeps 20ms
			 * and sets U0 state. This should probably be
			 * changed, but not right now.
			 */
		पूर्ण अन्यथा अणु
			/* port resume was discovered now and here,
			 * start resume timing
			 */
			अचिन्हित दीर्घ समयout = jअगरfies +
				msecs_to_jअगरfies(USB_RESUME_TIMEOUT);

			set_bit(wIndex, &bus_state->resuming_ports);
			bus_state->resume_करोne[wIndex] = समयout;
			mod_समयr(&hcd->rh_समयr, समयout);
			usb_hcd_start_port_resume(&hcd->self, wIndex);
		पूर्ण
	/* Has resume been संकेतled क्रम USB_RESUME_TIME yet? */
	पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies, bus_state->resume_करोne[wIndex])) अणु
		पूर्णांक समय_left;

		xhci_dbg(xhci, "resume USB2 port %d-%d\n",
			 hcd->self.busnum, wIndex + 1);

		bus_state->resume_करोne[wIndex] = 0;
		clear_bit(wIndex, &bus_state->resuming_ports);

		set_bit(wIndex, &bus_state->rनिकास_ports);

		xhci_test_and_clear_bit(xhci, port, PORT_PLC);
		xhci_set_link_state(xhci, port, XDEV_U0);

		spin_unlock_irqrestore(&xhci->lock, *flags);
		समय_left = रुको_क्रम_completion_समयout(
			&bus_state->rनिकास_करोne[wIndex],
			msecs_to_jअगरfies(XHCI_MAX_REXIT_TIMEOUT_MS));
		spin_lock_irqsave(&xhci->lock, *flags);

		अगर (समय_left) अणु
			slot_id = xhci_find_slot_id_by_port(hcd, xhci,
							    wIndex + 1);
			अगर (!slot_id) अणु
				xhci_dbg(xhci, "slot_id is zero\n");
				*status = 0xffffffff;
				वापस -ENODEV;
			पूर्ण
			xhci_ring_device(xhci, slot_id);
		पूर्ण अन्यथा अणु
			पूर्णांक port_status = पढ़ोl(port->addr);

			xhci_warn(xhci, "Port resume timed out, port %d-%d: 0x%x\n",
				  hcd->self.busnum, wIndex + 1, port_status);
			*status |= USB_PORT_STAT_SUSPEND;
			clear_bit(wIndex, &bus_state->rनिकास_ports);
		पूर्ण

		usb_hcd_end_port_resume(&hcd->self, wIndex);
		bus_state->port_c_suspend |= 1 << wIndex;
		bus_state->suspended_ports &= ~(1 << wIndex);
	पूर्ण अन्यथा अणु
		/*
		 * The resume has been संकेतing क्रम less than
		 * USB_RESUME_TIME. Report the port status as SUSPEND,
		 * let the usbcore check port status again and clear
		 * resume संकेतing later.
		 */
		*status |= USB_PORT_STAT_SUSPEND;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 xhci_get_ext_port_status(u32 raw_port_status, u32 port_li)
अणु
	u32 ext_stat = 0;
	पूर्णांक speed_id;

	/* only support rx and tx lane counts of 1 in usb3.1 spec */
	speed_id = DEV_PORT_SPEED(raw_port_status);
	ext_stat |= speed_id;		/* bits 3:0, RX speed id */
	ext_stat |= speed_id << 4;	/* bits 7:4, TX speed id */

	ext_stat |= PORT_RX_LANES(port_li) << 8;  /* bits 11:8 Rx lane count */
	ext_stat |= PORT_TX_LANES(port_li) << 12; /* bits 15:12 Tx lane count */

	वापस ext_stat;
पूर्ण

अटल व्योम xhci_get_usb3_port_status(काष्ठा xhci_port *port, u32 *status,
				      u32 portsc)
अणु
	काष्ठा xhci_bus_state *bus_state;
	काष्ठा xhci_hcd	*xhci;
	काष्ठा usb_hcd *hcd;
	u32 link_state;
	u32 portnum;

	bus_state = &port->rhub->bus_state;
	xhci = hcd_to_xhci(port->rhub->hcd);
	hcd = port->rhub->hcd;
	link_state = portsc & PORT_PLS_MASK;
	portnum = port->hcd_portnum;

	/* USB3 specअगरic wPortChange bits
	 *
	 * Port link change with port in resume state should not be
	 * reported to usbcore, as this is an पूर्णांकernal state to be
	 * handled by xhci driver. Reporting PLC to usbcore may
	 * cause usbcore clearing PLC first and port change event
	 * irq won't be generated.
	 */

	अगर (portsc & PORT_PLC && (link_state != XDEV_RESUME))
		*status |= USB_PORT_STAT_C_LINK_STATE << 16;
	अगर (portsc & PORT_WRC)
		*status |= USB_PORT_STAT_C_BH_RESET << 16;
	अगर (portsc & PORT_CEC)
		*status |= USB_PORT_STAT_C_CONFIG_ERROR << 16;

	/* USB3 specअगरic wPortStatus bits */
	अगर (portsc & PORT_POWER) अणु
		*status |= USB_SS_PORT_STAT_POWER;
		/* link state handling */
		अगर (link_state == XDEV_U0)
			bus_state->suspended_ports &= ~(1 << portnum);
	पूर्ण

	/* remote wake resume संकेतing complete */
	अगर (bus_state->port_remote_wakeup & (1 << portnum) &&
	    link_state != XDEV_RESUME &&
	    link_state != XDEV_RECOVERY) अणु
		bus_state->port_remote_wakeup &= ~(1 << portnum);
		usb_hcd_end_port_resume(&hcd->self, portnum);
	पूर्ण

	xhci_hub_report_usb3_link_state(xhci, status, portsc);
	xhci_del_comp_mod_समयr(xhci, portsc, portnum);
पूर्ण

अटल व्योम xhci_get_usb2_port_status(काष्ठा xhci_port *port, u32 *status,
				      u32 portsc, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा xhci_bus_state *bus_state;
	u32 link_state;
	u32 portnum;
	पूर्णांक ret;

	bus_state = &port->rhub->bus_state;
	link_state = portsc & PORT_PLS_MASK;
	portnum = port->hcd_portnum;

	/* USB2 wPortStatus bits */
	अगर (portsc & PORT_POWER) अणु
		*status |= USB_PORT_STAT_POWER;

		/* link state is only valid अगर port is घातered */
		अगर (link_state == XDEV_U3)
			*status |= USB_PORT_STAT_SUSPEND;
		अगर (link_state == XDEV_U2)
			*status |= USB_PORT_STAT_L1;
		अगर (link_state == XDEV_U0) अणु
			bus_state->resume_करोne[portnum] = 0;
			clear_bit(portnum, &bus_state->resuming_ports);
			अगर (bus_state->suspended_ports & (1 << portnum)) अणु
				bus_state->suspended_ports &= ~(1 << portnum);
				bus_state->port_c_suspend |= 1 << portnum;
			पूर्ण
		पूर्ण
		अगर (link_state == XDEV_RESUME) अणु
			ret = xhci_handle_usb2_port_link_resume(port, status,
								portsc, flags);
			अगर (ret)
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Converts a raw xHCI port status पूर्णांकo the क्रमmat that बाह्यal USB 2.0 or USB
 * 3.0 hubs use.
 *
 * Possible side effects:
 *  - Mark a port as being करोne with device resume,
 *    and ring the endpoपूर्णांक करोorbells.
 *  - Stop the Synopsys redriver Compliance Mode polling.
 *  - Drop and reacquire the xHCI lock, in order to रुको क्रम port resume.
 */
अटल u32 xhci_get_port_status(काष्ठा usb_hcd *hcd,
		काष्ठा xhci_bus_state *bus_state,
	u16 wIndex, u32 raw_port_status,
		अचिन्हित दीर्घ *flags)
	__releases(&xhci->lock)
	__acquires(&xhci->lock)
अणु
	u32 status = 0;
	काष्ठा xhci_hub *rhub;
	काष्ठा xhci_port *port;

	rhub = xhci_get_rhub(hcd);
	port = rhub->ports[wIndex];

	/* common wPortChange bits */
	अगर (raw_port_status & PORT_CSC)
		status |= USB_PORT_STAT_C_CONNECTION << 16;
	अगर (raw_port_status & PORT_PEC)
		status |= USB_PORT_STAT_C_ENABLE << 16;
	अगर ((raw_port_status & PORT_OCC))
		status |= USB_PORT_STAT_C_OVERCURRENT << 16;
	अगर ((raw_port_status & PORT_RC))
		status |= USB_PORT_STAT_C_RESET << 16;

	/* common wPortStatus bits */
	अगर (raw_port_status & PORT_CONNECT) अणु
		status |= USB_PORT_STAT_CONNECTION;
		status |= xhci_port_speed(raw_port_status);
	पूर्ण
	अगर (raw_port_status & PORT_PE)
		status |= USB_PORT_STAT_ENABLE;
	अगर (raw_port_status & PORT_OC)
		status |= USB_PORT_STAT_OVERCURRENT;
	अगर (raw_port_status & PORT_RESET)
		status |= USB_PORT_STAT_RESET;

	/* USB2 and USB3 specअगरic bits, including Port Link State */
	अगर (hcd->speed >= HCD_USB3)
		xhci_get_usb3_port_status(port, &status, raw_port_status);
	अन्यथा
		xhci_get_usb2_port_status(port, &status, raw_port_status,
					  flags);
	/*
	 * Clear stale usb2 resume संकेतling variables in हाल port changed
	 * state during resume संकेतling. For example on error
	 */
	अगर ((bus_state->resume_करोne[wIndex] ||
	     test_bit(wIndex, &bus_state->resuming_ports)) &&
	    (raw_port_status & PORT_PLS_MASK) != XDEV_U3 &&
	    (raw_port_status & PORT_PLS_MASK) != XDEV_RESUME) अणु
		bus_state->resume_करोne[wIndex] = 0;
		clear_bit(wIndex, &bus_state->resuming_ports);
		usb_hcd_end_port_resume(&hcd->self, wIndex);
	पूर्ण

	अगर (bus_state->port_c_suspend & (1 << wIndex))
		status |= USB_PORT_STAT_C_SUSPEND << 16;

	वापस status;
पूर्ण

पूर्णांक xhci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
		u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	पूर्णांक max_ports;
	अचिन्हित दीर्घ flags;
	u32 temp, status;
	पूर्णांक retval = 0;
	पूर्णांक slot_id;
	काष्ठा xhci_bus_state *bus_state;
	u16 link_state = 0;
	u16 wake_mask = 0;
	u16 समयout = 0;
	u16 test_mode = 0;
	काष्ठा xhci_hub *rhub;
	काष्ठा xhci_port **ports;

	rhub = xhci_get_rhub(hcd);
	ports = rhub->ports;
	max_ports = rhub->num_ports;
	bus_state = &rhub->bus_state;

	spin_lock_irqsave(&xhci->lock, flags);
	चयन (typeReq) अणु
	हाल GetHubStatus:
		/* No घातer source, over-current reported per port */
		स_रखो(buf, 0, 4);
		अवरोध;
	हाल GetHubDescriptor:
		/* Check to make sure userspace is asking क्रम the USB 3.0 hub
		 * descriptor क्रम the USB 3.0 roothub.  If not, we stall the
		 * endpoपूर्णांक, like बाह्यal hubs करो.
		 */
		अगर (hcd->speed >= HCD_USB3 &&
				(wLength < USB_DT_SS_HUB_SIZE ||
				 wValue != (USB_DT_SS_HUB << 8))) अणु
			xhci_dbg(xhci, "Wrong hub descriptor type for "
					"USB 3.0 roothub.\n");
			जाओ error;
		पूर्ण
		xhci_hub_descriptor(hcd, xhci,
				(काष्ठा usb_hub_descriptor *) buf);
		अवरोध;
	हाल DeviceRequest | USB_REQ_GET_DESCRIPTOR:
		अगर ((wValue & 0xff00) != (USB_DT_BOS << 8))
			जाओ error;

		अगर (hcd->speed < HCD_USB3)
			जाओ error;

		retval = xhci_create_usb3x_bos_desc(xhci, buf, wLength);
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस retval;
	हाल GetPortStatus:
		अगर (!wIndex || wIndex > max_ports)
			जाओ error;
		wIndex--;
		temp = पढ़ोl(ports[wIndex]->addr);
		अगर (temp == ~(u32)0) अणु
			xhci_hc_died(xhci);
			retval = -ENODEV;
			अवरोध;
		पूर्ण
		trace_xhci_get_port_status(wIndex, temp);
		status = xhci_get_port_status(hcd, bus_state, wIndex, temp,
					      &flags);
		अगर (status == 0xffffffff)
			जाओ error;

		xhci_dbg(xhci, "Get port status %d-%d read: 0x%x, return 0x%x",
			 hcd->self.busnum, wIndex + 1, temp, status);

		put_unaligned(cpu_to_le32(status), (__le32 *) buf);
		/* अगर USB 3.1 extended port status वापस additional 4 bytes */
		अगर (wValue == 0x02) अणु
			u32 port_li;

			अगर (hcd->speed < HCD_USB31 || wLength != 8) अणु
				xhci_err(xhci, "get ext port status invalid parameter\n");
				retval = -EINVAL;
				अवरोध;
			पूर्ण
			port_li = पढ़ोl(ports[wIndex]->addr + PORTLI);
			status = xhci_get_ext_port_status(temp, port_li);
			put_unaligned_le32(status, &buf[4]);
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		अगर (wValue == USB_PORT_FEAT_LINK_STATE)
			link_state = (wIndex & 0xff00) >> 3;
		अगर (wValue == USB_PORT_FEAT_REMOTE_WAKE_MASK)
			wake_mask = wIndex & 0xff00;
		अगर (wValue == USB_PORT_FEAT_TEST)
			test_mode = (wIndex & 0xff00) >> 8;
		/* The MSB of wIndex is the U1/U2 समयout */
		समयout = (wIndex & 0xff00) >> 8;
		wIndex &= 0xff;
		अगर (!wIndex || wIndex > max_ports)
			जाओ error;
		wIndex--;
		temp = पढ़ोl(ports[wIndex]->addr);
		अगर (temp == ~(u32)0) अणु
			xhci_hc_died(xhci);
			retval = -ENODEV;
			अवरोध;
		पूर्ण
		temp = xhci_port_state_to_neutral(temp);
		/* FIXME: What new port features करो we need to support? */
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			temp = पढ़ोl(ports[wIndex]->addr);
			अगर ((temp & PORT_PLS_MASK) != XDEV_U0) अणु
				/* Resume the port to U0 first */
				xhci_set_link_state(xhci, ports[wIndex],
							XDEV_U0);
				spin_unlock_irqrestore(&xhci->lock, flags);
				msleep(10);
				spin_lock_irqsave(&xhci->lock, flags);
			पूर्ण
			/* In spec software should not attempt to suspend
			 * a port unless the port reports that it is in the
			 * enabled (PED = ै 1ै ,PLS < ै 3ै ) state.
			 */
			temp = पढ़ोl(ports[wIndex]->addr);
			अगर ((temp & PORT_PE) == 0 || (temp & PORT_RESET)
				|| (temp & PORT_PLS_MASK) >= XDEV_U3) अणु
				xhci_warn(xhci, "USB core suspending port %d-%d not in U0/U1/U2\n",
					  hcd->self.busnum, wIndex + 1);
				जाओ error;
			पूर्ण

			slot_id = xhci_find_slot_id_by_port(hcd, xhci,
					wIndex + 1);
			अगर (!slot_id) अणु
				xhci_warn(xhci, "slot_id is zero\n");
				जाओ error;
			पूर्ण
			/* unlock to execute stop endpoपूर्णांक commands */
			spin_unlock_irqrestore(&xhci->lock, flags);
			xhci_stop_device(xhci, slot_id, 1);
			spin_lock_irqsave(&xhci->lock, flags);

			xhci_set_link_state(xhci, ports[wIndex], XDEV_U3);

			spin_unlock_irqrestore(&xhci->lock, flags);
			msleep(10); /* रुको device to enter */
			spin_lock_irqsave(&xhci->lock, flags);

			temp = पढ़ोl(ports[wIndex]->addr);
			bus_state->suspended_ports |= 1 << wIndex;
			अवरोध;
		हाल USB_PORT_FEAT_LINK_STATE:
			temp = पढ़ोl(ports[wIndex]->addr);
			/* Disable port */
			अगर (link_state == USB_SS_PORT_LS_SS_DISABLED) अणु
				xhci_dbg(xhci, "Disable port %d-%d\n",
					 hcd->self.busnum, wIndex + 1);
				temp = xhci_port_state_to_neutral(temp);
				/*
				 * Clear all change bits, so that we get a new
				 * connection event.
				 */
				temp |= PORT_CSC | PORT_PEC | PORT_WRC |
					PORT_OCC | PORT_RC | PORT_PLC |
					PORT_CEC;
				ग_लिखोl(temp | PORT_PE, ports[wIndex]->addr);
				temp = पढ़ोl(ports[wIndex]->addr);
				अवरोध;
			पूर्ण

			/* Put link in RxDetect (enable port) */
			अगर (link_state == USB_SS_PORT_LS_RX_DETECT) अणु
				xhci_dbg(xhci, "Enable port %d-%d\n",
					 hcd->self.busnum, wIndex + 1);
				xhci_set_link_state(xhci, ports[wIndex],
							link_state);
				temp = पढ़ोl(ports[wIndex]->addr);
				अवरोध;
			पूर्ण

			/*
			 * For xHCI 1.1 according to section 4.19.1.2.4.1 a
			 * root hub port's transition to compliance mode upon
			 * detecting LFPS समयout may be controlled by an
			 * Compliance Transition Enabled (CTE) flag (not
			 * software visible). This flag is set by writing 0xA
			 * to PORTSC PLS field which will allow transition to
			 * compliance mode the next समय LFPS समयout is
			 * encountered. A warm reset will clear it.
			 *
			 * The CTE flag is only supported अगर the HCCPARAMS2 CTC
			 * flag is set, otherwise, the compliance substate is
			 * स्वतःmatically entered as on 1.0 and prior.
			 */
			अगर (link_state == USB_SS_PORT_LS_COMP_MOD) अणु
				अगर (!HCC2_CTC(xhci->hcc_params2)) अणु
					xhci_dbg(xhci, "CTC flag is 0, port already supports entering compliance mode\n");
					अवरोध;
				पूर्ण

				अगर ((temp & PORT_CONNECT)) अणु
					xhci_warn(xhci, "Can't set compliance mode when port is connected\n");
					जाओ error;
				पूर्ण

				xhci_dbg(xhci, "Enable compliance mode transition for port %d-%d\n",
					 hcd->self.busnum, wIndex + 1);
				xhci_set_link_state(xhci, ports[wIndex],
						link_state);

				temp = पढ़ोl(ports[wIndex]->addr);
				अवरोध;
			पूर्ण
			/* Port must be enabled */
			अगर (!(temp & PORT_PE)) अणु
				retval = -ENODEV;
				अवरोध;
			पूर्ण
			/* Can't set port link state above '3' (U3) */
			अगर (link_state > USB_SS_PORT_LS_U3) अणु
				xhci_warn(xhci, "Cannot set port %d-%d link state %d\n",
					  hcd->self.busnum, wIndex + 1,
					  link_state);
				जाओ error;
			पूर्ण

			/*
			 * set link to U0, steps depend on current link state.
			 * U3: set link to U0 and रुको क्रम u3निकास completion.
			 * U1/U2:  no PLC complete event, only set link to U0.
			 * Resume/Recovery: device initiated U0, only रुको क्रम
			 * completion
			 */
			अगर (link_state == USB_SS_PORT_LS_U0) अणु
				u32 pls = temp & PORT_PLS_MASK;
				bool रुको_u0 = false;

				/* alपढ़ोy in U0 */
				अगर (pls == XDEV_U0)
					अवरोध;
				अगर (pls == XDEV_U3 ||
				    pls == XDEV_RESUME ||
				    pls == XDEV_RECOVERY) अणु
					रुको_u0 = true;
					reinit_completion(&bus_state->u3निकास_करोne[wIndex]);
				पूर्ण
				अगर (pls <= XDEV_U3) /* U1, U2, U3 */
					xhci_set_link_state(xhci, ports[wIndex],
							    USB_SS_PORT_LS_U0);
				अगर (!रुको_u0) अणु
					अगर (pls > XDEV_U3)
						जाओ error;
					अवरोध;
				पूर्ण
				spin_unlock_irqrestore(&xhci->lock, flags);
				अगर (!रुको_क्रम_completion_समयout(&bus_state->u3निकास_करोne[wIndex],
								 msecs_to_jअगरfies(100)))
					xhci_dbg(xhci, "missing U0 port change event for port %d-%d\n",
						 hcd->self.busnum, wIndex + 1);
				spin_lock_irqsave(&xhci->lock, flags);
				temp = पढ़ोl(ports[wIndex]->addr);
				अवरोध;
			पूर्ण

			अगर (link_state == USB_SS_PORT_LS_U3) अणु
				पूर्णांक retries = 16;
				slot_id = xhci_find_slot_id_by_port(hcd, xhci,
						wIndex + 1);
				अगर (slot_id) अणु
					/* unlock to execute stop endpoपूर्णांक
					 * commands */
					spin_unlock_irqrestore(&xhci->lock,
								flags);
					xhci_stop_device(xhci, slot_id, 1);
					spin_lock_irqsave(&xhci->lock, flags);
				पूर्ण
				xhci_set_link_state(xhci, ports[wIndex], USB_SS_PORT_LS_U3);
				spin_unlock_irqrestore(&xhci->lock, flags);
				जबतक (retries--) अणु
					usleep_range(4000, 8000);
					temp = पढ़ोl(ports[wIndex]->addr);
					अगर ((temp & PORT_PLS_MASK) == XDEV_U3)
						अवरोध;
				पूर्ण
				spin_lock_irqsave(&xhci->lock, flags);
				temp = पढ़ोl(ports[wIndex]->addr);
				bus_state->suspended_ports |= 1 << wIndex;
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			/*
			 * Turn on ports, even अगर there isn't per-port चयनing.
			 * HC will report connect events even beक्रमe this is set.
			 * However, hub_wq will ignore the roothub events until
			 * the roothub is रेजिस्टरed.
			 */
			xhci_set_port_घातer(xhci, hcd, wIndex, true, &flags);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			temp = (temp | PORT_RESET);
			ग_लिखोl(temp, ports[wIndex]->addr);

			temp = पढ़ोl(ports[wIndex]->addr);
			xhci_dbg(xhci, "set port reset, actual port %d-%d status  = 0x%x\n",
				 hcd->self.busnum, wIndex + 1, temp);
			अवरोध;
		हाल USB_PORT_FEAT_REMOTE_WAKE_MASK:
			xhci_set_remote_wake_mask(xhci, ports[wIndex],
						  wake_mask);
			temp = पढ़ोl(ports[wIndex]->addr);
			xhci_dbg(xhci, "set port remote wake mask, actual port %d-%d status  = 0x%x\n",
				 hcd->self.busnum, wIndex + 1, temp);
			अवरोध;
		हाल USB_PORT_FEAT_BH_PORT_RESET:
			temp |= PORT_WR;
			ग_लिखोl(temp, ports[wIndex]->addr);
			temp = पढ़ोl(ports[wIndex]->addr);
			अवरोध;
		हाल USB_PORT_FEAT_U1_TIMEOUT:
			अगर (hcd->speed < HCD_USB3)
				जाओ error;
			temp = पढ़ोl(ports[wIndex]->addr + PORTPMSC);
			temp &= ~PORT_U1_TIMEOUT_MASK;
			temp |= PORT_U1_TIMEOUT(समयout);
			ग_लिखोl(temp, ports[wIndex]->addr + PORTPMSC);
			अवरोध;
		हाल USB_PORT_FEAT_U2_TIMEOUT:
			अगर (hcd->speed < HCD_USB3)
				जाओ error;
			temp = पढ़ोl(ports[wIndex]->addr + PORTPMSC);
			temp &= ~PORT_U2_TIMEOUT_MASK;
			temp |= PORT_U2_TIMEOUT(समयout);
			ग_लिखोl(temp, ports[wIndex]->addr + PORTPMSC);
			अवरोध;
		हाल USB_PORT_FEAT_TEST:
			/* 4.19.6 Port Test Modes (USB2 Test Mode) */
			अगर (hcd->speed != HCD_USB2)
				जाओ error;
			अगर (test_mode > USB_TEST_FORCE_ENABLE ||
			    test_mode < USB_TEST_J)
				जाओ error;
			retval = xhci_enter_test_mode(xhci, test_mode, wIndex,
						      &flags);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		/* unblock any posted ग_लिखोs */
		temp = पढ़ोl(ports[wIndex]->addr);
		अवरोध;
	हाल ClearPortFeature:
		अगर (!wIndex || wIndex > max_ports)
			जाओ error;
		wIndex--;
		temp = पढ़ोl(ports[wIndex]->addr);
		अगर (temp == ~(u32)0) अणु
			xhci_hc_died(xhci);
			retval = -ENODEV;
			अवरोध;
		पूर्ण
		/* FIXME: What new port features करो we need to support? */
		temp = xhci_port_state_to_neutral(temp);
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			temp = पढ़ोl(ports[wIndex]->addr);
			xhci_dbg(xhci, "clear USB_PORT_FEAT_SUSPEND\n");
			xhci_dbg(xhci, "PORTSC %04x\n", temp);
			अगर (temp & PORT_RESET)
				जाओ error;
			अगर ((temp & PORT_PLS_MASK) == XDEV_U3) अणु
				अगर ((temp & PORT_PE) == 0)
					जाओ error;

				set_bit(wIndex, &bus_state->resuming_ports);
				usb_hcd_start_port_resume(&hcd->self, wIndex);
				xhci_set_link_state(xhci, ports[wIndex],
						    XDEV_RESUME);
				spin_unlock_irqrestore(&xhci->lock, flags);
				msleep(USB_RESUME_TIMEOUT);
				spin_lock_irqsave(&xhci->lock, flags);
				xhci_set_link_state(xhci, ports[wIndex],
							XDEV_U0);
				clear_bit(wIndex, &bus_state->resuming_ports);
				usb_hcd_end_port_resume(&hcd->self, wIndex);
			पूर्ण
			bus_state->port_c_suspend |= 1 << wIndex;

			slot_id = xhci_find_slot_id_by_port(hcd, xhci,
					wIndex + 1);
			अगर (!slot_id) अणु
				xhci_dbg(xhci, "slot_id is zero\n");
				जाओ error;
			पूर्ण
			xhci_ring_device(xhci, slot_id);
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			bus_state->port_c_suspend &= ~(1 << wIndex);
			fallthrough;
		हाल USB_PORT_FEAT_C_RESET:
		हाल USB_PORT_FEAT_C_BH_PORT_RESET:
		हाल USB_PORT_FEAT_C_CONNECTION:
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
		हाल USB_PORT_FEAT_C_ENABLE:
		हाल USB_PORT_FEAT_C_PORT_LINK_STATE:
		हाल USB_PORT_FEAT_C_PORT_CONFIG_ERROR:
			xhci_clear_port_change_bit(xhci, wValue, wIndex,
					ports[wIndex]->addr, temp);
			अवरोध;
		हाल USB_PORT_FEAT_ENABLE:
			xhci_disable_port(hcd, xhci, wIndex,
					ports[wIndex]->addr, temp);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			xhci_set_port_घातer(xhci, hcd, wIndex, false, &flags);
			अवरोध;
		हाल USB_PORT_FEAT_TEST:
			retval = xhci_निकास_test_mode(xhci);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	शेष:
error:
		/* "stall" on error */
		retval = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस retval;
पूर्ण

/*
 * Returns 0 अगर the status hasn't changed, or the number of bytes in buf.
 * Ports are 0-indexed from the HCD poपूर्णांक of view,
 * and 1-indexed from the USB core poपूर्णांकer of view.
 *
 * Note that the status change bits will be cleared as soon as a port status
 * change event is generated, so we use the saved status from that event.
 */
पूर्णांक xhci_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	अचिन्हित दीर्घ flags;
	u32 temp, status;
	u32 mask;
	पूर्णांक i, retval;
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	पूर्णांक max_ports;
	काष्ठा xhci_bus_state *bus_state;
	bool reset_change = false;
	काष्ठा xhci_hub *rhub;
	काष्ठा xhci_port **ports;

	rhub = xhci_get_rhub(hcd);
	ports = rhub->ports;
	max_ports = rhub->num_ports;
	bus_state = &rhub->bus_state;

	/* Initial status is no changes */
	retval = (max_ports + 8) / 8;
	स_रखो(buf, 0, retval);

	/*
	 * Inक्रमm the usbcore about resume-in-progress by वापसing
	 * a non-zero value even अगर there are no status changes.
	 */
	status = bus_state->resuming_ports;

	mask = PORT_CSC | PORT_PEC | PORT_OCC | PORT_PLC | PORT_WRC | PORT_CEC;

	spin_lock_irqsave(&xhci->lock, flags);
	/* For each port, did anything change?  If so, set that bit in buf. */
	क्रम (i = 0; i < max_ports; i++) अणु
		temp = पढ़ोl(ports[i]->addr);
		अगर (temp == ~(u32)0) अणु
			xhci_hc_died(xhci);
			retval = -ENODEV;
			अवरोध;
		पूर्ण
		trace_xhci_hub_status_data(i, temp);

		अगर ((temp & mask) != 0 ||
			(bus_state->port_c_suspend & 1 << i) ||
			(bus_state->resume_करोne[i] && समय_after_eq(
			    jअगरfies, bus_state->resume_करोne[i]))) अणु
			buf[(i + 1) / 8] |= 1 << (i + 1) % 8;
			status = 1;
		पूर्ण
		अगर ((temp & PORT_RC))
			reset_change = true;
		अगर (temp & PORT_OC)
			status = 1;
	पूर्ण
	अगर (!status && !reset_change) अणु
		xhci_dbg(xhci, "%s: stopping port polling.\n", __func__);
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	पूर्ण
	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस status ? retval : 0;
पूर्ण

#अगर_घोषित CONFIG_PM

पूर्णांक xhci_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	पूर्णांक max_ports, port_index;
	काष्ठा xhci_bus_state *bus_state;
	अचिन्हित दीर्घ flags;
	काष्ठा xhci_hub *rhub;
	काष्ठा xhci_port **ports;
	u32 portsc_buf[USB_MAXCHILDREN];
	bool wake_enabled;

	rhub = xhci_get_rhub(hcd);
	ports = rhub->ports;
	max_ports = rhub->num_ports;
	bus_state = &rhub->bus_state;
	wake_enabled = hcd->self.root_hub->करो_remote_wakeup;

	spin_lock_irqsave(&xhci->lock, flags);

	अगर (wake_enabled) अणु
		अगर (bus_state->resuming_ports ||	/* USB2 */
		    bus_state->port_remote_wakeup) अणु	/* USB3 */
			spin_unlock_irqrestore(&xhci->lock, flags);
			xhci_dbg(xhci, "suspend failed because a port is resuming\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	/*
	 * Prepare ports क्रम suspend, but करोn't ग_लिखो anything beक्रमe all ports
	 * are checked and we know bus suspend can proceed
	 */
	bus_state->bus_suspended = 0;
	port_index = max_ports;
	जबतक (port_index--) अणु
		u32 t1, t2;
		पूर्णांक retries = 10;
retry:
		t1 = पढ़ोl(ports[port_index]->addr);
		t2 = xhci_port_state_to_neutral(t1);
		portsc_buf[port_index] = 0;

		/*
		 * Give a USB3 port in link training समय to finish, but करोn't
		 * prevent suspend as port might be stuck
		 */
		अगर ((hcd->speed >= HCD_USB3) && retries-- &&
		    (t1 & PORT_PLS_MASK) == XDEV_POLLING) अणु
			spin_unlock_irqrestore(&xhci->lock, flags);
			msleep(XHCI_PORT_POLLING_LFPS_TIME);
			spin_lock_irqsave(&xhci->lock, flags);
			xhci_dbg(xhci, "port %d-%d polling in bus suspend, waiting\n",
				 hcd->self.busnum, port_index + 1);
			जाओ retry;
		पूर्ण
		/* bail out अगर port detected a over-current condition */
		अगर (t1 & PORT_OC) अणु
			bus_state->bus_suspended = 0;
			spin_unlock_irqrestore(&xhci->lock, flags);
			xhci_dbg(xhci, "Bus suspend bailout, port over-current detected\n");
			वापस -EBUSY;
		पूर्ण
		/* suspend ports in U0, or bail out क्रम new connect changes */
		अगर ((t1 & PORT_PE) && (t1 & PORT_PLS_MASK) == XDEV_U0) अणु
			अगर ((t1 & PORT_CSC) && wake_enabled) अणु
				bus_state->bus_suspended = 0;
				spin_unlock_irqrestore(&xhci->lock, flags);
				xhci_dbg(xhci, "Bus suspend bailout, port connect change\n");
				वापस -EBUSY;
			पूर्ण
			xhci_dbg(xhci, "port %d-%d not suspended\n",
				 hcd->self.busnum, port_index + 1);
			t2 &= ~PORT_PLS_MASK;
			t2 |= PORT_LINK_STROBE | XDEV_U3;
			set_bit(port_index, &bus_state->bus_suspended);
		पूर्ण
		/* USB core sets remote wake mask क्रम USB 3.0 hubs,
		 * including the USB 3.0 roothub, but only अगर CONFIG_PM
		 * is enabled, so also enable remote wake here.
		 */
		अगर (wake_enabled) अणु
			अगर (t1 & PORT_CONNECT) अणु
				t2 |= PORT_WKOC_E | PORT_WKDISC_E;
				t2 &= ~PORT_WKCONN_E;
			पूर्ण अन्यथा अणु
				t2 |= PORT_WKOC_E | PORT_WKCONN_E;
				t2 &= ~PORT_WKDISC_E;
			पूर्ण

			अगर ((xhci->quirks & XHCI_U2_DISABLE_WAKE) &&
			    (hcd->speed < HCD_USB3)) अणु
				अगर (usb_amd_pt_check_port(hcd->self.controller,
							  port_index))
					t2 &= ~PORT_WAKE_BITS;
			पूर्ण
		पूर्ण अन्यथा
			t2 &= ~PORT_WAKE_BITS;

		t1 = xhci_port_state_to_neutral(t1);
		अगर (t1 != t2)
			portsc_buf[port_index] = t2;
	पूर्ण

	/* ग_लिखो port settings, stopping and suspending ports अगर needed */
	port_index = max_ports;
	जबतक (port_index--) अणु
		अगर (!portsc_buf[port_index])
			जारी;
		अगर (test_bit(port_index, &bus_state->bus_suspended)) अणु
			पूर्णांक slot_id;

			slot_id = xhci_find_slot_id_by_port(hcd, xhci,
							    port_index + 1);
			अगर (slot_id) अणु
				spin_unlock_irqrestore(&xhci->lock, flags);
				xhci_stop_device(xhci, slot_id, 1);
				spin_lock_irqsave(&xhci->lock, flags);
			पूर्ण
		पूर्ण
		ग_लिखोl(portsc_buf[port_index], ports[port_index]->addr);
	पूर्ण
	hcd->state = HC_STATE_SUSPENDED;
	bus_state->next_statechange = jअगरfies + msecs_to_jअगरfies(10);
	spin_unlock_irqrestore(&xhci->lock, flags);

	अगर (bus_state->bus_suspended)
		usleep_range(5000, 10000);

	वापस 0;
पूर्ण

/*
 * Workaround क्रम missing Cold Attach Status (CAS) अगर device re-plugged in S3.
 * warm reset a USB3 device stuck in polling or compliance mode after resume.
 * See Intel 100/c230 series PCH specअगरication update Doc #332692-006 Errata #8
 */
अटल bool xhci_port_missing_cas_quirk(काष्ठा xhci_port *port)
अणु
	u32 portsc;

	portsc = पढ़ोl(port->addr);

	/* अगर any of these are set we are not stuck */
	अगर (portsc & (PORT_CONNECT | PORT_CAS))
		वापस false;

	अगर (((portsc & PORT_PLS_MASK) != XDEV_POLLING) &&
	    ((portsc & PORT_PLS_MASK) != XDEV_COMP_MODE))
		वापस false;

	/* clear wakeup/change bits, and करो a warm port reset */
	portsc &= ~(PORT_RWC_BITS | PORT_CEC | PORT_WAKE_BITS);
	portsc |= PORT_WR;
	ग_लिखोl(portsc, port->addr);
	/* flush ग_लिखो */
	पढ़ोl(port->addr);
	वापस true;
पूर्ण

पूर्णांक xhci_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_bus_state *bus_state;
	अचिन्हित दीर्घ flags;
	पूर्णांक max_ports, port_index;
	पूर्णांक slot_id;
	पूर्णांक sret;
	u32 next_state;
	u32 temp, portsc;
	काष्ठा xhci_hub *rhub;
	काष्ठा xhci_port **ports;

	rhub = xhci_get_rhub(hcd);
	ports = rhub->ports;
	max_ports = rhub->num_ports;
	bus_state = &rhub->bus_state;

	अगर (समय_beक्रमe(jअगरfies, bus_state->next_statechange))
		msleep(5);

	spin_lock_irqsave(&xhci->lock, flags);
	अगर (!HCD_HW_ACCESSIBLE(hcd)) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस -ESHUTDOWN;
	पूर्ण

	/* delay the irqs */
	temp = पढ़ोl(&xhci->op_regs->command);
	temp &= ~CMD_EIE;
	ग_लिखोl(temp, &xhci->op_regs->command);

	/* bus specअगरic resume क्रम ports we suspended at bus_suspend */
	अगर (hcd->speed >= HCD_USB3)
		next_state = XDEV_U0;
	अन्यथा
		next_state = XDEV_RESUME;

	port_index = max_ports;
	जबतक (port_index--) अणु
		portsc = पढ़ोl(ports[port_index]->addr);

		/* warm reset CAS limited ports stuck in polling/compliance */
		अगर ((xhci->quirks & XHCI_MISSING_CAS) &&
		    (hcd->speed >= HCD_USB3) &&
		    xhci_port_missing_cas_quirk(ports[port_index])) अणु
			xhci_dbg(xhci, "reset stuck port %d-%d\n",
				 hcd->self.busnum, port_index + 1);
			clear_bit(port_index, &bus_state->bus_suspended);
			जारी;
		पूर्ण
		/* resume अगर we suspended the link, and it is still suspended */
		अगर (test_bit(port_index, &bus_state->bus_suspended))
			चयन (portsc & PORT_PLS_MASK) अणु
			हाल XDEV_U3:
				portsc = xhci_port_state_to_neutral(portsc);
				portsc &= ~PORT_PLS_MASK;
				portsc |= PORT_LINK_STROBE | next_state;
				अवरोध;
			हाल XDEV_RESUME:
				/* resume alपढ़ोy initiated */
				अवरोध;
			शेष:
				/* not in a resumeable state, ignore it */
				clear_bit(port_index,
					  &bus_state->bus_suspended);
				अवरोध;
			पूर्ण
		/* disable wake क्रम all ports, ग_लिखो new link state अगर needed */
		portsc &= ~(PORT_RWC_BITS | PORT_CEC | PORT_WAKE_BITS);
		ग_लिखोl(portsc, ports[port_index]->addr);
	पूर्ण

	/* USB2 specअगरic resume संकेतing delay and U0 link state transition */
	अगर (hcd->speed < HCD_USB3) अणु
		अगर (bus_state->bus_suspended) अणु
			spin_unlock_irqrestore(&xhci->lock, flags);
			msleep(USB_RESUME_TIMEOUT);
			spin_lock_irqsave(&xhci->lock, flags);
		पूर्ण
		क्रम_each_set_bit(port_index, &bus_state->bus_suspended,
				 BITS_PER_LONG) अणु
			/* Clear PLC to poll it later क्रम U0 transition */
			xhci_test_and_clear_bit(xhci, ports[port_index],
						PORT_PLC);
			xhci_set_link_state(xhci, ports[port_index], XDEV_U0);
		पूर्ण
	पूर्ण

	/* poll क्रम U0 link state complete, both USB2 and USB3 */
	क्रम_each_set_bit(port_index, &bus_state->bus_suspended, BITS_PER_LONG) अणु
		sret = xhci_handshake(ports[port_index]->addr, PORT_PLC,
				      PORT_PLC, 10 * 1000);
		अगर (sret) अणु
			xhci_warn(xhci, "port %d-%d resume PLC timeout\n",
				  hcd->self.busnum, port_index + 1);
			जारी;
		पूर्ण
		xhci_test_and_clear_bit(xhci, ports[port_index], PORT_PLC);
		slot_id = xhci_find_slot_id_by_port(hcd, xhci, port_index + 1);
		अगर (slot_id)
			xhci_ring_device(xhci, slot_id);
	पूर्ण
	(व्योम) पढ़ोl(&xhci->op_regs->command);

	bus_state->next_statechange = jअगरfies + msecs_to_jअगरfies(5);
	/* re-enable irqs */
	temp = पढ़ोl(&xhci->op_regs->command);
	temp |= CMD_EIE;
	ग_लिखोl(temp, &xhci->op_regs->command);
	temp = पढ़ोl(&xhci->op_regs->command);

	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस 0;
पूर्ण

अचिन्हित दीर्घ xhci_get_resuming_ports(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hub *rhub = xhci_get_rhub(hcd);

	/* USB3 port wakeups are reported via usb_wakeup_notअगरication() */
	वापस rhub->bus_state.resuming_ports;	/* USB2 ports only */
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */
