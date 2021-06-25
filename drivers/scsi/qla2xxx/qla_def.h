<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#अगर_अघोषित __QLA_DEF_H
#घोषणा __QLA_DEF_H

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
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/firmware.h>
#समावेश <linux/aer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/btree.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_bsg_fc.h>

#समावेश <uapi/scsi/fc/fc_els.h>

/* Big endian Fibre Channel S_ID (source ID) or D_ID (destination ID). */
प्रकार काष्ठा अणु
	uपूर्णांक8_t करोमुख्य;
	uपूर्णांक8_t area;
	uपूर्णांक8_t al_pa;
पूर्ण be_id_t;

/* Little endian Fibre Channel S_ID (source ID) or D_ID (destination ID). */
प्रकार काष्ठा अणु
	uपूर्णांक8_t al_pa;
	uपूर्णांक8_t area;
	uपूर्णांक8_t करोमुख्य;
पूर्ण le_id_t;

#समावेश "qla_bsg.h"
#समावेश "qla_dsd.h"
#समावेश "qla_nx.h"
#समावेश "qla_nx2.h"
#समावेश "qla_nvme.h"
#घोषणा QLA2XXX_DRIVER_NAME	"qla2xxx"
#घोषणा QLA2XXX_APIDEV		"ql2xapidev"
#घोषणा QLA2XXX_MANUFACTURER	"QLogic Corporation"

/*
 * We have MAILBOX_REGISTER_COUNT sized arrays in a few places,
 * but that's fine as we don't look at the last 24 ones क्रम
 * ISP2100 HBAs.
 */
#घोषणा MAILBOX_REGISTER_COUNT_2100	8
#घोषणा MAILBOX_REGISTER_COUNT_2200	24
#घोषणा MAILBOX_REGISTER_COUNT		32

#घोषणा QLA2200A_RISC_ROM_VER	4
#घोषणा FPM_2300		6
#घोषणा FPM_2310		7

#समावेश "qla_settings.h"

#घोषणा MODE_DUAL (MODE_TARGET | MODE_INITIATOR)

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

#घोषणा LSB(x)	((uपूर्णांक8_t)(x))
#घोषणा MSB(x)	((uपूर्णांक8_t)((uपूर्णांक16_t)(x) >> 8))

#घोषणा LSW(x)	((uपूर्णांक16_t)(x))
#घोषणा MSW(x)	((uपूर्णांक16_t)((uपूर्णांक32_t)(x) >> 16))

#घोषणा LSD(x)	((uपूर्णांक32_t)((uपूर्णांक64_t)(x)))
#घोषणा MSD(x)	((uपूर्णांक32_t)((((uपूर्णांक64_t)(x)) >> 16) >> 16))

अटल अंतरभूत uपूर्णांक32_t make_handle(uपूर्णांक16_t x, uपूर्णांक16_t y)
अणु
	वापस ((uपूर्णांक32_t)x << 16) | y;
पूर्ण

/*
 * I/O रेजिस्टर
*/

अटल अंतरभूत u8 rd_reg_byte(स्थिर अस्थिर u8 __iomem *addr)
अणु
	वापस पढ़ोb(addr);
पूर्ण

अटल अंतरभूत u16 rd_reg_word(स्थिर अस्थिर __le16 __iomem *addr)
अणु
	वापस पढ़ोw(addr);
पूर्ण

