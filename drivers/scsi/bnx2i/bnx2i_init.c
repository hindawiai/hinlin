<शैली गुरु>
/* bnx2i.c: QLogic NetXtreme II iSCSI driver.
 *
 * Copyright (c) 2006 - 2013 Broadcom Corporation
 * Copyright (c) 2007, 2008 Red Hat, Inc.  All rights reserved.
 * Copyright (c) 2007, 2008 Mike Christie
 * Copyright (c) 2014, QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Anil Veerabhadrappa (anilgv@broadcom.com)
 * Previously Maपूर्णांकained by: Eddie Wai (eddie.wai@broadcom.com)
 * Maपूर्णांकained by: QLogic-Storage-Upstream@qlogic.com
 */

#समावेश "bnx2i.h"

अटल काष्ठा list_head adapter_list = LIST_HEAD_INIT(adapter_list);
अटल u32 adapter_count;

#घोषणा DRV_MODULE_NAME		"bnx2i"
#घोषणा DRV_MODULE_VERSION	"2.7.10.1"
#घोषणा DRV_MODULE_RELDATE	"Jul 16, 2014"

अटल अक्षर version[] =
		"QLogic NetXtreme II iSCSI Driver " DRV_MODULE_NAME \
		" v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";


MODULE_AUTHOR("Anil Veerabhadrappa <anilgv@broadcom.com> and "
	      "Eddie Wai <eddie.wai@broadcom.com>");

MODULE_DESCRIPTION("QLogic NetXtreme II BCM5706/5708/5709/57710/57711/57712"
		   "/57800/57810/57840 iSCSI Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

अटल DEFINE_MUTEX(bnx2i_dev_lock);

अचिन्हित पूर्णांक event_coal_min = 24;
module_param(event_coal_min, पूर्णांक, 0664);
MODULE_PARM_DESC(event_coal_min, "Event Coalescing Minimum Commands");

अचिन्हित पूर्णांक event_coal_भाग = 2;
module_param(event_coal_भाग, पूर्णांक, 0664);
MODULE_PARM_DESC(event_coal_भाग, "Event Coalescing Divide Factor");

अचिन्हित पूर्णांक en_tcp_dack = 1;
module_param(en_tcp_dack, पूर्णांक, 0664);
MODULE_PARM_DESC(en_tcp_dack, "Enable TCP Delayed ACK");

अचिन्हित पूर्णांक error_mask1 = 0x00;
module_param(error_mask1, uपूर्णांक, 0664);
MODULE_PARM_DESC(error_mask1, "Config FW iSCSI Error Mask #1");

अचिन्हित पूर्णांक error_mask2 = 0x00;
module_param(error_mask2, uपूर्णांक, 0664);
MODULE_PARM_DESC(error_mask2, "Config FW iSCSI Error Mask #2");

अचिन्हित पूर्णांक sq_size;
module_param(sq_size, पूर्णांक, 0664);
MODULE_PARM_DESC(sq_size, "Configure SQ size");

अचिन्हित पूर्णांक rq_size = BNX2I_RQ_WQES_DEFAULT;
module_param(rq_size, पूर्णांक, 0664);
MODULE_PARM_DESC(rq_size, "Configure RQ size");

u64 iscsi_error_mask = 0x00;

DEFINE_PER_CPU(काष्ठा bnx2i_percpu_s, bnx2i_percpu);

/**
 * bnx2i_identअगरy_device - identअगरies NetXtreme II device type
 * @hba: 		Adapter काष्ठाure poपूर्णांकer
 * @dev:		Corresponding cnic device
 *
 * This function identअगरies the NX2 device type and sets appropriate
 *	queue mailbox रेजिस्टर access method, 5709 requires driver to
 *	access MBOX regs using *bin* mode
 */
व्योम bnx2i_identअगरy_device(काष्ठा bnx2i_hba *hba, काष्ठा cnic_dev *dev)
अणु
	hba->cnic_dev_type = 0;
	अगर (test_bit(CNIC_F_BNX2_CLASS, &dev->flags)) अणु
		अगर (hba->pci_did == PCI_DEVICE_ID_NX2_5706 ||
		    hba->pci_did == PCI_DEVICE_ID_NX2_5706S) अणु
			set_bit(BNX2I_NX2_DEV_5706, &hba->cnic_dev_type);
		पूर्ण अन्यथा अगर (hba->pci_did == PCI_DEVICE_ID_NX2_5708 ||
		    hba->pci_did == PCI_DEVICE_ID_NX2_5708S) अणु
			set_bit(BNX2I_NX2_DEV_5708, &hba->cnic_dev_type);
		पूर्ण अन्यथा अगर (hba->pci_did == PCI_DEVICE_ID_NX2_5709 ||
		    hba->pci_did == PCI_DEVICE_ID_NX2_5709S) अणु
			set_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type);
			hba->mail_queue_access = BNX2I_MQ_BIN_MODE;
		पूर्ण
	पूर्ण अन्यथा अगर (test_bit(CNIC_F_BNX2X_CLASS, &dev->flags)) अणु
		set_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: unknown device, 0x%x\n",
				  hba->pci_did);
	पूर्ण
