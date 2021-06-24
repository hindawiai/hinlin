<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#अगर_अघोषित __QL4_DEF_H
#घोषणा __QL4_DEF_H

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/mempool.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/aer.h>
#समावेश <linux/bsg-lib.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <net/tcp.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <scsi/scsi_bsg_iscsi.h>
#समावेश <scsi/scsi_netlink.h>
#समावेश <scsi/libiscsi.h>

#समावेश "ql4_dbg.h"
#समावेश "ql4_nx.h"
#समावेश "ql4_fw.h"
#समावेश "ql4_nvram.h"
#समावेश "ql4_83xx.h"

#अगर_अघोषित PCI_DEVICE_ID_QLOGIC_ISP4010
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP4010	0x4010
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_QLOGIC_ISP4022
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP4022	0x4022
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_QLOGIC_ISP4032
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP4032	0x4032
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_QLOGIC_ISP8022
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP8022	0x8022
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_QLOGIC_ISP8324
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP8324	0x8032
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_QLOGIC_ISP8042
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP8042	0x8042
#पूर्ण_अगर

#घोषणा ISP4XXX_PCI_FN_1	0x1
#घोषणा ISP4XXX_PCI_FN_2	0x3

#घोषणा QLA_SUCCESS			0
#घोषणा QLA_ERROR			1
#घोषणा STATUS(status)		status == QLA_ERROR ? "FAILED" : "SUCCEEDED"

/*
 * Data bit definitions
 */
#घोषणा BIT_0	0x1
#घोषणा BIT_1	0x2
#घोषणा BIT_2	0x4
#घोषणा BIT_3	0x8
#घोषणा BIT_4	0x10
#घोषणा BIT_5	0x20
#घोषणा BIT_6	0x40
#घोषणा BIT_7	0x80
#घोषणा BIT_8	0x100
#घोषणा BIT_9	0x200
#घोषणा BIT_10	0x400
#घोषणा BIT_11	0x800
#घोषणा BIT_12	0x1000
#घोषणा BIT_13	0x2000
#घोषणा BIT_14	0x4000
#घोषणा BIT_15	0x8000
#घोषणा BIT_16	0x10000
#घोषणा BIT_17	0x20000
#घोषणा BIT_18	0x40000
#घोषणा BIT_19	0x80000
#घोषणा BIT_20	0x100000
#घोषणा BIT_21	0x200000
#घोषणा BIT_22	0x400000
#घोषणा BIT_23	0x800000
#घोषणा BIT_24	0x1000000
#घोषणा BIT_25	0x2000000
#घोषणा BIT_26	0x4000000
#घोषणा BIT_27	0x8000000
#घोषणा BIT_28	0x10000000
#घोषणा BIT_29	0x20000000
#घोषणा BIT_30	0x40000000
#घोषणा BIT_31	0x80000000

/**
 * Macros to help code, मुख्यtain, etc.
 **/
