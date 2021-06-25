<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  PS3 Platfom gelic network driver.
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2006, 2007 Sony Corporation.
 *
 * This file is based on: spider_net.h
 *
 * (C) Copyright IBM Corp. 2005
 *
 * Authors : Utz Bacher <utz.bacher@de.ibm.com>
 *           Jens Osterkamp <Jens.Osterkamp@de.ibm.com>
 */
#अगर_अघोषित _GELIC_NET_H
#घोषणा _GELIC_NET_H

/* descriptors */
#घोषणा GELIC_NET_RX_DESCRIPTORS        128 /* num of descriptors */
#घोषणा GELIC_NET_TX_DESCRIPTORS        128 /* num of descriptors */

#घोषणा GELIC_NET_MAX_MTU               VLAN_ETH_FRAME_LEN
#घोषणा GELIC_NET_MIN_MTU               VLAN_ETH_ZLEN
#घोषणा GELIC_NET_RXBUF_ALIGN           128
#घोषणा GELIC_CARD_RX_CSUM_DEFAULT      1 /* hw chksum */
#घोषणा GELIC_NET_WATCHDOG_TIMEOUT      5*HZ
#घोषणा GELIC_NET_BROADCAST_ADDR        0xffffffffffffL

#घोषणा GELIC_NET_MC_COUNT_MAX          32 /* multicast address list */

/* भव पूर्णांकerrupt status रेजिस्टर bits */
	/* INT1 */
#घोषणा GELIC_CARD_TX_RAM_FULL_ERR           0x0000000000000001L
#घोषणा GELIC_CARD_RX_RAM_FULL_ERR           0x0000000000000002L
#घोषणा GELIC_CARD_TX_SHORT_FRAME_ERR        0x0000000000000004L
#घोषणा GELIC_CARD_TX_INVALID_DESCR_ERR      0x0000000000000008L
#घोषणा GELIC_CARD_RX_FIFO_FULL_ERR          0x0000000000002000L
#घोषणा GELIC_CARD_RX_DESCR_CHAIN_END        0x0000000000004000L
#घोषणा GELIC_CARD_RX_INVALID_DESCR_ERR      0x0000000000008000L
#घोषणा GELIC_CARD_TX_RESPONCE_ERR           0x0000000000010000L
#घोषणा GELIC_CARD_RX_RESPONCE_ERR           0x0000000000100000L
#घोषणा GELIC_CARD_TX_PROTECTION_ERR         0x0000000000400000L
#घोषणा GELIC_CARD_RX_PROTECTION_ERR         0x0000000004000000L
#घोषणा GELIC_CARD_TX_TCP_UDP_CHECKSUM_ERR   0x0000000008000000L
#घोषणा GELIC_CARD_PORT_STATUS_CHANGED       0x0000000020000000L
#घोषणा GELIC_CARD_WLAN_EVENT_RECEIVED       0x0000000040000000L
#घोषणा GELIC_CARD_WLAN_COMMAND_COMPLETED    0x0000000080000000L
	/* INT 0 */
#घोषणा GELIC_CARD_TX_FLAGGED_DESCR          0x0004000000000000L
#घोषणा GELIC_CARD_RX_FLAGGED_DESCR          0x0040000000000000L
#घोषणा GELIC_CARD_TX_TRANSFER_END           0x0080000000000000L
#घोषणा GELIC_CARD_TX_DESCR_CHAIN_END        0x0100000000000000L
#घोषणा GELIC_CARD_NUMBER_OF_RX_FRAME        0x1000000000000000L
#घोषणा GELIC_CARD_ONE_TIME_COUNT_TIMER      0x4000000000000000L
#घोषणा GELIC_CARD_FREE_RUN_COUNT_TIMER      0x8000000000000000L

/* initial पूर्णांकerrupt mask */
#घोषणा GELIC_CARD_TXINT	GELIC_CARD_TX_DESCR_CHAIN_END

#घोषणा GELIC_CARD_RXINT	(GELIC_CARD_RX_DESCR_CHAIN_END | \
				 GELIC_CARD_NUMBER_OF_RX_FRAME)

 /* RX descriptor data_status bits */
क्रमागत gelic_descr_rx_status अणु
	GELIC_DESCR_RXDMADU	= 0x80000000, /* destination MAC addr unknown */
	GELIC_DESCR_RXLSTFBF	= 0x40000000, /* last frame buffer            */
	GELIC_DESCR_RXIPCHK	= 0x20000000, /* IP checksum perक्रमmed        */
	GELIC_DESCR_RXTCPCHK	= 0x10000000, /* TCP/UDP checksup perक्रमmed   */
	GELIC_DESCR_RXWTPKT	= 0x00C00000, /*
					       * wakeup trigger packet
					       * 01: Magic Packet (TM)
					       * 10: ARP packet
					       * 11: Multicast MAC addr
					       */
	GELIC_DESCR_RXVLNPKT	= 0x00200000, /* VLAN packet */
	/* bit 20..16 reserved */
	GELIC_DESCR_RXRRECNUM	= 0x0000ff00, /* reception receipt number */
	/* bit 7..0 reserved */
