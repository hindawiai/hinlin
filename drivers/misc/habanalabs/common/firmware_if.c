<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"
#समावेश "../include/common/hl_boot_if.h"

#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>

#घोषणा FW_खाता_MAX_SIZE	0x1400000 /* maximum size of 20MB */
/**
 * hl_fw_load_fw_to_device() - Load F/W code to device's memory.
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure.
 * @fw_name: the firmware image name
 * @dst: IO memory mapped address space to copy firmware to
 * @src_offset: offset in src FW to copy from
 * @size: amount of bytes to copy (0 to copy the whole binary)
 *
 * Copy fw code from firmware file to device memory.
 *
 * Return: 0 on success, non-zero क्रम failure.
 */
पूर्णांक hl_fw_load_fw_to_device(काष्ठा hl_device *hdev, स्थिर अक्षर *fw_name,
				व्योम __iomem *dst, u32 src_offset, u32 size)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर व्योम *fw_data;
	माप_प्रकार fw_size;
	पूर्णांक rc;

	rc = request_firmware(&fw, fw_name, hdev->dev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Firmware file %s is not found!\n", fw_name);
		जाओ out;
	पूर्ण

	fw_size = fw->size;
	अगर ((fw_size % 4) != 0) अणु
		dev_err(hdev->dev, "Illegal %s firmware size %zu\n",
			fw_name, fw_size);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	dev_dbg(hdev->dev, "%s firmware size == %zu\n", fw_name, fw_size);

	अगर (fw_size > FW_खाता_MAX_SIZE) अणु
		dev_err(hdev->dev,
			"FW file size %zu exceeds maximum of %u bytes\n",
			fw_size, FW_खाता_MAX_SIZE);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (size - src_offset > fw_size) अणु
		dev_err(hdev->dev,
			"size to copy(%u) and offset(%u) are invalid\n",
			size, src_offset);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (size)
		fw_size = size;

	fw_data = (स्थिर व्योम *) fw->data;

	स_नकल_toio(dst, fw_data + src_offset, fw_size);

out:
	release_firmware(fw);
	वापस rc;
पूर्ण

पूर्णांक hl_fw_send_pci_access_msg(काष्ठा hl_device *hdev, u32 opcode)
अणु
	काष्ठा cpucp_packet pkt = अणुपूर्ण;

	pkt.ctl = cpu_to_le32(opcode << CPUCP_PKT_CTL_OPCODE_SHIFT);

	वापस hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt,
						माप(pkt), 0, शून्य);
पूर्ण

पूर्णांक hl_fw_send_cpu_message(काष्ठा hl_device *hdev, u32 hw_queue_id, u32 *msg,
				u16 len, u32 समयout, u64 *result)
