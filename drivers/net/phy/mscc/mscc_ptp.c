<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Driver क्रम Microsemi VSC85xx PHYs - बारtamping and PHC support
 *
 * Authors: Quentin Schulz & Antoine Tenart
 * License: Dual MIT/GPL
 * Copyright (c) 2020 Microsemi Corporation
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/ip.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/udp.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "mscc.h"
#समावेश "mscc_ptp.h"

/* Two PHYs share the same 1588 processor and it's to be entirely configured
 * through the base PHY of this processor.
 */
/* phydev->bus->mdio_lock should be locked when using this function */
अटल पूर्णांक phy_ts_base_ग_लिखो(काष्ठा phy_device *phydev, u32 regnum, u16 val)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	WARN_ON_ONCE(!mutex_is_locked(&phydev->mdio.bus->mdio_lock));
	वापस __mdiobus_ग_लिखो(phydev->mdio.bus, priv->ts_base_addr, regnum,
			       val);
पूर्ण

/* phydev->bus->mdio_lock should be locked when using this function */
अटल पूर्णांक phy_ts_base_पढ़ो(काष्ठा phy_device *phydev, u32 regnum)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	WARN_ON_ONCE(!mutex_is_locked(&phydev->mdio.bus->mdio_lock));
	वापस __mdiobus_पढ़ो(phydev->mdio.bus, priv->ts_base_addr, regnum);
पूर्ण

क्रमागत ts_blk_hw अणु
	INGRESS_ENGINE_0,
	EGRESS_ENGINE_0,
	INGRESS_ENGINE_1,
	EGRESS_ENGINE_1,
	INGRESS_ENGINE_2,
	EGRESS_ENGINE_2,
	PROCESSOR_0,
	PROCESSOR_1,
पूर्ण;

क्रमागत ts_blk अणु
	INGRESS,
	EGRESS,
	PROCESSOR,
पूर्ण;

अटल u32 vsc85xx_ts_पढ़ो_csr(काष्ठा phy_device *phydev, क्रमागत ts_blk blk,
			       u16 addr)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	bool base_port = phydev->mdio.addr == priv->ts_base_addr;
	u32 val, cnt = 0;
	क्रमागत ts_blk_hw blk_hw;

	चयन (blk) अणु
	हाल INGRESS:
		blk_hw = base_port ? INGRESS_ENGINE_0 : INGRESS_ENGINE_1;
		अवरोध;
	हाल EGRESS:
		blk_hw = base_port ? EGRESS_ENGINE_0 : EGRESS_ENGINE_1;
		अवरोध;
	हाल PROCESSOR:
	शेष:
		blk_hw = base_port ? PROCESSOR_0 : PROCESSOR_1;
		अवरोध;
	पूर्ण

	phy_lock_mdio_bus(phydev);

	phy_ts_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_1588);

	phy_ts_base_ग_लिखो(phydev, MSCC_PHY_TS_BIU_ADDR_CNTL, BIU_ADDR_EXE |
			  BIU_ADDR_READ | BIU_BLK_ID(blk_hw) |
			  BIU_CSR_ADDR(addr));

	करो अणु
		val = phy_ts_base_पढ़ो(phydev, MSCC_PHY_TS_BIU_ADDR_CNTL);
	पूर्ण जबतक (!(val & BIU_ADDR_EXE) && cnt++ < BIU_ADDR_CNT_MAX);

	val = phy_ts_base_पढ़ो(phydev, MSCC_PHY_TS_CSR_DATA_MSB);
	val <<= 16;
	val |= phy_ts_base_पढ़ो(phydev, MSCC_PHY_TS_CSR_DATA_LSB);

	phy_ts_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	phy_unlock_mdio_bus(phydev);

	वापस val;
पूर्ण

अटल व्योम vsc85xx_ts_ग_लिखो_csr(काष्ठा phy_device *phydev, क्रमागत ts_blk blk,
				 u16 addr, u32 val)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	bool base_port = phydev->mdio.addr == priv->ts_base_addr;
	u32 reg, bypass, cnt = 0, lower = val & 0xffff, upper = val >> 16;
	bool cond = (addr == MSCC_PHY_PTP_LTC_CTRL ||
		     addr == MSCC_PHY_1588_INGR_VSC85XX_INT_MASK ||
		     addr == MSCC_PHY_1588_VSC85XX_INT_MASK ||
		     addr == MSCC_PHY_1588_INGR_VSC85XX_INT_STATUS ||
		     addr == MSCC_PHY_1588_VSC85XX_INT_STATUS) &&
		    blk == PROCESSOR;
	क्रमागत ts_blk_hw blk_hw;

	चयन (blk) अणु
	हाल INGRESS:
		blk_hw = base_port ? INGRESS_ENGINE_0 : INGRESS_ENGINE_1;
		अवरोध;
	हाल EGRESS:
		blk_hw = base_port ? EGRESS_ENGINE_0 : EGRESS_ENGINE_1;
		अवरोध;
	हाल PROCESSOR:
	शेष:
		blk_hw = base_port ? PROCESSOR_0 : PROCESSOR_1;
		अवरोध;
	पूर्ण

	phy_lock_mdio_bus(phydev);

	bypass = phy_ts_base_पढ़ो(phydev, MSCC_PHY_BYPASS_CONTROL);

	phy_ts_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_1588);

	अगर (!cond || upper)
		phy_ts_base_ग_लिखो(phydev, MSCC_PHY_TS_CSR_DATA_MSB, upper);

	phy_ts_base_ग_लिखो(phydev, MSCC_PHY_TS_CSR_DATA_LSB, lower);

	phy_ts_base_ग_लिखो(phydev, MSCC_PHY_TS_BIU_ADDR_CNTL, BIU_ADDR_EXE |
			  BIU_ADDR_WRITE | BIU_BLK_ID(blk_hw) |
			  BIU_CSR_ADDR(addr));

	करो अणु
		reg = phy_ts_base_पढ़ो(phydev, MSCC_PHY_TS_BIU_ADDR_CNTL);
	पूर्ण जबतक (!(reg & BIU_ADDR_EXE) && cnt++ < BIU_ADDR_CNT_MAX);

	phy_ts_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	अगर (cond && upper)
		phy_ts_base_ग_लिखो(phydev, MSCC_PHY_BYPASS_CONTROL, bypass);

	phy_unlock_mdio_bus(phydev);
पूर्ण

/* Pick bytes from PTP header */
#घोषणा PTP_HEADER_TRNSP_MSG		26
#घोषणा PTP_HEADER_DOMAIN_NUM		25
#घोषणा PTP_HEADER_BYTE_8_31(x)		(31 - (x))
#घोषणा MAC_ADDRESS_BYTE(x)		((x) + (35 - ETH_ALEN + 1))

अटल पूर्णांक vsc85xx_ts_fsb_init(काष्ठा phy_device *phydev)
अणु
	u8 sig_sel[16] = अणुपूर्ण;
	चिन्हित अक्षर i, pos = 0;

	/* Seq ID is 2B दीर्घ and starts at 30th byte */
	क्रम (i = 1; i >= 0; i--)
		sig_sel[pos++] = PTP_HEADER_BYTE_8_31(30 + i);

	/* Doमुख्यNum */
	sig_sel[pos++] = PTP_HEADER_DOMAIN_NUM;

	/* MsgType */
	sig_sel[pos++] = PTP_HEADER_TRNSP_MSG;

	/* MAC address is 6B दीर्घ */
	क्रम (i = ETH_ALEN - 1; i >= 0; i--)
		sig_sel[pos++] = MAC_ADDRESS_BYTE(i);

	/* Fill the last bytes of the signature to reach a 16B signature */
	क्रम (; pos < ARRAY_SIZE(sig_sel); pos++)
		sig_sel[pos] = PTP_HEADER_TRNSP_MSG;

	क्रम (i = 0; i <= 2; i++) अणु
		u32 val = 0;

		क्रम (pos = i * 5 + 4; pos >= i * 5; pos--)
			val = (val << 6) | sig_sel[pos];

		vsc85xx_ts_ग_लिखो_csr(phydev, EGRESS, MSCC_PHY_ANA_FSB_REG(i),
				     val);
	पूर्ण

	vsc85xx_ts_ग_लिखो_csr(phydev, EGRESS, MSCC_PHY_ANA_FSB_REG(3),
			     sig_sel[15]);

	वापस 0;
