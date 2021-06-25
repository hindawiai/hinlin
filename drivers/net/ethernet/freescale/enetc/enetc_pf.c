<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2017-2019 NXP */

#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/fsl/enetc_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश "enetc_ierb.h"
#समावेश "enetc_pf.h"

#घोषणा ENETC_DRV_NAME_STR "ENETC PF driver"

अटल व्योम enetc_pf_get_primary_mac_addr(काष्ठा enetc_hw *hw, पूर्णांक si, u8 *addr)
अणु
	u32 upper = __raw_पढ़ोl(hw->port + ENETC_PSIPMAR0(si));
	u16 lower = __raw_पढ़ोw(hw->port + ENETC_PSIPMAR1(si));

	*(u32 *)addr = upper;
	*(u16 *)(addr + 4) = lower;
पूर्ण

अटल व्योम enetc_pf_set_primary_mac_addr(काष्ठा enetc_hw *hw, पूर्णांक si,
					  स्थिर u8 *addr)
अणु
	u32 upper = *(स्थिर u32 *)addr;
	u16 lower = *(स्थिर u16 *)(addr + 4);

	__raw_ग_लिखोl(upper, hw->port + ENETC_PSIPMAR0(si));
	__raw_ग_लिखोw(lower, hw->port + ENETC_PSIPMAR1(si));
पूर्ण

