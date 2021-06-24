<शैली गुरु>
/*
 * Copyright (c) 2005-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश "common.h"
#समावेश "regs.h"

/*
 * # of exact address filters.  The first one is used क्रम the station address,
 * the rest are available क्रम multicast addresses.
 */
#घोषणा EXACT_ADDR_FILTERS 8

अटल अंतरभूत पूर्णांक macidx(स्थिर काष्ठा cmac *mac)
अणु
	वापस mac->offset / (XGMAC0_1_BASE_ADDR - XGMAC0_0_BASE_ADDR);
पूर्ण

अटल व्योम xaui_serdes_reset(काष्ठा cmac *mac)
अणु
	अटल स्थिर अचिन्हित पूर्णांक clear[] = अणु
		F_PWRDN0 | F_PWRDN1, F_RESETPLL01, F_RESET0 | F_RESET1,
		F_PWRDN2 | F_PWRDN3, F_RESETPLL23, F_RESET2 | F_RESET3
	पूर्ण;

	पूर्णांक i;
	काष्ठा adapter *adap = mac->adapter;
	u32 ctrl = A_XGM_SERDES_CTRL0 + mac->offset;

	t3_ग_लिखो_reg(adap, ctrl, adap->params.vpd.xauicfg[macidx(mac)] |
		     F_RESET3 | F_RESET2 | F_RESET1 | F_RESET0 |
		     F_PWRDN3 | F_PWRDN2 | F_PWRDN1 | F_PWRDN0 |
		     F_RESETPLL23 | F_RESETPLL01);
	t3_पढ़ो_reg(adap, ctrl);
	udelay(15);

	क्रम (i = 0; i < ARRAY_SIZE(clear); i++) अणु
		t3_set_reg_field(adap, ctrl, clear[i], 0);
		udelay(15);
	पूर्ण
पूर्ण

व्योम t3b_pcs_reset(काष्ठा cmac *mac)
अणु
	t3_set_reg_field(mac->adapter, A_XGM_RESET_CTRL + mac->offset,
			 F_PCS_RESET_, 0);
	udelay(20);
	t3_set_reg_field(mac->adapter, A_XGM_RESET_CTRL + mac->offset, 0,
			 F_PCS_RESET_);
पूर्ण

पूर्णांक t3_mac_reset(काष्ठा cmac *mac)
अणु
	अटल स्थिर काष्ठा addr_val_pair mac_reset_avp[] = अणु
		अणुA_XGM_TX_CTRL, 0पूर्ण,
		अणुA_XGM_RX_CTRL, 0पूर्ण,
		अणुA_XGM_RX_CFG, F_DISPAUSEFRAMES | F_EN1536BFRAMES |
		 F_RMFCS | F_ENJUMBO | F_ENHASHMCASTपूर्ण,
		अणुA_XGM_RX_HASH_LOW, 0पूर्ण,
		अणुA_XGM_RX_HASH_HIGH, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_1, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_2, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_3, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_4, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_5, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_6, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_7, 0पूर्ण,
		अणुA_XGM_RX_EXACT_MATCH_LOW_8, 0पूर्ण,
		अणुA_XGM_STAT_CTRL, F_CLRSTATSपूर्ण
	पूर्ण;
	u32 val;
	काष्ठा adapter *adap = mac->adapter;
	अचिन्हित पूर्णांक oft = mac->offset;

	t3_ग_लिखो_reg(adap, A_XGM_RESET_CTRL + oft, F_MAC_RESET_);
	t3_पढ़ो_reg(adap, A_XGM_RESET_CTRL + oft);	/* flush */

	t3_ग_लिखो_regs(adap, mac_reset_avp, ARRAY_SIZE(mac_reset_avp), oft);
	t3_set_reg_field(adap, A_XGM_RXFIFO_CFG + oft,
			 F_RXSTRFRWRD | F_DISERRFRAMES,
			 uses_xaui(adap) ? 0 : F_RXSTRFRWRD);
	t3_set_reg_field(adap, A_XGM_TXFIFO_CFG + oft, 0, F_UNDERUNFIX);

	अगर (uses_xaui(adap)) अणु
		अगर (adap->params.rev == 0) अणु
			t3_set_reg_field(adap, A_XGM_SERDES_CTRL + oft, 0,
					 F_RXENABLE | F_TXENABLE);
			अगर (t3_रुको_op_करोne(adap, A_XGM_SERDES_STATUS1 + oft,
					    F_CMULOCK, 1, 5, 2)) अणु
				CH_ERR(adap,
				       "MAC %d XAUI SERDES CMU lock failed\n",
				       macidx(mac));
				वापस -1;
			पूर्ण
			t3_set_reg_field(adap, A_XGM_SERDES_CTRL + oft, 0,
					 F_SERDESRESET_);
		पूर्ण अन्यथा
			xaui_serdes_reset(mac);
	पूर्ण

	t3_set_reg_field(adap, A_XGM_RX_MAX_PKT_SIZE + oft,
			 V_RXMAXFRAMERSIZE(M_RXMAXFRAMERSIZE),
			 V_RXMAXFRAMERSIZE(MAX_FRAME_SIZE) | F_RXENFRAMER);
	val = F_MAC_RESET_ | F_XGMAC_STOP_EN;

	अगर (is_10G(adap))
		val |= F_PCS_RESET_;
	अन्यथा अगर (uses_xaui(adap))
		val |= F_PCS_RESET_ | F_XG2G_RESET_;
	अन्यथा
		val |= F_RGMII_RESET_ | F_XG2G_RESET_;
	t3_ग_लिखो_reg(adap, A_XGM_RESET_CTRL + oft, val);
	t3_पढ़ो_reg(adap, A_XGM_RESET_CTRL + oft);	/* flush */
	अगर ((val & F_PCS_RESET_) && adap->params.rev) अणु
		msleep(1);
		t3b_pcs_reset(mac);
	पूर्ण

	स_रखो(&mac->stats, 0, माप(mac->stats));
	वापस 0;