पूर्ण

अटल स्थिर u32 vsc85xx_egr_latency[] = अणु
	/* Copper Egress */
	1272, /* 1000Mbps */
	12516, /* 100Mbps */
	125444, /* 10Mbps */
	/* Fiber Egress */
	1277, /* 1000Mbps */
	12537, /* 100Mbps */
पूर्ण;

अटल स्थिर u32 vsc85xx_egr_latency_macsec[] = अणु
	/* Copper Egress ON */
	3496, /* 1000Mbps */
	34760, /* 100Mbps */
	347844, /* 10Mbps */
	/* Fiber Egress ON */
	3502, /* 1000Mbps */
	34780, /* 100Mbps */
पूर्ण;

अटल स्थिर u32 vsc85xx_ingr_latency[] = अणु
	/* Copper Ingress */
	208, /* 1000Mbps */
	304, /* 100Mbps */
	2023, /* 10Mbps */
	/* Fiber Ingress */
	98, /* 1000Mbps */
	197, /* 100Mbps */
पूर्ण;

अटल स्थिर u32 vsc85xx_ingr_latency_macsec[] = अणु
	/* Copper Ingress */
	2408, /* 1000Mbps */
	22300, /* 100Mbps */
	222009, /* 10Mbps */
	/* Fiber Ingress */
	2299, /* 1000Mbps */
	22192, /* 100Mbps */
पूर्ण;

अटल व्योम vsc85xx_ts_set_latencies(काष्ठा phy_device *phydev)
अणु
	u32 val, ingr_latency, egr_latency;
	u8 idx;

	/* No need to set latencies of packets अगर the PHY is not connected */
	अगर (!phydev->link)
		वापस;

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_STALL_LATENCY,
			     STALL_EGR_LATENCY(phydev->speed));

	चयन (phydev->speed) अणु
	हाल SPEED_100:
		idx = 1;
		अवरोध;
	हाल SPEED_1000:
		idx = 0;
		अवरोध;
	शेष:
		idx = 2;
		अवरोध;
	पूर्ण

	ingr_latency = IS_ENABLED(CONFIG_MACSEC) ?
		vsc85xx_ingr_latency_macsec[idx] : vsc85xx_ingr_latency[idx];
	egr_latency = IS_ENABLED(CONFIG_MACSEC) ?
		vsc85xx_egr_latency_macsec[idx] : vsc85xx_egr_latency[idx];

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_LOCAL_LATENCY,
			     PTP_INGR_LOCAL_LATENCY(ingr_latency));

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_INGR_TSP_CTRL);
	val |= PHY_PTP_INGR_TSP_CTRL_LOAD_DELAYS;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_TSP_CTRL,
			     val);

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_LOCAL_LATENCY,
			     PTP_EGR_LOCAL_LATENCY(egr_latency));

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_TSP_CTRL);
	val |= PHY_PTP_EGR_TSP_CTRL_LOAD_DELAYS;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_TSP_CTRL, val);
पूर्ण

