<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * u_ether.h -- पूर्णांकerface to USB gadget "ethernet link" utilities
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2003-2004 Robert Schwebel, Benedikt Spranger
 * Copyright (C) 2008 Nokia Corporation
 */

#अगर_अघोषित __U_ETHER_H
#घोषणा __U_ETHER_H

#समावेश <linux/err.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/netdevice.h>

#घोषणा QMULT_DEFAULT 5

/*
 * dev_addr: initial value
 * changed by "ifconfig usb0 hw ether xx:xx:xx:xx:xx:xx"
 * host_addr: this address is invisible to अगरconfig
 */
#घोषणा USB_ETHERNET_MODULE_PARAMETERS() \
	अटल अचिन्हित qmult = QMULT_DEFAULT;				\
	module_param(qmult, uपूर्णांक, S_IRUGO|S_IWUSR);			\
	MODULE_PARM_DESC(qmult, "queue length multiplier at high/super speed");\
									\
	अटल अक्षर *dev_addr;						\
	module_param(dev_addr, अक्षरp, S_IRUGO);				\
	MODULE_PARM_DESC(dev_addr, "Device Ethernet Address");		\
									\
	अटल अक्षर *host_addr;						\
	module_param(host_addr, अक्षरp, S_IRUGO);			\
	MODULE_PARM_DESC(host_addr, "Host Ethernet Address")

काष्ठा eth_dev;

/*
 * This represents the USB side of an "ethernet" link, managed by a USB
 * function which provides control and (maybe) framing.  Two functions
 * in dअगरferent configurations could share the same ethernet link/netdev,
 * using dअगरferent host पूर्णांकeraction models.
 *
 * There is a current limitation that only one instance of this link may
 * be present in any given configuration.  When that's a problem, network
 * layer facilities can be used to package multiple logical links on this
 * single "physical" one.
 */
काष्ठा gether अणु
	काष्ठा usb_function		func;

	/* updated by gether_अणुconnect,disconnectपूर्ण */
	काष्ठा eth_dev			*ioport;

	/* endpoपूर्णांकs handle full and/or high speeds */
	काष्ठा usb_ep			*in_ep;
	काष्ठा usb_ep			*out_ep;

	bool				is_zlp_ok;

	u16				cdc_filter;

	/* hooks क्रम added framing, as needed क्रम RNDIS and EEM. */
	u32				header_len;
	/* NCM requires fixed size bundles */
	bool				is_fixed;
	u32				fixed_out_len;
	u32				fixed_in_len;
	bool				supports_multi_frame;
	काष्ठा sk_buff			*(*wrap)(काष्ठा gether *port,
						काष्ठा sk_buff *skb);
	पूर्णांक				(*unwrap)(काष्ठा gether *port,
						काष्ठा sk_buff *skb,
						काष्ठा sk_buff_head *list);

	/* called on network खोलो/बंद */
	व्योम				(*खोलो)(काष्ठा gether *);
	व्योम				(*बंद)(काष्ठा gether *);
पूर्ण;

#घोषणा	DEFAULT_FILTER	(USB_CDC_PACKET_TYPE_BROADCAST \
			|USB_CDC_PACKET_TYPE_ALL_MULTICAST \
			|USB_CDC_PACKET_TYPE_PROMISCUOUS \
			|USB_CDC_PACKET_TYPE_सूचीECTED)

/* variant of gether_setup that allows customizing network device name */
काष्ठा eth_dev *gether_setup_name(काष्ठा usb_gadget *g,
		स्थिर अक्षर *dev_addr, स्थिर अक्षर *host_addr,
		u8 ethaddr[ETH_ALEN], अचिन्हित qmult, स्थिर अक्षर *netname);

/* netdev setup/tearकरोwn as directed by the gadget driver */
/* gether_setup - initialize one ethernet-over-usb link
 * @g: gadget to associated with these links
 * @ethaddr: शून्य, or a buffer in which the ethernet address of the
 *	host side of the link is recorded
 * Context: may sleep
 *
 * This sets up the single network link that may be exported by a
 * gadget driver using this framework.  The link layer addresses are
 * set up using module parameters.
 *
 * Returns a eth_dev poपूर्णांकer on success, or an ERR_PTR on failure
 */
अटल अंतरभूत काष्ठा eth_dev *gether_setup(काष्ठा usb_gadget *g,
		स्थिर अक्षर *dev_addr, स्थिर अक्षर *host_addr,
		u8 ethaddr[ETH_ALEN], अचिन्हित qmult)
अणु
	वापस gether_setup_name(g, dev_addr, host_addr, ethaddr, qmult, "usb");
पूर्ण

/*
 * variant of gether_setup_शेष that allows customizing
 * network device name
 */
काष्ठा net_device *gether_setup_name_शेष(स्थिर अक्षर *netname);

/*
 * gether_रेजिस्टर_netdev - रेजिस्टर the net device
 * @net: net device to रेजिस्टर
 *
 * Registers the net device associated with this ethernet-over-usb link
 *
 */
पूर्णांक gether_रेजिस्टर_netdev(काष्ठा net_device *net);

/* gether_setup_शेष - initialize one ethernet-over-usb link
 * Context: may sleep
 *
 * This sets up the single network link that may be exported by a
 * gadget driver using this framework.  The link layer addresses
 * are set to अक्रमom values.
 *
 * Returns negative त्रुटि_सं, or zero on success
 */