पूर्ण


/**
 * get_adapter_list_head - वापसs head of adapter list
 */
काष्ठा bnx2i_hba *get_adapter_list_head(व्योम)
अणु
	काष्ठा bnx2i_hba *hba = शून्य;
	काष्ठा bnx2i_hba *पंचांगp_hba;

	अगर (!adapter_count)
		जाओ hba_not_found;

	mutex_lock(&bnx2i_dev_lock);
	list_क्रम_each_entry(पंचांगp_hba, &adapter_list, link) अणु
		अगर (पंचांगp_hba->cnic && पंचांगp_hba->cnic->cm_select_dev) अणु
			hba = पंचांगp_hba;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&bnx2i_dev_lock);
hba_not_found:
	वापस hba;
पूर्ण


/**
 * bnx2i_find_hba_क्रम_cnic - maps cnic device instance to bnx2i adapter instance
 * @cnic:	poपूर्णांकer to cnic device instance
 *
 */
काष्ठा bnx2i_hba *bnx2i_find_hba_क्रम_cnic(काष्ठा cnic_dev *cnic)
अणु
	काष्ठा bnx2i_hba *hba, *temp;

	mutex_lock(&bnx2i_dev_lock);
	list_क्रम_each_entry_safe(hba, temp, &adapter_list, link) अणु
		अगर (hba->cnic == cnic) अणु
			mutex_unlock(&bnx2i_dev_lock);
			वापस hba;
		पूर्ण
	पूर्ण
	mutex_unlock(&bnx2i_dev_lock);
	वापस शून्य;
पूर्ण


/**
 * bnx2i_start - cnic callback to initialize & start adapter instance
 * @handle:	transparent handle poपूर्णांकing to adapter काष्ठाure
 *
 * This function maps adapter काष्ठाure to pcidev काष्ठाure and initiates
 *	firmware handshake to enable/initialize on chip iscsi components
 * 	This bnx2i - cnic पूर्णांकerface api callback is issued after following
 *	2 conditions are met -
 *	  a) underlying network पूर्णांकerface is up (marked by event 'NETDEV_UP'
 *		from netdev
 *	  b) bnx2i adapter instance is रेजिस्टरed
 */
व्योम bnx2i_start(व्योम *handle)
अणु
#घोषणा BNX2I_INIT_POLL_TIME	(1000 / HZ)
	काष्ठा bnx2i_hba *hba = handle;
	पूर्णांक i = HZ;

	/* On some bnx2x devices, it is possible that iSCSI is no
	 * दीर्घer supported after firmware is करोwnloaded.  In that
	 * हाल, the iscsi_init_msg will वापस failure.
	 */

	bnx2i_send_fw_iscsi_init_msg(hba);
	जबतक (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state) &&
	       !test_bit(ADAPTER_STATE_INIT_FAILED, &hba->adapter_state) && i--)
		msleep(BNX2I_INIT_POLL_TIME);
पूर्ण


/**
 * bnx2i_chip_cleanup - local routine to handle chip cleanup
 * @hba:	Adapter instance to रेजिस्टर
 *
 * Driver checks अगर adapter still has any active connections beक्रमe
 *	executing the cleanup process
 */
अटल व्योम bnx2i_chip_cleanup(काष्ठा bnx2i_hba *hba)
अणु
	काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep;
	काष्ठा list_head *pos, *पंचांगp;

	अगर (hba->ofld_conns_active) अणु
		/* Stage to क्रमce the disconnection
		 * This is the हाल where the daemon is either slow or
		 * not present
		 */
		prपूर्णांकk(KERN_ALERT "bnx2i: (%s) chip cleanup for %d active "
			"connections\n", hba->netdev->name,
			hba->ofld_conns_active);
		mutex_lock(&hba->net_dev_lock);
		list_क्रम_each_safe(pos, पंचांगp, &hba->ep_active_list) अणु
			bnx2i_ep = list_entry(pos, काष्ठा bnx2i_endpoपूर्णांक, link);
			/* Clean up the chip only */
			bnx2i_hw_ep_disconnect(bnx2i_ep);
			bnx2i_ep->cm_sk = शून्य;
		पूर्ण
		mutex_unlock(&hba->net_dev_lock);
	पूर्ण
