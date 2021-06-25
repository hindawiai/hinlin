<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_CMD_H
#घोषणा _MLXSW_CMD_H

#समावेश "item.h"

#घोषणा MLXSW_CMD_MBOX_SIZE	4096

अटल अंतरभूत अक्षर *mlxsw_cmd_mbox_alloc(व्योम)
अणु
	वापस kzalloc(MLXSW_CMD_MBOX_SIZE, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम mlxsw_cmd_mbox_मुक्त(अक्षर *mbox)
अणु
	kमुक्त(mbox);
पूर्ण

अटल अंतरभूत व्योम mlxsw_cmd_mbox_zero(अक्षर *mbox)
अणु
	स_रखो(mbox, 0, MLXSW_CMD_MBOX_SIZE);
पूर्ण

काष्ठा mlxsw_core;

पूर्णांक mlxsw_cmd_exec(काष्ठा mlxsw_core *mlxsw_core, u16 opcode, u8 opcode_mod,
		   u32 in_mod, bool out_mbox_direct, bool reset_ok,
		   अक्षर *in_mbox, माप_प्रकार in_mbox_size,
		   अक्षर *out_mbox, माप_प्रकार out_mbox_size);

अटल अंतरभूत पूर्णांक mlxsw_cmd_exec_in(काष्ठा mlxsw_core *mlxsw_core, u16 opcode,
				    u8 opcode_mod, u32 in_mod, अक्षर *in_mbox,
				    माप_प्रकार in_mbox_size)
अणु
	वापस mlxsw_cmd_exec(mlxsw_core, opcode, opcode_mod, in_mod, false,
			      false, in_mbox, in_mbox_size, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_exec_out(काष्ठा mlxsw_core *mlxsw_core, u16 opcode,
				     u8 opcode_mod, u32 in_mod,
				     bool out_mbox_direct,
				     अक्षर *out_mbox, माप_प्रकार out_mbox_size)
अणु
	वापस mlxsw_cmd_exec(mlxsw_core, opcode, opcode_mod, in_mod,
			      out_mbox_direct, false, शून्य, 0,
			      out_mbox, out_mbox_size);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_exec_none(काष्ठा mlxsw_core *mlxsw_core, u16 opcode,
				      u8 opcode_mod, u32 in_mod)
अणु
	वापस mlxsw_cmd_exec(mlxsw_core, opcode, opcode_mod, in_mod, false,
			      false, शून्य, 0, शून्य, 0);
पूर्ण

क्रमागत mlxsw_cmd_opcode अणु
	MLXSW_CMD_OPCODE_QUERY_FW		= 0x004,
	MLXSW_CMD_OPCODE_QUERY_BOARDINFO	= 0x006,
	MLXSW_CMD_OPCODE_QUERY_AQ_CAP		= 0x003,
	MLXSW_CMD_OPCODE_MAP_FA			= 0xFFF,
	MLXSW_CMD_OPCODE_UNMAP_FA		= 0xFFE,
	MLXSW_CMD_OPCODE_CONFIG_PROखाता		= 0x100,
	MLXSW_CMD_OPCODE_ACCESS_REG		= 0x040,
	MLXSW_CMD_OPCODE_SW2HW_DQ		= 0x201,
	MLXSW_CMD_OPCODE_HW2SW_DQ		= 0x202,
	MLXSW_CMD_OPCODE_2ERR_DQ		= 0x01E,
	MLXSW_CMD_OPCODE_QUERY_DQ		= 0x022,
	MLXSW_CMD_OPCODE_SW2HW_CQ		= 0x016,
	MLXSW_CMD_OPCODE_HW2SW_CQ		= 0x017,
	MLXSW_CMD_OPCODE_QUERY_CQ		= 0x018,
	MLXSW_CMD_OPCODE_SW2HW_EQ		= 0x013,
	MLXSW_CMD_OPCODE_HW2SW_EQ		= 0x014,
	MLXSW_CMD_OPCODE_QUERY_EQ		= 0x015,
	MLXSW_CMD_OPCODE_QUERY_RESOURCES	= 0x101,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *mlxsw_cmd_opcode_str(u16 opcode)
अणु
	चयन (opcode) अणु
	हाल MLXSW_CMD_OPCODE_QUERY_FW:
		वापस "QUERY_FW";
	हाल MLXSW_CMD_OPCODE_QUERY_BOARDINFO:
		वापस "QUERY_BOARDINFO";
	हाल MLXSW_CMD_OPCODE_QUERY_AQ_CAP:
		वापस "QUERY_AQ_CAP";
	हाल MLXSW_CMD_OPCODE_MAP_FA:
		वापस "MAP_FA";
	हाल MLXSW_CMD_OPCODE_UNMAP_FA:
		वापस "UNMAP_FA";
	हाल MLXSW_CMD_OPCODE_CONFIG_PROखाता:
		वापस "CONFIG_PROFILE";
	हाल MLXSW_CMD_OPCODE_ACCESS_REG:
		वापस "ACCESS_REG";
	हाल MLXSW_CMD_OPCODE_SW2HW_DQ:
		वापस "SW2HW_DQ";
	हाल MLXSW_CMD_OPCODE_HW2SW_DQ:
		वापस "HW2SW_DQ";
	हाल MLXSW_CMD_OPCODE_2ERR_DQ:
		वापस "2ERR_DQ";
	हाल MLXSW_CMD_OPCODE_QUERY_DQ:
		वापस "QUERY_DQ";
	हाल MLXSW_CMD_OPCODE_SW2HW_CQ:
		वापस "SW2HW_CQ";
	हाल MLXSW_CMD_OPCODE_HW2SW_CQ:
		वापस "HW2SW_CQ";
	हाल MLXSW_CMD_OPCODE_QUERY_CQ:
		वापस "QUERY_CQ";
	हाल MLXSW_CMD_OPCODE_SW2HW_EQ:
		वापस "SW2HW_EQ";
	हाल MLXSW_CMD_OPCODE_HW2SW_EQ:
		वापस "HW2SW_EQ";
	हाल MLXSW_CMD_OPCODE_QUERY_EQ:
		वापस "QUERY_EQ";
	हाल MLXSW_CMD_OPCODE_QUERY_RESOURCES:
		वापस "QUERY_RESOURCES";
	शेष:
		वापस "*UNKNOWN*";
	पूर्ण
पूर्ण

क्रमागत mlxsw_cmd_status अणु
	/* Command execution succeeded. */
	MLXSW_CMD_STATUS_OK		= 0x00,
	/* Internal error (e.g. bus error) occurred जबतक processing command. */
	MLXSW_CMD_STATUS_INTERNAL_ERR	= 0x01,
	/* Operation/command not supported or opcode modअगरier not supported. */
	MLXSW_CMD_STATUS_BAD_OP		= 0x02,
	/* Parameter not supported, parameter out of range. */
	MLXSW_CMD_STATUS_BAD_PARAM	= 0x03,
	/* System was not enabled or bad प्रणाली state. */
	MLXSW_CMD_STATUS_BAD_SYS_STATE	= 0x04,
	/* Attempt to access reserved or unallocated resource, or resource in
	 * inappropriate ownership.
	 */
	MLXSW_CMD_STATUS_BAD_RESOURCE	= 0x05,
	/* Requested resource is currently executing a command. */
	MLXSW_CMD_STATUS_RESOURCE_BUSY	= 0x06,
	/* Required capability exceeds device limits. */
	MLXSW_CMD_STATUS_EXCEED_LIM	= 0x08,
	/* Resource is not in the appropriate state or ownership. */
	MLXSW_CMD_STATUS_BAD_RES_STATE	= 0x09,
	/* Index out of range (might be beyond table size or attempt to
	 * access a reserved resource).
	 */
	MLXSW_CMD_STATUS_BAD_INDEX	= 0x0A,
	/* NVMEM checksum/CRC failed. */
	MLXSW_CMD_STATUS_BAD_NVMEM	= 0x0B,
	/* Device is currently running reset */
	MLXSW_CMD_STATUS_RUNNING_RESET	= 0x26,
	/* Bad management packet (silently discarded). */
	MLXSW_CMD_STATUS_BAD_PKT	= 0x30,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *mlxsw_cmd_status_str(u8 status)
अणु
	चयन (status) अणु
	हाल MLXSW_CMD_STATUS_OK:
		वापस "OK";
	हाल MLXSW_CMD_STATUS_INTERNAL_ERR:
		वापस "INTERNAL_ERR";
	हाल MLXSW_CMD_STATUS_BAD_OP:
		वापस "BAD_OP";
	हाल MLXSW_CMD_STATUS_BAD_PARAM:
		वापस "BAD_PARAM";
	हाल MLXSW_CMD_STATUS_BAD_SYS_STATE:
		वापस "BAD_SYS_STATE";
	हाल MLXSW_CMD_STATUS_BAD_RESOURCE:
		वापस "BAD_RESOURCE";
	हाल MLXSW_CMD_STATUS_RESOURCE_BUSY:
		वापस "RESOURCE_BUSY";
	हाल MLXSW_CMD_STATUS_EXCEED_LIM:
		वापस "EXCEED_LIM";
	हाल MLXSW_CMD_STATUS_BAD_RES_STATE:
		वापस "BAD_RES_STATE";
	हाल MLXSW_CMD_STATUS_BAD_INDEX:
		वापस "BAD_INDEX";
	हाल MLXSW_CMD_STATUS_BAD_NVMEM:
		वापस "BAD_NVMEM";
	हाल MLXSW_CMD_STATUS_RUNNING_RESET:
		वापस "RUNNING_RESET";
	हाल MLXSW_CMD_STATUS_BAD_PKT:
		वापस "BAD_PKT";
	शेष:
		वापस "*UNKNOWN*";
	पूर्ण
पूर्ण

/* QUERY_FW - Query Firmware
 * -------------------------
 * OpMod == 0, INMmod == 0
 * -----------------------
 * The QUERY_FW command retrieves inक्रमmation related to firmware, command
 * पूर्णांकerface version and the amount of resources that should be allocated to
 * the firmware.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_query_fw(काष्ठा mlxsw_core *mlxsw_core,
				     अक्षर *out_mbox)
अणु
	वापस mlxsw_cmd_exec_out(mlxsw_core, MLXSW_CMD_OPCODE_QUERY_FW,
				  0, 0, false, out_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* cmd_mbox_query_fw_fw_pages
 * Amount of physical memory to be allocatedक्रम firmware usage in 4KB pages.
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_pages, 0x00, 16, 16);

/* cmd_mbox_query_fw_fw_rev_major
 * Firmware Revision - Major
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_rev_major, 0x00, 0, 16);

/* cmd_mbox_query_fw_fw_rev_subminor
 * Firmware Sub-minor version (Patch level)
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_rev_subminor, 0x04, 16, 16);

/* cmd_mbox_query_fw_fw_rev_minor
 * Firmware Revision - Minor
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_rev_minor, 0x04, 0, 16);

/* cmd_mbox_query_fw_core_clk
 * Internal Clock Frequency (in MHz)
 */
MLXSW_ITEM32(cmd_mbox, query_fw, core_clk, 0x08, 16, 16);

/* cmd_mbox_query_fw_cmd_पूर्णांकerface_rev
 * Command Interface Interpreter Revision ID. This number is bumped up
 * every समय a non-backward-compatible change is करोne क्रम the command
 * पूर्णांकerface. The current cmd_पूर्णांकerface_rev is 1.
 */
MLXSW_ITEM32(cmd_mbox, query_fw, cmd_पूर्णांकerface_rev, 0x08, 0, 16);

/* cmd_mbox_query_fw_dt
 * If set, Debug Trace is supported
 */
MLXSW_ITEM32(cmd_mbox, query_fw, dt, 0x0C, 31, 1);

/* cmd_mbox_query_fw_api_version
 * Indicates the version of the API, to enable software querying
 * क्रम compatibility. The current api_version is 1.
 */
MLXSW_ITEM32(cmd_mbox, query_fw, api_version, 0x0C, 0, 16);

/* cmd_mbox_query_fw_fw_hour
 * Firmware बारtamp - hour
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_hour, 0x10, 24, 8);

/* cmd_mbox_query_fw_fw_minutes
 * Firmware बारtamp - minutes
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_minutes, 0x10, 16, 8);

/* cmd_mbox_query_fw_fw_seconds
 * Firmware बारtamp - seconds
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_seconds, 0x10, 8, 8);

/* cmd_mbox_query_fw_fw_year
 * Firmware बारtamp - year
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_year, 0x14, 16, 16);

/* cmd_mbox_query_fw_fw_month
 * Firmware बारtamp - month
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_month, 0x14, 8, 8);

/* cmd_mbox_query_fw_fw_day
 * Firmware बारtamp - day
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fw_day, 0x14, 0, 8);

/* cmd_mbox_query_fw_clr_पूर्णांक_base_offset
 * Clear Interrupt रेजिस्टर's offset from clr_पूर्णांक_bar रेजिस्टर
 * in PCI address space.
 */
MLXSW_ITEM64(cmd_mbox, query_fw, clr_पूर्णांक_base_offset, 0x20, 0, 64);

/* cmd_mbox_query_fw_clr_पूर्णांक_bar
 * PCI base address रेजिस्टर (BAR) where clr_पूर्णांक रेजिस्टर is located.
 * 00 - BAR 0-1 (64 bit BAR)
 */
MLXSW_ITEM32(cmd_mbox, query_fw, clr_पूर्णांक_bar, 0x28, 30, 2);

/* cmd_mbox_query_fw_error_buf_offset
 * Read Only buffer क्रम पूर्णांकernal error reports of offset
 * from error_buf_bar रेजिस्टर in PCI address space).
 */
MLXSW_ITEM64(cmd_mbox, query_fw, error_buf_offset, 0x30, 0, 64);

/* cmd_mbox_query_fw_error_buf_size
 * Internal error buffer size in DWORDs
 */
MLXSW_ITEM32(cmd_mbox, query_fw, error_buf_size, 0x38, 0, 32);

/* cmd_mbox_query_fw_error_पूर्णांक_bar
 * PCI base address रेजिस्टर (BAR) where error buffer
 * रेजिस्टर is located.
 * 00 - BAR 0-1 (64 bit BAR)
 */
MLXSW_ITEM32(cmd_mbox, query_fw, error_पूर्णांक_bar, 0x3C, 30, 2);

/* cmd_mbox_query_fw_करोorbell_page_offset
 * Offset of the करोorbell page
 */
MLXSW_ITEM64(cmd_mbox, query_fw, करोorbell_page_offset, 0x40, 0, 64);

/* cmd_mbox_query_fw_करोorbell_page_bar
 * PCI base address रेजिस्टर (BAR) of the करोorbell page
 * 00 - BAR 0-1 (64 bit BAR)
 */
MLXSW_ITEM32(cmd_mbox, query_fw, करोorbell_page_bar, 0x48, 30, 2);

/* cmd_mbox_query_fw_मुक्त_running_घड़ी_offset
 * The offset of the मुक्त running घड़ी page
 */
MLXSW_ITEM64(cmd_mbox, query_fw, मुक्त_running_घड़ी_offset, 0x50, 0, 64);

/* cmd_mbox_query_fw_fr_rn_clk_bar
 * PCI base address रेजिस्टर (BAR) of the मुक्त running घड़ी page
 * 0: BAR 0
 * 1: 64 bit BAR
 */
MLXSW_ITEM32(cmd_mbox, query_fw, fr_rn_clk_bar, 0x58, 30, 2);

/* QUERY_BOARDINFO - Query Board Inक्रमmation
 * -----------------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -----------------------------------
 * The QUERY_BOARDINFO command retrieves adapter specअगरic parameters.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_boardinfo(काष्ठा mlxsw_core *mlxsw_core,
				      अक्षर *out_mbox)
अणु
	वापस mlxsw_cmd_exec_out(mlxsw_core, MLXSW_CMD_OPCODE_QUERY_BOARDINFO,
				  0, 0, false, out_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* cmd_mbox_xm_num_local_ports
 * Number of local_ports connected to the xm.
 * Each local port is a 4x
 * Spectrum-2/3: 25G
 * Spectrum-4: 50G
 */
MLXSW_ITEM32(cmd_mbox, boardinfo, xm_num_local_ports, 0x00, 4, 3);

/* cmd_mbox_xm_exists
 * An XM (eXtanded Mezanine, e.g. used क्रम the XLT) is connected on the board.
 */
MLXSW_ITEM32(cmd_mbox, boardinfo, xm_exists, 0x00, 0, 1);

/* cmd_mbox_xm_local_port_entry
 */
MLXSW_ITEM_BIT_ARRAY(cmd_mbox, boardinfo, xm_local_port_entry, 0x04, 4, 8);

/* cmd_mbox_boardinfo_पूर्णांकapin
 * When PCIe पूर्णांकerrupt messages are being used, this value is used क्रम clearing
 * an पूर्णांकerrupt. When using MSI-X, this रेजिस्टर is not used.
 */
MLXSW_ITEM32(cmd_mbox, boardinfo, पूर्णांकapin, 0x10, 24, 8);

/* cmd_mbox_boardinfo_vsd_venकरोr_id
 * PCISIG Venकरोr ID (www.pcisig.com/membership/vid_search) of the venकरोr
 * specअगरying/क्रमmatting the VSD. The vsd_venकरोr_id identअगरies the management
 * करोमुख्य of the VSD/PSID data. Dअगरferent venकरोrs may choose dअगरferent VSD/PSID
 * क्रमmat and encoding as दीर्घ as they use their asचिन्हित vsd_venकरोr_id.
 */
MLXSW_ITEM32(cmd_mbox, boardinfo, vsd_venकरोr_id, 0x1C, 0, 16);

/* cmd_mbox_boardinfo_vsd
 * Venकरोr Specअगरic Data. The VSD string that is burnt to the Flash
 * with the firmware.
 */
#घोषणा MLXSW_CMD_BOARDINFO_VSD_LEN 208
MLXSW_ITEM_BUF(cmd_mbox, boardinfo, vsd, 0x20, MLXSW_CMD_BOARDINFO_VSD_LEN);

/* cmd_mbox_boardinfo_psid
 * The PSID field is a 16-ascii (byte) अक्षरacter string which acts as
 * the board ID. The PSID क्रमmat is used in conjunction with
 * Mellanox vsd_venकरोr_id (15B3h).
 */
#घोषणा MLXSW_CMD_BOARDINFO_PSID_LEN 16
MLXSW_ITEM_BUF(cmd_mbox, boardinfo, psid, 0xF0, MLXSW_CMD_BOARDINFO_PSID_LEN);

/* QUERY_AQ_CAP - Query Asynchronous Queues Capabilities
 * -----------------------------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -----------------------------------
 * The QUERY_AQ_CAP command वापसs the device asynchronous queues
 * capabilities supported.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_query_aq_cap(काष्ठा mlxsw_core *mlxsw_core,
					 अक्षर *out_mbox)
अणु
	वापस mlxsw_cmd_exec_out(mlxsw_core, MLXSW_CMD_OPCODE_QUERY_AQ_CAP,
				  0, 0, false, out_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* cmd_mbox_query_aq_cap_log_max_sdq_sz
 * Log (base 2) of max WQEs allowed on SDQ.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, log_max_sdq_sz, 0x00, 24, 8);

/* cmd_mbox_query_aq_cap_max_num_sdqs
 * Maximum number of SDQs.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, max_num_sdqs, 0x00, 0, 8);

/* cmd_mbox_query_aq_cap_log_max_rdq_sz
 * Log (base 2) of max WQEs allowed on RDQ.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, log_max_rdq_sz, 0x04, 24, 8);

/* cmd_mbox_query_aq_cap_max_num_rdqs
 * Maximum number of RDQs.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, max_num_rdqs, 0x04, 0, 8);

/* cmd_mbox_query_aq_cap_log_max_cq_sz
 * Log (base 2) of the Maximum CQEs allowed in a CQ क्रम CQEv0 and CQEv1.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, log_max_cq_sz, 0x08, 24, 8);

/* cmd_mbox_query_aq_cap_log_max_cqv2_sz
 * Log (base 2) of the Maximum CQEs allowed in a CQ क्रम CQEv2.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, log_max_cqv2_sz, 0x08, 16, 8);

/* cmd_mbox_query_aq_cap_max_num_cqs
 * Maximum number of CQs.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, max_num_cqs, 0x08, 0, 8);

/* cmd_mbox_query_aq_cap_log_max_eq_sz
 * Log (base 2) of max EQEs allowed on EQ.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, log_max_eq_sz, 0x0C, 24, 8);

/* cmd_mbox_query_aq_cap_max_num_eqs
 * Maximum number of EQs.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, max_num_eqs, 0x0C, 0, 8);

/* cmd_mbox_query_aq_cap_max_sg_sq
 * The maximum S/G list elements in an DSQ. DSQ must not contain
 * more S/G entries than indicated here.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, max_sg_sq, 0x10, 8, 8);

/* cmd_mbox_query_aq_cap_
 * The maximum S/G list elements in an DRQ. DRQ must not contain
 * more S/G entries than indicated here.
 */
MLXSW_ITEM32(cmd_mbox, query_aq_cap, max_sg_rq, 0x10, 0, 8);

/* MAP_FA - Map Firmware Area
 * --------------------------
 * OpMod == 0 (N/A), INMmod == Number of VPM entries
 * -------------------------------------------------
 * The MAP_FA command passes physical pages to the चयन. These pages
 * are used to store the device firmware. MAP_FA can be executed multiple
 * बार until all the firmware area is mapped (the size that should be
 * mapped is retrieved through the QUERY_FW command). All required pages
 * must be mapped to finish the initialization phase. Physical memory
 * passed in this command must be pinned.
 */

#घोषणा MLXSW_CMD_MAP_FA_VPM_ENTRIES_MAX 32

अटल अंतरभूत पूर्णांक mlxsw_cmd_map_fa(काष्ठा mlxsw_core *mlxsw_core,
				   अक्षर *in_mbox, u32 vpm_entries_count)
अणु
	वापस mlxsw_cmd_exec_in(mlxsw_core, MLXSW_CMD_OPCODE_MAP_FA,
				 0, vpm_entries_count,
				 in_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* cmd_mbox_map_fa_pa
 * Physical Address.
 */
MLXSW_ITEM64_INDEXED(cmd_mbox, map_fa, pa, 0x00, 12, 52, 0x08, 0x00, true);

/* cmd_mbox_map_fa_log2size
 * Log (base 2) of the size in 4KB pages of the physical and contiguous memory
 * that starts at PA_L/H.
 */
MLXSW_ITEM32_INDEXED(cmd_mbox, map_fa, log2size, 0x00, 0, 5, 0x08, 0x04, false);

/* UNMAP_FA - Unmap Firmware Area
 * ------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -----------------------------------
 * The UNMAP_FA command unload the firmware and unmaps all the
 * firmware area. After this command is completed the device will not access
 * the pages that were mapped to the firmware area. After executing UNMAP_FA
 * command, software reset must be करोne prior to execution of MAP_FW command.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_unmap_fa(काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_cmd_exec_none(mlxsw_core, MLXSW_CMD_OPCODE_UNMAP_FA, 0, 0);
पूर्ण

/* QUERY_RESOURCES - Query chip resources
 * --------------------------------------
 * OpMod == 0 (N/A) , INMmod is index
 * ----------------------------------
 * The QUERY_RESOURCES command retrieves inक्रमmation related to chip resources
 * by resource ID. Every command वापसs 32 entries. INmod is being use as base.
 * क्रम example, index 1 will वापस entries 32-63. When the tables end and there
 * are no more sources in the table, will वापस resource id 0xFFF to indicate
 * it.
 */

#घोषणा MLXSW_CMD_QUERY_RESOURCES_TABLE_END_ID 0xffff
#घोषणा MLXSW_CMD_QUERY_RESOURCES_MAX_QUERIES 100
#घोषणा MLXSW_CMD_QUERY_RESOURCES_PER_QUERY 32

अटल अंतरभूत पूर्णांक mlxsw_cmd_query_resources(काष्ठा mlxsw_core *mlxsw_core,
					    अक्षर *out_mbox, पूर्णांक index)
अणु
	वापस mlxsw_cmd_exec_out(mlxsw_core, MLXSW_CMD_OPCODE_QUERY_RESOURCES,
				  0, index, false, out_mbox,
				  MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* cmd_mbox_query_resource_id
 * The resource id. 0xFFFF indicates table's end.
 */
MLXSW_ITEM32_INDEXED(cmd_mbox, query_resource, id, 0x00, 16, 16, 0x8, 0, false);

/* cmd_mbox_query_resource_data
 * The resource
 */
MLXSW_ITEM64_INDEXED(cmd_mbox, query_resource, data,
		     0x00, 0, 40, 0x8, 0, false);

/* CONFIG_PROखाता (Set) - Configure Switch Profile
 * ------------------------------
 * OpMod == 1 (Set), INMmod == 0 (N/A)
 * -----------------------------------
 * The CONFIG_PROखाता command sets the चयन profile. The command can be
 * executed on the device only once at startup in order to allocate and
 * configure all चयन resources and prepare it क्रम operational mode.
 * It is not possible to change the device profile after the chip is
 * in operational mode.
 * Failure of the CONFIG_PROखाता command leaves the hardware in an indeterminate
 * state thereक्रमe it is required to perक्रमm software reset to the device
 * following an unsuccessful completion of the command. It is required
 * to perक्रमm software reset to the device to change an existing profile.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_config_profile_set(काष्ठा mlxsw_core *mlxsw_core,
					       अक्षर *in_mbox)
अणु
	वापस mlxsw_cmd_exec_in(mlxsw_core, MLXSW_CMD_OPCODE_CONFIG_PROखाता,
				 1, 0, in_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* cmd_mbox_config_profile_set_max_vepa_channels
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_vepa_channels, 0x0C, 0, 1);

/* cmd_mbox_config_profile_set_max_lag
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_lag, 0x0C, 1, 1);

/* cmd_mbox_config_profile_set_max_port_per_lag
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_port_per_lag, 0x0C, 2, 1);

/* cmd_mbox_config_profile_set_max_mid
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_mid, 0x0C, 3, 1);

/* cmd_mbox_config_profile_set_max_pgt
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_pgt, 0x0C, 4, 1);

/* cmd_mbox_config_profile_set_max_प्रणाली_port
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_प्रणाली_port, 0x0C, 5, 1);

/* cmd_mbox_config_profile_set_max_vlan_groups
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_vlan_groups, 0x0C, 6, 1);

/* cmd_mbox_config_profile_set_max_regions
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_regions, 0x0C, 7, 1);

/* cmd_mbox_config_profile_set_flood_mode
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_flood_mode, 0x0C, 8, 1);

/* cmd_mbox_config_profile_set_max_flood_tables
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_flood_tables, 0x0C, 9, 1);

/* cmd_mbox_config_profile_set_max_ib_mc
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_ib_mc, 0x0C, 12, 1);

/* cmd_mbox_config_profile_set_max_pkey
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_max_pkey, 0x0C, 13, 1);

/* cmd_mbox_config_profile_set_adaptive_routing_group_cap
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile,
	     set_adaptive_routing_group_cap, 0x0C, 14, 1);

/* cmd_mbox_config_profile_set_ar_sec
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_ar_sec, 0x0C, 15, 1);

/* cmd_mbox_config_set_kvd_linear_size
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_kvd_linear_size, 0x0C, 24, 1);

/* cmd_mbox_config_set_kvd_hash_single_size
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_kvd_hash_single_size, 0x0C, 25, 1);

/* cmd_mbox_config_set_kvd_hash_द्विगुन_size
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_kvd_hash_द्विगुन_size, 0x0C, 26, 1);

/* cmd_mbox_config_set_cqe_version
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_cqe_version, 0x08, 0, 1);

/* cmd_mbox_config_set_kvh_xlt_cache_mode
 * Capability bit. Setting a bit to 1 configures the profile
 * according to the mailbox contents.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, set_kvh_xlt_cache_mode, 0x08, 3, 1);

/* cmd_mbox_config_profile_max_vepa_channels
 * Maximum number of VEPA channels per port (0 through 16)
 * 0 - multi-channel VEPA is disabled
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_vepa_channels, 0x10, 0, 8);

/* cmd_mbox_config_profile_max_lag
 * Maximum number of LAG IDs requested.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_lag, 0x14, 0, 16);

/* cmd_mbox_config_profile_max_port_per_lag
 * Maximum number of ports per LAG requested.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_port_per_lag, 0x18, 0, 16);

/* cmd_mbox_config_profile_max_mid
 * Maximum Multicast IDs.
 * Multicast IDs are allocated from 0 to max_mid-1
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_mid, 0x1C, 0, 16);

/* cmd_mbox_config_profile_max_pgt
 * Maximum records in the Port Group Table per Switch Partition.
 * Port Group Table indexes are from 0 to max_pgt-1
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_pgt, 0x20, 0, 16);

/* cmd_mbox_config_profile_max_प्रणाली_port
 * The maximum number of प्रणाली ports that can be allocated.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_प्रणाली_port, 0x24, 0, 16);

/* cmd_mbox_config_profile_max_vlan_groups
 * Maximum number VLAN Groups क्रम VLAN binding.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_vlan_groups, 0x28, 0, 12);

/* cmd_mbox_config_profile_max_regions
 * Maximum number of TCAM Regions.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_regions, 0x2C, 0, 16);

/* cmd_mbox_config_profile_max_flood_tables
 * Maximum number of single-entry flooding tables. Dअगरferent flooding tables
 * can be associated with dअगरferent packet types.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_flood_tables, 0x30, 16, 4);

/* cmd_mbox_config_profile_max_vid_flood_tables
 * Maximum number of per-vid flooding tables. Flooding tables are associated
 * to the dअगरferent packet types क्रम the dअगरferent चयन partitions.
 * Table size is 4K entries covering all VID space.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_vid_flood_tables, 0x30, 8, 4);

/* cmd_mbox_config_profile_flood_mode
 * Flooding mode to use.
 * 0-2 - Backward compatible modes क्रम SwitchX devices.
 * 3 - Mixed mode, where:
 * max_flood_tables indicates the number of single-entry tables.
 * max_vid_flood_tables indicates the number of per-VID tables.
 * max_fid_offset_flood_tables indicates the number of FID-offset tables.
 * max_fid_flood_tables indicates the number of per-FID tables.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, flood_mode, 0x30, 0, 2);

/* cmd_mbox_config_profile_max_fid_offset_flood_tables
 * Maximum number of FID-offset flooding tables.
 */
MLXSW_ITEM32(cmd_mbox, config_profile,
	     max_fid_offset_flood_tables, 0x34, 24, 4);

/* cmd_mbox_config_profile_fid_offset_flood_table_size
 * The size (number of entries) of each FID-offset flood table.
 */
MLXSW_ITEM32(cmd_mbox, config_profile,
	     fid_offset_flood_table_size, 0x34, 0, 16);

/* cmd_mbox_config_profile_max_fid_flood_tables
 * Maximum number of per-FID flooding tables.
 *
 * Note: This flooding tables cover special FIDs only (vFIDs), starting at
 * FID value 4K and higher.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_fid_flood_tables, 0x38, 24, 4);

/* cmd_mbox_config_profile_fid_flood_table_size
 * The size (number of entries) of each per-FID table.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, fid_flood_table_size, 0x38, 0, 16);

/* cmd_mbox_config_profile_max_ib_mc
 * Maximum number of multicast FDB records क्रम InfiniBand
 * FDB (in 512 chunks) per InfiniBand चयन partition.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_ib_mc, 0x40, 0, 15);

/* cmd_mbox_config_profile_max_pkey
 * Maximum per port PKEY table size (क्रम PKEY enक्रमcement)
 */
MLXSW_ITEM32(cmd_mbox, config_profile, max_pkey, 0x44, 0, 15);

/* cmd_mbox_config_profile_ar_sec
 * Primary/secondary capability
 * Describes the number of adaptive routing sub-groups
 * 0 - disable primary/secondary (single group)
 * 1 - enable primary/secondary (2 sub-groups)
 * 2 - 3 sub-groups: Not supported in SwitchX, SwitchX-2
 * 3 - 4 sub-groups: Not supported in SwitchX, SwitchX-2
 */
MLXSW_ITEM32(cmd_mbox, config_profile, ar_sec, 0x4C, 24, 2);

/* cmd_mbox_config_profile_adaptive_routing_group_cap
 * Adaptive Routing Group Capability. Indicates the number of AR groups
 * supported. Note that when Primary/secondary is enabled, each
 * primary/secondary couple consumes 2 adaptive routing entries.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, adaptive_routing_group_cap, 0x4C, 0, 16);

/* cmd_mbox_config_profile_arn
 * Adaptive Routing Notअगरication Enable
 * Not supported in SwitchX, SwitchX-2
 */
MLXSW_ITEM32(cmd_mbox, config_profile, arn, 0x50, 31, 1);

/* cmd_mbox_config_profile_kvh_xlt_cache_mode
 * KVH XLT cache mode:
 * 0 - XLT can use all KVH as best-efक्रमt
 * 1 - XLT cache uses 1/2 KVH
 */
MLXSW_ITEM32(cmd_mbox, config_profile, kvh_xlt_cache_mode, 0x50, 8, 4);

/* cmd_mbox_config_kvd_linear_size
 * KVD Linear Size
 * Valid क्रम Spectrum only
 * Allowed values are 128*N where N=0 or higher
 */
MLXSW_ITEM32(cmd_mbox, config_profile, kvd_linear_size, 0x54, 0, 24);

/* cmd_mbox_config_kvd_hash_single_size
 * KVD Hash single-entries size
 * Valid क्रम Spectrum only
 * Allowed values are 128*N where N=0 or higher
 * Must be greater or equal to cap_min_kvd_hash_single_size
 * Must be smaller or equal to cap_kvd_size - kvd_linear_size
 */
MLXSW_ITEM32(cmd_mbox, config_profile, kvd_hash_single_size, 0x58, 0, 24);

/* cmd_mbox_config_kvd_hash_द्विगुन_size
 * KVD Hash द्विगुन-entries size (units of single-size entries)
 * Valid क्रम Spectrum only
 * Allowed values are 128*N where N=0 or higher
 * Must be either 0 or greater or equal to cap_min_kvd_hash_द्विगुन_size
 * Must be smaller or equal to cap_kvd_size - kvd_linear_size
 */
MLXSW_ITEM32(cmd_mbox, config_profile, kvd_hash_द्विगुन_size, 0x5C, 0, 24);

/* cmd_mbox_config_profile_swid_config_mask
 * Modअगरy Switch Partition Configuration mask. When set, the configu-
 * ration value क्रम the Switch Partition are taken from the mailbox.
 * When clear, the current configuration values are used.
 * Bit 0 - set type
 * Bit 1 - properties
 * Other - reserved
 */
MLXSW_ITEM32_INDEXED(cmd_mbox, config_profile, swid_config_mask,
		     0x60, 24, 8, 0x08, 0x00, false);

/* cmd_mbox_config_profile_swid_config_type
 * Switch Partition type.
 * 0000 - disabled (Switch Partition करोes not exist)
 * 0001 - InfiniBand
 * 0010 - Ethernet
 * 1000 - router port (SwitchX-2 only)
 * Other - reserved
 */
MLXSW_ITEM32_INDEXED(cmd_mbox, config_profile, swid_config_type,
		     0x60, 20, 4, 0x08, 0x00, false);

/* cmd_mbox_config_profile_swid_config_properties
 * Switch Partition properties.
 */
MLXSW_ITEM32_INDEXED(cmd_mbox, config_profile, swid_config_properties,
		     0x60, 0, 8, 0x08, 0x00, false);

/* cmd_mbox_config_profile_cqe_version
 * CQE version:
 * 0: CQE version is 0
 * 1: CQE version is either 1 or 2
 * CQE ver 1 or 2 is configured by Completion Queue Context field cqe_ver.
 */
MLXSW_ITEM32(cmd_mbox, config_profile, cqe_version, 0xB0, 0, 8);

/* ACCESS_REG - Access EMAD Supported Register
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -------------------------------------
 * The ACCESS_REG command supports accessing device रेजिस्टरs. This access
 * is मुख्यly used क्रम bootstrapping.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_access_reg(काष्ठा mlxsw_core *mlxsw_core,
				       bool reset_ok,
				       अक्षर *in_mbox, अक्षर *out_mbox)
अणु
	वापस mlxsw_cmd_exec(mlxsw_core, MLXSW_CMD_OPCODE_ACCESS_REG,
			      0, 0, false, reset_ok,
			      in_mbox, MLXSW_CMD_MBOX_SIZE,
			      out_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* SW2HW_DQ - Software to Hardware DQ
 * ----------------------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (receive DQ)
 * INMmod == DQ number
 * ----------------------------------------------
 * The SW2HW_DQ command transitions a descriptor queue from software to
 * hardware ownership. The command enables posting WQEs and ringing DoorBells
 * on the descriptor queue.
 */

अटल अंतरभूत पूर्णांक __mlxsw_cmd_sw2hw_dq(काष्ठा mlxsw_core *mlxsw_core,
				       अक्षर *in_mbox, u32 dq_number,
				       u8 opcode_mod)
अणु
	वापस mlxsw_cmd_exec_in(mlxsw_core, MLXSW_CMD_OPCODE_SW2HW_DQ,
				 opcode_mod, dq_number,
				 in_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

क्रमागत अणु
	MLXSW_CMD_OPCODE_MOD_SDQ = 0,
	MLXSW_CMD_OPCODE_MOD_RDQ = 1,
पूर्ण;

अटल अंतरभूत पूर्णांक mlxsw_cmd_sw2hw_sdq(काष्ठा mlxsw_core *mlxsw_core,
				      अक्षर *in_mbox, u32 dq_number)
अणु
	वापस __mlxsw_cmd_sw2hw_dq(mlxsw_core, in_mbox, dq_number,
				    MLXSW_CMD_OPCODE_MOD_SDQ);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_sw2hw_rdq(काष्ठा mlxsw_core *mlxsw_core,
				      अक्षर *in_mbox, u32 dq_number)
अणु
	वापस __mlxsw_cmd_sw2hw_dq(mlxsw_core, in_mbox, dq_number,
				    MLXSW_CMD_OPCODE_MOD_RDQ);
पूर्ण

/* cmd_mbox_sw2hw_dq_cq
 * Number of the CQ that this Descriptor Queue reports completions to.
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_dq, cq, 0x00, 24, 8);

/* cmd_mbox_sw2hw_dq_sdq_tclass
 * SDQ: CPU Egress TClass
 * RDQ: Reserved
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_dq, sdq_tclass, 0x00, 16, 6);

/* cmd_mbox_sw2hw_dq_log2_dq_sz
 * Log (base 2) of the Descriptor Queue size in 4KB pages.
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_dq, log2_dq_sz, 0x00, 0, 6);

/* cmd_mbox_sw2hw_dq_pa
 * Physical Address.
 */
MLXSW_ITEM64_INDEXED(cmd_mbox, sw2hw_dq, pa, 0x10, 12, 52, 0x08, 0x00, true);

/* HW2SW_DQ - Hardware to Software DQ
 * ----------------------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (receive DQ)
 * INMmod == DQ number
 * ----------------------------------------------
 * The HW2SW_DQ command transitions a descriptor queue from hardware to
 * software ownership. Incoming packets on the DQ are silently discarded,
 * SW should not post descriptors on nonoperational DQs.
 */

अटल अंतरभूत पूर्णांक __mlxsw_cmd_hw2sw_dq(काष्ठा mlxsw_core *mlxsw_core,
				       u32 dq_number, u8 opcode_mod)
अणु
	वापस mlxsw_cmd_exec_none(mlxsw_core, MLXSW_CMD_OPCODE_HW2SW_DQ,
				   opcode_mod, dq_number);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_hw2sw_sdq(काष्ठा mlxsw_core *mlxsw_core,
				      u32 dq_number)
अणु
	वापस __mlxsw_cmd_hw2sw_dq(mlxsw_core, dq_number,
				    MLXSW_CMD_OPCODE_MOD_SDQ);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_hw2sw_rdq(काष्ठा mlxsw_core *mlxsw_core,
				      u32 dq_number)
अणु
	वापस __mlxsw_cmd_hw2sw_dq(mlxsw_core, dq_number,
				    MLXSW_CMD_OPCODE_MOD_RDQ);
पूर्ण

/* 2ERR_DQ - To Error DQ
 * ---------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (receive DQ)
 * INMmod == DQ number
 * ----------------------------------------------
 * The 2ERR_DQ command transitions the DQ पूर्णांकo the error state from the state
 * in which it has been. While the command is executed, some in-process
 * descriptors may complete. Once the DQ transitions पूर्णांकo the error state,
 * अगर there are posted descriptors on the RDQ/SDQ, the hardware ग_लिखोs
 * a completion with error (flushed) क्रम all descriptors posted in the RDQ/SDQ.
 * When the command is completed successfully, the DQ is alपढ़ोy in
 * the error state.
 */

अटल अंतरभूत पूर्णांक __mlxsw_cmd_2err_dq(काष्ठा mlxsw_core *mlxsw_core,
				      u32 dq_number, u8 opcode_mod)
अणु
	वापस mlxsw_cmd_exec_none(mlxsw_core, MLXSW_CMD_OPCODE_2ERR_DQ,
				   opcode_mod, dq_number);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_2err_sdq(काष्ठा mlxsw_core *mlxsw_core,
				     u32 dq_number)
अणु
	वापस __mlxsw_cmd_2err_dq(mlxsw_core, dq_number,
				   MLXSW_CMD_OPCODE_MOD_SDQ);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_2err_rdq(काष्ठा mlxsw_core *mlxsw_core,
				     u32 dq_number)
अणु
	वापस __mlxsw_cmd_2err_dq(mlxsw_core, dq_number,
				   MLXSW_CMD_OPCODE_MOD_RDQ);
पूर्ण

/* QUERY_DQ - Query DQ
 * ---------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (receive DQ)
 * INMmod == DQ number
 * ----------------------------------------------
 * The QUERY_DQ command retrieves a snapshot of DQ parameters from the hardware.
 *
 * Note: Output mailbox has the same क्रमmat as SW2HW_DQ.
 */

अटल अंतरभूत पूर्णांक __mlxsw_cmd_query_dq(काष्ठा mlxsw_core *mlxsw_core,
				       अक्षर *out_mbox, u32 dq_number,
				       u8 opcode_mod)
अणु
	वापस mlxsw_cmd_exec_out(mlxsw_core, MLXSW_CMD_OPCODE_2ERR_DQ,
				  opcode_mod, dq_number, false,
				  out_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_query_sdq(काष्ठा mlxsw_core *mlxsw_core,
				      अक्षर *out_mbox, u32 dq_number)
अणु
	वापस __mlxsw_cmd_query_dq(mlxsw_core, out_mbox, dq_number,
				    MLXSW_CMD_OPCODE_MOD_SDQ);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_cmd_query_rdq(काष्ठा mlxsw_core *mlxsw_core,
				      अक्षर *out_mbox, u32 dq_number)
अणु
	वापस __mlxsw_cmd_query_dq(mlxsw_core, out_mbox, dq_number,
				    MLXSW_CMD_OPCODE_MOD_RDQ);
पूर्ण

/* SW2HW_CQ - Software to Hardware CQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == CQ number
 * -------------------------------------
 * The SW2HW_CQ command transfers ownership of a CQ context entry from software
 * to hardware. The command takes the CQ context entry from the input mailbox
 * and stores it in the CQC in the ownership of the hardware. The command fails
 * अगर the requested CQC entry is alपढ़ोy in the ownership of the hardware.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_sw2hw_cq(काष्ठा mlxsw_core *mlxsw_core,
				     अक्षर *in_mbox, u32 cq_number)
अणु
	वापस mlxsw_cmd_exec_in(mlxsw_core, MLXSW_CMD_OPCODE_SW2HW_CQ,
				 0, cq_number, in_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

क्रमागत mlxsw_cmd_mbox_sw2hw_cq_cqe_ver अणु
	MLXSW_CMD_MBOX_SW2HW_CQ_CQE_VER_1,
	MLXSW_CMD_MBOX_SW2HW_CQ_CQE_VER_2,
पूर्ण;

/* cmd_mbox_sw2hw_cq_cqe_ver
 * CQE Version.
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_cq, cqe_ver, 0x00, 28, 4);

/* cmd_mbox_sw2hw_cq_c_eqn
 * Event Queue this CQ reports completion events to.
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_cq, c_eqn, 0x00, 24, 1);

/* cmd_mbox_sw2hw_cq_st
 * Event delivery state machine
 * 0x0 - FIRED
 * 0x1 - ARMED (Request क्रम Notअगरication)
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_cq, st, 0x00, 8, 1);

/* cmd_mbox_sw2hw_cq_log_cq_size
 * Log (base 2) of the CQ size (in entries).
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_cq, log_cq_size, 0x00, 0, 4);

/* cmd_mbox_sw2hw_cq_producer_counter
 * Producer Counter. The counter is incremented क्रम each CQE that is
 * written by the HW to the CQ.
 * Maपूर्णांकained by HW (valid क्रम the QUERY_CQ command only)
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_cq, producer_counter, 0x04, 0, 16);

/* cmd_mbox_sw2hw_cq_pa
 * Physical Address.
 */
MLXSW_ITEM64_INDEXED(cmd_mbox, sw2hw_cq, pa, 0x10, 11, 53, 0x08, 0x00, true);

/* HW2SW_CQ - Hardware to Software CQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == CQ number
 * -------------------------------------
 * The HW2SW_CQ command transfers ownership of a CQ context entry from hardware
 * to software. The CQC entry is invalidated as a result of this command.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_hw2sw_cq(काष्ठा mlxsw_core *mlxsw_core,
				     u32 cq_number)
अणु
	वापस mlxsw_cmd_exec_none(mlxsw_core, MLXSW_CMD_OPCODE_HW2SW_CQ,
				   0, cq_number);
पूर्ण

/* QUERY_CQ - Query CQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == CQ number
 * -------------------------------------
 * The QUERY_CQ command retrieves a snapshot of the current CQ context entry.
 * The command stores the snapshot in the output mailbox in the software क्रमmat.
 * Note that the CQ context state and values are not affected by the QUERY_CQ
 * command. The QUERY_CQ command is क्रम debug purposes only.
 *
 * Note: Output mailbox has the same क्रमmat as SW2HW_CQ.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_query_cq(काष्ठा mlxsw_core *mlxsw_core,
				     अक्षर *out_mbox, u32 cq_number)
अणु
	वापस mlxsw_cmd_exec_out(mlxsw_core, MLXSW_CMD_OPCODE_QUERY_CQ,
				  0, cq_number, false,
				  out_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* SW2HW_EQ - Software to Hardware EQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == EQ number
 * -------------------------------------
 * The SW2HW_EQ command transfers ownership of an EQ context entry from software
 * to hardware. The command takes the EQ context entry from the input mailbox
 * and stores it in the EQC in the ownership of the hardware. The command fails
 * अगर the requested EQC entry is alपढ़ोy in the ownership of the hardware.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_sw2hw_eq(काष्ठा mlxsw_core *mlxsw_core,
				     अक्षर *in_mbox, u32 eq_number)
अणु
	वापस mlxsw_cmd_exec_in(mlxsw_core, MLXSW_CMD_OPCODE_SW2HW_EQ,
				 0, eq_number, in_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

/* cmd_mbox_sw2hw_eq_पूर्णांक_msix
 * When set, MSI-X cycles will be generated by this EQ.
 * When cleared, an पूर्णांकerrupt will be generated by this EQ.
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_eq, पूर्णांक_msix, 0x00, 24, 1);

/* cmd_mbox_sw2hw_eq_st
 * Event delivery state machine
 * 0x0 - FIRED
 * 0x1 - ARMED (Request क्रम Notअगरication)
 * 0x11 - Always ARMED
 * other - reserved
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_eq, st, 0x00, 8, 2);

/* cmd_mbox_sw2hw_eq_log_eq_size
 * Log (base 2) of the EQ size (in entries).
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_eq, log_eq_size, 0x00, 0, 4);

/* cmd_mbox_sw2hw_eq_producer_counter
 * Producer Counter. The counter is incremented क्रम each EQE that is written
 * by the HW to the EQ.
 * Maपूर्णांकained by HW (valid क्रम the QUERY_EQ command only)
 */
MLXSW_ITEM32(cmd_mbox, sw2hw_eq, producer_counter, 0x04, 0, 16);

/* cmd_mbox_sw2hw_eq_pa
 * Physical Address.
 */
MLXSW_ITEM64_INDEXED(cmd_mbox, sw2hw_eq, pa, 0x10, 11, 53, 0x08, 0x00, true);

/* HW2SW_EQ - Hardware to Software EQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == EQ number
 * -------------------------------------
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_hw2sw_eq(काष्ठा mlxsw_core *mlxsw_core,
				     u32 eq_number)
अणु
	वापस mlxsw_cmd_exec_none(mlxsw_core, MLXSW_CMD_OPCODE_HW2SW_EQ,
				   0, eq_number);
पूर्ण

/* QUERY_EQ - Query EQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == EQ number
 * -------------------------------------
 *
 * Note: Output mailbox has the same क्रमmat as SW2HW_EQ.
 */

अटल अंतरभूत पूर्णांक mlxsw_cmd_query_eq(काष्ठा mlxsw_core *mlxsw_core,
				     अक्षर *out_mbox, u32 eq_number)
अणु
	वापस mlxsw_cmd_exec_out(mlxsw_core, MLXSW_CMD_OPCODE_QUERY_EQ,
				  0, eq_number, false,
				  out_mbox, MLXSW_CMD_MBOX_SIZE);
पूर्ण

#पूर्ण_अगर
