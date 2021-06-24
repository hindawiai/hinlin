<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * AMD MP2 platक्रमm driver
 *
 * Setup the I2C adapters क्रमागतerated in the ACPI namespace.
 * MP2 controllers have 2 separate busses, up to 2 I2C adapters may be listed.
 *
 * Authors: Nehal Bakulchandra Shah <Nehal-bakulchandra.shah@amd.com>
 *          Elie Morisse <syniurge@gmail.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "i2c-amd-mp2.h"

#घोषणा AMD_MP2_I2C_MAX_RW_LENGTH ((1 << 12) - 1)
#घोषणा AMD_I2C_TIMEOUT (msecs_to_jअगरfies(250))

/**
 * काष्ठा amd_i2c_dev - MP2 bus/i2c adapter context
 * @common: shared context with the MP2 PCI driver
 * @pdev: platक्रमm driver node
 * @adap: i2c adapter
 * @cmd_complete: xfer completion object
 */
काष्ठा amd_i2c_dev अणु
	काष्ठा amd_i2c_common common;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा i2c_adapter adap;
	काष्ठा completion cmd_complete;
पूर्ण;

#घोषणा amd_i2c_dev_common(__common) \
	container_of(__common, काष्ठा amd_i2c_dev, common)

अटल पूर्णांक i2c_amd_dma_map(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा device *dev_pci = &i2c_common->mp2_dev->pci_dev->dev;
	काष्ठा amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);
	क्रमागत dma_data_direction dma_direction =
			i2c_common->msg->flags & I2C_M_RD ?
			DMA_FROM_DEVICE : DMA_TO_DEVICE;

	i2c_common->dma_buf = i2c_get_dma_safe_msg_buf(i2c_common->msg, 0);
	i2c_common->dma_addr = dma_map_single(dev_pci, i2c_common->dma_buf,
					      i2c_common->msg->len,
					      dma_direction);

	अगर (unlikely(dma_mapping_error(dev_pci, i2c_common->dma_addr))) अणु
		dev_err(&i2c_dev->pdev->dev,
			"Error while mapping dma buffer %p\n",
			i2c_common->dma_buf);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i2c_amd_dma_unmap(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा device *dev_pci = &i2c_common->mp2_dev->pci_dev->dev;
	क्रमागत dma_data_direction dma_direction =
			i2c_common->msg->flags & I2C_M_RD ?
			DMA_FROM_DEVICE : DMA_TO_DEVICE;

	dma_unmap_single(dev_pci, i2c_common->dma_addr,
			 i2c_common->msg->len, dma_direction);

	i2c_put_dma_safe_msg_buf(i2c_common->dma_buf, i2c_common->msg, true);
पूर्ण

अटल व्योम i2c_amd_start_cmd(काष्ठा amd_i2c_dev *i2c_dev)
अणु
	काष्ठा amd_i2c_common *i2c_common = &i2c_dev->common;

	reinit_completion(&i2c_dev->cmd_complete);
	i2c_common->cmd_success = false;
पूर्ण

अटल व्योम i2c_amd_cmd_completion(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);
	जोड़ i2c_event *event = &i2c_common->eventval;

	अगर (event->r.status == i2c_पढ़ोcomplete_event)
		dev_dbg(&i2c_dev->pdev->dev, "readdata:%*ph\n", event->r.length,
			i2c_common->msg->buf);

	complete(&i2c_dev->cmd_complete);
पूर्ण

अटल पूर्णांक i2c_amd_check_cmd_completion(काष्ठा amd_i2c_dev *i2c_dev)
अणु
	काष्ठा amd_i2c_common *i2c_common = &i2c_dev->common;
	अचिन्हित दीर्घ समयout;

	समयout = रुको_क्रम_completion_समयout(&i2c_dev->cmd_complete,
					      i2c_dev->adap.समयout);

	अगर ((i2c_common->reqcmd == i2c_पढ़ो ||
	     i2c_common->reqcmd == i2c_ग_लिखो) &&
	    i2c_common->msg->len > 32)
		i2c_amd_dma_unmap(i2c_common);

	अगर (समयout == 0) अणु
		amd_mp2_rw_समयout(i2c_common);
		वापस -ETIMEDOUT;
	पूर्ण

	amd_mp2_process_event(i2c_common);

	अगर (!i2c_common->cmd_success)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_amd_enable_set(काष्ठा amd_i2c_dev *i2c_dev, bool enable)
अणु
	काष्ठा amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_amd_start_cmd(i2c_dev);
	amd_mp2_bus_enable_set(i2c_common, enable);

	वापस i2c_amd_check_cmd_completion(i2c_dev);
पूर्ण

अटल पूर्णांक i2c_amd_xfer_msg(काष्ठा amd_i2c_dev *i2c_dev, काष्ठा i2c_msg *pmsg)
अणु
	काष्ठा amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_amd_start_cmd(i2c_dev);
	i2c_common->msg = pmsg;

	अगर (pmsg->len > 32)
		अगर (i2c_amd_dma_map(i2c_common))
			वापस -EIO;

	अगर (pmsg->flags & I2C_M_RD)
		amd_mp2_rw(i2c_common, i2c_पढ़ो);
	अन्यथा
		amd_mp2_rw(i2c_common, i2c_ग_लिखो);

	वापस i2c_amd_check_cmd_completion(i2c_dev);
पूर्ण

अटल पूर्णांक i2c_amd_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा amd_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	पूर्णांक i;
	काष्ठा i2c_msg *pmsg;
	पूर्णांक err = 0;

	/* the adapter might have been deleted जबतक रुकोing क्रम the bus lock */
	अगर (unlikely(!i2c_dev->common.mp2_dev))
		वापस -EINVAL;

	amd_mp2_pm_runसमय_get(i2c_dev->common.mp2_dev);

	क्रम (i = 0; i < num; i++) अणु
		pmsg = &msgs[i];
		err = i2c_amd_xfer_msg(i2c_dev, pmsg);
		अगर (err)
			अवरोध;
	पूर्ण

	amd_mp2_pm_runसमय_put(i2c_dev->common.mp2_dev);
	वापस err ? err : num;
पूर्ण

अटल u32 i2c_amd_func(काष्ठा i2c_adapter *a)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_amd_algorithm = अणु
	.master_xfer = i2c_amd_xfer,
	.functionality = i2c_amd_func,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2c_amd_suspend(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);

	i2c_amd_enable_set(i2c_dev, false);
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_amd_resume(काष्ठा amd_i2c_common *i2c_common)
अणु
	काष्ठा amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);

	वापस i2c_amd_enable_set(i2c_dev, true);