अटल पूर्णांक enetc_pf_set_mac_addr(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा sockaddr *saddr = addr;

	अगर (!is_valid_ether_addr(saddr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(ndev->dev_addr, saddr->sa_data, ndev->addr_len);
	enetc_pf_set_primary_mac_addr(&priv->si->hw, 0, saddr->sa_data);

	वापस 0;
पूर्ण

अटल व्योम enetc_set_vlan_promisc(काष्ठा enetc_hw *hw, अक्षर si_map)
अणु
	u32 val = enetc_port_rd(hw, ENETC_PSIPVMR);

	val &= ~ENETC_PSIPVMR_SET_VP(ENETC_VLAN_PROMISC_MAP_ALL);
	enetc_port_wr(hw, ENETC_PSIPVMR, ENETC_PSIPVMR_SET_VP(si_map) | val);
पूर्ण

अटल व्योम enetc_enable_si_vlan_promisc(काष्ठा enetc_pf *pf, पूर्णांक si_idx)
अणु
	pf->vlan_promisc_simap |= BIT(si_idx);
	enetc_set_vlan_promisc(&pf->si->hw, pf->vlan_promisc_simap);
पूर्ण

अटल व्योम enetc_disable_si_vlan_promisc(काष्ठा enetc_pf *pf, पूर्णांक si_idx)
अणु
	pf->vlan_promisc_simap &= ~BIT(si_idx);
	enetc_set_vlan_promisc(&pf->si->hw, pf->vlan_promisc_simap);
पूर्ण

अटल व्योम enetc_set_isol_vlan(काष्ठा enetc_hw *hw, पूर्णांक si, u16 vlan, u8 qos)
अणु
	u32 val = 0;

	अगर (vlan)
		val = ENETC_PSIVLAN_EN | ENETC_PSIVLAN_SET_QOS(qos) | vlan;

	enetc_port_wr(hw, ENETC_PSIVLANR(si), val);
पूर्ण

अटल पूर्णांक enetc_mac_addr_hash_idx(स्थिर u8 *addr)
अणु
	u64 fold = __swab64(ether_addr_to_u64(addr)) >> 16;
	u64 mask = 0;
	पूर्णांक res = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		mask |= BIT_ULL(i * 6);

	क्रम (i = 0; i < 6; i++)
		res |= (hweight64(fold & (mask << i)) & 0x1) << i;

	वापस res;
पूर्ण

अटल व्योम enetc_reset_mac_addr_filter(काष्ठा enetc_mac_filter *filter)
अणु
	filter->mac_addr_cnt = 0;

	biपंचांगap_zero(filter->mac_hash_table,
		    ENETC_MADDR_HASH_TBL_SZ);
पूर्ण

अटल व्योम enetc_add_mac_addr_em_filter(काष्ठा enetc_mac_filter *filter,
					 स्थिर अचिन्हित अक्षर *addr)
अणु
	/* add exact match addr */
	ether_addr_copy(filter->mac_addr, addr);
	filter->mac_addr_cnt++;
पूर्ण

अटल व्योम enetc_add_mac_addr_ht_filter(काष्ठा enetc_mac_filter *filter,
					 स्थिर अचिन्हित अक्षर *addr)
अणु
	पूर्णांक idx = enetc_mac_addr_hash_idx(addr);

	/* add hash table entry */
	__set_bit(idx, filter->mac_hash_table);
	filter->mac_addr_cnt++;
पूर्ण

अटल व्योम enetc_clear_mac_ht_flt(काष्ठा enetc_si *si, पूर्णांक si_idx, पूर्णांक type)
अणु
	bool err = si->errata & ENETC_ERR_UCMCSWP;

	अगर (type == UC) अणु
		enetc_port_wr(&si->hw, ENETC_PSIUMHFR0(si_idx, err), 0);
		enetc_port_wr(&si->hw, ENETC_PSIUMHFR1(si_idx), 0);
	पूर्ण अन्यथा अणु /* MC */
		enetc_port_wr(&si->hw, ENETC_PSIMMHFR0(si_idx, err), 0);
		enetc_port_wr(&si->hw, ENETC_PSIMMHFR1(si_idx), 0);
	पूर्ण
पूर्ण

अटल व्योम enetc_set_mac_ht_flt(काष्ठा enetc_si *si, पूर्णांक si_idx, पूर्णांक type,
				 अचिन्हित दीर्घ hash)
अणु
	bool err = si->errata & ENETC_ERR_UCMCSWP;

	अगर (type == UC) अणु
		enetc_port_wr(&si->hw, ENETC_PSIUMHFR0(si_idx, err),
			      lower_32_bits(hash));
		enetc_port_wr(&si->hw, ENETC_PSIUMHFR1(si_idx),
			      upper_32_bits(hash));
	पूर्ण अन्यथा अणु /* MC */
		enetc_port_wr(&si->hw, ENETC_PSIMMHFR0(si_idx, err),
			      lower_32_bits(hash));
		enetc_port_wr(&si->hw, ENETC_PSIMMHFR1(si_idx),
			      upper_32_bits(hash));
	पूर्ण
पूर्ण

अटल व्योम enetc_sync_mac_filters(काष्ठा enetc_pf *pf)
अणु
	काष्ठा enetc_mac_filter *f = pf->mac_filter;
	काष्ठा enetc_si *si = pf->si;
	पूर्णांक i, pos;

	pos = EMETC_MAC_ADDR_FILT_RES;

	क्रम (i = 0; i < MADDR_TYPE; i++, f++) अणु
		bool em = (f->mac_addr_cnt == 1) && (i == UC);
		bool clear = !f->mac_addr_cnt;

		अगर (clear) अणु
			अगर (i == UC)
				enetc_clear_mac_flt_entry(si, pos);

			enetc_clear_mac_ht_flt(si, 0, i);
			जारी;
		पूर्ण

		/* exact match filter */
		अगर (em) अणु
			पूर्णांक err;

			enetc_clear_mac_ht_flt(si, 0, UC);

			err = enetc_set_mac_flt_entry(si, pos, f->mac_addr,
						      BIT(0));
			अगर (!err)
				जारी;

			/* fallback to HT filtering */
			dev_warn(&si->pdev->dev, "fallback to HT filt (%d)\n",
				 err);
		पूर्ण

		/* hash table filter, clear EM filter क्रम UC entries */
		अगर (i == UC)
			enetc_clear_mac_flt_entry(si, pos);

		enetc_set_mac_ht_flt(si, 0, i, *f->mac_hash_table);
	पूर्ण
पूर्ण

अटल व्योम enetc_pf_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	bool uprom = false, mprom = false;
	काष्ठा enetc_mac_filter *filter;
	काष्ठा netdev_hw_addr *ha;
	u32 psipmr = 0;
	bool em;

	अगर (ndev->flags & IFF_PROMISC) अणु
		/* enable promisc mode क्रम SI0 (PF) */
		psipmr = ENETC_PSIPMR_SET_UP(0) | ENETC_PSIPMR_SET_MP(0);
		uprom = true;
		mprom = true;
	पूर्ण अन्यथा अगर (ndev->flags & IFF_ALLMULTI) अणु
		/* enable multi cast promisc mode क्रम SI0 (PF) */
		psipmr = ENETC_PSIPMR_SET_MP(0);
		mprom = true;
	पूर्ण

	/* first 2 filter entries beदीर्घ to PF */
	अगर (!uprom) अणु
		/* Update unicast filters */
		filter = &pf->mac_filter[UC];
		enetc_reset_mac_addr_filter(filter);

		em = (netdev_uc_count(ndev) == 1);
		netdev_क्रम_each_uc_addr(ha, ndev) अणु
			अगर (em) अणु
				enetc_add_mac_addr_em_filter(filter, ha->addr);
				अवरोध;
			पूर्ण

			enetc_add_mac_addr_ht_filter(filter, ha->addr);
		पूर्ण
	पूर्ण

	अगर (!mprom) अणु
		/* Update multicast filters */
		filter = &pf->mac_filter[MC];
		enetc_reset_mac_addr_filter(filter);

		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			अगर (!is_multicast_ether_addr(ha->addr))
				जारी;

			enetc_add_mac_addr_ht_filter(filter, ha->addr);
		पूर्ण
	पूर्ण

	अगर (!uprom || !mprom)
		/* update PF entries */
		enetc_sync_mac_filters(pf);

	psipmr |= enetc_port_rd(hw, ENETC_PSIPMR) &
		  ~(ENETC_PSIPMR_SET_UP(0) | ENETC_PSIPMR_SET_MP(0));
	enetc_port_wr(hw, ENETC_PSIPMR, psipmr);
पूर्ण

अटल व्योम enetc_set_vlan_ht_filter(काष्ठा enetc_hw *hw, पूर्णांक si_idx,
				     अचिन्हित दीर्घ hash)
अणु
	enetc_port_wr(hw, ENETC_PSIVHFR0(si_idx), lower_32_bits(hash));
	enetc_port_wr(hw, ENETC_PSIVHFR1(si_idx), upper_32_bits(hash));
पूर्ण

अटल पूर्णांक enetc_vid_hash_idx(अचिन्हित पूर्णांक vid)
अणु
	पूर्णांक res = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		res |= (hweight8(vid & (BIT(i) | BIT(i + 6))) & 0x1) << i;

	वापस res;
पूर्ण

अटल व्योम enetc_sync_vlan_ht_filter(काष्ठा enetc_pf *pf, bool rehash)
अणु
	पूर्णांक i;

	अगर (rehash) अणु
		biपंचांगap_zero(pf->vlan_ht_filter, ENETC_VLAN_HT_SIZE);

		क्रम_each_set_bit(i, pf->active_vlans, VLAN_N_VID) अणु
			पूर्णांक hidx = enetc_vid_hash_idx(i);

			__set_bit(hidx, pf->vlan_ht_filter);
		पूर्ण
	पूर्ण

	enetc_set_vlan_ht_filter(&pf->si->hw, 0, *pf->vlan_ht_filter);
पूर्ण

अटल पूर्णांक enetc_vlan_rx_add_vid(काष्ठा net_device *ndev, __be16 prot, u16 vid)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);
	पूर्णांक idx;

	__set_bit(vid, pf->active_vlans);

	idx = enetc_vid_hash_idx(vid);
	अगर (!__test_and_set_bit(idx, pf->vlan_ht_filter))
		enetc_sync_vlan_ht_filter(pf, false);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_vlan_rx_del_vid(काष्ठा net_device *ndev, __be16 prot, u16 vid)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);

	__clear_bit(vid, pf->active_vlans);
	enetc_sync_vlan_ht_filter(pf, true);

	वापस 0;
पूर्ण

अटल व्योम enetc_set_loopback(काष्ठा net_device *ndev, bool en)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	u32 reg;

	reg = enetc_port_rd(hw, ENETC_PM0_IF_MODE);
	अगर (reg & ENETC_PM0_IFM_RG) अणु
		/* RGMII mode */
		reg = (reg & ~ENETC_PM0_IFM_RLP) |
		      (en ? ENETC_PM0_IFM_RLP : 0);
		enetc_port_wr(hw, ENETC_PM0_IF_MODE, reg);
	पूर्ण अन्यथा अणु
		/* assume SGMII mode */
		reg = enetc_port_rd(hw, ENETC_PM0_CMD_CFG);
		reg = (reg & ~ENETC_PM0_CMD_XGLP) |
		      (en ? ENETC_PM0_CMD_XGLP : 0);
		reg = (reg & ~ENETC_PM0_CMD_PHY_TX_EN) |
		      (en ? ENETC_PM0_CMD_PHY_TX_EN : 0);
		enetc_port_wr(hw, ENETC_PM0_CMD_CFG, reg);
		enetc_port_wr(hw, ENETC_PM1_CMD_CFG, reg);
	पूर्ण
पूर्ण

अटल पूर्णांक enetc_pf_set_vf_mac(काष्ठा net_device *ndev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);
	काष्ठा enetc_vf_state *vf_state;

	अगर (vf >= pf->total_vfs)
		वापस -EINVAL;

	अगर (!is_valid_ether_addr(mac))
		वापस -EADDRNOTAVAIL;

	vf_state = &pf->vf_state[vf];
	vf_state->flags |= ENETC_VF_FLAG_PF_SET_MAC;
	enetc_pf_set_primary_mac_addr(&priv->si->hw, vf + 1, mac);
	वापस 0;
पूर्ण

अटल पूर्णांक enetc_pf_set_vf_vlan(काष्ठा net_device *ndev, पूर्णांक vf, u16 vlan,
				u8 qos, __be16 proto)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);

	अगर (priv->si->errata & ENETC_ERR_VLAN_ISOL)
		वापस -EOPNOTSUPP;

	अगर (vf >= pf->total_vfs)
		वापस -EINVAL;

	अगर (proto != htons(ETH_P_8021Q))
		/* only C-tags supported क्रम now */
		वापस -EPROTONOSUPPORT;

	enetc_set_isol_vlan(&priv->si->hw, vf + 1, vlan, qos);
	वापस 0;