पूर्ण

अटल पूर्णांक t3b2_mac_reset(काष्ठा cmac *mac)
अणु
	काष्ठा adapter *adap = mac->adapter;
	अचिन्हित पूर्णांक oft = mac->offset, store;
	पूर्णांक idx = macidx(mac);
	u32 val;

	अगर (!macidx(mac))
		t3_set_reg_field(adap, A_MPS_CFG, F_PORT0ACTIVE, 0);
	अन्यथा
		t3_set_reg_field(adap, A_MPS_CFG, F_PORT1ACTIVE, 0);

	/* Stop NIC traffic to reduce the number of TXTOGGLES */
	t3_set_reg_field(adap, A_MPS_CFG, F_ENFORCEPKT, 0);
	/* Ensure TX drains */
	t3_set_reg_field(adap, A_XGM_TX_CFG + oft, F_TXPAUSEEN, 0);

	t3_ग_लिखो_reg(adap, A_XGM_RESET_CTRL + oft, F_MAC_RESET_);
	t3_पढ़ो_reg(adap, A_XGM_RESET_CTRL + oft);    /* flush */

	/* Store A_TP_TX_DROP_CFG_CH0 */
	t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR, A_TP_TX_DROP_CFG_CH0 + idx);
	store = t3_पढ़ो_reg(adap, A_TP_TX_DROP_CFG_CH0 + idx);

	msleep(10);

	/* Change DROP_CFG to 0xc0000011 */
	t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR, A_TP_TX_DROP_CFG_CH0 + idx);
	t3_ग_लिखो_reg(adap, A_TP_PIO_DATA, 0xc0000011);

	/* Check क्रम xgm Rx fअगरo empty */
	/* Increased loop count to 1000 from 5 cover 1G and 100Mbps हाल */
	अगर (t3_रुको_op_करोne(adap, A_XGM_RX_MAX_PKT_SIZE_ERR_CNT + oft,
			    0x80000000, 1, 1000, 2)) अणु
		CH_ERR(adap, "MAC %d Rx fifo drain failed\n",
		       macidx(mac));
		वापस -1;
	पूर्ण

	t3_ग_लिखो_reg(adap, A_XGM_RESET_CTRL + oft, 0);
	t3_पढ़ो_reg(adap, A_XGM_RESET_CTRL + oft);    /* flush */

	val = F_MAC_RESET_;
	अगर (is_10G(adap))
		val |= F_PCS_RESET_;
	अन्यथा अगर (uses_xaui(adap))
		val |= F_PCS_RESET_ | F_XG2G_RESET_;
	अन्यथा
		val |= F_RGMII_RESET_ | F_XG2G_RESET_;
	t3_ग_लिखो_reg(adap, A_XGM_RESET_CTRL + oft, val);
	t3_पढ़ो_reg(adap, A_XGM_RESET_CTRL + oft);  /* flush */
	अगर ((val & F_PCS_RESET_) && adap->params.rev) अणु
		msleep(1);
		t3b_pcs_reset(mac);
	पूर्ण
	t3_ग_लिखो_reg(adap, A_XGM_RX_CFG + oft,
		     F_DISPAUSEFRAMES | F_EN1536BFRAMES |
		     F_RMFCS | F_ENJUMBO | F_ENHASHMCAST);

	/* Restore the DROP_CFG */
	t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR, A_TP_TX_DROP_CFG_CH0 + idx);
	t3_ग_लिखो_reg(adap, A_TP_PIO_DATA, store);

	अगर (!idx)
		t3_set_reg_field(adap, A_MPS_CFG, 0, F_PORT0ACTIVE);
	अन्यथा
		t3_set_reg_field(adap, A_MPS_CFG, 0, F_PORT1ACTIVE);

	/* re-enable nic traffic */
	t3_set_reg_field(adap, A_MPS_CFG, F_ENFORCEPKT, 1);

	/*  Set: re-enable NIC traffic */
	t3_set_reg_field(adap, A_MPS_CFG, F_ENFORCEPKT, 1);

	वापस 0;
