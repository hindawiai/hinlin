<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * eeprom specअगरic definitions क्रम mac80211 Prism54 drivers
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 *
 * - LMAC API पूर्णांकerface header file क्रम STLC4560 (lmac_दीर्घbow.h)
 *   Copyright (C) 2007 Conexant Systems, Inc.
 *
 * - islmvc driver
 *   Copyright (C) 2001 Intersil Americas Inc.
 */

#अगर_अघोषित EEPROM_H
#घोषणा EEPROM_H

/* PDA defines are Copyright (C) 2005 Nokia Corporation (taken from islsm_pda.h) */

काष्ठा pda_entry अणु
	__le16 len;	/* includes both code and data */
	__le16 code;
	u8 data[];
पूर्ण __packed;

काष्ठा eeprom_pda_wrap अणु
	__le32 magic;
	__le16 pad;
	__le16 len;
	__le32 arm_opcode;
	u8 data[];
पूर्ण __packed;

काष्ठा p54_iq_स्वतःcal_entry अणु
	__le16 iq_param[4];
पूर्ण __packed;

काष्ठा pda_iq_स्वतःcal_entry अणु
	__le16 freq;
	काष्ठा p54_iq_स्वतःcal_entry params;
पूर्ण __packed;

काष्ठा pda_channel_output_limit अणु
	__le16 freq;
	u8 val_bpsk;
	u8 val_qpsk;
	u8 val_16qam;
	u8 val_64qam;
	u8 rate_set_mask;
	u8 rate_set_size;
पूर्ण __packed;

काष्ठा pda_channel_output_limit_poपूर्णांक_दीर्घbow अणु
	__le16 val_bpsk;
	__le16 val_qpsk;
	__le16 val_16qam;
	__le16 val_64qam;
पूर्ण __packed;

काष्ठा pda_channel_output_limit_दीर्घbow अणु
	__le16 freq;
	काष्ठा pda_channel_output_limit_poपूर्णांक_दीर्घbow poपूर्णांक[3];
पूर्ण __packed;

काष्ठा pda_pa_curve_data_sample_rev0 अणु
	u8 rf_घातer;
	u8 pa_detector;
	u8 pcv;
पूर्ण __packed;

काष्ठा pda_pa_curve_data_sample_rev1 अणु
	u8 rf_घातer;
	u8 pa_detector;
	u8 data_barker;
	u8 data_bpsk;
	u8 data_qpsk;
	u8 data_16qam;
	u8 data_64qam;
पूर्ण __packed;

काष्ठा pda_pa_curve_data अणु
	u8 cal_method_rev;
	u8 channels;
	u8 poपूर्णांकs_per_channel;
	u8 padding;
	u8 data[];
पूर्ण __packed;

काष्ठा pda_rssi_cal_ext_entry अणु
	__le16 freq;
	__le16 mul;
	__le16 add;
पूर्ण __packed;

काष्ठा pda_rssi_cal_entry अणु
	__le16 mul;
	__le16 add;
पूर्ण __packed;

काष्ठा pda_country अणु
	u8 regकरोमुख्य;
	u8 alpha2[2];
	u8 flags;
पूर्ण __packed;

काष्ठा pda_antenna_gain अणु
	काष्ठा अणु
		u8 gain_5GHz;	/* 0.25 dBi units */
		u8 gain_2GHz;	/* 0.25 dBi units */
	पूर्ण __packed antenna[0];
पूर्ण __packed;

काष्ठा pda_custom_wrapper अणु
	__le16 entries;
	__le16 entry_size;
	__le16 offset;
	__le16 len;
	u8 data[];
पूर्ण __packed;

/*
 * this defines the PDR codes used to build PDAs as defined in करोcument
 * number 553155. The current implementation mirrors version 1.1 of the
 * करोcument and lists only PDRs supported by the ARM platक्रमm.
 */

