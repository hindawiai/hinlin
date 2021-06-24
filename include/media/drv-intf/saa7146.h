<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SAA7146__
#घोषणा __SAA7146__

#समावेश <linux/delay.h>	/* क्रम delay-stuff */
#समावेश <linux/slab.h>		/* क्रम kदो_स्मृति/kमुक्त */
#समावेश <linux/pci.h>		/* क्रम pci-config-stuff, venकरोr ids etc. */
#समावेश <linux/init.h>		/* क्रम "__init" */
#समावेश <linux/पूर्णांकerrupt.h>	/* क्रम IMMEDIATE_BH */
#समावेश <linux/kmod.h>		/* क्रम kernel module loader */
#समावेश <linux/i2c.h>		/* क्रम i2c subप्रणाली */
#समावेश <यंत्र/पन.स>		/* क्रम accessing devices */
#समावेश <linux/stringअगरy.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश <linux/vदो_स्मृति.h>	/* क्रम vदो_स्मृति() */
#समावेश <linux/mm.h>		/* क्रम vदो_स्मृति_to_page() */

#घोषणा saa7146_ग_लिखो(sxy,adr,dat)    ग_लिखोl((dat),(sxy->mem+(adr)))
#घोषणा saa7146_पढ़ो(sxy,adr)         पढ़ोl(sxy->mem+(adr))

बाह्य अचिन्हित पूर्णांक saa7146_debug;

#अगर_अघोषित DEBUG_VARIABLE
	#घोषणा DEBUG_VARIABLE saa7146_debug
#पूर्ण_अगर

#घोषणा ERR(fmt, ...)	pr_err("%s: " fmt, __func__, ##__VA_ARGS__)

