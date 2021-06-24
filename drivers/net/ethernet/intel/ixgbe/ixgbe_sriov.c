<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_bridge.h>
#अगर_घोषित NETIF_F_HW_VLAN_CTAG_TX
#समावेश <linux/अगर_vlan.h>
#पूर्ण_अगर

#समावेश "ixgbe.h"
#समावेश "ixgbe_type.h"
#समावेश "ixgbe_sriov.h"

#अगर_घोषित CONFIG_PCI_IOV
अटल अंतरभूत व्योम ixgbe_alloc_vf_macvlans(काष्ठा ixgbe_adapter *adapter,
					   अचिन्हित पूर्णांक num_vfs)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा vf_macvlans *mv_list;
	पूर्णांक num_vf_macvlans, i;

	num_vf_macvlans = hw->mac.num_rar_entries -
			  (IXGBE_MAX_PF_MACVLANS + 1 + num_vfs);
	अगर (!num_vf_macvlans)
		वापस;

	mv_list = kसुस्मृति(num_vf_macvlans, माप(काष्ठा vf_macvlans),
			  GFP_KERNEL);
	अगर (mv_list) अणु
		/* Initialize list of VF macvlans */
		INIT_LIST_HEAD(&adapter->vf_mvs.l);
		क्रम (i = 0; i < num_vf_macvlans; i++) अणु
			mv_list[i].vf = -1;
			mv_list[i].मुक्त = true;
			list_add(&mv_list[i].l, &adapter->vf_mvs.l);
		पूर्ण
		adapter->mv_list = mv_list;
	पूर्ण
पूर्ण

अटल पूर्णांक __ixgbe_enable_sriov(काष्ठा ixgbe_adapter *adapter,
				अचिन्हित पूर्णांक num_vfs)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	अगर (adapter->xdp_prog) अणु
		e_warn(probe, "SRIOV is not supported with XDP\n");
		वापस -EINVAL;
	पूर्ण

	/* Enable VMDq flag so device will be set in VM mode */
	adapter->flags |= IXGBE_FLAG_SRIOV_ENABLED |
			  IXGBE_FLAG_VMDQ_ENABLED;

	/* Allocate memory क्रम per VF control काष्ठाures */
	adapter->vfinfo = kसुस्मृति(num_vfs, माप(काष्ठा vf_data_storage),
				  GFP_KERNEL);
	अगर (!adapter->vfinfo)
		वापस -ENOMEM;

	adapter->num_vfs = num_vfs;

	ixgbe_alloc_vf_macvlans(adapter, num_vfs);
	adapter->ring_feature[RING_F_VMDQ].offset = num_vfs;

	/* Initialize शेष चयनing mode VEB */
	IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, IXGBE_PFDTXGSWC_VT_LBEN);
	adapter->bridge_mode = BRIDGE_MODE_VEB;

	/* limit trafffic classes based on VFs enabled */
	अगर ((adapter->hw.mac.type == ixgbe_mac_82599EB) && (num_vfs < 16)) अणु
		adapter->dcb_cfg.num_tcs.pg_tcs = MAX_TRAFFIC_CLASS;
		adapter->dcb_cfg.num_tcs.pfc_tcs = MAX_TRAFFIC_CLASS;
	पूर्ण अन्यथा अगर (num_vfs < 32) अणु
		adapter->dcb_cfg.num_tcs.pg_tcs = 4;
		adapter->dcb_cfg.num_tcs.pfc_tcs = 4;
	पूर्ण अन्यथा अणु
		adapter->dcb_cfg.num_tcs.pg_tcs = 1;
		adapter->dcb_cfg.num_tcs.pfc_tcs = 1;
	पूर्ण

	/* Disable RSC when in SR-IOV mode */
	adapter->flags2 &= ~(IXGBE_FLAG2_RSC_CAPABLE |
			     IXGBE_FLAG2_RSC_ENABLED);

	क्रम (i = 0; i < num_vfs; i++) अणु
		/* enable spoof checking क्रम all VFs */
		adapter->vfinfo[i].spoofchk_enabled = true;

		/* We support VF RSS querying only क्रम 82599 and x540
		 * devices at the moment. These devices share RSS
		 * indirection table and RSS hash key with PF thereक्रमe
		 * we want to disable the querying by शेष.
		 */
		adapter->vfinfo[i].rss_query_enabled = false;

		/* Untrust all VFs */
		adapter->vfinfo[i].trusted = false;

		/* set the शेष xcast mode */
		adapter->vfinfo[i].xcast_mode = IXGBEVF_XCAST_MODE_NONE;
	पूर्ण

	e_info(probe, "SR-IOV enabled with %d VFs\n", num_vfs);
	वापस 0;
पूर्ण

/**
 * ixgbe_get_vfs - Find and take references to all vf devices
 * @adapter: Poपूर्णांकer to adapter काष्ठा
 */
अटल व्योम ixgbe_get_vfs(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	u16 venकरोr = pdev->venकरोr;
	काष्ठा pci_dev *vfdev;
	पूर्णांक vf = 0;
	u16 vf_id;
	पूर्णांक pos;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	अगर (!pos)
		वापस;
	pci_पढ़ो_config_word(pdev, pos + PCI_SRIOV_VF_DID, &vf_id);

	vfdev = pci_get_device(venकरोr, vf_id, शून्य);
	क्रम (; vfdev; vfdev = pci_get_device(venकरोr, vf_id, vfdev)) अणु
		अगर (!vfdev->is_virtfn)
			जारी;
		अगर (vfdev->physfn != pdev)
			जारी;
		अगर (vf >= adapter->num_vfs)
			जारी;
		pci_dev_get(vfdev);
		adapter->vfinfo[vf].vfdev = vfdev;
		++vf;
	पूर्ण
पूर्ण

/* Note this function is called when the user wants to enable SR-IOV
 * VFs using the now deprecated module parameter
 */
व्योम ixgbe_enable_sriov(काष्ठा ixgbe_adapter *adapter, अचिन्हित पूर्णांक max_vfs)
अणु
	पूर्णांक pre_existing_vfs = 0;
	अचिन्हित पूर्णांक num_vfs;

	pre_existing_vfs = pci_num_vf(adapter->pdev);
	अगर (!pre_existing_vfs && !max_vfs)
		वापस;

	/* If there are pre-existing VFs then we have to क्रमce
	 * use of that many - over ride any module parameter value.
	 * This may result from the user unloading the PF driver
	 * जबतक VFs were asचिन्हित to guest VMs or because the VFs
	 * have been created via the new PCI SR-IOV sysfs पूर्णांकerface.
	 */
	अगर (pre_existing_vfs) अणु
		num_vfs = pre_existing_vfs;
		dev_warn(&adapter->pdev->dev,
			 "Virtual Functions already enabled for this device - Please reload all VF drivers to avoid spoofed packet errors\n");
	पूर्ण अन्यथा अणु
		पूर्णांक err;
		/*
		 * The 82599 supports up to 64 VFs per physical function
		 * but this implementation limits allocation to 63 so that
		 * basic networking resources are still available to the
		 * physical function.  If the user requests greater than
		 * 63 VFs then it is an error - reset to शेष of zero.
		 */
		num_vfs = min_t(अचिन्हित पूर्णांक, max_vfs, IXGBE_MAX_VFS_DRV_LIMIT);

		err = pci_enable_sriov(adapter->pdev, num_vfs);
		अगर (err) अणु
			e_err(probe, "Failed to enable PCI sriov: %d\n", err);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!__ixgbe_enable_sriov(adapter, num_vfs)) अणु
		ixgbe_get_vfs(adapter);
		वापस;
	पूर्ण

	/* If we have gotten to this poपूर्णांक then there is no memory available
	 * to manage the VF devices - prपूर्णांक message and bail.
	 */
	e_err(probe, "Unable to allocate memory for VF Data Storage - "
	      "SRIOV disabled\n");
	ixgbe_disable_sriov(adapter);
पूर्ण

