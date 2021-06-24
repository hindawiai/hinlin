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
#समावेश <linux/firmware.h>
#समावेश <net/vxlan.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_nic.h"
#समावेश "octeon_main.h"
#समावेश "octeon_network.h"
#समावेश "cn66xx_regs.h"
#समावेश "cn66xx_device.h"
#समावेश "cn68xx_device.h"
#समावेश "cn23xx_pf_device.h"
#समावेश "liquidio_image.h"
#समावेश "lio_vf_rep.h"

MODULE_AUTHOR("Cavium Networks, <support@cavium.com>");
MODULE_DESCRIPTION("Cavium LiquidIO Intelligent Server Adapter Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(LIO_FW_सूची LIO_FW_BASE_NAME LIO_210SV_NAME
		"_" LIO_FW_NAME_TYPE_NIC LIO_FW_NAME_SUFFIX);
MODULE_FIRMWARE(LIO_FW_सूची LIO_FW_BASE_NAME LIO_210NV_NAME
		"_" LIO_FW_NAME_TYPE_NIC LIO_FW_NAME_SUFFIX);
MODULE_FIRMWARE(LIO_FW_सूची LIO_FW_BASE_NAME LIO_410NV_NAME
		"_" LIO_FW_NAME_TYPE_NIC LIO_FW_NAME_SUFFIX);
MODULE_FIRMWARE(LIO_FW_सूची LIO_FW_BASE_NAME LIO_23XX_NAME
		"_" LIO_FW_NAME_TYPE_NIC LIO_FW_NAME_SUFFIX);

अटल पूर्णांक ddr_समयout = 10000;
module_param(ddr_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(ddr_समयout,
		 "Number of milliseconds to wait for DDR initialization. 0 waits for ddr_timeout to be set to non-zero value before starting to check");

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "NETIF_MSG debug bits");

अटल अक्षर fw_type[LIO_MAX_FW_TYPE_LEN] = LIO_FW_NAME_TYPE_AUTO;
module_param_string(fw_type, fw_type, माप(fw_type), 0444);
MODULE_PARM_DESC(fw_type, "Type of firmware to be loaded (default is \"auto\"), which uses firmware in flash, if present, else loads \"nic\".");

अटल u32 console_biपंचांगask;
module_param(console_biपंचांगask, पूर्णांक, 0644);
MODULE_PARM_DESC(console_biपंचांगask,
		 "Bitmask indicating which consoles have debug output redirected to syslog.");

/**
 * octeon_console_debug_enabled - determines अगर a given console has debug enabled.
 * @console: console to check
 * Return:  1 = enabled. 0 otherwise
 */
अटल पूर्णांक octeon_console_debug_enabled(u32 console)
अणु
	वापस (console_biपंचांगask >> (console)) & 0x1;
पूर्ण

/* Polling पूर्णांकerval क्रम determining when NIC application is alive */
#घोषणा LIQUIDIO_STARTER_POLL_INTERVAL_MS 100

/* runसमय link query पूर्णांकerval */
#घोषणा LIQUIDIO_LINK_QUERY_INTERVAL_MS         1000
/* update स_स्थानीय to octeon firmware every 60 seconds.
 * make firmware to use same समय reference, so that it will be easy to
 * correlate firmware logged events/errors with host events, क्रम debugging.
 */
#घोषणा LIO_SYNC_OCTEON_TIME_INTERVAL_MS 60000

/* समय to रुको क्रम possible in-flight requests in milliseconds */
#घोषणा WAIT_INFLIGHT_REQUEST	msecs_to_jअगरfies(1000)

काष्ठा lio_trusted_vf_ctx अणु
	काष्ठा completion complete;
	पूर्णांक status;
पूर्ण;

काष्ठा oct_link_status_resp अणु
	u64 rh;
	काष्ठा oct_link_info link_info;
	u64 status;
पूर्ण;

काष्ठा oct_बारtamp_resp अणु
	u64 rh;
	u64 बारtamp;
	u64 status;
पूर्ण;

#घोषणा OCT_TIMESTAMP_RESP_SIZE (माप(काष्ठा oct_बारtamp_resp))

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

/* Octeon device properties to be used by the NIC module.
 * Each octeon device in the प्रणाली will be represented
 * by this काष्ठाure in the NIC module.
 */

#घोषणा OCTNIC_GSO_MAX_HEADER_SIZE 128
#घोषणा OCTNIC_GSO_MAX_SIZE                                                    \
	(CN23XX_DEFAULT_INPUT_JABBER - OCTNIC_GSO_MAX_HEADER_SIZE)

काष्ठा handshake अणु
	काष्ठा completion init;
	काष्ठा completion started;
	काष्ठा pci_dev *pci_dev;
	पूर्णांक init_ok;
	पूर्णांक started_ok;
पूर्ण;

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक liquidio_enable_sriov(काष्ठा pci_dev *dev, पूर्णांक num_vfs);
#पूर्ण_अगर

अटल पूर्णांक octeon_dbg_console_prपूर्णांक(काष्ठा octeon_device *oct, u32 console_num,
				    अक्षर *prefix, अक्षर *suffix);

अटल पूर्णांक octeon_device_init(काष्ठा octeon_device *);
अटल पूर्णांक liquidio_stop(काष्ठा net_device *netdev);
अटल व्योम liquidio_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक liquidio_probe(काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *ent);
अटल पूर्णांक liquidio_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vfidx,
				      पूर्णांक linkstate);

अटल काष्ठा handshake handshake[MAX_OCTEON_DEVICES];
अटल काष्ठा completion first_stage;

अटल व्योम octeon_droq_bh(काष्ठा tasklet_काष्ठा *t)
अणु
	पूर्णांक q_no;
	पूर्णांक reschedule = 0;
	काष्ठा octeon_device_priv *oct_priv = from_tasklet(oct_priv, t,
							  droq_tasklet);
	काष्ठा octeon_device *oct = oct_priv->dev;

	क्रम (q_no = 0; q_no < MAX_OCTEON_OUTPUT_QUEUES(oct); q_no++) अणु
		अगर (!(oct->io_qmask.oq & BIT_ULL(q_no)))
			जारी;
		reschedule |= octeon_droq_process_packets(oct, oct->droq[q_no],
							  MAX_PACKET_BUDGET);
		lio_enable_irq(oct->droq[q_no], शून्य);

		अगर (OCTEON_CN23XX_PF(oct) && oct->msix_on) अणु
			/* set समय and cnt पूर्णांकerrupt thresholds क्रम this DROQ
			 * क्रम NAPI
			 */
			पूर्णांक adjusted_q_no = q_no + oct->sriov_info.pf_srn;

			octeon_ग_लिखो_csr64(
			    oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(adjusted_q_no),
			    0x5700000040ULL);
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_SLI_OQ_PKTS_SENT(adjusted_q_no), 0);
		पूर्ण
	पूर्ण

	अगर (reschedule)
		tasklet_schedule(&oct_priv->droq_tasklet);
पूर्ण

अटल पूर्णांक lio_रुको_क्रम_oq_pkts(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)oct->priv;
	पूर्णांक retry = 100, pkt_cnt = 0, pending_pkts = 0;
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
 * क्रमce_io_queues_off - Forces all IO queues off on a given device
 * @oct: Poपूर्णांकer to Octeon device
 */
अटल व्योम क्रमce_io_queues_off(काष्ठा octeon_device *oct)
अणु
	अगर ((oct->chip_id == OCTEON_CN66XX) ||
	    (oct->chip_id == OCTEON_CN68XX)) अणु
		/* Reset the Enable bits क्रम Input Queues. */
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB, 0);

		/* Reset the Enable bits क्रम Output Queues. */
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB, 0);
	पूर्ण
पूर्ण

/**
 * pcierror_quiesce_device - Cause device to go quiet so it can be safely हटाओd/reset/etc
 * @oct: Poपूर्णांकer to Octeon device
 */
अटल अंतरभूत व्योम pcierror_quiesce_device(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i;

	/* Disable the input and output queues now. No more packets will
	 * arrive from Octeon, but we should रुको क्रम all packet processing
	 * to finish.
	 */
	क्रमce_io_queues_off(oct);

	/* To allow क्रम in-flight requests */
	schedule_समयout_unपूर्णांकerruptible(WAIT_INFLIGHT_REQUEST);

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
	पूर्णांक pos = 0x100;
	u32 status, mask;

	pr_info("%s :\n", __func__);

	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, &status);
	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, &mask);
	अगर (dev->error_state == pci_channel_io_normal)
		status &= ~mask;        /* Clear corresponding nonfatal bits */
	अन्यथा
		status &= mask;         /* Clear corresponding fatal bits */
	pci_ग_लिखो_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, status);
पूर्ण

/**
 * stop_pci_io - Stop all PCI IO to a given device
 * @oct: Poपूर्णांकer to Octeon device
 */
अटल व्योम stop_pci_io(काष्ठा octeon_device *oct)
अणु
	/* No more inकाष्ठाions will be क्रमwarded. */
	atomic_set(&oct->status, OCT_DEV_IN_RESET);

	pci_disable_device(oct->pci_dev);

	/* Disable पूर्णांकerrupts  */
	oct->fn_list.disable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

	pcierror_quiesce_device(oct);

	/* Release the पूर्णांकerrupt line */
	मुक्त_irq(oct->pci_dev->irq, oct);

	अगर (oct->flags & LIO_FLAG_MSI_ENABLED)
		pci_disable_msi(oct->pci_dev);

	dev_dbg(&oct->pci_dev->dev, "Device state is now %s\n",
		lio_get_state_string(&oct->status));

	/* making it a common function क्रम all OCTEON models */
	cleanup_aer_uncorrect_error_status(oct->pci_dev);
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

	/* Always वापस a DISCONNECT. There is no support क्रम recovery but only
	 * क्रम a clean shutकरोwn.
	 */
	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

/**
 * liquidio_pcie_mmio_enabled - mmio handler
 * @pdev: Poपूर्णांकer to PCI device
 */
अटल pci_ers_result_t liquidio_pcie_mmio_enabled(काष्ठा pci_dev __maybe_unused *pdev)
अणु
	/* We should never hit this since we never ask क्रम a reset क्रम a Fatal
	 * Error. We always वापस DISCONNECT in io_error above.
	 * But play safe and वापस RECOVERED क्रम now.
	 */
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * liquidio_pcie_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot. Implementation
 * resembles the first-half of the octeon_resume routine.
 */
अटल pci_ers_result_t liquidio_pcie_slot_reset(काष्ठा pci_dev __maybe_unused *pdev)
अणु
	/* We should never hit this since we never ask क्रम a reset क्रम a Fatal
	 * Error. We always वापस DISCONNECT in io_error above.
	 * But play safe and वापस RECOVERED क्रम now.
	 */
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * liquidio_pcie_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation. Implementation resembles the
 * second-half of the octeon_resume routine.
 */
अटल व्योम liquidio_pcie_resume(काष्ठा pci_dev __maybe_unused *pdev)
अणु
	/* Nothing to be करोne here. */
पूर्ण

#घोषणा liquidio_suspend शून्य
#घोषणा liquidio_resume शून्य

/* For PCI-E Advanced Error Recovery (AER) Interface */
अटल स्थिर काष्ठा pci_error_handlers liquidio_err_handler = अणु
	.error_detected = liquidio_pcie_error_detected,
	.mmio_enabled	= liquidio_pcie_mmio_enabled,
	.slot_reset	= liquidio_pcie_slot_reset,
	.resume		= liquidio_pcie_resume,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id liquidio_pci_tbl[] = अणु
	अणु       /* 68xx */
		PCI_VENDOR_ID_CAVIUM, 0x91, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0
	पूर्ण,
	अणु       /* 66xx */
		PCI_VENDOR_ID_CAVIUM, 0x92, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0
	पूर्ण,
	अणु       /* 23xx pf */
		PCI_VENDOR_ID_CAVIUM, 0x9702, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0
	पूर्ण,
	अणु
		0, 0, 0, 0, 0, 0, 0
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, liquidio_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(liquidio_pm_ops, liquidio_suspend, liquidio_resume);

अटल काष्ठा pci_driver liquidio_pci_driver = अणु
	.name		= "LiquidIO",
	.id_table	= liquidio_pci_tbl,
	.probe		= liquidio_probe,
	.हटाओ		= liquidio_हटाओ,
	.err_handler	= &liquidio_err_handler,    /* For AER */
	.driver.pm	= &liquidio_pm_ops,
#अगर_घोषित CONFIG_PCI_IOV
	.sriov_configure = liquidio_enable_sriov,
#पूर्ण_अगर
पूर्ण;

/**
 * liquidio_init_pci - रेजिस्टर PCI driver
 */
अटल पूर्णांक liquidio_init_pci(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&liquidio_pci_driver);
पूर्ण

/**
 * liquidio_deinit_pci - unरेजिस्टर PCI driver
 */
अटल व्योम liquidio_deinit_pci(व्योम)
अणु
	pci_unरेजिस्टर_driver(&liquidio_pci_driver);
पूर्ण

/**
 * check_txq_status - Check Tx queue status, and take appropriate action
 * @lio: per-network निजी data
 * Return: 0 अगर full, number of queues woken up otherwise
 */
अटल अंतरभूत पूर्णांक check_txq_status(काष्ठा lio *lio)
अणु
	पूर्णांक numqs = lio->netdev->real_num_tx_queues;
	पूर्णांक ret_val = 0;
	पूर्णांक q, iq;

	/* check each sub-queue state */
	क्रम (q = 0; q < numqs; q++) अणु
		iq = lio->linfo.txpciq[q %
			lio->oct_dev->num_iqs].s.q_no;
		अगर (octnet_iq_is_full(lio->oct_dev, iq))
			जारी;
		अगर (__netअगर_subqueue_stopped(lio->netdev, q)) अणु
			netअगर_wake_subqueue(lio->netdev, q);
			INCR_INSTRQUEUE_PKT_COUNT(lio->oct_dev, iq,
						  tx_restart, 1);
			ret_val++;
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * prपूर्णांक_link_info -  Prपूर्णांक link inक्रमmation
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
अटल अंतरभूत पूर्णांक setup_link_status_change_wq(काष्ठा net_device *netdev)
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

