<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom BCM7xxx System Port Ethernet MAC driver
 *
 * Copyright (C) 2014 Broadcom Corporation
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/dsa/brcm.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <net/dsa.h>
#समावेश <linux/clk.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>

#समावेश "bcmsysport.h"

/* I/O accessors रेजिस्टर helpers */
#घोषणा BCM_SYSPORT_IO_MACRO(name, offset) \
अटल अंतरभूत u32 name##_पढ़ोl(काष्ठा bcm_sysport_priv *priv, u32 off)	\
अणु									\
	u32 reg = पढ़ोl_relaxed(priv->base + offset + off);		\
	वापस reg;							\
पूर्ण									\
अटल अंतरभूत व्योम name##_ग_लिखोl(काष्ठा bcm_sysport_priv *priv,		\
				  u32 val, u32 off)			\
अणु									\
	ग_लिखोl_relaxed(val, priv->base + offset + off);			\
पूर्ण									\

BCM_SYSPORT_IO_MACRO(पूर्णांकrl2_0, SYS_PORT_INTRL2_0_OFFSET);
BCM_SYSPORT_IO_MACRO(पूर्णांकrl2_1, SYS_PORT_INTRL2_1_OFFSET);
BCM_SYSPORT_IO_MACRO(umac, SYS_PORT_UMAC_OFFSET);
BCM_SYSPORT_IO_MACRO(gib, SYS_PORT_GIB_OFFSET);
BCM_SYSPORT_IO_MACRO(tdma, SYS_PORT_TDMA_OFFSET);
BCM_SYSPORT_IO_MACRO(rxchk, SYS_PORT_RXCHK_OFFSET);
BCM_SYSPORT_IO_MACRO(txchk, SYS_PORT_TXCHK_OFFSET);
BCM_SYSPORT_IO_MACRO(rbuf, SYS_PORT_RBUF_OFFSET);
BCM_SYSPORT_IO_MACRO(tbuf, SYS_PORT_TBUF_OFFSET);
BCM_SYSPORT_IO_MACRO(topctrl, SYS_PORT_TOPCTRL_OFFSET);

/* On SYSTEMPORT Lite, any रेजिस्टर after RDMA_STATUS has the exact
 * same layout, except it has been moved by 4 bytes up, *sigh*
 */
अटल अंतरभूत u32 rdma_पढ़ोl(काष्ठा bcm_sysport_priv *priv, u32 off)
अणु
	अगर (priv->is_lite && off >= RDMA_STATUS)
		off += 4;
	वापस पढ़ोl_relaxed(priv->base + SYS_PORT_RDMA_OFFSET + off);
पूर्ण

अटल अंतरभूत व्योम rdma_ग_लिखोl(काष्ठा bcm_sysport_priv *priv, u32 val, u32 off)
अणु
	अगर (priv->is_lite && off >= RDMA_STATUS)
		off += 4;
	ग_लिखोl_relaxed(val, priv->base + SYS_PORT_RDMA_OFFSET + off);
पूर्ण

अटल अंतरभूत u32 tdma_control_bit(काष्ठा bcm_sysport_priv *priv, u32 bit)
अणु
	अगर (!priv->is_lite) अणु
		वापस BIT(bit);
	पूर्ण अन्यथा अणु
		अगर (bit >= ACB_ALGO)
			वापस BIT(bit + 1);
		अन्यथा
			वापस BIT(bit);
	पूर्ण
पूर्ण

/* L2-पूर्णांकerrupt masking/unmasking helpers, करोes स्वतःmatic saving of the applied
 * mask in a software copy to aव्योम CPU_MASK_STATUS पढ़ोs in hot-paths.
  */
#घोषणा BCM_SYSPORT_INTR_L2(which)	\
अटल अंतरभूत व्योम पूर्णांकrl2_##which##_mask_clear(काष्ठा bcm_sysport_priv *priv, \
						u32 mask)		\
अणु									\
	priv->irq##which##_mask &= ~(mask);				\
	पूर्णांकrl2_##which##_ग_लिखोl(priv, mask, INTRL2_CPU_MASK_CLEAR);	\
पूर्ण									\
अटल अंतरभूत व्योम पूर्णांकrl2_##which##_mask_set(काष्ठा bcm_sysport_priv *priv, \
						u32 mask)		\
अणु									\
	पूर्णांकrl2_## which##_ग_लिखोl(priv, mask, INTRL2_CPU_MASK_SET);	\
	priv->irq##which##_mask |= (mask);				\
पूर्ण									\

BCM_SYSPORT_INTR_L2(0)
BCM_SYSPORT_INTR_L2(1)

/* Register accesses to GISB/RBUS रेजिस्टरs are expensive (few hundred
 * nanoseconds), so keep the check क्रम 64-bits explicit here to save
 * one रेजिस्टर ग_लिखो per-packet on 32-bits platक्रमms.
 */
अटल अंतरभूत व्योम dma_desc_set_addr(काष्ठा bcm_sysport_priv *priv,
				     व्योम __iomem *d,
				     dma_addr_t addr)
अणु
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	ग_लिखोl_relaxed(upper_32_bits(addr) & DESC_ADDR_HI_MASK,
		     d + DESC_ADDR_HI_STATUS_LEN);
#पूर्ण_अगर
	ग_लिखोl_relaxed(lower_32_bits(addr), d + DESC_ADDR_LO);
पूर्ण

/* Ethtool operations */
अटल व्योम bcm_sysport_set_rx_csum(काष्ठा net_device *dev,
				    netdev_features_t wanted)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	u32 reg;

	priv->rx_chk_en = !!(wanted & NETIF_F_RXCSUM);
	reg = rxchk_पढ़ोl(priv, RXCHK_CONTROL);
	/* Clear L2 header checks, which would prevent BPDUs
	 * from being received.
	 */
	reg &= ~RXCHK_L2_HDR_DIS;
	अगर (priv->rx_chk_en)
		reg |= RXCHK_EN;
	अन्यथा
		reg &= ~RXCHK_EN;

	/* If UniMAC क्रमwards CRC, we need to skip over it to get
	 * a valid CHK bit to be set in the per-packet status word
	 */
	अगर (priv->rx_chk_en && priv->crc_fwd)
		reg |= RXCHK_SKIP_FCS;
	अन्यथा
		reg &= ~RXCHK_SKIP_FCS;

	/* If Broadcom tags are enabled (e.g: using a चयन), make
	 * sure we tell the RXCHK hardware to expect a 4-bytes Broadcom
	 * tag after the Ethernet MAC Source Address.
	 */
	अगर (netdev_uses_dsa(dev))
		reg |= RXCHK_BRCM_TAG_EN;
	अन्यथा
		reg &= ~RXCHK_BRCM_TAG_EN;

	rxchk_ग_लिखोl(priv, reg, RXCHK_CONTROL);
पूर्ण

अटल व्योम bcm_sysport_set_tx_csum(काष्ठा net_device *dev,
				    netdev_features_t wanted)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	u32 reg;

	/* Hardware transmit checksum requires us to enable the Transmit status
	 * block prepended to the packet contents
	 */
	priv->tsb_en = !!(wanted & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				    NETIF_F_HW_VLAN_CTAG_TX));
	reg = tdma_पढ़ोl(priv, TDMA_CONTROL);
	अगर (priv->tsb_en)
		reg |= tdma_control_bit(priv, TSB_EN);
	अन्यथा
		reg &= ~tdma_control_bit(priv, TSB_EN);
	/* Indicating that software inserts Broadcom tags is needed क्रम the TX
	 * checksum to be computed correctly when using VLAN HW acceleration,
	 * अन्यथा it has no effect, so it can always be turned on.
	 */
	अगर (netdev_uses_dsa(dev))
		reg |= tdma_control_bit(priv, SW_BRCM_TAG);
	अन्यथा
		reg &= ~tdma_control_bit(priv, SW_BRCM_TAG);
	tdma_ग_लिखोl(priv, reg, TDMA_CONTROL);

	/* Default TPID is ETH_P_8021AD, change to ETH_P_8021Q */
	अगर (wanted & NETIF_F_HW_VLAN_CTAG_TX)
		tdma_ग_लिखोl(priv, ETH_P_8021Q, TDMA_TPID);
पूर्ण

अटल पूर्णांक bcm_sysport_set_features(काष्ठा net_device *dev,
				    netdev_features_t features)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	/* Read CRC क्रमward */
	अगर (!priv->is_lite)
		priv->crc_fwd = !!(umac_पढ़ोl(priv, UMAC_CMD) & CMD_CRC_FWD);
	अन्यथा
		priv->crc_fwd = !((gib_पढ़ोl(priv, GIB_CONTROL) &
				  GIB_FCS_STRIP) >> GIB_FCS_STRIP_SHIFT);

	bcm_sysport_set_rx_csum(dev, features);
	bcm_sysport_set_tx_csum(dev, features);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

/* Hardware counters must be kept in sync because the order/offset
 * is important here (order in काष्ठाure declaration = order in hardware)
 */
अटल स्थिर काष्ठा bcm_sysport_stats bcm_sysport_gstrings_stats[] = अणु
	/* general stats */
	STAT_NETDEV64(rx_packets),
	STAT_NETDEV64(tx_packets),
	STAT_NETDEV64(rx_bytes),
	STAT_NETDEV64(tx_bytes),
	STAT_NETDEV(rx_errors),
	STAT_NETDEV(tx_errors),
	STAT_NETDEV(rx_dropped),
	STAT_NETDEV(tx_dropped),
	STAT_NETDEV(multicast),
	/* UniMAC RSV counters */
	STAT_MIB_RX("rx_64_octets", mib.rx.pkt_cnt.cnt_64),
	STAT_MIB_RX("rx_65_127_oct", mib.rx.pkt_cnt.cnt_127),
	STAT_MIB_RX("rx_128_255_oct", mib.rx.pkt_cnt.cnt_255),
	STAT_MIB_RX("rx_256_511_oct", mib.rx.pkt_cnt.cnt_511),
	STAT_MIB_RX("rx_512_1023_oct", mib.rx.pkt_cnt.cnt_1023),
	STAT_MIB_RX("rx_1024_1518_oct", mib.rx.pkt_cnt.cnt_1518),
	STAT_MIB_RX("rx_vlan_1519_1522_oct", mib.rx.pkt_cnt.cnt_mgv),
	STAT_MIB_RX("rx_1522_2047_oct", mib.rx.pkt_cnt.cnt_2047),
	STAT_MIB_RX("rx_2048_4095_oct", mib.rx.pkt_cnt.cnt_4095),
	STAT_MIB_RX("rx_4096_9216_oct", mib.rx.pkt_cnt.cnt_9216),
	STAT_MIB_RX("rx_pkts", mib.rx.pkt),
	STAT_MIB_RX("rx_bytes", mib.rx.bytes),
	STAT_MIB_RX("rx_multicast", mib.rx.mca),
	STAT_MIB_RX("rx_broadcast", mib.rx.bca),
	STAT_MIB_RX("rx_fcs", mib.rx.fcs),
	STAT_MIB_RX("rx_control", mib.rx.cf),
	STAT_MIB_RX("rx_pause", mib.rx.pf),
	STAT_MIB_RX("rx_unknown", mib.rx.uo),
	STAT_MIB_RX("rx_align", mib.rx.aln),
	STAT_MIB_RX("rx_outrange", mib.rx.flr),
	STAT_MIB_RX("rx_code", mib.rx.cde),
	STAT_MIB_RX("rx_carrier", mib.rx.fcr),
	STAT_MIB_RX("rx_oversize", mib.rx.ovr),
	STAT_MIB_RX("rx_jabber", mib.rx.jbr),
	STAT_MIB_RX("rx_mtu_err", mib.rx.mtue),
	STAT_MIB_RX("rx_good_pkts", mib.rx.pok),
	STAT_MIB_RX("rx_unicast", mib.rx.uc),
	STAT_MIB_RX("rx_ppp", mib.rx.ppp),
	STAT_MIB_RX("rx_crc", mib.rx.rcrc),
	/* UniMAC TSV counters */
	STAT_MIB_TX("tx_64_octets", mib.tx.pkt_cnt.cnt_64),
	STAT_MIB_TX("tx_65_127_oct", mib.tx.pkt_cnt.cnt_127),
	STAT_MIB_TX("tx_128_255_oct", mib.tx.pkt_cnt.cnt_255),
	STAT_MIB_TX("tx_256_511_oct", mib.tx.pkt_cnt.cnt_511),
	STAT_MIB_TX("tx_512_1023_oct", mib.tx.pkt_cnt.cnt_1023),
	STAT_MIB_TX("tx_1024_1518_oct", mib.tx.pkt_cnt.cnt_1518),
	STAT_MIB_TX("tx_vlan_1519_1522_oct", mib.tx.pkt_cnt.cnt_mgv),
	STAT_MIB_TX("tx_1522_2047_oct", mib.tx.pkt_cnt.cnt_2047),
	STAT_MIB_TX("tx_2048_4095_oct", mib.tx.pkt_cnt.cnt_4095),
	STAT_MIB_TX("tx_4096_9216_oct", mib.tx.pkt_cnt.cnt_9216),
	STAT_MIB_TX("tx_pkts", mib.tx.pkts),
	STAT_MIB_TX("tx_multicast", mib.tx.mca),
	STAT_MIB_TX("tx_broadcast", mib.tx.bca),
	STAT_MIB_TX("tx_pause", mib.tx.pf),
	STAT_MIB_TX("tx_control", mib.tx.cf),
	STAT_MIB_TX("tx_fcs_err", mib.tx.fcs),
	STAT_MIB_TX("tx_oversize", mib.tx.ovr),
	STAT_MIB_TX("tx_defer", mib.tx.drf),
	STAT_MIB_TX("tx_excess_defer", mib.tx.edf),
	STAT_MIB_TX("tx_single_col", mib.tx.scl),
	STAT_MIB_TX("tx_multi_col", mib.tx.mcl),
	STAT_MIB_TX("tx_late_col", mib.tx.lcl),
	STAT_MIB_TX("tx_excess_col", mib.tx.ecl),
	STAT_MIB_TX("tx_frags", mib.tx.frg),
	STAT_MIB_TX("tx_total_col", mib.tx.ncl),
	STAT_MIB_TX("tx_jabber", mib.tx.jbr),
	STAT_MIB_TX("tx_bytes", mib.tx.bytes),
	STAT_MIB_TX("tx_good_pkts", mib.tx.pok),
	STAT_MIB_TX("tx_unicast", mib.tx.uc),
	/* UniMAC RUNT counters */
	STAT_RUNT("rx_runt_pkts", mib.rx_runt_cnt),
	STAT_RUNT("rx_runt_valid_fcs", mib.rx_runt_fcs),
	STAT_RUNT("rx_runt_inval_fcs_align", mib.rx_runt_fcs_align),
	STAT_RUNT("rx_runt_bytes", mib.rx_runt_bytes),
	/* RXCHK misc statistics */
	STAT_RXCHK("rxchk_bad_csum", mib.rxchk_bad_csum, RXCHK_BAD_CSUM_CNTR),
	STAT_RXCHK("rxchk_other_pkt_disc", mib.rxchk_other_pkt_disc,
		   RXCHK_OTHER_DISC_CNTR),
	/* RBUF misc statistics */
	STAT_RBUF("rbuf_ovflow_cnt", mib.rbuf_ovflow_cnt, RBUF_OVFL_DISC_CNTR),
	STAT_RBUF("rbuf_err_cnt", mib.rbuf_err_cnt, RBUF_ERR_PKT_CNTR),
	STAT_MIB_SOFT("alloc_rx_buff_failed", mib.alloc_rx_buff_failed),
	STAT_MIB_SOFT("rx_dma_failed", mib.rx_dma_failed),
	STAT_MIB_SOFT("tx_dma_failed", mib.tx_dma_failed),
	STAT_MIB_SOFT("tx_realloc_tsb", mib.tx_पुनः_स्मृति_tsb),
	STAT_MIB_SOFT("tx_realloc_tsb_failed", mib.tx_पुनः_स्मृति_tsb_failed),
	/* Per TX-queue statistics are dynamically appended */