#पूर्ण_अगर /* #अगर_घोषित CONFIG_PCI_IOV */
पूर्णांक ixgbe_disable_sriov(काष्ठा ixgbe_adapter *adapter)
अणु
	अचिन्हित पूर्णांक num_vfs = adapter->num_vfs, vf;
	पूर्णांक rss;

	/* set num VFs to 0 to prevent access to vfinfo */
	adapter->num_vfs = 0;

	/* put the reference to all of the vf devices */
	क्रम (vf = 0; vf < num_vfs; ++vf) अणु
		काष्ठा pci_dev *vfdev = adapter->vfinfo[vf].vfdev;

		अगर (!vfdev)
			जारी;
		adapter->vfinfo[vf].vfdev = शून्य;
		pci_dev_put(vfdev);
	पूर्ण

	/* मुक्त VF control काष्ठाures */
	kमुक्त(adapter->vfinfo);
	adapter->vfinfo = शून्य;

	/* मुक्त macvlan list */
	kमुक्त(adapter->mv_list);
	adapter->mv_list = शून्य;

	/* अगर SR-IOV is alपढ़ोy disabled then there is nothing to करो */
	अगर (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		वापस 0;

#अगर_घोषित CONFIG_PCI_IOV
	/*
	 * If our VFs are asचिन्हित we cannot shut करोwn SR-IOV
	 * without causing issues, so just leave the hardware
	 * available but disabled
	 */
	अगर (pci_vfs_asचिन्हित(adapter->pdev)) अणु
		e_dev_warn("Unloading driver while VFs are assigned - VFs will not be deallocated\n");
		वापस -EPERM;
	पूर्ण
	/* disable iov and allow समय क्रम transactions to clear */
	pci_disable_sriov(adapter->pdev);
#पूर्ण_अगर

	/* Disable VMDq flag so device will be set in VM mode */
	अगर (biपंचांगap_weight(adapter->fwd_biपंचांगask, adapter->num_rx_pools) == 1) अणु
		adapter->flags &= ~IXGBE_FLAG_VMDQ_ENABLED;
		adapter->flags &= ~IXGBE_FLAG_SRIOV_ENABLED;
		rss = min_t(पूर्णांक, ixgbe_max_rss_indices(adapter),
			    num_online_cpus());
	पूर्ण अन्यथा अणु
		rss = min_t(पूर्णांक, IXGBE_MAX_L2A_QUEUES, num_online_cpus());
	पूर्ण

	adapter->ring_feature[RING_F_VMDQ].offset = 0;
	adapter->ring_feature[RING_F_RSS].limit = rss;

	/* take a breather then clean up driver data */
	msleep(100);
	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_pci_sriov_enable(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(dev);
	पूर्णांक pre_existing_vfs = pci_num_vf(dev);
	पूर्णांक err = 0, num_rx_pools, i, limit;
	u8 num_tc;

	अगर (pre_existing_vfs && pre_existing_vfs != num_vfs)
		err = ixgbe_disable_sriov(adapter);
	अन्यथा अगर (pre_existing_vfs && pre_existing_vfs == num_vfs)
		वापस num_vfs;

	अगर (err)
		वापस err;

	/* While the SR-IOV capability काष्ठाure reports total VFs to be 64,
	 * we limit the actual number allocated as below based on two factors.
	 *    Num_TCs	MAX_VFs
	 *	1	  63
	 *	<=4	  31
	 *	>4	  15
	 * First, we reserve some transmit/receive resources क्रम the PF.
	 * Second, VMDQ also uses the same pools that SR-IOV करोes. We need to
	 * account क्रम this, so that we करोn't accidentally allocate more VFs
	 * than we have available pools. The PCI bus driver alपढ़ोy checks क्रम
	 * other values out of range.
	 */
	num_tc = adapter->hw_tcs;
	num_rx_pools = biपंचांगap_weight(adapter->fwd_biपंचांगask,
				     adapter->num_rx_pools);
	limit = (num_tc > 4) ? IXGBE_MAX_VFS_8TC :
		(num_tc > 1) ? IXGBE_MAX_VFS_4TC : IXGBE_MAX_VFS_1TC;

	अगर (num_vfs > (limit - num_rx_pools)) अणु
		e_dev_err("Currently configured with %d TCs, and %d offloaded macvlans. Creating more than %d VFs is not allowed\n",
			  num_tc, num_rx_pools - 1, limit - num_rx_pools);
		वापस -EPERM;
	पूर्ण

	err = __ixgbe_enable_sriov(adapter, num_vfs);
	अगर (err)
		वापस  err;

	क्रम (i = 0; i < num_vfs; i++)
		ixgbe_vf_configuration(dev, (i | 0x10000000));

	/* reset beक्रमe enabling SRIOV to aव्योम mailbox issues */
	ixgbe_sriov_reinit(adapter);

	err = pci_enable_sriov(dev, num_vfs);
	अगर (err) अणु
		e_dev_warn("Failed to enable PCI sriov: %d\n", err);
		वापस err;
	पूर्ण
	ixgbe_get_vfs(adapter);

	वापस num_vfs;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ixgbe_pci_sriov_disable(काष्ठा pci_dev *dev)
अणु
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(dev);
	पूर्णांक err;
#अगर_घोषित CONFIG_PCI_IOV
	u32 current_flags = adapter->flags;
	पूर्णांक prev_num_vf = pci_num_vf(dev);
#पूर्ण_अगर

	err = ixgbe_disable_sriov(adapter);

	/* Only reinit अगर no error and state changed */
#अगर_घोषित CONFIG_PCI_IOV
	अगर (!err && (current_flags != adapter->flags ||
		     prev_num_vf != pci_num_vf(dev)))
		ixgbe_sriov_reinit(adapter);
#पूर्ण_अगर

	वापस err;
पूर्ण

पूर्णांक ixgbe_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
	अगर (num_vfs == 0)
		वापस ixgbe_pci_sriov_disable(dev);
	अन्यथा
		वापस ixgbe_pci_sriov_enable(dev, num_vfs);
पूर्ण

अटल पूर्णांक ixgbe_set_vf_multicasts(काष्ठा ixgbe_adapter *adapter,
				   u32 *msgbuf, u32 vf)
अणु
	पूर्णांक entries = (msgbuf[0] & IXGBE_VT_MSGINFO_MASK)
		       >> IXGBE_VT_MSGINFO_SHIFT;
	u16 *hash_list = (u16 *)&msgbuf[1];
	काष्ठा vf_data_storage *vfinfo = &adapter->vfinfo[vf];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;
	u32 vector_bit;
	u32 vector_reg;
	u32 mta_reg;
	u32 vmolr = IXGBE_READ_REG(hw, IXGBE_VMOLR(vf));

	/* only so many hash values supported */
	entries = min(entries, IXGBE_MAX_VF_MC_ENTRIES);

	/*
	 * salt away the number of multi cast addresses asचिन्हित
	 * to this VF क्रम later use to restore when the PF multi cast
	 * list changes
	 */
	vfinfo->num_vf_mc_hashes = entries;

	/*
	 * VFs are limited to using the MTA hash table क्रम their multicast
	 * addresses
	 */
	क्रम (i = 0; i < entries; i++) अणु
		vfinfo->vf_mc_hashes[i] = hash_list[i];
	पूर्ण

	क्रम (i = 0; i < vfinfo->num_vf_mc_hashes; i++) अणु
		vector_reg = (vfinfo->vf_mc_hashes[i] >> 5) & 0x7F;
		vector_bit = vfinfo->vf_mc_hashes[i] & 0x1F;
		mta_reg = IXGBE_READ_REG(hw, IXGBE_MTA(vector_reg));
		mta_reg |= BIT(vector_bit);
		IXGBE_WRITE_REG(hw, IXGBE_MTA(vector_reg), mta_reg);
	पूर्ण
	vmolr |= IXGBE_VMOLR_ROMPE;
	IXGBE_WRITE_REG(hw, IXGBE_VMOLR(vf), vmolr);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_restore_vf_multicasts(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा vf_data_storage *vfinfo;
	पूर्णांक i, j;
	u32 vector_bit;
	u32 vector_reg;
	u32 mta_reg;

	क्रम (i = 0; i < adapter->num_vfs; i++) अणु
		u32 vmolr = IXGBE_READ_REG(hw, IXGBE_VMOLR(i));
		vfinfo = &adapter->vfinfo[i];
		क्रम (j = 0; j < vfinfo->num_vf_mc_hashes; j++) अणु
			hw->addr_ctrl.mta_in_use++;
			vector_reg = (vfinfo->vf_mc_hashes[j] >> 5) & 0x7F;
			vector_bit = vfinfo->vf_mc_hashes[j] & 0x1F;
			mta_reg = IXGBE_READ_REG(hw, IXGBE_MTA(vector_reg));
			mta_reg |= BIT(vector_bit);
			IXGBE_WRITE_REG(hw, IXGBE_MTA(vector_reg), mta_reg);
		पूर्ण

		अगर (vfinfo->num_vf_mc_hashes)
			vmolr |= IXGBE_VMOLR_ROMPE;
		अन्यथा
			vmolr &= ~IXGBE_VMOLR_ROMPE;
		IXGBE_WRITE_REG(hw, IXGBE_VMOLR(i), vmolr);
	पूर्ण

	/* Restore any VF macvlans */
	ixgbe_full_sync_mac_table(adapter);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ixgbe_set_vf_vlan(काष्ठा ixgbe_adapter *adapter, पूर्णांक add, पूर्णांक vid,
			     u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* If VLAN overlaps with one the PF is currently monitoring make
	 * sure that we are able to allocate a VLVF entry.  This may be
	 * redundant but it guarantees PF will मुख्यtain visibility to
	 * the VLAN.
	 */
	अगर (add && test_bit(vid, adapter->active_vlans)) अणु
		err = hw->mac.ops.set_vfta(hw, vid, VMDQ_P(0), true, false);
		अगर (err)
			वापस err;
	पूर्ण

	err = hw->mac.ops.set_vfta(hw, vid, vf, !!add, false);

	अगर (add && !err)
		वापस err;

	/* If we failed to add the VF VLAN or we are removing the VF VLAN
	 * we may need to drop the PF pool bit in order to allow us to मुक्त
	 * up the VLVF resources.
	 */
	अगर (test_bit(vid, adapter->active_vlans) ||
	    (adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
		ixgbe_update_pf_promisc_vlvf(adapter, vid);

	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_set_vf_lpe(काष्ठा ixgbe_adapter *adapter, u32 max_frame, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 max_frs;

	अगर (max_frame < ETH_MIN_MTU || max_frame > IXGBE_MAX_JUMBO_FRAME_SIZE) अणु
		e_err(drv, "VF max_frame %d out of range\n", max_frame);
		वापस -EINVAL;
	पूर्ण

	/*
	 * For 82599EB we have to keep all PFs and VFs operating with
	 * the same max_frame value in order to aव्योम sending an oversize
	 * frame to a VF.  In order to guarantee this is handled correctly
	 * क्रम all हालs we have several special exceptions to take पूर्णांकo
	 * account beक्रमe we can enable the VF क्रम receive
	 */
	अगर (adapter->hw.mac.type == ixgbe_mac_82599EB) अणु
		काष्ठा net_device *dev = adapter->netdev;
		पूर्णांक pf_max_frame = dev->mtu + ETH_HLEN;
		u32 reg_offset, vf_shअगरt, vfre;
		s32 err = 0;

#अगर_घोषित CONFIG_FCOE
		अगर (dev->features & NETIF_F_FCOE_MTU)
			pf_max_frame = max_t(पूर्णांक, pf_max_frame,
					     IXGBE_FCOE_JUMBO_FRAME_SIZE);

#पूर्ण_अगर /* CONFIG_FCOE */
		चयन (adapter->vfinfo[vf].vf_api) अणु
		हाल ixgbe_mbox_api_11:
		हाल ixgbe_mbox_api_12:
		हाल ixgbe_mbox_api_13:
		हाल ixgbe_mbox_api_14:
			/* Version 1.1 supports jumbo frames on VFs अगर PF has
			 * jumbo frames enabled which means legacy VFs are
			 * disabled
			 */
			अगर (pf_max_frame > ETH_FRAME_LEN)
				अवरोध;
			fallthrough;
		शेष:
			/* If the PF or VF are running w/ jumbo frames enabled
			 * we need to shut करोwn the VF Rx path as we cannot
			 * support jumbo frames on legacy VFs
			 */
			अगर ((pf_max_frame > ETH_FRAME_LEN) ||
			    (max_frame > (ETH_FRAME_LEN + ETH_FCS_LEN)))
				err = -EINVAL;
			अवरोध;
		पूर्ण

		/* determine VF receive enable location */
		vf_shअगरt = vf % 32;
		reg_offset = vf / 32;

		/* enable or disable receive depending on error */
		vfre = IXGBE_READ_REG(hw, IXGBE_VFRE(reg_offset));
		अगर (err)
			vfre &= ~BIT(vf_shअगरt);
		अन्यथा
			vfre |= BIT(vf_shअगरt);
		IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset), vfre);

		अगर (err) अणु
			e_err(drv, "VF max_frame %d out of range\n", max_frame);
			वापस err;
		पूर्ण
	पूर्ण

	/* pull current max frame size from hardware */
	max_frs = IXGBE_READ_REG(hw, IXGBE_MAXFRS);
	max_frs &= IXGBE_MHADD_MFS_MASK;
	max_frs >>= IXGBE_MHADD_MFS_SHIFT;

	अगर (max_frs < max_frame) अणु
		max_frs = max_frame << IXGBE_MHADD_MFS_SHIFT;
		IXGBE_WRITE_REG(hw, IXGBE_MAXFRS, max_frs);
	पूर्ण

	e_info(hw, "VF requests change max MTU to %d\n", max_frame);

	वापस 0;
पूर्ण

अटल व्योम ixgbe_set_vmolr(काष्ठा ixgbe_hw *hw, u32 vf, bool aupe)
अणु
	u32 vmolr = IXGBE_READ_REG(hw, IXGBE_VMOLR(vf));
	vmolr |= IXGBE_VMOLR_BAM;
	अगर (aupe)
		vmolr |= IXGBE_VMOLR_AUPE;
	अन्यथा
		vmolr &= ~IXGBE_VMOLR_AUPE;
	IXGBE_WRITE_REG(hw, IXGBE_VMOLR(vf), vmolr);
पूर्ण

अटल व्योम ixgbe_clear_vmvir(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	IXGBE_WRITE_REG(hw, IXGBE_VMVIR(vf), 0);
पूर्ण

अटल व्योम ixgbe_clear_vf_vlans(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vlvfb_mask, pool_mask, i;

	/* create mask क्रम VF and other pools */
	pool_mask = ~BIT(VMDQ_P(0) % 32);
	vlvfb_mask = BIT(vf % 32);

	/* post increment loop, covers VLVF_ENTRIES - 1 to 0 */
	क्रम (i = IXGBE_VLVF_ENTRIES; i--;) अणु
		u32 bits[2], vlvfb, vid, vfta, vlvf;
		u32 word = i * 2 + vf / 32;
		u32 mask;

		vlvfb = IXGBE_READ_REG(hw, IXGBE_VLVFB(word));

		/* अगर our bit isn't set we can skip it */
		अगर (!(vlvfb & vlvfb_mask))
			जारी;

		/* clear our bit from vlvfb */
		vlvfb ^= vlvfb_mask;

		/* create 64b mask to chedk to see अगर we should clear VLVF */
		bits[word % 2] = vlvfb;
		bits[~word % 2] = IXGBE_READ_REG(hw, IXGBE_VLVFB(word ^ 1));

		/* अगर other pools are present, just हटाओ ourselves */
		अगर (bits[(VMDQ_P(0) / 32) ^ 1] ||
		    (bits[VMDQ_P(0) / 32] & pool_mask))
			जाओ update_vlvfb;

		/* अगर PF is present, leave VFTA */
		अगर (bits[0] || bits[1])
			जाओ update_vlvf;

		/* अगर we cannot determine VLAN just हटाओ ourselves */
		vlvf = IXGBE_READ_REG(hw, IXGBE_VLVF(i));
		अगर (!vlvf)
			जाओ update_vlvfb;

		vid = vlvf & VLAN_VID_MASK;
		mask = BIT(vid % 32);

		/* clear bit from VFTA */
		vfta = IXGBE_READ_REG(hw, IXGBE_VFTA(vid / 32));
		अगर (vfta & mask)
			IXGBE_WRITE_REG(hw, IXGBE_VFTA(vid / 32), vfta ^ mask);
update_vlvf:
		/* clear POOL selection enable */
		IXGBE_WRITE_REG(hw, IXGBE_VLVF(i), 0);

		अगर (!(adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
			vlvfb = 0;
update_vlvfb:
		/* clear pool bits */
		IXGBE_WRITE_REG(hw, IXGBE_VLVFB(word), vlvfb);
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_set_vf_macvlan(काष्ठा ixgbe_adapter *adapter,
				पूर्णांक vf, पूर्णांक index, अचिन्हित अक्षर *mac_addr)
अणु
	काष्ठा vf_macvlans *entry;
	काष्ठा list_head *pos;
	पूर्णांक retval = 0;

	अगर (index <= 1) अणु
		list_क्रम_each(pos, &adapter->vf_mvs.l) अणु
			entry = list_entry(pos, काष्ठा vf_macvlans, l);
			अगर (entry->vf == vf) अणु
				entry->vf = -1;
				entry->मुक्त = true;
				entry->is_macvlan = false;
				ixgbe_del_mac_filter(adapter,
						     entry->vf_macvlan, vf);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If index was zero then we were asked to clear the uc list
	 * क्रम the VF.  We're करोne.
	 */
	अगर (!index)
		वापस 0;

	entry = शून्य;

	list_क्रम_each(pos, &adapter->vf_mvs.l) अणु
		entry = list_entry(pos, काष्ठा vf_macvlans, l);
		अगर (entry->मुक्त)
			अवरोध;
	पूर्ण

	/*
	 * If we traversed the entire list and didn't find a मुक्त entry
	 * then we're out of space on the RAR table.  Also entry may
	 * be शून्य because the original memory allocation क्रम the list
	 * failed, which is not fatal but करोes mean we can't support
	 * VF requests क्रम MACVLAN because we couldn't allocate
	 * memory क्रम the list management required.
	 */
	अगर (!entry || !entry->मुक्त)
		वापस -ENOSPC;

	retval = ixgbe_add_mac_filter(adapter, mac_addr, vf);
	अगर (retval < 0)
		वापस retval;

	entry->मुक्त = false;
	entry->is_macvlan = true;
	entry->vf = vf;
	स_नकल(entry->vf_macvlan, mac_addr, ETH_ALEN);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ixgbe_vf_reset_event(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	काष्ठा vf_data_storage *vfinfo = &adapter->vfinfo[vf];
	u32 q_per_pool = __ALIGN_MASK(1, ~vmdq->mask);
	u8 num_tcs = adapter->hw_tcs;
	u32 reg_val;
	u32 queue;

	/* हटाओ VLAN filters beloning to this VF */
	ixgbe_clear_vf_vlans(adapter, vf);

	/* add back PF asचिन्हित VLAN or VLAN 0 */
	ixgbe_set_vf_vlan(adapter, true, vfinfo->pf_vlan, vf);

	/* reset offloads to शेषs */
	ixgbe_set_vmolr(hw, vf, !vfinfo->pf_vlan);

	/* set outgoing tags क्रम VFs */
	अगर (!vfinfo->pf_vlan && !vfinfo->pf_qos && !num_tcs) अणु
		ixgbe_clear_vmvir(adapter, vf);
	पूर्ण अन्यथा अणु
		अगर (vfinfo->pf_qos || !num_tcs)
			ixgbe_set_vmvir(adapter, vfinfo->pf_vlan,
					vfinfo->pf_qos, vf);
		अन्यथा
			ixgbe_set_vmvir(adapter, vfinfo->pf_vlan,
					adapter->शेष_up, vf);

		अगर (vfinfo->spoofchk_enabled) अणु
			hw->mac.ops.set_vlan_anti_spoofing(hw, true, vf);
			hw->mac.ops.set_mac_anti_spoofing(hw, true, vf);
		पूर्ण
	पूर्ण

	/* reset multicast table array क्रम vf */
	adapter->vfinfo[vf].num_vf_mc_hashes = 0;

	/* clear any ipsec table info */
	ixgbe_ipsec_vf_clear(adapter, vf);

	/* Flush and reset the mta with the new values */
	ixgbe_set_rx_mode(adapter->netdev);

	ixgbe_del_mac_filter(adapter, adapter->vfinfo[vf].vf_mac_addresses, vf);
	ixgbe_set_vf_macvlan(adapter, vf, 0, शून्य);

	/* reset VF api back to unknown */
	adapter->vfinfo[vf].vf_api = ixgbe_mbox_api_10;

	/* Restart each queue क्रम given VF */
	क्रम (queue = 0; queue < q_per_pool; queue++) अणु
		अचिन्हित पूर्णांक reg_idx = (vf * q_per_pool) + queue;

		reg_val = IXGBE_READ_REG(hw, IXGBE_PVFTXDCTL(reg_idx));

		/* Re-enabling only configured queues */
		अगर (reg_val) अणु
			reg_val |= IXGBE_TXDCTL_ENABLE;
			IXGBE_WRITE_REG(hw, IXGBE_PVFTXDCTL(reg_idx), reg_val);
			reg_val &= ~IXGBE_TXDCTL_ENABLE;
			IXGBE_WRITE_REG(hw, IXGBE_PVFTXDCTL(reg_idx), reg_val);
		पूर्ण
	पूर्ण

	IXGBE_WRITE_FLUSH(hw);
पूर्ण

अटल व्योम ixgbe_vf_clear_mbx(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 word;

	/* Clear VF's mailbox memory */
	क्रम (word = 0; word < IXGBE_VFMAILBOX_SIZE; word++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_PFMBMEM(vf), word, 0);

	IXGBE_WRITE_FLUSH(hw);
पूर्ण

अटल पूर्णांक ixgbe_set_vf_mac(काष्ठा ixgbe_adapter *adapter,
			    पूर्णांक vf, अचिन्हित अक्षर *mac_addr)
अणु
	s32 retval;

	ixgbe_del_mac_filter(adapter, adapter->vfinfo[vf].vf_mac_addresses, vf);
	retval = ixgbe_add_mac_filter(adapter, mac_addr, vf);
	अगर (retval >= 0)
		स_नकल(adapter->vfinfo[vf].vf_mac_addresses, mac_addr,
		       ETH_ALEN);
	अन्यथा
		eth_zero_addr(adapter->vfinfo[vf].vf_mac_addresses);

	वापस retval;
पूर्ण

पूर्णांक ixgbe_vf_configuration(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक event_mask)
अणु
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	अचिन्हित पूर्णांक vfn = (event_mask & 0x3f);

	bool enable = ((event_mask & 0x10000000U) != 0);

	अगर (enable)
		eth_zero_addr(adapter->vfinfo[vfn].vf_mac_addresses);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ixgbe_ग_लिखो_qde(काष्ठा ixgbe_adapter *adapter, u32 vf,
				   u32 qde)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	u32 q_per_pool = __ALIGN_MASK(1, ~vmdq->mask);
	पूर्णांक i;

	क्रम (i = vf * q_per_pool; i < ((vf + 1) * q_per_pool); i++) अणु
		u32 reg;

		/* flush previous ग_लिखो */
		IXGBE_WRITE_FLUSH(hw);

		/* indicate to hardware that we want to set drop enable */
		reg = IXGBE_QDE_WRITE | qde;
		reg |= i <<  IXGBE_QDE_IDX_SHIFT;
		IXGBE_WRITE_REG(hw, IXGBE_QDE, reg);
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_vf_reset_msg(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अचिन्हित अक्षर *vf_mac = adapter->vfinfo[vf].vf_mac_addresses;
	u32 reg, reg_offset, vf_shअगरt;
	u32 msgbuf[4] = अणु0, 0, 0, 0पूर्ण;
	u8 *addr = (u8 *)(&msgbuf[1]);
	u32 q_per_pool = __ALIGN_MASK(1, ~vmdq->mask);
	पूर्णांक i;

	e_info(probe, "VF Reset msg received from vf %d\n", vf);

	/* reset the filters क्रम the device */
	ixgbe_vf_reset_event(adapter, vf);

	ixgbe_vf_clear_mbx(adapter, vf);

	/* set vf mac address */
	अगर (!is_zero_ether_addr(vf_mac))
		ixgbe_set_vf_mac(adapter, vf, vf_mac);

	vf_shअगरt = vf % 32;
	reg_offset = vf / 32;

	/* enable transmit क्रम vf */
	reg = IXGBE_READ_REG(hw, IXGBE_VFTE(reg_offset));
	reg |= BIT(vf_shअगरt);
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(reg_offset), reg);

	/* क्रमce drop enable क्रम all VF Rx queues */
	reg = IXGBE_QDE_ENABLE;
	अगर (adapter->vfinfo[vf].pf_vlan)
		reg |= IXGBE_QDE_HIDE_VLAN;

	ixgbe_ग_लिखो_qde(adapter, vf, reg);

	/* enable receive क्रम vf */
	reg = IXGBE_READ_REG(hw, IXGBE_VFRE(reg_offset));
	reg |= BIT(vf_shअगरt);
	/*
	 * The 82599 cannot support a mix of jumbo and non-jumbo PF/VFs.
	 * For more info take a look at ixgbe_set_vf_lpe
	 */
	अगर (adapter->hw.mac.type == ixgbe_mac_82599EB) अणु
		काष्ठा net_device *dev = adapter->netdev;
		पूर्णांक pf_max_frame = dev->mtu + ETH_HLEN;

#अगर_घोषित CONFIG_FCOE
		अगर (dev->features & NETIF_F_FCOE_MTU)
			pf_max_frame = max_t(पूर्णांक, pf_max_frame,
					     IXGBE_FCOE_JUMBO_FRAME_SIZE);

#पूर्ण_अगर /* CONFIG_FCOE */
		अगर (pf_max_frame > ETH_FRAME_LEN)
			reg &= ~BIT(vf_shअगरt);
	पूर्ण
	IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset), reg);

	/* enable VF mailbox क्रम further messages */
	adapter->vfinfo[vf].clear_to_send = true;

	/* Enable counting of spoofed packets in the SSVPC रेजिस्टर */
	reg = IXGBE_READ_REG(hw, IXGBE_VMECM(reg_offset));
	reg |= BIT(vf_shअगरt);
	IXGBE_WRITE_REG(hw, IXGBE_VMECM(reg_offset), reg);

	/*
	 * Reset the VFs TDWBAL and TDWBAH रेजिस्टरs
	 * which are not cleared by an FLR
	 */
	क्रम (i = 0; i < q_per_pool; i++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_PVFTDWBAHn(q_per_pool, vf, i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_PVFTDWBALn(q_per_pool, vf, i), 0);
	पूर्ण

	/* reply to reset with ack and vf mac address */
	msgbuf[0] = IXGBE_VF_RESET;
	अगर (!is_zero_ether_addr(vf_mac) && adapter->vfinfo[vf].pf_set_mac) अणु
		msgbuf[0] |= IXGBE_VT_MSGTYPE_ACK;
		स_नकल(addr, vf_mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		msgbuf[0] |= IXGBE_VT_MSGTYPE_NACK;
	पूर्ण

	/*
	 * Piggyback the multicast filter type so VF can compute the
	 * correct vectors
	 */
	msgbuf[3] = hw->mac.mc_filter_type;
	ixgbe_ग_लिखो_mbx(hw, msgbuf, IXGBE_VF_PERMADDR_MSG_LEN, vf);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_set_vf_mac_addr(काष्ठा ixgbe_adapter *adapter,
				 u32 *msgbuf, u32 vf)
अणु
	u8 *new_mac = ((u8 *)(&msgbuf[1]));

	अगर (!is_valid_ether_addr(new_mac)) अणु
		e_warn(drv, "VF %d attempted to set invalid mac\n", vf);
		वापस -1;
	पूर्ण

	अगर (adapter->vfinfo[vf].pf_set_mac && !adapter->vfinfo[vf].trusted &&
	    !ether_addr_equal(adapter->vfinfo[vf].vf_mac_addresses, new_mac)) अणु
		e_warn(drv,
		       "VF %d attempted to override administratively set MAC address\n"
		       "Reload the VF driver to resume operations\n",
		       vf);
		वापस -1;
	पूर्ण

	वापस ixgbe_set_vf_mac(adapter, vf, new_mac) < 0;
पूर्ण

अटल पूर्णांक ixgbe_set_vf_vlan_msg(काष्ठा ixgbe_adapter *adapter,
				 u32 *msgbuf, u32 vf)
अणु
	u32 add = (msgbuf[0] & IXGBE_VT_MSGINFO_MASK) >> IXGBE_VT_MSGINFO_SHIFT;
	u32 vid = (msgbuf[1] & IXGBE_VLVF_VLANID_MASK);
	u8 tcs = adapter->hw_tcs;

	अगर (adapter->vfinfo[vf].pf_vlan || tcs) अणु
		e_warn(drv,
		       "VF %d attempted to override administratively set VLAN configuration\n"
		       "Reload the VF driver to resume operations\n",
		       vf);
		वापस -1;
	पूर्ण

	/* VLAN 0 is a special हाल, करोn't allow it to be हटाओd */
	अगर (!vid && !add)
		वापस 0;

	वापस ixgbe_set_vf_vlan(adapter, add, vid, vf);
पूर्ण

अटल पूर्णांक ixgbe_set_vf_macvlan_msg(काष्ठा ixgbe_adapter *adapter,
				    u32 *msgbuf, u32 vf)
अणु
	u8 *new_mac = ((u8 *)(&msgbuf[1]));
	पूर्णांक index = (msgbuf[0] & IXGBE_VT_MSGINFO_MASK) >>
		    IXGBE_VT_MSGINFO_SHIFT;
	पूर्णांक err;

	अगर (adapter->vfinfo[vf].pf_set_mac && !adapter->vfinfo[vf].trusted &&
	    index > 0) अणु
		e_warn(drv,
		       "VF %d requested MACVLAN filter but is administratively denied\n",
		       vf);
		वापस -1;
	पूर्ण

	/* An non-zero index indicates the VF is setting a filter */
	अगर (index) अणु
		अगर (!is_valid_ether_addr(new_mac)) अणु
			e_warn(drv, "VF %d attempted to set invalid mac\n", vf);
			वापस -1;
		पूर्ण

		/*
		 * If the VF is allowed to set MAC filters then turn off
		 * anti-spoofing to aव्योम false positives.
		 */
		अगर (adapter->vfinfo[vf].spoofchk_enabled) अणु
			काष्ठा ixgbe_hw *hw = &adapter->hw;

			hw->mac.ops.set_mac_anti_spoofing(hw, false, vf);
			hw->mac.ops.set_vlan_anti_spoofing(hw, false, vf);
		पूर्ण
	पूर्ण

	err = ixgbe_set_vf_macvlan(adapter, vf, index, new_mac);
	अगर (err == -ENOSPC)
		e_warn(drv,
		       "VF %d has requested a MACVLAN filter but there is no space for it\n",
		       vf);

	वापस err < 0;
पूर्ण

अटल पूर्णांक ixgbe_negotiate_vf_api(काष्ठा ixgbe_adapter *adapter,
				  u32 *msgbuf, u32 vf)
अणु
	पूर्णांक api = msgbuf[1];

	चयन (api) अणु
	हाल ixgbe_mbox_api_10:
	हाल ixgbe_mbox_api_11:
	हाल ixgbe_mbox_api_12:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_14:
		adapter->vfinfo[vf].vf_api = api;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	e_info(drv, "VF %d requested invalid api version %u\n", vf, api);

	वापस -1;
पूर्ण

अटल पूर्णांक ixgbe_get_vf_queues(काष्ठा ixgbe_adapter *adapter,
			       u32 *msgbuf, u32 vf)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	अचिन्हित पूर्णांक शेष_tc = 0;
	u8 num_tcs = adapter->hw_tcs;

	/* verअगरy the PF is supporting the correct APIs */
	चयन (adapter->vfinfo[vf].vf_api) अणु
	हाल ixgbe_mbox_api_20:
	हाल ixgbe_mbox_api_11:
	हाल ixgbe_mbox_api_12:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_14:
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	/* only allow 1 Tx queue क्रम bandwidth limiting */
	msgbuf[IXGBE_VF_TX_QUEUES] = __ALIGN_MASK(1, ~vmdq->mask);
	msgbuf[IXGBE_VF_RX_QUEUES] = __ALIGN_MASK(1, ~vmdq->mask);

	/* अगर TCs > 1 determine which TC beदीर्घs to शेष user priority */
	अगर (num_tcs > 1)
		शेष_tc = netdev_get_prio_tc_map(dev, adapter->शेष_up);

	/* notअगरy VF of need क्रम VLAN tag stripping, and correct queue */
	अगर (num_tcs)
		msgbuf[IXGBE_VF_TRANS_VLAN] = num_tcs;
	अन्यथा अगर (adapter->vfinfo[vf].pf_vlan || adapter->vfinfo[vf].pf_qos)
		msgbuf[IXGBE_VF_TRANS_VLAN] = 1;
	अन्यथा
		msgbuf[IXGBE_VF_TRANS_VLAN] = 0;

	/* notअगरy VF of शेष queue */
	msgbuf[IXGBE_VF_DEF_QUEUE] = शेष_tc;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_vf_reta(काष्ठा ixgbe_adapter *adapter, u32 *msgbuf, u32 vf)
अणु
	u32 i, j;
	u32 *out_buf = &msgbuf[1];
	स्थिर u8 *reta = adapter->rss_indir_tbl;
	u32 reta_size = ixgbe_rss_indir_tbl_entries(adapter);

	/* Check अगर operation is permitted */
	अगर (!adapter->vfinfo[vf].rss_query_enabled)
		वापस -EPERM;

	/* verअगरy the PF is supporting the correct API */
	चयन (adapter->vfinfo[vf].vf_api) अणु
	हाल ixgbe_mbox_api_14:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_12:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* This mailbox command is supported (required) only क्रम 82599 and x540
	 * VFs which support up to 4 RSS queues. Thereक्रमe we will compress the
	 * RETA by saving only 2 bits from each entry. This way we will be able
	 * to transfer the whole RETA in a single mailbox operation.
	 */
	क्रम (i = 0; i < reta_size / 16; i++) अणु
		out_buf[i] = 0;
		क्रम (j = 0; j < 16; j++)
			out_buf[i] |= (u32)(reta[16 * i + j] & 0x3) << (2 * j);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_vf_rss_key(काष्ठा ixgbe_adapter *adapter,
				u32 *msgbuf, u32 vf)
अणु
	u32 *rss_key = &msgbuf[1];

	/* Check अगर the operation is permitted */
	अगर (!adapter->vfinfo[vf].rss_query_enabled)
		वापस -EPERM;

	/* verअगरy the PF is supporting the correct API */
	चयन (adapter->vfinfo[vf].vf_api) अणु
	हाल ixgbe_mbox_api_14:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_12:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	स_नकल(rss_key, adapter->rss_key, IXGBE_RSS_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_update_vf_xcast_mode(काष्ठा ixgbe_adapter *adapter,
				      u32 *msgbuf, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक xcast_mode = msgbuf[1];
	u32 vmolr, fctrl, disable, enable;

	/* verअगरy the PF is supporting the correct APIs */
	चयन (adapter->vfinfo[vf].vf_api) अणु
	हाल ixgbe_mbox_api_12:
		/* promisc पूर्णांकroduced in 1.3 version */
		अगर (xcast_mode == IXGBEVF_XCAST_MODE_PROMISC)
			वापस -EOPNOTSUPP;
		fallthrough;
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_14:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (xcast_mode > IXGBEVF_XCAST_MODE_MULTI &&
	    !adapter->vfinfo[vf].trusted) अणु
		xcast_mode = IXGBEVF_XCAST_MODE_MULTI;
	पूर्ण

	अगर (adapter->vfinfo[vf].xcast_mode == xcast_mode)
		जाओ out;

	चयन (xcast_mode) अणु
	हाल IXGBEVF_XCAST_MODE_NONE:
		disable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE |
			  IXGBE_VMOLR_MPE | IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		enable = 0;
		अवरोध;
	हाल IXGBEVF_XCAST_MODE_MULTI:
		disable = IXGBE_VMOLR_MPE | IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE;
		अवरोध;
	हाल IXGBEVF_XCAST_MODE_ALLMULTI:
		disable = IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE | IXGBE_VMOLR_MPE;
		अवरोध;
	हाल IXGBEVF_XCAST_MODE_PROMISC:
		अगर (hw->mac.type <= ixgbe_mac_82599EB)
			वापस -EOPNOTSUPP;

		fctrl = IXGBE_READ_REG(hw, IXGBE_FCTRL);
		अगर (!(fctrl & IXGBE_FCTRL_UPE)) अणु
			/* VF promisc requires PF in promisc */
			e_warn(drv,
			       "Enabling VF promisc requires PF in promisc\n");
			वापस -EPERM;
		पूर्ण

		disable = 0;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE |
			 IXGBE_VMOLR_MPE | IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	vmolr = IXGBE_READ_REG(hw, IXGBE_VMOLR(vf));
	vmolr &= ~disable;
	vmolr |= enable;
	IXGBE_WRITE_REG(hw, IXGBE_VMOLR(vf), vmolr);

	adapter->vfinfo[vf].xcast_mode = xcast_mode;

out:
	msgbuf[1] = xcast_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_rcv_msg_from_vf(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	u32 mbx_size = IXGBE_VFMAILBOX_SIZE;
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	s32 retval;

	retval = ixgbe_पढ़ो_mbx(hw, msgbuf, mbx_size, vf);

	अगर (retval) अणु
		pr_err("Error receiving message from VF\n");
		वापस retval;
	पूर्ण

	/* this is a message we alपढ़ोy processed, करो nothing */
	अगर (msgbuf[0] & (IXGBE_VT_MSGTYPE_ACK | IXGBE_VT_MSGTYPE_NACK))
		वापस 0;

	/* flush the ack beक्रमe we ग_लिखो any messages back */
	IXGBE_WRITE_FLUSH(hw);

	अगर (msgbuf[0] == IXGBE_VF_RESET)
		वापस ixgbe_vf_reset_msg(adapter, vf);

	/*
	 * until the vf completes a भव function reset it should not be
	 * allowed to start any configuration.
	 */
	अगर (!adapter->vfinfo[vf].clear_to_send) अणु
		msgbuf[0] |= IXGBE_VT_MSGTYPE_NACK;
		ixgbe_ग_लिखो_mbx(hw, msgbuf, 1, vf);
		वापस 0;
	पूर्ण

	चयन ((msgbuf[0] & 0xFFFF)) अणु
	हाल IXGBE_VF_SET_MAC_ADDR:
		retval = ixgbe_set_vf_mac_addr(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_SET_MULTICAST:
		retval = ixgbe_set_vf_multicasts(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_SET_VLAN:
		retval = ixgbe_set_vf_vlan_msg(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_SET_LPE:
		retval = ixgbe_set_vf_lpe(adapter, msgbuf[1], vf);
		अवरोध;
	हाल IXGBE_VF_SET_MACVLAN:
		retval = ixgbe_set_vf_macvlan_msg(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_API_NEGOTIATE:
		retval = ixgbe_negotiate_vf_api(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_GET_QUEUES:
		retval = ixgbe_get_vf_queues(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_GET_RETA:
		retval = ixgbe_get_vf_reta(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_GET_RSS_KEY:
		retval = ixgbe_get_vf_rss_key(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_UPDATE_XCAST_MODE:
		retval = ixgbe_update_vf_xcast_mode(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_IPSEC_ADD:
		retval = ixgbe_ipsec_vf_add_sa(adapter, msgbuf, vf);
		अवरोध;
	हाल IXGBE_VF_IPSEC_DEL:
		retval = ixgbe_ipsec_vf_del_sa(adapter, msgbuf, vf);
		अवरोध;
	शेष:
		e_err(drv, "Unhandled Msg %8.8x\n", msgbuf[0]);
		retval = IXGBE_ERR_MBX;
		अवरोध;
	पूर्ण

	/* notअगरy the VF of the results of what it sent us */
	अगर (retval)
		msgbuf[0] |= IXGBE_VT_MSGTYPE_NACK;
	अन्यथा
		msgbuf[0] |= IXGBE_VT_MSGTYPE_ACK;

	msgbuf[0] |= IXGBE_VT_MSGTYPE_CTS;

	ixgbe_ग_लिखो_mbx(hw, msgbuf, mbx_size, vf);

	वापस retval;
पूर्ण

अटल व्योम ixgbe_rcv_ack_from_vf(काष्ठा ixgbe_adapter *adapter, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 msg = IXGBE_VT_MSGTYPE_NACK;

	/* अगर device isn't clear to send it shouldn't be पढ़ोing either */
	अगर (!adapter->vfinfo[vf].clear_to_send)
		ixgbe_ग_लिखो_mbx(hw, &msg, 1, vf);
पूर्ण

व्योम ixgbe_msg_task(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vf;

	क्रम (vf = 0; vf < adapter->num_vfs; vf++) अणु
		/* process any reset requests */
		अगर (!ixgbe_check_क्रम_rst(hw, vf))
			ixgbe_vf_reset_event(adapter, vf);

		/* process any messages pending */
		अगर (!ixgbe_check_क्रम_msg(hw, vf))
			ixgbe_rcv_msg_from_vf(adapter, vf);

		/* process any acks */
		अगर (!ixgbe_check_क्रम_ack(hw, vf))
			ixgbe_rcv_ack_from_vf(adapter, vf);
	पूर्ण
पूर्ण

व्योम ixgbe_disable_tx_rx(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	/* disable transmit and receive क्रम all vfs */
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(0), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(1), 0);

	IXGBE_WRITE_REG(hw, IXGBE_VFRE(0), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFRE(1), 0);
पूर्ण

अटल अंतरभूत व्योम ixgbe_ping_vf(काष्ठा ixgbe_adapter *adapter, पूर्णांक vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 ping;

	ping = IXGBE_PF_CONTROL_MSG;
	अगर (adapter->vfinfo[vf].clear_to_send)
		ping |= IXGBE_VT_MSGTYPE_CTS;
	ixgbe_ग_लिखो_mbx(hw, &ping, 1, vf);
पूर्ण

व्योम ixgbe_ping_all_vfs(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 ping;
	पूर्णांक i;

	क्रम (i = 0 ; i < adapter->num_vfs; i++) अणु
		ping = IXGBE_PF_CONTROL_MSG;
		अगर (adapter->vfinfo[i].clear_to_send)
			ping |= IXGBE_VT_MSGTYPE_CTS;
		ixgbe_ग_लिखो_mbx(hw, &ping, 1, i);
	पूर्ण
पूर्ण

पूर्णांक ixgbe_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	s32 retval;

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	अगर (is_valid_ether_addr(mac)) अणु
		dev_info(&adapter->pdev->dev, "setting MAC %pM on VF %d\n",
			 mac, vf);
		dev_info(&adapter->pdev->dev, "Reload the VF driver to make this change effective.");

		retval = ixgbe_set_vf_mac(adapter, vf, mac);
		अगर (retval >= 0) अणु
			adapter->vfinfo[vf].pf_set_mac = true;

			अगर (test_bit(__IXGBE_DOWN, &adapter->state)) अणु
				dev_warn(&adapter->pdev->dev, "The VF MAC address has been set, but the PF device is not up.\n");
				dev_warn(&adapter->pdev->dev, "Bring the PF device up before attempting to use the VF device.\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(&adapter->pdev->dev, "The VF MAC address was NOT set due to invalid or duplicate MAC address.\n");
		पूर्ण
	पूर्ण अन्यथा अगर (is_zero_ether_addr(mac)) अणु
		अचिन्हित अक्षर *vf_mac_addr =
					   adapter->vfinfo[vf].vf_mac_addresses;

		/* nothing to करो */
		अगर (is_zero_ether_addr(vf_mac_addr))
			वापस 0;

		dev_info(&adapter->pdev->dev, "removing MAC on VF %d\n", vf);

		retval = ixgbe_del_mac_filter(adapter, vf_mac_addr, vf);
		अगर (retval >= 0) अणु
			adapter->vfinfo[vf].pf_set_mac = false;
			स_नकल(vf_mac_addr, mac, ETH_ALEN);
		पूर्ण अन्यथा अणु
			dev_warn(&adapter->pdev->dev, "Could NOT remove the VF MAC address.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = -EINVAL;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक ixgbe_enable_port_vlan(काष्ठा ixgbe_adapter *adapter, पूर्णांक vf,
				  u16 vlan, u8 qos)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err;

	err = ixgbe_set_vf_vlan(adapter, true, vlan, vf);
	अगर (err)
		जाओ out;

	/* Revoke tagless access via VLAN 0 */
	ixgbe_set_vf_vlan(adapter, false, 0, vf);

	ixgbe_set_vmvir(adapter, vlan, qos, vf);
	ixgbe_set_vmolr(hw, vf, false);

	/* enable hide vlan on X550 */
	अगर (hw->mac.type >= ixgbe_mac_X550)
		ixgbe_ग_लिखो_qde(adapter, vf, IXGBE_QDE_ENABLE |
				IXGBE_QDE_HIDE_VLAN);

	adapter->vfinfo[vf].pf_vlan = vlan;
	adapter->vfinfo[vf].pf_qos = qos;
	dev_info(&adapter->pdev->dev,
		 "Setting VLAN %d, QOS 0x%x on VF %d\n", vlan, qos, vf);
	अगर (test_bit(__IXGBE_DOWN, &adapter->state)) अणु
		dev_warn(&adapter->pdev->dev,
			 "The VF VLAN has been set, but the PF device is not up.\n");
		dev_warn(&adapter->pdev->dev,
			 "Bring the PF device up before attempting to use the VF device.\n");
	पूर्ण

out:
	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_disable_port_vlan(काष्ठा ixgbe_adapter *adapter, पूर्णांक vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err;

	err = ixgbe_set_vf_vlan(adapter, false,
				adapter->vfinfo[vf].pf_vlan, vf);
	/* Restore tagless access via VLAN 0 */
	ixgbe_set_vf_vlan(adapter, true, 0, vf);
	ixgbe_clear_vmvir(adapter, vf);
	ixgbe_set_vmolr(hw, vf, true);

	/* disable hide VLAN on X550 */
	अगर (hw->mac.type >= ixgbe_mac_X550)
		ixgbe_ग_लिखो_qde(adapter, vf, IXGBE_QDE_ENABLE);

	adapter->vfinfo[vf].pf_vlan = 0;
	adapter->vfinfo[vf].pf_qos = 0;

	वापस err;
पूर्ण

पूर्णांक ixgbe_nकरो_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan,
			  u8 qos, __be16 vlan_proto)
अणु
	पूर्णांक err = 0;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर ((vf >= adapter->num_vfs) || (vlan > 4095) || (qos > 7))
		वापस -EINVAL;
	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;
	अगर (vlan || qos) अणु
		/* Check अगर there is alपढ़ोy a port VLAN set, अगर so
		 * we have to delete the old one first beक्रमe we
		 * can set the new one.  The usage model had
		 * previously assumed the user would delete the
		 * old port VLAN beक्रमe setting a new one but this
		 * is not necessarily the हाल.
		 */
		अगर (adapter->vfinfo[vf].pf_vlan)
			err = ixgbe_disable_port_vlan(adapter, vf);
		अगर (err)
			जाओ out;
		err = ixgbe_enable_port_vlan(adapter, vf, vlan, qos);
	पूर्ण अन्यथा अणु
		err = ixgbe_disable_port_vlan(adapter, vf);
	पूर्ण

out:
	वापस err;
पूर्ण

पूर्णांक ixgbe_link_mbps(काष्ठा ixgbe_adapter *adapter)
अणु
	चयन (adapter->link_speed) अणु
	हाल IXGBE_LINK_SPEED_100_FULL:
		वापस 100;
	हाल IXGBE_LINK_SPEED_1GB_FULL:
		वापस 1000;
	हाल IXGBE_LINK_SPEED_10GB_FULL:
		वापस 10000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_set_vf_rate_limit(काष्ठा ixgbe_adapter *adapter, पूर्णांक vf)
अणु
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 bcnrc_val = 0;
	u16 queue, queues_per_pool;
	u16 tx_rate = adapter->vfinfo[vf].tx_rate;

	अगर (tx_rate) अणु
		/* start with base link speed value */
		bcnrc_val = adapter->vf_rate_link_speed;

		/* Calculate the rate factor values to set */
		bcnrc_val <<= IXGBE_RTTBCNRC_RF_INT_SHIFT;
		bcnrc_val /= tx_rate;

		/* clear everything but the rate factor */
		bcnrc_val &= IXGBE_RTTBCNRC_RF_INT_MASK |
			     IXGBE_RTTBCNRC_RF_DEC_MASK;

		/* enable the rate scheduler */
		bcnrc_val |= IXGBE_RTTBCNRC_RS_ENA;
	पूर्ण

	/*
	 * Set global transmit compensation समय to the MMW_SIZE in RTTBCNRM
	 * रेजिस्टर. Typically MMW_SIZE=0x014 अगर 9728-byte jumbo is supported
	 * and 0x004 otherwise.
	 */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
		IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRM, 0x4);
		अवरोध;
	हाल ixgbe_mac_X540:
		IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRM, 0x14);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* determine how many queues per pool based on VMDq mask */
	queues_per_pool = __ALIGN_MASK(1, ~vmdq->mask);

	/* ग_लिखो value क्रम all Tx queues beदीर्घing to VF */
	क्रम (queue = 0; queue < queues_per_pool; queue++) अणु
		अचिन्हित पूर्णांक reg_idx = (vf * queues_per_pool) + queue;

		IXGBE_WRITE_REG(hw, IXGBE_RTTDQSEL, reg_idx);
		IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRC, bcnrc_val);
	पूर्ण
पूर्ण

व्योम ixgbe_check_vf_rate_limit(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;

	/* VF Tx rate limit was not set */
	अगर (!adapter->vf_rate_link_speed)
		वापस;

	अगर (ixgbe_link_mbps(adapter) != adapter->vf_rate_link_speed) अणु
		adapter->vf_rate_link_speed = 0;
		dev_info(&adapter->pdev->dev,
			 "Link speed has been changed. VF Transmit rate is disabled\n");
	पूर्ण

	क्रम (i = 0; i < adapter->num_vfs; i++) अणु
		अगर (!adapter->vf_rate_link_speed)
			adapter->vfinfo[i].tx_rate = 0;

		ixgbe_set_vf_rate_limit(adapter, i);
	पूर्ण
पूर्ण

पूर्णांक ixgbe_nकरो_set_vf_bw(काष्ठा net_device *netdev, पूर्णांक vf, पूर्णांक min_tx_rate,
			पूर्णांक max_tx_rate)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	पूर्णांक link_speed;

	/* verअगरy VF is active */
	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	/* verअगरy link is up */
	अगर (!adapter->link_up)
		वापस -EINVAL;

	/* verअगरy we are linked at 10Gbps */
	link_speed = ixgbe_link_mbps(adapter);
	अगर (link_speed != 10000)
		वापस -EINVAL;

	अगर (min_tx_rate)
		वापस -EINVAL;

	/* rate limit cannot be less than 10Mbs or greater than link speed */
	अगर (max_tx_rate && ((max_tx_rate <= 10) || (max_tx_rate > link_speed)))
		वापस -EINVAL;

	/* store values */
	adapter->vf_rate_link_speed = link_speed;
	adapter->vfinfo[vf].tx_rate = max_tx_rate;

	/* update hardware configuration */
	ixgbe_set_vf_rate_limit(adapter, vf);

	वापस 0;
पूर्ण

पूर्णांक ixgbe_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool setting)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	adapter->vfinfo[vf].spoofchk_enabled = setting;

	/* configure MAC spoofing */
	hw->mac.ops.set_mac_anti_spoofing(hw, setting, vf);

	/* configure VLAN spoofing */
	hw->mac.ops.set_vlan_anti_spoofing(hw, setting, vf);

	/* Ensure LLDP and FC is set क्रम Ethertype Antispoofing अगर we will be
	 * calling set_ethertype_anti_spoofing क्रम each VF in loop below
	 */
	अगर (hw->mac.ops.set_ethertype_anti_spoofing) अणु
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_LLDP),
				(IXGBE_ETQF_FILTER_EN    |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 ETH_P_LLDP));

		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_FC),
				(IXGBE_ETQF_FILTER_EN |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 ETH_P_PAUSE));

		hw->mac.ops.set_ethertype_anti_spoofing(hw, setting, vf);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ixgbe_nकरो_set_vf_rss_query_en(काष्ठा net_device *netdev, पूर्णांक vf,
				  bool setting)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	/* This operation is currently supported only क्रम 82599 and x540
	 * devices.
	 */
	अगर (adapter->hw.mac.type < ixgbe_mac_82599EB ||
	    adapter->hw.mac.type >= ixgbe_mac_X550)
		वापस -EOPNOTSUPP;

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	adapter->vfinfo[vf].rss_query_enabled = setting;

	वापस 0;
पूर्ण

पूर्णांक ixgbe_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool setting)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	/* nothing to करो */
	अगर (adapter->vfinfo[vf].trusted == setting)
		वापस 0;

	adapter->vfinfo[vf].trusted = setting;

	/* reset VF to reconfigure features */
	adapter->vfinfo[vf].clear_to_send = false;
	ixgbe_ping_vf(adapter, vf);

	e_info(drv, "VF %u is %strusted\n", vf, setting ? "" : "not ");

	वापस 0;
पूर्ण

पूर्णांक ixgbe_nकरो_get_vf_config(काष्ठा net_device *netdev,
			    पूर्णांक vf, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;
	ivi->vf = vf;
	स_नकल(&ivi->mac, adapter->vfinfo[vf].vf_mac_addresses, ETH_ALEN);
	ivi->max_tx_rate = adapter->vfinfo[vf].tx_rate;
	ivi->min_tx_rate = 0;
	ivi->vlan = adapter->vfinfo[vf].pf_vlan;
	ivi->qos = adapter->vfinfo[vf].pf_qos;
	ivi->spoofchk = adapter->vfinfo[vf].spoofchk_enabled;
	ivi->rss_query_en = adapter->vfinfo[vf].rss_query_enabled;
	ivi->trusted = adapter->vfinfo[vf].trusted;
	वापस 0;
पूर्ण