#घोषणा _DBG(mask, fmt, ...)						\
करो अणु									\
	अगर (DEBUG_VARIABLE & mask)					\
		pr_debug("%s(): " fmt, __func__, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

/* simple debug messages */
#घोषणा DEB_S(fmt, ...)		_DBG(0x01, fmt, ##__VA_ARGS__)
/* more detailed debug messages */
#घोषणा DEB_D(fmt, ...)		_DBG(0x02, fmt, ##__VA_ARGS__)
/* prपूर्णांक enter and निकास of functions */
#घोषणा DEB_EE(fmt, ...)	_DBG(0x04, fmt, ##__VA_ARGS__)
/* i2c debug messages */
#घोषणा DEB_I2C(fmt, ...)	_DBG(0x08, fmt, ##__VA_ARGS__)
/* vbi debug messages */
#घोषणा DEB_VBI(fmt, ...)	_DBG(0x10, fmt, ##__VA_ARGS__)
/* पूर्णांकerrupt debug messages */
#घोषणा DEB_INT(fmt, ...)	_DBG(0x20, fmt, ##__VA_ARGS__)
/* capture debug messages */
#घोषणा DEB_CAP(fmt, ...)	_DBG(0x40, fmt, ##__VA_ARGS__)

#घोषणा SAA7146_ISR_CLEAR(x,y) \
	saa7146_ग_लिखो(x, ISR, (y));

काष्ठा module;

काष्ठा saa7146_dev;
काष्ठा saa7146_extension;
काष्ठा saa7146_vv;

/* saa7146 page table */
काष्ठा saa7146_pgtable अणु
	अचिन्हित पूर्णांक	size;
	__le32		*cpu;
	dma_addr_t	dma;
	/* used क्रम offsets क्रम u,v planes क्रम planar capture modes */
	अचिन्हित दीर्घ	offset;
	/* used क्रम custom pagetables (used क्रम example by budget dvb cards) */
	काष्ठा scatterlist *slist;
	पूर्णांक		nents;
पूर्ण;

काष्ठा saa7146_pci_extension_data अणु
	काष्ठा saa7146_extension *ext;
	व्योम *ext_priv;			/* most likely a name string */
पूर्ण;

#घोषणा MAKE_EXTENSION_PCI(x_var, x_venकरोr, x_device)		\
	अणु							\
		.venकरोr    = PCI_VENDOR_ID_PHILIPS,		\
		.device	   = PCI_DEVICE_ID_PHILIPS_SAA7146,	\
		.subvenकरोr = x_venकरोr,				\
		.subdevice = x_device,				\
		.driver_data = (अचिन्हित दीर्घ)& x_var,		\
	पूर्ण

काष्ठा saa7146_extension
अणु
	अक्षर	name[32];		/* name of the device */
#घोषणा SAA7146_USE_I2C_IRQ	0x1
#घोषणा SAA7146_I2C_SHORT_DELAY	0x2
	पूर्णांक	flags;

	/* pairs of subvenकरोr and subdevice ids क्रम
	   supported devices, last entry 0xffff, 0xfff */
	काष्ठा module *module;
	काष्ठा pci_driver driver;
	स्थिर काष्ठा pci_device_id *pci_tbl;

	/* extension functions */
	पूर्णांक (*probe)(काष्ठा saa7146_dev *);
	पूर्णांक (*attach)(काष्ठा saa7146_dev *, काष्ठा saa7146_pci_extension_data *);
	पूर्णांक (*detach)(काष्ठा saa7146_dev*);

	u32	irq_mask;	/* mask to indicate, which irq-events are handled by the extension */
	व्योम	(*irq_func)(काष्ठा saa7146_dev*, u32* irq_mask);
पूर्ण;

काष्ठा saa7146_dma
अणु
	dma_addr_t	dma_handle;
	__le32		*cpu_addr;
पूर्ण;

काष्ठा saa7146_dev
अणु
	काष्ठा module			*module;

	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_handler;

	/* dअगरferent device locks */
	spinlock_t			slock;
	काष्ठा mutex			v4l2_lock;

	अचिन्हित अक्षर			__iomem *mem;		/* poपूर्णांकer to mapped IO memory */
	u32				revision;	/* chip revision; needed क्रम bug-workarounds*/

	/* pci-device & irq stuff*/
	अक्षर				name[32];
	काष्ठा pci_dev			*pci;
	u32				पूर्णांक_toकरो;
	spinlock_t			पूर्णांक_slock;

	/* extension handling */
	काष्ठा saa7146_extension	*ext;		/* indicates अगर handled by extension */
	व्योम				*ext_priv;	/* poपूर्णांकer क्रम extension निजी use (most likely some निजी data) */
	काष्ठा saa7146_ext_vv		*ext_vv_data;

	/* per device video/vbi inक्रमmation (अगर available) */
	काष्ठा saa7146_vv	*vv_data;
	व्योम (*vv_callback)(काष्ठा saa7146_dev *dev, अचिन्हित दीर्घ status);

	/* i2c-stuff */
	काष्ठा mutex			i2c_lock;

	u32				i2c_bitrate;
	काष्ठा saa7146_dma		d_i2c;	/* poपूर्णांकer to i2c memory */
	रुको_queue_head_t		i2c_wq;
	पूर्णांक				i2c_op;

	/* memories */
	काष्ठा saa7146_dma		d_rps0;
	काष्ठा saa7146_dma		d_rps1;
पूर्ण;

अटल अंतरभूत काष्ठा saa7146_dev *to_saa7146_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा saa7146_dev, v4l2_dev);
पूर्ण

/* from saa7146_i2c.c */
पूर्णांक saa7146_i2c_adapter_prepare(काष्ठा saa7146_dev *dev, काष्ठा i2c_adapter *i2c_adapter, u32 bitrate);

