<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Module पूर्णांकerface and handling of zfcp data काष्ठाures.
 *
 * Copyright IBM Corp. 2002, 2020
 */

/*
 * Driver authors:
 *            Martin Peschke (originator of the driver)
 *            Raimund Schroeder
 *            Aron Zeh
 *            Wolfgang Taphorn
 *            Stefan Bader
 *            Heiko Carstens (kernel 2.6 port of the driver)
 *            Andreas Herrmann
 *            Maxim Shchetynin
 *            Volker Sameske
 *            Ralph Wuerthner
 *            Michael Loehr
 *            Swen Schillig
 *            Christof Schmitt
 *            Martin Petermann
 *            Sven Schuetz
 *            Steffen Maier
 *	      Benjamin Block
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_fc.h"
#समावेश "zfcp_reqlist.h"
#समावेश "zfcp_diag.h"

#घोषणा ZFCP_BUS_ID_SIZE	20

MODULE_AUTHOR("IBM Deutschland Entwicklung GmbH - linux390@de.ibm.com");
MODULE_DESCRIPTION("FCP HBA driver");
MODULE_LICENSE("GPL");

अटल अक्षर *init_device;
module_param_named(device, init_device, अक्षरp, 0400);
MODULE_PARM_DESC(device, "specify initial device");

अटल काष्ठा kmem_cache * __init zfcp_cache_hw_align(स्थिर अक्षर *name,
						      अचिन्हित दीर्घ size)
अणु
	वापस kmem_cache_create(name, size, roundup_घात_of_two(size), 0, शून्य);
पूर्ण

अटल व्योम __init zfcp_init_device_configure(अक्षर *busid, u64 wwpn, u64 lun)
अणु
	काष्ठा ccw_device *cdev;
	काष्ठा zfcp_adapter *adapter;
	काष्ठा zfcp_port *port;

	cdev = get_ccwdev_by_busid(&zfcp_ccw_driver, busid);
	अगर (!cdev)
		वापस;

	अगर (ccw_device_set_online(cdev))
		जाओ out_ccw_device;

	adapter = zfcp_ccw_adapter_by_cdev(cdev);
	अगर (!adapter)
		जाओ out_ccw_device;

	port = zfcp_get_port_by_wwpn(adapter, wwpn);
	अगर (!port)
		जाओ out_port;
	flush_work(&port->rport_work);

	zfcp_unit_add(port, lun);
	put_device(&port->dev);

out_port:
	zfcp_ccw_adapter_put(adapter);
out_ccw_device:
	put_device(&cdev->dev);
	वापस;
पूर्ण

अटल व्योम __init zfcp_init_device_setup(अक्षर *devstr)
अणु
	अक्षर *token;
	अक्षर *str, *str_saved;
	अक्षर busid[ZFCP_BUS_ID_SIZE];
	u64 wwpn, lun;

	/* duplicate devstr and keep the original क्रम sysfs presentation*/
	str_saved = kstrdup(devstr, GFP_KERNEL);
	str = str_saved;
	अगर (!str)
		वापस;

	token = strsep(&str, ",");
	अगर (!token || म_माप(token) >= ZFCP_BUS_ID_SIZE)
		जाओ err_out;
	strlcpy(busid, token, ZFCP_BUS_ID_SIZE);

	token = strsep(&str, ",");
	अगर (!token || kम_से_अदीर्घl(token, 0, (अचिन्हित दीर्घ दीर्घ *) &wwpn))
		जाओ err_out;

	token = strsep(&str, ",");
	अगर (!token || kम_से_अदीर्घl(token, 0, (अचिन्हित दीर्घ दीर्घ *) &lun))
		जाओ err_out;

	kमुक्त(str_saved);
	zfcp_init_device_configure(busid, wwpn, lun);
	वापस;

err_out:
	kमुक्त(str_saved);
	pr_err("%s is not a valid SCSI device\n", devstr);
पूर्ण

