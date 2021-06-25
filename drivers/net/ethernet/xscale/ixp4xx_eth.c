<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel IXP4xx Ethernet driver क्रम Linux
 *
 * Copyright (C) 2007 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * Ethernet port config (0x00 is not present on IXP42X):
 *
 * logical port		0x00		0x10		0x20
 * NPE			0 (NPE-A)	1 (NPE-B)	2 (NPE-C)
 * physical PortId	2		0		1
 * TX queue		23		24		25
 * RX-मुक्त queue	26		27		28
 * TX-करोne queue is always 31, per-port RX and TX-पढ़ोy queues are configurable
 *
 * Queue entries:
 * bits 0 -> 1	- NPE ID (RX and TX-करोne)
 * bits 0 -> 2	- priority (TX, per 802.1D)
 * bits 3 -> 4	- port ID (user-set?)
 * bits 5 -> 31	- physical descriptor address
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_data/eth_ixp4xx.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/soc/ixp4xx/npe.h>
#समावेश <linux/soc/ixp4xx/qmgr.h>

#समावेश "ixp46x_ts.h"

#घोषणा DEBUG_DESC		0
#घोषणा DEBUG_RX		0
#घोषणा DEBUG_TX		0
#घोषणा DEBUG_PKT_BYTES		0
#घोषणा DEBUG_MDIO		0
#घोषणा DEBUG_CLOSE		0

#घोषणा DRV_NAME		"ixp4xx_eth"

#घोषणा MAX_NPES		3

#घोषणा RX_DESCS		64 /* also length of all RX queues */
#घोषणा TX_DESCS		16 /* also length of all TX queues */
#घोषणा TXDONE_QUEUE_LEN	64 /* dwords */

#घोषणा POOL_ALLOC_SIZE		(माप(काष्ठा desc) * (RX_DESCS + TX_DESCS))
#घोषणा REGS_SIZE		0x1000
#घोषणा MAX_MRU			1536 /* 0x600 */
#घोषणा RX_BUFF_SIZE		ALIGN((NET_IP_ALIGN) + MAX_MRU, 4)

#घोषणा NAPI_WEIGHT		16
#घोषणा MDIO_INTERVAL		(3 * HZ)
#घोषणा MAX_MDIO_RETRIES	100 /* microseconds, typically 30 cycles */
#घोषणा MAX_CLOSE_WAIT		1000 /* microseconds, typically 2-3 cycles */

#घोषणा NPE_ID(port_id)		((port_id) >> 4)
#घोषणा PHYSICAL_ID(port_id)	((NPE_ID(port_id) + 2) % 3)
#घोषणा TX_QUEUE(port_id)	(NPE_ID(port_id) + 23)
#घोषणा RXFREE_QUEUE(port_id)	(NPE_ID(port_id) + 26)
#घोषणा TXDONE_QUEUE		31

#घोषणा PTP_SLAVE_MODE		1
#घोषणा PTP_MASTER_MODE		2
#घोषणा PORT2CHANNEL(p)		NPE_ID(p->id)

/* TX Control Registers */
#घोषणा TX_CNTRL0_TX_EN		0x01
#घोषणा TX_CNTRL0_HALFDUPLEX	0x02
#घोषणा TX_CNTRL0_RETRY		0x04
#घोषणा TX_CNTRL0_PAD_EN	0x08
#घोषणा TX_CNTRL0_APPEND_FCS	0x10
#घोषणा TX_CNTRL0_2DEFER	0x20
#घोषणा TX_CNTRL0_RMII		0x40 /* reduced MII */
#घोषणा TX_CNTRL1_RETRIES	0x0F /* 4 bits */

/* RX Control Registers */
#घोषणा RX_CNTRL0_RX_EN		0x01
#घोषणा RX_CNTRL0_PADSTRIP_EN	0x02
#घोषणा RX_CNTRL0_SEND_FCS	0x04
#घोषणा RX_CNTRL0_PAUSE_EN	0x08
#घोषणा RX_CNTRL0_LOOP_EN	0x10
#घोषणा RX_CNTRL0_ADDR_FLTR_EN	0x20
#घोषणा RX_CNTRL0_RX_RUNT_EN	0x40
#घोषणा RX_CNTRL0_BCAST_DIS	0x80
#घोषणा RX_CNTRL1_DEFER_EN	0x01

/* Core Control Register */
#घोषणा CORE_RESET		0x01
#घोषणा CORE_RX_FIFO_FLUSH	0x02
#घोषणा CORE_TX_FIFO_FLUSH	0x04
#घोषणा CORE_SEND_JAM		0x08
#घोषणा CORE_MDC_EN		0x10 /* MDIO using NPE-B ETH-0 only */

#घोषणा DEFAULT_TX_CNTRL0	(TX_CNTRL0_TX_EN | TX_CNTRL0_RETRY |	\
				 TX_CNTRL0_PAD_EN | TX_CNTRL0_APPEND_FCS | \
				 TX_CNTRL0_2DEFER)
#घोषणा DEFAULT_RX_CNTRL0	RX_CNTRL0_RX_EN
#घोषणा DEFAULT_CORE_CNTRL	CORE_MDC_EN


/* NPE message codes */
#घोषणा NPE_GETSTATUS			0x00
#घोषणा NPE_EDB_SETPORTADDRESS		0x01
#घोषणा NPE_EDB_GETMACADDRESSDATABASE	0x02
#घोषणा NPE_EDB_SETMACADDRESSSDATABASE	0x03
#घोषणा NPE_GETSTATS			0x04
#घोषणा NPE_RESETSTATS			0x05
#घोषणा NPE_SETMAXFRAMELENGTHS		0x06
#घोषणा NPE_VLAN_SETRXTAGMODE		0x07
#घोषणा NPE_VLAN_SETDEFAULTRXVID	0x08
#घोषणा NPE_VLAN_SETPORTVLANTABLEENTRY	0x09
#घोषणा NPE_VLAN_SETPORTVLANTABLदुस्फल	0x0A
#घोषणा NPE_VLAN_SETRXQOSENTRY		0x0B
#घोषणा NPE_VLAN_SETPORTIDEXTRACTIONMODE 0x0C
#घोषणा NPE_STP_SETBLOCKINGSTATE	0x0D
#घोषणा NPE_FW_SETFIREWALLMODE		0x0E
#घोषणा NPE_PC_SETFRAMECONTROLDURATIONID 0x0F
#घोषणा NPE_PC_SETAPMACTABLE		0x11
#घोषणा NPE_SETLOOPBACK_MODE		0x12
#घोषणा NPE_PC_SETBSSIDTABLE		0x13
#घोषणा NPE_ADDRESS_FILTER_CONFIG	0x14
#घोषणा NPE_APPENDFCSCONFIG		0x15
#घोषणा NPE_NOTIFY_MAC_RECOVERY_DONE	0x16
#घोषणा NPE_MAC_RECOVERY_START		0x17


#अगर_घोषित __ARMEB__
प्रकार काष्ठा sk_buff buffer_t;
#घोषणा मुक्त_buffer dev_kमुक्त_skb
#घोषणा मुक्त_buffer_irq dev_consume_skb_irq
#अन्यथा
प्रकार व्योम buffer_t;
#घोषणा मुक्त_buffer kमुक्त
#घोषणा मुक्त_buffer_irq kमुक्त
#पूर्ण_अगर

