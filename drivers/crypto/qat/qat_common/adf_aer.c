<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"

अटल काष्ठा workqueue_काष्ठा *device_reset_wq;

अटल pci_ers_result_t adf_error_detected(काष्ठा pci_dev *pdev,
					   pci_channel_state_t state)
अणु
	काष्ठा adf_accel_dev *accel_dev = adf_devmgr_pci_to_accel_dev(pdev);

	dev_info(&pdev->dev, "Acceleration driver hardware error detected.\n");
	अगर (!accel_dev) अणु
		dev_err(&pdev->dev, "Can't find acceleration device\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	अगर (state == pci_channel_io_perm_failure) अणु
		dev_err(&pdev->dev, "Can't recover from device error\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/* reset dev data */
काष्ठा adf_reset_dev_data अणु
	पूर्णांक mode;
	काष्ठा adf_accel_dev *accel_dev;
	काष्ठा completion compl;
	काष्ठा work_काष्ठा reset_work;
पूर्ण;

व्योम adf_reset_sbr(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);
	काष्ठा pci_dev *parent = pdev->bus->self;
	u16 bridge_ctl = 0;

	अगर (!parent)
		parent = pdev;

	अगर (!pci_रुको_क्रम_pending_transaction(pdev))
		dev_info(&GET_DEV(accel_dev),
			 "Transaction still in progress. Proceeding\n");

	dev_info(&GET_DEV(accel_dev), "Secondary bus reset\n");

	pci_पढ़ो_config_word(parent, PCI_BRIDGE_CONTROL, &bridge_ctl);
	bridge_ctl |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_ग_लिखो_config_word(parent, PCI_BRIDGE_CONTROL, bridge_ctl);
	msleep(100);
	bridge_ctl &= ~PCI_BRIDGE_CTL_BUS_RESET;
	pci_ग_लिखो_config_word(parent, PCI_BRIDGE_CONTROL, bridge_ctl);
	msleep(100);
पूर्ण
EXPORT_SYMBOL_GPL(adf_reset_sbr);

व्योम adf_reset_flr(काष्ठा adf_accel_dev *accel_dev)
अणु
	pcie_flr(accel_to_pci_dev(accel_dev));
पूर्ण
EXPORT_SYMBOL_GPL(adf_reset_flr);

व्योम adf_dev_restore(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);

	अगर (hw_device->reset_device) अणु
		dev_info(&GET_DEV(accel_dev), "Resetting device qat_dev%d\n",
			 accel_dev->accel_id);
		hw_device->reset_device(accel_dev);
		pci_restore_state(pdev);
		pci_save_state(pdev);
	पूर्ण
पूर्ण

अटल व्योम adf_device_reset_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adf_reset_dev_data *reset_data =
		  container_of(work, काष्ठा adf_reset_dev_data, reset_work);
	काष्ठा adf_accel_dev *accel_dev = reset_data->accel_dev;

	adf_dev_restarting_notअगरy(accel_dev);
	adf_dev_stop(accel_dev);
	adf_dev_shutकरोwn(accel_dev);
	अगर (adf_dev_init(accel_dev) || adf_dev_start(accel_dev)) अणु
		/* The device hanged and we can't restart it so stop here */
		dev_err(&GET_DEV(accel_dev), "Restart device failed\n");
		kमुक्त(reset_data);
		WARN(1, "QAT: device restart failed. Device is unusable\n");
		वापस;
	पूर्ण
	adf_dev_restarted_notअगरy(accel_dev);
	clear_bit(ADF_STATUS_RESTARTING, &accel_dev->status);

	/* The dev is back alive. Notअगरy the caller अगर in sync mode */
	अगर (reset_data->mode == ADF_DEV_RESET_SYNC)
		complete(&reset_data->compl);
	अन्यथा
		kमुक्त(reset_data);
पूर्ण

अटल पूर्णांक adf_dev_aer_schedule_reset(काष्ठा adf_accel_dev *accel_dev,
				      क्रमागत adf_dev_reset_mode mode)
अणु
	काष्ठा adf_reset_dev_data *reset_data;

	अगर (!adf_dev_started(accel_dev) ||
	    test_bit(ADF_STATUS_RESTARTING, &accel_dev->status))
		वापस 0;

	set_bit(ADF_STATUS_RESTARTING, &accel_dev->status);
	reset_data = kzalloc(माप(*reset_data), GFP_KERNEL);
	अगर (!reset_data)
		वापस -ENOMEM;
	reset_data->accel_dev = accel_dev;
	init_completion(&reset_data->compl);
	reset_data->mode = mode;
	INIT_WORK(&reset_data->reset_work, adf_device_reset_worker);
	queue_work(device_reset_wq, &reset_data->reset_work);

	/* If in sync mode रुको क्रम the result */
	अगर (mode == ADF_DEV_RESET_SYNC) अणु
		पूर्णांक ret = 0;
		/* Maximum device reset समय is 10 seconds */
		अचिन्हित दीर्घ रुको_jअगरfies = msecs_to_jअगरfies(10000);
		अचिन्हित दीर्घ समयout = रुको_क्रम_completion_समयout(
				   &reset_data->compl, रुको_jअगरfies);
		अगर (!समयout) अणु
			dev_err(&GET_DEV(accel_dev),
				"Reset device timeout expired\n");
			ret = -EFAULT;
		पूर्ण
		kमुक्त(reset_data);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल pci_ers_result_t adf_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adf_accel_dev *accel_dev = adf_devmgr_pci_to_accel_dev(pdev);

	अगर (!accel_dev) अणु
		pr_err("QAT: Can't find acceleration device\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	अगर (adf_dev_aer_schedule_reset(accel_dev, ADF_DEV_RESET_SYNC))
		वापस PCI_ERS_RESULT_DISCONNECT;

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम adf_resume(काष्ठा pci_dev *pdev)
अणु
	dev_info(&pdev->dev, "Acceleration driver reset completed\n");
	dev_info(&pdev->dev, "Device is up and running\n");
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers adf_err_handler = अणु
	.error_detected = adf_error_detected,
	.slot_reset = adf_slot_reset,
	.resume = adf_resume,
पूर्ण;

/**
 * adf_enable_aer() - Enable Advance Error Reporting क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function enables PCI Advance Error Reporting क्रम the
 * QAT acceleration device accel_dev.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_enable_aer(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);
	काष्ठा pci_driver *pdrv = pdev->driver;

	pdrv->err_handler = &adf_err_handler;
	pci_enable_pcie_error_reporting(pdev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_enable_aer);

/**
 * adf_disable_aer() - Enable Advance Error Reporting क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function disables PCI Advance Error Reporting क्रम the
 * QAT acceleration device accel_dev.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम adf_disable_aer(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);

	pci_disable_pcie_error_reporting(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(adf_disable_aer);

पूर्णांक adf_init_aer(व्योम)
अणु
	device_reset_wq = alloc_workqueue("qat_device_reset_wq",
					  WQ_MEM_RECLAIM, 0);
	वापस !device_reset_wq ? -EFAULT : 0;
पूर्ण

व्योम adf_निकास_aer(व्योम)
अणु
	अगर (device_reset_wq)
		destroy_workqueue(device_reset_wq);
	device_reset_wq = शून्य;
पूर्ण