पूर्ण

अटल पूर्णांक enetc_pf_set_vf_spoofchk(काष्ठा net_device *ndev, पूर्णांक vf, bool en)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);
	u32 cfgr;

	अगर (vf >= pf->total_vfs)
		वापस -EINVAL;

	cfgr = enetc_port_rd(&priv->si->hw, ENETC_PSICFGR0(vf + 1));
	cfgr = (cfgr & ~ENETC_PSICFGR0_ASE) | (en ? ENETC_PSICFGR0_ASE : 0);
	enetc_port_wr(&priv->si->hw, ENETC_PSICFGR0(vf + 1), cfgr);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_setup_mac_address(काष्ठा device_node *np, काष्ठा enetc_pf *pf,
				   पूर्णांक si)
अणु
	काष्ठा device *dev = &pf->si->pdev->dev;
	काष्ठा enetc_hw *hw = &pf->si->hw;
	u8 mac_addr[ETH_ALEN] = अणु 0 पूर्ण;
	पूर्णांक err;

	/* (1) try to get the MAC address from the device tree */
	अगर (np) अणु
		err = of_get_mac_address(np, mac_addr);
		अगर (err == -EPROBE_DEFER)
			वापस err;
	पूर्ण

	/* (2) bootloader supplied MAC address */
	अगर (is_zero_ether_addr(mac_addr))
		enetc_pf_get_primary_mac_addr(hw, si, mac_addr);

	/* (3) choose a अक्रमom one */
	अगर (is_zero_ether_addr(mac_addr)) अणु
		eth_अक्रमom_addr(mac_addr);
		dev_info(dev, "no MAC address specified for SI%d, using %pM\n",
			 si, mac_addr);
	पूर्ण

	enetc_pf_set_primary_mac_addr(hw, si, mac_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_setup_mac_addresses(काष्ठा device_node *np,
				     काष्ठा enetc_pf *pf)
अणु
	पूर्णांक err, i;

	/* The PF might take its MAC from the device tree */
	err = enetc_setup_mac_address(np, pf, 0);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < pf->total_vfs; i++) अणु
		err = enetc_setup_mac_address(शून्य, pf, i + 1);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम enetc_port_assign_rfs_entries(काष्ठा enetc_si *si)
अणु
	काष्ठा enetc_pf *pf = enetc_si_priv(si);
	काष्ठा enetc_hw *hw = &si->hw;
	पूर्णांक num_entries, vf_entries, i;
	u32 val;

	/* split RFS entries between functions */
	val = enetc_port_rd(hw, ENETC_PRFSCAPR);
	num_entries = ENETC_PRFSCAPR_GET_NUM_RFS(val);
	vf_entries = num_entries / (pf->total_vfs + 1);

	क्रम (i = 0; i < pf->total_vfs; i++)
		enetc_port_wr(hw, ENETC_PSIRFSCFGR(i + 1), vf_entries);
	enetc_port_wr(hw, ENETC_PSIRFSCFGR(0),
		      num_entries - vf_entries * pf->total_vfs);

	/* enable RFS on port */
	enetc_port_wr(hw, ENETC_PRFSMR, ENETC_PRFSMR_RFSE);
पूर्ण

अटल व्योम enetc_port_si_configure(काष्ठा enetc_si *si)
अणु
	काष्ठा enetc_pf *pf = enetc_si_priv(si);
	काष्ठा enetc_hw *hw = &si->hw;
	पूर्णांक num_rings, i;
	u32 val;

	val = enetc_port_rd(hw, ENETC_PCAPR0);
	num_rings = min(ENETC_PCAPR0_RXBDR(val), ENETC_PCAPR0_TXBDR(val));

	val = ENETC_PSICFGR0_SET_TXBDR(ENETC_PF_NUM_RINGS);
	val |= ENETC_PSICFGR0_SET_RXBDR(ENETC_PF_NUM_RINGS);

	अगर (unlikely(num_rings < ENETC_PF_NUM_RINGS)) अणु
		val = ENETC_PSICFGR0_SET_TXBDR(num_rings);
		val |= ENETC_PSICFGR0_SET_RXBDR(num_rings);

		dev_warn(&si->pdev->dev, "Found %d rings, expected %d!\n",
			 num_rings, ENETC_PF_NUM_RINGS);

		num_rings = 0;
	पूर्ण

	/* Add शेष one-समय settings क्रम SI0 (PF) */
	val |= ENETC_PSICFGR0_SIVC(ENETC_VLAN_TYPE_C | ENETC_VLAN_TYPE_S);

	enetc_port_wr(hw, ENETC_PSICFGR0(0), val);

	अगर (num_rings)
		num_rings -= ENETC_PF_NUM_RINGS;

	/* Configure the SIs क्रम each available VF */
	val = ENETC_PSICFGR0_SIVC(ENETC_VLAN_TYPE_C | ENETC_VLAN_TYPE_S);
	val |= ENETC_PSICFGR0_VTE | ENETC_PSICFGR0_SIVIE;

	अगर (num_rings) अणु
		num_rings /= pf->total_vfs;
		val |= ENETC_PSICFGR0_SET_TXBDR(num_rings);
		val |= ENETC_PSICFGR0_SET_RXBDR(num_rings);
	पूर्ण

	क्रम (i = 0; i < pf->total_vfs; i++)
		enetc_port_wr(hw, ENETC_PSICFGR0(i + 1), val);

	/* Port level VLAN settings */
	val = ENETC_PVCLCTR_OVTPIDL(ENETC_VLAN_TYPE_C | ENETC_VLAN_TYPE_S);
	enetc_port_wr(hw, ENETC_PVCLCTR, val);
	/* use outer tag क्रम VLAN filtering */
	enetc_port_wr(hw, ENETC_PSIVLANFMR, ENETC_PSIVLANFMR_VS);
