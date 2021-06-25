<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#समावेश <scsi/iscsi_अगर.h>
#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"
#समावेश "ql4_inline.h"

अटल व्योम ql4xxx_set_mac_number(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t value;
	अचिन्हित दीर्घ flags;

	/* Get the function number */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	value = पढ़ोw(&ha->reg->ctrl_status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	चयन (value & ISP_CONTROL_FN_MASK) अणु
	हाल ISP_CONTROL_FN0_SCSI:
		ha->mac_index = 1;
		अवरोध;
	हाल ISP_CONTROL_FN1_SCSI:
		ha->mac_index = 3;
		अवरोध;
	शेष:
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Invalid function number, "
			      "ispControlStatus = 0x%x\n", ha->host_no,
			      __func__, value));
		अवरोध;
	पूर्ण
	DEBUG2(prपूर्णांकk("scsi%ld: %s: mac_index %d.\n", ha->host_no, __func__,
		      ha->mac_index));
पूर्ण

/**
 * qla4xxx_मुक्त_ddb - deallocate ddb
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 * @ddb_entry: poपूर्णांकer to device database entry
 *
 * This routine marks a DDB entry INVALID
 **/
व्योम qla4xxx_मुक्त_ddb(काष्ठा scsi_qla_host *ha,
    काष्ठा ddb_entry *ddb_entry)
अणु
	/* Remove device poपूर्णांकer from index mapping arrays */
	ha->fw_ddb_index_map[ddb_entry->fw_ddb_index] =
		(काष्ठा ddb_entry *) INVALID_ENTRY;
	ha->tot_ddbs--;
पूर्ण

/**
 * qla4xxx_init_response_q_entries() - Initializes response queue entries.
 * @ha: HA context
 *
 * Beginning of request ring has initialization control block alपढ़ोy built
 * by nvram config routine.
 **/
अटल व्योम qla4xxx_init_response_q_entries(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t cnt;
	काष्ठा response *pkt;

	pkt = (काष्ठा response *)ha->response_ptr;
	क्रम (cnt = 0; cnt < RESPONSE_QUEUE_DEPTH; cnt++) अणु
		pkt->signature = RESPONSE_PROCESSED;
		pkt++;
	पूर्ण
पूर्ण

/**
 * qla4xxx_init_rings - initialize hw queues
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine initializes the पूर्णांकernal queues क्रम the specअगरied adapter.
 * The QLA4010 requires us to restart the queues at index 0.
 * The QLA4000 करोesn't care, so just default to QLA4010's requirement.
 **/
पूर्णांक qla4xxx_init_rings(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक i;

	/* Initialize request queue. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->request_out = 0;
	ha->request_in = 0;
	ha->request_ptr = &ha->request_ring[ha->request_in];
	ha->req_q_count = REQUEST_QUEUE_DEPTH;

	/* Initialize response queue. */
	ha->response_in = 0;
	ha->response_out = 0;
	ha->response_ptr = &ha->response_ring[ha->response_out];

	अगर (is_qla8022(ha)) अणु
		ग_लिखोl(0,
		    (अचिन्हित दीर्घ  __iomem *)&ha->qla4_82xx_reg->req_q_out);
		ग_लिखोl(0,
		    (अचिन्हित दीर्घ  __iomem *)&ha->qla4_82xx_reg->rsp_q_in);
		ग_लिखोl(0,
		    (अचिन्हित दीर्घ  __iomem *)&ha->qla4_82xx_reg->rsp_q_out);
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		ग_लिखोl(0,
		       (अचिन्हित दीर्घ __iomem *)&ha->qla4_83xx_reg->req_q_in);
		ग_लिखोl(0,
		       (अचिन्हित दीर्घ __iomem *)&ha->qla4_83xx_reg->rsp_q_in);
		ग_लिखोl(0,
		       (अचिन्हित दीर्घ __iomem *)&ha->qla4_83xx_reg->rsp_q_out);
	पूर्ण अन्यथा अणु
		/*
		 * Initialize DMA Shaकरोw रेजिस्टरs.  The firmware is really
		 * supposed to take care of this, but on some uniprocessor
		 * प्रणालीs, the shaकरोw रेजिस्टरs aren't cleared-- causing
		 * the पूर्णांकerrupt_handler to think there are responses to be
		 * processed when there aren't.
		 */
		ha->shaकरोw_regs->req_q_out = __स्थिरant_cpu_to_le32(0);
		ha->shaकरोw_regs->rsp_q_in = __स्थिरant_cpu_to_le32(0);
		wmb();

		ग_लिखोl(0, &ha->reg->req_q_in);
		ग_लिखोl(0, &ha->reg->rsp_q_out);
		पढ़ोl(&ha->reg->rsp_q_out);
	पूर्ण

	qla4xxx_init_response_q_entries(ha);

	/* Initialize mailbox active array */
	क्रम (i = 0; i < MAX_MRB; i++)
		ha->active_mrb_array[i] = शून्य;

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_get_sys_info - validate adapter MAC address(es)
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 **/
पूर्णांक qla4xxx_get_sys_info(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा flash_sys_info *sys_info;
	dma_addr_t sys_info_dma;
	पूर्णांक status = QLA_ERROR;

	sys_info = dma_alloc_coherent(&ha->pdev->dev, माप(*sys_info),
				      &sys_info_dma, GFP_KERNEL);
	अगर (sys_info == शून्य) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Unable to allocate dma buffer.\n",
			      ha->host_no, __func__));

		जाओ निकास_get_sys_info_no_मुक्त;
	पूर्ण

	/* Get flash sys info */
	अगर (qla4xxx_get_flash(ha, sys_info_dma, FLASH_OFFSET_SYS_INFO,
			      माप(*sys_info)) != QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: get_flash FLASH_OFFSET_SYS_INFO "
			      "failed\n", ha->host_no, __func__));

		जाओ निकास_get_sys_info;
	पूर्ण

	/* Save M.A.C. address & serial_number */
	स_नकल(ha->my_mac, &sys_info->physAddr[0].address[0],
	       min(माप(ha->my_mac),
		   माप(sys_info->physAddr[0].address)));
	स_नकल(ha->serial_number, &sys_info->acSerialNumber,
	       min(माप(ha->serial_number),
		   माप(sys_info->acSerialNumber)));

	status = QLA_SUCCESS;

