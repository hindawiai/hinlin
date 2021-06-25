<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: rf.h
 *
 * Purpose:
 *
 * Author: Jerry Chen
 *
 * Date: Feb. 19, 2004
 *
 */

#अगर_अघोषित __RF_H__
#घोषणा __RF_H__

#समावेश "device.h"

/* Baseband RF pair definition in eeprom (Bits 6..0) */
#घोषणा RF_RFMD2959         0x01
#घोषणा RF_MAXIMAG          0x02
#घोषणा RF_AL2230           0x03
#घोषणा RF_GCT5103          0x04
#घोषणा RF_UW2451           0x05
#घोषणा RF_MAXIMG           0x06
#घोषणा RF_MAXIM2829        0x07
#घोषणा RF_UW2452           0x08
#घोषणा RF_VT3226           0x09
#घोषणा RF_AIROHA7230       0x0a
#घोषणा RF_UW2453           0x0b
#घोषणा RF_VT3226D0         0x0c /* RobertYu:20051114 */
#घोषणा RF_VT3342A0         0x0d /* RobertYu:20060609 */
#घोषणा RF_AL2230S          0x0e

#घोषणा RF_EMU              0x80
#घोषणा RF_MASK             0x7F

#घोषणा VNT_RF_MAX_POWER    0x3f
#घोषणा	VNT_RF_REG_LEN      0x17 /* 24 bit length */

पूर्णांक vnt_rf_ग_लिखो_embedded(काष्ठा vnt_निजी *priv, u32 data);
पूर्णांक vnt_rf_setघातer(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_channel *ch);
व्योम vnt_rf_rssi_to_dbm(काष्ठा vnt_निजी *priv, u8 rssi, दीर्घ *dbm);
पूर्णांक vnt_rf_table_करोwnload(काष्ठा vnt_निजी *priv);

#पूर्ण_अगर /* __RF_H__ */