पूर्ण

/*
 * Set the exact match रेजिस्टर 'idx' to recognize the given Ethernet address.
 */
अटल व्योम set_addr_filter(काष्ठा cmac *mac, पूर्णांक idx, स्थिर u8 * addr)
अणु
	u32 addr_lo, addr_hi;
	अचिन्हित पूर्णांक oft = mac->offset + idx * 8;

	addr_lo = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	addr_hi = (addr[5] << 8) | addr[4];

	t3_ग_लिखो_reg(mac->adapter, A_XGM_RX_EXACT_MATCH_LOW_1 + oft, addr_lo);
	t3_ग_लिखो_reg(mac->adapter, A_XGM_RX_EXACT_MATCH_HIGH_1 + oft, addr_hi);
पूर्ण

/* Set one of the station's unicast MAC addresses. */
पूर्णांक t3_mac_set_address(काष्ठा cmac *mac, अचिन्हित पूर्णांक idx, u8 addr[6])
अणु
	अगर (idx >= mac->nucast)
		वापस -EINVAL;
	set_addr_filter(mac, idx, addr);
	वापस 0;
पूर्ण

/*
 * Specअगरy the number of exact address filters that should be reserved क्रम
 * unicast addresses.  Caller should reload the unicast and multicast addresses
 * after calling this.
 */
पूर्णांक t3_mac_set_num_ucast(काष्ठा cmac *mac, पूर्णांक n)
अणु
	अगर (n > EXACT_ADDR_FILTERS)
		वापस -EINVAL;
	mac->nucast = n;
	वापस 0;
पूर्ण

व्योम t3_mac_disable_exact_filters(काष्ठा cmac *mac)
अणु
	अचिन्हित पूर्णांक i, reg = mac->offset + A_XGM_RX_EXACT_MATCH_LOW_1;

	क्रम (i = 0; i < EXACT_ADDR_FILTERS; i++, reg += 8) अणु
		u32 v = t3_पढ़ो_reg(mac->adapter, reg);
		t3_ग_लिखो_reg(mac->adapter, reg, v);
	पूर्ण
	t3_पढ़ो_reg(mac->adapter, A_XGM_RX_EXACT_MATCH_LOW_1);	/* flush */
पूर्ण