पूर्ण


/**
 * bnx2i_stop - cnic callback to shutकरोwn adapter instance
 * @handle:	transparent handle poपूर्णांकing to adapter काष्ठाure
 *
 * driver checks अगर adapter is alपढ़ोy in shutकरोwn mode, अगर not start
 *	the shutकरोwn process
 */
व्योम bnx2i_stop(व्योम *handle)
अणु
	काष्ठा bnx2i_hba *hba = handle;
	पूर्णांक conns_active;
	पूर्णांक रुको_delay = 1 * HZ;

	/* check अगर cleanup happened in GOING_DOWN context */
	अगर (!test_and_set_bit(ADAPTER_STATE_GOING_DOWN,
			      &hba->adapter_state)) अणु
		iscsi_host_क्रम_each_session(hba->shost,
					    bnx2i_drop_session);
		रुको_delay = hba->hba_shutकरोwn_पंचांगo;
	पूर्ण
	/* Wait क्रम inflight offload connection tasks to complete beक्रमe
	 * proceeding. Forcefully terminate all connection recovery in
	 * progress at the earliest, either in bind(), send_pdu(LOGIN),
	 * or conn_start()
	 */
	रुको_event_पूर्णांकerruptible_समयout(hba->eh_रुको,
					 (list_empty(&hba->ep_ofld_list) &&
					 list_empty(&hba->ep_destroy_list)),
					 2 * HZ);
	/* Wait क्रम all endpoपूर्णांकs to be torn करोwn, Chip will be reset once
	 *  control वापसs to network driver. So it is required to cleanup and
	 * release all connection resources beक्रमe वापसing from this routine.
	 */
	जबतक (hba->ofld_conns_active) अणु
		conns_active = hba->ofld_conns_active;
		रुको_event_पूर्णांकerruptible_समयout(hba->eh_रुको,
				(hba->ofld_conns_active != conns_active),
				रुको_delay);
		अगर (hba->ofld_conns_active == conns_active)
			अवरोध;
	पूर्ण
	bnx2i_chip_cleanup(hba);

	/* This flag should be cleared last so that ep_disconnect() gracefully
	 * cleans up connection context
	 */
	clear_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
	clear_bit(ADAPTER_STATE_UP, &hba->adapter_state);
पूर्ण


/**
 * bnx2i_init_one - initialize an adapter instance and allocate memory resources
 * @hba:	bnx2i adapter instance
 * @cnic:	cnic device handle
 *
 * Global resource lock is held during critical sections below. This routine is
 *	called from either cnic_रेजिस्टर_driver() or device hot plug context and
 *	and करोes majority of device specअगरic initialization
 */
अटल पूर्णांक bnx2i_init_one(काष्ठा bnx2i_hba *hba, काष्ठा cnic_dev *cnic)
अणु
	पूर्णांक rc;

	mutex_lock(&bnx2i_dev_lock);
	अगर (!cnic->max_iscsi_conn) अणु
		prपूर्णांकk(KERN_ALERT "bnx2i: dev %s does not support "
			"iSCSI\n", hba->netdev->name);
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	hba->cnic = cnic;
	rc = cnic->रेजिस्टर_device(cnic, CNIC_ULP_ISCSI, hba);
	अगर (!rc) अणु
		hba->age++;
		set_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic);
		list_add_tail(&hba->link, &adapter_list);
		adapter_count++;
	पूर्ण अन्यथा अगर (rc == -EBUSY) 	/* duplicate registration */
		prपूर्णांकk(KERN_ALERT "bnx2i, duplicate registration"
				  "hba=%p, cnic=%p\n", hba, cnic);
	अन्यथा अगर (rc == -EAGAIN)
		prपूर्णांकk(KERN_ERR "bnx2i, driver not registered\n");
	अन्यथा अगर (rc == -EINVAL)
		prपूर्णांकk(KERN_ERR "bnx2i, invalid type %d\n", CNIC_ULP_ISCSI);
	अन्यथा
		prपूर्णांकk(KERN_ERR "bnx2i dev reg, unknown error, %d\n", rc);

