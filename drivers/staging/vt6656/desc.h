<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: desc.h
 *
 * Purpose:The header file of descriptor
 *
 * Revision History:
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#अगर_अघोषित __DESC_H__
#घोषणा __DESC_H__

#समावेश <linux/bits.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>

/* max transmit or receive buffer size */
#घोषणा CB_MAX_BUF_SIZE     2900U       /* NOTE: must be multiple of 4 */

#घोषणा MAX_TOTAL_SIZE_WITH_ALL_HEADERS CB_MAX_BUF_SIZE

#घोषणा MAX_INTERRUPT_SIZE              32

#घोषणा CB_MAX_RX_DESC      128         /* max # of descriptors */
#घोषणा CB_MIN_RX_DESC      16          /* min # of RX descriptors */
#घोषणा CB_MAX_TX_DESC      128         /* max # of descriptors */
#घोषणा CB_MIN_TX_DESC      16          /* min # of TX descriptors */

/*
 * bits in the RSR रेजिस्टर
 */
#घोषणा RSR_ADDRBROAD       BIT(7)
#घोषणा RSR_ADDRMULTI       BIT(6)
#घोषणा RSR_ADDRUNI         0x00
#घोषणा RSR_IVLDTYP         BIT(5)	/* invalid packet type */
#घोषणा RSR_IVLDLEN         BIT(4)	/* invalid len (> 2312 byte) */
#घोषणा RSR_BSSIDOK         BIT(3)
#घोषणा RSR_CRCOK           BIT(2)
#घोषणा RSR_BCNSSIDOK       BIT(1)
#घोषणा RSR_ADDROK          BIT(0)

/*
 * bits in the new RSR रेजिस्टर
 */
#घोषणा NEWRSR_DECRYPTOK    BIT(4)
#घोषणा NEWRSR_CFPIND       BIT(3)
#घोषणा NEWRSR_HWUTSF       BIT(2)
#घोषणा NEWRSR_BCNHITAID    BIT(1)
#घोषणा NEWRSR_BCNHITAID0   BIT(0)

/*
 * bits in the TSR रेजिस्टर
 */
#घोषणा TSR_RETRYTMO        BIT(3)
#घोषणा TSR_TMO             BIT(2)
#घोषणा TSR_ACKDATA         BIT(1)
#घोषणा TSR_VALID           BIT(0)

#घोषणा FIFOCTL_AUTO_FB_1   0x1000
#घोषणा FIFOCTL_AUTO_FB_0   0x0800
#घोषणा FIFOCTL_GRPACK      0x0400
#घोषणा FIFOCTL_11GA        0x0300
#घोषणा FIFOCTL_11GB        0x0200
#घोषणा FIFOCTL_11B         0x0100
#घोषणा FIFOCTL_11A         0x0000
#घोषणा FIFOCTL_RTS         0x0080
#घोषणा FIFOCTL_ISDMA0      0x0040
#घोषणा FIFOCTL_GENINT      0x0020
#घोषणा FIFOCTL_TMOEN       0x0010
#घोषणा FIFOCTL_LRETRY      0x0008
#घोषणा FIFOCTL_CRCDIS      0x0004
#घोषणा FIFOCTL_NEEDACK     0x0002
#घोषणा FIFOCTL_LHEAD       0x0001

/* WMAC definition Frag Control */
#घोषणा FRAGCTL_AES         0x0300
#घोषणा FRAGCTL_TKIP        0x0200
#घोषणा FRAGCTL_LEGACY      0x0100
#घोषणा FRAGCTL_NONENCRYPT  0x0000
#घोषणा FRAGCTL_ENDFRAG     0x0003
#घोषणा FRAGCTL_MIDFRAG     0x0002
#घोषणा FRAGCTL_STAFRAG     0x0001
#घोषणा FRAGCTL_NONFRAG     0x0000

#पूर्ण_अगर /* __DESC_H__ */
