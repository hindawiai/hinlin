<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2017-2019 NXP */

#समावेश <linux/net_tstamp.h>
#समावेश <linux/module.h>
#समावेश "enetc.h"

अटल स्थिर u32 enetc_si_regs[] = अणु
	ENETC_SIMR, ENETC_SIPMAR0, ENETC_SIPMAR1, ENETC_SICBDRMR,
	ENETC_SICBDRSR,	ENETC_SICBDRBAR0, ENETC_SICBDRBAR1, ENETC_SICBDRPIR,
	ENETC_SICBDRCIR, ENETC_SICBDRLENR, ENETC_SICAPR0, ENETC_SICAPR1,
	ENETC_SIUEFDCR
पूर्ण;

अटल स्थिर u32 enetc_txbdr_regs[] = अणु
	ENETC_TBMR, ENETC_TBSR, ENETC_TBBAR0, ENETC_TBBAR1,
	ENETC_TBPIR, ENETC_TBCIR, ENETC_TBLENR, ENETC_TBIER, ENETC_TBICR0,
	ENETC_TBICR1
पूर्ण;

अटल स्थिर u32 enetc_rxbdr_regs[] = अणु
	ENETC_RBMR, ENETC_RBSR, ENETC_RBBSR, ENETC_RBCIR, ENETC_RBBAR0,
	ENETC_RBBAR1, ENETC_RBPIR, ENETC_RBLENR, ENETC_RBIER, ENETC_RBICR0,
	ENETC_RBICR1
पूर्ण;

अटल स्थिर u32 enetc_port_regs[] = अणु
	ENETC_PMR, ENETC_PSR, ENETC_PSIPMR, ENETC_PSIPMAR0(0),
	ENETC_PSIPMAR1(0), ENETC_PTXMBAR, ENETC_PCAPR0, ENETC_PCAPR1,
	ENETC_PSICFGR0(0), ENETC_PRFSCAPR, ENETC_PTCMSDUR(0),
	ENETC_PM0_CMD_CFG, ENETC_PM0_MAXFRM, ENETC_PM0_IF_MODE
पूर्ण;

अटल पूर्णांक enetc_get_reglen(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	पूर्णांक len;

	len = ARRAY_SIZE(enetc_si_regs);
	len += ARRAY_SIZE(enetc_txbdr_regs) * priv->num_tx_rings;
	len += ARRAY_SIZE(enetc_rxbdr_regs) * priv->num_rx_rings;

	अगर (hw->port)
		len += ARRAY_SIZE(enetc_port_regs);

	len *= माप(u32) * 2; /* store 2 entries per reg: addr and value */

	वापस len;
पूर्ण

अटल व्योम enetc_get_regs(काष्ठा net_device *ndev, काष्ठा ethtool_regs *regs,
			   व्योम *regbuf)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	u32 *buf = (u32 *)regbuf;
	पूर्णांक i, j;
	u32 addr;

	क्रम (i = 0; i < ARRAY_SIZE(enetc_si_regs); i++) अणु
		*buf++ = enetc_si_regs[i];
		*buf++ = enetc_rd(hw, enetc_si_regs[i]);
	पूर्ण

	क्रम (i = 0; i < priv->num_tx_rings; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(enetc_txbdr_regs); j++) अणु
			addr = ENETC_BDR(TX, i, enetc_txbdr_regs[j]);

			*buf++ = addr;
			*buf++ = enetc_rd(hw, addr);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_rings; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(enetc_rxbdr_regs); j++) अणु
			addr = ENETC_BDR(RX, i, enetc_rxbdr_regs[j]);

			*buf++ = addr;
			*buf++ = enetc_rd(hw, addr);
		पूर्ण
	पूर्ण

	अगर (!hw->port)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(enetc_port_regs); i++) अणु
		addr = ENETC_PORT_BASE + enetc_port_regs[i];
		*buf++ = addr;
		*buf++ = enetc_rd(hw, addr);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक reg;
	अक्षर name[ETH_GSTRING_LEN];
