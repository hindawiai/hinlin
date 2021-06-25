<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: card.h
 *
 * Purpose: Provide functions to setup NIC operation mode
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#अगर_अघोषित __CARD_H__
#घोषणा __CARD_H__

#समावेश <linux/types.h>
#समावेश <linux/nl80211.h>

/*
 * Loopback mode
 *
 * LOBYTE is MAC LB mode, HIBYTE is MII LB mode
 */
#घोषणा CARD_LB_NONE            MAKEWORD(MAC_LB_NONE, 0)
/* PHY must ISO, aव्योम MAC loopback packet go out */
#घोषणा CARD_LB_MAC             MAKEWORD(MAC_LB_INTERNAL, 0)
#घोषणा CARD_LB_PHY             MAKEWORD(MAC_LB_EXT, 0)

#घोषणा DEFAULT_MSDU_LIFETIME           512  /* ms */
#घोषणा DEFAULT_MSDU_LIFETIME_RES_64us  8000 /* 64us */

#घोषणा DEFAULT_MGN_LIFETIME            8    /* ms */
#घोषणा DEFAULT_MGN_LIFETIME_RES_64us   125  /* 64us */

#घोषणा CB_MAX_CHANNEL_24G      14
#घोषणा CB_MAX_CHANNEL_5G       42
#घोषणा CB_MAX_CHANNEL          (CB_MAX_CHANNEL_24G + CB_MAX_CHANNEL_5G)

काष्ठा vnt_निजी;

व्योम CARDvSetRSPINF(काष्ठा vnt_निजी *priv, u8 bb_type);
व्योम CARDvUpdateBasicTopRate(काष्ठा vnt_निजी *priv);
bool CARDbIsOFDMinBasicRate(काष्ठा vnt_निजी *priv);
व्योम CARDvSetFirstNextTBTT(काष्ठा vnt_निजी *priv,
			   अचिन्हित लघु wBeaconInterval);
व्योम CARDvUpdateNextTBTT(काष्ठा vnt_निजी *priv, u64 qwTSF,
			 अचिन्हित लघु wBeaconInterval);
bool CARDbGetCurrentTSF(काष्ठा vnt_निजी *priv, u64 *pqwCurrTSF);
u64 CARDqGetNextTBTT(u64 qwTSF, अचिन्हित लघु wBeaconInterval);
u64 CARDqGetTSFOffset(अचिन्हित अक्षर byRxRate, u64 qwTSF1, u64 qwTSF2);
अचिन्हित अक्षर CARDbyGetPktType(काष्ठा vnt_निजी *priv);
व्योम CARDvSafeResetTx(काष्ठा vnt_निजी *priv);
व्योम CARDvSafeResetRx(काष्ठा vnt_निजी *priv);
व्योम CARDbRadioPowerOff(काष्ठा vnt_निजी *priv);
bool CARDbSetPhyParameter(काष्ठा vnt_निजी *priv, u8 bb_type);
bool CARDbUpdateTSF(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRxRate,
		    u64 qwBSSTimestamp);
bool CARDbSetBeaconPeriod(काष्ठा vnt_निजी *priv,
			  अचिन्हित लघु wBeaconInterval);

#पूर्ण_अगर /* __CARD_H__ */
