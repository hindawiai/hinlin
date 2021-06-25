<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SuperTrak EX Series Storage Controller driver क्रम Linux
 *
 *	Copyright (C) 2005-2015 Promise Technology Inc.
 *
 *	Written By:
 *		Ed Lin <promise_linux@promise.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_eh.h>

#घोषणा DRV_NAME "stex"
#घोषणा ST_DRIVER_VERSION	"6.02.0000.01"
#घोषणा ST_VER_MAJOR		6
#घोषणा ST_VER_MINOR		02
#घोषणा ST_OEM				0000
#घोषणा ST_BUILD_VER		01

क्रमागत अणु
	/* MU रेजिस्टर offset */
	IMR0	= 0x10,	/* MU_INBOUND_MESSAGE_REG0 */
	IMR1	= 0x14,	/* MU_INBOUND_MESSAGE_REG1 */
	OMR0	= 0x18,	/* MU_OUTBOUND_MESSAGE_REG0 */
	OMR1	= 0x1c,	/* MU_OUTBOUND_MESSAGE_REG1 */
	IDBL	= 0x20,	/* MU_INBOUND_DOORBELL */
	IIS	= 0x24,	/* MU_INBOUND_INTERRUPT_STATUS */
	IIM	= 0x28,	/* MU_INBOUND_INTERRUPT_MASK */
	ODBL	= 0x2c,	/* MU_OUTBOUND_DOORBELL */
	OIS	= 0x30,	/* MU_OUTBOUND_INTERRUPT_STATUS */
	OIM	= 0x3c,	/* MU_OUTBOUND_INTERRUPT_MASK */

	YIOA_STATUS				= 0x00,
	YH2I_INT				= 0x20,
	YINT_EN					= 0x34,
	YI2H_INT				= 0x9c,
	YI2H_INT_C				= 0xa0,
	YH2I_REQ				= 0xc0,
	YH2I_REQ_HI				= 0xc4,
	PSCRATCH0				= 0xb0,
	PSCRATCH1				= 0xb4,
	PSCRATCH2				= 0xb8,
	PSCRATCH3				= 0xbc,
	PSCRATCH4				= 0xc8,
	MAILBOX_BASE			= 0x1000,
	MAILBOX_HNDSHK_STS		= 0x0,

	/* MU रेजिस्टर value */
	MU_INBOUND_DOORBELL_HANDSHAKE		= (1 << 0),
	MU_INBOUND_DOORBELL_REQHEADCHANGED	= (1 << 1),
	MU_INBOUND_DOORBELL_STATUSTAILCHANGED	= (1 << 2),
	MU_INBOUND_DOORBELL_HMUSTOPPED		= (1 << 3),
	MU_INBOUND_DOORBELL_RESET		= (1 << 4),

	MU_OUTBOUND_DOORBELL_HANDSHAKE		= (1 << 0),
	MU_OUTBOUND_DOORBELL_REQUESTTAILCHANGED	= (1 << 1),
	MU_OUTBOUND_DOORBELL_STATUSHEADCHANGED	= (1 << 2),
	MU_OUTBOUND_DOORBELL_BUSCHANGE		= (1 << 3),
	MU_OUTBOUND_DOORBELL_HASEVENT		= (1 << 4),
	MU_OUTBOUND_DOORBELL_REQUEST_RESET	= (1 << 27),

	/* MU status code */
	MU_STATE_STARTING			= 1,
	MU_STATE_STARTED			= 2,
	MU_STATE_RESETTING			= 3,
	MU_STATE_FAILED				= 4,
	MU_STATE_STOP				= 5,
	MU_STATE_NOCONNECT			= 6,

	MU_MAX_DELAY				= 50,
	MU_HANDSHAKE_SIGNATURE			= 0x55aaaa55,
	MU_HANDSHAKE_SIGNATURE_HALF		= 0x5a5a0000,
	MU_HARD_RESET_WAIT			= 30000,
	HMU_PARTNER_TYPE			= 2,

	/* firmware वापसed values */
	SRB_STATUS_SUCCESS			= 0x01,
	SRB_STATUS_ERROR			= 0x04,
	SRB_STATUS_BUSY				= 0x05,
	SRB_STATUS_INVALID_REQUEST		= 0x06,
	SRB_STATUS_SELECTION_TIMEOUT		= 0x0A,
	SRB_SEE_SENSE 				= 0x80,

	/* task attribute */
	TASK_ATTRIBUTE_SIMPLE			= 0x0,
	TASK_ATTRIBUTE_HEADOFQUEUE		= 0x1,
	TASK_ATTRIBUTE_ORDERED			= 0x2,
	TASK_ATTRIBUTE_ACA			= 0x4,

	SS_STS_NORMAL				= 0x80000000,
	SS_STS_DONE				= 0x40000000,
	SS_STS_HANDSHAKE			= 0x20000000,

	SS_HEAD_HANDSHAKE			= 0x80,

	SS_H2I_INT_RESET			= 0x100,

	SS_I2H_REQUEST_RESET			= 0x2000,

	SS_MU_OPERATIONAL			= 0x80000000,

	STEX_CDB_LENGTH				= 16,
	STATUS_VAR_LEN				= 128,

	/* sg flags */
	SG_CF_EOT				= 0x80,	/* end of table */
	SG_CF_64B				= 0x40,	/* 64 bit item */
	SG_CF_HOST				= 0x20,	/* sg in host memory */
	MSG_DATA_सूची_ND				= 0,
	MSG_DATA_सूची_IN				= 1,
	MSG_DATA_सूची_OUT			= 2,

	st_shasta				= 0,
	st_vsc					= 1,
	st_yosemite				= 2,
	st_seq					= 3,
	st_yel					= 4,
	st_P3					= 5,

	PASSTHRU_REQ_TYPE			= 0x00000001,
	PASSTHRU_REQ_NO_WAKEUP			= 0x00000100,
	ST_INTERNAL_TIMEOUT			= 180,

	ST_TO_CMD				= 0,
	ST_FROM_CMD				= 1,

	/* venकरोr specअगरic commands of Promise */
	MGT_CMD					= 0xd8,
	SINBAND_MGT_CMD				= 0xd9,
	ARRAY_CMD				= 0xe0,
	CONTROLLER_CMD				= 0xe1,
	DEBUGGING_CMD				= 0xe2,
	PASSTHRU_CMD				= 0xe3,

	PASSTHRU_GET_ADAPTER			= 0x05,
	PASSTHRU_GET_DRVVER			= 0x10,

	CTLR_CONFIG_CMD				= 0x03,
	CTLR_SHUTDOWN				= 0x0d,

	CTLR_POWER_STATE_CHANGE			= 0x0e,
	CTLR_POWER_SAVING			= 0x01,

	PASSTHRU_SIGNATURE			= 0x4e415041,
	MGT_CMD_SIGNATURE			= 0xba,

	INQUIRY_EVPD				= 0x01,

	ST_ADDITIONAL_MEM			= 0x200000,
	ST_ADDITIONAL_MEM_MIN			= 0x80000,
	PMIC_SHUTDOWN				= 0x0D,
	PMIC_REUMSE					= 0x10,
	ST_IGNORED					= -1,
	ST_NOTHANDLED				= 7,
	ST_S3						= 3,
	ST_S4						= 4,
	ST_S5						= 5,
	ST_S6						= 6,
पूर्ण;

काष्ठा st_sgitem अणु
	u8 ctrl;	/* SG_CF_xxx */
	u8 reserved[3];
	__le32 count;
	__le64 addr;
पूर्ण;

काष्ठा st_ss_sgitem अणु
	__le32 addr;
	__le32 addr_hi;
	__le32 count;
पूर्ण;

काष्ठा st_sgtable अणु
	__le16 sg_count;
	__le16 max_sg_count;
	__le32 sz_in_byte;
पूर्ण;

काष्ठा st_msg_header अणु
	__le64 handle;
	u8 flag;
	u8 channel;
	__le16 समयout;
	u32 reserved;
पूर्ण;

काष्ठा handshake_frame अणु
	__le64 rb_phy;		/* request payload queue physical address */
	__le16 req_sz;		/* size of each request payload */
	__le16 req_cnt;		/* count of reqs the buffer can hold */
	__le16 status_sz;	/* size of each status payload */
	__le16 status_cnt;	/* count of status the buffer can hold */
	__le64 hostसमय;	/* seconds from Jan 1, 1970 (GMT) */
	u8 partner_type;	/* who sends this frame */
	u8 reserved0[7];
	__le32 partner_ver_major;
	__le32 partner_ver_minor;
	__le32 partner_ver_oem;
	__le32 partner_ver_build;
	__le32 extra_offset;	/* NEW */
	__le32 extra_size;	/* NEW */
	__le32 scratch_size;
	u32 reserved1;
पूर्ण;

काष्ठा req_msg अणु
	__le16 tag;
	u8 lun;
	u8 target;
	u8 task_attr;
	u8 task_manage;
	u8 data_dir;
	u8 payload_sz;		/* payload size in 4-byte, not used */
	u8 cdb[STEX_CDB_LENGTH];
	u32 variable[];
पूर्ण;

काष्ठा status_msg अणु
	__le16 tag;
	u8 lun;
	u8 target;
	u8 srb_status;
	u8 scsi_status;
	u8 reserved;
	u8 payload_sz;		/* payload size in 4-byte */
	u8 variable[STATUS_VAR_LEN];
