<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, Zodiac Inflight Innovations
 * Copyright (c) 2007-2016, Synaptics Incorporated
 * Copyright (C) 2012 Alexandra Chin <alexandra.chin@tw.synaptics.com>
 * Copyright (C) 2012 Scott Lin <scott.lin@tw.synaptics.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rmi.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "rmi_driver.h"
#समावेश "rmi_f34.h"

अटल पूर्णांक rmi_f34v7_पढ़ो_flash_status(काष्ठा f34_data *f34)
अणु
	u8 status;
	u8 command;
	पूर्णांक ret;

	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			f34->fn->fd.data_base_addr + f34->v7.off.flash_status,
			&status,
			माप(status));
	अगर (ret < 0) अणु
		rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
			"%s: Error %d reading flash status\n", __func__, ret);
		वापस ret;
	पूर्ण

	f34->v7.in_bl_mode = status >> 7;
	f34->v7.flash_status = status & 0x1f;

	अगर (f34->v7.flash_status != 0x00) अणु
		dev_err(&f34->fn->dev, "%s: status=%d, command=0x%02x\n",
			__func__, f34->v7.flash_status, f34->v7.command);
	पूर्ण

	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			f34->fn->fd.data_base_addr + f34->v7.off.flash_cmd,
			&command,
			माप(command));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to read flash command\n",
			__func__);
		वापस ret;
	पूर्ण

	f34->v7.command = command;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_रुको_क्रम_idle(काष्ठा f34_data *f34, पूर्णांक समयout_ms)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = msecs_to_jअगरfies(समयout_ms);

	अगर (!रुको_क्रम_completion_समयout(&f34->v7.cmd_करोne, समयout)) अणु
		dev_warn(&f34->fn->dev, "%s: Timed out waiting for idle status\n",
			 __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_command_single_transaction(काष्ठा f34_data *f34,
						      u8 cmd)
अणु
	पूर्णांक ret;
	u8 base;
	काष्ठा f34v7_data_1_5 data_1_5;

	base = f34->fn->fd.data_base_addr;

	स_रखो(&data_1_5, 0, माप(data_1_5));

	चयन (cmd) अणु
	हाल v7_CMD_ERASE_ALL:
		data_1_5.partition_id = CORE_CODE_PARTITION;
		data_1_5.command = CMD_V7_ERASE_AP;
		अवरोध;
	हाल v7_CMD_ERASE_UI_FIRMWARE:
		data_1_5.partition_id = CORE_CODE_PARTITION;
		data_1_5.command = CMD_V7_ERASE;
		अवरोध;
	हाल v7_CMD_ERASE_BL_CONFIG:
		data_1_5.partition_id = GLOBAL_PARAMETERS_PARTITION;
		data_1_5.command = CMD_V7_ERASE;
		अवरोध;
	हाल v7_CMD_ERASE_UI_CONFIG:
		data_1_5.partition_id = CORE_CONFIG_PARTITION;
		data_1_5.command = CMD_V7_ERASE;
		अवरोध;
	हाल v7_CMD_ERASE_DISP_CONFIG:
		data_1_5.partition_id = DISPLAY_CONFIG_PARTITION;
		data_1_5.command = CMD_V7_ERASE;
		अवरोध;
	हाल v7_CMD_ERASE_FLASH_CONFIG:
		data_1_5.partition_id = FLASH_CONFIG_PARTITION;
		data_1_5.command = CMD_V7_ERASE;
		अवरोध;
	हाल v7_CMD_ERASE_GUEST_CODE:
		data_1_5.partition_id = GUEST_CODE_PARTITION;
		data_1_5.command = CMD_V7_ERASE;
		अवरोध;
	हाल v7_CMD_ENABLE_FLASH_PROG:
		data_1_5.partition_id = BOOTLOADER_PARTITION;
		data_1_5.command = CMD_V7_ENTER_BL;
		अवरोध;
	पूर्ण

	data_1_5.payload[0] = f34->bootloader_id[0];
	data_1_5.payload[1] = f34->bootloader_id[1];

	ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
			base + f34->v7.off.partition_id,
			&data_1_5, माप(data_1_5));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev,
			"%s: Failed to write single transaction command\n",
			__func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_command(काष्ठा f34_data *f34, u8 cmd)
