<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

/* Intel(R) Ethernet Connection E800 Series Linux Driver */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <generated/utsrelease.h>
#समावेश "ice.h"
#समावेश "ice_base.h"
#समावेश "ice_lib.h"
#समावेश "ice_fltr.h"
#समावेश "ice_dcb_lib.h"
#समावेश "ice_dcb_nl.h"
#समावेश "ice_devlink.h"

#घोषणा DRV_SUMMARY	"Intel(R) Ethernet Connection E800 Series Linux Driver"
अटल स्थिर अक्षर ice_driver_string[] = DRV_SUMMARY;
अटल स्थिर अक्षर ice_copyright[] = "Copyright (c) 2018, Intel Corporation.";

/* DDP Package file located in firmware search paths (e.g. /lib/firmware/) */
#घोषणा ICE_DDP_PKG_PATH	"intel/ice/ddp/"
#घोषणा ICE_DDP_PKG_खाता	ICE_DDP_PKG_PATH "ice.pkg"

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION(DRV_SUMMARY);
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(ICE_DDP_PKG_खाता);

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0644);
#अगर_अघोषित CONFIG_DYNAMIC_DEBUG
MODULE_PARM_DESC(debug, "netif level (0=none,...,16=all), hw debug_mask (0x8XXXXXXX)");
#अन्यथा
MODULE_PARM_DESC(debug, "netif level (0=none,...,16=all)");
#पूर्ण_अगर /* !CONFIG_DYNAMIC_DEBUG */

अटल काष्ठा workqueue_काष्ठा *ice_wq;
अटल स्थिर काष्ठा net_device_ops ice_netdev_safe_mode_ops;
अटल स्थिर काष्ठा net_device_ops ice_netdev_ops;
अटल पूर्णांक ice_vsi_खोलो(काष्ठा ice_vsi *vsi);

अटल व्योम ice_rebuild(काष्ठा ice_pf *pf, क्रमागत ice_reset_req reset_type);

अटल व्योम ice_vsi_release_all(काष्ठा ice_pf *pf);

bool netअगर_is_ice(काष्ठा net_device *dev)
अणु
	वापस dev && (dev->netdev_ops == &ice_netdev_ops);
पूर्ण

/**
 * ice_get_tx_pending - वापसs number of Tx descriptors not processed
 * @ring: the ring of descriptors
 */
अटल u16 ice_get_tx_pending(काष्ठा ice_ring *ring)
अणु
	u16 head, tail;

	head = ring->next_to_clean;
	tail = ring->next_to_use;

	अगर (head != tail)
		वापस (head < tail) ?
			tail - head : (tail + ring->count - head);
	वापस 0;
पूर्ण

/**
 * ice_check_क्रम_hang_subtask - check क्रम and recover hung queues
 * @pf: poपूर्णांकer to PF काष्ठा
 */
अटल व्योम ice_check_क्रम_hang_subtask(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_vsi *vsi = शून्य;
	काष्ठा ice_hw *hw;
	अचिन्हित पूर्णांक i;
	पूर्णांक packets;
	u32 v;

	ice_क्रम_each_vsi(pf, v)
		अगर (pf->vsi[v] && pf->vsi[v]->type == ICE_VSI_PF) अणु
			vsi = pf->vsi[v];
			अवरोध;
		पूर्ण

	अगर (!vsi || test_bit(ICE_VSI_DOWN, vsi->state))
		वापस;

	अगर (!(vsi->netdev && netअगर_carrier_ok(vsi->netdev)))
		वापस;

	hw = &vsi->back->hw;

	क्रम (i = 0; i < vsi->num_txq; i++) अणु
		काष्ठा ice_ring *tx_ring = vsi->tx_rings[i];

		अगर (tx_ring && tx_ring->desc) अणु
			/* If packet counter has not changed the queue is
			 * likely stalled, so क्रमce an पूर्णांकerrupt क्रम this
			 * queue.
			 *
			 * prev_pkt would be negative अगर there was no
			 * pending work.
			 */
			packets = tx_ring->stats.pkts & पूर्णांक_उच्च;
			अगर (tx_ring->tx_stats.prev_pkt == packets) अणु
				/* Trigger sw पूर्णांकerrupt to revive the queue */
				ice_trigger_sw_पूर्णांकr(hw, tx_ring->q_vector);
				जारी;
			पूर्ण

			/* Memory barrier between पढ़ो of packet count and call
			 * to ice_get_tx_pending()
			 */
			smp_rmb();
			tx_ring->tx_stats.prev_pkt =
			    ice_get_tx_pending(tx_ring) ? packets : -1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_init_mac_fltr - Set initial MAC filters
 * @pf: board निजी काष्ठाure
 *
 * Set initial set of MAC filters क्रम PF VSI; configure filters क्रम permanent
 * address and broadcast address. If an error is encountered, netdevice will be
 * unरेजिस्टरed.
 */
अटल पूर्णांक ice_init_mac_fltr(काष्ठा ice_pf *pf)
अणु
	क्रमागत ice_status status;
	काष्ठा ice_vsi *vsi;
	u8 *perm_addr;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi)
		वापस -EINVAL;

	perm_addr = vsi->port_info->mac.perm_addr;
	status = ice_fltr_add_mac_and_broadcast(vsi, perm_addr, ICE_FWD_TO_VSI);
	अगर (status)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * ice_add_mac_to_sync_list - creates list of MAC addresses to be synced
 * @netdev: the net device on which the sync is happening
 * @addr: MAC address to sync
 *
 * This is a callback function which is called by the in kernel device sync
 * functions (like __dev_uc_sync, __dev_mc_sync, etc). This function only
 * populates the पंचांगp_sync_list, which is later used by ice_add_mac to add the
 * MAC filters from the hardware.
 */
अटल पूर्णांक ice_add_mac_to_sync_list(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;

	अगर (ice_fltr_add_mac_to_list(vsi, &vsi->पंचांगp_sync_list, addr,
				     ICE_FWD_TO_VSI))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * ice_add_mac_to_unsync_list - creates list of MAC addresses to be unsynced
 * @netdev: the net device on which the unsync is happening
 * @addr: MAC address to unsync
 *
 * This is a callback function which is called by the in kernel device unsync
 * functions (like __dev_uc_unsync, __dev_mc_unsync, etc). This function only
 * populates the पंचांगp_unsync_list, which is later used by ice_हटाओ_mac to
 * delete the MAC filters from the hardware.
 */
अटल पूर्णांक ice_add_mac_to_unsync_list(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;

	अगर (ice_fltr_add_mac_to_list(vsi, &vsi->पंचांगp_unsync_list, addr,
				     ICE_FWD_TO_VSI))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * ice_vsi_fltr_changed - check अगर filter state changed
 * @vsi: VSI to be checked
 *
 * वापसs true अगर filter state has changed, false otherwise.
 */
अटल bool ice_vsi_fltr_changed(काष्ठा ice_vsi *vsi)
अणु
	वापस test_bit(ICE_VSI_UMAC_FLTR_CHANGED, vsi->state) ||
	       test_bit(ICE_VSI_MMAC_FLTR_CHANGED, vsi->state) ||
	       test_bit(ICE_VSI_VLAN_FLTR_CHANGED, vsi->state);
पूर्ण

/**
 * ice_cfg_promisc - Enable or disable promiscuous mode क्रम a given PF
 * @vsi: the VSI being configured
 * @promisc_m: mask of promiscuous config bits
 * @set_promisc: enable or disable promisc flag request
 *
 */
अटल पूर्णांक ice_cfg_promisc(काष्ठा ice_vsi *vsi, u8 promisc_m, bool set_promisc)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	क्रमागत ice_status status = 0;

	अगर (vsi->type != ICE_VSI_PF)
		वापस 0;

	अगर (vsi->num_vlan > 1) अणु
		status = ice_set_vlan_vsi_promisc(hw, vsi->idx, promisc_m,
						  set_promisc);
	पूर्ण अन्यथा अणु
		अगर (set_promisc)
			status = ice_set_vsi_promisc(hw, vsi->idx, promisc_m,
						     0);
		अन्यथा
			status = ice_clear_vsi_promisc(hw, vsi->idx, promisc_m,
						       0);
	पूर्ण

	अगर (status)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * ice_vsi_sync_fltr - Update the VSI filter list to the HW
 * @vsi: ptr to the VSI
 *
 * Push any outstanding VSI filter changes through the AdminQ.
 */
अटल पूर्णांक ice_vsi_sync_fltr(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vsi->back);
	काष्ठा net_device *netdev = vsi->netdev;
	bool promisc_क्रमced_on = false;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status = 0;
	u32 changed_flags = 0;
	u8 promisc_m;
	पूर्णांक err = 0;

	अगर (!vsi->netdev)
		वापस -EINVAL;

	जबतक (test_and_set_bit(ICE_CFG_BUSY, vsi->state))
		usleep_range(1000, 2000);

	changed_flags = vsi->current_netdev_flags ^ vsi->netdev->flags;
	vsi->current_netdev_flags = vsi->netdev->flags;

	INIT_LIST_HEAD(&vsi->पंचांगp_sync_list);
	INIT_LIST_HEAD(&vsi->पंचांगp_unsync_list);

	अगर (ice_vsi_fltr_changed(vsi)) अणु
		clear_bit(ICE_VSI_UMAC_FLTR_CHANGED, vsi->state);
		clear_bit(ICE_VSI_MMAC_FLTR_CHANGED, vsi->state);
		clear_bit(ICE_VSI_VLAN_FLTR_CHANGED, vsi->state);

		/* grab the netdev's addr_list_lock */
		netअगर_addr_lock_bh(netdev);
		__dev_uc_sync(netdev, ice_add_mac_to_sync_list,
			      ice_add_mac_to_unsync_list);
		__dev_mc_sync(netdev, ice_add_mac_to_sync_list,
			      ice_add_mac_to_unsync_list);
		/* our temp lists are populated. release lock */
		netअगर_addr_unlock_bh(netdev);
	पूर्ण

	/* Remove MAC addresses in the unsync list */
	status = ice_fltr_हटाओ_mac_list(vsi, &vsi->पंचांगp_unsync_list);
	ice_fltr_मुक्त_list(dev, &vsi->पंचांगp_unsync_list);
	अगर (status) अणु
		netdev_err(netdev, "Failed to delete MAC filters\n");
		/* अगर we failed because of alloc failures, just bail */
		अगर (status == ICE_ERR_NO_MEMORY) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Add MAC addresses in the sync list */
	status = ice_fltr_add_mac_list(vsi, &vsi->पंचांगp_sync_list);
	ice_fltr_मुक्त_list(dev, &vsi->पंचांगp_sync_list);
	/* If filter is added successfully or alपढ़ोy exists, करो not go पूर्णांकo
	 * 'if' condition and report it as error. Instead जारी processing
	 * rest of the function.
	 */
	अगर (status && status != ICE_ERR_ALREADY_EXISTS) अणु
		netdev_err(netdev, "Failed to add MAC filters\n");
		/* If there is no more space क्रम new umac filters, VSI
		 * should go पूर्णांकo promiscuous mode. There should be some
		 * space reserved क्रम promiscuous filters.
		 */
		अगर (hw->adminq.sq_last_status == ICE_AQ_RC_ENOSPC &&
		    !test_and_set_bit(ICE_FLTR_OVERFLOW_PROMISC,
				      vsi->state)) अणु
			promisc_क्रमced_on = true;
			netdev_warn(netdev, "Reached MAC filter limit, forcing promisc mode on VSI %d\n",
				    vsi->vsi_num);
		पूर्ण अन्यथा अणु
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
	/* check क्रम changes in promiscuous modes */
	अगर (changed_flags & IFF_ALLMULTI) अणु
		अगर (vsi->current_netdev_flags & IFF_ALLMULTI) अणु
			अगर (vsi->num_vlan > 1)
				promisc_m = ICE_MCAST_VLAN_PROMISC_BITS;
			अन्यथा
				promisc_m = ICE_MCAST_PROMISC_BITS;

			err = ice_cfg_promisc(vsi, promisc_m, true);
			अगर (err) अणु
				netdev_err(netdev, "Error setting Multicast promiscuous mode on VSI %i\n",
					   vsi->vsi_num);
				vsi->current_netdev_flags &= ~IFF_ALLMULTI;
				जाओ out_promisc;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* !(vsi->current_netdev_flags & IFF_ALLMULTI) */
			अगर (vsi->num_vlan > 1)
				promisc_m = ICE_MCAST_VLAN_PROMISC_BITS;
			अन्यथा
				promisc_m = ICE_MCAST_PROMISC_BITS;

			err = ice_cfg_promisc(vsi, promisc_m, false);
			अगर (err) अणु
				netdev_err(netdev, "Error clearing Multicast promiscuous mode on VSI %i\n",
					   vsi->vsi_num);
				vsi->current_netdev_flags |= IFF_ALLMULTI;
				जाओ out_promisc;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (((changed_flags & IFF_PROMISC) || promisc_क्रमced_on) ||
	    test_bit(ICE_VSI_PROMISC_CHANGED, vsi->state)) अणु
		clear_bit(ICE_VSI_PROMISC_CHANGED, vsi->state);
		अगर (vsi->current_netdev_flags & IFF_PROMISC) अणु
			/* Apply Rx filter rule to get traffic from wire */
			अगर (!ice_is_dflt_vsi_in_use(pf->first_sw)) अणु
				err = ice_set_dflt_vsi(pf->first_sw, vsi);
				अगर (err && err != -EEXIST) अणु
					netdev_err(netdev, "Error %d setting default VSI %i Rx rule\n",
						   err, vsi->vsi_num);
					vsi->current_netdev_flags &=
						~IFF_PROMISC;
					जाओ out_promisc;
				पूर्ण
				ice_cfg_vlan_pruning(vsi, false, false);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Clear Rx filter to हटाओ traffic from wire */
			अगर (ice_is_vsi_dflt_vsi(pf->first_sw, vsi)) अणु
				err = ice_clear_dflt_vsi(pf->first_sw);
				अगर (err) अणु
					netdev_err(netdev, "Error %d clearing default VSI %i Rx rule\n",
						   err, vsi->vsi_num);
					vsi->current_netdev_flags |=
						IFF_PROMISC;
					जाओ out_promisc;
				पूर्ण
				अगर (vsi->num_vlan > 1)
					ice_cfg_vlan_pruning(vsi, true, false);
			पूर्ण
		पूर्ण
	पूर्ण
	जाओ निकास;

out_promisc:
	set_bit(ICE_VSI_PROMISC_CHANGED, vsi->state);
	जाओ निकास;
out:
	/* अगर something went wrong then set the changed flag so we try again */
	set_bit(ICE_VSI_UMAC_FLTR_CHANGED, vsi->state);
	set_bit(ICE_VSI_MMAC_FLTR_CHANGED, vsi->state);
निकास:
	clear_bit(ICE_CFG_BUSY, vsi->state);
	वापस err;
पूर्ण

/**
 * ice_sync_fltr_subtask - Sync the VSI filter list with HW
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_sync_fltr_subtask(काष्ठा ice_pf *pf)
अणु
	पूर्णांक v;

	अगर (!pf || !(test_bit(ICE_FLAG_FLTR_SYNC, pf->flags)))
		वापस;

	clear_bit(ICE_FLAG_FLTR_SYNC, pf->flags);

	ice_क्रम_each_vsi(pf, v)
		अगर (pf->vsi[v] && ice_vsi_fltr_changed(pf->vsi[v]) &&
		    ice_vsi_sync_fltr(pf->vsi[v])) अणु
			/* come back and try again later */
			set_bit(ICE_FLAG_FLTR_SYNC, pf->flags);
			अवरोध;
		पूर्ण
पूर्ण

/**
 * ice_pf_dis_all_vsi - Pause all VSIs on a PF
 * @pf: the PF
 * @locked: is the rtnl_lock alपढ़ोy held
 */
अटल व्योम ice_pf_dis_all_vsi(काष्ठा ice_pf *pf, bool locked)
अणु
	पूर्णांक node;
	पूर्णांक v;

	ice_क्रम_each_vsi(pf, v)
		अगर (pf->vsi[v])
			ice_dis_vsi(pf->vsi[v], locked);

	क्रम (node = 0; node < ICE_MAX_PF_AGG_NODES; node++)
		pf->pf_agg_node[node].num_vsis = 0;

	क्रम (node = 0; node < ICE_MAX_VF_AGG_NODES; node++)
		pf->vf_agg_node[node].num_vsis = 0;
पूर्ण

/**
 * ice_prepare_क्रम_reset - prep क्रम the core to reset
 * @pf: board निजी काष्ठाure
 *
 * Inक्रमm or बंद all dependent features in prep क्रम reset.
 */
अटल व्योम
ice_prepare_क्रम_reset(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	अचिन्हित पूर्णांक i;

	/* alपढ़ोy prepared क्रम reset */
	अगर (test_bit(ICE_PREPARED_FOR_RESET, pf->state))
		वापस;

	/* Notअगरy VFs of impending reset */
	अगर (ice_check_sq_alive(hw, &hw->mailboxq))
		ice_vc_notअगरy_reset(pf);

	/* Disable VFs until reset is completed */
	ice_क्रम_each_vf(pf, i)
		ice_set_vf_state_qs_dis(&pf->vf[i]);

	/* clear SW filtering DB */
	ice_clear_hw_tbls(hw);
	/* disable the VSIs and their queues that are not alपढ़ोy DOWN */
	ice_pf_dis_all_vsi(pf, false);

	अगर (hw->port_info)
		ice_sched_clear_port(hw->port_info);

	ice_shutकरोwn_all_ctrlq(hw);

	set_bit(ICE_PREPARED_FOR_RESET, pf->state);
पूर्ण

/**
 * ice_करो_reset - Initiate one of many types of resets
 * @pf: board निजी काष्ठाure
 * @reset_type: reset type requested
 * beक्रमe this function was called.
 */
अटल व्योम ice_करो_reset(काष्ठा ice_pf *pf, क्रमागत ice_reset_req reset_type)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;

	dev_dbg(dev, "reset_type 0x%x requested\n", reset_type);

	ice_prepare_क्रम_reset(pf);

	/* trigger the reset */
	अगर (ice_reset(hw, reset_type)) अणु
		dev_err(dev, "reset %d failed\n", reset_type);
		set_bit(ICE_RESET_FAILED, pf->state);
		clear_bit(ICE_RESET_OICR_RECV, pf->state);
		clear_bit(ICE_PREPARED_FOR_RESET, pf->state);
		clear_bit(ICE_PFR_REQ, pf->state);
		clear_bit(ICE_CORER_REQ, pf->state);
		clear_bit(ICE_GLOBR_REQ, pf->state);
		वापस;
	पूर्ण

	/* PFR is a bit of a special हाल because it करोesn't result in an OICR
	 * पूर्णांकerrupt. So क्रम PFR, rebuild after the reset and clear the reset-
	 * associated state bits.
	 */
	अगर (reset_type == ICE_RESET_PFR) अणु
		pf->pfr_count++;
		ice_rebuild(pf, reset_type);
		clear_bit(ICE_PREPARED_FOR_RESET, pf->state);
		clear_bit(ICE_PFR_REQ, pf->state);
		ice_reset_all_vfs(pf, true);
	पूर्ण
पूर्ण

/**
 * ice_reset_subtask - Set up क्रम resetting the device and driver
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_reset_subtask(काष्ठा ice_pf *pf)
अणु
	क्रमागत ice_reset_req reset_type = ICE_RESET_INVAL;

	/* When a CORER/GLOBR/EMPR is about to happen, the hardware triggers an
	 * OICR पूर्णांकerrupt. The OICR handler (ice_misc_पूर्णांकr) determines what type
	 * of reset is pending and sets bits in pf->state indicating the reset
	 * type and ICE_RESET_OICR_RECV. So, अगर the latter bit is set
	 * prepare क्रम pending reset अगर not alपढ़ोy (क्रम PF software-initiated
	 * global resets the software should alपढ़ोy be prepared क्रम it as
	 * indicated by ICE_PREPARED_FOR_RESET; क्रम global resets initiated
	 * by firmware or software on other PFs, that bit is not set so prepare
	 * क्रम the reset now), poll क्रम reset करोne, rebuild and वापस.
	 */
	अगर (test_bit(ICE_RESET_OICR_RECV, pf->state)) अणु
		/* Perक्रमm the largest reset requested */
		अगर (test_and_clear_bit(ICE_CORER_RECV, pf->state))
			reset_type = ICE_RESET_CORER;
		अगर (test_and_clear_bit(ICE_GLOBR_RECV, pf->state))
			reset_type = ICE_RESET_GLOBR;
		अगर (test_and_clear_bit(ICE_EMPR_RECV, pf->state))
			reset_type = ICE_RESET_EMPR;
		/* वापस अगर no valid reset type requested */
		अगर (reset_type == ICE_RESET_INVAL)
			वापस;
		ice_prepare_क्रम_reset(pf);

		/* make sure we are पढ़ोy to rebuild */
		अगर (ice_check_reset(&pf->hw)) अणु
			set_bit(ICE_RESET_FAILED, pf->state);
		पूर्ण अन्यथा अणु
			/* करोne with reset. start rebuild */
			pf->hw.reset_ongoing = false;
			ice_rebuild(pf, reset_type);
			/* clear bit to resume normal operations, but
			 * ICE_NEEDS_RESTART bit is set in हाल rebuild failed
			 */
			clear_bit(ICE_RESET_OICR_RECV, pf->state);
			clear_bit(ICE_PREPARED_FOR_RESET, pf->state);
			clear_bit(ICE_PFR_REQ, pf->state);
			clear_bit(ICE_CORER_REQ, pf->state);
			clear_bit(ICE_GLOBR_REQ, pf->state);
			ice_reset_all_vfs(pf, true);
		पूर्ण

		वापस;
	पूर्ण

	/* No pending resets to finish processing. Check क्रम new resets */
	अगर (test_bit(ICE_PFR_REQ, pf->state))
		reset_type = ICE_RESET_PFR;
	अगर (test_bit(ICE_CORER_REQ, pf->state))
		reset_type = ICE_RESET_CORER;
	अगर (test_bit(ICE_GLOBR_REQ, pf->state))
		reset_type = ICE_RESET_GLOBR;
	/* If no valid reset type requested just वापस */
	अगर (reset_type == ICE_RESET_INVAL)
		वापस;

	/* reset अगर not alपढ़ोy करोwn or busy */
	अगर (!test_bit(ICE_DOWN, pf->state) &&
	    !test_bit(ICE_CFG_BUSY, pf->state)) अणु
		ice_करो_reset(pf, reset_type);
	पूर्ण
पूर्ण

/**
 * ice_prपूर्णांक_topo_conflict - prपूर्णांक topology conflict message
 * @vsi: the VSI whose topology status is being checked
 */
अटल व्योम ice_prपूर्णांक_topo_conflict(काष्ठा ice_vsi *vsi)
अणु
	चयन (vsi->port_info->phy.link_info.topo_media_conflict) अणु
	हाल ICE_AQ_LINK_TOPO_CONFLICT:
	हाल ICE_AQ_LINK_MEDIA_CONFLICT:
	हाल ICE_AQ_LINK_TOPO_UNREACH_PRT:
	हाल ICE_AQ_LINK_TOPO_UNDRUTIL_PRT:
	हाल ICE_AQ_LINK_TOPO_UNDRUTIL_MEDIA:
		netdev_info(vsi->netdev, "Potential misconfiguration of the Ethernet port detected. If it was not intended, please use the Intel (R) Ethernet Port Configuration Tool to address the issue.\n");
		अवरोध;
	हाल ICE_AQ_LINK_TOPO_UNSUPP_MEDIA:
		netdev_info(vsi->netdev, "Rx/Tx is disabled on this device because an unsupported module type was detected. Refer to the Intel(R) Ethernet Adapters and Devices User Guide for a list of supported modules.\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_prपूर्णांक_link_msg - prपूर्णांक link up or करोwn message
 * @vsi: the VSI whose link status is being queried
 * @isup: boolean क्रम अगर the link is now up or करोwn
 */
व्योम ice_prपूर्णांक_link_msg(काष्ठा ice_vsi *vsi, bool isup)
अणु
	काष्ठा ice_aqc_get_phy_caps_data *caps;
	स्थिर अक्षर *an_advertised;
	क्रमागत ice_status status;
	स्थिर अक्षर *fec_req;
	स्थिर अक्षर *speed;
	स्थिर अक्षर *fec;
	स्थिर अक्षर *fc;
	स्थिर अक्षर *an;

	अगर (!vsi)
		वापस;

	अगर (vsi->current_isup == isup)
		वापस;

	vsi->current_isup = isup;

	अगर (!isup) अणु
		netdev_info(vsi->netdev, "NIC Link is Down\n");
		वापस;
	पूर्ण

	चयन (vsi->port_info->phy.link_info.link_speed) अणु
	हाल ICE_AQ_LINK_SPEED_100GB:
		speed = "100 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_50GB:
		speed = "50 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_40GB:
		speed = "40 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_25GB:
		speed = "25 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_20GB:
		speed = "20 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_10GB:
		speed = "10 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_5GB:
		speed = "5 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_2500MB:
		speed = "2.5 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_1000MB:
		speed = "1 G";
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_100MB:
		speed = "100 M";
		अवरोध;
	शेष:
		speed = "Unknown ";
		अवरोध;
	पूर्ण

	चयन (vsi->port_info->fc.current_mode) अणु
	हाल ICE_FC_FULL:
		fc = "Rx/Tx";
		अवरोध;
	हाल ICE_FC_TX_PAUSE:
		fc = "Tx";
		अवरोध;
	हाल ICE_FC_RX_PAUSE:
		fc = "Rx";
		अवरोध;
	हाल ICE_FC_NONE:
		fc = "None";
		अवरोध;
	शेष:
		fc = "Unknown";
		अवरोध;
	पूर्ण

	/* Get FEC mode based on negotiated link info */
	चयन (vsi->port_info->phy.link_info.fec_info) अणु
	हाल ICE_AQ_LINK_25G_RS_528_FEC_EN:
	हाल ICE_AQ_LINK_25G_RS_544_FEC_EN:
		fec = "RS-FEC";
		अवरोध;
	हाल ICE_AQ_LINK_25G_KR_FEC_EN:
		fec = "FC-FEC/BASE-R";
		अवरोध;
	शेष:
		fec = "NONE";
		अवरोध;
	पूर्ण

	/* check अगर स्वतःneg completed, might be false due to not supported */
	अगर (vsi->port_info->phy.link_info.an_info & ICE_AQ_AN_COMPLETED)
		an = "True";
	अन्यथा
		an = "False";

	/* Get FEC mode requested based on PHY caps last SW configuration */
	caps = kzalloc(माप(*caps), GFP_KERNEL);
	अगर (!caps) अणु
		fec_req = "Unknown";
		an_advertised = "Unknown";
		जाओ करोne;
	पूर्ण

	status = ice_aq_get_phy_caps(vsi->port_info, false,
				     ICE_AQC_REPORT_ACTIVE_CFG, caps, शून्य);
	अगर (status)
		netdev_info(vsi->netdev, "Get phy capability failed.\n");

	an_advertised = ice_is_phy_caps_an_enabled(caps) ? "On" : "Off";

	अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_528_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_544_REQ)
		fec_req = "RS-FEC";
	अन्यथा अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ||
		 caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_REQ)
		fec_req = "FC-FEC/BASE-R";
	अन्यथा
		fec_req = "NONE";

	kमुक्त(caps);

करोne:
	netdev_info(vsi->netdev, "NIC Link is up %sbps Full Duplex, Requested FEC: %s, Negotiated FEC: %s, Autoneg Advertised: %s, Autoneg Negotiated: %s, Flow Control: %s\n",
		    speed, fec_req, fec, an_advertised, an, fc);
	ice_prपूर्णांक_topo_conflict(vsi);
पूर्ण

/**
 * ice_vsi_link_event - update the VSI's netdev
 * @vsi: the VSI on which the link event occurred
 * @link_up: whether or not the VSI needs to be set up or करोwn
 */
अटल व्योम ice_vsi_link_event(काष्ठा ice_vsi *vsi, bool link_up)
अणु
	अगर (!vsi)
		वापस;

	अगर (test_bit(ICE_VSI_DOWN, vsi->state) || !vsi->netdev)
		वापस;

	अगर (vsi->type == ICE_VSI_PF) अणु
		अगर (link_up == netअगर_carrier_ok(vsi->netdev))
			वापस;

		अगर (link_up) अणु
			netअगर_carrier_on(vsi->netdev);
			netअगर_tx_wake_all_queues(vsi->netdev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(vsi->netdev);
			netअगर_tx_stop_all_queues(vsi->netdev);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_set_dflt_mib - send a शेष config MIB to the FW
 * @pf: निजी PF काष्ठा
 *
 * This function sends a शेष configuration MIB to the FW.
 *
 * If this function errors out at any poपूर्णांक, the driver is still able to
 * function.  The मुख्य impact is that LFC may not operate as expected.
 * Thereक्रमe an error state in this function should be treated with a DBG
 * message and जारी on with driver rebuild/reenable.
 */
अटल व्योम ice_set_dflt_mib(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	u8 mib_type, *buf, *lldpmib = शून्य;
	u16 len, typelen, offset = 0;
	काष्ठा ice_lldp_org_tlv *tlv;
	काष्ठा ice_hw *hw = &pf->hw;
	u32 ouisubtype;

	mib_type = SET_LOCAL_MIB_TYPE_LOCAL_MIB;
	lldpmib = kzalloc(ICE_LLDPDU_SIZE, GFP_KERNEL);
	अगर (!lldpmib) अणु
		dev_dbg(dev, "%s Failed to allocate MIB memory\n",
			__func__);
		वापस;
	पूर्ण

	/* Add ETS CFG TLV */
	tlv = (काष्ठा ice_lldp_org_tlv *)lldpmib;
	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) |
		   ICE_IEEE_ETS_TLV_LEN);
	tlv->typelen = htons(typelen);
	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_ETS_CFG);
	tlv->ouisubtype = htonl(ouisubtype);

	buf = tlv->tlvinfo;
	buf[0] = 0;

	/* ETS CFG all UPs map to TC 0. Next 4 (1 - 4) Octets = 0.
	 * Octets 5 - 12 are BW values, set octet 5 to 100% BW.
	 * Octets 13 - 20 are TSA values - leave as zeros
	 */
	buf[5] = 0x64;
	len = (typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S;
	offset += len + 2;
	tlv = (काष्ठा ice_lldp_org_tlv *)
		((अक्षर *)tlv + माप(tlv->typelen) + len);

	/* Add ETS REC TLV */
	buf = tlv->tlvinfo;
	tlv->typelen = htons(typelen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_ETS_REC);
	tlv->ouisubtype = htonl(ouisubtype);

	/* First octet of buf is reserved
	 * Octets 1 - 4 map UP to TC - all UPs map to zero
	 * Octets 5 - 12 are BW values - set TC 0 to 100%.
	 * Octets 13 - 20 are TSA value - leave as zeros
	 */
	buf[5] = 0x64;
	offset += len + 2;
	tlv = (काष्ठा ice_lldp_org_tlv *)
		((अक्षर *)tlv + माप(tlv->typelen) + len);

	/* Add PFC CFG TLV */
	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) |
		   ICE_IEEE_PFC_TLV_LEN);
	tlv->typelen = htons(typelen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_PFC_CFG);
	tlv->ouisubtype = htonl(ouisubtype);

	/* Octet 1 left as all zeros - PFC disabled */
	buf[0] = 0x08;
	len = (typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S;
	offset += len + 2;

	अगर (ice_aq_set_lldp_mib(hw, mib_type, (व्योम *)lldpmib, offset, शून्य))
		dev_dbg(dev, "%s Failed to set default LLDP MIB\n", __func__);

	kमुक्त(lldpmib);
पूर्ण

/**
 * ice_link_event - process the link event
 * @pf: PF that the link event is associated with
 * @pi: port_info क्रम the port that the link event is associated with
 * @link_up: true अगर the physical link is up and false अगर it is करोwn
 * @link_speed: current link speed received from the link event
 *
 * Returns 0 on success and negative on failure
 */
अटल पूर्णांक
ice_link_event(काष्ठा ice_pf *pf, काष्ठा ice_port_info *pi, bool link_up,
	       u16 link_speed)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_phy_info *phy_info;
	क्रमागत ice_status status;
	काष्ठा ice_vsi *vsi;
	u16 old_link_speed;
	bool old_link;

	phy_info = &pi->phy;
	phy_info->link_info_old = phy_info->link_info;

	old_link = !!(phy_info->link_info_old.link_info & ICE_AQ_LINK_UP);
	old_link_speed = phy_info->link_info_old.link_speed;

	/* update the link info काष्ठाures and re-enable link events,
	 * करोn't bail on failure due to other book keeping needed
	 */
	status = ice_update_link_info(pi);
	अगर (status)
		dev_dbg(dev, "Failed to update link status on port %d, err %s aq_err %s\n",
			pi->lport, ice_stat_str(status),
			ice_aq_str(pi->hw->adminq.sq_last_status));

	/* Check अगर the link state is up after updating link info, and treat
	 * this event as an UP event since the link is actually UP now.
	 */
	अगर (phy_info->link_info.link_info & ICE_AQ_LINK_UP)
		link_up = true;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi || !vsi->port_info)
		वापस -EINVAL;

	/* turn off PHY अगर media was हटाओd */
	अगर (!test_bit(ICE_FLAG_NO_MEDIA, pf->flags) &&
	    !(pi->phy.link_info.link_info & ICE_AQ_MEDIA_AVAILABLE)) अणु
		set_bit(ICE_FLAG_NO_MEDIA, pf->flags);
		ice_set_link(vsi, false);
	पूर्ण

	/* अगर the old link up/करोwn and speed is the same as the new */
	अगर (link_up == old_link && link_speed == old_link_speed)
		वापस 0;

	अगर (ice_is_dcb_active(pf)) अणु
		अगर (test_bit(ICE_FLAG_DCB_ENA, pf->flags))
			ice_dcb_rebuild(pf);
	पूर्ण अन्यथा अणु
		अगर (link_up)
			ice_set_dflt_mib(pf);
	पूर्ण
	ice_vsi_link_event(vsi, link_up);
	ice_prपूर्णांक_link_msg(vsi, link_up);

	ice_vc_notअगरy_link_state(pf);

	वापस 0;
