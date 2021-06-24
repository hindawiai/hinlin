<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_common.h: Basic includes क्रम all files in project. */

#अगर_अघोषित AQ_COMMON_H
#घोषणा AQ_COMMON_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/अगर_vlan.h>
#समावेश "aq_cfg.h"
#समावेश "aq_utils.h"

#घोषणा PCI_VENDOR_ID_AQUANTIA  0x1D6A

#घोषणा AQ_DEVICE_ID_0001	0x0001
#घोषणा AQ_DEVICE_ID_D100	0xD100
#घोषणा AQ_DEVICE_ID_D107	0xD107
#घोषणा AQ_DEVICE_ID_D108	0xD108
#घोषणा AQ_DEVICE_ID_D109	0xD109

#घोषणा AQ_DEVICE_ID_AQC100	0x00B1
#घोषणा AQ_DEVICE_ID_AQC107	0x07B1
#घोषणा AQ_DEVICE_ID_AQC108	0x08B1
#घोषणा AQ_DEVICE_ID_AQC109	0x09B1
#घोषणा AQ_DEVICE_ID_AQC111	0x11B1
#घोषणा AQ_DEVICE_ID_AQC112	0x12B1

#घोषणा AQ_DEVICE_ID_AQC100S	0x80B1
#घोषणा AQ_DEVICE_ID_AQC107S	0x87B1
#घोषणा AQ_DEVICE_ID_AQC108S	0x88B1
#घोषणा AQ_DEVICE_ID_AQC109S	0x89B1
#घोषणा AQ_DEVICE_ID_AQC111S	0x91B1
#घोषणा AQ_DEVICE_ID_AQC112S	0x92B1

#घोषणा AQ_DEVICE_ID_AQC113DEV	0x00C0
#घोषणा AQ_DEVICE_ID_AQC113CS	0x94C0
#घोषणा AQ_DEVICE_ID_AQC114CS	0x93C0
#घोषणा AQ_DEVICE_ID_AQC113	0x04C0
#घोषणा AQ_DEVICE_ID_AQC113C	0x14C0
#घोषणा AQ_DEVICE_ID_AQC115C	0x12C0

#घोषणा HW_ATL_NIC_NAME "Marvell (aQuantia) AQtion 10Gbit Network Adapter"

#घोषणा AQ_HWREV_ANY	0
#घोषणा AQ_HWREV_1	1
#घोषणा AQ_HWREV_2	2

#घोषणा AQ_NIC_RATE_10G		BIT(0)
#घोषणा AQ_NIC_RATE_5G		BIT(1)
#घोषणा AQ_NIC_RATE_5GSR	BIT(2)
#घोषणा AQ_NIC_RATE_2G5		BIT(3)
#घोषणा AQ_NIC_RATE_1G		BIT(4)
#घोषणा AQ_NIC_RATE_100M	BIT(5)
#घोषणा AQ_NIC_RATE_10M		BIT(6)
#घोषणा AQ_NIC_RATE_1G_HALF	BIT(7)
#घोषणा AQ_NIC_RATE_100M_HALF	BIT(8)
#घोषणा AQ_NIC_RATE_10M_HALF	BIT(9)

#घोषणा AQ_NIC_RATE_EEE_10G	BIT(10)
#घोषणा AQ_NIC_RATE_EEE_5G	BIT(11)
#घोषणा AQ_NIC_RATE_EEE_2G5	BIT(12)
#घोषणा AQ_NIC_RATE_EEE_1G	BIT(13)
#घोषणा AQ_NIC_RATE_EEE_100M	BIT(14)
#घोषणा AQ_NIC_RATE_EEE_MSK     (AQ_NIC_RATE_EEE_10G |\
				 AQ_NIC_RATE_EEE_5G |\
				 AQ_NIC_RATE_EEE_2G5 |\
				 AQ_NIC_RATE_EEE_1G |\
				 AQ_NIC_RATE_EEE_100M)

#पूर्ण_अगर /* AQ_COMMON_H */
