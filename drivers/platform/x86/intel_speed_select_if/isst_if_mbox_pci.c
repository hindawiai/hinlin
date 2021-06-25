<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Speed Select Interface: Mbox via PCI Interface
 * Copyright (c) 2019, Intel Corporation.
 * All rights reserved.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */

#समावेश <linux/cpufeature.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/isst_अगर.h>

#समावेश "isst_if_common.h"

#घोषणा PUNIT_MAILBOX_DATA		0xA0
#घोषणा PUNIT_MAILBOX_INTERFACE		0xA4
#घोषणा PUNIT_MAILBOX_BUSY_BIT		31

/*
 * The average समय to complete mailbox commands is less than 40us. Most of
 * the commands complete in few micro seconds. But the same firmware handles
 * requests from all घातer management features.
 * We can create a scenario where we flood the firmware with requests then
 * the mailbox response can be delayed क्रम 100s of micro seconds. So define
 * two समयouts. One क्रम average हाल and one क्रम दीर्घ.
 * If the firmware is taking more than average, just call cond_resched().
 */
#घोषणा OS_MAILBOX_TIMEOUT_AVG_US	40
#घोषणा OS_MAILBOX_TIMEOUT_MAX_US	1000

काष्ठा isst_अगर_device अणु
	काष्ठा mutex mutex;
पूर्ण;

अटल पूर्णांक isst_अगर_mbox_cmd(काष्ठा pci_dev *pdev,
			    काष्ठा isst_अगर_mbox_cmd *mbox_cmd)
अणु
	s64 पंचांग_delta = 0;
	kसमय_प्रकार पंचांग;
	u32 data;
	पूर्णांक ret;

	/* Poll क्रम rb bit == 0 */
	पंचांग = kसमय_get();
	करो अणु
		ret = pci_पढ़ो_config_dword(pdev, PUNIT_MAILBOX_INTERFACE,
					    &data);
		अगर (ret)
			वापस ret;

		अगर (data & BIT_ULL(PUNIT_MAILBOX_BUSY_BIT)) अणु
			ret = -EBUSY;
			पंचांग_delta = kसमय_us_delta(kसमय_get(), पंचांग);
			अगर (पंचांग_delta > OS_MAILBOX_TIMEOUT_AVG_US)
				cond_resched();
			जारी;
		पूर्ण
		ret = 0;
		अवरोध;
	पूर्ण जबतक (पंचांग_delta < OS_MAILBOX_TIMEOUT_MAX_US);

	अगर (ret)
		वापस ret;

	/* Write DATA रेजिस्टर */
	ret = pci_ग_लिखो_config_dword(pdev, PUNIT_MAILBOX_DATA,
				     mbox_cmd->req_data);
	अगर (ret)
		वापस ret;

	/* Write command रेजिस्टर */
	data = BIT_ULL(PUNIT_MAILBOX_BUSY_BIT) |
		      (mbox_cmd->parameter & GENMASK_ULL(13, 0)) << 16 |
		      (mbox_cmd->sub_command << 8) |
		      mbox_cmd->command;

	ret = pci_ग_लिखो_config_dword(pdev, PUNIT_MAILBOX_INTERFACE, data);
	अगर (ret)
		वापस ret;

	/* Poll क्रम rb bit == 0 */
	पंचांग_delta = 0;
	पंचांग = kसमय_get();
	करो अणु
		ret = pci_पढ़ो_config_dword(pdev, PUNIT_MAILBOX_INTERFACE,
					    &data);
		अगर (ret)
			वापस ret;

		अगर (data & BIT_ULL(PUNIT_MAILBOX_BUSY_BIT)) अणु
			ret = -EBUSY;
			पंचांग_delta = kसमय_us_delta(kसमय_get(), पंचांग);
			अगर (पंचांग_delta > OS_MAILBOX_TIMEOUT_AVG_US)
				cond_resched();
			जारी;
		पूर्ण

		अगर (data & 0xff)
			वापस -ENXIO;

		ret = pci_पढ़ो_config_dword(pdev, PUNIT_MAILBOX_DATA, &data);
		अगर (ret)
			वापस ret;

		mbox_cmd->resp_data = data;
		ret = 0;
		अवरोध;
	पूर्ण जबतक (पंचांग_delta < OS_MAILBOX_TIMEOUT_MAX_US);

	वापस ret;
