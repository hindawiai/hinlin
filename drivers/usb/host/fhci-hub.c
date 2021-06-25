<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale QUICC Engine USB Host Controller Driver
 *
 * Copyright (c) Freescale Semicondutor, Inc. 2006.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) Logic Product Development, Inc. 2007
 *               Peter Barada <peterb@logicpd.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/gpपन.स>
#समावेश <soc/fsl/qe/qe.h>
#समावेश "fhci.h"

/* भव root hub specअगरic descriptor */
अटल u8 root_hub_des[] = अणु
	0x09, /* blength */
	USB_DT_HUB, /* bDescriptorType;hub-descriptor */
	0x01, /* bNbrPorts */
	HUB_CHAR_INDV_PORT_LPSM | HUB_CHAR_NO_OCPM, /* wHubCharacteristics */
	0x00, /* per-port घातer, no overcurrent */
	0x01, /* bPwrOn2pwrGood;2ms */
	0x00, /* bHubContrCurrent;0mA */
	0x00, /* DeviceRemoveable */
	0xff, /* PortPwrCtrlMask */
पूर्ण;

अटल व्योम fhci_gpio_set_value(काष्ठा fhci_hcd *fhci, पूर्णांक gpio_nr, bool on)
अणु
	पूर्णांक gpio = fhci->gpios[gpio_nr];
	bool alow = fhci->alow_gpios[gpio_nr];

	अगर (!gpio_is_valid(gpio))
		वापस;

	gpio_set_value(gpio, on ^ alow);
	mdelay(5);
पूर्ण

व्योम fhci_config_transceiver(काष्ठा fhci_hcd *fhci,
			     क्रमागत fhci_port_status status)
अणु
	fhci_dbg(fhci, "-> %s: %d\n", __func__, status);

	चयन (status) अणु
	हाल FHCI_PORT_POWER_OFF:
		fhci_gpio_set_value(fhci, GPIO_POWER, false);
		अवरोध;
	हाल FHCI_PORT_DISABLED:
	हाल FHCI_PORT_WAITING:
		fhci_gpio_set_value(fhci, GPIO_POWER, true);
		अवरोध;
	हाल FHCI_PORT_LOW:
		fhci_gpio_set_value(fhci, GPIO_SPEED, false);
		अवरोध;
	हाल FHCI_PORT_FULL:
		fhci_gpio_set_value(fhci, GPIO_SPEED, true);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	fhci_dbg(fhci, "<- %s: %d\n", __func__, status);
पूर्ण