काष्ठा eth_regs अणु
	u32 tx_control[2], __res1[2];		/* 000 */
	u32 rx_control[2], __res2[2];		/* 010 */
	u32 अक्रमom_seed, __res3[3];		/* 020 */
	u32 partial_empty_threshold, __res4;	/* 030 */
	u32 partial_full_threshold, __res5;	/* 038 */
	u32 tx_start_bytes, __res6[3];		/* 040 */
	u32 tx_deferral, rx_deferral, __res7[2];/* 050 */
	u32 tx_2part_deferral[2], __res8[2];	/* 060 */
	u32 slot_समय, __res9[3];		/* 070 */
	u32 mdio_command[4];			/* 080 */
	u32 mdio_status[4];			/* 090 */
	u32 mcast_mask[6], __res10[2];		/* 0A0 */
	u32 mcast_addr[6], __res11[2];		/* 0C0 */
	u32 पूर्णांक_घड़ी_प्रकारhreshold, __res12[3];	/* 0E0 */
	u32 hw_addr[6], __res13[61];		/* 0F0 */
	u32 core_control;			/* 1FC */
पूर्ण;

काष्ठा port अणु
	काष्ठा eth_regs __iomem *regs;
	काष्ठा npe *npe;
	काष्ठा net_device *netdev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा eth_plat_info *plat;
	buffer_t *rx_buff_tab[RX_DESCS], *tx_buff_tab[TX_DESCS];
	काष्ठा desc *desc_tab;	/* coherent */
	u32 desc_tab_phys;
	पूर्णांक id;			/* logical port ID */
	पूर्णांक speed, duplex;
	u8 firmware[4];
	पूर्णांक hwts_tx_en;
	पूर्णांक hwts_rx_en;
पूर्ण;

/* NPE message काष्ठाure */
काष्ठा msg अणु
#अगर_घोषित __ARMEB__
	u8 cmd, eth_id, byte2, byte3;
	u8 byte4, byte5, byte6, byte7;
#अन्यथा
	u8 byte3, byte2, eth_id, cmd;
	u8 byte7, byte6, byte5, byte4;
#पूर्ण_अगर
पूर्ण;

/* Ethernet packet descriptor */
काष्ठा desc अणु
	u32 next;		/* poपूर्णांकer to next buffer, unused */

#अगर_घोषित __ARMEB__
	u16 buf_len;		/* buffer length */
	u16 pkt_len;		/* packet length */
	u32 data;		/* poपूर्णांकer to data buffer in RAM */
	u8 dest_id;
	u8 src_id;
	u16 flags;
	u8 qos;
	u8 padlen;
	u16 vlan_tci;
#अन्यथा
	u16 pkt_len;		/* packet length */
	u16 buf_len;		/* buffer length */
	u32 data;		/* poपूर्णांकer to data buffer in RAM */
	u16 flags;
	u8 src_id;
	u8 dest_id;
	u16 vlan_tci;
	u8 padlen;
	u8 qos;
#पूर्ण_अगर

#अगर_घोषित __ARMEB__
	u8 dst_mac_0, dst_mac_1, dst_mac_2, dst_mac_3;
	u8 dst_mac_4, dst_mac_5, src_mac_0, src_mac_1;
	u8 src_mac_2, src_mac_3, src_mac_4, src_mac_5;
#अन्यथा
	u8 dst_mac_3, dst_mac_2, dst_mac_1, dst_mac_0;
	u8 src_mac_1, src_mac_0, dst_mac_5, dst_mac_4;
	u8 src_mac_5, src_mac_4, src_mac_3, src_mac_2;
#पूर्ण_अगर
पूर्ण;


#घोषणा rx_desc_phys(port, n)	((port)->desc_tab_phys +		\
				 (n) * माप(काष्ठा desc))
#घोषणा rx_desc_ptr(port, n)	(&(port)->desc_tab[n])

#घोषणा tx_desc_phys(port, n)	((port)->desc_tab_phys +		\
				 ((n) + RX_DESCS) * माप(काष्ठा desc))
#घोषणा tx_desc_ptr(port, n)	(&(port)->desc_tab[(n) + RX_DESCS])

#अगर_अघोषित __ARMEB__
अटल अंतरभूत व्योम स_नकल_swab32(u32 *dest, u32 *src, पूर्णांक cnt)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < cnt; i++)
		dest[i] = swab32(src[i]);
पूर्ण
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(mdio_lock);
अटल काष्ठा eth_regs __iomem *mdio_regs; /* mdio command and status only */
अटल काष्ठा mii_bus *mdio_bus;
अटल काष्ठा device_node *mdio_bus_np;
अटल पूर्णांक ports_खोलो;
अटल काष्ठा port *npe_port_tab[MAX_NPES];
अटल काष्ठा dma_pool *dma_pool;

अटल पूर्णांक ixp_ptp_match(काष्ठा sk_buff *skb, u16 uid_hi, u32 uid_lo, u16 seqid)
अणु
	u8 *data = skb->data;
	अचिन्हित पूर्णांक offset;
	u16 *hi, *id;
	u32 lo;

	अगर (ptp_classअगरy_raw(skb) != PTP_CLASS_V1_IPV4)
		वापस 0;

	offset = ETH_HLEN + IPV4_HLEN(data) + UDP_HLEN;

	अगर (skb->len < offset + OFF_PTP_SEQUENCE_ID + माप(seqid))
		वापस 0;

	hi = (u16 *)(data + offset + OFF_PTP_SOURCE_UUID);
	id = (u16 *)(data + offset + OFF_PTP_SEQUENCE_ID);

	स_नकल(&lo, &hi[1], माप(lo));

	वापस (uid_hi == ntohs(*hi) &&
		uid_lo == ntohl(lo) &&
		seqid  == ntohs(*id));
पूर्ण