/* from saa7146_core.c */
पूर्णांक saa7146_रेजिस्टर_extension(काष्ठा saa7146_extension*);
पूर्णांक saa7146_unरेजिस्टर_extension(काष्ठा saa7146_extension*);
काष्ठा saa7146_क्रमmat* saa7146_क्रमmat_by_fourcc(काष्ठा saa7146_dev *dev, पूर्णांक fourcc);
पूर्णांक saa7146_pgtable_alloc(काष्ठा pci_dev *pci, काष्ठा saa7146_pgtable *pt);
व्योम saa7146_pgtable_मुक्त(काष्ठा pci_dev *pci, काष्ठा saa7146_pgtable *pt);
पूर्णांक saa7146_pgtable_build_single(काष्ठा pci_dev *pci, काष्ठा saa7146_pgtable *pt, काष्ठा scatterlist *list, पूर्णांक length );
व्योम *saa7146_vदो_स्मृति_build_pgtable(काष्ठा pci_dev *pci, दीर्घ length, काष्ठा saa7146_pgtable *pt);
व्योम saa7146_vमुक्त_destroy_pgtable(काष्ठा pci_dev *pci, व्योम *mem, काष्ठा saa7146_pgtable *pt);
व्योम saa7146_setgpio(काष्ठा saa7146_dev *dev, पूर्णांक port, u32 data);
पूर्णांक saa7146_रुको_क्रम_debi_करोne(काष्ठा saa7146_dev *dev, पूर्णांक nobusyloop);

/* some memory sizes */
#घोषणा SAA7146_I2C_MEM		( 1*PAGE_SIZE)
#घोषणा SAA7146_RPS_MEM		( 1*PAGE_SIZE)

/* some i2c स्थिरants */
#घोषणा SAA7146_I2C_TIMEOUT	100	/* i2c-समयout-value in ms */
#घोषणा SAA7146_I2C_RETRIES	3	/* how many बार shall we retry an i2c-operation? */
#घोषणा SAA7146_I2C_DELAY	5	/* समय we रुको after certain i2c-operations */

/* unsorted defines */
#घोषणा ME1    0x0000000800
#घोषणा PV1    0x0000000008

/* gpio defines */
#घोषणा SAA7146_GPIO_INPUT 0x00
#घोषणा SAA7146_GPIO_IRQHI 0x10
#घोषणा SAA7146_GPIO_IRQLO 0x20
#घोषणा SAA7146_GPIO_IRQHL 0x30
#घोषणा SAA7146_GPIO_OUTLO 0x40
#घोषणा SAA7146_GPIO_OUTHI 0x50

/* debi defines */
#घोषणा DEBINOSWAP 0x000e0000

/* define क्रम the रेजिस्टर programming sequencer (rps) */
#घोषणा CMD_NOP		0x00000000  /* No operation */
#घोषणा CMD_CLR_EVENT	0x00000000  /* Clear event */
#घोषणा CMD_SET_EVENT	0x10000000  /* Set संकेत event */
#घोषणा CMD_PAUSE	0x20000000  /* Pause */
#घोषणा CMD_CHECK_LATE	0x30000000  /* Check late */
#घोषणा CMD_UPLOAD	0x40000000  /* Upload */
#घोषणा CMD_STOP	0x50000000  /* Stop */
#घोषणा CMD_INTERRUPT	0x60000000  /* Interrupt */
#घोषणा CMD_JUMP	0x80000000  /* Jump */
#घोषणा CMD_WR_REG	0x90000000  /* Write (load) रेजिस्टर */
#घोषणा CMD_RD_REG	0xa0000000  /* Read (store) रेजिस्टर */
#घोषणा CMD_WR_REG_MASK	0xc0000000  /* Write रेजिस्टर with mask */

#घोषणा CMD_OAN		MASK_27
#घोषणा CMD_INV		MASK_26
#घोषणा CMD_SIG4	MASK_25
#घोषणा CMD_SIG3	MASK_24
#घोषणा CMD_SIG2	MASK_23
#घोषणा CMD_SIG1	MASK_22
#घोषणा CMD_SIG0	MASK_21
#घोषणा CMD_O_FID_B	MASK_14
#घोषणा CMD_E_FID_B	MASK_13
#घोषणा CMD_O_FID_A	MASK_12
#घोषणा CMD_E_FID_A	MASK_11

/* some events and command modअगरiers क्रम rps1 squarewave generator */
#घोषणा EVT_HS          (1<<15)     // Source Line Threshold reached
#घोषणा EVT_VBI_B       (1<<9)      // VSYNC Event
#घोषणा RPS_OAN         (1<<27)     // 1: OR events, 0: AND events
#घोषणा RPS_INV         (1<<26)     // Invert (compound) event
#घोषणा GPIO3_MSK       0xFF000000  // GPIO #3 control bits