अटल अंतरभूत u32 rd_reg_dword(स्थिर अस्थिर __le32 __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण

अटल अंतरभूत u8 rd_reg_byte_relaxed(स्थिर अस्थिर u8 __iomem *addr)
अणु
	वापस पढ़ोb_relaxed(addr);
पूर्ण

अटल अंतरभूत u16 rd_reg_word_relaxed(स्थिर अस्थिर __le16 __iomem *addr)
अणु
	वापस पढ़ोw_relaxed(addr);
पूर्ण

अटल अंतरभूत u32 rd_reg_dword_relaxed(स्थिर अस्थिर __le32 __iomem *addr)
अणु
	वापस पढ़ोl_relaxed(addr);
पूर्ण

अटल अंतरभूत व्योम wrt_reg_byte(अस्थिर u8 __iomem *addr, u8 data)
अणु
	वापस ग_लिखोb(data, addr);
पूर्ण

अटल अंतरभूत व्योम wrt_reg_word(अस्थिर __le16 __iomem *addr, u16 data)
अणु
	वापस ग_लिखोw(data, addr);
पूर्ण

अटल अंतरभूत व्योम wrt_reg_dword(अस्थिर __le32 __iomem *addr, u32 data)
अणु
	वापस ग_लिखोl(data, addr);
पूर्ण

/*
 * ISP83XX specअगरic remote रेजिस्टर addresses
 */
#घोषणा QLA83XX_LED_PORT0			0x00201320
#घोषणा QLA83XX_LED_PORT1			0x00201328
#घोषणा QLA83XX_IDC_DEV_STATE		0x22102384
#घोषणा QLA83XX_IDC_MAJOR_VERSION	0x22102380
#घोषणा QLA83XX_IDC_MINOR_VERSION	0x22102398
#घोषणा QLA83XX_IDC_DRV_PRESENCE	0x22102388
#घोषणा QLA83XX_IDC_DRIVER_ACK		0x2210238c
#घोषणा QLA83XX_IDC_CONTROL			0x22102390
#घोषणा QLA83XX_IDC_AUDIT			0x22102394
#घोषणा QLA83XX_IDC_LOCK_RECOVERY	0x2210239c
#घोषणा QLA83XX_DRIVER_LOCKID		0x22102104
#घोषणा QLA83XX_DRIVER_LOCK			0x8111c028
#घोषणा QLA83XX_DRIVER_UNLOCK		0x8111c02c
#घोषणा QLA83XX_FLASH_LOCKID		0x22102100
#घोषणा QLA83XX_FLASH_LOCK			0x8111c010
#घोषणा QLA83XX_FLASH_UNLOCK		0x8111c014
#घोषणा QLA83XX_DEV_PARTINFO1		0x221023e0
#घोषणा QLA83XX_DEV_PARTINFO2		0x221023e4
#घोषणा QLA83XX_FW_HEARTBEAT		0x221020b0
#घोषणा QLA83XX_PEG_HALT_STATUS1	0x221020a8
#घोषणा QLA83XX_PEG_HALT_STATUS2	0x221020ac

/* 83XX: Macros defining 8200 AEN Reason codes */
#घोषणा IDC_DEVICE_STATE_CHANGE BIT_0
#घोषणा IDC_PEG_HALT_STATUS_CHANGE BIT_1
#घोषणा IDC_NIC_FW_REPORTED_FAILURE BIT_2
#घोषणा IDC_HEARTBEAT_FAILURE BIT_3

/* 83XX: Macros defining 8200 AEN Error-levels */
#घोषणा ERR_LEVEL_NON_FATAL 0x1
#घोषणा ERR_LEVEL_RECOVERABLE_FATAL 0x2
#घोषणा ERR_LEVEL_UNRECOVERABLE_FATAL 0x4

/* 83XX: Macros क्रम IDC Version */
#घोषणा QLA83XX_SUPP_IDC_MAJOR_VERSION 0x01
#घोषणा QLA83XX_SUPP_IDC_MINOR_VERSION 0x0

/* 83XX: Macros क्रम scheduling dpc tasks */
#घोषणा QLA83XX_NIC_CORE_RESET 0x1
#घोषणा QLA83XX_IDC_STATE_HANDLER 0x2
#घोषणा QLA83XX_NIC_CORE_UNRECOVERABLE 0x3

/* 83XX: Macros क्रम defining IDC-Control bits */
#घोषणा QLA83XX_IDC_RESET_DISABLED BIT_0
#घोषणा QLA83XX_IDC_GRACEFUL_RESET BIT_1

/* 83XX: Macros क्रम dअगरferent समयouts */
#घोषणा QLA83XX_IDC_INITIALIZATION_TIMEOUT 30
#घोषणा QLA83XX_IDC_RESET_ACK_TIMEOUT 10
#घोषणा QLA83XX_MAX_LOCK_RECOVERY_WAIT (2 * HZ)

/* 83XX: Macros क्रम defining class in DEV-Partition Info रेजिस्टर */
#घोषणा QLA83XX_CLASS_TYPE_NONE		0x0
#घोषणा QLA83XX_CLASS_TYPE_NIC		0x1
#घोषणा QLA83XX_CLASS_TYPE_FCOE		0x2
#घोषणा QLA83XX_CLASS_TYPE_ISCSI	0x3

/* 83XX: Macros क्रम IDC Lock-Recovery stages */
#घोषणा IDC_LOCK_RECOVERY_STAGE1	0x1 /* Stage1: Intent क्रम
					     * lock-recovery
					     */
#घोषणा IDC_LOCK_RECOVERY_STAGE2	0x2 /* Stage2: Perक्रमm lock-recovery */

/* 83XX: Macros क्रम IDC Audit type */
#घोषणा IDC_AUDIT_TIMESTAMP		0x0 /* IDC-AUDIT: Record बारtamp of
					     * dev-state change to NEED-RESET
					     * or NEED-QUIESCENT
					     */
#घोषणा IDC_AUDIT_COMPLETION		0x1 /* IDC-AUDIT: Record duration of
					     * reset-recovery completion is
					     * second
					     */
/* ISP2031: Values क्रम laser on/off */
#घोषणा PORT_0_2031	0x00201340
#घोषणा PORT_1_2031	0x00201350
#घोषणा LASER_ON_2031	0x01800100
#घोषणा LASER_OFF_2031	0x01800180

/*
 * The ISP2312 v2 chip cannot access the FLASH/GPIO रेजिस्टरs via MMIO in an
 * 133Mhz slot.
 */
#घोषणा RD_REG_WORD_PIO(addr)		(inw((अचिन्हित दीर्घ)addr))
#घोषणा WRT_REG_WORD_PIO(addr, data)	(outw(data, (अचिन्हित दीर्घ)addr))

/*
 * Fibre Channel device definitions.
 */
#घोषणा WWN_SIZE		8	/* Size of WWPN, WWN & WWNN */
#घोषणा MAX_FIBRE_DEVICES_2100	512
#घोषणा MAX_FIBRE_DEVICES_2400	2048
#घोषणा MAX_FIBRE_DEVICES_LOOP	128
#घोषणा MAX_FIBRE_DEVICES_MAX	MAX_FIBRE_DEVICES_2400
#घोषणा LOOPID_MAP_SIZE		(ha->max_fibre_devices)
#घोषणा MAX_FIBRE_LUNS  	0xFFFF
#घोषणा	MAX_HOST_COUNT		16

/*
 * Host adapter शेष definitions.
 */
#घोषणा MAX_BUSES		1  /* We only have one bus today */
#घोषणा MIN_LUNS		8
#घोषणा MAX_LUNS		MAX_FIBRE_LUNS
#घोषणा MAX_CMDS_PER_LUN	255

/*
 * Fibre Channel device definitions.
 */
#घोषणा SNS_LAST_LOOP_ID_2100	0xfe
#घोषणा SNS_LAST_LOOP_ID_2300	0x7ff

#घोषणा LAST_LOCAL_LOOP_ID	0x7d
#घोषणा SNS_FL_PORT		0x7e
#घोषणा FABRIC_CONTROLLER	0x7f
#घोषणा SIMPLE_NAME_SERVER	0x80
#घोषणा SNS_FIRST_LOOP_ID	0x81
#घोषणा MANAGEMENT_SERVER	0xfe
#घोषणा BROADCAST		0xff

/*
 * There is no correspondence between an N-PORT id and an AL_PA.  Thereक्रमe the
 * valid range of an N-PORT id is 0 through 0x7ef.
 */
#घोषणा NPH_LAST_HANDLE		0x7ee
#घोषणा NPH_MGMT_SERVER		0x7ef		/*  FFFFEF */
#घोषणा NPH_SNS			0x7fc		/*  FFFFFC */
#घोषणा NPH_FABRIC_CONTROLLER	0x7fd		/*  FFFFFD */
#घोषणा NPH_F_PORT		0x7fe		/*  FFFFFE */
#घोषणा NPH_IP_BROADCAST	0x7ff		/*  FFFFFF */

#घोषणा NPH_SNS_LID(ha)	(IS_FWI2_CAPABLE(ha) ? NPH_SNS : SIMPLE_NAME_SERVER)

#घोषणा MAX_CMDSZ	16		/* SCSI maximum CDB size. */
#समावेश "qla_fw.h"

काष्ठा name_list_extended अणु
	काष्ठा get_name_list_extended *l;
	dma_addr_t		ldma;
	काष्ठा list_head	fcports;
	u32			size;
	u8			sent;
पूर्ण;
/*
 * Timeout समयr counts in seconds
 */
#घोषणा PORT_RETRY_TIME			1
#घोषणा LOOP_DOWN_TIMEOUT		60
#घोषणा LOOP_DOWN_TIME			255	/* 240 */
#घोषणा	LOOP_DOWN_RESET			(LOOP_DOWN_TIME - 30)

#घोषणा DEFAULT_OUTSTANDING_COMMANDS	4096
#घोषणा MIN_OUTSTANDING_COMMANDS	128

/* ISP request and response entry counts (37-65535) */
#घोषणा REQUEST_ENTRY_CNT_2100		128	/* Number of request entries. */
#घोषणा REQUEST_ENTRY_CNT_2200		2048	/* Number of request entries. */
#घोषणा REQUEST_ENTRY_CNT_24XX		2048	/* Number of request entries. */
#घोषणा REQUEST_ENTRY_CNT_83XX		8192	/* Number of request entries. */
#घोषणा RESPONSE_ENTRY_CNT_83XX		4096	/* Number of response entries.*/
#घोषणा RESPONSE_ENTRY_CNT_2100		64	/* Number of response entries.*/
#घोषणा RESPONSE_ENTRY_CNT_2300		512	/* Number of response entries.*/
#घोषणा RESPONSE_ENTRY_CNT_MQ		128	/* Number of response entries.*/
#घोषणा ATIO_ENTRY_CNT_24XX		4096	/* Number of ATIO entries. */
#घोषणा RESPONSE_ENTRY_CNT_FX00		256     /* Number of response entries.*/
#घोषणा FW_DEF_EXCHANGES_CNT 2048
#घोषणा FW_MAX_EXCHANGES_CNT (32 * 1024)
#घोषणा REDUCE_EXCHANGES_CNT  (8 * 1024)

काष्ठा req_que;
काष्ठा qla_tgt_sess;

/*
 * SCSI Request Block
 */
काष्ठा srb_cmd अणु
	काष्ठा scsi_cmnd *cmd;		/* Linux SCSI command pkt */
	uपूर्णांक32_t request_sense_length;
	uपूर्णांक32_t fw_sense_length;
	uपूर्णांक8_t *request_sense_ptr;
	काष्ठा ct6_dsd *ct6_ctx;
	काष्ठा crc_context *crc_ctx;
पूर्ण;

/*
 * SRB flag definitions
 */
#घोषणा SRB_DMA_VALID			BIT_0	/* Command sent to ISP */
#घोषणा SRB_FCP_CMND_DMA_VALID		BIT_12	/* DIF: DSD List valid */
#घोषणा SRB_CRC_CTX_DMA_VALID		BIT_2	/* DIF: context DMA valid */
#घोषणा SRB_CRC_PROT_DMA_VALID		BIT_4	/* DIF: prot DMA valid */
#घोषणा SRB_CRC_CTX_DSD_VALID		BIT_5	/* DIF: dsd_list valid */
#घोषणा SRB_WAKEUP_ON_COMP		BIT_6
#घोषणा SRB_DIF_BUNDL_DMA_VALID		BIT_7   /* DIF: DMA list valid */

/* To identअगरy अगर a srb is of T10-CRC type. @sp => srb_t poपूर्णांकer */
#घोषणा IS_PROT_IO(sp)	(sp->flags & SRB_CRC_CTX_DSD_VALID)

/*
 * 24 bit port ID type definition.
 */
प्रकार जोड़ अणु
	uपूर्णांक32_t b24 : 24;

	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
		uपूर्णांक8_t करोमुख्य;
		uपूर्णांक8_t area;
		uपूर्णांक8_t al_pa;
#या_अगर defined(__LITTLE_ENDIAN)
		uपूर्णांक8_t al_pa;
		uपूर्णांक8_t area;
		uपूर्णांक8_t करोमुख्य;
#अन्यथा
#त्रुटि "__BIG_ENDIAN or __LITTLE_ENDIAN must be defined!"
#पूर्ण_अगर
		uपूर्णांक8_t rsvd_1;
	पूर्ण b;
पूर्ण port_id_t;
#घोषणा INVALID_PORT_ID	0xFFFFFF
#घोषणा ISP_REG16_DISCONNECT 0xFFFF

अटल अंतरभूत le_id_t be_id_to_le(be_id_t id)
अणु
	le_id_t res;

	res.करोमुख्य = id.करोमुख्य;
	res.area   = id.area;
	res.al_pa  = id.al_pa;

	वापस res;
पूर्ण

अटल अंतरभूत be_id_t le_id_to_be(le_id_t id)
अणु
	be_id_t res;

	res.करोमुख्य = id.करोमुख्य;
	res.area   = id.area;
	res.al_pa  = id.al_pa;

	वापस res;
पूर्ण

अटल अंतरभूत port_id_t be_to_port_id(be_id_t id)
अणु
	port_id_t res;

	res.b.करोमुख्य = id.करोमुख्य;
	res.b.area   = id.area;
	res.b.al_pa  = id.al_pa;
	res.b.rsvd_1 = 0;

	वापस res;
पूर्ण

अटल अंतरभूत be_id_t port_id_to_be_id(port_id_t port_id)
अणु
	be_id_t res;

	res.करोमुख्य = port_id.b.करोमुख्य;
	res.area   = port_id.b.area;
	res.al_pa  = port_id.b.al_pa;

	वापस res;
पूर्ण

काष्ठा els_logo_payload अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t rsvd[3];
	uपूर्णांक8_t s_id[3];
	uपूर्णांक8_t rsvd1[1];
	uपूर्णांक8_t wwpn[WWN_SIZE];
पूर्ण;

काष्ठा els_plogi_payload अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t rsvd[3];
	__be32	data[112 / 4];
पूर्ण;

काष्ठा ct_arg अणु
	व्योम		*iocb;
	u16		nport_handle;
	dma_addr_t	req_dma;
	dma_addr_t	rsp_dma;
	u32		req_size;
	u32		rsp_size;
	u32		req_allocated_size;
	u32		rsp_allocated_size;
	व्योम		*req;
	व्योम		*rsp;
	port_id_t	id;
पूर्ण;

/*
 * SRB extensions.
 */
काष्ठा srb_iocb अणु
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक16_t flags;
#घोषणा SRB_LOGIN_RETRIED	BIT_0
#घोषणा SRB_LOGIN_COND_PLOGI	BIT_1
#घोषणा SRB_LOGIN_SKIP_PRLI	BIT_2
#घोषणा SRB_LOGIN_NVME_PRLI	BIT_3
#घोषणा SRB_LOGIN_PRLI_ONLY	BIT_4
			uपूर्णांक16_t data[2];
			u32 iop[2];
		पूर्ण logio;
		काष्ठा अणु
#घोषणा ELS_DCMD_TIMEOUT 20
#घोषणा ELS_DCMD_LOGO 0x5
			uपूर्णांक32_t flags;
			uपूर्णांक32_t els_cmd;
			काष्ठा completion comp;
			काष्ठा els_logo_payload *els_logo_pyld;
			dma_addr_t els_logo_pyld_dma;
		पूर्ण els_logo;
		काष्ठा els_plogi अणु
#घोषणा ELS_DCMD_PLOGI 0x3
			uपूर्णांक32_t flags;
			uपूर्णांक32_t els_cmd;
			काष्ठा completion comp;
			काष्ठा els_plogi_payload *els_plogi_pyld;
			काष्ठा els_plogi_payload *els_resp_pyld;
			u32 tx_size;
			u32 rx_size;
			dma_addr_t els_plogi_pyld_dma;
			dma_addr_t els_resp_pyld_dma;
			__le32	fw_status[3];
			__le16	comp_status;
			__le16	len;
		पूर्ण els_plogi;
		काष्ठा अणु
			/*
			 * Values क्रम flags field below are as
			 * defined in tsk_mgmt_entry काष्ठा
			 * क्रम control_flags field in qla_fw.h.
			 */
			uपूर्णांक64_t lun;
			uपूर्णांक32_t flags;
			uपूर्णांक32_t data;
			काष्ठा completion comp;
			__le16 comp_status;
		पूर्ण पंचांगf;
		काष्ठा अणु
#घोषणा SRB_FXDISC_REQ_DMA_VALID	BIT_0
#घोषणा SRB_FXDISC_RESP_DMA_VALID	BIT_1
#घोषणा SRB_FXDISC_REQ_DWRD_VALID	BIT_2
#घोषणा SRB_FXDISC_RSP_DWRD_VALID	BIT_3
#घोषणा FXDISC_TIMEOUT 20
			uपूर्णांक8_t flags;
			uपूर्णांक32_t req_len;
			uपूर्णांक32_t rsp_len;
			व्योम *req_addr;
			व्योम *rsp_addr;
			dma_addr_t req_dma_handle;
			dma_addr_t rsp_dma_handle;
			__le32 adapter_id;
			__le32 adapter_id_hi;
			__le16 req_func_type;
			__le32 req_data;
			__le32 req_data_extra;
			__le32 result;
			__le32 seq_number;
			__le16 fw_flags;
			काष्ठा completion fxiocb_comp;
			__le32 reserved_0;
			uपूर्णांक8_t reserved_1;
		पूर्ण fxiocb;
		काष्ठा अणु
			uपूर्णांक32_t cmd_hndl;
			__le16 comp_status;
			__le16 req_que_no;
			काष्ठा completion comp;
		पूर्ण abt;
		काष्ठा ct_arg ctarg;
#घोषणा MAX_IOCB_MB_REG 28
#घोषणा SIZखातापूर्ण_IOCB_MB_REG (MAX_IOCB_MB_REG * माप(uपूर्णांक16_t))
		काष्ठा अणु
			u16 in_mb[MAX_IOCB_MB_REG];	/* from FW */
			u16 out_mb[MAX_IOCB_MB_REG];	/* to FW */
			व्योम *out, *in;
			dma_addr_t out_dma, in_dma;
			काष्ठा completion comp;
			पूर्णांक rc;
		पूर्ण mbx;
		काष्ठा अणु
			काष्ठा imm_ntfy_from_isp *ntfy;
		पूर्ण nack;
		काष्ठा अणु
			__le16 comp_status;
			__le16 rsp_pyld_len;
			uपूर्णांक8_t	aen_op;
			व्योम *desc;

			/* These are only used with ls4 requests */
			पूर्णांक cmd_len;
			पूर्णांक rsp_len;
			dma_addr_t cmd_dma;
			dma_addr_t rsp_dma;
			क्रमागत nvmefc_fcp_datadir dir;
			uपूर्णांक32_t dl;
			uपूर्णांक32_t समयout_sec;
			काष्ठा	list_head   entry;
		पूर्ण nvme;
		काष्ठा अणु
			u16 cmd;
			u16 vp_index;
		पूर्ण ctrlvp;
	पूर्ण u;

	काष्ठा समयr_list समयr;
	व्योम (*समयout)(व्योम *);
पूर्ण;

/* Values क्रम srb_ctx type */
#घोषणा SRB_LOGIN_CMD	1
#घोषणा SRB_LOGOUT_CMD	2
#घोषणा SRB_ELS_CMD_RPT 3
#घोषणा SRB_ELS_CMD_HST 4
#घोषणा SRB_CT_CMD	5
#घोषणा SRB_ADISC_CMD	6
#घोषणा SRB_TM_CMD	7
#घोषणा SRB_SCSI_CMD	8
#घोषणा SRB_BIDI_CMD	9
#घोषणा SRB_FXIOCB_DCMD	10
#घोषणा SRB_FXIOCB_BCMD	11
#घोषणा SRB_ABT_CMD	12
#घोषणा SRB_ELS_DCMD	13
#घोषणा SRB_MB_IOCB	14
#घोषणा SRB_CT_PTHRU_CMD 15
#घोषणा SRB_NACK_PLOGI	16
#घोषणा SRB_NACK_PRLI	17
#घोषणा SRB_NACK_LOGO	18
#घोषणा SRB_NVME_CMD	19
#घोषणा SRB_NVME_LS	20
#घोषणा SRB_PRLI_CMD	21
#घोषणा SRB_CTRL_VP	22
#घोषणा SRB_PRLO_CMD	23

क्रमागत अणु
	TYPE_SRB,
	TYPE_TGT_CMD,
	TYPE_TGT_TMCMD,		/* task management */
पूर्ण;

काष्ठा iocb_resource अणु
	u8 res_type;
	u8 pad;
	u16 iocb_cnt;
पूर्ण;

प्रकार काष्ठा srb अणु
	/*
	 * Do not move cmd_type field, it needs to
	 * line up with qla_tgt_cmd->cmd_type
	 */
	uपूर्णांक8_t cmd_type;
	uपूर्णांक8_t pad[3];
	काष्ठा iocb_resource iores;
	काष्ठा kref cmd_kref;	/* need to migrate ref_count over to this */
	व्योम *priv;
	रुको_queue_head_t nvme_ls_रुकोq;
	काष्ठा fc_port *fcport;
	काष्ठा scsi_qla_host *vha;
	अचिन्हित पूर्णांक start_समयr:1;

	uपूर्णांक32_t handle;
	uपूर्णांक16_t flags;
	uपूर्णांक16_t type;
	स्थिर अक्षर *name;
	पूर्णांक iocbs;
	काष्ठा qla_qpair *qpair;
	काष्ठा srb *cmd_sp;
	काष्ठा list_head elem;
	u32 gen1;	/* scratch */
	u32 gen2;	/* scratch */
	पूर्णांक rc;
	पूर्णांक retry_count;
	काष्ठा completion *comp;
	जोड़ अणु
		काष्ठा srb_iocb iocb_cmd;
		काष्ठा bsg_job *bsg_job;
		काष्ठा srb_cmd scmd;
	पूर्ण u;
	/*
	 * Report completion status @res and call sp_put(@sp). @res is
	 * an NVMe status code, a SCSI result (e.g. DID_OK << 16) or a
	 * QLA_* status value.
	 */
	व्योम (*करोne)(काष्ठा srb *sp, पूर्णांक res);
	/* Stop the समयr and मुक्त @sp. Only used by the FCP code. */
	व्योम (*मुक्त)(काष्ठा srb *sp);
	/*
	 * Call nvme_निजी->fd->करोne() and मुक्त @sp. Only used by the NVMe
	 * code.
	 */
	व्योम (*put_fn)(काष्ठा kref *kref);
पूर्ण srb_t;

#घोषणा GET_CMD_SP(sp) (sp->u.scmd.cmd)

#घोषणा GET_CMD_SENSE_LEN(sp) \
	(sp->u.scmd.request_sense_length)
#घोषणा SET_CMD_SENSE_LEN(sp, len) \
	(sp->u.scmd.request_sense_length = len)
#घोषणा GET_CMD_SENSE_PTR(sp) \
	(sp->u.scmd.request_sense_ptr)
#घोषणा SET_CMD_SENSE_PTR(sp, ptr) \
	(sp->u.scmd.request_sense_ptr = ptr)
#घोषणा GET_FW_SENSE_LEN(sp) \
	(sp->u.scmd.fw_sense_length)
#घोषणा SET_FW_SENSE_LEN(sp, len) \
	(sp->u.scmd.fw_sense_length = len)

काष्ठा msg_echo_lb अणु
	dma_addr_t send_dma;
	dma_addr_t rcv_dma;
	uपूर्णांक16_t req_sg_cnt;
	uपूर्णांक16_t rsp_sg_cnt;
	uपूर्णांक16_t options;
	uपूर्णांक32_t transfer_size;
	uपूर्णांक32_t iteration_count;
पूर्ण;

/*
 * ISP I/O Register Set काष्ठाure definitions.
 */
काष्ठा device_reg_2xxx अणु
	__le16	flash_address; 	/* Flash BIOS address */
	__le16	flash_data;		/* Flash BIOS data */
	__le16	unused_1[1];		/* Gap */
	__le16	ctrl_status;		/* Control/Status */
#घोषणा CSR_FLASH_64K_BANK	BIT_3	/* Flash upper 64K bank select */
#घोषणा CSR_FLASH_ENABLE	BIT_1	/* Flash BIOS Read/Write enable */
#घोषणा CSR_ISP_SOFT_RESET	BIT_0	/* ISP soft reset */

	__le16	ictrl;			/* Interrupt control */
#घोषणा ICR_EN_INT		BIT_15	/* ISP enable पूर्णांकerrupts. */
#घोषणा ICR_EN_RISC		BIT_3	/* ISP enable RISC पूर्णांकerrupts. */

	__le16	istatus;		/* Interrupt status */
#घोषणा ISR_RISC_INT		BIT_3	/* RISC पूर्णांकerrupt */

	__le16	semaphore;		/* Semaphore */
	__le16	nvram;			/* NVRAM रेजिस्टर. */
#घोषणा NVR_DESELECT		0
#घोषणा NVR_BUSY		BIT_15
#घोषणा NVR_WRT_ENABLE		BIT_14	/* Write enable */
#घोषणा NVR_PR_ENABLE		BIT_13	/* Protection रेजिस्टर enable */
#घोषणा NVR_DATA_IN		BIT_3
#घोषणा NVR_DATA_OUT		BIT_2
#घोषणा NVR_SELECT		BIT_1
#घोषणा NVR_CLOCK		BIT_0

#घोषणा NVR_WAIT_CNT		20000

	जोड़ अणु
		काष्ठा अणु
			__le16	mailbox0;
			__le16	mailbox1;
			__le16	mailbox2;
			__le16	mailbox3;
			__le16	mailbox4;
			__le16	mailbox5;
			__le16	mailbox6;
			__le16	mailbox7;
			__le16	unused_2[59];	/* Gap */
		पूर्ण __attribute__((packed)) isp2100;
		काष्ठा अणु
						/* Request Queue */
			__le16	req_q_in;	/*  In-Poपूर्णांकer */
			__le16	req_q_out;	/*  Out-Poपूर्णांकer */
						/* Response Queue */
			__le16	rsp_q_in;	/*  In-Poपूर्णांकer */
			__le16	rsp_q_out;	/*  Out-Poपूर्णांकer */

						/* RISC to Host Status */
			__le32	host_status;
#घोषणा HSR_RISC_INT		BIT_15	/* RISC पूर्णांकerrupt */
#घोषणा HSR_RISC_PAUSED		BIT_8	/* RISC Paused */

					/* Host to Host Semaphore */
			__le16	host_semaphore;
			__le16	unused_3[17];	/* Gap */
			__le16	mailbox0;
			__le16	mailbox1;
			__le16	mailbox2;
			__le16	mailbox3;
			__le16	mailbox4;
			__le16	mailbox5;
			__le16	mailbox6;
			__le16	mailbox7;
			__le16	mailbox8;
			__le16	mailbox9;
			__le16	mailbox10;
			__le16	mailbox11;
			__le16	mailbox12;
			__le16	mailbox13;
			__le16	mailbox14;
			__le16	mailbox15;
			__le16	mailbox16;
			__le16	mailbox17;
			__le16	mailbox18;
			__le16	mailbox19;
			__le16	mailbox20;
			__le16	mailbox21;
			__le16	mailbox22;
			__le16	mailbox23;
			__le16	mailbox24;
			__le16	mailbox25;
			__le16	mailbox26;
			__le16	mailbox27;
			__le16	mailbox28;
			__le16	mailbox29;
			__le16	mailbox30;
			__le16	mailbox31;
			__le16	fb_cmd;
			__le16	unused_4[10];	/* Gap */
		पूर्ण __attribute__((packed)) isp2300;
	पूर्ण u;

	__le16	fpm_diag_config;
	__le16	unused_5[0x4];		/* Gap */
	__le16	risc_hw;
	__le16	unused_5_1;		/* Gap */
	__le16	pcr;			/* Processor Control Register. */
	__le16	unused_6[0x5];		/* Gap */
	__le16	mctr;			/* Memory Configuration and Timing. */
	__le16	unused_7[0x3];		/* Gap */
	__le16	fb_cmd_2100;		/* Unused on 23XX */
	__le16	unused_8[0x3];		/* Gap */
	__le16	hccr;			/* Host command & control रेजिस्टर. */
#घोषणा HCCR_HOST_INT		BIT_7	/* Host पूर्णांकerrupt bit */
#घोषणा HCCR_RISC_PAUSE		BIT_5	/* Pause mode bit */
					/* HCCR commands */
#घोषणा HCCR_RESET_RISC		0x1000	/* Reset RISC */
#घोषणा HCCR_PAUSE_RISC		0x2000	/* Pause RISC */
#घोषणा HCCR_RELEASE_RISC	0x3000	/* Release RISC from reset. */
#घोषणा HCCR_SET_HOST_INT	0x5000	/* Set host पूर्णांकerrupt */
#घोषणा HCCR_CLR_HOST_INT	0x6000	/* Clear HOST पूर्णांकerrupt */
#घोषणा HCCR_CLR_RISC_INT	0x7000	/* Clear RISC पूर्णांकerrupt */
#घोषणा	HCCR_DISABLE_PARITY_PAUSE 0x4001 /* Disable parity error RISC छोड़ो. */
#घोषणा HCCR_ENABLE_PARITY	0xA000	/* Enable PARITY पूर्णांकerrupt */

	__le16	unused_9[5];		/* Gap */
	__le16	gpiod;			/* GPIO Data रेजिस्टर. */
	__le16	gpioe;			/* GPIO Enable रेजिस्टर. */
#घोषणा GPIO_LED_MASK			0x00C0
#घोषणा GPIO_LED_GREEN_OFF_AMBER_OFF	0x0000
#घोषणा GPIO_LED_GREEN_ON_AMBER_OFF	0x0040
#घोषणा GPIO_LED_GREEN_OFF_AMBER_ON	0x0080
#घोषणा GPIO_LED_GREEN_ON_AMBER_ON	0x00C0
#घोषणा GPIO_LED_ALL_OFF		0x0000
#घोषणा GPIO_LED_RED_ON_OTHER_OFF	0x0001	/* isp2322 */
#घोषणा GPIO_LED_RGA_ON			0x00C1	/* isp2322: red green amber */

	जोड़ अणु
		काष्ठा अणु
			__le16	unused_10[8];	/* Gap */
			__le16	mailbox8;
			__le16	mailbox9;
			__le16	mailbox10;
			__le16	mailbox11;
			__le16	mailbox12;
			__le16	mailbox13;
			__le16	mailbox14;
			__le16	mailbox15;
			__le16	mailbox16;
			__le16	mailbox17;
			__le16	mailbox18;
			__le16	mailbox19;
			__le16	mailbox20;
			__le16	mailbox21;
			__le16	mailbox22;
			__le16	mailbox23;	/* Also probe reg. */
		पूर्ण __attribute__((packed)) isp2200;
	पूर्ण u_end;
पूर्ण;

काष्ठा device_reg_25xxmq अणु
	__le32	req_q_in;
	__le32	req_q_out;
	__le32	rsp_q_in;
	__le32	rsp_q_out;
	__le32	atio_q_in;
	__le32	atio_q_out;
पूर्ण;


काष्ठा device_reg_fx00 अणु
	__le32	mailbox0;		/* 00 */
	__le32	mailbox1;		/* 04 */
	__le32	mailbox2;		/* 08 */
	__le32	mailbox3;		/* 0C */
	__le32	mailbox4;		/* 10 */
	__le32	mailbox5;		/* 14 */
	__le32	mailbox6;		/* 18 */
	__le32	mailbox7;		/* 1C */
	__le32	mailbox8;		/* 20 */
	__le32	mailbox9;		/* 24 */
	__le32	mailbox10;		/* 28 */
	__le32	mailbox11;
	__le32	mailbox12;
	__le32	mailbox13;
	__le32	mailbox14;
	__le32	mailbox15;
	__le32	mailbox16;
	__le32	mailbox17;
	__le32	mailbox18;
	__le32	mailbox19;
	__le32	mailbox20;
	__le32	mailbox21;
	__le32	mailbox22;
	__le32	mailbox23;
	__le32	mailbox24;
	__le32	mailbox25;
	__le32	mailbox26;
	__le32	mailbox27;
	__le32	mailbox28;
	__le32	mailbox29;
	__le32	mailbox30;
	__le32	mailbox31;
	__le32	aenmailbox0;
	__le32	aenmailbox1;
	__le32	aenmailbox2;
	__le32	aenmailbox3;
	__le32	aenmailbox4;
	__le32	aenmailbox5;
	__le32	aenmailbox6;
	__le32	aenmailbox7;
	/* Request Queue. */
	__le32	req_q_in;		/* A0 - Request Queue In-Poपूर्णांकer */
	__le32	req_q_out;		/* A4 - Request Queue Out-Poपूर्णांकer */
	/* Response Queue. */
	__le32	rsp_q_in;		/* A8 - Response Queue In-Poपूर्णांकer */
	__le32	rsp_q_out;		/* AC - Response Queue Out-Poपूर्णांकer */
	/* Init values shaकरोwed on FW Up Event */
	__le32	initval0;		/* B0 */
	__le32	initval1;		/* B4 */
	__le32	initval2;		/* B8 */
	__le32	initval3;		/* BC */
	__le32	initval4;		/* C0 */
	__le32	initval5;		/* C4 */
	__le32	initval6;		/* C8 */
	__le32	initval7;		/* CC */
	__le32	fwheartbeat;		/* D0 */
	__le32	pseuकरोaen;		/* D4 */
पूर्ण;



प्रकार जोड़ अणु
		काष्ठा device_reg_2xxx isp;
		काष्ठा device_reg_24xx isp24;
		काष्ठा device_reg_25xxmq isp25mq;
		काष्ठा device_reg_82xx isp82;
		काष्ठा device_reg_fx00 ispfx00;
पूर्ण __iomem device_reg_t;

#घोषणा ISP_REQ_Q_IN(ha, reg) \
	(IS_QLA2100(ha) || IS_QLA2200(ha) ? \
	 &(reg)->u.isp2100.mailbox4 : \
	 &(reg)->u.isp2300.req_q_in)
#घोषणा ISP_REQ_Q_OUT(ha, reg) \
	(IS_QLA2100(ha) || IS_QLA2200(ha) ? \
	 &(reg)->u.isp2100.mailbox4 : \
	 &(reg)->u.isp2300.req_q_out)
#घोषणा ISP_RSP_Q_IN(ha, reg) \
	(IS_QLA2100(ha) || IS_QLA2200(ha) ? \
	 &(reg)->u.isp2100.mailbox5 : \
	 &(reg)->u.isp2300.rsp_q_in)
#घोषणा ISP_RSP_Q_OUT(ha, reg) \
	(IS_QLA2100(ha) || IS_QLA2200(ha) ? \
	 &(reg)->u.isp2100.mailbox5 : \
	 &(reg)->u.isp2300.rsp_q_out)

#घोषणा ISP_ATIO_Q_IN(vha) (vha->hw->tgt.atio_q_in)
#घोषणा ISP_ATIO_Q_OUT(vha) (vha->hw->tgt.atio_q_out)

#घोषणा MAILBOX_REG(ha, reg, num) \
	(IS_QLA2100(ha) || IS_QLA2200(ha) ? \
	 (num < 8 ? \
	  &(reg)->u.isp2100.mailbox0 + (num) : \
	  &(reg)->u_end.isp2200.mailbox8 + (num) - 8) : \
	 &(reg)->u.isp2300.mailbox0 + (num))
#घोषणा RD_MAILBOX_REG(ha, reg, num) \
	rd_reg_word(MAILBOX_REG(ha, reg, num))
#घोषणा WRT_MAILBOX_REG(ha, reg, num, data) \
	wrt_reg_word(MAILBOX_REG(ha, reg, num), data)

#घोषणा FB_CMD_REG(ha, reg) \
	(IS_QLA2100(ha) || IS_QLA2200(ha) ? \
	 &(reg)->fb_cmd_2100 : \
	 &(reg)->u.isp2300.fb_cmd)
#घोषणा RD_FB_CMD_REG(ha, reg) \
	rd_reg_word(FB_CMD_REG(ha, reg))
#घोषणा WRT_FB_CMD_REG(ha, reg, data) \
	wrt_reg_word(FB_CMD_REG(ha, reg), data)

प्रकार काष्ठा अणु
	uपूर्णांक32_t	out_mb;		/* outbound from driver */
	uपूर्णांक32_t	in_mb;			/* Incoming from RISC */
	uपूर्णांक16_t	mb[MAILBOX_REGISTER_COUNT];
	दीर्घ		buf_size;
	व्योम		*bufp;
	uपूर्णांक32_t	tov;
	uपूर्णांक8_t		flags;
#घोषणा MBX_DMA_IN	BIT_0
#घोषणा	MBX_DMA_OUT	BIT_1
#घोषणा IOCTL_CMD	BIT_2
पूर्ण mbx_cmd_t;

काष्ठा mbx_cmd_32 अणु
	uपूर्णांक32_t	out_mb;		/* outbound from driver */
	uपूर्णांक32_t	in_mb;			/* Incoming from RISC */
	uपूर्णांक32_t	mb[MAILBOX_REGISTER_COUNT];
	दीर्घ		buf_size;
	व्योम		*bufp;
	uपूर्णांक32_t	tov;
	uपूर्णांक8_t		flags;
#घोषणा MBX_DMA_IN	BIT_0
#घोषणा	MBX_DMA_OUT	BIT_1
#घोषणा IOCTL_CMD	BIT_2
पूर्ण;


#घोषणा	MBX_TOV_SECONDS	30

/*
 *  ISP product identअगरication definitions in mailboxes after reset.
 */
#घोषणा PROD_ID_1		0x4953
#घोषणा PROD_ID_2		0x0000
#घोषणा PROD_ID_2a		0x5020
#घोषणा PROD_ID_3		0x2020

/*
 * ISP mailbox Self-Test status codes
 */
#घोषणा MBS_FRM_ALIVE		0	/* Firmware Alive. */
#घोषणा MBS_CHKSUM_ERR		1	/* Checksum Error. */
#घोषणा MBS_BUSY		4	/* Busy. */

/*
 * ISP mailbox command complete status codes
 */
#घोषणा MBS_COMMAND_COMPLETE		0x4000
#घोषणा MBS_INVALID_COMMAND		0x4001
#घोषणा MBS_HOST_INTERFACE_ERROR	0x4002
#घोषणा MBS_TEST_FAILED			0x4003
#घोषणा MBS_COMMAND_ERROR		0x4005
#घोषणा MBS_COMMAND_PARAMETER_ERROR	0x4006
#घोषणा MBS_PORT_ID_USED		0x4007
#घोषणा MBS_LOOP_ID_USED		0x4008
#घोषणा MBS_ALL_IDS_IN_USE		0x4009
#घोषणा MBS_NOT_LOGGED_IN		0x400A
#घोषणा MBS_LINK_DOWN_ERROR		0x400B
#घोषणा MBS_DIAG_ECHO_TEST_ERROR	0x400C

अटल अंतरभूत bool qla2xxx_is_valid_mbs(अचिन्हित पूर्णांक mbs)
अणु
	वापस MBS_COMMAND_COMPLETE <= mbs && mbs <= MBS_DIAG_ECHO_TEST_ERROR;
पूर्ण

/*
 * ISP mailbox asynchronous event status codes
 */
#घोषणा MBA_ASYNC_EVENT		0x8000	/* Asynchronous event. */
#घोषणा MBA_RESET		0x8001	/* Reset Detected. */
#घोषणा MBA_SYSTEM_ERR		0x8002	/* System Error. */
#घोषणा MBA_REQ_TRANSFER_ERR	0x8003	/* Request Transfer Error. */
#घोषणा MBA_RSP_TRANSFER_ERR	0x8004	/* Response Transfer Error. */
#घोषणा MBA_WAKEUP_THRES	0x8005	/* Request Queue Wake-up. */
#घोषणा MBA_LIP_OCCURRED	0x8010	/* Loop Initialization Procedure */
					/* occurred. */
#घोषणा MBA_LOOP_UP		0x8011	/* FC Loop UP. */
#घोषणा MBA_LOOP_DOWN		0x8012	/* FC Loop Down. */
#घोषणा MBA_LIP_RESET		0x8013	/* LIP reset occurred. */
#घोषणा MBA_PORT_UPDATE		0x8014	/* Port Database update. */
#घोषणा MBA_RSCN_UPDATE		0x8015	/* Register State Chg Notअगरication. */
#घोषणा MBA_LIP_F8		0x8016	/* Received a LIP F8. */
#घोषणा MBA_LOOP_INIT_ERR	0x8017	/* Loop Initialization Error. */
#घोषणा MBA_FABRIC_AUTH_REQ	0x801b	/* Fabric Authentication Required. */
#घोषणा MBA_CONGN_NOTI_RECV	0x801e	/* Congestion Notअगरication Received */
#घोषणा MBA_SCSI_COMPLETION	0x8020	/* SCSI Command Complete. */
#घोषणा MBA_CTIO_COMPLETION	0x8021	/* CTIO Complete. */
#घोषणा MBA_IP_COMPLETION	0x8022	/* IP Transmit Command Complete. */
#घोषणा MBA_IP_RECEIVE		0x8023	/* IP Received. */
#घोषणा MBA_IP_BROADCAST	0x8024	/* IP Broadcast Received. */
#घोषणा MBA_IP_LOW_WATER_MARK	0x8025	/* IP Low Water Mark reached. */
#घोषणा MBA_IP_RCV_BUFFER_EMPTY 0x8026	/* IP receive buffer queue empty. */
#घोषणा MBA_IP_HDR_DATA_SPLIT	0x8027	/* IP header/data splitting feature */
					/* used. */
#घोषणा MBA_TRACE_NOTIFICATION	0x8028	/* Trace/Diagnostic notअगरication. */
#घोषणा MBA_POINT_TO_POINT	0x8030	/* Poपूर्णांक to poपूर्णांक mode. */
#घोषणा MBA_CMPLT_1_16BIT	0x8031	/* Completion 1 16bit IOSB. */
#घोषणा MBA_CMPLT_2_16BIT	0x8032	/* Completion 2 16bit IOSB. */
#घोषणा MBA_CMPLT_3_16BIT	0x8033	/* Completion 3 16bit IOSB. */
#घोषणा MBA_CMPLT_4_16BIT	0x8034	/* Completion 4 16bit IOSB. */
#घोषणा MBA_CMPLT_5_16BIT	0x8035	/* Completion 5 16bit IOSB. */
#घोषणा MBA_CHG_IN_CONNECTION	0x8036	/* Change in connection mode. */
#घोषणा MBA_RIO_RESPONSE	0x8040	/* RIO response queue update. */
#घोषणा MBA_ZIO_RESPONSE	0x8040	/* ZIO response queue update. */
#घोषणा MBA_CMPLT_2_32BIT	0x8042	/* Completion 2 32bit IOSB. */
#घोषणा MBA_BYPASS_NOTIFICATION	0x8043	/* Auto bypass notअगरication. */
#घोषणा MBA_DISCARD_RND_FRAME	0x8048	/* discard RND frame due to error. */
#घोषणा MBA_REJECTED_FCP_CMD	0x8049	/* rejected FCP_CMD. */
#घोषणा MBA_FW_NOT_STARTED	0x8050	/* Firmware not started */
#घोषणा MBA_FW_STARTING		0x8051	/* Firmware starting */
#घोषणा MBA_FW_RESTART_CMPLT	0x8060	/* Firmware restart complete */
#घोषणा MBA_INIT_REQUIRED	0x8061	/* Initialization required */
#घोषणा MBA_SHUTDOWN_REQUESTED	0x8062	/* Shutकरोwn Requested */
#घोषणा MBA_TEMPERATURE_ALERT	0x8070	/* Temperature Alert */
#घोषणा MBA_DPORT_DIAGNOSTICS	0x8080	/* D-port Diagnostics */
#घोषणा MBA_TRANS_INSERT	0x8130	/* Transceiver Insertion */
#घोषणा MBA_TRANS_REMOVE	0x8131	/* Transceiver Removal */
#घोषणा MBA_FW_INIT_FAILURE	0x8401	/* Firmware initialization failure */
#घोषणा MBA_MIRROR_LUN_CHANGE	0x8402	/* Mirror LUN State Change
					   Notअगरication */
#घोषणा MBA_FW_POLL_STATE	0x8600  /* Firmware in poll diagnostic state */
#घोषणा MBA_FW_RESET_FCT	0x8502	/* Firmware reset factory शेषs */
#घोषणा MBA_FW_INIT_INPROGRESS	0x8500	/* Firmware boot in progress */
/* 83XX FCoE specअगरic */
#घोषणा MBA_IDC_AEN		0x8200  /* FCoE: NIC Core state change AEN */

/* Interrupt type codes */
#घोषणा INTR_ROM_MB_SUCCESS		0x1
#घोषणा INTR_ROM_MB_FAILED		0x2
#घोषणा INTR_MB_SUCCESS			0x10
#घोषणा INTR_MB_FAILED			0x11
#घोषणा INTR_ASYNC_EVENT		0x12
#घोषणा INTR_RSP_QUE_UPDATE		0x13
#घोषणा INTR_RSP_QUE_UPDATE_83XX	0x14
#घोषणा INTR_ATIO_QUE_UPDATE		0x1C
#घोषणा INTR_ATIO_RSP_QUE_UPDATE	0x1D
#घोषणा INTR_ATIO_QUE_UPDATE_27XX	0x1E

/* ISP mailbox loopback echo diagnostic error code */
#घोषणा MBS_LB_RESET	0x17
/*
 * Firmware options 1, 2, 3.
 */
#घोषणा FO1_AE_ON_LIPF8			BIT_0
#घोषणा FO1_AE_ALL_LIP_RESET		BIT_1
#घोषणा FO1_CTIO_RETRY			BIT_3
#घोषणा FO1_DISABLE_LIP_F7_SW		BIT_4
#घोषणा FO1_DISABLE_100MS_LOS_WAIT	BIT_5
#घोषणा FO1_DISABLE_GPIO6_7		BIT_6	/* LED bits */
#घोषणा FO1_AE_ON_LOOP_INIT_ERR		BIT_7
#घोषणा FO1_SET_EMPHASIS_SWING		BIT_8
#घोषणा FO1_AE_AUTO_BYPASS		BIT_9
#घोषणा FO1_ENABLE_PURE_IOCB		BIT_10
#घोषणा FO1_AE_PLOGI_RJT		BIT_11
#घोषणा FO1_ENABLE_ABORT_SEQUENCE	BIT_12
#घोषणा FO1_AE_QUEUE_FULL		BIT_13

#घोषणा FO2_ENABLE_ATIO_TYPE_3		BIT_0
#घोषणा FO2_REV_LOOPBACK		BIT_1

#घोषणा FO3_ENABLE_EMERG_IOCB		BIT_0
#घोषणा FO3_AE_RND_ERROR		BIT_1

/* 24XX additional firmware options */
#घोषणा ADD_FO_COUNT			3
#घोषणा ADD_FO1_DISABLE_GPIO_LED_CTRL	BIT_6	/* LED bits */
#घोषणा ADD_FO1_ENABLE_PUREX_IOCB	BIT_10

#घोषणा ADD_FO2_ENABLE_SEL_CLS2		BIT_5

#घोषणा ADD_FO3_NO_ABT_ON_LINK_DOWN	BIT_14

/*
 * ISP mailbox commands
 */
#घोषणा MBC_LOAD_RAM			1	/* Load RAM. */
#घोषणा MBC_EXECUTE_FIRMWARE		2	/* Execute firmware. */
#घोषणा MBC_READ_RAM_WORD		5	/* Read RAM word. */
#घोषणा MBC_MAILBOX_REGISTER_TEST	6	/* Wrap incoming mailboxes */
#घोषणा MBC_VERIFY_CHECKSUM		7	/* Verअगरy checksum. */
#घोषणा MBC_GET_FIRMWARE_VERSION	8	/* Get firmware revision. */
#घोषणा MBC_LOAD_RISC_RAM		9	/* Load RAM command. */
#घोषणा MBC_DUMP_RISC_RAM		0xa	/* Dump RAM command. */
#घोषणा MBC_SECURE_FLASH_UPDATE		0xa	/* Secure Flash Update(28xx) */
#घोषणा MBC_LOAD_RISC_RAM_EXTENDED	0xb	/* Load RAM extended. */
#घोषणा MBC_DUMP_RISC_RAM_EXTENDED	0xc	/* Dump RAM extended. */
#घोषणा MBC_WRITE_RAM_WORD_EXTENDED	0xd	/* Write RAM word extended */
#घोषणा MBC_READ_RAM_EXTENDED		0xf	/* Read RAM extended. */
#घोषणा MBC_IOCB_COMMAND		0x12	/* Execute IOCB command. */
#घोषणा MBC_STOP_FIRMWARE		0x14	/* Stop firmware. */
#घोषणा MBC_ABORT_COMMAND		0x15	/* Abort IOCB command. */
#घोषणा MBC_ABORT_DEVICE		0x16	/* Abort device (ID/LUN). */
#घोषणा MBC_ABORT_TARGET		0x17	/* Abort target (ID). */
#घोषणा MBC_RESET			0x18	/* Reset. */
#घोषणा MBC_GET_ADAPTER_LOOP_ID		0x20	/* Get loop id of ISP2200. */
#घोषणा MBC_GET_SET_ZIO_THRESHOLD	0x21	/* Get/SET ZIO THRESHOLD. */
#घोषणा MBC_GET_RETRY_COUNT		0x22	/* Get f/w retry cnt/delay. */
#घोषणा MBC_DISABLE_VI			0x24	/* Disable VI operation. */
#घोषणा MBC_ENABLE_VI			0x25	/* Enable VI operation. */
#घोषणा MBC_GET_FIRMWARE_OPTION		0x28	/* Get Firmware Options. */
#घोषणा MBC_GET_MEM_OFFLOAD_CNTRL_STAT	0x34	/* Memory Offload ctrl/Stat*/
#घोषणा MBC_SET_FIRMWARE_OPTION		0x38	/* Set Firmware Options. */
#घोषणा MBC_SET_GET_FC_LED_CONFIG	0x3b	/* Set/Get FC LED config */
#घोषणा MBC_LOOP_PORT_BYPASS		0x40	/* Loop Port Bypass. */
#घोषणा MBC_LOOP_PORT_ENABLE		0x41	/* Loop Port Enable. */
#घोषणा MBC_GET_RESOURCE_COUNTS		0x42	/* Get Resource Counts. */
#घोषणा MBC_NON_PARTICIPATE		0x43	/* Non-Participating Mode. */
#घोषणा MBC_DIAGNOSTIC_ECHO		0x44	/* Diagnostic echo. */
#घोषणा MBC_DIAGNOSTIC_LOOP_BACK	0x45	/* Diagnostic loop back. */
#घोषणा MBC_ONLINE_SELF_TEST		0x46	/* Online self-test. */
#घोषणा MBC_ENHANCED_GET_PORT_DATABASE	0x47	/* Get port database + login */
#घोषणा MBC_CONFIGURE_VF		0x4b	/* Configure VFs */
#घोषणा MBC_RESET_LINK_STATUS		0x52	/* Reset Link Error Status */
#घोषणा MBC_IOCB_COMMAND_A64		0x54	/* Execute IOCB command (64) */
#घोषणा MBC_PORT_LOGOUT			0x56	/* Port Logout request */
#घोषणा MBC_SEND_RNID_ELS		0x57	/* Send RNID ELS request */
#घोषणा MBC_SET_RNID_PARAMS		0x59	/* Set RNID parameters */
#घोषणा MBC_GET_RNID_PARAMS		0x5a	/* Get RNID parameters */
#घोषणा MBC_DATA_RATE			0x5d	/* Data Rate */
#घोषणा MBC_INITIALIZE_FIRMWARE		0x60	/* Initialize firmware */
#घोषणा MBC_INITIATE_LIP		0x62	/* Initiate Loop */
						/* Initialization Procedure */
#घोषणा MBC_GET_FC_AL_POSITION_MAP	0x63	/* Get FC_AL Position Map. */
#घोषणा MBC_GET_PORT_DATABASE		0x64	/* Get Port Database. */
#घोषणा MBC_CLEAR_ACA			0x65	/* Clear ACA. */
#घोषणा MBC_TARGET_RESET		0x66	/* Target Reset. */
#घोषणा MBC_CLEAR_TASK_SET		0x67	/* Clear Task Set. */
#घोषणा MBC_ABORT_TASK_SET		0x68	/* Abort Task Set. */
#घोषणा MBC_GET_FIRMWARE_STATE		0x69	/* Get firmware state. */
#घोषणा MBC_GET_PORT_NAME		0x6a	/* Get port name. */
#घोषणा MBC_GET_LINK_STATUS		0x6b	/* Get port link status. */
#घोषणा MBC_LIP_RESET			0x6c	/* LIP reset. */
#घोषणा MBC_SEND_SNS_COMMAND		0x6e	/* Send Simple Name Server */
						/* commandd. */
#घोषणा MBC_LOGIN_FABRIC_PORT		0x6f	/* Login fabric port. */
#घोषणा MBC_SEND_CHANGE_REQUEST		0x70	/* Send Change Request. */
#घोषणा MBC_LOGOUT_FABRIC_PORT		0x71	/* Logout fabric port. */
#घोषणा MBC_LIP_FULL_LOGIN		0x72	/* Full login LIP. */
#घोषणा MBC_LOGIN_LOOP_PORT		0x74	/* Login Loop Port. */
#घोषणा MBC_PORT_NODE_NAME_LIST		0x75	/* Get port/node name list. */
#घोषणा MBC_INITIALIZE_RECEIVE_QUEUE	0x77	/* Initialize receive queue */
#घोषणा MBC_UNLOAD_IP			0x79	/* Shutकरोwn IP */
#घोषणा MBC_GET_ID_LIST			0x7C	/* Get Port ID list. */
#घोषणा MBC_SEND_LFA_COMMAND		0x7D	/* Send Loop Fabric Address */
#घोषणा MBC_LUN_RESET			0x7E	/* Send LUN reset */

/*
 * all the Mt. Rainier mailbox command codes that clash with FC/FCoE ones
 * should be defined with MBC_MR_*
 */
#घोषणा MBC_MR_DRV_SHUTDOWN		0x6A

/*
 * ISP24xx mailbox commands
 */
#घोषणा MBC_WRITE_SERDES		0x3	/* Write serdes word. */
#घोषणा MBC_READ_SERDES			0x4	/* Read serdes word. */
#घोषणा MBC_LOAD_DUMP_MPI_RAM		0x5	/* Load/Dump MPI RAM. */
#घोषणा MBC_SERDES_PARAMS		0x10	/* Serdes Tx Parameters. */
#घोषणा MBC_GET_IOCB_STATUS		0x12	/* Get IOCB status command. */
#घोषणा MBC_PORT_PARAMS			0x1A	/* Port iDMA Parameters. */
#घोषणा MBC_GET_TIMEOUT_PARAMS		0x22	/* Get FW समयouts. */
#घोषणा MBC_TRACE_CONTROL		0x27	/* Trace control command. */
#घोषणा MBC_GEN_SYSTEM_ERROR		0x2a	/* Generate System Error. */
#घोषणा MBC_WRITE_SFP			0x30	/* Write SFP Data. */
#घोषणा MBC_READ_SFP			0x31	/* Read SFP Data. */
#घोषणा MBC_SET_TIMEOUT_PARAMS		0x32	/* Set FW समयouts. */
#घोषणा MBC_DPORT_DIAGNOSTICS		0x47	/* D-Port Diagnostics */
#घोषणा MBC_MID_INITIALIZE_FIRMWARE	0x48	/* MID Initialize firmware. */
#घोषणा MBC_MID_GET_VP_DATABASE		0x49	/* MID Get VP Database. */
#घोषणा MBC_MID_GET_VP_ENTRY		0x4a	/* MID Get VP Entry. */
#घोषणा MBC_HOST_MEMORY_COPY		0x53	/* Host Memory Copy. */
#घोषणा MBC_SEND_RNFT_ELS		0x5e	/* Send RNFT ELS request */
#घोषणा MBC_GET_LINK_PRIV_STATS		0x6d	/* Get link & निजी data. */
#घोषणा MBC_LINK_INITIALIZATION		0x72	/* Do link initialization. */
#घोषणा MBC_SET_VENDOR_ID		0x76	/* Set Venकरोr ID. */
#घोषणा MBC_PORT_RESET			0x120	/* Port Reset */
#घोषणा MBC_SET_PORT_CONFIG		0x122	/* Set port configuration */
#घोषणा MBC_GET_PORT_CONFIG		0x123	/* Get port configuration */

/*
 * ISP81xx mailbox commands
 */
#घोषणा MBC_WRITE_MPI_REGISTER		0x01    /* Write MPI Register. */

/*
 * ISP8044 mailbox commands
 */
#घोषणा MBC_SET_GET_ETH_SERDES_REG	0x150
#घोषणा HCS_WRITE_SERDES		0x3
#घोषणा HCS_READ_SERDES			0x4

/* Firmware वापस data sizes */
#घोषणा FCAL_MAP_SIZE	128

/* Mailbox bit definitions क्रम out_mb and in_mb */
#घोषणा	MBX_31		BIT_31
#घोषणा	MBX_30		BIT_30
#घोषणा	MBX_29		BIT_29
#घोषणा	MBX_28		BIT_28
#घोषणा	MBX_27		BIT_27
#घोषणा	MBX_26		BIT_26
#घोषणा	MBX_25		BIT_25
#घोषणा	MBX_24		BIT_24
#घोषणा	MBX_23		BIT_23
#घोषणा	MBX_22		BIT_22
#घोषणा	MBX_21		BIT_21
#घोषणा	MBX_20		BIT_20
#घोषणा	MBX_19		BIT_19
#घोषणा	MBX_18		BIT_18
#घोषणा	MBX_17		BIT_17
#घोषणा	MBX_16		BIT_16
#घोषणा	MBX_15		BIT_15
#घोषणा	MBX_14		BIT_14
#घोषणा	MBX_13		BIT_13
#घोषणा	MBX_12		BIT_12
#घोषणा	MBX_11		BIT_11
#घोषणा	MBX_10		BIT_10
#घोषणा	MBX_9		BIT_9
#घोषणा	MBX_8		BIT_8
#घोषणा	MBX_7		BIT_7
#घोषणा	MBX_6		BIT_6
#घोषणा	MBX_5		BIT_5
#घोषणा	MBX_4		BIT_4
#घोषणा	MBX_3		BIT_3
#घोषणा	MBX_2		BIT_2
#घोषणा	MBX_1		BIT_1
#घोषणा	MBX_0		BIT_0

#घोषणा RNID_TYPE_ELS_CMD	0x5
#घोषणा RNID_TYPE_PORT_LOGIN	0x7
#घोषणा RNID_BUFFER_CREDITS	0x8
#घोषणा RNID_TYPE_SET_VERSION	0x9
#घोषणा RNID_TYPE_ASIC_TEMP	0xC

#घोषणा ELS_CMD_MAP_SIZE	32

/*
 * Firmware state codes from get firmware state mailbox command
 */
#घोषणा FSTATE_CONFIG_WAIT      0
#घोषणा FSTATE_WAIT_AL_PA       1
#घोषणा FSTATE_WAIT_LOGIN       2
#घोषणा FSTATE_READY            3
#घोषणा FSTATE_LOSS_OF_SYNC     4
#घोषणा FSTATE_ERROR            5
#घोषणा FSTATE_REINIT           6
#घोषणा FSTATE_NON_PART         7

#घोषणा FSTATE_CONFIG_CORRECT      0
#घोषणा FSTATE_P2P_RCV_LIP         1
#घोषणा FSTATE_P2P_CHOOSE_LOOP     2
#घोषणा FSTATE_P2P_RCV_UNIDEN_LIP  3
#घोषणा FSTATE_FATAL_ERROR         4
#घोषणा FSTATE_LOOP_BACK_CONN      5

#घोषणा QLA27XX_IMG_STATUS_VER_MAJOR   0x01
#घोषणा QLA27XX_IMG_STATUS_VER_MINOR    0x00
#घोषणा QLA27XX_IMG_STATUS_SIGN   0xFACEFADE
#घोषणा QLA28XX_IMG_STATUS_SIGN    0xFACEFADF
#घोषणा QLA28XX_IMG_STATUS_SIGN		0xFACEFADF
#घोषणा QLA28XX_AUX_IMG_STATUS_SIGN	0xFACEFAED
#घोषणा QLA27XX_DEFAULT_IMAGE		0
#घोषणा QLA27XX_PRIMARY_IMAGE  1
#घोषणा QLA27XX_SECONDARY_IMAGE    2

/*
 * Port Database काष्ठाure definition
 * Little endian except where noted.
 */
#घोषणा	PORT_DATABASE_SIZE	128	/* bytes */
प्रकार काष्ठा अणु
	uपूर्णांक8_t options;
	uपूर्णांक8_t control;
	uपूर्णांक8_t master_state;
	uपूर्णांक8_t slave_state;
	uपूर्णांक8_t reserved[2];
	uपूर्णांक8_t hard_address;
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t port_id[4];
	uपूर्णांक8_t node_name[WWN_SIZE];
	uपूर्णांक8_t port_name[WWN_SIZE];
	__le16	execution_throttle;
	uपूर्णांक16_t execution_count;
	uपूर्णांक8_t reset_count;
	uपूर्णांक8_t reserved_2;
	uपूर्णांक16_t resource_allocation;
	uपूर्णांक16_t current_allocation;
	uपूर्णांक16_t queue_head;
	uपूर्णांक16_t queue_tail;
	uपूर्णांक16_t transmit_execution_list_next;
	uपूर्णांक16_t transmit_execution_list_previous;
	uपूर्णांक16_t common_features;
	uपूर्णांक16_t total_concurrent_sequences;
	uपूर्णांक16_t RO_by_inक्रमmation_category;
	uपूर्णांक8_t recipient;
	uपूर्णांक8_t initiator;
	uपूर्णांक16_t receive_data_size;
	uपूर्णांक16_t concurrent_sequences;
	uपूर्णांक16_t खोलो_sequences_per_exchange;
	uपूर्णांक16_t lun_पात_flags;
	uपूर्णांक16_t lun_stop_flags;
	uपूर्णांक16_t stop_queue_head;
	uपूर्णांक16_t stop_queue_tail;
	uपूर्णांक16_t port_retry_समयr;
	uपूर्णांक16_t next_sequence_id;
	uपूर्णांक16_t frame_count;
	uपूर्णांक16_t PRLI_payload_length;
	uपूर्णांक8_t prli_svc_param_word_0[2];	/* Big endian */
						/* Bits 15-0 of word 0 */
	uपूर्णांक8_t prli_svc_param_word_3[2];	/* Big endian */
						/* Bits 15-0 of word 3 */
	uपूर्णांक16_t loop_id;
	uपूर्णांक16_t extended_lun_info_list_poपूर्णांकer;
	uपूर्णांक16_t extended_lun_stop_list_poपूर्णांकer;
पूर्ण port_database_t;

/*
 * Port database slave/master states
 */
#घोषणा PD_STATE_DISCOVERY			0
#घोषणा PD_STATE_WAIT_DISCOVERY_ACK		1
#घोषणा PD_STATE_PORT_LOGIN			2
#घोषणा PD_STATE_WAIT_PORT_LOGIN_ACK		3
#घोषणा PD_STATE_PROCESS_LOGIN			4
#घोषणा PD_STATE_WAIT_PROCESS_LOGIN_ACK		5
#घोषणा PD_STATE_PORT_LOGGED_IN			6
#घोषणा PD_STATE_PORT_UNAVAILABLE		7
#घोषणा PD_STATE_PROCESS_LOGOUT			8
#घोषणा PD_STATE_WAIT_PROCESS_LOGOUT_ACK	9
#घोषणा PD_STATE_PORT_LOGOUT			10
#घोषणा PD_STATE_WAIT_PORT_LOGOUT_ACK		11


#घोषणा QLA_ZIO_MODE_6		(BIT_2 | BIT_1)
#घोषणा QLA_ZIO_DISABLED	0
#घोषणा QLA_ZIO_DEFAULT_TIMER	2

/*
 * ISP Initialization Control Block.
 * Little endian except where noted.
 */
#घोषणा	ICB_VERSION 1
प्रकार काष्ठा अणु
	uपूर्णांक8_t  version;
	uपूर्णांक8_t  reserved_1;

	/*
	 * LSB BIT 0  = Enable Hard Loop Id
	 * LSB BIT 1  = Enable Fairness
	 * LSB BIT 2  = Enable Full-Duplex
	 * LSB BIT 3  = Enable Fast Posting
	 * LSB BIT 4  = Enable Target Mode
	 * LSB BIT 5  = Disable Initiator Mode
	 * LSB BIT 6  = Enable ADISC
	 * LSB BIT 7  = Enable Target Inquiry Data
	 *
	 * MSB BIT 0  = Enable PDBC Notअगरy
	 * MSB BIT 1  = Non Participating LIP
	 * MSB BIT 2  = Descending Loop ID Search
	 * MSB BIT 3  = Acquire Loop ID in LIPA
	 * MSB BIT 4  = Stop PortQ on Full Status
	 * MSB BIT 5  = Full Login after LIP
	 * MSB BIT 6  = Node Name Option
	 * MSB BIT 7  = Ext IFWCB enable bit
	 */
	uपूर्णांक8_t  firmware_options[2];

	__le16	frame_payload_size;
	__le16	max_iocb_allocation;
	__le16	execution_throttle;
	uपूर्णांक8_t  retry_count;
	uपूर्णांक8_t	 retry_delay;			/* unused */
	uपूर्णांक8_t	 port_name[WWN_SIZE];		/* Big endian. */
	uपूर्णांक16_t hard_address;
	uपूर्णांक8_t	 inquiry_data;
	uपूर्णांक8_t	 login_समयout;
	uपूर्णांक8_t	 node_name[WWN_SIZE];		/* Big endian. */

	__le16	request_q_outpoपूर्णांकer;
	__le16	response_q_inpoपूर्णांकer;
	__le16	request_q_length;
	__le16	response_q_length;
	__le64  request_q_address __packed;
	__le64  response_q_address __packed;

	__le16	lun_enables;
	uपूर्णांक8_t  command_resource_count;
	uपूर्णांक8_t  immediate_notअगरy_resource_count;
	__le16	समयout;
	uपूर्णांक8_t  reserved_2[2];

	/*
	 * LSB BIT 0 = Timer Operation mode bit 0
	 * LSB BIT 1 = Timer Operation mode bit 1
	 * LSB BIT 2 = Timer Operation mode bit 2
	 * LSB BIT 3 = Timer Operation mode bit 3
	 * LSB BIT 4 = Init Config Mode bit 0
	 * LSB BIT 5 = Init Config Mode bit 1
	 * LSB BIT 6 = Init Config Mode bit 2
	 * LSB BIT 7 = Enable Non part on LIHA failure
	 *
	 * MSB BIT 0 = Enable class 2
	 * MSB BIT 1 = Enable ACK0
	 * MSB BIT 2 =
	 * MSB BIT 3 =
	 * MSB BIT 4 = FC Tape Enable
	 * MSB BIT 5 = Enable FC Confirm
	 * MSB BIT 6 = Enable command queuing in target mode
	 * MSB BIT 7 = No Logo On Link Down
	 */
	uपूर्णांक8_t	 add_firmware_options[2];

	uपूर्णांक8_t	 response_accumulation_समयr;
	uपूर्णांक8_t	 पूर्णांकerrupt_delay_समयr;

	/*
	 * LSB BIT 0 = Enable Read xfr_rdy
	 * LSB BIT 1 = Soft ID only
	 * LSB BIT 2 =
	 * LSB BIT 3 =
	 * LSB BIT 4 = FCP RSP Payload [0]
	 * LSB BIT 5 = FCP RSP Payload [1] / Sbus enable - 2200
	 * LSB BIT 6 = Enable Out-of-Order frame handling
	 * LSB BIT 7 = Disable Automatic PLOGI on Local Loop
	 *
	 * MSB BIT 0 = Sbus enable - 2300
	 * MSB BIT 1 =
	 * MSB BIT 2 =
	 * MSB BIT 3 =
	 * MSB BIT 4 = LED mode
	 * MSB BIT 5 = enable 50 ohm termination
	 * MSB BIT 6 = Data Rate (2300 only)
	 * MSB BIT 7 = Data Rate (2300 only)
	 */
	uपूर्णांक8_t	 special_options[2];

	uपूर्णांक8_t  reserved_3[26];
पूर्ण init_cb_t;

/* Special Features Control Block */
काष्ठा init_sf_cb अणु
	uपूर्णांक8_t	क्रमmat;
	uपूर्णांक8_t	reserved0;
	/*
	 * BIT 15-14 = Reserved
	 * BIT_13 = SAN Congestion Management (1 - Enabled, 0 - Disabled)
	 * BIT_12 = Remote Write Optimization (1 - Enabled, 0 - Disabled)
	 * BIT 11-0 = Reserved
	 */
	__le16	flags;
	uपूर्णांक8_t	reserved1[32];
	uपूर्णांक16_t discard_OHRB_समयout_value;
	uपूर्णांक16_t remote_ग_लिखो_opt_queue_num;
	uपूर्णांक8_t	reserved2[40];
	uपूर्णांक8_t scm_related_parameter[16];
	uपूर्णांक8_t reserved3[32];
पूर्ण;

/*
 * Get Link Status mailbox command वापस buffer.
 */
#घोषणा GLSO_SEND_RPS	BIT_0
#घोषणा GLSO_USE_DID	BIT_3

काष्ठा link_statistics अणु
	__le32 link_fail_cnt;
	__le32 loss_sync_cnt;
	__le32 loss_sig_cnt;
	__le32 prim_seq_err_cnt;
	__le32 inval_xmit_word_cnt;
	__le32 inval_crc_cnt;
	__le32 lip_cnt;
	__le32 link_up_cnt;
	__le32 link_करोwn_loop_init_पंचांगo;
	__le32 link_करोwn_los;
	__le32 link_करोwn_loss_rcv_clk;
	uपूर्णांक32_t reserved0[5];
	__le32 port_cfg_chg;
	uपूर्णांक32_t reserved1[11];
	__le32 rsp_q_full;
	__le32 atio_q_full;
	__le32 drop_ae;
	__le32 els_proto_err;
	__le32 reserved2;
	__le32 tx_frames;
	__le32 rx_frames;
	__le32 discarded_frames;
	__le32 dropped_frames;
	uपूर्णांक32_t reserved3;
	__le32 nos_rcvd;
	uपूर्णांक32_t reserved4[4];
	__le32 tx_prjt;
	__le32 rcv_exfail;
	__le32 rcv_abts;
	__le32 seq_frm_miss;
	__le32 corr_err;
	__le32 mb_rqst;
	__le32 nport_full;
	__le32 eofa;
	uपूर्णांक32_t reserved5;
	__le64 fpm_recv_word_cnt;
	__le64 fpm_disc_word_cnt;
	__le64 fpm_xmit_word_cnt;
	uपूर्णांक32_t reserved6[70];
पूर्ण;

/*
 * NVRAM Command values.
 */
#घोषणा NV_START_BIT            BIT_2
#घोषणा NV_WRITE_OP             (BIT_26+BIT_24)
#घोषणा NV_READ_OP              (BIT_26+BIT_25)
#घोषणा NV_ERASE_OP             (BIT_26+BIT_25+BIT_24)
#घोषणा NV_MASK_OP              (BIT_26+BIT_25+BIT_24)
#घोषणा NV_DELAY_COUNT          10

/*
 * QLogic ISP2100, ISP2200 and ISP2300 NVRAM काष्ठाure definition.
 */
प्रकार काष्ठा अणु
	/*
	 * NVRAM header
	 */
	uपूर्णांक8_t	id[4];
	uपूर्णांक8_t	nvram_version;
	uपूर्णांक8_t	reserved_0;

	/*
	 * NVRAM RISC parameter block
	 */
	uपूर्णांक8_t	parameter_block_version;
	uपूर्णांक8_t	reserved_1;

	/*
	 * LSB BIT 0  = Enable Hard Loop Id
	 * LSB BIT 1  = Enable Fairness
	 * LSB BIT 2  = Enable Full-Duplex
	 * LSB BIT 3  = Enable Fast Posting
	 * LSB BIT 4  = Enable Target Mode
	 * LSB BIT 5  = Disable Initiator Mode
	 * LSB BIT 6  = Enable ADISC
	 * LSB BIT 7  = Enable Target Inquiry Data
	 *
	 * MSB BIT 0  = Enable PDBC Notअगरy
	 * MSB BIT 1  = Non Participating LIP
	 * MSB BIT 2  = Descending Loop ID Search
	 * MSB BIT 3  = Acquire Loop ID in LIPA
	 * MSB BIT 4  = Stop PortQ on Full Status
	 * MSB BIT 5  = Full Login after LIP
	 * MSB BIT 6  = Node Name Option
	 * MSB BIT 7  = Ext IFWCB enable bit
	 */
	uपूर्णांक8_t	 firmware_options[2];

	__le16	frame_payload_size;
	__le16	max_iocb_allocation;
	__le16	execution_throttle;
	uपूर्णांक8_t	 retry_count;
	uपूर्णांक8_t	 retry_delay;			/* unused */
	uपूर्णांक8_t	 port_name[WWN_SIZE];		/* Big endian. */
	uपूर्णांक16_t hard_address;
	uपूर्णांक8_t	 inquiry_data;
	uपूर्णांक8_t	 login_समयout;
	uपूर्णांक8_t	 node_name[WWN_SIZE];		/* Big endian. */

	/*
	 * LSB BIT 0 = Timer Operation mode bit 0
	 * LSB BIT 1 = Timer Operation mode bit 1
	 * LSB BIT 2 = Timer Operation mode bit 2
	 * LSB BIT 3 = Timer Operation mode bit 3
	 * LSB BIT 4 = Init Config Mode bit 0
	 * LSB BIT 5 = Init Config Mode bit 1
	 * LSB BIT 6 = Init Config Mode bit 2
	 * LSB BIT 7 = Enable Non part on LIHA failure
	 *
	 * MSB BIT 0 = Enable class 2
	 * MSB BIT 1 = Enable ACK0
	 * MSB BIT 2 =
	 * MSB BIT 3 =
	 * MSB BIT 4 = FC Tape Enable
	 * MSB BIT 5 = Enable FC Confirm
	 * MSB BIT 6 = Enable command queuing in target mode
	 * MSB BIT 7 = No Logo On Link Down
	 */
	uपूर्णांक8_t	 add_firmware_options[2];

	uपूर्णांक8_t	 response_accumulation_समयr;
	uपूर्णांक8_t	 पूर्णांकerrupt_delay_समयr;

	/*
	 * LSB BIT 0 = Enable Read xfr_rdy
	 * LSB BIT 1 = Soft ID only
	 * LSB BIT 2 =
	 * LSB BIT 3 =
	 * LSB BIT 4 = FCP RSP Payload [0]
	 * LSB BIT 5 = FCP RSP Payload [1] / Sbus enable - 2200
	 * LSB BIT 6 = Enable Out-of-Order frame handling
	 * LSB BIT 7 = Disable Automatic PLOGI on Local Loop
	 *
	 * MSB BIT 0 = Sbus enable - 2300
	 * MSB BIT 1 =
	 * MSB BIT 2 =
	 * MSB BIT 3 =
	 * MSB BIT 4 = LED mode
	 * MSB BIT 5 = enable 50 ohm termination
	 * MSB BIT 6 = Data Rate (2300 only)
	 * MSB BIT 7 = Data Rate (2300 only)
	 */
	uपूर्णांक8_t	 special_options[2];

	/* Reserved क्रम expanded RISC parameter block */
	uपूर्णांक8_t reserved_2[22];

	/*
	 * LSB BIT 0 = Tx Sensitivity 1G bit 0
	 * LSB BIT 1 = Tx Sensitivity 1G bit 1
	 * LSB BIT 2 = Tx Sensitivity 1G bit 2
	 * LSB BIT 3 = Tx Sensitivity 1G bit 3
	 * LSB BIT 4 = Rx Sensitivity 1G bit 0
	 * LSB BIT 5 = Rx Sensitivity 1G bit 1
	 * LSB BIT 6 = Rx Sensitivity 1G bit 2
	 * LSB BIT 7 = Rx Sensitivity 1G bit 3
	 *
	 * MSB BIT 0 = Tx Sensitivity 2G bit 0
	 * MSB BIT 1 = Tx Sensitivity 2G bit 1
	 * MSB BIT 2 = Tx Sensitivity 2G bit 2
	 * MSB BIT 3 = Tx Sensitivity 2G bit 3
	 * MSB BIT 4 = Rx Sensitivity 2G bit 0
	 * MSB BIT 5 = Rx Sensitivity 2G bit 1
	 * MSB BIT 6 = Rx Sensitivity 2G bit 2
	 * MSB BIT 7 = Rx Sensitivity 2G bit 3
	 *
	 * LSB BIT 0 = Output Swing 1G bit 0
	 * LSB BIT 1 = Output Swing 1G bit 1
	 * LSB BIT 2 = Output Swing 1G bit 2
	 * LSB BIT 3 = Output Emphasis 1G bit 0
	 * LSB BIT 4 = Output Emphasis 1G bit 1
	 * LSB BIT 5 = Output Swing 2G bit 0
	 * LSB BIT 6 = Output Swing 2G bit 1
	 * LSB BIT 7 = Output Swing 2G bit 2
	 *
	 * MSB BIT 0 = Output Emphasis 2G bit 0
	 * MSB BIT 1 = Output Emphasis 2G bit 1
	 * MSB BIT 2 = Output Enable
	 * MSB BIT 3 =
	 * MSB BIT 4 =
	 * MSB BIT 5 =
	 * MSB BIT 6 =
	 * MSB BIT 7 =
	 */
	uपूर्णांक8_t seriallink_options[4];

	/*
	 * NVRAM host parameter block
	 *
	 * LSB BIT 0 = Enable spinup delay
	 * LSB BIT 1 = Disable BIOS
	 * LSB BIT 2 = Enable Memory Map BIOS
	 * LSB BIT 3 = Enable Selectable Boot
	 * LSB BIT 4 = Disable RISC code load
	 * LSB BIT 5 = Set cache line size 1
	 * LSB BIT 6 = PCI Parity Disable
	 * LSB BIT 7 = Enable extended logging
	 *
	 * MSB BIT 0 = Enable 64bit addressing
	 * MSB BIT 1 = Enable lip reset
	 * MSB BIT 2 = Enable lip full login
	 * MSB BIT 3 = Enable target reset
	 * MSB BIT 4 = Enable database storage
	 * MSB BIT 5 = Enable cache flush पढ़ो
	 * MSB BIT 6 = Enable database load
	 * MSB BIT 7 = Enable alternate WWN
	 */
	uपूर्णांक8_t host_p[2];

	uपूर्णांक8_t boot_node_name[WWN_SIZE];
	uपूर्णांक8_t boot_lun_number;
	uपूर्णांक8_t reset_delay;
	uपूर्णांक8_t port_करोwn_retry_count;
	uपूर्णांक8_t boot_id_number;
	__le16	max_luns_per_target;
	uपूर्णांक8_t fcode_boot_port_name[WWN_SIZE];
	uपूर्णांक8_t alternate_port_name[WWN_SIZE];
	uपूर्णांक8_t alternate_node_name[WWN_SIZE];

	/*
	 * BIT 0 = Selective Login
	 * BIT 1 = Alt-Boot Enable
	 * BIT 2 =
	 * BIT 3 = Boot Order List
	 * BIT 4 =
	 * BIT 5 = Selective LUN
	 * BIT 6 =
	 * BIT 7 = unused
	 */
	uपूर्णांक8_t efi_parameters;

	uपूर्णांक8_t link_करोwn_समयout;

	uपूर्णांक8_t adapter_id[16];

	uपूर्णांक8_t alt1_boot_node_name[WWN_SIZE];
	uपूर्णांक16_t alt1_boot_lun_number;
	uपूर्णांक8_t alt2_boot_node_name[WWN_SIZE];
	uपूर्णांक16_t alt2_boot_lun_number;
	uपूर्णांक8_t alt3_boot_node_name[WWN_SIZE];
	uपूर्णांक16_t alt3_boot_lun_number;
	uपूर्णांक8_t alt4_boot_node_name[WWN_SIZE];
	uपूर्णांक16_t alt4_boot_lun_number;
	uपूर्णांक8_t alt5_boot_node_name[WWN_SIZE];
	uपूर्णांक16_t alt5_boot_lun_number;
	uपूर्णांक8_t alt6_boot_node_name[WWN_SIZE];
	uपूर्णांक16_t alt6_boot_lun_number;
	uपूर्णांक8_t alt7_boot_node_name[WWN_SIZE];
	uपूर्णांक16_t alt7_boot_lun_number;

	uपूर्णांक8_t reserved_3[2];

	/* Offset 200-215 : Model Number */
	uपूर्णांक8_t model_number[16];

	/* OEM related items */
	uपूर्णांक8_t oem_specअगरic[16];

	/*
	 * NVRAM Adapter Features offset 232-239
	 *
	 * LSB BIT 0 = External GBIC
	 * LSB BIT 1 = Risc RAM parity
	 * LSB BIT 2 = Buffer Plus Module
	 * LSB BIT 3 = Multi Chip Adapter
	 * LSB BIT 4 = Internal connector
	 * LSB BIT 5 =
	 * LSB BIT 6 =
	 * LSB BIT 7 =
	 *
	 * MSB BIT 0 =
	 * MSB BIT 1 =
	 * MSB BIT 2 =
	 * MSB BIT 3 =
	 * MSB BIT 4 =
	 * MSB BIT 5 =
	 * MSB BIT 6 =
	 * MSB BIT 7 =
	 */
	uपूर्णांक8_t	adapter_features[2];

	uपूर्णांक8_t reserved_4[16];

	/* Subप्रणाली venकरोr ID क्रम ISP2200 */
	uपूर्णांक16_t subप्रणाली_venकरोr_id_2200;

	/* Subप्रणाली device ID क्रम ISP2200 */
	uपूर्णांक16_t subप्रणाली_device_id_2200;

	uपूर्णांक8_t	 reserved_5;
	uपूर्णांक8_t	 checksum;
पूर्ण nvram_t;

/*
 * ISP queue - response queue entry definition.
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t		entry_type;		/* Entry type. */
	uपूर्णांक8_t		entry_count;		/* Entry count. */
	uपूर्णांक8_t		sys_define;		/* System defined. */
	uपूर्णांक8_t		entry_status;		/* Entry Status. */
	uपूर्णांक32_t	handle;			/* System defined handle */
	uपूर्णांक8_t		data[52];
	uपूर्णांक32_t	signature;
#घोषणा RESPONSE_PROCESSED	0xDEADDEAD	/* Signature */
पूर्ण response_t;

/*
 * ISP queue - ATIO queue entry definition.
 */
काष्ठा atio अणु
	uपूर्णांक8_t		entry_type;		/* Entry type. */
	uपूर्णांक8_t		entry_count;		/* Entry count. */
	__le16		attr_n_length;
	uपूर्णांक8_t		data[56];
	uपूर्णांक32_t	signature;
#घोषणा ATIO_PROCESSED 0xDEADDEAD		/* Signature */
पूर्ण;

प्रकार जोड़ अणु
	__le16	extended;
	काष्ठा अणु
		uपूर्णांक8_t reserved;
		uपूर्णांक8_t standard;
	पूर्ण id;
पूर्ण target_id_t;

#घोषणा SET_TARGET_ID(ha, to, from)			\
करो अणु							\
	अगर (HAS_EXTENDED_IDS(ha))			\
		to.extended = cpu_to_le16(from);	\
	अन्यथा						\
		to.id.standard = (uपूर्णांक8_t)from;		\
पूर्ण जबतक (0)

/*
 * ISP queue - command entry काष्ठाure definition.
 */
#घोषणा COMMAND_TYPE	0x11		/* Command entry */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक32_t handle;		/* System handle. */
	target_id_t target;		/* SCSI ID */
	__le16	lun;			/* SCSI LUN */
	__le16	control_flags;		/* Control flags. */
#घोषणा CF_WRITE	BIT_6
#घोषणा CF_READ		BIT_5
#घोषणा CF_SIMPLE_TAG	BIT_3
#घोषणा CF_ORDERED_TAG	BIT_2
#घोषणा CF_HEAD_TAG	BIT_1
	uपूर्णांक16_t reserved_1;
	__le16	समयout;		/* Command समयout. */
	__le16	dseg_count;		/* Data segment count. */
	uपूर्णांक8_t scsi_cdb[MAX_CMDSZ]; 	/* SCSI command words. */
	__le32	byte_count;		/* Total byte count. */
	जोड़ अणु
		काष्ठा dsd32 dsd32[3];
		काष्ठा dsd64 dsd64[2];
	पूर्ण;
पूर्ण cmd_entry_t;

/*
 * ISP queue - 64-Bit addressing, command entry काष्ठाure definition.
 */
#घोषणा COMMAND_A64_TYPE	0x19	/* Command A64 entry */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक32_t handle;		/* System handle. */
	target_id_t target;		/* SCSI ID */
	__le16	lun;			/* SCSI LUN */
	__le16	control_flags;		/* Control flags. */
	uपूर्णांक16_t reserved_1;
	__le16	समयout;		/* Command समयout. */
	__le16	dseg_count;		/* Data segment count. */
	uपूर्णांक8_t scsi_cdb[MAX_CMDSZ];	/* SCSI command words. */
	uपूर्णांक32_t byte_count;		/* Total byte count. */
	काष्ठा dsd64 dsd[2];
पूर्ण cmd_a64_entry_t, request_t;

/*
 * ISP queue - continuation entry काष्ठाure definition.
 */
#घोषणा CONTINUE_TYPE		0x02	/* Continuation entry. */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक32_t reserved;
	काष्ठा dsd32 dsd[7];
पूर्ण cont_entry_t;

/*
 * ISP queue - 64-Bit addressing, continuation entry काष्ठाure definition.
 */
#घोषणा CONTINUE_A64_TYPE	0x0A	/* Continuation A64 entry. */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	काष्ठा dsd64 dsd[5];
पूर्ण cont_a64_entry_t;

#घोषणा PO_MODE_DIF_INSERT	0
#घोषणा PO_MODE_DIF_REMOVE	1
#घोषणा PO_MODE_DIF_PASS	2
#घोषणा PO_MODE_DIF_REPLACE	3
#घोषणा PO_MODE_DIF_TCP_CKSUM	6
#घोषणा PO_ENABLE_INCR_GUARD_SEED	BIT_3
#घोषणा PO_DISABLE_GUARD_CHECK	BIT_4
#घोषणा PO_DISABLE_INCR_REF_TAG	BIT_5
#घोषणा PO_DIS_HEADER_MODE	BIT_7
#घोषणा PO_ENABLE_DIF_BUNDLING	BIT_8
#घोषणा PO_DIS_FRAME_MODE	BIT_9
#घोषणा PO_DIS_VALD_APP_ESC	BIT_10 /* Dis validation क्रम escape tag/ffffh */
#घोषणा PO_DIS_VALD_APP_REF_ESC BIT_11

#घोषणा PO_DIS_APP_TAG_REPL	BIT_12 /* disable REG Tag replacement */
#घोषणा PO_DIS_REF_TAG_REPL	BIT_13
#घोषणा PO_DIS_APP_TAG_VALD	BIT_14 /* disable REF Tag validation */
#घोषणा PO_DIS_REF_TAG_VALD	BIT_15

/*
 * ISP queue - 64-Bit addressing, continuation crc entry काष्ठाure definition.
 */
काष्ठा crc_context अणु
	uपूर्णांक32_t handle;		/* System handle. */
	__le32 ref_tag;
	__le16 app_tag;
	uपूर्णांक8_t ref_tag_mask[4];	/* Validation/Replacement Mask*/
	uपूर्णांक8_t app_tag_mask[2];	/* Validation/Replacement Mask*/
	__le16 guard_seed;		/* Initial Guard Seed */
	__le16 prot_opts;		/* Requested Data Protection Mode */
	__le16 blk_size;		/* Data size in bytes */
	__le16	runt_blk_guard;	/* Guard value क्रम runt block (tape
					 * only) */
	__le32 byte_count;		/* Total byte count/ total data
					 * transfer count */
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t	reserved_1;
			uपूर्णांक16_t	reserved_2;
			uपूर्णांक16_t	reserved_3;
			uपूर्णांक32_t	reserved_4;
			काष्ठा dsd64	data_dsd[1];
			uपूर्णांक32_t	reserved_5[2];
			uपूर्णांक32_t	reserved_6;
		पूर्ण nobundling;
		काष्ठा अणु
			__le32	dअगर_byte_count;	/* Total DIF byte
							 * count */
			uपूर्णांक16_t	reserved_1;
			__le16	dseg_count;	/* Data segment count */
			uपूर्णांक32_t	reserved_2;
			काष्ठा dsd64	data_dsd[1];
			काष्ठा dsd64	dअगर_dsd;
		पूर्ण bundling;
	पूर्ण u;

	काष्ठा fcp_cmnd	fcp_cmnd;
	dma_addr_t	crc_ctx_dma;
	/* List of DMA context transfers */
	काष्ठा list_head dsd_list;

	/* List of DIF Bundling context DMA address */
	काष्ठा list_head ldअगर_dsd_list;
	u8 no_ldअगर_dsd;

	काष्ठा list_head ldअगर_dma_hndl_list;
	u32 dअगर_bundl_len;
	u8 no_dअगर_bundl;
	/* This काष्ठाure should not exceed 512 bytes */
पूर्ण;

#घोषणा CRC_CONTEXT_LEN_FW	(दुरत्व(काष्ठा crc_context, fcp_cmnd.lun))
#घोषणा CRC_CONTEXT_FCPCMND_OFF	(दुरत्व(काष्ठा crc_context, fcp_cmnd.lun))

/*
 * ISP queue - status entry काष्ठाure definition.
 */
#घोषणा	STATUS_TYPE	0x03		/* Status entry. */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक32_t handle;		/* System handle. */
	__le16	scsi_status;		/* SCSI status. */
	__le16	comp_status;		/* Completion status. */
	__le16	state_flags;		/* State flags. */
	__le16	status_flags;		/* Status flags. */
	__le16	rsp_info_len;		/* Response Info Length. */
	__le16	req_sense_length;	/* Request sense data length. */
	__le32	residual_length;	/* Residual transfer length. */
	uपूर्णांक8_t rsp_info[8];		/* FCP response inक्रमmation. */
	uपूर्णांक8_t req_sense_data[32];	/* Request sense data. */
पूर्ण sts_entry_t;

/*
 * Status entry entry status
 */
#घोषणा RF_RQ_DMA_ERROR	BIT_6		/* Request Queue DMA error. */
#घोषणा RF_INV_E_ORDER	BIT_5		/* Invalid entry order. */
#घोषणा RF_INV_E_COUNT	BIT_4		/* Invalid entry count. */
#घोषणा RF_INV_E_PARAM	BIT_3		/* Invalid entry parameter. */
#घोषणा RF_INV_E_TYPE	BIT_2		/* Invalid entry type. */
#घोषणा RF_BUSY		BIT_1		/* Busy */
#घोषणा RF_MASK		(RF_RQ_DMA_ERROR | RF_INV_E_ORDER | RF_INV_E_COUNT | \
			 RF_INV_E_PARAM | RF_INV_E_TYPE | RF_BUSY)