व्योम t3_mac_enable_exact_filters(काष्ठा cmac *mac)
अणु
	अचिन्हित पूर्णांक i, reg = mac->offset + A_XGM_RX_EXACT_MATCH_HIGH_1;

	क्रम (i = 0; i < EXACT_ADDR_FILTERS; i++, reg += 8) अणु
		u32 v = t3_पढ़ो_reg(mac->adapter, reg);
		t3_ग_लिखो_reg(mac->adapter, reg, v);
	पूर्ण
	t3_पढ़ो_reg(mac->adapter, A_XGM_RX_EXACT_MATCH_LOW_1);	/* flush */
पूर्ण

/* Calculate the RX hash filter index of an Ethernet address */
अटल पूर्णांक hash_hw_addr(स्थिर u8 * addr)
अणु
	पूर्णांक hash = 0, octet, bit, i = 0, c;

	क्रम (octet = 0; octet < 6; ++octet)
		क्रम (c = addr[octet], bit = 0; bit < 8; c >>= 1, ++bit) अणु
			hash ^= (c & 1) << i;
			अगर (++i == 6)
				i = 0;
		पूर्ण
	वापस hash;
पूर्ण

पूर्णांक t3_mac_set_rx_mode(काष्ठा cmac *mac, काष्ठा net_device *dev)
अणु
	u32 val, hash_lo, hash_hi;
	काष्ठा adapter *adap = mac->adapter;
	अचिन्हित पूर्णांक oft = mac->offset;

	val = t3_पढ़ो_reg(adap, A_XGM_RX_CFG + oft) & ~F_COPYALLFRAMES;
	अगर (dev->flags & IFF_PROMISC)
		val |= F_COPYALLFRAMES;
	t3_ग_लिखो_reg(adap, A_XGM_RX_CFG + oft, val);

	अगर (dev->flags & IFF_ALLMULTI)
		hash_lo = hash_hi = 0xffffffff;
	अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक exact_addr_idx = mac->nucast;

		hash_lo = hash_hi = 0;
		netdev_क्रम_each_mc_addr(ha, dev)
			अगर (exact_addr_idx < EXACT_ADDR_FILTERS)
				set_addr_filter(mac, exact_addr_idx++,
						ha->addr);
			अन्यथा अणु
				पूर्णांक hash = hash_hw_addr(ha->addr);

				अगर (hash < 32)
					hash_lo |= (1 << hash);
				अन्यथा
					hash_hi |= (1 << (hash - 32));
			पूर्ण
	पूर्ण

	t3_ग_लिखो_reg(adap, A_XGM_RX_HASH_LOW + oft, hash_lo);
	t3_ग_लिखो_reg(adap, A_XGM_RX_HASH_HIGH + oft, hash_hi);
	वापस 0;
पूर्ण

अटल पूर्णांक rx_fअगरo_hwm(पूर्णांक mtu)
अणु
	पूर्णांक hwm;

	hwm = max(MAC_RXFIFO_SIZE - 3 * mtu, (MAC_RXFIFO_SIZE * 38) / 100);
	वापस min(hwm, MAC_RXFIFO_SIZE - 8192);
पूर्ण

