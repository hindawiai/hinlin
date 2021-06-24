<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_cfg.h"
#समावेश "adf_common_drv.h"

अटल LIST_HEAD(service_table);
अटल DEFINE_MUTEX(service_lock);

अटल व्योम adf_service_add(काष्ठा service_hndl *service)
अणु
	mutex_lock(&service_lock);
	list_add(&service->list, &service_table);
	mutex_unlock(&service_lock);
पूर्ण

पूर्णांक adf_service_रेजिस्टर(काष्ठा service_hndl *service)
अणु
	स_रखो(service->init_status, 0, माप(service->init_status));
	स_रखो(service->start_status, 0, माप(service->start_status));
	adf_service_add(service);
	वापस 0;
पूर्ण

अटल व्योम adf_service_हटाओ(काष्ठा service_hndl *service)
अणु
	mutex_lock(&service_lock);
	list_del(&service->list);
	mutex_unlock(&service_lock);
पूर्ण

पूर्णांक adf_service_unरेजिस्टर(काष्ठा service_hndl *service)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(service->init_status); i++) अणु
		अगर (service->init_status[i] || service->start_status[i]) अणु
			pr_err("QAT: Could not remove active service\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	adf_service_हटाओ(service);
	वापस 0;
पूर्ण

/**
 * adf_dev_init() - Init data काष्ठाures and services क्रम the given accel device
 * @accel_dev: Poपूर्णांकer to acceleration device.
 *
 * Initialize the ring data काष्ठाures and the admin comms and arbitration
 * services.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_dev_init(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा service_hndl *service;
	काष्ठा list_head *list_itr;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;

	अगर (!hw_data) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to init device - hw_data not set\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!test_bit(ADF_STATUS_CONFIGURED, &accel_dev->status)) अणु
		dev_err(&GET_DEV(accel_dev), "Device not configured\n");
		वापस -EFAULT;
	पूर्ण

	अगर (adf_init_etr_data(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed initialize etr\n");
		वापस -EFAULT;
	पूर्ण

	अगर (hw_data->init_admin_comms && hw_data->init_admin_comms(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed initialize admin comms\n");
		वापस -EFAULT;
	पूर्ण

	अगर (hw_data->init_arb && hw_data->init_arb(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed initialize hw arbiter\n");
		वापस -EFAULT;
	पूर्ण

	hw_data->enable_पूर्णांकs(accel_dev);

	अगर (adf_ae_init(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to initialise Acceleration Engine\n");
		वापस -EFAULT;
	पूर्ण
	set_bit(ADF_STATUS_AE_INITIALISED, &accel_dev->status);

	अगर (adf_ae_fw_load(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to load acceleration FW\n");
		वापस -EFAULT;
	पूर्ण
	set_bit(ADF_STATUS_AE_UCODE_LOADED, &accel_dev->status);

	अगर (hw_data->alloc_irq(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to allocate interrupts\n");
		वापस -EFAULT;
	पूर्ण
	set_bit(ADF_STATUS_IRQ_ALLOCATED, &accel_dev->status);

	/*
	 * Subservice initialisation is भागided पूर्णांकo two stages: init and start.
	 * This is to facilitate any ordering dependencies between services
	 * prior to starting any of the accelerators.
	 */
	list_क्रम_each(list_itr, &service_table) अणु
		service = list_entry(list_itr, काष्ठा service_hndl, list);
		अगर (service->event_hld(accel_dev, ADF_EVENT_INIT)) अणु
			dev_err(&GET_DEV(accel_dev),
				"Failed to initialise service %s\n",
				service->name);
			वापस -EFAULT;
		पूर्ण
		set_bit(accel_dev->accel_id, service->init_status);
	पूर्ण

	hw_data->enable_error_correction(accel_dev);
	hw_data->enable_vf2pf_comms(accel_dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_init);

/**
 * adf_dev_start() - Start acceleration service क्रम the given accel device
 * @accel_dev:    Poपूर्णांकer to acceleration device.
 *
 * Function notअगरies all the रेजिस्टरed services that the acceleration device
 * is पढ़ोy to be used.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_dev_start(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा service_hndl *service;
	काष्ठा list_head *list_itr;

	set_bit(ADF_STATUS_STARTING, &accel_dev->status);

	अगर (adf_ae_start(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "AE Start Failed\n");
		वापस -EFAULT;
	पूर्ण
	set_bit(ADF_STATUS_AE_STARTED, &accel_dev->status);

	अगर (hw_data->send_admin_init(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to send init message\n");
		वापस -EFAULT;
	पूर्ण

	/* Set ssm watch करोg समयr */
	अगर (hw_data->set_ssm_wdसमयr)
		hw_data->set_ssm_wdसमयr(accel_dev);

	list_क्रम_each(list_itr, &service_table) अणु
		service = list_entry(list_itr, काष्ठा service_hndl, list);
		अगर (service->event_hld(accel_dev, ADF_EVENT_START)) अणु
			dev_err(&GET_DEV(accel_dev),
				"Failed to start service %s\n",
				service->name);
			वापस -EFAULT;
		पूर्ण
		set_bit(accel_dev->accel_id, service->start_status);
	पूर्ण

	clear_bit(ADF_STATUS_STARTING, &accel_dev->status);
	set_bit(ADF_STATUS_STARTED, &accel_dev->status);

	अगर (!list_empty(&accel_dev->crypto_list) &&
	    (qat_algs_रेजिस्टर() || qat_asym_algs_रेजिस्टर())) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to register crypto algs\n");
		set_bit(ADF_STATUS_STARTING, &accel_dev->status);
		clear_bit(ADF_STATUS_STARTED, &accel_dev->status);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_start);

