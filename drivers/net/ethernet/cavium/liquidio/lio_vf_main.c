<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <net/vxlan.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_nic.h"
#समावेश "octeon_main.h"
#समावेश "octeon_network.h"
#समावेश "cn23xx_vf_device.h"

MODULE_AUTHOR("Cavium Networks, <support@cavium.com>");
MODULE_DESCRIPTION("Cavium LiquidIO Intelligent Server Adapter Virtual Function Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "NETIF_MSG debug bits");

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)

काष्ठा oct_बारtamp_resp अणु
	u64 rh;
	u64 बारtamp;
	u64 status;
पूर्ण;

जोड़ tx_info अणु
	u64 u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u16 gso_size;
		u16 gso_segs;
		u32 reserved;
#अन्यथा
		u32 reserved;
		u16 gso_segs;
		u16 gso_size;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा OCTNIC_GSO_MAX_HEADER_SIZE 128
#घोषणा OCTNIC_GSO_MAX_SIZE \
		(CN23XX_DEFAULT_INPUT_JABBER - OCTNIC_GSO_MAX_HEADER_SIZE)

अटल पूर्णांक
liquidio_vf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम liquidio_vf_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक octeon_device_init(काष्ठा octeon_device *oct);
अटल पूर्णांक liquidio_stop(काष्ठा net_device *netdev);

अटल पूर्णांक lio_रुको_क्रम_oq_pkts(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_device_priv *oct_priv =
	    (काष्ठा octeon_device_priv *)oct->priv;
	पूर्णांक retry = MAX_IO_PENDING_PKT_COUNT;
	पूर्णांक pkt_cnt = 0, pending_pkts;
	पूर्णांक i;

	करो अणु
		pending_pkts = 0;

		क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) अणु
			अगर (!(oct->io_qmask.oq & BIT_ULL(i)))
				जारी;
			pkt_cnt += octeon_droq_check_hw_क्रम_pkts(oct->droq[i]);
		पूर्ण
		अगर (pkt_cnt > 0) अणु
			pending_pkts += pkt_cnt;
			tasklet_schedule(&oct_priv->droq_tasklet);
		पूर्ण
		pkt_cnt = 0;
		schedule_समयout_unपूर्णांकerruptible(1);

	पूर्ण जबतक (retry-- && pending_pkts);

	वापस pkt_cnt;
पूर्ण

/**
 * pcierror_quiesce_device - Cause device to go quiet so it can be safely हटाओd/reset/etc
 * @oct: Poपूर्णांकer to Octeon device
 */
अटल व्योम pcierror_quiesce_device(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i;

	/* Disable the input and output queues now. No more packets will
	 * arrive from Octeon, but we should रुको क्रम all packet processing
	 * to finish.
	 */

	/* To allow क्रम in-flight requests */
	schedule_समयout_unपूर्णांकerruptible(100);

	अगर (रुको_क्रम_pending_requests(oct))
		dev_err(&oct->pci_dev->dev, "There were pending requests\n");

	/* Force all requests रुकोing to be fetched by OCTEON to complete. */
	क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) अणु
		काष्ठा octeon_instr_queue *iq;

		अगर (!(oct->io_qmask.iq & BIT_ULL(i)))
			जारी;
		iq = oct->instr_queue[i];

		अगर (atomic_पढ़ो(&iq->instr_pending)) अणु
			spin_lock_bh(&iq->lock);
			iq->fill_cnt = 0;
			iq->octeon_पढ़ो_index = iq->host_ग_लिखो_index;
			iq->stats.instr_processed +=
			    atomic_पढ़ो(&iq->instr_pending);
			lio_process_iq_request_list(oct, iq, 0);
			spin_unlock_bh(&iq->lock);
		पूर्ण
	पूर्ण

	/* Force all pending ordered list requests to समय out. */
	lio_process_ordered_list(oct, 1);

	/* We करो not need to रुको क्रम output queue packets to be processed. */
पूर्ण

/**
 * cleanup_aer_uncorrect_error_status - Cleanup PCI AER uncorrectable error status
 * @dev: Poपूर्णांकer to PCI device
 */
अटल व्योम cleanup_aer_uncorrect_error_status(काष्ठा pci_dev *dev)
अणु
	u32 status, mask;
	पूर्णांक pos = 0x100;

	pr_info("%s :\n", __func__);

	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, &status);
	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, &mask);
	अगर (dev->error_state == pci_channel_io_normal)
		status &= ~mask; /* Clear corresponding nonfatal bits */
	अन्यथा
		status &= mask; /* Clear corresponding fatal bits */
	pci_ग_लिखो_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, status);
पूर्ण

/**
 * stop_pci_io - Stop all PCI IO to a given device
 * @oct: Poपूर्णांकer to Octeon device
 */
अटल व्योम stop_pci_io(काष्ठा octeon_device *oct)
अणु
	काष्ठा msix_entry *msix_entries;
	पूर्णांक i;

	/* No more inकाष्ठाions will be क्रमwarded. */
	atomic_set(&oct->status, OCT_DEV_IN_RESET);

	क्रम (i = 0; i < oct->अगरcount; i++)
		netअगर_device_detach(oct->props[i].netdev);

	/* Disable पूर्णांकerrupts  */
	oct->fn_list.disable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

	pcierror_quiesce_device(oct);
	अगर (oct->msix_on) अणु
		msix_entries = (काष्ठा msix_entry *)oct->msix_entries;
		क्रम (i = 0; i < oct->num_msix_irqs; i++) अणु
			/* clear the affinity_cpumask */
			irq_set_affinity_hपूर्णांक(msix_entries[i].vector,
					      शून्य);
			मुक्त_irq(msix_entries[i].vector,
				 &oct->ioq_vector[i]);
		पूर्ण
		pci_disable_msix(oct->pci_dev);
		kमुक्त(oct->msix_entries);
		oct->msix_entries = शून्य;
		octeon_मुक्त_ioq_vector(oct);
	पूर्ण
	dev_dbg(&oct->pci_dev->dev, "Device state is now %s\n",
		lio_get_state_string(&oct->status));

	/* making it a common function क्रम all OCTEON models */
	cleanup_aer_uncorrect_error_status(oct->pci_dev);

	pci_disable_device(oct->pci_dev);
पूर्ण

/**
 * liquidio_pcie_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t liquidio_pcie_error_detected(काष्ठा pci_dev *pdev,
						     pci_channel_state_t state)
अणु
	काष्ठा octeon_device *oct = pci_get_drvdata(pdev);

	/* Non-correctable Non-fatal errors */
	अगर (state == pci_channel_io_normal) अणु
		dev_err(&oct->pci_dev->dev, "Non-correctable non-fatal error reported:\n");
		cleanup_aer_uncorrect_error_status(oct->pci_dev);
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	पूर्ण

	/* Non-correctable Fatal errors */
	dev_err(&oct->pci_dev->dev, "Non-correctable FATAL reported by PCI AER driver\n");
	stop_pci_io(oct);

	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

/* For PCI-E Advanced Error Recovery (AER) Interface */
अटल स्थिर काष्ठा pci_error_handlers liquidio_vf_err_handler = अणु
	.error_detected = liquidio_pcie_error_detected,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id liquidio_vf_pci_tbl[] = अणु
	अणु
		PCI_VENDOR_ID_CAVIUM, OCTEON_CN23XX_VF_VID,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0
	पूर्ण,
	अणु
		0, 0, 0, 0, 0, 0, 0
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, liquidio_vf_pci_tbl);

अटल काष्ठा pci_driver liquidio_vf_pci_driver = अणु
	.name		= "LiquidIO_VF",
	.id_table	= liquidio_vf_pci_tbl,
	.probe		= liquidio_vf_probe,
	.हटाओ		= liquidio_vf_हटाओ,
	.err_handler	= &liquidio_vf_err_handler,    /* For AER */
पूर्ण;

/**
 * prपूर्णांक_link_info - Prपूर्णांक link inक्रमmation
 * @netdev: network device
 */