अटल अंतरभूत व्योम cleanup_link_status_change_wq(काष्ठा net_device *netdev)
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
अटल अंतरभूत व्योम update_link_status(काष्ठा net_device *netdev,
				      जोड़ oct_link_status *ls)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	पूर्णांक changed = (lio->linfo.link.u64 != ls->u64);
	पूर्णांक current_max_mtu = lio->linfo.link.s.mtu;
	काष्ठा octeon_device *oct = lio->oct_dev;

	dev_dbg(&oct->pci_dev->dev, "%s: lio->linfo.link.u64=%llx, ls->u64=%llx\n",
		__func__, lio->linfo.link.u64, ls->u64);
	lio->linfo.link.u64 = ls->u64;

	अगर ((lio->पूर्णांकf_खोलो) && (changed)) अणु
		prपूर्णांक_link_info(netdev);
		lio->link_changes++;

		अगर (lio->linfo.link.s.link_up) अणु
			dev_dbg(&oct->pci_dev->dev, "%s: link_up", __func__);
			netअगर_carrier_on(netdev);
			wake_txqs(netdev);
		पूर्ण अन्यथा अणु
			dev_dbg(&oct->pci_dev->dev, "%s: link_off", __func__);
			netअगर_carrier_off(netdev);
			stop_txqs(netdev);
		पूर्ण
		अगर (lio->linfo.link.s.mtu != current_max_mtu) अणु
			netअगर_info(lio, probe, lio->netdev, "Max MTU changed from %d to %d\n",
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
 * lio_sync_octeon_समय - send latest स_स्थानीय to octeon firmware so that
 * firmware will correct it's समय, in हाल there is a समय skew
 *
 * @work: work scheduled to send समय update to octeon firmware
 **/
अटल व्योम lio_sync_octeon_समय(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा lio *lio = (काष्ठा lio *)wk->ctxptr;
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octeon_soft_command *sc;
	काष्ठा बारpec64 ts;
	काष्ठा lio_समय *lt;
	पूर्णांक ret;

	sc = octeon_alloc_soft_command(oct, माप(काष्ठा lio_समय), 16, 0);
	अगर (!sc) अणु
		dev_err(&oct->pci_dev->dev,
			"Failed to sync time to octeon: soft command allocation failed\n");
		वापस;
	पूर्ण

	lt = (काष्ठा lio_समय *)sc->virtdptr;

	/* Get समय of the day */
	kसमय_get_real_ts64(&ts);
	lt->sec = ts.tv_sec;
	lt->nsec = ts.tv_nsec;
	octeon_swap_8B_data((u64 *)lt, (माप(काष्ठा lio_समय)) / 8);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;
	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_SYNC_OCTEON_TIME, 0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ret = octeon_send_soft_command(oct, sc);
	अगर (ret == IQ_SEND_FAILED) अणु
		dev_err(&oct->pci_dev->dev,
			"Failed to sync time to octeon: failed to send soft command\n");
		octeon_मुक्त_soft_command(oct, sc);
	पूर्ण अन्यथा अणु
		WRITE_ONCE(sc->caller_is_करोne, true);
	पूर्ण

	queue_delayed_work(lio->sync_octeon_समय_wq.wq,
			   &lio->sync_octeon_समय_wq.wk.work,
			   msecs_to_jअगरfies(LIO_SYNC_OCTEON_TIME_INTERVAL_MS));
पूर्ण

/**
 * setup_sync_octeon_समय_wq - prepare work to periodically update local समय to octeon firmware
 *
 * @netdev: network device which should send समय update to firmware
 **/
अटल अंतरभूत पूर्णांक setup_sync_octeon_समय_wq(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	lio->sync_octeon_समय_wq.wq =
		alloc_workqueue("update-octeon-time", WQ_MEM_RECLAIM, 0);
	अगर (!lio->sync_octeon_समय_wq.wq) अणु
		dev_err(&oct->pci_dev->dev, "Unable to create wq to update octeon time\n");
		वापस -1;
	पूर्ण
	INIT_DELAYED_WORK(&lio->sync_octeon_समय_wq.wk.work,
			  lio_sync_octeon_समय);
	lio->sync_octeon_समय_wq.wk.ctxptr = lio;
	queue_delayed_work(lio->sync_octeon_समय_wq.wq,
			   &lio->sync_octeon_समय_wq.wk.work,
			   msecs_to_jअगरfies(LIO_SYNC_OCTEON_TIME_INTERVAL_MS));

	वापस 0;
पूर्ण

/**
 * cleanup_sync_octeon_समय_wq - destroy wq
 *
 * @netdev: network device which should send समय update to firmware
 *
 * Stop scheduling and destroy the work created to periodically update local
 * समय to octeon firmware.
 **/
अटल अंतरभूत व्योम cleanup_sync_octeon_समय_wq(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा cavium_wq *समय_wq = &lio->sync_octeon_समय_wq;

	अगर (समय_wq->wq) अणु
		cancel_delayed_work_sync(&समय_wq->wk.work);
		destroy_workqueue(समय_wq->wq);
	पूर्ण
पूर्ण

अटल काष्ठा octeon_device *get_other_octeon_device(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_device *other_oct;

	other_oct = lio_get_device(oct->octeon_id + 1);

	अगर (other_oct && other_oct->pci_dev) अणु
		पूर्णांक oct_busnum, other_oct_busnum;

		oct_busnum = oct->pci_dev->bus->number;
		other_oct_busnum = other_oct->pci_dev->bus->number;

		अगर (oct_busnum == other_oct_busnum) अणु
			पूर्णांक oct_slot, other_oct_slot;

			oct_slot = PCI_SLOT(oct->pci_dev->devfn);
			other_oct_slot = PCI_SLOT(other_oct->pci_dev->devfn);

			अगर (oct_slot == other_oct_slot)
				वापस other_oct;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम disable_all_vf_links(काष्ठा octeon_device *oct)
अणु
	काष्ठा net_device *netdev;
	पूर्णांक max_vfs, vf, i;

	अगर (!oct)
		वापस;

	max_vfs = oct->sriov_info.max_vfs;

	क्रम (i = 0; i < oct->अगरcount; i++) अणु
		netdev = oct->props[i].netdev;
		अगर (!netdev)
			जारी;

		क्रम (vf = 0; vf < max_vfs; vf++)
			liquidio_set_vf_link_state(netdev, vf,
						   IFLA_VF_LINK_STATE_DISABLE);
	पूर्ण
पूर्ण

अटल पूर्णांक liquidio_watchकरोg(व्योम *param)
अणु
	bool err_msg_was_prपूर्णांकed[LIO_MAX_CORES];
	u16 mask_of_crashed_or_stuck_cores = 0;
	bool all_vf_links_are_disabled = false;
	काष्ठा octeon_device *oct = param;
	काष्ठा octeon_device *other_oct;
#अगर_घोषित CONFIG_MODULE_UNLOAD
	दीर्घ refcount, vfs_referencing_pf;
	u64 vfs_mask1, vfs_mask2;
#पूर्ण_अगर
	पूर्णांक core;

	स_रखो(err_msg_was_prपूर्णांकed, 0, माप(err_msg_was_prपूर्णांकed));

	जबतक (!kthपढ़ो_should_stop()) अणु
		/* sleep क्रम a couple of seconds so that we करोn't hog the CPU */
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(2000));

		mask_of_crashed_or_stuck_cores =
		    (u16)octeon_पढ़ो_csr64(oct, CN23XX_SLI_SCRATCH2);

		अगर (!mask_of_crashed_or_stuck_cores)
			जारी;

		WRITE_ONCE(oct->cores_crashed, true);
		other_oct = get_other_octeon_device(oct);
		अगर (other_oct)
			WRITE_ONCE(other_oct->cores_crashed, true);

		क्रम (core = 0; core < LIO_MAX_CORES; core++) अणु
			bool core_crashed_or_got_stuck;

			core_crashed_or_got_stuck =
						(mask_of_crashed_or_stuck_cores
						 >> core) & 1;

			अगर (core_crashed_or_got_stuck &&
			    !err_msg_was_prपूर्णांकed[core]) अणु
				dev_err(&oct->pci_dev->dev,
					"ERROR: Octeon core %d crashed or got stuck!  See oct-fwdump for details.\n",
					core);
				err_msg_was_prपूर्णांकed[core] = true;
			पूर्ण
		पूर्ण

		अगर (all_vf_links_are_disabled)
			जारी;

		disable_all_vf_links(oct);
		disable_all_vf_links(other_oct);
		all_vf_links_are_disabled = true;

#अगर_घोषित CONFIG_MODULE_UNLOAD
		vfs_mask1 = READ_ONCE(oct->sriov_info.vf_drv_loaded_mask);
		vfs_mask2 = READ_ONCE(other_oct->sriov_info.vf_drv_loaded_mask);

		vfs_referencing_pf  = hweight64(vfs_mask1);
		vfs_referencing_pf += hweight64(vfs_mask2);

		refcount = module_refcount(THIS_MODULE);
		अगर (refcount >= vfs_referencing_pf) अणु
			जबतक (vfs_referencing_pf) अणु
				module_put(THIS_MODULE);
				vfs_referencing_pf--;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/**
 * liquidio_probe - PCI probe handler
 * @pdev: PCI device काष्ठाure
 * @ent: unused
 */
अटल पूर्णांक
liquidio_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id __maybe_unused *ent)
अणु
	काष्ठा octeon_device *oct_dev = शून्य;
	काष्ठा handshake *hs;

	oct_dev = octeon_allocate_device(pdev->device,
					 माप(काष्ठा octeon_device_priv));
	अगर (!oct_dev) अणु
		dev_err(&pdev->dev, "Unable to allocate device\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (pdev->device == OCTEON_CN23XX_PF_VID)
		oct_dev->msix_on = LIO_FLAG_MSIX_ENABLED;

	/* Enable PTP क्रम 6XXX Device */
	अगर (((pdev->device == OCTEON_CN66XX) ||
	     (pdev->device == OCTEON_CN68XX)))
		oct_dev->ptp_enable = true;
	अन्यथा
		oct_dev->ptp_enable = false;

	dev_info(&pdev->dev, "Initializing device %x:%x.\n",
		 (u32)pdev->venकरोr, (u32)pdev->device);

	/* Assign octeon_device क्रम this device to the निजी data area. */
	pci_set_drvdata(pdev, oct_dev);

	/* set linux specअगरic device poपूर्णांकer */
	oct_dev->pci_dev = (व्योम *)pdev;

	oct_dev->subप्रणाली_id = pdev->subप्रणाली_venकरोr |
		(pdev->subप्रणाली_device << 16);

	hs = &handshake[oct_dev->octeon_id];
	init_completion(&hs->init);
	init_completion(&hs->started);
	hs->pci_dev = pdev;

	अगर (oct_dev->octeon_id == 0)
		/* first LiquidIO NIC is detected */
		complete(&first_stage);

	अगर (octeon_device_init(oct_dev)) अणु
		complete(&hs->init);
		liquidio_हटाओ(pdev);
		वापस -ENOMEM;
	पूर्ण

	अगर (OCTEON_CN23XX_PF(oct_dev)) अणु
		u8 bus, device, function;

		अगर (atomic_पढ़ो(oct_dev->adapter_refcount) == 1) अणु
			/* Each NIC माला_लो one watchकरोg kernel thपढ़ो.  The first
			 * PF (of each NIC) that माला_लो pci_driver->probe()'d
			 * creates that thपढ़ो.
			 */
			bus = pdev->bus->number;
			device = PCI_SLOT(pdev->devfn);
			function = PCI_FUNC(pdev->devfn);
			oct_dev->watchकरोg_task = kthपढ़ो_create(
			    liquidio_watchकरोg, oct_dev,
			    "liowd/%02hhx:%02hhx.%hhx", bus, device, function);
			अगर (!IS_ERR(oct_dev->watchकरोg_task)) अणु
				wake_up_process(oct_dev->watchकरोg_task);
			पूर्ण अन्यथा अणु
				oct_dev->watchकरोg_task = शून्य;
				dev_err(&oct_dev->pci_dev->dev,
					"failed to create kernel_thread\n");
				liquidio_हटाओ(pdev);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	oct_dev->rx_छोड़ो = 1;
	oct_dev->tx_छोड़ो = 1;

	dev_dbg(&oct_dev->pci_dev->dev, "Device is ready\n");

	वापस 0;
पूर्ण

अटल bool fw_type_is_स्वतः(व्योम)
अणु
	वापस म_भेदन(fw_type, LIO_FW_NAME_TYPE_AUTO,
		       माप(LIO_FW_NAME_TYPE_AUTO)) == 0;
पूर्ण

/**
 * octeon_pci_flr - PCI FLR क्रम each Octeon device.
 * @oct: octeon device
 */
अटल व्योम octeon_pci_flr(काष्ठा octeon_device *oct)
अणु
	पूर्णांक rc;

	pci_save_state(oct->pci_dev);

	pci_cfg_access_lock(oct->pci_dev);

	/* Quiesce the device completely */
	pci_ग_लिखो_config_word(oct->pci_dev, PCI_COMMAND,
			      PCI_COMMAND_INTX_DISABLE);

	rc = __pci_reset_function_locked(oct->pci_dev);

	अगर (rc != 0)
		dev_err(&oct->pci_dev->dev, "Error %d resetting PCI function %d\n",
			rc, oct->pf_num);

	pci_cfg_access_unlock(oct->pci_dev);

	pci_restore_state(oct->pci_dev);
पूर्ण

/**
 * octeon_destroy_resources - Destroy resources associated with octeon device
 * @oct: octeon device
 */
अटल व्योम octeon_destroy_resources(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i, refcount;
	काष्ठा msix_entry *msix_entries;
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)oct->priv;

	काष्ठा handshake *hs;

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

	हाल OCT_DEV_CONSOLE_INIT_DONE:
		/* Remove any consoles */
		octeon_हटाओ_consoles(oct);

		fallthrough;
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
			क्रम (i = 0; i < oct->num_msix_irqs - 1; i++) अणु
				अगर (oct->ioq_vector[i].vector) अणु
					/* clear the affinity_cpumask */
					irq_set_affinity_hपूर्णांक(
							msix_entries[i].vector,
							शून्य);
					मुक्त_irq(msix_entries[i].vector,
						 &oct->ioq_vector[i]);
					oct->ioq_vector[i].vector = 0;
				पूर्ण
			पूर्ण
			/* non-iov vector's argument is oct काष्ठा */
			मुक्त_irq(msix_entries[i].vector, oct);

			pci_disable_msix(oct->pci_dev);
			kमुक्त(oct->msix_entries);
			oct->msix_entries = शून्य;
		पूर्ण अन्यथा अणु
			/* Release the पूर्णांकerrupt line */
			मुक्त_irq(oct->pci_dev->irq, oct);

			अगर (oct->flags & LIO_FLAG_MSI_ENABLED)
				pci_disable_msi(oct->pci_dev);
		पूर्ण

		kमुक्त(oct->irq_name_storage);
		oct->irq_name_storage = शून्य;

		fallthrough;
	हाल OCT_DEV_MSIX_ALLOC_VECTOR_DONE:
		अगर (OCTEON_CN23XX_PF(oct))
			octeon_मुक्त_ioq_vector(oct);

		fallthrough;
	हाल OCT_DEV_MBOX_SETUP_DONE:
		अगर (OCTEON_CN23XX_PF(oct))
			oct->fn_list.मुक्त_mbox(oct);

		fallthrough;
	हाल OCT_DEV_IN_RESET:
	हाल OCT_DEV_DROQ_INIT_DONE:
		/* Wait क्रम any pending operations */
		mdelay(100);
		क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) अणु
			अगर (!(oct->io_qmask.oq & BIT_ULL(i)))
				जारी;
			octeon_delete_droq(oct, i);
		पूर्ण

		/* Force any pending handshakes to complete */
		क्रम (i = 0; i < MAX_OCTEON_DEVICES; i++) अणु
			hs = &handshake[i];

			अगर (hs->pci_dev) अणु
				handshake[oct->octeon_id].init_ok = 0;
				complete(&handshake[oct->octeon_id].init);
				handshake[oct->octeon_id].started_ok = 0;
				complete(&handshake[oct->octeon_id].started);
			पूर्ण
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
#अगर_घोषित CONFIG_PCI_IOV
		अगर (oct->sriov_info.sriov_enabled)
			pci_disable_sriov(oct->pci_dev);
#पूर्ण_अगर
		fallthrough;
	हाल OCT_DEV_SC_BUFF_POOL_INIT_DONE:
		octeon_मुक्त_sc_buffer_pool(oct);

		fallthrough;
	हाल OCT_DEV_DISPATCH_INIT_DONE:
		octeon_delete_dispatch_list(oct);
		cancel_delayed_work_sync(&oct->nic_poll_work.work);

		fallthrough;
	हाल OCT_DEV_PCI_MAP_DONE:
		refcount = octeon_deरेजिस्टर_device(oct);

		/* Soft reset the octeon device beक्रमe निकासing.
		 * However, अगर fw was loaded from card (i.e. स्वतःboot),
		 * perक्रमm an FLR instead.
		 * Implementation note: only soft-reset the device
		 * अगर it is a CN6XXX OR the LAST CN23XX device.
		 */
		अगर (atomic_पढ़ो(oct->adapter_fw_state) == FW_IS_PRELOADED)
			octeon_pci_flr(oct);
		अन्यथा अगर (OCTEON_CN6XXX(oct) || !refcount)
			oct->fn_list.soft_reset(oct);

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
	पूर्ण                       /* end चयन (oct->status) */

	tasklet_समाप्त(&oct_priv->droq_tasklet);
पूर्ण

/**
 * send_rx_ctrl_cmd - Send Rx control command
 * @lio: per-network निजी data
 * @start_stop: whether to start or stop
 */
अटल पूर्णांक send_rx_ctrl_cmd(काष्ठा lio *lio, पूर्णांक start_stop)
अणु
	काष्ठा octeon_soft_command *sc;
	जोड़ octnet_cmd *ncmd;
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)lio->oct_dev;
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

		अगर (OCTEON_CN23XX_PF(oct))
			oct->droq[0]->ops.poll_mode = 0;
	पूर्ण

	/* Delete NAPI */
	list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
		netअगर_napi_del(napi);

	tasklet_enable(&oct_priv->droq_tasklet);

	अगर (atomic_पढ़ो(&lio->अगरstate) & LIO_IFSTATE_REGISTERED)
		unरेजिस्टर_netdev(netdev);

	cleanup_sync_octeon_समय_wq(netdev);
	cleanup_link_status_change_wq(netdev);

	cleanup_rx_oom_poll_fn(netdev);

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
	पूर्णांक i, j;
	काष्ठा lio *lio;

	dev_dbg(&oct->pci_dev->dev, "Stopping network interfaces\n");
	अगर (!oct->अगरcount) अणु
		dev_err(&oct->pci_dev->dev, "Init for Octeon was not completed\n");
		वापस 1;
	पूर्ण

	spin_lock_bh(&oct->cmd_resp_wqlock);
	oct->cmd_resp_state = OCT_DRV_OFFLINE;
	spin_unlock_bh(&oct->cmd_resp_wqlock);

	lio_vf_rep_destroy(oct);

	क्रम (i = 0; i < oct->अगरcount; i++) अणु
		lio = GET_LIO(oct->props[i].netdev);
		क्रम (j = 0; j < oct->num_oqs; j++)
			octeon_unरेजिस्टर_droq_ops(oct,
						   lio->linfo.rxpciq[j].s.q_no);
	पूर्ण

	क्रम (i = 0; i < oct->अगरcount; i++)
		liquidio_destroy_nic_device(oct, i);

	अगर (oct->devlink) अणु
		devlink_unरेजिस्टर(oct->devlink);
		devlink_मुक्त(oct->devlink);
		oct->devlink = शून्य;
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "Network interfaces stopped\n");
	वापस 0;
पूर्ण

/**
 * liquidio_हटाओ - Cleans up resources at unload समय
 * @pdev: PCI device काष्ठाure
 */
अटल व्योम liquidio_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा octeon_device *oct_dev = pci_get_drvdata(pdev);

	dev_dbg(&oct_dev->pci_dev->dev, "Stopping device\n");

	अगर (oct_dev->watchकरोg_task)
		kthपढ़ो_stop(oct_dev->watchकरोg_task);

	अगर (!oct_dev->octeon_id &&
	    oct_dev->fw_info.app_cap_flags & LIQUIDIO_SWITCHDEV_CAP)
		lio_vf_rep_modनिकास();

	अगर (oct_dev->app_mode && (oct_dev->app_mode == CVM_DRV_NIC_APP))
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
 * octeon_chip_specअगरic_setup - Identअगरy the Octeon device and to map the BAR address space
 * @oct: octeon device
 */
अटल पूर्णांक octeon_chip_specअगरic_setup(काष्ठा octeon_device *oct)
अणु
	u32 dev_id, rev_id;
	पूर्णांक ret = 1;

	pci_पढ़ो_config_dword(oct->pci_dev, 0, &dev_id);
	pci_पढ़ो_config_dword(oct->pci_dev, 8, &rev_id);
	oct->rev_id = rev_id & 0xff;

	चयन (dev_id) अणु
	हाल OCTEON_CN68XX_PCIID:
		oct->chip_id = OCTEON_CN68XX;
		ret = lio_setup_cn68xx_octeon_device(oct);
		अवरोध;

	हाल OCTEON_CN66XX_PCIID:
		oct->chip_id = OCTEON_CN66XX;
		ret = lio_setup_cn66xx_octeon_device(oct);
		अवरोध;

	हाल OCTEON_CN23XX_PCIID_PF:
		oct->chip_id = OCTEON_CN23XX_PF_VID;
		ret = setup_cn23xx_octeon_pf_device(oct);
		अगर (ret)
			अवरोध;
#अगर_घोषित CONFIG_PCI_IOV
		अगर (!ret)
			pci_sriov_set_totalvfs(oct->pci_dev,
					       oct->sriov_info.max_vfs);
#पूर्ण_अगर
		अवरोध;

	शेष:
		dev_err(&oct->pci_dev->dev, "Unknown device found (dev_id: %x)\n",
			dev_id);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * octeon_pci_os_setup - PCI initialization क्रम each Octeon device.
 * @oct: octeon device
 */
अटल पूर्णांक octeon_pci_os_setup(काष्ठा octeon_device *oct)
अणु
	/* setup PCI stuff first */
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
	काष्ठा sk_buff *skb;
	काष्ठा octnet_buf_मुक्त_info *finfo;
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
	काष्ठा sk_buff *skb;
	काष्ठा lio *lio;
	काष्ठा octnic_gather *g;
	पूर्णांक i, frags, iq;

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
	काष्ठा octeon_soft_command *sc;
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा sk_buff *skb;
	काष्ठा lio *lio;
	काष्ठा octnic_gather *g;
	पूर्णांक i, frags, iq;

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
 * liquidio_ptp_adjfreq - Adjust ptp frequency
 * @ptp: PTP घड़ी info
 * @ppb: how much to adjust by, in parts-per-billion
 */
अटल पूर्णांक liquidio_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा lio *lio = container_of(ptp, काष्ठा lio, ptp_info);
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)lio->oct_dev;
	u64 comp, delta;
	अचिन्हित दीर्घ flags;
	bool neg_adj = false;

	अगर (ppb < 0) अणु
		neg_adj = true;
		ppb = -ppb;
	पूर्ण

	/* The hardware adds the घड़ी compensation value to the
	 * PTP घड़ी on every coprocessor घड़ी cycle, so we
	 * compute the delta in terms of coprocessor घड़ीs.
	 */
	delta = (u64)ppb << 32;
	करो_भाग(delta, oct->coproc_घड़ी_rate);

	spin_lock_irqsave(&lio->ptp_lock, flags);
	comp = lio_pci_पढ़ोq(oct, CN6XXX_MIO_PTP_CLOCK_COMP);
	अगर (neg_adj)
		comp -= delta;
	अन्यथा
		comp += delta;
	lio_pci_ग_लिखोq(oct, comp, CN6XXX_MIO_PTP_CLOCK_COMP);
	spin_unlock_irqrestore(&lio->ptp_lock, flags);

	वापस 0;