पूर्ण;

काष्ठा ver_info अणु
	u32 major;
	u32 minor;
	u32 oem;
	u32 build;
	u32 reserved[2];
पूर्ण;

काष्ठा st_frame अणु
	u32 base[6];
	u32 rom_addr;

	काष्ठा ver_info drv_ver;
	काष्ठा ver_info bios_ver;

	u32 bus;
	u32 slot;
	u32 irq_level;
	u32 irq_vec;
	u32 id;
	u32 subid;

	u32 dimm_size;
	u8 dimm_type;
	u8 reserved[3];

	u32 channel;
	u32 reserved1;
पूर्ण;

काष्ठा st_drvver अणु
	u32 major;
	u32 minor;
	u32 oem;
	u32 build;
	u32 signature[2];
	u8 console_id;
	u8 host_no;
	u8 reserved0[2];
	u32 reserved[3];
पूर्ण;

काष्ठा st_ccb अणु
	काष्ठा req_msg *req;
	काष्ठा scsi_cmnd *cmd;

	व्योम *sense_buffer;
	अचिन्हित पूर्णांक sense_bufflen;
	पूर्णांक sg_count;

	u32 req_type;
	u8 srb_status;
	u8 scsi_status;
	u8 reserved[2];
पूर्ण;

काष्ठा st_hba अणु
	व्योम __iomem *mmio_base;	/* iomapped PCI memory space */
	व्योम *dma_mem;
	dma_addr_t dma_handle;
	माप_प्रकार dma_size;

	काष्ठा Scsi_Host *host;
	काष्ठा pci_dev *pdev;

	काष्ठा req_msg * (*alloc_rq) (काष्ठा st_hba *);
	पूर्णांक (*map_sg)(काष्ठा st_hba *, काष्ठा req_msg *, काष्ठा st_ccb *);
	व्योम (*send) (काष्ठा st_hba *, काष्ठा req_msg *, u16);

	u32 req_head;
	u32 req_tail;
	u32 status_head;
	u32 status_tail;

	काष्ठा status_msg *status_buffer;
	व्योम *copy_buffer; /* temp buffer क्रम driver-handled commands */
	काष्ठा st_ccb *ccb;
	काष्ठा st_ccb *रुको_ccb;
	__le32 *scratch;

	अक्षर work_q_name[20];
	काष्ठा workqueue_काष्ठा *work_q;
	काष्ठा work_काष्ठा reset_work;
	रुको_queue_head_t reset_रुकोq;
	अचिन्हित पूर्णांक mu_status;
	अचिन्हित पूर्णांक cardtype;
	पूर्णांक msi_enabled;
	पूर्णांक out_req_cnt;
	u32 extra_offset;
	u16 rq_count;
	u16 rq_size;
	u16 sts_count;
	u8  supports_pm;
	पूर्णांक msi_lock;
पूर्ण;

काष्ठा st_card_info अणु
	काष्ठा req_msg * (*alloc_rq) (काष्ठा st_hba *);
	पूर्णांक (*map_sg)(काष्ठा st_hba *, काष्ठा req_msg *, काष्ठा st_ccb *);
	व्योम (*send) (काष्ठा st_hba *, काष्ठा req_msg *, u16);
	अचिन्हित पूर्णांक max_id;
	अचिन्हित पूर्णांक max_lun;
	अचिन्हित पूर्णांक max_channel;
	u16 rq_count;
	u16 rq_size;
	u16 sts_count;
पूर्ण;

अटल पूर्णांक S6flag;
अटल पूर्णांक stex_halt(काष्ठा notअगरier_block *nb, uदीर्घ event, व्योम *buf);
अटल काष्ठा notअगरier_block stex_notअगरier = अणु
	stex_halt, शून्य, 0
पूर्ण;

अटल पूर्णांक msi;
module_param(msi, पूर्णांक, 0);
MODULE_PARM_DESC(msi, "Enable Message Signaled Interrupts(0=off, 1=on)");

अटल स्थिर अक्षर console_inq_page[] =
अणु
	0x03,0x00,0x03,0x03,0xFA,0x00,0x00,0x30,
	0x50,0x72,0x6F,0x6D,0x69,0x73,0x65,0x20,	/* "Promise " */
	0x52,0x41,0x49,0x44,0x20,0x43,0x6F,0x6E,	/* "RAID Con" */
	0x73,0x6F,0x6C,0x65,0x20,0x20,0x20,0x20,	/* "sole    " */
	0x31,0x2E,0x30,0x30,0x20,0x20,0x20,0x20,	/* "1.00    " */
	0x53,0x58,0x2F,0x52,0x53,0x41,0x46,0x2D,	/* "SX/RSAF-" */
	0x54,0x45,0x31,0x2E,0x30,0x30,0x20,0x20,	/* "TE1.00  " */
	0x0C,0x20,0x20,0x20,0x20,0x20,0x20,0x20
पूर्ण;

MODULE_AUTHOR("Ed Lin");
MODULE_DESCRIPTION("Promise Technology SuperTrak EX Controllers");
MODULE_LICENSE("GPL");
MODULE_VERSION(ST_DRIVER_VERSION);

अटल काष्ठा status_msg *stex_get_status(काष्ठा st_hba *hba)
अणु
	काष्ठा status_msg *status = hba->status_buffer + hba->status_tail;

	++hba->status_tail;
	hba->status_tail %= hba->sts_count+1;

	वापस status;
पूर्ण

अटल व्योम stex_invalid_field(काष्ठा scsi_cmnd *cmd,
			       व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	/* "Invalid field in cdb" */
	scsi_build_sense_buffer(0, cmd->sense_buffer, ILLEGAL_REQUEST, 0x24,
				0x0);
	करोne(cmd);
पूर्ण

अटल काष्ठा req_msg *stex_alloc_req(काष्ठा st_hba *hba)
अणु
	काष्ठा req_msg *req = hba->dma_mem + hba->req_head * hba->rq_size;

	++hba->req_head;
	hba->req_head %= hba->rq_count+1;

	वापस req;
पूर्ण

अटल काष्ठा req_msg *stex_ss_alloc_req(काष्ठा st_hba *hba)
अणु
	वापस (काष्ठा req_msg *)(hba->dma_mem +
		hba->req_head * hba->rq_size + माप(काष्ठा st_msg_header));
पूर्ण

अटल पूर्णांक stex_map_sg(काष्ठा st_hba *hba,
	काष्ठा req_msg *req, काष्ठा st_ccb *ccb)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा scatterlist *sg;
	काष्ठा st_sgtable *dst;
	काष्ठा st_sgitem *table;
	पूर्णांक i, nseg;

	cmd = ccb->cmd;
	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);
	अगर (nseg) अणु
		dst = (काष्ठा st_sgtable *)req->variable;

		ccb->sg_count = nseg;
		dst->sg_count = cpu_to_le16((u16)nseg);
		dst->max_sg_count = cpu_to_le16(hba->host->sg_tablesize);
		dst->sz_in_byte = cpu_to_le32(scsi_bufflen(cmd));

		table = (काष्ठा st_sgitem *)(dst + 1);
		scsi_क्रम_each_sg(cmd, sg, nseg, i) अणु
			table[i].count = cpu_to_le32((u32)sg_dma_len(sg));
			table[i].addr = cpu_to_le64(sg_dma_address(sg));
			table[i].ctrl = SG_CF_64B | SG_CF_HOST;
		पूर्ण
		table[--i].ctrl |= SG_CF_EOT;
	पूर्ण

	वापस nseg;
पूर्ण

अटल पूर्णांक stex_ss_map_sg(काष्ठा st_hba *hba,
	काष्ठा req_msg *req, काष्ठा st_ccb *ccb)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा scatterlist *sg;
	काष्ठा st_sgtable *dst;
	काष्ठा st_ss_sgitem *table;
	पूर्णांक i, nseg;

	cmd = ccb->cmd;
	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);
	अगर (nseg) अणु
		dst = (काष्ठा st_sgtable *)req->variable;

		ccb->sg_count = nseg;
		dst->sg_count = cpu_to_le16((u16)nseg);
		dst->max_sg_count = cpu_to_le16(hba->host->sg_tablesize);
		dst->sz_in_byte = cpu_to_le32(scsi_bufflen(cmd));

		table = (काष्ठा st_ss_sgitem *)(dst + 1);
		scsi_क्रम_each_sg(cmd, sg, nseg, i) अणु
			table[i].count = cpu_to_le32((u32)sg_dma_len(sg));
			table[i].addr =
				cpu_to_le32(sg_dma_address(sg) & 0xffffffff);
			table[i].addr_hi =
				cpu_to_le32((sg_dma_address(sg) >> 16) >> 16);
		पूर्ण
	पूर्ण

	वापस nseg;
पूर्ण

