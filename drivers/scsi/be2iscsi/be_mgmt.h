<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2017 Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * Contact Inक्रमmation:
 * linux-drivers@broadcom.com
 */

#अगर_अघोषित _BEISCSI_MGMT_
#घोषणा _BEISCSI_MGMT_

#समावेश <scsi/scsi_bsg_iscsi.h>
#समावेश "be_iscsi.h"
#समावेश "be_main.h"

#घोषणा IP_ACTION_ADD	0x01
#घोषणा IP_ACTION_DEL	0x02

#घोषणा IP_V6_LEN	16
#घोषणा IP_V4_LEN	4

/* UE Status and Mask रेजिस्टर */
#घोषणा PCICFG_UE_STATUS_LOW            0xA0
#घोषणा PCICFG_UE_STATUS_HIGH           0xA4
#घोषणा PCICFG_UE_STATUS_MASK_LOW       0xA8
#घोषणा PCICFG_UE_STATUS_MASK_HI        0xAC

पूर्णांक mgmt_खोलो_connection(काष्ठा beiscsi_hba *phba,
			 काष्ठा sockaddr *dst_addr,
			 काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep,
			 काष्ठा be_dma_mem *nonemb_cmd);

अचिन्हित पूर्णांक mgmt_venकरोr_specअगरic_fw_cmd(काष्ठा be_ctrl_info *ctrl,
					 काष्ठा beiscsi_hba *phba,
					 काष्ठा bsg_job *job,
					 काष्ठा be_dma_mem *nonemb_cmd);

#घोषणा BE_INVLDT_CMD_TBL_SZ	128
काष्ठा invldt_cmd_tbl अणु
	अचिन्हित लघु icd;
	अचिन्हित लघु cid;
पूर्ण __packed;

काष्ठा invldt_cmds_params_in अणु
	काष्ठा be_cmd_req_hdr hdr;
	अचिन्हित पूर्णांक ref_handle;
	अचिन्हित पूर्णांक icd_count;
	काष्ठा invldt_cmd_tbl table[BE_INVLDT_CMD_TBL_SZ];
	अचिन्हित लघु cleanup_type;
	अचिन्हित लघु unused;
पूर्ण __packed;

काष्ठा invldt_cmds_params_out अणु
	काष्ठा be_cmd_resp_hdr hdr;
	अचिन्हित पूर्णांक ref_handle;
	अचिन्हित पूर्णांक icd_count;
	अचिन्हित पूर्णांक icd_status[BE_INVLDT_CMD_TBL_SZ];
पूर्ण __packed;

जोड़ be_invldt_cmds_params अणु
	काष्ठा invldt_cmds_params_in request;
	काष्ठा invldt_cmds_params_out response;
पूर्ण __packed;

काष्ठा mgmt_hba_attributes अणु
	u8 flashrom_version_string[BEISCSI_VER_STRLEN];
	u8 manufacturer_name[BEISCSI_VER_STRLEN];
	u32 supported_modes;
	u8 seeprom_version_lo;
	u8 seeprom_version_hi;
	u8 rsvd0[2];
	u32 fw_cmd_data_काष्ठा_version;
	u32 ep_fw_data_काष्ठा_version;
	u8 ncsi_version_string[12];
	u32 शेष_extended_समयout;
	u8 controller_model_number[BEISCSI_VER_STRLEN];
	u8 controller_description[64];
	u8 controller_serial_number[BEISCSI_VER_STRLEN];
	u8 ip_version_string[BEISCSI_VER_STRLEN];
	u8 firmware_version_string[BEISCSI_VER_STRLEN];
	u8 bios_version_string[BEISCSI_VER_STRLEN];
	u8 redboot_version_string[BEISCSI_VER_STRLEN];
	u8 driver_version_string[BEISCSI_VER_STRLEN];
	u8 fw_on_flash_version_string[BEISCSI_VER_STRLEN];
	u32 functionalities_supported;
	u16 max_cdblength;
	u8 asic_revision;
	u8 generational_guid[16];
	u8 hba_port_count;
	u16 शेष_link_करोwn_समयout;
	u8 iscsi_ver_min_max;
	u8 multअगरunction_device;
	u8 cache_valid;
	u8 hba_status;
	u8 max_करोमुख्यs_supported;
	u8 phy_port;
	u32 firmware_post_status;
	u32 hba_mtu[8];
	u8 iscsi_features;
	u8 asic_generation;
	u8 future_u8[2];
	u32 future_u32[3];
पूर्ण __packed;

काष्ठा mgmt_controller_attributes अणु
	काष्ठा mgmt_hba_attributes hba_attribs;
	u16 pci_venकरोr_id;
	u16 pci_device_id;
	u16 pci_sub_venकरोr_id;
	u16 pci_sub_प्रणाली_id;
	u8 pci_bus_number;
	u8 pci_device_number;
	u8 pci_function_number;
	u8 पूर्णांकerface_type;
	u64 unique_identअगरier;
	u8 netfilters;
	u8 rsvd0[3];
	u32 future_u32[4];
पूर्ण __packed;

काष्ठा be_mgmt_controller_attributes अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा mgmt_controller_attributes params;
पूर्ण __packed;

काष्ठा be_mgmt_controller_attributes_resp अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा mgmt_controller_attributes params;
पूर्ण __packed;