अटल पूर्णांक vsc85xx_ts_disable_flows(काष्ठा phy_device *phydev, क्रमागत ts_blk blk)
अणु
	u8 i;

	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_NXT_COMP, 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_UDP_CHKSUM,
			     IP1_NXT_PROT_UDP_CHKSUM_WIDTH(2));
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP2_NXT_PROT_NXT_COMP, 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP2_NXT_PROT_UDP_CHKSUM,
			     IP2_NXT_PROT_UDP_CHKSUM_WIDTH(2));
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_PHY_ANA_MPLS_COMP_NXT_COMP, 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_PHY_ANA_ETH1_NTX_PROT, 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_PHY_ANA_ETH2_NTX_PROT, 0);

	क्रम (i = 0; i < COMP_MAX_FLOWS; i++) अणु
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_ENA(i),
				     IP1_FLOW_VALID_CH0 | IP1_FLOW_VALID_CH1);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP2_FLOW_ENA(i),
				     IP2_FLOW_VALID_CH0 | IP2_FLOW_VALID_CH1);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_ENA(i),
				     ETH1_FLOW_VALID_CH0 | ETH1_FLOW_VALID_CH1);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH2_FLOW_ENA(i),
				     ETH2_FLOW_VALID_CH0 | ETH2_FLOW_VALID_CH1);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_MPLS_FLOW_CTRL(i),
				     MPLS_FLOW_VALID_CH0 | MPLS_FLOW_VALID_CH1);

		अगर (i >= PTP_COMP_MAX_FLOWS)
			जारी;

		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_PTP_FLOW_ENA(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_DOMAIN_RANGE(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_MASK_UPPER(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_MASK_LOWER(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_MATCH_UPPER(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_MATCH_LOWER(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_PTP_ACTION(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_PTP_ACTION2(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_PTP_0_FIELD(i), 0);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_OAM_PTP_FLOW_ENA(i),
				     0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_ts_eth_cmp1_sig(काष्ठा phy_device *phydev)
अणु
	u32 val;

	val = vsc85xx_ts_पढ़ो_csr(phydev, EGRESS, MSCC_PHY_ANA_ETH1_NTX_PROT);
	val &= ~ANA_ETH1_NTX_PROT_SIG_OFF_MASK;
	val |= ANA_ETH1_NTX_PROT_SIG_OFF(0);
	vsc85xx_ts_ग_लिखो_csr(phydev, EGRESS, MSCC_PHY_ANA_ETH1_NTX_PROT, val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, EGRESS, MSCC_PHY_ANA_FSB_CFG);
	val &= ~ANA_FSB_ADDR_FROM_BLOCK_SEL_MASK;
	val |= ANA_FSB_ADDR_FROM_ETH1;
	vsc85xx_ts_ग_लिखो_csr(phydev, EGRESS, MSCC_PHY_ANA_FSB_CFG, val);

	वापस 0;
पूर्ण

अटल काष्ठा vsc85xx_ptphdr *get_ptp_header_l4(काष्ठा sk_buff *skb,
						काष्ठा iphdr *iphdr,
						काष्ठा udphdr *udphdr)
अणु
	अगर (iphdr->version != 4 || iphdr->protocol != IPPROTO_UDP)
		वापस शून्य;

	वापस (काष्ठा vsc85xx_ptphdr *)(((अचिन्हित अक्षर *)udphdr) + UDP_HLEN);
पूर्ण

अटल काष्ठा vsc85xx_ptphdr *get_ptp_header_tx(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);
	काष्ठा udphdr *udphdr;
	काष्ठा iphdr *iphdr;

	अगर (ethhdr->h_proto == htons(ETH_P_1588))
		वापस (काष्ठा vsc85xx_ptphdr *)(((अचिन्हित अक्षर *)ethhdr) +
						 skb_mac_header_len(skb));

	अगर (ethhdr->h_proto != htons(ETH_P_IP))
		वापस शून्य;

	iphdr = ip_hdr(skb);
	udphdr = udp_hdr(skb);

	वापस get_ptp_header_l4(skb, iphdr, udphdr);
पूर्ण

अटल काष्ठा vsc85xx_ptphdr *get_ptp_header_rx(काष्ठा sk_buff *skb,
						क्रमागत hwtstamp_rx_filters rx_filter)
अणु
	काष्ठा udphdr *udphdr;
	काष्ठा iphdr *iphdr;

	अगर (rx_filter == HWTSTAMP_FILTER_PTP_V2_L2_EVENT)
		वापस (काष्ठा vsc85xx_ptphdr *)skb->data;

	iphdr = (काष्ठा iphdr *)skb->data;
	udphdr = (काष्ठा udphdr *)(skb->data + iphdr->ihl * 4);

	वापस get_ptp_header_l4(skb, iphdr, udphdr);
पूर्ण

अटल पूर्णांक get_sig(काष्ठा sk_buff *skb, u8 *sig)
अणु
	काष्ठा vsc85xx_ptphdr *ptphdr = get_ptp_header_tx(skb);
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);
	अचिन्हित पूर्णांक i;

	अगर (!ptphdr)
		वापस -EOPNOTSUPP;

	sig[0] = (__क्रमce u16)ptphdr->seq_id >> 8;
	sig[1] = (__क्रमce u16)ptphdr->seq_id & GENMASK(7, 0);
	sig[2] = ptphdr->करोमुख्य;
	sig[3] = ptphdr->tsmt & GENMASK(3, 0);

	स_नकल(&sig[4], ethhdr->h_dest, ETH_ALEN);

	/* Fill the last bytes of the signature to reach a 16B signature */
	क्रम (i = 10; i < 16; i++)
		sig[i] = ptphdr->tsmt & GENMASK(3, 0);

	वापस 0;
पूर्ण

अटल व्योम vsc85xx_dequeue_skb(काष्ठा vsc85xx_ptp *ptp)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा vsc85xx_ts_fअगरo fअगरo;
	काष्ठा sk_buff *skb;
	u8 skb_sig[16], *p;
	पूर्णांक i, len;
	u32 reg;

	स_रखो(&fअगरo, 0, माप(fअगरo));
	p = (u8 *)&fअगरo;

	reg = vsc85xx_ts_पढ़ो_csr(ptp->phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_TS_FIFO(0));
	अगर (reg & PTP_EGR_TS_FIFO_EMPTY)
		वापस;

	*p++ = reg & 0xff;
	*p++ = (reg >> 8) & 0xff;

	/* Read the current FIFO item. Reading FIFO6 pops the next one. */
	क्रम (i = 1; i < 7; i++) अणु
		reg = vsc85xx_ts_पढ़ो_csr(ptp->phydev, PROCESSOR,
					  MSCC_PHY_PTP_EGR_TS_FIFO(i));
		*p++ = reg & 0xff;
		*p++ = (reg >> 8) & 0xff;
		*p++ = (reg >> 16) & 0xff;
		*p++ = (reg >> 24) & 0xff;
	पूर्ण

	len = skb_queue_len(&ptp->tx_queue);
	अगर (len < 1)
		वापस;

	जबतक (len--) अणु
		skb = __skb_dequeue(&ptp->tx_queue);
		अगर (!skb)
			वापस;

		/* Can't get the signature of the packet, won't ever
		 * be able to have one so let's dequeue the packet.
		 */
		अगर (get_sig(skb, skb_sig) < 0) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		/* Check अगर we found the signature we were looking क्रम. */
		अगर (!स_भेद(skb_sig, fअगरo.sig, माप(fअगरo.sig))) अणु
			स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
			shhwtstamps.hwtstamp = kसमय_set(fअगरo.secs, fअगरo.ns);
			skb_complete_tx_बारtamp(skb, &shhwtstamps);

			वापस;
		पूर्ण

		/* Valid signature but करोes not match the one of the
		 * packet in the FIFO right now, reschedule it क्रम later
		 * packets.
		 */
		__skb_queue_tail(&ptp->tx_queue, skb);
	पूर्ण
पूर्ण

अटल व्योम vsc85xx_get_tx_ts(काष्ठा vsc85xx_ptp *ptp)
अणु
	u32 reg;

	करो अणु
		vsc85xx_dequeue_skb(ptp);

		/* If other बारtamps are available in the FIFO, process them. */
		reg = vsc85xx_ts_पढ़ो_csr(ptp->phydev, PROCESSOR,
					  MSCC_PHY_PTP_EGR_TS_FIFO_CTRL);
	पूर्ण जबतक (PTP_EGR_FIFO_LEVEL_LAST_READ(reg) > 1);
पूर्ण

अटल पूर्णांक vsc85xx_ptp_cmp_init(काष्ठा phy_device *phydev, क्रमागत ts_blk blk)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	bool base = phydev->mdio.addr == vsc8531->ts_base_addr;
	u8 msgs[] = अणु
		PTP_MSGTYPE_SYNC,
		PTP_MSGTYPE_DELAY_REQ
	पूर्ण;
	u32 val;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(msgs); i++) अणु
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_PTP_FLOW_ENA(i),
				     base ? PTP_FLOW_VALID_CH0 :
				     PTP_FLOW_VALID_CH1);

		val = vsc85xx_ts_पढ़ो_csr(phydev, blk,
					  MSCC_ANA_PTP_FLOW_DOMAIN_RANGE(i));
		val &= ~PTP_FLOW_DOMAIN_RANGE_ENA;
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_DOMAIN_RANGE(i), val);

		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_MATCH_UPPER(i),
				     msgs[i] << 24);

		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_PTP_FLOW_MASK_UPPER(i),
				     PTP_FLOW_MSG_TYPE_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_eth_cmp1_init(काष्ठा phy_device *phydev, क्रमागत ts_blk blk)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	bool base = phydev->mdio.addr == vsc8531->ts_base_addr;
	u32 val;

	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_PHY_ANA_ETH1_NXT_PROT_TAG, 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_PHY_ANA_ETH1_NTX_PROT_VLAN_TPID,
			     ANA_ETH1_NTX_PROT_VLAN_TPID(ETH_P_8021AD));

	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_ENA(0),
			     base ? ETH1_FLOW_VALID_CH0 : ETH1_FLOW_VALID_CH1);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_MATCH_MODE(0),
			     ANA_ETH1_FLOW_MATCH_VLAN_TAG2);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_ADDR_MATCH1(0), 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_ADDR_MATCH2(0), 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk,
			     MSCC_ANA_ETH1_FLOW_VLAN_RANGE_I_TAG(0), 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_VLAN_TAG1(0), 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk,
			     MSCC_ANA_ETH1_FLOW_VLAN_TAG2_I_TAG(0), 0);

	val = vsc85xx_ts_पढ़ो_csr(phydev, blk,
				  MSCC_ANA_ETH1_FLOW_MATCH_MODE(0));
	val &= ~ANA_ETH1_FLOW_MATCH_VLAN_TAG_MASK;
	val |= ANA_ETH1_FLOW_MATCH_VLAN_VERIFY;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_MATCH_MODE(0),
			     val);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_ip_cmp1_init(काष्ठा phy_device *phydev, क्रमागत ts_blk blk)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	bool base = phydev->mdio.addr == vsc8531->ts_base_addr;
	u32 val;

	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_MATCH2_UPPER,
			     PTP_EV_PORT);
	/* Match on dest port only, ignore src */
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_MASK2_UPPER,
			     0xffff);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_MATCH2_LOWER,
			     0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_MASK2_LOWER, 0);

	val = vsc85xx_ts_पढ़ो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_ENA(0));
	val &= ~IP1_FLOW_ENA_CHANNEL_MASK_MASK;
	val |= base ? IP1_FLOW_VALID_CH0 : IP1_FLOW_VALID_CH1;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_ENA(0), val);

	/* Match all IPs */
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MATCH_UPPER(0), 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MASK_UPPER(0), 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MATCH_UPPER_MID(0),
			     0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MASK_UPPER_MID(0),
			     0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MATCH_LOWER_MID(0),
			     0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MASK_LOWER_MID(0),
			     0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MATCH_LOWER(0), 0);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_MASK_LOWER(0), 0);

	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_PTP_IP_CHKSUM_SEL, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_adjfine(काष्ठा ptp_घड़ी_info *info, दीर्घ scaled_ppm)