अटल पूर्णांक __init zfcp_module_init(व्योम)
अणु
	पूर्णांक retval = -ENOMEM;

	अगर (zfcp_experimental_dix)
		pr_warn("DIX is enabled. It is experimental and might cause problems\n");

	zfcp_fsf_qtcb_cache = zfcp_cache_hw_align("zfcp_fsf_qtcb",
						  माप(काष्ठा fsf_qtcb));
	अगर (!zfcp_fsf_qtcb_cache)
		जाओ out_qtcb_cache;

	zfcp_fc_req_cache = zfcp_cache_hw_align("zfcp_fc_req",
						माप(काष्ठा zfcp_fc_req));
	अगर (!zfcp_fc_req_cache)
		जाओ out_fc_cache;

	zfcp_scsi_transport_ढाँचा =
		fc_attach_transport(&zfcp_transport_functions);
	अगर (!zfcp_scsi_transport_ढाँचा)
		जाओ out_transport;
	scsi_transport_reserve_device(zfcp_scsi_transport_ढाँचा,
				      माप(काष्ठा zfcp_scsi_dev));

	retval = ccw_driver_रेजिस्टर(&zfcp_ccw_driver);
	अगर (retval) अणु
		pr_err("The zfcp device driver could not register with "
		       "the common I/O layer\n");
		जाओ out_ccw_रेजिस्टर;
	पूर्ण

	अगर (init_device)
		zfcp_init_device_setup(init_device);
	वापस 0;

out_ccw_रेजिस्टर:
	fc_release_transport(zfcp_scsi_transport_ढाँचा);
out_transport:
	kmem_cache_destroy(zfcp_fc_req_cache);
out_fc_cache:
	kmem_cache_destroy(zfcp_fsf_qtcb_cache);
out_qtcb_cache:
	वापस retval;
पूर्ण

module_init(zfcp_module_init);

अटल व्योम __निकास zfcp_module_निकास(व्योम)
अणु
	ccw_driver_unरेजिस्टर(&zfcp_ccw_driver);
	fc_release_transport(zfcp_scsi_transport_ढाँचा);
	kmem_cache_destroy(zfcp_fc_req_cache);
	kmem_cache_destroy(zfcp_fsf_qtcb_cache);
पूर्ण

module_निकास(zfcp_module_निकास);

/**
 * zfcp_get_port_by_wwpn - find port in port list of adapter by wwpn
 * @adapter: poपूर्णांकer to adapter to search क्रम port
 * @wwpn: wwpn to search क्रम
 *
 * Returns: poपूर्णांकer to zfcp_port or शून्य
 */
काष्ठा zfcp_port *zfcp_get_port_by_wwpn(काष्ठा zfcp_adapter *adapter,
					u64 wwpn)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_port *port;

	पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		अगर (port->wwpn == wwpn) अणु
			अगर (!get_device(&port->dev))
				port = शून्य;
			पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);
			वापस port;
		पूर्ण
	पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);
	वापस शून्य;
पूर्ण

अटल पूर्णांक zfcp_allocate_low_mem_buffers(काष्ठा zfcp_adapter *adapter)
अणु
	adapter->pool.erp_req =
		mempool_create_kदो_स्मृति_pool(1, माप(काष्ठा zfcp_fsf_req));
	अगर (!adapter->pool.erp_req)
		वापस -ENOMEM;

	adapter->pool.gid_pn_req =
		mempool_create_kदो_स्मृति_pool(1, माप(काष्ठा zfcp_fsf_req));
	अगर (!adapter->pool.gid_pn_req)
		वापस -ENOMEM;

	adapter->pool.scsi_req =
		mempool_create_kदो_स्मृति_pool(1, माप(काष्ठा zfcp_fsf_req));
	अगर (!adapter->pool.scsi_req)
		वापस -ENOMEM;

	adapter->pool.scsi_पात =
		mempool_create_kदो_स्मृति_pool(1, माप(काष्ठा zfcp_fsf_req));
	अगर (!adapter->pool.scsi_पात)
		वापस -ENOMEM;

	adapter->pool.status_पढ़ो_req =
		mempool_create_kदो_स्मृति_pool(FSF_STATUS_READS_RECOM,
					    माप(काष्ठा zfcp_fsf_req));
	अगर (!adapter->pool.status_पढ़ो_req)
		वापस -ENOMEM;

	adapter->pool.qtcb_pool =
		mempool_create_slab_pool(4, zfcp_fsf_qtcb_cache);
	अगर (!adapter->pool.qtcb_pool)
		वापस -ENOMEM;

	BUILD_BUG_ON(माप(काष्ठा fsf_status_पढ़ो_buffer) > PAGE_SIZE);
	adapter->pool.sr_data =
		mempool_create_page_pool(FSF_STATUS_READS_RECOM, 0);
	अगर (!adapter->pool.sr_data)
		वापस -ENOMEM;

	adapter->pool.gid_pn =
		mempool_create_slab_pool(1, zfcp_fc_req_cache);
	अगर (!adapter->pool.gid_pn)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम zfcp_मुक्त_low_mem_buffers(काष्ठा zfcp_adapter *adapter)