/**
 * adf_dev_stop() - Stop acceleration service क्रम the given accel device
 * @accel_dev:    Poपूर्णांकer to acceleration device.
 *
 * Function notअगरies all the रेजिस्टरed services that the acceleration device
 * is shuting करोwn.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम adf_dev_stop(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा service_hndl *service;
	काष्ठा list_head *list_itr;
	bool रुको = false;
	पूर्णांक ret;

	अगर (!adf_dev_started(accel_dev) &&
	    !test_bit(ADF_STATUS_STARTING, &accel_dev->status))
		वापस;

	clear_bit(ADF_STATUS_STARTING, &accel_dev->status);
	clear_bit(ADF_STATUS_STARTED, &accel_dev->status);

	अगर (!list_empty(&accel_dev->crypto_list)) अणु
		qat_algs_unरेजिस्टर();
		qat_asym_algs_unरेजिस्टर();
	पूर्ण

	list_क्रम_each(list_itr, &service_table) अणु
		service = list_entry(list_itr, काष्ठा service_hndl, list);
		अगर (!test_bit(accel_dev->accel_id, service->start_status))
			जारी;
		ret = service->event_hld(accel_dev, ADF_EVENT_STOP);
		अगर (!ret) अणु
			clear_bit(accel_dev->accel_id, service->start_status);
		पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
			रुको = true;
			clear_bit(accel_dev->accel_id, service->start_status);
		पूर्ण
	पूर्ण

	अगर (रुको)
		msleep(100);

	अगर (test_bit(ADF_STATUS_AE_STARTED, &accel_dev->status)) अणु
		अगर (adf_ae_stop(accel_dev))
			dev_err(&GET_DEV(accel_dev), "failed to stop AE\n");
		अन्यथा
			clear_bit(ADF_STATUS_AE_STARTED, &accel_dev->status);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_stop);

/**
 * adf_dev_shutकरोwn() - shutकरोwn acceleration services and data strucutures
 * @accel_dev: Poपूर्णांकer to acceleration device
 *
 * Cleanup the ring data काष्ठाures and the admin comms and arbitration
 * services.
 */
व्योम adf_dev_shutकरोwn(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा service_hndl *service;
	काष्ठा list_head *list_itr;

	अगर (!hw_data) अणु
		dev_err(&GET_DEV(accel_dev),
			"QAT: Failed to shutdown device - hw_data not set\n");
		वापस;
	पूर्ण

	अगर (test_bit(ADF_STATUS_AE_UCODE_LOADED, &accel_dev->status)) अणु
		adf_ae_fw_release(accel_dev);
		clear_bit(ADF_STATUS_AE_UCODE_LOADED, &accel_dev->status);
	पूर्ण

	अगर (test_bit(ADF_STATUS_AE_INITIALISED, &accel_dev->status)) अणु
		अगर (adf_ae_shutकरोwn(accel_dev))
			dev_err(&GET_DEV(accel_dev),
				"Failed to shutdown Accel Engine\n");
		अन्यथा
			clear_bit(ADF_STATUS_AE_INITIALISED,
				  &accel_dev->status);
	पूर्ण

	list_क्रम_each(list_itr, &service_table) अणु
		service = list_entry(list_itr, काष्ठा service_hndl, list);
		अगर (!test_bit(accel_dev->accel_id, service->init_status))
			जारी;
		अगर (service->event_hld(accel_dev, ADF_EVENT_SHUTDOWN))
			dev_err(&GET_DEV(accel_dev),
				"Failed to shutdown service %s\n",
				service->name);
		अन्यथा
			clear_bit(accel_dev->accel_id, service->init_status);
	पूर्ण

	hw_data->disable_iov(accel_dev);

	अगर (test_bit(ADF_STATUS_IRQ_ALLOCATED, &accel_dev->status)) अणु
		hw_data->मुक्त_irq(accel_dev);
		clear_bit(ADF_STATUS_IRQ_ALLOCATED, &accel_dev->status);
	पूर्ण

	/* Delete configuration only अगर not restarting */
	अगर (!test_bit(ADF_STATUS_RESTARTING, &accel_dev->status))
		adf_cfg_del_all(accel_dev);

	अगर (hw_data->निकास_arb)
		hw_data->निकास_arb(accel_dev);

	अगर (hw_data->निकास_admin_comms)
		hw_data->निकास_admin_comms(accel_dev);

	adf_cleanup_etr_data(accel_dev);
	adf_dev_restore(accel_dev);
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_shutकरोwn);

पूर्णांक adf_dev_restarting_notअगरy(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा service_hndl *service;
	काष्ठा list_head *list_itr;

	list_क्रम_each(list_itr, &service_table) अणु
		service = list_entry(list_itr, काष्ठा service_hndl, list);
		अगर (service->event_hld(accel_dev, ADF_EVENT_RESTARTING))
			dev_err(&GET_DEV(accel_dev),
				"Failed to restart service %s.\n",
				service->name);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक adf_dev_restarted_notअगरy(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा service_hndl *service;
	काष्ठा list_head *list_itr;

	list_क्रम_each(list_itr, &service_table) अणु
		service = list_entry(list_itr, काष्ठा service_hndl, list);
		अगर (service->event_hld(accel_dev, ADF_EVENT_RESTARTED))
			dev_err(&GET_DEV(accel_dev),
				"Failed to restart service %s.\n",
				service->name);
	पूर्ण
	वापस 0;
पूर्ण