#घोषणा RF_MASK_24XX	(RF_INV_E_ORDER | RF_INV_E_COUNT | RF_INV_E_PARAM | \
			 RF_INV_E_TYPE)

/*
 * Status entry SCSI status bit definitions.
 */
#घोषणा SS_MASK				0xfff	/* Reserved bits BIT_12-BIT_15*/
#घोषणा SS_RESIDUAL_UNDER		BIT_11
#घोषणा SS_RESIDUAL_OVER		BIT_10
#घोषणा SS_SENSE_LEN_VALID		BIT_9
#घोषणा SS_RESPONSE_INFO_LEN_VALID	BIT_8
#घोषणा SS_SCSI_STATUS_BYTE	0xff

#घोषणा SS_RESERVE_CONFLICT		(BIT_4 | BIT_3)
#घोषणा SS_BUSY_CONDITION		BIT_3
#घोषणा SS_CONDITION_MET		BIT_2
#घोषणा SS_CHECK_CONDITION		BIT_1

/*
 * Status entry completion status
 */
#घोषणा CS_COMPLETE		0x0	/* No errors */
#घोषणा CS_INCOMPLETE		0x1	/* Incomplete transfer of cmd. */
#घोषणा CS_DMA			0x2	/* A DMA direction error. */
#घोषणा CS_TRANSPORT		0x3	/* Transport error. */
#घोषणा CS_RESET		0x4	/* SCSI bus reset occurred */
#घोषणा CS_ABORTED		0x5	/* System पातed command. */
#घोषणा CS_TIMEOUT		0x6	/* Timeout error. */
#घोषणा CS_DATA_OVERRUN		0x7	/* Data overrun. */
#घोषणा CS_DIF_ERROR		0xC	/* DIF error detected  */