पूर्ण enetc_si_counters[] =  अणु
	अणु ENETC_SIROCT, "SI rx octets" पूर्ण,
	अणु ENETC_SIRFRM, "SI rx frames" पूर्ण,
	अणु ENETC_SIRUCA, "SI rx u-cast frames" पूर्ण,
	अणु ENETC_SIRMCA, "SI rx m-cast frames" पूर्ण,
	अणु ENETC_SITOCT, "SI tx octets" पूर्ण,
	अणु ENETC_SITFRM, "SI tx frames" पूर्ण,
	अणु ENETC_SITUCA, "SI tx u-cast frames" पूर्ण,
	अणु ENETC_SITMCA, "SI tx m-cast frames" पूर्ण,
	अणु ENETC_RBDCR(0), "Rx ring  0 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(1), "Rx ring  1 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(2), "Rx ring  2 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(3), "Rx ring  3 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(4), "Rx ring  4 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(5), "Rx ring  5 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(6), "Rx ring  6 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(7), "Rx ring  7 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(8), "Rx ring  8 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(9), "Rx ring  9 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(10), "Rx ring 10 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(11), "Rx ring 11 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(12), "Rx ring 12 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(13), "Rx ring 13 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(14), "Rx ring 14 discarded frames" पूर्ण,
	अणु ENETC_RBDCR(15), "Rx ring 15 discarded frames" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक reg;
	अक्षर name[ETH_GSTRING_LEN];
