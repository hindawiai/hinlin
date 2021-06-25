<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * pmcraid.h -- PMC Sierra MaxRAID controller driver header file
 *
 * Written By: Anil Ravindranath<anil_ravindranath@pmc-sierra.com>
 *             PMC-Sierra Inc
 *
 * Copyright (C) 2008, 2009 PMC Sierra Inc.
 */

#अगर_अघोषित _PMCRAID_H
#घोषणा _PMCRAID_H

#समावेश <linux/types.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/cdev.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <linux/connector.h>
/*
 * Driver name   : string representing the driver name
 * Device file   : /dev file to be used क्रम management पूर्णांकerfaces
 * Driver version: version string in major_version.minor_version.patch क्रमmat
 * Driver date   : date inक्रमmation in "Mon dd yyyy" क्रमmat
 */
#घोषणा PMCRAID_DRIVER_NAME		"PMC MaxRAID"
#घोषणा PMCRAID_DEVखाता			"pmcsas"
#घोषणा PMCRAID_DRIVER_VERSION		"1.0.3"

#घोषणा PMCRAID_FW_VERSION_1		0x002

/* Maximum number of adapters supported by current version of the driver */
#घोषणा PMCRAID_MAX_ADAPTERS		1024

/* Bit definitions as per firmware, bit position [0][1][2].....[31] */
#घोषणा PMC_BIT8(n)          (1 << (7-n))
#घोषणा PMC_BIT16(n)         (1 << (15-n))
#घोषणा PMC_BIT32(n)         (1 << (31-n))

/* PMC PCI venकरोr ID and device ID values */
#घोषणा PCI_VENDOR_ID_PMC			0x11F8
#घोषणा PCI_DEVICE_ID_PMC_MAXRAID		0x5220

/*
 * MAX_CMD          : maximum commands that can be outstanding with IOA
 * MAX_IO_CMD       : command blocks available क्रम IO commands
 * MAX_HCAM_CMD     : command blocks avaibale क्रम HCAMS
 * MAX_INTERNAL_CMD : command blocks avaible क्रम पूर्णांकernal commands like reset
 */
#घोषणा PMCRAID_MAX_CMD				1024
#घोषणा PMCRAID_MAX_IO_CMD			1020
#घोषणा PMCRAID_MAX_HCAM_CMD			2
#घोषणा PMCRAID_MAX_INTERNAL_CMD		2

/* MAX_IOADLS       : max number of scatter-gather lists supported by IOA
 * IOADLS_INTERNAL  : number of ioadls included as part of IOARCB.
 * IOADLS_EXTERNAL  : number of ioadls allocated बाह्यal to IOARCB
 */
#घोषणा PMCRAID_IOADLS_INTERNAL			 27
#घोषणा PMCRAID_IOADLS_EXTERNAL			 37
#घोषणा PMCRAID_MAX_IOADLS			 PMCRAID_IOADLS_INTERNAL

/* HRRQ_ENTRY_SIZE  : size of hrrq buffer
 * IOARCB_ALIGNMENT : alignment required क्रम IOARCB
 * IOADL_ALIGNMENT  : alignment requirement क्रम IOADLs
 * MSIX_VECTORS     : number of MSIX vectors supported
 */
#घोषणा HRRQ_ENTRY_SIZE                          माप(__le32)
#घोषणा PMCRAID_IOARCB_ALIGNMENT                 32
#घोषणा PMCRAID_IOADL_ALIGNMENT                  16
#घोषणा PMCRAID_IOASA_ALIGNMENT                  4
#घोषणा PMCRAID_NUM_MSIX_VECTORS                 16

/* various other limits */
#घोषणा PMCRAID_VENDOR_ID_LEN			8
#घोषणा PMCRAID_PRODUCT_ID_LEN			16
#घोषणा PMCRAID_SERIAL_NUM_LEN			8
#घोषणा PMCRAID_LUN_LEN				8
#घोषणा PMCRAID_MAX_CDB_LEN			16
#घोषणा PMCRAID_DEVICE_ID_LEN			8
#घोषणा PMCRAID_SENSE_DATA_LEN			256
#घोषणा PMCRAID_ADD_CMD_PARAM_LEN		48

#घोषणा PMCRAID_MAX_BUS_TO_SCAN                  1
#घोषणा PMCRAID_MAX_NUM_TARGETS_PER_BUS          256
#घोषणा PMCRAID_MAX_NUM_LUNS_PER_TARGET          8

/* IOA bus/target/lun number of IOA resources */
#घोषणा PMCRAID_IOA_BUS_ID                       0xfe
#घोषणा PMCRAID_IOA_TARGET_ID                    0xff
#घोषणा PMCRAID_IOA_LUN_ID                       0xff
#घोषणा PMCRAID_VSET_BUS_ID                      0x1
#घोषणा PMCRAID_VSET_LUN_ID                      0x0
#घोषणा PMCRAID_PHYS_BUS_ID                      0x0
#घोषणा PMCRAID_VIRTUAL_ENCL_BUS_ID              0x8
#घोषणा PMCRAID_MAX_VSET_TARGETS                 0x7F
#घोषणा PMCRAID_MAX_VSET_LUNS_PER_TARGET         8

#घोषणा PMCRAID_IOA_MAX_SECTORS                  32767
#घोषणा PMCRAID_VSET_MAX_SECTORS                 512
#घोषणा PMCRAID_MAX_CMD_PER_LUN                  254

/* Number of configuration table entries (resources), includes 1 FP,
 * 1 Enclosure device
 */
#घोषणा PMCRAID_MAX_RESOURCES                    256

/* Adapter Commands used by driver */
#घोषणा PMCRAID_QUERY_RESOURCE_STATE             0xC2
#घोषणा PMCRAID_RESET_DEVICE                     0xC3
/* options to select reset target */
#घोषणा ENABLE_RESET_MODIFIER                    0x80
#घोषणा RESET_DEVICE_LUN                         0x40
#घोषणा RESET_DEVICE_TARGET                      0x20
#घोषणा RESET_DEVICE_BUS                         0x10

#घोषणा PMCRAID_IDENTIFY_HRRQ                    0xC4
#घोषणा PMCRAID_QUERY_IOA_CONFIG                 0xC5
#घोषणा PMCRAID_QUERY_CMD_STATUS		 0xCB
#घोषणा PMCRAID_ABORT_CMD                        0xC7

/* CANCEL ALL command, provides option क्रम setting SYNC_COMPLETE
 * on the target resources क्रम which commands got cancelled
 */
#घोषणा PMCRAID_CANCEL_ALL_REQUESTS		 0xCE
#घोषणा PMCRAID_SYNC_COMPLETE_AFTER_CANCEL       PMC_BIT8(0)