काष्ठा be_bsg_venकरोr_cmd अणु
	काष्ठा be_cmd_req_hdr hdr;
	अचिन्हित लघु region;
	अचिन्हित लघु offset;
	अचिन्हित लघु sector;
पूर्ण __packed;

/* configuration management */

#घोषणा GET_MGMT_CONTROLLER_WS(phba)    (phba->pmgmt_ws)

#घोषणा ISCSI_GET_PDU_TEMPLATE_ADDRESS(pc, pa) अणु\
	pa->lo = phba->init_mem[ISCSI_MEM_GLOBAL_HEADER].mem_array[0].\
					bus_address.u.a32.address_lo;  \
	pa->hi = phba->init_mem[ISCSI_MEM_GLOBAL_HEADER].mem_array[0].\
					bus_address.u.a32.address_hi;  \
पूर्ण

#घोषणा BEISCSI_WRITE_FLASH 0
#घोषणा BEISCSI_READ_FLASH 1

काष्ठा beiscsi_endpoपूर्णांक अणु
	काष्ठा beiscsi_hba *phba;
	काष्ठा beiscsi_conn *conn;
	काष्ठा iscsi_endpoपूर्णांक *खोलोiscsi_ep;
	अचिन्हित लघु ip_type;
	अक्षर dst6_addr[ISCSI_ADDRESS_BUF_LEN];
	अचिन्हित दीर्घ dst_addr;
	अचिन्हित लघु ep_cid;
	अचिन्हित पूर्णांक fw_handle;
	u16 dst_tcpport;
	u16 cid_vld;
पूर्ण;

पूर्णांक beiscsi_mgmt_invalidate_icds(काष्ठा beiscsi_hba *phba,
				 काष्ठा invldt_cmd_tbl *inv_tbl,
				 अचिन्हित पूर्णांक nents);

पूर्णांक beiscsi_get_initiator_name(काष्ठा beiscsi_hba *phba, अक्षर *name, bool cfg);

पूर्णांक beiscsi_अगर_en_dhcp(काष्ठा beiscsi_hba *phba, u32 ip_type);

पूर्णांक beiscsi_अगर_en_अटल(काष्ठा beiscsi_hba *phba, u32 ip_type,
			 u8 *ip, u8 *subnet);

पूर्णांक beiscsi_अगर_set_gw(काष्ठा beiscsi_hba *phba, u32 ip_type, u8 *gw);

पूर्णांक beiscsi_अगर_get_gw(काष्ठा beiscsi_hba *phba, u32 ip_type,
		      काष्ठा be_cmd_get_def_gateway_resp *resp);

पूर्णांक mgmt_get_nic_conf(काष्ठा beiscsi_hba *phba,
		      काष्ठा be_cmd_get_nic_conf_resp *mac);

पूर्णांक beiscsi_अगर_get_info(काष्ठा beiscsi_hba *phba, पूर्णांक ip_type,
			काष्ठा be_cmd_get_अगर_info_resp **अगर_info);

अचिन्हित पूर्णांक beiscsi_अगर_get_handle(काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_अगर_set_vlan(काष्ठा beiscsi_hba *phba, uपूर्णांक16_t vlan_tag);

अचिन्हित पूर्णांक beiscsi_boot_logout_sess(काष्ठा beiscsi_hba *phba);

अचिन्हित पूर्णांक beiscsi_boot_reखोलो_sess(काष्ठा beiscsi_hba *phba);

अचिन्हित पूर्णांक beiscsi_boot_get_sinfo(काष्ठा beiscsi_hba *phba);

अचिन्हित पूर्णांक __beiscsi_boot_get_shandle(काष्ठा beiscsi_hba *phba, पूर्णांक async);

पूर्णांक beiscsi_boot_get_shandle(काष्ठा beiscsi_hba *phba, अचिन्हित पूर्णांक *s_handle);

sमाप_प्रकार beiscsi_drvr_ver_disp(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf);

sमाप_प्रकार beiscsi_fw_ver_disp(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf);

sमाप_प्रकार beiscsi_active_session_disp(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf);

sमाप_प्रकार beiscsi_adap_family_disp(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf);


sमाप_प्रकार beiscsi_मुक्त_session_disp(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf);

sमाप_प्रकार beiscsi_phys_port_disp(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf);

व्योम beiscsi_offload_cxn_v0(काष्ठा beiscsi_offload_params *params,
			     काष्ठा wrb_handle *pwrb_handle,
			     काष्ठा be_mem_descriptor *mem_descr,
			     काष्ठा hwi_wrb_context *pwrb_context);

व्योम beiscsi_offload_cxn_v2(काष्ठा beiscsi_offload_params *params,
			     काष्ठा wrb_handle *pwrb_handle,
			     काष्ठा hwi_wrb_context *pwrb_context);

अचिन्हित पूर्णांक beiscsi_invalidate_cxn(काष्ठा beiscsi_hba *phba,
				    काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep);

अचिन्हित पूर्णांक beiscsi_upload_cxn(काष्ठा beiscsi_hba *phba,
				काष्ठा beiscsi_endpoपूर्णांक *beiscsi_ep);

पूर्णांक be_cmd_modअगरy_eq_delay(काष्ठा beiscsi_hba *phba,
			 काष्ठा be_set_eqd *, पूर्णांक num);

पूर्णांक beiscsi_logout_fw_sess(काष्ठा beiscsi_hba *phba,
			    uपूर्णांक32_t fw_sess_handle);

#पूर्ण_अगर
