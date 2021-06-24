<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2001-2002 by David Brownell
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __USB_CORE_HCD_H
#घोषणा __USB_CORE_HCD_H

#अगर_घोषित __KERNEL__

#समावेश <linux/rwsem.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/idr.h>

#घोषणा MAX_TOPO_LEVEL		6

/* This file contains declarations of usbcore पूर्णांकernals that are mostly
 * used or exposed by Host Controller Drivers.
 */

/*
 * USB Packet IDs (PIDs)
 */
#घोषणा USB_PID_EXT			0xf0	/* USB 2.0 LPM ECN */
#घोषणा USB_PID_OUT			0xe1
#घोषणा USB_PID_ACK			0xd2
#घोषणा USB_PID_DATA0			0xc3
#घोषणा USB_PID_PING			0xb4	/* USB 2.0 */
#घोषणा USB_PID_SOF			0xa5
#घोषणा USB_PID_NYET			0x96	/* USB 2.0 */
#घोषणा USB_PID_DATA2			0x87	/* USB 2.0 */
#घोषणा USB_PID_SPLIT			0x78	/* USB 2.0 */
#घोषणा USB_PID_IN			0x69
#घोषणा USB_PID_NAK			0x5a
#घोषणा USB_PID_DATA1			0x4b
#घोषणा USB_PID_PREAMBLE		0x3c	/* Token mode */
#घोषणा USB_PID_ERR			0x3c	/* USB 2.0: handshake mode */
#घोषणा USB_PID_SETUP			0x2d
#घोषणा USB_PID_STALL			0x1e
#घोषणा USB_PID_MDATA			0x0f	/* USB 2.0 */

/*-------------------------------------------------------------------------*/

/*
 * USB Host Controller Driver (usb_hcd) framework
 *
 * Since "struct usb_bus" is so thin, you can't share much code in it.
 * This framework is a layer over that, and should be more sharable.
 */

/*-------------------------------------------------------------------------*/

काष्ठा giveback_urb_bh अणु
	bool running;
	spinlock_t lock;
	काष्ठा list_head  head;
	काष्ठा tasklet_काष्ठा bh;
	काष्ठा usb_host_endpoपूर्णांक *completing_ep;
पूर्ण;

क्रमागत usb_dev_authorize_policy अणु
	USB_DEVICE_AUTHORIZE_NONE	= 0,
	USB_DEVICE_AUTHORIZE_ALL	= 1,
	USB_DEVICE_AUTHORIZE_INTERNAL	= 2,
पूर्ण;

काष्ठा usb_hcd अणु

	/*
	 * housekeeping
	 */
	काष्ठा usb_bus		self;		/* hcd is-a bus */
	काष्ठा kref		kref;		/* reference counter */

	स्थिर अक्षर		*product_desc;	/* product/venकरोr string */
	पूर्णांक			speed;		/* Speed क्रम this roothub.
						 * May be dअगरferent from
						 * hcd->driver->flags & HCD_MASK
						 */
	अक्षर			irq_descr[24];	/* driver + bus # */

	काष्ठा समयr_list	rh_समयr;	/* drives root-hub polling */
	काष्ठा urb		*status_urb;	/* the current status urb */
#अगर_घोषित CONFIG_PM
	काष्ठा work_काष्ठा	wakeup_work;	/* क्रम remote wakeup */
#पूर्ण_अगर
	काष्ठा work_काष्ठा	died_work;	/* क्रम when the device dies */

	/*
	 * hardware info/state
	 */
	स्थिर काष्ठा hc_driver	*driver;	/* hw-specअगरic hooks */

	/*
	 * OTG and some Host controllers need software पूर्णांकeraction with phys;
	 * other बाह्यal phys should be software-transparent
	 */
	काष्ठा usb_phy		*usb_phy;
	काष्ठा usb_phy_roothub	*phy_roothub;

	/* Flags that need to be manipulated atomically because they can
	 * change जबतक the host controller is running.  Always use
	 * set_bit() or clear_bit() to change their values.
	 */
	अचिन्हित दीर्घ		flags;
#घोषणा HCD_FLAG_HW_ACCESSIBLE		0	/* at full घातer */
#घोषणा HCD_FLAG_POLL_RH		2	/* poll क्रम rh status? */
#घोषणा HCD_FLAG_POLL_PENDING		3	/* status has changed? */
#घोषणा HCD_FLAG_WAKEUP_PENDING		4	/* root hub is resuming? */
#घोषणा HCD_FLAG_RH_RUNNING		5	/* root hub is running? */
#घोषणा HCD_FLAG_DEAD			6	/* controller has died? */
#घोषणा HCD_FLAG_INTF_AUTHORIZED	7	/* authorize पूर्णांकerfaces? */

	/* The flags can be tested using these macros; they are likely to
	 * be slightly faster than test_bit().
	 */