अटल व्योम prपूर्णांक_link_info(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	अगर (!अगरstate_check(lio, LIO_IFSTATE_RESETTING) &&
	    अगरstate_check(lio, LIO_IFSTATE_REGISTERED)) अणु
		काष्ठा oct_link_info *linfo = &lio->linfo;

		अगर (linfo->link.s.link_up) अणु
			netअगर_info(lio, link, lio->netdev, "%d Mbps %s Duplex UP\n",
				   linfo->link.s.speed,
				   (linfo->link.s.duplex) ? "Full" : "Half");
		पूर्ण अन्यथा अणु
			netअगर_info(lio, link, lio->netdev, "Link Down\n");
		पूर्ण
	पूर्ण
पूर्ण

/**
 * octnet_link_status_change - Routine to notअगरy MTU change
 * @work: work_काष्ठा data काष्ठाure
 */
अटल व्योम octnet_link_status_change(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा lio *lio = (काष्ठा lio *)wk->ctxptr;

	/* lio->linfo.link.s.mtu always contains max MTU of the lio पूर्णांकerface.
	 * this API is invoked only when new max-MTU of the पूर्णांकerface is
	 * less than current MTU.
	 */
	rtnl_lock();
	dev_set_mtu(lio->netdev, lio->linfo.link.s.mtu);
	rtnl_unlock();
पूर्ण

/**
 * setup_link_status_change_wq - Sets up the mtu status change work
 * @netdev: network device
 */
अटल पूर्णांक setup_link_status_change_wq(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	lio->link_status_wq.wq = alloc_workqueue("link-status",
						 WQ_MEM_RECLAIM, 0);
	अगर (!lio->link_status_wq.wq) अणु
		dev_err(&oct->pci_dev->dev, "unable to create cavium link status wq\n");
		वापस -1;
	पूर्ण
	INIT_DELAYED_WORK(&lio->link_status_wq.wk.work,
			  octnet_link_status_change);
	lio->link_status_wq.wk.ctxptr = lio;

	वापस 0;
पूर्ण

अटल व्योम cleanup_link_status_change_wq(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	अगर (lio->link_status_wq.wq) अणु
		cancel_delayed_work_sync(&lio->link_status_wq.wk.work);
		destroy_workqueue(lio->link_status_wq.wq);
	पूर्ण
पूर्ण

/**
 * update_link_status - Update link status
 * @netdev: network device
 * @ls: link status काष्ठाure
 *
 * Called on receipt of a link status response from the core application to
 * update each पूर्णांकerface's link status.
 */
अटल व्योम update_link_status(काष्ठा net_device *netdev,
			       जोड़ oct_link_status *ls)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	पूर्णांक current_max_mtu = lio->linfo.link.s.mtu;
	काष्ठा octeon_device *oct = lio->oct_dev;

	अगर ((lio->पूर्णांकf_खोलो) && (lio->linfo.link.u64 != ls->u64)) अणु
		lio->linfo.link.u64 = ls->u64;

		prपूर्णांक_link_info(netdev);
		lio->link_changes++;

		अगर (lio->linfo.link.s.link_up) अणु
			netअगर_carrier_on(netdev);
			wake_txqs(netdev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(netdev);
			stop_txqs(netdev);
		पूर्ण

		अगर (lio->linfo.link.s.mtu != current_max_mtu) अणु
			dev_info(&oct->pci_dev->dev,
				 "Max MTU Changed from %d to %d\n",
				 current_max_mtu, lio->linfo.link.s.mtu);
			netdev->max_mtu = lio->linfo.link.s.mtu;
		पूर्ण

		अगर (lio->linfo.link.s.mtu < netdev->mtu) अणु
			dev_warn(&oct->pci_dev->dev,
				 "Current MTU is higher than new max MTU; Reducing the current mtu from %d to %d\n",
				 netdev->mtu, lio->linfo.link.s.mtu);
			queue_delayed_work(lio->link_status_wq.wq,
					   &lio->link_status_wq.wk.work, 0);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * liquidio_vf_probe - PCI probe handler
 * @pdev: PCI device काष्ठाure
 * @ent: unused
 */
अटल पूर्णांक
liquidio_vf_probe(काष्ठा pci_dev *pdev,
		  स्थिर काष्ठा pci_device_id __maybe_unused *ent)
अणु
	काष्ठा octeon_device *oct_dev = शून्य;

	oct_dev = octeon_allocate_device(pdev->device,
					 माप(काष्ठा octeon_device_priv));

	अगर (!oct_dev) अणु
		dev_err(&pdev->dev, "Unable to allocate device\n");
		वापस -ENOMEM;
	पूर्ण
	oct_dev->msix_on = LIO_FLAG_MSIX_ENABLED;

	dev_info(&pdev->dev, "Initializing device %x:%x.\n",
		 (u32)pdev->venकरोr, (u32)pdev->device);

	/* Assign octeon_device क्रम this device to the निजी data area. */
	pci_set_drvdata(pdev, oct_dev);

	/* set linux specअगरic device poपूर्णांकer */
	oct_dev->pci_dev = pdev;

	oct_dev->subप्रणाली_id = pdev->subप्रणाली_venकरोr |
		(pdev->subप्रणाली_device << 16);

	अगर (octeon_device_init(oct_dev)) अणु
		liquidio_vf_हटाओ(pdev);
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(&oct_dev->pci_dev->dev, "Device is ready\n");

	वापस 0;
पूर्ण

/**
 * octeon_pci_flr - PCI FLR क्रम each Octeon device.
 * @oct: octeon device
 */
अटल व्योम octeon_pci_flr(काष्ठा octeon_device *oct)
अणु
	pci_save_state(oct->pci_dev);

	pci_cfg_access_lock(oct->pci_dev);

	/* Quiesce the device completely */
	pci_ग_लिखो_config_word(oct->pci_dev, PCI_COMMAND,
			      PCI_COMMAND_INTX_DISABLE);

	pcie_flr(oct->pci_dev);

	pci_cfg_access_unlock(oct->pci_dev);

	pci_restore_state(oct->pci_dev);
पूर्ण

/**
 * octeon_destroy_resources - Destroy resources associated with octeon device
 * @oct: octeon device
 */
अटल व्योम octeon_destroy_resources(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)oct->priv;
	काष्ठा msix_entry *msix_entries;
	पूर्णांक i;

	चयन (atomic_पढ़ो(&oct->status)) अणु
	हाल OCT_DEV_RUNNING:
	हाल OCT_DEV_CORE_OK:
		/* No more inकाष्ठाions will be क्रमwarded. */
		atomic_set(&oct->status, OCT_DEV_IN_RESET);

		oct->app_mode = CVM_DRV_INVALID_APP;
		dev_dbg(&oct->pci_dev->dev, "Device state is now %s\n",
			lio_get_state_string(&oct->status));

		schedule_समयout_unपूर्णांकerruptible(HZ / 10);

		fallthrough;
	हाल OCT_DEV_HOST_OK:
	हाल OCT_DEV_IO_QUEUES_DONE:
		अगर (lio_रुको_क्रम_instr_fetch(oct))
			dev_err(&oct->pci_dev->dev, "IQ had pending instructions\n");

		अगर (रुको_क्रम_pending_requests(oct))
			dev_err(&oct->pci_dev->dev, "There were pending requests\n");

		/* Disable the input and output queues now. No more packets will
		 * arrive from Octeon, but we should रुको क्रम all packet
		 * processing to finish.
		 */
		oct->fn_list.disable_io_queues(oct);

		अगर (lio_रुको_क्रम_oq_pkts(oct))
			dev_err(&oct->pci_dev->dev, "OQ had pending packets\n");

		/* Force all requests रुकोing to be fetched by OCTEON to
		 * complete.
		 */
		क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) अणु
			काष्ठा octeon_instr_queue *iq;

			अगर (!(oct->io_qmask.iq & BIT_ULL(i)))
				जारी;
			iq = oct->instr_queue[i];

			अगर (atomic_पढ़ो(&iq->instr_pending)) अणु
				spin_lock_bh(&iq->lock);
				iq->fill_cnt = 0;
				iq->octeon_पढ़ो_index = iq->host_ग_लिखो_index;
				iq->stats.instr_processed +=
					atomic_पढ़ो(&iq->instr_pending);
				lio_process_iq_request_list(oct, iq, 0);
				spin_unlock_bh(&iq->lock);
			पूर्ण
		पूर्ण

		lio_process_ordered_list(oct, 1);
		octeon_मुक्त_sc_करोne_list(oct);
		octeon_मुक्त_sc_zombie_list(oct);

		fallthrough;
	हाल OCT_DEV_INTR_SET_DONE:
		/* Disable पूर्णांकerrupts  */
		oct->fn_list.disable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

		अगर (oct->msix_on) अणु
			msix_entries = (काष्ठा msix_entry *)oct->msix_entries;
			क्रम (i = 0; i < oct->num_msix_irqs; i++) अणु
				अगर (oct->ioq_vector[i].vector) अणु
					irq_set_affinity_hपूर्णांक(
							msix_entries[i].vector,
							शून्य);
					मुक्त_irq(msix_entries[i].vector,
						 &oct->ioq_vector[i]);
					oct->ioq_vector[i].vector = 0;
				पूर्ण
			पूर्ण
			pci_disable_msix(oct->pci_dev);
			kमुक्त(oct->msix_entries);
			oct->msix_entries = शून्य;
			kमुक्त(oct->irq_name_storage);
			oct->irq_name_storage = शून्य;
		पूर्ण
		/* Soft reset the octeon device beक्रमe निकासing */
		अगर (oct->pci_dev->reset_fn)
			octeon_pci_flr(oct);
		अन्यथा
			cn23xx_vf_ask_pf_to_करो_flr(oct);

		fallthrough;
	हाल OCT_DEV_MSIX_ALLOC_VECTOR_DONE:
		octeon_मुक्त_ioq_vector(oct);

		fallthrough;
	हाल OCT_DEV_MBOX_SETUP_DONE:
		oct->fn_list.मुक्त_mbox(oct);

		fallthrough;
	हाल OCT_DEV_IN_RESET:
	हाल OCT_DEV_DROQ_INIT_DONE:
		mdelay(100);
		क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) अणु
			अगर (!(oct->io_qmask.oq & BIT_ULL(i)))
				जारी;
			octeon_delete_droq(oct, i);
		पूर्ण

		fallthrough;
	हाल OCT_DEV_RESP_LIST_INIT_DONE:
		octeon_delete_response_list(oct);

		fallthrough;
	हाल OCT_DEV_INSTR_QUEUE_INIT_DONE:
		क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) अणु
			अगर (!(oct->io_qmask.iq & BIT_ULL(i)))
				जारी;
			octeon_delete_instr_queue(oct, i);
		पूर्ण

		fallthrough;
	हाल OCT_DEV_SC_BUFF_POOL_INIT_DONE:
		octeon_मुक्त_sc_buffer_pool(oct);

		fallthrough;
	हाल OCT_DEV_DISPATCH_INIT_DONE:
		octeon_delete_dispatch_list(oct);
		cancel_delayed_work_sync(&oct->nic_poll_work.work);

		fallthrough;
	हाल OCT_DEV_PCI_MAP_DONE:
		octeon_unmap_pci_barx(oct, 0);
		octeon_unmap_pci_barx(oct, 1);

		fallthrough;
	हाल OCT_DEV_PCI_ENABLE_DONE:
		pci_clear_master(oct->pci_dev);
		/* Disable the device, releasing the PCI INT */
		pci_disable_device(oct->pci_dev);

		fallthrough;
	हाल OCT_DEV_BEGIN_STATE:
		/* Nothing to be करोne here either */
		अवरोध;
	पूर्ण

	tasklet_समाप्त(&oct_priv->droq_tasklet);
पूर्ण

/**
 * send_rx_ctrl_cmd - Send Rx control command
 * @lio: per-network निजी data
 * @start_stop: whether to start or stop
 */
अटल पूर्णांक send_rx_ctrl_cmd(काष्ठा lio *lio, पूर्णांक start_stop)
अणु
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)lio->oct_dev;
	काष्ठा octeon_soft_command *sc;
	जोड़ octnet_cmd *ncmd;
	पूर्णांक retval;

	अगर (oct->props[lio->अगरidx].rx_on == start_stop)
		वापस 0;

	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE,
					  16, 0);
	अगर (!sc) अणु
		netअगर_info(lio, rx_err, lio->netdev,
			   "Failed to allocate octeon_soft_command struct\n");
		वापस -ENOMEM;
	पूर्ण

	ncmd = (जोड़ octnet_cmd *)sc->virtdptr;

	ncmd->u64 = 0;
	ncmd->s.cmd = OCTNET_CMD_RX_CTL;
	ncmd->s.param1 = start_stop;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_CMD, 0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		netअगर_info(lio, rx_err, lio->netdev, "Failed to send RX Control message\n");
		octeon_मुक्त_soft_command(oct, sc);
	पूर्ण अन्यथा अणु
		/* Sleep on a रुको queue till the cond flag indicates that the
		 * response arrived or समयd-out.
		 */
		retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
		अगर (retval)
			वापस retval;

		oct->props[lio->अगरidx].rx_on = start_stop;
		WRITE_ONCE(sc->caller_is_करोne, true);
	पूर्ण

	वापस retval;
