<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver SAS definitions and hardware पूर्णांकerface header file.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _AIC94XX_SAS_H_
#घोषणा _AIC94XX_SAS_H_

#समावेश <scsi/libsas.h>

/* ---------- DDBs ---------- */
/* DDBs are device descriptor blocks which describe a device in the
 * करोमुख्य that this sequencer can मुख्यtain low-level connections क्रम
 * us.  They are be 64 bytes.
 */
#घोषणा ASD_MAX_DDBS	128

काष्ठा asd_ddb_ssp_smp_target_port अणु
	u8     conn_type;	  /* byte 0 */
#घोषणा DDB_TP_CONN_TYPE 0x81	  /* Initiator port and addr frame type 0x01 */

	u8     conn_rate;
	__be16 init_conn_tag;
	u8     dest_sas_addr[8];  /* bytes 4-11 */

	__le16 send_queue_head;
	u8     sq_suspended;
	u8     ddb_type;	  /* DDB_TYPE_TARGET */
#घोषणा DDB_TYPE_UNUSED    0xFF
#घोषणा DDB_TYPE_TARGET    0xFE
#घोषणा DDB_TYPE_INITIATOR 0xFD
#घोषणा DDB_TYPE_PM_PORT   0xFC

	__le16 _r_a;
	__be16 awt_def;

	u8     compat_features;	  /* byte 20 */
	u8     pathway_blocked_count;
	__be16 arb_रुको_समय;
	__be32 more_compat_features; /* byte 24 */

	u8     conn_mask;
	u8     flags;	  /* concurrent conn:2,2 and खोलो:0(1) */
#घोषणा CONCURRENT_CONN_SUPP 0x04
#घोषणा OPEN_REQUIRED        0x01

	u16    _r_b;
	__le16 exec_queue_tail;
	__le16 send_queue_tail;
	__le16 sister_ddb;

	__le16 _r_c;

	u8     max_concurrent_conn;
	u8     num_concurrent_conn;
	u8     num_contexts;

	u8     _r_d;

	__le16 active_task_count;

	u8     _r_e[9];

	u8     itnl_reason;	  /* I_T nexus loss reason */

	__le16 _r_f;

	__le16 itnl_समयout;
#घोषणा ITNL_TIMEOUT_CONST 0x7D0 /* 2 seconds */

	__le32 itnl_बारtamp;
पूर्ण __attribute__ ((packed));

काष्ठा asd_ddb_stp_sata_target_port अणु
	u8     conn_type;	  /* byte 0 */
	u8     conn_rate;
	__be16 init_conn_tag;
	u8     dest_sas_addr[8];  /* bytes 4-11 */

	__le16 send_queue_head;
	u8     sq_suspended;
	u8     ddb_type;	  /* DDB_TYPE_TARGET */

	__le16 _r_a;

	__be16 awt_def;
	u8     compat_features;	  /* byte 20 */
	u8     pathway_blocked_count;
	__be16 arb_रुको_समय;
	__be32 more_compat_features; /* byte 24 */

	u8     conn_mask;
	u8     flags;	  /* concurrent conn:2,2 and खोलो:0(1) */
#घोषणा SATA_MULTIPORT     0x80
#घोषणा SUPPORTS_AFFIL     0x40
#घोषणा STP_AFFIL_POL      0x20

	u8     _r_b;
	u8     flags2;		  /* STP बंद policy:0 */
#घोषणा STP_CL_POL_NO_TX    0x00
#घोषणा STP_CL_POL_BTW_CMDS 0x01

	__le16 exec_queue_tail;
	__le16 send_queue_tail;
	__le16 sister_ddb;
	__le16 ata_cmd_scbptr;
	__le32 sata_tag_alloc_mask;
	__le16 active_task_count;
	__le16 _r_c;
	__le32 sata_sactive;
	u8     num_sata_tags;
	u8     sata_status;
	u8     sata_ending_status;
	u8     itnl_reason;	  /* I_T nexus loss reason */
	__le16 ncq_data_scb_ptr;
	__le16 itnl_समयout;
	__le32 itnl_बारtamp;
पूर्ण __attribute__ ((packed));

/* This काष्ठा asd_ddb_init_port, describes the device descriptor block
 * of an initiator port (when the sequencer is operating in target mode).
 * Bytes [0,11] and [20,27] are from the OPEN address frame.
 * The sequencer allocates an initiator port DDB entry.
 */