अणु
	काष्ठा vsc85xx_ptp *ptp = container_of(info, काष्ठा vsc85xx_ptp, caps);
	काष्ठा phy_device *phydev = ptp->phydev;
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	u64 adj = 0;
	u32 val;

	अगर (असल(scaled_ppm) < 66 || असल(scaled_ppm) > 65536UL * 1000000UL)
		वापस 0;

	adj = भाग64_u64(1000000ULL * 65536ULL, असल(scaled_ppm));
	अगर (adj > 1000000000L)
		adj = 1000000000L;

	val = PTP_AUTO_ADJ_NS_ROLLOVER(adj);
	val |= scaled_ppm > 0 ? PTP_AUTO_ADJ_ADD_1NS : PTP_AUTO_ADJ_SUB_1NS;

	mutex_lock(&priv->phc_lock);

	/* Update the ppb val in nano seconds to the स्वतः adjust reg. */
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_AUTO_ADJ,
			     val);

	/* The स्वतः adjust update val is set to 0 after ग_लिखो operation. */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL);
	val |= PTP_LTC_CTRL_AUTO_ADJ_UPDATE;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL, val);

	mutex_unlock(&priv->phc_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __vsc85xx_समय_लो(काष्ठा ptp_घड़ी_info *info, काष्ठा बारpec64 *ts)
अणु
	काष्ठा vsc85xx_ptp *ptp = container_of(info, काष्ठा vsc85xx_ptp, caps);
	काष्ठा phy_device *phydev = ptp->phydev;
	काष्ठा vsc85xx_shared_निजी *shared =
		(काष्ठा vsc85xx_shared_निजी *)phydev->shared->priv;
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	u32 val;

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL);
	val |= PTP_LTC_CTRL_SAVE_ENA;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL, val);

	/* Local Time Counter (LTC) is put in SAVE* regs on rising edge of
	 * LOAD_SAVE pin.
	 */
	mutex_lock(&shared->gpio_lock);
	gpiod_set_value(priv->load_save, 1);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_LTC_SAVED_SEC_MSB);

	ts->tv_sec = ((समय64_t)val) << 32;

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_LTC_SAVED_SEC_LSB);
	ts->tv_sec += val;

	ts->tv_nsec = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
					  MSCC_PHY_PTP_LTC_SAVED_NS);

	gpiod_set_value(priv->load_save, 0);
	mutex_unlock(&shared->gpio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_समय_लो(काष्ठा ptp_घड़ी_info *info, काष्ठा बारpec64 *ts)
अणु
	काष्ठा vsc85xx_ptp *ptp = container_of(info, काष्ठा vsc85xx_ptp, caps);
	काष्ठा phy_device *phydev = ptp->phydev;
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	mutex_lock(&priv->phc_lock);
	__vsc85xx_समय_लो(info, ts);
	mutex_unlock(&priv->phc_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __vsc85xx_समय_रखो(काष्ठा ptp_घड़ी_info *info,
			     स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा vsc85xx_ptp *ptp = container_of(info, काष्ठा vsc85xx_ptp, caps);
	काष्ठा phy_device *phydev = ptp->phydev;
	काष्ठा vsc85xx_shared_निजी *shared =
		(काष्ठा vsc85xx_shared_निजी *)phydev->shared->priv;
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	u32 val;

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_LOAD_SEC_MSB,
			     PTP_LTC_LOAD_SEC_MSB(ts->tv_sec));
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_LOAD_SEC_LSB,
			     PTP_LTC_LOAD_SEC_LSB(ts->tv_sec));
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_LOAD_NS,
			     PTP_LTC_LOAD_NS(ts->tv_nsec));

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL);
	val |= PTP_LTC_CTRL_LOAD_ENA;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL, val);

	/* Local Time Counter (LTC) is set from LOAD* regs on rising edge of
	 * LOAD_SAVE pin.
	 */
	mutex_lock(&shared->gpio_lock);
	gpiod_set_value(priv->load_save, 1);

	val &= ~PTP_LTC_CTRL_LOAD_ENA;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL, val);

	gpiod_set_value(priv->load_save, 0);
	mutex_unlock(&shared->gpio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_समय_रखो(काष्ठा ptp_घड़ी_info *info,
			   स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा vsc85xx_ptp *ptp = container_of(info, काष्ठा vsc85xx_ptp, caps);
	काष्ठा phy_device *phydev = ptp->phydev;
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	mutex_lock(&priv->phc_lock);
	__vsc85xx_समय_रखो(info, ts);
	mutex_unlock(&priv->phc_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_adjसमय(काष्ठा ptp_घड़ी_info *info, s64 delta)
अणु
	काष्ठा vsc85xx_ptp *ptp = container_of(info, काष्ठा vsc85xx_ptp, caps);
	काष्ठा phy_device *phydev = ptp->phydev;
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	u32 val;

	/* Can't recover that big of an offset. Let's set the समय directly. */
	अगर (असल(delta) >= NSEC_PER_SEC) अणु
		काष्ठा बारpec64 ts;
		u64 now;

		mutex_lock(&priv->phc_lock);

		__vsc85xx_समय_लो(info, &ts);
		now = kसमय_प्रकारo_ns(बारpec64_to_kसमय(ts));
		ts = ns_to_बारpec64(now + delta);
		__vsc85xx_समय_रखो(info, &ts);

		mutex_unlock(&priv->phc_lock);

		वापस 0;
	पूर्ण

	mutex_lock(&priv->phc_lock);

	val = PTP_LTC_OFFSET_VAL(असल(delta)) | PTP_LTC_OFFSET_ADJ;
	अगर (delta > 0)
		val |= PTP_LTC_OFFSET_ADD;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_OFFSET, val);

	mutex_unlock(&priv->phc_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_eth1_next_comp(काष्ठा phy_device *phydev, क्रमागत ts_blk blk,
				  u32 next_comp, u32 etype)
अणु
	u32 val;

	val = vsc85xx_ts_पढ़ो_csr(phydev, blk, MSCC_PHY_ANA_ETH1_NTX_PROT);
	val &= ~ANA_ETH1_NTX_PROT_COMPARATOR_MASK;
	val |= next_comp;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_PHY_ANA_ETH1_NTX_PROT, val);

	val = ANA_ETH1_NXT_PROT_ETYPE_MATCH(etype) |
		ANA_ETH1_NXT_PROT_ETYPE_MATCH_ENA;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk,
			     MSCC_PHY_ANA_ETH1_NXT_PROT_ETYPE_MATCH, val);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_ip1_next_comp(काष्ठा phy_device *phydev, क्रमागत ts_blk blk,
				 u32 next_comp, u32 header)
अणु
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_NXT_COMP,
			     ANA_IP1_NXT_PROT_NXT_COMP_BYTES_HDR(header) |
			     next_comp);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_ts_ptp_action_flow(काष्ठा phy_device *phydev, क्रमागत ts_blk blk, u8 flow, क्रमागत ptp_cmd cmd)