/* Bit mask स्थिरants */
#घोषणा MASK_00   0x00000001    /* Mask value क्रम bit 0 */
#घोषणा MASK_01   0x00000002    /* Mask value क्रम bit 1 */
#घोषणा MASK_02   0x00000004    /* Mask value क्रम bit 2 */
#घोषणा MASK_03   0x00000008    /* Mask value क्रम bit 3 */
#घोषणा MASK_04   0x00000010    /* Mask value क्रम bit 4 */
#घोषणा MASK_05   0x00000020    /* Mask value क्रम bit 5 */
#घोषणा MASK_06   0x00000040    /* Mask value क्रम bit 6 */
#घोषणा MASK_07   0x00000080    /* Mask value क्रम bit 7 */
#घोषणा MASK_08   0x00000100    /* Mask value क्रम bit 8 */
#घोषणा MASK_09   0x00000200    /* Mask value क्रम bit 9 */
#घोषणा MASK_10   0x00000400    /* Mask value क्रम bit 10 */
#घोषणा MASK_11   0x00000800    /* Mask value क्रम bit 11 */
#घोषणा MASK_12   0x00001000    /* Mask value क्रम bit 12 */
#घोषणा MASK_13   0x00002000    /* Mask value क्रम bit 13 */
#घोषणा MASK_14   0x00004000    /* Mask value क्रम bit 14 */
#घोषणा MASK_15   0x00008000    /* Mask value क्रम bit 15 */
#घोषणा MASK_16   0x00010000    /* Mask value क्रम bit 16 */
#घोषणा MASK_17   0x00020000    /* Mask value क्रम bit 17 */
#घोषणा MASK_18   0x00040000    /* Mask value क्रम bit 18 */
#घोषणा MASK_19   0x00080000    /* Mask value क्रम bit 19 */
#घोषणा MASK_20   0x00100000    /* Mask value क्रम bit 20 */
#घोषणा MASK_21   0x00200000    /* Mask value क्रम bit 21 */
#घोषणा MASK_22   0x00400000    /* Mask value क्रम bit 22 */
#घोषणा MASK_23   0x00800000    /* Mask value क्रम bit 23 */
#घोषणा MASK_24   0x01000000    /* Mask value क्रम bit 24 */
#घोषणा MASK_25   0x02000000    /* Mask value क्रम bit 25 */
#घोषणा MASK_26   0x04000000    /* Mask value क्रम bit 26 */
#घोषणा MASK_27   0x08000000    /* Mask value क्रम bit 27 */
#घोषणा MASK_28   0x10000000    /* Mask value क्रम bit 28 */
#घोषणा MASK_29   0x20000000    /* Mask value क्रम bit 29 */
#घोषणा MASK_30   0x40000000    /* Mask value क्रम bit 30 */
#घोषणा MASK_31   0x80000000    /* Mask value क्रम bit 31 */

#घोषणा MASK_B0   0x000000ff    /* Mask value क्रम byte 0 */
#घोषणा MASK_B1   0x0000ff00    /* Mask value क्रम byte 1 */
#घोषणा MASK_B2   0x00ff0000    /* Mask value क्रम byte 2 */
#घोषणा MASK_B3   0xff000000    /* Mask value क्रम byte 3 */

#घोषणा MASK_W0   0x0000ffff    /* Mask value क्रम word 0 */
#घोषणा MASK_W1   0xffff0000    /* Mask value क्रम word 1 */

#घोषणा MASK_PA   0xfffffffc    /* Mask value क्रम physical address */
#घोषणा MASK_PR   0xfffffffe	/* Mask value क्रम protection रेजिस्टर */
#घोषणा MASK_ER   0xffffffff    /* Mask value क्रम the entire रेजिस्टर */

#घोषणा MASK_NONE 0x00000000    /* No mask */