अटल व्योम stex_controller_info(काष्ठा st_hba *hba, काष्ठा st_ccb *ccb)
अणु
	काष्ठा st_frame *p;
	माप_प्रकार count = माप(काष्ठा st_frame);

	p = hba->copy_buffer;
	scsi_sg_copy_to_buffer(ccb->cmd, p, count);
	स_रखो(p->base, 0, माप(u32)*6);
	*(अचिन्हित दीर्घ *)(p->base) = pci_resource_start(hba->pdev, 0);
	p->rom_addr = 0;

	p->drv_ver.major = ST_VER_MAJOR;
	p->drv_ver.minor = ST_VER_MINOR;
	p->drv_ver.oem = ST_OEM;
	p->drv_ver.build = ST_BUILD_VER;

	p->bus = hba->pdev->bus->number;
	p->slot = hba->pdev->devfn;
	p->irq_level = 0;
	p->irq_vec = hba->pdev->irq;
	p->id = hba->pdev->venकरोr << 16 | hba->pdev->device;
	p->subid =
		hba->pdev->subप्रणाली_venकरोr << 16 | hba->pdev->subप्रणाली_device;

	scsi_sg_copy_from_buffer(ccb->cmd, p, count);
पूर्ण

अटल व्योम
stex_send_cmd(काष्ठा st_hba *hba, काष्ठा req_msg *req, u16 tag)
अणु
	req->tag = cpu_to_le16(tag);

	hba->ccb[tag].req = req;
	hba->out_req_cnt++;

	ग_लिखोl(hba->req_head, hba->mmio_base + IMR0);
	ग_लिखोl(MU_INBOUND_DOORBELL_REQHEADCHANGED, hba->mmio_base + IDBL);
	पढ़ोl(hba->mmio_base + IDBL); /* flush */
पूर्ण

अटल व्योम
stex_ss_send_cmd(काष्ठा st_hba *hba, काष्ठा req_msg *req, u16 tag)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा st_msg_header *msg_h;
	dma_addr_t addr;

	req->tag = cpu_to_le16(tag);

	hba->ccb[tag].req = req;
	hba->out_req_cnt++;

	cmd = hba->ccb[tag].cmd;
	msg_h = (काष्ठा st_msg_header *)req - 1;
	अगर (likely(cmd)) अणु
		msg_h->channel = (u8)cmd->device->channel;
		msg_h->समयout = cpu_to_le16(cmd->request->समयout/HZ);
	पूर्ण
	addr = hba->dma_handle + hba->req_head * hba->rq_size;
	addr += (hba->ccb[tag].sg_count+4)/11;
	msg_h->handle = cpu_to_le64(addr);

	++hba->req_head;
	hba->req_head %= hba->rq_count+1;
	अगर (hba->cardtype == st_P3) अणु
		ग_लिखोl((addr >> 16) >> 16, hba->mmio_base + YH2I_REQ_HI);
		ग_लिखोl(addr, hba->mmio_base + YH2I_REQ);
	पूर्ण अन्यथा अणु
		ग_लिखोl((addr >> 16) >> 16, hba->mmio_base + YH2I_REQ_HI);
		पढ़ोl(hba->mmio_base + YH2I_REQ_HI); /* flush */
		ग_लिखोl(addr, hba->mmio_base + YH2I_REQ);
		पढ़ोl(hba->mmio_base + YH2I_REQ); /* flush */
	पूर्ण
पूर्ण

अटल व्योम वापस_abnormal_state(काष्ठा st_hba *hba, पूर्णांक status)
अणु
	काष्ठा st_ccb *ccb;
	अचिन्हित दीर्घ flags;
	u16 tag;

	spin_lock_irqsave(hba->host->host_lock, flags);
	क्रम (tag = 0; tag < hba->host->can_queue; tag++) अणु
		ccb = &hba->ccb[tag];
		अगर (ccb->req == शून्य)
			जारी;
		ccb->req = शून्य;
		अगर (ccb->cmd) अणु
			scsi_dma_unmap(ccb->cmd);
			ccb->cmd->result = status << 16;
			ccb->cmd->scsi_करोne(ccb->cmd);
			ccb->cmd = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);
पूर्ण
अटल पूर्णांक
stex_slave_config(काष्ठा scsi_device *sdev)
अणु
	sdev->use_10_क्रम_rw = 1;
	sdev->use_10_क्रम_ms = 1;
	blk_queue_rq_समयout(sdev->request_queue, 60 * HZ);

	वापस 0;
पूर्ण

अटल पूर्णांक
stex_queuecommand_lck(काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा st_hba *hba;
	काष्ठा Scsi_Host *host;
	अचिन्हित पूर्णांक id, lun;
	काष्ठा req_msg *req;
	u16 tag;

	host = cmd->device->host;
	id = cmd->device->id;
	lun = cmd->device->lun;
	hba = (काष्ठा st_hba *) &host->hostdata[0];
	अगर (hba->mu_status == MU_STATE_NOCONNECT) अणु
		cmd->result = DID_NO_CONNECT;
		करोne(cmd);
		वापस 0;
	पूर्ण
	अगर (unlikely(hba->mu_status != MU_STATE_STARTED))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	चयन (cmd->cmnd[0]) अणु
	हाल MODE_SENSE_10:
	अणु
		अटल अक्षर ms10_caching_page[12] =
			अणु 0, 0x12, 0, 0, 0, 0, 0, 0, 0x8, 0xa, 0x4, 0 पूर्ण;
		अचिन्हित अक्षर page;

		page = cmd->cmnd[2] & 0x3f;
		अगर (page == 0x8 || page == 0x3f) अणु
			scsi_sg_copy_from_buffer(cmd, ms10_caching_page,
						 माप(ms10_caching_page));
			cmd->result = DID_OK << 16;
			करोne(cmd);
		पूर्ण अन्यथा
			stex_invalid_field(cmd, करोne);
		वापस 0;
	पूर्ण
	हाल REPORT_LUNS:
		/*
		 * The shasta firmware करोes not report actual luns in the
		 * target, so fail the command to क्रमce sequential lun scan.
		 * Also, the console device करोes not support this command.
		 */
		अगर (hba->cardtype == st_shasta || id == host->max_id - 1) अणु
			stex_invalid_field(cmd, करोne);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल TEST_UNIT_READY:
		अगर (id == host->max_id - 1) अणु
			cmd->result = DID_OK << 16;
			करोne(cmd);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल INQUIRY:
		अगर (lun >= host->max_lun) अणु
			cmd->result = DID_NO_CONNECT << 16;
			करोne(cmd);
			वापस 0;
		पूर्ण
		अगर (id != host->max_id - 1)
			अवरोध;
		अगर (!lun && !cmd->device->channel &&
			(cmd->cmnd[1] & INQUIRY_EVPD) == 0) अणु
			scsi_sg_copy_from_buffer(cmd, (व्योम *)console_inq_page,
						 माप(console_inq_page));
			cmd->result = DID_OK << 16;
			करोne(cmd);
		पूर्ण अन्यथा
			stex_invalid_field(cmd, करोne);
		वापस 0;
	हाल PASSTHRU_CMD:
		अगर (cmd->cmnd[1] == PASSTHRU_GET_DRVVER) अणु
			काष्ठा st_drvver ver;
			माप_प्रकार cp_len = माप(ver);

			ver.major = ST_VER_MAJOR;
			ver.minor = ST_VER_MINOR;
			ver.oem = ST_OEM;
			ver.build = ST_BUILD_VER;
			ver.signature[0] = PASSTHRU_SIGNATURE;
			ver.console_id = host->max_id - 1;
			ver.host_no = hba->host->host_no;
			cp_len = scsi_sg_copy_from_buffer(cmd, &ver, cp_len);
			अगर (माप(ver) == cp_len)
				cmd->result = DID_OK << 16;
			अन्यथा
				cmd->result = DID_ERROR << 16;
			करोne(cmd);
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	cmd->scsi_करोne = करोne;

	tag = cmd->request->tag;

	अगर (unlikely(tag >= host->can_queue))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	req = hba->alloc_rq(hba);

	req->lun = lun;
	req->target = id;

	/* cdb */
	स_नकल(req->cdb, cmd->cmnd, STEX_CDB_LENGTH);

	अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
		req->data_dir = MSG_DATA_सूची_IN;
	अन्यथा अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
		req->data_dir = MSG_DATA_सूची_OUT;
	अन्यथा
		req->data_dir = MSG_DATA_सूची_ND;

	hba->ccb[tag].cmd = cmd;
	hba->ccb[tag].sense_bufflen = SCSI_SENSE_BUFFERSIZE;
	hba->ccb[tag].sense_buffer = cmd->sense_buffer;

	अगर (!hba->map_sg(hba, req, &hba->ccb[tag])) अणु
		hba->ccb[tag].sg_count = 0;
		स_रखो(&req->variable[0], 0, 8);
	पूर्ण

	hba->send(hba, req, tag);
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(stex_queuecommand)

अटल व्योम stex_scsi_करोne(काष्ठा st_ccb *ccb)
अणु
	काष्ठा scsi_cmnd *cmd = ccb->cmd;
	पूर्णांक result;

	अगर (ccb->srb_status == SRB_STATUS_SUCCESS || ccb->srb_status == 0) अणु
		result = ccb->scsi_status;
		चयन (ccb->scsi_status) अणु
		हाल SAM_STAT_GOOD:
			result |= DID_OK << 16;
			अवरोध;
		हाल SAM_STAT_CHECK_CONDITION:
			result |= DRIVER_SENSE << 24;
			अवरोध;
		हाल SAM_STAT_BUSY:
			result |= DID_BUS_BUSY << 16;
			अवरोध;
		शेष:
			result |= DID_ERROR << 16;
			अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा अगर (ccb->srb_status & SRB_SEE_SENSE)
		result = DRIVER_SENSE << 24 | SAM_STAT_CHECK_CONDITION;
	अन्यथा चयन (ccb->srb_status) अणु
		हाल SRB_STATUS_SELECTION_TIMEOUT:
			result = DID_NO_CONNECT << 16;
			अवरोध;
		हाल SRB_STATUS_BUSY:
			result = DID_BUS_BUSY << 16;
			अवरोध;
		हाल SRB_STATUS_INVALID_REQUEST:
		हाल SRB_STATUS_ERROR:
		शेष:
			result = DID_ERROR << 16;
			अवरोध;
	पूर्ण

	cmd->result = result;
	cmd->scsi_करोne(cmd);
पूर्ण

अटल व्योम stex_copy_data(काष्ठा st_ccb *ccb,
	काष्ठा status_msg *resp, अचिन्हित पूर्णांक variable)
अणु
	अगर (resp->scsi_status != SAM_STAT_GOOD) अणु
		अगर (ccb->sense_buffer != शून्य)
			स_नकल(ccb->sense_buffer, resp->variable,
				min(variable, ccb->sense_bufflen));
		वापस;
	पूर्ण

	अगर (ccb->cmd == शून्य)
		वापस;
	scsi_sg_copy_from_buffer(ccb->cmd, resp->variable, variable);
पूर्ण

अटल व्योम stex_check_cmd(काष्ठा st_hba *hba,
	काष्ठा st_ccb *ccb, काष्ठा status_msg *resp)
अणु
	अगर (ccb->cmd->cmnd[0] == MGT_CMD &&
		resp->scsi_status != SAM_STAT_CHECK_CONDITION)
		scsi_set_resid(ccb->cmd, scsi_bufflen(ccb->cmd) -
			le32_to_cpu(*(__le32 *)&resp->variable[0]));
पूर्ण

अटल व्योम stex_mu_पूर्णांकr(काष्ठा st_hba *hba, u32 करोorbell)
अणु
	व्योम __iomem *base = hba->mmio_base;
	काष्ठा status_msg *resp;
	काष्ठा st_ccb *ccb;
	अचिन्हित पूर्णांक size;
	u16 tag;

	अगर (unlikely(!(करोorbell & MU_OUTBOUND_DOORBELL_STATUSHEADCHANGED)))
		वापस;

	/* status payloads */
	hba->status_head = पढ़ोl(base + OMR1);
	अगर (unlikely(hba->status_head > hba->sts_count)) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME "(%s): invalid status head\n",
			pci_name(hba->pdev));
		वापस;
	पूर्ण

	/*
	 * it's not a valid status payload अगर:
	 * 1. there are no pending requests(e.g. during init stage)
	 * 2. there are some pending requests, but the controller is in
	 *     reset status, and its type is not st_yosemite
	 * firmware of st_yosemite in reset status will वापस pending requests
	 * to driver, so we allow it to pass
	 */
	अगर (unlikely(hba->out_req_cnt <= 0 ||
			(hba->mu_status == MU_STATE_RESETTING &&
			 hba->cardtype != st_yosemite))) अणु
		hba->status_tail = hba->status_head;
		जाओ update_status;
	पूर्ण

	जबतक (hba->status_tail != hba->status_head) अणु
		resp = stex_get_status(hba);
		tag = le16_to_cpu(resp->tag);
		अगर (unlikely(tag >= hba->host->can_queue)) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
				"(%s): invalid tag\n", pci_name(hba->pdev));
			जारी;
		पूर्ण

		hba->out_req_cnt--;
		ccb = &hba->ccb[tag];
		अगर (unlikely(hba->रुको_ccb == ccb))
			hba->रुको_ccb = शून्य;
		अगर (unlikely(ccb->req == शून्य)) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
				"(%s): lagging req\n", pci_name(hba->pdev));
			जारी;
		पूर्ण

		size = resp->payload_sz * माप(u32); /* payload size */
		अगर (unlikely(size < माप(*resp) - STATUS_VAR_LEN ||
			size > माप(*resp))) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME "(%s): bad status size\n",
				pci_name(hba->pdev));
		पूर्ण अन्यथा अणु
			size -= माप(*resp) - STATUS_VAR_LEN; /* copy size */
			अगर (size)
				stex_copy_data(ccb, resp, size);
		पूर्ण

		ccb->req = शून्य;
		ccb->srb_status = resp->srb_status;
		ccb->scsi_status = resp->scsi_status;

		अगर (likely(ccb->cmd != शून्य)) अणु
			अगर (hba->cardtype == st_yosemite)
				stex_check_cmd(hba, ccb, resp);

			अगर (unlikely(ccb->cmd->cmnd[0] == PASSTHRU_CMD &&
				ccb->cmd->cmnd[1] == PASSTHRU_GET_ADAPTER))
				stex_controller_info(hba, ccb);

			scsi_dma_unmap(ccb->cmd);
			stex_scsi_करोne(ccb);
		पूर्ण अन्यथा
			ccb->req_type = 0;
	पूर्ण