पूर्ण

/**
 * liquidio_destroy_nic_device - Destroy NIC device पूर्णांकerface
 * @oct: octeon device
 * @अगरidx: which पूर्णांकerface to destroy
 *
 * Cleanup associated with each पूर्णांकerface क्रम an Octeon device  when NIC
 * module is being unloaded or अगर initialization fails during load.
 */
अटल व्योम liquidio_destroy_nic_device(काष्ठा octeon_device *oct, पूर्णांक अगरidx)
अणु
	काष्ठा net_device *netdev = oct->props[अगरidx].netdev;
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)oct->priv;
	काष्ठा napi_काष्ठा *napi, *n;
	काष्ठा lio *lio;

	अगर (!netdev) अणु
		dev_err(&oct->pci_dev->dev, "%s No netdevice ptr for index %d\n",
			__func__, अगरidx);
		वापस;
	पूर्ण

	lio = GET_LIO(netdev);

	dev_dbg(&oct->pci_dev->dev, "NIC device cleanup\n");

	अगर (atomic_पढ़ो(&lio->अगरstate) & LIO_IFSTATE_RUNNING)
		liquidio_stop(netdev);

	अगर (oct->props[lio->अगरidx].napi_enabled == 1) अणु
		list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
			napi_disable(napi);

		oct->props[lio->अगरidx].napi_enabled = 0;

		oct->droq[0]->ops.poll_mode = 0;
	पूर्ण

	/* Delete NAPI */
	list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
		netअगर_napi_del(napi);

	tasklet_enable(&oct_priv->droq_tasklet);

	अगर (atomic_पढ़ो(&lio->अगरstate) & LIO_IFSTATE_REGISTERED)
		unरेजिस्टर_netdev(netdev);

	cleanup_rx_oom_poll_fn(netdev);

	cleanup_link_status_change_wq(netdev);

	lio_delete_glists(lio);

	मुक्त_netdev(netdev);

	oct->props[अगरidx].gmxport = -1;

	oct->props[अगरidx].netdev = शून्य;
पूर्ण

/**
 * liquidio_stop_nic_module - Stop complete NIC functionality
 * @oct: octeon device
 */
अटल पूर्णांक liquidio_stop_nic_module(काष्ठा octeon_device *oct)
अणु
	काष्ठा lio *lio;
	पूर्णांक i, j;

	dev_dbg(&oct->pci_dev->dev, "Stopping network interfaces\n");
	अगर (!oct->अगरcount) अणु
		dev_err(&oct->pci_dev->dev, "Init for Octeon was not completed\n");
		वापस 1;
	पूर्ण

	spin_lock_bh(&oct->cmd_resp_wqlock);
	oct->cmd_resp_state = OCT_DRV_OFFLINE;
	spin_unlock_bh(&oct->cmd_resp_wqlock);

	क्रम (i = 0; i < oct->अगरcount; i++) अणु
		lio = GET_LIO(oct->props[i].netdev);
		क्रम (j = 0; j < oct->num_oqs; j++)
			octeon_unरेजिस्टर_droq_ops(oct,
						   lio->linfo.rxpciq[j].s.q_no);
	पूर्ण

	क्रम (i = 0; i < oct->अगरcount; i++)
		liquidio_destroy_nic_device(oct, i);

	dev_dbg(&oct->pci_dev->dev, "Network interfaces stopped\n");
	वापस 0;
पूर्ण

/**
 * liquidio_vf_हटाओ - Cleans up resources at unload समय
 * @pdev: PCI device काष्ठाure
 */
अटल व्योम liquidio_vf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा octeon_device *oct_dev = pci_get_drvdata(pdev);

	dev_dbg(&oct_dev->pci_dev->dev, "Stopping device\n");

	अगर (oct_dev->app_mode == CVM_DRV_NIC_APP)
		liquidio_stop_nic_module(oct_dev);

	/* Reset the octeon device and cleanup all memory allocated क्रम
	 * the octeon device by driver.
	 */
	octeon_destroy_resources(oct_dev);

	dev_info(&oct_dev->pci_dev->dev, "Device removed\n");

	/* This octeon device has been हटाओd. Update the global
	 * data काष्ठाure to reflect this. Free the device काष्ठाure.
	 */
	octeon_मुक्त_device_mem(oct_dev);
पूर्ण

/**
 * octeon_pci_os_setup - PCI initialization क्रम each Octeon device.
 * @oct: octeon device
 */
अटल पूर्णांक octeon_pci_os_setup(काष्ठा octeon_device *oct)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	/* setup PCI stuff first */
	अगर (!oct->pci_dev->physfn)
		octeon_pci_flr(oct);
#पूर्ण_अगर

	अगर (pci_enable_device(oct->pci_dev)) अणु
		dev_err(&oct->pci_dev->dev, "pci_enable_device failed\n");
		वापस 1;
	पूर्ण

	अगर (dma_set_mask_and_coherent(&oct->pci_dev->dev, DMA_BIT_MASK(64))) अणु
		dev_err(&oct->pci_dev->dev, "Unexpected DMA device capability\n");
		pci_disable_device(oct->pci_dev);
		वापस 1;
	पूर्ण

	/* Enable PCI DMA Master. */
	pci_set_master(oct->pci_dev);

	वापस 0;
पूर्ण

/**
 * मुक्त_netbuf - Unmap and मुक्त network buffer
 * @buf: buffer
 */
अटल व्योम मुक्त_netbuf(व्योम *buf)
अणु
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा sk_buff *skb;
	काष्ठा lio *lio;

	finfo = (काष्ठा octnet_buf_मुक्त_info *)buf;
	skb = finfo->skb;
	lio = finfo->lio;

	dma_unmap_single(&lio->oct_dev->pci_dev->dev, finfo->dptr, skb->len,
			 DMA_TO_DEVICE);

	tx_buffer_मुक्त(skb);
पूर्ण

/**
 * मुक्त_netsgbuf - Unmap and मुक्त gather buffer
 * @buf: buffer
 */
अटल व्योम मुक्त_netsgbuf(व्योम *buf)
अणु
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा octnic_gather *g;
	काष्ठा sk_buff *skb;
	पूर्णांक i, frags, iq;
	काष्ठा lio *lio;

	finfo = (काष्ठा octnet_buf_मुक्त_info *)buf;
	skb = finfo->skb;
	lio = finfo->lio;
	g = finfo->g;
	frags = skb_shinfo(skb)->nr_frags;

	dma_unmap_single(&lio->oct_dev->pci_dev->dev,
			 g->sg[0].ptr[0], (skb->len - skb->data_len),
			 DMA_TO_DEVICE);

	i = 1;
	जबतक (frags--) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i - 1];

		pci_unmap_page((lio->oct_dev)->pci_dev,
			       g->sg[(i >> 2)].ptr[(i & 3)],
			       skb_frag_size(frag), DMA_TO_DEVICE);
		i++;
	पूर्ण

	iq = skb_iq(lio->oct_dev, skb);

	spin_lock(&lio->glist_lock[iq]);
	list_add_tail(&g->list, &lio->glist[iq]);
	spin_unlock(&lio->glist_lock[iq]);

	tx_buffer_मुक्त(skb);
पूर्ण

/**
 * मुक्त_netsgbuf_with_resp - Unmap and मुक्त gather buffer with response
 * @buf: buffer
 */
अटल व्योम मुक्त_netsgbuf_with_resp(व्योम *buf)
अणु
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा octeon_soft_command *sc;
	काष्ठा octnic_gather *g;
	काष्ठा sk_buff *skb;
	पूर्णांक i, frags, iq;
	काष्ठा lio *lio;

	sc = (काष्ठा octeon_soft_command *)buf;
	skb = (काष्ठा sk_buff *)sc->callback_arg;
	finfo = (काष्ठा octnet_buf_मुक्त_info *)&skb->cb;

	lio = finfo->lio;
	g = finfo->g;
	frags = skb_shinfo(skb)->nr_frags;

	dma_unmap_single(&lio->oct_dev->pci_dev->dev,
			 g->sg[0].ptr[0], (skb->len - skb->data_len),
			 DMA_TO_DEVICE);

	i = 1;
	जबतक (frags--) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i - 1];

		pci_unmap_page((lio->oct_dev)->pci_dev,
			       g->sg[(i >> 2)].ptr[(i & 3)],
			       skb_frag_size(frag), DMA_TO_DEVICE);
		i++;
	पूर्ण

	iq = skb_iq(lio->oct_dev, skb);

	spin_lock(&lio->glist_lock[iq]);
	list_add_tail(&g->list, &lio->glist[iq]);
	spin_unlock(&lio->glist_lock[iq]);

	/* Don't मुक्त the skb yet */
पूर्ण

/**
 * liquidio_खोलो - Net device खोलो क्रम LiquidIO
 * @netdev: network device
 */
अटल पूर्णांक liquidio_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)oct->priv;
	काष्ठा napi_काष्ठा *napi, *n;
	पूर्णांक ret = 0;

	अगर (!oct->props[lio->अगरidx].napi_enabled) अणु
		tasklet_disable(&oct_priv->droq_tasklet);

		list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
			napi_enable(napi);

		oct->props[lio->अगरidx].napi_enabled = 1;

		oct->droq[0]->ops.poll_mode = 1;
	पूर्ण

	अगरstate_set(lio, LIO_IFSTATE_RUNNING);

	/* Ready क्रम link status updates */
	lio->पूर्णांकf_खोलो = 1;

	netअगर_info(lio, अगरup, lio->netdev, "Interface Open, ready for traffic\n");
	start_txqs(netdev);

	INIT_DELAYED_WORK(&lio->stats_wk.work, lio_fetch_stats);
	lio->stats_wk.ctxptr = lio;
	schedule_delayed_work(&lio->stats_wk.work, msecs_to_jअगरfies
					(LIQUIDIO_NDEV_STATS_POLL_TIME_MS));

	/* tell Octeon to start क्रमwarding packets to host */
	ret = send_rx_ctrl_cmd(lio, 1);
	अगर (ret)
		वापस ret;

	dev_info(&oct->pci_dev->dev, "%s interface is opened\n", netdev->name);

	वापस ret;
पूर्ण

/**
 * liquidio_stop - jNet device stop क्रम LiquidIO
 * @netdev: network device
 */