निकास_get_sys_info:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(*sys_info), sys_info,
			  sys_info_dma);

निकास_get_sys_info_no_मुक्त:
	वापस status;
पूर्ण

/**
 * qla4xxx_init_local_data - initialize adapter specअगरic local data
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 **/
अटल व्योम qla4xxx_init_local_data(काष्ठा scsi_qla_host *ha)
अणु
	/* Initialize aen queue */
	ha->aen_q_count = MAX_AEN_ENTRIES;
पूर्ण

अटल uपूर्णांक8_t
qla4xxx_रुको_क्रम_ip_config(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक8_t ipv4_रुको = 0;
	uपूर्णांक8_t ipv6_रुको = 0;
	पूर्णांक8_t ip_address[IPv6_ADDR_LEN] = अणु0पूर्ण ;

	/* If both IPv4 & IPv6 are enabled, possibly only one
	 * IP address may be acquired, so check to see अगर we
	 * need to रुको क्रम another */
	अगर (is_ipv4_enabled(ha) && is_ipv6_enabled(ha)) अणु
		अगर (((ha->addl_fw_state & FW_ADDSTATE_DHCPv4_ENABLED) != 0) &&
		    ((ha->addl_fw_state &
				    FW_ADDSTATE_DHCPv4_LEASE_ACQUIRED) == 0)) अणु
			ipv4_रुको = 1;
		पूर्ण
		अगर (((ha->ip_config.ipv6_addl_options &
		      IPV6_ADDOPT_NEIGHBOR_DISCOVERY_ADDR_ENABLE) != 0) &&
		    ((ha->ip_config.ipv6_link_local_state ==
		      IP_ADDRSTATE_ACQUIRING) ||
		     (ha->ip_config.ipv6_addr0_state ==
		      IP_ADDRSTATE_ACQUIRING) ||
		     (ha->ip_config.ipv6_addr1_state ==
		      IP_ADDRSTATE_ACQUIRING))) अणु

			ipv6_रुको = 1;

			अगर ((ha->ip_config.ipv6_link_local_state ==
			     IP_ADDRSTATE_PREFERRED) ||
			    (ha->ip_config.ipv6_addr0_state ==
			     IP_ADDRSTATE_PREFERRED) ||
			    (ha->ip_config.ipv6_addr1_state ==
			     IP_ADDRSTATE_PREFERRED)) अणु
				DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: "
					      "Preferred IP configured."
					      " Don't wait!\n", ha->host_no,
					      __func__));
				ipv6_रुको = 0;
			पूर्ण
			अगर (स_भेद(&ha->ip_config.ipv6_शेष_router_addr,
				   ip_address, IPv6_ADDR_LEN) == 0) अणु
				DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: "
					      "No Router configured. "
					      "Don't wait!\n", ha->host_no,
					      __func__));
				ipv6_रुको = 0;
			पूर्ण
			अगर ((ha->ip_config.ipv6_शेष_router_state ==
			     IPV6_RTRSTATE_MANUAL) &&
			    (ha->ip_config.ipv6_link_local_state ==
			     IP_ADDRSTATE_TENTATIVE) &&
			    (स_भेद(&ha->ip_config.ipv6_link_local_addr,
			     &ha->ip_config.ipv6_शेष_router_addr, 4) ==
			     0)) अणु
				DEBUG2(prपूर्णांकk("scsi%ld: %s: LinkLocal Router & "
					"IP configured. Don't wait!\n",
					ha->host_no, __func__));
				ipv6_रुको = 0;
			पूर्ण
		पूर्ण
		अगर (ipv4_रुको || ipv6_रुको) अणु
			DEBUG2(prपूर्णांकk("scsi%ld: %s: Wait for additional "
				      "IP(s) \"", ha->host_no, __func__));
			अगर (ipv4_रुको)
				DEBUG2(prपूर्णांकk("IPv4 "));
			अगर (ha->ip_config.ipv6_link_local_state ==
			    IP_ADDRSTATE_ACQUIRING)
				DEBUG2(prपूर्णांकk("IPv6LinkLocal "));
			अगर (ha->ip_config.ipv6_addr0_state ==
			    IP_ADDRSTATE_ACQUIRING)
				DEBUG2(prपूर्णांकk("IPv6Addr0 "));
			अगर (ha->ip_config.ipv6_addr1_state ==
			    IP_ADDRSTATE_ACQUIRING)
				DEBUG2(prपूर्णांकk("IPv6Addr1 "));
			DEBUG2(prपूर्णांकk("\"\n"));
		पूर्ण
	पूर्ण

	वापस ipv4_रुको|ipv6_रुको;
पूर्ण

अटल पूर्णांक qla4_80xx_is_minidump_dma_capable(काष्ठा scsi_qla_host *ha,
		काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *md_hdr)
अणु
	पूर्णांक offset = (is_qla8022(ha)) ? QLA8022_TEMPLATE_CAP_OFFSET :
					QLA83XX_TEMPLATE_CAP_OFFSET;
	पूर्णांक rval = 1;
	uपूर्णांक32_t *cap_offset;

	cap_offset = (uपूर्णांक32_t *)((अक्षर *)md_hdr + offset);

	अगर (!(le32_to_cpu(*cap_offset) & BIT_0)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "PEX DMA Not supported %d\n",
			   *cap_offset);
		rval = 0;
	पूर्ण

	वापस rval;
पूर्ण