पूर्ण

अटल दीर्घ isst_अगर_mbox_proc_cmd(u8 *cmd_ptr, पूर्णांक *ग_लिखो_only, पूर्णांक resume)
अणु
	काष्ठा isst_अगर_mbox_cmd *mbox_cmd;
	काष्ठा isst_अगर_device *punit_dev;
	काष्ठा pci_dev *pdev;
	पूर्णांक ret;

	mbox_cmd = (काष्ठा isst_अगर_mbox_cmd *)cmd_ptr;

	अगर (isst_अगर_mbox_cmd_invalid(mbox_cmd))
		वापस -EINVAL;

	अगर (isst_अगर_mbox_cmd_set_req(mbox_cmd) && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	pdev = isst_अगर_get_pci_dev(mbox_cmd->logical_cpu, 1, 30, 1);
	अगर (!pdev)
		वापस -EINVAL;

	punit_dev = pci_get_drvdata(pdev);
	अगर (!punit_dev)
		वापस -EINVAL;

	/*
	 * Basically we are allowing one complete mailbox transaction on
	 * a mapped PCI device at a समय.
	 */
	mutex_lock(&punit_dev->mutex);
	ret = isst_अगर_mbox_cmd(pdev, mbox_cmd);
	अगर (!ret && !resume && isst_अगर_mbox_cmd_set_req(mbox_cmd))
		ret = isst_store_cmd(mbox_cmd->command,
				     mbox_cmd->sub_command,
				     mbox_cmd->logical_cpu, 1,
				     mbox_cmd->parameter,
				     mbox_cmd->req_data);
	mutex_unlock(&punit_dev->mutex);
	अगर (ret)
		वापस ret;

	*ग_लिखो_only = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id isst_अगर_mbox_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CFG_MBOX_DEVID_0)पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_CFG_MBOX_DEVID_1)पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, isst_अगर_mbox_ids);

अटल पूर्णांक isst_अगर_mbox_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा isst_अगर_device *punit_dev;
	काष्ठा isst_अगर_cmd_cb cb;
	पूर्णांक ret;

	punit_dev = devm_kzalloc(&pdev->dev, माप(*punit_dev), GFP_KERNEL);
	अगर (!punit_dev)
		वापस -ENOMEM;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	mutex_init(&punit_dev->mutex);
	pci_set_drvdata(pdev, punit_dev);

	स_रखो(&cb, 0, माप(cb));
	cb.cmd_size = माप(काष्ठा isst_अगर_mbox_cmd);
	cb.offset = दुरत्व(काष्ठा isst_अगर_mbox_cmds, mbox_cmd);
	cb.cmd_callback = isst_अगर_mbox_proc_cmd;
	cb.owner = THIS_MODULE;
	ret = isst_अगर_cdev_रेजिस्टर(ISST_IF_DEV_MBOX, &cb);

	अगर (ret)
		mutex_destroy(&punit_dev->mutex);

	वापस ret;
पूर्ण

अटल व्योम isst_अगर_mbox_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा isst_अगर_device *punit_dev;

	punit_dev = pci_get_drvdata(pdev);
	isst_अगर_cdev_unरेजिस्टर(ISST_IF_DEV_MBOX);
	mutex_destroy(&punit_dev->mutex);
पूर्ण

अटल पूर्णांक __maybe_unused isst_अगर_resume(काष्ठा device *device)
अणु
	isst_resume_common();
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(isst_अगर_pm_ops, शून्य, isst_अगर_resume);

अटल काष्ठा pci_driver isst_अगर_pci_driver = अणु
	.name			= "isst_if_mbox_pci",
	.id_table		= isst_अगर_mbox_ids,
	.probe			= isst_अगर_mbox_probe,
	.हटाओ			= isst_अगर_mbox_हटाओ,
	.driver.pm		= &isst_अगर_pm_ops,
पूर्ण;

module_pci_driver(isst_अगर_pci_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel speed select interface pci mailbox driver");
