<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ipr.h -- driver क्रम IBM Power Linux RAID adapters
 *
 * Written By: Brian King <brking@us.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2003, 2004 IBM Corporation
 *
 * Alan Cox <alan@lxorguk.ukuu.org.uk> - Removed several careless u32/dma_addr_t errors
 *				that broke 64bit platक्रमms.
 */

#अगर_अघोषित _IPR_H
#घोषणा _IPR_H

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/types.h>
#समावेश <linux/completion.h>
#समावेश <linux/libata.h>
#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/irq_poll.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

/*
 * Literals
 */
#घोषणा IPR_DRIVER_VERSION "2.6.4"
#घोषणा IPR_DRIVER_DATE "(March 14, 2017)"

/*
 * IPR_MAX_CMD_PER_LUN: This defines the maximum number of outstanding
 *	ops per device क्रम devices not running tagged command queuing.
 *	This can be adjusted at runसमय through sysfs device attributes.
 */
#घोषणा IPR_MAX_CMD_PER_LUN				6
#घोषणा IPR_MAX_CMD_PER_ATA_LUN			1

/*
 * IPR_NUM_BASE_CMD_BLKS: This defines the maximum number of
 *	ops the mid-layer can send to the adapter.
 */
#घोषणा IPR_NUM_BASE_CMD_BLKS			(ioa_cfg->max_cmds)

#घोषणा PCI_DEVICE_ID_IBM_OBSIDIAN_E	0x0339

#घोषणा PCI_DEVICE_ID_IBM_CROC_FPGA_E2          0x033D
#घोषणा PCI_DEVICE_ID_IBM_CROCODILE             0x034A
#घोषणा PCI_DEVICE_ID_IBM_RATTLESNAKE		0x04DA

#घोषणा IPR_SUBS_DEV_ID_2780	0x0264
#घोषणा IPR_SUBS_DEV_ID_5702	0x0266
#घोषणा IPR_SUBS_DEV_ID_5703	0x0278
#घोषणा IPR_SUBS_DEV_ID_572E	0x028D
#घोषणा IPR_SUBS_DEV_ID_573E	0x02D3
#घोषणा IPR_SUBS_DEV_ID_573D	0x02D4
#घोषणा IPR_SUBS_DEV_ID_571A	0x02C0
#घोषणा IPR_SUBS_DEV_ID_571B	0x02BE
#घोषणा IPR_SUBS_DEV_ID_571E	0x02BF
#घोषणा IPR_SUBS_DEV_ID_571F	0x02D5
#घोषणा IPR_SUBS_DEV_ID_572A	0x02C1
#घोषणा IPR_SUBS_DEV_ID_572B	0x02C2
#घोषणा IPR_SUBS_DEV_ID_572F	0x02C3
#घोषणा IPR_SUBS_DEV_ID_574E	0x030A
#घोषणा IPR_SUBS_DEV_ID_575B	0x030D
#घोषणा IPR_SUBS_DEV_ID_575C	0x0338
#घोषणा IPR_SUBS_DEV_ID_57B3	0x033A
#घोषणा IPR_SUBS_DEV_ID_57B7	0x0360
#घोषणा IPR_SUBS_DEV_ID_57B8	0x02C2

#घोषणा IPR_SUBS_DEV_ID_57B4    0x033B
#घोषणा IPR_SUBS_DEV_ID_57B2    0x035F
#घोषणा IPR_SUBS_DEV_ID_57C0    0x0352
#घोषणा IPR_SUBS_DEV_ID_57C3    0x0353
#घोषणा IPR_SUBS_DEV_ID_57C4    0x0354
#घोषणा IPR_SUBS_DEV_ID_57C6    0x0357
#घोषणा IPR_SUBS_DEV_ID_57CC    0x035C

#घोषणा IPR_SUBS_DEV_ID_57B5    0x033C
#घोषणा IPR_SUBS_DEV_ID_57CE    0x035E
#घोषणा IPR_SUBS_DEV_ID_57B1    0x0355

#घोषणा IPR_SUBS_DEV_ID_574D    0x0356
#घोषणा IPR_SUBS_DEV_ID_57C8    0x035D

#घोषणा IPR_SUBS_DEV_ID_57D5    0x03FB
#घोषणा IPR_SUBS_DEV_ID_57D6    0x03FC
#घोषणा IPR_SUBS_DEV_ID_57D7    0x03FF
#घोषणा IPR_SUBS_DEV_ID_57D8    0x03FE
#घोषणा IPR_SUBS_DEV_ID_57D9    0x046D
#घोषणा IPR_SUBS_DEV_ID_57DA    0x04CA
#घोषणा IPR_SUBS_DEV_ID_57EB    0x0474
#घोषणा IPR_SUBS_DEV_ID_57EC    0x0475
#घोषणा IPR_SUBS_DEV_ID_57ED    0x0499
#घोषणा IPR_SUBS_DEV_ID_57EE    0x049A
#घोषणा IPR_SUBS_DEV_ID_57EF    0x049B
#घोषणा IPR_SUBS_DEV_ID_57F0    0x049C
#घोषणा IPR_SUBS_DEV_ID_2CCA	0x04C7
#घोषणा IPR_SUBS_DEV_ID_2CD2	0x04C8
#घोषणा IPR_SUBS_DEV_ID_2CCD	0x04C9
#घोषणा IPR_SUBS_DEV_ID_580A	0x04FC
#घोषणा IPR_SUBS_DEV_ID_580B	0x04FB
#घोषणा IPR_NAME				"ipr"

/*
 * Return codes
 */
#घोषणा IPR_RC_JOB_CONTINUE		1
#घोषणा IPR_RC_JOB_RETURN		2

/*
 * IOASCs
 */
#घोषणा IPR_IOASC_NR_INIT_CMD_REQUIRED		0x02040200
#घोषणा IPR_IOASC_NR_IOA_RESET_REQUIRED		0x02048000
#घोषणा IPR_IOASC_SYNC_REQUIRED			0x023f0000
#घोषणा IPR_IOASC_MED_DO_NOT_REALLOC		0x03110C00
#घोषणा IPR_IOASC_HW_SEL_TIMEOUT			0x04050000
#घोषणा IPR_IOASC_HW_DEV_BUS_STATUS			0x04448500
#घोषणा	IPR_IOASC_IOASC_MASK			0xFFFFFF00
#घोषणा	IPR_IOASC_SCSI_STATUS_MASK		0x000000FF
#घोषणा IPR_IOASC_HW_CMD_FAILED			0x046E0000
#घोषणा IPR_IOASC_IR_INVALID_REQ_TYPE_OR_PKT	0x05240000
#घोषणा IPR_IOASC_IR_RESOURCE_HANDLE		0x05250000
#घोषणा IPR_IOASC_IR_NO_CMDS_TO_2ND_IOA		0x05258100
#घोषणा IPR_IOASA_IR_DUAL_IOA_DISABLED		0x052C8000
#घोषणा IPR_IOASC_BUS_WAS_RESET			0x06290000
#घोषणा IPR_IOASC_BUS_WAS_RESET_BY_OTHER		0x06298000
#घोषणा IPR_IOASC_ABORTED_CMD_TERM_BY_HOST	0x0B5A0000
#घोषणा IPR_IOASC_IR_NON_OPTIMIZED		0x05258200

#घोषणा IPR_FIRST_DRIVER_IOASC			0x10000000
#घोषणा IPR_IOASC_IOA_WAS_RESET			0x10000001
#घोषणा IPR_IOASC_PCI_ACCESS_ERROR			0x10000002

/* Driver data flags */
#घोषणा IPR_USE_LONG_TRANSOP_TIMEOUT		0x00000001
#घोषणा IPR_USE_PCI_WARM_RESET			0x00000002

#घोषणा IPR_DEFAULT_MAX_ERROR_DUMP			984
#घोषणा IPR_NUM_LOG_HCAMS				2
#घोषणा IPR_NUM_CFG_CHG_HCAMS				2
#घोषणा IPR_NUM_HCAM_QUEUE				12
#घोषणा IPR_NUM_HCAMS	(IPR_NUM_LOG_HCAMS + IPR_NUM_CFG_CHG_HCAMS)
#घोषणा IPR_MAX_HCAMS	(IPR_NUM_HCAMS + IPR_NUM_HCAM_QUEUE)

#घोषणा IPR_MAX_SIS64_TARGETS_PER_BUS			1024
#घोषणा IPR_MAX_SIS64_LUNS_PER_TARGET			0xffffffff

#घोषणा IPR_MAX_NUM_TARGETS_PER_BUS			256
#घोषणा IPR_MAX_NUM_LUNS_PER_TARGET			256
#घोषणा IPR_VSET_BUS					0xff
#घोषणा IPR_IOA_BUS						0xff
#घोषणा IPR_IOA_TARGET					0xff
#घोषणा IPR_IOA_LUN						0xff
#घोषणा IPR_MAX_NUM_BUSES				16

#घोषणा IPR_NUM_RESET_RELOAD_RETRIES		3

/* We need resources क्रम HCAMS, IOA reset, IOA bringकरोwn, and ERP */
#घोषणा IPR_NUM_INTERNAL_CMD_BLKS	(IPR_NUM_HCAMS + \
                                     ((IPR_NUM_RESET_RELOAD_RETRIES + 1) * 2) + 4)

#घोषणा IPR_MAX_COMMANDS		100
#घोषणा IPR_NUM_CMD_BLKS		(IPR_NUM_BASE_CMD_BLKS + \
						IPR_NUM_INTERNAL_CMD_BLKS)

#घोषणा IPR_MAX_PHYSICAL_DEVS				192
#घोषणा IPR_DEFAULT_SIS64_DEVS				1024
#घोषणा IPR_MAX_SIS64_DEVS				4096

#घोषणा IPR_MAX_SGLIST					64
#घोषणा IPR_IOA_MAX_SECTORS				32767
#घोषणा IPR_VSET_MAX_SECTORS				512
#घोषणा IPR_MAX_CDB_LEN					16
#घोषणा IPR_MAX_HRRQ_RETRIES				3

#घोषणा IPR_DEFAULT_BUS_WIDTH				16
#घोषणा IPR_80MBs_SCSI_RATE		((80 * 10) / (IPR_DEFAULT_BUS_WIDTH / 8))
#घोषणा IPR_U160_SCSI_RATE	((160 * 10) / (IPR_DEFAULT_BUS_WIDTH / 8))
#घोषणा IPR_U320_SCSI_RATE	((320 * 10) / (IPR_DEFAULT_BUS_WIDTH / 8))
#घोषणा IPR_MAX_SCSI_RATE(width) ((320 * 10) / ((width) / 8))

#घोषणा IPR_IOA_RES_HANDLE				0xffffffff
#घोषणा IPR_INVALID_RES_HANDLE			0
#घोषणा IPR_IOA_RES_ADDR				0x00ffffff

/*
 * Adapter Commands
 */