अणु
	u32 val;

	/* Check non-zero reserved field */
	val = PTP_FLOW_PTP_0_FIELD_PTP_FRAME | PTP_FLOW_PTP_0_FIELD_RSVRD_CHECK;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk,
			     MSCC_ANA_PTP_FLOW_PTP_0_FIELD(flow), val);

	val = PTP_FLOW_PTP_ACTION_CORR_OFFSET(8) |
	      PTP_FLOW_PTP_ACTION_TIME_OFFSET(8) |
	      PTP_FLOW_PTP_ACTION_PTP_CMD(cmd == PTP_SAVE_IN_TS_FIFO ?
					  PTP_NOP : cmd);
	अगर (cmd == PTP_SAVE_IN_TS_FIFO)
		val |= PTP_FLOW_PTP_ACTION_SAVE_LOCAL_TIME;
	अन्यथा अगर (cmd == PTP_WRITE_NS)
		val |= PTP_FLOW_PTP_ACTION_MOD_FRAME_STATUS_UPDATE |
		       PTP_FLOW_PTP_ACTION_MOD_FRAME_STATUS_BYTE_OFFSET(6);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_PTP_FLOW_PTP_ACTION(flow),
			     val);

	अगर (cmd == PTP_WRITE_1588)
		/* Reग_लिखो बारtamp directly in frame */
		val = PTP_FLOW_PTP_ACTION2_REWRITE_OFFSET(34) |
		      PTP_FLOW_PTP_ACTION2_REWRITE_BYTES(10);
	अन्यथा अगर (cmd == PTP_SAVE_IN_TS_FIFO)
		/* no reग_लिखो */
		val = PTP_FLOW_PTP_ACTION2_REWRITE_OFFSET(0) |
		      PTP_FLOW_PTP_ACTION2_REWRITE_BYTES(0);
	अन्यथा
		/* Write in reserved field */
		val = PTP_FLOW_PTP_ACTION2_REWRITE_OFFSET(16) |
		      PTP_FLOW_PTP_ACTION2_REWRITE_BYTES(4);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk,
			     MSCC_ANA_PTP_FLOW_PTP_ACTION2(flow), val);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_ptp_conf(काष्ठा phy_device *phydev, क्रमागत ts_blk blk,
			    bool one_step, bool enable)
अणु
	u8 msgs[] = अणु
		PTP_MSGTYPE_SYNC,
		PTP_MSGTYPE_DELAY_REQ
	पूर्ण;
	u32 val;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(msgs); i++) अणु
		अगर (blk == INGRESS)
			vsc85xx_ts_ptp_action_flow(phydev, blk, msgs[i],
						   PTP_WRITE_NS);
		अन्यथा अगर (msgs[i] == PTP_MSGTYPE_SYNC && one_step)
			/* no need to know Sync t when sending in one_step */
			vsc85xx_ts_ptp_action_flow(phydev, blk, msgs[i],
						   PTP_WRITE_1588);
		अन्यथा
			vsc85xx_ts_ptp_action_flow(phydev, blk, msgs[i],
						   PTP_SAVE_IN_TS_FIFO);

		val = vsc85xx_ts_पढ़ो_csr(phydev, blk,
					  MSCC_ANA_PTP_FLOW_ENA(i));
		val &= ~PTP_FLOW_ENA;
		अगर (enable)
			val |= PTP_FLOW_ENA;
		vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_PTP_FLOW_ENA(i),
				     val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_eth1_conf(काष्ठा phy_device *phydev, क्रमागत ts_blk blk,
			     bool enable)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	u32 val = ANA_ETH1_FLOW_ADDR_MATCH2_DEST;

	अगर (vsc8531->ptp->rx_filter == HWTSTAMP_FILTER_PTP_V2_L2_EVENT) अणु
		/* PTP over Ethernet multicast address क्रम SYNC and DELAY msg */
		u8 ptp_multicast[6] = अणु0x01, 0x1b, 0x19, 0x00, 0x00, 0x00पूर्ण;

		val |= ANA_ETH1_FLOW_ADDR_MATCH2_FULL_ADDR |
		       get_unaligned_be16(&ptp_multicast[4]);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_ETH1_FLOW_ADDR_MATCH2(0), val);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_ETH1_FLOW_ADDR_MATCH1(0),
				     get_unaligned_be32(ptp_multicast));
	पूर्ण अन्यथा अणु
		val |= ANA_ETH1_FLOW_ADDR_MATCH2_ANY_MULTICAST;
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_ETH1_FLOW_ADDR_MATCH2(0), val);
		vsc85xx_ts_ग_लिखो_csr(phydev, blk,
				     MSCC_ANA_ETH1_FLOW_ADDR_MATCH1(0), 0);
	पूर्ण

	val = vsc85xx_ts_पढ़ो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_ENA(0));
	val &= ~ETH1_FLOW_ENA;
	अगर (enable)
		val |= ETH1_FLOW_ENA;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_ETH1_FLOW_ENA(0), val);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_ip1_conf(काष्ठा phy_device *phydev, क्रमागत ts_blk blk,
			    bool enable)
अणु
	u32 val;

	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_IP1_MODE,
			     ANA_IP1_NXT_PROT_IPV4 |
			     ANA_IP1_NXT_PROT_FLOW_OFFSET_IPV4);

	/* Matching UDP protocol number */
	val = ANA_IP1_NXT_PROT_IP_MATCH1_PROT_MASK(0xff) |
	      ANA_IP1_NXT_PROT_IP_MATCH1_PROT_MATCH(IPPROTO_UDP) |
	      ANA_IP1_NXT_PROT_IP_MATCH1_PROT_OFF(9);
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_IP_MATCH1,
			     val);

	/* End of IP protocol, start of next protocol (UDP) */
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_OFFSET2,
			     ANA_IP1_NXT_PROT_OFFSET2(20));

	val = vsc85xx_ts_पढ़ो_csr(phydev, blk,
				  MSCC_ANA_IP1_NXT_PROT_UDP_CHKSUM);
	val &= ~(IP1_NXT_PROT_UDP_CHKSUM_OFF_MASK |
		 IP1_NXT_PROT_UDP_CHKSUM_WIDTH_MASK);
	val |= IP1_NXT_PROT_UDP_CHKSUM_WIDTH(2);

	val &= ~(IP1_NXT_PROT_UDP_CHKSUM_UPDATE |
		 IP1_NXT_PROT_UDP_CHKSUM_CLEAR);
	/* UDP checksum offset in IPv4 packet
	 * according to: https://tools.ietf.org/hपंचांगl/rfc768
	 */
	val |= IP1_NXT_PROT_UDP_CHKSUM_OFF(26) | IP1_NXT_PROT_UDP_CHKSUM_CLEAR;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_NXT_PROT_UDP_CHKSUM,
			     val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_ENA(0));
	val &= ~(IP1_FLOW_MATCH_ADDR_MASK | IP1_FLOW_ENA);
	val |= IP1_FLOW_MATCH_DEST_SRC_ADDR;
	अगर (enable)
		val |= IP1_FLOW_ENA;
	vsc85xx_ts_ग_लिखो_csr(phydev, blk, MSCC_ANA_IP1_FLOW_ENA(0), val);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_ts_engine_init(काष्ठा phy_device *phydev, bool one_step)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	bool ptp_l4, base = phydev->mdio.addr == vsc8531->ts_base_addr;
	u8 eng_id = base ? 0 : 1;
	u32 val;

	ptp_l4 = vsc8531->ptp->rx_filter == HWTSTAMP_FILTER_PTP_V2_L4_EVENT;

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_ANALYZER_MODE);
	/* Disable INGRESS and EGRESS so engine eng_id can be reconfigured */
	val &= ~(PTP_ANALYZER_MODE_EGR_ENA(BIT(eng_id)) |
		 PTP_ANALYZER_MODE_INGR_ENA(BIT(eng_id)));
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ANALYZER_MODE,
			     val);

	अगर (vsc8531->ptp->rx_filter == HWTSTAMP_FILTER_PTP_V2_L2_EVENT) अणु
		vsc85xx_eth1_next_comp(phydev, INGRESS,
				       ANA_ETH1_NTX_PROT_PTP_OAM, ETH_P_1588);
		vsc85xx_eth1_next_comp(phydev, EGRESS,
				       ANA_ETH1_NTX_PROT_PTP_OAM, ETH_P_1588);
	पूर्ण अन्यथा अणु
		vsc85xx_eth1_next_comp(phydev, INGRESS,
				       ANA_ETH1_NTX_PROT_IP_UDP_ACH_1,
				       ETH_P_IP);
		vsc85xx_eth1_next_comp(phydev, EGRESS,
				       ANA_ETH1_NTX_PROT_IP_UDP_ACH_1,
				       ETH_P_IP);
		/* Header length of IPv[4/6] + UDP */
		vsc85xx_ip1_next_comp(phydev, INGRESS,
				      ANA_ETH1_NTX_PROT_PTP_OAM, 28);
		vsc85xx_ip1_next_comp(phydev, EGRESS,
				      ANA_ETH1_NTX_PROT_PTP_OAM, 28);
	पूर्ण

	vsc85xx_eth1_conf(phydev, INGRESS,
			  vsc8531->ptp->rx_filter != HWTSTAMP_FILTER_NONE);
	vsc85xx_ip1_conf(phydev, INGRESS,
			 ptp_l4 && vsc8531->ptp->rx_filter != HWTSTAMP_FILTER_NONE);
	vsc85xx_ptp_conf(phydev, INGRESS, one_step,
			 vsc8531->ptp->rx_filter != HWTSTAMP_FILTER_NONE);

	vsc85xx_eth1_conf(phydev, EGRESS,
			  vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF);
	vsc85xx_ip1_conf(phydev, EGRESS,
			 ptp_l4 && vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF);
	vsc85xx_ptp_conf(phydev, EGRESS, one_step,
			 vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF);

	val &= ~PTP_ANALYZER_MODE_EGR_ENA(BIT(eng_id));
	अगर (vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF)
		val |= PTP_ANALYZER_MODE_EGR_ENA(BIT(eng_id));

	val &= ~PTP_ANALYZER_MODE_INGR_ENA(BIT(eng_id));
	अगर (vsc8531->ptp->rx_filter != HWTSTAMP_FILTER_NONE)
		val |= PTP_ANALYZER_MODE_INGR_ENA(BIT(eng_id));

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ANALYZER_MODE,
			     val);

	वापस 0;