पूर्ण;

#घोषणा BCM_SYSPORT_STATS_LEN	ARRAY_SIZE(bcm_sysport_gstrings_stats)

अटल व्योम bcm_sysport_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->bus_info, "platform", माप(info->bus_info));
पूर्ण

अटल u32 bcm_sysport_get_msglvl(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम bcm_sysport_set_msglvl(काष्ठा net_device *dev, u32 enable)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);

	priv->msg_enable = enable;
पूर्ण

अटल अंतरभूत bool bcm_sysport_lite_stat_valid(क्रमागत bcm_sysport_stat_type type)
अणु
	चयन (type) अणु
	हाल BCM_SYSPORT_STAT_NETDEV:
	हाल BCM_SYSPORT_STAT_NETDEV64:
	हाल BCM_SYSPORT_STAT_RXCHK:
	हाल BCM_SYSPORT_STAT_RBUF:
	हाल BCM_SYSPORT_STAT_SOFT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_sysport_get_sset_count(काष्ठा net_device *dev, पूर्णांक string_set)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	स्थिर काष्ठा bcm_sysport_stats *s;
	अचिन्हित पूर्णांक i, j;

	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0, j = 0; i < BCM_SYSPORT_STATS_LEN; i++) अणु
			s = &bcm_sysport_gstrings_stats[i];
			अगर (priv->is_lite &&
			    !bcm_sysport_lite_stat_valid(s->type))
				जारी;
			j++;
		पूर्ण
		/* Include per-queue statistics */
		वापस j + dev->num_tx_queues * NUM_SYSPORT_TXQ_STAT;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम bcm_sysport_get_strings(काष्ठा net_device *dev,
				    u32 stringset, u8 *data)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	स्थिर काष्ठा bcm_sysport_stats *s;
	अक्षर buf[128];
	पूर्णांक i, j;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0, j = 0; i < BCM_SYSPORT_STATS_LEN; i++) अणु
			s = &bcm_sysport_gstrings_stats[i];
			अगर (priv->is_lite &&
			    !bcm_sysport_lite_stat_valid(s->type))
				जारी;

			स_नकल(data + j * ETH_GSTRING_LEN, s->stat_string,
			       ETH_GSTRING_LEN);
			j++;
		पूर्ण

		क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
			snम_लिखो(buf, माप(buf), "txq%d_packets", i);
			स_नकल(data + j * ETH_GSTRING_LEN, buf,
			       ETH_GSTRING_LEN);
			j++;

			snम_लिखो(buf, माप(buf), "txq%d_bytes", i);
			स_नकल(data + j * ETH_GSTRING_LEN, buf,
			       ETH_GSTRING_LEN);
			j++;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bcm_sysport_update_mib_counters(काष्ठा bcm_sysport_priv *priv)
अणु
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < BCM_SYSPORT_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcm_sysport_stats *s;
		u8 offset = 0;
		u32 val = 0;
		अक्षर *p;

		s = &bcm_sysport_gstrings_stats[i];
		चयन (s->type) अणु
		हाल BCM_SYSPORT_STAT_NETDEV:
		हाल BCM_SYSPORT_STAT_NETDEV64:
		हाल BCM_SYSPORT_STAT_SOFT:
			जारी;
		हाल BCM_SYSPORT_STAT_MIB_RX:
		हाल BCM_SYSPORT_STAT_MIB_TX:
		हाल BCM_SYSPORT_STAT_RUNT:
			अगर (priv->is_lite)
				जारी;

			अगर (s->type != BCM_SYSPORT_STAT_MIB_RX)
				offset = UMAC_MIB_STAT_OFFSET;
			val = umac_पढ़ोl(priv, UMAC_MIB_START + j + offset);
			अवरोध;
		हाल BCM_SYSPORT_STAT_RXCHK:
			val = rxchk_पढ़ोl(priv, s->reg_offset);
			अगर (val == ~0)
				rxchk_ग_लिखोl(priv, 0, s->reg_offset);
			अवरोध;
		हाल BCM_SYSPORT_STAT_RBUF:
			val = rbuf_पढ़ोl(priv, s->reg_offset);
			अगर (val == ~0)
				rbuf_ग_लिखोl(priv, 0, s->reg_offset);
			अवरोध;
		पूर्ण

		j += s->stat_माप;
		p = (अक्षर *)priv + s->stat_offset;
		*(u32 *)p = val;
	पूर्ण

	netअगर_dbg(priv, hw, priv->netdev, "updated MIB counters\n");
पूर्ण

अटल व्योम bcm_sysport_update_tx_stats(काष्ठा bcm_sysport_priv *priv,
					u64 *tx_bytes, u64 *tx_packets)
अणु
	काष्ठा bcm_sysport_tx_ring *ring;
	u64 bytes = 0, packets = 0;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक q;

	क्रम (q = 0; q < priv->netdev->num_tx_queues; q++) अणु
		ring = &priv->tx_rings[q];
		करो अणु
			start = u64_stats_fetch_begin_irq(&priv->syncp);
			bytes = ring->bytes;
			packets = ring->packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&priv->syncp, start));

		*tx_bytes += bytes;
		*tx_packets += packets;
	पूर्ण
पूर्ण