काष्ठा asd_ddb_init_port अणु
	u8     conn_type;	  /* byte 0 */
	u8     conn_rate;
	__be16 init_conn_tag;     /* BE */
	u8     dest_sas_addr[8];
	__le16 send_queue_head;   /* LE, byte 12 */
	u8     sq_suspended;
	u8     ddb_type;	  /* DDB_TYPE_INITIATOR */
	__le16 _r_a;
	__be16 awt_def;		  /* BE */
	u8     compat_features;
	u8     pathway_blocked_count;
	__be16 arb_रुको_समय;	  /* BE */
	__be32 more_compat_features; /* BE */
	u8     conn_mask;
	u8     flags;		  /* == 5 */
	u16    _r_b;
	__le16 exec_queue_tail;	  /* execution queue tail */
	__le16 send_queue_tail;
	__le16 sister_ddb;
	__le16 init_resp_समयout; /* initiator response समयout */
	__le32 _r_c;
	__le16 active_tasks;	  /* active task count */
	__le16 init_list;	  /* initiator list link poपूर्णांकer */
	__le32 _r_d;
	u8     max_conn_to[3]; /* from Conn-Disc mode page, in us, LE */
	u8     itnl_reason;	  /* I_T nexus loss reason */
	__le16 bus_inact_to; /* from Conn-Disc mode page, in 100 us, LE */
	__le16 itnl_to;		  /* from the Protocol Specअगरic Port Ctrl MP */
	__le32 itnl_बारtamp;
पूर्ण __attribute__ ((packed));

/* This काष्ठा asd_ddb_sata_tag, describes a look-up table to be used
 * by the sequencers.  SATA II, IDENTIFY DEVICE data, word 76, bit 8:
 * NCQ support.  This table is used by the sequencers to find the
 * corresponding SCB, given a SATA II tag value.
 */
काष्ठा asd_ddb_sata_tag अणु
	__le16 scb_poपूर्णांकer[32];
पूर्ण __attribute__ ((packed));

/* This काष्ठा asd_ddb_sata_pm_table, describes a port number to
 * connection handle look-up table.  SATA tarमाला_लो attached to a port
 * multiplier require a 4-bit port number value.  There is one DDB
 * entry of this type क्रम each SATA port multiplier (sister DDB).
 * Given a SATA PM port number, this table gives us the SATA PM Port
 * DDB of the SATA port multiplier port (i.e. the SATA target
 * discovered on the port).
 */
काष्ठा asd_ddb_sata_pm_table अणु
	__le16 ddb_poपूर्णांकer[16];
	__le16 _r_a[16];
पूर्ण __attribute__ ((packed));

/* This काष्ठा asd_ddb_sata_pm_port, describes the SATA port multiplier
 * port क्रमmat DDB.
 */
काष्ठा asd_ddb_sata_pm_port अणु
	u8     _r_a[15];
	u8     ddb_type;
	u8     _r_b[13];
	u8     pm_port_flags;
#घोषणा PM_PORT_MASK  0xF0
#घोषणा PM_PORT_SET   0x02
	u8     _r_c[6];
	__le16 sister_ddb;
	__le16 ata_cmd_scbptr;
	__le32 sata_tag_alloc_mask;
	__le16 active_task_count;
	__le16 parent_ddb;
	__le32 sata_sactive;
	u8     num_sata_tags;
	u8     sata_status;
	u8     sata_ending_status;
	u8     _r_d[9];
पूर्ण __attribute__ ((packed));

/* This काष्ठा asd_ddb_seq_shared, describes a DDB shared by the
 * central and link sequencers.  port_map_by_links is indexed phy
 * number [0,7]; each byte is a bit mask of all the phys that are in
 * the same port as the indexed phy.
 */
काष्ठा asd_ddb_seq_shared अणु
	__le16 q_मुक्त_ddb_head;
	__le16 q_मुक्त_ddb_tail;
	__le16 q_मुक्त_ddb_cnt;
	__le16 q_used_ddb_head;
	__le16 q_used_ddb_tail;
	__le16 shared_mem_lock;
	__le16 smp_conn_tag;
	__le16 est_nexus_buf_cnt;
	__le16 est_nexus_buf_thresh;
	u32    _r_a;
	u8     settable_max_contexts;
	u8     _r_b[23];
	u8     conn_not_active;
	u8     phy_is_up;
	u8     _r_c[8];
	u8     port_map_by_links[8];