/**
 * qla4xxx_alloc_fw_dump - Allocate memory क्रम minidump data.
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 **/
व्योम qla4xxx_alloc_fw_dump(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक status;
	uपूर्णांक32_t capture_debug_level;
	पूर्णांक hdr_entry_bit, k;
	व्योम *md_पंचांगp;
	dma_addr_t md_पंचांगp_dma;
	काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *md_hdr;
	पूर्णांक dma_capable;

	अगर (ha->fw_dump) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
			   "Firmware dump previously allocated.\n");
		वापस;
	पूर्ण

	status = qla4xxx_req_ढाँचा_size(ha);
	अगर (status != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "scsi%ld: Failed to get template size\n",
			   ha->host_no);
		वापस;
	पूर्ण

	clear_bit(AF_82XX_FW_DUMPED, &ha->flags);

	/* Allocate memory क्रम saving the ढाँचा */
	md_पंचांगp = dma_alloc_coherent(&ha->pdev->dev, ha->fw_dump_पंचांगplt_size,
				    &md_पंचांगp_dma, GFP_KERNEL);
	अगर (!md_पंचांगp) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "scsi%ld: Failed to allocate DMA memory\n",
			   ha->host_no);
		वापस;
	पूर्ण

	/* Request ढाँचा */
	status =  qla4xxx_get_minidump_ढाँचा(ha, md_पंचांगp_dma);
	अगर (status != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "scsi%ld: Failed to get minidump template\n",
			   ha->host_no);
		जाओ alloc_cleanup;
	पूर्ण

	md_hdr = (काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *)md_पंचांगp;

	dma_capable = qla4_80xx_is_minidump_dma_capable(ha, md_hdr);

	capture_debug_level = md_hdr->capture_debug_level;

	/* Get capture mask based on module loadसमय setting. */
	अगर ((ql4xmdcapmask >= 0x3 && ql4xmdcapmask <= 0x7F) ||
	    (ql4xmdcapmask == 0xFF && dma_capable))  अणु
		ha->fw_dump_capture_mask = ql4xmdcapmask;
	पूर्ण अन्यथा अणु
		अगर (ql4xmdcapmask == 0xFF)
			ql4_prपूर्णांकk(KERN_INFO, ha, "Falling back to default capture mask, as PEX DMA is not supported\n");
		ha->fw_dump_capture_mask = capture_debug_level;
	पूर्ण

	md_hdr->driver_capture_mask = ha->fw_dump_capture_mask;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Minimum num of entries = %d\n",
			  md_hdr->num_of_entries));
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Dump template size  = %d\n",
			  ha->fw_dump_पंचांगplt_size));
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Selected Capture mask =0x%x\n",
			  ha->fw_dump_capture_mask));

	/* Calculate fw_dump_size */
	क्रम (hdr_entry_bit = 0x2, k = 1; (hdr_entry_bit & 0xFF);
	     hdr_entry_bit <<= 1, k++) अणु
		अगर (hdr_entry_bit & ha->fw_dump_capture_mask)
			ha->fw_dump_size += md_hdr->capture_size_array[k];
	पूर्ण

	/* Total firmware dump size including command header */
	ha->fw_dump_size += ha->fw_dump_पंचांगplt_size;
	ha->fw_dump = vदो_स्मृति(ha->fw_dump_size);
	अगर (!ha->fw_dump)
		जाओ alloc_cleanup;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Minidump Template Size = 0x%x KB\n",
			  ha->fw_dump_पंचांगplt_size));
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Total Minidump size = 0x%x KB\n", ha->fw_dump_size));

	स_नकल(ha->fw_dump, md_पंचांगp, ha->fw_dump_पंचांगplt_size);
	ha->fw_dump_पंचांगplt_hdr = ha->fw_dump;

alloc_cleanup:
	dma_मुक्त_coherent(&ha->pdev->dev, ha->fw_dump_पंचांगplt_size,
			  md_पंचांगp, md_पंचांगp_dma);
पूर्ण

अटल पूर्णांक qla4xxx_fw_पढ़ोy(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t समयout_count;
	पूर्णांक पढ़ोy = 0;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Waiting for Firmware Ready..\n"));
	क्रम (समयout_count = ADAPTER_INIT_TOV; समयout_count > 0;
	     समयout_count--) अणु
		अगर (test_and_clear_bit(DPC_GET_DHCP_IP_ADDR, &ha->dpc_flags))
			qla4xxx_get_dhcp_ip_address(ha);

		/* Get firmware state. */
		अगर (qla4xxx_get_firmware_state(ha) != QLA_SUCCESS) अणु
			DEBUG2(prपूर्णांकk("scsi%ld: %s: unable to get firmware "
				      "state\n", ha->host_no, __func__));
			अवरोध;
		पूर्ण

		अगर (ha->firmware_state & FW_STATE_ERROR) अणु
			DEBUG2(prपूर्णांकk("scsi%ld: %s: an unrecoverable error has"
				      " occurred\n", ha->host_no, __func__));
			अवरोध;

		पूर्ण
		अगर (ha->firmware_state & FW_STATE_CONFIG_WAIT) अणु
			/*
			 * The firmware has not yet been issued an Initialize
			 * Firmware command, so issue it now.
			 */
			अगर (qla4xxx_initialize_fw_cb(ha) == QLA_ERROR)
				अवरोध;

			/* Go back and test क्रम पढ़ोy state - no रुको. */
			जारी;
		पूर्ण

		अगर (ha->firmware_state & FW_STATE_WAIT_AUTOCONNECT) अणु
			DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: fwstate:"
				      "AUTOCONNECT in progress\n",
				      ha->host_no, __func__));
		पूर्ण

		अगर (ha->firmware_state & FW_STATE_CONFIGURING_IP) अणु
			DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: fwstate:"
				      " CONFIGURING IP\n",
				      ha->host_no, __func__));
			/*
			 * Check क्रम link state after 15 secs and अगर link is
			 * still DOWN then, cable is unplugged. Ignore "DHCP
			 * in Progress/CONFIGURING IP" bit to check अगर firmware
			 * is in पढ़ोy state or not after 15 secs.
			 * This is applicable क्रम both 2.x & 3.x firmware
			 */
			अगर (समयout_count <= (ADAPTER_INIT_TOV - 15)) अणु
				अगर (ha->addl_fw_state & FW_ADDSTATE_LINK_UP) अणु
					DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s:"
						  " LINK UP (Cable plugged)\n",
						  ha->host_no, __func__));
				पूर्ण अन्यथा अगर (ha->firmware_state &
					  (FW_STATE_CONFIGURING_IP |
							     FW_STATE_READY)) अणु
					DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: "
						"LINK DOWN (Cable unplugged)\n",
						ha->host_no, __func__));
					ha->firmware_state = FW_STATE_READY;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (ha->firmware_state == FW_STATE_READY) अणु
			/* If DHCP IP Addr is available, retrieve it now. */
			अगर (test_and_clear_bit(DPC_GET_DHCP_IP_ADDR,
								&ha->dpc_flags))
				qla4xxx_get_dhcp_ip_address(ha);

			अगर (!qla4xxx_रुको_क्रम_ip_config(ha) ||
							समयout_count == 1) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				    "Firmware Ready..\n"));
				/* The firmware is पढ़ोy to process SCSI
				   commands. */
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					"scsi%ld: %s: MEDIA TYPE"
					" - %s\n", ha->host_no,
					__func__, (ha->addl_fw_state &
					FW_ADDSTATE_OPTICAL_MEDIA)
					!= 0 ? "OPTICAL" : "COPPER"));
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					"scsi%ld: %s: DHCPv4 STATE"
					" Enabled %s\n", ha->host_no,
					 __func__, (ha->addl_fw_state &
					 FW_ADDSTATE_DHCPv4_ENABLED) != 0 ?
					"YES" : "NO"));
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					"scsi%ld: %s: LINK %s\n",
					ha->host_no, __func__,
					(ha->addl_fw_state &
					 FW_ADDSTATE_LINK_UP) != 0 ?
					"UP" : "DOWN"));
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					"scsi%ld: %s: iSNS Service "
					"Started %s\n",
					ha->host_no, __func__,
					(ha->addl_fw_state &
					 FW_ADDSTATE_ISNS_SVC_ENABLED) != 0 ?
					"YES" : "NO"));

				पढ़ोy = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		DEBUG2(prपूर्णांकk("scsi%ld: %s: waiting on fw, state=%x:%x - "
			      "seconds expired= %d\n", ha->host_no, __func__,
			      ha->firmware_state, ha->addl_fw_state,
			      समयout_count));
		अगर (is_qla4032(ha) &&
			!(ha->addl_fw_state & FW_ADDSTATE_LINK_UP) &&
			(समयout_count < ADAPTER_INIT_TOV - 5)) अणु
			अवरोध;
		पूर्ण

		msleep(1000);
	पूर्ण			/* end of क्रम */

	अगर (समयout_count <= 0)
		DEBUG2(prपूर्णांकk("scsi%ld: %s: FW Initialization timed out!\n",
			      ha->host_no, __func__));

	अगर (ha->firmware_state & FW_STATE_CONFIGURING_IP) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: FW initialized, but is reporting "
			      "it's waiting to configure an IP address\n",
			       ha->host_no, __func__));
		पढ़ोy = 1;
	पूर्ण अन्यथा अगर (ha->firmware_state & FW_STATE_WAIT_AUTOCONNECT) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: FW initialized, but "
			      "auto-discovery still in process\n",
			       ha->host_no, __func__));
		पढ़ोy = 1;
	पूर्ण

	वापस पढ़ोy;
