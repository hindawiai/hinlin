<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश "debug.h"
#समावेश "acx.h"
#समावेश "boot.h"
#समावेश "io.h"
#समावेश "event.h"
#समावेश "rx.h"
#समावेश "hw_ops.h"

अटल पूर्णांक wl1271_boot_set_ecpu_ctrl(काष्ठा wl1271 *wl, u32 flag)
अणु
	u32 cpu_ctrl;
	पूर्णांक ret;

	/* 10.5.0 run the firmware (I) */
	ret = wlcore_पढ़ो_reg(wl, REG_ECPU_CONTROL, &cpu_ctrl);
	अगर (ret < 0)
		जाओ out;

	/* 10.5.1 run the firmware (II) */
	cpu_ctrl |= flag;
	ret = wlcore_ग_लिखो_reg(wl, REG_ECPU_CONTROL, cpu_ctrl);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wlcore_boot_parse_fw_ver(काष्ठा wl1271 *wl,
				    काष्ठा wl1271_अटल_data *अटल_data)
अणु
	पूर्णांक ret;

	म_नकलन(wl->chip.fw_ver_str, अटल_data->fw_version,
		माप(wl->chip.fw_ver_str));

	/* make sure the string is शून्य-terminated */
	wl->chip.fw_ver_str[माप(wl->chip.fw_ver_str) - 1] = '\0';

	ret = माला_पूछो(wl->chip.fw_ver_str + 4, "%u.%u.%u.%u.%u",
		     &wl->chip.fw_ver[0], &wl->chip.fw_ver[1],
		     &wl->chip.fw_ver[2], &wl->chip.fw_ver[3],
		     &wl->chip.fw_ver[4]);

	अगर (ret != 5) अणु
		wl1271_warning("fw version incorrect value");
		स_रखो(wl->chip.fw_ver, 0, माप(wl->chip.fw_ver));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = wlcore_identअगरy_fw(wl);
	अगर (ret < 0)
		जाओ out;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक wlcore_validate_fw_ver(काष्ठा wl1271 *wl)
अणु
	अचिन्हित पूर्णांक *fw_ver = wl->chip.fw_ver;
	अचिन्हित पूर्णांक *min_ver = (wl->fw_type == WL12XX_FW_TYPE_MULTI) ?
		wl->min_mr_fw_ver : wl->min_sr_fw_ver;
	अक्षर min_fw_str[32] = "";
	पूर्णांक off = 0;
	पूर्णांक i;

	/* the chip must be exactly equal */
	अगर ((min_ver[FW_VER_CHIP] != WLCORE_FW_VER_IGNORE) &&
	    (min_ver[FW_VER_CHIP] != fw_ver[FW_VER_CHIP]))
		जाओ fail;

	/* the firmware type must be equal */
	अगर ((min_ver[FW_VER_IF_TYPE] != WLCORE_FW_VER_IGNORE) &&
	    (min_ver[FW_VER_IF_TYPE] != fw_ver[FW_VER_IF_TYPE]))
		जाओ fail;

	/* the project number must be equal */
	अगर ((min_ver[FW_VER_SUBTYPE] != WLCORE_FW_VER_IGNORE) &&
	    (min_ver[FW_VER_SUBTYPE] != fw_ver[FW_VER_SUBTYPE]))
		जाओ fail;

	/* the API version must be greater or equal */
	अगर ((min_ver[FW_VER_MAJOR] != WLCORE_FW_VER_IGNORE) &&
		 (min_ver[FW_VER_MAJOR] > fw_ver[FW_VER_MAJOR]))
		जाओ fail;

	/* अगर the API version is equal... */
	अगर (((min_ver[FW_VER_MAJOR] == WLCORE_FW_VER_IGNORE) ||
	     (min_ver[FW_VER_MAJOR] == fw_ver[FW_VER_MAJOR])) &&
	    /* ...the minor must be greater or equal */
	    ((min_ver[FW_VER_MINOR] != WLCORE_FW_VER_IGNORE) &&
	     (min_ver[FW_VER_MINOR] > fw_ver[FW_VER_MINOR])))
		जाओ fail;

	वापस 0;