पूर्ण __attribute__ ((packed));

/* ---------- SG Element ---------- */

/* This काष्ठा sg_el, describes the hardware scatter gather buffer
 * element.  All entries are little endian.  In an SCB, there are 2 of
 * this, plus one more, called a link element of this indicating a
 * sublist अगर needed.
 *
 * A link element has only the bus address set and the flags (DS) bit
 * valid.  The bus address poपूर्णांकs to the start of the sublist.
 *
 * If a sublist is needed, then that sublist should also include the 2
 * sg_el embedded in the SCB, in which हाल next_sg_offset is 32,
 * since माप(sg_el) = 16; EOS should be 1 and EOL 0 in this हाल.
 */
काष्ठा sg_el अणु
	__le64 bus_addr;
	__le32 size;
	__le16 _r;
	u8     next_sg_offs;
	u8     flags;
#घोषणा ASD_SG_EL_DS_MASK   0x30
#घोषणा ASD_SG_EL_DS_OCM    0x10
#घोषणा ASD_SG_EL_DS_HM     0x00
#घोषणा ASD_SG_EL_LIST_MASK 0xC0
#घोषणा ASD_SG_EL_LIST_EOL  0x40
#घोषणा ASD_SG_EL_LIST_EOS  0x80
पूर्ण __attribute__ ((packed));

/* ---------- SCBs ---------- */

/* An SCB (sequencer control block) is comprised of a common header
 * and a task part, क्रम a total of 128 bytes.  All fields are in LE
 * order, unless otherwise noted.
 */

/* This काष्ठा scb_header, defines the SCB header क्रमmat.
 */
काष्ठा scb_header अणु
	__le64 next_scb;
	__le16 index;		  /* transaction context */
	u8     opcode;
पूर्ण __attribute__ ((packed));

/* SCB opcodes: Execution queue
 */
#घोषणा INITIATE_SSP_TASK       0x00
#घोषणा INITIATE_LONG_SSP_TASK  0x01
#घोषणा INITIATE_BIसूची_SSP_TASK 0x02
#घोषणा SCB_ABORT_TASK          0x03
#घोषणा INITIATE_SSP_TMF        0x04
#घोषणा SSP_TARG_GET_DATA       0x05
#घोषणा SSP_TARG_GET_DATA_GOOD  0x06
#घोषणा SSP_TARG_SEND_RESP      0x07
#घोषणा QUERY_SSP_TASK          0x08
#घोषणा INITIATE_ATA_TASK       0x09
#घोषणा INITIATE_ATAPI_TASK     0x0a
#घोषणा CONTROL_ATA_DEV         0x0b
#घोषणा INITIATE_SMP_TASK       0x0c
#घोषणा SMP_TARG_SEND_RESP      0x0f

/* SCB opcodes: Send Queue
 */
#घोषणा SSP_TARG_SEND_DATA      0x40
#घोषणा SSP_TARG_SEND_DATA_GOOD 0x41

/* SCB opcodes: Link Queue
 */
#घोषणा CONTROL_PHY             0x80
#घोषणा SEND_PRIMITIVE          0x81
#घोषणा INITIATE_LINK_ADM_TASK  0x82

/* SCB opcodes: other
 */
#घोषणा EMPTY_SCB               0xc0
#घोषणा INITIATE_SEQ_ADM_TASK   0xc1
#घोषणा EST_ICL_TARG_WINDOW     0xc2
#घोषणा COPY_MEM                0xc3
#घोषणा CLEAR_NEXUS             0xc4
#घोषणा INITIATE_DDB_ADM_TASK   0xc6
#घोषणा ESTABLISH_NEXUS_ESCB    0xd0

#घोषणा LUN_SIZE                8

#घोषणा EFB_MASK                0x80
#घोषणा TASK_PRIO_MASK          0x78
#घोषणा TASK_ATTR_MASK          0x07
/* ---------- SCB tasks ---------- */

/* This is both ssp_task and दीर्घ_ssp_task
 */
काष्ठा initiate_ssp_task अणु
	u8     proto_conn_rate;	  /* proto:6,4, conn_rate:3,0 */
	__le32 total_xfer_len;
	काष्ठा ssp_frame_hdr  ssp_frame;
	काष्ठा ssp_command_iu ssp_cmd;
	__le16 sister_scb;	  /* 0xFFFF */
	__le16 conn_handle;	  /* index to DDB क्रम the पूर्णांकended target */
	u8     data_dir;	  /* :1,0 */