पूर्ण

/**
 * qla4xxx_init_firmware - initializes the firmware.
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 **/
अटल पूर्णांक qla4xxx_init_firmware(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक status = QLA_ERROR;

	अगर (is_aer_supported(ha) &&
	    test_bit(AF_PCI_CHANNEL_IO_PERM_FAILURE, &ha->flags))
		वापस status;

	/* For 82xx, stop firmware beक्रमe initializing because अगर BIOS
	 * has previously initialized firmware, then driver's initialize
	 * firmware will fail. */
	अगर (is_qla80XX(ha))
		qla4_8xxx_stop_firmware(ha);

	ql4_prपूर्णांकk(KERN_INFO, ha, "Initializing firmware..\n");
	अगर (qla4xxx_initialize_fw_cb(ha) == QLA_ERROR) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Failed to initialize firmware "
			      "control block\n", ha->host_no, __func__));
		वापस status;
	पूर्ण

	अगर (!qla4xxx_fw_पढ़ोy(ha))
		वापस status;

	अगर (is_qla80XX(ha) && !test_bit(AF_INIT_DONE, &ha->flags))
		qla4xxx_alloc_fw_dump(ha);

	वापस qla4xxx_get_firmware_status(ha);
पूर्ण

अटल व्योम qla4xxx_set_model_info(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t board_id_string[8];
	पूर्णांक i;
	पूर्णांक size = माप(ha->nvram->isp4022.boardIdStr);
	पूर्णांक offset = दुरत्व(काष्ठा eeprom_data, isp4022.boardIdStr) / 2;

	क्रम (i = 0; i < (size / 2) ; i++) अणु
		board_id_string[i] = rd_nvram_word(ha, offset);
		offset += 1;
	पूर्ण

	स_नकल(ha->model_name, board_id_string, size);
पूर्ण

अटल पूर्णांक qla4xxx_config_nvram(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ flags;
	जोड़ बाह्यal_hw_config_reg extHwConfig;

	DEBUG2(prपूर्णांकk("scsi%ld: %s: Get EEProm parameters \n", ha->host_no,
		      __func__));
	अगर (ql4xxx_lock_flash(ha) != QLA_SUCCESS)
		वापस QLA_ERROR;
	अगर (ql4xxx_lock_nvram(ha) != QLA_SUCCESS) अणु
		ql4xxx_unlock_flash(ha);
		वापस QLA_ERROR;
	पूर्ण

	/* Get EEPRom Parameters from NVRAM and validate */
	ql4_prपूर्णांकk(KERN_INFO, ha, "Configuring NVRAM ...\n");
	अगर (qla4xxx_is_nvram_configuration_valid(ha) == QLA_SUCCESS) अणु
		spin_lock_irqsave(&ha->hardware_lock, flags);
		extHwConfig.Asuपूर्णांक32_t =
			rd_nvram_word(ha, eeprom_ext_hw_conf_offset(ha));
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "scsi%ld: %s: EEProm checksum invalid.  "
		    "Please update your EEPROM\n", ha->host_no,
		    __func__);

		/* Attempt to set शेषs */
		अगर (is_qla4010(ha))
			extHwConfig.Asuपूर्णांक32_t = 0x1912;
		अन्यथा अगर (is_qla4022(ha) | is_qla4032(ha))
			extHwConfig.Asuपूर्णांक32_t = 0x0023;
		अन्यथा
			वापस QLA_ERROR;
	पूर्ण

	अगर (is_qla4022(ha) || is_qla4032(ha))
		qla4xxx_set_model_info(ha);
	अन्यथा
		म_नकल(ha->model_name, "QLA4010");

	DEBUG(prपूर्णांकk("scsi%ld: %s: Setting extHwConfig to 0xFFFF%04x\n",
		     ha->host_no, __func__, extHwConfig.Asuपूर्णांक32_t));

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ग_लिखोl((0xFFFF << 16) | extHwConfig.Asuपूर्णांक32_t, isp_ext_hw_conf(ha));
	पढ़ोl(isp_ext_hw_conf(ha));
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	ql4xxx_unlock_nvram(ha);
	ql4xxx_unlock_flash(ha);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4_8xxx_pci_config() - Setup ISP82xx PCI configuration रेजिस्टरs.
 * @ha: HA context
 */
व्योम qla4_8xxx_pci_config(काष्ठा scsi_qla_host *ha)
अणु
	pci_set_master(ha->pdev);
पूर्ण

व्योम qla4xxx_pci_config(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t w;
	पूर्णांक status;

	ql4_prपूर्णांकk(KERN_INFO, ha, "Configuring PCI space...\n");

	pci_set_master(ha->pdev);
	status = pci_set_mwi(ha->pdev);
	अगर (status)
		ql4_prपूर्णांकk(KERN_WARNING, ha, "Failed to set MWI\n");

	/*
	 * We want to respect framework's setting of PCI configuration space
	 * command रेजिस्टर and also want to make sure that all bits of
	 * पूर्णांकerest to us are properly set in command रेजिस्टर.
	 */
	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= PCI_COMMAND_PARITY | PCI_COMMAND_SERR;
	w &= ~PCI_COMMAND_INTX_DISABLE;
	pci_ग_लिखो_config_word(ha->pdev, PCI_COMMAND, w);
पूर्ण

अटल पूर्णांक qla4xxx_start_firmware_from_flash(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक status = QLA_ERROR;
	अचिन्हित दीर्घ max_रुको_समय;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t mbox_status;

	ql4_prपूर्णांकk(KERN_INFO, ha, "Starting firmware ...\n");

	/*
	 * Start firmware from flash ROM
	 *
	 * WORKAROUND: Stuff a non-स्थिरant value that the firmware can
	 * use as a seed क्रम a अक्रमom number generator in MB7 prior to
	 * setting BOOT_ENABLE.	 Fixes problem where the TCP
	 * connections use the same TCP ports after each reboot,
	 * causing some connections to not get re-established.
	 */
	DEBUG(prपूर्णांकk("scsi%d: %s: Start firmware from flash ROM\n",
		     ha->host_no, __func__));

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ग_लिखोl(jअगरfies, &ha->reg->mailbox[7]);
	अगर (is_qla4022(ha) | is_qla4032(ha))
		ग_लिखोl(set_rmask(NVR_WRITE_ENABLE),
		       &ha->reg->u1.isp4022.nvram);

        ग_लिखोl(2, &ha->reg->mailbox[6]);
        पढ़ोl(&ha->reg->mailbox[6]);

	ग_लिखोl(set_rmask(CSR_BOOT_ENABLE), &ha->reg->ctrl_status);
	पढ़ोl(&ha->reg->ctrl_status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	/* Wait क्रम firmware to come UP. */
	DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: Wait up to %d seconds for "
		      "boot firmware to complete...\n",
		      ha->host_no, __func__, FIRMWARE_UP_TOV));
	max_रुको_समय = jअगरfies + (FIRMWARE_UP_TOV * HZ);
	करो अणु
		uपूर्णांक32_t ctrl_status;

		spin_lock_irqsave(&ha->hardware_lock, flags);
		ctrl_status = पढ़ोw(&ha->reg->ctrl_status);
		mbox_status = पढ़ोw(&ha->reg->mailbox[0]);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		अगर (ctrl_status & set_rmask(CSR_SCSI_PROCESSOR_INTR))
			अवरोध;
		अगर (mbox_status == MBOX_STS_COMMAND_COMPLETE)
			अवरोध;

		DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: Waiting for boot "
		    "firmware to complete... ctrl_sts=0x%x, remaining=%ld\n",
		    ha->host_no, __func__, ctrl_status, max_रुको_समय));

		msleep_पूर्णांकerruptible(250);
	पूर्ण जबतक (!समय_after_eq(jअगरfies, max_रुको_समय));

	अगर (mbox_status == MBOX_STS_COMMAND_COMPLETE) अणु
		DEBUG(prपूर्णांकk(KERN_INFO "scsi%ld: %s: Firmware has started\n",
			     ha->host_no, __func__));

		spin_lock_irqsave(&ha->hardware_lock, flags);
		ग_लिखोl(set_rmask(CSR_SCSI_PROCESSOR_INTR),
		       &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		status = QLA_SUCCESS;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "scsi%ld: %s: Boot firmware failed "
		       "-  mbox status 0x%x\n", ha->host_no, __func__,
		       mbox_status);
		status = QLA_ERROR;
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक ql4xxx_lock_drvr_रुको(काष्ठा scsi_qla_host *a)
अणु
#घोषणा QL4_LOCK_DRVR_WAIT	60
#घोषणा QL4_LOCK_DRVR_SLEEP	1

	पूर्णांक drvr_रुको = QL4_LOCK_DRVR_WAIT;
	जबतक (drvr_रुको) अणु
		अगर (ql4xxx_lock_drvr(a) == 0) अणु
			ssleep(QL4_LOCK_DRVR_SLEEP);
			DEBUG2(prपूर्णांकk("scsi%ld: %s: Waiting for "
				      "Global Init Semaphore(%d)...\n",
				      a->host_no,
				      __func__, drvr_रुको));
			drvr_रुको -= QL4_LOCK_DRVR_SLEEP;
		पूर्ण अन्यथा अणु
			DEBUG2(prपूर्णांकk("scsi%ld: %s: Global Init Semaphore "
				      "acquired\n", a->host_no, __func__));
			वापस QLA_SUCCESS;
		पूर्ण
	पूर्ण
	वापस QLA_ERROR;