/* disable the USB port by clearing the EN bit in the USBMOD रेजिस्टर */
व्योम fhci_port_disable(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा fhci_usb *usb = (काष्ठा fhci_usb *)fhci->usb_lld;
	क्रमागत fhci_port_status port_status;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_stop_sof_समयr(fhci);

	fhci_flush_all_transmissions(usb);

	fhci_usb_disable_पूर्णांकerrupt((काष्ठा fhci_usb *)fhci->usb_lld);
	port_status = usb->port_status;
	usb->port_status = FHCI_PORT_DISABLED;

	/* Enable IDLE since we want to know अगर something comes aदीर्घ */
	usb->saved_msk |= USB_E_IDLE_MASK;
	out_be16(&usb->fhci->regs->usb_usbmr, usb->saved_msk);

	/* check अगर during the disconnection process attached new device */
	अगर (port_status == FHCI_PORT_WAITING)
		fhci_device_connected_पूर्णांकerrupt(fhci);
	usb->vroot_hub->port.wPortStatus &= ~USB_PORT_STAT_ENABLE;
	usb->vroot_hub->port.wPortChange |= USB_PORT_STAT_C_ENABLE;
	fhci_usb_enable_पूर्णांकerrupt((काष्ठा fhci_usb *)fhci->usb_lld);

	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

/* enable the USB port by setting the EN bit in the USBMOD रेजिस्टर */
व्योम fhci_port_enable(व्योम *lld)
अणु
	काष्ठा fhci_usb *usb = (काष्ठा fhci_usb *)lld;
	काष्ठा fhci_hcd *fhci = usb->fhci;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_config_transceiver(fhci, usb->port_status);

	अगर ((usb->port_status != FHCI_PORT_FULL) &&
			(usb->port_status != FHCI_PORT_LOW))
		fhci_start_sof_समयr(fhci);

	usb->vroot_hub->port.wPortStatus |= USB_PORT_STAT_ENABLE;
	usb->vroot_hub->port.wPortChange |= USB_PORT_STAT_C_ENABLE;

	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

व्योम fhci_io_port_generate_reset(काष्ठा fhci_hcd *fhci)
अणु
	fhci_dbg(fhci, "-> %s\n", __func__);

	gpio_direction_output(fhci->gpios[GPIO_USBOE], 0);
	gpio_direction_output(fhci->gpios[GPIO_USBTP], 0);
	gpio_direction_output(fhci->gpios[GPIO_USBTN], 0);

	mdelay(5);

	qe_pin_set_dedicated(fhci->pins[PIN_USBOE]);
	qe_pin_set_dedicated(fhci->pins[PIN_USBTP]);
	qe_pin_set_dedicated(fhci->pins[PIN_USBTN]);

	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

/* generate the RESET condition on the bus */
व्योम fhci_port_reset(व्योम *lld)
अणु
	काष्ठा fhci_usb *usb = (काष्ठा fhci_usb *)lld;
	काष्ठा fhci_hcd *fhci = usb->fhci;
	u8 mode;
	u16 mask;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_stop_sof_समयr(fhci);
	/* disable the USB controller */
	mode = in_8(&fhci->regs->usb_usmod);
	out_8(&fhci->regs->usb_usmod, mode & (~USB_MODE_EN));

	/* disable idle पूर्णांकerrupts */
	mask = in_be16(&fhci->regs->usb_usbmr);
	out_be16(&fhci->regs->usb_usbmr, mask & (~USB_E_IDLE_MASK));

	fhci_io_port_generate_reset(fhci);

	/* enable पूर्णांकerrupt on this endpoपूर्णांक */
	out_be16(&fhci->regs->usb_usbmr, mask);

	/* enable the USB controller */
	mode = in_8(&fhci->regs->usb_usmod);
	out_8(&fhci->regs->usb_usmod, mode | USB_MODE_EN);
	fhci_start_sof_समयr(fhci);

	fhci_dbg(fhci, "<- %s\n", __func__);
पूर्ण

पूर्णांक fhci_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	fhci_dbg(fhci, "-> %s\n", __func__);

	spin_lock_irqsave(&fhci->lock, flags);

	अगर (fhci->vroot_hub->port.wPortChange & (USB_PORT_STAT_C_CONNECTION |
			USB_PORT_STAT_C_ENABLE | USB_PORT_STAT_C_SUSPEND |
			USB_PORT_STAT_C_RESET | USB_PORT_STAT_C_OVERCURRENT)) अणु
		*buf = 1 << 1;
		ret = 1;
		fhci_dbg(fhci, "-- %s\n", __func__);
	पूर्ण

	spin_unlock_irqrestore(&fhci->lock, flags);

	fhci_dbg(fhci, "<- %s\n", __func__);

	वापस ret;
पूर्ण

पूर्णांक fhci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
			    u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा fhci_hcd *fhci = hcd_to_fhci(hcd);
	पूर्णांक retval = 0;
	काष्ठा usb_hub_status *hub_status;
	काष्ठा usb_port_status *port_status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fhci->lock, flags);

	fhci_dbg(fhci, "-> %s\n", __func__);

	चयन (typeReq) अणु
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		fhci->vroot_hub->feature &= (1 << wValue);

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			fhci->vroot_hub->port.wPortStatus &=
			    ~USB_PORT_STAT_ENABLE;
			fhci_port_disable(fhci);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			fhci->vroot_hub->port.wPortChange &=
			    ~USB_PORT_STAT_C_ENABLE;
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			fhci->vroot_hub->port.wPortStatus &=
			    ~USB_PORT_STAT_SUSPEND;
			fhci_stop_sof_समयr(fhci);
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			fhci->vroot_hub->port.wPortChange &=
			    ~USB_PORT_STAT_C_SUSPEND;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			fhci->vroot_hub->port.wPortStatus &=
			    ~USB_PORT_STAT_POWER;
			fhci_config_transceiver(fhci, FHCI_PORT_POWER_OFF);
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			fhci->vroot_hub->port.wPortChange &=
			    ~USB_PORT_STAT_C_CONNECTION;
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			fhci->vroot_hub->port.wPortChange &=
			    ~USB_PORT_STAT_C_OVERCURRENT;
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			fhci->vroot_hub->port.wPortChange &=
			    ~USB_PORT_STAT_C_RESET;
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		स_नकल(buf, root_hub_des, माप(root_hub_des));
		अवरोध;
	हाल GetHubStatus:
		hub_status = (काष्ठा usb_hub_status *)buf;
		hub_status->wHubStatus =
		    cpu_to_le16(fhci->vroot_hub->hub.wHubStatus);
		hub_status->wHubChange =
		    cpu_to_le16(fhci->vroot_hub->hub.wHubChange);
		अवरोध;
	हाल GetPortStatus:
		port_status = (काष्ठा usb_port_status *)buf;
		port_status->wPortStatus =
		    cpu_to_le16(fhci->vroot_hub->port.wPortStatus);
		port_status->wPortChange =
		    cpu_to_le16(fhci->vroot_hub->port.wPortChange);
		अवरोध;
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		fhci->vroot_hub->feature |= (1 << wValue);

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			fhci->vroot_hub->port.wPortStatus |=
			    USB_PORT_STAT_ENABLE;
			fhci_port_enable(fhci->usb_lld);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			fhci->vroot_hub->port.wPortStatus |=
			    USB_PORT_STAT_SUSPEND;
			fhci_stop_sof_समयr(fhci);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			fhci->vroot_hub->port.wPortStatus |=
			    USB_PORT_STAT_RESET;
			fhci_port_reset(fhci->usb_lld);
			fhci->vroot_hub->port.wPortStatus |=
			    USB_PORT_STAT_ENABLE;
			fhci->vroot_hub->port.wPortStatus &=
			    ~USB_PORT_STAT_RESET;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			fhci->vroot_hub->port.wPortStatus |=
			    USB_PORT_STAT_POWER;
			fhci_config_transceiver(fhci, FHCI_PORT_WAITING);
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	शेष:
error:
		retval = -EPIPE;
	पूर्ण

	fhci_dbg(fhci, "<- %s\n", __func__);

	spin_unlock_irqrestore(&fhci->lock, flags);

	वापस retval;
पूर्ण