पूर्ण
#पूर्ण_अगर

अटल स्थिर u32 supported_speeds[] = अणु
	I2C_MAX_HIGH_SPEED_MODE_FREQ,
	I2C_MAX_TURBO_MODE_FREQ,
	I2C_MAX_FAST_MODE_PLUS_FREQ,
	I2C_MAX_FAST_MODE_FREQ,
	I2C_MAX_STANDARD_MODE_FREQ,
पूर्ण;

अटल क्रमागत speed_क्रमागत i2c_amd_get_bus_speed(काष्ठा platक्रमm_device *pdev)
अणु
	u32 acpi_speed;
	पूर्णांक i;

	acpi_speed = i2c_acpi_find_bus_speed(&pdev->dev);
	/* round करोwn to the lowest standard speed */
	क्रम (i = 0; i < ARRAY_SIZE(supported_speeds); i++) अणु
		अगर (acpi_speed >= supported_speeds[i])
			अवरोध;
	पूर्ण
	acpi_speed = i < ARRAY_SIZE(supported_speeds) ? supported_speeds[i] : 0;

	चयन (acpi_speed) अणु
	हाल I2C_MAX_STANDARD_MODE_FREQ:
		वापस speed100k;
	हाल I2C_MAX_FAST_MODE_FREQ:
		वापस speed400k;
	हाल I2C_MAX_FAST_MODE_PLUS_FREQ:
		वापस speed1000k;
	हाल I2C_MAX_TURBO_MODE_FREQ:
		वापस speed1400k;
	हाल I2C_MAX_HIGH_SPEED_MODE_FREQ:
		वापस speed3400k;
	शेष:
		वापस speed400k;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा i2c_adapter_quirks amd_i2c_dev_quirks = अणु
	.max_पढ़ो_len = AMD_MP2_I2C_MAX_RW_LENGTH,
	.max_ग_लिखो_len = AMD_MP2_I2C_MAX_RW_LENGTH,
पूर्ण;