अटल व्योम ixp_rx_बारtamp(काष्ठा port *port, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा ixp46x_ts_regs *regs;
	u64 ns;
	u32 ch, hi, lo, val;
	u16 uid, seq;

	अगर (!port->hwts_rx_en)
		वापस;

	ch = PORT2CHANNEL(port);

	regs = (काष्ठा ixp46x_ts_regs __iomem *) IXP4XX_TIMESYNC_BASE_VIRT;

	val = __raw_पढ़ोl(&regs->channel[ch].ch_event);

	अगर (!(val & RX_SNAPSHOT_LOCKED))
		वापस;

	lo = __raw_पढ़ोl(&regs->channel[ch].src_uuid_lo);
	hi = __raw_पढ़ोl(&regs->channel[ch].src_uuid_hi);

	uid = hi & 0xffff;
	seq = (hi >> 16) & 0xffff;

	अगर (!ixp_ptp_match(skb, htons(uid), htonl(lo), htons(seq)))
		जाओ out;

	lo = __raw_पढ़ोl(&regs->channel[ch].rx_snap_lo);
	hi = __raw_पढ़ोl(&regs->channel[ch].rx_snap_hi);
	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	shhwtstamps = skb_hwtstamps(skb);
	स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
	shhwtstamps->hwtstamp = ns_to_kसमय(ns);
out:
	__raw_ग_लिखोl(RX_SNAPSHOT_LOCKED, &regs->channel[ch].ch_event);
पूर्ण

अटल व्योम ixp_tx_बारtamp(काष्ठा port *port, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा ixp46x_ts_regs *regs;
	काष्ठा skb_shared_info *shtx;
	u64 ns;
	u32 ch, cnt, hi, lo, val;

	shtx = skb_shinfo(skb);
	अगर (unlikely(shtx->tx_flags & SKBTX_HW_TSTAMP && port->hwts_tx_en))
		shtx->tx_flags |= SKBTX_IN_PROGRESS;
	अन्यथा
		वापस;

	ch = PORT2CHANNEL(port);

	regs = (काष्ठा ixp46x_ts_regs __iomem *) IXP4XX_TIMESYNC_BASE_VIRT;

	/*
	 * This really stinks, but we have to poll क्रम the Tx समय stamp.
	 * Usually, the समय stamp is पढ़ोy after 4 to 6 microseconds.
	 */
	क्रम (cnt = 0; cnt < 100; cnt++) अणु
		val = __raw_पढ़ोl(&regs->channel[ch].ch_event);
		अगर (val & TX_SNAPSHOT_LOCKED)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (!(val & TX_SNAPSHOT_LOCKED)) अणु
		shtx->tx_flags &= ~SKBTX_IN_PROGRESS;
		वापस;
	पूर्ण

	lo = __raw_पढ़ोl(&regs->channel[ch].tx_snap_lo);
	hi = __raw_पढ़ोl(&regs->channel[ch].tx_snap_hi);
	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_kसमय(ns);
	skb_tstamp_tx(skb, &shhwtstamps);

	__raw_ग_लिखोl(TX_SNAPSHOT_LOCKED, &regs->channel[ch].ch_event);
पूर्ण

अटल पूर्णांक hwtstamp_set(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config cfg;
	काष्ठा ixp46x_ts_regs *regs;
	काष्ठा port *port = netdev_priv(netdev);
	पूर्णांक ch;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	अगर (cfg.flags) /* reserved क्रम future extensions */
		वापस -EINVAL;

	ch = PORT2CHANNEL(port);
	regs = (काष्ठा ixp46x_ts_regs __iomem *) IXP4XX_TIMESYNC_BASE_VIRT;

	अगर (cfg.tx_type != HWTSTAMP_TX_OFF && cfg.tx_type != HWTSTAMP_TX_ON)
		वापस -दुस्फल;

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		port->hwts_rx_en = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		port->hwts_rx_en = PTP_SLAVE_MODE;
		__raw_ग_लिखोl(0, &regs->channel[ch].ch_control);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		port->hwts_rx_en = PTP_MASTER_MODE;
		__raw_ग_लिखोl(MASTER_MODE, &regs->channel[ch].ch_control);
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	port->hwts_tx_en = cfg.tx_type == HWTSTAMP_TX_ON;

	/* Clear out any old समय stamps. */
	__raw_ग_लिखोl(TX_SNAPSHOT_LOCKED | RX_SNAPSHOT_LOCKED,
		     &regs->channel[ch].ch_event);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक hwtstamp_get(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config cfg;
	काष्ठा port *port = netdev_priv(netdev);

	cfg.flags = 0;
	cfg.tx_type = port->hwts_tx_en ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;

	चयन (port->hwts_rx_en) अणु
	हाल 0:
		cfg.rx_filter = HWTSTAMP_FILTER_NONE;
		अवरोध;
	हाल PTP_SLAVE_MODE:
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_SYNC;
		अवरोध;
	हाल PTP_MASTER_MODE:
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -दुस्फल;
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक ixp4xx_mdio_cmd(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location,
			   पूर्णांक ग_लिखो, u16 cmd)
अणु
	पूर्णांक cycles = 0;

	अगर (__raw_पढ़ोl(&mdio_regs->mdio_command[3]) & 0x80) अणु
		prपूर्णांकk(KERN_ERR "%s: MII not ready to transmit\n", bus->name);
		वापस -1;
	पूर्ण

	अगर (ग_लिखो) अणु
		__raw_ग_लिखोl(cmd & 0xFF, &mdio_regs->mdio_command[0]);
		__raw_ग_लिखोl(cmd >> 8, &mdio_regs->mdio_command[1]);
	पूर्ण
	__raw_ग_लिखोl(((phy_id << 5) | location) & 0xFF,
		     &mdio_regs->mdio_command[2]);
	__raw_ग_लिखोl((phy_id >> 3) | (ग_लिखो << 2) | 0x80 /* GO */,
		     &mdio_regs->mdio_command[3]);

	जबतक ((cycles < MAX_MDIO_RETRIES) &&
	       (__raw_पढ़ोl(&mdio_regs->mdio_command[3]) & 0x80)) अणु
		udelay(1);
		cycles++;
	पूर्ण

	अगर (cycles == MAX_MDIO_RETRIES) अणु
		prपूर्णांकk(KERN_ERR "%s #%i: MII write failed\n", bus->name,
		       phy_id);
		वापस -1;
	पूर्ण

#अगर DEBUG_MDIO
	prपूर्णांकk(KERN_DEBUG "%s #%i: mdio_%s() took %i cycles\n", bus->name,
	       phy_id, ग_लिखो ? "write" : "read", cycles);
#पूर्ण_अगर

	अगर (ग_लिखो)
		वापस 0;

	अगर (__raw_पढ़ोl(&mdio_regs->mdio_status[3]) & 0x80) अणु
#अगर DEBUG_MDIO
		prपूर्णांकk(KERN_DEBUG "%s #%i: MII read failed\n", bus->name,
		       phy_id);
#पूर्ण_अगर
		वापस 0xFFFF; /* करोn't वापस error */
	पूर्ण

	वापस (__raw_पढ़ोl(&mdio_regs->mdio_status[0]) & 0xFF) |
		((__raw_पढ़ोl(&mdio_regs->mdio_status[1]) & 0xFF) << 8);
पूर्ण

अटल पूर्णांक ixp4xx_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&mdio_lock, flags);
	ret = ixp4xx_mdio_cmd(bus, phy_id, location, 0, 0);
	spin_unlock_irqrestore(&mdio_lock, flags);
#अगर DEBUG_MDIO
	prपूर्णांकk(KERN_DEBUG "%s #%i: MII read [%i] -> 0x%X\n", bus->name,
	       phy_id, location, ret);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक ixp4xx_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location,
			     u16 val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&mdio_lock, flags);
	ret = ixp4xx_mdio_cmd(bus, phy_id, location, 1, val);
	spin_unlock_irqrestore(&mdio_lock, flags);
#अगर DEBUG_MDIO
	prपूर्णांकk(KERN_DEBUG "%s #%i: MII write [%i] <- 0x%X, err = %i\n",
	       bus->name, phy_id, location, val, ret);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक ixp4xx_mdio_रेजिस्टर(काष्ठा eth_regs __iomem *regs)
अणु
	पूर्णांक err;

	अगर (!(mdio_bus = mdiobus_alloc()))
		वापस -ENOMEM;

	mdio_regs = regs;
	__raw_ग_लिखोl(DEFAULT_CORE_CNTRL, &mdio_regs->core_control);
	mdio_bus->name = "IXP4xx MII Bus";
	mdio_bus->पढ़ो = &ixp4xx_mdio_पढ़ो;
	mdio_bus->ग_लिखो = &ixp4xx_mdio_ग_लिखो;
	snम_लिखो(mdio_bus->id, MII_BUS_ID_SIZE, "ixp4xx-eth-0");

	err = of_mdiobus_रेजिस्टर(mdio_bus, mdio_bus_np);
	अगर (err)
		mdiobus_मुक्त(mdio_bus);
	वापस err;
पूर्ण

अटल व्योम ixp4xx_mdio_हटाओ(व्योम)
अणु
	mdiobus_unरेजिस्टर(mdio_bus);
	mdiobus_मुक्त(mdio_bus);
पूर्ण


अटल व्योम ixp4xx_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;

	अगर (!phydev->link) अणु
		अगर (port->speed) अणु
			port->speed = 0;
			prपूर्णांकk(KERN_INFO "%s: link down\n", dev->name);
		पूर्ण
		वापस;
	पूर्ण

	अगर (port->speed == phydev->speed && port->duplex == phydev->duplex)
		वापस;

	port->speed = phydev->speed;
	port->duplex = phydev->duplex;

	अगर (port->duplex)
		__raw_ग_लिखोl(DEFAULT_TX_CNTRL0 & ~TX_CNTRL0_HALFDUPLEX,
			     &port->regs->tx_control[0]);
	अन्यथा
		__raw_ग_लिखोl(DEFAULT_TX_CNTRL0 | TX_CNTRL0_HALFDUPLEX,
			     &port->regs->tx_control[0]);

	netdev_info(dev, "%s: link up, speed %u Mb/s, %s duplex\n",
		    dev->name, port->speed, port->duplex ? "full" : "half");
पूर्ण


अटल अंतरभूत व्योम debug_pkt(काष्ठा net_device *dev, स्थिर अक्षर *func,
			     u8 *data, पूर्णांक len)
अणु
#अगर DEBUG_PKT_BYTES
	पूर्णांक i;

	netdev_debug(dev, "%s(%i) ", func, len);
	क्रम (i = 0; i < len; i++) अणु
		अगर (i >= DEBUG_PKT_BYTES)
			अवरोध;
		prपूर्णांकk("%s%02X",
		       ((i == 6) || (i == 12) || (i >= 14)) ? " " : "",
		       data[i]);
	पूर्ण
	prपूर्णांकk("\n");
#पूर्ण_अगर
पूर्ण


अटल अंतरभूत व्योम debug_desc(u32 phys, काष्ठा desc *desc)
अणु
#अगर DEBUG_DESC
	prपूर्णांकk(KERN_DEBUG "%X: %X %3X %3X %08X %2X < %2X %4X %X"
	       " %X %X %02X%02X%02X%02X%02X%02X < %02X%02X%02X%02X%02X%02X\n",
	       phys, desc->next, desc->buf_len, desc->pkt_len,
	       desc->data, desc->dest_id, desc->src_id, desc->flags,
	       desc->qos, desc->padlen, desc->vlan_tci,
	       desc->dst_mac_0, desc->dst_mac_1, desc->dst_mac_2,
	       desc->dst_mac_3, desc->dst_mac_4, desc->dst_mac_5,
	       desc->src_mac_0, desc->src_mac_1, desc->src_mac_2,
	       desc->src_mac_3, desc->src_mac_4, desc->src_mac_5);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक queue_get_desc(अचिन्हित पूर्णांक queue, काष्ठा port *port,
				 पूर्णांक is_tx)
अणु
	u32 phys, tab_phys, n_desc;
	काष्ठा desc *tab;

	अगर (!(phys = qmgr_get_entry(queue)))
		वापस -1;

	phys &= ~0x1F; /* mask out non-address bits */
	tab_phys = is_tx ? tx_desc_phys(port, 0) : rx_desc_phys(port, 0);
	tab = is_tx ? tx_desc_ptr(port, 0) : rx_desc_ptr(port, 0);
	n_desc = (phys - tab_phys) / माप(काष्ठा desc);
	BUG_ON(n_desc >= (is_tx ? TX_DESCS : RX_DESCS));
	debug_desc(phys, &tab[n_desc]);
	BUG_ON(tab[n_desc].next);
	वापस n_desc;
पूर्ण

अटल अंतरभूत व्योम queue_put_desc(अचिन्हित पूर्णांक queue, u32 phys,
				  काष्ठा desc *desc)
अणु
	debug_desc(phys, desc);
	BUG_ON(phys & 0x1F);
	qmgr_put_entry(queue, phys);
	/* Don't check for queue overflow here, we've allocated sufficient
	   length and queues >= 32 करोn't support this check anyway. */
पूर्ण


अटल अंतरभूत व्योम dma_unmap_tx(काष्ठा port *port, काष्ठा desc *desc)
अणु
#अगर_घोषित __ARMEB__
	dma_unmap_single(&port->netdev->dev, desc->data,
			 desc->buf_len, DMA_TO_DEVICE);
#अन्यथा
	dma_unmap_single(&port->netdev->dev, desc->data & ~3,
			 ALIGN((desc->data & 3) + desc->buf_len, 4),
			 DMA_TO_DEVICE);
#पूर्ण_अगर
पूर्ण


अटल व्योम eth_rx_irq(व्योम *pdev)
अणु
	काष्ठा net_device *dev = pdev;
	काष्ठा port *port = netdev_priv(dev);

#अगर DEBUG_RX
	prपूर्णांकk(KERN_DEBUG "%s: eth_rx_irq\n", dev->name);
#पूर्ण_अगर
	qmgr_disable_irq(port->plat->rxq);
	napi_schedule(&port->napi);
पूर्ण

अटल पूर्णांक eth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा port *port = container_of(napi, काष्ठा port, napi);
	काष्ठा net_device *dev = port->netdev;
	अचिन्हित पूर्णांक rxq = port->plat->rxq, rxमुक्तq = RXFREE_QUEUE(port->id);
	पूर्णांक received = 0;

#अगर DEBUG_RX
	netdev_debug(dev, "eth_poll\n");
#पूर्ण_अगर

	जबतक (received < budget) अणु
		काष्ठा sk_buff *skb;
		काष्ठा desc *desc;
		पूर्णांक n;
#अगर_घोषित __ARMEB__
		काष्ठा sk_buff *temp;
		u32 phys;
#पूर्ण_अगर

		अगर ((n = queue_get_desc(rxq, port, 0)) < 0) अणु
#अगर DEBUG_RX
			netdev_debug(dev, "eth_poll napi_complete\n");
#पूर्ण_अगर
			napi_complete(napi);
			qmgr_enable_irq(rxq);
			अगर (!qmgr_stat_below_low_watermark(rxq) &&
			    napi_reschedule(napi)) अणु /* not empty again */
#अगर DEBUG_RX
				netdev_debug(dev, "eth_poll napi_reschedule succeeded\n");
#पूर्ण_अगर
				qmgr_disable_irq(rxq);
				जारी;
			पूर्ण
#अगर DEBUG_RX
			netdev_debug(dev, "eth_poll all done\n");
#पूर्ण_अगर
			वापस received; /* all work करोne */
		पूर्ण

		desc = rx_desc_ptr(port, n);

#अगर_घोषित __ARMEB__
		अगर ((skb = netdev_alloc_skb(dev, RX_BUFF_SIZE))) अणु
			phys = dma_map_single(&dev->dev, skb->data,
					      RX_BUFF_SIZE, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&dev->dev, phys)) अणु
				dev_kमुक्त_skb(skb);
				skb = शून्य;
			पूर्ण
		पूर्ण
#अन्यथा
		skb = netdev_alloc_skb(dev,
				       ALIGN(NET_IP_ALIGN + desc->pkt_len, 4));
#पूर्ण_अगर

		अगर (!skb) अणु
			dev->stats.rx_dropped++;
			/* put the desc back on RX-पढ़ोy queue */
			desc->buf_len = MAX_MRU;
			desc->pkt_len = 0;
			queue_put_desc(rxमुक्तq, rx_desc_phys(port, n), desc);
			जारी;
		पूर्ण

		/* process received frame */
#अगर_घोषित __ARMEB__
		temp = skb;
		skb = port->rx_buff_tab[n];
		dma_unmap_single(&dev->dev, desc->data - NET_IP_ALIGN,
				 RX_BUFF_SIZE, DMA_FROM_DEVICE);
#अन्यथा
		dma_sync_single_क्रम_cpu(&dev->dev, desc->data - NET_IP_ALIGN,
					RX_BUFF_SIZE, DMA_FROM_DEVICE);
		स_नकल_swab32((u32 *)skb->data, (u32 *)port->rx_buff_tab[n],
			      ALIGN(NET_IP_ALIGN + desc->pkt_len, 4) / 4);
#पूर्ण_अगर
		skb_reserve(skb, NET_IP_ALIGN);
		skb_put(skb, desc->pkt_len);

		debug_pkt(dev, "eth_poll", skb->data, skb->len);

		ixp_rx_बारtamp(port, skb);
		skb->protocol = eth_type_trans(skb, dev);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		netअगर_receive_skb(skb);

		/* put the new buffer on RX-मुक्त queue */
#अगर_घोषित __ARMEB__
		port->rx_buff_tab[n] = temp;
		desc->data = phys + NET_IP_ALIGN;
#पूर्ण_अगर
		desc->buf_len = MAX_MRU;
		desc->pkt_len = 0;
		queue_put_desc(rxमुक्तq, rx_desc_phys(port, n), desc);
		received++;
	पूर्ण

#अगर DEBUG_RX
	netdev_debug(dev, "eth_poll(): end, not all work done\n");
#पूर्ण_अगर
	वापस received;		/* not all work करोne */
पूर्ण


अटल व्योम eth_txकरोne_irq(व्योम *unused)
अणु
	u32 phys;

#अगर DEBUG_TX
	prपूर्णांकk(KERN_DEBUG DRV_NAME ": eth_txdone_irq\n");
#पूर्ण_अगर
	जबतक ((phys = qmgr_get_entry(TXDONE_QUEUE)) != 0) अणु
		u32 npe_id, n_desc;
		काष्ठा port *port;
		काष्ठा desc *desc;
		पूर्णांक start;

		npe_id = phys & 3;
		BUG_ON(npe_id >= MAX_NPES);
		port = npe_port_tab[npe_id];
		BUG_ON(!port);
		phys &= ~0x1F; /* mask out non-address bits */
		n_desc = (phys - tx_desc_phys(port, 0)) / माप(काष्ठा desc);
		BUG_ON(n_desc >= TX_DESCS);
		desc = tx_desc_ptr(port, n_desc);
		debug_desc(phys, desc);

		अगर (port->tx_buff_tab[n_desc]) अणु /* not the draining packet */
			port->netdev->stats.tx_packets++;
			port->netdev->stats.tx_bytes += desc->pkt_len;

			dma_unmap_tx(port, desc);
#अगर DEBUG_TX
			prपूर्णांकk(KERN_DEBUG "%s: eth_txdone_irq free %p\n",
			       port->netdev->name, port->tx_buff_tab[n_desc]);
#पूर्ण_अगर
			मुक्त_buffer_irq(port->tx_buff_tab[n_desc]);
			port->tx_buff_tab[n_desc] = शून्य;
		पूर्ण

		start = qmgr_stat_below_low_watermark(port->plat->txपढ़ोyq);
		queue_put_desc(port->plat->txपढ़ोyq, phys, desc);
		अगर (start) अणु /* TX-पढ़ोy queue was empty */
#अगर DEBUG_TX
			prपूर्णांकk(KERN_DEBUG "%s: eth_txdone_irq xmit ready\n",
			       port->netdev->name);
#पूर्ण_अगर
			netअगर_wake_queue(port->netdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक eth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा port *port = netdev_priv(dev);
	अचिन्हित पूर्णांक txपढ़ोyq = port->plat->txपढ़ोyq;
	पूर्णांक len, offset, bytes, n;
	व्योम *mem;
	u32 phys;
	काष्ठा desc *desc;

#अगर DEBUG_TX
	netdev_debug(dev, "eth_xmit\n");
#पूर्ण_अगर

	अगर (unlikely(skb->len > MAX_MRU)) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.tx_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	debug_pkt(dev, "eth_xmit", skb->data, skb->len);

	len = skb->len;
#अगर_घोषित __ARMEB__
	offset = 0; /* no need to keep alignment */
	bytes = len;
	mem = skb->data;
#अन्यथा
	offset = (पूर्णांक)skb->data & 3; /* keep 32-bit alignment */
	bytes = ALIGN(offset + len, 4);
	अगर (!(mem = kदो_स्मृति(bytes, GFP_ATOMIC))) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	स_नकल_swab32(mem, (u32 *)((पूर्णांक)skb->data & ~3), bytes / 4);
#पूर्ण_अगर

	phys = dma_map_single(&dev->dev, mem, bytes, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&dev->dev, phys)) अणु
		dev_kमुक्त_skb(skb);
#अगर_अघोषित __ARMEB__
		kमुक्त(mem);
#पूर्ण_अगर
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	n = queue_get_desc(txपढ़ोyq, port, 1);
	BUG_ON(n < 0);
	desc = tx_desc_ptr(port, n);

#अगर_घोषित __ARMEB__
	port->tx_buff_tab[n] = skb;
#अन्यथा
	port->tx_buff_tab[n] = mem;
#पूर्ण_अगर
	desc->data = phys + offset;
	desc->buf_len = desc->pkt_len = len;

	/* NPE firmware pads लघु frames with zeros पूर्णांकernally */
	wmb();
	queue_put_desc(TX_QUEUE(port->id), tx_desc_phys(port, n), desc);

	अगर (qmgr_stat_below_low_watermark(txपढ़ोyq)) अणु /* empty */
#अगर DEBUG_TX
		netdev_debug(dev, "eth_xmit queue full\n");
#पूर्ण_अगर
		netअगर_stop_queue(dev);
		/* we could miss TX पढ़ोy पूर्णांकerrupt */
		/* really empty in fact */
		अगर (!qmgr_stat_below_low_watermark(txपढ़ोyq)) अणु
#अगर DEBUG_TX
			netdev_debug(dev, "eth_xmit ready again\n");
#पूर्ण_अगर
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण

#अगर DEBUG_TX
	netdev_debug(dev, "eth_xmit end\n");
#पूर्ण_अगर

	ixp_tx_बारtamp(port, skb);
	skb_tx_बारtamp(skb);

#अगर_अघोषित __ARMEB__
	dev_kमुक्त_skb(skb);
#पूर्ण_अगर
	वापस NETDEV_TX_OK;
पूर्ण


अटल व्योम eth_set_mcast_list(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	u8 dअगरfs[ETH_ALEN], *addr;
	पूर्णांक i;
	अटल स्थिर u8 allmulti[] = अणु 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	अगर ((dev->flags & IFF_ALLMULTI) && !(dev->flags & IFF_PROMISC)) अणु
		क्रम (i = 0; i < ETH_ALEN; i++) अणु
			__raw_ग_लिखोl(allmulti[i], &port->regs->mcast_addr[i]);
			__raw_ग_लिखोl(allmulti[i], &port->regs->mcast_mask[i]);
		पूर्ण
		__raw_ग_लिखोl(DEFAULT_RX_CNTRL0 | RX_CNTRL0_ADDR_FLTR_EN,
			&port->regs->rx_control[0]);
		वापस;
	पूर्ण

	अगर ((dev->flags & IFF_PROMISC) || netdev_mc_empty(dev)) अणु
		__raw_ग_लिखोl(DEFAULT_RX_CNTRL0 & ~RX_CNTRL0_ADDR_FLTR_EN,
			     &port->regs->rx_control[0]);
		वापस;
	पूर्ण

	eth_zero_addr(dअगरfs);

	addr = शून्य;
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अगर (!addr)
			addr = ha->addr; /* first MAC address */
		क्रम (i = 0; i < ETH_ALEN; i++)
			dअगरfs[i] |= addr[i] ^ ha->addr[i];
	पूर्ण

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		__raw_ग_लिखोl(addr[i], &port->regs->mcast_addr[i]);
		__raw_ग_लिखोl(~dअगरfs[i], &port->regs->mcast_mask[i]);
	पूर्ण

	__raw_ग_लिखोl(DEFAULT_RX_CNTRL0 | RX_CNTRL0_ADDR_FLTR_EN,
		     &port->regs->rx_control[0]);
पूर्ण


अटल पूर्णांक eth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (cpu_is_ixp46x()) अणु
		अगर (cmd == SIOCSHWTSTAMP)
			वापस hwtstamp_set(dev, req);
		अगर (cmd == SIOCGHWTSTAMP)
			वापस hwtstamp_get(dev, req);
	पूर्ण

	वापस phy_mii_ioctl(dev->phydev, req, cmd);
पूर्ण

/* ethtool support */

अटल व्योम ixp4xx_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा port *port = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	snम_लिखो(info->fw_version, माप(info->fw_version), "%u:%u:%u:%u",
		 port->firmware[0], port->firmware[1],
		 port->firmware[2], port->firmware[3]);
	strlcpy(info->bus_info, "internal", माप(info->bus_info));
पूर्ण

पूर्णांक ixp46x_phc_index = -1;
EXPORT_SYMBOL_GPL(ixp46x_phc_index);

अटल पूर्णांक ixp4xx_get_ts_info(काष्ठा net_device *dev,
			      काष्ठा ethtool_ts_info *info)
अणु
	अगर (!cpu_is_ixp46x()) अणु
		info->so_बारtamping =
			SOF_TIMESTAMPING_TX_SOFTWARE |
			SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		info->phc_index = -1;
		वापस 0;
	पूर्ण
	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->phc_index = ixp46x_phc_index;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ixp4xx_ethtool_ops = अणु
	.get_drvinfo = ixp4xx_get_drvinfo,
	.nway_reset = phy_ethtool_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_ts_info = ixp4xx_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;


अटल पूर्णांक request_queues(काष्ठा port *port)
अणु
	पूर्णांक err;

	err = qmgr_request_queue(RXFREE_QUEUE(port->id), RX_DESCS, 0, 0,
				 "%s:RX-free", port->netdev->name);
	अगर (err)
		वापस err;

	err = qmgr_request_queue(port->plat->rxq, RX_DESCS, 0, 0,
				 "%s:RX", port->netdev->name);
	अगर (err)
		जाओ rel_rxमुक्त;

	err = qmgr_request_queue(TX_QUEUE(port->id), TX_DESCS, 0, 0,
				 "%s:TX", port->netdev->name);
	अगर (err)
		जाओ rel_rx;

	err = qmgr_request_queue(port->plat->txपढ़ोyq, TX_DESCS, 0, 0,
				 "%s:TX-ready", port->netdev->name);
	अगर (err)
		जाओ rel_tx;

	/* TX-करोne queue handles skbs sent out by the NPEs */
	अगर (!ports_खोलो) अणु
		err = qmgr_request_queue(TXDONE_QUEUE, TXDONE_QUEUE_LEN, 0, 0,
					 "%s:TX-done", DRV_NAME);
		अगर (err)
			जाओ rel_txपढ़ोy;
	पूर्ण
	वापस 0;

rel_txपढ़ोy:
	qmgr_release_queue(port->plat->txपढ़ोyq);
rel_tx:
	qmgr_release_queue(TX_QUEUE(port->id));
rel_rx:
	qmgr_release_queue(port->plat->rxq);
rel_rxमुक्त:
	qmgr_release_queue(RXFREE_QUEUE(port->id));
	prपूर्णांकk(KERN_DEBUG "%s: unable to request hardware queues\n",
	       port->netdev->name);
	वापस err;
पूर्ण

अटल व्योम release_queues(काष्ठा port *port)
अणु
	qmgr_release_queue(RXFREE_QUEUE(port->id));
	qmgr_release_queue(port->plat->rxq);
	qmgr_release_queue(TX_QUEUE(port->id));
	qmgr_release_queue(port->plat->txपढ़ोyq);

	अगर (!ports_खोलो)
		qmgr_release_queue(TXDONE_QUEUE);
पूर्ण

अटल पूर्णांक init_queues(काष्ठा port *port)
अणु
	पूर्णांक i;

	अगर (!ports_खोलो) अणु
		dma_pool = dma_pool_create(DRV_NAME, &port->netdev->dev,
					   POOL_ALLOC_SIZE, 32, 0);
		अगर (!dma_pool)
			वापस -ENOMEM;
	पूर्ण

	अगर (!(port->desc_tab = dma_pool_alloc(dma_pool, GFP_KERNEL,
					      &port->desc_tab_phys)))
		वापस -ENOMEM;
	स_रखो(port->desc_tab, 0, POOL_ALLOC_SIZE);
	स_रखो(port->rx_buff_tab, 0, माप(port->rx_buff_tab)); /* tables */
	स_रखो(port->tx_buff_tab, 0, माप(port->tx_buff_tab));

	/* Setup RX buffers */
	क्रम (i = 0; i < RX_DESCS; i++) अणु
		काष्ठा desc *desc = rx_desc_ptr(port, i);
		buffer_t *buff; /* skb or kदो_स्मृति()ated memory */
		व्योम *data;
#अगर_घोषित __ARMEB__
		अगर (!(buff = netdev_alloc_skb(port->netdev, RX_BUFF_SIZE)))
			वापस -ENOMEM;
		data = buff->data;
#अन्यथा
		अगर (!(buff = kदो_स्मृति(RX_BUFF_SIZE, GFP_KERNEL)))
			वापस -ENOMEM;
		data = buff;
#पूर्ण_अगर
		desc->buf_len = MAX_MRU;
		desc->data = dma_map_single(&port->netdev->dev, data,
					    RX_BUFF_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&port->netdev->dev, desc->data)) अणु
			मुक्त_buffer(buff);
			वापस -EIO;
		पूर्ण
		desc->data += NET_IP_ALIGN;
		port->rx_buff_tab[i] = buff;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम destroy_queues(काष्ठा port *port)
अणु
	पूर्णांक i;

	अगर (port->desc_tab) अणु
		क्रम (i = 0; i < RX_DESCS; i++) अणु
			काष्ठा desc *desc = rx_desc_ptr(port, i);
			buffer_t *buff = port->rx_buff_tab[i];
			अगर (buff) अणु
				dma_unmap_single(&port->netdev->dev,
						 desc->data - NET_IP_ALIGN,
						 RX_BUFF_SIZE, DMA_FROM_DEVICE);
				मुक्त_buffer(buff);
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < TX_DESCS; i++) अणु
			काष्ठा desc *desc = tx_desc_ptr(port, i);
			buffer_t *buff = port->tx_buff_tab[i];
			अगर (buff) अणु
				dma_unmap_tx(port, desc);
				मुक्त_buffer(buff);
			पूर्ण
		पूर्ण
		dma_pool_मुक्त(dma_pool, port->desc_tab, port->desc_tab_phys);
		port->desc_tab = शून्य;
	पूर्ण

	अगर (!ports_खोलो && dma_pool) अणु
		dma_pool_destroy(dma_pool);
		dma_pool = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक eth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = netdev_priv(dev);
	काष्ठा npe *npe = port->npe;
	काष्ठा msg msg;
	पूर्णांक i, err;

	अगर (!npe_running(npe)) अणु
		err = npe_load_firmware(npe, npe_name(npe), &dev->dev);
		अगर (err)
			वापस err;

		अगर (npe_recv_message(npe, &msg, "ETH_GET_STATUS")) अणु
			netdev_err(dev, "%s not responding\n", npe_name(npe));
			वापस -EIO;
		पूर्ण
		port->firmware[0] = msg.byte4;
		port->firmware[1] = msg.byte5;
		port->firmware[2] = msg.byte6;
		port->firmware[3] = msg.byte7;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = NPE_VLAN_SETRXQOSENTRY;
	msg.eth_id = port->id;
	msg.byte5 = port->plat->rxq | 0x80;
	msg.byte7 = port->plat->rxq << 4;
	क्रम (i = 0; i < 8; i++) अणु
		msg.byte3 = i;
		अगर (npe_send_recv_message(port->npe, &msg, "ETH_SET_RXQ"))
			वापस -EIO;
	पूर्ण

	msg.cmd = NPE_EDB_SETPORTADDRESS;
	msg.eth_id = PHYSICAL_ID(port->id);
	msg.byte2 = dev->dev_addr[0];
	msg.byte3 = dev->dev_addr[1];
	msg.byte4 = dev->dev_addr[2];
	msg.byte5 = dev->dev_addr[3];
	msg.byte6 = dev->dev_addr[4];
	msg.byte7 = dev->dev_addr[5];
	अगर (npe_send_recv_message(port->npe, &msg, "ETH_SET_MAC"))
		वापस -EIO;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = NPE_FW_SETFIREWALLMODE;
	msg.eth_id = port->id;
	अगर (npe_send_recv_message(port->npe, &msg, "ETH_SET_FIREWALL_MODE"))
		वापस -EIO;

	अगर ((err = request_queues(port)) != 0)
		वापस err;

	अगर ((err = init_queues(port)) != 0) अणु
		destroy_queues(port);
		release_queues(port);
		वापस err;
	पूर्ण

	port->speed = 0;	/* क्रमce "link up" message */
	phy_start(dev->phydev);

	क्रम (i = 0; i < ETH_ALEN; i++)
		__raw_ग_लिखोl(dev->dev_addr[i], &port->regs->hw_addr[i]);
	__raw_ग_लिखोl(0x08, &port->regs->अक्रमom_seed);
	__raw_ग_लिखोl(0x12, &port->regs->partial_empty_threshold);
	__raw_ग_लिखोl(0x30, &port->regs->partial_full_threshold);
	__raw_ग_लिखोl(0x08, &port->regs->tx_start_bytes);
	__raw_ग_लिखोl(0x15, &port->regs->tx_deferral);
	__raw_ग_लिखोl(0x08, &port->regs->tx_2part_deferral[0]);
	__raw_ग_लिखोl(0x07, &port->regs->tx_2part_deferral[1]);
	__raw_ग_लिखोl(0x80, &port->regs->slot_समय);
	__raw_ग_लिखोl(0x01, &port->regs->पूर्णांक_घड़ी_प्रकारhreshold);

	/* Populate queues with buffers, no failure after this poपूर्णांक */
	क्रम (i = 0; i < TX_DESCS; i++)
		queue_put_desc(port->plat->txपढ़ोyq,
			       tx_desc_phys(port, i), tx_desc_ptr(port, i));

	क्रम (i = 0; i < RX_DESCS; i++)
		queue_put_desc(RXFREE_QUEUE(port->id),
			       rx_desc_phys(port, i), rx_desc_ptr(port, i));

	__raw_ग_लिखोl(TX_CNTRL1_RETRIES, &port->regs->tx_control[1]);
	__raw_ग_लिखोl(DEFAULT_TX_CNTRL0, &port->regs->tx_control[0]);
	__raw_ग_लिखोl(0, &port->regs->rx_control[1]);
	__raw_ग_लिखोl(DEFAULT_RX_CNTRL0, &port->regs->rx_control[0]);

	napi_enable(&port->napi);
	eth_set_mcast_list(dev);
	netअगर_start_queue(dev);

	qmgr_set_irq(port->plat->rxq, QUEUE_IRQ_SRC_NOT_EMPTY,
		     eth_rx_irq, dev);
	अगर (!ports_खोलो) अणु
		qmgr_set_irq(TXDONE_QUEUE, QUEUE_IRQ_SRC_NOT_EMPTY,
			     eth_txकरोne_irq, शून्य);
		qmgr_enable_irq(TXDONE_QUEUE);
	पूर्ण
	ports_खोलो++;
	/* we may alपढ़ोy have RX data, enables IRQ */
	napi_schedule(&port->napi);
	वापस 0;