#घोषणा HCD_HW_ACCESSIBLE(hcd)	((hcd)->flags & (1U << HCD_FLAG_HW_ACCESSIBLE))
#घोषणा HCD_POLL_RH(hcd)	((hcd)->flags & (1U << HCD_FLAG_POLL_RH))
#घोषणा HCD_POLL_PENDING(hcd)	((hcd)->flags & (1U << HCD_FLAG_POLL_PENDING))
#घोषणा HCD_WAKEUP_PENDING(hcd)	((hcd)->flags & (1U << HCD_FLAG_WAKEUP_PENDING))
#घोषणा HCD_RH_RUNNING(hcd)	((hcd)->flags & (1U << HCD_FLAG_RH_RUNNING))
#घोषणा HCD_DEAD(hcd)		((hcd)->flags & (1U << HCD_FLAG_DEAD))

	/*
	 * Specअगरies अगर पूर्णांकerfaces are authorized by शेष
	 * or they require explicit user space authorization; this bit is
	 * settable through /sys/class/usb_host/X/पूर्णांकerface_authorized_शेष
	 */
#घोषणा HCD_INTF_AUTHORIZED(hcd) \
	((hcd)->flags & (1U << HCD_FLAG_INTF_AUTHORIZED))

	/*
	 * Specअगरies अगर devices are authorized by शेष
	 * or they require explicit user space authorization; this bit is
	 * settable through /sys/class/usb_host/X/authorized_शेष
	 */
	क्रमागत usb_dev_authorize_policy dev_policy;

	/* Flags that get set only during HCD registration or removal. */
	अचिन्हित		rh_रेजिस्टरed:1;/* is root hub रेजिस्टरed? */
	अचिन्हित		rh_pollable:1;	/* may we poll the root hub? */
	अचिन्हित		msix_enabled:1;	/* driver has MSI-X enabled? */
	अचिन्हित		msi_enabled:1;	/* driver has MSI enabled? */
	/*
	 * करो not manage the PHY state in the HCD core, instead let the driver
	 * handle this (क्रम example अगर the PHY can only be turned on after a
	 * specअगरic event)
	 */
	अचिन्हित		skip_phy_initialization:1;

	/* The next flag is a stopgap, to be हटाओd when all the HCDs
	 * support the new root-hub polling mechanism. */
	अचिन्हित		uses_new_polling:1;
	अचिन्हित		wireless:1;	/* Wireless USB HCD */
	अचिन्हित		has_tt:1;	/* Integrated TT in root hub */
	अचिन्हित		amd_resume_bug:1; /* AMD remote wakeup quirk */
	अचिन्हित		can_करो_streams:1; /* HC supports streams */
	अचिन्हित		tpl_support:1; /* OTG & EH TPL support */
	अचिन्हित		cant_recv_wakeups:1;
			/* wakeup requests from करोwnstream aren't received */

	अचिन्हित पूर्णांक		irq;		/* irq allocated */
	व्योम __iomem		*regs;		/* device memory/io */
	resource_माप_प्रकार		rsrc_start;	/* memory/io resource start */
	resource_माप_प्रकार		rsrc_len;	/* memory/io resource length */
	अचिन्हित		घातer_budget;	/* in mA, 0 = no limit */

	काष्ठा giveback_urb_bh  high_prio_bh;
	काष्ठा giveback_urb_bh  low_prio_bh;

	/* bandwidth_mutex should be taken beक्रमe adding or removing
	 * any new bus bandwidth स्थिरraपूर्णांकs:
	 *   1. Beक्रमe adding a configuration क्रम a new device.
	 *   2. Beक्रमe removing the configuration to put the device पूर्णांकo
	 *      the addressed state.
	 *   3. Beक्रमe selecting a dअगरferent configuration.
	 *   4. Beक्रमe selecting an alternate पूर्णांकerface setting.
	 *
	 * bandwidth_mutex should be dropped after a successful control message
	 * to the device, or resetting the bandwidth after a failed attempt.
	 */
	काष्ठा mutex		*address0_mutex;
	काष्ठा mutex		*bandwidth_mutex;
	काष्ठा usb_hcd		*shared_hcd;
	काष्ठा usb_hcd		*primary_hcd;


#घोषणा HCD_BUFFER_POOLS	4
	काष्ठा dma_pool		*pool[HCD_BUFFER_POOLS];

	पूर्णांक			state;
#	define	__ACTIVE		0x01
#	define	__SUSPEND		0x04
#	define	__TRANSIENT		0x80

#	define	HC_STATE_HALT		0
#	define	HC_STATE_RUNNING	(__ACTIVE)
#	define	HC_STATE_QUIESCING	(__SUSPEND|__TRANSIENT|__ACTIVE)
#	define	HC_STATE_RESUMING	(__SUSPEND|__TRANSIENT)
#	define	HC_STATE_SUSPENDED	(__SUSPEND)