अटल पूर्णांक liquidio_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)oct->priv;
	काष्ठा napi_काष्ठा *napi, *n;
	पूर्णांक ret = 0;

	/* tell Octeon to stop क्रमwarding packets to host */
	ret = send_rx_ctrl_cmd(lio, 0);
	अगर (ret)
		वापस ret;

	netअगर_info(lio, अगरकरोwn, lio->netdev, "Stopping interface!\n");
	/* Inक्रमm that netअगर carrier is करोwn */
	lio->पूर्णांकf_खोलो = 0;
	lio->linfo.link.s.link_up = 0;

	netअगर_carrier_off(netdev);
	lio->link_changes++;

	अगरstate_reset(lio, LIO_IFSTATE_RUNNING);

	stop_txqs(netdev);

	/* Wait क्रम any pending Rx descriptors */
	अगर (lio_रुको_क्रम_clean_oq(oct))
		netअगर_info(lio, rx_err, lio->netdev,
			   "Proceeding with stop interface after partial RX desc processing\n");

	अगर (oct->props[lio->अगरidx].napi_enabled == 1) अणु
		list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
			napi_disable(napi);

		oct->props[lio->अगरidx].napi_enabled = 0;

		oct->droq[0]->ops.poll_mode = 0;

		tasklet_enable(&oct_priv->droq_tasklet);
	पूर्ण

	cancel_delayed_work_sync(&lio->stats_wk.work);

	dev_info(&oct->pci_dev->dev, "%s interface is stopped\n", netdev->name);

	वापस ret;
पूर्ण

/**
 * get_new_flags - Converts a mask based on net device flags
 * @netdev: network device
 *
 * This routine generates a octnet_अगरflags mask from the net device flags
 * received from the OS.
 */
अटल क्रमागत octnet_अगरflags get_new_flags(काष्ठा net_device *netdev)
अणु
	क्रमागत octnet_अगरflags f = OCTNET_IFFLAG_UNICAST;

	अगर (netdev->flags & IFF_PROMISC)
		f |= OCTNET_IFFLAG_PROMISC;

	अगर (netdev->flags & IFF_ALLMULTI)
		f |= OCTNET_IFFLAG_ALLMULTI;

	अगर (netdev->flags & IFF_MULTICAST) अणु
		f |= OCTNET_IFFLAG_MULTICAST;

		/* Accept all multicast addresses अगर there are more than we
		 * can handle
		 */
		अगर (netdev_mc_count(netdev) > MAX_OCTEON_MULTICAST_ADDR)
			f |= OCTNET_IFFLAG_ALLMULTI;
	पूर्ण

	अगर (netdev->flags & IFF_BROADCAST)
		f |= OCTNET_IFFLAG_BROADCAST;

	वापस f;
पूर्ण

अटल व्योम liquidio_set_uc_list(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	काष्ठा netdev_hw_addr *ha;
	u64 *mac;

	अगर (lio->netdev_uc_count == netdev_uc_count(netdev))
		वापस;

	अगर (netdev_uc_count(netdev) > MAX_NCTRL_UDD) अणु
		dev_err(&oct->pci_dev->dev, "too many MAC addresses in netdev uc list\n");
		वापस;
	पूर्ण

	lio->netdev_uc_count = netdev_uc_count(netdev);

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_UC_LIST;
	nctrl.ncmd.s.more = lio->netdev_uc_count;
	nctrl.ncmd.s.param1 = oct->vf_num;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	/* copy all the addresses पूर्णांकo the udd */
	mac = &nctrl.udd[0];
	netdev_क्रम_each_uc_addr(ha, netdev) अणु
		ether_addr_copy(((u8 *)mac) + 2, ha->addr);
		mac++;
	पूर्ण

	octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
पूर्ण

/**
 * liquidio_set_mcast_list - Net device set_multicast_list
 * @netdev: network device
 */
अटल व्योम liquidio_set_mcast_list(काष्ठा net_device *netdev)
अणु
	पूर्णांक mc_count = min(netdev_mc_count(netdev), MAX_OCTEON_MULTICAST_ADDR);
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	काष्ठा netdev_hw_addr *ha;
	u64 *mc;
	पूर्णांक ret;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	/* Create a ctrl pkt command to be sent to core app. */
	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_MULTI_LIST;
	nctrl.ncmd.s.param1 = get_new_flags(netdev);
	nctrl.ncmd.s.param2 = mc_count;
	nctrl.ncmd.s.more = mc_count;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	/* copy all the addresses पूर्णांकo the udd */
	mc = &nctrl.udd[0];
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		*mc = 0;
		ether_addr_copy(((u8 *)mc) + 2, ha->addr);
		/* no need to swap bytes */
		अगर (++mc > &nctrl.udd[mc_count])
			अवरोध;
	पूर्ण

	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;

	/* Apparently, any activity in this call from the kernel has to
	 * be atomic. So we won't रुको क्रम response.
	 */

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "DEVFLAGS change failed in core (ret: 0x%x)\n",
			ret);
	पूर्ण

	liquidio_set_uc_list(netdev);
पूर्ण

/**
 * liquidio_set_mac - Net device set_mac_address
 * @netdev: network device
 * @p: opaque poपूर्णांकer to sockaddr
 */
अटल पूर्णांक liquidio_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)p;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (ether_addr_equal(addr->sa_data, netdev->dev_addr))
		वापस 0;

	अगर (lio->linfo.macaddr_is_admin_asgnd)
		वापस -EPERM;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_CHANGE_MACADDR;
	nctrl.ncmd.s.param1 = 0;
	nctrl.ncmd.s.more = 1;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;

	nctrl.udd[0] = 0;
	/* The MAC Address is presented in network byte order. */
	ether_addr_copy((u8 *)&nctrl.udd[0] + 2, addr->sa_data);

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret < 0) अणु
		dev_err(&oct->pci_dev->dev, "MAC Address change failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (nctrl.sc_status ==
	    FIRMWARE_STATUS_CODE(OCTEON_REQUEST_NO_PERMISSION)) अणु
		dev_err(&oct->pci_dev->dev, "MAC Address change failed: no permission\n");
		वापस -EPERM;
	पूर्ण

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	ether_addr_copy(((u8 *)&lio->linfo.hw_addr) + 2, addr->sa_data);

	वापस 0;
पूर्ण

अटल व्योम
liquidio_get_stats64(काष्ठा net_device *netdev,
		     काष्ठा rtnl_link_stats64 *lstats)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct;
	u64 pkts = 0, drop = 0, bytes = 0;
	काष्ठा oct_droq_stats *oq_stats;
	काष्ठा oct_iq_stats *iq_stats;
	पूर्णांक i, iq_no, oq_no;

	oct = lio->oct_dev;

	अगर (अगरstate_check(lio, LIO_IFSTATE_RESETTING))
		वापस;

	क्रम (i = 0; i < oct->num_iqs; i++) अणु
		iq_no = lio->linfo.txpciq[i].s.q_no;
		iq_stats = &oct->instr_queue[iq_no]->stats;
		pkts += iq_stats->tx_करोne;
		drop += iq_stats->tx_dropped;
		bytes += iq_stats->tx_tot_bytes;
	पूर्ण

	lstats->tx_packets = pkts;
	lstats->tx_bytes = bytes;
	lstats->tx_dropped = drop;

	pkts = 0;
	drop = 0;
	bytes = 0;

	क्रम (i = 0; i < oct->num_oqs; i++) अणु
		oq_no = lio->linfo.rxpciq[i].s.q_no;
		oq_stats = &oct->droq[oq_no]->stats;
		pkts += oq_stats->rx_pkts_received;
		drop += (oq_stats->rx_dropped +
			 oq_stats->dropped_nodispatch +
			 oq_stats->dropped_toomany +
			 oq_stats->dropped_nomem);
		bytes += oq_stats->rx_bytes_received;
	पूर्ण

	lstats->rx_bytes = bytes;
	lstats->rx_packets = pkts;
	lstats->rx_dropped = drop;

	lstats->multicast = oct->link_stats.fromwire.fw_total_mcast;

	/* detailed rx_errors: */
	lstats->rx_length_errors = oct->link_stats.fromwire.l2_err;
	/* recved pkt with crc error */
	lstats->rx_crc_errors = oct->link_stats.fromwire.fcs_err;
	/* recv'd frame alignment error */
	lstats->rx_frame_errors = oct->link_stats.fromwire.frame_err;

	lstats->rx_errors = lstats->rx_length_errors + lstats->rx_crc_errors +
			    lstats->rx_frame_errors;

	/* detailed tx_errors */
	lstats->tx_पातed_errors = oct->link_stats.fromhost.fw_err_pko;
	lstats->tx_carrier_errors = oct->link_stats.fromhost.fw_err_link;

	lstats->tx_errors = lstats->tx_पातed_errors +
		lstats->tx_carrier_errors;
पूर्ण

/**
 * hwtstamp_ioctl - Handler क्रम SIOCSHWTSTAMP ioctl
 * @netdev: network device
 * @अगरr: पूर्णांकerface request
 */
अटल पूर्णांक hwtstamp_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा hwtstamp_config conf;

	अगर (copy_from_user(&conf, अगरr->अगरr_data, माप(conf)))
		वापस -EFAULT;

	अगर (conf.flags)
		वापस -EINVAL;

	चयन (conf.tx_type) अणु
	हाल HWTSTAMP_TX_ON:
	हाल HWTSTAMP_TX_OFF:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (conf.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		conf.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (conf.rx_filter == HWTSTAMP_FILTER_ALL)
		अगरstate_set(lio, LIO_IFSTATE_RX_TIMESTAMP_ENABLED);

	अन्यथा
		अगरstate_reset(lio, LIO_IFSTATE_RX_TIMESTAMP_ENABLED);

	वापस copy_to_user(अगरr->अगरr_data, &conf, माप(conf)) ? -EFAULT : 0;
पूर्ण

/**
 * liquidio_ioctl - ioctl handler
 * @netdev: network device
 * @अगरr: पूर्णांकerface request
 * @cmd: command
 */
अटल पूर्णांक liquidio_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस hwtstamp_ioctl(netdev, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम handle_बारtamp(काष्ठा octeon_device *oct, u32 status, व्योम *buf)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)buf;
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा oct_बारtamp_resp *resp;
	काष्ठा octeon_soft_command *sc;
	काष्ठा lio *lio;

	finfo = (काष्ठा octnet_buf_मुक्त_info *)skb->cb;
	lio = finfo->lio;
	sc = finfo->sc;
	oct = lio->oct_dev;
	resp = (काष्ठा oct_बारtamp_resp *)sc->virtrptr;

	अगर (status != OCTEON_REQUEST_DONE) अणु
		dev_err(&oct->pci_dev->dev, "Tx timestamp instruction failed. Status: %llx\n",
			CVM_CAST64(status));
		resp->बारtamp = 0;
	पूर्ण

	octeon_swap_8B_data(&resp->बारtamp, 1);

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)) अणु
		काष्ठा skb_shared_hwtstamps ts;
		u64 ns = resp->बारtamp;

		netअगर_info(lio, tx_करोne, lio->netdev,
			   "Got resulting SKBTX_HW_TSTAMP skb=%p ns=%016llu\n",
			   skb, (अचिन्हित दीर्घ दीर्घ)ns);
		ts.hwtstamp = ns_to_kसमय(ns + lio->ptp_adjust);
		skb_tstamp_tx(skb, &ts);
	पूर्ण

	octeon_मुक्त_soft_command(oct, sc);
	tx_buffer_मुक्त(skb);