पूर्ण

/**
 * liquidio_ptp_adjसमय - Adjust ptp समय
 * @ptp: PTP घड़ी info
 * @delta: how much to adjust by, in nanosecs
 */
अटल पूर्णांक liquidio_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lio *lio = container_of(ptp, काष्ठा lio, ptp_info);

	spin_lock_irqsave(&lio->ptp_lock, flags);
	lio->ptp_adjust += delta;
	spin_unlock_irqrestore(&lio->ptp_lock, flags);

	वापस 0;
पूर्ण

/**
 * liquidio_ptp_समय_लो - Get hardware घड़ी समय, including any adjusपंचांगent
 * @ptp: PTP घड़ी info
 * @ts: बारpec
 */
अटल पूर्णांक liquidio_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp,
				काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा lio *lio = container_of(ptp, काष्ठा lio, ptp_info);
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)lio->oct_dev;

	spin_lock_irqsave(&lio->ptp_lock, flags);
	ns = lio_pci_पढ़ोq(oct, CN6XXX_MIO_PTP_CLOCK_HI);
	ns += lio->ptp_adjust;
	spin_unlock_irqrestore(&lio->ptp_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

/**
 * liquidio_ptp_समय_रखो - Set hardware घड़ी समय. Reset adjusपंचांगent
 * @ptp: PTP घड़ी info
 * @ts: बारpec
 */
अटल पूर्णांक liquidio_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
				स्थिर काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा lio *lio = container_of(ptp, काष्ठा lio, ptp_info);
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)lio->oct_dev;

	ns = बारpec64_to_ns(ts);

	spin_lock_irqsave(&lio->ptp_lock, flags);
	lio_pci_ग_लिखोq(oct, ns, CN6XXX_MIO_PTP_CLOCK_HI);
	lio->ptp_adjust = 0;
	spin_unlock_irqrestore(&lio->ptp_lock, flags);

	वापस 0;
पूर्ण

/**
 * liquidio_ptp_enable - Check अगर PTP is enabled
 * @ptp: PTP घड़ी info
 * @rq: request
 * @on: is it on
 */
अटल पूर्णांक
liquidio_ptp_enable(काष्ठा ptp_घड़ी_info __maybe_unused *ptp,
		    काष्ठा ptp_घड़ी_request __maybe_unused *rq,
		    पूर्णांक __maybe_unused on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * oct_ptp_खोलो - Open PTP घड़ी source
 * @netdev: network device
 */
अटल व्योम oct_ptp_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)lio->oct_dev;

	spin_lock_init(&lio->ptp_lock);

	snम_लिखो(lio->ptp_info.name, 16, "%s", netdev->name);
	lio->ptp_info.owner = THIS_MODULE;
	lio->ptp_info.max_adj = 250000000;
	lio->ptp_info.n_alarm = 0;
	lio->ptp_info.n_ext_ts = 0;
	lio->ptp_info.n_per_out = 0;
	lio->ptp_info.pps = 0;
	lio->ptp_info.adjfreq = liquidio_ptp_adjfreq;
	lio->ptp_info.adjसमय = liquidio_ptp_adjसमय;
	lio->ptp_info.समय_लो64 = liquidio_ptp_समय_लो;
	lio->ptp_info.समय_रखो64 = liquidio_ptp_समय_रखो;
	lio->ptp_info.enable = liquidio_ptp_enable;

	lio->ptp_adjust = 0;

	lio->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&lio->ptp_info,
					     &oct->pci_dev->dev);

	अगर (IS_ERR(lio->ptp_घड़ी))
		lio->ptp_घड़ी = शून्य;
पूर्ण

/**
 * liquidio_ptp_init - Init PTP घड़ी
 * @oct: octeon device
 */
अटल व्योम liquidio_ptp_init(काष्ठा octeon_device *oct)
अणु
	u64 घड़ी_comp, cfg;

	घड़ी_comp = (u64)NSEC_PER_SEC << 32;
	करो_भाग(घड़ी_comp, oct->coproc_घड़ी_rate);
	lio_pci_ग_लिखोq(oct, घड़ी_comp, CN6XXX_MIO_PTP_CLOCK_COMP);

	/* Enable */
	cfg = lio_pci_पढ़ोq(oct, CN6XXX_MIO_PTP_CLOCK_CFG);
	lio_pci_ग_लिखोq(oct, cfg | 0x01, CN6XXX_MIO_PTP_CLOCK_CFG);
पूर्ण

/**
 * load_firmware - Load firmware to device
 * @oct: octeon device
 *
 * Maps device to firmware filename, requests firmware, and करोwnloads it
 */
