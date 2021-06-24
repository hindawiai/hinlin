<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_HPD_H_
#घोषणा _DP_HPD_H_

//#समावेश <linux/usb/usbpd.h>

#समावेश <linux/types.h>
#समावेश <linux/device.h>

क्रमागत plug_orientation अणु
	ORIENTATION_NONE,
	ORIENTATION_CC1,
	ORIENTATION_CC2,
पूर्ण;

/**
 * काष्ठा dp_usbpd - DisplayPort status
 *
 * @orientation: plug orientation configuration
 * @low_घात_st: low घातer state
 * @adaptor_dp_en: adaptor functionality enabled
 * @multi_func: multi-function preferred
 * @usb_config_req: request to चयन to usb
 * @निकास_dp_mode: request निकास from displayport mode
 * @hpd_high: Hot Plug Detect संकेत is high.
 * @hpd_irq: Change in the status since last message
 * @alt_mode_cfg_करोne: bool to specअगरy alt mode status
 * @debug_en: bool to specअगरy debug mode
 * @connect: simulate disconnect or connect क्रम debug mode
 */
काष्ठा dp_usbpd अणु
	क्रमागत plug_orientation orientation;
	bool low_घात_st;
	bool adaptor_dp_en;
	bool multi_func;
	bool usb_config_req;
	bool निकास_dp_mode;
	bool hpd_high;
	bool hpd_irq;
	bool alt_mode_cfg_करोne;
	bool debug_en;

	पूर्णांक (*connect)(काष्ठा dp_usbpd *dp_usbpd, bool hpd);
पूर्ण;

/**
 * काष्ठा dp_usbpd_cb - callback functions provided by the client
 *
 * @configure: called by usbpd module when PD communication has
 * been completed and the usb peripheral has been configured on
 * dp mode.
 * @disconnect: notअगरy the cable disconnect issued by usb.
 * @attention: notअगरy any attention message issued by usb.
 */
काष्ठा dp_usbpd_cb अणु
	पूर्णांक (*configure)(काष्ठा device *dev);
	पूर्णांक (*disconnect)(काष्ठा device *dev);
	पूर्णांक (*attention)(काष्ठा device *dev);
पूर्ण;

/**
 * dp_hpd_get() - setup hpd module
 *
 * @dev: device instance of the caller
 * @cb: काष्ठा containing callback function poपूर्णांकers.
 *
 * This function allows the client to initialize the usbpd
 * module. The module will communicate with HPD module.
 */
काष्ठा dp_usbpd *dp_hpd_get(काष्ठा device *dev, काष्ठा dp_usbpd_cb *cb);

पूर्णांक dp_hpd_रेजिस्टर(काष्ठा dp_usbpd *dp_usbpd);
व्योम dp_hpd_unरेजिस्टर(काष्ठा dp_usbpd *dp_usbpd);
पूर्णांक dp_hpd_connect(काष्ठा dp_usbpd *dp_usbpd, bool hpd);

#पूर्ण_अगर /* _DP_HPD_H_ */
