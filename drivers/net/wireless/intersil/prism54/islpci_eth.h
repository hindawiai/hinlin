<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 */

#अगर_अघोषित _ISLPCI_ETH_H
#घोषणा _ISLPCI_ETH_H

#समावेश "isl_38xx.h"
#समावेश "islpci_dev.h"

काष्ठा rfmon_header अणु
	__le16 unk0;		/* = 0x0000 */
	__le16 length;		/* = 0x1400 */
	__le32 घड़ी;		/* 1MHz घड़ी */
	u8 flags;
	u8 unk1;
	u8 rate;
	u8 unk2;
	__le16 freq;
	__le16 unk3;
	u8 rssi;
	u8 padding[3];
पूर्ण __packed;

काष्ठा rx_annex_header अणु
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	काष्ठा rfmon_header rfmon;
पूर्ण __packed;

/* wlan-ng (and hopefully others) AVS header, version one.  Fields in
 * network byte order. */
#घोषणा P80211CAPTURE_VERSION 0x80211001

काष्ठा avs_80211_1_header अणु
	__be32 version;
	__be32 length;
	__be64 maस_समय;
	__be64 hostसमय;
	__be32 phytype;
	__be32 channel;
	__be32 datarate;
	__be32 antenna;
	__be32 priority;
	__be32 ssi_type;
	__be32 ssi_संकेत;
	__be32 ssi_noise;
	__be32 preamble;
	__be32 encoding;
पूर्ण;

व्योम islpci_eth_cleanup_transmit(islpci_निजी *, isl38xx_control_block *);
netdev_tx_t islpci_eth_transmit(काष्ठा sk_buff *, काष्ठा net_device *);
पूर्णांक islpci_eth_receive(islpci_निजी *);
व्योम islpci_eth_tx_समयout(काष्ठा net_device *, अचिन्हित पूर्णांक txqueue);
व्योम islpci_करो_reset_and_wake(काष्ठा work_काष्ठा *);

#पूर्ण_अगर				/* _ISL_GEN_H */