पूर्ण

/**
 * ice_watchकरोg_subtask - periodic tasks not using event driven scheduling
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_watchकरोg_subtask(काष्ठा ice_pf *pf)
अणु
	पूर्णांक i;

	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(ICE_DOWN, pf->state) ||
	    test_bit(ICE_CFG_BUSY, pf->state))
		वापस;

	/* make sure we करोn't करो these things too often */
	अगर (समय_beक्रमe(jअगरfies,
			pf->serv_पंचांगr_prev + pf->serv_पंचांगr_period))
		वापस;

	pf->serv_पंचांगr_prev = jअगरfies;

	/* Update the stats क्रम active netdevs so the network stack
	 * can look at updated numbers whenever it cares to
	 */
	ice_update_pf_stats(pf);
	ice_क्रम_each_vsi(pf, i)
		अगर (pf->vsi[i] && pf->vsi[i]->netdev)
			ice_update_vsi_stats(pf->vsi[i]);
पूर्ण

/**
 * ice_init_link_events - enable/initialize link events
 * @pi: poपूर्णांकer to the port_info instance
 *
 * Returns -EIO on failure, 0 on success
 */
अटल पूर्णांक ice_init_link_events(काष्ठा ice_port_info *pi)
अणु
	u16 mask;

	mask = ~((u16)(ICE_AQ_LINK_EVENT_UPDOWN | ICE_AQ_LINK_EVENT_MEDIA_NA |
		       ICE_AQ_LINK_EVENT_MODULE_QUAL_FAIL));

	अगर (ice_aq_set_event_mask(pi->hw, pi->lport, mask, शून्य)) अणु
		dev_dbg(ice_hw_to_dev(pi->hw), "Failed to set link event mask for port %d\n",
			pi->lport);
		वापस -EIO;
	पूर्ण

	अगर (ice_aq_get_link_info(pi, true, शून्य, शून्य)) अणु
		dev_dbg(ice_hw_to_dev(pi->hw), "Failed to enable link events for port %d\n",
			pi->lport);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_handle_link_event - handle link event via ARQ
 * @pf: PF that the link event is associated with
 * @event: event काष्ठाure containing link status info
 */
अटल पूर्णांक
ice_handle_link_event(काष्ठा ice_pf *pf, काष्ठा ice_rq_event_info *event)
अणु
	काष्ठा ice_aqc_get_link_status_data *link_data;
	काष्ठा ice_port_info *port_info;
	पूर्णांक status;

	link_data = (काष्ठा ice_aqc_get_link_status_data *)event->msg_buf;
	port_info = pf->hw.port_info;
	अगर (!port_info)
		वापस -EINVAL;

	status = ice_link_event(pf, port_info,
				!!(link_data->link_info & ICE_AQ_LINK_UP),
				le16_to_cpu(link_data->link_speed));
	अगर (status)
		dev_dbg(ice_pf_to_dev(pf), "Could not process link event, error %d\n",
			status);

	वापस status;
पूर्ण

क्रमागत ice_aq_task_state अणु
	ICE_AQ_TASK_WAITING = 0,
	ICE_AQ_TASK_COMPLETE,
	ICE_AQ_TASK_CANCELED,
पूर्ण;

काष्ठा ice_aq_task अणु
	काष्ठा hlist_node entry;

	u16 opcode;
	काष्ठा ice_rq_event_info *event;
	क्रमागत ice_aq_task_state state;
पूर्ण;

/**
 * ice_aq_रुको_क्रम_event - Wait क्रम an AdminQ event from firmware
 * @pf: poपूर्णांकer to the PF निजी काष्ठाure
 * @opcode: the opcode to रुको क्रम
 * @समयout: how दीर्घ to रुको, in jअगरfies
 * @event: storage क्रम the event info
 *
 * Waits क्रम a specअगरic AdminQ completion event on the ARQ क्रम a given PF. The
 * current thपढ़ो will be put to sleep until the specअगरied event occurs or
 * until the given समयout is reached.
 *
 * To obtain only the descriptor contents, pass an event without an allocated
 * msg_buf. If the complete data buffer is desired, allocate the
 * event->msg_buf with enough space ahead of समय.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
पूर्णांक ice_aq_रुको_क्रम_event(काष्ठा ice_pf *pf, u16 opcode, अचिन्हित दीर्घ समयout,
			  काष्ठा ice_rq_event_info *event)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_aq_task *task;
	अचिन्हित दीर्घ start;
	दीर्घ ret;
	पूर्णांक err;

	task = kzalloc(माप(*task), GFP_KERNEL);
	अगर (!task)
		वापस -ENOMEM;

	INIT_HLIST_NODE(&task->entry);
	task->opcode = opcode;
	task->event = event;
	task->state = ICE_AQ_TASK_WAITING;

	spin_lock_bh(&pf->aq_रुको_lock);
	hlist_add_head(&task->entry, &pf->aq_रुको_list);
	spin_unlock_bh(&pf->aq_रुको_lock);

	start = jअगरfies;

	ret = रुको_event_पूर्णांकerruptible_समयout(pf->aq_रुको_queue, task->state,
					       समयout);
	चयन (task->state) अणु
	हाल ICE_AQ_TASK_WAITING:
		err = ret < 0 ? ret : -ETIMEDOUT;
		अवरोध;
	हाल ICE_AQ_TASK_CANCELED:
		err = ret < 0 ? ret : -ECANCELED;
		अवरोध;
	हाल ICE_AQ_TASK_COMPLETE:
		err = ret < 0 ? ret : 0;
		अवरोध;
	शेष:
		WARN(1, "Unexpected AdminQ wait task state %u", task->state);
		err = -EINVAL;
		अवरोध;
	पूर्ण

	dev_dbg(dev, "Waited %u msecs (max %u msecs) for firmware response to op 0x%04x\n",
		jअगरfies_to_msecs(jअगरfies - start),
		jअगरfies_to_msecs(समयout),
		opcode);

	spin_lock_bh(&pf->aq_रुको_lock);
	hlist_del(&task->entry);
	spin_unlock_bh(&pf->aq_रुको_lock);
	kमुक्त(task);

	वापस err;
पूर्ण

/**
 * ice_aq_check_events - Check अगर any thपढ़ो is रुकोing क्रम an AdminQ event
 * @pf: poपूर्णांकer to the PF निजी काष्ठाure
 * @opcode: the opcode of the event
 * @event: the event to check
 *
 * Loops over the current list of pending thपढ़ोs रुकोing क्रम an AdminQ event.
 * For each matching task, copy the contents of the event पूर्णांकo the task
 * काष्ठाure and wake up the thपढ़ो.
 *
 * If multiple thपढ़ोs रुको क्रम the same opcode, they will all be woken up.
 *
 * Note that event->msg_buf will only be duplicated अगर the event has a buffer
 * with enough space alपढ़ोy allocated. Otherwise, only the descriptor and
 * message length will be copied.
 *
 * Returns: true अगर an event was found, false otherwise
 */
अटल व्योम ice_aq_check_events(काष्ठा ice_pf *pf, u16 opcode,
				काष्ठा ice_rq_event_info *event)
अणु
	काष्ठा ice_aq_task *task;
	bool found = false;

	spin_lock_bh(&pf->aq_रुको_lock);
	hlist_क्रम_each_entry(task, &pf->aq_रुको_list, entry) अणु
		अगर (task->state || task->opcode != opcode)
			जारी;

		स_नकल(&task->event->desc, &event->desc, माप(event->desc));
		task->event->msg_len = event->msg_len;

		/* Only copy the data buffer अगर a destination was set */
		अगर (task->event->msg_buf &&
		    task->event->buf_len > event->buf_len) अणु
			स_नकल(task->event->msg_buf, event->msg_buf,
			       event->buf_len);
			task->event->buf_len = event->buf_len;
		पूर्ण

		task->state = ICE_AQ_TASK_COMPLETE;
		found = true;
	पूर्ण
	spin_unlock_bh(&pf->aq_रुको_lock);

	अगर (found)
		wake_up(&pf->aq_रुको_queue);
पूर्ण

/**
 * ice_aq_cancel_रुकोing_tasks - Immediately cancel all रुकोing tasks
 * @pf: the PF निजी काष्ठाure
 *
 * Set all रुकोing tasks to ICE_AQ_TASK_CANCELED, and wake up their thपढ़ोs.
 * This will then cause ice_aq_रुको_क्रम_event to निकास with -ECANCELED.
 */