अणु
	पूर्णांक ret;
	u8 base;
	u8 command;

	base = f34->fn->fd.data_base_addr;

	चयन (cmd) अणु
	हाल v7_CMD_WRITE_FW:
	हाल v7_CMD_WRITE_CONFIG:
	हाल v7_CMD_WRITE_GUEST_CODE:
		command = CMD_V7_WRITE;
		अवरोध;
	हाल v7_CMD_READ_CONFIG:
		command = CMD_V7_READ;
		अवरोध;
	हाल v7_CMD_ERASE_ALL:
		command = CMD_V7_ERASE_AP;
		अवरोध;
	हाल v7_CMD_ERASE_UI_FIRMWARE:
	हाल v7_CMD_ERASE_BL_CONFIG:
	हाल v7_CMD_ERASE_UI_CONFIG:
	हाल v7_CMD_ERASE_DISP_CONFIG:
	हाल v7_CMD_ERASE_FLASH_CONFIG:
	हाल v7_CMD_ERASE_GUEST_CODE:
		command = CMD_V7_ERASE;
		अवरोध;
	हाल v7_CMD_ENABLE_FLASH_PROG:
		command = CMD_V7_ENTER_BL;
		अवरोध;
	शेष:
		dev_err(&f34->fn->dev, "%s: Invalid command 0x%02x\n",
			__func__, cmd);
		वापस -EINVAL;
	पूर्ण

	f34->v7.command = command;

	चयन (cmd) अणु
	हाल v7_CMD_ERASE_ALL:
	हाल v7_CMD_ERASE_UI_FIRMWARE:
	हाल v7_CMD_ERASE_BL_CONFIG:
	हाल v7_CMD_ERASE_UI_CONFIG:
	हाल v7_CMD_ERASE_DISP_CONFIG:
	हाल v7_CMD_ERASE_FLASH_CONFIG:
	हाल v7_CMD_ERASE_GUEST_CODE:
	हाल v7_CMD_ENABLE_FLASH_PROG:
		ret = rmi_f34v7_ग_लिखो_command_single_transaction(f34, cmd);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev, "%s: writing cmd %02X\n",
		__func__, command);

	ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
			base + f34->v7.off.flash_cmd,
			&command, माप(command));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to write flash command\n",
			__func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_partition_id(काष्ठा f34_data *f34, u8 cmd)
अणु
	पूर्णांक ret;
	u8 base;
	u8 partition;

	base = f34->fn->fd.data_base_addr;

	चयन (cmd) अणु
	हाल v7_CMD_WRITE_FW:
		partition = CORE_CODE_PARTITION;
		अवरोध;
	हाल v7_CMD_WRITE_CONFIG:
	हाल v7_CMD_READ_CONFIG:
		अगर (f34->v7.config_area == v7_UI_CONFIG_AREA)
			partition = CORE_CONFIG_PARTITION;
		अन्यथा अगर (f34->v7.config_area == v7_DP_CONFIG_AREA)
			partition = DISPLAY_CONFIG_PARTITION;
		अन्यथा अगर (f34->v7.config_area == v7_PM_CONFIG_AREA)
			partition = GUEST_SERIALIZATION_PARTITION;
		अन्यथा अगर (f34->v7.config_area == v7_BL_CONFIG_AREA)
			partition = GLOBAL_PARAMETERS_PARTITION;
		अन्यथा अगर (f34->v7.config_area == v7_FLASH_CONFIG_AREA)
			partition = FLASH_CONFIG_PARTITION;
		अवरोध;
	हाल v7_CMD_WRITE_GUEST_CODE:
		partition = GUEST_CODE_PARTITION;
		अवरोध;
	हाल v7_CMD_ERASE_ALL:
		partition = CORE_CODE_PARTITION;
		अवरोध;
	हाल v7_CMD_ERASE_BL_CONFIG:
		partition = GLOBAL_PARAMETERS_PARTITION;
		अवरोध;
	हाल v7_CMD_ERASE_UI_CONFIG:
		partition = CORE_CONFIG_PARTITION;
		अवरोध;
	हाल v7_CMD_ERASE_DISP_CONFIG:
		partition = DISPLAY_CONFIG_PARTITION;
		अवरोध;
	हाल v7_CMD_ERASE_FLASH_CONFIG:
		partition = FLASH_CONFIG_PARTITION;
		अवरोध;
	हाल v7_CMD_ERASE_GUEST_CODE:
		partition = GUEST_CODE_PARTITION;
		अवरोध;
	हाल v7_CMD_ENABLE_FLASH_PROG:
		partition = BOOTLOADER_PARTITION;
		अवरोध;
	शेष:
		dev_err(&f34->fn->dev, "%s: Invalid command 0x%02x\n",
			__func__, cmd);
		वापस -EINVAL;
	पूर्ण

	ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
			base + f34->v7.off.partition_id,
			&partition, माप(partition));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to write partition ID\n",
			__func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_पढ़ो_partition_table(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	u8 base;
	__le16 length;
	u16 block_number = 0;

	base = f34->fn->fd.data_base_addr;

	f34->v7.config_area = v7_FLASH_CONFIG_AREA;

	ret = rmi_f34v7_ग_लिखो_partition_id(f34, v7_CMD_READ_CONFIG);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
			base + f34->v7.off.block_number,
			&block_number, माप(block_number));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to write block number\n",
			__func__);
		वापस ret;
	पूर्ण

	put_unaligned_le16(f34->v7.flash_config_length, &length);

	ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
			base + f34->v7.off.transfer_length,
			&length, माप(length));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to write transfer length\n",
			__func__);
		वापस ret;
	पूर्ण

	init_completion(&f34->v7.cmd_करोne);

	ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_READ_CONFIG);
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to write command\n",
			__func__);
		वापस ret;
	पूर्ण

	समयout = msecs_to_jअगरfies(F34_WRITE_WAIT_MS);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		usleep_range(5000, 6000);
		rmi_f34v7_पढ़ो_flash_status(f34);

		अगर (f34->v7.command == v7_CMD_IDLE &&
		    f34->v7.flash_status == 0x00) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			base + f34->v7.off.payload,
			f34->v7.पढ़ो_config_buf,
			f34->v7.partition_table_bytes);
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to read block data\n",
			__func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rmi_f34v7_parse_partition_table(काष्ठा f34_data *f34,
					    स्थिर व्योम *partition_table,
					    काष्ठा block_count *blkcount,
					    काष्ठा physical_address *phyaddr)