पूर्णांक t3_mac_set_mtu(काष्ठा cmac *mac, अचिन्हित पूर्णांक mtu)
अणु
	पूर्णांक hwm, lwm, भागisor;
	पूर्णांक ipg;
	अचिन्हित पूर्णांक thres, v, reg;
	काष्ठा adapter *adap = mac->adapter;

	/*
	 * MAX_FRAME_SIZE inludes header + FCS, mtu करोesn't.  The HW max
	 * packet size रेजिस्टर includes header, but not FCS.
	 */
	mtu += 14;
	अगर (mtu > 1536)
		mtu += 4;

	अगर (mtu > MAX_FRAME_SIZE - 4)
		वापस -EINVAL;
	t3_ग_लिखो_reg(adap, A_XGM_RX_MAX_PKT_SIZE + mac->offset, mtu);

	अगर (adap->params.rev >= T3_REV_B2 &&
	    (t3_पढ़ो_reg(adap, A_XGM_RX_CTRL + mac->offset) & F_RXEN)) अणु
		t3_mac_disable_exact_filters(mac);
		v = t3_पढ़ो_reg(adap, A_XGM_RX_CFG + mac->offset);
		t3_set_reg_field(adap, A_XGM_RX_CFG + mac->offset,
				 F_ENHASHMCAST | F_COPYALLFRAMES, F_DISBCAST);

		reg = adap->params.rev == T3_REV_B2 ?
			A_XGM_RX_MAX_PKT_SIZE_ERR_CNT : A_XGM_RXFIFO_CFG;

		/* drain RX FIFO */
		अगर (t3_रुको_op_करोne(adap, reg + mac->offset,
				    F_RXFIFO_EMPTY, 1, 20, 5)) अणु
			t3_ग_लिखो_reg(adap, A_XGM_RX_CFG + mac->offset, v);
			t3_mac_enable_exact_filters(mac);
			वापस -EIO;
		पूर्ण
		t3_set_reg_field(adap, A_XGM_RX_MAX_PKT_SIZE + mac->offset,
				 V_RXMAXPKTSIZE(M_RXMAXPKTSIZE),
				 V_RXMAXPKTSIZE(mtu));
		t3_ग_लिखो_reg(adap, A_XGM_RX_CFG + mac->offset, v);
		t3_mac_enable_exact_filters(mac);
	पूर्ण अन्यथा
		t3_set_reg_field(adap, A_XGM_RX_MAX_PKT_SIZE + mac->offset,
				 V_RXMAXPKTSIZE(M_RXMAXPKTSIZE),
				 V_RXMAXPKTSIZE(mtu));

	/*
	 * Adjust the PAUSE frame watermarks.  We always set the LWM, and the
	 * HWM only अगर flow-control is enabled.
	 */
	hwm = rx_fअगरo_hwm(mtu);
	lwm = min(3 * (पूर्णांक)mtu, MAC_RXFIFO_SIZE / 4);
	v = t3_पढ़ो_reg(adap, A_XGM_RXFIFO_CFG + mac->offset);
	v &= ~V_RXFIFOPAUSELWM(M_RXFIFOPAUSELWM);
	v |= V_RXFIFOPAUSELWM(lwm / 8);
	अगर (G_RXFIFOPAUSEHWM(v))
		v = (v & ~V_RXFIFOPAUSEHWM(M_RXFIFOPAUSEHWM)) |
		    V_RXFIFOPAUSEHWM(hwm / 8);

	t3_ग_लिखो_reg(adap, A_XGM_RXFIFO_CFG + mac->offset, v);

	/* Adjust the TX FIFO threshold based on the MTU */
	thres = (adap->params.vpd.cclk * 1000) / 15625;
	thres = (thres * mtu) / 1000;
	अगर (is_10G(adap))
		thres /= 10;
	thres = mtu > thres ? (mtu - thres + 7) / 8 : 0;
	thres = max(thres, 8U);	/* need at least 8 */
	ipg = (adap->params.rev == T3_REV_C) ? 0 : 1;
	t3_set_reg_field(adap, A_XGM_TXFIFO_CFG + mac->offset,
			 V_TXFIFOTHRESH(M_TXFIFOTHRESH) | V_TXIPG(M_TXIPG),
			 V_TXFIFOTHRESH(thres) | V_TXIPG(ipg));

	अगर (adap->params.rev > 0) अणु
		भागisor = (adap->params.rev == T3_REV_C) ? 64 : 8;
		t3_ग_लिखो_reg(adap, A_XGM_PAUSE_TIMER + mac->offset,
			     (hwm - lwm) * 4 / भागisor);
	पूर्ण
	t3_ग_लिखो_reg(adap, A_XGM_TX_PAUSE_QUANTA + mac->offset,
		     MAC_RXFIFO_SIZE * 4 * 8 / 512);
	वापस 0;
पूर्ण