#घोषणा CS_DATA_UNDERRUN	0x15	/* Data Underrun. */
#घोषणा CS_QUEUE_FULL		0x1C	/* Queue Full. */
#घोषणा CS_PORT_UNAVAILABLE	0x28	/* Port unavailable */
					/* (selection समयout) */
#घोषणा CS_PORT_LOGGED_OUT	0x29	/* Port Logged Out */
#घोषणा CS_PORT_CONFIG_CHG	0x2A	/* Port Configuration Changed */
#घोषणा CS_PORT_BUSY		0x2B	/* Port Busy */
#घोषणा CS_COMPLETE_CHKCOND	0x30	/* Error? */
#घोषणा CS_IOCB_ERROR		0x31	/* Generic error क्रम IOCB request
					   failure */
#घोषणा CS_REJECT_RECEIVED	0x4E	/* Reject received */
#घोषणा CS_BAD_PAYLOAD		0x80	/* Driver defined */
#घोषणा CS_UNKNOWN		0x81	/* Driver defined */
#घोषणा CS_RETRY		0x82	/* Driver defined */
#घोषणा CS_LOOP_DOWN_ABORT	0x83	/* Driver defined */

#घोषणा CS_BIसूची_RD_OVERRUN			0x700
#घोषणा CS_BIसूची_RD_WR_OVERRUN			0x707
#घोषणा CS_BIसूची_RD_OVERRUN_WR_UNDERRUN		0x715
#घोषणा CS_BIसूची_RD_UNDERRUN			0x1500
#घोषणा CS_BIसूची_RD_UNDERRUN_WR_OVERRUN		0x1507
#घोषणा CS_BIसूची_RD_WR_UNDERRUN			0x1515
#घोषणा CS_BIसूची_DMA				0x200
/*
 * Status entry status flags
 */
#घोषणा SF_ABTS_TERMINATED	BIT_10
#घोषणा SF_LOGOUT_SENT		BIT_13

/*
 * ISP queue - status continuation entry काष्ठाure definition.
 */
#घोषणा	STATUS_CONT_TYPE	0x10	/* Status continuation entry. */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक8_t data[60];		/* data */
पूर्ण sts_cont_entry_t;

/*
 * ISP queue -	RIO Type 1 status entry (32 bit I/O entry handles)
 *		काष्ठाure definition.
 */
#घोषणा	STATUS_TYPE_21 0x21		/* Status entry. */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक32_t handle[15];		/* System handles. */
पूर्ण sts21_entry_t;

/*
 * ISP queue -	RIO Type 2 status entry (16 bit I/O entry handles)
 *		काष्ठाure definition.
 */
#घोषणा	STATUS_TYPE_22	0x22		/* Status entry. */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक16_t handle[30];		/* System handles. */
पूर्ण sts22_entry_t;

/*
 * ISP queue - marker entry काष्ठाure definition.
 */
#घोषणा MARKER_TYPE	0x04		/* Marker entry. */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक32_t sys_define_2;		/* System defined. */
	target_id_t target;		/* SCSI ID */
	uपूर्णांक8_t modअगरier;		/* Modअगरier (7-0). */
#घोषणा MK_SYNC_ID_LUN	0		/* Synchronize ID/LUN */
#घोषणा MK_SYNC_ID	1		/* Synchronize ID */
#घोषणा MK_SYNC_ALL	2		/* Synchronize all ID/LUN */
#घोषणा MK_SYNC_LIP	3		/* Synchronize all ID/LUN, */
					/* clear port changed, */
					/* use sequence number. */
	uपूर्णांक8_t reserved_1;
	__le16	sequence_number;	/* Sequence number of event */
	__le16	lun;			/* SCSI LUN */
	uपूर्णांक8_t reserved_2[48];
पूर्ण mrk_entry_t;

/*
 * ISP queue - Management Server entry काष्ठाure definition.
 */
#घोषणा MS_IOCB_TYPE		0x29	/* Management Server IOCB entry */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	uपूर्णांक32_t handle1;		/* System handle. */
	target_id_t loop_id;
	__le16	status;
	__le16	control_flags;		/* Control flags. */
	uपूर्णांक16_t reserved2;
	__le16	समयout;
	__le16	cmd_dsd_count;
	__le16	total_dsd_count;
	uपूर्णांक8_t type;
	uपूर्णांक8_t r_ctl;
	__le16	rx_id;
	uपूर्णांक16_t reserved3;
	uपूर्णांक32_t handle2;
	__le32	rsp_bytecount;
	__le32	req_bytecount;
	काष्ठा dsd64 req_dsd;
	काष्ठा dsd64 rsp_dsd;
पूर्ण ms_iocb_entry_t;

#घोषणा SCM_EDC_ACC_RECEIVED		BIT_6
#घोषणा SCM_RDF_ACC_RECEIVED		BIT_7

/*
 * ISP queue - Mailbox Command entry काष्ठाure definition.
 */
#घोषणा MBX_IOCB_TYPE	0x39
काष्ठा mbx_entry अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	uपूर्णांक8_t sys_define1;
	/* Use sys_define1 क्रम source type */
#घोषणा SOURCE_SCSI	0x00
#घोषणा SOURCE_IP	0x01
#घोषणा SOURCE_VI	0x02
#घोषणा SOURCE_SCTP	0x03
#घोषणा SOURCE_MP	0x04
#घोषणा SOURCE_MPIOCTL	0x05
#घोषणा SOURCE_ASYNC_IOCB 0x07

	uपूर्णांक8_t entry_status;

	uपूर्णांक32_t handle;
	target_id_t loop_id;

	__le16	status;
	__le16	state_flags;
	__le16	status_flags;

	uपूर्णांक32_t sys_define2[2];

	__le16	mb0;
	__le16	mb1;
	__le16	mb2;
	__le16	mb3;
	__le16	mb6;
	__le16	mb7;
	__le16	mb9;
	__le16	mb10;
	uपूर्णांक32_t reserved_2[2];
	uपूर्णांक8_t node_name[WWN_SIZE];
	uपूर्णांक8_t port_name[WWN_SIZE];
पूर्ण;

#अगर_अघोषित IMMED_NOTIFY_TYPE
#घोषणा IMMED_NOTIFY_TYPE 0x0D		/* Immediate notअगरy entry. */
/*
 * ISP queue -	immediate notअगरy entry काष्ठाure definition.
 *		This is sent by the ISP to the Target driver.
 *		This IOCB would have report of events sent by the
 *		initiator, that needs to be handled by the target
 *		driver immediately.
 */
काष्ठा imm_ntfy_from_isp अणु
	uपूर्णांक8_t	 entry_type;		    /* Entry type. */
	uपूर्णांक8_t	 entry_count;		    /* Entry count. */
	uपूर्णांक8_t	 sys_define;		    /* System defined. */
	uपूर्णांक8_t	 entry_status;		    /* Entry Status. */
	जोड़ अणु
		काष्ठा अणु
			__le32	sys_define_2; /* System defined. */
			target_id_t target;
			__le16	lun;
			uपूर्णांक8_t  target_id;
			uपूर्णांक8_t  reserved_1;
			__le16	status_modअगरier;
			__le16	status;
			__le16	task_flags;
			__le16	seq_id;
			__le16	srr_rx_id;
			__le32	srr_rel_offs;
			__le16	srr_ui;
#घोषणा SRR_IU_DATA_IN	0x1
#घोषणा SRR_IU_DATA_OUT	0x5
#घोषणा SRR_IU_STATUS	0x7
			__le16	srr_ox_id;
			uपूर्णांक8_t reserved_2[28];
		पूर्ण isp2x;
		काष्ठा अणु
			uपूर्णांक32_t reserved;
			__le16	nport_handle;
			uपूर्णांक16_t reserved_2;
			__le16	flags;
#घोषणा NOTIFY24XX_FLAGS_GLOBAL_TPRLO   BIT_1
#घोषणा NOTIFY24XX_FLAGS_PUREX_IOCB     BIT_0
			__le16	srr_rx_id;
			__le16	status;
			uपूर्णांक8_t  status_subcode;
			uपूर्णांक8_t  fw_handle;
			__le32	exchange_address;
			__le32	srr_rel_offs;
			__le16	srr_ui;
			__le16	srr_ox_id;
			जोड़ अणु
				काष्ठा अणु
					uपूर्णांक8_t node_name[8];
				पूर्ण plogi; /* PLOGI/ADISC/PDISC */
				काष्ठा अणु
					/* PRLI word 3 bit 0-15 */
					__le16	wd3_lo;
					uपूर्णांक8_t resv0[6];
				पूर्ण prli;
				काष्ठा अणु
					uपूर्णांक8_t port_id[3];
					uपूर्णांक8_t resv1;
					__le16	nport_handle;
					uपूर्णांक16_t resv2;
				पूर्ण req_els;
			पूर्ण u;
			uपूर्णांक8_t port_name[8];
			uपूर्णांक8_t resv3[3];
			uपूर्णांक8_t  vp_index;
			uपूर्णांक32_t reserved_5;
			uपूर्णांक8_t  port_id[3];
			uपूर्णांक8_t  reserved_6;
		पूर्ण isp24;
	पूर्ण u;
	uपूर्णांक16_t reserved_7;
	__le16	ox_id;
पूर्ण __packed;
#पूर्ण_अगर

/*
 * ISP request and response queue entry sizes
 */
#घोषणा RESPONSE_ENTRY_SIZE	(माप(response_t))
#घोषणा REQUEST_ENTRY_SIZE	(माप(request_t))



/*
 * Switch info gathering काष्ठाure.
 */
प्रकार काष्ठा अणु
	port_id_t d_id;
	uपूर्णांक8_t node_name[WWN_SIZE];
	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक8_t fabric_port_name[WWN_SIZE];
	uपूर्णांक16_t fp_speed;
	uपूर्णांक8_t fc4_type;
	uपूर्णांक8_t fc4_features;
पूर्ण sw_info_t;

/* FCP-4 types */
#घोषणा FC4_TYPE_FCP_SCSI	0x08
#घोषणा FC4_TYPE_NVME		0x28
#घोषणा FC4_TYPE_OTHER		0x0
#घोषणा FC4_TYPE_UNKNOWN	0xff

/* mailbox command 4G & above */
काष्ठा mbx_24xx_entry अणु
	uपूर्णांक8_t		entry_type;
	uपूर्णांक8_t		entry_count;
	uपूर्णांक8_t		sys_define1;
	uपूर्णांक8_t		entry_status;
	uपूर्णांक32_t	handle;
	uपूर्णांक16_t	mb[28];
पूर्ण;

#घोषणा IOCB_SIZE 64

/*
 * Fibre channel port type.
 */
प्रकार क्रमागत अणु
	FCT_UNKNOWN,
	FCT_RSCN,
	FCT_SWITCH,
	FCT_BROADCAST,
	FCT_INITIATOR,
	FCT_TARGET,
	FCT_NVME_INITIATOR = 0x10,
	FCT_NVME_TARGET = 0x20,
	FCT_NVME_DISCOVERY = 0x40,
	FCT_NVME = 0xf0,
पूर्ण fc_port_type_t;

क्रमागत qla_sess_deletion अणु
	QLA_SESS_DELETION_NONE		= 0,
	QLA_SESS_DELETION_IN_PROGRESS,
	QLA_SESS_DELETED,
पूर्ण;

क्रमागत qlt_plogi_link_t अणु
	QLT_PLOGI_LINK_SAME_WWN,
	QLT_PLOGI_LINK_CONFLICT,
	QLT_PLOGI_LINK_MAX
पूर्ण;

काष्ठा qlt_plogi_ack_t अणु
	काष्ठा list_head	list;
	काष्ठा imm_ntfy_from_isp iocb;
	port_id_t	id;
	पूर्णांक		ref_count;
	व्योम		*fcport;
पूर्ण;

काष्ठा ct_sns_desc अणु
	काष्ठा ct_sns_pkt	*ct_sns;
	dma_addr_t		ct_sns_dma;
पूर्ण;

क्रमागत discovery_state अणु
	DSC_DELETED,
	DSC_GNN_ID,
	DSC_GNL,
	DSC_LOGIN_PEND,
	DSC_LOGIN_FAILED,
	DSC_GPDB,
	DSC_UPD_FCPORT,
	DSC_LOGIN_COMPLETE,
	DSC_ADISC,
	DSC_DELETE_PEND,
पूर्ण;

क्रमागत login_state अणु	/* FW control Target side */
	DSC_LS_LLIOCB_SENT = 2,
	DSC_LS_PLOGI_PEND,
	DSC_LS_PLOGI_COMP,
	DSC_LS_PRLI_PEND,
	DSC_LS_PRLI_COMP,
	DSC_LS_PORT_UNAVAIL,
	DSC_LS_PRLO_PEND = 9,
	DSC_LS_LOGO_PEND,
पूर्ण;

क्रमागत rscn_addr_क्रमmat अणु
	RSCN_PORT_ADDR,
	RSCN_AREA_ADDR,
	RSCN_DOM_ADDR,
	RSCN_FAB_ADDR,
पूर्ण;

/*
 * Fibre channel port काष्ठाure.
 */
प्रकार काष्ठा fc_port अणु
	काष्ठा list_head list;
	काष्ठा scsi_qla_host *vha;

	अचिन्हित पूर्णांक conf_compl_supported:1;
	अचिन्हित पूर्णांक deleted:2;
	अचिन्हित पूर्णांक मुक्त_pending:1;
	अचिन्हित पूर्णांक local:1;
	अचिन्हित पूर्णांक logout_on_delete:1;
	अचिन्हित पूर्णांक logo_ack_needed:1;
	अचिन्हित पूर्णांक keep_nport_handle:1;
	अचिन्हित पूर्णांक send_els_logo:1;
	अचिन्हित पूर्णांक login_छोड़ो:1;
	अचिन्हित पूर्णांक login_succ:1;
	अचिन्हित पूर्णांक query:1;
	अचिन्हित पूर्णांक id_changed:1;
	अचिन्हित पूर्णांक scan_needed:1;
	अचिन्हित पूर्णांक n2n_flag:1;
	अचिन्हित पूर्णांक explicit_logout:1;
	अचिन्हित पूर्णांक prli_pend_समयr:1;
	uपूर्णांक8_t nvme_flag;

	uपूर्णांक8_t node_name[WWN_SIZE];
	uपूर्णांक8_t port_name[WWN_SIZE];
	port_id_t d_id;
	uपूर्णांक16_t loop_id;
	uपूर्णांक16_t old_loop_id;

	काष्ठा completion nvme_del_करोne;
	uपूर्णांक32_t nvme_prli_service_param;
#घोषणा NVME_PRLI_SP_PI_CTRL	BIT_9
#घोषणा NVME_PRLI_SP_SLER	BIT_8
#घोषणा NVME_PRLI_SP_CONF       BIT_7
#घोषणा NVME_PRLI_SP_INITIATOR  BIT_5
#घोषणा NVME_PRLI_SP_TARGET     BIT_4
#घोषणा NVME_PRLI_SP_DISCOVERY  BIT_3
#घोषणा NVME_PRLI_SP_FIRST_BURST	BIT_0

	uपूर्णांक32_t nvme_first_burst_size;
#घोषणा NVME_FLAG_REGISTERED 4
#घोषणा NVME_FLAG_DELETING 2
#घोषणा NVME_FLAG_RESETTING 1

	काष्ठा fc_port *conflict;
	अचिन्हित अक्षर logout_completed;
	पूर्णांक generation;

	काष्ठा se_session *se_sess;
	काष्ठा list_head sess_cmd_list;
	spinlock_t sess_cmd_lock;
	काष्ठा kref sess_kref;
	काष्ठा qla_tgt *tgt;
	अचिन्हित दीर्घ expires;
	काष्ठा list_head del_list_entry;
	काष्ठा work_काष्ठा मुक्त_work;
	काष्ठा work_काष्ठा reg_work;
	uपूर्णांक64_t jअगरfies_at_registration;
	अचिन्हित दीर्घ prli_expired;
	काष्ठा qlt_plogi_ack_t *plogi_link[QLT_PLOGI_LINK_MAX];

	uपूर्णांक16_t tgt_id;
	uपूर्णांक16_t old_tgt_id;
	uपूर्णांक16_t sec_since_registration;

	uपूर्णांक8_t fcp_prio;

	uपूर्णांक8_t fabric_port_name[WWN_SIZE];
	uपूर्णांक16_t fp_speed;

	fc_port_type_t port_type;

	atomic_t state;
	uपूर्णांक32_t flags;

	पूर्णांक login_retry;

	काष्ठा fc_rport *rport, *drport;
	u32 supported_classes;

	uपूर्णांक8_t fc4_type;
	uपूर्णांक8_t fc4_features;
	uपूर्णांक8_t scan_state;

	अचिन्हित दीर्घ last_queue_full;
	अचिन्हित दीर्घ last_ramp_up;

	uपूर्णांक16_t port_id;

	काष्ठा nvme_fc_remote_port *nvme_remote_port;

	अचिन्हित दीर्घ retry_delay_बारtamp;
	काष्ठा qla_tgt_sess *tgt_session;
	काष्ठा ct_sns_desc ct_desc;
	क्रमागत discovery_state disc_state;
	atomic_t shaकरोw_disc_state;
	क्रमागत discovery_state next_disc_state;
	क्रमागत login_state fw_login_state;
	अचिन्हित दीर्घ dm_login_expire;
	अचिन्हित दीर्घ plogi_nack_करोne_deadline;

	u32 login_gen, last_login_gen;
	u32 rscn_gen, last_rscn_gen;
	u32 chip_reset;
	काष्ठा list_head gnl_entry;
	काष्ठा work_काष्ठा del_work;
	u8 iocb[IOCB_SIZE];
	u8 current_login_state;
	u8 last_login_state;
	u16 n2n_link_reset_cnt;
	u16 n2n_chip_reset;

	काष्ठा dentry *dfs_rport_dir;

	u64 tgt_लघु_link_करोwn_cnt;
	u64 tgt_link_करोwn_समय;
	u64 dev_loss_पंचांगo;
पूर्ण fc_port_t;

क्रमागत अणु
	FC4_PRIORITY_NVME = 1,
	FC4_PRIORITY_FCP  = 2,
पूर्ण;

#घोषणा QLA_FCPORT_SCAN		1
#घोषणा QLA_FCPORT_FOUND	2

काष्ठा event_arg अणु
	fc_port_t		*fcport;
	srb_t			*sp;
	port_id_t		id;
	u16			data[2], rc;
	u8			port_name[WWN_SIZE];
	u32			iop[2];
पूर्ण;

#समावेश "qla_mr.h"

/*
 * Fibre channel port/lun states.
 */
#घोषणा FCS_UNCONFIGURED	1
#घोषणा FCS_DEVICE_DEAD		2
#घोषणा FCS_DEVICE_LOST		3
#घोषणा FCS_ONLINE		4

बाह्य स्थिर अक्षर *स्थिर port_state_str[5];

अटल स्थिर अक्षर * स्थिर port_dstate_str[] = अणु
	"DELETED",
	"GNN_ID",
	"GNL",
	"LOGIN_PEND",
	"LOGIN_FAILED",
	"GPDB",
	"UPD_FCPORT",
	"LOGIN_COMPLETE",
	"ADISC",
	"DELETE_PEND"
पूर्ण;

/*
 * FC port flags.
 */
#घोषणा FCF_FABRIC_DEVICE	BIT_0
#घोषणा FCF_LOGIN_NEEDED	BIT_1
#घोषणा FCF_FCP2_DEVICE		BIT_2
#घोषणा FCF_ASYNC_SENT		BIT_3
#घोषणा FCF_CONF_COMP_SUPPORTED BIT_4
#घोषणा FCF_ASYNC_ACTIVE	BIT_5

/* No loop ID flag. */
#घोषणा FC_NO_LOOP_ID		0x1000

/*
 * FC-CT पूर्णांकerface
 *
 * NOTE: All काष्ठाures are big-endian in क्रमm.
 */

#घोषणा CT_REJECT_RESPONSE	0x8001
#घोषणा CT_ACCEPT_RESPONSE	0x8002
#घोषणा CT_REASON_INVALID_COMMAND_CODE		0x01
#घोषणा CT_REASON_CANNOT_PERFORM		0x09
#घोषणा CT_REASON_COMMAND_UNSUPPORTED		0x0b
#घोषणा CT_EXPL_ALREADY_REGISTERED		0x10
#घोषणा CT_EXPL_HBA_ATTR_NOT_REGISTERED		0x11
#घोषणा CT_EXPL_MULTIPLE_HBA_ATTR		0x12
#घोषणा CT_EXPL_INVALID_HBA_BLOCK_LENGTH	0x13
#घोषणा CT_EXPL_MISSING_REQ_HBA_ATTR		0x14
#घोषणा CT_EXPL_PORT_NOT_REGISTERED_		0x15
#घोषणा CT_EXPL_MISSING_HBA_ID_PORT_LIST	0x16
#घोषणा CT_EXPL_HBA_NOT_REGISTERED		0x17
#घोषणा CT_EXPL_PORT_ATTR_NOT_REGISTERED	0x20
#घोषणा CT_EXPL_PORT_NOT_REGISTERED		0x21
#घोषणा CT_EXPL_MULTIPLE_PORT_ATTR		0x22
#घोषणा CT_EXPL_INVALID_PORT_BLOCK_LENGTH	0x23

#घोषणा NS_N_PORT_TYPE	0x01
#घोषणा NS_NL_PORT_TYPE	0x02
#घोषणा NS_NX_PORT_TYPE	0x7F

