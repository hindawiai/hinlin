<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Elan I2C/SMBus Touchpad driver
 *
 * Copyright (c) 2013 ELAN Microelectronics Corp.
 *
 * Author: ौौडॉघऐ (Duson Lin) <dusonlin@emc.com.tw>
 *
 * Based on cyapa driver:
 * copyright (c) 2011-2012 Cypress Semiconductor, Inc.
 * copyright (c) 2011-2012 Google, Inc.
 *
 * Trademarks are the property of their respective owners.
 */

#अगर_अघोषित _ELAN_I2C_H
#घोषणा _ELAN_I2C_H

#समावेश <linux/types.h>

#घोषणा ETP_ENABLE_ABS		0x0001
#घोषणा ETP_ENABLE_CALIBRATE	0x0002
#घोषणा ETP_DISABLE_CALIBRATE	0x0000
#घोषणा ETP_DISABLE_POWER	0x0001
#घोषणा ETP_PRESSURE_OFFSET	25

#घोषणा ETP_CALIBRATE_MAX_LEN	3

#घोषणा ETP_FEATURE_REPORT_MK	BIT(0)

#घोषणा ETP_REPORT_ID		0x5D
#घोषणा ETP_TP_REPORT_ID	0x5E
#घोषणा ETP_TP_REPORT_ID2	0x5F
#घोषणा ETP_REPORT_ID2		0x60	/* High precision report */

#घोषणा ETP_REPORT_ID_OFFSET	2
#घोषणा ETP_TOUCH_INFO_OFFSET	3
#घोषणा ETP_FINGER_DATA_OFFSET	4
#घोषणा ETP_HOVER_INFO_OFFSET	30
#घोषणा ETP_MK_DATA_OFFSET	33	/* For high precision reports */

#घोषणा ETP_MAX_REPORT_LEN	39

#घोषणा ETP_MAX_FINGERS		5
#घोषणा ETP_FINGER_DATA_LEN	5

/* IAP Firmware handling */
#घोषणा ETP_PRODUCT_ID_FORMAT_STRING	"%d.0"
#घोषणा ETP_FW_NAME		"elan_i2c_" ETP_PRODUCT_ID_FORMAT_STRING ".bin"
#घोषणा ETP_IAP_START_ADDR	0x0083
#घोषणा ETP_FW_IAP_PAGE_ERR	(1 << 5)
#घोषणा ETP_FW_IAP_INTF_ERR	(1 << 4)
#घोषणा ETP_FW_PAGE_SIZE	64
#घोषणा ETP_FW_PAGE_SIZE_128	128
#घोषणा ETP_FW_PAGE_SIZE_512	512
#घोषणा ETP_FW_SIGNATURE_SIZE	6

#घोषणा ETP_PRODUCT_ID_DELBIN	0x00C2
#घोषणा ETP_PRODUCT_ID_VOXEL	0x00BF
#घोषणा ETP_PRODUCT_ID_MAGPIE	0x0120
#घोषणा ETP_PRODUCT_ID_BOBBA	0x0121

काष्ठा i2c_client;
काष्ठा completion;

क्रमागत tp_mode अणु
	IAP_MODE = 1,
	MAIN_MODE
पूर्ण;

काष्ठा elan_transport_ops अणु
	पूर्णांक (*initialize)(काष्ठा i2c_client *client);
	पूर्णांक (*sleep_control)(काष्ठा i2c_client *, bool sleep);
	पूर्णांक (*घातer_control)(काष्ठा i2c_client *, bool enable);
	पूर्णांक (*set_mode)(काष्ठा i2c_client *client, u8 mode);

	पूर्णांक (*calibrate)(काष्ठा i2c_client *client);
	पूर्णांक (*calibrate_result)(काष्ठा i2c_client *client, u8 *val);

	पूर्णांक (*get_baseline_data)(काष्ठा i2c_client *client,
				 bool max_baseline, u8 *value);

	पूर्णांक (*get_version)(काष्ठा i2c_client *client, u8 pattern, bool iap,
			   u8 *version);
	पूर्णांक (*get_sm_version)(काष्ठा i2c_client *client, u8 pattern,
			      u16 *ic_type, u8 *version, u8 *clickpad);
	पूर्णांक (*get_checksum)(काष्ठा i2c_client *client, bool iap, u16 *csum);
	पूर्णांक (*get_product_id)(काष्ठा i2c_client *client, u16 *id);

	पूर्णांक (*get_max)(काष्ठा i2c_client *client,
		       अचिन्हित पूर्णांक *max_x, अचिन्हित पूर्णांक *max_y);
	पूर्णांक (*get_resolution)(काष्ठा i2c_client *client,
			      u8 *hw_res_x, u8 *hw_res_y);
	पूर्णांक (*get_num_traces)(काष्ठा i2c_client *client,
			      अचिन्हित पूर्णांक *x_tracक्रमागत,
			      अचिन्हित पूर्णांक *y_tracक्रमागत);

	पूर्णांक (*iap_get_mode)(काष्ठा i2c_client *client, क्रमागत tp_mode *mode);
	पूर्णांक (*iap_reset)(काष्ठा i2c_client *client);

	पूर्णांक (*prepare_fw_update)(काष्ठा i2c_client *client, u16 ic_type,
				 u8 iap_version, u16 fw_page_size);
	पूर्णांक (*ग_लिखो_fw_block)(काष्ठा i2c_client *client, u16 fw_page_size,
			      स्थिर u8 *page, u16 checksum, पूर्णांक idx);
	पूर्णांक (*finish_fw_update)(काष्ठा i2c_client *client,
				काष्ठा completion *reset_करोne);

	पूर्णांक (*get_report_features)(काष्ठा i2c_client *client, u8 pattern,
				   अचिन्हित पूर्णांक *features,
				   अचिन्हित पूर्णांक *report_len);
	पूर्णांक (*get_report)(काष्ठा i2c_client *client, u8 *report,
			  अचिन्हित पूर्णांक report_len);
	पूर्णांक (*get_pressure_adjusपंचांगent)(काष्ठा i2c_client *client,
				       पूर्णांक *adjusपंचांगent);
	पूर्णांक (*get_pattern)(काष्ठा i2c_client *client, u8 *pattern);
पूर्ण;

बाह्य स्थिर काष्ठा elan_transport_ops elan_smbus_ops, elan_i2c_ops;

#पूर्ण_अगर /* _ELAN_I2C_H */