अटल व्योम ice_aq_cancel_रुकोing_tasks(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_aq_task *task;

	spin_lock_bh(&pf->aq_रुको_lock);
	hlist_क्रम_each_entry(task, &pf->aq_रुको_list, entry)
		task->state = ICE_AQ_TASK_CANCELED;
	spin_unlock_bh(&pf->aq_रुको_lock);

	wake_up(&pf->aq_रुको_queue);
पूर्ण

/**
 * __ice_clean_ctrlq - helper function to clean controlq rings
 * @pf: ptr to काष्ठा ice_pf
 * @q_type: specअगरic Control queue type
 */
अटल पूर्णांक __ice_clean_ctrlq(काष्ठा ice_pf *pf, क्रमागत ice_ctl_q q_type)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_rq_event_info event;
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_ctl_q_info *cq;
	u16 pending, i = 0;
	स्थिर अक्षर *qtype;
	u32 oldval, val;

	/* Do not clean control queue अगर/when PF reset fails */
	अगर (test_bit(ICE_RESET_FAILED, pf->state))
		वापस 0;

	चयन (q_type) अणु
	हाल ICE_CTL_Q_ADMIN:
		cq = &hw->adminq;
		qtype = "Admin";
		अवरोध;
	हाल ICE_CTL_Q_MAILBOX:
		cq = &hw->mailboxq;
		qtype = "Mailbox";
		/* we are going to try to detect a malicious VF, so set the
		 * state to begin detection
		 */
		hw->mbx_snapshot.mbx_buf.state = ICE_MAL_VF_DETECT_STATE_NEW_SNAPSHOT;
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown control queue type 0x%x\n", q_type);
		वापस 0;
	पूर्ण

	/* check क्रम error indications - PF_xx_AxQLEN रेजिस्टर layout क्रम
	 * FW/MBX/SB are identical so just use defines क्रम PF_FW_AxQLEN.
	 */
	val = rd32(hw, cq->rq.len);
	अगर (val & (PF_FW_ARQLEN_ARQVFE_M | PF_FW_ARQLEN_ARQOVFL_M |
		   PF_FW_ARQLEN_ARQCRIT_M)) अणु
		oldval = val;
		अगर (val & PF_FW_ARQLEN_ARQVFE_M)
			dev_dbg(dev, "%s Receive Queue VF Error detected\n",
				qtype);
		अगर (val & PF_FW_ARQLEN_ARQOVFL_M) अणु
			dev_dbg(dev, "%s Receive Queue Overflow Error detected\n",
				qtype);
		पूर्ण
		अगर (val & PF_FW_ARQLEN_ARQCRIT_M)
			dev_dbg(dev, "%s Receive Queue Critical Error detected\n",
				qtype);
		val &= ~(PF_FW_ARQLEN_ARQVFE_M | PF_FW_ARQLEN_ARQOVFL_M |
			 PF_FW_ARQLEN_ARQCRIT_M);
		अगर (oldval != val)
			wr32(hw, cq->rq.len, val);
	पूर्ण

	val = rd32(hw, cq->sq.len);
	अगर (val & (PF_FW_ATQLEN_ATQVFE_M | PF_FW_ATQLEN_ATQOVFL_M |
		   PF_FW_ATQLEN_ATQCRIT_M)) अणु
		oldval = val;
		अगर (val & PF_FW_ATQLEN_ATQVFE_M)
			dev_dbg(dev, "%s Send Queue VF Error detected\n",
				qtype);
		अगर (val & PF_FW_ATQLEN_ATQOVFL_M) अणु
			dev_dbg(dev, "%s Send Queue Overflow Error detected\n",
				qtype);
		पूर्ण
		अगर (val & PF_FW_ATQLEN_ATQCRIT_M)
			dev_dbg(dev, "%s Send Queue Critical Error detected\n",
				qtype);
		val &= ~(PF_FW_ATQLEN_ATQVFE_M | PF_FW_ATQLEN_ATQOVFL_M |
			 PF_FW_ATQLEN_ATQCRIT_M);
		अगर (oldval != val)
			wr32(hw, cq->sq.len, val);
	पूर्ण

	event.buf_len = cq->rq_buf_size;
	event.msg_buf = kzalloc(event.buf_len, GFP_KERNEL);
	अगर (!event.msg_buf)
		वापस 0;

	करो अणु
		क्रमागत ice_status ret;
		u16 opcode;

		ret = ice_clean_rq_elem(hw, cq, &event, &pending);
		अगर (ret == ICE_ERR_AQ_NO_WORK)
			अवरोध;
		अगर (ret) अणु
			dev_err(dev, "%s Receive Queue event error %s\n", qtype,
				ice_stat_str(ret));
			अवरोध;
		पूर्ण

		opcode = le16_to_cpu(event.desc.opcode);

		/* Notअगरy any thपढ़ो that might be रुकोing क्रम this event */
		ice_aq_check_events(pf, opcode, &event);

		चयन (opcode) अणु
		हाल ice_aqc_opc_get_link_status:
			अगर (ice_handle_link_event(pf, &event))
				dev_err(dev, "Could not handle link event\n");
			अवरोध;
		हाल ice_aqc_opc_event_lan_overflow:
			ice_vf_lan_overflow_event(pf, &event);
			अवरोध;
		हाल ice_mbx_opc_send_msg_to_pf:
			अगर (!ice_is_malicious_vf(pf, &event, i, pending))
				ice_vc_process_vf_msg(pf, &event);
			अवरोध;
		हाल ice_aqc_opc_fw_logging:
			ice_output_fw_log(hw, &event.desc, event.msg_buf);
			अवरोध;
		हाल ice_aqc_opc_lldp_set_mib_change:
			ice_dcb_process_lldp_set_mib_change(pf, &event);
			अवरोध;
		शेष:
			dev_dbg(dev, "%s Receive Queue unknown event 0x%04x ignored\n",
				qtype, opcode);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (pending && (i++ < ICE_DFLT_IRQ_WORK));

	kमुक्त(event.msg_buf);

	वापस pending && (i == ICE_DFLT_IRQ_WORK);
पूर्ण

/**
 * ice_ctrlq_pending - check अगर there is a dअगरference between ntc and ntu
 * @hw: poपूर्णांकer to hardware info
 * @cq: control queue inक्रमmation
 *
 * वापसs true अगर there are pending messages in a queue, false अगर there aren't
 */
अटल bool ice_ctrlq_pending(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	u16 ntu;

	ntu = (u16)(rd32(hw, cq->rq.head) & cq->rq.head_mask);
	वापस cq->rq.next_to_clean != ntu;
पूर्ण

/**
 * ice_clean_adminq_subtask - clean the AdminQ rings
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_clean_adminq_subtask(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;

	अगर (!test_bit(ICE_ADMINQ_EVENT_PENDING, pf->state))
		वापस;

	अगर (__ice_clean_ctrlq(pf, ICE_CTL_Q_ADMIN))
		वापस;

	clear_bit(ICE_ADMINQ_EVENT_PENDING, pf->state);

	/* There might be a situation where new messages arrive to a control
	 * queue between processing the last message and clearing the
	 * EVENT_PENDING bit. So beक्रमe निकासing, check queue head again (using
	 * ice_ctrlq_pending) and process new messages अगर any.
	 */
	अगर (ice_ctrlq_pending(hw, &hw->adminq))
		__ice_clean_ctrlq(pf, ICE_CTL_Q_ADMIN);

	ice_flush(hw);
पूर्ण

/**
 * ice_clean_mailboxq_subtask - clean the MailboxQ rings
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_clean_mailboxq_subtask(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;

	अगर (!test_bit(ICE_MAILBOXQ_EVENT_PENDING, pf->state))
		वापस;

	अगर (__ice_clean_ctrlq(pf, ICE_CTL_Q_MAILBOX))
		वापस;

	clear_bit(ICE_MAILBOXQ_EVENT_PENDING, pf->state);

	अगर (ice_ctrlq_pending(hw, &hw->mailboxq))
		__ice_clean_ctrlq(pf, ICE_CTL_Q_MAILBOX);

	ice_flush(hw);
पूर्ण

/**
 * ice_service_task_schedule - schedule the service task to wake up
 * @pf: board निजी काष्ठाure
 *
 * If not alपढ़ोy scheduled, this माला_दो the task पूर्णांकo the work queue.
 */
व्योम ice_service_task_schedule(काष्ठा ice_pf *pf)
अणु
	अगर (!test_bit(ICE_SERVICE_DIS, pf->state) &&
	    !test_and_set_bit(ICE_SERVICE_SCHED, pf->state) &&
	    !test_bit(ICE_NEEDS_RESTART, pf->state))
		queue_work(ice_wq, &pf->serv_task);
पूर्ण

/**
 * ice_service_task_complete - finish up the service task
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_service_task_complete(काष्ठा ice_pf *pf)
अणु
	WARN_ON(!test_bit(ICE_SERVICE_SCHED, pf->state));

	/* क्रमce memory (pf->state) to sync beक्रमe next service task */
	smp_mb__beक्रमe_atomic();
	clear_bit(ICE_SERVICE_SCHED, pf->state);
पूर्ण

/**
 * ice_service_task_stop - stop service task and cancel works
 * @pf: board निजी काष्ठाure
 *
 * Return 0 अगर the ICE_SERVICE_DIS bit was not alपढ़ोy set,
 * 1 otherwise.
 */
अटल पूर्णांक ice_service_task_stop(काष्ठा ice_pf *pf)
अणु
	पूर्णांक ret;

	ret = test_and_set_bit(ICE_SERVICE_DIS, pf->state);

	अगर (pf->serv_पंचांगr.function)
		del_समयr_sync(&pf->serv_पंचांगr);
	अगर (pf->serv_task.func)
		cancel_work_sync(&pf->serv_task);

	clear_bit(ICE_SERVICE_SCHED, pf->state);
	वापस ret;
पूर्ण

/**
 * ice_service_task_restart - restart service task and schedule works
 * @pf: board निजी काष्ठाure
 *
 * This function is needed क्रम suspend and resume works (e.g WoL scenario)
 */
अटल व्योम ice_service_task_restart(काष्ठा ice_pf *pf)
अणु
	clear_bit(ICE_SERVICE_DIS, pf->state);
	ice_service_task_schedule(pf);
पूर्ण

/**
 * ice_service_समयr - समयr callback to schedule service task
 * @t: poपूर्णांकer to समयr_list
 */
अटल व्योम ice_service_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ice_pf *pf = from_समयr(pf, t, serv_पंचांगr);

	mod_समयr(&pf->serv_पंचांगr, round_jअगरfies(pf->serv_पंचांगr_period + jअगरfies));
	ice_service_task_schedule(pf);
पूर्ण

/**
 * ice_handle_mdd_event - handle malicious driver detect event
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * Called from service task. OICR पूर्णांकerrupt handler indicates MDD event.
 * VF MDD logging is guarded by net_ratelimit. Additional PF and VF log
 * messages are wrapped by netअगर_msg_[rx|tx]_err. Since VF Rx MDD events
 * disable the queue, the PF can be configured to reset the VF using ethtool
 * निजी flag mdd-स्वतः-reset-vf.
 */
अटल व्योम ice_handle_mdd_event(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	अचिन्हित पूर्णांक i;
	u32 reg;

	अगर (!test_and_clear_bit(ICE_MDD_EVENT_PENDING, pf->state)) अणु
		/* Since the VF MDD event logging is rate limited, check अगर
		 * there are pending MDD events.
		 */
		ice_prपूर्णांक_vfs_mdd_events(pf);
		वापस;
	पूर्ण

	/* find what triggered an MDD event */
	reg = rd32(hw, GL_MDET_TX_PQM);
	अगर (reg & GL_MDET_TX_PQM_VALID_M) अणु
		u8 pf_num = (reg & GL_MDET_TX_PQM_PF_NUM_M) >>
				GL_MDET_TX_PQM_PF_NUM_S;
		u16 vf_num = (reg & GL_MDET_TX_PQM_VF_NUM_M) >>
				GL_MDET_TX_PQM_VF_NUM_S;
		u8 event = (reg & GL_MDET_TX_PQM_MAL_TYPE_M) >>
				GL_MDET_TX_PQM_MAL_TYPE_S;
		u16 queue = ((reg & GL_MDET_TX_PQM_QNUM_M) >>
				GL_MDET_TX_PQM_QNUM_S);

		अगर (netअगर_msg_tx_err(pf))
			dev_info(dev, "Malicious Driver Detection event %d on TX queue %d PF# %d VF# %d\n",
				 event, queue, pf_num, vf_num);
		wr32(hw, GL_MDET_TX_PQM, 0xffffffff);
	पूर्ण

	reg = rd32(hw, GL_MDET_TX_TCLAN);
	अगर (reg & GL_MDET_TX_TCLAN_VALID_M) अणु
		u8 pf_num = (reg & GL_MDET_TX_TCLAN_PF_NUM_M) >>
				GL_MDET_TX_TCLAN_PF_NUM_S;
		u16 vf_num = (reg & GL_MDET_TX_TCLAN_VF_NUM_M) >>
				GL_MDET_TX_TCLAN_VF_NUM_S;
		u8 event = (reg & GL_MDET_TX_TCLAN_MAL_TYPE_M) >>
				GL_MDET_TX_TCLAN_MAL_TYPE_S;
		u16 queue = ((reg & GL_MDET_TX_TCLAN_QNUM_M) >>
				GL_MDET_TX_TCLAN_QNUM_S);

		अगर (netअगर_msg_tx_err(pf))
			dev_info(dev, "Malicious Driver Detection event %d on TX queue %d PF# %d VF# %d\n",
				 event, queue, pf_num, vf_num);
		wr32(hw, GL_MDET_TX_TCLAN, 0xffffffff);
	पूर्ण

	reg = rd32(hw, GL_MDET_RX);
	अगर (reg & GL_MDET_RX_VALID_M) अणु
		u8 pf_num = (reg & GL_MDET_RX_PF_NUM_M) >>
				GL_MDET_RX_PF_NUM_S;
		u16 vf_num = (reg & GL_MDET_RX_VF_NUM_M) >>
				GL_MDET_RX_VF_NUM_S;
		u8 event = (reg & GL_MDET_RX_MAL_TYPE_M) >>
				GL_MDET_RX_MAL_TYPE_S;
		u16 queue = ((reg & GL_MDET_RX_QNUM_M) >>
				GL_MDET_RX_QNUM_S);

		अगर (netअगर_msg_rx_err(pf))
			dev_info(dev, "Malicious Driver Detection event %d on RX queue %d PF# %d VF# %d\n",
				 event, queue, pf_num, vf_num);
		wr32(hw, GL_MDET_RX, 0xffffffff);
	पूर्ण

	/* check to see अगर this PF caused an MDD event */
	reg = rd32(hw, PF_MDET_TX_PQM);
	अगर (reg & PF_MDET_TX_PQM_VALID_M) अणु
		wr32(hw, PF_MDET_TX_PQM, 0xFFFF);
		अगर (netअगर_msg_tx_err(pf))
			dev_info(dev, "Malicious Driver Detection event TX_PQM detected on PF\n");
	पूर्ण

	reg = rd32(hw, PF_MDET_TX_TCLAN);
	अगर (reg & PF_MDET_TX_TCLAN_VALID_M) अणु
		wr32(hw, PF_MDET_TX_TCLAN, 0xFFFF);
		अगर (netअगर_msg_tx_err(pf))
			dev_info(dev, "Malicious Driver Detection event TX_TCLAN detected on PF\n");
	पूर्ण

	reg = rd32(hw, PF_MDET_RX);
	अगर (reg & PF_MDET_RX_VALID_M) अणु
		wr32(hw, PF_MDET_RX, 0xFFFF);
		अगर (netअगर_msg_rx_err(pf))
			dev_info(dev, "Malicious Driver Detection event RX detected on PF\n");
	पूर्ण

	/* Check to see अगर one of the VFs caused an MDD event, and then
	 * increment counters and set prपूर्णांक pending
	 */
	ice_क्रम_each_vf(pf, i) अणु
		काष्ठा ice_vf *vf = &pf->vf[i];

		reg = rd32(hw, VP_MDET_TX_PQM(i));
		अगर (reg & VP_MDET_TX_PQM_VALID_M) अणु
			wr32(hw, VP_MDET_TX_PQM(i), 0xFFFF);
			vf->mdd_tx_events.count++;
			set_bit(ICE_MDD_VF_PRINT_PENDING, pf->state);
			अगर (netअगर_msg_tx_err(pf))
				dev_info(dev, "Malicious Driver Detection event TX_PQM detected on VF %d\n",
					 i);
		पूर्ण

		reg = rd32(hw, VP_MDET_TX_TCLAN(i));
		अगर (reg & VP_MDET_TX_TCLAN_VALID_M) अणु
			wr32(hw, VP_MDET_TX_TCLAN(i), 0xFFFF);
			vf->mdd_tx_events.count++;
			set_bit(ICE_MDD_VF_PRINT_PENDING, pf->state);
			अगर (netअगर_msg_tx_err(pf))
				dev_info(dev, "Malicious Driver Detection event TX_TCLAN detected on VF %d\n",
					 i);
		पूर्ण

		reg = rd32(hw, VP_MDET_TX_TDPU(i));
		अगर (reg & VP_MDET_TX_TDPU_VALID_M) अणु
			wr32(hw, VP_MDET_TX_TDPU(i), 0xFFFF);
			vf->mdd_tx_events.count++;
			set_bit(ICE_MDD_VF_PRINT_PENDING, pf->state);
			अगर (netअगर_msg_tx_err(pf))
				dev_info(dev, "Malicious Driver Detection event TX_TDPU detected on VF %d\n",
					 i);
		पूर्ण

		reg = rd32(hw, VP_MDET_RX(i));
		अगर (reg & VP_MDET_RX_VALID_M) अणु
			wr32(hw, VP_MDET_RX(i), 0xFFFF);
			vf->mdd_rx_events.count++;
			set_bit(ICE_MDD_VF_PRINT_PENDING, pf->state);
			अगर (netअगर_msg_rx_err(pf))
				dev_info(dev, "Malicious Driver Detection event RX detected on VF %d\n",
					 i);

			/* Since the queue is disabled on VF Rx MDD events, the
			 * PF can be configured to reset the VF through ethtool
			 * निजी flag mdd-स्वतः-reset-vf.
			 */
			अगर (test_bit(ICE_FLAG_MDD_AUTO_RESET_VF, pf->flags)) अणु
				/* VF MDD event counters will be cleared by
				 * reset, so prपूर्णांक the event prior to reset.
				 */
				ice_prपूर्णांक_vf_rx_mdd_event(vf);
				ice_reset_vf(&pf->vf[i], false);
			पूर्ण
		पूर्ण
	पूर्ण

	ice_prपूर्णांक_vfs_mdd_events(pf);
पूर्ण

/**
 * ice_क्रमce_phys_link_state - Force the physical link state
 * @vsi: VSI to क्रमce the physical link state to up/करोwn
 * @link_up: true/false indicates to set the physical link to up/करोwn
 *
 * Force the physical link state by getting the current PHY capabilities from
 * hardware and setting the PHY config based on the determined capabilities. If
 * link changes a link event will be triggered because both the Enable Automatic
 * Link Update and LESM Enable bits are set when setting the PHY capabilities.
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक ice_क्रमce_phys_link_state(काष्ठा ice_vsi *vsi, bool link_up)
अणु
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	काष्ठा ice_aqc_set_phy_cfg_data *cfg;
	काष्ठा ice_port_info *pi;
	काष्ठा device *dev;
	पूर्णांक retcode;

	अगर (!vsi || !vsi->port_info || !vsi->back)
		वापस -EINVAL;
	अगर (vsi->type != ICE_VSI_PF)
		वापस 0;

	dev = ice_pf_to_dev(vsi->back);

	pi = vsi->port_info;

	pcaps = kzalloc(माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस -ENOMEM;

	retcode = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_ACTIVE_CFG, pcaps,
				      शून्य);
	अगर (retcode) अणु
		dev_err(dev, "Failed to get phy capabilities, VSI %d error %d\n",
			vsi->vsi_num, retcode);
		retcode = -EIO;
		जाओ out;
	पूर्ण

	/* No change in link */
	अगर (link_up == !!(pcaps->caps & ICE_AQC_PHY_EN_LINK) &&
	    link_up == !!(pi->phy.link_info.link_info & ICE_AQ_LINK_UP))
		जाओ out;

	/* Use the current user PHY configuration. The current user PHY
	 * configuration is initialized during probe from PHY capabilities
	 * software mode, and updated on set PHY configuration.
	 */
	cfg = kmemdup(&pi->phy.curr_user_phy_cfg, माप(*cfg), GFP_KERNEL);
	अगर (!cfg) अणु
		retcode = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg->caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;
	अगर (link_up)
		cfg->caps |= ICE_AQ_PHY_ENA_LINK;
	अन्यथा
		cfg->caps &= ~ICE_AQ_PHY_ENA_LINK;

	retcode = ice_aq_set_phy_cfg(&vsi->back->hw, pi, cfg, शून्य);
	अगर (retcode) अणु
		dev_err(dev, "Failed to set phy config, VSI %d error %d\n",
			vsi->vsi_num, retcode);
		retcode = -EIO;
	पूर्ण

	kमुक्त(cfg);
out:
	kमुक्त(pcaps);
	वापस retcode;
पूर्ण

/**
 * ice_init_nvm_phy_type - Initialize the NVM PHY type
 * @pi: port info काष्ठाure
 *
 * Initialize nvm_phy_type_[low|high] क्रम link lenient mode support
 */
अटल पूर्णांक ice_init_nvm_phy_type(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	काष्ठा ice_pf *pf = pi->hw->back;
	क्रमागत ice_status status;
	पूर्णांक err = 0;

	pcaps = kzalloc(माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस -ENOMEM;

	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP_NO_MEDIA, pcaps,
				     शून्य);

	अगर (status) अणु
		dev_err(ice_pf_to_dev(pf), "Get PHY capability failed.\n");
		err = -EIO;
		जाओ out;
	पूर्ण

	pf->nvm_phy_type_hi = pcaps->phy_type_high;
	pf->nvm_phy_type_lo = pcaps->phy_type_low;

out:
	kमुक्त(pcaps);
	वापस err;
पूर्ण

/**
 * ice_init_link_dflt_override - Initialize link शेष override
 * @pi: port info काष्ठाure
 *
 * Initialize link शेष override and PHY total port shutकरोwn during probe
 */
अटल व्योम ice_init_link_dflt_override(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_link_शेष_override_tlv *lकरो;
	काष्ठा ice_pf *pf = pi->hw->back;

	lकरो = &pf->link_dflt_override;
	अगर (ice_get_link_शेष_override(lकरो, pi))
		वापस;

	अगर (!(lकरो->options & ICE_LINK_OVERRIDE_PORT_DIS))
		वापस;

	/* Enable Total Port Shutकरोwn (override/replace link-करोwn-on-बंद
	 * ethtool निजी flag) क्रम ports with Port Disable bit set.
	 */
	set_bit(ICE_FLAG_TOTAL_PORT_SHUTDOWN_ENA, pf->flags);
	set_bit(ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA, pf->flags);
पूर्ण

/**
 * ice_init_phy_cfg_dflt_override - Initialize PHY cfg शेष override settings
 * @pi: port info काष्ठाure
 *
 * If शेष override is enabled, initialize the user PHY cfg speed and FEC
 * settings using the शेष override mask from the NVM.
 *
 * The PHY should only be configured with the शेष override settings the
 * first समय media is available. The ICE_LINK_DEFAULT_OVERRIDE_PENDING state
 * is used to indicate that the user PHY cfg शेष override is initialized
 * and the PHY has not been configured with the शेष override settings. The
 * state is set here, and cleared in ice_configure_phy the first समय the PHY is
 * configured.
 *
 * This function should be called only अगर the FW करोesn't support शेष
 * configuration mode, as reported by ice_fw_supports_report_dflt_cfg.
 */
अटल व्योम ice_init_phy_cfg_dflt_override(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_link_शेष_override_tlv *lकरो;
	काष्ठा ice_aqc_set_phy_cfg_data *cfg;
	काष्ठा ice_phy_info *phy = &pi->phy;
	काष्ठा ice_pf *pf = pi->hw->back;

	lकरो = &pf->link_dflt_override;

	/* If link शेष override is enabled, use to mask NVM PHY capabilities
	 * क्रम speed and FEC शेष configuration.
	 */
	cfg = &phy->curr_user_phy_cfg;

	अगर (lकरो->phy_type_low || lकरो->phy_type_high) अणु
		cfg->phy_type_low = pf->nvm_phy_type_lo &
				    cpu_to_le64(lकरो->phy_type_low);
		cfg->phy_type_high = pf->nvm_phy_type_hi &
				     cpu_to_le64(lकरो->phy_type_high);
	पूर्ण
	cfg->link_fec_opt = lकरो->fec_options;
	phy->curr_user_fec_req = ICE_FEC_AUTO;

	set_bit(ICE_LINK_DEFAULT_OVERRIDE_PENDING, pf->state);
पूर्ण

/**
 * ice_init_phy_user_cfg - Initialize the PHY user configuration
 * @pi: port info काष्ठाure
 *
 * Initialize the current user PHY configuration, speed, FEC, and FC requested
 * mode to शेष. The PHY शेषs are from get PHY capabilities topology
 * with media so call when media is first available. An error is वापसed अगर
 * called when media is not available. The PHY initialization completed state is
 * set here.
 *
 * These configurations are used when setting PHY
 * configuration. The user PHY configuration is updated on set PHY
 * configuration. Returns 0 on success, negative on failure
 */
अटल पूर्णांक ice_init_phy_user_cfg(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	काष्ठा ice_phy_info *phy = &pi->phy;
	काष्ठा ice_pf *pf = pi->hw->back;
	क्रमागत ice_status status;
	पूर्णांक err = 0;

	अगर (!(phy->link_info.link_info & ICE_AQ_MEDIA_AVAILABLE))
		वापस -EIO;

	pcaps = kzalloc(माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस -ENOMEM;

	अगर (ice_fw_supports_report_dflt_cfg(pi->hw))
		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_DFLT_CFG,
					     pcaps, शून्य);
	अन्यथा
		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP_MEDIA,
					     pcaps, शून्य);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(pf), "Get PHY capability failed.\n");
		err = -EIO;
		जाओ err_out;
	पूर्ण

	ice_copy_phy_caps_to_cfg(pi, pcaps, &pi->phy.curr_user_phy_cfg);

	/* check अगर lenient mode is supported and enabled */
	अगर (ice_fw_supports_link_override(pi->hw) &&
	    !(pcaps->module_compliance_enक्रमcement &
	      ICE_AQC_MOD_ENFORCE_STRICT_MODE)) अणु
		set_bit(ICE_FLAG_LINK_LENIENT_MODE_ENA, pf->flags);

		/* अगर the FW supports शेष PHY configuration mode, then the driver
		 * करोes not have to apply link override settings. If not,
		 * initialize user PHY configuration with link override values
		 */
		अगर (!ice_fw_supports_report_dflt_cfg(pi->hw) &&
		    (pf->link_dflt_override.options & ICE_LINK_OVERRIDE_EN)) अणु
			ice_init_phy_cfg_dflt_override(pi);
			जाओ out;
		पूर्ण
	पूर्ण

	/* अगर link शेष override is not enabled, set user flow control and
	 * FEC settings based on what get_phy_caps वापसed
	 */
	phy->curr_user_fec_req = ice_caps_to_fec_mode(pcaps->caps,
						      pcaps->link_fec_options);
	phy->curr_user_fc_req = ice_caps_to_fc_mode(pcaps->caps);

out:
	phy->curr_user_speed_req = ICE_AQ_LINK_SPEED_M;
	set_bit(ICE_PHY_INIT_COMPLETE, pf->state);
err_out:
	kमुक्त(pcaps);
	वापस err;
पूर्ण

/**
 * ice_configure_phy - configure PHY
 * @vsi: VSI of PHY
 *
 * Set the PHY configuration. If the current PHY configuration is the same as
 * the curr_user_phy_cfg, then करो nothing to aव्योम link flap. Otherwise
 * configure the based get PHY capabilities क्रम topology with media.
 */
अटल पूर्णांक ice_configure_phy(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vsi->back);
	काष्ठा ice_port_info *pi = vsi->port_info;
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	काष्ठा ice_aqc_set_phy_cfg_data *cfg;
	काष्ठा ice_phy_info *phy = &pi->phy;
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_status status;
	पूर्णांक err = 0;

	/* Ensure we have media as we cannot configure a medialess port */
	अगर (!(phy->link_info.link_info & ICE_AQ_MEDIA_AVAILABLE))
		वापस -EPERM;

	ice_prपूर्णांक_topo_conflict(vsi);

	अगर (phy->link_info.topo_media_conflict == ICE_AQ_LINK_TOPO_UNSUPP_MEDIA)
		वापस -EPERM;

	अगर (test_bit(ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA, pf->flags))
		वापस ice_क्रमce_phys_link_state(vsi, true);

	pcaps = kzalloc(माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस -ENOMEM;

	/* Get current PHY config */
	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_ACTIVE_CFG, pcaps,
				     शून्य);
	अगर (status) अणु
		dev_err(dev, "Failed to get PHY configuration, VSI %d error %s\n",
			vsi->vsi_num, ice_stat_str(status));
		err = -EIO;
		जाओ करोne;
	पूर्ण

	/* If PHY enable link is configured and configuration has not changed,
	 * there's nothing to करो
	 */
	अगर (pcaps->caps & ICE_AQC_PHY_EN_LINK &&
	    ice_phy_caps_equals_cfg(pcaps, &phy->curr_user_phy_cfg))
		जाओ करोne;

	/* Use PHY topology as baseline क्रम configuration */
	स_रखो(pcaps, 0, माप(*pcaps));
	अगर (ice_fw_supports_report_dflt_cfg(pi->hw))
		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_DFLT_CFG,
					     pcaps, शून्य);
	अन्यथा
		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP_MEDIA,
					     pcaps, शून्य);
	अगर (status) अणु
		dev_err(dev, "Failed to get PHY caps, VSI %d error %s\n",
			vsi->vsi_num, ice_stat_str(status));
		err = -EIO;
		जाओ करोne;
	पूर्ण

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	ice_copy_phy_caps_to_cfg(pi, pcaps, cfg);

	/* Speed - If शेष override pending, use curr_user_phy_cfg set in
	 * ice_init_phy_user_cfg_lकरो.
	 */
	अगर (test_and_clear_bit(ICE_LINK_DEFAULT_OVERRIDE_PENDING,
			       vsi->back->state)) अणु
		cfg->phy_type_low = phy->curr_user_phy_cfg.phy_type_low;
		cfg->phy_type_high = phy->curr_user_phy_cfg.phy_type_high;
	पूर्ण अन्यथा अणु
		u64 phy_low = 0, phy_high = 0;

		ice_update_phy_type(&phy_low, &phy_high,
				    pi->phy.curr_user_speed_req);
		cfg->phy_type_low = pcaps->phy_type_low & cpu_to_le64(phy_low);
		cfg->phy_type_high = pcaps->phy_type_high &
				     cpu_to_le64(phy_high);
	पूर्ण

	/* Can't provide what was requested; use PHY capabilities */
	अगर (!cfg->phy_type_low && !cfg->phy_type_high) अणु
		cfg->phy_type_low = pcaps->phy_type_low;
		cfg->phy_type_high = pcaps->phy_type_high;
	पूर्ण

	/* FEC */
	ice_cfg_phy_fec(pi, cfg, phy->curr_user_fec_req);

	/* Can't provide what was requested; use PHY capabilities */
	अगर (cfg->link_fec_opt !=
	    (cfg->link_fec_opt & pcaps->link_fec_options)) अणु
		cfg->caps |= pcaps->caps & ICE_AQC_PHY_EN_AUTO_FEC;
		cfg->link_fec_opt = pcaps->link_fec_options;
	पूर्ण

	/* Flow Control - always supported; no need to check against
	 * capabilities
	 */
	ice_cfg_phy_fc(pi, cfg, phy->curr_user_fc_req);

	/* Enable link and link update */
	cfg->caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT | ICE_AQ_PHY_ENA_LINK;

	status = ice_aq_set_phy_cfg(&pf->hw, pi, cfg, शून्य);
	अगर (status) अणु
		dev_err(dev, "Failed to set phy config, VSI %d error %s\n",
			vsi->vsi_num, ice_stat_str(status));
		err = -EIO;
	पूर्ण

	kमुक्त(cfg);
करोne:
	kमुक्त(pcaps);
	वापस err;
पूर्ण

/**
 * ice_check_media_subtask - Check क्रम media
 * @pf: poपूर्णांकer to PF काष्ठा
 *
 * If media is available, then initialize PHY user configuration अगर it is not
 * been, and configure the PHY अगर the पूर्णांकerface is up.
 */
अटल व्योम ice_check_media_subtask(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_port_info *pi;
	काष्ठा ice_vsi *vsi;
	पूर्णांक err;

	/* No need to check क्रम media अगर it's alपढ़ोy present */
	अगर (!test_bit(ICE_FLAG_NO_MEDIA, pf->flags))
		वापस;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi)
		वापस;

	/* Refresh link info and check अगर media is present */
	pi = vsi->port_info;
	err = ice_update_link_info(pi);
	अगर (err)
		वापस;

	अगर (pi->phy.link_info.link_info & ICE_AQ_MEDIA_AVAILABLE) अणु
		अगर (!test_bit(ICE_PHY_INIT_COMPLETE, pf->state))
			ice_init_phy_user_cfg(pi);

		/* PHY settings are reset on media insertion, reconfigure
		 * PHY to preserve settings.
		 */
		अगर (test_bit(ICE_VSI_DOWN, vsi->state) &&
		    test_bit(ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA, vsi->back->flags))
			वापस;

		err = ice_configure_phy(vsi);
		अगर (!err)
			clear_bit(ICE_FLAG_NO_MEDIA, pf->flags);

		/* A Link Status Event will be generated; the event handler
		 * will complete bringing the पूर्णांकerface up
		 */
	पूर्ण
पूर्ण

/**
 * ice_service_task - manage and run subtasks
 * @work: poपूर्णांकer to work_काष्ठा contained by the PF काष्ठा
 */
अटल व्योम ice_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ice_pf *pf = container_of(work, काष्ठा ice_pf, serv_task);
	अचिन्हित दीर्घ start_समय = jअगरfies;

	/* subtasks */

	/* process reset requests first */
	ice_reset_subtask(pf);

	/* bail अगर a reset/recovery cycle is pending or rebuild failed */
	अगर (ice_is_reset_in_progress(pf->state) ||
	    test_bit(ICE_SUSPENDED, pf->state) ||
	    test_bit(ICE_NEEDS_RESTART, pf->state)) अणु
		ice_service_task_complete(pf);
		वापस;
	पूर्ण

	ice_clean_adminq_subtask(pf);
	ice_check_media_subtask(pf);
	ice_check_क्रम_hang_subtask(pf);
	ice_sync_fltr_subtask(pf);
	ice_handle_mdd_event(pf);
	ice_watchकरोg_subtask(pf);

	अगर (ice_is_safe_mode(pf)) अणु
		ice_service_task_complete(pf);
		वापस;
	पूर्ण

	ice_process_vflr_event(pf);
	ice_clean_mailboxq_subtask(pf);
	ice_sync_arfs_fltrs(pf);
	ice_flush_fdir_ctx(pf);

	/* Clear ICE_SERVICE_SCHED flag to allow scheduling next event */
	ice_service_task_complete(pf);

	/* If the tasks have taken दीर्घer than one service समयr period
	 * or there is more work to be करोne, reset the service समयr to
	 * schedule the service task now.
	 */
	अगर (समय_after(jअगरfies, (start_समय + pf->serv_पंचांगr_period)) ||
	    test_bit(ICE_MDD_EVENT_PENDING, pf->state) ||
	    test_bit(ICE_VFLR_EVENT_PENDING, pf->state) ||
	    test_bit(ICE_MAILBOXQ_EVENT_PENDING, pf->state) ||
	    test_bit(ICE_FD_VF_FLUSH_CTX, pf->state) ||
	    test_bit(ICE_ADMINQ_EVENT_PENDING, pf->state))
		mod_समयr(&pf->serv_पंचांगr, jअगरfies);
पूर्ण

/**
 * ice_set_ctrlq_len - helper function to set controlq length
 * @hw: poपूर्णांकer to the HW instance
 */
अटल व्योम ice_set_ctrlq_len(काष्ठा ice_hw *hw)
अणु
	hw->adminq.num_rq_entries = ICE_AQ_LEN;
	hw->adminq.num_sq_entries = ICE_AQ_LEN;
	hw->adminq.rq_buf_size = ICE_AQ_MAX_BUF_LEN;
	hw->adminq.sq_buf_size = ICE_AQ_MAX_BUF_LEN;
	hw->mailboxq.num_rq_entries = PF_MBX_ARQLEN_ARQLEN_M;
	hw->mailboxq.num_sq_entries = ICE_MBXSQ_LEN;
	hw->mailboxq.rq_buf_size = ICE_MBXQ_MAX_BUF_LEN;
	hw->mailboxq.sq_buf_size = ICE_MBXQ_MAX_BUF_LEN;
पूर्ण

/**
 * ice_schedule_reset - schedule a reset
 * @pf: board निजी काष्ठाure
 * @reset: reset being requested
 */
पूर्णांक ice_schedule_reset(काष्ठा ice_pf *pf, क्रमागत ice_reset_req reset)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);

	/* bail out अगर earlier reset has failed */
	अगर (test_bit(ICE_RESET_FAILED, pf->state)) अणु
		dev_dbg(dev, "earlier reset has failed\n");
		वापस -EIO;
	पूर्ण
	/* bail अगर reset/recovery alपढ़ोy in progress */
	अगर (ice_is_reset_in_progress(pf->state)) अणु
		dev_dbg(dev, "Reset already in progress\n");
		वापस -EBUSY;
	पूर्ण

	चयन (reset) अणु
	हाल ICE_RESET_PFR:
		set_bit(ICE_PFR_REQ, pf->state);
		अवरोध;
	हाल ICE_RESET_CORER:
		set_bit(ICE_CORER_REQ, pf->state);
		अवरोध;
	हाल ICE_RESET_GLOBR:
		set_bit(ICE_GLOBR_REQ, pf->state);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ice_service_task_schedule(pf);
	वापस 0;
पूर्ण

/**
 * ice_irq_affinity_notअगरy - Callback क्रम affinity changes
 * @notअगरy: context as to what irq was changed
 * @mask: the new affinity mask
 *
 * This is a callback function used by the irq_set_affinity_notअगरier function
 * so that we may रेजिस्टर to receive changes to the irq affinity masks.
 */
अटल व्योम
ice_irq_affinity_notअगरy(काष्ठा irq_affinity_notअगरy *notअगरy,
			स्थिर cpumask_t *mask)
अणु
	काष्ठा ice_q_vector *q_vector =
		container_of(notअगरy, काष्ठा ice_q_vector, affinity_notअगरy);

	cpumask_copy(&q_vector->affinity_mask, mask);
पूर्ण

/**
 * ice_irq_affinity_release - Callback क्रम affinity notअगरier release
 * @ref: पूर्णांकernal core kernel usage
 *
 * This is a callback function used by the irq_set_affinity_notअगरier function
 * to inक्रमm the current notअगरication subscriber that they will no दीर्घer
 * receive notअगरications.
 */
अटल व्योम ice_irq_affinity_release(काष्ठा kref __always_unused *ref) अणुपूर्ण

/**
 * ice_vsi_ena_irq - Enable IRQ क्रम the given VSI
 * @vsi: the VSI being configured
 */
अटल पूर्णांक ice_vsi_ena_irq(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	पूर्णांक i;

	ice_क्रम_each_q_vector(vsi, i)
		ice_irq_dynamic_ena(hw, vsi, vsi->q_vectors[i]);

	ice_flush(hw);
	वापस 0;
पूर्ण

/**
 * ice_vsi_req_irq_msix - get MSI-X vectors from the OS क्रम the VSI
 * @vsi: the VSI being configured
 * @basename: name क्रम the vector
 */
अटल पूर्णांक ice_vsi_req_irq_msix(काष्ठा ice_vsi *vsi, अक्षर *basename)
अणु
	पूर्णांक q_vectors = vsi->num_q_vectors;
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक base = vsi->base_vector;
	काष्ठा device *dev;
	पूर्णांक rx_पूर्णांक_idx = 0;
	पूर्णांक tx_पूर्णांक_idx = 0;
	पूर्णांक vector, err;
	पूर्णांक irq_num;

	dev = ice_pf_to_dev(pf);
	क्रम (vector = 0; vector < q_vectors; vector++) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[vector];

		irq_num = pf->msix_entries[base + vector].vector;

		अगर (q_vector->tx.ring && q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name) - 1,
				 "%s-%s-%d", basename, "TxRx", rx_पूर्णांक_idx++);
			tx_पूर्णांक_idx++;
		पूर्ण अन्यथा अगर (q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name) - 1,
				 "%s-%s-%d", basename, "rx", rx_पूर्णांक_idx++);
		पूर्ण अन्यथा अगर (q_vector->tx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name) - 1,
				 "%s-%s-%d", basename, "tx", tx_पूर्णांक_idx++);
		पूर्ण अन्यथा अणु
			/* skip this unused q_vector */
			जारी;
		पूर्ण
		अगर (vsi->type == ICE_VSI_CTRL && vsi->vf_id != ICE_INVAL_VFID)
			err = devm_request_irq(dev, irq_num, vsi->irq_handler,
					       IRQF_SHARED, q_vector->name,
					       q_vector);
		अन्यथा
			err = devm_request_irq(dev, irq_num, vsi->irq_handler,
					       0, q_vector->name, q_vector);
		अगर (err) अणु
			netdev_err(vsi->netdev, "MSIX request_irq failed, error: %d\n",
				   err);
			जाओ मुक्त_q_irqs;
		पूर्ण

		/* रेजिस्टर क्रम affinity change notअगरications */
		अगर (!IS_ENABLED(CONFIG_RFS_ACCEL)) अणु
			काष्ठा irq_affinity_notअगरy *affinity_notअगरy;

			affinity_notअगरy = &q_vector->affinity_notअगरy;
			affinity_notअगरy->notअगरy = ice_irq_affinity_notअगरy;
			affinity_notअगरy->release = ice_irq_affinity_release;
			irq_set_affinity_notअगरier(irq_num, affinity_notअगरy);
		पूर्ण

		/* assign the mask क्रम this irq */
		irq_set_affinity_hपूर्णांक(irq_num, &q_vector->affinity_mask);
	पूर्ण

	vsi->irqs_पढ़ोy = true;
	वापस 0;

मुक्त_q_irqs:
	जबतक (vector) अणु
		vector--;
		irq_num = pf->msix_entries[base + vector].vector;
		अगर (!IS_ENABLED(CONFIG_RFS_ACCEL))
			irq_set_affinity_notअगरier(irq_num, शून्य);
		irq_set_affinity_hपूर्णांक(irq_num, शून्य);
		devm_मुक्त_irq(dev, irq_num, &vsi->q_vectors[vector]);
	पूर्ण
	वापस err;
पूर्ण

/**
 * ice_xdp_alloc_setup_rings - Allocate and setup Tx rings क्रम XDP
 * @vsi: VSI to setup Tx rings used by XDP
 *
 * Return 0 on success and negative value on error
 */
अटल पूर्णांक ice_xdp_alloc_setup_rings(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vsi->back);
	पूर्णांक i;

	क्रम (i = 0; i < vsi->num_xdp_txq; i++) अणु
		u16 xdp_q_idx = vsi->alloc_txq + i;
		काष्ठा ice_ring *xdp_ring;

		xdp_ring = kzalloc(माप(*xdp_ring), GFP_KERNEL);

		अगर (!xdp_ring)
			जाओ मुक्त_xdp_rings;

		xdp_ring->q_index = xdp_q_idx;
		xdp_ring->reg_idx = vsi->txq_map[xdp_q_idx];
		xdp_ring->ring_active = false;
		xdp_ring->vsi = vsi;
		xdp_ring->netdev = शून्य;
		xdp_ring->dev = dev;
		xdp_ring->count = vsi->num_tx_desc;
		WRITE_ONCE(vsi->xdp_rings[i], xdp_ring);
		अगर (ice_setup_tx_ring(xdp_ring))
			जाओ मुक्त_xdp_rings;
		ice_set_ring_xdp(xdp_ring);
		xdp_ring->xsk_pool = ice_xsk_pool(xdp_ring);
	पूर्ण

	वापस 0;

मुक्त_xdp_rings:
	क्रम (; i >= 0; i--)
		अगर (vsi->xdp_rings[i] && vsi->xdp_rings[i]->desc)
			ice_मुक्त_tx_ring(vsi->xdp_rings[i]);
	वापस -ENOMEM;
पूर्ण

/**
 * ice_vsi_assign_bpf_prog - set or clear bpf prog poपूर्णांकer on VSI
 * @vsi: VSI to set the bpf prog on
 * @prog: the bpf prog poपूर्णांकer
 */
