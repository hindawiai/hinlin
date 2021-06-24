<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 * Copyright (C) 2015 Nobuo Iwata
 */

#अगर_अघोषित __USBIP_VHCI_H
#घोषणा __USBIP_VHCI_H

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/रुको.h>

काष्ठा vhci_device अणु
	काष्ठा usb_device *udev;

	/*
	 * devid specअगरies a remote usb device uniquely instead
	 * of combination of busnum and devnum.
	 */
	__u32 devid;

	/* speed of a remote device */
	क्रमागत usb_device_speed speed;

	/* vhci root-hub port to which this device is attached */
	__u32 rhport;

	काष्ठा usbip_device ud;

	/* lock क्रम the below link lists */
	spinlock_t priv_lock;

	/* vhci_priv is linked to one of them. */
	काष्ठा list_head priv_tx;
	काष्ठा list_head priv_rx;

	/* vhci_unlink is linked to one of them */
	काष्ठा list_head unlink_tx;
	काष्ठा list_head unlink_rx;

	/* vhci_tx thपढ़ो sleeps क्रम this queue */
	रुको_queue_head_t रुकोq_tx;
पूर्ण;

/* urb->hcpriv, use container_of() */
काष्ठा vhci_priv अणु
	अचिन्हित दीर्घ seqnum;
	काष्ठा list_head list;

	काष्ठा vhci_device *vdev;
	काष्ठा urb *urb;
पूर्ण;

काष्ठा vhci_unlink अणु
	/* seqnum of this request */
	अचिन्हित दीर्घ seqnum;

	काष्ठा list_head list;

	/* seqnum of the unlink target */
	अचिन्हित दीर्घ unlink_seqnum;
पूर्ण;

क्रमागत hub_speed अणु
	HUB_SPEED_HIGH = 0,
	HUB_SPEED_SUPER,
पूर्ण;

/* Number of supported ports. Value has an upperbound of USB_MAXCHILDREN */
#अगर_घोषित CONFIG_USBIP_VHCI_HC_PORTS
#घोषणा VHCI_HC_PORTS CONFIG_USBIP_VHCI_HC_PORTS
#अन्यथा
#घोषणा VHCI_HC_PORTS 8
#पूर्ण_अगर

/* Each VHCI has 2 hubs (USB2 and USB3), each has VHCI_HC_PORTS ports */
#घोषणा VHCI_PORTS	(VHCI_HC_PORTS*2)

#अगर_घोषित CONFIG_USBIP_VHCI_NR_HCS
#घोषणा VHCI_NR_HCS CONFIG_USBIP_VHCI_NR_HCS
#अन्यथा
#घोषणा VHCI_NR_HCS 1
#पूर्ण_अगर

#घोषणा MAX_STATUS_NAME 16

काष्ठा vhci अणु
	spinlock_t lock;

	काष्ठा platक्रमm_device *pdev;

	काष्ठा vhci_hcd *vhci_hcd_hs;
	काष्ठा vhci_hcd *vhci_hcd_ss;
पूर्ण;

/* क्रम usb_hcd.hcd_priv[0] */
काष्ठा vhci_hcd अणु
	काष्ठा vhci *vhci;

	u32 port_status[VHCI_HC_PORTS];

	अचिन्हित resuming:1;
	अचिन्हित दीर्घ re_समयout;

	atomic_t seqnum;

	/*
	 * NOTE:
	 * wIndex shows the port number and begins from 1.
	 * But, the index of this array begins from 0.
	 */
	काष्ठा vhci_device vdev[VHCI_HC_PORTS];
पूर्ण;

बाह्य पूर्णांक vhci_num_controllers;
बाह्य काष्ठा vhci *vhcis;
बाह्य काष्ठा attribute_group vhci_attr_group;

/* vhci_hcd.c */
व्योम rh_port_connect(काष्ठा vhci_device *vdev, क्रमागत usb_device_speed speed);

/* vhci_sysfs.c */
पूर्णांक vhci_init_attr_group(व्योम);
व्योम vhci_finish_attr_group(व्योम);

/* vhci_rx.c */
काष्ठा urb *pickup_urb_and_मुक्त_priv(काष्ठा vhci_device *vdev, __u32 seqnum);
पूर्णांक vhci_rx_loop(व्योम *data);

/* vhci_tx.c */
पूर्णांक vhci_tx_loop(व्योम *data);

अटल अंतरभूत __u32 port_to_rhport(__u32 port)
अणु
	वापस port % VHCI_HC_PORTS;
पूर्ण

अटल अंतरभूत पूर्णांक port_to_pdev_nr(__u32 port)
अणु
	वापस port / VHCI_PORTS;
पूर्ण

अटल अंतरभूत काष्ठा vhci_hcd *hcd_to_vhci_hcd(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा vhci_hcd *) (hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा device *hcd_dev(काष्ठा usb_hcd *hcd)
अणु
	वापस (hcd)->self.controller;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *hcd_name(काष्ठा usb_hcd *hcd)
अणु
	वापस (hcd)->self.bus_name;
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *vhci_hcd_to_hcd(काष्ठा vhci_hcd *vhci_hcd)
अणु
	वापस container_of((व्योम *) vhci_hcd, काष्ठा usb_hcd, hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा vhci_hcd *vdev_to_vhci_hcd(काष्ठा vhci_device *vdev)
अणु
	वापस container_of((व्योम *)(vdev - vdev->rhport), काष्ठा vhci_hcd, vdev);
पूर्ण

#पूर्ण_अगर /* __USBIP_VHCI_H */
