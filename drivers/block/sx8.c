<शैली गुरु>
/*
 *  sx8.c: Driver क्रम Promise SATA SX8 looks-like-I2O hardware
 *
 *  Copyright 2004-2005 Red Hat, Inc.
 *
 *  Author/मुख्यtainer:  Jeff Garzik <jgarzik@pobox.com>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file "COPYING" in the मुख्य directory of this archive
 *  क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compiler.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/hdreg.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/completion.h>
#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#अगर 0
#घोषणा CARM_DEBUG
#घोषणा CARM_VERBOSE_DEBUG
#अन्यथा
#अघोषित CARM_DEBUG
#अघोषित CARM_VERBOSE_DEBUG
#पूर्ण_अगर
#अघोषित CARM_न_संशोधन

#घोषणा DRV_NAME "sx8"
#घोषणा DRV_VERSION "1.0"
#घोषणा PFX DRV_NAME ": "

MODULE_AUTHOR("Jeff Garzik");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Promise SATA SX8 block driver");
MODULE_VERSION(DRV_VERSION);

/*
 * SX8 hardware has a single message queue क्रम all ATA ports.
 * When this driver was written, the hardware (firmware?) would
 * corrupt data eventually, अगर more than one request was outstanding.
 * As one can imagine, having 8 ports bottlenecking on a single
 * command hurts perक्रमmance.
 *
 * Based on user reports, later versions of the hardware (firmware?)
 * seem to be able to survive with more than one command queued.
 *
 * Thereक्रमe, we शेष to the safe option -- 1 command -- but
 * allow the user to increase this.
 *
 * SX8 should be able to support up to ~60 queued commands (CARM_MAX_REQ),
 * but problems seem to occur when you exceed ~30, even on newer hardware.
 */
अटल पूर्णांक max_queue = 1;
module_param(max_queue, पूर्णांक, 0444);
MODULE_PARM_DESC(max_queue, "Maximum number of queued commands. (min==1, max==30, safe==1)");


#घोषणा NEXT_RESP(idx)	((idx + 1) % RMSG_Q_LEN)

/* 0xf is just arbitrary, non-zero noise; this is sorta like poisoning */
#घोषणा TAG_ENCODE(tag)	(((tag) << 16) | 0xf)
#घोषणा TAG_DECODE(tag)	(((tag) >> 16) & 0x1f)
#घोषणा TAG_VALID(tag)	((((tag) & 0xf) == 0xf) && (TAG_DECODE(tag) < 32))

/* note: prपूर्णांकs function name क्रम you */
#अगर_घोषित CARM_DEBUG
#घोषणा DPRINTK(fmt, args...) prपूर्णांकk(KERN_ERR "%s: " fmt, __func__, ## args)
#अगर_घोषित CARM_VERBOSE_DEBUG
#घोषणा VPRINTK(fmt, args...) prपूर्णांकk(KERN_ERR "%s: " fmt, __func__, ## args)
#अन्यथा
#घोषणा VPRINTK(fmt, args...)
#पूर्ण_अगर	/* CARM_VERBOSE_DEBUG */
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#घोषणा VPRINTK(fmt, args...)
#पूर्ण_अगर	/* CARM_DEBUG */