अणु
	काष्ठा hl_hw_queue *queue = &hdev->kernel_queues[hw_queue_id];
	काष्ठा cpucp_packet *pkt;
	dma_addr_t pkt_dma_addr;
	u32 पंचांगp, expected_ack_val;
	पूर्णांक rc = 0;

	pkt = hdev->asic_funcs->cpu_accessible_dma_pool_alloc(hdev, len,
								&pkt_dma_addr);
	अगर (!pkt) अणु
		dev_err(hdev->dev,
			"Failed to allocate DMA memory for packet to CPU\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(pkt, msg, len);

	mutex_lock(&hdev->send_cpu_message_lock);

	अगर (hdev->disabled)
		जाओ out;

	अगर (hdev->device_cpu_disabled) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* set fence to a non valid value */
	pkt->fence = अच_पूर्णांक_उच्च;

	rc = hl_hw_queue_send_cb_no_cmpl(hdev, hw_queue_id, len, pkt_dma_addr);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to send CB on CPU PQ (%d)\n", rc);
		जाओ out;
	पूर्ण

	अगर (hdev->asic_prop.fw_app_security_map &
			CPU_BOOT_DEV_STS0_PKT_PI_ACK_EN)
		expected_ack_val = queue->pi;
	अन्यथा
		expected_ack_val = CPUCP_PACKET_FENCE_VAL;

	rc = hl_poll_समयout_memory(hdev, &pkt->fence, पंचांगp,
				(पंचांगp == expected_ack_val), 1000,
				समयout, true);

	hl_hw_queue_inc_ci_kernel(hdev, hw_queue_id);

	अगर (rc == -ETIMEDOUT) अणु
		dev_err(hdev->dev, "Device CPU packet timeout (0x%x)\n", पंचांगp);
		hdev->device_cpu_disabled = true;
		जाओ out;
	पूर्ण

	पंचांगp = le32_to_cpu(pkt->ctl);

	rc = (पंचांगp & CPUCP_PKT_CTL_RC_MASK) >> CPUCP_PKT_CTL_RC_SHIFT;
	अगर (rc) अणु
		dev_err(hdev->dev, "F/W ERROR %d for CPU packet %d\n",
			rc,
			(पंचांगp & CPUCP_PKT_CTL_OPCODE_MASK)
						>> CPUCP_PKT_CTL_OPCODE_SHIFT);
		rc = -EIO;
	पूर्ण अन्यथा अगर (result) अणु
		*result = le64_to_cpu(pkt->result);
	पूर्ण

out:
	mutex_unlock(&hdev->send_cpu_message_lock);

	hdev->asic_funcs->cpu_accessible_dma_pool_मुक्त(hdev, len, pkt);

	वापस rc;
पूर्ण

पूर्णांक hl_fw_unmask_irq(काष्ठा hl_device *hdev, u16 event_type)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_UNMASK_RAZWI_IRQ <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.value = cpu_to_le64(event_type);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	अगर (rc)
		dev_err(hdev->dev, "failed to unmask RAZWI IRQ %d", event_type);

	वापस rc;
पूर्ण

पूर्णांक hl_fw_unmask_irq_arr(काष्ठा hl_device *hdev, स्थिर u32 *irq_arr,
		माप_प्रकार irq_arr_size)
अणु
	काष्ठा cpucp_unmask_irq_arr_packet *pkt;
	माप_प्रकार total_pkt_size;
	u64 result;
	पूर्णांक rc;

	total_pkt_size = माप(काष्ठा cpucp_unmask_irq_arr_packet) +
			irq_arr_size;

	/* data should be aligned to 8 bytes in order to CPU-CP to copy it */
	total_pkt_size = (total_pkt_size + 0x7) & ~0x7;

	/* total_pkt_size is casted to u16 later on */
	अगर (total_pkt_size > अच_लघु_उच्च) अणु
		dev_err(hdev->dev, "too many elements in IRQ array\n");
		वापस -EINVAL;
	पूर्ण

	pkt = kzalloc(total_pkt_size, GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	pkt->length = cpu_to_le32(irq_arr_size / माप(irq_arr[0]));
	स_नकल(&pkt->irqs, irq_arr, irq_arr_size);

	pkt->cpucp_pkt.ctl = cpu_to_le32(CPUCP_PACKET_UNMASK_RAZWI_IRQ_ARRAY <<
						CPUCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) pkt,
						total_pkt_size, 0, &result);

	अगर (rc)
		dev_err(hdev->dev, "failed to unmask IRQ array\n");

	kमुक्त(pkt);

	वापस rc;
पूर्ण

पूर्णांक hl_fw_test_cpu_queue(काष्ठा hl_device *hdev)
अणु
	काष्ठा cpucp_packet test_pkt = अणुपूर्ण;
	u64 result;
	पूर्णांक rc;

	test_pkt.ctl = cpu_to_le32(CPUCP_PACKET_TEST <<
					CPUCP_PKT_CTL_OPCODE_SHIFT);
	test_pkt.value = cpu_to_le64(CPUCP_PACKET_FENCE_VAL);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &test_pkt,
						माप(test_pkt), 0, &result);

	अगर (!rc) अणु
		अगर (result != CPUCP_PACKET_FENCE_VAL)
			dev_err(hdev->dev,
				"CPU queue test failed (%#08llx)\n", result);
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev, "CPU queue test failed, error %d\n", rc);
	पूर्ण

	वापस rc;
पूर्ण

व्योम *hl_fw_cpu_accessible_dma_pool_alloc(काष्ठा hl_device *hdev, माप_प्रकार size,
						dma_addr_t *dma_handle)
अणु
	u64 kernel_addr;

	kernel_addr = gen_pool_alloc(hdev->cpu_accessible_dma_pool, size);

	*dma_handle = hdev->cpu_accessible_dma_address +
		(kernel_addr - (u64) (uपूर्णांकptr_t) hdev->cpu_accessible_dma_mem);

	वापस (व्योम *) (uपूर्णांकptr_t) kernel_addr;
पूर्ण

व्योम hl_fw_cpu_accessible_dma_pool_मुक्त(काष्ठा hl_device *hdev, माप_प्रकार size,
					व्योम *vaddr)
अणु
	gen_pool_मुक्त(hdev->cpu_accessible_dma_pool, (u64) (uपूर्णांकptr_t) vaddr,
			size);
पूर्ण

