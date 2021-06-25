<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * USB PHY defines
 *
 * These APIs may be used between USB controllers.  USB device drivers
 * (क्रम either host or peripheral roles) करोn't use these calls; they
 * जारी to use just usb_device and usb_gadget.
 */

#अगर_अघोषित __LINUX_USB_PHY_H
#घोषणा __LINUX_USB_PHY_H

#समावेश <linux/extcon.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/usb.h>
#समावेश <uapi/linux/usb/अक्षरger.h>

क्रमागत usb_phy_पूर्णांकerface अणु
	USBPHY_INTERFACE_MODE_UNKNOWN,
	USBPHY_INTERFACE_MODE_UTMI,
	USBPHY_INTERFACE_MODE_UTMIW,
	USBPHY_INTERFACE_MODE_ULPI,
	USBPHY_INTERFACE_MODE_SERIAL,
	USBPHY_INTERFACE_MODE_HSIC,
पूर्ण;

क्रमागत usb_phy_events अणु
	USB_EVENT_NONE,         /* no events or cable disconnected */
	USB_EVENT_VBUS,         /* vbus valid event */
	USB_EVENT_ID,           /* id was grounded */
	USB_EVENT_CHARGER,      /* usb dedicated अक्षरger */
	USB_EVENT_ENUMERATED,   /* gadget driver क्रमागतerated */
पूर्ण;

/* associate a type with PHY */
क्रमागत usb_phy_type अणु
	USB_PHY_TYPE_UNDEFINED,
	USB_PHY_TYPE_USB2,
	USB_PHY_TYPE_USB3,
पूर्ण;

/* OTG defines lots of क्रमागतeration states beक्रमe device reset */
क्रमागत usb_otg_state अणु
	OTG_STATE_UNDEFINED = 0,

	/* single-role peripheral, and dual-role शेष-b */
	OTG_STATE_B_IDLE,
	OTG_STATE_B_SRP_INIT,
	OTG_STATE_B_PERIPHERAL,

	/* extra dual-role शेष-b states */
	OTG_STATE_B_WAIT_ACON,
	OTG_STATE_B_HOST,

	/* dual-role शेष-a */
	OTG_STATE_A_IDLE,
	OTG_STATE_A_WAIT_VRISE,
	OTG_STATE_A_WAIT_BCON,
	OTG_STATE_A_HOST,
	OTG_STATE_A_SUSPEND,
	OTG_STATE_A_PERIPHERAL,
	OTG_STATE_A_WAIT_VFALL,
	OTG_STATE_A_VBUS_ERR,
पूर्ण;

काष्ठा usb_phy;
काष्ठा usb_otg;

/* क्रम phys connected thru an ULPI पूर्णांकerface, the user must
 * provide access ops
 */
काष्ठा usb_phy_io_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा usb_phy *x, u32 reg);
	पूर्णांक (*ग_लिखो)(काष्ठा usb_phy *x, u32 val, u32 reg);
पूर्ण;

काष्ठा usb_अक्षरger_current अणु
	अचिन्हित पूर्णांक sdp_min;
	अचिन्हित पूर्णांक sdp_max;
	अचिन्हित पूर्णांक dcp_min;
	अचिन्हित पूर्णांक dcp_max;
	अचिन्हित पूर्णांक cdp_min;
	अचिन्हित पूर्णांक cdp_max;
	अचिन्हित पूर्णांक aca_min;
	अचिन्हित पूर्णांक aca_max;
पूर्ण;