पूर्ण

/**
 * qla4xxx_start_firmware - starts qla4xxx firmware
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine perक्रमms the necessary steps to start the firmware क्रम
 * the QLA4010 adapter.
 **/
पूर्णांक qla4xxx_start_firmware(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ flags = 0;
	uपूर्णांक32_t mbox_status;
	पूर्णांक status = QLA_ERROR;
	पूर्णांक soft_reset = 1;
	पूर्णांक config_chip = 0;

	अगर (is_qla4022(ha) | is_qla4032(ha))
		ql4xxx_set_mac_number(ha);

	अगर (ql4xxx_lock_drvr_रुको(ha) != QLA_SUCCESS)
		वापस QLA_ERROR;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	DEBUG2(prपूर्णांकk("scsi%ld: %s: port_ctrl	= 0x%08X\n", ha->host_no,
		      __func__, पढ़ोw(isp_port_ctrl(ha))));
	DEBUG(prपूर्णांकk("scsi%ld: %s: port_status = 0x%08X\n", ha->host_no,
		     __func__, पढ़ोw(isp_port_status(ha))));

	/* Is Hardware alपढ़ोy initialized? */
	अगर ((पढ़ोw(isp_port_ctrl(ha)) & 0x8000) != 0) अणु
		DEBUG(prपूर्णांकk("scsi%ld: %s: Hardware has already been "
			     "initialized\n", ha->host_no, __func__));

		/* Receive firmware boot acknowledgement */
		mbox_status = पढ़ोw(&ha->reg->mailbox[0]);

		DEBUG2(prपूर्णांकk("scsi%ld: %s: H/W Config complete - mbox[0]= "
			      "0x%x\n", ha->host_no, __func__, mbox_status));

		/* Is firmware alपढ़ोy booted? */
		अगर (mbox_status == 0) अणु
			/* F/W not running, must be config by net driver */
			config_chip = 1;
			soft_reset = 0;
		पूर्ण अन्यथा अणु
			ग_लिखोl(set_rmask(CSR_SCSI_PROCESSOR_INTR),
			       &ha->reg->ctrl_status);
			पढ़ोl(&ha->reg->ctrl_status);
			ग_लिखोl(set_rmask(CSR_SCSI_COMPLETION_INTR),
			       &ha->reg->ctrl_status);
			पढ़ोl(&ha->reg->ctrl_status);
			spin_unlock_irqrestore(&ha->hardware_lock, flags);
			अगर (qla4xxx_get_firmware_state(ha) == QLA_SUCCESS) अणु
				DEBUG2(prपूर्णांकk("scsi%ld: %s: Get firmware "
					      "state -- state = 0x%x\n",
					      ha->host_no,
					      __func__, ha->firmware_state));
				/* F/W is running */
				अगर (ha->firmware_state &
				    FW_STATE_CONFIG_WAIT) अणु
					DEBUG2(prपूर्णांकk("scsi%ld: %s: Firmware "
						      "in known state -- "
						      "config and "
						      "boot, state = 0x%x\n",
						      ha->host_no, __func__,
						      ha->firmware_state));
					config_chip = 1;
					soft_reset = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				DEBUG2(prपूर्णांकk("scsi%ld: %s: Firmware in "
					      "unknown state -- resetting,"
					      " state = "
					      "0x%x\n", ha->host_no, __func__,
					      ha->firmware_state));
			पूर्ण
			spin_lock_irqsave(&ha->hardware_lock, flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		DEBUG(prपूर्णांकk("scsi%ld: %s: H/W initialization hasn't been "
			     "started - resetting\n", ha->host_no, __func__));
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	DEBUG(prपूर्णांकk("scsi%ld: %s: Flags soft_rest=%d, config= %d\n ",
		     ha->host_no, __func__, soft_reset, config_chip));
	अगर (soft_reset) अणु
		DEBUG(prपूर्णांकk("scsi%ld: %s: Issue Soft Reset\n", ha->host_no,
			     __func__));
		status = qla4xxx_soft_reset(ha);	/* NOTE: acquires drvr
							 * lock again, but ok */
		अगर (status == QLA_ERROR) अणु
			DEBUG(prपूर्णांकk("scsi%d: %s: Soft Reset failed!\n",
				     ha->host_no, __func__));
			ql4xxx_unlock_drvr(ha);
			वापस QLA_ERROR;
		पूर्ण
		config_chip = 1;

		/* Reset clears the semaphore, so acquire again */
		अगर (ql4xxx_lock_drvr_रुको(ha) != QLA_SUCCESS)
			वापस QLA_ERROR;
	पूर्ण

	अगर (config_chip) अणु
		अगर ((status = qla4xxx_config_nvram(ha)) == QLA_SUCCESS)
			status = qla4xxx_start_firmware_from_flash(ha);
	पूर्ण

	ql4xxx_unlock_drvr(ha);
	अगर (status == QLA_SUCCESS) अणु
		अगर (test_and_clear_bit(AF_GET_CRASH_RECORD, &ha->flags))
			qla4xxx_get_crash_record(ha);

		qla4xxx_init_rings(ha);
	पूर्ण अन्यथा अणु
		DEBUG(prपूर्णांकk("scsi%ld: %s: Firmware has NOT started\n",
			     ha->host_no, __func__));
	पूर्ण
	वापस status;
पूर्ण
/**
 * qla4xxx_मुक्त_ddb_index - Free DDBs reserved by firmware
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Since firmware is not running in स्वतःconnect mode the DDB indices should
 * be मुक्तd so that when login happens from user space there are मुक्त DDB
 * indices available.
 **/
व्योम qla4xxx_मुक्त_ddb_index(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक max_ddbs;
	पूर्णांक ret;
	uपूर्णांक32_t idx = 0, next_idx = 0;
	uपूर्णांक32_t state = 0, conn_err = 0;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	क्रम (idx = 0; idx < max_ddbs; idx = next_idx) अणु
		ret = qla4xxx_get_fwddb_entry(ha, idx, शून्य, 0, शून्य,
					      &next_idx, &state, &conn_err,
						शून्य, शून्य);
		अगर (ret == QLA_ERROR) अणु
			next_idx++;
			जारी;
		पूर्ण
		अगर (state == DDB_DS_NO_CONNECTION_ACTIVE ||
		    state == DDB_DS_SESSION_FAILED) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "Freeing DDB index = 0x%x\n", idx));
			ret = qla4xxx_clear_ddb_entry(ha, idx);
			अगर (ret == QLA_ERROR)
				ql4_prपूर्णांकk(KERN_ERR, ha,
					   "Unable to clear DDB index = "
					   "0x%x\n", idx);
		पूर्ण
		अगर (next_idx == 0)
			अवरोध;
	पूर्ण
पूर्ण

/**
 * qla4xxx_initialize_adapter - initiailizes hba
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @is_reset: Is this init path or reset path
 *
 * This routine parक्रमms all of the steps necessary to initialize the adapter.
 *
 **/
पूर्णांक qla4xxx_initialize_adapter(काष्ठा scsi_qla_host *ha, पूर्णांक is_reset)
अणु
	पूर्णांक status = QLA_ERROR;

	ha->eeprom_cmd_data = 0;

	ql4_prपूर्णांकk(KERN_INFO, ha, "Configuring PCI space...\n");
	ha->isp_ops->pci_config(ha);

	ha->isp_ops->disable_पूर्णांकrs(ha);

	/* Initialize the Host adapter request/response queues and firmware */
	अगर (ha->isp_ops->start_firmware(ha) == QLA_ERROR)
		जाओ निकास_init_hba;

	/*
	 * For ISP83XX, mailbox and IOCB पूर्णांकerrupts are enabled separately.
	 * Mailbox पूर्णांकerrupts must be enabled prior to issuing any mailbox
	 * command in order to prevent the possibility of losing पूर्णांकerrupts
	 * जबतक चयनing from polling to पूर्णांकerrupt mode. IOCB पूर्णांकerrupts are
	 * enabled via isp_ops->enable_पूर्णांकrs.
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha))
		qla4_83xx_enable_mbox_पूर्णांकrs(ha);

	अगर (qla4xxx_about_firmware(ha) == QLA_ERROR)
		जाओ निकास_init_hba;

	अगर (ha->isp_ops->get_sys_info(ha) == QLA_ERROR)
		जाओ निकास_init_hba;

	qla4xxx_init_local_data(ha);

	status = qla4xxx_init_firmware(ha);
	अगर (status == QLA_ERROR)
		जाओ निकास_init_hba;

	अगर (is_reset == RESET_ADAPTER)
		qla4xxx_build_ddb_list(ha, is_reset);

	set_bit(AF_ONLINE, &ha->flags);

निकास_init_hba:
	DEBUG2(prपूर्णांकk("scsi%ld: initialize adapter: %s\n", ha->host_no,
	    status == QLA_ERROR ? "FAILED" : "SUCCEEDED"));
	वापस status;
पूर्ण

पूर्णांक qla4xxx_ddb_change(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index,
		       काष्ठा ddb_entry *ddb_entry, uपूर्णांक32_t state)
अणु
	uपूर्णांक32_t old_fw_ddb_device_state;
	पूर्णांक status = QLA_ERROR;

	old_fw_ddb_device_state = ddb_entry->fw_ddb_device_state;
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: DDB - old state = 0x%x, new state = 0x%x for "
			  "index [%d]\n", __func__,
			  ddb_entry->fw_ddb_device_state, state, fw_ddb_index));

	ddb_entry->fw_ddb_device_state = state;

	चयन (old_fw_ddb_device_state) अणु
	हाल DDB_DS_LOGIN_IN_PROCESS:
		चयन (state) अणु
		हाल DDB_DS_SESSION_ACTIVE:
		हाल DDB_DS_DISCOVERY:
			qla4xxx_update_session_conn_param(ha, ddb_entry);
			ddb_entry->unblock_sess(ddb_entry->sess);
			status = QLA_SUCCESS;
			अवरोध;
		हाल DDB_DS_SESSION_FAILED:
		हाल DDB_DS_NO_CONNECTION_ACTIVE:
			iscsi_conn_login_event(ddb_entry->conn,
					       ISCSI_CONN_STATE_FREE);
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DDB_DS_SESSION_ACTIVE:
	हाल DDB_DS_DISCOVERY:
		चयन (state) अणु
		हाल DDB_DS_SESSION_FAILED:
			/*
			 * iscsi_session failure  will cause userspace to
			 * stop the connection which in turn would block the
			 * iscsi_session and start relogin
			 */
			iscsi_session_failure(ddb_entry->sess->dd_data,
					      ISCSI_ERR_CONN_FAILED);
			status = QLA_SUCCESS;
			अवरोध;
		हाल DDB_DS_NO_CONNECTION_ACTIVE:
			clear_bit(fw_ddb_index, ha->ddb_idx_map);
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DDB_DS_SESSION_FAILED:
		चयन (state) अणु
		हाल DDB_DS_SESSION_ACTIVE:
		हाल DDB_DS_DISCOVERY:
			ddb_entry->unblock_sess(ddb_entry->sess);
			qla4xxx_update_session_conn_param(ha, ddb_entry);
			status = QLA_SUCCESS;
			अवरोध;
		हाल DDB_DS_SESSION_FAILED:
			iscsi_session_failure(ddb_entry->sess->dd_data,
					      ISCSI_ERR_CONN_FAILED);
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Unknown Event\n",
				__func__));
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