पूर्णांक t3_mac_set_speed_duplex_fc(काष्ठा cmac *mac, पूर्णांक speed, पूर्णांक duplex, पूर्णांक fc)
अणु
	u32 val;
	काष्ठा adapter *adap = mac->adapter;
	अचिन्हित पूर्णांक oft = mac->offset;

	अगर (duplex >= 0 && duplex != DUPLEX_FULL)
		वापस -EINVAL;
	अगर (speed >= 0) अणु
		अगर (speed == SPEED_10)
			val = V_PORTSPEED(0);
		अन्यथा अगर (speed == SPEED_100)
			val = V_PORTSPEED(1);
		अन्यथा अगर (speed == SPEED_1000)
			val = V_PORTSPEED(2);
		अन्यथा अगर (speed == SPEED_10000)
			val = V_PORTSPEED(3);
		अन्यथा
			वापस -EINVAL;

		t3_set_reg_field(adap, A_XGM_PORT_CFG + oft,
				 V_PORTSPEED(M_PORTSPEED), val);
	पूर्ण

	val = t3_पढ़ो_reg(adap, A_XGM_RXFIFO_CFG + oft);
	val &= ~V_RXFIFOPAUSEHWM(M_RXFIFOPAUSEHWM);
	अगर (fc & PAUSE_TX) अणु
		u32 rx_max_pkt_size =
		    G_RXMAXPKTSIZE(t3_पढ़ो_reg(adap,
					       A_XGM_RX_MAX_PKT_SIZE + oft));
		val |= V_RXFIFOPAUSEHWM(rx_fअगरo_hwm(rx_max_pkt_size) / 8);
	पूर्ण
	t3_ग_लिखो_reg(adap, A_XGM_RXFIFO_CFG + oft, val);

	t3_set_reg_field(adap, A_XGM_TX_CFG + oft, F_TXPAUSEEN,
			 (fc & PAUSE_RX) ? F_TXPAUSEEN : 0);
	वापस 0;
पूर्ण

पूर्णांक t3_mac_enable(काष्ठा cmac *mac, पूर्णांक which)
अणु
	पूर्णांक idx = macidx(mac);
	काष्ठा adapter *adap = mac->adapter;
	अचिन्हित पूर्णांक oft = mac->offset;
	काष्ठा mac_stats *s = &mac->stats;

	अगर (which & MAC_सूचीECTION_TX) अणु
		t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR, A_TP_TX_DROP_CFG_CH0 + idx);
		t3_ग_लिखो_reg(adap, A_TP_PIO_DATA,
			     adap->params.rev == T3_REV_C ?
			     0xc4ffff01 : 0xc0ede401);
		t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR, A_TP_TX_DROP_MODE);
		t3_set_reg_field(adap, A_TP_PIO_DATA, 1 << idx,
				 adap->params.rev == T3_REV_C ? 0 : 1 << idx);

		t3_ग_लिखो_reg(adap, A_XGM_TX_CTRL + oft, F_TXEN);

		t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR, A_TP_TX_DROP_CNT_CH0 + idx);
		mac->tx_mcnt = s->tx_frames;
		mac->tx_tcnt = (G_TXDROPCNTCH0RCVD(t3_पढ़ो_reg(adap,
							A_TP_PIO_DATA)));
		mac->tx_xcnt = (G_TXSPI4SOPCNT(t3_पढ़ो_reg(adap,
						A_XGM_TX_SPI4_SOP_EOP_CNT +
						oft)));
		mac->rx_mcnt = s->rx_frames;
		mac->rx_छोड़ो = s->rx_छोड़ो;
		mac->rx_xcnt = (G_TXSPI4SOPCNT(t3_पढ़ो_reg(adap,
						A_XGM_RX_SPI4_SOP_EOP_CNT +
						oft)));
		mac->rx_ocnt = s->rx_fअगरo_ovfl;
		mac->txen = F_TXEN;
		mac->toggle_cnt = 0;
	पूर्ण
	अगर (which & MAC_सूचीECTION_RX)
		t3_ग_लिखो_reg(adap, A_XGM_RX_CTRL + oft, F_RXEN);
	वापस 0;
पूर्ण