update_status:
	ग_लिखोl(hba->status_head, base + IMR1);
	पढ़ोl(base + IMR1); /* flush */
पूर्ण

अटल irqवापस_t stex_पूर्णांकr(पूर्णांक irq, व्योम *__hba)
अणु
	काष्ठा st_hba *hba = __hba;
	व्योम __iomem *base = hba->mmio_base;
	u32 data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hba->host->host_lock, flags);

	data = पढ़ोl(base + ODBL);

	अगर (data && data != 0xffffffff) अणु
		/* clear the पूर्णांकerrupt */
		ग_लिखोl(data, base + ODBL);
		पढ़ोl(base + ODBL); /* flush */
		stex_mu_पूर्णांकr(hba, data);
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		अगर (unlikely(data & MU_OUTBOUND_DOORBELL_REQUEST_RESET &&
			hba->cardtype == st_shasta))
			queue_work(hba->work_q, &hba->reset_work);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(hba->host->host_lock, flags);

	वापस IRQ_NONE;
पूर्ण

अटल व्योम stex_ss_mu_पूर्णांकr(काष्ठा st_hba *hba)
अणु
	काष्ठा status_msg *resp;
	काष्ठा st_ccb *ccb;
	__le32 *scratch;
	अचिन्हित पूर्णांक size;
	पूर्णांक count = 0;
	u32 value;
	u16 tag;

	अगर (unlikely(hba->out_req_cnt <= 0 ||
			hba->mu_status == MU_STATE_RESETTING))
		वापस;

	जबतक (count < hba->sts_count) अणु
		scratch = hba->scratch + hba->status_tail;
		value = le32_to_cpu(*scratch);
		अगर (unlikely(!(value & SS_STS_NORMAL)))
			वापस;

		resp = hba->status_buffer + hba->status_tail;
		*scratch = 0;
		++count;
		++hba->status_tail;
		hba->status_tail %= hba->sts_count+1;

		tag = (u16)value;
		अगर (unlikely(tag >= hba->host->can_queue)) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
				"(%s): invalid tag\n", pci_name(hba->pdev));
			जारी;
		पूर्ण

		hba->out_req_cnt--;
		ccb = &hba->ccb[tag];
		अगर (unlikely(hba->रुको_ccb == ccb))
			hba->रुको_ccb = शून्य;
		अगर (unlikely(ccb->req == शून्य)) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
				"(%s): lagging req\n", pci_name(hba->pdev));
			जारी;
		पूर्ण

		ccb->req = शून्य;
		अगर (likely(value & SS_STS_DONE)) अणु /* normal हाल */
			ccb->srb_status = SRB_STATUS_SUCCESS;
			ccb->scsi_status = SAM_STAT_GOOD;
		पूर्ण अन्यथा अणु
			ccb->srb_status = resp->srb_status;
			ccb->scsi_status = resp->scsi_status;
			size = resp->payload_sz * माप(u32);
			अगर (unlikely(size < माप(*resp) - STATUS_VAR_LEN ||
				size > माप(*resp))) अणु
				prपूर्णांकk(KERN_WARNING DRV_NAME
					"(%s): bad status size\n",
					pci_name(hba->pdev));
			पूर्ण अन्यथा अणु
				size -= माप(*resp) - STATUS_VAR_LEN;
				अगर (size)
					stex_copy_data(ccb, resp, size);
			पूर्ण
			अगर (likely(ccb->cmd != शून्य))
				stex_check_cmd(hba, ccb, resp);
		पूर्ण

		अगर (likely(ccb->cmd != शून्य)) अणु
			scsi_dma_unmap(ccb->cmd);
			stex_scsi_करोne(ccb);
		पूर्ण अन्यथा
			ccb->req_type = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t stex_ss_पूर्णांकr(पूर्णांक irq, व्योम *__hba)