व्योम qla4xxx_arm_relogin_समयr(काष्ठा ddb_entry *ddb_entry)
अणु
	/*
	 * This triggers a relogin.  After the relogin_समयr
	 * expires, the relogin माला_लो scheduled.  We must रुको a
	 * minimum amount of समय since receiving an 0x8014 AEN
	 * with failed device_state or a logout response beक्रमe
	 * we can issue another relogin.
	 *
	 * Firmware pads this समयout: (समय2रुको +1).
	 * Driver retry to login should be दीर्घer than F/W.
	 * Otherwise F/W will fail
	 * set_ddb() mbx cmd with 0x4005 since it still
	 * counting करोwn its समय2रुको.
	 */
	atomic_set(&ddb_entry->relogin_समयr, 0);
	atomic_set(&ddb_entry->retry_relogin_समयr,
		   ddb_entry->शेष_समय2रुको + 4);

पूर्ण

पूर्णांक qla4xxx_flash_ddb_change(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index,
			     काष्ठा ddb_entry *ddb_entry, uपूर्णांक32_t state)
अणु
	uपूर्णांक32_t old_fw_ddb_device_state;
	पूर्णांक status = QLA_ERROR;

	old_fw_ddb_device_state = ddb_entry->fw_ddb_device_state;
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: DDB - old state = 0x%x, new state = 0x%x for "
			  "index [%d]\n", __func__,
			  ddb_entry->fw_ddb_device_state, state, fw_ddb_index));

	ddb_entry->fw_ddb_device_state = state;

	चयन (old_fw_ddb_device_state) अणु
	हाल DDB_DS_LOGIN_IN_PROCESS:
	हाल DDB_DS_NO_CONNECTION_ACTIVE:
		चयन (state) अणु
		हाल DDB_DS_SESSION_ACTIVE:
			ddb_entry->unblock_sess(ddb_entry->sess);
			qla4xxx_update_session_conn_fwddb_param(ha, ddb_entry);
			status = QLA_SUCCESS;
			अवरोध;
		हाल DDB_DS_SESSION_FAILED:
			iscsi_block_session(ddb_entry->sess);
			अगर (!test_bit(DF_RELOGIN, &ddb_entry->flags))
				qla4xxx_arm_relogin_समयr(ddb_entry);
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DDB_DS_SESSION_ACTIVE:
		चयन (state) अणु
		हाल DDB_DS_SESSION_FAILED:
			iscsi_block_session(ddb_entry->sess);
			अगर (!test_bit(DF_RELOGIN, &ddb_entry->flags))
				qla4xxx_arm_relogin_समयr(ddb_entry);
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DDB_DS_SESSION_FAILED:
		चयन (state) अणु
		हाल DDB_DS_SESSION_ACTIVE:
			ddb_entry->unblock_sess(ddb_entry->sess);
			qla4xxx_update_session_conn_fwddb_param(ha, ddb_entry);
			status = QLA_SUCCESS;
			अवरोध;
		हाल DDB_DS_SESSION_FAILED:
			अगर (!test_bit(DF_RELOGIN, &ddb_entry->flags))
				qla4xxx_arm_relogin_समयr(ddb_entry);
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Unknown Event\n",
				  __func__));
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