पूर्ण

अटल पूर्णांक eth_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = netdev_priv(dev);
	काष्ठा msg msg;
	पूर्णांक buffs = RX_DESCS; /* allocated RX buffers */
	पूर्णांक i;

	ports_खोलो--;
	qmgr_disable_irq(port->plat->rxq);
	napi_disable(&port->napi);
	netअगर_stop_queue(dev);

	जबतक (queue_get_desc(RXFREE_QUEUE(port->id), port, 0) >= 0)
		buffs--;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = NPE_SETLOOPBACK_MODE;
	msg.eth_id = port->id;
	msg.byte3 = 1;
	अगर (npe_send_recv_message(port->npe, &msg, "ETH_ENABLE_LOOPBACK"))
		netdev_crit(dev, "unable to enable loopback\n");

	i = 0;
	करो अणु			/* drain RX buffers */
		जबतक (queue_get_desc(port->plat->rxq, port, 0) >= 0)
			buffs--;
		अगर (!buffs)
			अवरोध;
		अगर (qmgr_stat_empty(TX_QUEUE(port->id))) अणु
			/* we have to inject some packet */
			काष्ठा desc *desc;
			u32 phys;
			पूर्णांक n = queue_get_desc(port->plat->txपढ़ोyq, port, 1);
			BUG_ON(n < 0);
			desc = tx_desc_ptr(port, n);
			phys = tx_desc_phys(port, n);
			desc->buf_len = desc->pkt_len = 1;
			wmb();
			queue_put_desc(TX_QUEUE(port->id), phys, desc);
		पूर्ण
		udelay(1);
	पूर्ण जबतक (++i < MAX_CLOSE_WAIT);

	अगर (buffs)
		netdev_crit(dev, "unable to drain RX queue, %i buffer(s)"
			    " left in NPE\n", buffs);