/* HCAM command and types of HCAM supported by IOA */
#घोषणा PMCRAID_HOST_CONTROLLED_ASYNC            0xCF
#घोषणा PMCRAID_HCAM_CODE_CONFIG_CHANGE          0x01
#घोषणा PMCRAID_HCAM_CODE_LOG_DATA               0x02

/* IOA shutकरोwn command and various shutकरोwn types */
#घोषणा PMCRAID_IOA_SHUTDOWN                     0xF7
#घोषणा PMCRAID_SHUTDOWN_NORMAL                  0x00
#घोषणा PMCRAID_SHUTDOWN_PREPARE_FOR_NORMAL      0x40
#घोषणा PMCRAID_SHUTDOWN_NONE                    0x100
#घोषणा PMCRAID_SHUTDOWN_ABBREV                  0x80

/* SET SUPPORTED DEVICES command and the option to select all the
 * devices to be supported
 */
#घोषणा PMCRAID_SET_SUPPORTED_DEVICES            0xFB
#घोषणा ALL_DEVICES_SUPPORTED                    PMC_BIT8(0)

/* This option is used with SCSI WRITE_BUFFER command */
#घोषणा PMCRAID_WR_BUF_DOWNLOAD_AND_SAVE         0x05

/* IOASC Codes used by driver */
#घोषणा PMCRAID_IOASC_SENSE_MASK                 0xFFFFFF00
#घोषणा PMCRAID_IOASC_SENSE_KEY(ioasc)           ((ioasc) >> 24)
#घोषणा PMCRAID_IOASC_SENSE_CODE(ioasc)          (((ioasc) & 0x00ff0000) >> 16)
#घोषणा PMCRAID_IOASC_SENSE_QUAL(ioasc)          (((ioasc) & 0x0000ff00) >> 8)
#घोषणा PMCRAID_IOASC_SENSE_STATUS(ioasc)        ((ioasc) & 0x000000ff)

#घोषणा PMCRAID_IOASC_GOOD_COMPLETION			0x00000000
#घोषणा PMCRAID_IOASC_GC_IOARCB_NOTFOUND		0x005A0000
#घोषणा PMCRAID_IOASC_NR_INIT_CMD_REQUIRED		0x02040200
#घोषणा PMCRAID_IOASC_NR_IOA_RESET_REQUIRED		0x02048000
#घोषणा PMCRAID_IOASC_NR_SYNC_REQUIRED			0x023F0000
#घोषणा PMCRAID_IOASC_ME_READ_ERROR_NO_REALLOC		0x03110C00
#घोषणा PMCRAID_IOASC_HW_CANNOT_COMMUNICATE		0x04050000
#घोषणा PMCRAID_IOASC_HW_DEVICE_TIMEOUT			0x04080100
#घोषणा PMCRAID_IOASC_HW_DEVICE_BUS_STATUS_ERROR	0x04448500
#घोषणा PMCRAID_IOASC_HW_IOA_RESET_REQUIRED		0x04448600
#घोषणा PMCRAID_IOASC_IR_INVALID_RESOURCE_HANDLE        0x05250000
#घोषणा PMCRAID_IOASC_AC_TERMINATED_BY_HOST		0x0B5A0000
#घोषणा PMCRAID_IOASC_UA_BUS_WAS_RESET			0x06290000
#घोषणा PMCRAID_IOASC_TIME_STAMP_OUT_OF_SYNC		0x06908B00
#घोषणा PMCRAID_IOASC_UA_BUS_WAS_RESET_BY_OTHER		0x06298000

/* Driver defined IOASCs */
#घोषणा PMCRAID_IOASC_IOA_WAS_RESET			0x10000001
#घोषणा PMCRAID_IOASC_PCI_ACCESS_ERROR			0x10000002

/* Various समयout values (in milliseconds) used. If any of these are chip
 * specअगरic, move them to pmcraid_chip_details काष्ठाure.
 */
#घोषणा PMCRAID_PCI_DEASSERT_TIMEOUT		2000
#घोषणा PMCRAID_BIST_TIMEOUT			2000
#घोषणा PMCRAID_AENWAIT_TIMEOUT			5000
#घोषणा PMCRAID_TRANSOP_TIMEOUT			60000

#घोषणा PMCRAID_RESET_TIMEOUT			(2 * HZ)
#घोषणा PMCRAID_CHECK_FOR_RESET_TIMEOUT		((HZ / 10))
#घोषणा PMCRAID_VSET_IO_TIMEOUT			(60 * HZ)
#घोषणा PMCRAID_INTERNAL_TIMEOUT		(60 * HZ)
#घोषणा PMCRAID_SHUTDOWN_TIMEOUT		(150 * HZ)
#घोषणा PMCRAID_RESET_BUS_TIMEOUT		(60 * HZ)
#घोषणा PMCRAID_RESET_HOST_TIMEOUT		(150 * HZ)
#घोषणा PMCRAID_REQUEST_SENSE_TIMEOUT		(30 * HZ)
#घोषणा PMCRAID_SET_SUP_DEV_TIMEOUT		(2 * 60 * HZ)

/* काष्ठाure to represent a scatter-gather element (IOADL descriptor) */
काष्ठा pmcraid_ioadl_desc अणु
	__le64 address;
	__le32 data_len;
	__u8  reserved[3];
	__u8  flags;
पूर्ण __attribute__((packed, aligned(PMCRAID_IOADL_ALIGNMENT)));

/* pmcraid_ioadl_desc.flags values */
#घोषणा IOADL_FLAGS_CHAINED      PMC_BIT8(0)
#घोषणा IOADL_FLAGS_LAST_DESC    PMC_BIT8(1)
#घोषणा IOADL_FLAGS_READ_LAST    PMC_BIT8(1)
#घोषणा IOADL_FLAGS_WRITE_LAST   PMC_BIT8(1)


/* additional IOARCB data which can be CDB or additional request parameters
 * or list of IOADLs. Firmware supports max of 512 bytes क्रम IOARCB, hence then
 * number of IOADLs are limted to 27. In हाल they are more than 27, they will
 * be used in chained क्रमm
 */
काष्ठा pmcraid_ioarcb_add_data अणु
	जोड़ अणु
		काष्ठा pmcraid_ioadl_desc ioadl[PMCRAID_IOADLS_INTERNAL];
		__u8 add_cmd_params[PMCRAID_ADD_CMD_PARAM_LEN];
	पूर्ण u;
पूर्ण;

/*
 * IOA Request Control Block
 */
काष्ठा pmcraid_ioarcb अणु
	__le64 ioarcb_bus_addr;
	__le32 resource_handle;
	__le32 response_handle;
	__le64 ioadl_bus_addr;
	__le32 ioadl_length;
	__le32 data_transfer_length;
	__le64 ioasa_bus_addr;
	__le16 ioasa_len;
	__le16 cmd_समयout;
	__le16 add_cmd_param_offset;
	__le16 add_cmd_param_length;
	__le32 reserved1[2];
	__le32 reserved2;
	__u8  request_type;
	__u8  request_flags0;
	__u8  request_flags1;
	__u8  hrrq_id;
	__u8  cdb[PMCRAID_MAX_CDB_LEN];
	काष्ठा pmcraid_ioarcb_add_data add_data;