अणु
	mempool_destroy(adapter->pool.erp_req);
	mempool_destroy(adapter->pool.scsi_req);
	mempool_destroy(adapter->pool.scsi_पात);
	mempool_destroy(adapter->pool.qtcb_pool);
	mempool_destroy(adapter->pool.status_पढ़ो_req);
	mempool_destroy(adapter->pool.sr_data);
	mempool_destroy(adapter->pool.gid_pn);
पूर्ण

/**
 * zfcp_status_पढ़ो_refill - refill the दीर्घ running status_पढ़ो_requests
 * @adapter: ptr to काष्ठा zfcp_adapter क्रम which the buffers should be refilled
 *
 * Return:
 * * 0 on success meaning at least one status पढ़ो is pending
 * * 1 अगर posting failed and not a single status पढ़ो buffer is pending,
 *     also triggers adapter reखोलो recovery
 */
पूर्णांक zfcp_status_पढ़ो_refill(काष्ठा zfcp_adapter *adapter)
अणु
	जबतक (atomic_add_unless(&adapter->stat_miss, -1, 0))
		अगर (zfcp_fsf_status_पढ़ो(adapter->qdio)) अणु
			atomic_inc(&adapter->stat_miss); /* unकरो add -1 */
			अगर (atomic_पढ़ो(&adapter->stat_miss) >=
			    adapter->stat_पढ़ो_buf_num) अणु
				zfcp_erp_adapter_reखोलो(adapter, 0, "axsref1");
				वापस 1;
			पूर्ण
			अवरोध;
		पूर्ण
	वापस 0;
पूर्ण

अटल व्योम _zfcp_status_पढ़ो_scheduler(काष्ठा work_काष्ठा *work)
अणु
	zfcp_status_पढ़ो_refill(container_of(work, काष्ठा zfcp_adapter,
					     stat_work));
पूर्ण

अटल व्योम zfcp_version_change_lost_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zfcp_adapter *adapter = container_of(work, काष्ठा zfcp_adapter,
						    version_change_lost_work);

	zfcp_fsf_exchange_config_data_sync(adapter->qdio, शून्य);
पूर्ण

अटल व्योम zfcp_prपूर्णांक_sl(काष्ठा seq_file *m, काष्ठा service_level *sl)
अणु
	काष्ठा zfcp_adapter *adapter =
		container_of(sl, काष्ठा zfcp_adapter, service_level);

	seq_म_लिखो(m, "zfcp: %s microcode level %x\n",
		   dev_name(&adapter->ccw_device->dev),
		   adapter->fsf_lic_version);
पूर्ण

अटल पूर्णांक zfcp_setup_adapter_work_queue(काष्ठा zfcp_adapter *adapter)
अणु
	अक्षर name[TASK_COMM_LEN];

	snम_लिखो(name, माप(name), "zfcp_q_%s",
		 dev_name(&adapter->ccw_device->dev));
	adapter->work_queue = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);

	अगर (adapter->work_queue)
		वापस 0;
	वापस -ENOMEM;
पूर्ण

अटल व्योम zfcp_destroy_adapter_work_queue(काष्ठा zfcp_adapter *adapter)
अणु
	अगर (adapter->work_queue)
		destroy_workqueue(adapter->work_queue);
	adapter->work_queue = शून्य;

पूर्ण

/**
 * zfcp_adapter_enqueue - enqueue a new adapter to the list
 * @ccw_device: poपूर्णांकer to the काष्ठा cc_device
 *
 * Returns:	काष्ठा zfcp_adapter*
 * Enqueues an adapter at the end of the adapter list in the driver data.
 * All adapter पूर्णांकernal काष्ठाures are set up.
 * Proc-fs entries are also created.
 */