अटल व्योम bcm_sysport_get_stats(काष्ठा net_device *dev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा bcm_sysport_stats64 *stats64 = &priv->stats64;
	काष्ठा u64_stats_sync *syncp = &priv->syncp;
	काष्ठा bcm_sysport_tx_ring *ring;
	u64 tx_bytes = 0, tx_packets = 0;
	अचिन्हित पूर्णांक start;
	पूर्णांक i, j;

	अगर (netअगर_running(dev)) अणु
		bcm_sysport_update_mib_counters(priv);
		bcm_sysport_update_tx_stats(priv, &tx_bytes, &tx_packets);
		stats64->tx_bytes = tx_bytes;
		stats64->tx_packets = tx_packets;
	पूर्ण

	क्रम (i =  0, j = 0; i < BCM_SYSPORT_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcm_sysport_stats *s;
		अक्षर *p;

		s = &bcm_sysport_gstrings_stats[i];
		अगर (s->type == BCM_SYSPORT_STAT_NETDEV)
			p = (अक्षर *)&dev->stats;
		अन्यथा अगर (s->type == BCM_SYSPORT_STAT_NETDEV64)
			p = (अक्षर *)stats64;
		अन्यथा
			p = (अक्षर *)priv;

		अगर (priv->is_lite && !bcm_sysport_lite_stat_valid(s->type))
			जारी;
		p += s->stat_offset;

		अगर (s->stat_माप == माप(u64) &&
		    s->type == BCM_SYSPORT_STAT_NETDEV64) अणु
			करो अणु
				start = u64_stats_fetch_begin_irq(syncp);
				data[i] = *(u64 *)p;
			पूर्ण जबतक (u64_stats_fetch_retry_irq(syncp, start));
		पूर्ण अन्यथा
			data[i] = *(u32 *)p;
		j++;
	पूर्ण

	/* For SYSTEMPORT Lite since we have holes in our statistics, j would
	 * be equal to BCM_SYSPORT_STATS_LEN at the end of the loop, but it
	 * needs to poपूर्णांक to how many total statistics we have minus the
	 * number of per TX queue statistics
	 */
	j = bcm_sysport_get_sset_count(dev, ETH_SS_STATS) -
	    dev->num_tx_queues * NUM_SYSPORT_TXQ_STAT;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		ring = &priv->tx_rings[i];
		data[j] = ring->packets;
		j++;
		data[j] = ring->bytes;
		j++;
	पूर्ण
पूर्ण

अटल व्योम bcm_sysport_get_wol(काष्ठा net_device *dev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);

	wol->supported = WAKE_MAGIC | WAKE_MAGICSECURE | WAKE_FILTER;
	wol->wolopts = priv->wolopts;

	अगर (!(priv->wolopts & WAKE_MAGICSECURE))
		वापस;

	स_नकल(wol->sopass, priv->sopass, माप(priv->sopass));
पूर्ण

अटल पूर्णांक bcm_sysport_set_wol(काष्ठा net_device *dev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा device *kdev = &priv->pdev->dev;
	u32 supported = WAKE_MAGIC | WAKE_MAGICSECURE | WAKE_FILTER;

	अगर (!device_can_wakeup(kdev))
		वापस -ENOTSUPP;

	अगर (wol->wolopts & ~supported)
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGICSECURE)
		स_नकल(priv->sopass, wol->sopass, माप(priv->sopass));

	/* Flag the device and relevant IRQ as wakeup capable */
	अगर (wol->wolopts) अणु
		device_set_wakeup_enable(kdev, 1);
		अगर (priv->wol_irq_disabled)
			enable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = 0;
	पूर्ण अन्यथा अणु
		device_set_wakeup_enable(kdev, 0);
		/* Aव्योम unbalanced disable_irq_wake calls */
		अगर (!priv->wol_irq_disabled)
			disable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = 1;
	पूर्ण

	priv->wolopts = wol->wolopts;

	वापस 0;
पूर्ण

अटल व्योम bcm_sysport_set_rx_coalesce(काष्ठा bcm_sysport_priv *priv,
					u32 usecs, u32 pkts)
अणु
	u32 reg;

	reg = rdma_पढ़ोl(priv, RDMA_MBDONE_INTR);
	reg &= ~(RDMA_INTR_THRESH_MASK |
		 RDMA_TIMEOUT_MASK << RDMA_TIMEOUT_SHIFT);
	reg |= pkts;
	reg |= DIV_ROUND_UP(usecs * 1000, 8192) << RDMA_TIMEOUT_SHIFT;
	rdma_ग_लिखोl(priv, reg, RDMA_MBDONE_INTR);
पूर्ण

अटल व्योम bcm_sysport_set_tx_coalesce(काष्ठा bcm_sysport_tx_ring *ring,
					काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा bcm_sysport_priv *priv = ring->priv;
	u32 reg;

	reg = tdma_पढ़ोl(priv, TDMA_DESC_RING_INTR_CONTROL(ring->index));
	reg &= ~(RING_INTR_THRESH_MASK |
		 RING_TIMEOUT_MASK << RING_TIMEOUT_SHIFT);
	reg |= ec->tx_max_coalesced_frames;
	reg |= DIV_ROUND_UP(ec->tx_coalesce_usecs * 1000, 8192) <<
			    RING_TIMEOUT_SHIFT;
	tdma_ग_लिखोl(priv, reg, TDMA_DESC_RING_INTR_CONTROL(ring->index));
पूर्ण

अटल पूर्णांक bcm_sysport_get_coalesce(काष्ठा net_device *dev,
				    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	u32 reg;

	reg = tdma_पढ़ोl(priv, TDMA_DESC_RING_INTR_CONTROL(0));

	ec->tx_coalesce_usecs = (reg >> RING_TIMEOUT_SHIFT) * 8192 / 1000;
	ec->tx_max_coalesced_frames = reg & RING_INTR_THRESH_MASK;

	reg = rdma_पढ़ोl(priv, RDMA_MBDONE_INTR);

	ec->rx_coalesce_usecs = (reg >> RDMA_TIMEOUT_SHIFT) * 8192 / 1000;
	ec->rx_max_coalesced_frames = reg & RDMA_INTR_THRESH_MASK;
	ec->use_adaptive_rx_coalesce = priv->dim.use_dim;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_set_coalesce(काष्ठा net_device *dev,
				    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा dim_cq_moder moder;
	u32 usecs, pkts;
	अचिन्हित पूर्णांक i;

	/* Base प्रणाली घड़ी is 125Mhz, DMA समयout is this reference घड़ी
	 * भागided by 1024, which yield roughly 8.192 us, our maximum value has
	 * to fit in the RING_TIMEOUT_MASK (16 bits).
	 */
	अगर (ec->tx_max_coalesced_frames > RING_INTR_THRESH_MASK ||
	    ec->tx_coalesce_usecs > (RING_TIMEOUT_MASK * 8) + 1 ||
	    ec->rx_max_coalesced_frames > RDMA_INTR_THRESH_MASK ||
	    ec->rx_coalesce_usecs > (RDMA_TIMEOUT_MASK * 8) + 1)
		वापस -EINVAL;

	अगर ((ec->tx_coalesce_usecs == 0 && ec->tx_max_coalesced_frames == 0) ||
	    (ec->rx_coalesce_usecs == 0 && ec->rx_max_coalesced_frames == 0))
		वापस -EINVAL;

	क्रम (i = 0; i < dev->num_tx_queues; i++)
		bcm_sysport_set_tx_coalesce(&priv->tx_rings[i], ec);

	priv->rx_coalesce_usecs = ec->rx_coalesce_usecs;
	priv->rx_max_coalesced_frames = ec->rx_max_coalesced_frames;
	usecs = priv->rx_coalesce_usecs;
	pkts = priv->rx_max_coalesced_frames;

	अगर (ec->use_adaptive_rx_coalesce && !priv->dim.use_dim) अणु
		moder = net_dim_get_def_rx_moderation(priv->dim.dim.mode);
		usecs = moder.usec;
		pkts = moder.pkts;
	पूर्ण

	priv->dim.use_dim = ec->use_adaptive_rx_coalesce;

	/* Apply desired coalescing parameters */
	bcm_sysport_set_rx_coalesce(priv, usecs, pkts);

	वापस 0;
पूर्ण

अटल व्योम bcm_sysport_मुक्त_cb(काष्ठा bcm_sysport_cb *cb)
अणु
	dev_consume_skb_any(cb->skb);
	cb->skb = शून्य;
	dma_unmap_addr_set(cb, dma_addr, 0);
पूर्ण

अटल काष्ठा sk_buff *bcm_sysport_rx_refill(काष्ठा bcm_sysport_priv *priv,
					     काष्ठा bcm_sysport_cb *cb)
अणु
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा net_device *ndev = priv->netdev;
	काष्ठा sk_buff *skb, *rx_skb;
	dma_addr_t mapping;

	/* Allocate a new SKB क्रम a new packet */
	skb = __netdev_alloc_skb(priv->netdev, RX_BUF_LENGTH,
				 GFP_ATOMIC | __GFP_NOWARN);
	अगर (!skb) अणु
		priv->mib.alloc_rx_buff_failed++;
		netअगर_err(priv, rx_err, ndev, "SKB alloc failed\n");
		वापस शून्य;
	पूर्ण

	mapping = dma_map_single(kdev, skb->data,
				 RX_BUF_LENGTH, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(kdev, mapping)) अणु
		priv->mib.rx_dma_failed++;
		dev_kमुक्त_skb_any(skb);
		netअगर_err(priv, rx_err, ndev, "DMA mapping failure\n");
		वापस शून्य;
	पूर्ण

	/* Grab the current SKB on the ring */
	rx_skb = cb->skb;
	अगर (likely(rx_skb))
		dma_unmap_single(kdev, dma_unmap_addr(cb, dma_addr),
				 RX_BUF_LENGTH, DMA_FROM_DEVICE);

	/* Put the new SKB on the ring */
	cb->skb = skb;
	dma_unmap_addr_set(cb, dma_addr, mapping);
	dma_desc_set_addr(priv, cb->bd_addr, mapping);

	netअगर_dbg(priv, rx_status, ndev, "RX refill\n");

	/* Return the current SKB to the caller */
	वापस rx_skb;
पूर्ण

अटल पूर्णांक bcm_sysport_alloc_rx_bufs(काष्ठा bcm_sysport_priv *priv)
अणु
	काष्ठा bcm_sysport_cb *cb;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_bds; i++) अणु
		cb = &priv->rx_cbs[i];
		skb = bcm_sysport_rx_refill(priv, cb);
		dev_kमुक्त_skb(skb);
		अगर (!cb->skb)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* Poll the hardware क्रम up to budget packets to process */
अटल अचिन्हित पूर्णांक bcm_sysport_desc_rx(काष्ठा bcm_sysport_priv *priv,
					अचिन्हित पूर्णांक budget)
अणु
	काष्ठा bcm_sysport_stats64 *stats64 = &priv->stats64;
	काष्ठा net_device *ndev = priv->netdev;
	अचिन्हित पूर्णांक processed = 0, to_process;
	अचिन्हित पूर्णांक processed_bytes = 0;
	काष्ठा bcm_sysport_cb *cb;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक p_index;
	u16 len, status;
	काष्ठा bcm_rsb *rsb;

	/* Clear status beक्रमe servicing to reduce spurious पूर्णांकerrupts */
	पूर्णांकrl2_0_ग_लिखोl(priv, INTRL2_0_RDMA_MBDONE, INTRL2_CPU_CLEAR);

	/* Determine how much we should process since last call, SYSTEMPORT Lite
	 * groups the producer and consumer indexes पूर्णांकo the same 32-bit
	 * which we access using RDMA_CONS_INDEX
	 */
	अगर (!priv->is_lite)
		p_index = rdma_पढ़ोl(priv, RDMA_PROD_INDEX);
	अन्यथा
		p_index = rdma_पढ़ोl(priv, RDMA_CONS_INDEX);
	p_index &= RDMA_PROD_INDEX_MASK;

	to_process = (p_index - priv->rx_c_index) & RDMA_CONS_INDEX_MASK;

	netअगर_dbg(priv, rx_status, ndev,
		  "p_index=%d rx_c_index=%d to_process=%d\n",
		  p_index, priv->rx_c_index, to_process);

	जबतक ((processed < to_process) && (processed < budget)) अणु
		cb = &priv->rx_cbs[priv->rx_पढ़ो_ptr];
		skb = bcm_sysport_rx_refill(priv, cb);


		/* We करो not have a backing SKB, so we करो not a corresponding
		 * DMA mapping क्रम this incoming packet since
		 * bcm_sysport_rx_refill always either has both skb and mapping
		 * or none.
		 */
		अगर (unlikely(!skb)) अणु
			netअगर_err(priv, rx_err, ndev, "out of memory!\n");
			ndev->stats.rx_dropped++;
			ndev->stats.rx_errors++;
			जाओ next;
		पूर्ण

		/* Extract the Receive Status Block prepended */
		rsb = (काष्ठा bcm_rsb *)skb->data;
		len = (rsb->rx_status_len >> DESC_LEN_SHIFT) & DESC_LEN_MASK;
		status = (rsb->rx_status_len >> DESC_STATUS_SHIFT) &
			  DESC_STATUS_MASK;

		netअगर_dbg(priv, rx_status, ndev,
			  "p=%d, c=%d, rd_ptr=%d, len=%d, flag=0x%04x\n",
			  p_index, priv->rx_c_index, priv->rx_पढ़ो_ptr,
			  len, status);

		अगर (unlikely(len > RX_BUF_LENGTH)) अणु
			netअगर_err(priv, rx_status, ndev, "oversized packet\n");
			ndev->stats.rx_length_errors++;
			ndev->stats.rx_errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण

		अगर (unlikely(!(status & DESC_EOP) || !(status & DESC_SOP))) अणु
			netअगर_err(priv, rx_status, ndev, "fragmented packet!\n");
			ndev->stats.rx_dropped++;
			ndev->stats.rx_errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण

		अगर (unlikely(status & (RX_STATUS_ERR | RX_STATUS_OVFLOW))) अणु
			netअगर_err(priv, rx_err, ndev, "error packet\n");
			अगर (status & RX_STATUS_OVFLOW)
				ndev->stats.rx_over_errors++;
			ndev->stats.rx_dropped++;
			ndev->stats.rx_errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण

		skb_put(skb, len);

		/* Hardware validated our checksum */
		अगर (likely(status & DESC_L4_CSUM))
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		/* Hardware pre-pends packets with 2bytes beक्रमe Ethernet
		 * header plus we have the Receive Status Block, strip off all
		 * of this from the SKB.
		 */
		skb_pull(skb, माप(*rsb) + 2);
		len -= (माप(*rsb) + 2);
		processed_bytes += len;

		/* UniMAC may क्रमward CRC */
		अगर (priv->crc_fwd) अणु
			skb_trim(skb, len - ETH_FCS_LEN);
			len -= ETH_FCS_LEN;
		पूर्ण

		skb->protocol = eth_type_trans(skb, ndev);
		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += len;
		u64_stats_update_begin(&priv->syncp);
		stats64->rx_packets++;
		stats64->rx_bytes += len;
		u64_stats_update_end(&priv->syncp);

		napi_gro_receive(&priv->napi, skb);
next:
		processed++;
		priv->rx_पढ़ो_ptr++;

		अगर (priv->rx_पढ़ो_ptr == priv->num_rx_bds)
			priv->rx_पढ़ो_ptr = 0;
	पूर्ण

	priv->dim.packets = processed;
	priv->dim.bytes = processed_bytes;

	वापस processed;
पूर्ण

अटल व्योम bcm_sysport_tx_reclaim_one(काष्ठा bcm_sysport_tx_ring *ring,
				       काष्ठा bcm_sysport_cb *cb,
				       अचिन्हित पूर्णांक *bytes_compl,
				       अचिन्हित पूर्णांक *pkts_compl)
अणु
	काष्ठा bcm_sysport_priv *priv = ring->priv;
	काष्ठा device *kdev = &priv->pdev->dev;

	अगर (cb->skb) अणु
		*bytes_compl += cb->skb->len;
		dma_unmap_single(kdev, dma_unmap_addr(cb, dma_addr),
				 dma_unmap_len(cb, dma_len),
				 DMA_TO_DEVICE);
		(*pkts_compl)++;
		bcm_sysport_मुक्त_cb(cb);
	/* SKB fragment */
	पूर्ण अन्यथा अगर (dma_unmap_addr(cb, dma_addr)) अणु
		*bytes_compl += dma_unmap_len(cb, dma_len);
		dma_unmap_page(kdev, dma_unmap_addr(cb, dma_addr),
			       dma_unmap_len(cb, dma_len), DMA_TO_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);
	पूर्ण
पूर्ण

/* Reclaim queued SKBs क्रम transmission completion, lockless version */
अटल अचिन्हित पूर्णांक __bcm_sysport_tx_reclaim(काष्ठा bcm_sysport_priv *priv,
					     काष्ठा bcm_sysport_tx_ring *ring)
अणु
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;
	काष्ठा net_device *ndev = priv->netdev;
	अचिन्हित पूर्णांक txbds_processed = 0;
	काष्ठा bcm_sysport_cb *cb;
	अचिन्हित पूर्णांक txbds_पढ़ोy;
	अचिन्हित पूर्णांक c_index;
	u32 hw_ind;

	/* Clear status beक्रमe servicing to reduce spurious पूर्णांकerrupts */
	अगर (!ring->priv->is_lite)
		पूर्णांकrl2_1_ग_लिखोl(ring->priv, BIT(ring->index), INTRL2_CPU_CLEAR);
	अन्यथा
		पूर्णांकrl2_0_ग_लिखोl(ring->priv, BIT(ring->index +
				INTRL2_0_TDMA_MBDONE_SHIFT), INTRL2_CPU_CLEAR);

	/* Compute how many descriptors have been processed since last call */
	hw_ind = tdma_पढ़ोl(priv, TDMA_DESC_RING_PROD_CONS_INDEX(ring->index));
	c_index = (hw_ind >> RING_CONS_INDEX_SHIFT) & RING_CONS_INDEX_MASK;
	txbds_पढ़ोy = (c_index - ring->c_index) & RING_CONS_INDEX_MASK;

	netअगर_dbg(priv, tx_करोne, ndev,
		  "ring=%d old_c_index=%u c_index=%u txbds_ready=%u\n",
		  ring->index, ring->c_index, c_index, txbds_पढ़ोy);

	जबतक (txbds_processed < txbds_पढ़ोy) अणु
		cb = &ring->cbs[ring->clean_index];
		bcm_sysport_tx_reclaim_one(ring, cb, &bytes_compl, &pkts_compl);

		ring->desc_count++;
		txbds_processed++;

		अगर (likely(ring->clean_index < ring->size - 1))
			ring->clean_index++;
		अन्यथा
			ring->clean_index = 0;
	पूर्ण

	u64_stats_update_begin(&priv->syncp);
	ring->packets += pkts_compl;
	ring->bytes += bytes_compl;
	u64_stats_update_end(&priv->syncp);

	ring->c_index = c_index;

	netअगर_dbg(priv, tx_करोne, ndev,
		  "ring=%d c_index=%d pkts_compl=%d, bytes_compl=%d\n",
		  ring->index, ring->c_index, pkts_compl, bytes_compl);

	वापस pkts_compl;
पूर्ण

/* Locked version of the per-ring TX reclaim routine */
अटल अचिन्हित पूर्णांक bcm_sysport_tx_reclaim(काष्ठा bcm_sysport_priv *priv,
					   काष्ठा bcm_sysport_tx_ring *ring)
अणु
	काष्ठा netdev_queue *txq;
	अचिन्हित पूर्णांक released;
	अचिन्हित दीर्घ flags;

	txq = netdev_get_tx_queue(priv->netdev, ring->index);

	spin_lock_irqsave(&ring->lock, flags);
	released = __bcm_sysport_tx_reclaim(priv, ring);
	अगर (released)
		netअगर_tx_wake_queue(txq);

	spin_unlock_irqrestore(&ring->lock, flags);

	वापस released;
पूर्ण

/* Locked version of the per-ring TX reclaim, but करोes not wake the queue */
अटल व्योम bcm_sysport_tx_clean(काष्ठा bcm_sysport_priv *priv,
				 काष्ठा bcm_sysport_tx_ring *ring)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->lock, flags);
	__bcm_sysport_tx_reclaim(priv, ring);
	spin_unlock_irqrestore(&ring->lock, flags);
पूर्ण

अटल पूर्णांक bcm_sysport_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bcm_sysport_tx_ring *ring =
		container_of(napi, काष्ठा bcm_sysport_tx_ring, napi);
	अचिन्हित पूर्णांक work_करोne = 0;

	work_करोne = bcm_sysport_tx_reclaim(ring->priv, ring);

	अगर (work_करोne == 0) अणु
		napi_complete(napi);
		/* re-enable TX पूर्णांकerrupt */
		अगर (!ring->priv->is_lite)
			पूर्णांकrl2_1_mask_clear(ring->priv, BIT(ring->index));
		अन्यथा
			पूर्णांकrl2_0_mask_clear(ring->priv, BIT(ring->index +
					    INTRL2_0_TDMA_MBDONE_SHIFT));

		वापस 0;
	पूर्ण

	वापस budget;
पूर्ण

अटल व्योम bcm_sysport_tx_reclaim_all(काष्ठा bcm_sysport_priv *priv)
अणु
	अचिन्हित पूर्णांक q;

	क्रम (q = 0; q < priv->netdev->num_tx_queues; q++)
		bcm_sysport_tx_reclaim(priv, &priv->tx_rings[q]);
पूर्ण

अटल पूर्णांक bcm_sysport_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bcm_sysport_priv *priv =
		container_of(napi, काष्ठा bcm_sysport_priv, napi);
	काष्ठा dim_sample dim_sample = अणुपूर्ण;
	अचिन्हित पूर्णांक work_करोne = 0;

	work_करोne = bcm_sysport_desc_rx(priv, budget);

	priv->rx_c_index += work_करोne;
	priv->rx_c_index &= RDMA_CONS_INDEX_MASK;

	/* SYSTEMPORT Lite groups the producer/consumer index, producer is
	 * मुख्यtained by HW, but ग_लिखोs to it will be ignore जबतक RDMA
	 * is active
	 */
	अगर (!priv->is_lite)
		rdma_ग_लिखोl(priv, priv->rx_c_index, RDMA_CONS_INDEX);
	अन्यथा
		rdma_ग_लिखोl(priv, priv->rx_c_index << 16, RDMA_CONS_INDEX);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		/* re-enable RX पूर्णांकerrupts */
		पूर्णांकrl2_0_mask_clear(priv, INTRL2_0_RDMA_MBDONE);
	पूर्ण

	अगर (priv->dim.use_dim) अणु
		dim_update_sample(priv->dim.event_ctr, priv->dim.packets,
				  priv->dim.bytes, &dim_sample);
		net_dim(&priv->dim.dim, dim_sample);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम mpd_enable_set(काष्ठा bcm_sysport_priv *priv, bool enable)
अणु
	u32 reg, bit;

	reg = umac_पढ़ोl(priv, UMAC_MPD_CTRL);
	अगर (enable)
		reg |= MPD_EN;
	अन्यथा
		reg &= ~MPD_EN;
	umac_ग_लिखोl(priv, reg, UMAC_MPD_CTRL);

	अगर (priv->is_lite)
		bit = RBUF_ACPI_EN_LITE;
	अन्यथा
		bit = RBUF_ACPI_EN;

	reg = rbuf_पढ़ोl(priv, RBUF_CONTROL);
	अगर (enable)
		reg |= bit;
	अन्यथा
		reg &= ~bit;
	rbuf_ग_लिखोl(priv, reg, RBUF_CONTROL);
पूर्ण

अटल व्योम bcm_sysport_resume_from_wol(काष्ठा bcm_sysport_priv *priv)
अणु
	अचिन्हित पूर्णांक index;
	u32 reg;

	/* Disable RXCHK, active filters and Broadcom tag matching */
	reg = rxchk_पढ़ोl(priv, RXCHK_CONTROL);
	reg &= ~(RXCHK_BRCM_TAG_MATCH_MASK <<
		 RXCHK_BRCM_TAG_MATCH_SHIFT | RXCHK_EN | RXCHK_BRCM_TAG_EN);
	rxchk_ग_लिखोl(priv, reg, RXCHK_CONTROL);

	/* Make sure we restore correct CID index in हाल HW lost
	 * its context during deep idle state
	 */
	क्रम_each_set_bit(index, priv->filters, RXCHK_BRCM_TAG_MAX) अणु
		rxchk_ग_लिखोl(priv, priv->filters_loc[index] <<
			     RXCHK_BRCM_TAG_CID_SHIFT, RXCHK_BRCM_TAG(index));
		rxchk_ग_लिखोl(priv, 0xff00ffff, RXCHK_BRCM_TAG_MASK(index));
	पूर्ण

	/* Clear the MagicPacket detection logic */
	mpd_enable_set(priv, false);

	reg = पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_STATUS);
	अगर (reg & INTRL2_0_MPD)
		netdev_info(priv->netdev, "Wake-on-LAN (MPD) interrupt!\n");

	अगर (reg & INTRL2_0_BRCM_MATCH_TAG) अणु
		reg = rxchk_पढ़ोl(priv, RXCHK_BRCM_TAG_MATCH_STATUS) &
				  RXCHK_BRCM_TAG_MATCH_MASK;
		netdev_info(priv->netdev,
			    "Wake-on-LAN (filters 0x%02x) interrupt!\n", reg);
	पूर्ण

	netअगर_dbg(priv, wol, priv->netdev, "resumed from WOL\n");
पूर्ण

अटल व्योम bcm_sysport_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा bcm_sysport_net_dim *ndim =
			container_of(dim, काष्ठा bcm_sysport_net_dim, dim);
	काष्ठा bcm_sysport_priv *priv =
			container_of(ndim, काष्ठा bcm_sysport_priv, dim);
	काष्ठा dim_cq_moder cur_profile = net_dim_get_rx_moderation(dim->mode,
								    dim->profile_ix);

	bcm_sysport_set_rx_coalesce(priv, cur_profile.usec, cur_profile.pkts);
	dim->state = DIM_START_MEASURE;
पूर्ण

/* RX and misc पूर्णांकerrupt routine */
अटल irqवापस_t bcm_sysport_rx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा bcm_sysport_tx_ring *txr;
	अचिन्हित पूर्णांक ring, ring_bit;

	priv->irq0_stat = पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_STATUS) &
			  ~पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_MASK_STATUS);
	पूर्णांकrl2_0_ग_लिखोl(priv, priv->irq0_stat, INTRL2_CPU_CLEAR);

	अगर (unlikely(priv->irq0_stat == 0)) अणु
		netdev_warn(priv->netdev, "spurious RX interrupt\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर (priv->irq0_stat & INTRL2_0_RDMA_MBDONE) अणु
		priv->dim.event_ctr++;
		अगर (likely(napi_schedule_prep(&priv->napi))) अणु
			/* disable RX पूर्णांकerrupts */
			पूर्णांकrl2_0_mask_set(priv, INTRL2_0_RDMA_MBDONE);
			__napi_schedule_irqoff(&priv->napi);
		पूर्ण
	पूर्ण

	/* TX ring is full, perक्रमm a full reclaim since we करो not know
	 * which one would trigger this पूर्णांकerrupt
	 */
	अगर (priv->irq0_stat & INTRL2_0_TX_RING_FULL)
		bcm_sysport_tx_reclaim_all(priv);

	अगर (!priv->is_lite)
		जाओ out;

	क्रम (ring = 0; ring < dev->num_tx_queues; ring++) अणु
		ring_bit = BIT(ring + INTRL2_0_TDMA_MBDONE_SHIFT);
		अगर (!(priv->irq0_stat & ring_bit))
			जारी;

		txr = &priv->tx_rings[ring];

		अगर (likely(napi_schedule_prep(&txr->napi))) अणु
			पूर्णांकrl2_0_mask_set(priv, ring_bit);
			__napi_schedule(&txr->napi);
		पूर्ण
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

/* TX पूर्णांकerrupt service routine */
अटल irqवापस_t bcm_sysport_tx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा bcm_sysport_tx_ring *txr;
	अचिन्हित पूर्णांक ring;

	priv->irq1_stat = पूर्णांकrl2_1_पढ़ोl(priv, INTRL2_CPU_STATUS) &
				~पूर्णांकrl2_1_पढ़ोl(priv, INTRL2_CPU_MASK_STATUS);
	पूर्णांकrl2_1_ग_लिखोl(priv, 0xffffffff, INTRL2_CPU_CLEAR);

	अगर (unlikely(priv->irq1_stat == 0)) अणु
		netdev_warn(priv->netdev, "spurious TX interrupt\n");
		वापस IRQ_NONE;
	पूर्ण

	क्रम (ring = 0; ring < dev->num_tx_queues; ring++) अणु
		अगर (!(priv->irq1_stat & BIT(ring)))
			जारी;

		txr = &priv->tx_rings[ring];

		अगर (likely(napi_schedule_prep(&txr->napi))) अणु
			पूर्णांकrl2_1_mask_set(priv, BIT(ring));
			__napi_schedule_irqoff(&txr->napi);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bcm_sysport_wol_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_sysport_priv *priv = dev_id;

	pm_wakeup_event(&priv->pdev->dev, 0);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम bcm_sysport_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);

	disable_irq(priv->irq0);
	bcm_sysport_rx_isr(priv->irq0, priv);
	enable_irq(priv->irq0);

	अगर (!priv->is_lite) अणु
		disable_irq(priv->irq1);
		bcm_sysport_tx_isr(priv->irq1, priv);
		enable_irq(priv->irq1);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा sk_buff *bcm_sysport_insert_tsb(काष्ठा sk_buff *skb,
					      काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा sk_buff *nskb;
	काष्ठा bcm_tsb *tsb;
	u32 csum_info;
	u8 ip_proto;
	u16 csum_start;
	__be16 ip_ver;

	/* Re-allocate SKB अगर needed */
	अगर (unlikely(skb_headroom(skb) < माप(*tsb))) अणु
		nskb = skb_पुनः_स्मृति_headroom(skb, माप(*tsb));
		अगर (!nskb) अणु
			dev_kमुक्त_skb_any(skb);
			priv->mib.tx_पुनः_स्मृति_tsb_failed++;
			dev->stats.tx_errors++;
			dev->stats.tx_dropped++;
			वापस शून्य;
		पूर्ण
		dev_consume_skb_any(skb);
		skb = nskb;
		priv->mib.tx_पुनः_स्मृति_tsb++;
	पूर्ण

	tsb = skb_push(skb, माप(*tsb));
	/* Zero-out TSB by शेष */
	स_रखो(tsb, 0, माप(*tsb));

	अगर (skb_vlan_tag_present(skb)) अणु
		tsb->pcp_dei_vid = skb_vlan_tag_get_prio(skb) & PCP_DEI_MASK;
		tsb->pcp_dei_vid |= (u32)skb_vlan_tag_get_id(skb) << VID_SHIFT;
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		ip_ver = skb->protocol;
		चयन (ip_ver) अणु
		हाल htons(ETH_P_IP):
			ip_proto = ip_hdr(skb)->protocol;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			ip_proto = ipv6_hdr(skb)->nexthdr;
			अवरोध;
		शेष:
			वापस skb;
		पूर्ण

		/* Get the checksum offset and the L4 (transport) offset */
		csum_start = skb_checksum_start_offset(skb) - माप(*tsb);
		/* Account क्रम the HW inserted VLAN tag */
		अगर (skb_vlan_tag_present(skb))
			csum_start += VLAN_HLEN;
		csum_info = (csum_start + skb->csum_offset) & L4_CSUM_PTR_MASK;
		csum_info |= (csum_start << L4_PTR_SHIFT);

		अगर (ip_proto == IPPROTO_TCP || ip_proto == IPPROTO_UDP) अणु
			csum_info |= L4_LENGTH_VALID;
			अगर (ip_proto == IPPROTO_UDP &&
			    ip_ver == htons(ETH_P_IP))
				csum_info |= L4_UDP;
		पूर्ण अन्यथा अणु
			csum_info = 0;
		पूर्ण

		tsb->l4_ptr_dest_map = csum_info;
	पूर्ण

	वापस skb;
पूर्ण

अटल netdev_tx_t bcm_sysport_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा bcm_sysport_tx_ring *ring;
	काष्ठा bcm_sysport_cb *cb;
	काष्ठा netdev_queue *txq;
	u32 len_status, addr_lo;
	अचिन्हित पूर्णांक skb_len;
	अचिन्हित दीर्घ flags;
	dma_addr_t mapping;
	u16 queue;
	पूर्णांक ret;

	queue = skb_get_queue_mapping(skb);
	txq = netdev_get_tx_queue(dev, queue);
	ring = &priv->tx_rings[queue];

	/* lock against tx reclaim in BH context and TX ring full पूर्णांकerrupt */
	spin_lock_irqsave(&ring->lock, flags);
	अगर (unlikely(ring->desc_count == 0)) अणु
		netअगर_tx_stop_queue(txq);
		netdev_err(dev, "queue %d awake and ring full!\n", queue);
		ret = NETDEV_TX_BUSY;
		जाओ out;
	पूर्ण

	/* Insert TSB and checksum infos */
	अगर (priv->tsb_en) अणु
		skb = bcm_sysport_insert_tsb(skb, dev);
		अगर (!skb) अणु
			ret = NETDEV_TX_OK;
			जाओ out;
		पूर्ण
	पूर्ण

	skb_len = skb->len;

	mapping = dma_map_single(kdev, skb->data, skb_len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(kdev, mapping)) अणु
		priv->mib.tx_dma_failed++;
		netअगर_err(priv, tx_err, dev, "DMA map failed at %p (len=%d)\n",
			  skb->data, skb_len);
		ret = NETDEV_TX_OK;
		जाओ out;
	पूर्ण

	/* Remember the SKB क्रम future मुक्तing */
	cb = &ring->cbs[ring->curr_desc];
	cb->skb = skb;
	dma_unmap_addr_set(cb, dma_addr, mapping);
	dma_unmap_len_set(cb, dma_len, skb_len);

	addr_lo = lower_32_bits(mapping);
	len_status = upper_32_bits(mapping) & DESC_ADDR_HI_MASK;
	len_status |= (skb_len << DESC_LEN_SHIFT);
	len_status |= (DESC_SOP | DESC_EOP | TX_STATUS_APP_CRC) <<
		       DESC_STATUS_SHIFT;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		len_status |= (DESC_L4_CSUM << DESC_STATUS_SHIFT);
	अगर (skb_vlan_tag_present(skb))
		len_status |= (TX_STATUS_VLAN_VID_TSB << DESC_STATUS_SHIFT);

	ring->curr_desc++;
	अगर (ring->curr_desc == ring->size)
		ring->curr_desc = 0;
	ring->desc_count--;

	/* Ports are latched, so ग_लिखो upper address first */
	tdma_ग_लिखोl(priv, len_status, TDMA_WRITE_PORT_HI(ring->index));
	tdma_ग_लिखोl(priv, addr_lo, TDMA_WRITE_PORT_LO(ring->index));

	/* Check ring space and update SW control flow */
	अगर (ring->desc_count == 0)
		netअगर_tx_stop_queue(txq);

	netअगर_dbg(priv, tx_queued, dev, "ring=%d desc_count=%d, curr_desc=%d\n",
		  ring->index, ring->desc_count, ring->curr_desc);

	ret = NETDEV_TX_OK;
out:
	spin_unlock_irqrestore(&ring->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम bcm_sysport_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	netdev_warn(dev, "transmit timeout!\n");

	netअगर_trans_update(dev);
	dev->stats.tx_errors++;

	netअगर_tx_wake_all_queues(dev);
पूर्ण

/* phylib adjust link callback */
अटल व्योम bcm_sysport_adj_link(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	अचिन्हित पूर्णांक changed = 0;
	u32 cmd_bits = 0, reg;

	अगर (priv->old_link != phydev->link) अणु
		changed = 1;
		priv->old_link = phydev->link;
	पूर्ण

	अगर (priv->old_duplex != phydev->duplex) अणु
		changed = 1;
		priv->old_duplex = phydev->duplex;
	पूर्ण

	अगर (priv->is_lite)
		जाओ out;

	चयन (phydev->speed) अणु
	हाल SPEED_2500:
		cmd_bits = CMD_SPEED_2500;
		अवरोध;
	हाल SPEED_1000:
		cmd_bits = CMD_SPEED_1000;
		अवरोध;
	हाल SPEED_100:
		cmd_bits = CMD_SPEED_100;
		अवरोध;
	हाल SPEED_10:
		cmd_bits = CMD_SPEED_10;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	cmd_bits <<= CMD_SPEED_SHIFT;

	अगर (phydev->duplex == DUPLEX_HALF)
		cmd_bits |= CMD_HD_EN;

	अगर (priv->old_छोड़ो != phydev->छोड़ो) अणु
		changed = 1;
		priv->old_छोड़ो = phydev->छोड़ो;
	पूर्ण

	अगर (!phydev->छोड़ो)
		cmd_bits |= CMD_RX_PAUSE_IGNORE | CMD_TX_PAUSE_IGNORE;

	अगर (!changed)
		वापस;

	अगर (phydev->link) अणु
		reg = umac_पढ़ोl(priv, UMAC_CMD);
		reg &= ~((CMD_SPEED_MASK << CMD_SPEED_SHIFT) |
			CMD_HD_EN | CMD_RX_PAUSE_IGNORE |
			CMD_TX_PAUSE_IGNORE);
		reg |= cmd_bits;
		umac_ग_लिखोl(priv, reg, UMAC_CMD);
	पूर्ण
out:
	अगर (changed)
		phy_prपूर्णांक_status(phydev);
पूर्ण

अटल व्योम bcm_sysport_init_dim(काष्ठा bcm_sysport_priv *priv,
				 व्योम (*cb)(काष्ठा work_काष्ठा *work))
अणु
	काष्ठा bcm_sysport_net_dim *dim = &priv->dim;

	INIT_WORK(&dim->dim.work, cb);
	dim->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
	dim->event_ctr = 0;
	dim->packets = 0;
	dim->bytes = 0;
पूर्ण

अटल व्योम bcm_sysport_init_rx_coalesce(काष्ठा bcm_sysport_priv *priv)
अणु
	काष्ठा bcm_sysport_net_dim *dim = &priv->dim;
	काष्ठा dim_cq_moder moder;
	u32 usecs, pkts;

	usecs = priv->rx_coalesce_usecs;
	pkts = priv->rx_max_coalesced_frames;

	/* If DIM was enabled, re-apply शेष parameters */
	अगर (dim->use_dim) अणु
		moder = net_dim_get_def_rx_moderation(dim->dim.mode);
		usecs = moder.usec;
		pkts = moder.pkts;
	पूर्ण

	bcm_sysport_set_rx_coalesce(priv, usecs, pkts);
पूर्ण

अटल पूर्णांक bcm_sysport_init_tx_ring(काष्ठा bcm_sysport_priv *priv,
				    अचिन्हित पूर्णांक index)
अणु
	काष्ठा bcm_sysport_tx_ring *ring = &priv->tx_rings[index];
	माप_प्रकार size;
	u32 reg;

	/* Simple descriptors partitioning क्रम now */
	size = 256;

	ring->cbs = kसुस्मृति(size, माप(काष्ठा bcm_sysport_cb), GFP_KERNEL);
	अगर (!ring->cbs) अणु
		netअगर_err(priv, hw, priv->netdev, "CB allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* Initialize SW view of the ring */
	spin_lock_init(&ring->lock);
	ring->priv = priv;
	netअगर_tx_napi_add(priv->netdev, &ring->napi, bcm_sysport_tx_poll, 64);
	ring->index = index;
	ring->size = size;
	ring->clean_index = 0;
	ring->alloc_size = ring->size;
	ring->desc_count = ring->size;
	ring->curr_desc = 0;

	/* Initialize HW ring */
	tdma_ग_लिखोl(priv, RING_EN, TDMA_DESC_RING_HEAD_TAIL_PTR(index));
	tdma_ग_लिखोl(priv, 0, TDMA_DESC_RING_COUNT(index));
	tdma_ग_लिखोl(priv, 1, TDMA_DESC_RING_INTR_CONTROL(index));
	tdma_ग_लिखोl(priv, 0, TDMA_DESC_RING_PROD_CONS_INDEX(index));

	/* Configure QID and port mapping */
	reg = tdma_पढ़ोl(priv, TDMA_DESC_RING_MAPPING(index));
	reg &= ~(RING_QID_MASK | RING_PORT_ID_MASK << RING_PORT_ID_SHIFT);
	अगर (ring->inspect) अणु
		reg |= ring->चयन_queue & RING_QID_MASK;
		reg |= ring->चयन_port << RING_PORT_ID_SHIFT;
	पूर्ण अन्यथा अणु
		reg |= RING_IGNORE_STATUS;
	पूर्ण
	tdma_ग_लिखोl(priv, reg, TDMA_DESC_RING_MAPPING(index));
	reg = 0;
	/* Adjust the packet size calculations अगर SYSTEMPORT is responsible
	 * क्रम HW insertion of VLAN tags
	 */
	अगर (priv->netdev->features & NETIF_F_HW_VLAN_CTAG_TX)
		reg = VLAN_HLEN << RING_PKT_SIZE_ADJ_SHIFT;
	tdma_ग_लिखोl(priv, reg, TDMA_DESC_RING_PCP_DEI_VID(index));

	/* Enable ACB algorithm 2 */
	reg = tdma_पढ़ोl(priv, TDMA_CONTROL);
	reg |= tdma_control_bit(priv, ACB_ALGO);
	tdma_ग_लिखोl(priv, reg, TDMA_CONTROL);

	/* Do not use tdma_control_bit() here because TSB_SWAP1 collides
	 * with the original definition of ACB_ALGO
	 */
	reg = tdma_पढ़ोl(priv, TDMA_CONTROL);
	अगर (priv->is_lite)
		reg &= ~BIT(TSB_SWAP1);
	/* Set a correct TSB क्रमmat based on host endian */
	अगर (!IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		reg |= tdma_control_bit(priv, TSB_SWAP0);
	अन्यथा
		reg &= ~tdma_control_bit(priv, TSB_SWAP0);
	tdma_ग_लिखोl(priv, reg, TDMA_CONTROL);

	/* Program the number of descriptors as MAX_THRESHOLD and half of
	 * its size क्रम the hysteresis trigger
	 */
	tdma_ग_लिखोl(priv, ring->size |
			1 << RING_HYST_THRESH_SHIFT,
			TDMA_DESC_RING_MAX_HYST(index));

	/* Enable the ring queue in the arbiter */
	reg = tdma_पढ़ोl(priv, TDMA_TIER1_ARB_0_QUEUE_EN);
	reg |= (1 << index);
	tdma_ग_लिखोl(priv, reg, TDMA_TIER1_ARB_0_QUEUE_EN);

	napi_enable(&ring->napi);

	netअगर_dbg(priv, hw, priv->netdev,
		  "TDMA cfg, size=%d, switch q=%d,port=%d\n",
		  ring->size, ring->चयन_queue,
		  ring->चयन_port);

	वापस 0;
पूर्ण

अटल व्योम bcm_sysport_fini_tx_ring(काष्ठा bcm_sysport_priv *priv,
				     अचिन्हित पूर्णांक index)
अणु
	काष्ठा bcm_sysport_tx_ring *ring = &priv->tx_rings[index];
	u32 reg;

	/* Caller should stop the TDMA engine */
	reg = tdma_पढ़ोl(priv, TDMA_STATUS);
	अगर (!(reg & TDMA_DISABLED))
		netdev_warn(priv->netdev, "TDMA not stopped!\n");

	/* ring->cbs is the last part in bcm_sysport_init_tx_ring which could
	 * fail, so by checking this poपूर्णांकer we know whether the TX ring was
	 * fully initialized or not.
	 */
	अगर (!ring->cbs)
		वापस;

	napi_disable(&ring->napi);
	netअगर_napi_del(&ring->napi);

	bcm_sysport_tx_clean(priv, ring);

	kमुक्त(ring->cbs);
	ring->cbs = शून्य;
	ring->size = 0;
	ring->alloc_size = 0;

	netअगर_dbg(priv, hw, priv->netdev, "TDMA fini done\n");
पूर्ण

/* RDMA helper */
अटल अंतरभूत पूर्णांक rdma_enable_set(काष्ठा bcm_sysport_priv *priv,
				  अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u32 reg;

	reg = rdma_पढ़ोl(priv, RDMA_CONTROL);
	अगर (enable)
		reg |= RDMA_EN;
	अन्यथा
		reg &= ~RDMA_EN;
	rdma_ग_लिखोl(priv, reg, RDMA_CONTROL);

	/* Poll क्रम RMDA disabling completion */
	करो अणु
		reg = rdma_पढ़ोl(priv, RDMA_STATUS);
		अगर (!!(reg & RDMA_DISABLED) == !enable)
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण जबतक (समयout-- > 0);

	netdev_err(priv->netdev, "timeout waiting for RDMA to finish\n");

	वापस -ETIMEDOUT;
पूर्ण

/* TDMA helper */
अटल अंतरभूत पूर्णांक tdma_enable_set(काष्ठा bcm_sysport_priv *priv,
				  अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u32 reg;

	reg = tdma_पढ़ोl(priv, TDMA_CONTROL);
	अगर (enable)
		reg |= tdma_control_bit(priv, TDMA_EN);
	अन्यथा
		reg &= ~tdma_control_bit(priv, TDMA_EN);
	tdma_ग_लिखोl(priv, reg, TDMA_CONTROL);

	/* Poll क्रम TMDA disabling completion */
	करो अणु
		reg = tdma_पढ़ोl(priv, TDMA_STATUS);
		अगर (!!(reg & TDMA_DISABLED) == !enable)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समयout-- > 0);

	netdev_err(priv->netdev, "timeout waiting for TDMA to finish\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक bcm_sysport_init_rx_ring(काष्ठा bcm_sysport_priv *priv)
अणु
	काष्ठा bcm_sysport_cb *cb;
	u32 reg;
	पूर्णांक ret;
	पूर्णांक i;

	/* Initialize SW view of the RX ring */
	priv->num_rx_bds = priv->num_rx_desc_words / WORDS_PER_DESC;
	priv->rx_bds = priv->base + SYS_PORT_RDMA_OFFSET;
	priv->rx_c_index = 0;
	priv->rx_पढ़ो_ptr = 0;
	priv->rx_cbs = kसुस्मृति(priv->num_rx_bds, माप(काष्ठा bcm_sysport_cb),
				GFP_KERNEL);
	अगर (!priv->rx_cbs) अणु
		netअगर_err(priv, hw, priv->netdev, "CB allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_bds; i++) अणु
		cb = priv->rx_cbs + i;
		cb->bd_addr = priv->rx_bds + i * DESC_SIZE;
	पूर्ण

	ret = bcm_sysport_alloc_rx_bufs(priv);
	अगर (ret) अणु
		netअगर_err(priv, hw, priv->netdev, "SKB allocation failed\n");
		वापस ret;
	पूर्ण

	/* Initialize HW, ensure RDMA is disabled */
	reg = rdma_पढ़ोl(priv, RDMA_STATUS);
	अगर (!(reg & RDMA_DISABLED))
		rdma_enable_set(priv, 0);

	rdma_ग_लिखोl(priv, 0, RDMA_WRITE_PTR_LO);
	rdma_ग_लिखोl(priv, 0, RDMA_WRITE_PTR_HI);
	rdma_ग_लिखोl(priv, 0, RDMA_PROD_INDEX);
	rdma_ग_लिखोl(priv, 0, RDMA_CONS_INDEX);
	rdma_ग_लिखोl(priv, priv->num_rx_bds << RDMA_RING_SIZE_SHIFT |
			  RX_BUF_LENGTH, RDMA_RING_BUF_SIZE);
	/* Operate the queue in ring mode */
	rdma_ग_लिखोl(priv, 0, RDMA_START_ADDR_HI);
	rdma_ग_लिखोl(priv, 0, RDMA_START_ADDR_LO);
	rdma_ग_लिखोl(priv, 0, RDMA_END_ADDR_HI);
	rdma_ग_लिखोl(priv, priv->num_rx_desc_words - 1, RDMA_END_ADDR_LO);

	netअगर_dbg(priv, hw, priv->netdev,
		  "RDMA cfg, num_rx_bds=%d, rx_bds=%p\n",
		  priv->num_rx_bds, priv->rx_bds);

	वापस 0;
पूर्ण

अटल व्योम bcm_sysport_fini_rx_ring(काष्ठा bcm_sysport_priv *priv)
अणु
	काष्ठा bcm_sysport_cb *cb;
	अचिन्हित पूर्णांक i;
	u32 reg;

	/* Caller should ensure RDMA is disabled */
	reg = rdma_पढ़ोl(priv, RDMA_STATUS);
	अगर (!(reg & RDMA_DISABLED))
		netdev_warn(priv->netdev, "RDMA not stopped!\n");

	क्रम (i = 0; i < priv->num_rx_bds; i++) अणु
		cb = &priv->rx_cbs[i];
		अगर (dma_unmap_addr(cb, dma_addr))
			dma_unmap_single(&priv->pdev->dev,
					 dma_unmap_addr(cb, dma_addr),
					 RX_BUF_LENGTH, DMA_FROM_DEVICE);
		bcm_sysport_मुक्त_cb(cb);
	पूर्ण

	kमुक्त(priv->rx_cbs);
	priv->rx_cbs = शून्य;

	netअगर_dbg(priv, hw, priv->netdev, "RDMA fini done\n");
पूर्ण

अटल व्योम bcm_sysport_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	u32 reg;

	अगर (priv->is_lite)
		वापस;

	reg = umac_पढ़ोl(priv, UMAC_CMD);
	अगर (dev->flags & IFF_PROMISC)
		reg |= CMD_PROMISC;
	अन्यथा
		reg &= ~CMD_PROMISC;
	umac_ग_लिखोl(priv, reg, UMAC_CMD);

	/* No support क्रम ALLMULTI */
	अगर (dev->flags & IFF_ALLMULTI)
		वापस;
पूर्ण

अटल अंतरभूत व्योम umac_enable_set(काष्ठा bcm_sysport_priv *priv,
				   u32 mask, अचिन्हित पूर्णांक enable)
अणु
	u32 reg;

	अगर (!priv->is_lite) अणु
		reg = umac_पढ़ोl(priv, UMAC_CMD);
		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;
		umac_ग_लिखोl(priv, reg, UMAC_CMD);
	पूर्ण अन्यथा अणु
		reg = gib_पढ़ोl(priv, GIB_CONTROL);
		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;
		gib_ग_लिखोl(priv, reg, GIB_CONTROL);
	पूर्ण

	/* UniMAC stops on a packet boundary, रुको क्रम a full-sized packet
	 * to be processed (1 msec).
	 */
	अगर (enable == 0)
		usleep_range(1000, 2000);
पूर्ण

अटल अंतरभूत व्योम umac_reset(काष्ठा bcm_sysport_priv *priv)
अणु
	u32 reg;

	अगर (priv->is_lite)
		वापस;

	reg = umac_पढ़ोl(priv, UMAC_CMD);
	reg |= CMD_SW_RESET;
	umac_ग_लिखोl(priv, reg, UMAC_CMD);
	udelay(10);
	reg = umac_पढ़ोl(priv, UMAC_CMD);
	reg &= ~CMD_SW_RESET;
	umac_ग_लिखोl(priv, reg, UMAC_CMD);
पूर्ण

अटल व्योम umac_set_hw_addr(काष्ठा bcm_sysport_priv *priv,
			     अचिन्हित अक्षर *addr)
अणु
	u32 mac0 = (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) |
		    addr[3];
	u32 mac1 = (addr[4] << 8) | addr[5];

	अगर (!priv->is_lite) अणु
		umac_ग_लिखोl(priv, mac0, UMAC_MAC0);
		umac_ग_लिखोl(priv, mac1, UMAC_MAC1);
	पूर्ण अन्यथा अणु
		gib_ग_लिखोl(priv, mac0, GIB_MAC0);
		gib_ग_लिखोl(priv, mac1, GIB_MAC1);
	पूर्ण
पूर्ण

अटल व्योम topctrl_flush(काष्ठा bcm_sysport_priv *priv)
अणु
	topctrl_ग_लिखोl(priv, RX_FLUSH, RX_FLUSH_CNTL);
	topctrl_ग_लिखोl(priv, TX_FLUSH, TX_FLUSH_CNTL);
	mdelay(1);
	topctrl_ग_लिखोl(priv, 0, RX_FLUSH_CNTL);
	topctrl_ग_लिखोl(priv, 0, TX_FLUSH_CNTL);
पूर्ण

अटल पूर्णांक bcm_sysport_change_mac(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EINVAL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	/* पूर्णांकerface is disabled, changes to MAC will be reflected on next
	 * खोलो call
	 */
	अगर (!netअगर_running(dev))
		वापस 0;

	umac_set_hw_addr(priv, dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम bcm_sysport_get_stats64(काष्ठा net_device *dev,
				    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा bcm_sysport_stats64 *stats64 = &priv->stats64;
	अचिन्हित पूर्णांक start;

	netdev_stats_to_stats64(stats, &dev->stats);

	bcm_sysport_update_tx_stats(priv, &stats->tx_bytes,
				    &stats->tx_packets);

	करो अणु
		start = u64_stats_fetch_begin_irq(&priv->syncp);
		stats->rx_packets = stats64->rx_packets;
		stats->rx_bytes = stats64->rx_bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&priv->syncp, start));
पूर्ण

अटल व्योम bcm_sysport_netअगर_start(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);

	/* Enable NAPI */
	bcm_sysport_init_dim(priv, bcm_sysport_dim_work);
	bcm_sysport_init_rx_coalesce(priv);
	napi_enable(&priv->napi);

	/* Enable RX पूर्णांकerrupt and TX ring full पूर्णांकerrupt */
	पूर्णांकrl2_0_mask_clear(priv, INTRL2_0_RDMA_MBDONE | INTRL2_0_TX_RING_FULL);

	phy_start(dev->phydev);

	/* Enable TX पूर्णांकerrupts क्रम the TXQs */
	अगर (!priv->is_lite)
		पूर्णांकrl2_1_mask_clear(priv, 0xffffffff);
	अन्यथा
		पूर्णांकrl2_0_mask_clear(priv, INTRL2_0_TDMA_MBDONE_MASK);
पूर्ण

अटल व्योम rbuf_init(काष्ठा bcm_sysport_priv *priv)
अणु
	u32 reg;

	reg = rbuf_पढ़ोl(priv, RBUF_CONTROL);
	reg |= RBUF_4B_ALGN | RBUF_RSB_EN;
	/* Set a correct RSB क्रमmat on SYSTEMPORT Lite */
	अगर (priv->is_lite)
		reg &= ~RBUF_RSB_SWAP1;

	/* Set a correct RSB क्रमmat based on host endian */
	अगर (!IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		reg |= RBUF_RSB_SWAP0;
	अन्यथा
		reg &= ~RBUF_RSB_SWAP0;
	rbuf_ग_लिखोl(priv, reg, RBUF_CONTROL);
पूर्ण

अटल अंतरभूत व्योम bcm_sysport_mask_all_पूर्णांकrs(काष्ठा bcm_sysport_priv *priv)
अणु
	पूर्णांकrl2_0_mask_set(priv, 0xffffffff);
	पूर्णांकrl2_0_ग_लिखोl(priv, 0xffffffff, INTRL2_CPU_CLEAR);
	अगर (!priv->is_lite) अणु
		पूर्णांकrl2_1_mask_set(priv, 0xffffffff);
		पूर्णांकrl2_1_ग_लिखोl(priv, 0xffffffff, INTRL2_CPU_CLEAR);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gib_set_pad_extension(काष्ठा bcm_sysport_priv *priv)
अणु
	u32 reg;

	reg = gib_पढ़ोl(priv, GIB_CONTROL);
	/* Include Broadcom tag in pad extension and fix up IPG_LENGTH */
	अगर (netdev_uses_dsa(priv->netdev)) अणु
		reg &= ~(GIB_PAD_EXTENSION_MASK << GIB_PAD_EXTENSION_SHIFT);
		reg |= ENET_BRCM_TAG_LEN << GIB_PAD_EXTENSION_SHIFT;
	पूर्ण
	reg &= ~(GIB_IPG_LEN_MASK << GIB_IPG_LEN_SHIFT);
	reg |= 12 << GIB_IPG_LEN_SHIFT;
	gib_ग_लिखोl(priv, reg, GIB_CONTROL);
पूर्ण

अटल पूर्णांक bcm_sysport_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	clk_prepare_enable(priv->clk);

	/* Reset UniMAC */
	umac_reset(priv);

	/* Flush TX and RX FIFOs at TOPCTRL level */
	topctrl_flush(priv);

	/* Disable the UniMAC RX/TX */
	umac_enable_set(priv, CMD_RX_EN | CMD_TX_EN, 0);

	/* Enable RBUF 2bytes alignment and Receive Status Block */
	rbuf_init(priv);

	/* Set maximum frame length */
	अगर (!priv->is_lite)
		umac_ग_लिखोl(priv, UMAC_MAX_MTU_SIZE, UMAC_MAX_FRAME_LEN);
	अन्यथा
		gib_set_pad_extension(priv);

	/* Apply features again in हाल we changed them जबतक पूर्णांकerface was
	 * करोwn
	 */
	bcm_sysport_set_features(dev, dev->features);

	/* Set MAC address */
	umac_set_hw_addr(priv, dev->dev_addr);

	phydev = of_phy_connect(dev, priv->phy_dn, bcm_sysport_adj_link,
				0, priv->phy_पूर्णांकerface);
	अगर (!phydev) अणु
		netdev_err(dev, "could not attach to PHY\n");
		ret = -ENODEV;
		जाओ out_clk_disable;
	पूर्ण

	/* Reset house keeping link status */
	priv->old_duplex = -1;
	priv->old_link = -1;
	priv->old_छोड़ो = -1;

	/* mask all पूर्णांकerrupts and request them */
	bcm_sysport_mask_all_पूर्णांकrs(priv);

	ret = request_irq(priv->irq0, bcm_sysport_rx_isr, 0, dev->name, dev);
	अगर (ret) अणु
		netdev_err(dev, "failed to request RX interrupt\n");
		जाओ out_phy_disconnect;
	पूर्ण

	अगर (!priv->is_lite) अणु
		ret = request_irq(priv->irq1, bcm_sysport_tx_isr, 0,
				  dev->name, dev);
		अगर (ret) अणु
			netdev_err(dev, "failed to request TX interrupt\n");
			जाओ out_मुक्त_irq0;
		पूर्ण
	पूर्ण

	/* Initialize both hardware and software ring */
	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		ret = bcm_sysport_init_tx_ring(priv, i);
		अगर (ret) अणु
			netdev_err(dev, "failed to initialize TX ring %d\n",
				   i);
			जाओ out_मुक्त_tx_ring;
		पूर्ण
	पूर्ण

	/* Initialize linked-list */
	tdma_ग_लिखोl(priv, TDMA_LL_RAM_INIT_BUSY, TDMA_STATUS);

	/* Initialize RX ring */
	ret = bcm_sysport_init_rx_ring(priv);
	अगर (ret) अणु
		netdev_err(dev, "failed to initialize RX ring\n");
		जाओ out_मुक्त_rx_ring;
	पूर्ण

	/* Turn on RDMA */
	ret = rdma_enable_set(priv, 1);
	अगर (ret)
		जाओ out_मुक्त_rx_ring;

	/* Turn on TDMA */
	ret = tdma_enable_set(priv, 1);
	अगर (ret)
		जाओ out_clear_rx_पूर्णांक;

	/* Turn on UniMAC TX/RX */
	umac_enable_set(priv, CMD_RX_EN | CMD_TX_EN, 1);

	bcm_sysport_netअगर_start(dev);

	netअगर_tx_start_all_queues(dev);

	वापस 0;

out_clear_rx_पूर्णांक:
	पूर्णांकrl2_0_mask_set(priv, INTRL2_0_RDMA_MBDONE | INTRL2_0_TX_RING_FULL);
out_मुक्त_rx_ring:
	bcm_sysport_fini_rx_ring(priv);
out_मुक्त_tx_ring:
	क्रम (i = 0; i < dev->num_tx_queues; i++)
		bcm_sysport_fini_tx_ring(priv, i);
	अगर (!priv->is_lite)
		मुक्त_irq(priv->irq1, dev);
out_मुक्त_irq0:
	मुक्त_irq(priv->irq0, dev);
out_phy_disconnect:
	phy_disconnect(phydev);
out_clk_disable:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल व्योम bcm_sysport_netअगर_stop(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);

	/* stop all software from updating hardware */
	netअगर_tx_disable(dev);
	napi_disable(&priv->napi);
	cancel_work_sync(&priv->dim.dim.work);
	phy_stop(dev->phydev);

	/* mask all पूर्णांकerrupts */
	bcm_sysport_mask_all_पूर्णांकrs(priv);
पूर्ण

अटल पूर्णांक bcm_sysport_stop(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	bcm_sysport_netअगर_stop(dev);

	/* Disable UniMAC RX */
	umac_enable_set(priv, CMD_RX_EN, 0);

	ret = tdma_enable_set(priv, 0);
	अगर (ret) अणु
		netdev_err(dev, "timeout disabling RDMA\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम a maximum packet size to be drained */
	usleep_range(2000, 3000);

	ret = rdma_enable_set(priv, 0);
	अगर (ret) अणु
		netdev_err(dev, "timeout disabling TDMA\n");
		वापस ret;
	पूर्ण

	/* Disable UniMAC TX */
	umac_enable_set(priv, CMD_TX_EN, 0);

	/* Free RX/TX rings SW काष्ठाures */
	क्रम (i = 0; i < dev->num_tx_queues; i++)
		bcm_sysport_fini_tx_ring(priv, i);
	bcm_sysport_fini_rx_ring(priv);

	मुक्त_irq(priv->irq0, dev);
	अगर (!priv->is_lite)
		मुक्त_irq(priv->irq1, dev);

	/* Disconnect from PHY */
	phy_disconnect(dev->phydev);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_rule_find(काष्ठा bcm_sysport_priv *priv,
				 u64 location)
अणु
	अचिन्हित पूर्णांक index;
	u32 reg;

	क्रम_each_set_bit(index, priv->filters, RXCHK_BRCM_TAG_MAX) अणु
		reg = rxchk_पढ़ोl(priv, RXCHK_BRCM_TAG(index));
		reg >>= RXCHK_BRCM_TAG_CID_SHIFT;
		reg &= RXCHK_BRCM_TAG_CID_MASK;
		अगर (reg == location)
			वापस index;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bcm_sysport_rule_get(काष्ठा bcm_sysport_priv *priv,
				काष्ठा ethtool_rxnfc *nfc)
अणु
	पूर्णांक index;

	/* This is not a rule that we know about */
	index = bcm_sysport_rule_find(priv, nfc->fs.location);
	अगर (index < 0)
		वापस -EOPNOTSUPP;

	nfc->fs.ring_cookie = RX_CLS_FLOW_WAKE;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_rule_set(काष्ठा bcm_sysport_priv *priv,
				काष्ठा ethtool_rxnfc *nfc)
अणु
	अचिन्हित पूर्णांक index;
	u32 reg;

	/* We cannot match locations greater than what the classअगरication ID
	 * permits (256 entries)
	 */
	अगर (nfc->fs.location > RXCHK_BRCM_TAG_CID_MASK)
		वापस -E2BIG;

	/* We cannot support flows that are not destined क्रम a wake-up */
	अगर (nfc->fs.ring_cookie != RX_CLS_FLOW_WAKE)
		वापस -EOPNOTSUPP;

	/* All filters are alपढ़ोy in use, we cannot match more rules */
	अगर (biपंचांगap_weight(priv->filters, RXCHK_BRCM_TAG_MAX) ==
	    RXCHK_BRCM_TAG_MAX)
		वापस -ENOSPC;

	index = find_first_zero_bit(priv->filters, RXCHK_BRCM_TAG_MAX);
	अगर (index >= RXCHK_BRCM_TAG_MAX)
		वापस -ENOSPC;

	/* Location is the classअगरication ID, and index is the position
	 * within one of our 8 possible filters to be programmed
	 */
	reg = rxchk_पढ़ोl(priv, RXCHK_BRCM_TAG(index));
	reg &= ~(RXCHK_BRCM_TAG_CID_MASK << RXCHK_BRCM_TAG_CID_SHIFT);
	reg |= nfc->fs.location << RXCHK_BRCM_TAG_CID_SHIFT;
	rxchk_ग_लिखोl(priv, reg, RXCHK_BRCM_TAG(index));
	rxchk_ग_लिखोl(priv, 0xff00ffff, RXCHK_BRCM_TAG_MASK(index));

	priv->filters_loc[index] = nfc->fs.location;
	set_bit(index, priv->filters);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_rule_del(काष्ठा bcm_sysport_priv *priv,
				u64 location)
अणु
	पूर्णांक index;

	/* This is not a rule that we know about */
	index = bcm_sysport_rule_find(priv, location);
	अगर (index < 0)
		वापस -EOPNOTSUPP;

	/* No need to disable this filter अगर it was enabled, this will
	 * be taken care of during suspend समय by bcm_sysport_suspend_to_wol
	 */
	clear_bit(index, priv->filters);
	priv->filters_loc[index] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_get_rxnfc(काष्ठा net_device *dev,
				 काष्ठा ethtool_rxnfc *nfc, u32 *rule_locs)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_GRXCLSRULE:
		ret = bcm_sysport_rule_get(priv, nfc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sysport_set_rxnfc(काष्ठा net_device *dev,
				 काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		ret = bcm_sysport_rule_set(priv, nfc);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = bcm_sysport_rule_del(priv, nfc->fs.location);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bcm_sysport_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_drvinfo		= bcm_sysport_get_drvinfo,
	.get_msglevel		= bcm_sysport_get_msglvl,
	.set_msglevel		= bcm_sysport_set_msglvl,
	.get_link		= ethtool_op_get_link,
	.get_strings		= bcm_sysport_get_strings,
	.get_ethtool_stats	= bcm_sysport_get_stats,
	.get_sset_count		= bcm_sysport_get_sset_count,
	.get_wol		= bcm_sysport_get_wol,
	.set_wol		= bcm_sysport_set_wol,
	.get_coalesce		= bcm_sysport_get_coalesce,
	.set_coalesce		= bcm_sysport_set_coalesce,
	.get_link_ksettings     = phy_ethtool_get_link_ksettings,
	.set_link_ksettings     = phy_ethtool_set_link_ksettings,
	.get_rxnfc		= bcm_sysport_get_rxnfc,
	.set_rxnfc		= bcm_sysport_set_rxnfc,
पूर्ण;

अटल u16 bcm_sysport_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
				    काष्ठा net_device *sb_dev)
अणु
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	u16 queue = skb_get_queue_mapping(skb);
	काष्ठा bcm_sysport_tx_ring *tx_ring;
	अचिन्हित पूर्णांक q, port;

	अगर (!netdev_uses_dsa(dev))
		वापस netdev_pick_tx(dev, skb, शून्य);

	/* DSA tagging layer will have configured the correct queue */
	q = BRCM_TAG_GET_QUEUE(queue);
	port = BRCM_TAG_GET_PORT(queue);
	tx_ring = priv->ring_map[q + port * priv->per_port_num_tx_queues];

	अगर (unlikely(!tx_ring))
		वापस netdev_pick_tx(dev, skb, शून्य);

	वापस tx_ring->index;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bcm_sysport_netdev_ops = अणु
	.nकरो_start_xmit		= bcm_sysport_xmit,
	.nकरो_tx_समयout		= bcm_sysport_tx_समयout,
	.nकरो_खोलो		= bcm_sysport_खोलो,
	.nकरो_stop		= bcm_sysport_stop,
	.nकरो_set_features	= bcm_sysport_set_features,
	.nकरो_set_rx_mode	= bcm_sysport_set_rx_mode,
	.nकरो_set_mac_address	= bcm_sysport_change_mac,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= bcm_sysport_poll_controller,
#पूर्ण_अगर
	.nकरो_get_stats64	= bcm_sysport_get_stats64,
	.nकरो_select_queue	= bcm_sysport_select_queue,
पूर्ण;

अटल पूर्णांक bcm_sysport_map_queues(काष्ठा net_device *dev,
				  काष्ठा net_device *slave_dev)
अणु
	काष्ठा dsa_port *dp = dsa_port_from_netdev(slave_dev);
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा bcm_sysport_tx_ring *ring;
	अचिन्हित पूर्णांक num_tx_queues;
	अचिन्हित पूर्णांक q, qp, port;

	/* We can't be setting up queue inspection क्रम non directly attached
	 * चयनes
	 */
	अगर (dp->ds->index)
		वापस 0;

	port = dp->index;

	/* On SYSTEMPORT Lite we have twice as less queues, so we cannot करो a
	 * 1:1 mapping, we can only करो a 2:1 mapping. By reducing the number of
	 * per-port (slave_dev) network devices queue, we achieve just that.
	 * This need to happen now beक्रमe any slave network device is used such
	 * it accurately reflects the number of real TX queues.
	 */
	अगर (priv->is_lite)
		netअगर_set_real_num_tx_queues(slave_dev,
					     slave_dev->num_tx_queues / 2);

	num_tx_queues = slave_dev->real_num_tx_queues;

	अगर (priv->per_port_num_tx_queues &&
	    priv->per_port_num_tx_queues != num_tx_queues)
		netdev_warn(slave_dev, "asymmetric number of per-port queues\n");

	priv->per_port_num_tx_queues = num_tx_queues;

	क्रम (q = 0, qp = 0; q < dev->num_tx_queues && qp < num_tx_queues;
	     q++) अणु
		ring = &priv->tx_rings[q];

		अगर (ring->inspect)
			जारी;

		/* Just remember the mapping actual programming करोne
		 * during bcm_sysport_init_tx_ring
		 */
		ring->चयन_queue = qp;
		ring->चयन_port = port;
		ring->inspect = true;
		priv->ring_map[qp + port * num_tx_queues] = ring;
		qp++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_unmap_queues(काष्ठा net_device *dev,
				    काष्ठा net_device *slave_dev)
अणु
	काष्ठा dsa_port *dp = dsa_port_from_netdev(slave_dev);
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा bcm_sysport_tx_ring *ring;
	अचिन्हित पूर्णांक num_tx_queues;
	अचिन्हित पूर्णांक q, qp, port;

	port = dp->index;

	num_tx_queues = slave_dev->real_num_tx_queues;

	क्रम (q = 0; q < dev->num_tx_queues; q++) अणु
		ring = &priv->tx_rings[q];

		अगर (ring->चयन_port != port)
			जारी;

		अगर (!ring->inspect)
			जारी;

		ring->inspect = false;
		qp = ring->चयन_queue;
		priv->ring_map[qp + port * num_tx_queues] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_netdevice_event(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा bcm_sysport_priv *priv;
	पूर्णांक ret = 0;

	priv = container_of(nb, काष्ठा bcm_sysport_priv, netdev_notअगरier);
	अगर (priv->netdev != dev)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		अगर (dev->netdev_ops != &bcm_sysport_netdev_ops)
			वापस NOTIFY_DONE;

		अगर (!dsa_slave_dev_check(info->upper_dev))
			वापस NOTIFY_DONE;

		अगर (info->linking)
			ret = bcm_sysport_map_queues(dev, info->upper_dev);
		अन्यथा
			ret = bcm_sysport_unmap_queues(dev, info->upper_dev);
		अवरोध;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

#घोषणा REV_FMT	"v%2x.%02x"

अटल स्थिर काष्ठा bcm_sysport_hw_params bcm_sysport_params[] = अणु
	[SYSTEMPORT] = अणु
		.is_lite = false,
		.num_rx_desc_words = SP_NUM_HW_RX_DESC_WORDS,
	पूर्ण,
	[SYSTEMPORT_LITE] = अणु
		.is_lite = true,
		.num_rx_desc_words = SP_LT_NUM_HW_RX_DESC_WORDS,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_sysport_of_match[] = अणु
	अणु .compatible = "brcm,systemportlite-v1.00",
	  .data = &bcm_sysport_params[SYSTEMPORT_LITE] पूर्ण,
	अणु .compatible = "brcm,systemport-v1.00",
	  .data = &bcm_sysport_params[SYSTEMPORT] पूर्ण,
	अणु .compatible = "brcm,systemport",
	  .data = &bcm_sysport_params[SYSTEMPORT] पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_sysport_of_match);

अटल पूर्णांक bcm_sysport_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा bcm_sysport_hw_params *params;
	स्थिर काष्ठा of_device_id *of_id = शून्य;
	काष्ठा bcm_sysport_priv *priv;
	काष्ठा device_node *dn;
	काष्ठा net_device *dev;
	u32 txq, rxq;
	पूर्णांक ret;

	dn = pdev->dev.of_node;
	of_id = of_match_node(bcm_sysport_of_match, dn);
	अगर (!of_id || !of_id->data)
		वापस -EINVAL;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(40));
	अगर (ret)
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to set DMA mask: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Fairly quickly we need to know the type of adapter we have */
	params = of_id->data;

	/* Read the Transmit/Receive Queue properties */
	अगर (of_property_पढ़ो_u32(dn, "systemport,num-txq", &txq))
		txq = TDMA_NUM_RINGS;
	अगर (of_property_पढ़ो_u32(dn, "systemport,num-rxq", &rxq))
		rxq = 1;

	/* Sanity check the number of transmit queues */
	अगर (!txq || txq > TDMA_NUM_RINGS)
		वापस -EINVAL;

	dev = alloc_etherdev_mqs(माप(*priv), txq, rxq);
	अगर (!dev)
		वापस -ENOMEM;

	/* Initialize निजी members */
	priv = netdev_priv(dev);

	priv->clk = devm_clk_get_optional(&pdev->dev, "sw_sysport");
	अगर (IS_ERR(priv->clk)) अणु
		ret = PTR_ERR(priv->clk);
		जाओ err_मुक्त_netdev;
	पूर्ण

	/* Allocate number of TX rings */
	priv->tx_rings = devm_kसुस्मृति(&pdev->dev, txq,
				      माप(काष्ठा bcm_sysport_tx_ring),
				      GFP_KERNEL);
	अगर (!priv->tx_rings) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण

	priv->is_lite = params->is_lite;
	priv->num_rx_desc_words = params->num_rx_desc_words;

	priv->irq0 = platक्रमm_get_irq(pdev, 0);
	अगर (!priv->is_lite) अणु
		priv->irq1 = platक्रमm_get_irq(pdev, 1);
		priv->wol_irq = platक्रमm_get_irq(pdev, 2);
	पूर्ण अन्यथा अणु
		priv->wol_irq = platक्रमm_get_irq(pdev, 1);
	पूर्ण
	अगर (priv->irq0 <= 0 || (priv->irq1 <= 0 && !priv->is_lite)) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_netdev;
	पूर्ण

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ err_मुक्त_netdev;
	पूर्ण

	priv->netdev = dev;
	priv->pdev = pdev;

	ret = of_get_phy_mode(dn, &priv->phy_पूर्णांकerface);
	/* Default to GMII पूर्णांकerface mode */
	अगर (ret)
		priv->phy_पूर्णांकerface = PHY_INTERFACE_MODE_GMII;

	/* In the हाल of a fixed PHY, the DT node associated
	 * to the PHY is the Ethernet MAC DT node.
	 */
	अगर (of_phy_is_fixed_link(dn)) अणु
		ret = of_phy_रेजिस्टर_fixed_link(dn);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to register fixed PHY\n");
			जाओ err_मुक्त_netdev;
		पूर्ण

		priv->phy_dn = dn;
	पूर्ण

	/* Initialize netdevice members */
	ret = of_get_mac_address(dn, dev->dev_addr);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "using random Ethernet MAC\n");
		eth_hw_addr_अक्रमom(dev);
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev_set_drvdata(&pdev->dev, dev);
	dev->ethtool_ops = &bcm_sysport_ethtool_ops;
	dev->netdev_ops = &bcm_sysport_netdev_ops;
	netअगर_napi_add(dev, &priv->napi, bcm_sysport_poll, 64);

	dev->features |= NETIF_F_RXCSUM | NETIF_F_HIGHDMA |
			 NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			 NETIF_F_HW_VLAN_CTAG_TX;
	dev->hw_features |= dev->features;
	dev->vlan_features |= dev->features;
	dev->max_mtu = UMAC_MAX_MTU_SIZE;

	/* Request the WOL पूर्णांकerrupt and advertise suspend अगर available */
	priv->wol_irq_disabled = 1;
	ret = devm_request_irq(&pdev->dev, priv->wol_irq,
			       bcm_sysport_wol_isr, 0, dev->name, priv);
	अगर (!ret)
		device_set_wakeup_capable(&pdev->dev, 1);

	priv->wol_clk = devm_clk_get_optional(&pdev->dev, "sw_sysportwol");
	अगर (IS_ERR(priv->wol_clk))
		वापस PTR_ERR(priv->wol_clk);

	/* Set the needed headroom once and क्रम all */
	BUILD_BUG_ON(माप(काष्ठा bcm_tsb) != 8);
	dev->needed_headroom += माप(काष्ठा bcm_tsb);

	/* libphy will adjust the link state accordingly */
	netअगर_carrier_off(dev);

	priv->rx_max_coalesced_frames = 1;
	u64_stats_init(&priv->syncp);

	priv->netdev_notअगरier.notअगरier_call = bcm_sysport_netdevice_event;

	ret = रेजिस्टर_netdevice_notअगरier(&priv->netdev_notअगरier);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register DSA notifier\n");
		जाओ err_deरेजिस्टर_fixed_link;
	पूर्ण

	ret = रेजिस्टर_netdev(dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register net_device\n");
		जाओ err_deरेजिस्टर_notअगरier;
	पूर्ण

	clk_prepare_enable(priv->clk);

	priv->rev = topctrl_पढ़ोl(priv, REV_CNTL) & REV_MASK;
	dev_info(&pdev->dev,
		 "Broadcom SYSTEMPORT%s " REV_FMT
		 " (irqs: %d, %d, TXQs: %d, RXQs: %d)\n",
		 priv->is_lite ? " Lite" : "",
		 (priv->rev >> 8) & 0xff, priv->rev & 0xff,
		 priv->irq0, priv->irq1, txq, rxq);

	clk_disable_unprepare(priv->clk);

	वापस 0;

err_deरेजिस्टर_notअगरier:
	unरेजिस्टर_netdevice_notअगरier(&priv->netdev_notअगरier);
err_deरेजिस्टर_fixed_link:
	अगर (of_phy_is_fixed_link(dn))
		of_phy_deरेजिस्टर_fixed_link(dn);
err_मुक्त_netdev:
	मुक्त_netdev(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sysport_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(&pdev->dev);
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	काष्ठा device_node *dn = pdev->dev.of_node;

	/* Not much to करो, nकरो_बंद has been called
	 * and we use managed allocations
	 */
	unरेजिस्टर_netdevice_notअगरier(&priv->netdev_notअगरier);
	unरेजिस्टर_netdev(dev);
	अगर (of_phy_is_fixed_link(dn))
		of_phy_deरेजिस्टर_fixed_link(dn);
	मुक्त_netdev(dev);
	dev_set_drvdata(&pdev->dev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sysport_suspend_to_wol(काष्ठा bcm_sysport_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->netdev;
	अचिन्हित पूर्णांक समयout = 1000;
	अचिन्हित पूर्णांक index, i = 0;
	u32 reg;

	reg = umac_पढ़ोl(priv, UMAC_MPD_CTRL);
	अगर (priv->wolopts & (WAKE_MAGIC | WAKE_MAGICSECURE))
		reg |= MPD_EN;
	reg &= ~PSW_EN;
	अगर (priv->wolopts & WAKE_MAGICSECURE) अणु
		/* Program the SecureOn password */
		umac_ग_लिखोl(priv, get_unaligned_be16(&priv->sopass[0]),
			    UMAC_PSW_MS);
		umac_ग_लिखोl(priv, get_unaligned_be32(&priv->sopass[2]),
			    UMAC_PSW_LS);
		reg |= PSW_EN;
	पूर्ण
	umac_ग_लिखोl(priv, reg, UMAC_MPD_CTRL);

	अगर (priv->wolopts & WAKE_FILTER) अणु
		/* Turn on ACPI matching to steal packets from RBUF */
		reg = rbuf_पढ़ोl(priv, RBUF_CONTROL);
		अगर (priv->is_lite)
			reg |= RBUF_ACPI_EN_LITE;
		अन्यथा
			reg |= RBUF_ACPI_EN;
		rbuf_ग_लिखोl(priv, reg, RBUF_CONTROL);

		/* Enable RXCHK, active filters and Broadcom tag matching */
		reg = rxchk_पढ़ोl(priv, RXCHK_CONTROL);
		reg &= ~(RXCHK_BRCM_TAG_MATCH_MASK <<
			 RXCHK_BRCM_TAG_MATCH_SHIFT);
		क्रम_each_set_bit(index, priv->filters, RXCHK_BRCM_TAG_MAX) अणु
			reg |= BIT(RXCHK_BRCM_TAG_MATCH_SHIFT + i);
			i++;
		पूर्ण
		reg |= RXCHK_EN | RXCHK_BRCM_TAG_EN;
		rxchk_ग_लिखोl(priv, reg, RXCHK_CONTROL);
	पूर्ण

	/* Make sure RBUF entered WoL mode as result */
	करो अणु
		reg = rbuf_पढ़ोl(priv, RBUF_STATUS);
		अगर (reg & RBUF_WOL_MODE)
			अवरोध;

		udelay(10);
	पूर्ण जबतक (समयout-- > 0);

	/* Do not leave the UniMAC RBUF matching only MPD packets */
	अगर (!समयout) अणु
		mpd_enable_set(priv, false);
		netअगर_err(priv, wol, ndev, "failed to enter WOL mode\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* UniMAC receive needs to be turned on */
	umac_enable_set(priv, CMD_RX_EN, 1);

	netअगर_dbg(priv, wol, ndev, "entered WOL mode\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bcm_sysport_suspend(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(d);
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;
	u32 reg;

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_detach(dev);

	bcm_sysport_netअगर_stop(dev);

	phy_suspend(dev->phydev);

	/* Disable UniMAC RX */
	umac_enable_set(priv, CMD_RX_EN, 0);

	ret = rdma_enable_set(priv, 0);
	अगर (ret) अणु
		netdev_err(dev, "RDMA timeout!\n");
		वापस ret;
	पूर्ण

	/* Disable RXCHK अगर enabled */
	अगर (priv->rx_chk_en) अणु
		reg = rxchk_पढ़ोl(priv, RXCHK_CONTROL);
		reg &= ~RXCHK_EN;
		rxchk_ग_लिखोl(priv, reg, RXCHK_CONTROL);
	पूर्ण

	/* Flush RX pipe */
	अगर (!priv->wolopts)
		topctrl_ग_लिखोl(priv, RX_FLUSH, RX_FLUSH_CNTL);

	ret = tdma_enable_set(priv, 0);
	अगर (ret) अणु
		netdev_err(dev, "TDMA timeout!\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम a packet boundary */
	usleep_range(2000, 3000);

	umac_enable_set(priv, CMD_TX_EN, 0);

	topctrl_ग_लिखोl(priv, TX_FLUSH, TX_FLUSH_CNTL);

	/* Free RX/TX rings SW काष्ठाures */
	क्रम (i = 0; i < dev->num_tx_queues; i++)
		bcm_sysport_fini_tx_ring(priv, i);
	bcm_sysport_fini_rx_ring(priv);

	/* Get prepared क्रम Wake-on-LAN */
	अगर (device_may_wakeup(d) && priv->wolopts) अणु
		clk_prepare_enable(priv->wol_clk);
		ret = bcm_sysport_suspend_to_wol(priv);
	पूर्ण

	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused bcm_sysport_resume(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(d);
	काष्ठा bcm_sysport_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!netअगर_running(dev))
		वापस 0;

	clk_prepare_enable(priv->clk);
	अगर (priv->wolopts)
		clk_disable_unprepare(priv->wol_clk);

	umac_reset(priv);

	/* Disable the UniMAC RX/TX */
	umac_enable_set(priv, CMD_RX_EN | CMD_TX_EN, 0);

	/* We may have been suspended and never received a WOL event that
	 * would turn off MPD detection, take care of that now
	 */
	bcm_sysport_resume_from_wol(priv);

	/* Initialize both hardware and software ring */
	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		ret = bcm_sysport_init_tx_ring(priv, i);
		अगर (ret) अणु
			netdev_err(dev, "failed to initialize TX ring %d\n",
				   i);
			जाओ out_मुक्त_tx_rings;
		पूर्ण
	पूर्ण

	/* Initialize linked-list */
	tdma_ग_लिखोl(priv, TDMA_LL_RAM_INIT_BUSY, TDMA_STATUS);

	/* Initialize RX ring */
	ret = bcm_sysport_init_rx_ring(priv);
	अगर (ret) अणु
		netdev_err(dev, "failed to initialize RX ring\n");
		जाओ out_मुक्त_rx_ring;
	पूर्ण

	/* RX pipe enable */
	topctrl_ग_लिखोl(priv, 0, RX_FLUSH_CNTL);

	ret = rdma_enable_set(priv, 1);
	अगर (ret) अणु
		netdev_err(dev, "failed to enable RDMA\n");
		जाओ out_मुक्त_rx_ring;
	पूर्ण

	/* Restore enabled features */
	bcm_sysport_set_features(dev, dev->features);

	rbuf_init(priv);

	/* Set maximum frame length */
	अगर (!priv->is_lite)
		umac_ग_लिखोl(priv, UMAC_MAX_MTU_SIZE, UMAC_MAX_FRAME_LEN);
	अन्यथा
		gib_set_pad_extension(priv);

	/* Set MAC address */
	umac_set_hw_addr(priv, dev->dev_addr);

	umac_enable_set(priv, CMD_RX_EN, 1);

	/* TX pipe enable */
	topctrl_ग_लिखोl(priv, 0, TX_FLUSH_CNTL);

	umac_enable_set(priv, CMD_TX_EN, 1);

	ret = tdma_enable_set(priv, 1);
	अगर (ret) अणु
		netdev_err(dev, "TDMA timeout!\n");
		जाओ out_मुक्त_rx_ring;
	पूर्ण

	phy_resume(dev->phydev);

	bcm_sysport_netअगर_start(dev);

	netअगर_device_attach(dev);

	वापस 0;

out_मुक्त_rx_ring:
	bcm_sysport_fini_rx_ring(priv);
out_मुक्त_tx_rings:
	क्रम (i = 0; i < dev->num_tx_queues; i++)
		bcm_sysport_fini_tx_ring(priv, i);
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(bcm_sysport_pm_ops,
		bcm_sysport_suspend, bcm_sysport_resume);

अटल काष्ठा platक्रमm_driver bcm_sysport_driver = अणु
	.probe	= bcm_sysport_probe,
	.हटाओ	= bcm_sysport_हटाओ,
	.driver =  अणु
		.name = "brcm-systemport",
		.of_match_table = bcm_sysport_of_match,
		.pm = &bcm_sysport_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm_sysport_driver);

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom System Port Ethernet MAC driver");
MODULE_ALIAS("platform:brcm-systemport");
MODULE_LICENSE("GPL");