पूर्ण;

#घोषणा GELIC_DESCR_DATA_STATUS_CHK_MASK	\
	(GELIC_DESCR_RXIPCHK | GELIC_DESCR_RXTCPCHK)

 /* TX descriptor data_status bits */
क्रमागत gelic_descr_tx_status अणु
	GELIC_DESCR_TX_TAIL	= 0x00000001, /* gelic treated this
					       * descriptor was end of
					       * a tx frame
					       */
पूर्ण;

/* RX descriptor data error bits */
क्रमागत gelic_descr_rx_error अणु
	/* bit 31 reserved */
	GELIC_DESCR_RXALNERR	= 0x40000000, /* alignement error 10/100M */
	GELIC_DESCR_RXOVERERR	= 0x20000000, /* oversize error */
	GELIC_DESCR_RXRNTERR	= 0x10000000, /* Runt error */
	GELIC_DESCR_RXIPCHKERR	= 0x08000000, /* IP checksum  error */
	GELIC_DESCR_RXTCPCHKERR	= 0x04000000, /* TCP/UDP checksum  error */
	GELIC_DESCR_RXDRPPKT	= 0x00100000, /* drop packet */
	GELIC_DESCR_RXIPFMTERR	= 0x00080000, /* IP packet क्रमmat error */
	/* bit 18 reserved */
	GELIC_DESCR_RXDATAERR	= 0x00020000, /* IP packet क्रमmat error */
	GELIC_DESCR_RXCALERR	= 0x00010000, /* cariier extension length
					      * error */
	GELIC_DESCR_RXCREXERR	= 0x00008000, /* carrier extension error */
	GELIC_DESCR_RXMLTCST	= 0x00004000, /* multicast address frame */
	/* bit 13..0 reserved */
पूर्ण;
#घोषणा GELIC_DESCR_DATA_ERROR_CHK_MASK		\
	(GELIC_DESCR_RXIPCHKERR | GELIC_DESCR_RXTCPCHKERR)

/* DMA command and status (RX and TX)*/
क्रमागत gelic_descr_dma_status अणु
	GELIC_DESCR_DMA_COMPLETE            = 0x00000000, /* used in tx */
	GELIC_DESCR_DMA_BUFFER_FULL         = 0x00000000, /* used in rx */
	GELIC_DESCR_DMA_RESPONSE_ERROR      = 0x10000000, /* used in rx, tx */
	GELIC_DESCR_DMA_PROTECTION_ERROR    = 0x20000000, /* used in rx, tx */
	GELIC_DESCR_DMA_FRAME_END           = 0x40000000, /* used in rx */
	GELIC_DESCR_DMA_FORCE_END           = 0x50000000, /* used in rx, tx */
	GELIC_DESCR_DMA_CARDOWNED           = 0xa0000000, /* used in rx, tx */
	GELIC_DESCR_DMA_NOT_IN_USE          = 0xb0000000, /* any other value */
पूर्ण;

#घोषणा GELIC_DESCR_DMA_STAT_MASK	(0xf0000000)

/* tx descriptor command and status */
क्रमागत gelic_descr_tx_dma_status अणु
	/* [19] */
	GELIC_DESCR_TX_DMA_IKE		= 0x00080000, /* IPSEC off */
	/* [18] */
	GELIC_DESCR_TX_DMA_FRAME_TAIL	= 0x00040000, /* last descriptor of
						       * the packet
						       */
	/* [17..16] */
	GELIC_DESCR_TX_DMA_TCP_CHKSUM	= 0x00020000, /* TCP packet */
	GELIC_DESCR_TX_DMA_UDP_CHKSUM	= 0x00030000, /* UDP packet */
	GELIC_DESCR_TX_DMA_NO_CHKSUM	= 0x00000000, /* no checksum */

	/* [1] */
	GELIC_DESCR_TX_DMA_CHAIN_END	= 0x00000002, /* DMA terminated
						       * due to chain end
						       */
पूर्ण;

#घोषणा GELIC_DESCR_DMA_CMD_NO_CHKSUM	\
	(GELIC_DESCR_DMA_CARDOWNED | GELIC_DESCR_TX_DMA_IKE | \
	GELIC_DESCR_TX_DMA_NO_CHKSUM)