अणु
	पूर्णांक i;
	पूर्णांक index;
	u16 partition_length;
	u16 physical_address;
	स्थिर काष्ठा partition_table *ptable;

	क्रम (i = 0; i < f34->v7.partitions; i++) अणु
		index = i * 8 + 2;
		ptable = partition_table + index;
		partition_length = le16_to_cpu(ptable->partition_length);
		physical_address = le16_to_cpu(ptable->start_physical_address);
		rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
			"%s: Partition entry %d: %*ph\n",
			__func__, i, माप(काष्ठा partition_table), ptable);
		चयन (ptable->partition_id & 0x1f) अणु
		हाल CORE_CODE_PARTITION:
			blkcount->ui_firmware = partition_length;
			phyaddr->ui_firmware = physical_address;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Core code block count: %d\n",
				__func__, blkcount->ui_firmware);
			अवरोध;
		हाल CORE_CONFIG_PARTITION:
			blkcount->ui_config = partition_length;
			phyaddr->ui_config = physical_address;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Core config block count: %d\n",
				__func__, blkcount->ui_config);
			अवरोध;
		हाल DISPLAY_CONFIG_PARTITION:
			blkcount->dp_config = partition_length;
			phyaddr->dp_config = physical_address;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Display config block count: %d\n",
				__func__, blkcount->dp_config);
			अवरोध;
		हाल FLASH_CONFIG_PARTITION:
			blkcount->fl_config = partition_length;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Flash config block count: %d\n",
				__func__, blkcount->fl_config);
			अवरोध;
		हाल GUEST_CODE_PARTITION:
			blkcount->guest_code = partition_length;
			phyaddr->guest_code = physical_address;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Guest code block count: %d\n",
				__func__, blkcount->guest_code);
			अवरोध;
		हाल GUEST_SERIALIZATION_PARTITION:
			blkcount->pm_config = partition_length;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Guest serialization block count: %d\n",
				__func__, blkcount->pm_config);
			अवरोध;
		हाल GLOBAL_PARAMETERS_PARTITION:
			blkcount->bl_config = partition_length;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Global parameters block count: %d\n",
				__func__, blkcount->bl_config);
			अवरोध;
		हाल DEVICE_CONFIG_PARTITION:
			blkcount->lockकरोwn = partition_length;
			rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
				"%s: Device config block count: %d\n",
				__func__, blkcount->lockकरोwn);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rmi_f34v7_पढ़ो_queries_bl_version(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;
	u8 base;
	पूर्णांक offset;
	u8 query_0;
	काष्ठा f34v7_query_1_7 query_1_7;

	base = f34->fn->fd.query_base_addr;

	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			base,
			&query_0,
			माप(query_0));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev,
			"%s: Failed to read query 0\n", __func__);
		वापस ret;
	पूर्ण

	offset = (query_0 & 0x7) + 1;

	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			base + offset,
			&query_1_7,
			माप(query_1_7));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to read queries 1 to 7\n",
			__func__);
		वापस ret;
	पूर्ण

	f34->bootloader_id[0] = query_1_7.bl_minor_revision;
	f34->bootloader_id[1] = query_1_7.bl_major_revision;

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev, "Bootloader V%d.%d\n",
		f34->bootloader_id[1], f34->bootloader_id[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_पढ़ो_queries(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	u8 base;
	पूर्णांक offset;
	u8 *ptable;
	u8 query_0;
	काष्ठा f34v7_query_1_7 query_1_7;

	base = f34->fn->fd.query_base_addr;

	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			base,
			&query_0,
			माप(query_0));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev,
			"%s: Failed to read query 0\n", __func__);
		वापस ret;
	पूर्ण

	offset = (query_0 & 0x07) + 1;

	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			base + offset,
			&query_1_7,
			माप(query_1_7));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to read queries 1 to 7\n",
			__func__);
		वापस ret;
	पूर्ण

	f34->bootloader_id[0] = query_1_7.bl_minor_revision;
	f34->bootloader_id[1] = query_1_7.bl_major_revision;

	f34->v7.block_size = le16_to_cpu(query_1_7.block_size);
	f34->v7.flash_config_length =
			le16_to_cpu(query_1_7.flash_config_length);
	f34->v7.payload_length = le16_to_cpu(query_1_7.payload_length);

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev, "%s: f34->v7.block_size = %d\n",
		 __func__, f34->v7.block_size);

	f34->v7.off.flash_status = V7_FLASH_STATUS_OFFSET;
	f34->v7.off.partition_id = V7_PARTITION_ID_OFFSET;
	f34->v7.off.block_number = V7_BLOCK_NUMBER_OFFSET;
	f34->v7.off.transfer_length = V7_TRANSFER_LENGTH_OFFSET;
	f34->v7.off.flash_cmd = V7_COMMAND_OFFSET;
	f34->v7.off.payload = V7_PAYLOAD_OFFSET;

	f34->v7.has_display_cfg = query_1_7.partition_support[1] & HAS_DISP_CFG;
	f34->v7.has_guest_code =
			query_1_7.partition_support[1] & HAS_GUEST_CODE;

	अगर (query_0 & HAS_CONFIG_ID) अणु
		u8 f34_ctrl[CONFIG_ID_SIZE];

		ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
				f34->fn->fd.control_base_addr,
				f34_ctrl,
				माप(f34_ctrl));
		अगर (ret)
			वापस ret;

		/* Eat leading zeros */
		क्रम (i = 0; i < माप(f34_ctrl) - 1 && !f34_ctrl[i]; i++)
			/* Empty */;

		snम_लिखो(f34->configuration_id, माप(f34->configuration_id),
			 "%*phN", (पूर्णांक)माप(f34_ctrl) - i, f34_ctrl + i);

		rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev, "Configuration ID: %s\n",
			f34->configuration_id);
	पूर्ण

	f34->v7.partitions = 0;
	क्रम (i = 0; i < माप(query_1_7.partition_support); i++)
		f34->v7.partitions += hweight8(query_1_7.partition_support[i]);

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev, "%s: Supported partitions: %*ph\n",
		__func__, माप(query_1_7.partition_support),
		query_1_7.partition_support);


	f34->v7.partition_table_bytes = f34->v7.partitions * 8 + 2;

	f34->v7.पढ़ो_config_buf = devm_kzalloc(&f34->fn->dev,
			f34->v7.partition_table_bytes,
			GFP_KERNEL);
	अगर (!f34->v7.पढ़ो_config_buf) अणु
		f34->v7.पढ़ो_config_buf_size = 0;
		वापस -ENOMEM;
	पूर्ण

	f34->v7.पढ़ो_config_buf_size = f34->v7.partition_table_bytes;
	ptable = f34->v7.पढ़ो_config_buf;

	ret = rmi_f34v7_पढ़ो_partition_table(f34);
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to read partition table\n",
				__func__);
		वापस ret;
	पूर्ण

	rmi_f34v7_parse_partition_table(f34, ptable,
					&f34->v7.blkcount, &f34->v7.phyaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_check_ui_firmware_size(काष्ठा f34_data *f34)
अणु
	u16 block_count;

	block_count = f34->v7.img.ui_firmware.size / f34->v7.block_size;
	f34->update_size += block_count;

	अगर (block_count != f34->v7.blkcount.ui_firmware) अणु
		dev_err(&f34->fn->dev,
			"UI firmware size mismatch: %d != %d\n",
			block_count, f34->v7.blkcount.ui_firmware);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_check_ui_config_size(काष्ठा f34_data *f34)
अणु
	u16 block_count;

	block_count = f34->v7.img.ui_config.size / f34->v7.block_size;
	f34->update_size += block_count;

	अगर (block_count != f34->v7.blkcount.ui_config) अणु
		dev_err(&f34->fn->dev, "UI config size mismatch\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_check_dp_config_size(काष्ठा f34_data *f34)
अणु
	u16 block_count;

	block_count = f34->v7.img.dp_config.size / f34->v7.block_size;
	f34->update_size += block_count;

	अगर (block_count != f34->v7.blkcount.dp_config) अणु
		dev_err(&f34->fn->dev, "Display config size mismatch\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_check_guest_code_size(काष्ठा f34_data *f34)
अणु
	u16 block_count;

	block_count = f34->v7.img.guest_code.size / f34->v7.block_size;
	f34->update_size += block_count;

	अगर (block_count != f34->v7.blkcount.guest_code) अणु
		dev_err(&f34->fn->dev, "Guest code size mismatch\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_check_bl_config_size(काष्ठा f34_data *f34)
अणु
	u16 block_count;

	block_count = f34->v7.img.bl_config.size / f34->v7.block_size;
	f34->update_size += block_count;

	अगर (block_count != f34->v7.blkcount.bl_config) अणु
		dev_err(&f34->fn->dev, "Bootloader config size mismatch\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_erase_config(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;

	dev_info(&f34->fn->dev, "Erasing config...\n");

	init_completion(&f34->v7.cmd_करोne);

	चयन (f34->v7.config_area) अणु
	हाल v7_UI_CONFIG_AREA:
		ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_ERASE_UI_CONFIG);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल v7_DP_CONFIG_AREA:
		ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_ERASE_DISP_CONFIG);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल v7_BL_CONFIG_AREA:
		ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_ERASE_BL_CONFIG);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	पूर्ण

	ret = rmi_f34v7_रुको_क्रम_idle(f34, F34_ERASE_WAIT_MS);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_erase_guest_code(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;

	dev_info(&f34->fn->dev, "Erasing guest code...\n");

	init_completion(&f34->v7.cmd_करोne);

	ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_ERASE_GUEST_CODE);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_f34v7_रुको_क्रम_idle(f34, F34_ERASE_WAIT_MS);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_erase_all(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;

	dev_info(&f34->fn->dev, "Erasing firmware...\n");

	init_completion(&f34->v7.cmd_करोne);

	ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_ERASE_UI_FIRMWARE);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_f34v7_रुको_क्रम_idle(f34, F34_ERASE_WAIT_MS);
	अगर (ret < 0)
		वापस ret;

	f34->v7.config_area = v7_UI_CONFIG_AREA;
	ret = rmi_f34v7_erase_config(f34);
	अगर (ret < 0)
		वापस ret;

	अगर (f34->v7.has_display_cfg) अणु
		f34->v7.config_area = v7_DP_CONFIG_AREA;
		ret = rmi_f34v7_erase_config(f34);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (f34->v7.new_partition_table && f34->v7.has_guest_code) अणु
		ret = rmi_f34v7_erase_guest_code(f34);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_पढ़ो_blocks(काष्ठा f34_data *f34,
				 u16 block_cnt, u8 command)
अणु
	पूर्णांक ret;
	u8 base;
	__le16 length;
	u16 transfer;
	u16 max_transfer;
	u16 reमुख्यing = block_cnt;
	u16 block_number = 0;
	u16 index = 0;

	base = f34->fn->fd.data_base_addr;

	ret = rmi_f34v7_ग_लिखो_partition_id(f34, command);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
			base + f34->v7.off.block_number,
			&block_number, माप(block_number));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to write block number\n",
			__func__);
		वापस ret;
	पूर्ण

	max_transfer = min(f34->v7.payload_length,
			   (u16)(PAGE_SIZE / f34->v7.block_size));

	करो अणु
		transfer = min(reमुख्यing, max_transfer);
		put_unaligned_le16(transfer, &length);

		ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
				base + f34->v7.off.transfer_length,
				&length, माप(length));
		अगर (ret < 0) अणु
			dev_err(&f34->fn->dev,
				"%s: Write transfer length fail (%d remaining)\n",
				__func__, reमुख्यing);
			वापस ret;
		पूर्ण

		init_completion(&f34->v7.cmd_करोne);

		ret = rmi_f34v7_ग_लिखो_command(f34, command);
		अगर (ret < 0)
			वापस ret;

		ret = rmi_f34v7_रुको_क्रम_idle(f34, F34_ENABLE_WAIT_MS);
		अगर (ret < 0)
			वापस ret;

		ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
				base + f34->v7.off.payload,
				&f34->v7.पढ़ो_config_buf[index],
				transfer * f34->v7.block_size);
		अगर (ret < 0) अणु
			dev_err(&f34->fn->dev,
				"%s: Read block failed (%d blks remaining)\n",
				__func__, reमुख्यing);
			वापस ret;
		पूर्ण

		index += (transfer * f34->v7.block_size);
		reमुख्यing -= transfer;
	पूर्ण जबतक (reमुख्यing);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_f34v7_blocks(काष्ठा f34_data *f34,
					स्थिर व्योम *block_ptr, u16 block_cnt,
					u8 command)