/**
 * qla4xxx_process_ddb_changed - process ddb state change
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @fw_ddb_index: Firmware's device database index
 * @state: Device state
 * @conn_err: Unused
 *
 * This routine processes a Decive Database Changed AEN Event.
 **/
पूर्णांक qla4xxx_process_ddb_changed(काष्ठा scsi_qla_host *ha,
				uपूर्णांक32_t fw_ddb_index,
				uपूर्णांक32_t state, uपूर्णांक32_t conn_err)
अणु
	काष्ठा ddb_entry *ddb_entry;

	/* check क्रम out of range index */
	अगर (fw_ddb_index >= MAX_DDB_ENTRIES)
		जाओ निकास_ddb_event;

	/* Get the corresponging ddb entry */
	ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, fw_ddb_index);
	/* Device करोes not currently exist in our database. */
	अगर (ddb_entry == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: No ddb_entry at FW index [%d]\n",
			   __func__, fw_ddb_index);

		अगर (state == DDB_DS_NO_CONNECTION_ACTIVE)
			clear_bit(fw_ddb_index, ha->ddb_idx_map);

		जाओ निकास_ddb_event;
	पूर्ण

	ddb_entry->ddb_change(ha, fw_ddb_index, ddb_entry, state);

निकास_ddb_event:
	वापस QLA_ERROR;