पूर्ण

व्योम vsc85xx_link_change_notअगरy(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	mutex_lock(&priv->ts_lock);
	vsc85xx_ts_set_latencies(phydev);
	mutex_unlock(&priv->ts_lock);
पूर्ण

अटल व्योम vsc85xx_ts_reset_fअगरo(काष्ठा phy_device *phydev)
अणु
	u32 val;

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_TS_FIFO_CTRL);
	val |= PTP_EGR_TS_FIFO_RESET;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_TS_FIFO_CTRL,
			     val);

	val &= ~PTP_EGR_TS_FIFO_RESET;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_TS_FIFO_CTRL,
			     val);
पूर्ण

अटल पूर्णांक vsc85xx_hwtstamp(काष्ठा mii_बारtamper *mii_ts, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा vsc8531_निजी *vsc8531 =
		container_of(mii_ts, काष्ठा vsc8531_निजी, mii_ts);
	काष्ठा phy_device *phydev = vsc8531->ptp->phydev;
	काष्ठा hwtstamp_config cfg;
	bool one_step = false;
	u32 val;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	अगर (cfg.flags)
		वापस -EINVAL;

	चयन (cfg.tx_type) अणु
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		one_step = true;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	हाल HWTSTAMP_TX_OFF:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	vsc8531->ptp->tx_type = cfg.tx_type;

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		/* ETH->IP->UDP->PTP */
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		/* ETH->PTP */
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	vsc8531->ptp->rx_filter = cfg.rx_filter;

	mutex_lock(&vsc8531->ts_lock);

	__skb_queue_purge(&vsc8531->ptp->tx_queue);
	__skb_queue_head_init(&vsc8531->ptp->tx_queue);

	/* Disable predictor जबतक configuring the 1588 block */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_INGR_PREDICTOR);
	val &= ~PTP_INGR_PREDICTOR_EN;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_PREDICTOR,
			     val);
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_PREDICTOR);
	val &= ~PTP_EGR_PREDICTOR_EN;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_PREDICTOR,
			     val);

	/* Bypass egress or ingress blocks अगर बारtamping isn't used */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_IFACE_CTRL);
	val &= ~(PTP_IFACE_CTRL_EGR_BYPASS | PTP_IFACE_CTRL_INGR_BYPASS);
	अगर (vsc8531->ptp->tx_type == HWTSTAMP_TX_OFF)
		val |= PTP_IFACE_CTRL_EGR_BYPASS;
	अगर (vsc8531->ptp->rx_filter == HWTSTAMP_FILTER_NONE)
		val |= PTP_IFACE_CTRL_INGR_BYPASS;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_IFACE_CTRL, val);

	/* Resetting FIFO so that it's empty after reconfiguration */
	vsc85xx_ts_reset_fअगरo(phydev);

	vsc85xx_ts_engine_init(phydev, one_step);

	/* Re-enable predictors now */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_INGR_PREDICTOR);
	val |= PTP_INGR_PREDICTOR_EN;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_PREDICTOR,
			     val);
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_PREDICTOR);
	val |= PTP_EGR_PREDICTOR_EN;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_PREDICTOR,
			     val);

	vsc8531->ptp->configured = 1;
	mutex_unlock(&vsc8531->ts_lock);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vsc85xx_ts_info(काष्ठा mii_बारtamper *mii_ts,
			   काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा vsc8531_निजी *vsc8531 =
		container_of(mii_ts, काष्ठा vsc8531_निजी, mii_ts);

	info->phc_index = ptp_घड़ी_index(vsc8531->ptp->ptp_घड़ी);
	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON) |
		(1 << HWTSTAMP_TX_ONESTEP_SYNC);
	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT);

	वापस 0;
पूर्ण