#अगर_घोषित CARM_न_संशोधन
#घोषणा निश्चित(expr)
#अन्यथा
#घोषणा निश्चित(expr) \
        अगर(unlikely(!(expr))) अणु                                   \
        prपूर्णांकk(KERN_ERR "Assertion failed! %s,%s,%s,line=%d\n", \
	#expr, __खाता__, __func__, __LINE__);          \
        पूर्ण
#पूर्ण_अगर

/* defines only क्रम the स्थिरants which करोn't work well as क्रमागतs */
काष्ठा carm_host;

क्रमागत अणु
	/* adapter-wide limits */
	CARM_MAX_PORTS		= 8,
	CARM_SHM_SIZE		= (4096 << 7),
	CARM_MINORS_PER_MAJOR	= 256 / CARM_MAX_PORTS,
	CARM_MAX_WAIT_Q		= CARM_MAX_PORTS + 1,

	/* command message queue limits */
	CARM_MAX_REQ		= 64,	       /* max command msgs per host */
	CARM_MSG_LOW_WATER	= (CARM_MAX_REQ / 4),	     /* refill mark */

	/* S/G limits, host-wide and per-request */
	CARM_MAX_REQ_SG		= 32,	     /* max s/g entries per request */
	CARM_MAX_HOST_SG	= 600,		/* max s/g entries per host */
	CARM_SG_LOW_WATER	= (CARM_MAX_HOST_SG / 4),   /* re-fill mark */

	/* hardware रेजिस्टरs */
	CARM_IHQP		= 0x1c,
	CARM_INT_STAT		= 0x10, /* पूर्णांकerrupt status */
	CARM_INT_MASK		= 0x14, /* पूर्णांकerrupt mask */
	CARM_HMUC		= 0x18, /* host message unit control */
	RBUF_ADDR_LO		= 0x20, /* response msg DMA buf low 32 bits */
	RBUF_ADDR_HI		= 0x24, /* response msg DMA buf high 32 bits */
	RBUF_BYTE_SZ		= 0x28,
	CARM_RESP_IDX		= 0x2c,
	CARM_CMS0		= 0x30, /* command message size reg 0 */
	CARM_LMUC		= 0x48,
	CARM_HMPHA		= 0x6c,
	CARM_INITC		= 0xb5,

	/* bits in CARM_INT_अणुSTAT,MASKपूर्ण */
	INT_RESERVED		= 0xfffffff0,
	INT_WATCHDOG		= (1 << 3),	/* watchकरोg समयr */
	INT_Q_OVERFLOW		= (1 << 2),	/* cmd msg q overflow */
	INT_Q_AVAILABLE		= (1 << 1),	/* cmd msg q has मुक्त space */
	INT_RESPONSE		= (1 << 0),	/* response msg available */
	INT_ACK_MASK		= INT_WATCHDOG | INT_Q_OVERFLOW,
	INT_DEF_MASK		= INT_RESERVED | INT_Q_OVERFLOW |
				  INT_RESPONSE,

	/* command messages, and related रेजिस्टर bits */
	CARM_HAVE_RESP		= 0x01,
	CARM_MSG_READ		= 1,
	CARM_MSG_WRITE		= 2,
	CARM_MSG_VERIFY		= 3,
	CARM_MSG_GET_CAPACITY	= 4,
	CARM_MSG_FLUSH		= 5,
	CARM_MSG_IOCTL		= 6,
	CARM_MSG_ARRAY		= 8,
	CARM_MSG_MISC		= 9,
	CARM_CME		= (1 << 2),
	CARM_RME		= (1 << 1),
	CARM_WZBC		= (1 << 0),
	CARM_RMI		= (1 << 0),
	CARM_Q_FULL		= (1 << 3),
	CARM_MSG_SIZE		= 288,
	CARM_Q_LEN		= 48,

	/* CARM_MSG_IOCTL messages */
	CARM_IOC_SCAN_CHAN	= 5,	/* scan channels क्रम devices */
	CARM_IOC_GET_TCQ	= 13,	/* get tcq/ncq depth */
	CARM_IOC_SET_TCQ	= 14,	/* set tcq/ncq depth */

	IOC_SCAN_CHAN_NODEV	= 0x1f,
	IOC_SCAN_CHAN_OFFSET	= 0x40,

	/* CARM_MSG_ARRAY messages */
	CARM_ARRAY_INFO		= 0,

	ARRAY_NO_EXIST		= (1 << 31),

	/* response messages */
	RMSG_SZ			= 8,	/* माप(काष्ठा carm_response) */
	RMSG_Q_LEN		= 48,	/* resp. msg list length */
	RMSG_OK			= 1,	/* bit indicating msg was successful */
					/* length of entire resp. msg buffer */
	RBUF_LEN		= RMSG_SZ * RMSG_Q_LEN,

	PDC_SHM_SIZE		= (4096 << 7), /* length of entire h/w buffer */

	/* CARM_MSG_MISC messages */
	MISC_GET_FW_VER		= 2,
	MISC_ALLOC_MEM		= 3,
	MISC_SET_TIME		= 5,

	/* MISC_GET_FW_VER feature bits */
	FW_VER_4PORT		= (1 << 2), /* 1=4 ports, 0=8 ports */
	FW_VER_NON_RAID		= (1 << 1), /* 1=non-RAID firmware, 0=RAID */
	FW_VER_ZCR		= (1 << 0), /* zero channel RAID (whatever that is) */

	/* carm_host flags */
	FL_NON_RAID		= FW_VER_NON_RAID,
	FL_4PORT		= FW_VER_4PORT,
	FL_FW_VER_MASK		= (FW_VER_NON_RAID | FW_VER_4PORT),
	FL_DYN_MAJOR		= (1 << 17),
पूर्ण;

क्रमागत अणु
	CARM_SG_BOUNDARY	= 0xffffUL,	    /* s/g segment boundary */
पूर्ण;

क्रमागत scatter_gather_types अणु
	SGT_32BIT		= 0,
	SGT_64BIT		= 1,
पूर्ण;

क्रमागत host_states अणु
	HST_INVALID,		/* invalid state; never used */
	HST_ALLOC_BUF,		/* setting up master SHM area */
	HST_ERROR,		/* we never leave here */
	HST_PORT_SCAN,		/* start dev scan */
	HST_DEV_SCAN_START,	/* start per-device probe */
	HST_DEV_SCAN,		/* जारी per-device probe */
	HST_DEV_ACTIVATE,	/* activate devices we found */
	HST_PROBE_FINISHED,	/* probe is complete */
	HST_PROBE_START,	/* initiate probe */
	HST_SYNC_TIME,		/* tell firmware what समय it is */
	HST_GET_FW_VER,		/* get firmware version, adapter port cnt */
पूर्ण;

#अगर_घोषित CARM_DEBUG
अटल स्थिर अक्षर *state_name[] = अणु
	"HST_INVALID",
	"HST_ALLOC_BUF",
	"HST_ERROR",
	"HST_PORT_SCAN",
	"HST_DEV_SCAN_START",
	"HST_DEV_SCAN",
	"HST_DEV_ACTIVATE",
	"HST_PROBE_FINISHED",
	"HST_PROBE_START",
	"HST_SYNC_TIME",
	"HST_GET_FW_VER",
पूर्ण;
#पूर्ण_अगर

काष्ठा carm_port अणु
	अचिन्हित पूर्णांक			port_no;
	काष्ठा gendisk			*disk;
	काष्ठा carm_host		*host;

	/* attached device अक्षरacteristics */
	u64				capacity;
	अक्षर				name[41];
	u16				dev_geom_head;
	u16				dev_geom_sect;
	u16				dev_geom_cyl;
पूर्ण;

काष्ठा carm_request अणु
	पूर्णांक				n_elem;
	अचिन्हित पूर्णांक			msg_type;
	अचिन्हित पूर्णांक			msg_subtype;
	अचिन्हित पूर्णांक			msg_bucket;
	काष्ठा scatterlist		sg[CARM_MAX_REQ_SG];
पूर्ण;

काष्ठा carm_host अणु
	अचिन्हित दीर्घ			flags;
	व्योम				__iomem *mmio;
	व्योम				*shm;
	dma_addr_t			shm_dma;

	पूर्णांक				major;
	पूर्णांक				id;
	अक्षर				name[32];

	spinlock_t			lock;
	काष्ठा pci_dev			*pdev;
	अचिन्हित पूर्णांक			state;
	u32				fw_ver;

	काष्ठा blk_mq_tag_set		tag_set;
	काष्ठा request_queue		*oob_q;
	अचिन्हित पूर्णांक			n_oob;

	अचिन्हित पूर्णांक			hw_sg_used;

	अचिन्हित पूर्णांक			resp_idx;

	अचिन्हित पूर्णांक			रुको_q_prod;
	अचिन्हित पूर्णांक			रुको_q_cons;
	काष्ठा request_queue		*रुको_q[CARM_MAX_WAIT_Q];

	व्योम				*msg_base;
	dma_addr_t			msg_dma;

	पूर्णांक				cur_scan_dev;
	अचिन्हित दीर्घ			dev_active;
	अचिन्हित दीर्घ			dev_present;
	काष्ठा carm_port		port[CARM_MAX_PORTS];

	काष्ठा work_काष्ठा		fsm_task;

	काष्ठा completion		probe_comp;
पूर्ण;

काष्ठा carm_response अणु
	__le32 ret_handle;
	__le32 status;
पूर्ण  __attribute__((packed));

काष्ठा carm_msg_sg अणु
	__le32 start;
	__le32 len;
पूर्ण  __attribute__((packed));

काष्ठा carm_msg_rw अणु
	u8 type;
	u8 id;
	u8 sg_count;
	u8 sg_type;
	__le32 handle;
	__le32 lba;
	__le16 lba_count;
	__le16 lba_high;
	काष्ठा carm_msg_sg sg[32];
पूर्ण  __attribute__((packed));

काष्ठा carm_msg_allocbuf अणु
	u8 type;
	u8 subtype;
	u8 n_sg;
	u8 sg_type;
	__le32 handle;
	__le32 addr;
	__le32 len;
	__le32 evt_pool;
	__le32 n_evt;
	__le32 rbuf_pool;
	__le32 n_rbuf;
	__le32 msg_pool;
	__le32 n_msg;
	काष्ठा carm_msg_sg sg[8];
पूर्ण  __attribute__((packed));

काष्ठा carm_msg_ioctl अणु
	u8 type;
	u8 subtype;
	u8 array_id;
	u8 reserved1;
	__le32 handle;
	__le32 data_addr;
	u32 reserved2;
पूर्ण  __attribute__((packed));

काष्ठा carm_msg_sync_समय अणु
	u8 type;
	u8 subtype;
	u16 reserved1;
	__le32 handle;
	u32 reserved2;
	__le32 बारtamp;
पूर्ण  __attribute__((packed));

काष्ठा carm_msg_get_fw_ver अणु
	u8 type;
	u8 subtype;
	u16 reserved1;
	__le32 handle;
	__le32 data_addr;
	u32 reserved2;
पूर्ण  __attribute__((packed));

काष्ठा carm_fw_ver अणु
	__le32 version;
	u8 features;
	u8 reserved1;
	u16 reserved2;
पूर्ण  __attribute__((packed));

काष्ठा carm_array_info अणु
	__le32 size;

	__le16 size_hi;
	__le16 stripe_size;

	__le32 mode;

	__le16 stripe_blk_sz;
	__le16 reserved1;

	__le16 cyl;
	__le16 head;

	__le16 sect;
	u8 array_id;
	u8 reserved2;

	अक्षर name[40];

	__le32 array_status;

	/* device list जारीs beyond this poपूर्णांक? */
पूर्ण  __attribute__((packed));

अटल पूर्णांक carm_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम carm_हटाओ_one (काष्ठा pci_dev *pdev);
अटल पूर्णांक carm_bdev_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo);