/* common and choice range (0x0000 - 0x0fff) */
#घोषणा PDR_END					0x0000
#घोषणा PDR_MANUFACTURING_PART_NUMBER		0x0001
#घोषणा PDR_PDA_VERSION				0x0002
#घोषणा PDR_NIC_SERIAL_NUMBER			0x0003
#घोषणा PDR_NIC_RAM_SIZE			0x0005
#घोषणा PDR_RFMODEM_SUP_RANGE			0x0006
#घोषणा PDR_PRISM_MAC_SUP_RANGE			0x0007
#घोषणा PDR_NIC_ID				0x0008

#घोषणा PDR_MAC_ADDRESS				0x0101
#घोषणा PDR_REGULATORY_DOMAIN_LIST		0x0103 /* obsolete */
#घोषणा PDR_ALLOWED_CHAN_SET			0x0104
#घोषणा PDR_DEFAULT_CHAN			0x0105
#घोषणा PDR_TEMPERATURE_TYPE			0x0107

#घोषणा PDR_IFR_SETTING				0x0200
#घोषणा PDR_RFR_SETTING				0x0201
#घोषणा PDR_3861_BASELINE_REG_SETTINGS		0x0202
#घोषणा PDR_3861_SHADOW_REG_SETTINGS		0x0203
#घोषणा PDR_3861_IFRF_REG_SETTINGS		0x0204

#घोषणा PDR_3861_CHAN_CALIB_SET_POINTS		0x0300
#घोषणा PDR_3861_CHAN_CALIB_INTEGRATOR		0x0301

#घोषणा PDR_3842_PRISM_II_NIC_CONFIG		0x0400
#घोषणा PDR_PRISM_USB_ID			0x0401
#घोषणा PDR_PRISM_PCI_ID			0x0402
#घोषणा PDR_PRISM_PCI_IF_CONFIG			0x0403
#घोषणा PDR_PRISM_PCI_PM_CONFIG			0x0404

#घोषणा PDR_3861_MF_TEST_CHAN_SET_POINTS	0x0900
#घोषणा PDR_3861_MF_TEST_CHAN_INTEGRATORS	0x0901

/* ARM range (0x1000 - 0x1fff) */
#घोषणा PDR_COUNTRY_INFORMATION			0x1000 /* obsolete */
#घोषणा PDR_INTERFACE_LIST			0x1001
#घोषणा PDR_HARDWARE_PLATFORM_COMPONENT_ID	0x1002
#घोषणा PDR_OEM_NAME				0x1003
#घोषणा PDR_PRODUCT_NAME			0x1004
#घोषणा PDR_UTF8_OEM_NAME			0x1005
#घोषणा PDR_UTF8_PRODUCT_NAME			0x1006
#घोषणा PDR_COUNTRY_LIST			0x1007
#घोषणा PDR_DEFAULT_COUNTRY			0x1008

#घोषणा PDR_ANTENNA_GAIN			0x1100

#घोषणा PDR_PRISM_INDIGO_PA_CALIBRATION_DATA	0x1901
#घोषणा PDR_RSSI_LINEAR_APPROXIMATION		0x1902
#घोषणा PDR_PRISM_PA_CAL_OUTPUT_POWER_LIMITS	0x1903
#घोषणा PDR_PRISM_PA_CAL_CURVE_DATA		0x1904
#घोषणा PDR_RSSI_LINEAR_APPROXIMATION_DUAL_BAND	0x1905
#घोषणा PDR_PRISM_ZIF_TX_IQ_CALIBRATION		0x1906
#घोषणा PDR_REGULATORY_POWER_LIMITS		0x1907
#घोषणा PDR_RSSI_LINEAR_APPROXIMATION_EXTENDED	0x1908
#घोषणा PDR_RADIATED_TRANSMISSION_CORRECTION	0x1909
#घोषणा PDR_PRISM_TX_IQ_CALIBRATION		0x190a

/* reserved range (0x2000 - 0x7fff) */