/* रेजिस्टर aliases */
#घोषणा BASE_ODD1         0x00  /* Video DMA 1 रेजिस्टरs  */
#घोषणा BASE_EVEN1        0x04
#घोषणा PROT_ADDR1        0x08
#घोषणा PITCH1            0x0C
#घोषणा BASE_PAGE1        0x10  /* Video DMA 1 base page */
#घोषणा NUM_LINE_BYTE1    0x14

#घोषणा BASE_ODD2         0x18  /* Video DMA 2 रेजिस्टरs */
#घोषणा BASE_EVEN2        0x1C
#घोषणा PROT_ADDR2        0x20
#घोषणा PITCH2            0x24
#घोषणा BASE_PAGE2        0x28  /* Video DMA 2 base page */
#घोषणा NUM_LINE_BYTE2    0x2C

#घोषणा BASE_ODD3         0x30  /* Video DMA 3 रेजिस्टरs */
#घोषणा BASE_EVEN3        0x34
#घोषणा PROT_ADDR3        0x38
#घोषणा PITCH3            0x3C
#घोषणा BASE_PAGE3        0x40  /* Video DMA 3 base page */
#घोषणा NUM_LINE_BYTE3    0x44

#घोषणा PCI_BT_V1         0x48  /* Video/FIFO 1 */
#घोषणा PCI_BT_V2         0x49  /* Video/FIFO 2 */
#घोषणा PCI_BT_V3         0x4A  /* Video/FIFO 3 */
#घोषणा PCI_BT_DEBI       0x4B  /* DEBI */
#घोषणा PCI_BT_A          0x4C  /* Audio */

#घोषणा DD1_INIT          0x50  /* Init setting of DD1 पूर्णांकerface */

#घोषणा DD1_STREAM_B      0x54  /* DD1 B video data stream handling */
#घोषणा DD1_STREAM_A      0x56  /* DD1 A video data stream handling */

#घोषणा BRS_CTRL          0x58  /* BRS control रेजिस्टर */
#घोषणा HPS_CTRL          0x5C  /* HPS control रेजिस्टर */
#घोषणा HPS_V_SCALE       0x60  /* HPS vertical scale */
#घोषणा HPS_V_GAIN        0x64  /* HPS vertical ACL and gain */
#घोषणा HPS_H_PRESCALE    0x68  /* HPS horizontal prescale   */
#घोषणा HPS_H_SCALE       0x6C  /* HPS horizontal scale */
#घोषणा BCS_CTRL          0x70  /* BCS control */
#घोषणा CHROMA_KEY_RANGE  0x74
#घोषणा CLIP_FORMAT_CTRL  0x78  /* HPS outमाला_दो क्रमmats & clipping */

#घोषणा DEBI_CONFIG       0x7C
#घोषणा DEBI_COMMAND      0x80
#घोषणा DEBI_PAGE         0x84
#घोषणा DEBI_AD           0x88

#घोषणा I2C_TRANSFER      0x8C
#घोषणा I2C_STATUS        0x90

#घोषणा BASE_A1_IN        0x94	/* Audio 1 input DMA */
#घोषणा PROT_A1_IN        0x98
#घोषणा PAGE_A1_IN        0x9C

#घोषणा BASE_A1_OUT       0xA0  /* Audio 1 output DMA */
#घोषणा PROT_A1_OUT       0xA4
#घोषणा PAGE_A1_OUT       0xA8

#घोषणा BASE_A2_IN        0xAC  /* Audio 2 input DMA */
#घोषणा PROT_A2_IN        0xB0
#घोषणा PAGE_A2_IN        0xB4

#घोषणा BASE_A2_OUT       0xB8  /* Audio 2 output DMA */
#घोषणा PROT_A2_OUT       0xBC
#घोषणा PAGE_A2_OUT       0xC0

#घोषणा RPS_PAGE0         0xC4  /* RPS task 0 page रेजिस्टर */
#घोषणा RPS_PAGE1         0xC8  /* RPS task 1 page रेजिस्टर */

#घोषणा RPS_THRESH0       0xCC  /* HBI threshold क्रम task 0 */
#घोषणा RPS_THRESH1       0xD0  /* HBI threshold क्रम task 1 */