#घोषणा IPR_CANCEL_REQUEST				0xC0
#घोषणा	IPR_CANCEL_64BIT_IOARCB			0x01
#घोषणा IPR_QUERY_RSRC_STATE				0xC2
#घोषणा IPR_RESET_DEVICE				0xC3
#घोषणा	IPR_RESET_TYPE_SELECT				0x80
#घोषणा	IPR_LUN_RESET					0x40
#घोषणा	IPR_TARGET_RESET					0x20
#घोषणा	IPR_BUS_RESET					0x10
#घोषणा	IPR_ATA_PHY_RESET					0x80
#घोषणा IPR_ID_HOST_RR_Q				0xC4
#घोषणा IPR_QUERY_IOA_CONFIG				0xC5
#घोषणा IPR_CANCEL_ALL_REQUESTS			0xCE
#घोषणा IPR_HOST_CONTROLLED_ASYNC			0xCF
#घोषणा	IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE	0x01
#घोषणा	IPR_HCAM_CDB_OP_CODE_LOG_DATA		0x02
#घोषणा IPR_SET_SUPPORTED_DEVICES			0xFB
#घोषणा IPR_SET_ALL_SUPPORTED_DEVICES			0x80
#घोषणा IPR_IOA_SHUTDOWN				0xF7
#घोषणा	IPR_WR_BUF_DOWNLOAD_AND_SAVE			0x05
#घोषणा IPR_IOA_SERVICE_ACTION				0xD2

/* IOA Service Actions */
#घोषणा IPR_IOA_SA_CHANGE_CACHE_PARAMS			0x14

/*
 * Timeouts
 */
#घोषणा IPR_SHUTDOWN_TIMEOUT			(ipr_fastfail ? 60 * HZ : 10 * 60 * HZ)
#घोषणा IPR_VSET_RW_TIMEOUT			(ipr_fastfail ? 30 * HZ : 2 * 60 * HZ)
#घोषणा IPR_ABBREV_SHUTDOWN_TIMEOUT		(10 * HZ)
#घोषणा IPR_DUAL_IOA_ABBR_SHUTDOWN_TO	(2 * 60 * HZ)
#घोषणा IPR_DEVICE_RESET_TIMEOUT		(ipr_fastfail ? 10 * HZ : 30 * HZ)
#घोषणा IPR_CANCEL_TIMEOUT			(ipr_fastfail ? 10 * HZ : 30 * HZ)
#घोषणा IPR_CANCEL_ALL_TIMEOUT		(ipr_fastfail ? 10 * HZ : 30 * HZ)
#घोषणा IPR_ABORT_TASK_TIMEOUT		(ipr_fastfail ? 10 * HZ : 30 * HZ)
#घोषणा IPR_INTERNAL_TIMEOUT			(ipr_fastfail ? 10 * HZ : 30 * HZ)
#घोषणा IPR_WRITE_BUFFER_TIMEOUT		(30 * 60 * HZ)
#घोषणा IPR_SET_SUP_DEVICE_TIMEOUT		(2 * 60 * HZ)
#घोषणा IPR_REQUEST_SENSE_TIMEOUT		(10 * HZ)
#घोषणा IPR_OPERATIONAL_TIMEOUT		(5 * 60)
#घोषणा IPR_LONG_OPERATIONAL_TIMEOUT	(12 * 60)
#घोषणा IPR_WAIT_FOR_RESET_TIMEOUT		(2 * HZ)
#घोषणा IPR_CHECK_FOR_RESET_TIMEOUT		(HZ / 10)
#घोषणा IPR_WAIT_FOR_BIST_TIMEOUT		(2 * HZ)
#घोषणा IPR_PCI_ERROR_RECOVERY_TIMEOUT	(120 * HZ)
#घोषणा IPR_PCI_RESET_TIMEOUT			(HZ / 2)
#घोषणा IPR_SIS32_DUMP_TIMEOUT			(15 * HZ)
#घोषणा IPR_SIS64_DUMP_TIMEOUT			(40 * HZ)
#घोषणा IPR_DUMP_DELAY_SECONDS			4
#घोषणा IPR_DUMP_DELAY_TIMEOUT			(IPR_DUMP_DELAY_SECONDS * HZ)

/*
 * SCSI Literals
 */
#घोषणा IPR_VENDOR_ID_LEN			8
#घोषणा IPR_PROD_ID_LEN				16
#घोषणा IPR_SERIAL_NUM_LEN			8

/*
 * Hardware literals
 */
#घोषणा IPR_FMT2_MBX_ADDR_MASK				0x0fffffff
#घोषणा IPR_FMT2_MBX_BAR_SEL_MASK			0xf0000000
#घोषणा IPR_FMT2_MKR_BAR_SEL_SHIFT			28
#घोषणा IPR_GET_FMT2_BAR_SEL(mbx) \
(((mbx) & IPR_FMT2_MBX_BAR_SEL_MASK) >> IPR_FMT2_MKR_BAR_SEL_SHIFT)
#घोषणा IPR_SDT_FMT2_BAR0_SEL				0x0
#घोषणा IPR_SDT_FMT2_BAR1_SEL				0x1
#घोषणा IPR_SDT_FMT2_BAR2_SEL				0x2
#घोषणा IPR_SDT_FMT2_BAR3_SEL				0x3
#घोषणा IPR_SDT_FMT2_BAR4_SEL				0x4
#घोषणा IPR_SDT_FMT2_BAR5_SEL				0x5
#घोषणा IPR_SDT_FMT2_EXP_ROM_SEL			0x8
#घोषणा IPR_FMT2_SDT_READY_TO_USE			0xC4D4E3F2
#घोषणा IPR_FMT3_SDT_READY_TO_USE			0xC4D4E3F3
#घोषणा IPR_DOORBELL					0x82800000
#घोषणा IPR_RUNTIME_RESET				0x40000000

#घोषणा IPR_IPL_INIT_MIN_STAGE_TIME			5
#घोषणा IPR_IPL_INIT_DEFAULT_STAGE_TIME                 30
#घोषणा IPR_IPL_INIT_STAGE_UNKNOWN			0x0
#घोषणा IPR_IPL_INIT_STAGE_TRANSOP			0xB0000000
#घोषणा IPR_IPL_INIT_STAGE_MASK				0xff000000
#घोषणा IPR_IPL_INIT_STAGE_TIME_MASK			0x0000ffff
#घोषणा IPR_PCII_IPL_STAGE_CHANGE			(0x80000000 >> 0)

#घोषणा IPR_PCII_MAILBOX_STABLE				(0x80000000 >> 4)
#घोषणा IPR_WAIT_FOR_MAILBOX				(2 * HZ)

#घोषणा IPR_PCII_IOA_TRANS_TO_OPER			(0x80000000 >> 0)
#घोषणा IPR_PCII_IOARCB_XFER_FAILED			(0x80000000 >> 3)
#घोषणा IPR_PCII_IOA_UNIT_CHECKED			(0x80000000 >> 4)
#घोषणा IPR_PCII_NO_HOST_RRQ				(0x80000000 >> 5)
#घोषणा IPR_PCII_CRITICAL_OPERATION			(0x80000000 >> 6)
#घोषणा IPR_PCII_IO_DEBUG_ACKNOWLEDGE		(0x80000000 >> 7)
#घोषणा IPR_PCII_IOARRIN_LOST				(0x80000000 >> 27)
#घोषणा IPR_PCII_MMIO_ERROR				(0x80000000 >> 28)
#घोषणा IPR_PCII_PROC_ERR_STATE			(0x80000000 >> 29)
#घोषणा IPR_PCII_HRRQ_UPDATED				(0x80000000 >> 30)
#घोषणा IPR_PCII_CORE_ISSUED_RST_REQ		(0x80000000 >> 31)

#घोषणा IPR_PCII_ERROR_INTERRUPTS \
(IPR_PCII_IOARCB_XFER_FAILED | IPR_PCII_IOA_UNIT_CHECKED | \
IPR_PCII_NO_HOST_RRQ | IPR_PCII_IOARRIN_LOST | IPR_PCII_MMIO_ERROR)

#घोषणा IPR_PCII_OPER_INTERRUPTS \
(IPR_PCII_ERROR_INTERRUPTS | IPR_PCII_HRRQ_UPDATED | IPR_PCII_IOA_TRANS_TO_OPER)

#घोषणा IPR_UPROCI_RESET_ALERT			(0x80000000 >> 7)
#घोषणा IPR_UPROCI_IO_DEBUG_ALERT			(0x80000000 >> 9)
#घोषणा IPR_UPROCI_SIS64_START_BIST			(0x80000000 >> 23)

#घोषणा IPR_LDUMP_MAX_LONG_ACK_DELAY_IN_USEC		200000	/* 200 ms */
#घोषणा IPR_LDUMP_MAX_SHORT_ACK_DELAY_IN_USEC		200000	/* 200 ms */

/*
 * Dump literals
 */
#घोषणा IPR_FMT2_MAX_IOA_DUMP_SIZE			(4 * 1024 * 1024)
#घोषणा IPR_FMT3_MAX_IOA_DUMP_SIZE			(80 * 1024 * 1024)
#घोषणा IPR_FMT2_NUM_SDT_ENTRIES			511
#घोषणा IPR_FMT3_NUM_SDT_ENTRIES			0xFFF
#घोषणा IPR_FMT2_MAX_NUM_DUMP_PAGES	((IPR_FMT2_MAX_IOA_DUMP_SIZE / PAGE_SIZE) + 1)
#घोषणा IPR_FMT3_MAX_NUM_DUMP_PAGES	((IPR_FMT3_MAX_IOA_DUMP_SIZE / PAGE_SIZE) + 1)

/*
 * Misc literals
 */
#घोषणा IPR_NUM_IOADL_ENTRIES			IPR_MAX_SGLIST
#घोषणा IPR_MAX_MSIX_VECTORS		0x10
#घोषणा IPR_MAX_HRRQ_NUM		0x10
#घोषणा IPR_INIT_HRRQ			0x0

/*
 * Adapter पूर्णांकerface types
 */

काष्ठा ipr_res_addr अणु
	u8 reserved;
	u8 bus;
	u8 target;
	u8 lun;
#घोषणा IPR_GET_PHYS_LOC(res_addr) \
	(((res_addr).bus << 16) | ((res_addr).target << 8) | (res_addr).lun)
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_std_inq_vpids अणु
	u8 venकरोr_id[IPR_VENDOR_ID_LEN];
	u8 product_id[IPR_PROD_ID_LEN];
पूर्ण__attribute__((packed));

काष्ठा ipr_vpd अणु
	काष्ठा ipr_std_inq_vpids vpids;
	u8 sn[IPR_SERIAL_NUM_LEN];
पूर्ण__attribute__((packed));

काष्ठा ipr_ext_vpd अणु
	काष्ठा ipr_vpd vpd;
	__be32 wwid[2];
पूर्ण__attribute__((packed));

काष्ठा ipr_ext_vpd64 अणु
	काष्ठा ipr_vpd vpd;
	__be32 wwid[4];
पूर्ण__attribute__((packed));

काष्ठा ipr_std_inq_data अणु
	u8 peri_qual_dev_type;