अटल व्योम vsc85xx_txtstamp(काष्ठा mii_बारtamper *mii_ts,
			     काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा vsc8531_निजी *vsc8531 =
		container_of(mii_ts, काष्ठा vsc8531_निजी, mii_ts);

	अगर (!vsc8531->ptp->configured)
		वापस;

	अगर (vsc8531->ptp->tx_type == HWTSTAMP_TX_OFF) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	mutex_lock(&vsc8531->ts_lock);
	__skb_queue_tail(&vsc8531->ptp->tx_queue, skb);
	mutex_unlock(&vsc8531->ts_lock);
पूर्ण

अटल bool vsc85xx_rxtstamp(काष्ठा mii_बारtamper *mii_ts,
			     काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा vsc8531_निजी *vsc8531 =
		container_of(mii_ts, काष्ठा vsc8531_निजी, mii_ts);
	काष्ठा skb_shared_hwtstamps *shhwtstamps = शून्य;
	काष्ठा vsc85xx_ptphdr *ptphdr;
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ ns;

	अगर (!vsc8531->ptp->configured)
		वापस false;

	अगर (vsc8531->ptp->rx_filter == HWTSTAMP_FILTER_NONE ||
	    type == PTP_CLASS_NONE)
		वापस false;

	vsc85xx_समय_लो(&vsc8531->ptp->caps, &ts);

	ptphdr = get_ptp_header_rx(skb, vsc8531->ptp->rx_filter);
	अगर (!ptphdr)
		वापस false;

	shhwtstamps = skb_hwtstamps(skb);
	स_रखो(shhwtstamps, 0, माप(काष्ठा skb_shared_hwtstamps));

	ns = ntohl(ptphdr->rsrvd2);

	/* nsec is in reserved field */
	अगर (ts.tv_nsec < ns)
		ts.tv_sec--;

	shhwtstamps->hwtstamp = kसमय_set(ts.tv_sec, ns);
	netअगर_rx_ni(skb);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info vsc85xx_clk_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "VSC85xx timer",
	.max_adj	= S32_MAX,
	.n_alarm	= 0,
	.n_pins		= 0,
	.n_ext_ts	= 0,
	.n_per_out	= 0,
	.pps		= 0,
	.adjसमय        = &vsc85xx_adjसमय,
	.adjfine	= &vsc85xx_adjfine,
	.समय_लो64	= &vsc85xx_समय_लो,
	.समय_रखो64	= &vsc85xx_समय_रखो,
पूर्ण;

अटल काष्ठा vsc8531_निजी *vsc8584_base_priv(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;

	अगर (vsc8531->ts_base_addr != phydev->mdio.addr) अणु
		काष्ठा mdio_device *dev;

		dev = phydev->mdio.bus->mdio_map[vsc8531->ts_base_addr];
		phydev = container_of(dev, काष्ठा phy_device, mdio);

		वापस phydev->priv;
	पूर्ण

	वापस vsc8531;
पूर्ण

अटल bool vsc8584_is_1588_input_clk_configured(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = vsc8584_base_priv(phydev);

	वापस vsc8531->input_clk_init;
पूर्ण

अटल व्योम vsc8584_set_input_clk_configured(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = vsc8584_base_priv(phydev);

	vsc8531->input_clk_init = true;
पूर्ण

अटल पूर्णांक __vsc8584_init_ptp(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	u32 ltc_seq_e[] = अणु 0, 400000, 0, 0, 0 पूर्ण;
	u8  ltc_seq_a[] = अणु 8, 6, 5, 4, 2 पूर्ण;
	u32 val;

	अगर (!vsc8584_is_1588_input_clk_configured(phydev)) अणु
		phy_lock_mdio_bus(phydev);

		/* 1588_DIFF_INPUT_CLK configuration: Use an बाह्यal घड़ी क्रम
		 * the LTC, as per 3.13.29 in the VSC8584 datasheet.
		 */
		phy_ts_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
				  MSCC_PHY_PAGE_1588);
		phy_ts_base_ग_लिखो(phydev, 29, 0x7ae0);
		phy_ts_base_ग_लिखो(phydev, 30, 0xb71c);
		phy_ts_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
				  MSCC_PHY_PAGE_STANDARD);

		phy_unlock_mdio_bus(phydev);

		vsc8584_set_input_clk_configured(phydev);
	पूर्ण

	/* Disable predictor beक्रमe configuring the 1588 block */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_INGR_PREDICTOR);
	val &= ~PTP_INGR_PREDICTOR_EN;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_PREDICTOR,
			     val);
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_PREDICTOR);
	val &= ~PTP_EGR_PREDICTOR_EN;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_PREDICTOR,
			     val);

	/* By शेष, the पूर्णांकernal घड़ी of fixed rate 250MHz is used */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL);
	val &= ~PTP_LTC_CTRL_CLK_SEL_MASK;
	val |= PTP_LTC_CTRL_CLK_SEL_INTERNAL_250;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_CTRL, val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_SEQUENCE);
	val &= ~PTP_LTC_SEQUENCE_A_MASK;
	val |= PTP_LTC_SEQUENCE_A(ltc_seq_a[PHC_CLK_250MHZ]);
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_SEQUENCE, val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_SEQ);
	val &= ~(PTP_LTC_SEQ_ERR_MASK | PTP_LTC_SEQ_ADD_SUB);
	अगर (ltc_seq_e[PHC_CLK_250MHZ])
		val |= PTP_LTC_SEQ_ADD_SUB;
	val |= PTP_LTC_SEQ_ERR(ltc_seq_e[PHC_CLK_250MHZ]);
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_SEQ, val);

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_LTC_1PPS_WIDTH_ADJ,
			     PPS_WIDTH_ADJ);

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_DELAY_FIFO,
			     IS_ENABLED(CONFIG_MACSEC) ?
			     PTP_INGR_DELAY_FIFO_DEPTH_MACSEC :
			     PTP_INGR_DELAY_FIFO_DEPTH_DEFAULT);

	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_DELAY_FIFO,
			     IS_ENABLED(CONFIG_MACSEC) ?
			     PTP_EGR_DELAY_FIFO_DEPTH_MACSEC :
			     PTP_EGR_DELAY_FIFO_DEPTH_DEFAULT);

	/* Enable n-phase sampler क्रम Viper Rev-B */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_ACCUR_CFG_STATUS);
	val &= ~(PTP_ACCUR_PPS_OUT_BYPASS | PTP_ACCUR_PPS_IN_BYPASS |
		 PTP_ACCUR_EGR_SOF_BYPASS | PTP_ACCUR_INGR_SOF_BYPASS |
		 PTP_ACCUR_LOAD_SAVE_BYPASS);
	val |= PTP_ACCUR_PPS_OUT_CALIB_ERR | PTP_ACCUR_PPS_OUT_CALIB_DONE |
	       PTP_ACCUR_PPS_IN_CALIB_ERR | PTP_ACCUR_PPS_IN_CALIB_DONE |
	       PTP_ACCUR_EGR_SOF_CALIB_ERR | PTP_ACCUR_EGR_SOF_CALIB_DONE |
	       PTP_ACCUR_INGR_SOF_CALIB_ERR | PTP_ACCUR_INGR_SOF_CALIB_DONE |
	       PTP_ACCUR_LOAD_SAVE_CALIB_ERR | PTP_ACCUR_LOAD_SAVE_CALIB_DONE;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ACCUR_CFG_STATUS,
			     val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_ACCUR_CFG_STATUS);
	val |= PTP_ACCUR_CALIB_TRIGG;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ACCUR_CFG_STATUS,
			     val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_ACCUR_CFG_STATUS);
	val &= ~PTP_ACCUR_CALIB_TRIGG;
	val |= PTP_ACCUR_PPS_OUT_CALIB_ERR | PTP_ACCUR_PPS_OUT_CALIB_DONE |
	       PTP_ACCUR_PPS_IN_CALIB_ERR | PTP_ACCUR_PPS_IN_CALIB_DONE |
	       PTP_ACCUR_EGR_SOF_CALIB_ERR | PTP_ACCUR_EGR_SOF_CALIB_DONE |
	       PTP_ACCUR_INGR_SOF_CALIB_ERR | PTP_ACCUR_INGR_SOF_CALIB_DONE |
	       PTP_ACCUR_LOAD_SAVE_CALIB_ERR | PTP_ACCUR_LOAD_SAVE_CALIB_DONE;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ACCUR_CFG_STATUS,
			     val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_ACCUR_CFG_STATUS);
	val |= PTP_ACCUR_CALIB_TRIGG;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ACCUR_CFG_STATUS,
			     val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_ACCUR_CFG_STATUS);
	val &= ~PTP_ACCUR_CALIB_TRIGG;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ACCUR_CFG_STATUS,
			     val);

	/* Do not access FIFO via SI */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_TSTAMP_FIFO_SI);
	val &= ~PTP_TSTAMP_FIFO_SI_EN;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_TSTAMP_FIFO_SI,
			     val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_INGR_REWRITER_CTRL);
	val &= ~PTP_INGR_REWRITER_REDUCE_PREAMBLE;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_REWRITER_CTRL,
			     val);
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_REWRITER_CTRL);
	val &= ~PTP_EGR_REWRITER_REDUCE_PREAMBLE;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_REWRITER_CTRL,
			     val);

	/* Put the flag that indicates the frame has been modअगरied to bit 7 */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_INGR_REWRITER_CTRL);
	val |= PTP_INGR_REWRITER_FLAG_BIT_OFF(7) | PTP_INGR_REWRITER_FLAG_VAL;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_REWRITER_CTRL,
			     val);
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_REWRITER_CTRL);
	val |= PTP_EGR_REWRITER_FLAG_BIT_OFF(7);
	val &= ~PTP_EGR_REWRITER_FLAG_VAL;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_REWRITER_CTRL,
			     val);

	/* 30bit mode क्रम RX बारtamp, only the nanoseconds are kept in
	 * reserved field.
	 */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_INGR_TSP_CTRL);
	val |= PHY_PTP_INGR_TSP_CTRL_FRACT_NS;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_INGR_TSP_CTRL,
			     val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_TSP_CTRL);
	val |= PHY_PTP_EGR_TSP_CTRL_FRACT_NS;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_TSP_CTRL, val);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_SERIAL_TOD_IFACE);
	val |= PTP_SERIAL_TOD_IFACE_LS_AUTO_CLR;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_SERIAL_TOD_IFACE,
			     val);

	vsc85xx_ts_fsb_init(phydev);

	/* Set the Egress बारtamp FIFO configuration and status रेजिस्टर */
	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_EGR_TS_FIFO_CTRL);
	val &= ~(PTP_EGR_TS_FIFO_SIG_BYTES_MASK | PTP_EGR_TS_FIFO_THRESH_MASK);
	/* 16 bytes क्रम the signature, 10 क्रम the बारtamp in the TS FIFO */
	val |= PTP_EGR_TS_FIFO_SIG_BYTES(16) | PTP_EGR_TS_FIFO_THRESH(7);
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_EGR_TS_FIFO_CTRL,
			     val);

	vsc85xx_ts_reset_fअगरo(phydev);

	val = PTP_IFACE_CTRL_CLK_ENA;
	अगर (!IS_ENABLED(CONFIG_MACSEC))
		val |= PTP_IFACE_CTRL_GMII_PROT;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_IFACE_CTRL, val);

	vsc85xx_ts_set_latencies(phydev);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_VERSION_CODE);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_IFACE_CTRL);
	val |= PTP_IFACE_CTRL_EGR_BYPASS;
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_IFACE_CTRL, val);

	vsc85xx_ts_disable_flows(phydev, EGRESS);
	vsc85xx_ts_disable_flows(phydev, INGRESS);

	val = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				  MSCC_PHY_PTP_ANALYZER_MODE);
	/* Disable INGRESS and EGRESS so engine eng_id can be reconfigured */
	val &= ~(PTP_ANALYZER_MODE_EGR_ENA_MASK |
		 PTP_ANALYZER_MODE_INGR_ENA_MASK |
		 PTP_ANA_INGR_ENCAP_FLOW_MODE_MASK |
		 PTP_ANA_EGR_ENCAP_FLOW_MODE_MASK);
	/* Strict matching in flow (packets should match flows from the same
	 * index in all enabled comparators (except PTP)).
	 */
	val |= PTP_ANA_SPLIT_ENCAP_FLOW | PTP_ANA_INGR_ENCAP_FLOW_MODE(0x7) |
	       PTP_ANA_EGR_ENCAP_FLOW_MODE(0x7);
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_PTP_ANALYZER_MODE,
			     val);

	/* Initialized क्रम ingress and egress flows:
	 * - The Ethernet comparator.
	 * - The IP comparator.
	 * - The PTP comparator.
	 */
	vsc85xx_eth_cmp1_init(phydev, INGRESS);
	vsc85xx_ip_cmp1_init(phydev, INGRESS);
	vsc85xx_ptp_cmp_init(phydev, INGRESS);
	vsc85xx_eth_cmp1_init(phydev, EGRESS);
	vsc85xx_ip_cmp1_init(phydev, EGRESS);
	vsc85xx_ptp_cmp_init(phydev, EGRESS);

	vsc85xx_ts_eth_cmp1_sig(phydev);

	vsc8531->mii_ts.rxtstamp = vsc85xx_rxtstamp;
	vsc8531->mii_ts.txtstamp = vsc85xx_txtstamp;
	vsc8531->mii_ts.hwtstamp = vsc85xx_hwtstamp;
	vsc8531->mii_ts.ts_info  = vsc85xx_ts_info;
	phydev->mii_ts = &vsc8531->mii_ts;

	स_नकल(&vsc8531->ptp->caps, &vsc85xx_clk_caps, माप(vsc85xx_clk_caps));

	vsc8531->ptp->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&vsc8531->ptp->caps,
						     &phydev->mdio.dev);
	वापस PTR_ERR_OR_ZERO(vsc8531->ptp->ptp_घड़ी);