पूर्ण

/* send_nic_बारtamp_pkt - Send a data packet that will be बारtamped
 * @oct: octeon device
 * @ndata: poपूर्णांकer to network data
 * @finfo: poपूर्णांकer to निजी network data
 */
अटल पूर्णांक send_nic_बारtamp_pkt(काष्ठा octeon_device *oct,
				  काष्ठा octnic_data_pkt *ndata,
				  काष्ठा octnet_buf_मुक्त_info *finfo,
				  पूर्णांक xmit_more)
अणु
	काष्ठा octeon_soft_command *sc;
	पूर्णांक ring_करोorbell;
	काष्ठा lio *lio;
	पूर्णांक retval;
	u32 len;

	lio = finfo->lio;

	sc = octeon_alloc_soft_command_resp(oct, &ndata->cmd,
					    माप(काष्ठा oct_बारtamp_resp));
	finfo->sc = sc;

	अगर (!sc) अणु
		dev_err(&oct->pci_dev->dev, "No memory for timestamped data packet\n");
		वापस IQ_SEND_FAILED;
	पूर्ण

	अगर (ndata->reqtype == REQTYPE_NORESP_NET)
		ndata->reqtype = REQTYPE_RESP_NET;
	अन्यथा अगर (ndata->reqtype == REQTYPE_NORESP_NET_SG)
		ndata->reqtype = REQTYPE_RESP_NET_SG;

	sc->callback = handle_बारtamp;
	sc->callback_arg = finfo->skb;
	sc->iq_no = ndata->q_no;

	len = (u32)((काष्ठा octeon_instr_ih3 *)(&sc->cmd.cmd3.ih3))->dlengsz;

	ring_करोorbell = !xmit_more;

	retval = octeon_send_command(oct, sc->iq_no, ring_करोorbell, &sc->cmd,
				     sc, len, ndata->reqtype);

	अगर (retval == IQ_SEND_FAILED) अणु
		dev_err(&oct->pci_dev->dev, "timestamp data packet failed status: %x\n",
			retval);
		octeon_मुक्त_soft_command(oct, sc);
	पूर्ण अन्यथा अणु
		netअगर_info(lio, tx_queued, lio->netdev, "Queued timestamp packet\n");
	पूर्ण

	वापस retval;
पूर्ण

/**
 * liquidio_xmit - Transmit networks packets to the Octeon पूर्णांकerface
 * @skb: skbuff काष्ठा to be passed to network layer.
 * @netdev: poपूर्णांकer to network device
 * @वापसs whether the packet was transmitted to the device okay or not
 *             (NETDEV_TX_OK or NETDEV_TX_BUSY)
 */
अटल netdev_tx_t liquidio_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा octnet_buf_मुक्त_info *finfo;
	जोड़ octnic_cmd_setup cmdsetup;
	काष्ठा octnic_data_pkt ndata;
	काष्ठा octeon_instr_irh *irh;
	काष्ठा oct_iq_stats *stats;
	काष्ठा octeon_device *oct;
	पूर्णांक q_idx = 0, iq_no = 0;
	जोड़ tx_info *tx_info;
	पूर्णांक xmit_more = 0;
	काष्ठा lio *lio;
	पूर्णांक status = 0;
	u64 dptr = 0;
	u32 tag = 0;
	पूर्णांक j;

	lio = GET_LIO(netdev);
	oct = lio->oct_dev;

	q_idx = skb_iq(lio->oct_dev, skb);
	tag = q_idx;
	iq_no = lio->linfo.txpciq[q_idx].s.q_no;

	stats = &oct->instr_queue[iq_no]->stats;

	/* Check क्रम all conditions in which the current packet cannot be
	 * transmitted.
	 */
	अगर (!(atomic_पढ़ो(&lio->अगरstate) & LIO_IFSTATE_RUNNING) ||
	    (!lio->linfo.link.s.link_up) || (skb->len <= 0)) अणु
		netअगर_info(lio, tx_err, lio->netdev, "Transmit failed link_status : %d\n",
			   lio->linfo.link.s.link_up);
		जाओ lio_xmit_failed;
	पूर्ण

	/* Use space in skb->cb to store info used to unmap and
	 * मुक्त the buffers.
	 */
	finfo = (काष्ठा octnet_buf_मुक्त_info *)skb->cb;
	finfo->lio = lio;
	finfo->skb = skb;
	finfo->sc = शून्य;

	/* Prepare the attributes क्रम the data to be passed to OSI. */
	स_रखो(&ndata, 0, माप(काष्ठा octnic_data_pkt));

	ndata.buf = finfo;

	ndata.q_no = iq_no;

	अगर (octnet_iq_is_full(oct, ndata.q_no)) अणु
		/* defer sending अगर queue is full */
		netअगर_info(lio, tx_err, lio->netdev, "Transmit failed iq:%d full\n",
			   ndata.q_no);
		stats->tx_iq_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	ndata.datasize = skb->len;

	cmdsetup.u64 = 0;
	cmdsetup.s.iq_no = iq_no;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (skb->encapsulation) अणु
			cmdsetup.s.tnl_csum = 1;
			stats->tx_vxlan++;
		पूर्ण अन्यथा अणु
			cmdsetup.s.transport_csum = 1;
		पूर्ण
	पूर्ण
	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		cmdsetup.s.बारtamp = 1;
	पूर्ण

	अगर (!skb_shinfo(skb)->nr_frags) अणु
		cmdsetup.s.u.datasize = skb->len;
		octnet_prepare_pci_cmd(oct, &ndata.cmd, &cmdsetup, tag);
		/* Offload checksum calculation क्रम TCP/UDP packets */
		dptr = dma_map_single(&oct->pci_dev->dev,
				      skb->data,
				      skb->len,
				      DMA_TO_DEVICE);
		अगर (dma_mapping_error(&oct->pci_dev->dev, dptr)) अणु
			dev_err(&oct->pci_dev->dev, "%s DMA mapping error 1\n",
				__func__);
			वापस NETDEV_TX_BUSY;
		पूर्ण

		ndata.cmd.cmd3.dptr = dptr;
		finfo->dptr = dptr;
		ndata.reqtype = REQTYPE_NORESP_NET;

	पूर्ण अन्यथा अणु
		skb_frag_t *frag;
		काष्ठा octnic_gather *g;
		पूर्णांक i, frags;

		spin_lock(&lio->glist_lock[q_idx]);
		g = (काष्ठा octnic_gather *)
			lio_list_delete_head(&lio->glist[q_idx]);
		spin_unlock(&lio->glist_lock[q_idx]);

		अगर (!g) अणु
			netअगर_info(lio, tx_err, lio->netdev,
				   "Transmit scatter gather: glist null!\n");
			जाओ lio_xmit_failed;
		पूर्ण

		cmdsetup.s.gather = 1;
		cmdsetup.s.u.gatherptrs = (skb_shinfo(skb)->nr_frags + 1);
		octnet_prepare_pci_cmd(oct, &ndata.cmd, &cmdsetup, tag);

		स_रखो(g->sg, 0, g->sg_size);

		g->sg[0].ptr[0] = dma_map_single(&oct->pci_dev->dev,
						 skb->data,
						 (skb->len - skb->data_len),
						 DMA_TO_DEVICE);
		अगर (dma_mapping_error(&oct->pci_dev->dev, g->sg[0].ptr[0])) अणु
			dev_err(&oct->pci_dev->dev, "%s DMA mapping error 2\n",
				__func__);
			वापस NETDEV_TX_BUSY;
		पूर्ण
		add_sg_size(&g->sg[0], (skb->len - skb->data_len), 0);

		frags = skb_shinfo(skb)->nr_frags;
		i = 1;
		जबतक (frags--) अणु
			frag = &skb_shinfo(skb)->frags[i - 1];

			g->sg[(i >> 2)].ptr[(i & 3)] =
				skb_frag_dma_map(&oct->pci_dev->dev,
						 frag, 0, skb_frag_size(frag),
						 DMA_TO_DEVICE);
			अगर (dma_mapping_error(&oct->pci_dev->dev,
					      g->sg[i >> 2].ptr[i & 3])) अणु
				dma_unmap_single(&oct->pci_dev->dev,
						 g->sg[0].ptr[0],
						 skb->len - skb->data_len,
						 DMA_TO_DEVICE);
				क्रम (j = 1; j < i; j++) अणु
					frag = &skb_shinfo(skb)->frags[j - 1];
					dma_unmap_page(&oct->pci_dev->dev,
						       g->sg[j >> 2].ptr[j & 3],
						       skb_frag_size(frag),
						       DMA_TO_DEVICE);
				पूर्ण
				dev_err(&oct->pci_dev->dev, "%s DMA mapping error 3\n",
					__func__);
				वापस NETDEV_TX_BUSY;
			पूर्ण

			add_sg_size(&g->sg[(i >> 2)], skb_frag_size(frag),
				    (i & 3));
			i++;
		पूर्ण

		dptr = g->sg_dma_ptr;

		ndata.cmd.cmd3.dptr = dptr;
		finfo->dptr = dptr;
		finfo->g = g;

		ndata.reqtype = REQTYPE_NORESP_NET_SG;
	पूर्ण

	irh = (काष्ठा octeon_instr_irh *)&ndata.cmd.cmd3.irh;
	tx_info = (जोड़ tx_info *)&ndata.cmd.cmd3.ossp[0];

	अगर (skb_shinfo(skb)->gso_size) अणु
		tx_info->s.gso_size = skb_shinfo(skb)->gso_size;
		tx_info->s.gso_segs = skb_shinfo(skb)->gso_segs;
	पूर्ण

	/* HW insert VLAN tag */
	अगर (skb_vlan_tag_present(skb)) अणु
		irh->priority = skb_vlan_tag_get(skb) >> VLAN_PRIO_SHIFT;
		irh->vlan = skb_vlan_tag_get(skb) & VLAN_VID_MASK;
	पूर्ण

	xmit_more = netdev_xmit_more();

	अगर (unlikely(cmdsetup.s.बारtamp))
		status = send_nic_बारtamp_pkt(oct, &ndata, finfo, xmit_more);
	अन्यथा
		status = octnet_send_nic_data_pkt(oct, &ndata, xmit_more);
	अगर (status == IQ_SEND_FAILED)
		जाओ lio_xmit_failed;

	netअगर_info(lio, tx_queued, lio->netdev, "Transmit queued successfully\n");

	अगर (status == IQ_SEND_STOP) अणु
		dev_err(&oct->pci_dev->dev, "Rcvd IQ_SEND_STOP signal; stopping IQ-%d\n",
			iq_no);
		netअगर_stop_subqueue(netdev, q_idx);
	पूर्ण

	netअगर_trans_update(netdev);

	अगर (tx_info->s.gso_segs)
		stats->tx_करोne += tx_info->s.gso_segs;
	अन्यथा
		stats->tx_करोne++;
	stats->tx_tot_bytes += ndata.datasize;

	वापस NETDEV_TX_OK;