#घोषणा IPR_STD_INQ_PERI_QUAL(peri) ((peri) >> 5)
#घोषणा IPR_STD_INQ_PERI_DEV_TYPE(peri) ((peri) & 0x1F)

	u8 हटाओable_medium_rsvd;
#घोषणा IPR_STD_INQ_REMOVEABLE_MEDIUM 0x80

#घोषणा IPR_IS_DASD_DEVICE(std_inq) \
((IPR_STD_INQ_PERI_DEV_TYPE((std_inq).peri_qual_dev_type) == TYPE_DISK) && \
!(((std_inq).हटाओable_medium_rsvd) & IPR_STD_INQ_REMOVEABLE_MEDIUM))

#घोषणा IPR_IS_SES_DEVICE(std_inq) \
(IPR_STD_INQ_PERI_DEV_TYPE((std_inq).peri_qual_dev_type) == TYPE_ENCLOSURE)

	u8 version;
	u8 aen_naca_fmt;
	u8 additional_len;
	u8 sccs_rsvd;
	u8 bq_enc_multi;
	u8 sync_cmdq_flags;

	काष्ठा ipr_std_inq_vpids vpids;

	u8 ros_rsvd_ram_rsvd[4];

	u8 serial_num[IPR_SERIAL_NUM_LEN];
पूर्ण__attribute__ ((packed));

#घोषणा IPR_RES_TYPE_AF_DASD		0x00
#घोषणा IPR_RES_TYPE_GENERIC_SCSI	0x01
#घोषणा IPR_RES_TYPE_VOLUME_SET		0x02
#घोषणा IPR_RES_TYPE_REMOTE_AF_DASD	0x03
#घोषणा IPR_RES_TYPE_GENERIC_ATA	0x04
#घोषणा IPR_RES_TYPE_ARRAY		0x05
#घोषणा IPR_RES_TYPE_IOAFP		0xff

काष्ठा ipr_config_table_entry अणु
	u8 proto;
#घोषणा IPR_PROTO_SATA			0x02
#घोषणा IPR_PROTO_SATA_ATAPI		0x03
#घोषणा IPR_PROTO_SAS_STP		0x06
#घोषणा IPR_PROTO_SAS_STP_ATAPI		0x07
	u8 array_id;
	u8 flags;
#घोषणा IPR_IS_IOA_RESOURCE		0x80
	u8 rsvd_subtype;

#घोषणा IPR_QUEUEING_MODEL(res)	((((res)->flags) & 0x70) >> 4)
#घोषणा IPR_QUEUE_FROZEN_MODEL		0
#घोषणा IPR_QUEUE_NACA_MODEL		1

	काष्ठा ipr_res_addr res_addr;
	__be32 res_handle;
	__be32 lun_wwn[2];
	काष्ठा ipr_std_inq_data std_inq_data;
पूर्ण__attribute__ ((packed, aligned (4)));

काष्ठा ipr_config_table_entry64 अणु
	u8 res_type;
	u8 proto;
	u8 vset_num;
	u8 array_id;
	__be16 flags;
	__be16 res_flags;
#घोषणा IPR_QUEUEING_MODEL64(res) ((((res)->res_flags) & 0x7000) >> 12)
	__be32 res_handle;
	u8 dev_id_type;
	u8 reserved[3];
	__be64 dev_id;
	__be64 lun;
	__be64 lun_wwn[2];
#घोषणा IPR_MAX_RES_PATH_LENGTH		48
	__be64 res_path;
	काष्ठा ipr_std_inq_data std_inq_data;
	u8 reserved2[4];
	__be64 reserved3[2];
	u8 reserved4[8];
पूर्ण__attribute__ ((packed, aligned (8)));

काष्ठा ipr_config_table_hdr अणु
	u8 num_entries;
	u8 flags;
#घोषणा IPR_UCODE_DOWNLOAD_REQ	0x10
	__be16 reserved;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_config_table_hdr64 अणु
	__be16 num_entries;
	__be16 reserved;
	u8 flags;
	u8 reserved2[11];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_config_table अणु
	काष्ठा ipr_config_table_hdr hdr;
	काष्ठा ipr_config_table_entry dev[];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_config_table64 अणु
	काष्ठा ipr_config_table_hdr64 hdr64;
	काष्ठा ipr_config_table_entry64 dev[];
पूर्ण__attribute__((packed, aligned (8)));

काष्ठा ipr_config_table_entry_wrapper अणु
	जोड़ अणु
		काष्ठा ipr_config_table_entry *cfgte;
		काष्ठा ipr_config_table_entry64 *cfgte64;
	पूर्ण u;
पूर्ण;

काष्ठा ipr_hostrcb_cfg_ch_not अणु
	जोड़ अणु
		काष्ठा ipr_config_table_entry cfgte;
		काष्ठा ipr_config_table_entry64 cfgte64;
	पूर्ण u;
	u8 reserved[936];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_supported_device अणु
	__be16 data_length;
	u8 reserved;
	u8 num_records;
	काष्ठा ipr_std_inq_vpids vpids;
	u8 reserved2[16];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hrr_queue अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	__be32 *host_rrq;
	dma_addr_t host_rrq_dma;
#घोषणा IPR_HRRQ_REQ_RESP_HANDLE_MASK	0xfffffffc
#घोषणा IPR_HRRQ_RESP_BIT_SET		0x00000002
#घोषणा IPR_HRRQ_TOGGLE_BIT		0x00000001
#घोषणा IPR_HRRQ_REQ_RESP_HANDLE_SHIFT	2
#घोषणा IPR_ID_HRRQ_SELE_ENABLE		0x02
	अस्थिर __be32 *hrrq_start;
	अस्थिर __be32 *hrrq_end;
	अस्थिर __be32 *hrrq_curr;

	काष्ठा list_head hrrq_मुक्त_q;
	काष्ठा list_head hrrq_pending_q;
	spinlock_t _lock;
	spinlock_t *lock;

	अस्थिर u32 toggle_bit;
	u32 size;
	u32 min_cmd_id;
	u32 max_cmd_id;
	u8 allow_पूर्णांकerrupts:1;
	u8 ioa_is_dead:1;
	u8 allow_cmds:1;
	u8 removing_ioa:1;

	काष्ठा irq_poll iopoll;
पूर्ण;

/* Command packet काष्ठाure */
काष्ठा ipr_cmd_pkt अणु
	u8 reserved;		/* Reserved by IOA */
	u8 hrrq_id;
	u8 request_type;
#घोषणा IPR_RQTYPE_SCSICDB		0x00
#घोषणा IPR_RQTYPE_IOACMD		0x01
#घोषणा IPR_RQTYPE_HCAM			0x02
#घोषणा IPR_RQTYPE_ATA_PASSTHRU	0x04
#घोषणा IPR_RQTYPE_PIPE			0x05

	u8 reserved2;

	u8 flags_hi;
#घोषणा IPR_FLAGS_HI_WRITE_NOT_READ		0x80
#घोषणा IPR_FLAGS_HI_NO_ULEN_CHK		0x20
#घोषणा IPR_FLAGS_HI_SYNC_OVERRIDE		0x10
#घोषणा IPR_FLAGS_HI_SYNC_COMPLETE		0x08
#घोषणा IPR_FLAGS_HI_NO_LINK_DESC		0x04

	u8 flags_lo;
#घोषणा IPR_FLAGS_LO_ALIGNED_BFR		0x20
#घोषणा IPR_FLAGS_LO_DELAY_AFTER_RST		0x10
#घोषणा IPR_FLAGS_LO_UNTAGGED_TASK		0x00
#घोषणा IPR_FLAGS_LO_SIMPLE_TASK		0x02
#घोषणा IPR_FLAGS_LO_ORDERED_TASK		0x04
#घोषणा IPR_FLAGS_LO_HEAD_OF_Q_TASK		0x06
#घोषणा IPR_FLAGS_LO_ACA_TASK			0x08

	u8 cdb[16];
	__be16 समयout;
पूर्ण__attribute__ ((packed, aligned(4)));

काष्ठा ipr_ioarcb_ata_regs अणु	/* 22 bytes */
	u8 flags;
#घोषणा IPR_ATA_FLAG_PACKET_CMD			0x80
#घोषणा IPR_ATA_FLAG_XFER_TYPE_DMA			0x40
#घोषणा IPR_ATA_FLAG_STATUS_ON_GOOD_COMPLETION	0x20
	u8 reserved[3];

	__be16 data;
	u8 feature;
	u8 nsect;
	u8 lbal;
	u8 lbam;
	u8 lbah;
	u8 device;
	u8 command;
	u8 reserved2[3];
	u8 hob_feature;
	u8 hob_nsect;
	u8 hob_lbal;
	u8 hob_lbam;
	u8 hob_lbah;
	u8 ctl;
पूर्ण__attribute__ ((packed, aligned(2)));

काष्ठा ipr_ioadl_desc अणु
	__be32 flags_and_data_len;
#घोषणा IPR_IOADL_FLAGS_MASK		0xff000000
#घोषणा IPR_IOADL_GET_FLAGS(x) (be32_to_cpu(x) & IPR_IOADL_FLAGS_MASK)
#घोषणा IPR_IOADL_DATA_LEN_MASK		0x00ffffff
#घोषणा IPR_IOADL_GET_DATA_LEN(x) (be32_to_cpu(x) & IPR_IOADL_DATA_LEN_MASK)
#घोषणा IPR_IOADL_FLAGS_READ		0x48000000
#घोषणा IPR_IOADL_FLAGS_READ_LAST	0x49000000
#घोषणा IPR_IOADL_FLAGS_WRITE		0x68000000
#घोषणा IPR_IOADL_FLAGS_WRITE_LAST	0x69000000
#घोषणा IPR_IOADL_FLAGS_LAST		0x01000000

	__be32 address;
पूर्ण__attribute__((packed, aligned (8)));

काष्ठा ipr_ioadl64_desc अणु
	__be32 flags;
	__be32 data_len;
	__be64 address;
पूर्ण__attribute__((packed, aligned (16)));

काष्ठा ipr_ata64_ioadl अणु
	काष्ठा ipr_ioarcb_ata_regs regs;
	u16 reserved[5];
	काष्ठा ipr_ioadl64_desc ioadl64[IPR_NUM_IOADL_ENTRIES];
पूर्ण__attribute__((packed, aligned (16)));

काष्ठा ipr_ioarcb_add_data अणु
	जोड़ अणु
		काष्ठा ipr_ioarcb_ata_regs regs;
		काष्ठा ipr_ioadl_desc ioadl[5];
		__be32 add_cmd_parms[10];
	पूर्ण u;
पूर्ण__attribute__ ((packed, aligned (4)));

काष्ठा ipr_ioarcb_sis64_add_addr_ecb अणु
	__be64 ioasa_host_pci_addr;
	__be64 data_ioadl_addr;
	__be64 reserved;
	__be32 ext_control_buf[4];
पूर्ण__attribute__((packed, aligned (8)));