पूर्ण

व्योम vsc8584_config_ts_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	mutex_lock(&priv->ts_lock);
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR, MSCC_PHY_1588_VSC85XX_INT_MASK,
			     VSC85XX_1588_INT_MASK_MASK);
	mutex_unlock(&priv->ts_lock);
पूर्ण

पूर्णांक vsc8584_ptp_init(काष्ठा phy_device *phydev)
अणु
	चयन (phydev->phy_id & phydev->drv->phy_id_mask) अणु
	हाल PHY_ID_VSC8572:
	हाल PHY_ID_VSC8574:
	हाल PHY_ID_VSC8575:
	हाल PHY_ID_VSC8582:
	हाल PHY_ID_VSC8584:
		वापस __vsc8584_init_ptp(phydev);
	पूर्ण

	वापस 0;
पूर्ण

irqवापस_t vsc8584_handle_ts_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	पूर्णांक rc;

	mutex_lock(&priv->ts_lock);
	rc = vsc85xx_ts_पढ़ो_csr(phydev, PROCESSOR,
				 MSCC_PHY_1588_VSC85XX_INT_STATUS);
	/* Ack the PTP पूर्णांकerrupt */
	vsc85xx_ts_ग_लिखो_csr(phydev, PROCESSOR,
			     MSCC_PHY_1588_VSC85XX_INT_STATUS, rc);

	अगर (!(rc & VSC85XX_1588_INT_MASK_MASK)) अणु
		mutex_unlock(&priv->ts_lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (rc & VSC85XX_1588_INT_FIFO_ADD) अणु
		vsc85xx_get_tx_ts(priv->ptp);
	पूर्ण अन्यथा अगर (rc & VSC85XX_1588_INT_FIFO_OVERFLOW) अणु
		__skb_queue_purge(&priv->ptp->tx_queue);
		vsc85xx_ts_reset_fअगरo(phydev);
	पूर्ण

	mutex_unlock(&priv->ts_lock);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक vsc8584_ptp_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;

	vsc8531->ptp = devm_kzalloc(&phydev->mdio.dev, माप(*vsc8531->ptp),
				    GFP_KERNEL);
	अगर (!vsc8531->ptp)
		वापस -ENOMEM;

	mutex_init(&vsc8531->phc_lock);
	mutex_init(&vsc8531->ts_lock);

	/* Retrieve the shared load/save GPIO. Request it as non exclusive as
	 * the same GPIO can be requested by all the PHYs of the same package.
	 * This GPIO must be used with the gpio_lock taken (the lock is shared
	 * between all PHYs).
	 */
	vsc8531->load_save = devm_gpiod_get_optional(&phydev->mdio.dev, "load-save",
						     GPIOD_FLAGS_BIT_NONEXCLUSIVE |
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(vsc8531->load_save)) अणु
		phydev_err(phydev, "Can't get load-save GPIO (%ld)\n",
			   PTR_ERR(vsc8531->load_save));
		वापस PTR_ERR(vsc8531->load_save);
	पूर्ण

	vsc8531->ptp->phydev = phydev;

	वापस 0;
पूर्ण

पूर्णांक vsc8584_ptp_probe_once(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc85xx_shared_निजी *shared =
		(काष्ठा vsc85xx_shared_निजी *)phydev->shared->priv;

	/* Initialize shared GPIO lock */
	mutex_init(&shared->gpio_lock);

	वापस 0;
पूर्ण