lio_xmit_failed:
	stats->tx_dropped++;
	netअगर_info(lio, tx_err, lio->netdev, "IQ%d Transmit dropped:%llu\n",
		   iq_no, stats->tx_dropped);
	अगर (dptr)
		dma_unmap_single(&oct->pci_dev->dev, dptr,
				 ndata.datasize, DMA_TO_DEVICE);

	octeon_ring_करोorbell_locked(oct, iq_no);

	tx_buffer_मुक्त(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * liquidio_tx_समयout - Network device Tx समयout
 * @netdev: poपूर्णांकer to network device
 * @txqueue: index of the hung transmit queue
 */
अटल व्योम liquidio_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा lio *lio;

	lio = GET_LIO(netdev);

	netअगर_info(lio, tx_err, lio->netdev,
		   "Transmit timeout tx_dropped:%ld, waking up queues now!!\n",
		   netdev->stats.tx_dropped);
	netअगर_trans_update(netdev);
	wake_txqs(netdev);
पूर्ण

अटल पूर्णांक
liquidio_vlan_rx_add_vid(काष्ठा net_device *netdev,
			 __be16 proto __attribute__((unused)), u16 vid)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_ADD_VLAN_FILTER;
	nctrl.ncmd.s.param1 = vid;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "Add VLAN filter failed in core (ret: 0x%x)\n",
			ret);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
liquidio_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
			  __be16 proto __attribute__((unused)), u16 vid)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_DEL_VLAN_FILTER;
	nctrl.ncmd.s.param1 = vid;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "Del VLAN filter failed in core (ret: 0x%x)\n",
			ret);
		अगर (ret > 0)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/** Sending command to enable/disable RX checksum offload
 * @param netdev                poपूर्णांकer to network device
 * @param command               OCTNET_CMD_TNL_RX_CSUM_CTL
 * @param rx_cmd_bit            OCTNET_CMD_RXCSUM_ENABLE/
 *                              OCTNET_CMD_RXCSUM_DISABLE
 * @वापसs                     SUCCESS or FAILURE
 */
अटल पूर्णांक liquidio_set_rxcsum_command(काष्ठा net_device *netdev, पूर्णांक command,
				       u8 rx_cmd)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = command;
	nctrl.ncmd.s.param1 = rx_cmd;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "DEVFLAGS RXCSUM change failed in core (ret:0x%x)\n",
			ret);
		अगर (ret > 0)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/** Sending command to add/delete VxLAN UDP port to firmware
 * @param netdev                poपूर्णांकer to network device
 * @param command               OCTNET_CMD_VXLAN_PORT_CONFIG
 * @param vxlan_port            VxLAN port to be added or deleted
 * @param vxlan_cmd_bit         OCTNET_CMD_VXLAN_PORT_ADD,
 *                              OCTNET_CMD_VXLAN_PORT_DEL
 * @वापसs                     SUCCESS or FAILURE
 */
अटल पूर्णांक liquidio_vxlan_port_command(काष्ठा net_device *netdev, पूर्णांक command,
				       u16 vxlan_port, u8 vxlan_cmd_bit)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = command;
	nctrl.ncmd.s.more = vxlan_cmd_bit;
	nctrl.ncmd.s.param1 = vxlan_port;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev,
			"DEVFLAGS VxLAN port add/delete failed in core (ret : 0x%x)\n",
			ret);
		अगर (ret > 0)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक liquidio_udp_tunnel_set_port(काष्ठा net_device *netdev,
					अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
					काष्ठा udp_tunnel_info *ti)
अणु
	वापस liquidio_vxlan_port_command(netdev,
					   OCTNET_CMD_VXLAN_PORT_CONFIG,
					   htons(ti->port),
					   OCTNET_CMD_VXLAN_PORT_ADD);
पूर्ण

अटल पूर्णांक liquidio_udp_tunnel_unset_port(काष्ठा net_device *netdev,
					  अचिन्हित पूर्णांक table,
					  अचिन्हित पूर्णांक entry,
					  काष्ठा udp_tunnel_info *ti)
अणु
	वापस liquidio_vxlan_port_command(netdev,
					   OCTNET_CMD_VXLAN_PORT_CONFIG,
					   htons(ti->port),
					   OCTNET_CMD_VXLAN_PORT_DEL);
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info liquidio_udp_tunnels = अणु
	.set_port	= liquidio_udp_tunnel_set_port,
	.unset_port	= liquidio_udp_tunnel_unset_port,
	.tables		= अणु
		अणु .n_entries = 1024, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN, पूर्ण,
	पूर्ण,
पूर्ण;

/** \मrief Net device fix features
 * @param netdev  poपूर्णांकer to network device
 * @param request features requested
 * @वापसs updated features list
 */
अटल netdev_features_t liquidio_fix_features(काष्ठा net_device *netdev,
					       netdev_features_t request)
अणु
	काष्ठा lio *lio = netdev_priv(netdev);

	अगर ((request & NETIF_F_RXCSUM) &&
	    !(lio->dev_capability & NETIF_F_RXCSUM))
		request &= ~NETIF_F_RXCSUM;

	अगर ((request & NETIF_F_HW_CSUM) &&
	    !(lio->dev_capability & NETIF_F_HW_CSUM))
		request &= ~NETIF_F_HW_CSUM;

	अगर ((request & NETIF_F_TSO) && !(lio->dev_capability & NETIF_F_TSO))
		request &= ~NETIF_F_TSO;

	अगर ((request & NETIF_F_TSO6) && !(lio->dev_capability & NETIF_F_TSO6))
		request &= ~NETIF_F_TSO6;

	अगर ((request & NETIF_F_LRO) && !(lio->dev_capability & NETIF_F_LRO))
		request &= ~NETIF_F_LRO;

	/* Disable LRO अगर RXCSUM is off */
	अगर (!(request & NETIF_F_RXCSUM) && (netdev->features & NETIF_F_LRO) &&
	    (lio->dev_capability & NETIF_F_LRO))
		request &= ~NETIF_F_LRO;

	वापस request;
पूर्ण

/** \मrief Net device set features
 * @param netdev  poपूर्णांकer to network device
 * @param features features to enable/disable
 */
अटल पूर्णांक liquidio_set_features(काष्ठा net_device *netdev,
				 netdev_features_t features)
अणु
	काष्ठा lio *lio = netdev_priv(netdev);

	अगर (!((netdev->features ^ features) & NETIF_F_LRO))
		वापस 0;

	अगर ((features & NETIF_F_LRO) && (lio->dev_capability & NETIF_F_LRO))
		liquidio_set_feature(netdev, OCTNET_CMD_LRO_ENABLE,
				     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);
	अन्यथा अगर (!(features & NETIF_F_LRO) &&
		 (lio->dev_capability & NETIF_F_LRO))
		liquidio_set_feature(netdev, OCTNET_CMD_LRO_DISABLE,
				     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);
	अगर (!(netdev->features & NETIF_F_RXCSUM) &&
	    (lio->enc_dev_capability & NETIF_F_RXCSUM) &&
	    (features & NETIF_F_RXCSUM))
		liquidio_set_rxcsum_command(netdev, OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_ENABLE);
	अन्यथा अगर ((netdev->features & NETIF_F_RXCSUM) &&
		 (lio->enc_dev_capability & NETIF_F_RXCSUM) &&
		 !(features & NETIF_F_RXCSUM))
		liquidio_set_rxcsum_command(netdev, OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_DISABLE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops lionetdevops = अणु
	.nकरो_खोलो		= liquidio_खोलो,
	.nकरो_stop		= liquidio_stop,
	.nकरो_start_xmit		= liquidio_xmit,
	.nकरो_get_stats64	= liquidio_get_stats64,
	.nकरो_set_mac_address	= liquidio_set_mac,
	.nकरो_set_rx_mode	= liquidio_set_mcast_list,
	.nकरो_tx_समयout		= liquidio_tx_समयout,
	.nकरो_vlan_rx_add_vid    = liquidio_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid   = liquidio_vlan_rx_समाप्त_vid,
	.nकरो_change_mtu		= liquidio_change_mtu,
	.nकरो_करो_ioctl		= liquidio_ioctl,
	.nकरो_fix_features	= liquidio_fix_features,
	.nकरो_set_features	= liquidio_set_features,
पूर्ण;

अटल पूर्णांक lio_nic_info(काष्ठा octeon_recv_info *recv_info, व्योम *buf)
अणु
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)buf;
	काष्ठा octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	जोड़ oct_link_status *ls;
	पूर्णांक gmxport = 0;
	पूर्णांक i;

	अगर (recv_pkt->buffer_size[0] != (माप(*ls) + OCT_DROQ_INFO_SIZE)) अणु
		dev_err(&oct->pci_dev->dev, "Malformed NIC_INFO, len=%d, ifidx=%d\n",
			recv_pkt->buffer_size[0],
			recv_pkt->rh.r_nic_info.gmxport);
		जाओ nic_info_err;
	पूर्ण

	gmxport = recv_pkt->rh.r_nic_info.gmxport;
	ls = (जोड़ oct_link_status *)(get_rbd(recv_pkt->buffer_ptr[0]) +
		OCT_DROQ_INFO_SIZE);

	octeon_swap_8B_data((u64 *)ls, (माप(जोड़ oct_link_status)) >> 3);

	क्रम (i = 0; i < oct->अगरcount; i++) अणु
		अगर (oct->props[i].gmxport == gmxport) अणु
			update_link_status(oct->props[i].netdev, ls);
			अवरोध;
		पूर्ण
	पूर्ण