#घोषणा	HC_IS_RUNNING(state) ((state) & __ACTIVE)
#घोषणा	HC_IS_SUSPENDED(state) ((state) & __SUSPEND)

	/* memory pool क्रम HCs having local memory, or %शून्य */
	काष्ठा gen_pool         *localmem_pool;

	/* more shared queuing code would be good; it should support
	 * smarter scheduling, handle transaction translators, etc;
	 * input size of periodic table to an पूर्णांकerrupt scheduler.
	 * (ohci 32, uhci 1024, ehci 256/512/1024).
	 */

	/* The HC driver's निजी data is stored at the end of
	 * this काष्ठाure.
	 */
	अचिन्हित दीर्घ hcd_priv[]
			__attribute__ ((aligned(माप(s64))));
पूर्ण;

/* 2.4 करोes this a bit dअगरferently ... */
अटल अंतरभूत काष्ठा usb_bus *hcd_to_bus(काष्ठा usb_hcd *hcd)
अणु
	वापस &hcd->self;
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *bus_to_hcd(काष्ठा usb_bus *bus)
अणु
	वापस container_of(bus, काष्ठा usb_hcd, self);
पूर्ण

/*-------------------------------------------------------------------------*/


काष्ठा hc_driver अणु
	स्थिर अक्षर	*description;	/* "ehci-hcd" etc */
	स्थिर अक्षर	*product_desc;	/* product/venकरोr string */
	माप_प्रकार		hcd_priv_size;	/* size of निजी data */

	/* irq handler */
	irqवापस_t	(*irq) (काष्ठा usb_hcd *hcd);

	पूर्णांक	flags;
