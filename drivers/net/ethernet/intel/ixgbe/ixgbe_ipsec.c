<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 Oracle and/or its affiliates. All rights reserved. */

#समावेश "ixgbe.h"
#समावेश <net/xfrm.h>
#समावेश <crypto/aead.h>
#समावेश <linux/अगर_bridge.h>

#घोषणा IXGBE_IPSEC_KEY_BITS  160
अटल स्थिर अक्षर aes_gcm_name[] = "rfc4106(gcm(aes))";

अटल व्योम ixgbe_ipsec_del_sa(काष्ठा xfrm_state *xs);

/**
 * ixgbe_ipsec_set_tx_sa - set the Tx SA रेजिस्टरs
 * @hw: hw specअगरic details
 * @idx: रेजिस्टर index to ग_लिखो
 * @key: key byte array
 * @salt: salt bytes
 **/
अटल व्योम ixgbe_ipsec_set_tx_sa(काष्ठा ixgbe_hw *hw, u16 idx,
				  u32 key[], u32 salt)
अणु
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		IXGBE_WRITE_REG(hw, IXGBE_IPSTXKEY(i),
				(__क्रमce u32)cpu_to_be32(key[3 - i]));
	IXGBE_WRITE_REG(hw, IXGBE_IPSTXSALT, (__क्रमce u32)cpu_to_be32(salt));
	IXGBE_WRITE_FLUSH(hw);

	reg = IXGBE_READ_REG(hw, IXGBE_IPSTXIDX);
	reg &= IXGBE_RXTXIDX_IPS_EN;
	reg |= idx << IXGBE_RXTXIDX_IDX_SHIFT | IXGBE_RXTXIDX_WRITE;
	IXGBE_WRITE_REG(hw, IXGBE_IPSTXIDX, reg);
	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_ipsec_set_rx_item - set an Rx table item
 * @hw: hw specअगरic details
 * @idx: रेजिस्टर index to ग_लिखो
 * @tbl: table selector
 *
 * Trigger the device to store पूर्णांकo a particular Rx table the
 * data that has alपढ़ोy been loaded पूर्णांकo the input रेजिस्टर
 **/
अटल व्योम ixgbe_ipsec_set_rx_item(काष्ठा ixgbe_hw *hw, u16 idx,
				    क्रमागत ixgbe_ipsec_tbl_sel tbl)
अणु
	u32 reg;

	reg = IXGBE_READ_REG(hw, IXGBE_IPSRXIDX);
	reg &= IXGBE_RXTXIDX_IPS_EN;
	reg |= tbl << IXGBE_RXIDX_TBL_SHIFT |
	       idx << IXGBE_RXTXIDX_IDX_SHIFT |
	       IXGBE_RXTXIDX_WRITE;
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIDX, reg);
	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_ipsec_set_rx_sa - set up the रेजिस्टर bits to save SA info
 * @hw: hw specअगरic details
 * @idx: रेजिस्टर index to ग_लिखो
 * @spi: security parameter index
 * @key: key byte array
 * @salt: salt bytes
 * @mode: rx decrypt control bits
 * @ip_idx: index पूर्णांकo IP table क्रम related IP address
 **/
अटल व्योम ixgbe_ipsec_set_rx_sa(काष्ठा ixgbe_hw *hw, u16 idx, __be32 spi,
				  u32 key[], u32 salt, u32 mode, u32 ip_idx)
अणु
	पूर्णांक i;

	/* store the SPI (in bigendian) and IPidx */
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXSPI,
			(__क्रमce u32)cpu_to_le32((__क्रमce u32)spi));
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIPIDX, ip_idx);
	IXGBE_WRITE_FLUSH(hw);

	ixgbe_ipsec_set_rx_item(hw, idx, ips_rx_spi_tbl);

	/* store the key, salt, and mode */
	क्रम (i = 0; i < 4; i++)
		IXGBE_WRITE_REG(hw, IXGBE_IPSRXKEY(i),
				(__क्रमce u32)cpu_to_be32(key[3 - i]));
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXSALT, (__क्रमce u32)cpu_to_be32(salt));
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXMOD, mode);
	IXGBE_WRITE_FLUSH(hw);

	ixgbe_ipsec_set_rx_item(hw, idx, ips_rx_key_tbl);
पूर्ण

/**
 * ixgbe_ipsec_set_rx_ip - set up the रेजिस्टर bits to save SA IP addr info
 * @hw: hw specअगरic details
 * @idx: रेजिस्टर index to ग_लिखो
 * @addr: IP address byte array
 **/
अटल व्योम ixgbe_ipsec_set_rx_ip(काष्ठा ixgbe_hw *hw, u16 idx, __be32 addr[])
अणु
	पूर्णांक i;

	/* store the ip address */
	क्रम (i = 0; i < 4; i++)
		IXGBE_WRITE_REG(hw, IXGBE_IPSRXIPADDR(i),
				(__क्रमce u32)cpu_to_le32((__क्रमce u32)addr[i]));
	IXGBE_WRITE_FLUSH(hw);

	ixgbe_ipsec_set_rx_item(hw, idx, ips_rx_ip_tbl);
पूर्ण

/**
 * ixgbe_ipsec_clear_hw_tables - because some tables करोn't get cleared on reset
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbe_ipsec_clear_hw_tables(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 buf[4] = अणु0, 0, 0, 0पूर्ण;
	u16 idx;

	/* disable Rx and Tx SA lookup */
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIDX, 0);
	IXGBE_WRITE_REG(hw, IXGBE_IPSTXIDX, 0);

	/* scrub the tables - split the loops क्रम the max of the IP table */
	क्रम (idx = 0; idx < IXGBE_IPSEC_MAX_RX_IP_COUNT; idx++) अणु
		ixgbe_ipsec_set_tx_sa(hw, idx, buf, 0);
		ixgbe_ipsec_set_rx_sa(hw, idx, 0, buf, 0, 0, 0);
		ixgbe_ipsec_set_rx_ip(hw, idx, (__be32 *)buf);
	पूर्ण
	क्रम (; idx < IXGBE_IPSEC_MAX_SA_COUNT; idx++) अणु
		ixgbe_ipsec_set_tx_sa(hw, idx, buf, 0);
		ixgbe_ipsec_set_rx_sa(hw, idx, 0, buf, 0, 0, 0);
	पूर्ण