/* customer range (0x8000 - 0xffff) */
#घोषणा PDR_BASEBAND_REGISTERS				0x8000
#घोषणा PDR_PER_CHANNEL_BASEBAND_REGISTERS		0x8001

/* used by our modअगरicated eeprom image */
#घोषणा PDR_RSSI_LINEAR_APPROXIMATION_CUSTOM		0xDEAD
#घोषणा PDR_RSSI_LINEAR_APPROXIMATION_CUSTOMV2		0xCAFF
#घोषणा PDR_PRISM_PA_CAL_OUTPUT_POWER_LIMITS_CUSTOM	0xBEEF
#घोषणा PDR_PRISM_PA_CAL_CURVE_DATA_CUSTOM		0xB05D

/* Interface Definitions */
#घोषणा PDR_INTERFACE_ROLE_SERVER	0x0000
#घोषणा PDR_INTERFACE_ROLE_CLIENT	0x0001

/* PDR definitions क्रम शेष country & country list */
#घोषणा PDR_COUNTRY_CERT_CODE		0x80
#घोषणा PDR_COUNTRY_CERT_CODE_REAL	0x00
#घोषणा PDR_COUNTRY_CERT_CODE_PSEUDO	0x80
#घोषणा PDR_COUNTRY_CERT_BAND		0x40
#घोषणा PDR_COUNTRY_CERT_BAND_2GHZ	0x00
#घोषणा PDR_COUNTRY_CERT_BAND_5GHZ	0x40
#घोषणा PDR_COUNTRY_CERT_IODOOR		0x30
#घोषणा PDR_COUNTRY_CERT_IODOOR_BOTH	0x00
#घोषणा PDR_COUNTRY_CERT_IODOOR_INDOOR	0x20
#घोषणा PDR_COUNTRY_CERT_IODOOR_OUTDOOR	0x30
#घोषणा PDR_COUNTRY_CERT_INDEX		0x0f

/* Specअगरic LMAC FW/HW variant definitions */
#घोषणा PDR_SYNTH_FRONTEND_MASK		0x0007
#घोषणा PDR_SYNTH_FRONTEND_DUETTE3	0x0001
#घोषणा PDR_SYNTH_FRONTEND_DUETTE2	0x0002
#घोषणा PDR_SYNTH_FRONTEND_FRISBEE	0x0003
#घोषणा PDR_SYNTH_FRONTEND_XBOW		0x0004
#घोषणा PDR_SYNTH_FRONTEND_LONGBOW	0x0005
#घोषणा PDR_SYNTH_IQ_CAL_MASK		0x0018
#घोषणा PDR_SYNTH_IQ_CAL_PA_DETECTOR	0x0000
#घोषणा PDR_SYNTH_IQ_CAL_DISABLED	0x0008
#घोषणा PDR_SYNTH_IQ_CAL_ZIF		0x0010
#घोषणा PDR_SYNTH_FAA_SWITCH_MASK	0x0020
#घोषणा PDR_SYNTH_FAA_SWITCH_ENABLED	0x0020
#घोषणा PDR_SYNTH_24_GHZ_MASK		0x0040
#घोषणा PDR_SYNTH_24_GHZ_DISABLED	0x0040
#घोषणा PDR_SYNTH_5_GHZ_MASK		0x0080
#घोषणा PDR_SYNTH_5_GHZ_DISABLED	0x0080
#घोषणा PDR_SYNTH_RX_DIV_MASK		0x0100
#घोषणा PDR_SYNTH_RX_DIV_SUPPORTED	0x0100
#घोषणा PDR_SYNTH_TX_DIV_MASK		0x0200
#घोषणा PDR_SYNTH_TX_DIV_SUPPORTED	0x0200
#घोषणा PDR_SYNTH_ASM_MASK		0x0400
#घोषणा PDR_SYNTH_ASM_XSWON		0x0400

#पूर्ण_अगर /* EEPROM_H */