पूर्ण

अटल व्योम enetc_configure_port_mac(काष्ठा enetc_hw *hw)
अणु
	enetc_port_wr(hw, ENETC_PM0_MAXFRM,
		      ENETC_SET_MAXFRM(ENETC_RX_MAXFRM_SIZE));

	enetc_port_wr(hw, ENETC_PTCMSDUR(0), ENETC_MAC_MAXFRM_SIZE);

	enetc_port_wr(hw, ENETC_PM0_CMD_CFG, ENETC_PM0_CMD_PHY_TX_EN |
		      ENETC_PM0_CMD_TXP	| ENETC_PM0_PROMISC);

	enetc_port_wr(hw, ENETC_PM1_CMD_CFG, ENETC_PM0_CMD_PHY_TX_EN |
		      ENETC_PM0_CMD_TXP	| ENETC_PM0_PROMISC);

	/* On LS1028A, the MAC RX FIFO शेषs to 2, which is too high
	 * and may lead to RX lock-up under traffic. Set it to 1 instead,
	 * as recommended by the hardware team.
	 */
	enetc_port_wr(hw, ENETC_PM0_RX_FIFO, ENETC_PM0_RX_FIFO_VAL);
पूर्ण

अटल व्योम enetc_mac_config(काष्ठा enetc_hw *hw, phy_पूर्णांकerface_t phy_mode)
अणु
	u32 val;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(phy_mode)) अणु
		val = enetc_port_rd(hw, ENETC_PM0_IF_MODE);
		val &= ~ENETC_PM0_IFM_EN_AUTO;
		val &= ENETC_PM0_IFM_IFMODE_MASK;
		val |= ENETC_PM0_IFM_IFMODE_GMII | ENETC_PM0_IFM_RG;
		enetc_port_wr(hw, ENETC_PM0_IF_MODE, val);
	पूर्ण

	अगर (phy_mode == PHY_INTERFACE_MODE_USXGMII) अणु
		val = ENETC_PM0_IFM_FULL_DPX | ENETC_PM0_IFM_IFMODE_XGMII;
		enetc_port_wr(hw, ENETC_PM0_IF_MODE, val);
	पूर्ण
पूर्ण

अटल व्योम enetc_mac_enable(काष्ठा enetc_hw *hw, bool en)
अणु
	u32 val = enetc_port_rd(hw, ENETC_PM0_CMD_CFG);

	val &= ~(ENETC_PM0_TX_EN | ENETC_PM0_RX_EN);
	val |= en ? (ENETC_PM0_TX_EN | ENETC_PM0_RX_EN) : 0;

	enetc_port_wr(hw, ENETC_PM0_CMD_CFG, val);
	enetc_port_wr(hw, ENETC_PM1_CMD_CFG, val);
पूर्ण

अटल व्योम enetc_configure_port_pmac(काष्ठा enetc_hw *hw)
अणु
	u32 temp;

	/* Set pMAC step lock */
	temp = enetc_port_rd(hw, ENETC_PFPMR);
	enetc_port_wr(hw, ENETC_PFPMR,
		      temp | ENETC_PFPMR_PMACE | ENETC_PFPMR_MWLM);

	temp = enetc_port_rd(hw, ENETC_MMCSR);
	enetc_port_wr(hw, ENETC_MMCSR, temp | ENETC_MMCSR_ME);
पूर्ण

अटल व्योम enetc_configure_port(काष्ठा enetc_pf *pf)
अणु
	u8 hash_key[ENETC_RSSHASH_KEY_SIZE];
	काष्ठा enetc_hw *hw = &pf->si->hw;

	enetc_configure_port_pmac(hw);

	enetc_configure_port_mac(hw);

	enetc_port_si_configure(pf->si);

	/* set up hash key */
	get_अक्रमom_bytes(hash_key, ENETC_RSSHASH_KEY_SIZE);
	enetc_set_rss_key(hw, hash_key);

	/* split up RFS entries */
	enetc_port_assign_rfs_entries(pf->si);

	/* enक्रमce VLAN promisc mode क्रम all SIs */
	pf->vlan_promisc_simap = ENETC_VLAN_PROMISC_MAP_ALL;
	enetc_set_vlan_promisc(hw, pf->vlan_promisc_simap);

	enetc_port_wr(hw, ENETC_PSIPMR, 0);

	/* enable port */
	enetc_port_wr(hw, ENETC_PMR, ENETC_PMR_EN);
पूर्ण

/* Messaging */
अटल u16 enetc_msg_pf_set_vf_primary_mac_addr(काष्ठा enetc_pf *pf,
						पूर्णांक vf_id)
अणु
	काष्ठा enetc_vf_state *vf_state = &pf->vf_state[vf_id];
	काष्ठा enetc_msg_swbd *msg = &pf->rxmsg[vf_id];
	काष्ठा enetc_msg_cmd_set_primary_mac *cmd;
	काष्ठा device *dev = &pf->si->pdev->dev;
	u16 cmd_id;
	अक्षर *addr;

	cmd = (काष्ठा enetc_msg_cmd_set_primary_mac *)msg->vaddr;
	cmd_id = cmd->header.id;
	अगर (cmd_id != ENETC_MSG_CMD_MNG_ADD)
		वापस ENETC_MSG_CMD_STATUS_FAIL;

	addr = cmd->mac.sa_data;
	अगर (vf_state->flags & ENETC_VF_FLAG_PF_SET_MAC)
		dev_warn(dev, "Attempt to override PF set mac addr for VF%d\n",
			 vf_id);
	अन्यथा
		enetc_pf_set_primary_mac_addr(&pf->si->hw, vf_id + 1, addr);

	वापस ENETC_MSG_CMD_STATUS_OK;
पूर्ण