पूर्णांक t3_mac_disable(काष्ठा cmac *mac, पूर्णांक which)
अणु
	काष्ठा adapter *adap = mac->adapter;

	अगर (which & MAC_सूचीECTION_TX) अणु
		t3_ग_लिखो_reg(adap, A_XGM_TX_CTRL + mac->offset, 0);
		mac->txen = 0;
	पूर्ण
	अगर (which & MAC_सूचीECTION_RX) अणु
		पूर्णांक val = F_MAC_RESET_;

		t3_set_reg_field(mac->adapter, A_XGM_RESET_CTRL + mac->offset,
				 F_PCS_RESET_, 0);
		msleep(100);
		t3_ग_लिखो_reg(adap, A_XGM_RX_CTRL + mac->offset, 0);
		अगर (is_10G(adap))
			val |= F_PCS_RESET_;
		अन्यथा अगर (uses_xaui(adap))
			val |= F_PCS_RESET_ | F_XG2G_RESET_;
		अन्यथा
			val |= F_RGMII_RESET_ | F_XG2G_RESET_;
		t3_ग_लिखो_reg(mac->adapter, A_XGM_RESET_CTRL + mac->offset, val);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक t3b2_mac_watchकरोg_task(काष्ठा cmac *mac)
अणु
	काष्ठा adapter *adap = mac->adapter;
	काष्ठा mac_stats *s = &mac->stats;
	अचिन्हित पूर्णांक tx_tcnt, tx_xcnt;
	u64 tx_mcnt = s->tx_frames;
	पूर्णांक status;

	status = 0;
	tx_xcnt = 1;		/* By शेष tx_xcnt is making progress */
	tx_tcnt = mac->tx_tcnt;	/* If tx_mcnt is progressing ignore tx_tcnt */
	अगर (tx_mcnt == mac->tx_mcnt && mac->rx_छोड़ो == s->rx_छोड़ो) अणु
		tx_xcnt = (G_TXSPI4SOPCNT(t3_पढ़ो_reg(adap,
						A_XGM_TX_SPI4_SOP_EOP_CNT +
					       	mac->offset)));
		अगर (tx_xcnt == 0) अणु
			t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR,
				     A_TP_TX_DROP_CNT_CH0 + macidx(mac));
			tx_tcnt = (G_TXDROPCNTCH0RCVD(t3_पढ़ो_reg(adap,
						      A_TP_PIO_DATA)));
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		mac->toggle_cnt = 0;
		जाओ out;
	पूर्ण

	अगर ((tx_tcnt != mac->tx_tcnt) && (mac->tx_xcnt == 0)) अणु
		अगर (mac->toggle_cnt > 4) अणु
			status = 2;
			जाओ out;
		पूर्ण अन्यथा अणु
			status = 1;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		mac->toggle_cnt = 0;
		जाओ out;
	पूर्ण

out:
	mac->tx_tcnt = tx_tcnt;
	mac->tx_xcnt = tx_xcnt;
	mac->tx_mcnt = s->tx_frames;
	mac->rx_छोड़ो = s->rx_छोड़ो;
	अगर (status == 1) अणु
		t3_ग_लिखो_reg(adap, A_XGM_TX_CTRL + mac->offset, 0);
		t3_पढ़ो_reg(adap, A_XGM_TX_CTRL + mac->offset);  /* flush */
		t3_ग_लिखो_reg(adap, A_XGM_TX_CTRL + mac->offset, mac->txen);
		t3_पढ़ो_reg(adap, A_XGM_TX_CTRL + mac->offset);  /* flush */
		mac->toggle_cnt++;
	पूर्ण अन्यथा अगर (status == 2) अणु
		t3b2_mac_reset(mac);
		mac->toggle_cnt = 0;
	पूर्ण
	वापस status;
पूर्ण

/*
 * This function is called periodically to accumulate the current values of the
 * RMON counters पूर्णांकo the port statistics.  Since the packet counters are only
 * 32 bits they can overflow in ~286 secs at 10G, so the function should be
 * called more frequently than that.  The byte counters are 45-bit wide, they
 * would overflow in ~7.8 hours.
 */