पूर्ण;

/* well known resource handle values */
#घोषणा PMCRAID_IOA_RES_HANDLE        0xffffffff
#घोषणा PMCRAID_INVALID_RES_HANDLE    0

/* pmcraid_ioarcb.request_type values */
#घोषणा REQ_TYPE_SCSI                 0x00
#घोषणा REQ_TYPE_IOACMD               0x01
#घोषणा REQ_TYPE_HCAM                 0x02

/* pmcraid_ioarcb.flags0 values */
#घोषणा TRANSFER_सूची_WRITE            PMC_BIT8(0)
#घोषणा INHIBIT_UL_CHECK              PMC_BIT8(2)
#घोषणा SYNC_OVERRIDE                 PMC_BIT8(3)
#घोषणा SYNC_COMPLETE                 PMC_BIT8(4)
#घोषणा NO_LINK_DESCS                 PMC_BIT8(5)

/* pmcraid_ioarcb.flags1 values */
#घोषणा DELAY_AFTER_RESET             PMC_BIT8(0)
#घोषणा TASK_TAG_SIMPLE               0x10
#घोषणा TASK_TAG_ORDERED              0x20
#घोषणा TASK_TAG_QUEUE_HEAD           0x30

/* toggle bit offset in response handle */
#घोषणा HRRQ_TOGGLE_BIT               0x01
#घोषणा HRRQ_RESPONSE_BIT             0x02

/* IOA Status Area */
काष्ठा pmcraid_ioasa_vset अणु
	__le32 failing_lba_hi;
	__le32 failing_lba_lo;
	__le32 reserved;
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा pmcraid_ioasa अणु
	__le32 ioasc;
	__le16 वापसed_status_length;
	__le16 available_status_length;
	__le32 residual_data_length;
	__le32 ilid;
	__le32 fd_ioasc;
	__le32 fd_res_address;
	__le32 fd_res_handle;
	__le32 reserved;

	/* resource specअगरic sense inक्रमmation */
	जोड़ अणु
		काष्ठा pmcraid_ioasa_vset vset;
	पूर्ण u;

	/* IOA स्वतःsense data */
	__le16 स्वतः_sense_length;
	__le16 error_data_length;
	__u8  sense_data[PMCRAID_SENSE_DATA_LEN];
पूर्ण __attribute__((packed, aligned(4)));

#घोषणा PMCRAID_DRIVER_ILID           0xffffffff

/* Config Table Entry per Resource */
काष्ठा pmcraid_config_table_entry अणु
	__u8  resource_type;
	__u8  bus_protocol;
	__le16 array_id;
	__u8  common_flags0;
	__u8  common_flags1;
	__u8  unique_flags0;
	__u8  unique_flags1;	/*also used as vset target_id */
	__le32 resource_handle;
	__le32 resource_address;
	__u8  device_id[PMCRAID_DEVICE_ID_LEN];
	__u8  lun[PMCRAID_LUN_LEN];
पूर्ण __attribute__((packed, aligned(4)));

/* extended configuration table sizes are also of 32 bytes in size */
काष्ठा pmcraid_config_table_entry_ext अणु
	काष्ठा pmcraid_config_table_entry cfgte;
पूर्ण;

/* resource types (config_table_entry.resource_type values) */
#घोषणा RES_TYPE_AF_DASD     0x00
#घोषणा RES_TYPE_GSCSI       0x01
#घोषणा RES_TYPE_VSET        0x02
#घोषणा RES_TYPE_IOA_FP      0xFF

#घोषणा RES_IS_IOA(res)      ((res).resource_type == RES_TYPE_IOA_FP)
#घोषणा RES_IS_GSCSI(res)    ((res).resource_type == RES_TYPE_GSCSI)
#घोषणा RES_IS_VSET(res)     ((res).resource_type == RES_TYPE_VSET)
#घोषणा RES_IS_AFDASD(res)   ((res).resource_type == RES_TYPE_AF_DASD)

/* bus_protocol values used by driver */
#घोषणा RES_TYPE_VENCLOSURE  0x8

/* config_table_entry.common_flags0 */
#घोषणा MULTIPATH_RESOURCE   PMC_BIT32(0)

/* unique_flags1 */
#घोषणा IMPORT_MODE_MANUAL   PMC_BIT8(0)

/* well known resource handle values */
#घोषणा RES_HANDLE_IOA       0xFFFFFFFF
#घोषणा RES_HANDLE_NONE      0x00000000

/* well known resource address values */
#घोषणा RES_ADDRESS_IOAFP    0xFEFFFFFF
#घोषणा RES_ADDRESS_INVALID  0xFFFFFFFF

/* BUS/TARGET/LUN values from resource_addrr */
#घोषणा RES_BUS(res_addr)    (le32_to_cpu(res_addr) & 0xFF)
#घोषणा RES_TARGET(res_addr) ((le32_to_cpu(res_addr) >> 16) & 0xFF)
#घोषणा RES_LUN(res_addr)    0x0

/* configuration table काष्ठाure */
काष्ठा pmcraid_config_table अणु
	__le16 num_entries;
	__u8  table_क्रमmat;
	__u8  reserved1;
	__u8  flags;
	__u8  reserved2[11];
	जोड़ अणु
		काष्ठा pmcraid_config_table_entry
				entries[PMCRAID_MAX_RESOURCES];
		काष्ठा pmcraid_config_table_entry_ext
				entries_ext[PMCRAID_MAX_RESOURCES];
	पूर्ण;
पूर्ण __attribute__((packed, aligned(4)));

/* config_table.flags value */
#घोषणा MICROCODE_UPDATE_REQUIRED		PMC_BIT32(0)

/*
 * HCAM क्रमmat
 */
#घोषणा PMCRAID_HOSTRCB_LDNSIZE			4056

/* Error log notअगरication क्रमmat */
काष्ठा pmcraid_hostrcb_error अणु
	__le32 fd_ioasc;
	__le32 fd_ra;
	__le32 fd_rh;
	__le32 prc;
	जोड़ अणु
		__u8 data[PMCRAID_HOSTRCB_LDNSIZE];
	पूर्ण u;
पूर्ण __attribute__ ((packed, aligned(4)));

काष्ठा pmcraid_hcam_hdr अणु
	__u8  op_code;
	__u8  notअगरication_type;
	__u8  notअगरication_lost;
	__u8  flags;
	__u8  overlay_id;
	__u8  reserved1[3];
	__le32 ilid;
	__le32 बारtamp1;
	__le32 बारtamp2;
	__le32 data_len;