#घोषणा	HCD_MEMORY	0x0001		/* HC regs use memory (अन्यथा I/O) */
#घोषणा	HCD_DMA		0x0002		/* HC uses DMA */
#घोषणा	HCD_SHARED	0x0004		/* Two (or more) usb_hcds share HW */
#घोषणा	HCD_USB11	0x0010		/* USB 1.1 */
#घोषणा	HCD_USB2	0x0020		/* USB 2.0 */
#घोषणा	HCD_USB25	0x0030		/* Wireless USB 1.0 (USB 2.5)*/
#घोषणा	HCD_USB3	0x0040		/* USB 3.0 */
#घोषणा	HCD_USB31	0x0050		/* USB 3.1 */
#घोषणा	HCD_USB32	0x0060		/* USB 3.2 */
#घोषणा	HCD_MASK	0x0070
#घोषणा	HCD_BH		0x0100		/* URB complete in BH context */

	/* called to init HCD and root hub */
	पूर्णांक	(*reset) (काष्ठा usb_hcd *hcd);
	पूर्णांक	(*start) (काष्ठा usb_hcd *hcd);

	/* NOTE:  these suspend/resume calls relate to the HC as
	 * a whole, not just the root hub; they're क्रम PCI bus glue.
	 */
	/* called after suspending the hub, beक्रमe entering D3 etc */
	पूर्णांक	(*pci_suspend)(काष्ठा usb_hcd *hcd, bool करो_wakeup);

	/* called after entering D0 (etc), beक्रमe resuming the hub */
	पूर्णांक	(*pci_resume)(काष्ठा usb_hcd *hcd, bool hibernated);

	/* cleanly make HCD stop writing memory and करोing I/O */
	व्योम	(*stop) (काष्ठा usb_hcd *hcd);

	/* shutकरोwn HCD */
	व्योम	(*shutकरोwn) (काष्ठा usb_hcd *hcd);

	/* वापस current frame number */
	पूर्णांक	(*get_frame_number) (काष्ठा usb_hcd *hcd);

	/* manage i/o requests, device state */
	पूर्णांक	(*urb_enqueue)(काष्ठा usb_hcd *hcd,
				काष्ठा urb *urb, gfp_t mem_flags);
	पूर्णांक	(*urb_dequeue)(काष्ठा usb_hcd *hcd,
				काष्ठा urb *urb, पूर्णांक status);

	/*
	 * (optional) these hooks allow an HCD to override the शेष DMA
	 * mapping and unmapping routines.  In general, they shouldn't be
	 * necessary unless the host controller has special DMA requirements,
	 * such as alignment contraपूर्णांकs.  If these are not specअगरied, the
	 * general usb_hcd_(un)?map_urb_क्रम_dma functions will be used instead
	 * (and it may be a good idea to call these functions in your HCD
	 * implementation)
	 */
	पूर्णांक	(*map_urb_क्रम_dma)(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				   gfp_t mem_flags);
	व्योम    (*unmap_urb_क्रम_dma)(काष्ठा usb_hcd *hcd, काष्ठा urb *urb);

	/* hw synch, मुक्तing endpoपूर्णांक resources that urb_dequeue can't */
	व्योम	(*endpoपूर्णांक_disable)(काष्ठा usb_hcd *hcd,
			काष्ठा usb_host_endpoपूर्णांक *ep);

	/* (optional) reset any endpoपूर्णांक state such as sequence number
	   and current winकरोw */
	व्योम	(*endpoपूर्णांक_reset)(काष्ठा usb_hcd *hcd,
			काष्ठा usb_host_endpoपूर्णांक *ep);

	/* root hub support */
	पूर्णांक	(*hub_status_data) (काष्ठा usb_hcd *hcd, अक्षर *buf);
	पूर्णांक	(*hub_control) (काष्ठा usb_hcd *hcd,
				u16 typeReq, u16 wValue, u16 wIndex,
				अक्षर *buf, u16 wLength);
	पूर्णांक	(*bus_suspend)(काष्ठा usb_hcd *);
	पूर्णांक	(*bus_resume)(काष्ठा usb_hcd *);
	पूर्णांक	(*start_port_reset)(काष्ठा usb_hcd *, अचिन्हित port_num);
	अचिन्हित दीर्घ	(*get_resuming_ports)(काष्ठा usb_hcd *);

		/* क्रमce hanकरोver of high-speed port to full-speed companion */
	व्योम	(*relinquish_port)(काष्ठा usb_hcd *, पूर्णांक);
		/* has a port been handed over to a companion? */
	पूर्णांक	(*port_handed_over)(काष्ठा usb_hcd *, पूर्णांक);

		/* CLEAR_TT_BUFFER completion callback */
	व्योम	(*clear_tt_buffer_complete)(काष्ठा usb_hcd *,
				काष्ठा usb_host_endpoपूर्णांक *);

	/* xHCI specअगरic functions */
		/* Called by usb_alloc_dev to alloc HC device काष्ठाures */
	पूर्णांक	(*alloc_dev)(काष्ठा usb_hcd *, काष्ठा usb_device *);
		/* Called by usb_disconnect to मुक्त HC device काष्ठाures */
	व्योम	(*मुक्त_dev)(काष्ठा usb_hcd *, काष्ठा usb_device *);
	/* Change a group of bulk endpoपूर्णांकs to support multiple stream IDs */
	पूर्णांक	(*alloc_streams)(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		अचिन्हित पूर्णांक num_streams, gfp_t mem_flags);
	/* Reverts a group of bulk endpoपूर्णांकs back to not using stream IDs.
	 * Can fail अगर we run out of memory.
	 */
	पूर्णांक	(*मुक्त_streams)(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		gfp_t mem_flags);

	/* Bandwidth computation functions */
	/* Note that add_endpoपूर्णांक() can only be called once per endpoपूर्णांक beक्रमe
	 * check_bandwidth() or reset_bandwidth() must be called.
	 * drop_endpoपूर्णांक() can only be called once per endpoपूर्णांक also.
	 * A call to xhci_drop_endpoपूर्णांक() followed by a call to
	 * xhci_add_endpoपूर्णांक() will add the endpoपूर्णांक to the schedule with
	 * possibly new parameters denoted by a dअगरferent endpoपूर्णांक descriptor
	 * in usb_host_endpoपूर्णांक.  A call to xhci_add_endpoपूर्णांक() followed by a
	 * call to xhci_drop_endpoपूर्णांक() is not allowed.
	 */
		/* Allocate endpoपूर्णांक resources and add them to a new schedule */
	पूर्णांक	(*add_endpoपूर्णांक)(काष्ठा usb_hcd *, काष्ठा usb_device *,
				काष्ठा usb_host_endpoपूर्णांक *);
		/* Drop an endpoपूर्णांक from a new schedule */
	पूर्णांक	(*drop_endpoपूर्णांक)(काष्ठा usb_hcd *, काष्ठा usb_device *,
				 काष्ठा usb_host_endpoपूर्णांक *);
		/* Check that a new hardware configuration, set using
		 * endpoपूर्णांक_enable and endpoपूर्णांक_disable, करोes not exceed bus
		 * bandwidth.  This must be called beक्रमe any set configuration
		 * or set पूर्णांकerface requests are sent to the device.
		 */
	पूर्णांक	(*check_bandwidth)(काष्ठा usb_hcd *, काष्ठा usb_device *);
		/* Reset the device schedule to the last known good schedule,
		 * which was set from a previous successful call to
		 * check_bandwidth().  This reverts any add_endpoपूर्णांक() and
		 * drop_endpoपूर्णांक() calls since that last successful call.
		 * Used क्रम when a check_bandwidth() call fails due to resource
		 * or bandwidth स्थिरraपूर्णांकs.
		 */
	व्योम	(*reset_bandwidth)(काष्ठा usb_hcd *, काष्ठा usb_device *);
		/* Returns the hardware-chosen device address */
	पूर्णांक	(*address_device)(काष्ठा usb_hcd *, काष्ठा usb_device *udev);
		/* prepares the hardware to send commands to the device */
	पूर्णांक	(*enable_device)(काष्ठा usb_hcd *, काष्ठा usb_device *udev);
		/* Notअगरies the HCD after a hub descriptor is fetched.
		 * Will block.
		 */
	पूर्णांक	(*update_hub_device)(काष्ठा usb_hcd *, काष्ठा usb_device *hdev,
			काष्ठा usb_tt *tt, gfp_t mem_flags);
	पूर्णांक	(*reset_device)(काष्ठा usb_hcd *, काष्ठा usb_device *);
		/* Notअगरies the HCD after a device is connected and its
		 * address is set
		 */
	पूर्णांक	(*update_device)(काष्ठा usb_hcd *, काष्ठा usb_device *);
	पूर्णांक	(*set_usb2_hw_lpm)(काष्ठा usb_hcd *, काष्ठा usb_device *, पूर्णांक);
	/* USB 3.0 Link Power Management */
		/* Returns the USB3 hub-encoded value क्रम the U1/U2 समयout. */
	पूर्णांक	(*enable_usb3_lpm_समयout)(काष्ठा usb_hcd *,
			काष्ठा usb_device *, क्रमागत usb3_link_state state);
		/* The xHCI host controller can still fail the command to
		 * disable the LPM समयouts, so this can वापस an error code.
		 */
	पूर्णांक	(*disable_usb3_lpm_समयout)(काष्ठा usb_hcd *,
			काष्ठा usb_device *, क्रमागत usb3_link_state state);
	पूर्णांक	(*find_raw_port_number)(काष्ठा usb_hcd *, पूर्णांक);
	/* Call क्रम घातer on/off the port अगर necessary */
	पूर्णांक	(*port_घातer)(काष्ठा usb_hcd *hcd, पूर्णांक portnum, bool enable);