अणु
	पूर्णांक ret;
	u8 base;
	__le16 length;
	u16 transfer;
	u16 max_transfer;
	u16 reमुख्यing = block_cnt;
	u16 block_number = 0;

	base = f34->fn->fd.data_base_addr;

	ret = rmi_f34v7_ग_लिखो_partition_id(f34, command);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
			base + f34->v7.off.block_number,
			&block_number, माप(block_number));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to write block number\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर (f34->v7.payload_length > (PAGE_SIZE / f34->v7.block_size))
		max_transfer = PAGE_SIZE / f34->v7.block_size;
	अन्यथा
		max_transfer = f34->v7.payload_length;

	करो अणु
		transfer = min(reमुख्यing, max_transfer);
		put_unaligned_le16(transfer, &length);

		init_completion(&f34->v7.cmd_करोne);

		ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
				base + f34->v7.off.transfer_length,
				&length, माप(length));
		अगर (ret < 0) अणु
			dev_err(&f34->fn->dev,
				"%s: Write transfer length fail (%d remaining)\n",
				__func__, reमुख्यing);
			वापस ret;
		पूर्ण

		ret = rmi_f34v7_ग_लिखो_command(f34, command);
		अगर (ret < 0)
			वापस ret;

		ret = rmi_ग_लिखो_block(f34->fn->rmi_dev,
				base + f34->v7.off.payload,
				block_ptr, transfer * f34->v7.block_size);
		अगर (ret < 0) अणु
			dev_err(&f34->fn->dev,
				"%s: Failed writing data (%d blks remaining)\n",
				__func__, reमुख्यing);
			वापस ret;
		पूर्ण

		ret = rmi_f34v7_रुको_क्रम_idle(f34, F34_ENABLE_WAIT_MS);
		अगर (ret < 0)
			वापस ret;

		block_ptr += (transfer * f34->v7.block_size);
		reमुख्यing -= transfer;
		f34->update_progress += transfer;
		f34->update_status = (f34->update_progress * 100) /
				     f34->update_size;
	पूर्ण जबतक (reमुख्यing);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_config(काष्ठा f34_data *f34)