पूर्ण __attribute__((packed, aligned(4)));

#घोषणा PMCRAID_AEN_GROUP	0x3

काष्ठा pmcraid_hcam_ccn अणु
	काष्ठा pmcraid_hcam_hdr header;
	काष्ठा pmcraid_config_table_entry cfg_entry;
	काष्ठा pmcraid_config_table_entry cfg_entry_old;
पूर्ण __attribute__((packed, aligned(4)));

#घोषणा PMCRAID_CCN_EXT_SIZE	3944
काष्ठा pmcraid_hcam_ccn_ext अणु
	काष्ठा pmcraid_hcam_hdr header;
	काष्ठा pmcraid_config_table_entry_ext cfg_entry;
	काष्ठा pmcraid_config_table_entry_ext cfg_entry_old;
	__u8   reserved[PMCRAID_CCN_EXT_SIZE];
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा pmcraid_hcam_ldn अणु
	काष्ठा pmcraid_hcam_hdr header;
	काष्ठा pmcraid_hostrcb_error error_log;
पूर्ण __attribute__((packed, aligned(4)));

/* pmcraid_hcam.op_code values */
#घोषणा HOSTRCB_TYPE_CCN			0xE1
#घोषणा HOSTRCB_TYPE_LDN			0xE2

/* pmcraid_hcam.notअगरication_type values */
#घोषणा NOTIFICATION_TYPE_ENTRY_CHANGED		0x0
#घोषणा NOTIFICATION_TYPE_ENTRY_NEW		0x1
#घोषणा NOTIFICATION_TYPE_ENTRY_DELETED		0x2
#घोषणा NOTIFICATION_TYPE_STATE_CHANGE		0x3
#घोषणा NOTIFICATION_TYPE_ENTRY_STATECHANGED	0x4
#घोषणा NOTIFICATION_TYPE_ERROR_LOG		0x10
#घोषणा NOTIFICATION_TYPE_INFORMATION_LOG	0x11

#घोषणा HOSTRCB_NOTIFICATIONS_LOST		PMC_BIT8(0)

/* pmcraid_hcam.flags values */
#घोषणा HOSTRCB_INTERNAL_OP_ERROR		PMC_BIT8(0)
#घोषणा HOSTRCB_ERROR_RESPONSE_SENT		PMC_BIT8(1)

/* pmcraid_hcam.overlay_id values */
#घोषणा HOSTRCB_OVERLAY_ID_08			0x08
#घोषणा HOSTRCB_OVERLAY_ID_09			0x09
#घोषणा HOSTRCB_OVERLAY_ID_11			0x11
#घोषणा HOSTRCB_OVERLAY_ID_12			0x12
#घोषणा HOSTRCB_OVERLAY_ID_13			0x13
#घोषणा HOSTRCB_OVERLAY_ID_14			0x14
#घोषणा HOSTRCB_OVERLAY_ID_16			0x16
#घोषणा HOSTRCB_OVERLAY_ID_17			0x17
#घोषणा HOSTRCB_OVERLAY_ID_20			0x20
#घोषणा HOSTRCB_OVERLAY_ID_FF			0xFF

/* Implementation specअगरic card details */
काष्ठा pmcraid_chip_details अणु
	/* hardware रेजिस्टर offsets */
	अचिन्हित दीर्घ  ioastatus;
	अचिन्हित दीर्घ  ioarrin;
	अचिन्हित दीर्घ  mailbox;
	अचिन्हित दीर्घ  global_पूर्णांकr_mask;
	अचिन्हित दीर्घ  ioa_host_पूर्णांकr;
	अचिन्हित दीर्घ  ioa_host_msix_पूर्णांकr;
	अचिन्हित दीर्घ  ioa_host_पूर्णांकr_clr;
	अचिन्हित दीर्घ  ioa_host_mask;
	अचिन्हित दीर्घ  ioa_host_mask_clr;
	अचिन्हित दीर्घ  host_ioa_पूर्णांकr;
	अचिन्हित दीर्घ  host_ioa_पूर्णांकr_clr;

	/* समयout used during transitional to operational state */
	अचिन्हित दीर्घ transop_समयout;
पूर्ण;

/* IOA to HOST करोorbells (पूर्णांकerrupts) */
#घोषणा INTRS_TRANSITION_TO_OPERATIONAL		PMC_BIT32(0)
#घोषणा INTRS_IOARCB_TRANSFER_FAILED		PMC_BIT32(3)
#घोषणा INTRS_IOA_UNIT_CHECK			PMC_BIT32(4)
#घोषणा INTRS_NO_HRRQ_FOR_CMD_RESPONSE		PMC_BIT32(5)
#घोषणा INTRS_CRITICAL_OP_IN_PROGRESS		PMC_BIT32(6)
#घोषणा INTRS_IO_DEBUG_ACK			PMC_BIT32(7)
#घोषणा INTRS_IOARRIN_LOST			PMC_BIT32(27)
#घोषणा INTRS_SYSTEM_BUS_MMIO_ERROR		PMC_BIT32(28)
#घोषणा INTRS_IOA_PROCESSOR_ERROR		PMC_BIT32(29)
#घोषणा INTRS_HRRQ_VALID			PMC_BIT32(30)
#घोषणा INTRS_OPERATIONAL_STATUS		PMC_BIT32(0)
#घोषणा INTRS_ALLOW_MSIX_VECTOR0		PMC_BIT32(31)

/* Host to IOA Doorbells */
#घोषणा DOORBELL_RUNTIME_RESET			PMC_BIT32(1)
#घोषणा DOORBELL_IOA_RESET_ALERT		PMC_BIT32(7)
#घोषणा DOORBELL_IOA_DEBUG_ALERT		PMC_BIT32(9)
#घोषणा DOORBELL_ENABLE_DESTRUCTIVE_DIAGS	PMC_BIT32(8)
#घोषणा DOORBELL_IOA_START_BIST			PMC_BIT32(23)
#घोषणा DOORBELL_INTR_MODE_MSIX			PMC_BIT32(25)
#घोषणा DOORBELL_INTR_MSIX_CLR			PMC_BIT32(26)
#घोषणा DOORBELL_RESET_IOA			PMC_BIT32(31)

/* Global पूर्णांकerrupt mask रेजिस्टर value */
#घोषणा GLOBAL_INTERRUPT_MASK			0x5ULL

#घोषणा PMCRAID_ERROR_INTERRUPTS	(INTRS_IOARCB_TRANSFER_FAILED | \
					 INTRS_IOA_UNIT_CHECK | \
					 INTRS_NO_HRRQ_FOR_CMD_RESPONSE | \
					 INTRS_IOARRIN_LOST | \
					 INTRS_SYSTEM_BUS_MMIO_ERROR | \
					 INTRS_IOA_PROCESSOR_ERROR)