पूर्णांक hl_fw_send_heartbeat(काष्ठा hl_device *hdev)
अणु
	काष्ठा cpucp_packet hb_pkt = अणुपूर्ण;
	u64 result;
	पूर्णांक rc;

	hb_pkt.ctl = cpu_to_le32(CPUCP_PACKET_TEST <<
					CPUCP_PKT_CTL_OPCODE_SHIFT);
	hb_pkt.value = cpu_to_le64(CPUCP_PACKET_FENCE_VAL);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &hb_pkt,
						माप(hb_pkt), 0, &result);

	अगर ((rc) || (result != CPUCP_PACKET_FENCE_VAL))
		rc = -EIO;

	वापस rc;
पूर्ण

अटल पूर्णांक fw_पढ़ो_errors(काष्ठा hl_device *hdev, u32 boot_err0_reg,
		u32 cpu_security_boot_status_reg)
अणु
	u32 err_val, security_val;
	bool err_exists = false;

	/* Some of the firmware status codes are deprecated in newer f/w
	 * versions. In those versions, the errors are reported
	 * in dअगरferent रेजिस्टरs. Thereक्रमe, we need to check those
	 * रेजिस्टरs and prपूर्णांक the exact errors. Moreover, there
	 * may be multiple errors, so we need to report on each error
	 * separately. Some of the error codes might indicate a state
	 * that is not an error per-se, but it is an error in production
	 * environment
	 */
	err_val = RREG32(boot_err0_reg);
	अगर (!(err_val & CPU_BOOT_ERR0_ENABLED))
		वापस 0;

	अगर (err_val & CPU_BOOT_ERR0_DRAM_INIT_FAIL) अणु
		dev_err(hdev->dev,
			"Device boot error - DRAM initialization failed\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_FIT_CORRUPTED) अणु
		dev_err(hdev->dev, "Device boot error - FIT image corrupted\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_TS_INIT_FAIL) अणु
		dev_err(hdev->dev,
			"Device boot error - Thermal Sensor initialization failed\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_DRAM_SKIPPED) अणु
		dev_warn(hdev->dev,
			"Device boot warning - Skipped DRAM initialization\n");
		/* This is a warning so we करोn't want it to disable the
		 * device
		 */
		err_val &= ~CPU_BOOT_ERR0_DRAM_SKIPPED;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_BMC_WAIT_SKIPPED) अणु
		अगर (hdev->bmc_enable) अणु
			dev_err(hdev->dev,
				"Device boot error - Skipped waiting for BMC\n");
			err_exists = true;
		पूर्ण अन्यथा अणु
			dev_info(hdev->dev,
				"Device boot message - Skipped waiting for BMC\n");
			/* This is an info so we करोn't want it to disable the
			 * device
			 */
			err_val &= ~CPU_BOOT_ERR0_BMC_WAIT_SKIPPED;
		पूर्ण
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_NIC_DATA_NOT_RDY) अणु
		dev_err(hdev->dev,
			"Device boot error - Serdes data from BMC not available\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_NIC_FW_FAIL) अणु
		dev_err(hdev->dev,
			"Device boot error - NIC F/W initialization failed\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_SECURITY_NOT_RDY) अणु
		dev_err(hdev->dev,
			"Device boot warning - security not ready\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_SECURITY_FAIL) अणु
		dev_err(hdev->dev, "Device boot error - security failure\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_EFUSE_FAIL) अणु
		dev_err(hdev->dev, "Device boot error - eFuse failure\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_PLL_FAIL) अणु
		dev_err(hdev->dev, "Device boot error - PLL failure\n");
		err_exists = true;
	पूर्ण

	अगर (err_val & CPU_BOOT_ERR0_DEVICE_UNUSABLE_FAIL) अणु
		dev_err(hdev->dev,
			"Device boot error - device unusable\n");
		err_exists = true;
	पूर्ण

	security_val = RREG32(cpu_security_boot_status_reg);
	अगर (security_val & CPU_BOOT_DEV_STS0_ENABLED)
		dev_dbg(hdev->dev, "Device security status %#x\n",
				security_val);

	अगर (!err_exists && (err_val & ~CPU_BOOT_ERR0_ENABLED)) अणु
		dev_err(hdev->dev,
			"Device boot error - unknown error 0x%08x\n",
			err_val);
		err_exists = true;
	पूर्ण

	अगर (err_exists && ((err_val & ~CPU_BOOT_ERR0_ENABLED) &
				lower_32_bits(hdev->boot_error_status_mask)))
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक hl_fw_cpucp_info_get(काष्ठा hl_device *hdev,
			u32 cpu_security_boot_status_reg,
			u32 boot_err0_reg)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा cpucp_packet pkt = अणुपूर्ण;
	व्योम *cpucp_info_cpu_addr;
	dma_addr_t cpucp_info_dma_addr;
	u64 result;
	पूर्णांक rc;

	cpucp_info_cpu_addr =
			hdev->asic_funcs->cpu_accessible_dma_pool_alloc(hdev,
					माप(काष्ठा cpucp_info),
					&cpucp_info_dma_addr);
	अगर (!cpucp_info_cpu_addr) अणु
		dev_err(hdev->dev,
			"Failed to allocate DMA memory for CPU-CP info packet\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(cpucp_info_cpu_addr, 0, माप(काष्ठा cpucp_info));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_INFO_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.addr = cpu_to_le64(cpucp_info_dma_addr);
	pkt.data_max_size = cpu_to_le32(माप(काष्ठा cpucp_info));

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
					HL_CPUCP_INFO_TIMEOUT_USEC, &result);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to handle CPU-CP info pkt, error %d\n", rc);
		जाओ out;
	पूर्ण

	rc = fw_पढ़ो_errors(hdev, boot_err0_reg, cpu_security_boot_status_reg);
	अगर (rc) अणु
		dev_err(hdev->dev, "Errors in device boot\n");
		जाओ out;
	पूर्ण

	स_नकल(&prop->cpucp_info, cpucp_info_cpu_addr,
			माप(prop->cpucp_info));

	rc = hl_build_hwmon_channel_info(hdev, prop->cpucp_info.sensors);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to build hwmon channel info, error %d\n", rc);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	/* Read FW application security bits again */
	अगर (hdev->asic_prop.fw_security_status_valid)
		hdev->asic_prop.fw_app_security_map =
				RREG32(cpu_security_boot_status_reg);

out:
	hdev->asic_funcs->cpu_accessible_dma_pool_मुक्त(hdev,
			माप(काष्ठा cpucp_info), cpucp_info_cpu_addr);

	वापस rc;
पूर्ण

अटल पूर्णांक hl_fw_send_msi_info_msg(काष्ठा hl_device *hdev)
अणु
	काष्ठा cpucp_array_data_packet *pkt;
	माप_प्रकार total_pkt_size, data_size;
	u64 result;
	पूर्णांक rc;

	/* skip sending this info क्रम unsupported ASICs */
	अगर (!hdev->asic_funcs->get_msi_info)
		वापस 0;

	data_size = CPUCP_NUM_OF_MSI_TYPES * माप(u32);
	total_pkt_size = माप(काष्ठा cpucp_array_data_packet) + data_size;

	/* data should be aligned to 8 bytes in order to CPU-CP to copy it */
	total_pkt_size = (total_pkt_size + 0x7) & ~0x7;

	/* total_pkt_size is casted to u16 later on */
	अगर (total_pkt_size > अच_लघु_उच्च) अणु
		dev_err(hdev->dev, "CPUCP array data is too big\n");
		वापस -EINVAL;
	पूर्ण

	pkt = kzalloc(total_pkt_size, GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	pkt->length = cpu_to_le32(CPUCP_NUM_OF_MSI_TYPES);

	hdev->asic_funcs->get_msi_info((u32 *)&pkt->data);

	pkt->cpucp_pkt.ctl = cpu_to_le32(CPUCP_PACKET_MSI_INFO_SET <<
						CPUCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *)pkt,
						total_pkt_size, 0, &result);

	/*
	 * in हाल packet result is invalid it means that FW करोes not support
	 * this feature and will use शेष/hard coded MSI values. no reason
	 * to stop the boot
	 */
	अगर (rc && result == cpucp_packet_invalid)
		rc = 0;

	अगर (rc)
		dev_err(hdev->dev, "failed to send CPUCP array data\n");

	kमुक्त(pkt);

	वापस rc;
पूर्ण

पूर्णांक hl_fw_cpucp_handshake(काष्ठा hl_device *hdev,
			u32 cpu_security_boot_status_reg,
			u32 boot_err0_reg)
अणु
	पूर्णांक rc;

	rc = hl_fw_cpucp_info_get(hdev, cpu_security_boot_status_reg,
					boot_err0_reg);
	अगर (rc)
		वापस rc;

	वापस hl_fw_send_msi_info_msg(hdev);
पूर्ण

पूर्णांक hl_fw_get_eeprom_data(काष्ठा hl_device *hdev, व्योम *data, माप_प्रकार max_size)
अणु
	काष्ठा cpucp_packet pkt = अणुपूर्ण;
	व्योम *eeprom_info_cpu_addr;
	dma_addr_t eeprom_info_dma_addr;
	u64 result;
	पूर्णांक rc;

	eeprom_info_cpu_addr =
			hdev->asic_funcs->cpu_accessible_dma_pool_alloc(hdev,
					max_size, &eeprom_info_dma_addr);
	अगर (!eeprom_info_cpu_addr) अणु
		dev_err(hdev->dev,
			"Failed to allocate DMA memory for CPU-CP EEPROM packet\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(eeprom_info_cpu_addr, 0, max_size);

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_EEPROM_DATA_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.addr = cpu_to_le64(eeprom_info_dma_addr);
	pkt.data_max_size = cpu_to_le32(max_size);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
			HL_CPUCP_EEPROM_TIMEOUT_USEC, &result);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to handle CPU-CP EEPROM packet, error %d\n",
			rc);
		जाओ out;
	पूर्ण

	/* result contains the actual size */
	स_नकल(data, eeprom_info_cpu_addr, min((माप_प्रकार)result, max_size));

out:
	hdev->asic_funcs->cpu_accessible_dma_pool_मुक्त(hdev, max_size,
			eeprom_info_cpu_addr);

	वापस rc;
पूर्ण

पूर्णांक hl_fw_cpucp_pci_counters_get(काष्ठा hl_device *hdev,
		काष्ठा hl_info_pci_counters *counters)
अणु
	काष्ठा cpucp_packet pkt = अणुपूर्ण;
	u64 result;
	पूर्णांक rc;

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_PCIE_THROUGHPUT_GET <<
			CPUCP_PKT_CTL_OPCODE_SHIFT);

	/* Fetch PCI rx counter */
	pkt.index = cpu_to_le32(cpucp_pcie_throughput_rx);
	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
					HL_CPUCP_INFO_TIMEOUT_USEC, &result);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to handle CPU-CP PCI info pkt, error %d\n", rc);
		वापस rc;
	पूर्ण
	counters->rx_throughput = result;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.ctl = cpu_to_le32(CPUCP_PACKET_PCIE_THROUGHPUT_GET <<
			CPUCP_PKT_CTL_OPCODE_SHIFT);

	/* Fetch PCI tx counter */
	pkt.index = cpu_to_le32(cpucp_pcie_throughput_tx);
	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
					HL_CPUCP_INFO_TIMEOUT_USEC, &result);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to handle CPU-CP PCI info pkt, error %d\n", rc);
		वापस rc;
	पूर्ण
	counters->tx_throughput = result;

	/* Fetch PCI replay counter */
	स_रखो(&pkt, 0, माप(pkt));
	pkt.ctl = cpu_to_le32(CPUCP_PACKET_PCIE_REPLAY_CNT_GET <<
			CPUCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
			HL_CPUCP_INFO_TIMEOUT_USEC, &result);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to handle CPU-CP PCI info pkt, error %d\n", rc);
		वापस rc;
	पूर्ण
	counters->replay_cnt = (u32) result;

	वापस rc;
पूर्ण

पूर्णांक hl_fw_cpucp_total_energy_get(काष्ठा hl_device *hdev, u64 *total_energy)
अणु
	काष्ठा cpucp_packet pkt = अणुपूर्ण;
	u64 result;
	पूर्णांक rc;

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_TOTAL_ENERGY_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
					HL_CPUCP_INFO_TIMEOUT_USEC, &result);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to handle CpuCP total energy pkt, error %d\n",
				rc);
		वापस rc;
	पूर्ण

	*total_energy = result;

	वापस rc;