अटल पूर्णांक load_firmware(काष्ठा octeon_device *oct)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा firmware *fw;
	अक्षर fw_name[LIO_MAX_FW_खाताNAME_LEN];
	अक्षर *पंचांगp_fw_type;

	अगर (fw_type_is_स्वतः()) अणु
		पंचांगp_fw_type = LIO_FW_NAME_TYPE_NIC;
		म_नकलन(fw_type, पंचांगp_fw_type, माप(fw_type));
	पूर्ण अन्यथा अणु
		पंचांगp_fw_type = fw_type;
	पूर्ण

	प्र_लिखो(fw_name, "%s%s%s_%s%s", LIO_FW_सूची, LIO_FW_BASE_NAME,
		octeon_get_conf(oct)->card_name, पंचांगp_fw_type,
		LIO_FW_NAME_SUFFIX);

	ret = request_firmware(&fw, fw_name, &oct->pci_dev->dev);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "Request firmware failed. Could not find file %s.\n",
			fw_name);
		release_firmware(fw);
		वापस ret;
	पूर्ण

	ret = octeon_करोwnload_firmware(oct, fw->data, fw->size);

	release_firmware(fw);

	वापस ret;
पूर्ण

/**
 * octnet_poll_check_txq_status - Poll routine क्रम checking transmit queue status
 * @work: work_काष्ठा data काष्ठाure
 */
अटल व्योम octnet_poll_check_txq_status(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा lio *lio = (काष्ठा lio *)wk->ctxptr;

	अगर (!अगरstate_check(lio, LIO_IFSTATE_RUNNING))
		वापस;

	check_txq_status(lio);
	queue_delayed_work(lio->txq_status_wq.wq,
			   &lio->txq_status_wq.wk.work, msecs_to_jअगरfies(1));
पूर्ण

/**
 * setup_tx_poll_fn - Sets up the txq poll check
 * @netdev: network device
 */
अटल अंतरभूत पूर्णांक setup_tx_poll_fn(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	lio->txq_status_wq.wq = alloc_workqueue("txq-status",
						WQ_MEM_RECLAIM, 0);
	अगर (!lio->txq_status_wq.wq) अणु
		dev_err(&oct->pci_dev->dev, "unable to create cavium txq status wq\n");
		वापस -1;
	पूर्ण
	INIT_DELAYED_WORK(&lio->txq_status_wq.wk.work,
			  octnet_poll_check_txq_status);
	lio->txq_status_wq.wk.ctxptr = lio;
	queue_delayed_work(lio->txq_status_wq.wq,
			   &lio->txq_status_wq.wk.work, msecs_to_jअगरfies(1));
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cleanup_tx_poll_fn(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	अगर (lio->txq_status_wq.wq) अणु
		cancel_delayed_work_sync(&lio->txq_status_wq.wk.work);
		destroy_workqueue(lio->txq_status_wq.wq);
	पूर्ण
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

	अगर (oct->props[lio->अगरidx].napi_enabled == 0) अणु
		tasklet_disable(&oct_priv->droq_tasklet);

		list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
			napi_enable(napi);

		oct->props[lio->अगरidx].napi_enabled = 1;

		अगर (OCTEON_CN23XX_PF(oct))
			oct->droq[0]->ops.poll_mode = 1;
	पूर्ण

	अगर (oct->ptp_enable)
		oct_ptp_खोलो(netdev);

	अगरstate_set(lio, LIO_IFSTATE_RUNNING);

	अगर (OCTEON_CN23XX_PF(oct)) अणु
		अगर (!oct->msix_on)
			अगर (setup_tx_poll_fn(netdev))
				वापस -1;
	पूर्ण अन्यथा अणु
		अगर (setup_tx_poll_fn(netdev))
			वापस -1;
	पूर्ण

	netअगर_tx_start_all_queues(netdev);

	/* Ready क्रम link status updates */
	lio->पूर्णांकf_खोलो = 1;

	netअगर_info(lio, अगरup, lio->netdev, "Interface Open, ready for traffic\n");

	/* tell Octeon to start क्रमwarding packets to host */
	ret = send_rx_ctrl_cmd(lio, 1);
	अगर (ret)
		वापस ret;

	/* start periodical statistics fetch */
	INIT_DELAYED_WORK(&lio->stats_wk.work, lio_fetch_stats);
	lio->stats_wk.ctxptr = lio;
	schedule_delayed_work(&lio->stats_wk.work, msecs_to_jअगरfies
					(LIQUIDIO_NDEV_STATS_POLL_TIME_MS));

	dev_info(&oct->pci_dev->dev, "%s interface is opened\n",
		 netdev->name);

	वापस ret;
पूर्ण

/**
 * liquidio_stop - Net device stop क्रम LiquidIO
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

	अगरstate_reset(lio, LIO_IFSTATE_RUNNING);

	/* Stop any link updates */
	lio->पूर्णांकf_खोलो = 0;

	stop_txqs(netdev);

	/* Inक्रमm that netअगर carrier is करोwn */
	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);

	lio->linfo.link.s.link_up = 0;
	lio->link_changes++;

	/* Tell Octeon that nic पूर्णांकerface is करोwn. */
	ret = send_rx_ctrl_cmd(lio, 0);
	अगर (ret)
		वापस ret;

	अगर (OCTEON_CN23XX_PF(oct)) अणु
		अगर (!oct->msix_on)
			cleanup_tx_poll_fn(netdev);
	पूर्ण अन्यथा अणु
		cleanup_tx_poll_fn(netdev);
	पूर्ण

	cancel_delayed_work_sync(&lio->stats_wk.work);

	अगर (lio->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(lio->ptp_घड़ी);
		lio->ptp_घड़ी = शून्य;
	पूर्ण

	/* Wait क्रम any pending Rx descriptors */
	अगर (lio_रुको_क्रम_clean_oq(oct))
		netअगर_info(lio, rx_err, lio->netdev,
			   "Proceeding with stop interface after partial RX desc processing\n");

	अगर (oct->props[lio->अगरidx].napi_enabled == 1) अणु
		list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
			napi_disable(napi);

		oct->props[lio->अगरidx].napi_enabled = 0;

		अगर (OCTEON_CN23XX_PF(oct))
			oct->droq[0]->ops.poll_mode = 0;

		tasklet_enable(&oct_priv->droq_tasklet);
	पूर्ण

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
अटल अंतरभूत क्रमागत octnet_अगरflags get_new_flags(काष्ठा net_device *netdev)
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

/**
 * liquidio_set_mcast_list - Net device set_multicast_list
 * @netdev: network device
 */
अटल व्योम liquidio_set_mcast_list(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	काष्ठा netdev_hw_addr *ha;
	u64 *mc;
	पूर्णांक ret;
	पूर्णांक mc_count = min(netdev_mc_count(netdev), MAX_OCTEON_MULTICAST_ADDR);

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	/* Create a ctrl pkt command to be sent to core app. */
	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_MULTI_LIST;
	nctrl.ncmd.s.param1 = get_new_flags(netdev);
	nctrl.ncmd.s.param2 = mc_count;
	nctrl.ncmd.s.more = mc_count;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	/* copy all the addresses पूर्णांकo the udd */
	mc = &nctrl.udd[0];
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		*mc = 0;
		स_नकल(((u8 *)mc) + 2, ha->addr, ETH_ALEN);
		/* no need to swap bytes */

		अगर (++mc > &nctrl.udd[mc_count])
			अवरोध;
	पूर्ण

	/* Apparently, any activity in this call from the kernel has to
	 * be atomic. So we won't रुको क्रम response.
	 */

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "DEVFLAGS change failed in core (ret: 0x%x)\n",
			ret);
	पूर्ण
पूर्ण

/**
 * liquidio_set_mac - Net device set_mac_address
 * @netdev: network device
 * @p: poपूर्णांकer to sockaddr
 */
अटल पूर्णांक liquidio_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	पूर्णांक ret = 0;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)p;
	काष्ठा octnic_ctrl_pkt nctrl;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_CHANGE_MACADDR;
	nctrl.ncmd.s.param1 = 0;
	nctrl.ncmd.s.more = 1;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;

	nctrl.udd[0] = 0;
	/* The MAC Address is presented in network byte order. */
	स_नकल((u8 *)&nctrl.udd[0] + 2, addr->sa_data, ETH_ALEN);

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret < 0) अणु
		dev_err(&oct->pci_dev->dev, "MAC Address change failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (nctrl.sc_status) अणु
		dev_err(&oct->pci_dev->dev,
			"%s: MAC Address change failed. sc return=%x\n",
			 __func__, nctrl.sc_status);
		वापस -EIO;
	पूर्ण

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(((u8 *)&lio->linfo.hw_addr) + 2, addr->sa_data, ETH_ALEN);

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
	lstats->collisions = oct->link_stats.fromhost.total_collisions;

	/* detailed rx_errors: */
	lstats->rx_length_errors = oct->link_stats.fromwire.l2_err;
	/* recved pkt with crc error    */
	lstats->rx_crc_errors = oct->link_stats.fromwire.fcs_err;
	/* recv'd frame alignment error */
	lstats->rx_frame_errors = oct->link_stats.fromwire.frame_err;
	/* recv'r fअगरo overrun */
	lstats->rx_fअगरo_errors = oct->link_stats.fromwire.fअगरo_err;

	lstats->rx_errors = lstats->rx_length_errors + lstats->rx_crc_errors +
		lstats->rx_frame_errors + lstats->rx_fअगरo_errors;

	/* detailed tx_errors */
	lstats->tx_पातed_errors = oct->link_stats.fromhost.fw_err_pko;
	lstats->tx_carrier_errors = oct->link_stats.fromhost.fw_err_link;
	lstats->tx_fअगरo_errors = oct->link_stats.fromhost.fअगरo_err;

	lstats->tx_errors = lstats->tx_पातed_errors +
		lstats->tx_carrier_errors +
		lstats->tx_fअगरo_errors;
पूर्ण

/**
 * hwtstamp_ioctl - Handler क्रम SIOCSHWTSTAMP ioctl
 * @netdev: network device
 * @अगरr: पूर्णांकerface request
 */
अटल पूर्णांक hwtstamp_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config conf;
	काष्ठा lio *lio = GET_LIO(netdev);

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
	काष्ठा lio *lio = GET_LIO(netdev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		अगर (lio->oct_dev->ptp_enable)
			वापस hwtstamp_ioctl(netdev, अगरr);
		fallthrough;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * handle_बारtamp - handle a Tx बारtamp response
 * @oct: octeon device
 * @status: response status
 * @buf: poपूर्णांकer to skb
 */
अटल व्योम handle_बारtamp(काष्ठा octeon_device *oct,
			     u32 status,
			     व्योम *buf)
अणु
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा octeon_soft_command *sc;
	काष्ठा oct_बारtamp_resp *resp;
	काष्ठा lio *lio;
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)buf;

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

	अगर (unlikely((skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS) != 0)) अणु
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

/**
 * send_nic_बारtamp_pkt - Send a data packet that will be बारtamped
 * @oct: octeon device
 * @ndata: poपूर्णांकer to network data
 * @finfo: poपूर्णांकer to निजी network data
 * @xmit_more: more is coming
 */
अटल अंतरभूत पूर्णांक send_nic_बारtamp_pkt(काष्ठा octeon_device *oct,
					 काष्ठा octnic_data_pkt *ndata,
					 काष्ठा octnet_buf_मुक्त_info *finfo,
					 पूर्णांक xmit_more)
अणु
	पूर्णांक retval;
	काष्ठा octeon_soft_command *sc;
	काष्ठा lio *lio;
	पूर्णांक ring_करोorbell;
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

	अगर (OCTEON_CN23XX_PF(oct))
		len = (u32)((काष्ठा octeon_instr_ih3 *)
			    (&sc->cmd.cmd3.ih3))->dlengsz;
	अन्यथा
		len = (u32)((काष्ठा octeon_instr_ih2 *)
			    (&sc->cmd.cmd2.ih2))->dlengsz;

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
 *
 * Return: whether the packet was transmitted to the device okay or not
 *             (NETDEV_TX_OK or NETDEV_TX_BUSY)
 */
अटल netdev_tx_t liquidio_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio;
	काष्ठा octnet_buf_मुक्त_info *finfo;
	जोड़ octnic_cmd_setup cmdsetup;
	काष्ठा octnic_data_pkt ndata;
	काष्ठा octeon_device *oct;
	काष्ठा oct_iq_stats *stats;
	काष्ठा octeon_instr_irh *irh;
	जोड़ tx_info *tx_info;
	पूर्णांक status = 0;
	पूर्णांक q_idx = 0, iq_no = 0;
	पूर्णांक j, xmit_more = 0;
	u64 dptr = 0;
	u32 tag = 0;

	lio = GET_LIO(netdev);
	oct = lio->oct_dev;

	q_idx = skb_iq(oct, skb);
	tag = q_idx;
	iq_no = lio->linfo.txpciq[q_idx].s.q_no;

	stats = &oct->instr_queue[iq_no]->stats;

	/* Check क्रम all conditions in which the current packet cannot be
	 * transmitted.
	 */
	अगर (!(atomic_पढ़ो(&lio->अगरstate) & LIO_IFSTATE_RUNNING) ||
	    (!lio->linfo.link.s.link_up) ||
	    (skb->len <= 0)) अणु
		netअगर_info(lio, tx_err, lio->netdev,
			   "Transmit failed link_status : %d\n",
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

	ndata.buf = (व्योम *)finfo;

	ndata.q_no = iq_no;

	अगर (octnet_iq_is_full(oct, ndata.q_no)) अणु
		/* defer sending अगर queue is full */
		netअगर_info(lio, tx_err, lio->netdev, "Transmit failed iq:%d full\n",
			   ndata.q_no);
		stats->tx_iq_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* pr_info(" XMIT - valid Qs: %d, 1st Q no: %d, cpu:  %d, q_no:%d\n",
	 *	lio->linfo.num_txpciq, lio->txq, cpu, ndata.q_no);
	 */

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

	अगर (skb_shinfo(skb)->nr_frags == 0) अणु
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
			stats->tx_dmamap_fail++;
			वापस NETDEV_TX_BUSY;
		पूर्ण

		अगर (OCTEON_CN23XX_PF(oct))
			ndata.cmd.cmd3.dptr = dptr;
		अन्यथा
			ndata.cmd.cmd2.dptr = dptr;
		finfo->dptr = dptr;
		ndata.reqtype = REQTYPE_NORESP_NET;

	पूर्ण अन्यथा अणु
		पूर्णांक i, frags;
		skb_frag_t *frag;
		काष्ठा octnic_gather *g;

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
			stats->tx_dmamap_fail++;
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

		अगर (OCTEON_CN23XX_PF(oct))
			ndata.cmd.cmd3.dptr = dptr;
		अन्यथा
			ndata.cmd.cmd2.dptr = dptr;
		finfo->dptr = dptr;
		finfo->g = g;

		ndata.reqtype = REQTYPE_NORESP_NET_SG;
	पूर्ण

	अगर (OCTEON_CN23XX_PF(oct)) अणु
		irh = (काष्ठा octeon_instr_irh *)&ndata.cmd.cmd3.irh;
		tx_info = (जोड़ tx_info *)&ndata.cmd.cmd3.ossp[0];
	पूर्ण अन्यथा अणु
		irh = (काष्ठा octeon_instr_irh *)&ndata.cmd.cmd2.irh;
		tx_info = (जोड़ tx_info *)&ndata.cmd.cmd2.ossp[0];
	पूर्ण

	अगर (skb_shinfo(skb)->gso_size) अणु
		tx_info->s.gso_size = skb_shinfo(skb)->gso_size;
		tx_info->s.gso_segs = skb_shinfo(skb)->gso_segs;
		stats->tx_gso++;
	पूर्ण

	/* HW insert VLAN tag */
	अगर (skb_vlan_tag_present(skb)) अणु
		irh->priority = skb_vlan_tag_get(skb) >> 13;
		irh->vlan = skb_vlan_tag_get(skb) & 0xfff;
	पूर्ण

	xmit_more = netdev_xmit_more();

	अगर (unlikely(cmdsetup.s.बारtamp))
		status = send_nic_बारtamp_pkt(oct, &ndata, finfo, xmit_more);
	अन्यथा
		status = octnet_send_nic_data_pkt(oct, &ndata, xmit_more);
	अगर (status == IQ_SEND_FAILED)
		जाओ lio_xmit_failed;

	netअगर_info(lio, tx_queued, lio->netdev, "Transmit queued successfully\n");

	अगर (status == IQ_SEND_STOP)
		netअगर_stop_subqueue(netdev, q_idx);

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
 * @netdev:    poपूर्णांकer to network device
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

अटल पूर्णांक liquidio_vlan_rx_add_vid(काष्ठा net_device *netdev,
				    __be16 proto __attribute__((unused)),
				    u16 vid)
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
		अगर (ret > 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक liquidio_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				     __be16 proto __attribute__((unused)),
				     u16 vid)
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

/**
 * liquidio_set_rxcsum_command - Sending command to enable/disable RX checksum offload
 * @netdev:                poपूर्णांकer to network device
 * @command:               OCTNET_CMD_TNL_RX_CSUM_CTL
 * @rx_cmd:                OCTNET_CMD_RXCSUM_ENABLE/OCTNET_CMD_RXCSUM_DISABLE
 * Returns:                SUCCESS or FAILURE
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
		dev_err(&oct->pci_dev->dev,
			"DEVFLAGS RXCSUM change failed in core(ret:0x%x)\n",
			ret);
		अगर (ret > 0)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * liquidio_vxlan_port_command - Sending command to add/delete VxLAN UDP port to firmware
 * @netdev:                poपूर्णांकer to network device
 * @command:               OCTNET_CMD_VXLAN_PORT_CONFIG
 * @vxlan_port:            VxLAN port to be added or deleted
 * @vxlan_cmd_bit:         OCTNET_CMD_VXLAN_PORT_ADD,
 *                              OCTNET_CMD_VXLAN_PORT_DEL
 * Return:                     SUCCESS or FAILURE
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
			"VxLAN port add/delete failed in core (ret:0x%x)\n",
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

/**
 * liquidio_fix_features - Net device fix features
 * @netdev:  poपूर्णांकer to network device
 * @request: features requested
 * Return: updated features list
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

	/*Disable LRO अगर RXCSUM is off */
	अगर (!(request & NETIF_F_RXCSUM) && (netdev->features & NETIF_F_LRO) &&
	    (lio->dev_capability & NETIF_F_LRO))
		request &= ~NETIF_F_LRO;

	अगर ((request & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    !(lio->dev_capability & NETIF_F_HW_VLAN_CTAG_FILTER))
		request &= ~NETIF_F_HW_VLAN_CTAG_FILTER;

	वापस request;
पूर्ण

/**
 * liquidio_set_features - Net device set features
 * @netdev:  poपूर्णांकer to network device
 * @features: features to enable/disable
 */
अटल पूर्णांक liquidio_set_features(काष्ठा net_device *netdev,
				 netdev_features_t features)
अणु
	काष्ठा lio *lio = netdev_priv(netdev);

	अगर ((features & NETIF_F_LRO) &&
	    (lio->dev_capability & NETIF_F_LRO) &&
	    !(netdev->features & NETIF_F_LRO))
		liquidio_set_feature(netdev, OCTNET_CMD_LRO_ENABLE,
				     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);
	अन्यथा अगर (!(features & NETIF_F_LRO) &&
		 (lio->dev_capability & NETIF_F_LRO) &&
		 (netdev->features & NETIF_F_LRO))
		liquidio_set_feature(netdev, OCTNET_CMD_LRO_DISABLE,
				     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);

	/* Sending command to firmware to enable/disable RX checksum
	 * offload settings using ethtool
	 */
	अगर (!(netdev->features & NETIF_F_RXCSUM) &&
	    (lio->enc_dev_capability & NETIF_F_RXCSUM) &&
	    (features & NETIF_F_RXCSUM))
		liquidio_set_rxcsum_command(netdev,
					    OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_ENABLE);
	अन्यथा अगर ((netdev->features & NETIF_F_RXCSUM) &&
		 (lio->enc_dev_capability & NETIF_F_RXCSUM) &&
		 !(features & NETIF_F_RXCSUM))
		liquidio_set_rxcsum_command(netdev, OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_DISABLE);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    (lio->dev_capability & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		liquidio_set_feature(netdev, OCTNET_CMD_VLAN_FILTER_CTL,
				     OCTNET_CMD_VLAN_FILTER_ENABLE);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
		 (lio->dev_capability & NETIF_F_HW_VLAN_CTAG_FILTER) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		liquidio_set_feature(netdev, OCTNET_CMD_VLAN_FILTER_CTL,
				     OCTNET_CMD_VLAN_FILTER_DISABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक __liquidio_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vfidx,
				 u8 *mac, bool is_admin_asचिन्हित)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	अगर (!is_valid_ether_addr(mac))
		वापस -EINVAL;

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.max_vfs)
		वापस -EINVAL;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_CHANGE_MACADDR;
	/* vfidx is 0 based, but vf_num (param1) is 1 based */
	nctrl.ncmd.s.param1 = vfidx + 1;
	nctrl.ncmd.s.more = 1;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	अगर (is_admin_asचिन्हित) अणु
		nctrl.ncmd.s.param2 = true;
		nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;
	पूर्ण

	nctrl.udd[0] = 0;
	/* The MAC Address is presented in network byte order. */
	ether_addr_copy((u8 *)&nctrl.udd[0] + 2, mac);

	oct->sriov_info.vf_macaddr[vfidx] = nctrl.udd[0];

	ret = octnet_send_nic_ctrl_pkt(oct, &nctrl);
	अगर (ret > 0)
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक liquidio_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vfidx, u8 *mac)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	पूर्णांक retval;

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		वापस -EINVAL;

	retval = __liquidio_set_vf_mac(netdev, vfidx, mac, true);
	अगर (!retval)
		cn23xx_tell_vf_its_macaddr_changed(oct, vfidx, mac);

	वापस retval;
पूर्ण

अटल पूर्णांक liquidio_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vfidx,
				    bool enable)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक retval;

	अगर (!(oct->fw_info.app_cap_flags & LIQUIDIO_SPOOFCHK_CAP)) अणु
		netअगर_info(lio, drv, lio->netdev,
			   "firmware does not support spoofchk\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced) अणु
		netअगर_info(lio, drv, lio->netdev, "Invalid vfidx %d\n", vfidx);
		वापस -EINVAL;
	पूर्ण

	अगर (enable) अणु
		अगर (oct->sriov_info.vf_spoofchk[vfidx])
			वापस 0;
	पूर्ण अन्यथा अणु
		/* Clear */
		अगर (!oct->sriov_info.vf_spoofchk[vfidx])
			वापस 0;
	पूर्ण

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));
	nctrl.ncmd.s.cmdgroup = OCTNET_CMD_GROUP1;
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_VF_SPOOFCHK;
	nctrl.ncmd.s.param1 =
		vfidx + 1; /* vfidx is 0 based,
			    * but vf_num (param1) is 1 based
			    */
	nctrl.ncmd.s.param2 = enable;
	nctrl.ncmd.s.more = 0;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.cb_fn = शून्य;

	retval = octnet_send_nic_ctrl_pkt(oct, &nctrl);

	अगर (retval) अणु
		netअगर_info(lio, drv, lio->netdev,
			   "Failed to set VF %d spoofchk %s\n", vfidx,
			enable ? "on" : "off");
		वापस -1;
	पूर्ण

	oct->sriov_info.vf_spoofchk[vfidx] = enable;
	netअगर_info(lio, drv, lio->netdev, "VF %u spoofchk is %s\n", vfidx,
		   enable ? "on" : "off");

	वापस 0;
पूर्ण

अटल पूर्णांक liquidio_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vfidx,
				u16 vlan, u8 qos, __be16 vlan_proto)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	u16 vlantci;
	पूर्णांक ret = 0;

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		वापस -EINVAL;

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	अगर (vlan >= VLAN_N_VID || qos > 7)
		वापस -EINVAL;

	अगर (vlan)
		vlantci = vlan | (u16)qos << VLAN_PRIO_SHIFT;
	अन्यथा
		vlantci = 0;

	अगर (oct->sriov_info.vf_vlantci[vfidx] == vlantci)
		वापस 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	अगर (vlan)
		nctrl.ncmd.s.cmd = OCTNET_CMD_ADD_VLAN_FILTER;
	अन्यथा
		nctrl.ncmd.s.cmd = OCTNET_CMD_DEL_VLAN_FILTER;

	nctrl.ncmd.s.param1 = vlantci;
	nctrl.ncmd.s.param2 =
	    vfidx + 1; /* vfidx is 0 based, but vf_num (param2) is 1 based */
	nctrl.ncmd.s.more = 0;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.cb_fn = शून्य;

	ret = octnet_send_nic_ctrl_pkt(oct, &nctrl);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -EIO;
		वापस ret;
	पूर्ण

	oct->sriov_info.vf_vlantci[vfidx] = vlantci;

	वापस ret;