व्योम enetc_msg_handle_rxmsg(काष्ठा enetc_pf *pf, पूर्णांक vf_id, u16 *status)
अणु
	काष्ठा enetc_msg_swbd *msg = &pf->rxmsg[vf_id];
	काष्ठा device *dev = &pf->si->pdev->dev;
	काष्ठा enetc_msg_cmd_header *cmd_hdr;
	u16 cmd_type;

	*status = ENETC_MSG_CMD_STATUS_OK;
	cmd_hdr = (काष्ठा enetc_msg_cmd_header *)msg->vaddr;
	cmd_type = cmd_hdr->type;

	चयन (cmd_type) अणु
	हाल ENETC_MSG_CMD_MNG_MAC:
		*status = enetc_msg_pf_set_vf_primary_mac_addr(pf, vf_id);
		अवरोध;
	शेष:
		dev_err(dev, "command not supported (cmd_type: 0x%x)\n",
			cmd_type);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक enetc_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा enetc_si *si = pci_get_drvdata(pdev);
	काष्ठा enetc_pf *pf = enetc_si_priv(si);
	पूर्णांक err;

	अगर (!num_vfs) अणु
		enetc_msg_psi_मुक्त(pf);
		kमुक्त(pf->vf_state);
		pf->num_vfs = 0;
		pci_disable_sriov(pdev);
	पूर्ण अन्यथा अणु
		pf->num_vfs = num_vfs;

		pf->vf_state = kसुस्मृति(num_vfs, माप(काष्ठा enetc_vf_state),
				       GFP_KERNEL);
		अगर (!pf->vf_state) अणु
			pf->num_vfs = 0;
			वापस -ENOMEM;
		पूर्ण

		err = enetc_msg_psi_init(pf);
		अगर (err) अणु
			dev_err(&pdev->dev, "enetc_msg_psi_init (%d)\n", err);
			जाओ err_msg_psi;
		पूर्ण

		err = pci_enable_sriov(pdev, num_vfs);
		अगर (err) अणु
			dev_err(&pdev->dev, "pci_enable_sriov err %d\n", err);
			जाओ err_en_sriov;
		पूर्ण
	पूर्ण

	वापस num_vfs;

err_en_sriov:
	enetc_msg_psi_मुक्त(pf);
err_msg_psi:
	kमुक्त(pf->vf_state);
	pf->num_vfs = 0;

	वापस err;
पूर्ण
#अन्यथा
#घोषणा enetc_sriov_configure(pdev, num_vfs)	(व्योम)0
#पूर्ण_अगर

अटल पूर्णांक enetc_pf_set_features(काष्ठा net_device *ndev,
				 netdev_features_t features)
अणु
	netdev_features_t changed = ndev->features ^ features;
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	अगर (changed & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);

		अगर (!!(features & NETIF_F_HW_VLAN_CTAG_FILTER))
			enetc_disable_si_vlan_promisc(pf, 0);
		अन्यथा
			enetc_enable_si_vlan_promisc(pf, 0);
	पूर्ण

	अगर (changed & NETIF_F_LOOPBACK)
		enetc_set_loopback(ndev, !!(features & NETIF_F_LOOPBACK));

	वापस enetc_set_features(ndev, features);
पूर्ण

अटल स्थिर काष्ठा net_device_ops enetc_ndev_ops = अणु
	.nकरो_खोलो		= enetc_खोलो,
	.nकरो_stop		= enetc_बंद,
	.nकरो_start_xmit		= enetc_xmit,
	.nकरो_get_stats		= enetc_get_stats,
	.nकरो_set_mac_address	= enetc_pf_set_mac_addr,
	.nकरो_set_rx_mode	= enetc_pf_set_rx_mode,
	.nकरो_vlan_rx_add_vid	= enetc_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= enetc_vlan_rx_del_vid,
	.nकरो_set_vf_mac		= enetc_pf_set_vf_mac,
	.nकरो_set_vf_vlan	= enetc_pf_set_vf_vlan,
	.nकरो_set_vf_spoofchk	= enetc_pf_set_vf_spoofchk,
	.nकरो_set_features	= enetc_pf_set_features,
	.nकरो_करो_ioctl		= enetc_ioctl,
	.nकरो_setup_tc		= enetc_setup_tc,
	.nकरो_bpf		= enetc_setup_bpf,
	.nकरो_xdp_xmit		= enetc_xdp_xmit,
पूर्ण;

अटल व्योम enetc_pf_netdev_setup(काष्ठा enetc_si *si, काष्ठा net_device *ndev,
				  स्थिर काष्ठा net_device_ops *ndev_ops)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	SET_NETDEV_DEV(ndev, &si->pdev->dev);
	priv->ndev = ndev;
	priv->si = si;
	priv->dev = &si->pdev->dev;
	si->ndev = ndev;

	priv->msg_enable = (NETIF_MSG_WOL << 1) - 1;
	ndev->netdev_ops = ndev_ops;
	enetc_set_ethtool_ops(ndev);
	ndev->watchकरोg_समयo = 5 * HZ;
	ndev->max_mtu = ENETC_MAX_MTU;

	ndev->hw_features = NETIF_F_SG | NETIF_F_RXCSUM |
			    NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_LOOPBACK;
	ndev->features = NETIF_F_HIGHDMA | NETIF_F_SG | NETIF_F_RXCSUM |
			 NETIF_F_HW_VLAN_CTAG_TX |
			 NETIF_F_HW_VLAN_CTAG_RX;

	अगर (si->num_rss)
		ndev->hw_features |= NETIF_F_RXHASH;

	ndev->priv_flags |= IFF_UNICAST_FLT;

	अगर (si->hw_features & ENETC_SI_F_QBV)
		priv->active_offloads |= ENETC_F_QBV;

	अगर (si->hw_features & ENETC_SI_F_PSFP && !enetc_psfp_enable(priv)) अणु
		priv->active_offloads |= ENETC_F_QCI;
		ndev->features |= NETIF_F_HW_TC;
		ndev->hw_features |= NETIF_F_HW_TC;
	पूर्ण

	/* pick up primary MAC address from SI */
	enetc_get_primary_mac_addr(&si->hw, ndev->dev_addr);
पूर्ण

अटल पूर्णांक enetc_mdio_probe(काष्ठा enetc_pf *pf, काष्ठा device_node *np)
अणु
	काष्ठा device *dev = &pf->si->pdev->dev;
	काष्ठा enetc_mdio_priv *mdio_priv;
	काष्ठा mii_bus *bus;
	पूर्णांक err;

	bus = devm_mdiobus_alloc_size(dev, माप(*mdio_priv));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "Freescale ENETC MDIO Bus";
	bus->पढ़ो = enetc_mdio_पढ़ो;
	bus->ग_लिखो = enetc_mdio_ग_लिखो;
	bus->parent = dev;
	mdio_priv = bus->priv;
	mdio_priv->hw = &pf->si->hw;
	mdio_priv->mdio_base = ENETC_EMDIO_BASE;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	err = of_mdiobus_रेजिस्टर(bus, np);
	अगर (err) अणु
		dev_err(dev, "cannot register MDIO bus\n");
		वापस err;
	पूर्ण

	pf->mdio = bus;

	वापस 0;