पूर्ण

/**
 * ixgbe_ipsec_stop_data
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbe_ipsec_stop_data(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	bool link = adapter->link_up;
	u32 t_rdy, r_rdy;
	u32 limit;
	u32 reg;

	/* halt data paths */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXCTRL);
	reg |= IXGBE_SECTXCTRL_TX_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXCTRL, reg);

	reg = IXGBE_READ_REG(hw, IXGBE_SECRXCTRL);
	reg |= IXGBE_SECRXCTRL_RX_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, reg);

	/* If both Tx and Rx are पढ़ोy there are no packets
	 * that we need to flush so the loopback configuration
	 * below is not necessary.
	 */
	t_rdy = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT) &
		IXGBE_SECTXSTAT_SECTX_RDY;
	r_rdy = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT) &
		IXGBE_SECRXSTAT_SECRX_RDY;
	अगर (t_rdy && r_rdy)
		वापस;

	/* If the tx fअगरo करोesn't have link, but still has data,
	 * we can't clear the tx sec block.  Set the MAC loopback
	 * beक्रमe block clear
	 */
	अगर (!link) अणु
		reg = IXGBE_READ_REG(hw, IXGBE_MACC);
		reg |= IXGBE_MACC_FLU;
		IXGBE_WRITE_REG(hw, IXGBE_MACC, reg);

		reg = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		reg |= IXGBE_HLREG0_LPBK;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, reg);

		IXGBE_WRITE_FLUSH(hw);
		mdelay(3);
	पूर्ण

	/* रुको क्रम the paths to empty */
	limit = 20;
	करो अणु
		mdelay(10);
		t_rdy = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT) &
			IXGBE_SECTXSTAT_SECTX_RDY;
		r_rdy = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT) &
			IXGBE_SECRXSTAT_SECRX_RDY;
	पूर्ण जबतक (!(t_rdy && r_rdy) && limit--);

	/* unकरो loopback अगर we played with it earlier */
	अगर (!link) अणु
		reg = IXGBE_READ_REG(hw, IXGBE_MACC);
		reg &= ~IXGBE_MACC_FLU;
		IXGBE_WRITE_REG(hw, IXGBE_MACC, reg);

		reg = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		reg &= ~IXGBE_HLREG0_LPBK;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, reg);

		IXGBE_WRITE_FLUSH(hw);
	पूर्ण
पूर्ण

/**
 * ixgbe_ipsec_stop_engine
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbe_ipsec_stop_engine(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 reg;

	ixgbe_ipsec_stop_data(adapter);

	/* disable Rx and Tx SA lookup */
	IXGBE_WRITE_REG(hw, IXGBE_IPSTXIDX, 0);
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIDX, 0);

	/* disable the Rx and Tx engines and full packet store-n-क्रमward */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXCTRL);
	reg |= IXGBE_SECTXCTRL_SECTX_DIS;
	reg &= ~IXGBE_SECTXCTRL_STORE_FORWARD;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXCTRL, reg);

	reg = IXGBE_READ_REG(hw, IXGBE_SECRXCTRL);
	reg |= IXGBE_SECRXCTRL_SECRX_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, reg);

	/* restore the "tx security buffer almost full threshold" to 0x250 */
	IXGBE_WRITE_REG(hw, IXGBE_SECTXBUFFAF, 0x250);

	/* Set minimum IFG between packets back to the शेष 0x1 */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
	reg = (reg & 0xfffffff0) | 0x1;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXMINIFG, reg);

	/* final set क्रम normal (no ipsec offload) processing */
	IXGBE_WRITE_REG(hw, IXGBE_SECTXCTRL, IXGBE_SECTXCTRL_SECTX_DIS);
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, IXGBE_SECRXCTRL_SECRX_DIS);

	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_ipsec_start_engine
 * @adapter: board निजी काष्ठाure
 *
 * NOTE: this increases घातer consumption whether being used or not
 **/
अटल व्योम ixgbe_ipsec_start_engine(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 reg;

	ixgbe_ipsec_stop_data(adapter);

	/* Set minimum IFG between packets to 3 */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
	reg = (reg & 0xfffffff0) | 0x3;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXMINIFG, reg);

	/* Set "tx security buffer almost full threshold" to 0x15 so that the
	 * almost full indication is generated only after buffer contains at
	 * least an entire jumbo packet.
	 */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXBUFFAF);
	reg = (reg & 0xfffffc00) | 0x15;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXBUFFAF, reg);

	/* restart the data paths by clearing the DISABLE bits */
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, 0);
	IXGBE_WRITE_REG(hw, IXGBE_SECTXCTRL, IXGBE_SECTXCTRL_STORE_FORWARD);

	/* enable Rx and Tx SA lookup */
	IXGBE_WRITE_REG(hw, IXGBE_IPSTXIDX, IXGBE_RXTXIDX_IPS_EN);
	IXGBE_WRITE_REG(hw, IXGBE_IPSRXIDX, IXGBE_RXTXIDX_IPS_EN);

	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_ipsec_restore - restore the ipsec HW settings after a reset
 * @adapter: board निजी काष्ठाure
 *
 * Reload the HW tables from the SW tables after they've been bashed
 * by a chip reset.
 *
 * Any VF entries are हटाओd from the SW and HW tables since either
 * (a) the VF also माला_लो reset on PF reset and will ask again क्रम the
 * offloads, or (b) the VF has been हटाओd by a change in the num_vfs.
 **/
व्योम ixgbe_ipsec_restore(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	अगर (!(adapter->flags2 & IXGBE_FLAG2_IPSEC_ENABLED))
		वापस;

	/* clean up and restart the engine */
	ixgbe_ipsec_stop_engine(adapter);
	ixgbe_ipsec_clear_hw_tables(adapter);
	ixgbe_ipsec_start_engine(adapter);

	/* reload the Rx and Tx keys */
	क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) अणु
		काष्ठा rx_sa *r = &ipsec->rx_tbl[i];
		काष्ठा tx_sa *t = &ipsec->tx_tbl[i];

		अगर (r->used) अणु
			अगर (r->mode & IXGBE_RXTXMOD_VF)
				ixgbe_ipsec_del_sa(r->xs);
			अन्यथा
				ixgbe_ipsec_set_rx_sa(hw, i, r->xs->id.spi,
						      r->key, r->salt,
						      r->mode, r->iptbl_ind);
		पूर्ण

		अगर (t->used) अणु
			अगर (t->mode & IXGBE_RXTXMOD_VF)
				ixgbe_ipsec_del_sa(t->xs);
			अन्यथा
				ixgbe_ipsec_set_tx_sa(hw, i, t->key, t->salt);
		पूर्ण
	पूर्ण

	/* reload the IP addrs */
	क्रम (i = 0; i < IXGBE_IPSEC_MAX_RX_IP_COUNT; i++) अणु
		काष्ठा rx_ip_sa *ipsa = &ipsec->ip_tbl[i];

		अगर (ipsa->used)
			ixgbe_ipsec_set_rx_ip(hw, i, ipsa->ipaddr);
	पूर्ण