#घोषणा PMCRAID_PCI_INTERRUPTS		(PMCRAID_ERROR_INTERRUPTS | \
					 INTRS_HRRQ_VALID | \
					 INTRS_TRANSITION_TO_OPERATIONAL |\
					 INTRS_ALLOW_MSIX_VECTOR0)

/* control_block, associated with each of the commands contains IOARCB, IOADLs
 * memory क्रम IOASA. Additional 3 * 16 bytes are allocated in order to support
 * additional request parameters (of max size 48) any command.
 */
काष्ठा pmcraid_control_block अणु
	काष्ठा pmcraid_ioarcb ioarcb;
	काष्ठा pmcraid_ioadl_desc ioadl[PMCRAID_IOADLS_EXTERNAL + 3];
	काष्ठा pmcraid_ioasa ioasa;
पूर्ण __attribute__ ((packed, aligned(PMCRAID_IOARCB_ALIGNMENT)));

/* pmcraid_sglist - Scatter-gather list allocated क्रम passthrough ioctls
 */
काष्ठा pmcraid_sglist अणु
	u32 order;
	u32 num_sg;
	u32 num_dma_sg;
	काष्ठा scatterlist *scatterlist;
पूर्ण;

/* page D0 inquiry data of focal poपूर्णांक resource */
काष्ठा pmcraid_inquiry_data अणु
	__u8	ph_dev_type;
	__u8	page_code;
	__u8	reserved1;
	__u8	add_page_len;
	__u8	length;
	__u8	reserved2;
	__be16	fw_version;
	__u8	reserved3[16];
पूर्ण;

#घोषणा PMCRAID_TIMESTAMP_LEN		12
#घोषणा PMCRAID_REQ_TM_STR_LEN		6
#घोषणा PMCRAID_SCSI_SET_TIMESTAMP	0xA4
#घोषणा PMCRAID_SCSI_SERVICE_ACTION	0x0F

काष्ठा pmcraid_बारtamp_data अणु
	__u8 reserved1[4];
	__u8 बारtamp[PMCRAID_REQ_TM_STR_LEN];		/* current समय value */
	__u8 reserved2[2];
पूर्ण;

/* pmcraid_cmd - LLD representation of SCSI command */
काष्ठा pmcraid_cmd अणु

	/* Ptr and bus address of DMA.able control block क्रम this command */
	काष्ठा pmcraid_control_block *ioa_cb;
	dma_addr_t ioa_cb_bus_addr;
	dma_addr_t dma_handle;

	/* poपूर्णांकer to mid layer काष्ठाure of SCSI commands */
	काष्ठा scsi_cmnd *scsi_cmd;

	काष्ठा list_head मुक्त_list;
	काष्ठा completion रुको_क्रम_completion;
	काष्ठा समयr_list समयr;	/* needed क्रम पूर्णांकernal commands */
	u32 समयout;			/* current समयout value */
	u32 index;			/* index पूर्णांकo the command list */
	u8 completion_req;		/* क्रम handling पूर्णांकernal commands */
	u8 release;			/* क्रम handling completions */

	व्योम (*cmd_करोne) (काष्ठा pmcraid_cmd *);
	काष्ठा pmcraid_instance *drv_inst;

	काष्ठा pmcraid_sglist *sglist; /* used क्रम passthrough IOCTLs */

	/* scratch used */
	जोड़ अणु
		/* during reset sequence */
		अचिन्हित दीर्घ समय_left;
		काष्ठा pmcraid_resource_entry *res;
		पूर्णांक hrrq_index;

		/* used during IO command error handling. Sense buffer
		 * क्रम REQUEST SENSE command अगर firmware is not sending
		 * स्वतः sense data
		 */
		काष्ठा  अणु
			u8 *sense_buffer;
			dma_addr_t sense_buffer_dma;
		पूर्ण;
	पूर्ण;
पूर्ण;

/*
 * Interrupt रेजिस्टरs of IOA
 */
काष्ठा pmcraid_पूर्णांकerrupts अणु
	व्योम __iomem *ioa_host_पूर्णांकerrupt_reg;
	व्योम __iomem *ioa_host_msix_पूर्णांकerrupt_reg;
	व्योम __iomem *ioa_host_पूर्णांकerrupt_clr_reg;
	व्योम __iomem *ioa_host_पूर्णांकerrupt_mask_reg;
	व्योम __iomem *ioa_host_पूर्णांकerrupt_mask_clr_reg;
	व्योम __iomem *global_पूर्णांकerrupt_mask_reg;
	व्योम __iomem *host_ioa_पूर्णांकerrupt_reg;
	व्योम __iomem *host_ioa_पूर्णांकerrupt_clr_reg;
पूर्ण;

/* ISR parameters LLD allocates (one क्रम each MSI-X अगर enabled) vectors */
काष्ठा pmcraid_isr_param अणु
	काष्ठा pmcraid_instance *drv_inst;
	u8 hrrq_id;			/* hrrq entry index */
पूर्ण;


/* AEN message header sent as part of event data to applications */
काष्ठा pmcraid_aen_msg अणु
	u32 hostno;
	u32 length;
	u8  reserved[8];
	u8  data[];
पूर्ण;

/* Controller state event message type */
काष्ठा pmcraid_state_msg अणु
	काष्ठा pmcraid_aen_msg msg;
	u32 ioa_state;
पूर्ण;

#घोषणा PMC_DEVICE_EVENT_RESET_START		0x11000000
#घोषणा PMC_DEVICE_EVENT_RESET_SUCCESS		0x11000001
#घोषणा PMC_DEVICE_EVENT_RESET_FAILED		0x11000002
#घोषणा PMC_DEVICE_EVENT_SHUTDOWN_START		0x11000003
#घोषणा PMC_DEVICE_EVENT_SHUTDOWN_SUCCESS	0x11000004
#घोषणा PMC_DEVICE_EVENT_SHUTDOWN_FAILED	0x11000005

काष्ठा pmcraid_hostrcb अणु
	काष्ठा pmcraid_instance *drv_inst;
	काष्ठा pmcraid_aen_msg *msg;
	काष्ठा pmcraid_hcam_hdr *hcam;	/* poपूर्णांकer to hcam buffer */
	काष्ठा pmcraid_cmd  *cmd;       /* poपूर्णांकer to command block used */
	dma_addr_t baddr;		/* प्रणाली address of hcam buffer */
	atomic_t ignore;		/* process HCAM response ? */
पूर्ण;

#घोषणा PMCRAID_AEN_HDR_SIZE	माप(काष्ठा pmcraid_aen_msg)



/*
 * Per adapter काष्ठाure मुख्यtained by LLD
 */