अणु
	वापस rmi_f34v7_ग_लिखो_f34v7_blocks(f34, f34->v7.config_data,
					    f34->v7.config_block_count,
					    v7_CMD_WRITE_CONFIG);
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_ui_config(काष्ठा f34_data *f34)
अणु
	f34->v7.config_area = v7_UI_CONFIG_AREA;
	f34->v7.config_data = f34->v7.img.ui_config.data;
	f34->v7.config_size = f34->v7.img.ui_config.size;
	f34->v7.config_block_count = f34->v7.config_size / f34->v7.block_size;

	वापस rmi_f34v7_ग_लिखो_config(f34);
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_dp_config(काष्ठा f34_data *f34)
अणु
	f34->v7.config_area = v7_DP_CONFIG_AREA;
	f34->v7.config_data = f34->v7.img.dp_config.data;
	f34->v7.config_size = f34->v7.img.dp_config.size;
	f34->v7.config_block_count = f34->v7.config_size / f34->v7.block_size;

	वापस rmi_f34v7_ग_लिखो_config(f34);
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_guest_code(काष्ठा f34_data *f34)
अणु
	वापस rmi_f34v7_ग_लिखो_f34v7_blocks(f34, f34->v7.img.guest_code.data,
					    f34->v7.img.guest_code.size /
							f34->v7.block_size,
					    v7_CMD_WRITE_GUEST_CODE);
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_flash_config(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;

	f34->v7.config_area = v7_FLASH_CONFIG_AREA;
	f34->v7.config_data = f34->v7.img.fl_config.data;
	f34->v7.config_size = f34->v7.img.fl_config.size;
	f34->v7.config_block_count = f34->v7.config_size / f34->v7.block_size;

	अगर (f34->v7.config_block_count != f34->v7.blkcount.fl_config) अणु
		dev_err(&f34->fn->dev, "%s: Flash config size mismatch\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	init_completion(&f34->v7.cmd_करोne);

	ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_ERASE_FLASH_CONFIG);
	अगर (ret < 0)
		वापस ret;

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
		"%s: Erase flash config command written\n", __func__);

	ret = rmi_f34v7_रुको_क्रम_idle(f34, F34_WRITE_WAIT_MS);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_f34v7_ग_लिखो_config(f34);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_partition_table(काष्ठा f34_data *f34)