अटल स्थिर काष्ठा pci_device_id carm_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_PROMISE, 0x8000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, पूर्ण,
	अणु PCI_VENDOR_ID_PROMISE, 0x8002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, carm_pci_tbl);

अटल काष्ठा pci_driver carm_driver = अणु
	.name		= DRV_NAME,
	.id_table	= carm_pci_tbl,
	.probe		= carm_init_one,
	.हटाओ		= carm_हटाओ_one,
पूर्ण;

अटल स्थिर काष्ठा block_device_operations carm_bd_ops = अणु
	.owner		= THIS_MODULE,
	.getgeo		= carm_bdev_getgeo,
पूर्ण;

अटल अचिन्हित पूर्णांक carm_host_id;
अटल अचिन्हित दीर्घ carm_major_alloc;



अटल पूर्णांक carm_bdev_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा carm_port *port = bdev->bd_disk->निजी_data;

	geo->heads = (u8) port->dev_geom_head;
	geo->sectors = (u8) port->dev_geom_sect;
	geo->cylinders = port->dev_geom_cyl;
	वापस 0;
पूर्ण

अटल स्थिर u32 msg_sizes[] = अणु 32, 64, 128, CARM_MSG_SIZE पूर्ण;

अटल अंतरभूत पूर्णांक carm_lookup_bucket(u32 msg_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(msg_sizes); i++)
		अगर (msg_size <= msg_sizes[i])
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल व्योम carm_init_buckets(व्योम __iomem *mmio)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(msg_sizes); i++)
		ग_लिखोl(msg_sizes[i], mmio + CARM_CMS0 + (4 * i));
पूर्ण

अटल अंतरभूत व्योम *carm_ref_msg(काष्ठा carm_host *host,
				 अचिन्हित पूर्णांक msg_idx)
अणु
	वापस host->msg_base + (msg_idx * CARM_MSG_SIZE);
पूर्ण

अटल अंतरभूत dma_addr_t carm_ref_msg_dma(काष्ठा carm_host *host,
					  अचिन्हित पूर्णांक msg_idx)
अणु
	वापस host->msg_dma + (msg_idx * CARM_MSG_SIZE);
पूर्ण

अटल पूर्णांक carm_send_msg(काष्ठा carm_host *host,
			 काष्ठा carm_request *crq, अचिन्हित tag)
अणु
	व्योम __iomem *mmio = host->mmio;
	u32 msg = (u32) carm_ref_msg_dma(host, tag);
	u32 cm_bucket = crq->msg_bucket;
	u32 पंचांगp;
	पूर्णांक rc = 0;

	VPRINTK("ENTER\n");

	पंचांगp = पढ़ोl(mmio + CARM_HMUC);
	अगर (पंचांगp & CARM_Q_FULL) अणु
#अगर 0
		पंचांगp = पढ़ोl(mmio + CARM_INT_MASK);
		पंचांगp |= INT_Q_AVAILABLE;
		ग_लिखोl(पंचांगp, mmio + CARM_INT_MASK);
		पढ़ोl(mmio + CARM_INT_MASK);	/* flush */
#पूर्ण_अगर
		DPRINTK("host msg queue full\n");
		rc = -EBUSY;
	पूर्ण अन्यथा अणु
		ग_लिखोl(msg | (cm_bucket << 1), mmio + CARM_IHQP);
		पढ़ोl(mmio + CARM_IHQP);	/* flush */
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक carm_array_info (काष्ठा carm_host *host, अचिन्हित पूर्णांक array_idx)
अणु
	काष्ठा carm_msg_ioctl *ioc;
	u32 msg_data;
	dma_addr_t msg_dma;
	काष्ठा carm_request *crq;
	काष्ठा request *rq;
	पूर्णांक rc;

	rq = blk_mq_alloc_request(host->oob_q, REQ_OP_DRV_OUT, 0);
	अगर (IS_ERR(rq)) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	crq = blk_mq_rq_to_pdu(rq);

	ioc = carm_ref_msg(host, rq->tag);
	msg_dma = carm_ref_msg_dma(host, rq->tag);
	msg_data = (u32) (msg_dma + माप(काष्ठा carm_array_info));

	crq->msg_type = CARM_MSG_ARRAY;
	crq->msg_subtype = CARM_ARRAY_INFO;
	rc = carm_lookup_bucket(माप(काष्ठा carm_msg_ioctl) +
				माप(काष्ठा carm_array_info));
	BUG_ON(rc < 0);
	crq->msg_bucket = (u32) rc;

	स_रखो(ioc, 0, माप(*ioc));
	ioc->type	= CARM_MSG_ARRAY;
	ioc->subtype	= CARM_ARRAY_INFO;
	ioc->array_id	= (u8) array_idx;
	ioc->handle	= cpu_to_le32(TAG_ENCODE(rq->tag));
	ioc->data_addr	= cpu_to_le32(msg_data);

	spin_lock_irq(&host->lock);
	निश्चित(host->state == HST_DEV_SCAN_START ||
	       host->state == HST_DEV_SCAN);
	spin_unlock_irq(&host->lock);

	DPRINTK("blk_execute_rq_nowait, tag == %u\n", rq->tag);
	blk_execute_rq_noरुको(शून्य, rq, true, शून्य);

	वापस 0;

err_out:
	spin_lock_irq(&host->lock);
	host->state = HST_ERROR;
	spin_unlock_irq(&host->lock);
	वापस rc;
पूर्ण

प्रकार अचिन्हित पूर्णांक (*carm_sspc_t)(काष्ठा carm_host *, अचिन्हित पूर्णांक, व्योम *);

अटल पूर्णांक carm_send_special (काष्ठा carm_host *host, carm_sspc_t func)
अणु
	काष्ठा request *rq;
	काष्ठा carm_request *crq;
	काष्ठा carm_msg_ioctl *ioc;
	व्योम *mem;
	अचिन्हित पूर्णांक msg_size;
	पूर्णांक rc;

	rq = blk_mq_alloc_request(host->oob_q, REQ_OP_DRV_OUT, 0);
	अगर (IS_ERR(rq))
		वापस -ENOMEM;
	crq = blk_mq_rq_to_pdu(rq);

	mem = carm_ref_msg(host, rq->tag);

	msg_size = func(host, rq->tag, mem);

	ioc = mem;
	crq->msg_type = ioc->type;
	crq->msg_subtype = ioc->subtype;
	rc = carm_lookup_bucket(msg_size);
	BUG_ON(rc < 0);
	crq->msg_bucket = (u32) rc;

	DPRINTK("blk_execute_rq_nowait, tag == %u\n", rq->tag);
	blk_execute_rq_noरुको(शून्य, rq, true, शून्य);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक carm_fill_sync_समय(काष्ठा carm_host *host,
					अचिन्हित पूर्णांक idx, व्योम *mem)