fail:
	क्रम (i = 0; i < NUM_FW_VER && off < माप(min_fw_str); i++)
		अगर (min_ver[i] == WLCORE_FW_VER_IGNORE)
			off += snम_लिखो(min_fw_str + off,
					माप(min_fw_str) - off,
					"*.");
		अन्यथा
			off += snम_लिखो(min_fw_str + off,
					माप(min_fw_str) - off,
					"%u.", min_ver[i]);

	wl1271_error("Your WiFi FW version (%u.%u.%u.%u.%u) is invalid.\n"
		     "Please use at least FW %s\n"
		     "You can get the latest firmwares at:\n"
		     "git://git.ti.com/wilink8-wlan/wl18xx_fw.git",
		     fw_ver[FW_VER_CHIP], fw_ver[FW_VER_IF_TYPE],
		     fw_ver[FW_VER_MAJOR], fw_ver[FW_VER_SUBTYPE],
		     fw_ver[FW_VER_MINOR], min_fw_str);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wlcore_boot_अटल_data(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_अटल_data *अटल_data;
	माप_प्रकार len = माप(*अटल_data) + wl->अटल_data_priv_len;
	पूर्णांक ret;

	अटल_data = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!अटल_data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wlcore_पढ़ो(wl, wl->cmd_box_addr, अटल_data, len, false);
	अगर (ret < 0)
		जाओ out_मुक्त;

	ret = wlcore_boot_parse_fw_ver(wl, अटल_data);
	अगर (ret < 0)
		जाओ out_मुक्त;

	ret = wlcore_validate_fw_ver(wl);
	अगर (ret < 0)
		जाओ out_मुक्त;

	ret = wlcore_handle_अटल_data(wl, अटल_data);
	अगर (ret < 0)
		जाओ out_मुक्त;

out_मुक्त:
	kमुक्त(अटल_data);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_boot_upload_firmware_chunk(काष्ठा wl1271 *wl, व्योम *buf,
					     माप_प्रकार fw_data_len, u32 dest)
अणु
	काष्ठा wlcore_partition_set partition;
	पूर्णांक addr, chunk_num, partition_limit;
	u8 *p, *chunk;
	पूर्णांक ret;

	/* whal_FwCtrl_LoadFwImageSm() */

	wl1271_debug(DEBUG_BOOT, "starting firmware upload");

	wl1271_debug(DEBUG_BOOT, "fw_data_len %zd chunk_size %d",
		     fw_data_len, CHUNK_SIZE);

	अगर ((fw_data_len % 4) != 0) अणु
		wl1271_error("firmware length not multiple of four");
		वापस -EIO;
	पूर्ण

	chunk = kदो_स्मृति(CHUNK_SIZE, GFP_KERNEL);
	अगर (!chunk) अणु
		wl1271_error("allocation for firmware upload chunk failed");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&partition, &wl->ptable[PART_DOWN], माप(partition));
	partition.mem.start = dest;
	ret = wlcore_set_partition(wl, &partition);
	अगर (ret < 0)
		जाओ out;

	/* 10.1 set partition limit and chunk num */
	chunk_num = 0;
	partition_limit = wl->ptable[PART_DOWN].mem.size;

	जबतक (chunk_num < fw_data_len / CHUNK_SIZE) अणु
		/* 10.2 update partition, अगर needed */
		addr = dest + (chunk_num + 2) * CHUNK_SIZE;
		अगर (addr > partition_limit) अणु
			addr = dest + chunk_num * CHUNK_SIZE;
			partition_limit = chunk_num * CHUNK_SIZE +
				wl->ptable[PART_DOWN].mem.size;
			partition.mem.start = addr;
			ret = wlcore_set_partition(wl, &partition);
			अगर (ret < 0)
				जाओ out;
		पूर्ण

		/* 10.3 upload the chunk */
		addr = dest + chunk_num * CHUNK_SIZE;
		p = buf + chunk_num * CHUNK_SIZE;
		स_नकल(chunk, p, CHUNK_SIZE);
		wl1271_debug(DEBUG_BOOT, "uploading fw chunk 0x%p to 0x%x",
			     p, addr);
		ret = wlcore_ग_लिखो(wl, addr, chunk, CHUNK_SIZE, false);
		अगर (ret < 0)
			जाओ out;

		chunk_num++;
	पूर्ण

	/* 10.4 upload the last chunk */
	addr = dest + chunk_num * CHUNK_SIZE;
	p = buf + chunk_num * CHUNK_SIZE;
	स_नकल(chunk, p, fw_data_len % CHUNK_SIZE);
	wl1271_debug(DEBUG_BOOT, "uploading fw last chunk (%zd B) 0x%p to 0x%x",
		     fw_data_len % CHUNK_SIZE, p, addr);
	ret = wlcore_ग_लिखो(wl, addr, chunk, fw_data_len % CHUNK_SIZE, false);

