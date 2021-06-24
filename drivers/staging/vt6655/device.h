<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: device.h
 *
 * Purpose: MAC Data काष्ठाure
 *
 * Author: Tevin Chen
 *
 * Date: Mar 17, 1997
 *
 */

#अगर_अघोषित __DEVICE_H__
#घोषणा __DEVICE_H__

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/crc32.h>
#समावेश <net/mac80211.h>

/* device specअगरic */

#समावेश "device_cfg.h"
#समावेश "card.h"
#समावेश "srom.h"
#समावेश "desc.h"
#समावेश "key.h"
#समावेश "mac.h"

/*---------------------  Export Definitions -------------------------*/

#घोषणा RATE_1M		0
#घोषणा RATE_2M		1
#घोषणा RATE_5M		2
#घोषणा RATE_11M	3
#घोषणा RATE_6M		4
#घोषणा RATE_9M		5
#घोषणा RATE_12M	6
#घोषणा RATE_18M	7
#घोषणा RATE_24M	8
#घोषणा RATE_36M	9
#घोषणा RATE_48M	10
#घोषणा RATE_54M	11
#घोषणा MAX_RATE	12

#घोषणा AUTO_FB_NONE            0
#घोषणा AUTO_FB_0               1
#घोषणा AUTO_FB_1               2

#घोषणा FB_RATE0                0
#घोषणा FB_RATE1                1

/* Antenna Mode */
#घोषणा ANT_A                   0
#घोषणा ANT_B                   1
#घोषणा ANT_DIVERSITY           2
#घोषणा ANT_RXD_TXA             3
#घोषणा ANT_RXD_TXB             4
#घोषणा ANT_UNKNOWN             0xFF

#घोषणा BB_VGA_LEVEL            4
#घोषणा BB_VGA_CHANGE_THRESHOLD 16

#घोषणा MAKE_BEACON_RESERVED	10  /* (us) */

/* BUILD OBJ mode */

#घोषणा	AVAIL_TD(p, q)	((p)->opts.tx_descs[(q)] - ((p)->iTDUsed[(q)]))

/* 0:11A 1:11B 2:11G */
#घोषणा BB_TYPE_11A    0
#घोषणा BB_TYPE_11B    1
#घोषणा BB_TYPE_11G    2

/* 0:11a, 1:11b, 2:11gb (only CCK in BasicRate), 3:11ga (OFDM in BasicRate) */
#घोषणा PK_TYPE_11A     0
#घोषणा PK_TYPE_11B     1
#घोषणा PK_TYPE_11GB    2
#घोषणा PK_TYPE_11GA    3

#घोषणा OWNED_BY_HOST	0
#घोषणा	OWNED_BY_NIC	1

काष्ठा vnt_options अणु
	पूर्णांक rx_descs0;		/* Number of RX descriptors0 */
	पूर्णांक rx_descs1;		/* Number of RX descriptors1 */
	पूर्णांक tx_descs[2];	/* Number of TX descriptors 0, 1 */
	पूर्णांक पूर्णांक_works;		/* पूर्णांकerrupt limits */
	पूर्णांक लघु_retry;
	पूर्णांक दीर्घ_retry;
	पूर्णांक bbp_type;
	u32 flags;
पूर्ण;

काष्ठा vnt_निजी अणु
	काष्ठा pci_dev *pcid;
	/* mac80211 */
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_vअगर *vअगर;
	अचिन्हित दीर्घ key_entry_inuse;
	u32 basic_rates;
	u16 current_aid;
	पूर्णांक mc_list_count;
	u8 mac_hw;

