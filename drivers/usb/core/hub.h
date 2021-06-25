<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * usb hub driver head file
 *
 * Copyright (C) 1999 Linus Torvalds
 * Copyright (C) 1999 Johannes Erdfelt
 * Copyright (C) 1999 Gregory P. Smith
 * Copyright (C) 2001 Brad Hards (bhards@bigpond.net.au)
 * Copyright (C) 2012 Intel Corp (tianyu.lan@पूर्णांकel.com)
 *
 *  move काष्ठा usb_hub to this file.
 */

#समावेश <linux/usb.h>
#समावेश <linux/usb/ch11.h>
#समावेश <linux/usb/hcd.h>
#समावेश "usb.h"

काष्ठा usb_hub अणु
	काष्ठा device		*पूर्णांकfdev;	/* the "interface" device */
	काष्ठा usb_device	*hdev;
	काष्ठा kref		kref;
	काष्ठा urb		*urb;		/* क्रम पूर्णांकerrupt polling pipe */

	/* buffer क्रम urb ... with extra space in हाल of babble */
	u8			(*buffer)[8];
	जोड़ अणु
		काष्ठा usb_hub_status	hub;
		काष्ठा usb_port_status	port;
	पूर्ण			*status;	/* buffer क्रम status reports */
	काष्ठा mutex		status_mutex;	/* क्रम the status buffer */

	पूर्णांक			error;		/* last reported error */
	पूर्णांक			nerrors;	/* track consecutive errors */

	अचिन्हित दीर्घ		event_bits[1];	/* status change biपंचांगask */
	अचिन्हित दीर्घ		change_bits[1];	/* ports with logical connect
							status change */
	अचिन्हित दीर्घ		हटाओd_bits[1]; /* ports with a "removed"
							device present */
	अचिन्हित दीर्घ		wakeup_bits[1];	/* ports that have संकेतed
							remote wakeup */
	अचिन्हित दीर्घ		घातer_bits[1]; /* ports that are घातered */
	अचिन्हित दीर्घ		child_usage_bits[1]; /* ports घातered on क्रम
							children */
	अचिन्हित दीर्घ		warm_reset_bits[1]; /* ports requesting warm
							reset recovery */
#अगर USB_MAXCHILDREN > 31 /* 8*माप(अचिन्हित दीर्घ) - 1 */
#त्रुटि event_bits[] is too लघु!
#पूर्ण_अगर

	काष्ठा usb_hub_descriptor *descriptor;	/* class descriptor */
	काष्ठा usb_tt		tt;		/* Transaction Translator */

	अचिन्हित		mA_per_port;	/* current क्रम each child */
#अगर_घोषित	CONFIG_PM
	अचिन्हित		wakeup_enabled_descendants;
#पूर्ण_अगर

	अचिन्हित		limited_घातer:1;
	अचिन्हित		quiescing:1;
	अचिन्हित		disconnected:1;
	अचिन्हित		in_reset:1;
	अचिन्हित		quirk_disable_स्वतःsuspend:1;

	अचिन्हित		quirk_check_port_स्वतः_suspend:1;

	अचिन्हित		has_indicators:1;
	u8			indicator[USB_MAXCHILDREN];
	काष्ठा delayed_work	leds;
	काष्ठा delayed_work	init_work;
	काष्ठा work_काष्ठा      events;
	spinlock_t		irq_urb_lock;
	काष्ठा समयr_list	irq_urb_retry;
	काष्ठा usb_port		**ports;
पूर्ण;

/**
 * काष्ठा usb port - kernel's representation of a usb port
 * @child: usb device attached to the port
 * @dev: generic device पूर्णांकerface
 * @port_owner: port's owner
 * @peer: related usb2 and usb3 ports (share the same connector)
 * @req: शेष pm qos request क्रम hubs without port घातer control
 * @connect_type: port's connect type
 * @location: opaque representation of platक्रमm connector location
 * @status_lock: synchronize port_event() vs usb_port_अणुsuspend|resumeपूर्ण
 * @portnum: port index num based one
 * @is_superspeed cache super-speed status
 * @usb3_lpm_u1_permit: whether USB3 U1 LPM is permitted.
 * @usb3_lpm_u2_permit: whether USB3 U2 LPM is permitted.
 */