पूर्ण

/**
 * qla4xxx_login_flash_ddb - Login to target (DDB)
 * @cls_session: Poपूर्णांकer to the session to login
 *
 * This routine logins to the target.
 * Issues setddb and conn खोलो mbx
 **/
व्योम qla4xxx_login_flash_ddb(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_dma;
	uपूर्णांक32_t mbx_sts = 0;
	पूर्णांक ret;

	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;
	ha =  ddb_entry->ha;

	अगर (!test_bit(AF_LINK_UP, &ha->flags))
		वापस;

	अगर (ddb_entry->ddb_type != FLASH_DDB) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "Skipping login to non FLASH DB"));
		जाओ निकास_login;
	पूर्ण

	fw_ddb_entry = dma_pool_alloc(ha->fw_ddb_dma_pool, GFP_KERNEL,
				      &fw_ddb_dma);
	अगर (fw_ddb_entry == शून्य) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "Out of memory\n"));
		जाओ निकास_login;
	पूर्ण

	अगर (ddb_entry->fw_ddb_index == INVALID_ENTRY) अणु
		ret = qla4xxx_get_ddb_index(ha, &ddb_entry->fw_ddb_index);
		अगर (ret == QLA_ERROR)
			जाओ निकास_login;

		ha->fw_ddb_index_map[ddb_entry->fw_ddb_index] = ddb_entry;
		ha->tot_ddbs++;
	पूर्ण

	स_नकल(fw_ddb_entry, &ddb_entry->fw_ddb_entry,
	       माप(काष्ठा dev_db_entry));
	ddb_entry->sess->target_id = ddb_entry->fw_ddb_index;

	ret = qla4xxx_set_ddb_entry(ha, ddb_entry->fw_ddb_index,
				    fw_ddb_dma, &mbx_sts);
	अगर (ret == QLA_ERROR) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "Set DDB failed\n"));
		जाओ निकास_login;
	पूर्ण

	ddb_entry->fw_ddb_device_state = DDB_DS_LOGIN_IN_PROCESS;
	ret = qla4xxx_conn_खोलो(ha, ddb_entry->fw_ddb_index);
	अगर (ret == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Login failed: %s\n", __func__,
			   sess->targetname);
		जाओ निकास_login;
	पूर्ण

निकास_login:
	अगर (fw_ddb_entry)
		dma_pool_मुक्त(ha->fw_ddb_dma_pool, fw_ddb_entry, fw_ddb_dma);
पूर्ण