काष्ठा usb_phy अणु
	काष्ठा device		*dev;
	स्थिर अक्षर		*label;
	अचिन्हित पूर्णांक		 flags;

	क्रमागत usb_phy_type	type;
	क्रमागत usb_phy_events	last_event;

	काष्ठा usb_otg		*otg;

	काष्ठा device		*io_dev;
	काष्ठा usb_phy_io_ops	*io_ops;
	व्योम __iomem		*io_priv;

	/* to support extcon device */
	काष्ठा extcon_dev	*edev;
	काष्ठा extcon_dev	*id_edev;
	काष्ठा notअगरier_block	vbus_nb;
	काष्ठा notअगरier_block	id_nb;
	काष्ठा notअगरier_block	type_nb;

	/* Support USB अक्षरger */
	क्रमागत usb_अक्षरger_type	chg_type;
	क्रमागत usb_अक्षरger_state	chg_state;
	काष्ठा usb_अक्षरger_current	chg_cur;
	काष्ठा work_काष्ठा		chg_work;

	/* क्रम notअगरication of usb_phy_events */
	काष्ठा atomic_notअगरier_head	notअगरier;

	/* to pass extra port status to the root hub */
	u16			port_status;
	u16			port_change;

	/* to support controllers that have multiple phys */
	काष्ठा list_head	head;

	/* initialize/shutकरोwn the phy */
	पूर्णांक	(*init)(काष्ठा usb_phy *x);
	व्योम	(*shutकरोwn)(काष्ठा usb_phy *x);

	/* enable/disable VBUS */
	पूर्णांक	(*set_vbus)(काष्ठा usb_phy *x, पूर्णांक on);

	/* effective क्रम B devices, ignored क्रम A-peripheral */
	पूर्णांक	(*set_घातer)(काष्ठा usb_phy *x,
				अचिन्हित mA);

	/* Set phy पूर्णांकo suspend mode */
	पूर्णांक	(*set_suspend)(काष्ठा usb_phy *x,
				पूर्णांक suspend);

	/*
	 * Set wakeup enable क्रम PHY, in that हाल, the PHY can be
	 * woken up from suspend status due to बाह्यal events,
	 * like vbus change, dp/dm change and id.
	 */
	पूर्णांक	(*set_wakeup)(काष्ठा usb_phy *x, bool enabled);

	/* notअगरy phy connect status change */
	पूर्णांक	(*notअगरy_connect)(काष्ठा usb_phy *x,
			क्रमागत usb_device_speed speed);
	पूर्णांक	(*notअगरy_disconnect)(काष्ठा usb_phy *x,
			क्रमागत usb_device_speed speed);

	/*
	 * Charger detection method can be implemented अगर you need to
	 * manually detect the अक्षरger type.
	 */
	क्रमागत usb_अक्षरger_type (*अक्षरger_detect)(काष्ठा usb_phy *x);
पूर्ण;

/* क्रम board-specअगरic init logic */
बाह्य पूर्णांक usb_add_phy(काष्ठा usb_phy *, क्रमागत usb_phy_type type);
बाह्य पूर्णांक usb_add_phy_dev(काष्ठा usb_phy *);
बाह्य व्योम usb_हटाओ_phy(काष्ठा usb_phy *);

/* helpers क्रम direct access thru low-level io पूर्णांकerface */
अटल अंतरभूत पूर्णांक usb_phy_io_पढ़ो(काष्ठा usb_phy *x, u32 reg)
अणु
	अगर (x && x->io_ops && x->io_ops->पढ़ो)
		वापस x->io_ops->पढ़ो(x, reg);

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक usb_phy_io_ग_लिखो(काष्ठा usb_phy *x, u32 val, u32 reg)
अणु
	अगर (x && x->io_ops && x->io_ops->ग_लिखो)
		वापस x->io_ops->ग_लिखो(x, val, reg);

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
usb_phy_init(काष्ठा usb_phy *x)
अणु
	अगर (x && x->init)
		वापस x->init(x);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
usb_phy_shutकरोwn(काष्ठा usb_phy *x)
अणु
	अगर (x && x->shutकरोwn)
		x->shutकरोwn(x);
पूर्ण

अटल अंतरभूत पूर्णांक
usb_phy_vbus_on(काष्ठा usb_phy *x)
अणु
	अगर (!x || !x->set_vbus)
		वापस 0;

	वापस x->set_vbus(x, true);
पूर्ण

अटल अंतरभूत पूर्णांक
usb_phy_vbus_off(काष्ठा usb_phy *x)
अणु
	अगर (!x || !x->set_vbus)
		वापस 0;

	वापस x->set_vbus(x, false);
पूर्ण

/* क्रम usb host and peripheral controller drivers */
#अगर IS_ENABLED(CONFIG_USB_PHY)
बाह्य काष्ठा usb_phy *usb_get_phy(क्रमागत usb_phy_type type);
बाह्य काष्ठा usb_phy *devm_usb_get_phy(काष्ठा device *dev,
	क्रमागत usb_phy_type type);
बाह्य काष्ठा usb_phy *devm_usb_get_phy_by_phandle(काष्ठा device *dev,
	स्थिर अक्षर *phandle, u8 index);
बाह्य काष्ठा usb_phy *devm_usb_get_phy_by_node(काष्ठा device *dev,
	काष्ठा device_node *node, काष्ठा notअगरier_block *nb);
बाह्य व्योम usb_put_phy(काष्ठा usb_phy *);
बाह्य व्योम devm_usb_put_phy(काष्ठा device *dev, काष्ठा usb_phy *x);
बाह्य व्योम usb_phy_set_event(काष्ठा usb_phy *x, अचिन्हित दीर्घ event);
बाह्य व्योम usb_phy_set_अक्षरger_current(काष्ठा usb_phy *usb_phy,
					अचिन्हित पूर्णांक mA);