पूर्ण

पूर्णांक get_used_pll_index(काष्ठा hl_device *hdev, u32 input_pll_index,
						क्रमागत pll_index *pll_index)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u8 pll_byte, pll_bit_off;
	bool dynamic_pll;
	पूर्णांक fw_pll_idx;

	dynamic_pll = prop->fw_security_status_valid &&
		(prop->fw_app_security_map & CPU_BOOT_DEV_STS0_DYN_PLL_EN);

	अगर (!dynamic_pll) अणु
		/*
		 * in हाल we are working with legacy FW (each asic has unique
		 * PLL numbering) use the driver based index as they are
		 * aligned with fw legacy numbering
		 */
		*pll_index = input_pll_index;
		वापस 0;
	पूर्ण

	/* retrieve a FW compatible PLL index based on
	 * ASIC specअगरic user request
	 */
	fw_pll_idx = hdev->asic_funcs->map_pll_idx_to_fw_idx(input_pll_index);
	अगर (fw_pll_idx < 0) अणु
		dev_err(hdev->dev, "Invalid PLL index (%u) error %d\n",
			input_pll_index, fw_pll_idx);
		वापस -EINVAL;
	पूर्ण

	/* PLL map is a u8 array */
	pll_byte = prop->cpucp_info.pll_map[fw_pll_idx >> 3];
	pll_bit_off = fw_pll_idx & 0x7;

	अगर (!(pll_byte & BIT(pll_bit_off))) अणु
		dev_err(hdev->dev, "PLL index %d is not supported\n",
			fw_pll_idx);
		वापस -EINVAL;
	पूर्ण

	*pll_index = fw_pll_idx;

	वापस 0;
