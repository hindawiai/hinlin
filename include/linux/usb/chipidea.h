<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Platक्रमm data क्रम the chipidea USB dual role controller
 */

#अगर_अघोषित __LINUX_USB_CHIPIDEA_H
#घोषणा __LINUX_USB_CHIPIDEA_H

#समावेश <linux/extcon.h>
#समावेश <linux/usb/otg.h>

काष्ठा ci_hdrc;

/**
 * काष्ठा ci_hdrc_cable - काष्ठाure क्रम बाह्यal connector cable state tracking
 * @connected: true अगर cable is connected, false otherwise
 * @changed: set to true when extcon event happen
 * @enabled: set to true अगर we've enabled the vbus or id पूर्णांकerrupt
 * @edev: device which generate events
 * @ci: driver state of the chipidea device
 * @nb: hold event notअगरication callback
 * @conn: used क्रम notअगरication registration
 */
काष्ठा ci_hdrc_cable अणु
	bool				connected;
	bool				changed;
	bool				enabled;
	काष्ठा extcon_dev		*edev;
	काष्ठा ci_hdrc			*ci;
	काष्ठा notअगरier_block		nb;
पूर्ण;

काष्ठा ci_hdrc_platक्रमm_data अणु
	स्थिर अक्षर	*name;
	/* offset of the capability रेजिस्टरs */
	uपूर्णांकptr_t	 capoffset;
	अचिन्हित	 घातer_budget;
	काष्ठा phy	*phy;
	/* old usb_phy पूर्णांकerface */
	काष्ठा usb_phy	*usb_phy;
	क्रमागत usb_phy_पूर्णांकerface phy_mode;
	अचिन्हित दीर्घ	 flags;
#घोषणा CI_HDRC_REGS_SHARED		BIT(0)
#घोषणा CI_HDRC_DISABLE_DEVICE_STREAMING	BIT(1)
#घोषणा CI_HDRC_SUPPORTS_RUNTIME_PM	BIT(2)
#घोषणा CI_HDRC_DISABLE_HOST_STREAMING	BIT(3)
#घोषणा CI_HDRC_DISABLE_STREAMING (CI_HDRC_DISABLE_DEVICE_STREAMING |	\
		CI_HDRC_DISABLE_HOST_STREAMING)
	/*
	 * Only set it when DCCPARAMS.DC==1 and DCCPARAMS.HC==1,
	 * but otg is not supported (no रेजिस्टर otgsc).
	 */
#घोषणा CI_HDRC_DUAL_ROLE_NOT_OTG	BIT(4)
#घोषणा CI_HDRC_IMX28_WRITE_FIX		BIT(5)
#घोषणा CI_HDRC_FORCE_FULLSPEED		BIT(6)
#घोषणा CI_HDRC_TURN_VBUS_EARLY_ON	BIT(7)
#घोषणा CI_HDRC_SET_NON_ZERO_TTHA	BIT(8)
#घोषणा CI_HDRC_OVERRIDE_AHB_BURST	BIT(9)
#घोषणा CI_HDRC_OVERRIDE_TX_BURST	BIT(10)
#घोषणा CI_HDRC_OVERRIDE_RX_BURST	BIT(11)
#घोषणा CI_HDRC_OVERRIDE_PHY_CONTROL	BIT(12) /* Glue layer manages phy */
#घोषणा CI_HDRC_REQUIRES_ALIGNED_DMA	BIT(13)
#घोषणा CI_HDRC_IMX_IS_HSIC		BIT(14)
#घोषणा CI_HDRC_PMQOS			BIT(15)
	क्रमागत usb_dr_mode	dr_mode;
#घोषणा CI_HDRC_CONTROLLER_RESET_EVENT		0
#घोषणा CI_HDRC_CONTROLLER_STOPPED_EVENT	1
#घोषणा CI_HDRC_IMX_HSIC_ACTIVE_EVENT		2
#घोषणा CI_HDRC_IMX_HSIC_SUSPEND_EVENT		3
#घोषणा CI_HDRC_CONTROLLER_VBUS_EVENT		4
	पूर्णांक	(*notअगरy_event) (काष्ठा ci_hdrc *ci, अचिन्हित event);
	काष्ठा regulator	*reg_vbus;
	काष्ठा usb_otg_caps	ci_otg_caps;
	bool			tpl_support;
	/* पूर्णांकerrupt threshold setting */
	u32			itc_setting;
	u32			ahb_burst_config;
	u32			tx_burst_size;
	u32			rx_burst_size;

	/* VBUS and ID संकेत state tracking, using extcon framework */
	काष्ठा ci_hdrc_cable		vbus_extcon;
	काष्ठा ci_hdrc_cable		id_extcon;
	u32			phy_clkgate_delay_us;

	/* pins */
	काष्ठा pinctrl *pctl;
	काष्ठा pinctrl_state *pins_शेष;
	काष्ठा pinctrl_state *pins_host;
	काष्ठा pinctrl_state *pins_device;

	/* platक्रमm-specअगरic hooks */
	पूर्णांक (*hub_control)(काष्ठा ci_hdrc *ci, u16 typeReq, u16 wValue,
			   u16 wIndex, अक्षर *buf, u16 wLength,
			   bool *करोne, अचिन्हित दीर्घ *flags);
	व्योम (*enter_lpm)(काष्ठा ci_hdrc *ci, bool enable);
पूर्ण;

/* Default offset of capability रेजिस्टरs */
#घोषणा DEF_CAPOFFSET		0x100

/* Add ci hdrc device */
काष्ठा platक्रमm_device *ci_hdrc_add_device(काष्ठा device *dev,
			काष्ठा resource *res, पूर्णांक nres,
			काष्ठा ci_hdrc_platक्रमm_data *platdata);
/* Remove ci hdrc device */
व्योम ci_hdrc_हटाओ_device(काष्ठा platक्रमm_device *pdev);
/* Get current available role */
क्रमागत usb_dr_mode ci_hdrc_query_available_role(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर
