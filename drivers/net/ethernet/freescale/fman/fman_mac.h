<शैली गुरु>
/*
 * Copyright 2008-2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FM MAC ... */
#अगर_अघोषित __FM_MAC_H
#घोषणा __FM_MAC_H

#समावेश "fman.h"

#समावेश <linux/slab.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_ether.h>

काष्ठा fman_mac;

/* Ethernet Address */
प्रकार u8 enet_addr_t[ETH_ALEN];

#घोषणा ENET_ADDR_TO_UINT64(_enet_addr)		\
	(u64)(((u64)(_enet_addr)[0] << 40) |		\
	      ((u64)(_enet_addr)[1] << 32) |		\
	      ((u64)(_enet_addr)[2] << 24) |		\
	      ((u64)(_enet_addr)[3] << 16) |		\
	      ((u64)(_enet_addr)[4] << 8) |		\
	      ((u64)(_enet_addr)[5]))

#घोषणा MAKE_ENET_ADDR_FROM_UINT64(_addr64, _enet_addr) \
	करो अणु \
		पूर्णांक i; \
		क्रम (i = 0; i < ETH_ALEN; i++) \
			(_enet_addr)[i] = \
			(u8)((_addr64) >> ((5 - i) * 8)); \
	पूर्ण जबतक (0)

/* शेषs */
#घोषणा DEFAULT_RESET_ON_INIT                 false

/* PFC defines */
#घोषणा FSL_FM_PAUSE_TIME_ENABLE	0xf000
#घोषणा FSL_FM_PAUSE_TIME_DISABLE	0
#घोषणा FSL_FM_PAUSE_THRESH_DEFAULT	0

#घोषणा FM_MAC_NO_PFC   0xff

/* HASH defines */
#घोषणा ETH_HASH_ENTRY_OBJ(ptr)	\
	hlist_entry_safe(ptr, काष्ठा eth_hash_entry, node)

/* Enumeration (bit flags) of communication modes (Transmit,
 * receive or both).
 */
क्रमागत comm_mode अणु
	COMM_MODE_NONE = 0,	/* No transmit/receive communication */
	COMM_MODE_RX = 1,	/* Only receive communication */
	COMM_MODE_TX = 2,	/* Only transmit communication */
	COMM_MODE_RX_AND_TX = 3	/* Both transmit and receive communication */
पूर्ण;

/* FM MAC Exceptions */
क्रमागत fman_mac_exceptions अणु
	FM_MAC_EX_10G_MDIO_SCAN_EVENT = 0
	/* 10GEC MDIO scan event पूर्णांकerrupt */
	, FM_MAC_EX_10G_MDIO_CMD_CMPL
	/* 10GEC MDIO command completion पूर्णांकerrupt */
	, FM_MAC_EX_10G_REM_FAULT
	/* 10GEC, mEMAC Remote fault पूर्णांकerrupt */
	, FM_MAC_EX_10G_LOC_FAULT
	/* 10GEC, mEMAC Local fault पूर्णांकerrupt */
	, FM_MAC_EX_10G_TX_ECC_ER
	/* 10GEC, mEMAC Transmit frame ECC error पूर्णांकerrupt */
	, FM_MAC_EX_10G_TX_FIFO_UNFL
	/* 10GEC, mEMAC Transmit FIFO underflow पूर्णांकerrupt */
	, FM_MAC_EX_10G_TX_FIFO_OVFL
	/* 10GEC, mEMAC Transmit FIFO overflow पूर्णांकerrupt */
	, FM_MAC_EX_10G_TX_ER
	/* 10GEC Transmit frame error पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_FIFO_OVFL
	/* 10GEC, mEMAC Receive FIFO overflow पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_ECC_ER
	/* 10GEC, mEMAC Receive frame ECC error पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_JAB_FRM
	/* 10GEC Receive jabber frame पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_OVRSZ_FRM
	/* 10GEC Receive oversized frame पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_RUNT_FRM
	/* 10GEC Receive runt frame पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_FRAG_FRM
	/* 10GEC Receive fragment frame पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_LEN_ER
	/* 10GEC Receive payload length error पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_CRC_ER
	/* 10GEC Receive CRC error पूर्णांकerrupt */
	, FM_MAC_EX_10G_RX_ALIGN_ER
	/* 10GEC Receive alignment error पूर्णांकerrupt */
	, FM_MAC_EX_1G_BAB_RX
	/* dTSEC Babbling receive error */
	, FM_MAC_EX_1G_RX_CTL
	/* dTSEC Receive control (छोड़ो frame) पूर्णांकerrupt */
	, FM_MAC_EX_1G_GRATEFUL_TX_STP_COMPLET
	/* dTSEC Graceful transmit stop complete */
	, FM_MAC_EX_1G_BAB_TX
	/* dTSEC Babbling transmit error */
	, FM_MAC_EX_1G_TX_CTL
	/* dTSEC Transmit control (छोड़ो frame) पूर्णांकerrupt */
	, FM_MAC_EX_1G_TX_ERR
	/* dTSEC Transmit error */
	, FM_MAC_EX_1G_LATE_COL
	/* dTSEC Late collision */
	, FM_MAC_EX_1G_COL_RET_LMT
	/* dTSEC Collision retry limit */
	, FM_MAC_EX_1G_TX_FIFO_UNDRN
	/* dTSEC Transmit FIFO underrun */
	, FM_MAC_EX_1G_MAG_PCKT
	/* dTSEC Magic Packet detection */
	, FM_MAC_EX_1G_MII_MNG_RD_COMPLET
	/* dTSEC MII management पढ़ो completion */
	, FM_MAC_EX_1G_MII_MNG_WR_COMPLET
	/* dTSEC MII management ग_लिखो completion */
	, FM_MAC_EX_1G_GRATEFUL_RX_STP_COMPLET
	/* dTSEC Graceful receive stop complete */
	, FM_MAC_EX_1G_DATA_ERR
	/* dTSEC Internal data error on transmit */
	, FM_MAC_1G_RX_DATA_ERR
	/* dTSEC Internal data error on receive */
	, FM_MAC_EX_1G_1588_TS_RX_ERR
	/* dTSEC Time-Stamp Receive Error */
	, FM_MAC_EX_1G_RX_MIB_CNT_OVFL
	/* dTSEC MIB counter overflow */
	, FM_MAC_EX_TS_FIFO_ECC_ERR
	/* mEMAC Time-stamp FIFO ECC error पूर्णांकerrupt;
	 * not supported on T4240/B4860 rev1 chips
	 */
	, FM_MAC_EX_MAGIC_PACKET_INDICATION = FM_MAC_EX_1G_MAG_PCKT
	/* mEMAC Magic Packet Indication Interrupt */