#घोषणा	GA_NXT_CMD	0x100
#घोषणा	GA_NXT_REQ_SIZE	(16 + 4)
#घोषणा	GA_NXT_RSP_SIZE	(16 + 620)

#घोषणा	GPN_FT_CMD	0x172
#घोषणा	GPN_FT_REQ_SIZE	(16 + 4)
#घोषणा	GNN_FT_CMD	0x173
#घोषणा	GNN_FT_REQ_SIZE	(16 + 4)

#घोषणा	GID_PT_CMD	0x1A1
#घोषणा	GID_PT_REQ_SIZE	(16 + 4)

#घोषणा	GPN_ID_CMD	0x112
#घोषणा	GPN_ID_REQ_SIZE	(16 + 4)
#घोषणा	GPN_ID_RSP_SIZE	(16 + 8)

#घोषणा	GNN_ID_CMD	0x113
#घोषणा	GNN_ID_REQ_SIZE	(16 + 4)
#घोषणा	GNN_ID_RSP_SIZE	(16 + 8)

#घोषणा	GFT_ID_CMD	0x117
#घोषणा	GFT_ID_REQ_SIZE	(16 + 4)
#घोषणा	GFT_ID_RSP_SIZE	(16 + 32)

#घोषणा GID_PN_CMD 0x121
#घोषणा GID_PN_REQ_SIZE (16 + 8)
#घोषणा GID_PN_RSP_SIZE (16 + 4)

#घोषणा	RFT_ID_CMD	0x217
#घोषणा	RFT_ID_REQ_SIZE	(16 + 4 + 32)
#घोषणा	RFT_ID_RSP_SIZE	16

#घोषणा	RFF_ID_CMD	0x21F
#घोषणा	RFF_ID_REQ_SIZE	(16 + 4 + 2 + 1 + 1)
#घोषणा	RFF_ID_RSP_SIZE	16

#घोषणा	RNN_ID_CMD	0x213
#घोषणा	RNN_ID_REQ_SIZE	(16 + 4 + 8)
#घोषणा	RNN_ID_RSP_SIZE	16

#घोषणा	RSNN_NN_CMD	 0x239
#घोषणा	RSNN_NN_REQ_SIZE (16 + 8 + 1 + 255)
#घोषणा	RSNN_NN_RSP_SIZE 16

#घोषणा	GFPN_ID_CMD	0x11C
#घोषणा	GFPN_ID_REQ_SIZE (16 + 4)
#घोषणा	GFPN_ID_RSP_SIZE (16 + 8)

#घोषणा	GPSC_CMD	0x127
#घोषणा	GPSC_REQ_SIZE	(16 + 8)
#घोषणा	GPSC_RSP_SIZE	(16 + 2 + 2)

#घोषणा GFF_ID_CMD	0x011F
#घोषणा GFF_ID_REQ_SIZE	(16 + 4)
#घोषणा GFF_ID_RSP_SIZE (16 + 128)

/*
 * FDMI HBA attribute types.
 */
#घोषणा FDMI1_HBA_ATTR_COUNT			9
#घोषणा FDMI2_HBA_ATTR_COUNT			17

#घोषणा FDMI_HBA_NODE_NAME			0x1
#घोषणा FDMI_HBA_MANUFACTURER			0x2
#घोषणा FDMI_HBA_SERIAL_NUMBER			0x3
#घोषणा FDMI_HBA_MODEL				0x4
#घोषणा FDMI_HBA_MODEL_DESCRIPTION		0x5
#घोषणा FDMI_HBA_HARDWARE_VERSION		0x6
#घोषणा FDMI_HBA_DRIVER_VERSION			0x7
#घोषणा FDMI_HBA_OPTION_ROM_VERSION		0x8
#घोषणा FDMI_HBA_FIRMWARE_VERSION		0x9
#घोषणा FDMI_HBA_OS_NAME_AND_VERSION		0xa
#घोषणा FDMI_HBA_MAXIMUM_CT_PAYLOAD_LENGTH	0xb

#घोषणा FDMI_HBA_NODE_SYMBOLIC_NAME		0xc
#घोषणा FDMI_HBA_VENDOR_SPECIFIC_INFO		0xd
#घोषणा FDMI_HBA_NUM_PORTS			0xe
#घोषणा FDMI_HBA_FABRIC_NAME			0xf
#घोषणा FDMI_HBA_BOOT_BIOS_NAME			0x10
#घोषणा FDMI_HBA_VENDOR_IDENTIFIER		0xe0

काष्ठा ct_fdmi_hba_attr अणु
	__be16	type;
	__be16	len;
	जोड़ अणु
		uपूर्णांक8_t node_name[WWN_SIZE];
		uपूर्णांक8_t manufacturer[64];
		uपूर्णांक8_t serial_num[32];
		uपूर्णांक8_t model[16+1];
		uपूर्णांक8_t model_desc[80];
		uपूर्णांक8_t hw_version[32];
		uपूर्णांक8_t driver_version[32];
		uपूर्णांक8_t orom_version[16];
		uपूर्णांक8_t fw_version[32];
		uपूर्णांक8_t os_version[128];
		__be32	 max_ct_len;

		uपूर्णांक8_t sym_name[256];
		__be32	 venकरोr_specअगरic_info;
		__be32	 num_ports;
		uपूर्णांक8_t fabric_name[WWN_SIZE];
		uपूर्णांक8_t bios_name[32];
		uपूर्णांक8_t venकरोr_identअगरier[8];
	पूर्ण a;
पूर्ण;

काष्ठा ct_fdmi1_hba_attributes अणु
	__be32	count;
	काष्ठा ct_fdmi_hba_attr entry[FDMI1_HBA_ATTR_COUNT];
पूर्ण;

काष्ठा ct_fdmi2_hba_attributes अणु
	__be32	count;
	काष्ठा ct_fdmi_hba_attr entry[FDMI2_HBA_ATTR_COUNT];
पूर्ण;

/*
 * FDMI Port attribute types.
 */
#घोषणा FDMI1_PORT_ATTR_COUNT		6
#घोषणा FDMI2_PORT_ATTR_COUNT		16
#घोषणा FDMI2_SMARTSAN_PORT_ATTR_COUNT	23

#घोषणा FDMI_PORT_FC4_TYPES		0x1
#घोषणा FDMI_PORT_SUPPORT_SPEED		0x2
#घोषणा FDMI_PORT_CURRENT_SPEED		0x3
#घोषणा FDMI_PORT_MAX_FRAME_SIZE	0x4
#घोषणा FDMI_PORT_OS_DEVICE_NAME	0x5
#घोषणा FDMI_PORT_HOST_NAME		0x6

#घोषणा FDMI_PORT_NODE_NAME		0x7
#घोषणा FDMI_PORT_NAME			0x8
#घोषणा FDMI_PORT_SYM_NAME		0x9
#घोषणा FDMI_PORT_TYPE			0xa
#घोषणा FDMI_PORT_SUPP_COS		0xb
#घोषणा FDMI_PORT_FABRIC_NAME		0xc
#घोषणा FDMI_PORT_FC4_TYPE		0xd
#घोषणा FDMI_PORT_STATE			0x101
#घोषणा FDMI_PORT_COUNT			0x102
#घोषणा FDMI_PORT_IDENTIFIER		0x103

#घोषणा FDMI_SMARTSAN_SERVICE		0xF100
#घोषणा FDMI_SMARTSAN_GUID		0xF101
#घोषणा FDMI_SMARTSAN_VERSION		0xF102
#घोषणा FDMI_SMARTSAN_PROD_NAME		0xF103
#घोषणा FDMI_SMARTSAN_PORT_INFO		0xF104
#घोषणा FDMI_SMARTSAN_QOS_SUPPORT	0xF105
#घोषणा FDMI_SMARTSAN_SECURITY_SUPPORT	0xF106

#घोषणा FDMI_PORT_SPEED_1GB		0x1
#घोषणा FDMI_PORT_SPEED_2GB		0x2
#घोषणा FDMI_PORT_SPEED_10GB		0x4
#घोषणा FDMI_PORT_SPEED_4GB		0x8
#घोषणा FDMI_PORT_SPEED_8GB		0x10
#घोषणा FDMI_PORT_SPEED_16GB		0x20
#घोषणा FDMI_PORT_SPEED_32GB		0x40
#घोषणा FDMI_PORT_SPEED_64GB		0x80
#घोषणा FDMI_PORT_SPEED_UNKNOWN		0x8000

#घोषणा FC_CLASS_2	0x04
#घोषणा FC_CLASS_3	0x08
#घोषणा FC_CLASS_2_3	0x0C

काष्ठा ct_fdmi_port_attr अणु
	__be16	type;
	__be16	len;
	जोड़ अणु
		uपूर्णांक8_t fc4_types[32];
		__be32	sup_speed;
		__be32	cur_speed;
		__be32	max_frame_size;
		uपूर्णांक8_t os_dev_name[32];
		uपूर्णांक8_t host_name[256];

		uपूर्णांक8_t node_name[WWN_SIZE];
		uपूर्णांक8_t port_name[WWN_SIZE];
		uपूर्णांक8_t port_sym_name[128];
		__be32	port_type;
		__be32	port_supported_cos;
		uपूर्णांक8_t fabric_name[WWN_SIZE];
		uपूर्णांक8_t port_fc4_type[32];
		__be32	 port_state;
		__be32	 num_ports;
		__be32	 port_id;

		uपूर्णांक8_t smartsan_service[24];
		uपूर्णांक8_t smartsan_guid[16];
		uपूर्णांक8_t smartsan_version[24];
		uपूर्णांक8_t smartsan_prod_name[16];
		__be32	 smartsan_port_info;
		__be32	 smartsan_qos_support;
		__be32	 smartsan_security_support;
	पूर्ण a;
पूर्ण;

काष्ठा ct_fdmi1_port_attributes अणु
	__be32	 count;
	काष्ठा ct_fdmi_port_attr entry[FDMI1_PORT_ATTR_COUNT];
पूर्ण;

काष्ठा ct_fdmi2_port_attributes अणु
	__be32	count;
	काष्ठा ct_fdmi_port_attr entry[FDMI2_PORT_ATTR_COUNT];
पूर्ण;

#घोषणा FDMI_ATTR_TYPELEN(obj) \
	(माप((obj)->type) + माप((obj)->len))

#घोषणा FDMI_ATTR_ALIGNMENT(len) \
	(4 - ((len) & 3))

/* FDMI रेजिस्टर call options */
#घोषणा CALLOPT_FDMI1		0
#घोषणा CALLOPT_FDMI2		1
#घोषणा CALLOPT_FDMI2_SMARTSAN	2

/* FDMI definitions. */
#घोषणा GRHL_CMD	0x100
#घोषणा GHAT_CMD	0x101
#घोषणा GRPL_CMD	0x102
#घोषणा GPAT_CMD	0x110

#घोषणा RHBA_CMD	0x200
#घोषणा RHBA_RSP_SIZE	16

#घोषणा RHAT_CMD	0x201

#घोषणा RPRT_CMD	0x210
#घोषणा RPRT_RSP_SIZE	24

#घोषणा RPA_CMD		0x211
#घोषणा RPA_RSP_SIZE	16
#घोषणा SMARTSAN_RPA_RSP_SIZE	24

#घोषणा DHBA_CMD	0x300
#घोषणा DHBA_REQ_SIZE	(16 + 8)
#घोषणा DHBA_RSP_SIZE	16

#घोषणा DHAT_CMD	0x301
#घोषणा DPRT_CMD	0x310
#घोषणा DPA_CMD		0x311

/* CT command header -- request/response common fields */
काष्ठा ct_cmd_hdr अणु
	uपूर्णांक8_t revision;
	uपूर्णांक8_t in_id[3];
	uपूर्णांक8_t gs_type;
	uपूर्णांक8_t gs_subtype;
	uपूर्णांक8_t options;
	uपूर्णांक8_t reserved;
पूर्ण;

/* CT command request */
काष्ठा ct_sns_req अणु
	काष्ठा ct_cmd_hdr header;
	__be16	command;
	__be16	max_rsp_size;
	uपूर्णांक8_t fragment_id;
	uपूर्णांक8_t reserved[3];

	जोड़ अणु
		/* GA_NXT, GPN_ID, GNN_ID, GFT_ID, GFPN_ID */
		काष्ठा अणु
			uपूर्णांक8_t reserved;
			be_id_t port_id;
		पूर्ण port_id;

		काष्ठा अणु
			uपूर्णांक8_t reserved;
			uपूर्णांक8_t करोमुख्य;
			uपूर्णांक8_t area;
			uपूर्णांक8_t port_type;
		पूर्ण gpn_ft;

		काष्ठा अणु
			uपूर्णांक8_t port_type;
			uपूर्णांक8_t करोमुख्य;
			uपूर्णांक8_t area;
			uपूर्णांक8_t reserved;
		पूर्ण gid_pt;

		काष्ठा अणु
			uपूर्णांक8_t reserved;
			be_id_t port_id;
			uपूर्णांक8_t fc4_types[32];
		पूर्ण rft_id;

		काष्ठा अणु
			uपूर्णांक8_t reserved;
			be_id_t port_id;
			uपूर्णांक16_t reserved2;
			uपूर्णांक8_t fc4_feature;
			uपूर्णांक8_t fc4_type;
		पूर्ण rff_id;

		काष्ठा अणु
			uपूर्णांक8_t reserved;
			be_id_t port_id;
			uपूर्णांक8_t node_name[8];
		पूर्ण rnn_id;

		काष्ठा अणु
			uपूर्णांक8_t node_name[8];
			uपूर्णांक8_t name_len;
			uपूर्णांक8_t sym_node_name[255];
		पूर्ण rsnn_nn;

		काष्ठा अणु
			uपूर्णांक8_t hba_identअगरier[8];
		पूर्ण ghat;

		काष्ठा अणु
			uपूर्णांक8_t hba_identअगरier[8];
			__be32	entry_count;
			uपूर्णांक8_t port_name[8];
			काष्ठा ct_fdmi2_hba_attributes attrs;
		पूर्ण rhba;

		काष्ठा अणु
			uपूर्णांक8_t hba_identअगरier[8];
			काष्ठा ct_fdmi1_hba_attributes attrs;
		पूर्ण rhat;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
			काष्ठा ct_fdmi2_port_attributes attrs;
		पूर्ण rpa;

		काष्ठा अणु
			uपूर्णांक8_t hba_identअगरier[8];
			uपूर्णांक8_t port_name[8];
			काष्ठा ct_fdmi2_port_attributes attrs;
		पूर्ण rprt;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण dhba;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण dhat;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण dprt;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण dpa;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण gpsc;

		काष्ठा अणु
			uपूर्णांक8_t reserved;
			uपूर्णांक8_t port_id[3];
		पूर्ण gff_id;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण gid_pn;
	पूर्ण req;
पूर्ण;

/* CT command response header */
काष्ठा ct_rsp_hdr अणु
	काष्ठा ct_cmd_hdr header;
	__be16	response;
	uपूर्णांक16_t residual;
	uपूर्णांक8_t fragment_id;
	uपूर्णांक8_t reason_code;
	uपूर्णांक8_t explanation_code;
	uपूर्णांक8_t venकरोr_unique;
पूर्ण;

काष्ठा ct_sns_gid_pt_data अणु
	uपूर्णांक8_t control_byte;
	be_id_t port_id;
पूर्ण;

/* It's the same क्रम both GPN_FT and GNN_FT */
काष्ठा ct_sns_gpnft_rsp अणु
	काष्ठा अणु
		काष्ठा ct_cmd_hdr header;
		uपूर्णांक16_t response;
		uपूर्णांक16_t residual;
		uपूर्णांक8_t fragment_id;
		uपूर्णांक8_t reason_code;
		uपूर्णांक8_t explanation_code;
		uपूर्णांक8_t venकरोr_unique;
	पूर्ण;
	/* Assume the largest number of tarमाला_लो क्रम the जोड़ */
	काष्ठा ct_sns_gpn_ft_data अणु
		u8 control_byte;
		u8 port_id[3];
		u32 reserved;
		u8 port_name[8];
	पूर्ण entries[1];
पूर्ण;

/* CT command response */
काष्ठा ct_sns_rsp अणु
	काष्ठा ct_rsp_hdr header;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक8_t port_type;
			be_id_t port_id;
			uपूर्णांक8_t port_name[8];
			uपूर्णांक8_t sym_port_name_len;
			uपूर्णांक8_t sym_port_name[255];
			uपूर्णांक8_t node_name[8];
			uपूर्णांक8_t sym_node_name_len;
			uपूर्णांक8_t sym_node_name[255];
			uपूर्णांक8_t init_proc_assoc[8];
			uपूर्णांक8_t node_ip_addr[16];
			uपूर्णांक8_t class_of_service[4];
			uपूर्णांक8_t fc4_types[32];
			uपूर्णांक8_t ip_address[16];
			uपूर्णांक8_t fabric_port_name[8];
			uपूर्णांक8_t reserved;
			uपूर्णांक8_t hard_address[3];
		पूर्ण ga_nxt;

		काष्ठा अणु
			/* Assume the largest number of tarमाला_लो क्रम the जोड़ */
			काष्ठा ct_sns_gid_pt_data
			    entries[MAX_FIBRE_DEVICES_MAX];
		पूर्ण gid_pt;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण gpn_id;

		काष्ठा अणु
			uपूर्णांक8_t node_name[8];
		पूर्ण gnn_id;

		काष्ठा अणु
			uपूर्णांक8_t fc4_types[32];
		पूर्ण gft_id;

		काष्ठा अणु
			uपूर्णांक32_t entry_count;
			uपूर्णांक8_t port_name[8];
			काष्ठा ct_fdmi1_hba_attributes attrs;
		पूर्ण ghat;

		काष्ठा अणु
			uपूर्णांक8_t port_name[8];
		पूर्ण gfpn_id;

		काष्ठा अणु
			__be16	speeds;
			__be16	speed;
		पूर्ण gpsc;

#घोषणा GFF_FCP_SCSI_OFFSET	7
#घोषणा GFF_NVME_OFFSET		23 /* type = 28h */
		काष्ठा अणु
			uपूर्णांक8_t fc4_features[128];
		पूर्ण gff_id;
		काष्ठा अणु
			uपूर्णांक8_t reserved;
			uपूर्णांक8_t port_id[3];
		पूर्ण gid_pn;
	पूर्ण rsp;
पूर्ण;

काष्ठा ct_sns_pkt अणु
	जोड़ अणु
		काष्ठा ct_sns_req req;
		काष्ठा ct_sns_rsp rsp;
	पूर्ण p;
पूर्ण;

काष्ठा ct_sns_gpnft_pkt अणु
	जोड़ अणु
		काष्ठा ct_sns_req req;
		काष्ठा ct_sns_gpnft_rsp rsp;
	पूर्ण p;
पूर्ण;

क्रमागत scan_flags_t अणु
	SF_SCANNING = BIT_0,
	SF_QUEUED = BIT_1,
पूर्ण;

क्रमागत fc4type_t अणु
	FS_FC4TYPE_FCP	= BIT_0,
	FS_FC4TYPE_NVME	= BIT_1,
	FS_FCP_IS_N2N = BIT_7,
पूर्ण;

काष्ठा fab_scan_rp अणु
	port_id_t id;
	क्रमागत fc4type_t fc4type;
	u8 port_name[8];
	u8 node_name[8];
पूर्ण;

काष्ठा fab_scan अणु
	काष्ठा fab_scan_rp *l;
	u32 size;
	u16 scan_retry;
#घोषणा MAX_SCAN_RETRIES 5
	क्रमागत scan_flags_t scan_flags;
	काष्ठा delayed_work scan_work;
पूर्ण;

/*
 * SNS command काष्ठाures -- क्रम 2200 compatibility.
 */
#घोषणा	RFT_ID_SNS_SCMD_LEN	22
#घोषणा	RFT_ID_SNS_CMD_SIZE	60
#घोषणा	RFT_ID_SNS_DATA_SIZE	16

#घोषणा	RNN_ID_SNS_SCMD_LEN	10
#घोषणा	RNN_ID_SNS_CMD_SIZE	36
#घोषणा	RNN_ID_SNS_DATA_SIZE	16

#घोषणा	GA_NXT_SNS_SCMD_LEN	6
#घोषणा	GA_NXT_SNS_CMD_SIZE	28
#घोषणा	GA_NXT_SNS_DATA_SIZE	(620 + 16)

#घोषणा	GID_PT_SNS_SCMD_LEN	6
#घोषणा	GID_PT_SNS_CMD_SIZE	28
/*
 * Assume MAX_FIBRE_DEVICES_2100 as these defines are only used with older
 * adapters.
 */
#घोषणा	GID_PT_SNS_DATA_SIZE	(MAX_FIBRE_DEVICES_2100 * 4 + 16)

#घोषणा	GPN_ID_SNS_SCMD_LEN	6
#घोषणा	GPN_ID_SNS_CMD_SIZE	28
#घोषणा	GPN_ID_SNS_DATA_SIZE	(8 + 16)

#घोषणा	GNN_ID_SNS_SCMD_LEN	6
#घोषणा	GNN_ID_SNS_CMD_SIZE	28
#घोषणा	GNN_ID_SNS_DATA_SIZE	(8 + 16)

काष्ठा sns_cmd_pkt अणु
	जोड़ अणु
		काष्ठा अणु
			__le16	buffer_length;
			__le16	reserved_1;
			__le64	buffer_address __packed;
			__le16	subcommand_length;
			__le16	reserved_2;
			__le16	subcommand;
			__le16	size;
			uपूर्णांक32_t reserved_3;
			uपूर्णांक8_t param[36];
		पूर्ण cmd;

		uपूर्णांक8_t rft_data[RFT_ID_SNS_DATA_SIZE];
		uपूर्णांक8_t rnn_data[RNN_ID_SNS_DATA_SIZE];
		uपूर्णांक8_t gan_data[GA_NXT_SNS_DATA_SIZE];
		uपूर्णांक8_t gid_data[GID_PT_SNS_DATA_SIZE];
		uपूर्णांक8_t gpn_data[GPN_ID_SNS_DATA_SIZE];
		uपूर्णांक8_t gnn_data[GNN_ID_SNS_DATA_SIZE];
	पूर्ण p;
पूर्ण;

काष्ठा fw_blob अणु
	अक्षर *name;
	uपूर्णांक32_t segs[4];
	स्थिर काष्ठा firmware *fw;
पूर्ण;

/* Return data from MBC_GET_ID_LIST call. */
काष्ठा gid_list_info अणु
	uपूर्णांक8_t	al_pa;
	uपूर्णांक8_t	area;
	uपूर्णांक8_t	करोमुख्य;
	uपूर्णांक8_t	loop_id_2100;	/* ISP2100/ISP2200 -- 4 bytes. */
	__le16	loop_id;	/* ISP23XX         -- 6 bytes. */
	uपूर्णांक16_t reserved_1;	/* ISP24XX         -- 8 bytes. */
पूर्ण;

/* NPIV */
प्रकार काष्ठा vport_info अणु
	uपूर्णांक8_t		port_name[WWN_SIZE];
	uपूर्णांक8_t		node_name[WWN_SIZE];
	पूर्णांक		vp_id;
	uपूर्णांक16_t	loop_id;
	अचिन्हित दीर्घ	host_no;
	uपूर्णांक8_t		port_id[3];
	पूर्णांक		loop_state;
पूर्ण vport_info_t;

प्रकार काष्ठा vport_params अणु
	uपूर्णांक8_t 	port_name[WWN_SIZE];
	uपूर्णांक8_t 	node_name[WWN_SIZE];
	uपूर्णांक32_t 	options;
#घोषणा	VP_OPTS_RETRY_ENABLE	BIT_0
#घोषणा	VP_OPTS_VP_DISABLE	BIT_1
पूर्ण vport_params_t;

/* NPIV - वापस codes of VP create and modअगरy */
#घोषणा VP_RET_CODE_OK			0
#घोषणा VP_RET_CODE_FATAL		1
#घोषणा VP_RET_CODE_WRONG_ID		2
#घोषणा VP_RET_CODE_WWPN		3
#घोषणा VP_RET_CODE_RESOURCES		4
#घोषणा VP_RET_CODE_NO_MEM		5
#घोषणा VP_RET_CODE_NOT_FOUND		6

काष्ठा qla_hw_data;
काष्ठा rsp_que;
/*
 * ISP operations
 */
काष्ठा isp_operations अणु

	पूर्णांक (*pci_config) (काष्ठा scsi_qla_host *);
	पूर्णांक (*reset_chip)(काष्ठा scsi_qla_host *);
	पूर्णांक (*chip_diag) (काष्ठा scsi_qla_host *);
	व्योम (*config_rings) (काष्ठा scsi_qla_host *);
	पूर्णांक (*reset_adapter)(काष्ठा scsi_qla_host *);
	पूर्णांक (*nvram_config) (काष्ठा scsi_qla_host *);
	व्योम (*update_fw_options) (काष्ठा scsi_qla_host *);
	पूर्णांक (*load_risc) (काष्ठा scsi_qla_host *, uपूर्णांक32_t *);

	अक्षर * (*pci_info_str)(काष्ठा scsi_qla_host *, अक्षर *, माप_प्रकार);
	अक्षर * (*fw_version_str)(काष्ठा scsi_qla_host *, अक्षर *, माप_प्रकार);

	irq_handler_t पूर्णांकr_handler;
	व्योम (*enable_पूर्णांकrs) (काष्ठा qla_hw_data *);
	व्योम (*disable_पूर्णांकrs) (काष्ठा qla_hw_data *);

	पूर्णांक (*पात_command) (srb_t *);
	पूर्णांक (*target_reset) (काष्ठा fc_port *, uपूर्णांक64_t, पूर्णांक);
	पूर्णांक (*lun_reset) (काष्ठा fc_port *, uपूर्णांक64_t, पूर्णांक);
	पूर्णांक (*fabric_login) (काष्ठा scsi_qla_host *, uपूर्णांक16_t, uपूर्णांक8_t,
		uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक16_t *, uपूर्णांक8_t);
	पूर्णांक (*fabric_logout) (काष्ठा scsi_qla_host *, uपूर्णांक16_t, uपूर्णांक8_t,
	    uपूर्णांक8_t, uपूर्णांक8_t);

	uपूर्णांक16_t (*calc_req_entries) (uपूर्णांक16_t);
	व्योम (*build_iocbs) (srb_t *, cmd_entry_t *, uपूर्णांक16_t);
	व्योम *(*prep_ms_iocb) (काष्ठा scsi_qla_host *, काष्ठा ct_arg *);
	व्योम *(*prep_ms_fdmi_iocb) (काष्ठा scsi_qla_host *, uपूर्णांक32_t,
	    uपूर्णांक32_t);

	uपूर्णांक8_t *(*पढ़ो_nvram)(काष्ठा scsi_qla_host *, व्योम *,
		uपूर्णांक32_t, uपूर्णांक32_t);
	पूर्णांक (*ग_लिखो_nvram)(काष्ठा scsi_qla_host *, व्योम *, uपूर्णांक32_t,
		uपूर्णांक32_t);

	व्योम (*fw_dump)(काष्ठा scsi_qla_host *vha);
	व्योम (*mpi_fw_dump)(काष्ठा scsi_qla_host *, पूर्णांक);

	/* Context: task, might sleep */
	पूर्णांक (*beacon_on) (काष्ठा scsi_qla_host *);
	पूर्णांक (*beacon_off) (काष्ठा scsi_qla_host *);

	व्योम (*beacon_blink) (काष्ठा scsi_qla_host *);

	व्योम *(*पढ़ो_optrom)(काष्ठा scsi_qla_host *, व्योम *,
		uपूर्णांक32_t, uपूर्णांक32_t);
	पूर्णांक (*ग_लिखो_optrom)(काष्ठा scsi_qla_host *, व्योम *, uपूर्णांक32_t,
		uपूर्णांक32_t);

	पूर्णांक (*get_flash_version) (काष्ठा scsi_qla_host *, व्योम *);
	पूर्णांक (*start_scsi) (srb_t *);
	पूर्णांक (*start_scsi_mq) (srb_t *);

	/* Context: task, might sleep */
	पूर्णांक (*पात_isp) (काष्ठा scsi_qla_host *);

	पूर्णांक (*iospace_config)(काष्ठा qla_hw_data *);
	पूर्णांक (*initialize_adapter)(काष्ठा scsi_qla_host *);
पूर्ण;

/* MSI-X Support *************************************************************/

#घोषणा QLA_MSIX_CHIP_REV_24XX	3
#घोषणा QLA_MSIX_FW_MODE(m)	(((m) & (BIT_7|BIT_8|BIT_9)) >> 7)
#घोषणा QLA_MSIX_FW_MODE_1(m)	(QLA_MSIX_FW_MODE(m) == 1)

#घोषणा QLA_BASE_VECTORS	2 /* शेष + RSP */
#घोषणा QLA_MSIX_RSP_Q			0x01
#घोषणा QLA_ATIO_VECTOR		0x02
#घोषणा QLA_MSIX_QPAIR_MULTIQ_RSP_Q	0x03
#घोषणा QLA_MSIX_QPAIR_MULTIQ_RSP_Q_HS	0x04

#घोषणा QLA_MIDX_DEFAULT	0
#घोषणा QLA_MIDX_RSP_Q		1
#घोषणा QLA_PCI_MSIX_CONTROL	0xa2
#घोषणा QLA_83XX_PCI_MSIX_CONTROL	0x92

काष्ठा scsi_qla_host;


#घोषणा QLA83XX_RSPQ_MSIX_ENTRY_NUMBER 1 /* refer to qla83xx_msix_entries */

काष्ठा qla_msix_entry अणु
	पूर्णांक have_irq;
	पूर्णांक in_use;
	uपूर्णांक32_t vector;
	uपूर्णांक16_t entry;
	अक्षर name[30];
	व्योम *handle;
	पूर्णांक cpuid;