#घोषणा DATA_सूची_NONE   0x00
#घोषणा DATA_सूची_IN     0x01
#घोषणा DATA_सूची_OUT    0x02
#घोषणा DATA_सूची_BYRECIPIENT 0x03

	u8     _r_a;
	u8     retry_count;
	u8     _r_b[5];
	काष्ठा sg_el sg_element[3]; /* 2 real and 1 link */
पूर्ण __attribute__ ((packed));

/* This defines both ata_task and atapi_task.
 * ata: C bit of FIS should be 1,
 * atapi: C bit of FIS should be 1, and command रेजिस्टर should be 0xA0,
 * to indicate a packet command.
 */
काष्ठा initiate_ata_task अणु
	u8     proto_conn_rate;
	__le32 total_xfer_len;
	काष्ठा host_to_dev_fis fis;
	__le32 data_offs;
	u8     atapi_packet[16];
	u8     _r_a[12];
	__le16 sister_scb;
	__le16 conn_handle;
	u8     ata_flags;	  /* CSMI:6,6, DTM:4,4, QT:3,3, data dir:1,0 */
#घोषणा CSMI_TASK           0x40
#घोषणा DATA_XFER_MODE_DMA  0x10
#घोषणा ATA_Q_TYPE_MASK     0x08
#घोषणा	ATA_Q_TYPE_UNTAGGED 0x00
#घोषणा ATA_Q_TYPE_NCQ      0x08

	u8     _r_b;
	u8     retry_count;
	u8     _r_c;
	u8     flags;
#घोषणा STP_AFFIL_POLICY   0x20
#घोषणा SET_AFFIL_POLICY   0x10
#घोषणा RET_PARTIAL_SGLIST 0x02

	u8     _r_d[3];
	काष्ठा sg_el sg_element[3];
पूर्ण __attribute__ ((packed));

काष्ठा initiate_smp_task अणु
	u8     proto_conn_rate;
	u8     _r_a[40];
	काष्ठा sg_el smp_req;
	__le16 sister_scb;
	__le16 conn_handle;
	u8     _r_c[8];
	काष्ठा sg_el smp_resp;
	u8     _r_d[32];
पूर्ण __attribute__ ((packed));

काष्ठा control_phy अणु
	u8     phy_id;
	u8     sub_func;
#घोषणा DISABLE_PHY            0x00
#घोषणा ENABLE_PHY             0x01
#घोषणा RELEASE_SPINUP_HOLD    0x02
#घोषणा ENABLE_PHY_NO_SAS_OOB  0x03
#घोषणा ENABLE_PHY_NO_SATA_OOB 0x04
#घोषणा PHY_NO_OP              0x05
#घोषणा EXECUTE_HARD_RESET     0x81

	u8     func_mask;
	u8     speed_mask;
	u8     hot_plug_delay;
	u8     port_type;
	u8     flags;
#घोषणा DEV_PRES_TIMER_OVERRIDE_ENABLE 0x01
#घोषणा DISABLE_PHY_IF_OOB_FAILS       0x02

	__le32 समयout_override;
	u8     link_reset_retries;
	u8     _r_a[47];
	__le16 conn_handle;
	u8     _r_b[56];
पूर्ण __attribute__ ((packed));

काष्ठा control_ata_dev अणु
	u8     proto_conn_rate;
	__le32 _r_a;
	काष्ठा host_to_dev_fis fis;
	u8     _r_b[32];
	__le16 sister_scb;
	__le16 conn_handle;
	u8     ata_flags;	  /* 0 */
	u8     _r_c[55];
पूर्ण __attribute__ ((packed));

काष्ठा empty_scb अणु
	u8     num_valid;
	__le32 _r_a;
#घोषणा ASD_EDBS_PER_SCB 7
/* header+data+CRC+DMA suffix data */
#घोषणा ASD_EDB_SIZE (24+1024+4+16)
	काष्ठा sg_el eb[ASD_EDBS_PER_SCB];
#घोषणा ELEMENT_NOT_VALID  0xC0
पूर्ण __attribute__ ((packed));

काष्ठा initiate_link_adm अणु
	u8     phy_id;
	u8     sub_func;