/* dma addr, rx/tx pool */
	dma_addr_t                  pool_dma;
	dma_addr_t                  rd0_pool_dma;
	dma_addr_t                  rd1_pool_dma;

	dma_addr_t                  td0_pool_dma;
	dma_addr_t                  td1_pool_dma;

	dma_addr_t                  tx_bufs_dma0;
	dma_addr_t                  tx_bufs_dma1;
	dma_addr_t                  tx_beacon_dma;

	अचिन्हित अक्षर *tx0_bufs;
	अचिन्हित अक्षर *tx1_bufs;
	अचिन्हित अक्षर *tx_beacon_bufs;

	व्योम __iomem                *PortOffset;
	u32                         memaddr;
	u32                         ioaddr;

	अचिन्हित अक्षर byRxMode;

	spinlock_t                  lock;

	अस्थिर पूर्णांक                iTDUsed[TYPE_MAXTD];

	काष्ठा vnt_tx_desc *apCurrTD[TYPE_MAXTD];
	काष्ठा vnt_tx_desc *apTailTD[TYPE_MAXTD];

	काष्ठा vnt_tx_desc *apTD0Rings;
	काष्ठा vnt_tx_desc *apTD1Rings;

	काष्ठा vnt_rx_desc *aRD0Ring;
	काष्ठा vnt_rx_desc *aRD1Ring;
	काष्ठा vnt_rx_desc *pCurrRD[TYPE_MAXRD];

	काष्ठा vnt_options opts;

	u32                         flags;

	u32                         rx_buf_sz;
	u8 rx_rate;

	u32                         rx_bytes;

	/* Version control */
	अचिन्हित अक्षर byLocalID;
	अचिन्हित अक्षर byRFType;

	अचिन्हित अक्षर byMaxPwrLevel;
	अचिन्हित अक्षर byZoneType;
	bool bZoneRegExist;
	अचिन्हित अक्षर byOriginalZonetype;

	अचिन्हित अक्षर abyCurrentNetAddr[ETH_ALEN]; __aligned(2)
	bool bLinkPass;          /* link status: OK or fail */

	अचिन्हित पूर्णांक	uCurrRSSI;
	अचिन्हित अक्षर byCurrSQ;

	अचिन्हित दीर्घ dwTxAntennaSel;
	अचिन्हित दीर्घ dwRxAntennaSel;
	अचिन्हित अक्षर byAntennaCount;
	अचिन्हित अक्षर byRxAntennaMode;
	अचिन्हित अक्षर byTxAntennaMode;
	bool bTxRxAntInv;

	अचिन्हित अक्षर *pbyTmpBuff;
	अचिन्हित पूर्णांक	uSIFS;    /* Current SIFS */
	अचिन्हित पूर्णांक	uDIFS;    /* Current DIFS */
	अचिन्हित पूर्णांक	uEIFS;    /* Current EIFS */
	अचिन्हित पूर्णांक	uSlot;    /* Current SlotTime */
	अचिन्हित पूर्णांक	uCwMin;   /* Current CwMin */
	अचिन्हित पूर्णांक	uCwMax;   /* CwMax is fixed on 1023. */
	/* PHY parameter */
	अचिन्हित अक्षर bySIFS;
	अचिन्हित अक्षर byDIFS;
	अचिन्हित अक्षर byEIFS;
	अचिन्हित अक्षर bySlot;
	अचिन्हित अक्षर byCWMaxMin;

	u8		byBBType; /* 0:11A, 1:11B, 2:11G */
	u8		byPacketType; /*
				       * 0:11a,1:11b,2:11gb (only CCK
				       * in BasicRate), 3:11ga (OFDM in
				       * Basic Rate)
				       */
	अचिन्हित लघु wBasicRate;
	अचिन्हित अक्षर byACKRate;
	अचिन्हित अक्षर byTopOFDMBasicRate;
	अचिन्हित अक्षर byTopCCKBasicRate;

	अचिन्हित अक्षर byMinChannel;
	अचिन्हित अक्षर byMaxChannel;

	अचिन्हित अक्षर byPreambleType;
	अचिन्हित अक्षर byShortPreamble;

	अचिन्हित लघु wCurrentRate;
	अचिन्हित अक्षर byShortRetryLimit;
	अचिन्हित अक्षर byLongRetryLimit;
	क्रमागत nl80211_अगरtype op_mode;
	bool bBSSIDFilter;
	अचिन्हित लघु wMaxTransmitMSDULअगरeसमय;

	bool bEncryptionEnable;
	bool bLongHeader;
	bool bShortSlotTime;
	bool bProtectMode;
	bool bNonERPPresent;
	bool bBarkerPreambleMd;

	bool bRadioControlOff;
	bool bRadioOff;
	bool bEnablePSMode;
	अचिन्हित लघु wListenInterval;
	bool bPWBitOn;

	/* GPIO Radio Control */
	अचिन्हित अक्षर byRadioCtl;
	अचिन्हित अक्षर byGPIO;
	bool bHWRadioOff;
	bool bPrvActive4RadioOFF;
	bool bGPIOBlockRead;

	/* Beacon related */
	अचिन्हित लघु wSeqCounter;
	अचिन्हित लघु wBCNBufLen;
	bool bBeaconBufReady;
	bool bBeaconSent;
	bool bIsBeaconBufReadySet;
	अचिन्हित पूर्णांक	cbBeaconBufReadySetCnt;
	bool bFixRate;
	u16 byCurrentCh;

	bool bAES;

	अचिन्हित अक्षर byAutoFBCtrl;

	/* For Update BaseBand VGA Gain Offset */
	bool bUpdateBBVGA;
	अचिन्हित पूर्णांक	uBBVGADअगरfCount;
	अचिन्हित अक्षर byBBVGANew;
	अचिन्हित अक्षर byBBVGACurrent;
	अचिन्हित अक्षर abyBBVGA[BB_VGA_LEVEL];
	दीर्घ                    ldBmThreshold[BB_VGA_LEVEL];

	अचिन्हित अक्षर byBBPreEDRSSI;
	अचिन्हित अक्षर byBBPreEDIndex;

	अचिन्हित दीर्घ dwDiagRefCount;

	/* For FOE Tuning */
	अचिन्हित अक्षर byFOETuning;

	/* For RF Power table */
	अचिन्हित अक्षर byCCKPwr;
	अचिन्हित अक्षर byOFDMPwrG;
	अचिन्हित अक्षर byCurPwr;
	अक्षर	 byCurPwrdBm;
	अचिन्हित अक्षर abyCCKPwrTbl[CB_MAX_CHANNEL_24G + 1];
	अचिन्हित अक्षर abyOFDMPwrTbl[CB_MAX_CHANNEL + 1];
	अक्षर	abyCCKDefaultPwr[CB_MAX_CHANNEL_24G + 1];
	अक्षर	abyOFDMDefaultPwr[CB_MAX_CHANNEL + 1];
	अक्षर	abyRegPwr[CB_MAX_CHANNEL + 1];
	अक्षर	abyLocalPwr[CB_MAX_CHANNEL + 1];

	/* BaseBand Loopback Use */
	अचिन्हित अक्षर byBBCR4d;
	अचिन्हित अक्षर byBBCRc9;
	अचिन्हित अक्षर byBBCR88;
	अचिन्हित अक्षर byBBCR09;

	अचिन्हित अक्षर abyEEPROM[EEP_MAX_CONTEXT_SIZE]; /* अचिन्हित दीर्घ alignment */

	अचिन्हित लघु wBeaconInterval;
	u16 wake_up_count;

	काष्ठा work_काष्ठा पूर्णांकerrupt_work;

	काष्ठा ieee80211_low_level_stats low_stats;
पूर्ण;

#पूर्ण_अगर