पूर्ण;

#घोषणा	WATCH_INTERVAL		1       /* number of seconds */

/* Work events.  */
क्रमागत qla_work_type अणु
	QLA_EVT_AEN,
	QLA_EVT_IDC_ACK,
	QLA_EVT_ASYNC_LOGIN,
	QLA_EVT_ASYNC_LOGOUT,
	QLA_EVT_ASYNC_ADISC,
	QLA_EVT_UEVENT,
	QLA_EVT_AENFX,
	QLA_EVT_GPNID,
	QLA_EVT_UNMAP,
	QLA_EVT_NEW_SESS,
	QLA_EVT_GPDB,
	QLA_EVT_PRLI,
	QLA_EVT_GPSC,
	QLA_EVT_GNL,
	QLA_EVT_NACK,
	QLA_EVT_RELOGIN,
	QLA_EVT_ASYNC_PRLO,
	QLA_EVT_ASYNC_PRLO_DONE,
	QLA_EVT_GPNFT,
	QLA_EVT_GPNFT_DONE,
	QLA_EVT_GNNFT_DONE,
	QLA_EVT_GNNID,
	QLA_EVT_GFPNID,
	QLA_EVT_SP_RETRY,
	QLA_EVT_IIDMA,
	QLA_EVT_ELS_PLOGI,
पूर्ण;


काष्ठा qla_work_evt अणु
	काष्ठा list_head	list;
	क्रमागत qla_work_type	type;
	u32			flags;
#घोषणा QLA_EVT_FLAG_FREE	0x1

	जोड़ अणु
		काष्ठा अणु
			क्रमागत fc_host_event_code code;
			u32 data;
		पूर्ण aen;
		काष्ठा अणु
#घोषणा QLA_IDC_ACK_REGS	7
			uपूर्णांक16_t mb[QLA_IDC_ACK_REGS];
		पूर्ण idc_ack;
		काष्ठा अणु
			काष्ठा fc_port *fcport;
#घोषणा QLA_LOGIO_LOGIN_RETRIED	BIT_0
			u16 data[2];
		पूर्ण logio;
		काष्ठा अणु
			u32 code;
#घोषणा QLA_UEVENT_CODE_FW_DUMP	0
		पूर्ण uevent;
		काष्ठा अणु
			uपूर्णांक32_t        evtcode;
			uपूर्णांक32_t        mbx[8];
			uपूर्णांक32_t        count;
		पूर्ण aenfx;
		काष्ठा अणु
			srb_t *sp;
		पूर्ण iosb;
		काष्ठा अणु
			port_id_t id;
		पूर्ण gpnid;
		काष्ठा अणु
			port_id_t id;
			u8 port_name[8];
			u8 node_name[8];
			व्योम *pla;
			u8 fc4_type;
		पूर्ण new_sess;
		काष्ठा अणु /*Get PDB, Get Speed, update fcport, gnl, gidpn */
			fc_port_t *fcport;
			u8 opt;
		पूर्ण fcport;
		काष्ठा अणु
			fc_port_t *fcport;
			u8 iocb[IOCB_SIZE];
			पूर्णांक type;
		पूर्ण nack;
		काष्ठा अणु
			u8 fc4_type;
			srb_t *sp;
		पूर्ण gpnft;
	 पूर्ण u;
पूर्ण;

काष्ठा qla_chip_state_84xx अणु
	काष्ठा list_head list;
	काष्ठा kref kref;

	व्योम *bus;
	spinlock_t access_lock;
	काष्ठा mutex fw_update_mutex;
	uपूर्णांक32_t fw_update;
	uपूर्णांक32_t op_fw_version;
	uपूर्णांक32_t op_fw_size;
	uपूर्णांक32_t op_fw_seq_size;
	uपूर्णांक32_t diag_fw_version;
	uपूर्णांक32_t gold_fw_version;
पूर्ण;

काष्ठा qla_dअगर_statistics अणु
	uपूर्णांक64_t dअगर_input_bytes;
	uपूर्णांक64_t dअगर_output_bytes;
	uपूर्णांक64_t dअगर_input_requests;
	uपूर्णांक64_t dअगर_output_requests;
	uपूर्णांक32_t dअगर_guard_err;
	uपूर्णांक32_t dअगर_ref_tag_err;
	uपूर्णांक32_t dअगर_app_tag_err;
पूर्ण;

काष्ठा qla_statistics अणु
	uपूर्णांक32_t total_isp_पातs;
	uपूर्णांक64_t input_bytes;
	uपूर्णांक64_t output_bytes;
	uपूर्णांक64_t input_requests;
	uपूर्णांक64_t output_requests;
	uपूर्णांक32_t control_requests;

	uपूर्णांक64_t jअगरfies_at_last_reset;
	uपूर्णांक32_t stat_max_pend_cmds;
	uपूर्णांक32_t stat_max_qfull_cmds_alloc;
	uपूर्णांक32_t stat_max_qfull_cmds_dropped;

	काष्ठा qla_dअगर_statistics qla_dअगर_stats;
पूर्ण;

काष्ठा bidi_statistics अणु
	अचिन्हित दीर्घ दीर्घ io_count;
	अचिन्हित दीर्घ दीर्घ transfer_bytes;
पूर्ण;

काष्ठा qla_tc_param अणु
	काष्ठा scsi_qla_host *vha;
	uपूर्णांक32_t blk_sz;
	uपूर्णांक32_t bufflen;
	काष्ठा scatterlist *sg;
	काष्ठा scatterlist *prot_sg;
	काष्ठा crc_context *ctx;
	uपूर्णांक8_t *ctx_dsd_alloced;
पूर्ण;

/* Multi queue support */
#घोषणा MBC_INITIALIZE_MULTIQ 0x1f
#घोषणा QLA_QUE_PAGE 0X1000
#घोषणा QLA_MQ_SIZE 32
#घोषणा QLA_MAX_QUEUES 256
#घोषणा ISP_QUE_REG(ha, id) \
	((ha->mqenable || IS_QLA83XX(ha) || \
	  IS_QLA27XX(ha) || IS_QLA28XX(ha)) ? \
	 ((व्योम __iomem *)ha->mqiobase + (QLA_QUE_PAGE * id)) :\
	 ((व्योम __iomem *)ha->iobase))
#घोषणा QLA_REQ_QUE_ID(tag) \
	((tag < QLA_MAX_QUEUES && tag > 0) ? tag : 0)
#घोषणा QLA_DEFAULT_QUE_QOS 5
#घोषणा QLA_PRECONFIG_VPORTS 32
#घोषणा QLA_MAX_VPORTS_QLA24XX	128
#घोषणा QLA_MAX_VPORTS_QLA25XX	256

काष्ठा qla_tgt_counters अणु
	uपूर्णांक64_t qla_core_sbt_cmd;
	uपूर्णांक64_t core_qla_que_buf;
	uपूर्णांक64_t qla_core_ret_ctio;
	uपूर्णांक64_t core_qla_snd_status;
	uपूर्णांक64_t qla_core_ret_sta_ctio;
	uपूर्णांक64_t core_qla_मुक्त_cmd;
	uपूर्णांक64_t num_q_full_sent;
	uपूर्णांक64_t num_alloc_iocb_failed;
	uपूर्णांक64_t num_term_xchg_sent;
पूर्ण;

काष्ठा qla_counters अणु
	uपूर्णांक64_t input_bytes;
	uपूर्णांक64_t input_requests;
	uपूर्णांक64_t output_bytes;
	uपूर्णांक64_t output_requests;

पूर्ण;

काष्ठा qla_qpair;

/* Response queue data काष्ठाure */
काष्ठा rsp_que अणु
	dma_addr_t  dma;
	response_t *ring;
	response_t *ring_ptr;
	__le32	__iomem *rsp_q_in;	/* FWI2-capable only. */
	__le32	__iomem *rsp_q_out;
	uपूर्णांक16_t  ring_index;
	uपूर्णांक16_t  out_ptr;
	uपूर्णांक16_t  *in_ptr;		/* queue shaकरोw in index */
	uपूर्णांक16_t  length;
	uपूर्णांक16_t  options;
	uपूर्णांक16_t  rid;
	uपूर्णांक16_t  id;
	uपूर्णांक16_t  vp_idx;
	काष्ठा qla_hw_data *hw;
	काष्ठा qla_msix_entry *msix;
	काष्ठा req_que *req;
	srb_t *status_srb; /* status continuation entry */
	काष्ठा qla_qpair *qpair;

	dma_addr_t  dma_fx00;
	response_t *ring_fx00;
	uपूर्णांक16_t  length_fx00;
	uपूर्णांक8_t rsp_pkt[REQUEST_ENTRY_SIZE];
पूर्ण;

/* Request queue data काष्ठाure */
काष्ठा req_que अणु
	dma_addr_t  dma;
	request_t *ring;
	request_t *ring_ptr;
	__le32	__iomem *req_q_in;	/* FWI2-capable only. */
	__le32	__iomem *req_q_out;
	uपूर्णांक16_t  ring_index;
	uपूर्णांक16_t  in_ptr;
	uपूर्णांक16_t  *out_ptr;		/* queue shaकरोw out index */
	uपूर्णांक16_t  cnt;
	uपूर्णांक16_t  length;
	uपूर्णांक16_t  options;
	uपूर्णांक16_t  rid;
	uपूर्णांक16_t  id;
	uपूर्णांक16_t  qos;
	uपूर्णांक16_t  vp_idx;
	काष्ठा rsp_que *rsp;
	srb_t **outstanding_cmds;
	uपूर्णांक32_t current_outstanding_cmd;
	uपूर्णांक16_t num_outstanding_cmds;
	पूर्णांक max_q_depth;

	dma_addr_t  dma_fx00;
	request_t *ring_fx00;
	uपूर्णांक16_t  length_fx00;
	uपूर्णांक8_t req_pkt[REQUEST_ENTRY_SIZE];
पूर्ण;

काष्ठा qla_fw_resources अणु
	u16 iocbs_total;
	u16 iocbs_limit;
	u16 iocbs_qp_limit;
	u16 iocbs_used;
पूर्ण;

#घोषणा QLA_IOCB_PCT_LIMIT 95

/*Queue pair data काष्ठाure */
काष्ठा qla_qpair अणु
	spinlock_t qp_lock;
	atomic_t ref_count;
	uपूर्णांक32_t lun_cnt;
	/*
	 * For qpair 0, qp_lock_ptr will poपूर्णांक at hardware_lock due to
	 * legacy code. For other Qpair(s), it will poपूर्णांक at qp_lock.
	 */
	spinlock_t *qp_lock_ptr;
	काष्ठा scsi_qla_host *vha;
	u32 chip_reset;

	/* distill these fields करोwn to 'online=0/1'
	 * ha->flags.eeh_busy
	 * ha->flags.pci_channel_io_perm_failure
	 * base_vha->loop_state
	 */
	uपूर्णांक32_t online:1;
	/* move vha->flags.dअगरdix_supported here */
	uपूर्णांक32_t dअगरdix_supported:1;
	uपूर्णांक32_t delete_in_progress:1;
	uपूर्णांक32_t fw_started:1;
	uपूर्णांक32_t enable_class_2:1;
	uपूर्णांक32_t enable_explicit_conf:1;
	uपूर्णांक32_t use_shaकरोw_reg:1;
	uपूर्णांक32_t rcv_पूर्णांकr:1;

	uपूर्णांक16_t id;			/* qp number used with FW */
	uपूर्णांक16_t vp_idx;		/* vport ID */
	mempool_t *srb_mempool;

	काष्ठा pci_dev  *pdev;
	व्योम (*reqq_start_iocbs)(काष्ठा qla_qpair *);

	/* to करो: New driver: move queues to here instead of poपूर्णांकers */
	काष्ठा req_que *req;
	काष्ठा rsp_que *rsp;
	काष्ठा atio_que *atio;
	काष्ठा qla_msix_entry *msix; /* poपूर्णांक to &ha->msix_entries[x] */
	काष्ठा qla_hw_data *hw;
	काष्ठा work_काष्ठा q_work;
	काष्ठा qla_counters counters;

	काष्ठा list_head qp_list_elem; /* vha->qp_list */
	काष्ठा list_head hपूर्णांकs_list;

	uपूर्णांक16_t retry_term_cnt;
	__le32	retry_term_exchg_addr;
	uपूर्णांक64_t retry_term_jअगरf;
	काष्ठा qla_tgt_counters tgt_counters;
	uपूर्णांक16_t cpuid;
	काष्ठा qla_fw_resources fwres ____cacheline_aligned;
पूर्ण;

/* Place holder क्रम FW buffer parameters */
काष्ठा qlfc_fw अणु
	व्योम *fw_buf;
	dma_addr_t fw_dma;
	uपूर्णांक32_t len;
पूर्ण;

काष्ठा rdp_req_payload अणु
	uपूर्णांक32_t	els_request;
	uपूर्णांक32_t	desc_list_len;

	/* NPIV descriptor */
	काष्ठा अणु
		uपूर्णांक32_t desc_tag;
		uपूर्णांक32_t desc_len;
		uपूर्णांक8_t  reserved;
		uपूर्णांक8_t  nport_id[3];
	पूर्ण npiv_desc;
पूर्ण;

काष्ठा rdp_rsp_payload अणु
	काष्ठा अणु
		__be32	cmd;
		__be32	len;
	पूर्ण hdr;

	/* LS Request Info descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		__be32	req_payload_word_0;
	पूर्ण ls_req_info_desc;

	/* LS Request Info descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		__be32	req_payload_word_0;
	पूर्ण ls_req_info_desc2;

	/* SFP diagnostic param descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		__be16	temperature;
		__be16	vcc;
		__be16	tx_bias;
		__be16	tx_घातer;
		__be16	rx_घातer;
		__be16	sfp_flags;
	पूर्ण sfp_diag_desc;

	/* Port Speed Descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		__be16	speed_capab;
		__be16	operating_speed;
	पूर्ण port_speed_desc;

	/* Link Error Status Descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		__be32	link_fail_cnt;
		__be32	loss_sync_cnt;
		__be32	loss_sig_cnt;
		__be32	prim_seq_err_cnt;
		__be32	inval_xmit_word_cnt;
		__be32	inval_crc_cnt;
		uपूर्णांक8_t  pn_port_phy_type;
		uपूर्णांक8_t  reserved[3];
	पूर्ण ls_err_desc;

	/* Port name description with diag param */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		uपूर्णांक8_t WWNN[WWN_SIZE];
		uपूर्णांक8_t WWPN[WWN_SIZE];
	पूर्ण port_name_diag_desc;

	/* Port Name desc क्रम Direct attached Fx_Port or Nx_Port */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		uपूर्णांक8_t WWNN[WWN_SIZE];
		uपूर्णांक8_t WWPN[WWN_SIZE];
	पूर्ण port_name_direct_desc;

	/* Buffer Credit descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		__be32	fcport_b2b;
		__be32	attached_fcport_b2b;
		__be32	fcport_rtt;
	पूर्ण buffer_credit_desc;

	/* Optical Element Data Descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		__be16	high_alarm;
		__be16	low_alarm;
		__be16	high_warn;
		__be16	low_warn;
		__be32	element_flags;
	पूर्ण optical_elmt_desc[5];

	/* Optical Product Data Descriptor */
	काष्ठा अणु
		__be32	desc_tag;
		__be32	desc_len;
		uपूर्णांक8_t  venकरोr_name[16];
		uपूर्णांक8_t  part_number[16];
		uपूर्णांक8_t  serial_number[16];
		uपूर्णांक8_t  revision[4];
		uपूर्णांक8_t  date[8];
	पूर्ण optical_prod_desc;
पूर्ण;

#घोषणा RDP_DESC_LEN(obj) \
	(माप(obj) - माप((obj).desc_tag) - माप((obj).desc_len))

#घोषणा RDP_PORT_SPEED_1GB		BIT_15
#घोषणा RDP_PORT_SPEED_2GB		BIT_14
#घोषणा RDP_PORT_SPEED_4GB		BIT_13
#घोषणा RDP_PORT_SPEED_10GB		BIT_12
#घोषणा RDP_PORT_SPEED_8GB		BIT_11
#घोषणा RDP_PORT_SPEED_16GB		BIT_10
#घोषणा RDP_PORT_SPEED_32GB		BIT_9
#घोषणा RDP_PORT_SPEED_64GB             BIT_8
#घोषणा RDP_PORT_SPEED_UNKNOWN		BIT_0

काष्ठा scsi_qlt_host अणु
	व्योम *target_lport_ptr;
	काष्ठा mutex tgt_mutex;
	काष्ठा mutex tgt_host_action_mutex;
	काष्ठा qla_tgt *qla_tgt;
पूर्ण;

काष्ठा qlt_hw_data अणु
	/* Protected by hw lock */
	uपूर्णांक32_t node_name_set:1;

	dma_addr_t atio_dma;	/* Physical address. */
	काष्ठा atio *atio_ring;	/* Base भव address */
	काष्ठा atio *atio_ring_ptr;	/* Current address. */
	uपूर्णांक16_t atio_ring_index; /* Current index. */
	uपूर्णांक16_t atio_q_length;
	__le32 __iomem *atio_q_in;
	__le32 __iomem *atio_q_out;

	स्थिर काष्ठा qla_tgt_func_पंचांगpl *tgt_ops;
	काष्ठा qla_tgt_vp_map *tgt_vp_map;

	पूर्णांक saved_set;
	__le16	saved_exchange_count;
	__le32	saved_firmware_options_1;
	__le32	saved_firmware_options_2;
	__le32	saved_firmware_options_3;
	uपूर्णांक8_t saved_firmware_options[2];
	uपूर्णांक8_t saved_add_firmware_options[2];

	uपूर्णांक8_t tgt_node_name[WWN_SIZE];

	काष्ठा dentry *dfs_tgt_sess;
	काष्ठा dentry *dfs_tgt_port_database;
	काष्ठा dentry *dfs_naqp;

	काष्ठा list_head q_full_list;
	uपूर्णांक32_t num_pend_cmds;
	uपूर्णांक32_t num_qfull_cmds_alloc;
	uपूर्णांक32_t num_qfull_cmds_dropped;
	spinlock_t q_full_lock;
	uपूर्णांक32_t leak_exchg_thresh_hold;
	spinlock_t sess_lock;
	पूर्णांक num_act_qpairs;
#घोषणा DEFAULT_NAQP 2
	spinlock_t atio_lock ____cacheline_aligned;
	काष्ठा btree_head32 host_map;
पूर्ण;

#घोषणा MAX_QFULL_CMDS_ALLOC	8192
#घोषणा Q_FULL_THRESH_HOLD_PERCENT 90
#घोषणा Q_FULL_THRESH_HOLD(ha) \
	((ha->cur_fw_xcb_count/100) * Q_FULL_THRESH_HOLD_PERCENT)

#घोषणा LEAK_EXCHG_THRESH_HOLD_PERCENT 75	/* 75 percent */

काष्ठा qla_hw_data_stat अणु
	u32 num_fw_dump;
	u32 num_mpi_reset;
पूर्ण;

/* refer to pcie_करो_recovery reference */
प्रकार क्रमागत अणु
	QLA_PCI_RESUME,
	QLA_PCI_ERR_DETECTED,
	QLA_PCI_MMIO_ENABLED,
	QLA_PCI_SLOT_RESET,
पूर्ण pci_error_state_t;
/*
 * Qlogic host adapter specअगरic data काष्ठाure.
*/
काष्ठा qla_hw_data अणु
	काष्ठा pci_dev  *pdev;
	/* SRB cache. */
#घोषणा SRB_MIN_REQ     128
	mempool_t       *srb_mempool;

	अस्थिर काष्ठा अणु
		uपूर्णांक32_t	mbox_पूर्णांक		:1;
		uपूर्णांक32_t	mbox_busy		:1;
		uपूर्णांक32_t	disable_risc_code_load	:1;
		uपूर्णांक32_t	enable_64bit_addressing	:1;
		uपूर्णांक32_t	enable_lip_reset	:1;
		uपूर्णांक32_t	enable_target_reset	:1;
		uपूर्णांक32_t	enable_lip_full_login	:1;
		uपूर्णांक32_t	enable_led_scheme	:1;

		uपूर्णांक32_t	msi_enabled		:1;
		uपूर्णांक32_t	msix_enabled		:1;
		uपूर्णांक32_t	disable_serdes		:1;
		uपूर्णांक32_t	gpsc_supported		:1;
		uपूर्णांक32_t	npiv_supported		:1;
		uपूर्णांक32_t	pci_channel_io_perm_failure	:1;
		uपूर्णांक32_t	fce_enabled		:1;
		uपूर्णांक32_t	fac_supported		:1;

		uपूर्णांक32_t	chip_reset_करोne		:1;
		uपूर्णांक32_t	running_gold_fw		:1;
		uपूर्णांक32_t	eeh_busy		:1;
		uपूर्णांक32_t	disable_msix_handshake	:1;
		uपूर्णांक32_t	fcp_prio_enabled	:1;
		uपूर्णांक32_t	isp82xx_fw_hung:1;
		uपूर्णांक32_t	nic_core_hung:1;

		uपूर्णांक32_t	quiesce_owner:1;
		uपूर्णांक32_t	nic_core_reset_hdlr_active:1;
		uपूर्णांक32_t	nic_core_reset_owner:1;
		uपूर्णांक32_t	isp82xx_no_md_cap:1;
		uपूर्णांक32_t	host_shutting_करोwn:1;
		uपूर्णांक32_t	idc_compl_status:1;
		uपूर्णांक32_t        mr_reset_hdlr_active:1;
		uपूर्णांक32_t        mr_पूर्णांकr_valid:1;

		uपूर्णांक32_t        dport_enabled:1;
		uपूर्णांक32_t	fawwpn_enabled:1;
		uपूर्णांक32_t	exlogins_enabled:1;
		uपूर्णांक32_t	exchoffld_enabled:1;

		uपूर्णांक32_t	lip_ae:1;
		uपूर्णांक32_t	n2n_ae:1;
		uपूर्णांक32_t	fw_started:1;
		uपूर्णांक32_t	fw_init_करोne:1;

		uपूर्णांक32_t	lr_detected:1;

		uपूर्णांक32_t	rida_fmt2:1;
		uपूर्णांक32_t	purge_mbox:1;
		uपूर्णांक32_t        n2n_bigger:1;
		uपूर्णांक32_t	secure_adapter:1;
		uपूर्णांक32_t	secure_fw:1;
				/* Supported by Adapter */
		uपूर्णांक32_t	scm_supported_a:1;
				/* Supported by Firmware */
		uपूर्णांक32_t	scm_supported_f:1;
				/* Enabled in Driver */
		uपूर्णांक32_t	scm_enabled:1;
		uपूर्णांक32_t	max_req_queue_warned:1;
		uपूर्णांक32_t	plogi_ढाँचा_valid:1;
		uपूर्णांक32_t	port_isolated:1;
	पूर्ण flags;

	uपूर्णांक16_t max_exchg;
	uपूर्णांक16_t lr_distance;	/* 32G & above */
#घोषणा LR_DISTANCE_5K  1
#घोषणा LR_DISTANCE_10K 0

	/* This spinlock is used to protect "io transactions", you must
	* acquire it beक्रमe करोing any IO to the card, eg with RD_REG*() and
	* WRT_REG*() क्रम the duration of your entire commandtransaction.
	*
	* This spinlock is of lower priority than the io request lock.
	*/

	spinlock_t	hardware_lock ____cacheline_aligned;
	पूर्णांक		bars;
	पूर्णांक		mem_only;
	device_reg_t *iobase;           /* Base I/O address */
	resource_माप_प्रकार pio_address;

#घोषणा MIN_IOBASE_LEN          0x100
	dma_addr_t		bar0_hdl;

	व्योम __iomem *cregbase;
	dma_addr_t		bar2_hdl;
#घोषणा BAR0_LEN_FX00			(1024 * 1024)
#घोषणा BAR2_LEN_FX00			(128 * 1024)

	uपूर्णांक32_t		rqstq_पूर्णांकr_code;
	uपूर्णांक32_t		mbx_पूर्णांकr_code;
	uपूर्णांक32_t		req_que_len;
	uपूर्णांक32_t		rsp_que_len;
	uपूर्णांक32_t		req_que_off;
	uपूर्णांक32_t		rsp_que_off;

	/* Multi queue data काष्ठाs */
	device_reg_t *mqiobase;
	device_reg_t *msixbase;
	uपूर्णांक16_t        msix_count;
	uपूर्णांक8_t         mqenable;
	काष्ठा req_que **req_q_map;
	काष्ठा rsp_que **rsp_q_map;
	काष्ठा qla_qpair **queue_pair_map;
	अचिन्हित दीर्घ req_qid_map[(QLA_MAX_QUEUES / 8) / माप(अचिन्हित दीर्घ)];
	अचिन्हित दीर्घ rsp_qid_map[(QLA_MAX_QUEUES / 8) / माप(अचिन्हित दीर्घ)];
	अचिन्हित दीर्घ qpair_qid_map[(QLA_MAX_QUEUES / 8)
		/ माप(अचिन्हित दीर्घ)];
	uपूर्णांक8_t 	max_req_queues;
	uपूर्णांक8_t 	max_rsp_queues;
	uपूर्णांक8_t		max_qpairs;
	uपूर्णांक8_t		num_qpairs;
	काष्ठा qla_qpair *base_qpair;
	काष्ठा qla_npiv_entry *npiv_info;
	uपूर्णांक16_t	nvram_npiv_size;

	uपूर्णांक16_t        चयन_cap;
#घोषणा FLOGI_SEQ_DEL           BIT_8
#घोषणा FLOGI_MID_SUPPORT       BIT_10
#घोषणा FLOGI_VSAN_SUPPORT      BIT_12
#घोषणा FLOGI_SP_SUPPORT        BIT_13

	uपूर्णांक8_t		port_no;		/* Physical port of adapter */
	uपूर्णांक8_t		exch_starvation;

	/* Timeout समयrs. */
	uपूर्णांक8_t 	loop_करोwn_पात_समय;    /* port करोwn समयr */
	atomic_t	loop_करोwn_समयr;         /* loop करोwn समयr */
	uपूर्णांक8_t		link_करोwn_समयout;       /* link करोwn समयout */
	uपूर्णांक16_t	max_loop_id;
	uपूर्णांक16_t	max_fibre_devices;	/* Maximum number of tarमाला_लो */

	uपूर्णांक16_t	fb_rev;
	uपूर्णांक16_t	min_बाह्यal_loopid;    /* First बाह्यal loop Id */

#घोषणा PORT_SPEED_UNKNOWN 0xFFFF
#घोषणा PORT_SPEED_1GB  0x00
#घोषणा PORT_SPEED_2GB  0x01
#घोषणा PORT_SPEED_AUTO 0x02
#घोषणा PORT_SPEED_4GB  0x03
#घोषणा PORT_SPEED_8GB  0x04
#घोषणा PORT_SPEED_16GB 0x05
#घोषणा PORT_SPEED_32GB 0x06
#घोषणा PORT_SPEED_64GB 0x07
#घोषणा PORT_SPEED_10GB	0x13
	uपूर्णांक16_t	link_data_rate;         /* F/W operating speed */
	uपूर्णांक16_t	set_data_rate;		/* Set by user */

	uपूर्णांक8_t		current_topology;
	uपूर्णांक8_t		prev_topology;
#घोषणा ISP_CFG_NL	1
#घोषणा ISP_CFG_N	2
#घोषणा ISP_CFG_FL	4
#घोषणा ISP_CFG_F	8

	uपूर्णांक8_t		operating_mode;         /* F/W operating mode */
#घोषणा LOOP      0
#घोषणा P2P       1
#घोषणा LOOP_P2P  2
#घोषणा P2P_LOOP  3
	uपूर्णांक8_t		पूर्णांकerrupts_on;
	uपूर्णांक32_t	isp_पात_cnt;
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2532    0x2532
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP8432    0x8432
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP8001	0x8001
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP8031	0x8031
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2031	0x2031
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2071	0x2071
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2271	0x2271
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2261	0x2261
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2061	0x2061
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2081	0x2081
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2089	0x2089
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2281	0x2281
#घोषणा PCI_DEVICE_ID_QLOGIC_ISP2289	0x2289

	uपूर्णांक32_t	isp_type;
#घोषणा DT_ISP2100                      BIT_0
#घोषणा DT_ISP2200                      BIT_1
#घोषणा DT_ISP2300                      BIT_2
#घोषणा DT_ISP2312                      BIT_3
#घोषणा DT_ISP2322                      BIT_4
#घोषणा DT_ISP6312                      BIT_5
#घोषणा DT_ISP6322                      BIT_6
#घोषणा DT_ISP2422                      BIT_7
#घोषणा DT_ISP2432                      BIT_8
#घोषणा DT_ISP5422                      BIT_9
#घोषणा DT_ISP5432                      BIT_10
#घोषणा DT_ISP2532                      BIT_11
#घोषणा DT_ISP8432                      BIT_12
#घोषणा DT_ISP8001			BIT_13
#घोषणा DT_ISP8021			BIT_14
#घोषणा DT_ISP2031			BIT_15
#घोषणा DT_ISP8031			BIT_16
#घोषणा DT_ISPFX00			BIT_17
#घोषणा DT_ISP8044			BIT_18
#घोषणा DT_ISP2071			BIT_19
#घोषणा DT_ISP2271			BIT_20
#घोषणा DT_ISP2261			BIT_21
#घोषणा DT_ISP2061			BIT_22
#घोषणा DT_ISP2081			BIT_23
#घोषणा DT_ISP2089			BIT_24
#घोषणा DT_ISP2281			BIT_25
#घोषणा DT_ISP2289			BIT_26
#घोषणा DT_ISP_LAST			(DT_ISP2289 << 1)

	uपूर्णांक32_t	device_type;