काष्ठा pmcraid_instance अणु
	/* Array of allowed-to-be-exposed resources, initialized from
	 * Configutation Table, later updated with CCNs
	 */
	काष्ठा pmcraid_resource_entry *res_entries;

	काष्ठा list_head मुक्त_res_q;	/* res_entries lists क्रम easy lookup */
	काष्ठा list_head used_res_q;	/* List of to be exposed resources */
	spinlock_t resource_lock;	/* spinlock to protect resource list */

	व्योम __iomem *mapped_dma_addr;
	व्योम __iomem *ioa_status;	/* Iomapped IOA status रेजिस्टर */
	व्योम __iomem *mailbox;		/* Iomapped mailbox रेजिस्टर */
	व्योम __iomem *ioarrin;		/* IOmapped IOARR IN रेजिस्टर */

	काष्ठा pmcraid_पूर्णांकerrupts पूर्णांक_regs;
	काष्ठा pmcraid_chip_details *chip_cfg;

	/* HostRCBs needed क्रम HCAM */
	काष्ठा pmcraid_hostrcb ldn;
	काष्ठा pmcraid_hostrcb ccn;
	काष्ठा pmcraid_state_msg scn;	/* controller state change msg */


	/* Bus address of start of HRRQ */
	dma_addr_t hrrq_start_bus_addr[PMCRAID_NUM_MSIX_VECTORS];

	/* Poपूर्णांकer to 1st entry of HRRQ */
	__le32 *hrrq_start[PMCRAID_NUM_MSIX_VECTORS];

	/* Poपूर्णांकer to last entry of HRRQ */
	__le32 *hrrq_end[PMCRAID_NUM_MSIX_VECTORS];

	/* Poपूर्णांकer to current poपूर्णांकer of hrrq */
	__le32 *hrrq_curr[PMCRAID_NUM_MSIX_VECTORS];

	/* Lock क्रम HRRQ access */
	spinlock_t hrrq_lock[PMCRAID_NUM_MSIX_VECTORS];

	काष्ठा pmcraid_inquiry_data *inq_data;
	dma_addr_t  inq_data_baddr;

	काष्ठा pmcraid_बारtamp_data *बारtamp_data;
	dma_addr_t  बारtamp_data_baddr;

	/* size of configuration table entry, varies based on the firmware */
	u32	config_table_entry_size;

	/* Expected toggle bit at host */
	u8 host_toggle_bit[PMCRAID_NUM_MSIX_VECTORS];


	/* Wait Q क्रम  thपढ़ोs to रुको क्रम Reset IOA completion */
	रुको_queue_head_t reset_रुको_q;
	काष्ठा pmcraid_cmd *reset_cmd;

	/* काष्ठाures क्रम supporting SIGIO based AEN. */
	काष्ठा fasync_काष्ठा *aen_queue;
	काष्ठा mutex aen_queue_lock;	/* lock क्रम aen subscribers list */
	काष्ठा cdev cdev;

	काष्ठा Scsi_Host *host;	/* mid layer पूर्णांकerface काष्ठाure handle */
	काष्ठा pci_dev *pdev;	/* PCI device काष्ठाure handle */

	/* No of Reset IOA retries . IOA marked dead अगर threshold exceeds */
	u8 ioa_reset_attempts;
#घोषणा PMCRAID_RESET_ATTEMPTS 3

	u8  current_log_level;	/* शेष level क्रम logging IOASC errors */

	u8  num_hrrq;		/* Number of पूर्णांकerrupt vectors allocated */
	u8  पूर्णांकerrupt_mode;	/* current पूर्णांकerrupt mode legacy or msix */
	dev_t dev;		/* Major-Minor numbers क्रम Char device */

	/* Used as ISR handler argument */
	काष्ठा pmcraid_isr_param hrrq_vector[PMCRAID_NUM_MSIX_VECTORS];

	/* Message id as filled in last fired IOARCB, used to identअगरy HRRQ */
	atomic_t last_message_id;

	/* configuration table */
	काष्ठा pmcraid_config_table *cfg_table;
	dma_addr_t cfg_table_bus_addr;

	/* काष्ठाures related to command blocks */
	काष्ठा kmem_cache *cmd_cachep;		/* cache क्रम cmd blocks */
	काष्ठा dma_pool *control_pool;		/* pool क्रम control blocks */
	अक्षर   cmd_pool_name[64];		/* name of cmd cache */
	अक्षर   ctl_pool_name[64];		/* name of control cache */

	काष्ठा pmcraid_cmd *cmd_list[PMCRAID_MAX_CMD];

	काष्ठा list_head मुक्त_cmd_pool;
	काष्ठा list_head pending_cmd_pool;
	spinlock_t मुक्त_pool_lock;		/* मुक्त pool lock */
	spinlock_t pending_pool_lock;		/* pending pool lock */

	/* Tasklet to handle deferred processing */
	काष्ठा tasklet_काष्ठा isr_tasklet[PMCRAID_NUM_MSIX_VECTORS];

	/* Work-queue (Shared) क्रम deferred reset processing */
	काष्ठा work_काष्ठा worker_q;

	/* No of IO commands pending with FW */
	atomic_t outstanding_cmds;

	/* should add/delete resources to mid-layer now ?*/
	atomic_t expose_resources;



	u32 ioa_state:4;	/* For IOA Reset sequence FSM */
#घोषणा IOA_STATE_OPERATIONAL       0x0
#घोषणा IOA_STATE_UNKNOWN           0x1
#घोषणा IOA_STATE_DEAD              0x2
#घोषणा IOA_STATE_IN_SOFT_RESET     0x3
#घोषणा IOA_STATE_IN_HARD_RESET     0x4
#घोषणा IOA_STATE_IN_RESET_ALERT    0x5
#घोषणा IOA_STATE_IN_BRINGDOWN      0x6
#घोषणा IOA_STATE_IN_BRINGUP        0x7

	u32 ioa_reset_in_progress:1; /* true अगर IOA reset is in progress */
	u32 ioa_hard_reset:1;	/* TRUE अगर Hard Reset is needed */
	u32 ioa_unit_check:1;	/* Indicates Unit Check condition */
	u32 ioa_bringकरोwn:1;	/* whether IOA needs to be brought करोwn */
	u32 क्रमce_ioa_reset:1;  /* क्रमce adapter reset ? */
	u32 reinit_cfg_table:1; /* reinit config table due to lost CCN */
	u32 ioa_shutकरोwn_type:2;/* shutकरोwn type used during reset */
#घोषणा SHUTDOWN_NONE               0x0
#घोषणा SHUTDOWN_NORMAL             0x1
#घोषणा SHUTDOWN_ABBREV             0x2
	u32 बारtamp_error:1; /* indicate set बारtamp क्रम out of sync */

पूर्ण;