अणु
	काष्ठा st_hba *hba = __hba;
	व्योम __iomem *base = hba->mmio_base;
	u32 data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hba->host->host_lock, flags);

	अगर (hba->cardtype == st_yel) अणु
		data = पढ़ोl(base + YI2H_INT);
		अगर (data && data != 0xffffffff) अणु
			/* clear the पूर्णांकerrupt */
			ग_लिखोl(data, base + YI2H_INT_C);
			stex_ss_mu_पूर्णांकr(hba);
			spin_unlock_irqrestore(hba->host->host_lock, flags);
			अगर (unlikely(data & SS_I2H_REQUEST_RESET))
				queue_work(hba->work_q, &hba->reset_work);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण अन्यथा अणु
		data = पढ़ोl(base + PSCRATCH4);
		अगर (data != 0xffffffff) अणु
			अगर (data != 0) अणु
				/* clear the पूर्णांकerrupt */
				ग_लिखोl(data, base + PSCRATCH1);
				ग_लिखोl((1 << 22), base + YH2I_INT);
			पूर्ण
			stex_ss_mu_पूर्णांकr(hba);
			spin_unlock_irqrestore(hba->host->host_lock, flags);
			अगर (unlikely(data & SS_I2H_REQUEST_RESET))
				queue_work(hba->work_q, &hba->reset_work);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(hba->host->host_lock, flags);

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक stex_common_handshake(काष्ठा st_hba *hba)
अणु
	व्योम __iomem *base = hba->mmio_base;
	काष्ठा handshake_frame *h;
	dma_addr_t status_phys;
	u32 data;
	अचिन्हित दीर्घ beक्रमe;

	अगर (पढ़ोl(base + OMR0) != MU_HANDSHAKE_SIGNATURE) अणु
		ग_लिखोl(MU_INBOUND_DOORBELL_HANDSHAKE, base + IDBL);
		पढ़ोl(base + IDBL);
		beक्रमe = jअगरfies;
		जबतक (पढ़ोl(base + OMR0) != MU_HANDSHAKE_SIGNATURE) अणु
			अगर (समय_after(jअगरfies, beक्रमe + MU_MAX_DELAY * HZ)) अणु
				prपूर्णांकk(KERN_ERR DRV_NAME
					"(%s): no handshake signature\n",
					pci_name(hba->pdev));
				वापस -1;
			पूर्ण
			rmb();
			msleep(1);
		पूर्ण
	पूर्ण

	udelay(10);

	data = पढ़ोl(base + OMR1);
	अगर ((data & 0xffff0000) == MU_HANDSHAKE_SIGNATURE_HALF) अणु
		data &= 0x0000ffff;
		अगर (hba->host->can_queue > data) अणु
			hba->host->can_queue = data;
			hba->host->cmd_per_lun = data;
		पूर्ण
	पूर्ण

	h = (काष्ठा handshake_frame *)hba->status_buffer;
	h->rb_phy = cpu_to_le64(hba->dma_handle);
	h->req_sz = cpu_to_le16(hba->rq_size);
	h->req_cnt = cpu_to_le16(hba->rq_count+1);
	h->status_sz = cpu_to_le16(माप(काष्ठा status_msg));
	h->status_cnt = cpu_to_le16(hba->sts_count+1);
	h->hostसमय = cpu_to_le64(kसमय_get_real_seconds());
	h->partner_type = HMU_PARTNER_TYPE;
	अगर (hba->extra_offset) अणु
		h->extra_offset = cpu_to_le32(hba->extra_offset);
		h->extra_size = cpu_to_le32(hba->dma_size - hba->extra_offset);
	पूर्ण अन्यथा
		h->extra_offset = h->extra_size = 0;

	status_phys = hba->dma_handle + (hba->rq_count+1) * hba->rq_size;
	ग_लिखोl(status_phys, base + IMR0);
	पढ़ोl(base + IMR0);
	ग_लिखोl((status_phys >> 16) >> 16, base + IMR1);
	पढ़ोl(base + IMR1);

	ग_लिखोl((status_phys >> 16) >> 16, base + OMR0); /* old fw compatible */
	पढ़ोl(base + OMR0);
	ग_लिखोl(MU_INBOUND_DOORBELL_HANDSHAKE, base + IDBL);
	पढ़ोl(base + IDBL); /* flush */

	udelay(10);
	beक्रमe = jअगरfies;
	जबतक (पढ़ोl(base + OMR0) != MU_HANDSHAKE_SIGNATURE) अणु
		अगर (समय_after(jअगरfies, beक्रमe + MU_MAX_DELAY * HZ)) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME
				"(%s): no signature after handshake frame\n",
				pci_name(hba->pdev));
			वापस -1;
		पूर्ण
		rmb();
		msleep(1);
	पूर्ण

	ग_लिखोl(0, base + IMR0);
	पढ़ोl(base + IMR0);
	ग_लिखोl(0, base + OMR0);
	पढ़ोl(base + OMR0);
	ग_लिखोl(0, base + IMR1);
	पढ़ोl(base + IMR1);
	ग_लिखोl(0, base + OMR1);
	पढ़ोl(base + OMR1); /* flush */
	वापस 0;
पूर्ण

अटल पूर्णांक stex_ss_handshake(काष्ठा st_hba *hba)
अणु
	व्योम __iomem *base = hba->mmio_base;
	काष्ठा st_msg_header *msg_h;
	काष्ठा handshake_frame *h;
	__le32 *scratch;
	u32 data, scratch_size, mailboxdata, operationaldata;
	अचिन्हित दीर्घ beक्रमe;
	पूर्णांक ret = 0;

	beक्रमe = jअगरfies;

	अगर (hba->cardtype == st_yel) अणु
		operationaldata = पढ़ोl(base + YIOA_STATUS);
		जबतक (operationaldata != SS_MU_OPERATIONAL) अणु
			अगर (समय_after(jअगरfies, beक्रमe + MU_MAX_DELAY * HZ)) अणु
				prपूर्णांकk(KERN_ERR DRV_NAME
					"(%s): firmware not operational\n",
					pci_name(hba->pdev));
				वापस -1;
			पूर्ण
			msleep(1);
			operationaldata = पढ़ोl(base + YIOA_STATUS);
		पूर्ण
	पूर्ण अन्यथा अणु
		operationaldata = पढ़ोl(base + PSCRATCH3);
		जबतक (operationaldata != SS_MU_OPERATIONAL) अणु
			अगर (समय_after(jअगरfies, beक्रमe + MU_MAX_DELAY * HZ)) अणु
				prपूर्णांकk(KERN_ERR DRV_NAME
					"(%s): firmware not operational\n",
					pci_name(hba->pdev));
				वापस -1;
			पूर्ण
			msleep(1);
			operationaldata = पढ़ोl(base + PSCRATCH3);
		पूर्ण
	पूर्ण

	msg_h = (काष्ठा st_msg_header *)hba->dma_mem;
	msg_h->handle = cpu_to_le64(hba->dma_handle);
	msg_h->flag = SS_HEAD_HANDSHAKE;

	h = (काष्ठा handshake_frame *)(msg_h + 1);
	h->rb_phy = cpu_to_le64(hba->dma_handle);
	h->req_sz = cpu_to_le16(hba->rq_size);
	h->req_cnt = cpu_to_le16(hba->rq_count+1);
	h->status_sz = cpu_to_le16(माप(काष्ठा status_msg));
	h->status_cnt = cpu_to_le16(hba->sts_count+1);
	h->hostसमय = cpu_to_le64(kसमय_get_real_seconds());
	h->partner_type = HMU_PARTNER_TYPE;
	h->extra_offset = h->extra_size = 0;
	scratch_size = (hba->sts_count+1)*माप(u32);
	h->scratch_size = cpu_to_le32(scratch_size);

	अगर (hba->cardtype == st_yel) अणु
		data = पढ़ोl(base + YINT_EN);
		data &= ~4;
		ग_लिखोl(data, base + YINT_EN);
		ग_लिखोl((hba->dma_handle >> 16) >> 16, base + YH2I_REQ_HI);
		पढ़ोl(base + YH2I_REQ_HI);
		ग_लिखोl(hba->dma_handle, base + YH2I_REQ);
		पढ़ोl(base + YH2I_REQ); /* flush */
	पूर्ण अन्यथा अणु
		data = पढ़ोl(base + YINT_EN);
		data &= ~(1 << 0);
		data &= ~(1 << 2);
		ग_लिखोl(data, base + YINT_EN);
		अगर (hba->msi_lock == 0) अणु
			/* P3 MSI Register cannot access twice */
			ग_लिखोl((1 << 6), base + YH2I_INT);
			hba->msi_lock  = 1;
		पूर्ण
		ग_लिखोl((hba->dma_handle >> 16) >> 16, base + YH2I_REQ_HI);
		ग_लिखोl(hba->dma_handle, base + YH2I_REQ);
	पूर्ण

	beक्रमe = jअगरfies;
	scratch = hba->scratch;
	अगर (hba->cardtype == st_yel) अणु
		जबतक (!(le32_to_cpu(*scratch) & SS_STS_HANDSHAKE)) अणु
			अगर (समय_after(jअगरfies, beक्रमe + MU_MAX_DELAY * HZ)) अणु
				prपूर्णांकk(KERN_ERR DRV_NAME
					"(%s): no signature after handshake frame\n",
					pci_name(hba->pdev));
				ret = -1;
				अवरोध;
			पूर्ण
			rmb();
			msleep(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		mailboxdata = पढ़ोl(base + MAILBOX_BASE + MAILBOX_HNDSHK_STS);
		जबतक (mailboxdata != SS_STS_HANDSHAKE) अणु
			अगर (समय_after(jअगरfies, beक्रमe + MU_MAX_DELAY * HZ)) अणु
				prपूर्णांकk(KERN_ERR DRV_NAME
					"(%s): no signature after handshake frame\n",
					pci_name(hba->pdev));
				ret = -1;
				अवरोध;
			पूर्ण
			rmb();
			msleep(1);
			mailboxdata = पढ़ोl(base + MAILBOX_BASE + MAILBOX_HNDSHK_STS);
		पूर्ण
	पूर्ण
	स_रखो(scratch, 0, scratch_size);
	msg_h->flag = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक stex_handshake(काष्ठा st_hba *hba)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mu_status;

	अगर (hba->cardtype == st_yel || hba->cardtype == st_P3)
		err = stex_ss_handshake(hba);
	अन्यथा
		err = stex_common_handshake(hba);
	spin_lock_irqsave(hba->host->host_lock, flags);
	mu_status = hba->mu_status;
	अगर (err == 0) अणु
		hba->req_head = 0;
		hba->req_tail = 0;
		hba->status_head = 0;
		hba->status_tail = 0;
		hba->out_req_cnt = 0;
		hba->mu_status = MU_STATE_STARTED;
	पूर्ण अन्यथा
		hba->mu_status = MU_STATE_FAILED;
	अगर (mu_status == MU_STATE_RESETTING)
		wake_up_all(&hba->reset_रुकोq);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक stex_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा st_hba *hba = (काष्ठा st_hba *)host->hostdata;
	u16 tag = cmd->request->tag;
	व्योम __iomem *base;
	u32 data;
	पूर्णांक result = SUCCESS;
	अचिन्हित दीर्घ flags;

	scmd_prपूर्णांकk(KERN_INFO, cmd, "aborting command\n");

	base = hba->mmio_base;
	spin_lock_irqsave(host->host_lock, flags);
	अगर (tag < host->can_queue &&
		hba->ccb[tag].req && hba->ccb[tag].cmd == cmd)
		hba->रुको_ccb = &hba->ccb[tag];
	अन्यथा
		जाओ out;

	अगर (hba->cardtype == st_yel) अणु
		data = पढ़ोl(base + YI2H_INT);
		अगर (data == 0 || data == 0xffffffff)
			जाओ fail_out;

		ग_लिखोl(data, base + YI2H_INT_C);
		stex_ss_mu_पूर्णांकr(hba);
	पूर्ण अन्यथा अगर (hba->cardtype == st_P3) अणु
		data = पढ़ोl(base + PSCRATCH4);
		अगर (data == 0xffffffff)
			जाओ fail_out;
		अगर (data != 0) अणु
			ग_लिखोl(data, base + PSCRATCH1);
			ग_लिखोl((1 << 22), base + YH2I_INT);
		पूर्ण
		stex_ss_mu_पूर्णांकr(hba);
	पूर्ण अन्यथा अणु
		data = पढ़ोl(base + ODBL);
		अगर (data == 0 || data == 0xffffffff)
			जाओ fail_out;

		ग_लिखोl(data, base + ODBL);
		पढ़ोl(base + ODBL); /* flush */
		stex_mu_पूर्णांकr(hba, data);
	पूर्ण
	अगर (hba->रुको_ccb == शून्य) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
			"(%s): lost interrupt\n", pci_name(hba->pdev));
		जाओ out;
	पूर्ण