पूर्ण

पूर्णांक hl_fw_cpucp_pll_info_get(काष्ठा hl_device *hdev, u32 pll_index,
		u16 *pll_freq_arr)
अणु
	काष्ठा cpucp_packet pkt;
	क्रमागत pll_index used_pll_idx;
	u64 result;
	पूर्णांक rc;

	rc = get_used_pll_index(hdev, pll_index, &used_pll_idx);
	अगर (rc)
		वापस rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_PLL_INFO_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.pll_type = __cpu_to_le16((u16)used_pll_idx);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
			HL_CPUCP_INFO_TIMEOUT_USEC, &result);
	अगर (rc)
		dev_err(hdev->dev, "Failed to read PLL info, error %d\n", rc);

	pll_freq_arr[0] = FIELD_GET(CPUCP_PKT_RES_PLL_OUT0_MASK, result);
	pll_freq_arr[1] = FIELD_GET(CPUCP_PKT_RES_PLL_OUT1_MASK, result);
	pll_freq_arr[2] = FIELD_GET(CPUCP_PKT_RES_PLL_OUT2_MASK, result);
	pll_freq_arr[3] = FIELD_GET(CPUCP_PKT_RES_PLL_OUT3_MASK, result);

	वापस rc;
पूर्ण

पूर्णांक hl_fw_cpucp_घातer_get(काष्ठा hl_device *hdev, u64 *घातer)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_POWER_GET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
			HL_CPUCP_INFO_TIMEOUT_USEC, &result);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to read power, error %d\n", rc);
		वापस rc;
	पूर्ण

	*घातer = result;

	वापस rc;
