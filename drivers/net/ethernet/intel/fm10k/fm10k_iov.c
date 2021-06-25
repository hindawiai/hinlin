<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश "fm10k.h"
#समावेश "fm10k_vf.h"
#समावेश "fm10k_pf.h"

अटल s32 fm10k_iov_msg_error(काष्ठा fm10k_hw *hw, u32 **results,
			       काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_vf_info *vf_info = (काष्ठा fm10k_vf_info *)mbx;
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = hw->back;
	काष्ठा pci_dev *pdev = पूर्णांकerface->pdev;

	dev_err(&pdev->dev, "Unknown message ID %u on VF %d\n",
		**results & FM10K_TLV_ID_MASK, vf_info->vf_idx);

	वापस fm10k_tlv_msg_error(hw, results, mbx);
पूर्ण

/**
 *  fm10k_iov_msg_queue_mac_vlan - Message handler क्रम MAC/VLAN request from VF
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: Poपूर्णांकer array to message, results[0] is poपूर्णांकer to message
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This function is a custom handler क्रम MAC/VLAN requests from the VF. The
 *  assumption is that it is acceptable to directly hand off the message from
 *  the VF to the PF's चयन manager. However, we use a MAC/VLAN message
 *  queue to aव्योम overloading the mailbox when a large number of requests
 *  come in.
 **/
अटल s32 fm10k_iov_msg_queue_mac_vlan(काष्ठा fm10k_hw *hw, u32 **results,
					काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_vf_info *vf_info = (काष्ठा fm10k_vf_info *)mbx;
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = hw->back;
	u8 mac[ETH_ALEN];
	u32 *result;
	पूर्णांक err = 0;
	bool set;
	u16 vlan;
	u32 vid;

	/* we shouldn't be updating rules on a disabled पूर्णांकerface */
	अगर (!FM10K_VF_FLAG_ENABLED(vf_info))
		err = FM10K_ERR_PARAM;

	अगर (!err && !!results[FM10K_MAC_VLAN_MSG_VLAN]) अणु
		result = results[FM10K_MAC_VLAN_MSG_VLAN];

		/* record VLAN id requested */
		err = fm10k_tlv_attr_get_u32(result, &vid);
		अगर (err)
			वापस err;

		set = !(vid & FM10K_VLAN_CLEAR);
		vid &= ~FM10K_VLAN_CLEAR;

		/* अगर the length field has been set, this is a multi-bit
		 * update request. For multi-bit requests, simply disallow
		 * them when the pf_vid has been set. In this हाल, the PF
		 * should have alपढ़ोy cleared the VLAN_TABLE, and अगर we
		 * allowed them, it could allow a rogue VF to receive traffic
		 * on a VLAN it was not asचिन्हित. In the single-bit हाल, we
		 * need to modअगरy requests क्रम VLAN 0 to use the शेष PF or
		 * SW vid when asचिन्हित.
		 */

		अगर (vid >> 16) अणु
			/* prevent multi-bit requests when PF has
			 * administratively set the VLAN क्रम this VF
			 */
			अगर (vf_info->pf_vid)
				वापस FM10K_ERR_PARAM;
		पूर्ण अन्यथा अणु
			err = fm10k_iov_select_vid(vf_info, (u16)vid);
			अगर (err < 0)
				वापस err;

			vid = err;
		पूर्ण

		/* update VSI info क्रम VF in regards to VLAN table */
		err = hw->mac.ops.update_vlan(hw, vid, vf_info->vsi, set);
	पूर्ण

	अगर (!err && !!results[FM10K_MAC_VLAN_MSG_MAC]) अणु
		result = results[FM10K_MAC_VLAN_MSG_MAC];

		/* record unicast MAC address requested */
		err = fm10k_tlv_attr_get_mac_vlan(result, mac, &vlan);
		अगर (err)
			वापस err;

		/* block attempts to set MAC क्रम a locked device */
		अगर (is_valid_ether_addr(vf_info->mac) &&
		    !ether_addr_equal(mac, vf_info->mac))
			वापस FM10K_ERR_PARAM;

		set = !(vlan & FM10K_VLAN_CLEAR);
		vlan &= ~FM10K_VLAN_CLEAR;

		err = fm10k_iov_select_vid(vf_info, vlan);
		अगर (err < 0)
			वापस err;

		vlan = (u16)err;

		/* Add this request to the MAC/VLAN queue */
		err = fm10k_queue_mac_request(पूर्णांकerface, vf_info->glort,
					      mac, vlan, set);
	पूर्ण

	अगर (!err && !!results[FM10K_MAC_VLAN_MSG_MULTICAST]) अणु
		result = results[FM10K_MAC_VLAN_MSG_MULTICAST];

		/* record multicast MAC address requested */
		err = fm10k_tlv_attr_get_mac_vlan(result, mac, &vlan);
		अगर (err)
			वापस err;

		/* verअगरy that the VF is allowed to request multicast */
		अगर (!(vf_info->vf_flags & FM10K_VF_FLAG_MULTI_ENABLED))
			वापस FM10K_ERR_PARAM;

		set = !(vlan & FM10K_VLAN_CLEAR);
		vlan &= ~FM10K_VLAN_CLEAR;

		err = fm10k_iov_select_vid(vf_info, vlan);
		अगर (err < 0)
			वापस err;

		vlan = (u16)err;

		/* Add this request to the MAC/VLAN queue */
		err = fm10k_queue_mac_request(पूर्णांकerface, vf_info->glort,
					      mac, vlan, set);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा fm10k_msg_data iov_mbx_data[] = अणु
	FM10K_TLV_MSG_TEST_HANDLER(fm10k_tlv_msg_test),
	FM10K_VF_MSG_MSIX_HANDLER(fm10k_iov_msg_msix_pf),
	FM10K_VF_MSG_MAC_VLAN_HANDLER(fm10k_iov_msg_queue_mac_vlan),
	FM10K_VF_MSG_LPORT_STATE_HANDLER(fm10k_iov_msg_lport_state_pf),
	FM10K_TLV_MSG_ERROR_HANDLER(fm10k_iov_msg_error),
पूर्ण;

s32 fm10k_iov_event(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_iov_data *iov_data;
	s64 vflre;
	पूर्णांक i;

	/* अगर there is no iov_data then there is no mailbox to process */
	अगर (!READ_ONCE(पूर्णांकerface->iov_data))
		वापस 0;

	rcu_पढ़ो_lock();

	iov_data = पूर्णांकerface->iov_data;

	/* check again now that we are in the RCU block */
	अगर (!iov_data)
		जाओ पढ़ो_unlock;

	अगर (!(fm10k_पढ़ो_reg(hw, FM10K_EICR) & FM10K_EICR_VFLR))
		जाओ पढ़ो_unlock;

	/* पढ़ो VFLRE to determine अगर any VFs have been reset */
	vflre = fm10k_पढ़ो_reg(hw, FM10K_PFVFLRE(1));
	vflre <<= 32;
	vflre |= fm10k_पढ़ो_reg(hw, FM10K_PFVFLRE(0));

	i = iov_data->num_vfs;

	क्रम (vflre <<= 64 - i; vflre && i--; vflre += vflre) अणु
		काष्ठा fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		अगर (vflre >= 0)
			जारी;

		hw->iov.ops.reset_resources(hw, vf_info);
		vf_info->mbx.ops.connect(hw, &vf_info->mbx);
	पूर्ण

पढ़ो_unlock:
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

s32 fm10k_iov_mbx(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_iov_data *iov_data;
	पूर्णांक i;

	/* अगर there is no iov_data then there is no mailbox to process */
	अगर (!READ_ONCE(पूर्णांकerface->iov_data))
		वापस 0;

	rcu_पढ़ो_lock();

	iov_data = पूर्णांकerface->iov_data;

	/* check again now that we are in the RCU block */
	अगर (!iov_data)
		जाओ पढ़ो_unlock;

	/* lock the mailbox क्रम transmit and receive */
	fm10k_mbx_lock(पूर्णांकerface);

	/* Most VF messages sent to the PF cause the PF to respond by
	 * requesting from the SM mailbox. This means that too many VF
	 * messages processed at once could cause a mailbox समयout on the PF.
	 * To prevent this, store a poपूर्णांकer to the next VF mbx to process. Use
	 * that as the start of the loop so that we करोn't starve whichever VF
	 * got ignored on the previous run.
	 */
process_mbx:
	क्रम (i = iov_data->next_vf_mbx ? : iov_data->num_vfs; i--;) अणु
		काष्ठा fm10k_vf_info *vf_info = &iov_data->vf_info[i];
		काष्ठा fm10k_mbx_info *mbx = &vf_info->mbx;
		u16 glort = vf_info->glort;

		/* process the SM mailbox first to drain outgoing messages */
		hw->mbx.ops.process(hw, &hw->mbx);

		/* verअगरy port mapping is valid, अगर not reset port */
		अगर (vf_info->vf_flags && !fm10k_glort_valid_pf(hw, glort)) अणु
			hw->iov.ops.reset_lport(hw, vf_info);
			fm10k_clear_macvlan_queue(पूर्णांकerface, glort, false);
		पूर्ण

		/* reset VFs that have mailbox समयd out */
		अगर (!mbx->समयout) अणु
			hw->iov.ops.reset_resources(hw, vf_info);
			mbx->ops.connect(hw, mbx);
		पूर्ण

		/* guarantee we have मुक्त space in the SM mailbox */
		अगर (hw->mbx.state == FM10K_STATE_OPEN &&
		    !hw->mbx.ops.tx_पढ़ोy(&hw->mbx, FM10K_VFMBX_MSG_MTU)) अणु
			/* keep track of how many बार this occurs */
			पूर्णांकerface->hw_sm_mbx_full++;

			/* make sure we try again momentarily */
			fm10k_service_event_schedule(पूर्णांकerface);

			अवरोध;
		पूर्ण

		/* cleanup mailbox and process received messages */
		mbx->ops.process(hw, mbx);
	पूर्ण

	/* अगर we stopped processing mailboxes early, update next_vf_mbx.
	 * Otherwise, reset next_vf_mbx, and restart loop so that we process
	 * the reमुख्यing mailboxes we skipped at the start.
	 */
	अगर (i >= 0) अणु
		iov_data->next_vf_mbx = i + 1;
	पूर्ण अन्यथा अगर (iov_data->next_vf_mbx) अणु
		iov_data->next_vf_mbx = 0;
		जाओ process_mbx;
	पूर्ण

	/* मुक्त the lock */
	fm10k_mbx_unlock(पूर्णांकerface);

पढ़ो_unlock:
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

व्योम fm10k_iov_suspend(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक num_vfs, i;

	/* pull out num_vfs from iov_data */
	num_vfs = iov_data ? iov_data->num_vfs : 0;

	/* shut करोwn queue mapping क्रम VFs */
	fm10k_ग_लिखो_reg(hw, FM10K_DGLORTMAP(fm10k_dglort_vf_rss),
			FM10K_DGLORTMAP_NONE);

	/* Stop any active VFs and reset their resources */
	क्रम (i = 0; i < num_vfs; i++) अणु
		काष्ठा fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		hw->iov.ops.reset_resources(hw, vf_info);
		hw->iov.ops.reset_lport(hw, vf_info);
		fm10k_clear_macvlan_queue(पूर्णांकerface, vf_info->glort, false);
	पूर्ण
पूर्ण

अटल व्योम fm10k_mask_aer_comp_पात(काष्ठा pci_dev *pdev)
अणु
	u32 err_mask;
	पूर्णांक pos;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ERR);
	अगर (!pos)
		वापस;

	/* Mask the completion पात bit in the ERR_UNCOR_MASK रेजिस्टर,
	 * preventing the device from reporting these errors to the upstream
	 * PCIe root device. This aव्योमs bringing करोwn platक्रमms which upgrade
	 * non-fatal completer पातs पूर्णांकo machine check exceptions. Completer
	 * पातs can occur whenever a VF पढ़ोs a queue it करोesn't own.
	 */
	pci_पढ़ो_config_dword(pdev, pos + PCI_ERR_UNCOR_MASK, &err_mask);
	err_mask |= PCI_ERR_UNC_COMP_ABORT;
	pci_ग_लिखो_config_dword(pdev, pos + PCI_ERR_UNCOR_MASK, err_mask);
पूर्ण

पूर्णांक fm10k_iov_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_dglort_cfg dglort = अणु 0 पूर्ण;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक num_vfs, i;

	/* pull out num_vfs from iov_data */
	num_vfs = iov_data ? iov_data->num_vfs : 0;

	/* वापस error अगर iov_data is not alपढ़ोy populated */
	अगर (!iov_data)
		वापस -ENOMEM;

	/* Lower severity of completer पात error reporting as
	 * the VFs can trigger this any समय they पढ़ो a queue
	 * that they करोn't own.
	 */
	fm10k_mask_aer_comp_पात(pdev);

	/* allocate hardware resources क्रम the VFs */
	hw->iov.ops.assign_resources(hw, num_vfs, num_vfs);

	/* configure DGLORT mapping क्रम RSS */
	dglort.glort = hw->mac.dglort_map & FM10K_DGLORTMAP_NONE;
	dglort.idx = fm10k_dglort_vf_rss;
	dglort.inner_rss = 1;
	dglort.rss_l = fls(fm10k_queues_per_pool(hw) - 1);
	dglort.queue_b = fm10k_vf_queue_index(hw, 0);
	dglort.vsi_l = fls(hw->iov.total_vfs - 1);
	dglort.vsi_b = 1;

	hw->mac.ops.configure_dglort_map(hw, &dglort);

	/* assign resources to the device */
	क्रम (i = 0; i < num_vfs; i++) अणु
		काष्ठा fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		/* allocate all but the last GLORT to the VFs */
		अगर (i == (~hw->mac.dglort_map >> FM10K_DGLORTMAP_MASK_SHIFT))
			अवरोध;

		/* assign GLORT to VF, and restrict it to multicast */
		hw->iov.ops.set_lport(hw, vf_info, i,
				      FM10K_VF_FLAG_MULTI_CAPABLE);

		/* mailbox is disconnected so we करोn't send a message */
		hw->iov.ops.assign_शेष_mac_vlan(hw, vf_info);

		/* now we are पढ़ोy so we can connect */
		vf_info->mbx.ops.connect(hw, &vf_info->mbx);
	पूर्ण

	वापस 0;
पूर्ण

s32 fm10k_iov_update_pvid(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u16 glort, u16 pvid)
अणु
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_vf_info *vf_info;
	u16 vf_idx = (glort - hw->mac.dglort_map) & FM10K_DGLORTMAP_NONE;

	/* no IOV support, not our message to process */
	अगर (!iov_data)
		वापस FM10K_ERR_PARAM;

	/* glort outside our range, not our message to process */
	अगर (vf_idx >= iov_data->num_vfs)
		वापस FM10K_ERR_PARAM;

	/* determine अगर an update has occurred and अगर so notअगरy the VF */
	vf_info = &iov_data->vf_info[vf_idx];
	अगर (vf_info->sw_vid != pvid) अणु
		vf_info->sw_vid = pvid;
		hw->iov.ops.assign_शेष_mac_vlan(hw, vf_info);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fm10k_iov_मुक्त_data(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);

	अगर (!पूर्णांकerface->iov_data)
		वापस;

	/* reclaim hardware resources */
	fm10k_iov_suspend(pdev);

	/* drop iov_data from पूर्णांकerface */
	kमुक्त_rcu(पूर्णांकerface->iov_data, rcu);
	पूर्णांकerface->iov_data = शून्य;
पूर्ण

अटल s32 fm10k_iov_alloc_data(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	माप_प्रकार size;
	पूर्णांक i;

	/* वापस error अगर iov_data is alपढ़ोy populated */
	अगर (iov_data)
		वापस -EBUSY;

	/* The PF should always be able to assign resources */
	अगर (!hw->iov.ops.assign_resources)
		वापस -ENODEV;

	/* nothing to करो अगर no VFs are requested */
	अगर (!num_vfs)
		वापस 0;

	/* allocate memory क्रम VF storage */
	size = दुरत्व(काष्ठा fm10k_iov_data, vf_info[num_vfs]);
	iov_data = kzalloc(size, GFP_KERNEL);
	अगर (!iov_data)
		वापस -ENOMEM;

	/* record number of VFs */
	iov_data->num_vfs = num_vfs;

	/* loop through vf_info काष्ठाures initializing each entry */
	क्रम (i = 0; i < num_vfs; i++) अणु
		काष्ठा fm10k_vf_info *vf_info = &iov_data->vf_info[i];
		पूर्णांक err;

		/* Record VF VSI value */
		vf_info->vsi = i + 1;
		vf_info->vf_idx = i;

		/* initialize mailbox memory */
		err = fm10k_pfvf_mbx_init(hw, &vf_info->mbx, iov_mbx_data, i);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Unable to initialize SR-IOV mailbox\n");
			kमुक्त(iov_data);
			वापस err;
		पूर्ण
	पूर्ण

	/* assign iov_data to पूर्णांकerface */
	पूर्णांकerface->iov_data = iov_data;

	/* allocate hardware resources क्रम the VFs */
	fm10k_iov_resume(pdev);

	वापस 0;
पूर्ण

व्योम fm10k_iov_disable(काष्ठा pci_dev *pdev)
अणु
	अगर (pci_num_vf(pdev) && pci_vfs_asचिन्हित(pdev))
		dev_err(&pdev->dev,
			"Cannot disable SR-IOV while VFs are assigned\n");
	अन्यथा
		pci_disable_sriov(pdev);

	fm10k_iov_मुक्त_data(pdev);
पूर्ण

पूर्णांक fm10k_iov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	पूर्णांक current_vfs = pci_num_vf(pdev);
	पूर्णांक err = 0;

	अगर (current_vfs && pci_vfs_asचिन्हित(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot modify SR-IOV while VFs are assigned\n");
		num_vfs = current_vfs;
	पूर्ण अन्यथा अणु
		pci_disable_sriov(pdev);
		fm10k_iov_मुक्त_data(pdev);
	पूर्ण

	/* allocate resources क्रम the VFs */
	err = fm10k_iov_alloc_data(pdev, num_vfs);
	अगर (err)
		वापस err;

	/* allocate VFs अगर not alपढ़ोy allocated */
	अगर (num_vfs && num_vfs != current_vfs) अणु
		err = pci_enable_sriov(pdev, num_vfs);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Enable PCI SR-IOV failed: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस num_vfs;
पूर्ण

/**
 * fm10k_iov_update_stats - Update stats क्रम all VFs
 * @पूर्णांकerface: device निजी काष्ठाure
 *
 * Updates the VF statistics क्रम all enabled VFs. Expects to be called by
 * fm10k_update_stats and assumes that locking via the __FM10K_UPDATING_STATS
 * bit is alपढ़ोy handled.
 */
व्योम fm10k_iov_update_stats(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक i;

	अगर (!iov_data)
		वापस;

	क्रम (i = 0; i < iov_data->num_vfs; i++)
		hw->iov.ops.update_stats(hw, iov_data->vf_info[i].stats, i);
पूर्ण

अटल अंतरभूत व्योम fm10k_reset_vf_info(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				       काष्ठा fm10k_vf_info *vf_info)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	/* assigning the MAC address will send a mailbox message */
	fm10k_mbx_lock(पूर्णांकerface);

	/* disable LPORT क्रम this VF which clears चयन rules */
	hw->iov.ops.reset_lport(hw, vf_info);

	fm10k_clear_macvlan_queue(पूर्णांकerface, vf_info->glort, false);

	/* assign new MAC+VLAN क्रम this VF */
	hw->iov.ops.assign_शेष_mac_vlan(hw, vf_info);

	/* re-enable the LPORT क्रम this VF */
	hw->iov.ops.set_lport(hw, vf_info, vf_info->vf_idx,
			      FM10K_VF_FLAG_MULTI_CAPABLE);

	fm10k_mbx_unlock(पूर्णांकerface);
पूर्ण

पूर्णांक fm10k_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf_idx, u8 *mac)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_vf_info *vf_info;

	/* verअगरy SR-IOV is active and that vf idx is valid */
	अगर (!iov_data || vf_idx >= iov_data->num_vfs)
		वापस -EINVAL;

	/* verअगरy MAC addr is valid */
	अगर (!is_zero_ether_addr(mac) && !is_valid_ether_addr(mac))
		वापस -EINVAL;

	/* record new MAC address */
	vf_info = &iov_data->vf_info[vf_idx];
	ether_addr_copy(vf_info->mac, mac);

	fm10k_reset_vf_info(पूर्णांकerface, vf_info);

	वापस 0;
पूर्ण

पूर्णांक fm10k_nकरो_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf_idx, u16 vid,
			  u8 qos, __be16 vlan_proto)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_vf_info *vf_info;

	/* verअगरy SR-IOV is active and that vf idx is valid */
	अगर (!iov_data || vf_idx >= iov_data->num_vfs)
		वापस -EINVAL;

	/* QOS is unsupported and VLAN IDs accepted range 0-4094 */
	अगर (qos || (vid > (VLAN_VID_MASK - 1)))
		वापस -EINVAL;

	/* VF VLAN Protocol part to शेष is unsupported */
	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	vf_info = &iov_data->vf_info[vf_idx];

	/* निकास अगर there is nothing to करो */
	अगर (vf_info->pf_vid == vid)
		वापस 0;

	/* record शेष VLAN ID क्रम VF */
	vf_info->pf_vid = vid;

	/* Clear the VLAN table क्रम the VF */
	hw->mac.ops.update_vlan(hw, FM10K_VLAN_ALL, vf_info->vsi, false);

	fm10k_reset_vf_info(पूर्णांकerface, vf_info);

	वापस 0;
पूर्ण

पूर्णांक fm10k_nकरो_set_vf_bw(काष्ठा net_device *netdev, पूर्णांक vf_idx,
			पूर्णांक __always_unused min_rate, पूर्णांक max_rate)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	/* verअगरy SR-IOV is active and that vf idx is valid */
	अगर (!iov_data || vf_idx >= iov_data->num_vfs)
		वापस -EINVAL;

	/* rate limit cannot be less than 10Mbs or greater than link speed */
	अगर (max_rate &&
	    (max_rate < FM10K_VF_TC_MIN || max_rate > FM10K_VF_TC_MAX))
		वापस -EINVAL;

	/* store values */
	iov_data->vf_info[vf_idx].rate = max_rate;

	/* update hardware configuration */
	hw->iov.ops.configure_tc(hw, vf_idx, max_rate);

	वापस 0;
पूर्ण

पूर्णांक fm10k_nकरो_get_vf_config(काष्ठा net_device *netdev,
			    पूर्णांक vf_idx, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_vf_info *vf_info;

	/* verअगरy SR-IOV is active and that vf idx is valid */
	अगर (!iov_data || vf_idx >= iov_data->num_vfs)
		वापस -EINVAL;

	vf_info = &iov_data->vf_info[vf_idx];

	ivi->vf = vf_idx;
	ivi->max_tx_rate = vf_info->rate;
	ivi->min_tx_rate = 0;
	ether_addr_copy(ivi->mac, vf_info->mac);
	ivi->vlan = vf_info->pf_vid;
	ivi->qos = 0;

	वापस 0;
पूर्ण

पूर्णांक fm10k_nकरो_get_vf_stats(काष्ठा net_device *netdev,
			   पूर्णांक vf_idx, काष्ठा अगरla_vf_stats *stats)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_hw_stats_q *hw_stats;
	u32 idx, qpp;

	/* verअगरy SR-IOV is active and that vf idx is valid */
	अगर (!iov_data || vf_idx >= iov_data->num_vfs)
		वापस -EINVAL;

	qpp = fm10k_queues_per_pool(hw);
	hw_stats = iov_data->vf_info[vf_idx].stats;

	क्रम (idx = 0; idx < qpp; idx++) अणु
		stats->rx_packets += hw_stats[idx].rx_packets.count;
		stats->tx_packets += hw_stats[idx].tx_packets.count;
		stats->rx_bytes += hw_stats[idx].rx_bytes.count;
		stats->tx_bytes += hw_stats[idx].tx_bytes.count;
		stats->rx_dropped += hw_stats[idx].rx_drops.count;
	पूर्ण

	वापस 0;
पूर्ण