out:
	mutex_unlock(&bnx2i_dev_lock);

	वापस rc;
पूर्ण


/**
 * bnx2i_ulp_init - initialize an adapter instance
 * @dev:	cnic device handle
 *
 * Called from cnic_रेजिस्टर_driver() context to initialize all क्रमागतerated
 *	cnic devices. This routine allocate adapter काष्ठाure and other
 *	device specअगरic resources.
 */
व्योम bnx2i_ulp_init(काष्ठा cnic_dev *dev)
अणु
	काष्ठा bnx2i_hba *hba;

	/* Allocate a HBA काष्ठाure क्रम this device */
	hba = bnx2i_alloc_hba(dev);
	अगर (!hba) अणु
		prपूर्णांकk(KERN_ERR "bnx2i init: hba initialization failed\n");
		वापस;
	पूर्ण

	/* Get PCI related inक्रमmation and update hba काष्ठा members */
	clear_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic);
	अगर (bnx2i_init_one(hba, dev)) अणु
		prपूर्णांकk(KERN_ERR "bnx2i - hba %p init failed\n", hba);
		bnx2i_मुक्त_hba(hba);
	पूर्ण
पूर्ण


/**
 * bnx2i_ulp_निकास - shuts करोwn adapter instance and मुक्तs all resources
 * @dev:	cnic device handle
 *
 */
व्योम bnx2i_ulp_निकास(काष्ठा cnic_dev *dev)
अणु
	काष्ठा bnx2i_hba *hba;

	hba = bnx2i_find_hba_क्रम_cnic(dev);
	अगर (!hba) अणु
		prपूर्णांकk(KERN_INFO "bnx2i_ulp_exit: hba not "
				 "found, dev 0x%p\n", dev);
		वापस;
	पूर्ण
	mutex_lock(&bnx2i_dev_lock);
	list_del_init(&hba->link);
	adapter_count--;

	अगर (test_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic)) अणु
		hba->cnic->unरेजिस्टर_device(hba->cnic, CNIC_ULP_ISCSI);
		clear_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic);
	पूर्ण
	mutex_unlock(&bnx2i_dev_lock);

	bnx2i_मुक्त_hba(hba);
पूर्ण


/**
 * bnx2i_get_stats - Retrieve various statistic from iSCSI offload
 * @handle:	bnx2i_hba
 *
 * function callback exported via bnx2i - cnic driver पूर्णांकerface to
 *      retrieve various iSCSI offload related statistics.
 */
पूर्णांक bnx2i_get_stats(व्योम *handle)
अणु
	काष्ठा bnx2i_hba *hba = handle;
	काष्ठा iscsi_stats_info *stats;

	अगर (!hba)
		वापस -EINVAL;

	stats = (काष्ठा iscsi_stats_info *)hba->cnic->stats_addr;

	अगर (!stats)
		वापस -ENOMEM;

	strlcpy(stats->version, DRV_MODULE_VERSION, माप(stats->version));
	स_नकल(stats->mac_add1 + 2, hba->cnic->mac_addr, ETH_ALEN);

	stats->max_frame_size = hba->netdev->mtu;
	stats->txq_size = hba->max_sqes;
	stats->rxq_size = hba->max_cqes;

	stats->txq_avg_depth = 0;
	stats->rxq_avg_depth = 0;

	GET_STATS_64(hba, stats, rx_pdus);
	GET_STATS_64(hba, stats, rx_bytes);

	GET_STATS_64(hba, stats, tx_pdus);
	GET_STATS_64(hba, stats, tx_bytes);

	वापस 0;
पूर्ण


/**
 * bnx2i_cpu_online - Create a receive thपढ़ो क्रम an online CPU
 *
 * @cpu:	cpu index क्रम the online cpu
 */