#घोषणा GET_LINK_ERROR_COUNT      0x00
#घोषणा RESET_LINK_ERROR_COUNT    0x01
#घोषणा ENABLE_NOTIFY_SPINUP_INTS 0x02

	u8     _r_a[57];
	__le16 conn_handle;
	u8     _r_b[56];
पूर्ण __attribute__ ((packed));

काष्ठा copy_memory अणु
	u8     _r_a;
	__le16 xfer_len;
	__le16 _r_b;
	__le64 src_busaddr;
	u8     src_ds;		  /* See definition of sg_el */
	u8     _r_c[45];
	__le16 conn_handle;
	__le64 _r_d;
	__le64 dest_busaddr;
	u8     dest_ds;		  /* See definition of sg_el */
	u8     _r_e[39];
पूर्ण __attribute__ ((packed));

काष्ठा पात_task अणु
	u8     proto_conn_rate;
	__le32 _r_a;
	काष्ठा ssp_frame_hdr ssp_frame;
	काष्ठा ssp_पंचांगf_iu ssp_task;
	__le16 sister_scb;
	__le16 conn_handle;
	u8     flags;	  /* ovrd_itnl_समयr:3,3, suspend_data_trans:2,2 */
#घोषणा SUSPEND_DATA_TRANS 0x04

	u8     _r_b;
	u8     retry_count;
	u8     _r_c[5];
	__le16 index;  /* Transaction context of task to be queried */
	__le16 itnl_to;
	u8     _r_d[44];
पूर्ण __attribute__ ((packed));

काष्ठा clear_nexus अणु
	u8     nexus;
#घोषणा NEXUS_ADAPTER  0x00
#घोषणा NEXUS_PORT     0x01
#घोषणा NEXUS_I_T      0x02
#घोषणा NEXUS_I_T_L    0x03
#घोषणा NEXUS_TAG      0x04
#घोषणा NEXUS_TRANS_CX 0x05
#घोषणा NEXUS_SATA_TAG 0x06
#घोषणा NEXUS_T_L      0x07
#घोषणा NEXUS_L        0x08
#घोषणा NEXUS_T_TAG    0x09

	__le32 _r_a;
	u8     flags;
#घोषणा SUSPEND_TX     0x80
#घोषणा RESUME_TX      0x40
#घोषणा SEND_Q         0x04
#घोषणा EXEC_Q         0x02
#घोषणा NOTINQ         0x01

	u8     _r_b[3];
	u8     conn_mask;
	u8     _r_c[19];
	काष्ठा ssp_पंचांगf_iu ssp_task; /* LUN and TAG */
	__le16 _r_d;
	__le16 conn_handle;
	__le64 _r_e;
	__le16 index;  /* Transaction context of task to be cleared */
	__le16 context;		  /* Clear nexus context */
	u8     _r_f[44];
पूर्ण __attribute__ ((packed));

काष्ठा initiate_ssp_पंचांगf अणु
	u8     proto_conn_rate;
	__le32 _r_a;
	काष्ठा ssp_frame_hdr ssp_frame;
	काष्ठा ssp_पंचांगf_iu ssp_task;
	__le16 sister_scb;
	__le16 conn_handle;
	u8     flags;	  /* itnl override and suspend data tx */
#घोषणा OVERRIDE_ITNL_TIMER  8

	u8     _r_b;
	u8     retry_count;
	u8     _r_c[5];
	__le16 index;  /* Transaction context of task to be queried */
	__le16 itnl_to;
	u8     _r_d[44];
पूर्ण __attribute__ ((packed));

/* Transmits an arbitrary primitive on the link.
 * Used क्रम NOTIFY and BROADCAST.
 */
काष्ठा send_prim अणु
	u8     phy_id;
	u8     रुको_transmit; 	  /* :0,0 */
	u8     xmit_flags;
#घोषणा XMTPSIZE_MASK      0xF0
#घोषणा XMTPSIZE_SINGLE    0x10
#घोषणा XMTPSIZE_REPEATED  0x20
#घोषणा XMTPSIZE_CONT      0x20
#घोषणा XMTPSIZE_TRIPLE    0x30
#घोषणा XMTPSIZE_REDUNDANT 0x60
#घोषणा XMTPSIZE_INF       0