काष्ठा usb_port अणु
	काष्ठा usb_device *child;
	काष्ठा device dev;
	काष्ठा usb_dev_state *port_owner;
	काष्ठा usb_port *peer;
	काष्ठा dev_pm_qos_request *req;
	क्रमागत usb_port_connect_type connect_type;
	usb_port_location_t location;
	काष्ठा mutex status_lock;
	u32 over_current_count;
	u8 portnum;
	u32 quirks;
	अचिन्हित पूर्णांक is_superspeed:1;
	अचिन्हित पूर्णांक usb3_lpm_u1_permit:1;
	अचिन्हित पूर्णांक usb3_lpm_u2_permit:1;
पूर्ण;

#घोषणा to_usb_port(_dev) \
	container_of(_dev, काष्ठा usb_port, dev)

बाह्य पूर्णांक usb_hub_create_port_device(काष्ठा usb_hub *hub,
		पूर्णांक port1);
बाह्य व्योम usb_hub_हटाओ_port_device(काष्ठा usb_hub *hub,
		पूर्णांक port1);
बाह्य पूर्णांक usb_hub_set_port_घातer(काष्ठा usb_device *hdev, काष्ठा usb_hub *hub,
		पूर्णांक port1, bool set);
बाह्य काष्ठा usb_hub *usb_hub_to_काष्ठा_hub(काष्ठा usb_device *hdev);
बाह्य पूर्णांक hub_port_debounce(काष्ठा usb_hub *hub, पूर्णांक port1,
		bool must_be_connected);
बाह्य पूर्णांक usb_clear_port_feature(काष्ठा usb_device *hdev,
		पूर्णांक port1, पूर्णांक feature);

अटल अंतरभूत bool hub_is_port_घातer_चयनable(काष्ठा usb_hub *hub)
अणु
	__le16 hcs;

	अगर (!hub)
		वापस false;
	hcs = hub->descriptor->wHubCharacteristics;
	वापस (le16_to_cpu(hcs) & HUB_CHAR_LPSM) < HUB_CHAR_NO_LPSM;
पूर्ण

अटल अंतरभूत पूर्णांक hub_is_superspeed(काष्ठा usb_device *hdev)
अणु
	वापस hdev->descriptor.bDeviceProtocol == USB_HUB_PR_SS;
पूर्ण

अटल अंतरभूत पूर्णांक hub_is_superspeedplus(काष्ठा usb_device *hdev)
अणु
	वापस (hdev->descriptor.bDeviceProtocol == USB_HUB_PR_SS &&
		le16_to_cpu(hdev->descriptor.bcdUSB) >= 0x0310 &&
		hdev->bos->ssp_cap);
पूर्ण

अटल अंतरभूत अचिन्हित hub_घातer_on_good_delay(काष्ठा usb_hub *hub)
अणु
	अचिन्हित delay = hub->descriptor->bPwrOn2PwrGood * 2;

	अगर (!hub->hdev->parent)	/* root hub */
		वापस delay;
	अन्यथा /* Wait at least 100 msec क्रम घातer to become stable */
		वापस max(delay, 100U);
पूर्ण

अटल अंतरभूत पूर्णांक hub_port_debounce_be_connected(काष्ठा usb_hub *hub,
		पूर्णांक port1)
अणु
	वापस hub_port_debounce(hub, port1, true);
पूर्ण

अटल अंतरभूत पूर्णांक hub_port_debounce_be_stable(काष्ठा usb_hub *hub,
		पूर्णांक port1)
अणु
	वापस hub_port_debounce(hub, port1, false);
पूर्ण