पूर्ण enetc_port_counters[] = अणु
	अणु ENETC_PM0_REOCT,  "MAC rx ethernet octets" पूर्ण,
	अणु ENETC_PM0_RALN,   "MAC rx alignment errors" पूर्ण,
	अणु ENETC_PM0_RXPF,   "MAC rx valid pause frames" पूर्ण,
	अणु ENETC_PM0_RFRM,   "MAC rx valid frames" पूर्ण,
	अणु ENETC_PM0_RFCS,   "MAC rx fcs errors" पूर्ण,
	अणु ENETC_PM0_RVLAN,  "MAC rx VLAN frames" पूर्ण,
	अणु ENETC_PM0_RERR,   "MAC rx frame errors" पूर्ण,
	अणु ENETC_PM0_RUCA,   "MAC rx unicast frames" पूर्ण,
	अणु ENETC_PM0_RMCA,   "MAC rx multicast frames" पूर्ण,
	अणु ENETC_PM0_RBCA,   "MAC rx broadcast frames" पूर्ण,
	अणु ENETC_PM0_RDRP,   "MAC rx dropped packets" पूर्ण,
	अणु ENETC_PM0_RPKT,   "MAC rx packets" पूर्ण,
	अणु ENETC_PM0_RUND,   "MAC rx undersized packets" पूर्ण,
	अणु ENETC_PM0_R64,    "MAC rx 64 byte packets" पूर्ण,
	अणु ENETC_PM0_R127,   "MAC rx 65-127 byte packets" पूर्ण,
	अणु ENETC_PM0_R255,   "MAC rx 128-255 byte packets" पूर्ण,
	अणु ENETC_PM0_R511,   "MAC rx 256-511 byte packets" पूर्ण,
	अणु ENETC_PM0_R1023,  "MAC rx 512-1023 byte packets" पूर्ण,
	अणु ENETC_PM0_R1522,  "MAC rx 1024-1522 byte packets" पूर्ण,
	अणु ENETC_PM0_R1523X, "MAC rx 1523 to max-octet packets" पूर्ण,
	अणु ENETC_PM0_ROVR,   "MAC rx oversized packets" पूर्ण,
	अणु ENETC_PM0_RJBR,   "MAC rx jabber packets" पूर्ण,
	अणु ENETC_PM0_RFRG,   "MAC rx fragment packets" पूर्ण,
	अणु ENETC_PM0_RCNP,   "MAC rx control packets" पूर्ण,
	अणु ENETC_PM0_RDRNTP, "MAC rx fifo drop" पूर्ण,
	अणु ENETC_PM0_TEOCT,  "MAC tx ethernet octets" पूर्ण,
	अणु ENETC_PM0_TOCT,   "MAC tx octets" पूर्ण,
	अणु ENETC_PM0_TCRSE,  "MAC tx carrier sense errors" पूर्ण,
	अणु ENETC_PM0_TXPF,   "MAC tx valid pause frames" पूर्ण,
	अणु ENETC_PM0_TFRM,   "MAC tx frames" पूर्ण,
	अणु ENETC_PM0_TFCS,   "MAC tx fcs errors" पूर्ण,
	अणु ENETC_PM0_TVLAN,  "MAC tx VLAN frames" पूर्ण,
	अणु ENETC_PM0_TERR,   "MAC tx frames" पूर्ण,
	अणु ENETC_PM0_TUCA,   "MAC tx unicast frames" पूर्ण,
	अणु ENETC_PM0_TMCA,   "MAC tx multicast frames" पूर्ण,
	अणु ENETC_PM0_TBCA,   "MAC tx broadcast frames" पूर्ण,
	अणु ENETC_PM0_TPKT,   "MAC tx packets" पूर्ण,
	अणु ENETC_PM0_TUND,   "MAC tx undersized packets" पूर्ण,
	अणु ENETC_PM0_T64,    "MAC tx 64 byte packets" पूर्ण,
	अणु ENETC_PM0_T127,   "MAC tx 65-127 byte packets" पूर्ण,
	अणु ENETC_PM0_T255,   "MAC tx 128-255 byte packets" पूर्ण,
	अणु ENETC_PM0_T511,   "MAC tx 256-511 byte packets" पूर्ण,
	अणु ENETC_PM0_T1023,  "MAC tx 512-1023 byte packets" पूर्ण,
	अणु ENETC_PM0_T1522,  "MAC tx 1024-1522 byte packets" पूर्ण,
	अणु ENETC_PM0_T1523X, "MAC tx 1523 to max-octet packets" पूर्ण,
	अणु ENETC_PM0_TCNP,   "MAC tx control packets" पूर्ण,
	अणु ENETC_PM0_TDFR,   "MAC tx deferred packets" पूर्ण,
	अणु ENETC_PM0_TMCOL,  "MAC tx multiple collisions" पूर्ण,
	अणु ENETC_PM0_TSCOL,  "MAC tx single collisions" पूर्ण,
	अणु ENETC_PM0_TLCOL,  "MAC tx late collisions" पूर्ण,
	अणु ENETC_PM0_TECOL,  "MAC tx excessive collisions" पूर्ण,
	अणु ENETC_UFDMF,      "SI MAC nomatch u-cast discards" पूर्ण,
	अणु ENETC_MFDMF,      "SI MAC nomatch m-cast discards" पूर्ण,
	अणु ENETC_PBFDSIR,    "SI MAC nomatch b-cast discards" पूर्ण,
	अणु ENETC_PUFDVFR,    "SI VLAN nomatch u-cast discards" पूर्ण,
	अणु ENETC_PMFDVFR,    "SI VLAN nomatch m-cast discards" पूर्ण,
	अणु ENETC_PBFDVFR,    "SI VLAN nomatch b-cast discards" पूर्ण,
	अणु ENETC_PFDMSAPR,   "SI pruning discarded frames" पूर्ण,
	अणु ENETC_PICDR(0),   "ICM DR0 discarded frames" पूर्ण,
	अणु ENETC_PICDR(1),   "ICM DR1 discarded frames" पूर्ण,
	अणु ENETC_PICDR(2),   "ICM DR2 discarded frames" पूर्ण,
	अणु ENETC_PICDR(3),   "ICM DR3 discarded frames" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर rx_ring_stats[][ETH_GSTRING_LEN] = अणु
	"Rx ring %2d frames",
	"Rx ring %2d alloc errors",
	"Rx ring %2d XDP drops",
	"Rx ring %2d recycles",
	"Rx ring %2d recycle failures",
	"Rx ring %2d redirects",
	"Rx ring %2d redirect failures",
	"Rx ring %2d redirect S/G",
पूर्ण;

अटल स्थिर अक्षर tx_ring_stats[][ETH_GSTRING_LEN] = अणु
	"Tx ring %2d frames",
	"Tx ring %2d XDP frames",
	"Tx ring %2d XDP drops",
पूर्ण;