#घोषणा RPS_TOV0          0xD4  /* RPS समयout क्रम task 0 */
#घोषणा RPS_TOV1          0xD8  /* RPS समयout क्रम task 1 */

#घोषणा IER               0xDC  /* Interrupt enable रेजिस्टर */

#घोषणा GPIO_CTRL         0xE0  /* GPIO 0-3 रेजिस्टर */

#घोषणा EC1SSR            0xE4  /* Event cnt set 1 source select */
#घोषणा EC2SSR            0xE8  /* Event cnt set 2 source select */
#घोषणा ECT1R             0xEC  /* Event cnt set 1 thresholds */
#घोषणा ECT2R             0xF0  /* Event cnt set 2 thresholds */

#घोषणा ACON1             0xF4
#घोषणा ACON2             0xF8

#घोषणा MC1               0xFC   /* Main control रेजिस्टर 1 */
#घोषणा MC2               0x100  /* Main control रेजिस्टर 2  */

#घोषणा RPS_ADDR0         0x104  /* RPS task 0 address रेजिस्टर */
#घोषणा RPS_ADDR1         0x108  /* RPS task 1 address रेजिस्टर */

#घोषणा ISR               0x10C  /* Interrupt status रेजिस्टर */
#घोषणा PSR               0x110  /* Primary status रेजिस्टर */
#घोषणा SSR               0x114  /* Secondary status रेजिस्टर */

#घोषणा EC1R              0x118  /* Event counter set 1 रेजिस्टर */
#घोषणा EC2R              0x11C  /* Event counter set 2 रेजिस्टर */

#घोषणा PCI_VDP1          0x120  /* Video DMA poपूर्णांकer of FIFO 1 */
#घोषणा PCI_VDP2          0x124  /* Video DMA poपूर्णांकer of FIFO 2 */
#घोषणा PCI_VDP3          0x128  /* Video DMA poपूर्णांकer of FIFO 3 */
#घोषणा PCI_ADP1          0x12C  /* Audio DMA poपूर्णांकer of audio out 1 */
#घोषणा PCI_ADP2          0x130  /* Audio DMA poपूर्णांकer of audio in 1 */
#घोषणा PCI_ADP3          0x134  /* Audio DMA poपूर्णांकer of audio out 2 */
#घोषणा PCI_ADP4          0x138  /* Audio DMA poपूर्णांकer of audio in 2 */
#घोषणा PCI_DMA_DDP       0x13C  /* DEBI DMA poपूर्णांकer */

#घोषणा LEVEL_REP         0x140,
#घोषणा A_TIME_SLOT1      0x180,  /* from 180 - 1BC */
#घोषणा A_TIME_SLOT2      0x1C0,  /* from 1C0 - 1FC */