fail_out:
	scsi_dma_unmap(cmd);
	hba->रुको_ccb->req = शून्य; /* nullअगरy the req's future वापस */
	hba->रुको_ccb = शून्य;
	result = FAILED;
out:
	spin_unlock_irqrestore(host->host_lock, flags);
	वापस result;
पूर्ण

अटल व्योम stex_hard_reset(काष्ठा st_hba *hba)
अणु
	काष्ठा pci_bus *bus;
	पूर्णांक i;
	u16 pci_cmd;
	u8 pci_bctl;

	क्रम (i = 0; i < 16; i++)
		pci_पढ़ो_config_dword(hba->pdev, i * 4,
			&hba->pdev->saved_config_space[i]);

	/* Reset secondary bus. Our controller(MU/ATU) is the only device on
	   secondary bus. Consult Intel 80331/3 developer's manual क्रम detail */
	bus = hba->pdev->bus;
	pci_पढ़ो_config_byte(bus->self, PCI_BRIDGE_CONTROL, &pci_bctl);
	pci_bctl |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_ग_लिखो_config_byte(bus->self, PCI_BRIDGE_CONTROL, pci_bctl);

	/*
	 * 1 ms may be enough क्रम 8-port controllers. But 16-port controllers
	 * require more समय to finish bus reset. Use 100 ms here क्रम safety
	 */
	msleep(100);
	pci_bctl &= ~PCI_BRIDGE_CTL_BUS_RESET;
	pci_ग_लिखो_config_byte(bus->self, PCI_BRIDGE_CONTROL, pci_bctl);

	क्रम (i = 0; i < MU_HARD_RESET_WAIT; i++) अणु
		pci_पढ़ो_config_word(hba->pdev, PCI_COMMAND, &pci_cmd);
		अगर (pci_cmd != 0xffff && (pci_cmd & PCI_COMMAND_MASTER))
			अवरोध;
		msleep(1);
	पूर्ण

	ssleep(5);
	क्रम (i = 0; i < 16; i++)
		pci_ग_लिखो_config_dword(hba->pdev, i * 4,
			hba->pdev->saved_config_space[i]);
पूर्ण

अटल पूर्णांक stex_yos_reset(काष्ठा st_hba *hba)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ flags, beक्रमe;
	पूर्णांक ret = 0;

	base = hba->mmio_base;
	ग_लिखोl(MU_INBOUND_DOORBELL_RESET, base + IDBL);
	पढ़ोl(base + IDBL); /* flush */
	beक्रमe = jअगरfies;
	जबतक (hba->out_req_cnt > 0) अणु
		अगर (समय_after(jअगरfies, beक्रमe + ST_INTERNAL_TIMEOUT * HZ)) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
				"(%s): reset timeout\n", pci_name(hba->pdev));
			ret = -1;
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (ret == -1)
		hba->mu_status = MU_STATE_FAILED;
	अन्यथा
		hba->mu_status = MU_STATE_STARTED;
	wake_up_all(&hba->reset_रुकोq);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम stex_ss_reset(काष्ठा st_hba *hba)
अणु
	ग_लिखोl(SS_H2I_INT_RESET, hba->mmio_base + YH2I_INT);
	पढ़ोl(hba->mmio_base + YH2I_INT);
	ssleep(5);
पूर्ण

अटल व्योम stex_p3_reset(काष्ठा st_hba *hba)
अणु
	ग_लिखोl(SS_H2I_INT_RESET, hba->mmio_base + YH2I_INT);
	ssleep(5);
पूर्ण

अटल पूर्णांक stex_करो_reset(काष्ठा st_hba *hba)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mu_status = MU_STATE_RESETTING;

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (hba->mu_status == MU_STATE_STARTING) अणु
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		prपूर्णांकk(KERN_INFO DRV_NAME "(%s): request reset during init\n",
			pci_name(hba->pdev));
		वापस 0;
	पूर्ण
	जबतक (hba->mu_status == MU_STATE_RESETTING) अणु
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		रुको_event_समयout(hba->reset_रुकोq,
				   hba->mu_status != MU_STATE_RESETTING,
				   MU_MAX_DELAY * HZ);
		spin_lock_irqsave(hba->host->host_lock, flags);
		mu_status = hba->mu_status;
	पूर्ण

	अगर (mu_status != MU_STATE_RESETTING) अणु
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		वापस (mu_status == MU_STATE_STARTED) ? 0 : -1;
	पूर्ण

	hba->mu_status = MU_STATE_RESETTING;
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	अगर (hba->cardtype == st_yosemite)
		वापस stex_yos_reset(hba);

	अगर (hba->cardtype == st_shasta)
		stex_hard_reset(hba);
	अन्यथा अगर (hba->cardtype == st_yel)
		stex_ss_reset(hba);
	अन्यथा अगर (hba->cardtype == st_P3)
		stex_p3_reset(hba);

	वापस_abnormal_state(hba, DID_RESET);

	अगर (stex_handshake(hba) == 0)
		वापस 0;

	prपूर्णांकk(KERN_WARNING DRV_NAME "(%s): resetting: handshake failed\n",
		pci_name(hba->pdev));
	वापस -1;
पूर्ण

अटल पूर्णांक stex_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा st_hba *hba;

	hba = (काष्ठा st_hba *) &cmd->device->host->hostdata[0];

	shost_prपूर्णांकk(KERN_INFO, cmd->device->host,
		     "resetting host\n");

	वापस stex_करो_reset(hba) ? FAILED : SUCCESS;
पूर्ण

अटल व्योम stex_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा st_hba *hba = container_of(work, काष्ठा st_hba, reset_work);

	stex_करो_reset(hba);
पूर्ण