/* IOA Request Control Block    128 bytes  */
काष्ठा ipr_ioarcb अणु
	जोड़ अणु
		__be32 ioarcb_host_pci_addr;
		__be64 ioarcb_host_pci_addr64;
	पूर्ण a;
	__be32 res_handle;
	__be32 host_response_handle;
	__be32 reserved1;
	__be32 reserved2;
	__be32 reserved3;

	__be32 data_transfer_length;
	__be32 पढ़ो_data_transfer_length;
	__be32 ग_लिखो_ioadl_addr;
	__be32 ioadl_len;
	__be32 पढ़ो_ioadl_addr;
	__be32 पढ़ो_ioadl_len;

	__be32 ioasa_host_pci_addr;
	__be16 ioasa_len;
	__be16 reserved4;

	काष्ठा ipr_cmd_pkt cmd_pkt;

	__be16 add_cmd_parms_offset;
	__be16 add_cmd_parms_len;

	जोड़ अणु
		काष्ठा ipr_ioarcb_add_data add_data;
		काष्ठा ipr_ioarcb_sis64_add_addr_ecb sis64_addr_data;
	पूर्ण u;

पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ioasa_vset अणु
	__be32 failing_lba_hi;
	__be32 failing_lba_lo;
	__be32 reserved;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ioasa_af_dasd अणु
	__be32 failing_lba;
	__be32 reserved[2];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ioasa_gpdd अणु
	u8 end_state;
	u8 bus_phase;
	__be16 reserved;
	__be32 ioa_data[2];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ioasa_gata अणु
	u8 error;
	u8 nsect;		/* Interrupt reason */
	u8 lbal;
	u8 lbam;
	u8 lbah;
	u8 device;
	u8 status;
	u8 alt_status;	/* ATA CTL */
	u8 hob_nsect;
	u8 hob_lbal;
	u8 hob_lbam;
	u8 hob_lbah;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_स्वतः_sense अणु
	__be16 स्वतः_sense_len;
	__be16 ioa_data_len;
	__be32 data[SCSI_SENSE_BUFFERSIZE/माप(__be32)];
पूर्ण;

काष्ठा ipr_ioasa_hdr अणु
	__be32 ioasc;
#घोषणा IPR_IOASC_SENSE_KEY(ioasc) ((ioasc) >> 24)
#घोषणा IPR_IOASC_SENSE_CODE(ioasc) (((ioasc) & 0x00ff0000) >> 16)
#घोषणा IPR_IOASC_SENSE_QUAL(ioasc) (((ioasc) & 0x0000ff00) >> 8)
#घोषणा IPR_IOASC_SENSE_STATUS(ioasc) ((ioasc) & 0x000000ff)

	__be16 ret_stat_len;	/* Length of the वापसed IOASA */

	__be16 avail_stat_len;	/* Total Length of status available. */

	__be32 residual_data_len;	/* number of bytes in the host data */
	/* buffers that were not used by the IOARCB command. */

	__be32 ilid;
#घोषणा IPR_NO_ILID			0
#घोषणा IPR_DRIVER_ILID		0xffffffff

	__be32 fd_ioasc;

	__be32 fd_phys_locator;

	__be32 fd_res_handle;

	__be32 ioasc_specअगरic;	/* status code specअगरic field */
#घोषणा IPR_ADDITIONAL_STATUS_FMT		0x80000000
#घोषणा IPR_AUTOSENSE_VALID			0x40000000
#घोषणा IPR_ATA_DEVICE_WAS_RESET		0x20000000
#घोषणा IPR_IOASC_SPECIFIC_MASK		0x00ffffff
#घोषणा IPR_FIELD_POINTER_VALID		(0x80000000 >> 8)
#घोषणा IPR_FIELD_POINTER_MASK		0x0000ffff

पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ioasa अणु
	काष्ठा ipr_ioasa_hdr hdr;

	जोड़ अणु
		काष्ठा ipr_ioasa_vset vset;
		काष्ठा ipr_ioasa_af_dasd dasd;
		काष्ठा ipr_ioasa_gpdd gpdd;
		काष्ठा ipr_ioasa_gata gata;
	पूर्ण u;

	काष्ठा ipr_स्वतः_sense स्वतः_sense;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ioasa64 अणु
	काष्ठा ipr_ioasa_hdr hdr;
	u8 fd_res_path[8];

	जोड़ अणु
		काष्ठा ipr_ioasa_vset vset;
		काष्ठा ipr_ioasa_af_dasd dasd;
		काष्ठा ipr_ioasa_gpdd gpdd;
		काष्ठा ipr_ioasa_gata gata;
	पूर्ण u;

	काष्ठा ipr_स्वतः_sense स्वतः_sense;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_mode_parm_hdr अणु
	u8 length;
	u8 medium_type;
	u8 device_spec_parms;
	u8 block_desc_len;
पूर्ण__attribute__((packed));

काष्ठा ipr_mode_pages अणु
	काष्ठा ipr_mode_parm_hdr hdr;
	u8 data[255 - माप(काष्ठा ipr_mode_parm_hdr)];
पूर्ण__attribute__((packed));

काष्ठा ipr_mode_page_hdr अणु
	u8 ps_page_code;
#घोषणा IPR_MODE_PAGE_PS	0x80
#घोषणा IPR_GET_MODE_PAGE_CODE(hdr) ((hdr)->ps_page_code & 0x3F)
	u8 page_length;
पूर्ण__attribute__ ((packed));

काष्ठा ipr_dev_bus_entry अणु
	काष्ठा ipr_res_addr res_addr;
	u8 flags;
#घोषणा IPR_SCSI_ATTR_ENABLE_QAS			0x80
#घोषणा IPR_SCSI_ATTR_DISABLE_QAS			0x40
#घोषणा IPR_SCSI_ATTR_QAS_MASK				0xC0
#घोषणा IPR_SCSI_ATTR_ENABLE_TM				0x20
#घोषणा IPR_SCSI_ATTR_NO_TERM_PWR			0x10
#घोषणा IPR_SCSI_ATTR_TM_SUPPORTED			0x08
#घोषणा IPR_SCSI_ATTR_LVD_TO_SE_NOT_ALLOWED	0x04

	u8 scsi_id;
	u8 bus_width;
	u8 extended_reset_delay;
#घोषणा IPR_EXTENDED_RESET_DELAY	7

	__be32 max_xfer_rate;

	u8 spinup_delay;
	u8 reserved3;
	__be16 reserved4;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_mode_page28 अणु
	काष्ठा ipr_mode_page_hdr hdr;
	u8 num_entries;
	u8 entry_length;
	काष्ठा ipr_dev_bus_entry bus[];
पूर्ण__attribute__((packed));

काष्ठा ipr_mode_page24 अणु
	काष्ठा ipr_mode_page_hdr hdr;
	u8 flags;
#घोषणा IPR_ENABLE_DUAL_IOA_AF 0x80
पूर्ण__attribute__((packed));

काष्ठा ipr_ioa_vpd अणु
	काष्ठा ipr_std_inq_data std_inq_data;
	u8 ascii_part_num[12];
	u8 reserved[40];
	u8 ascii_plant_code[4];
पूर्ण__attribute__((packed));

काष्ठा ipr_inquiry_page3 अणु
	u8 peri_qual_dev_type;
	u8 page_code;
	u8 reserved1;
	u8 page_length;
	u8 ascii_len;
	u8 reserved2[3];
	u8 load_id[4];
	u8 major_release;
	u8 card_type;
	u8 minor_release[2];
	u8 ptf_number[4];
	u8 patch_number[4];
पूर्ण__attribute__((packed));

काष्ठा ipr_inquiry_cap अणु
	u8 peri_qual_dev_type;
	u8 page_code;
	u8 reserved1;
	u8 page_length;
	u8 ascii_len;
	u8 reserved2;
	u8 sis_version[2];
	u8 cap;
#घोषणा IPR_CAP_DUAL_IOA_RAID		0x80
	u8 reserved3[15];
पूर्ण__attribute__((packed));

#घोषणा IPR_INQUIRY_PAGE0_ENTRIES 20
काष्ठा ipr_inquiry_page0 अणु
	u8 peri_qual_dev_type;
	u8 page_code;
	u8 reserved1;
	u8 len;
	u8 page[IPR_INQUIRY_PAGE0_ENTRIES];
पूर्ण__attribute__((packed));

काष्ठा ipr_inquiry_pageC4 अणु
	u8 peri_qual_dev_type;
	u8 page_code;
	u8 reserved1;
	u8 len;
	u8 cache_cap[4];
#घोषणा IPR_CAP_SYNC_CACHE		0x08
	u8 reserved2[20];
पूर्ण __packed;