/* isr masks */
#घोषणा SPCI_PPEF       0x80000000  /* PCI parity error */
#घोषणा SPCI_PABO       0x40000000  /* PCI access error (target or master पात) */
#घोषणा SPCI_PPED       0x20000000  /* PCI parity error on 'real time data' */
#घोषणा SPCI_RPS_I1     0x10000000  /* Interrupt issued by RPS1 */
#घोषणा SPCI_RPS_I0     0x08000000  /* Interrupt issued by RPS0 */
#घोषणा SPCI_RPS_LATE1  0x04000000  /* RPS task 1 is late */
#घोषणा SPCI_RPS_LATE0  0x02000000  /* RPS task 0 is late */
#घोषणा SPCI_RPS_E1     0x01000000  /* RPS error from task 1 */
#घोषणा SPCI_RPS_E0     0x00800000  /* RPS error from task 0 */
#घोषणा SPCI_RPS_TO1    0x00400000  /* RPS समयout task 1 */
#घोषणा SPCI_RPS_TO0    0x00200000  /* RPS समयout task 0 */
#घोषणा SPCI_UPLD       0x00100000  /* RPS in upload */
#घोषणा SPCI_DEBI_S     0x00080000  /* DEBI status */
#घोषणा SPCI_DEBI_E     0x00040000  /* DEBI error */
#घोषणा SPCI_IIC_S      0x00020000  /* I2C status */
#घोषणा SPCI_IIC_E      0x00010000  /* I2C error */
#घोषणा SPCI_A2_IN      0x00008000  /* Audio 2 input DMA protection / limit */
#घोषणा SPCI_A2_OUT     0x00004000  /* Audio 2 output DMA protection / limit */
#घोषणा SPCI_A1_IN      0x00002000  /* Audio 1 input DMA protection / limit */
#घोषणा SPCI_A1_OUT     0x00001000  /* Audio 1 output DMA protection / limit */
#घोषणा SPCI_AFOU       0x00000800  /* Audio FIFO over- / underflow */
#घोषणा SPCI_V_PE       0x00000400  /* Video protection address */
#घोषणा SPCI_VFOU       0x00000200  /* Video FIFO over- / underflow */
#घोषणा SPCI_FIDA       0x00000100  /* Field ID video port A */
#घोषणा SPCI_FIDB       0x00000080  /* Field ID video port B */
#घोषणा SPCI_PIN3       0x00000040  /* GPIO pin 3 */
#घोषणा SPCI_PIN2       0x00000020  /* GPIO pin 2 */
#घोषणा SPCI_PIN1       0x00000010  /* GPIO pin 1 */
#घोषणा SPCI_PIN0       0x00000008  /* GPIO pin 0 */
#घोषणा SPCI_ECS        0x00000004  /* Event counter 1, 2, 4, 5 */
#घोषणा SPCI_EC3S       0x00000002  /* Event counter 3 */
#घोषणा SPCI_EC0S       0x00000001  /* Event counter 0 */

/* i2c */
#घोषणा	SAA7146_I2C_ABORT	(1<<7)
#घोषणा	SAA7146_I2C_SPERR	(1<<6)
#घोषणा	SAA7146_I2C_APERR	(1<<5)
#घोषणा	SAA7146_I2C_DTERR	(1<<4)
#घोषणा	SAA7146_I2C_DRERR	(1<<3)
#घोषणा	SAA7146_I2C_AL		(1<<2)
#घोषणा	SAA7146_I2C_ERR		(1<<1)
#घोषणा	SAA7146_I2C_BUSY	(1<<0)

#घोषणा	SAA7146_I2C_START	(0x3)
#घोषणा	SAA7146_I2C_CONT	(0x2)
#घोषणा	SAA7146_I2C_STOP	(0x1)
#घोषणा	SAA7146_I2C_NOP		(0x0)

#घोषणा SAA7146_I2C_BUS_BIT_RATE_6400	(0x500)
#घोषणा SAA7146_I2C_BUS_BIT_RATE_3200	(0x100)
#घोषणा SAA7146_I2C_BUS_BIT_RATE_480	(0x400)
#घोषणा SAA7146_I2C_BUS_BIT_RATE_320	(0x600)
#घोषणा SAA7146_I2C_BUS_BIT_RATE_240	(0x700)
#घोषणा SAA7146_I2C_BUS_BIT_RATE_120	(0x000)
#घोषणा SAA7146_I2C_BUS_BIT_RATE_80	(0x200)
#घोषणा SAA7146_I2C_BUS_BIT_RATE_60	(0x300)

अटल अंतरभूत व्योम SAA7146_IER_DISABLE(काष्ठा saa7146_dev *x, अचिन्हित y)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&x->पूर्णांक_slock, flags);
	saa7146_ग_लिखो(x, IER, saa7146_पढ़ो(x, IER) & ~y);
	spin_unlock_irqrestore(&x->पूर्णांक_slock, flags);
पूर्ण

अटल अंतरभूत व्योम SAA7146_IER_ENABLE(काष्ठा saa7146_dev *x, अचिन्हित y)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&x->पूर्णांक_slock, flags);
	saa7146_ग_लिखो(x, IER, saa7146_पढ़ो(x, IER) | y);
	spin_unlock_irqrestore(&x->पूर्णांक_slock, flags);
पूर्ण

#पूर्ण_अगर