अणु
	काष्ठा carm_msg_sync_समय *st = mem;

	समय64_t tv = kसमय_get_real_seconds();

	स_रखो(st, 0, माप(*st));
	st->type	= CARM_MSG_MISC;
	st->subtype	= MISC_SET_TIME;
	st->handle	= cpu_to_le32(TAG_ENCODE(idx));
	st->बारtamp	= cpu_to_le32(tv);

	वापस माप(काष्ठा carm_msg_sync_समय);
पूर्ण

अटल अचिन्हित पूर्णांक carm_fill_alloc_buf(काष्ठा carm_host *host,
					अचिन्हित पूर्णांक idx, व्योम *mem)
अणु
	काष्ठा carm_msg_allocbuf *ab = mem;

	स_रखो(ab, 0, माप(*ab));
	ab->type	= CARM_MSG_MISC;
	ab->subtype	= MISC_ALLOC_MEM;
	ab->handle	= cpu_to_le32(TAG_ENCODE(idx));
	ab->n_sg	= 1;
	ab->sg_type	= SGT_32BIT;
	ab->addr	= cpu_to_le32(host->shm_dma + (PDC_SHM_SIZE >> 1));
	ab->len		= cpu_to_le32(PDC_SHM_SIZE >> 1);
	ab->evt_pool	= cpu_to_le32(host->shm_dma + (16 * 1024));
	ab->n_evt	= cpu_to_le32(1024);
	ab->rbuf_pool	= cpu_to_le32(host->shm_dma);
	ab->n_rbuf	= cpu_to_le32(RMSG_Q_LEN);
	ab->msg_pool	= cpu_to_le32(host->shm_dma + RBUF_LEN);
	ab->n_msg	= cpu_to_le32(CARM_Q_LEN);
	ab->sg[0].start	= cpu_to_le32(host->shm_dma + (PDC_SHM_SIZE >> 1));
	ab->sg[0].len	= cpu_to_le32(65536);

	वापस माप(काष्ठा carm_msg_allocbuf);
पूर्ण

अटल अचिन्हित पूर्णांक carm_fill_scan_channels(काष्ठा carm_host *host,
					    अचिन्हित पूर्णांक idx, व्योम *mem)
अणु
	काष्ठा carm_msg_ioctl *ioc = mem;
	u32 msg_data = (u32) (carm_ref_msg_dma(host, idx) +
			      IOC_SCAN_CHAN_OFFSET);

	स_रखो(ioc, 0, माप(*ioc));
	ioc->type	= CARM_MSG_IOCTL;
	ioc->subtype	= CARM_IOC_SCAN_CHAN;
	ioc->handle	= cpu_to_le32(TAG_ENCODE(idx));
	ioc->data_addr	= cpu_to_le32(msg_data);

	/* fill output data area with "no device" शेष values */
	mem += IOC_SCAN_CHAN_OFFSET;
	स_रखो(mem, IOC_SCAN_CHAN_NODEV, CARM_MAX_PORTS);

	वापस IOC_SCAN_CHAN_OFFSET + CARM_MAX_PORTS;
पूर्ण

अटल अचिन्हित पूर्णांक carm_fill_get_fw_ver(काष्ठा carm_host *host,
					 अचिन्हित पूर्णांक idx, व्योम *mem)
अणु
	काष्ठा carm_msg_get_fw_ver *ioc = mem;
	u32 msg_data = (u32) (carm_ref_msg_dma(host, idx) + माप(*ioc));

	स_रखो(ioc, 0, माप(*ioc));
	ioc->type	= CARM_MSG_MISC;
	ioc->subtype	= MISC_GET_FW_VER;
	ioc->handle	= cpu_to_le32(TAG_ENCODE(idx));
	ioc->data_addr	= cpu_to_le32(msg_data);

	वापस माप(काष्ठा carm_msg_get_fw_ver) +
	       माप(काष्ठा carm_fw_ver);
पूर्ण

अटल अंतरभूत व्योम carm_push_q (काष्ठा carm_host *host, काष्ठा request_queue *q)
अणु
	अचिन्हित पूर्णांक idx = host->रुको_q_prod % CARM_MAX_WAIT_Q;

	blk_mq_stop_hw_queues(q);
	VPRINTK("STOPPED QUEUE %p\n", q);

	host->रुको_q[idx] = q;
	host->रुको_q_prod++;
	BUG_ON(host->रुको_q_prod == host->रुको_q_cons); /* overrun */
पूर्ण

अटल अंतरभूत काष्ठा request_queue *carm_pop_q(काष्ठा carm_host *host)
अणु
	अचिन्हित पूर्णांक idx;

	अगर (host->रुको_q_prod == host->रुको_q_cons)
		वापस शून्य;

	idx = host->रुको_q_cons % CARM_MAX_WAIT_Q;
	host->रुको_q_cons++;

	वापस host->रुको_q[idx];
पूर्ण

अटल अंतरभूत व्योम carm_round_robin(काष्ठा carm_host *host)
अणु
	काष्ठा request_queue *q = carm_pop_q(host);
	अगर (q) अणु
		blk_mq_start_hw_queues(q);
		VPRINTK("STARTED QUEUE %p\n", q);
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत dma_data_direction carm_rq_dir(काष्ठा request *rq)
अणु
	वापस op_is_ग_लिखो(req_op(rq)) ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
पूर्ण

अटल blk_status_t carm_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				  स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा request *rq = bd->rq;
	काष्ठा carm_port *port = q->queuedata;
	काष्ठा carm_host *host = port->host;
	काष्ठा carm_request *crq = blk_mq_rq_to_pdu(rq);
	काष्ठा carm_msg_rw *msg;
	काष्ठा scatterlist *sg;
	पूर्णांक i, n_elem = 0, rc;
	अचिन्हित पूर्णांक msg_size;
	u32 पंचांगp;

	crq->n_elem = 0;
	sg_init_table(crq->sg, CARM_MAX_REQ_SG);

	blk_mq_start_request(rq);

	spin_lock_irq(&host->lock);
	अगर (req_op(rq) == REQ_OP_DRV_OUT)
		जाओ send_msg;

	/* get scatterlist from block layer */
	sg = &crq->sg[0];
	n_elem = blk_rq_map_sg(q, rq, sg);
	अगर (n_elem <= 0)
		जाओ out_ioerr;

	/* map scatterlist to PCI bus addresses */
	n_elem = dma_map_sg(&host->pdev->dev, sg, n_elem, carm_rq_dir(rq));
	अगर (n_elem <= 0)
		जाओ out_ioerr;

	/* obey global hardware limit on S/G entries */
	अगर (host->hw_sg_used >= CARM_MAX_HOST_SG - n_elem)
		जाओ out_resource;

	crq->n_elem = n_elem;
	host->hw_sg_used += n_elem;

	/*
	 * build पढ़ो/ग_लिखो message
	 */

	VPRINTK("build msg\n");
	msg = (काष्ठा carm_msg_rw *) carm_ref_msg(host, rq->tag);

	अगर (rq_data_dir(rq) == WRITE) अणु
		msg->type = CARM_MSG_WRITE;
		crq->msg_type = CARM_MSG_WRITE;
	पूर्ण अन्यथा अणु
		msg->type = CARM_MSG_READ;
		crq->msg_type = CARM_MSG_READ;
	पूर्ण

	msg->id		= port->port_no;
	msg->sg_count	= n_elem;
	msg->sg_type	= SGT_32BIT;
	msg->handle	= cpu_to_le32(TAG_ENCODE(rq->tag));
	msg->lba	= cpu_to_le32(blk_rq_pos(rq) & 0xffffffff);
	पंचांगp		= (blk_rq_pos(rq) >> 16) >> 16;
	msg->lba_high	= cpu_to_le16( (u16) पंचांगp );
	msg->lba_count	= cpu_to_le16(blk_rq_sectors(rq));

	msg_size = माप(काष्ठा carm_msg_rw) - माप(msg->sg);
	क्रम (i = 0; i < n_elem; i++) अणु
		काष्ठा carm_msg_sg *carm_sg = &msg->sg[i];
		carm_sg->start = cpu_to_le32(sg_dma_address(&crq->sg[i]));
		carm_sg->len = cpu_to_le32(sg_dma_len(&crq->sg[i]));
		msg_size += माप(काष्ठा carm_msg_sg);
	पूर्ण

	rc = carm_lookup_bucket(msg_size);
	BUG_ON(rc < 0);
	crq->msg_bucket = (u32) rc;