काष्ठा ipr_hostrcb_device_data_entry अणु
	काष्ठा ipr_vpd vpd;
	काष्ठा ipr_res_addr dev_res_addr;
	काष्ठा ipr_vpd new_vpd;
	काष्ठा ipr_vpd ioa_last_with_dev_vpd;
	काष्ठा ipr_vpd cfc_last_with_dev_vpd;
	__be32 ioa_data[5];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_device_data_entry_enhanced अणु
	काष्ठा ipr_ext_vpd vpd;
	u8 ccin[4];
	काष्ठा ipr_res_addr dev_res_addr;
	काष्ठा ipr_ext_vpd new_vpd;
	u8 new_ccin[4];
	काष्ठा ipr_ext_vpd ioa_last_with_dev_vpd;
	काष्ठा ipr_ext_vpd cfc_last_with_dev_vpd;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb64_device_data_entry_enhanced अणु
	काष्ठा ipr_ext_vpd vpd;
	u8 ccin[4];
	u8 res_path[8];
	काष्ठा ipr_ext_vpd new_vpd;
	u8 new_ccin[4];
	काष्ठा ipr_ext_vpd ioa_last_with_dev_vpd;
	काष्ठा ipr_ext_vpd cfc_last_with_dev_vpd;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_array_data_entry अणु
	काष्ठा ipr_vpd vpd;
	काष्ठा ipr_res_addr expected_dev_res_addr;
	काष्ठा ipr_res_addr dev_res_addr;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb64_array_data_entry अणु
	काष्ठा ipr_ext_vpd vpd;
	u8 ccin[4];
	u8 expected_res_path[8];
	u8 res_path[8];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_array_data_entry_enhanced अणु
	काष्ठा ipr_ext_vpd vpd;
	u8 ccin[4];
	काष्ठा ipr_res_addr expected_dev_res_addr;
	काष्ठा ipr_res_addr dev_res_addr;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_ff_error अणु
	__be32 ioa_data[758];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_01_error अणु
	__be32 seek_counter;
	__be32 पढ़ो_counter;
	u8 sense_data[32];
	__be32 ioa_data[236];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_21_error अणु
	__be32 wwn[4];
	u8 res_path[8];
	u8 primary_problem_desc[32];
	u8 second_problem_desc[32];
	__be32 sense_data[8];
	__be32 cdb[4];
	__be32 residual_trans_length;
	__be32 length_of_error;
	__be32 ioa_data[236];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_02_error अणु
	काष्ठा ipr_vpd ioa_vpd;
	काष्ठा ipr_vpd cfc_vpd;
	काष्ठा ipr_vpd ioa_last_attached_to_cfc_vpd;
	काष्ठा ipr_vpd cfc_last_attached_to_ioa_vpd;
	__be32 ioa_data[3];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_12_error अणु
	काष्ठा ipr_ext_vpd ioa_vpd;
	काष्ठा ipr_ext_vpd cfc_vpd;
	काष्ठा ipr_ext_vpd ioa_last_attached_to_cfc_vpd;
	काष्ठा ipr_ext_vpd cfc_last_attached_to_ioa_vpd;
	__be32 ioa_data[3];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_03_error अणु
	काष्ठा ipr_vpd ioa_vpd;
	काष्ठा ipr_vpd cfc_vpd;
	__be32 errors_detected;
	__be32 errors_logged;
	u8 ioa_data[12];
	काष्ठा ipr_hostrcb_device_data_entry dev[3];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_13_error अणु
	काष्ठा ipr_ext_vpd ioa_vpd;
	काष्ठा ipr_ext_vpd cfc_vpd;
	__be32 errors_detected;
	__be32 errors_logged;
	काष्ठा ipr_hostrcb_device_data_entry_enhanced dev[3];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_23_error अणु
	काष्ठा ipr_ext_vpd ioa_vpd;
	काष्ठा ipr_ext_vpd cfc_vpd;
	__be32 errors_detected;
	__be32 errors_logged;
	काष्ठा ipr_hostrcb64_device_data_entry_enhanced dev[3];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_04_error अणु
	काष्ठा ipr_vpd ioa_vpd;
	काष्ठा ipr_vpd cfc_vpd;
	u8 ioa_data[12];
	काष्ठा ipr_hostrcb_array_data_entry array_member[10];
	__be32 exposed_mode_adn;
	__be32 array_id;
	काष्ठा ipr_vpd incomp_dev_vpd;
	__be32 ioa_data2;
	काष्ठा ipr_hostrcb_array_data_entry array_member2[8];
	काष्ठा ipr_res_addr last_func_vset_res_addr;
	u8 vset_serial_num[IPR_SERIAL_NUM_LEN];
	u8 protection_level[8];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_14_error अणु
	काष्ठा ipr_ext_vpd ioa_vpd;
	काष्ठा ipr_ext_vpd cfc_vpd;
	__be32 exposed_mode_adn;
	__be32 array_id;
	काष्ठा ipr_res_addr last_func_vset_res_addr;
	u8 vset_serial_num[IPR_SERIAL_NUM_LEN];
	u8 protection_level[8];
	__be32 num_entries;
	काष्ठा ipr_hostrcb_array_data_entry_enhanced array_member[18];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_24_error अणु
	काष्ठा ipr_ext_vpd ioa_vpd;
	काष्ठा ipr_ext_vpd cfc_vpd;
	u8 reserved[2];
	u8 exposed_mode_adn;
#घोषणा IPR_INVALID_ARRAY_DEV_NUM		0xff
	u8 array_id;
	u8 last_res_path[8];
	u8 protection_level[8];
	काष्ठा ipr_ext_vpd64 array_vpd;
	u8 description[16];
	u8 reserved2[3];
	u8 num_entries;
	काष्ठा ipr_hostrcb64_array_data_entry array_member[32];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_07_error अणु
	u8 failure_reason[64];
	काष्ठा ipr_vpd vpd;
	__be32 data[222];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_17_error अणु
	u8 failure_reason[64];
	काष्ठा ipr_ext_vpd vpd;
	__be32 data[476];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_config_element अणु
	u8 type_status;
#घोषणा IPR_PATH_CFG_TYPE_MASK	0xF0
#घोषणा IPR_PATH_CFG_NOT_EXIST	0x00
#घोषणा IPR_PATH_CFG_IOA_PORT		0x10
#घोषणा IPR_PATH_CFG_EXP_PORT		0x20
#घोषणा IPR_PATH_CFG_DEVICE_PORT	0x30
#घोषणा IPR_PATH_CFG_DEVICE_LUN	0x40

#घोषणा IPR_PATH_CFG_STATUS_MASK	0x0F
#घोषणा IPR_PATH_CFG_NO_PROB		0x00
#घोषणा IPR_PATH_CFG_DEGRADED		0x01
#घोषणा IPR_PATH_CFG_FAILED		0x02
#घोषणा IPR_PATH_CFG_SUSPECT		0x03
#घोषणा IPR_PATH_NOT_DETECTED		0x04
#घोषणा IPR_PATH_INCORRECT_CONN	0x05

	u8 cascaded_expander;
	u8 phy;
	u8 link_rate;
#घोषणा IPR_PHY_LINK_RATE_MASK	0x0F

	__be32 wwid[2];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb64_config_element अणु
	__be16 length;
	u8 descriptor_id;
#घोषणा IPR_DESCRIPTOR_MASK		0xC0
#घोषणा IPR_DESCRIPTOR_SIS64		0x00

	u8 reserved;
	u8 type_status;

	u8 reserved2[2];
	u8 link_rate;

	u8 res_path[8];
	__be32 wwid[2];
पूर्ण__attribute__((packed, aligned (8)));

काष्ठा ipr_hostrcb_fabric_desc अणु
	__be16 length;
	u8 ioa_port;
	u8 cascaded_expander;
	u8 phy;
	u8 path_state;
#घोषणा IPR_PATH_ACTIVE_MASK		0xC0
#घोषणा IPR_PATH_NO_INFO		0x00
#घोषणा IPR_PATH_ACTIVE			0x40
#घोषणा IPR_PATH_NOT_ACTIVE		0x80

#घोषणा IPR_PATH_STATE_MASK		0x0F
#घोषणा IPR_PATH_STATE_NO_INFO	0x00
#घोषणा IPR_PATH_HEALTHY		0x01
#घोषणा IPR_PATH_DEGRADED		0x02
#घोषणा IPR_PATH_FAILED			0x03

	__be16 num_entries;
	काष्ठा ipr_hostrcb_config_element elem[1];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb64_fabric_desc अणु
	__be16 length;
	u8 descriptor_id;

	u8 reserved[2];
	u8 path_state;

	u8 reserved2[2];
	u8 res_path[8];
	u8 reserved3[6];
	__be16 num_entries;
	काष्ठा ipr_hostrcb64_config_element elem[1];
पूर्ण__attribute__((packed, aligned (8)));

#घोषणा क्रम_each_hrrq(hrrq, ioa_cfg) \
		क्रम (hrrq = (ioa_cfg)->hrrq; \
			hrrq < ((ioa_cfg)->hrrq + (ioa_cfg)->hrrq_num); hrrq++)

#घोषणा क्रम_each_fabric_cfg(fabric, cfg) \
		क्रम (cfg = (fabric)->elem; \
			cfg < ((fabric)->elem + be16_to_cpu((fabric)->num_entries)); \
			cfg++)

काष्ठा ipr_hostrcb_type_20_error अणु
	u8 failure_reason[64];
	u8 reserved[3];
	u8 num_entries;
	काष्ठा ipr_hostrcb_fabric_desc desc[1];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_30_error अणु
	u8 failure_reason[64];
	u8 reserved[3];
	u8 num_entries;
	काष्ठा ipr_hostrcb64_fabric_desc desc[1];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_type_41_error अणु
	u8 failure_reason[64];
	 __be32 data[200];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb_error अणु
	__be32 fd_ioasc;
	काष्ठा ipr_res_addr fd_res_addr;
	__be32 fd_res_handle;
	__be32 prc;
	जोड़ अणु
		काष्ठा ipr_hostrcb_type_ff_error type_ff_error;
		काष्ठा ipr_hostrcb_type_01_error type_01_error;
		काष्ठा ipr_hostrcb_type_02_error type_02_error;
		काष्ठा ipr_hostrcb_type_03_error type_03_error;
		काष्ठा ipr_hostrcb_type_04_error type_04_error;
		काष्ठा ipr_hostrcb_type_07_error type_07_error;
		काष्ठा ipr_hostrcb_type_12_error type_12_error;
		काष्ठा ipr_hostrcb_type_13_error type_13_error;
		काष्ठा ipr_hostrcb_type_14_error type_14_error;
		काष्ठा ipr_hostrcb_type_17_error type_17_error;
		काष्ठा ipr_hostrcb_type_20_error type_20_error;
	पूर्ण u;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb64_error अणु
	__be32 fd_ioasc;
	__be32 ioa_fw_level;
	__be32 fd_res_handle;
	__be32 prc;
	__be64 fd_dev_id;
	__be64 fd_lun;
	u8 fd_res_path[8];
	__be64 समय_stamp;
	u8 reserved[16];
	जोड़ अणु
		काष्ठा ipr_hostrcb_type_ff_error type_ff_error;
		काष्ठा ipr_hostrcb_type_12_error type_12_error;
		काष्ठा ipr_hostrcb_type_17_error type_17_error;
		काष्ठा ipr_hostrcb_type_21_error type_21_error;
		काष्ठा ipr_hostrcb_type_23_error type_23_error;
		काष्ठा ipr_hostrcb_type_24_error type_24_error;
		काष्ठा ipr_hostrcb_type_30_error type_30_error;
		काष्ठा ipr_hostrcb_type_41_error type_41_error;
	पूर्ण u;
पूर्ण__attribute__((packed, aligned (8)));

काष्ठा ipr_hostrcb_raw अणु
	__be32 data[माप(काष्ठा ipr_hostrcb_error)/माप(__be32)];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hcam अणु
	u8 op_code;
#घोषणा IPR_HOST_RCB_OP_CODE_CONFIG_CHANGE			0xE1
#घोषणा IPR_HOST_RCB_OP_CODE_LOG_DATA				0xE2

	u8 notअगरy_type;
#घोषणा IPR_HOST_RCB_NOTIF_TYPE_EXISTING_CHANGED	0x00
#घोषणा IPR_HOST_RCB_NOTIF_TYPE_NEW_ENTRY			0x01
#घोषणा IPR_HOST_RCB_NOTIF_TYPE_REM_ENTRY			0x02
#घोषणा IPR_HOST_RCB_NOTIF_TYPE_ERROR_LOG_ENTRY		0x10
#घोषणा IPR_HOST_RCB_NOTIF_TYPE_INFORMATION_ENTRY	0x11

	u8 notअगरications_lost;
#घोषणा IPR_HOST_RCB_NO_NOTIFICATIONS_LOST			0
#घोषणा IPR_HOST_RCB_NOTIFICATIONS_LOST				0x80

	u8 flags;
#घोषणा IPR_HOSTRCB_INTERNAL_OPER	0x80
#घोषणा IPR_HOSTRCB_ERR_RESP_SENT	0x40

	u8 overlay_id;