#घोषणा ql4_prपूर्णांकk(level, ha, क्रमmat, arg...) \
	dev_prपूर्णांकk(level , &((ha)->pdev->dev) , क्रमmat , ## arg)


/*
 * Host adapter शेष definitions
 ***********************************/
#घोषणा MAX_HBAS		16
#घोषणा MAX_BUSES		1
#घोषणा MAX_TARGETS		MAX_DEV_DB_ENTRIES
#घोषणा MAX_LUNS		0xffff
#घोषणा MAX_AEN_ENTRIES		MAX_DEV_DB_ENTRIES
#घोषणा MAX_DDB_ENTRIES		MAX_DEV_DB_ENTRIES
#घोषणा MAX_PDU_ENTRIES		32
#घोषणा INVALID_ENTRY		0xFFFF
#घोषणा MAX_CMDS_TO_RISC	1024
#घोषणा MAX_SRBS		MAX_CMDS_TO_RISC
#घोषणा MBOX_AEN_REG_COUNT	8
#घोषणा MAX_INIT_RETRIES	5

/*
 * Buffer sizes
 */
#घोषणा REQUEST_QUEUE_DEPTH		MAX_CMDS_TO_RISC
#घोषणा RESPONSE_QUEUE_DEPTH		64
#घोषणा QUEUE_SIZE			64
#घोषणा DMA_BUFFER_SIZE			512
#घोषणा IOCB_HIWAT_CUSHION		4

/*
 * Misc
 */
#घोषणा MAC_ADDR_LEN			6	/* in bytes */
#घोषणा IP_ADDR_LEN			4	/* in bytes */
#घोषणा IPv6_ADDR_LEN			16	/* IPv6 address size */
#घोषणा DRIVER_NAME			"qla4xxx"

#घोषणा MAX_LINKED_CMDS_PER_LUN		3
#घोषणा MAX_REQS_SERVICED_PER_INTR	1

#घोषणा ISCSI_IPADDR_SIZE		4	/* IP address size */
#घोषणा ISCSI_ALIAS_SIZE		32	/* ISCSI Alias name size */
#घोषणा ISCSI_NAME_SIZE			0xE0	/* ISCSI Name size */

#घोषणा QL4_SESS_RECOVERY_TMO		120	/* iSCSI session */
						/* recovery समयout */

#घोषणा LSDW(x) ((u32)((u64)(x)))
#घोषणा MSDW(x) ((u32)((((u64)(x)) >> 16) >> 16))

#घोषणा DEV_DB_NON_PERSISTENT	0
#घोषणा DEV_DB_PERSISTENT	1

#घोषणा QL4_ISP_REG_DISCONNECT 0xffffffffU

#घोषणा COPY_ISID(dst_isid, src_isid) अणु			\
	पूर्णांक i, j;					\
	क्रम (i = 0, j = ISID_SIZE - 1; i < ISID_SIZE;)	\
		dst_isid[i++] = src_isid[j--];		\
पूर्ण

#घोषणा SET_BITVAL(o, n, v) अणु	\
	अगर (o)			\
		n |= v;		\
	अन्यथा			\
		n &= ~v;	\
पूर्ण

#घोषणा OP_STATE(o, f, p) अणु			\
	p = (o & f) ? "enable" : "disable";	\
पूर्ण

/*
 * Retry & Timeout Values
 */
#घोषणा MBOX_TOV			60
#घोषणा SOFT_RESET_TOV			30
#घोषणा RESET_INTR_TOV			3
#घोषणा SEMAPHORE_TOV			10
#घोषणा ADAPTER_INIT_TOV		30
#घोषणा ADAPTER_RESET_TOV		180
#घोषणा EXTEND_CMD_TOV			60
#घोषणा WAIT_CMD_TOV			5
#घोषणा EH_WAIT_CMD_TOV			120
#घोषणा FIRMWARE_UP_TOV			60
#घोषणा RESET_FIRMWARE_TOV		30
#घोषणा LOGOUT_TOV			10
#घोषणा IOCB_TOV_MARGIN			10
#घोषणा RELOGIN_TOV			18
#घोषणा ISNS_DEREG_TOV			5
#घोषणा HBA_ONLINE_TOV			30
#घोषणा DISABLE_ACB_TOV			30
#घोषणा IP_CONFIG_TOV			30
#घोषणा LOGIN_TOV			12
#घोषणा BOOT_LOGIN_RESP_TOV		60

#घोषणा MAX_RESET_HA_RETRIES		2
#घोषणा FW_ALIVE_WAIT_TOV		3
#घोषणा IDC_EXTEND_TOV			8
#घोषणा IDC_COMP_TOV			5
#घोषणा LINK_UP_COMP_TOV		30

#घोषणा CMD_SP(Cmnd)			((Cmnd)->SCp.ptr)

/*
 * SCSI Request Block काष्ठाure	 (srb)	that is placed
 * on cmd->SCp location of every I/O	 [We have 22 bytes available]
 */
काष्ठा srb अणु
	काष्ठा list_head list;	/* (8)	 */
	काष्ठा scsi_qla_host *ha;	/* HA the SP is queued on */
	काष्ठा ddb_entry *ddb;
	uपूर्णांक16_t flags;		/* (1) Status flags. */

#घोषणा SRB_DMA_VALID		BIT_3	/* DMA Buffer mapped. */
#घोषणा SRB_GOT_SENSE		BIT_4	/* sense data received. */
	uपूर्णांक8_t state;		/* (1) Status flags. */

#घोषणा SRB_NO_QUEUE_STATE	 0	/* Request is in between states */
#घोषणा SRB_FREE_STATE		 1
#घोषणा SRB_ACTIVE_STATE	 3
#घोषणा SRB_ACTIVE_TIMEOUT_STATE 4
#घोषणा SRB_SUSPENDED_STATE	 7	/* Request in suspended state */

	काष्ठा scsi_cmnd *cmd;	/* (4) SCSI command block */
	dma_addr_t dma_handle;	/* (4) क्रम unmap of single transfers */
	काष्ठा kref srb_ref;	/* reference count क्रम this srb */
	uपूर्णांक8_t err_id;		/* error id */
#घोषणा SRB_ERR_PORT	   1	/* Request failed because "port down" */
#घोषणा SRB_ERR_LOOP	   2	/* Request failed because "loop down" */
#घोषणा SRB_ERR_DEVICE	   3	/* Request failed because "device error" */
#घोषणा SRB_ERR_OTHER	   4

	uपूर्णांक16_t reserved;
	uपूर्णांक16_t iocb_tov;
	uपूर्णांक16_t iocb_cnt;	/* Number of used iocbs */
	uपूर्णांक16_t cc_stat;

	/* Used क्रम extended sense / status continuation */
	uपूर्णांक8_t *req_sense_ptr;
	uपूर्णांक16_t req_sense_len;
	uपूर्णांक16_t reserved2;
पूर्ण;

/* Mailbox request block काष्ठाure */
काष्ठा mrb अणु
	काष्ठा scsi_qla_host *ha;
	काष्ठा mbox_cmd_iocb *mbox;
	uपूर्णांक32_t mbox_cmd;
	uपूर्णांक16_t iocb_cnt;		/* Number of used iocbs */
	uपूर्णांक32_t pid;
पूर्ण;

/*
 * Asynchronous Event Queue काष्ठाure
 */
काष्ठा aen अणु
        uपूर्णांक32_t mbox_sts[MBOX_AEN_REG_COUNT];
पूर्ण;

काष्ठा ql4_aen_log अणु
        पूर्णांक count;
        काष्ठा aen entry[MAX_AEN_ENTRIES];
पूर्ण;

/*
 * Device Database (DDB) काष्ठाure
 */
काष्ठा ddb_entry अणु
	काष्ठा scsi_qla_host *ha;
	काष्ठा iscsi_cls_session *sess;
	काष्ठा iscsi_cls_conn *conn;

	uपूर्णांक16_t fw_ddb_index;	/* DDB firmware index */
	uपूर्णांक32_t fw_ddb_device_state; /* F/W Device State  -- see ql4_fw.h */
	uपूर्णांक16_t ddb_type;
#घोषणा FLASH_DDB 0x01

	काष्ठा dev_db_entry fw_ddb_entry;
	पूर्णांक (*unblock_sess)(काष्ठा iscsi_cls_session *cls_session);
	पूर्णांक (*ddb_change)(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index,
			  काष्ठा ddb_entry *ddb_entry, uपूर्णांक32_t state);

	/* Driver Re-login  */
	अचिन्हित दीर्घ flags;		  /* DDB Flags */
#घोषणा DDB_CONN_CLOSE_FAILURE		0 /* 0x00000001 */

	uपूर्णांक16_t शेष_relogin_समयout; /*  Max समय to रुको क्रम
					   *  relogin to complete */
	atomic_t retry_relogin_समयr;	  /* Min Time between relogins
					   * (4000 only) */
	atomic_t relogin_समयr;		  /* Max Time to रुको क्रम
					   * relogin to complete */
	atomic_t relogin_retry_count;	  /* Num of बार relogin has been
					   * retried */
	uपूर्णांक32_t शेष_समय2रुको;	  /* Default Min समय between
					   * relogins (+aens) */
	uपूर्णांक16_t chap_tbl_idx;
पूर्ण;

काष्ठा qla_ddb_index अणु
	काष्ठा list_head list;
	uपूर्णांक16_t fw_ddb_idx;
	uपूर्णांक16_t flash_ddb_idx;
	काष्ठा dev_db_entry fw_ddb;
	uपूर्णांक8_t flash_isid[6];
पूर्ण;

#घोषणा DDB_IPADDR_LEN 64

काष्ठा ql4_tuple_ddb अणु
	पूर्णांक port;
	पूर्णांक tpgt;
	अक्षर ip_addr[DDB_IPADDR_LEN];
	अक्षर iscsi_name[ISCSI_NAME_SIZE];
	uपूर्णांक16_t options;
#घोषणा DDB_OPT_IPV6 0x0e0e
#घोषणा DDB_OPT_IPV4 0x0f0f
	uपूर्णांक8_t isid[6];
पूर्ण;

/*
 * DDB states.
 */
#घोषणा DDB_STATE_DEAD		0	/* We can no दीर्घer talk to
					 * this device */
#घोषणा DDB_STATE_ONLINE	1	/* Device पढ़ोy to accept
					 * commands */
#घोषणा DDB_STATE_MISSING	2	/* Device logged off, trying
					 * to re-login */

/*
 * DDB flags.
 */
#घोषणा DF_RELOGIN		0	/* Relogin to device */
#घोषणा DF_BOOT_TGT		1	/* Boot target entry */
#घोषणा DF_ISNS_DISCOVERED	2	/* Device was discovered via iSNS */
#घोषणा DF_FO_MASKED		3
#घोषणा DF_DISABLE_RELOGIN		4	/* Disable relogin to device */

क्रमागत qla4_work_type अणु
	QLA4_EVENT_AEN,
	QLA4_EVENT_PING_STATUS,
पूर्ण;

काष्ठा qla4_work_evt अणु
	काष्ठा list_head list;
	क्रमागत qla4_work_type type;
	जोड़ अणु
		काष्ठा अणु
			क्रमागत iscsi_host_event_code code;
			uपूर्णांक32_t data_size;
			uपूर्णांक8_t data[0];
		पूर्ण aen;
		काष्ठा अणु
			uपूर्णांक32_t status;
			uपूर्णांक32_t pid;
			uपूर्णांक32_t data_size;
			uपूर्णांक8_t data[0];
		पूर्ण ping;
	पूर्ण u;
पूर्ण;

काष्ठा ql82xx_hw_data अणु
	/* Offsets क्रम flash/nvram access (set to ~0 अगर not used). */
	uपूर्णांक32_t flash_conf_off;
	uपूर्णांक32_t flash_data_off;

	uपूर्णांक32_t fdt_wrt_disable;
	uपूर्णांक32_t fdt_erase_cmd;
	uपूर्णांक32_t fdt_block_size;
	uपूर्णांक32_t fdt_unprotect_sec_cmd;
	uपूर्णांक32_t fdt_protect_sec_cmd;

	uपूर्णांक32_t flt_region_flt;
	uपूर्णांक32_t flt_region_fdt;
	uपूर्णांक32_t flt_region_boot;
	uपूर्णांक32_t flt_region_bootload;
	uपूर्णांक32_t flt_region_fw;

	uपूर्णांक32_t flt_iscsi_param;
	uपूर्णांक32_t flt_region_chap;
	uपूर्णांक32_t flt_chap_size;
	uपूर्णांक32_t flt_region_ddb;
	uपूर्णांक32_t flt_ddb_size;
पूर्ण;

काष्ठा qla4_8xxx_legacy_पूर्णांकr_set अणु
	uपूर्णांक32_t पूर्णांक_vec_bit;
	uपूर्णांक32_t tgt_status_reg;
	uपूर्णांक32_t tgt_mask_reg;
	uपूर्णांक32_t pci_पूर्णांक_reg;
पूर्ण;

/* MSI-X Support */
#घोषणा QLA_MSIX_ENTRIES	2

/*
 * ISP Operations
 */
काष्ठा isp_operations अणु
	पूर्णांक (*iospace_config) (काष्ठा scsi_qla_host *ha);
	व्योम (*pci_config) (काष्ठा scsi_qla_host *);
	व्योम (*disable_पूर्णांकrs) (काष्ठा scsi_qla_host *);
	व्योम (*enable_पूर्णांकrs) (काष्ठा scsi_qla_host *);
	पूर्णांक (*start_firmware) (काष्ठा scsi_qla_host *);
	पूर्णांक (*restart_firmware) (काष्ठा scsi_qla_host *);
	irqवापस_t (*पूर्णांकr_handler) (पूर्णांक , व्योम *);
	व्योम (*पूर्णांकerrupt_service_routine) (काष्ठा scsi_qla_host *, uपूर्णांक32_t);
	पूर्णांक (*need_reset) (काष्ठा scsi_qla_host *);
	पूर्णांक (*reset_chip) (काष्ठा scsi_qla_host *);
	पूर्णांक (*reset_firmware) (काष्ठा scsi_qla_host *);
	व्योम (*queue_iocb) (काष्ठा scsi_qla_host *);
	व्योम (*complete_iocb) (काष्ठा scsi_qla_host *);
	uपूर्णांक16_t (*rd_shdw_req_q_out) (काष्ठा scsi_qla_host *);
	uपूर्णांक16_t (*rd_shdw_rsp_q_in) (काष्ठा scsi_qla_host *);
	पूर्णांक (*get_sys_info) (काष्ठा scsi_qla_host *);
	uपूर्णांक32_t (*rd_reg_direct) (काष्ठा scsi_qla_host *, uदीर्घ);
	व्योम (*wr_reg_direct) (काष्ठा scsi_qla_host *, uदीर्घ, uपूर्णांक32_t);
	पूर्णांक (*rd_reg_indirect) (काष्ठा scsi_qla_host *, uपूर्णांक32_t, uपूर्णांक32_t *);
	पूर्णांक (*wr_reg_indirect) (काष्ठा scsi_qla_host *, uपूर्णांक32_t, uपूर्णांक32_t);
	पूर्णांक (*idc_lock) (काष्ठा scsi_qla_host *); /* Context: task, can sleep */
	व्योम (*idc_unlock) (काष्ठा scsi_qla_host *);
	व्योम (*rom_lock_recovery) (काष्ठा scsi_qla_host *); /* Context: task, can sleep */
	व्योम (*queue_mailbox_command) (काष्ठा scsi_qla_host *, uपूर्णांक32_t *, पूर्णांक);
	व्योम (*process_mailbox_पूर्णांकerrupt) (काष्ठा scsi_qla_host *, पूर्णांक);
पूर्ण;

काष्ठा ql4_mdump_माप_प्रकारable अणु
	uपूर्णांक32_t size;
	uपूर्णांक32_t size_cmask_02;
	uपूर्णांक32_t size_cmask_04;
	uपूर्णांक32_t size_cmask_08;
	uपूर्णांक32_t size_cmask_10;
	uपूर्णांक32_t size_cmask_FF;
	uपूर्णांक32_t version;
पूर्ण;

/*qla4xxx ipaddress configuration details */
काष्ठा ipaddress_config अणु
	uपूर्णांक16_t ipv4_options;
	uपूर्णांक16_t tcp_options;
	uपूर्णांक16_t ipv4_vlan_tag;
	uपूर्णांक8_t ipv4_addr_state;
	uपूर्णांक8_t ip_address[IP_ADDR_LEN];
	uपूर्णांक8_t subnet_mask[IP_ADDR_LEN];
	uपूर्णांक8_t gateway[IP_ADDR_LEN];
	uपूर्णांक32_t ipv6_options;
	uपूर्णांक32_t ipv6_addl_options;
	uपूर्णांक8_t ipv6_link_local_state;
	uपूर्णांक8_t ipv6_addr0_state;
	uपूर्णांक8_t ipv6_addr1_state;
	uपूर्णांक8_t ipv6_शेष_router_state;
	uपूर्णांक16_t ipv6_vlan_tag;
	काष्ठा in6_addr ipv6_link_local_addr;
	काष्ठा in6_addr ipv6_addr0;
	काष्ठा in6_addr ipv6_addr1;
	काष्ठा in6_addr ipv6_शेष_router_addr;
	uपूर्णांक16_t eth_mtu_size;
	uपूर्णांक16_t ipv4_port;
	uपूर्णांक16_t ipv6_port;
	uपूर्णांक8_t control;
	uपूर्णांक16_t ipv6_tcp_options;
	uपूर्णांक8_t tcp_wsf;
	uपूर्णांक8_t ipv6_tcp_wsf;
	uपूर्णांक8_t ipv4_tos;
	uपूर्णांक8_t ipv4_cache_id;
	uपूर्णांक8_t ipv6_cache_id;
	uपूर्णांक8_t ipv4_alt_cid_len;
	uपूर्णांक8_t ipv4_alt_cid[11];
	uपूर्णांक8_t ipv4_vid_len;
	uपूर्णांक8_t ipv4_vid[11];
	uपूर्णांक8_t ipv4_ttl;
	uपूर्णांक16_t ipv6_flow_lbl;
	uपूर्णांक8_t ipv6_traffic_class;
	uपूर्णांक8_t ipv6_hop_limit;
	uपूर्णांक32_t ipv6_nd_reach_समय;
	uपूर्णांक32_t ipv6_nd_rexmit_समयr;
	uपूर्णांक32_t ipv6_nd_stale_समयout;
	uपूर्णांक8_t ipv6_dup_addr_detect_count;
	uपूर्णांक32_t ipv6_gw_advrt_mtu;
	uपूर्णांक16_t def_समयout;
	uपूर्णांक8_t पात_समयr;
	uपूर्णांक16_t iscsi_options;
	uपूर्णांक16_t iscsi_max_pdu_size;
	uपूर्णांक16_t iscsi_first_burst_len;
	uपूर्णांक16_t iscsi_max_outstnd_r2t;
	uपूर्णांक16_t iscsi_max_burst_len;
	uपूर्णांक8_t iscsi_name[224];
पूर्ण;

#घोषणा QL4_CHAP_MAX_NAME_LEN 256
#घोषणा QL4_CHAP_MAX_SECRET_LEN 100
#घोषणा LOCAL_CHAP	0
#घोषणा BIDI_CHAP	1

काष्ठा ql4_chap_क्रमmat अणु
	u8  पूर्णांकr_chap_name[QL4_CHAP_MAX_NAME_LEN];
	u8  पूर्णांकr_secret[QL4_CHAP_MAX_SECRET_LEN];
	u8  target_chap_name[QL4_CHAP_MAX_NAME_LEN];
	u8  target_secret[QL4_CHAP_MAX_SECRET_LEN];
	u16 पूर्णांकr_chap_name_length;
	u16 पूर्णांकr_secret_length;
	u16 target_chap_name_length;
	u16 target_secret_length;
पूर्ण;

काष्ठा ip_address_क्रमmat अणु
	u8 ip_type;
	u8 ip_address[16];
पूर्ण;

काष्ठा	ql4_conn_info अणु
	u16	dest_port;
	काष्ठा	ip_address_क्रमmat dest_ipaddr;
	काष्ठा	ql4_chap_क्रमmat chap;
पूर्ण;

काष्ठा ql4_boot_session_info अणु
	u8	target_name[224];
	काष्ठा	ql4_conn_info conn_list[1];
पूर्ण;

काष्ठा ql4_boot_tgt_info अणु
	काष्ठा ql4_boot_session_info boot_pri_sess;
	काष्ठा ql4_boot_session_info boot_sec_sess;
पूर्ण;

/*
 * Linux Host Adapter काष्ठाure
 */
काष्ठा scsi_qla_host अणु
	/* Linux adapter configuration data */
	अचिन्हित दीर्घ flags;

#घोषणा AF_ONLINE			0 /* 0x00000001 */
#घोषणा AF_INIT_DONE			1 /* 0x00000002 */
#घोषणा AF_MBOX_COMMAND			2 /* 0x00000004 */
#घोषणा AF_MBOX_COMMAND_DONE		3 /* 0x00000008 */
#घोषणा AF_ST_DISCOVERY_IN_PROGRESS	4 /* 0x00000010 */
#घोषणा AF_INTERRUPTS_ON		6 /* 0x00000040 */
#घोषणा AF_GET_CRASH_RECORD		7 /* 0x00000080 */
#घोषणा AF_LINK_UP			8 /* 0x00000100 */
#घोषणा AF_LOOPBACK			9 /* 0x00000200 */
#घोषणा AF_IRQ_ATTACHED			10 /* 0x00000400 */
#घोषणा AF_DISABLE_ACB_COMPLETE		11 /* 0x00000800 */
#घोषणा AF_HA_REMOVAL			12 /* 0x00001000 */
#घोषणा AF_MBOX_COMMAND_NOPOLL		18 /* 0x00040000 */
#घोषणा AF_FW_RECOVERY			19 /* 0x00080000 */
#घोषणा AF_EEH_BUSY			20 /* 0x00100000 */
#घोषणा AF_PCI_CHANNEL_IO_PERM_FAILURE	21 /* 0x00200000 */
#घोषणा AF_BUILD_DDB_LIST		22 /* 0x00400000 */
#घोषणा AF_82XX_FW_DUMPED		24 /* 0x01000000 */
#घोषणा AF_8XXX_RST_OWNER		25 /* 0x02000000 */
#घोषणा AF_82XX_DUMP_READING		26 /* 0x04000000 */
#घोषणा AF_83XX_IOCB_INTR_ON		28 /* 0x10000000 */
#घोषणा AF_83XX_MBOX_INTR_ON		29 /* 0x20000000 */

	अचिन्हित दीर्घ dpc_flags;

#घोषणा DPC_RESET_HA			1 /* 0x00000002 */
#घोषणा DPC_RETRY_RESET_HA		2 /* 0x00000004 */
#घोषणा DPC_RELOGIN_DEVICE		3 /* 0x00000008 */
#घोषणा DPC_RESET_HA_FW_CONTEXT		4 /* 0x00000010 */
#घोषणा DPC_RESET_HA_INTR		5 /* 0x00000020 */
#घोषणा DPC_ISNS_RESTART		7 /* 0x00000080 */
#घोषणा DPC_AEN				9 /* 0x00000200 */
#घोषणा DPC_GET_DHCP_IP_ADDR		15 /* 0x00008000 */
#घोषणा DPC_LINK_CHANGED		18 /* 0x00040000 */
#घोषणा DPC_RESET_ACTIVE		20 /* 0x00100000 */
#घोषणा DPC_HA_UNRECOVERABLE		21 /* 0x00200000 ISP-82xx only*/
#घोषणा DPC_HA_NEED_QUIESCENT		22 /* 0x00400000 ISP-82xx only*/
#घोषणा DPC_POST_IDC_ACK		23 /* 0x00800000 */
#घोषणा DPC_RESTORE_ACB			24 /* 0x01000000 */
#घोषणा DPC_SYSFS_DDB_EXPORT		25 /* 0x02000000 */

	काष्ठा Scsi_Host *host; /* poपूर्णांकer to host data */
	uपूर्णांक32_t tot_ddbs;

	uपूर्णांक16_t iocb_cnt;
	uपूर्णांक16_t iocb_hiwat;

	/* SRB cache. */
#घोषणा SRB_MIN_REQ	128
	mempool_t *srb_mempool;

	/* pci inक्रमmation */
	काष्ठा pci_dev *pdev;

	काष्ठा isp_reg __iomem *reg; /* Base I/O address */
	अचिन्हित दीर्घ pio_address;
	अचिन्हित दीर्घ pio_length;
#घोषणा MIN_IOBASE_LEN		0x100

	uपूर्णांक16_t req_q_count;

	अचिन्हित दीर्घ host_no;

	/* NVRAM रेजिस्टरs */
	काष्ठा eeprom_data *nvram;
	spinlock_t hardware_lock ____cacheline_aligned;
	uपूर्णांक32_t eeprom_cmd_data;

	/* Counters क्रम general statistics */
	uपूर्णांक64_t isr_count;
	uपूर्णांक64_t adapter_error_count;
	uपूर्णांक64_t device_error_count;
	uपूर्णांक64_t total_io_count;
	uपूर्णांक64_t total_mbytes_xferred;
	uपूर्णांक64_t link_failure_count;
	uपूर्णांक64_t invalid_crc_count;
	uपूर्णांक32_t bytes_xfered;
	uपूर्णांक32_t spurious_पूर्णांक_count;
	uपूर्णांक32_t पातed_io_count;
	uपूर्णांक32_t io_समयout_count;
	uपूर्णांक32_t mailbox_समयout_count;
	uपूर्णांक32_t seconds_since_last_पूर्णांकr;
	uपूर्णांक32_t seconds_since_last_heartbeat;
	uपूर्णांक32_t mac_index;

	/* Info Needed क्रम Management App */
	/* --- From GetFwVersion --- */
	uपूर्णांक32_t firmware_version[2];
	uपूर्णांक32_t patch_number;
	uपूर्णांक32_t build_number;
	uपूर्णांक32_t board_id;

	/* --- From Init_FW --- */
	/* init_cb_t *init_cb; */
	uपूर्णांक16_t firmware_options;
	uपूर्णांक8_t alias[32];
	uपूर्णांक8_t name_string[256];
	uपूर्णांक8_t heartbeat_पूर्णांकerval;

	/* --- From FlashSysInfo --- */
	uपूर्णांक8_t my_mac[MAC_ADDR_LEN];
	uपूर्णांक8_t serial_number[16];
	uपूर्णांक16_t port_num;
	/* --- From GetFwState --- */
	uपूर्णांक32_t firmware_state;
	uपूर्णांक32_t addl_fw_state;

	/* Linux kernel thपढ़ो */
	काष्ठा workqueue_काष्ठा *dpc_thपढ़ो;
	काष्ठा work_काष्ठा dpc_work;

	/* Linux समयr thपढ़ो */
	काष्ठा समयr_list समयr;
	uपूर्णांक32_t समयr_active;

	/* Recovery Timers */
	atomic_t check_relogin_समयouts;
	uपूर्णांक32_t retry_reset_ha_cnt;
	uपूर्णांक32_t isp_reset_समयr;	/* reset test समयr */
	uपूर्णांक32_t nic_reset_समयr;	/* simulated nic reset test समयr */
	पूर्णांक eh_start;
	काष्ठा list_head मुक्त_srb_q;
	uपूर्णांक16_t मुक्त_srb_q_count;
	uपूर्णांक16_t num_srbs_allocated;

	/* DMA Memory Block */
	व्योम *queues;
	dma_addr_t queues_dma;
	अचिन्हित दीर्घ queues_len;

#घोषणा MEM_ALIGN_VALUE \
	    ((max(REQUEST_QUEUE_DEPTH, RESPONSE_QUEUE_DEPTH)) * \
	     माप(काष्ठा queue_entry))
	/* request and response queue variables */
	dma_addr_t request_dma;
	काष्ठा queue_entry *request_ring;
	काष्ठा queue_entry *request_ptr;
	dma_addr_t response_dma;
	काष्ठा queue_entry *response_ring;
	काष्ठा queue_entry *response_ptr;
	dma_addr_t shaकरोw_regs_dma;
	काष्ठा shaकरोw_regs *shaकरोw_regs;
	uपूर्णांक16_t request_in;	/* Current indexes. */
	uपूर्णांक16_t request_out;
	uपूर्णांक16_t response_in;
	uपूर्णांक16_t response_out;

	/* aen queue variables */
	uपूर्णांक16_t aen_q_count;	/* Number of available aen_q entries */
	uपूर्णांक16_t aen_in;	/* Current indexes */
	uपूर्णांक16_t aen_out;
	काष्ठा aen aen_q[MAX_AEN_ENTRIES];

	काष्ठा ql4_aen_log aen_log;/* tracks all aens */

	/* This mutex protects several thपढ़ोs to करो mailbox commands
	 * concurrently.
	 */
	काष्ठा mutex  mbox_sem;

	/* temporary mailbox status रेजिस्टरs */
	अस्थिर uपूर्णांक8_t mbox_status_count;
	अस्थिर uपूर्णांक32_t mbox_status[MBOX_REG_COUNT];

	/* FW ddb index map */
	काष्ठा ddb_entry *fw_ddb_index_map[MAX_DDB_ENTRIES];

	/* Saved srb क्रम status continuation entry processing */
	काष्ठा srb *status_srb;

	uपूर्णांक8_t acb_version;

	/* qla82xx specअगरic fields */
	काष्ठा device_reg_82xx  __iomem *qla4_82xx_reg; /* Base I/O address */
	अचिन्हित दीर्घ nx_pcibase;	/* Base I/O address */
	uपूर्णांक8_t *nx_db_rd_ptr;		/* Doorbell पढ़ो poपूर्णांकer */
	अचिन्हित दीर्घ nx_db_wr_ptr;	/* Door bell ग_लिखो poपूर्णांकer */
	अचिन्हित दीर्घ first_page_group_start;
	अचिन्हित दीर्घ first_page_group_end;

	uपूर्णांक32_t crb_win;
	uपूर्णांक32_t curr_winकरोw;
	uपूर्णांक32_t ddr_mn_winकरोw;
	अचिन्हित दीर्घ mn_win_crb;
	अचिन्हित दीर्घ ms_win_crb;
	पूर्णांक qdr_sn_winकरोw;
	rwlock_t hw_lock;
	uपूर्णांक16_t func_num;
	पूर्णांक link_width;

	काष्ठा qla4_8xxx_legacy_पूर्णांकr_set nx_legacy_पूर्णांकr;
	u32 nx_crb_mask;

	uपूर्णांक8_t revision_id;
	uपूर्णांक32_t fw_heartbeat_counter;

	काष्ठा isp_operations *isp_ops;
	काष्ठा ql82xx_hw_data hw;

	uपूर्णांक32_t nx_dev_init_समयout;
	uपूर्णांक32_t nx_reset_समयout;
	व्योम *fw_dump;
	uपूर्णांक32_t fw_dump_size;
	uपूर्णांक32_t fw_dump_capture_mask;
	व्योम *fw_dump_पंचांगplt_hdr;
	uपूर्णांक32_t fw_dump_पंचांगplt_size;
	uपूर्णांक32_t fw_dump_skip_size;

	काष्ठा completion mbx_पूर्णांकr_comp;

	काष्ठा ipaddress_config ip_config;
	काष्ठा iscsi_अगरace *अगरace_ipv4;
	काष्ठा iscsi_अगरace *अगरace_ipv6_0;
	काष्ठा iscsi_अगरace *अगरace_ipv6_1;

	/* --- From About Firmware --- */
	काष्ठा about_fw_info fw_info;
	uपूर्णांक32_t fw_upसमय_secs;  /* seconds elapsed since fw bootup */
	uपूर्णांक32_t fw_upसमय_msecs; /* milliseconds beyond elapsed seconds */
	uपूर्णांक16_t def_समयout; /* Default login समयout */

	uपूर्णांक32_t flash_state;
#घोषणा	QLFLASH_WAITING		0
#घोषणा	QLFLASH_READING		1
#घोषणा	QLFLASH_WRITING		2
	काष्ठा dma_pool *chap_dma_pool;
	uपूर्णांक8_t *chap_list; /* CHAP table cache */
	काष्ठा mutex  chap_sem;

#घोषणा CHAP_DMA_BLOCK_SIZE    512
	काष्ठा workqueue_काष्ठा *task_wq;
	अचिन्हित दीर्घ ddb_idx_map[MAX_DDB_ENTRIES / BITS_PER_LONG];
#घोषणा SYSFS_FLAG_FW_SEL_BOOT 2
	काष्ठा iscsi_boot_kset *boot_kset;
	काष्ठा ql4_boot_tgt_info boot_tgt;
	uपूर्णांक16_t phy_port_num;
	uपूर्णांक16_t phy_port_cnt;
	uपूर्णांक16_t iscsi_pci_func_cnt;
	uपूर्णांक8_t model_name[16];
	काष्ठा completion disable_acb_comp;
	काष्ठा dma_pool *fw_ddb_dma_pool;
#घोषणा DDB_DMA_BLOCK_SIZE 512
	uपूर्णांक16_t pri_ddb_idx;
	uपूर्णांक16_t sec_ddb_idx;
	पूर्णांक is_reset;
	uपूर्णांक16_t temperature;

	/* event work list */
	काष्ठा list_head work_list;
	spinlock_t work_lock;

	/* mbox iocb */
#घोषणा MAX_MRB		128
	काष्ठा mrb *active_mrb_array[MAX_MRB];
	uपूर्णांक32_t mrb_index;

	uपूर्णांक32_t *reg_tbl;
	काष्ठा qla4_83xx_reset_ढाँचा reset_पंचांगplt;
	काष्ठा device_reg_83xx  __iomem *qla4_83xx_reg; /* Base I/O address
							   क्रम ISP8324 and
							   and ISP8042 */
	uपूर्णांक32_t pf_bit;
	काष्ठा qla4_83xx_idc_inक्रमmation idc_info;
	काष्ठा addr_ctrl_blk *saved_acb;
	पूर्णांक notअगरy_idc_comp;
	पूर्णांक notअगरy_link_up_comp;
	पूर्णांक idc_extend_पंचांगo;
	काष्ठा completion idc_comp;
	काष्ठा completion link_up_comp;
पूर्ण;

काष्ठा ql4_task_data अणु
	काष्ठा scsi_qla_host *ha;
	uपूर्णांक8_t iocb_req_cnt;
	dma_addr_t data_dma;
	व्योम *req_buffer;
	dma_addr_t req_dma;
	uपूर्णांक32_t req_len;
	व्योम *resp_buffer;
	dma_addr_t resp_dma;
	uपूर्णांक32_t resp_len;
	काष्ठा iscsi_task *task;
	काष्ठा passthru_status sts;
	काष्ठा work_काष्ठा task_work;
पूर्ण;

काष्ठा qla_endpoपूर्णांक अणु
	काष्ठा Scsi_Host *host;
	काष्ठा sockaddr_storage dst_addr;
पूर्ण;

काष्ठा qla_conn अणु
	काष्ठा qla_endpoपूर्णांक *qla_ep;
पूर्ण;

अटल अंतरभूत पूर्णांक is_ipv4_enabled(काष्ठा scsi_qla_host *ha)
अणु
	वापस ((ha->ip_config.ipv4_options & IPOPT_IPV4_PROTOCOL_ENABLE) != 0);
पूर्ण

अटल अंतरभूत पूर्णांक is_ipv6_enabled(काष्ठा scsi_qla_host *ha)
अणु
	वापस ((ha->ip_config.ipv6_options &
		IPV6_OPT_IPV6_PROTOCOL_ENABLE) != 0);
पूर्ण

अटल अंतरभूत पूर्णांक is_qla4010(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP4010;
पूर्ण

अटल अंतरभूत पूर्णांक is_qla4022(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP4022;
पूर्ण

अटल अंतरभूत पूर्णांक is_qla4032(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP4032;
पूर्ण

अटल अंतरभूत पूर्णांक is_qla40XX(काष्ठा scsi_qla_host *ha)
अणु
	वापस is_qla4032(ha) || is_qla4022(ha) || is_qla4010(ha);
पूर्ण

अटल अंतरभूत पूर्णांक is_qla8022(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8022;
पूर्ण

अटल अंतरभूत पूर्णांक is_qla8032(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8324;
पूर्ण

अटल अंतरभूत पूर्णांक is_qla8042(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8042;
पूर्ण

अटल अंतरभूत पूर्णांक is_qla80XX(काष्ठा scsi_qla_host *ha)
अणु
	वापस is_qla8022(ha) || is_qla8032(ha) || is_qla8042(ha);
पूर्ण

अटल अंतरभूत पूर्णांक is_aer_supported(काष्ठा scsi_qla_host *ha)
अणु
	वापस ((ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8022) ||
		(ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8324) ||
		(ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8042));
पूर्ण

अटल अंतरभूत पूर्णांक adapter_up(काष्ठा scsi_qla_host *ha)
अणु
	वापस (test_bit(AF_ONLINE, &ha->flags) != 0) &&
	       (test_bit(AF_LINK_UP, &ha->flags) != 0) &&
	       (!test_bit(AF_LOOPBACK, &ha->flags));
पूर्ण

अटल अंतरभूत काष्ठा scsi_qla_host* to_qla_host(काष्ठा Scsi_Host *shost)
अणु
	वापस (काष्ठा scsi_qla_host *)iscsi_host_priv(shost);
पूर्ण

अटल अंतरभूत व्योम __iomem* isp_semaphore(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		&ha->reg->u1.isp4010.nvram :
		&ha->reg->u1.isp4022.semaphore);
पूर्ण

अटल अंतरभूत व्योम __iomem* isp_nvram(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		&ha->reg->u1.isp4010.nvram :
		&ha->reg->u1.isp4022.nvram);
पूर्ण

अटल अंतरभूत व्योम __iomem* isp_ext_hw_conf(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		&ha->reg->u2.isp4010.ext_hw_conf :
		&ha->reg->u2.isp4022.p0.ext_hw_conf);
पूर्ण

अटल अंतरभूत व्योम __iomem* isp_port_status(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		&ha->reg->u2.isp4010.port_status :
		&ha->reg->u2.isp4022.p0.port_status);
पूर्ण

अटल अंतरभूत व्योम __iomem* isp_port_ctrl(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		&ha->reg->u2.isp4010.port_ctrl :
		&ha->reg->u2.isp4022.p0.port_ctrl);
पूर्ण

अटल अंतरभूत व्योम __iomem* isp_port_error_status(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		&ha->reg->u2.isp4010.port_err_status :
		&ha->reg->u2.isp4022.p0.port_err_status);
पूर्ण

अटल अंतरभूत व्योम __iomem * isp_gp_out(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		&ha->reg->u2.isp4010.gp_out :
		&ha->reg->u2.isp4022.p0.gp_out);
पूर्ण

अटल अंतरभूत पूर्णांक eeprom_ext_hw_conf_offset(काष्ठा scsi_qla_host *ha)
अणु
	वापस (is_qla4010(ha) ?
		दुरत्व(काष्ठा eeprom_data, isp4010.ext_hw_conf) / 2 :
		दुरत्व(काष्ठा eeprom_data, isp4022.ext_hw_conf) / 2);
पूर्ण

पूर्णांक ql4xxx_sem_spinlock(काष्ठा scsi_qla_host * ha, u32 sem_mask, u32 sem_bits);
व्योम ql4xxx_sem_unlock(काष्ठा scsi_qla_host * ha, u32 sem_mask);
पूर्णांक ql4xxx_sem_lock(काष्ठा scsi_qla_host * ha, u32 sem_mask, u32 sem_bits);

अटल अंतरभूत पूर्णांक ql4xxx_lock_flash(काष्ठा scsi_qla_host *a)
अणु
	अगर (is_qla4010(a))
		वापस ql4xxx_sem_spinlock(a, QL4010_FLASH_SEM_MASK,
					   QL4010_FLASH_SEM_BITS);
	अन्यथा
		वापस ql4xxx_sem_spinlock(a, QL4022_FLASH_SEM_MASK,
					   (QL4022_RESOURCE_BITS_BASE_CODE |
					    (a->mac_index)) << 13);
पूर्ण

अटल अंतरभूत व्योम ql4xxx_unlock_flash(काष्ठा scsi_qla_host *a)
अणु
	अगर (is_qla4010(a))
		ql4xxx_sem_unlock(a, QL4010_FLASH_SEM_MASK);
	अन्यथा
		ql4xxx_sem_unlock(a, QL4022_FLASH_SEM_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक ql4xxx_lock_nvram(काष्ठा scsi_qla_host *a)
अणु
	अगर (is_qla4010(a))
		वापस ql4xxx_sem_spinlock(a, QL4010_NVRAM_SEM_MASK,
					   QL4010_NVRAM_SEM_BITS);
	अन्यथा
		वापस ql4xxx_sem_spinlock(a, QL4022_NVRAM_SEM_MASK,
					   (QL4022_RESOURCE_BITS_BASE_CODE |
					    (a->mac_index)) << 10);
पूर्ण

अटल अंतरभूत व्योम ql4xxx_unlock_nvram(काष्ठा scsi_qla_host *a)
अणु
	अगर (is_qla4010(a))
		ql4xxx_sem_unlock(a, QL4010_NVRAM_SEM_MASK);
	अन्यथा
		ql4xxx_sem_unlock(a, QL4022_NVRAM_SEM_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक ql4xxx_lock_drvr(काष्ठा scsi_qla_host *a)
अणु
	अगर (is_qla4010(a))
		वापस ql4xxx_sem_lock(a, QL4010_DRVR_SEM_MASK,
				       QL4010_DRVR_SEM_BITS);
	अन्यथा
		वापस ql4xxx_sem_lock(a, QL4022_DRVR_SEM_MASK,
				       (QL4022_RESOURCE_BITS_BASE_CODE |
					(a->mac_index)) << 1);
पूर्ण

अटल अंतरभूत व्योम ql4xxx_unlock_drvr(काष्ठा scsi_qla_host *a)
अणु
	अगर (is_qla4010(a))
		ql4xxx_sem_unlock(a, QL4010_DRVR_SEM_MASK);
	अन्यथा
		ql4xxx_sem_unlock(a, QL4022_DRVR_SEM_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक ql4xxx_reset_active(काष्ठा scsi_qla_host *ha)
अणु
	वापस test_bit(DPC_RESET_ACTIVE, &ha->dpc_flags) ||
	       test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	       test_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags) ||
	       test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags) ||
	       test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags) ||
	       test_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags);

पूर्ण

अटल अंतरभूत पूर्णांक qla4_8xxx_rd_direct(काष्ठा scsi_qla_host *ha,
				      स्थिर uपूर्णांक32_t crb_reg)
अणु
	वापस ha->isp_ops->rd_reg_direct(ha, ha->reg_tbl[crb_reg]);
पूर्ण

अटल अंतरभूत व्योम qla4_8xxx_wr_direct(काष्ठा scsi_qla_host *ha,
				       स्थिर uपूर्णांक32_t crb_reg,
				       स्थिर uपूर्णांक32_t value)
अणु
	ha->isp_ops->wr_reg_direct(ha, ha->reg_tbl[crb_reg], value);
पूर्ण

/*---------------------------------------------------------------------------*/

/* Defines क्रम qla4xxx_initialize_adapter() and qla4xxx_recover_adapter() */

#घोषणा INIT_ADAPTER    0
#घोषणा RESET_ADAPTER   1

#घोषणा PRESERVE_DDB_LIST	0
#घोषणा REBUILD_DDB_LIST	1

/* Defines क्रम process_aen() */
#घोषणा PROCESS_ALL_AENS	 0
#घोषणा FLUSH_DDB_CHANGED_AENS	 1

/* Defines क्रम udev events */
#घोषणा QL4_UEVENT_CODE_FW_DUMP		0

#पूर्ण_अगर	/*_QLA4XXX_H */