send_msg:
	/*
	 * queue पढ़ो/ग_लिखो message to hardware
	 */
	VPRINTK("send msg, tag == %u\n", rq->tag);
	rc = carm_send_msg(host, crq, rq->tag);
	अगर (rc) अणु
		host->hw_sg_used -= n_elem;
		जाओ out_resource;
	पूर्ण

	spin_unlock_irq(&host->lock);
	वापस BLK_STS_OK;
out_resource:
	dma_unmap_sg(&host->pdev->dev, &crq->sg[0], n_elem, carm_rq_dir(rq));
	carm_push_q(host, q);
	spin_unlock_irq(&host->lock);
	वापस BLK_STS_DEV_RESOURCE;
out_ioerr:
	carm_round_robin(host);
	spin_unlock_irq(&host->lock);
	वापस BLK_STS_IOERR;
पूर्ण

अटल व्योम carm_handle_array_info(काष्ठा carm_host *host,
				   काष्ठा carm_request *crq, u8 *mem,
				   blk_status_t error)
अणु
	काष्ठा carm_port *port;
	u8 *msg_data = mem + माप(काष्ठा carm_array_info);
	काष्ठा carm_array_info *desc = (काष्ठा carm_array_info *) msg_data;
	u64 lo, hi;
	पूर्णांक cur_port;
	माप_प्रकार slen;

	DPRINTK("ENTER\n");

	अगर (error)
		जाओ out;
	अगर (le32_to_cpu(desc->array_status) & ARRAY_NO_EXIST)
		जाओ out;

	cur_port = host->cur_scan_dev;

	/* should never occur */
	अगर ((cur_port < 0) || (cur_port >= CARM_MAX_PORTS)) अणु
		prपूर्णांकk(KERN_ERR PFX "BUG: cur_scan_dev==%d, array_id==%d\n",
		       cur_port, (पूर्णांक) desc->array_id);
		जाओ out;
	पूर्ण

	port = &host->port[cur_port];

	lo = (u64) le32_to_cpu(desc->size);
	hi = (u64) le16_to_cpu(desc->size_hi);

	port->capacity = lo | (hi << 32);
	port->dev_geom_head = le16_to_cpu(desc->head);
	port->dev_geom_sect = le16_to_cpu(desc->sect);
	port->dev_geom_cyl = le16_to_cpu(desc->cyl);

	host->dev_active |= (1 << cur_port);

	म_नकलन(port->name, desc->name, माप(port->name));
	port->name[माप(port->name) - 1] = 0;
	slen = म_माप(port->name);
	जबतक (slen && (port->name[slen - 1] == ' ')) अणु
		port->name[slen - 1] = 0;
		slen--;
	पूर्ण

	prपूर्णांकk(KERN_INFO DRV_NAME "(%s): port %u device %Lu sectors\n",
	       pci_name(host->pdev), port->port_no,
	       (अचिन्हित दीर्घ दीर्घ) port->capacity);
	prपूर्णांकk(KERN_INFO DRV_NAME "(%s): port %u device \"%s\"\n",
	       pci_name(host->pdev), port->port_no, port->name);

out:
	निश्चित(host->state == HST_DEV_SCAN);
	schedule_work(&host->fsm_task);
पूर्ण

अटल व्योम carm_handle_scan_chan(काष्ठा carm_host *host,
				  काष्ठा carm_request *crq, u8 *mem,
				  blk_status_t error)
अणु
	u8 *msg_data = mem + IOC_SCAN_CHAN_OFFSET;
	अचिन्हित पूर्णांक i, dev_count = 0;
	पूर्णांक new_state = HST_DEV_SCAN_START;

	DPRINTK("ENTER\n");

	अगर (error) अणु
		new_state = HST_ERROR;
		जाओ out;
	पूर्ण

	/* TODO: scan and support non-disk devices */
	क्रम (i = 0; i < 8; i++)
		अगर (msg_data[i] == 0) अणु /* direct-access device (disk) */
			host->dev_present |= (1 << i);
			dev_count++;
		पूर्ण

	prपूर्णांकk(KERN_INFO DRV_NAME "(%s): found %u interesting devices\n",
	       pci_name(host->pdev), dev_count);

out:
	निश्चित(host->state == HST_PORT_SCAN);
	host->state = new_state;
	schedule_work(&host->fsm_task);
पूर्ण

अटल व्योम carm_handle_generic(काष्ठा carm_host *host,
				काष्ठा carm_request *crq, blk_status_t error,
				पूर्णांक cur_state, पूर्णांक next_state)
अणु
	DPRINTK("ENTER\n");

	निश्चित(host->state == cur_state);
	अगर (error)
		host->state = HST_ERROR;
	अन्यथा
		host->state = next_state;
	schedule_work(&host->fsm_task);
पूर्ण

अटल अंतरभूत व्योम carm_handle_resp(काष्ठा carm_host *host,
				    __le32 ret_handle_le, u32 status)