nic_info_err:
	क्रम (i = 0; i < recv_pkt->buffer_count; i++)
		recv_buffer_मुक्त(recv_pkt->buffer_ptr[i]);
	octeon_मुक्त_recv_info(recv_info);
	वापस 0;
पूर्ण

/**
 * setup_nic_devices - Setup network पूर्णांकerfaces
 * @octeon_dev:  octeon device
 *
 * Called during init समय क्रम each device. It assumes the NIC
 * is alपढ़ोy up and running.  The link inक्रमmation क्रम each
 * पूर्णांकerface is passed in link_info.
 */
अटल पूर्णांक setup_nic_devices(काष्ठा octeon_device *octeon_dev)
अणु
	पूर्णांक retval, num_iqueues, num_oqueues;
	u32 resp_size, data_size;
	काष्ठा liquidio_अगर_cfg_resp *resp;
	काष्ठा octeon_soft_command *sc;
	जोड़ oct_nic_अगर_cfg अगर_cfg;
	काष्ठा octdev_props *props;
	काष्ठा net_device *netdev;
	काष्ठा lio_version *vdata;
	काष्ठा lio *lio = शून्य;
	u8 mac[ETH_ALEN], i, j;
	u32 अगरidx_or_pfnum;

	अगरidx_or_pfnum = octeon_dev->pf_num;

	/* This is to handle link status changes */
	octeon_रेजिस्टर_dispatch_fn(octeon_dev, OPCODE_NIC, OPCODE_NIC_INFO,
				    lio_nic_info, octeon_dev);

	/* REQTYPE_RESP_NET and REQTYPE_SOFT_COMMAND करो not have मुक्त functions.
	 * They are handled directly.
	 */
	octeon_रेजिस्टर_reqtype_मुक्त_fn(octeon_dev, REQTYPE_NORESP_NET,
					मुक्त_netbuf);

	octeon_रेजिस्टर_reqtype_मुक्त_fn(octeon_dev, REQTYPE_NORESP_NET_SG,
					मुक्त_netsgbuf);

	octeon_रेजिस्टर_reqtype_मुक्त_fn(octeon_dev, REQTYPE_RESP_NET_SG,
					मुक्त_netsgbuf_with_resp);

	क्रम (i = 0; i < octeon_dev->अगरcount; i++) अणु
		resp_size = माप(काष्ठा liquidio_अगर_cfg_resp);
		data_size = माप(काष्ठा lio_version);
		sc = (काष्ठा octeon_soft_command *)
			octeon_alloc_soft_command(octeon_dev, data_size,
						  resp_size, 0);
		resp = (काष्ठा liquidio_अगर_cfg_resp *)sc->virtrptr;
		vdata = (काष्ठा lio_version *)sc->virtdptr;

		*((u64 *)vdata) = 0;
		vdata->major = cpu_to_be16(LIQUIDIO_BASE_MAJOR_VERSION);
		vdata->minor = cpu_to_be16(LIQUIDIO_BASE_MINOR_VERSION);
		vdata->micro = cpu_to_be16(LIQUIDIO_BASE_MICRO_VERSION);

		अगर_cfg.u64 = 0;

		अगर_cfg.s.num_iqueues = octeon_dev->sriov_info.rings_per_vf;
		अगर_cfg.s.num_oqueues = octeon_dev->sriov_info.rings_per_vf;
		अगर_cfg.s.base_queue = 0;

		sc->iq_no = 0;

		octeon_prepare_soft_command(octeon_dev, sc, OPCODE_NIC,
					    OPCODE_NIC_IF_CFG, 0, अगर_cfg.u64,
					    0);

		init_completion(&sc->complete);
		sc->sc_status = OCTEON_REQUEST_PENDING;

		retval = octeon_send_soft_command(octeon_dev, sc);
		अगर (retval == IQ_SEND_FAILED) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"iq/oq config failed status: %x\n", retval);
			/* Soft instr is मुक्तd by driver in हाल of failure. */
			octeon_मुक्त_soft_command(octeon_dev, sc);
			वापस(-EIO);
		पूर्ण

		/* Sleep on a रुको queue till the cond flag indicates that the
		 * response arrived or समयd-out.
		 */
		retval = रुको_क्रम_sc_completion_समयout(octeon_dev, sc, 0);
		अगर (retval)
			वापस retval;

		retval = resp->status;
		अगर (retval) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"iq/oq config failed, retval = %d\n", retval);
			WRITE_ONCE(sc->caller_is_करोne, true);
			वापस -EIO;
		पूर्ण

		snम_लिखो(octeon_dev->fw_info.liquidio_firmware_version,
			 32, "%s",
			 resp->cfg_info.liquidio_firmware_version);

		octeon_swap_8B_data((u64 *)(&resp->cfg_info),
				    (माप(काष्ठा liquidio_अगर_cfg_info)) >> 3);

		num_iqueues = hweight64(resp->cfg_info.iqmask);
		num_oqueues = hweight64(resp->cfg_info.oqmask);

		अगर (!(num_iqueues) || !(num_oqueues)) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"Got bad iqueues (%016llx) or oqueues (%016llx) from firmware.\n",
				resp->cfg_info.iqmask, resp->cfg_info.oqmask);
			WRITE_ONCE(sc->caller_is_करोne, true);
			जाओ setup_nic_dev_करोne;
		पूर्ण
		dev_dbg(&octeon_dev->pci_dev->dev,
			"interface %d, iqmask %016llx, oqmask %016llx, numiqueues %d, numoqueues %d\n",
			i, resp->cfg_info.iqmask, resp->cfg_info.oqmask,
			num_iqueues, num_oqueues);

		netdev = alloc_etherdev_mq(LIO_SIZE, num_iqueues);

		अगर (!netdev) अणु
			dev_err(&octeon_dev->pci_dev->dev, "Device allocation failed\n");
			WRITE_ONCE(sc->caller_is_करोne, true);
			जाओ setup_nic_dev_करोne;
		पूर्ण

		SET_NETDEV_DEV(netdev, &octeon_dev->pci_dev->dev);

		/* Associate the routines that will handle dअगरferent
		 * netdev tasks.
		 */
		netdev->netdev_ops = &lionetdevops;

		lio = GET_LIO(netdev);

		स_रखो(lio, 0, माप(काष्ठा lio));

		lio->अगरidx = अगरidx_or_pfnum;

		props = &octeon_dev->props[i];
		props->gmxport = resp->cfg_info.linfo.gmxport;
		props->netdev = netdev;

		lio->linfo.num_rxpciq = num_oqueues;
		lio->linfo.num_txpciq = num_iqueues;

		क्रम (j = 0; j < num_oqueues; j++) अणु
			lio->linfo.rxpciq[j].u64 =
			    resp->cfg_info.linfo.rxpciq[j].u64;
		पूर्ण
		क्रम (j = 0; j < num_iqueues; j++) अणु
			lio->linfo.txpciq[j].u64 =
			    resp->cfg_info.linfo.txpciq[j].u64;
		पूर्ण

		lio->linfo.hw_addr = resp->cfg_info.linfo.hw_addr;
		lio->linfo.gmxport = resp->cfg_info.linfo.gmxport;
		lio->linfo.link.u64 = resp->cfg_info.linfo.link.u64;
		lio->linfo.macaddr_is_admin_asgnd =
			resp->cfg_info.linfo.macaddr_is_admin_asgnd;
		lio->linfo.macaddr_spoofchk =
			resp->cfg_info.linfo.macaddr_spoofchk;

		lio->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

		lio->dev_capability = NETIF_F_HIGHDMA
				      | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM
				      | NETIF_F_SG | NETIF_F_RXCSUM
				      | NETIF_F_TSO | NETIF_F_TSO6
				      | NETIF_F_GRO
				      | NETIF_F_LRO;
		netअगर_set_gso_max_size(netdev, OCTNIC_GSO_MAX_SIZE);

		/* Copy of transmit encapsulation capabilities:
		 * TSO, TSO6, Checksums क्रम this device
		 */
		lio->enc_dev_capability = NETIF_F_IP_CSUM
					  | NETIF_F_IPV6_CSUM
					  | NETIF_F_GSO_UDP_TUNNEL
					  | NETIF_F_HW_CSUM | NETIF_F_SG
					  | NETIF_F_RXCSUM
					  | NETIF_F_TSO | NETIF_F_TSO6
					  | NETIF_F_LRO;

		netdev->hw_enc_features =
		    (lio->enc_dev_capability & ~NETIF_F_LRO);
		netdev->udp_tunnel_nic_info = &liquidio_udp_tunnels;

		netdev->vlan_features = lio->dev_capability;
		/* Add any unchangeable hw features */
		lio->dev_capability |= NETIF_F_HW_VLAN_CTAG_FILTER |
				       NETIF_F_HW_VLAN_CTAG_RX |
				       NETIF_F_HW_VLAN_CTAG_TX;

		netdev->features = (lio->dev_capability & ~NETIF_F_LRO);

		netdev->hw_features = lio->dev_capability;
		netdev->hw_features &= ~NETIF_F_HW_VLAN_CTAG_RX;

		/* MTU range: 68 - 16000 */
		netdev->min_mtu = LIO_MIN_MTU_SIZE;
		netdev->max_mtu = LIO_MAX_MTU_SIZE;

		WRITE_ONCE(sc->caller_is_करोne, true);

		/* Poपूर्णांक to the  properties क्रम octeon device to which this
		 * पूर्णांकerface beदीर्घs.
		 */
		lio->oct_dev = octeon_dev;
		lio->octprops = props;
		lio->netdev = netdev;

		dev_dbg(&octeon_dev->pci_dev->dev,
			"if%d gmx: %d hw_addr: 0x%llx\n", i,
			lio->linfo.gmxport, CVM_CAST64(lio->linfo.hw_addr));

		/* 64-bit swap required on LE machines */
		octeon_swap_8B_data(&lio->linfo.hw_addr, 1);
		क्रम (j = 0; j < ETH_ALEN; j++)
			mac[j] = *((u8 *)(((u8 *)&lio->linfo.hw_addr) + 2 + j));

		/* Copy MAC Address to OS network device काष्ठाure */
		ether_addr_copy(netdev->dev_addr, mac);

		अगर (liquidio_setup_io_queues(octeon_dev, i,
					     lio->linfo.num_txpciq,
					     lio->linfo.num_rxpciq)) अणु
			dev_err(&octeon_dev->pci_dev->dev, "I/O queues creation failed\n");
			जाओ setup_nic_dev_मुक्त;
		पूर्ण

		अगरstate_set(lio, LIO_IFSTATE_DROQ_OPS);

		/* For VFs, enable Octeon device पूर्णांकerrupts here,
		 * as this is contingent upon IO queue setup
		 */
		octeon_dev->fn_list.enable_पूर्णांकerrupt(octeon_dev,
						     OCTEON_ALL_INTR);

		/* By शेष all पूर्णांकerfaces on a single Octeon uses the same
		 * tx and rx queues
		 */
		lio->txq = lio->linfo.txpciq[0].s.q_no;
		lio->rxq = lio->linfo.rxpciq[0].s.q_no;

		lio->tx_qsize = octeon_get_tx_qsize(octeon_dev, lio->txq);
		lio->rx_qsize = octeon_get_rx_qsize(octeon_dev, lio->rxq);

		अगर (lio_setup_glists(octeon_dev, lio, num_iqueues)) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"Gather list allocation failed\n");
			जाओ setup_nic_dev_मुक्त;
		पूर्ण

		/* Register ethtool support */
		liquidio_set_ethtool_ops(netdev);
		अगर (lio->oct_dev->chip_id == OCTEON_CN23XX_VF_VID)
			octeon_dev->priv_flags = OCT_PRIV_FLAG_DEFAULT;
		अन्यथा
			octeon_dev->priv_flags = 0x0;

		अगर (netdev->features & NETIF_F_LRO)
			liquidio_set_feature(netdev, OCTNET_CMD_LRO_ENABLE,
					     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);

		अगर (setup_link_status_change_wq(netdev))
			जाओ setup_nic_dev_मुक्त;

		अगर (setup_rx_oom_poll_fn(netdev))
			जाओ setup_nic_dev_मुक्त;

		/* Register the network device with the OS */
		अगर (रेजिस्टर_netdev(netdev)) अणु
			dev_err(&octeon_dev->pci_dev->dev, "Device registration failed\n");
			जाओ setup_nic_dev_मुक्त;
		पूर्ण

		dev_dbg(&octeon_dev->pci_dev->dev,
			"Setup NIC ifidx:%d mac:%02x%02x%02x%02x%02x%02x\n",
			i, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		netअगर_carrier_off(netdev);
		lio->link_changes++;

		अगरstate_set(lio, LIO_IFSTATE_REGISTERED);

		/* Sending command to firmware to enable Rx checksum offload
		 * by शेष at the समय of setup of Liquidio driver क्रम
		 * this device
		 */
		liquidio_set_rxcsum_command(netdev, OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_ENABLE);
		liquidio_set_feature(netdev, OCTNET_CMD_TNL_TX_CSUM_CTL,
				     OCTNET_CMD_TXCSUM_ENABLE);

		dev_dbg(&octeon_dev->pci_dev->dev,
			"NIC ifidx:%d Setup successful\n", i);

		octeon_dev->no_speed_setting = 1;
	पूर्ण

	वापस 0;

setup_nic_dev_मुक्त:

	जबतक (i--) अणु
		dev_err(&octeon_dev->pci_dev->dev,
			"NIC ifidx:%d Setup failed\n", i);
		liquidio_destroy_nic_device(octeon_dev, i);
	पूर्ण

setup_nic_dev_करोne:

	वापस -ENODEV;
पूर्ण

/**
 * liquidio_init_nic_module - initialize the NIC
 * @oct: octeon device
 *
 * This initialization routine is called once the Octeon device application is
 * up and running
 */
अटल पूर्णांक liquidio_init_nic_module(काष्ठा octeon_device *oct)
अणु
	पूर्णांक num_nic_ports = 1;
	पूर्णांक i, retval = 0;

	dev_dbg(&oct->pci_dev->dev, "Initializing network interfaces\n");

	/* only शेष iq and oq were initialized
	 * initialize the rest as well run port_config command क्रम each port
	 */
	oct->अगरcount = num_nic_ports;
	स_रखो(oct->props, 0,
	       माप(काष्ठा octdev_props) * num_nic_ports);

	क्रम (i = 0; i < MAX_OCTEON_LINKS; i++)
		oct->props[i].gmxport = -1;

	retval = setup_nic_devices(oct);
	अगर (retval) अणु
		dev_err(&oct->pci_dev->dev, "Setup NIC devices failed\n");
		जाओ octnet_init_failure;
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "Network interfaces ready\n");

	वापस retval;