#घोषणा DT_T10_PI                       BIT_25
#घोषणा DT_IIDMA                        BIT_26
#घोषणा DT_FWI2                         BIT_27
#घोषणा DT_ZIO_SUPPORTED                BIT_28
#घोषणा DT_OEM_001                      BIT_29
#घोषणा DT_ISP2200A                     BIT_30
#घोषणा DT_EXTENDED_IDS                 BIT_31

#घोषणा DT_MASK(ha)     ((ha)->isp_type & (DT_ISP_LAST - 1))
#घोषणा IS_QLA2100(ha)  (DT_MASK(ha) & DT_ISP2100)
#घोषणा IS_QLA2200(ha)  (DT_MASK(ha) & DT_ISP2200)
#घोषणा IS_QLA2300(ha)  (DT_MASK(ha) & DT_ISP2300)
#घोषणा IS_QLA2312(ha)  (DT_MASK(ha) & DT_ISP2312)
#घोषणा IS_QLA2322(ha)  (DT_MASK(ha) & DT_ISP2322)
#घोषणा IS_QLA6312(ha)  (DT_MASK(ha) & DT_ISP6312)
#घोषणा IS_QLA6322(ha)  (DT_MASK(ha) & DT_ISP6322)
#घोषणा IS_QLA2422(ha)  (DT_MASK(ha) & DT_ISP2422)
#घोषणा IS_QLA2432(ha)  (DT_MASK(ha) & DT_ISP2432)
#घोषणा IS_QLA5422(ha)  (DT_MASK(ha) & DT_ISP5422)
#घोषणा IS_QLA5432(ha)  (DT_MASK(ha) & DT_ISP5432)
#घोषणा IS_QLA2532(ha)  (DT_MASK(ha) & DT_ISP2532)
#घोषणा IS_QLA8432(ha)  (DT_MASK(ha) & DT_ISP8432)
#घोषणा IS_QLA8001(ha)	(DT_MASK(ha) & DT_ISP8001)
#घोषणा IS_QLA81XX(ha)	(IS_QLA8001(ha))
#घोषणा IS_QLA82XX(ha)	(DT_MASK(ha) & DT_ISP8021)
#घोषणा IS_QLA8044(ha)  (DT_MASK(ha) & DT_ISP8044)
#घोषणा IS_QLA2031(ha)	(DT_MASK(ha) & DT_ISP2031)
#घोषणा IS_QLA8031(ha)	(DT_MASK(ha) & DT_ISP8031)
#घोषणा IS_QLAFX00(ha)	(DT_MASK(ha) & DT_ISPFX00)
#घोषणा IS_QLA2071(ha)	(DT_MASK(ha) & DT_ISP2071)
#घोषणा IS_QLA2271(ha)	(DT_MASK(ha) & DT_ISP2271)
#घोषणा IS_QLA2261(ha)	(DT_MASK(ha) & DT_ISP2261)
#घोषणा IS_QLA2081(ha)	(DT_MASK(ha) & DT_ISP2081)
#घोषणा IS_QLA2281(ha)	(DT_MASK(ha) & DT_ISP2281)

#घोषणा IS_QLA23XX(ha)  (IS_QLA2300(ha) || IS_QLA2312(ha) || IS_QLA2322(ha) || \
			IS_QLA6312(ha) || IS_QLA6322(ha))
#घोषणा IS_QLA24XX(ha)  (IS_QLA2422(ha) || IS_QLA2432(ha))
#घोषणा IS_QLA54XX(ha)  (IS_QLA5422(ha) || IS_QLA5432(ha))
#घोषणा IS_QLA25XX(ha)  (IS_QLA2532(ha))
#घोषणा IS_QLA83XX(ha)	(IS_QLA2031(ha) || IS_QLA8031(ha))
#घोषणा IS_QLA84XX(ha)  (IS_QLA8432(ha))
#घोषणा IS_QLA27XX(ha)  (IS_QLA2071(ha) || IS_QLA2271(ha) || IS_QLA2261(ha))
#घोषणा IS_QLA28XX(ha)	(IS_QLA2081(ha) || IS_QLA2281(ha))
#घोषणा IS_QLA24XX_TYPE(ha)     (IS_QLA24XX(ha) || IS_QLA54XX(ha) || \
				IS_QLA84XX(ha))
#घोषणा IS_CNA_CAPABLE(ha)	(IS_QLA81XX(ha) || IS_QLA82XX(ha) || \
				IS_QLA8031(ha) || IS_QLA8044(ha))
#घोषणा IS_P3P_TYPE(ha)		(IS_QLA82XX(ha) || IS_QLA8044(ha))
#घोषणा IS_QLA2XXX_MIDTYPE(ha)	(IS_QLA24XX(ha) || IS_QLA84XX(ha) || \
				IS_QLA25XX(ha) || IS_QLA81XX(ha) || \
				IS_QLA82XX(ha) || IS_QLA83XX(ha) || \
				IS_QLA8044(ha) || IS_QLA27XX(ha) || \
				IS_QLA28XX(ha))
#घोषणा IS_MSIX_NACK_CAPABLE(ha) (IS_QLA81XX(ha) || IS_QLA83XX(ha) || \
				IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_NOPOLLING_TYPE(ha)	(IS_QLA81XX(ha) && (ha)->flags.msix_enabled)
#घोषणा IS_FAC_REQUIRED(ha)	(IS_QLA81XX(ha) || IS_QLA83XX(ha) || \
				IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_NOCACHE_VPD_TYPE(ha)	(IS_QLA81XX(ha) || IS_QLA83XX(ha) || \
				IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_ALOGIO_CAPABLE(ha)	(IS_QLA23XX(ha) || IS_FWI2_CAPABLE(ha))

#घोषणा IS_T10_PI_CAPABLE(ha)   ((ha)->device_type & DT_T10_PI)
#घोषणा IS_IIDMA_CAPABLE(ha)    ((ha)->device_type & DT_IIDMA)
#घोषणा IS_FWI2_CAPABLE(ha)     ((ha)->device_type & DT_FWI2)
#घोषणा IS_ZIO_SUPPORTED(ha)    ((ha)->device_type & DT_ZIO_SUPPORTED)
#घोषणा IS_OEM_001(ha)          ((ha)->device_type & DT_OEM_001)
#घोषणा HAS_EXTENDED_IDS(ha)    ((ha)->device_type & DT_EXTENDED_IDS)
#घोषणा IS_CT6_SUPPORTED(ha)	((ha)->device_type & DT_CT6_SUPPORTED)
#घोषणा IS_MQUE_CAPABLE(ha)	((ha)->mqenable || IS_QLA83XX(ha) || \
				IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_BIDI_CAPABLE(ha) \
    (IS_QLA25XX(ha) || IS_QLA2031(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
/* Bit 21 of fw_attributes decides the MCTP capabilities */
#घोषणा IS_MCTP_CAPABLE(ha)	(IS_QLA2031(ha) && \
				((ha)->fw_attributes_ext[0] & BIT_0))
#घोषणा QLA_ABTS_FW_ENABLED(_ha)       ((_ha)->fw_attributes_ext[0] & BIT_14)
#घोषणा QLA_SRB_NVME_LS(_sp) ((_sp)->type == SRB_NVME_LS)
#घोषणा QLA_SRB_NVME_CMD(_sp) ((_sp)->type == SRB_NVME_CMD)
#घोषणा QLA_NVME_IOS(_sp) (QLA_SRB_NVME_CMD(_sp) || QLA_SRB_NVME_LS(_sp))
#घोषणा QLA_LS_ABTS_WAIT_ENABLED(_sp) \
	(QLA_SRB_NVME_LS(_sp) && QLA_ABTS_FW_ENABLED(_sp->fcport->vha->hw))
#घोषणा QLA_CMD_ABTS_WAIT_ENABLED(_sp) \
	(QLA_SRB_NVME_CMD(_sp) && QLA_ABTS_FW_ENABLED(_sp->fcport->vha->hw))
#घोषणा QLA_ABTS_WAIT_ENABLED(_sp) \
	(QLA_NVME_IOS(_sp) && QLA_ABTS_FW_ENABLED(_sp->fcport->vha->hw))

#घोषणा IS_PI_UNINIT_CAPABLE(ha)	(IS_QLA83XX(ha) || IS_QLA27XX(ha))
#घोषणा IS_PI_IPGUARD_CAPABLE(ha)	(IS_QLA83XX(ha) || IS_QLA27XX(ha))
#घोषणा IS_PI_DIFB_DIX0_CAPABLE(ha)	(0)
#घोषणा IS_PI_SPLIT_DET_CAPABLE_HBA(ha)	(IS_QLA83XX(ha) || IS_QLA27XX(ha) || \
					IS_QLA28XX(ha))
#घोषणा IS_PI_SPLIT_DET_CAPABLE(ha)	(IS_PI_SPLIT_DET_CAPABLE_HBA(ha) && \
    (((ha)->fw_attributes_h << 16 | (ha)->fw_attributes) & BIT_22))
#घोषणा IS_ATIO_MSIX_CAPABLE(ha) (IS_QLA83XX(ha) || IS_QLA27XX(ha) || \
				IS_QLA28XX(ha))
#घोषणा IS_TGT_MODE_CAPABLE(ha)	(ha->tgt.atio_q_length)
#घोषणा IS_SHADOW_REG_CAPABLE(ha)  (IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_DPORT_CAPABLE(ha)  (IS_QLA83XX(ha) || IS_QLA27XX(ha) || \
				IS_QLA28XX(ha))
#घोषणा IS_FAWWN_CAPABLE(ha)	(IS_QLA83XX(ha) || IS_QLA27XX(ha) || \
				IS_QLA28XX(ha))