अटल पूर्णांक enetc_get_sset_count(काष्ठा net_device *ndev, पूर्णांक sset)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक len;

	अगर (sset != ETH_SS_STATS)
		वापस -EOPNOTSUPP;

	len = ARRAY_SIZE(enetc_si_counters) +
	      ARRAY_SIZE(tx_ring_stats) * priv->num_tx_rings +
	      ARRAY_SIZE(rx_ring_stats) * priv->num_rx_rings;

	अगर (!enetc_si_is_pf(priv->si))
		वापस len;

	len += ARRAY_SIZE(enetc_port_counters);

	वापस len;
पूर्ण

अटल व्योम enetc_get_strings(काष्ठा net_device *ndev, u32 stringset, u8 *data)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	u8 *p = data;
	पूर्णांक i, j;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(enetc_si_counters); i++) अणु
			strlcpy(p, enetc_si_counters[i].name, ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < priv->num_tx_rings; i++) अणु
			क्रम (j = 0; j < ARRAY_SIZE(tx_ring_stats); j++) अणु
				snम_लिखो(p, ETH_GSTRING_LEN, tx_ring_stats[j],
					 i);
				p += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < priv->num_rx_rings; i++) अणु
			क्रम (j = 0; j < ARRAY_SIZE(rx_ring_stats); j++) अणु
				snम_लिखो(p, ETH_GSTRING_LEN, rx_ring_stats[j],
					 i);
				p += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		अगर (!enetc_si_is_pf(priv->si))
			अवरोध;

		क्रम (i = 0; i < ARRAY_SIZE(enetc_port_counters); i++) अणु
			strlcpy(p, enetc_port_counters[i].name,
				ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम enetc_get_ethtool_stats(काष्ठा net_device *ndev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	पूर्णांक i, o = 0;

	क्रम (i = 0; i < ARRAY_SIZE(enetc_si_counters); i++)
		data[o++] = enetc_rd64(hw, enetc_si_counters[i].reg);

	क्रम (i = 0; i < priv->num_tx_rings; i++) अणु
		data[o++] = priv->tx_ring[i]->stats.packets;
		data[o++] = priv->tx_ring[i]->stats.xdp_tx;
		data[o++] = priv->tx_ring[i]->stats.xdp_tx_drops;
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_rings; i++) अणु
		data[o++] = priv->rx_ring[i]->stats.packets;
		data[o++] = priv->rx_ring[i]->stats.rx_alloc_errs;
		data[o++] = priv->rx_ring[i]->stats.xdp_drops;
		data[o++] = priv->rx_ring[i]->stats.recycles;
		data[o++] = priv->rx_ring[i]->stats.recycle_failures;
		data[o++] = priv->rx_ring[i]->stats.xdp_redirect;
		data[o++] = priv->rx_ring[i]->stats.xdp_redirect_failures;
		data[o++] = priv->rx_ring[i]->stats.xdp_redirect_sg;
	पूर्ण

	अगर (!enetc_si_is_pf(priv->si))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(enetc_port_counters); i++)
		data[o++] = enetc_port_rd(hw, enetc_port_counters[i].reg);
पूर्ण

#घोषणा ENETC_RSSHASH_L3 (RXH_L2DA | RXH_VLAN | RXH_L3_PROTO | RXH_IP_SRC | \
			  RXH_IP_DST)
#घोषणा ENETC_RSSHASH_L4 (ENETC_RSSHASH_L3 | RXH_L4_B_0_1 | RXH_L4_B_2_3)
अटल पूर्णांक enetc_get_rsshash(काष्ठा ethtool_rxnfc *rxnfc)
अणु
	अटल स्थिर u32 rsshash[] = अणु
			[TCP_V4_FLOW]    = ENETC_RSSHASH_L4,
			[UDP_V4_FLOW]    = ENETC_RSSHASH_L4,
			[SCTP_V4_FLOW]   = ENETC_RSSHASH_L4,
			[AH_ESP_V4_FLOW] = ENETC_RSSHASH_L3,
			[IPV4_FLOW]      = ENETC_RSSHASH_L3,
			[TCP_V6_FLOW]    = ENETC_RSSHASH_L4,
			[UDP_V6_FLOW]    = ENETC_RSSHASH_L4,
			[SCTP_V6_FLOW]   = ENETC_RSSHASH_L4,
			[AH_ESP_V6_FLOW] = ENETC_RSSHASH_L3,
			[IPV6_FLOW]      = ENETC_RSSHASH_L3,
			[ETHER_FLOW]     = 0,
	पूर्ण;

	अगर (rxnfc->flow_type >= ARRAY_SIZE(rsshash))
		वापस -EINVAL;

	rxnfc->data = rsshash[rxnfc->flow_type];

	वापस 0;