#घोषणा IPR_HOST_RCB_OVERLAY_ID_1				0x01
#घोषणा IPR_HOST_RCB_OVERLAY_ID_2				0x02
#घोषणा IPR_HOST_RCB_OVERLAY_ID_3				0x03
#घोषणा IPR_HOST_RCB_OVERLAY_ID_4				0x04
#घोषणा IPR_HOST_RCB_OVERLAY_ID_6				0x06
#घोषणा IPR_HOST_RCB_OVERLAY_ID_7				0x07
#घोषणा IPR_HOST_RCB_OVERLAY_ID_12				0x12
#घोषणा IPR_HOST_RCB_OVERLAY_ID_13				0x13
#घोषणा IPR_HOST_RCB_OVERLAY_ID_14				0x14
#घोषणा IPR_HOST_RCB_OVERLAY_ID_16				0x16
#घोषणा IPR_HOST_RCB_OVERLAY_ID_17				0x17
#घोषणा IPR_HOST_RCB_OVERLAY_ID_20				0x20
#घोषणा IPR_HOST_RCB_OVERLAY_ID_21				0x21
#घोषणा IPR_HOST_RCB_OVERLAY_ID_23				0x23
#घोषणा IPR_HOST_RCB_OVERLAY_ID_24				0x24
#घोषणा IPR_HOST_RCB_OVERLAY_ID_26				0x26
#घोषणा IPR_HOST_RCB_OVERLAY_ID_30				0x30
#घोषणा IPR_HOST_RCB_OVERLAY_ID_41				0x41
#घोषणा IPR_HOST_RCB_OVERLAY_ID_DEFAULT				0xFF

	u8 reserved1[3];
	__be32 ilid;
	__be32 समय_since_last_ioa_reset;
	__be32 reserved2;
	__be32 length;

	जोड़ अणु
		काष्ठा ipr_hostrcb_error error;
		काष्ठा ipr_hostrcb64_error error64;
		काष्ठा ipr_hostrcb_cfg_ch_not ccn;
		काष्ठा ipr_hostrcb_raw raw;
	पूर्ण u;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_hostrcb अणु
	काष्ठा ipr_hcam hcam;
	dma_addr_t hostrcb_dma;
	काष्ठा list_head queue;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	अक्षर rp_buffer[IPR_MAX_RES_PATH_LENGTH];
पूर्ण;

/* IPR smart dump table काष्ठाures */
काष्ठा ipr_sdt_entry अणु
	__be32 start_token;
	__be32 end_token;
	u8 reserved[4];

	u8 flags;
#घोषणा IPR_SDT_ENDIAN		0x80
#घोषणा IPR_SDT_VALID_ENTRY	0x20

	u8 resv;
	__be16 priority;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_sdt_header अणु
	__be32 state;
	__be32 num_entries;
	__be32 num_entries_used;
	__be32 dump_size;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_sdt अणु
	काष्ठा ipr_sdt_header hdr;
	काष्ठा ipr_sdt_entry entry[IPR_FMT3_NUM_SDT_ENTRIES];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_uc_sdt अणु
	काष्ठा ipr_sdt_header hdr;
	काष्ठा ipr_sdt_entry entry[1];
पूर्ण__attribute__((packed, aligned (4)));

/*
 * Driver types
 */
काष्ठा ipr_bus_attributes अणु
	u8 bus;
	u8 qas_enabled;
	u8 bus_width;
	u8 reserved;
	u32 max_xfer_rate;
पूर्ण;

काष्ठा ipr_sata_port अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा ata_port *ap;
	काष्ठा ipr_resource_entry *res;
	काष्ठा ipr_ioasa_gata ioasa;
पूर्ण;

काष्ठा ipr_resource_entry अणु
	u8 needs_sync_complete:1;
	u8 in_erp:1;
	u8 add_to_ml:1;
	u8 del_from_ml:1;
	u8 resetting_device:1;
	u8 reset_occurred:1;
	u8 raw_mode:1;

	u32 bus;		/* AKA channel */
	u32 target;		/* AKA id */
	u32 lun;
#घोषणा IPR_ARRAY_VIRTUAL_BUS			0x1
#घोषणा IPR_VSET_VIRTUAL_BUS			0x2
#घोषणा IPR_IOAFP_VIRTUAL_BUS			0x3
#घोषणा IPR_MAX_SIS64_BUSES			0x4

#घोषणा IPR_GET_RES_PHYS_LOC(res) \
	(((res)->bus << 24) | ((res)->target << 8) | (res)->lun)

	u8 ata_class;
	u8 type;

	u16 flags;
	u16 res_flags;

	u8 qmodel;
	काष्ठा ipr_std_inq_data std_inq_data;

	__be32 res_handle;
	__be64 dev_id;
	u64 lun_wwn;
	काष्ठा scsi_lun dev_lun;
	u8 res_path[8];

	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा scsi_device *sdev;
	काष्ठा ipr_sata_port *sata_port;
	काष्ठा list_head queue;
पूर्ण; /* काष्ठा ipr_resource_entry */

काष्ठा ipr_resource_hdr अणु
	u16 num_entries;
	u16 reserved;
पूर्ण;

काष्ठा ipr_misc_cbs अणु
	काष्ठा ipr_ioa_vpd ioa_vpd;
	काष्ठा ipr_inquiry_page0 page0_data;
	काष्ठा ipr_inquiry_page3 page3_data;
	काष्ठा ipr_inquiry_cap cap;
	काष्ठा ipr_inquiry_pageC4 pageC4_data;
	काष्ठा ipr_mode_pages mode_pages;
	काष्ठा ipr_supported_device supp_dev;
पूर्ण;

काष्ठा ipr_पूर्णांकerrupt_offsets अणु
	अचिन्हित दीर्घ set_पूर्णांकerrupt_mask_reg;
	अचिन्हित दीर्घ clr_पूर्णांकerrupt_mask_reg;
	अचिन्हित दीर्घ clr_पूर्णांकerrupt_mask_reg32;
	अचिन्हित दीर्घ sense_पूर्णांकerrupt_mask_reg;
	अचिन्हित दीर्घ sense_पूर्णांकerrupt_mask_reg32;
	अचिन्हित दीर्घ clr_पूर्णांकerrupt_reg;
	अचिन्हित दीर्घ clr_पूर्णांकerrupt_reg32;

	अचिन्हित दीर्घ sense_पूर्णांकerrupt_reg;
	अचिन्हित दीर्घ sense_पूर्णांकerrupt_reg32;
	अचिन्हित दीर्घ ioarrin_reg;
	अचिन्हित दीर्घ sense_uproc_पूर्णांकerrupt_reg;
	अचिन्हित दीर्घ sense_uproc_पूर्णांकerrupt_reg32;
	अचिन्हित दीर्घ set_uproc_पूर्णांकerrupt_reg;
	अचिन्हित दीर्घ set_uproc_पूर्णांकerrupt_reg32;
	अचिन्हित दीर्घ clr_uproc_पूर्णांकerrupt_reg;
	अचिन्हित दीर्घ clr_uproc_पूर्णांकerrupt_reg32;

	अचिन्हित दीर्घ init_feedback_reg;

	अचिन्हित दीर्घ dump_addr_reg;
	अचिन्हित दीर्घ dump_data_reg;

#घोषणा IPR_ENDIAN_SWAP_KEY		0x00080800
	अचिन्हित दीर्घ endian_swap_reg;
पूर्ण;

काष्ठा ipr_पूर्णांकerrupts अणु
	व्योम __iomem *set_पूर्णांकerrupt_mask_reg;
	व्योम __iomem *clr_पूर्णांकerrupt_mask_reg;
	व्योम __iomem *clr_पूर्णांकerrupt_mask_reg32;
	व्योम __iomem *sense_पूर्णांकerrupt_mask_reg;
	व्योम __iomem *sense_पूर्णांकerrupt_mask_reg32;
	व्योम __iomem *clr_पूर्णांकerrupt_reg;
	व्योम __iomem *clr_पूर्णांकerrupt_reg32;

	व्योम __iomem *sense_पूर्णांकerrupt_reg;
	व्योम __iomem *sense_पूर्णांकerrupt_reg32;
	व्योम __iomem *ioarrin_reg;
	व्योम __iomem *sense_uproc_पूर्णांकerrupt_reg;
	व्योम __iomem *sense_uproc_पूर्णांकerrupt_reg32;
	व्योम __iomem *set_uproc_पूर्णांकerrupt_reg;
	व्योम __iomem *set_uproc_पूर्णांकerrupt_reg32;
	व्योम __iomem *clr_uproc_पूर्णांकerrupt_reg;
	व्योम __iomem *clr_uproc_पूर्णांकerrupt_reg32;

	व्योम __iomem *init_feedback_reg;

	व्योम __iomem *dump_addr_reg;
	व्योम __iomem *dump_data_reg;

	व्योम __iomem *endian_swap_reg;
पूर्ण;

काष्ठा ipr_chip_cfg_t अणु
	u32 mailbox;
	u16 max_cmds;
	u8 cache_line_size;
	u8 clear_isr;
	u32 iopoll_weight;
	काष्ठा ipr_पूर्णांकerrupt_offsets regs;
पूर्ण;

काष्ठा ipr_chip_t अणु
	u16 venकरोr;
	u16 device;
	bool has_msi;
	u16 sis_type;
#घोषणा IPR_SIS32			0x00
#घोषणा IPR_SIS64			0x01
	u16 bist_method;
#घोषणा IPR_PCI_CFG			0x00
#घोषणा IPR_MMIO			0x01
	स्थिर काष्ठा ipr_chip_cfg_t *cfg;
पूर्ण;

क्रमागत ipr_shutकरोwn_type अणु
	IPR_SHUTDOWN_NORMAL = 0x00,
	IPR_SHUTDOWN_PREPARE_FOR_NORMAL = 0x40,
	IPR_SHUTDOWN_ABBREV = 0x80,
	IPR_SHUTDOWN_NONE = 0x100,
	IPR_SHUTDOWN_QUIESCE = 0x101,
पूर्ण;

काष्ठा ipr_trace_entry अणु
	u32 समय;

	u8 op_code;
	u8 ata_op_code;
	u8 type;
#घोषणा IPR_TRACE_START			0x00
#घोषणा IPR_TRACE_FINISH		0xff
	u8 cmd_index;

	__be32 res_handle;
	जोड़ अणु
		u32 ioasc;
		u32 add_data;
		u32 res_addr;
	पूर्ण u;
पूर्ण;

काष्ठा ipr_sglist अणु
	u32 order;
	u32 num_sg;
	u32 num_dma_sg;
	u32 buffer_len;
	काष्ठा scatterlist *scatterlist;
पूर्ण;

क्रमागत ipr_sdt_state अणु
	INACTIVE,
	WAIT_FOR_DUMP,
	GET_DUMP,
	READ_DUMP,
	ABORT_DUMP,
	DUMP_OBTAINED
पूर्ण;

/* Per-controller data */
काष्ठा ipr_ioa_cfg अणु
	अक्षर eye_catcher[8];
