<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/of_net.h>
#समावेश <linux/pci.h>
#समावेश <linux/bpf.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/crash_dump.h>

/* Local includes */
#समावेश "i40e.h"
#समावेश "i40e_diag.h"
#समावेश "i40e_xsk.h"
#समावेश <net/udp_tunnel.h>
#समावेश <net/xdp_sock_drv.h>
/* All i40e tracepoपूर्णांकs are defined by the include below, which
 * must be included exactly once across the whole kernel with
 * CREATE_TRACE_POINTS defined
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "i40e_trace.h"

स्थिर अक्षर i40e_driver_name[] = "i40e";
अटल स्थिर अक्षर i40e_driver_string[] =
			"Intel(R) Ethernet Connection XL710 Network Driver";

अटल स्थिर अक्षर i40e_copyright[] = "Copyright (c) 2013 - 2019 Intel Corporation.";

/* a bit of क्रमward declarations */
अटल व्योम i40e_vsi_reinit_locked(काष्ठा i40e_vsi *vsi);
अटल व्योम i40e_handle_reset_warning(काष्ठा i40e_pf *pf, bool lock_acquired);
अटल पूर्णांक i40e_add_vsi(काष्ठा i40e_vsi *vsi);
अटल पूर्णांक i40e_add_veb(काष्ठा i40e_veb *veb, काष्ठा i40e_vsi *vsi);
अटल पूर्णांक i40e_setup_pf_चयन(काष्ठा i40e_pf *pf, bool reinit);
अटल पूर्णांक i40e_setup_misc_vector(काष्ठा i40e_pf *pf);
अटल व्योम i40e_determine_queue_usage(काष्ठा i40e_pf *pf);
अटल पूर्णांक i40e_setup_pf_filter_control(काष्ठा i40e_pf *pf);
अटल व्योम i40e_prep_क्रम_reset(काष्ठा i40e_pf *pf);
अटल व्योम i40e_reset_and_rebuild(काष्ठा i40e_pf *pf, bool reinit,
				   bool lock_acquired);
अटल पूर्णांक i40e_reset(काष्ठा i40e_pf *pf);
अटल व्योम i40e_rebuild(काष्ठा i40e_pf *pf, bool reinit, bool lock_acquired);
अटल पूर्णांक i40e_setup_misc_vector_क्रम_recovery_mode(काष्ठा i40e_pf *pf);
अटल पूर्णांक i40e_restore_पूर्णांकerrupt_scheme(काष्ठा i40e_pf *pf);
अटल bool i40e_check_recovery_mode(काष्ठा i40e_pf *pf);
अटल पूर्णांक i40e_init_recovery_mode(काष्ठा i40e_pf *pf, काष्ठा i40e_hw *hw);
अटल व्योम i40e_fdir_sb_setup(काष्ठा i40e_pf *pf);
अटल पूर्णांक i40e_veb_get_bw_info(काष्ठा i40e_veb *veb);
अटल पूर्णांक i40e_get_capabilities(काष्ठा i40e_pf *pf,
				 क्रमागत i40e_admin_queue_opc list_type);
अटल bool i40e_is_total_port_shutकरोwn_enabled(काष्ठा i40e_pf *pf);

/* i40e_pci_tbl - PCI Device ID Table
 *
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id i40e_pci_tbl[] = अणु
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_SFP_XL710), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_QEMU), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_KX_B), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_KX_C), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_QSFP_A), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_QSFP_B), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_QSFP_C), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_10G_BASE_T), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_10G_BASE_T4), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_10G_BASE_T_BC), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_10G_SFP), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_10G_B), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_KX_X722), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_QSFP_X722), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_SFP_X722), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_1G_BASE_T_X722), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_10G_BASE_T_X722), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_SFP_I_X722), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_20G_KR2), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_20G_KR2_A), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_X710_N3000), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_XXV710_N3000), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_25G_B), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, I40E_DEV_ID_25G_SFP28), 0पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, i40e_pci_tbl);

#घोषणा I40E_MAX_VF_COUNT 128
अटल पूर्णांक debug = -1;
module_param(debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all), Debug mask (0x8XXXXXXX)");

MODULE_AUTHOR("Intel Corporation, <e1000-devel@lists.sourceforge.net>");
MODULE_DESCRIPTION("Intel(R) Ethernet Connection XL710 Network Driver");
MODULE_LICENSE("GPL v2");

अटल काष्ठा workqueue_काष्ठा *i40e_wq;

/**
 * i40e_allocate_dma_mem_d - OS specअगरic memory alloc क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to fill out
 * @size: size of memory requested
 * @alignment: what to align the allocation to
 **/
पूर्णांक i40e_allocate_dma_mem_d(काष्ठा i40e_hw *hw, काष्ठा i40e_dma_mem *mem,
			    u64 size, u32 alignment)
अणु
	काष्ठा i40e_pf *pf = (काष्ठा i40e_pf *)hw->back;

	mem->size = ALIGN(size, alignment);
	mem->va = dma_alloc_coherent(&pf->pdev->dev, mem->size, &mem->pa,
				     GFP_KERNEL);
	अगर (!mem->va)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * i40e_मुक्त_dma_mem_d - OS specअगरic memory मुक्त क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to मुक्त
 **/
पूर्णांक i40e_मुक्त_dma_mem_d(काष्ठा i40e_hw *hw, काष्ठा i40e_dma_mem *mem)
अणु
	काष्ठा i40e_pf *pf = (काष्ठा i40e_pf *)hw->back;

	dma_मुक्त_coherent(&pf->pdev->dev, mem->size, mem->va, mem->pa);
	mem->va = शून्य;
	mem->pa = 0;
	mem->size = 0;

	वापस 0;
पूर्ण

/**
 * i40e_allocate_virt_mem_d - OS specअगरic memory alloc क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to fill out
 * @size: size of memory requested
 **/
पूर्णांक i40e_allocate_virt_mem_d(काष्ठा i40e_hw *hw, काष्ठा i40e_virt_mem *mem,
			     u32 size)
अणु
	mem->size = size;
	mem->va = kzalloc(size, GFP_KERNEL);

	अगर (!mem->va)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * i40e_मुक्त_virt_mem_d - OS specअगरic memory मुक्त क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to मुक्त
 **/
पूर्णांक i40e_मुक्त_virt_mem_d(काष्ठा i40e_hw *hw, काष्ठा i40e_virt_mem *mem)
अणु
	/* it's ok to kमुक्त a शून्य poपूर्णांकer */
	kमुक्त(mem->va);
	mem->va = शून्य;
	mem->size = 0;

	वापस 0;
पूर्ण

/**
 * i40e_get_lump - find a lump of मुक्त generic resource
 * @pf: board निजी काष्ठाure
 * @pile: the pile of resource to search
 * @needed: the number of items needed
 * @id: an owner id to stick on the items asचिन्हित
 *
 * Returns the base item index of the lump, or negative क्रम error
 *
 * The search_hपूर्णांक trick and lack of advanced fit-finding only work
 * because we're highly likely to have all the same size lump requests.
 * Linear search समय and any fragmentation should be minimal.
 **/
अटल पूर्णांक i40e_get_lump(काष्ठा i40e_pf *pf, काष्ठा i40e_lump_tracking *pile,
			 u16 needed, u16 id)
अणु
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i, j;

	अगर (!pile || needed == 0 || id >= I40E_PILE_VALID_BIT) अणु
		dev_info(&pf->pdev->dev,
			 "param err: pile=%s needed=%d id=0x%04x\n",
			 pile ? "<valid>" : "<null>", needed, id);
		वापस -EINVAL;
	पूर्ण

	/* start the linear search with an imperfect hपूर्णांक */
	i = pile->search_hपूर्णांक;
	जबतक (i < pile->num_entries) अणु
		/* skip alपढ़ोy allocated entries */
		अगर (pile->list[i] & I40E_PILE_VALID_BIT) अणु
			i++;
			जारी;
		पूर्ण

		/* करो we have enough in this lump? */
		क्रम (j = 0; (j < needed) && ((i+j) < pile->num_entries); j++) अणु
			अगर (pile->list[i+j] & I40E_PILE_VALID_BIT)
				अवरोध;
		पूर्ण

		अगर (j == needed) अणु
			/* there was enough, so assign it to the requestor */
			क्रम (j = 0; j < needed; j++)
				pile->list[i+j] = id | I40E_PILE_VALID_BIT;
			ret = i;
			pile->search_hपूर्णांक = i + j;
			अवरोध;
		पूर्ण

		/* not enough, so skip over it and जारी looking */
		i += j;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_put_lump - वापस a lump of generic resource
 * @pile: the pile of resource to search
 * @index: the base item index
 * @id: the owner id of the items asचिन्हित
 *
 * Returns the count of items in the lump
 **/
अटल पूर्णांक i40e_put_lump(काष्ठा i40e_lump_tracking *pile, u16 index, u16 id)
अणु
	पूर्णांक valid_id = (id | I40E_PILE_VALID_BIT);
	पूर्णांक count = 0;
	पूर्णांक i;

	अगर (!pile || index >= pile->num_entries)
		वापस -EINVAL;

	क्रम (i = index;
	     i < pile->num_entries && pile->list[i] == valid_id;
	     i++) अणु
		pile->list[i] = 0;
		count++;
	पूर्ण

	अगर (count && index < pile->search_hपूर्णांक)
		pile->search_hपूर्णांक = index;

	वापस count;
पूर्ण

/**
 * i40e_find_vsi_from_id - searches क्रम the vsi with the given id
 * @pf: the pf काष्ठाure to search क्रम the vsi
 * @id: id of the vsi it is searching क्रम
 **/
काष्ठा i40e_vsi *i40e_find_vsi_from_id(काष्ठा i40e_pf *pf, u16 id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pf->num_alloc_vsi; i++)
		अगर (pf->vsi[i] && (pf->vsi[i]->id == id))
			वापस pf->vsi[i];

	वापस शून्य;
पूर्ण

/**
 * i40e_service_event_schedule - Schedule the service task to wake up
 * @pf: board निजी काष्ठाure
 *
 * If not alपढ़ोy scheduled, this माला_दो the task पूर्णांकo the work queue
 **/
व्योम i40e_service_event_schedule(काष्ठा i40e_pf *pf)
अणु
	अगर ((!test_bit(__I40E_DOWN, pf->state) &&
	     !test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state)) ||
	      test_bit(__I40E_RECOVERY_MODE, pf->state))
		queue_work(i40e_wq, &pf->service_task);
पूर्ण

/**
 * i40e_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: queue number timing out
 *
 * If any port has noticed a Tx समयout, it is likely that the whole
 * device is munged, not just the one netdev port, so go क्रम the full
 * reset.
 **/
अटल व्योम i40e_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_ring *tx_ring = शून्य;
	अचिन्हित पूर्णांक i;
	u32 head, val;

	pf->tx_समयout_count++;

	/* with txqueue index, find the tx_ring काष्ठा */
	क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
		अगर (vsi->tx_rings[i] && vsi->tx_rings[i]->desc) अणु
			अगर (txqueue ==
			    vsi->tx_rings[i]->queue_index) अणु
				tx_ring = vsi->tx_rings[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (समय_after(jअगरfies, (pf->tx_समयout_last_recovery + HZ*20)))
		pf->tx_समयout_recovery_level = 1;  /* reset after some समय */
	अन्यथा अगर (समय_beक्रमe(jअगरfies,
		      (pf->tx_समयout_last_recovery + netdev->watchकरोg_समयo)))
		वापस;   /* करोn't करो any new action beक्रमe the next समयout */

	/* करोn't kick off another recovery अगर one is alपढ़ोy pending */
	अगर (test_and_set_bit(__I40E_TIMEOUT_RECOVERY_PENDING, pf->state))
		वापस;

	अगर (tx_ring) अणु
		head = i40e_get_head(tx_ring);
		/* Read पूर्णांकerrupt रेजिस्टर */
		अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
			val = rd32(&pf->hw,
			     I40E_PFINT_DYN_CTLN(tx_ring->q_vector->v_idx +
						tx_ring->vsi->base_vector - 1));
		अन्यथा
			val = rd32(&pf->hw, I40E_PFINT_DYN_CTL0);

		netdev_info(netdev, "tx_timeout: VSI_seid: %d, Q %d, NTC: 0x%x, HWB: 0x%x, NTU: 0x%x, TAIL: 0x%x, INT: 0x%x\n",
			    vsi->seid, txqueue, tx_ring->next_to_clean,
			    head, tx_ring->next_to_use,
			    पढ़ोl(tx_ring->tail), val);
	पूर्ण

	pf->tx_समयout_last_recovery = jअगरfies;
	netdev_info(netdev, "tx_timeout recovery level %d, txqueue %d\n",
		    pf->tx_समयout_recovery_level, txqueue);

	चयन (pf->tx_समयout_recovery_level) अणु
	हाल 1:
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		अवरोध;
	हाल 2:
		set_bit(__I40E_CORE_RESET_REQUESTED, pf->state);
		अवरोध;
	हाल 3:
		set_bit(__I40E_GLOBAL_RESET_REQUESTED, pf->state);
		अवरोध;
	शेष:
		netdev_err(netdev, "tx_timeout recovery unsuccessful\n");
		अवरोध;
	पूर्ण

	i40e_service_event_schedule(pf);
	pf->tx_समयout_recovery_level++;
पूर्ण

/**
 * i40e_get_vsi_stats_काष्ठा - Get System Network Statistics
 * @vsi: the VSI we care about
 *
 * Returns the address of the device statistics काष्ठाure.
 * The statistics are actually updated from the service task.
 **/
काष्ठा rtnl_link_stats64 *i40e_get_vsi_stats_काष्ठा(काष्ठा i40e_vsi *vsi)
अणु
	वापस &vsi->net_stats;
पूर्ण

/**
 * i40e_get_netdev_stats_काष्ठा_tx - populate stats from a Tx ring
 * @ring: Tx ring to get statistics from
 * @stats: statistics entry to be updated
 **/
अटल व्योम i40e_get_netdev_stats_काष्ठा_tx(काष्ठा i40e_ring *ring,
					    काष्ठा rtnl_link_stats64 *stats)
अणु
	u64 bytes, packets;
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin_irq(&ring->syncp);
		packets = ring->stats.packets;
		bytes   = ring->stats.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));

	stats->tx_packets += packets;
	stats->tx_bytes   += bytes;
पूर्ण

/**
 * i40e_get_netdev_stats_काष्ठा - Get statistics क्रम netdev पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @stats: data काष्ठाure to store statistics
 *
 * Returns the address of the device statistics काष्ठाure.
 * The statistics are actually updated from the service task.
 **/
अटल व्योम i40e_get_netdev_stats_काष्ठा(काष्ठा net_device *netdev,
				  काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा rtnl_link_stats64 *vsi_stats = i40e_get_vsi_stats_काष्ठा(vsi);
	काष्ठा i40e_ring *ring;
	पूर्णांक i;

	अगर (test_bit(__I40E_VSI_DOWN, vsi->state))
		वापस;

	अगर (!vsi->tx_rings)
		वापस;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
		u64 bytes, packets;
		अचिन्हित पूर्णांक start;

		ring = READ_ONCE(vsi->tx_rings[i]);
		अगर (!ring)
			जारी;
		i40e_get_netdev_stats_काष्ठा_tx(ring, stats);

		अगर (i40e_enabled_xdp_vsi(vsi)) अणु
			ring = READ_ONCE(vsi->xdp_rings[i]);
			अगर (!ring)
				जारी;
			i40e_get_netdev_stats_काष्ठा_tx(ring, stats);
		पूर्ण

		ring = READ_ONCE(vsi->rx_rings[i]);
		अगर (!ring)
			जारी;
		करो अणु
			start   = u64_stats_fetch_begin_irq(&ring->syncp);
			packets = ring->stats.packets;
			bytes   = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));

		stats->rx_packets += packets;
		stats->rx_bytes   += bytes;

	पूर्ण
	rcu_पढ़ो_unlock();

	/* following stats updated by i40e_watchकरोg_subtask() */
	stats->multicast	= vsi_stats->multicast;
	stats->tx_errors	= vsi_stats->tx_errors;
	stats->tx_dropped	= vsi_stats->tx_dropped;
	stats->rx_errors	= vsi_stats->rx_errors;
	stats->rx_dropped	= vsi_stats->rx_dropped;
	stats->rx_crc_errors	= vsi_stats->rx_crc_errors;
	stats->rx_length_errors	= vsi_stats->rx_length_errors;
पूर्ण

/**
 * i40e_vsi_reset_stats - Resets all stats of the given vsi
 * @vsi: the VSI to have its stats reset
 **/
व्योम i40e_vsi_reset_stats(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा rtnl_link_stats64 *ns;
	पूर्णांक i;

	अगर (!vsi)
		वापस;

	ns = i40e_get_vsi_stats_काष्ठा(vsi);
	स_रखो(ns, 0, माप(*ns));
	स_रखो(&vsi->net_stats_offsets, 0, माप(vsi->net_stats_offsets));
	स_रखो(&vsi->eth_stats, 0, माप(vsi->eth_stats));
	स_रखो(&vsi->eth_stats_offsets, 0, माप(vsi->eth_stats_offsets));
	अगर (vsi->rx_rings && vsi->rx_rings[0]) अणु
		क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
			स_रखो(&vsi->rx_rings[i]->stats, 0,
			       माप(vsi->rx_rings[i]->stats));
			स_रखो(&vsi->rx_rings[i]->rx_stats, 0,
			       माप(vsi->rx_rings[i]->rx_stats));
			स_रखो(&vsi->tx_rings[i]->stats, 0,
			       माप(vsi->tx_rings[i]->stats));
			स_रखो(&vsi->tx_rings[i]->tx_stats, 0,
			       माप(vsi->tx_rings[i]->tx_stats));
		पूर्ण
	पूर्ण
	vsi->stat_offsets_loaded = false;
पूर्ण

/**
 * i40e_pf_reset_stats - Reset all of the stats क्रम the given PF
 * @pf: the PF to be reset
 **/
व्योम i40e_pf_reset_stats(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक i;

	स_रखो(&pf->stats, 0, माप(pf->stats));
	स_रखो(&pf->stats_offsets, 0, माप(pf->stats_offsets));
	pf->stat_offsets_loaded = false;

	क्रम (i = 0; i < I40E_MAX_VEB; i++) अणु
		अगर (pf->veb[i]) अणु
			स_रखो(&pf->veb[i]->stats, 0,
			       माप(pf->veb[i]->stats));
			स_रखो(&pf->veb[i]->stats_offsets, 0,
			       माप(pf->veb[i]->stats_offsets));
			स_रखो(&pf->veb[i]->tc_stats, 0,
			       माप(pf->veb[i]->tc_stats));
			स_रखो(&pf->veb[i]->tc_stats_offsets, 0,
			       माप(pf->veb[i]->tc_stats_offsets));
			pf->veb[i]->stat_offsets_loaded = false;
		पूर्ण
	पूर्ण
	pf->hw_csum_rx_error = 0;
पूर्ण

/**
 * i40e_stat_update48 - पढ़ो and update a 48 bit stat from the chip
 * @hw: ptr to the hardware info
 * @hireg: the high 32 bit reg to पढ़ो
 * @loreg: the low 32 bit reg to पढ़ो
 * @offset_loaded: has the initial offset been loaded yet
 * @offset: ptr to current offset value
 * @stat: ptr to the stat
 *
 * Since the device stats are not reset at PFReset, they likely will not
 * be zeroed when the driver starts.  We'll save the first values पढ़ो
 * and use them as offsets to be subtracted from the raw values in order
 * to report stats that count from zero.  In the process, we also manage
 * the potential roll-over.
 **/
अटल व्योम i40e_stat_update48(काष्ठा i40e_hw *hw, u32 hireg, u32 loreg,
			       bool offset_loaded, u64 *offset, u64 *stat)
अणु
	u64 new_data;

	अगर (hw->device_id == I40E_DEV_ID_QEMU) अणु
		new_data = rd32(hw, loreg);
		new_data |= ((u64)(rd32(hw, hireg) & 0xFFFF)) << 32;
	पूर्ण अन्यथा अणु
		new_data = rd64(hw, loreg);
	पूर्ण
	अगर (!offset_loaded)
		*offset = new_data;
	अगर (likely(new_data >= *offset))
		*stat = new_data - *offset;
	अन्यथा
		*stat = (new_data + BIT_ULL(48)) - *offset;
	*stat &= 0xFFFFFFFFFFFFULL;
पूर्ण

/**
 * i40e_stat_update32 - पढ़ो and update a 32 bit stat from the chip
 * @hw: ptr to the hardware info
 * @reg: the hw reg to पढ़ो
 * @offset_loaded: has the initial offset been loaded yet
 * @offset: ptr to current offset value
 * @stat: ptr to the stat
 **/
अटल व्योम i40e_stat_update32(काष्ठा i40e_hw *hw, u32 reg,
			       bool offset_loaded, u64 *offset, u64 *stat)
अणु
	u32 new_data;

	new_data = rd32(hw, reg);
	अगर (!offset_loaded)
		*offset = new_data;
	अगर (likely(new_data >= *offset))
		*stat = (u32)(new_data - *offset);
	अन्यथा
		*stat = (u32)((new_data + BIT_ULL(32)) - *offset);
पूर्ण

/**
 * i40e_stat_update_and_clear32 - पढ़ो and clear hw reg, update a 32 bit stat
 * @hw: ptr to the hardware info
 * @reg: the hw reg to पढ़ो and clear
 * @stat: ptr to the stat
 **/
अटल व्योम i40e_stat_update_and_clear32(काष्ठा i40e_hw *hw, u32 reg, u64 *stat)
अणु
	u32 new_data = rd32(hw, reg);

	wr32(hw, reg, 1); /* must ग_लिखो a nonzero value to clear रेजिस्टर */
	*stat += new_data;
पूर्ण

/**
 * i40e_update_eth_stats - Update VSI-specअगरic ethernet statistics counters.
 * @vsi: the VSI to be updated
 **/
व्योम i40e_update_eth_stats(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक stat_idx = le16_to_cpu(vsi->info.stat_counter_idx);
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_eth_stats *oes;
	काष्ठा i40e_eth_stats *es;     /* device's eth stats */

	es = &vsi->eth_stats;
	oes = &vsi->eth_stats_offsets;

	/* Gather up the stats that the hw collects */
	i40e_stat_update32(hw, I40E_GLV_TEPC(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_errors, &es->tx_errors);
	i40e_stat_update32(hw, I40E_GLV_RDPC(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_discards, &es->rx_discards);
	i40e_stat_update32(hw, I40E_GLV_RUPP(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_unknown_protocol, &es->rx_unknown_protocol);

	i40e_stat_update48(hw, I40E_GLV_GORCH(stat_idx),
			   I40E_GLV_GORCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_bytes, &es->rx_bytes);
	i40e_stat_update48(hw, I40E_GLV_UPRCH(stat_idx),
			   I40E_GLV_UPRCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_unicast, &es->rx_unicast);
	i40e_stat_update48(hw, I40E_GLV_MPRCH(stat_idx),
			   I40E_GLV_MPRCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_multicast, &es->rx_multicast);
	i40e_stat_update48(hw, I40E_GLV_BPRCH(stat_idx),
			   I40E_GLV_BPRCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_broadcast, &es->rx_broadcast);

	i40e_stat_update48(hw, I40E_GLV_GOTCH(stat_idx),
			   I40E_GLV_GOTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_bytes, &es->tx_bytes);
	i40e_stat_update48(hw, I40E_GLV_UPTCH(stat_idx),
			   I40E_GLV_UPTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_unicast, &es->tx_unicast);
	i40e_stat_update48(hw, I40E_GLV_MPTCH(stat_idx),
			   I40E_GLV_MPTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_multicast, &es->tx_multicast);
	i40e_stat_update48(hw, I40E_GLV_BPTCH(stat_idx),
			   I40E_GLV_BPTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_broadcast, &es->tx_broadcast);
	vsi->stat_offsets_loaded = true;
पूर्ण

/**
 * i40e_update_veb_stats - Update Switch component statistics
 * @veb: the VEB being updated
 **/
व्योम i40e_update_veb_stats(काष्ठा i40e_veb *veb)
अणु
	काष्ठा i40e_pf *pf = veb->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_eth_stats *oes;
	काष्ठा i40e_eth_stats *es;     /* device's eth stats */
	काष्ठा i40e_veb_tc_stats *veb_oes;
	काष्ठा i40e_veb_tc_stats *veb_es;
	पूर्णांक i, idx = 0;

	idx = veb->stats_idx;
	es = &veb->stats;
	oes = &veb->stats_offsets;
	veb_es = &veb->tc_stats;
	veb_oes = &veb->tc_stats_offsets;

	/* Gather up the stats that the hw collects */
	i40e_stat_update32(hw, I40E_GLSW_TDPC(idx),
			   veb->stat_offsets_loaded,
			   &oes->tx_discards, &es->tx_discards);
	अगर (hw->revision_id > 0)
		i40e_stat_update32(hw, I40E_GLSW_RUPP(idx),
				   veb->stat_offsets_loaded,
				   &oes->rx_unknown_protocol,
				   &es->rx_unknown_protocol);
	i40e_stat_update48(hw, I40E_GLSW_GORCH(idx), I40E_GLSW_GORCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->rx_bytes, &es->rx_bytes);
	i40e_stat_update48(hw, I40E_GLSW_UPRCH(idx), I40E_GLSW_UPRCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->rx_unicast, &es->rx_unicast);
	i40e_stat_update48(hw, I40E_GLSW_MPRCH(idx), I40E_GLSW_MPRCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->rx_multicast, &es->rx_multicast);
	i40e_stat_update48(hw, I40E_GLSW_BPRCH(idx), I40E_GLSW_BPRCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->rx_broadcast, &es->rx_broadcast);

	i40e_stat_update48(hw, I40E_GLSW_GOTCH(idx), I40E_GLSW_GOTCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->tx_bytes, &es->tx_bytes);
	i40e_stat_update48(hw, I40E_GLSW_UPTCH(idx), I40E_GLSW_UPTCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->tx_unicast, &es->tx_unicast);
	i40e_stat_update48(hw, I40E_GLSW_MPTCH(idx), I40E_GLSW_MPTCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->tx_multicast, &es->tx_multicast);
	i40e_stat_update48(hw, I40E_GLSW_BPTCH(idx), I40E_GLSW_BPTCL(idx),
			   veb->stat_offsets_loaded,
			   &oes->tx_broadcast, &es->tx_broadcast);
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		i40e_stat_update48(hw, I40E_GLVEBTC_RPCH(i, idx),
				   I40E_GLVEBTC_RPCL(i, idx),
				   veb->stat_offsets_loaded,
				   &veb_oes->tc_rx_packets[i],
				   &veb_es->tc_rx_packets[i]);
		i40e_stat_update48(hw, I40E_GLVEBTC_RBCH(i, idx),
				   I40E_GLVEBTC_RBCL(i, idx),
				   veb->stat_offsets_loaded,
				   &veb_oes->tc_rx_bytes[i],
				   &veb_es->tc_rx_bytes[i]);
		i40e_stat_update48(hw, I40E_GLVEBTC_TPCH(i, idx),
				   I40E_GLVEBTC_TPCL(i, idx),
				   veb->stat_offsets_loaded,
				   &veb_oes->tc_tx_packets[i],
				   &veb_es->tc_tx_packets[i]);
		i40e_stat_update48(hw, I40E_GLVEBTC_TBCH(i, idx),
				   I40E_GLVEBTC_TBCL(i, idx),
				   veb->stat_offsets_loaded,
				   &veb_oes->tc_tx_bytes[i],
				   &veb_es->tc_tx_bytes[i]);
	पूर्ण
	veb->stat_offsets_loaded = true;
पूर्ण

/**
 * i40e_update_vsi_stats - Update the vsi statistics counters.
 * @vsi: the VSI to be updated
 *
 * There are a few instances where we store the same stat in a
 * couple of dअगरferent काष्ठाs.  This is partly because we have
 * the netdev stats that need to be filled out, which is slightly
 * dअगरferent from the "eth_stats" defined by the chip and used in
 * VF communications.  We sort it out here.
 **/
अटल व्योम i40e_update_vsi_stats(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा rtnl_link_stats64 *ons;
	काष्ठा rtnl_link_stats64 *ns;   /* netdev stats */
	काष्ठा i40e_eth_stats *oes;
	काष्ठा i40e_eth_stats *es;     /* device's eth stats */
	u32 tx_restart, tx_busy;
	काष्ठा i40e_ring *p;
	u32 rx_page, rx_buf;
	u64 bytes, packets;
	अचिन्हित पूर्णांक start;
	u64 tx_linearize;
	u64 tx_क्रमce_wb;
	u64 rx_p, rx_b;
	u64 tx_p, tx_b;
	u16 q;

	अगर (test_bit(__I40E_VSI_DOWN, vsi->state) ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		वापस;

	ns = i40e_get_vsi_stats_काष्ठा(vsi);
	ons = &vsi->net_stats_offsets;
	es = &vsi->eth_stats;
	oes = &vsi->eth_stats_offsets;

	/* Gather up the netdev and vsi stats that the driver collects
	 * on the fly during packet processing
	 */
	rx_b = rx_p = 0;
	tx_b = tx_p = 0;
	tx_restart = tx_busy = tx_linearize = tx_क्रमce_wb = 0;
	rx_page = 0;
	rx_buf = 0;
	rcu_पढ़ो_lock();
	क्रम (q = 0; q < vsi->num_queue_pairs; q++) अणु
		/* locate Tx ring */
		p = READ_ONCE(vsi->tx_rings[q]);
		अगर (!p)
			जारी;

		करो अणु
			start = u64_stats_fetch_begin_irq(&p->syncp);
			packets = p->stats.packets;
			bytes = p->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp, start));
		tx_b += bytes;
		tx_p += packets;
		tx_restart += p->tx_stats.restart_queue;
		tx_busy += p->tx_stats.tx_busy;
		tx_linearize += p->tx_stats.tx_linearize;
		tx_क्रमce_wb += p->tx_stats.tx_क्रमce_wb;

		/* locate Rx ring */
		p = READ_ONCE(vsi->rx_rings[q]);
		अगर (!p)
			जारी;

		करो अणु
			start = u64_stats_fetch_begin_irq(&p->syncp);
			packets = p->stats.packets;
			bytes = p->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp, start));
		rx_b += bytes;
		rx_p += packets;
		rx_buf += p->rx_stats.alloc_buff_failed;
		rx_page += p->rx_stats.alloc_page_failed;

		अगर (i40e_enabled_xdp_vsi(vsi)) अणु
			/* locate XDP ring */
			p = READ_ONCE(vsi->xdp_rings[q]);
			अगर (!p)
				जारी;

			करो अणु
				start = u64_stats_fetch_begin_irq(&p->syncp);
				packets = p->stats.packets;
				bytes = p->stats.bytes;
			पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp, start));
			tx_b += bytes;
			tx_p += packets;
			tx_restart += p->tx_stats.restart_queue;
			tx_busy += p->tx_stats.tx_busy;
			tx_linearize += p->tx_stats.tx_linearize;
			tx_क्रमce_wb += p->tx_stats.tx_क्रमce_wb;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	vsi->tx_restart = tx_restart;
	vsi->tx_busy = tx_busy;
	vsi->tx_linearize = tx_linearize;
	vsi->tx_क्रमce_wb = tx_क्रमce_wb;
	vsi->rx_page_failed = rx_page;
	vsi->rx_buf_failed = rx_buf;

	ns->rx_packets = rx_p;
	ns->rx_bytes = rx_b;
	ns->tx_packets = tx_p;
	ns->tx_bytes = tx_b;

	/* update netdev stats from eth stats */
	i40e_update_eth_stats(vsi);
	ons->tx_errors = oes->tx_errors;
	ns->tx_errors = es->tx_errors;
	ons->multicast = oes->rx_multicast;
	ns->multicast = es->rx_multicast;
	ons->rx_dropped = oes->rx_discards;
	ns->rx_dropped = es->rx_discards;
	ons->tx_dropped = oes->tx_discards;
	ns->tx_dropped = es->tx_discards;

	/* pull in a couple PF stats अगर this is the मुख्य vsi */
	अगर (vsi == pf->vsi[pf->lan_vsi]) अणु
		ns->rx_crc_errors = pf->stats.crc_errors;
		ns->rx_errors = pf->stats.crc_errors + pf->stats.illegal_bytes;
		ns->rx_length_errors = pf->stats.rx_length_errors;
	पूर्ण
पूर्ण

/**
 * i40e_update_pf_stats - Update the PF statistics counters.
 * @pf: the PF to be updated
 **/
अटल व्योम i40e_update_pf_stats(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw_port_stats *osd = &pf->stats_offsets;
	काष्ठा i40e_hw_port_stats *nsd = &pf->stats;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 val;
	पूर्णांक i;

	i40e_stat_update48(hw, I40E_GLPRT_GORCH(hw->port),
			   I40E_GLPRT_GORCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.rx_bytes, &nsd->eth.rx_bytes);
	i40e_stat_update48(hw, I40E_GLPRT_GOTCH(hw->port),
			   I40E_GLPRT_GOTCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.tx_bytes, &nsd->eth.tx_bytes);
	i40e_stat_update32(hw, I40E_GLPRT_RDPC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.rx_discards,
			   &nsd->eth.rx_discards);
	i40e_stat_update48(hw, I40E_GLPRT_UPRCH(hw->port),
			   I40E_GLPRT_UPRCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.rx_unicast,
			   &nsd->eth.rx_unicast);
	i40e_stat_update48(hw, I40E_GLPRT_MPRCH(hw->port),
			   I40E_GLPRT_MPRCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.rx_multicast,
			   &nsd->eth.rx_multicast);
	i40e_stat_update48(hw, I40E_GLPRT_BPRCH(hw->port),
			   I40E_GLPRT_BPRCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.rx_broadcast,
			   &nsd->eth.rx_broadcast);
	i40e_stat_update48(hw, I40E_GLPRT_UPTCH(hw->port),
			   I40E_GLPRT_UPTCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.tx_unicast,
			   &nsd->eth.tx_unicast);
	i40e_stat_update48(hw, I40E_GLPRT_MPTCH(hw->port),
			   I40E_GLPRT_MPTCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.tx_multicast,
			   &nsd->eth.tx_multicast);
	i40e_stat_update48(hw, I40E_GLPRT_BPTCH(hw->port),
			   I40E_GLPRT_BPTCL(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->eth.tx_broadcast,
			   &nsd->eth.tx_broadcast);

	i40e_stat_update32(hw, I40E_GLPRT_TDOLD(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_dropped_link_करोwn,
			   &nsd->tx_dropped_link_करोwn);

	i40e_stat_update32(hw, I40E_GLPRT_CRCERRS(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->crc_errors, &nsd->crc_errors);

	i40e_stat_update32(hw, I40E_GLPRT_ILLERRC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->illegal_bytes, &nsd->illegal_bytes);

	i40e_stat_update32(hw, I40E_GLPRT_MLFC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->mac_local_faults,
			   &nsd->mac_local_faults);
	i40e_stat_update32(hw, I40E_GLPRT_MRFC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->mac_remote_faults,
			   &nsd->mac_remote_faults);

	i40e_stat_update32(hw, I40E_GLPRT_RLEC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_length_errors,
			   &nsd->rx_length_errors);

	i40e_stat_update32(hw, I40E_GLPRT_LXONRXC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->link_xon_rx, &nsd->link_xon_rx);
	i40e_stat_update32(hw, I40E_GLPRT_LXONTXC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->link_xon_tx, &nsd->link_xon_tx);
	i40e_stat_update32(hw, I40E_GLPRT_LXOFFRXC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->link_xoff_rx, &nsd->link_xoff_rx);
	i40e_stat_update32(hw, I40E_GLPRT_LXOFFTXC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->link_xoff_tx, &nsd->link_xoff_tx);

	क्रम (i = 0; i < 8; i++) अणु
		i40e_stat_update32(hw, I40E_GLPRT_PXOFFRXC(hw->port, i),
				   pf->stat_offsets_loaded,
				   &osd->priority_xoff_rx[i],
				   &nsd->priority_xoff_rx[i]);
		i40e_stat_update32(hw, I40E_GLPRT_PXONRXC(hw->port, i),
				   pf->stat_offsets_loaded,
				   &osd->priority_xon_rx[i],
				   &nsd->priority_xon_rx[i]);
		i40e_stat_update32(hw, I40E_GLPRT_PXONTXC(hw->port, i),
				   pf->stat_offsets_loaded,
				   &osd->priority_xon_tx[i],
				   &nsd->priority_xon_tx[i]);
		i40e_stat_update32(hw, I40E_GLPRT_PXOFFTXC(hw->port, i),
				   pf->stat_offsets_loaded,
				   &osd->priority_xoff_tx[i],
				   &nsd->priority_xoff_tx[i]);
		i40e_stat_update32(hw,
				   I40E_GLPRT_RXON2OFFCNT(hw->port, i),
				   pf->stat_offsets_loaded,
				   &osd->priority_xon_2_xoff[i],
				   &nsd->priority_xon_2_xoff[i]);
	पूर्ण

	i40e_stat_update48(hw, I40E_GLPRT_PRC64H(hw->port),
			   I40E_GLPRT_PRC64L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_size_64, &nsd->rx_size_64);
	i40e_stat_update48(hw, I40E_GLPRT_PRC127H(hw->port),
			   I40E_GLPRT_PRC127L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_size_127, &nsd->rx_size_127);
	i40e_stat_update48(hw, I40E_GLPRT_PRC255H(hw->port),
			   I40E_GLPRT_PRC255L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_size_255, &nsd->rx_size_255);
	i40e_stat_update48(hw, I40E_GLPRT_PRC511H(hw->port),
			   I40E_GLPRT_PRC511L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_size_511, &nsd->rx_size_511);
	i40e_stat_update48(hw, I40E_GLPRT_PRC1023H(hw->port),
			   I40E_GLPRT_PRC1023L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_size_1023, &nsd->rx_size_1023);
	i40e_stat_update48(hw, I40E_GLPRT_PRC1522H(hw->port),
			   I40E_GLPRT_PRC1522L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_size_1522, &nsd->rx_size_1522);
	i40e_stat_update48(hw, I40E_GLPRT_PRC9522H(hw->port),
			   I40E_GLPRT_PRC9522L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_size_big, &nsd->rx_size_big);

	i40e_stat_update48(hw, I40E_GLPRT_PTC64H(hw->port),
			   I40E_GLPRT_PTC64L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_size_64, &nsd->tx_size_64);
	i40e_stat_update48(hw, I40E_GLPRT_PTC127H(hw->port),
			   I40E_GLPRT_PTC127L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_size_127, &nsd->tx_size_127);
	i40e_stat_update48(hw, I40E_GLPRT_PTC255H(hw->port),
			   I40E_GLPRT_PTC255L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_size_255, &nsd->tx_size_255);
	i40e_stat_update48(hw, I40E_GLPRT_PTC511H(hw->port),
			   I40E_GLPRT_PTC511L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_size_511, &nsd->tx_size_511);
	i40e_stat_update48(hw, I40E_GLPRT_PTC1023H(hw->port),
			   I40E_GLPRT_PTC1023L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_size_1023, &nsd->tx_size_1023);
	i40e_stat_update48(hw, I40E_GLPRT_PTC1522H(hw->port),
			   I40E_GLPRT_PTC1522L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_size_1522, &nsd->tx_size_1522);
	i40e_stat_update48(hw, I40E_GLPRT_PTC9522H(hw->port),
			   I40E_GLPRT_PTC9522L(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->tx_size_big, &nsd->tx_size_big);

	i40e_stat_update32(hw, I40E_GLPRT_RUC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_undersize, &nsd->rx_undersize);
	i40e_stat_update32(hw, I40E_GLPRT_RFC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_fragments, &nsd->rx_fragments);
	i40e_stat_update32(hw, I40E_GLPRT_ROC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_oversize, &nsd->rx_oversize);
	i40e_stat_update32(hw, I40E_GLPRT_RJC(hw->port),
			   pf->stat_offsets_loaded,
			   &osd->rx_jabber, &nsd->rx_jabber);

	/* Fसूची stats */
	i40e_stat_update_and_clear32(hw,
			I40E_GLQF_PCNT(I40E_FD_ATR_STAT_IDX(hw->pf_id)),
			&nsd->fd_atr_match);
	i40e_stat_update_and_clear32(hw,
			I40E_GLQF_PCNT(I40E_FD_SB_STAT_IDX(hw->pf_id)),
			&nsd->fd_sb_match);
	i40e_stat_update_and_clear32(hw,
			I40E_GLQF_PCNT(I40E_FD_ATR_TUNNEL_STAT_IDX(hw->pf_id)),
			&nsd->fd_atr_tunnel_match);

	val = rd32(hw, I40E_PRTPM_EEE_STAT);
	nsd->tx_lpi_status =
		       (val & I40E_PRTPM_EEE_STAT_TX_LPI_STATUS_MASK) >>
			I40E_PRTPM_EEE_STAT_TX_LPI_STATUS_SHIFT;
	nsd->rx_lpi_status =
		       (val & I40E_PRTPM_EEE_STAT_RX_LPI_STATUS_MASK) >>
			I40E_PRTPM_EEE_STAT_RX_LPI_STATUS_SHIFT;
	i40e_stat_update32(hw, I40E_PRTPM_TLPIC,
			   pf->stat_offsets_loaded,
			   &osd->tx_lpi_count, &nsd->tx_lpi_count);
	i40e_stat_update32(hw, I40E_PRTPM_RLPIC,
			   pf->stat_offsets_loaded,
			   &osd->rx_lpi_count, &nsd->rx_lpi_count);

	अगर (pf->flags & I40E_FLAG_FD_SB_ENABLED &&
	    !test_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state))
		nsd->fd_sb_status = true;
	अन्यथा
		nsd->fd_sb_status = false;

	अगर (pf->flags & I40E_FLAG_FD_ATR_ENABLED &&
	    !test_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state))
		nsd->fd_atr_status = true;
	अन्यथा
		nsd->fd_atr_status = false;

	pf->stat_offsets_loaded = true;
पूर्ण

/**
 * i40e_update_stats - Update the various statistics counters.
 * @vsi: the VSI to be updated
 *
 * Update the various stats क्रम this VSI and its related entities.
 **/
व्योम i40e_update_stats(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;

	अगर (vsi == pf->vsi[pf->lan_vsi])
		i40e_update_pf_stats(pf);

	i40e_update_vsi_stats(vsi);
पूर्ण

/**
 * i40e_count_filters - counts VSI mac filters
 * @vsi: the VSI to be searched
 *
 * Returns count of mac filters
 **/
पूर्णांक i40e_count_filters(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_mac_filter *f;
	काष्ठा hlist_node *h;
	पूर्णांक bkt;
	पूर्णांक cnt = 0;

	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist)
		++cnt;

	वापस cnt;
पूर्ण

/**
 * i40e_find_filter - Search VSI filter list क्रम specअगरic mac/vlan filter
 * @vsi: the VSI to be searched
 * @macaddr: the MAC address
 * @vlan: the vlan
 *
 * Returns ptr to the filter object or शून्य
 **/
अटल काष्ठा i40e_mac_filter *i40e_find_filter(काष्ठा i40e_vsi *vsi,
						स्थिर u8 *macaddr, s16 vlan)
अणु
	काष्ठा i40e_mac_filter *f;
	u64 key;

	अगर (!vsi || !macaddr)
		वापस शून्य;

	key = i40e_addr_to_hkey(macaddr);
	hash_क्रम_each_possible(vsi->mac_filter_hash, f, hlist, key) अणु
		अगर ((ether_addr_equal(macaddr, f->macaddr)) &&
		    (vlan == f->vlan))
			वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * i40e_find_mac - Find a mac addr in the macvlan filters list
 * @vsi: the VSI to be searched
 * @macaddr: the MAC address we are searching क्रम
 *
 * Returns the first filter with the provided MAC address or शून्य अगर
 * MAC address was not found
 **/
काष्ठा i40e_mac_filter *i40e_find_mac(काष्ठा i40e_vsi *vsi, स्थिर u8 *macaddr)
अणु
	काष्ठा i40e_mac_filter *f;
	u64 key;

	अगर (!vsi || !macaddr)
		वापस शून्य;

	key = i40e_addr_to_hkey(macaddr);
	hash_क्रम_each_possible(vsi->mac_filter_hash, f, hlist, key) अणु
		अगर ((ether_addr_equal(macaddr, f->macaddr)))
			वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * i40e_is_vsi_in_vlan - Check अगर VSI is in vlan mode
 * @vsi: the VSI to be searched
 *
 * Returns true अगर VSI is in vlan mode or false otherwise
 **/
bool i40e_is_vsi_in_vlan(काष्ठा i40e_vsi *vsi)
अणु
	/* If we have a PVID, always operate in VLAN mode */
	अगर (vsi->info.pvid)
		वापस true;

	/* We need to operate in VLAN mode whenever we have any filters with
	 * a VLAN other than I40E_VLAN_ALL. We could check the table each
	 * समय, incurring search cost repeatedly. However, we can notice two
	 * things:
	 *
	 * 1) the only place where we can gain a VLAN filter is in
	 *    i40e_add_filter.
	 *
	 * 2) the only place where filters are actually हटाओd is in
	 *    i40e_sync_filters_subtask.
	 *
	 * Thus, we can simply use a boolean value, has_vlan_filters which we
	 * will set to true when we add a VLAN filter in i40e_add_filter. Then
	 * we have to perक्रमm the full search after deleting filters in
	 * i40e_sync_filters_subtask, but we alपढ़ोy have to search
	 * filters here and can perक्रमm the check at the same समय. This
	 * results in aव्योमing embedding a loop क्रम VLAN mode inside another
	 * loop over all the filters, and should मुख्यtain correctness as noted
	 * above.
	 */
	वापस vsi->has_vlan_filter;
पूर्ण

/**
 * i40e_correct_mac_vlan_filters - Correct non-VLAN filters अगर necessary
 * @vsi: the VSI to configure
 * @पंचांगp_add_list: list of filters पढ़ोy to be added
 * @पंचांगp_del_list: list of filters पढ़ोy to be deleted
 * @vlan_filters: the number of active VLAN filters
 *
 * Update VLAN=0 and VLAN=-1 (I40E_VLAN_ANY) filters properly so that they
 * behave as expected. If we have any active VLAN filters reमुख्यing or about
 * to be added then we need to update non-VLAN filters to be marked as VLAN=0
 * so that they only match against untagged traffic. If we no दीर्घer have any
 * active VLAN filters, we need to make all non-VLAN filters marked as VLAN=-1
 * so that they match against both tagged and untagged traffic. In this way,
 * we ensure that we correctly receive the desired traffic. This ensures that
 * when we have an active VLAN we will receive only untagged traffic and
 * traffic matching active VLANs. If we have no active VLANs then we will
 * operate in non-VLAN mode and receive all traffic, tagged or untagged.
 *
 * Finally, in a similar fashion, this function also corrects filters when
 * there is an active PVID asचिन्हित to this VSI.
 *
 * In हाल of memory allocation failure वापस -ENOMEM. Otherwise, वापस 0.
 *
 * This function is only expected to be called from within
 * i40e_sync_vsi_filters.
 *
 * NOTE: This function expects to be called जबतक under the
 * mac_filter_hash_lock
 */
अटल पूर्णांक i40e_correct_mac_vlan_filters(काष्ठा i40e_vsi *vsi,
					 काष्ठा hlist_head *पंचांगp_add_list,
					 काष्ठा hlist_head *पंचांगp_del_list,
					 पूर्णांक vlan_filters)
अणु
	s16 pvid = le16_to_cpu(vsi->info.pvid);
	काष्ठा i40e_mac_filter *f, *add_head;
	काष्ठा i40e_new_mac_filter *new;
	काष्ठा hlist_node *h;
	पूर्णांक bkt, new_vlan;

	/* To determine अगर a particular filter needs to be replaced we
	 * have the three following conditions:
	 *
	 * a) अगर we have a PVID asचिन्हित, then all filters which are
	 *    not marked as VLAN=PVID must be replaced with filters that
	 *    are.
	 * b) otherwise, अगर we have any active VLANS, all filters
	 *    which are marked as VLAN=-1 must be replaced with
	 *    filters marked as VLAN=0
	 * c) finally, अगर we करो not have any active VLANS, all filters
	 *    which are marked as VLAN=0 must be replaced with filters
	 *    marked as VLAN=-1
	 */

	/* Update the filters about to be added in place */
	hlist_क्रम_each_entry(new, पंचांगp_add_list, hlist) अणु
		अगर (pvid && new->f->vlan != pvid)
			new->f->vlan = pvid;
		अन्यथा अगर (vlan_filters && new->f->vlan == I40E_VLAN_ANY)
			new->f->vlan = 0;
		अन्यथा अगर (!vlan_filters && new->f->vlan == 0)
			new->f->vlan = I40E_VLAN_ANY;
	पूर्ण

	/* Update the reमुख्यing active filters */
	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
		/* Combine the checks क्रम whether a filter needs to be changed
		 * and then determine the new VLAN inside the अगर block, in
		 * order to aव्योम duplicating code क्रम adding the new filter
		 * then deleting the old filter.
		 */
		अगर ((pvid && f->vlan != pvid) ||
		    (vlan_filters && f->vlan == I40E_VLAN_ANY) ||
		    (!vlan_filters && f->vlan == 0)) अणु
			/* Determine the new vlan we will be adding */
			अगर (pvid)
				new_vlan = pvid;
			अन्यथा अगर (vlan_filters)
				new_vlan = 0;
			अन्यथा
				new_vlan = I40E_VLAN_ANY;

			/* Create the new filter */
			add_head = i40e_add_filter(vsi, f->macaddr, new_vlan);
			अगर (!add_head)
				वापस -ENOMEM;

			/* Create a temporary i40e_new_mac_filter */
			new = kzalloc(माप(*new), GFP_ATOMIC);
			अगर (!new)
				वापस -ENOMEM;

			new->f = add_head;
			new->state = add_head->state;

			/* Add the new filter to the पंचांगp list */
			hlist_add_head(&new->hlist, पंचांगp_add_list);

			/* Put the original filter पूर्णांकo the delete list */
			f->state = I40E_FILTER_REMOVE;
			hash_del(&f->hlist);
			hlist_add_head(&f->hlist, पंचांगp_del_list);
		पूर्ण
	पूर्ण

	vsi->has_vlan_filter = !!vlan_filters;

	वापस 0;
पूर्ण

/**
 * i40e_rm_शेष_mac_filter - Remove the शेष MAC filter set by NVM
 * @vsi: the PF Main VSI - inappropriate क्रम any other VSI
 * @macaddr: the MAC address
 *
 * Remove whatever filter the firmware set up so the driver can manage
 * its own filtering पूर्णांकelligently.
 **/
अटल व्योम i40e_rm_शेष_mac_filter(काष्ठा i40e_vsi *vsi, u8 *macaddr)
अणु
	काष्ठा i40e_aqc_हटाओ_macvlan_element_data element;
	काष्ठा i40e_pf *pf = vsi->back;

	/* Only appropriate क्रम the PF मुख्य VSI */
	अगर (vsi->type != I40E_VSI_MAIN)
		वापस;

	स_रखो(&element, 0, माप(element));
	ether_addr_copy(element.mac_addr, macaddr);
	element.vlan_tag = 0;
	/* Ignore error वापसs, some firmware करोes it this way... */
	element.flags = I40E_AQC_MACVLAN_DEL_PERFECT_MATCH;
	i40e_aq_हटाओ_macvlan(&pf->hw, vsi->seid, &element, 1, शून्य);

	स_रखो(&element, 0, माप(element));
	ether_addr_copy(element.mac_addr, macaddr);
	element.vlan_tag = 0;
	/* ...and some firmware करोes it this way. */
	element.flags = I40E_AQC_MACVLAN_DEL_PERFECT_MATCH |
			I40E_AQC_MACVLAN_DEL_IGNORE_VLAN;
	i40e_aq_हटाओ_macvlan(&pf->hw, vsi->seid, &element, 1, शून्य);
पूर्ण

/**
 * i40e_add_filter - Add a mac/vlan filter to the VSI
 * @vsi: the VSI to be searched
 * @macaddr: the MAC address
 * @vlan: the vlan
 *
 * Returns ptr to the filter object or शून्य when no memory available.
 *
 * NOTE: This function is expected to be called with mac_filter_hash_lock
 * being held.
 **/
काष्ठा i40e_mac_filter *i40e_add_filter(काष्ठा i40e_vsi *vsi,
					स्थिर u8 *macaddr, s16 vlan)
अणु
	काष्ठा i40e_mac_filter *f;
	u64 key;

	अगर (!vsi || !macaddr)
		वापस शून्य;

	f = i40e_find_filter(vsi, macaddr, vlan);
	अगर (!f) अणु
		f = kzalloc(माप(*f), GFP_ATOMIC);
		अगर (!f)
			वापस शून्य;

		/* Update the boolean indicating अगर we need to function in
		 * VLAN mode.
		 */
		अगर (vlan >= 0)
			vsi->has_vlan_filter = true;

		ether_addr_copy(f->macaddr, macaddr);
		f->vlan = vlan;
		f->state = I40E_FILTER_NEW;
		INIT_HLIST_NODE(&f->hlist);

		key = i40e_addr_to_hkey(macaddr);
		hash_add(vsi->mac_filter_hash, &f->hlist, key);

		vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;
		set_bit(__I40E_MACVLAN_SYNC_PENDING, vsi->back->state);
	पूर्ण

	/* If we're asked to add a filter that has been marked क्रम removal, it
	 * is safe to simply restore it to active state. __i40e_del_filter
	 * will have simply deleted any filters which were previously marked
	 * NEW or FAILED, so अगर it is currently marked REMOVE it must have
	 * previously been ACTIVE. Since we haven't yet run the sync filters
	 * task, just restore this filter to the ACTIVE state so that the
	 * sync task leaves it in place
	 */
	अगर (f->state == I40E_FILTER_REMOVE)
		f->state = I40E_FILTER_ACTIVE;

	वापस f;
पूर्ण

/**
 * __i40e_del_filter - Remove a specअगरic filter from the VSI
 * @vsi: VSI to हटाओ from
 * @f: the filter to हटाओ from the list
 *
 * This function should be called instead of i40e_del_filter only अगर you know
 * the exact filter you will हटाओ alपढ़ोy, such as via i40e_find_filter or
 * i40e_find_mac.
 *
 * NOTE: This function is expected to be called with mac_filter_hash_lock
 * being held.
 * ANOTHER NOTE: This function MUST be called from within the context of
 * the "safe" variants of any list iterators, e.g. list_क्रम_each_entry_safe()
 * instead of list_क्रम_each_entry().
 **/
व्योम __i40e_del_filter(काष्ठा i40e_vsi *vsi, काष्ठा i40e_mac_filter *f)
अणु
	अगर (!f)
		वापस;

	/* If the filter was never added to firmware then we can just delete it
	 * directly and we करोn't want to set the status to हटाओ or अन्यथा an
	 * admin queue command will unnecessarily fire.
	 */
	अगर ((f->state == I40E_FILTER_FAILED) ||
	    (f->state == I40E_FILTER_NEW)) अणु
		hash_del(&f->hlist);
		kमुक्त(f);
	पूर्ण अन्यथा अणु
		f->state = I40E_FILTER_REMOVE;
	पूर्ण

	vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;
	set_bit(__I40E_MACVLAN_SYNC_PENDING, vsi->back->state);
पूर्ण

/**
 * i40e_del_filter - Remove a MAC/VLAN filter from the VSI
 * @vsi: the VSI to be searched
 * @macaddr: the MAC address
 * @vlan: the VLAN
 *
 * NOTE: This function is expected to be called with mac_filter_hash_lock
 * being held.
 * ANOTHER NOTE: This function MUST be called from within the context of
 * the "safe" variants of any list iterators, e.g. list_क्रम_each_entry_safe()
 * instead of list_क्रम_each_entry().
 **/
व्योम i40e_del_filter(काष्ठा i40e_vsi *vsi, स्थिर u8 *macaddr, s16 vlan)
अणु
	काष्ठा i40e_mac_filter *f;

	अगर (!vsi || !macaddr)
		वापस;

	f = i40e_find_filter(vsi, macaddr, vlan);
	__i40e_del_filter(vsi, f);
पूर्ण

/**
 * i40e_add_mac_filter - Add a MAC filter क्रम all active VLANs
 * @vsi: the VSI to be searched
 * @macaddr: the mac address to be filtered
 *
 * If we're not in VLAN mode, just add the filter to I40E_VLAN_ANY. Otherwise,
 * go through all the macvlan filters and add a macvlan filter क्रम each
 * unique vlan that alपढ़ोy exists. If a PVID has been asचिन्हित, instead only
 * add the macaddr to that VLAN.
 *
 * Returns last filter added on success, अन्यथा शून्य
 **/
काष्ठा i40e_mac_filter *i40e_add_mac_filter(काष्ठा i40e_vsi *vsi,
					    स्थिर u8 *macaddr)
अणु
	काष्ठा i40e_mac_filter *f, *add = शून्य;
	काष्ठा hlist_node *h;
	पूर्णांक bkt;

	अगर (vsi->info.pvid)
		वापस i40e_add_filter(vsi, macaddr,
				       le16_to_cpu(vsi->info.pvid));

	अगर (!i40e_is_vsi_in_vlan(vsi))
		वापस i40e_add_filter(vsi, macaddr, I40E_VLAN_ANY);

	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
		अगर (f->state == I40E_FILTER_REMOVE)
			जारी;
		add = i40e_add_filter(vsi, macaddr, f->vlan);
		अगर (!add)
			वापस शून्य;
	पूर्ण

	वापस add;
पूर्ण

/**
 * i40e_del_mac_filter - Remove a MAC filter from all VLANs
 * @vsi: the VSI to be searched
 * @macaddr: the mac address to be हटाओd
 *
 * Removes a given MAC address from a VSI regardless of what VLAN it has been
 * associated with.
 *
 * Returns 0 क्रम success, or error
 **/
पूर्णांक i40e_del_mac_filter(काष्ठा i40e_vsi *vsi, स्थिर u8 *macaddr)
अणु
	काष्ठा i40e_mac_filter *f;
	काष्ठा hlist_node *h;
	bool found = false;
	पूर्णांक bkt;

	lockdep_निश्चित_held(&vsi->mac_filter_hash_lock);
	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
		अगर (ether_addr_equal(macaddr, f->macaddr)) अणु
			__i40e_del_filter(vsi, f);
			found = true;
		पूर्ण
	पूर्ण

	अगर (found)
		वापस 0;
	अन्यथा
		वापस -ENOENT;
पूर्ण

/**
 * i40e_set_mac - NDO callback to set mac address
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (ether_addr_equal(netdev->dev_addr, addr->sa_data)) अणु
		netdev_info(netdev, "already using mac address %pM\n",
			    addr->sa_data);
		वापस 0;
	पूर्ण

	अगर (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state))
		वापस -EADDRNOTAVAIL;

	अगर (ether_addr_equal(hw->mac.addr, addr->sa_data))
		netdev_info(netdev, "returning to hw mac address %pM\n",
			    hw->mac.addr);
	अन्यथा
		netdev_info(netdev, "set new mac address %pM\n", addr->sa_data);

	/* Copy the address first, so that we aव्योम a possible race with
	 * .set_rx_mode().
	 * - Remove old address from MAC filter
	 * - Copy new address
	 * - Add new address to MAC filter
	 */
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	i40e_del_mac_filter(vsi, netdev->dev_addr);
	ether_addr_copy(netdev->dev_addr, addr->sa_data);
	i40e_add_mac_filter(vsi, netdev->dev_addr);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	अगर (vsi->type == I40E_VSI_MAIN) अणु
		i40e_status ret;

		ret = i40e_aq_mac_address_ग_लिखो(hw, I40E_AQC_WRITE_TYPE_LAA_WOL,
						addr->sa_data, शून्य);
		अगर (ret)
			netdev_info(netdev, "Ignoring error from firmware on LAA update, status %s, AQ ret %s\n",
				    i40e_stat_str(hw, ret),
				    i40e_aq_str(hw, hw->aq.asq_last_status));
	पूर्ण

	/* schedule our worker thपढ़ो which will take care of
	 * applying the new filter changes
	 */
	i40e_service_event_schedule(pf);
	वापस 0;
पूर्ण

/**
 * i40e_config_rss_aq - Prepare क्रम RSS using AQ commands
 * @vsi: vsi काष्ठाure
 * @seed: RSS hash seed
 * @lut: poपूर्णांकer to lookup table of lut_size
 * @lut_size: size of the lookup table
 **/
अटल पूर्णांक i40e_config_rss_aq(काष्ठा i40e_vsi *vsi, स्थिर u8 *seed,
			      u8 *lut, u16 lut_size)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक ret = 0;

	अगर (seed) अणु
		काष्ठा i40e_aqc_get_set_rss_key_data *seed_dw =
			(काष्ठा i40e_aqc_get_set_rss_key_data *)seed;
		ret = i40e_aq_set_rss_key(hw, vsi->id, seed_dw);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "Cannot set RSS key, err %s aq_err %s\n",
				 i40e_stat_str(hw, ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (lut) अणु
		bool pf_lut = vsi->type == I40E_VSI_MAIN;

		ret = i40e_aq_set_rss_lut(hw, vsi->id, pf_lut, lut, lut_size);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "Cannot set RSS lut, err %s aq_err %s\n",
				 i40e_stat_str(hw, ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40e_vsi_config_rss - Prepare क्रम VSI(VMDq) RSS अगर used
 * @vsi: VSI काष्ठाure
 **/
अटल पूर्णांक i40e_vsi_config_rss(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	u8 seed[I40E_HKEY_ARRAY_SIZE];
	u8 *lut;
	पूर्णांक ret;

	अगर (!(pf->hw_features & I40E_HW_RSS_AQ_CAPABLE))
		वापस 0;
	अगर (!vsi->rss_size)
		vsi->rss_size = min_t(पूर्णांक, pf->alloc_rss_size,
				      vsi->num_queue_pairs);
	अगर (!vsi->rss_size)
		वापस -EINVAL;
	lut = kzalloc(vsi->rss_table_size, GFP_KERNEL);
	अगर (!lut)
		वापस -ENOMEM;

	/* Use the user configured hash keys and lookup table अगर there is one,
	 * otherwise use शेष
	 */
	अगर (vsi->rss_lut_user)
		स_नकल(lut, vsi->rss_lut_user, vsi->rss_table_size);
	अन्यथा
		i40e_fill_rss_lut(pf, lut, vsi->rss_table_size, vsi->rss_size);
	अगर (vsi->rss_hkey_user)
		स_नकल(seed, vsi->rss_hkey_user, I40E_HKEY_ARRAY_SIZE);
	अन्यथा
		netdev_rss_key_fill((व्योम *)seed, I40E_HKEY_ARRAY_SIZE);
	ret = i40e_config_rss_aq(vsi, seed, lut, vsi->rss_table_size);
	kमुक्त(lut);
	वापस ret;
पूर्ण

/**
 * i40e_vsi_setup_queue_map_mqprio - Prepares mqprio based tc_config
 * @vsi: the VSI being configured,
 * @ctxt: VSI context काष्ठाure
 * @enabled_tc: number of traffic classes to enable
 *
 * Prepares VSI tc_config to have queue configurations based on MQPRIO options.
 **/
अटल पूर्णांक i40e_vsi_setup_queue_map_mqprio(काष्ठा i40e_vsi *vsi,
					   काष्ठा i40e_vsi_context *ctxt,
					   u8 enabled_tc)
अणु
	u16 qcount = 0, max_qcount, qmap, sections = 0;
	पूर्णांक i, override_q, घात, num_qps, ret;
	u8 netdev_tc = 0, offset = 0;

	अगर (vsi->type != I40E_VSI_MAIN)
		वापस -EINVAL;
	sections = I40E_AQ_VSI_PROP_QUEUE_MAP_VALID;
	sections |= I40E_AQ_VSI_PROP_SCHED_VALID;
	vsi->tc_config.numtc = vsi->mqprio_qopt.qopt.num_tc;
	vsi->tc_config.enabled_tc = enabled_tc ? enabled_tc : 1;
	num_qps = vsi->mqprio_qopt.qopt.count[0];

	/* find the next higher घातer-of-2 of num queue pairs */
	घात = ilog2(num_qps);
	अगर (!is_घातer_of_2(num_qps))
		घात++;
	qmap = (offset << I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT) |
		(घात << I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT);

	/* Setup queue offset/count क्रम all TCs क्रम given VSI */
	max_qcount = vsi->mqprio_qopt.qopt.count[0];
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		/* See अगर the given TC is enabled क्रम the given VSI */
		अगर (vsi->tc_config.enabled_tc & BIT(i)) अणु
			offset = vsi->mqprio_qopt.qopt.offset[i];
			qcount = vsi->mqprio_qopt.qopt.count[i];
			अगर (qcount > max_qcount)
				max_qcount = qcount;
			vsi->tc_config.tc_info[i].qoffset = offset;
			vsi->tc_config.tc_info[i].qcount = qcount;
			vsi->tc_config.tc_info[i].netdev_tc = netdev_tc++;
		पूर्ण अन्यथा अणु
			/* TC is not enabled so set the offset to
			 * शेष queue and allocate one queue
			 * क्रम the given TC.
			 */
			vsi->tc_config.tc_info[i].qoffset = 0;
			vsi->tc_config.tc_info[i].qcount = 1;
			vsi->tc_config.tc_info[i].netdev_tc = 0;
		पूर्ण
	पूर्ण

	/* Set actual Tx/Rx queue pairs */
	vsi->num_queue_pairs = offset + qcount;

	/* Setup queue TC[0].qmap क्रम given VSI context */
	ctxt->info.tc_mapping[0] = cpu_to_le16(qmap);
	ctxt->info.mapping_flags |= cpu_to_le16(I40E_AQ_VSI_QUE_MAP_CONTIG);
	ctxt->info.queue_mapping[0] = cpu_to_le16(vsi->base_queue);
	ctxt->info.valid_sections |= cpu_to_le16(sections);

	/* Reconfigure RSS क्रम मुख्य VSI with max queue count */
	vsi->rss_size = max_qcount;
	ret = i40e_vsi_config_rss(vsi);
	अगर (ret) अणु
		dev_info(&vsi->back->pdev->dev,
			 "Failed to reconfig rss for num_queues (%u)\n",
			 max_qcount);
		वापस ret;
	पूर्ण
	vsi->reconfig_rss = true;
	dev_dbg(&vsi->back->pdev->dev,
		"Reconfigured rss with num_queues (%u)\n", max_qcount);

	/* Find queue count available क्रम channel VSIs and starting offset
	 * क्रम channel VSIs
	 */
	override_q = vsi->mqprio_qopt.qopt.count[0];
	अगर (override_q && override_q < vsi->num_queue_pairs) अणु
		vsi->cnt_q_avail = vsi->num_queue_pairs - override_q;
		vsi->next_base_queue = override_q;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_vsi_setup_queue_map - Setup a VSI queue map based on enabled_tc
 * @vsi: the VSI being setup
 * @ctxt: VSI context काष्ठाure
 * @enabled_tc: Enabled TCs biपंचांगap
 * @is_add: True अगर called beक्रमe Add VSI
 *
 * Setup VSI queue mapping क्रम enabled traffic classes.
 **/
अटल व्योम i40e_vsi_setup_queue_map(काष्ठा i40e_vsi *vsi,
				     काष्ठा i40e_vsi_context *ctxt,
				     u8 enabled_tc,
				     bool is_add)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	u16 sections = 0;
	u8 netdev_tc = 0;
	u16 numtc = 1;
	u16 qcount;
	u8 offset;
	u16 qmap;
	पूर्णांक i;
	u16 num_tc_qps = 0;

	sections = I40E_AQ_VSI_PROP_QUEUE_MAP_VALID;
	offset = 0;

	/* Number of queues per enabled TC */
	num_tc_qps = vsi->alloc_queue_pairs;
	अगर (enabled_tc && (vsi->back->flags & I40E_FLAG_DCB_ENABLED)) अणु
		/* Find numtc from enabled TC biपंचांगap */
		क्रम (i = 0, numtc = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
			अगर (enabled_tc & BIT(i)) /* TC is enabled */
				numtc++;
		पूर्ण
		अगर (!numtc) अणु
			dev_warn(&pf->pdev->dev, "DCB is enabled but no TC enabled, forcing TC0\n");
			numtc = 1;
		पूर्ण
		num_tc_qps = num_tc_qps / numtc;
		num_tc_qps = min_t(पूर्णांक, num_tc_qps,
				   i40e_pf_get_max_q_per_tc(pf));
	पूर्ण

	vsi->tc_config.numtc = numtc;
	vsi->tc_config.enabled_tc = enabled_tc ? enabled_tc : 1;

	/* Do not allow use more TC queue pairs than MSI-X vectors exist */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
		num_tc_qps = min_t(पूर्णांक, num_tc_qps, pf->num_lan_msix);

	/* Setup queue offset/count क्रम all TCs क्रम given VSI */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		/* See अगर the given TC is enabled क्रम the given VSI */
		अगर (vsi->tc_config.enabled_tc & BIT(i)) अणु
			/* TC is enabled */
			पूर्णांक घात, num_qps;

			चयन (vsi->type) अणु
			हाल I40E_VSI_MAIN:
				अगर (!(pf->flags & (I40E_FLAG_FD_SB_ENABLED |
				    I40E_FLAG_FD_ATR_ENABLED)) ||
				    vsi->tc_config.enabled_tc != 1) अणु
					qcount = min_t(पूर्णांक, pf->alloc_rss_size,
						       num_tc_qps);
					अवरोध;
				पूर्ण
				fallthrough;
			हाल I40E_VSI_Fसूची:
			हाल I40E_VSI_SRIOV:
			हाल I40E_VSI_VMDQ2:
			शेष:
				qcount = num_tc_qps;
				WARN_ON(i != 0);
				अवरोध;
			पूर्ण
			vsi->tc_config.tc_info[i].qoffset = offset;
			vsi->tc_config.tc_info[i].qcount = qcount;

			/* find the next higher घातer-of-2 of num queue pairs */
			num_qps = qcount;
			घात = 0;
			जबतक (num_qps && (BIT_ULL(घात) < qcount)) अणु
				घात++;
				num_qps >>= 1;
			पूर्ण

			vsi->tc_config.tc_info[i].netdev_tc = netdev_tc++;
			qmap =
			    (offset << I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT) |
			    (घात << I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT);

			offset += qcount;
		पूर्ण अन्यथा अणु
			/* TC is not enabled so set the offset to
			 * शेष queue and allocate one queue
			 * क्रम the given TC.
			 */
			vsi->tc_config.tc_info[i].qoffset = 0;
			vsi->tc_config.tc_info[i].qcount = 1;
			vsi->tc_config.tc_info[i].netdev_tc = 0;

			qmap = 0;
		पूर्ण
		ctxt->info.tc_mapping[i] = cpu_to_le16(qmap);
	पूर्ण

	/* Set actual Tx/Rx queue pairs */
	vsi->num_queue_pairs = offset;
	अगर ((vsi->type == I40E_VSI_MAIN) && (numtc == 1)) अणु
		अगर (vsi->req_queue_pairs > 0)
			vsi->num_queue_pairs = vsi->req_queue_pairs;
		अन्यथा अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
			vsi->num_queue_pairs = pf->num_lan_msix;
	पूर्ण

	/* Scheduler section valid can only be set क्रम ADD VSI */
	अगर (is_add) अणु
		sections |= I40E_AQ_VSI_PROP_SCHED_VALID;

		ctxt->info.up_enable_bits = enabled_tc;
	पूर्ण
	अगर (vsi->type == I40E_VSI_SRIOV) अणु
		ctxt->info.mapping_flags |=
				     cpu_to_le16(I40E_AQ_VSI_QUE_MAP_NONCONTIG);
		क्रम (i = 0; i < vsi->num_queue_pairs; i++)
			ctxt->info.queue_mapping[i] =
					       cpu_to_le16(vsi->base_queue + i);
	पूर्ण अन्यथा अणु
		ctxt->info.mapping_flags |=
					cpu_to_le16(I40E_AQ_VSI_QUE_MAP_CONTIG);
		ctxt->info.queue_mapping[0] = cpu_to_le16(vsi->base_queue);
	पूर्ण
	ctxt->info.valid_sections |= cpu_to_le16(sections);
पूर्ण

/**
 * i40e_addr_sync - Callback क्रम dev_(mc|uc)_sync to add address
 * @netdev: the netdevice
 * @addr: address to add
 *
 * Called by __dev_(mc|uc)_sync when an address needs to be added. We call
 * __dev_(uc|mc)_sync from .set_rx_mode and guarantee to hold the hash lock.
 */
अटल पूर्णांक i40e_addr_sync(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	अगर (i40e_add_mac_filter(vsi, addr))
		वापस 0;
	अन्यथा
		वापस -ENOMEM;
पूर्ण

/**
 * i40e_addr_unsync - Callback क्रम dev_(mc|uc)_sync to हटाओ address
 * @netdev: the netdevice
 * @addr: address to add
 *
 * Called by __dev_(mc|uc)_sync when an address needs to be हटाओd. We call
 * __dev_(uc|mc)_sync from .set_rx_mode and guarantee to hold the hash lock.
 */
अटल पूर्णांक i40e_addr_unsync(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	/* Under some circumstances, we might receive a request to delete
	 * our own device address from our uc list. Because we store the
	 * device address in the VSI's MAC/VLAN filter list, we need to ignore
	 * such requests and not delete our device address from this list.
	 */
	अगर (ether_addr_equal(addr, netdev->dev_addr))
		वापस 0;

	i40e_del_mac_filter(vsi, addr);

	वापस 0;
पूर्ण

/**
 * i40e_set_rx_mode - NDO callback to set the netdev filters
 * @netdev: network पूर्णांकerface device काष्ठाure
 **/
अटल व्योम i40e_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	spin_lock_bh(&vsi->mac_filter_hash_lock);

	__dev_uc_sync(netdev, i40e_addr_sync, i40e_addr_unsync);
	__dev_mc_sync(netdev, i40e_addr_sync, i40e_addr_unsync);

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* check क्रम other flag changes */
	अगर (vsi->current_netdev_flags != vsi->netdev->flags) अणु
		vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;
		set_bit(__I40E_MACVLAN_SYNC_PENDING, vsi->back->state);
	पूर्ण
पूर्ण

/**
 * i40e_unकरो_del_filter_entries - Unकरो the changes made to MAC filter entries
 * @vsi: Poपूर्णांकer to VSI काष्ठा
 * @from: Poपूर्णांकer to list which contains MAC filter entries - changes to
 *        those entries needs to be unकरोne.
 *
 * MAC filter entries from this list were slated क्रम deletion.
 **/
अटल व्योम i40e_unकरो_del_filter_entries(काष्ठा i40e_vsi *vsi,
					 काष्ठा hlist_head *from)
अणु
	काष्ठा i40e_mac_filter *f;
	काष्ठा hlist_node *h;

	hlist_क्रम_each_entry_safe(f, h, from, hlist) अणु
		u64 key = i40e_addr_to_hkey(f->macaddr);

		/* Move the element back पूर्णांकo MAC filter list*/
		hlist_del(&f->hlist);
		hash_add(vsi->mac_filter_hash, &f->hlist, key);
	पूर्ण
पूर्ण

/**
 * i40e_unकरो_add_filter_entries - Unकरो the changes made to MAC filter entries
 * @vsi: Poपूर्णांकer to vsi काष्ठा
 * @from: Poपूर्णांकer to list which contains MAC filter entries - changes to
 *        those entries needs to be unकरोne.
 *
 * MAC filter entries from this list were slated क्रम addition.
 **/
अटल व्योम i40e_unकरो_add_filter_entries(काष्ठा i40e_vsi *vsi,
					 काष्ठा hlist_head *from)
अणु
	काष्ठा i40e_new_mac_filter *new;
	काष्ठा hlist_node *h;

	hlist_क्रम_each_entry_safe(new, h, from, hlist) अणु
		/* We can simply मुक्त the wrapper काष्ठाure */
		hlist_del(&new->hlist);
		kमुक्त(new);
	पूर्ण
पूर्ण

/**
 * i40e_next_filter - Get the next non-broadcast filter from a list
 * @next: poपूर्णांकer to filter in list
 *
 * Returns the next non-broadcast filter in the list. Required so that we
 * ignore broadcast filters within the list, since these are not handled via
 * the normal firmware update path.
 */
अटल
काष्ठा i40e_new_mac_filter *i40e_next_filter(काष्ठा i40e_new_mac_filter *next)
अणु
	hlist_क्रम_each_entry_जारी(next, hlist) अणु
		अगर (!is_broadcast_ether_addr(next->f->macaddr))
			वापस next;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * i40e_update_filter_state - Update filter state based on वापस data
 * from firmware
 * @count: Number of filters added
 * @add_list: वापस data from fw
 * @add_head: poपूर्णांकer to first filter in current batch
 *
 * MAC filter entries from list were slated to be added to device. Returns
 * number of successful filters. Note that 0 करोes NOT mean success!
 **/
अटल पूर्णांक
i40e_update_filter_state(पूर्णांक count,
			 काष्ठा i40e_aqc_add_macvlan_element_data *add_list,
			 काष्ठा i40e_new_mac_filter *add_head)
अणु
	पूर्णांक retval = 0;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		/* Always check status of each filter. We करोn't need to check
		 * the firmware वापस status because we pre-set the filter
		 * status to I40E_AQC_MM_ERR_NO_RES when sending the filter
		 * request to the adminq. Thus, अगर it no दीर्घer matches then
		 * we know the filter is active.
		 */
		अगर (add_list[i].match_method == I40E_AQC_MM_ERR_NO_RES) अणु
			add_head->state = I40E_FILTER_FAILED;
		पूर्ण अन्यथा अणु
			add_head->state = I40E_FILTER_ACTIVE;
			retval++;
		पूर्ण

		add_head = i40e_next_filter(add_head);
		अगर (!add_head)
			अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/**
 * i40e_aqc_del_filters - Request firmware to delete a set of filters
 * @vsi: ptr to the VSI
 * @vsi_name: name to display in messages
 * @list: the list of filters to send to firmware
 * @num_del: the number of filters to delete
 * @retval: Set to -EIO on failure to delete
 *
 * Send a request to firmware via AdminQ to delete a set of filters. Uses
 * *retval instead of a वापस value so that success करोes not क्रमce ret_val to
 * be set to 0. This ensures that a sequence of calls to this function
 * preserve the previous value of *retval on successful delete.
 */
अटल
व्योम i40e_aqc_del_filters(काष्ठा i40e_vsi *vsi, स्थिर अक्षर *vsi_name,
			  काष्ठा i40e_aqc_हटाओ_macvlan_element_data *list,
			  पूर्णांक num_del, पूर्णांक *retval)
अणु
	काष्ठा i40e_hw *hw = &vsi->back->hw;
	i40e_status aq_ret;
	पूर्णांक aq_err;

	aq_ret = i40e_aq_हटाओ_macvlan(hw, vsi->seid, list, num_del, शून्य);
	aq_err = hw->aq.asq_last_status;

	/* Explicitly ignore and करो not report when firmware वापसs ENOENT */
	अगर (aq_ret && !(aq_err == I40E_AQ_RC_ENOENT)) अणु
		*retval = -EIO;
		dev_info(&vsi->back->pdev->dev,
			 "ignoring delete macvlan error on %s, err %s, aq_err %s\n",
			 vsi_name, i40e_stat_str(hw, aq_ret),
			 i40e_aq_str(hw, aq_err));
	पूर्ण
पूर्ण

/**
 * i40e_aqc_add_filters - Request firmware to add a set of filters
 * @vsi: ptr to the VSI
 * @vsi_name: name to display in messages
 * @list: the list of filters to send to firmware
 * @add_head: Position in the add hlist
 * @num_add: the number of filters to add
 *
 * Send a request to firmware via AdminQ to add a chunk of filters. Will set
 * __I40E_VSI_OVERFLOW_PROMISC bit in vsi->state अगर the firmware has run out of
 * space क्रम more filters.
 */
अटल
व्योम i40e_aqc_add_filters(काष्ठा i40e_vsi *vsi, स्थिर अक्षर *vsi_name,
			  काष्ठा i40e_aqc_add_macvlan_element_data *list,
			  काष्ठा i40e_new_mac_filter *add_head,
			  पूर्णांक num_add)
अणु
	काष्ठा i40e_hw *hw = &vsi->back->hw;
	पूर्णांक aq_err, fcnt;

	i40e_aq_add_macvlan(hw, vsi->seid, list, num_add, शून्य);
	aq_err = hw->aq.asq_last_status;
	fcnt = i40e_update_filter_state(num_add, list, add_head);

	अगर (fcnt != num_add) अणु
		अगर (vsi->type == I40E_VSI_MAIN) अणु
			set_bit(__I40E_VSI_OVERFLOW_PROMISC, vsi->state);
			dev_warn(&vsi->back->pdev->dev,
				 "Error %s adding RX filters on %s, promiscuous mode forced on\n",
				 i40e_aq_str(hw, aq_err), vsi_name);
		पूर्ण अन्यथा अगर (vsi->type == I40E_VSI_SRIOV ||
			   vsi->type == I40E_VSI_VMDQ1 ||
			   vsi->type == I40E_VSI_VMDQ2) अणु
			dev_warn(&vsi->back->pdev->dev,
				 "Error %s adding RX filters on %s, please set promiscuous on manually for %s\n",
				 i40e_aq_str(hw, aq_err), vsi_name, vsi_name);
		पूर्ण अन्यथा अणु
			dev_warn(&vsi->back->pdev->dev,
				 "Error %s adding RX filters on %s, incorrect VSI type: %i.\n",
				 i40e_aq_str(hw, aq_err), vsi_name, vsi->type);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_aqc_broadcast_filter - Set promiscuous broadcast flags
 * @vsi: poपूर्णांकer to the VSI
 * @vsi_name: the VSI name
 * @f: filter data
 *
 * This function sets or clears the promiscuous broadcast flags क्रम VLAN
 * filters in order to properly receive broadcast frames. Assumes that only
 * broadcast filters are passed.
 *
 * Returns status indicating success or failure;
 **/
अटल i40e_status
i40e_aqc_broadcast_filter(काष्ठा i40e_vsi *vsi, स्थिर अक्षर *vsi_name,
			  काष्ठा i40e_mac_filter *f)
अणु
	bool enable = f->state == I40E_FILTER_NEW;
	काष्ठा i40e_hw *hw = &vsi->back->hw;
	i40e_status aq_ret;

	अगर (f->vlan == I40E_VLAN_ANY) अणु
		aq_ret = i40e_aq_set_vsi_broadcast(hw,
						   vsi->seid,
						   enable,
						   शून्य);
	पूर्ण अन्यथा अणु
		aq_ret = i40e_aq_set_vsi_bc_promisc_on_vlan(hw,
							    vsi->seid,
							    enable,
							    f->vlan,
							    शून्य);
	पूर्ण

	अगर (aq_ret) अणु
		set_bit(__I40E_VSI_OVERFLOW_PROMISC, vsi->state);
		dev_warn(&vsi->back->pdev->dev,
			 "Error %s, forcing overflow promiscuous on %s\n",
			 i40e_aq_str(hw, hw->aq.asq_last_status),
			 vsi_name);
	पूर्ण

	वापस aq_ret;
पूर्ण

/**
 * i40e_set_promiscuous - set promiscuous mode
 * @pf: board निजी काष्ठाure
 * @promisc: promisc on or off
 *
 * There are dअगरferent ways of setting promiscuous mode on a PF depending on
 * what state/environment we're in.  This identअगरies and sets it appropriately.
 * Returns 0 on success.
 **/
अटल पूर्णांक i40e_set_promiscuous(काष्ठा i40e_pf *pf, bool promisc)
अणु
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status aq_ret;

	अगर (vsi->type == I40E_VSI_MAIN &&
	    pf->lan_veb != I40E_NO_VEB &&
	    !(pf->flags & I40E_FLAG_MFP_ENABLED)) अणु
		/* set defport ON क्रम Main VSI instead of true promisc
		 * this way we will get all unicast/multicast and VLAN
		 * promisc behavior but will not get VF or VMDq traffic
		 * replicated on the Main VSI.
		 */
		अगर (promisc)
			aq_ret = i40e_aq_set_शेष_vsi(hw,
							 vsi->seid,
							 शून्य);
		अन्यथा
			aq_ret = i40e_aq_clear_शेष_vsi(hw,
							   vsi->seid,
							   शून्य);
		अगर (aq_ret) अणु
			dev_info(&pf->pdev->dev,
				 "Set default VSI failed, err %s, aq_err %s\n",
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		पूर्ण
	पूर्ण अन्यथा अणु
		aq_ret = i40e_aq_set_vsi_unicast_promiscuous(
						  hw,
						  vsi->seid,
						  promisc, शून्य,
						  true);
		अगर (aq_ret) अणु
			dev_info(&pf->pdev->dev,
				 "set unicast promisc failed, err %s, aq_err %s\n",
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		पूर्ण
		aq_ret = i40e_aq_set_vsi_multicast_promiscuous(
						  hw,
						  vsi->seid,
						  promisc, शून्य);
		अगर (aq_ret) अणु
			dev_info(&pf->pdev->dev,
				 "set multicast promisc failed, err %s, aq_err %s\n",
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		पूर्ण
	पूर्ण

	अगर (!aq_ret)
		pf->cur_promisc = promisc;

	वापस aq_ret;
पूर्ण

/**
 * i40e_sync_vsi_filters - Update the VSI filter list to the HW
 * @vsi: ptr to the VSI
 *
 * Push any outstanding VSI filter changes through the AdminQ.
 *
 * Returns 0 or error value
 **/
पूर्णांक i40e_sync_vsi_filters(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा hlist_head पंचांगp_add_list, पंचांगp_del_list;
	काष्ठा i40e_mac_filter *f;
	काष्ठा i40e_new_mac_filter *new, *add_head = शून्य;
	काष्ठा i40e_hw *hw = &vsi->back->hw;
	bool old_overflow, new_overflow;
	अचिन्हित पूर्णांक failed_filters = 0;
	अचिन्हित पूर्णांक vlan_filters = 0;
	अक्षर vsi_name[16] = "PF";
	पूर्णांक filter_list_len = 0;
	i40e_status aq_ret = 0;
	u32 changed_flags = 0;
	काष्ठा hlist_node *h;
	काष्ठा i40e_pf *pf;
	पूर्णांक num_add = 0;
	पूर्णांक num_del = 0;
	पूर्णांक retval = 0;
	u16 cmd_flags;
	पूर्णांक list_size;
	पूर्णांक bkt;

	/* empty array typed poपूर्णांकers, kसुस्मृति later */
	काष्ठा i40e_aqc_add_macvlan_element_data *add_list;
	काष्ठा i40e_aqc_हटाओ_macvlan_element_data *del_list;

	जबतक (test_and_set_bit(__I40E_VSI_SYNCING_FILTERS, vsi->state))
		usleep_range(1000, 2000);
	pf = vsi->back;

	old_overflow = test_bit(__I40E_VSI_OVERFLOW_PROMISC, vsi->state);

	अगर (vsi->netdev) अणु
		changed_flags = vsi->current_netdev_flags ^ vsi->netdev->flags;
		vsi->current_netdev_flags = vsi->netdev->flags;
	पूर्ण

	INIT_HLIST_HEAD(&पंचांगp_add_list);
	INIT_HLIST_HEAD(&पंचांगp_del_list);

	अगर (vsi->type == I40E_VSI_SRIOV)
		snम_लिखो(vsi_name, माप(vsi_name) - 1, "VF %d", vsi->vf_id);
	अन्यथा अगर (vsi->type != I40E_VSI_MAIN)
		snम_लिखो(vsi_name, माप(vsi_name) - 1, "vsi %d", vsi->seid);

	अगर (vsi->flags & I40E_VSI_FLAG_FILTER_CHANGED) अणु
		vsi->flags &= ~I40E_VSI_FLAG_FILTER_CHANGED;

		spin_lock_bh(&vsi->mac_filter_hash_lock);
		/* Create a list of filters to delete. */
		hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
			अगर (f->state == I40E_FILTER_REMOVE) अणु
				/* Move the element पूर्णांकo temporary del_list */
				hash_del(&f->hlist);
				hlist_add_head(&f->hlist, &पंचांगp_del_list);

				/* Aव्योम counting हटाओd filters */
				जारी;
			पूर्ण
			अगर (f->state == I40E_FILTER_NEW) अणु
				/* Create a temporary i40e_new_mac_filter */
				new = kzalloc(माप(*new), GFP_ATOMIC);
				अगर (!new)
					जाओ err_no_memory_locked;

				/* Store poपूर्णांकer to the real filter */
				new->f = f;
				new->state = f->state;

				/* Add it to the hash list */
				hlist_add_head(&new->hlist, &पंचांगp_add_list);
			पूर्ण

			/* Count the number of active (current and new) VLAN
			 * filters we have now. Does not count filters which
			 * are marked क्रम deletion.
			 */
			अगर (f->vlan > 0)
				vlan_filters++;
		पूर्ण

		retval = i40e_correct_mac_vlan_filters(vsi,
						       &पंचांगp_add_list,
						       &पंचांगp_del_list,
						       vlan_filters);
		अगर (retval)
			जाओ err_no_memory_locked;

		spin_unlock_bh(&vsi->mac_filter_hash_lock);
	पूर्ण

	/* Now process 'del_list' outside the lock */
	अगर (!hlist_empty(&पंचांगp_del_list)) अणु
		filter_list_len = hw->aq.asq_buf_size /
			    माप(काष्ठा i40e_aqc_हटाओ_macvlan_element_data);
		list_size = filter_list_len *
			    माप(काष्ठा i40e_aqc_हटाओ_macvlan_element_data);
		del_list = kzalloc(list_size, GFP_ATOMIC);
		अगर (!del_list)
			जाओ err_no_memory;

		hlist_क्रम_each_entry_safe(f, h, &पंचांगp_del_list, hlist) अणु
			cmd_flags = 0;

			/* handle broadcast filters by updating the broadcast
			 * promiscuous flag and release filter list.
			 */
			अगर (is_broadcast_ether_addr(f->macaddr)) अणु
				i40e_aqc_broadcast_filter(vsi, vsi_name, f);

				hlist_del(&f->hlist);
				kमुक्त(f);
				जारी;
			पूर्ण

			/* add to delete list */
			ether_addr_copy(del_list[num_del].mac_addr, f->macaddr);
			अगर (f->vlan == I40E_VLAN_ANY) अणु
				del_list[num_del].vlan_tag = 0;
				cmd_flags |= I40E_AQC_MACVLAN_DEL_IGNORE_VLAN;
			पूर्ण अन्यथा अणु
				del_list[num_del].vlan_tag =
					cpu_to_le16((u16)(f->vlan));
			पूर्ण

			cmd_flags |= I40E_AQC_MACVLAN_DEL_PERFECT_MATCH;
			del_list[num_del].flags = cmd_flags;
			num_del++;

			/* flush a full buffer */
			अगर (num_del == filter_list_len) अणु
				i40e_aqc_del_filters(vsi, vsi_name, del_list,
						     num_del, &retval);
				स_रखो(del_list, 0, list_size);
				num_del = 0;
			पूर्ण
			/* Release memory क्रम MAC filter entries which were
			 * synced up with HW.
			 */
			hlist_del(&f->hlist);
			kमुक्त(f);
		पूर्ण

		अगर (num_del) अणु
			i40e_aqc_del_filters(vsi, vsi_name, del_list,
					     num_del, &retval);
		पूर्ण

		kमुक्त(del_list);
		del_list = शून्य;
	पूर्ण

	अगर (!hlist_empty(&पंचांगp_add_list)) अणु
		/* Do all the adds now. */
		filter_list_len = hw->aq.asq_buf_size /
			       माप(काष्ठा i40e_aqc_add_macvlan_element_data);
		list_size = filter_list_len *
			       माप(काष्ठा i40e_aqc_add_macvlan_element_data);
		add_list = kzalloc(list_size, GFP_ATOMIC);
		अगर (!add_list)
			जाओ err_no_memory;

		num_add = 0;
		hlist_क्रम_each_entry_safe(new, h, &पंचांगp_add_list, hlist) अणु
			/* handle broadcast filters by updating the broadcast
			 * promiscuous flag instead of adding a MAC filter.
			 */
			अगर (is_broadcast_ether_addr(new->f->macaddr)) अणु
				अगर (i40e_aqc_broadcast_filter(vsi, vsi_name,
							      new->f))
					new->state = I40E_FILTER_FAILED;
				अन्यथा
					new->state = I40E_FILTER_ACTIVE;
				जारी;
			पूर्ण

			/* add to add array */
			अगर (num_add == 0)
				add_head = new;
			cmd_flags = 0;
			ether_addr_copy(add_list[num_add].mac_addr,
					new->f->macaddr);
			अगर (new->f->vlan == I40E_VLAN_ANY) अणु
				add_list[num_add].vlan_tag = 0;
				cmd_flags |= I40E_AQC_MACVLAN_ADD_IGNORE_VLAN;
			पूर्ण अन्यथा अणु
				add_list[num_add].vlan_tag =
					cpu_to_le16((u16)(new->f->vlan));
			पूर्ण
			add_list[num_add].queue_number = 0;
			/* set invalid match method क्रम later detection */
			add_list[num_add].match_method = I40E_AQC_MM_ERR_NO_RES;
			cmd_flags |= I40E_AQC_MACVLAN_ADD_PERFECT_MATCH;
			add_list[num_add].flags = cpu_to_le16(cmd_flags);
			num_add++;

			/* flush a full buffer */
			अगर (num_add == filter_list_len) अणु
				i40e_aqc_add_filters(vsi, vsi_name, add_list,
						     add_head, num_add);
				स_रखो(add_list, 0, list_size);
				num_add = 0;
			पूर्ण
		पूर्ण
		अगर (num_add) अणु
			i40e_aqc_add_filters(vsi, vsi_name, add_list, add_head,
					     num_add);
		पूर्ण
		/* Now move all of the filters from the temp add list back to
		 * the VSI's list.
		 */
		spin_lock_bh(&vsi->mac_filter_hash_lock);
		hlist_क्रम_each_entry_safe(new, h, &पंचांगp_add_list, hlist) अणु
			/* Only update the state अगर we're still NEW */
			अगर (new->f->state == I40E_FILTER_NEW)
				new->f->state = new->state;
			hlist_del(&new->hlist);
			kमुक्त(new);
		पूर्ण
		spin_unlock_bh(&vsi->mac_filter_hash_lock);
		kमुक्त(add_list);
		add_list = शून्य;
	पूर्ण

	/* Determine the number of active and failed filters. */
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	vsi->active_filters = 0;
	hash_क्रम_each(vsi->mac_filter_hash, bkt, f, hlist) अणु
		अगर (f->state == I40E_FILTER_ACTIVE)
			vsi->active_filters++;
		अन्यथा अगर (f->state == I40E_FILTER_FAILED)
			failed_filters++;
	पूर्ण
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* Check अगर we are able to निकास overflow promiscuous mode. We can
	 * safely निकास अगर we didn't just enter, we no दीर्घer have any failed
	 * filters, and we have reduced filters below the threshold value.
	 */
	अगर (old_overflow && !failed_filters &&
	    vsi->active_filters < vsi->promisc_threshold) अणु
		dev_info(&pf->pdev->dev,
			 "filter logjam cleared on %s, leaving overflow promiscuous mode\n",
			 vsi_name);
		clear_bit(__I40E_VSI_OVERFLOW_PROMISC, vsi->state);
		vsi->promisc_threshold = 0;
	पूर्ण

	/* अगर the VF is not trusted करो not करो promisc */
	अगर ((vsi->type == I40E_VSI_SRIOV) && !pf->vf[vsi->vf_id].trusted) अणु
		clear_bit(__I40E_VSI_OVERFLOW_PROMISC, vsi->state);
		जाओ out;
	पूर्ण

	new_overflow = test_bit(__I40E_VSI_OVERFLOW_PROMISC, vsi->state);

	/* If we are entering overflow promiscuous, we need to calculate a new
	 * threshold क्रम when we are safe to निकास
	 */
	अगर (!old_overflow && new_overflow)
		vsi->promisc_threshold = (vsi->active_filters * 3) / 4;

	/* check क्रम changes in promiscuous modes */
	अगर (changed_flags & IFF_ALLMULTI) अणु
		bool cur_multipromisc;

		cur_multipromisc = !!(vsi->current_netdev_flags & IFF_ALLMULTI);
		aq_ret = i40e_aq_set_vsi_multicast_promiscuous(&vsi->back->hw,
							       vsi->seid,
							       cur_multipromisc,
							       शून्य);
		अगर (aq_ret) अणु
			retval = i40e_aq_rc_to_posix(aq_ret,
						     hw->aq.asq_last_status);
			dev_info(&pf->pdev->dev,
				 "set multi promisc failed on %s, err %s aq_err %s\n",
				 vsi_name,
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		पूर्ण अन्यथा अणु
			dev_info(&pf->pdev->dev, "%s allmulti mode.\n",
				 cur_multipromisc ? "entering" : "leaving");
		पूर्ण
	पूर्ण

	अगर ((changed_flags & IFF_PROMISC) || old_overflow != new_overflow) अणु
		bool cur_promisc;

		cur_promisc = (!!(vsi->current_netdev_flags & IFF_PROMISC) ||
			       new_overflow);
		aq_ret = i40e_set_promiscuous(pf, cur_promisc);
		अगर (aq_ret) अणु
			retval = i40e_aq_rc_to_posix(aq_ret,
						     hw->aq.asq_last_status);
			dev_info(&pf->pdev->dev,
				 "Setting promiscuous %s failed on %s, err %s aq_err %s\n",
				 cur_promisc ? "on" : "off",
				 vsi_name,
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		पूर्ण
	पूर्ण
out:
	/* अगर something went wrong then set the changed flag so we try again */
	अगर (retval)
		vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;

	clear_bit(__I40E_VSI_SYNCING_FILTERS, vsi->state);
	वापस retval;

err_no_memory:
	/* Restore elements on the temporary add and delete lists */
	spin_lock_bh(&vsi->mac_filter_hash_lock);
err_no_memory_locked:
	i40e_unकरो_del_filter_entries(vsi, &पंचांगp_del_list);
	i40e_unकरो_add_filter_entries(vsi, &पंचांगp_add_list);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;
	clear_bit(__I40E_VSI_SYNCING_FILTERS, vsi->state);
	वापस -ENOMEM;
पूर्ण

/**
 * i40e_sync_filters_subtask - Sync the VSI filter list with HW
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_sync_filters_subtask(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक v;

	अगर (!pf)
		वापस;
	अगर (!test_and_clear_bit(__I40E_MACVLAN_SYNC_PENDING, pf->state))
		वापस;
	अगर (test_bit(__I40E_VF_DISABLE, pf->state)) अणु
		set_bit(__I40E_MACVLAN_SYNC_PENDING, pf->state);
		वापस;
	पूर्ण

	क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
		अगर (pf->vsi[v] &&
		    (pf->vsi[v]->flags & I40E_VSI_FLAG_FILTER_CHANGED)) अणु
			पूर्णांक ret = i40e_sync_vsi_filters(pf->vsi[v]);

			अगर (ret) अणु
				/* come back and try again later */
				set_bit(__I40E_MACVLAN_SYNC_PENDING,
					pf->state);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_max_xdp_frame_size - वापसs the maximum allowed frame size क्रम XDP
 * @vsi: the vsi
 **/
अटल पूर्णांक i40e_max_xdp_frame_size(काष्ठा i40e_vsi *vsi)
अणु
	अगर (PAGE_SIZE >= 8192 || (vsi->back->flags & I40E_FLAG_LEGACY_RX))
		वापस I40E_RXBUFFER_2048;
	अन्यथा
		वापस I40E_RXBUFFER_3072;
पूर्ण

/**
 * i40e_change_mtu - NDO callback to change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;

	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		पूर्णांक frame_size = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;

		अगर (frame_size > i40e_max_xdp_frame_size(vsi))
			वापस -EINVAL;
	पूर्ण

	netdev_dbg(netdev, "changing MTU from %d to %d\n",
		   netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;
	अगर (netअगर_running(netdev))
		i40e_vsi_reinit_locked(vsi);
	set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
	set_bit(__I40E_CLIENT_L2_CHANGE, pf->state);
	वापस 0;
पूर्ण

/**
 * i40e_ioctl - Access the hwtstamp पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @अगरr: पूर्णांकerface request data
 * @cmd: ioctl command
 **/
पूर्णांक i40e_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;

	चयन (cmd) अणु
	हाल SIOCGHWTSTAMP:
		वापस i40e_ptp_get_ts_config(pf, अगरr);
	हाल SIOCSHWTSTAMP:
		वापस i40e_ptp_set_ts_config(pf, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * i40e_vlan_stripping_enable - Turn on vlan stripping क्रम the VSI
 * @vsi: the vsi being adjusted
 **/
व्योम i40e_vlan_stripping_enable(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_vsi_context ctxt;
	i40e_status ret;

	/* Don't modअगरy stripping options अगर a port VLAN is active */
	अगर (vsi->info.pvid)
		वापस;

	अगर ((vsi->info.valid_sections &
	     cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID)) &&
	    ((vsi->info.port_vlan_flags & I40E_AQ_VSI_PVLAN_MODE_MASK) == 0))
		वापस;  /* alपढ़ोy enabled */

	vsi->info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID);
	vsi->info.port_vlan_flags = I40E_AQ_VSI_PVLAN_MODE_ALL |
				    I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH;

	ctxt.seid = vsi->seid;
	ctxt.info = vsi->info;
	ret = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&vsi->back->pdev->dev,
			 "update vlan stripping failed, err %s aq_err %s\n",
			 i40e_stat_str(&vsi->back->hw, ret),
			 i40e_aq_str(&vsi->back->hw,
				     vsi->back->hw.aq.asq_last_status));
	पूर्ण
पूर्ण

/**
 * i40e_vlan_stripping_disable - Turn off vlan stripping क्रम the VSI
 * @vsi: the vsi being adjusted
 **/
व्योम i40e_vlan_stripping_disable(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_vsi_context ctxt;
	i40e_status ret;

	/* Don't modअगरy stripping options अगर a port VLAN is active */
	अगर (vsi->info.pvid)
		वापस;

	अगर ((vsi->info.valid_sections &
	     cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID)) &&
	    ((vsi->info.port_vlan_flags & I40E_AQ_VSI_PVLAN_EMOD_MASK) ==
	     I40E_AQ_VSI_PVLAN_EMOD_MASK))
		वापस;  /* alपढ़ोy disabled */

	vsi->info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID);
	vsi->info.port_vlan_flags = I40E_AQ_VSI_PVLAN_MODE_ALL |
				    I40E_AQ_VSI_PVLAN_EMOD_NOTHING;

	ctxt.seid = vsi->seid;
	ctxt.info = vsi->info;
	ret = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&vsi->back->pdev->dev,
			 "update vlan stripping failed, err %s aq_err %s\n",
			 i40e_stat_str(&vsi->back->hw, ret),
			 i40e_aq_str(&vsi->back->hw,
				     vsi->back->hw.aq.asq_last_status));
	पूर्ण
पूर्ण

/**
 * i40e_add_vlan_all_mac - Add a MAC/VLAN filter क्रम each existing MAC address
 * @vsi: the vsi being configured
 * @vid: vlan id to be added (0 = untagged only , -1 = any)
 *
 * This is a helper function क्रम adding a new MAC/VLAN filter with the
 * specअगरied VLAN क्रम each existing MAC address alपढ़ोy in the hash table.
 * This function करोes *not* perक्रमm any accounting to update filters based on
 * VLAN mode.
 *
 * NOTE: this function expects to be called जबतक under the
 * mac_filter_hash_lock
 **/
पूर्णांक i40e_add_vlan_all_mac(काष्ठा i40e_vsi *vsi, s16 vid)
अणु
	काष्ठा i40e_mac_filter *f, *add_f;
	काष्ठा hlist_node *h;
	पूर्णांक bkt;

	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
		अगर (f->state == I40E_FILTER_REMOVE)
			जारी;
		add_f = i40e_add_filter(vsi, f->macaddr, vid);
		अगर (!add_f) अणु
			dev_info(&vsi->back->pdev->dev,
				 "Could not add vlan filter %d for %pM\n",
				 vid, f->macaddr);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vsi_add_vlan - Add VSI membership क्रम given VLAN
 * @vsi: the VSI being configured
 * @vid: VLAN id to be added
 **/
पूर्णांक i40e_vsi_add_vlan(काष्ठा i40e_vsi *vsi, u16 vid)
अणु
	पूर्णांक err;

	अगर (vsi->info.pvid)
		वापस -EINVAL;

	/* The network stack will attempt to add VID=0, with the पूर्णांकention to
	 * receive priority tagged packets with a VLAN of 0. Our HW receives
	 * these packets by शेष when configured to receive untagged
	 * packets, so we करोn't need to add a filter क्रम this हाल.
	 * Additionally, HW पूर्णांकerprets adding a VID=0 filter as meaning to
	 * receive *only* tagged traffic and stops receiving untagged traffic.
	 * Thus, we करो not want to actually add a filter क्रम VID=0
	 */
	अगर (!vid)
		वापस 0;

	/* Locked once because all functions invoked below iterates list*/
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	err = i40e_add_vlan_all_mac(vsi, vid);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);
	अगर (err)
		वापस err;

	/* schedule our worker thपढ़ो which will take care of
	 * applying the new filter changes
	 */
	i40e_service_event_schedule(vsi->back);
	वापस 0;
पूर्ण

/**
 * i40e_rm_vlan_all_mac - Remove MAC/VLAN pair क्रम all MAC with the given VLAN
 * @vsi: the vsi being configured
 * @vid: vlan id to be हटाओd (0 = untagged only , -1 = any)
 *
 * This function should be used to हटाओ all VLAN filters which match the
 * given VID. It करोes not schedule the service event and करोes not take the
 * mac_filter_hash_lock so it may be combined with other operations under
 * a single invocation of the mac_filter_hash_lock.
 *
 * NOTE: this function expects to be called जबतक under the
 * mac_filter_hash_lock
 */
व्योम i40e_rm_vlan_all_mac(काष्ठा i40e_vsi *vsi, s16 vid)
अणु
	काष्ठा i40e_mac_filter *f;
	काष्ठा hlist_node *h;
	पूर्णांक bkt;

	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
		अगर (f->vlan == vid)
			__i40e_del_filter(vsi, f);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_समाप्त_vlan - Remove VSI membership क्रम given VLAN
 * @vsi: the VSI being configured
 * @vid: VLAN id to be हटाओd
 **/
व्योम i40e_vsi_समाप्त_vlan(काष्ठा i40e_vsi *vsi, u16 vid)
अणु
	अगर (!vid || vsi->info.pvid)
		वापस;

	spin_lock_bh(&vsi->mac_filter_hash_lock);
	i40e_rm_vlan_all_mac(vsi, vid);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* schedule our worker thपढ़ो which will take care of
	 * applying the new filter changes
	 */
	i40e_service_event_schedule(vsi->back);
पूर्ण

/**
 * i40e_vlan_rx_add_vid - Add a vlan id filter to HW offload
 * @netdev: network पूर्णांकerface to be adjusted
 * @proto: unused protocol value
 * @vid: vlan id to be added
 *
 * net_device_ops implementation क्रम adding vlan ids
 **/
अटल पूर्णांक i40e_vlan_rx_add_vid(काष्ठा net_device *netdev,
				__always_unused __be16 proto, u16 vid)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	पूर्णांक ret = 0;

	अगर (vid >= VLAN_N_VID)
		वापस -EINVAL;

	ret = i40e_vsi_add_vlan(vsi, vid);
	अगर (!ret)
		set_bit(vid, vsi->active_vlans);

	वापस ret;
पूर्ण

/**
 * i40e_vlan_rx_add_vid_up - Add a vlan id filter to HW offload in UP path
 * @netdev: network पूर्णांकerface to be adjusted
 * @proto: unused protocol value
 * @vid: vlan id to be added
 **/
अटल व्योम i40e_vlan_rx_add_vid_up(काष्ठा net_device *netdev,
				    __always_unused __be16 proto, u16 vid)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	अगर (vid >= VLAN_N_VID)
		वापस;
	set_bit(vid, vsi->active_vlans);
पूर्ण

/**
 * i40e_vlan_rx_समाप्त_vid - Remove a vlan id filter from HW offload
 * @netdev: network पूर्णांकerface to be adjusted
 * @proto: unused protocol value
 * @vid: vlan id to be हटाओd
 *
 * net_device_ops implementation क्रम removing vlan ids
 **/
अटल पूर्णांक i40e_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				 __always_unused __be16 proto, u16 vid)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	/* वापस code is ignored as there is nothing a user
	 * can करो about failure to हटाओ and a log message was
	 * alपढ़ोy prपूर्णांकed from the other function
	 */
	i40e_vsi_समाप्त_vlan(vsi, vid);

	clear_bit(vid, vsi->active_vlans);

	वापस 0;
पूर्ण

/**
 * i40e_restore_vlan - Reinstate vlans when vsi/netdev comes back up
 * @vsi: the vsi being brought back up
 **/
अटल व्योम i40e_restore_vlan(काष्ठा i40e_vsi *vsi)
अणु
	u16 vid;

	अगर (!vsi->netdev)
		वापस;

	अगर (vsi->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		i40e_vlan_stripping_enable(vsi);
	अन्यथा
		i40e_vlan_stripping_disable(vsi);

	क्रम_each_set_bit(vid, vsi->active_vlans, VLAN_N_VID)
		i40e_vlan_rx_add_vid_up(vsi->netdev, htons(ETH_P_8021Q),
					vid);
पूर्ण

/**
 * i40e_vsi_add_pvid - Add pvid क्रम the VSI
 * @vsi: the vsi being adjusted
 * @vid: the vlan id to set as a PVID
 **/
पूर्णांक i40e_vsi_add_pvid(काष्ठा i40e_vsi *vsi, u16 vid)
अणु
	काष्ठा i40e_vsi_context ctxt;
	i40e_status ret;

	vsi->info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID);
	vsi->info.pvid = cpu_to_le16(vid);
	vsi->info.port_vlan_flags = I40E_AQ_VSI_PVLAN_MODE_TAGGED |
				    I40E_AQ_VSI_PVLAN_INSERT_PVID |
				    I40E_AQ_VSI_PVLAN_EMOD_STR;

	ctxt.seid = vsi->seid;
	ctxt.info = vsi->info;
	ret = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&vsi->back->pdev->dev,
			 "add pvid failed, err %s aq_err %s\n",
			 i40e_stat_str(&vsi->back->hw, ret),
			 i40e_aq_str(&vsi->back->hw,
				     vsi->back->hw.aq.asq_last_status));
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vsi_हटाओ_pvid - Remove the pvid from the VSI
 * @vsi: the vsi being adjusted
 *
 * Just use the vlan_rx_रेजिस्टर() service to put it back to normal
 **/
व्योम i40e_vsi_हटाओ_pvid(काष्ठा i40e_vsi *vsi)
अणु
	vsi->info.pvid = 0;

	i40e_vlan_stripping_disable(vsi);
पूर्ण

/**
 * i40e_vsi_setup_tx_resources - Allocate VSI Tx queue resources
 * @vsi: ptr to the VSI
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_vsi_setup_tx_resources(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < vsi->num_queue_pairs && !err; i++)
		err = i40e_setup_tx_descriptors(vsi->tx_rings[i]);

	अगर (!i40e_enabled_xdp_vsi(vsi))
		वापस err;

	क्रम (i = 0; i < vsi->num_queue_pairs && !err; i++)
		err = i40e_setup_tx_descriptors(vsi->xdp_rings[i]);

	वापस err;
पूर्ण

/**
 * i40e_vsi_मुक्त_tx_resources - Free Tx resources क्रम VSI queues
 * @vsi: ptr to the VSI
 *
 * Free VSI's transmit software resources
 **/
अटल व्योम i40e_vsi_मुक्त_tx_resources(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक i;

	अगर (vsi->tx_rings) अणु
		क्रम (i = 0; i < vsi->num_queue_pairs; i++)
			अगर (vsi->tx_rings[i] && vsi->tx_rings[i]->desc)
				i40e_मुक्त_tx_resources(vsi->tx_rings[i]);
	पूर्ण

	अगर (vsi->xdp_rings) अणु
		क्रम (i = 0; i < vsi->num_queue_pairs; i++)
			अगर (vsi->xdp_rings[i] && vsi->xdp_rings[i]->desc)
				i40e_मुक्त_tx_resources(vsi->xdp_rings[i]);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_setup_rx_resources - Allocate VSI queues Rx resources
 * @vsi: ptr to the VSI
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_vsi_setup_rx_resources(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < vsi->num_queue_pairs && !err; i++)
		err = i40e_setup_rx_descriptors(vsi->rx_rings[i]);
	वापस err;
पूर्ण

/**
 * i40e_vsi_मुक्त_rx_resources - Free Rx Resources क्रम VSI queues
 * @vsi: ptr to the VSI
 *
 * Free all receive software resources
 **/
अटल व्योम i40e_vsi_मुक्त_rx_resources(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक i;

	अगर (!vsi->rx_rings)
		वापस;

	क्रम (i = 0; i < vsi->num_queue_pairs; i++)
		अगर (vsi->rx_rings[i] && vsi->rx_rings[i]->desc)
			i40e_मुक्त_rx_resources(vsi->rx_rings[i]);
पूर्ण

/**
 * i40e_config_xps_tx_ring - Configure XPS क्रम a Tx ring
 * @ring: The Tx ring to configure
 *
 * This enables/disables XPS क्रम a given Tx descriptor ring
 * based on the TCs enabled क्रम the VSI that ring beदीर्घs to.
 **/
अटल व्योम i40e_config_xps_tx_ring(काष्ठा i40e_ring *ring)
अणु
	पूर्णांक cpu;

	अगर (!ring->q_vector || !ring->netdev || ring->ch)
		वापस;

	/* We only initialize XPS once, so as not to overग_लिखो user settings */
	अगर (test_and_set_bit(__I40E_TX_XPS_INIT_DONE, ring->state))
		वापस;

	cpu = cpumask_local_spपढ़ो(ring->q_vector->v_idx, -1);
	netअगर_set_xps_queue(ring->netdev, get_cpu_mask(cpu),
			    ring->queue_index);
पूर्ण

/**
 * i40e_xsk_pool - Retrieve the AF_XDP buffer pool अगर XDP and ZC is enabled
 * @ring: The Tx or Rx ring
 *
 * Returns the AF_XDP buffer pool or शून्य.
 **/
अटल काष्ठा xsk_buff_pool *i40e_xsk_pool(काष्ठा i40e_ring *ring)
अणु
	bool xdp_on = i40e_enabled_xdp_vsi(ring->vsi);
	पूर्णांक qid = ring->queue_index;

	अगर (ring_is_xdp(ring))
		qid -= ring->vsi->alloc_queue_pairs;

	अगर (!xdp_on || !test_bit(qid, ring->vsi->af_xdp_zc_qps))
		वापस शून्य;

	वापस xsk_get_pool_from_qid(ring->vsi->netdev, qid);
पूर्ण

/**
 * i40e_configure_tx_ring - Configure a transmit ring context and rest
 * @ring: The Tx ring to configure
 *
 * Configure the Tx descriptor ring in the HMC context.
 **/
अटल पूर्णांक i40e_configure_tx_ring(काष्ठा i40e_ring *ring)
अणु
	काष्ठा i40e_vsi *vsi = ring->vsi;
	u16 pf_q = vsi->base_queue + ring->queue_index;
	काष्ठा i40e_hw *hw = &vsi->back->hw;
	काष्ठा i40e_hmc_obj_txq tx_ctx;
	i40e_status err = 0;
	u32 qtx_ctl = 0;

	अगर (ring_is_xdp(ring))
		ring->xsk_pool = i40e_xsk_pool(ring);

	/* some ATR related tx ring init */
	अगर (vsi->back->flags & I40E_FLAG_FD_ATR_ENABLED) अणु
		ring->atr_sample_rate = vsi->back->atr_sample_rate;
		ring->atr_count = 0;
	पूर्ण अन्यथा अणु
		ring->atr_sample_rate = 0;
	पूर्ण

	/* configure XPS */
	i40e_config_xps_tx_ring(ring);

	/* clear the context काष्ठाure first */
	स_रखो(&tx_ctx, 0, माप(tx_ctx));

	tx_ctx.new_context = 1;
	tx_ctx.base = (ring->dma / 128);
	tx_ctx.qlen = ring->count;
	tx_ctx.fd_ena = !!(vsi->back->flags & (I40E_FLAG_FD_SB_ENABLED |
					       I40E_FLAG_FD_ATR_ENABLED));
	tx_ctx.बारync_ena = !!(vsi->back->flags & I40E_FLAG_PTP);
	/* Fसूची VSI tx ring can still use RS bit and ग_लिखोbacks */
	अगर (vsi->type != I40E_VSI_Fसूची)
		tx_ctx.head_wb_ena = 1;
	tx_ctx.head_wb_addr = ring->dma +
			      (ring->count * माप(काष्ठा i40e_tx_desc));

	/* As part of VSI creation/update, FW allocates certain
	 * Tx arbitration queue sets क्रम each TC enabled क्रम
	 * the VSI. The FW वापसs the handles to these queue
	 * sets as part of the response buffer to Add VSI,
	 * Update VSI, etc. AQ commands. It is expected that
	 * these queue set handles be associated with the Tx
	 * queues by the driver as part of the TX queue context
	 * initialization. This has to be करोne regardless of
	 * DCB as by शेष everything is mapped to TC0.
	 */

	अगर (ring->ch)
		tx_ctx.rdylist =
			le16_to_cpu(ring->ch->info.qs_handle[ring->dcb_tc]);

	अन्यथा
		tx_ctx.rdylist = le16_to_cpu(vsi->info.qs_handle[ring->dcb_tc]);

	tx_ctx.rdylist_act = 0;

	/* clear the context in the HMC */
	err = i40e_clear_lan_tx_queue_context(hw, pf_q);
	अगर (err) अणु
		dev_info(&vsi->back->pdev->dev,
			 "Failed to clear LAN Tx queue context on Tx ring %d (pf_q %d), error: %d\n",
			 ring->queue_index, pf_q, err);
		वापस -ENOMEM;
	पूर्ण

	/* set the context in the HMC */
	err = i40e_set_lan_tx_queue_context(hw, pf_q, &tx_ctx);
	अगर (err) अणु
		dev_info(&vsi->back->pdev->dev,
			 "Failed to set LAN Tx queue context on Tx ring %d (pf_q %d, error: %d\n",
			 ring->queue_index, pf_q, err);
		वापस -ENOMEM;
	पूर्ण

	/* Now associate this queue with this PCI function */
	अगर (ring->ch) अणु
		अगर (ring->ch->type == I40E_VSI_VMDQ2)
			qtx_ctl = I40E_QTX_CTL_VM_QUEUE;
		अन्यथा
			वापस -EINVAL;

		qtx_ctl |= (ring->ch->vsi_number <<
			    I40E_QTX_CTL_VFVM_INDX_SHIFT) &
			    I40E_QTX_CTL_VFVM_INDX_MASK;
	पूर्ण अन्यथा अणु
		अगर (vsi->type == I40E_VSI_VMDQ2) अणु
			qtx_ctl = I40E_QTX_CTL_VM_QUEUE;
			qtx_ctl |= ((vsi->id) << I40E_QTX_CTL_VFVM_INDX_SHIFT) &
				    I40E_QTX_CTL_VFVM_INDX_MASK;
		पूर्ण अन्यथा अणु
			qtx_ctl = I40E_QTX_CTL_PF_QUEUE;
		पूर्ण
	पूर्ण

	qtx_ctl |= ((hw->pf_id << I40E_QTX_CTL_PF_INDX_SHIFT) &
		    I40E_QTX_CTL_PF_INDX_MASK);
	wr32(hw, I40E_QTX_CTL(pf_q), qtx_ctl);
	i40e_flush(hw);

	/* cache tail off क्रम easier ग_लिखोs later */
	ring->tail = hw->hw_addr + I40E_QTX_TAIL(pf_q);

	वापस 0;
पूर्ण

/**
 * i40e_rx_offset - Return expected offset पूर्णांकo page to access data
 * @rx_ring: Ring we are requesting offset of
 *
 * Returns the offset value क्रम ring पूर्णांकo the data buffer.
 */
अटल अचिन्हित पूर्णांक i40e_rx_offset(काष्ठा i40e_ring *rx_ring)
अणु
	वापस ring_uses_build_skb(rx_ring) ? I40E_SKB_PAD : 0;
पूर्ण

/**
 * i40e_configure_rx_ring - Configure a receive ring context
 * @ring: The Rx ring to configure
 *
 * Configure the Rx descriptor ring in the HMC context.
 **/
अटल पूर्णांक i40e_configure_rx_ring(काष्ठा i40e_ring *ring)
अणु
	काष्ठा i40e_vsi *vsi = ring->vsi;
	u32 chain_len = vsi->back->hw.func_caps.rx_buf_chain_len;
	u16 pf_q = vsi->base_queue + ring->queue_index;
	काष्ठा i40e_hw *hw = &vsi->back->hw;
	काष्ठा i40e_hmc_obj_rxq rx_ctx;
	i40e_status err = 0;
	bool ok;
	पूर्णांक ret;

	biपंचांगap_zero(ring->state, __I40E_RING_STATE_NBITS);

	/* clear the context काष्ठाure first */
	स_रखो(&rx_ctx, 0, माप(rx_ctx));

	अगर (ring->vsi->type == I40E_VSI_MAIN)
		xdp_rxq_info_unreg_mem_model(&ring->xdp_rxq);

	kमुक्त(ring->rx_bi);
	ring->xsk_pool = i40e_xsk_pool(ring);
	अगर (ring->xsk_pool) अणु
		ret = i40e_alloc_rx_bi_zc(ring);
		अगर (ret)
			वापस ret;
		ring->rx_buf_len =
		  xsk_pool_get_rx_frame_size(ring->xsk_pool);
		/* For AF_XDP ZC, we disallow packets to span on
		 * multiple buffers, thus letting us skip that
		 * handling in the fast-path.
		 */
		chain_len = 1;
		ret = xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
						 MEM_TYPE_XSK_BUFF_POOL,
						 शून्य);
		अगर (ret)
			वापस ret;
		dev_info(&vsi->back->pdev->dev,
			 "Registered XDP mem model MEM_TYPE_XSK_BUFF_POOL on Rx ring %d\n",
			 ring->queue_index);

	पूर्ण अन्यथा अणु
		ret = i40e_alloc_rx_bi(ring);
		अगर (ret)
			वापस ret;
		ring->rx_buf_len = vsi->rx_buf_len;
		अगर (ring->vsi->type == I40E_VSI_MAIN) अणु
			ret = xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
							 MEM_TYPE_PAGE_SHARED,
							 शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	rx_ctx.dbuff = DIV_ROUND_UP(ring->rx_buf_len,
				    BIT_ULL(I40E_RXQ_CTX_DBUFF_SHIFT));

	rx_ctx.base = (ring->dma / 128);
	rx_ctx.qlen = ring->count;

	/* use 16 byte descriptors */
	rx_ctx.dsize = 0;

	/* descriptor type is always zero
	 * rx_ctx.dtype = 0;
	 */
	rx_ctx.hsplit_0 = 0;

	rx_ctx.rxmax = min_t(u16, vsi->max_frame, chain_len * ring->rx_buf_len);
	अगर (hw->revision_id == 0)
		rx_ctx.lrxqthresh = 0;
	अन्यथा
		rx_ctx.lrxqthresh = 1;
	rx_ctx.crcstrip = 1;
	rx_ctx.l2tsel = 1;
	/* this controls whether VLAN is stripped from inner headers */
	rx_ctx.showiv = 0;
	/* set the prefena field to 1 because the manual says to */
	rx_ctx.prefena = 1;

	/* clear the context in the HMC */
	err = i40e_clear_lan_rx_queue_context(hw, pf_q);
	अगर (err) अणु
		dev_info(&vsi->back->pdev->dev,
			 "Failed to clear LAN Rx queue context on Rx ring %d (pf_q %d), error: %d\n",
			 ring->queue_index, pf_q, err);
		वापस -ENOMEM;
	पूर्ण

	/* set the context in the HMC */
	err = i40e_set_lan_rx_queue_context(hw, pf_q, &rx_ctx);
	अगर (err) अणु
		dev_info(&vsi->back->pdev->dev,
			 "Failed to set LAN Rx queue context on Rx ring %d (pf_q %d), error: %d\n",
			 ring->queue_index, pf_q, err);
		वापस -ENOMEM;
	पूर्ण

	/* configure Rx buffer alignment */
	अगर (!vsi->netdev || (vsi->back->flags & I40E_FLAG_LEGACY_RX))
		clear_ring_build_skb_enabled(ring);
	अन्यथा
		set_ring_build_skb_enabled(ring);

	ring->rx_offset = i40e_rx_offset(ring);

	/* cache tail क्रम quicker ग_लिखोs, and clear the reg beक्रमe use */
	ring->tail = hw->hw_addr + I40E_QRX_TAIL(pf_q);
	ग_लिखोl(0, ring->tail);

	अगर (ring->xsk_pool) अणु
		xsk_pool_set_rxq_info(ring->xsk_pool, &ring->xdp_rxq);
		ok = i40e_alloc_rx_buffers_zc(ring, I40E_DESC_UNUSED(ring));
	पूर्ण अन्यथा अणु
		ok = !i40e_alloc_rx_buffers(ring, I40E_DESC_UNUSED(ring));
	पूर्ण
	अगर (!ok) अणु
		/* Log this in हाल the user has क्रमgotten to give the kernel
		 * any buffers, even later in the application.
		 */
		dev_info(&vsi->back->pdev->dev,
			 "Failed to allocate some buffers on %sRx ring %d (pf_q %d)\n",
			 ring->xsk_pool ? "AF_XDP ZC enabled " : "",
			 ring->queue_index, pf_q);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vsi_configure_tx - Configure the VSI क्रम Tx
 * @vsi: VSI काष्ठाure describing this set of rings and resources
 *
 * Configure the Tx VSI क्रम operation.
 **/
अटल पूर्णांक i40e_vsi_configure_tx(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक err = 0;
	u16 i;

	क्रम (i = 0; (i < vsi->num_queue_pairs) && !err; i++)
		err = i40e_configure_tx_ring(vsi->tx_rings[i]);

	अगर (err || !i40e_enabled_xdp_vsi(vsi))
		वापस err;

	क्रम (i = 0; (i < vsi->num_queue_pairs) && !err; i++)
		err = i40e_configure_tx_ring(vsi->xdp_rings[i]);

	वापस err;
पूर्ण

/**
 * i40e_vsi_configure_rx - Configure the VSI क्रम Rx
 * @vsi: the VSI being configured
 *
 * Configure the Rx VSI क्रम operation.
 **/
अटल पूर्णांक i40e_vsi_configure_rx(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक err = 0;
	u16 i;

	अगर (!vsi->netdev || (vsi->back->flags & I40E_FLAG_LEGACY_RX)) अणु
		vsi->max_frame = I40E_MAX_RXBUFFER;
		vsi->rx_buf_len = I40E_RXBUFFER_2048;
#अगर (PAGE_SIZE < 8192)
	पूर्ण अन्यथा अगर (!I40E_2K_TOO_SMALL_WITH_PADDING &&
		   (vsi->netdev->mtu <= ETH_DATA_LEN)) अणु
		vsi->max_frame = I40E_RXBUFFER_1536 - NET_IP_ALIGN;
		vsi->rx_buf_len = I40E_RXBUFFER_1536 - NET_IP_ALIGN;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		vsi->max_frame = I40E_MAX_RXBUFFER;
		vsi->rx_buf_len = (PAGE_SIZE < 8192) ? I40E_RXBUFFER_3072 :
						       I40E_RXBUFFER_2048;
	पूर्ण

	/* set up inभागidual rings */
	क्रम (i = 0; i < vsi->num_queue_pairs && !err; i++)
		err = i40e_configure_rx_ring(vsi->rx_rings[i]);

	वापस err;
पूर्ण

/**
 * i40e_vsi_config_dcb_rings - Update rings to reflect DCB TC
 * @vsi: ptr to the VSI
 **/
अटल व्योम i40e_vsi_config_dcb_rings(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_ring *tx_ring, *rx_ring;
	u16 qoffset, qcount;
	पूर्णांक i, n;

	अगर (!(vsi->back->flags & I40E_FLAG_DCB_ENABLED)) अणु
		/* Reset the TC inक्रमmation */
		क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
			rx_ring = vsi->rx_rings[i];
			tx_ring = vsi->tx_rings[i];
			rx_ring->dcb_tc = 0;
			tx_ring->dcb_tc = 0;
		पूर्ण
		वापस;
	पूर्ण

	क्रम (n = 0; n < I40E_MAX_TRAFFIC_CLASS; n++) अणु
		अगर (!(vsi->tc_config.enabled_tc & BIT_ULL(n)))
			जारी;

		qoffset = vsi->tc_config.tc_info[n].qoffset;
		qcount = vsi->tc_config.tc_info[n].qcount;
		क्रम (i = qoffset; i < (qoffset + qcount); i++) अणु
			rx_ring = vsi->rx_rings[i];
			tx_ring = vsi->tx_rings[i];
			rx_ring->dcb_tc = n;
			tx_ring->dcb_tc = n;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_set_vsi_rx_mode - Call set_rx_mode on a VSI
 * @vsi: ptr to the VSI
 **/
अटल व्योम i40e_set_vsi_rx_mode(काष्ठा i40e_vsi *vsi)
अणु
	अगर (vsi->netdev)
		i40e_set_rx_mode(vsi->netdev);
पूर्ण

/**
 * i40e_reset_fdir_filter_cnt - Reset flow director filter counters
 * @pf: Poपूर्णांकer to the targeted PF
 *
 * Set all flow director counters to 0.
 */
अटल व्योम i40e_reset_fdir_filter_cnt(काष्ठा i40e_pf *pf)
अणु
	pf->fd_tcp4_filter_cnt = 0;
	pf->fd_udp4_filter_cnt = 0;
	pf->fd_sctp4_filter_cnt = 0;
	pf->fd_ip4_filter_cnt = 0;
	pf->fd_tcp6_filter_cnt = 0;
	pf->fd_udp6_filter_cnt = 0;
	pf->fd_sctp6_filter_cnt = 0;
	pf->fd_ip6_filter_cnt = 0;
पूर्ण

/**
 * i40e_fdir_filter_restore - Restore the Sideband Flow Director filters
 * @vsi: Poपूर्णांकer to the targeted VSI
 *
 * This function replays the hlist on the hw where all the SB Flow Director
 * filters were saved.
 **/
अटल व्योम i40e_fdir_filter_restore(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_fdir_filter *filter;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा hlist_node *node;

	अगर (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
		वापस;

	/* Reset FDir counters as we're replaying all existing filters */
	i40e_reset_fdir_filter_cnt(pf);

	hlist_क्रम_each_entry_safe(filter, node,
				  &pf->fdir_filter_list, fdir_node) अणु
		i40e_add_del_fdir(vsi, filter, true);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_configure - Set up the VSI क्रम action
 * @vsi: the VSI being configured
 **/
अटल पूर्णांक i40e_vsi_configure(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक err;

	i40e_set_vsi_rx_mode(vsi);
	i40e_restore_vlan(vsi);
	i40e_vsi_config_dcb_rings(vsi);
	err = i40e_vsi_configure_tx(vsi);
	अगर (!err)
		err = i40e_vsi_configure_rx(vsi);

	वापस err;
पूर्ण

/**
 * i40e_vsi_configure_msix - MSIX mode Interrupt Config in the HW
 * @vsi: the VSI being configured
 **/
अटल व्योम i40e_vsi_configure_msix(काष्ठा i40e_vsi *vsi)
अणु
	bool has_xdp = i40e_enabled_xdp_vsi(vsi);
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 vector;
	पूर्णांक i, q;
	u32 qp;

	/* The पूर्णांकerrupt indexing is offset by 1 in the PFINT_ITRn
	 * and PFINT_LNKLSTn रेजिस्टरs, e.g.:
	 *   PFINT_ITRn[0..n-1] माला_लो msix-1..msix-n  (qpair पूर्णांकerrupts)
	 */
	qp = vsi->base_queue;
	vector = vsi->base_vector;
	क्रम (i = 0; i < vsi->num_q_vectors; i++, vector++) अणु
		काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[i];

		q_vector->rx.next_update = jअगरfies + 1;
		q_vector->rx.target_itr =
			ITR_TO_REG(vsi->rx_rings[i]->itr_setting);
		wr32(hw, I40E_PFINT_ITRN(I40E_RX_ITR, vector - 1),
		     q_vector->rx.target_itr >> 1);
		q_vector->rx.current_itr = q_vector->rx.target_itr;

		q_vector->tx.next_update = jअगरfies + 1;
		q_vector->tx.target_itr =
			ITR_TO_REG(vsi->tx_rings[i]->itr_setting);
		wr32(hw, I40E_PFINT_ITRN(I40E_TX_ITR, vector - 1),
		     q_vector->tx.target_itr >> 1);
		q_vector->tx.current_itr = q_vector->tx.target_itr;

		wr32(hw, I40E_PFINT_RATEN(vector - 1),
		     i40e_पूर्णांकrl_usec_to_reg(vsi->पूर्णांक_rate_limit));

		/* Linked list क्रम the queuepairs asचिन्हित to this vector */
		wr32(hw, I40E_PFINT_LNKLSTN(vector - 1), qp);
		क्रम (q = 0; q < q_vector->num_ringpairs; q++) अणु
			u32 nextqp = has_xdp ? qp + vsi->alloc_queue_pairs : qp;
			u32 val;

			val = I40E_QINT_RQCTL_CAUSE_ENA_MASK |
			      (I40E_RX_ITR << I40E_QINT_RQCTL_ITR_INDX_SHIFT) |
			      (vector << I40E_QINT_RQCTL_MSIX_INDX_SHIFT) |
			      (nextqp << I40E_QINT_RQCTL_NEXTQ_INDX_SHIFT) |
			      (I40E_QUEUE_TYPE_TX <<
			       I40E_QINT_RQCTL_NEXTQ_TYPE_SHIFT);

			wr32(hw, I40E_QINT_RQCTL(qp), val);

			अगर (has_xdp) अणु
				val = I40E_QINT_TQCTL_CAUSE_ENA_MASK |
				      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT) |
				      (vector << I40E_QINT_TQCTL_MSIX_INDX_SHIFT) |
				      (qp << I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT) |
				      (I40E_QUEUE_TYPE_TX <<
				       I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

				wr32(hw, I40E_QINT_TQCTL(nextqp), val);
			पूर्ण

			val = I40E_QINT_TQCTL_CAUSE_ENA_MASK |
			      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT) |
			      (vector << I40E_QINT_TQCTL_MSIX_INDX_SHIFT) |
			      ((qp + 1) << I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT) |
			      (I40E_QUEUE_TYPE_RX <<
			       I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

			/* Terminate the linked list */
			अगर (q == (q_vector->num_ringpairs - 1))
				val |= (I40E_QUEUE_END_OF_LIST <<
					I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT);

			wr32(hw, I40E_QINT_TQCTL(qp), val);
			qp++;
		पूर्ण
	पूर्ण

	i40e_flush(hw);
पूर्ण

/**
 * i40e_enable_misc_पूर्णांक_causes - enable the non-queue पूर्णांकerrupts
 * @pf: poपूर्णांकer to निजी device data काष्ठाure
 **/
अटल व्योम i40e_enable_misc_पूर्णांक_causes(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 val;

	/* clear things first */
	wr32(hw, I40E_PFINT_ICR0_ENA, 0);  /* disable all */
	rd32(hw, I40E_PFINT_ICR0);         /* पढ़ो to clear */

	val = I40E_PFINT_ICR0_ENA_ECC_ERR_MASK       |
	      I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK    |
	      I40E_PFINT_ICR0_ENA_GRST_MASK          |
	      I40E_PFINT_ICR0_ENA_PCI_EXCEPTION_MASK |
	      I40E_PFINT_ICR0_ENA_GPIO_MASK          |
	      I40E_PFINT_ICR0_ENA_HMC_ERR_MASK       |
	      I40E_PFINT_ICR0_ENA_VFLR_MASK          |
	      I40E_PFINT_ICR0_ENA_ADMINQ_MASK;

	अगर (pf->flags & I40E_FLAG_IWARP_ENABLED)
		val |= I40E_PFINT_ICR0_ENA_PE_CRITERR_MASK;

	अगर (pf->flags & I40E_FLAG_PTP)
		val |= I40E_PFINT_ICR0_ENA_TIMESYNC_MASK;

	wr32(hw, I40E_PFINT_ICR0_ENA, val);

	/* SW_ITR_IDX = 0, but करोn't change INTENA */
	wr32(hw, I40E_PFINT_DYN_CTL0, I40E_PFINT_DYN_CTL0_SW_ITR_INDX_MASK |
					I40E_PFINT_DYN_CTL0_INTENA_MSK_MASK);

	/* OTHER_ITR_IDX = 0 */
	wr32(hw, I40E_PFINT_STAT_CTL0, 0);
पूर्ण

/**
 * i40e_configure_msi_and_legacy - Legacy mode पूर्णांकerrupt config in the HW
 * @vsi: the VSI being configured
 **/
अटल व्योम i40e_configure_msi_and_legacy(काष्ठा i40e_vsi *vsi)
अणु
	u32 nextqp = i40e_enabled_xdp_vsi(vsi) ? vsi->alloc_queue_pairs : 0;
	काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[0];
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 val;

	/* set the ITR configuration */
	q_vector->rx.next_update = jअगरfies + 1;
	q_vector->rx.target_itr = ITR_TO_REG(vsi->rx_rings[0]->itr_setting);
	wr32(hw, I40E_PFINT_ITR0(I40E_RX_ITR), q_vector->rx.target_itr >> 1);
	q_vector->rx.current_itr = q_vector->rx.target_itr;
	q_vector->tx.next_update = jअगरfies + 1;
	q_vector->tx.target_itr = ITR_TO_REG(vsi->tx_rings[0]->itr_setting);
	wr32(hw, I40E_PFINT_ITR0(I40E_TX_ITR), q_vector->tx.target_itr >> 1);
	q_vector->tx.current_itr = q_vector->tx.target_itr;

	i40e_enable_misc_पूर्णांक_causes(pf);

	/* FIRSTQ_INDX = 0, FIRSTQ_TYPE = 0 (rx) */
	wr32(hw, I40E_PFINT_LNKLST0, 0);

	/* Associate the queue pair to the vector and enable the queue पूर्णांक */
	val = I40E_QINT_RQCTL_CAUSE_ENA_MASK		       |
	      (I40E_RX_ITR << I40E_QINT_RQCTL_ITR_INDX_SHIFT)  |
	      (nextqp	   << I40E_QINT_RQCTL_NEXTQ_INDX_SHIFT)|
	      (I40E_QUEUE_TYPE_TX << I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

	wr32(hw, I40E_QINT_RQCTL(0), val);

	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		val = I40E_QINT_TQCTL_CAUSE_ENA_MASK		     |
		      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT)|
		      (I40E_QUEUE_TYPE_TX
		       << I40E_QINT_TQCTL_NEXTQ_TYPE_SHIFT);

		wr32(hw, I40E_QINT_TQCTL(nextqp), val);
	पूर्ण

	val = I40E_QINT_TQCTL_CAUSE_ENA_MASK		      |
	      (I40E_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT) |
	      (I40E_QUEUE_END_OF_LIST << I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT);

	wr32(hw, I40E_QINT_TQCTL(0), val);
	i40e_flush(hw);
पूर्ण

/**
 * i40e_irq_dynamic_disable_icr0 - Disable शेष पूर्णांकerrupt generation क्रम icr0
 * @pf: board निजी काष्ठाure
 **/
व्योम i40e_irq_dynamic_disable_icr0(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;

	wr32(hw, I40E_PFINT_DYN_CTL0,
	     I40E_ITR_NONE << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT);
	i40e_flush(hw);
पूर्ण

/**
 * i40e_irq_dynamic_enable_icr0 - Enable शेष पूर्णांकerrupt generation क्रम icr0
 * @pf: board निजी काष्ठाure
 **/
व्योम i40e_irq_dynamic_enable_icr0(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 val;

	val = I40E_PFINT_DYN_CTL0_INTENA_MASK   |
	      I40E_PFINT_DYN_CTL0_CLEARPBA_MASK |
	      (I40E_ITR_NONE << I40E_PFINT_DYN_CTL0_ITR_INDX_SHIFT);

	wr32(hw, I40E_PFINT_DYN_CTL0, val);
	i40e_flush(hw);
पूर्ण

/**
 * i40e_msix_clean_rings - MSIX mode Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 **/
अटल irqवापस_t i40e_msix_clean_rings(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा i40e_q_vector *q_vector = data;

	अगर (!q_vector->tx.ring && !q_vector->rx.ring)
		वापस IRQ_HANDLED;

	napi_schedule_irqoff(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * i40e_irq_affinity_notअगरy - Callback क्रम affinity changes
 * @notअगरy: context as to what irq was changed
 * @mask: the new affinity mask
 *
 * This is a callback function used by the irq_set_affinity_notअगरier function
 * so that we may रेजिस्टर to receive changes to the irq affinity masks.
 **/
अटल व्योम i40e_irq_affinity_notअगरy(काष्ठा irq_affinity_notअगरy *notअगरy,
				     स्थिर cpumask_t *mask)
अणु
	काष्ठा i40e_q_vector *q_vector =
		container_of(notअगरy, काष्ठा i40e_q_vector, affinity_notअगरy);

	cpumask_copy(&q_vector->affinity_mask, mask);
पूर्ण

/**
 * i40e_irq_affinity_release - Callback क्रम affinity notअगरier release
 * @ref: पूर्णांकernal core kernel usage
 *
 * This is a callback function used by the irq_set_affinity_notअगरier function
 * to inक्रमm the current notअगरication subscriber that they will no दीर्घer
 * receive notअगरications.
 **/
अटल व्योम i40e_irq_affinity_release(काष्ठा kref *ref) अणुपूर्ण

/**
 * i40e_vsi_request_irq_msix - Initialize MSI-X पूर्णांकerrupts
 * @vsi: the VSI being configured
 * @basename: name क्रम the vector
 *
 * Allocates MSI-X vectors and requests पूर्णांकerrupts from the kernel.
 **/
अटल पूर्णांक i40e_vsi_request_irq_msix(काष्ठा i40e_vsi *vsi, अक्षर *basename)
अणु
	पूर्णांक q_vectors = vsi->num_q_vectors;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक base = vsi->base_vector;
	पूर्णांक rx_पूर्णांक_idx = 0;
	पूर्णांक tx_पूर्णांक_idx = 0;
	पूर्णांक vector, err;
	पूर्णांक irq_num;
	पूर्णांक cpu;

	क्रम (vector = 0; vector < q_vectors; vector++) अणु
		काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[vector];

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
		err = request_irq(irq_num,
				  vsi->irq_handler,
				  0,
				  q_vector->name,
				  q_vector);
		अगर (err) अणु
			dev_info(&pf->pdev->dev,
				 "MSIX request_irq failed, error: %d\n", err);
			जाओ मुक्त_queue_irqs;
		पूर्ण

		/* रेजिस्टर क्रम affinity change notअगरications */
		q_vector->affinity_notअगरy.notअगरy = i40e_irq_affinity_notअगरy;
		q_vector->affinity_notअगरy.release = i40e_irq_affinity_release;
		irq_set_affinity_notअगरier(irq_num, &q_vector->affinity_notअगरy);
		/* Spपढ़ो affinity hपूर्णांकs out across online CPUs.
		 *
		 * get_cpu_mask वापसs a अटल स्थिरant mask with
		 * a permanent lअगरeसमय so it's ok to pass to
		 * irq_set_affinity_hपूर्णांक without making a copy.
		 */
		cpu = cpumask_local_spपढ़ो(q_vector->v_idx, -1);
		irq_set_affinity_hपूर्णांक(irq_num, get_cpu_mask(cpu));
	पूर्ण

	vsi->irqs_पढ़ोy = true;
	वापस 0;

मुक्त_queue_irqs:
	जबतक (vector) अणु
		vector--;
		irq_num = pf->msix_entries[base + vector].vector;
		irq_set_affinity_notअगरier(irq_num, शून्य);
		irq_set_affinity_hपूर्णांक(irq_num, शून्य);
		मुक्त_irq(irq_num, &vsi->q_vectors[vector]);
	पूर्ण
	वापस err;
पूर्ण

/**
 * i40e_vsi_disable_irq - Mask off queue पूर्णांकerrupt generation on the VSI
 * @vsi: the VSI being un-configured
 **/
अटल व्योम i40e_vsi_disable_irq(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक base = vsi->base_vector;
	पूर्णांक i;

	/* disable पूर्णांकerrupt causation from each queue */
	क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
		u32 val;

		val = rd32(hw, I40E_QINT_TQCTL(vsi->tx_rings[i]->reg_idx));
		val &= ~I40E_QINT_TQCTL_CAUSE_ENA_MASK;
		wr32(hw, I40E_QINT_TQCTL(vsi->tx_rings[i]->reg_idx), val);

		val = rd32(hw, I40E_QINT_RQCTL(vsi->rx_rings[i]->reg_idx));
		val &= ~I40E_QINT_RQCTL_CAUSE_ENA_MASK;
		wr32(hw, I40E_QINT_RQCTL(vsi->rx_rings[i]->reg_idx), val);

		अगर (!i40e_enabled_xdp_vsi(vsi))
			जारी;
		wr32(hw, I40E_QINT_TQCTL(vsi->xdp_rings[i]->reg_idx), 0);
	पूर्ण

	/* disable each पूर्णांकerrupt */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		क्रम (i = vsi->base_vector;
		     i < (vsi->num_q_vectors + vsi->base_vector); i++)
			wr32(hw, I40E_PFINT_DYN_CTLN(i - 1), 0);

		i40e_flush(hw);
		क्रम (i = 0; i < vsi->num_q_vectors; i++)
			synchronize_irq(pf->msix_entries[i + base].vector);
	पूर्ण अन्यथा अणु
		/* Legacy and MSI mode - this stops all पूर्णांकerrupt handling */
		wr32(hw, I40E_PFINT_ICR0_ENA, 0);
		wr32(hw, I40E_PFINT_DYN_CTL0, 0);
		i40e_flush(hw);
		synchronize_irq(pf->pdev->irq);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_enable_irq - Enable IRQ क्रम the given VSI
 * @vsi: the VSI being configured
 **/
अटल पूर्णांक i40e_vsi_enable_irq(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक i;

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		क्रम (i = 0; i < vsi->num_q_vectors; i++)
			i40e_irq_dynamic_enable(vsi, i);
	पूर्ण अन्यथा अणु
		i40e_irq_dynamic_enable_icr0(pf);
	पूर्ण

	i40e_flush(&pf->hw);
	वापस 0;
पूर्ण

/**
 * i40e_मुक्त_misc_vector - Free the vector that handles non-queue events
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_मुक्त_misc_vector(काष्ठा i40e_pf *pf)
अणु
	/* Disable ICR 0 */
	wr32(&pf->hw, I40E_PFINT_ICR0_ENA, 0);
	i40e_flush(&pf->hw);

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED && pf->msix_entries) अणु
		synchronize_irq(pf->msix_entries[0].vector);
		मुक्त_irq(pf->msix_entries[0].vector, pf);
		clear_bit(__I40E_MISC_IRQ_REQUESTED, pf->state);
	पूर्ण
पूर्ण

/**
 * i40e_पूर्णांकr - MSI/Legacy and non-queue पूर्णांकerrupt handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 *
 * This is the handler used क्रम all MSI/Legacy पूर्णांकerrupts, and deals
 * with both queue and non-queue पूर्णांकerrupts.  This is also used in
 * MSIX mode to handle the non-queue पूर्णांकerrupts.
 **/
अटल irqवापस_t i40e_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा i40e_pf *pf = (काष्ठा i40e_pf *)data;
	काष्ठा i40e_hw *hw = &pf->hw;
	irqवापस_t ret = IRQ_NONE;
	u32 icr0, icr0_reमुख्यing;
	u32 val, ena_mask;

	icr0 = rd32(hw, I40E_PFINT_ICR0);
	ena_mask = rd32(hw, I40E_PFINT_ICR0_ENA);

	/* अगर sharing a legacy IRQ, we might get called w/o an पूर्णांकr pending */
	अगर ((icr0 & I40E_PFINT_ICR0_INTEVENT_MASK) == 0)
		जाओ enable_पूर्णांकr;

	/* अगर पूर्णांकerrupt but no bits showing, must be SWINT */
	अगर (((icr0 & ~I40E_PFINT_ICR0_INTEVENT_MASK) == 0) ||
	    (icr0 & I40E_PFINT_ICR0_SWINT_MASK))
		pf->sw_पूर्णांक_count++;

	अगर ((pf->flags & I40E_FLAG_IWARP_ENABLED) &&
	    (icr0 & I40E_PFINT_ICR0_ENA_PE_CRITERR_MASK)) अणु
		ena_mask &= ~I40E_PFINT_ICR0_ENA_PE_CRITERR_MASK;
		dev_dbg(&pf->pdev->dev, "cleared PE_CRITERR\n");
		set_bit(__I40E_CORE_RESET_REQUESTED, pf->state);
	पूर्ण

	/* only q0 is used in MSI/Legacy mode, and none are used in MSIX */
	अगर (icr0 & I40E_PFINT_ICR0_QUEUE_0_MASK) अणु
		काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
		काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[0];

		/* We करो not have a way to disarm Queue causes जबतक leaving
		 * पूर्णांकerrupt enabled क्रम all other causes, ideally
		 * पूर्णांकerrupt should be disabled जबतक we are in NAPI but
		 * this is not a perक्रमmance path and napi_schedule()
		 * can deal with rescheduling.
		 */
		अगर (!test_bit(__I40E_DOWN, pf->state))
			napi_schedule_irqoff(&q_vector->napi);
	पूर्ण

	अगर (icr0 & I40E_PFINT_ICR0_ADMINQ_MASK) अणु
		ena_mask &= ~I40E_PFINT_ICR0_ENA_ADMINQ_MASK;
		set_bit(__I40E_ADMINQ_EVENT_PENDING, pf->state);
		i40e_debug(&pf->hw, I40E_DEBUG_NVM, "AdminQ event\n");
	पूर्ण

	अगर (icr0 & I40E_PFINT_ICR0_MAL_DETECT_MASK) अणु
		ena_mask &= ~I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK;
		set_bit(__I40E_MDD_EVENT_PENDING, pf->state);
	पूर्ण

	अगर (icr0 & I40E_PFINT_ICR0_VFLR_MASK) अणु
		/* disable any further VFLR event notअगरications */
		अगर (test_bit(__I40E_VF_RESETS_DISABLED, pf->state)) अणु
			u32 reg = rd32(hw, I40E_PFINT_ICR0_ENA);

			reg &= ~I40E_PFINT_ICR0_VFLR_MASK;
			wr32(hw, I40E_PFINT_ICR0_ENA, reg);
		पूर्ण अन्यथा अणु
			ena_mask &= ~I40E_PFINT_ICR0_ENA_VFLR_MASK;
			set_bit(__I40E_VFLR_EVENT_PENDING, pf->state);
		पूर्ण
	पूर्ण

	अगर (icr0 & I40E_PFINT_ICR0_GRST_MASK) अणु
		अगर (!test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state))
			set_bit(__I40E_RESET_INTR_RECEIVED, pf->state);
		ena_mask &= ~I40E_PFINT_ICR0_ENA_GRST_MASK;
		val = rd32(hw, I40E_GLGEN_RSTAT);
		val = (val & I40E_GLGEN_RSTAT_RESET_TYPE_MASK)
		       >> I40E_GLGEN_RSTAT_RESET_TYPE_SHIFT;
		अगर (val == I40E_RESET_CORER) अणु
			pf->corer_count++;
		पूर्ण अन्यथा अगर (val == I40E_RESET_GLOBR) अणु
			pf->globr_count++;
		पूर्ण अन्यथा अगर (val == I40E_RESET_EMPR) अणु
			pf->empr_count++;
			set_bit(__I40E_EMP_RESET_INTR_RECEIVED, pf->state);
		पूर्ण
	पूर्ण

	अगर (icr0 & I40E_PFINT_ICR0_HMC_ERR_MASK) अणु
		icr0 &= ~I40E_PFINT_ICR0_HMC_ERR_MASK;
		dev_info(&pf->pdev->dev, "HMC error interrupt\n");
		dev_info(&pf->pdev->dev, "HMC error info 0x%x, HMC error data 0x%x\n",
			 rd32(hw, I40E_PFHMC_ERRORINFO),
			 rd32(hw, I40E_PFHMC_ERRORDATA));
	पूर्ण

	अगर (icr0 & I40E_PFINT_ICR0_TIMESYNC_MASK) अणु
		u32 prttsyn_stat = rd32(hw, I40E_PRTTSYN_STAT_0);

		अगर (prttsyn_stat & I40E_PRTTSYN_STAT_0_TXTIME_MASK) अणु
			icr0 &= ~I40E_PFINT_ICR0_ENA_TIMESYNC_MASK;
			i40e_ptp_tx_hwtstamp(pf);
		पूर्ण
	पूर्ण

	/* If a critical error is pending we have no choice but to reset the
	 * device.
	 * Report and mask out any reमुख्यing unexpected पूर्णांकerrupts.
	 */
	icr0_reमुख्यing = icr0 & ena_mask;
	अगर (icr0_reमुख्यing) अणु
		dev_info(&pf->pdev->dev, "unhandled interrupt icr0=0x%08x\n",
			 icr0_reमुख्यing);
		अगर ((icr0_reमुख्यing & I40E_PFINT_ICR0_PE_CRITERR_MASK) ||
		    (icr0_reमुख्यing & I40E_PFINT_ICR0_PCI_EXCEPTION_MASK) ||
		    (icr0_reमुख्यing & I40E_PFINT_ICR0_ECC_ERR_MASK)) अणु
			dev_info(&pf->pdev->dev, "device will be reset\n");
			set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
			i40e_service_event_schedule(pf);
		पूर्ण
		ena_mask &= ~icr0_reमुख्यing;
	पूर्ण
	ret = IRQ_HANDLED;

enable_पूर्णांकr:
	/* re-enable पूर्णांकerrupt causes */
	wr32(hw, I40E_PFINT_ICR0_ENA, ena_mask);
	अगर (!test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_RECOVERY_MODE, pf->state)) अणु
		i40e_service_event_schedule(pf);
		i40e_irq_dynamic_enable_icr0(pf);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_clean_fdir_tx_irq - Reclaim resources after transmit completes
 * @tx_ring:  tx ring to clean
 * @budget:   how many cleans we're allowed
 *
 * Returns true अगर there's any budget left (e.g. the clean is finished)
 **/
अटल bool i40e_clean_fdir_tx_irq(काष्ठा i40e_ring *tx_ring, पूर्णांक budget)
अणु
	काष्ठा i40e_vsi *vsi = tx_ring->vsi;
	u16 i = tx_ring->next_to_clean;
	काष्ठा i40e_tx_buffer *tx_buf;
	काष्ठा i40e_tx_desc *tx_desc;

	tx_buf = &tx_ring->tx_bi[i];
	tx_desc = I40E_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		काष्ठा i40e_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर the descriptor isn't करोne, no work yet to करो */
		अगर (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_le64(I40E_TX_DESC_DTYPE_DESC_DONE)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = शून्य;

		tx_desc->buffer_addr = 0;
		tx_desc->cmd_type_offset_bsz = 0;
		/* move past filter desc */
		tx_buf++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_bi;
			tx_desc = I40E_TX_DESC(tx_ring, 0);
		पूर्ण
		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buf, dma),
				 dma_unmap_len(tx_buf, len),
				 DMA_TO_DEVICE);
		अगर (tx_buf->tx_flags & I40E_TX_FLAGS_FD_SB)
			kमुक्त(tx_buf->raw_buf);

		tx_buf->raw_buf = शून्य;
		tx_buf->tx_flags = 0;
		tx_buf->next_to_watch = शून्य;
		dma_unmap_len_set(tx_buf, len, 0);
		tx_desc->buffer_addr = 0;
		tx_desc->cmd_type_offset_bsz = 0;

		/* move us past the eop_desc क्रम start of next FD desc */
		tx_buf++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_bi;
			tx_desc = I40E_TX_DESC(tx_ring, 0);
		पूर्ण

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;

	अगर (vsi->back->flags & I40E_FLAG_MSIX_ENABLED)
		i40e_irq_dynamic_enable(vsi, tx_ring->q_vector->v_idx);

	वापस budget > 0;
पूर्ण

/**
 * i40e_fdir_clean_ring - Interrupt Handler क्रम Fसूची SB ring
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 **/
अटल irqवापस_t i40e_fdir_clean_ring(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा i40e_q_vector *q_vector = data;
	काष्ठा i40e_vsi *vsi;

	अगर (!q_vector->tx.ring)
		वापस IRQ_HANDLED;

	vsi = q_vector->tx.ring->vsi;
	i40e_clean_fdir_tx_irq(q_vector->tx.ring, vsi->work_limit);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * i40e_map_vector_to_qp - Assigns the queue pair to the vector
 * @vsi: the VSI being configured
 * @v_idx: vector index
 * @qp_idx: queue pair index
 **/
अटल व्योम i40e_map_vector_to_qp(काष्ठा i40e_vsi *vsi, पूर्णांक v_idx, पूर्णांक qp_idx)
अणु
	काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[v_idx];
	काष्ठा i40e_ring *tx_ring = vsi->tx_rings[qp_idx];
	काष्ठा i40e_ring *rx_ring = vsi->rx_rings[qp_idx];

	tx_ring->q_vector = q_vector;
	tx_ring->next = q_vector->tx.ring;
	q_vector->tx.ring = tx_ring;
	q_vector->tx.count++;

	/* Place XDP Tx ring in the same q_vector ring list as regular Tx */
	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		काष्ठा i40e_ring *xdp_ring = vsi->xdp_rings[qp_idx];

		xdp_ring->q_vector = q_vector;
		xdp_ring->next = q_vector->tx.ring;
		q_vector->tx.ring = xdp_ring;
		q_vector->tx.count++;
	पूर्ण

	rx_ring->q_vector = q_vector;
	rx_ring->next = q_vector->rx.ring;
	q_vector->rx.ring = rx_ring;
	q_vector->rx.count++;
पूर्ण

/**
 * i40e_vsi_map_rings_to_vectors - Maps descriptor rings to vectors
 * @vsi: the VSI being configured
 *
 * This function maps descriptor rings to the queue-specअगरic vectors
 * we were allotted through the MSI-X enabling code.  Ideally, we'd have
 * one vector per queue pair, but on a स्थिरrained vector budget, we
 * group the queue pairs as "efficiently" as possible.
 **/
अटल व्योम i40e_vsi_map_rings_to_vectors(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक qp_reमुख्यing = vsi->num_queue_pairs;
	पूर्णांक q_vectors = vsi->num_q_vectors;
	पूर्णांक num_ringpairs;
	पूर्णांक v_start = 0;
	पूर्णांक qp_idx = 0;

	/* If we करोn't have enough vectors for a 1-to-1 mapping, we'll have to
	 * group them so there are multiple queues per vector.
	 * It is also important to go through all the vectors available to be
	 * sure that अगर we करोn't use all the vectors, that the reमुख्यing vectors
	 * are cleared. This is especially important when decreasing the
	 * number of queues in use.
	 */
	क्रम (; v_start < q_vectors; v_start++) अणु
		काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[v_start];

		num_ringpairs = DIV_ROUND_UP(qp_reमुख्यing, q_vectors - v_start);

		q_vector->num_ringpairs = num_ringpairs;
		q_vector->reg_idx = q_vector->v_idx + vsi->base_vector - 1;

		q_vector->rx.count = 0;
		q_vector->tx.count = 0;
		q_vector->rx.ring = शून्य;
		q_vector->tx.ring = शून्य;

		जबतक (num_ringpairs--) अणु
			i40e_map_vector_to_qp(vsi, v_start, qp_idx);
			qp_idx++;
			qp_reमुख्यing--;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_vsi_request_irq - Request IRQ from the OS
 * @vsi: the VSI being configured
 * @basename: name क्रम the vector
 **/
अटल पूर्णांक i40e_vsi_request_irq(काष्ठा i40e_vsi *vsi, अक्षर *basename)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक err;

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
		err = i40e_vsi_request_irq_msix(vsi, basename);
	अन्यथा अगर (pf->flags & I40E_FLAG_MSI_ENABLED)
		err = request_irq(pf->pdev->irq, i40e_पूर्णांकr, 0,
				  pf->पूर्णांक_name, pf);
	अन्यथा
		err = request_irq(pf->pdev->irq, i40e_पूर्णांकr, IRQF_SHARED,
				  pf->पूर्णांक_name, pf);

	अगर (err)
		dev_info(&pf->pdev->dev, "request_irq failed, Error %d\n", err);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * i40e_netpoll - A Polling 'interrupt' handler
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * This is used by netconsole to send skbs without having to re-enable
 * पूर्णांकerrupts.  It's not called जबतक the normal पूर्णांकerrupt routine is executing.
 **/
अटल व्योम i40e_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक i;

	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(__I40E_VSI_DOWN, vsi->state))
		वापस;

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		क्रम (i = 0; i < vsi->num_q_vectors; i++)
			i40e_msix_clean_rings(0, vsi->q_vectors[i]);
	पूर्ण अन्यथा अणु
		i40e_पूर्णांकr(pf->pdev->irq, netdev);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#घोषणा I40E_QTX_ENA_WAIT_COUNT 50

/**
 * i40e_pf_txq_रुको - Wait क्रम a PF's Tx queue to be enabled or disabled
 * @pf: the PF being configured
 * @pf_q: the PF queue
 * @enable: enable or disable state of the queue
 *
 * This routine will रुको क्रम the given Tx queue of the PF to reach the
 * enabled or disabled state.
 * Returns -ETIMEDOUT in हाल of failing to reach the requested state after
 * multiple retries; अन्यथा will वापस 0 in हाल of success.
 **/
अटल पूर्णांक i40e_pf_txq_रुको(काष्ठा i40e_pf *pf, पूर्णांक pf_q, bool enable)
अणु
	पूर्णांक i;
	u32 tx_reg;

	क्रम (i = 0; i < I40E_QUEUE_WAIT_RETRY_LIMIT; i++) अणु
		tx_reg = rd32(&pf->hw, I40E_QTX_ENA(pf_q));
		अगर (enable == !!(tx_reg & I40E_QTX_ENA_QENA_STAT_MASK))
			अवरोध;

		usleep_range(10, 20);
	पूर्ण
	अगर (i >= I40E_QUEUE_WAIT_RETRY_LIMIT)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/**
 * i40e_control_tx_q - Start or stop a particular Tx queue
 * @pf: the PF काष्ठाure
 * @pf_q: the PF queue to configure
 * @enable: start or stop the queue
 *
 * This function enables or disables a single queue. Note that any delay
 * required after the operation is expected to be handled by the caller of
 * this function.
 **/
अटल व्योम i40e_control_tx_q(काष्ठा i40e_pf *pf, पूर्णांक pf_q, bool enable)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 tx_reg;
	पूर्णांक i;

	/* warn the TX unit of coming changes */
	i40e_pre_tx_queue_cfg(&pf->hw, pf_q, enable);
	अगर (!enable)
		usleep_range(10, 20);

	क्रम (i = 0; i < I40E_QTX_ENA_WAIT_COUNT; i++) अणु
		tx_reg = rd32(hw, I40E_QTX_ENA(pf_q));
		अगर (((tx_reg >> I40E_QTX_ENA_QENA_REQ_SHIFT) & 1) ==
		    ((tx_reg >> I40E_QTX_ENA_QENA_STAT_SHIFT) & 1))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	/* Skip अगर the queue is alपढ़ोy in the requested state */
	अगर (enable == !!(tx_reg & I40E_QTX_ENA_QENA_STAT_MASK))
		वापस;

	/* turn on/off the queue */
	अगर (enable) अणु
		wr32(hw, I40E_QTX_HEAD(pf_q), 0);
		tx_reg |= I40E_QTX_ENA_QENA_REQ_MASK;
	पूर्ण अन्यथा अणु
		tx_reg &= ~I40E_QTX_ENA_QENA_REQ_MASK;
	पूर्ण

	wr32(hw, I40E_QTX_ENA(pf_q), tx_reg);
पूर्ण

/**
 * i40e_control_रुको_tx_q - Start/stop Tx queue and रुको क्रम completion
 * @seid: VSI SEID
 * @pf: the PF काष्ठाure
 * @pf_q: the PF queue to configure
 * @is_xdp: true अगर the queue is used क्रम XDP
 * @enable: start or stop the queue
 **/
पूर्णांक i40e_control_रुको_tx_q(पूर्णांक seid, काष्ठा i40e_pf *pf, पूर्णांक pf_q,
			   bool is_xdp, bool enable)
अणु
	पूर्णांक ret;

	i40e_control_tx_q(pf, pf_q, enable);

	/* रुको क्रम the change to finish */
	ret = i40e_pf_txq_रुको(pf, pf_q, enable);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "VSI seid %d %sTx ring %d %sable timeout\n",
			 seid, (is_xdp ? "XDP " : ""), pf_q,
			 (enable ? "en" : "dis"));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_vsi_control_tx - Start or stop a VSI's rings
 * @vsi: the VSI being configured
 * @enable: start or stop the rings
 **/
अटल पूर्णांक i40e_vsi_control_tx(काष्ठा i40e_vsi *vsi, bool enable)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक i, pf_q, ret = 0;

	pf_q = vsi->base_queue;
	क्रम (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) अणु
		ret = i40e_control_रुको_tx_q(vsi->seid, pf,
					     pf_q,
					     false /*is xdp*/, enable);
		अगर (ret)
			अवरोध;

		अगर (!i40e_enabled_xdp_vsi(vsi))
			जारी;

		ret = i40e_control_रुको_tx_q(vsi->seid, pf,
					     pf_q + vsi->alloc_queue_pairs,
					     true /*is xdp*/, enable);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40e_pf_rxq_रुको - Wait क्रम a PF's Rx queue to be enabled or disabled
 * @pf: the PF being configured
 * @pf_q: the PF queue
 * @enable: enable or disable state of the queue
 *
 * This routine will रुको क्रम the given Rx queue of the PF to reach the
 * enabled or disabled state.
 * Returns -ETIMEDOUT in हाल of failing to reach the requested state after
 * multiple retries; अन्यथा will वापस 0 in हाल of success.
 **/
अटल पूर्णांक i40e_pf_rxq_रुको(काष्ठा i40e_pf *pf, पूर्णांक pf_q, bool enable)
अणु
	पूर्णांक i;
	u32 rx_reg;

	क्रम (i = 0; i < I40E_QUEUE_WAIT_RETRY_LIMIT; i++) अणु
		rx_reg = rd32(&pf->hw, I40E_QRX_ENA(pf_q));
		अगर (enable == !!(rx_reg & I40E_QRX_ENA_QENA_STAT_MASK))
			अवरोध;

		usleep_range(10, 20);
	पूर्ण
	अगर (i >= I40E_QUEUE_WAIT_RETRY_LIMIT)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/**
 * i40e_control_rx_q - Start or stop a particular Rx queue
 * @pf: the PF काष्ठाure
 * @pf_q: the PF queue to configure
 * @enable: start or stop the queue
 *
 * This function enables or disables a single queue. Note that
 * any delay required after the operation is expected to be
 * handled by the caller of this function.
 **/
अटल व्योम i40e_control_rx_q(काष्ठा i40e_pf *pf, पूर्णांक pf_q, bool enable)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 rx_reg;
	पूर्णांक i;

	क्रम (i = 0; i < I40E_QTX_ENA_WAIT_COUNT; i++) अणु
		rx_reg = rd32(hw, I40E_QRX_ENA(pf_q));
		अगर (((rx_reg >> I40E_QRX_ENA_QENA_REQ_SHIFT) & 1) ==
		    ((rx_reg >> I40E_QRX_ENA_QENA_STAT_SHIFT) & 1))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	/* Skip अगर the queue is alपढ़ोy in the requested state */
	अगर (enable == !!(rx_reg & I40E_QRX_ENA_QENA_STAT_MASK))
		वापस;

	/* turn on/off the queue */
	अगर (enable)
		rx_reg |= I40E_QRX_ENA_QENA_REQ_MASK;
	अन्यथा
		rx_reg &= ~I40E_QRX_ENA_QENA_REQ_MASK;

	wr32(hw, I40E_QRX_ENA(pf_q), rx_reg);
पूर्ण

/**
 * i40e_control_रुको_rx_q
 * @pf: the PF काष्ठाure
 * @pf_q: queue being configured
 * @enable: start or stop the rings
 *
 * This function enables or disables a single queue aदीर्घ with रुकोing
 * क्रम the change to finish. The caller of this function should handle
 * the delays needed in the हाल of disabling queues.
 **/
पूर्णांक i40e_control_रुको_rx_q(काष्ठा i40e_pf *pf, पूर्णांक pf_q, bool enable)
अणु
	पूर्णांक ret = 0;

	i40e_control_rx_q(pf, pf_q, enable);

	/* रुको क्रम the change to finish */
	ret = i40e_pf_rxq_रुको(pf, pf_q, enable);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

/**
 * i40e_vsi_control_rx - Start or stop a VSI's rings
 * @vsi: the VSI being configured
 * @enable: start or stop the rings
 **/
अटल पूर्णांक i40e_vsi_control_rx(काष्ठा i40e_vsi *vsi, bool enable)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक i, pf_q, ret = 0;

	pf_q = vsi->base_queue;
	क्रम (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) अणु
		ret = i40e_control_रुको_rx_q(pf, pf_q, enable);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "VSI seid %d Rx ring %d %sable timeout\n",
				 vsi->seid, pf_q, (enable ? "en" : "dis"));
			अवरोध;
		पूर्ण
	पूर्ण

	/* Due to HW errata, on Rx disable only, the रेजिस्टर can indicate करोne
	 * beक्रमe it really is. Needs 50ms to be sure
	 */
	अगर (!enable)
		mdelay(50);

	वापस ret;
पूर्ण

/**
 * i40e_vsi_start_rings - Start a VSI's rings
 * @vsi: the VSI being configured
 **/
पूर्णांक i40e_vsi_start_rings(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक ret = 0;

	/* करो rx first क्रम enable and last क्रम disable */
	ret = i40e_vsi_control_rx(vsi, true);
	अगर (ret)
		वापस ret;
	ret = i40e_vsi_control_tx(vsi, true);

	वापस ret;
पूर्ण

/**
 * i40e_vsi_stop_rings - Stop a VSI's rings
 * @vsi: the VSI being configured
 **/
व्योम i40e_vsi_stop_rings(काष्ठा i40e_vsi *vsi)
अणु
	/* When port TX is suspended, करोn't रुको */
	अगर (test_bit(__I40E_PORT_SUSPENDED, vsi->back->state))
		वापस i40e_vsi_stop_rings_no_रुको(vsi);

	/* करो rx first क्रम enable and last क्रम disable
	 * Ignore वापस value, we need to shutकरोwn whatever we can
	 */
	i40e_vsi_control_tx(vsi, false);
	i40e_vsi_control_rx(vsi, false);
पूर्ण

/**
 * i40e_vsi_stop_rings_no_रुको - Stop a VSI's rings and करो not delay
 * @vsi: the VSI being shutकरोwn
 *
 * This function stops all the rings क्रम a VSI but करोes not delay to verअगरy
 * that rings have been disabled. It is expected that the caller is shutting
 * करोwn multiple VSIs at once and will delay together क्रम all the VSIs after
 * initiating the shutकरोwn. This is particularly useful क्रम shutting करोwn lots
 * of VFs together. Otherwise, a large delay can be incurred जबतक configuring
 * each VSI in serial.
 **/
व्योम i40e_vsi_stop_rings_no_रुको(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक i, pf_q;

	pf_q = vsi->base_queue;
	क्रम (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) अणु
		i40e_control_tx_q(pf, pf_q, false);
		i40e_control_rx_q(pf, pf_q, false);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_मुक्त_irq - Free the irq association with the OS
 * @vsi: the VSI being configured
 **/
अटल व्योम i40e_vsi_मुक्त_irq(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक base = vsi->base_vector;
	u32 val, qp;
	पूर्णांक i;

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		अगर (!vsi->q_vectors)
			वापस;

		अगर (!vsi->irqs_पढ़ोy)
			वापस;

		vsi->irqs_पढ़ोy = false;
		क्रम (i = 0; i < vsi->num_q_vectors; i++) अणु
			पूर्णांक irq_num;
			u16 vector;

			vector = i + base;
			irq_num = pf->msix_entries[vector].vector;

			/* मुक्त only the irqs that were actually requested */
			अगर (!vsi->q_vectors[i] ||
			    !vsi->q_vectors[i]->num_ringpairs)
				जारी;

			/* clear the affinity notअगरier in the IRQ descriptor */
			irq_set_affinity_notअगरier(irq_num, शून्य);
			/* हटाओ our suggested affinity mask क्रम this IRQ */
			irq_set_affinity_hपूर्णांक(irq_num, शून्य);
			synchronize_irq(irq_num);
			मुक्त_irq(irq_num, vsi->q_vectors[i]);

			/* Tear करोwn the पूर्णांकerrupt queue link list
			 *
			 * We know that they come in pairs and always
			 * the Rx first, then the Tx.  To clear the
			 * link list, stick the EOL value पूर्णांकo the
			 * next_q field of the रेजिस्टरs.
			 */
			val = rd32(hw, I40E_PFINT_LNKLSTN(vector - 1));
			qp = (val & I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK)
				>> I40E_PFINT_LNKLSTN_FIRSTQ_INDX_SHIFT;
			val |= I40E_QUEUE_END_OF_LIST
				<< I40E_PFINT_LNKLSTN_FIRSTQ_INDX_SHIFT;
			wr32(hw, I40E_PFINT_LNKLSTN(vector - 1), val);

			जबतक (qp != I40E_QUEUE_END_OF_LIST) अणु
				u32 next;

				val = rd32(hw, I40E_QINT_RQCTL(qp));

				val &= ~(I40E_QINT_RQCTL_MSIX_INDX_MASK  |
					 I40E_QINT_RQCTL_MSIX0_INDX_MASK |
					 I40E_QINT_RQCTL_CAUSE_ENA_MASK  |
					 I40E_QINT_RQCTL_INTEVENT_MASK);

				val |= (I40E_QINT_RQCTL_ITR_INDX_MASK |
					 I40E_QINT_RQCTL_NEXTQ_INDX_MASK);

				wr32(hw, I40E_QINT_RQCTL(qp), val);

				val = rd32(hw, I40E_QINT_TQCTL(qp));

				next = (val & I40E_QINT_TQCTL_NEXTQ_INDX_MASK)
					>> I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT;

				val &= ~(I40E_QINT_TQCTL_MSIX_INDX_MASK  |
					 I40E_QINT_TQCTL_MSIX0_INDX_MASK |
					 I40E_QINT_TQCTL_CAUSE_ENA_MASK  |
					 I40E_QINT_TQCTL_INTEVENT_MASK);

				val |= (I40E_QINT_TQCTL_ITR_INDX_MASK |
					 I40E_QINT_TQCTL_NEXTQ_INDX_MASK);

				wr32(hw, I40E_QINT_TQCTL(qp), val);
				qp = next;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		मुक्त_irq(pf->pdev->irq, pf);

		val = rd32(hw, I40E_PFINT_LNKLST0);
		qp = (val & I40E_PFINT_LNKLSTN_FIRSTQ_INDX_MASK)
			>> I40E_PFINT_LNKLSTN_FIRSTQ_INDX_SHIFT;
		val |= I40E_QUEUE_END_OF_LIST
			<< I40E_PFINT_LNKLST0_FIRSTQ_INDX_SHIFT;
		wr32(hw, I40E_PFINT_LNKLST0, val);

		val = rd32(hw, I40E_QINT_RQCTL(qp));
		val &= ~(I40E_QINT_RQCTL_MSIX_INDX_MASK  |
			 I40E_QINT_RQCTL_MSIX0_INDX_MASK |
			 I40E_QINT_RQCTL_CAUSE_ENA_MASK  |
			 I40E_QINT_RQCTL_INTEVENT_MASK);

		val |= (I40E_QINT_RQCTL_ITR_INDX_MASK |
			I40E_QINT_RQCTL_NEXTQ_INDX_MASK);

		wr32(hw, I40E_QINT_RQCTL(qp), val);

		val = rd32(hw, I40E_QINT_TQCTL(qp));

		val &= ~(I40E_QINT_TQCTL_MSIX_INDX_MASK  |
			 I40E_QINT_TQCTL_MSIX0_INDX_MASK |
			 I40E_QINT_TQCTL_CAUSE_ENA_MASK  |
			 I40E_QINT_TQCTL_INTEVENT_MASK);

		val |= (I40E_QINT_TQCTL_ITR_INDX_MASK |
			I40E_QINT_TQCTL_NEXTQ_INDX_MASK);

		wr32(hw, I40E_QINT_TQCTL(qp), val);
	पूर्ण
पूर्ण

/**
 * i40e_मुक्त_q_vector - Free memory allocated क्रम specअगरic पूर्णांकerrupt vector
 * @vsi: the VSI being configured
 * @v_idx: Index of vector to be मुक्तd
 *
 * This function मुक्तs the memory allocated to the q_vector.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम i40e_मुक्त_q_vector(काष्ठा i40e_vsi *vsi, पूर्णांक v_idx)
अणु
	काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[v_idx];
	काष्ठा i40e_ring *ring;

	अगर (!q_vector)
		वापस;

	/* disassociate q_vector from rings */
	i40e_क्रम_each_ring(ring, q_vector->tx)
		ring->q_vector = शून्य;

	i40e_क्रम_each_ring(ring, q_vector->rx)
		ring->q_vector = शून्य;

	/* only VSI w/ an associated netdev is set up w/ NAPI */
	अगर (vsi->netdev)
		netअगर_napi_del(&q_vector->napi);

	vsi->q_vectors[v_idx] = शून्य;

	kमुक्त_rcu(q_vector, rcu);
पूर्ण

/**
 * i40e_vsi_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 * @vsi: the VSI being un-configured
 *
 * This मुक्तs the memory allocated to the q_vectors and
 * deletes references to the NAPI काष्ठा.
 **/
अटल व्योम i40e_vsi_मुक्त_q_vectors(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक v_idx;

	क्रम (v_idx = 0; v_idx < vsi->num_q_vectors; v_idx++)
		i40e_मुक्त_q_vector(vsi, v_idx);
पूर्ण

/**
 * i40e_reset_पूर्णांकerrupt_capability - Disable पूर्णांकerrupt setup in OS
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_reset_पूर्णांकerrupt_capability(काष्ठा i40e_pf *pf)
अणु
	/* If we're in Legacy mode, the पूर्णांकerrupt was cleaned in vsi_बंद */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		pci_disable_msix(pf->pdev);
		kमुक्त(pf->msix_entries);
		pf->msix_entries = शून्य;
		kमुक्त(pf->irq_pile);
		pf->irq_pile = शून्य;
	पूर्ण अन्यथा अगर (pf->flags & I40E_FLAG_MSI_ENABLED) अणु
		pci_disable_msi(pf->pdev);
	पूर्ण
	pf->flags &= ~(I40E_FLAG_MSIX_ENABLED | I40E_FLAG_MSI_ENABLED);
पूर्ण

/**
 * i40e_clear_पूर्णांकerrupt_scheme - Clear the current पूर्णांकerrupt scheme settings
 * @pf: board निजी काष्ठाure
 *
 * We go through and clear पूर्णांकerrupt specअगरic resources and reset the काष्ठाure
 * to pre-load conditions
 **/
अटल व्योम i40e_clear_पूर्णांकerrupt_scheme(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक i;

	i40e_मुक्त_misc_vector(pf);

	i40e_put_lump(pf->irq_pile, pf->iwarp_base_vector,
		      I40E_IWARP_IRQ_PILE_ID);

	i40e_put_lump(pf->irq_pile, 0, I40E_PILE_VALID_BIT-1);
	क्रम (i = 0; i < pf->num_alloc_vsi; i++)
		अगर (pf->vsi[i])
			i40e_vsi_मुक्त_q_vectors(pf->vsi[i]);
	i40e_reset_पूर्णांकerrupt_capability(pf);
पूर्ण

/**
 * i40e_napi_enable_all - Enable NAPI क्रम all q_vectors in the VSI
 * @vsi: the VSI being configured
 **/
अटल व्योम i40e_napi_enable_all(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक q_idx;

	अगर (!vsi->netdev)
		वापस;

	क्रम (q_idx = 0; q_idx < vsi->num_q_vectors; q_idx++) अणु
		काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[q_idx];

		अगर (q_vector->rx.ring || q_vector->tx.ring)
			napi_enable(&q_vector->napi);
	पूर्ण
पूर्ण

/**
 * i40e_napi_disable_all - Disable NAPI क्रम all q_vectors in the VSI
 * @vsi: the VSI being configured
 **/
अटल व्योम i40e_napi_disable_all(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक q_idx;

	अगर (!vsi->netdev)
		वापस;

	क्रम (q_idx = 0; q_idx < vsi->num_q_vectors; q_idx++) अणु
		काष्ठा i40e_q_vector *q_vector = vsi->q_vectors[q_idx];

		अगर (q_vector->rx.ring || q_vector->tx.ring)
			napi_disable(&q_vector->napi);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_बंद - Shut करोwn a VSI
 * @vsi: the vsi to be quelled
 **/
अटल व्योम i40e_vsi_बंद(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	अगर (!test_and_set_bit(__I40E_VSI_DOWN, vsi->state))
		i40e_करोwn(vsi);
	i40e_vsi_मुक्त_irq(vsi);
	i40e_vsi_मुक्त_tx_resources(vsi);
	i40e_vsi_मुक्त_rx_resources(vsi);
	vsi->current_netdev_flags = 0;
	set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
	अगर (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state))
		set_bit(__I40E_CLIENT_RESET, pf->state);
पूर्ण

/**
 * i40e_quiesce_vsi - Pause a given VSI
 * @vsi: the VSI being छोड़ोd
 **/
अटल व्योम i40e_quiesce_vsi(काष्ठा i40e_vsi *vsi)
अणु
	अगर (test_bit(__I40E_VSI_DOWN, vsi->state))
		वापस;

	set_bit(__I40E_VSI_NEEDS_RESTART, vsi->state);
	अगर (vsi->netdev && netअगर_running(vsi->netdev))
		vsi->netdev->netdev_ops->nकरो_stop(vsi->netdev);
	अन्यथा
		i40e_vsi_बंद(vsi);
पूर्ण

/**
 * i40e_unquiesce_vsi - Resume a given VSI
 * @vsi: the VSI being resumed
 **/
अटल व्योम i40e_unquiesce_vsi(काष्ठा i40e_vsi *vsi)
अणु
	अगर (!test_and_clear_bit(__I40E_VSI_NEEDS_RESTART, vsi->state))
		वापस;

	अगर (vsi->netdev && netअगर_running(vsi->netdev))
		vsi->netdev->netdev_ops->nकरो_खोलो(vsi->netdev);
	अन्यथा
		i40e_vsi_खोलो(vsi);   /* this clears the DOWN bit */
पूर्ण

/**
 * i40e_pf_quiesce_all_vsi - Pause all VSIs on a PF
 * @pf: the PF
 **/
अटल व्योम i40e_pf_quiesce_all_vsi(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक v;

	क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
		अगर (pf->vsi[v])
			i40e_quiesce_vsi(pf->vsi[v]);
	पूर्ण
पूर्ण

/**
 * i40e_pf_unquiesce_all_vsi - Resume all VSIs on a PF
 * @pf: the PF
 **/
अटल व्योम i40e_pf_unquiesce_all_vsi(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक v;

	क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
		अगर (pf->vsi[v])
			i40e_unquiesce_vsi(pf->vsi[v]);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_रुको_queues_disabled - Wait क्रम VSI's queues to be disabled
 * @vsi: the VSI being configured
 *
 * Wait until all queues on a given VSI have been disabled.
 **/
पूर्णांक i40e_vsi_रुको_queues_disabled(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक i, pf_q, ret;

	pf_q = vsi->base_queue;
	क्रम (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) अणु
		/* Check and रुको क्रम the Tx queue */
		ret = i40e_pf_txq_रुको(pf, pf_q, false);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "VSI seid %d Tx ring %d disable timeout\n",
				 vsi->seid, pf_q);
			वापस ret;
		पूर्ण

		अगर (!i40e_enabled_xdp_vsi(vsi))
			जाओ रुको_rx;

		/* Check and रुको क्रम the XDP Tx queue */
		ret = i40e_pf_txq_रुको(pf, pf_q + vsi->alloc_queue_pairs,
				       false);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "VSI seid %d XDP Tx ring %d disable timeout\n",
				 vsi->seid, pf_q);
			वापस ret;
		पूर्ण
रुको_rx:
		/* Check and रुको क्रम the Rx queue */
		ret = i40e_pf_rxq_रुको(pf, pf_q, false);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "VSI seid %d Rx ring %d disable timeout\n",
				 vsi->seid, pf_q);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_I40E_DCB
/**
 * i40e_pf_रुको_queues_disabled - Wait क्रम all queues of PF VSIs to be disabled
 * @pf: the PF
 *
 * This function रुकोs क्रम the queues to be in disabled state क्रम all the
 * VSIs that are managed by this PF.
 **/
अटल पूर्णांक i40e_pf_रुको_queues_disabled(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक v, ret = 0;

	क्रम (v = 0; v < pf->hw.func_caps.num_vsis; v++) अणु
		अगर (pf->vsi[v]) अणु
			ret = i40e_vsi_रुको_queues_disabled(pf->vsi[v]);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

#पूर्ण_अगर

/**
 * i40e_get_iscsi_tc_map - Return TC map क्रम iSCSI APP
 * @pf: poपूर्णांकer to PF
 *
 * Get TC map क्रम ISCSI PF type that will include iSCSI TC
 * and LAN TC.
 **/
अटल u8 i40e_get_iscsi_tc_map(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_dcb_app_priority_table app;
	काष्ठा i40e_hw *hw = &pf->hw;
	u8 enabled_tc = 1; /* TC0 is always enabled */
	u8 tc, i;
	/* Get the iSCSI APP TLV */
	काष्ठा i40e_dcbx_config *dcbcfg = &hw->local_dcbx_config;

	क्रम (i = 0; i < dcbcfg->numapps; i++) अणु
		app = dcbcfg->app[i];
		अगर (app.selector == I40E_APP_SEL_TCPIP &&
		    app.protocolid == I40E_APP_PROTOID_ISCSI) अणु
			tc = dcbcfg->etscfg.prioritytable[app.priority];
			enabled_tc |= BIT(tc);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस enabled_tc;
पूर्ण

/**
 * i40e_dcb_get_num_tc -  Get the number of TCs from DCBx config
 * @dcbcfg: the corresponding DCBx configuration काष्ठाure
 *
 * Return the number of TCs from given DCBx configuration
 **/
अटल u8 i40e_dcb_get_num_tc(काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	पूर्णांक i, tc_unused = 0;
	u8 num_tc = 0;
	u8 ret = 0;

	/* Scan the ETS Config Priority Table to find
	 * traffic class enabled क्रम a given priority
	 * and create a biपंचांगask of enabled TCs
	 */
	क्रम (i = 0; i < I40E_MAX_USER_PRIORITY; i++)
		num_tc |= BIT(dcbcfg->etscfg.prioritytable[i]);

	/* Now scan the biपंचांगask to check क्रम
	 * contiguous TCs starting with TC0
	 */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (num_tc & BIT(i)) अणु
			अगर (!tc_unused) अणु
				ret++;
			पूर्ण अन्यथा अणु
				pr_err("Non-contiguous TC - Disabling DCB\n");
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			tc_unused = 1;
		पूर्ण
	पूर्ण

	/* There is always at least TC0 */
	अगर (!ret)
		ret = 1;

	वापस ret;
पूर्ण

/**
 * i40e_dcb_get_enabled_tc - Get enabled traffic classes
 * @dcbcfg: the corresponding DCBx configuration काष्ठाure
 *
 * Query the current DCB configuration and वापस the number of
 * traffic classes enabled from the given DCBX config
 **/
अटल u8 i40e_dcb_get_enabled_tc(काष्ठा i40e_dcbx_config *dcbcfg)
अणु
	u8 num_tc = i40e_dcb_get_num_tc(dcbcfg);
	u8 enabled_tc = 1;
	u8 i;

	क्रम (i = 0; i < num_tc; i++)
		enabled_tc |= BIT(i);

	वापस enabled_tc;
पूर्ण

/**
 * i40e_mqprio_get_enabled_tc - Get enabled traffic classes
 * @pf: PF being queried
 *
 * Query the current MQPRIO configuration and वापस the number of
 * traffic classes enabled.
 **/
अटल u8 i40e_mqprio_get_enabled_tc(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	u8 num_tc = vsi->mqprio_qopt.qopt.num_tc;
	u8 enabled_tc = 1, i;

	क्रम (i = 1; i < num_tc; i++)
		enabled_tc |= BIT(i);
	वापस enabled_tc;
पूर्ण

/**
 * i40e_pf_get_num_tc - Get enabled traffic classes क्रम PF
 * @pf: PF being queried
 *
 * Return number of traffic classes enabled क्रम the given PF
 **/
अटल u8 i40e_pf_get_num_tc(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u8 i, enabled_tc = 1;
	u8 num_tc = 0;
	काष्ठा i40e_dcbx_config *dcbcfg = &hw->local_dcbx_config;

	अगर (pf->flags & I40E_FLAG_TC_MQPRIO)
		वापस pf->vsi[pf->lan_vsi]->mqprio_qopt.qopt.num_tc;

	/* If neither MQPRIO nor DCB is enabled, then always use single TC */
	अगर (!(pf->flags & I40E_FLAG_DCB_ENABLED))
		वापस 1;

	/* SFP mode will be enabled क्रम all TCs on port */
	अगर (!(pf->flags & I40E_FLAG_MFP_ENABLED))
		वापस i40e_dcb_get_num_tc(dcbcfg);

	/* MFP mode वापस count of enabled TCs क्रम this PF */
	अगर (pf->hw.func_caps.iscsi)
		enabled_tc =  i40e_get_iscsi_tc_map(pf);
	अन्यथा
		वापस 1; /* Only TC0 */

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (enabled_tc & BIT(i))
			num_tc++;
	पूर्ण
	वापस num_tc;
पूर्ण

/**
 * i40e_pf_get_tc_map - Get biपंचांगap क्रम enabled traffic classes
 * @pf: PF being queried
 *
 * Return a biपंचांगap क्रम enabled traffic classes क्रम this PF.
 **/
अटल u8 i40e_pf_get_tc_map(काष्ठा i40e_pf *pf)
अणु
	अगर (pf->flags & I40E_FLAG_TC_MQPRIO)
		वापस i40e_mqprio_get_enabled_tc(pf);

	/* If neither MQPRIO nor DCB is enabled क्रम this PF then just वापस
	 * शेष TC
	 */
	अगर (!(pf->flags & I40E_FLAG_DCB_ENABLED))
		वापस I40E_DEFAULT_TRAFFIC_CLASS;

	/* SFP mode we want PF to be enabled क्रम all TCs */
	अगर (!(pf->flags & I40E_FLAG_MFP_ENABLED))
		वापस i40e_dcb_get_enabled_tc(&pf->hw.local_dcbx_config);

	/* MFP enabled and iSCSI PF type */
	अगर (pf->hw.func_caps.iscsi)
		वापस i40e_get_iscsi_tc_map(pf);
	अन्यथा
		वापस I40E_DEFAULT_TRAFFIC_CLASS;
पूर्ण

/**
 * i40e_vsi_get_bw_info - Query VSI BW Inक्रमmation
 * @vsi: the VSI being queried
 *
 * Returns 0 on success, negative value on failure
 **/
अटल पूर्णांक i40e_vsi_get_bw_info(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_aqc_query_vsi_ets_sla_config_resp bw_ets_config = अणु0पूर्ण;
	काष्ठा i40e_aqc_query_vsi_bw_config_resp bw_config = अणु0पूर्ण;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status ret;
	u32 tc_bw_max;
	पूर्णांक i;

	/* Get the VSI level BW configuration */
	ret = i40e_aq_query_vsi_bw_config(hw, vsi->seid, &bw_config, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi bw config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EINVAL;
	पूर्ण

	/* Get the VSI level BW configuration per TC */
	ret = i40e_aq_query_vsi_ets_sla_config(hw, vsi->seid, &bw_ets_config,
					       शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi ets bw config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EINVAL;
	पूर्ण

	अगर (bw_config.tc_valid_bits != bw_ets_config.tc_valid_bits) अणु
		dev_info(&pf->pdev->dev,
			 "Enabled TCs mismatch from querying VSI BW info 0x%08x 0x%08x\n",
			 bw_config.tc_valid_bits,
			 bw_ets_config.tc_valid_bits);
		/* Still continuing */
	पूर्ण

	vsi->bw_limit = le16_to_cpu(bw_config.port_bw_limit);
	vsi->bw_max_quanta = bw_config.max_bw;
	tc_bw_max = le16_to_cpu(bw_ets_config.tc_bw_max[0]) |
		    (le16_to_cpu(bw_ets_config.tc_bw_max[1]) << 16);
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		vsi->bw_ets_share_credits[i] = bw_ets_config.share_credits[i];
		vsi->bw_ets_limit_credits[i] =
					le16_to_cpu(bw_ets_config.credits[i]);
		/* 3 bits out of 4 क्रम each TC */
		vsi->bw_ets_max_quanta[i] = (u8)((tc_bw_max >> (i*4)) & 0x7);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vsi_configure_bw_alloc - Configure VSI BW allocation per TC
 * @vsi: the VSI being configured
 * @enabled_tc: TC biपंचांगap
 * @bw_share: BW shared credits per TC
 *
 * Returns 0 on success, negative value on failure
 **/
अटल पूर्णांक i40e_vsi_configure_bw_alloc(काष्ठा i40e_vsi *vsi, u8 enabled_tc,
				       u8 *bw_share)
अणु
	काष्ठा i40e_aqc_configure_vsi_tc_bw_data bw_data;
	काष्ठा i40e_pf *pf = vsi->back;
	i40e_status ret;
	पूर्णांक i;

	/* There is no need to reset BW when mqprio mode is on.  */
	अगर (pf->flags & I40E_FLAG_TC_MQPRIO)
		वापस 0;
	अगर (!vsi->mqprio_qopt.qopt.hw && !(pf->flags & I40E_FLAG_DCB_ENABLED)) अणु
		ret = i40e_set_bw_limit(vsi, vsi->seid, 0);
		अगर (ret)
			dev_info(&pf->pdev->dev,
				 "Failed to reset tx rate for vsi->seid %u\n",
				 vsi->seid);
		वापस ret;
	पूर्ण
	स_रखो(&bw_data, 0, माप(bw_data));
	bw_data.tc_valid_bits = enabled_tc;
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		bw_data.tc_bw_credits[i] = bw_share[i];

	ret = i40e_aq_config_vsi_tc_bw(&pf->hw, vsi->seid, &bw_data, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "AQ command Config VSI BW allocation per TC failed = %d\n",
			 pf->hw.aq.asq_last_status);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		vsi->info.qs_handle[i] = bw_data.qs_handles[i];

	वापस 0;
पूर्ण

/**
 * i40e_vsi_config_netdev_tc - Setup the netdev TC configuration
 * @vsi: the VSI being configured
 * @enabled_tc: TC map to be enabled
 *
 **/
अटल व्योम i40e_vsi_config_netdev_tc(काष्ठा i40e_vsi *vsi, u8 enabled_tc)
अणु
	काष्ठा net_device *netdev = vsi->netdev;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u8 netdev_tc = 0;
	पूर्णांक i;
	काष्ठा i40e_dcbx_config *dcbcfg = &hw->local_dcbx_config;

	अगर (!netdev)
		वापस;

	अगर (!enabled_tc) अणु
		netdev_reset_tc(netdev);
		वापस;
	पूर्ण

	/* Set up actual enabled TCs on the VSI */
	अगर (netdev_set_num_tc(netdev, vsi->tc_config.numtc))
		वापस;

	/* set per TC queues क्रम the VSI */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		/* Only set TC queues क्रम enabled tcs
		 *
		 * e.g. For a VSI that has TC0 and TC3 enabled the
		 * enabled_tc biपंचांगap would be 0x00001001; the driver
		 * will set the numtc क्रम netdev as 2 that will be
		 * referenced by the netdev layer as TC 0 and 1.
		 */
		अगर (vsi->tc_config.enabled_tc & BIT(i))
			netdev_set_tc_queue(netdev,
					vsi->tc_config.tc_info[i].netdev_tc,
					vsi->tc_config.tc_info[i].qcount,
					vsi->tc_config.tc_info[i].qoffset);
	पूर्ण

	अगर (pf->flags & I40E_FLAG_TC_MQPRIO)
		वापस;

	/* Assign UP2TC map क्रम the VSI */
	क्रम (i = 0; i < I40E_MAX_USER_PRIORITY; i++) अणु
		/* Get the actual TC# क्रम the UP */
		u8 ets_tc = dcbcfg->etscfg.prioritytable[i];
		/* Get the mapped netdev TC# क्रम the UP */
		netdev_tc =  vsi->tc_config.tc_info[ets_tc].netdev_tc;
		netdev_set_prio_tc_map(netdev, i, netdev_tc);
	पूर्ण
पूर्ण

/**
 * i40e_vsi_update_queue_map - Update our copy of VSi info with new queue map
 * @vsi: the VSI being configured
 * @ctxt: the ctxt buffer वापसed from AQ VSI update param command
 **/
अटल व्योम i40e_vsi_update_queue_map(काष्ठा i40e_vsi *vsi,
				      काष्ठा i40e_vsi_context *ctxt)
अणु
	/* copy just the sections touched not the entire info
	 * since not all sections are valid as वापसed by
	 * update vsi params
	 */
	vsi->info.mapping_flags = ctxt->info.mapping_flags;
	स_नकल(&vsi->info.queue_mapping,
	       &ctxt->info.queue_mapping, माप(vsi->info.queue_mapping));
	स_नकल(&vsi->info.tc_mapping, ctxt->info.tc_mapping,
	       माप(vsi->info.tc_mapping));
पूर्ण

/**
 * i40e_vsi_config_tc - Configure VSI Tx Scheduler क्रम given TC map
 * @vsi: VSI to be configured
 * @enabled_tc: TC biपंचांगap
 *
 * This configures a particular VSI क्रम TCs that are mapped to the
 * given TC biपंचांगap. It uses शेष bandwidth share क्रम TCs across
 * VSIs to configure TC क्रम a particular VSI.
 *
 * NOTE:
 * It is expected that the VSI queues have been quisced beक्रमe calling
 * this function.
 **/
अटल पूर्णांक i40e_vsi_config_tc(काष्ठा i40e_vsi *vsi, u8 enabled_tc)
अणु
	u8 bw_share[I40E_MAX_TRAFFIC_CLASS] = अणु0पूर्ण;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vsi_context ctxt;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Check अगर enabled_tc is same as existing or new TCs */
	अगर (vsi->tc_config.enabled_tc == enabled_tc &&
	    vsi->mqprio_qopt.mode != TC_MQPRIO_MODE_CHANNEL)
		वापस ret;

	/* Enable ETS TCs with equal BW Share क्रम now across all VSIs */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (enabled_tc & BIT(i))
			bw_share[i] = 1;
	पूर्ण

	ret = i40e_vsi_configure_bw_alloc(vsi, enabled_tc, bw_share);
	अगर (ret) अणु
		काष्ठा i40e_aqc_query_vsi_bw_config_resp bw_config = अणु0पूर्ण;

		dev_info(&pf->pdev->dev,
			 "Failed configuring TC map %d for VSI %d\n",
			 enabled_tc, vsi->seid);
		ret = i40e_aq_query_vsi_bw_config(hw, vsi->seid,
						  &bw_config, शून्य);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "Failed querying vsi bw info, err %s aq_err %s\n",
				 i40e_stat_str(hw, ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
			जाओ out;
		पूर्ण
		अगर ((bw_config.tc_valid_bits & enabled_tc) != enabled_tc) अणु
			u8 valid_tc = bw_config.tc_valid_bits & enabled_tc;

			अगर (!valid_tc)
				valid_tc = bw_config.tc_valid_bits;
			/* Always enable TC0, no matter what */
			valid_tc |= 1;
			dev_info(&pf->pdev->dev,
				 "Requested tc 0x%x, but FW reports 0x%x as valid. Attempting to use 0x%x.\n",
				 enabled_tc, bw_config.tc_valid_bits, valid_tc);
			enabled_tc = valid_tc;
		पूर्ण

		ret = i40e_vsi_configure_bw_alloc(vsi, enabled_tc, bw_share);
		अगर (ret) अणु
			dev_err(&pf->pdev->dev,
				"Unable to  configure TC map %d for VSI %d\n",
				enabled_tc, vsi->seid);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Update Queue Pairs Mapping क्रम currently enabled UPs */
	ctxt.seid = vsi->seid;
	ctxt.pf_num = vsi->back->hw.pf_id;
	ctxt.vf_num = 0;
	ctxt.uplink_seid = vsi->uplink_seid;
	ctxt.info = vsi->info;
	अगर (vsi->back->flags & I40E_FLAG_TC_MQPRIO) अणु
		ret = i40e_vsi_setup_queue_map_mqprio(vsi, &ctxt, enabled_tc);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, false);
	पूर्ण

	/* On destroying the qdisc, reset vsi->rss_size, as number of enabled
	 * queues changed.
	 */
	अगर (!vsi->mqprio_qopt.qopt.hw && vsi->reconfig_rss) अणु
		vsi->rss_size = min_t(पूर्णांक, vsi->back->alloc_rss_size,
				      vsi->num_queue_pairs);
		ret = i40e_vsi_config_rss(vsi);
		अगर (ret) अणु
			dev_info(&vsi->back->pdev->dev,
				 "Failed to reconfig rss for num_queues\n");
			वापस ret;
		पूर्ण
		vsi->reconfig_rss = false;
	पूर्ण
	अगर (vsi->back->flags & I40E_FLAG_IWARP_ENABLED) अणु
		ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_QUEUE_OPT_VALID);
		ctxt.info.queueing_opt_flags |= I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	पूर्ण

	/* Update the VSI after updating the VSI queue-mapping
	 * inक्रमmation
	 */
	ret = i40e_aq_update_vsi_params(hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Update vsi tc config failed, err %s aq_err %s\n",
			 i40e_stat_str(hw, ret),
			 i40e_aq_str(hw, hw->aq.asq_last_status));
		जाओ out;
	पूर्ण
	/* update the local VSI info with updated queue map */
	i40e_vsi_update_queue_map(vsi, &ctxt);
	vsi->info.valid_sections = 0;

	/* Update current VSI BW inक्रमmation */
	ret = i40e_vsi_get_bw_info(vsi);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Failed updating vsi bw info, err %s aq_err %s\n",
			 i40e_stat_str(hw, ret),
			 i40e_aq_str(hw, hw->aq.asq_last_status));
		जाओ out;
	पूर्ण

	/* Update the netdev TC setup */
	i40e_vsi_config_netdev_tc(vsi, enabled_tc);
out:
	वापस ret;
पूर्ण

/**
 * i40e_get_link_speed - Returns link speed क्रम the पूर्णांकerface
 * @vsi: VSI to be configured
 *
 **/
अटल पूर्णांक i40e_get_link_speed(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;

	चयन (pf->hw.phy.link_info.link_speed) अणु
	हाल I40E_LINK_SPEED_40GB:
		वापस 40000;
	हाल I40E_LINK_SPEED_25GB:
		वापस 25000;
	हाल I40E_LINK_SPEED_20GB:
		वापस 20000;
	हाल I40E_LINK_SPEED_10GB:
		वापस 10000;
	हाल I40E_LINK_SPEED_1GB:
		वापस 1000;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * i40e_set_bw_limit - setup BW limit क्रम Tx traffic based on max_tx_rate
 * @vsi: VSI to be configured
 * @seid: seid of the channel/VSI
 * @max_tx_rate: max TX rate to be configured as BW limit
 *
 * Helper function to set BW limit क्रम a given VSI
 **/
पूर्णांक i40e_set_bw_limit(काष्ठा i40e_vsi *vsi, u16 seid, u64 max_tx_rate)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	u64 credits = 0;
	पूर्णांक speed = 0;
	पूर्णांक ret = 0;

	speed = i40e_get_link_speed(vsi);
	अगर (max_tx_rate > speed) अणु
		dev_err(&pf->pdev->dev,
			"Invalid max tx rate %llu specified for VSI seid %d.",
			max_tx_rate, seid);
		वापस -EINVAL;
	पूर्ण
	अगर (max_tx_rate && max_tx_rate < 50) अणु
		dev_warn(&pf->pdev->dev,
			 "Setting max tx rate to minimum usable value of 50Mbps.\n");
		max_tx_rate = 50;
	पूर्ण

	/* Tx rate credits are in values of 50Mbps, 0 is disabled */
	credits = max_tx_rate;
	करो_भाग(credits, I40E_BW_CREDIT_DIVISOR);
	ret = i40e_aq_config_vsi_bw_limit(&pf->hw, seid, credits,
					  I40E_MAX_BW_INACTIVE_ACCUM, शून्य);
	अगर (ret)
		dev_err(&pf->pdev->dev,
			"Failed set tx rate (%llu Mbps) for vsi->seid %u, err %s aq_err %s\n",
			max_tx_rate, seid, i40e_stat_str(&pf->hw, ret),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
	वापस ret;
पूर्ण

/**
 * i40e_हटाओ_queue_channels - Remove queue channels क्रम the TCs
 * @vsi: VSI to be configured
 *
 * Remove queue channels क्रम the TCs
 **/
अटल व्योम i40e_हटाओ_queue_channels(काष्ठा i40e_vsi *vsi)
अणु
	क्रमागत i40e_admin_queue_err last_aq_status;
	काष्ठा i40e_cloud_filter *cfilter;
	काष्ठा i40e_channel *ch, *ch_पंचांगp;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा hlist_node *node;
	पूर्णांक ret, i;

	/* Reset rss size that was stored when reconfiguring rss क्रम
	 * channel VSIs with non-घातer-of-2 queue count.
	 */
	vsi->current_rss_size = 0;

	/* perक्रमm cleanup क्रम channels अगर they exist */
	अगर (list_empty(&vsi->ch_list))
		वापस;

	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->ch_list, list) अणु
		काष्ठा i40e_vsi *p_vsi;

		list_del(&ch->list);
		p_vsi = ch->parent_vsi;
		अगर (!p_vsi || !ch->initialized) अणु
			kमुक्त(ch);
			जारी;
		पूर्ण
		/* Reset queue contexts */
		क्रम (i = 0; i < ch->num_queue_pairs; i++) अणु
			काष्ठा i40e_ring *tx_ring, *rx_ring;
			u16 pf_q;

			pf_q = ch->base_queue + i;
			tx_ring = vsi->tx_rings[pf_q];
			tx_ring->ch = शून्य;

			rx_ring = vsi->rx_rings[pf_q];
			rx_ring->ch = शून्य;
		पूर्ण

		/* Reset BW configured क्रम this VSI via mqprio */
		ret = i40e_set_bw_limit(vsi, ch->seid, 0);
		अगर (ret)
			dev_info(&vsi->back->pdev->dev,
				 "Failed to reset tx rate for ch->seid %u\n",
				 ch->seid);

		/* delete cloud filters associated with this channel */
		hlist_क्रम_each_entry_safe(cfilter, node,
					  &pf->cloud_filter_list, cloud_node) अणु
			अगर (cfilter->seid != ch->seid)
				जारी;

			hash_del(&cfilter->cloud_node);
			अगर (cfilter->dst_port)
				ret = i40e_add_del_cloud_filter_big_buf(vsi,
									cfilter,
									false);
			अन्यथा
				ret = i40e_add_del_cloud_filter(vsi, cfilter,
								false);
			last_aq_status = pf->hw.aq.asq_last_status;
			अगर (ret)
				dev_info(&pf->pdev->dev,
					 "Failed to delete cloud filter, err %s aq_err %s\n",
					 i40e_stat_str(&pf->hw, ret),
					 i40e_aq_str(&pf->hw, last_aq_status));
			kमुक्त(cfilter);
		पूर्ण

		/* delete VSI from FW */
		ret = i40e_aq_delete_element(&vsi->back->hw, ch->seid,
					     शून्य);
		अगर (ret)
			dev_err(&vsi->back->pdev->dev,
				"unable to remove channel (%d) for parent VSI(%d)\n",
				ch->seid, p_vsi->seid);
		kमुक्त(ch);
	पूर्ण
	INIT_LIST_HEAD(&vsi->ch_list);
पूर्ण

/**
 * i40e_is_any_channel - channel exist or not
 * @vsi: ptr to VSI to which channels are associated with
 *
 * Returns true or false अगर channel(s) exist क्रम associated VSI or not
 **/
अटल bool i40e_is_any_channel(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_channel *ch, *ch_पंचांगp;

	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->ch_list, list) अणु
		अगर (ch->initialized)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * i40e_get_max_queues_क्रम_channel
 * @vsi: ptr to VSI to which channels are associated with
 *
 * Helper function which वापसs max value among the queue counts set on the
 * channels/TCs created.
 **/
अटल पूर्णांक i40e_get_max_queues_क्रम_channel(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_channel *ch, *ch_पंचांगp;
	पूर्णांक max = 0;

	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->ch_list, list) अणु
		अगर (!ch->initialized)
			जारी;
		अगर (ch->num_queue_pairs > max)
			max = ch->num_queue_pairs;
	पूर्ण

	वापस max;
पूर्ण

/**
 * i40e_validate_num_queues - validate num_queues w.r.t channel
 * @pf: ptr to PF device
 * @num_queues: number of queues
 * @vsi: the parent VSI
 * @reconfig_rss: indicates should the RSS be reconfigured or not
 *
 * This function validates number of queues in the context of new channel
 * which is being established and determines अगर RSS should be reconfigured
 * or not क्रम parent VSI.
 **/
अटल पूर्णांक i40e_validate_num_queues(काष्ठा i40e_pf *pf, पूर्णांक num_queues,
				    काष्ठा i40e_vsi *vsi, bool *reconfig_rss)
अणु
	पूर्णांक max_ch_queues;

	अगर (!reconfig_rss)
		वापस -EINVAL;

	*reconfig_rss = false;
	अगर (vsi->current_rss_size) अणु
		अगर (num_queues > vsi->current_rss_size) अणु
			dev_dbg(&pf->pdev->dev,
				"Error: num_queues (%d) > vsi's current_size(%d)\n",
				num_queues, vsi->current_rss_size);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर ((num_queues < vsi->current_rss_size) &&
			   (!is_घातer_of_2(num_queues))) अणु
			dev_dbg(&pf->pdev->dev,
				"Error: num_queues (%d) < vsi's current_size(%d), but not power of 2\n",
				num_queues, vsi->current_rss_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!is_घातer_of_2(num_queues)) अणु
		/* Find the max num_queues configured क्रम channel अगर channel
		 * exist.
		 * अगर channel exist, then enक्रमce 'num_queues' to be more than
		 * max ever queues configured क्रम channel.
		 */
		max_ch_queues = i40e_get_max_queues_क्रम_channel(vsi);
		अगर (num_queues < max_ch_queues) अणु
			dev_dbg(&pf->pdev->dev,
				"Error: num_queues (%d) < max queues configured for channel(%d)\n",
				num_queues, max_ch_queues);
			वापस -EINVAL;
		पूर्ण
		*reconfig_rss = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vsi_reconfig_rss - reconfig RSS based on specअगरied rss_size
 * @vsi: the VSI being setup
 * @rss_size: size of RSS, accordingly LUT माला_लो reprogrammed
 *
 * This function reconfigures RSS by reprogramming LUTs using 'rss_size'
 **/
अटल पूर्णांक i40e_vsi_reconfig_rss(काष्ठा i40e_vsi *vsi, u16 rss_size)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	u8 seed[I40E_HKEY_ARRAY_SIZE];
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक local_rss_size;
	u8 *lut;
	पूर्णांक ret;

	अगर (!vsi->rss_size)
		वापस -EINVAL;

	अगर (rss_size > vsi->rss_size)
		वापस -EINVAL;

	local_rss_size = min_t(पूर्णांक, vsi->rss_size, rss_size);
	lut = kzalloc(vsi->rss_table_size, GFP_KERNEL);
	अगर (!lut)
		वापस -ENOMEM;

	/* Ignoring user configured lut अगर there is one */
	i40e_fill_rss_lut(pf, lut, vsi->rss_table_size, local_rss_size);

	/* Use user configured hash key अगर there is one, otherwise
	 * use शेष.
	 */
	अगर (vsi->rss_hkey_user)
		स_नकल(seed, vsi->rss_hkey_user, I40E_HKEY_ARRAY_SIZE);
	अन्यथा
		netdev_rss_key_fill((व्योम *)seed, I40E_HKEY_ARRAY_SIZE);

	ret = i40e_config_rss(vsi, seed, lut, vsi->rss_table_size);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Cannot set RSS lut, err %s aq_err %s\n",
			 i40e_stat_str(hw, ret),
			 i40e_aq_str(hw, hw->aq.asq_last_status));
		kमुक्त(lut);
		वापस ret;
	पूर्ण
	kमुक्त(lut);

	/* Do the update w.r.t. storing rss_size */
	अगर (!vsi->orig_rss_size)
		vsi->orig_rss_size = vsi->rss_size;
	vsi->current_rss_size = local_rss_size;

	वापस ret;
पूर्ण

/**
 * i40e_channel_setup_queue_map - Setup a channel queue map
 * @pf: ptr to PF device
 * @ctxt: VSI context काष्ठाure
 * @ch: ptr to channel काष्ठाure
 *
 * Setup queue map क्रम a specअगरic channel
 **/
अटल व्योम i40e_channel_setup_queue_map(काष्ठा i40e_pf *pf,
					 काष्ठा i40e_vsi_context *ctxt,
					 काष्ठा i40e_channel *ch)
अणु
	u16 qcount, qmap, sections = 0;
	u8 offset = 0;
	पूर्णांक घात;

	sections = I40E_AQ_VSI_PROP_QUEUE_MAP_VALID;
	sections |= I40E_AQ_VSI_PROP_SCHED_VALID;

	qcount = min_t(पूर्णांक, ch->num_queue_pairs, pf->num_lan_msix);
	ch->num_queue_pairs = qcount;

	/* find the next higher घातer-of-2 of num queue pairs */
	घात = ilog2(qcount);
	अगर (!is_घातer_of_2(qcount))
		घात++;

	qmap = (offset << I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT) |
		(घात << I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT);

	/* Setup queue TC[0].qmap क्रम given VSI context */
	ctxt->info.tc_mapping[0] = cpu_to_le16(qmap);

	ctxt->info.up_enable_bits = 0x1; /* TC0 enabled */
	ctxt->info.mapping_flags |= cpu_to_le16(I40E_AQ_VSI_QUE_MAP_CONTIG);
	ctxt->info.queue_mapping[0] = cpu_to_le16(ch->base_queue);
	ctxt->info.valid_sections |= cpu_to_le16(sections);
पूर्ण

/**
 * i40e_add_channel - add a channel by adding VSI
 * @pf: ptr to PF device
 * @uplink_seid: underlying HW चयनing element (VEB) ID
 * @ch: ptr to channel काष्ठाure
 *
 * Add a channel (VSI) using add_vsi and queue_map
 **/
अटल पूर्णांक i40e_add_channel(काष्ठा i40e_pf *pf, u16 uplink_seid,
			    काष्ठा i40e_channel *ch)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vsi_context ctxt;
	u8 enabled_tc = 0x1; /* TC0 enabled */
	पूर्णांक ret;

	अगर (ch->type != I40E_VSI_VMDQ2) अणु
		dev_info(&pf->pdev->dev,
			 "add new vsi failed, ch->type %d\n", ch->type);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&ctxt, 0, माप(ctxt));
	ctxt.pf_num = hw->pf_id;
	ctxt.vf_num = 0;
	ctxt.uplink_seid = uplink_seid;
	ctxt.connection_type = I40E_AQ_VSI_CONN_TYPE_NORMAL;
	अगर (ch->type == I40E_VSI_VMDQ2)
		ctxt.flags = I40E_AQ_VSI_TYPE_VMDQ2;

	अगर (pf->flags & I40E_FLAG_VEB_MODE_ENABLED) अणु
		ctxt.info.valid_sections |=
		     cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
		ctxt.info.चयन_id =
		   cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);
	पूर्ण

	/* Set queue map क्रम a given VSI context */
	i40e_channel_setup_queue_map(pf, &ctxt, ch);

	/* Now समय to create VSI */
	ret = i40e_aq_add_vsi(hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "add new vsi failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw,
				     pf->hw.aq.asq_last_status));
		वापस -ENOENT;
	पूर्ण

	/* Success, update channel, set enabled_tc only अगर the channel
	 * is not a macvlan
	 */
	ch->enabled_tc = !i40e_is_channel_macvlan(ch) && enabled_tc;
	ch->seid = ctxt.seid;
	ch->vsi_number = ctxt.vsi_number;
	ch->stat_counter_idx = le16_to_cpu(ctxt.info.stat_counter_idx);

	/* copy just the sections touched not the entire info
	 * since not all sections are valid as वापसed by
	 * update vsi params
	 */
	ch->info.mapping_flags = ctxt.info.mapping_flags;
	स_नकल(&ch->info.queue_mapping,
	       &ctxt.info.queue_mapping, माप(ctxt.info.queue_mapping));
	स_नकल(&ch->info.tc_mapping, ctxt.info.tc_mapping,
	       माप(ctxt.info.tc_mapping));

	वापस 0;
पूर्ण

अटल पूर्णांक i40e_channel_config_bw(काष्ठा i40e_vsi *vsi, काष्ठा i40e_channel *ch,
				  u8 *bw_share)
अणु
	काष्ठा i40e_aqc_configure_vsi_tc_bw_data bw_data;
	i40e_status ret;
	पूर्णांक i;

	स_रखो(&bw_data, 0, माप(bw_data));
	bw_data.tc_valid_bits = ch->enabled_tc;
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		bw_data.tc_bw_credits[i] = bw_share[i];

	ret = i40e_aq_config_vsi_tc_bw(&vsi->back->hw, ch->seid,
				       &bw_data, शून्य);
	अगर (ret) अणु
		dev_info(&vsi->back->pdev->dev,
			 "Config VSI BW allocation per TC failed, aq_err: %d for new_vsi->seid %u\n",
			 vsi->back->hw.aq.asq_last_status, ch->seid);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		ch->info.qs_handle[i] = bw_data.qs_handles[i];

	वापस 0;
पूर्ण

/**
 * i40e_channel_config_tx_ring - config TX ring associated with new channel
 * @pf: ptr to PF device
 * @vsi: the VSI being setup
 * @ch: ptr to channel काष्ठाure
 *
 * Configure TX rings associated with channel (VSI) since queues are being
 * from parent VSI.
 **/
अटल पूर्णांक i40e_channel_config_tx_ring(काष्ठा i40e_pf *pf,
				       काष्ठा i40e_vsi *vsi,
				       काष्ठा i40e_channel *ch)
अणु
	i40e_status ret;
	पूर्णांक i;
	u8 bw_share[I40E_MAX_TRAFFIC_CLASS] = अणु0पूर्ण;

	/* Enable ETS TCs with equal BW Share क्रम now across all VSIs */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (ch->enabled_tc & BIT(i))
			bw_share[i] = 1;
	पूर्ण

	/* configure BW क्रम new VSI */
	ret = i40e_channel_config_bw(vsi, ch, bw_share);
	अगर (ret) अणु
		dev_info(&vsi->back->pdev->dev,
			 "Failed configuring TC map %d for channel (seid %u)\n",
			 ch->enabled_tc, ch->seid);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ch->num_queue_pairs; i++) अणु
		काष्ठा i40e_ring *tx_ring, *rx_ring;
		u16 pf_q;

		pf_q = ch->base_queue + i;

		/* Get to TX ring ptr of मुख्य VSI, क्रम re-setup TX queue
		 * context
		 */
		tx_ring = vsi->tx_rings[pf_q];
		tx_ring->ch = ch;

		/* Get the RX ring ptr */
		rx_ring = vsi->rx_rings[pf_q];
		rx_ring->ch = ch;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_setup_hw_channel - setup new channel
 * @pf: ptr to PF device
 * @vsi: the VSI being setup
 * @ch: ptr to channel काष्ठाure
 * @uplink_seid: underlying HW चयनing element (VEB) ID
 * @type: type of channel to be created (VMDq2/VF)
 *
 * Setup new channel (VSI) based on specअगरied type (VMDq2/VF)
 * and configures TX rings accordingly
 **/
अटल अंतरभूत पूर्णांक i40e_setup_hw_channel(काष्ठा i40e_pf *pf,
					काष्ठा i40e_vsi *vsi,
					काष्ठा i40e_channel *ch,
					u16 uplink_seid, u8 type)
अणु
	पूर्णांक ret;

	ch->initialized = false;
	ch->base_queue = vsi->next_base_queue;
	ch->type = type;

	/* Proceed with creation of channel (VMDq2) VSI */
	ret = i40e_add_channel(pf, uplink_seid, ch);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "failed to add_channel using uplink_seid %u\n",
			 uplink_seid);
		वापस ret;
	पूर्ण

	/* Mark the successful creation of channel */
	ch->initialized = true;

	/* Reconfigure TX queues using QTX_CTL रेजिस्टर */
	ret = i40e_channel_config_tx_ring(pf, vsi, ch);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "failed to configure TX rings for channel %u\n",
			 ch->seid);
		वापस ret;
	पूर्ण

	/* update 'next_base_queue' */
	vsi->next_base_queue = vsi->next_base_queue + ch->num_queue_pairs;
	dev_dbg(&pf->pdev->dev,
		"Added channel: vsi_seid %u, vsi_number %u, stat_counter_idx %u, num_queue_pairs %u, pf->next_base_queue %d\n",
		ch->seid, ch->vsi_number, ch->stat_counter_idx,
		ch->num_queue_pairs,
		vsi->next_base_queue);
	वापस ret;
पूर्ण

/**
 * i40e_setup_channel - setup new channel using uplink element
 * @pf: ptr to PF device
 * @vsi: poपूर्णांकer to the VSI to set up the channel within
 * @ch: ptr to channel काष्ठाure
 *
 * Setup new channel (VSI) based on specअगरied type (VMDq2/VF)
 * and uplink चयनing element (uplink_seid)
 **/
अटल bool i40e_setup_channel(काष्ठा i40e_pf *pf, काष्ठा i40e_vsi *vsi,
			       काष्ठा i40e_channel *ch)
अणु
	u8 vsi_type;
	u16 seid;
	पूर्णांक ret;

	अगर (vsi->type == I40E_VSI_MAIN) अणु
		vsi_type = I40E_VSI_VMDQ2;
	पूर्ण अन्यथा अणु
		dev_err(&pf->pdev->dev, "unsupported parent vsi type(%d)\n",
			vsi->type);
		वापस false;
	पूर्ण

	/* underlying चयनing element */
	seid = pf->vsi[pf->lan_vsi]->uplink_seid;

	/* create channel (VSI), configure TX rings */
	ret = i40e_setup_hw_channel(pf, vsi, ch, seid, vsi_type);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev, "failed to setup hw_channel\n");
		वापस false;
	पूर्ण

	वापस ch->initialized ? true : false;
पूर्ण

/**
 * i40e_validate_and_set_चयन_mode - sets up चयन mode correctly
 * @vsi: ptr to VSI which has PF backing
 *
 * Sets up चयन mode correctly अगर it needs to be changed and perक्रमm
 * what are allowed modes.
 **/
अटल पूर्णांक i40e_validate_and_set_चयन_mode(काष्ठा i40e_vsi *vsi)
अणु
	u8 mode;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक ret;

	ret = i40e_get_capabilities(pf, i40e_aqc_opc_list_dev_capabilities);
	अगर (ret)
		वापस -EINVAL;

	अगर (hw->dev_caps.चयन_mode) अणु
		/* अगर चयन mode is set, support mode2 (non-tunneled क्रम
		 * cloud filter) क्रम now
		 */
		u32 चयन_mode = hw->dev_caps.चयन_mode &
				  I40E_SWITCH_MODE_MASK;
		अगर (चयन_mode >= I40E_CLOUD_FILTER_MODE1) अणु
			अगर (चयन_mode == I40E_CLOUD_FILTER_MODE2)
				वापस 0;
			dev_err(&pf->pdev->dev,
				"Invalid switch_mode (%d), only non-tunneled mode for cloud filter is supported\n",
				hw->dev_caps.चयन_mode);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Set Bit 7 to be valid */
	mode = I40E_AQ_SET_SWITCH_BIT7_VALID;

	/* Set L4type क्रम TCP support */
	mode |= I40E_AQ_SET_SWITCH_L4_TYPE_TCP;

	/* Set cloud filter mode */
	mode |= I40E_AQ_SET_SWITCH_MODE_NON_TUNNEL;

	/* Prep mode field क्रम set_चयन_config */
	ret = i40e_aq_set_चयन_config(hw, pf->last_sw_conf_flags,
					pf->last_sw_conf_valid_flags,
					mode, शून्य);
	अगर (ret && hw->aq.asq_last_status != I40E_AQ_RC_ESRCH)
		dev_err(&pf->pdev->dev,
			"couldn't set switch config bits, err %s aq_err %s\n",
			i40e_stat_str(hw, ret),
			i40e_aq_str(hw,
				    hw->aq.asq_last_status));

	वापस ret;
पूर्ण

/**
 * i40e_create_queue_channel - function to create channel
 * @vsi: VSI to be configured
 * @ch: ptr to channel (it contains channel specअगरic params)
 *
 * This function creates channel (VSI) using num_queues specअगरied by user,
 * reconfigs RSS अगर needed.
 **/
पूर्णांक i40e_create_queue_channel(काष्ठा i40e_vsi *vsi,
			      काष्ठा i40e_channel *ch)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	bool reconfig_rss;
	पूर्णांक err;

	अगर (!ch)
		वापस -EINVAL;

	अगर (!ch->num_queue_pairs) अणु
		dev_err(&pf->pdev->dev, "Invalid num_queues requested: %d\n",
			ch->num_queue_pairs);
		वापस -EINVAL;
	पूर्ण

	/* validate user requested num_queues क्रम channel */
	err = i40e_validate_num_queues(pf, ch->num_queue_pairs, vsi,
				       &reconfig_rss);
	अगर (err) अणु
		dev_info(&pf->pdev->dev, "Failed to validate num_queues (%d)\n",
			 ch->num_queue_pairs);
		वापस -EINVAL;
	पूर्ण

	/* By शेष we are in VEPA mode, अगर this is the first VF/VMDq
	 * VSI to be added चयन to VEB mode.
	 */
	अगर ((!(pf->flags & I40E_FLAG_VEB_MODE_ENABLED)) ||
	    (!i40e_is_any_channel(vsi))) अणु
		अगर (!is_घातer_of_2(vsi->tc_config.tc_info[0].qcount)) अणु
			dev_dbg(&pf->pdev->dev,
				"Failed to create channel. Override queues (%u) not power of 2\n",
				vsi->tc_config.tc_info[0].qcount);
			वापस -EINVAL;
		पूर्ण

		अगर (!(pf->flags & I40E_FLAG_VEB_MODE_ENABLED)) अणु
			pf->flags |= I40E_FLAG_VEB_MODE_ENABLED;

			अगर (vsi->type == I40E_VSI_MAIN) अणु
				अगर (pf->flags & I40E_FLAG_TC_MQPRIO)
					i40e_करो_reset(pf, I40E_PF_RESET_FLAG,
						      true);
				अन्यथा
					i40e_करो_reset_safe(pf,
							   I40E_PF_RESET_FLAG);
			पूर्ण
		पूर्ण
		/* now onwards क्रम मुख्य VSI, number of queues will be value
		 * of TC0's queue count
		 */
	पूर्ण

	/* By this समय, vsi->cnt_q_avail shall be set to non-zero and
	 * it should be more than num_queues
	 */
	अगर (!vsi->cnt_q_avail || vsi->cnt_q_avail < ch->num_queue_pairs) अणु
		dev_dbg(&pf->pdev->dev,
			"Error: cnt_q_avail (%u) less than num_queues %d\n",
			vsi->cnt_q_avail, ch->num_queue_pairs);
		वापस -EINVAL;
	पूर्ण

	/* reconfig_rss only अगर vsi type is MAIN_VSI */
	अगर (reconfig_rss && (vsi->type == I40E_VSI_MAIN)) अणु
		err = i40e_vsi_reconfig_rss(vsi, ch->num_queue_pairs);
		अगर (err) अणु
			dev_info(&pf->pdev->dev,
				 "Error: unable to reconfig rss for num_queues (%u)\n",
				 ch->num_queue_pairs);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!i40e_setup_channel(pf, vsi, ch)) अणु
		dev_info(&pf->pdev->dev, "Failed to setup channel\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(&pf->pdev->dev,
		 "Setup channel (id:%u) utilizing num_queues %d\n",
		 ch->seid, ch->num_queue_pairs);

	/* configure VSI क्रम BW limit */
	अगर (ch->max_tx_rate) अणु
		u64 credits = ch->max_tx_rate;

		अगर (i40e_set_bw_limit(vsi, ch->seid, ch->max_tx_rate))
			वापस -EINVAL;

		करो_भाग(credits, I40E_BW_CREDIT_DIVISOR);
		dev_dbg(&pf->pdev->dev,
			"Set tx rate of %llu Mbps (count of 50Mbps %llu) for vsi->seid %u\n",
			ch->max_tx_rate,
			credits,
			ch->seid);
	पूर्ण

	/* in हाल of VF, this will be मुख्य SRIOV VSI */
	ch->parent_vsi = vsi;

	/* and update मुख्य_vsi's count क्रम queue_available to use */
	vsi->cnt_q_avail -= ch->num_queue_pairs;

	वापस 0;
पूर्ण

/**
 * i40e_configure_queue_channels - Add queue channel क्रम the given TCs
 * @vsi: VSI to be configured
 *
 * Configures queue channel mapping to the given TCs
 **/
अटल पूर्णांक i40e_configure_queue_channels(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_channel *ch;
	u64 max_rate = 0;
	पूर्णांक ret = 0, i;

	/* Create app vsi with the TCs. Main VSI with TC0 is alपढ़ोy set up */
	vsi->tc_seid_map[0] = vsi->seid;
	क्रम (i = 1; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (vsi->tc_config.enabled_tc & BIT(i)) अणु
			ch = kzalloc(माप(*ch), GFP_KERNEL);
			अगर (!ch) अणु
				ret = -ENOMEM;
				जाओ err_मुक्त;
			पूर्ण

			INIT_LIST_HEAD(&ch->list);
			ch->num_queue_pairs =
				vsi->tc_config.tc_info[i].qcount;
			ch->base_queue =
				vsi->tc_config.tc_info[i].qoffset;

			/* Bandwidth limit through tc पूर्णांकerface is in bytes/s,
			 * change to Mbit/s
			 */
			max_rate = vsi->mqprio_qopt.max_rate[i];
			करो_भाग(max_rate, I40E_BW_MBPS_DIVISOR);
			ch->max_tx_rate = max_rate;

			list_add_tail(&ch->list, &vsi->ch_list);

			ret = i40e_create_queue_channel(vsi, ch);
			अगर (ret) अणु
				dev_err(&vsi->back->pdev->dev,
					"Failed creating queue channel with TC%d: queues %d\n",
					i, ch->num_queue_pairs);
				जाओ err_मुक्त;
			पूर्ण
			vsi->tc_seid_map[i] = ch->seid;
		पूर्ण
	पूर्ण
	वापस ret;

err_मुक्त:
	i40e_हटाओ_queue_channels(vsi);
	वापस ret;
पूर्ण

/**
 * i40e_veb_config_tc - Configure TCs क्रम given VEB
 * @veb: given VEB
 * @enabled_tc: TC biपंचांगap
 *
 * Configures given TC biपंचांगap क्रम VEB (चयनing) element
 **/
पूर्णांक i40e_veb_config_tc(काष्ठा i40e_veb *veb, u8 enabled_tc)
अणु
	काष्ठा i40e_aqc_configure_चयनing_comp_bw_config_data bw_data = अणु0पूर्ण;
	काष्ठा i40e_pf *pf = veb->pf;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* No TCs or alपढ़ोy enabled TCs just वापस */
	अगर (!enabled_tc || veb->enabled_tc == enabled_tc)
		वापस ret;

	bw_data.tc_valid_bits = enabled_tc;
	/* bw_data.असलolute_credits is not set (relative) */

	/* Enable ETS TCs with equal BW Share क्रम now */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (enabled_tc & BIT(i))
			bw_data.tc_bw_share_credits[i] = 1;
	पूर्ण

	ret = i40e_aq_config_चयन_comp_bw_config(&pf->hw, veb->seid,
						   &bw_data, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "VEB bw config failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		जाओ out;
	पूर्ण

	/* Update the BW inक्रमmation */
	ret = i40e_veb_get_bw_info(veb);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Failed getting veb bw config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
	पूर्ण

out:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_I40E_DCB
/**
 * i40e_dcb_reconfigure - Reconfigure all VEBs and VSIs
 * @pf: PF काष्ठा
 *
 * Reconfigure VEB/VSIs on a given PF; it is assumed that
 * the caller would've quiesce all the VSIs beक्रमe calling
 * this function
 **/
अटल व्योम i40e_dcb_reconfigure(काष्ठा i40e_pf *pf)
अणु
	u8 tc_map = 0;
	पूर्णांक ret;
	u8 v;

	/* Enable the TCs available on PF to all VEBs */
	tc_map = i40e_pf_get_tc_map(pf);
	अगर (tc_map == I40E_DEFAULT_TRAFFIC_CLASS)
		वापस;

	क्रम (v = 0; v < I40E_MAX_VEB; v++) अणु
		अगर (!pf->veb[v])
			जारी;
		ret = i40e_veb_config_tc(pf->veb[v], tc_map);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "Failed configuring TC for VEB seid=%d\n",
				 pf->veb[v]->seid);
			/* Will try to configure as many components */
		पूर्ण
	पूर्ण

	/* Update each VSI */
	क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
		अगर (!pf->vsi[v])
			जारी;

		/* - Enable all TCs क्रम the LAN VSI
		 * - For all others keep them at TC0 क्रम now
		 */
		अगर (v == pf->lan_vsi)
			tc_map = i40e_pf_get_tc_map(pf);
		अन्यथा
			tc_map = I40E_DEFAULT_TRAFFIC_CLASS;

		ret = i40e_vsi_config_tc(pf->vsi[v], tc_map);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "Failed configuring TC for VSI seid=%d\n",
				 pf->vsi[v]->seid);
			/* Will try to configure as many components */
		पूर्ण अन्यथा अणु
			/* Re-configure VSI vectors based on updated TC map */
			i40e_vsi_map_rings_to_vectors(pf->vsi[v]);
			अगर (pf->vsi[v]->netdev)
				i40e_dcbnl_set_all(pf->vsi[v]);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_resume_port_tx - Resume port Tx
 * @pf: PF काष्ठा
 *
 * Resume a port's Tx and issue a PF reset in हाल of failure to
 * resume.
 **/
अटल पूर्णांक i40e_resume_port_tx(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक ret;

	ret = i40e_aq_resume_port_tx(hw, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Resume Port Tx failed, err %s aq_err %s\n",
			  i40e_stat_str(&pf->hw, ret),
			  i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		/* Schedule PF reset to recover */
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		i40e_service_event_schedule(pf);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_suspend_port_tx - Suspend port Tx
 * @pf: PF काष्ठा
 *
 * Suspend a port's Tx and issue a PF reset in हाल of failure.
 **/
अटल पूर्णांक i40e_suspend_port_tx(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक ret;

	ret = i40e_aq_suspend_port_tx(hw, pf->mac_seid, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Suspend Port Tx failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		/* Schedule PF reset to recover */
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		i40e_service_event_schedule(pf);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_hw_set_dcb_config - Program new DCBX settings पूर्णांकo HW
 * @pf: PF being configured
 * @new_cfg: New DCBX configuration
 *
 * Program DCB settings पूर्णांकo HW and reconfigure VEB/VSIs on
 * given PF. Uses "Set LLDP MIB" AQC to program the hardware.
 **/
अटल पूर्णांक i40e_hw_set_dcb_config(काष्ठा i40e_pf *pf,
				  काष्ठा i40e_dcbx_config *new_cfg)
अणु
	काष्ठा i40e_dcbx_config *old_cfg = &pf->hw.local_dcbx_config;
	पूर्णांक ret;

	/* Check अगर need reconfiguration */
	अगर (!स_भेद(&new_cfg, &old_cfg, माप(new_cfg))) अणु
		dev_dbg(&pf->pdev->dev, "No Change in DCB Config required.\n");
		वापस 0;
	पूर्ण

	/* Config change disable all VSIs */
	i40e_pf_quiesce_all_vsi(pf);

	/* Copy the new config to the current config */
	*old_cfg = *new_cfg;
	old_cfg->etsrec = old_cfg->etscfg;
	ret = i40e_set_dcb_config(&pf->hw);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Set DCB Config failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		जाओ out;
	पूर्ण

	/* Changes in configuration update VEB/VSI */
	i40e_dcb_reconfigure(pf);
out:
	/* In हाल of reset करो not try to resume anything */
	अगर (!test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state)) अणु
		/* Re-start the VSIs अगर disabled */
		ret = i40e_resume_port_tx(pf);
		/* In हाल of error no poपूर्णांक in resuming VSIs */
		अगर (ret)
			जाओ err;
		i40e_pf_unquiesce_all_vsi(pf);
	पूर्ण
err:
	वापस ret;
पूर्ण

/**
 * i40e_hw_dcb_config - Program new DCBX settings पूर्णांकo HW
 * @pf: PF being configured
 * @new_cfg: New DCBX configuration
 *
 * Program DCB settings पूर्णांकo HW and reconfigure VEB/VSIs on
 * given PF
 **/
पूर्णांक i40e_hw_dcb_config(काष्ठा i40e_pf *pf, काष्ठा i40e_dcbx_config *new_cfg)
अणु
	काष्ठा i40e_aqc_configure_चयनing_comp_ets_data ets_data;
	u8 prio_type[I40E_MAX_TRAFFIC_CLASS] = अणु0पूर्ण;
	u32 mfs_tc[I40E_MAX_TRAFFIC_CLASS];
	काष्ठा i40e_dcbx_config *old_cfg;
	u8 mode[I40E_MAX_TRAFFIC_CLASS];
	काष्ठा i40e_rx_pb_config pb_cfg;
	काष्ठा i40e_hw *hw = &pf->hw;
	u8 num_ports = hw->num_ports;
	bool need_reconfig;
	पूर्णांक ret = -EINVAL;
	u8 lltc_map = 0;
	u8 tc_map = 0;
	u8 new_numtc;
	u8 i;

	dev_dbg(&pf->pdev->dev, "Configuring DCB registers directly\n");
	/* Un-pack inक्रमmation to Program ETS HW via shared API
	 * numtc, tcmap
	 * LLTC map
	 * ETS/NON-ETS arbiter mode
	 * max exponent (credit refills)
	 * Total number of ports
	 * PFC priority bit-map
	 * Priority Table
	 * BW % per TC
	 * Arbiter mode between UPs sharing same TC
	 * TSA table (ETS or non-ETS)
	 * EEE enabled or not
	 * MFS TC table
	 */

	new_numtc = i40e_dcb_get_num_tc(new_cfg);

	स_रखो(&ets_data, 0, माप(ets_data));
	क्रम (i = 0; i < new_numtc; i++) अणु
		tc_map |= BIT(i);
		चयन (new_cfg->etscfg.tsatable[i]) अणु
		हाल I40E_IEEE_TSA_ETS:
			prio_type[i] = I40E_DCB_PRIO_TYPE_ETS;
			ets_data.tc_bw_share_credits[i] =
					new_cfg->etscfg.tcbwtable[i];
			अवरोध;
		हाल I40E_IEEE_TSA_STRICT:
			prio_type[i] = I40E_DCB_PRIO_TYPE_STRICT;
			lltc_map |= BIT(i);
			ets_data.tc_bw_share_credits[i] =
					I40E_DCB_STRICT_PRIO_CREDITS;
			अवरोध;
		शेष:
			/* Invalid TSA type */
			need_reconfig = false;
			जाओ out;
		पूर्ण
	पूर्ण

	old_cfg = &hw->local_dcbx_config;
	/* Check अगर need reconfiguration */
	need_reconfig = i40e_dcb_need_reconfig(pf, old_cfg, new_cfg);

	/* If needed, enable/disable frame tagging, disable all VSIs
	 * and suspend port tx
	 */
	अगर (need_reconfig) अणु
		/* Enable DCB tagging only when more than one TC */
		अगर (new_numtc > 1)
			pf->flags |= I40E_FLAG_DCB_ENABLED;
		अन्यथा
			pf->flags &= ~I40E_FLAG_DCB_ENABLED;

		set_bit(__I40E_PORT_SUSPENDED, pf->state);
		/* Reconfiguration needed quiesce all VSIs */
		i40e_pf_quiesce_all_vsi(pf);
		ret = i40e_suspend_port_tx(pf);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Configure Port ETS Tx Scheduler */
	ets_data.tc_valid_bits = tc_map;
	ets_data.tc_strict_priority_flags = lltc_map;
	ret = i40e_aq_config_चयन_comp_ets
		(hw, pf->mac_seid, &ets_data,
		 i40e_aqc_opc_modअगरy_चयनing_comp_ets, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Modify Port ETS failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		जाओ out;
	पूर्ण

	/* Configure Rx ETS HW */
	स_रखो(&mode, I40E_DCB_ARB_MODE_ROUND_ROBIN, माप(mode));
	i40e_dcb_hw_set_num_tc(hw, new_numtc);
	i40e_dcb_hw_rx_fअगरo_config(hw, I40E_DCB_ARB_MODE_ROUND_ROBIN,
				   I40E_DCB_ARB_MODE_STRICT_PRIORITY,
				   I40E_DCB_DEFAULT_MAX_EXPONENT,
				   lltc_map);
	i40e_dcb_hw_rx_cmd_monitor_config(hw, new_numtc, num_ports);
	i40e_dcb_hw_rx_ets_bw_config(hw, new_cfg->etscfg.tcbwtable, mode,
				     prio_type);
	i40e_dcb_hw_pfc_config(hw, new_cfg->pfc.pfcenable,
			       new_cfg->etscfg.prioritytable);
	i40e_dcb_hw_rx_up2tc_config(hw, new_cfg->etscfg.prioritytable);

	/* Configure Rx Packet Buffers in HW */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		mfs_tc[i] = pf->vsi[pf->lan_vsi]->netdev->mtu;
		mfs_tc[i] += I40E_PACKET_HDR_PAD;
	पूर्ण

	i40e_dcb_hw_calculate_pool_sizes(hw, num_ports,
					 false, new_cfg->pfc.pfcenable,
					 mfs_tc, &pb_cfg);
	i40e_dcb_hw_rx_pb_config(hw, &pf->pb_cfg, &pb_cfg);

	/* Update the local Rx Packet buffer config */
	pf->pb_cfg = pb_cfg;

	/* Inक्रमm the FW about changes to DCB configuration */
	ret = i40e_aq_dcb_updated(&pf->hw, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "DCB Updated failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		जाओ out;
	पूर्ण

	/* Update the port DCBx configuration */
	*old_cfg = *new_cfg;

	/* Changes in configuration update VEB/VSI */
	i40e_dcb_reconfigure(pf);
out:
	/* Re-start the VSIs अगर disabled */
	अगर (need_reconfig) अणु
		ret = i40e_resume_port_tx(pf);

		clear_bit(__I40E_PORT_SUSPENDED, pf->state);
		/* In हाल of error no poपूर्णांक in resuming VSIs */
		अगर (ret)
			जाओ err;

		/* Wait क्रम the PF's queues to be disabled */
		ret = i40e_pf_रुको_queues_disabled(pf);
		अगर (ret) अणु
			/* Schedule PF reset to recover */
			set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
			i40e_service_event_schedule(pf);
			जाओ err;
		पूर्ण अन्यथा अणु
			i40e_pf_unquiesce_all_vsi(pf);
			set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
			set_bit(__I40E_CLIENT_L2_CHANGE, pf->state);
		पूर्ण
		/* रेजिस्टरs are set, lets apply */
		अगर (pf->hw_features & I40E_HW_USE_SET_LLDP_MIB)
			ret = i40e_hw_set_dcb_config(pf, new_cfg);
	पूर्ण

err:
	वापस ret;
पूर्ण

/**
 * i40e_dcb_sw_शेष_config - Set शेष DCB configuration when DCB in SW
 * @pf: PF being queried
 *
 * Set शेष DCB configuration in हाल DCB is to be करोne in SW.
 **/
पूर्णांक i40e_dcb_sw_शेष_config(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_dcbx_config *dcb_cfg = &pf->hw.local_dcbx_config;
	काष्ठा i40e_aqc_configure_चयनing_comp_ets_data ets_data;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक err;

	अगर (pf->hw_features & I40E_HW_USE_SET_LLDP_MIB) अणु
		/* Update the local cached instance with TC0 ETS */
		स_रखो(&pf->पंचांगp_cfg, 0, माप(काष्ठा i40e_dcbx_config));
		pf->पंचांगp_cfg.etscfg.willing = I40E_IEEE_DEFAULT_ETS_WILLING;
		pf->पंचांगp_cfg.etscfg.maxtcs = 0;
		pf->पंचांगp_cfg.etscfg.tcbwtable[0] = I40E_IEEE_DEFAULT_ETS_TCBW;
		pf->पंचांगp_cfg.etscfg.tsatable[0] = I40E_IEEE_TSA_ETS;
		pf->पंचांगp_cfg.pfc.willing = I40E_IEEE_DEFAULT_PFC_WILLING;
		pf->पंचांगp_cfg.pfc.pfccap = I40E_MAX_TRAFFIC_CLASS;
		/* FW needs one App to configure HW */
		pf->पंचांगp_cfg.numapps = I40E_IEEE_DEFAULT_NUM_APPS;
		pf->पंचांगp_cfg.app[0].selector = I40E_APP_SEL_ETHTYPE;
		pf->पंचांगp_cfg.app[0].priority = I40E_IEEE_DEFAULT_APP_PRIO;
		pf->पंचांगp_cfg.app[0].protocolid = I40E_APP_PROTOID_FCOE;

		वापस i40e_hw_set_dcb_config(pf, &pf->पंचांगp_cfg);
	पूर्ण

	स_रखो(&ets_data, 0, माप(ets_data));
	ets_data.tc_valid_bits = I40E_DEFAULT_TRAFFIC_CLASS; /* TC0 only */
	ets_data.tc_strict_priority_flags = 0; /* ETS */
	ets_data.tc_bw_share_credits[0] = I40E_IEEE_DEFAULT_ETS_TCBW; /* 100% to TC0 */

	/* Enable ETS on the Physical port */
	err = i40e_aq_config_चयन_comp_ets
		(hw, pf->mac_seid, &ets_data,
		 i40e_aqc_opc_enable_चयनing_comp_ets, शून्य);
	अगर (err) अणु
		dev_info(&pf->pdev->dev,
			 "Enable Port ETS failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, err),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		err = -ENOENT;
		जाओ out;
	पूर्ण

	/* Update the local cached instance with TC0 ETS */
	dcb_cfg->etscfg.willing = I40E_IEEE_DEFAULT_ETS_WILLING;
	dcb_cfg->etscfg.cbs = 0;
	dcb_cfg->etscfg.maxtcs = I40E_MAX_TRAFFIC_CLASS;
	dcb_cfg->etscfg.tcbwtable[0] = I40E_IEEE_DEFAULT_ETS_TCBW;

out:
	वापस err;
पूर्ण

/**
 * i40e_init_pf_dcb - Initialize DCB configuration
 * @pf: PF being configured
 *
 * Query the current DCB configuration and cache it
 * in the hardware काष्ठाure
 **/
अटल पूर्णांक i40e_init_pf_dcb(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक err;

	/* Do not enable DCB क्रम SW1 and SW2 images even अगर the FW is capable
	 * Also करो not enable DCBx अगर FW LLDP agent is disabled
	 */
	अगर (pf->hw_features & I40E_HW_NO_DCB_SUPPORT) अणु
		dev_info(&pf->pdev->dev, "DCB is not supported.\n");
		err = I40E_NOT_SUPPORTED;
		जाओ out;
	पूर्ण
	अगर (pf->flags & I40E_FLAG_DISABLE_FW_LLDP) अणु
		dev_info(&pf->pdev->dev, "FW LLDP is disabled, attempting SW DCB\n");
		err = i40e_dcb_sw_शेष_config(pf);
		अगर (err) अणु
			dev_info(&pf->pdev->dev, "Could not initialize SW DCB\n");
			जाओ out;
		पूर्ण
		dev_info(&pf->pdev->dev, "SW DCB initialization succeeded.\n");
		pf->dcbx_cap = DCB_CAP_DCBX_HOST |
			       DCB_CAP_DCBX_VER_IEEE;
		/* at init capable but disabled */
		pf->flags |= I40E_FLAG_DCB_CAPABLE;
		pf->flags &= ~I40E_FLAG_DCB_ENABLED;
		जाओ out;
	पूर्ण
	err = i40e_init_dcb(hw, true);
	अगर (!err) अणु
		/* Device/Function is not DCBX capable */
		अगर ((!hw->func_caps.dcb) ||
		    (hw->dcbx_status == I40E_DCBX_STATUS_DISABLED)) अणु
			dev_info(&pf->pdev->dev,
				 "DCBX offload is not supported or is disabled for this PF.\n");
		पूर्ण अन्यथा अणु
			/* When status is not DISABLED then DCBX in FW */
			pf->dcbx_cap = DCB_CAP_DCBX_LLD_MANAGED |
				       DCB_CAP_DCBX_VER_IEEE;

			pf->flags |= I40E_FLAG_DCB_CAPABLE;
			/* Enable DCB tagging only when more than one TC
			 * or explicitly disable अगर only one TC
			 */
			अगर (i40e_dcb_get_num_tc(&hw->local_dcbx_config) > 1)
				pf->flags |= I40E_FLAG_DCB_ENABLED;
			अन्यथा
				pf->flags &= ~I40E_FLAG_DCB_ENABLED;
			dev_dbg(&pf->pdev->dev,
				"DCBX offload is supported for this PF.\n");
		पूर्ण
	पूर्ण अन्यथा अगर (pf->hw.aq.asq_last_status == I40E_AQ_RC_EPERM) अणु
		dev_info(&pf->pdev->dev, "FW LLDP disabled for this PF.\n");
		pf->flags |= I40E_FLAG_DISABLE_FW_LLDP;
	पूर्ण अन्यथा अणु
		dev_info(&pf->pdev->dev,
			 "Query for DCB configuration failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, err),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
	पूर्ण

out:
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_I40E_DCB */

/**
 * i40e_prपूर्णांक_link_message - prपूर्णांक link up or करोwn
 * @vsi: the VSI क्रम which link needs a message
 * @isup: true of link is up, false otherwise
 */
व्योम i40e_prपूर्णांक_link_message(काष्ठा i40e_vsi *vsi, bool isup)
अणु
	क्रमागत i40e_aq_link_speed new_speed;
	काष्ठा i40e_pf *pf = vsi->back;
	अक्षर *speed = "Unknown";
	अक्षर *fc = "Unknown";
	अक्षर *fec = "";
	अक्षर *req_fec = "";
	अक्षर *an = "";

	अगर (isup)
		new_speed = pf->hw.phy.link_info.link_speed;
	अन्यथा
		new_speed = I40E_LINK_SPEED_UNKNOWN;

	अगर ((vsi->current_isup == isup) && (vsi->current_speed == new_speed))
		वापस;
	vsi->current_isup = isup;
	vsi->current_speed = new_speed;
	अगर (!isup) अणु
		netdev_info(vsi->netdev, "NIC Link is Down\n");
		वापस;
	पूर्ण

	/* Warn user अगर link speed on NPAR enabled partition is not at
	 * least 10GB
	 */
	अगर (pf->hw.func_caps.npar_enable &&
	    (pf->hw.phy.link_info.link_speed == I40E_LINK_SPEED_1GB ||
	     pf->hw.phy.link_info.link_speed == I40E_LINK_SPEED_100MB))
		netdev_warn(vsi->netdev,
			    "The partition detected link speed that is less than 10Gbps\n");

	चयन (pf->hw.phy.link_info.link_speed) अणु
	हाल I40E_LINK_SPEED_40GB:
		speed = "40 G";
		अवरोध;
	हाल I40E_LINK_SPEED_20GB:
		speed = "20 G";
		अवरोध;
	हाल I40E_LINK_SPEED_25GB:
		speed = "25 G";
		अवरोध;
	हाल I40E_LINK_SPEED_10GB:
		speed = "10 G";
		अवरोध;
	हाल I40E_LINK_SPEED_5GB:
		speed = "5 G";
		अवरोध;
	हाल I40E_LINK_SPEED_2_5GB:
		speed = "2.5 G";
		अवरोध;
	हाल I40E_LINK_SPEED_1GB:
		speed = "1000 M";
		अवरोध;
	हाल I40E_LINK_SPEED_100MB:
		speed = "100 M";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (pf->hw.fc.current_mode) अणु
	हाल I40E_FC_FULL:
		fc = "RX/TX";
		अवरोध;
	हाल I40E_FC_TX_PAUSE:
		fc = "TX";
		अवरोध;
	हाल I40E_FC_RX_PAUSE:
		fc = "RX";
		अवरोध;
	शेष:
		fc = "None";
		अवरोध;
	पूर्ण

	अगर (pf->hw.phy.link_info.link_speed == I40E_LINK_SPEED_25GB) अणु
		req_fec = "None";
		fec = "None";
		an = "False";

		अगर (pf->hw.phy.link_info.an_info & I40E_AQ_AN_COMPLETED)
			an = "True";

		अगर (pf->hw.phy.link_info.fec_info &
		    I40E_AQ_CONFIG_FEC_KR_ENA)
			fec = "CL74 FC-FEC/BASE-R";
		अन्यथा अगर (pf->hw.phy.link_info.fec_info &
			 I40E_AQ_CONFIG_FEC_RS_ENA)
			fec = "CL108 RS-FEC";

		/* 'CL108 RS-FEC' should be displayed when RS is requested, or
		 * both RS and FC are requested
		 */
		अगर (vsi->back->hw.phy.link_info.req_fec_info &
		    (I40E_AQ_REQUEST_FEC_KR | I40E_AQ_REQUEST_FEC_RS)) अणु
			अगर (vsi->back->hw.phy.link_info.req_fec_info &
			    I40E_AQ_REQUEST_FEC_RS)
				req_fec = "CL108 RS-FEC";
			अन्यथा
				req_fec = "CL74 FC-FEC/BASE-R";
		पूर्ण
		netdev_info(vsi->netdev,
			    "NIC Link is Up, %sbps Full Duplex, Requested FEC: %s, Negotiated FEC: %s, Autoneg: %s, Flow Control: %s\n",
			    speed, req_fec, fec, an, fc);
	पूर्ण अन्यथा अगर (pf->hw.device_id == I40E_DEV_ID_KX_X722) अणु
		req_fec = "None";
		fec = "None";
		an = "False";

		अगर (pf->hw.phy.link_info.an_info & I40E_AQ_AN_COMPLETED)
			an = "True";

		अगर (pf->hw.phy.link_info.fec_info &
		    I40E_AQ_CONFIG_FEC_KR_ENA)
			fec = "CL74 FC-FEC/BASE-R";

		अगर (pf->hw.phy.link_info.req_fec_info &
		    I40E_AQ_REQUEST_FEC_KR)
			req_fec = "CL74 FC-FEC/BASE-R";

		netdev_info(vsi->netdev,
			    "NIC Link is Up, %sbps Full Duplex, Requested FEC: %s, Negotiated FEC: %s, Autoneg: %s, Flow Control: %s\n",
			    speed, req_fec, fec, an, fc);
	पूर्ण अन्यथा अणु
		netdev_info(vsi->netdev,
			    "NIC Link is Up, %sbps Full Duplex, Flow Control: %s\n",
			    speed, fc);
	पूर्ण

पूर्ण

/**
 * i40e_up_complete - Finish the last steps of bringing up a connection
 * @vsi: the VSI being configured
 **/
अटल पूर्णांक i40e_up_complete(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक err;

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
		i40e_vsi_configure_msix(vsi);
	अन्यथा
		i40e_configure_msi_and_legacy(vsi);

	/* start rings */
	err = i40e_vsi_start_rings(vsi);
	अगर (err)
		वापस err;

	clear_bit(__I40E_VSI_DOWN, vsi->state);
	i40e_napi_enable_all(vsi);
	i40e_vsi_enable_irq(vsi);

	अगर ((pf->hw.phy.link_info.link_info & I40E_AQ_LINK_UP) &&
	    (vsi->netdev)) अणु
		i40e_prपूर्णांक_link_message(vsi, true);
		netअगर_tx_start_all_queues(vsi->netdev);
		netअगर_carrier_on(vsi->netdev);
	पूर्ण

	/* replay Fसूची SB filters */
	अगर (vsi->type == I40E_VSI_Fसूची) अणु
		/* reset fd counters */
		pf->fd_add_err = 0;
		pf->fd_atr_cnt = 0;
		i40e_fdir_filter_restore(vsi);
	पूर्ण

	/* On the next run of the service_task, notअगरy any clients of the new
	 * खोलोed netdev
	 */
	set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
	i40e_service_event_schedule(pf);

	वापस 0;
पूर्ण

/**
 * i40e_vsi_reinit_locked - Reset the VSI
 * @vsi: the VSI being configured
 *
 * Rebuild the ring काष्ठाs after some configuration
 * has changed, e.g. MTU size.
 **/
अटल व्योम i40e_vsi_reinit_locked(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;

	जबतक (test_and_set_bit(__I40E_CONFIG_BUSY, pf->state))
		usleep_range(1000, 2000);
	i40e_करोwn(vsi);

	i40e_up(vsi);
	clear_bit(__I40E_CONFIG_BUSY, pf->state);
पूर्ण

/**
 * i40e_क्रमce_link_state - Force the link status
 * @pf: board निजी काष्ठाure
 * @is_up: whether the link state should be क्रमced up or करोwn
 **/
अटल i40e_status i40e_क्रमce_link_state(काष्ठा i40e_pf *pf, bool is_up)
अणु
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
	काष्ठा i40e_aq_set_phy_config config = अणु0पूर्ण;
	bool non_zero_phy_type = is_up;
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status err;
	u64 mask;
	u8 speed;

	/* Card might've been put in an unstable state by other drivers
	 * and applications, which causes incorrect speed values being
	 * set on startup. In order to clear speed रेजिस्टरs, we call
	 * get_phy_capabilities twice, once to get initial state of
	 * available speeds, and once to get current PHY config.
	 */
	err = i40e_aq_get_phy_capabilities(hw, false, true, &abilities,
					   शून्य);
	अगर (err) अणु
		dev_err(&pf->pdev->dev,
			"failed to get phy cap., ret =  %s last_status =  %s\n",
			i40e_stat_str(hw, err),
			i40e_aq_str(hw, hw->aq.asq_last_status));
		वापस err;
	पूर्ण
	speed = abilities.link_speed;

	/* Get the current phy config */
	err = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					   शून्य);
	अगर (err) अणु
		dev_err(&pf->pdev->dev,
			"failed to get phy cap., ret =  %s last_status =  %s\n",
			i40e_stat_str(hw, err),
			i40e_aq_str(hw, hw->aq.asq_last_status));
		वापस err;
	पूर्ण

	/* If link needs to go up, but was not क्रमced to go करोwn,
	 * and its speed values are OK, no need क्रम a flap
	 * अगर non_zero_phy_type was set, still need to क्रमce up
	 */
	अगर (pf->flags & I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED)
		non_zero_phy_type = true;
	अन्यथा अगर (is_up && abilities.phy_type != 0 && abilities.link_speed != 0)
		वापस I40E_SUCCESS;

	/* To क्रमce link we need to set bits क्रम all supported PHY types,
	 * but there are now more than 32, so we need to split the biपंचांगap
	 * across two fields.
	 */
	mask = I40E_PHY_TYPES_BITMASK;
	config.phy_type =
		non_zero_phy_type ? cpu_to_le32((u32)(mask & 0xffffffff)) : 0;
	config.phy_type_ext =
		non_zero_phy_type ? (u8)((mask >> 32) & 0xff) : 0;
	/* Copy the old settings, except of phy_type */
	config.abilities = abilities.abilities;
	अगर (pf->flags & I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED) अणु
		अगर (is_up)
			config.abilities |= I40E_AQ_PHY_ENABLE_LINK;
		अन्यथा
			config.abilities &= ~(I40E_AQ_PHY_ENABLE_LINK);
	पूर्ण
	अगर (abilities.link_speed != 0)
		config.link_speed = abilities.link_speed;
	अन्यथा
		config.link_speed = speed;
	config.eee_capability = abilities.eee_capability;
	config.eeer = abilities.eeer_val;
	config.low_घातer_ctrl = abilities.d3_lpan;
	config.fec_config = abilities.fec_cfg_curr_mod_ext_info &
			    I40E_AQ_PHY_FEC_CONFIG_MASK;
	err = i40e_aq_set_phy_config(hw, &config, शून्य);

	अगर (err) अणु
		dev_err(&pf->pdev->dev,
			"set phy config ret =  %s last_status =  %s\n",
			i40e_stat_str(&pf->hw, err),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस err;
	पूर्ण

	/* Update the link info */
	err = i40e_update_link_info(hw);
	अगर (err) अणु
		/* Wait a little bit (on 40G cards it someबार takes a really
		 * दीर्घ समय क्रम link to come back from the atomic reset)
		 * and try once more
		 */
		msleep(1000);
		i40e_update_link_info(hw);
	पूर्ण

	i40e_aq_set_link_restart_an(hw, is_up, शून्य);

	वापस I40E_SUCCESS;
पूर्ण

/**
 * i40e_up - Bring the connection back up after being करोwn
 * @vsi: the VSI being configured
 **/
पूर्णांक i40e_up(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक err;

	अगर (vsi->type == I40E_VSI_MAIN &&
	    (vsi->back->flags & I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED ||
	     vsi->back->flags & I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED))
		i40e_क्रमce_link_state(vsi->back, true);

	err = i40e_vsi_configure(vsi);
	अगर (!err)
		err = i40e_up_complete(vsi);

	वापस err;
पूर्ण

/**
 * i40e_करोwn - Shutकरोwn the connection processing
 * @vsi: the VSI being stopped
 **/
व्योम i40e_करोwn(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक i;

	/* It is assumed that the caller of this function
	 * sets the vsi->state __I40E_VSI_DOWN bit.
	 */
	अगर (vsi->netdev) अणु
		netअगर_carrier_off(vsi->netdev);
		netअगर_tx_disable(vsi->netdev);
	पूर्ण
	i40e_vsi_disable_irq(vsi);
	i40e_vsi_stop_rings(vsi);
	अगर (vsi->type == I40E_VSI_MAIN &&
	   (vsi->back->flags & I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED ||
	    vsi->back->flags & I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED))
		i40e_क्रमce_link_state(vsi->back, false);
	i40e_napi_disable_all(vsi);

	क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
		i40e_clean_tx_ring(vsi->tx_rings[i]);
		अगर (i40e_enabled_xdp_vsi(vsi)) अणु
			/* Make sure that in-progress nकरो_xdp_xmit and
			 * nकरो_xsk_wakeup calls are completed.
			 */
			synchronize_rcu();
			i40e_clean_tx_ring(vsi->xdp_rings[i]);
		पूर्ण
		i40e_clean_rx_ring(vsi->rx_rings[i]);
	पूर्ण

पूर्ण

/**
 * i40e_validate_mqprio_qopt- validate queue mapping info
 * @vsi: the VSI being configured
 * @mqprio_qopt: queue parametrs
 **/
अटल पूर्णांक i40e_validate_mqprio_qopt(काष्ठा i40e_vsi *vsi,
				     काष्ठा tc_mqprio_qopt_offload *mqprio_qopt)
अणु
	u64 sum_max_rate = 0;
	u64 max_rate = 0;
	पूर्णांक i;

	अगर (mqprio_qopt->qopt.offset[0] != 0 ||
	    mqprio_qopt->qopt.num_tc < 1 ||
	    mqprio_qopt->qopt.num_tc > I40E_MAX_TRAFFIC_CLASS)
		वापस -EINVAL;
	क्रम (i = 0; ; i++) अणु
		अगर (!mqprio_qopt->qopt.count[i])
			वापस -EINVAL;
		अगर (mqprio_qopt->min_rate[i]) अणु
			dev_err(&vsi->back->pdev->dev,
				"Invalid min tx rate (greater than 0) specified\n");
			वापस -EINVAL;
		पूर्ण
		max_rate = mqprio_qopt->max_rate[i];
		करो_भाग(max_rate, I40E_BW_MBPS_DIVISOR);
		sum_max_rate += max_rate;

		अगर (i >= mqprio_qopt->qopt.num_tc - 1)
			अवरोध;
		अगर (mqprio_qopt->qopt.offset[i + 1] !=
		    (mqprio_qopt->qopt.offset[i] + mqprio_qopt->qopt.count[i]))
			वापस -EINVAL;
	पूर्ण
	अगर (vsi->num_queue_pairs <
	    (mqprio_qopt->qopt.offset[i] + mqprio_qopt->qopt.count[i])) अणु
		वापस -EINVAL;
	पूर्ण
	अगर (sum_max_rate > i40e_get_link_speed(vsi)) अणु
		dev_err(&vsi->back->pdev->dev,
			"Invalid max tx rate specified\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_vsi_set_शेष_tc_config - set शेष values क्रम tc configuration
 * @vsi: the VSI being configured
 **/
अटल व्योम i40e_vsi_set_शेष_tc_config(काष्ठा i40e_vsi *vsi)
अणु
	u16 qcount;
	पूर्णांक i;

	/* Only TC0 is enabled */
	vsi->tc_config.numtc = 1;
	vsi->tc_config.enabled_tc = 1;
	qcount = min_t(पूर्णांक, vsi->alloc_queue_pairs,
		       i40e_pf_get_max_q_per_tc(vsi->back));
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		/* For the TC that is not enabled set the offset to शेष
		 * queue and allocate one queue क्रम the given TC.
		 */
		vsi->tc_config.tc_info[i].qoffset = 0;
		अगर (i == 0)
			vsi->tc_config.tc_info[i].qcount = qcount;
		अन्यथा
			vsi->tc_config.tc_info[i].qcount = 1;
		vsi->tc_config.tc_info[i].netdev_tc = 0;
	पूर्ण
पूर्ण

/**
 * i40e_del_macvlan_filter
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @seid: seid of the channel VSI
 * @macaddr: the mac address to apply as a filter
 * @aq_err: store the admin Q error
 *
 * This function deletes a mac filter on the channel VSI which serves as the
 * macvlan. Returns 0 on success.
 **/
अटल i40e_status i40e_del_macvlan_filter(काष्ठा i40e_hw *hw, u16 seid,
					   स्थिर u8 *macaddr, पूर्णांक *aq_err)
अणु
	काष्ठा i40e_aqc_हटाओ_macvlan_element_data element;
	i40e_status status;

	स_रखो(&element, 0, माप(element));
	ether_addr_copy(element.mac_addr, macaddr);
	element.vlan_tag = 0;
	element.flags = I40E_AQC_MACVLAN_DEL_PERFECT_MATCH;
	status = i40e_aq_हटाओ_macvlan(hw, seid, &element, 1, शून्य);
	*aq_err = hw->aq.asq_last_status;

	वापस status;
पूर्ण

/**
 * i40e_add_macvlan_filter
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @seid: seid of the channel VSI
 * @macaddr: the mac address to apply as a filter
 * @aq_err: store the admin Q error
 *
 * This function adds a mac filter on the channel VSI which serves as the
 * macvlan. Returns 0 on success.
 **/
अटल i40e_status i40e_add_macvlan_filter(काष्ठा i40e_hw *hw, u16 seid,
					   स्थिर u8 *macaddr, पूर्णांक *aq_err)
अणु
	काष्ठा i40e_aqc_add_macvlan_element_data element;
	i40e_status status;
	u16 cmd_flags = 0;

	ether_addr_copy(element.mac_addr, macaddr);
	element.vlan_tag = 0;
	element.queue_number = 0;
	element.match_method = I40E_AQC_MM_ERR_NO_RES;
	cmd_flags |= I40E_AQC_MACVLAN_ADD_PERFECT_MATCH;
	element.flags = cpu_to_le16(cmd_flags);
	status = i40e_aq_add_macvlan(hw, seid, &element, 1, शून्य);
	*aq_err = hw->aq.asq_last_status;

	वापस status;
पूर्ण

/**
 * i40e_reset_ch_rings - Reset the queue contexts in a channel
 * @vsi: the VSI we want to access
 * @ch: the channel we want to access
 */
अटल व्योम i40e_reset_ch_rings(काष्ठा i40e_vsi *vsi, काष्ठा i40e_channel *ch)
अणु
	काष्ठा i40e_ring *tx_ring, *rx_ring;
	u16 pf_q;
	पूर्णांक i;

	क्रम (i = 0; i < ch->num_queue_pairs; i++) अणु
		pf_q = ch->base_queue + i;
		tx_ring = vsi->tx_rings[pf_q];
		tx_ring->ch = शून्य;
		rx_ring = vsi->rx_rings[pf_q];
		rx_ring->ch = शून्य;
	पूर्ण
पूर्ण

/**
 * i40e_मुक्त_macvlan_channels
 * @vsi: the VSI we want to access
 *
 * This function मुक्तs the Qs of the channel VSI from
 * the stack and also deletes the channel VSIs which
 * serve as macvlans.
 */
अटल व्योम i40e_मुक्त_macvlan_channels(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_channel *ch, *ch_पंचांगp;
	पूर्णांक ret;

	अगर (list_empty(&vsi->macvlan_list))
		वापस;

	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->macvlan_list, list) अणु
		काष्ठा i40e_vsi *parent_vsi;

		अगर (i40e_is_channel_macvlan(ch)) अणु
			i40e_reset_ch_rings(vsi, ch);
			clear_bit(ch->fwd->bit_no, vsi->fwd_biपंचांगask);
			netdev_unbind_sb_channel(vsi->netdev, ch->fwd->netdev);
			netdev_set_sb_channel(ch->fwd->netdev, 0);
			kमुक्त(ch->fwd);
			ch->fwd = शून्य;
		पूर्ण

		list_del(&ch->list);
		parent_vsi = ch->parent_vsi;
		अगर (!parent_vsi || !ch->initialized) अणु
			kमुक्त(ch);
			जारी;
		पूर्ण

		/* हटाओ the VSI */
		ret = i40e_aq_delete_element(&vsi->back->hw, ch->seid,
					     शून्य);
		अगर (ret)
			dev_err(&vsi->back->pdev->dev,
				"unable to remove channel (%d) for parent VSI(%d)\n",
				ch->seid, parent_vsi->seid);
		kमुक्त(ch);
	पूर्ण
	vsi->macvlan_cnt = 0;
पूर्ण

/**
 * i40e_fwd_ring_up - bring the macvlan device up
 * @vsi: the VSI we want to access
 * @vdev: macvlan netdevice
 * @fwd: the निजी fwd काष्ठाure
 */
अटल पूर्णांक i40e_fwd_ring_up(काष्ठा i40e_vsi *vsi, काष्ठा net_device *vdev,
			    काष्ठा i40e_fwd_adapter *fwd)
अणु
	पूर्णांक ret = 0, num_tc = 1,  i, aq_err;
	काष्ठा i40e_channel *ch, *ch_पंचांगp;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;

	अगर (list_empty(&vsi->macvlan_list))
		वापस -EINVAL;

	/* Go through the list and find an available channel */
	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->macvlan_list, list) अणु
		अगर (!i40e_is_channel_macvlan(ch)) अणु
			ch->fwd = fwd;
			/* record configuration क्रम macvlan पूर्णांकerface in vdev */
			क्रम (i = 0; i < num_tc; i++)
				netdev_bind_sb_channel_queue(vsi->netdev, vdev,
							     i,
							     ch->num_queue_pairs,
							     ch->base_queue);
			क्रम (i = 0; i < ch->num_queue_pairs; i++) अणु
				काष्ठा i40e_ring *tx_ring, *rx_ring;
				u16 pf_q;

				pf_q = ch->base_queue + i;

				/* Get to TX ring ptr */
				tx_ring = vsi->tx_rings[pf_q];
				tx_ring->ch = ch;

				/* Get the RX ring ptr */
				rx_ring = vsi->rx_rings[pf_q];
				rx_ring->ch = ch;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* Guarantee all rings are updated beक्रमe we update the
	 * MAC address filter.
	 */
	wmb();

	/* Add a mac filter */
	ret = i40e_add_macvlan_filter(hw, ch->seid, vdev->dev_addr, &aq_err);
	अगर (ret) अणु
		/* अगर we cannot add the MAC rule then disable the offload */
		macvlan_release_l2fw_offload(vdev);
		क्रम (i = 0; i < ch->num_queue_pairs; i++) अणु
			काष्ठा i40e_ring *rx_ring;
			u16 pf_q;

			pf_q = ch->base_queue + i;
			rx_ring = vsi->rx_rings[pf_q];
			rx_ring->netdev = शून्य;
		पूर्ण
		dev_info(&pf->pdev->dev,
			 "Error adding mac filter on macvlan err %s, aq_err %s\n",
			  i40e_stat_str(hw, ret),
			  i40e_aq_str(hw, aq_err));
		netdev_err(vdev, "L2fwd offload disabled to L2 filter error\n");
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_setup_macvlans - create the channels which will be macvlans
 * @vsi: the VSI we want to access
 * @macvlan_cnt: no. of macvlans to be setup
 * @qcnt: no. of Qs per macvlan
 * @vdev: macvlan netdevice
 */
अटल पूर्णांक i40e_setup_macvlans(काष्ठा i40e_vsi *vsi, u16 macvlan_cnt, u16 qcnt,
			       काष्ठा net_device *vdev)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vsi_context ctxt;
	u16 sections, qmap, num_qps;
	काष्ठा i40e_channel *ch;
	पूर्णांक i, घात, ret = 0;
	u8 offset = 0;

	अगर (vsi->type != I40E_VSI_MAIN || !macvlan_cnt)
		वापस -EINVAL;

	num_qps = vsi->num_queue_pairs - (macvlan_cnt * qcnt);

	/* find the next higher घातer-of-2 of num queue pairs */
	घात = fls(roundup_घात_of_two(num_qps) - 1);

	qmap = (offset << I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT) |
		(घात << I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT);

	/* Setup context bits क्रम the मुख्य VSI */
	sections = I40E_AQ_VSI_PROP_QUEUE_MAP_VALID;
	sections |= I40E_AQ_VSI_PROP_SCHED_VALID;
	स_रखो(&ctxt, 0, माप(ctxt));
	ctxt.seid = vsi->seid;
	ctxt.pf_num = vsi->back->hw.pf_id;
	ctxt.vf_num = 0;
	ctxt.uplink_seid = vsi->uplink_seid;
	ctxt.info = vsi->info;
	ctxt.info.tc_mapping[0] = cpu_to_le16(qmap);
	ctxt.info.mapping_flags |= cpu_to_le16(I40E_AQ_VSI_QUE_MAP_CONTIG);
	ctxt.info.queue_mapping[0] = cpu_to_le16(vsi->base_queue);
	ctxt.info.valid_sections |= cpu_to_le16(sections);

	/* Reconfigure RSS क्रम मुख्य VSI with new max queue count */
	vsi->rss_size = max_t(u16, num_qps, qcnt);
	ret = i40e_vsi_config_rss(vsi);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Failed to reconfig RSS for num_queues (%u)\n",
			 vsi->rss_size);
		वापस ret;
	पूर्ण
	vsi->reconfig_rss = true;
	dev_dbg(&vsi->back->pdev->dev,
		"Reconfigured RSS with num_queues (%u)\n", vsi->rss_size);
	vsi->next_base_queue = num_qps;
	vsi->cnt_q_avail = vsi->num_queue_pairs - num_qps;

	/* Update the VSI after updating the VSI queue-mapping
	 * inक्रमmation
	 */
	ret = i40e_aq_update_vsi_params(hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Update vsi tc config failed, err %s aq_err %s\n",
			 i40e_stat_str(hw, ret),
			 i40e_aq_str(hw, hw->aq.asq_last_status));
		वापस ret;
	पूर्ण
	/* update the local VSI info with updated queue map */
	i40e_vsi_update_queue_map(vsi, &ctxt);
	vsi->info.valid_sections = 0;

	/* Create channels क्रम macvlans */
	INIT_LIST_HEAD(&vsi->macvlan_list);
	क्रम (i = 0; i < macvlan_cnt; i++) अणु
		ch = kzalloc(माप(*ch), GFP_KERNEL);
		अगर (!ch) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण
		INIT_LIST_HEAD(&ch->list);
		ch->num_queue_pairs = qcnt;
		अगर (!i40e_setup_channel(pf, vsi, ch)) अणु
			ret = -EINVAL;
			kमुक्त(ch);
			जाओ err_मुक्त;
		पूर्ण
		ch->parent_vsi = vsi;
		vsi->cnt_q_avail -= ch->num_queue_pairs;
		vsi->macvlan_cnt++;
		list_add_tail(&ch->list, &vsi->macvlan_list);
	पूर्ण

	वापस ret;

err_मुक्त:
	dev_info(&pf->pdev->dev, "Failed to setup macvlans\n");
	i40e_मुक्त_macvlan_channels(vsi);

	वापस ret;
पूर्ण

/**
 * i40e_fwd_add - configure macvlans
 * @netdev: net device to configure
 * @vdev: macvlan netdevice
 **/
अटल व्योम *i40e_fwd_add(काष्ठा net_device *netdev, काष्ठा net_device *vdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	u16 q_per_macvlan = 0, macvlan_cnt = 0, vectors;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_fwd_adapter *fwd;
	पूर्णांक avail_macvlan, ret;

	अगर ((pf->flags & I40E_FLAG_DCB_ENABLED)) अणु
		netdev_info(netdev, "Macvlans are not supported when DCB is enabled\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर ((pf->flags & I40E_FLAG_TC_MQPRIO)) अणु
		netdev_info(netdev, "Macvlans are not supported when HW TC offload is on\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (pf->num_lan_msix < I40E_MIN_MACVLAN_VECTORS) अणु
		netdev_info(netdev, "Not enough vectors available to support macvlans\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* The macvlan device has to be a single Q device so that the
	 * tc_to_txq field can be reused to pick the tx queue.
	 */
	अगर (netअगर_is_multiqueue(vdev))
		वापस ERR_PTR(-दुस्फल);

	अगर (!vsi->macvlan_cnt) अणु
		/* reserve bit 0 क्रम the pf device */
		set_bit(0, vsi->fwd_biपंचांगask);

		/* Try to reserve as many queues as possible क्रम macvlans. First
		 * reserve 3/4th of max vectors, then half, then quarter and
		 * calculate Qs per macvlan as you go
		 */
		vectors = pf->num_lan_msix;
		अगर (vectors <= I40E_MAX_MACVLANS && vectors > 64) अणु
			/* allocate 4 Qs per macvlan and 32 Qs to the PF*/
			q_per_macvlan = 4;
			macvlan_cnt = (vectors - 32) / 4;
		पूर्ण अन्यथा अगर (vectors <= 64 && vectors > 32) अणु
			/* allocate 2 Qs per macvlan and 16 Qs to the PF*/
			q_per_macvlan = 2;
			macvlan_cnt = (vectors - 16) / 2;
		पूर्ण अन्यथा अगर (vectors <= 32 && vectors > 16) अणु
			/* allocate 1 Q per macvlan and 16 Qs to the PF*/
			q_per_macvlan = 1;
			macvlan_cnt = vectors - 16;
		पूर्ण अन्यथा अगर (vectors <= 16 && vectors > 8) अणु
			/* allocate 1 Q per macvlan and 8 Qs to the PF */
			q_per_macvlan = 1;
			macvlan_cnt = vectors - 8;
		पूर्ण अन्यथा अणु
			/* allocate 1 Q per macvlan and 1 Q to the PF */
			q_per_macvlan = 1;
			macvlan_cnt = vectors - 1;
		पूर्ण

		अगर (macvlan_cnt == 0)
			वापस ERR_PTR(-EBUSY);

		/* Quiesce VSI queues */
		i40e_quiesce_vsi(vsi);

		/* sets up the macvlans but करोes not "enable" them */
		ret = i40e_setup_macvlans(vsi, macvlan_cnt, q_per_macvlan,
					  vdev);
		अगर (ret)
			वापस ERR_PTR(ret);

		/* Unquiesce VSI */
		i40e_unquiesce_vsi(vsi);
	पूर्ण
	avail_macvlan = find_first_zero_bit(vsi->fwd_biपंचांगask,
					    vsi->macvlan_cnt);
	अगर (avail_macvlan >= I40E_MAX_MACVLANS)
		वापस ERR_PTR(-EBUSY);

	/* create the fwd काष्ठा */
	fwd = kzalloc(माप(*fwd), GFP_KERNEL);
	अगर (!fwd)
		वापस ERR_PTR(-ENOMEM);

	set_bit(avail_macvlan, vsi->fwd_biपंचांगask);
	fwd->bit_no = avail_macvlan;
	netdev_set_sb_channel(vdev, avail_macvlan);
	fwd->netdev = vdev;

	अगर (!netअगर_running(netdev))
		वापस fwd;

	/* Set fwd ring up */
	ret = i40e_fwd_ring_up(vsi, vdev, fwd);
	अगर (ret) अणु
		/* unbind the queues and drop the subordinate channel config */
		netdev_unbind_sb_channel(netdev, vdev);
		netdev_set_sb_channel(vdev, 0);

		kमुक्त(fwd);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस fwd;
पूर्ण

/**
 * i40e_del_all_macvlans - Delete all the mac filters on the channels
 * @vsi: the VSI we want to access
 */
अटल व्योम i40e_del_all_macvlans(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_channel *ch, *ch_पंचांगp;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक aq_err, ret = 0;

	अगर (list_empty(&vsi->macvlan_list))
		वापस;

	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->macvlan_list, list) अणु
		अगर (i40e_is_channel_macvlan(ch)) अणु
			ret = i40e_del_macvlan_filter(hw, ch->seid,
						      i40e_channel_mac(ch),
						      &aq_err);
			अगर (!ret) अणु
				/* Reset queue contexts */
				i40e_reset_ch_rings(vsi, ch);
				clear_bit(ch->fwd->bit_no, vsi->fwd_biपंचांगask);
				netdev_unbind_sb_channel(vsi->netdev,
							 ch->fwd->netdev);
				netdev_set_sb_channel(ch->fwd->netdev, 0);
				kमुक्त(ch->fwd);
				ch->fwd = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_fwd_del - delete macvlan पूर्णांकerfaces
 * @netdev: net device to configure
 * @vdev: macvlan netdevice
 */
अटल व्योम i40e_fwd_del(काष्ठा net_device *netdev, व्योम *vdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_fwd_adapter *fwd = vdev;
	काष्ठा i40e_channel *ch, *ch_पंचांगp;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक aq_err, ret = 0;

	/* Find the channel associated with the macvlan and del mac filter */
	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->macvlan_list, list) अणु
		अगर (i40e_is_channel_macvlan(ch) &&
		    ether_addr_equal(i40e_channel_mac(ch),
				     fwd->netdev->dev_addr)) अणु
			ret = i40e_del_macvlan_filter(hw, ch->seid,
						      i40e_channel_mac(ch),
						      &aq_err);
			अगर (!ret) अणु
				/* Reset queue contexts */
				i40e_reset_ch_rings(vsi, ch);
				clear_bit(ch->fwd->bit_no, vsi->fwd_biपंचांगask);
				netdev_unbind_sb_channel(netdev, fwd->netdev);
				netdev_set_sb_channel(fwd->netdev, 0);
				kमुक्त(ch->fwd);
				ch->fwd = शून्य;
			पूर्ण अन्यथा अणु
				dev_info(&pf->pdev->dev,
					 "Error deleting mac filter on macvlan err %s, aq_err %s\n",
					  i40e_stat_str(hw, ret),
					  i40e_aq_str(hw, aq_err));
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_setup_tc - configure multiple traffic classes
 * @netdev: net device to configure
 * @type_data: tc offload data
 **/
अटल पूर्णांक i40e_setup_tc(काष्ठा net_device *netdev, व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt_offload *mqprio_qopt = type_data;
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	u8 enabled_tc = 0, num_tc, hw;
	bool need_reset = false;
	पूर्णांक old_queue_pairs;
	पूर्णांक ret = -EINVAL;
	u16 mode;
	पूर्णांक i;

	old_queue_pairs = vsi->num_queue_pairs;
	num_tc = mqprio_qopt->qopt.num_tc;
	hw = mqprio_qopt->qopt.hw;
	mode = mqprio_qopt->mode;
	अगर (!hw) अणु
		pf->flags &= ~I40E_FLAG_TC_MQPRIO;
		स_नकल(&vsi->mqprio_qopt, mqprio_qopt, माप(*mqprio_qopt));
		जाओ config_tc;
	पूर्ण

	/* Check अगर MFP enabled */
	अगर (pf->flags & I40E_FLAG_MFP_ENABLED) अणु
		netdev_info(netdev,
			    "Configuring TC not supported in MFP mode\n");
		वापस ret;
	पूर्ण
	चयन (mode) अणु
	हाल TC_MQPRIO_MODE_DCB:
		pf->flags &= ~I40E_FLAG_TC_MQPRIO;

		/* Check अगर DCB enabled to जारी */
		अगर (!(pf->flags & I40E_FLAG_DCB_ENABLED)) अणु
			netdev_info(netdev,
				    "DCB is not enabled for adapter\n");
			वापस ret;
		पूर्ण

		/* Check whether tc count is within enabled limit */
		अगर (num_tc > i40e_pf_get_num_tc(pf)) अणु
			netdev_info(netdev,
				    "TC count greater than enabled on link for adapter\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल TC_MQPRIO_MODE_CHANNEL:
		अगर (pf->flags & I40E_FLAG_DCB_ENABLED) अणु
			netdev_info(netdev,
				    "Full offload of TC Mqprio options is not supported when DCB is enabled\n");
			वापस ret;
		पूर्ण
		अगर (!(pf->flags & I40E_FLAG_MSIX_ENABLED))
			वापस ret;
		ret = i40e_validate_mqprio_qopt(vsi, mqprio_qopt);
		अगर (ret)
			वापस ret;
		स_नकल(&vsi->mqprio_qopt, mqprio_qopt,
		       माप(*mqprio_qopt));
		pf->flags |= I40E_FLAG_TC_MQPRIO;
		pf->flags &= ~I40E_FLAG_DCB_ENABLED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

config_tc:
	/* Generate TC map क्रम number of tc requested */
	क्रम (i = 0; i < num_tc; i++)
		enabled_tc |= BIT(i);

	/* Requesting same TC configuration as alपढ़ोy enabled */
	अगर (enabled_tc == vsi->tc_config.enabled_tc &&
	    mode != TC_MQPRIO_MODE_CHANNEL)
		वापस 0;

	/* Quiesce VSI queues */
	i40e_quiesce_vsi(vsi);

	अगर (!hw && !(pf->flags & I40E_FLAG_TC_MQPRIO))
		i40e_हटाओ_queue_channels(vsi);

	/* Configure VSI क्रम enabled TCs */
	ret = i40e_vsi_config_tc(vsi, enabled_tc);
	अगर (ret) अणु
		netdev_info(netdev, "Failed configuring TC for VSI seid=%d\n",
			    vsi->seid);
		need_reset = true;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		dev_info(&vsi->back->pdev->dev,
			 "Setup channel (id:%u) utilizing num_queues %d\n",
			 vsi->seid, vsi->tc_config.tc_info[0].qcount);
	पूर्ण

	अगर (pf->flags & I40E_FLAG_TC_MQPRIO) अणु
		अगर (vsi->mqprio_qopt.max_rate[0]) अणु
			u64 max_tx_rate = vsi->mqprio_qopt.max_rate[0];

			करो_भाग(max_tx_rate, I40E_BW_MBPS_DIVISOR);
			ret = i40e_set_bw_limit(vsi, vsi->seid, max_tx_rate);
			अगर (!ret) अणु
				u64 credits = max_tx_rate;

				करो_भाग(credits, I40E_BW_CREDIT_DIVISOR);
				dev_dbg(&vsi->back->pdev->dev,
					"Set tx rate of %llu Mbps (count of 50Mbps %llu) for vsi->seid %u\n",
					max_tx_rate,
					credits,
					vsi->seid);
			पूर्ण अन्यथा अणु
				need_reset = true;
				जाओ निकास;
			पूर्ण
		पूर्ण
		ret = i40e_configure_queue_channels(vsi);
		अगर (ret) अणु
			vsi->num_queue_pairs = old_queue_pairs;
			netdev_info(netdev,
				    "Failed configuring queue channels\n");
			need_reset = true;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	/* Reset the configuration data to शेषs, only TC0 is enabled */
	अगर (need_reset) अणु
		i40e_vsi_set_शेष_tc_config(vsi);
		need_reset = false;
	पूर्ण

	/* Unquiesce VSI */
	i40e_unquiesce_vsi(vsi);
	वापस ret;
पूर्ण

/**
 * i40e_set_cld_element - sets cloud filter element data
 * @filter: cloud filter rule
 * @cld: ptr to cloud filter element data
 *
 * This is helper function to copy data पूर्णांकo cloud filter element
 **/
अटल अंतरभूत व्योम
i40e_set_cld_element(काष्ठा i40e_cloud_filter *filter,
		     काष्ठा i40e_aqc_cloud_filters_element_data *cld)
अणु
	u32 ipa;
	पूर्णांक i;

	स_रखो(cld, 0, माप(*cld));
	ether_addr_copy(cld->outer_mac, filter->dst_mac);
	ether_addr_copy(cld->inner_mac, filter->src_mac);

	अगर (filter->n_proto != ETH_P_IP && filter->n_proto != ETH_P_IPV6)
		वापस;

	अगर (filter->n_proto == ETH_P_IPV6) अणु
#घोषणा IPV6_MAX_INDEX	(ARRAY_SIZE(filter->dst_ipv6) - 1)
		क्रम (i = 0; i < ARRAY_SIZE(filter->dst_ipv6); i++) अणु
			ipa = be32_to_cpu(filter->dst_ipv6[IPV6_MAX_INDEX - i]);

			*(__le32 *)&cld->ipaddr.raw_v6.data[i * 2] = cpu_to_le32(ipa);
		पूर्ण
	पूर्ण अन्यथा अणु
		ipa = be32_to_cpu(filter->dst_ipv4);

		स_नकल(&cld->ipaddr.v4.data, &ipa, माप(ipa));
	पूर्ण

	cld->inner_vlan = cpu_to_le16(ntohs(filter->vlan_id));

	/* tenant_id is not supported by FW now, once the support is enabled
	 * fill the cld->tenant_id with cpu_to_le32(filter->tenant_id)
	 */
	अगर (filter->tenant_id)
		वापस;
पूर्ण

/**
 * i40e_add_del_cloud_filter - Add/del cloud filter
 * @vsi: poपूर्णांकer to VSI
 * @filter: cloud filter rule
 * @add: अगर true, add, अगर false, delete
 *
 * Add or delete a cloud filter क्रम a specअगरic flow spec.
 * Returns 0 अगर the filter were successfully added.
 **/
पूर्णांक i40e_add_del_cloud_filter(काष्ठा i40e_vsi *vsi,
			      काष्ठा i40e_cloud_filter *filter, bool add)
अणु
	काष्ठा i40e_aqc_cloud_filters_element_data cld_filter;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret;
	अटल स्थिर u16 flag_table[128] = अणु
		[I40E_CLOUD_FILTER_FLAGS_OMAC]  =
			I40E_AQC_ADD_CLOUD_FILTER_OMAC,
		[I40E_CLOUD_FILTER_FLAGS_IMAC]  =
			I40E_AQC_ADD_CLOUD_FILTER_IMAC,
		[I40E_CLOUD_FILTER_FLAGS_IMAC_IVLAN]  =
			I40E_AQC_ADD_CLOUD_FILTER_IMAC_IVLAN,
		[I40E_CLOUD_FILTER_FLAGS_IMAC_TEN_ID] =
			I40E_AQC_ADD_CLOUD_FILTER_IMAC_TEN_ID,
		[I40E_CLOUD_FILTER_FLAGS_OMAC_TEN_ID_IMAC] =
			I40E_AQC_ADD_CLOUD_FILTER_OMAC_TEN_ID_IMAC,
		[I40E_CLOUD_FILTER_FLAGS_IMAC_IVLAN_TEN_ID] =
			I40E_AQC_ADD_CLOUD_FILTER_IMAC_IVLAN_TEN_ID,
		[I40E_CLOUD_FILTER_FLAGS_IIP] =
			I40E_AQC_ADD_CLOUD_FILTER_IIP,
	पूर्ण;

	अगर (filter->flags >= ARRAY_SIZE(flag_table))
		वापस I40E_ERR_CONFIG;

	स_रखो(&cld_filter, 0, माप(cld_filter));

	/* copy element needed to add cloud filter from filter */
	i40e_set_cld_element(filter, &cld_filter);

	अगर (filter->tunnel_type != I40E_CLOUD_TNL_TYPE_NONE)
		cld_filter.flags = cpu_to_le16(filter->tunnel_type <<
					     I40E_AQC_ADD_CLOUD_TNL_TYPE_SHIFT);

	अगर (filter->n_proto == ETH_P_IPV6)
		cld_filter.flags |= cpu_to_le16(flag_table[filter->flags] |
						I40E_AQC_ADD_CLOUD_FLAGS_IPV6);
	अन्यथा
		cld_filter.flags |= cpu_to_le16(flag_table[filter->flags] |
						I40E_AQC_ADD_CLOUD_FLAGS_IPV4);

	अगर (add)
		ret = i40e_aq_add_cloud_filters(&pf->hw, filter->seid,
						&cld_filter, 1);
	अन्यथा
		ret = i40e_aq_rem_cloud_filters(&pf->hw, filter->seid,
						&cld_filter, 1);
	अगर (ret)
		dev_dbg(&pf->pdev->dev,
			"Failed to %s cloud filter using l4 port %u, err %d aq_err %d\n",
			add ? "add" : "delete", filter->dst_port, ret,
			pf->hw.aq.asq_last_status);
	अन्यथा
		dev_info(&pf->pdev->dev,
			 "%s cloud filter for VSI: %d\n",
			 add ? "Added" : "Deleted", filter->seid);
	वापस ret;
पूर्ण

/**
 * i40e_add_del_cloud_filter_big_buf - Add/del cloud filter using big_buf
 * @vsi: poपूर्णांकer to VSI
 * @filter: cloud filter rule
 * @add: अगर true, add, अगर false, delete
 *
 * Add or delete a cloud filter क्रम a specअगरic flow spec using big buffer.
 * Returns 0 अगर the filter were successfully added.
 **/
पूर्णांक i40e_add_del_cloud_filter_big_buf(काष्ठा i40e_vsi *vsi,
				      काष्ठा i40e_cloud_filter *filter,
				      bool add)
अणु
	काष्ठा i40e_aqc_cloud_filters_element_bb cld_filter;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret;

	/* Both (src/dst) valid mac_addr are not supported */
	अगर ((is_valid_ether_addr(filter->dst_mac) &&
	     is_valid_ether_addr(filter->src_mac)) ||
	    (is_multicast_ether_addr(filter->dst_mac) &&
	     is_multicast_ether_addr(filter->src_mac)))
		वापस -EOPNOTSUPP;

	/* Big buffer cloud filter needs 'L4 port' to be non-zero. Also, UDP
	 * ports are not supported via big buffer now.
	 */
	अगर (!filter->dst_port || filter->ip_proto == IPPROTO_UDP)
		वापस -EOPNOTSUPP;

	/* adding filter using src_port/src_ip is not supported at this stage */
	अगर (filter->src_port ||
	    (filter->src_ipv4 && filter->n_proto != ETH_P_IPV6) ||
	    !ipv6_addr_any(&filter->ip.v6.src_ip6))
		वापस -EOPNOTSUPP;

	स_रखो(&cld_filter, 0, माप(cld_filter));

	/* copy element needed to add cloud filter from filter */
	i40e_set_cld_element(filter, &cld_filter.element);

	अगर (is_valid_ether_addr(filter->dst_mac) ||
	    is_valid_ether_addr(filter->src_mac) ||
	    is_multicast_ether_addr(filter->dst_mac) ||
	    is_multicast_ether_addr(filter->src_mac)) अणु
		/* MAC + IP : unsupported mode */
		अगर (filter->dst_ipv4)
			वापस -EOPNOTSUPP;

		/* since we validated that L4 port must be valid beक्रमe
		 * we get here, start with respective "flags" value
		 * and update अगर vlan is present or not
		 */
		cld_filter.element.flags =
			cpu_to_le16(I40E_AQC_ADD_CLOUD_FILTER_MAC_PORT);

		अगर (filter->vlan_id) अणु
			cld_filter.element.flags =
			cpu_to_le16(I40E_AQC_ADD_CLOUD_FILTER_MAC_VLAN_PORT);
		पूर्ण

	पूर्ण अन्यथा अगर ((filter->dst_ipv4 && filter->n_proto != ETH_P_IPV6) ||
		   !ipv6_addr_any(&filter->ip.v6.dst_ip6)) अणु
		cld_filter.element.flags =
				cpu_to_le16(I40E_AQC_ADD_CLOUD_FILTER_IP_PORT);
		अगर (filter->n_proto == ETH_P_IPV6)
			cld_filter.element.flags |=
				cpu_to_le16(I40E_AQC_ADD_CLOUD_FLAGS_IPV6);
		अन्यथा
			cld_filter.element.flags |=
				cpu_to_le16(I40E_AQC_ADD_CLOUD_FLAGS_IPV4);
	पूर्ण अन्यथा अणु
		dev_err(&pf->pdev->dev,
			"either mac or ip has to be valid for cloud filter\n");
		वापस -EINVAL;
	पूर्ण

	/* Now copy L4 port in Byte 6..7 in general fields */
	cld_filter.general_fields[I40E_AQC_ADD_CLOUD_FV_FLU_0X16_WORD0] =
						be16_to_cpu(filter->dst_port);

	अगर (add) अणु
		/* Validate current device चयन mode, change अगर necessary */
		ret = i40e_validate_and_set_चयन_mode(vsi);
		अगर (ret) अणु
			dev_err(&pf->pdev->dev,
				"failed to set switch mode, ret %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = i40e_aq_add_cloud_filters_bb(&pf->hw, filter->seid,
						   &cld_filter, 1);
	पूर्ण अन्यथा अणु
		ret = i40e_aq_rem_cloud_filters_bb(&pf->hw, filter->seid,
						   &cld_filter, 1);
	पूर्ण

	अगर (ret)
		dev_dbg(&pf->pdev->dev,
			"Failed to %s cloud filter(big buffer) err %d aq_err %d\n",
			add ? "add" : "delete", ret, pf->hw.aq.asq_last_status);
	अन्यथा
		dev_info(&pf->pdev->dev,
			 "%s cloud filter for VSI: %d, L4 port: %d\n",
			 add ? "add" : "delete", filter->seid,
			 ntohs(filter->dst_port));
	वापस ret;
पूर्ण

/**
 * i40e_parse_cls_flower - Parse tc flower filters provided by kernel
 * @vsi: Poपूर्णांकer to VSI
 * @f: Poपूर्णांकer to काष्ठा flow_cls_offload
 * @filter: Poपूर्णांकer to cloud filter काष्ठाure
 *
 **/
अटल पूर्णांक i40e_parse_cls_flower(काष्ठा i40e_vsi *vsi,
				 काष्ठा flow_cls_offload *f,
				 काष्ठा i40e_cloud_filter *filter)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	u16 n_proto_mask = 0, n_proto_key = 0, addr_type = 0;
	काष्ठा i40e_pf *pf = vsi->back;
	u8 field_flags = 0;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID))) अणु
		dev_err(&pf->pdev->dev, "Unsupported key used: 0x%x\n",
			dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		अगर (match.mask->keyid != 0)
			field_flags |= I40E_CLOUD_FIELD_TEN_ID;

		filter->tenant_id = be32_to_cpu(match.key->keyid);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		n_proto_key = ntohs(match.key->n_proto);
		n_proto_mask = ntohs(match.mask->n_proto);

		अगर (n_proto_key == ETH_P_ALL) अणु
			n_proto_key = 0;
			n_proto_mask = 0;
		पूर्ण
		filter->n_proto = n_proto_key & n_proto_mask;
		filter->ip_proto = match.key->ip_proto;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);

		/* use is_broadcast and is_zero to check क्रम all 0xf or 0 */
		अगर (!is_zero_ether_addr(match.mask->dst)) अणु
			अगर (is_broadcast_ether_addr(match.mask->dst)) अणु
				field_flags |= I40E_CLOUD_FIELD_OMAC;
			पूर्ण अन्यथा अणु
				dev_err(&pf->pdev->dev, "Bad ether dest mask %pM\n",
					match.mask->dst);
				वापस I40E_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (!is_zero_ether_addr(match.mask->src)) अणु
			अगर (is_broadcast_ether_addr(match.mask->src)) अणु
				field_flags |= I40E_CLOUD_FIELD_IMAC;
			पूर्ण अन्यथा अणु
				dev_err(&pf->pdev->dev, "Bad ether src mask %pM\n",
					match.mask->src);
				वापस I40E_ERR_CONFIG;
			पूर्ण
		पूर्ण
		ether_addr_copy(filter->dst_mac, match.key->dst);
		ether_addr_copy(filter->src_mac, match.key->src);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		अगर (match.mask->vlan_id) अणु
			अगर (match.mask->vlan_id == VLAN_VID_MASK) अणु
				field_flags |= I40E_CLOUD_FIELD_IVLAN;

			पूर्ण अन्यथा अणु
				dev_err(&pf->pdev->dev, "Bad vlan mask 0x%04x\n",
					match.mask->vlan_id);
				वापस I40E_ERR_CONFIG;
			पूर्ण
		पूर्ण

		filter->vlan_id = cpu_to_be16(match.key->vlan_id);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		अगर (match.mask->dst) अणु
			अगर (match.mask->dst == cpu_to_be32(0xffffffff)) अणु
				field_flags |= I40E_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&pf->pdev->dev, "Bad ip dst mask %pI4b\n",
					&match.mask->dst);
				वापस I40E_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (match.mask->src) अणु
			अगर (match.mask->src == cpu_to_be32(0xffffffff)) अणु
				field_flags |= I40E_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&pf->pdev->dev, "Bad ip src mask %pI4b\n",
					&match.mask->src);
				वापस I40E_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (field_flags & I40E_CLOUD_FIELD_TEN_ID) अणु
			dev_err(&pf->pdev->dev, "Tenant id not allowed for ip filter\n");
			वापस I40E_ERR_CONFIG;
		पूर्ण
		filter->dst_ipv4 = match.key->dst;
		filter->src_ipv4 = match.key->src;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);

		/* src and dest IPV6 address should not be LOOPBACK
		 * (0:0:0:0:0:0:0:1), which can be represented as ::1
		 */
		अगर (ipv6_addr_loopback(&match.key->dst) ||
		    ipv6_addr_loopback(&match.key->src)) अणु
			dev_err(&pf->pdev->dev,
				"Bad ipv6, addr is LOOPBACK\n");
			वापस I40E_ERR_CONFIG;
		पूर्ण
		अगर (!ipv6_addr_any(&match.mask->dst) ||
		    !ipv6_addr_any(&match.mask->src))
			field_flags |= I40E_CLOUD_FIELD_IIP;

		स_नकल(&filter->src_ipv6, &match.key->src.s6_addr32,
		       माप(filter->src_ipv6));
		स_नकल(&filter->dst_ipv6, &match.key->dst.s6_addr32,
		       माप(filter->dst_ipv6));
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		अगर (match.mask->src) अणु
			अगर (match.mask->src == cpu_to_be16(0xffff)) अणु
				field_flags |= I40E_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&pf->pdev->dev, "Bad src port mask 0x%04x\n",
					be16_to_cpu(match.mask->src));
				वापस I40E_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (match.mask->dst) अणु
			अगर (match.mask->dst == cpu_to_be16(0xffff)) अणु
				field_flags |= I40E_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&pf->pdev->dev, "Bad dst port mask 0x%04x\n",
					be16_to_cpu(match.mask->dst));
				वापस I40E_ERR_CONFIG;
			पूर्ण
		पूर्ण

		filter->dst_port = match.key->dst;
		filter->src_port = match.key->src;

		चयन (filter->ip_proto) अणु
		हाल IPPROTO_TCP:
		हाल IPPROTO_UDP:
			अवरोध;
		शेष:
			dev_err(&pf->pdev->dev,
				"Only UDP and TCP transport are supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	filter->flags = field_flags;
	वापस 0;
पूर्ण

/**
 * i40e_handle_tclass: Forward to a traffic class on the device
 * @vsi: Poपूर्णांकer to VSI
 * @tc: traffic class index on the device
 * @filter: Poपूर्णांकer to cloud filter काष्ठाure
 *
 **/
अटल पूर्णांक i40e_handle_tclass(काष्ठा i40e_vsi *vsi, u32 tc,
			      काष्ठा i40e_cloud_filter *filter)
अणु
	काष्ठा i40e_channel *ch, *ch_पंचांगp;

	/* direct to a traffic class on the same device */
	अगर (tc == 0) अणु
		filter->seid = vsi->seid;
		वापस 0;
	पूर्ण अन्यथा अगर (vsi->tc_config.enabled_tc & BIT(tc)) अणु
		अगर (!filter->dst_port) अणु
			dev_err(&vsi->back->pdev->dev,
				"Specify destination port to direct to traffic class that is not default\n");
			वापस -EINVAL;
		पूर्ण
		अगर (list_empty(&vsi->ch_list))
			वापस -EINVAL;
		list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->ch_list,
					 list) अणु
			अगर (ch->seid == vsi->tc_seid_map[tc])
				filter->seid = ch->seid;
		पूर्ण
		वापस 0;
	पूर्ण
	dev_err(&vsi->back->pdev->dev, "TC is not enabled\n");
	वापस -EINVAL;
पूर्ण

/**
 * i40e_configure_clsflower - Configure tc flower filters
 * @vsi: Poपूर्णांकer to VSI
 * @cls_flower: Poपूर्णांकer to काष्ठा flow_cls_offload
 *
 **/
अटल पूर्णांक i40e_configure_clsflower(काष्ठा i40e_vsi *vsi,
				    काष्ठा flow_cls_offload *cls_flower)
अणु
	पूर्णांक tc = tc_classid_to_hwtc(vsi->netdev, cls_flower->classid);
	काष्ठा i40e_cloud_filter *filter = शून्य;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक err = 0;

	अगर (tc < 0) अणु
		dev_err(&vsi->back->pdev->dev, "Invalid traffic class\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
	    test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
		वापस -EBUSY;

	अगर (pf->fdir_pf_active_filters ||
	    (!hlist_empty(&pf->fdir_filter_list))) अणु
		dev_err(&vsi->back->pdev->dev,
			"Flow Director Sideband filters exists, turn ntuple off to configure cloud filters\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vsi->back->flags & I40E_FLAG_FD_SB_ENABLED) अणु
		dev_err(&vsi->back->pdev->dev,
			"Disable Flow Director Sideband, configuring Cloud filters via tc-flower\n");
		vsi->back->flags &= ~I40E_FLAG_FD_SB_ENABLED;
		vsi->back->flags |= I40E_FLAG_FD_SB_TO_CLOUD_FILTER;
	पूर्ण

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	filter->cookie = cls_flower->cookie;

	err = i40e_parse_cls_flower(vsi, cls_flower, filter);
	अगर (err < 0)
		जाओ err;

	err = i40e_handle_tclass(vsi, tc, filter);
	अगर (err < 0)
		जाओ err;

	/* Add cloud filter */
	अगर (filter->dst_port)
		err = i40e_add_del_cloud_filter_big_buf(vsi, filter, true);
	अन्यथा
		err = i40e_add_del_cloud_filter(vsi, filter, true);

	अगर (err) अणु
		dev_err(&pf->pdev->dev,
			"Failed to add cloud filter, err %s\n",
			i40e_stat_str(&pf->hw, err));
		जाओ err;
	पूर्ण

	/* add filter to the ordered list */
	INIT_HLIST_NODE(&filter->cloud_node);

	hlist_add_head(&filter->cloud_node, &pf->cloud_filter_list);

	pf->num_cloud_filters++;

	वापस err;
err:
	kमुक्त(filter);
	वापस err;
पूर्ण

/**
 * i40e_find_cloud_filter - Find the could filter in the list
 * @vsi: Poपूर्णांकer to VSI
 * @cookie: filter specअगरic cookie
 *
 **/
अटल काष्ठा i40e_cloud_filter *i40e_find_cloud_filter(काष्ठा i40e_vsi *vsi,
							अचिन्हित दीर्घ *cookie)
अणु
	काष्ठा i40e_cloud_filter *filter = शून्य;
	काष्ठा hlist_node *node2;

	hlist_क्रम_each_entry_safe(filter, node2,
				  &vsi->back->cloud_filter_list, cloud_node)
		अगर (!स_भेद(cookie, &filter->cookie, माप(filter->cookie)))
			वापस filter;
	वापस शून्य;
पूर्ण

/**
 * i40e_delete_clsflower - Remove tc flower filters
 * @vsi: Poपूर्णांकer to VSI
 * @cls_flower: Poपूर्णांकer to काष्ठा flow_cls_offload
 *
 **/
अटल पूर्णांक i40e_delete_clsflower(काष्ठा i40e_vsi *vsi,
				 काष्ठा flow_cls_offload *cls_flower)
अणु
	काष्ठा i40e_cloud_filter *filter = शून्य;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक err = 0;

	filter = i40e_find_cloud_filter(vsi, &cls_flower->cookie);

	अगर (!filter)
		वापस -EINVAL;

	hash_del(&filter->cloud_node);

	अगर (filter->dst_port)
		err = i40e_add_del_cloud_filter_big_buf(vsi, filter, false);
	अन्यथा
		err = i40e_add_del_cloud_filter(vsi, filter, false);

	kमुक्त(filter);
	अगर (err) अणु
		dev_err(&pf->pdev->dev,
			"Failed to delete cloud filter, err %s\n",
			i40e_stat_str(&pf->hw, err));
		वापस i40e_aq_rc_to_posix(err, pf->hw.aq.asq_last_status);
	पूर्ण

	pf->num_cloud_filters--;
	अगर (!pf->num_cloud_filters)
		अगर ((pf->flags & I40E_FLAG_FD_SB_TO_CLOUD_FILTER) &&
		    !(pf->flags & I40E_FLAG_FD_SB_INACTIVE)) अणु
			pf->flags |= I40E_FLAG_FD_SB_ENABLED;
			pf->flags &= ~I40E_FLAG_FD_SB_TO_CLOUD_FILTER;
			pf->flags &= ~I40E_FLAG_FD_SB_INACTIVE;
		पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_setup_tc_cls_flower - flower classअगरier offloads
 * @np: net device to configure
 * @cls_flower: offload data
 **/
अटल पूर्णांक i40e_setup_tc_cls_flower(काष्ठा i40e_netdev_priv *np,
				    काष्ठा flow_cls_offload *cls_flower)
अणु
	काष्ठा i40e_vsi *vsi = np->vsi;

	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस i40e_configure_clsflower(vsi, cls_flower);
	हाल FLOW_CLS_DESTROY:
		वापस i40e_delete_clsflower(vsi, cls_flower);
	हाल FLOW_CLS_STATS:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक i40e_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				  व्योम *cb_priv)
अणु
	काष्ठा i40e_netdev_priv *np = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(np->vsi->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस i40e_setup_tc_cls_flower(np, type_data);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(i40e_block_cb_list);

अटल पूर्णांक __i40e_setup_tc(काष्ठा net_device *netdev, क्रमागत tc_setup_type type,
			   व्योम *type_data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);

	चयन (type) अणु
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस i40e_setup_tc(netdev, type_data);
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &i40e_block_cb_list,
						  i40e_setup_tc_block_cb,
						  np, np, true);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * i40e_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the netdev watchकरोg subtask is
 * enabled, and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 *
 * Returns 0 on success, negative value on failure
 **/
पूर्णांक i40e_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक err;

	/* disallow खोलो during test or अगर eeprom is broken */
	अगर (test_bit(__I40E_TESTING, pf->state) ||
	    test_bit(__I40E_BAD_EEPROM, pf->state))
		वापस -EBUSY;

	netअगर_carrier_off(netdev);

	अगर (i40e_क्रमce_link_state(pf, true))
		वापस -EAGAIN;

	err = i40e_vsi_खोलो(vsi);
	अगर (err)
		वापस err;

	/* configure global TSO hardware offload settings */
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_F, be32_to_cpu(TCP_FLAG_PSH |
						       TCP_FLAG_FIN) >> 16);
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_M, be32_to_cpu(TCP_FLAG_PSH |
						       TCP_FLAG_FIN |
						       TCP_FLAG_CWR) >> 16);
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_L, be32_to_cpu(TCP_FLAG_CWR) >> 16);
	udp_tunnel_get_rx_info(netdev);

	वापस 0;
पूर्ण

/**
 * i40e_vsi_खोलो -
 * @vsi: the VSI to खोलो
 *
 * Finish initialization of the VSI.
 *
 * Returns 0 on success, negative value on failure
 *
 * Note: expects to be called जबतक under rtnl_lock()
 **/
पूर्णांक i40e_vsi_खोलो(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	अक्षर पूर्णांक_name[I40E_INT_NAME_STR_LEN];
	पूर्णांक err;

	/* allocate descriptors */
	err = i40e_vsi_setup_tx_resources(vsi);
	अगर (err)
		जाओ err_setup_tx;
	err = i40e_vsi_setup_rx_resources(vsi);
	अगर (err)
		जाओ err_setup_rx;

	err = i40e_vsi_configure(vsi);
	अगर (err)
		जाओ err_setup_rx;

	अगर (vsi->netdev) अणु
		snम_लिखो(पूर्णांक_name, माप(पूर्णांक_name) - 1, "%s-%s",
			 dev_driver_string(&pf->pdev->dev), vsi->netdev->name);
		err = i40e_vsi_request_irq(vsi, पूर्णांक_name);
		अगर (err)
			जाओ err_setup_rx;

		/* Notअगरy the stack of the actual queue counts. */
		err = netअगर_set_real_num_tx_queues(vsi->netdev,
						   vsi->num_queue_pairs);
		अगर (err)
			जाओ err_set_queues;

		err = netअगर_set_real_num_rx_queues(vsi->netdev,
						   vsi->num_queue_pairs);
		अगर (err)
			जाओ err_set_queues;

	पूर्ण अन्यथा अगर (vsi->type == I40E_VSI_Fसूची) अणु
		snम_लिखो(पूर्णांक_name, माप(पूर्णांक_name) - 1, "%s-%s:fdir",
			 dev_driver_string(&pf->pdev->dev),
			 dev_name(&pf->pdev->dev));
		err = i40e_vsi_request_irq(vsi, पूर्णांक_name);

	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ err_setup_rx;
	पूर्ण

	err = i40e_up_complete(vsi);
	अगर (err)
		जाओ err_up_complete;

	वापस 0;

err_up_complete:
	i40e_करोwn(vsi);
err_set_queues:
	i40e_vsi_मुक्त_irq(vsi);
err_setup_rx:
	i40e_vsi_मुक्त_rx_resources(vsi);
err_setup_tx:
	i40e_vsi_मुक्त_tx_resources(vsi);
	अगर (vsi == pf->vsi[pf->lan_vsi])
		i40e_करो_reset(pf, I40E_PF_RESET_FLAG, true);

	वापस err;
पूर्ण

/**
 * i40e_fdir_filter_निकास - Cleans up the Flow Director accounting
 * @pf: Poपूर्णांकer to PF
 *
 * This function destroys the hlist where all the Flow Director
 * filters were saved.
 **/
अटल व्योम i40e_fdir_filter_निकास(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_fdir_filter *filter;
	काष्ठा i40e_flex_pit *pit_entry, *पंचांगp;
	काष्ठा hlist_node *node2;

	hlist_क्रम_each_entry_safe(filter, node2,
				  &pf->fdir_filter_list, fdir_node) अणु
		hlist_del(&filter->fdir_node);
		kमुक्त(filter);
	पूर्ण

	list_क्रम_each_entry_safe(pit_entry, पंचांगp, &pf->l3_flex_pit_list, list) अणु
		list_del(&pit_entry->list);
		kमुक्त(pit_entry);
	पूर्ण
	INIT_LIST_HEAD(&pf->l3_flex_pit_list);

	list_क्रम_each_entry_safe(pit_entry, पंचांगp, &pf->l4_flex_pit_list, list) अणु
		list_del(&pit_entry->list);
		kमुक्त(pit_entry);
	पूर्ण
	INIT_LIST_HEAD(&pf->l4_flex_pit_list);

	pf->fdir_pf_active_filters = 0;
	i40e_reset_fdir_filter_cnt(pf);

	/* Reprogram the शेष input set क्रम TCP/IPv4 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV4_TCP,
				I40E_L3_SRC_MASK | I40E_L3_DST_MASK |
				I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

	/* Reprogram the शेष input set क्रम TCP/IPv6 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV6_TCP,
				I40E_L3_V6_SRC_MASK | I40E_L3_V6_DST_MASK |
				I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

	/* Reprogram the शेष input set क्रम UDP/IPv4 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV4_UDP,
				I40E_L3_SRC_MASK | I40E_L3_DST_MASK |
				I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

	/* Reprogram the शेष input set क्रम UDP/IPv6 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV6_UDP,
				I40E_L3_V6_SRC_MASK | I40E_L3_V6_DST_MASK |
				I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

	/* Reprogram the शेष input set क्रम SCTP/IPv4 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV4_SCTP,
				I40E_L3_SRC_MASK | I40E_L3_DST_MASK |
				I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

	/* Reprogram the शेष input set क्रम SCTP/IPv6 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV6_SCTP,
				I40E_L3_V6_SRC_MASK | I40E_L3_V6_DST_MASK |
				I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

	/* Reprogram the शेष input set क्रम Other/IPv4 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV4_OTHER,
				I40E_L3_SRC_MASK | I40E_L3_DST_MASK);

	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_FRAG_IPV4,
				I40E_L3_SRC_MASK | I40E_L3_DST_MASK);

	/* Reprogram the शेष input set क्रम Other/IPv6 */
	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV6_OTHER,
				I40E_L3_SRC_MASK | I40E_L3_DST_MASK);

	i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_FRAG_IPV6,
				I40E_L3_SRC_MASK | I40E_L3_DST_MASK);
पूर्ण

/**
 * i40e_cloud_filter_निकास - Cleans up the cloud filters
 * @pf: Poपूर्णांकer to PF
 *
 * This function destroys the hlist where all the cloud filters
 * were saved.
 **/
अटल व्योम i40e_cloud_filter_निकास(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_cloud_filter *cfilter;
	काष्ठा hlist_node *node;

	hlist_क्रम_each_entry_safe(cfilter, node,
				  &pf->cloud_filter_list, cloud_node) अणु
		hlist_del(&cfilter->cloud_node);
		kमुक्त(cfilter);
	पूर्ण
	pf->num_cloud_filters = 0;

	अगर ((pf->flags & I40E_FLAG_FD_SB_TO_CLOUD_FILTER) &&
	    !(pf->flags & I40E_FLAG_FD_SB_INACTIVE)) अणु
		pf->flags |= I40E_FLAG_FD_SB_ENABLED;
		pf->flags &= ~I40E_FLAG_FD_SB_TO_CLOUD_FILTER;
		pf->flags &= ~I40E_FLAG_FD_SB_INACTIVE;
	पूर्ण
पूर्ण

/**
 * i40e_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the driver's control, but
 * this netdev पूर्णांकerface is disabled.
 *
 * Returns 0, this is not allowed to fail
 **/
पूर्णांक i40e_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	i40e_vsi_बंद(vsi);

	वापस 0;
पूर्ण

/**
 * i40e_करो_reset - Start a PF or Core Reset sequence
 * @pf: board निजी काष्ठाure
 * @reset_flags: which reset is requested
 * @lock_acquired: indicates whether or not the lock has been acquired
 * beक्रमe this function was called.
 *
 * The essential dअगरference in resets is that the PF Reset
 * करोesn't clear the packet buffers, doesn't reset the PE
 * firmware, and करोesn't bother the other PFs on the chip.
 **/
व्योम i40e_करो_reset(काष्ठा i40e_pf *pf, u32 reset_flags, bool lock_acquired)
अणु
	u32 val;

	/* करो the biggest reset indicated */
	अगर (reset_flags & BIT_ULL(__I40E_GLOBAL_RESET_REQUESTED)) अणु

		/* Request a Global Reset
		 *
		 * This will start the chip's countकरोwn to the actual full
		 * chip reset event, and a warning पूर्णांकerrupt to be sent
		 * to all PFs, including the requestor.  Our handler
		 * क्रम the warning पूर्णांकerrupt will deal with the shutकरोwn
		 * and recovery of the चयन setup.
		 */
		dev_dbg(&pf->pdev->dev, "GlobalR requested\n");
		val = rd32(&pf->hw, I40E_GLGEN_RTRIG);
		val |= I40E_GLGEN_RTRIG_GLOBR_MASK;
		wr32(&pf->hw, I40E_GLGEN_RTRIG, val);

	पूर्ण अन्यथा अगर (reset_flags & BIT_ULL(__I40E_CORE_RESET_REQUESTED)) अणु

		/* Request a Core Reset
		 *
		 * Same as Global Reset, except करोes *not* include the MAC/PHY
		 */
		dev_dbg(&pf->pdev->dev, "CoreR requested\n");
		val = rd32(&pf->hw, I40E_GLGEN_RTRIG);
		val |= I40E_GLGEN_RTRIG_CORER_MASK;
		wr32(&pf->hw, I40E_GLGEN_RTRIG, val);
		i40e_flush(&pf->hw);

	पूर्ण अन्यथा अगर (reset_flags & I40E_PF_RESET_FLAG) अणु

		/* Request a PF Reset
		 *
		 * Resets only the PF-specअगरic रेजिस्टरs
		 *
		 * This goes directly to the tear-करोwn and rebuild of
		 * the चयन, since we need to करो all the recovery as
		 * क्रम the Core Reset.
		 */
		dev_dbg(&pf->pdev->dev, "PFR requested\n");
		i40e_handle_reset_warning(pf, lock_acquired);

	पूर्ण अन्यथा अगर (reset_flags & I40E_PF_RESET_AND_REBUILD_FLAG) अणु
		/* Request a PF Reset
		 *
		 * Resets PF and reinitializes PFs VSI.
		 */
		i40e_prep_क्रम_reset(pf);
		i40e_reset_and_rebuild(pf, true, lock_acquired);
		dev_info(&pf->pdev->dev,
			 pf->flags & I40E_FLAG_DISABLE_FW_LLDP ?
			 "FW LLDP is disabled\n" :
			 "FW LLDP is enabled\n");

	पूर्ण अन्यथा अगर (reset_flags & BIT_ULL(__I40E_REINIT_REQUESTED)) अणु
		पूर्णांक v;

		/* Find the VSI(s) that requested a re-init */
		dev_info(&pf->pdev->dev,
			 "VSI reinit requested\n");
		क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
			काष्ठा i40e_vsi *vsi = pf->vsi[v];

			अगर (vsi != शून्य &&
			    test_and_clear_bit(__I40E_VSI_REINIT_REQUESTED,
					       vsi->state))
				i40e_vsi_reinit_locked(pf->vsi[v]);
		पूर्ण
	पूर्ण अन्यथा अगर (reset_flags & BIT_ULL(__I40E_DOWN_REQUESTED)) अणु
		पूर्णांक v;

		/* Find the VSI(s) that needs to be brought करोwn */
		dev_info(&pf->pdev->dev, "VSI down requested\n");
		क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
			काष्ठा i40e_vsi *vsi = pf->vsi[v];

			अगर (vsi != शून्य &&
			    test_and_clear_bit(__I40E_VSI_DOWN_REQUESTED,
					       vsi->state)) अणु
				set_bit(__I40E_VSI_DOWN, vsi->state);
				i40e_करोwn(vsi);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&pf->pdev->dev,
			 "bad reset request 0x%08x\n", reset_flags);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_I40E_DCB
/**
 * i40e_dcb_need_reconfig - Check अगर DCB needs reconfig
 * @pf: board निजी काष्ठाure
 * @old_cfg: current DCB config
 * @new_cfg: new DCB config
 **/
bool i40e_dcb_need_reconfig(काष्ठा i40e_pf *pf,
			    काष्ठा i40e_dcbx_config *old_cfg,
			    काष्ठा i40e_dcbx_config *new_cfg)
अणु
	bool need_reconfig = false;

	/* Check अगर ETS configuration has changed */
	अगर (स_भेद(&new_cfg->etscfg,
		   &old_cfg->etscfg,
		   माप(new_cfg->etscfg))) अणु
		/* If Priority Table has changed reconfig is needed */
		अगर (स_भेद(&new_cfg->etscfg.prioritytable,
			   &old_cfg->etscfg.prioritytable,
			   माप(new_cfg->etscfg.prioritytable))) अणु
			need_reconfig = true;
			dev_dbg(&pf->pdev->dev, "ETS UP2TC changed.\n");
		पूर्ण

		अगर (स_भेद(&new_cfg->etscfg.tcbwtable,
			   &old_cfg->etscfg.tcbwtable,
			   माप(new_cfg->etscfg.tcbwtable)))
			dev_dbg(&pf->pdev->dev, "ETS TC BW Table changed.\n");

		अगर (स_भेद(&new_cfg->etscfg.tsatable,
			   &old_cfg->etscfg.tsatable,
			   माप(new_cfg->etscfg.tsatable)))
			dev_dbg(&pf->pdev->dev, "ETS TSA Table changed.\n");
	पूर्ण

	/* Check अगर PFC configuration has changed */
	अगर (स_भेद(&new_cfg->pfc,
		   &old_cfg->pfc,
		   माप(new_cfg->pfc))) अणु
		need_reconfig = true;
		dev_dbg(&pf->pdev->dev, "PFC config change detected.\n");
	पूर्ण

	/* Check अगर APP Table has changed */
	अगर (स_भेद(&new_cfg->app,
		   &old_cfg->app,
		   माप(new_cfg->app))) अणु
		need_reconfig = true;
		dev_dbg(&pf->pdev->dev, "APP Table change detected.\n");
	पूर्ण

	dev_dbg(&pf->pdev->dev, "dcb need_reconfig=%d\n", need_reconfig);
	वापस need_reconfig;
पूर्ण

/**
 * i40e_handle_lldp_event - Handle LLDP Change MIB event
 * @pf: board निजी काष्ठाure
 * @e: event info posted on ARQ
 **/
अटल पूर्णांक i40e_handle_lldp_event(काष्ठा i40e_pf *pf,
				  काष्ठा i40e_arq_event_info *e)
अणु
	काष्ठा i40e_aqc_lldp_get_mib *mib =
		(काष्ठा i40e_aqc_lldp_get_mib *)&e->desc.params.raw;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_dcbx_config पंचांगp_dcbx_cfg;
	bool need_reconfig = false;
	पूर्णांक ret = 0;
	u8 type;

	/* X710-T*L 2.5G and 5G speeds करोn't support DCB */
	अगर (I40E_IS_X710TL_DEVICE(hw->device_id) &&
	    (hw->phy.link_info.link_speed &
	     ~(I40E_LINK_SPEED_2_5GB | I40E_LINK_SPEED_5GB)) &&
	     !(pf->flags & I40E_FLAG_DCB_CAPABLE))
		/* let firmware decide अगर the DCB should be disabled */
		pf->flags |= I40E_FLAG_DCB_CAPABLE;

	/* Not DCB capable or capability disabled */
	अगर (!(pf->flags & I40E_FLAG_DCB_CAPABLE))
		वापस ret;

	/* Ignore अगर event is not क्रम Nearest Bridge */
	type = ((mib->type >> I40E_AQ_LLDP_BRIDGE_TYPE_SHIFT)
		& I40E_AQ_LLDP_BRIDGE_TYPE_MASK);
	dev_dbg(&pf->pdev->dev, "LLDP event mib bridge type 0x%x\n", type);
	अगर (type != I40E_AQ_LLDP_BRIDGE_TYPE_NEAREST_BRIDGE)
		वापस ret;

	/* Check MIB Type and वापस अगर event क्रम Remote MIB update */
	type = mib->type & I40E_AQ_LLDP_MIB_TYPE_MASK;
	dev_dbg(&pf->pdev->dev,
		"LLDP event mib type %s\n", type ? "remote" : "local");
	अगर (type == I40E_AQ_LLDP_MIB_REMOTE) अणु
		/* Update the remote cached instance and वापस */
		ret = i40e_aq_get_dcb_config(hw, I40E_AQ_LLDP_MIB_REMOTE,
				I40E_AQ_LLDP_BRIDGE_TYPE_NEAREST_BRIDGE,
				&hw->remote_dcbx_config);
		जाओ निकास;
	पूर्ण

	/* Store the old configuration */
	पंचांगp_dcbx_cfg = hw->local_dcbx_config;

	/* Reset the old DCBx configuration data */
	स_रखो(&hw->local_dcbx_config, 0, माप(hw->local_dcbx_config));
	/* Get updated DCBX data from firmware */
	ret = i40e_get_dcb_config(&pf->hw);
	अगर (ret) अणु
		/* X710-T*L 2.5G and 5G speeds करोn't support DCB */
		अगर (I40E_IS_X710TL_DEVICE(hw->device_id) &&
		    (hw->phy.link_info.link_speed &
		     (I40E_LINK_SPEED_2_5GB | I40E_LINK_SPEED_5GB))) अणु
			dev_warn(&pf->pdev->dev,
				 "DCB is not supported for X710-T*L 2.5/5G speeds\n");
			pf->flags &= ~I40E_FLAG_DCB_CAPABLE;
		पूर्ण अन्यथा अणु
			dev_info(&pf->pdev->dev,
				 "Failed querying DCB configuration data from firmware, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
		पूर्ण
		जाओ निकास;
	पूर्ण

	/* No change detected in DCBX configs */
	अगर (!स_भेद(&पंचांगp_dcbx_cfg, &hw->local_dcbx_config,
		    माप(पंचांगp_dcbx_cfg))) अणु
		dev_dbg(&pf->pdev->dev, "No change detected in DCBX configuration.\n");
		जाओ निकास;
	पूर्ण

	need_reconfig = i40e_dcb_need_reconfig(pf, &पंचांगp_dcbx_cfg,
					       &hw->local_dcbx_config);

	i40e_dcbnl_flush_apps(pf, &पंचांगp_dcbx_cfg, &hw->local_dcbx_config);

	अगर (!need_reconfig)
		जाओ निकास;

	/* Enable DCB tagging only when more than one TC */
	अगर (i40e_dcb_get_num_tc(&hw->local_dcbx_config) > 1)
		pf->flags |= I40E_FLAG_DCB_ENABLED;
	अन्यथा
		pf->flags &= ~I40E_FLAG_DCB_ENABLED;

	set_bit(__I40E_PORT_SUSPENDED, pf->state);
	/* Reconfiguration needed quiesce all VSIs */
	i40e_pf_quiesce_all_vsi(pf);

	/* Changes in configuration update VEB/VSI */
	i40e_dcb_reconfigure(pf);

	ret = i40e_resume_port_tx(pf);

	clear_bit(__I40E_PORT_SUSPENDED, pf->state);
	/* In हाल of error no poपूर्णांक in resuming VSIs */
	अगर (ret)
		जाओ निकास;

	/* Wait क्रम the PF's queues to be disabled */
	ret = i40e_pf_रुको_queues_disabled(pf);
	अगर (ret) अणु
		/* Schedule PF reset to recover */
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		i40e_service_event_schedule(pf);
	पूर्ण अन्यथा अणु
		i40e_pf_unquiesce_all_vsi(pf);
		set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
		set_bit(__I40E_CLIENT_L2_CHANGE, pf->state);
	पूर्ण

निकास:
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_I40E_DCB */

/**
 * i40e_करो_reset_safe - Protected reset path क्रम userland calls.
 * @pf: board निजी काष्ठाure
 * @reset_flags: which reset is requested
 *
 **/
व्योम i40e_करो_reset_safe(काष्ठा i40e_pf *pf, u32 reset_flags)
अणु
	rtnl_lock();
	i40e_करो_reset(pf, reset_flags, true);
	rtnl_unlock();
पूर्ण

/**
 * i40e_handle_lan_overflow_event - Handler क्रम LAN queue overflow event
 * @pf: board निजी काष्ठाure
 * @e: event info posted on ARQ
 *
 * Handler क्रम LAN Queue Overflow Event generated by the firmware क्रम PF
 * and VF queues
 **/
अटल व्योम i40e_handle_lan_overflow_event(काष्ठा i40e_pf *pf,
					   काष्ठा i40e_arq_event_info *e)
अणु
	काष्ठा i40e_aqc_lan_overflow *data =
		(काष्ठा i40e_aqc_lan_overflow *)&e->desc.params.raw;
	u32 queue = le32_to_cpu(data->prtdcb_rupto);
	u32 qtx_ctl = le32_to_cpu(data->otx_ctl);
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vf *vf;
	u16 vf_id;

	dev_dbg(&pf->pdev->dev, "overflow Rx Queue Number = %d QTX_CTL=0x%08x\n",
		queue, qtx_ctl);

	/* Queue beदीर्घs to VF, find the VF and issue VF reset */
	अगर (((qtx_ctl & I40E_QTX_CTL_PFVF_Q_MASK)
	    >> I40E_QTX_CTL_PFVF_Q_SHIFT) == I40E_QTX_CTL_VF_QUEUE) अणु
		vf_id = (u16)((qtx_ctl & I40E_QTX_CTL_VFVM_INDX_MASK)
			 >> I40E_QTX_CTL_VFVM_INDX_SHIFT);
		vf_id -= hw->func_caps.vf_base_id;
		vf = &pf->vf[vf_id];
		i40e_vc_notअगरy_vf_reset(vf);
		/* Allow VF to process pending reset notअगरication */
		msleep(20);
		i40e_reset_vf(vf, false);
	पूर्ण
पूर्ण

/**
 * i40e_get_cur_guaranteed_fd_count - Get the consumed guaranteed FD filters
 * @pf: board निजी काष्ठाure
 **/
u32 i40e_get_cur_guaranteed_fd_count(काष्ठा i40e_pf *pf)
अणु
	u32 val, fcnt_prog;

	val = rd32(&pf->hw, I40E_PFQF_FDSTAT);
	fcnt_prog = (val & I40E_PFQF_FDSTAT_GUARANT_CNT_MASK);
	वापस fcnt_prog;
पूर्ण

/**
 * i40e_get_current_fd_count - Get total FD filters programmed क्रम this PF
 * @pf: board निजी काष्ठाure
 **/
u32 i40e_get_current_fd_count(काष्ठा i40e_pf *pf)
अणु
	u32 val, fcnt_prog;

	val = rd32(&pf->hw, I40E_PFQF_FDSTAT);
	fcnt_prog = (val & I40E_PFQF_FDSTAT_GUARANT_CNT_MASK) +
		    ((val & I40E_PFQF_FDSTAT_BEST_CNT_MASK) >>
		      I40E_PFQF_FDSTAT_BEST_CNT_SHIFT);
	वापस fcnt_prog;
पूर्ण

/**
 * i40e_get_global_fd_count - Get total FD filters programmed on device
 * @pf: board निजी काष्ठाure
 **/
u32 i40e_get_global_fd_count(काष्ठा i40e_pf *pf)
अणु
	u32 val, fcnt_prog;

	val = rd32(&pf->hw, I40E_GLQF_FDCNT_0);
	fcnt_prog = (val & I40E_GLQF_FDCNT_0_GUARANT_CNT_MASK) +
		    ((val & I40E_GLQF_FDCNT_0_BESTCNT_MASK) >>
		     I40E_GLQF_FDCNT_0_BESTCNT_SHIFT);
	वापस fcnt_prog;
पूर्ण

/**
 * i40e_reenable_fdir_sb - Restore FDir SB capability
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_reenable_fdir_sb(काष्ठा i40e_pf *pf)
अणु
	अगर (test_and_clear_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state))
		अगर ((pf->flags & I40E_FLAG_FD_SB_ENABLED) &&
		    (I40E_DEBUG_FD & pf->hw.debug_mask))
			dev_info(&pf->pdev->dev, "FD Sideband/ntuple is being enabled since we have space in the table now\n");
पूर्ण

/**
 * i40e_reenable_fdir_atr - Restore FDir ATR capability
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_reenable_fdir_atr(काष्ठा i40e_pf *pf)
अणु
	अगर (test_and_clear_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state)) अणु
		/* ATR uses the same filtering logic as SB rules. It only
		 * functions properly अगर the input set mask is at the शेष
		 * settings. It is safe to restore the शेष input set
		 * because there are no active TCPv4 filter rules.
		 */
		i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV4_TCP,
					I40E_L3_SRC_MASK | I40E_L3_DST_MASK |
					I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

		अगर ((pf->flags & I40E_FLAG_FD_ATR_ENABLED) &&
		    (I40E_DEBUG_FD & pf->hw.debug_mask))
			dev_info(&pf->pdev->dev, "ATR is being enabled since we have space in the table and there are no conflicting ntuple rules\n");
	पूर्ण
पूर्ण

/**
 * i40e_delete_invalid_filter - Delete an invalid Fसूची filter
 * @pf: board निजी काष्ठाure
 * @filter: FDir filter to हटाओ
 */
अटल व्योम i40e_delete_invalid_filter(काष्ठा i40e_pf *pf,
				       काष्ठा i40e_fdir_filter *filter)
अणु
	/* Update counters */
	pf->fdir_pf_active_filters--;
	pf->fd_inv = 0;

	चयन (filter->flow_type) अणु
	हाल TCP_V4_FLOW:
		pf->fd_tcp4_filter_cnt--;
		अवरोध;
	हाल UDP_V4_FLOW:
		pf->fd_udp4_filter_cnt--;
		अवरोध;
	हाल SCTP_V4_FLOW:
		pf->fd_sctp4_filter_cnt--;
		अवरोध;
	हाल TCP_V6_FLOW:
		pf->fd_tcp6_filter_cnt--;
		अवरोध;
	हाल UDP_V6_FLOW:
		pf->fd_udp6_filter_cnt--;
		अवरोध;
	हाल SCTP_V6_FLOW:
		pf->fd_udp6_filter_cnt--;
		अवरोध;
	हाल IP_USER_FLOW:
		चयन (filter->ipl4_proto) अणु
		हाल IPPROTO_TCP:
			pf->fd_tcp4_filter_cnt--;
			अवरोध;
		हाल IPPROTO_UDP:
			pf->fd_udp4_filter_cnt--;
			अवरोध;
		हाल IPPROTO_SCTP:
			pf->fd_sctp4_filter_cnt--;
			अवरोध;
		हाल IPPROTO_IP:
			pf->fd_ip4_filter_cnt--;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IPV6_USER_FLOW:
		चयन (filter->ipl4_proto) अणु
		हाल IPPROTO_TCP:
			pf->fd_tcp6_filter_cnt--;
			अवरोध;
		हाल IPPROTO_UDP:
			pf->fd_udp6_filter_cnt--;
			अवरोध;
		हाल IPPROTO_SCTP:
			pf->fd_sctp6_filter_cnt--;
			अवरोध;
		हाल IPPROTO_IP:
			pf->fd_ip6_filter_cnt--;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Remove the filter from the list and मुक्त memory */
	hlist_del(&filter->fdir_node);
	kमुक्त(filter);
पूर्ण

/**
 * i40e_fdir_check_and_reenable - Function to reenabe FD ATR or SB अगर disabled
 * @pf: board निजी काष्ठाure
 **/
व्योम i40e_fdir_check_and_reenable(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_fdir_filter *filter;
	u32 fcnt_prog, fcnt_avail;
	काष्ठा hlist_node *node;

	अगर (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
		वापस;

	/* Check अगर we have enough room to re-enable FDir SB capability. */
	fcnt_prog = i40e_get_global_fd_count(pf);
	fcnt_avail = pf->fdir_pf_filter_count;
	अगर ((fcnt_prog < (fcnt_avail - I40E_Fसूची_BUFFER_HEAD_ROOM)) ||
	    (pf->fd_add_err == 0) ||
	    (i40e_get_current_atr_cnt(pf) < pf->fd_atr_cnt))
		i40e_reenable_fdir_sb(pf);

	/* We should रुको क्रम even more space beक्रमe re-enabling ATR.
	 * Additionally, we cannot enable ATR as दीर्घ as we still have TCP SB
	 * rules active.
	 */
	अगर ((fcnt_prog < (fcnt_avail - I40E_Fसूची_BUFFER_HEAD_ROOM_FOR_ATR)) &&
	    pf->fd_tcp4_filter_cnt == 0 && pf->fd_tcp6_filter_cnt == 0)
		i40e_reenable_fdir_atr(pf);

	/* अगर hw had a problem adding a filter, delete it */
	अगर (pf->fd_inv > 0) अणु
		hlist_क्रम_each_entry_safe(filter, node,
					  &pf->fdir_filter_list, fdir_node)
			अगर (filter->fd_id == pf->fd_inv)
				i40e_delete_invalid_filter(pf, filter);
	पूर्ण
पूर्ण

#घोषणा I40E_MIN_FD_FLUSH_INTERVAL 10
#घोषणा I40E_MIN_FD_FLUSH_SB_ATR_UNSTABLE 30
/**
 * i40e_fdir_flush_and_replay - Function to flush all FD filters and replay SB
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_fdir_flush_and_replay(काष्ठा i40e_pf *pf)
अणु
	अचिन्हित दीर्घ min_flush_समय;
	पूर्णांक flush_रुको_retry = 50;
	bool disable_atr = false;
	पूर्णांक fd_room;
	पूर्णांक reg;

	अगर (!समय_after(jअगरfies, pf->fd_flush_बारtamp +
				 (I40E_MIN_FD_FLUSH_INTERVAL * HZ)))
		वापस;

	/* If the flush is happening too quick and we have mostly SB rules we
	 * should not re-enable ATR क्रम some समय.
	 */
	min_flush_समय = pf->fd_flush_बारtamp +
			 (I40E_MIN_FD_FLUSH_SB_ATR_UNSTABLE * HZ);
	fd_room = pf->fdir_pf_filter_count - pf->fdir_pf_active_filters;

	अगर (!(समय_after(jअगरfies, min_flush_समय)) &&
	    (fd_room < I40E_Fसूची_BUFFER_HEAD_ROOM_FOR_ATR)) अणु
		अगर (I40E_DEBUG_FD & pf->hw.debug_mask)
			dev_info(&pf->pdev->dev, "ATR disabled, not enough FD filter space.\n");
		disable_atr = true;
	पूर्ण

	pf->fd_flush_बारtamp = jअगरfies;
	set_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state);
	/* flush all filters */
	wr32(&pf->hw, I40E_PFQF_CTL_1,
	     I40E_PFQF_CTL_1_CLEARFDTABLE_MASK);
	i40e_flush(&pf->hw);
	pf->fd_flush_cnt++;
	pf->fd_add_err = 0;
	करो अणु
		/* Check FD flush status every 5-6msec */
		usleep_range(5000, 6000);
		reg = rd32(&pf->hw, I40E_PFQF_CTL_1);
		अगर (!(reg & I40E_PFQF_CTL_1_CLEARFDTABLE_MASK))
			अवरोध;
	पूर्ण जबतक (flush_रुको_retry--);
	अगर (reg & I40E_PFQF_CTL_1_CLEARFDTABLE_MASK) अणु
		dev_warn(&pf->pdev->dev, "FD table did not flush, needs more time\n");
	पूर्ण अन्यथा अणु
		/* replay sideband filters */
		i40e_fdir_filter_restore(pf->vsi[pf->lan_vsi]);
		अगर (!disable_atr && !pf->fd_tcp4_filter_cnt)
			clear_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state);
		clear_bit(__I40E_FD_FLUSH_REQUESTED, pf->state);
		अगर (I40E_DEBUG_FD & pf->hw.debug_mask)
			dev_info(&pf->pdev->dev, "FD Filter table flushed and FD-SB replayed.\n");
	पूर्ण
पूर्ण

/**
 * i40e_get_current_atr_cnt - Get the count of total FD ATR filters programmed
 * @pf: board निजी काष्ठाure
 **/
u32 i40e_get_current_atr_cnt(काष्ठा i40e_pf *pf)
अणु
	वापस i40e_get_current_fd_count(pf) - pf->fdir_pf_active_filters;
पूर्ण

/**
 * i40e_fdir_reinit_subtask - Worker thपढ़ो to reinit Fसूची filter table
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_fdir_reinit_subtask(काष्ठा i40e_pf *pf)
अणु

	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(__I40E_DOWN, pf->state))
		वापस;

	अगर (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
		i40e_fdir_flush_and_replay(pf);

	i40e_fdir_check_and_reenable(pf);

पूर्ण

/**
 * i40e_vsi_link_event - notअगरy VSI of a link event
 * @vsi: vsi to be notअगरied
 * @link_up: link up or करोwn
 **/
अटल व्योम i40e_vsi_link_event(काष्ठा i40e_vsi *vsi, bool link_up)
अणु
	अगर (!vsi || test_bit(__I40E_VSI_DOWN, vsi->state))
		वापस;

	चयन (vsi->type) अणु
	हाल I40E_VSI_MAIN:
		अगर (!vsi->netdev || !vsi->netdev_रेजिस्टरed)
			अवरोध;

		अगर (link_up) अणु
			netअगर_carrier_on(vsi->netdev);
			netअगर_tx_wake_all_queues(vsi->netdev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(vsi->netdev);
			netअगर_tx_stop_all_queues(vsi->netdev);
		पूर्ण
		अवरोध;

	हाल I40E_VSI_SRIOV:
	हाल I40E_VSI_VMDQ2:
	हाल I40E_VSI_CTRL:
	हाल I40E_VSI_IWARP:
	हाल I40E_VSI_MIRROR:
	शेष:
		/* there is no notअगरication क्रम other VSIs */
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40e_veb_link_event - notअगरy elements on the veb of a link event
 * @veb: veb to be notअगरied
 * @link_up: link up or करोwn
 **/
अटल व्योम i40e_veb_link_event(काष्ठा i40e_veb *veb, bool link_up)
अणु
	काष्ठा i40e_pf *pf;
	पूर्णांक i;

	अगर (!veb || !veb->pf)
		वापस;
	pf = veb->pf;

	/* depth first... */
	क्रम (i = 0; i < I40E_MAX_VEB; i++)
		अगर (pf->veb[i] && (pf->veb[i]->uplink_seid == veb->seid))
			i40e_veb_link_event(pf->veb[i], link_up);

	/* ... now the local VSIs */
	क्रम (i = 0; i < pf->num_alloc_vsi; i++)
		अगर (pf->vsi[i] && (pf->vsi[i]->uplink_seid == veb->seid))
			i40e_vsi_link_event(pf->vsi[i], link_up);
पूर्ण

/**
 * i40e_link_event - Update netअगर_carrier status
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_link_event(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	u8 new_link_speed, old_link_speed;
	i40e_status status;
	bool new_link, old_link;
#अगर_घोषित CONFIG_I40E_DCB
	पूर्णांक err;
#पूर्ण_अगर /* CONFIG_I40E_DCB */

	/* set this to क्रमce the get_link_status call to refresh state */
	pf->hw.phy.get_link_info = true;
	old_link = (pf->hw.phy.link_info_old.link_info & I40E_AQ_LINK_UP);
	status = i40e_get_link_status(&pf->hw, &new_link);

	/* On success, disable temp link polling */
	अगर (status == I40E_SUCCESS) अणु
		clear_bit(__I40E_TEMP_LINK_POLLING, pf->state);
	पूर्ण अन्यथा अणु
		/* Enable link polling temporarily until i40e_get_link_status
		 * वापसs I40E_SUCCESS
		 */
		set_bit(__I40E_TEMP_LINK_POLLING, pf->state);
		dev_dbg(&pf->pdev->dev, "couldn't get link state, status: %d\n",
			status);
		वापस;
	पूर्ण

	old_link_speed = pf->hw.phy.link_info_old.link_speed;
	new_link_speed = pf->hw.phy.link_info.link_speed;

	अगर (new_link == old_link &&
	    new_link_speed == old_link_speed &&
	    (test_bit(__I40E_VSI_DOWN, vsi->state) ||
	     new_link == netअगर_carrier_ok(vsi->netdev)))
		वापस;

	i40e_prपूर्णांक_link_message(vsi, new_link);

	/* Notअगरy the base of the चयन tree connected to
	 * the link.  Floating VEBs are not notअगरied.
	 */
	अगर (pf->lan_veb < I40E_MAX_VEB && pf->veb[pf->lan_veb])
		i40e_veb_link_event(pf->veb[pf->lan_veb], new_link);
	अन्यथा
		i40e_vsi_link_event(vsi, new_link);

	अगर (pf->vf)
		i40e_vc_notअगरy_link_state(pf);

	अगर (pf->flags & I40E_FLAG_PTP)
		i40e_ptp_set_increment(pf);
#अगर_घोषित CONFIG_I40E_DCB
	अगर (new_link == old_link)
		वापस;
	/* Not SW DCB so firmware will take care of शेष settings */
	अगर (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED)
		वापस;

	/* We cover here only link करोwn, as after link up in हाल of SW DCB
	 * SW LLDP agent will take care of setting it up
	 */
	अगर (!new_link) अणु
		dev_dbg(&pf->pdev->dev, "Reconfig DCB to single TC as result of Link Down\n");
		स_रखो(&pf->पंचांगp_cfg, 0, माप(pf->पंचांगp_cfg));
		err = i40e_dcb_sw_शेष_config(pf);
		अगर (err) अणु
			pf->flags &= ~(I40E_FLAG_DCB_CAPABLE |
				       I40E_FLAG_DCB_ENABLED);
		पूर्ण अन्यथा अणु
			pf->dcbx_cap = DCB_CAP_DCBX_HOST |
				       DCB_CAP_DCBX_VER_IEEE;
			pf->flags |= I40E_FLAG_DCB_CAPABLE;
			pf->flags &= ~I40E_FLAG_DCB_ENABLED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_I40E_DCB */
पूर्ण

/**
 * i40e_watchकरोg_subtask - periodic checks not using event driven response
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_watchकरोg_subtask(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक i;

	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		वापस;

	/* make sure we करोn't करो these things too often */
	अगर (समय_beक्रमe(jअगरfies, (pf->service_समयr_previous +
				  pf->service_समयr_period)))
		वापस;
	pf->service_समयr_previous = jअगरfies;

	अगर ((pf->flags & I40E_FLAG_LINK_POLLING_ENABLED) ||
	    test_bit(__I40E_TEMP_LINK_POLLING, pf->state))
		i40e_link_event(pf);

	/* Update the stats क्रम active netdevs so the network stack
	 * can look at updated numbers whenever it cares to
	 */
	क्रम (i = 0; i < pf->num_alloc_vsi; i++)
		अगर (pf->vsi[i] && pf->vsi[i]->netdev)
			i40e_update_stats(pf->vsi[i]);

	अगर (pf->flags & I40E_FLAG_VEB_STATS_ENABLED) अणु
		/* Update the stats क्रम the active चयनing components */
		क्रम (i = 0; i < I40E_MAX_VEB; i++)
			अगर (pf->veb[i])
				i40e_update_veb_stats(pf->veb[i]);
	पूर्ण

	i40e_ptp_rx_hang(pf);
	i40e_ptp_tx_hang(pf);
पूर्ण

/**
 * i40e_reset_subtask - Set up क्रम resetting the device and driver
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_reset_subtask(काष्ठा i40e_pf *pf)
अणु
	u32 reset_flags = 0;

	अगर (test_bit(__I40E_REINIT_REQUESTED, pf->state)) अणु
		reset_flags |= BIT(__I40E_REINIT_REQUESTED);
		clear_bit(__I40E_REINIT_REQUESTED, pf->state);
	पूर्ण
	अगर (test_bit(__I40E_PF_RESET_REQUESTED, pf->state)) अणु
		reset_flags |= BIT(__I40E_PF_RESET_REQUESTED);
		clear_bit(__I40E_PF_RESET_REQUESTED, pf->state);
	पूर्ण
	अगर (test_bit(__I40E_CORE_RESET_REQUESTED, pf->state)) अणु
		reset_flags |= BIT(__I40E_CORE_RESET_REQUESTED);
		clear_bit(__I40E_CORE_RESET_REQUESTED, pf->state);
	पूर्ण
	अगर (test_bit(__I40E_GLOBAL_RESET_REQUESTED, pf->state)) अणु
		reset_flags |= BIT(__I40E_GLOBAL_RESET_REQUESTED);
		clear_bit(__I40E_GLOBAL_RESET_REQUESTED, pf->state);
	पूर्ण
	अगर (test_bit(__I40E_DOWN_REQUESTED, pf->state)) अणु
		reset_flags |= BIT(__I40E_DOWN_REQUESTED);
		clear_bit(__I40E_DOWN_REQUESTED, pf->state);
	पूर्ण

	/* If there's a recovery alपढ़ोy रुकोing, it takes
	 * precedence beक्रमe starting a new reset sequence.
	 */
	अगर (test_bit(__I40E_RESET_INTR_RECEIVED, pf->state)) अणु
		i40e_prep_क्रम_reset(pf);
		i40e_reset(pf);
		i40e_rebuild(pf, false, false);
	पूर्ण

	/* If we're alपढ़ोy करोwn or resetting, just bail */
	अगर (reset_flags &&
	    !test_bit(__I40E_DOWN, pf->state) &&
	    !test_bit(__I40E_CONFIG_BUSY, pf->state)) अणु
		i40e_करो_reset(pf, reset_flags, false);
	पूर्ण
पूर्ण

/**
 * i40e_handle_link_event - Handle link event
 * @pf: board निजी काष्ठाure
 * @e: event info posted on ARQ
 **/
अटल व्योम i40e_handle_link_event(काष्ठा i40e_pf *pf,
				   काष्ठा i40e_arq_event_info *e)
अणु
	काष्ठा i40e_aqc_get_link_status *status =
		(काष्ठा i40e_aqc_get_link_status *)&e->desc.params.raw;

	/* Do a new status request to re-enable LSE reporting
	 * and load new status inक्रमmation पूर्णांकo the hw काष्ठा
	 * This completely ignores any state inक्रमmation
	 * in the ARQ event info, instead choosing to always
	 * issue the AQ update link status command.
	 */
	i40e_link_event(pf);

	/* Check अगर module meets thermal requirements */
	अगर (status->phy_type == I40E_PHY_TYPE_NOT_SUPPORTED_HIGH_TEMP) अणु
		dev_err(&pf->pdev->dev,
			"Rx/Tx is disabled on this device because the module does not meet thermal requirements.\n");
		dev_err(&pf->pdev->dev,
			"Refer to the Intel(R) Ethernet Adapters and Devices User Guide for a list of supported modules.\n");
	पूर्ण अन्यथा अणु
		/* check क्रम unqualअगरied module, अगर link is करोwn, suppress
		 * the message अगर link was क्रमced to be करोwn.
		 */
		अगर ((status->link_info & I40E_AQ_MEDIA_AVAILABLE) &&
		    (!(status->an_info & I40E_AQ_QUALIFIED_MODULE)) &&
		    (!(status->link_info & I40E_AQ_LINK_UP)) &&
		    (!(pf->flags & I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED))) अणु
			dev_err(&pf->pdev->dev,
				"Rx/Tx is disabled on this device because an unsupported SFP module type was detected.\n");
			dev_err(&pf->pdev->dev,
				"Refer to the Intel(R) Ethernet Adapters and Devices User Guide for a list of supported modules.\n");
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_clean_adminq_subtask - Clean the AdminQ rings
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_clean_adminq_subtask(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_arq_event_info event;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 pending, i = 0;
	i40e_status ret;
	u16 opcode;
	u32 oldval;
	u32 val;

	/* Do not run clean AQ when PF reset fails */
	अगर (test_bit(__I40E_RESET_FAILED, pf->state))
		वापस;

	/* check क्रम error indications */
	val = rd32(&pf->hw, pf->hw.aq.arq.len);
	oldval = val;
	अगर (val & I40E_PF_ARQLEN_ARQVFE_MASK) अणु
		अगर (hw->debug_mask & I40E_DEBUG_AQ)
			dev_info(&pf->pdev->dev, "ARQ VF Error detected\n");
		val &= ~I40E_PF_ARQLEN_ARQVFE_MASK;
	पूर्ण
	अगर (val & I40E_PF_ARQLEN_ARQOVFL_MASK) अणु
		अगर (hw->debug_mask & I40E_DEBUG_AQ)
			dev_info(&pf->pdev->dev, "ARQ Overflow Error detected\n");
		val &= ~I40E_PF_ARQLEN_ARQOVFL_MASK;
		pf->arq_overflows++;
	पूर्ण
	अगर (val & I40E_PF_ARQLEN_ARQCRIT_MASK) अणु
		अगर (hw->debug_mask & I40E_DEBUG_AQ)
			dev_info(&pf->pdev->dev, "ARQ Critical Error detected\n");
		val &= ~I40E_PF_ARQLEN_ARQCRIT_MASK;
	पूर्ण
	अगर (oldval != val)
		wr32(&pf->hw, pf->hw.aq.arq.len, val);

	val = rd32(&pf->hw, pf->hw.aq.asq.len);
	oldval = val;
	अगर (val & I40E_PF_ATQLEN_ATQVFE_MASK) अणु
		अगर (pf->hw.debug_mask & I40E_DEBUG_AQ)
			dev_info(&pf->pdev->dev, "ASQ VF Error detected\n");
		val &= ~I40E_PF_ATQLEN_ATQVFE_MASK;
	पूर्ण
	अगर (val & I40E_PF_ATQLEN_ATQOVFL_MASK) अणु
		अगर (pf->hw.debug_mask & I40E_DEBUG_AQ)
			dev_info(&pf->pdev->dev, "ASQ Overflow Error detected\n");
		val &= ~I40E_PF_ATQLEN_ATQOVFL_MASK;
	पूर्ण
	अगर (val & I40E_PF_ATQLEN_ATQCRIT_MASK) अणु
		अगर (pf->hw.debug_mask & I40E_DEBUG_AQ)
			dev_info(&pf->pdev->dev, "ASQ Critical Error detected\n");
		val &= ~I40E_PF_ATQLEN_ATQCRIT_MASK;
	पूर्ण
	अगर (oldval != val)
		wr32(&pf->hw, pf->hw.aq.asq.len, val);

	event.buf_len = I40E_MAX_AQ_BUF_SIZE;
	event.msg_buf = kzalloc(event.buf_len, GFP_KERNEL);
	अगर (!event.msg_buf)
		वापस;

	करो अणु
		ret = i40e_clean_arq_element(hw, &event, &pending);
		अगर (ret == I40E_ERR_ADMIN_QUEUE_NO_WORK)
			अवरोध;
		अन्यथा अगर (ret) अणु
			dev_info(&pf->pdev->dev, "ARQ event error %d\n", ret);
			अवरोध;
		पूर्ण

		opcode = le16_to_cpu(event.desc.opcode);
		चयन (opcode) अणु

		हाल i40e_aqc_opc_get_link_status:
			rtnl_lock();
			i40e_handle_link_event(pf, &event);
			rtnl_unlock();
			अवरोध;
		हाल i40e_aqc_opc_send_msg_to_pf:
			ret = i40e_vc_process_vf_msg(pf,
					le16_to_cpu(event.desc.retval),
					le32_to_cpu(event.desc.cookie_high),
					le32_to_cpu(event.desc.cookie_low),
					event.msg_buf,
					event.msg_len);
			अवरोध;
		हाल i40e_aqc_opc_lldp_update_mib:
			dev_dbg(&pf->pdev->dev, "ARQ: Update LLDP MIB event received\n");
#अगर_घोषित CONFIG_I40E_DCB
			rtnl_lock();
			i40e_handle_lldp_event(pf, &event);
			rtnl_unlock();
#पूर्ण_अगर /* CONFIG_I40E_DCB */
			अवरोध;
		हाल i40e_aqc_opc_event_lan_overflow:
			dev_dbg(&pf->pdev->dev, "ARQ LAN queue overflow event received\n");
			i40e_handle_lan_overflow_event(pf, &event);
			अवरोध;
		हाल i40e_aqc_opc_send_msg_to_peer:
			dev_info(&pf->pdev->dev, "ARQ: Msg from other pf\n");
			अवरोध;
		हाल i40e_aqc_opc_nvm_erase:
		हाल i40e_aqc_opc_nvm_update:
		हाल i40e_aqc_opc_oem_post_update:
			i40e_debug(&pf->hw, I40E_DEBUG_NVM,
				   "ARQ NVM operation 0x%04x completed\n",
				   opcode);
			अवरोध;
		शेष:
			dev_info(&pf->pdev->dev,
				 "ARQ: Unknown event 0x%04x ignored\n",
				 opcode);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (i++ < pf->adminq_work_limit);

	अगर (i < pf->adminq_work_limit)
		clear_bit(__I40E_ADMINQ_EVENT_PENDING, pf->state);

	/* re-enable Admin queue पूर्णांकerrupt cause */
	val = rd32(hw, I40E_PFINT_ICR0_ENA);
	val |=  I40E_PFINT_ICR0_ENA_ADMINQ_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, val);
	i40e_flush(hw);

	kमुक्त(event.msg_buf);
पूर्ण

/**
 * i40e_verअगरy_eeprom - make sure eeprom is good to use
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_verअगरy_eeprom(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक err;

	err = i40e_diag_eeprom_test(&pf->hw);
	अगर (err) अणु
		/* retry in हाल of garbage पढ़ो */
		err = i40e_diag_eeprom_test(&pf->hw);
		अगर (err) अणु
			dev_info(&pf->pdev->dev, "eeprom check failed (%d), Tx/Rx traffic disabled\n",
				 err);
			set_bit(__I40E_BAD_EEPROM, pf->state);
		पूर्ण
	पूर्ण

	अगर (!err && test_bit(__I40E_BAD_EEPROM, pf->state)) अणु
		dev_info(&pf->pdev->dev, "eeprom check passed, Tx/Rx traffic enabled\n");
		clear_bit(__I40E_BAD_EEPROM, pf->state);
	पूर्ण
पूर्ण

/**
 * i40e_enable_pf_चयन_lb
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * enable चयन loop back or die - no poपूर्णांक in a वापस value
 **/
अटल व्योम i40e_enable_pf_चयन_lb(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	काष्ठा i40e_vsi_context ctxt;
	पूर्णांक ret;

	ctxt.seid = pf->मुख्य_vsi_seid;
	ctxt.pf_num = pf->hw.pf_id;
	ctxt.vf_num = 0;
	ret = i40e_aq_get_vsi_params(&pf->hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस;
	पूर्ण
	ctxt.flags = I40E_AQ_VSI_TYPE_PF;
	ctxt.info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
	ctxt.info.चयन_id |= cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);

	ret = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "update vsi switch failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
	पूर्ण
पूर्ण

/**
 * i40e_disable_pf_चयन_lb
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * disable चयन loop back or die - no poपूर्णांक in a वापस value
 **/
अटल व्योम i40e_disable_pf_चयन_lb(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	काष्ठा i40e_vsi_context ctxt;
	पूर्णांक ret;

	ctxt.seid = pf->मुख्य_vsi_seid;
	ctxt.pf_num = pf->hw.pf_id;
	ctxt.vf_num = 0;
	ret = i40e_aq_get_vsi_params(&pf->hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस;
	पूर्ण
	ctxt.flags = I40E_AQ_VSI_TYPE_PF;
	ctxt.info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
	ctxt.info.चयन_id &= ~cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);

	ret = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "update vsi switch failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
	पूर्ण
पूर्ण

/**
 * i40e_config_bridge_mode - Configure the HW bridge mode
 * @veb: poपूर्णांकer to the bridge instance
 *
 * Configure the loop back mode क्रम the LAN VSI that is करोwnlink to the
 * specअगरied HW bridge instance. It is expected this function is called
 * when a new HW bridge is instantiated.
 **/
अटल व्योम i40e_config_bridge_mode(काष्ठा i40e_veb *veb)
अणु
	काष्ठा i40e_pf *pf = veb->pf;

	अगर (pf->hw.debug_mask & I40E_DEBUG_LAN)
		dev_info(&pf->pdev->dev, "enabling bridge mode: %s\n",
			 veb->bridge_mode == BRIDGE_MODE_VEPA ? "VEPA" : "VEB");
	अगर (veb->bridge_mode & BRIDGE_MODE_VEPA)
		i40e_disable_pf_चयन_lb(pf);
	अन्यथा
		i40e_enable_pf_चयन_lb(pf);
पूर्ण

/**
 * i40e_reस्थिरitute_veb - rebuild the VEB and anything connected to it
 * @veb: poपूर्णांकer to the VEB instance
 *
 * This is a recursive function that first builds the attached VSIs then
 * recurses in to build the next layer of VEB.  We track the connections
 * through our own index numbers because the seid's from the HW could
 * change across the reset.
 **/
अटल पूर्णांक i40e_reस्थिरitute_veb(काष्ठा i40e_veb *veb)
अणु
	काष्ठा i40e_vsi *ctl_vsi = शून्य;
	काष्ठा i40e_pf *pf = veb->pf;
	पूर्णांक v, veb_idx;
	पूर्णांक ret;

	/* build VSI that owns this VEB, temporarily attached to base VEB */
	क्रम (v = 0; v < pf->num_alloc_vsi && !ctl_vsi; v++) अणु
		अगर (pf->vsi[v] &&
		    pf->vsi[v]->veb_idx == veb->idx &&
		    pf->vsi[v]->flags & I40E_VSI_FLAG_VEB_OWNER) अणु
			ctl_vsi = pf->vsi[v];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!ctl_vsi) अणु
		dev_info(&pf->pdev->dev,
			 "missing owner VSI for veb_idx %d\n", veb->idx);
		ret = -ENOENT;
		जाओ end_reस्थिरitute;
	पूर्ण
	अगर (ctl_vsi != pf->vsi[pf->lan_vsi])
		ctl_vsi->uplink_seid = pf->vsi[pf->lan_vsi]->uplink_seid;
	ret = i40e_add_vsi(ctl_vsi);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "rebuild of veb_idx %d owner VSI failed: %d\n",
			 veb->idx, ret);
		जाओ end_reस्थिरitute;
	पूर्ण
	i40e_vsi_reset_stats(ctl_vsi);

	/* create the VEB in the चयन and move the VSI onto the VEB */
	ret = i40e_add_veb(veb, ctl_vsi);
	अगर (ret)
		जाओ end_reस्थिरitute;

	अगर (pf->flags & I40E_FLAG_VEB_MODE_ENABLED)
		veb->bridge_mode = BRIDGE_MODE_VEB;
	अन्यथा
		veb->bridge_mode = BRIDGE_MODE_VEPA;
	i40e_config_bridge_mode(veb);

	/* create the reमुख्यing VSIs attached to this VEB */
	क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
		अगर (!pf->vsi[v] || pf->vsi[v] == ctl_vsi)
			जारी;

		अगर (pf->vsi[v]->veb_idx == veb->idx) अणु
			काष्ठा i40e_vsi *vsi = pf->vsi[v];

			vsi->uplink_seid = veb->seid;
			ret = i40e_add_vsi(vsi);
			अगर (ret) अणु
				dev_info(&pf->pdev->dev,
					 "rebuild of vsi_idx %d failed: %d\n",
					 v, ret);
				जाओ end_reस्थिरitute;
			पूर्ण
			i40e_vsi_reset_stats(vsi);
		पूर्ण
	पूर्ण

	/* create any VEBs attached to this VEB - RECURSION */
	क्रम (veb_idx = 0; veb_idx < I40E_MAX_VEB; veb_idx++) अणु
		अगर (pf->veb[veb_idx] && pf->veb[veb_idx]->veb_idx == veb->idx) अणु
			pf->veb[veb_idx]->uplink_seid = veb->seid;
			ret = i40e_reस्थिरitute_veb(pf->veb[veb_idx]);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

end_reस्थिरitute:
	वापस ret;
पूर्ण

/**
 * i40e_get_capabilities - get info about the HW
 * @pf: the PF काष्ठा
 * @list_type: AQ capability to be queried
 **/
अटल पूर्णांक i40e_get_capabilities(काष्ठा i40e_pf *pf,
				 क्रमागत i40e_admin_queue_opc list_type)
अणु
	काष्ठा i40e_aqc_list_capabilities_element_resp *cap_buf;
	u16 data_size;
	पूर्णांक buf_len;
	पूर्णांक err;

	buf_len = 40 * माप(काष्ठा i40e_aqc_list_capabilities_element_resp);
	करो अणु
		cap_buf = kzalloc(buf_len, GFP_KERNEL);
		अगर (!cap_buf)
			वापस -ENOMEM;

		/* this loads the data पूर्णांकo the hw काष्ठा क्रम us */
		err = i40e_aq_discover_capabilities(&pf->hw, cap_buf, buf_len,
						    &data_size, list_type,
						    शून्य);
		/* data loaded, buffer no दीर्घer needed */
		kमुक्त(cap_buf);

		अगर (pf->hw.aq.asq_last_status == I40E_AQ_RC_ENOMEM) अणु
			/* retry with a larger buffer */
			buf_len = data_size;
		पूर्ण अन्यथा अगर (pf->hw.aq.asq_last_status != I40E_AQ_RC_OK) अणु
			dev_info(&pf->pdev->dev,
				 "capability discovery failed, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, err),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			वापस -ENODEV;
		पूर्ण
	पूर्ण जबतक (err);

	अगर (pf->hw.debug_mask & I40E_DEBUG_USER) अणु
		अगर (list_type == i40e_aqc_opc_list_func_capabilities) अणु
			dev_info(&pf->pdev->dev,
				 "pf=%d, num_vfs=%d, msix_pf=%d, msix_vf=%d, fd_g=%d, fd_b=%d, pf_max_q=%d num_vsi=%d\n",
				 pf->hw.pf_id, pf->hw.func_caps.num_vfs,
				 pf->hw.func_caps.num_msix_vectors,
				 pf->hw.func_caps.num_msix_vectors_vf,
				 pf->hw.func_caps.fd_filters_guaranteed,
				 pf->hw.func_caps.fd_filters_best_efक्रमt,
				 pf->hw.func_caps.num_tx_qp,
				 pf->hw.func_caps.num_vsis);
		पूर्ण अन्यथा अगर (list_type == i40e_aqc_opc_list_dev_capabilities) अणु
			dev_info(&pf->pdev->dev,
				 "switch_mode=0x%04x, function_valid=0x%08x\n",
				 pf->hw.dev_caps.चयन_mode,
				 pf->hw.dev_caps.valid_functions);
			dev_info(&pf->pdev->dev,
				 "SR-IOV=%d, num_vfs for all function=%u\n",
				 pf->hw.dev_caps.sr_iov_1_1,
				 pf->hw.dev_caps.num_vfs);
			dev_info(&pf->pdev->dev,
				 "num_vsis=%u, num_rx:%u, num_tx=%u\n",
				 pf->hw.dev_caps.num_vsis,
				 pf->hw.dev_caps.num_rx_qp,
				 pf->hw.dev_caps.num_tx_qp);
		पूर्ण
	पूर्ण
	अगर (list_type == i40e_aqc_opc_list_func_capabilities) अणु
#घोषणा DEF_NUM_VSI (1 + (pf->hw.func_caps.fcoe ? 1 : 0) \
		       + pf->hw.func_caps.num_vfs)
		अगर (pf->hw.revision_id == 0 &&
		    pf->hw.func_caps.num_vsis < DEF_NUM_VSI) अणु
			dev_info(&pf->pdev->dev,
				 "got num_vsis %d, setting num_vsis to %d\n",
				 pf->hw.func_caps.num_vsis, DEF_NUM_VSI);
			pf->hw.func_caps.num_vsis = DEF_NUM_VSI;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i40e_vsi_clear(काष्ठा i40e_vsi *vsi);

/**
 * i40e_fdir_sb_setup - initialize the Flow Director resources क्रम Sideband
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_fdir_sb_setup(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vsi *vsi;

	/* quick workaround क्रम an NVM issue that leaves a critical रेजिस्टर
	 * uninitialized
	 */
	अगर (!rd32(&pf->hw, I40E_GLQF_HKEY(0))) अणु
		अटल स्थिर u32 hkey[] = अणु
			0xe640d33f, 0xcdfe98ab, 0x73fa7161, 0x0d7a7d36,
			0xeacb7d61, 0xaa4f05b6, 0x9c5c89ed, 0xfc425ddb,
			0xa4654832, 0xfc7461d4, 0x8f827619, 0xf5c63c21,
			0x95b3a76dपूर्ण;
		पूर्णांक i;

		क्रम (i = 0; i <= I40E_GLQF_HKEY_MAX_INDEX; i++)
			wr32(&pf->hw, I40E_GLQF_HKEY(i), hkey[i]);
	पूर्ण

	अगर (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
		वापस;

	/* find existing VSI and see अगर it needs configuring */
	vsi = i40e_find_vsi_by_type(pf, I40E_VSI_Fसूची);

	/* create a new VSI अगर none exists */
	अगर (!vsi) अणु
		vsi = i40e_vsi_setup(pf, I40E_VSI_Fसूची,
				     pf->vsi[pf->lan_vsi]->seid, 0);
		अगर (!vsi) अणु
			dev_info(&pf->pdev->dev, "Couldn't create FDir VSI\n");
			pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
			pf->flags |= I40E_FLAG_FD_SB_INACTIVE;
			वापस;
		पूर्ण
	पूर्ण

	i40e_vsi_setup_irqhandler(vsi, i40e_fdir_clean_ring);
पूर्ण

/**
 * i40e_fdir_tearकरोwn - release the Flow Director resources
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_fdir_tearकरोwn(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vsi *vsi;

	i40e_fdir_filter_निकास(pf);
	vsi = i40e_find_vsi_by_type(pf, I40E_VSI_Fसूची);
	अगर (vsi)
		i40e_vsi_release(vsi);
पूर्ण

/**
 * i40e_rebuild_cloud_filters - Rebuilds cloud filters क्रम VSIs
 * @vsi: PF मुख्य vsi
 * @seid: seid of मुख्य or channel VSIs
 *
 * Rebuilds cloud filters associated with मुख्य VSI and channel VSIs अगर they
 * existed beक्रमe reset
 **/
अटल पूर्णांक i40e_rebuild_cloud_filters(काष्ठा i40e_vsi *vsi, u16 seid)
अणु
	काष्ठा i40e_cloud_filter *cfilter;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा hlist_node *node;
	i40e_status ret;

	/* Add cloud filters back अगर they exist */
	hlist_क्रम_each_entry_safe(cfilter, node, &pf->cloud_filter_list,
				  cloud_node) अणु
		अगर (cfilter->seid != seid)
			जारी;

		अगर (cfilter->dst_port)
			ret = i40e_add_del_cloud_filter_big_buf(vsi, cfilter,
								true);
		अन्यथा
			ret = i40e_add_del_cloud_filter(vsi, cfilter, true);

		अगर (ret) अणु
			dev_dbg(&pf->pdev->dev,
				"Failed to rebuild cloud filter, err %s aq_err %s\n",
				i40e_stat_str(&pf->hw, ret),
				i40e_aq_str(&pf->hw,
					    pf->hw.aq.asq_last_status));
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_rebuild_channels - Rebuilds channel VSIs अगर they existed beक्रमe reset
 * @vsi: PF मुख्य vsi
 *
 * Rebuilds channel VSIs अगर they existed beक्रमe reset
 **/
अटल पूर्णांक i40e_rebuild_channels(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_channel *ch, *ch_पंचांगp;
	i40e_status ret;

	अगर (list_empty(&vsi->ch_list))
		वापस 0;

	list_क्रम_each_entry_safe(ch, ch_पंचांगp, &vsi->ch_list, list) अणु
		अगर (!ch->initialized)
			अवरोध;
		/* Proceed with creation of channel (VMDq2) VSI */
		ret = i40e_add_channel(vsi->back, vsi->uplink_seid, ch);
		अगर (ret) अणु
			dev_info(&vsi->back->pdev->dev,
				 "failed to rebuild channels using uplink_seid %u\n",
				 vsi->uplink_seid);
			वापस ret;
		पूर्ण
		/* Reconfigure TX queues using QTX_CTL रेजिस्टर */
		ret = i40e_channel_config_tx_ring(vsi->back, vsi, ch);
		अगर (ret) अणु
			dev_info(&vsi->back->pdev->dev,
				 "failed to configure TX rings for channel %u\n",
				 ch->seid);
			वापस ret;
		पूर्ण
		/* update 'next_base_queue' */
		vsi->next_base_queue = vsi->next_base_queue +
							ch->num_queue_pairs;
		अगर (ch->max_tx_rate) अणु
			u64 credits = ch->max_tx_rate;

			अगर (i40e_set_bw_limit(vsi, ch->seid,
					      ch->max_tx_rate))
				वापस -EINVAL;

			करो_भाग(credits, I40E_BW_CREDIT_DIVISOR);
			dev_dbg(&vsi->back->pdev->dev,
				"Set tx rate of %llu Mbps (count of 50Mbps %llu) for vsi->seid %u\n",
				ch->max_tx_rate,
				credits,
				ch->seid);
		पूर्ण
		ret = i40e_rebuild_cloud_filters(vsi, ch->seid);
		अगर (ret) अणु
			dev_dbg(&vsi->back->pdev->dev,
				"Failed to rebuild cloud filters for channel VSI %u\n",
				ch->seid);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_prep_क्रम_reset - prep क्रम the core to reset
 * @pf: board निजी काष्ठाure
 *
 * Close up the VFs and other things in prep क्रम PF Reset.
  **/
अटल व्योम i40e_prep_क्रम_reset(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status ret = 0;
	u32 v;

	clear_bit(__I40E_RESET_INTR_RECEIVED, pf->state);
	अगर (test_and_set_bit(__I40E_RESET_RECOVERY_PENDING, pf->state))
		वापस;
	अगर (i40e_check_asq_alive(&pf->hw))
		i40e_vc_notअगरy_reset(pf);

	dev_dbg(&pf->pdev->dev, "Tearing down internal switch for reset\n");

	/* quiesce the VSIs and their queues that are not alपढ़ोy DOWN */
	i40e_pf_quiesce_all_vsi(pf);

	क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
		अगर (pf->vsi[v])
			pf->vsi[v]->seid = 0;
	पूर्ण

	i40e_shutकरोwn_adminq(&pf->hw);

	/* call shutकरोwn HMC */
	अगर (hw->hmc.hmc_obj) अणु
		ret = i40e_shutकरोwn_lan_hmc(hw);
		अगर (ret)
			dev_warn(&pf->pdev->dev,
				 "shutdown_lan_hmc failed: %d\n", ret);
	पूर्ण

	/* Save the current PTP समय so that we can restore the समय after the
	 * reset completes.
	 */
	i40e_ptp_save_hw_समय(pf);
पूर्ण

/**
 * i40e_send_version - update firmware with driver version
 * @pf: PF काष्ठा
 */
अटल व्योम i40e_send_version(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_driver_version dv;

	dv.major_version = 0xff;
	dv.minor_version = 0xff;
	dv.build_version = 0xff;
	dv.subbuild_version = 0;
	strlcpy(dv.driver_string, UTS_RELEASE, माप(dv.driver_string));
	i40e_aq_send_driver_version(&pf->hw, &dv, शून्य);
पूर्ण

/**
 * i40e_get_oem_version - get OEM specअगरic version inक्रमmation
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल व्योम i40e_get_oem_version(काष्ठा i40e_hw *hw)
अणु
	u16 block_offset = 0xffff;
	u16 block_length = 0;
	u16 capabilities = 0;
	u16 gen_snap = 0;
	u16 release = 0;

#घोषणा I40E_SR_NVM_OEM_VERSION_PTR		0x1B
#घोषणा I40E_NVM_OEM_LENGTH_OFFSET		0x00
#घोषणा I40E_NVM_OEM_CAPABILITIES_OFFSET	0x01
#घोषणा I40E_NVM_OEM_GEN_OFFSET			0x02
#घोषणा I40E_NVM_OEM_RELEASE_OFFSET		0x03
#घोषणा I40E_NVM_OEM_CAPABILITIES_MASK		0x000F
#घोषणा I40E_NVM_OEM_LENGTH			3

	/* Check अगर poपूर्णांकer to OEM version block is valid. */
	i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_OEM_VERSION_PTR, &block_offset);
	अगर (block_offset == 0xffff)
		वापस;

	/* Check अगर OEM version block has correct length. */
	i40e_पढ़ो_nvm_word(hw, block_offset + I40E_NVM_OEM_LENGTH_OFFSET,
			   &block_length);
	अगर (block_length < I40E_NVM_OEM_LENGTH)
		वापस;

	/* Check अगर OEM version क्रमmat is as expected. */
	i40e_पढ़ो_nvm_word(hw, block_offset + I40E_NVM_OEM_CAPABILITIES_OFFSET,
			   &capabilities);
	अगर ((capabilities & I40E_NVM_OEM_CAPABILITIES_MASK) != 0)
		वापस;

	i40e_पढ़ो_nvm_word(hw, block_offset + I40E_NVM_OEM_GEN_OFFSET,
			   &gen_snap);
	i40e_पढ़ो_nvm_word(hw, block_offset + I40E_NVM_OEM_RELEASE_OFFSET,
			   &release);
	hw->nvm.oem_ver = (gen_snap << I40E_OEM_SNAP_SHIFT) | release;
	hw->nvm.eetrack = I40E_OEM_EETRACK_ID;
पूर्ण

/**
 * i40e_reset - रुको क्रम core reset to finish reset, reset pf अगर corer not seen
 * @pf: board निजी काष्ठाure
 **/
अटल पूर्णांक i40e_reset(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status ret;

	ret = i40e_pf_reset(hw);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev, "PF reset failed, %d\n", ret);
		set_bit(__I40E_RESET_FAILED, pf->state);
		clear_bit(__I40E_RESET_RECOVERY_PENDING, pf->state);
	पूर्ण अन्यथा अणु
		pf->pfr_count++;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40e_rebuild - rebuild using a saved config
 * @pf: board निजी काष्ठाure
 * @reinit: अगर the Main VSI needs to re-initialized.
 * @lock_acquired: indicates whether or not the lock has been acquired
 * beक्रमe this function was called.
 **/
अटल व्योम i40e_rebuild(काष्ठा i40e_pf *pf, bool reinit, bool lock_acquired)
अणु
	पूर्णांक old_recovery_mode_bit = test_bit(__I40E_RECOVERY_MODE, pf->state);
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status ret;
	u32 val;
	पूर्णांक v;

	अगर (test_bit(__I40E_EMP_RESET_INTR_RECEIVED, pf->state) &&
	    i40e_check_recovery_mode(pf)) अणु
		i40e_set_ethtool_ops(pf->vsi[pf->lan_vsi]->netdev);
	पूर्ण

	अगर (test_bit(__I40E_DOWN, pf->state) &&
	    !test_bit(__I40E_RECOVERY_MODE, pf->state) &&
	    !old_recovery_mode_bit)
		जाओ clear_recovery;
	dev_dbg(&pf->pdev->dev, "Rebuilding internal switch\n");

	/* rebuild the basics क्रम the AdminQ, HMC, and initial HW चयन */
	ret = i40e_init_adminq(&pf->hw);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev, "Rebuild AdminQ failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		जाओ clear_recovery;
	पूर्ण
	i40e_get_oem_version(&pf->hw);

	अगर (test_bit(__I40E_EMP_RESET_INTR_RECEIVED, pf->state) &&
	    ((hw->aq.fw_maj_ver == 4 && hw->aq.fw_min_ver <= 33) ||
	     hw->aq.fw_maj_ver < 4) && hw->mac.type == I40E_MAC_XL710) अणु
		/* The following delay is necessary क्रम 4.33 firmware and older
		 * to recover after EMP reset. 200 ms should suffice but we
		 * put here 300 ms to be sure that FW is पढ़ोy to operate
		 * after reset.
		 */
		mdelay(300);
	पूर्ण

	/* re-verअगरy the eeprom अगर we just had an EMP reset */
	अगर (test_and_clear_bit(__I40E_EMP_RESET_INTR_RECEIVED, pf->state))
		i40e_verअगरy_eeprom(pf);

	/* अगर we are going out of or पूर्णांकo recovery mode we have to act
	 * accordingly with regard to resources initialization
	 * and deinitialization
	 */
	अगर (test_bit(__I40E_RECOVERY_MODE, pf->state) ||
	    old_recovery_mode_bit) अणु
		अगर (i40e_get_capabilities(pf,
					  i40e_aqc_opc_list_func_capabilities))
			जाओ end_unlock;

		अगर (test_bit(__I40E_RECOVERY_MODE, pf->state)) अणु
			/* we're staying in recovery mode so we'll reinitialize
			 * misc vector here
			 */
			अगर (i40e_setup_misc_vector_क्रम_recovery_mode(pf))
				जाओ end_unlock;
		पूर्ण अन्यथा अणु
			अगर (!lock_acquired)
				rtnl_lock();
			/* we're going out of recovery mode so we'll मुक्त
			 * the IRQ allocated specअगरically क्रम recovery mode
			 * and restore the पूर्णांकerrupt scheme
			 */
			मुक्त_irq(pf->pdev->irq, pf);
			i40e_clear_पूर्णांकerrupt_scheme(pf);
			अगर (i40e_restore_पूर्णांकerrupt_scheme(pf))
				जाओ end_unlock;
		पूर्ण

		/* tell the firmware that we're starting */
		i40e_send_version(pf);

		/* bail out in हाल recovery mode was detected, as there is
		 * no need क्रम further configuration.
		 */
		जाओ end_unlock;
	पूर्ण

	i40e_clear_pxe_mode(hw);
	ret = i40e_get_capabilities(pf, i40e_aqc_opc_list_func_capabilities);
	अगर (ret)
		जाओ end_core_reset;

	ret = i40e_init_lan_hmc(hw, hw->func_caps.num_tx_qp,
				hw->func_caps.num_rx_qp, 0, 0);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev, "init_lan_hmc failed: %d\n", ret);
		जाओ end_core_reset;
	पूर्ण
	ret = i40e_configure_lan_hmc(hw, I40E_HMC_MODEL_सूचीECT_ONLY);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev, "configure_lan_hmc failed: %d\n", ret);
		जाओ end_core_reset;
	पूर्ण

#अगर_घोषित CONFIG_I40E_DCB
	/* Enable FW to ग_लिखो a शेष DCB config on link-up
	 * unless I40E_FLAG_TC_MQPRIO was enabled or DCB
	 * is not supported with new link speed
	 */
	अगर (pf->flags & I40E_FLAG_TC_MQPRIO) अणु
		i40e_aq_set_dcb_parameters(hw, false, शून्य);
	पूर्ण अन्यथा अणु
		अगर (I40E_IS_X710TL_DEVICE(hw->device_id) &&
		    (hw->phy.link_info.link_speed &
		     (I40E_LINK_SPEED_2_5GB | I40E_LINK_SPEED_5GB))) अणु
			i40e_aq_set_dcb_parameters(hw, false, शून्य);
			dev_warn(&pf->pdev->dev,
				 "DCB is not supported for X710-T*L 2.5/5G speeds\n");
			pf->flags &= ~I40E_FLAG_DCB_CAPABLE;
		पूर्ण अन्यथा अणु
			i40e_aq_set_dcb_parameters(hw, true, शून्य);
			ret = i40e_init_pf_dcb(pf);
			अगर (ret) अणु
				dev_info(&pf->pdev->dev, "DCB init failed %d, disabled\n",
					 ret);
				pf->flags &= ~I40E_FLAG_DCB_CAPABLE;
				/* Continue without DCB enabled */
			पूर्ण
		पूर्ण
	पूर्ण

#पूर्ण_अगर /* CONFIG_I40E_DCB */
	अगर (!lock_acquired)
		rtnl_lock();
	ret = i40e_setup_pf_चयन(pf, reinit);
	अगर (ret)
		जाओ end_unlock;

	/* The driver only wants link up/करोwn and module qualअगरication
	 * reports from firmware.  Note the negative logic.
	 */
	ret = i40e_aq_set_phy_पूर्णांक_mask(&pf->hw,
				       ~(I40E_AQ_EVENT_LINK_UPDOWN |
					 I40E_AQ_EVENT_MEDIA_NA |
					 I40E_AQ_EVENT_MODULE_QUAL_FAIL), शून्य);
	अगर (ret)
		dev_info(&pf->pdev->dev, "set phy mask fail, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));

	/* Rebuild the VSIs and VEBs that existed beक्रमe reset.
	 * They are still in our local चयन element arrays, so only
	 * need to rebuild the चयन model in the HW.
	 *
	 * If there were VEBs but the reस्थिरitution failed, we'll try
	 * to recover minimal use by getting the basic PF VSI working.
	 */
	अगर (vsi->uplink_seid != pf->mac_seid) अणु
		dev_dbg(&pf->pdev->dev, "attempting to rebuild switch\n");
		/* find the one VEB connected to the MAC, and find orphans */
		क्रम (v = 0; v < I40E_MAX_VEB; v++) अणु
			अगर (!pf->veb[v])
				जारी;

			अगर (pf->veb[v]->uplink_seid == pf->mac_seid ||
			    pf->veb[v]->uplink_seid == 0) अणु
				ret = i40e_reस्थिरitute_veb(pf->veb[v]);

				अगर (!ret)
					जारी;

				/* If Main VEB failed, we're in deep करोoकरोo,
				 * so give up rebuilding the चयन and set up
				 * क्रम minimal rebuild of PF VSI.
				 * If orphan failed, we'll report the error
				 * but try to keep going.
				 */
				अगर (pf->veb[v]->uplink_seid == pf->mac_seid) अणु
					dev_info(&pf->pdev->dev,
						 "rebuild of switch failed: %d, will try to set up simple PF connection\n",
						 ret);
					vsi->uplink_seid = pf->mac_seid;
					अवरोध;
				पूर्ण अन्यथा अगर (pf->veb[v]->uplink_seid == 0) अणु
					dev_info(&pf->pdev->dev,
						 "rebuild of orphan VEB failed: %d\n",
						 ret);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (vsi->uplink_seid == pf->mac_seid) अणु
		dev_dbg(&pf->pdev->dev, "attempting to rebuild PF VSI\n");
		/* no VEB, so rebuild only the Main VSI */
		ret = i40e_add_vsi(vsi);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "rebuild of Main VSI failed: %d\n", ret);
			जाओ end_unlock;
		पूर्ण
	पूर्ण

	अगर (vsi->mqprio_qopt.max_rate[0]) अणु
		u64 max_tx_rate = vsi->mqprio_qopt.max_rate[0];
		u64 credits = 0;

		करो_भाग(max_tx_rate, I40E_BW_MBPS_DIVISOR);
		ret = i40e_set_bw_limit(vsi, vsi->seid, max_tx_rate);
		अगर (ret)
			जाओ end_unlock;

		credits = max_tx_rate;
		करो_भाग(credits, I40E_BW_CREDIT_DIVISOR);
		dev_dbg(&vsi->back->pdev->dev,
			"Set tx rate of %llu Mbps (count of 50Mbps %llu) for vsi->seid %u\n",
			max_tx_rate,
			credits,
			vsi->seid);
	पूर्ण

	ret = i40e_rebuild_cloud_filters(vsi, vsi->seid);
	अगर (ret)
		जाओ end_unlock;

	/* PF Main VSI is rebuild by now, go ahead and rebuild channel VSIs
	 * क्रम this मुख्य VSI अगर they exist
	 */
	ret = i40e_rebuild_channels(vsi);
	अगर (ret)
		जाओ end_unlock;

	/* Reconfigure hardware क्रम allowing smaller MSS in the हाल
	 * of TSO, so that we aव्योम the MDD being fired and causing
	 * a reset in the हाल of small MSS+TSO.
	 */
#घोषणा I40E_REG_MSS          0x000E64DC
#घोषणा I40E_REG_MSS_MIN_MASK 0x3FF0000
#घोषणा I40E_64BYTE_MSS       0x400000
	val = rd32(hw, I40E_REG_MSS);
	अगर ((val & I40E_REG_MSS_MIN_MASK) > I40E_64BYTE_MSS) अणु
		val &= ~I40E_REG_MSS_MIN_MASK;
		val |= I40E_64BYTE_MSS;
		wr32(hw, I40E_REG_MSS, val);
	पूर्ण

	अगर (pf->hw_features & I40E_HW_RESTART_AUTONEG) अणु
		msleep(75);
		ret = i40e_aq_set_link_restart_an(&pf->hw, true, शून्य);
		अगर (ret)
			dev_info(&pf->pdev->dev, "link restart failed, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
	पूर्ण
	/* reinit the misc पूर्णांकerrupt */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
		ret = i40e_setup_misc_vector(pf);

	/* Add a filter to drop all Flow control frames from any VSI from being
	 * transmitted. By करोing so we stop a malicious VF from sending out
	 * PAUSE or PFC frames and potentially controlling traffic क्रम other
	 * PF/VF VSIs.
	 * The FW can still send Flow control frames अगर enabled.
	 */
	i40e_add_filter_to_drop_tx_flow_control_frames(&pf->hw,
						       pf->मुख्य_vsi_seid);

	/* restart the VSIs that were rebuilt and running beक्रमe the reset */
	i40e_pf_unquiesce_all_vsi(pf);

	/* Release the RTNL lock beक्रमe we start resetting VFs */
	अगर (!lock_acquired)
		rtnl_unlock();

	/* Restore promiscuous settings */
	ret = i40e_set_promiscuous(pf, pf->cur_promisc);
	अगर (ret)
		dev_warn(&pf->pdev->dev,
			 "Failed to restore promiscuous setting: %s, err %s aq_err %s\n",
			 pf->cur_promisc ? "on" : "off",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));

	i40e_reset_all_vfs(pf, true);

	/* tell the firmware that we're starting */
	i40e_send_version(pf);

	/* We've already released the lock, so don't करो it again */
	जाओ end_core_reset;

end_unlock:
	अगर (!lock_acquired)
		rtnl_unlock();
end_core_reset:
	clear_bit(__I40E_RESET_FAILED, pf->state);
clear_recovery:
	clear_bit(__I40E_RESET_RECOVERY_PENDING, pf->state);
	clear_bit(__I40E_TIMEOUT_RECOVERY_PENDING, pf->state);
पूर्ण

/**
 * i40e_reset_and_rebuild - reset and rebuild using a saved config
 * @pf: board निजी काष्ठाure
 * @reinit: अगर the Main VSI needs to re-initialized.
 * @lock_acquired: indicates whether or not the lock has been acquired
 * beक्रमe this function was called.
 **/
अटल व्योम i40e_reset_and_rebuild(काष्ठा i40e_pf *pf, bool reinit,
				   bool lock_acquired)
अणु
	पूर्णांक ret;
	/* Now we रुको क्रम GRST to settle out.
	 * We करोn't have to delete the VEBs or VSIs from the hw चयन
	 * because the reset will make them disappear.
	 */
	ret = i40e_reset(pf);
	अगर (!ret)
		i40e_rebuild(pf, reinit, lock_acquired);
पूर्ण

/**
 * i40e_handle_reset_warning - prep क्रम the PF to reset, reset and rebuild
 * @pf: board निजी काष्ठाure
 *
 * Close up the VFs and other things in prep क्रम a Core Reset,
 * then get पढ़ोy to rebuild the world.
 * @lock_acquired: indicates whether or not the lock has been acquired
 * beक्रमe this function was called.
 **/
अटल व्योम i40e_handle_reset_warning(काष्ठा i40e_pf *pf, bool lock_acquired)
अणु
	i40e_prep_क्रम_reset(pf);
	i40e_reset_and_rebuild(pf, false, lock_acquired);
पूर्ण

/**
 * i40e_handle_mdd_event
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * Called from the MDD irq handler to identअगरy possibly malicious vfs
 **/
अटल व्योम i40e_handle_mdd_event(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	bool mdd_detected = false;
	काष्ठा i40e_vf *vf;
	u32 reg;
	पूर्णांक i;

	अगर (!test_bit(__I40E_MDD_EVENT_PENDING, pf->state))
		वापस;

	/* find what triggered the MDD event */
	reg = rd32(hw, I40E_GL_MDET_TX);
	अगर (reg & I40E_GL_MDET_TX_VALID_MASK) अणु
		u8 pf_num = (reg & I40E_GL_MDET_TX_PF_NUM_MASK) >>
				I40E_GL_MDET_TX_PF_NUM_SHIFT;
		u16 vf_num = (reg & I40E_GL_MDET_TX_VF_NUM_MASK) >>
				I40E_GL_MDET_TX_VF_NUM_SHIFT;
		u8 event = (reg & I40E_GL_MDET_TX_EVENT_MASK) >>
				I40E_GL_MDET_TX_EVENT_SHIFT;
		u16 queue = ((reg & I40E_GL_MDET_TX_QUEUE_MASK) >>
				I40E_GL_MDET_TX_QUEUE_SHIFT) -
				pf->hw.func_caps.base_queue;
		अगर (netअगर_msg_tx_err(pf))
			dev_info(&pf->pdev->dev, "Malicious Driver Detection event 0x%02x on TX queue %d PF number 0x%02x VF number 0x%02x\n",
				 event, queue, pf_num, vf_num);
		wr32(hw, I40E_GL_MDET_TX, 0xffffffff);
		mdd_detected = true;
	पूर्ण
	reg = rd32(hw, I40E_GL_MDET_RX);
	अगर (reg & I40E_GL_MDET_RX_VALID_MASK) अणु
		u8 func = (reg & I40E_GL_MDET_RX_FUNCTION_MASK) >>
				I40E_GL_MDET_RX_FUNCTION_SHIFT;
		u8 event = (reg & I40E_GL_MDET_RX_EVENT_MASK) >>
				I40E_GL_MDET_RX_EVENT_SHIFT;
		u16 queue = ((reg & I40E_GL_MDET_RX_QUEUE_MASK) >>
				I40E_GL_MDET_RX_QUEUE_SHIFT) -
				pf->hw.func_caps.base_queue;
		अगर (netअगर_msg_rx_err(pf))
			dev_info(&pf->pdev->dev, "Malicious Driver Detection event 0x%02x on RX queue %d of function 0x%02x\n",
				 event, queue, func);
		wr32(hw, I40E_GL_MDET_RX, 0xffffffff);
		mdd_detected = true;
	पूर्ण

	अगर (mdd_detected) अणु
		reg = rd32(hw, I40E_PF_MDET_TX);
		अगर (reg & I40E_PF_MDET_TX_VALID_MASK) अणु
			wr32(hw, I40E_PF_MDET_TX, 0xFFFF);
			dev_dbg(&pf->pdev->dev, "TX driver issue detected on PF\n");
		पूर्ण
		reg = rd32(hw, I40E_PF_MDET_RX);
		अगर (reg & I40E_PF_MDET_RX_VALID_MASK) अणु
			wr32(hw, I40E_PF_MDET_RX, 0xFFFF);
			dev_dbg(&pf->pdev->dev, "RX driver issue detected on PF\n");
		पूर्ण
	पूर्ण

	/* see अगर one of the VFs needs its hand slapped */
	क्रम (i = 0; i < pf->num_alloc_vfs && mdd_detected; i++) अणु
		vf = &(pf->vf[i]);
		reg = rd32(hw, I40E_VP_MDET_TX(i));
		अगर (reg & I40E_VP_MDET_TX_VALID_MASK) अणु
			wr32(hw, I40E_VP_MDET_TX(i), 0xFFFF);
			vf->num_mdd_events++;
			dev_info(&pf->pdev->dev, "TX driver issue detected on VF %d\n",
				 i);
			dev_info(&pf->pdev->dev,
				 "Use PF Control I/F to re-enable the VF\n");
			set_bit(I40E_VF_STATE_DISABLED, &vf->vf_states);
		पूर्ण

		reg = rd32(hw, I40E_VP_MDET_RX(i));
		अगर (reg & I40E_VP_MDET_RX_VALID_MASK) अणु
			wr32(hw, I40E_VP_MDET_RX(i), 0xFFFF);
			vf->num_mdd_events++;
			dev_info(&pf->pdev->dev, "RX driver issue detected on VF %d\n",
				 i);
			dev_info(&pf->pdev->dev,
				 "Use PF Control I/F to re-enable the VF\n");
			set_bit(I40E_VF_STATE_DISABLED, &vf->vf_states);
		पूर्ण
	पूर्ण

	/* re-enable mdd पूर्णांकerrupt cause */
	clear_bit(__I40E_MDD_EVENT_PENDING, pf->state);
	reg = rd32(hw, I40E_PFINT_ICR0_ENA);
	reg |=  I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, reg);
	i40e_flush(hw);
पूर्ण

/**
 * i40e_service_task - Run the driver's async subtasks
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 **/
अटल व्योम i40e_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा i40e_pf *pf = container_of(work,
					  काष्ठा i40e_pf,
					  service_task);
	अचिन्हित दीर्घ start_समय = jअगरfies;

	/* करोn't bother with service tasks अगर a reset is in progress */
	अगर (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
	    test_bit(__I40E_SUSPENDED, pf->state))
		वापस;

	अगर (test_and_set_bit(__I40E_SERVICE_SCHED, pf->state))
		वापस;

	अगर (!test_bit(__I40E_RECOVERY_MODE, pf->state)) अणु
		i40e_detect_recover_hung(pf->vsi[pf->lan_vsi]);
		i40e_sync_filters_subtask(pf);
		i40e_reset_subtask(pf);
		i40e_handle_mdd_event(pf);
		i40e_vc_process_vflr_event(pf);
		i40e_watchकरोg_subtask(pf);
		i40e_fdir_reinit_subtask(pf);
		अगर (test_and_clear_bit(__I40E_CLIENT_RESET, pf->state)) अणु
			/* Client subtask will reखोलो next समय through. */
			i40e_notअगरy_client_of_netdev_बंद(pf->vsi[pf->lan_vsi],
							   true);
		पूर्ण अन्यथा अणु
			i40e_client_subtask(pf);
			अगर (test_and_clear_bit(__I40E_CLIENT_L2_CHANGE,
					       pf->state))
				i40e_notअगरy_client_of_l2_param_changes(
								pf->vsi[pf->lan_vsi]);
		पूर्ण
		i40e_sync_filters_subtask(pf);
	पूर्ण अन्यथा अणु
		i40e_reset_subtask(pf);
	पूर्ण

	i40e_clean_adminq_subtask(pf);

	/* flush memory to make sure state is correct beक्रमe next watchकरोg */
	smp_mb__beक्रमe_atomic();
	clear_bit(__I40E_SERVICE_SCHED, pf->state);

	/* If the tasks have taken दीर्घer than one समयr cycle or there
	 * is more work to be करोne, reschedule the service task now
	 * rather than रुको क्रम the समयr to tick again.
	 */
	अगर (समय_after(jअगरfies, (start_समय + pf->service_समयr_period)) ||
	    test_bit(__I40E_ADMINQ_EVENT_PENDING, pf->state)		 ||
	    test_bit(__I40E_MDD_EVENT_PENDING, pf->state)		 ||
	    test_bit(__I40E_VFLR_EVENT_PENDING, pf->state))
		i40e_service_event_schedule(pf);
पूर्ण

/**
 * i40e_service_समयr - समयr callback
 * @t: समयr list poपूर्णांकer
 **/
अटल व्योम i40e_service_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा i40e_pf *pf = from_समयr(pf, t, service_समयr);

	mod_समयr(&pf->service_समयr,
		  round_jअगरfies(jअगरfies + pf->service_समयr_period));
	i40e_service_event_schedule(pf);
पूर्ण

/**
 * i40e_set_num_rings_in_vsi - Determine number of rings in the VSI
 * @vsi: the VSI being configured
 **/
अटल पूर्णांक i40e_set_num_rings_in_vsi(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;

	चयन (vsi->type) अणु
	हाल I40E_VSI_MAIN:
		vsi->alloc_queue_pairs = pf->num_lan_qps;
		अगर (!vsi->num_tx_desc)
			vsi->num_tx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		अगर (!vsi->num_rx_desc)
			vsi->num_rx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
			vsi->num_q_vectors = pf->num_lan_msix;
		अन्यथा
			vsi->num_q_vectors = 1;

		अवरोध;

	हाल I40E_VSI_Fसूची:
		vsi->alloc_queue_pairs = 1;
		vsi->num_tx_desc = ALIGN(I40E_Fसूची_RING_COUNT,
					 I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_rx_desc = ALIGN(I40E_Fसूची_RING_COUNT,
					 I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_q_vectors = pf->num_fdsb_msix;
		अवरोध;

	हाल I40E_VSI_VMDQ2:
		vsi->alloc_queue_pairs = pf->num_vmdq_qps;
		अगर (!vsi->num_tx_desc)
			vsi->num_tx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		अगर (!vsi->num_rx_desc)
			vsi->num_rx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_q_vectors = pf->num_vmdq_msix;
		अवरोध;

	हाल I40E_VSI_SRIOV:
		vsi->alloc_queue_pairs = pf->num_vf_qps;
		अगर (!vsi->num_tx_desc)
			vsi->num_tx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		अगर (!vsi->num_rx_desc)
			vsi->num_rx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		अवरोध;

	शेष:
		WARN_ON(1);
		वापस -ENODATA;
	पूर्ण

	अगर (is_kdump_kernel()) अणु
		vsi->num_tx_desc = I40E_MIN_NUM_DESCRIPTORS;
		vsi->num_rx_desc = I40E_MIN_NUM_DESCRIPTORS;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vsi_alloc_arrays - Allocate queue and vector poपूर्णांकer arrays क्रम the vsi
 * @vsi: VSI poपूर्णांकer
 * @alloc_qvectors: a bool to specअगरy अगर q_vectors need to be allocated.
 *
 * On error: वापसs error code (negative)
 * On success: वापसs 0
 **/
अटल पूर्णांक i40e_vsi_alloc_arrays(काष्ठा i40e_vsi *vsi, bool alloc_qvectors)
अणु
	काष्ठा i40e_ring **next_rings;
	पूर्णांक size;
	पूर्णांक ret = 0;

	/* allocate memory क्रम both Tx, XDP Tx and Rx ring poपूर्णांकers */
	size = माप(काष्ठा i40e_ring *) * vsi->alloc_queue_pairs *
	       (i40e_enabled_xdp_vsi(vsi) ? 3 : 2);
	vsi->tx_rings = kzalloc(size, GFP_KERNEL);
	अगर (!vsi->tx_rings)
		वापस -ENOMEM;
	next_rings = vsi->tx_rings + vsi->alloc_queue_pairs;
	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		vsi->xdp_rings = next_rings;
		next_rings += vsi->alloc_queue_pairs;
	पूर्ण
	vsi->rx_rings = next_rings;

	अगर (alloc_qvectors) अणु
		/* allocate memory क्रम q_vector poपूर्णांकers */
		size = माप(काष्ठा i40e_q_vector *) * vsi->num_q_vectors;
		vsi->q_vectors = kzalloc(size, GFP_KERNEL);
		अगर (!vsi->q_vectors) अणु
			ret = -ENOMEM;
			जाओ err_vectors;
		पूर्ण
	पूर्ण
	वापस ret;

err_vectors:
	kमुक्त(vsi->tx_rings);
	वापस ret;
पूर्ण

/**
 * i40e_vsi_mem_alloc - Allocates the next available काष्ठा vsi in the PF
 * @pf: board निजी काष्ठाure
 * @type: type of VSI
 *
 * On error: वापसs error code (negative)
 * On success: वापसs vsi index in PF (positive)
 **/
अटल पूर्णांक i40e_vsi_mem_alloc(काष्ठा i40e_pf *pf, क्रमागत i40e_vsi_type type)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा i40e_vsi *vsi;
	पूर्णांक vsi_idx;
	पूर्णांक i;

	/* Need to protect the allocation of the VSIs at the PF level */
	mutex_lock(&pf->चयन_mutex);

	/* VSI list may be fragmented अगर VSI creation/deकाष्ठाion has
	 * been happening.  We can afक्रमd to करो a quick scan to look
	 * क्रम any मुक्त VSIs in the list.
	 *
	 * find next empty vsi slot, looping back around अगर necessary
	 */
	i = pf->next_vsi;
	जबतक (i < pf->num_alloc_vsi && pf->vsi[i])
		i++;
	अगर (i >= pf->num_alloc_vsi) अणु
		i = 0;
		जबतक (i < pf->next_vsi && pf->vsi[i])
			i++;
	पूर्ण

	अगर (i < pf->num_alloc_vsi && !pf->vsi[i]) अणु
		vsi_idx = i;             /* Found one! */
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
		जाओ unlock_pf;  /* out of VSI slots! */
	पूर्ण
	pf->next_vsi = ++i;

	vsi = kzalloc(माप(*vsi), GFP_KERNEL);
	अगर (!vsi) अणु
		ret = -ENOMEM;
		जाओ unlock_pf;
	पूर्ण
	vsi->type = type;
	vsi->back = pf;
	set_bit(__I40E_VSI_DOWN, vsi->state);
	vsi->flags = 0;
	vsi->idx = vsi_idx;
	vsi->पूर्णांक_rate_limit = 0;
	vsi->rss_table_size = (vsi->type == I40E_VSI_MAIN) ?
				pf->rss_table_size : 64;
	vsi->netdev_रेजिस्टरed = false;
	vsi->work_limit = I40E_DEFAULT_IRQ_WORK;
	hash_init(vsi->mac_filter_hash);
	vsi->irqs_पढ़ोy = false;

	अगर (type == I40E_VSI_MAIN) अणु
		vsi->af_xdp_zc_qps = biपंचांगap_zalloc(pf->num_lan_qps, GFP_KERNEL);
		अगर (!vsi->af_xdp_zc_qps)
			जाओ err_rings;
	पूर्ण

	ret = i40e_set_num_rings_in_vsi(vsi);
	अगर (ret)
		जाओ err_rings;

	ret = i40e_vsi_alloc_arrays(vsi, true);
	अगर (ret)
		जाओ err_rings;

	/* Setup शेष MSIX irq handler क्रम VSI */
	i40e_vsi_setup_irqhandler(vsi, i40e_msix_clean_rings);

	/* Initialize VSI lock */
	spin_lock_init(&vsi->mac_filter_hash_lock);
	pf->vsi[vsi_idx] = vsi;
	ret = vsi_idx;
	जाओ unlock_pf;

err_rings:
	biपंचांगap_मुक्त(vsi->af_xdp_zc_qps);
	pf->next_vsi = i - 1;
	kमुक्त(vsi);
unlock_pf:
	mutex_unlock(&pf->चयन_mutex);
	वापस ret;
पूर्ण

/**
 * i40e_vsi_मुक्त_arrays - Free queue and vector poपूर्णांकer arrays क्रम the VSI
 * @vsi: VSI poपूर्णांकer
 * @मुक्त_qvectors: a bool to specअगरy अगर q_vectors need to be मुक्तd.
 *
 * On error: वापसs error code (negative)
 * On success: वापसs 0
 **/
अटल व्योम i40e_vsi_मुक्त_arrays(काष्ठा i40e_vsi *vsi, bool मुक्त_qvectors)
अणु
	/* मुक्त the ring and vector containers */
	अगर (मुक्त_qvectors) अणु
		kमुक्त(vsi->q_vectors);
		vsi->q_vectors = शून्य;
	पूर्ण
	kमुक्त(vsi->tx_rings);
	vsi->tx_rings = शून्य;
	vsi->rx_rings = शून्य;
	vsi->xdp_rings = शून्य;
पूर्ण

/**
 * i40e_clear_rss_config_user - clear the user configured RSS hash keys
 * and lookup table
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 */
अटल व्योम i40e_clear_rss_config_user(काष्ठा i40e_vsi *vsi)
अणु
	अगर (!vsi)
		वापस;

	kमुक्त(vsi->rss_hkey_user);
	vsi->rss_hkey_user = शून्य;

	kमुक्त(vsi->rss_lut_user);
	vsi->rss_lut_user = शून्य;
पूर्ण

/**
 * i40e_vsi_clear - Deallocate the VSI provided
 * @vsi: the VSI being un-configured
 **/
अटल पूर्णांक i40e_vsi_clear(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf;

	अगर (!vsi)
		वापस 0;

	अगर (!vsi->back)
		जाओ मुक्त_vsi;
	pf = vsi->back;

	mutex_lock(&pf->चयन_mutex);
	अगर (!pf->vsi[vsi->idx]) अणु
		dev_err(&pf->pdev->dev, "pf->vsi[%d] is NULL, just free vsi[%d](type %d)\n",
			vsi->idx, vsi->idx, vsi->type);
		जाओ unlock_vsi;
	पूर्ण

	अगर (pf->vsi[vsi->idx] != vsi) अणु
		dev_err(&pf->pdev->dev,
			"pf->vsi[%d](type %d) != vsi[%d](type %d): no free!\n",
			pf->vsi[vsi->idx]->idx,
			pf->vsi[vsi->idx]->type,
			vsi->idx, vsi->type);
		जाओ unlock_vsi;
	पूर्ण

	/* updates the PF क्रम this cleared vsi */
	i40e_put_lump(pf->qp_pile, vsi->base_queue, vsi->idx);
	i40e_put_lump(pf->irq_pile, vsi->base_vector, vsi->idx);

	biपंचांगap_मुक्त(vsi->af_xdp_zc_qps);
	i40e_vsi_मुक्त_arrays(vsi, true);
	i40e_clear_rss_config_user(vsi);

	pf->vsi[vsi->idx] = शून्य;
	अगर (vsi->idx < pf->next_vsi)
		pf->next_vsi = vsi->idx;

unlock_vsi:
	mutex_unlock(&pf->चयन_mutex);
मुक्त_vsi:
	kमुक्त(vsi);

	वापस 0;
पूर्ण

/**
 * i40e_vsi_clear_rings - Deallocates the Rx and Tx rings क्रम the provided VSI
 * @vsi: the VSI being cleaned
 **/
अटल व्योम i40e_vsi_clear_rings(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक i;

	अगर (vsi->tx_rings && vsi->tx_rings[0]) अणु
		क्रम (i = 0; i < vsi->alloc_queue_pairs; i++) अणु
			kमुक्त_rcu(vsi->tx_rings[i], rcu);
			WRITE_ONCE(vsi->tx_rings[i], शून्य);
			WRITE_ONCE(vsi->rx_rings[i], शून्य);
			अगर (vsi->xdp_rings)
				WRITE_ONCE(vsi->xdp_rings[i], शून्य);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_alloc_rings - Allocates the Rx and Tx rings क्रम the provided VSI
 * @vsi: the VSI being configured
 **/
अटल पूर्णांक i40e_alloc_rings(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक i, qpv = i40e_enabled_xdp_vsi(vsi) ? 3 : 2;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_ring *ring;

	/* Set basic values in the rings to be used later during खोलो() */
	क्रम (i = 0; i < vsi->alloc_queue_pairs; i++) अणु
		/* allocate space क्रम both Tx and Rx in one shot */
		ring = kसुस्मृति(qpv, माप(काष्ठा i40e_ring), GFP_KERNEL);
		अगर (!ring)
			जाओ err_out;

		ring->queue_index = i;
		ring->reg_idx = vsi->base_queue + i;
		ring->ring_active = false;
		ring->vsi = vsi;
		ring->netdev = vsi->netdev;
		ring->dev = &pf->pdev->dev;
		ring->count = vsi->num_tx_desc;
		ring->size = 0;
		ring->dcb_tc = 0;
		अगर (vsi->back->hw_features & I40E_HW_WB_ON_ITR_CAPABLE)
			ring->flags = I40E_TXR_FLAGS_WB_ON_ITR;
		ring->itr_setting = pf->tx_itr_शेष;
		WRITE_ONCE(vsi->tx_rings[i], ring++);

		अगर (!i40e_enabled_xdp_vsi(vsi))
			जाओ setup_rx;

		ring->queue_index = vsi->alloc_queue_pairs + i;
		ring->reg_idx = vsi->base_queue + ring->queue_index;
		ring->ring_active = false;
		ring->vsi = vsi;
		ring->netdev = शून्य;
		ring->dev = &pf->pdev->dev;
		ring->count = vsi->num_tx_desc;
		ring->size = 0;
		ring->dcb_tc = 0;
		अगर (vsi->back->hw_features & I40E_HW_WB_ON_ITR_CAPABLE)
			ring->flags = I40E_TXR_FLAGS_WB_ON_ITR;
		set_ring_xdp(ring);
		ring->itr_setting = pf->tx_itr_शेष;
		WRITE_ONCE(vsi->xdp_rings[i], ring++);

setup_rx:
		ring->queue_index = i;
		ring->reg_idx = vsi->base_queue + i;
		ring->ring_active = false;
		ring->vsi = vsi;
		ring->netdev = vsi->netdev;
		ring->dev = &pf->pdev->dev;
		ring->count = vsi->num_rx_desc;
		ring->size = 0;
		ring->dcb_tc = 0;
		ring->itr_setting = pf->rx_itr_शेष;
		WRITE_ONCE(vsi->rx_rings[i], ring);
	पूर्ण

	वापस 0;

err_out:
	i40e_vsi_clear_rings(vsi);
	वापस -ENOMEM;
पूर्ण

/**
 * i40e_reserve_msix_vectors - Reserve MSI-X vectors in the kernel
 * @pf: board निजी काष्ठाure
 * @vectors: the number of MSI-X vectors to request
 *
 * Returns the number of vectors reserved, or error
 **/
अटल पूर्णांक i40e_reserve_msix_vectors(काष्ठा i40e_pf *pf, पूर्णांक vectors)
अणु
	vectors = pci_enable_msix_range(pf->pdev, pf->msix_entries,
					I40E_MIN_MSIX, vectors);
	अगर (vectors < 0) अणु
		dev_info(&pf->pdev->dev,
			 "MSI-X vector reservation failed: %d\n", vectors);
		vectors = 0;
	पूर्ण

	वापस vectors;
पूर्ण

/**
 * i40e_init_msix - Setup the MSIX capability
 * @pf: board निजी काष्ठाure
 *
 * Work with the OS to set up the MSIX vectors needed.
 *
 * Returns the number of vectors reserved or negative on failure
 **/
अटल पूर्णांक i40e_init_msix(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक cpus, extra_vectors;
	पूर्णांक vectors_left;
	पूर्णांक v_budget, i;
	पूर्णांक v_actual;
	पूर्णांक iwarp_requested = 0;

	अगर (!(pf->flags & I40E_FLAG_MSIX_ENABLED))
		वापस -ENODEV;

	/* The number of vectors we'll request will be comprised of:
	 *   - Add 1 क्रम "other" cause क्रम Admin Queue events, etc.
	 *   - The number of LAN queue pairs
	 *	- Queues being used क्रम RSS.
	 *		We करोn't need as many as max_rss_size vectors.
	 *		use rss_size instead in the calculation since that
	 *		is governed by number of cpus in the प्रणाली.
	 *	- assumes symmetric Tx/Rx pairing
	 *   - The number of VMDq pairs
	 *   - The CPU count within the NUMA node अगर iWARP is enabled
	 * Once we count this up, try the request.
	 *
	 * If we can't get what we want, we'll simplअगरy to nearly nothing
	 * and try again.  If that still fails, we punt.
	 */
	vectors_left = hw->func_caps.num_msix_vectors;
	v_budget = 0;

	/* reserve one vector क्रम miscellaneous handler */
	अगर (vectors_left) अणु
		v_budget++;
		vectors_left--;
	पूर्ण

	/* reserve some vectors क्रम the मुख्य PF traffic queues. Initially we
	 * only reserve at most 50% of the available vectors, in the हाल that
	 * the number of online CPUs is large. This ensures that we can enable
	 * extra features as well. Once we've enabled the other features, we
	 * will use any reमुख्यing vectors to reach as बंद as we can to the
	 * number of online CPUs.
	 */
	cpus = num_online_cpus();
	pf->num_lan_msix = min_t(पूर्णांक, cpus, vectors_left / 2);
	vectors_left -= pf->num_lan_msix;

	/* reserve one vector क्रम sideband flow director */
	अगर (pf->flags & I40E_FLAG_FD_SB_ENABLED) अणु
		अगर (vectors_left) अणु
			pf->num_fdsb_msix = 1;
			v_budget++;
			vectors_left--;
		पूर्ण अन्यथा अणु
			pf->num_fdsb_msix = 0;
		पूर्ण
	पूर्ण

	/* can we reserve enough क्रम iWARP? */
	अगर (pf->flags & I40E_FLAG_IWARP_ENABLED) अणु
		iwarp_requested = pf->num_iwarp_msix;

		अगर (!vectors_left)
			pf->num_iwarp_msix = 0;
		अन्यथा अगर (vectors_left < pf->num_iwarp_msix)
			pf->num_iwarp_msix = 1;
		v_budget += pf->num_iwarp_msix;
		vectors_left -= pf->num_iwarp_msix;
	पूर्ण

	/* any vectors left over go क्रम VMDq support */
	अगर (pf->flags & I40E_FLAG_VMDQ_ENABLED) अणु
		अगर (!vectors_left) अणु
			pf->num_vmdq_msix = 0;
			pf->num_vmdq_qps = 0;
		पूर्ण अन्यथा अणु
			पूर्णांक vmdq_vecs_wanted =
				pf->num_vmdq_vsis * pf->num_vmdq_qps;
			पूर्णांक vmdq_vecs =
				min_t(पूर्णांक, vectors_left, vmdq_vecs_wanted);

			/* अगर we're short on vectors for what's desired, we limit
			 * the queues per vmdq.  If this is still more than are
			 * available, the user will need to change the number of
			 * queues/vectors used by the PF later with the ethtool
			 * channels command
			 */
			अगर (vectors_left < vmdq_vecs_wanted) अणु
				pf->num_vmdq_qps = 1;
				vmdq_vecs_wanted = pf->num_vmdq_vsis;
				vmdq_vecs = min_t(पूर्णांक,
						  vectors_left,
						  vmdq_vecs_wanted);
			पूर्ण
			pf->num_vmdq_msix = pf->num_vmdq_qps;

			v_budget += vmdq_vecs;
			vectors_left -= vmdq_vecs;
		पूर्ण
	पूर्ण

	/* On प्रणालीs with a large number of SMP cores, we previously limited
	 * the number of vectors क्रम num_lan_msix to be at most 50% of the
	 * available vectors, to allow क्रम other features. Now, we add back
	 * the reमुख्यing vectors. However, we ensure that the total
	 * num_lan_msix will not exceed num_online_cpus(). To करो this, we
	 * calculate the number of vectors we can add without going over the
	 * cap of CPUs. For प्रणालीs with a small number of CPUs this will be
	 * zero.
	 */
	extra_vectors = min_t(पूर्णांक, cpus - pf->num_lan_msix, vectors_left);
	pf->num_lan_msix += extra_vectors;
	vectors_left -= extra_vectors;

	WARN(vectors_left < 0,
	     "Calculation of remaining vectors underflowed. This is an accounting bug when determining total MSI-X vectors.\n");

	v_budget += pf->num_lan_msix;
	pf->msix_entries = kसुस्मृति(v_budget, माप(काष्ठा msix_entry),
				   GFP_KERNEL);
	अगर (!pf->msix_entries)
		वापस -ENOMEM;

	क्रम (i = 0; i < v_budget; i++)
		pf->msix_entries[i].entry = i;
	v_actual = i40e_reserve_msix_vectors(pf, v_budget);

	अगर (v_actual < I40E_MIN_MSIX) अणु
		pf->flags &= ~I40E_FLAG_MSIX_ENABLED;
		kमुक्त(pf->msix_entries);
		pf->msix_entries = शून्य;
		pci_disable_msix(pf->pdev);
		वापस -ENODEV;

	पूर्ण अन्यथा अगर (v_actual == I40E_MIN_MSIX) अणु
		/* Adjust क्रम minimal MSIX use */
		pf->num_vmdq_vsis = 0;
		pf->num_vmdq_qps = 0;
		pf->num_lan_qps = 1;
		pf->num_lan_msix = 1;

	पूर्ण अन्यथा अगर (v_actual != v_budget) अणु
		/* If we have limited resources, we will start with no vectors
		 * क्रम the special features and then allocate vectors to some
		 * of these features based on the policy and at the end disable
		 * the features that did not get any vectors.
		 */
		पूर्णांक vec;

		dev_info(&pf->pdev->dev,
			 "MSI-X vector limit reached with %d, wanted %d, attempting to redistribute vectors\n",
			 v_actual, v_budget);
		/* reserve the misc vector */
		vec = v_actual - 1;

		/* Scale vector usage करोwn */
		pf->num_vmdq_msix = 1;    /* क्रमce VMDqs to only one vector */
		pf->num_vmdq_vsis = 1;
		pf->num_vmdq_qps = 1;

		/* partition out the reमुख्यing vectors */
		चयन (vec) अणु
		हाल 2:
			pf->num_lan_msix = 1;
			अवरोध;
		हाल 3:
			अगर (pf->flags & I40E_FLAG_IWARP_ENABLED) अणु
				pf->num_lan_msix = 1;
				pf->num_iwarp_msix = 1;
			पूर्ण अन्यथा अणु
				pf->num_lan_msix = 2;
			पूर्ण
			अवरोध;
		शेष:
			अगर (pf->flags & I40E_FLAG_IWARP_ENABLED) अणु
				pf->num_iwarp_msix = min_t(पूर्णांक, (vec / 3),
						 iwarp_requested);
				pf->num_vmdq_vsis = min_t(पूर्णांक, (vec / 3),
						  I40E_DEFAULT_NUM_VMDQ_VSI);
			पूर्ण अन्यथा अणु
				pf->num_vmdq_vsis = min_t(पूर्णांक, (vec / 2),
						  I40E_DEFAULT_NUM_VMDQ_VSI);
			पूर्ण
			अगर (pf->flags & I40E_FLAG_FD_SB_ENABLED) अणु
				pf->num_fdsb_msix = 1;
				vec--;
			पूर्ण
			pf->num_lan_msix = min_t(पूर्णांक,
			       (vec - (pf->num_iwarp_msix + pf->num_vmdq_vsis)),
							      pf->num_lan_msix);
			pf->num_lan_qps = pf->num_lan_msix;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((pf->flags & I40E_FLAG_FD_SB_ENABLED) &&
	    (pf->num_fdsb_msix == 0)) अणु
		dev_info(&pf->pdev->dev, "Sideband Flowdir disabled, not enough MSI-X vectors\n");
		pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
		pf->flags |= I40E_FLAG_FD_SB_INACTIVE;
	पूर्ण
	अगर ((pf->flags & I40E_FLAG_VMDQ_ENABLED) &&
	    (pf->num_vmdq_msix == 0)) अणु
		dev_info(&pf->pdev->dev, "VMDq disabled, not enough MSI-X vectors\n");
		pf->flags &= ~I40E_FLAG_VMDQ_ENABLED;
	पूर्ण

	अगर ((pf->flags & I40E_FLAG_IWARP_ENABLED) &&
	    (pf->num_iwarp_msix == 0)) अणु
		dev_info(&pf->pdev->dev, "IWARP disabled, not enough MSI-X vectors\n");
		pf->flags &= ~I40E_FLAG_IWARP_ENABLED;
	पूर्ण
	i40e_debug(&pf->hw, I40E_DEBUG_INIT,
		   "MSI-X vector distribution: PF %d, VMDq %d, FDSB %d, iWARP %d\n",
		   pf->num_lan_msix,
		   pf->num_vmdq_msix * pf->num_vmdq_vsis,
		   pf->num_fdsb_msix,
		   pf->num_iwarp_msix);

	वापस v_actual;
पूर्ण

/**
 * i40e_vsi_alloc_q_vector - Allocate memory क्रम a single पूर्णांकerrupt vector
 * @vsi: the VSI being configured
 * @v_idx: index of the vector in the vsi काष्ठा
 *
 * We allocate one q_vector.  If allocation fails we वापस -ENOMEM.
 **/
अटल पूर्णांक i40e_vsi_alloc_q_vector(काष्ठा i40e_vsi *vsi, पूर्णांक v_idx)
अणु
	काष्ठा i40e_q_vector *q_vector;

	/* allocate q_vector */
	q_vector = kzalloc(माप(काष्ठा i40e_q_vector), GFP_KERNEL);
	अगर (!q_vector)
		वापस -ENOMEM;

	q_vector->vsi = vsi;
	q_vector->v_idx = v_idx;
	cpumask_copy(&q_vector->affinity_mask, cpu_possible_mask);

	अगर (vsi->netdev)
		netअगर_napi_add(vsi->netdev, &q_vector->napi,
			       i40e_napi_poll, NAPI_POLL_WEIGHT);

	/* tie q_vector and vsi together */
	vsi->q_vectors[v_idx] = q_vector;

	वापस 0;
पूर्ण

/**
 * i40e_vsi_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 * @vsi: the VSI being configured
 *
 * We allocate one q_vector per queue पूर्णांकerrupt.  If allocation fails we
 * वापस -ENOMEM.
 **/
अटल पूर्णांक i40e_vsi_alloc_q_vectors(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक err, v_idx, num_q_vectors;

	/* अगर not MSIX, give the one vector only to the LAN VSI */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
		num_q_vectors = vsi->num_q_vectors;
	अन्यथा अगर (vsi == pf->vsi[pf->lan_vsi])
		num_q_vectors = 1;
	अन्यथा
		वापस -EINVAL;

	क्रम (v_idx = 0; v_idx < num_q_vectors; v_idx++) अणु
		err = i40e_vsi_alloc_q_vector(vsi, v_idx);
		अगर (err)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	जबतक (v_idx--)
		i40e_मुक्त_q_vector(vsi, v_idx);

	वापस err;
पूर्ण

/**
 * i40e_init_पूर्णांकerrupt_scheme - Determine proper पूर्णांकerrupt scheme
 * @pf: board निजी काष्ठाure to initialize
 **/
अटल पूर्णांक i40e_init_पूर्णांकerrupt_scheme(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक vectors = 0;
	sमाप_प्रकार size;

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		vectors = i40e_init_msix(pf);
		अगर (vectors < 0) अणु
			pf->flags &= ~(I40E_FLAG_MSIX_ENABLED	|
				       I40E_FLAG_IWARP_ENABLED	|
				       I40E_FLAG_RSS_ENABLED	|
				       I40E_FLAG_DCB_CAPABLE	|
				       I40E_FLAG_DCB_ENABLED	|
				       I40E_FLAG_SRIOV_ENABLED	|
				       I40E_FLAG_FD_SB_ENABLED	|
				       I40E_FLAG_FD_ATR_ENABLED	|
				       I40E_FLAG_VMDQ_ENABLED);
			pf->flags |= I40E_FLAG_FD_SB_INACTIVE;

			/* rework the queue expectations without MSIX */
			i40e_determine_queue_usage(pf);
		पूर्ण
	पूर्ण

	अगर (!(pf->flags & I40E_FLAG_MSIX_ENABLED) &&
	    (pf->flags & I40E_FLAG_MSI_ENABLED)) अणु
		dev_info(&pf->pdev->dev, "MSI-X not available, trying MSI\n");
		vectors = pci_enable_msi(pf->pdev);
		अगर (vectors < 0) अणु
			dev_info(&pf->pdev->dev, "MSI init failed - %d\n",
				 vectors);
			pf->flags &= ~I40E_FLAG_MSI_ENABLED;
		पूर्ण
		vectors = 1;  /* one MSI or Legacy vector */
	पूर्ण

	अगर (!(pf->flags & (I40E_FLAG_MSIX_ENABLED | I40E_FLAG_MSI_ENABLED)))
		dev_info(&pf->pdev->dev, "MSI-X and MSI not available, falling back to Legacy IRQ\n");

	/* set up vector assignment tracking */
	size = माप(काष्ठा i40e_lump_tracking) + (माप(u16) * vectors);
	pf->irq_pile = kzalloc(size, GFP_KERNEL);
	अगर (!pf->irq_pile)
		वापस -ENOMEM;

	pf->irq_pile->num_entries = vectors;
	pf->irq_pile->search_hपूर्णांक = 0;

	/* track first vector क्रम misc पूर्णांकerrupts, ignore वापस */
	(व्योम)i40e_get_lump(pf, pf->irq_pile, 1, I40E_PILE_VALID_BIT - 1);

	वापस 0;
पूर्ण

/**
 * i40e_restore_पूर्णांकerrupt_scheme - Restore the पूर्णांकerrupt scheme
 * @pf: निजी board data काष्ठाure
 *
 * Restore the पूर्णांकerrupt scheme that was cleared when we suspended the
 * device. This should be called during resume to re-allocate the q_vectors
 * and reacquire IRQs.
 */
अटल पूर्णांक i40e_restore_पूर्णांकerrupt_scheme(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक err, i;

	/* We cleared the MSI and MSI-X flags when disabling the old पूर्णांकerrupt
	 * scheme. We need to re-enabled them here in order to attempt to
	 * re-acquire the MSI or MSI-X vectors
	 */
	pf->flags |= (I40E_FLAG_MSIX_ENABLED | I40E_FLAG_MSI_ENABLED);

	err = i40e_init_पूर्णांकerrupt_scheme(pf);
	अगर (err)
		वापस err;

	/* Now that we've re-acquired IRQs, we need to remap the vectors and
	 * rings together again.
	 */
	क्रम (i = 0; i < pf->num_alloc_vsi; i++) अणु
		अगर (pf->vsi[i]) अणु
			err = i40e_vsi_alloc_q_vectors(pf->vsi[i]);
			अगर (err)
				जाओ err_unwind;
			i40e_vsi_map_rings_to_vectors(pf->vsi[i]);
		पूर्ण
	पूर्ण

	err = i40e_setup_misc_vector(pf);
	अगर (err)
		जाओ err_unwind;

	अगर (pf->flags & I40E_FLAG_IWARP_ENABLED)
		i40e_client_update_msix_info(pf);

	वापस 0;

err_unwind:
	जबतक (i--) अणु
		अगर (pf->vsi[i])
			i40e_vsi_मुक्त_q_vectors(pf->vsi[i]);
	पूर्ण

	वापस err;
पूर्ण

/**
 * i40e_setup_misc_vector_क्रम_recovery_mode - Setup the misc vector to handle
 * non queue events in recovery mode
 * @pf: board निजी काष्ठाure
 *
 * This sets up the handler क्रम MSIX 0 or MSI/legacy, which is used to manage
 * the non-queue पूर्णांकerrupts, e.g. AdminQ and errors in recovery mode.
 * This is handled dअगरferently than in recovery mode since no Tx/Rx resources
 * are being allocated.
 **/
अटल पूर्णांक i40e_setup_misc_vector_क्रम_recovery_mode(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक err;

	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		err = i40e_setup_misc_vector(pf);

		अगर (err) अणु
			dev_info(&pf->pdev->dev,
				 "MSI-X misc vector request failed, error %d\n",
				 err);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 flags = pf->flags & I40E_FLAG_MSI_ENABLED ? 0 : IRQF_SHARED;

		err = request_irq(pf->pdev->irq, i40e_पूर्णांकr, flags,
				  pf->पूर्णांक_name, pf);

		अगर (err) अणु
			dev_info(&pf->pdev->dev,
				 "MSI/legacy misc vector request failed, error %d\n",
				 err);
			वापस err;
		पूर्ण
		i40e_enable_misc_पूर्णांक_causes(pf);
		i40e_irq_dynamic_enable_icr0(pf);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_setup_misc_vector - Setup the misc vector to handle non queue events
 * @pf: board निजी काष्ठाure
 *
 * This sets up the handler क्रम MSIX 0, which is used to manage the
 * non-queue पूर्णांकerrupts, e.g. AdminQ and errors.  This is not used
 * when in MSI or Legacy पूर्णांकerrupt mode.
 **/
अटल पूर्णांक i40e_setup_misc_vector(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक err = 0;

	/* Only request the IRQ once, the first समय through. */
	अगर (!test_and_set_bit(__I40E_MISC_IRQ_REQUESTED, pf->state)) अणु
		err = request_irq(pf->msix_entries[0].vector,
				  i40e_पूर्णांकr, 0, pf->पूर्णांक_name, pf);
		अगर (err) अणु
			clear_bit(__I40E_MISC_IRQ_REQUESTED, pf->state);
			dev_info(&pf->pdev->dev,
				 "request_irq for %s failed: %d\n",
				 pf->पूर्णांक_name, err);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	i40e_enable_misc_पूर्णांक_causes(pf);

	/* associate no queues to the misc vector */
	wr32(hw, I40E_PFINT_LNKLST0, I40E_QUEUE_END_OF_LIST);
	wr32(hw, I40E_PFINT_ITR0(I40E_RX_ITR), I40E_ITR_8K >> 1);

	i40e_flush(hw);

	i40e_irq_dynamic_enable_icr0(pf);

	वापस err;
पूर्ण

/**
 * i40e_get_rss_aq - Get RSS keys and lut by using AQ commands
 * @vsi: Poपूर्णांकer to vsi काष्ठाure
 * @seed: Buffter to store the hash keys
 * @lut: Buffer to store the lookup table entries
 * @lut_size: Size of buffer to store the lookup table entries
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक i40e_get_rss_aq(काष्ठा i40e_vsi *vsi, स्थिर u8 *seed,
			   u8 *lut, u16 lut_size)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक ret = 0;

	अगर (seed) अणु
		ret = i40e_aq_get_rss_key(hw, vsi->id,
			(काष्ठा i40e_aqc_get_set_rss_key_data *)seed);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "Cannot get RSS key, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (lut) अणु
		bool pf_lut = vsi->type == I40E_VSI_MAIN;

		ret = i40e_aq_get_rss_lut(hw, vsi->id, pf_lut, lut, lut_size);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "Cannot get RSS lut, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_config_rss_reg - Configure RSS keys and lut by writing रेजिस्टरs
 * @vsi: Poपूर्णांकer to vsi काष्ठाure
 * @seed: RSS hash seed
 * @lut: Lookup table
 * @lut_size: Lookup table size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_config_rss_reg(काष्ठा i40e_vsi *vsi, स्थिर u8 *seed,
			       स्थिर u8 *lut, u16 lut_size)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 vf_id = vsi->vf_id;
	u8 i;

	/* Fill out hash function seed */
	अगर (seed) अणु
		u32 *seed_dw = (u32 *)seed;

		अगर (vsi->type == I40E_VSI_MAIN) अणु
			क्रम (i = 0; i <= I40E_PFQF_HKEY_MAX_INDEX; i++)
				wr32(hw, I40E_PFQF_HKEY(i), seed_dw[i]);
		पूर्ण अन्यथा अगर (vsi->type == I40E_VSI_SRIOV) अणु
			क्रम (i = 0; i <= I40E_VFQF_HKEY1_MAX_INDEX; i++)
				wr32(hw, I40E_VFQF_HKEY1(i, vf_id), seed_dw[i]);
		पूर्ण अन्यथा अणु
			dev_err(&pf->pdev->dev, "Cannot set RSS seed - invalid VSI type\n");
		पूर्ण
	पूर्ण

	अगर (lut) अणु
		u32 *lut_dw = (u32 *)lut;

		अगर (vsi->type == I40E_VSI_MAIN) अणु
			अगर (lut_size != I40E_HLUT_ARRAY_SIZE)
				वापस -EINVAL;
			क्रम (i = 0; i <= I40E_PFQF_HLUT_MAX_INDEX; i++)
				wr32(hw, I40E_PFQF_HLUT(i), lut_dw[i]);
		पूर्ण अन्यथा अगर (vsi->type == I40E_VSI_SRIOV) अणु
			अगर (lut_size != I40E_VF_HLUT_ARRAY_SIZE)
				वापस -EINVAL;
			क्रम (i = 0; i <= I40E_VFQF_HLUT_MAX_INDEX; i++)
				wr32(hw, I40E_VFQF_HLUT1(i, vf_id), lut_dw[i]);
		पूर्ण अन्यथा अणु
			dev_err(&pf->pdev->dev, "Cannot set RSS LUT - invalid VSI type\n");
		पूर्ण
	पूर्ण
	i40e_flush(hw);

	वापस 0;
पूर्ण

/**
 * i40e_get_rss_reg - Get the RSS keys and lut by पढ़ोing रेजिस्टरs
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 * @seed: Buffer to store the keys
 * @lut: Buffer to store the lookup table entries
 * @lut_size: Size of buffer to store the lookup table entries
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक i40e_get_rss_reg(काष्ठा i40e_vsi *vsi, u8 *seed,
			    u8 *lut, u16 lut_size)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 i;

	अगर (seed) अणु
		u32 *seed_dw = (u32 *)seed;

		क्रम (i = 0; i <= I40E_PFQF_HKEY_MAX_INDEX; i++)
			seed_dw[i] = i40e_पढ़ो_rx_ctl(hw, I40E_PFQF_HKEY(i));
	पूर्ण
	अगर (lut) अणु
		u32 *lut_dw = (u32 *)lut;

		अगर (lut_size != I40E_HLUT_ARRAY_SIZE)
			वापस -EINVAL;
		क्रम (i = 0; i <= I40E_PFQF_HLUT_MAX_INDEX; i++)
			lut_dw[i] = rd32(hw, I40E_PFQF_HLUT(i));
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_config_rss - Configure RSS keys and lut
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 * @seed: RSS hash seed
 * @lut: Lookup table
 * @lut_size: Lookup table size
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक i40e_config_rss(काष्ठा i40e_vsi *vsi, u8 *seed, u8 *lut, u16 lut_size)
अणु
	काष्ठा i40e_pf *pf = vsi->back;

	अगर (pf->hw_features & I40E_HW_RSS_AQ_CAPABLE)
		वापस i40e_config_rss_aq(vsi, seed, lut, lut_size);
	अन्यथा
		वापस i40e_config_rss_reg(vsi, seed, lut, lut_size);
पूर्ण

/**
 * i40e_get_rss - Get RSS keys and lut
 * @vsi: Poपूर्णांकer to VSI काष्ठाure
 * @seed: Buffer to store the keys
 * @lut: Buffer to store the lookup table entries
 * @lut_size: Size of buffer to store the lookup table entries
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक i40e_get_rss(काष्ठा i40e_vsi *vsi, u8 *seed, u8 *lut, u16 lut_size)
अणु
	काष्ठा i40e_pf *pf = vsi->back;

	अगर (pf->hw_features & I40E_HW_RSS_AQ_CAPABLE)
		वापस i40e_get_rss_aq(vsi, seed, lut, lut_size);
	अन्यथा
		वापस i40e_get_rss_reg(vsi, seed, lut, lut_size);
पूर्ण

/**
 * i40e_fill_rss_lut - Fill the RSS lookup table with शेष values
 * @pf: Poपूर्णांकer to board निजी काष्ठाure
 * @lut: Lookup table
 * @rss_table_size: Lookup table size
 * @rss_size: Range of queue number क्रम hashing
 */
व्योम i40e_fill_rss_lut(काष्ठा i40e_pf *pf, u8 *lut,
		       u16 rss_table_size, u16 rss_size)
अणु
	u16 i;

	क्रम (i = 0; i < rss_table_size; i++)
		lut[i] = i % rss_size;
पूर्ण

/**
 * i40e_pf_config_rss - Prepare क्रम RSS अगर used
 * @pf: board निजी काष्ठाure
 **/
अटल पूर्णांक i40e_pf_config_rss(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	u8 seed[I40E_HKEY_ARRAY_SIZE];
	u8 *lut;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg_val;
	u64 hena;
	पूर्णांक ret;

	/* By शेष we enable TCP/UDP with IPv4/IPv6 ptypes */
	hena = (u64)i40e_पढ़ो_rx_ctl(hw, I40E_PFQF_HENA(0)) |
		((u64)i40e_पढ़ो_rx_ctl(hw, I40E_PFQF_HENA(1)) << 32);
	hena |= i40e_pf_get_शेष_rss_hena(pf);

	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_HENA(0), (u32)hena);
	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_HENA(1), (u32)(hena >> 32));

	/* Determine the RSS table size based on the hardware capabilities */
	reg_val = i40e_पढ़ो_rx_ctl(hw, I40E_PFQF_CTL_0);
	reg_val = (pf->rss_table_size == 512) ?
			(reg_val | I40E_PFQF_CTL_0_HASHLUTSIZE_512) :
			(reg_val & ~I40E_PFQF_CTL_0_HASHLUTSIZE_512);
	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_CTL_0, reg_val);

	/* Determine the RSS size of the VSI */
	अगर (!vsi->rss_size) अणु
		u16 qcount;
		/* If the firmware करोes something weird during VSI init, we
		 * could end up with zero TCs. Check क्रम that to aव्योम
		 * भागide-by-zero. It probably won't pass traffic, but it also
		 * won't panic.
		 */
		qcount = vsi->num_queue_pairs /
			 (vsi->tc_config.numtc ? vsi->tc_config.numtc : 1);
		vsi->rss_size = min_t(पूर्णांक, pf->alloc_rss_size, qcount);
	पूर्ण
	अगर (!vsi->rss_size)
		वापस -EINVAL;

	lut = kzalloc(vsi->rss_table_size, GFP_KERNEL);
	अगर (!lut)
		वापस -ENOMEM;

	/* Use user configured lut अगर there is one, otherwise use शेष */
	अगर (vsi->rss_lut_user)
		स_नकल(lut, vsi->rss_lut_user, vsi->rss_table_size);
	अन्यथा
		i40e_fill_rss_lut(pf, lut, vsi->rss_table_size, vsi->rss_size);

	/* Use user configured hash key अगर there is one, otherwise
	 * use शेष.
	 */
	अगर (vsi->rss_hkey_user)
		स_नकल(seed, vsi->rss_hkey_user, I40E_HKEY_ARRAY_SIZE);
	अन्यथा
		netdev_rss_key_fill((व्योम *)seed, I40E_HKEY_ARRAY_SIZE);
	ret = i40e_config_rss(vsi, seed, lut, vsi->rss_table_size);
	kमुक्त(lut);

	वापस ret;
पूर्ण

/**
 * i40e_reconfig_rss_queues - change number of queues क्रम rss and rebuild
 * @pf: board निजी काष्ठाure
 * @queue_count: the requested queue count क्रम rss.
 *
 * वापसs 0 अगर rss is not enabled, अगर enabled वापसs the final rss queue
 * count which may be dअगरferent from the requested queue count.
 * Note: expects to be called जबतक under rtnl_lock()
 **/
पूर्णांक i40e_reconfig_rss_queues(काष्ठा i40e_pf *pf, पूर्णांक queue_count)
अणु
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	पूर्णांक new_rss_size;

	अगर (!(pf->flags & I40E_FLAG_RSS_ENABLED))
		वापस 0;

	queue_count = min_t(पूर्णांक, queue_count, num_online_cpus());
	new_rss_size = min_t(पूर्णांक, queue_count, pf->rss_size_max);

	अगर (queue_count != vsi->num_queue_pairs) अणु
		u16 qcount;

		vsi->req_queue_pairs = queue_count;
		i40e_prep_क्रम_reset(pf);

		pf->alloc_rss_size = new_rss_size;

		i40e_reset_and_rebuild(pf, true, true);

		/* Discard the user configured hash keys and lut, अगर less
		 * queues are enabled.
		 */
		अगर (queue_count < vsi->rss_size) अणु
			i40e_clear_rss_config_user(vsi);
			dev_dbg(&pf->pdev->dev,
				"discard user configured hash keys and lut\n");
		पूर्ण

		/* Reset vsi->rss_size, as number of enabled queues changed */
		qcount = vsi->num_queue_pairs / vsi->tc_config.numtc;
		vsi->rss_size = min_t(पूर्णांक, pf->alloc_rss_size, qcount);

		i40e_pf_config_rss(pf);
	पूर्ण
	dev_info(&pf->pdev->dev, "User requested queue count/HW max RSS count:  %d/%d\n",
		 vsi->req_queue_pairs, pf->rss_size_max);
	वापस pf->alloc_rss_size;
पूर्ण

/**
 * i40e_get_partition_bw_setting - Retrieve BW settings क्रम this PF partition
 * @pf: board निजी काष्ठाure
 **/
i40e_status i40e_get_partition_bw_setting(काष्ठा i40e_pf *pf)
अणु
	i40e_status status;
	bool min_valid, max_valid;
	u32 max_bw, min_bw;

	status = i40e_पढ़ो_bw_from_alt_ram(&pf->hw, &max_bw, &min_bw,
					   &min_valid, &max_valid);

	अगर (!status) अणु
		अगर (min_valid)
			pf->min_bw = min_bw;
		अगर (max_valid)
			pf->max_bw = max_bw;
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_set_partition_bw_setting - Set BW settings क्रम this PF partition
 * @pf: board निजी काष्ठाure
 **/
i40e_status i40e_set_partition_bw_setting(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_aqc_configure_partition_bw_data bw_data;
	i40e_status status;

	स_रखो(&bw_data, 0, माप(bw_data));

	/* Set the valid bit क्रम this PF */
	bw_data.pf_valid_bits = cpu_to_le16(BIT(pf->hw.pf_id));
	bw_data.max_bw[pf->hw.pf_id] = pf->max_bw & I40E_ALT_BW_VALUE_MASK;
	bw_data.min_bw[pf->hw.pf_id] = pf->min_bw & I40E_ALT_BW_VALUE_MASK;

	/* Set the new bandwidths */
	status = i40e_aq_configure_partition_bw(&pf->hw, &bw_data, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_commit_partition_bw_setting - Commit BW settings क्रम this PF partition
 * @pf: board निजी काष्ठाure
 **/
i40e_status i40e_commit_partition_bw_setting(काष्ठा i40e_pf *pf)
अणु
	/* Commit temporary BW setting to permanent NVM image */
	क्रमागत i40e_admin_queue_err last_aq_status;
	i40e_status ret;
	u16 nvm_word;

	अगर (pf->hw.partition_id != 1) अणु
		dev_info(&pf->pdev->dev,
			 "Commit BW only works on partition 1! This is partition %d",
			 pf->hw.partition_id);
		ret = I40E_NOT_SUPPORTED;
		जाओ bw_commit_out;
	पूर्ण

	/* Acquire NVM क्रम पढ़ो access */
	ret = i40e_acquire_nvm(&pf->hw, I40E_RESOURCE_READ);
	last_aq_status = pf->hw.aq.asq_last_status;
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Cannot acquire NVM for read access, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
		जाओ bw_commit_out;
	पूर्ण

	/* Read word 0x10 of NVM - SW compatibility word 1 */
	ret = i40e_aq_पढ़ो_nvm(&pf->hw,
			       I40E_SR_NVM_CONTROL_WORD,
			       0x10, माप(nvm_word), &nvm_word,
			       false, शून्य);
	/* Save off last admin queue command status beक्रमe releasing
	 * the NVM
	 */
	last_aq_status = pf->hw.aq.asq_last_status;
	i40e_release_nvm(&pf->hw);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev, "NVM read error, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
		जाओ bw_commit_out;
	पूर्ण

	/* Wait a bit क्रम NVM release to complete */
	msleep(50);

	/* Acquire NVM क्रम ग_लिखो access */
	ret = i40e_acquire_nvm(&pf->hw, I40E_RESOURCE_WRITE);
	last_aq_status = pf->hw.aq.asq_last_status;
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Cannot acquire NVM for write access, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
		जाओ bw_commit_out;
	पूर्ण
	/* Write it back out unchanged to initiate update NVM,
	 * which will क्रमce a ग_लिखो of the shaकरोw (alt) RAM to
	 * the NVM - thus storing the bandwidth values permanently.
	 */
	ret = i40e_aq_update_nvm(&pf->hw,
				 I40E_SR_NVM_CONTROL_WORD,
				 0x10, माप(nvm_word),
				 &nvm_word, true, 0, शून्य);
	/* Save off last admin queue command status beक्रमe releasing
	 * the NVM
	 */
	last_aq_status = pf->hw.aq.asq_last_status;
	i40e_release_nvm(&pf->hw);
	अगर (ret)
		dev_info(&pf->pdev->dev,
			 "BW settings NOT SAVED, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
bw_commit_out:

	वापस ret;
पूर्ण

/**
 * i40e_is_total_port_shutकरोwn_enabled - पढ़ो NVM and वापस value
 * अगर total port shutकरोwn feature is enabled क्रम this PF
 * @pf: board निजी काष्ठाure
 **/
अटल bool i40e_is_total_port_shutकरोwn_enabled(काष्ठा i40e_pf *pf)
अणु
#घोषणा I40E_TOTAL_PORT_SHUTDOWN_ENABLED	BIT(4)
#घोषणा I40E_FEATURES_ENABLE_PTR		0x2A
#घोषणा I40E_CURRENT_SETTING_PTR		0x2B
#घोषणा I40E_LINK_BEHAVIOR_WORD_OFFSET		0x2D
#घोषणा I40E_LINK_BEHAVIOR_WORD_LENGTH		0x1
#घोषणा I40E_LINK_BEHAVIOR_OS_FORCED_ENABLED	BIT(0)
#घोषणा I40E_LINK_BEHAVIOR_PORT_BIT_LENGTH	4
	i40e_status पढ़ो_status = I40E_SUCCESS;
	u16 sr_emp_sr_settings_ptr = 0;
	u16 features_enable = 0;
	u16 link_behavior = 0;
	bool ret = false;

	पढ़ो_status = i40e_पढ़ो_nvm_word(&pf->hw,
					 I40E_SR_EMP_SR_SETTINGS_PTR,
					 &sr_emp_sr_settings_ptr);
	अगर (पढ़ो_status)
		जाओ err_nvm;
	पढ़ो_status = i40e_पढ़ो_nvm_word(&pf->hw,
					 sr_emp_sr_settings_ptr +
					 I40E_FEATURES_ENABLE_PTR,
					 &features_enable);
	अगर (पढ़ो_status)
		जाओ err_nvm;
	अगर (I40E_TOTAL_PORT_SHUTDOWN_ENABLED & features_enable) अणु
		पढ़ो_status = i40e_पढ़ो_nvm_module_data(&pf->hw,
							I40E_SR_EMP_SR_SETTINGS_PTR,
							I40E_CURRENT_SETTING_PTR,
							I40E_LINK_BEHAVIOR_WORD_OFFSET,
							I40E_LINK_BEHAVIOR_WORD_LENGTH,
							&link_behavior);
		अगर (पढ़ो_status)
			जाओ err_nvm;
		link_behavior >>= (pf->hw.port * I40E_LINK_BEHAVIOR_PORT_BIT_LENGTH);
		ret = I40E_LINK_BEHAVIOR_OS_FORCED_ENABLED & link_behavior;
	पूर्ण
	वापस ret;

err_nvm:
	dev_warn(&pf->pdev->dev,
		 "total-port-shutdown feature is off due to read nvm error: %s\n",
		 i40e_stat_str(&pf->hw, पढ़ो_status));
	वापस ret;
पूर्ण

/**
 * i40e_sw_init - Initialize general software काष्ठाures (काष्ठा i40e_pf)
 * @pf: board निजी काष्ठाure to initialize
 *
 * i40e_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 **/
अटल पूर्णांक i40e_sw_init(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक err = 0;
	पूर्णांक size;
	u16 घात;

	/* Set शेष capability flags */
	pf->flags = I40E_FLAG_RX_CSUM_ENABLED |
		    I40E_FLAG_MSI_ENABLED     |
		    I40E_FLAG_MSIX_ENABLED;

	/* Set शेष ITR */
	pf->rx_itr_शेष = I40E_ITR_RX_DEF;
	pf->tx_itr_शेष = I40E_ITR_TX_DEF;

	/* Depending on PF configurations, it is possible that the RSS
	 * maximum might end up larger than the available queues
	 */
	pf->rss_size_max = BIT(pf->hw.func_caps.rss_table_entry_width);
	pf->alloc_rss_size = 1;
	pf->rss_table_size = pf->hw.func_caps.rss_table_size;
	pf->rss_size_max = min_t(पूर्णांक, pf->rss_size_max,
				 pf->hw.func_caps.num_tx_qp);

	/* find the next higher घातer-of-2 of num cpus */
	घात = roundup_घात_of_two(num_online_cpus());
	pf->rss_size_max = min_t(पूर्णांक, pf->rss_size_max, घात);

	अगर (pf->hw.func_caps.rss) अणु
		pf->flags |= I40E_FLAG_RSS_ENABLED;
		pf->alloc_rss_size = min_t(पूर्णांक, pf->rss_size_max,
					   num_online_cpus());
	पूर्ण

	/* MFP mode enabled */
	अगर (pf->hw.func_caps.npar_enable || pf->hw.func_caps.flex10_enable) अणु
		pf->flags |= I40E_FLAG_MFP_ENABLED;
		dev_info(&pf->pdev->dev, "MFP mode Enabled\n");
		अगर (i40e_get_partition_bw_setting(pf)) अणु
			dev_warn(&pf->pdev->dev,
				 "Could not get partition bw settings\n");
		पूर्ण अन्यथा अणु
			dev_info(&pf->pdev->dev,
				 "Partition BW Min = %8.8x, Max = %8.8x\n",
				 pf->min_bw, pf->max_bw);

			/* nudge the Tx scheduler */
			i40e_set_partition_bw_setting(pf);
		पूर्ण
	पूर्ण

	अगर ((pf->hw.func_caps.fd_filters_guaranteed > 0) ||
	    (pf->hw.func_caps.fd_filters_best_efक्रमt > 0)) अणु
		pf->flags |= I40E_FLAG_FD_ATR_ENABLED;
		pf->atr_sample_rate = I40E_DEFAULT_ATR_SAMPLE_RATE;
		अगर (pf->flags & I40E_FLAG_MFP_ENABLED &&
		    pf->hw.num_partitions > 1)
			dev_info(&pf->pdev->dev,
				 "Flow Director Sideband mode Disabled in MFP mode\n");
		अन्यथा
			pf->flags |= I40E_FLAG_FD_SB_ENABLED;
		pf->fdir_pf_filter_count =
				 pf->hw.func_caps.fd_filters_guaranteed;
		pf->hw.fdir_shared_filter_count =
				 pf->hw.func_caps.fd_filters_best_efक्रमt;
	पूर्ण

	अगर (pf->hw.mac.type == I40E_MAC_X722) अणु
		pf->hw_features |= (I40E_HW_RSS_AQ_CAPABLE |
				    I40E_HW_128_QP_RSS_CAPABLE |
				    I40E_HW_ATR_EVICT_CAPABLE |
				    I40E_HW_WB_ON_ITR_CAPABLE |
				    I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE |
				    I40E_HW_NO_PCI_LINK_CHECK |
				    I40E_HW_USE_SET_LLDP_MIB |
				    I40E_HW_GENEVE_OFFLOAD_CAPABLE |
				    I40E_HW_PTP_L4_CAPABLE |
				    I40E_HW_WOL_MC_MAGIC_PKT_WAKE |
				    I40E_HW_OUTER_UDP_CSUM_CAPABLE);

#घोषणा I40E_FDEVICT_PCTYPE_DEFAULT 0xc03
		अगर (rd32(&pf->hw, I40E_GLQF_FDEVICTENA(1)) !=
		    I40E_FDEVICT_PCTYPE_DEFAULT) अणु
			dev_warn(&pf->pdev->dev,
				 "FD EVICT PCTYPES are not right, disable FD HW EVICT\n");
			pf->hw_features &= ~I40E_HW_ATR_EVICT_CAPABLE;
		पूर्ण
	पूर्ण अन्यथा अगर ((pf->hw.aq.api_maj_ver > 1) ||
		   ((pf->hw.aq.api_maj_ver == 1) &&
		    (pf->hw.aq.api_min_ver > 4))) अणु
		/* Supported in FW API version higher than 1.4 */
		pf->hw_features |= I40E_HW_GENEVE_OFFLOAD_CAPABLE;
	पूर्ण

	/* Enable HW ATR eviction अगर possible */
	अगर (pf->hw_features & I40E_HW_ATR_EVICT_CAPABLE)
		pf->flags |= I40E_FLAG_HW_ATR_EVICT_ENABLED;

	अगर ((pf->hw.mac.type == I40E_MAC_XL710) &&
	    (((pf->hw.aq.fw_maj_ver == 4) && (pf->hw.aq.fw_min_ver < 33)) ||
	    (pf->hw.aq.fw_maj_ver < 4))) अणु
		pf->hw_features |= I40E_HW_RESTART_AUTONEG;
		/* No DCB support  क्रम FW < v4.33 */
		pf->hw_features |= I40E_HW_NO_DCB_SUPPORT;
	पूर्ण

	/* Disable FW LLDP अगर FW < v4.3 */
	अगर ((pf->hw.mac.type == I40E_MAC_XL710) &&
	    (((pf->hw.aq.fw_maj_ver == 4) && (pf->hw.aq.fw_min_ver < 3)) ||
	    (pf->hw.aq.fw_maj_ver < 4)))
		pf->hw_features |= I40E_HW_STOP_FW_LLDP;

	/* Use the FW Set LLDP MIB API अगर FW > v4.40 */
	अगर ((pf->hw.mac.type == I40E_MAC_XL710) &&
	    (((pf->hw.aq.fw_maj_ver == 4) && (pf->hw.aq.fw_min_ver >= 40)) ||
	    (pf->hw.aq.fw_maj_ver >= 5)))
		pf->hw_features |= I40E_HW_USE_SET_LLDP_MIB;

	/* Enable PTP L4 अगर FW > v6.0 */
	अगर (pf->hw.mac.type == I40E_MAC_XL710 &&
	    pf->hw.aq.fw_maj_ver >= 6)
		pf->hw_features |= I40E_HW_PTP_L4_CAPABLE;

	अगर (pf->hw.func_caps.vmdq && num_online_cpus() != 1) अणु
		pf->num_vmdq_vsis = I40E_DEFAULT_NUM_VMDQ_VSI;
		pf->flags |= I40E_FLAG_VMDQ_ENABLED;
		pf->num_vmdq_qps = i40e_शेष_queues_per_vmdq(pf);
	पूर्ण

	अगर (pf->hw.func_caps.iwarp && num_online_cpus() != 1) अणु
		pf->flags |= I40E_FLAG_IWARP_ENABLED;
		/* IWARP needs one extra vector क्रम CQP just like MISC.*/
		pf->num_iwarp_msix = (पूर्णांक)num_online_cpus() + 1;
	पूर्ण
	/* Stopping FW LLDP engine is supported on XL710 and X722
	 * starting from FW versions determined in i40e_init_adminq.
	 * Stopping the FW LLDP engine is not supported on XL710
	 * अगर NPAR is functioning so unset this hw flag in this हाल.
	 */
	अगर (pf->hw.mac.type == I40E_MAC_XL710 &&
	    pf->hw.func_caps.npar_enable &&
	    (pf->hw.flags & I40E_HW_FLAG_FW_LLDP_STOPPABLE))
		pf->hw.flags &= ~I40E_HW_FLAG_FW_LLDP_STOPPABLE;

#अगर_घोषित CONFIG_PCI_IOV
	अगर (pf->hw.func_caps.num_vfs && pf->hw.partition_id == 1) अणु
		pf->num_vf_qps = I40E_DEFAULT_QUEUES_PER_VF;
		pf->flags |= I40E_FLAG_SRIOV_ENABLED;
		pf->num_req_vfs = min_t(पूर्णांक,
					pf->hw.func_caps.num_vfs,
					I40E_MAX_VF_COUNT);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */
	pf->eeprom_version = 0xDEAD;
	pf->lan_veb = I40E_NO_VEB;
	pf->lan_vsi = I40E_NO_VSI;

	/* By शेष FW has this off क्रम perक्रमmance reasons */
	pf->flags &= ~I40E_FLAG_VEB_STATS_ENABLED;

	/* set up queue assignment tracking */
	size = माप(काष्ठा i40e_lump_tracking)
		+ (माप(u16) * pf->hw.func_caps.num_tx_qp);
	pf->qp_pile = kzalloc(size, GFP_KERNEL);
	अगर (!pf->qp_pile) अणु
		err = -ENOMEM;
		जाओ sw_init_करोne;
	पूर्ण
	pf->qp_pile->num_entries = pf->hw.func_caps.num_tx_qp;
	pf->qp_pile->search_hपूर्णांक = 0;

	pf->tx_समयout_recovery_level = 1;

	अगर (pf->hw.mac.type != I40E_MAC_X722 &&
	    i40e_is_total_port_shutकरोwn_enabled(pf)) अणु
		/* Link करोwn on बंद must be on when total port shutकरोwn
		 * is enabled क्रम a given port
		 */
		pf->flags |= (I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED |
			      I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED);
		dev_info(&pf->pdev->dev,
			 "total-port-shutdown was enabled, link-down-on-close is forced on\n");
	पूर्ण
	mutex_init(&pf->चयन_mutex);

sw_init_करोne:
	वापस err;
पूर्ण

/**
 * i40e_set_ntuple - set the ntuple feature flag and take action
 * @pf: board निजी काष्ठाure to initialize
 * @features: the feature set that the stack is suggesting
 *
 * वापसs a bool to indicate अगर reset needs to happen
 **/
bool i40e_set_ntuple(काष्ठा i40e_pf *pf, netdev_features_t features)
अणु
	bool need_reset = false;

	/* Check अगर Flow Director n-tuple support was enabled or disabled.  If
	 * the state changed, we need to reset.
	 */
	अगर (features & NETIF_F_NTUPLE) अणु
		/* Enable filters and mark क्रम reset */
		अगर (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
			need_reset = true;
		/* enable FD_SB only अगर there is MSI-X vector and no cloud
		 * filters exist
		 */
		अगर (pf->num_fdsb_msix > 0 && !pf->num_cloud_filters) अणु
			pf->flags |= I40E_FLAG_FD_SB_ENABLED;
			pf->flags &= ~I40E_FLAG_FD_SB_INACTIVE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* turn off filters, mark क्रम reset and clear SW filter list */
		अगर (pf->flags & I40E_FLAG_FD_SB_ENABLED) अणु
			need_reset = true;
			i40e_fdir_filter_निकास(pf);
		पूर्ण
		pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
		clear_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state);
		pf->flags |= I40E_FLAG_FD_SB_INACTIVE;

		/* reset fd counters */
		pf->fd_add_err = 0;
		pf->fd_atr_cnt = 0;
		/* अगर ATR was स्वतः disabled it can be re-enabled. */
		अगर (test_and_clear_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state))
			अगर ((pf->flags & I40E_FLAG_FD_ATR_ENABLED) &&
			    (I40E_DEBUG_FD & pf->hw.debug_mask))
				dev_info(&pf->pdev->dev, "ATR re-enabled.\n");
	पूर्ण
	वापस need_reset;
पूर्ण

/**
 * i40e_clear_rss_lut - clear the rx hash lookup table
 * @vsi: the VSI being configured
 **/
अटल व्योम i40e_clear_rss_lut(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 vf_id = vsi->vf_id;
	u8 i;

	अगर (vsi->type == I40E_VSI_MAIN) अणु
		क्रम (i = 0; i <= I40E_PFQF_HLUT_MAX_INDEX; i++)
			wr32(hw, I40E_PFQF_HLUT(i), 0);
	पूर्ण अन्यथा अगर (vsi->type == I40E_VSI_SRIOV) अणु
		क्रम (i = 0; i <= I40E_VFQF_HLUT_MAX_INDEX; i++)
			i40e_ग_लिखो_rx_ctl(hw, I40E_VFQF_HLUT1(i, vf_id), 0);
	पूर्ण अन्यथा अणु
		dev_err(&pf->pdev->dev, "Cannot set RSS LUT - invalid VSI type\n");
	पूर्ण
पूर्ण

/**
 * i40e_set_features - set the netdev feature flags
 * @netdev: ptr to the netdev being adjusted
 * @features: the feature set that the stack is suggesting
 * Note: expects to be called जबतक under rtnl_lock()
 **/
अटल पूर्णांक i40e_set_features(काष्ठा net_device *netdev,
			     netdev_features_t features)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	bool need_reset;

	अगर (features & NETIF_F_RXHASH && !(netdev->features & NETIF_F_RXHASH))
		i40e_pf_config_rss(pf);
	अन्यथा अगर (!(features & NETIF_F_RXHASH) &&
		 netdev->features & NETIF_F_RXHASH)
		i40e_clear_rss_lut(vsi);

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		i40e_vlan_stripping_enable(vsi);
	अन्यथा
		i40e_vlan_stripping_disable(vsi);

	अगर (!(features & NETIF_F_HW_TC) && pf->num_cloud_filters) अणु
		dev_err(&pf->pdev->dev,
			"Offloaded tc filters active, can't turn hw_tc_offload off");
		वापस -EINVAL;
	पूर्ण

	अगर (!(features & NETIF_F_HW_L2FW_DOFFLOAD) && vsi->macvlan_cnt)
		i40e_del_all_macvlans(vsi);

	need_reset = i40e_set_ntuple(pf, features);

	अगर (need_reset)
		i40e_करो_reset(pf, I40E_PF_RESET_FLAG, true);

	वापस 0;
पूर्ण

अटल पूर्णांक i40e_udp_tunnel_set_port(काष्ठा net_device *netdev,
				    अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक idx,
				    काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_hw *hw = &np->vsi->back->hw;
	u8 type, filter_index;
	i40e_status ret;

	type = ti->type == UDP_TUNNEL_TYPE_VXLAN ? I40E_AQC_TUNNEL_TYPE_VXLAN :
						   I40E_AQC_TUNNEL_TYPE_NGE;

	ret = i40e_aq_add_udp_tunnel(hw, ntohs(ti->port), type, &filter_index,
				     शून्य);
	अगर (ret) अणु
		netdev_info(netdev, "add UDP port failed, err %s aq_err %s\n",
			    i40e_stat_str(hw, ret),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		वापस -EIO;
	पूर्ण

	udp_tunnel_nic_set_port_priv(netdev, table, idx, filter_index);
	वापस 0;
पूर्ण

अटल पूर्णांक i40e_udp_tunnel_unset_port(काष्ठा net_device *netdev,
				      अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक idx,
				      काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_hw *hw = &np->vsi->back->hw;
	i40e_status ret;

	ret = i40e_aq_del_udp_tunnel(hw, ti->hw_priv, शून्य);
	अगर (ret) अणु
		netdev_info(netdev, "delete UDP port failed, err %s aq_err %s\n",
			    i40e_stat_str(hw, ret),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i40e_get_phys_port_id(काष्ठा net_device *netdev,
				 काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;

	अगर (!(pf->hw_features & I40E_HW_PORT_ID_VALID))
		वापस -EOPNOTSUPP;

	ppid->id_len = min_t(पूर्णांक, माप(hw->mac.port_addr), माप(ppid->id));
	स_नकल(ppid->id, hw->mac.port_addr, ppid->id_len);

	वापस 0;
पूर्ण

/**
 * i40e_nकरो_fdb_add - add an entry to the hardware database
 * @ndm: the input from the stack
 * @tb: poपूर्णांकer to array of nladdr (unused)
 * @dev: the net device poपूर्णांकer
 * @addr: the MAC address entry being added
 * @vid: VLAN ID
 * @flags: inकाष्ठाions from stack about fdb operation
 * @extack: netlink extended ack, unused currently
 */
अटल पूर्णांक i40e_nकरो_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			    काष्ठा net_device *dev,
			    स्थिर अचिन्हित अक्षर *addr, u16 vid,
			    u16 flags,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	पूर्णांक err = 0;

	अगर (!(pf->flags & I40E_FLAG_SRIOV_ENABLED))
		वापस -EOPNOTSUPP;

	अगर (vid) अणु
		pr_info("%s: vlans aren't supported yet for dev_uc|mc_add()\n", dev->name);
		वापस -EINVAL;
	पूर्ण

	/* Hardware करोes not support aging addresses so अगर a
	 * ndm_state is given only allow permanent addresses
	 */
	अगर (ndm->ndm_state && !(ndm->ndm_state & NUD_PERMANENT)) अणु
		netdev_info(dev, "FDB only supports static addresses\n");
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
 * i40e_nकरो_bridge_setlink - Set the hardware bridge mode
 * @dev: the netdev being configured
 * @nlh: RTNL message
 * @flags: bridge flags
 * @extack: netlink extended ack
 *
 * Inserts a new hardware bridge अगर not alपढ़ोy created and
 * enables the bridging mode requested (VEB or VEPA). If the
 * hardware bridge has alपढ़ोy been inserted and the request
 * is to change the mode then that requires a PF reset to
 * allow rebuild of the components with required hardware
 * bridge mode enabled.
 *
 * Note: expects to be called जबतक under rtnl_lock()
 **/
अटल पूर्णांक i40e_nकरो_bridge_setlink(काष्ठा net_device *dev,
				   काष्ठा nlmsghdr *nlh,
				   u16 flags,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_veb *veb = शून्य;
	काष्ठा nlattr *attr, *br_spec;
	पूर्णांक i, rem;

	/* Only क्रम PF VSI क्रम now */
	अगर (vsi->seid != pf->vsi[pf->lan_vsi]->seid)
		वापस -EOPNOTSUPP;

	/* Find the HW bridge क्रम PF VSI */
	क्रम (i = 0; i < I40E_MAX_VEB && !veb; i++) अणु
		अगर (pf->veb[i] && pf->veb[i]->seid == vsi->uplink_seid)
			veb = pf->veb[i];
	पूर्ण

	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);

	nla_क्रम_each_nested(attr, br_spec, rem) अणु
		__u16 mode;

		अगर (nla_type(attr) != IFLA_BRIDGE_MODE)
			जारी;

		mode = nla_get_u16(attr);
		अगर ((mode != BRIDGE_MODE_VEPA) &&
		    (mode != BRIDGE_MODE_VEB))
			वापस -EINVAL;

		/* Insert a new HW bridge */
		अगर (!veb) अणु
			veb = i40e_veb_setup(pf, 0, vsi->uplink_seid, vsi->seid,
					     vsi->tc_config.enabled_tc);
			अगर (veb) अणु
				veb->bridge_mode = mode;
				i40e_config_bridge_mode(veb);
			पूर्ण अन्यथा अणु
				/* No Bridge HW offload available */
				वापस -ENOENT;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (mode != veb->bridge_mode) अणु
			/* Existing HW bridge but dअगरferent mode needs reset */
			veb->bridge_mode = mode;
			/* TODO: If no VFs or VMDq VSIs, disallow VEB mode */
			अगर (mode == BRIDGE_MODE_VEB)
				pf->flags |= I40E_FLAG_VEB_MODE_ENABLED;
			अन्यथा
				pf->flags &= ~I40E_FLAG_VEB_MODE_ENABLED;
			i40e_करो_reset(pf, I40E_PF_RESET_FLAG, true);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_nकरो_bridge_getlink - Get the hardware bridge mode
 * @skb: skb buff
 * @pid: process id
 * @seq: RTNL message seq #
 * @dev: the netdev being configured
 * @filter_mask: unused
 * @nlflags: netlink flags passed in
 *
 * Return the mode in which the hardware bridge is operating in
 * i.e VEB or VEPA.
 **/
अटल पूर्णांक i40e_nकरो_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
				   काष्ठा net_device *dev,
				   u32 __always_unused filter_mask,
				   पूर्णांक nlflags)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_veb *veb = शून्य;
	पूर्णांक i;

	/* Only क्रम PF VSI क्रम now */
	अगर (vsi->seid != pf->vsi[pf->lan_vsi]->seid)
		वापस -EOPNOTSUPP;

	/* Find the HW bridge क्रम the PF VSI */
	क्रम (i = 0; i < I40E_MAX_VEB && !veb; i++) अणु
		अगर (pf->veb[i] && pf->veb[i]->seid == vsi->uplink_seid)
			veb = pf->veb[i];
	पूर्ण

	अगर (!veb)
		वापस 0;

	वापस nकरो_dflt_bridge_getlink(skb, pid, seq, dev, veb->bridge_mode,
				       0, 0, nlflags, filter_mask, शून्य);
पूर्ण

/**
 * i40e_features_check - Validate encapsulated packet conक्रमms to limits
 * @skb: skb buff
 * @dev: This physical port's netdev
 * @features: Offload features that the stack believes apply
 **/
अटल netdev_features_t i40e_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	माप_प्रकार len;

	/* No poपूर्णांक in करोing any of this अगर neither checksum nor GSO are
	 * being requested क्रम this frame.  We can rule out both by just
	 * checking क्रम CHECKSUM_PARTIAL
	 */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस features;

	/* We cannot support GSO अगर the MSS is going to be less than
	 * 64 bytes.  If it is then we need to drop support क्रम GSO.
	 */
	अगर (skb_is_gso(skb) && (skb_shinfo(skb)->gso_size < 64))
		features &= ~NETIF_F_GSO_MASK;

	/* MACLEN can support at most 63 words */
	len = skb_network_header(skb) - skb->data;
	अगर (len & ~(63 * 2))
		जाओ out_err;

	/* IPLEN and EIPLEN can support at most 127 dwords */
	len = skb_transport_header(skb) - skb_network_header(skb);
	अगर (len & ~(127 * 4))
		जाओ out_err;

	अगर (skb->encapsulation) अणु
		/* L4TUNLEN can support 127 words */
		len = skb_inner_network_header(skb) - skb_transport_header(skb);
		अगर (len & ~(127 * 2))
			जाओ out_err;

		/* IPLEN can support at most 127 dwords */
		len = skb_inner_transport_header(skb) -
		      skb_inner_network_header(skb);
		अगर (len & ~(127 * 4))
			जाओ out_err;
	पूर्ण

	/* No need to validate L4LEN as TCP is the only protocol with a
	 * a flexible value and we support all possible values supported
	 * by TCP, which is at most 15 dwords
	 */

	वापस features;
out_err:
	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

/**
 * i40e_xdp_setup - add/हटाओ an XDP program
 * @vsi: VSI to changed
 * @prog: XDP program
 * @extack: netlink extended ack
 **/
अटल पूर्णांक i40e_xdp_setup(काष्ठा i40e_vsi *vsi, काष्ठा bpf_prog *prog,
			  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक frame_size = vsi->netdev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा bpf_prog *old_prog;
	bool need_reset;
	पूर्णांक i;

	/* Don't allow frames that span over multiple buffers */
	अगर (frame_size > vsi->rx_buf_len) अणु
		NL_SET_ERR_MSG_MOD(extack, "MTU too large to enable XDP");
		वापस -EINVAL;
	पूर्ण

	/* When turning XDP on->off/off->on we reset and rebuild the rings. */
	need_reset = (i40e_enabled_xdp_vsi(vsi) != !!prog);

	अगर (need_reset)
		i40e_prep_क्रम_reset(pf);

	old_prog = xchg(&vsi->xdp_prog, prog);

	अगर (need_reset) अणु
		अगर (!prog)
			/* Wait until nकरो_xsk_wakeup completes. */
			synchronize_rcu();
		i40e_reset_and_rebuild(pf, true, true);
	पूर्ण

	क्रम (i = 0; i < vsi->num_queue_pairs; i++)
		WRITE_ONCE(vsi->rx_rings[i]->xdp_prog, vsi->xdp_prog);

	अगर (old_prog)
		bpf_prog_put(old_prog);

	/* Kick start the NAPI context अगर there is an AF_XDP socket खोलो
	 * on that queue id. This so that receiving will start.
	 */
	अगर (need_reset && prog)
		क्रम (i = 0; i < vsi->num_queue_pairs; i++)
			अगर (vsi->xdp_rings[i]->xsk_pool)
				(व्योम)i40e_xsk_wakeup(vsi->netdev, i,
						      XDP_WAKEUP_RX);

	वापस 0;
पूर्ण

/**
 * i40e_enter_busy_conf - Enters busy config state
 * @vsi: vsi
 *
 * Returns 0 on success, <0 क्रम failure.
 **/
अटल पूर्णांक i40e_enter_busy_conf(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक समयout = 50;

	जबतक (test_and_set_bit(__I40E_CONFIG_BUSY, pf->state)) अणु
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
		usleep_range(1000, 2000);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_निकास_busy_conf - Exits busy config state
 * @vsi: vsi
 **/
अटल व्योम i40e_निकास_busy_conf(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;

	clear_bit(__I40E_CONFIG_BUSY, pf->state);
पूर्ण

/**
 * i40e_queue_pair_reset_stats - Resets all statistics क्रम a queue pair
 * @vsi: vsi
 * @queue_pair: queue pair
 **/
अटल व्योम i40e_queue_pair_reset_stats(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair)
अणु
	स_रखो(&vsi->rx_rings[queue_pair]->rx_stats, 0,
	       माप(vsi->rx_rings[queue_pair]->rx_stats));
	स_रखो(&vsi->tx_rings[queue_pair]->stats, 0,
	       माप(vsi->tx_rings[queue_pair]->stats));
	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		स_रखो(&vsi->xdp_rings[queue_pair]->stats, 0,
		       माप(vsi->xdp_rings[queue_pair]->stats));
	पूर्ण
पूर्ण

/**
 * i40e_queue_pair_clean_rings - Cleans all the rings of a queue pair
 * @vsi: vsi
 * @queue_pair: queue pair
 **/
अटल व्योम i40e_queue_pair_clean_rings(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair)
अणु
	i40e_clean_tx_ring(vsi->tx_rings[queue_pair]);
	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		/* Make sure that in-progress nकरो_xdp_xmit calls are
		 * completed.
		 */
		synchronize_rcu();
		i40e_clean_tx_ring(vsi->xdp_rings[queue_pair]);
	पूर्ण
	i40e_clean_rx_ring(vsi->rx_rings[queue_pair]);
पूर्ण

/**
 * i40e_queue_pair_toggle_napi - Enables/disables NAPI क्रम a queue pair
 * @vsi: vsi
 * @queue_pair: queue pair
 * @enable: true क्रम enable, false क्रम disable
 **/
अटल व्योम i40e_queue_pair_toggle_napi(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair,
					bool enable)
अणु
	काष्ठा i40e_ring *rxr = vsi->rx_rings[queue_pair];
	काष्ठा i40e_q_vector *q_vector = rxr->q_vector;

	अगर (!vsi->netdev)
		वापस;

	/* All rings in a qp beदीर्घ to the same qvector. */
	अगर (q_vector->rx.ring || q_vector->tx.ring) अणु
		अगर (enable)
			napi_enable(&q_vector->napi);
		अन्यथा
			napi_disable(&q_vector->napi);
	पूर्ण
पूर्ण

/**
 * i40e_queue_pair_toggle_rings - Enables/disables all rings क्रम a queue pair
 * @vsi: vsi
 * @queue_pair: queue pair
 * @enable: true क्रम enable, false क्रम disable
 *
 * Returns 0 on success, <0 on failure.
 **/
अटल पूर्णांक i40e_queue_pair_toggle_rings(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair,
					bool enable)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक pf_q, ret = 0;

	pf_q = vsi->base_queue + queue_pair;
	ret = i40e_control_रुको_tx_q(vsi->seid, pf, pf_q,
				     false /*is xdp*/, enable);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "VSI seid %d Tx ring %d %sable timeout\n",
			 vsi->seid, pf_q, (enable ? "en" : "dis"));
		वापस ret;
	पूर्ण

	i40e_control_rx_q(pf, pf_q, enable);
	ret = i40e_pf_rxq_रुको(pf, pf_q, enable);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "VSI seid %d Rx ring %d %sable timeout\n",
			 vsi->seid, pf_q, (enable ? "en" : "dis"));
		वापस ret;
	पूर्ण

	/* Due to HW errata, on Rx disable only, the रेजिस्टर can
	 * indicate करोne beक्रमe it really is. Needs 50ms to be sure
	 */
	अगर (!enable)
		mdelay(50);

	अगर (!i40e_enabled_xdp_vsi(vsi))
		वापस ret;

	ret = i40e_control_रुको_tx_q(vsi->seid, pf,
				     pf_q + vsi->alloc_queue_pairs,
				     true /*is xdp*/, enable);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "VSI seid %d XDP Tx ring %d %sable timeout\n",
			 vsi->seid, pf_q, (enable ? "en" : "dis"));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_queue_pair_enable_irq - Enables पूर्णांकerrupts क्रम a queue pair
 * @vsi: vsi
 * @queue_pair: queue_pair
 **/
अटल व्योम i40e_queue_pair_enable_irq(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair)
अणु
	काष्ठा i40e_ring *rxr = vsi->rx_rings[queue_pair];
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;

	/* All rings in a qp beदीर्घ to the same qvector. */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED)
		i40e_irq_dynamic_enable(vsi, rxr->q_vector->v_idx);
	अन्यथा
		i40e_irq_dynamic_enable_icr0(pf);

	i40e_flush(hw);
पूर्ण

/**
 * i40e_queue_pair_disable_irq - Disables पूर्णांकerrupts क्रम a queue pair
 * @vsi: vsi
 * @queue_pair: queue_pair
 **/
अटल व्योम i40e_queue_pair_disable_irq(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair)
अणु
	काष्ठा i40e_ring *rxr = vsi->rx_rings[queue_pair];
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;

	/* For simplicity, instead of removing the qp पूर्णांकerrupt causes
	 * from the पूर्णांकerrupt linked list, we simply disable the पूर्णांकerrupt, and
	 * leave the list पूर्णांकact.
	 *
	 * All rings in a qp beदीर्घ to the same qvector.
	 */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		u32 पूर्णांकpf = vsi->base_vector + rxr->q_vector->v_idx;

		wr32(hw, I40E_PFINT_DYN_CTLN(पूर्णांकpf - 1), 0);
		i40e_flush(hw);
		synchronize_irq(pf->msix_entries[पूर्णांकpf].vector);
	पूर्ण अन्यथा अणु
		/* Legacy and MSI mode - this stops all पूर्णांकerrupt handling */
		wr32(hw, I40E_PFINT_ICR0_ENA, 0);
		wr32(hw, I40E_PFINT_DYN_CTL0, 0);
		i40e_flush(hw);
		synchronize_irq(pf->pdev->irq);
	पूर्ण
पूर्ण

/**
 * i40e_queue_pair_disable - Disables a queue pair
 * @vsi: vsi
 * @queue_pair: queue pair
 *
 * Returns 0 on success, <0 on failure.
 **/
पूर्णांक i40e_queue_pair_disable(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair)
अणु
	पूर्णांक err;

	err = i40e_enter_busy_conf(vsi);
	अगर (err)
		वापस err;

	i40e_queue_pair_disable_irq(vsi, queue_pair);
	err = i40e_queue_pair_toggle_rings(vsi, queue_pair, false /* off */);
	i40e_queue_pair_toggle_napi(vsi, queue_pair, false /* off */);
	i40e_queue_pair_clean_rings(vsi, queue_pair);
	i40e_queue_pair_reset_stats(vsi, queue_pair);

	वापस err;
पूर्ण

/**
 * i40e_queue_pair_enable - Enables a queue pair
 * @vsi: vsi
 * @queue_pair: queue pair
 *
 * Returns 0 on success, <0 on failure.
 **/
पूर्णांक i40e_queue_pair_enable(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair)
अणु
	पूर्णांक err;

	err = i40e_configure_tx_ring(vsi->tx_rings[queue_pair]);
	अगर (err)
		वापस err;

	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		err = i40e_configure_tx_ring(vsi->xdp_rings[queue_pair]);
		अगर (err)
			वापस err;
	पूर्ण

	err = i40e_configure_rx_ring(vsi->rx_rings[queue_pair]);
	अगर (err)
		वापस err;

	err = i40e_queue_pair_toggle_rings(vsi, queue_pair, true /* on */);
	i40e_queue_pair_toggle_napi(vsi, queue_pair, true /* on */);
	i40e_queue_pair_enable_irq(vsi, queue_pair);

	i40e_निकास_busy_conf(vsi);

	वापस err;
पूर्ण

/**
 * i40e_xdp - implements nकरो_bpf क्रम i40e
 * @dev: netdevice
 * @xdp: XDP command
 **/
अटल पूर्णांक i40e_xdp(काष्ठा net_device *dev,
		    काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	अगर (vsi->type != I40E_VSI_MAIN)
		वापस -EINVAL;

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस i40e_xdp_setup(vsi, xdp->prog, xdp->extack);
	हाल XDP_SETUP_XSK_POOL:
		वापस i40e_xsk_pool_setup(vsi, xdp->xsk.pool,
					   xdp->xsk.queue_id);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops i40e_netdev_ops = अणु
	.nकरो_खोलो		= i40e_खोलो,
	.nकरो_stop		= i40e_बंद,
	.nकरो_start_xmit		= i40e_lan_xmit_frame,
	.nकरो_get_stats64	= i40e_get_netdev_stats_काष्ठा,
	.nकरो_set_rx_mode	= i40e_set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= i40e_set_mac,
	.nकरो_change_mtu		= i40e_change_mtu,
	.nकरो_करो_ioctl		= i40e_ioctl,
	.nकरो_tx_समयout		= i40e_tx_समयout,
	.nकरो_vlan_rx_add_vid	= i40e_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= i40e_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= i40e_netpoll,
#पूर्ण_अगर
	.nकरो_setup_tc		= __i40e_setup_tc,
	.nकरो_set_features	= i40e_set_features,
	.nकरो_set_vf_mac		= i40e_nकरो_set_vf_mac,
	.nकरो_set_vf_vlan	= i40e_nकरो_set_vf_port_vlan,
	.nकरो_get_vf_stats	= i40e_get_vf_stats,
	.nकरो_set_vf_rate	= i40e_nकरो_set_vf_bw,
	.nकरो_get_vf_config	= i40e_nकरो_get_vf_config,
	.nकरो_set_vf_link_state	= i40e_nकरो_set_vf_link_state,
	.nकरो_set_vf_spoofchk	= i40e_nकरो_set_vf_spoofchk,
	.nकरो_set_vf_trust	= i40e_nकरो_set_vf_trust,
	.nकरो_get_phys_port_id	= i40e_get_phys_port_id,
	.nकरो_fdb_add		= i40e_nकरो_fdb_add,
	.nकरो_features_check	= i40e_features_check,
	.nकरो_bridge_getlink	= i40e_nकरो_bridge_getlink,
	.nकरो_bridge_setlink	= i40e_nकरो_bridge_setlink,
	.nकरो_bpf		= i40e_xdp,
	.nकरो_xdp_xmit		= i40e_xdp_xmit,
	.nकरो_xsk_wakeup	        = i40e_xsk_wakeup,
	.nकरो_dfwd_add_station	= i40e_fwd_add,
	.nकरो_dfwd_del_station	= i40e_fwd_del,
पूर्ण;

/**
 * i40e_config_netdev - Setup the netdev flags
 * @vsi: the VSI being configured
 *
 * Returns 0 on success, negative value on failure
 **/
अटल पूर्णांक i40e_config_netdev(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_netdev_priv *np;
	काष्ठा net_device *netdev;
	u8 broadcast[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];
	पूर्णांक etherdev_size;
	netdev_features_t hw_enc_features;
	netdev_features_t hw_features;

	etherdev_size = माप(काष्ठा i40e_netdev_priv);
	netdev = alloc_etherdev_mq(etherdev_size, vsi->alloc_queue_pairs);
	अगर (!netdev)
		वापस -ENOMEM;

	vsi->netdev = netdev;
	np = netdev_priv(netdev);
	np->vsi = vsi;

	hw_enc_features = NETIF_F_SG			|
			  NETIF_F_IP_CSUM		|
			  NETIF_F_IPV6_CSUM		|
			  NETIF_F_HIGHDMA		|
			  NETIF_F_SOFT_FEATURES		|
			  NETIF_F_TSO			|
			  NETIF_F_TSO_ECN		|
			  NETIF_F_TSO6			|
			  NETIF_F_GSO_GRE		|
			  NETIF_F_GSO_GRE_CSUM		|
			  NETIF_F_GSO_PARTIAL		|
			  NETIF_F_GSO_IPXIP4		|
			  NETIF_F_GSO_IPXIP6		|
			  NETIF_F_GSO_UDP_TUNNEL	|
			  NETIF_F_GSO_UDP_TUNNEL_CSUM	|
			  NETIF_F_GSO_UDP_L4		|
			  NETIF_F_SCTP_CRC		|
			  NETIF_F_RXHASH		|
			  NETIF_F_RXCSUM		|
			  0;

	अगर (!(pf->hw_features & I40E_HW_OUTER_UDP_CSUM_CAPABLE))
		netdev->gso_partial_features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;

	netdev->udp_tunnel_nic_info = &pf->udp_tunnel_nic;

	netdev->gso_partial_features |= NETIF_F_GSO_GRE_CSUM;

	netdev->hw_enc_features |= hw_enc_features;

	/* record features VLANs can make use of */
	netdev->vlan_features |= hw_enc_features | NETIF_F_TSO_MANGLEID;

	/* enable macvlan offloads */
	netdev->hw_features |= NETIF_F_HW_L2FW_DOFFLOAD;

	hw_features = hw_enc_features		|
		      NETIF_F_HW_VLAN_CTAG_TX	|
		      NETIF_F_HW_VLAN_CTAG_RX;

	अगर (!(pf->flags & I40E_FLAG_MFP_ENABLED))
		hw_features |= NETIF_F_NTUPLE | NETIF_F_HW_TC;

	netdev->hw_features |= hw_features;

	netdev->features |= hw_features | NETIF_F_HW_VLAN_CTAG_FILTER;
	netdev->hw_enc_features |= NETIF_F_TSO_MANGLEID;

	अगर (vsi->type == I40E_VSI_MAIN) अणु
		SET_NETDEV_DEV(netdev, &pf->pdev->dev);
		ether_addr_copy(mac_addr, hw->mac.perm_addr);
		/* The following steps are necessary क्रम two reasons. First,
		 * some older NVM configurations load a शेष MAC-VLAN
		 * filter that will accept any tagged packet, and we want to
		 * replace this with a normal filter. Additionally, it is
		 * possible our MAC address was provided by the platक्रमm using
		 * Open Firmware or similar.
		 *
		 * Thus, we need to हटाओ the शेष filter and install one
		 * specअगरic to the MAC address.
		 */
		i40e_rm_शेष_mac_filter(vsi, mac_addr);
		spin_lock_bh(&vsi->mac_filter_hash_lock);
		i40e_add_mac_filter(vsi, mac_addr);
		spin_unlock_bh(&vsi->mac_filter_hash_lock);
	पूर्ण अन्यथा अणु
		/* Relate the VSI_VMDQ name to the VSI_MAIN name. Note that we
		 * are still limited by IFNAMSIZ, but we're adding 'v%d\0' to
		 * the end, which is 4 bytes दीर्घ, so क्रमce truncation of the
		 * original name by IFNAMSIZ - 4
		 */
		snम_लिखो(netdev->name, IFNAMSIZ, "%.*sv%%d",
			 IFNAMSIZ - 4,
			 pf->vsi[pf->lan_vsi]->netdev->name);
		eth_अक्रमom_addr(mac_addr);

		spin_lock_bh(&vsi->mac_filter_hash_lock);
		i40e_add_mac_filter(vsi, mac_addr);
		spin_unlock_bh(&vsi->mac_filter_hash_lock);
	पूर्ण

	/* Add the broadcast filter so that we initially will receive
	 * broadcast packets. Note that when a new VLAN is first added the
	 * driver will convert all filters marked I40E_VLAN_ANY पूर्णांकo VLAN
	 * specअगरic filters as part of transitioning पूर्णांकo "vlan" operation.
	 * When more VLANs are added, the driver will copy each existing MAC
	 * filter and add it क्रम the new VLAN.
	 *
	 * Broadcast filters are handled specially by
	 * i40e_sync_filters_subtask, as the driver must to set the broadcast
	 * promiscuous bit instead of adding this directly as a MAC/VLAN
	 * filter. The subtask will update the correct broadcast promiscuous
	 * bits as VLANs become active or inactive.
	 */
	eth_broadcast_addr(broadcast);
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	i40e_add_mac_filter(vsi, broadcast);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	ether_addr_copy(netdev->dev_addr, mac_addr);
	ether_addr_copy(netdev->perm_addr, mac_addr);

	/* i40iw_net_event() पढ़ोs 16 bytes from neigh->primary_key */
	netdev->neigh_priv_len = माप(u32) * 4;

	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->priv_flags |= IFF_SUPP_NOFCS;
	/* Setup netdev TC inक्रमmation */
	i40e_vsi_config_netdev_tc(vsi, vsi->tc_config.enabled_tc);

	netdev->netdev_ops = &i40e_netdev_ops;
	netdev->watchकरोg_समयo = 5 * HZ;
	i40e_set_ethtool_ops(netdev);

	/* MTU range: 68 - 9706 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = I40E_MAX_RXBUFFER - I40E_PACKET_HDR_PAD;

	वापस 0;
पूर्ण

/**
 * i40e_vsi_delete - Delete a VSI from the चयन
 * @vsi: the VSI being हटाओd
 *
 * Returns 0 on success, negative value on failure
 **/
अटल व्योम i40e_vsi_delete(काष्ठा i40e_vsi *vsi)
अणु
	/* हटाओ शेष VSI is not allowed */
	अगर (vsi == vsi->back->vsi[vsi->back->lan_vsi])
		वापस;

	i40e_aq_delete_element(&vsi->back->hw, vsi->seid, शून्य);
पूर्ण

/**
 * i40e_is_vsi_uplink_mode_veb - Check अगर the VSI's uplink bridge mode is VEB
 * @vsi: the VSI being queried
 *
 * Returns 1 अगर HW bridge mode is VEB and वापस 0 in हाल of VEPA mode
 **/
पूर्णांक i40e_is_vsi_uplink_mode_veb(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_veb *veb;
	काष्ठा i40e_pf *pf = vsi->back;

	/* Uplink is not a bridge so शेष to VEB */
	अगर (vsi->veb_idx >= I40E_MAX_VEB)
		वापस 1;

	veb = pf->veb[vsi->veb_idx];
	अगर (!veb) अणु
		dev_info(&pf->pdev->dev,
			 "There is no veb associated with the bridge\n");
		वापस -ENOENT;
	पूर्ण

	/* Uplink is a bridge in VEPA mode */
	अगर (veb->bridge_mode & BRIDGE_MODE_VEPA) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		/* Uplink is a bridge in VEB mode */
		वापस 1;
	पूर्ण

	/* VEPA is now शेष bridge, so वापस 0 */
	वापस 0;
पूर्ण

/**
 * i40e_add_vsi - Add a VSI to the चयन
 * @vsi: the VSI being configured
 *
 * This initializes a VSI context depending on the VSI type to be added and
 * passes it करोwn to the add_vsi aq command.
 **/
अटल पूर्णांक i40e_add_vsi(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vsi_context ctxt;
	काष्ठा i40e_mac_filter *f;
	काष्ठा hlist_node *h;
	पूर्णांक bkt;

	u8 enabled_tc = 0x1; /* TC0 enabled */
	पूर्णांक f_count = 0;

	स_रखो(&ctxt, 0, माप(ctxt));
	चयन (vsi->type) अणु
	हाल I40E_VSI_MAIN:
		/* The PF's मुख्य VSI is alपढ़ोy setup as part of the
		 * device initialization, so we'll not bother with
		 * the add_vsi call, but we will retrieve the current
		 * VSI context.
		 */
		ctxt.seid = pf->मुख्य_vsi_seid;
		ctxt.pf_num = pf->hw.pf_id;
		ctxt.vf_num = 0;
		ret = i40e_aq_get_vsi_params(&pf->hw, &ctxt, शून्य);
		ctxt.flags = I40E_AQ_VSI_TYPE_PF;
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "couldn't get PF vsi config, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			वापस -ENOENT;
		पूर्ण
		vsi->info = ctxt.info;
		vsi->info.valid_sections = 0;

		vsi->seid = ctxt.seid;
		vsi->id = ctxt.vsi_number;

		enabled_tc = i40e_pf_get_tc_map(pf);

		/* Source pruning is enabled by शेष, so the flag is
		 * negative logic - अगर it's set, we need to fiddle with
		 * the VSI to disable source pruning.
		 */
		अगर (pf->flags & I40E_FLAG_SOURCE_PRUNING_DISABLED) अणु
			स_रखो(&ctxt, 0, माप(ctxt));
			ctxt.seid = pf->मुख्य_vsi_seid;
			ctxt.pf_num = pf->hw.pf_id;
			ctxt.vf_num = 0;
			ctxt.info.valid_sections |=
				     cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
			ctxt.info.चयन_id =
				   cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_LOCAL_LB);
			ret = i40e_aq_update_vsi_params(hw, &ctxt, शून्य);
			अगर (ret) अणु
				dev_info(&pf->pdev->dev,
					 "update vsi failed, err %s aq_err %s\n",
					 i40e_stat_str(&pf->hw, ret),
					 i40e_aq_str(&pf->hw,
						     pf->hw.aq.asq_last_status));
				ret = -ENOENT;
				जाओ err;
			पूर्ण
		पूर्ण

		/* MFP mode setup queue map and update VSI */
		अगर ((pf->flags & I40E_FLAG_MFP_ENABLED) &&
		    !(pf->hw.func_caps.iscsi)) अणु /* NIC type PF */
			स_रखो(&ctxt, 0, माप(ctxt));
			ctxt.seid = pf->मुख्य_vsi_seid;
			ctxt.pf_num = pf->hw.pf_id;
			ctxt.vf_num = 0;
			i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, false);
			ret = i40e_aq_update_vsi_params(hw, &ctxt, शून्य);
			अगर (ret) अणु
				dev_info(&pf->pdev->dev,
					 "update vsi failed, err %s aq_err %s\n",
					 i40e_stat_str(&pf->hw, ret),
					 i40e_aq_str(&pf->hw,
						    pf->hw.aq.asq_last_status));
				ret = -ENOENT;
				जाओ err;
			पूर्ण
			/* update the local VSI info queue map */
			i40e_vsi_update_queue_map(vsi, &ctxt);
			vsi->info.valid_sections = 0;
		पूर्ण अन्यथा अणु
			/* Default/Main VSI is only enabled क्रम TC0
			 * reconfigure it to enable all TCs that are
			 * available on the port in SFP mode.
			 * For MFP हाल the iSCSI PF would use this
			 * flow to enable LAN+iSCSI TC.
			 */
			ret = i40e_vsi_config_tc(vsi, enabled_tc);
			अगर (ret) अणु
				/* Single TC condition is not fatal,
				 * message and जारी
				 */
				dev_info(&pf->pdev->dev,
					 "failed to configure TCs for main VSI tc_map 0x%08x, err %s aq_err %s\n",
					 enabled_tc,
					 i40e_stat_str(&pf->hw, ret),
					 i40e_aq_str(&pf->hw,
						    pf->hw.aq.asq_last_status));
			पूर्ण
		पूर्ण
		अवरोध;

	हाल I40E_VSI_Fसूची:
		ctxt.pf_num = hw->pf_id;
		ctxt.vf_num = 0;
		ctxt.uplink_seid = vsi->uplink_seid;
		ctxt.connection_type = I40E_AQ_VSI_CONN_TYPE_NORMAL;
		ctxt.flags = I40E_AQ_VSI_TYPE_PF;
		अगर ((pf->flags & I40E_FLAG_VEB_MODE_ENABLED) &&
		    (i40e_is_vsi_uplink_mode_veb(vsi))) अणु
			ctxt.info.valid_sections |=
			     cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
			ctxt.info.चयन_id =
			   cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);
		पूर्ण
		i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, true);
		अवरोध;

	हाल I40E_VSI_VMDQ2:
		ctxt.pf_num = hw->pf_id;
		ctxt.vf_num = 0;
		ctxt.uplink_seid = vsi->uplink_seid;
		ctxt.connection_type = I40E_AQ_VSI_CONN_TYPE_NORMAL;
		ctxt.flags = I40E_AQ_VSI_TYPE_VMDQ2;

		/* This VSI is connected to VEB so the चयन_id
		 * should be set to zero by शेष.
		 */
		अगर (i40e_is_vsi_uplink_mode_veb(vsi)) अणु
			ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
			ctxt.info.चयन_id =
				cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);
		पूर्ण

		/* Setup the VSI tx/rx queue map क्रम TC0 only क्रम now */
		i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, true);
		अवरोध;

	हाल I40E_VSI_SRIOV:
		ctxt.pf_num = hw->pf_id;
		ctxt.vf_num = vsi->vf_id + hw->func_caps.vf_base_id;
		ctxt.uplink_seid = vsi->uplink_seid;
		ctxt.connection_type = I40E_AQ_VSI_CONN_TYPE_NORMAL;
		ctxt.flags = I40E_AQ_VSI_TYPE_VF;

		/* This VSI is connected to VEB so the चयन_id
		 * should be set to zero by शेष.
		 */
		अगर (i40e_is_vsi_uplink_mode_veb(vsi)) अणु
			ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
			ctxt.info.चयन_id =
				cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);
		पूर्ण

		अगर (vsi->back->flags & I40E_FLAG_IWARP_ENABLED) अणु
			ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_QUEUE_OPT_VALID);
			ctxt.info.queueing_opt_flags |=
				(I40E_AQ_VSI_QUE_OPT_TCP_ENA |
				 I40E_AQ_VSI_QUE_OPT_RSS_LUT_VSI);
		पूर्ण

		ctxt.info.valid_sections |= cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID);
		ctxt.info.port_vlan_flags |= I40E_AQ_VSI_PVLAN_MODE_ALL;
		अगर (pf->vf[vsi->vf_id].spoofchk) अणु
			ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_SECURITY_VALID);
			ctxt.info.sec_flags |=
				(I40E_AQ_VSI_SEC_FLAG_ENABLE_VLAN_CHK |
				 I40E_AQ_VSI_SEC_FLAG_ENABLE_MAC_CHK);
		पूर्ण
		/* Setup the VSI tx/rx queue map क्रम TC0 only क्रम now */
		i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, true);
		अवरोध;

	हाल I40E_VSI_IWARP:
		/* send करोwn message to iWARP */
		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	अगर (vsi->type != I40E_VSI_MAIN) अणु
		ret = i40e_aq_add_vsi(hw, &ctxt, शून्य);
		अगर (ret) अणु
			dev_info(&vsi->back->pdev->dev,
				 "add vsi failed, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			ret = -ENOENT;
			जाओ err;
		पूर्ण
		vsi->info = ctxt.info;
		vsi->info.valid_sections = 0;
		vsi->seid = ctxt.seid;
		vsi->id = ctxt.vsi_number;
	पूर्ण

	vsi->active_filters = 0;
	clear_bit(__I40E_VSI_OVERFLOW_PROMISC, vsi->state);
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	/* If macvlan filters alपढ़ोy exist, क्रमce them to get loaded */
	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
		f->state = I40E_FILTER_NEW;
		f_count++;
	पूर्ण
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	अगर (f_count) अणु
		vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;
		set_bit(__I40E_MACVLAN_SYNC_PENDING, pf->state);
	पूर्ण

	/* Update VSI BW inक्रमmation */
	ret = i40e_vsi_get_bw_info(vsi);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get vsi bw info, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		/* VSI is alपढ़ोy added so not tearing that up */
		ret = 0;
	पूर्ण

err:
	वापस ret;
पूर्ण

/**
 * i40e_vsi_release - Delete a VSI and मुक्त its resources
 * @vsi: the VSI being हटाओd
 *
 * Returns 0 on success or < 0 on error
 **/
पूर्णांक i40e_vsi_release(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_mac_filter *f;
	काष्ठा hlist_node *h;
	काष्ठा i40e_veb *veb = शून्य;
	काष्ठा i40e_pf *pf;
	u16 uplink_seid;
	पूर्णांक i, n, bkt;

	pf = vsi->back;

	/* release of a VEB-owner or last VSI is not allowed */
	अगर (vsi->flags & I40E_VSI_FLAG_VEB_OWNER) अणु
		dev_info(&pf->pdev->dev, "VSI %d has existing VEB %d\n",
			 vsi->seid, vsi->uplink_seid);
		वापस -ENODEV;
	पूर्ण
	अगर (vsi == pf->vsi[pf->lan_vsi] &&
	    !test_bit(__I40E_DOWN, pf->state)) अणु
		dev_info(&pf->pdev->dev, "Can't remove PF VSI\n");
		वापस -ENODEV;
	पूर्ण

	uplink_seid = vsi->uplink_seid;
	अगर (vsi->type != I40E_VSI_SRIOV) अणु
		अगर (vsi->netdev_रेजिस्टरed) अणु
			vsi->netdev_रेजिस्टरed = false;
			अगर (vsi->netdev) अणु
				/* results in a call to i40e_बंद() */
				unरेजिस्टर_netdev(vsi->netdev);
			पूर्ण
		पूर्ण अन्यथा अणु
			i40e_vsi_बंद(vsi);
		पूर्ण
		i40e_vsi_disable_irq(vsi);
	पूर्ण

	spin_lock_bh(&vsi->mac_filter_hash_lock);

	/* clear the sync flag on all filters */
	अगर (vsi->netdev) अणु
		__dev_uc_unsync(vsi->netdev, शून्य);
		__dev_mc_unsync(vsi->netdev, शून्य);
	पूर्ण

	/* make sure any reमुख्यing filters are marked क्रम deletion */
	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist)
		__i40e_del_filter(vsi, f);

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	i40e_sync_vsi_filters(vsi);

	i40e_vsi_delete(vsi);
	i40e_vsi_मुक्त_q_vectors(vsi);
	अगर (vsi->netdev) अणु
		मुक्त_netdev(vsi->netdev);
		vsi->netdev = शून्य;
	पूर्ण
	i40e_vsi_clear_rings(vsi);
	i40e_vsi_clear(vsi);

	/* If this was the last thing on the VEB, except क्रम the
	 * controlling VSI, हटाओ the VEB, which माला_दो the controlling
	 * VSI onto the next level करोwn in the चयन.
	 *
	 * Well, okay, there's one more exception here: don't हटाओ
	 * the orphan VEBs yet.  We'll रुको क्रम an explicit हटाओ request
	 * from up the network stack.
	 */
	क्रम (n = 0, i = 0; i < pf->num_alloc_vsi; i++) अणु
		अगर (pf->vsi[i] &&
		    pf->vsi[i]->uplink_seid == uplink_seid &&
		    (pf->vsi[i]->flags & I40E_VSI_FLAG_VEB_OWNER) == 0) अणु
			n++;      /* count the VSIs */
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < I40E_MAX_VEB; i++) अणु
		अगर (!pf->veb[i])
			जारी;
		अगर (pf->veb[i]->uplink_seid == uplink_seid)
			n++;     /* count the VEBs */
		अगर (pf->veb[i]->seid == uplink_seid)
			veb = pf->veb[i];
	पूर्ण
	अगर (n == 0 && veb && veb->uplink_seid != 0)
		i40e_veb_release(veb);

	वापस 0;
पूर्ण

/**
 * i40e_vsi_setup_vectors - Set up the q_vectors क्रम the given VSI
 * @vsi: ptr to the VSI
 *
 * This should only be called after i40e_vsi_mem_alloc() which allocates the
 * corresponding SW VSI काष्ठाure and initializes num_queue_pairs क्रम the
 * newly allocated VSI.
 *
 * Returns 0 on success or negative on failure
 **/
अटल पूर्णांक i40e_vsi_setup_vectors(काष्ठा i40e_vsi *vsi)
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा i40e_pf *pf = vsi->back;

	अगर (vsi->q_vectors[0]) अणु
		dev_info(&pf->pdev->dev, "VSI %d has existing q_vectors\n",
			 vsi->seid);
		वापस -EEXIST;
	पूर्ण

	अगर (vsi->base_vector) अणु
		dev_info(&pf->pdev->dev, "VSI %d has non-zero base vector %d\n",
			 vsi->seid, vsi->base_vector);
		वापस -EEXIST;
	पूर्ण

	ret = i40e_vsi_alloc_q_vectors(vsi);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "failed to allocate %d q_vector for VSI %d, ret=%d\n",
			 vsi->num_q_vectors, vsi->seid, ret);
		vsi->num_q_vectors = 0;
		जाओ vector_setup_out;
	पूर्ण

	/* In Legacy mode, we करो not have to get any other vector since we
	 * piggyback on the misc/ICR0 क्रम queue पूर्णांकerrupts.
	*/
	अगर (!(pf->flags & I40E_FLAG_MSIX_ENABLED))
		वापस ret;
	अगर (vsi->num_q_vectors)
		vsi->base_vector = i40e_get_lump(pf, pf->irq_pile,
						 vsi->num_q_vectors, vsi->idx);
	अगर (vsi->base_vector < 0) अणु
		dev_info(&pf->pdev->dev,
			 "failed to get tracking for %d vectors for VSI %d, err=%d\n",
			 vsi->num_q_vectors, vsi->seid, vsi->base_vector);
		i40e_vsi_मुक्त_q_vectors(vsi);
		ret = -ENOENT;
		जाओ vector_setup_out;
	पूर्ण

vector_setup_out:
	वापस ret;
पूर्ण

/**
 * i40e_vsi_reinit_setup - वापस and पुनः_स्मृतिate resources क्रम a VSI
 * @vsi: poपूर्णांकer to the vsi.
 *
 * This re-allocates a vsi's queue resources.
 *
 * Returns poपूर्णांकer to the successfully allocated and configured VSI sw काष्ठा
 * on success, otherwise वापसs शून्य on failure.
 **/
अटल काष्ठा i40e_vsi *i40e_vsi_reinit_setup(काष्ठा i40e_vsi *vsi)
अणु
	u16 alloc_queue_pairs;
	काष्ठा i40e_pf *pf;
	u8 enabled_tc;
	पूर्णांक ret;

	अगर (!vsi)
		वापस शून्य;

	pf = vsi->back;

	i40e_put_lump(pf->qp_pile, vsi->base_queue, vsi->idx);
	i40e_vsi_clear_rings(vsi);

	i40e_vsi_मुक्त_arrays(vsi, false);
	i40e_set_num_rings_in_vsi(vsi);
	ret = i40e_vsi_alloc_arrays(vsi, false);
	अगर (ret)
		जाओ err_vsi;

	alloc_queue_pairs = vsi->alloc_queue_pairs *
			    (i40e_enabled_xdp_vsi(vsi) ? 2 : 1);

	ret = i40e_get_lump(pf, pf->qp_pile, alloc_queue_pairs, vsi->idx);
	अगर (ret < 0) अणु
		dev_info(&pf->pdev->dev,
			 "failed to get tracking for %d queues for VSI %d err %d\n",
			 alloc_queue_pairs, vsi->seid, ret);
		जाओ err_vsi;
	पूर्ण
	vsi->base_queue = ret;

	/* Update the FW view of the VSI. Force a reset of TC and queue
	 * layout configurations.
	 */
	enabled_tc = pf->vsi[pf->lan_vsi]->tc_config.enabled_tc;
	pf->vsi[pf->lan_vsi]->tc_config.enabled_tc = 0;
	pf->vsi[pf->lan_vsi]->seid = pf->मुख्य_vsi_seid;
	i40e_vsi_config_tc(pf->vsi[pf->lan_vsi], enabled_tc);
	अगर (vsi->type == I40E_VSI_MAIN)
		i40e_rm_शेष_mac_filter(vsi, pf->hw.mac.perm_addr);

	/* assign it some queues */
	ret = i40e_alloc_rings(vsi);
	अगर (ret)
		जाओ err_rings;

	/* map all of the rings to the q_vectors */
	i40e_vsi_map_rings_to_vectors(vsi);
	वापस vsi;

err_rings:
	i40e_vsi_मुक्त_q_vectors(vsi);
	अगर (vsi->netdev_रेजिस्टरed) अणु
		vsi->netdev_रेजिस्टरed = false;
		unरेजिस्टर_netdev(vsi->netdev);
		मुक्त_netdev(vsi->netdev);
		vsi->netdev = शून्य;
	पूर्ण
	i40e_aq_delete_element(&pf->hw, vsi->seid, शून्य);
err_vsi:
	i40e_vsi_clear(vsi);
	वापस शून्य;
पूर्ण

/**
 * i40e_vsi_setup - Set up a VSI by a given type
 * @pf: board निजी काष्ठाure
 * @type: VSI type
 * @uplink_seid: the चयन element to link to
 * @param1: usage depends upon VSI type. For VF types, indicates VF id
 *
 * This allocates the sw VSI काष्ठाure and its queue resources, then add a VSI
 * to the identअगरied VEB.
 *
 * Returns poपूर्णांकer to the successfully allocated and configure VSI sw काष्ठा on
 * success, otherwise वापसs शून्य on failure.
 **/
काष्ठा i40e_vsi *i40e_vsi_setup(काष्ठा i40e_pf *pf, u8 type,
				u16 uplink_seid, u32 param1)
अणु
	काष्ठा i40e_vsi *vsi = शून्य;
	काष्ठा i40e_veb *veb = शून्य;
	u16 alloc_queue_pairs;
	पूर्णांक ret, i;
	पूर्णांक v_idx;

	/* The requested uplink_seid must be either
	 *     - the PF's port seid
	 *              no VEB is needed because this is the PF
	 *              or this is a Flow Director special हाल VSI
	 *     - seid of an existing VEB
	 *     - seid of a VSI that owns an existing VEB
	 *     - seid of a VSI that करोesn't own a VEB
	 *              a new VEB is created and the VSI becomes the owner
	 *     - seid of the PF VSI, which is what creates the first VEB
	 *              this is a special हाल of the previous
	 *
	 * Find which uplink_seid we were given and create a new VEB अगर needed
	 */
	क्रम (i = 0; i < I40E_MAX_VEB; i++) अणु
		अगर (pf->veb[i] && pf->veb[i]->seid == uplink_seid) अणु
			veb = pf->veb[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!veb && uplink_seid != pf->mac_seid) अणु

		क्रम (i = 0; i < pf->num_alloc_vsi; i++) अणु
			अगर (pf->vsi[i] && pf->vsi[i]->seid == uplink_seid) अणु
				vsi = pf->vsi[i];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!vsi) अणु
			dev_info(&pf->pdev->dev, "no such uplink_seid %d\n",
				 uplink_seid);
			वापस शून्य;
		पूर्ण

		अगर (vsi->uplink_seid == pf->mac_seid)
			veb = i40e_veb_setup(pf, 0, pf->mac_seid, vsi->seid,
					     vsi->tc_config.enabled_tc);
		अन्यथा अगर ((vsi->flags & I40E_VSI_FLAG_VEB_OWNER) == 0)
			veb = i40e_veb_setup(pf, 0, vsi->uplink_seid, vsi->seid,
					     vsi->tc_config.enabled_tc);
		अगर (veb) अणु
			अगर (vsi->seid != pf->vsi[pf->lan_vsi]->seid) अणु
				dev_info(&vsi->back->pdev->dev,
					 "New VSI creation error, uplink seid of LAN VSI expected.\n");
				वापस शून्य;
			पूर्ण
			/* We come up by शेष in VEPA mode अगर SRIOV is not
			 * alपढ़ोy enabled, in which हाल we can't क्रमce VEPA
			 * mode.
			 */
			अगर (!(pf->flags & I40E_FLAG_VEB_MODE_ENABLED)) अणु
				veb->bridge_mode = BRIDGE_MODE_VEPA;
				pf->flags &= ~I40E_FLAG_VEB_MODE_ENABLED;
			पूर्ण
			i40e_config_bridge_mode(veb);
		पूर्ण
		क्रम (i = 0; i < I40E_MAX_VEB && !veb; i++) अणु
			अगर (pf->veb[i] && pf->veb[i]->seid == vsi->uplink_seid)
				veb = pf->veb[i];
		पूर्ण
		अगर (!veb) अणु
			dev_info(&pf->pdev->dev, "couldn't add VEB\n");
			वापस शून्य;
		पूर्ण

		vsi->flags |= I40E_VSI_FLAG_VEB_OWNER;
		uplink_seid = veb->seid;
	पूर्ण

	/* get vsi sw काष्ठा */
	v_idx = i40e_vsi_mem_alloc(pf, type);
	अगर (v_idx < 0)
		जाओ err_alloc;
	vsi = pf->vsi[v_idx];
	अगर (!vsi)
		जाओ err_alloc;
	vsi->type = type;
	vsi->veb_idx = (veb ? veb->idx : I40E_NO_VEB);

	अगर (type == I40E_VSI_MAIN)
		pf->lan_vsi = v_idx;
	अन्यथा अगर (type == I40E_VSI_SRIOV)
		vsi->vf_id = param1;
	/* assign it some queues */
	alloc_queue_pairs = vsi->alloc_queue_pairs *
			    (i40e_enabled_xdp_vsi(vsi) ? 2 : 1);

	ret = i40e_get_lump(pf, pf->qp_pile, alloc_queue_pairs, vsi->idx);
	अगर (ret < 0) अणु
		dev_info(&pf->pdev->dev,
			 "failed to get tracking for %d queues for VSI %d err=%d\n",
			 alloc_queue_pairs, vsi->seid, ret);
		जाओ err_vsi;
	पूर्ण
	vsi->base_queue = ret;

	/* get a VSI from the hardware */
	vsi->uplink_seid = uplink_seid;
	ret = i40e_add_vsi(vsi);
	अगर (ret)
		जाओ err_vsi;

	चयन (vsi->type) अणु
	/* setup the netdev अगर needed */
	हाल I40E_VSI_MAIN:
	हाल I40E_VSI_VMDQ2:
		ret = i40e_config_netdev(vsi);
		अगर (ret)
			जाओ err_netdev;
		ret = रेजिस्टर_netdev(vsi->netdev);
		अगर (ret)
			जाओ err_netdev;
		vsi->netdev_रेजिस्टरed = true;
		netअगर_carrier_off(vsi->netdev);
#अगर_घोषित CONFIG_I40E_DCB
		/* Setup DCB netlink पूर्णांकerface */
		i40e_dcbnl_setup(vsi);
#पूर्ण_अगर /* CONFIG_I40E_DCB */
		fallthrough;
	हाल I40E_VSI_Fसूची:
		/* set up vectors and rings अगर needed */
		ret = i40e_vsi_setup_vectors(vsi);
		अगर (ret)
			जाओ err_msix;

		ret = i40e_alloc_rings(vsi);
		अगर (ret)
			जाओ err_rings;

		/* map all of the rings to the q_vectors */
		i40e_vsi_map_rings_to_vectors(vsi);

		i40e_vsi_reset_stats(vsi);
		अवरोध;
	शेष:
		/* no netdev or rings क्रम the other VSI types */
		अवरोध;
	पूर्ण

	अगर ((pf->hw_features & I40E_HW_RSS_AQ_CAPABLE) &&
	    (vsi->type == I40E_VSI_VMDQ2)) अणु
		ret = i40e_vsi_config_rss(vsi);
	पूर्ण
	वापस vsi;

err_rings:
	i40e_vsi_मुक्त_q_vectors(vsi);
err_msix:
	अगर (vsi->netdev_रेजिस्टरed) अणु
		vsi->netdev_रेजिस्टरed = false;
		unरेजिस्टर_netdev(vsi->netdev);
		मुक्त_netdev(vsi->netdev);
		vsi->netdev = शून्य;
	पूर्ण
err_netdev:
	i40e_aq_delete_element(&pf->hw, vsi->seid, शून्य);
err_vsi:
	i40e_vsi_clear(vsi);
err_alloc:
	वापस शून्य;
पूर्ण

/**
 * i40e_veb_get_bw_info - Query VEB BW inक्रमmation
 * @veb: the veb to query
 *
 * Query the Tx scheduler BW configuration data क्रम given VEB
 **/
अटल पूर्णांक i40e_veb_get_bw_info(काष्ठा i40e_veb *veb)
अणु
	काष्ठा i40e_aqc_query_चयनing_comp_ets_config_resp ets_data;
	काष्ठा i40e_aqc_query_चयनing_comp_bw_config_resp bw_data;
	काष्ठा i40e_pf *pf = veb->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 tc_bw_max;
	पूर्णांक ret = 0;
	पूर्णांक i;

	ret = i40e_aq_query_चयन_comp_bw_config(hw, veb->seid,
						  &bw_data, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "query veb bw config failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, hw->aq.asq_last_status));
		जाओ out;
	पूर्ण

	ret = i40e_aq_query_चयन_comp_ets_config(hw, veb->seid,
						   &ets_data, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "query veb bw ets config failed, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, hw->aq.asq_last_status));
		जाओ out;
	पूर्ण

	veb->bw_limit = le16_to_cpu(ets_data.port_bw_limit);
	veb->bw_max_quanta = ets_data.tc_bw_max;
	veb->is_असल_credits = bw_data.असलolute_credits_enable;
	veb->enabled_tc = ets_data.tc_valid_bits;
	tc_bw_max = le16_to_cpu(bw_data.tc_bw_max[0]) |
		    (le16_to_cpu(bw_data.tc_bw_max[1]) << 16);
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		veb->bw_tc_share_credits[i] = bw_data.tc_bw_share_credits[i];
		veb->bw_tc_limit_credits[i] =
					le16_to_cpu(bw_data.tc_bw_limits[i]);
		veb->bw_tc_max_quanta[i] = ((tc_bw_max >> (i*4)) & 0x7);
	पूर्ण

out:
	वापस ret;
पूर्ण

/**
 * i40e_veb_mem_alloc - Allocates the next available काष्ठा veb in the PF
 * @pf: board निजी काष्ठाure
 *
 * On error: वापसs error code (negative)
 * On success: वापसs vsi index in PF (positive)
 **/
अटल पूर्णांक i40e_veb_mem_alloc(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा i40e_veb *veb;
	पूर्णांक i;

	/* Need to protect the allocation of चयन elements at the PF level */
	mutex_lock(&pf->चयन_mutex);

	/* VEB list may be fragmented अगर VEB creation/deकाष्ठाion has
	 * been happening.  We can afक्रमd to करो a quick scan to look
	 * क्रम any मुक्त slots in the list.
	 *
	 * find next empty veb slot, looping back around अगर necessary
	 */
	i = 0;
	जबतक ((i < I40E_MAX_VEB) && (pf->veb[i] != शून्य))
		i++;
	अगर (i >= I40E_MAX_VEB) अणु
		ret = -ENOMEM;
		जाओ err_alloc_veb;  /* out of VEB slots! */
	पूर्ण

	veb = kzalloc(माप(*veb), GFP_KERNEL);
	अगर (!veb) अणु
		ret = -ENOMEM;
		जाओ err_alloc_veb;
	पूर्ण
	veb->pf = pf;
	veb->idx = i;
	veb->enabled_tc = 1;

	pf->veb[i] = veb;
	ret = i;
err_alloc_veb:
	mutex_unlock(&pf->चयन_mutex);
	वापस ret;
पूर्ण

/**
 * i40e_चयन_branch_release - Delete a branch of the चयन tree
 * @branch: where to start deleting
 *
 * This uses recursion to find the tips of the branch to be
 * हटाओd, deleting until we get back to and can delete this VEB.
 **/
अटल व्योम i40e_चयन_branch_release(काष्ठा i40e_veb *branch)
अणु
	काष्ठा i40e_pf *pf = branch->pf;
	u16 branch_seid = branch->seid;
	u16 veb_idx = branch->idx;
	पूर्णांक i;

	/* release any VEBs on this VEB - RECURSION */
	क्रम (i = 0; i < I40E_MAX_VEB; i++) अणु
		अगर (!pf->veb[i])
			जारी;
		अगर (pf->veb[i]->uplink_seid == branch->seid)
			i40e_चयन_branch_release(pf->veb[i]);
	पूर्ण

	/* Release the VSIs on this VEB, but not the owner VSI.
	 *
	 * NOTE: Removing the last VSI on a VEB has the SIDE EFFECT of removing
	 *       the VEB itself, so करोn't use (*branch) after this loop.
	 */
	क्रम (i = 0; i < pf->num_alloc_vsi; i++) अणु
		अगर (!pf->vsi[i])
			जारी;
		अगर (pf->vsi[i]->uplink_seid == branch_seid &&
		   (pf->vsi[i]->flags & I40E_VSI_FLAG_VEB_OWNER) == 0) अणु
			i40e_vsi_release(pf->vsi[i]);
		पूर्ण
	पूर्ण

	/* There's one corner हाल where the VEB might not have been
	 * हटाओd, so द्विगुन check it here and हटाओ it अगर needed.
	 * This हाल happens अगर the veb was created from the debugfs
	 * commands and no VSIs were added to it.
	 */
	अगर (pf->veb[veb_idx])
		i40e_veb_release(pf->veb[veb_idx]);
पूर्ण

/**
 * i40e_veb_clear - हटाओ veb काष्ठा
 * @veb: the veb to हटाओ
 **/
अटल व्योम i40e_veb_clear(काष्ठा i40e_veb *veb)
अणु
	अगर (!veb)
		वापस;

	अगर (veb->pf) अणु
		काष्ठा i40e_pf *pf = veb->pf;

		mutex_lock(&pf->चयन_mutex);
		अगर (pf->veb[veb->idx] == veb)
			pf->veb[veb->idx] = शून्य;
		mutex_unlock(&pf->चयन_mutex);
	पूर्ण

	kमुक्त(veb);
पूर्ण

/**
 * i40e_veb_release - Delete a VEB and मुक्त its resources
 * @veb: the VEB being हटाओd
 **/
व्योम i40e_veb_release(काष्ठा i40e_veb *veb)
अणु
	काष्ठा i40e_vsi *vsi = शून्य;
	काष्ठा i40e_pf *pf;
	पूर्णांक i, n = 0;

	pf = veb->pf;

	/* find the reमुख्यing VSI and check क्रम extras */
	क्रम (i = 0; i < pf->num_alloc_vsi; i++) अणु
		अगर (pf->vsi[i] && pf->vsi[i]->uplink_seid == veb->seid) अणु
			n++;
			vsi = pf->vsi[i];
		पूर्ण
	पूर्ण
	अगर (n != 1) अणु
		dev_info(&pf->pdev->dev,
			 "can't remove VEB %d with %d VSIs left\n",
			 veb->seid, n);
		वापस;
	पूर्ण

	/* move the reमुख्यing VSI to uplink veb */
	vsi->flags &= ~I40E_VSI_FLAG_VEB_OWNER;
	अगर (veb->uplink_seid) अणु
		vsi->uplink_seid = veb->uplink_seid;
		अगर (veb->uplink_seid == pf->mac_seid)
			vsi->veb_idx = I40E_NO_VEB;
		अन्यथा
			vsi->veb_idx = veb->veb_idx;
	पूर्ण अन्यथा अणु
		/* भग्नing VEB */
		vsi->uplink_seid = pf->vsi[pf->lan_vsi]->uplink_seid;
		vsi->veb_idx = pf->vsi[pf->lan_vsi]->veb_idx;
	पूर्ण

	i40e_aq_delete_element(&pf->hw, veb->seid, शून्य);
	i40e_veb_clear(veb);
पूर्ण

/**
 * i40e_add_veb - create the VEB in the चयन
 * @veb: the VEB to be instantiated
 * @vsi: the controlling VSI
 **/
अटल पूर्णांक i40e_add_veb(काष्ठा i40e_veb *veb, काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_pf *pf = veb->pf;
	bool enable_stats = !!(pf->flags & I40E_FLAG_VEB_STATS_ENABLED);
	पूर्णांक ret;

	ret = i40e_aq_add_veb(&pf->hw, veb->uplink_seid, vsi->seid,
			      veb->enabled_tc, false,
			      &veb->seid, enable_stats, शून्य);

	/* get a VEB from the hardware */
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't add VEB, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EPERM;
	पूर्ण

	/* get statistics counter */
	ret = i40e_aq_get_veb_parameters(&pf->hw, veb->seid, शून्य, शून्य,
					 &veb->stats_idx, शून्य, शून्य, शून्य);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get VEB statistics idx, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EPERM;
	पूर्ण
	ret = i40e_veb_get_bw_info(veb);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't get VEB bw info, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		i40e_aq_delete_element(&pf->hw, veb->seid, शून्य);
		वापस -ENOENT;
	पूर्ण

	vsi->uplink_seid = veb->seid;
	vsi->veb_idx = veb->idx;
	vsi->flags |= I40E_VSI_FLAG_VEB_OWNER;

	वापस 0;
पूर्ण

/**
 * i40e_veb_setup - Set up a VEB
 * @pf: board निजी काष्ठाure
 * @flags: VEB setup flags
 * @uplink_seid: the चयन element to link to
 * @vsi_seid: the initial VSI seid
 * @enabled_tc: Enabled TC bit-map
 *
 * This allocates the sw VEB काष्ठाure and links it पूर्णांकo the चयन
 * It is possible and legal क्रम this to be a duplicate of an alपढ़ोy
 * existing VEB.  It is also possible क्रम both uplink and vsi seids
 * to be zero, in order to create a भग्नing VEB.
 *
 * Returns poपूर्णांकer to the successfully allocated VEB sw काष्ठा on
 * success, otherwise वापसs शून्य on failure.
 **/
काष्ठा i40e_veb *i40e_veb_setup(काष्ठा i40e_pf *pf, u16 flags,
				u16 uplink_seid, u16 vsi_seid,
				u8 enabled_tc)
अणु
	काष्ठा i40e_veb *veb, *uplink_veb = शून्य;
	पूर्णांक vsi_idx, veb_idx;
	पूर्णांक ret;

	/* अगर one seid is 0, the other must be 0 to create a भग्नing relay */
	अगर ((uplink_seid == 0 || vsi_seid == 0) &&
	    (uplink_seid + vsi_seid != 0)) अणु
		dev_info(&pf->pdev->dev,
			 "one, not both seid's are 0: uplink=%d vsi=%d\n",
			 uplink_seid, vsi_seid);
		वापस शून्य;
	पूर्ण

	/* make sure there is such a vsi and uplink */
	क्रम (vsi_idx = 0; vsi_idx < pf->num_alloc_vsi; vsi_idx++)
		अगर (pf->vsi[vsi_idx] && pf->vsi[vsi_idx]->seid == vsi_seid)
			अवरोध;
	अगर (vsi_idx == pf->num_alloc_vsi && vsi_seid != 0) अणु
		dev_info(&pf->pdev->dev, "vsi seid %d not found\n",
			 vsi_seid);
		वापस शून्य;
	पूर्ण

	अगर (uplink_seid && uplink_seid != pf->mac_seid) अणु
		क्रम (veb_idx = 0; veb_idx < I40E_MAX_VEB; veb_idx++) अणु
			अगर (pf->veb[veb_idx] &&
			    pf->veb[veb_idx]->seid == uplink_seid) अणु
				uplink_veb = pf->veb[veb_idx];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!uplink_veb) अणु
			dev_info(&pf->pdev->dev,
				 "uplink seid %d not found\n", uplink_seid);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* get veb sw काष्ठा */
	veb_idx = i40e_veb_mem_alloc(pf);
	अगर (veb_idx < 0)
		जाओ err_alloc;
	veb = pf->veb[veb_idx];
	veb->flags = flags;
	veb->uplink_seid = uplink_seid;
	veb->veb_idx = (uplink_veb ? uplink_veb->idx : I40E_NO_VEB);
	veb->enabled_tc = (enabled_tc ? enabled_tc : 0x1);

	/* create the VEB in the चयन */
	ret = i40e_add_veb(veb, pf->vsi[vsi_idx]);
	अगर (ret)
		जाओ err_veb;
	अगर (vsi_idx == pf->lan_vsi)
		pf->lan_veb = veb->idx;

	वापस veb;

err_veb:
	i40e_veb_clear(veb);
err_alloc:
	वापस शून्य;
पूर्ण

/**
 * i40e_setup_pf_चयन_element - set PF vars based on चयन type
 * @pf: board निजी काष्ठाure
 * @ele: element we are building info from
 * @num_reported: total number of elements
 * @prपूर्णांकconfig: should we prपूर्णांक the contents
 *
 * helper function to assist in extracting a few useful SEID values.
 **/
अटल व्योम i40e_setup_pf_चयन_element(काष्ठा i40e_pf *pf,
				काष्ठा i40e_aqc_चयन_config_element_resp *ele,
				u16 num_reported, bool prपूर्णांकconfig)
अणु
	u16 करोwnlink_seid = le16_to_cpu(ele->करोwnlink_seid);
	u16 uplink_seid = le16_to_cpu(ele->uplink_seid);
	u8 element_type = ele->element_type;
	u16 seid = le16_to_cpu(ele->seid);

	अगर (prपूर्णांकconfig)
		dev_info(&pf->pdev->dev,
			 "type=%d seid=%d uplink=%d downlink=%d\n",
			 element_type, seid, uplink_seid, करोwnlink_seid);

	चयन (element_type) अणु
	हाल I40E_SWITCH_ELEMENT_TYPE_MAC:
		pf->mac_seid = seid;
		अवरोध;
	हाल I40E_SWITCH_ELEMENT_TYPE_VEB:
		/* Main VEB? */
		अगर (uplink_seid != pf->mac_seid)
			अवरोध;
		अगर (pf->lan_veb >= I40E_MAX_VEB) अणु
			पूर्णांक v;

			/* find existing or अन्यथा empty VEB */
			क्रम (v = 0; v < I40E_MAX_VEB; v++) अणु
				अगर (pf->veb[v] && (pf->veb[v]->seid == seid)) अणु
					pf->lan_veb = v;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (pf->lan_veb >= I40E_MAX_VEB) अणु
				v = i40e_veb_mem_alloc(pf);
				अगर (v < 0)
					अवरोध;
				pf->lan_veb = v;
			पूर्ण
		पूर्ण
		अगर (pf->lan_veb >= I40E_MAX_VEB)
			अवरोध;

		pf->veb[pf->lan_veb]->seid = seid;
		pf->veb[pf->lan_veb]->uplink_seid = pf->mac_seid;
		pf->veb[pf->lan_veb]->pf = pf;
		pf->veb[pf->lan_veb]->veb_idx = I40E_NO_VEB;
		अवरोध;
	हाल I40E_SWITCH_ELEMENT_TYPE_VSI:
		अगर (num_reported != 1)
			अवरोध;
		/* This is immediately after a reset so we can assume this is
		 * the PF's VSI
		 */
		pf->mac_seid = uplink_seid;
		pf->pf_seid = करोwnlink_seid;
		pf->मुख्य_vsi_seid = seid;
		अगर (prपूर्णांकconfig)
			dev_info(&pf->pdev->dev,
				 "pf_seid=%d main_vsi_seid=%d\n",
				 pf->pf_seid, pf->मुख्य_vsi_seid);
		अवरोध;
	हाल I40E_SWITCH_ELEMENT_TYPE_PF:
	हाल I40E_SWITCH_ELEMENT_TYPE_VF:
	हाल I40E_SWITCH_ELEMENT_TYPE_EMP:
	हाल I40E_SWITCH_ELEMENT_TYPE_BMC:
	हाल I40E_SWITCH_ELEMENT_TYPE_PE:
	हाल I40E_SWITCH_ELEMENT_TYPE_PA:
		/* ignore these क्रम now */
		अवरोध;
	शेष:
		dev_info(&pf->pdev->dev, "unknown element type=%d seid=%d\n",
			 element_type, seid);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40e_fetch_चयन_configuration - Get चयन config from firmware
 * @pf: board निजी काष्ठाure
 * @prपूर्णांकconfig: should we prपूर्णांक the contents
 *
 * Get the current चयन configuration from the device and
 * extract a few useful SEID values.
 **/
पूर्णांक i40e_fetch_चयन_configuration(काष्ठा i40e_pf *pf, bool prपूर्णांकconfig)
अणु
	काष्ठा i40e_aqc_get_चयन_config_resp *sw_config;
	u16 next_seid = 0;
	पूर्णांक ret = 0;
	u8 *aq_buf;
	पूर्णांक i;

	aq_buf = kzalloc(I40E_AQ_LARGE_BUF, GFP_KERNEL);
	अगर (!aq_buf)
		वापस -ENOMEM;

	sw_config = (काष्ठा i40e_aqc_get_चयन_config_resp *)aq_buf;
	करो अणु
		u16 num_reported, num_total;

		ret = i40e_aq_get_चयन_config(&pf->hw, sw_config,
						I40E_AQ_LARGE_BUF,
						&next_seid, शून्य);
		अगर (ret) अणु
			dev_info(&pf->pdev->dev,
				 "get switch config failed err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			kमुक्त(aq_buf);
			वापस -ENOENT;
		पूर्ण

		num_reported = le16_to_cpu(sw_config->header.num_reported);
		num_total = le16_to_cpu(sw_config->header.num_total);

		अगर (prपूर्णांकconfig)
			dev_info(&pf->pdev->dev,
				 "header: %d reported %d total\n",
				 num_reported, num_total);

		क्रम (i = 0; i < num_reported; i++) अणु
			काष्ठा i40e_aqc_चयन_config_element_resp *ele =
				&sw_config->element[i];

			i40e_setup_pf_चयन_element(pf, ele, num_reported,
						     prपूर्णांकconfig);
		पूर्ण
	पूर्ण जबतक (next_seid != 0);

	kमुक्त(aq_buf);
	वापस ret;
पूर्ण

/**
 * i40e_setup_pf_चयन - Setup the HW चयन on startup or after reset
 * @pf: board निजी काष्ठाure
 * @reinit: अगर the Main VSI needs to re-initialized.
 *
 * Returns 0 on success, negative value on failure
 **/
अटल पूर्णांक i40e_setup_pf_चयन(काष्ठा i40e_pf *pf, bool reinit)
अणु
	u16 flags = 0;
	पूर्णांक ret;

	/* find out what's out there alपढ़ोy */
	ret = i40e_fetch_चयन_configuration(pf, false);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "couldn't fetch switch config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस ret;
	पूर्ण
	i40e_pf_reset_stats(pf);

	/* set the चयन config bit क्रम the whole device to
	 * support limited promisc or true promisc
	 * when user requests promisc. The शेष is limited
	 * promisc.
	*/

	अगर ((pf->hw.pf_id == 0) &&
	    !(pf->flags & I40E_FLAG_TRUE_PROMISC_SUPPORT)) अणु
		flags = I40E_AQ_SET_SWITCH_CFG_PROMISC;
		pf->last_sw_conf_flags = flags;
	पूर्ण

	अगर (pf->hw.pf_id == 0) अणु
		u16 valid_flags;

		valid_flags = I40E_AQ_SET_SWITCH_CFG_PROMISC;
		ret = i40e_aq_set_चयन_config(&pf->hw, flags, valid_flags, 0,
						शून्य);
		अगर (ret && pf->hw.aq.asq_last_status != I40E_AQ_RC_ESRCH) अणु
			dev_info(&pf->pdev->dev,
				 "couldn't set switch config bits, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			/* not a fatal problem, just keep going */
		पूर्ण
		pf->last_sw_conf_valid_flags = valid_flags;
	पूर्ण

	/* first समय setup */
	अगर (pf->lan_vsi == I40E_NO_VSI || reinit) अणु
		काष्ठा i40e_vsi *vsi = शून्य;
		u16 uplink_seid;

		/* Set up the PF VSI associated with the PF's मुख्य VSI
		 * that is alपढ़ोy in the HW चयन
		 */
		अगर (pf->lan_veb < I40E_MAX_VEB && pf->veb[pf->lan_veb])
			uplink_seid = pf->veb[pf->lan_veb]->seid;
		अन्यथा
			uplink_seid = pf->mac_seid;
		अगर (pf->lan_vsi == I40E_NO_VSI)
			vsi = i40e_vsi_setup(pf, I40E_VSI_MAIN, uplink_seid, 0);
		अन्यथा अगर (reinit)
			vsi = i40e_vsi_reinit_setup(pf->vsi[pf->lan_vsi]);
		अगर (!vsi) अणु
			dev_info(&pf->pdev->dev, "setup of MAIN VSI failed\n");
			i40e_cloud_filter_निकास(pf);
			i40e_fdir_tearकरोwn(pf);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* क्रमce a reset of TC and queue layout configurations */
		u8 enabled_tc = pf->vsi[pf->lan_vsi]->tc_config.enabled_tc;

		pf->vsi[pf->lan_vsi]->tc_config.enabled_tc = 0;
		pf->vsi[pf->lan_vsi]->seid = pf->मुख्य_vsi_seid;
		i40e_vsi_config_tc(pf->vsi[pf->lan_vsi], enabled_tc);
	पूर्ण
	i40e_vlan_stripping_disable(pf->vsi[pf->lan_vsi]);

	i40e_fdir_sb_setup(pf);

	/* Setup अटल PF queue filter control settings */
	ret = i40e_setup_pf_filter_control(pf);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev, "setup_pf_filter_control failed: %d\n",
			 ret);
		/* Failure here should not stop continuing other steps */
	पूर्ण

	/* enable RSS in the HW, even क्रम only one queue, as the stack can use
	 * the hash
	 */
	अगर ((pf->flags & I40E_FLAG_RSS_ENABLED))
		i40e_pf_config_rss(pf);

	/* fill in link inक्रमmation and enable LSE reporting */
	i40e_link_event(pf);

	/* Initialize user-specअगरic link properties */
	pf->fc_स्वतःneg_status = ((pf->hw.phy.link_info.an_info &
				  I40E_AQ_AN_COMPLETED) ? true : false);

	i40e_ptp_init(pf);

	/* repopulate tunnel port filters */
	udp_tunnel_nic_reset_ntf(pf->vsi[pf->lan_vsi]->netdev);

	वापस ret;
पूर्ण

/**
 * i40e_determine_queue_usage - Work out queue distribution
 * @pf: board निजी काष्ठाure
 **/
अटल व्योम i40e_determine_queue_usage(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक queues_left;
	पूर्णांक q_max;

	pf->num_lan_qps = 0;

	/* Find the max queues to be put पूर्णांकo basic use.  We'll always be
	 * using TC0, whether or not DCB is running, and TC0 will get the
	 * big RSS set.
	 */
	queues_left = pf->hw.func_caps.num_tx_qp;

	अगर ((queues_left == 1) ||
	    !(pf->flags & I40E_FLAG_MSIX_ENABLED)) अणु
		/* one qp क्रम PF, no queues क्रम anything अन्यथा */
		queues_left = 0;
		pf->alloc_rss_size = pf->num_lan_qps = 1;

		/* make sure all the fancies are disabled */
		pf->flags &= ~(I40E_FLAG_RSS_ENABLED	|
			       I40E_FLAG_IWARP_ENABLED	|
			       I40E_FLAG_FD_SB_ENABLED	|
			       I40E_FLAG_FD_ATR_ENABLED	|
			       I40E_FLAG_DCB_CAPABLE	|
			       I40E_FLAG_DCB_ENABLED	|
			       I40E_FLAG_SRIOV_ENABLED	|
			       I40E_FLAG_VMDQ_ENABLED);
		pf->flags |= I40E_FLAG_FD_SB_INACTIVE;
	पूर्ण अन्यथा अगर (!(pf->flags & (I40E_FLAG_RSS_ENABLED |
				  I40E_FLAG_FD_SB_ENABLED |
				  I40E_FLAG_FD_ATR_ENABLED |
				  I40E_FLAG_DCB_CAPABLE))) अणु
		/* one qp क्रम PF */
		pf->alloc_rss_size = pf->num_lan_qps = 1;
		queues_left -= pf->num_lan_qps;

		pf->flags &= ~(I40E_FLAG_RSS_ENABLED	|
			       I40E_FLAG_IWARP_ENABLED	|
			       I40E_FLAG_FD_SB_ENABLED	|
			       I40E_FLAG_FD_ATR_ENABLED	|
			       I40E_FLAG_DCB_ENABLED	|
			       I40E_FLAG_VMDQ_ENABLED);
		pf->flags |= I40E_FLAG_FD_SB_INACTIVE;
	पूर्ण अन्यथा अणु
		/* Not enough queues क्रम all TCs */
		अगर ((pf->flags & I40E_FLAG_DCB_CAPABLE) &&
		    (queues_left < I40E_MAX_TRAFFIC_CLASS)) अणु
			pf->flags &= ~(I40E_FLAG_DCB_CAPABLE |
					I40E_FLAG_DCB_ENABLED);
			dev_info(&pf->pdev->dev, "not enough queues for DCB. DCB is disabled.\n");
		पूर्ण

		/* limit lan qps to the smaller of qps, cpus or msix */
		q_max = max_t(पूर्णांक, pf->rss_size_max, num_online_cpus());
		q_max = min_t(पूर्णांक, q_max, pf->hw.func_caps.num_tx_qp);
		q_max = min_t(पूर्णांक, q_max, pf->hw.func_caps.num_msix_vectors);
		pf->num_lan_qps = q_max;

		queues_left -= pf->num_lan_qps;
	पूर्ण

	अगर (pf->flags & I40E_FLAG_FD_SB_ENABLED) अणु
		अगर (queues_left > 1) अणु
			queues_left -= 1; /* save 1 queue क्रम FD */
		पूर्ण अन्यथा अणु
			pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
			pf->flags |= I40E_FLAG_FD_SB_INACTIVE;
			dev_info(&pf->pdev->dev, "not enough queues for Flow Director. Flow Director feature is disabled\n");
		पूर्ण
	पूर्ण

	अगर ((pf->flags & I40E_FLAG_SRIOV_ENABLED) &&
	    pf->num_vf_qps && pf->num_req_vfs && queues_left) अणु
		pf->num_req_vfs = min_t(पूर्णांक, pf->num_req_vfs,
					(queues_left / pf->num_vf_qps));
		queues_left -= (pf->num_req_vfs * pf->num_vf_qps);
	पूर्ण

	अगर ((pf->flags & I40E_FLAG_VMDQ_ENABLED) &&
	    pf->num_vmdq_vsis && pf->num_vmdq_qps && queues_left) अणु
		pf->num_vmdq_vsis = min_t(पूर्णांक, pf->num_vmdq_vsis,
					  (queues_left / pf->num_vmdq_qps));
		queues_left -= (pf->num_vmdq_vsis * pf->num_vmdq_qps);
	पूर्ण

	pf->queues_left = queues_left;
	dev_dbg(&pf->pdev->dev,
		"qs_avail=%d FD SB=%d lan_qs=%d lan_tc0=%d vf=%d*%d vmdq=%d*%d, remaining=%d\n",
		pf->hw.func_caps.num_tx_qp,
		!!(pf->flags & I40E_FLAG_FD_SB_ENABLED),
		pf->num_lan_qps, pf->alloc_rss_size, pf->num_req_vfs,
		pf->num_vf_qps, pf->num_vmdq_vsis, pf->num_vmdq_qps,
		queues_left);
पूर्ण

/**
 * i40e_setup_pf_filter_control - Setup PF अटल filter control
 * @pf: PF to be setup
 *
 * i40e_setup_pf_filter_control sets up a PF's initial filter control
 * settings. If PE/FCoE are enabled then it will also set the per PF
 * based filter sizes required क्रम them. It also enables Flow director,
 * ethertype and macvlan type filter settings क्रम the pf.
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_setup_pf_filter_control(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_filter_control_settings *settings = &pf->filter_settings;

	settings->hash_lut_size = I40E_HASH_LUT_SIZE_128;

	/* Flow Director is enabled */
	अगर (pf->flags & (I40E_FLAG_FD_SB_ENABLED | I40E_FLAG_FD_ATR_ENABLED))
		settings->enable_fdir = true;

	/* Ethtype and MACVLAN filters enabled क्रम PF */
	settings->enable_ethtype = true;
	settings->enable_macvlan = true;

	अगर (i40e_set_filter_control(&pf->hw, settings))
		वापस -ENOENT;

	वापस 0;
पूर्ण

#घोषणा INFO_STRING_LEN 255
#घोषणा REMAIN(__x) (INFO_STRING_LEN - (__x))
अटल व्योम i40e_prपूर्णांक_features(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	अक्षर *buf;
	पूर्णांक i;

	buf = kदो_स्मृति(INFO_STRING_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस;

	i = snम_लिखो(buf, INFO_STRING_LEN, "Features: PF-id[%d]", hw->pf_id);
#अगर_घोषित CONFIG_PCI_IOV
	i += scnम_लिखो(&buf[i], REMAIN(i), " VFs: %d", pf->num_req_vfs);
#पूर्ण_अगर
	i += scnम_लिखो(&buf[i], REMAIN(i), " VSIs: %d QP: %d",
		      pf->hw.func_caps.num_vsis,
		      pf->vsi[pf->lan_vsi]->num_queue_pairs);
	अगर (pf->flags & I40E_FLAG_RSS_ENABLED)
		i += scnम_लिखो(&buf[i], REMAIN(i), " RSS");
	अगर (pf->flags & I40E_FLAG_FD_ATR_ENABLED)
		i += scnम_लिखो(&buf[i], REMAIN(i), " FD_ATR");
	अगर (pf->flags & I40E_FLAG_FD_SB_ENABLED) अणु
		i += scnम_लिखो(&buf[i], REMAIN(i), " FD_SB");
		i += scnम_लिखो(&buf[i], REMAIN(i), " NTUPLE");
	पूर्ण
	अगर (pf->flags & I40E_FLAG_DCB_CAPABLE)
		i += scnम_लिखो(&buf[i], REMAIN(i), " DCB");
	i += scnम_लिखो(&buf[i], REMAIN(i), " VxLAN");
	i += scnम_लिखो(&buf[i], REMAIN(i), " Geneve");
	अगर (pf->flags & I40E_FLAG_PTP)
		i += scnम_लिखो(&buf[i], REMAIN(i), " PTP");
	अगर (pf->flags & I40E_FLAG_VEB_MODE_ENABLED)
		i += scnम_लिखो(&buf[i], REMAIN(i), " VEB");
	अन्यथा
		i += scnम_लिखो(&buf[i], REMAIN(i), " VEPA");

	dev_info(&pf->pdev->dev, "%s\n", buf);
	kमुक्त(buf);
	WARN_ON(i > INFO_STRING_LEN);
पूर्ण

/**
 * i40e_get_platक्रमm_mac_addr - get platक्रमm-specअगरic MAC address
 * @pdev: PCI device inक्रमmation काष्ठा
 * @pf: board निजी काष्ठाure
 *
 * Look up the MAC address क्रम the device. First we'll try
 * eth_platक्रमm_get_mac_address, which will check Open Firmware, or arch
 * specअगरic fallback. Otherwise, we'll शेष to the stored value in
 * firmware.
 **/
अटल व्योम i40e_get_platक्रमm_mac_addr(काष्ठा pci_dev *pdev, काष्ठा i40e_pf *pf)
अणु
	अगर (eth_platक्रमm_get_mac_address(&pdev->dev, pf->hw.mac.addr))
		i40e_get_mac_addr(&pf->hw, pf->hw.mac.addr);
पूर्ण

/**
 * i40e_set_fec_in_flags - helper function क्रम setting FEC options in flags
 * @fec_cfg: FEC option to set in flags
 * @flags: ptr to flags in which we set FEC option
 **/
व्योम i40e_set_fec_in_flags(u8 fec_cfg, u32 *flags)
अणु
	अगर (fec_cfg & I40E_AQ_SET_FEC_AUTO)
		*flags |= I40E_FLAG_RS_FEC | I40E_FLAG_BASE_R_FEC;
	अगर ((fec_cfg & I40E_AQ_SET_FEC_REQUEST_RS) ||
	    (fec_cfg & I40E_AQ_SET_FEC_ABILITY_RS)) अणु
		*flags |= I40E_FLAG_RS_FEC;
		*flags &= ~I40E_FLAG_BASE_R_FEC;
	पूर्ण
	अगर ((fec_cfg & I40E_AQ_SET_FEC_REQUEST_KR) ||
	    (fec_cfg & I40E_AQ_SET_FEC_ABILITY_KR)) अणु
		*flags |= I40E_FLAG_BASE_R_FEC;
		*flags &= ~I40E_FLAG_RS_FEC;
	पूर्ण
	अगर (fec_cfg == 0)
		*flags &= ~(I40E_FLAG_RS_FEC | I40E_FLAG_BASE_R_FEC);
पूर्ण

/**
 * i40e_check_recovery_mode - check अगर we are running transition firmware
 * @pf: board निजी काष्ठाure
 *
 * Check रेजिस्टरs indicating the firmware runs in recovery mode. Sets the
 * appropriate driver state.
 *
 * Returns true अगर the recovery mode was detected, false otherwise
 **/
अटल bool i40e_check_recovery_mode(काष्ठा i40e_pf *pf)
अणु
	u32 val = rd32(&pf->hw, I40E_GL_FWSTS);

	अगर (val & I40E_GL_FWSTS_FWS1B_MASK) अणु
		dev_crit(&pf->pdev->dev, "Firmware recovery mode detected. Limiting functionality.\n");
		dev_crit(&pf->pdev->dev, "Refer to the Intel(R) Ethernet Adapters and Devices User Guide for details on firmware recovery mode.\n");
		set_bit(__I40E_RECOVERY_MODE, pf->state);

		वापस true;
	पूर्ण
	अगर (test_bit(__I40E_RECOVERY_MODE, pf->state))
		dev_info(&pf->pdev->dev, "Please do Power-On Reset to initialize adapter in normal mode with full functionality.\n");

	वापस false;
पूर्ण

/**
 * i40e_pf_loop_reset - perक्रमm reset in a loop.
 * @pf: board निजी काष्ठाure
 *
 * This function is useful when a NIC is about to enter recovery mode.
 * When a NIC's internal data structures are corrupted the NIC's
 * firmware is going to enter recovery mode.
 * Right after a POR it takes about 7 minutes क्रम firmware to enter
 * recovery mode. Until that समय a NIC is in some kind of पूर्णांकermediate
 * state. After that समय period the NIC almost surely enters
 * recovery mode. The only way क्रम a driver to detect पूर्णांकermediate
 * state is to issue a series of pf-resets and check a वापस value.
 * If a PF reset वापसs success then the firmware could be in recovery
 * mode so the caller of this code needs to check क्रम recovery mode
 * अगर this function वापसs success. There is a little chance that
 * firmware will hang in पूर्णांकermediate state क्रमever.
 * Since रुकोing 7 minutes is quite a lot of समय this function रुकोs
 * 10 seconds and then gives up by वापसing an error.
 *
 * Return 0 on success, negative on failure.
 **/
अटल i40e_status i40e_pf_loop_reset(काष्ठा i40e_pf *pf)
अणु
	/* रुको max 10 seconds क्रम PF reset to succeed */
	स्थिर अचिन्हित दीर्घ समय_end = jअगरfies + 10 * HZ;

	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status ret;

	ret = i40e_pf_reset(hw);
	जबतक (ret != I40E_SUCCESS && समय_beक्रमe(jअगरfies, समय_end)) अणु
		usleep_range(10000, 20000);
		ret = i40e_pf_reset(hw);
	पूर्ण

	अगर (ret == I40E_SUCCESS)
		pf->pfr_count++;
	अन्यथा
		dev_info(&pf->pdev->dev, "PF reset failed: %d\n", ret);

	वापस ret;
पूर्ण

/**
 * i40e_check_fw_empr - check अगर FW issued unexpected EMP Reset
 * @pf: board निजी काष्ठाure
 *
 * Check FW रेजिस्टरs to determine अगर FW issued unexpected EMP Reset.
 * Every समय when unexpected EMP Reset occurs the FW increments
 * a counter of unexpected EMP Resets. When the counter reaches 10
 * the FW should enter the Recovery mode
 *
 * Returns true अगर FW issued unexpected EMP Reset
 **/
अटल bool i40e_check_fw_empr(काष्ठा i40e_pf *pf)
अणु
	स्थिर u32 fw_sts = rd32(&pf->hw, I40E_GL_FWSTS) &
			   I40E_GL_FWSTS_FWS1B_MASK;
	वापस (fw_sts > I40E_GL_FWSTS_FWS1B_EMPR_0) &&
	       (fw_sts <= I40E_GL_FWSTS_FWS1B_EMPR_10);
पूर्ण

/**
 * i40e_handle_resets - handle EMP resets and PF resets
 * @pf: board निजी काष्ठाure
 *
 * Handle both EMP resets and PF resets and conclude whether there are
 * any issues regarding these resets. If there are any issues then
 * generate log entry.
 *
 * Return 0 अगर NIC is healthy or negative value when there are issues
 * with resets
 **/
अटल i40e_status i40e_handle_resets(काष्ठा i40e_pf *pf)
अणु
	स्थिर i40e_status pfr = i40e_pf_loop_reset(pf);
	स्थिर bool is_empr = i40e_check_fw_empr(pf);

	अगर (is_empr || pfr != I40E_SUCCESS)
		dev_crit(&pf->pdev->dev, "Entering recovery mode due to repeated FW resets. This may take several minutes. Refer to the Intel(R) Ethernet Adapters and Devices User Guide.\n");

	वापस is_empr ? I40E_ERR_RESET_FAILED : pfr;
पूर्ण

/**
 * i40e_init_recovery_mode - initialize subप्रणालीs needed in recovery mode
 * @pf: board निजी काष्ठाure
 * @hw: ptr to the hardware info
 *
 * This function करोes a minimal setup of all subप्रणालीs needed क्रम running
 * recovery mode.
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_init_recovery_mode(काष्ठा i40e_pf *pf, काष्ठा i40e_hw *hw)
अणु
	काष्ठा i40e_vsi *vsi;
	पूर्णांक err;
	पूर्णांक v_idx;

	pci_save_state(pf->pdev);

	/* set up periodic task facility */
	समयr_setup(&pf->service_समयr, i40e_service_समयr, 0);
	pf->service_समयr_period = HZ;

	INIT_WORK(&pf->service_task, i40e_service_task);
	clear_bit(__I40E_SERVICE_SCHED, pf->state);

	err = i40e_init_पूर्णांकerrupt_scheme(pf);
	अगर (err)
		जाओ err_चयन_setup;

	/* The number of VSIs reported by the FW is the minimum guaranteed
	 * to us; HW supports far more and we share the reमुख्यing pool with
	 * the other PFs. We allocate space क्रम more than the guarantee with
	 * the understanding that we might not get them all later.
	 */
	अगर (pf->hw.func_caps.num_vsis < I40E_MIN_VSI_ALLOC)
		pf->num_alloc_vsi = I40E_MIN_VSI_ALLOC;
	अन्यथा
		pf->num_alloc_vsi = pf->hw.func_caps.num_vsis;

	/* Set up the vsi काष्ठा and our local tracking of the MAIN PF vsi. */
	pf->vsi = kसुस्मृति(pf->num_alloc_vsi, माप(काष्ठा i40e_vsi *),
			  GFP_KERNEL);
	अगर (!pf->vsi) अणु
		err = -ENOMEM;
		जाओ err_चयन_setup;
	पूर्ण

	/* We allocate one VSI which is needed as असलolute minimum
	 * in order to रेजिस्टर the netdev
	 */
	v_idx = i40e_vsi_mem_alloc(pf, I40E_VSI_MAIN);
	अगर (v_idx < 0) अणु
		err = v_idx;
		जाओ err_चयन_setup;
	पूर्ण
	pf->lan_vsi = v_idx;
	vsi = pf->vsi[v_idx];
	अगर (!vsi) अणु
		err = -EFAULT;
		जाओ err_चयन_setup;
	पूर्ण
	vsi->alloc_queue_pairs = 1;
	err = i40e_config_netdev(vsi);
	अगर (err)
		जाओ err_चयन_setup;
	err = रेजिस्टर_netdev(vsi->netdev);
	अगर (err)
		जाओ err_चयन_setup;
	vsi->netdev_रेजिस्टरed = true;
	i40e_dbg_pf_init(pf);

	err = i40e_setup_misc_vector_क्रम_recovery_mode(pf);
	अगर (err)
		जाओ err_चयन_setup;

	/* tell the firmware that we're starting */
	i40e_send_version(pf);

	/* since everything's happy, start the service_task समयr */
	mod_समयr(&pf->service_समयr,
		  round_jअगरfies(jअगरfies + pf->service_समयr_period));

	वापस 0;

err_चयन_setup:
	i40e_reset_पूर्णांकerrupt_capability(pf);
	del_समयr_sync(&pf->service_समयr);
	i40e_shutकरोwn_adminq(hw);
	iounmap(hw->hw_addr);
	pci_disable_pcie_error_reporting(pf->pdev);
	pci_release_mem_regions(pf->pdev);
	pci_disable_device(pf->pdev);
	kमुक्त(pf);

	वापस err;
पूर्ण

/**
 * i40e_probe - Device initialization routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in i40e_pci_tbl
 *
 * i40e_probe initializes a PF identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the PF निजी काष्ठाure,
 * and a hardware reset occur.
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
#अगर_घोषित CONFIG_I40E_DCB
	क्रमागत i40e_get_fw_lldp_status_resp lldp_status;
	i40e_status status;
#पूर्ण_अगर /* CONFIG_I40E_DCB */
	काष्ठा i40e_pf *pf;
	काष्ठा i40e_hw *hw;
	अटल u16 pfs_found;
	u16 wol_nvm_bits;
	u16 link_status;
	पूर्णांक err;
	u32 val;
	u32 i;

	err = pci_enable_device_mem(pdev);
	अगर (err)
		वापस err;

	/* set up क्रम high or low dma */
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err) अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"DMA configuration failed: 0x%x\n", err);
			जाओ err_dma;
		पूर्ण
	पूर्ण

	/* set up pci connections */
	err = pci_request_mem_regions(pdev, i40e_driver_name);
	अगर (err) अणु
		dev_info(&pdev->dev,
			 "pci_request_selected_regions failed %d\n", err);
		जाओ err_pci_reg;
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);
	pci_set_master(pdev);

	/* Now that we have a PCI connection, we need to करो the
	 * low level device setup.  This is primarily setting up
	 * the Admin Queue काष्ठाures and then querying क्रम the
	 * device's current profile inक्रमmation.
	 */
	pf = kzalloc(माप(*pf), GFP_KERNEL);
	अगर (!pf) अणु
		err = -ENOMEM;
		जाओ err_pf_alloc;
	पूर्ण
	pf->next_vsi = 0;
	pf->pdev = pdev;
	set_bit(__I40E_DOWN, pf->state);

	hw = &pf->hw;
	hw->back = pf;

	pf->ioremap_len = min_t(पूर्णांक, pci_resource_len(pdev, 0),
				I40E_MAX_CSR_SPACE);
	/* We believe that the highest रेजिस्टर to पढ़ो is
	 * I40E_GLGEN_STAT_CLEAR, so we check अगर the BAR size
	 * is not less than that beक्रमe mapping to prevent a
	 * kernel panic.
	 */
	अगर (pf->ioremap_len < I40E_GLGEN_STAT_CLEAR) अणु
		dev_err(&pdev->dev, "Cannot map registers, bar size 0x%X too small, aborting\n",
			pf->ioremap_len);
		err = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण
	hw->hw_addr = ioremap(pci_resource_start(pdev, 0), pf->ioremap_len);
	अगर (!hw->hw_addr) अणु
		err = -EIO;
		dev_info(&pdev->dev, "ioremap(0x%04x, 0x%04x) failed: 0x%x\n",
			 (अचिन्हित पूर्णांक)pci_resource_start(pdev, 0),
			 pf->ioremap_len, err);
		जाओ err_ioremap;
	पूर्ण
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	pci_पढ़ो_config_byte(pdev, PCI_REVISION_ID, &hw->revision_id);
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;
	hw->bus.device = PCI_SLOT(pdev->devfn);
	hw->bus.func = PCI_FUNC(pdev->devfn);
	hw->bus.bus_id = pdev->bus->number;
	pf->instance = pfs_found;

	/* Select something other than the 802.1ad ethertype क्रम the
	 * चयन to use पूर्णांकernally and drop on ingress.
	 */
	hw->चयन_tag = 0xffff;
	hw->first_tag = ETH_P_8021AD;
	hw->second_tag = ETH_P_8021Q;

	INIT_LIST_HEAD(&pf->l3_flex_pit_list);
	INIT_LIST_HEAD(&pf->l4_flex_pit_list);
	INIT_LIST_HEAD(&pf->ddp_old_prof);

	/* set up the locks क्रम the AQ, करो this only once in probe
	 * and destroy them only once in हटाओ
	 */
	mutex_init(&hw->aq.asq_mutex);
	mutex_init(&hw->aq.arq_mutex);

	pf->msg_enable = netअगर_msg_init(debug,
					NETIF_MSG_DRV |
					NETIF_MSG_PROBE |
					NETIF_MSG_LINK);
	अगर (debug < -1)
		pf->hw.debug_mask = debug;

	/* करो a special CORER क्रम clearing PXE mode once at init */
	अगर (hw->revision_id == 0 &&
	    (rd32(hw, I40E_GLLAN_RCTL_0) & I40E_GLLAN_RCTL_0_PXE_MODE_MASK)) अणु
		wr32(hw, I40E_GLGEN_RTRIG, I40E_GLGEN_RTRIG_CORER_MASK);
		i40e_flush(hw);
		msleep(200);
		pf->corer_count++;

		i40e_clear_pxe_mode(hw);
	पूर्ण

	/* Reset here to make sure all is clean and to define PF 'n' */
	i40e_clear_hw(hw);

	err = i40e_set_mac_type(hw);
	अगर (err) अणु
		dev_warn(&pdev->dev, "unidentified MAC or BLANK NVM: %d\n",
			 err);
		जाओ err_pf_reset;
	पूर्ण

	err = i40e_handle_resets(pf);
	अगर (err)
		जाओ err_pf_reset;

	i40e_check_recovery_mode(pf);

	अगर (is_kdump_kernel()) अणु
		hw->aq.num_arq_entries = I40E_MIN_ARQ_LEN;
		hw->aq.num_asq_entries = I40E_MIN_ASQ_LEN;
	पूर्ण अन्यथा अणु
		hw->aq.num_arq_entries = I40E_AQ_LEN;
		hw->aq.num_asq_entries = I40E_AQ_LEN;
	पूर्ण
	hw->aq.arq_buf_size = I40E_MAX_AQ_BUF_SIZE;
	hw->aq.asq_buf_size = I40E_MAX_AQ_BUF_SIZE;
	pf->adminq_work_limit = I40E_AQ_WORK_LIMIT;

	snम_लिखो(pf->पूर्णांक_name, माप(pf->पूर्णांक_name) - 1,
		 "%s-%s:misc",
		 dev_driver_string(&pf->pdev->dev), dev_name(&pdev->dev));

	err = i40e_init_shared_code(hw);
	अगर (err) अणु
		dev_warn(&pdev->dev, "unidentified MAC or BLANK NVM: %d\n",
			 err);
		जाओ err_pf_reset;
	पूर्ण

	/* set up a शेष setting क्रम link flow control */
	pf->hw.fc.requested_mode = I40E_FC_NONE;

	err = i40e_init_adminq(hw);
	अगर (err) अणु
		अगर (err == I40E_ERR_FIRMWARE_API_VERSION)
			dev_info(&pdev->dev,
				 "The driver for the device stopped because the NVM image v%u.%u is newer than expected v%u.%u. You must install the most recent version of the network driver.\n",
				 hw->aq.api_maj_ver,
				 hw->aq.api_min_ver,
				 I40E_FW_API_VERSION_MAJOR,
				 I40E_FW_MINOR_VERSION(hw));
		अन्यथा
			dev_info(&pdev->dev,
				 "The driver for the device stopped because the device firmware failed to init. Try updating your NVM image.\n");

		जाओ err_pf_reset;
	पूर्ण
	i40e_get_oem_version(hw);

	/* provide nvm, fw, api versions, venकरोr:device id, subsys venकरोr:device id */
	dev_info(&pdev->dev, "fw %d.%d.%05d api %d.%d nvm %s [%04x:%04x] [%04x:%04x]\n",
		 hw->aq.fw_maj_ver, hw->aq.fw_min_ver, hw->aq.fw_build,
		 hw->aq.api_maj_ver, hw->aq.api_min_ver,
		 i40e_nvm_version_str(hw), hw->venकरोr_id, hw->device_id,
		 hw->subप्रणाली_venकरोr_id, hw->subप्रणाली_device_id);

	अगर (hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
	    hw->aq.api_min_ver > I40E_FW_MINOR_VERSION(hw))
		dev_info(&pdev->dev,
			 "The driver for the device detected a newer version of the NVM image v%u.%u than expected v%u.%u. Please install the most recent version of the network driver.\n",
			 hw->aq.api_maj_ver,
			 hw->aq.api_min_ver,
			 I40E_FW_API_VERSION_MAJOR,
			 I40E_FW_MINOR_VERSION(hw));
	अन्यथा अगर (hw->aq.api_maj_ver == 1 && hw->aq.api_min_ver < 4)
		dev_info(&pdev->dev,
			 "The driver for the device detected an older version of the NVM image v%u.%u than expected v%u.%u. Please update the NVM image.\n",
			 hw->aq.api_maj_ver,
			 hw->aq.api_min_ver,
			 I40E_FW_API_VERSION_MAJOR,
			 I40E_FW_MINOR_VERSION(hw));

	i40e_verअगरy_eeprom(pf);

	/* Rev 0 hardware was never productized */
	अगर (hw->revision_id < 1)
		dev_warn(&pdev->dev, "This device is a pre-production adapter/LOM. Please be aware there may be issues with your hardware. If you are experiencing problems please contact your Intel or hardware representative who provided you with this hardware.\n");

	i40e_clear_pxe_mode(hw);

	err = i40e_get_capabilities(pf, i40e_aqc_opc_list_func_capabilities);
	अगर (err)
		जाओ err_adminq_setup;

	err = i40e_sw_init(pf);
	अगर (err) अणु
		dev_info(&pdev->dev, "sw_init failed: %d\n", err);
		जाओ err_sw_init;
	पूर्ण

	अगर (test_bit(__I40E_RECOVERY_MODE, pf->state))
		वापस i40e_init_recovery_mode(pf, hw);

	err = i40e_init_lan_hmc(hw, hw->func_caps.num_tx_qp,
				hw->func_caps.num_rx_qp, 0, 0);
	अगर (err) अणु
		dev_info(&pdev->dev, "init_lan_hmc failed: %d\n", err);
		जाओ err_init_lan_hmc;
	पूर्ण

	err = i40e_configure_lan_hmc(hw, I40E_HMC_MODEL_सूचीECT_ONLY);
	अगर (err) अणु
		dev_info(&pdev->dev, "configure_lan_hmc failed: %d\n", err);
		err = -ENOENT;
		जाओ err_configure_lan_hmc;
	पूर्ण

	/* Disable LLDP क्रम NICs that have firmware versions lower than v4.3.
	 * Ignore error वापस codes because अगर it was alपढ़ोy disabled via
	 * hardware settings this will fail
	 */
	अगर (pf->hw_features & I40E_HW_STOP_FW_LLDP) अणु
		dev_info(&pdev->dev, "Stopping firmware LLDP agent.\n");
		i40e_aq_stop_lldp(hw, true, false, शून्य);
	पूर्ण

	/* allow a platक्रमm config to override the HW addr */
	i40e_get_platक्रमm_mac_addr(pdev, pf);

	अगर (!is_valid_ether_addr(hw->mac.addr)) अणु
		dev_info(&pdev->dev, "invalid MAC address %pM\n", hw->mac.addr);
		err = -EIO;
		जाओ err_mac_addr;
	पूर्ण
	dev_info(&pdev->dev, "MAC address: %pM\n", hw->mac.addr);
	ether_addr_copy(hw->mac.perm_addr, hw->mac.addr);
	i40e_get_port_mac_addr(hw, hw->mac.port_addr);
	अगर (is_valid_ether_addr(hw->mac.port_addr))
		pf->hw_features |= I40E_HW_PORT_ID_VALID;

	pci_set_drvdata(pdev, pf);
	pci_save_state(pdev);

#अगर_घोषित CONFIG_I40E_DCB
	status = i40e_get_fw_lldp_status(&pf->hw, &lldp_status);
	(!status &&
	 lldp_status == I40E_GET_FW_LLDP_STATUS_ENABLED) ?
		(pf->flags &= ~I40E_FLAG_DISABLE_FW_LLDP) :
		(pf->flags |= I40E_FLAG_DISABLE_FW_LLDP);
	dev_info(&pdev->dev,
		 (pf->flags & I40E_FLAG_DISABLE_FW_LLDP) ?
			"FW LLDP is disabled\n" :
			"FW LLDP is enabled\n");

	/* Enable FW to ग_लिखो शेष DCB config on link-up */
	i40e_aq_set_dcb_parameters(hw, true, शून्य);

	err = i40e_init_pf_dcb(pf);
	अगर (err) अणु
		dev_info(&pdev->dev, "DCB init failed %d, disabled\n", err);
		pf->flags &= ~(I40E_FLAG_DCB_CAPABLE | I40E_FLAG_DCB_ENABLED);
		/* Continue without DCB enabled */
	पूर्ण
#पूर्ण_अगर /* CONFIG_I40E_DCB */

	/* set up periodic task facility */
	समयr_setup(&pf->service_समयr, i40e_service_समयr, 0);
	pf->service_समयr_period = HZ;

	INIT_WORK(&pf->service_task, i40e_service_task);
	clear_bit(__I40E_SERVICE_SCHED, pf->state);

	/* NVM bit on means WoL disabled क्रम the port */
	i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_WAKE_ON_LAN, &wol_nvm_bits);
	अगर (BIT (hw->port) & wol_nvm_bits || hw->partition_id != 1)
		pf->wol_en = false;
	अन्यथा
		pf->wol_en = true;
	device_set_wakeup_enable(&pf->pdev->dev, pf->wol_en);

	/* set up the मुख्य चयन operations */
	i40e_determine_queue_usage(pf);
	err = i40e_init_पूर्णांकerrupt_scheme(pf);
	अगर (err)
		जाओ err_चयन_setup;

	/* Reduce Tx and Rx pairs क्रम kdump
	 * When MSI-X is enabled, it's not allowed to use more TC queue
	 * pairs than MSI-X vectors (pf->num_lan_msix) exist. Thus
	 * vsi->num_queue_pairs will be equal to pf->num_lan_msix, i.e., 1.
	 */
	अगर (is_kdump_kernel())
		pf->num_lan_msix = 1;

	pf->udp_tunnel_nic.set_port = i40e_udp_tunnel_set_port;
	pf->udp_tunnel_nic.unset_port = i40e_udp_tunnel_unset_port;
	pf->udp_tunnel_nic.flags = UDP_TUNNEL_NIC_INFO_MAY_SLEEP;
	pf->udp_tunnel_nic.shared = &pf->udp_tunnel_shared;
	pf->udp_tunnel_nic.tables[0].n_entries = I40E_MAX_PF_UDP_OFFLOAD_PORTS;
	pf->udp_tunnel_nic.tables[0].tunnel_types = UDP_TUNNEL_TYPE_VXLAN |
						    UDP_TUNNEL_TYPE_GENEVE;

	/* The number of VSIs reported by the FW is the minimum guaranteed
	 * to us; HW supports far more and we share the reमुख्यing pool with
	 * the other PFs. We allocate space क्रम more than the guarantee with
	 * the understanding that we might not get them all later.
	 */
	अगर (pf->hw.func_caps.num_vsis < I40E_MIN_VSI_ALLOC)
		pf->num_alloc_vsi = I40E_MIN_VSI_ALLOC;
	अन्यथा
		pf->num_alloc_vsi = pf->hw.func_caps.num_vsis;
	अगर (pf->num_alloc_vsi > UDP_TUNNEL_NIC_MAX_SHARING_DEVICES) अणु
		dev_warn(&pf->pdev->dev,
			 "limiting the VSI count due to UDP tunnel limitation %d > %d\n",
			 pf->num_alloc_vsi, UDP_TUNNEL_NIC_MAX_SHARING_DEVICES);
		pf->num_alloc_vsi = UDP_TUNNEL_NIC_MAX_SHARING_DEVICES;
	पूर्ण

	/* Set up the *vsi काष्ठा and our local tracking of the MAIN PF vsi. */
	pf->vsi = kसुस्मृति(pf->num_alloc_vsi, माप(काष्ठा i40e_vsi *),
			  GFP_KERNEL);
	अगर (!pf->vsi) अणु
		err = -ENOMEM;
		जाओ err_चयन_setup;
	पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
	/* prep क्रम VF support */
	अगर ((pf->flags & I40E_FLAG_SRIOV_ENABLED) &&
	    (pf->flags & I40E_FLAG_MSIX_ENABLED) &&
	    !test_bit(__I40E_BAD_EEPROM, pf->state)) अणु
		अगर (pci_num_vf(pdev))
			pf->flags |= I40E_FLAG_VEB_MODE_ENABLED;
	पूर्ण
#पूर्ण_अगर
	err = i40e_setup_pf_चयन(pf, false);
	अगर (err) अणु
		dev_info(&pdev->dev, "setup_pf_switch failed: %d\n", err);
		जाओ err_vsis;
	पूर्ण
	INIT_LIST_HEAD(&pf->vsi[pf->lan_vsi]->ch_list);

	/* अगर Fसूची VSI was set up, start it now */
	क्रम (i = 0; i < pf->num_alloc_vsi; i++) अणु
		अगर (pf->vsi[i] && pf->vsi[i]->type == I40E_VSI_Fसूची) अणु
			i40e_vsi_खोलो(pf->vsi[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	/* The driver only wants link up/करोwn and module qualअगरication
	 * reports from firmware.  Note the negative logic.
	 */
	err = i40e_aq_set_phy_पूर्णांक_mask(&pf->hw,
				       ~(I40E_AQ_EVENT_LINK_UPDOWN |
					 I40E_AQ_EVENT_MEDIA_NA |
					 I40E_AQ_EVENT_MODULE_QUAL_FAIL), शून्य);
	अगर (err)
		dev_info(&pf->pdev->dev, "set phy mask fail, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, err),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));

	/* Reconfigure hardware क्रम allowing smaller MSS in the हाल
	 * of TSO, so that we aव्योम the MDD being fired and causing
	 * a reset in the हाल of small MSS+TSO.
	 */
	val = rd32(hw, I40E_REG_MSS);
	अगर ((val & I40E_REG_MSS_MIN_MASK) > I40E_64BYTE_MSS) अणु
		val &= ~I40E_REG_MSS_MIN_MASK;
		val |= I40E_64BYTE_MSS;
		wr32(hw, I40E_REG_MSS, val);
	पूर्ण

	अगर (pf->hw_features & I40E_HW_RESTART_AUTONEG) अणु
		msleep(75);
		err = i40e_aq_set_link_restart_an(&pf->hw, true, शून्य);
		अगर (err)
			dev_info(&pf->pdev->dev, "link restart failed, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, err),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
	पूर्ण
	/* The मुख्य driver is (mostly) up and happy. We need to set this state
	 * beक्रमe setting up the misc vector or we get a race and the vector
	 * ends up disabled क्रमever.
	 */
	clear_bit(__I40E_DOWN, pf->state);

	/* In हाल of MSIX we are going to setup the misc vector right here
	 * to handle admin queue events etc. In हाल of legacy and MSI
	 * the misc functionality and queue processing is combined in
	 * the same vector and that माला_लो setup at खोलो.
	 */
	अगर (pf->flags & I40E_FLAG_MSIX_ENABLED) अणु
		err = i40e_setup_misc_vector(pf);
		अगर (err) अणु
			dev_info(&pdev->dev,
				 "setup of misc vector failed: %d\n", err);
			i40e_cloud_filter_निकास(pf);
			i40e_fdir_tearकरोwn(pf);
			जाओ err_vsis;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
	/* prep क्रम VF support */
	अगर ((pf->flags & I40E_FLAG_SRIOV_ENABLED) &&
	    (pf->flags & I40E_FLAG_MSIX_ENABLED) &&
	    !test_bit(__I40E_BAD_EEPROM, pf->state)) अणु
		/* disable link पूर्णांकerrupts क्रम VFs */
		val = rd32(hw, I40E_PFGEN_PORTMDIO_NUM);
		val &= ~I40E_PFGEN_PORTMDIO_NUM_VFLINK_STAT_ENA_MASK;
		wr32(hw, I40E_PFGEN_PORTMDIO_NUM, val);
		i40e_flush(hw);

		अगर (pci_num_vf(pdev)) अणु
			dev_info(&pdev->dev,
				 "Active VFs found, allocating resources.\n");
			err = i40e_alloc_vfs(pf, pci_num_vf(pdev));
			अगर (err)
				dev_info(&pdev->dev,
					 "Error %d allocating resources for existing VFs\n",
					 err);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

	अगर (pf->flags & I40E_FLAG_IWARP_ENABLED) अणु
		pf->iwarp_base_vector = i40e_get_lump(pf, pf->irq_pile,
						      pf->num_iwarp_msix,
						      I40E_IWARP_IRQ_PILE_ID);
		अगर (pf->iwarp_base_vector < 0) अणु
			dev_info(&pdev->dev,
				 "failed to get tracking for %d vectors for IWARP err=%d\n",
				 pf->num_iwarp_msix, pf->iwarp_base_vector);
			pf->flags &= ~I40E_FLAG_IWARP_ENABLED;
		पूर्ण
	पूर्ण

	i40e_dbg_pf_init(pf);

	/* tell the firmware that we're starting */
	i40e_send_version(pf);

	/* since everything's happy, start the service_task समयr */
	mod_समयr(&pf->service_समयr,
		  round_jअगरfies(jअगरfies + pf->service_समयr_period));

	/* add this PF to client device list and launch a client service task */
	अगर (pf->flags & I40E_FLAG_IWARP_ENABLED) अणु
		err = i40e_lan_add_device(pf);
		अगर (err)
			dev_info(&pdev->dev, "Failed to add PF to client API service list: %d\n",
				 err);
	पूर्ण

#घोषणा PCI_SPEED_SIZE 8
#घोषणा PCI_WIDTH_SIZE 8
	/* Devices on the IOSF bus करो not have this inक्रमmation
	 * and will report PCI Gen 1 x 1 by शेष so करोn't bother
	 * checking them.
	 */
	अगर (!(pf->hw_features & I40E_HW_NO_PCI_LINK_CHECK)) अणु
		अक्षर speed[PCI_SPEED_SIZE] = "Unknown";
		अक्षर width[PCI_WIDTH_SIZE] = "Unknown";

		/* Get the negotiated link width and speed from PCI config
		 * space
		 */
		pcie_capability_पढ़ो_word(pf->pdev, PCI_EXP_LNKSTA,
					  &link_status);

		i40e_set_pci_config_data(hw, link_status);

		चयन (hw->bus.speed) अणु
		हाल i40e_bus_speed_8000:
			strlcpy(speed, "8.0", PCI_SPEED_SIZE); अवरोध;
		हाल i40e_bus_speed_5000:
			strlcpy(speed, "5.0", PCI_SPEED_SIZE); अवरोध;
		हाल i40e_bus_speed_2500:
			strlcpy(speed, "2.5", PCI_SPEED_SIZE); अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		चयन (hw->bus.width) अणु
		हाल i40e_bus_width_pcie_x8:
			strlcpy(width, "8", PCI_WIDTH_SIZE); अवरोध;
		हाल i40e_bus_width_pcie_x4:
			strlcpy(width, "4", PCI_WIDTH_SIZE); अवरोध;
		हाल i40e_bus_width_pcie_x2:
			strlcpy(width, "2", PCI_WIDTH_SIZE); अवरोध;
		हाल i40e_bus_width_pcie_x1:
			strlcpy(width, "1", PCI_WIDTH_SIZE); अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		dev_info(&pdev->dev, "PCI-Express: Speed %sGT/s Width x%s\n",
			 speed, width);

		अगर (hw->bus.width < i40e_bus_width_pcie_x8 ||
		    hw->bus.speed < i40e_bus_speed_8000) अणु
			dev_warn(&pdev->dev, "PCI-Express bandwidth available for this device may be insufficient for optimal performance.\n");
			dev_warn(&pdev->dev, "Please move the device to a different PCI-e link with more lanes and/or higher transfer rate.\n");
		पूर्ण
	पूर्ण

	/* get the requested speeds from the fw */
	err = i40e_aq_get_phy_capabilities(hw, false, false, &abilities, शून्य);
	अगर (err)
		dev_dbg(&pf->pdev->dev, "get requested speeds ret =  %s last_status =  %s\n",
			i40e_stat_str(&pf->hw, err),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
	pf->hw.phy.link_info.requested_speeds = abilities.link_speed;

	/* set the FEC config due to the board capabilities */
	i40e_set_fec_in_flags(abilities.fec_cfg_curr_mod_ext_info, &pf->flags);

	/* get the supported phy types from the fw */
	err = i40e_aq_get_phy_capabilities(hw, false, true, &abilities, शून्य);
	अगर (err)
		dev_dbg(&pf->pdev->dev, "get supported phy types ret =  %s last_status =  %s\n",
			i40e_stat_str(&pf->hw, err),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));

	/* make sure the MFS hasn't been set lower than the शेष */
#घोषणा MAX_FRAME_SIZE_DEFAULT 0x2600
	val = (rd32(&pf->hw, I40E_PRTGL_SAH) &
	       I40E_PRTGL_SAH_MFS_MASK) >> I40E_PRTGL_SAH_MFS_SHIFT;
	अगर (val < MAX_FRAME_SIZE_DEFAULT)
		dev_warn(&pdev->dev, "MFS for port %x has been set below the default: %x\n",
			 i, val);

	/* Add a filter to drop all Flow control frames from any VSI from being
	 * transmitted. By करोing so we stop a malicious VF from sending out
	 * PAUSE or PFC frames and potentially controlling traffic क्रम other
	 * PF/VF VSIs.
	 * The FW can still send Flow control frames अगर enabled.
	 */
	i40e_add_filter_to_drop_tx_flow_control_frames(&pf->hw,
						       pf->मुख्य_vsi_seid);

	अगर ((pf->hw.device_id == I40E_DEV_ID_10G_BASE_T) ||
		(pf->hw.device_id == I40E_DEV_ID_10G_BASE_T4))
		pf->hw_features |= I40E_HW_PHY_CONTROLS_LEDS;
	अगर (pf->hw.device_id == I40E_DEV_ID_SFP_I_X722)
		pf->hw_features |= I40E_HW_HAVE_CRT_RETIMER;
	/* prपूर्णांक a string summarizing features */
	i40e_prपूर्णांक_features(pf);

	वापस 0;

	/* Unwind what we've करोne अगर something failed in the setup */
err_vsis:
	set_bit(__I40E_DOWN, pf->state);
	i40e_clear_पूर्णांकerrupt_scheme(pf);
	kमुक्त(pf->vsi);
err_चयन_setup:
	i40e_reset_पूर्णांकerrupt_capability(pf);
	del_समयr_sync(&pf->service_समयr);
err_mac_addr:
err_configure_lan_hmc:
	(व्योम)i40e_shutकरोwn_lan_hmc(hw);
err_init_lan_hmc:
	kमुक्त(pf->qp_pile);
err_sw_init:
err_adminq_setup:
err_pf_reset:
	iounmap(hw->hw_addr);
err_ioremap:
	kमुक्त(pf);
err_pf_alloc:
	pci_disable_pcie_error_reporting(pdev);
	pci_release_mem_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * i40e_हटाओ - Device removal routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * i40e_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that is should release a PCI device.  This could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम i40e_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status ret_code;
	पूर्णांक i;

	i40e_dbg_pf_निकास(pf);

	i40e_ptp_stop(pf);

	/* Disable RSS in hw */
	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_HENA(0), 0);
	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_HENA(1), 0);

	जबतक (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state))
		usleep_range(1000, 2000);

	अगर (pf->flags & I40E_FLAG_SRIOV_ENABLED) अणु
		set_bit(__I40E_VF_RESETS_DISABLED, pf->state);
		i40e_मुक्त_vfs(pf);
		pf->flags &= ~I40E_FLAG_SRIOV_ENABLED;
	पूर्ण
	/* no more scheduling of any task */
	set_bit(__I40E_SUSPENDED, pf->state);
	set_bit(__I40E_DOWN, pf->state);
	अगर (pf->service_समयr.function)
		del_समयr_sync(&pf->service_समयr);
	अगर (pf->service_task.func)
		cancel_work_sync(&pf->service_task);

	अगर (test_bit(__I40E_RECOVERY_MODE, pf->state)) अणु
		काष्ठा i40e_vsi *vsi = pf->vsi[0];

		/* We know that we have allocated only one vsi क्रम this PF,
		 * it was just क्रम रेजिस्टरing netdevice, so the पूर्णांकerface
		 * could be visible in the 'ifconfig' output
		 */
		unरेजिस्टर_netdev(vsi->netdev);
		मुक्त_netdev(vsi->netdev);

		जाओ unmap;
	पूर्ण

	/* Client बंद must be called explicitly here because the समयr
	 * has been stopped.
	 */
	i40e_notअगरy_client_of_netdev_बंद(pf->vsi[pf->lan_vsi], false);

	i40e_fdir_tearकरोwn(pf);

	/* If there is a चयन काष्ठाure or any orphans, हटाओ them.
	 * This will leave only the PF's VSI reमुख्यing.
	 */
	क्रम (i = 0; i < I40E_MAX_VEB; i++) अणु
		अगर (!pf->veb[i])
			जारी;

		अगर (pf->veb[i]->uplink_seid == pf->mac_seid ||
		    pf->veb[i]->uplink_seid == 0)
			i40e_चयन_branch_release(pf->veb[i]);
	पूर्ण

	/* Now we can shutकरोwn the PF's VSI, just beक्रमe we समाप्त
	 * adminq and hmc.
	 */
	अगर (pf->vsi[pf->lan_vsi])
		i40e_vsi_release(pf->vsi[pf->lan_vsi]);

	i40e_cloud_filter_निकास(pf);

	/* हटाओ attached clients */
	अगर (pf->flags & I40E_FLAG_IWARP_ENABLED) अणु
		ret_code = i40e_lan_del_device(pf);
		अगर (ret_code)
			dev_warn(&pdev->dev, "Failed to delete client device: %d\n",
				 ret_code);
	पूर्ण

	/* shutकरोwn and destroy the HMC */
	अगर (hw->hmc.hmc_obj) अणु
		ret_code = i40e_shutकरोwn_lan_hmc(hw);
		अगर (ret_code)
			dev_warn(&pdev->dev,
				 "Failed to destroy the HMC resources: %d\n",
				 ret_code);
	पूर्ण

unmap:
	/* Free MSI/legacy पूर्णांकerrupt 0 when in recovery mode. */
	अगर (test_bit(__I40E_RECOVERY_MODE, pf->state) &&
	    !(pf->flags & I40E_FLAG_MSIX_ENABLED))
		मुक्त_irq(pf->pdev->irq, pf);

	/* shutकरोwn the adminq */
	i40e_shutकरोwn_adminq(hw);

	/* destroy the locks only once, here */
	mutex_destroy(&hw->aq.arq_mutex);
	mutex_destroy(&hw->aq.asq_mutex);

	/* Clear all dynamic memory lists of rings, q_vectors, and VSIs */
	rtnl_lock();
	i40e_clear_पूर्णांकerrupt_scheme(pf);
	क्रम (i = 0; i < pf->num_alloc_vsi; i++) अणु
		अगर (pf->vsi[i]) अणु
			अगर (!test_bit(__I40E_RECOVERY_MODE, pf->state))
				i40e_vsi_clear_rings(pf->vsi[i]);
			i40e_vsi_clear(pf->vsi[i]);
			pf->vsi[i] = शून्य;
		पूर्ण
	पूर्ण
	rtnl_unlock();

	क्रम (i = 0; i < I40E_MAX_VEB; i++) अणु
		kमुक्त(pf->veb[i]);
		pf->veb[i] = शून्य;
	पूर्ण

	kमुक्त(pf->qp_pile);
	kमुक्त(pf->vsi);

	iounmap(hw->hw_addr);
	kमुक्त(pf);
	pci_release_mem_regions(pdev);

	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
पूर्ण

/**
 * i40e_pci_error_detected - warning that something funky happened in PCI land
 * @pdev: PCI device inक्रमmation काष्ठा
 * @error: the type of PCI error
 *
 * Called to warn that something happened and the error handling steps
 * are in progress.  Allows the driver to quiesce things, be पढ़ोy क्रम
 * remediation.
 **/
अटल pci_ers_result_t i40e_pci_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t error)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);

	dev_info(&pdev->dev, "%s: error %d\n", __func__, error);

	अगर (!pf) अणु
		dev_info(&pdev->dev,
			 "Cannot recover - error happened during device probe\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	/* shutकरोwn all operations */
	अगर (!test_bit(__I40E_SUSPENDED, pf->state))
		i40e_prep_क्रम_reset(pf);

	/* Request a slot reset */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * i40e_pci_error_slot_reset - a PCI slot reset just happened
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * Called to find अगर the driver can work with the device now that
 * the pci slot has been reset.  If a basic connection seems good
 * (रेजिस्टरs are पढ़ोable and have sane content) then वापस a
 * happy little PCI_ERS_RESULT_xxx.
 **/
अटल pci_ers_result_t i40e_pci_error_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);
	pci_ers_result_t result;
	u32 reg;

	dev_dbg(&pdev->dev, "%s\n", __func__);
	अगर (pci_enable_device_mem(pdev)) अणु
		dev_info(&pdev->dev,
			 "Cannot re-enable PCI device after reset.\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		pci_restore_state(pdev);
		pci_save_state(pdev);
		pci_wake_from_d3(pdev, false);

		reg = rd32(&pf->hw, I40E_GLGEN_RTRIG);
		अगर (reg == 0)
			result = PCI_ERS_RESULT_RECOVERED;
		अन्यथा
			result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस result;
पूर्ण

/**
 * i40e_pci_error_reset_prepare - prepare device driver क्रम pci reset
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम i40e_pci_error_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);

	i40e_prep_क्रम_reset(pf);
पूर्ण

/**
 * i40e_pci_error_reset_करोne - pci reset करोne, device driver reset can begin
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम i40e_pci_error_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);

	i40e_reset_and_rebuild(pf, false, false);
पूर्ण

/**
 * i40e_pci_error_resume - restart operations after PCI error recovery
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * Called to allow the driver to bring things back up after PCI error
 * and/or reset recovery has finished.
 **/
अटल व्योम i40e_pci_error_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s\n", __func__);
	अगर (test_bit(__I40E_SUSPENDED, pf->state))
		वापस;

	i40e_handle_reset_warning(pf, false);
पूर्ण

/**
 * i40e_enable_mc_magic_wake - enable multicast magic packet wake up
 * using the mac_address_ग_लिखो admin q function
 * @pf: poपूर्णांकer to i40e_pf काष्ठा
 **/
अटल व्योम i40e_enable_mc_magic_wake(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status ret;
	u8 mac_addr[6];
	u16 flags = 0;

	/* Get current MAC address in हाल it's an LAA */
	अगर (pf->vsi[pf->lan_vsi] && pf->vsi[pf->lan_vsi]->netdev) अणु
		ether_addr_copy(mac_addr,
				pf->vsi[pf->lan_vsi]->netdev->dev_addr);
	पूर्ण अन्यथा अणु
		dev_err(&pf->pdev->dev,
			"Failed to retrieve MAC address; using default\n");
		ether_addr_copy(mac_addr, hw->mac.addr);
	पूर्ण

	/* The FW expects the mac address ग_लिखो cmd to first be called with
	 * one of these flags beक्रमe calling it again with the multicast
	 * enable flags.
	 */
	flags = I40E_AQC_WRITE_TYPE_LAA_WOL;

	अगर (hw->func_caps.flex10_enable && hw->partition_id != 1)
		flags = I40E_AQC_WRITE_TYPE_LAA_ONLY;

	ret = i40e_aq_mac_address_ग_लिखो(hw, flags, mac_addr, शून्य);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev,
			"Failed to update MAC address registers; cannot enable Multicast Magic packet wake up");
		वापस;
	पूर्ण

	flags = I40E_AQC_MC_MAG_EN
			| I40E_AQC_WOL_PRESERVE_ON_PFR
			| I40E_AQC_WRITE_TYPE_UPDATE_MC_MAG;
	ret = i40e_aq_mac_address_ग_लिखो(hw, flags, mac_addr, शून्य);
	अगर (ret)
		dev_err(&pf->pdev->dev,
			"Failed to enable Multicast Magic Packet wake up\n");
पूर्ण

/**
 * i40e_shutकरोwn - PCI callback क्रम shutting करोwn
 * @pdev: PCI device inक्रमmation काष्ठा
 **/
अटल व्योम i40e_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);
	काष्ठा i40e_hw *hw = &pf->hw;

	set_bit(__I40E_SUSPENDED, pf->state);
	set_bit(__I40E_DOWN, pf->state);

	del_समयr_sync(&pf->service_समयr);
	cancel_work_sync(&pf->service_task);
	i40e_cloud_filter_निकास(pf);
	i40e_fdir_tearकरोwn(pf);

	/* Client बंद must be called explicitly here because the समयr
	 * has been stopped.
	 */
	i40e_notअगरy_client_of_netdev_बंद(pf->vsi[pf->lan_vsi], false);

	अगर (pf->wol_en && (pf->hw_features & I40E_HW_WOL_MC_MAGIC_PKT_WAKE))
		i40e_enable_mc_magic_wake(pf);

	i40e_prep_क्रम_reset(pf);

	wr32(hw, I40E_PFPM_APM,
	     (pf->wol_en ? I40E_PFPM_APM_APME_MASK : 0));
	wr32(hw, I40E_PFPM_WUFC,
	     (pf->wol_en ? I40E_PFPM_WUFC_MAG_MASK : 0));

	/* Free MSI/legacy पूर्णांकerrupt 0 when in recovery mode. */
	अगर (test_bit(__I40E_RECOVERY_MODE, pf->state) &&
	    !(pf->flags & I40E_FLAG_MSIX_ENABLED))
		मुक्त_irq(pf->pdev->irq, pf);

	/* Since we're going to destroy queues during the
	 * i40e_clear_पूर्णांकerrupt_scheme() we should hold the RTNL lock क्रम this
	 * whole section
	 */
	rtnl_lock();
	i40e_clear_पूर्णांकerrupt_scheme(pf);
	rtnl_unlock();

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, pf->wol_en);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

/**
 * i40e_suspend - PM callback क्रम moving to D3
 * @dev: generic device inक्रमmation काष्ठाure
 **/
अटल पूर्णांक __maybe_unused i40e_suspend(काष्ठा device *dev)
अणु
	काष्ठा i40e_pf *pf = dev_get_drvdata(dev);
	काष्ठा i40e_hw *hw = &pf->hw;

	/* If we're alपढ़ोy suspended, then there is nothing to करो */
	अगर (test_and_set_bit(__I40E_SUSPENDED, pf->state))
		वापस 0;

	set_bit(__I40E_DOWN, pf->state);

	/* Ensure service task will not be running */
	del_समयr_sync(&pf->service_समयr);
	cancel_work_sync(&pf->service_task);

	/* Client बंद must be called explicitly here because the समयr
	 * has been stopped.
	 */
	i40e_notअगरy_client_of_netdev_बंद(pf->vsi[pf->lan_vsi], false);

	अगर (pf->wol_en && (pf->hw_features & I40E_HW_WOL_MC_MAGIC_PKT_WAKE))
		i40e_enable_mc_magic_wake(pf);

	/* Since we're going to destroy queues during the
	 * i40e_clear_पूर्णांकerrupt_scheme() we should hold the RTNL lock क्रम this
	 * whole section
	 */
	rtnl_lock();

	i40e_prep_क्रम_reset(pf);

	wr32(hw, I40E_PFPM_APM, (pf->wol_en ? I40E_PFPM_APM_APME_MASK : 0));
	wr32(hw, I40E_PFPM_WUFC, (pf->wol_en ? I40E_PFPM_WUFC_MAG_MASK : 0));

	/* Clear the पूर्णांकerrupt scheme and release our IRQs so that the प्रणाली
	 * can safely hibernate even when there are a large number of CPUs.
	 * Otherwise hibernation might fail when mapping all the vectors back
	 * to CPU0.
	 */
	i40e_clear_पूर्णांकerrupt_scheme(pf);

	rtnl_unlock();

	वापस 0;
पूर्ण

/**
 * i40e_resume - PM callback क्रम waking up from D3
 * @dev: generic device inक्रमmation काष्ठाure
 **/
अटल पूर्णांक __maybe_unused i40e_resume(काष्ठा device *dev)
अणु
	काष्ठा i40e_pf *pf = dev_get_drvdata(dev);
	पूर्णांक err;

	/* If we're not suspended, then there is nothing to करो */
	अगर (!test_bit(__I40E_SUSPENDED, pf->state))
		वापस 0;

	/* We need to hold the RTNL lock prior to restoring पूर्णांकerrupt schemes,
	 * since we're going to be restoring queues
	 */
	rtnl_lock();

	/* We cleared the पूर्णांकerrupt scheme when we suspended, so we need to
	 * restore it now to resume device functionality.
	 */
	err = i40e_restore_पूर्णांकerrupt_scheme(pf);
	अगर (err) अणु
		dev_err(dev, "Cannot restore interrupt scheme: %d\n",
			err);
	पूर्ण

	clear_bit(__I40E_DOWN, pf->state);
	i40e_reset_and_rebuild(pf, false, true);

	rtnl_unlock();

	/* Clear suspended state last after everything is recovered */
	clear_bit(__I40E_SUSPENDED, pf->state);

	/* Restart the service task */
	mod_समयr(&pf->service_समयr,
		  round_jअगरfies(jअगरfies + pf->service_समयr_period));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers i40e_err_handler = अणु
	.error_detected = i40e_pci_error_detected,
	.slot_reset = i40e_pci_error_slot_reset,
	.reset_prepare = i40e_pci_error_reset_prepare,
	.reset_करोne = i40e_pci_error_reset_करोne,
	.resume = i40e_pci_error_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(i40e_pm_ops, i40e_suspend, i40e_resume);

अटल काष्ठा pci_driver i40e_driver = अणु
	.name     = i40e_driver_name,
	.id_table = i40e_pci_tbl,
	.probe    = i40e_probe,
	.हटाओ   = i40e_हटाओ,
	.driver   = अणु
		.pm = &i40e_pm_ops,
	पूर्ण,
	.shutकरोwn = i40e_shutकरोwn,
	.err_handler = &i40e_err_handler,
	.sriov_configure = i40e_pci_sriov_configure,
पूर्ण;

/**
 * i40e_init_module - Driver registration routine
 *
 * i40e_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init i40e_init_module(व्योम)
अणु
	pr_info("%s: %s\n", i40e_driver_name, i40e_driver_string);
	pr_info("%s: %s\n", i40e_driver_name, i40e_copyright);

	/* There is no need to throttle the number of active tasks because
	 * each device limits its own task using a state bit क्रम scheduling
	 * the service task, and the device tasks करो not पूर्णांकerfere with each
	 * other, so we करोn't set a max task limit. We must set WQ_MEM_RECLAIM
	 * since we need to be able to guarantee क्रमward progress even under
	 * memory pressure.
	 */
	i40e_wq = alloc_workqueue("%s", WQ_MEM_RECLAIM, 0, i40e_driver_name);
	अगर (!i40e_wq) अणु
		pr_err("%s: Failed to create workqueue\n", i40e_driver_name);
		वापस -ENOMEM;
	पूर्ण

	i40e_dbg_init();
	वापस pci_रेजिस्टर_driver(&i40e_driver);
पूर्ण
module_init(i40e_init_module);

/**
 * i40e_निकास_module - Driver निकास cleanup routine
 *
 * i40e_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास i40e_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&i40e_driver);
	destroy_workqueue(i40e_wq);
	i40e_dbg_निकास();
पूर्ण
module_निकास(i40e_निकास_module);
