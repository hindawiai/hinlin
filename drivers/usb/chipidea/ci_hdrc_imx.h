<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __DRIVER_USB_CHIPIDEA_CI_HDRC_IMX_H
#घोषणा __DRIVER_USB_CHIPIDEA_CI_HDRC_IMX_H

काष्ठा imx_usbmisc_data अणु
	काष्ठा device *dev;
	पूर्णांक index;

	अचिन्हित पूर्णांक disable_oc:1; /* over current detect disabled */

	/* true अगर over-current polarity is active low */
	अचिन्हित पूर्णांक oc_pol_active_low:1;

	/* true अगर dt specअगरies polarity */
	अचिन्हित पूर्णांक oc_pol_configured:1;

	अचिन्हित पूर्णांक pwr_pol:1; /* घातer polarity */
	अचिन्हित पूर्णांक evकरो:1; /* set बाह्यal vbus भागider option */
	अचिन्हित पूर्णांक ulpi:1; /* connected to an ULPI phy */
	अचिन्हित पूर्णांक hsic:1; /* HSIC controlller */
	अचिन्हित पूर्णांक ext_id:1; /* ID from exteranl event */
	अचिन्हित पूर्णांक ext_vbus:1; /* Vbus from exteranl event */
	काष्ठा usb_phy *usb_phy;
	क्रमागत usb_dr_mode available_role; /* runसमय usb dr mode */
	पूर्णांक emp_curr_control;
	पूर्णांक dc_vol_level_adjust;
पूर्ण;

पूर्णांक imx_usbmisc_init(काष्ठा imx_usbmisc_data *data);
पूर्णांक imx_usbmisc_init_post(काष्ठा imx_usbmisc_data *data);
पूर्णांक imx_usbmisc_set_wakeup(काष्ठा imx_usbmisc_data *data, bool enabled);
पूर्णांक imx_usbmisc_hsic_set_connect(काष्ठा imx_usbmisc_data *data);
पूर्णांक imx_usbmisc_hsic_set_clk(काष्ठा imx_usbmisc_data *data, bool on);
पूर्णांक imx_usbmisc_अक्षरger_detection(काष्ठा imx_usbmisc_data *data, bool connect);

#पूर्ण_अगर /* __DRIVER_USB_CHIPIDEA_CI_HDRC_IMX_H */