बाह्य व्योम usb_phy_get_अक्षरger_current(काष्ठा usb_phy *usb_phy,
					अचिन्हित पूर्णांक *min, अचिन्हित पूर्णांक *max);
बाह्य व्योम usb_phy_set_अक्षरger_state(काष्ठा usb_phy *usb_phy,
				      क्रमागत usb_अक्षरger_state state);
#अन्यथा
अटल अंतरभूत काष्ठा usb_phy *usb_get_phy(क्रमागत usb_phy_type type)
अणु
	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल अंतरभूत काष्ठा usb_phy *devm_usb_get_phy(काष्ठा device *dev,
	क्रमागत usb_phy_type type)
अणु
	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल अंतरभूत काष्ठा usb_phy *devm_usb_get_phy_by_phandle(काष्ठा device *dev,
	स्थिर अक्षर *phandle, u8 index)
अणु
	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल अंतरभूत काष्ठा usb_phy *devm_usb_get_phy_by_node(काष्ठा device *dev,
	काष्ठा device_node *node, काष्ठा notअगरier_block *nb)
अणु
	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल अंतरभूत व्योम usb_put_phy(काष्ठा usb_phy *x)
अणु
पूर्ण

अटल अंतरभूत व्योम devm_usb_put_phy(काष्ठा device *dev, काष्ठा usb_phy *x)
अणु
पूर्ण

अटल अंतरभूत व्योम usb_phy_set_event(काष्ठा usb_phy *x, अचिन्हित दीर्घ event)
अणु
पूर्ण

अटल अंतरभूत व्योम usb_phy_set_अक्षरger_current(काष्ठा usb_phy *usb_phy,
					       अचिन्हित पूर्णांक mA)
अणु
पूर्ण

अटल अंतरभूत व्योम usb_phy_get_अक्षरger_current(काष्ठा usb_phy *usb_phy,
					       अचिन्हित पूर्णांक *min,
					       अचिन्हित पूर्णांक *max)
अणु
पूर्ण

अटल अंतरभूत व्योम usb_phy_set_अक्षरger_state(काष्ठा usb_phy *usb_phy,
					     क्रमागत usb_अक्षरger_state state)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
usb_phy_set_घातer(काष्ठा usb_phy *x, अचिन्हित mA)
अणु
	अगर (!x)
		वापस 0;

	usb_phy_set_अक्षरger_current(x, mA);

	अगर (x->set_घातer)
		वापस x->set_घातer(x, mA);
	वापस 0;
पूर्ण

/* Context: can sleep */
अटल अंतरभूत पूर्णांक
usb_phy_set_suspend(काष्ठा usb_phy *x, पूर्णांक suspend)
अणु
	अगर (x && x->set_suspend != शून्य)
		वापस x->set_suspend(x, suspend);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
usb_phy_set_wakeup(काष्ठा usb_phy *x, bool enabled)
अणु
	अगर (x && x->set_wakeup)
		वापस x->set_wakeup(x, enabled);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
usb_phy_notअगरy_connect(काष्ठा usb_phy *x, क्रमागत usb_device_speed speed)
अणु
	अगर (x && x->notअगरy_connect)
		वापस x->notअगरy_connect(x, speed);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
usb_phy_notअगरy_disconnect(काष्ठा usb_phy *x, क्रमागत usb_device_speed speed)
अणु
	अगर (x && x->notअगरy_disconnect)
		वापस x->notअगरy_disconnect(x, speed);
	अन्यथा
		वापस 0;
पूर्ण

/* notअगरiers */
अटल अंतरभूत पूर्णांक
usb_रेजिस्टर_notअगरier(काष्ठा usb_phy *x, काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&x->notअगरier, nb);
पूर्ण

अटल अंतरभूत व्योम
usb_unरेजिस्टर_notअगरier(काष्ठा usb_phy *x, काष्ठा notअगरier_block *nb)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&x->notअगरier, nb);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *usb_phy_type_string(क्रमागत usb_phy_type type)
अणु
	चयन (type) अणु
	हाल USB_PHY_TYPE_USB2:
		वापस "USB2 PHY";
	हाल USB_PHY_TYPE_USB3:
		वापस "USB3 PHY";
	शेष:
		वापस "UNKNOWN PHY TYPE";
	पूर्ण
पूर्ण
#पूर्ण_अगर /* __LINUX_USB_PHY_H */
