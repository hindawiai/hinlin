<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014 Intel Corporation
 */
/*
 * Please use this file (iwl-agn-hw.h) only क्रम hardware-related definitions.
 */

#अगर_अघोषित __iwl_agn_hw_h__
#घोषणा __iwl_agn_hw_h__

#घोषणा IWLAGN_RTC_INST_LOWER_BOUND		(0x000000)
#घोषणा IWLAGN_RTC_INST_UPPER_BOUND		(0x020000)

#घोषणा IWLAGN_RTC_DATA_LOWER_BOUND		(0x800000)
#घोषणा IWLAGN_RTC_DATA_UPPER_BOUND		(0x80C000)

#घोषणा IWLAGN_RTC_INST_SIZE (IWLAGN_RTC_INST_UPPER_BOUND - \
				IWLAGN_RTC_INST_LOWER_BOUND)
#घोषणा IWLAGN_RTC_DATA_SIZE (IWLAGN_RTC_DATA_UPPER_BOUND - \
				IWLAGN_RTC_DATA_LOWER_BOUND)

#घोषणा IWL60_RTC_INST_LOWER_BOUND		(0x000000)
#घोषणा IWL60_RTC_INST_UPPER_BOUND		(0x040000)
#घोषणा IWL60_RTC_DATA_LOWER_BOUND		(0x800000)
#घोषणा IWL60_RTC_DATA_UPPER_BOUND		(0x814000)
#घोषणा IWL60_RTC_INST_SIZE \
	(IWL60_RTC_INST_UPPER_BOUND - IWL60_RTC_INST_LOWER_BOUND)
#घोषणा IWL60_RTC_DATA_SIZE \
	(IWL60_RTC_DATA_UPPER_BOUND - IWL60_RTC_DATA_LOWER_BOUND)

/* RSSI to dBm */
#घोषणा IWLAGN_RSSI_OFFSET	44

#घोषणा IWLAGN_DEFAULT_TX_RETRY			15
#घोषणा IWLAGN_MGMT_DFAULT_RETRY_LIMIT		3
#घोषणा IWLAGN_RTS_DFAULT_RETRY_LIMIT		60
#घोषणा IWLAGN_BAR_DFAULT_RETRY_LIMIT		60
#घोषणा IWLAGN_LOW_RETRY_LIMIT			7

/* Limit range of txघातer output target to be between these values */
#घोषणा IWLAGN_TX_POWER_TARGET_POWER_MIN	(0)	/* 0 dBm: 1 milliwatt */
#घोषणा IWLAGN_TX_POWER_TARGET_POWER_MAX	(16)	/* 16 dBm */

/* EEPROM */
#घोषणा IWLAGN_EEPROM_IMG_SIZE		2048

/* high blocks contain PAPD data */
#घोषणा OTP_HIGH_IMAGE_SIZE_6x00        (6 * 512 * माप(u16)) /* 6 KB */
#घोषणा OTP_HIGH_IMAGE_SIZE_1000        (0x200 * माप(u16)) /* 1024 bytes */
#घोषणा OTP_MAX_LL_ITEMS_1000		(3)	/* OTP blocks क्रम 1000 */
#घोषणा OTP_MAX_LL_ITEMS_6x00		(4)	/* OTP blocks क्रम 6x00 */
#घोषणा OTP_MAX_LL_ITEMS_6x50		(7)	/* OTP blocks क्रम 6x50 */
#घोषणा OTP_MAX_LL_ITEMS_2x00		(4)	/* OTP blocks क्रम 2x00 */


#घोषणा IWLAGN_NUM_QUEUES		20

#पूर्ण_अगर /* __iwl_agn_hw_h__ */