काष्ठा zfcp_adapter *zfcp_adapter_enqueue(काष्ठा ccw_device *ccw_device)
अणु
	काष्ठा zfcp_adapter *adapter;

	अगर (!get_device(&ccw_device->dev))
		वापस ERR_PTR(-ENODEV);

	adapter = kzalloc(माप(काष्ठा zfcp_adapter), GFP_KERNEL);
	अगर (!adapter) अणु
		put_device(&ccw_device->dev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	kref_init(&adapter->ref);

	ccw_device->handler = शून्य;
	adapter->ccw_device = ccw_device;

	INIT_WORK(&adapter->stat_work, _zfcp_status_पढ़ो_scheduler);
	INIT_DELAYED_WORK(&adapter->scan_work, zfcp_fc_scan_ports);
	INIT_WORK(&adapter->ns_up_work, zfcp_fc_sym_name_update);
	INIT_WORK(&adapter->version_change_lost_work,
		  zfcp_version_change_lost_work);

	adapter->next_port_scan = jअगरfies;

	adapter->erp_action.adapter = adapter;

	अगर (zfcp_diag_adapter_setup(adapter))
		जाओ failed;

	अगर (zfcp_qdio_setup(adapter))
		जाओ failed;

	अगर (zfcp_allocate_low_mem_buffers(adapter))
		जाओ failed;

	adapter->req_list = zfcp_reqlist_alloc();
	अगर (!adapter->req_list)
		जाओ failed;

	अगर (zfcp_dbf_adapter_रेजिस्टर(adapter))
		जाओ failed;

	अगर (zfcp_setup_adapter_work_queue(adapter))
		जाओ failed;

	अगर (zfcp_fc_gs_setup(adapter))
		जाओ failed;

	rwlock_init(&adapter->port_list_lock);
	INIT_LIST_HEAD(&adapter->port_list);

	INIT_LIST_HEAD(&adapter->events.list);
	INIT_WORK(&adapter->events.work, zfcp_fc_post_event);
	spin_lock_init(&adapter->events.list_lock);

	init_रुकोqueue_head(&adapter->erp_पढ़ोy_wq);
	init_रुकोqueue_head(&adapter->erp_करोne_wqh);

	INIT_LIST_HEAD(&adapter->erp_पढ़ोy_head);
	INIT_LIST_HEAD(&adapter->erp_running_head);

	rwlock_init(&adapter->erp_lock);
	rwlock_init(&adapter->पात_lock);

	अगर (zfcp_erp_thपढ़ो_setup(adapter))
		जाओ failed;

	adapter->service_level.seq_prपूर्णांक = zfcp_prपूर्णांक_sl;

	dev_set_drvdata(&ccw_device->dev, adapter);

	अगर (device_add_groups(&ccw_device->dev, zfcp_sysfs_adapter_attr_groups))
		जाओ err_sysfs;

	/* report size limit per scatter-gather segment */
	adapter->ccw_device->dev.dma_parms = &adapter->dma_parms;

	adapter->stat_पढ़ो_buf_num = FSF_STATUS_READS_RECOM;

	वापस adapter;

err_sysfs:
failed:
	/* TODO: make this more fine-granular */
	cancel_delayed_work_sync(&adapter->scan_work);
	cancel_work_sync(&adapter->stat_work);
	cancel_work_sync(&adapter->ns_up_work);
	cancel_work_sync(&adapter->version_change_lost_work);
	zfcp_destroy_adapter_work_queue(adapter);

	zfcp_fc_wka_ports_क्रमce_offline(adapter->gs);
	zfcp_scsi_adapter_unरेजिस्टर(adapter);

	zfcp_erp_thपढ़ो_समाप्त(adapter);
	zfcp_dbf_adapter_unरेजिस्टर(adapter);
	zfcp_qdio_destroy(adapter->qdio);

	zfcp_ccw_adapter_put(adapter); /* final put to release */
	वापस ERR_PTR(-ENOMEM);
पूर्ण

व्योम zfcp_adapter_unरेजिस्टर(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा ccw_device *cdev = adapter->ccw_device;

	cancel_delayed_work_sync(&adapter->scan_work);
	cancel_work_sync(&adapter->stat_work);
	cancel_work_sync(&adapter->ns_up_work);
	cancel_work_sync(&adapter->version_change_lost_work);
	zfcp_destroy_adapter_work_queue(adapter);

	zfcp_fc_wka_ports_क्रमce_offline(adapter->gs);
	zfcp_scsi_adapter_unरेजिस्टर(adapter);
	device_हटाओ_groups(&cdev->dev, zfcp_sysfs_adapter_attr_groups);

	zfcp_erp_thपढ़ो_समाप्त(adapter);
	zfcp_dbf_adapter_unरेजिस्टर(adapter);
	zfcp_qdio_destroy(adapter->qdio);

	zfcp_ccw_adapter_put(adapter); /* final put to release */
पूर्ण

/**
 * zfcp_adapter_release - हटाओ the adapter from the resource list
 * @ref: poपूर्णांकer to काष्ठा kref
 * locks:	adapter list ग_लिखो lock is assumed to be held by caller
 */
व्योम zfcp_adapter_release(काष्ठा kref *ref)
अणु
	काष्ठा zfcp_adapter *adapter = container_of(ref, काष्ठा zfcp_adapter,
						    ref);
	काष्ठा ccw_device *cdev = adapter->ccw_device;

	dev_set_drvdata(&adapter->ccw_device->dev, शून्य);
	zfcp_fc_gs_destroy(adapter);
	zfcp_मुक्त_low_mem_buffers(adapter);
	zfcp_diag_adapter_मुक्त(adapter);
	kमुक्त(adapter->req_list);
	kमुक्त(adapter->fc_stats);
	kमुक्त(adapter->stats_reset_data);
	kमुक्त(adapter);
	put_device(&cdev->dev);
पूर्ण

अटल व्योम zfcp_port_release(काष्ठा device *dev)
अणु
	काष्ठा zfcp_port *port = container_of(dev, काष्ठा zfcp_port, dev);

	zfcp_ccw_adapter_put(port->adapter);
	kमुक्त(port);
पूर्ण

/**
 * zfcp_port_enqueue - enqueue port to port list of adapter
 * @adapter: adapter where remote port is added
 * @wwpn: WWPN of the remote port to be enqueued
 * @status: initial status क्रम the port
 * @d_id: destination id of the remote port to be enqueued
 * Returns: poपूर्णांकer to enqueued port on success, ERR_PTR on error
 *
 * All port पूर्णांकernal काष्ठाures are set up and the sysfs entry is generated.
 * d_id is used to enqueue ports with a well known address like the Directory
 * Service क्रम nameserver lookup.
 */
काष्ठा zfcp_port *zfcp_port_enqueue(काष्ठा zfcp_adapter *adapter, u64 wwpn,
				     u32 status, u32 d_id)
अणु
	काष्ठा zfcp_port *port;
	पूर्णांक retval = -ENOMEM;

	kref_get(&adapter->ref);

	port = zfcp_get_port_by_wwpn(adapter, wwpn);
	अगर (port) अणु
		put_device(&port->dev);
		retval = -EEXIST;
		जाओ err_out;
	पूर्ण

	port = kzalloc(माप(काष्ठा zfcp_port), GFP_KERNEL);
	अगर (!port)
		जाओ err_out;

	rwlock_init(&port->unit_list_lock);
	INIT_LIST_HEAD(&port->unit_list);
	atomic_set(&port->units, 0);

	INIT_WORK(&port->gid_pn_work, zfcp_fc_port_did_lookup);
	INIT_WORK(&port->test_link_work, zfcp_fc_link_test_work);
	INIT_WORK(&port->rport_work, zfcp_scsi_rport_work);

	port->adapter = adapter;
	port->d_id = d_id;
	port->wwpn = wwpn;
	port->rport_task = RPORT_NONE;
	port->dev.parent = &adapter->ccw_device->dev;
	port->dev.groups = zfcp_port_attr_groups;
	port->dev.release = zfcp_port_release;

	port->erp_action.adapter = adapter;
	port->erp_action.port = port;

	अगर (dev_set_name(&port->dev, "0x%016llx", (अचिन्हित दीर्घ दीर्घ)wwpn)) अणु
		kमुक्त(port);
		जाओ err_out;
	पूर्ण
	retval = -EINVAL;

	अगर (device_रेजिस्टर(&port->dev)) अणु
		put_device(&port->dev);
		जाओ err_out;
	पूर्ण

	ग_लिखो_lock_irq(&adapter->port_list_lock);
	list_add_tail(&port->list, &adapter->port_list);
	ग_लिखो_unlock_irq(&adapter->port_list_lock);

	atomic_or(status | ZFCP_STATUS_COMMON_RUNNING, &port->status);

	वापस port;

err_out:
	zfcp_ccw_adapter_put(adapter);
	वापस ERR_PTR(retval);
पूर्ण