/* LLD मुख्यtained resource entry काष्ठाure */
काष्ठा pmcraid_resource_entry अणु
	काष्ठा list_head queue;	/* link to "to be exposed" resources */
	जोड़ अणु
		काष्ठा pmcraid_config_table_entry cfg_entry;
		काष्ठा pmcraid_config_table_entry_ext cfg_entry_ext;
	पूर्ण;
	काष्ठा scsi_device *scsi_dev;	/* Link scsi_device काष्ठाure */
	atomic_t पढ़ो_failures;		/* count of failed READ commands */
	atomic_t ग_लिखो_failures;	/* count of failed WRITE commands */

	/* To indicate add/delete/modअगरy during CCN */
	u8 change_detected;
#घोषणा RES_CHANGE_ADD          0x1	/* add this to mid-layer */
#घोषणा RES_CHANGE_DEL          0x2	/* हटाओ this from mid-layer */

	u8 reset_progress;      /* Device is resetting */

	/*
	 * When IOA asks क्रम sync (i.e. IOASC = Not Ready, Sync Required), this
	 * flag will be set, mid layer will be asked to retry. In the next
	 * attempt, this flag will be checked in queuecommand() to set
	 * SYNC_COMPLETE flag in IOARCB (flag_0).
	 */
	u8 sync_reqd;

	/* target indicates the mapped target_id asचिन्हित to this resource अगर
	 * this is VSET resource. For non-VSET resources this will be un-used
	 * or zero
	 */
	u8 target;
पूर्ण;

/* Data काष्ठाures used in IOASC error code logging */
काष्ठा pmcraid_ioasc_error अणु
	u32 ioasc_code;		/* IOASC code */
	u8 log_level;		/* शेष log level assignment. */
	अक्षर *error_string;
पूर्ण;

/* Initial log_level assignments क्रम various IOASCs */
#घोषणा IOASC_LOG_LEVEL_NONE	    0x0 /* no logging */
#घोषणा IOASC_LOG_LEVEL_MUST        0x1	/* must log: all high-severity errors */
#घोषणा IOASC_LOG_LEVEL_HARD        0x2	/* optional ै  low severity errors */

/* Error inक्रमmation मुख्यtained by LLD. LLD initializes the pmcraid_error_table
 * अटलally.
 */
अटल काष्ठा pmcraid_ioasc_error pmcraid_ioasc_error_table[] = अणु
	अणु0x01180600, IOASC_LOG_LEVEL_HARD,
	 "Recovered Error, soft media error, sector reassignment suggested"पूर्ण,
	अणु0x015D0000, IOASC_LOG_LEVEL_HARD,
	 "Recovered Error, failure prediction threshold exceeded"पूर्ण,
	अणु0x015D9200, IOASC_LOG_LEVEL_HARD,
	 "Recovered Error, soft Cache Card Battery error threshold"पूर्ण,
	अणु0x015D9200, IOASC_LOG_LEVEL_HARD,
	 "Recovered Error, soft Cache Card Battery error threshold"पूर्ण,
	अणु0x02048000, IOASC_LOG_LEVEL_HARD,
	 "Not Ready, IOA Reset Required"पूर्ण,
	अणु0x02408500, IOASC_LOG_LEVEL_HARD,
	 "Not Ready, IOA microcode download required"पूर्ण,
	अणु0x03110B00, IOASC_LOG_LEVEL_HARD,
	 "Medium Error, data unreadable, reassignment suggested"पूर्ण,
	अणु0x03110C00, IOASC_LOG_LEVEL_MUST,
	 "Medium Error, data unreadable do not reassign"पूर्ण,
	अणु0x03310000, IOASC_LOG_LEVEL_HARD,
	 "Medium Error, media corrupted"पूर्ण,
	अणु0x04050000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, IOA can't communicate with device"पूर्ण,
	अणु0x04080000, IOASC_LOG_LEVEL_MUST,
	 "Hardware Error, device bus error"पूर्ण,
	अणु0x04088000, IOASC_LOG_LEVEL_MUST,
	 "Hardware Error, device bus is not functioning"पूर्ण,
	अणु0x04118000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, IOA reserved area data check"पूर्ण,
	अणु0x04118100, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, IOA reserved area invalid data pattern"पूर्ण,
	अणु0x04118200, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, IOA reserved area LRC error"पूर्ण,
	अणु0x04320000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, reassignment space exhausted"पूर्ण,
	अणु0x04330000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, data transfer underlength error"पूर्ण,
	अणु0x04330000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, data transfer overlength error"पूर्ण,
	अणु0x04418000, IOASC_LOG_LEVEL_MUST,
	 "Hardware Error, PCI bus error"पूर्ण,
	अणु0x04440000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, device error"पूर्ण,
	अणु0x04448200, IOASC_LOG_LEVEL_MUST,
	 "Hardware Error, IOA error"पूर्ण,
	अणु0x04448300, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, undefined device response"पूर्ण,
	अणु0x04448400, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, IOA microcode error"पूर्ण,
	अणु0x04448600, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, IOA reset required"पूर्ण,
	अणु0x04449200, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, hard Cache Fearuee Card Battery error"पूर्ण,
	अणु0x0444A000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, failed device altered"पूर्ण,
	अणु0x0444A200, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, data check after reassignment"पूर्ण,
	अणु0x0444A300, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, LRC error after reassignment"पूर्ण,
	अणु0x044A0000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, device bus error (msg/cmd phase)"पूर्ण,
	अणु0x04670400, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, new device can't be used"पूर्ण,
	अणु0x04678000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, invalid multiadapter configuration"पूर्ण,
	अणु0x04678100, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, incorrect connection between enclosures"पूर्ण,
	अणु0x04678200, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, connections exceed IOA design limits"पूर्ण,
	अणु0x04678300, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, incorrect multipath connection"पूर्ण,
	अणु0x04679000, IOASC_LOG_LEVEL_HARD,
	 "Hardware Error, command to LUN failed"पूर्ण,
	अणु0x064C8000, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, cache exists for missing/failed device"पूर्ण,
	अणु0x06670100, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, incompatible exposed mode device"पूर्ण,
	अणु0x06670600, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, attachment of logical unit failed"पूर्ण,
	अणु0x06678000, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, cables exceed connective design limit"पूर्ण,
	अणु0x06678300, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, incomplete multipath connection between" \
	 "IOA and enclosure"पूर्ण,
	अणु0x06678400, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, incomplete multipath connection between" \
	 "device and enclosure"पूर्ण,
	अणु0x06678500, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, incomplete multipath connection between" \
	 "IOA and remote IOA"पूर्ण,
	अणु0x06678600, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, missing remote IOA"पूर्ण,
	अणु0x06679100, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, enclosure doesn't support required multipath" \
	 "function"पूर्ण,
	अणु0x06698200, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, corrupt array parity detected on device"पूर्ण,
	अणु0x066B0200, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, array exposed"पूर्ण,
	अणु0x066B8200, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, exposed array is still protected"पूर्ण,
	अणु0x066B9200, IOASC_LOG_LEVEL_HARD,
	 "Unit Attention, Multipath redundancy level got worse"पूर्ण,
	अणु0x07270000, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, device is read/write protected by IOA"पूर्ण,
	अणु0x07278000, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, IOA doesn't support device attribute"पूर्ण,
	अणु0x07278100, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, NVRAM mirroring prohibited"पूर्ण,
	अणु0x07278400, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, array is short 2 or more devices"पूर्ण,
	अणु0x07278600, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, exposed array is short a required device"पूर्ण,
	अणु0x07278700, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, array members not at required addresses"पूर्ण,
	अणु0x07278800, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, exposed mode device resource address conflict"पूर्ण,
	अणु0x07278900, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, incorrect resource address of exposed mode device"पूर्ण,
	अणु0x07278A00, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, Array is missing a device and parity is out of sync"पूर्ण,
	अणु0x07278B00, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, maximum number of arrays already exist"पूर्ण,
	अणु0x07278C00, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, cannot locate cache data for device"पूर्ण,
	अणु0x07278D00, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, cache data exits for a changed device"पूर्ण,
	अणु0x07279100, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, detection of a device requiring format"पूर्ण,
	अणु0x07279200, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, IOA exceeds maximum number of devices"पूर्ण,
	अणु0x07279600, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, missing array, volume set is not functional"पूर्ण,
	अणु0x07279700, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, single device for a volume set"पूर्ण,
	अणु0x07279800, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, missing multiple devices for a volume set"पूर्ण,
	अणु0x07279900, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, maximum number of volument sets already exists"पूर्ण,
	अणु0x07279A00, IOASC_LOG_LEVEL_HARD,
	 "Data Protect, other volume set problem"पूर्ण,