#घोषणा IS_EXCHG_OFFLD_CAPABLE(ha) \
	(IS_QLA81XX(ha) || IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_EXLOGIN_OFFLD_CAPABLE(ha) \
	(IS_QLA25XX(ha) || IS_QLA81XX(ha) || IS_QLA83XX(ha) || \
	 IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा USE_ASYNC_SCAN(ha) (IS_QLA25XX(ha) || IS_QLA81XX(ha) ||\
	IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))

#घोषणा IS_ZIO_THRESHOLD_CAPABLE(ha) \
	((IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) &&\
	 (ha->zio_mode == QLA_ZIO_MODE_6))

	/* HBA serial number */
	uपूर्णांक8_t		serial0;
	uपूर्णांक8_t		serial1;
	uपूर्णांक8_t		serial2;

	/* NVRAM configuration data */
#घोषणा MAX_NVRAM_SIZE  4096
#घोषणा VPD_OFFSET      (MAX_NVRAM_SIZE / 2)
	uपूर्णांक16_t	nvram_size;
	uपूर्णांक16_t	nvram_base;
	व्योम		*nvram;
	uपूर्णांक16_t	vpd_size;
	uपूर्णांक16_t	vpd_base;
	व्योम		*vpd;

	uपूर्णांक16_t	loop_reset_delay;
	uपूर्णांक8_t		retry_count;
	uपूर्णांक8_t		login_समयout;
	uपूर्णांक16_t	r_a_tov;
	पूर्णांक		port_करोwn_retry_count;
	uपूर्णांक8_t		mbx_count;
	uपूर्णांक8_t		aen_mbx_count;
	atomic_t	num_pend_mbx_stage1;
	atomic_t	num_pend_mbx_stage2;
	atomic_t	num_pend_mbx_stage3;
	uपूर्णांक16_t	frame_payload_size;

	uपूर्णांक32_t	login_retry_count;
	/* SNS command पूर्णांकerfaces. */
	ms_iocb_entry_t		*ms_iocb;
	dma_addr_t		ms_iocb_dma;
	काष्ठा ct_sns_pkt	*ct_sns;
	dma_addr_t		ct_sns_dma;
	/* SNS command पूर्णांकerfaces क्रम 2200. */
	काष्ठा sns_cmd_pkt	*sns_cmd;
	dma_addr_t		sns_cmd_dma;

#घोषणा SFP_DEV_SIZE    512
#घोषणा SFP_BLOCK_SIZE  64
#घोषणा SFP_RTDI_LEN	SFP_BLOCK_SIZE

	व्योम		*sfp_data;
	dma_addr_t	sfp_data_dma;

	काष्ठा qla_flt_header *flt;
	dma_addr_t	flt_dma;

#घोषणा XGMAC_DATA_SIZE	4096
	व्योम		*xgmac_data;
	dma_addr_t	xgmac_data_dma;

#घोषणा DCBX_TLV_DATA_SIZE 4096
	व्योम		*dcbx_tlv;
	dma_addr_t	dcbx_tlv_dma;

	काष्ठा task_काष्ठा	*dpc_thपढ़ो;
	uपूर्णांक8_t dpc_active;                  /* DPC routine is active */

	dma_addr_t	gid_list_dma;
	काष्ठा gid_list_info *gid_list;
	पूर्णांक		gid_list_info_size;

	/* Small DMA pool allocations -- maximum 256 bytes in length. */
#घोषणा DMA_POOL_SIZE   256
	काष्ठा dma_pool *s_dma_pool;

	dma_addr_t	init_cb_dma;
	init_cb_t	*init_cb;
	पूर्णांक		init_cb_size;
	dma_addr_t	ex_init_cb_dma;
	काष्ठा ex_init_cb_81xx *ex_init_cb;
	dma_addr_t	sf_init_cb_dma;
	काष्ठा init_sf_cb *sf_init_cb;

	व्योम		*scm_fpin_els_buff;
	uपूर्णांक64_t	scm_fpin_els_buff_size;
	bool		scm_fpin_valid;
	bool		scm_fpin_payload_size;

	व्योम		*async_pd;
	dma_addr_t	async_pd_dma;

#घोषणा ENABLE_EXTENDED_LOGIN	BIT_7

	/* Extended Logins  */
	व्योम		*exlogin_buf;
	dma_addr_t	exlogin_buf_dma;
	uपूर्णांक32_t	exlogin_size;

#घोषणा ENABLE_EXCHANGE_OFFLD	BIT_2

	/* Exchange Offload */
	व्योम		*exchoffld_buf;
	dma_addr_t	exchoffld_buf_dma;
	पूर्णांक		exchoffld_size;
	पूर्णांक 		exchoffld_count;

	/* n2n */
	काष्ठा fc_els_flogi plogi_els_payld;
#घोषणा LOGIN_TEMPLATE_SIZE (माप(काष्ठा fc_els_flogi) - 4)

	व्योम            *swl;

	/* These are used by mailbox operations. */
	uपूर्णांक16_t mailbox_out[MAILBOX_REGISTER_COUNT];
	uपूर्णांक32_t mailbox_out32[MAILBOX_REGISTER_COUNT];
	uपूर्णांक32_t aenmb[AEN_MAILBOX_REGISTER_COUNT_FX00];

	mbx_cmd_t	*mcp;
	काष्ठा mbx_cmd_32	*mcp32;

	अचिन्हित दीर्घ	mbx_cmd_flags;
#घोषणा MBX_INTERRUPT		1
#घोषणा MBX_INTR_WAIT		2
#घोषणा MBX_UPDATE_FLASH_ACTIVE	3

	काष्ठा mutex vport_lock;        /* Virtual port synchronization */
	spinlock_t vport_slock; /* order is hardware_lock, then vport_slock */
	काष्ठा mutex mq_lock;        /* multi-queue synchronization */
	काष्ठा completion mbx_cmd_comp; /* Serialize mbx access */
	काष्ठा completion mbx_पूर्णांकr_comp;  /* Used क्रम completion notअगरication */
	काष्ठा completion dcbx_comp;	/* For set port config notअगरication */
	काष्ठा completion lb_portup_comp; /* Used to रुको क्रम link up during
					   * loopback */
#घोषणा DCBX_COMP_TIMEOUT	20
#घोषणा LB_PORTUP_COMP_TIMEOUT	10

	पूर्णांक notअगरy_dcbx_comp;
	पूर्णांक notअगरy_lb_portup_comp;
	काष्ठा mutex selflogin_lock;

	/* Basic firmware related inक्रमmation. */
	uपूर्णांक16_t	fw_major_version;
	uपूर्णांक16_t	fw_minor_version;
	uपूर्णांक16_t	fw_subminor_version;
	uपूर्णांक16_t	fw_attributes;
	uपूर्णांक16_t	fw_attributes_h;
#घोषणा FW_ATTR_H_NVME_FBURST 	BIT_1
#घोषणा FW_ATTR_H_NVME		BIT_10
#घोषणा FW_ATTR_H_NVME_UPDATED  BIT_14

	/* About firmware SCM support */
#घोषणा FW_ATTR_EXT0_SCM_SUPPORTED	BIT_12
	/* Brocade fabric attached */
#घोषणा FW_ATTR_EXT0_SCM_BROCADE	0x00001000
	/* Cisco fabric attached */
#घोषणा FW_ATTR_EXT0_SCM_CISCO		0x00002000
#घोषणा FW_ATTR_EXT0_NVME2	BIT_13
	uपूर्णांक16_t	fw_attributes_ext[2];
	uपूर्णांक32_t	fw_memory_size;
	uपूर्णांक32_t	fw_transfer_size;
	uपूर्णांक32_t	fw_srisc_address;
#घोषणा RISC_START_ADDRESS_2100 0x1000
#घोषणा RISC_START_ADDRESS_2300 0x800
#घोषणा RISC_START_ADDRESS_2400 0x100000

	uपूर्णांक16_t	orig_fw_tgt_xcb_count;
	uपूर्णांक16_t	cur_fw_tgt_xcb_count;
	uपूर्णांक16_t	orig_fw_xcb_count;
	uपूर्णांक16_t	cur_fw_xcb_count;
	uपूर्णांक16_t	orig_fw_iocb_count;
	uपूर्णांक16_t	cur_fw_iocb_count;
	uपूर्णांक16_t	fw_max_fcf_count;

	uपूर्णांक32_t	fw_shared_ram_start;
	uपूर्णांक32_t	fw_shared_ram_end;
	uपूर्णांक32_t	fw_ddr_ram_start;
	uपूर्णांक32_t	fw_ddr_ram_end;

	uपूर्णांक16_t	fw_options[16];         /* slots: 1,2,3,10,11 */
	uपूर्णांक8_t		fw_seriallink_options[4];
	__le16		fw_seriallink_options24[4];

	uपूर्णांक8_t		serdes_version[3];
	uपूर्णांक8_t		mpi_version[3];
	uपूर्णांक32_t	mpi_capabilities;
	uपूर्णांक8_t		phy_version[3];
	uपूर्णांक8_t		pep_version[3];

	/* Firmware dump ढाँचा */
	काष्ठा fwdt अणु
		व्योम *ढाँचा;
		uदीर्घ length;
		uदीर्घ dump_size;
	पूर्ण fwdt[2];
	काष्ठा qla2xxx_fw_dump *fw_dump;
	uपूर्णांक32_t	fw_dump_len;
	u32		fw_dump_alloc_len;
	bool		fw_dumped;
	अचिन्हित दीर्घ	fw_dump_cap_flags;
#घोषणा RISC_PAUSE_CMPL		0
#घोषणा DMA_SHUTDOWN_CMPL	1
#घोषणा ISP_RESET_CMPL		2
#घोषणा RISC_RDY_AFT_RESET	3
#घोषणा RISC_SRAM_DUMP_CMPL	4
#घोषणा RISC_EXT_MEM_DUMP_CMPL	5
#घोषणा ISP_MBX_RDY		6
#घोषणा ISP_SOFT_RESET_CMPL	7
	पूर्णांक		fw_dump_पढ़ोing;
	व्योम		*mpi_fw_dump;
	u32		mpi_fw_dump_len;
	अचिन्हित पूर्णांक	mpi_fw_dump_पढ़ोing:1;
	अचिन्हित पूर्णांक	mpi_fw_dumped:1;
	पूर्णांक		prev_minidump_failed;
	dma_addr_t	eft_dma;
	व्योम		*eft;
/* Current size of mctp dump is 0x086064 bytes */
#घोषणा MCTP_DUMP_SIZE  0x086064
	dma_addr_t	mctp_dump_dma;
	व्योम		*mctp_dump;
	पूर्णांक		mctp_dumped;
	पूर्णांक		mctp_dump_पढ़ोing;
	uपूर्णांक32_t	chain_offset;
	काष्ठा dentry *dfs_dir;
	काष्ठा dentry *dfs_fce;
	काष्ठा dentry *dfs_tgt_counters;
	काष्ठा dentry *dfs_fw_resource_cnt;

	dma_addr_t	fce_dma;
	व्योम		*fce;
	uपूर्णांक32_t	fce_bufs;
	uपूर्णांक16_t	fce_mb[8];
	uपूर्णांक64_t	fce_wr, fce_rd;
	काष्ठा mutex	fce_mutex;

	uपूर्णांक32_t	pci_attr;
	uपूर्णांक16_t	chip_revision;

	uपूर्णांक16_t	product_id[4];

	uपूर्णांक8_t		model_number[16+1];
	अक्षर		model_desc[80];
	uपूर्णांक8_t		adapter_id[16+1];

	/* Option ROM inक्रमmation. */
	अक्षर		*optrom_buffer;
	uपूर्णांक32_t	optrom_size;
	पूर्णांक		optrom_state;
#घोषणा QLA_SWAITING	0
#घोषणा QLA_SREADING	1
#घोषणा QLA_SWRITING	2
	uपूर्णांक32_t	optrom_region_start;
	uपूर्णांक32_t	optrom_region_size;
	काष्ठा mutex	optrom_mutex;

/* PCI expansion ROM image inक्रमmation. */
#घोषणा ROM_CODE_TYPE_BIOS	0
#घोषणा ROM_CODE_TYPE_FCODE	1
#घोषणा ROM_CODE_TYPE_EFI	3
	uपूर्णांक8_t 	bios_revision[2];
	uपूर्णांक8_t 	efi_revision[2];
	uपूर्णांक8_t 	fcode_revision[16];
	uपूर्णांक32_t	fw_revision[4];

	uपूर्णांक32_t	gold_fw_version[4];

	/* Offsets क्रम flash/nvram access (set to ~0 अगर not used). */
	uपूर्णांक32_t	flash_conf_off;
	uपूर्णांक32_t	flash_data_off;
	uपूर्णांक32_t	nvram_conf_off;
	uपूर्णांक32_t	nvram_data_off;

	uपूर्णांक32_t	fdt_wrt_disable;
	uपूर्णांक32_t	fdt_wrt_enable;
	uपूर्णांक32_t	fdt_erase_cmd;
	uपूर्णांक32_t	fdt_block_size;
	uपूर्णांक32_t	fdt_unprotect_sec_cmd;
	uपूर्णांक32_t	fdt_protect_sec_cmd;
	uपूर्णांक32_t	fdt_wrt_sts_reg_cmd;

	काष्ठा अणु
		uपूर्णांक32_t	flt_region_flt;
		uपूर्णांक32_t	flt_region_fdt;
		uपूर्णांक32_t	flt_region_boot;
		uपूर्णांक32_t	flt_region_boot_sec;
		uपूर्णांक32_t	flt_region_fw;
		uपूर्णांक32_t	flt_region_fw_sec;
		uपूर्णांक32_t	flt_region_vpd_nvram;
		uपूर्णांक32_t	flt_region_vpd_nvram_sec;
		uपूर्णांक32_t	flt_region_vpd;
		uपूर्णांक32_t	flt_region_vpd_sec;
		uपूर्णांक32_t	flt_region_nvram;
		uपूर्णांक32_t	flt_region_nvram_sec;
		uपूर्णांक32_t	flt_region_npiv_conf;
		uपूर्णांक32_t	flt_region_gold_fw;
		uपूर्णांक32_t	flt_region_fcp_prio;
		uपूर्णांक32_t	flt_region_bootload;
		uपूर्णांक32_t	flt_region_img_status_pri;
		uपूर्णांक32_t	flt_region_img_status_sec;
		uपूर्णांक32_t	flt_region_aux_img_status_pri;
		uपूर्णांक32_t	flt_region_aux_img_status_sec;
	पूर्ण;
	uपूर्णांक8_t         active_image;

	/* Needed क्रम BEACON */
	uपूर्णांक16_t        beacon_blink_led;
	uपूर्णांक8_t         beacon_color_state;
#घोषणा QLA_LED_GRN_ON		0x01
#घोषणा QLA_LED_YLW_ON		0x02
#घोषणा QLA_LED_ABR_ON		0x04
#घोषणा QLA_LED_ALL_ON		0x07	/* yellow, green, amber. */
					/* ISP2322: red, green, amber. */
	uपूर्णांक16_t        zio_mode;
	uपूर्णांक16_t        zio_समयr;

	काष्ठा qla_msix_entry *msix_entries;

	काष्ठा list_head        vp_list;        /* list of VP */
	अचिन्हित दीर्घ   vp_idx_map[(MAX_MULTI_ID_FABRIC / 8) /
			माप(अचिन्हित दीर्घ)];
	uपूर्णांक16_t        num_vhosts;     /* number of vports created */
	uपूर्णांक16_t        num_vsans;      /* number of vsan created */
	uपूर्णांक16_t        max_npiv_vports;        /* 63 or 125 per topoloty */
	पूर्णांक             cur_vport_count;

	काष्ठा qla_chip_state_84xx *cs84xx;
	काष्ठा isp_operations *isp_ops;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा qlfc_fw fw_buf;

	/* FCP_CMND priority support */
	काष्ठा qla_fcp_prio_cfg *fcp_prio_cfg;

	काष्ठा dma_pool *dl_dma_pool;
#घोषणा DSD_LIST_DMA_POOL_SIZE  512

	काष्ठा dma_pool *fcp_cmnd_dma_pool;
	mempool_t       *ctx_mempool;
#घोषणा FCP_CMND_DMA_POOL_SIZE 512

	व्योम __iomem	*nx_pcibase;		/* Base I/O address */
	व्योम __iomem	*nxdb_rd_ptr;		/* Doorbell पढ़ो poपूर्णांकer */
	व्योम __iomem	*nxdb_wr_ptr;		/* Door bell ग_लिखो poपूर्णांकer */

	uपूर्णांक32_t	crb_win;
	uपूर्णांक32_t	curr_winकरोw;
	uपूर्णांक32_t	ddr_mn_winकरोw;
	अचिन्हित दीर्घ	mn_win_crb;
	अचिन्हित दीर्घ	ms_win_crb;
	पूर्णांक		qdr_sn_winकरोw;
	uपूर्णांक32_t	fcoe_dev_init_समयout;
	uपूर्णांक32_t	fcoe_reset_समयout;
	rwlock_t	hw_lock;
	uपूर्णांक16_t	portnum;		/* port number */
	पूर्णांक		link_width;
	काष्ठा fw_blob	*hablob;
	काष्ठा qla82xx_legacy_पूर्णांकr_set nx_legacy_पूर्णांकr;

	uपूर्णांक16_t	gbl_dsd_inuse;
	uपूर्णांक16_t	gbl_dsd_avail;
	काष्ठा list_head gbl_dsd_list;
#घोषणा NUM_DSD_CHAIN 4096

	uपूर्णांक8_t fw_type;
	uपूर्णांक32_t file_prd_off;	/* File firmware product offset */

	uपूर्णांक32_t	md_ढाँचा_size;
	व्योम		*md_पंचांगplt_hdr;
	dma_addr_t      md_पंचांगplt_hdr_dma;
	व्योम            *md_dump;
	uपूर्णांक32_t	md_dump_size;

	व्योम		*loop_id_map;

	/* QLA83XX IDC specअगरic fields */
	uपूर्णांक32_t	idc_audit_ts;
	uपूर्णांक32_t	idc_extend_पंचांगo;

	/* DPC low-priority workqueue */
	काष्ठा workqueue_काष्ठा *dpc_lp_wq;
	काष्ठा work_काष्ठा idc_aen;
	/* DPC high-priority workqueue */
	काष्ठा workqueue_काष्ठा *dpc_hp_wq;
	काष्ठा work_काष्ठा nic_core_reset;
	काष्ठा work_काष्ठा idc_state_handler;
	काष्ठा work_काष्ठा nic_core_unrecoverable;
	काष्ठा work_काष्ठा board_disable;

	काष्ठा mr_data_fx00 mr;
	uपूर्णांक32_t chip_reset;

	काष्ठा qlt_hw_data tgt;
	पूर्णांक	allow_cna_fw_dump;
	uपूर्णांक32_t fw_ability_mask;
	uपूर्णांक16_t min_supported_speed;
	uपूर्णांक16_t max_supported_speed;

	/* DMA pool क्रम the DIF bundling buffers */
	काष्ठा dma_pool *dअगर_bundl_pool;
	#घोषणा DIF_BUNDLING_DMA_POOL_SIZE  1024
	काष्ठा अणु
		काष्ठा अणु
			काष्ठा list_head head;
			uपूर्णांक count;
		पूर्ण good;
		काष्ठा अणु
			काष्ठा list_head head;
			uपूर्णांक count;
		पूर्ण unusable;
	पूर्ण pool;

	अचिन्हित दीर्घ दीर्घ dअगर_bundle_crossed_pages;
	अचिन्हित दीर्घ दीर्घ dअगर_bundle_पढ़ोs;
	अचिन्हित दीर्घ दीर्घ dअगर_bundle_ग_लिखोs;
	अचिन्हित दीर्घ दीर्घ dअगर_bundle_kallocs;
	अचिन्हित दीर्घ दीर्घ dअगर_bundle_dma_allocs;

	atomic_t        nvme_active_aen_cnt;
	uपूर्णांक16_t        nvme_last_rptd_aen;             /* Last recorded aen count */

	uपूर्णांक8_t fc4_type_priority;

	atomic_t zio_threshold;
	uपूर्णांक16_t last_zio_threshold;

#घोषणा DEFAULT_ZIO_THRESHOLD 5

	काष्ठा qla_hw_data_stat stat;
	pci_error_state_t pci_error_state;
पूर्ण;

काष्ठा active_regions अणु
	uपूर्णांक8_t global;
	काष्ठा अणु
		uपूर्णांक8_t board_config;
		uपूर्णांक8_t vpd_nvram;
		uपूर्णांक8_t npiv_config_0_1;
		uपूर्णांक8_t npiv_config_2_3;
	पूर्ण aux;
पूर्ण;

#घोषणा FW_ABILITY_MAX_SPEED_MASK	0xFUL
#घोषणा FW_ABILITY_MAX_SPEED_16G	0x0
#घोषणा FW_ABILITY_MAX_SPEED_32G	0x1
#घोषणा FW_ABILITY_MAX_SPEED(ha)	\
	(ha->fw_ability_mask & FW_ABILITY_MAX_SPEED_MASK)

#घोषणा QLA_GET_DATA_RATE	0
#घोषणा QLA_SET_DATA_RATE_NOLR	1
#घोषणा QLA_SET_DATA_RATE_LR	2 /* Set speed and initiate LR */

#घोषणा QLA_DEFAULT_PAYLOAD_SIZE	64
/*
 * This item might be allocated with a size > माप(काष्ठा purex_item).
 * The "size" variable gives the size of the payload (which
 * is variable) starting at "iocb".
 */
काष्ठा purex_item अणु
	काष्ठा list_head list;
	काष्ठा scsi_qla_host *vha;
	व्योम (*process_item)(काष्ठा scsi_qla_host *vha,
			     काष्ठा purex_item *pkt);
	atomic_t in_use;
	uपूर्णांक16_t size;
	काष्ठा अणु
		uपूर्णांक8_t iocb[64];
	पूर्ण iocb;
पूर्ण;

#घोषणा SCM_FLAG_RDF_REJECT		0x00
#घोषणा SCM_FLAG_RDF_COMPLETED		0x01

#घोषणा QLA_CON_PRIMITIVE_RECEIVED	0x1
#घोषणा QLA_CONGESTION_ARB_WARNING	0x1
#घोषणा QLA_CONGESTION_ARB_ALARM	0X2

/*
 * Qlogic scsi host काष्ठाure
 */
प्रकार काष्ठा scsi_qla_host अणु
	काष्ठा list_head list;
	काष्ठा list_head vp_fcports;	/* list of fcports */
	काष्ठा list_head work_list;
	spinlock_t work_lock;
	काष्ठा work_काष्ठा iocb_work;

	/* Commonly used flags and state inक्रमmation. */
	काष्ठा Scsi_Host *host;
	अचिन्हित दीर्घ	host_no;
	uपूर्णांक8_t		host_str[16];

	अस्थिर काष्ठा अणु
		uपूर्णांक32_t	init_करोne		:1;
		uपूर्णांक32_t	online			:1;
		uपूर्णांक32_t	reset_active		:1;

		uपूर्णांक32_t	management_server_logged_in :1;
		uपूर्णांक32_t	process_response_queue	:1;
		uपूर्णांक32_t	dअगरdix_supported:1;
		uपूर्णांक32_t	delete_progress:1;

		uपूर्णांक32_t	fw_tgt_reported:1;
		uपूर्णांक32_t	bbcr_enable:1;
		uपूर्णांक32_t	qpairs_available:1;
		uपूर्णांक32_t	qpairs_req_created:1;
		uपूर्णांक32_t	qpairs_rsp_created:1;
		uपूर्णांक32_t	nvme_enabled:1;
		uपूर्णांक32_t        nvme_first_burst:1;
		uपूर्णांक32_t        nvme2_enabled:1;
	पूर्ण flags;

	atomic_t	loop_state;
#घोषणा LOOP_TIMEOUT	1
#घोषणा LOOP_DOWN	2
#घोषणा LOOP_UP		3
#घोषणा LOOP_UPDATE	4
#घोषणा LOOP_READY	5
#घोषणा LOOP_DEAD	6

	अचिन्हित दीर्घ   relogin_jअगर;
	अचिन्हित दीर्घ   dpc_flags;
#घोषणा RESET_MARKER_NEEDED	0	/* Send marker to ISP. */
#घोषणा RESET_ACTIVE		1
#घोषणा ISP_ABORT_NEEDED	2	/* Initiate ISP पात. */
#घोषणा ABORT_ISP_ACTIVE	3	/* ISP पात in progress. */
#घोषणा LOOP_RESYNC_NEEDED	4	/* Device Resync needed. */
#घोषणा LOOP_RESYNC_ACTIVE	5
#घोषणा LOCAL_LOOP_UPDATE	6	/* Perक्रमm a local loop update. */
#घोषणा RSCN_UPDATE		7	/* Perक्रमm an RSCN update. */
#घोषणा RELOGIN_NEEDED		8
#घोषणा REGISTER_FC4_NEEDED	9	/* SNS FC4 registration required. */
#घोषणा ISP_ABORT_RETRY		10	/* ISP पातed. */
#घोषणा BEACON_BLINK_NEEDED	11
#घोषणा REGISTER_FDMI_NEEDED	12
#घोषणा FCPORT_UPDATE_NEEDED	13
#घोषणा VP_DPC_NEEDED		14	/* wake up क्रम VP dpc handling */
#घोषणा UNLOADING		15
#घोषणा NPIV_CONFIG_NEEDED	16
#घोषणा ISP_UNRECOVERABLE	17
#घोषणा FCOE_CTX_RESET_NEEDED	18	/* Initiate FCoE context reset */
#घोषणा MPI_RESET_NEEDED	19	/* Initiate MPI FW reset */
#घोषणा ISP_QUIESCE_NEEDED	20	/* Driver need some quiescence */
#घोषणा N2N_LINK_RESET		21
#घोषणा PORT_UPDATE_NEEDED	22
#घोषणा FX00_RESET_RECOVERY	23
#घोषणा FX00_TARGET_SCAN	24
#घोषणा FX00_CRITEMP_RECOVERY	25
#घोषणा FX00_HOST_INFO_RESEND	26
#घोषणा QPAIR_ONLINE_CHECK_NEEDED	27
#घोषणा DO_EEH_RECOVERY		28
#घोषणा DETECT_SFP_CHANGE	29
#घोषणा N2N_LOGIN_NEEDED	30
#घोषणा IOCB_WORK_ACTIVE	31
#घोषणा SET_ZIO_THRESHOLD_NEEDED 32
#घोषणा ISP_ABORT_TO_ROM	33
#घोषणा VPORT_DELETE		34

#घोषणा PROCESS_PUREX_IOCB	63

	अचिन्हित दीर्घ	pci_flags;
#घोषणा PFLG_DISCONNECTED	0	/* PCI device हटाओd */
#घोषणा PFLG_DRIVER_REMOVING	1	/* PCI driver .हटाओ */
#घोषणा PFLG_DRIVER_PROBING	2	/* PCI driver .probe */

	uपूर्णांक32_t	device_flags;
#घोषणा SWITCH_FOUND		BIT_0
#घोषणा DFLG_NO_CABLE		BIT_1
#घोषणा DFLG_DEV_FAILED		BIT_5

	/* ISP configuration data. */
	uपूर्णांक16_t	loop_id;		/* Host adapter loop id */
	uपूर्णांक16_t        self_login_loop_id;     /* host adapter loop id
						 * get it on self login
						 */
	fc_port_t       bidir_fcport;		/* fcport used क्रम bidir cmnds
						 * no need of allocating it क्रम
						 * each command
						 */

	port_id_t	d_id;			/* Host adapter port id */
	uपूर्णांक8_t		marker_needed;
	uपूर्णांक16_t	mgmt_svr_loop_id;



	/* Timeout समयrs. */
	uपूर्णांक8_t         loop_करोwn_पात_समय;    /* port करोwn समयr */
	atomic_t        loop_करोwn_समयr;         /* loop करोwn समयr */
	uपूर्णांक8_t         link_करोwn_समयout;       /* link करोwn समयout */

	uपूर्णांक32_t        समयr_active;
	काष्ठा समयr_list        समयr;

	uपूर्णांक8_t		node_name[WWN_SIZE];
	uपूर्णांक8_t		port_name[WWN_SIZE];
	uपूर्णांक8_t		fabric_node_name[WWN_SIZE];
	uपूर्णांक8_t		fabric_port_name[WWN_SIZE];

	काष्ठा		nvme_fc_local_port *nvme_local_port;
	काष्ठा completion nvme_del_करोne;

	uपूर्णांक16_t	fcoe_vlan_id;
	uपूर्णांक16_t	fcoe_fcf_idx;
	uपूर्णांक8_t		fcoe_vn_port_mac[6];

	/* list of commands रुकोing on workqueue */
	काष्ठा list_head	qla_cmd_list;
	काष्ठा list_head	qla_sess_op_cmd_list;
	काष्ठा list_head	unknown_atio_list;
	spinlock_t		cmd_list_lock;
	काष्ठा delayed_work	unknown_atio_work;

	/* Counter to detect races between ELS and RSCN events */
	atomic_t		generation_tick;
	/* Time when global fcport update has been scheduled */
	पूर्णांक			total_fcport_update_gen;
	/* List of pending LOGOs, रक्षित by tgt_mutex */
	काष्ठा list_head	logo_list;
	/* List of pending PLOGI acks, रक्षित by hw lock */
	काष्ठा list_head	plogi_ack_list;

	काष्ठा list_head	qp_list;

	uपूर्णांक32_t	vp_पात_cnt;

	काष्ठा fc_vport	*fc_vport;	/* holds fc_vport * क्रम each vport */
	uपूर्णांक16_t        vp_idx;		/* vport ID */
	काष्ठा qla_qpair *qpair;	/* base qpair */

	अचिन्हित दीर्घ		vp_flags;
#घोषणा VP_IDX_ACQUIRED		0	/* bit no 0 */
#घोषणा VP_CREATE_NEEDED	1
#घोषणा VP_BIND_NEEDED		2
#घोषणा VP_DELETE_NEEDED	3
#घोषणा VP_SCR_NEEDED		4	/* State Change Request registration */
#घोषणा VP_CONFIG_OK		5	/* Flag to cfg VP, अगर FW is पढ़ोy */
	atomic_t 		vp_state;
#घोषणा VP_OFFLINE		0
#घोषणा VP_ACTIVE		1
#घोषणा VP_FAILED		2
// #घोषणा VP_DISABLE		3
	uपूर्णांक16_t 	vp_err_state;
	uपूर्णांक16_t	vp_prev_err_state;
#घोषणा VP_ERR_UNKWN		0
#घोषणा VP_ERR_PORTDWN		1
#घोषणा VP_ERR_FAB_UNSUPPORTED	2
#घोषणा VP_ERR_FAB_NORESOURCES	3
#घोषणा VP_ERR_FAB_LOGOUT	4
#घोषणा VP_ERR_ADAP_NORESOURCES	5
	काष्ठा qla_hw_data *hw;
	काष्ठा scsi_qlt_host vha_tgt;
	काष्ठा req_que *req;
	पूर्णांक		fw_heartbeat_counter;
	पूर्णांक		seconds_since_last_heartbeat;
	काष्ठा fc_host_statistics fc_host_stat;
	काष्ठा qla_statistics qla_stats;
	काष्ठा bidi_statistics bidi_stats;
	atomic_t	vref_count;
	काष्ठा qla8044_reset_ढाँचा reset_पंचांगplt;
	uपूर्णांक16_t	bbcr;

	uपूर्णांक16_t u_ql2xexchoffld;
	uपूर्णांक16_t u_ql2xiniexchg;
	uपूर्णांक16_t qlini_mode;
	uपूर्णांक16_t ql2xexchoffld;
	uपूर्णांक16_t ql2xiniexchg;

	काष्ठा dentry *dfs_rport_root;

	काष्ठा purex_list अणु
		काष्ठा list_head head;
		spinlock_t lock;
	पूर्ण purex_list;
	काष्ठा purex_item शेष_item;

	काष्ठा name_list_extended gnl;
	/* Count of active session/fcport */
	पूर्णांक fcport_count;
	रुको_queue_head_t fcport_रुकोQ;
	रुको_queue_head_t vref_रुकोq;
	uपूर्णांक8_t min_supported_speed;
	uपूर्णांक8_t n2n_node_name[WWN_SIZE];
	uपूर्णांक8_t n2n_port_name[WWN_SIZE];
	uपूर्णांक16_t	n2n_id;
	__le16 dport_data[4];
	काष्ठा list_head gpnid_list;
	काष्ठा fab_scan scan;
	uपूर्णांक8_t	scm_fabric_connection_flags;

	अचिन्हित पूर्णांक irq_offset;

	u64 hw_err_cnt;
	u64 पूर्णांकerface_err_cnt;
	u64 cmd_समयout_cnt;
	u64 reset_cmd_err_cnt;
	u64 link_करोwn_समय;
	u64 लघु_link_करोwn_cnt;
पूर्ण scsi_qla_host_t;

काष्ठा qla27xx_image_status अणु
	uपूर्णांक8_t image_status_mask;
	__le16	generation;
	uपूर्णांक8_t ver_major;
	uपूर्णांक8_t ver_minor;
	uपूर्णांक8_t biपंचांगap;		/* 28xx only */
	uपूर्णांक8_t reserved[2];
	__le32	checksum;
	__le32	signature;
पूर्ण __packed;

/* 28xx aux image status bimap values */
#घोषणा QLA28XX_AUX_IMG_BOARD_CONFIG		BIT_0
#घोषणा QLA28XX_AUX_IMG_VPD_NVRAM		BIT_1
#घोषणा QLA28XX_AUX_IMG_NPIV_CONFIG_0_1		BIT_2
#घोषणा QLA28XX_AUX_IMG_NPIV_CONFIG_2_3		BIT_3

#घोषणा SET_VP_IDX	1
#घोषणा SET_AL_PA	2
#घोषणा RESET_VP_IDX	3
#घोषणा RESET_AL_PA	4
काष्ठा qla_tgt_vp_map अणु
	uपूर्णांक8_t	idx;
	scsi_qla_host_t *vha;
पूर्ण;

काष्ठा qla2_sgx अणु
	dma_addr_t		dma_addr;	/* OUT */
	uपूर्णांक32_t		dma_len;	/* OUT */

	uपूर्णांक32_t		tot_bytes;	/* IN */
	काष्ठा scatterlist	*cur_sg;	/* IN */

	/* क्रम book keeping, bzero on initial invocation */
	uपूर्णांक32_t		bytes_consumed;
	uपूर्णांक32_t		num_bytes;
	uपूर्णांक32_t		tot_partial;

	/* क्रम debugging */
	uपूर्णांक32_t		num_sg;
	srb_t			*sp;
पूर्ण;

#घोषणा QLA_FW_STARTED(_ha) अणु			\
	पूर्णांक i;					\
	_ha->flags.fw_started = 1;		\
	_ha->base_qpair->fw_started = 1;	\
	क्रम (i = 0; i < _ha->max_qpairs; i++) अणु	\
	अगर (_ha->queue_pair_map[i])	\
	_ha->queue_pair_map[i]->fw_started = 1;	\
	पूर्ण					\
पूर्ण

#घोषणा QLA_FW_STOPPED(_ha) अणु			\
	पूर्णांक i;					\
	_ha->flags.fw_started = 0;		\
	_ha->base_qpair->fw_started = 0;	\
	क्रम (i = 0; i < _ha->max_qpairs; i++) अणु	\
	अगर (_ha->queue_pair_map[i])	\
	_ha->queue_pair_map[i]->fw_started = 0;	\
	पूर्ण					\
पूर्ण


#घोषणा SFUB_CHECKSUM_SIZE	4

काष्ठा secure_flash_update_block अणु
	uपूर्णांक32_t	block_info;
	uपूर्णांक32_t	signature_lo;
	uपूर्णांक32_t	signature_hi;
	uपूर्णांक32_t	signature_upper[0x3e];
पूर्ण;

काष्ठा secure_flash_update_block_pk अणु
	uपूर्णांक32_t	block_info;
	uपूर्णांक32_t	signature_lo;
	uपूर्णांक32_t	signature_hi;
	uपूर्णांक32_t	signature_upper[0x3e];
	uपूर्णांक32_t	खुला_key[0x41];
पूर्ण;

/*
 * Macros to help code, मुख्यtain, etc.
 */
#घोषणा LOOP_TRANSITION(ha) \
	(test_bit(ISP_ABORT_NEEDED, &ha->dpc_flags) || \
	 test_bit(LOOP_RESYNC_NEEDED, &ha->dpc_flags) || \
	 atomic_पढ़ो(&ha->loop_state) == LOOP_DOWN)

#घोषणा STATE_TRANSITION(ha) \
		(test_bit(ISP_ABORT_NEEDED, &ha->dpc_flags) || \
			 test_bit(LOOP_RESYNC_NEEDED, &ha->dpc_flags))

#घोषणा QLA_VHA_MARK_BUSY(__vha, __bail) करो अणु		\
	atomic_inc(&__vha->vref_count);			\
	mb();						\
	अगर (__vha->flags.delete_progress) अणु		\
		atomic_dec(&__vha->vref_count);		\
		wake_up(&__vha->vref_रुकोq);		\
		__bail = 1;				\
	पूर्ण अन्यथा अणु					\
		__bail = 0;				\
	पूर्ण						\
पूर्ण जबतक (0)

#घोषणा QLA_VHA_MARK_NOT_BUSY(__vha) करो अणु		\
	atomic_dec(&__vha->vref_count);			\
	wake_up(&__vha->vref_रुकोq);			\
पूर्ण जबतक (0)						\

#घोषणा QLA_QPAIR_MARK_BUSY(__qpair, __bail) करो अणु	\
	atomic_inc(&__qpair->ref_count);		\
	mb();						\
	अगर (__qpair->delete_in_progress) अणु		\
		atomic_dec(&__qpair->ref_count);	\
		__bail = 1;				\
	पूर्ण अन्यथा अणु					\
	       __bail = 0;				\
	पूर्ण						\
पूर्ण जबतक (0)

#घोषणा QLA_QPAIR_MARK_NOT_BUSY(__qpair)		\
	atomic_dec(&__qpair->ref_count)

#घोषणा QLA_ENA_CONF(_ha) अणु\
    पूर्णांक i;\
    _ha->base_qpair->enable_explicit_conf = 1;	\
    क्रम (i = 0; i < _ha->max_qpairs; i++) अणु	\
	अगर (_ha->queue_pair_map[i])		\
	    _ha->queue_pair_map[i]->enable_explicit_conf = 1; \
    पूर्ण						\
पूर्ण

#घोषणा QLA_DIS_CONF(_ha) अणु\
    पूर्णांक i;\
    _ha->base_qpair->enable_explicit_conf = 0;	\
    क्रम (i = 0; i < _ha->max_qpairs; i++) अणु	\
	अगर (_ha->queue_pair_map[i])		\
	    _ha->queue_pair_map[i]->enable_explicit_conf = 0; \
    पूर्ण						\
पूर्ण

/*
 * qla2x00 local function वापस status codes
 */
#घोषणा MBS_MASK		0x3fff

#घोषणा QLA_SUCCESS		(MBS_COMMAND_COMPLETE & MBS_MASK)
#घोषणा QLA_INVALID_COMMAND	(MBS_INVALID_COMMAND & MBS_MASK)
#घोषणा QLA_INTERFACE_ERROR	(MBS_HOST_INTERFACE_ERROR & MBS_MASK)
#घोषणा QLA_TEST_FAILED		(MBS_TEST_FAILED & MBS_MASK)
#घोषणा QLA_COMMAND_ERROR	(MBS_COMMAND_ERROR & MBS_MASK)
#घोषणा QLA_PARAMETER_ERROR	(MBS_COMMAND_PARAMETER_ERROR & MBS_MASK)
#घोषणा QLA_PORT_ID_USED	(MBS_PORT_ID_USED & MBS_MASK)
#घोषणा QLA_LOOP_ID_USED	(MBS_LOOP_ID_USED & MBS_MASK)
#घोषणा QLA_ALL_IDS_IN_USE	(MBS_ALL_IDS_IN_USE & MBS_MASK)
#घोषणा QLA_NOT_LOGGED_IN	(MBS_NOT_LOGGED_IN & MBS_MASK)

#घोषणा QLA_FUNCTION_TIMEOUT		0x100
#घोषणा QLA_FUNCTION_PARAMETER_ERROR	0x101
#घोषणा QLA_FUNCTION_FAILED		0x102
#घोषणा QLA_MEMORY_ALLOC_FAILED		0x103
#घोषणा QLA_LOCK_TIMEOUT		0x104
#घोषणा QLA_ABORTED			0x105
#घोषणा QLA_SUSPENDED			0x106
#घोषणा QLA_BUSY			0x107
#घोषणा QLA_ALREADY_REGISTERED		0x109
#घोषणा QLA_OS_TIMER_EXPIRED		0x10a

#घोषणा NVRAM_DELAY()		udelay(10)

/*
 * Flash support definitions
 */
#घोषणा OPTROM_SIZE_2300	0x20000
#घोषणा OPTROM_SIZE_2322	0x100000
#घोषणा OPTROM_SIZE_24XX	0x100000
#घोषणा OPTROM_SIZE_25XX	0x200000
#घोषणा OPTROM_SIZE_81XX	0x400000
#घोषणा OPTROM_SIZE_82XX	0x800000
#घोषणा OPTROM_SIZE_83XX	0x1000000
#घोषणा OPTROM_SIZE_28XX	0x2000000

#घोषणा OPTROM_BURST_SIZE	0x1000
#घोषणा OPTROM_BURST_DWORDS	(OPTROM_BURST_SIZE / 4)

#घोषणा	QLA_DSDS_PER_IOCB	37

#घोषणा CMD_SP(Cmnd)		((Cmnd)->SCp.ptr)

#घोषणा QLA_SG_ALL	1024

क्रमागत nexus_रुको_type अणु
	WAIT_HOST = 0,
	WAIT_TARGET,
	WAIT_LUN,
पूर्ण;

/* Refer to SNIA SFF 8247 */
काष्ठा sff_8247_a0 अणु
	u8 txid;	/* transceiver id */
	u8 ext_txid;
	u8 connector;
	/* compliance code */
	u8 eth_infi_cc3;	/* ethernet, inअगरiband */
	u8 sonet_cc4[2];
	u8 eth_cc6;
	/* link length */
#घोषणा FC_LL_VL BIT_7	/* very दीर्घ */
#घोषणा FC_LL_S  BIT_6	/* Short */
#घोषणा FC_LL_I  BIT_5	/* Intermidiate*/
#घोषणा FC_LL_L  BIT_4	/* Long */
#घोषणा FC_LL_M  BIT_3	/* Medium */
#घोषणा FC_LL_SA BIT_2	/* ShortWave laser */
#घोषणा FC_LL_LC BIT_1	/* LongWave laser */
#घोषणा FC_LL_EL BIT_0	/* Electrical पूर्णांकer enclosure */
	u8 fc_ll_cc7;
	/* FC technology */
#घोषणा FC_TEC_EL BIT_7	/* Electrical पूर्णांकer enclosure */
#घोषणा FC_TEC_SN BIT_6	/* लघु wave w/o OFC */
#घोषणा FC_TEC_SL BIT_5	/* लघु wave with OFC */
#घोषणा FC_TEC_LL BIT_4	/* Longwave Laser */
#घोषणा FC_TEC_ACT BIT_3	/* Active cable */
#घोषणा FC_TEC_PAS BIT_2	/* Passive cable */
	u8 fc_tec_cc8;
	/* Transmission Media */
#घोषणा FC_MED_TW BIT_7	/* Twin Ax */
#घोषणा FC_MED_TP BIT_6	/* Twited Pair */
#घोषणा FC_MED_MI BIT_5	/* Min Coax */
#घोषणा FC_MED_TV BIT_4	/* Video Coax */
#घोषणा FC_MED_M6 BIT_3	/* Multimode, 62.5um */
#घोषणा FC_MED_M5 BIT_2	/* Multimode, 50um */
#घोषणा FC_MED_SM BIT_0	/* Single Mode */
	u8 fc_med_cc9;
	/* speed FC_SP_12: 12*100M = 1200 MB/s */
#घोषणा FC_SP_12 BIT_7
#घोषणा FC_SP_8  BIT_6
#घोषणा FC_SP_16 BIT_5
#घोषणा FC_SP_4  BIT_4
#घोषणा FC_SP_32 BIT_3
#घोषणा FC_SP_2  BIT_2
#घोषणा FC_SP_1  BIT_0
	u8 fc_sp_cc10;
	u8 encode;
	u8 bitrate;
	u8 rate_id;
	u8 length_km;		/* offset 14/eh */
	u8 length_100m;
	u8 length_50um_10m;
	u8 length_62um_10m;
	u8 length_om4_10m;
	u8 length_om3_10m;
#घोषणा SFF_VEN_NAME_LEN 16
	u8 venकरोr_name[SFF_VEN_NAME_LEN];	/* offset 20/14h */
	u8 tx_compat;
	u8 venकरोr_oui[3];
#घोषणा SFF_PART_NAME_LEN 16
	u8 venकरोr_pn[SFF_PART_NAME_LEN];	/* part number */
	u8 venकरोr_rev[4];
	u8 wavelength[2];
	u8 resv;
	u8 cc_base;
	u8 options[2];	/* offset 64 */
	u8 br_max;
	u8 br_min;
	u8 venकरोr_sn[16];
	u8 date_code[8];
	u8 diag;
	u8 enh_options;
	u8 sff_revision;
	u8 cc_ext;
	u8 venकरोr_specअगरic[32];
	u8 resv2[128];
पूर्ण;

/* BPM -- Buffer Plus Management support. */
#घोषणा IS_BPM_CAPABLE(ha) \
	(IS_QLA25XX(ha) || IS_QLA81XX(ha) || IS_QLA83XX(ha) || \
	 IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_BPM_RANGE_CAPABLE(ha) \
	(IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
#घोषणा IS_BPM_ENABLED(vha) \
	(ql2xस्वतःdetectsfp && !vha->vp_idx && IS_BPM_CAPABLE(vha->hw))

#घोषणा FLASH_SEMAPHORE_REGISTER_ADDR   0x00101016

#घोषणा USER_CTRL_IRQ(_ha) (ql2xuctrlirq && QLA_TGT_MODE_ENABLED() && \
	(IS_QLA27XX(_ha) || IS_QLA28XX(_ha) || IS_QLA83XX(_ha)))

#घोषणा SAVE_TOPO(_ha) अणु \
	अगर (_ha->current_topology)				\
		_ha->prev_topology = _ha->current_topology;     \
पूर्ण

#घोषणा N2N_TOPO(ha) \
	((ha->prev_topology == ISP_CFG_N && !ha->current_topology) || \
	 ha->current_topology == ISP_CFG_N || \
	 !ha->current_topology)

#घोषणा QLA_N2N_WAIT_TIME	5 /* 2 * ra_tov(n2n) + 1 */

#घोषणा NVME_TYPE(fcport) \
	(fcport->fc4_type & FS_FC4TYPE_NVME) \

#घोषणा FCP_TYPE(fcport) \
	(fcport->fc4_type & FS_FC4TYPE_FCP) \

#घोषणा NVME_ONLY_TARGET(fcport) \
	(NVME_TYPE(fcport) && !FCP_TYPE(fcport))  \

#घोषणा NVME_FCP_TARGET(fcport) \
	(FCP_TYPE(fcport) && NVME_TYPE(fcport)) \

#घोषणा NVME_TARGET(ha, fcport) \
	((NVME_FCP_TARGET(fcport) && \
	(ha->fc4_type_priority == FC4_PRIORITY_NVME)) || \
	NVME_ONLY_TARGET(fcport)) \

#घोषणा PRLI_PHASE(_cls) \
	((_cls == DSC_LS_PRLI_PEND) || (_cls == DSC_LS_PRLI_COMP))

क्रमागत ql_vnd_host_stat_action अणु
	QLA_STOP = 0,
	QLA_START,
	QLA_CLEAR,
पूर्ण;

काष्ठा ql_vnd_mng_host_stats_param अणु
	u32 stat_type;
	क्रमागत ql_vnd_host_stat_action action;
पूर्ण __packed;

काष्ठा ql_vnd_mng_host_stats_resp अणु
	u32 status;
पूर्ण __packed;

काष्ठा ql_vnd_stats_param अणु
	u32 stat_type;
पूर्ण __packed;

काष्ठा ql_vnd_tgt_stats_param अणु
	s32 tgt_id;
	u32 stat_type;
पूर्ण __packed;

क्रमागत ql_vnd_host_port_action अणु
	QLA_ENABLE = 0,
	QLA_DISABLE,
पूर्ण;

काष्ठा ql_vnd_mng_host_port_param अणु
	क्रमागत ql_vnd_host_port_action action;
पूर्ण __packed;

काष्ठा ql_vnd_mng_host_port_resp अणु
	u32 status;
पूर्ण __packed;

काष्ठा ql_vnd_stat_entry अणु
	u32 stat_type;	/* Failure type */
	u32 tgt_num;	/* Target Num */
	u64 cnt;	/* Counter value */
पूर्ण __packed;

काष्ठा ql_vnd_stats अणु
	u64 entry_count; /* Num of entries */
	u64 rservd;
	काष्ठा ql_vnd_stat_entry entry[0]; /* Place holder of entries */
पूर्ण __packed;

काष्ठा ql_vnd_host_stats_resp अणु
	u32 status;
	काष्ठा ql_vnd_stats stats;
पूर्ण __packed;

काष्ठा ql_vnd_tgt_stats_resp अणु
	u32 status;
	काष्ठा ql_vnd_stats stats;
पूर्ण __packed;

#समावेश "qla_target.h"
#समावेश "qla_gbl.h"
#समावेश "qla_dbg.h"
#समावेश "qla_inline.h"
#पूर्ण_अगर