अटल पूर्णांक i2c_amd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा amd_i2c_dev *i2c_dev;
	acpi_handle handle = ACPI_HANDLE(&pdev->dev);
	काष्ठा acpi_device *adev;
	काष्ठा amd_mp2_dev *mp2_dev;
	स्थिर अक्षर *uid;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस -ENODEV;

	/* The ACPI namespace करोesn't contain inक्रमmation about which MP2 PCI
	 * device an AMDI0011 ACPI device is related to, so assume that there's
	 * only one MP2 PCI device per प्रणाली.
	 */
	mp2_dev = amd_mp2_find_device();
	अगर (!mp2_dev || !mp2_dev->probed)
		/* The MP2 PCI device should get probed later */
		वापस -EPROBE_DEFER;

	i2c_dev = devm_kzalloc(&pdev->dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	i2c_dev->common.mp2_dev = mp2_dev;
	i2c_dev->pdev = pdev;
	platक्रमm_set_drvdata(pdev, i2c_dev);

	i2c_dev->common.cmd_completion = &i2c_amd_cmd_completion;
#अगर_घोषित CONFIG_PM
	i2c_dev->common.suspend = &i2c_amd_suspend;
	i2c_dev->common.resume = &i2c_amd_resume;
#पूर्ण_अगर

	uid = adev->pnp.unique_id;
	अगर (!uid) अणु
		dev_err(&pdev->dev, "missing UID/bus id!\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (म_भेद(uid, "0") == 0) अणु
		i2c_dev->common.bus_id = 0;
	पूर्ण अन्यथा अगर (म_भेद(uid, "1") == 0) अणु
		i2c_dev->common.bus_id = 1;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "incorrect UID/bus id \"%s\"!\n", uid);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&pdev->dev, "bus id is %u\n", i2c_dev->common.bus_id);

	/* Register the adapter */
	amd_mp2_pm_runसमय_get(mp2_dev);

	i2c_dev->common.reqcmd = i2c_none;
	अगर (amd_mp2_रेजिस्टर_cb(&i2c_dev->common))
		वापस -EINVAL;
	device_link_add(&i2c_dev->pdev->dev, &mp2_dev->pci_dev->dev,
			DL_FLAG_AUTOREMOVE_CONSUMER);

	i2c_dev->common.i2c_speed = i2c_amd_get_bus_speed(pdev);

	/* Setup i2c adapter description */
	i2c_dev->adap.owner = THIS_MODULE;
	i2c_dev->adap.algo = &i2c_amd_algorithm;
	i2c_dev->adap.quirks = &amd_i2c_dev_quirks;
	i2c_dev->adap.dev.parent = &pdev->dev;
	i2c_dev->adap.algo_data = i2c_dev;
	i2c_dev->adap.समयout = AMD_I2C_TIMEOUT;
	ACPI_COMPANION_SET(&i2c_dev->adap.dev, ACPI_COMPANION(&pdev->dev));
	i2c_dev->adap.dev.of_node = pdev->dev.of_node;
	snम_लिखो(i2c_dev->adap.name, माप(i2c_dev->adap.name),
		 "AMD MP2 i2c bus %u", i2c_dev->common.bus_id);
	i2c_set_adapdata(&i2c_dev->adap, i2c_dev);

	init_completion(&i2c_dev->cmd_complete);

	/* Enable the bus */
	अगर (i2c_amd_enable_set(i2c_dev, true))
		dev_err(&pdev->dev, "initial bus enable failed\n");

	/* Attach to the i2c layer */
	ret = i2c_add_adapter(&i2c_dev->adap);

	amd_mp2_pm_runसमय_put(mp2_dev);

	अगर (ret < 0)
		dev_err(&pdev->dev, "i2c add adapter failed = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_amd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amd_i2c_dev *i2c_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_lock_bus(&i2c_dev->adap, I2C_LOCK_ROOT_ADAPTER);

	i2c_amd_enable_set(i2c_dev, false);
	amd_mp2_unरेजिस्टर_cb(i2c_common);
	i2c_common->mp2_dev = शून्य;

	i2c_unlock_bus(&i2c_dev->adap, I2C_LOCK_ROOT_ADAPTER);

	i2c_del_adapter(&i2c_dev->adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id i2c_amd_acpi_match[] = अणु
	अणु "AMDI0011" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, i2c_amd_acpi_match);

अटल काष्ठा platक्रमm_driver i2c_amd_plat_driver = अणु
	.probe = i2c_amd_probe,
	.हटाओ = i2c_amd_हटाओ,
	.driver = अणु
		.name = "i2c_amd_mp2",
		.acpi_match_table = ACPI_PTR(i2c_amd_acpi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(i2c_amd_plat_driver);

MODULE_DESCRIPTION("AMD(R) MP2 I2C Platform Driver");
MODULE_AUTHOR("Nehal Shah <nehal-bakulchandra.shah@amd.com>");
MODULE_AUTHOR("Elie Morisse <syniurge@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
