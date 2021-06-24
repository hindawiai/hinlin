<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * AMD MP2 PCIe communication driver
 *
 * Authors: Shyam Sundar S K <Shyam-sundar.S-k@amd.com>
 *          Elie Morisse <syniurge@gmail.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "i2c-amd-mp2.h"

#समावेश <linux/io-64-nonatomic-lo-hi.h>

अटल व्योम amd_mp2_c2p_mutex_lock(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;

	/* there is only one data mailbox क्रम two i2c adapters */
	mutex_lock(&privdata->c2p_lock);
	privdata->c2p_lock_busid = i2c_common->bus_id;
पूर्ण

अटल व्योम amd_mp2_c2p_mutex_unlock(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;

	अगर (unlikely(privdata->c2p_lock_busid != i2c_common->bus_id)) अणु
		pci_warn(privdata->pci_dev,
			 "bus %d attempting to unlock C2P locked by bus %d\n",
			 i2c_common->bus_id, privdata->c2p_lock_busid);
		वापस;
	पूर्ण

	mutex_unlock(&privdata->c2p_lock);
पूर्ण

अटल पूर्णांक amd_mp2_cmd(काष्ठा amd_i2c_common *i2c_common,
		       जोड़ i2c_cmd_base i2c_cmd_base)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;
	व्योम __iomem *reg;

	i2c_common->reqcmd = i2c_cmd_base.s.i2c_cmd;

	reg = privdata->mmio + ((i2c_cmd_base.s.bus_id == 1) ?
				AMD_C2P_MSG1 : AMD_C2P_MSG0);
	ग_लिखोl(i2c_cmd_base.ul, reg);

	वापस 0;
पूर्ण

पूर्णांक amd_mp2_bus_enable_set(काष्ठा amd_i2c_common *i2c_common, bool enable)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;
	जोड़ i2c_cmd_base i2c_cmd_base;

	pci_dbg(privdata->pci_dev, "id: %d\n", i2c_common->bus_id);

	i2c_cmd_base.ul = 0;
	i2c_cmd_base.s.i2c_cmd = enable ? i2c_enable : i2c_disable;
	i2c_cmd_base.s.bus_id = i2c_common->bus_id;
	i2c_cmd_base.s.i2c_speed = i2c_common->i2c_speed;

	amd_mp2_c2p_mutex_lock(i2c_common);

	वापस amd_mp2_cmd(i2c_common, i2c_cmd_base);
पूर्ण
EXPORT_SYMBOL_GPL(amd_mp2_bus_enable_set);

अटल व्योम amd_mp2_cmd_rw_fill(काष्ठा amd_i2c_common *i2c_common,
				जोड़ i2c_cmd_base *i2c_cmd_base,
				क्रमागत i2c_cmd reqcmd)
अणु
	i2c_cmd_base->s.i2c_cmd = reqcmd;
	i2c_cmd_base->s.bus_id = i2c_common->bus_id;
	i2c_cmd_base->s.i2c_speed = i2c_common->i2c_speed;
	i2c_cmd_base->s.slave_addr = i2c_common->msg->addr;
	i2c_cmd_base->s.length = i2c_common->msg->len;
पूर्ण

पूर्णांक amd_mp2_rw(काष्ठा amd_i2c_common *i2c_common, क्रमागत i2c_cmd reqcmd)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;
	जोड़ i2c_cmd_base i2c_cmd_base;

	amd_mp2_cmd_rw_fill(i2c_common, &i2c_cmd_base, reqcmd);
	amd_mp2_c2p_mutex_lock(i2c_common);

	अगर (i2c_common->msg->len <= 32) अणु
		i2c_cmd_base.s.mem_type = use_c2pmsg;
		अगर (reqcmd == i2c_ग_लिखो)
			स_नकल_toio(privdata->mmio + AMD_C2P_MSG2,
				    i2c_common->msg->buf,
				    i2c_common->msg->len);
	पूर्ण अन्यथा अणु
		i2c_cmd_base.s.mem_type = use_dram;
		ग_लिखोq((u64)i2c_common->dma_addr,
		       privdata->mmio + AMD_C2P_MSG2);
	पूर्ण

	वापस amd_mp2_cmd(i2c_common, i2c_cmd_base);
पूर्ण
EXPORT_SYMBOL_GPL(amd_mp2_rw);

अटल व्योम amd_mp2_pci_check_rw_event(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;
	काष्ठा pci_dev *pdev = privdata->pci_dev;
	पूर्णांक len = i2c_common->eventval.r.length;
	u32 slave_addr = i2c_common->eventval.r.slave_addr;
	bool err = false;

	अगर (unlikely(len != i2c_common->msg->len)) अणु
		pci_err(pdev, "length %d in event doesn't match buffer length %d!\n",
			len, i2c_common->msg->len);
		err = true;
	पूर्ण

	अगर (unlikely(slave_addr != i2c_common->msg->addr)) अणु
		pci_err(pdev, "unexpected slave address %x (expected: %x)!\n",
			slave_addr, i2c_common->msg->addr);
		err = true;
	पूर्ण

	अगर (!err)
		i2c_common->cmd_success = true;
पूर्ण

अटल व्योम __amd_mp2_process_event(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;
	काष्ठा pci_dev *pdev = privdata->pci_dev;
	क्रमागत status_type sts = i2c_common->eventval.r.status;
	क्रमागत response_type res = i2c_common->eventval.r.response;
	पूर्णांक len = i2c_common->eventval.r.length;

	अगर (res != command_success) अणु
		अगर (res != command_failed)
			pci_err(pdev, "invalid response to i2c command!\n");
		वापस;
	पूर्ण

	चयन (i2c_common->reqcmd) अणु
	हाल i2c_पढ़ो:
		अगर (sts == i2c_पढ़ोcomplete_event) अणु
			amd_mp2_pci_check_rw_event(i2c_common);
			अगर (len <= 32)
				स_नकल_fromio(i2c_common->msg->buf,
					      privdata->mmio + AMD_C2P_MSG2,
					      len);
		पूर्ण अन्यथा अगर (sts != i2c_पढ़ोfail_event) अणु
			pci_err(pdev, "invalid i2c status after read (%d)!\n", sts);
		पूर्ण
		अवरोध;
	हाल i2c_ग_लिखो:
		अगर (sts == i2c_ग_लिखोcomplete_event)
			amd_mp2_pci_check_rw_event(i2c_common);
		अन्यथा अगर (sts != i2c_ग_लिखोfail_event)
			pci_err(pdev, "invalid i2c status after write (%d)!\n", sts);
		अवरोध;
	हाल i2c_enable:
		अगर (sts == i2c_busenable_complete)
			i2c_common->cmd_success = true;
		अन्यथा अगर (sts != i2c_busenable_failed)
			pci_err(pdev, "invalid i2c status after bus enable (%d)!\n", sts);
		अवरोध;
	हाल i2c_disable:
		अगर (sts == i2c_busdisable_complete)
			i2c_common->cmd_success = true;
		अन्यथा अगर (sts != i2c_busdisable_failed)
			pci_err(pdev, "invalid i2c status after bus disable (%d)!\n", sts);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम amd_mp2_process_event(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;
	काष्ठा pci_dev *pdev = privdata->pci_dev;

	अगर (unlikely(i2c_common->reqcmd == i2c_none)) अणु
		pci_warn(pdev, "received msg but no cmd was sent (bus = %d)!\n",
			 i2c_common->bus_id);
		वापस;
	पूर्ण

	__amd_mp2_process_event(i2c_common);

	i2c_common->reqcmd = i2c_none;
	amd_mp2_c2p_mutex_unlock(i2c_common);
पूर्ण
EXPORT_SYMBOL_GPL(amd_mp2_process_event);

अटल irqवापस_t amd_mp2_irq_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा amd_mp2_dev *privdata = dev;
	काष्ठा pci_dev *pdev = privdata->pci_dev;
	काष्ठा amd_i2c_common *i2c_common;
	u32 val;
	अचिन्हित पूर्णांक bus_id;
	व्योम __iomem *reg;
	क्रमागत irqवापस ret = IRQ_NONE;

	क्रम (bus_id = 0; bus_id < 2; bus_id++) अणु
		i2c_common = privdata->busses[bus_id];
		अगर (!i2c_common)
			जारी;

		reg = privdata->mmio + ((bus_id == 0) ?
					AMD_P2C_MSG1 : AMD_P2C_MSG2);
		val = पढ़ोl(reg);
		अगर (val != 0) अणु
			ग_लिखोl(0, reg);
			ग_लिखोl(0, privdata->mmio + AMD_P2C_MSG_INTEN);
			i2c_common->eventval.ul = val;
			i2c_common->cmd_completion(i2c_common);

			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	अगर (ret != IRQ_HANDLED) अणु
		val = पढ़ोl(privdata->mmio + AMD_P2C_MSG_INTEN);
		अगर (val != 0) अणु
			ग_लिखोl(0, privdata->mmio + AMD_P2C_MSG_INTEN);
			pci_warn(pdev, "received irq without message\n");
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम amd_mp2_rw_समयout(काष्ठा amd_i2c_common *i2c_common)
अणु
	i2c_common->reqcmd = i2c_none;
	amd_mp2_c2p_mutex_unlock(i2c_common);
पूर्ण
EXPORT_SYMBOL_GPL(amd_mp2_rw_समयout);

पूर्णांक amd_mp2_रेजिस्टर_cb(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;
	काष्ठा pci_dev *pdev = privdata->pci_dev;

	अगर (i2c_common->bus_id > 1)
		वापस -EINVAL;

	अगर (privdata->busses[i2c_common->bus_id]) अणु
		pci_err(pdev, "Bus %d already taken!\n", i2c_common->bus_id);
		वापस -EINVAL;
	पूर्ण

	privdata->busses[i2c_common->bus_id] = i2c_common;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amd_mp2_रेजिस्टर_cb);

पूर्णांक amd_mp2_unरेजिस्टर_cb(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_mp2_dev *privdata = i2c_common->mp2_dev;

	privdata->busses[i2c_common->bus_id] = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amd_mp2_unरेजिस्टर_cb);

अटल व्योम amd_mp2_clear_reg(काष्ठा amd_mp2_dev *privdata)
अणु
	पूर्णांक reg;

	क्रम (reg = AMD_C2P_MSG0; reg <= AMD_C2P_MSG9; reg += 4)
		ग_लिखोl(0, privdata->mmio + reg);

	क्रम (reg = AMD_P2C_MSG1; reg <= AMD_P2C_MSG2; reg += 4)
		ग_लिखोl(0, privdata->mmio + reg);
पूर्ण

अटल पूर्णांक amd_mp2_pci_init(काष्ठा amd_mp2_dev *privdata,
			    काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक rc;

	pci_set_drvdata(pci_dev, privdata);

	rc = pcim_enable_device(pci_dev);
	अगर (rc) अणु
		pci_err(pci_dev, "Failed to enable MP2 PCI device\n");
		जाओ err_pci_enable;
	पूर्ण

	rc = pcim_iomap_regions(pci_dev, 1 << 2, pci_name(pci_dev));
	अगर (rc) अणु
		pci_err(pci_dev, "I/O memory remapping failed\n");
		जाओ err_pci_enable;
	पूर्ण
	privdata->mmio = pcim_iomap_table(pci_dev)[2];

	pci_set_master(pci_dev);

	rc = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		rc = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32));
		अगर (rc)
			जाओ err_dma_mask;
	पूर्ण

	/* Set up पूर्णांकx irq */
	ग_लिखोl(0, privdata->mmio + AMD_P2C_MSG_INTEN);
	pci_पूर्णांकx(pci_dev, 1);
	rc = devm_request_irq(&pci_dev->dev, pci_dev->irq, amd_mp2_irq_isr,
			      IRQF_SHARED, dev_name(&pci_dev->dev), privdata);
	अगर (rc)
		pci_err(pci_dev, "Failure requesting irq %i: %d\n",
			pci_dev->irq, rc);

	वापस rc;

err_dma_mask:
	pci_clear_master(pci_dev);
err_pci_enable:
	pci_set_drvdata(pci_dev, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक amd_mp2_pci_probe(काष्ठा pci_dev *pci_dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा amd_mp2_dev *privdata;
	पूर्णांक rc;

	privdata = devm_kzalloc(&pci_dev->dev, माप(*privdata), GFP_KERNEL);
	अगर (!privdata)
		वापस -ENOMEM;

	privdata->pci_dev = pci_dev;
	rc = amd_mp2_pci_init(privdata, pci_dev);
	अगर (rc)
		वापस rc;

	mutex_init(&privdata->c2p_lock);

	pm_runसमय_set_स्वतःsuspend_delay(&pci_dev->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&pci_dev->dev);
	pm_runसमय_put_स्वतःsuspend(&pci_dev->dev);
	pm_runसमय_allow(&pci_dev->dev);

	privdata->probed = true;

	pci_info(pci_dev, "MP2 device registered.\n");
	वापस 0;
पूर्ण

अटल व्योम amd_mp2_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा amd_mp2_dev *privdata = pci_get_drvdata(pci_dev);

	pm_runसमय_क्रमbid(&pci_dev->dev);
	pm_runसमय_get_noresume(&pci_dev->dev);

	pci_पूर्णांकx(pci_dev, 0);
	pci_clear_master(pci_dev);

	amd_mp2_clear_reg(privdata);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक amd_mp2_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा amd_mp2_dev *privdata = pci_get_drvdata(pci_dev);
	काष्ठा amd_i2c_common *i2c_common;
	अचिन्हित पूर्णांक bus_id;
	पूर्णांक ret = 0;

	क्रम (bus_id = 0; bus_id < 2; bus_id++) अणु
		i2c_common = privdata->busses[bus_id];
		अगर (i2c_common)
			i2c_common->suspend(i2c_common);
	पूर्ण

	ret = pci_save_state(pci_dev);
	अगर (ret) अणु
		pci_err(pci_dev, "pci_save_state failed = %d\n", ret);
		वापस ret;
	पूर्ण

	pci_disable_device(pci_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक amd_mp2_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा amd_mp2_dev *privdata = pci_get_drvdata(pci_dev);
	काष्ठा amd_i2c_common *i2c_common;
	अचिन्हित पूर्णांक bus_id;
	पूर्णांक ret = 0;

	pci_restore_state(pci_dev);
	ret = pci_enable_device(pci_dev);
	अगर (ret < 0) अणु
		pci_err(pci_dev, "pci_enable_device failed = %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (bus_id = 0; bus_id < 2; bus_id++) अणु
		i2c_common = privdata->busses[bus_id];
		अगर (i2c_common) अणु
			ret = i2c_common->resume(i2c_common);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(amd_mp2_pci_pm_ops, amd_mp2_pci_suspend,
			    amd_mp2_pci_resume, शून्य);
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा pci_device_id amd_mp2_pci_tbl[] = अणु
	अणुPCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_MP2)पूर्ण,
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd_mp2_pci_tbl);

अटल काष्ठा pci_driver amd_mp2_pci_driver = अणु
	.name		= "i2c_amd_mp2",
	.id_table	= amd_mp2_pci_tbl,
	.probe		= amd_mp2_pci_probe,
	.हटाओ		= amd_mp2_pci_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver = अणु
		.pm	= &amd_mp2_pci_pm_ops,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;
module_pci_driver(amd_mp2_pci_driver);

काष्ठा amd_mp2_dev *amd_mp2_find_device(व्योम)
अणु
	काष्ठा device *dev;
	काष्ठा pci_dev *pci_dev;

	dev = driver_find_next_device(&amd_mp2_pci_driver.driver, शून्य);
	अगर (!dev)
		वापस शून्य;

	pci_dev = to_pci_dev(dev);
	वापस (काष्ठा amd_mp2_dev *)pci_get_drvdata(pci_dev);
पूर्ण
EXPORT_SYMBOL_GPL(amd_mp2_find_device);

MODULE_DESCRIPTION("AMD(R) PCI-E MP2 I2C Controller Driver");
MODULE_AUTHOR("Shyam Sundar S K <Shyam-sundar.S-k@amd.com>");
MODULE_AUTHOR("Elie Morisse <syniurge@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