पूर्ण;

अटल अंतरभूत पूर्णांक hcd_giveback_urb_in_bh(काष्ठा usb_hcd *hcd)
अणु
	वापस hcd->driver->flags & HCD_BH;
पूर्ण

अटल अंतरभूत bool hcd_periodic_completion_in_progress(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	वापस hcd->high_prio_bh.completing_ep == ep;
पूर्ण

अटल अंतरभूत bool hcd_uses_dma(काष्ठा usb_hcd *hcd)
अणु
	वापस IS_ENABLED(CONFIG_HAS_DMA) && (hcd->driver->flags & HCD_DMA);
पूर्ण

बाह्य पूर्णांक usb_hcd_link_urb_to_ep(काष्ठा usb_hcd *hcd, काष्ठा urb *urb);
बाह्य पूर्णांक usb_hcd_check_unlink_urb(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		पूर्णांक status);
बाह्य व्योम usb_hcd_unlink_urb_from_ep(काष्ठा usb_hcd *hcd, काष्ठा urb *urb);

बाह्य पूर्णांक usb_hcd_submit_urb(काष्ठा urb *urb, gfp_t mem_flags);
बाह्य पूर्णांक usb_hcd_unlink_urb(काष्ठा urb *urb, पूर्णांक status);
बाह्य व्योम usb_hcd_giveback_urb(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		पूर्णांक status);
बाह्य पूर्णांक usb_hcd_map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		gfp_t mem_flags);
बाह्य व्योम usb_hcd_unmap_urb_setup_क्रम_dma(काष्ठा usb_hcd *, काष्ठा urb *);
बाह्य व्योम usb_hcd_unmap_urb_क्रम_dma(काष्ठा usb_hcd *, काष्ठा urb *);
बाह्य व्योम usb_hcd_flush_endpoपूर्णांक(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep);
बाह्य व्योम usb_hcd_disable_endpoपूर्णांक(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep);
बाह्य व्योम usb_hcd_reset_endpoपूर्णांक(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep);
बाह्य व्योम usb_hcd_synchronize_unlinks(काष्ठा usb_device *udev);
बाह्य पूर्णांक usb_hcd_alloc_bandwidth(काष्ठा usb_device *udev,
		काष्ठा usb_host_config *new_config,
		काष्ठा usb_host_पूर्णांकerface *old_alt,
		काष्ठा usb_host_पूर्णांकerface *new_alt);
बाह्य पूर्णांक usb_hcd_get_frame_number(काष्ठा usb_device *udev);

काष्ठा usb_hcd *__usb_create_hcd(स्थिर काष्ठा hc_driver *driver,
		काष्ठा device *sysdev, काष्ठा device *dev, स्थिर अक्षर *bus_name,
		काष्ठा usb_hcd *primary_hcd);
बाह्य काष्ठा usb_hcd *usb_create_hcd(स्थिर काष्ठा hc_driver *driver,
		काष्ठा device *dev, स्थिर अक्षर *bus_name);
बाह्य काष्ठा usb_hcd *usb_create_shared_hcd(स्थिर काष्ठा hc_driver *driver,
		काष्ठा device *dev, स्थिर अक्षर *bus_name,
		काष्ठा usb_hcd *shared_hcd);
बाह्य काष्ठा usb_hcd *usb_get_hcd(काष्ठा usb_hcd *hcd);
बाह्य व्योम usb_put_hcd(काष्ठा usb_hcd *hcd);
बाह्य पूर्णांक usb_hcd_is_primary_hcd(काष्ठा usb_hcd *hcd);
बाह्य पूर्णांक usb_add_hcd(काष्ठा usb_hcd *hcd,
		अचिन्हित पूर्णांक irqnum, अचिन्हित दीर्घ irqflags);
