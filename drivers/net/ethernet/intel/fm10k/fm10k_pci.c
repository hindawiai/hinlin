<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/aer.h>

#समावेश "fm10k.h"

अटल स्थिर काष्ठा fm10k_info *fm10k_info_tbl[] = अणु
	[fm10k_device_pf] = &fm10k_pf_info,
	[fm10k_device_vf] = &fm10k_vf_info,
पूर्ण;

/*
 * fm10k_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id fm10k_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, FM10K_DEV_ID_PF), fm10k_device_pf पूर्ण,
	अणु PCI_VDEVICE(INTEL, FM10K_DEV_ID_SDI_FM10420_QDA2), fm10k_device_pf पूर्ण,
	अणु PCI_VDEVICE(INTEL, FM10K_DEV_ID_SDI_FM10420_DA2), fm10k_device_pf पूर्ण,
	अणु PCI_VDEVICE(INTEL, FM10K_DEV_ID_VF), fm10k_device_vf पूर्ण,
	/* required last entry */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, fm10k_pci_tbl);

u16 fm10k_पढ़ो_pci_cfg_word(काष्ठा fm10k_hw *hw, u32 reg)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = hw->back;
	u16 value = 0;

	अगर (FM10K_REMOVED(hw->hw_addr))
		वापस ~value;

	pci_पढ़ो_config_word(पूर्णांकerface->pdev, reg, &value);
	अगर (value == 0xFFFF)
		fm10k_ग_लिखो_flush(hw);

	वापस value;
पूर्ण