पूर्ण

/**
 * ixgbe_ipsec_find_empty_idx - find the first unused security parameter index
 * @ipsec: poपूर्णांकer to ipsec काष्ठा
 * @rxtable: true अगर we need to look in the Rx table
 *
 * Returns the first unused index in either the Rx or Tx SA table
 **/
अटल पूर्णांक ixgbe_ipsec_find_empty_idx(काष्ठा ixgbe_ipsec *ipsec, bool rxtable)
अणु
	u32 i;

	अगर (rxtable) अणु
		अगर (ipsec->num_rx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			वापस -ENOSPC;

		/* search rx sa table */
		क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) अणु
			अगर (!ipsec->rx_tbl[i].used)
				वापस i;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ipsec->num_tx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			वापस -ENOSPC;

		/* search tx sa table */
		क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) अणु
			अगर (!ipsec->tx_tbl[i].used)
				वापस i;
		पूर्ण
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/**
 * ixgbe_ipsec_find_rx_state - find the state that matches
 * @ipsec: poपूर्णांकer to ipsec काष्ठा
 * @daddr: inbound address to match
 * @proto: protocol to match
 * @spi: SPI to match
 * @ip4: true अगर using an ipv4 address
 *
 * Returns a poपूर्णांकer to the matching SA state inक्रमmation
 **/
अटल काष्ठा xfrm_state *ixgbe_ipsec_find_rx_state(काष्ठा ixgbe_ipsec *ipsec,
						    __be32 *daddr, u8 proto,
						    __be32 spi, bool ip4)
अणु
	काष्ठा rx_sa *rsa;
	काष्ठा xfrm_state *ret = शून्य;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu(ipsec->rx_sa_list, rsa, hlist,
				   (__क्रमce u32)spi) अणु
		अगर (rsa->mode & IXGBE_RXTXMOD_VF)
			जारी;
		अगर (spi == rsa->xs->id.spi &&
		    ((ip4 && *daddr == rsa->xs->id.daddr.a4) ||
		      (!ip4 && !स_भेद(daddr, &rsa->xs->id.daddr.a6,
				       माप(rsa->xs->id.daddr.a6)))) &&
		    proto == rsa->xs->id.proto) अणु
			ret = rsa->xs;
			xfrm_state_hold(ret);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * ixgbe_ipsec_parse_proto_keys - find the key and salt based on the protocol
 * @xs: poपूर्णांकer to xfrm_state काष्ठा
 * @mykey: poपूर्णांकer to key array to populate
 * @mysalt: poपूर्णांकer to salt value to populate
 *
 * This copies the protocol keys and salt to our own data tables.  The
 * 82599 family only supports the one algorithm.
 **/
अटल पूर्णांक ixgbe_ipsec_parse_proto_keys(काष्ठा xfrm_state *xs,
					u32 *mykey, u32 *mysalt)