out:
	kमुक्त(chunk);
	वापस ret;
पूर्ण

पूर्णांक wlcore_boot_upload_firmware(काष्ठा wl1271 *wl)
अणु
	u32 chunks, addr, len;
	पूर्णांक ret = 0;
	u8 *fw;

	fw = wl->fw;
	chunks = be32_to_cpup((__be32 *) fw);
	fw += माप(u32);

	wl1271_debug(DEBUG_BOOT, "firmware chunks to be uploaded: %u", chunks);

	जबतक (chunks--) अणु
		addr = be32_to_cpup((__be32 *) fw);
		fw += माप(u32);
		len = be32_to_cpup((__be32 *) fw);
		fw += माप(u32);

		अगर (len > 300000) अणु
			wl1271_info("firmware chunk too long: %u", len);
			वापस -EINVAL;
		पूर्ण
		wl1271_debug(DEBUG_BOOT, "chunk %d addr 0x%x len %u",
			     chunks, addr, len);
		ret = wl1271_boot_upload_firmware_chunk(wl, fw, len, addr);
		अगर (ret != 0)
			अवरोध;
		fw += len;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_boot_upload_firmware);

पूर्णांक wlcore_boot_upload_nvs(काष्ठा wl1271 *wl)
अणु
	काष्ठा platक्रमm_device *pdev = wl->pdev;
	काष्ठा wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);
	स्थिर अक्षर *nvs_name = "unknown";
	माप_प्रकार nvs_len, burst_len;
	पूर्णांक i;
	u32 dest_addr, val;
	u8 *nvs_ptr, *nvs_aligned;
	पूर्णांक ret;

	अगर (wl->nvs == शून्य) अणु
		wl1271_error("NVS file is needed during boot");
		वापस -ENODEV;
	पूर्ण

	अगर (pdev_data && pdev_data->family)
		nvs_name = pdev_data->family->nvs_name;

	अगर (wl->quirks & WLCORE_QUIRK_LEGACY_NVS) अणु
		काष्ठा wl1271_nvs_file *nvs =
			(काष्ठा wl1271_nvs_file *)wl->nvs;
		/*
		 * FIXME: the LEGACY NVS image support (NVS's missing the 5GHz
		 * band configurations) can be हटाओd when those NVS files stop
		 * भग्नing around.
		 */
		अगर (wl->nvs_len == माप(काष्ठा wl1271_nvs_file) ||
		    wl->nvs_len == WL1271_INI_LEGACY_NVS_खाता_SIZE) अणु
			अगर (nvs->general_params.dual_mode_select)
				wl->enable_11a = true;
		पूर्ण

		अगर (wl->nvs_len != माप(काष्ठा wl1271_nvs_file) &&
		    (wl->nvs_len != WL1271_INI_LEGACY_NVS_खाता_SIZE ||
		     wl->enable_11a)) अणु
			wl1271_error("%s size is not as expected: %zu != %zu",
				     nvs_name, wl->nvs_len,
				     माप(काष्ठा wl1271_nvs_file));
			kमुक्त(wl->nvs);
			wl->nvs = शून्य;
			wl->nvs_len = 0;
			वापस -EILSEQ;
		पूर्ण

		/* only the first part of the NVS needs to be uploaded */
		nvs_len = माप(nvs->nvs);
		nvs_ptr = (u8 *) nvs->nvs;
	पूर्ण अन्यथा अणु
		काष्ठा wl128x_nvs_file *nvs = (काष्ठा wl128x_nvs_file *)wl->nvs;

		अगर (wl->nvs_len == माप(काष्ठा wl128x_nvs_file)) अणु
			अगर (nvs->general_params.dual_mode_select)
				wl->enable_11a = true;
		पूर्ण अन्यथा अणु
			wl1271_error("%s size is not as expected: %zu != %zu",
				     nvs_name, wl->nvs_len,
				     माप(काष्ठा wl128x_nvs_file));
			kमुक्त(wl->nvs);
			wl->nvs = शून्य;
			wl->nvs_len = 0;
			वापस -EILSEQ;
		पूर्ण

		/* only the first part of the NVS needs to be uploaded */
		nvs_len = माप(nvs->nvs);
		nvs_ptr = (u8 *)nvs->nvs;
	पूर्ण

	/* update current MAC address to NVS */
	nvs_ptr[11] = wl->addresses[0].addr[0];
	nvs_ptr[10] = wl->addresses[0].addr[1];
	nvs_ptr[6] = wl->addresses[0].addr[2];
	nvs_ptr[5] = wl->addresses[0].addr[3];
	nvs_ptr[4] = wl->addresses[0].addr[4];
	nvs_ptr[3] = wl->addresses[0].addr[5];

	/*
	 * Layout beक्रमe the actual NVS tables:
	 * 1 byte : burst length.
	 * 2 bytes: destination address.
	 * n bytes: data to burst copy.
	 *
	 * This is ended by a 0 length, then the NVS tables.
	 */

	/* FIXME: Do we need to check here whether the LSB is 1? */
	जबतक (nvs_ptr[0]) अणु
		burst_len = nvs_ptr[0];
		dest_addr = (nvs_ptr[1] & 0xfe) | ((u32)(nvs_ptr[2] << 8));

		/*
		 * Due to our new wl1271_translate_reg_addr function,
		 * we need to add the रेजिस्टर partition start address
		 * to the destination
		 */
		dest_addr += wl->curr_part.reg.start;

		/* We move our poपूर्णांकer to the data */
		nvs_ptr += 3;

		क्रम (i = 0; i < burst_len; i++) अणु
			अगर (nvs_ptr + 3 >= (u8 *) wl->nvs + nvs_len)
				जाओ out_badnvs;

			val = (nvs_ptr[0] | (nvs_ptr[1] << 8)
			       | (nvs_ptr[2] << 16) | (nvs_ptr[3] << 24));

			wl1271_debug(DEBUG_BOOT,
				     "nvs burst write 0x%x: 0x%x",
				     dest_addr, val);
			ret = wlcore_ग_लिखो32(wl, dest_addr, val);
			अगर (ret < 0)
				वापस ret;

			nvs_ptr += 4;
			dest_addr += 4;
		पूर्ण

		अगर (nvs_ptr >= (u8 *) wl->nvs + nvs_len)
			जाओ out_badnvs;
	पूर्ण

	/*
	 * We've reached the first zero length, the first NVS table
	 * is located at an aligned offset which is at least 7 bytes further.
	 * NOTE: The wl->nvs->nvs element must be first, in order to
	 * simplअगरy the casting, we assume it is at the beginning of
	 * the wl->nvs काष्ठाure.
	 */
	nvs_ptr = (u8 *)wl->nvs +
			ALIGN(nvs_ptr - (u8 *)wl->nvs + 7, 4);

	अगर (nvs_ptr >= (u8 *) wl->nvs + nvs_len)
		जाओ out_badnvs;

	nvs_len -= nvs_ptr - (u8 *)wl->nvs;

	/* Now we must set the partition correctly */
	ret = wlcore_set_partition(wl, &wl->ptable[PART_WORK]);
	अगर (ret < 0)
		वापस ret;

	/* Copy the NVS tables to a new block to ensure alignment */
	nvs_aligned = kmemdup(nvs_ptr, nvs_len, GFP_KERNEL);
	अगर (!nvs_aligned)
		वापस -ENOMEM;

	/* And finally we upload the NVS tables */
	ret = wlcore_ग_लिखो_data(wl, REG_CMD_MBOX_ADDRESS, nvs_aligned, nvs_len,
				false);

	kमुक्त(nvs_aligned);
	वापस ret;