अणु
	u16 block_count;
	पूर्णांक ret;

	block_count = f34->v7.blkcount.bl_config;
	f34->v7.config_area = v7_BL_CONFIG_AREA;
	f34->v7.config_size = f34->v7.block_size * block_count;
	devm_kमुक्त(&f34->fn->dev, f34->v7.पढ़ो_config_buf);
	f34->v7.पढ़ो_config_buf = devm_kzalloc(&f34->fn->dev,
					       f34->v7.config_size, GFP_KERNEL);
	अगर (!f34->v7.पढ़ो_config_buf) अणु
		f34->v7.पढ़ो_config_buf_size = 0;
		वापस -ENOMEM;
	पूर्ण

	f34->v7.पढ़ो_config_buf_size = f34->v7.config_size;

	ret = rmi_f34v7_पढ़ो_blocks(f34, block_count, v7_CMD_READ_CONFIG);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_f34v7_erase_config(f34);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_f34v7_ग_लिखो_flash_config(f34);
	अगर (ret < 0)
		वापस ret;

	f34->v7.config_area = v7_BL_CONFIG_AREA;
	f34->v7.config_data = f34->v7.पढ़ो_config_buf;
	f34->v7.config_size = f34->v7.img.bl_config.size;
	f34->v7.config_block_count = f34->v7.config_size / f34->v7.block_size;

	ret = rmi_f34v7_ग_लिखो_config(f34);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f34v7_ग_लिखो_firmware(काष्ठा f34_data *f34)
अणु
	u16 blk_count;

	blk_count = f34->v7.img.ui_firmware.size / f34->v7.block_size;

	वापस rmi_f34v7_ग_लिखो_f34v7_blocks(f34, f34->v7.img.ui_firmware.data,
					    blk_count, v7_CMD_WRITE_FW);
पूर्ण

अटल व्योम rmi_f34v7_compare_partition_tables(काष्ठा f34_data *f34)
अणु
	अगर (f34->v7.phyaddr.ui_firmware != f34->v7.img.phyaddr.ui_firmware) अणु
		f34->v7.new_partition_table = true;
		वापस;
	पूर्ण

	अगर (f34->v7.phyaddr.ui_config != f34->v7.img.phyaddr.ui_config) अणु
		f34->v7.new_partition_table = true;
		वापस;
	पूर्ण

	अगर (f34->v7.has_display_cfg &&
	    f34->v7.phyaddr.dp_config != f34->v7.img.phyaddr.dp_config) अणु
		f34->v7.new_partition_table = true;
		वापस;
	पूर्ण

	अगर (f34->v7.has_guest_code &&
	    f34->v7.phyaddr.guest_code != f34->v7.img.phyaddr.guest_code) अणु
		f34->v7.new_partition_table = true;
		वापस;
	पूर्ण

	f34->v7.new_partition_table = false;
पूर्ण

अटल व्योम rmi_f34v7_parse_img_header_10_bl_container(काष्ठा f34_data *f34,
						       स्थिर व्योम *image)