बाह्य व्योम usb_हटाओ_hcd(काष्ठा usb_hcd *hcd);
बाह्य पूर्णांक usb_hcd_find_raw_port_number(काष्ठा usb_hcd *hcd, पूर्णांक port1);
पूर्णांक usb_hcd_setup_local_mem(काष्ठा usb_hcd *hcd, phys_addr_t phys_addr,
			    dma_addr_t dma, माप_प्रकार size);

काष्ठा platक्रमm_device;
बाह्य व्योम usb_hcd_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *dev);

#अगर_घोषित CONFIG_USB_PCI
काष्ठा pci_dev;
काष्ठा pci_device_id;
बाह्य पूर्णांक usb_hcd_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id,
			     स्थिर काष्ठा hc_driver *driver);
बाह्य व्योम usb_hcd_pci_हटाओ(काष्ठा pci_dev *dev);
बाह्य व्योम usb_hcd_pci_shutकरोwn(काष्ठा pci_dev *dev);

बाह्य पूर्णांक usb_hcd_amd_remote_wakeup_quirk(काष्ठा pci_dev *dev);

#अगर_घोषित CONFIG_PM
बाह्य स्थिर काष्ठा dev_pm_ops usb_hcd_pci_pm_ops;
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_USB_PCI */

/* pci-ish (pdev null is ok) buffer alloc/mapping support */
व्योम usb_init_pool_max(व्योम);
पूर्णांक hcd_buffer_create(काष्ठा usb_hcd *hcd);
व्योम hcd_buffer_destroy(काष्ठा usb_hcd *hcd);

व्योम *hcd_buffer_alloc(काष्ठा usb_bus *bus, माप_प्रकार size,
	gfp_t mem_flags, dma_addr_t *dma);
व्योम hcd_buffer_मुक्त(काष्ठा usb_bus *bus, माप_प्रकार size,
	व्योम *addr, dma_addr_t dma);

/* generic bus glue, needed क्रम host controllers that करोn't use PCI */
बाह्य irqवापस_t usb_hcd_irq(पूर्णांक irq, व्योम *__hcd);

बाह्य व्योम usb_hc_died(काष्ठा usb_hcd *hcd);
बाह्य व्योम usb_hcd_poll_rh_status(काष्ठा usb_hcd *hcd);
बाह्य व्योम usb_wakeup_notअगरication(काष्ठा usb_device *hdev,
		अचिन्हित पूर्णांक portnum);

बाह्य व्योम usb_hcd_start_port_resume(काष्ठा usb_bus *bus, पूर्णांक portnum);
बाह्य व्योम usb_hcd_end_port_resume(काष्ठा usb_bus *bus, पूर्णांक portnum);

/* The D0/D1 toggle bits ... USE WITH CAUTION (they're almost hcd-पूर्णांकernal) */
#घोषणा usb_gettoggle(dev, ep, out) (((dev)->toggle[out] >> (ep)) & 1)
#घोषणा	usb_करोtoggle(dev, ep, out)  ((dev)->toggle[out] ^= (1 << (ep)))
#घोषणा usb_settoggle(dev, ep, out, bit) \
		((dev)->toggle[out] = ((dev)->toggle[out] & ~(1 << (ep))) | \
		 ((bit) << (ep)))

/* -------------------------------------------------------------------------- */

/* Enumeration is only क्रम the hub driver, or HCD भव root hubs */
बाह्य काष्ठा usb_device *usb_alloc_dev(काष्ठा usb_device *parent,
					काष्ठा usb_bus *, अचिन्हित port);
बाह्य पूर्णांक usb_new_device(काष्ठा usb_device *dev);
बाह्य व्योम usb_disconnect(काष्ठा usb_device **);

बाह्य पूर्णांक usb_get_configuration(काष्ठा usb_device *dev);
बाह्य व्योम usb_destroy_configuration(काष्ठा usb_device *dev);

/*-------------------------------------------------------------------------*/

/*
 * HCD Root Hub support
 */

#समावेश <linux/usb/ch11.h>

/*
 * As of USB 2.0, full/low speed devices are segregated पूर्णांकo trees.
 * One type grows from USB 1.1 host controllers (OHCI, UHCI etc).
 * The other type grows from high speed hubs when they connect to
 * full/low speed devices using "Transaction Translators" (TTs).
 *
 * TTs should only be known to the hub driver, and high speed bus
 * drivers (only EHCI क्रम now).  They affect periodic scheduling and
 * someबार control/bulk error recovery.
 */

काष्ठा usb_device;

काष्ठा usb_tt अणु
	काष्ठा usb_device	*hub;	/* upstream highspeed hub */
	पूर्णांक			multi;	/* true means one TT per port */
	अचिन्हित		think_समय;	/* think समय in ns */
	व्योम			*hcpriv;	/* HCD निजी data */

	/* क्रम control/bulk error recovery (CLEAR_TT_BUFFER) */
	spinlock_t		lock;
	काष्ठा list_head	clear_list;	/* of usb_tt_clear */
	काष्ठा work_काष्ठा	clear_work;
पूर्ण;