पूर्ण

/* current HW spec करोes byte reversal on everything including MAC addresses */
अटल व्योम ether_addr_copy_swap(u8 *dst, स्थिर u8 *src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		dst[i] = src[ETH_ALEN - i - 1];
पूर्ण

अटल पूर्णांक enetc_set_cls_entry(काष्ठा enetc_si *si,
			       काष्ठा ethtool_rx_flow_spec *fs, bool en)
अणु
	काष्ठा ethtool_tcpip4_spec *l4ip4_h, *l4ip4_m;
	काष्ठा ethtool_usrip4_spec *l3ip4_h, *l3ip4_m;
	काष्ठा ethhdr *eth_h, *eth_m;
	काष्ठा enetc_cmd_rfse rfse = अणु अणु0पूर्ण पूर्ण;

	अगर (!en)
		जाओ करोne;

	चयन (fs->flow_type & 0xff) अणु
	हाल TCP_V4_FLOW:
		l4ip4_h = &fs->h_u.tcp_ip4_spec;
		l4ip4_m = &fs->m_u.tcp_ip4_spec;
		जाओ l4ip4;
	हाल UDP_V4_FLOW:
		l4ip4_h = &fs->h_u.udp_ip4_spec;
		l4ip4_m = &fs->m_u.udp_ip4_spec;
		जाओ l4ip4;
	हाल SCTP_V4_FLOW:
		l4ip4_h = &fs->h_u.sctp_ip4_spec;
		l4ip4_m = &fs->m_u.sctp_ip4_spec;
l4ip4:
		rfse.sip_h[0] = l4ip4_h->ip4src;
		rfse.sip_m[0] = l4ip4_m->ip4src;
		rfse.dip_h[0] = l4ip4_h->ip4dst;
		rfse.dip_m[0] = l4ip4_m->ip4dst;
		rfse.sport_h = ntohs(l4ip4_h->psrc);
		rfse.sport_m = ntohs(l4ip4_m->psrc);
		rfse.dport_h = ntohs(l4ip4_h->pdst);
		rfse.dport_m = ntohs(l4ip4_m->pdst);
		अगर (l4ip4_m->tos)
			netdev_warn(si->ndev, "ToS field is not supported and was ignored\n");
		rfse.ethtype_h = ETH_P_IP; /* IPv4 */
		rfse.ethtype_m = 0xffff;
		अवरोध;
	हाल IP_USER_FLOW:
		l3ip4_h = &fs->h_u.usr_ip4_spec;
		l3ip4_m = &fs->m_u.usr_ip4_spec;

		rfse.sip_h[0] = l3ip4_h->ip4src;
		rfse.sip_m[0] = l3ip4_m->ip4src;
		rfse.dip_h[0] = l3ip4_h->ip4dst;
		rfse.dip_m[0] = l3ip4_m->ip4dst;
		अगर (l3ip4_m->tos)
			netdev_warn(si->ndev, "ToS field is not supported and was ignored\n");
		rfse.ethtype_h = ETH_P_IP; /* IPv4 */
		rfse.ethtype_m = 0xffff;
		अवरोध;
	हाल ETHER_FLOW:
		eth_h = &fs->h_u.ether_spec;
		eth_m = &fs->m_u.ether_spec;

		ether_addr_copy_swap(rfse.smac_h, eth_h->h_source);
		ether_addr_copy_swap(rfse.smac_m, eth_m->h_source);
		ether_addr_copy_swap(rfse.dmac_h, eth_h->h_dest);
		ether_addr_copy_swap(rfse.dmac_m, eth_m->h_dest);
		rfse.ethtype_h = ntohs(eth_h->h_proto);
		rfse.ethtype_m = ntohs(eth_m->h_proto);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	rfse.mode |= ENETC_RFSE_EN;
	अगर (fs->ring_cookie != RX_CLS_FLOW_DISC) अणु
		rfse.mode |= ENETC_RFSE_MODE_BD;
		rfse.result = fs->ring_cookie;
	पूर्ण
करोne:
	वापस enetc_set_fs_entry(si, &rfse, fs->location);
पूर्ण

अटल पूर्णांक enetc_get_rxnfc(काष्ठा net_device *ndev, काष्ठा ethtool_rxnfc *rxnfc,
			   u32 *rule_locs)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक i, j;

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		rxnfc->data = priv->num_rx_rings;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		/* get RSS hash config */
		वापस enetc_get_rsshash(rxnfc);
	हाल ETHTOOL_GRXCLSRLCNT:
		/* total number of entries */
		rxnfc->data = priv->si->num_fs_entries;
		/* number of entries in use */
		rxnfc->rule_cnt = 0;
		क्रम (i = 0; i < priv->si->num_fs_entries; i++)
			अगर (priv->cls_rules[i].used)
				rxnfc->rule_cnt++;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		अगर (rxnfc->fs.location >= priv->si->num_fs_entries)
			वापस -EINVAL;

		/* get entry x */
		rxnfc->fs = priv->cls_rules[rxnfc->fs.location].fs;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		/* total number of entries */
		rxnfc->data = priv->si->num_fs_entries;
		/* array of indexes of used entries */
		j = 0;
		क्रम (i = 0; i < priv->si->num_fs_entries; i++) अणु
			अगर (!priv->cls_rules[i].used)
				जारी;
			अगर (j == rxnfc->rule_cnt)
				वापस -EMSGSIZE;
			rule_locs[j++] = i;
		पूर्ण
		/* number of entries in use */
		rxnfc->rule_cnt = j;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_set_rxnfc(काष्ठा net_device *ndev, काष्ठा ethtool_rxnfc *rxnfc)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		अगर (rxnfc->fs.location >= priv->si->num_fs_entries)
			वापस -EINVAL;

		अगर (rxnfc->fs.ring_cookie >= priv->num_rx_rings &&
		    rxnfc->fs.ring_cookie != RX_CLS_FLOW_DISC)
			वापस -EINVAL;

		err = enetc_set_cls_entry(priv->si, &rxnfc->fs, true);
		अगर (err)
			वापस err;
		priv->cls_rules[rxnfc->fs.location].fs = rxnfc->fs;
		priv->cls_rules[rxnfc->fs.location].used = 1;
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		अगर (rxnfc->fs.location >= priv->si->num_fs_entries)
			वापस -EINVAL;

		err = enetc_set_cls_entry(priv->si, &rxnfc->fs, false);
		अगर (err)
			वापस err;
		priv->cls_rules[rxnfc->fs.location].used = 0;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 enetc_get_rxfh_key_size(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	/* वापस the size of the RX flow hash key.  PF only */
	वापस (priv->si->hw.port) ? ENETC_RSSHASH_KEY_SIZE : 0;
पूर्ण

अटल u32 enetc_get_rxfh_indir_size(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	/* वापस the size of the RX flow hash indirection table */
	वापस priv->si->num_rss;
पूर्ण

अटल पूर्णांक enetc_get_rxfh(काष्ठा net_device *ndev, u32 *indir, u8 *key,
			  u8 *hfunc)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	पूर्णांक err = 0, i;

	/* वापस hash function */
	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	/* वापस hash key */
	अगर (key && hw->port)
		क्रम (i = 0; i < ENETC_RSSHASH_KEY_SIZE / 4; i++)
			((u32 *)key)[i] = enetc_port_rd(hw, ENETC_PRSSK(i));

	/* वापस RSS table */
	अगर (indir)
		err = enetc_get_rss_table(priv->si, indir, priv->si->num_rss);

	वापस err;
पूर्ण

व्योम enetc_set_rss_key(काष्ठा enetc_hw *hw, स्थिर u8 *bytes)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ENETC_RSSHASH_KEY_SIZE / 4; i++)
		enetc_port_wr(hw, ENETC_PRSSK(i), ((u32 *)bytes)[i]);
पूर्ण

अटल पूर्णांक enetc_set_rxfh(काष्ठा net_device *ndev, स्थिर u32 *indir,
			  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	पूर्णांक err = 0;

	/* set hash key, अगर PF */
	अगर (key && hw->port)
		enetc_set_rss_key(hw, key);

	/* set RSS table */
	अगर (indir)
		err = enetc_set_rss_table(priv->si, indir, priv->si->num_rss);

	वापस err;
पूर्ण

अटल व्योम enetc_get_ringparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	ring->rx_pending = priv->rx_bd_count;
	ring->tx_pending = priv->tx_bd_count;

	/* करो some h/w sanity checks क्रम BDR length */
	अगर (netअगर_running(ndev)) अणु
		काष्ठा enetc_hw *hw = &priv->si->hw;
		u32 val = enetc_rxbdr_rd(hw, 0, ENETC_RBLENR);

		अगर (val != priv->rx_bd_count)
			netअगर_err(priv, hw, ndev, "RxBDR[RBLENR] = %d!\n", val);

		val = enetc_txbdr_rd(hw, 0, ENETC_TBLENR);

		अगर (val != priv->tx_bd_count)
			netअगर_err(priv, hw, ndev, "TxBDR[TBLENR] = %d!\n", val);
	पूर्ण
पूर्ण

अटल पूर्णांक enetc_get_coalesce(काष्ठा net_device *ndev,
			      काष्ठा ethtool_coalesce *ic)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_पूर्णांक_vector *v = priv->पूर्णांक_vector[0];

	ic->tx_coalesce_usecs = enetc_cycles_to_usecs(priv->tx_ictt);
	ic->rx_coalesce_usecs = enetc_cycles_to_usecs(v->rx_ictt);

	ic->tx_max_coalesced_frames = ENETC_TXIC_PKTTHR;
	ic->rx_max_coalesced_frames = ENETC_RXIC_PKTTHR;

	ic->use_adaptive_rx_coalesce = priv->ic_mode & ENETC_IC_RX_ADAPTIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_set_coalesce(काष्ठा net_device *ndev,
			      काष्ठा ethtool_coalesce *ic)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	u32 rx_ictt, tx_ictt;
	पूर्णांक i, ic_mode;
	bool changed;

	tx_ictt = enetc_usecs_to_cycles(ic->tx_coalesce_usecs);
	rx_ictt = enetc_usecs_to_cycles(ic->rx_coalesce_usecs);

	अगर (ic->rx_max_coalesced_frames != ENETC_RXIC_PKTTHR)
		वापस -EOPNOTSUPP;

	अगर (ic->tx_max_coalesced_frames != ENETC_TXIC_PKTTHR)
		वापस -EOPNOTSUPP;

	ic_mode = ENETC_IC_NONE;
	अगर (ic->use_adaptive_rx_coalesce) अणु
		ic_mode |= ENETC_IC_RX_ADAPTIVE;
		rx_ictt = 0x1;
	पूर्ण अन्यथा अणु
		ic_mode |= rx_ictt ? ENETC_IC_RX_MANUAL : 0;
	पूर्ण

	ic_mode |= tx_ictt ? ENETC_IC_TX_MANUAL : 0;

	/* commit the settings */
	changed = (ic_mode != priv->ic_mode) || (priv->tx_ictt != tx_ictt);

	priv->ic_mode = ic_mode;
	priv->tx_ictt = tx_ictt;

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		काष्ठा enetc_पूर्णांक_vector *v = priv->पूर्णांक_vector[i];

		v->rx_ictt = rx_ictt;
		v->rx_dim_en = !!(ic_mode & ENETC_IC_RX_ADAPTIVE);
	पूर्ण

	अगर (netअगर_running(ndev) && changed) अणु
		/* reconfigure the operation mode of h/w पूर्णांकerrupts,
		 * traffic needs to be छोड़ोd in the process
		 */
		enetc_stop(ndev);
		enetc_start(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_get_ts_info(काष्ठा net_device *ndev,
			     काष्ठा ethtool_ts_info *info)
अणु
	पूर्णांक *phc_idx;

	phc_idx = symbol_get(enetc_phc_index);
	अगर (phc_idx) अणु
		info->phc_index = *phc_idx;
		symbol_put(enetc_phc_index);
	पूर्ण अन्यथा अणु
		info->phc_index = -1;
	पूर्ण

#अगर_घोषित CONFIG_FSL_ENETC_PTP_CLOCK
	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON) |
			 (1 << HWTSTAMP_TX_ONESTEP_SYNC);
	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);
#अन्यथा
	info->so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम enetc_get_wol(काष्ठा net_device *dev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts = 0;

	अगर (dev->phydev)
		phy_ethtool_get_wol(dev->phydev, wol);
पूर्ण

अटल पूर्णांक enetc_set_wol(काष्ठा net_device *dev,
			 काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक ret;

	अगर (!dev->phydev)
		वापस -EOPNOTSUPP;

	ret = phy_ethtool_set_wol(dev->phydev, wol);
	अगर (!ret)
		device_set_wakeup_enable(&dev->dev, wol->wolopts);

	वापस ret;
पूर्ण

अटल व्योम enetc_get_छोड़ोparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(dev);

	phylink_ethtool_get_छोड़ोparam(priv->phylink, छोड़ो);
पूर्ण

अटल पूर्णांक enetc_set_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(dev);

	वापस phylink_ethtool_set_छोड़ोparam(priv->phylink, छोड़ो);
पूर्ण

अटल पूर्णांक enetc_get_link_ksettings(काष्ठा net_device *dev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(dev);

	अगर (!priv->phylink)
		वापस -EOPNOTSUPP;

	वापस phylink_ethtool_ksettings_get(priv->phylink, cmd);
पूर्ण

अटल पूर्णांक enetc_set_link_ksettings(काष्ठा net_device *dev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(dev);

	अगर (!priv->phylink)
		वापस -EOPNOTSUPP;

	वापस phylink_ethtool_ksettings_set(priv->phylink, cmd);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops enetc_pf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_regs_len = enetc_get_reglen,
	.get_regs = enetc_get_regs,
	.get_sset_count = enetc_get_sset_count,
	.get_strings = enetc_get_strings,
	.get_ethtool_stats = enetc_get_ethtool_stats,
	.get_rxnfc = enetc_get_rxnfc,
	.set_rxnfc = enetc_set_rxnfc,
	.get_rxfh_key_size = enetc_get_rxfh_key_size,
	.get_rxfh_indir_size = enetc_get_rxfh_indir_size,
	.get_rxfh = enetc_get_rxfh,
	.set_rxfh = enetc_set_rxfh,
	.get_ringparam = enetc_get_ringparam,
	.get_coalesce = enetc_get_coalesce,
	.set_coalesce = enetc_set_coalesce,
	.get_link_ksettings = enetc_get_link_ksettings,
	.set_link_ksettings = enetc_set_link_ksettings,
	.get_link = ethtool_op_get_link,
	.get_ts_info = enetc_get_ts_info,
	.get_wol = enetc_get_wol,
	.set_wol = enetc_set_wol,
	.get_छोड़ोparam = enetc_get_छोड़ोparam,
	.set_छोड़ोparam = enetc_set_छोड़ोparam,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops enetc_vf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_regs_len = enetc_get_reglen,
	.get_regs = enetc_get_regs,
	.get_sset_count = enetc_get_sset_count,
	.get_strings = enetc_get_strings,
	.get_ethtool_stats = enetc_get_ethtool_stats,
	.get_rxnfc = enetc_get_rxnfc,
	.set_rxnfc = enetc_set_rxnfc,
	.get_rxfh_indir_size = enetc_get_rxfh_indir_size,
	.get_rxfh = enetc_get_rxfh,
	.set_rxfh = enetc_set_rxfh,
	.get_ringparam = enetc_get_ringparam,
	.get_coalesce = enetc_get_coalesce,
	.set_coalesce = enetc_set_coalesce,
	.get_link = ethtool_op_get_link,
	.get_ts_info = enetc_get_ts_info,
पूर्ण;

व्योम enetc_set_ethtool_ops(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	अगर (enetc_si_is_pf(priv->si))
		ndev->ethtool_ops = &enetc_pf_ethtool_ops;
	अन्यथा
		ndev->ethtool_ops = &enetc_vf_ethtool_ops;
पूर्ण