अणु
	u32 handle = le32_to_cpu(ret_handle_le);
	अचिन्हित पूर्णांक msg_idx;
	काष्ठा request *rq;
	काष्ठा carm_request *crq;
	blk_status_t error = (status == RMSG_OK) ? 0 : BLK_STS_IOERR;
	u8 *mem;

	VPRINTK("ENTER, handle == 0x%x\n", handle);

	अगर (unlikely(!TAG_VALID(handle))) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): BUG: invalid tag 0x%x\n",
		       pci_name(host->pdev), handle);
		वापस;
	पूर्ण

	msg_idx = TAG_DECODE(handle);
	VPRINTK("tag == %u\n", msg_idx);

	rq = blk_mq_tag_to_rq(host->tag_set.tags[0], msg_idx);
	crq = blk_mq_rq_to_pdu(rq);

	/* fast path */
	अगर (likely(crq->msg_type == CARM_MSG_READ ||
		   crq->msg_type == CARM_MSG_WRITE)) अणु
		dma_unmap_sg(&host->pdev->dev, &crq->sg[0], crq->n_elem,
			     carm_rq_dir(rq));
		जाओ करोne;
	पूर्ण

	mem = carm_ref_msg(host, msg_idx);

	चयन (crq->msg_type) अणु
	हाल CARM_MSG_IOCTL: अणु
		चयन (crq->msg_subtype) अणु
		हाल CARM_IOC_SCAN_CHAN:
			carm_handle_scan_chan(host, crq, mem, error);
			जाओ करोne;
		शेष:
			/* unknown / invalid response */
			जाओ err_out;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल CARM_MSG_MISC: अणु
		चयन (crq->msg_subtype) अणु
		हाल MISC_ALLOC_MEM:
			carm_handle_generic(host, crq, error,
					    HST_ALLOC_BUF, HST_SYNC_TIME);
			जाओ करोne;
		हाल MISC_SET_TIME:
			carm_handle_generic(host, crq, error,
					    HST_SYNC_TIME, HST_GET_FW_VER);
			जाओ करोne;
		हाल MISC_GET_FW_VER: अणु
			काष्ठा carm_fw_ver *ver = (काष्ठा carm_fw_ver *)
				(mem + माप(काष्ठा carm_msg_get_fw_ver));
			अगर (!error) अणु
				host->fw_ver = le32_to_cpu(ver->version);
				host->flags |= (ver->features & FL_FW_VER_MASK);
			पूर्ण
			carm_handle_generic(host, crq, error,
					    HST_GET_FW_VER, HST_PORT_SCAN);
			जाओ करोne;
		पूर्ण
		शेष:
			/* unknown / invalid response */
			जाओ err_out;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल CARM_MSG_ARRAY: अणु
		चयन (crq->msg_subtype) अणु
		हाल CARM_ARRAY_INFO:
			carm_handle_array_info(host, crq, mem, error);
			अवरोध;
		शेष:
			/* unknown / invalid response */
			जाओ err_out;
		पूर्ण
		अवरोध;
	पूर्ण

	शेष:
		/* unknown / invalid response */
		जाओ err_out;
	पूर्ण

	वापस;

err_out:
	prपूर्णांकk(KERN_WARNING DRV_NAME "(%s): BUG: unhandled message type %d/%d\n",
	       pci_name(host->pdev), crq->msg_type, crq->msg_subtype);
	error = BLK_STS_IOERR;
करोne:
	host->hw_sg_used -= crq->n_elem;
	blk_mq_end_request(blk_mq_rq_from_pdu(crq), error);

	अगर (host->hw_sg_used <= CARM_SG_LOW_WATER)
		carm_round_robin(host);
पूर्ण

अटल अंतरभूत व्योम carm_handle_responses(काष्ठा carm_host *host)
अणु
	व्योम __iomem *mmio = host->mmio;
	काष्ठा carm_response *resp = (काष्ठा carm_response *) host->shm;
	अचिन्हित पूर्णांक work = 0;
	अचिन्हित पूर्णांक idx = host->resp_idx % RMSG_Q_LEN;

	जबतक (1) अणु
		u32 status = le32_to_cpu(resp[idx].status);

		अगर (status == 0xffffffff) अणु
			VPRINTK("ending response on index %u\n", idx);
			ग_लिखोl(idx << 3, mmio + CARM_RESP_IDX);
			अवरोध;
		पूर्ण

		/* response to a message we sent */
		अन्यथा अगर ((status & (1 << 31)) == 0) अणु
			VPRINTK("handling msg response on index %u\n", idx);
			carm_handle_resp(host, resp[idx].ret_handle, status);
			resp[idx].status = cpu_to_le32(0xffffffff);
		पूर्ण

		/* asynchronous events the hardware throws our way */
		अन्यथा अगर ((status & 0xff000000) == (1 << 31)) अणु
			u8 *evt_type_ptr = (u8 *) &resp[idx];
			u8 evt_type = *evt_type_ptr;
			prपूर्णांकk(KERN_WARNING DRV_NAME "(%s): unhandled event type %d\n",
			       pci_name(host->pdev), (पूर्णांक) evt_type);
			resp[idx].status = cpu_to_le32(0xffffffff);
		पूर्ण

		idx = NEXT_RESP(idx);
		work++;
	पूर्ण

	VPRINTK("EXIT, work==%u\n", work);
	host->resp_idx += work;
पूर्ण

अटल irqवापस_t carm_पूर्णांकerrupt(पूर्णांक irq, व्योम *__host)
अणु
	काष्ठा carm_host *host = __host;
	व्योम __iomem *mmio;
	u32 mask;
	पूर्णांक handled = 0;
	अचिन्हित दीर्घ flags;

	अगर (!host) अणु
		VPRINTK("no host\n");
		वापस IRQ_NONE;
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);

	mmio = host->mmio;

	/* पढ़ोing should also clear पूर्णांकerrupts */
	mask = पढ़ोl(mmio + CARM_INT_STAT);

	अगर (mask == 0 || mask == 0xffffffff) अणु
		VPRINTK("no work, mask == 0x%x\n", mask);
		जाओ out;
	पूर्ण

	अगर (mask & INT_ACK_MASK)
		ग_लिखोl(mask, mmio + CARM_INT_STAT);

	अगर (unlikely(host->state == HST_INVALID)) अणु
		VPRINTK("not initialized yet, mask = 0x%x\n", mask);
		जाओ out;
	पूर्ण

	अगर (mask & CARM_HAVE_RESP) अणु
		handled = 1;
		carm_handle_responses(host);
	पूर्ण

out:
	spin_unlock_irqrestore(&host->lock, flags);
	VPRINTK("EXIT\n");
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम carm_fsm_task (काष्ठा work_काष्ठा *work)
अणु
	काष्ठा carm_host *host =
		container_of(work, काष्ठा carm_host, fsm_task);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक state;
	पूर्णांक rc, i, next_dev;
	पूर्णांक reschedule = 0;
	पूर्णांक new_state = HST_INVALID;

	spin_lock_irqsave(&host->lock, flags);
	state = host->state;
	spin_unlock_irqrestore(&host->lock, flags);

	DPRINTK("ENTER, state == %s\n", state_name[state]);

	चयन (state) अणु
	हाल HST_PROBE_START:
		new_state = HST_ALLOC_BUF;
		reschedule = 1;
		अवरोध;

	हाल HST_ALLOC_BUF:
		rc = carm_send_special(host, carm_fill_alloc_buf);
		अगर (rc) अणु
			new_state = HST_ERROR;
			reschedule = 1;
		पूर्ण
		अवरोध;

	हाल HST_SYNC_TIME:
		rc = carm_send_special(host, carm_fill_sync_समय);
		अगर (rc) अणु
			new_state = HST_ERROR;
			reschedule = 1;
		पूर्ण
		अवरोध;

	हाल HST_GET_FW_VER:
		rc = carm_send_special(host, carm_fill_get_fw_ver);
		अगर (rc) अणु
			new_state = HST_ERROR;
			reschedule = 1;
		पूर्ण
		अवरोध;

	हाल HST_PORT_SCAN:
		rc = carm_send_special(host, carm_fill_scan_channels);
		अगर (rc) अणु
			new_state = HST_ERROR;
			reschedule = 1;
		पूर्ण
		अवरोध;

	हाल HST_DEV_SCAN_START:
		host->cur_scan_dev = -1;
		new_state = HST_DEV_SCAN;
		reschedule = 1;
		अवरोध;

	हाल HST_DEV_SCAN:
		next_dev = -1;
		क्रम (i = host->cur_scan_dev + 1; i < CARM_MAX_PORTS; i++)
			अगर (host->dev_present & (1 << i)) अणु
				next_dev = i;
				अवरोध;
			पूर्ण

		अगर (next_dev >= 0) अणु
			host->cur_scan_dev = next_dev;
			rc = carm_array_info(host, next_dev);
			अगर (rc) अणु
				new_state = HST_ERROR;
				reschedule = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			new_state = HST_DEV_ACTIVATE;
			reschedule = 1;
		पूर्ण
		अवरोध;

	हाल HST_DEV_ACTIVATE: अणु
		पूर्णांक activated = 0;
		क्रम (i = 0; i < CARM_MAX_PORTS; i++)
			अगर (host->dev_active & (1 << i)) अणु
				काष्ठा carm_port *port = &host->port[i];
				काष्ठा gendisk *disk = port->disk;

				set_capacity(disk, port->capacity);
				add_disk(disk);
				activated++;
			पूर्ण

		prपूर्णांकk(KERN_INFO DRV_NAME "(%s): %d ports activated\n",
		       pci_name(host->pdev), activated);

		new_state = HST_PROBE_FINISHED;
		reschedule = 1;
		अवरोध;
	पूर्ण

	हाल HST_PROBE_FINISHED:
		complete(&host->probe_comp);
		अवरोध;

	हाल HST_ERROR:
		/* FIXME: TODO */
		अवरोध;

	शेष:
		/* should never occur */
		prपूर्णांकk(KERN_ERR PFX "BUG: unknown state %d\n", state);
		निश्चित(0);
		अवरोध;
	पूर्ण

	अगर (new_state != HST_INVALID) अणु
		spin_lock_irqsave(&host->lock, flags);
		host->state = new_state;
		spin_unlock_irqrestore(&host->lock, flags);
	पूर्ण
	अगर (reschedule)
		schedule_work(&host->fsm_task);