अटल व्योम ice_vsi_assign_bpf_prog(काष्ठा ice_vsi *vsi, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *old_prog;
	पूर्णांक i;

	old_prog = xchg(&vsi->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	ice_क्रम_each_rxq(vsi, i)
		WRITE_ONCE(vsi->rx_rings[i]->xdp_prog, vsi->xdp_prog);
पूर्ण

/**
 * ice_prepare_xdp_rings - Allocate, configure and setup Tx rings क्रम XDP
 * @vsi: VSI to bring up Tx rings used by XDP
 * @prog: bpf program that will be asचिन्हित to VSI
 *
 * Return 0 on success and negative value on error
 */
पूर्णांक ice_prepare_xdp_rings(काष्ठा ice_vsi *vsi, काष्ठा bpf_prog *prog)
अणु
	u16 max_txqs[ICE_MAX_TRAFFIC_CLASS] = अणु 0 पूर्ण;
	पूर्णांक xdp_rings_rem = vsi->num_xdp_txq;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_qs_cfg xdp_qs_cfg = अणु
		.qs_mutex = &pf->avail_q_mutex,
		.pf_map = pf->avail_txqs,
		.pf_map_size = pf->max_pf_txqs,
		.q_count = vsi->num_xdp_txq,
		.scatter_count = ICE_MAX_SCATTER_TXQS,
		.vsi_map = vsi->txq_map,
		.vsi_map_offset = vsi->alloc_txq,
		.mapping_mode = ICE_VSI_MAP_CONTIG
	पूर्ण;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	पूर्णांक i, v_idx;

	dev = ice_pf_to_dev(pf);
	vsi->xdp_rings = devm_kसुस्मृति(dev, vsi->num_xdp_txq,
				      माप(*vsi->xdp_rings), GFP_KERNEL);
	अगर (!vsi->xdp_rings)
		वापस -ENOMEM;

	vsi->xdp_mapping_mode = xdp_qs_cfg.mapping_mode;
	अगर (__ice_vsi_get_qs(&xdp_qs_cfg))
		जाओ err_map_xdp;

	अगर (ice_xdp_alloc_setup_rings(vsi))
		जाओ clear_xdp_rings;

	/* follow the logic from ice_vsi_map_rings_to_vectors */
	ice_क्रम_each_q_vector(vsi, v_idx) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[v_idx];
		पूर्णांक xdp_rings_per_v, q_id, q_base;

		xdp_rings_per_v = DIV_ROUND_UP(xdp_rings_rem,
					       vsi->num_q_vectors - v_idx);
		q_base = vsi->num_xdp_txq - xdp_rings_rem;

		क्रम (q_id = q_base; q_id < (q_base + xdp_rings_per_v); q_id++) अणु
			काष्ठा ice_ring *xdp_ring = vsi->xdp_rings[q_id];

			xdp_ring->q_vector = q_vector;
			xdp_ring->next = q_vector->tx.ring;
			q_vector->tx.ring = xdp_ring;
		पूर्ण
		xdp_rings_rem -= xdp_rings_per_v;
	पूर्ण

	/* omit the scheduler update अगर in reset path; XDP queues will be
	 * taken पूर्णांकo account at the end of ice_vsi_rebuild, where
	 * ice_cfg_vsi_lan is being called
	 */
	अगर (ice_is_reset_in_progress(pf->state))
		वापस 0;

	/* tell the Tx scheduler that right now we have
	 * additional queues
	 */
	क्रम (i = 0; i < vsi->tc_cfg.numtc; i++)
		max_txqs[i] = vsi->num_txq + vsi->num_xdp_txq;

	status = ice_cfg_vsi_lan(vsi->port_info, vsi->idx, vsi->tc_cfg.ena_tc,
				 max_txqs);
	अगर (status) अणु
		dev_err(dev, "Failed VSI LAN queue config for XDP, error: %s\n",
			ice_stat_str(status));
		जाओ clear_xdp_rings;
	पूर्ण
	ice_vsi_assign_bpf_prog(vsi, prog);

	वापस 0;
clear_xdp_rings:
	क्रम (i = 0; i < vsi->num_xdp_txq; i++)
		अगर (vsi->xdp_rings[i]) अणु
			kमुक्त_rcu(vsi->xdp_rings[i], rcu);
			vsi->xdp_rings[i] = शून्य;
		पूर्ण

err_map_xdp:
	mutex_lock(&pf->avail_q_mutex);
	क्रम (i = 0; i < vsi->num_xdp_txq; i++) अणु
		clear_bit(vsi->txq_map[i + vsi->alloc_txq], pf->avail_txqs);
		vsi->txq_map[i + vsi->alloc_txq] = ICE_INVAL_Q_INDEX;
	पूर्ण
	mutex_unlock(&pf->avail_q_mutex);

	devm_kमुक्त(dev, vsi->xdp_rings);
	वापस -ENOMEM;
पूर्ण

/**
 * ice_destroy_xdp_rings - unकरो the configuration made by ice_prepare_xdp_rings
 * @vsi: VSI to हटाओ XDP rings
 *
 * Detach XDP rings from irq vectors, clean up the PF biपंचांगap and मुक्त
 * resources
 */
पूर्णांक ice_destroy_xdp_rings(काष्ठा ice_vsi *vsi)
अणु
	u16 max_txqs[ICE_MAX_TRAFFIC_CLASS] = अणु 0 पूर्ण;
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक i, v_idx;

	/* q_vectors are मुक्तd in reset path so there's no poपूर्णांक in detaching
	 * rings; in हाल of rebuild being triggered not from reset bits
	 * in pf->state won't be set, so additionally check first q_vector
	 * against शून्य
	 */
	अगर (ice_is_reset_in_progress(pf->state) || !vsi->q_vectors[0])
		जाओ मुक्त_qmap;

	ice_क्रम_each_q_vector(vsi, v_idx) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[v_idx];
		काष्ठा ice_ring *ring;

		ice_क्रम_each_ring(ring, q_vector->tx)
			अगर (!ring->tx_buf || !ice_ring_is_xdp(ring))
				अवरोध;

		/* restore the value of last node prior to XDP setup */
		q_vector->tx.ring = ring;
	पूर्ण

मुक्त_qmap:
	mutex_lock(&pf->avail_q_mutex);
	क्रम (i = 0; i < vsi->num_xdp_txq; i++) अणु
		clear_bit(vsi->txq_map[i + vsi->alloc_txq], pf->avail_txqs);
		vsi->txq_map[i + vsi->alloc_txq] = ICE_INVAL_Q_INDEX;
	पूर्ण
	mutex_unlock(&pf->avail_q_mutex);

	क्रम (i = 0; i < vsi->num_xdp_txq; i++)
		अगर (vsi->xdp_rings[i]) अणु
			अगर (vsi->xdp_rings[i]->desc)
				ice_मुक्त_tx_ring(vsi->xdp_rings[i]);
			kमुक्त_rcu(vsi->xdp_rings[i], rcu);
			vsi->xdp_rings[i] = शून्य;
		पूर्ण

	devm_kमुक्त(ice_pf_to_dev(pf), vsi->xdp_rings);
	vsi->xdp_rings = शून्य;

	अगर (ice_is_reset_in_progress(pf->state) || !vsi->q_vectors[0])
		वापस 0;

	ice_vsi_assign_bpf_prog(vsi, शून्य);

	/* notअगरy Tx scheduler that we destroyed XDP queues and bring
	 * back the old number of child nodes
	 */
	क्रम (i = 0; i < vsi->tc_cfg.numtc; i++)
		max_txqs[i] = vsi->num_txq;

	/* change number of XDP Tx queues to 0 */
	vsi->num_xdp_txq = 0;

	वापस ice_cfg_vsi_lan(vsi->port_info, vsi->idx, vsi->tc_cfg.ena_tc,
			       max_txqs);
पूर्ण

/**
 * ice_vsi_rx_napi_schedule - Schedule napi on RX queues from VSI
 * @vsi: VSI to schedule napi on
 */
अटल व्योम ice_vsi_rx_napi_schedule(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i;

	ice_क्रम_each_rxq(vsi, i) अणु
		काष्ठा ice_ring *rx_ring = vsi->rx_rings[i];

		अगर (rx_ring->xsk_pool)
			napi_schedule(&rx_ring->q_vector->napi);
	पूर्ण
पूर्ण

/**
 * ice_xdp_setup_prog - Add or हटाओ XDP eBPF program
 * @vsi: VSI to setup XDP क्रम
 * @prog: XDP program
 * @extack: netlink extended ack
 */
अटल पूर्णांक
ice_xdp_setup_prog(काष्ठा ice_vsi *vsi, काष्ठा bpf_prog *prog,
		   काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक frame_size = vsi->netdev->mtu + ICE_ETH_PKT_HDR_PAD;
	bool अगर_running = netअगर_running(vsi->netdev);
	पूर्णांक ret = 0, xdp_ring_err = 0;

	अगर (frame_size > vsi->rx_buf_len) अणु
		NL_SET_ERR_MSG_MOD(extack, "MTU too large for loading XDP");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* need to stop netdev जबतक setting up the program क्रम Rx rings */
	अगर (अगर_running && !test_and_set_bit(ICE_VSI_DOWN, vsi->state)) अणु
		ret = ice_करोwn(vsi);
		अगर (ret) अणु
			NL_SET_ERR_MSG_MOD(extack, "Preparing device for XDP attach failed");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!ice_is_xdp_ena_vsi(vsi) && prog) अणु
		vsi->num_xdp_txq = vsi->alloc_rxq;
		xdp_ring_err = ice_prepare_xdp_rings(vsi, prog);
		अगर (xdp_ring_err)
			NL_SET_ERR_MSG_MOD(extack, "Setting up XDP Tx resources failed");
	पूर्ण अन्यथा अगर (ice_is_xdp_ena_vsi(vsi) && !prog) अणु
		xdp_ring_err = ice_destroy_xdp_rings(vsi);
		अगर (xdp_ring_err)
			NL_SET_ERR_MSG_MOD(extack, "Freeing XDP Tx resources failed");
	पूर्ण अन्यथा अणु
		ice_vsi_assign_bpf_prog(vsi, prog);
	पूर्ण

	अगर (अगर_running)
		ret = ice_up(vsi);

	अगर (!ret && prog)
		ice_vsi_rx_napi_schedule(vsi);

	वापस (ret || xdp_ring_err) ? -ENOMEM : 0;
पूर्ण

/**
 * ice_xdp_safe_mode - XDP handler क्रम safe mode
 * @dev: netdevice
 * @xdp: XDP command
 */
अटल पूर्णांक ice_xdp_safe_mode(काष्ठा net_device __always_unused *dev,
			     काष्ठा netdev_bpf *xdp)
अणु
	NL_SET_ERR_MSG_MOD(xdp->extack,
			   "Please provide working DDP firmware package in order to use XDP\n"
			   "Refer to Documentation/networking/device_drivers/ethernet/intel/ice.rst");
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * ice_xdp - implements XDP handler
 * @dev: netdevice
 * @xdp: XDP command
 */
अटल पूर्णांक ice_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(dev);
	काष्ठा ice_vsi *vsi = np->vsi;

	अगर (vsi->type != ICE_VSI_PF) अणु
		NL_SET_ERR_MSG_MOD(xdp->extack, "XDP can be loaded only on PF VSI");
		वापस -EINVAL;
	पूर्ण

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस ice_xdp_setup_prog(vsi, xdp->prog, xdp->extack);
	हाल XDP_SETUP_XSK_POOL:
		वापस ice_xsk_pool_setup(vsi, xdp->xsk.pool,
					  xdp->xsk.queue_id);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * ice_ena_misc_vector - enable the non-queue पूर्णांकerrupts
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_ena_misc_vector(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	u32 val;

	/* Disable anti-spoof detection पूर्णांकerrupt to prevent spurious event
	 * पूर्णांकerrupts during a function reset. Anti-spoof functionally is
	 * still supported.
	 */
	val = rd32(hw, GL_MDCK_TX_TDPU);
	val |= GL_MDCK_TX_TDPU_RCU_ANTISPOOF_ITR_DIS_M;
	wr32(hw, GL_MDCK_TX_TDPU, val);

	/* clear things first */
	wr32(hw, PFINT_OICR_ENA, 0);	/* disable all */
	rd32(hw, PFINT_OICR);		/* पढ़ो to clear */

	val = (PFINT_OICR_ECC_ERR_M |
	       PFINT_OICR_MAL_DETECT_M |
	       PFINT_OICR_GRST_M |
	       PFINT_OICR_PCI_EXCEPTION_M |
	       PFINT_OICR_VFLR_M |
	       PFINT_OICR_HMC_ERR_M |
	       PFINT_OICR_PE_CRITERR_M);

	wr32(hw, PFINT_OICR_ENA, val);

	/* SW_ITR_IDX = 0, but करोn't change INTENA */
	wr32(hw, GLINT_DYN_CTL(pf->oicr_idx),
	     GLINT_DYN_CTL_SW_ITR_INDX_M | GLINT_DYN_CTL_INTENA_MSK_M);
पूर्ण

/**
 * ice_misc_पूर्णांकr - misc पूर्णांकerrupt handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 */
अटल irqवापस_t ice_misc_पूर्णांकr(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा ice_pf *pf = (काष्ठा ice_pf *)data;
	काष्ठा ice_hw *hw = &pf->hw;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा device *dev;
	u32 oicr, ena_mask;

	dev = ice_pf_to_dev(pf);
	set_bit(ICE_ADMINQ_EVENT_PENDING, pf->state);
	set_bit(ICE_MAILBOXQ_EVENT_PENDING, pf->state);

	oicr = rd32(hw, PFINT_OICR);
	ena_mask = rd32(hw, PFINT_OICR_ENA);

	अगर (oicr & PFINT_OICR_SWINT_M) अणु
		ena_mask &= ~PFINT_OICR_SWINT_M;
		pf->sw_पूर्णांक_count++;
	पूर्ण

	अगर (oicr & PFINT_OICR_MAL_DETECT_M) अणु
		ena_mask &= ~PFINT_OICR_MAL_DETECT_M;
		set_bit(ICE_MDD_EVENT_PENDING, pf->state);
	पूर्ण
	अगर (oicr & PFINT_OICR_VFLR_M) अणु
		/* disable any further VFLR event notअगरications */
		अगर (test_bit(ICE_VF_RESETS_DISABLED, pf->state)) अणु
			u32 reg = rd32(hw, PFINT_OICR_ENA);

			reg &= ~PFINT_OICR_VFLR_M;
			wr32(hw, PFINT_OICR_ENA, reg);
		पूर्ण अन्यथा अणु
			ena_mask &= ~PFINT_OICR_VFLR_M;
			set_bit(ICE_VFLR_EVENT_PENDING, pf->state);
		पूर्ण
	पूर्ण

	अगर (oicr & PFINT_OICR_GRST_M) अणु
		u32 reset;

		/* we have a reset warning */
		ena_mask &= ~PFINT_OICR_GRST_M;
		reset = (rd32(hw, GLGEN_RSTAT) & GLGEN_RSTAT_RESET_TYPE_M) >>
			GLGEN_RSTAT_RESET_TYPE_S;

		अगर (reset == ICE_RESET_CORER)
			pf->corer_count++;
		अन्यथा अगर (reset == ICE_RESET_GLOBR)
			pf->globr_count++;
		अन्यथा अगर (reset == ICE_RESET_EMPR)
			pf->empr_count++;
		अन्यथा
			dev_dbg(dev, "Invalid reset type %d\n", reset);

		/* If a reset cycle isn't alपढ़ोy in progress, we set a bit in
		 * pf->state so that the service task can start a reset/rebuild.
		 * We also make note of which reset happened so that peer
		 * devices/drivers can be inक्रमmed.
		 */
		अगर (!test_and_set_bit(ICE_RESET_OICR_RECV, pf->state)) अणु
			अगर (reset == ICE_RESET_CORER)
				set_bit(ICE_CORER_RECV, pf->state);
			अन्यथा अगर (reset == ICE_RESET_GLOBR)
				set_bit(ICE_GLOBR_RECV, pf->state);
			अन्यथा
				set_bit(ICE_EMPR_RECV, pf->state);

			/* There are couple of dअगरferent bits at play here.
			 * hw->reset_ongoing indicates whether the hardware is
			 * in reset. This is set to true when a reset पूर्णांकerrupt
			 * is received and set back to false after the driver
			 * has determined that the hardware is out of reset.
			 *
			 * ICE_RESET_OICR_RECV in pf->state indicates
			 * that a post reset rebuild is required beक्रमe the
			 * driver is operational again. This is set above.
			 *
			 * As this is the start of the reset/rebuild cycle, set
			 * both to indicate that.
			 */
			hw->reset_ongoing = true;
		पूर्ण
	पूर्ण

	अगर (oicr & PFINT_OICR_HMC_ERR_M) अणु
		ena_mask &= ~PFINT_OICR_HMC_ERR_M;
		dev_dbg(dev, "HMC Error interrupt - info 0x%x, data 0x%x\n",
			rd32(hw, PFHMC_ERRORINFO),
			rd32(hw, PFHMC_ERRORDATA));
	पूर्ण

	/* Report any reमुख्यing unexpected पूर्णांकerrupts */
	oicr &= ena_mask;
	अगर (oicr) अणु
		dev_dbg(dev, "unhandled interrupt oicr=0x%08x\n", oicr);
		/* If a critical error is pending there is no choice but to
		 * reset the device.
		 */
		अगर (oicr & (PFINT_OICR_PE_CRITERR_M |
			    PFINT_OICR_PCI_EXCEPTION_M |
			    PFINT_OICR_ECC_ERR_M)) अणु
			set_bit(ICE_PFR_REQ, pf->state);
			ice_service_task_schedule(pf);
		पूर्ण
	पूर्ण
	ret = IRQ_HANDLED;

	ice_service_task_schedule(pf);
	ice_irq_dynamic_ena(hw, शून्य, शून्य);

	वापस ret;
पूर्ण

/**
 * ice_dis_ctrlq_पूर्णांकerrupts - disable control queue पूर्णांकerrupts
 * @hw: poपूर्णांकer to HW काष्ठाure
 */
अटल व्योम ice_dis_ctrlq_पूर्णांकerrupts(काष्ठा ice_hw *hw)
अणु
	/* disable Admin queue Interrupt causes */
	wr32(hw, PFINT_FW_CTL,
	     rd32(hw, PFINT_FW_CTL) & ~PFINT_FW_CTL_CAUSE_ENA_M);

	/* disable Mailbox queue Interrupt causes */
	wr32(hw, PFINT_MBX_CTL,
	     rd32(hw, PFINT_MBX_CTL) & ~PFINT_MBX_CTL_CAUSE_ENA_M);

	/* disable Control queue Interrupt causes */
	wr32(hw, PFINT_OICR_CTL,
	     rd32(hw, PFINT_OICR_CTL) & ~PFINT_OICR_CTL_CAUSE_ENA_M);

	ice_flush(hw);
पूर्ण

/**
 * ice_मुक्त_irq_msix_misc - Unroll misc vector setup
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_मुक्त_irq_msix_misc(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;

	ice_dis_ctrlq_पूर्णांकerrupts(hw);

	/* disable OICR पूर्णांकerrupt */
	wr32(hw, PFINT_OICR_ENA, 0);
	ice_flush(hw);

	अगर (pf->msix_entries) अणु
		synchronize_irq(pf->msix_entries[pf->oicr_idx].vector);
		devm_मुक्त_irq(ice_pf_to_dev(pf),
			      pf->msix_entries[pf->oicr_idx].vector, pf);
	पूर्ण

	pf->num_avail_sw_msix += 1;
	ice_मुक्त_res(pf->irq_tracker, pf->oicr_idx, ICE_RES_MISC_VEC_ID);
पूर्ण

/**
 * ice_ena_ctrlq_पूर्णांकerrupts - enable control queue पूर्णांकerrupts
 * @hw: poपूर्णांकer to HW काष्ठाure
 * @reg_idx: HW vector index to associate the control queue पूर्णांकerrupts with
 */
अटल व्योम ice_ena_ctrlq_पूर्णांकerrupts(काष्ठा ice_hw *hw, u16 reg_idx)
अणु
	u32 val;

	val = ((reg_idx & PFINT_OICR_CTL_MSIX_INDX_M) |
	       PFINT_OICR_CTL_CAUSE_ENA_M);
	wr32(hw, PFINT_OICR_CTL, val);

	/* enable Admin queue Interrupt causes */
	val = ((reg_idx & PFINT_FW_CTL_MSIX_INDX_M) |
	       PFINT_FW_CTL_CAUSE_ENA_M);
	wr32(hw, PFINT_FW_CTL, val);

	/* enable Mailbox queue Interrupt causes */
	val = ((reg_idx & PFINT_MBX_CTL_MSIX_INDX_M) |
	       PFINT_MBX_CTL_CAUSE_ENA_M);
	wr32(hw, PFINT_MBX_CTL, val);

	ice_flush(hw);
पूर्ण

/**
 * ice_req_irq_msix_misc - Setup the misc vector to handle non queue events
 * @pf: board निजी काष्ठाure
 *
 * This sets up the handler क्रम MSIX 0, which is used to manage the
 * non-queue पूर्णांकerrupts, e.g. AdminQ and errors. This is not used
 * when in MSI or Legacy पूर्णांकerrupt mode.
 */
अटल पूर्णांक ice_req_irq_msix_misc(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक oicr_idx, err = 0;

	अगर (!pf->पूर्णांक_name[0])
		snम_लिखो(pf->पूर्णांक_name, माप(pf->पूर्णांक_name) - 1, "%s-%s:misc",
			 dev_driver_string(dev), dev_name(dev));

	/* Do not request IRQ but करो enable OICR पूर्णांकerrupt since settings are
	 * lost during reset. Note that this function is called only during
	 * rebuild path and not जबतक reset is in progress.
	 */
	अगर (ice_is_reset_in_progress(pf->state))
		जाओ skip_req_irq;

	/* reserve one vector in irq_tracker क्रम misc पूर्णांकerrupts */
	oicr_idx = ice_get_res(pf, pf->irq_tracker, 1, ICE_RES_MISC_VEC_ID);
	अगर (oicr_idx < 0)
		वापस oicr_idx;

	pf->num_avail_sw_msix -= 1;
	pf->oicr_idx = (u16)oicr_idx;

	err = devm_request_irq(dev, pf->msix_entries[pf->oicr_idx].vector,
			       ice_misc_पूर्णांकr, 0, pf->पूर्णांक_name, pf);
	अगर (err) अणु
		dev_err(dev, "devm_request_irq for %s failed: %d\n",
			pf->पूर्णांक_name, err);
		ice_मुक्त_res(pf->irq_tracker, 1, ICE_RES_MISC_VEC_ID);
		pf->num_avail_sw_msix += 1;
		वापस err;
	पूर्ण

skip_req_irq:
	ice_ena_misc_vector(pf);

	ice_ena_ctrlq_पूर्णांकerrupts(hw, pf->oicr_idx);
	wr32(hw, GLINT_ITR(ICE_RX_ITR, pf->oicr_idx),
	     ITR_REG_ALIGN(ICE_ITR_8K) >> ICE_ITR_GRAN_S);

	ice_flush(hw);
	ice_irq_dynamic_ena(hw, शून्य, शून्य);

	वापस 0;
पूर्ण

/**
 * ice_napi_add - रेजिस्टर NAPI handler क्रम the VSI
 * @vsi: VSI क्रम which NAPI handler is to be रेजिस्टरed
 *
 * This function is only called in the driver's load path. Registering the NAPI
 * handler is करोne in ice_vsi_alloc_q_vector() क्रम all other हालs (i.e. resume,
 * reset/rebuild, etc.)
 */
अटल व्योम ice_napi_add(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक v_idx;

	अगर (!vsi->netdev)
		वापस;

	ice_क्रम_each_q_vector(vsi, v_idx)
		netअगर_napi_add(vsi->netdev, &vsi->q_vectors[v_idx]->napi,
			       ice_napi_poll, NAPI_POLL_WEIGHT);
पूर्ण

/**
 * ice_set_ops - set netdev and ethtools ops क्रम the given netdev
 * @netdev: netdev instance
 */
अटल व्योम ice_set_ops(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	अगर (ice_is_safe_mode(pf)) अणु
		netdev->netdev_ops = &ice_netdev_safe_mode_ops;
		ice_set_ethtool_safe_mode_ops(netdev);
		वापस;
	पूर्ण

	netdev->netdev_ops = &ice_netdev_ops;
	netdev->udp_tunnel_nic_info = &pf->hw.udp_tunnel_nic;
	ice_set_ethtool_ops(netdev);
पूर्ण

/**
 * ice_set_netdev_features - set features क्रम the given netdev
 * @netdev: netdev instance
 */
अटल व्योम ice_set_netdev_features(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	netdev_features_t csumo_features;
	netdev_features_t vlano_features;
	netdev_features_t dflt_features;
	netdev_features_t tso_features;

	अगर (ice_is_safe_mode(pf)) अणु
		/* safe mode */
		netdev->features = NETIF_F_SG | NETIF_F_HIGHDMA;
		netdev->hw_features = netdev->features;
		वापस;
	पूर्ण

	dflt_features = NETIF_F_SG	|
			NETIF_F_HIGHDMA	|
			NETIF_F_NTUPLE	|
			NETIF_F_RXHASH;

	csumo_features = NETIF_F_RXCSUM	  |
			 NETIF_F_IP_CSUM  |
			 NETIF_F_SCTP_CRC |
			 NETIF_F_IPV6_CSUM;

	vlano_features = NETIF_F_HW_VLAN_CTAG_FILTER |
			 NETIF_F_HW_VLAN_CTAG_TX     |
			 NETIF_F_HW_VLAN_CTAG_RX;

	tso_features = NETIF_F_TSO			|
		       NETIF_F_TSO_ECN			|
		       NETIF_F_TSO6			|
		       NETIF_F_GSO_GRE			|
		       NETIF_F_GSO_UDP_TUNNEL		|
		       NETIF_F_GSO_GRE_CSUM		|
		       NETIF_F_GSO_UDP_TUNNEL_CSUM	|
		       NETIF_F_GSO_PARTIAL		|
		       NETIF_F_GSO_IPXIP4		|
		       NETIF_F_GSO_IPXIP6		|
		       NETIF_F_GSO_UDP_L4;

	netdev->gso_partial_features |= NETIF_F_GSO_UDP_TUNNEL_CSUM |
					NETIF_F_GSO_GRE_CSUM;
	/* set features that user can change */
	netdev->hw_features = dflt_features | csumo_features |
			      vlano_features | tso_features;

	/* add support क्रम HW_CSUM on packets with MPLS header */
	netdev->mpls_features =  NETIF_F_HW_CSUM;

	/* enable features */
	netdev->features |= netdev->hw_features;
	/* encap and VLAN devices inherit शेष, csumo and tso features */
	netdev->hw_enc_features |= dflt_features | csumo_features |
				   tso_features;
	netdev->vlan_features |= dflt_features | csumo_features |
				 tso_features;
पूर्ण

/**
 * ice_cfg_netdev - Allocate, configure and रेजिस्टर a netdev
 * @vsi: the VSI associated with the new netdev
 *
 * Returns 0 on success, negative value on failure
 */
अटल पूर्णांक ice_cfg_netdev(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_netdev_priv *np;
	काष्ठा net_device *netdev;
	u8 mac_addr[ETH_ALEN];

	netdev = alloc_etherdev_mqs(माप(*np), vsi->alloc_txq,
				    vsi->alloc_rxq);
	अगर (!netdev)
		वापस -ENOMEM;

	set_bit(ICE_VSI_NETDEV_ALLOCD, vsi->state);
	vsi->netdev = netdev;
	np = netdev_priv(netdev);
	np->vsi = vsi;

	ice_set_netdev_features(netdev);

	ice_set_ops(netdev);

	अगर (vsi->type == ICE_VSI_PF) अणु
		SET_NETDEV_DEV(netdev, ice_pf_to_dev(pf));
		ether_addr_copy(mac_addr, vsi->port_info->mac.perm_addr);
		ether_addr_copy(netdev->dev_addr, mac_addr);
		ether_addr_copy(netdev->perm_addr, mac_addr);
	पूर्ण

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* Setup netdev TC inक्रमmation */
	ice_vsi_cfg_netdev_tc(vsi, vsi->tc_cfg.ena_tc);

	/* setup watchकरोg समयout value to be 5 second */
	netdev->watchकरोg_समयo = 5 * HZ;

	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = ICE_MAX_MTU;

	वापस 0;
पूर्ण

/**
 * ice_fill_rss_lut - Fill the RSS lookup table with शेष values
 * @lut: Lookup table
 * @rss_table_size: Lookup table size
 * @rss_size: Range of queue number क्रम hashing
 */
व्योम ice_fill_rss_lut(u8 *lut, u16 rss_table_size, u16 rss_size)
अणु
	u16 i;

	क्रम (i = 0; i < rss_table_size; i++)
		lut[i] = i % rss_size;
पूर्ण

/**
 * ice_pf_vsi_setup - Set up a PF VSI
 * @pf: board निजी काष्ठाure
 * @pi: poपूर्णांकer to the port_info instance
 *
 * Returns poपूर्णांकer to the successfully allocated VSI software काष्ठा
 * on success, otherwise वापसs शून्य on failure.
 */
अटल काष्ठा ice_vsi *
ice_pf_vsi_setup(काष्ठा ice_pf *pf, काष्ठा ice_port_info *pi)
अणु
	वापस ice_vsi_setup(pf, pi, ICE_VSI_PF, ICE_INVAL_VFID);
पूर्ण

/**
 * ice_ctrl_vsi_setup - Set up a control VSI
 * @pf: board निजी काष्ठाure
 * @pi: poपूर्णांकer to the port_info instance
 *
 * Returns poपूर्णांकer to the successfully allocated VSI software काष्ठा
 * on success, otherwise वापसs शून्य on failure.
 */
अटल काष्ठा ice_vsi *
ice_ctrl_vsi_setup(काष्ठा ice_pf *pf, काष्ठा ice_port_info *pi)
अणु
	वापस ice_vsi_setup(pf, pi, ICE_VSI_CTRL, ICE_INVAL_VFID);
पूर्ण

/**
 * ice_lb_vsi_setup - Set up a loopback VSI
 * @pf: board निजी काष्ठाure
 * @pi: poपूर्णांकer to the port_info instance
 *
 * Returns poपूर्णांकer to the successfully allocated VSI software काष्ठा
 * on success, otherwise वापसs शून्य on failure.
 */
काष्ठा ice_vsi *
ice_lb_vsi_setup(काष्ठा ice_pf *pf, काष्ठा ice_port_info *pi)
अणु
	वापस ice_vsi_setup(pf, pi, ICE_VSI_LB, ICE_INVAL_VFID);
पूर्ण

/**
 * ice_vlan_rx_add_vid - Add a VLAN ID filter to HW offload
 * @netdev: network पूर्णांकerface to be adjusted
 * @proto: unused protocol
 * @vid: VLAN ID to be added
 *
 * net_device_ops implementation क्रम adding VLAN IDs
 */
अटल पूर्णांक
ice_vlan_rx_add_vid(काष्ठा net_device *netdev, __always_unused __be16 proto,
		    u16 vid)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	पूर्णांक ret;

	/* VLAN 0 is added by शेष during load/reset */
	अगर (!vid)
		वापस 0;

	/* Enable VLAN pruning when a VLAN other than 0 is added */
	अगर (!ice_vsi_is_vlan_pruning_ena(vsi)) अणु
		ret = ice_cfg_vlan_pruning(vsi, true, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Add a चयन rule क्रम this VLAN ID so its corresponding VLAN tagged
	 * packets aren't pruned by the device's पूर्णांकernal चयन on Rx
	 */
	ret = ice_vsi_add_vlan(vsi, vid, ICE_FWD_TO_VSI);
	अगर (!ret)
		set_bit(ICE_VSI_VLAN_FLTR_CHANGED, vsi->state);

	वापस ret;
पूर्ण

/**
 * ice_vlan_rx_समाप्त_vid - Remove a VLAN ID filter from HW offload
 * @netdev: network पूर्णांकerface to be adjusted
 * @proto: unused protocol
 * @vid: VLAN ID to be हटाओd
 *
 * net_device_ops implementation क्रम removing VLAN IDs
 */
अटल पूर्णांक
ice_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __always_unused __be16 proto,
		     u16 vid)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	पूर्णांक ret;

	/* करोn't allow removal of VLAN 0 */
	अगर (!vid)
		वापस 0;

	/* Make sure ice_vsi_समाप्त_vlan is successful beक्रमe updating VLAN
	 * inक्रमmation
	 */
	ret = ice_vsi_समाप्त_vlan(vsi, vid);
	अगर (ret)
		वापस ret;

	/* Disable pruning when VLAN 0 is the only VLAN rule */
	अगर (vsi->num_vlan == 1 && ice_vsi_is_vlan_pruning_ena(vsi))
		ret = ice_cfg_vlan_pruning(vsi, false, false);

	set_bit(ICE_VSI_VLAN_FLTR_CHANGED, vsi->state);
	वापस ret;
पूर्ण

/**
 * ice_setup_pf_sw - Setup the HW चयन on startup or after reset
 * @pf: board निजी काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 */
अटल पूर्णांक ice_setup_pf_sw(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_vsi *vsi;
	पूर्णांक status = 0;

	अगर (ice_is_reset_in_progress(pf->state))
		वापस -EBUSY;

	vsi = ice_pf_vsi_setup(pf, pf->hw.port_info);
	अगर (!vsi)
		वापस -ENOMEM;

	status = ice_cfg_netdev(vsi);
	अगर (status) अणु
		status = -ENODEV;
		जाओ unroll_vsi_setup;
	पूर्ण
	/* netdev has to be configured beक्रमe setting frame size */
	ice_vsi_cfg_frame_size(vsi);

	/* Setup DCB netlink पूर्णांकerface */
	ice_dcbnl_setup(vsi);

	/* रेजिस्टरing the NAPI handler requires both the queues and
	 * netdev to be created, which are करोne in ice_pf_vsi_setup()
	 * and ice_cfg_netdev() respectively
	 */
	ice_napi_add(vsi);

	status = ice_set_cpu_rx_rmap(vsi);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(pf), "Failed to set CPU Rx map VSI %d error %d\n",
			vsi->vsi_num, status);
		status = -EINVAL;
		जाओ unroll_napi_add;
	पूर्ण
	status = ice_init_mac_fltr(pf);
	अगर (status)
		जाओ मुक्त_cpu_rx_map;

	वापस status;

मुक्त_cpu_rx_map:
	ice_मुक्त_cpu_rx_rmap(vsi);

unroll_napi_add:
	अगर (vsi) अणु
		ice_napi_del(vsi);
		अगर (vsi->netdev) अणु
			clear_bit(ICE_VSI_NETDEV_ALLOCD, vsi->state);
			मुक्त_netdev(vsi->netdev);
			vsi->netdev = शून्य;
		पूर्ण
	पूर्ण

unroll_vsi_setup:
	ice_vsi_release(vsi);
	वापस status;
पूर्ण

/**
 * ice_get_avail_q_count - Get count of queues in use
 * @pf_qmap: biपंचांगap to get queue use count from
 * @lock: poपूर्णांकer to a mutex that protects access to pf_qmap
 * @size: size of the biपंचांगap
 */
अटल u16
ice_get_avail_q_count(अचिन्हित दीर्घ *pf_qmap, काष्ठा mutex *lock, u16 size)
अणु
	अचिन्हित दीर्घ bit;
	u16 count = 0;

	mutex_lock(lock);
	क्रम_each_clear_bit(bit, pf_qmap, size)
		count++;
	mutex_unlock(lock);

	वापस count;
पूर्ण

/**
 * ice_get_avail_txq_count - Get count of Tx queues in use
 * @pf: poपूर्णांकer to an ice_pf instance
 */
u16 ice_get_avail_txq_count(काष्ठा ice_pf *pf)
अणु
	वापस ice_get_avail_q_count(pf->avail_txqs, &pf->avail_q_mutex,
				     pf->max_pf_txqs);
पूर्ण

/**
 * ice_get_avail_rxq_count - Get count of Rx queues in use
 * @pf: poपूर्णांकer to an ice_pf instance
 */
u16 ice_get_avail_rxq_count(काष्ठा ice_pf *pf)
अणु
	वापस ice_get_avail_q_count(pf->avail_rxqs, &pf->avail_q_mutex,
				     pf->max_pf_rxqs);
पूर्ण

/**
 * ice_deinit_pf - Unrolls initialziations करोne by ice_init_pf
 * @pf: board निजी काष्ठाure to initialize
 */
अटल व्योम ice_deinit_pf(काष्ठा ice_pf *pf)
अणु
	ice_service_task_stop(pf);
	mutex_destroy(&pf->sw_mutex);
	mutex_destroy(&pf->tc_mutex);
	mutex_destroy(&pf->avail_q_mutex);

	अगर (pf->avail_txqs) अणु
		biपंचांगap_मुक्त(pf->avail_txqs);
		pf->avail_txqs = शून्य;
	पूर्ण

	अगर (pf->avail_rxqs) अणु
		biपंचांगap_मुक्त(pf->avail_rxqs);
		pf->avail_rxqs = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_set_pf_caps - set PFs capability flags
 * @pf: poपूर्णांकer to the PF instance
 */
अटल व्योम ice_set_pf_caps(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw_func_caps *func_caps = &pf->hw.func_caps;

	clear_bit(ICE_FLAG_DCB_CAPABLE, pf->flags);
	अगर (func_caps->common_cap.dcb)
		set_bit(ICE_FLAG_DCB_CAPABLE, pf->flags);
	clear_bit(ICE_FLAG_SRIOV_CAPABLE, pf->flags);
	अगर (func_caps->common_cap.sr_iov_1_1) अणु
		set_bit(ICE_FLAG_SRIOV_CAPABLE, pf->flags);
		pf->num_vfs_supported = min_t(पूर्णांक, func_caps->num_allocd_vfs,
					      ICE_MAX_VF_COUNT);
	पूर्ण
	clear_bit(ICE_FLAG_RSS_ENA, pf->flags);
	अगर (func_caps->common_cap.rss_table_size)
		set_bit(ICE_FLAG_RSS_ENA, pf->flags);

	clear_bit(ICE_FLAG_FD_ENA, pf->flags);
	अगर (func_caps->fd_fltr_guar > 0 || func_caps->fd_fltr_best_efक्रमt > 0) अणु
		u16 unused;

		/* ctrl_vsi_idx will be set to a valid value when flow director
		 * is setup by ice_init_fdir
		 */
		pf->ctrl_vsi_idx = ICE_NO_VSI;
		set_bit(ICE_FLAG_FD_ENA, pf->flags);
		/* क्रमce guaranteed filter pool क्रम PF */
		ice_alloc_fd_guar_item(&pf->hw, &unused,
				       func_caps->fd_fltr_guar);
		/* क्रमce shared filter pool क्रम PF */
		ice_alloc_fd_shrd_item(&pf->hw, &unused,
				       func_caps->fd_fltr_best_efक्रमt);
	पूर्ण

	pf->max_pf_txqs = func_caps->common_cap.num_txq;
	pf->max_pf_rxqs = func_caps->common_cap.num_rxq;
पूर्ण

/**
 * ice_init_pf - Initialize general software काष्ठाures (काष्ठा ice_pf)
 * @pf: board निजी काष्ठाure to initialize
 */
अटल पूर्णांक ice_init_pf(काष्ठा ice_pf *pf)
अणु
	ice_set_pf_caps(pf);

	mutex_init(&pf->sw_mutex);
	mutex_init(&pf->tc_mutex);

	INIT_HLIST_HEAD(&pf->aq_रुको_list);
	spin_lock_init(&pf->aq_रुको_lock);
	init_रुकोqueue_head(&pf->aq_रुको_queue);

	/* setup service समयr and periodic service task */
	समयr_setup(&pf->serv_पंचांगr, ice_service_समयr, 0);
	pf->serv_पंचांगr_period = HZ;
	INIT_WORK(&pf->serv_task, ice_service_task);
	clear_bit(ICE_SERVICE_SCHED, pf->state);

	mutex_init(&pf->avail_q_mutex);
	pf->avail_txqs = biपंचांगap_zalloc(pf->max_pf_txqs, GFP_KERNEL);
	अगर (!pf->avail_txqs)
		वापस -ENOMEM;

	pf->avail_rxqs = biपंचांगap_zalloc(pf->max_pf_rxqs, GFP_KERNEL);
	अगर (!pf->avail_rxqs) अणु
		devm_kमुक्त(ice_pf_to_dev(pf), pf->avail_txqs);
		pf->avail_txqs = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_ena_msix_range - Request a range of MSIX vectors from the OS
 * @pf: board निजी काष्ठाure
 *
 * compute the number of MSIX vectors required (v_budget) and request from
 * the OS. Return the number of vectors reserved or negative on failure
 */
अटल पूर्णांक ice_ena_msix_range(काष्ठा ice_pf *pf)
अणु
	पूर्णांक v_left, v_actual, v_other, v_budget = 0;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	पूर्णांक needed, err, i;

	v_left = pf->hw.func_caps.common_cap.num_msix_vectors;

	/* reserve क्रम LAN miscellaneous handler */
	needed = ICE_MIN_LAN_OICR_MSIX;
	अगर (v_left < needed)
		जाओ no_hw_vecs_left_err;
	v_budget += needed;
	v_left -= needed;

	/* reserve क्रम flow director */
	अगर (test_bit(ICE_FLAG_FD_ENA, pf->flags)) अणु
		needed = ICE_Fसूची_MSIX;
		अगर (v_left < needed)
			जाओ no_hw_vecs_left_err;
		v_budget += needed;
		v_left -= needed;
	पूर्ण

	/* total used क्रम non-traffic vectors */
	v_other = v_budget;

	/* reserve vectors क्रम LAN traffic */
	needed = min_t(पूर्णांक, num_online_cpus(), v_left);
	अगर (v_left < needed)
		जाओ no_hw_vecs_left_err;
	pf->num_lan_msix = needed;
	v_budget += needed;
	v_left -= needed;

	pf->msix_entries = devm_kसुस्मृति(dev, v_budget,
					माप(*pf->msix_entries), GFP_KERNEL);
	अगर (!pf->msix_entries) अणु
		err = -ENOMEM;
		जाओ निकास_err;
	पूर्ण

	क्रम (i = 0; i < v_budget; i++)
		pf->msix_entries[i].entry = i;

	/* actually reserve the vectors */
	v_actual = pci_enable_msix_range(pf->pdev, pf->msix_entries,
					 ICE_MIN_MSIX, v_budget);
	अगर (v_actual < 0) अणु
		dev_err(dev, "unable to reserve MSI-X vectors\n");
		err = v_actual;
		जाओ msix_err;
	पूर्ण

	अगर (v_actual < v_budget) अणु
		dev_warn(dev, "not enough OS MSI-X vectors. requested = %d, obtained = %d\n",
			 v_budget, v_actual);

		अगर (v_actual < ICE_MIN_MSIX) अणु
			/* error अगर we can't get minimum vectors */
			pci_disable_msix(pf->pdev);
			err = -दुस्फल;
			जाओ msix_err;
		पूर्ण अन्यथा अणु
			पूर्णांक v_traffic = v_actual - v_other;

			अगर (v_actual == ICE_MIN_MSIX ||
			    v_traffic < ICE_MIN_LAN_TXRX_MSIX)
				pf->num_lan_msix = ICE_MIN_LAN_TXRX_MSIX;
			अन्यथा
				pf->num_lan_msix = v_traffic;

			dev_notice(dev, "Enabled %d MSI-X vectors for LAN traffic.\n",
				   pf->num_lan_msix);
		पूर्ण
	पूर्ण

	वापस v_actual;

msix_err:
	devm_kमुक्त(dev, pf->msix_entries);
	जाओ निकास_err;

no_hw_vecs_left_err:
	dev_err(dev, "not enough device MSI-X vectors. requested = %d, available = %d\n",
		needed, v_left);
	err = -दुस्फल;
निकास_err:
	pf->num_lan_msix = 0;
	वापस err;
पूर्ण

/**
 * ice_dis_msix - Disable MSI-X पूर्णांकerrupt setup in OS
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_dis_msix(काष्ठा ice_pf *pf)
अणु
	pci_disable_msix(pf->pdev);
	devm_kमुक्त(ice_pf_to_dev(pf), pf->msix_entries);
	pf->msix_entries = शून्य;
पूर्ण

/**
 * ice_clear_पूर्णांकerrupt_scheme - Unकरो things करोne by ice_init_पूर्णांकerrupt_scheme
 * @pf: board निजी काष्ठाure
 */
अटल व्योम ice_clear_पूर्णांकerrupt_scheme(काष्ठा ice_pf *pf)
अणु
	ice_dis_msix(pf);

	अगर (pf->irq_tracker) अणु
		devm_kमुक्त(ice_pf_to_dev(pf), pf->irq_tracker);
		pf->irq_tracker = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_init_पूर्णांकerrupt_scheme - Determine proper पूर्णांकerrupt scheme
 * @pf: board निजी काष्ठाure to initialize
 */
अटल पूर्णांक ice_init_पूर्णांकerrupt_scheme(काष्ठा ice_pf *pf)
अणु
	पूर्णांक vectors;

	vectors = ice_ena_msix_range(pf);

	अगर (vectors < 0)
		वापस vectors;

	/* set up vector assignment tracking */
	pf->irq_tracker = devm_kzalloc(ice_pf_to_dev(pf),
				       काष्ठा_size(pf->irq_tracker, list, vectors),
				       GFP_KERNEL);
	अगर (!pf->irq_tracker) अणु
		ice_dis_msix(pf);
		वापस -ENOMEM;
	पूर्ण

	/* populate SW पूर्णांकerrupts pool with number of OS granted IRQs. */
	pf->num_avail_sw_msix = (u16)vectors;
	pf->irq_tracker->num_entries = (u16)vectors;
	pf->irq_tracker->end = pf->irq_tracker->num_entries;

	वापस 0;
पूर्ण

/**
 * ice_is_wol_supported - check अगर WoL is supported
 * @hw: poपूर्णांकer to hardware info
 *
 * Check अगर WoL is supported based on the HW configuration.
 * Returns true अगर NVM supports and enables WoL क्रम this port, false otherwise
 */
bool ice_is_wol_supported(काष्ठा ice_hw *hw)
अणु
	u16 wol_ctrl;

	/* A bit set to 1 in the NVM Software Reserved Word 2 (WoL control
	 * word) indicates WoL is not supported on the corresponding PF ID.
	 */
	अगर (ice_पढ़ो_sr_word(hw, ICE_SR_NVM_WOL_CFG, &wol_ctrl))
		वापस false;

	वापस !(BIT(hw->port_info->lport) & wol_ctrl);
पूर्ण

/**
 * ice_vsi_recfg_qs - Change the number of queues on a VSI
 * @vsi: VSI being changed
 * @new_rx: new number of Rx queues
 * @new_tx: new number of Tx queues
 *
 * Only change the number of queues अगर new_tx, or new_rx is non-0.
 *
 * Returns 0 on success.
 */
पूर्णांक ice_vsi_recfg_qs(काष्ठा ice_vsi *vsi, पूर्णांक new_rx, पूर्णांक new_tx)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक err = 0, समयout = 50;

	अगर (!new_rx && !new_tx)
		वापस -EINVAL;

	जबतक (test_and_set_bit(ICE_CFG_BUSY, pf->state)) अणु
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
		usleep_range(1000, 2000);
	पूर्ण

	अगर (new_tx)
		vsi->req_txq = (u16)new_tx;
	अगर (new_rx)
		vsi->req_rxq = (u16)new_rx;

	/* set क्रम the next समय the netdev is started */
	अगर (!netअगर_running(vsi->netdev)) अणु
		ice_vsi_rebuild(vsi, false);
		dev_dbg(ice_pf_to_dev(pf), "Link is down, queue count change happens when link is brought up\n");
		जाओ करोne;
	पूर्ण

	ice_vsi_बंद(vsi);
	ice_vsi_rebuild(vsi, false);
	ice_pf_dcb_recfg(pf);
	ice_vsi_खोलो(vsi);
करोne:
	clear_bit(ICE_CFG_BUSY, pf->state);
	वापस err;
पूर्ण

/**
 * ice_set_safe_mode_vlan_cfg - configure PF VSI to allow all VLANs in safe mode
 * @pf: PF to configure
 *
 * No VLAN offloads/filtering are advertised in safe mode so make sure the PF
 * VSI can still Tx/Rx VLAN tagged packets.
 */
अटल व्योम ice_set_safe_mode_vlan_cfg(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_vsi *vsi = ice_get_मुख्य_vsi(pf);
	काष्ठा ice_vsi_ctx *ctxt;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;

	अगर (!vsi)
		वापस;

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस;

	hw = &pf->hw;
	ctxt->info = vsi->info;

	ctxt->info.valid_sections =
		cpu_to_le16(ICE_AQ_VSI_PROP_VLAN_VALID |
			    ICE_AQ_VSI_PROP_SECURITY_VALID |
			    ICE_AQ_VSI_PROP_SW_VALID);

	/* disable VLAN anti-spoof */
	ctxt->info.sec_flags &= ~(ICE_AQ_VSI_SEC_TX_VLAN_PRUNE_ENA <<
				  ICE_AQ_VSI_SEC_TX_PRUNE_ENA_S);

	/* disable VLAN pruning and keep all other settings */
	ctxt->info.sw_flags2 &= ~ICE_AQ_VSI_SW_FLAG_RX_VLAN_PRUNE_ENA;

	/* allow all VLANs on Tx and करोn't strip on Rx */
	ctxt->info.vlan_flags = ICE_AQ_VSI_VLAN_MODE_ALL |
		ICE_AQ_VSI_VLAN_EMOD_NOTHING;

	status = ice_update_vsi(hw, vsi->idx, ctxt, शून्य);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Failed to update VSI for safe mode VLANs, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
	पूर्ण अन्यथा अणु
		vsi->info.sec_flags = ctxt->info.sec_flags;
		vsi->info.sw_flags2 = ctxt->info.sw_flags2;
		vsi->info.vlan_flags = ctxt->info.vlan_flags;
	पूर्ण

	kमुक्त(ctxt);
पूर्ण

/**
 * ice_log_pkg_init - log result of DDP package load
 * @hw: poपूर्णांकer to hardware info
 * @status: status of package load
 */
अटल व्योम
ice_log_pkg_init(काष्ठा ice_hw *hw, क्रमागत ice_status *status)
अणु
	काष्ठा ice_pf *pf = (काष्ठा ice_pf *)hw->back;
	काष्ठा device *dev = ice_pf_to_dev(pf);

	चयन (*status) अणु
	हाल ICE_SUCCESS:
		/* The package करोwnload AdminQ command वापसed success because
		 * this करोwnload succeeded or ICE_ERR_AQ_NO_WORK since there is
		 * alपढ़ोy a package loaded on the device.
		 */
		अगर (hw->pkg_ver.major == hw->active_pkg_ver.major &&
		    hw->pkg_ver.minor == hw->active_pkg_ver.minor &&
		    hw->pkg_ver.update == hw->active_pkg_ver.update &&
		    hw->pkg_ver.draft == hw->active_pkg_ver.draft &&
		    !स_भेद(hw->pkg_name, hw->active_pkg_name,
			    माप(hw->pkg_name))) अणु
			अगर (hw->pkg_dwnld_status == ICE_AQ_RC_EEXIST)
				dev_info(dev, "DDP package already present on device: %s version %d.%d.%d.%d\n",
					 hw->active_pkg_name,
					 hw->active_pkg_ver.major,
					 hw->active_pkg_ver.minor,
					 hw->active_pkg_ver.update,
					 hw->active_pkg_ver.draft);
			अन्यथा
				dev_info(dev, "The DDP package was successfully loaded: %s version %d.%d.%d.%d\n",
					 hw->active_pkg_name,
					 hw->active_pkg_ver.major,
					 hw->active_pkg_ver.minor,
					 hw->active_pkg_ver.update,
					 hw->active_pkg_ver.draft);
		पूर्ण अन्यथा अगर (hw->active_pkg_ver.major != ICE_PKG_SUPP_VER_MAJ ||
			   hw->active_pkg_ver.minor != ICE_PKG_SUPP_VER_MNR) अणु
			dev_err(dev, "The device has a DDP package that is not supported by the driver.  The device has package '%s' version %d.%d.x.x.  The driver requires version %d.%d.x.x.  Entering Safe Mode.\n",
				hw->active_pkg_name,
				hw->active_pkg_ver.major,
				hw->active_pkg_ver.minor,
				ICE_PKG_SUPP_VER_MAJ, ICE_PKG_SUPP_VER_MNR);
			*status = ICE_ERR_NOT_SUPPORTED;
		पूर्ण अन्यथा अगर (hw->active_pkg_ver.major == ICE_PKG_SUPP_VER_MAJ &&
			   hw->active_pkg_ver.minor == ICE_PKG_SUPP_VER_MNR) अणु
			dev_info(dev, "The driver could not load the DDP package file because a compatible DDP package is already present on the device.  The device has package '%s' version %d.%d.%d.%d.  The package file found by the driver: '%s' version %d.%d.%d.%d.\n",
				 hw->active_pkg_name,
				 hw->active_pkg_ver.major,
				 hw->active_pkg_ver.minor,
				 hw->active_pkg_ver.update,
				 hw->active_pkg_ver.draft,
				 hw->pkg_name,
				 hw->pkg_ver.major,
				 hw->pkg_ver.minor,
				 hw->pkg_ver.update,
				 hw->pkg_ver.draft);
		पूर्ण अन्यथा अणु
			dev_err(dev, "An unknown error occurred when loading the DDP package, please reboot the system.  If the problem persists, update the NVM.  Entering Safe Mode.\n");
			*status = ICE_ERR_NOT_SUPPORTED;
		पूर्ण
		अवरोध;
	हाल ICE_ERR_FW_DDP_MISMATCH:
		dev_err(dev, "The firmware loaded on the device is not compatible with the DDP package.  Please update the device's NVM.  Entering safe mode.\n");
		अवरोध;
	हाल ICE_ERR_BUF_TOO_SHORT:
	हाल ICE_ERR_CFG:
		dev_err(dev, "The DDP package file is invalid. Entering Safe Mode.\n");
		अवरोध;
	हाल ICE_ERR_NOT_SUPPORTED:
		/* Package File version not supported */
		अगर (hw->pkg_ver.major > ICE_PKG_SUPP_VER_MAJ ||
		    (hw->pkg_ver.major == ICE_PKG_SUPP_VER_MAJ &&
		     hw->pkg_ver.minor > ICE_PKG_SUPP_VER_MNR))
			dev_err(dev, "The DDP package file version is higher than the driver supports.  Please use an updated driver.  Entering Safe Mode.\n");
		अन्यथा अगर (hw->pkg_ver.major < ICE_PKG_SUPP_VER_MAJ ||
			 (hw->pkg_ver.major == ICE_PKG_SUPP_VER_MAJ &&
			  hw->pkg_ver.minor < ICE_PKG_SUPP_VER_MNR))
			dev_err(dev, "The DDP package file version is lower than the driver supports.  The driver requires version %d.%d.x.x.  Please use an updated DDP Package file.  Entering Safe Mode.\n",
				ICE_PKG_SUPP_VER_MAJ, ICE_PKG_SUPP_VER_MNR);
		अवरोध;
	हाल ICE_ERR_AQ_ERROR:
		चयन (hw->pkg_dwnld_status) अणु
		हाल ICE_AQ_RC_ENOSEC:
		हाल ICE_AQ_RC_EBADSIG:
			dev_err(dev, "The DDP package could not be loaded because its signature is not valid.  Please use a valid DDP Package.  Entering Safe Mode.\n");
			वापस;
		हाल ICE_AQ_RC_ESVN:
			dev_err(dev, "The DDP Package could not be loaded because its security revision is too low.  Please use an updated DDP Package.  Entering Safe Mode.\n");
			वापस;
		हाल ICE_AQ_RC_EBADMAN:
		हाल ICE_AQ_RC_EBADBUF:
			dev_err(dev, "An error occurred on the device while loading the DDP package.  The device will be reset.\n");
			/* poll क्रम reset to complete */
			अगर (ice_check_reset(hw))
				dev_err(dev, "Error resetting device. Please reload the driver\n");
			वापस;
		शेष:
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		dev_err(dev, "An unknown error (%d) occurred when loading the DDP package.  Entering Safe Mode.\n",
			*status);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_load_pkg - load/reload the DDP Package file
 * @firmware: firmware काष्ठाure when firmware requested or शून्य क्रम reload
 * @pf: poपूर्णांकer to the PF instance
 *
 * Called on probe and post CORER/GLOBR rebuild to load DDP Package and
 * initialize HW tables.
 */
अटल व्योम
ice_load_pkg(स्थिर काष्ठा firmware *firmware, काष्ठा ice_pf *pf)
अणु
	क्रमागत ice_status status = ICE_ERR_PARAM;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;

	/* Load DDP Package */
	अगर (firmware && !hw->pkg_copy) अणु
		status = ice_copy_and_init_pkg(hw, firmware->data,
					       firmware->size);
		ice_log_pkg_init(hw, &status);
	पूर्ण अन्यथा अगर (!firmware && hw->pkg_copy) अणु
		/* Reload package during rebuild after CORER/GLOBR reset */
		status = ice_init_pkg(hw, hw->pkg_copy, hw->pkg_size);
		ice_log_pkg_init(hw, &status);
	पूर्ण अन्यथा अणु
		dev_err(dev, "The DDP package file failed to load. Entering Safe Mode.\n");
	पूर्ण

	अगर (status) अणु
		/* Safe Mode */
		clear_bit(ICE_FLAG_ADV_FEATURES, pf->flags);
		वापस;
	पूर्ण

	/* Successful करोwnload package is the precondition क्रम advanced
	 * features, hence setting the ICE_FLAG_ADV_FEATURES flag
	 */
	set_bit(ICE_FLAG_ADV_FEATURES, pf->flags);
पूर्ण

/**
 * ice_verअगरy_cacheline_size - verअगरy driver's assumption of 64 Byte cache lines
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * There is no error वापसed here because the driver should be able to handle
 * 128 Byte cache lines, so we only prपूर्णांक a warning in हाल issues are seen,
 * specअगरically with Tx.
 */
अटल व्योम ice_verअगरy_cacheline_size(काष्ठा ice_pf *pf)
अणु
	अगर (rd32(&pf->hw, GLPCI_CNF2) & GLPCI_CNF2_CACHELINE_SIZE_M)
		dev_warn(ice_pf_to_dev(pf), "%d Byte cache line assumption is invalid, driver may have Tx timeouts!\n",
			 ICE_CACHE_LINE_BYTES);
पूर्ण

/**
 * ice_send_version - update firmware with driver version
 * @pf: PF काष्ठा
 *
 * Returns ICE_SUCCESS on success, अन्यथा error code
 */
अटल क्रमागत ice_status ice_send_version(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_driver_ver dv;

	dv.major_ver = 0xff;
	dv.minor_ver = 0xff;
	dv.build_ver = 0xff;
	dv.subbuild_ver = 0;
	strscpy((अक्षर *)dv.driver_string, UTS_RELEASE,
		माप(dv.driver_string));
	वापस ice_aq_send_driver_ver(&pf->hw, &dv, शून्य);
पूर्ण

/**
 * ice_init_fdir - Initialize flow director VSI and configuration
 * @pf: poपूर्णांकer to the PF instance
 *
 * वापसs 0 on success, negative on error
 */
अटल पूर्णांक ice_init_fdir(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_vsi *ctrl_vsi;
	पूर्णांक err;

	/* Side Band Flow Director needs to have a control VSI.
	 * Allocate it and store it in the PF.
	 */
	ctrl_vsi = ice_ctrl_vsi_setup(pf, pf->hw.port_info);
	अगर (!ctrl_vsi) अणु
		dev_dbg(dev, "could not create control VSI\n");
		वापस -ENOMEM;
	पूर्ण

	err = ice_vsi_खोलो_ctrl(ctrl_vsi);
	अगर (err) अणु
		dev_dbg(dev, "could not open control VSI\n");
		जाओ err_vsi_खोलो;
	पूर्ण

	mutex_init(&pf->hw.fdir_fltr_lock);

	err = ice_fdir_create_dflt_rules(pf);
	अगर (err)
		जाओ err_fdir_rule;

	वापस 0;

err_fdir_rule:
	ice_fdir_release_flows(&pf->hw);
	ice_vsi_बंद(ctrl_vsi);
err_vsi_खोलो:
	ice_vsi_release(ctrl_vsi);
	अगर (pf->ctrl_vsi_idx != ICE_NO_VSI) अणु
		pf->vsi[pf->ctrl_vsi_idx] = शून्य;
		pf->ctrl_vsi_idx = ICE_NO_VSI;
	पूर्ण
	वापस err;
पूर्ण

/**
 * ice_get_opt_fw_name - वापस optional firmware file name or शून्य
 * @pf: poपूर्णांकer to the PF instance
 */
अटल अक्षर *ice_get_opt_fw_name(काष्ठा ice_pf *pf)
अणु
	/* Optional firmware name same as शेष with additional dash
	 * followed by a EUI-64 identअगरier (PCIe Device Serial Number)
	 */
	काष्ठा pci_dev *pdev = pf->pdev;
	अक्षर *opt_fw_filename;
	u64 dsn;

	/* Determine the name of the optional file using the DSN (two
	 * dwords following the start of the DSN Capability).
	 */
	dsn = pci_get_dsn(pdev);
	अगर (!dsn)
		वापस शून्य;

	opt_fw_filename = kzalloc(NAME_MAX, GFP_KERNEL);
	अगर (!opt_fw_filename)
		वापस शून्य;

	snम_लिखो(opt_fw_filename, NAME_MAX, "%sice-%016llx.pkg",
		 ICE_DDP_PKG_PATH, dsn);

	वापस opt_fw_filename;
पूर्ण

/**
 * ice_request_fw - Device initialization routine
 * @pf: poपूर्णांकer to the PF instance
 */
अटल व्योम ice_request_fw(काष्ठा ice_pf *pf)
अणु
	अक्षर *opt_fw_filename = ice_get_opt_fw_name(pf);
	स्थिर काष्ठा firmware *firmware = शून्य;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	पूर्णांक err = 0;

	/* optional device-specअगरic DDP (अगर present) overrides the शेष DDP
	 * package file. kernel logs a debug message अगर the file करोesn't exist,
	 * and warning messages क्रम other errors.
	 */
	अगर (opt_fw_filename) अणु
		err = firmware_request_nowarn(&firmware, opt_fw_filename, dev);
		अगर (err) अणु
			kमुक्त(opt_fw_filename);
			जाओ dflt_pkg_load;
		पूर्ण

		/* request क्रम firmware was successful. Download to device */
		ice_load_pkg(firmware, pf);
		kमुक्त(opt_fw_filename);
		release_firmware(firmware);
		वापस;
	पूर्ण

dflt_pkg_load:
	err = request_firmware(&firmware, ICE_DDP_PKG_खाता, dev);
	अगर (err) अणु
		dev_err(dev, "The DDP package file was not found or could not be read. Entering Safe Mode\n");
		वापस;
	पूर्ण

	/* request क्रम firmware was successful. Download to device */
	ice_load_pkg(firmware, pf);
	release_firmware(firmware);
पूर्ण

/**
 * ice_prपूर्णांक_wake_reason - show the wake up cause in the log
 * @pf: poपूर्णांकer to the PF काष्ठा
 */
अटल व्योम ice_prपूर्णांक_wake_reason(काष्ठा ice_pf *pf)
अणु
	u32 wus = pf->wakeup_reason;
	स्थिर अक्षर *wake_str;

	/* अगर no wake event, nothing to prपूर्णांक */
	अगर (!wus)
		वापस;

	अगर (wus & PFPM_WUS_LNKC_M)
		wake_str = "Link\n";
	अन्यथा अगर (wus & PFPM_WUS_MAG_M)
		wake_str = "Magic Packet\n";
	अन्यथा अगर (wus & PFPM_WUS_MNG_M)
		wake_str = "Management\n";
	अन्यथा अगर (wus & PFPM_WUS_FW_RST_WK_M)
		wake_str = "Firmware Reset\n";
	अन्यथा
		wake_str = "Unknown\n";

	dev_info(ice_pf_to_dev(pf), "Wake reason: %s", wake_str);
पूर्ण

/**
 * ice_रेजिस्टर_netdev - रेजिस्टर netdev and devlink port
 * @pf: poपूर्णांकer to the PF काष्ठा
 */
अटल पूर्णांक ice_रेजिस्टर_netdev(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_vsi *vsi;
	पूर्णांक err = 0;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi || !vsi->netdev)
		वापस -EIO;

	err = रेजिस्टर_netdev(vsi->netdev);
	अगर (err)
		जाओ err_रेजिस्टर_netdev;

	set_bit(ICE_VSI_NETDEV_REGISTERED, vsi->state);
	netअगर_carrier_off(vsi->netdev);
	netअगर_tx_stop_all_queues(vsi->netdev);
	err = ice_devlink_create_port(vsi);
	अगर (err)
		जाओ err_devlink_create;

	devlink_port_type_eth_set(&vsi->devlink_port, vsi->netdev);

	वापस 0;
err_devlink_create:
	unरेजिस्टर_netdev(vsi->netdev);
	clear_bit(ICE_VSI_NETDEV_REGISTERED, vsi->state);
err_रेजिस्टर_netdev:
	मुक्त_netdev(vsi->netdev);
	vsi->netdev = शून्य;
	clear_bit(ICE_VSI_NETDEV_ALLOCD, vsi->state);
	वापस err;
पूर्ण

/**
 * ice_probe - Device initialization routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in ice_pci_tbl
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक
ice_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id __always_unused *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ice_pf *pf;
	काष्ठा ice_hw *hw;
	पूर्णांक i, err;

	/* this driver uses devres, see
	 * Documentation/driver-api/driver-model/devres.rst
	 */
	err = pcim_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pcim_iomap_regions(pdev, BIT(ICE_BAR0), dev_driver_string(dev));
	अगर (err) अणु
		dev_err(dev, "BAR0 I/O map error %d\n", err);
		वापस err;
	पूर्ण

	pf = ice_allocate_pf(dev);
	अगर (!pf)
		वापस -ENOMEM;

	/* set up क्रम high or low DMA */
	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (err)
		err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(dev, "DMA configuration failed: 0x%x\n", err);
		वापस err;
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);
	pci_set_master(pdev);

	pf->pdev = pdev;
	pci_set_drvdata(pdev, pf);
	set_bit(ICE_DOWN, pf->state);
	/* Disable service task until DOWN bit is cleared */
	set_bit(ICE_SERVICE_DIS, pf->state);

	hw = &pf->hw;
	hw->hw_addr = pcim_iomap_table(pdev)[ICE_BAR0];
	pci_save_state(pdev);

	hw->back = pf;
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	pci_पढ़ो_config_byte(pdev, PCI_REVISION_ID, &hw->revision_id);
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;
	hw->bus.device = PCI_SLOT(pdev->devfn);
	hw->bus.func = PCI_FUNC(pdev->devfn);
	ice_set_ctrlq_len(hw);

	pf->msg_enable = netअगर_msg_init(debug, ICE_DFLT_NETIF_M);

	err = ice_devlink_रेजिस्टर(pf);
	अगर (err) अणु
		dev_err(dev, "ice_devlink_register failed: %d\n", err);
		जाओ err_निकास_unroll;
	पूर्ण

#अगर_अघोषित CONFIG_DYNAMIC_DEBUG
	अगर (debug < -1)
		hw->debug_mask = debug;
#पूर्ण_अगर

	err = ice_init_hw(hw);
	अगर (err) अणु
		dev_err(dev, "ice_init_hw failed: %d\n", err);
		err = -EIO;
		जाओ err_निकास_unroll;
	पूर्ण

	ice_request_fw(pf);

	/* अगर ice_request_fw fails, ICE_FLAG_ADV_FEATURES bit won't be
	 * set in pf->state, which will cause ice_is_safe_mode to वापस
	 * true
	 */
	अगर (ice_is_safe_mode(pf)) अणु
		dev_err(dev, "Package download failed. Advanced features disabled - Device now in Safe Mode\n");
		/* we alपढ़ोy got function/device capabilities but these करोn't
		 * reflect what the driver needs to करो in safe mode. Instead of
		 * adding conditional logic everywhere to ignore these
		 * device/function capabilities, override them.
		 */
		ice_set_safe_mode_caps(hw);
	पूर्ण

	err = ice_init_pf(pf);
	अगर (err) अणु
		dev_err(dev, "ice_init_pf failed: %d\n", err);
		जाओ err_init_pf_unroll;
	पूर्ण

	ice_devlink_init_regions(pf);

	pf->hw.udp_tunnel_nic.set_port = ice_udp_tunnel_set_port;
	pf->hw.udp_tunnel_nic.unset_port = ice_udp_tunnel_unset_port;
	pf->hw.udp_tunnel_nic.flags = UDP_TUNNEL_NIC_INFO_MAY_SLEEP;
	pf->hw.udp_tunnel_nic.shared = &pf->hw.udp_tunnel_shared;
	i = 0;
	अगर (pf->hw.tnl.valid_count[TNL_VXLAN]) अणु
		pf->hw.udp_tunnel_nic.tables[i].n_entries =
			pf->hw.tnl.valid_count[TNL_VXLAN];
		pf->hw.udp_tunnel_nic.tables[i].tunnel_types =
			UDP_TUNNEL_TYPE_VXLAN;
		i++;
	पूर्ण
	अगर (pf->hw.tnl.valid_count[TNL_GENEVE]) अणु
		pf->hw.udp_tunnel_nic.tables[i].n_entries =
			pf->hw.tnl.valid_count[TNL_GENEVE];
		pf->hw.udp_tunnel_nic.tables[i].tunnel_types =
			UDP_TUNNEL_TYPE_GENEVE;
		i++;
	पूर्ण

	pf->num_alloc_vsi = hw->func_caps.guar_num_vsi;
	अगर (!pf->num_alloc_vsi) अणु
		err = -EIO;
		जाओ err_init_pf_unroll;
	पूर्ण
	अगर (pf->num_alloc_vsi > UDP_TUNNEL_NIC_MAX_SHARING_DEVICES) अणु
		dev_warn(&pf->pdev->dev,
			 "limiting the VSI count due to UDP tunnel limitation %d > %d\n",
			 pf->num_alloc_vsi, UDP_TUNNEL_NIC_MAX_SHARING_DEVICES);
		pf->num_alloc_vsi = UDP_TUNNEL_NIC_MAX_SHARING_DEVICES;
	पूर्ण

	pf->vsi = devm_kसुस्मृति(dev, pf->num_alloc_vsi, माप(*pf->vsi),
			       GFP_KERNEL);
	अगर (!pf->vsi) अणु
		err = -ENOMEM;
		जाओ err_init_pf_unroll;
	पूर्ण

	err = ice_init_पूर्णांकerrupt_scheme(pf);
	अगर (err) अणु
		dev_err(dev, "ice_init_interrupt_scheme failed: %d\n", err);
		err = -EIO;
		जाओ err_init_vsi_unroll;
	पूर्ण

	/* In हाल of MSIX we are going to setup the misc vector right here
	 * to handle admin queue events etc. In हाल of legacy and MSI
	 * the misc functionality and queue processing is combined in
	 * the same vector and that माला_लो setup at खोलो.
	 */
	err = ice_req_irq_msix_misc(pf);
	अगर (err) अणु
		dev_err(dev, "setup of misc vector failed: %d\n", err);
		जाओ err_init_पूर्णांकerrupt_unroll;
	पूर्ण

	/* create चयन काष्ठा क्रम the चयन element created by FW on boot */
	pf->first_sw = devm_kzalloc(dev, माप(*pf->first_sw), GFP_KERNEL);
	अगर (!pf->first_sw) अणु
		err = -ENOMEM;
		जाओ err_msix_misc_unroll;
	पूर्ण

	अगर (hw->evb_veb)
		pf->first_sw->bridge_mode = BRIDGE_MODE_VEB;
	अन्यथा
		pf->first_sw->bridge_mode = BRIDGE_MODE_VEPA;

	pf->first_sw->pf = pf;

	/* record the sw_id available क्रम later use */
	pf->first_sw->sw_id = hw->port_info->sw_id;

	err = ice_setup_pf_sw(pf);
	अगर (err) अणु
		dev_err(dev, "probe failed due to setup PF switch: %d\n", err);
		जाओ err_alloc_sw_unroll;
	पूर्ण

	clear_bit(ICE_SERVICE_DIS, pf->state);

	/* tell the firmware we are up */
	err = ice_send_version(pf);
	अगर (err) अणु
		dev_err(dev, "probe failed sending driver version %s. error: %d\n",
			UTS_RELEASE, err);
		जाओ err_send_version_unroll;
	पूर्ण

	/* since everything is good, start the service समयr */
	mod_समयr(&pf->serv_पंचांगr, round_jअगरfies(jअगरfies + pf->serv_पंचांगr_period));

	err = ice_init_link_events(pf->hw.port_info);
	अगर (err) अणु
		dev_err(dev, "ice_init_link_events failed: %d\n", err);
		जाओ err_send_version_unroll;
	पूर्ण

	/* not a fatal error अगर this fails */
	err = ice_init_nvm_phy_type(pf->hw.port_info);
	अगर (err)
		dev_err(dev, "ice_init_nvm_phy_type failed: %d\n", err);

	/* not a fatal error अगर this fails */
	err = ice_update_link_info(pf->hw.port_info);
	अगर (err)
		dev_err(dev, "ice_update_link_info failed: %d\n", err);

	ice_init_link_dflt_override(pf->hw.port_info);

	/* अगर media available, initialize PHY settings */
	अगर (pf->hw.port_info->phy.link_info.link_info &
	    ICE_AQ_MEDIA_AVAILABLE) अणु
		/* not a fatal error अगर this fails */
		err = ice_init_phy_user_cfg(pf->hw.port_info);
		अगर (err)
			dev_err(dev, "ice_init_phy_user_cfg failed: %d\n", err);

		अगर (!test_bit(ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA, pf->flags)) अणु
			काष्ठा ice_vsi *vsi = ice_get_मुख्य_vsi(pf);

			अगर (vsi)
				ice_configure_phy(vsi);
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(ICE_FLAG_NO_MEDIA, pf->flags);
	पूर्ण

	ice_verअगरy_cacheline_size(pf);

	/* Save wakeup reason रेजिस्टर क्रम later use */
	pf->wakeup_reason = rd32(hw, PFPM_WUS);

	/* check क्रम a घातer management event */
	ice_prपूर्णांक_wake_reason(pf);

	/* clear wake status, all bits */
	wr32(hw, PFPM_WUS, U32_MAX);

	/* Disable WoL at init, रुको क्रम user to enable */
	device_set_wakeup_enable(dev, false);

	अगर (ice_is_safe_mode(pf)) अणु
		ice_set_safe_mode_vlan_cfg(pf);
		जाओ probe_करोne;
	पूर्ण

	/* initialize DDP driven features */

	/* Note: Flow director init failure is non-fatal to load */
	अगर (ice_init_fdir(pf))
		dev_err(dev, "could not initialize flow director\n");

	/* Note: DCB init failure is non-fatal to load */
	अगर (ice_init_pf_dcb(pf, false)) अणु
		clear_bit(ICE_FLAG_DCB_CAPABLE, pf->flags);
		clear_bit(ICE_FLAG_DCB_ENA, pf->flags);
	पूर्ण अन्यथा अणु
		ice_cfg_lldp_mib_change(&pf->hw, true);
	पूर्ण

	अगर (ice_init_lag(pf))
		dev_warn(dev, "Failed to init link aggregation support\n");

	/* prपूर्णांक PCI link speed and width */
	pcie_prपूर्णांक_link_status(pf->pdev);

probe_करोne:
	err = ice_रेजिस्टर_netdev(pf);
	अगर (err)
		जाओ err_netdev_reg;

	/* पढ़ोy to go, so clear करोwn state bit */
	clear_bit(ICE_DOWN, pf->state);
	वापस 0;

err_netdev_reg:
err_send_version_unroll:
	ice_vsi_release_all(pf);
err_alloc_sw_unroll:
	set_bit(ICE_SERVICE_DIS, pf->state);
	set_bit(ICE_DOWN, pf->state);
	devm_kमुक्त(dev, pf->first_sw);
err_msix_misc_unroll:
	ice_मुक्त_irq_msix_misc(pf);
err_init_पूर्णांकerrupt_unroll:
	ice_clear_पूर्णांकerrupt_scheme(pf);
err_init_vsi_unroll:
	devm_kमुक्त(dev, pf->vsi);
err_init_pf_unroll:
	ice_deinit_pf(pf);
	ice_devlink_destroy_regions(pf);
	ice_deinit_hw(hw);
err_निकास_unroll:
	ice_devlink_unरेजिस्टर(pf);
	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * ice_set_wake - enable or disable Wake on LAN
 * @pf: poपूर्णांकer to the PF काष्ठा
 *
 * Simple helper क्रम WoL control
 */
अटल व्योम ice_set_wake(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	bool wol = pf->wol_ena;

	/* clear wake state, otherwise new wake events won't fire */
	wr32(hw, PFPM_WUS, U32_MAX);

	/* enable / disable APM wake up, no RMW needed */
	wr32(hw, PFPM_APM, wol ? PFPM_APM_APME_M : 0);

	/* set magic packet filter enabled */
	wr32(hw, PFPM_WUFC, wol ? PFPM_WUFC_MAG_M : 0);
पूर्ण

/**
 * ice_setup_mc_magic_wake - setup device to wake on multicast magic packet
 * @pf: poपूर्णांकer to the PF काष्ठा
 *
 * Issue firmware command to enable multicast magic wake, making
 * sure that any locally administered address (LAA) is used क्रम
 * wake, and that PF reset करोesn't unकरो the LAA.
 */
अटल व्योम ice_setup_mc_magic_wake(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u8 mac_addr[ETH_ALEN];
	काष्ठा ice_vsi *vsi;
	u8 flags;

	अगर (!pf->wol_ena)
		वापस;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi)
		वापस;

	/* Get current MAC address in हाल it's an LAA */
	अगर (vsi->netdev)
		ether_addr_copy(mac_addr, vsi->netdev->dev_addr);
	अन्यथा
		ether_addr_copy(mac_addr, vsi->port_info->mac.perm_addr);

	flags = ICE_AQC_MAN_MAC_WR_MC_MAG_EN |
		ICE_AQC_MAN_MAC_UPDATE_LAA_WOL |
		ICE_AQC_MAN_MAC_WR_WOL_LAA_PFR_KEEP;

	status = ice_aq_manage_mac_ग_लिखो(hw, mac_addr, flags, शून्य);
	अगर (status)
		dev_err(dev, "Failed to enable Multicast Magic Packet wake, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
पूर्ण

/**
 * ice_हटाओ - Device removal routine
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम ice_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ice_pf *pf = pci_get_drvdata(pdev);
	पूर्णांक i;

	अगर (!pf)
		वापस;

	क्रम (i = 0; i < ICE_MAX_RESET_WAIT; i++) अणु
		अगर (!ice_is_reset_in_progress(pf->state))
			अवरोध;
		msleep(100);
	पूर्ण

	अगर (test_bit(ICE_FLAG_SRIOV_ENA, pf->flags)) अणु
		set_bit(ICE_VF_RESETS_DISABLED, pf->state);
		ice_मुक्त_vfs(pf);
	पूर्ण

	set_bit(ICE_DOWN, pf->state);
	ice_service_task_stop(pf);

	ice_aq_cancel_रुकोing_tasks(pf);

	mutex_destroy(&(&pf->hw)->fdir_fltr_lock);
	ice_deinit_lag(pf);
	अगर (!ice_is_safe_mode(pf))
		ice_हटाओ_arfs(pf);
	ice_setup_mc_magic_wake(pf);
	ice_vsi_release_all(pf);
	ice_set_wake(pf);
	ice_मुक्त_irq_msix_misc(pf);
	ice_क्रम_each_vsi(pf, i) अणु
		अगर (!pf->vsi[i])
			जारी;
		ice_vsi_मुक्त_q_vectors(pf->vsi[i]);
	पूर्ण
	ice_deinit_pf(pf);
	ice_devlink_destroy_regions(pf);
	ice_deinit_hw(&pf->hw);
	ice_devlink_unरेजिस्टर(pf);

	/* Issue a PFR as part of the prescribed driver unload flow.  Do not
	 * करो it via ice_schedule_reset() since there is no need to rebuild
	 * and the service task is alपढ़ोy stopped.
	 */
	ice_reset(&pf->hw, ICE_RESET_PFR);
	pci_रुको_क्रम_pending_transaction(pdev);
	ice_clear_पूर्णांकerrupt_scheme(pf);
	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
पूर्ण

/**
 * ice_shutकरोwn - PCI callback क्रम shutting करोwn device
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम ice_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ice_pf *pf = pci_get_drvdata(pdev);

	ice_हटाओ(pdev);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, pf->wol_ena);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
/**
 * ice_prepare_क्रम_shutकरोwn - prep क्रम PCI shutकरोwn
 * @pf: board निजी काष्ठाure
 *
 * Inक्रमm or बंद all dependent features in prep क्रम PCI device shutकरोwn
 */
अटल व्योम ice_prepare_क्रम_shutकरोwn(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	u32 v;

	/* Notअगरy VFs of impending reset */
	अगर (ice_check_sq_alive(hw, &hw->mailboxq))
		ice_vc_notअगरy_reset(pf);

	dev_dbg(ice_pf_to_dev(pf), "Tearing down internal switch for shutdown\n");

	/* disable the VSIs and their queues that are not alपढ़ोy DOWN */
	ice_pf_dis_all_vsi(pf, false);

	ice_क्रम_each_vsi(pf, v)
		अगर (pf->vsi[v])
			pf->vsi[v]->vsi_num = 0;

	ice_shutकरोwn_all_ctrlq(hw);
पूर्ण

/**
 * ice_reinit_पूर्णांकerrupt_scheme - Reinitialize पूर्णांकerrupt scheme
 * @pf: board निजी काष्ठाure to reinitialize
 *
 * This routine reinitialize पूर्णांकerrupt scheme that was cleared during
 * घातer management suspend callback.
 *
 * This should be called during resume routine to re-allocate the q_vectors
 * and reacquire पूर्णांकerrupts.
 */
अटल पूर्णांक ice_reinit_पूर्णांकerrupt_scheme(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	पूर्णांक ret, v;

	/* Since we clear MSIX flag during suspend, we need to
	 * set it back during resume...
	 */

	ret = ice_init_पूर्णांकerrupt_scheme(pf);
	अगर (ret) अणु
		dev_err(dev, "Failed to re-initialize interrupt %d\n", ret);
		वापस ret;
	पूर्ण

	/* Remap vectors and rings, after successful re-init पूर्णांकerrupts */
	ice_क्रम_each_vsi(pf, v) अणु
		अगर (!pf->vsi[v])
			जारी;

		ret = ice_vsi_alloc_q_vectors(pf->vsi[v]);
		अगर (ret)
			जाओ err_reinit;
		ice_vsi_map_rings_to_vectors(pf->vsi[v]);
	पूर्ण

	ret = ice_req_irq_msix_misc(pf);
	अगर (ret) अणु
		dev_err(dev, "Setting up misc vector failed after device suspend %d\n",
			ret);
		जाओ err_reinit;
	पूर्ण

	वापस 0;

err_reinit:
	जबतक (v--)
		अगर (pf->vsi[v])
			ice_vsi_मुक्त_q_vectors(pf->vsi[v]);

	वापस ret;
पूर्ण

/**
 * ice_suspend
 * @dev: generic device inक्रमmation काष्ठाure
 *
 * Power Management callback to quiesce the device and prepare
 * क्रम D3 transition.
 */
अटल पूर्णांक __maybe_unused ice_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा ice_pf *pf;
	पूर्णांक disabled, v;

	pf = pci_get_drvdata(pdev);

	अगर (!ice_pf_state_is_nominal(pf)) अणु
		dev_err(dev, "Device is not ready, no need to suspend it\n");
		वापस -EBUSY;
	पूर्ण

	/* Stop watchकरोg tasks until resume completion.
	 * Even though it is most likely that the service task is
	 * disabled अगर the device is suspended or करोwn, the service task's
	 * state is controlled by a dअगरferent state bit, and we should
	 * store and honor whatever state that bit is in at this poपूर्णांक.
	 */
	disabled = ice_service_task_stop(pf);

	/* Alपढ़ोy suspended?, then there is nothing to करो */
	अगर (test_and_set_bit(ICE_SUSPENDED, pf->state)) अणु
		अगर (!disabled)
			ice_service_task_restart(pf);
		वापस 0;
	पूर्ण

	अगर (test_bit(ICE_DOWN, pf->state) ||
	    ice_is_reset_in_progress(pf->state)) अणु
		dev_err(dev, "can't suspend device in reset or already down\n");
		अगर (!disabled)
			ice_service_task_restart(pf);
		वापस 0;
	पूर्ण

	ice_setup_mc_magic_wake(pf);

	ice_prepare_क्रम_shutकरोwn(pf);

	ice_set_wake(pf);

	/* Free vectors, clear the पूर्णांकerrupt scheme and release IRQs
	 * क्रम proper hibernation, especially with large number of CPUs.
	 * Otherwise hibernation might fail when mapping all the vectors back
	 * to CPU0.
	 */
	ice_मुक्त_irq_msix_misc(pf);
	ice_क्रम_each_vsi(pf, v) अणु
		अगर (!pf->vsi[v])
			जारी;
		ice_vsi_मुक्त_q_vectors(pf->vsi[v]);
	पूर्ण
	ice_मुक्त_cpu_rx_rmap(ice_get_मुख्य_vsi(pf));
	ice_clear_पूर्णांकerrupt_scheme(pf);

	pci_save_state(pdev);
	pci_wake_from_d3(pdev, pf->wol_ena);
	pci_set_घातer_state(pdev, PCI_D3hot);
	वापस 0;
पूर्ण

/**
 * ice_resume - PM callback क्रम waking up from D3
 * @dev: generic device inक्रमmation काष्ठाure
 */
अटल पूर्णांक __maybe_unused ice_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	क्रमागत ice_reset_req reset_type;
	काष्ठा ice_pf *pf;
	काष्ठा ice_hw *hw;
	पूर्णांक ret;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	अगर (!pci_device_is_present(pdev))
		वापस -ENODEV;

	ret = pci_enable_device_mem(pdev);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable device after suspend\n");
		वापस ret;
	पूर्ण

	pf = pci_get_drvdata(pdev);
	hw = &pf->hw;

	pf->wakeup_reason = rd32(hw, PFPM_WUS);
	ice_prपूर्णांक_wake_reason(pf);

	/* We cleared the पूर्णांकerrupt scheme when we suspended, so we need to
	 * restore it now to resume device functionality.
	 */
	ret = ice_reinit_पूर्णांकerrupt_scheme(pf);
	अगर (ret)
		dev_err(dev, "Cannot restore interrupt scheme: %d\n", ret);

	clear_bit(ICE_DOWN, pf->state);
	/* Now perक्रमm PF reset and rebuild */
	reset_type = ICE_RESET_PFR;
	/* re-enable service task क्रम reset, but allow reset to schedule it */
	clear_bit(ICE_SERVICE_DIS, pf->state);

	अगर (ice_schedule_reset(pf, reset_type))
		dev_err(dev, "Reset during resume failed.\n");

	clear_bit(ICE_SUSPENDED, pf->state);
	ice_service_task_restart(pf);

	/* Restart the service task */
	mod_समयr(&pf->serv_पंचांगr, round_jअगरfies(jअगरfies + pf->serv_पंचांगr_period));

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

/**
 * ice_pci_err_detected - warning that PCI error has been detected
 * @pdev: PCI device inक्रमmation काष्ठा
 * @err: the type of PCI error
 *
 * Called to warn that something happened on the PCI bus and the error handling
 * is in progress.  Allows the driver to gracefully prepare/handle PCI errors.
 */
अटल pci_ers_result_t
ice_pci_err_detected(काष्ठा pci_dev *pdev, pci_channel_state_t err)
अणु
	काष्ठा ice_pf *pf = pci_get_drvdata(pdev);

	अगर (!pf) अणु
		dev_err(&pdev->dev, "%s: unrecoverable device error %d\n",
			__func__, err);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	अगर (!test_bit(ICE_SUSPENDED, pf->state)) अणु
		ice_service_task_stop(pf);

		अगर (!test_bit(ICE_PREPARED_FOR_RESET, pf->state)) अणु
			set_bit(ICE_PFR_REQ, pf->state);
			ice_prepare_क्रम_reset(pf);
		पूर्ण
	पूर्ण

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * ice_pci_err_slot_reset - a PCI slot reset has just happened
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * Called to determine अगर the driver can recover from the PCI slot reset by
 * using a रेजिस्टर पढ़ो to determine अगर the device is recoverable.
 */
अटल pci_ers_result_t ice_pci_err_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ice_pf *pf = pci_get_drvdata(pdev);
	pci_ers_result_t result;
	पूर्णांक err;
	u32 reg;

	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot re-enable PCI device after reset, error %d\n",
			err);
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		pci_restore_state(pdev);
		pci_save_state(pdev);
		pci_wake_from_d3(pdev, false);

		/* Check क्रम lअगरe */
		reg = rd32(&pf->hw, GLGEN_RTRIG);
		अगर (!reg)
			result = PCI_ERS_RESULT_RECOVERED;
		अन्यथा
			result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	err = pci_aer_clear_nonfatal_status(pdev);
	अगर (err)
		dev_dbg(&pdev->dev, "pci_aer_clear_nonfatal_status() failed, error %d\n",
			err);
		/* non-fatal, जारी */

	वापस result;
पूर्ण

/**
 * ice_pci_err_resume - restart operations after PCI error recovery
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * Called to allow the driver to bring things back up after PCI error and/or
 * reset recovery have finished
 */
अटल व्योम ice_pci_err_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ice_pf *pf = pci_get_drvdata(pdev);

	अगर (!pf) अणु
		dev_err(&pdev->dev, "%s failed, device is unrecoverable\n",
			__func__);
		वापस;
	पूर्ण

	अगर (test_bit(ICE_SUSPENDED, pf->state)) अणु
		dev_dbg(&pdev->dev, "%s failed to resume normal operations!\n",
			__func__);
		वापस;
	पूर्ण

	ice_restore_all_vfs_msi_state(pdev);

	ice_करो_reset(pf, ICE_RESET_PFR);
	ice_service_task_restart(pf);
	mod_समयr(&pf->serv_पंचांगr, round_jअगरfies(jअगरfies + pf->serv_पंचांगr_period));
पूर्ण

/**
 * ice_pci_err_reset_prepare - prepare device driver क्रम PCI reset
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम ice_pci_err_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ice_pf *pf = pci_get_drvdata(pdev);

	अगर (!test_bit(ICE_SUSPENDED, pf->state)) अणु
		ice_service_task_stop(pf);

		अगर (!test_bit(ICE_PREPARED_FOR_RESET, pf->state)) अणु
			set_bit(ICE_PFR_REQ, pf->state);
			ice_prepare_क्रम_reset(pf);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_pci_err_reset_करोne - PCI reset करोne, device driver reset can begin
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम ice_pci_err_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	ice_pci_err_resume(pdev);
पूर्ण

/* ice_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id ice_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E810C_BACKPLANE), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E810C_QSFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E810C_SFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E810_XXV_SFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823C_BACKPLANE), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823C_QSFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823C_SFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823C_10G_BASE_T), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823C_SGMII), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822C_BACKPLANE), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822C_QSFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822C_SFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822C_10G_BASE_T), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822C_SGMII), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822L_BACKPLANE), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822L_SFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822L_10G_BASE_T), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E822L_SGMII), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823L_BACKPLANE), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823L_SFP), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823L_10G_BASE_T), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823L_1GBE), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, ICE_DEV_ID_E823L_QSFP), 0 पूर्ण,
	/* required last entry */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ice_pci_tbl);

अटल __maybe_unused SIMPLE_DEV_PM_OPS(ice_pm_ops, ice_suspend, ice_resume);

अटल स्थिर काष्ठा pci_error_handlers ice_pci_err_handler = अणु
	.error_detected = ice_pci_err_detected,
	.slot_reset = ice_pci_err_slot_reset,
	.reset_prepare = ice_pci_err_reset_prepare,
	.reset_करोne = ice_pci_err_reset_करोne,
	.resume = ice_pci_err_resume
पूर्ण;

अटल काष्ठा pci_driver ice_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = ice_pci_tbl,
	.probe = ice_probe,
	.हटाओ = ice_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver.pm = &ice_pm_ops,
#पूर्ण_अगर /* CONFIG_PM */
	.shutकरोwn = ice_shutकरोwn,
	.sriov_configure = ice_sriov_configure,
	.err_handler = &ice_pci_err_handler
पूर्ण;

/**
 * ice_module_init - Driver registration routine
 *
 * ice_module_init is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 */
अटल पूर्णांक __init ice_module_init(व्योम)
अणु
	पूर्णांक status;

	pr_info("%s\n", ice_driver_string);
	pr_info("%s\n", ice_copyright);

	ice_wq = alloc_workqueue("%s", WQ_MEM_RECLAIM, 0, KBUILD_MODNAME);
	अगर (!ice_wq) अणु
		pr_err("Failed to create workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	status = pci_रेजिस्टर_driver(&ice_driver);
	अगर (status) अणु
		pr_err("failed to register PCI driver, err %d\n", status);
		destroy_workqueue(ice_wq);
	पूर्ण

	वापस status;
पूर्ण
module_init(ice_module_init);

/**
 * ice_module_निकास - Driver निकास cleanup routine
 *
 * ice_module_निकास is called just beक्रमe the driver is हटाओd
 * from memory.
 */
अटल व्योम __निकास ice_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ice_driver);
	destroy_workqueue(ice_wq);
	pr_info("module unloaded\n");
पूर्ण
module_निकास(ice_module_निकास);

/**
 * ice_set_mac_address - NDO callback to set MAC address
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @pi: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक ice_set_mac_address(काष्ठा net_device *netdev, व्योम *pi)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा sockaddr *addr = pi;
	क्रमागत ice_status status;
	u8 flags = 0;
	पूर्णांक err = 0;
	u8 *mac;

	mac = (u8 *)addr->sa_data;

	अगर (!is_valid_ether_addr(mac))
		वापस -EADDRNOTAVAIL;

	अगर (ether_addr_equal(netdev->dev_addr, mac)) अणु
		netdev_warn(netdev, "already using mac %pM\n", mac);
		वापस 0;
	पूर्ण

	अगर (test_bit(ICE_DOWN, pf->state) ||
	    ice_is_reset_in_progress(pf->state)) अणु
		netdev_err(netdev, "can't set mac %pM. device not ready\n",
			   mac);
		वापस -EBUSY;
	पूर्ण

	/* Clean up old MAC filter. Not an error अगर old filter करोesn't exist */
	status = ice_fltr_हटाओ_mac(vsi, netdev->dev_addr, ICE_FWD_TO_VSI);
	अगर (status && status != ICE_ERR_DOES_NOT_EXIST) अणु
		err = -EADDRNOTAVAIL;
		जाओ err_update_filters;
	पूर्ण

	/* Add filter क्रम new MAC. If filter exists, वापस success */
	status = ice_fltr_add_mac(vsi, mac, ICE_FWD_TO_VSI);
	अगर (status == ICE_ERR_ALREADY_EXISTS) अणु
		/* Although this MAC filter is alपढ़ोy present in hardware it's
		 * possible in some हालs (e.g. bonding) that dev_addr was
		 * modअगरied outside of the driver and needs to be restored back
		 * to this value.
		 */
		स_नकल(netdev->dev_addr, mac, netdev->addr_len);
		netdev_dbg(netdev, "filter for MAC %pM already exists\n", mac);
		वापस 0;
	पूर्ण

	/* error अगर the new filter addition failed */
	अगर (status)
		err = -EADDRNOTAVAIL;

err_update_filters:
	अगर (err) अणु
		netdev_err(netdev, "can't set MAC %pM. filter update failed\n",
			   mac);
		वापस err;
	पूर्ण

	/* change the netdev's MAC address */
	स_नकल(netdev->dev_addr, mac, netdev->addr_len);
	netdev_dbg(vsi->netdev, "updated MAC address to %pM\n",
		   netdev->dev_addr);

	/* ग_लिखो new MAC address to the firmware */
	flags = ICE_AQC_MAN_MAC_UPDATE_LAA_WOL;
	status = ice_aq_manage_mac_ग_लिखो(hw, mac, flags, शून्य);
	अगर (status) अणु
		netdev_err(netdev, "can't set MAC %pM. write to firmware failed error %s\n",
			   mac, ice_stat_str(status));
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_set_rx_mode - NDO callback to set the netdev filters
 * @netdev: network पूर्णांकerface device काष्ठाure
 */
अटल व्योम ice_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;

	अगर (!vsi)
		वापस;

	/* Set the flags to synchronize filters
	 * nकरो_set_rx_mode may be triggered even without a change in netdev
	 * flags
	 */
	set_bit(ICE_VSI_UMAC_FLTR_CHANGED, vsi->state);
	set_bit(ICE_VSI_MMAC_FLTR_CHANGED, vsi->state);
	set_bit(ICE_FLAG_FLTR_SYNC, vsi->back->flags);

	/* schedule our worker thपढ़ो which will take care of
	 * applying the new filter changes
	 */
	ice_service_task_schedule(vsi->back);
पूर्ण

/**
 * ice_set_tx_maxrate - NDO callback to set the maximum per-queue bitrate
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @queue_index: Queue ID
 * @maxrate: maximum bandwidth in Mbps
 */
अटल पूर्णांक
ice_set_tx_maxrate(काष्ठा net_device *netdev, पूर्णांक queue_index, u32 maxrate)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	क्रमागत ice_status status;
	u16 q_handle;
	u8 tc;

	/* Validate maxrate requested is within permitted range */
	अगर (maxrate && (maxrate > (ICE_SCHED_MAX_BW / 1000))) अणु
		netdev_err(netdev, "Invalid max rate %d specified for the queue %d\n",
			   maxrate, queue_index);
		वापस -EINVAL;
	पूर्ण

	q_handle = vsi->tx_rings[queue_index]->q_handle;
	tc = ice_dcb_get_tc(vsi, queue_index);

	/* Set BW back to शेष, when user set maxrate to 0 */
	अगर (!maxrate)
		status = ice_cfg_q_bw_dflt_lmt(vsi->port_info, vsi->idx, tc,
					       q_handle, ICE_MAX_BW);
	अन्यथा
		status = ice_cfg_q_bw_lmt(vsi->port_info, vsi->idx, tc,
					  q_handle, ICE_MAX_BW, maxrate * 1000);
	अगर (status) अणु
		netdev_err(netdev, "Unable to set Tx max rate, error %s\n",
			   ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_fdb_add - add an entry to the hardware database
 * @ndm: the input from the stack
 * @tb: poपूर्णांकer to array of nladdr (unused)
 * @dev: the net device poपूर्णांकer
 * @addr: the MAC address entry being added
 * @vid: VLAN ID
 * @flags: inकाष्ठाions from stack about fdb operation
 * @extack: netlink extended ack
 */
अटल पूर्णांक
ice_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr __always_unused *tb[],
	    काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr, u16 vid,
	    u16 flags, काष्ठा netlink_ext_ack __always_unused *extack)
अणु
	पूर्णांक err;

	अगर (vid) अणु
		netdev_err(dev, "VLANs aren't supported yet for dev_uc|mc_add()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ndm->ndm_state && !(ndm->ndm_state & NUD_PERMANENT)) अणु
		netdev_err(dev, "FDB only supports static addresses\n");
		वापस -EINVAL;
	पूर्ण

	अगर (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr))
		err = dev_uc_add_excl(dev, addr);
	अन्यथा अगर (is_multicast_ether_addr(addr))
		err = dev_mc_add_excl(dev, addr);
	अन्यथा
		err = -EINVAL;

	/* Only वापस duplicate errors अगर NLM_F_EXCL is set */
	अगर (err == -EEXIST && !(flags & NLM_F_EXCL))
		err = 0;

	वापस err;
पूर्ण

/**
 * ice_fdb_del - delete an entry from the hardware database
 * @ndm: the input from the stack
 * @tb: poपूर्णांकer to array of nladdr (unused)
 * @dev: the net device poपूर्णांकer
 * @addr: the MAC address entry being added
 * @vid: VLAN ID
 */
अटल पूर्णांक
ice_fdb_del(काष्ठा ndmsg *ndm, __always_unused काष्ठा nlattr *tb[],
	    काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr,
	    __always_unused u16 vid)
अणु
	पूर्णांक err;

	अगर (ndm->ndm_state & NUD_PERMANENT) अणु
		netdev_err(dev, "FDB only supports static addresses\n");
		वापस -EINVAL;
	पूर्ण

	अगर (is_unicast_ether_addr(addr))
		err = dev_uc_del(dev, addr);
	अन्यथा अगर (is_multicast_ether_addr(addr))
		err = dev_mc_del(dev, addr);
	अन्यथा
		err = -EINVAL;

	वापस err;
पूर्ण

/**
 * ice_set_features - set the netdev feature flags
 * @netdev: ptr to the netdev being adjusted
 * @features: the feature set that the stack is suggesting
 */
अटल पूर्णांक
ice_set_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक ret = 0;

	/* Don't set any netdev advanced features with device in Safe Mode */
	अगर (ice_is_safe_mode(vsi->back)) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Device is in Safe Mode - not enabling advanced netdev features\n");
		वापस ret;
	पूर्ण

	/* Do not change setting during reset */
	अगर (ice_is_reset_in_progress(pf->state)) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Device is resetting, changing advanced netdev features temporarily unavailable.\n");
		वापस -EBUSY;
	पूर्ण

	/* Multiple features can be changed in one call so keep features in
	 * separate अगर/अन्यथा statements to guarantee each feature is checked
	 */
	अगर (features & NETIF_F_RXHASH && !(netdev->features & NETIF_F_RXHASH))
		ice_vsi_manage_rss_lut(vsi, true);
	अन्यथा अगर (!(features & NETIF_F_RXHASH) &&
		 netdev->features & NETIF_F_RXHASH)
		ice_vsi_manage_rss_lut(vsi, false);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_RX))
		ret = ice_vsi_manage_vlan_stripping(vsi, true);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_RX) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_RX))
		ret = ice_vsi_manage_vlan_stripping(vsi, false);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_TX) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_TX))
		ret = ice_vsi_manage_vlan_insertion(vsi);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_TX) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_TX))
		ret = ice_vsi_manage_vlan_insertion(vsi);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		ret = ice_cfg_vlan_pruning(vsi, true, false);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		ret = ice_cfg_vlan_pruning(vsi, false, false);

	अगर ((features & NETIF_F_NTUPLE) &&
	    !(netdev->features & NETIF_F_NTUPLE)) अणु
		ice_vsi_manage_fdir(vsi, true);
		ice_init_arfs(vsi);
	पूर्ण अन्यथा अगर (!(features & NETIF_F_NTUPLE) &&
		 (netdev->features & NETIF_F_NTUPLE)) अणु
		ice_vsi_manage_fdir(vsi, false);
		ice_clear_arfs(vsi);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ice_vsi_vlan_setup - Setup VLAN offload properties on a VSI
 * @vsi: VSI to setup VLAN properties क्रम
 */
अटल पूर्णांक ice_vsi_vlan_setup(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक ret = 0;

	अगर (vsi->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		ret = ice_vsi_manage_vlan_stripping(vsi, true);
	अगर (vsi->netdev->features & NETIF_F_HW_VLAN_CTAG_TX)
		ret = ice_vsi_manage_vlan_insertion(vsi);

	वापस ret;
पूर्ण

/**
 * ice_vsi_cfg - Setup the VSI
 * @vsi: the VSI being configured
 *
 * Return 0 on success and negative value on error
 */
पूर्णांक ice_vsi_cfg(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक err;

	अगर (vsi->netdev) अणु
		ice_set_rx_mode(vsi->netdev);

		err = ice_vsi_vlan_setup(vsi);

		अगर (err)
			वापस err;
	पूर्ण
	ice_vsi_cfg_dcb_rings(vsi);

	err = ice_vsi_cfg_lan_txqs(vsi);
	अगर (!err && ice_is_xdp_ena_vsi(vsi))
		err = ice_vsi_cfg_xdp_txqs(vsi);
	अगर (!err)
		err = ice_vsi_cfg_rxqs(vsi);

	वापस err;
पूर्ण

/* THEORY OF MODERATION:
 * The below code creates custom DIM profiles क्रम use by this driver, because
 * the ice driver hardware works dअगरferently than the hardware that DIMLIB was
 * originally made क्रम. ice hardware करोesn't have packet count limits that
 * can trigger an पूर्णांकerrupt, but it *करोes* have पूर्णांकerrupt rate limit support,
 * and this code adds that capability to be used by the driver when it's using
 * DIMLIB. The DIMLIB code was always deचिन्हित to be a suggestion to the driver
 * क्रम how to "respond" to traffic and पूर्णांकerrupts, so this driver uses a
 * slightly dअगरferent set of moderation parameters to get best perक्रमmance.
 */
काष्ठा ice_dim अणु
	/* the throttle rate क्रम पूर्णांकerrupts, basically worst हाल delay beक्रमe
	 * an initial पूर्णांकerrupt fires, value is stored in microseconds.
	 */
	u16 itr;
	/* the rate limit क्रम पूर्णांकerrupts, which can cap a delay from a small
	 * ITR at a certain amount of पूर्णांकerrupts per second. f.e. a 2us ITR
	 * could yield as much as 500,000 पूर्णांकerrupts per second, but with a
	 * 10us rate limit, it limits to 100,000 पूर्णांकerrupts per second. Value
	 * is stored in microseconds.
	 */
	u16 पूर्णांकrl;
पूर्ण;

/* Make a dअगरferent profile क्रम Rx that करोesn't allow quite so aggressive
 * moderation at the high end (it maxes out at 128us or about 8k पूर्णांकerrupts a
 * second. The INTRL/rate parameters here are only useful to cap small ITR
 * values, which is why क्रम larger ITR's - like 128, which can only generate
 * 8k पूर्णांकerrupts per second, there is no poपूर्णांक to rate limit and the values
 * are set to zero. The rate limit values करो affect latency, and so must
 * be reasonably small so to not impact latency sensitive tests.
 */
अटल स्थिर काष्ठा ice_dim rx_profile[] = अणु
	अणु2, 10पूर्ण,
	अणु8, 16पूर्ण,
	अणु32, 0पूर्ण,
	अणु96, 0पूर्ण,
	अणु128, 0पूर्ण
पूर्ण;

/* The transmit profile, which has the same sorts of values
 * as the previous काष्ठा
 */
अटल स्थिर काष्ठा ice_dim tx_profile[] = अणु
	अणु2, 10पूर्ण,
	अणु8, 16पूर्ण,
	अणु64, 0पूर्ण,
	अणु128, 0पूर्ण,
	अणु256, 0पूर्ण
पूर्ण;

अटल व्योम ice_tx_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ice_ring_container *rc;
	काष्ठा ice_q_vector *q_vector;
	काष्ठा dim *dim;
	u16 itr, पूर्णांकrl;

	dim = container_of(work, काष्ठा dim, work);
	rc = container_of(dim, काष्ठा ice_ring_container, dim);
	q_vector = container_of(rc, काष्ठा ice_q_vector, tx);

	अगर (dim->profile_ix >= ARRAY_SIZE(tx_profile))
		dim->profile_ix = ARRAY_SIZE(tx_profile) - 1;

	/* look up the values in our local table */
	itr = tx_profile[dim->profile_ix].itr;
	पूर्णांकrl = tx_profile[dim->profile_ix].पूर्णांकrl;

	ice_ग_लिखो_itr(rc, itr);
	ice_ग_लिखो_पूर्णांकrl(q_vector, पूर्णांकrl);

	dim->state = DIM_START_MEASURE;
पूर्ण

अटल व्योम ice_rx_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ice_ring_container *rc;
	काष्ठा ice_q_vector *q_vector;
	काष्ठा dim *dim;
	u16 itr, पूर्णांकrl;

	dim = container_of(work, काष्ठा dim, work);
	rc = container_of(dim, काष्ठा ice_ring_container, dim);
	q_vector = container_of(rc, काष्ठा ice_q_vector, rx);

	अगर (dim->profile_ix >= ARRAY_SIZE(rx_profile))
		dim->profile_ix = ARRAY_SIZE(rx_profile) - 1;

	/* look up the values in our local table */
	itr = rx_profile[dim->profile_ix].itr;
	पूर्णांकrl = rx_profile[dim->profile_ix].पूर्णांकrl;

	ice_ग_लिखो_itr(rc, itr);
	ice_ग_लिखो_पूर्णांकrl(q_vector, पूर्णांकrl);

	dim->state = DIM_START_MEASURE;
पूर्ण

/**
 * ice_napi_enable_all - Enable NAPI क्रम all q_vectors in the VSI
 * @vsi: the VSI being configured
 */
अटल व्योम ice_napi_enable_all(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक q_idx;

	अगर (!vsi->netdev)
		वापस;

	ice_क्रम_each_q_vector(vsi, q_idx) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[q_idx];

		INIT_WORK(&q_vector->tx.dim.work, ice_tx_dim_work);
		q_vector->tx.dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;

		INIT_WORK(&q_vector->rx.dim.work, ice_rx_dim_work);
		q_vector->rx.dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;

		अगर (q_vector->rx.ring || q_vector->tx.ring)
			napi_enable(&q_vector->napi);
	पूर्ण
पूर्ण

/**
 * ice_up_complete - Finish the last steps of bringing up a connection
 * @vsi: The VSI being configured
 *
 * Return 0 on success and negative value on error
 */
अटल पूर्णांक ice_up_complete(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक err;

	ice_vsi_cfg_msix(vsi);

	/* Enable only Rx rings, Tx rings were enabled by the FW when the
	 * Tx queue group list was configured and the context bits were
	 * programmed using ice_vsi_cfg_txqs
	 */
	err = ice_vsi_start_all_rx_rings(vsi);
	अगर (err)
		वापस err;

	clear_bit(ICE_VSI_DOWN, vsi->state);
	ice_napi_enable_all(vsi);
	ice_vsi_ena_irq(vsi);

	अगर (vsi->port_info &&
	    (vsi->port_info->phy.link_info.link_info & ICE_AQ_LINK_UP) &&
	    vsi->netdev) अणु
		ice_prपूर्णांक_link_msg(vsi, true);
		netअगर_tx_start_all_queues(vsi->netdev);
		netअगर_carrier_on(vsi->netdev);
	पूर्ण

	ice_service_task_schedule(pf);

	वापस 0;
पूर्ण

/**
 * ice_up - Bring the connection back up after being करोwn
 * @vsi: VSI being configured
 */
पूर्णांक ice_up(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक err;

	err = ice_vsi_cfg(vsi);
	अगर (!err)
		err = ice_up_complete(vsi);

	वापस err;
पूर्ण

/**
 * ice_fetch_u64_stats_per_ring - get packets and bytes stats per ring
 * @ring: Tx or Rx ring to पढ़ो stats from
 * @pkts: packets stats counter
 * @bytes: bytes stats counter
 *
 * This function fetches stats from the ring considering the atomic operations
 * that needs to be perक्रमmed to पढ़ो u64 values in 32 bit machine.
 */
अटल व्योम
ice_fetch_u64_stats_per_ring(काष्ठा ice_ring *ring, u64 *pkts, u64 *bytes)
अणु
	अचिन्हित पूर्णांक start;
	*pkts = 0;
	*bytes = 0;

	अगर (!ring)
		वापस;
	करो अणु
		start = u64_stats_fetch_begin_irq(&ring->syncp);
		*pkts = ring->stats.pkts;
		*bytes = ring->stats.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
पूर्ण

/**
 * ice_update_vsi_tx_ring_stats - Update VSI Tx ring stats counters
 * @vsi: the VSI to be updated
 * @rings: rings to work on
 * @count: number of rings
 */
अटल व्योम
ice_update_vsi_tx_ring_stats(काष्ठा ice_vsi *vsi, काष्ठा ice_ring **rings,
			     u16 count)
अणु
	काष्ठा rtnl_link_stats64 *vsi_stats = &vsi->net_stats;
	u16 i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा ice_ring *ring;
		u64 pkts, bytes;

		ring = READ_ONCE(rings[i]);
		ice_fetch_u64_stats_per_ring(ring, &pkts, &bytes);
		vsi_stats->tx_packets += pkts;
		vsi_stats->tx_bytes += bytes;
		vsi->tx_restart += ring->tx_stats.restart_q;
		vsi->tx_busy += ring->tx_stats.tx_busy;
		vsi->tx_linearize += ring->tx_stats.tx_linearize;
	पूर्ण
पूर्ण

/**
 * ice_update_vsi_ring_stats - Update VSI stats counters
 * @vsi: the VSI to be updated
 */
अटल व्योम ice_update_vsi_ring_stats(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा rtnl_link_stats64 *vsi_stats = &vsi->net_stats;
	काष्ठा ice_ring *ring;
	u64 pkts, bytes;
	पूर्णांक i;

	/* reset netdev stats */
	vsi_stats->tx_packets = 0;
	vsi_stats->tx_bytes = 0;
	vsi_stats->rx_packets = 0;
	vsi_stats->rx_bytes = 0;

	/* reset non-netdev (extended) stats */
	vsi->tx_restart = 0;
	vsi->tx_busy = 0;
	vsi->tx_linearize = 0;
	vsi->rx_buf_failed = 0;
	vsi->rx_page_failed = 0;

	rcu_पढ़ो_lock();

	/* update Tx rings counters */
	ice_update_vsi_tx_ring_stats(vsi, vsi->tx_rings, vsi->num_txq);

	/* update Rx rings counters */
	ice_क्रम_each_rxq(vsi, i) अणु
		ring = READ_ONCE(vsi->rx_rings[i]);
		ice_fetch_u64_stats_per_ring(ring, &pkts, &bytes);
		vsi_stats->rx_packets += pkts;
		vsi_stats->rx_bytes += bytes;
		vsi->rx_buf_failed += ring->rx_stats.alloc_buf_failed;
		vsi->rx_page_failed += ring->rx_stats.alloc_page_failed;
	पूर्ण

	/* update XDP Tx rings counters */
	अगर (ice_is_xdp_ena_vsi(vsi))
		ice_update_vsi_tx_ring_stats(vsi, vsi->xdp_rings,
					     vsi->num_xdp_txq);

	rcu_पढ़ो_unlock();
पूर्ण

/**
 * ice_update_vsi_stats - Update VSI stats counters
 * @vsi: the VSI to be updated
 */
व्योम ice_update_vsi_stats(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा rtnl_link_stats64 *cur_ns = &vsi->net_stats;
	काष्ठा ice_eth_stats *cur_es = &vsi->eth_stats;
	काष्ठा ice_pf *pf = vsi->back;

	अगर (test_bit(ICE_VSI_DOWN, vsi->state) ||
	    test_bit(ICE_CFG_BUSY, pf->state))
		वापस;

	/* get stats as recorded by Tx/Rx rings */
	ice_update_vsi_ring_stats(vsi);

	/* get VSI stats as recorded by the hardware */
	ice_update_eth_stats(vsi);

	cur_ns->tx_errors = cur_es->tx_errors;
	cur_ns->rx_dropped = cur_es->rx_discards;
	cur_ns->tx_dropped = cur_es->tx_discards;
	cur_ns->multicast = cur_es->rx_multicast;

	/* update some more netdev stats अगर this is मुख्य VSI */
	अगर (vsi->type == ICE_VSI_PF) अणु
		cur_ns->rx_crc_errors = pf->stats.crc_errors;
		cur_ns->rx_errors = pf->stats.crc_errors +
				    pf->stats.illegal_bytes +
				    pf->stats.rx_len_errors +
				    pf->stats.rx_undersize +
				    pf->hw_csum_rx_error +
				    pf->stats.rx_jabber +
				    pf->stats.rx_fragments +
				    pf->stats.rx_oversize;
		cur_ns->rx_length_errors = pf->stats.rx_len_errors;
		/* record drops from the port level */
		cur_ns->rx_missed_errors = pf->stats.eth.rx_discards;
	पूर्ण
पूर्ण

/**
 * ice_update_pf_stats - Update PF port stats counters
 * @pf: PF whose stats needs to be updated
 */
व्योम ice_update_pf_stats(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw_port_stats *prev_ps, *cur_ps;
	काष्ठा ice_hw *hw = &pf->hw;
	u16 fd_ctr_base;
	u8 port;

	port = hw->port_info->lport;
	prev_ps = &pf->stats_prev;
	cur_ps = &pf->stats;

	ice_stat_update40(hw, GLPRT_GORCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_bytes,
			  &cur_ps->eth.rx_bytes);

	ice_stat_update40(hw, GLPRT_UPRCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_unicast,
			  &cur_ps->eth.rx_unicast);

	ice_stat_update40(hw, GLPRT_MPRCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_multicast,
			  &cur_ps->eth.rx_multicast);

	ice_stat_update40(hw, GLPRT_BPRCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_broadcast,
			  &cur_ps->eth.rx_broadcast);

	ice_stat_update32(hw, PRTRPB_RDPC, pf->stat_prev_loaded,
			  &prev_ps->eth.rx_discards,
			  &cur_ps->eth.rx_discards);

	ice_stat_update40(hw, GLPRT_GOTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_bytes,
			  &cur_ps->eth.tx_bytes);

	ice_stat_update40(hw, GLPRT_UPTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_unicast,
			  &cur_ps->eth.tx_unicast);

	ice_stat_update40(hw, GLPRT_MPTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_multicast,
			  &cur_ps->eth.tx_multicast);

	ice_stat_update40(hw, GLPRT_BPTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_broadcast,
			  &cur_ps->eth.tx_broadcast);

	ice_stat_update32(hw, GLPRT_TDOLD(port), pf->stat_prev_loaded,
			  &prev_ps->tx_dropped_link_करोwn,
			  &cur_ps->tx_dropped_link_करोwn);

	ice_stat_update40(hw, GLPRT_PRC64L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_64, &cur_ps->rx_size_64);

	ice_stat_update40(hw, GLPRT_PRC127L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_127, &cur_ps->rx_size_127);

	ice_stat_update40(hw, GLPRT_PRC255L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_255, &cur_ps->rx_size_255);

	ice_stat_update40(hw, GLPRT_PRC511L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_511, &cur_ps->rx_size_511);

	ice_stat_update40(hw, GLPRT_PRC1023L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_1023, &cur_ps->rx_size_1023);

	ice_stat_update40(hw, GLPRT_PRC1522L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_1522, &cur_ps->rx_size_1522);

	ice_stat_update40(hw, GLPRT_PRC9522L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_big, &cur_ps->rx_size_big);

	ice_stat_update40(hw, GLPRT_PTC64L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_64, &cur_ps->tx_size_64);

	ice_stat_update40(hw, GLPRT_PTC127L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_127, &cur_ps->tx_size_127);

	ice_stat_update40(hw, GLPRT_PTC255L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_255, &cur_ps->tx_size_255);

	ice_stat_update40(hw, GLPRT_PTC511L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_511, &cur_ps->tx_size_511);

	ice_stat_update40(hw, GLPRT_PTC1023L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_1023, &cur_ps->tx_size_1023);

	ice_stat_update40(hw, GLPRT_PTC1522L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_1522, &cur_ps->tx_size_1522);

	ice_stat_update40(hw, GLPRT_PTC9522L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_big, &cur_ps->tx_size_big);

	fd_ctr_base = hw->fd_ctr_base;

	ice_stat_update40(hw,
			  GLSTAT_FD_CNT0L(ICE_FD_SB_STAT_IDX(fd_ctr_base)),
			  pf->stat_prev_loaded, &prev_ps->fd_sb_match,
			  &cur_ps->fd_sb_match);
	ice_stat_update32(hw, GLPRT_LXONRXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xon_rx, &cur_ps->link_xon_rx);

	ice_stat_update32(hw, GLPRT_LXOFFRXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xoff_rx, &cur_ps->link_xoff_rx);

	ice_stat_update32(hw, GLPRT_LXONTXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xon_tx, &cur_ps->link_xon_tx);

	ice_stat_update32(hw, GLPRT_LXOFFTXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xoff_tx, &cur_ps->link_xoff_tx);

	ice_update_dcb_stats(pf);

	ice_stat_update32(hw, GLPRT_CRCERRS(port), pf->stat_prev_loaded,
			  &prev_ps->crc_errors, &cur_ps->crc_errors);

	ice_stat_update32(hw, GLPRT_ILLERRC(port), pf->stat_prev_loaded,
			  &prev_ps->illegal_bytes, &cur_ps->illegal_bytes);

	ice_stat_update32(hw, GLPRT_MLFC(port), pf->stat_prev_loaded,
			  &prev_ps->mac_local_faults,
			  &cur_ps->mac_local_faults);

	ice_stat_update32(hw, GLPRT_MRFC(port), pf->stat_prev_loaded,
			  &prev_ps->mac_remote_faults,
			  &cur_ps->mac_remote_faults);

	ice_stat_update32(hw, GLPRT_RLEC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_len_errors, &cur_ps->rx_len_errors);

	ice_stat_update32(hw, GLPRT_RUC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_undersize, &cur_ps->rx_undersize);

	ice_stat_update32(hw, GLPRT_RFC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_fragments, &cur_ps->rx_fragments);

	ice_stat_update32(hw, GLPRT_ROC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_oversize, &cur_ps->rx_oversize);

	ice_stat_update32(hw, GLPRT_RJC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_jabber, &cur_ps->rx_jabber);

	cur_ps->fd_sb_status = test_bit(ICE_FLAG_FD_ENA, pf->flags) ? 1 : 0;

	pf->stat_prev_loaded = true;
पूर्ण

/**
 * ice_get_stats64 - get statistics क्रम network device काष्ठाure
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @stats: मुख्य device statistics काष्ठाure
 */
अटल
व्योम ice_get_stats64(काष्ठा net_device *netdev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा rtnl_link_stats64 *vsi_stats;
	काष्ठा ice_vsi *vsi = np->vsi;

	vsi_stats = &vsi->net_stats;

	अगर (!vsi->num_txq || !vsi->num_rxq)
		वापस;

	/* netdev packet/byte stats come from ring counter. These are obtained
	 * by summing up ring counters (करोne by ice_update_vsi_ring_stats).
	 * But, only call the update routine and पढ़ो the रेजिस्टरs अगर VSI is
	 * not करोwn.
	 */
	अगर (!test_bit(ICE_VSI_DOWN, vsi->state))
		ice_update_vsi_ring_stats(vsi);
	stats->tx_packets = vsi_stats->tx_packets;
	stats->tx_bytes = vsi_stats->tx_bytes;
	stats->rx_packets = vsi_stats->rx_packets;
	stats->rx_bytes = vsi_stats->rx_bytes;

	/* The rest of the stats can be पढ़ो from the hardware but instead we
	 * just वापस values that the watchकरोg task has alपढ़ोy obtained from
	 * the hardware.
	 */
	stats->multicast = vsi_stats->multicast;
	stats->tx_errors = vsi_stats->tx_errors;
	stats->tx_dropped = vsi_stats->tx_dropped;
	stats->rx_errors = vsi_stats->rx_errors;
	stats->rx_dropped = vsi_stats->rx_dropped;
	stats->rx_crc_errors = vsi_stats->rx_crc_errors;
	stats->rx_length_errors = vsi_stats->rx_length_errors;
पूर्ण

/**
 * ice_napi_disable_all - Disable NAPI क्रम all q_vectors in the VSI
 * @vsi: VSI having NAPI disabled
 */
अटल व्योम ice_napi_disable_all(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक q_idx;

	अगर (!vsi->netdev)
		वापस;

	ice_क्रम_each_q_vector(vsi, q_idx) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[q_idx];

		अगर (q_vector->rx.ring || q_vector->tx.ring)
			napi_disable(&q_vector->napi);

		cancel_work_sync(&q_vector->tx.dim.work);
		cancel_work_sync(&q_vector->rx.dim.work);
	पूर्ण
पूर्ण

/**
 * ice_करोwn - Shutकरोwn the connection
 * @vsi: The VSI being stopped
 */
पूर्णांक ice_करोwn(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i, tx_err, rx_err, link_err = 0;

	/* Caller of this function is expected to set the
	 * vsi->state ICE_DOWN bit
	 */
	अगर (vsi->netdev) अणु
		netअगर_carrier_off(vsi->netdev);
		netअगर_tx_disable(vsi->netdev);
	पूर्ण

	ice_vsi_dis_irq(vsi);

	tx_err = ice_vsi_stop_lan_tx_rings(vsi, ICE_NO_RESET, 0);
	अगर (tx_err)
		netdev_err(vsi->netdev, "Failed stop Tx rings, VSI %d error %d\n",
			   vsi->vsi_num, tx_err);
	अगर (!tx_err && ice_is_xdp_ena_vsi(vsi)) अणु
		tx_err = ice_vsi_stop_xdp_tx_rings(vsi);
		अगर (tx_err)
			netdev_err(vsi->netdev, "Failed stop XDP rings, VSI %d error %d\n",
				   vsi->vsi_num, tx_err);
	पूर्ण

	rx_err = ice_vsi_stop_all_rx_rings(vsi);
	अगर (rx_err)
		netdev_err(vsi->netdev, "Failed stop Rx rings, VSI %d error %d\n",
			   vsi->vsi_num, rx_err);

	ice_napi_disable_all(vsi);

	अगर (test_bit(ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA, vsi->back->flags)) अणु
		link_err = ice_क्रमce_phys_link_state(vsi, false);
		अगर (link_err)
			netdev_err(vsi->netdev, "Failed to set physical link down, VSI %d error %d\n",
				   vsi->vsi_num, link_err);
	पूर्ण

	ice_क्रम_each_txq(vsi, i)
		ice_clean_tx_ring(vsi->tx_rings[i]);

	ice_क्रम_each_rxq(vsi, i)
		ice_clean_rx_ring(vsi->rx_rings[i]);

	अगर (tx_err || rx_err || link_err) अणु
		netdev_err(vsi->netdev, "Failed to close VSI 0x%04X on switch 0x%04X\n",
			   vsi->vsi_num, vsi->vsw->sw_id);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vsi_setup_tx_rings - Allocate VSI Tx queue resources
 * @vsi: VSI having resources allocated
 *
 * Return 0 on success, negative on failure
 */
पूर्णांक ice_vsi_setup_tx_rings(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i, err = 0;

	अगर (!vsi->num_txq) अणु
		dev_err(ice_pf_to_dev(vsi->back), "VSI %d has 0 Tx queues\n",
			vsi->vsi_num);
		वापस -EINVAL;
	पूर्ण

	ice_क्रम_each_txq(vsi, i) अणु
		काष्ठा ice_ring *ring = vsi->tx_rings[i];

		अगर (!ring)
			वापस -EINVAL;

		ring->netdev = vsi->netdev;
		err = ice_setup_tx_ring(ring);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ice_vsi_setup_rx_rings - Allocate VSI Rx queue resources
 * @vsi: VSI having resources allocated
 *
 * Return 0 on success, negative on failure
 */
पूर्णांक ice_vsi_setup_rx_rings(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i, err = 0;

	अगर (!vsi->num_rxq) अणु
		dev_err(ice_pf_to_dev(vsi->back), "VSI %d has 0 Rx queues\n",
			vsi->vsi_num);
		वापस -EINVAL;
	पूर्ण

	ice_क्रम_each_rxq(vsi, i) अणु
		काष्ठा ice_ring *ring = vsi->rx_rings[i];

		अगर (!ring)
			वापस -EINVAL;

		ring->netdev = vsi->netdev;
		err = ice_setup_rx_ring(ring);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ice_vsi_खोलो_ctrl - खोलो control VSI क्रम use
 * @vsi: the VSI to खोलो
 *
 * Initialization of the Control VSI
 *
 * Returns 0 on success, negative value on error
 */
पूर्णांक ice_vsi_खोलो_ctrl(काष्ठा ice_vsi *vsi)
अणु
	अक्षर पूर्णांक_name[ICE_INT_NAME_STR_LEN];
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	पूर्णांक err;

	dev = ice_pf_to_dev(pf);
	/* allocate descriptors */
	err = ice_vsi_setup_tx_rings(vsi);
	अगर (err)
		जाओ err_setup_tx;

	err = ice_vsi_setup_rx_rings(vsi);
	अगर (err)
		जाओ err_setup_rx;

	err = ice_vsi_cfg(vsi);
	अगर (err)
		जाओ err_setup_rx;

	snम_लिखो(पूर्णांक_name, माप(पूर्णांक_name) - 1, "%s-%s:ctrl",
		 dev_driver_string(dev), dev_name(dev));
	err = ice_vsi_req_irq_msix(vsi, पूर्णांक_name);
	अगर (err)
		जाओ err_setup_rx;

	ice_vsi_cfg_msix(vsi);

	err = ice_vsi_start_all_rx_rings(vsi);
	अगर (err)
		जाओ err_up_complete;

	clear_bit(ICE_VSI_DOWN, vsi->state);
	ice_vsi_ena_irq(vsi);

	वापस 0;

err_up_complete:
	ice_करोwn(vsi);
err_setup_rx:
	ice_vsi_मुक्त_rx_rings(vsi);
err_setup_tx:
	ice_vsi_मुक्त_tx_rings(vsi);

	वापस err;
पूर्ण

/**
 * ice_vsi_खोलो - Called when a network पूर्णांकerface is made active
 * @vsi: the VSI to खोलो
 *
 * Initialization of the VSI
 *
 * Returns 0 on success, negative value on error
 */
अटल पूर्णांक ice_vsi_खोलो(काष्ठा ice_vsi *vsi)
अणु
	अक्षर पूर्णांक_name[ICE_INT_NAME_STR_LEN];
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक err;

	/* allocate descriptors */
	err = ice_vsi_setup_tx_rings(vsi);
	अगर (err)
		जाओ err_setup_tx;

	err = ice_vsi_setup_rx_rings(vsi);
	अगर (err)
		जाओ err_setup_rx;

	err = ice_vsi_cfg(vsi);
	अगर (err)
		जाओ err_setup_rx;

	snम_लिखो(पूर्णांक_name, माप(पूर्णांक_name) - 1, "%s-%s",
		 dev_driver_string(ice_pf_to_dev(pf)), vsi->netdev->name);
	err = ice_vsi_req_irq_msix(vsi, पूर्णांक_name);
	अगर (err)
		जाओ err_setup_rx;

	/* Notअगरy the stack of the actual queue counts. */
	err = netअगर_set_real_num_tx_queues(vsi->netdev, vsi->num_txq);
	अगर (err)
		जाओ err_set_qs;

	err = netअगर_set_real_num_rx_queues(vsi->netdev, vsi->num_rxq);
	अगर (err)
		जाओ err_set_qs;

	err = ice_up_complete(vsi);
	अगर (err)
		जाओ err_up_complete;

	वापस 0;

err_up_complete:
	ice_करोwn(vsi);
err_set_qs:
	ice_vsi_मुक्त_irq(vsi);
err_setup_rx:
	ice_vsi_मुक्त_rx_rings(vsi);
err_setup_tx:
	ice_vsi_मुक्त_tx_rings(vsi);

	वापस err;
पूर्ण

/**
 * ice_vsi_release_all - Delete all VSIs
 * @pf: PF from which all VSIs are being हटाओd
 */
अटल व्योम ice_vsi_release_all(काष्ठा ice_pf *pf)
अणु
	पूर्णांक err, i;

	अगर (!pf->vsi)
		वापस;

	ice_क्रम_each_vsi(pf, i) अणु
		अगर (!pf->vsi[i])
			जारी;

		err = ice_vsi_release(pf->vsi[i]);
		अगर (err)
			dev_dbg(ice_pf_to_dev(pf), "Failed to release pf->vsi[%d], err %d, vsi_num = %d\n",
				i, err, pf->vsi[i]->vsi_num);
	पूर्ण
पूर्ण

/**
 * ice_vsi_rebuild_by_type - Rebuild VSI of a given type
 * @pf: poपूर्णांकer to the PF instance
 * @type: VSI type to rebuild
 *
 * Iterates through the pf->vsi array and rebuilds VSIs of the requested type
 */
अटल पूर्णांक ice_vsi_rebuild_by_type(काष्ठा ice_pf *pf, क्रमागत ice_vsi_type type)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	क्रमागत ice_status status;
	पूर्णांक i, err;

	ice_क्रम_each_vsi(pf, i) अणु
		काष्ठा ice_vsi *vsi = pf->vsi[i];

		अगर (!vsi || vsi->type != type)
			जारी;

		/* rebuild the VSI */
		err = ice_vsi_rebuild(vsi, true);
		अगर (err) अणु
			dev_err(dev, "rebuild VSI failed, err %d, VSI index %d, type %s\n",
				err, vsi->idx, ice_vsi_type_str(type));
			वापस err;
		पूर्ण

		/* replay filters क्रम the VSI */
		status = ice_replay_vsi(&pf->hw, vsi->idx);
		अगर (status) अणु
			dev_err(dev, "replay VSI failed, status %s, VSI index %d, type %s\n",
				ice_stat_str(status), vsi->idx,
				ice_vsi_type_str(type));
			वापस -EIO;
		पूर्ण

		/* Re-map HW VSI number, using VSI handle that has been
		 * previously validated in ice_replay_vsi() call above
		 */
		vsi->vsi_num = ice_get_hw_vsi_num(&pf->hw, vsi->idx);

		/* enable the VSI */
		err = ice_ena_vsi(vsi, false);
		अगर (err) अणु
			dev_err(dev, "enable VSI failed, err %d, VSI index %d, type %s\n",
				err, vsi->idx, ice_vsi_type_str(type));
			वापस err;
		पूर्ण

		dev_info(dev, "VSI rebuilt. VSI index %d, type %s\n", vsi->idx,
			 ice_vsi_type_str(type));
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_update_pf_netdev_link - Update PF netdev link status
 * @pf: poपूर्णांकer to the PF instance
 */
अटल व्योम ice_update_pf_netdev_link(काष्ठा ice_pf *pf)
अणु
	bool link_up;
	पूर्णांक i;

	ice_क्रम_each_vsi(pf, i) अणु
		काष्ठा ice_vsi *vsi = pf->vsi[i];

		अगर (!vsi || vsi->type != ICE_VSI_PF)
			वापस;

		ice_get_link_status(pf->vsi[i]->port_info, &link_up);
		अगर (link_up) अणु
			netअगर_carrier_on(pf->vsi[i]->netdev);
			netअगर_tx_wake_all_queues(pf->vsi[i]->netdev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(pf->vsi[i]->netdev);
			netअगर_tx_stop_all_queues(pf->vsi[i]->netdev);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_rebuild - rebuild after reset
 * @pf: PF to rebuild
 * @reset_type: type of reset
 *
 * Do not rebuild VF VSI in this flow because that is alपढ़ोy handled via
 * ice_reset_all_vfs(). This is because requirements क्रम resetting a VF after a
 * PFR/CORER/GLOBER/etc. are dअगरferent than the normal flow. Also, we करोn't want
 * to reset/rebuild all the VF VSI twice.
 */
अटल व्योम ice_rebuild(काष्ठा ice_pf *pf, क्रमागत ice_reset_req reset_type)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status ret;
	पूर्णांक err;

	अगर (test_bit(ICE_DOWN, pf->state))
		जाओ clear_recovery;

	dev_dbg(dev, "rebuilding PF after reset_type=%d\n", reset_type);

	ret = ice_init_all_ctrlq(hw);
	अगर (ret) अणु
		dev_err(dev, "control queues init failed %s\n",
			ice_stat_str(ret));
		जाओ err_init_ctrlq;
	पूर्ण

	/* अगर DDP was previously loaded successfully */
	अगर (!ice_is_safe_mode(pf)) अणु
		/* reload the SW DB of filter tables */
		अगर (reset_type == ICE_RESET_PFR)
			ice_fill_blk_tbls(hw);
		अन्यथा
			/* Reload DDP Package after CORER/GLOBR reset */
			ice_load_pkg(शून्य, pf);
	पूर्ण

	ret = ice_clear_pf_cfg(hw);
	अगर (ret) अणु
		dev_err(dev, "clear PF configuration failed %s\n",
			ice_stat_str(ret));
		जाओ err_init_ctrlq;
	पूर्ण

	अगर (pf->first_sw->dflt_vsi_ena)
		dev_info(dev, "Clearing default VSI, re-enable after reset completes\n");
	/* clear the शेष VSI configuration अगर it exists */
	pf->first_sw->dflt_vsi = शून्य;
	pf->first_sw->dflt_vsi_ena = false;

	ice_clear_pxe_mode(hw);

	ret = ice_get_caps(hw);
	अगर (ret) अणु
		dev_err(dev, "ice_get_caps failed %s\n", ice_stat_str(ret));
		जाओ err_init_ctrlq;
	पूर्ण

	ret = ice_aq_set_mac_cfg(hw, ICE_AQ_SET_MAC_FRAME_SIZE_MAX, शून्य);
	अगर (ret) अणु
		dev_err(dev, "set_mac_cfg failed %s\n", ice_stat_str(ret));
		जाओ err_init_ctrlq;
	पूर्ण

	err = ice_sched_init_port(hw->port_info);
	अगर (err)
		जाओ err_sched_init_port;

	/* start misc vector */
	err = ice_req_irq_msix_misc(pf);
	अगर (err) अणु
		dev_err(dev, "misc vector setup failed: %d\n", err);
		जाओ err_sched_init_port;
	पूर्ण

	अगर (test_bit(ICE_FLAG_FD_ENA, pf->flags)) अणु
		wr32(hw, PFQF_FD_ENA, PFQF_FD_ENA_FD_ENA_M);
		अगर (!rd32(hw, PFQF_FD_SIZE)) अणु
			u16 unused, guar, b_efक्रमt;

			guar = hw->func_caps.fd_fltr_guar;
			b_efक्रमt = hw->func_caps.fd_fltr_best_efक्रमt;

			/* क्रमce guaranteed filter pool क्रम PF */
			ice_alloc_fd_guar_item(hw, &unused, guar);
			/* क्रमce shared filter pool क्रम PF */
			ice_alloc_fd_shrd_item(hw, &unused, b_efक्रमt);
		पूर्ण
	पूर्ण

	अगर (test_bit(ICE_FLAG_DCB_ENA, pf->flags))
		ice_dcb_rebuild(pf);

	/* rebuild PF VSI */
	err = ice_vsi_rebuild_by_type(pf, ICE_VSI_PF);
	अगर (err) अणु
		dev_err(dev, "PF VSI rebuild failed: %d\n", err);
		जाओ err_vsi_rebuild;
	पूर्ण

	/* If Flow Director is active */
	अगर (test_bit(ICE_FLAG_FD_ENA, pf->flags)) अणु
		err = ice_vsi_rebuild_by_type(pf, ICE_VSI_CTRL);
		अगर (err) अणु
			dev_err(dev, "control VSI rebuild failed: %d\n", err);
			जाओ err_vsi_rebuild;
		पूर्ण

		/* replay HW Flow Director recipes */
		अगर (hw->fdir_prof)
			ice_fdir_replay_flows(hw);

		/* replay Flow Director filters */
		ice_fdir_replay_fltrs(pf);

		ice_rebuild_arfs(pf);
	पूर्ण

	ice_update_pf_netdev_link(pf);

	/* tell the firmware we are up */
	ret = ice_send_version(pf);
	अगर (ret) अणु
		dev_err(dev, "Rebuild failed due to error sending driver version: %s\n",
			ice_stat_str(ret));
		जाओ err_vsi_rebuild;
	पूर्ण

	ice_replay_post(hw);

	/* अगर we get here, reset flow is successful */
	clear_bit(ICE_RESET_FAILED, pf->state);
	वापस;

err_vsi_rebuild:
err_sched_init_port:
	ice_sched_cleanup_all(hw);
err_init_ctrlq:
	ice_shutकरोwn_all_ctrlq(hw);
	set_bit(ICE_RESET_FAILED, pf->state);
clear_recovery:
	/* set this bit in PF state to control service task scheduling */
	set_bit(ICE_NEEDS_RESTART, pf->state);
	dev_err(dev, "Rebuild failed, unload and reload driver\n");
पूर्ण

/**
 * ice_max_xdp_frame_size - वापसs the maximum allowed frame size क्रम XDP
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 */
अटल पूर्णांक ice_max_xdp_frame_size(काष्ठा ice_vsi *vsi)
अणु
	अगर (PAGE_SIZE >= 8192 || test_bit(ICE_FLAG_LEGACY_RX, vsi->back->flags))
		वापस ICE_RXBUF_2048 - XDP_PACKET_HEADROOM;
	अन्यथा
		वापस ICE_RXBUF_3072;
पूर्ण

/**
 * ice_change_mtu - NDO callback to change the MTU
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक ice_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	u8 count = 0;

	अगर (new_mtu == (पूर्णांक)netdev->mtu) अणु
		netdev_warn(netdev, "MTU is already %u\n", netdev->mtu);
		वापस 0;
	पूर्ण

	अगर (ice_is_xdp_ena_vsi(vsi)) अणु
		पूर्णांक frame_size = ice_max_xdp_frame_size(vsi);

		अगर (new_mtu + ICE_ETH_PKT_HDR_PAD > frame_size) अणु
			netdev_err(netdev, "max MTU for XDP usage is %d\n",
				   frame_size - ICE_ETH_PKT_HDR_PAD);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* अगर a reset is in progress, रुको क्रम some समय क्रम it to complete */
	करो अणु
		अगर (ice_is_reset_in_progress(pf->state)) अणु
			count++;
			usleep_range(1000, 2000);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण

	पूर्ण जबतक (count < 100);

	अगर (count == 100) अणु
		netdev_err(netdev, "can't change MTU. Device is busy\n");
		वापस -EBUSY;
	पूर्ण

	netdev->mtu = (अचिन्हित पूर्णांक)new_mtu;

	/* अगर VSI is up, bring it करोwn and then back up */
	अगर (!test_and_set_bit(ICE_VSI_DOWN, vsi->state)) अणु
		पूर्णांक err;

		err = ice_करोwn(vsi);
		अगर (err) अणु
			netdev_err(netdev, "change MTU if_down err %d\n", err);
			वापस err;
		पूर्ण

		err = ice_up(vsi);
		अगर (err) अणु
			netdev_err(netdev, "change MTU if_up err %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	netdev_dbg(netdev, "changed MTU to %d\n", new_mtu);
	वापस 0;
पूर्ण

/**
 * ice_aq_str - convert AQ err code to a string
 * @aq_err: the AQ error code to convert
 */
स्थिर अक्षर *ice_aq_str(क्रमागत ice_aq_err aq_err)
अणु
	चयन (aq_err) अणु
	हाल ICE_AQ_RC_OK:
		वापस "OK";
	हाल ICE_AQ_RC_EPERM:
		वापस "ICE_AQ_RC_EPERM";
	हाल ICE_AQ_RC_ENOENT:
		वापस "ICE_AQ_RC_ENOENT";
	हाल ICE_AQ_RC_ENOMEM:
		वापस "ICE_AQ_RC_ENOMEM";
	हाल ICE_AQ_RC_EBUSY:
		वापस "ICE_AQ_RC_EBUSY";
	हाल ICE_AQ_RC_EEXIST:
		वापस "ICE_AQ_RC_EEXIST";
	हाल ICE_AQ_RC_EINVAL:
		वापस "ICE_AQ_RC_EINVAL";
	हाल ICE_AQ_RC_ENOSPC:
		वापस "ICE_AQ_RC_ENOSPC";
	हाल ICE_AQ_RC_ENOSYS:
		वापस "ICE_AQ_RC_ENOSYS";
	हाल ICE_AQ_RC_EMODE:
		वापस "ICE_AQ_RC_EMODE";
	हाल ICE_AQ_RC_ENOSEC:
		वापस "ICE_AQ_RC_ENOSEC";
	हाल ICE_AQ_RC_EBADSIG:
		वापस "ICE_AQ_RC_EBADSIG";
	हाल ICE_AQ_RC_ESVN:
		वापस "ICE_AQ_RC_ESVN";
	हाल ICE_AQ_RC_EBADMAN:
		वापस "ICE_AQ_RC_EBADMAN";
	हाल ICE_AQ_RC_EBADBUF:
		वापस "ICE_AQ_RC_EBADBUF";
	पूर्ण

	वापस "ICE_AQ_RC_UNKNOWN";
पूर्ण

/**
 * ice_stat_str - convert status err code to a string
 * @stat_err: the status error code to convert
 */
स्थिर अक्षर *ice_stat_str(क्रमागत ice_status stat_err)
अणु
	चयन (stat_err) अणु
	हाल ICE_SUCCESS:
		वापस "OK";
	हाल ICE_ERR_PARAM:
		वापस "ICE_ERR_PARAM";
	हाल ICE_ERR_NOT_IMPL:
		वापस "ICE_ERR_NOT_IMPL";
	हाल ICE_ERR_NOT_READY:
		वापस "ICE_ERR_NOT_READY";
	हाल ICE_ERR_NOT_SUPPORTED:
		वापस "ICE_ERR_NOT_SUPPORTED";
	हाल ICE_ERR_BAD_PTR:
		वापस "ICE_ERR_BAD_PTR";
	हाल ICE_ERR_INVAL_SIZE:
		वापस "ICE_ERR_INVAL_SIZE";
	हाल ICE_ERR_DEVICE_NOT_SUPPORTED:
		वापस "ICE_ERR_DEVICE_NOT_SUPPORTED";
	हाल ICE_ERR_RESET_FAILED:
		वापस "ICE_ERR_RESET_FAILED";
	हाल ICE_ERR_FW_API_VER:
		वापस "ICE_ERR_FW_API_VER";
	हाल ICE_ERR_NO_MEMORY:
		वापस "ICE_ERR_NO_MEMORY";
	हाल ICE_ERR_CFG:
		वापस "ICE_ERR_CFG";
	हाल ICE_ERR_OUT_OF_RANGE:
		वापस "ICE_ERR_OUT_OF_RANGE";
	हाल ICE_ERR_ALREADY_EXISTS:
		वापस "ICE_ERR_ALREADY_EXISTS";
	हाल ICE_ERR_NVM:
		वापस "ICE_ERR_NVM";
	हाल ICE_ERR_NVM_CHECKSUM:
		वापस "ICE_ERR_NVM_CHECKSUM";
	हाल ICE_ERR_BUF_TOO_SHORT:
		वापस "ICE_ERR_BUF_TOO_SHORT";
	हाल ICE_ERR_NVM_BLANK_MODE:
		वापस "ICE_ERR_NVM_BLANK_MODE";
	हाल ICE_ERR_IN_USE:
		वापस "ICE_ERR_IN_USE";
	हाल ICE_ERR_MAX_LIMIT:
		वापस "ICE_ERR_MAX_LIMIT";
	हाल ICE_ERR_RESET_ONGOING:
		वापस "ICE_ERR_RESET_ONGOING";
	हाल ICE_ERR_HW_TABLE:
		वापस "ICE_ERR_HW_TABLE";
	हाल ICE_ERR_DOES_NOT_EXIST:
		वापस "ICE_ERR_DOES_NOT_EXIST";
	हाल ICE_ERR_FW_DDP_MISMATCH:
		वापस "ICE_ERR_FW_DDP_MISMATCH";
	हाल ICE_ERR_AQ_ERROR:
		वापस "ICE_ERR_AQ_ERROR";
	हाल ICE_ERR_AQ_TIMEOUT:
		वापस "ICE_ERR_AQ_TIMEOUT";
	हाल ICE_ERR_AQ_FULL:
		वापस "ICE_ERR_AQ_FULL";
	हाल ICE_ERR_AQ_NO_WORK:
		वापस "ICE_ERR_AQ_NO_WORK";
	हाल ICE_ERR_AQ_EMPTY:
		वापस "ICE_ERR_AQ_EMPTY";
	हाल ICE_ERR_AQ_FW_CRITICAL:
		वापस "ICE_ERR_AQ_FW_CRITICAL";
	पूर्ण

	वापस "ICE_ERR_UNKNOWN";
पूर्ण

/**
 * ice_set_rss_lut - Set RSS LUT
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 * @lut: Lookup table
 * @lut_size: Lookup table size
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ice_set_rss_lut(काष्ठा ice_vsi *vsi, u8 *lut, u16 lut_size)
अणु
	काष्ठा ice_aq_get_set_rss_lut_params params = अणुपूर्ण;
	काष्ठा ice_hw *hw = &vsi->back->hw;
	क्रमागत ice_status status;

	अगर (!lut)
		वापस -EINVAL;

	params.vsi_handle = vsi->idx;
	params.lut_size = lut_size;
	params.lut_type = vsi->rss_lut_type;
	params.lut = lut;

	status = ice_aq_set_rss_lut(hw, &params);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Cannot set RSS lut, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_set_rss_key - Set RSS key
 * @vsi: Poपूर्णांकer to the VSI काष्ठाure
 * @seed: RSS hash seed
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ice_set_rss_key(काष्ठा ice_vsi *vsi, u8 *seed)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	क्रमागत ice_status status;

	अगर (!seed)
		वापस -EINVAL;

	status = ice_aq_set_rss_key(hw, vsi->idx, (काष्ठा ice_aqc_get_set_rss_keys *)seed);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Cannot set RSS key, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_get_rss_lut - Get RSS LUT
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 * @lut: Buffer to store the lookup table entries
 * @lut_size: Size of buffer to store the lookup table entries
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ice_get_rss_lut(काष्ठा ice_vsi *vsi, u8 *lut, u16 lut_size)
अणु
	काष्ठा ice_aq_get_set_rss_lut_params params = अणुपूर्ण;
	काष्ठा ice_hw *hw = &vsi->back->hw;
	क्रमागत ice_status status;

	अगर (!lut)
		वापस -EINVAL;

	params.vsi_handle = vsi->idx;
	params.lut_size = lut_size;
	params.lut_type = vsi->rss_lut_type;
	params.lut = lut;

	status = ice_aq_get_rss_lut(hw, &params);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Cannot get RSS lut, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_get_rss_key - Get RSS key
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 * @seed: Buffer to store the key in
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ice_get_rss_key(काष्ठा ice_vsi *vsi, u8 *seed)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	क्रमागत ice_status status;

	अगर (!seed)
		वापस -EINVAL;

	status = ice_aq_get_rss_key(hw, vsi->idx, (काष्ठा ice_aqc_get_set_rss_keys *)seed);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Cannot get RSS key, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_bridge_getlink - Get the hardware bridge mode
 * @skb: skb buff
 * @pid: process ID
 * @seq: RTNL message seq
 * @dev: the netdev being configured
 * @filter_mask: filter mask passed in
 * @nlflags: netlink flags passed in
 *
 * Return the bridge mode (VEB/VEPA)
 */
अटल पूर्णांक
ice_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
		   काष्ठा net_device *dev, u32 filter_mask, पूर्णांक nlflags)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(dev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	u16 bmode;

	bmode = pf->first_sw->bridge_mode;

	वापस nकरो_dflt_bridge_getlink(skb, pid, seq, dev, bmode, 0, 0, nlflags,
				       filter_mask, शून्य);
पूर्ण

/**
 * ice_vsi_update_bridge_mode - Update VSI क्रम चयनing bridge mode (VEB/VEPA)
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 * @bmode: Hardware bridge mode (VEB/VEPA)
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक ice_vsi_update_bridge_mode(काष्ठा ice_vsi *vsi, u16 bmode)
अणु
	काष्ठा ice_aqc_vsi_props *vsi_props;
	काष्ठा ice_hw *hw = &vsi->back->hw;
	काष्ठा ice_vsi_ctx *ctxt;
	क्रमागत ice_status status;
	पूर्णांक ret = 0;

	vsi_props = &vsi->info;

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस -ENOMEM;

	ctxt->info = vsi->info;

	अगर (bmode == BRIDGE_MODE_VEB)
		/* change from VEPA to VEB mode */
		ctxt->info.sw_flags |= ICE_AQ_VSI_SW_FLAG_ALLOW_LB;
	अन्यथा
		/* change from VEB to VEPA mode */
		ctxt->info.sw_flags &= ~ICE_AQ_VSI_SW_FLAG_ALLOW_LB;
	ctxt->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_SW_VALID);

	status = ice_update_vsi(hw, vsi->idx, ctxt, शून्य);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "update VSI for bridge mode failed, bmode = %d err %s aq_err %s\n",
			bmode, ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		ret = -EIO;
		जाओ out;
	पूर्ण
	/* Update sw flags क्रम book keeping */
	vsi_props->sw_flags = ctxt->info.sw_flags;

out:
	kमुक्त(ctxt);
	वापस ret;
पूर्ण

/**
 * ice_bridge_setlink - Set the hardware bridge mode
 * @dev: the netdev being configured
 * @nlh: RTNL message
 * @flags: bridge setlink flags
 * @extack: netlink extended ack
 *
 * Sets the bridge mode (VEB/VEPA) of the चयन to which the netdev (VSI) is
 * hooked up to. Iterates through the PF VSI list and sets the loopback mode (अगर
 * not alपढ़ोy set क्रम all VSIs connected to this चयन. And also update the
 * unicast चयन filter rules क्रम the corresponding चयन of the netdev.
 */
अटल पूर्णांक
ice_bridge_setlink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh,
		   u16 __always_unused flags,
		   काष्ठा netlink_ext_ack __always_unused *extack)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(dev);
	काष्ठा ice_pf *pf = np->vsi->back;
	काष्ठा nlattr *attr, *br_spec;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	काष्ठा ice_sw *pf_sw;
	पूर्णांक rem, v, err = 0;

	pf_sw = pf->first_sw;
	/* find the attribute in the netlink message */
	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);

	nla_क्रम_each_nested(attr, br_spec, rem) अणु
		__u16 mode;

		अगर (nla_type(attr) != IFLA_BRIDGE_MODE)
			जारी;
		mode = nla_get_u16(attr);
		अगर (mode != BRIDGE_MODE_VEPA && mode != BRIDGE_MODE_VEB)
			वापस -EINVAL;
		/* Continue  अगर bridge mode is not being flipped */
		अगर (mode == pf_sw->bridge_mode)
			जारी;
		/* Iterates through the PF VSI list and update the loopback
		 * mode of the VSI
		 */
		ice_क्रम_each_vsi(pf, v) अणु
			अगर (!pf->vsi[v])
				जारी;
			err = ice_vsi_update_bridge_mode(pf->vsi[v], mode);
			अगर (err)
				वापस err;
		पूर्ण

		hw->evb_veb = (mode == BRIDGE_MODE_VEB);
		/* Update the unicast चयन filter rules क्रम the corresponding
		 * चयन of the netdev
		 */
		status = ice_update_sw_rule_bridge_mode(hw);
		अगर (status) अणु
			netdev_err(dev, "switch rule update failed, mode = %d err %s aq_err %s\n",
				   mode, ice_stat_str(status),
				   ice_aq_str(hw->adminq.sq_last_status));
			/* revert hw->evb_veb */
			hw->evb_veb = (pf_sw->bridge_mode == BRIDGE_MODE_VEB);
			वापस -EIO;
		पूर्ण

		pf_sw->bridge_mode = mode;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: Tx queue
 */
अटल व्योम ice_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_ring *tx_ring = शून्य;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	u32 i;

	pf->tx_समयout_count++;

	/* Check अगर PFC is enabled क्रम the TC to which the queue beदीर्घs
	 * to. If yes then Tx समयout is not caused by a hung queue, no
	 * need to reset and rebuild
	 */
	अगर (ice_is_pfc_causing_hung_q(pf, txqueue)) अणु
		dev_info(ice_pf_to_dev(pf), "Fake Tx hang detected on queue %u, timeout caused by PFC storm\n",
			 txqueue);
		वापस;
	पूर्ण

	/* now that we have an index, find the tx_ring काष्ठा */
	क्रम (i = 0; i < vsi->num_txq; i++)
		अगर (vsi->tx_rings[i] && vsi->tx_rings[i]->desc)
			अगर (txqueue == vsi->tx_rings[i]->q_index) अणु
				tx_ring = vsi->tx_rings[i];
				अवरोध;
			पूर्ण

	/* Reset recovery level अगर enough समय has elapsed after last समयout.
	 * Also ensure no new reset action happens beक्रमe next समयout period.
	 */
	अगर (समय_after(jअगरfies, (pf->tx_समयout_last_recovery + HZ * 20)))
		pf->tx_समयout_recovery_level = 1;
	अन्यथा अगर (समय_beक्रमe(jअगरfies, (pf->tx_समयout_last_recovery +
				       netdev->watchकरोg_समयo)))
		वापस;

	अगर (tx_ring) अणु
		काष्ठा ice_hw *hw = &pf->hw;
		u32 head, val = 0;

		head = (rd32(hw, QTX_COMM_HEAD(vsi->txq_map[txqueue])) &
			QTX_COMM_HEAD_HEAD_M) >> QTX_COMM_HEAD_HEAD_S;
		/* Read पूर्णांकerrupt रेजिस्टर */
		val = rd32(hw, GLINT_DYN_CTL(tx_ring->q_vector->reg_idx));

		netdev_info(netdev, "tx_timeout: VSI_num: %d, Q %u, NTC: 0x%x, HW_HEAD: 0x%x, NTU: 0x%x, INT: 0x%x\n",
			    vsi->vsi_num, txqueue, tx_ring->next_to_clean,
			    head, tx_ring->next_to_use, val);
	पूर्ण

	pf->tx_समयout_last_recovery = jअगरfies;
	netdev_info(netdev, "tx_timeout recovery level %d, txqueue %u\n",
		    pf->tx_समयout_recovery_level, txqueue);

	चयन (pf->tx_समयout_recovery_level) अणु
	हाल 1:
		set_bit(ICE_PFR_REQ, pf->state);
		अवरोध;
	हाल 2:
		set_bit(ICE_CORER_REQ, pf->state);
		अवरोध;
	हाल 3:
		set_bit(ICE_GLOBR_REQ, pf->state);
		अवरोध;
	शेष:
		netdev_err(netdev, "tx_timeout recovery unsuccessful, device is in unrecoverable state.\n");
		set_bit(ICE_DOWN, pf->state);
		set_bit(ICE_VSI_NEEDS_RESTART, vsi->state);
		set_bit(ICE_SERVICE_DIS, pf->state);
		अवरोध;
	पूर्ण

	ice_service_task_schedule(pf);
	pf->tx_समयout_recovery_level++;
पूर्ण

/**
 * ice_खोलो - Called when a network पूर्णांकerface becomes active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP). At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the netdev watchकरोg is enabled,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 *
 * Returns 0 on success, negative value on failure
 */
पूर्णांक ice_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;

	अगर (ice_is_reset_in_progress(pf->state)) अणु
		netdev_err(netdev, "can't open net device while reset is in progress");
		वापस -EBUSY;
	पूर्ण

	वापस ice_खोलो_पूर्णांकernal(netdev);
पूर्ण

/**
 * ice_खोलो_पूर्णांकernal - Called when a network पूर्णांकerface becomes active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Internal ice_खोलो implementation. Should not be used directly except क्रम ice_खोलो and reset
 * handling routine
 *
 * Returns 0 on success, negative value on failure
 */
पूर्णांक ice_खोलो_पूर्णांकernal(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_port_info *pi;
	क्रमागत ice_status status;
	पूर्णांक err;

	अगर (test_bit(ICE_NEEDS_RESTART, pf->state)) अणु
		netdev_err(netdev, "driver needs to be unloaded and reloaded\n");
		वापस -EIO;
	पूर्ण

	netअगर_carrier_off(netdev);

	pi = vsi->port_info;
	status = ice_update_link_info(pi);
	अगर (status) अणु
		netdev_err(netdev, "Failed to get link info, error %s\n",
			   ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	/* Set PHY अगर there is media, otherwise, turn off PHY */
	अगर (pi->phy.link_info.link_info & ICE_AQ_MEDIA_AVAILABLE) अणु
		clear_bit(ICE_FLAG_NO_MEDIA, pf->flags);
		अगर (!test_bit(ICE_PHY_INIT_COMPLETE, pf->state)) अणु
			err = ice_init_phy_user_cfg(pi);
			अगर (err) अणु
				netdev_err(netdev, "Failed to initialize PHY settings, error %d\n",
					   err);
				वापस err;
			पूर्ण
		पूर्ण

		err = ice_configure_phy(vsi);
		अगर (err) अणु
			netdev_err(netdev, "Failed to set physical link up, error %d\n",
				   err);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(ICE_FLAG_NO_MEDIA, pf->flags);
		ice_set_link(vsi, false);
	पूर्ण

	err = ice_vsi_खोलो(vsi);
	अगर (err)
		netdev_err(netdev, "Failed to open VSI 0x%04X on switch 0x%04X\n",
			   vsi->vsi_num, vsi->vsw->sw_id);

	/* Update existing tunnels inक्रमmation */
	udp_tunnel_get_rx_info(netdev);

	वापस err;
पूर्ण

/**
 * ice_stop - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The stop entry poपूर्णांक is called when an पूर्णांकerface is de-activated by the OS,
 * and the netdevice enters the DOWN state. The hardware is still under the
 * driver's control, but the netdev पूर्णांकerface is disabled.
 *
 * Returns success only - not allowed to fail
 */
पूर्णांक ice_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;

	अगर (ice_is_reset_in_progress(pf->state)) अणु
		netdev_err(netdev, "can't stop net device while reset is in progress");
		वापस -EBUSY;
	पूर्ण

	ice_vsi_बंद(vsi);

	वापस 0;
पूर्ण

/**
 * ice_features_check - Validate encapsulated packet conक्रमms to limits
 * @skb: skb buffer
 * @netdev: This port's netdev
 * @features: Offload features that the stack believes apply
 */
अटल netdev_features_t
ice_features_check(काष्ठा sk_buff *skb,
		   काष्ठा net_device __always_unused *netdev,
		   netdev_features_t features)
अणु
	माप_प्रकार len;

	/* No poपूर्णांक in करोing any of this अगर neither checksum nor GSO are
	 * being requested क्रम this frame. We can rule out both by just
	 * checking क्रम CHECKSUM_PARTIAL
	 */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस features;

	/* We cannot support GSO अगर the MSS is going to be less than
	 * 64 bytes. If it is then we need to drop support क्रम GSO.
	 */
	अगर (skb_is_gso(skb) && (skb_shinfo(skb)->gso_size < 64))
		features &= ~NETIF_F_GSO_MASK;

	len = skb_network_header(skb) - skb->data;
	अगर (len > ICE_TXD_MACLEN_MAX || len & 0x1)
		जाओ out_rm_features;

	len = skb_transport_header(skb) - skb_network_header(skb);
	अगर (len > ICE_TXD_IPLEN_MAX || len & 0x1)
		जाओ out_rm_features;

	अगर (skb->encapsulation) अणु
		len = skb_inner_network_header(skb) - skb_transport_header(skb);
		अगर (len > ICE_TXD_L4LEN_MAX || len & 0x1)
			जाओ out_rm_features;

		len = skb_inner_transport_header(skb) -
		      skb_inner_network_header(skb);
		अगर (len > ICE_TXD_IPLEN_MAX || len & 0x1)
			जाओ out_rm_features;
	पूर्ण

	वापस features;
out_rm_features:
	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ice_netdev_safe_mode_ops = अणु
	.nकरो_खोलो = ice_खोलो,
	.nकरो_stop = ice_stop,
	.nकरो_start_xmit = ice_start_xmit,
	.nकरो_set_mac_address = ice_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_change_mtu = ice_change_mtu,
	.nकरो_get_stats64 = ice_get_stats64,
	.nकरो_tx_समयout = ice_tx_समयout,
	.nकरो_bpf = ice_xdp_safe_mode,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ice_netdev_ops = अणु
	.nकरो_खोलो = ice_खोलो,
	.nकरो_stop = ice_stop,
	.nकरो_start_xmit = ice_start_xmit,
	.nकरो_features_check = ice_features_check,
	.nकरो_set_rx_mode = ice_set_rx_mode,
	.nकरो_set_mac_address = ice_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_change_mtu = ice_change_mtu,
	.nकरो_get_stats64 = ice_get_stats64,
	.nकरो_set_tx_maxrate = ice_set_tx_maxrate,
	.nकरो_set_vf_spoofchk = ice_set_vf_spoofchk,
	.nकरो_set_vf_mac = ice_set_vf_mac,
	.nकरो_get_vf_config = ice_get_vf_cfg,
	.nकरो_set_vf_trust = ice_set_vf_trust,
	.nकरो_set_vf_vlan = ice_set_vf_port_vlan,
	.nकरो_set_vf_link_state = ice_set_vf_link_state,
	.nकरो_get_vf_stats = ice_get_vf_stats,
	.nकरो_vlan_rx_add_vid = ice_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = ice_vlan_rx_समाप्त_vid,
	.nकरो_set_features = ice_set_features,
	.nकरो_bridge_getlink = ice_bridge_getlink,
	.nकरो_bridge_setlink = ice_bridge_setlink,
	.nकरो_fdb_add = ice_fdb_add,
	.nकरो_fdb_del = ice_fdb_del,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer = ice_rx_flow_steer,
#पूर्ण_अगर
	.nकरो_tx_समयout = ice_tx_समयout,
	.nकरो_bpf = ice_xdp,
	.nकरो_xdp_xmit = ice_xdp_xmit,
	.nकरो_xsk_wakeup = ice_xsk_wakeup,
पूर्ण;