अणु
	पूर्णांक i;
	पूर्णांक num_of_containers;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक container_id;
	अचिन्हित पूर्णांक length;
	स्थिर व्योम *content;
	स्थिर काष्ठा container_descriptor *descriptor;

	num_of_containers = f34->v7.img.bootloader.size / 4 - 1;

	क्रम (i = 1; i <= num_of_containers; i++) अणु
		addr = get_unaligned_le32(f34->v7.img.bootloader.data + i * 4);
		descriptor = image + addr;
		container_id = le16_to_cpu(descriptor->container_id);
		content = image + le32_to_cpu(descriptor->content_address);
		length = le32_to_cpu(descriptor->content_length);
		चयन (container_id) अणु
		हाल BL_CONFIG_CONTAINER:
		हाल GLOBAL_PARAMETERS_CONTAINER:
			f34->v7.img.bl_config.data = content;
			f34->v7.img.bl_config.size = length;
			अवरोध;
		हाल BL_LOCKDOWN_INFO_CONTAINER:
		हाल DEVICE_CONFIG_CONTAINER:
			f34->v7.img.lockकरोwn.data = content;
			f34->v7.img.lockकरोwn.size = length;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rmi_f34v7_parse_image_header_10(काष्ठा f34_data *f34)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_of_containers;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक container_id;
	अचिन्हित पूर्णांक length;
	स्थिर व्योम *image = f34->v7.image;
	स्थिर u8 *content;
	स्थिर काष्ठा container_descriptor *descriptor;
	स्थिर काष्ठा image_header_10 *header = image;

	f34->v7.img.checksum = le32_to_cpu(header->checksum);

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev, "%s: f34->v7.img.checksum=%X\n",
		__func__, f34->v7.img.checksum);

	/* address of top level container */
	offset = le32_to_cpu(header->top_level_container_start_addr);
	descriptor = image + offset;

	/* address of top level container content */
	offset = le32_to_cpu(descriptor->content_address);
	num_of_containers = le32_to_cpu(descriptor->content_length) / 4;

	क्रम (i = 0; i < num_of_containers; i++) अणु
		addr = get_unaligned_le32(image + offset);
		offset += 4;
		descriptor = image + addr;
		container_id = le16_to_cpu(descriptor->container_id);
		content = image + le32_to_cpu(descriptor->content_address);
		length = le32_to_cpu(descriptor->content_length);

		rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
			"%s: container_id=%d, length=%d\n", __func__,
			container_id, length);

		चयन (container_id) अणु
		हाल UI_CONTAINER:
		हाल CORE_CODE_CONTAINER:
			f34->v7.img.ui_firmware.data = content;
			f34->v7.img.ui_firmware.size = length;
			अवरोध;
		हाल UI_CONFIG_CONTAINER:
		हाल CORE_CONFIG_CONTAINER:
			f34->v7.img.ui_config.data = content;
			f34->v7.img.ui_config.size = length;
			अवरोध;
		हाल BL_CONTAINER:
			f34->v7.img.bl_version = *content;
			f34->v7.img.bootloader.data = content;
			f34->v7.img.bootloader.size = length;
			rmi_f34v7_parse_img_header_10_bl_container(f34, image);
			अवरोध;
		हाल GUEST_CODE_CONTAINER:
			f34->v7.img.contains_guest_code = true;
			f34->v7.img.guest_code.data = content;
			f34->v7.img.guest_code.size = length;
			अवरोध;
		हाल DISPLAY_CONFIG_CONTAINER:
			f34->v7.img.contains_display_cfg = true;
			f34->v7.img.dp_config.data = content;
			f34->v7.img.dp_config.size = length;
			अवरोध;
		हाल FLASH_CONFIG_CONTAINER:
			f34->v7.img.contains_flash_config = true;
			f34->v7.img.fl_config.data = content;
			f34->v7.img.fl_config.size = length;
			अवरोध;
		हाल GENERAL_INFORMATION_CONTAINER:
			f34->v7.img.contains_firmware_id = true;
			f34->v7.img.firmware_id =
				get_unaligned_le32(content + 4);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rmi_f34v7_parse_image_info(काष्ठा f34_data *f34)
अणु
	स्थिर काष्ठा image_header_10 *header = f34->v7.image;

	स_रखो(&f34->v7.img, 0x00, माप(f34->v7.img));

	rmi_dbg(RMI_DEBUG_FN, &f34->fn->dev,
		"%s: header->major_header_version = %d\n",
		__func__, header->major_header_version);

	चयन (header->major_header_version) अणु
	हाल IMAGE_HEADER_VERSION_10:
		rmi_f34v7_parse_image_header_10(f34);
		अवरोध;
	शेष:
		dev_err(&f34->fn->dev, "Unsupported image file format %02X\n",
			header->major_header_version);
		वापस -EINVAL;
	पूर्ण

	अगर (!f34->v7.img.contains_flash_config) अणु
		dev_err(&f34->fn->dev, "%s: No flash config in fw image\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	rmi_f34v7_parse_partition_table(f34, f34->v7.img.fl_config.data,
			&f34->v7.img.blkcount, &f34->v7.img.phyaddr);

	rmi_f34v7_compare_partition_tables(f34);

	वापस 0;
पूर्ण