#घोषणा XMTCONTEN          0x04
#घोषणा XMTPFRM            0x02	  /* Transmit at the next frame boundary */
#घोषणा XMTPIMM            0x01	  /* Transmit immediately */

	__le16 _r_a;
	u8     prim[4];		  /* K, D0, D1, D2 */
	u8     _r_b[50];
	__le16 conn_handle;
	u8     _r_c[56];
पूर्ण __attribute__ ((packed));

/* This describes both SSP Target Get Data and SSP Target Get Data And
 * Send Good Response SCBs.  Used when the sequencer is operating in
 * target mode...
 */
काष्ठा ssp_targ_get_data अणु
	u8     proto_conn_rate;
	__le32 total_xfer_len;
	काष्ठा ssp_frame_hdr ssp_frame;
	काष्ठा xfer_rdy_iu  xfer_rdy;
	u8     lun[LUN_SIZE];
	__le64 _r_a;
	__le16 sister_scb;
	__le16 conn_handle;
	u8     data_dir;	  /* 01b */
	u8     _r_b;
	u8     retry_count;
	u8     _r_c[5];
	काष्ठा sg_el sg_element[3];
पूर्ण __attribute__ ((packed));

/* ---------- The actual SCB काष्ठा ---------- */

काष्ठा scb अणु
	काष्ठा scb_header header;
	जोड़ अणु
		काष्ठा initiate_ssp_task ssp_task;
		काष्ठा initiate_ata_task ata_task;
		काष्ठा initiate_smp_task smp_task;
		काष्ठा control_phy       control_phy;
		काष्ठा control_ata_dev   control_ata_dev;
		काष्ठा empty_scb         escb;
		काष्ठा initiate_link_adm link_adm;
		काष्ठा copy_memory       cp_mem;
		काष्ठा पात_task        पात_task;
		काष्ठा clear_nexus       clear_nexus;
		काष्ठा initiate_ssp_पंचांगf  ssp_पंचांगf;
	पूर्ण;
पूर्ण __attribute__ ((packed));

/* ---------- Done List ---------- */
/* The करोne list entry opcode field is defined below.
 * The mnemonic encoding and meaning is as follows:
 * TC - Task Complete, status was received and acknowledged
 * TF - Task Failed, indicates an error prior to receiving acknowledgment
 *   क्रम the command:
 *   - no conn,
 *   - NACK or R_ERR received in response to this command,
 *   - credit blocked or not available, or in the हाल of SMP request,
 *   - no SMP response was received.
 *   In these four हालs it is known that the target didn't receive the
 *   command.
 * TI - Task Interrupted, error after the command was acknowledged.  It is
 *   known that the command was received by the target.
 * TU - Task Unacked, command was transmitted but neither ACK (R_OK) nor NAK
 *   (R_ERR) was received due to loss of संकेत, broken connection, loss of
 *   dword sync or other reason.  The application client should send the
 *   appropriate task query.
 * TA - Task Aborted, see TF.
 * _RESP - The completion includes an empty buffer containing status.
 * TO - Timeout.
 */
#घोषणा TC_NO_ERROR             0x00
#घोषणा TC_UNDERRUN             0x01
#घोषणा TC_OVERRUN              0x02
#घोषणा TF_OPEN_TO              0x03
#घोषणा TF_OPEN_REJECT          0x04
#घोषणा TI_BREAK                0x05
#घोषणा TI_PROTO_ERR            0x06
#घोषणा TC_SSP_RESP             0x07
#घोषणा TI_PHY_DOWN             0x08
#घोषणा TF_PHY_DOWN             0x09
#घोषणा TC_LINK_ADM_RESP        0x0a
#घोषणा TC_CSMI                 0x0b
#घोषणा TC_ATA_RESP             0x0c
#घोषणा TU_PHY_DOWN             0x0d
#घोषणा TU_BREAK                0x0e
#घोषणा TI_SATA_TO              0x0f
#घोषणा TI_NAK                  0x10
#घोषणा TC_CONTROL_PHY          0x11
#घोषणा TF_BREAK                0x12
#घोषणा TC_RESUME               0x13
#घोषणा TI_ACK_NAK_TO           0x14
#घोषणा TF_SMPRSP_TO            0x15
#घोषणा TF_SMP_XMIT_RCV_ERR     0x16
#घोषणा TC_PARTIAL_SG_LIST      0x17
#घोषणा TU_ACK_NAK_TO           0x18
#घोषणा TU_SATA_TO              0x19
#घोषणा TF_NAK_RECV             0x1a
#घोषणा TA_I_T_NEXUS_LOSS       0x1b
#घोषणा TC_ATA_R_ERR_RECV       0x1c
#घोषणा TF_TMF_NO_CTX           0x1d
#घोषणा TA_ON_REQ               0x1e
#घोषणा TF_TMF_NO_TAG           0x1f
#घोषणा TF_TMF_TAG_FREE         0x20
#घोषणा TF_TMF_TASK_DONE        0x21
#घोषणा TF_TMF_NO_CONN_HANDLE   0x22
#घोषणा TC_TASK_CLEARED         0x23
#घोषणा TI_SYNCS_RECV           0x24
#घोषणा TU_SYNCS_RECV           0x25
#घोषणा TF_IRTT_TO              0x26
#घोषणा TF_NO_SMP_CONN          0x27
#घोषणा TF_IU_SHORT             0x28
#घोषणा TF_DATA_OFFS_ERR        0x29
#घोषणा TF_INV_CONN_HANDLE      0x2a
#घोषणा TF_REQUESTED_N_PENDING  0x2b