पूर्ण

अटल पूर्णांक carm_init_रुको(व्योम __iomem *mmio, u32 bits, अचिन्हित पूर्णांक test_bit)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 50000; i++) अणु
		u32 पंचांगp = पढ़ोl(mmio + CARM_LMUC);
		udelay(100);

		अगर (test_bit) अणु
			अगर ((पंचांगp & bits) == bits)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर ((पंचांगp & bits) == 0)
				वापस 0;
		पूर्ण

		cond_resched();
	पूर्ण

	prपूर्णांकk(KERN_ERR PFX "carm_init_wait timeout, bits == 0x%x, test_bit == %s\n",
	       bits, test_bit ? "yes" : "no");
	वापस -EBUSY;
पूर्ण

अटल व्योम carm_init_responses(काष्ठा carm_host *host)
अणु
	व्योम __iomem *mmio = host->mmio;
	अचिन्हित पूर्णांक i;
	काष्ठा carm_response *resp = (काष्ठा carm_response *) host->shm;

	क्रम (i = 0; i < RMSG_Q_LEN; i++)
		resp[i].status = cpu_to_le32(0xffffffff);

	ग_लिखोl(0, mmio + CARM_RESP_IDX);
पूर्ण

अटल पूर्णांक carm_init_host(काष्ठा carm_host *host)
अणु
	व्योम __iomem *mmio = host->mmio;
	u32 पंचांगp;
	u8 पंचांगp8;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	ग_लिखोl(0, mmio + CARM_INT_MASK);

	पंचांगp8 = पढ़ोb(mmio + CARM_INITC);
	अगर (पंचांगp8 & 0x01) अणु
		पंचांगp8 &= ~0x01;
		ग_लिखोb(पंचांगp8, mmio + CARM_INITC);
		पढ़ोb(mmio + CARM_INITC);	/* flush */

		DPRINTK("snooze...\n");
		msleep(5000);
	पूर्ण

	पंचांगp = पढ़ोl(mmio + CARM_HMUC);
	अगर (पंचांगp & CARM_CME) अणु
		DPRINTK("CME bit present, waiting\n");
		rc = carm_init_रुको(mmio, CARM_CME, 1);
		अगर (rc) अणु
			DPRINTK("EXIT, carm_init_wait 1 failed\n");
			वापस rc;
		पूर्ण
	पूर्ण
	अगर (पंचांगp & CARM_RME) अणु
		DPRINTK("RME bit present, waiting\n");
		rc = carm_init_रुको(mmio, CARM_RME, 1);
		अगर (rc) अणु
			DPRINTK("EXIT, carm_init_wait 2 failed\n");
			वापस rc;
		पूर्ण
	पूर्ण

	पंचांगp &= ~(CARM_RME | CARM_CME);
	ग_लिखोl(पंचांगp, mmio + CARM_HMUC);
	पढ़ोl(mmio + CARM_HMUC);	/* flush */

	rc = carm_init_रुको(mmio, CARM_RME | CARM_CME, 0);
	अगर (rc) अणु
		DPRINTK("EXIT, carm_init_wait 3 failed\n");
		वापस rc;
	पूर्ण

	carm_init_buckets(mmio);

	ग_लिखोl(host->shm_dma & 0xffffffff, mmio + RBUF_ADDR_LO);
	ग_लिखोl((host->shm_dma >> 16) >> 16, mmio + RBUF_ADDR_HI);
	ग_लिखोl(RBUF_LEN, mmio + RBUF_BYTE_SZ);

	पंचांगp = पढ़ोl(mmio + CARM_HMUC);
	पंचांगp |= (CARM_RME | CARM_CME | CARM_WZBC);
	ग_लिखोl(पंचांगp, mmio + CARM_HMUC);
	पढ़ोl(mmio + CARM_HMUC);	/* flush */

	rc = carm_init_रुको(mmio, CARM_RME | CARM_CME, 1);
	अगर (rc) अणु
		DPRINTK("EXIT, carm_init_wait 4 failed\n");
		वापस rc;
	पूर्ण

	ग_लिखोl(0, mmio + CARM_HMPHA);
	ग_लिखोl(INT_DEF_MASK, mmio + CARM_INT_MASK);

	carm_init_responses(host);

	/* start initialization, probing state machine */
	spin_lock_irq(&host->lock);
	निश्चित(host->state == HST_INVALID);
	host->state = HST_PROBE_START;
	spin_unlock_irq(&host->lock);
	schedule_work(&host->fsm_task);

	DPRINTK("EXIT\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops carm_mq_ops = अणु
	.queue_rq	= carm_queue_rq,
पूर्ण;

अटल पूर्णांक carm_init_disk(काष्ठा carm_host *host, अचिन्हित पूर्णांक port_no)
अणु
	काष्ठा carm_port *port = &host->port[port_no];
	काष्ठा gendisk *disk;
	काष्ठा request_queue *q;

	port->host = host;
	port->port_no = port_no;

	disk = alloc_disk(CARM_MINORS_PER_MAJOR);
	अगर (!disk)
		वापस -ENOMEM;

	port->disk = disk;
	प्र_लिखो(disk->disk_name, DRV_NAME "/%u",
		(अचिन्हित पूर्णांक)host->id * CARM_MAX_PORTS + port_no);
	disk->major = host->major;
	disk->first_minor = port_no * CARM_MINORS_PER_MAJOR;
	disk->fops = &carm_bd_ops;
	disk->निजी_data = port;

	q = blk_mq_init_queue(&host->tag_set);
	अगर (IS_ERR(q))
		वापस PTR_ERR(q);

	blk_queue_max_segments(q, CARM_MAX_REQ_SG);
	blk_queue_segment_boundary(q, CARM_SG_BOUNDARY);

	q->queuedata = port;
	disk->queue = q;
	वापस 0;
पूर्ण

अटल व्योम carm_मुक्त_disk(काष्ठा carm_host *host, अचिन्हित पूर्णांक port_no)
अणु
	काष्ठा carm_port *port = &host->port[port_no];
	काष्ठा gendisk *disk = port->disk;

	अगर (!disk)
		वापस;

	अगर (disk->flags & GENHD_FL_UP)
		del_gendisk(disk);
	अगर (disk->queue)
		blk_cleanup_queue(disk->queue);
	put_disk(disk);
पूर्ण

अटल पूर्णांक carm_init_shm(काष्ठा carm_host *host)
अणु
	host->shm = dma_alloc_coherent(&host->pdev->dev, CARM_SHM_SIZE,
				       &host->shm_dma, GFP_KERNEL);
	अगर (!host->shm)
		वापस -ENOMEM;

	host->msg_base = host->shm + RBUF_LEN;
	host->msg_dma = host->shm_dma + RBUF_LEN;

	स_रखो(host->shm, 0xff, RBUF_LEN);
	स_रखो(host->msg_base, 0, PDC_SHM_SIZE - RBUF_LEN);

	वापस 0;
पूर्ण

अटल पूर्णांक carm_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा carm_host *host;
	पूर्णांक rc;
	काष्ठा request_queue *q;
	अचिन्हित पूर्णांक i;

	prपूर्णांकk_once(KERN_DEBUG DRV_NAME " version " DRV_VERSION "\n");

	rc = pci_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out;

	rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): DMA mask failure\n",
			pci_name(pdev));
		जाओ err_out_regions;
	पूर्ण

	host = kzalloc(माप(*host), GFP_KERNEL);
	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): memory alloc failure\n",
		       pci_name(pdev));
		rc = -ENOMEM;
		जाओ err_out_regions;
	पूर्ण

	host->pdev = pdev;
	spin_lock_init(&host->lock);
	INIT_WORK(&host->fsm_task, carm_fsm_task);
	init_completion(&host->probe_comp);

	host->mmio = ioremap(pci_resource_start(pdev, 0),
			     pci_resource_len(pdev, 0));
	अगर (!host->mmio) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): MMIO alloc failure\n",
		       pci_name(pdev));
		rc = -ENOMEM;
		जाओ err_out_kमुक्त;
	पूर्ण

	rc = carm_init_shm(host);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): DMA SHM alloc failure\n",
		       pci_name(pdev));
		जाओ err_out_iounmap;
	पूर्ण

	स_रखो(&host->tag_set, 0, माप(host->tag_set));
	host->tag_set.ops = &carm_mq_ops;
	host->tag_set.cmd_size = माप(काष्ठा carm_request);
	host->tag_set.nr_hw_queues = 1;
	host->tag_set.nr_maps = 1;
	host->tag_set.queue_depth = max_queue;
	host->tag_set.numa_node = NUMA_NO_NODE;
	host->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;

	rc = blk_mq_alloc_tag_set(&host->tag_set);
	अगर (rc)
		जाओ err_out_dma_मुक्त;

	q = blk_mq_init_queue(&host->tag_set);
	अगर (IS_ERR(q)) अणु
		rc = PTR_ERR(q);
		blk_mq_मुक्त_tag_set(&host->tag_set);
		जाओ err_out_dma_मुक्त;
	पूर्ण

	host->oob_q = q;
	q->queuedata = host;

	/*
	 * Figure out which major to use: 160, 161, or dynamic
	 */
	अगर (!test_and_set_bit(0, &carm_major_alloc))
		host->major = 160;
	अन्यथा अगर (!test_and_set_bit(1, &carm_major_alloc))
		host->major = 161;
	अन्यथा
		host->flags |= FL_DYN_MAJOR;

	host->id = carm_host_id;
	प्र_लिखो(host->name, DRV_NAME "%d", carm_host_id);

	rc = रेजिस्टर_blkdev(host->major, host->name);
	अगर (rc < 0)
		जाओ err_out_मुक्त_majors;
	अगर (host->flags & FL_DYN_MAJOR)
		host->major = rc;

	क्रम (i = 0; i < CARM_MAX_PORTS; i++) अणु
		rc = carm_init_disk(host, i);
		अगर (rc)
			जाओ err_out_blkdev_disks;
	पूर्ण

	pci_set_master(pdev);

	rc = request_irq(pdev->irq, carm_पूर्णांकerrupt, IRQF_SHARED, DRV_NAME, host);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME "(%s): irq alloc failure\n",
		       pci_name(pdev));
		जाओ err_out_blkdev_disks;
	पूर्ण

	rc = carm_init_host(host);
	अगर (rc)
		जाओ err_out_मुक्त_irq;

	DPRINTK("waiting for probe_comp\n");
	रुको_क्रम_completion(&host->probe_comp);

	prपूर्णांकk(KERN_INFO "%s: pci %s, ports %d, io %llx, irq %u, major %d\n",
	       host->name, pci_name(pdev), (पूर्णांक) CARM_MAX_PORTS,
	       (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0),
		   pdev->irq, host->major);

	carm_host_id++;
	pci_set_drvdata(pdev, host);
	वापस 0;

