<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2016, Synaptics Incorporated
 * Copyright (C) 2016 Zodiac Inflight Innovations
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rmi.h>
#समावेश <linux/firmware.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/bitops.h>

#समावेश "rmi_driver.h"
#समावेश "rmi_f34.h"

अटल पूर्णांक rmi_f34_ग_लिखो_bootloader_id(काष्ठा f34_data *f34)
अणु
	काष्ठा rmi_function *fn = f34->fn;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	u8 bootloader_id[F34_BOOTLOADER_ID_LEN];
	पूर्णांक ret;

	ret = rmi_पढ़ो_block(rmi_dev, fn->fd.query_base_addr,
			     bootloader_id, माप(bootloader_id));
	अगर (ret) अणु
		dev_err(&fn->dev, "%s: Reading bootloader ID failed: %d\n",
				__func__, ret);
		वापस ret;
	पूर्ण

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "%s: writing bootloader id '%c%c'\n",
			__func__, bootloader_id[0], bootloader_id[1]);

	ret = rmi_ग_लिखो_block(rmi_dev,
			      fn->fd.data_base_addr + F34_BLOCK_DATA_OFFSET,
			      bootloader_id, माप(bootloader_id));
	अगर (ret) अणु
		dev_err(&fn->dev, "Failed to write bootloader ID: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34_command(काष्ठा f34_data *f34, u8 command,
			   अचिन्हित पूर्णांक समयout, bool ग_लिखो_bl_id)
अणु
	काष्ठा rmi_function *fn = f34->fn;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	पूर्णांक ret;

	अगर (ग_लिखो_bl_id) अणु
		ret = rmi_f34_ग_लिखो_bootloader_id(f34);
		अगर (ret)
			वापस ret;
	पूर्ण

	init_completion(&f34->v5.cmd_करोne);

	ret = rmi_पढ़ो(rmi_dev, f34->v5.ctrl_address, &f34->v5.status);
	अगर (ret) अणु
		dev_err(&f34->fn->dev,
			"%s: Failed to read cmd register: %d (command %#02x)\n",
			__func__, ret, command);
		वापस ret;
	पूर्ण

	f34->v5.status |= command & 0x0f;

	ret = rmi_ग_लिखो(rmi_dev, f34->v5.ctrl_address, f34->v5.status);
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev,
			"Failed to write F34 command %#02x: %d\n",
			command, ret);
		वापस ret;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&f34->v5.cmd_करोne,
				msecs_to_jअगरfies(समयout))) अणु

		ret = rmi_पढ़ो(rmi_dev, f34->v5.ctrl_address, &f34->v5.status);
		अगर (ret) अणु
			dev_err(&f34->fn->dev,
				"%s: cmd %#02x timed out: %d\n",
				__func__, command, ret);
			वापस ret;
		पूर्ण

		अगर (f34->v5.status & 0x7f) अणु
			dev_err(&f34->fn->dev,
				"%s: cmd %#02x timed out, status: %#02x\n",
				__func__, command, f34->v5.status);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t rmi_f34_attention(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा rmi_function *fn = ctx;
	काष्ठा f34_data *f34 = dev_get_drvdata(&fn->dev);
	पूर्णांक ret;
	u8 status;

	अगर (f34->bl_version == 5) अणु
		ret = rmi_पढ़ो(f34->fn->rmi_dev, f34->v5.ctrl_address,
			       &status);
		rmi_dbg(RMI_DEBUG_FN, &fn->dev, "%s: status: %#02x, ret: %d\n",
			__func__, status, ret);

		अगर (!ret && !(status & 0x7f))
			complete(&f34->v5.cmd_करोne);
	पूर्ण अन्यथा अणु
		ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
				     f34->fn->fd.data_base_addr +
						f34->v7.off.flash_status,
				     &status, माप(status));
		rmi_dbg(RMI_DEBUG_FN, &fn->dev, "%s: status: %#02x, ret: %d\n",
			__func__, status, ret);

		अगर (!ret && !(status & 0x1f))
			complete(&f34->v7.cmd_करोne);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rmi_f34_ग_लिखो_blocks(काष्ठा f34_data *f34, स्थिर व्योम *data,
				पूर्णांक block_count, u8 command)