अटल पूर्णांक bnx2i_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा bnx2i_percpu_s *p;
	काष्ठा task_काष्ठा *thपढ़ो;

	p = &per_cpu(bnx2i_percpu, cpu);

	thपढ़ो = kthपढ़ो_create_on_node(bnx2i_percpu_io_thपढ़ो, (व्योम *)p,
					cpu_to_node(cpu),
					"bnx2i_thread/%d", cpu);
	अगर (IS_ERR(thपढ़ो))
		वापस PTR_ERR(thपढ़ो);

	/* bind thपढ़ो to the cpu */
	kthपढ़ो_bind(thपढ़ो, cpu);
	p->iothपढ़ो = thपढ़ो;
	wake_up_process(thपढ़ो);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2i_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा bnx2i_percpu_s *p;
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा bnx2i_work *work, *पंचांगp;

	/* Prevent any new work from being queued क्रम this CPU */
	p = &per_cpu(bnx2i_percpu, cpu);
	spin_lock_bh(&p->p_work_lock);
	thपढ़ो = p->iothपढ़ो;
	p->iothपढ़ो = शून्य;

	/* Free all work in the list */
	list_क्रम_each_entry_safe(work, पंचांगp, &p->work_list, list) अणु
		list_del_init(&work->list);
		bnx2i_process_scsi_cmd_resp(work->session,
					    work->bnx2i_conn, &work->cqe);
		kमुक्त(work);
	पूर्ण

	spin_unlock_bh(&p->p_work_lock);
	अगर (thपढ़ो)
		kthपढ़ो_stop(thपढ़ो);
	वापस 0;
पूर्ण

अटल क्रमागत cpuhp_state bnx2i_online_state;

/**
 * bnx2i_mod_init - module init entry poपूर्णांक
 *
 * initialize any driver wide global data काष्ठाures such as endpoपूर्णांक pool,
 *	tcp port manager/queue, sysfs. finally driver will रेजिस्टर itself
 *	with the cnic module
 */
अटल पूर्णांक __init bnx2i_mod_init(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित cpu = 0;
	काष्ठा bnx2i_percpu_s *p;

	prपूर्णांकk(KERN_INFO "%s", version);

	अगर (sq_size && !is_घातer_of_2(sq_size))
		sq_size = roundup_घात_of_two(sq_size);

	bnx2i_scsi_xport_ढाँचा =
			iscsi_रेजिस्टर_transport(&bnx2i_iscsi_transport);
	अगर (!bnx2i_scsi_xport_ढाँचा) अणु
		prपूर्णांकk(KERN_ERR "Could not register bnx2i transport.\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = cnic_रेजिस्टर_driver(CNIC_ULP_ISCSI, &bnx2i_cnic_cb);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Could not register bnx2i cnic driver.\n");
		जाओ unreg_xport;
	पूर्ण

	/* Create percpu kernel thपढ़ोs to handle iSCSI I/O completions */
	क्रम_each_possible_cpu(cpu) अणु
		p = &per_cpu(bnx2i_percpu, cpu);
		INIT_LIST_HEAD(&p->work_list);
		spin_lock_init(&p->p_work_lock);
		p->iothपढ़ो = शून्य;
	पूर्ण

	err = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "scsi/bnx2i:online",
				bnx2i_cpu_online, bnx2i_cpu_offline);
	अगर (err < 0)
		जाओ unreg_driver;
	bnx2i_online_state = err;
	वापस 0;

unreg_driver:
	cnic_unरेजिस्टर_driver(CNIC_ULP_ISCSI);
unreg_xport:
	iscsi_unरेजिस्टर_transport(&bnx2i_iscsi_transport);
out:
	वापस err;
पूर्ण


/**
 * bnx2i_mod_निकास - module cleanup/निकास entry poपूर्णांक
 *
 * Global resource lock and host adapter lock is held during critical sections
 *	in this function. Driver will browse through the adapter list, cleans-up
 *	each instance, unरेजिस्टरs iscsi transport name and finally driver will
 *	unरेजिस्टर itself with the cnic module
 */
अटल व्योम __निकास bnx2i_mod_निकास(व्योम)
अणु
	काष्ठा bnx2i_hba *hba;

	mutex_lock(&bnx2i_dev_lock);
	जबतक (!list_empty(&adapter_list)) अणु
		hba = list_entry(adapter_list.next, काष्ठा bnx2i_hba, link);
		list_del(&hba->link);
		adapter_count--;

		अगर (test_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic)) अणु
			bnx2i_chip_cleanup(hba);
			hba->cnic->unरेजिस्टर_device(hba->cnic, CNIC_ULP_ISCSI);
			clear_bit(BNX2I_CNIC_REGISTERED, &hba->reg_with_cnic);
		पूर्ण

		bnx2i_मुक्त_hba(hba);
	पूर्ण
	mutex_unlock(&bnx2i_dev_lock);

	cpuhp_हटाओ_state(bnx2i_online_state);

	iscsi_unरेजिस्टर_transport(&bnx2i_iscsi_transport);
	cnic_unरेजिस्टर_driver(CNIC_ULP_ISCSI);
पूर्ण

module_init(bnx2i_mod_init);
module_निकास(bnx2i_mod_निकास);