#घोषणा IPR_EYECATCHER			"iprcfg"

	काष्ठा list_head queue;

	u8 in_reset_reload:1;
	u8 in_ioa_bringकरोwn:1;
	u8 ioa_unit_checked:1;
	u8 dump_taken:1;
	u8 scan_enabled:1;
	u8 scan_करोne:1;
	u8 needs_hard_reset:1;
	u8 dual_raid:1;
	u8 needs_warm_reset:1;
	u8 msi_received:1;
	u8 sis64:1;
	u8 dump_समयout:1;
	u8 cfg_locked:1;
	u8 clear_isr:1;
	u8 probe_करोne:1;
	u8 scsi_unblock:1;
	u8 scsi_blocked:1;

	u8 revid;

	/*
	 * Biपंचांगaps क्रम SIS64 generated target values
	 */
	अचिन्हित दीर्घ target_ids[BITS_TO_LONGS(IPR_MAX_SIS64_DEVS)];
	अचिन्हित दीर्घ array_ids[BITS_TO_LONGS(IPR_MAX_SIS64_DEVS)];
	अचिन्हित दीर्घ vset_ids[BITS_TO_LONGS(IPR_MAX_SIS64_DEVS)];

	u16 type; /* CCIN of the card */

	u8 log_level;
#घोषणा IPR_MAX_LOG_LEVEL			4
#घोषणा IPR_DEFAULT_LOG_LEVEL		2
#घोषणा IPR_DEBUG_LOG_LEVEL		3

#घोषणा IPR_NUM_TRACE_INDEX_BITS	8
#घोषणा IPR_NUM_TRACE_ENTRIES		(1 << IPR_NUM_TRACE_INDEX_BITS)
#घोषणा IPR_TRACE_INDEX_MASK		(IPR_NUM_TRACE_ENTRIES - 1)
#घोषणा IPR_TRACE_SIZE	(माप(काष्ठा ipr_trace_entry) * IPR_NUM_TRACE_ENTRIES)
	अक्षर trace_start[8];
#घोषणा IPR_TRACE_START_LABEL			"trace"
	काष्ठा ipr_trace_entry *trace;
	atomic_t trace_index;

	अक्षर cfg_table_start[8];
#घोषणा IPR_CFG_TBL_START		"cfg"
	जोड़ अणु
		काष्ठा ipr_config_table *cfg_table;
		काष्ठा ipr_config_table64 *cfg_table64;
	पूर्ण u;
	dma_addr_t cfg_table_dma;
	u32 cfg_table_size;
	u32 max_devs_supported;

	अक्षर resource_table_label[8];
#घोषणा IPR_RES_TABLE_LABEL		"res_tbl"
	काष्ठा ipr_resource_entry *res_entries;
	काष्ठा list_head मुक्त_res_q;
	काष्ठा list_head used_res_q;

	अक्षर ipr_hcam_label[8];
#घोषणा IPR_HCAM_LABEL			"hcams"
	काष्ठा ipr_hostrcb *hostrcb[IPR_MAX_HCAMS];
	dma_addr_t hostrcb_dma[IPR_MAX_HCAMS];
	काष्ठा list_head hostrcb_मुक्त_q;
	काष्ठा list_head hostrcb_pending_q;
	काष्ठा list_head hostrcb_report_q;

	काष्ठा ipr_hrr_queue hrrq[IPR_MAX_HRRQ_NUM];
	u32 hrrq_num;
	atomic_t  hrrq_index;
	u16 identअगरy_hrrq_index;

	काष्ठा ipr_bus_attributes bus_attr[IPR_MAX_NUM_BUSES];

	अचिन्हित पूर्णांक transop_समयout;
	स्थिर काष्ठा ipr_chip_cfg_t *chip_cfg;
	स्थिर काष्ठा ipr_chip_t *ipr_chip;

	व्योम __iomem *hdw_dma_regs;	/* iomapped PCI memory space */
	अचिन्हित दीर्घ hdw_dma_regs_pci;	/* raw PCI memory space */
	व्योम __iomem *ioa_mailbox;
	काष्ठा ipr_पूर्णांकerrupts regs;

	u16 saved_pcix_cmd_reg;
	u16 reset_retries;

	u32 errors_logged;
	u32 करोorbell;

	काष्ठा Scsi_Host *host;
	काष्ठा pci_dev *pdev;
	काष्ठा ipr_sglist *ucode_sglist;
	u8 saved_mode_page_len;

	काष्ठा work_काष्ठा work_q;
	काष्ठा work_काष्ठा scsi_add_work_q;
	काष्ठा workqueue_काष्ठा *reset_work_q;

	रुको_queue_head_t reset_रुको_q;
	रुको_queue_head_t msi_रुको_q;
	रुको_queue_head_t eeh_रुको_q;

	काष्ठा ipr_dump *dump;
	क्रमागत ipr_sdt_state sdt_state;

	काष्ठा ipr_misc_cbs *vpd_cbs;
	dma_addr_t vpd_cbs_dma;

	काष्ठा dma_pool *ipr_cmd_pool;

	काष्ठा ipr_cmnd *reset_cmd;
	पूर्णांक (*reset) (काष्ठा ipr_cmnd *);

	काष्ठा ata_host ata_host;
	अक्षर ipr_cmd_label[8];
#घोषणा IPR_CMD_LABEL		"ipr_cmd"
	u32 max_cmds;
	काष्ठा ipr_cmnd **ipr_cmnd_list;
	dma_addr_t *ipr_cmnd_list_dma;

	अचिन्हित पूर्णांक nvectors;

	काष्ठा अणु
		अक्षर desc[22];
	पूर्ण vectors_info[IPR_MAX_MSIX_VECTORS];

	u32 iopoll_weight;

पूर्ण; /* काष्ठा ipr_ioa_cfg */

काष्ठा ipr_cmnd अणु
	काष्ठा ipr_ioarcb ioarcb;
	जोड़ अणु
		काष्ठा ipr_ioadl_desc ioadl[IPR_NUM_IOADL_ENTRIES];
		काष्ठा ipr_ioadl64_desc ioadl64[IPR_NUM_IOADL_ENTRIES];
		काष्ठा ipr_ata64_ioadl ata_ioadl;
	पूर्ण i;
	जोड़ अणु
		काष्ठा ipr_ioasa ioasa;
		काष्ठा ipr_ioasa64 ioasa64;
	पूर्ण s;
	काष्ठा list_head queue;
	काष्ठा scsi_cmnd *scsi_cmd;
	काष्ठा ata_queued_cmd *qc;
	काष्ठा completion completion;
	काष्ठा समयr_list समयr;
	काष्ठा work_काष्ठा work;
	व्योम (*fast_करोne) (काष्ठा ipr_cmnd *);
	व्योम (*करोne) (काष्ठा ipr_cmnd *);
	पूर्णांक (*job_step) (काष्ठा ipr_cmnd *);
	पूर्णांक (*job_step_failed) (काष्ठा ipr_cmnd *);
	u16 cmd_index;
	u8 sense_buffer[SCSI_SENSE_BUFFERSIZE];
	dma_addr_t sense_buffer_dma;
	अचिन्हित लघु dma_use_sg;
	dma_addr_t dma_addr;
	काष्ठा ipr_cmnd *sibling;
	जोड़ अणु
		क्रमागत ipr_shutकरोwn_type shutकरोwn_type;
		काष्ठा ipr_hostrcb *hostrcb;
		अचिन्हित दीर्घ समय_left;
		अचिन्हित दीर्घ scratch;
		काष्ठा ipr_resource_entry *res;
		काष्ठा scsi_device *sdev;
	पूर्ण u;

	काष्ठा completion *eh_comp;
	काष्ठा ipr_hrr_queue *hrrq;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
पूर्ण;

काष्ठा ipr_ses_table_entry अणु
	अक्षर product_id[17];
	अक्षर compare_product_id_byte[17];
	u32 max_bus_speed_limit;	/* MB/sec limit क्रम this backplane */
पूर्ण;

काष्ठा ipr_dump_header अणु
	u32 eye_catcher;
#घोषणा IPR_DUMP_EYE_CATCHER		0xC5D4E3F2
	u32 len;
	u32 num_entries;
	u32 first_entry_offset;
	u32 status;
#घोषणा IPR_DUMP_STATUS_SUCCESS			0
#घोषणा IPR_DUMP_STATUS_QUAL_SUCCESS		2
#घोषणा IPR_DUMP_STATUS_FAILED			0xffffffff
	u32 os;
#घोषणा IPR_DUMP_OS_LINUX	0x4C4E5558
	u32 driver_name;
#घोषणा IPR_DUMP_DRIVER_NAME	0x49505232
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_dump_entry_header अणु
	u32 eye_catcher;
#घोषणा IPR_DUMP_EYE_CATCHER		0xC5D4E3F2
	u32 len;
	u32 num_elems;
	u32 offset;
	u32 data_type;
#घोषणा IPR_DUMP_DATA_TYPE_ASCII	0x41534349
#घोषणा IPR_DUMP_DATA_TYPE_BINARY	0x42494E41
	u32 id;
#घोषणा IPR_DUMP_IOA_DUMP_ID		0x494F4131
#घोषणा IPR_DUMP_LOCATION_ID		0x4C4F4341
#घोषणा IPR_DUMP_TRACE_ID		0x54524143
#घोषणा IPR_DUMP_DRIVER_VERSION_ID	0x44525652
#घोषणा IPR_DUMP_DRIVER_TYPE_ID	0x54595045
#घोषणा IPR_DUMP_IOA_CTRL_BLK		0x494F4342
#घोषणा IPR_DUMP_PEND_OPS		0x414F5053
	u32 status;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_dump_location_entry अणु
	काष्ठा ipr_dump_entry_header hdr;
	u8 location[20];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_dump_trace_entry अणु
	काष्ठा ipr_dump_entry_header hdr;
	u32 trace[IPR_TRACE_SIZE / माप(u32)];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_dump_version_entry अणु
	काष्ठा ipr_dump_entry_header hdr;
	u8 version[माप(IPR_DRIVER_VERSION)];
पूर्ण;

काष्ठा ipr_dump_ioa_type_entry अणु
	काष्ठा ipr_dump_entry_header hdr;
	u32 type;
	u32 fw_version;
पूर्ण;

काष्ठा ipr_driver_dump अणु
	काष्ठा ipr_dump_header hdr;
	काष्ठा ipr_dump_version_entry version_entry;
	काष्ठा ipr_dump_location_entry location_entry;
	काष्ठा ipr_dump_ioa_type_entry ioa_type_entry;
	काष्ठा ipr_dump_trace_entry trace_entry;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ioa_dump अणु
	काष्ठा ipr_dump_entry_header hdr;
	काष्ठा ipr_sdt sdt;
	__be32 **ioa_data;
	u32 reserved;
	u32 next_page_index;
	u32 page_offset;
	u32 क्रमmat;
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_dump अणु
	काष्ठा kref kref;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा ipr_driver_dump driver_dump;
	काष्ठा ipr_ioa_dump ioa_dump;
पूर्ण;

काष्ठा ipr_error_table_t अणु
	u32 ioasc;
	पूर्णांक log_ioasa;
	पूर्णांक log_hcam;
	अक्षर *error;