काष्ठा usb_tt_clear अणु
	काष्ठा list_head	clear_list;
	अचिन्हित		tt;
	u16			devinfo;
	काष्ठा usb_hcd		*hcd;
	काष्ठा usb_host_endpoपूर्णांक	*ep;
पूर्ण;

बाह्य पूर्णांक usb_hub_clear_tt_buffer(काष्ठा urb *urb);
बाह्य व्योम usb_ep0_reinit(काष्ठा usb_device *);

/* (shअगरted) direction/type/recipient from the USB 2.0 spec, table 9.2 */
#घोषणा DeviceRequest \
	((USB_सूची_IN|USB_TYPE_STANDARD|USB_RECIP_DEVICE)<<8)
#घोषणा DeviceOutRequest \
	((USB_सूची_OUT|USB_TYPE_STANDARD|USB_RECIP_DEVICE)<<8)

#घोषणा InterfaceRequest \
	((USB_सूची_IN|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)<<8)

#घोषणा Endpoपूर्णांकRequest \
	((USB_सूची_IN|USB_TYPE_STANDARD|USB_RECIP_ENDPOINT)<<8)
#घोषणा Endpoपूर्णांकOutRequest \
	((USB_सूची_OUT|USB_TYPE_STANDARD|USB_RECIP_ENDPOINT)<<8)

/* class requests from the USB 2.0 hub spec, table 11-15 */
#घोषणा HUB_CLASS_REQ(dir, type, request) ((((dir) | (type)) << 8) | (request))
/* GetBusState and SetHubDescriptor are optional, omitted */
#घोषणा ClearHubFeature		HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_HUB, USB_REQ_CLEAR_FEATURE)
#घोषणा ClearPortFeature	HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_PORT, USB_REQ_CLEAR_FEATURE)
#घोषणा GetHubDescriptor	HUB_CLASS_REQ(USB_सूची_IN, USB_RT_HUB, USB_REQ_GET_DESCRIPTOR)
#घोषणा GetHubStatus		HUB_CLASS_REQ(USB_सूची_IN, USB_RT_HUB, USB_REQ_GET_STATUS)
#घोषणा GetPortStatus		HUB_CLASS_REQ(USB_सूची_IN, USB_RT_PORT, USB_REQ_GET_STATUS)
#घोषणा SetHubFeature		HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_HUB, USB_REQ_SET_FEATURE)
#घोषणा SetPortFeature		HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_PORT, USB_REQ_SET_FEATURE)
#घोषणा ClearTTBuffer		HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_PORT, HUB_CLEAR_TT_BUFFER)
#घोषणा ResetTT			HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_PORT, HUB_RESET_TT)
#घोषणा GetTTState		HUB_CLASS_REQ(USB_सूची_IN, USB_RT_PORT, HUB_GET_TT_STATE)
#घोषणा StopTT			HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_PORT, HUB_STOP_TT)


/*-------------------------------------------------------------------------*/

/* class requests from USB 3.1 hub spec, table 10-7 */
#घोषणा SetHubDepth		HUB_CLASS_REQ(USB_सूची_OUT, USB_RT_HUB, HUB_SET_DEPTH)
#घोषणा GetPortErrorCount	HUB_CLASS_REQ(USB_सूची_IN, USB_RT_PORT, HUB_GET_PORT_ERR_COUNT)

/*
 * Generic bandwidth allocation स्थिरants/support
 */
#घोषणा FRAME_TIME_USECS	1000L
#घोषणा BitTime(bytecount) (7 * 8 * bytecount / 6) /* with पूर्णांकeger truncation */
		/* Trying not to use worst-हाल bit-stuffing
		 * of (7/6 * 8 * bytecount) = 9.33 * bytecount */
		/* bytecount = data payload byte count */

#घोषणा NS_TO_US(ns)	DIV_ROUND_UP(ns, 1000L)
			/* convert nanoseconds to microseconds, rounding up */

/*
 * Full/low speed bandwidth allocation स्थिरants/support.
 */
#घोषणा BW_HOST_DELAY	1000L		/* nanoseconds */
#घोषणा BW_HUB_LS_SETUP	333L		/* nanoseconds */
			/* 4 full-speed bit बार (est.) */

#घोषणा FRAME_TIME_BITS			12000L	/* frame = 1 millisecond */
#घोषणा FRAME_TIME_MAX_BITS_ALLOC	(90L * FRAME_TIME_BITS / 100L)
#घोषणा FRAME_TIME_MAX_USECS_ALLOC	(90L * FRAME_TIME_USECS / 100L)

/*
 * Ceiling [nano/micro]seconds (typical) क्रम that many bytes at high speed
 * ISO is a bit less, no ACK ... from USB 2.0 spec, 5.11.3 (and needed
 * to pपुनः_स्मृतिate bandwidth)
 */
#घोषणा USB2_HOST_DELAY	5	/* nsec, guess */
#घोषणा HS_NSECS(bytes) (((55 * 8 * 2083) \
	+ (2083UL * (3 + BitTime(bytes))))/1000 \
	+ USB2_HOST_DELAY)