u32 fm10k_पढ़ो_reg(काष्ठा fm10k_hw *hw, पूर्णांक reg)
अणु
	u32 __iomem *hw_addr = READ_ONCE(hw->hw_addr);
	u32 value = 0;

	अगर (FM10K_REMOVED(hw_addr))
		वापस ~value;

	value = पढ़ोl(&hw_addr[reg]);
	अगर (!(~value) && (!reg || !(~पढ़ोl(hw_addr)))) अणु
		काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = hw->back;
		काष्ठा net_device *netdev = पूर्णांकerface->netdev;

		hw->hw_addr = शून्य;
		netअगर_device_detach(netdev);
		netdev_err(netdev, "PCIe link lost, device now detached\n");
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक fm10k_hw_पढ़ोy(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	fm10k_ग_लिखो_flush(hw);

	वापस FM10K_REMOVED(hw->hw_addr) ? -ENODEV : 0;
पूर्ण

/**
 * fm10k_macvlan_schedule - Schedule MAC/VLAN queue task
 * @पूर्णांकerface: fm10k निजी पूर्णांकerface काष्ठाure
 *
 * Schedule the MAC/VLAN queue monitor task. If the MAC/VLAN task cannot be
 * started immediately, request that it be restarted when possible.
 */
व्योम fm10k_macvlan_schedule(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* Aव्योम processing the MAC/VLAN queue when the service task is
	 * disabled, or when we're resetting the device.
	 */
	अगर (!test_bit(__FM10K_MACVLAN_DISABLE, पूर्णांकerface->state) &&
	    !test_and_set_bit(__FM10K_MACVLAN_SCHED, पूर्णांकerface->state)) अणु
		clear_bit(__FM10K_MACVLAN_REQUEST, पूर्णांकerface->state);
		/* We delay the actual start of execution in order to allow
		 * multiple MAC/VLAN updates to accumulate beक्रमe handling
		 * them, and to allow some समय to let the mailbox drain
		 * between runs.
		 */
		queue_delayed_work(fm10k_workqueue,
				   &पूर्णांकerface->macvlan_task, 10);
	पूर्ण अन्यथा अणु
		set_bit(__FM10K_MACVLAN_REQUEST, पूर्णांकerface->state);
	पूर्ण
पूर्ण

/**
 * fm10k_stop_macvlan_task - Stop the MAC/VLAN queue monitor
 * @पूर्णांकerface: fm10k निजी पूर्णांकerface काष्ठाure
 *
 * Wait until the MAC/VLAN queue task has stopped, and cancel any future
 * requests.
 */
अटल व्योम fm10k_stop_macvlan_task(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* Disable the MAC/VLAN work item */
	set_bit(__FM10K_MACVLAN_DISABLE, पूर्णांकerface->state);

	/* Make sure we रुकोed until any current invocations have stopped */
	cancel_delayed_work_sync(&पूर्णांकerface->macvlan_task);

	/* We set the __FM10K_MACVLAN_SCHED bit when we schedule the task.
	 * However, it may not be unset of the MAC/VLAN task never actually
	 * got a chance to run. Since we've canceled the task here, and it
	 * cannot be rescheuled right now, we need to ensure the scheduled bit
	 * माला_लो unset.
	 */
	clear_bit(__FM10K_MACVLAN_SCHED, पूर्णांकerface->state);
पूर्ण

/**
 * fm10k_resume_macvlan_task - Restart the MAC/VLAN queue monitor
 * @पूर्णांकerface: fm10k निजी पूर्णांकerface काष्ठाure
 *
 * Clear the __FM10K_MACVLAN_DISABLE bit and, अगर a request occurred, schedule
 * the MAC/VLAN work monitor.
 */
अटल व्योम fm10k_resume_macvlan_task(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* Re-enable the MAC/VLAN work item */
	clear_bit(__FM10K_MACVLAN_DISABLE, पूर्णांकerface->state);

	/* We might have received a MAC/VLAN request जबतक disabled. If so,
	 * kick off the queue now.
	 */
	अगर (test_bit(__FM10K_MACVLAN_REQUEST, पूर्णांकerface->state))
		fm10k_macvlan_schedule(पूर्णांकerface);
पूर्ण

व्योम fm10k_service_event_schedule(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	अगर (!test_bit(__FM10K_SERVICE_DISABLE, पूर्णांकerface->state) &&
	    !test_and_set_bit(__FM10K_SERVICE_SCHED, पूर्णांकerface->state)) अणु
		clear_bit(__FM10K_SERVICE_REQUEST, पूर्णांकerface->state);
		queue_work(fm10k_workqueue, &पूर्णांकerface->service_task);
	पूर्ण अन्यथा अणु
		set_bit(__FM10K_SERVICE_REQUEST, पूर्णांकerface->state);
	पूर्ण
पूर्ण

अटल व्योम fm10k_service_event_complete(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	WARN_ON(!test_bit(__FM10K_SERVICE_SCHED, पूर्णांकerface->state));

	/* flush memory to make sure state is correct beक्रमe next watchog */
	smp_mb__beक्रमe_atomic();
	clear_bit(__FM10K_SERVICE_SCHED, पूर्णांकerface->state);

	/* If a service event was requested since we started, immediately
	 * re-schedule now. This ensures we करोn't drop a request until the
	 * next समयr event.
	 */
	अगर (test_bit(__FM10K_SERVICE_REQUEST, पूर्णांकerface->state))
		fm10k_service_event_schedule(पूर्णांकerface);
पूर्ण

अटल व्योम fm10k_stop_service_event(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	set_bit(__FM10K_SERVICE_DISABLE, पूर्णांकerface->state);
	cancel_work_sync(&पूर्णांकerface->service_task);

	/* It's possible that cancel_work_sync stopped the service task from
	 * running beक्रमe it could actually start. In this हाल the
	 * __FM10K_SERVICE_SCHED bit will never be cleared. Since we know that
	 * the service task cannot be running at this poपूर्णांक, we need to clear
	 * the scheduled bit, as otherwise the service task may never be
	 * restarted.
	 */
	clear_bit(__FM10K_SERVICE_SCHED, पूर्णांकerface->state);
पूर्ण

अटल व्योम fm10k_start_service_event(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	clear_bit(__FM10K_SERVICE_DISABLE, पूर्णांकerface->state);
	fm10k_service_event_schedule(पूर्णांकerface);
पूर्ण

/**
 * fm10k_service_समयr - Timer Call-back
 * @t: poपूर्णांकer to समयr data
 **/
अटल व्योम fm10k_service_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = from_समयr(पूर्णांकerface, t,
						   service_समयr);

	/* Reset the समयr */
	mod_समयr(&पूर्णांकerface->service_समयr, (HZ * 2) + jअगरfies);

	fm10k_service_event_schedule(पूर्णांकerface);
पूर्ण

/**
 * fm10k_prepare_क्रम_reset - Prepare the driver and device क्रम a pending reset
 * @पूर्णांकerface: fm10k निजी data काष्ठाure
 *
 * This function prepares क्रम a device reset by shutting as much करोwn as we
 * can. It करोes nothing and वापसs false अगर __FM10K_RESETTING was alपढ़ोy set
 * prior to calling this function. It वापसs true अगर it actually did work.
 */
अटल bool fm10k_prepare_क्रम_reset(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;

	/* put off any impending NetWatchDogTimeout */
	netअगर_trans_update(netdev);

	/* Nothing to करो अगर a reset is alपढ़ोy in progress */
	अगर (test_and_set_bit(__FM10K_RESETTING, पूर्णांकerface->state))
		वापस false;

	/* As the MAC/VLAN task will be accessing रेजिस्टरs it must not be
	 * running जबतक we reset. Although the task will not be scheduled
	 * once we start resetting it may alपढ़ोy be running
	 */
	fm10k_stop_macvlan_task(पूर्णांकerface);

	rtnl_lock();

	fm10k_iov_suspend(पूर्णांकerface->pdev);

	अगर (netअगर_running(netdev))
		fm10k_बंद(netdev);

	fm10k_mbx_मुक्त_irq(पूर्णांकerface);

	/* मुक्त पूर्णांकerrupts */
	fm10k_clear_queueing_scheme(पूर्णांकerface);

	/* delay any future reset requests */
	पूर्णांकerface->last_reset = jअगरfies + (10 * HZ);

	rtnl_unlock();

	वापस true;
पूर्ण

अटल पूर्णांक fm10k_handle_reset(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक err;

	WARN_ON(!test_bit(__FM10K_RESETTING, पूर्णांकerface->state));

	rtnl_lock();

	pci_set_master(पूर्णांकerface->pdev);

	/* reset and initialize the hardware so it is in a known state */
	err = hw->mac.ops.reset_hw(hw);
	अगर (err) अणु
		dev_err(&पूर्णांकerface->pdev->dev, "reset_hw failed: %d\n", err);
		जाओ reinit_err;
	पूर्ण

	err = hw->mac.ops.init_hw(hw);
	अगर (err) अणु
		dev_err(&पूर्णांकerface->pdev->dev, "init_hw failed: %d\n", err);
		जाओ reinit_err;
	पूर्ण

	err = fm10k_init_queueing_scheme(पूर्णांकerface);
	अगर (err) अणु
		dev_err(&पूर्णांकerface->pdev->dev,
			"init_queueing_scheme failed: %d\n", err);
		जाओ reinit_err;
	पूर्ण

	/* re-associate पूर्णांकerrupts */
	err = fm10k_mbx_request_irq(पूर्णांकerface);
	अगर (err)
		जाओ err_mbx_irq;

	err = fm10k_hw_पढ़ोy(पूर्णांकerface);
	अगर (err)
		जाओ err_खोलो;

	/* update hardware address क्रम VFs अगर perm_addr has changed */
	अगर (hw->mac.type == fm10k_mac_vf) अणु
		अगर (is_valid_ether_addr(hw->mac.perm_addr)) अणु
			ether_addr_copy(hw->mac.addr, hw->mac.perm_addr);
			ether_addr_copy(netdev->perm_addr, hw->mac.perm_addr);
			ether_addr_copy(netdev->dev_addr, hw->mac.perm_addr);
			netdev->addr_assign_type &= ~NET_ADDR_RANDOM;
		पूर्ण

		अगर (hw->mac.vlan_override)
			netdev->features &= ~NETIF_F_HW_VLAN_CTAG_RX;
		अन्यथा
			netdev->features |= NETIF_F_HW_VLAN_CTAG_RX;
	पूर्ण

	err = netअगर_running(netdev) ? fm10k_खोलो(netdev) : 0;
	अगर (err)
		जाओ err_खोलो;

	fm10k_iov_resume(पूर्णांकerface->pdev);

	rtnl_unlock();

	fm10k_resume_macvlan_task(पूर्णांकerface);

	clear_bit(__FM10K_RESETTING, पूर्णांकerface->state);

	वापस err;
err_खोलो:
	fm10k_mbx_मुक्त_irq(पूर्णांकerface);
err_mbx_irq:
	fm10k_clear_queueing_scheme(पूर्णांकerface);
reinit_err:
	netअगर_device_detach(netdev);

	rtnl_unlock();

	clear_bit(__FM10K_RESETTING, पूर्णांकerface->state);

	वापस err;
पूर्ण

अटल व्योम fm10k_detach_subtask(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	u32 __iomem *hw_addr;
	u32 value;

	/* करो nothing अगर netdev is still present or hw_addr is set */
	अगर (netअगर_device_present(netdev) || पूर्णांकerface->hw.hw_addr)
		वापस;

	/* We've lost the PCIe रेजिस्टर space, and can no दीर्घer access the
	 * device. Shut everything except the detach subtask करोwn and prepare
	 * to reset the device in हाल we recover. If we actually prepare क्रम
	 * reset, indicate that we're detached.
	 */
	अगर (fm10k_prepare_क्रम_reset(पूर्णांकerface))
		set_bit(__FM10K_RESET_DETACHED, पूर्णांकerface->state);

	/* check the real address space to see अगर we've recovered */
	hw_addr = READ_ONCE(पूर्णांकerface->uc_addr);
	value = पढ़ोl(hw_addr);
	अगर (~value) अणु
		पूर्णांक err;

		/* Make sure the reset was initiated because we detached,
		 * otherwise we might race with a dअगरferent reset flow.
		 */
		अगर (!test_and_clear_bit(__FM10K_RESET_DETACHED,
					पूर्णांकerface->state))
			वापस;

		/* Restore the hardware address */
		पूर्णांकerface->hw.hw_addr = पूर्णांकerface->uc_addr;

		/* PCIe link has been restored, and the device is active
		 * again. Restore everything and reset the device.
		 */
		err = fm10k_handle_reset(पूर्णांकerface);
		अगर (err) अणु
			netdev_err(netdev, "Unable to reset device: %d\n", err);
			पूर्णांकerface->hw.hw_addr = शून्य;
			वापस;
		पूर्ण

		/* Re-attach the netdev */
		netअगर_device_attach(netdev);
		netdev_warn(netdev, "PCIe link restored, device now attached\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम fm10k_reset_subtask(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक err;

	अगर (!test_and_clear_bit(FM10K_FLAG_RESET_REQUESTED,
				पूर्णांकerface->flags))
		वापस;

	/* If another thपढ़ो has alपढ़ोy prepared to reset the device, we
	 * should not attempt to handle a reset here, since we'd race with
	 * that thपढ़ो. This may happen अगर we suspend the device or अगर the
	 * PCIe link is lost. In this हाल, we'll just ignore the RESET
	 * request, as it will (eventually) be taken care of when the thपढ़ो
	 * which actually started the reset is finished.
	 */
	अगर (!fm10k_prepare_क्रम_reset(पूर्णांकerface))
		वापस;

	netdev_err(पूर्णांकerface->netdev, "Reset interface\n");

	err = fm10k_handle_reset(पूर्णांकerface);
	अगर (err)
		dev_err(&पूर्णांकerface->pdev->dev,
			"fm10k_handle_reset failed: %d\n", err);
पूर्ण

/**
 * fm10k_configure_swpri_map - Configure Receive SWPRI to PC mapping
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Configure the SWPRI to PC mapping क्रम the port.
 **/
अटल व्योम fm10k_configure_swpri_map(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक i;

	/* clear flag indicating update is needed */
	clear_bit(FM10K_FLAG_SWPRI_CONFIG, पूर्णांकerface->flags);

	/* these रेजिस्टरs are only available on the PF */
	अगर (hw->mac.type != fm10k_mac_pf)
		वापस;

	/* configure SWPRI to PC map */
	क्रम (i = 0; i < FM10K_SWPRI_MAX; i++)
		fm10k_ग_लिखो_reg(hw, FM10K_SWPRI_MAP(i),
				netdev_get_prio_tc_map(netdev, i));
पूर्ण

/**
 * fm10k_watchकरोg_update_host_state - Update the link status based on host.
 * @पूर्णांकerface: board निजी काष्ठाure
 **/
अटल व्योम fm10k_watchकरोg_update_host_state(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	s32 err;

	अगर (test_bit(__FM10K_LINK_DOWN, पूर्णांकerface->state)) अणु
		पूर्णांकerface->host_पढ़ोy = false;
		अगर (समय_is_after_jअगरfies(पूर्णांकerface->link_करोwn_event))
			वापस;
		clear_bit(__FM10K_LINK_DOWN, पूर्णांकerface->state);
	पूर्ण

	अगर (test_bit(FM10K_FLAG_SWPRI_CONFIG, पूर्णांकerface->flags)) अणु
		अगर (rtnl_trylock()) अणु
			fm10k_configure_swpri_map(पूर्णांकerface);
			rtnl_unlock();
		पूर्ण
	पूर्ण

	/* lock the mailbox क्रम transmit and receive */
	fm10k_mbx_lock(पूर्णांकerface);

	err = hw->mac.ops.get_host_state(hw, &पूर्णांकerface->host_पढ़ोy);
	अगर (err && समय_is_beक्रमe_jअगरfies(पूर्णांकerface->last_reset))
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);

	/* मुक्त the lock */
	fm10k_mbx_unlock(पूर्णांकerface);
पूर्ण

/**
 * fm10k_mbx_subtask - Process upstream and करोwnstream mailboxes
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * This function will process both the upstream and करोwnstream mailboxes.
 **/
अटल व्योम fm10k_mbx_subtask(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* If we're resetting, bail out */
	अगर (test_bit(__FM10K_RESETTING, पूर्णांकerface->state))
		वापस;

	/* process upstream mailbox and update device state */
	fm10k_watchकरोg_update_host_state(पूर्णांकerface);

	/* process करोwnstream mailboxes */
	fm10k_iov_mbx(पूर्णांकerface);
पूर्ण

/**
 * fm10k_watchकरोg_host_is_पढ़ोy - Update netdev status based on host पढ़ोy
 * @पूर्णांकerface: board निजी काष्ठाure
 **/
अटल व्योम fm10k_watchकरोg_host_is_पढ़ोy(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;

	/* only जारी अगर link state is currently करोwn */
	अगर (netअगर_carrier_ok(netdev))
		वापस;

	netअगर_info(पूर्णांकerface, drv, netdev, "NIC Link is up\n");

	netअगर_carrier_on(netdev);
	netअगर_tx_wake_all_queues(netdev);
पूर्ण

/**
 * fm10k_watchकरोg_host_not_पढ़ोy - Update netdev status based on host not पढ़ोy
 * @पूर्णांकerface: board निजी काष्ठाure
 **/
अटल व्योम fm10k_watchकरोg_host_not_पढ़ोy(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;

	/* only जारी अगर link state is currently up */
	अगर (!netअगर_carrier_ok(netdev))
		वापस;

	netअगर_info(पूर्णांकerface, drv, netdev, "NIC Link is down\n");

	netअगर_carrier_off(netdev);
	netअगर_tx_stop_all_queues(netdev);
पूर्ण

/**
 * fm10k_update_stats - Update the board statistics counters.
 * @पूर्णांकerface: board निजी काष्ठाure
 **/
व्योम fm10k_update_stats(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device_stats *net_stats = &पूर्णांकerface->netdev->stats;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u64 hw_csum_tx_good = 0, hw_csum_rx_good = 0, rx_length_errors = 0;
	u64 rx_चयन_errors = 0, rx_drops = 0, rx_pp_errors = 0;
	u64 rx_link_errors = 0;
	u64 rx_errors = 0, rx_csum_errors = 0, tx_csum_errors = 0;
	u64 restart_queue = 0, tx_busy = 0, alloc_failed = 0;
	u64 rx_bytes_nic = 0, rx_pkts_nic = 0, rx_drops_nic = 0;
	u64 tx_bytes_nic = 0, tx_pkts_nic = 0;
	u64 bytes, pkts;
	पूर्णांक i;

	/* ensure only one thपढ़ो updates stats at a समय */
	अगर (test_and_set_bit(__FM10K_UPDATING_STATS, पूर्णांकerface->state))
		वापस;

	/* करो not allow stats update via service task क्रम next second */
	पूर्णांकerface->next_stats_update = jअगरfies + HZ;

	/* gather some stats to the पूर्णांकerface काष्ठा that are per queue */
	क्रम (bytes = 0, pkts = 0, i = 0; i < पूर्णांकerface->num_tx_queues; i++) अणु
		काष्ठा fm10k_ring *tx_ring = READ_ONCE(पूर्णांकerface->tx_ring[i]);

		अगर (!tx_ring)
			जारी;

		restart_queue += tx_ring->tx_stats.restart_queue;
		tx_busy += tx_ring->tx_stats.tx_busy;
		tx_csum_errors += tx_ring->tx_stats.csum_err;
		bytes += tx_ring->stats.bytes;
		pkts += tx_ring->stats.packets;
		hw_csum_tx_good += tx_ring->tx_stats.csum_good;
	पूर्ण

	पूर्णांकerface->restart_queue = restart_queue;
	पूर्णांकerface->tx_busy = tx_busy;
	net_stats->tx_bytes = bytes;
	net_stats->tx_packets = pkts;
	पूर्णांकerface->tx_csum_errors = tx_csum_errors;
	पूर्णांकerface->hw_csum_tx_good = hw_csum_tx_good;

	/* gather some stats to the पूर्णांकerface काष्ठा that are per queue */
	क्रम (bytes = 0, pkts = 0, i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
		काष्ठा fm10k_ring *rx_ring = READ_ONCE(पूर्णांकerface->rx_ring[i]);

		अगर (!rx_ring)
			जारी;

		bytes += rx_ring->stats.bytes;
		pkts += rx_ring->stats.packets;
		alloc_failed += rx_ring->rx_stats.alloc_failed;
		rx_csum_errors += rx_ring->rx_stats.csum_err;
		rx_errors += rx_ring->rx_stats.errors;
		hw_csum_rx_good += rx_ring->rx_stats.csum_good;
		rx_चयन_errors += rx_ring->rx_stats.चयन_errors;
		rx_drops += rx_ring->rx_stats.drops;
		rx_pp_errors += rx_ring->rx_stats.pp_errors;
		rx_link_errors += rx_ring->rx_stats.link_errors;
		rx_length_errors += rx_ring->rx_stats.length_errors;
	पूर्ण

	net_stats->rx_bytes = bytes;
	net_stats->rx_packets = pkts;
	पूर्णांकerface->alloc_failed = alloc_failed;
	पूर्णांकerface->rx_csum_errors = rx_csum_errors;
	पूर्णांकerface->hw_csum_rx_good = hw_csum_rx_good;
	पूर्णांकerface->rx_चयन_errors = rx_चयन_errors;
	पूर्णांकerface->rx_drops = rx_drops;
	पूर्णांकerface->rx_pp_errors = rx_pp_errors;
	पूर्णांकerface->rx_link_errors = rx_link_errors;
	पूर्णांकerface->rx_length_errors = rx_length_errors;

	hw->mac.ops.update_hw_stats(hw, &पूर्णांकerface->stats);

	क्रम (i = 0; i < hw->mac.max_queues; i++) अणु
		काष्ठा fm10k_hw_stats_q *q = &पूर्णांकerface->stats.q[i];

		tx_bytes_nic += q->tx_bytes.count;
		tx_pkts_nic += q->tx_packets.count;
		rx_bytes_nic += q->rx_bytes.count;
		rx_pkts_nic += q->rx_packets.count;
		rx_drops_nic += q->rx_drops.count;
	पूर्ण

	पूर्णांकerface->tx_bytes_nic = tx_bytes_nic;
	पूर्णांकerface->tx_packets_nic = tx_pkts_nic;
	पूर्णांकerface->rx_bytes_nic = rx_bytes_nic;
	पूर्णांकerface->rx_packets_nic = rx_pkts_nic;
	पूर्णांकerface->rx_drops_nic = rx_drops_nic;

	/* Fill out the OS statistics काष्ठाure */
	net_stats->rx_errors = rx_errors;
	net_stats->rx_dropped = पूर्णांकerface->stats.nodesc_drop.count;

	/* Update VF statistics */
	fm10k_iov_update_stats(पूर्णांकerface);

	clear_bit(__FM10K_UPDATING_STATS, पूर्णांकerface->state);
पूर्ण

/**
 * fm10k_watchकरोg_flush_tx - flush queues on host not पढ़ोy
 * @पूर्णांकerface: poपूर्णांकer to the device पूर्णांकerface काष्ठाure
 **/
अटल व्योम fm10k_watchकरोg_flush_tx(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक some_tx_pending = 0;
	पूर्णांक i;

	/* nothing to करो अगर carrier is up */
	अगर (netअगर_carrier_ok(पूर्णांकerface->netdev))
		वापस;

	क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++) अणु
		काष्ठा fm10k_ring *tx_ring = पूर्णांकerface->tx_ring[i];

		अगर (tx_ring->next_to_use != tx_ring->next_to_clean) अणु
			some_tx_pending = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* We've lost link, so the controller stops DMA, but we've got
	 * queued Tx work that's never going to get करोne, so reset
	 * controller to flush Tx.
	 */
	अगर (some_tx_pending)
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);
पूर्ण

/**
 * fm10k_watchकरोg_subtask - check and bring link up
 * @पूर्णांकerface: poपूर्णांकer to the device पूर्णांकerface काष्ठाure
 **/
अटल व्योम fm10k_watchकरोg_subtask(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(__FM10K_DOWN, पूर्णांकerface->state) ||
	    test_bit(__FM10K_RESETTING, पूर्णांकerface->state))
		वापस;

	अगर (पूर्णांकerface->host_पढ़ोy)
		fm10k_watchकरोg_host_is_पढ़ोy(पूर्णांकerface);
	अन्यथा
		fm10k_watchकरोg_host_not_पढ़ोy(पूर्णांकerface);

	/* update stats only once every second */
	अगर (समय_is_beक्रमe_jअगरfies(पूर्णांकerface->next_stats_update))
		fm10k_update_stats(पूर्णांकerface);

	/* flush any uncompleted work */
	fm10k_watchकरोg_flush_tx(पूर्णांकerface);
पूर्ण

/**
 * fm10k_check_hang_subtask - check क्रम hung queues and dropped पूर्णांकerrupts
 * @पूर्णांकerface: poपूर्णांकer to the device पूर्णांकerface काष्ठाure
 *
 * This function serves two purposes.  First it strobes the पूर्णांकerrupt lines
 * in order to make certain पूर्णांकerrupts are occurring.  Secondly it sets the
 * bits needed to check क्रम TX hangs.  As a result we should immediately
 * determine अगर a hang has occurred.
 */
अटल व्योम fm10k_check_hang_subtask(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* If we're करोwn or resetting, just bail */
	अगर (test_bit(__FM10K_DOWN, पूर्णांकerface->state) ||
	    test_bit(__FM10K_RESETTING, पूर्णांकerface->state))
		वापस;

	/* rate limit tx hang checks to only once every 2 seconds */
	अगर (समय_is_after_eq_jअगरfies(पूर्णांकerface->next_tx_hang_check))
		वापस;
	पूर्णांकerface->next_tx_hang_check = jअगरfies + (2 * HZ);

	अगर (netअगर_carrier_ok(पूर्णांकerface->netdev)) अणु
		पूर्णांक i;

		/* Force detection of hung controller */
		क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++)
			set_check_क्रम_tx_hang(पूर्णांकerface->tx_ring[i]);

		/* Rearm all in-use q_vectors क्रम immediate firing */
		क्रम (i = 0; i < पूर्णांकerface->num_q_vectors; i++) अणु
			काष्ठा fm10k_q_vector *qv = पूर्णांकerface->q_vector[i];

			अगर (!qv->tx.count && !qv->rx.count)
				जारी;
			ग_लिखोl(FM10K_ITR_ENABLE | FM10K_ITR_PENDING2, qv->itr);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * fm10k_service_task - manages and runs subtasks
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 **/
अटल व्योम fm10k_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;

	पूर्णांकerface = container_of(work, काष्ठा fm10k_पूर्णांकfc, service_task);

	/* Check whether we're detached first */
	fm10k_detach_subtask(पूर्णांकerface);

	/* tasks run even when पूर्णांकerface is करोwn */
	fm10k_mbx_subtask(पूर्णांकerface);
	fm10k_reset_subtask(पूर्णांकerface);

	/* tasks only run when पूर्णांकerface is up */
	fm10k_watchकरोg_subtask(पूर्णांकerface);
	fm10k_check_hang_subtask(पूर्णांकerface);

	/* release lock on service events to allow scheduling next event */
	fm10k_service_event_complete(पूर्णांकerface);
पूर्ण

/**
 * fm10k_macvlan_task - send queued MAC/VLAN requests to चयन manager
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 *
 * This work item handles sending MAC/VLAN updates to the चयन manager. When
 * the पूर्णांकerface is up, it will attempt to queue mailbox messages to the
 * चयन manager requesting updates क्रम MAC/VLAN pairs. If the Tx fअगरo of the
 * mailbox is full, it will reschedule itself to try again in a लघु जबतक.
 * This ensures that the driver करोes not overload the चयन mailbox with too
 * many simultaneous requests, causing an unnecessary reset.
 **/
अटल व्योम fm10k_macvlan_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fm10k_macvlan_request *item;
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	काष्ठा delayed_work *dwork;
	काष्ठा list_head *requests;
	काष्ठा fm10k_hw *hw;
	अचिन्हित दीर्घ flags;

	dwork = to_delayed_work(work);
	पूर्णांकerface = container_of(dwork, काष्ठा fm10k_पूर्णांकfc, macvlan_task);
	hw = &पूर्णांकerface->hw;
	requests = &पूर्णांकerface->macvlan_requests;

	करो अणु
		/* Pop the first item off the list */
		spin_lock_irqsave(&पूर्णांकerface->macvlan_lock, flags);
		item = list_first_entry_or_null(requests,
						काष्ठा fm10k_macvlan_request,
						list);
		अगर (item)
			list_del_init(&item->list);

		spin_unlock_irqrestore(&पूर्णांकerface->macvlan_lock, flags);

		/* We have no more items to process */
		अगर (!item)
			जाओ करोne;

		fm10k_mbx_lock(पूर्णांकerface);

		/* Check that we have plenty of space to send the message. We
		 * want to ensure that the mailbox stays low enough to aव्योम a
		 * change in the host state, otherwise we may see spurious
		 * link up / link करोwn notअगरications.
		 */
		अगर (!hw->mbx.ops.tx_पढ़ोy(&hw->mbx, FM10K_VFMBX_MSG_MTU + 5)) अणु
			hw->mbx.ops.process(hw, &hw->mbx);
			set_bit(__FM10K_MACVLAN_REQUEST, पूर्णांकerface->state);
			fm10k_mbx_unlock(पूर्णांकerface);

			/* Put the request back on the list */
			spin_lock_irqsave(&पूर्णांकerface->macvlan_lock, flags);
			list_add(&item->list, requests);
			spin_unlock_irqrestore(&पूर्णांकerface->macvlan_lock, flags);
			अवरोध;
		पूर्ण

		चयन (item->type) अणु
		हाल FM10K_MC_MAC_REQUEST:
			hw->mac.ops.update_mc_addr(hw,
						   item->mac.glort,
						   item->mac.addr,
						   item->mac.vid,
						   item->set);
			अवरोध;
		हाल FM10K_UC_MAC_REQUEST:
			hw->mac.ops.update_uc_addr(hw,
						   item->mac.glort,
						   item->mac.addr,
						   item->mac.vid,
						   item->set,
						   0);
			अवरोध;
		हाल FM10K_VLAN_REQUEST:
			hw->mac.ops.update_vlan(hw,
						item->vlan.vid,
						item->vlan.vsi,
						item->set);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		fm10k_mbx_unlock(पूर्णांकerface);

		/* Free the item now that we've sent the update */
		kमुक्त(item);
	पूर्ण जबतक (true);

करोne:
	WARN_ON(!test_bit(__FM10K_MACVLAN_SCHED, पूर्णांकerface->state));

	/* flush memory to make sure state is correct */
	smp_mb__beक्रमe_atomic();
	clear_bit(__FM10K_MACVLAN_SCHED, पूर्णांकerface->state);

	/* If a MAC/VLAN request was scheduled since we started, we should
	 * re-schedule. However, there is no reason to re-schedule अगर there is
	 * no work to करो.
	 */
	अगर (test_bit(__FM10K_MACVLAN_REQUEST, पूर्णांकerface->state))
		fm10k_macvlan_schedule(पूर्णांकerface);
पूर्ण

/**
 * fm10k_configure_tx_ring - Configure Tx ring after Reset
 * @पूर्णांकerface: board निजी काष्ठाure
 * @ring: काष्ठाure containing ring specअगरic data
 *
 * Configure the Tx descriptor ring after a reset.
 **/
अटल व्योम fm10k_configure_tx_ring(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				    काष्ठा fm10k_ring *ring)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u64 tdba = ring->dma;
	u32 size = ring->count * माप(काष्ठा fm10k_tx_desc);
	u32 txपूर्णांक = FM10K_INT_MAP_DISABLE;
	u32 txdctl = BIT(FM10K_TXDCTL_MAX_TIME_SHIFT) | FM10K_TXDCTL_ENABLE;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to aव्योम issues जबतक updating state */
	fm10k_ग_लिखो_reg(hw, FM10K_TXDCTL(reg_idx), 0);
	fm10k_ग_लिखो_flush(hw);

	/* possible poll here to verअगरy ring resources have been cleaned */

	/* set location and size क्रम descriptor ring */
	fm10k_ग_लिखो_reg(hw, FM10K_TDBAL(reg_idx), tdba & DMA_BIT_MASK(32));
	fm10k_ग_लिखो_reg(hw, FM10K_TDBAH(reg_idx), tdba >> 32);
	fm10k_ग_लिखो_reg(hw, FM10K_TDLEN(reg_idx), size);

	/* reset head and tail poपूर्णांकers */
	fm10k_ग_लिखो_reg(hw, FM10K_TDH(reg_idx), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_TDT(reg_idx), 0);

	/* store tail poपूर्णांकer */
	ring->tail = &पूर्णांकerface->uc_addr[FM10K_TDT(reg_idx)];

	/* reset ntu and ntc to place SW in sync with hardware */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;

	/* Map पूर्णांकerrupt */
	अगर (ring->q_vector) अणु
		txपूर्णांक = ring->q_vector->v_idx + NON_Q_VECTORS;
		txपूर्णांक |= FM10K_INT_MAP_TIMER0;
	पूर्ण

	fm10k_ग_लिखो_reg(hw, FM10K_TXINT(reg_idx), txपूर्णांक);

	/* enable use of FTAG bit in Tx descriptor, रेजिस्टर is RO क्रम VF */
	fm10k_ग_लिखो_reg(hw, FM10K_PFVTCTL(reg_idx),
			FM10K_PFVTCTL_FTAG_DESC_ENABLE);

	/* Initialize XPS */
	अगर (!test_and_set_bit(__FM10K_TX_XPS_INIT_DONE, ring->state) &&
	    ring->q_vector)
		netअगर_set_xps_queue(ring->netdev,
				    &ring->q_vector->affinity_mask,
				    ring->queue_index);

	/* enable queue */
	fm10k_ग_लिखो_reg(hw, FM10K_TXDCTL(reg_idx), txdctl);
पूर्ण

/**
 * fm10k_enable_tx_ring - Verअगरy Tx ring is enabled after configuration
 * @पूर्णांकerface: board निजी काष्ठाure
 * @ring: काष्ठाure containing ring specअगरic data
 *
 * Verअगरy the Tx descriptor ring is पढ़ोy क्रम transmit.
 **/
अटल व्योम fm10k_enable_tx_ring(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				 काष्ठा fm10k_ring *ring)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक रुको_loop = 10;
	u32 txdctl;
	u8 reg_idx = ring->reg_idx;

	/* अगर we are alपढ़ोy enabled just निकास */
	अगर (fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(reg_idx)) & FM10K_TXDCTL_ENABLE)
		वापस;

	/* poll to verअगरy queue is enabled */
	करो अणु
		usleep_range(1000, 2000);
		txdctl = fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(reg_idx));
	पूर्ण जबतक (!(txdctl & FM10K_TXDCTL_ENABLE) && --रुको_loop);
	अगर (!रुको_loop)
		netअगर_err(पूर्णांकerface, drv, पूर्णांकerface->netdev,
			  "Could not enable Tx Queue %d\n", reg_idx);
पूर्ण

/**
 * fm10k_configure_tx - Configure Transmit Unit after Reset
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम fm10k_configure_tx(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i;

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */
	क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++)
		fm10k_configure_tx_ring(पूर्णांकerface, पूर्णांकerface->tx_ring[i]);

	/* poll here to verअगरy that Tx rings are now enabled */
	क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++)
		fm10k_enable_tx_ring(पूर्णांकerface, पूर्णांकerface->tx_ring[i]);
पूर्ण

/**
 * fm10k_configure_rx_ring - Configure Rx ring after Reset
 * @पूर्णांकerface: board निजी काष्ठाure
 * @ring: काष्ठाure containing ring specअगरic data
 *
 * Configure the Rx descriptor ring after a reset.
 **/
अटल व्योम fm10k_configure_rx_ring(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				    काष्ठा fm10k_ring *ring)
अणु
	u64 rdba = ring->dma;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u32 size = ring->count * माप(जोड़ fm10k_rx_desc);
	u32 rxqctl, rxdctl = FM10K_RXDCTL_WRITE_BACK_MIN_DELAY;
	u32 srrctl = FM10K_SRRCTL_BUFFER_CHAINING_EN;
	u32 rxपूर्णांक = FM10K_INT_MAP_DISABLE;
	u8 rx_छोड़ो = पूर्णांकerface->rx_छोड़ो;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to aव्योम issues जबतक updating state */
	rxqctl = fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(reg_idx));
	rxqctl &= ~FM10K_RXQCTL_ENABLE;
	fm10k_ग_लिखो_reg(hw, FM10K_RXQCTL(reg_idx), rxqctl);
	fm10k_ग_लिखो_flush(hw);

	/* possible poll here to verअगरy ring resources have been cleaned */

	/* set location and size क्रम descriptor ring */
	fm10k_ग_लिखो_reg(hw, FM10K_RDBAL(reg_idx), rdba & DMA_BIT_MASK(32));
	fm10k_ग_लिखो_reg(hw, FM10K_RDBAH(reg_idx), rdba >> 32);
	fm10k_ग_लिखो_reg(hw, FM10K_RDLEN(reg_idx), size);

	/* reset head and tail poपूर्णांकers */
	fm10k_ग_लिखो_reg(hw, FM10K_RDH(reg_idx), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_RDT(reg_idx), 0);

	/* store tail poपूर्णांकer */
	ring->tail = &पूर्णांकerface->uc_addr[FM10K_RDT(reg_idx)];

	/* reset ntu and ntc to place SW in sync with hardware */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
	ring->next_to_alloc = 0;

	/* Configure the Rx buffer size क्रम one buff without split */
	srrctl |= FM10K_RX_BUFSZ >> FM10K_SRRCTL_BSIZEPKT_SHIFT;

	/* Configure the Rx ring to suppress loopback packets */
	srrctl |= FM10K_SRRCTL_LOOPBACK_SUPPRESS;
	fm10k_ग_लिखो_reg(hw, FM10K_SRRCTL(reg_idx), srrctl);

	/* Enable drop on empty */
#अगर_घोषित CONFIG_DCB
	अगर (पूर्णांकerface->pfc_en)
		rx_छोड़ो = पूर्णांकerface->pfc_en;
#पूर्ण_अगर
	अगर (!(rx_छोड़ो & BIT(ring->qos_pc)))
		rxdctl |= FM10K_RXDCTL_DROP_ON_EMPTY;

	fm10k_ग_लिखो_reg(hw, FM10K_RXDCTL(reg_idx), rxdctl);

	/* assign शेष VLAN to queue */
	ring->vid = hw->mac.शेष_vid;

	/* अगर we have an active VLAN, disable शेष VLAN ID */
	अगर (test_bit(hw->mac.शेष_vid, पूर्णांकerface->active_vlans))
		ring->vid |= FM10K_VLAN_CLEAR;

	/* Map पूर्णांकerrupt */
	अगर (ring->q_vector) अणु
		rxपूर्णांक = ring->q_vector->v_idx + NON_Q_VECTORS;
		rxपूर्णांक |= FM10K_INT_MAP_TIMER1;
	पूर्ण

	fm10k_ग_लिखो_reg(hw, FM10K_RXINT(reg_idx), rxपूर्णांक);

	/* enable queue */
	rxqctl = fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(reg_idx));
	rxqctl |= FM10K_RXQCTL_ENABLE;
	fm10k_ग_लिखो_reg(hw, FM10K_RXQCTL(reg_idx), rxqctl);

	/* place buffers on ring क्रम receive data */
	fm10k_alloc_rx_buffers(ring, fm10k_desc_unused(ring));
पूर्ण

/**
 * fm10k_update_rx_drop_en - Configures the drop enable bits क्रम Rx rings
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Configure the drop enable bits क्रम the Rx rings.
 **/
व्योम fm10k_update_rx_drop_en(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u8 rx_छोड़ो = पूर्णांकerface->rx_छोड़ो;
	पूर्णांक i;

#अगर_घोषित CONFIG_DCB
	अगर (पूर्णांकerface->pfc_en)
		rx_छोड़ो = पूर्णांकerface->pfc_en;

#पूर्ण_अगर
	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
		काष्ठा fm10k_ring *ring = पूर्णांकerface->rx_ring[i];
		u32 rxdctl = FM10K_RXDCTL_WRITE_BACK_MIN_DELAY;
		u8 reg_idx = ring->reg_idx;

		अगर (!(rx_छोड़ो & BIT(ring->qos_pc)))
			rxdctl |= FM10K_RXDCTL_DROP_ON_EMPTY;

		fm10k_ग_लिखो_reg(hw, FM10K_RXDCTL(reg_idx), rxdctl);
	पूर्ण
पूर्ण

/**
 * fm10k_configure_dglort - Configure Receive DGLORT after reset
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Configure the DGLORT description and RSS tables.
 **/
अटल व्योम fm10k_configure_dglort(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_dglort_cfg dglort = अणु 0 पूर्ण;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक i;
	u32 mrqc;

	/* Fill out hash function seeds */
	क्रम (i = 0; i < FM10K_RSSRK_SIZE; i++)
		fm10k_ग_लिखो_reg(hw, FM10K_RSSRK(0, i), पूर्णांकerface->rssrk[i]);

	/* Write RETA table to hardware */
	क्रम (i = 0; i < FM10K_RETA_SIZE; i++)
		fm10k_ग_लिखो_reg(hw, FM10K_RETA(0, i), पूर्णांकerface->reta[i]);

	/* Generate RSS hash based on packet types, TCP/UDP
	 * port numbers and/or IPv4/v6 src and dst addresses
	 */
	mrqc = FM10K_MRQC_IPV4 |
	       FM10K_MRQC_TCP_IPV4 |
	       FM10K_MRQC_IPV6 |
	       FM10K_MRQC_TCP_IPV6;

	अगर (test_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP, पूर्णांकerface->flags))
		mrqc |= FM10K_MRQC_UDP_IPV4;
	अगर (test_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP, पूर्णांकerface->flags))
		mrqc |= FM10K_MRQC_UDP_IPV6;

	fm10k_ग_लिखो_reg(hw, FM10K_MRQC(0), mrqc);

	/* configure शेष DGLORT mapping क्रम RSS/DCB */
	dglort.inner_rss = 1;
	dglort.rss_l = fls(पूर्णांकerface->ring_feature[RING_F_RSS].mask);
	dglort.pc_l = fls(पूर्णांकerface->ring_feature[RING_F_QOS].mask);
	hw->mac.ops.configure_dglort_map(hw, &dglort);

	/* assign GLORT per queue क्रम queue mapped testing */
	अगर (पूर्णांकerface->glort_count > 64) अणु
		स_रखो(&dglort, 0, माप(dglort));
		dglort.inner_rss = 1;
		dglort.glort = पूर्णांकerface->glort + 64;
		dglort.idx = fm10k_dglort_pf_queue;
		dglort.queue_l = fls(पूर्णांकerface->num_rx_queues - 1);
		hw->mac.ops.configure_dglort_map(hw, &dglort);
	पूर्ण

	/* assign glort value क्रम RSS/DCB specअगरic to this पूर्णांकerface */
	स_रखो(&dglort, 0, माप(dglort));
	dglort.inner_rss = 1;
	dglort.glort = पूर्णांकerface->glort;
	dglort.rss_l = fls(पूर्णांकerface->ring_feature[RING_F_RSS].mask);
	dglort.pc_l = fls(पूर्णांकerface->ring_feature[RING_F_QOS].mask);
	/* configure DGLORT mapping क्रम RSS/DCB */
	dglort.idx = fm10k_dglort_pf_rss;
	अगर (पूर्णांकerface->l2_accel)
		dglort.shared_l = fls(पूर्णांकerface->l2_accel->size);
	hw->mac.ops.configure_dglort_map(hw, &dglort);
पूर्ण

/**
 * fm10k_configure_rx - Configure Receive Unit after Reset
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम fm10k_configure_rx(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i;

	/* Configure SWPRI to PC map */
	fm10k_configure_swpri_map(पूर्णांकerface);

	/* Configure RSS and DGLORT map */
	fm10k_configure_dglort(पूर्णांकerface);

	/* Setup the HW Rx Head and Tail descriptor poपूर्णांकers */
	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++)
		fm10k_configure_rx_ring(पूर्णांकerface, पूर्णांकerface->rx_ring[i]);

	/* possible poll here to verअगरy that Rx rings are now enabled */
पूर्ण

अटल व्योम fm10k_napi_enable_all(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_q_vector *q_vector;
	पूर्णांक q_idx;

	क्रम (q_idx = 0; q_idx < पूर्णांकerface->num_q_vectors; q_idx++) अणु
		q_vector = पूर्णांकerface->q_vector[q_idx];
		napi_enable(&q_vector->napi);
	पूर्ण
पूर्ण

अटल irqवापस_t fm10k_msix_clean_rings(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा fm10k_q_vector *q_vector = data;

	अगर (q_vector->rx.count || q_vector->tx.count)
		napi_schedule_irqoff(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fm10k_msix_mbx_vf(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;

	/* re-enable mailbox पूर्णांकerrupt and indicate 20us delay */
	fm10k_ग_लिखो_reg(hw, FM10K_VFITR(FM10K_MBX_VECTOR),
			(FM10K_MBX_INT_DELAY >> hw->mac.itr_scale) |
			FM10K_ITR_ENABLE);

	/* service upstream mailbox */
	अगर (fm10k_mbx_trylock(पूर्णांकerface)) अणु
		mbx->ops.process(hw, mbx);
		fm10k_mbx_unlock(पूर्णांकerface);
	पूर्ण

	hw->mac.get_host_state = true;
	fm10k_service_event_schedule(पूर्णांकerface);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा FM10K_ERR_MSG(type) हाल (type): error = #type; अवरोध
अटल व्योम fm10k_handle_fault(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, पूर्णांक type,
			       काष्ठा fm10k_fault *fault)
अणु
	काष्ठा pci_dev *pdev = पूर्णांकerface->pdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_iov_data *iov_data = पूर्णांकerface->iov_data;
	अक्षर *error;

	चयन (type) अणु
	हाल FM10K_PCA_FAULT:
		चयन (fault->type) अणु
		शेष:
			error = "Unknown PCA error";
			अवरोध;
		FM10K_ERR_MSG(PCA_NO_FAULT);
		FM10K_ERR_MSG(PCA_UNMAPPED_ADDR);
		FM10K_ERR_MSG(PCA_BAD_QACCESS_PF);
		FM10K_ERR_MSG(PCA_BAD_QACCESS_VF);
		FM10K_ERR_MSG(PCA_MALICIOUS_REQ);
		FM10K_ERR_MSG(PCA_POISONED_TLP);
		FM10K_ERR_MSG(PCA_TLP_ABORT);
		पूर्ण
		अवरोध;
	हाल FM10K_THI_FAULT:
		चयन (fault->type) अणु
		शेष:
			error = "Unknown THI error";
			अवरोध;
		FM10K_ERR_MSG(THI_NO_FAULT);
		FM10K_ERR_MSG(THI_MAL_DIS_Q_FAULT);
		पूर्ण
		अवरोध;
	हाल FM10K_FUM_FAULT:
		चयन (fault->type) अणु
		शेष:
			error = "Unknown FUM error";
			अवरोध;
		FM10K_ERR_MSG(FUM_NO_FAULT);
		FM10K_ERR_MSG(FUM_UNMAPPED_ADDR);
		FM10K_ERR_MSG(FUM_BAD_VF_QACCESS);
		FM10K_ERR_MSG(FUM_ADD_DECODE_ERR);
		FM10K_ERR_MSG(FUM_RO_ERROR);
		FM10K_ERR_MSG(FUM_QPRC_CRC_ERROR);
		FM10K_ERR_MSG(FUM_CSR_TIMEOUT);
		FM10K_ERR_MSG(FUM_INVALID_TYPE);
		FM10K_ERR_MSG(FUM_INVALID_LENGTH);
		FM10K_ERR_MSG(FUM_INVALID_BE);
		FM10K_ERR_MSG(FUM_INVALID_ALIGN);
		पूर्ण
		अवरोध;
	शेष:
		error = "Undocumented fault";
		अवरोध;
	पूर्ण

	dev_warn(&pdev->dev,
		 "%s Address: 0x%llx SpecInfo: 0x%x Func: %02x.%0x\n",
		 error, fault->address, fault->specinfo,
		 PCI_SLOT(fault->func), PCI_FUNC(fault->func));

	/* For VF faults, clear out the respective LPORT, reset the queue
	 * resources, and then reconnect to the mailbox. This allows the
	 * VF in question to resume behavior. For transient faults that are
	 * the result of non-malicious behavior this will log the fault and
	 * allow the VF to resume functionality. Obviously क्रम malicious VFs
	 * they will be able to attempt malicious behavior again. In this
	 * हाल, the प्रणाली administrator will need to step in and manually
	 * हटाओ or disable the VF in question.
	 */
	अगर (fault->func && iov_data) अणु
		पूर्णांक vf = fault->func - 1;
		काष्ठा fm10k_vf_info *vf_info = &iov_data->vf_info[vf];

		hw->iov.ops.reset_lport(hw, vf_info);
		hw->iov.ops.reset_resources(hw, vf_info);

		/* reset_lport disables the VF, so re-enable it */
		hw->iov.ops.set_lport(hw, vf_info, vf,
				      FM10K_VF_FLAG_MULTI_CAPABLE);

		/* reset_resources will disconnect from the mbx  */
		vf_info->mbx.ops.connect(hw, &vf_info->mbx);
	पूर्ण
पूर्ण

अटल व्योम fm10k_report_fault(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u32 eicr)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_fault fault = अणु 0 पूर्ण;
	पूर्णांक type, err;

	क्रम (eicr &= FM10K_EICR_FAULT_MASK, type = FM10K_PCA_FAULT;
	     eicr;
	     eicr >>= 1, type += FM10K_FAULT_SIZE) अणु
		/* only check अगर there is an error reported */
		अगर (!(eicr & 0x1))
			जारी;

		/* retrieve fault info */
		err = hw->mac.ops.get_fault(hw, type, &fault);
		अगर (err) अणु
			dev_err(&पूर्णांकerface->pdev->dev,
				"error reading fault\n");
			जारी;
		पूर्ण

		fm10k_handle_fault(पूर्णांकerface, type, &fault);
	पूर्ण
पूर्ण

अटल व्योम fm10k_reset_drop_on_empty(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u32 eicr)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	स्थिर u32 rxdctl = FM10K_RXDCTL_WRITE_BACK_MIN_DELAY;
	u32 maxholdq;
	पूर्णांक q;

	अगर (!(eicr & FM10K_EICR_MAXHOLDTIME))
		वापस;

	maxholdq = fm10k_पढ़ो_reg(hw, FM10K_MAXHOLDQ(7));
	अगर (maxholdq)
		fm10k_ग_लिखो_reg(hw, FM10K_MAXHOLDQ(7), maxholdq);
	क्रम (q = 255;;) अणु
		अगर (maxholdq & BIT(31)) अणु
			अगर (q < FM10K_MAX_QUEUES_PF) अणु
				पूर्णांकerface->rx_overrun_pf++;
				fm10k_ग_लिखो_reg(hw, FM10K_RXDCTL(q), rxdctl);
			पूर्ण अन्यथा अणु
				पूर्णांकerface->rx_overrun_vf++;
			पूर्ण
		पूर्ण

		maxholdq *= 2;
		अगर (!maxholdq)
			q &= ~(32 - 1);

		अगर (!q)
			अवरोध;

		अगर (q-- % 32)
			जारी;

		maxholdq = fm10k_पढ़ो_reg(hw, FM10K_MAXHOLDQ(q / 32));
		अगर (maxholdq)
			fm10k_ग_लिखो_reg(hw, FM10K_MAXHOLDQ(q / 32), maxholdq);
	पूर्ण
पूर्ण

अटल irqवापस_t fm10k_msix_mbx_pf(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = data;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 eicr;
	s32 err = 0;

	/* unmask any set bits related to this पूर्णांकerrupt */
	eicr = fm10k_पढ़ो_reg(hw, FM10K_EICR);
	fm10k_ग_लिखो_reg(hw, FM10K_EICR, eicr & (FM10K_EICR_MAILBOX |
						FM10K_EICR_SWITCHREADY |
						FM10K_EICR_SWITCHNOTREADY));

	/* report any faults found to the message log */
	fm10k_report_fault(पूर्णांकerface, eicr);

	/* reset any queues disabled due to receiver overrun */
	fm10k_reset_drop_on_empty(पूर्णांकerface, eicr);

	/* service mailboxes */
	अगर (fm10k_mbx_trylock(पूर्णांकerface)) अणु
		err = mbx->ops.process(hw, mbx);
		/* handle VFLRE events */
		fm10k_iov_event(पूर्णांकerface);
		fm10k_mbx_unlock(पूर्णांकerface);
	पूर्ण

	अगर (err == FM10K_ERR_RESET_REQUESTED)
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);

	/* अगर चयन toggled state we should reset GLORTs */
	अगर (eicr & FM10K_EICR_SWITCHNOTREADY) अणु
		/* क्रमce link करोwn क्रम at least 4 seconds */
		पूर्णांकerface->link_करोwn_event = jअगरfies + (4 * HZ);
		set_bit(__FM10K_LINK_DOWN, पूर्णांकerface->state);

		/* reset dglort_map back to no config */
		hw->mac.dglort_map = FM10K_DGLORTMAP_NONE;
	पूर्ण

	/* we should validate host state after पूर्णांकerrupt event */
	hw->mac.get_host_state = true;

	/* validate host state, and handle VF mailboxes in the service task */
	fm10k_service_event_schedule(पूर्णांकerface);

	/* re-enable mailbox पूर्णांकerrupt and indicate 20us delay */
	fm10k_ग_लिखो_reg(hw, FM10K_ITR(FM10K_MBX_VECTOR),
			(FM10K_MBX_INT_DELAY >> hw->mac.itr_scale) |
			FM10K_ITR_ENABLE);

	वापस IRQ_HANDLED;
पूर्ण

व्योम fm10k_mbx_मुक्त_irq(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा msix_entry *entry;
	पूर्णांक itr_reg;

	/* no mailbox IRQ to मुक्त अगर MSI-X is not enabled */
	अगर (!पूर्णांकerface->msix_entries)
		वापस;

	entry = &पूर्णांकerface->msix_entries[FM10K_MBX_VECTOR];

	/* disconnect the mailbox */
	hw->mbx.ops.disconnect(hw, &hw->mbx);

	/* disable Mailbox cause */
	अगर (hw->mac.type == fm10k_mac_pf) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_EIMR,
				FM10K_EIMR_DISABLE(PCA_FAULT) |
				FM10K_EIMR_DISABLE(FUM_FAULT) |
				FM10K_EIMR_DISABLE(MAILBOX) |
				FM10K_EIMR_DISABLE(SWITCHREADY) |
				FM10K_EIMR_DISABLE(SWITCHNOTREADY) |
				FM10K_EIMR_DISABLE(SRAMERROR) |
				FM10K_EIMR_DISABLE(VFLR) |
				FM10K_EIMR_DISABLE(MAXHOLDTIME));
		itr_reg = FM10K_ITR(FM10K_MBX_VECTOR);
	पूर्ण अन्यथा अणु
		itr_reg = FM10K_VFITR(FM10K_MBX_VECTOR);
	पूर्ण

	fm10k_ग_लिखो_reg(hw, itr_reg, FM10K_ITR_MASK_SET);

	मुक्त_irq(entry->vector, पूर्णांकerface);
पूर्ण

अटल s32 fm10k_mbx_mac_addr(काष्ठा fm10k_hw *hw, u32 **results,
			      काष्ठा fm10k_mbx_info *mbx)
अणु
	bool vlan_override = hw->mac.vlan_override;
	u16 शेष_vid = hw->mac.शेष_vid;
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	s32 err;

	err = fm10k_msg_mac_vlan_vf(hw, results, mbx);
	अगर (err)
		वापस err;

	पूर्णांकerface = container_of(hw, काष्ठा fm10k_पूर्णांकfc, hw);

	/* MAC was changed so we need reset */
	अगर (is_valid_ether_addr(hw->mac.perm_addr) &&
	    !ether_addr_equal(hw->mac.perm_addr, hw->mac.addr))
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);

	/* VLAN override was changed, or शेष VLAN changed */
	अगर ((vlan_override != hw->mac.vlan_override) ||
	    (शेष_vid != hw->mac.शेष_vid))
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);

	वापस 0;
पूर्ण

/* generic error handler क्रम mailbox issues */
अटल s32 fm10k_mbx_error(काष्ठा fm10k_hw *hw, u32 **results,
			   काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	काष्ठा pci_dev *pdev;

	पूर्णांकerface = container_of(hw, काष्ठा fm10k_पूर्णांकfc, hw);
	pdev = पूर्णांकerface->pdev;

	dev_err(&pdev->dev, "Unknown message ID %u\n",
		**results & FM10K_TLV_ID_MASK);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fm10k_msg_data vf_mbx_data[] = अणु
	FM10K_TLV_MSG_TEST_HANDLER(fm10k_tlv_msg_test),
	FM10K_VF_MSG_MAC_VLAN_HANDLER(fm10k_mbx_mac_addr),
	FM10K_VF_MSG_LPORT_STATE_HANDLER(fm10k_msg_lport_state_vf),
	FM10K_TLV_MSG_ERROR_HANDLER(fm10k_mbx_error),
पूर्ण;

अटल पूर्णांक fm10k_mbx_request_irq_vf(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा msix_entry *entry = &पूर्णांकerface->msix_entries[FM10K_MBX_VECTOR];
	काष्ठा net_device *dev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक err;

	/* Use समयr0 क्रम पूर्णांकerrupt moderation on the mailbox */
	u32 itr = entry->entry | FM10K_INT_MAP_TIMER0;

	/* रेजिस्टर mailbox handlers */
	err = hw->mbx.ops.रेजिस्टर_handlers(&hw->mbx, vf_mbx_data);
	अगर (err)
		वापस err;

	/* request the IRQ */
	err = request_irq(entry->vector, fm10k_msix_mbx_vf, 0,
			  dev->name, पूर्णांकerface);
	अगर (err) अणु
		netअगर_err(पूर्णांकerface, probe, dev,
			  "request_irq for msix_mbx failed: %d\n", err);
		वापस err;
	पूर्ण

	/* map all of the पूर्णांकerrupt sources */
	fm10k_ग_लिखो_reg(hw, FM10K_VFINT_MAP, itr);

	/* enable पूर्णांकerrupt */
	fm10k_ग_लिखो_reg(hw, FM10K_VFITR(entry->entry), FM10K_ITR_ENABLE);

	वापस 0;
पूर्ण

अटल s32 fm10k_lport_map(काष्ठा fm10k_hw *hw, u32 **results,
			   काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	u32 dglort_map = hw->mac.dglort_map;
	s32 err;

	पूर्णांकerface = container_of(hw, काष्ठा fm10k_पूर्णांकfc, hw);

	err = fm10k_msg_err_pf(hw, results, mbx);
	अगर (!err && hw->swapi.status) अणु
		/* क्रमce link करोwn क्रम a reasonable delay */
		पूर्णांकerface->link_करोwn_event = jअगरfies + (2 * HZ);
		set_bit(__FM10K_LINK_DOWN, पूर्णांकerface->state);

		/* reset dglort_map back to no config */
		hw->mac.dglort_map = FM10K_DGLORTMAP_NONE;

		fm10k_service_event_schedule(पूर्णांकerface);

		/* prevent overloading kernel message buffer */
		अगर (पूर्णांकerface->lport_map_failed)
			वापस 0;

		पूर्णांकerface->lport_map_failed = true;

		अगर (hw->swapi.status == FM10K_MSG_ERR_PEP_NOT_SCHEDULED)
			dev_warn(&पूर्णांकerface->pdev->dev,
				 "cannot obtain link because the host interface is configured for a PCIe host interface bandwidth of zero\n");
		dev_warn(&पूर्णांकerface->pdev->dev,
			 "request logical port map failed: %d\n",
			 hw->swapi.status);

		वापस 0;
	पूर्ण

	err = fm10k_msg_lport_map_pf(hw, results, mbx);
	अगर (err)
		वापस err;

	पूर्णांकerface->lport_map_failed = false;

	/* we need to reset अगर port count was just updated */
	अगर (dglort_map != hw->mac.dglort_map)
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);

	वापस 0;
पूर्ण

अटल s32 fm10k_update_pvid(काष्ठा fm10k_hw *hw, u32 **results,
			     काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	u16 glort, pvid;
	u32 pvid_update;
	s32 err;

	err = fm10k_tlv_attr_get_u32(results[FM10K_PF_ATTR_ID_UPDATE_PVID],
				     &pvid_update);
	अगर (err)
		वापस err;

	/* extract values from the pvid update */
	glort = FM10K_MSG_HDR_FIELD_GET(pvid_update, UPDATE_PVID_GLORT);
	pvid = FM10K_MSG_HDR_FIELD_GET(pvid_update, UPDATE_PVID_PVID);

	/* अगर glort is not valid वापस error */
	अगर (!fm10k_glort_valid_pf(hw, glort))
		वापस FM10K_ERR_PARAM;

	/* verअगरy VLAN ID is valid */
	अगर (pvid >= FM10K_VLAN_TABLE_VID_MAX)
		वापस FM10K_ERR_PARAM;

	पूर्णांकerface = container_of(hw, काष्ठा fm10k_पूर्णांकfc, hw);

	/* check to see अगर this beदीर्घs to one of the VFs */
	err = fm10k_iov_update_pvid(पूर्णांकerface, glort, pvid);
	अगर (!err)
		वापस 0;

	/* we need to reset अगर शेष VLAN was just updated */
	अगर (pvid != hw->mac.शेष_vid)
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);

	hw->mac.शेष_vid = pvid;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fm10k_msg_data pf_mbx_data[] = अणु
	FM10K_PF_MSG_ERR_HANDLER(XCAST_MODES, fm10k_msg_err_pf),
	FM10K_PF_MSG_ERR_HANDLER(UPDATE_MAC_FWD_RULE, fm10k_msg_err_pf),
	FM10K_PF_MSG_LPORT_MAP_HANDLER(fm10k_lport_map),
	FM10K_PF_MSG_ERR_HANDLER(LPORT_CREATE, fm10k_msg_err_pf),
	FM10K_PF_MSG_ERR_HANDLER(LPORT_DELETE, fm10k_msg_err_pf),
	FM10K_PF_MSG_UPDATE_PVID_HANDLER(fm10k_update_pvid),
	FM10K_TLV_MSG_ERROR_HANDLER(fm10k_mbx_error),
पूर्ण;

अटल पूर्णांक fm10k_mbx_request_irq_pf(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा msix_entry *entry = &पूर्णांकerface->msix_entries[FM10K_MBX_VECTOR];
	काष्ठा net_device *dev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक err;

	/* Use समयr0 क्रम पूर्णांकerrupt moderation on the mailbox */
	u32 mbx_itr = entry->entry | FM10K_INT_MAP_TIMER0;
	u32 other_itr = entry->entry | FM10K_INT_MAP_IMMEDIATE;

	/* रेजिस्टर mailbox handlers */
	err = hw->mbx.ops.रेजिस्टर_handlers(&hw->mbx, pf_mbx_data);
	अगर (err)
		वापस err;

	/* request the IRQ */
	err = request_irq(entry->vector, fm10k_msix_mbx_pf, 0,
			  dev->name, पूर्णांकerface);
	अगर (err) अणु
		netअगर_err(पूर्णांकerface, probe, dev,
			  "request_irq for msix_mbx failed: %d\n", err);
		वापस err;
	पूर्ण

	/* Enable पूर्णांकerrupts w/ no moderation क्रम "other" पूर्णांकerrupts */
	fm10k_ग_लिखो_reg(hw, FM10K_INT_MAP(fm10k_पूर्णांक_pcie_fault), other_itr);
	fm10k_ग_लिखो_reg(hw, FM10K_INT_MAP(fm10k_पूर्णांक_चयन_up_करोwn), other_itr);
	fm10k_ग_लिखो_reg(hw, FM10K_INT_MAP(fm10k_पूर्णांक_sram), other_itr);
	fm10k_ग_लिखो_reg(hw, FM10K_INT_MAP(fm10k_पूर्णांक_max_hold_समय), other_itr);
	fm10k_ग_लिखो_reg(hw, FM10K_INT_MAP(fm10k_पूर्णांक_vflr), other_itr);

	/* Enable पूर्णांकerrupts w/ moderation क्रम mailbox */
	fm10k_ग_लिखो_reg(hw, FM10K_INT_MAP(fm10k_पूर्णांक_mailbox), mbx_itr);

	/* Enable inभागidual पूर्णांकerrupt causes */
	fm10k_ग_लिखो_reg(hw, FM10K_EIMR, FM10K_EIMR_ENABLE(PCA_FAULT) |
					FM10K_EIMR_ENABLE(FUM_FAULT) |
					FM10K_EIMR_ENABLE(MAILBOX) |
					FM10K_EIMR_ENABLE(SWITCHREADY) |
					FM10K_EIMR_ENABLE(SWITCHNOTREADY) |
					FM10K_EIMR_ENABLE(SRAMERROR) |
					FM10K_EIMR_ENABLE(VFLR) |
					FM10K_EIMR_ENABLE(MAXHOLDTIME));

	/* enable पूर्णांकerrupt */
	fm10k_ग_लिखो_reg(hw, FM10K_ITR(entry->entry), FM10K_ITR_ENABLE);

	वापस 0;
पूर्ण

पूर्णांक fm10k_mbx_request_irq(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक err;

	/* enable Mailbox cause */
	अगर (hw->mac.type == fm10k_mac_pf)
		err = fm10k_mbx_request_irq_pf(पूर्णांकerface);
	अन्यथा
		err = fm10k_mbx_request_irq_vf(पूर्णांकerface);
	अगर (err)
		वापस err;

	/* connect mailbox */
	err = hw->mbx.ops.connect(hw, &hw->mbx);

	/* अगर the mailbox failed to connect, then मुक्त IRQ */
	अगर (err)
		fm10k_mbx_मुक्त_irq(पूर्णांकerface);

	वापस err;
पूर्ण

/**
 * fm10k_qv_मुक्त_irq - release पूर्णांकerrupts associated with queue vectors
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Release all पूर्णांकerrupts associated with this पूर्णांकerface
 **/
व्योम fm10k_qv_मुक्त_irq(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक vector = पूर्णांकerface->num_q_vectors;
	काष्ठा msix_entry *entry;

	entry = &पूर्णांकerface->msix_entries[NON_Q_VECTORS + vector];

	जबतक (vector) अणु
		काष्ठा fm10k_q_vector *q_vector;

		vector--;
		entry--;
		q_vector = पूर्णांकerface->q_vector[vector];

		अगर (!q_vector->tx.count && !q_vector->rx.count)
			जारी;

		/* clear the affinity_mask in the IRQ descriptor */
		irq_set_affinity_hपूर्णांक(entry->vector, शून्य);

		/* disable पूर्णांकerrupts */
		ग_लिखोl(FM10K_ITR_MASK_SET, q_vector->itr);

		मुक्त_irq(entry->vector, q_vector);
	पूर्ण
पूर्ण

/**
 * fm10k_qv_request_irq - initialize पूर्णांकerrupts क्रम queue vectors
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Attempts to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 **/
पूर्णांक fm10k_qv_request_irq(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *dev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा msix_entry *entry;
	अचिन्हित पूर्णांक ri = 0, ti = 0;
	पूर्णांक vector, err;

	entry = &पूर्णांकerface->msix_entries[NON_Q_VECTORS];

	क्रम (vector = 0; vector < पूर्णांकerface->num_q_vectors; vector++) अणु
		काष्ठा fm10k_q_vector *q_vector = पूर्णांकerface->q_vector[vector];

		/* name the vector */
		अगर (q_vector->tx.count && q_vector->rx.count) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-TxRx-%u", dev->name, ri++);
			ti++;
		पूर्ण अन्यथा अगर (q_vector->rx.count) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-rx-%u", dev->name, ri++);
		पूर्ण अन्यथा अगर (q_vector->tx.count) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-tx-%u", dev->name, ti++);
		पूर्ण अन्यथा अणु
			/* skip this unused q_vector */
			जारी;
		पूर्ण

		/* Assign ITR रेजिस्टर to q_vector */
		q_vector->itr = (hw->mac.type == fm10k_mac_pf) ?
				&पूर्णांकerface->uc_addr[FM10K_ITR(entry->entry)] :
				&पूर्णांकerface->uc_addr[FM10K_VFITR(entry->entry)];

		/* request the IRQ */
		err = request_irq(entry->vector, &fm10k_msix_clean_rings, 0,
				  q_vector->name, q_vector);
		अगर (err) अणु
			netअगर_err(पूर्णांकerface, probe, dev,
				  "request_irq failed for MSIX interrupt Error: %d\n",
				  err);
			जाओ err_out;
		पूर्ण

		/* assign the mask क्रम this irq */
		irq_set_affinity_hपूर्णांक(entry->vector, &q_vector->affinity_mask);

		/* Enable q_vector */
		ग_लिखोl(FM10K_ITR_ENABLE, q_vector->itr);

		entry++;
	पूर्ण

	वापस 0;

err_out:
	/* wind through the ring मुक्तing all entries and vectors */
	जबतक (vector) अणु
		काष्ठा fm10k_q_vector *q_vector;

		entry--;
		vector--;
		q_vector = पूर्णांकerface->q_vector[vector];

		अगर (!q_vector->tx.count && !q_vector->rx.count)
			जारी;

		/* clear the affinity_mask in the IRQ descriptor */
		irq_set_affinity_hपूर्णांक(entry->vector, शून्य);

		/* disable पूर्णांकerrupts */
		ग_लिखोl(FM10K_ITR_MASK_SET, q_vector->itr);

		मुक्त_irq(entry->vector, q_vector);
	पूर्ण

	वापस err;
पूर्ण

व्योम fm10k_up(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	/* Enable Tx/Rx DMA */
	hw->mac.ops.start_hw(hw);

	/* configure Tx descriptor rings */
	fm10k_configure_tx(पूर्णांकerface);

	/* configure Rx descriptor rings */
	fm10k_configure_rx(पूर्णांकerface);

	/* configure पूर्णांकerrupts */
	hw->mac.ops.update_पूर्णांक_moderator(hw);

	/* enable statistics capture again */
	clear_bit(__FM10K_UPDATING_STATS, पूर्णांकerface->state);

	/* clear करोwn bit to indicate we are पढ़ोy to go */
	clear_bit(__FM10K_DOWN, पूर्णांकerface->state);

	/* enable polling cleanups */
	fm10k_napi_enable_all(पूर्णांकerface);

	/* re-establish Rx filters */
	fm10k_restore_rx_state(पूर्णांकerface);

	/* enable transmits */
	netअगर_tx_start_all_queues(पूर्णांकerface->netdev);

	/* kick off the service समयr now */
	hw->mac.get_host_state = true;
	mod_समयr(&पूर्णांकerface->service_समयr, jअगरfies);
पूर्ण

अटल व्योम fm10k_napi_disable_all(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_q_vector *q_vector;
	पूर्णांक q_idx;

	क्रम (q_idx = 0; q_idx < पूर्णांकerface->num_q_vectors; q_idx++) अणु
		q_vector = पूर्णांकerface->q_vector[q_idx];
		napi_disable(&q_vector->napi);
	पूर्ण
पूर्ण

व्योम fm10k_करोwn(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक err, i = 0, count = 0;

	/* संकेत that we are करोwn to the पूर्णांकerrupt handler and service task */
	अगर (test_and_set_bit(__FM10K_DOWN, पूर्णांकerface->state))
		वापस;

	/* call carrier off first to aव्योम false dev_watchकरोg समयouts */
	netअगर_carrier_off(netdev);

	/* disable transmits */
	netअगर_tx_stop_all_queues(netdev);
	netअगर_tx_disable(netdev);

	/* reset Rx filters */
	fm10k_reset_rx_state(पूर्णांकerface);

	/* disable polling routines */
	fm10k_napi_disable_all(पूर्णांकerface);

	/* capture stats one last समय beक्रमe stopping पूर्णांकerface */
	fm10k_update_stats(पूर्णांकerface);

	/* prevent updating statistics जबतक we're करोwn */
	जबतक (test_and_set_bit(__FM10K_UPDATING_STATS, पूर्णांकerface->state))
		usleep_range(1000, 2000);

	/* skip रुकोing क्रम TX DMA अगर we lost PCIe link */
	अगर (FM10K_REMOVED(hw->hw_addr))
		जाओ skip_tx_dma_drain;

	/* In some rare circumstances it can take a जबतक क्रम Tx queues to
	 * quiesce and be fully disabled. Attempt to .stop_hw() first, and
	 * then अगर we get ERR_REQUESTS_PENDING, go ahead and रुको in a loop
	 * until the Tx queues have emptied, or until a number of retries. If
	 * we fail to clear within the retry loop, we will issue a warning
	 * indicating that Tx DMA is probably hung. Note this means we call
	 * .stop_hw() twice but this shouldn't cause any problems.
	 */
	err = hw->mac.ops.stop_hw(hw);
	अगर (err != FM10K_ERR_REQUESTS_PENDING)
		जाओ skip_tx_dma_drain;

#घोषणा TX_DMA_DRAIN_RETRIES 25
	क्रम (count = 0; count < TX_DMA_DRAIN_RETRIES; count++) अणु
		usleep_range(10000, 20000);

		/* start checking at the last ring to have pending Tx */
		क्रम (; i < पूर्णांकerface->num_tx_queues; i++)
			अगर (fm10k_get_tx_pending(पूर्णांकerface->tx_ring[i], false))
				अवरोध;

		/* अगर all the queues are drained, we can अवरोध now */
		अगर (i == पूर्णांकerface->num_tx_queues)
			अवरोध;
	पूर्ण

	अगर (count >= TX_DMA_DRAIN_RETRIES)
		dev_err(&पूर्णांकerface->pdev->dev,
			"Tx queues failed to drain after %d tries. Tx DMA is probably hung.\n",
			count);
skip_tx_dma_drain:
	/* Disable DMA engine क्रम Tx/Rx */
	err = hw->mac.ops.stop_hw(hw);
	अगर (err == FM10K_ERR_REQUESTS_PENDING)
		dev_err(&पूर्णांकerface->pdev->dev,
			"due to pending requests hw was not shut down gracefully\n");
	अन्यथा अगर (err)
		dev_err(&पूर्णांकerface->pdev->dev, "stop_hw failed: %d\n", err);

	/* मुक्त any buffers still on the rings */
	fm10k_clean_all_tx_rings(पूर्णांकerface);
	fm10k_clean_all_rx_rings(पूर्णांकerface);
पूर्ण

/**
 * fm10k_sw_init - Initialize general software काष्ठाures
 * @पूर्णांकerface: host पूर्णांकerface निजी काष्ठाure to initialize
 * @ent: PCI device ID entry
 *
 * fm10k_sw_init initializes the पूर्णांकerface निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 **/
अटल पूर्णांक fm10k_sw_init(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
			 स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा fm10k_info *fi = fm10k_info_tbl[ent->driver_data];
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा pci_dev *pdev = पूर्णांकerface->pdev;
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	u32 rss_key[FM10K_RSSRK_SIZE];
	अचिन्हित पूर्णांक rss;
	पूर्णांक err;

	/* initialize back poपूर्णांकer */
	hw->back = पूर्णांकerface;
	hw->hw_addr = पूर्णांकerface->uc_addr;

	/* PCI config space info */
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->revision_id = pdev->revision;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;

	/* Setup hw api */
	स_नकल(&hw->mac.ops, fi->mac_ops, माप(hw->mac.ops));
	hw->mac.type = fi->mac;

	/* Setup IOV handlers */
	अगर (fi->iov_ops)
		स_नकल(&hw->iov.ops, fi->iov_ops, माप(hw->iov.ops));

	/* Set common capability flags and settings */
	rss = min_t(पूर्णांक, FM10K_MAX_RSS_INDICES, num_online_cpus());
	पूर्णांकerface->ring_feature[RING_F_RSS].limit = rss;
	fi->get_invariants(hw);

	/* pick up the PCIe bus settings क्रम reporting later */
	अगर (hw->mac.ops.get_bus_info)
		hw->mac.ops.get_bus_info(hw);

	/* limit the usable DMA range */
	अगर (hw->mac.ops.set_dma_mask)
		hw->mac.ops.set_dma_mask(hw, dma_get_mask(&pdev->dev));

	/* update netdev with DMA restrictions */
	अगर (dma_get_mask(&pdev->dev) > DMA_BIT_MASK(32)) अणु
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	पूर्ण

	/* reset and initialize the hardware so it is in a known state */
	err = hw->mac.ops.reset_hw(hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "reset_hw failed: %d\n", err);
		वापस err;
	पूर्ण

	err = hw->mac.ops.init_hw(hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "init_hw failed: %d\n", err);
		वापस err;
	पूर्ण

	/* initialize hardware statistics */
	hw->mac.ops.update_hw_stats(hw, &पूर्णांकerface->stats);

	/* Set upper limit on IOV VFs that can be allocated */
	pci_sriov_set_totalvfs(pdev, hw->iov.total_vfs);

	/* Start with अक्रमom Ethernet address */
	eth_अक्रमom_addr(hw->mac.addr);

	/* Initialize MAC address from hardware */
	err = hw->mac.ops.पढ़ो_mac_addr(hw);
	अगर (err) अणु
		dev_warn(&pdev->dev,
			 "Failed to obtain MAC address defaulting to random\n");
		/* tag address assignment as अक्रमom */
		netdev->addr_assign_type |= NET_ADDR_RANDOM;
	पूर्ण

	ether_addr_copy(netdev->dev_addr, hw->mac.addr);
	ether_addr_copy(netdev->perm_addr, hw->mac.addr);

	अगर (!is_valid_ether_addr(netdev->perm_addr)) अणु
		dev_err(&pdev->dev, "Invalid MAC Address\n");
		वापस -EIO;
	पूर्ण

	/* initialize DCBNL पूर्णांकerface */
	fm10k_dcbnl_set_ops(netdev);

	/* set शेष ring sizes */
	पूर्णांकerface->tx_ring_count = FM10K_DEFAULT_TXD;
	पूर्णांकerface->rx_ring_count = FM10K_DEFAULT_RXD;

	/* set शेष पूर्णांकerrupt moderation */
	पूर्णांकerface->tx_itr = FM10K_TX_ITR_DEFAULT;
	पूर्णांकerface->rx_itr = FM10K_ITR_ADAPTIVE | FM10K_RX_ITR_DEFAULT;

	/* Initialize the MAC/VLAN queue */
	INIT_LIST_HEAD(&पूर्णांकerface->macvlan_requests);

	netdev_rss_key_fill(rss_key, माप(rss_key));
	स_नकल(पूर्णांकerface->rssrk, rss_key, माप(rss_key));

	/* Initialize the mailbox lock */
	spin_lock_init(&पूर्णांकerface->mbx_lock);
	spin_lock_init(&पूर्णांकerface->macvlan_lock);

	/* Start off पूर्णांकerface as being करोwn */
	set_bit(__FM10K_DOWN, पूर्णांकerface->state);
	set_bit(__FM10K_UPDATING_STATS, पूर्णांकerface->state);

	वापस 0;
पूर्ण

/**
 * fm10k_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in fm10k_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * fm10k_probe initializes an पूर्णांकerface identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the पूर्णांकerface निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक fm10k_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	पूर्णांक err;

	अगर (pdev->error_state != pci_channel_io_normal) अणु
		dev_err(&pdev->dev,
			"PCI device still in an error state. Unable to load...\n");
		वापस -EIO;
	पूर्ण

	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"PCI enable device failed: %d\n", err);
		वापस err;
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	अगर (err)
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev,
			"DMA configuration failed: %d\n", err);
		जाओ err_dma;
	पूर्ण

	err = pci_request_mem_regions(pdev, fm10k_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"pci_request_selected_regions failed: %d\n", err);
		जाओ err_pci_reg;
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);
	pci_save_state(pdev);

	netdev = fm10k_alloc_netdev(fm10k_info_tbl[ent->driver_data]);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_netdev;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	पूर्णांकerface = netdev_priv(netdev);
	pci_set_drvdata(pdev, पूर्णांकerface);

	पूर्णांकerface->netdev = netdev;
	पूर्णांकerface->pdev = pdev;

	पूर्णांकerface->uc_addr = ioremap(pci_resource_start(pdev, 0),
				     FM10K_UC_ADDR_SIZE);
	अगर (!पूर्णांकerface->uc_addr) अणु
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	err = fm10k_sw_init(पूर्णांकerface, ent);
	अगर (err)
		जाओ err_sw_init;

	/* enable debugfs support */
	fm10k_dbg_पूर्णांकfc_init(पूर्णांकerface);

	err = fm10k_init_queueing_scheme(पूर्णांकerface);
	अगर (err)
		जाओ err_sw_init;

	/* the mbx पूर्णांकerrupt might attempt to schedule the service task, so we
	 * must ensure it is disabled since we haven't yet requested the समयr
	 * or work item.
	 */
	set_bit(__FM10K_SERVICE_DISABLE, पूर्णांकerface->state);

	err = fm10k_mbx_request_irq(पूर्णांकerface);
	अगर (err)
		जाओ err_mbx_पूर्णांकerrupt;

	/* final check of hardware state beक्रमe रेजिस्टरing the पूर्णांकerface */
	err = fm10k_hw_पढ़ोy(पूर्णांकerface);
	अगर (err)
		जाओ err_रेजिस्टर;

	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	/* stop all the transmit queues from transmitting until link is up */
	netअगर_tx_stop_all_queues(netdev);

	/* Initialize service समयr and service task late in order to aव्योम
	 * cleanup issues.
	 */
	समयr_setup(&पूर्णांकerface->service_समयr, fm10k_service_समयr, 0);
	INIT_WORK(&पूर्णांकerface->service_task, fm10k_service_task);

	/* Setup the MAC/VLAN queue */
	INIT_DELAYED_WORK(&पूर्णांकerface->macvlan_task, fm10k_macvlan_task);

	/* kick off service समयr now, even when पूर्णांकerface is करोwn */
	mod_समयr(&पूर्णांकerface->service_समयr, (HZ * 2) + jअगरfies);

	/* prपूर्णांक warning क्रम non-optimal configurations */
	pcie_prपूर्णांक_link_status(पूर्णांकerface->pdev);

	/* report MAC address क्रम logging */
	dev_info(&pdev->dev, "%pM\n", netdev->dev_addr);

	/* enable SR-IOV after रेजिस्टरing netdev to enक्रमce PF/VF ordering */
	fm10k_iov_configure(pdev, 0);

	/* clear the service task disable bit and kick off service task */
	clear_bit(__FM10K_SERVICE_DISABLE, पूर्णांकerface->state);
	fm10k_service_event_schedule(पूर्णांकerface);

	वापस 0;

err_रेजिस्टर:
	fm10k_mbx_मुक्त_irq(पूर्णांकerface);
err_mbx_पूर्णांकerrupt:
	fm10k_clear_queueing_scheme(पूर्णांकerface);
err_sw_init:
	अगर (पूर्णांकerface->sw_addr)
		iounmap(पूर्णांकerface->sw_addr);
	iounmap(पूर्णांकerface->uc_addr);
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_netdev:
	pci_release_mem_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * fm10k_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * fm10k_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम fm10k_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;

	del_समयr_sync(&पूर्णांकerface->service_समयr);

	fm10k_stop_service_event(पूर्णांकerface);
	fm10k_stop_macvlan_task(पूर्णांकerface);

	/* Remove all pending MAC/VLAN requests */
	fm10k_clear_macvlan_queue(पूर्णांकerface, पूर्णांकerface->glort, true);

	/* मुक्त netdev, this may bounce the पूर्णांकerrupts due to setup_tc */
	अगर (netdev->reg_state == NETREG_REGISTERED)
		unरेजिस्टर_netdev(netdev);

	/* release VFs */
	fm10k_iov_disable(pdev);

	/* disable mailbox पूर्णांकerrupt */
	fm10k_mbx_मुक्त_irq(पूर्णांकerface);

	/* मुक्त पूर्णांकerrupts */
	fm10k_clear_queueing_scheme(पूर्णांकerface);

	/* हटाओ any debugfs पूर्णांकerfaces */
	fm10k_dbg_पूर्णांकfc_निकास(पूर्णांकerface);

	अगर (पूर्णांकerface->sw_addr)
		iounmap(पूर्णांकerface->sw_addr);
	iounmap(पूर्णांकerface->uc_addr);

	मुक्त_netdev(netdev);

	pci_release_mem_regions(pdev);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
पूर्ण

अटल व्योम fm10k_prepare_suspend(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* the watchकरोg task पढ़ोs from रेजिस्टरs, which might appear like
	 * a surprise हटाओ अगर the PCIe device is disabled जबतक we're
	 * stopped. We stop the watchकरोg task until after we resume software
	 * activity.
	 *
	 * Note that the MAC/VLAN task will be stopped as part of preparing
	 * क्रम reset so we करोn't need to handle it here.
	 */
	fm10k_stop_service_event(पूर्णांकerface);

	अगर (fm10k_prepare_क्रम_reset(पूर्णांकerface))
		set_bit(__FM10K_RESET_SUSPENDED, पूर्णांकerface->state);
पूर्ण

अटल पूर्णांक fm10k_handle_resume(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक err;

	/* Even अगर we didn't properly prepare क्रम reset in
	 * fm10k_prepare_suspend, we'll attempt to resume anyways.
	 */
	अगर (!test_and_clear_bit(__FM10K_RESET_SUSPENDED, पूर्णांकerface->state))
		dev_warn(&पूर्णांकerface->pdev->dev,
			 "Device was shut down as part of suspend... Attempting to recover\n");

	/* reset statistics starting values */
	hw->mac.ops.rebind_hw_stats(hw, &पूर्णांकerface->stats);

	err = fm10k_handle_reset(पूर्णांकerface);
	अगर (err)
		वापस err;

	/* assume host is not पढ़ोy, to prevent race with watchकरोg in हाल we
	 * actually करोn't have connection to the चयन
	 */
	पूर्णांकerface->host_पढ़ोy = false;
	fm10k_watchकरोg_host_not_पढ़ोy(पूर्णांकerface);

	/* क्रमce link to stay करोwn क्रम a second to prevent link flutter */
	पूर्णांकerface->link_करोwn_event = jअगरfies + (HZ);
	set_bit(__FM10K_LINK_DOWN, पूर्णांकerface->state);

	/* restart the service task */
	fm10k_start_service_event(पूर्णांकerface);

	/* Restart the MAC/VLAN request queue in-हाल of outstanding events */
	fm10k_macvlan_schedule(पूर्णांकerface);

	वापस 0;
पूर्ण

/**
 * fm10k_resume - Generic PM resume hook
 * @dev: generic device काष्ठाure
 *
 * Generic PM hook used when waking the device from a low घातer state after
 * suspend or hibernation. This function करोes not need to handle lower PCIe
 * device state as the stack takes care of that क्रम us.
 **/
अटल पूर्णांक __maybe_unused fm10k_resume(काष्ठा device *dev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक err;

	/* refresh hw_addr in हाल it was dropped */
	hw->hw_addr = पूर्णांकerface->uc_addr;

	err = fm10k_handle_resume(पूर्णांकerface);
	अगर (err)
		वापस err;

	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण

/**
 * fm10k_suspend - Generic PM suspend hook
 * @dev: generic device काष्ठाure
 *
 * Generic PM hook used when setting the device पूर्णांकo a low घातer state क्रम
 * प्रणाली suspend or hibernation. This function करोes not need to handle lower
 * PCIe device state as the stack takes care of that क्रम us.
 **/
अटल पूर्णांक __maybe_unused fm10k_suspend(काष्ठा device *dev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;

	netअगर_device_detach(netdev);

	fm10k_prepare_suspend(पूर्णांकerface);

	वापस 0;
पूर्ण

/**
 * fm10k_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t fm10k_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	fm10k_prepare_suspend(पूर्णांकerface);

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * fm10k_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 */
अटल pci_ers_result_t fm10k_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	pci_ers_result_t result;

	अगर (pci_reenable_device(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		pci_restore_state(pdev);

		/* After second error pci->state_saved is false, this
		 * resets it so EEH करोesn't अवरोध.
		 */
		pci_save_state(pdev);

		pci_wake_from_d3(pdev, false);

		result = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	वापस result;
पूर्ण

/**
 * fm10k_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation.
 */
अटल व्योम fm10k_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	पूर्णांक err;

	err = fm10k_handle_resume(पूर्णांकerface);

	अगर (err)
		dev_warn(&pdev->dev,
			 "%s failed: %d\n", __func__, err);
	अन्यथा
		netअगर_device_attach(netdev);
पूर्ण

/**
 * fm10k_io_reset_prepare - called when PCI function is about to be reset
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the PCI function is about to be reset,
 * allowing the device driver to prepare क्रम it.
 */
अटल व्योम fm10k_io_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	/* warn inहाल we have any active VF devices */
	अगर (pci_num_vf(pdev))
		dev_warn(&pdev->dev,
			 "PCIe FLR may cause issues for any active VF devices\n");
	fm10k_prepare_suspend(pci_get_drvdata(pdev));
पूर्ण

/**
 * fm10k_io_reset_करोne - called when PCI function has finished resetting
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called just after the PCI function is reset, such as via
 * /sys/class/net/<enpX>/device/reset or similar.
 */
अटल व्योम fm10k_io_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = pci_get_drvdata(pdev);
	पूर्णांक err = fm10k_handle_resume(पूर्णांकerface);

	अगर (err) अणु
		dev_warn(&pdev->dev,
			 "%s failed: %d\n", __func__, err);
		netअगर_device_detach(पूर्णांकerface->netdev);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers fm10k_err_handler = अणु
	.error_detected = fm10k_io_error_detected,
	.slot_reset = fm10k_io_slot_reset,
	.resume = fm10k_io_resume,
	.reset_prepare = fm10k_io_reset_prepare,
	.reset_करोne = fm10k_io_reset_करोne,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(fm10k_pm_ops, fm10k_suspend, fm10k_resume);

अटल काष्ठा pci_driver fm10k_driver = अणु
	.name			= fm10k_driver_name,
	.id_table		= fm10k_pci_tbl,
	.probe			= fm10k_probe,
	.हटाओ			= fm10k_हटाओ,
	.driver = अणु
		.pm		= &fm10k_pm_ops,
	पूर्ण,
	.sriov_configure	= fm10k_iov_configure,
	.err_handler		= &fm10k_err_handler
पूर्ण;

/**
 * fm10k_रेजिस्टर_pci_driver - रेजिस्टर driver पूर्णांकerface
 *
 * This function is called on module load in order to रेजिस्टर the driver.
 **/
पूर्णांक fm10k_रेजिस्टर_pci_driver(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&fm10k_driver);
पूर्ण

/**
 * fm10k_unरेजिस्टर_pci_driver - unरेजिस्टर driver पूर्णांकerface
 *
 * This function is called on module unload in order to हटाओ the driver.
 **/
व्योम fm10k_unरेजिस्टर_pci_driver(व्योम)
अणु
	pci_unरेजिस्टर_driver(&fm10k_driver);
पूर्ण