स्थिर काष्ठा mac_stats *t3_mac_update_stats(काष्ठा cmac *mac)
अणु
#घोषणा RMON_READ(mac, addr) t3_पढ़ो_reg(mac->adapter, addr + mac->offset)
#घोषणा RMON_UPDATE(mac, name, reg) \
	(mac)->stats.name += (u64)RMON_READ(mac, A_XGM_STAT_##reg)
#घोषणा RMON_UPDATE64(mac, name, reg_lo, reg_hi) \
	(mac)->stats.name += RMON_READ(mac, A_XGM_STAT_##reg_lo) + \
			     ((u64)RMON_READ(mac, A_XGM_STAT_##reg_hi) << 32)

	u32 v, lo;

	RMON_UPDATE64(mac, rx_octets, RX_BYTES_LOW, RX_BYTES_HIGH);
	RMON_UPDATE64(mac, rx_frames, RX_FRAMES_LOW, RX_FRAMES_HIGH);
	RMON_UPDATE(mac, rx_mcast_frames, RX_MCAST_FRAMES);
	RMON_UPDATE(mac, rx_bcast_frames, RX_BCAST_FRAMES);
	RMON_UPDATE(mac, rx_fcs_errs, RX_CRC_ERR_FRAMES);
	RMON_UPDATE(mac, rx_छोड़ो, RX_PAUSE_FRAMES);
	RMON_UPDATE(mac, rx_jabber, RX_JABBER_FRAMES);
	RMON_UPDATE(mac, rx_लघु, RX_SHORT_FRAMES);
	RMON_UPDATE(mac, rx_symbol_errs, RX_SYM_CODE_ERR_FRAMES);

	RMON_UPDATE(mac, rx_too_दीर्घ, RX_OVERSIZE_FRAMES);

	v = RMON_READ(mac, A_XGM_RX_MAX_PKT_SIZE_ERR_CNT);
	अगर (mac->adapter->params.rev == T3_REV_B2)
		v &= 0x7fffffff;
	mac->stats.rx_too_दीर्घ += v;

	RMON_UPDATE(mac, rx_frames_64, RX_64B_FRAMES);
	RMON_UPDATE(mac, rx_frames_65_127, RX_65_127B_FRAMES);
	RMON_UPDATE(mac, rx_frames_128_255, RX_128_255B_FRAMES);
	RMON_UPDATE(mac, rx_frames_256_511, RX_256_511B_FRAMES);
	RMON_UPDATE(mac, rx_frames_512_1023, RX_512_1023B_FRAMES);
	RMON_UPDATE(mac, rx_frames_1024_1518, RX_1024_1518B_FRAMES);
	RMON_UPDATE(mac, rx_frames_1519_max, RX_1519_MAXB_FRAMES);

	RMON_UPDATE64(mac, tx_octets, TX_BYTE_LOW, TX_BYTE_HIGH);
	RMON_UPDATE64(mac, tx_frames, TX_FRAME_LOW, TX_FRAME_HIGH);
	RMON_UPDATE(mac, tx_mcast_frames, TX_MCAST);
	RMON_UPDATE(mac, tx_bcast_frames, TX_BCAST);
	RMON_UPDATE(mac, tx_छोड़ो, TX_PAUSE);
	/* This counts error frames in general (bad FCS, underrun, etc). */
	RMON_UPDATE(mac, tx_underrun, TX_ERR_FRAMES);

	RMON_UPDATE(mac, tx_frames_64, TX_64B_FRAMES);
	RMON_UPDATE(mac, tx_frames_65_127, TX_65_127B_FRAMES);
	RMON_UPDATE(mac, tx_frames_128_255, TX_128_255B_FRAMES);
	RMON_UPDATE(mac, tx_frames_256_511, TX_256_511B_FRAMES);
	RMON_UPDATE(mac, tx_frames_512_1023, TX_512_1023B_FRAMES);
	RMON_UPDATE(mac, tx_frames_1024_1518, TX_1024_1518B_FRAMES);
	RMON_UPDATE(mac, tx_frames_1519_max, TX_1519_MAXB_FRAMES);

	/* The next stat isn't clear-on-पढ़ो. */
	t3_ग_लिखो_reg(mac->adapter, A_TP_MIB_INDEX, mac->offset ? 51 : 50);
	v = t3_पढ़ो_reg(mac->adapter, A_TP_MIB_RDATA);
	lo = (u32) mac->stats.rx_cong_drops;
	mac->stats.rx_cong_drops += (u64) (v - lo);

	वापस &mac->stats;
पूर्ण