#घोषणा HS_NSECS_ISO(bytes) (((38 * 8 * 2083) \
	+ (2083UL * (3 + BitTime(bytes))))/1000 \
	+ USB2_HOST_DELAY)
#घोषणा HS_USECS(bytes)		NS_TO_US(HS_NSECS(bytes))
#घोषणा HS_USECS_ISO(bytes)	NS_TO_US(HS_NSECS_ISO(bytes))

बाह्य दीर्घ usb_calc_bus_समय(पूर्णांक speed, पूर्णांक is_input,
			पूर्णांक isoc, पूर्णांक bytecount);

/*-------------------------------------------------------------------------*/

बाह्य व्योम usb_set_device_state(काष्ठा usb_device *udev,
		क्रमागत usb_device_state new_state);

/*-------------------------------------------------------------------------*/

/* exported only within usbcore */

बाह्य काष्ठा idr usb_bus_idr;
बाह्य काष्ठा mutex usb_bus_idr_lock;
बाह्य रुको_queue_head_t usb_समाप्त_urb_queue;


#घोषणा usb_endpoपूर्णांक_out(ep_dir)	(!((ep_dir) & USB_सूची_IN))

#अगर_घोषित CONFIG_PM
बाह्य अचिन्हित usb_wakeup_enabled_descendants(काष्ठा usb_device *udev);
बाह्य व्योम usb_root_hub_lost_घातer(काष्ठा usb_device *rhdev);
बाह्य पूर्णांक hcd_bus_suspend(काष्ठा usb_device *rhdev, pm_message_t msg);
बाह्य पूर्णांक hcd_bus_resume(काष्ठा usb_device *rhdev, pm_message_t msg);
बाह्य व्योम usb_hcd_resume_root_hub(काष्ठा usb_hcd *hcd);
#अन्यथा
अटल अंतरभूत अचिन्हित usb_wakeup_enabled_descendants(काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम usb_hcd_resume_root_hub(काष्ठा usb_hcd *hcd)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

/*-------------------------------------------------------------------------*/

#अगर defined(CONFIG_USB_MON) || defined(CONFIG_USB_MON_MODULE)

काष्ठा usb_mon_operations अणु
	व्योम (*urb_submit)(काष्ठा usb_bus *bus, काष्ठा urb *urb);
	व्योम (*urb_submit_error)(काष्ठा usb_bus *bus, काष्ठा urb *urb, पूर्णांक err);
	व्योम (*urb_complete)(काष्ठा usb_bus *bus, काष्ठा urb *urb, पूर्णांक status);
	/* व्योम (*urb_unlink)(काष्ठा usb_bus *bus, काष्ठा urb *urb); */
पूर्ण;

बाह्य स्थिर काष्ठा usb_mon_operations *mon_ops;

अटल अंतरभूत व्योम usbmon_urb_submit(काष्ठा usb_bus *bus, काष्ठा urb *urb)
अणु
	अगर (bus->monitored)
		(*mon_ops->urb_submit)(bus, urb);
पूर्ण

अटल अंतरभूत व्योम usbmon_urb_submit_error(काष्ठा usb_bus *bus, काष्ठा urb *urb,
    पूर्णांक error)
अणु
	अगर (bus->monitored)
		(*mon_ops->urb_submit_error)(bus, urb, error);
पूर्ण

अटल अंतरभूत व्योम usbmon_urb_complete(काष्ठा usb_bus *bus, काष्ठा urb *urb,
		पूर्णांक status)
अणु
	अगर (bus->monitored)
		(*mon_ops->urb_complete)(bus, urb, status);
पूर्ण

पूर्णांक usb_mon_रेजिस्टर(स्थिर काष्ठा usb_mon_operations *ops);
व्योम usb_mon_deरेजिस्टर(व्योम);

#अन्यथा

अटल अंतरभूत व्योम usbmon_urb_submit(काष्ठा usb_bus *bus, काष्ठा urb *urb) अणुपूर्ण
अटल अंतरभूत व्योम usbmon_urb_submit_error(काष्ठा usb_bus *bus, काष्ठा urb *urb,
    पूर्णांक error) अणुपूर्ण
अटल अंतरभूत व्योम usbmon_urb_complete(काष्ठा usb_bus *bus, काष्ठा urb *urb,
		पूर्णांक status) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_USB_MON || CONFIG_USB_MON_MODULE */

/*-------------------------------------------------------------------------*/

/* अक्रमom stuff */

/* This rwsem is क्रम use only by the hub driver and ehci-hcd.
 * Nobody अन्यथा should touch it.
 */
बाह्य काष्ठा rw_semaphore ehci_cf_port_reset_rwsem;

/* Keep track of which host controller drivers are loaded */
#घोषणा USB_UHCI_LOADED		0
#घोषणा USB_OHCI_LOADED		1
#घोषणा USB_EHCI_LOADED		2
बाह्य अचिन्हित दीर्घ usb_hcds_loaded;

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __USB_CORE_HCD_H */