पूर्ण;

काष्ठा ipr_software_inq_lid_info अणु
	__be32 load_id;
	__be32 बारtamp[3];
पूर्ण__attribute__((packed, aligned (4)));

काष्ठा ipr_ucode_image_header अणु
	__be32 header_length;
	__be32 lid_table_offset;
	u8 major_release;
	u8 card_type;
	u8 minor_release[2];
	u8 reserved[20];
	अक्षर eyecatcher[16];
	__be32 num_lids;
	काष्ठा ipr_software_inq_lid_info lid[1];
पूर्ण__attribute__((packed, aligned (4)));

/*
 * Macros
 */
#घोषणा IPR_DBG_CMD(CMD) अगर (ipr_debug) अणु CMD; पूर्ण

#अगर_घोषित CONFIG_SCSI_IPR_TRACE
#घोषणा ipr_create_trace_file(kobj, attr) sysfs_create_bin_file(kobj, attr)
#घोषणा ipr_हटाओ_trace_file(kobj, attr) sysfs_हटाओ_bin_file(kobj, attr)
#अन्यथा
#घोषणा ipr_create_trace_file(kobj, attr) 0
#घोषणा ipr_हटाओ_trace_file(kobj, attr) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCSI_IPR_DUMP
#घोषणा ipr_create_dump_file(kobj, attr) sysfs_create_bin_file(kobj, attr)
#घोषणा ipr_हटाओ_dump_file(kobj, attr) sysfs_हटाओ_bin_file(kobj, attr)
#अन्यथा
#घोषणा ipr_create_dump_file(kobj, attr) 0
#घोषणा ipr_हटाओ_dump_file(kobj, attr) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/*
 * Error logging macros
 */
#घोषणा ipr_err(...) prपूर्णांकk(KERN_ERR IPR_NAME ": "__VA_ARGS__)
#घोषणा ipr_info(...) prपूर्णांकk(KERN_INFO IPR_NAME ": "__VA_ARGS__)
#घोषणा ipr_dbg(...) IPR_DBG_CMD(prपूर्णांकk(KERN_INFO IPR_NAME ": "__VA_ARGS__))

#घोषणा ipr_res_prपूर्णांकk(level, ioa_cfg, bus, target, lun, fmt, ...) \
	prपूर्णांकk(level IPR_NAME ": %d:%d:%d:%d: " fmt, (ioa_cfg)->host->host_no, \
		bus, target, lun, ##__VA_ARGS__)

#घोषणा ipr_res_err(ioa_cfg, res, fmt, ...) \
	ipr_res_prपूर्णांकk(KERN_ERR, ioa_cfg, (res)->bus, (res)->target, (res)->lun, fmt, ##__VA_ARGS__)

#घोषणा ipr_ra_prपूर्णांकk(level, ioa_cfg, ra, fmt, ...) \
	prपूर्णांकk(level IPR_NAME ": %d:%d:%d:%d: " fmt, (ioa_cfg)->host->host_no, \
		(ra).bus, (ra).target, (ra).lun, ##__VA_ARGS__)

#घोषणा ipr_ra_err(ioa_cfg, ra, fmt, ...) \
	ipr_ra_prपूर्णांकk(KERN_ERR, ioa_cfg, ra, fmt, ##__VA_ARGS__)

#घोषणा ipr_phys_res_err(ioa_cfg, res, fmt, ...)			\
अणु									\
	अगर ((res).bus >= IPR_MAX_NUM_BUSES) अणु				\
		ipr_err(fmt": unknown\n", ##__VA_ARGS__);		\
	पूर्ण अन्यथा अणु							\
		ipr_err(fmt": %d:%d:%d:%d\n",				\
			##__VA_ARGS__, (ioa_cfg)->host->host_no,	\
			(res).bus, (res).target, (res).lun);		\
	पूर्ण								\
पूर्ण

#घोषणा ipr_hcam_err(hostrcb, fmt, ...)					\
अणु									\
	अगर (ipr_is_device(hostrcb)) अणु					\
		अगर ((hostrcb)->ioa_cfg->sis64) अणु			\
			prपूर्णांकk(KERN_ERR IPR_NAME ": %s: " fmt, 		\
				ipr_क्रमmat_res_path(hostrcb->ioa_cfg,	\
					hostrcb->hcam.u.error64.fd_res_path, \
					hostrcb->rp_buffer,		\
					माप(hostrcb->rp_buffer)),	\
				__VA_ARGS__);				\
		पूर्ण अन्यथा अणु						\
			ipr_ra_err((hostrcb)->ioa_cfg,			\
				(hostrcb)->hcam.u.error.fd_res_addr,	\
				fmt, __VA_ARGS__);			\
		पूर्ण							\
	पूर्ण अन्यथा अणु							\
		dev_err(&(hostrcb)->ioa_cfg->pdev->dev, fmt, __VA_ARGS__); \
	पूर्ण								\
पूर्ण

#घोषणा ipr_trace ipr_dbg("%s: %s: Line: %d\n",\
	__खाता__, __func__, __LINE__)

#घोषणा ENTER IPR_DBG_CMD(prपूर्णांकk(KERN_INFO IPR_NAME": Entering %s\n", __func__))
#घोषणा LEAVE IPR_DBG_CMD(prपूर्णांकk(KERN_INFO IPR_NAME": Leaving %s\n", __func__))

#घोषणा ipr_err_separator \
ipr_err("----------------------------------------------------------\n")


/*
 * Inlines
 */

/**
 * ipr_is_ioa_resource - Determine अगर a resource is the IOA
 * @res:	resource entry काष्ठा
 *
 * Return value:
 * 	1 अगर IOA / 0 अगर not IOA
 **/
अटल अंतरभूत पूर्णांक ipr_is_ioa_resource(काष्ठा ipr_resource_entry *res)
अणु
	वापस res->type == IPR_RES_TYPE_IOAFP;
पूर्ण

/**
 * ipr_is_af_dasd_device - Determine अगर a resource is an AF DASD
 * @res:	resource entry काष्ठा
 *
 * Return value:
 * 	1 अगर AF DASD / 0 अगर not AF DASD
 **/
अटल अंतरभूत पूर्णांक ipr_is_af_dasd_device(काष्ठा ipr_resource_entry *res)
अणु
	वापस res->type == IPR_RES_TYPE_AF_DASD ||
		res->type == IPR_RES_TYPE_REMOTE_AF_DASD;
पूर्ण

/**
 * ipr_is_vset_device - Determine अगर a resource is a VSET
 * @res:	resource entry काष्ठा
 *
 * Return value:
 * 	1 अगर VSET / 0 अगर not VSET
 **/
अटल अंतरभूत पूर्णांक ipr_is_vset_device(काष्ठा ipr_resource_entry *res)
अणु
	वापस res->type == IPR_RES_TYPE_VOLUME_SET;
पूर्ण

/**
 * ipr_is_gscsi - Determine अगर a resource is a generic scsi resource
 * @res:	resource entry काष्ठा
 *
 * Return value:
 * 	1 अगर GSCSI / 0 अगर not GSCSI
 **/
अटल अंतरभूत पूर्णांक ipr_is_gscsi(काष्ठा ipr_resource_entry *res)
अणु
	वापस res->type == IPR_RES_TYPE_GENERIC_SCSI;
पूर्ण

/**
 * ipr_is_scsi_disk - Determine अगर a resource is a SCSI disk
 * @res:	resource entry काष्ठा
 *
 * Return value:
 * 	1 अगर SCSI disk / 0 अगर not SCSI disk
 **/
अटल अंतरभूत पूर्णांक ipr_is_scsi_disk(काष्ठा ipr_resource_entry *res)
अणु
	अगर (ipr_is_af_dasd_device(res) ||
	    (ipr_is_gscsi(res) && IPR_IS_DASD_DEVICE(res->std_inq_data)))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * ipr_is_gata - Determine अगर a resource is a generic ATA resource
 * @res:	resource entry काष्ठा
 *
 * Return value:
 * 	1 अगर GATA / 0 अगर not GATA
 **/
अटल अंतरभूत पूर्णांक ipr_is_gata(काष्ठा ipr_resource_entry *res)
अणु
	वापस res->type == IPR_RES_TYPE_GENERIC_ATA;
पूर्ण

/**
 * ipr_is_naca_model - Determine अगर a resource is using NACA queueing model
 * @res:	resource entry काष्ठा
 *
 * Return value:
 * 	1 अगर NACA queueing model / 0 अगर not NACA queueing model
 **/
अटल अंतरभूत पूर्णांक ipr_is_naca_model(काष्ठा ipr_resource_entry *res)
अणु
	अगर (ipr_is_gscsi(res) && res->qmodel == IPR_QUEUE_NACA_MODEL)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ipr_is_device - Determine अगर the hostrcb काष्ठाure is related to a device
 * @hostrcb:	host resource control blocks काष्ठा
 *
 * Return value:
 * 	1 अगर AF / 0 अगर not AF
 **/
अटल अंतरभूत पूर्णांक ipr_is_device(काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_res_addr *res_addr;
	u8 *res_path;

	अगर (hostrcb->ioa_cfg->sis64) अणु
		res_path = &hostrcb->hcam.u.error64.fd_res_path[0];
		अगर ((res_path[0] == 0x00 || res_path[0] == 0x80 ||
		    res_path[0] == 0x81) && res_path[2] != 0xFF)
			वापस 1;
	पूर्ण अन्यथा अणु
		res_addr = &hostrcb->hcam.u.error.fd_res_addr;

		अगर ((res_addr->bus < IPR_MAX_NUM_BUSES) &&
		    (res_addr->target < (IPR_MAX_NUM_TARGETS_PER_BUS - 1)))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ipr_sdt_is_fmt2 - Determine अगर a SDT address is in क्रमmat 2
 * @sdt_word:	SDT address
 *
 * Return value:
 * 	1 अगर क्रमmat 2 / 0 अगर not
 **/
अटल अंतरभूत पूर्णांक ipr_sdt_is_fmt2(u32 sdt_word)
अणु
	u32 bar_sel = IPR_GET_FMT2_BAR_SEL(sdt_word);

	चयन (bar_sel) अणु
	हाल IPR_SDT_FMT2_BAR0_SEL:
	हाल IPR_SDT_FMT2_BAR1_SEL:
	हाल IPR_SDT_FMT2_BAR2_SEL:
	हाल IPR_SDT_FMT2_BAR3_SEL:
	हाल IPR_SDT_FMT2_BAR4_SEL:
	हाल IPR_SDT_FMT2_BAR5_SEL:
	हाल IPR_SDT_FMT2_EXP_ROM_SEL:
		वापस 1;
	पूर्ण;

	वापस 0;
पूर्ण

#अगर_अघोषित ग_लिखोq
अटल अंतरभूत व्योम ग_लिखोq(u64 val, व्योम __iomem *addr)
अणु
        ग_लिखोl(((u32) (val >> 32)), addr);
        ग_लिखोl(((u32) (val)), (addr + 4));
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _IPR_H */