#अगर DEBUG_CLOSE
	अगर (!buffs)
		netdev_debug(dev, "draining RX queue took %i cycles\n", i);
#पूर्ण_अगर

	buffs = TX_DESCS;
	जबतक (queue_get_desc(TX_QUEUE(port->id), port, 1) >= 0)
		buffs--; /* cancel TX */

	i = 0;
	करो अणु
		जबतक (queue_get_desc(port->plat->txपढ़ोyq, port, 1) >= 0)
			buffs--;
		अगर (!buffs)
			अवरोध;
	पूर्ण जबतक (++i < MAX_CLOSE_WAIT);

	अगर (buffs)
		netdev_crit(dev, "unable to drain TX queue, %i buffer(s) "
			    "left in NPE\n", buffs);
#अगर DEBUG_CLOSE
	अगर (!buffs)
		netdev_debug(dev, "draining TX queues took %i cycles\n", i);
#पूर्ण_अगर

	msg.byte3 = 0;
	अगर (npe_send_recv_message(port->npe, &msg, "ETH_DISABLE_LOOPBACK"))
		netdev_crit(dev, "unable to disable loopback\n");

	phy_stop(dev->phydev);

	अगर (!ports_खोलो)
		qmgr_disable_irq(TXDONE_QUEUE);
	destroy_queues(port);
	release_queues(port);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ixp4xx_netdev_ops = अणु
	.nकरो_खोलो = eth_खोलो,
	.nकरो_stop = eth_बंद,
	.nकरो_start_xmit = eth_xmit,
	.nकरो_set_rx_mode = eth_set_mcast_list,
	.nकरो_करो_ioctl = eth_ioctl,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_validate_addr = eth_validate_addr,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा eth_plat_info *ixp4xx_of_get_platdata(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args queue_spec;
	काष्ठा of_phandle_args npe_spec;
	काष्ठा device_node *mdio_np;
	काष्ठा eth_plat_info *plat;
	पूर्णांक ret;

	plat = devm_kzalloc(dev, माप(*plat), GFP_KERNEL);
	अगर (!plat)
		वापस शून्य;

	ret = of_parse_phandle_with_fixed_args(np, "intel,npe-handle", 1, 0,
					       &npe_spec);
	अगर (ret) अणु
		dev_err(dev, "no NPE engine specified\n");
		वापस शून्य;
	पूर्ण
	/* NPE ID 0x00, 0x10, 0x20... */
	plat->npe = (npe_spec.args[0] << 4);

	/* Check अगर this device has an MDIO bus */
	mdio_np = of_get_child_by_name(np, "mdio");
	अगर (mdio_np) अणु
		plat->has_mdio = true;
		mdio_bus_np = mdio_np;
		/* DO NOT put the mdio_np, it will be used */
	पूर्ण

	/* Get the rx queue as a resource from queue manager */
	ret = of_parse_phandle_with_fixed_args(np, "queue-rx", 1, 0,
					       &queue_spec);
	अगर (ret) अणु
		dev_err(dev, "no rx queue phandle\n");
		वापस शून्य;
	पूर्ण
	plat->rxq = queue_spec.args[0];

	/* Get the txपढ़ोy queue as resource from queue manager */
	ret = of_parse_phandle_with_fixed_args(np, "queue-txready", 1, 0,
					       &queue_spec);
	अगर (ret) अणु
		dev_err(dev, "no txready queue phandle\n");
		वापस शून्य;
	पूर्ण
	plat->txपढ़ोyq = queue_spec.args[0];

	वापस plat;
पूर्ण
#अन्यथा
अटल काष्ठा eth_plat_info *ixp4xx_of_get_platdata(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ixp4xx_eth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_device *phydev = शून्य;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा eth_plat_info *plat;
	काष्ठा net_device *ndev;
	काष्ठा resource *res;
	काष्ठा port *port;
	पूर्णांक err;

	अगर (np) अणु
		plat = ixp4xx_of_get_platdata(dev);
		अगर (!plat)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		plat = dev_get_platdata(dev);
		अगर (!plat)
			वापस -ENODEV;
		plat->npe = pdev->id;
		चयन (plat->npe) अणु
		हाल IXP4XX_ETH_NPEA:
			/* If the MDIO bus is not up yet, defer probe */
			अवरोध;
		हाल IXP4XX_ETH_NPEB:
			/* On all except IXP43x, NPE-B is used क्रम the MDIO bus.
			 * If there is no NPE-B in the feature set, bail out,
			 * अन्यथा we have the MDIO bus here.
			 */
			अगर (!cpu_is_ixp43x()) अणु
				अगर (!(ixp4xx_पढ़ो_feature_bits() &
				      IXP4XX_FEATURE_NPEB_ETH0))
					वापस -ENODEV;
				/* Else रेजिस्टर the MDIO bus on NPE-B */
				plat->has_mdio = true;
			पूर्ण
			अवरोध;
		हाल IXP4XX_ETH_NPEC:
			/* IXP43x lacks NPE-B and uses NPE-C क्रम the MDIO bus
			 * access, अगर there is no NPE-C, no bus, nothing works,
			 * so bail out.
			 */
			अगर (cpu_is_ixp43x()) अणु
				अगर (!(ixp4xx_पढ़ो_feature_bits() &
				      IXP4XX_FEATURE_NPEC_ETH))
					वापस -ENODEV;
				/* Else रेजिस्टर the MDIO bus on NPE-B */
				plat->has_mdio = true;
			पूर्ण
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!(ndev = devm_alloc_etherdev(dev, माप(काष्ठा port))))
		वापस -ENOMEM;

	SET_NETDEV_DEV(ndev, dev);
	port = netdev_priv(ndev);
	port->netdev = ndev;
	port->id = plat->npe;

	/* Get the port resource and remap */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	port->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(port->regs))
		वापस PTR_ERR(port->regs);

	/* Register the MDIO bus अगर we have it */
	अगर (plat->has_mdio) अणु
		err = ixp4xx_mdio_रेजिस्टर(port->regs);
		अगर (err) अणु
			dev_err(dev, "failed to register MDIO bus\n");
			वापस err;
		पूर्ण
	पूर्ण
	/* If the instance with the MDIO bus has not yet appeared,
	 * defer probing until it माला_लो probed.
	 */
	अगर (!mdio_bus)
		वापस -EPROBE_DEFER;

	ndev->netdev_ops = &ixp4xx_netdev_ops;
	ndev->ethtool_ops = &ixp4xx_ethtool_ops;
	ndev->tx_queue_len = 100;
	/* Inherit the DMA masks from the platक्रमm device */
	ndev->dev.dma_mask = dev->dma_mask;
	ndev->dev.coherent_dma_mask = dev->coherent_dma_mask;

	netअगर_napi_add(ndev, &port->napi, eth_poll, NAPI_WEIGHT);

	अगर (!(port->npe = npe_request(NPE_ID(port->id))))
		वापस -EIO;

	port->plat = plat;
	npe_port_tab[NPE_ID(port->id)] = port;
	स_नकल(ndev->dev_addr, plat->hwaddr, ETH_ALEN);

	platक्रमm_set_drvdata(pdev, ndev);

	__raw_ग_लिखोl(DEFAULT_CORE_CNTRL | CORE_RESET,
		     &port->regs->core_control);
	udelay(50);
	__raw_ग_लिखोl(DEFAULT_CORE_CNTRL, &port->regs->core_control);
	udelay(50);

	अगर (np) अणु
		phydev = of_phy_get_and_connect(ndev, np, ixp4xx_adjust_link);
	पूर्ण अन्यथा अणु
		phydev = mdiobus_get_phy(mdio_bus, plat->phy);
		अगर (IS_ERR(phydev)) अणु
			err = PTR_ERR(phydev);
			dev_err(dev, "could not connect phydev (%d)\n", err);
			जाओ err_मुक्त_mem;
		पूर्ण
		err = phy_connect_direct(ndev, phydev, ixp4xx_adjust_link,
					 PHY_INTERFACE_MODE_MII);
		अगर (err)
			जाओ err_मुक्त_mem;

	पूर्ण
	अगर (!phydev) अणु
		err = -ENODEV;
		dev_err(dev, "no phydev\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	phydev->irq = PHY_POLL;

	अगर ((err = रेजिस्टर_netdev(ndev)))
		जाओ err_phy_dis;

	netdev_info(ndev, "%s: MII PHY %i on %s\n", ndev->name, plat->phy,
		    npe_name(port->npe));

	वापस 0;

err_phy_dis:
	phy_disconnect(phydev);
err_मुक्त_mem:
	npe_port_tab[NPE_ID(port->id)] = शून्य;
	npe_release(port->npe);
	वापस err;
पूर्ण

अटल पूर्णांक ixp4xx_eth_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा phy_device *phydev = ndev->phydev;
	काष्ठा port *port = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	phy_disconnect(phydev);
	ixp4xx_mdio_हटाओ();
	npe_port_tab[NPE_ID(port->id)] = शून्य;
	npe_release(port->npe);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ixp4xx_eth_of_match[] = अणु
	अणु
		.compatible = "intel,ixp4xx-ethernet",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ixp4xx_eth_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(ixp4xx_eth_of_match),
	पूर्ण,
	.probe		= ixp4xx_eth_probe,
	.हटाओ		= ixp4xx_eth_हटाओ,
पूर्ण;
module_platक्रमm_driver(ixp4xx_eth_driver);

MODULE_AUTHOR("Krzysztof Halasa");
MODULE_DESCRIPTION("Intel IXP4xx Ethernet driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ixp4xx_eth");