अणु
	काष्ठा net_device *dev = xs->xso.real_dev;
	अचिन्हित अक्षर *key_data;
	अक्षर *alg_name = शून्य;
	पूर्णांक key_len;

	अगर (!xs->aead) अणु
		netdev_err(dev, "Unsupported IPsec algorithm\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xs->aead->alg_icv_len != IXGBE_IPSEC_AUTH_BITS) अणु
		netdev_err(dev, "IPsec offload requires %d bit authentication\n",
			   IXGBE_IPSEC_AUTH_BITS);
		वापस -EINVAL;
	पूर्ण

	key_data = &xs->aead->alg_key[0];
	key_len = xs->aead->alg_key_len;
	alg_name = xs->aead->alg_name;

	अगर (म_भेद(alg_name, aes_gcm_name)) अणु
		netdev_err(dev, "Unsupported IPsec algorithm - please use %s\n",
			   aes_gcm_name);
		वापस -EINVAL;
	पूर्ण

	/* The key bytes come करोwn in a bigendian array of bytes, so
	 * we करोn't need to करो any byteswapping.
	 * 160 accounts क्रम 16 byte key and 4 byte salt
	 */
	अगर (key_len == IXGBE_IPSEC_KEY_BITS) अणु
		*mysalt = ((u32 *)key_data)[4];
	पूर्ण अन्यथा अगर (key_len != (IXGBE_IPSEC_KEY_BITS - (माप(*mysalt) * 8))) अणु
		netdev_err(dev, "IPsec hw offload only supports keys up to 128 bits with a 32 bit salt\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		netdev_info(dev, "IPsec hw offload parameters missing 32 bit salt value\n");
		*mysalt = 0;
	पूर्ण
	स_नकल(mykey, key_data, 16);

	वापस 0;
पूर्ण

/**
 * ixgbe_ipsec_check_mgmt_ip - make sure there is no clash with mgmt IP filters
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल पूर्णांक ixgbe_ipsec_check_mgmt_ip(काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *dev = xs->xso.real_dev;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 mfval, manc, reg;
	पूर्णांक num_filters = 4;
	bool manc_ipv4;
	u32 bmcipval;
	पूर्णांक i, j;

#घोषणा MANC_EN_IPV4_FILTER      BIT(24)
#घोषणा MFVAL_IPV4_FILTER_SHIFT  16
#घोषणा MFVAL_IPV6_FILTER_SHIFT  24
#घोषणा MIPAF_ARR(_m, _n)        (IXGBE_MIPAF + ((_m) * 0x10) + ((_n) * 4))

#घोषणा IXGBE_BMCIP(_n)          (0x5050 + ((_n) * 4))
#घोषणा IXGBE_BMCIPVAL           0x5060
#घोषणा BMCIP_V4                 0x2
#घोषणा BMCIP_V6                 0x3
#घोषणा BMCIP_MASK               0x3

	manc = IXGBE_READ_REG(hw, IXGBE_MANC);
	manc_ipv4 = !!(manc & MANC_EN_IPV4_FILTER);
	mfval = IXGBE_READ_REG(hw, IXGBE_MFVAL);
	bmcipval = IXGBE_READ_REG(hw, IXGBE_BMCIPVAL);

	अगर (xs->props.family == AF_INET) अणु
		/* are there any IPv4 filters to check? */
		अगर (manc_ipv4) अणु
			/* the 4 ipv4 filters are all in MIPAF(3, i) */
			क्रम (i = 0; i < num_filters; i++) अणु
				अगर (!(mfval & BIT(MFVAL_IPV4_FILTER_SHIFT + i)))
					जारी;

				reg = IXGBE_READ_REG(hw, MIPAF_ARR(3, i));
				अगर (reg == xs->id.daddr.a4)
					वापस 1;
			पूर्ण
		पूर्ण

		अगर ((bmcipval & BMCIP_MASK) == BMCIP_V4) अणु
			reg = IXGBE_READ_REG(hw, IXGBE_BMCIP(3));
			अगर (reg == xs->id.daddr.a4)
				वापस 1;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* अगर there are ipv4 filters, they are in the last ipv6 slot */
		अगर (manc_ipv4)
			num_filters = 3;

		क्रम (i = 0; i < num_filters; i++) अणु
			अगर (!(mfval & BIT(MFVAL_IPV6_FILTER_SHIFT + i)))
				जारी;

			क्रम (j = 0; j < 4; j++) अणु
				reg = IXGBE_READ_REG(hw, MIPAF_ARR(i, j));
				अगर (reg != xs->id.daddr.a6[j])
					अवरोध;
			पूर्ण
			अगर (j == 4)   /* did we match all 4 words? */
				वापस 1;
		पूर्ण

		अगर ((bmcipval & BMCIP_MASK) == BMCIP_V6) अणु
			क्रम (j = 0; j < 4; j++) अणु
				reg = IXGBE_READ_REG(hw, IXGBE_BMCIP(j));
				अगर (reg != xs->id.daddr.a6[j])
					अवरोध;
			पूर्ण
			अगर (j == 4)   /* did we match all 4 words? */
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_ipsec_add_sa - program device with a security association
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल पूर्णांक ixgbe_ipsec_add_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *dev = xs->xso.real_dev;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक checked, match, first;
	u16 sa_idx;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (xs->id.proto != IPPROTO_ESP && xs->id.proto != IPPROTO_AH) अणु
		netdev_err(dev, "Unsupported protocol 0x%04x for ipsec offload\n",
			   xs->id.proto);
		वापस -EINVAL;
	पूर्ण

	अगर (xs->props.mode != XFRM_MODE_TRANSPORT) अणु
		netdev_err(dev, "Unsupported mode for ipsec offload\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ixgbe_ipsec_check_mgmt_ip(xs)) अणु
		netdev_err(dev, "IPsec IP addr clash with mgmt filters\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xs->xso.flags & XFRM_OFFLOAD_INBOUND) अणु
		काष्ठा rx_sa rsa;

		अगर (xs->calg) अणु
			netdev_err(dev, "Compression offload not supported\n");
			वापस -EINVAL;
		पूर्ण

		/* find the first unused index */
		ret = ixgbe_ipsec_find_empty_idx(ipsec, true);
		अगर (ret < 0) अणु
			netdev_err(dev, "No space for SA in Rx table!\n");
			वापस ret;
		पूर्ण
		sa_idx = (u16)ret;

		स_रखो(&rsa, 0, माप(rsa));
		rsa.used = true;
		rsa.xs = xs;

		अगर (rsa.xs->id.proto & IPPROTO_ESP)
			rsa.decrypt = xs->ealg || xs->aead;

		/* get the key and salt */
		ret = ixgbe_ipsec_parse_proto_keys(xs, rsa.key, &rsa.salt);
		अगर (ret) अणु
			netdev_err(dev, "Failed to get key data for Rx SA table\n");
			वापस ret;
		पूर्ण

		/* get ip क्रम rx sa table */
		अगर (xs->props.family == AF_INET6)
			स_नकल(rsa.ipaddr, &xs->id.daddr.a6, 16);
		अन्यथा
			स_नकल(&rsa.ipaddr[3], &xs->id.daddr.a4, 4);

		/* The HW करोes not have a 1:1 mapping from keys to IP addrs, so
		 * check क्रम a matching IP addr entry in the table.  If the addr
		 * alपढ़ोy exists, use it; अन्यथा find an unused slot and add the
		 * addr.  If one करोes not exist and there are no unused table
		 * entries, fail the request.
		 */

		/* Find an existing match or first not used, and stop looking
		 * after we've checked all we know we have.
		 */
		checked = 0;
		match = -1;
		first = -1;
		क्रम (i = 0;
		     i < IXGBE_IPSEC_MAX_RX_IP_COUNT &&
		     (checked < ipsec->num_rx_sa || first < 0);
		     i++) अणु
			अगर (ipsec->ip_tbl[i].used) अणु
				अगर (!स_भेद(ipsec->ip_tbl[i].ipaddr,
					    rsa.ipaddr, माप(rsa.ipaddr))) अणु
					match = i;
					अवरोध;
				पूर्ण
				checked++;
			पूर्ण अन्यथा अगर (first < 0) अणु
				first = i;  /* track the first empty seen */
			पूर्ण
		पूर्ण

		अगर (ipsec->num_rx_sa == 0)
			first = 0;

		अगर (match >= 0) अणु
			/* addrs are the same, we should use this one */
			rsa.iptbl_ind = match;
			ipsec->ip_tbl[match].ref_cnt++;

		पूर्ण अन्यथा अगर (first >= 0) अणु
			/* no matches, but here's an empty slot */
			rsa.iptbl_ind = first;

			स_नकल(ipsec->ip_tbl[first].ipaddr,
			       rsa.ipaddr, माप(rsa.ipaddr));
			ipsec->ip_tbl[first].ref_cnt = 1;
			ipsec->ip_tbl[first].used = true;

			ixgbe_ipsec_set_rx_ip(hw, rsa.iptbl_ind, rsa.ipaddr);

		पूर्ण अन्यथा अणु
			/* no match and no empty slot */
			netdev_err(dev, "No space for SA in Rx IP SA table\n");
			स_रखो(&rsa, 0, माप(rsa));
			वापस -ENOSPC;
		पूर्ण

		rsa.mode = IXGBE_RXMOD_VALID;
		अगर (rsa.xs->id.proto & IPPROTO_ESP)
			rsa.mode |= IXGBE_RXMOD_PROTO_ESP;
		अगर (rsa.decrypt)
			rsa.mode |= IXGBE_RXMOD_DECRYPT;
		अगर (rsa.xs->props.family == AF_INET6)
			rsa.mode |= IXGBE_RXMOD_IPV6;

		/* the preparations worked, so save the info */
		स_नकल(&ipsec->rx_tbl[sa_idx], &rsa, माप(rsa));

		ixgbe_ipsec_set_rx_sa(hw, sa_idx, rsa.xs->id.spi, rsa.key,
				      rsa.salt, rsa.mode, rsa.iptbl_ind);
		xs->xso.offload_handle = sa_idx + IXGBE_IPSEC_BASE_RX_INDEX;

		ipsec->num_rx_sa++;

		/* hash the new entry क्रम faster search in Rx path */
		hash_add_rcu(ipsec->rx_sa_list, &ipsec->rx_tbl[sa_idx].hlist,
			     (__क्रमce u32)rsa.xs->id.spi);
	पूर्ण अन्यथा अणु
		काष्ठा tx_sa tsa;

		अगर (adapter->num_vfs &&
		    adapter->bridge_mode != BRIDGE_MODE_VEPA)
			वापस -EOPNOTSUPP;

		/* find the first unused index */
		ret = ixgbe_ipsec_find_empty_idx(ipsec, false);
		अगर (ret < 0) अणु
			netdev_err(dev, "No space for SA in Tx table\n");
			वापस ret;
		पूर्ण
		sa_idx = (u16)ret;

		स_रखो(&tsa, 0, माप(tsa));
		tsa.used = true;
		tsa.xs = xs;

		अगर (xs->id.proto & IPPROTO_ESP)
			tsa.encrypt = xs->ealg || xs->aead;

		ret = ixgbe_ipsec_parse_proto_keys(xs, tsa.key, &tsa.salt);
		अगर (ret) अणु
			netdev_err(dev, "Failed to get key data for Tx SA table\n");
			स_रखो(&tsa, 0, माप(tsa));
			वापस ret;
		पूर्ण

		/* the preparations worked, so save the info */
		स_नकल(&ipsec->tx_tbl[sa_idx], &tsa, माप(tsa));

		ixgbe_ipsec_set_tx_sa(hw, sa_idx, tsa.key, tsa.salt);

		xs->xso.offload_handle = sa_idx + IXGBE_IPSEC_BASE_TX_INDEX;

		ipsec->num_tx_sa++;
	पूर्ण

	/* enable the engine अगर not alपढ़ोy warmed up */
	अगर (!(adapter->flags2 & IXGBE_FLAG2_IPSEC_ENABLED)) अणु
		ixgbe_ipsec_start_engine(adapter);
		adapter->flags2 |= IXGBE_FLAG2_IPSEC_ENABLED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_ipsec_del_sa - clear out this specअगरic SA
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल व्योम ixgbe_ipsec_del_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *dev = xs->xso.real_dev;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 zerobuf[4] = अणु0, 0, 0, 0पूर्ण;
	u16 sa_idx;

	अगर (xs->xso.flags & XFRM_OFFLOAD_INBOUND) अणु
		काष्ठा rx_sa *rsa;
		u8 ipi;

		sa_idx = xs->xso.offload_handle - IXGBE_IPSEC_BASE_RX_INDEX;
		rsa = &ipsec->rx_tbl[sa_idx];

		अगर (!rsa->used) अणु
			netdev_err(dev, "Invalid Rx SA selected sa_idx=%d offload_handle=%lu\n",
				   sa_idx, xs->xso.offload_handle);
			वापस;
		पूर्ण

		ixgbe_ipsec_set_rx_sa(hw, sa_idx, 0, zerobuf, 0, 0, 0);
		hash_del_rcu(&rsa->hlist);

		/* अगर the IP table entry is referenced by only this SA,
		 * i.e. ref_cnt is only 1, clear the IP table entry as well
		 */
		ipi = rsa->iptbl_ind;
		अगर (ipsec->ip_tbl[ipi].ref_cnt > 0) अणु
			ipsec->ip_tbl[ipi].ref_cnt--;

			अगर (!ipsec->ip_tbl[ipi].ref_cnt) अणु
				स_रखो(&ipsec->ip_tbl[ipi], 0,
				       माप(काष्ठा rx_ip_sa));
				ixgbe_ipsec_set_rx_ip(hw, ipi,
						      (__क्रमce __be32 *)zerobuf);
			पूर्ण
		पूर्ण

		स_रखो(rsa, 0, माप(काष्ठा rx_sa));
		ipsec->num_rx_sa--;
	पूर्ण अन्यथा अणु
		sa_idx = xs->xso.offload_handle - IXGBE_IPSEC_BASE_TX_INDEX;

		अगर (!ipsec->tx_tbl[sa_idx].used) अणु
			netdev_err(dev, "Invalid Tx SA selected sa_idx=%d offload_handle=%lu\n",
				   sa_idx, xs->xso.offload_handle);
			वापस;
		पूर्ण

		ixgbe_ipsec_set_tx_sa(hw, sa_idx, zerobuf, 0);
		स_रखो(&ipsec->tx_tbl[sa_idx], 0, माप(काष्ठा tx_sa));
		ipsec->num_tx_sa--;
	पूर्ण

	/* अगर there are no SAs left, stop the engine to save energy */
	अगर (ipsec->num_rx_sa == 0 && ipsec->num_tx_sa == 0) अणु
		adapter->flags2 &= ~IXGBE_FLAG2_IPSEC_ENABLED;
		ixgbe_ipsec_stop_engine(adapter);
	पूर्ण
पूर्ण

/**
 * ixgbe_ipsec_offload_ok - can this packet use the xfrm hw offload
 * @skb: current data packet
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल bool ixgbe_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *xs)
अणु
	अगर (xs->props.family == AF_INET) अणु
		/* Offload with IPv4 options is not supported yet */
		अगर (ip_hdr(skb)->ihl != 5)
			वापस false;
	पूर्ण अन्यथा अणु
		/* Offload with IPv6 extension headers is not support yet */
		अगर (ipv6_ext_hdr(ipv6_hdr(skb)->nexthdr))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा xfrmdev_ops ixgbe_xfrmdev_ops = अणु
	.xकरो_dev_state_add = ixgbe_ipsec_add_sa,
	.xकरो_dev_state_delete = ixgbe_ipsec_del_sa,
	.xकरो_dev_offload_ok = ixgbe_ipsec_offload_ok,
पूर्ण;

/**
 * ixgbe_ipsec_vf_clear - clear the tables of data क्रम a VF
 * @adapter: board निजी काष्ठाure
 * @vf: VF id to be हटाओd
 **/
व्योम ixgbe_ipsec_vf_clear(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	पूर्णांक i;

	अगर (!ipsec)
		वापस;

	/* search rx sa table */
	क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT && ipsec->num_rx_sa; i++) अणु
		अगर (!ipsec->rx_tbl[i].used)
			जारी;
		अगर (ipsec->rx_tbl[i].mode & IXGBE_RXTXMOD_VF &&
		    ipsec->rx_tbl[i].vf == vf)
			ixgbe_ipsec_del_sa(ipsec->rx_tbl[i].xs);
	पूर्ण

	/* search tx sa table */
	क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT && ipsec->num_tx_sa; i++) अणु
		अगर (!ipsec->tx_tbl[i].used)
			जारी;
		अगर (ipsec->tx_tbl[i].mode & IXGBE_RXTXMOD_VF &&
		    ipsec->tx_tbl[i].vf == vf)
			ixgbe_ipsec_del_sa(ipsec->tx_tbl[i].xs);
	पूर्ण
पूर्ण

/**
 * ixgbe_ipsec_vf_add_sa - translate VF request to SA add
 * @adapter: board निजी काष्ठाure
 * @msgbuf: The message buffer
 * @vf: the VF index
 *
 * Make up a new xs and algorithm info from the data sent by the VF.
 * We only need to sketch in just enough to set up the HW offload.
 * Put the resulting offload_handle पूर्णांकo the वापस message to the VF.
 *
 * Returns 0 or error value
 **/
पूर्णांक ixgbe_ipsec_vf_add_sa(काष्ठा ixgbe_adapter *adapter, u32 *msgbuf, u32 vf)
अणु
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	काष्ठा xfrm_algo_desc *algo;
	काष्ठा sa_mbx_msg *sam;
	काष्ठा xfrm_state *xs;
	माप_प्रकार aead_len;
	u16 sa_idx;
	u32 pfsa;
	पूर्णांक err;

	sam = (काष्ठा sa_mbx_msg *)(&msgbuf[1]);
	अगर (!adapter->vfinfo[vf].trusted ||
	    !(adapter->flags2 & IXGBE_FLAG2_VF_IPSEC_ENABLED)) अणु
		e_warn(drv, "VF %d attempted to add an IPsec SA\n", vf);
		err = -EACCES;
		जाओ err_out;
	पूर्ण

	/* Tx IPsec offload करोesn't seem to work on this
	 * device, so block these requests क्रम now.
	 */
	अगर (!(sam->flags & XFRM_OFFLOAD_INBOUND)) अणु
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	xs = kzalloc(माप(*xs), GFP_KERNEL);
	अगर (unlikely(!xs)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	xs->xso.flags = sam->flags;
	xs->id.spi = sam->spi;
	xs->id.proto = sam->proto;
	xs->props.family = sam->family;
	अगर (xs->props.family == AF_INET6)
		स_नकल(&xs->id.daddr.a6, sam->addr, माप(xs->id.daddr.a6));
	अन्यथा
		स_नकल(&xs->id.daddr.a4, sam->addr, माप(xs->id.daddr.a4));
	xs->xso.dev = adapter->netdev;

	algo = xfrm_aead_get_byname(aes_gcm_name, IXGBE_IPSEC_AUTH_BITS, 1);
	अगर (unlikely(!algo)) अणु
		err = -ENOENT;
		जाओ err_xs;
	पूर्ण

	aead_len = माप(*xs->aead) + IXGBE_IPSEC_KEY_BITS / 8;
	xs->aead = kzalloc(aead_len, GFP_KERNEL);
	अगर (unlikely(!xs->aead)) अणु
		err = -ENOMEM;
		जाओ err_xs;
	पूर्ण

	xs->props.ealgo = algo->desc.sadb_alg_id;
	xs->geniv = algo->uinfo.aead.geniv;
	xs->aead->alg_icv_len = IXGBE_IPSEC_AUTH_BITS;
	xs->aead->alg_key_len = IXGBE_IPSEC_KEY_BITS;
	स_नकल(xs->aead->alg_key, sam->key, माप(sam->key));
	स_नकल(xs->aead->alg_name, aes_gcm_name, माप(aes_gcm_name));

	/* set up the HW offload */
	err = ixgbe_ipsec_add_sa(xs);
	अगर (err)
		जाओ err_aead;

	pfsa = xs->xso.offload_handle;
	अगर (pfsa < IXGBE_IPSEC_BASE_TX_INDEX) अणु
		sa_idx = pfsa - IXGBE_IPSEC_BASE_RX_INDEX;
		ipsec->rx_tbl[sa_idx].vf = vf;
		ipsec->rx_tbl[sa_idx].mode |= IXGBE_RXTXMOD_VF;
	पूर्ण अन्यथा अणु
		sa_idx = pfsa - IXGBE_IPSEC_BASE_TX_INDEX;
		ipsec->tx_tbl[sa_idx].vf = vf;
		ipsec->tx_tbl[sa_idx].mode |= IXGBE_RXTXMOD_VF;
	पूर्ण

	msgbuf[1] = xs->xso.offload_handle;

	वापस 0;

err_aead:
	kमुक्त_sensitive(xs->aead);
err_xs:
	kमुक्त_sensitive(xs);
err_out:
	msgbuf[1] = err;
	वापस err;
पूर्ण

/**
 * ixgbe_ipsec_vf_del_sa - translate VF request to SA delete
 * @adapter: board निजी काष्ठाure
 * @msgbuf: The message buffer
 * @vf: the VF index
 *
 * Given the offload_handle sent by the VF, look क्रम the related SA table
 * entry and use its xs field to call क्रम a delete of the SA.
 *
 * Note: We silently ignore requests to delete entries that are alपढ़ोy
 *       set to unused because when a VF is set to "DOWN", the PF first
 *       माला_लो a reset and clears all the VF's entries; then the VF's
 *       XFRM stack sends inभागidual deletes क्रम each entry, which the
 *       reset alपढ़ोy हटाओd.  In the future it might be good to try to
 *       optimize this so not so many unnecessary delete messages are sent.
 *
 * Returns 0 or error value
 **/
पूर्णांक ixgbe_ipsec_vf_del_sa(काष्ठा ixgbe_adapter *adapter, u32 *msgbuf, u32 vf)
अणु
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	काष्ठा xfrm_state *xs;
	u32 pfsa = msgbuf[1];
	u16 sa_idx;

	अगर (!adapter->vfinfo[vf].trusted) अणु
		e_err(drv, "vf %d attempted to delete an SA\n", vf);
		वापस -EPERM;
	पूर्ण

	अगर (pfsa < IXGBE_IPSEC_BASE_TX_INDEX) अणु
		काष्ठा rx_sa *rsa;

		sa_idx = pfsa - IXGBE_IPSEC_BASE_RX_INDEX;
		अगर (sa_idx >= IXGBE_IPSEC_MAX_SA_COUNT) अणु
			e_err(drv, "vf %d SA index %d out of range\n",
			      vf, sa_idx);
			वापस -EINVAL;
		पूर्ण

		rsa = &ipsec->rx_tbl[sa_idx];

		अगर (!rsa->used)
			वापस 0;

		अगर (!(rsa->mode & IXGBE_RXTXMOD_VF) ||
		    rsa->vf != vf) अणु
			e_err(drv, "vf %d bad Rx SA index %d\n", vf, sa_idx);
			वापस -ENOENT;
		पूर्ण

		xs = ipsec->rx_tbl[sa_idx].xs;
	पूर्ण अन्यथा अणु
		काष्ठा tx_sa *tsa;

		sa_idx = pfsa - IXGBE_IPSEC_BASE_TX_INDEX;
		अगर (sa_idx >= IXGBE_IPSEC_MAX_SA_COUNT) अणु
			e_err(drv, "vf %d SA index %d out of range\n",
			      vf, sa_idx);
			वापस -EINVAL;
		पूर्ण

		tsa = &ipsec->tx_tbl[sa_idx];

		अगर (!tsa->used)
			वापस 0;

		अगर (!(tsa->mode & IXGBE_RXTXMOD_VF) ||
		    tsa->vf != vf) अणु
			e_err(drv, "vf %d bad Tx SA index %d\n", vf, sa_idx);
			वापस -ENOENT;
		पूर्ण

		xs = ipsec->tx_tbl[sa_idx].xs;
	पूर्ण

	ixgbe_ipsec_del_sa(xs);

	/* हटाओ the xs that was made-up in the add request */
	kमुक्त_sensitive(xs);

	वापस 0;
पूर्ण

/**
 * ixgbe_ipsec_tx - setup Tx flags क्रम ipsec offload
 * @tx_ring: outgoing context
 * @first: current data packet
 * @itd: ipsec Tx data क्रम later use in building context descriptor
 **/
पूर्णांक ixgbe_ipsec_tx(काष्ठा ixgbe_ring *tx_ring,
		   काष्ठा ixgbe_tx_buffer *first,
		   काष्ठा ixgbe_ipsec_tx_data *itd)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(tx_ring->netdev);
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	काष्ठा xfrm_state *xs;
	काष्ठा sec_path *sp;
	काष्ठा tx_sa *tsa;

	sp = skb_sec_path(first->skb);
	अगर (unlikely(!sp->len)) अणु
		netdev_err(tx_ring->netdev, "%s: no xfrm state len = %d\n",
			   __func__, sp->len);
		वापस 0;
	पूर्ण

	xs = xfrm_input_state(first->skb);
	अगर (unlikely(!xs)) अणु
		netdev_err(tx_ring->netdev, "%s: no xfrm_input_state() xs = %p\n",
			   __func__, xs);
		वापस 0;
	पूर्ण

	itd->sa_idx = xs->xso.offload_handle - IXGBE_IPSEC_BASE_TX_INDEX;
	अगर (unlikely(itd->sa_idx >= IXGBE_IPSEC_MAX_SA_COUNT)) अणु
		netdev_err(tx_ring->netdev, "%s: bad sa_idx=%d handle=%lu\n",
			   __func__, itd->sa_idx, xs->xso.offload_handle);
		वापस 0;
	पूर्ण

	tsa = &ipsec->tx_tbl[itd->sa_idx];
	अगर (unlikely(!tsa->used)) अणु
		netdev_err(tx_ring->netdev, "%s: unused sa_idx=%d\n",
			   __func__, itd->sa_idx);
		वापस 0;
	पूर्ण

	first->tx_flags |= IXGBE_TX_FLAGS_IPSEC | IXGBE_TX_FLAGS_CC;

	अगर (xs->id.proto == IPPROTO_ESP) अणु

		itd->flags |= IXGBE_ADVTXD_TUCMD_IPSEC_TYPE_ESP |
			      IXGBE_ADVTXD_TUCMD_L4T_TCP;
		अगर (first->protocol == htons(ETH_P_IP))
			itd->flags |= IXGBE_ADVTXD_TUCMD_IPV4;

		/* The actual trailer length is authlen (16 bytes) plus
		 * 2 bytes क्रम the proto and the padlen values, plus
		 * padlen bytes of padding.  This ends up not the same
		 * as the अटल value found in xs->props.trailer_len (21).
		 *
		 * ... but अगर we're doing GSO, don't bother as the stack
		 * करोesn't add a trailer क्रम those.
		 */
		अगर (!skb_is_gso(first->skb)) अणु
			/* The "correct" way to get the auth length would be
			 * to use
			 *    authlen = crypto_aead_authsize(xs->data);
			 * but since we know we only have one size to worry
			 * about * we can let the compiler use the स्थिरant
			 * and save us a few CPU cycles.
			 */
			स्थिर पूर्णांक authlen = IXGBE_IPSEC_AUTH_BITS / 8;
			काष्ठा sk_buff *skb = first->skb;
			u8 padlen;
			पूर्णांक ret;

			ret = skb_copy_bits(skb, skb->len - (authlen + 2),
					    &padlen, 1);
			अगर (unlikely(ret))
				वापस 0;
			itd->trailer_len = authlen + 2 + padlen;
		पूर्ण
	पूर्ण
	अगर (tsa->encrypt)
		itd->flags |= IXGBE_ADVTXD_TUCMD_IPSEC_ENCRYPT_EN;

	वापस 1;
पूर्ण

/**
 * ixgbe_ipsec_rx - decode ipsec bits from Rx descriptor
 * @rx_ring: receiving ring
 * @rx_desc: receive data descriptor
 * @skb: current data packet
 *
 * Determine अगर there was an ipsec encapsulation noticed, and अगर so set up
 * the resulting status क्रम later in the receive stack.
 **/
व्योम ixgbe_ipsec_rx(काष्ठा ixgbe_ring *rx_ring,
		    जोड़ ixgbe_adv_rx_desc *rx_desc,
		    काष्ठा sk_buff *skb)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(rx_ring->netdev);
	__le16 pkt_info = rx_desc->wb.lower.lo_dword.hs_rss.pkt_info;
	__le16 ipsec_pkt_types = cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPSEC_AH |
					     IXGBE_RXDADV_PKTTYPE_IPSEC_ESP);
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;
	काष्ठा xfrm_offload *xo = शून्य;
	काष्ठा xfrm_state *xs = शून्य;
	काष्ठा ipv6hdr *ip6 = शून्य;
	काष्ठा iphdr *ip4 = शून्य;
	काष्ठा sec_path *sp;
	व्योम *daddr;
	__be32 spi;
	u8 *c_hdr;
	u8 proto;

	/* Find the ip and crypto headers in the data.
	 * We can assume no vlan header in the way, b/c the
	 * hw won't recognize the IPsec packet and anyway the
	 * currently vlan device करोesn't support xfrm offload.
	 */
	अगर (pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPV4)) अणु
		ip4 = (काष्ठा iphdr *)(skb->data + ETH_HLEN);
		daddr = &ip4->daddr;
		c_hdr = (u8 *)ip4 + ip4->ihl * 4;
	पूर्ण अन्यथा अगर (pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPV6)) अणु
		ip6 = (काष्ठा ipv6hdr *)(skb->data + ETH_HLEN);
		daddr = &ip6->daddr;
		c_hdr = (u8 *)ip6 + माप(काष्ठा ipv6hdr);
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	चयन (pkt_info & ipsec_pkt_types) अणु
	हाल cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPSEC_AH):
		spi = ((काष्ठा ip_auth_hdr *)c_hdr)->spi;
		proto = IPPROTO_AH;
		अवरोध;
	हाल cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPSEC_ESP):
		spi = ((काष्ठा ip_esp_hdr *)c_hdr)->spi;
		proto = IPPROTO_ESP;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	xs = ixgbe_ipsec_find_rx_state(ipsec, daddr, proto, spi, !!ip4);
	अगर (unlikely(!xs))
		वापस;

	sp = secpath_set(skb);
	अगर (unlikely(!sp))
		वापस;

	sp->xvec[sp->len++] = xs;
	sp->olen++;
	xo = xfrm_offload(skb);
	xo->flags = CRYPTO_DONE;
	xo->status = CRYPTO_SUCCESS;

	adapter->rx_ipsec++;