पूर्ण;

काष्ठा eth_hash_entry अणु
	u64 addr;		/* Ethernet Address  */
	काष्ठा list_head node;
पूर्ण;

प्रकार व्योम (fman_mac_exception_cb)(व्योम *dev_id,
				    क्रमागत fman_mac_exceptions exceptions);

/* FMan MAC config input */
काष्ठा fman_mac_params अणु
	/* Base of memory mapped FM MAC रेजिस्टरs */
	व्योम __iomem *base_addr;
	/* MAC address of device; First octet is sent first */
	enet_addr_t addr;
	/* MAC ID; numbering of dTSEC and 1G-mEMAC:
	 * 0 - FM_MAX_NUM_OF_1G_MACS;
	 * numbering of 10G-MAC (TGEC) and 10G-mEMAC:
	 * 0 - FM_MAX_NUM_OF_10G_MACS
	 */
	u8 mac_id;
	/* PHY पूर्णांकerface */
	phy_पूर्णांकerface_t	 phy_अगर;
	/* Note that the speed should indicate the maximum rate that
	 * this MAC should support rather than the actual speed;
	 */
	u16 max_speed;
	/* A handle to the FM object this port related to */
	व्योम *fm;
	व्योम *dev_id; /* device cookie used by the exception cbs */
	fman_mac_exception_cb *event_cb;    /* MDIO Events Callback Routine */
	fman_mac_exception_cb *exception_cb;/* Exception Callback Routine */
	/* SGMII/QSGII पूर्णांकerface with 1000BaseX स्वतः-negotiation between MAC
	 * and phy or backplane; Note: 1000BaseX स्वतः-negotiation relates only
	 * to पूर्णांकerface between MAC and phy/backplane, SGMII phy can still
	 * synchronize with far-end phy at 10Mbps, 100Mbps or 1000Mbps
	*/
	bool basex_अगर;
	/* Poपूर्णांकer to TBI/PCS PHY node, used क्रम TBI/PCS PHY access */
	काष्ठा device_node *पूर्णांकernal_phy_node;
पूर्ण;

काष्ठा eth_hash_t अणु
	u16 size;
	काष्ठा list_head *lsts;
पूर्ण;

अटल अंतरभूत काष्ठा eth_hash_entry
*dequeue_addr_from_hash_entry(काष्ठा list_head *addr_lst)
अणु
	काष्ठा eth_hash_entry *hash_entry = शून्य;

	अगर (!list_empty(addr_lst)) अणु
		hash_entry = ETH_HASH_ENTRY_OBJ(addr_lst->next);
		list_del_init(&hash_entry->node);
	पूर्ण
	वापस hash_entry;
पूर्ण

अटल अंतरभूत व्योम मुक्त_hash_table(काष्ठा eth_hash_t *hash)
अणु
	काष्ठा eth_hash_entry *hash_entry;
	पूर्णांक i = 0;

	अगर (hash) अणु
		अगर (hash->lsts) अणु
			क्रम (i = 0; i < hash->size; i++) अणु
				hash_entry =
				dequeue_addr_from_hash_entry(&hash->lsts[i]);
				जबतक (hash_entry) अणु
					kमुक्त(hash_entry);
					hash_entry =
					dequeue_addr_from_hash_entry(&hash->
								     lsts[i]);
				पूर्ण
			पूर्ण

			kमुक्त(hash->lsts);
		पूर्ण

		kमुक्त(hash);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा eth_hash_t *alloc_hash_table(u16 size)
अणु
	u32 i;
	काष्ठा eth_hash_t *hash;

	/* Allocate address hash table */
	hash = kदो_स्मृति(माप(*hash), GFP_KERNEL);
	अगर (!hash)
		वापस शून्य;

	hash->size = size;

	hash->lsts = kदो_स्मृति_array(hash->size, माप(काष्ठा list_head),
				   GFP_KERNEL);
	अगर (!hash->lsts) अणु
		kमुक्त(hash);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < hash->size; i++)
		INIT_LIST_HEAD(&hash->lsts[i]);

	वापस hash;
पूर्ण

#पूर्ण_अगर /* __FM_MAC_H */