octnet_init_failure:

	oct->अगरcount = 0;

	वापस retval;
पूर्ण

/**
 * octeon_device_init - Device initialization क्रम each Octeon device that is probed
 * @oct:  octeon device
 */
अटल पूर्णांक octeon_device_init(काष्ठा octeon_device *oct)
अणु
	u32 rev_id;
	पूर्णांक j;

	atomic_set(&oct->status, OCT_DEV_BEGIN_STATE);

	/* Enable access to the octeon device and make its DMA capability
	 * known to the OS.
	 */
	अगर (octeon_pci_os_setup(oct))
		वापस 1;
	atomic_set(&oct->status, OCT_DEV_PCI_ENABLE_DONE);

	oct->chip_id = OCTEON_CN23XX_VF_VID;
	pci_पढ़ो_config_dword(oct->pci_dev, 8, &rev_id);
	oct->rev_id = rev_id & 0xff;

	अगर (cn23xx_setup_octeon_vf_device(oct))
		वापस 1;

	atomic_set(&oct->status, OCT_DEV_PCI_MAP_DONE);

	oct->app_mode = CVM_DRV_NIC_APP;

	/* Initialize the dispatch mechanism used to push packets arriving on
	 * Octeon Output queues.
	 */
	अगर (octeon_init_dispatch_list(oct))
		वापस 1;

	atomic_set(&oct->status, OCT_DEV_DISPATCH_INIT_DONE);

	अगर (octeon_set_io_queues_off(oct)) अणु
		dev_err(&oct->pci_dev->dev, "setting io queues off failed\n");
		वापस 1;
	पूर्ण

	अगर (oct->fn_list.setup_device_regs(oct)) अणु
		dev_err(&oct->pci_dev->dev, "device registers configuration failed\n");
		वापस 1;
	पूर्ण

	/* Initialize soft command buffer pool */
	अगर (octeon_setup_sc_buffer_pool(oct)) अणु
		dev_err(&oct->pci_dev->dev, "sc buffer pool allocation failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&oct->status, OCT_DEV_SC_BUFF_POOL_INIT_DONE);

	/* Setup the data काष्ठाures that manage this Octeon's Input queues. */
	अगर (octeon_setup_instr_queues(oct)) अणु
		dev_err(&oct->pci_dev->dev, "instruction queue initialization failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&oct->status, OCT_DEV_INSTR_QUEUE_INIT_DONE);

	/* Initialize lists to manage the requests of dअगरferent types that
	 * arrive from user & kernel applications क्रम this octeon device.
	 */
	अगर (octeon_setup_response_list(oct)) अणु
		dev_err(&oct->pci_dev->dev, "Response list allocation failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&oct->status, OCT_DEV_RESP_LIST_INIT_DONE);

	अगर (octeon_setup_output_queues(oct)) अणु
		dev_err(&oct->pci_dev->dev, "Output queue initialization failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&oct->status, OCT_DEV_DROQ_INIT_DONE);

	अगर (oct->fn_list.setup_mbox(oct)) अणु
		dev_err(&oct->pci_dev->dev, "Mailbox setup failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&oct->status, OCT_DEV_MBOX_SETUP_DONE);

	अगर (octeon_allocate_ioq_vector(oct, oct->sriov_info.rings_per_vf)) अणु
		dev_err(&oct->pci_dev->dev, "ioq vector allocation failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&oct->status, OCT_DEV_MSIX_ALLOC_VECTOR_DONE);

	dev_info(&oct->pci_dev->dev, "OCTEON_CN23XX VF: %d ioqs\n",
		 oct->sriov_info.rings_per_vf);

	/* Setup the पूर्णांकerrupt handler and record the INT SUM रेजिस्टर address*/
	अगर (octeon_setup_पूर्णांकerrupt(oct, oct->sriov_info.rings_per_vf))
		वापस 1;

	atomic_set(&oct->status, OCT_DEV_INTR_SET_DONE);

	/* ***************************************************************
	 * The पूर्णांकerrupts need to be enabled क्रम the PF<-->VF handshake.
	 * They are [re]-enabled after the PF<-->VF handshake so that the
	 * correct OQ tick value is used (i.e. the value retrieved from
	 * the PF as part of the handshake).
	 */

	/* Enable Octeon device पूर्णांकerrupts */
	oct->fn_list.enable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

	अगर (cn23xx_octeon_pfvf_handshake(oct))
		वापस 1;

	/* Here we [re]-enable the पूर्णांकerrupts so that the correct OQ tick value
	 * is used (i.e. the value that was retrieved during the handshake)
	 */

	/* Enable Octeon device पूर्णांकerrupts */
	oct->fn_list.enable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);
	/* *************************************************************** */

	/* Enable the input and output queues क्रम this Octeon device */
	अगर (oct->fn_list.enable_io_queues(oct)) अणु
		dev_err(&oct->pci_dev->dev, "enabling io queues failed\n");
		वापस 1;
	पूर्ण

	atomic_set(&oct->status, OCT_DEV_IO_QUEUES_DONE);

	atomic_set(&oct->status, OCT_DEV_HOST_OK);

	/* Send Credit क्रम Octeon Output queues. Credits are always sent after
	 * the output queue is enabled.
	 */
	क्रम (j = 0; j < oct->num_oqs; j++)
		ग_लिखोl(oct->droq[j]->max_count, oct->droq[j]->pkts_credit_reg);

	/* Packets can start arriving on the output queues from this poपूर्णांक. */

	atomic_set(&oct->status, OCT_DEV_CORE_OK);

	atomic_set(&oct->status, OCT_DEV_RUNNING);

	अगर (liquidio_init_nic_module(oct))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक __init liquidio_vf_init(व्योम)
अणु
	octeon_init_device_list(0);
	वापस pci_रेजिस्टर_driver(&liquidio_vf_pci_driver);
पूर्ण

अटल व्योम __निकास liquidio_vf_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&liquidio_vf_pci_driver);

	pr_info("LiquidIO_VF network module is now unloaded\n");
पूर्ण

module_init(liquidio_vf_init);
module_निकास(liquidio_vf_निकास);