पूर्ण

अटल पूर्णांक liquidio_get_vf_config(काष्ठा net_device *netdev, पूर्णांक vfidx,
				  काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	u8 *macaddr;

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		वापस -EINVAL;

	स_रखो(ivi, 0, माप(काष्ठा अगरla_vf_info));

	ivi->vf = vfidx;
	macaddr = 2 + (u8 *)&oct->sriov_info.vf_macaddr[vfidx];
	ether_addr_copy(&ivi->mac[0], macaddr);
	ivi->vlan = oct->sriov_info.vf_vlantci[vfidx] & VLAN_VID_MASK;
	ivi->qos = oct->sriov_info.vf_vlantci[vfidx] >> VLAN_PRIO_SHIFT;
	अगर (oct->sriov_info.trusted_vf.active &&
	    oct->sriov_info.trusted_vf.id == vfidx)
		ivi->trusted = true;
	अन्यथा
		ivi->trusted = false;
	ivi->linkstate = oct->sriov_info.vf_linkstate[vfidx];
	ivi->spoofchk = oct->sriov_info.vf_spoofchk[vfidx];
	ivi->max_tx_rate = lio->linfo.link.s.speed;
	ivi->min_tx_rate = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक liquidio_send_vf_trust_cmd(काष्ठा lio *lio, पूर्णांक vfidx, bool trusted)
अणु
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octeon_soft_command *sc;
	पूर्णांक retval;

	sc = octeon_alloc_soft_command(oct, 0, 16, 0);
	अगर (!sc)
		वापस -ENOMEM;

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	/* vfidx is 0 based, but vf_num (param1) is 1 based */
	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_SET_TRUSTED_VF, 0, vfidx + 1,
				    trusted);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		octeon_मुक्त_soft_command(oct, sc);
		retval = -1;
	पूर्ण अन्यथा अणु
		/* Wait क्रम response or समयout */
		retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
		अगर (retval)
			वापस (retval);

		WRITE_ONCE(sc->caller_is_करोne, true);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक liquidio_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vfidx,
				 bool setting)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	अगर (म_भेद(oct->fw_info.liquidio_firmware_version, "1.7.1") < 0) अणु
		/* trusted vf is not supported by firmware older than 1.7.1 */
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced) अणु
		netअगर_info(lio, drv, lio->netdev, "Invalid vfidx %d\n", vfidx);
		वापस -EINVAL;
	पूर्ण

	अगर (setting) अणु
		/* Set */

		अगर (oct->sriov_info.trusted_vf.active &&
		    oct->sriov_info.trusted_vf.id == vfidx)
			वापस 0;

		अगर (oct->sriov_info.trusted_vf.active) अणु
			netअगर_info(lio, drv, lio->netdev, "More than one trusted VF is not allowed\n");
			वापस -EPERM;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Clear */

		अगर (!oct->sriov_info.trusted_vf.active)
			वापस 0;
	पूर्ण

	अगर (!liquidio_send_vf_trust_cmd(lio, vfidx, setting)) अणु
		अगर (setting) अणु
			oct->sriov_info.trusted_vf.id = vfidx;
			oct->sriov_info.trusted_vf.active = true;
		पूर्ण अन्यथा अणु
			oct->sriov_info.trusted_vf.active = false;
		पूर्ण

		netअगर_info(lio, drv, lio->netdev, "VF %u is %strusted\n", vfidx,
			   setting ? "" : "not ");
	पूर्ण अन्यथा अणु
		netअगर_info(lio, drv, lio->netdev, "Failed to set VF trusted\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक liquidio_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vfidx,
				      पूर्णांक linkstate)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		वापस -EINVAL;

	अगर (oct->sriov_info.vf_linkstate[vfidx] == linkstate)
		वापस 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_VF_LINKSTATE;
	nctrl.ncmd.s.param1 =
	    vfidx + 1; /* vfidx is 0 based, but vf_num (param1) is 1 based */
	nctrl.ncmd.s.param2 = linkstate;
	nctrl.ncmd.s.more = 0;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.cb_fn = शून्य;

	ret = octnet_send_nic_ctrl_pkt(oct, &nctrl);

	अगर (!ret)
		oct->sriov_info.vf_linkstate[vfidx] = linkstate;
	अन्यथा अगर (ret > 0)
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक
liquidio_eचयन_mode_get(काष्ठा devlink *devlink, u16 *mode)
अणु
	काष्ठा lio_devlink_priv *priv;
	काष्ठा octeon_device *oct;

	priv = devlink_priv(devlink);
	oct = priv->oct;

	*mode = oct->eचयन_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक
liquidio_eचयन_mode_set(काष्ठा devlink *devlink, u16 mode,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा lio_devlink_priv *priv;
	काष्ठा octeon_device *oct;
	पूर्णांक ret = 0;

	priv = devlink_priv(devlink);
	oct = priv->oct;

	अगर (!(oct->fw_info.app_cap_flags & LIQUIDIO_SWITCHDEV_CAP))
		वापस -EINVAL;

	अगर (oct->eचयन_mode == mode)
		वापस 0;

	चयन (mode) अणु
	हाल DEVLINK_ESWITCH_MODE_SWITCHDEV:
		oct->eचयन_mode = mode;
		ret = lio_vf_rep_create(oct);
		अवरोध;

	हाल DEVLINK_ESWITCH_MODE_LEGACY:
		lio_vf_rep_destroy(oct);
		oct->eचयन_mode = mode;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा devlink_ops liquidio_devlink_ops = अणु
	.eचयन_mode_get = liquidio_eचयन_mode_get,
	.eचयन_mode_set = liquidio_eचयन_mode_set,
पूर्ण;

अटल पूर्णांक
liquidio_get_port_parent_id(काष्ठा net_device *dev,
			    काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा lio *lio = GET_LIO(dev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	अगर (oct->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस -EOPNOTSUPP;

	ppid->id_len = ETH_ALEN;
	ether_addr_copy(ppid->id, (व्योम *)&lio->linfo.hw_addr + 2);

	वापस 0;
पूर्ण

अटल पूर्णांक liquidio_get_vf_stats(काष्ठा net_device *netdev, पूर्णांक vfidx,
				 काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा oct_vf_stats stats;
	पूर्णांक ret;

	अगर (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		वापस -EINVAL;

	स_रखो(&stats, 0, माप(काष्ठा oct_vf_stats));
	ret = cn23xx_get_vf_stats(oct, vfidx, &stats);
	अगर (!ret) अणु
		vf_stats->rx_packets = stats.rx_packets;
		vf_stats->tx_packets = stats.tx_packets;
		vf_stats->rx_bytes = stats.rx_bytes;
		vf_stats->tx_bytes = stats.tx_bytes;
		vf_stats->broadcast = stats.broadcast;
		vf_stats->multicast = stats.multicast;
	पूर्ण

	वापस ret;
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
	.nकरो_set_vf_mac		= liquidio_set_vf_mac,
	.nकरो_set_vf_vlan	= liquidio_set_vf_vlan,
	.nकरो_get_vf_config	= liquidio_get_vf_config,
	.nकरो_set_vf_spoofchk	= liquidio_set_vf_spoofchk,
	.nकरो_set_vf_trust	= liquidio_set_vf_trust,
	.nकरो_set_vf_link_state  = liquidio_set_vf_link_state,
	.nकरो_get_vf_stats	= liquidio_get_vf_stats,
	.nकरो_get_port_parent_id	= liquidio_get_port_parent_id,
पूर्ण;

/**
 * liquidio_init - Entry poपूर्णांक क्रम the liquidio module
 */
अटल पूर्णांक __init liquidio_init(व्योम)
अणु
	पूर्णांक i;
	काष्ठा handshake *hs;

	init_completion(&first_stage);

	octeon_init_device_list(OCTEON_CONFIG_TYPE_DEFAULT);

	अगर (liquidio_init_pci())
		वापस -EINVAL;

	रुको_क्रम_completion_समयout(&first_stage, msecs_to_jअगरfies(1000));

	क्रम (i = 0; i < MAX_OCTEON_DEVICES; i++) अणु
		hs = &handshake[i];
		अगर (hs->pci_dev) अणु
			रुको_क्रम_completion(&hs->init);
			अगर (!hs->init_ok) अणु
				/* init handshake failed */
				dev_err(&hs->pci_dev->dev,
					"Failed to init device\n");
				liquidio_deinit_pci();
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_OCTEON_DEVICES; i++) अणु
		hs = &handshake[i];
		अगर (hs->pci_dev) अणु
			रुको_क्रम_completion_समयout(&hs->started,
						    msecs_to_jअगरfies(30000));
			अगर (!hs->started_ok) अणु
				/* starter handshake failed */
				dev_err(&hs->pci_dev->dev,
					"Firmware failed to start\n");
				liquidio_deinit_pci();
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lio_nic_info(काष्ठा octeon_recv_info *recv_info, व्योम *buf)
अणु
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)buf;
	काष्ठा octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	पूर्णांक gmxport = 0;
	जोड़ oct_link_status *ls;
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
	काष्ठा lio *lio = शून्य;
	काष्ठा net_device *netdev;
	u8 mac[6], i, j, *fw_ver, *micro_ver;
	अचिन्हित दीर्घ micro;
	u32 cur_ver;
	काष्ठा octeon_soft_command *sc;
	काष्ठा liquidio_अगर_cfg_resp *resp;
	काष्ठा octdev_props *props;
	पूर्णांक retval, num_iqueues, num_oqueues;
	पूर्णांक max_num_queues = 0;
	जोड़ oct_nic_अगर_cfg अगर_cfg;
	अचिन्हित पूर्णांक base_queue;
	अचिन्हित पूर्णांक gmx_port_id;
	u32 resp_size, data_size;
	u32 अगरidx_or_pfnum;
	काष्ठा lio_version *vdata;
	काष्ठा devlink *devlink;
	काष्ठा lio_devlink_priv *lio_devlink;

	/* This is to handle link status changes */
	octeon_रेजिस्टर_dispatch_fn(octeon_dev, OPCODE_NIC,
				    OPCODE_NIC_INFO,
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

		अगर (OCTEON_CN23XX_PF(octeon_dev)) अणु
			num_iqueues = octeon_dev->sriov_info.num_pf_rings;
			num_oqueues = octeon_dev->sriov_info.num_pf_rings;
			base_queue = octeon_dev->sriov_info.pf_srn;

			gmx_port_id = octeon_dev->pf_num;
			अगरidx_or_pfnum = octeon_dev->pf_num;
		पूर्ण अन्यथा अणु
			num_iqueues = CFG_GET_NUM_TXQS_NIC_IF(
						octeon_get_conf(octeon_dev), i);
			num_oqueues = CFG_GET_NUM_RXQS_NIC_IF(
						octeon_get_conf(octeon_dev), i);
			base_queue = CFG_GET_BASE_QUE_NIC_IF(
						octeon_get_conf(octeon_dev), i);
			gmx_port_id = CFG_GET_GMXID_NIC_IF(
						octeon_get_conf(octeon_dev), i);
			अगरidx_or_pfnum = i;
		पूर्ण

		dev_dbg(&octeon_dev->pci_dev->dev,
			"requesting config for interface %d, iqs %d, oqs %d\n",
			अगरidx_or_pfnum, num_iqueues, num_oqueues);

		अगर_cfg.u64 = 0;
		अगर_cfg.s.num_iqueues = num_iqueues;
		अगर_cfg.s.num_oqueues = num_oqueues;
		अगर_cfg.s.base_queue = base_queue;
		अगर_cfg.s.gmx_port_id = gmx_port_id;

		sc->iq_no = 0;

		octeon_prepare_soft_command(octeon_dev, sc, OPCODE_NIC,
					    OPCODE_NIC_IF_CFG, 0,
					    अगर_cfg.u64, 0);

		init_completion(&sc->complete);
		sc->sc_status = OCTEON_REQUEST_PENDING;

		retval = octeon_send_soft_command(octeon_dev, sc);
		अगर (retval == IQ_SEND_FAILED) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"iq/oq config failed status: %x\n",
				retval);
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
			dev_err(&octeon_dev->pci_dev->dev, "iq/oq config failed\n");
			WRITE_ONCE(sc->caller_is_करोne, true);
			जाओ setup_nic_dev_करोne;
		पूर्ण
		snम_लिखो(octeon_dev->fw_info.liquidio_firmware_version,
			 32, "%s",
			 resp->cfg_info.liquidio_firmware_version);

		/* Verअगरy f/w version (in हाल of 'auto' loading from flash) */
		fw_ver = octeon_dev->fw_info.liquidio_firmware_version;
		अगर (स_भेद(LIQUIDIO_BASE_VERSION,
			   fw_ver,
			   म_माप(LIQUIDIO_BASE_VERSION))) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"Unmatched firmware version. Expected %s.x, got %s.\n",
				LIQUIDIO_BASE_VERSION, fw_ver);
			WRITE_ONCE(sc->caller_is_करोne, true);
			जाओ setup_nic_dev_करोne;
		पूर्ण अन्यथा अगर (atomic_पढ़ो(octeon_dev->adapter_fw_state) ==
			   FW_IS_PRELOADED) अणु
			dev_info(&octeon_dev->pci_dev->dev,
				 "Using auto-loaded firmware version %s.\n",
				 fw_ver);
		पूर्ण

		/* extract micro version field; poपूर्णांक past '<maj>.<min>.' */
		micro_ver = fw_ver + म_माप(LIQUIDIO_BASE_VERSION) + 1;
		अगर (kम_से_अदीर्घ(micro_ver, 10, &micro) != 0)
			micro = 0;
		octeon_dev->fw_info.ver.maj = LIQUIDIO_BASE_MAJOR_VERSION;
		octeon_dev->fw_info.ver.min = LIQUIDIO_BASE_MINOR_VERSION;
		octeon_dev->fw_info.ver.rev = micro;

		octeon_swap_8B_data((u64 *)(&resp->cfg_info),
				    (माप(काष्ठा liquidio_अगर_cfg_info)) >> 3);

		num_iqueues = hweight64(resp->cfg_info.iqmask);
		num_oqueues = hweight64(resp->cfg_info.oqmask);

		अगर (!(num_iqueues) || !(num_oqueues)) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"Got bad iqueues (%016llx) or oqueues (%016llx) from firmware.\n",
				resp->cfg_info.iqmask,
				resp->cfg_info.oqmask);
			WRITE_ONCE(sc->caller_is_करोne, true);
			जाओ setup_nic_dev_करोne;
		पूर्ण

		अगर (OCTEON_CN6XXX(octeon_dev)) अणु
			max_num_queues = CFG_GET_IQ_MAX_Q(CHIP_CONF(octeon_dev,
								    cn6xxx));
		पूर्ण अन्यथा अगर (OCTEON_CN23XX_PF(octeon_dev)) अणु
			max_num_queues = CFG_GET_IQ_MAX_Q(CHIP_CONF(octeon_dev,
								    cn23xx_pf));
		पूर्ण

		dev_dbg(&octeon_dev->pci_dev->dev,
			"interface %d, iqmask %016llx, oqmask %016llx, numiqueues %d, numoqueues %d max_num_queues: %d\n",
			i, resp->cfg_info.iqmask, resp->cfg_info.oqmask,
			num_iqueues, num_oqueues, max_num_queues);
		netdev = alloc_etherdev_mq(LIO_SIZE, max_num_queues);

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

		retval = netअगर_set_real_num_rx_queues(netdev, num_oqueues);
		अगर (retval) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"setting real number rx failed\n");
			WRITE_ONCE(sc->caller_is_करोne, true);
			जाओ setup_nic_dev_मुक्त;
		पूर्ण

		retval = netअगर_set_real_num_tx_queues(netdev, num_iqueues);
		अगर (retval) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"setting real number tx failed\n");
			WRITE_ONCE(sc->caller_is_करोne, true);
			जाओ setup_nic_dev_मुक्त;
		पूर्ण

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

		WRITE_ONCE(sc->caller_is_करोne, true);

		lio->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

		अगर (OCTEON_CN23XX_PF(octeon_dev) ||
		    OCTEON_CN6XXX(octeon_dev)) अणु
			lio->dev_capability = NETIF_F_HIGHDMA
					      | NETIF_F_IP_CSUM
					      | NETIF_F_IPV6_CSUM
					      | NETIF_F_SG | NETIF_F_RXCSUM
					      | NETIF_F_GRO
					      | NETIF_F_TSO | NETIF_F_TSO6
					      | NETIF_F_LRO;
		पूर्ण
		netअगर_set_gso_max_size(netdev, OCTNIC_GSO_MAX_SIZE);

		/*  Copy of transmit encapsulation capabilities:
		 *  TSO, TSO6, Checksums क्रम this device
		 */
		lio->enc_dev_capability = NETIF_F_IP_CSUM
					  | NETIF_F_IPV6_CSUM
					  | NETIF_F_GSO_UDP_TUNNEL
					  | NETIF_F_HW_CSUM | NETIF_F_SG
					  | NETIF_F_RXCSUM
					  | NETIF_F_TSO | NETIF_F_TSO6
					  | NETIF_F_LRO;

		netdev->hw_enc_features = (lio->enc_dev_capability &
					   ~NETIF_F_LRO);

		netdev->udp_tunnel_nic_info = &liquidio_udp_tunnels;

		lio->dev_capability |= NETIF_F_GSO_UDP_TUNNEL;

		netdev->vlan_features = lio->dev_capability;
		/* Add any unchangeable hw features */
		lio->dev_capability |=  NETIF_F_HW_VLAN_CTAG_FILTER |
					NETIF_F_HW_VLAN_CTAG_RX |
					NETIF_F_HW_VLAN_CTAG_TX;

		netdev->features = (lio->dev_capability & ~NETIF_F_LRO);

		netdev->hw_features = lio->dev_capability;
		/*HW_VLAN_RX and HW_VLAN_FILTER is always on*/
		netdev->hw_features = netdev->hw_features &
			~NETIF_F_HW_VLAN_CTAG_RX;

		/* MTU range: 68 - 16000 */
		netdev->min_mtu = LIO_MIN_MTU_SIZE;
		netdev->max_mtu = LIO_MAX_MTU_SIZE;

		/* Poपूर्णांक to the  properties क्रम octeon device to which this
		 * पूर्णांकerface beदीर्घs.
		 */
		lio->oct_dev = octeon_dev;
		lio->octprops = props;
		lio->netdev = netdev;

		dev_dbg(&octeon_dev->pci_dev->dev,
			"if%d gmx: %d hw_addr: 0x%llx\n", i,
			lio->linfo.gmxport, CVM_CAST64(lio->linfo.hw_addr));

		क्रम (j = 0; j < octeon_dev->sriov_info.max_vfs; j++) अणु
			u8 vfmac[ETH_ALEN];

			eth_अक्रमom_addr(vfmac);
			अगर (__liquidio_set_vf_mac(netdev, j, vfmac, false)) अणु
				dev_err(&octeon_dev->pci_dev->dev,
					"Error setting VF%d MAC address\n",
					j);
				जाओ setup_nic_dev_मुक्त;
			पूर्ण
		पूर्ण

		/* 64-bit swap required on LE machines */
		octeon_swap_8B_data(&lio->linfo.hw_addr, 1);
		क्रम (j = 0; j < 6; j++)
			mac[j] = *((u8 *)(((u8 *)&lio->linfo.hw_addr) + 2 + j));

		/* Copy MAC Address to OS network device काष्ठाure */

		ether_addr_copy(netdev->dev_addr, mac);

		/* By शेष all पूर्णांकerfaces on a single Octeon uses the same
		 * tx and rx queues
		 */
		lio->txq = lio->linfo.txpciq[0].s.q_no;
		lio->rxq = lio->linfo.rxpciq[0].s.q_no;
		अगर (liquidio_setup_io_queues(octeon_dev, i,
					     lio->linfo.num_txpciq,
					     lio->linfo.num_rxpciq)) अणु
			dev_err(&octeon_dev->pci_dev->dev, "I/O queues creation failed\n");
			जाओ setup_nic_dev_मुक्त;
		पूर्ण

		अगरstate_set(lio, LIO_IFSTATE_DROQ_OPS);

		lio->tx_qsize = octeon_get_tx_qsize(octeon_dev, lio->txq);
		lio->rx_qsize = octeon_get_rx_qsize(octeon_dev, lio->rxq);

		अगर (lio_setup_glists(octeon_dev, lio, num_iqueues)) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"Gather list allocation failed\n");
			जाओ setup_nic_dev_मुक्त;
		पूर्ण

		/* Register ethtool support */
		liquidio_set_ethtool_ops(netdev);
		अगर (lio->oct_dev->chip_id == OCTEON_CN23XX_PF_VID)
			octeon_dev->priv_flags = OCT_PRIV_FLAG_DEFAULT;
		अन्यथा
			octeon_dev->priv_flags = 0x0;

		अगर (netdev->features & NETIF_F_LRO)
			liquidio_set_feature(netdev, OCTNET_CMD_LRO_ENABLE,
					     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);

		liquidio_set_feature(netdev, OCTNET_CMD_VLAN_FILTER_CTL,
				     OCTNET_CMD_VLAN_FILTER_ENABLE);

		अगर ((debug != -1) && (debug & NETIF_MSG_HW))
			liquidio_set_feature(netdev,
					     OCTNET_CMD_VERBOSE_ENABLE, 0);

		अगर (setup_link_status_change_wq(netdev))
			जाओ setup_nic_dev_मुक्त;

		अगर ((octeon_dev->fw_info.app_cap_flags &
		     LIQUIDIO_TIME_SYNC_CAP) &&
		    setup_sync_octeon_समय_wq(netdev))
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

		अगर (octeon_dev->subप्रणाली_id ==
			OCTEON_CN2350_25GB_SUBSYS_ID ||
		    octeon_dev->subप्रणाली_id ==
			OCTEON_CN2360_25GB_SUBSYS_ID) अणु
			cur_ver = OCT_FW_VER(octeon_dev->fw_info.ver.maj,
					     octeon_dev->fw_info.ver.min,
					     octeon_dev->fw_info.ver.rev);

			/* speed control unsupported in f/w older than 1.7.2 */
			अगर (cur_ver < OCT_FW_VER(1, 7, 2)) अणु
				dev_info(&octeon_dev->pci_dev->dev,
					 "speed setting not supported by f/w.");
				octeon_dev->speed_setting = 25;
				octeon_dev->no_speed_setting = 1;
			पूर्ण अन्यथा अणु
				liquidio_get_speed(lio);
			पूर्ण

			अगर (octeon_dev->speed_setting == 0) अणु
				octeon_dev->speed_setting = 25;
				octeon_dev->no_speed_setting = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			octeon_dev->no_speed_setting = 1;
			octeon_dev->speed_setting = 10;
		पूर्ण
		octeon_dev->speed_boot = octeon_dev->speed_setting;

		/* करोn't पढ़ो FEC setting अगर unsupported by f/w (see above) */
		अगर (octeon_dev->speed_boot == 25 &&
		    !octeon_dev->no_speed_setting) अणु
			liquidio_get_fec(lio);
			octeon_dev->props[lio->अगरidx].fec_boot =
				octeon_dev->props[lio->अगरidx].fec;
		पूर्ण
	पूर्ण

	devlink = devlink_alloc(&liquidio_devlink_ops,
				माप(काष्ठा lio_devlink_priv));
	अगर (!devlink) अणु
		dev_err(&octeon_dev->pci_dev->dev, "devlink alloc failed\n");
		जाओ setup_nic_dev_मुक्त;
	पूर्ण

	lio_devlink = devlink_priv(devlink);
	lio_devlink->oct = octeon_dev;

	अगर (devlink_रेजिस्टर(devlink, &octeon_dev->pci_dev->dev)) अणु
		devlink_मुक्त(devlink);
		dev_err(&octeon_dev->pci_dev->dev,
			"devlink registration failed\n");
		जाओ setup_nic_dev_मुक्त;
	पूर्ण

	octeon_dev->devlink = devlink;
	octeon_dev->eचयन_mode = DEVLINK_ESWITCH_MODE_LEGACY;

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

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक octeon_enable_sriov(काष्ठा octeon_device *oct)
अणु
	अचिन्हित पूर्णांक num_vfs_alloced = oct->sriov_info.num_vfs_alloced;
	काष्ठा pci_dev *vfdev;
	पूर्णांक err;
	u32 u;

	अगर (OCTEON_CN23XX_PF(oct) && num_vfs_alloced) अणु
		err = pci_enable_sriov(oct->pci_dev,
				       oct->sriov_info.num_vfs_alloced);
		अगर (err) अणु
			dev_err(&oct->pci_dev->dev,
				"OCTEON: Failed to enable PCI sriov: %d\n",
				err);
			oct->sriov_info.num_vfs_alloced = 0;
			वापस err;
		पूर्ण
		oct->sriov_info.sriov_enabled = 1;

		/* init lookup table that maps DPI ring number to VF pci_dev
		 * काष्ठा poपूर्णांकer
		 */
		u = 0;
		vfdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
				       OCTEON_CN23XX_VF_VID, शून्य);
		जबतक (vfdev) अणु
			अगर (vfdev->is_virtfn &&
			    (vfdev->physfn == oct->pci_dev)) अणु
				oct->sriov_info.dpiring_to_vfpcidev_lut[u] =
					vfdev;
				u += oct->sriov_info.rings_per_vf;
			पूर्ण
			vfdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
					       OCTEON_CN23XX_VF_VID, vfdev);
		पूर्ण
	पूर्ण

	वापस num_vfs_alloced;