अटल पूर्णांक stex_biosparam(काष्ठा scsi_device *sdev,
	काष्ठा block_device *bdev, sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads = 255, sectors = 63;

	अगर (capacity < 0x200000) अणु
		heads = 64;
		sectors = 32;
	पूर्ण

	sector_भाग(capacity, heads * sectors);

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = capacity;

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= DRV_NAME,
	.proc_name			= DRV_NAME,
	.bios_param			= stex_biosparam,
	.queuecommand			= stex_queuecommand,
	.slave_configure		= stex_slave_config,
	.eh_पात_handler		= stex_पात,
	.eh_host_reset_handler		= stex_reset,
	.this_id			= -1,
	.dma_boundary			= PAGE_SIZE - 1,
पूर्ण;

अटल काष्ठा pci_device_id stex_pci_tbl[] = अणु
	/* st_shasta */
	अणु 0x105a, 0x8350, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta पूर्ण, /* SuperTrak EX8350/8300/16350/16300 */
	अणु 0x105a, 0xc350, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta पूर्ण, /* SuperTrak EX12350 */
	अणु 0x105a, 0x4302, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta पूर्ण, /* SuperTrak EX4350 */
	अणु 0x105a, 0xe350, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta पूर्ण, /* SuperTrak EX24350 */

	/* st_vsc */
	अणु 0x105a, 0x7250, PCI_ANY_ID, PCI_ANY_ID, 0, 0, st_vsc पूर्ण,

	/* st_yosemite */
	अणु 0x105a, 0x8650, 0x105a, PCI_ANY_ID, 0, 0, st_yosemite पूर्ण,

	/* st_seq */
	अणु 0x105a, 0x3360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, st_seq पूर्ण,

	/* st_yel */
	अणु 0x105a, 0x8650, 0x1033, PCI_ANY_ID, 0, 0, st_yel पूर्ण,
	अणु 0x105a, 0x8760, PCI_ANY_ID, PCI_ANY_ID, 0, 0, st_yel पूर्ण,

	/* st_P3, pluto */
	अणु PCI_VENDOR_ID_PROMISE, 0x8870, PCI_VENDOR_ID_PROMISE,
		0x8870, 0, 0, st_P3 पूर्ण,
	/* st_P3, p3 */
	अणु PCI_VENDOR_ID_PROMISE, 0x8870, PCI_VENDOR_ID_PROMISE,
		0x4300, 0, 0, st_P3 पूर्ण,

	/* st_P3, SymplyStor4E */
	अणु PCI_VENDOR_ID_PROMISE, 0x8871, PCI_VENDOR_ID_PROMISE,
		0x4311, 0, 0, st_P3 पूर्ण,
	/* st_P3, SymplyStor8E */
	अणु PCI_VENDOR_ID_PROMISE, 0x8871, PCI_VENDOR_ID_PROMISE,
		0x4312, 0, 0, st_P3 पूर्ण,
	/* st_P3, SymplyStor4 */
	अणु PCI_VENDOR_ID_PROMISE, 0x8871, PCI_VENDOR_ID_PROMISE,
		0x4321, 0, 0, st_P3 पूर्ण,
	/* st_P3, SymplyStor8 */
	अणु PCI_VENDOR_ID_PROMISE, 0x8871, PCI_VENDOR_ID_PROMISE,
		0x4322, 0, 0, st_P3 पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा st_card_info stex_card_info[] = अणु
	/* st_shasta */
	अणु
		.max_id		= 17,
		.max_lun	= 8,
		.max_channel	= 0,
		.rq_count	= 32,
		.rq_size	= 1048,
		.sts_count	= 32,
		.alloc_rq	= stex_alloc_req,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	पूर्ण,

	/* st_vsc */
	अणु
		.max_id		= 129,
		.max_lun	= 1,
		.max_channel	= 0,
		.rq_count	= 32,
		.rq_size	= 1048,
		.sts_count	= 32,
		.alloc_rq	= stex_alloc_req,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	पूर्ण,

	/* st_yosemite */
	अणु
		.max_id		= 2,
		.max_lun	= 256,
		.max_channel	= 0,
		.rq_count	= 256,
		.rq_size	= 1048,
		.sts_count	= 256,
		.alloc_rq	= stex_alloc_req,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	पूर्ण,

	/* st_seq */
	अणु
		.max_id		= 129,
		.max_lun	= 1,
		.max_channel	= 0,
		.rq_count	= 32,
		.rq_size	= 1048,
		.sts_count	= 32,
		.alloc_rq	= stex_alloc_req,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	पूर्ण,

	/* st_yel */
	अणु
		.max_id		= 129,
		.max_lun	= 256,
		.max_channel	= 3,
		.rq_count	= 801,
		.rq_size	= 512,
		.sts_count	= 801,
		.alloc_rq	= stex_ss_alloc_req,
		.map_sg		= stex_ss_map_sg,
		.send		= stex_ss_send_cmd,
	पूर्ण,

	/* st_P3 */
	अणु
		.max_id		= 129,
		.max_lun	= 256,
		.max_channel	= 0,
		.rq_count	= 801,
		.rq_size	= 512,
		.sts_count	= 801,
		.alloc_rq	= stex_ss_alloc_req,
		.map_sg		= stex_ss_map_sg,
		.send		= stex_ss_send_cmd,
	पूर्ण,
पूर्ण;

अटल पूर्णांक stex_request_irq(काष्ठा st_hba *hba)
अणु
	काष्ठा pci_dev *pdev = hba->pdev;
	पूर्णांक status;

	अगर (msi || hba->cardtype == st_P3) अणु
		status = pci_enable_msi(pdev);
		अगर (status != 0)
			prपूर्णांकk(KERN_ERR DRV_NAME
				"(%s): error %d setting up MSI\n",
				pci_name(pdev), status);
		अन्यथा
			hba->msi_enabled = 1;
	पूर्ण अन्यथा
		hba->msi_enabled = 0;

	status = request_irq(pdev->irq,
		(hba->cardtype == st_yel || hba->cardtype == st_P3) ?
		stex_ss_पूर्णांकr : stex_पूर्णांकr, IRQF_SHARED, DRV_NAME, hba);

	अगर (status != 0) अणु
		अगर (hba->msi_enabled)
			pci_disable_msi(pdev);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम stex_मुक्त_irq(काष्ठा st_hba *hba)
अणु
	काष्ठा pci_dev *pdev = hba->pdev;

	मुक्त_irq(pdev->irq, hba);
	अगर (hba->msi_enabled)
		pci_disable_msi(pdev);
पूर्ण

अटल पूर्णांक stex_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा st_hba *hba;
	काष्ठा Scsi_Host *host;
	स्थिर काष्ठा st_card_info *ci = शून्य;
	u32 sts_offset, cp_offset, scratch_offset;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	pci_set_master(pdev);

	S6flag = 0;
	रेजिस्टर_reboot_notअगरier(&stex_notअगरier);

	host = scsi_host_alloc(&driver_ढाँचा, माप(काष्ठा st_hba));

	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): scsi_host_alloc failed\n",
			pci_name(pdev));
		err = -ENOMEM;
		जाओ out_disable;
	पूर्ण

	hba = (काष्ठा st_hba *)host->hostdata;
	स_रखो(hba, 0, माप(काष्ठा st_hba));

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): request regions failed\n",
			pci_name(pdev));
		जाओ out_scsi_host_put;
	पूर्ण

	hba->mmio_base = pci_ioremap_bar(pdev, 0);
	अगर ( !hba->mmio_base) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): memory map failed\n",
			pci_name(pdev));
		err = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err)
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): set dma mask failed\n",
			pci_name(pdev));
		जाओ out_iounmap;
	पूर्ण

	hba->cardtype = (अचिन्हित पूर्णांक) id->driver_data;
	ci = &stex_card_info[hba->cardtype];
	चयन (id->subdevice) अणु
	हाल 0x4221:
	हाल 0x4222:
	हाल 0x4223:
	हाल 0x4224:
	हाल 0x4225:
	हाल 0x4226:
	हाल 0x4227:
	हाल 0x4261:
	हाल 0x4262:
	हाल 0x4263:
	हाल 0x4264:
	हाल 0x4265:
		अवरोध;
	शेष:
		अगर (hba->cardtype == st_yel || hba->cardtype == st_P3)
			hba->supports_pm = 1;
	पूर्ण

	sts_offset = scratch_offset = (ci->rq_count+1) * ci->rq_size;
	अगर (hba->cardtype == st_yel || hba->cardtype == st_P3)
		sts_offset += (ci->sts_count+1) * माप(u32);
	cp_offset = sts_offset + (ci->sts_count+1) * माप(काष्ठा status_msg);
	hba->dma_size = cp_offset + माप(काष्ठा st_frame);
	अगर (hba->cardtype == st_seq ||
		(hba->cardtype == st_vsc && (pdev->subप्रणाली_device & 1))) अणु
		hba->extra_offset = hba->dma_size;
		hba->dma_size += ST_ADDITIONAL_MEM;
	पूर्ण
	hba->dma_mem = dma_alloc_coherent(&pdev->dev,
		hba->dma_size, &hba->dma_handle, GFP_KERNEL);
	अगर (!hba->dma_mem) अणु
		/* Retry minimum coherent mapping क्रम st_seq and st_vsc */
		अगर (hba->cardtype == st_seq ||
		    (hba->cardtype == st_vsc && (pdev->subप्रणाली_device & 1))) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
				"(%s): allocating min buffer for controller\n",
				pci_name(pdev));
			hba->dma_size = hba->extra_offset
				+ ST_ADDITIONAL_MEM_MIN;
			hba->dma_mem = dma_alloc_coherent(&pdev->dev,
				hba->dma_size, &hba->dma_handle, GFP_KERNEL);
		पूर्ण

		अगर (!hba->dma_mem) अणु
			err = -ENOMEM;
			prपूर्णांकk(KERN_ERR DRV_NAME "(%s): dma mem alloc failed\n",
				pci_name(pdev));
			जाओ out_iounmap;
		पूर्ण
	पूर्ण

	hba->ccb = kसुस्मृति(ci->rq_count, माप(काष्ठा st_ccb), GFP_KERNEL);
	अगर (!hba->ccb) अणु
		err = -ENOMEM;
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): ccb alloc failed\n",
			pci_name(pdev));
		जाओ out_pci_मुक्त;
	पूर्ण

	अगर (hba->cardtype == st_yel || hba->cardtype == st_P3)
		hba->scratch = (__le32 *)(hba->dma_mem + scratch_offset);
	hba->status_buffer = (काष्ठा status_msg *)(hba->dma_mem + sts_offset);
	hba->copy_buffer = hba->dma_mem + cp_offset;
	hba->rq_count = ci->rq_count;
	hba->rq_size = ci->rq_size;
	hba->sts_count = ci->sts_count;
	hba->alloc_rq = ci->alloc_rq;
	hba->map_sg = ci->map_sg;
	hba->send = ci->send;
	hba->mu_status = MU_STATE_STARTING;
	hba->msi_lock = 0;

	अगर (hba->cardtype == st_yel || hba->cardtype == st_P3)
		host->sg_tablesize = 38;
	अन्यथा
		host->sg_tablesize = 32;
	host->can_queue = ci->rq_count;
	host->cmd_per_lun = ci->rq_count;
	host->max_id = ci->max_id;
	host->max_lun = ci->max_lun;
	host->max_channel = ci->max_channel;
	host->unique_id = host->host_no;
	host->max_cmd_len = STEX_CDB_LENGTH;

	hba->host = host;
	hba->pdev = pdev;
	init_रुकोqueue_head(&hba->reset_रुकोq);

	snम_लिखो(hba->work_q_name, माप(hba->work_q_name),
		 "stex_wq_%d", host->host_no);
	hba->work_q = create_singlethपढ़ो_workqueue(hba->work_q_name);
	अगर (!hba->work_q) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): create workqueue failed\n",
			pci_name(pdev));
		err = -ENOMEM;
		जाओ out_ccb_मुक्त;
	पूर्ण
	INIT_WORK(&hba->reset_work, stex_reset_work);

	err = stex_request_irq(hba);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): request irq failed\n",
			pci_name(pdev));
		जाओ out_मुक्त_wq;
	पूर्ण

	err = stex_handshake(hba);
	अगर (err)
		जाओ out_मुक्त_irq;

	pci_set_drvdata(pdev, hba);

	err = scsi_add_host(host, &pdev->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): scsi_add_host failed\n",
			pci_name(pdev));
		जाओ out_मुक्त_irq;
	पूर्ण

	scsi_scan_host(host);

	वापस 0;