पूर्ण;

/* macros to help in debugging */
#घोषणा pmcraid_err(...)  \
	prपूर्णांकk(KERN_ERR "MaxRAID: "__VA_ARGS__)

#घोषणा pmcraid_info(...) \
	अगर (pmcraid_debug_log) \
		prपूर्णांकk(KERN_INFO "MaxRAID: "__VA_ARGS__)

/* check अगर given command is a SCSI READ or SCSI WRITE command */
#घोषणा SCSI_READ_CMD           0x1	/* any of SCSI READ commands */
#घोषणा SCSI_WRITE_CMD          0x2	/* any of SCSI WRITE commands */
#घोषणा SCSI_CMD_TYPE(opcode) \
(अणु  u8 op = opcode; u8 __type = 0;\
	अगर (op == READ_6 || op == READ_10 || op == READ_12 || op == READ_16)\
		__type = SCSI_READ_CMD;\
	अन्यथा अगर (op == WRITE_6 || op == WRITE_10 || op == WRITE_12 || \
		 op == WRITE_16)\
		__type = SCSI_WRITE_CMD;\
	__type;\
पूर्ण)

#घोषणा IS_SCSI_READ_WRITE(opcode) \
(अणु	u8 __type = SCSI_CMD_TYPE(opcode); \
	(__type == SCSI_READ_CMD || __type == SCSI_WRITE_CMD) ? 1 : 0;\
पूर्ण)


/*
 * pmcraid_ioctl_header - definition of header काष्ठाure that precedes all the
 * buffers given as ioctl arguments.
 *
 * .signature           : always ASCII string, "PMCRAID"
 * .reserved            : not used
 * .buffer_length       : length of the buffer following the header
 */
काष्ठा pmcraid_ioctl_header अणु
	u8  signature[8];
	u32 reserved;
	u32 buffer_length;
पूर्ण;

#घोषणा PMCRAID_IOCTL_SIGNATURE      "PMCRAID"

/*
 * pmcraid_passthrough_ioctl_buffer - काष्ठाure given as argument to
 * passthrough(or firmware handled) IOCTL commands. Note that ioarcb requires
 * 32-byte alignment so, it is necessary to pack this काष्ठाure to aव्योम any
 * holes between ioctl_header and passthrough buffer
 *
 * .ioactl_header : ioctl header
 * .ioarcb        : filled-up ioarcb buffer, driver always पढ़ोs this buffer
 * .ioasa         : buffer क्रम ioasa, driver fills this with IOASA from firmware
 * .request_buffer: The I/O buffer (flat), driver पढ़ोs/ग_लिखोs to this based on
 *                  the transfer directions passed in ioarcb.flags0. Contents
 *                  of this buffer are valid only when ioarcb.data_transfer_len
 *                  is not zero.
 */
काष्ठा pmcraid_passthrough_ioctl_buffer अणु
	काष्ठा pmcraid_ioctl_header ioctl_header;
	काष्ठा pmcraid_ioarcb ioarcb;
	काष्ठा pmcraid_ioasa  ioasa;
	u8  request_buffer[];
पूर्ण __attribute__ ((packed, aligned(PMCRAID_IOARCB_ALIGNMENT)));

/*
 * keys to dअगरferentiate between driver handled IOCTLs and passthrough
 * IOCTLs passed to IOA. driver determines the ioctl type using macro
 * _IOC_TYPE
 */
#घोषणा PMCRAID_DRIVER_IOCTL         'D'
#घोषणा PMCRAID_PASSTHROUGH_IOCTL    'F'

#घोषणा DRV_IOCTL(n, size) \
	_IOC(_IOC_READ|_IOC_WRITE, PMCRAID_DRIVER_IOCTL, (n), (size))

#घोषणा FMW_IOCTL(n, size) \
	_IOC(_IOC_READ|_IOC_WRITE, PMCRAID_PASSTHROUGH_IOCTL,  (n), (size))

/*
 * _ARGSIZE: macro that gives size of the argument type passed to an IOCTL cmd.
 * This is to facilitate applications aव्योमing un-necessary memory allocations.
 * For example, most of driver handled ioctls करो not require ioarcb, ioasa.
 */
#घोषणा _ARGSIZE(arg) (माप(काष्ठा pmcraid_ioctl_header) + माप(arg))

/* Driver handled IOCTL command definitions */

#घोषणा PMCRAID_IOCTL_RESET_ADAPTER          \
	DRV_IOCTL(5, माप(काष्ठा pmcraid_ioctl_header))

/* passthrough/firmware handled commands */
#घोषणा PMCRAID_IOCTL_PASSTHROUGH_COMMAND         \
	FMW_IOCTL(1, माप(काष्ठा pmcraid_passthrough_ioctl_buffer))

#घोषणा PMCRAID_IOCTL_DOWNLOAD_MICROCODE     \
	FMW_IOCTL(2, माप(काष्ठा pmcraid_passthrough_ioctl_buffer))


#पूर्ण_अगर /* _PMCRAID_H */