पूर्ण

अटल पूर्णांक lio_pci_sriov_disable(काष्ठा octeon_device *oct)
अणु
	पूर्णांक u;

	अगर (pci_vfs_asचिन्हित(oct->pci_dev)) अणु
		dev_err(&oct->pci_dev->dev, "VFs are still assigned to VMs.\n");
		वापस -EPERM;
	पूर्ण

	pci_disable_sriov(oct->pci_dev);

	u = 0;
	जबतक (u < MAX_POSSIBLE_VFS) अणु
		oct->sriov_info.dpiring_to_vfpcidev_lut[u] = शून्य;
		u += oct->sriov_info.rings_per_vf;
	पूर्ण

	oct->sriov_info.num_vfs_alloced = 0;
	dev_info(&oct->pci_dev->dev, "oct->pf_num:%d disabled VFs\n",
		 oct->pf_num);

	वापस 0;
पूर्ण

अटल पूर्णांक liquidio_enable_sriov(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
	काष्ठा octeon_device *oct = pci_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर ((num_vfs == oct->sriov_info.num_vfs_alloced) &&
	    (oct->sriov_info.sriov_enabled)) अणु
		dev_info(&oct->pci_dev->dev, "oct->pf_num:%d already enabled num_vfs:%d\n",
			 oct->pf_num, num_vfs);
		वापस 0;
	पूर्ण

	अगर (!num_vfs) अणु
		lio_vf_rep_destroy(oct);
		ret = lio_pci_sriov_disable(oct);
	पूर्ण अन्यथा अगर (num_vfs > oct->sriov_info.max_vfs) अणु
		dev_err(&oct->pci_dev->dev,
			"OCTEON: Max allowed VFs:%d user requested:%d",
			oct->sriov_info.max_vfs, num_vfs);
		ret = -EPERM;
	पूर्ण अन्यथा अणु
		oct->sriov_info.num_vfs_alloced = num_vfs;
		ret = octeon_enable_sriov(oct);
		dev_info(&oct->pci_dev->dev, "oct->pf_num:%d num_vfs:%d\n",
			 oct->pf_num, num_vfs);
		ret = lio_vf_rep_create(oct);
		अगर (ret)
			dev_info(&oct->pci_dev->dev,
				 "vf representor create failed");
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

/**
 * liquidio_init_nic_module - initialize the NIC
 * @oct: octeon device
 *
 * This initialization routine is called once the Octeon device application is
 * up and running
 */
अटल पूर्णांक liquidio_init_nic_module(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i, retval = 0;
	पूर्णांक num_nic_ports = CFG_GET_NUM_NIC_PORTS(octeon_get_conf(oct));

	dev_dbg(&oct->pci_dev->dev, "Initializing network interfaces\n");

	/* only शेष iq and oq were initialized
	 * initialize the rest as well
	 */
	/* run port_config command क्रम each port */
	oct->अगरcount = num_nic_ports;

	स_रखो(oct->props, 0, माप(काष्ठा octdev_props) * num_nic_ports);

	क्रम (i = 0; i < MAX_OCTEON_LINKS; i++)
		oct->props[i].gmxport = -1;

	retval = setup_nic_devices(oct);
	अगर (retval) अणु
		dev_err(&oct->pci_dev->dev, "Setup NIC devices failed\n");
		जाओ octnet_init_failure;
	पूर्ण

	/* Call vf_rep_modinit अगर the firmware is चयनdev capable
	 * and करो it from the first liquidio function probed.
	 */
	अगर (!oct->octeon_id &&
	    oct->fw_info.app_cap_flags & LIQUIDIO_SWITCHDEV_CAP) अणु
		retval = lio_vf_rep_modinit();
		अगर (retval) अणु
			liquidio_stop_nic_module(oct);
			जाओ octnet_init_failure;
		पूर्ण
	पूर्ण

	liquidio_ptp_init(oct);

	dev_dbg(&oct->pci_dev->dev, "Network interfaces ready\n");

	वापस retval;

octnet_init_failure:

	oct->अगरcount = 0;

	वापस retval;
पूर्ण

/**
 * nic_starter - finish init
 * @work:  work काष्ठा work_काष्ठा
 *
 * starter callback that invokes the reमुख्यing initialization work after the NIC is up and running.
 */
अटल व्योम nic_starter(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा octeon_device *oct;
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;

	oct = (काष्ठा octeon_device *)wk->ctxptr;

	अगर (atomic_पढ़ो(&oct->status) == OCT_DEV_RUNNING)
		वापस;

	/* If the status of the device is CORE_OK, the core
	 * application has reported its application type. Call
	 * any रेजिस्टरed handlers now and move to the RUNNING
	 * state.
	 */
	अगर (atomic_पढ़ो(&oct->status) != OCT_DEV_CORE_OK) अणु
		schedule_delayed_work(&oct->nic_poll_work.work,
				      LIQUIDIO_STARTER_POLL_INTERVAL_MS);
		वापस;
	पूर्ण

	atomic_set(&oct->status, OCT_DEV_RUNNING);

	अगर (oct->app_mode && oct->app_mode == CVM_DRV_NIC_APP) अणु
		dev_dbg(&oct->pci_dev->dev, "Starting NIC module\n");

		अगर (liquidio_init_nic_module(oct))
			dev_err(&oct->pci_dev->dev, "NIC initialization failed\n");
		अन्यथा
			handshake[oct->octeon_id].started_ok = 1;
	पूर्ण अन्यथा अणु
		dev_err(&oct->pci_dev->dev,
			"Unexpected application running on NIC (%d). Check firmware.\n",
			oct->app_mode);
	पूर्ण

	complete(&handshake[oct->octeon_id].started);
पूर्ण

अटल पूर्णांक
octeon_recv_vf_drv_notice(काष्ठा octeon_recv_info *recv_info, व्योम *buf)
अणु
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)buf;
	काष्ठा octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	पूर्णांक i, notice, vf_idx;
	bool cores_crashed;
	u64 *data, vf_num;

	notice = recv_pkt->rh.r.ossp;
	data = (u64 *)(get_rbd(recv_pkt->buffer_ptr[0]) + OCT_DROQ_INFO_SIZE);

	/* the first 64-bit word of data is the vf_num */
	vf_num = data[0];
	octeon_swap_8B_data(&vf_num, 1);
	vf_idx = (पूर्णांक)vf_num - 1;

	cores_crashed = READ_ONCE(oct->cores_crashed);

	अगर (notice == VF_DRV_LOADED) अणु
		अगर (!(oct->sriov_info.vf_drv_loaded_mask & BIT_ULL(vf_idx))) अणु
			oct->sriov_info.vf_drv_loaded_mask |= BIT_ULL(vf_idx);
			dev_info(&oct->pci_dev->dev,
				 "driver for VF%d was loaded\n", vf_idx);
			अगर (!cores_crashed)
				try_module_get(THIS_MODULE);
		पूर्ण
	पूर्ण अन्यथा अगर (notice == VF_DRV_REMOVED) अणु
		अगर (oct->sriov_info.vf_drv_loaded_mask & BIT_ULL(vf_idx)) अणु
			oct->sriov_info.vf_drv_loaded_mask &= ~BIT_ULL(vf_idx);
			dev_info(&oct->pci_dev->dev,
				 "driver for VF%d was removed\n", vf_idx);
			अगर (!cores_crashed)
				module_put(THIS_MODULE);
		पूर्ण
	पूर्ण अन्यथा अगर (notice == VF_DRV_MACADDR_CHANGED) अणु
		u8 *b = (u8 *)&data[1];

		oct->sriov_info.vf_macaddr[vf_idx] = data[1];
		dev_info(&oct->pci_dev->dev,
			 "VF driver changed VF%d's MAC address to %pM\n",
			 vf_idx, b + 2);
	पूर्ण

	क्रम (i = 0; i < recv_pkt->buffer_count; i++)
		recv_buffer_मुक्त(recv_pkt->buffer_ptr[i]);
	octeon_मुक्त_recv_info(recv_info);

	वापस 0;
पूर्ण

/**
 * octeon_device_init - Device initialization क्रम each Octeon device that is probed
 * @octeon_dev:  octeon device
 */
अटल पूर्णांक octeon_device_init(काष्ठा octeon_device *octeon_dev)
अणु
	पूर्णांक j, ret;
	अक्षर bootcmd[] = "\n";
	अक्षर *dbg_enb = शून्य;
	क्रमागत lio_fw_state fw_state;
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)octeon_dev->priv;
	atomic_set(&octeon_dev->status, OCT_DEV_BEGIN_STATE);

	/* Enable access to the octeon device and make its DMA capability
	 * known to the OS.
	 */
	अगर (octeon_pci_os_setup(octeon_dev))
		वापस 1;

	atomic_set(&octeon_dev->status, OCT_DEV_PCI_ENABLE_DONE);

	/* Identअगरy the Octeon type and map the BAR address space. */
	अगर (octeon_chip_specअगरic_setup(octeon_dev)) अणु
		dev_err(&octeon_dev->pci_dev->dev, "Chip specific setup failed\n");
		वापस 1;
	पूर्ण

	atomic_set(&octeon_dev->status, OCT_DEV_PCI_MAP_DONE);

	/* Only add a reference after setting status 'OCT_DEV_PCI_MAP_DONE',
	 * since that is what is required क्रम the reference to be हटाओd
	 * during de-initialization (see 'octeon_destroy_resources').
	 */
	octeon_रेजिस्टर_device(octeon_dev, octeon_dev->pci_dev->bus->number,
			       PCI_SLOT(octeon_dev->pci_dev->devfn),
			       PCI_FUNC(octeon_dev->pci_dev->devfn),
			       true);

	octeon_dev->app_mode = CVM_DRV_INVALID_APP;

	/* CN23XX supports preloaded firmware अगर the following is true:
	 *
	 * The adapter indicates that firmware is currently running AND
	 * 'fw_type' is 'auto'.
	 *
	 * (शेष state is NEEDS_TO_BE_LOADED, override it अगर appropriate).
	 */
	अगर (OCTEON_CN23XX_PF(octeon_dev) &&
	    cn23xx_fw_loaded(octeon_dev) && fw_type_is_स्वतः()) अणु
		atomic_cmpxchg(octeon_dev->adapter_fw_state,
			       FW_NEEDS_TO_BE_LOADED, FW_IS_PRELOADED);
	पूर्ण

	/* If loading firmware, only first device of adapter needs to करो so. */
	fw_state = atomic_cmpxchg(octeon_dev->adapter_fw_state,
				  FW_NEEDS_TO_BE_LOADED,
				  FW_IS_BEING_LOADED);

	/* Here, [local variable] 'fw_state' is set to one of:
	 *
	 *   FW_IS_PRELOADED:       No firmware is to be loaded (see above)
	 *   FW_NEEDS_TO_BE_LOADED: The driver's first instance will load
	 *                          firmware to the adapter.
	 *   FW_IS_BEING_LOADED:    The driver's second instance will not load
	 *                          firmware to the adapter.
	 */

	/* Prior to f/w load, perक्रमm a soft reset of the Octeon device;
	 * अगर error resetting, वापस w/error.
	 */
	अगर (fw_state == FW_NEEDS_TO_BE_LOADED)
		अगर (octeon_dev->fn_list.soft_reset(octeon_dev))
			वापस 1;

	/* Initialize the dispatch mechanism used to push packets arriving on
	 * Octeon Output queues.
	 */
	अगर (octeon_init_dispatch_list(octeon_dev))
		वापस 1;

	octeon_रेजिस्टर_dispatch_fn(octeon_dev, OPCODE_NIC,
				    OPCODE_NIC_CORE_DRV_ACTIVE,
				    octeon_core_drv_init,
				    octeon_dev);

	octeon_रेजिस्टर_dispatch_fn(octeon_dev, OPCODE_NIC,
				    OPCODE_NIC_VF_DRV_NOTICE,
				    octeon_recv_vf_drv_notice, octeon_dev);
	INIT_DELAYED_WORK(&octeon_dev->nic_poll_work.work, nic_starter);
	octeon_dev->nic_poll_work.ctxptr = (व्योम *)octeon_dev;
	schedule_delayed_work(&octeon_dev->nic_poll_work.work,
			      LIQUIDIO_STARTER_POLL_INTERVAL_MS);

	atomic_set(&octeon_dev->status, OCT_DEV_DISPATCH_INIT_DONE);

	अगर (octeon_set_io_queues_off(octeon_dev)) अणु
		dev_err(&octeon_dev->pci_dev->dev, "setting io queues off failed\n");
		वापस 1;
	पूर्ण

	अगर (OCTEON_CN23XX_PF(octeon_dev)) अणु
		ret = octeon_dev->fn_list.setup_device_regs(octeon_dev);
		अगर (ret) अणु
			dev_err(&octeon_dev->pci_dev->dev, "OCTEON: Failed to configure device registers\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Initialize soft command buffer pool
	 */
	अगर (octeon_setup_sc_buffer_pool(octeon_dev)) अणु
		dev_err(&octeon_dev->pci_dev->dev, "sc buffer pool allocation failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&octeon_dev->status, OCT_DEV_SC_BUFF_POOL_INIT_DONE);

	/*  Setup the data काष्ठाures that manage this Octeon's Input queues. */
	अगर (octeon_setup_instr_queues(octeon_dev)) अणु
		dev_err(&octeon_dev->pci_dev->dev,
			"instruction queue initialization failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&octeon_dev->status, OCT_DEV_INSTR_QUEUE_INIT_DONE);

	/* Initialize lists to manage the requests of dअगरferent types that
	 * arrive from user & kernel applications क्रम this octeon device.
	 */
	अगर (octeon_setup_response_list(octeon_dev)) अणु
		dev_err(&octeon_dev->pci_dev->dev, "Response list allocation failed\n");
		वापस 1;
	पूर्ण
	atomic_set(&octeon_dev->status, OCT_DEV_RESP_LIST_INIT_DONE);

	अगर (octeon_setup_output_queues(octeon_dev)) अणु
		dev_err(&octeon_dev->pci_dev->dev, "Output queue initialization failed\n");
		वापस 1;
	पूर्ण

	atomic_set(&octeon_dev->status, OCT_DEV_DROQ_INIT_DONE);

	अगर (OCTEON_CN23XX_PF(octeon_dev)) अणु
		अगर (octeon_dev->fn_list.setup_mbox(octeon_dev)) अणु
			dev_err(&octeon_dev->pci_dev->dev, "OCTEON: Mailbox setup failed\n");
			वापस 1;
		पूर्ण
		atomic_set(&octeon_dev->status, OCT_DEV_MBOX_SETUP_DONE);

		अगर (octeon_allocate_ioq_vector
				(octeon_dev,
				 octeon_dev->sriov_info.num_pf_rings)) अणु
			dev_err(&octeon_dev->pci_dev->dev, "OCTEON: ioq vector allocation failed\n");
			वापस 1;
		पूर्ण
		atomic_set(&octeon_dev->status, OCT_DEV_MSIX_ALLOC_VECTOR_DONE);

	पूर्ण अन्यथा अणु
		/* The input and output queue रेजिस्टरs were setup earlier (the
		 * queues were not enabled). Any additional रेजिस्टरs
		 * that need to be programmed should be करोne now.
		 */
		ret = octeon_dev->fn_list.setup_device_regs(octeon_dev);
		अगर (ret) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"Failed to configure device registers\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Initialize the tasklet that handles output queue packet processing.*/
	dev_dbg(&octeon_dev->pci_dev->dev, "Initializing droq tasklet\n");
	tasklet_setup(&oct_priv->droq_tasklet, octeon_droq_bh);

	/* Setup the पूर्णांकerrupt handler and record the INT SUM रेजिस्टर address
	 */
	अगर (octeon_setup_पूर्णांकerrupt(octeon_dev,
				   octeon_dev->sriov_info.num_pf_rings))
		वापस 1;

	/* Enable Octeon device पूर्णांकerrupts */
	octeon_dev->fn_list.enable_पूर्णांकerrupt(octeon_dev, OCTEON_ALL_INTR);

	atomic_set(&octeon_dev->status, OCT_DEV_INTR_SET_DONE);

	/* Send Credit क्रम Octeon Output queues. Credits are always sent BEFORE
	 * the output queue is enabled.
	 * This ensures that we'll receive the f/w CORE DRV_ACTIVE message in
	 * हाल we've configured CN23XX_SLI_GBL_CONTROL[NOPTR_D] = 0.
	 * Otherwise, it is possible that the DRV_ACTIVE message will be sent
	 * beक्रमe any credits have been issued, causing the ring to be reset
	 * (and the f/w appear to never have started).
	 */
	क्रम (j = 0; j < octeon_dev->num_oqs; j++)
		ग_लिखोl(octeon_dev->droq[j]->max_count,
		       octeon_dev->droq[j]->pkts_credit_reg);

	/* Enable the input and output queues क्रम this Octeon device */
	ret = octeon_dev->fn_list.enable_io_queues(octeon_dev);
	अगर (ret) अणु
		dev_err(&octeon_dev->pci_dev->dev, "Failed to enable input/output queues");
		वापस ret;
	पूर्ण

	atomic_set(&octeon_dev->status, OCT_DEV_IO_QUEUES_DONE);

	अगर (fw_state == FW_NEEDS_TO_BE_LOADED) अणु
		dev_dbg(&octeon_dev->pci_dev->dev, "Waiting for DDR initialization...\n");
		अगर (!ddr_समयout) अणु
			dev_info(&octeon_dev->pci_dev->dev,
				 "WAITING. Set ddr_timeout to non-zero value to proceed with initialization.\n");
		पूर्ण

		schedule_समयout_unपूर्णांकerruptible(HZ * LIO_RESET_SECS);

		/* Wait क्रम the octeon to initialize DDR after the soft-reset.*/
		जबतक (!ddr_समयout) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			अगर (schedule_समयout(HZ / 10)) अणु
				/* user probably pressed Control-C */
				वापस 1;
			पूर्ण
		पूर्ण
		ret = octeon_रुको_क्रम_ddr_init(octeon_dev, &ddr_समयout);
		अगर (ret) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"DDR not initialized. Please confirm that board is configured to boot from Flash, ret: %d\n",
				ret);
			वापस 1;
		पूर्ण

		अगर (octeon_रुको_क्रम_bootloader(octeon_dev, 1000)) अणु
			dev_err(&octeon_dev->pci_dev->dev, "Board not responding\n");
			वापस 1;
		पूर्ण

		/* Divert uboot to take commands from host instead. */
		ret = octeon_console_send_cmd(octeon_dev, bootcmd, 50);

		dev_dbg(&octeon_dev->pci_dev->dev, "Initializing consoles\n");
		ret = octeon_init_consoles(octeon_dev);
		अगर (ret) अणु
			dev_err(&octeon_dev->pci_dev->dev, "Could not access board consoles\n");
			वापस 1;
		पूर्ण
		/* If console debug enabled, specअगरy empty string to use शेष
		 * enablement ELSE specअगरy शून्य string क्रम 'disabled'.
		 */
		dbg_enb = octeon_console_debug_enabled(0) ? "" : शून्य;
		ret = octeon_add_console(octeon_dev, 0, dbg_enb);
		अगर (ret) अणु
			dev_err(&octeon_dev->pci_dev->dev, "Could not access board console\n");
			वापस 1;
		पूर्ण अन्यथा अगर (octeon_console_debug_enabled(0)) अणु
			/* If console was added AND we're logging console output
			 * then set our console prपूर्णांक function.
			 */
			octeon_dev->console[0].prपूर्णांक = octeon_dbg_console_prपूर्णांक;
		पूर्ण

		atomic_set(&octeon_dev->status, OCT_DEV_CONSOLE_INIT_DONE);

		dev_dbg(&octeon_dev->pci_dev->dev, "Loading firmware\n");
		ret = load_firmware(octeon_dev);
		अगर (ret) अणु
			dev_err(&octeon_dev->pci_dev->dev, "Could not load firmware to board\n");
			वापस 1;
		पूर्ण

		atomic_set(octeon_dev->adapter_fw_state, FW_HAS_BEEN_LOADED);
	पूर्ण

	handshake[octeon_dev->octeon_id].init_ok = 1;
	complete(&handshake[octeon_dev->octeon_id].init);

	atomic_set(&octeon_dev->status, OCT_DEV_HOST_OK);
	oct_priv->dev = octeon_dev;

	वापस 0;
पूर्ण

/**
 * octeon_dbg_console_prपूर्णांक - Debug console prपूर्णांक function
 * @oct:  octeon device
 * @console_num: console number
 * @prefix:      first portion of line to display
 * @suffix:      second portion of line to display
 *
 * The OCTEON debug console outमाला_दो entire lines (excluding '\n').
 * Normally, the line will be passed in the 'prefix' parameter.
 * However, due to buffering, it is possible क्रम a line to be split पूर्णांकo two
 * parts, in which हाल they will be passed as the 'prefix' parameter and
 * 'suffix' parameter.
 */
अटल पूर्णांक octeon_dbg_console_prपूर्णांक(काष्ठा octeon_device *oct, u32 console_num,
				    अक्षर *prefix, अक्षर *suffix)
अणु
	अगर (prefix && suffix)
		dev_info(&oct->pci_dev->dev, "%u: %s%s\n", console_num, prefix,
			 suffix);
	अन्यथा अगर (prefix)
		dev_info(&oct->pci_dev->dev, "%u: %s\n", console_num, prefix);
	अन्यथा अगर (suffix)
		dev_info(&oct->pci_dev->dev, "%u: %s\n", console_num, suffix);

	वापस 0;
पूर्ण

/**
 * liquidio_निकास - Exits the module
 */
अटल व्योम __निकास liquidio_निकास(व्योम)
अणु
	liquidio_deinit_pci();

	pr_info("LiquidIO network module is now unloaded\n");
पूर्ण

module_init(liquidio_init);
module_निकास(liquidio_निकास);