पूर्ण

अटल व्योम enetc_mdio_हटाओ(काष्ठा enetc_pf *pf)
अणु
	अगर (pf->mdio)
		mdiobus_unरेजिस्टर(pf->mdio);
पूर्ण

अटल पूर्णांक enetc_imdio_create(काष्ठा enetc_pf *pf)
अणु
	काष्ठा device *dev = &pf->si->pdev->dev;
	काष्ठा enetc_mdio_priv *mdio_priv;
	काष्ठा lynx_pcs *pcs_lynx;
	काष्ठा mdio_device *pcs;
	काष्ठा mii_bus *bus;
	पूर्णांक err;

	bus = mdiobus_alloc_size(माप(*mdio_priv));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "Freescale ENETC internal MDIO Bus";
	bus->पढ़ो = enetc_mdio_पढ़ो;
	bus->ग_लिखो = enetc_mdio_ग_लिखो;
	bus->parent = dev;
	bus->phy_mask = ~0;
	mdio_priv = bus->priv;
	mdio_priv->hw = &pf->si->hw;
	mdio_priv->mdio_base = ENETC_PM_IMDIO_BASE;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-imdio", dev_name(dev));

	err = mdiobus_रेजिस्टर(bus);
	अगर (err) अणु
		dev_err(dev, "cannot register internal MDIO bus (%d)\n", err);
		जाओ मुक्त_mdio_bus;
	पूर्ण

	pcs = mdio_device_create(bus, 0);
	अगर (IS_ERR(pcs)) अणु
		err = PTR_ERR(pcs);
		dev_err(dev, "cannot create pcs (%d)\n", err);
		जाओ unरेजिस्टर_mdiobus;
	पूर्ण

	pcs_lynx = lynx_pcs_create(pcs);
	अगर (!pcs_lynx) अणु
		mdio_device_मुक्त(pcs);
		err = -ENOMEM;
		dev_err(dev, "cannot create lynx pcs (%d)\n", err);
		जाओ unरेजिस्टर_mdiobus;
	पूर्ण

	pf->imdio = bus;
	pf->pcs = pcs_lynx;

	वापस 0;

unरेजिस्टर_mdiobus:
	mdiobus_unरेजिस्टर(bus);
मुक्त_mdio_bus:
	mdiobus_मुक्त(bus);
	वापस err;
पूर्ण

अटल व्योम enetc_imdio_हटाओ(काष्ठा enetc_pf *pf)
अणु
	अगर (pf->pcs) अणु
		mdio_device_मुक्त(pf->pcs->mdio);
		lynx_pcs_destroy(pf->pcs);
	पूर्ण
	अगर (pf->imdio) अणु
		mdiobus_unरेजिस्टर(pf->imdio);
		mdiobus_मुक्त(pf->imdio);
	पूर्ण
पूर्ण

अटल bool enetc_port_has_pcs(काष्ठा enetc_pf *pf)
अणु
	वापस (pf->अगर_mode == PHY_INTERFACE_MODE_SGMII ||
		pf->अगर_mode == PHY_INTERFACE_MODE_2500BASEX ||
		pf->अगर_mode == PHY_INTERFACE_MODE_USXGMII);
पूर्ण

अटल पूर्णांक enetc_mdiobus_create(काष्ठा enetc_pf *pf, काष्ठा device_node *node)
अणु
	काष्ठा device_node *mdio_np;
	पूर्णांक err;

	mdio_np = of_get_child_by_name(node, "mdio");
	अगर (mdio_np) अणु
		err = enetc_mdio_probe(pf, mdio_np);

		of_node_put(mdio_np);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (enetc_port_has_pcs(pf)) अणु
		err = enetc_imdio_create(pf);
		अगर (err) अणु
			enetc_mdio_हटाओ(pf);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम enetc_mdiobus_destroy(काष्ठा enetc_pf *pf)
अणु
	enetc_mdio_हटाओ(pf);
	enetc_imdio_हटाओ(pf);
पूर्ण