अटल अंतरभूत काष्ठा net_device *gether_setup_शेष(व्योम)
अणु
	वापस gether_setup_name_शेष("usb");
पूर्ण

/**
 * gether_set_gadget - initialize one ethernet-over-usb link with a gadget
 * @net: device representing this link
 * @g: the gadget to initialize with
 *
 * This associates one ethernet-over-usb link with a gadget.
 */
व्योम gether_set_gadget(काष्ठा net_device *net, काष्ठा usb_gadget *g);

/**
 * gether_set_dev_addr - initialize an ethernet-over-usb link with eth address
 * @net: device representing this link
 * @dev_addr: eth address of this device
 *
 * This sets the device-side Ethernet address of this ethernet-over-usb link
 * अगर dev_addr is correct.
 * Returns negative त्रुटि_सं अगर the new address is incorrect.
 */
पूर्णांक gether_set_dev_addr(काष्ठा net_device *net, स्थिर अक्षर *dev_addr);

/**
 * gether_get_dev_addr - get an ethernet-over-usb link eth address
 * @net: device representing this link
 * @dev_addr: place to store device's eth address
 * @len: length of the @dev_addr buffer
 *
 * This माला_लो the device-side Ethernet address of this ethernet-over-usb link.
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक gether_get_dev_addr(काष्ठा net_device *net, अक्षर *dev_addr, पूर्णांक len);

/**
 * gether_set_host_addr - initialize an ethernet-over-usb link with host address
 * @net: device representing this link
 * @host_addr: eth address of the host
 *
 * This sets the host-side Ethernet address of this ethernet-over-usb link
 * अगर host_addr is correct.
 * Returns negative त्रुटि_सं अगर the new address is incorrect.
 */
पूर्णांक gether_set_host_addr(काष्ठा net_device *net, स्थिर अक्षर *host_addr);

/**
 * gether_get_host_addr - get an ethernet-over-usb link host address
 * @net: device representing this link
 * @host_addr: place to store eth address of the host
 * @len: length of the @host_addr buffer
 *
 * This माला_लो the host-side Ethernet address of this ethernet-over-usb link.
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक gether_get_host_addr(काष्ठा net_device *net, अक्षर *host_addr, पूर्णांक len);

/**
 * gether_get_host_addr_cdc - get an ethernet-over-usb link host address
 * @net: device representing this link
 * @host_addr: place to store eth address of the host
 * @len: length of the @host_addr buffer
 *
 * This माला_लो the CDC क्रमmatted host-side Ethernet address of this
 * ethernet-over-usb link.
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक gether_get_host_addr_cdc(काष्ठा net_device *net, अक्षर *host_addr, पूर्णांक len);

/**
 * gether_get_host_addr_u8 - get an ethernet-over-usb link host address
 * @net: device representing this link
 * @host_mac: place to store the eth address of the host
 *
 * This माला_लो the binary क्रमmatted host-side Ethernet address of this
 * ethernet-over-usb link.
 */
व्योम gether_get_host_addr_u8(काष्ठा net_device *net, u8 host_mac[ETH_ALEN]);

/**
 * gether_set_qmult - initialize an ethernet-over-usb link with a multiplier
 * @net: device representing this link
 * @qmult: queue multiplier
 *
 * This sets the queue length multiplier of this ethernet-over-usb link.
 * For higher speeds use दीर्घer queues.
 */
व्योम gether_set_qmult(काष्ठा net_device *net, अचिन्हित qmult);

/**
 * gether_get_qmult - get an ethernet-over-usb link multiplier
 * @net: device representing this link
 *
 * This माला_लो the queue length multiplier of this ethernet-over-usb link.
 */
अचिन्हित gether_get_qmult(काष्ठा net_device *net);

/**
 * gether_get_अगरname - get an ethernet-over-usb link पूर्णांकerface name
 * @net: device representing this link
 * @name: place to store the पूर्णांकerface name
 * @len: length of the @name buffer
 *
 * This माला_लो the पूर्णांकerface name of this ethernet-over-usb link.
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक gether_get_अगरname(काष्ठा net_device *net, अक्षर *name, पूर्णांक len);

/**
 * gether_set_अगरname - set an ethernet-over-usb link पूर्णांकerface name
 * @net: device representing this link
 * @name: new पूर्णांकerface name
 * @len: length of @name
 *
 * This sets the पूर्णांकerface name of this ethernet-over-usb link.
 * A single terminating newline, अगर any, is ignored.
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक gether_set_अगरname(काष्ठा net_device *net, स्थिर अक्षर *name, पूर्णांक len);

व्योम gether_cleanup(काष्ठा eth_dev *dev);

/* connect/disconnect is handled by inभागidual functions */
काष्ठा net_device *gether_connect(काष्ठा gether *);
व्योम gether_disconnect(काष्ठा gether *);

/* Some controllers can't support CDC Ethernet (ECM) ... */
अटल अंतरभूत bool can_support_ecm(काष्ठा usb_gadget *gadget)
अणु
	अगर (!gadget_is_altset_supported(gadget))
		वापस false;

	/* Everything अन्यथा is *presumably* fine ... but this is a bit
	 * chancy, so be **CERTAIN** there are no hardware issues with
	 * your controller.  Add it above अगर it can't handle CDC.
	 */
	वापस true;
पूर्ण

#पूर्ण_अगर /* __U_ETHER_H */