पूर्ण

/**
 * ixgbe_init_ipsec_offload - initialize security रेजिस्टरs क्रम IPSec operation
 * @adapter: board निजी काष्ठाure
 **/
व्योम ixgbe_init_ipsec_offload(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_ipsec *ipsec;
	u32 t_dis, r_dis;
	माप_प्रकार size;

	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	/* If there is no support क्रम either Tx or Rx offload
	 * we should not be advertising support क्रम IPsec.
	 */
	t_dis = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT) &
		IXGBE_SECTXSTAT_SECTX_OFF_DIS;
	r_dis = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT) &
		IXGBE_SECRXSTAT_SECRX_OFF_DIS;
	अगर (t_dis || r_dis)
		वापस;

	ipsec = kzalloc(माप(*ipsec), GFP_KERNEL);
	अगर (!ipsec)
		जाओ err1;
	hash_init(ipsec->rx_sa_list);

	size = माप(काष्ठा rx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->rx_tbl = kzalloc(size, GFP_KERNEL);
	अगर (!ipsec->rx_tbl)
		जाओ err2;

	size = माप(काष्ठा tx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->tx_tbl = kzalloc(size, GFP_KERNEL);
	अगर (!ipsec->tx_tbl)
		जाओ err2;

	size = माप(काष्ठा rx_ip_sa) * IXGBE_IPSEC_MAX_RX_IP_COUNT;
	ipsec->ip_tbl = kzalloc(size, GFP_KERNEL);
	अगर (!ipsec->ip_tbl)
		जाओ err2;

	ipsec->num_rx_sa = 0;
	ipsec->num_tx_sa = 0;

	adapter->ipsec = ipsec;
	ixgbe_ipsec_stop_engine(adapter);
	ixgbe_ipsec_clear_hw_tables(adapter);

	adapter->netdev->xfrmdev_ops = &ixgbe_xfrmdev_ops;

	वापस;

err2:
	kमुक्त(ipsec->ip_tbl);
	kमुक्त(ipsec->rx_tbl);
	kमुक्त(ipsec->tx_tbl);
	kमुक्त(ipsec);
err1:
	netdev_err(adapter->netdev, "Unable to allocate memory for SA tables");
पूर्ण

/**
 * ixgbe_stop_ipsec_offload - tear करोwn the ipsec offload
 * @adapter: board निजी काष्ठाure
 **/
व्योम ixgbe_stop_ipsec_offload(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_ipsec *ipsec = adapter->ipsec;

	adapter->ipsec = शून्य;
	अगर (ipsec) अणु
		kमुक्त(ipsec->ip_tbl);
		kमुक्त(ipsec->rx_tbl);
		kमुक्त(ipsec->tx_tbl);
		kमुक्त(ipsec);
	पूर्ण
पूर्ण