/* 0xc1 - 0xc7: empty buffer received,
   0xd1 - 0xd7: establish nexus empty buffer received
*/
/* This is the ESCB mask */
#घोषणा ESCB_RECVD              0xC0


/* This काष्ठा करोne_list_काष्ठा defines the करोne list entry.
 * All fields are LE.
 */
काष्ठा करोne_list_काष्ठा अणु
	__le16 index;		  /* aka transaction context */
	u8     opcode;
	u8     status_block[4];
	u8     toggle;		  /* bit 0 */
#घोषणा DL_TOGGLE_MASK     0x01
पूर्ण __attribute__ ((packed));

/* ---------- PHYS ---------- */

काष्ठा asd_phy अणु
	काष्ठा asd_sas_phy        sas_phy;
	काष्ठा asd_phy_desc   *phy_desc; /* hw profile */

	काष्ठा sas_identअगरy_frame *identअगरy_frame;
	काष्ठा asd_dma_tok  *id_frm_tok;
	काष्ठा asd_port     *asd_port;

	u8         frame_rcvd[ASD_EDB_SIZE];
पूर्ण;


#घोषणा ASD_SCB_SIZE माप(काष्ठा scb)
#घोषणा ASD_DDB_SIZE माप(काष्ठा asd_ddb_ssp_smp_target_port)

/* Define this to 0 अगर you करो not want NOTIFY (ENABLE SPINIP) sent.
 * Default: 0x10 (it's a mask)
 */
#घोषणा ASD_NOTIFY_ENABLE_SPINUP  0x10

/* If enabled, set this to the पूर्णांकerval between transmission
 * of NOTIFY (ENABLE SPINUP). In units of 200 us.
 */
#घोषणा ASD_NOTIFY_TIMEOUT        2500

/* Initial delay after OOB, beक्रमe we transmit NOTIFY (ENABLE SPINUP).
 * If 0, transmit immediately. In milliseconds.
 */
#घोषणा ASD_NOTIFY_DOWN_COUNT     0

/* Device present समयr समयout स्थिरant, 10 ms. */
#घोषणा ASD_DEV_PRESENT_TIMEOUT   0x2710

#घोषणा ASD_SATA_INTERLOCK_TIMEOUT 0

/* How दीर्घ to रुको beक्रमe shutting करोwn an STP connection, unless
 * an STP target sent frame(s). 50 usec.
 * IGNORED by the sequencer (i.e. value 0 always).
 */
#घोषणा ASD_STP_SHUTDOWN_TIMEOUT  0x0

/* ATA soft reset समयr समयout. 5 usec. */
#घोषणा ASD_SRST_ASSERT_TIMEOUT   0x05

/* 31 sec */
#घोषणा ASD_RCV_FIS_TIMEOUT       0x01D905C0

#घोषणा ASD_ONE_MILLISEC_TIMEOUT  0x03e8

/* COMINIT समयr */
#घोषणा ASD_TEN_MILLISEC_TIMEOUT  0x2710
#घोषणा ASD_COMINIT_TIMEOUT ASD_TEN_MILLISEC_TIMEOUT

/* 1 sec */
#घोषणा ASD_SMP_RCV_TIMEOUT       0x000F4240

#पूर्ण_अगर
