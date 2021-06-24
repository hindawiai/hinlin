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

/*---------------------  Export Definitions -------------------------*/
/*
 * Baseband RF pair definition in eeprom (Bits 6..0)
 */
#घोषणा RF_RFMD2959             0x01
#घोषणा RF_MAXIMAG              0x02
#घोषणा RF_AIROHA               0x03

#घोषणा RF_UW2451               0x05
#घोषणा RF_MAXIMG               0x06
#घोषणा RF_MAXIM2829            0x07 /* RobertYu: 20041118 */
#घोषणा RF_UW2452               0x08 /* RobertYu: 20041210 */
#घोषणा RF_AIROHA7230           0x0a /* RobertYu: 20050104 */
#घोषणा RF_UW2453               0x0b

#घोषणा RF_VT3226               0x09
#घोषणा RF_AL2230S              0x0e

#घोषणा RF_NOTHING              0x7E
#घोषणा RF_EMU                  0x80
#घोषणा RF_MASK                 0x7F

#घोषणा ZONE_FCC                0
#घोषणा ZONE_MKK1               1
#घोषणा ZONE_ETSI               2
#घोषणा ZONE_IC                 3
#घोषणा ZONE_SPAIN              4
#घोषणा ZONE_FRANCE             5
#घोषणा ZONE_MKK                6
#घोषणा ZONE_ISRAEL             7

/* [20050104] CB_MAXIM2829_CHANNEL_5G_HIGH, CB_UW2452_CHANNEL_5G_HIGH: 40==>41 */
#घोषणा CB_MAXIM2829_CHANNEL_5G_HIGH    41 /* Index41: channel = 100, Tf = 5500MHz, set the (A3:A0=0101) D6=1 */
#घोषणा CB_UW2452_CHANNEL_5G_HIGH       41 /* [20041210] Index41: channel = 100, Tf = 5500MHz, change VCO2->VCO3 */

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

bool IFRFbWriteEmbedded(काष्ठा vnt_निजी *priv, अचिन्हित दीर्घ dwData);
bool RFbSelectChannel(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRFType, u16 byChannel);
bool RFbInit(काष्ठा vnt_निजी *priv);
bool RFvWriteWakeProgSyn(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRFType, u16 uChannel);
bool RFbSetPower(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक rate, u16 uCH);
bool RFbRawSetPower(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byPwr,
		    अचिन्हित पूर्णांक rate);

व्योम RFvRSSITodBm(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byCurrRSSI,
		  दीर्घ *pldBm);

/* अणुअणु RobertYu: 20050104 */
bool RFbAL7230SelectChannelPostProcess(काष्ठा vnt_निजी *priv, u16 byOldChannel, u16 byNewChannel);
/* पूर्णपूर्ण RobertYu */

#पूर्ण_अगर /* __RF_H__ */