out_मुक्त_irq:
	stex_मुक्त_irq(hba);
out_मुक्त_wq:
	destroy_workqueue(hba->work_q);
out_ccb_मुक्त:
	kमुक्त(hba->ccb);
out_pci_मुक्त:
	dma_मुक्त_coherent(&pdev->dev, hba->dma_size,
			  hba->dma_mem, hba->dma_handle);
out_iounmap:
	iounmap(hba->mmio_base);
out_release_regions:
	pci_release_regions(pdev);
out_scsi_host_put:
	scsi_host_put(host);
out_disable:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम stex_hba_stop(काष्ठा st_hba *hba, पूर्णांक st_sleep_mic)
अणु
	काष्ठा req_msg *req;
	काष्ठा st_msg_header *msg_h;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ beक्रमe;
	u16 tag = 0;

	spin_lock_irqsave(hba->host->host_lock, flags);

	अगर ((hba->cardtype == st_yel || hba->cardtype == st_P3) &&
		hba->supports_pm == 1) अणु
		अगर (st_sleep_mic == ST_NOTHANDLED) अणु
			spin_unlock_irqrestore(hba->host->host_lock, flags);
			वापस;
		पूर्ण
	पूर्ण
	req = hba->alloc_rq(hba);
	अगर (hba->cardtype == st_yel || hba->cardtype == st_P3) अणु
		msg_h = (काष्ठा st_msg_header *)req - 1;
		स_रखो(msg_h, 0, hba->rq_size);
	पूर्ण अन्यथा
		स_रखो(req, 0, hba->rq_size);

	अगर ((hba->cardtype == st_yosemite || hba->cardtype == st_yel
		|| hba->cardtype == st_P3)
		&& st_sleep_mic == ST_IGNORED) अणु
		req->cdb[0] = MGT_CMD;
		req->cdb[1] = MGT_CMD_SIGNATURE;
		req->cdb[2] = CTLR_CONFIG_CMD;
		req->cdb[3] = CTLR_SHUTDOWN;
	पूर्ण अन्यथा अगर ((hba->cardtype == st_yel || hba->cardtype == st_P3)
		&& st_sleep_mic != ST_IGNORED) अणु
		req->cdb[0] = MGT_CMD;
		req->cdb[1] = MGT_CMD_SIGNATURE;
		req->cdb[2] = CTLR_CONFIG_CMD;
		req->cdb[3] = PMIC_SHUTDOWN;
		req->cdb[4] = st_sleep_mic;
	पूर्ण अन्यथा अणु
		req->cdb[0] = CONTROLLER_CMD;
		req->cdb[1] = CTLR_POWER_STATE_CHANGE;
		req->cdb[2] = CTLR_POWER_SAVING;
	पूर्ण
	hba->ccb[tag].cmd = शून्य;
	hba->ccb[tag].sg_count = 0;
	hba->ccb[tag].sense_bufflen = 0;
	hba->ccb[tag].sense_buffer = शून्य;
	hba->ccb[tag].req_type = PASSTHRU_REQ_TYPE;
	hba->send(hba, req, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	beक्रमe = jअगरfies;
	जबतक (hba->ccb[tag].req_type & PASSTHRU_REQ_TYPE) अणु
		अगर (समय_after(jअगरfies, beक्रमe + ST_INTERNAL_TIMEOUT * HZ)) अणु
			hba->ccb[tag].req_type = 0;
			hba->mu_status = MU_STATE_STOP;
			वापस;
		पूर्ण
		msleep(1);
	पूर्ण
	hba->mu_status = MU_STATE_STOP;
पूर्ण

अटल व्योम stex_hba_मुक्त(काष्ठा st_hba *hba)
अणु
	stex_मुक्त_irq(hba);

	destroy_workqueue(hba->work_q);

	iounmap(hba->mmio_base);

	pci_release_regions(hba->pdev);

	kमुक्त(hba->ccb);

	dma_मुक्त_coherent(&hba->pdev->dev, hba->dma_size,
			  hba->dma_mem, hba->dma_handle);
पूर्ण

अटल व्योम stex_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा st_hba *hba = pci_get_drvdata(pdev);

	hba->mu_status = MU_STATE_NOCONNECT;
	वापस_abnormal_state(hba, DID_NO_CONNECT);
	scsi_हटाओ_host(hba->host);

	scsi_block_requests(hba->host);

	stex_hba_मुक्त(hba);

	scsi_host_put(hba->host);

	pci_disable_device(pdev);

	unरेजिस्टर_reboot_notअगरier(&stex_notअगरier);
पूर्ण

अटल व्योम stex_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा st_hba *hba = pci_get_drvdata(pdev);

	अगर (hba->supports_pm == 0) अणु
		stex_hba_stop(hba, ST_IGNORED);
	पूर्ण अन्यथा अगर (hba->supports_pm == 1 && S6flag) अणु
		unरेजिस्टर_reboot_notअगरier(&stex_notअगरier);
		stex_hba_stop(hba, ST_S6);
	पूर्ण अन्यथा
		stex_hba_stop(hba, ST_S5);
पूर्ण

अटल पूर्णांक stex_choice_sleep_mic(काष्ठा st_hba *hba, pm_message_t state)
अणु
	चयन (state.event) अणु
	हाल PM_EVENT_SUSPEND:
		वापस ST_S3;
	हाल PM_EVENT_HIBERNATE:
		hba->msi_lock = 0;
		वापस ST_S4;
	शेष:
		वापस ST_NOTHANDLED;
	पूर्ण
पूर्ण

अटल पूर्णांक stex_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा st_hba *hba = pci_get_drvdata(pdev);

	अगर ((hba->cardtype == st_yel || hba->cardtype == st_P3)
		&& hba->supports_pm == 1)
		stex_hba_stop(hba, stex_choice_sleep_mic(hba, state));
	अन्यथा
		stex_hba_stop(hba, ST_IGNORED);
	वापस 0;
पूर्ण

अटल पूर्णांक stex_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा st_hba *hba = pci_get_drvdata(pdev);

	hba->mu_status = MU_STATE_STARTING;
	stex_handshake(hba);
	वापस 0;
पूर्ण

अटल पूर्णांक stex_halt(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *buf)
अणु
	S6flag = 1;
	वापस NOTIFY_OK;
पूर्ण
MODULE_DEVICE_TABLE(pci, stex_pci_tbl);

अटल काष्ठा pci_driver stex_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= stex_pci_tbl,
	.probe		= stex_probe,
	.हटाओ		= stex_हटाओ,
	.shutकरोwn	= stex_shutकरोwn,
	.suspend	= stex_suspend,
	.resume		= stex_resume,
पूर्ण;

अटल पूर्णांक __init stex_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO DRV_NAME
		": Promise SuperTrak EX Driver version: %s\n",
		 ST_DRIVER_VERSION);

	वापस pci_रेजिस्टर_driver(&stex_pci_driver);
पूर्ण

अटल व्योम __निकास stex_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&stex_pci_driver);
पूर्ण

module_init(stex_init);
module_निकास(stex_निकास);