पूर्ण

अटल व्योम detect_cpu_boot_status(काष्ठा hl_device *hdev, u32 status)
अणु
	/* Some of the status codes below are deprecated in newer f/w
	 * versions but we keep them here क्रम backward compatibility
	 */
	चयन (status) अणु
	हाल CPU_BOOT_STATUS_NA:
		dev_err(hdev->dev,
			"Device boot error - BTL did NOT run\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_IN_WFE:
		dev_err(hdev->dev,
			"Device boot error - Stuck inside WFE loop\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_IN_BTL:
		dev_err(hdev->dev,
			"Device boot error - Stuck in BTL\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_IN_PREBOOT:
		dev_err(hdev->dev,
			"Device boot error - Stuck in Preboot\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_IN_SPL:
		dev_err(hdev->dev,
			"Device boot error - Stuck in SPL\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_IN_UBOOT:
		dev_err(hdev->dev,
			"Device boot error - Stuck in u-boot\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_DRAM_INIT_FAIL:
		dev_err(hdev->dev,
			"Device boot error - DRAM initialization failed\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_UBOOT_NOT_READY:
		dev_err(hdev->dev,
			"Device boot error - u-boot stopped by user\n");
		अवरोध;
	हाल CPU_BOOT_STATUS_TS_INIT_FAIL:
		dev_err(hdev->dev,
			"Device boot error - Thermal Sensor initialization failed\n");
		अवरोध;
	शेष:
		dev_err(hdev->dev,
			"Device boot error - Invalid status code %d\n",
			status);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक hl_fw_पढ़ो_preboot_status(काष्ठा hl_device *hdev, u32 cpu_boot_status_reg,
		u32 cpu_security_boot_status_reg, u32 boot_err0_reg,
		u32 समयout)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u32 status, security_status;
	पूर्णांक rc;

	/* pldm was added क्रम हालs in which we use preboot on pldm and want
	 * to load boot fit, but we can't रुको क्रम preboot because it runs
	 * very slowly
	 */
	अगर (!(hdev->fw_components & FW_TYPE_PREBOOT_CPU) || hdev->pldm)
		वापस 0;

	/* Need to check two possible scenarios:
	 *
	 * CPU_BOOT_STATUS_WAITING_FOR_BOOT_FIT - क्रम newer firmwares where
	 * the preboot is रुकोing क्रम the boot fit
	 *
	 * All other status values - क्रम older firmwares where the uboot was
	 * loaded from the FLASH
	 */
	rc = hl_poll_समयout(
		hdev,
		cpu_boot_status_reg,
		status,
		(status == CPU_BOOT_STATUS_IN_UBOOT) ||
		(status == CPU_BOOT_STATUS_DRAM_RDY) ||
		(status == CPU_BOOT_STATUS_NIC_FW_RDY) ||
		(status == CPU_BOOT_STATUS_READY_TO_BOOT) ||
		(status == CPU_BOOT_STATUS_SRAM_AVAIL) ||
		(status == CPU_BOOT_STATUS_WAITING_FOR_BOOT_FIT),
		10000,
		समयout);

	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to read preboot version\n");
		detect_cpu_boot_status(hdev, status);

		/* If we पढ़ो all FF, then something is totally wrong, no poपूर्णांक
		 * of पढ़ोing specअगरic errors
		 */
		अगर (status != -1)
			fw_पढ़ो_errors(hdev, boot_err0_reg,
					cpu_security_boot_status_reg);
		वापस -EIO;
	पूर्ण

	rc = hdev->asic_funcs->पढ़ो_device_fw_version(hdev, FW_COMP_PREBOOT);
	अगर (rc)
		वापस rc;

	security_status = RREG32(cpu_security_boot_status_reg);

	/* We पढ़ो security status multiple बार during boot:
	 * 1. preboot - a. Check whether the security status bits are valid
	 *              b. Check whether fw security is enabled
	 *              c. Check whether hard reset is करोne by preboot
	 * 2. boot cpu - a. Fetch boot cpu security status
	 *               b. Check whether hard reset is करोne by boot cpu
	 * 3. FW application - a. Fetch fw application security status
	 *                     b. Check whether hard reset is करोne by fw app
	 *
	 * Preboot:
	 * Check security status bit (CPU_BOOT_DEV_STS0_ENABLED), अगर it is set
	 * check security enabled bit (CPU_BOOT_DEV_STS0_SECURITY_EN)
	 */
	अगर (security_status & CPU_BOOT_DEV_STS0_ENABLED) अणु
		prop->fw_security_status_valid = 1;

		/* FW security should be derived from PCI ID, we keep this
		 * check क्रम backward compatibility
		 */
		अगर (security_status & CPU_BOOT_DEV_STS0_SECURITY_EN)
			prop->fw_security_disabled = false;

		अगर (security_status & CPU_BOOT_DEV_STS0_FW_HARD_RST_EN)
			prop->hard_reset_करोne_by_fw = true;
	पूर्ण अन्यथा अणु
		prop->fw_security_status_valid = 0;
	पूर्ण

	dev_dbg(hdev->dev, "Firmware preboot security status %#x\n",
			security_status);

	dev_dbg(hdev->dev, "Firmware preboot hard-reset is %s\n",
			prop->hard_reset_करोne_by_fw ? "enabled" : "disabled");

	dev_info(hdev->dev, "firmware-level security is %s\n",
			prop->fw_security_disabled ? "disabled" : "enabled");

	वापस 0;
पूर्ण

पूर्णांक hl_fw_init_cpu(काष्ठा hl_device *hdev, u32 cpu_boot_status_reg,
			u32 msg_to_cpu_reg, u32 cpu_msg_status_reg,
			u32 cpu_security_boot_status_reg, u32 boot_err0_reg,
			bool skip_bmc, u32 cpu_समयout, u32 boot_fit_समयout)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u32 status;
	पूर्णांक rc;

	अगर (!(hdev->fw_components & FW_TYPE_BOOT_CPU))
		वापस 0;

	dev_info(hdev->dev, "Going to wait for device boot (up to %lds)\n",
		cpu_समयout / USEC_PER_SEC);

	/* Wait क्रम boot FIT request */
	rc = hl_poll_समयout(
		hdev,
		cpu_boot_status_reg,
		status,
		status == CPU_BOOT_STATUS_WAITING_FOR_BOOT_FIT,
		10000,
		boot_fit_समयout);

	अगर (rc) अणु
		dev_dbg(hdev->dev,
			"No boot fit request received, resuming boot\n");
	पूर्ण अन्यथा अणु
		rc = hdev->asic_funcs->load_boot_fit_to_device(hdev);
		अगर (rc)
			जाओ out;

		/* Clear device CPU message status */
		WREG32(cpu_msg_status_reg, CPU_MSG_CLR);

		/* Signal device CPU that boot loader is पढ़ोy */
		WREG32(msg_to_cpu_reg, KMD_MSG_FIT_RDY);

		/* Poll क्रम CPU device ack */
		rc = hl_poll_समयout(
			hdev,
			cpu_msg_status_reg,
			status,
			status == CPU_MSG_OK,
			10000,
			boot_fit_समयout);

		अगर (rc) अणु
			dev_err(hdev->dev,
				"Timeout waiting for boot fit load ack\n");
			जाओ out;
		पूर्ण

		/* Clear message */
		WREG32(msg_to_cpu_reg, KMD_MSG_NA);
	पूर्ण

	/* Make sure CPU boot-loader is running */
	rc = hl_poll_समयout(
		hdev,
		cpu_boot_status_reg,
		status,
		(status == CPU_BOOT_STATUS_DRAM_RDY) ||
		(status == CPU_BOOT_STATUS_NIC_FW_RDY) ||
		(status == CPU_BOOT_STATUS_READY_TO_BOOT) ||
		(status == CPU_BOOT_STATUS_SRAM_AVAIL),
		10000,
		cpu_समयout);

	dev_dbg(hdev->dev, "uboot status = %d\n", status);

	/* Read U-Boot version now in हाल we will later fail */
	hdev->asic_funcs->पढ़ो_device_fw_version(hdev, FW_COMP_UBOOT);

	/* Clear reset status since we need to पढ़ो it again from boot CPU */
	prop->hard_reset_करोne_by_fw = false;

	/* Read boot_cpu security bits */
	अगर (prop->fw_security_status_valid) अणु
		prop->fw_boot_cpu_security_map =
				RREG32(cpu_security_boot_status_reg);

		अगर (prop->fw_boot_cpu_security_map &
				CPU_BOOT_DEV_STS0_FW_HARD_RST_EN)
			prop->hard_reset_करोne_by_fw = true;

		dev_dbg(hdev->dev,
			"Firmware boot CPU security status %#x\n",
			prop->fw_boot_cpu_security_map);
	पूर्ण

	dev_dbg(hdev->dev, "Firmware boot CPU hard-reset is %s\n",
			prop->hard_reset_करोne_by_fw ? "enabled" : "disabled");

	अगर (rc) अणु
		detect_cpu_boot_status(hdev, status);
		rc = -EIO;
		जाओ out;
	पूर्ण

	अगर (!(hdev->fw_components & FW_TYPE_LINUX)) अणु
		dev_info(hdev->dev, "Skip loading Linux F/W\n");
		जाओ out;
	पूर्ण

	अगर (status == CPU_BOOT_STATUS_SRAM_AVAIL)
		जाओ out;

	dev_info(hdev->dev,
		"Loading firmware to device, may take some time...\n");

	rc = hdev->asic_funcs->load_firmware_to_device(hdev);
	अगर (rc)
		जाओ out;

	अगर (skip_bmc) अणु
		WREG32(msg_to_cpu_reg, KMD_MSG_SKIP_BMC);

		rc = hl_poll_समयout(
			hdev,
			cpu_boot_status_reg,
			status,
			(status == CPU_BOOT_STATUS_BMC_WAITING_SKIPPED),
			10000,
			cpu_समयout);

		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to get ACK on skipping BMC, %d\n",
				status);
			WREG32(msg_to_cpu_reg, KMD_MSG_NA);
			rc = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	WREG32(msg_to_cpu_reg, KMD_MSG_FIT_RDY);

	rc = hl_poll_समयout(
		hdev,
		cpu_boot_status_reg,
		status,
		(status == CPU_BOOT_STATUS_SRAM_AVAIL),
		10000,
		cpu_समयout);

	/* Clear message */
	WREG32(msg_to_cpu_reg, KMD_MSG_NA);

	अगर (rc) अणु
		अगर (status == CPU_BOOT_STATUS_FIT_CORRUPTED)
			dev_err(hdev->dev,
				"Device reports FIT image is corrupted\n");
		अन्यथा
			dev_err(hdev->dev,
				"Failed to load firmware to device, %d\n",
				status);

		rc = -EIO;
		जाओ out;
	पूर्ण

	rc = fw_पढ़ो_errors(hdev, boot_err0_reg, cpu_security_boot_status_reg);
	अगर (rc)
		वापस rc;

	/* Clear reset status since we need to पढ़ो again from app */
	prop->hard_reset_करोne_by_fw = false;

	/* Read FW application security bits */
	अगर (prop->fw_security_status_valid) अणु
		prop->fw_app_security_map =
				RREG32(cpu_security_boot_status_reg);

		अगर (prop->fw_app_security_map &
				CPU_BOOT_DEV_STS0_FW_HARD_RST_EN)
			prop->hard_reset_करोne_by_fw = true;

		dev_dbg(hdev->dev,
			"Firmware application CPU security status %#x\n",
			prop->fw_app_security_map);
	पूर्ण

	dev_dbg(hdev->dev, "Firmware application CPU hard-reset is %s\n",
			prop->hard_reset_करोne_by_fw ? "enabled" : "disabled");

	dev_info(hdev->dev, "Successfully loaded firmware to device\n");

	वापस 0;

out:
	fw_पढ़ो_errors(hdev, boot_err0_reg, cpu_security_boot_status_reg);

	वापस rc;
पूर्ण