अणु
	काष्ठा rmi_function *fn = f34->fn;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	u16 address = fn->fd.data_base_addr + F34_BLOCK_DATA_OFFSET;
	u8 start_address[] = अणु 0, 0 पूर्ण;
	पूर्णांक i;
	पूर्णांक ret;

	ret = rmi_ग_लिखो_block(rmi_dev, fn->fd.data_base_addr,
			      start_address, माप(start_address));
	अगर (ret) अणु
		dev_err(&fn->dev, "Failed to write initial zeros: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < block_count; i++) अणु
		ret = rmi_ग_लिखो_block(rmi_dev, address,
				      data, f34->v5.block_size);
		अगर (ret) अणु
			dev_err(&fn->dev,
				"failed to write block #%d: %d\n", i, ret);
			वापस ret;
		पूर्ण

		ret = rmi_f34_command(f34, command, F34_IDLE_WAIT_MS, false);
		अगर (ret) अणु
			dev_err(&fn->dev,
				"Failed to write command for block #%d: %d\n",
				i, ret);
			वापस ret;
		पूर्ण

		rmi_dbg(RMI_DEBUG_FN, &fn->dev, "wrote block %d of %d\n",
			i + 1, block_count);

		data += f34->v5.block_size;
		f34->update_progress += f34->v5.block_size;
		f34->update_status = (f34->update_progress * 100) /
			f34->update_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34_ग_लिखो_firmware(काष्ठा f34_data *f34, स्थिर व्योम *data)
अणु
	वापस rmi_f34_ग_लिखो_blocks(f34, data, f34->v5.fw_blocks,
				    F34_WRITE_FW_BLOCK);
पूर्ण

अटल पूर्णांक rmi_f34_ग_लिखो_config(काष्ठा f34_data *f34, स्थिर व्योम *data)
अणु
	वापस rmi_f34_ग_लिखो_blocks(f34, data, f34->v5.config_blocks,
				    F34_WRITE_CONFIG_BLOCK);
पूर्ण

अटल पूर्णांक rmi_f34_enable_flash(काष्ठा f34_data *f34)
अणु
	वापस rmi_f34_command(f34, F34_ENABLE_FLASH_PROG,
			       F34_ENABLE_WAIT_MS, true);
पूर्ण

अटल पूर्णांक rmi_f34_flash_firmware(काष्ठा f34_data *f34,
				  स्थिर काष्ठा rmi_f34_firmware *syn_fw)
अणु
	काष्ठा rmi_function *fn = f34->fn;
	u32 image_size = le32_to_cpu(syn_fw->image_size);
	u32 config_size = le32_to_cpu(syn_fw->config_size);
	पूर्णांक ret;

	f34->update_progress = 0;
	f34->update_size = image_size + config_size;

	अगर (image_size) अणु
		dev_info(&fn->dev, "Erasing firmware...\n");
		ret = rmi_f34_command(f34, F34_ERASE_ALL,
				      F34_ERASE_WAIT_MS, true);
		अगर (ret)
			वापस ret;

		dev_info(&fn->dev, "Writing firmware (%d bytes)...\n",
			 image_size);
		ret = rmi_f34_ग_लिखो_firmware(f34, syn_fw->data);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (config_size) अणु
		/*
		 * We only need to erase config अगर we haven't updated
		 * firmware.
		 */
		अगर (!image_size) अणु
			dev_info(&fn->dev, "Erasing config...\n");
			ret = rmi_f34_command(f34, F34_ERASE_CONFIG,
					      F34_ERASE_WAIT_MS, true);
			अगर (ret)
				वापस ret;
		पूर्ण

		dev_info(&fn->dev, "Writing config (%d bytes)...\n",
			 config_size);
		ret = rmi_f34_ग_लिखो_config(f34, &syn_fw->data[image_size]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34_update_firmware(काष्ठा f34_data *f34,
				   स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा rmi_f34_firmware *syn_fw =
				(स्थिर काष्ठा rmi_f34_firmware *)fw->data;
	u32 image_size = le32_to_cpu(syn_fw->image_size);
	u32 config_size = le32_to_cpu(syn_fw->config_size);
	पूर्णांक ret;

	BUILD_BUG_ON(दुरत्व(काष्ठा rmi_f34_firmware, data) !=
			F34_FW_IMAGE_OFFSET);

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
		"FW size:%zd, checksum:%08x, image_size:%d, config_size:%d\n",
		fw->size,
		le32_to_cpu(syn_fw->checksum),
		image_size, config_size);

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
		"FW bootloader_id:%02x, product_id:%.*s, info: %02x%02x\n",
		syn_fw->bootloader_version,
		(पूर्णांक)माप(syn_fw->product_id), syn_fw->product_id,
		syn_fw->product_info[0], syn_fw->product_info[1]);

	अगर (image_size && image_size != f34->v5.fw_blocks * f34->v5.block_size) अणु
		dev_err(&f34->fn->dev,
			"Bad firmware image: fw size %d, expected %d\n",
			image_size, f34->v5.fw_blocks * f34->v5.block_size);
		ret = -EILSEQ;
		जाओ out;
	पूर्ण

	अगर (config_size &&
	    config_size != f34->v5.config_blocks * f34->v5.block_size) अणु
		dev_err(&f34->fn->dev,
			"Bad firmware image: config size %d, expected %d\n",
			config_size,
			f34->v5.config_blocks * f34->v5.block_size);
		ret = -EILSEQ;
		जाओ out;
	पूर्ण

	अगर (image_size && !config_size) अणु
		dev_err(&f34->fn->dev, "Bad firmware image: no config data\n");
		ret = -EILSEQ;
		जाओ out;
	पूर्ण

	dev_info(&f34->fn->dev, "Firmware image OK\n");
	mutex_lock(&f34->v5.flash_mutex);

	ret = rmi_f34_flash_firmware(f34, syn_fw);

	mutex_unlock(&f34->v5.flash_mutex);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक rmi_f34_status(काष्ठा rmi_function *fn)
अणु
	काष्ठा f34_data *f34 = dev_get_drvdata(&fn->dev);

	/*
	 * The status is the percentage complete, or once complete,
	 * zero क्रम success or a negative वापस code.
	 */
	वापस f34->update_status;
पूर्ण

अटल sमाप_प्रकार rmi_driver_bootloader_id_show(काष्ठा device *dev,
					     काष्ठा device_attribute *dattr,
					     अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	काष्ठा rmi_function *fn = data->f34_container;
	काष्ठा f34_data *f34;

	अगर (fn) अणु
		f34 = dev_get_drvdata(&fn->dev);

		अगर (f34->bl_version == 5)
			वापस scnम_लिखो(buf, PAGE_SIZE, "%c%c\n",
					 f34->bootloader_id[0],
					 f34->bootloader_id[1]);
		अन्यथा
			वापस scnम_लिखो(buf, PAGE_SIZE, "V%d.%d\n",
					 f34->bootloader_id[1],
					 f34->bootloader_id[0]);
	पूर्ण

	वापस 0;
पूर्ण

अटल DEVICE_ATTR(bootloader_id, 0444, rmi_driver_bootloader_id_show, शून्य);

अटल sमाप_प्रकार rmi_driver_configuration_id_show(काष्ठा device *dev,
						काष्ठा device_attribute *dattr,
						अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	काष्ठा rmi_function *fn = data->f34_container;
	काष्ठा f34_data *f34;

	अगर (fn) अणु
		f34 = dev_get_drvdata(&fn->dev);

		वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", f34->configuration_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल DEVICE_ATTR(configuration_id, 0444,
		   rmi_driver_configuration_id_show, शून्य);

अटल पूर्णांक rmi_firmware_update(काष्ठा rmi_driver_data *data,
			       स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा rmi_device *rmi_dev = data->rmi_dev;
	काष्ठा device *dev = &rmi_dev->dev;
	काष्ठा f34_data *f34;
	पूर्णांक ret;

	अगर (!data->f34_container) अणु
		dev_warn(dev, "%s: No F34 present!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	f34 = dev_get_drvdata(&data->f34_container->dev);

	अगर (f34->bl_version == 7) अणु
		अगर (data->pdt_props & HAS_BSR) अणु
			dev_err(dev, "%s: LTS not supported\n", __func__);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (f34->bl_version != 5) अणु
		dev_warn(dev, "F34 V%d not supported!\n",
			 data->f34_container->fd.function_version);
		वापस -ENODEV;
	पूर्ण

	/* Enter flash mode */
	अगर (f34->bl_version == 7)
		ret = rmi_f34v7_start_reflash(f34, fw);
	अन्यथा
		ret = rmi_f34_enable_flash(f34);
	अगर (ret)
		वापस ret;

	rmi_disable_irq(rmi_dev, false);

	/* Tear करोwn functions and re-probe */
	rmi_मुक्त_function_list(rmi_dev);

	ret = rmi_probe_पूर्णांकerrupts(data);
	अगर (ret)
		वापस ret;

	ret = rmi_init_functions(data);
	अगर (ret)
		वापस ret;

	अगर (!data->bootloader_mode || !data->f34_container) अणु
		dev_warn(dev, "%s: No F34 present or not in bootloader!\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	rmi_enable_irq(rmi_dev, false);

	f34 = dev_get_drvdata(&data->f34_container->dev);

	/* Perक्रमm firmware update */
	अगर (f34->bl_version == 7)
		ret = rmi_f34v7_करो_reflash(f34, fw);
	अन्यथा
		ret = rmi_f34_update_firmware(f34, fw);

	अगर (ret) अणु
		f34->update_status = ret;
		dev_err(&f34->fn->dev,
			"Firmware update failed, status: %d\n", ret);
	पूर्ण अन्यथा अणु
		dev_info(&f34->fn->dev, "Firmware update complete\n");
	पूर्ण

	rmi_disable_irq(rmi_dev, false);

	/* Re-probe */
	rmi_dbg(RMI_DEBUG_FN, dev, "Re-probing device\n");
	rmi_मुक्त_function_list(rmi_dev);

	ret = rmi_scan_pdt(rmi_dev, शून्य, rmi_initial_reset);
	अगर (ret < 0)
		dev_warn(dev, "RMI reset failed!\n");

	ret = rmi_probe_पूर्णांकerrupts(data);
	अगर (ret)
		वापस ret;

	ret = rmi_init_functions(data);
	अगर (ret)
		वापस ret;

	rmi_enable_irq(rmi_dev, false);

	अगर (data->f01_container->dev.driver)
		/* Driver alपढ़ोy bound, so enable ATTN now. */
		वापस rmi_enable_sensor(rmi_dev);

	rmi_dbg(RMI_DEBUG_FN, dev, "%s complete\n", __func__);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार rmi_driver_update_fw_store(काष्ठा device *dev,
					  काष्ठा device_attribute *dattr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	अक्षर fw_name[NAME_MAX];
	स्थिर काष्ठा firmware *fw;
	माप_प्रकार copy_count = count;
	पूर्णांक ret;

	अगर (count == 0 || count >= NAME_MAX)
		वापस -EINVAL;

	अगर (buf[count - 1] == '\0' || buf[count - 1] == '\n')
		copy_count -= 1;

	म_नकलन(fw_name, buf, copy_count);
	fw_name[copy_count] = '\0';

	ret = request_firmware(&fw, fw_name, dev);
	अगर (ret)
		वापस ret;

	dev_info(dev, "Flashing %s\n", fw_name);

	ret = rmi_firmware_update(data, fw);

	release_firmware(fw);

	वापस ret ?: count;
पूर्ण

अटल DEVICE_ATTR(update_fw, 0200, शून्य, rmi_driver_update_fw_store);

अटल sमाप_प्रकार rmi_driver_update_fw_status_show(काष्ठा device *dev,
						काष्ठा device_attribute *dattr,
						अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	पूर्णांक update_status = 0;

	अगर (data->f34_container)
		update_status = rmi_f34_status(data->f34_container);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", update_status);
पूर्ण

अटल DEVICE_ATTR(update_fw_status, 0444,
		   rmi_driver_update_fw_status_show, शून्य);

अटल काष्ठा attribute *rmi_firmware_attrs[] = अणु
	&dev_attr_bootloader_id.attr,
	&dev_attr_configuration_id.attr,
	&dev_attr_update_fw.attr,
	&dev_attr_update_fw_status.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rmi_firmware_attr_group = अणु
	.attrs = rmi_firmware_attrs,
पूर्ण;

अटल पूर्णांक rmi_f34_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा f34_data *f34;
	अचिन्हित अक्षर f34_queries[9];
	bool has_config_id;
	u8 version = fn->fd.function_version;
	पूर्णांक ret;

	f34 = devm_kzalloc(&fn->dev, माप(काष्ठा f34_data), GFP_KERNEL);
	अगर (!f34)
		वापस -ENOMEM;

	f34->fn = fn;
	dev_set_drvdata(&fn->dev, f34);

	/* v5 code only supported version 0, try V7 probe */
	अगर (version > 0)
		वापस rmi_f34v7_probe(f34);

	f34->bl_version = 5;

	ret = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.query_base_addr,
			     f34_queries, माप(f34_queries));
	अगर (ret) अणु
		dev_err(&fn->dev, "%s: Failed to query properties\n",
			__func__);
		वापस ret;
	पूर्ण

	snम_लिखो(f34->bootloader_id, माप(f34->bootloader_id),
		 "%c%c", f34_queries[0], f34_queries[1]);

	mutex_init(&f34->v5.flash_mutex);
	init_completion(&f34->v5.cmd_करोne);

	f34->v5.block_size = get_unaligned_le16(&f34_queries[3]);
	f34->v5.fw_blocks = get_unaligned_le16(&f34_queries[5]);
	f34->v5.config_blocks = get_unaligned_le16(&f34_queries[7]);
	f34->v5.ctrl_address = fn->fd.data_base_addr + F34_BLOCK_DATA_OFFSET +
		f34->v5.block_size;
	has_config_id = f34_queries[2] & (1 << 2);

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "Bootloader ID: %s\n",
		f34->bootloader_id);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "Block size: %d\n",
		f34->v5.block_size);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "FW blocks: %d\n",
		f34->v5.fw_blocks);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "CFG blocks: %d\n",
		f34->v5.config_blocks);

	अगर (has_config_id) अणु
		ret = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.control_base_addr,
				     f34_queries, माप(f34_queries));
		अगर (ret) अणु
			dev_err(&fn->dev, "Failed to read F34 config ID\n");
			वापस ret;
		पूर्ण

		snम_लिखो(f34->configuration_id, माप(f34->configuration_id),
			 "%02x%02x%02x%02x",
			 f34_queries[0], f34_queries[1],
			 f34_queries[2], f34_queries[3]);

		rmi_dbg(RMI_DEBUG_FN, &fn->dev, "Configuration ID: %s\n",
			 f34->configuration_id);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rmi_f34_create_sysfs(काष्ठा rmi_device *rmi_dev)
अणु
	वापस sysfs_create_group(&rmi_dev->dev.kobj, &rmi_firmware_attr_group);
पूर्ण

व्योम rmi_f34_हटाओ_sysfs(काष्ठा rmi_device *rmi_dev)
अणु
	sysfs_हटाओ_group(&rmi_dev->dev.kobj, &rmi_firmware_attr_group);
पूर्ण

काष्ठा rmi_function_handler rmi_f34_handler = अणु
	.driver = अणु
		.name = "rmi4_f34",
	पूर्ण,
	.func = 0x34,
	.probe = rmi_f34_probe,
	.attention = rmi_f34_attention,
पूर्ण;