अटल व्योम enetc_pl_mac_validate(काष्ठा phylink_config *config,
				  अचिन्हित दीर्घ *supported,
				  काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_INTERNAL &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_2500BASEX &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_USXGMII &&
	    !phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface)) अणु
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		वापस;
	पूर्ण

	phylink_set_port_modes(mask);
	phylink_set(mask, Autoneg);
	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);
	phylink_set(mask, 10baseT_Half);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 100baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 1000baseT_Half);
	phylink_set(mask, 1000baseT_Full);

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_INTERNAL ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_USXGMII) अणु
		phylink_set(mask, 2500baseT_Full);
		phylink_set(mask, 2500baseX_Full);
	पूर्ण

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम enetc_pl_mac_config(काष्ठा phylink_config *config,
				अचिन्हित पूर्णांक mode,
				स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा enetc_pf *pf = phylink_to_enetc_pf(config);
	काष्ठा enetc_ndev_priv *priv;

	enetc_mac_config(&pf->si->hw, state->पूर्णांकerface);

	priv = netdev_priv(pf->si->ndev);
	अगर (pf->pcs)
		phylink_set_pcs(priv->phylink, &pf->pcs->pcs);
पूर्ण

अटल व्योम enetc_क्रमce_rgmii_mac(काष्ठा enetc_hw *hw, पूर्णांक speed, पूर्णांक duplex)
अणु
	u32 old_val, val;

	old_val = val = enetc_port_rd(hw, ENETC_PM0_IF_MODE);

	अगर (speed == SPEED_1000) अणु
		val &= ~ENETC_PM0_IFM_SSP_MASK;
		val |= ENETC_PM0_IFM_SSP_1000;
	पूर्ण अन्यथा अगर (speed == SPEED_100) अणु
		val &= ~ENETC_PM0_IFM_SSP_MASK;
		val |= ENETC_PM0_IFM_SSP_100;
	पूर्ण अन्यथा अगर (speed == SPEED_10) अणु
		val &= ~ENETC_PM0_IFM_SSP_MASK;
		val |= ENETC_PM0_IFM_SSP_10;
	पूर्ण

	अगर (duplex == DUPLEX_FULL)
		val |= ENETC_PM0_IFM_FULL_DPX;
	अन्यथा
		val &= ~ENETC_PM0_IFM_FULL_DPX;

	अगर (val == old_val)
		वापस;

	enetc_port_wr(hw, ENETC_PM0_IF_MODE, val);
पूर्ण

अटल व्योम enetc_pl_mac_link_up(काष्ठा phylink_config *config,
				 काष्ठा phy_device *phy, अचिन्हित पूर्णांक mode,
				 phy_पूर्णांकerface_t पूर्णांकerface, पूर्णांक speed,
				 पूर्णांक duplex, bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा enetc_pf *pf = phylink_to_enetc_pf(config);
	u32 छोड़ो_off_thresh = 0, छोड़ो_on_thresh = 0;
	u32 init_quanta = 0, refresh_quanta = 0;
	काष्ठा enetc_hw *hw = &pf->si->hw;
	काष्ठा enetc_ndev_priv *priv;
	u32 rbmr, cmd_cfg;
	पूर्णांक idx;

	priv = netdev_priv(pf->si->ndev);
	अगर (priv->active_offloads & ENETC_F_QBV)
		enetc_sched_speed_set(priv, speed);

	अगर (!phylink_स्वतःneg_inband(mode) &&
	    phy_पूर्णांकerface_mode_is_rgmii(पूर्णांकerface))
		enetc_क्रमce_rgmii_mac(hw, speed, duplex);

	/* Flow control */
	क्रम (idx = 0; idx < priv->num_rx_rings; idx++) अणु
		rbmr = enetc_rxbdr_rd(hw, idx, ENETC_RBMR);

		अगर (tx_छोड़ो)
			rbmr |= ENETC_RBMR_CM;
		अन्यथा
			rbmr &= ~ENETC_RBMR_CM;

		enetc_rxbdr_wr(hw, idx, ENETC_RBMR, rbmr);
	पूर्ण

	अगर (tx_छोड़ो) अणु
		/* When the port first enters congestion, send a PAUSE request
		 * with the maximum number of quanta. When the port निकासs
		 * congestion, it will स्वतःmatically send a PAUSE frame with
		 * zero quanta.
		 */
		init_quanta = 0xffff;

		/* Also, set up the refresh समयr to send follow-up PAUSE
		 * frames at half the quanta value, in हाल the congestion
		 * condition persists.
		 */
		refresh_quanta = 0xffff / 2;

		/* Start emitting PAUSE frames when 3 large frames (or more
		 * smaller frames) have accumulated in the FIFO रुकोing to be
		 * DMAed to the RX ring.
		 */
		छोड़ो_on_thresh = 3 * ENETC_MAC_MAXFRM_SIZE;
		छोड़ो_off_thresh = 1 * ENETC_MAC_MAXFRM_SIZE;
	पूर्ण

	enetc_port_wr(hw, ENETC_PM0_PAUSE_QUANTA, init_quanta);
	enetc_port_wr(hw, ENETC_PM1_PAUSE_QUANTA, init_quanta);
	enetc_port_wr(hw, ENETC_PM0_PAUSE_THRESH, refresh_quanta);
	enetc_port_wr(hw, ENETC_PM1_PAUSE_THRESH, refresh_quanta);
	enetc_port_wr(hw, ENETC_PPAUONTR, छोड़ो_on_thresh);
	enetc_port_wr(hw, ENETC_PPAUOFFTR, छोड़ो_off_thresh);

	cmd_cfg = enetc_port_rd(hw, ENETC_PM0_CMD_CFG);

	अगर (rx_छोड़ो)
		cmd_cfg &= ~ENETC_PM0_PAUSE_IGN;
	अन्यथा
		cmd_cfg |= ENETC_PM0_PAUSE_IGN;

	enetc_port_wr(hw, ENETC_PM0_CMD_CFG, cmd_cfg);
	enetc_port_wr(hw, ENETC_PM1_CMD_CFG, cmd_cfg);

	enetc_mac_enable(hw, true);
पूर्ण

अटल व्योम enetc_pl_mac_link_करोwn(काष्ठा phylink_config *config,
				   अचिन्हित पूर्णांक mode,
				   phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा enetc_pf *pf = phylink_to_enetc_pf(config);

	enetc_mac_enable(&pf->si->hw, false);
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops enetc_mac_phylink_ops = अणु
	.validate = enetc_pl_mac_validate,
	.mac_config = enetc_pl_mac_config,
	.mac_link_up = enetc_pl_mac_link_up,
	.mac_link_करोwn = enetc_pl_mac_link_करोwn,
पूर्ण;

अटल पूर्णांक enetc_phylink_create(काष्ठा enetc_ndev_priv *priv,
				काष्ठा device_node *node)
अणु
	काष्ठा enetc_pf *pf = enetc_si_priv(priv->si);
	काष्ठा phylink *phylink;
	पूर्णांक err;

	pf->phylink_config.dev = &priv->ndev->dev;
	pf->phylink_config.type = PHYLINK_NETDEV;

	phylink = phylink_create(&pf->phylink_config, of_fwnode_handle(node),
				 pf->अगर_mode, &enetc_mac_phylink_ops);
	अगर (IS_ERR(phylink)) अणु
		err = PTR_ERR(phylink);
		वापस err;
	पूर्ण

	priv->phylink = phylink;

	वापस 0;
पूर्ण

अटल व्योम enetc_phylink_destroy(काष्ठा enetc_ndev_priv *priv)
अणु
	अगर (priv->phylink)
		phylink_destroy(priv->phylink);
पूर्ण

/* Initialize the entire shared memory क्रम the flow steering entries
 * of this port (PF + VFs)
 */
अटल पूर्णांक enetc_init_port_rfs_memory(काष्ठा enetc_si *si)
अणु
	काष्ठा enetc_cmd_rfse rfse = अणु0पूर्ण;
	काष्ठा enetc_hw *hw = &si->hw;
	पूर्णांक num_rfs, i, err = 0;
	u32 val;

	val = enetc_port_rd(hw, ENETC_PRFSCAPR);
	num_rfs = ENETC_PRFSCAPR_GET_NUM_RFS(val);

	क्रम (i = 0; i < num_rfs; i++) अणु
		err = enetc_set_fs_entry(si, &rfse, i);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक enetc_init_port_rss_memory(काष्ठा enetc_si *si)
अणु
	काष्ठा enetc_hw *hw = &si->hw;
	पूर्णांक num_rss, err;
	पूर्णांक *rss_table;
	u32 val;

	val = enetc_port_rd(hw, ENETC_PRSSCAPR);
	num_rss = ENETC_PRSSCAPR_GET_NUM_RSS(val);
	अगर (!num_rss)
		वापस 0;

	rss_table = kसुस्मृति(num_rss, माप(*rss_table), GFP_KERNEL);
	अगर (!rss_table)
		वापस -ENOMEM;

	err = enetc_set_rss_table(si, rss_table, num_rss);

	kमुक्त(rss_table);

	वापस err;
पूर्ण

अटल पूर्णांक enetc_pf_रेजिस्टर_with_ierb(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा platक्रमm_device *ierb_pdev;
	काष्ठा device_node *ierb_node;

	/* Don't रेजिस्टर with the IERB अगर the PF itself is disabled */
	अगर (!node || !of_device_is_available(node))
		वापस 0;

	ierb_node = of_find_compatible_node(शून्य, शून्य,
					    "fsl,ls1028a-enetc-ierb");
	अगर (!ierb_node || !of_device_is_available(ierb_node))
		वापस -ENODEV;

	ierb_pdev = of_find_device_by_node(ierb_node);
	of_node_put(ierb_node);

	अगर (!ierb_pdev)
		वापस -EPROBE_DEFER;

	वापस enetc_ierb_रेजिस्टर_pf(ierb_pdev, pdev);
पूर्ण

अटल पूर्णांक enetc_pf_probe(काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा enetc_ndev_priv *priv;
	काष्ठा net_device *ndev;
	काष्ठा enetc_si *si;
	काष्ठा enetc_pf *pf;
	पूर्णांक err;

	err = enetc_pf_रेजिस्टर_with_ierb(pdev);
	अगर (err == -EPROBE_DEFER)
		वापस err;
	अगर (err)
		dev_warn(&pdev->dev,
			 "Could not register with IERB driver: %pe, please update the device tree\n",
			 ERR_PTR(err));

	err = enetc_pci_probe(pdev, KBUILD_MODNAME, माप(*pf));
	अगर (err) अणु
		dev_err(&pdev->dev, "PCI probing failed\n");
		वापस err;
	पूर्ण

	si = pci_get_drvdata(pdev);
	अगर (!si->hw.port || !si->hw.global) अणु
		err = -ENODEV;
		dev_err(&pdev->dev, "could not map PF space, probing a VF?\n");
		जाओ err_map_pf_space;
	पूर्ण

	err = enetc_setup_cbdr(&pdev->dev, &si->hw, ENETC_CBDR_DEFAULT_SIZE,
			       &si->cbd_ring);
	अगर (err)
		जाओ err_setup_cbdr;

	err = enetc_init_port_rfs_memory(si);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize RFS memory\n");
		जाओ err_init_port_rfs;
	पूर्ण

	err = enetc_init_port_rss_memory(si);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize RSS memory\n");
		जाओ err_init_port_rss;
	पूर्ण

	अगर (node && !of_device_is_available(node)) अणु
		dev_info(&pdev->dev, "device is disabled, skipping\n");
		err = -ENODEV;
		जाओ err_device_disabled;
	पूर्ण

	pf = enetc_si_priv(si);
	pf->si = si;
	pf->total_vfs = pci_sriov_get_totalvfs(pdev);

	err = enetc_setup_mac_addresses(node, pf);
	अगर (err)
		जाओ err_setup_mac_addresses;

	enetc_configure_port(pf);

	enetc_get_si_caps(si);

	ndev = alloc_etherdev_mq(माप(*priv), ENETC_MAX_NUM_TXQS);
	अगर (!ndev) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "netdev creation failed\n");
		जाओ err_alloc_netdev;
	पूर्ण

	enetc_pf_netdev_setup(si, ndev, &enetc_ndev_ops);

	priv = netdev_priv(ndev);

	enetc_init_si_rings_params(priv);

	err = enetc_alloc_si_resources(priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "SI resource alloc failed\n");
		जाओ err_alloc_si_res;
	पूर्ण

	err = enetc_configure_si(priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to configure SI\n");
		जाओ err_config_si;
	पूर्ण

	err = enetc_alloc_msix(priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "MSIX alloc failed\n");
		जाओ err_alloc_msix;
	पूर्ण

	अगर (!of_get_phy_mode(node, &pf->अगर_mode)) अणु
		err = enetc_mdiobus_create(pf, node);
		अगर (err)
			जाओ err_mdiobus_create;

		err = enetc_phylink_create(priv, node);
		अगर (err)
			जाओ err_phylink_create;
	पूर्ण

	err = रेजिस्टर_netdev(ndev);
	अगर (err)
		जाओ err_reg_netdev;

	वापस 0;

err_reg_netdev:
	enetc_phylink_destroy(priv);
err_phylink_create:
	enetc_mdiobus_destroy(pf);
err_mdiobus_create:
	enetc_मुक्त_msix(priv);
err_config_si:
err_alloc_msix:
	enetc_मुक्त_si_resources(priv);
err_alloc_si_res:
	si->ndev = शून्य;
	मुक्त_netdev(ndev);
err_alloc_netdev:
err_init_port_rss:
err_init_port_rfs:
err_device_disabled:
err_setup_mac_addresses:
	enetc_tearकरोwn_cbdr(&si->cbd_ring);
err_setup_cbdr:
err_map_pf_space:
	enetc_pci_हटाओ(pdev);

	वापस err;
पूर्ण

अटल व्योम enetc_pf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा enetc_si *si = pci_get_drvdata(pdev);
	काष्ठा enetc_pf *pf = enetc_si_priv(si);
	काष्ठा enetc_ndev_priv *priv;

	priv = netdev_priv(si->ndev);

	अगर (pf->num_vfs)
		enetc_sriov_configure(pdev, 0);

	unरेजिस्टर_netdev(si->ndev);

	enetc_phylink_destroy(priv);
	enetc_mdiobus_destroy(pf);

	enetc_मुक्त_msix(priv);

	enetc_मुक्त_si_resources(priv);
	enetc_tearकरोwn_cbdr(&si->cbd_ring);

	मुक्त_netdev(si->ndev);

	enetc_pci_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id enetc_pf_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_FREESCALE, ENETC_DEV_ID_PF) पूर्ण,
	अणु 0, पूर्ण /* End of table. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, enetc_pf_id_table);

अटल काष्ठा pci_driver enetc_pf_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = enetc_pf_id_table,
	.probe = enetc_pf_probe,
	.हटाओ = enetc_pf_हटाओ,
#अगर_घोषित CONFIG_PCI_IOV
	.sriov_configure = enetc_sriov_configure,
#पूर्ण_अगर
पूर्ण;
module_pci_driver(enetc_pf_driver);

MODULE_DESCRIPTION(ENETC_DRV_NAME_STR);
MODULE_LICENSE("Dual BSD/GPL");