out_badnvs:
	wl1271_error("nvs data is malformed");
	वापस -EILSEQ;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_boot_upload_nvs);

पूर्णांक wlcore_boot_run_firmware(काष्ठा wl1271 *wl)
अणु
	पूर्णांक loop, ret;
	u32 chip_id, पूर्णांकr;

	/* Make sure we have the boot partition */
	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_boot_set_ecpu_ctrl(wl, ECPU_CONTROL_HALT);
	अगर (ret < 0)
		वापस ret;

	ret = wlcore_पढ़ो_reg(wl, REG_CHIP_ID_B, &chip_id);
	अगर (ret < 0)
		वापस ret;

	wl1271_debug(DEBUG_BOOT, "chip id after firmware boot: 0x%x", chip_id);

	अगर (chip_id != wl->chip.id) अणु
		wl1271_error("chip id doesn't match after firmware boot");
		वापस -EIO;
	पूर्ण

	/* रुको क्रम init to complete */
	loop = 0;
	जबतक (loop++ < INIT_LOOP) अणु
		udelay(INIT_LOOP_DELAY);
		ret = wlcore_पढ़ो_reg(wl, REG_INTERRUPT_NO_CLEAR, &पूर्णांकr);
		अगर (ret < 0)
			वापस ret;

		अगर (पूर्णांकr == 0xffffffff) अणु
			wl1271_error("error reading hardware complete "
				     "init indication");
			वापस -EIO;
		पूर्ण
		/* check that ACX_INTR_INIT_COMPLETE is enabled */
		अन्यथा अगर (पूर्णांकr & WL1271_ACX_INTR_INIT_COMPLETE) अणु
			ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_ACK,
					       WL1271_ACX_INTR_INIT_COMPLETE);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (loop > INIT_LOOP) अणु
		wl1271_error("timeout waiting for the hardware to "
			     "complete initialization");
		वापस -EIO;
	पूर्ण

	/* get hardware config command mail box */
	ret = wlcore_पढ़ो_reg(wl, REG_COMMAND_MAILBOX_PTR, &wl->cmd_box_addr);
	अगर (ret < 0)
		वापस ret;

	wl1271_debug(DEBUG_MAILBOX, "cmd_box_addr 0x%x", wl->cmd_box_addr);

	/* get hardware config event mail box */
	ret = wlcore_पढ़ो_reg(wl, REG_EVENT_MAILBOX_PTR, &wl->mbox_ptr[0]);
	अगर (ret < 0)
		वापस ret;

	wl->mbox_ptr[1] = wl->mbox_ptr[0] + wl->mbox_size;

	wl1271_debug(DEBUG_MAILBOX, "MBOX ptrs: 0x%x 0x%x",
		     wl->mbox_ptr[0], wl->mbox_ptr[1]);

	ret = wlcore_boot_अटल_data(wl);
	अगर (ret < 0) अणु
		wl1271_error("error getting static data");
		वापस ret;
	पूर्ण

	/*
	 * in हाल of full asynchronous mode the firmware event must be
	 * पढ़ोy to receive event from the command mailbox
	 */

	/* unmask required mbox events  */
	ret = wl1271_event_unmask(wl);
	अगर (ret < 0) अणु
		wl1271_error("EVENT mask setting failed");
		वापस ret;
	पूर्ण

	/* set the working partition to its "running" mode offset */
	ret = wlcore_set_partition(wl, &wl->ptable[PART_WORK]);

	/* firmware startup completed */
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_boot_run_firmware);