err_out_मुक्त_irq:
	मुक्त_irq(pdev->irq, host);
err_out_blkdev_disks:
	क्रम (i = 0; i < CARM_MAX_PORTS; i++)
		carm_मुक्त_disk(host, i);
	unरेजिस्टर_blkdev(host->major, host->name);
err_out_मुक्त_majors:
	अगर (host->major == 160)
		clear_bit(0, &carm_major_alloc);
	अन्यथा अगर (host->major == 161)
		clear_bit(1, &carm_major_alloc);
	blk_cleanup_queue(host->oob_q);
	blk_mq_मुक्त_tag_set(&host->tag_set);
err_out_dma_मुक्त:
	dma_मुक्त_coherent(&pdev->dev, CARM_SHM_SIZE, host->shm, host->shm_dma);
err_out_iounmap:
	iounmap(host->mmio);
err_out_kमुक्त:
	kमुक्त(host);
err_out_regions:
	pci_release_regions(pdev);
err_out:
	pci_disable_device(pdev);
	वापस rc;
पूर्ण

अटल व्योम carm_हटाओ_one (काष्ठा pci_dev *pdev)
अणु
	काष्ठा carm_host *host = pci_get_drvdata(pdev);
	अचिन्हित पूर्णांक i;

	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR PFX "BUG: no host data for PCI(%s)\n",
		       pci_name(pdev));
		वापस;
	पूर्ण

	मुक्त_irq(pdev->irq, host);
	क्रम (i = 0; i < CARM_MAX_PORTS; i++)
		carm_मुक्त_disk(host, i);
	unरेजिस्टर_blkdev(host->major, host->name);
	अगर (host->major == 160)
		clear_bit(0, &carm_major_alloc);
	अन्यथा अगर (host->major == 161)
		clear_bit(1, &carm_major_alloc);
	blk_cleanup_queue(host->oob_q);
	blk_mq_मुक्त_tag_set(&host->tag_set);
	dma_मुक्त_coherent(&pdev->dev, CARM_SHM_SIZE, host->shm, host->shm_dma);
	iounmap(host->mmio);
	kमुक्त(host);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

module_pci_driver(carm_driver);