पूर्णांक rmi_f34v7_करो_reflash(काष्ठा f34_data *f34, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret;

	f34->fn->rmi_dev->driver->set_irq_bits(f34->fn->rmi_dev,
					       f34->fn->irq_mask);

	rmi_f34v7_पढ़ो_queries_bl_version(f34);

	f34->v7.image = fw->data;
	f34->update_progress = 0;
	f34->update_size = 0;

	ret = rmi_f34v7_parse_image_info(f34);
	अगर (ret < 0)
		जाओ fail;

	अगर (!f34->v7.new_partition_table) अणु
		ret = rmi_f34v7_check_ui_firmware_size(f34);
		अगर (ret < 0)
			जाओ fail;

		ret = rmi_f34v7_check_ui_config_size(f34);
		अगर (ret < 0)
			जाओ fail;

		अगर (f34->v7.has_display_cfg &&
		    f34->v7.img.contains_display_cfg) अणु
			ret = rmi_f34v7_check_dp_config_size(f34);
			अगर (ret < 0)
				जाओ fail;
		पूर्ण

		अगर (f34->v7.has_guest_code && f34->v7.img.contains_guest_code) अणु
			ret = rmi_f34v7_check_guest_code_size(f34);
			अगर (ret < 0)
				जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = rmi_f34v7_check_bl_config_size(f34);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	ret = rmi_f34v7_erase_all(f34);
	अगर (ret < 0)
		जाओ fail;

	अगर (f34->v7.new_partition_table) अणु
		ret = rmi_f34v7_ग_लिखो_partition_table(f34);
		अगर (ret < 0)
			जाओ fail;
		dev_info(&f34->fn->dev, "%s: Partition table programmed\n",
			 __func__);
	पूर्ण

	dev_info(&f34->fn->dev, "Writing firmware (%d bytes)...\n",
		 f34->v7.img.ui_firmware.size);

	ret = rmi_f34v7_ग_लिखो_firmware(f34);
	अगर (ret < 0)
		जाओ fail;

	dev_info(&f34->fn->dev, "Writing config (%d bytes)...\n",
		 f34->v7.img.ui_config.size);

	f34->v7.config_area = v7_UI_CONFIG_AREA;
	ret = rmi_f34v7_ग_लिखो_ui_config(f34);
	अगर (ret < 0)
		जाओ fail;

	अगर (f34->v7.has_display_cfg && f34->v7.img.contains_display_cfg) अणु
		dev_info(&f34->fn->dev, "Writing display config...\n");

		ret = rmi_f34v7_ग_लिखो_dp_config(f34);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	अगर (f34->v7.new_partition_table) अणु
		अगर (f34->v7.has_guest_code && f34->v7.img.contains_guest_code) अणु
			dev_info(&f34->fn->dev, "Writing guest code...\n");

			ret = rmi_f34v7_ग_लिखो_guest_code(f34);
			अगर (ret < 0)
				जाओ fail;
		पूर्ण
	पूर्ण

fail:
	वापस ret;
पूर्ण

अटल पूर्णांक rmi_f34v7_enter_flash_prog(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;

	f34->fn->rmi_dev->driver->set_irq_bits(f34->fn->rmi_dev, f34->fn->irq_mask);

	ret = rmi_f34v7_पढ़ो_flash_status(f34);
	अगर (ret < 0)
		वापस ret;

	अगर (f34->v7.in_bl_mode)
		वापस 0;

	init_completion(&f34->v7.cmd_करोne);

	ret = rmi_f34v7_ग_लिखो_command(f34, v7_CMD_ENABLE_FLASH_PROG);
	अगर (ret < 0)
		वापस ret;

	ret = rmi_f34v7_रुको_क्रम_idle(f34, F34_ENABLE_WAIT_MS);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक rmi_f34v7_start_reflash(काष्ठा f34_data *f34, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret = 0;

	f34->fn->rmi_dev->driver->set_irq_bits(f34->fn->rmi_dev, f34->fn->irq_mask);

	f34->v7.config_area = v7_UI_CONFIG_AREA;
	f34->v7.image = fw->data;

	ret = rmi_f34v7_parse_image_info(f34);
	अगर (ret < 0)
		जाओ निकास;

	अगर (!f34->v7.क्रमce_update && f34->v7.new_partition_table) अणु
		dev_err(&f34->fn->dev, "%s: Partition table mismatch\n",
				__func__);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	dev_info(&f34->fn->dev, "Firmware image OK\n");

	ret = rmi_f34v7_पढ़ो_flash_status(f34);
	अगर (ret < 0)
		जाओ निकास;

	अगर (f34->v7.in_bl_mode) अणु
		dev_info(&f34->fn->dev, "%s: Device in bootloader mode\n",
				__func__);
	पूर्ण

	rmi_f34v7_enter_flash_prog(f34);

	वापस 0;

निकास:
	वापस ret;
पूर्ण

पूर्णांक rmi_f34v7_probe(काष्ठा f34_data *f34)
अणु
	पूर्णांक ret;

	/* Read bootloader version */
	ret = rmi_पढ़ो_block(f34->fn->rmi_dev,
			f34->fn->fd.query_base_addr + V7_BOOTLOADER_ID_OFFSET,
			f34->bootloader_id,
			माप(f34->bootloader_id));
	अगर (ret < 0) अणु
		dev_err(&f34->fn->dev, "%s: Failed to read bootloader ID\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर (f34->bootloader_id[1] == '5') अणु
		f34->bl_version = 5;
	पूर्ण अन्यथा अगर (f34->bootloader_id[1] == '6') अणु
		f34->bl_version = 6;
	पूर्ण अन्यथा अगर (f34->bootloader_id[1] == 7) अणु
		f34->bl_version = 7;
	पूर्ण अन्यथा अगर (f34->bootloader_id[1] == 8) अणु
		f34->bl_version = 8;
	पूर्ण अन्यथा अणु
		dev_err(&f34->fn->dev,
			"%s: Unrecognized bootloader version: %d (%c) %d (%c)\n",
			__func__,
			f34->bootloader_id[0], f34->bootloader_id[0],
			f34->bootloader_id[1], f34->bootloader_id[1]);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&f34->v7.blkcount, 0x00, माप(f34->v7.blkcount));
	स_रखो(&f34->v7.phyaddr, 0x00, माप(f34->v7.phyaddr));

	init_completion(&f34->v7.cmd_करोne);

	ret = rmi_f34v7_पढ़ो_queries(f34);
	अगर (ret < 0)
		वापस ret;

	f34->v7.क्रमce_update = true;
	वापस 0;
पूर्ण