#घोषणा GELIC_DESCR_DMA_CMD_TCP_CHKSUM	\
	(GELIC_DESCR_DMA_CARDOWNED | GELIC_DESCR_TX_DMA_IKE | \
	GELIC_DESCR_TX_DMA_TCP_CHKSUM)

#घोषणा GELIC_DESCR_DMA_CMD_UDP_CHKSUM	\
	(GELIC_DESCR_DMA_CARDOWNED | GELIC_DESCR_TX_DMA_IKE | \
	GELIC_DESCR_TX_DMA_UDP_CHKSUM)

क्रमागत gelic_descr_rx_dma_status अणु
	/* [ 1 ] */
	GELIC_DESCR_RX_DMA_CHAIN_END	= 0x00000002, /* DMA terminated
						       * due to chain end
						       */
पूर्ण;

/* क्रम lv1_net_control */
क्रमागत gelic_lv1_net_control_code अणु
	GELIC_LV1_GET_MAC_ADDRESS	= 1,
	GELIC_LV1_GET_ETH_PORT_STATUS	= 2,
	GELIC_LV1_SET_NEGOTIATION_MODE	= 3,
	GELIC_LV1_GET_VLAN_ID		= 4,
	GELIC_LV1_SET_WOL		= 5,
	GELIC_LV1_GET_CHANNEL           = 6,
	GELIC_LV1_POST_WLAN_CMD		= 9,
	GELIC_LV1_GET_WLAN_CMD_RESULT	= 10,
	GELIC_LV1_GET_WLAN_EVENT	= 11,
पूर्ण;

/* क्रम GELIC_LV1_SET_WOL */
क्रमागत gelic_lv1_wol_command अणु
	GELIC_LV1_WOL_MAGIC_PACKET	= 1,
	GELIC_LV1_WOL_ADD_MATCH_ADDR	= 6,
	GELIC_LV1_WOL_DELETE_MATCH_ADDR	= 7,
पूर्ण;

/* क्रम GELIC_LV1_WOL_MAGIC_PACKET */
क्रमागत gelic_lv1_wol_mp_arg अणु
	GELIC_LV1_WOL_MP_DISABLE	= 0,
	GELIC_LV1_WOL_MP_ENABLE		= 1,
पूर्ण;

/* क्रम GELIC_LV1_WOL_अणुADD,DELETEपूर्ण_MATCH_ADDR */
क्रमागत gelic_lv1_wol_match_arg अणु
	GELIC_LV1_WOL_MATCH_INDIVIDUAL	= 0,
	GELIC_LV1_WOL_MATCH_ALL		= 1,
पूर्ण;

/* status returened from GET_ETH_PORT_STATUS */
क्रमागत gelic_lv1_ether_port_status अणु
	GELIC_LV1_ETHER_LINK_UP		= 0x0000000000000001L,
	GELIC_LV1_ETHER_FULL_DUPLEX	= 0x0000000000000002L,
	GELIC_LV1_ETHER_AUTO_NEG	= 0x0000000000000004L,

	GELIC_LV1_ETHER_SPEED_10	= 0x0000000000000010L,
	GELIC_LV1_ETHER_SPEED_100	= 0x0000000000000020L,
	GELIC_LV1_ETHER_SPEED_1000	= 0x0000000000000040L,
	GELIC_LV1_ETHER_SPEED_MASK	= 0x0000000000000070L,
पूर्ण;

क्रमागत gelic_lv1_vlan_index अणु
	/* क्रम outgoing packets */
	GELIC_LV1_VLAN_TX_ETHERNET_0	= 0x0000000000000002L,
	GELIC_LV1_VLAN_TX_WIRELESS	= 0x0000000000000003L,

	/* क्रम incoming packets */
	GELIC_LV1_VLAN_RX_ETHERNET_0	= 0x0000000000000012L,
	GELIC_LV1_VLAN_RX_WIRELESS	= 0x0000000000000013L,
पूर्ण;

क्रमागत gelic_lv1_phy अणु
	GELIC_LV1_PHY_ETHERNET_0	= 0x0000000000000002L,
पूर्ण;

/* size of hardware part of gelic descriptor */
#घोषणा GELIC_DESCR_SIZE	(32)

क्रमागत gelic_port_type अणु
	GELIC_PORT_ETHERNET_0	= 0,
	GELIC_PORT_WIRELESS	= 1,
	GELIC_PORT_MAX
पूर्ण;

काष्ठा gelic_descr अणु
	/* as defined by the hardware */
	__be32 buf_addr;
	__be32 buf_size;
	__be32 next_descr_addr;
	__be32 dmac_cmd_status;
	__be32 result_size;
	__be32 valid_size;	/* all zeroes क्रम tx */
	__be32 data_status;
	__be32 data_error;	/* all zeroes क्रम tx */

	/* used in the driver */
	काष्ठा sk_buff *skb;
	dma_addr_t bus_addr;
	काष्ठा gelic_descr *next;
	काष्ठा gelic_descr *prev;
पूर्ण __attribute__((aligned(32)));

काष्ठा gelic_descr_chain अणु
	/* we walk from tail to head */
	काष्ठा gelic_descr *head;
	काष्ठा gelic_descr *tail;
पूर्ण;

काष्ठा gelic_vlan_id अणु
	u16 tx;
	u16 rx;
पूर्ण;

काष्ठा gelic_card अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *netdev[GELIC_PORT_MAX];
	/*
	 * hypervisor requires irq_status should be
	 * 8 bytes aligned, but u64 member is
	 * always disposed in that manner
	 */
	u64 irq_status;
	u64 irq_mask;

	काष्ठा ps3_प्रणाली_bus_device *dev;
	काष्ठा gelic_vlan_id vlan[GELIC_PORT_MAX];
	पूर्णांक vlan_required;

	काष्ठा gelic_descr_chain tx_chain;
	काष्ठा gelic_descr_chain rx_chain;
	/*
	 * tx_lock guards tx descriptor list and
	 * tx_dma_progress.
	 */
	spinlock_t tx_lock;
	पूर्णांक tx_dma_progress;

	काष्ठा work_काष्ठा tx_समयout_task;
	atomic_t tx_समयout_task_counter;
	रुको_queue_head_t रुकोq;

	/* only first user should up the card */
	काष्ठा mutex upकरोwn_lock;
	atomic_t users;

	u64 ether_port_status;
	पूर्णांक link_mode;

	/* original address वापसed by kzalloc */
	व्योम *unalign;

	/*
	 * each netdevice has copy of irq
	 */
	अचिन्हित पूर्णांक irq;
	काष्ठा gelic_descr *tx_top, *rx_top;
	काष्ठा gelic_descr descr[]; /* must be the last */
पूर्ण;

काष्ठा gelic_port अणु
	काष्ठा gelic_card *card;
	काष्ठा net_device *netdev;
	क्रमागत gelic_port_type type;
	दीर्घ priv[]; /* दीर्घ क्रम alignment */
पूर्ण;

अटल अंतरभूत काष्ठा gelic_card *port_to_card(काष्ठा gelic_port *p)
अणु
	वापस p->card;
पूर्ण
अटल अंतरभूत काष्ठा net_device *port_to_netdev(काष्ठा gelic_port *p)
अणु
	वापस p->netdev;
पूर्ण
अटल अंतरभूत काष्ठा gelic_card *netdev_card(काष्ठा net_device *d)
अणु
	वापस ((काष्ठा gelic_port *)netdev_priv(d))->card;
पूर्ण
अटल अंतरभूत काष्ठा gelic_port *netdev_port(काष्ठा net_device *d)
अणु
	वापस (काष्ठा gelic_port *)netdev_priv(d);
पूर्ण
अटल अंतरभूत काष्ठा device *ctodev(काष्ठा gelic_card *card)
अणु
	वापस &card->dev->core;
पूर्ण
अटल अंतरभूत u64 bus_id(काष्ठा gelic_card *card)
अणु
	वापस card->dev->bus_id;
पूर्ण
अटल अंतरभूत u64 dev_id(काष्ठा gelic_card *card)
अणु
	वापस card->dev->dev_id;
पूर्ण

अटल अंतरभूत व्योम *port_priv(काष्ठा gelic_port *port)
अणु
	वापस port->priv;
पूर्ण

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_PS3GELIC
व्योम udbg_shutकरोwn_ps3gelic(व्योम);
#अन्यथा
अटल अंतरभूत व्योम udbg_shutकरोwn_ps3gelic(व्योम) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक gelic_card_set_irq_mask(काष्ठा gelic_card *card, u64 mask);
/* shared netdev ops */
व्योम gelic_card_up(काष्ठा gelic_card *card);
व्योम gelic_card_करोwn(काष्ठा gelic_card *card);
पूर्णांक gelic_net_खोलो(काष्ठा net_device *netdev);
पूर्णांक gelic_net_stop(काष्ठा net_device *netdev);
netdev_tx_t gelic_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);
व्योम gelic_net_set_multi(काष्ठा net_device *netdev);
व्योम gelic_net_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue);
पूर्णांक gelic_net_setup_netdev(काष्ठा net_device *netdev, काष्ठा gelic_card *card);

/* shared ethtool ops */
व्योम gelic_net_get_drvinfo(काष्ठा net_device *netdev,
			   काष्ठा ethtool_drvinfo *info);
व्योम gelic_net_poll_controller(काष्ठा net_device *netdev);

#पूर्ण_अगर /* _GELIC_NET_H */
