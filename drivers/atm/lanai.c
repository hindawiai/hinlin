<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* lanai.c -- Copyright 1999-2003 by Mitchell Blank Jr <mitch@sfgoth.com>
 *
 * This driver supports ATM cards based on the Efficient "Lanai"
 * chipset such as the Speedstream 3010 and the ENI-25p.  The
 * Speedstream 3060 is currently not supported since we करोn't
 * have the code to drive the on-board Alcatel DSL chipset (yet).
 *
 * Thanks to Efficient क्रम supporting this project with hardware,
 * करोcumentation, and by answering my questions.
 *
 * Things not working yet:
 *
 * o  We करोn't support the Speedstream 3060 yet - this card has
 *    an on-board DSL modem chip by Alcatel and the driver will
 *    need some extra code added to handle it
 *
 * o  Note that due to limitations of the Lanai only one VCC can be
 *    in CBR at once
 *
 * o We करोn't currently parse the EEPROM at all.  The code is all
 *   there as per the spec, but it करोesn't actually work.  I think
 *   there may be some issues with the करोcs.  Anyway, करो NOT
 *   enable it yet - bugs in that code may actually damage your
 *   hardware!  Because of this you should hardware an ESI beक्रमe
 *   trying to use this in a LANE or MPOA environment.
 *
 * o  AAL0 is stubbed in but the actual rx/tx path isn't written yet:
 *	vcc_tx_aal0() needs to send or queue a SKB
 *	vcc_tx_unqueue_aal0() needs to attempt to send queued SKBs
 *	vcc_rx_aal0() needs to handle AAL0 पूर्णांकerrupts
 *    This isn't too much work - I just wanted to get other things
 *    करोne first.
 *
 * o  lanai_change_qos() isn't written yet
 *
 * o  There aren't any ioctl's yet -- I'd like to eventually support
 *    setting loopback and LED modes that way.
 *
 * o  If the segmentation engine or DMA माला_लो shut करोwn we should restart
 *    card as per section 17.0i.  (see lanai_reset)
 *
 * o setsockopt(SO_CIRANGE) isn't करोne (although despite what the
 *   API says it isn't exactly commonly implemented)
 */

/* Version history:
 *   v.1.00 -- 26-JUL-2003 -- PCI/DMA updates
 *   v.0.02 -- 11-JAN-2000 -- Endian fixes
 *   v.0.01 -- 30-NOV-1999 -- Initial release
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* -------------------- TUNABLE PARAMATERS: */

/*
 * Maximum number of VCIs per card.  Setting it lower could theoretically
 * save some memory, but since we allocate our vcc list with get_मुक्त_pages,
 * it's not really likely क्रम most architectures
 */
#घोषणा NUM_VCI			(1024)

/*
 * Enable extra debugging
 */
#घोषणा DEBUG
/*
 * Debug _all_ रेजिस्टर operations with card, except the memory test.
 * Also disables the समयd poll to prevent extra chattiness.  This
 * isn't क्रम normal use
 */
#अघोषित DEBUG_RW

/*
 * The programming guide specअगरies a full test of the on-board SRAM
 * at initialization समय.  Undefine to हटाओ this
 */
#घोषणा FULL_MEMORY_TEST

/*
 * This is the number of (4 byte) service entries that we will
 * try to allocate at startup.  Note that we will end up with
 * one PAGE_SIZE's worth regardless of what this is set to
 */
#घोषणा SERVICE_ENTRIES		(1024)
/* TODO: make above a module load-समय option */

/*
 * We normally पढ़ो the onboard EEPROM in order to discover our MAC
 * address.  Undefine to _not_ करो this
 */
/* #घोषणा READ_EEPROM */ /* ***DONT ENABLE YET*** */
/* TODO: make above a module load-समय option (also) */

/*
 * Depth of TX fअगरo (in 128 byte units; range 2-31)
 * Smaller numbers are better क्रम network latency
 * Larger numbers are better क्रम PCI latency
 * I'm really sure where the best tradeoff is, but the BSD driver uses
 * 7 and it seems to work ok.
 */
#घोषणा TX_FIFO_DEPTH		(7)
/* TODO: make above a module load-समय option */

/*
 * How often (in jअगरfies) we will try to unstick stuck connections -
 * shouldn't need to happen much
 */
#घोषणा LANAI_POLL_PERIOD	(10*HZ)
/* TODO: make above a module load-समय option */

/*
 * When allocating an AAL5 receiving buffer, try to make it at least
 * large enough to hold this many max_sdu sized PDUs
 */
#घोषणा AAL5_RX_MULTIPLIER	(3)
/* TODO: make above a module load-समय option */

/*
 * Same क्रम transmitting buffer
 */
#घोषणा AAL5_TX_MULTIPLIER	(3)
/* TODO: make above a module load-समय option */

/*
 * When allocating an AAL0 transmiting buffer, how many cells should fit.
 * Remember we'll end up with a PAGE_SIZE of them anyway, so this isn't
 * really critical
 */
#घोषणा AAL0_TX_MULTIPLIER	(40)
/* TODO: make above a module load-समय option */

/*
 * How large should we make the AAL0 receiving buffer.  Remember that this
 * is shared between all AAL0 VC's
 */
#घोषणा AAL0_RX_BUFFER_SIZE	(PAGE_SIZE)
/* TODO: make above a module load-समय option */

/*
 * Should we use Lanai's "powerdown" feature when no vcc's are bound?
 */
/* #घोषणा USE_POWERDOWN */
/* TODO: make above a module load-समय option (also) */

/* -------------------- DEBUGGING AIDS: */

#घोषणा DEV_LABEL "lanai"

#अगर_घोषित DEBUG

#घोषणा DPRINTK(क्रमmat, args...) \
	prपूर्णांकk(KERN_DEBUG DEV_LABEL ": " क्रमmat, ##args)
#घोषणा APRINTK(truth, क्रमmat, args...) \
	करो अणु \
		अगर (unlikely(!(truth))) \
			prपूर्णांकk(KERN_ERR DEV_LABEL ": " क्रमmat, ##args); \
	पूर्ण जबतक (0)

#अन्यथा /* !DEBUG */

#घोषणा DPRINTK(क्रमmat, args...)
#घोषणा APRINTK(truth, क्रमmat, args...)

#पूर्ण_अगर /* DEBUG */

#अगर_घोषित DEBUG_RW
#घोषणा RWDEBUG(क्रमmat, args...) \
	prपूर्णांकk(KERN_DEBUG DEV_LABEL ": " क्रमmat, ##args)
#अन्यथा /* !DEBUG_RW */
#घोषणा RWDEBUG(क्रमmat, args...)
#पूर्ण_अगर

/* -------------------- DATA DEFINITIONS: */

#घोषणा LANAI_MAPPING_SIZE	(0x40000)
#घोषणा LANAI_EEPROM_SIZE	(128)

प्रकार पूर्णांक vci_t;
प्रकार व्योम __iomem *bus_addr_t;

/* DMA buffer in host memory क्रम TX, RX, or service list. */
काष्ठा lanai_buffer अणु
	u32 *start;	/* From get_मुक्त_pages */
	u32 *end;	/* One past last byte */
	u32 *ptr;	/* Poपूर्णांकer to current host location */
	dma_addr_t dmaaddr;
पूर्ण;

काष्ठा lanai_vcc_stats अणु
	अचिन्हित rx_nomem;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित rx_badlen;
			अचिन्हित service_trash;
			अचिन्हित service_stream;
			अचिन्हित service_rxcrc;
		पूर्ण aal5;
		काष्ठा अणु
		पूर्ण aal0;
	पूर्ण x;
पूर्ण;

काष्ठा lanai_dev;			/* Forward declaration */

/*
 * This is the card-specअगरic per-vcc data.  Note that unlike some other
 * drivers there is NOT a 1-to-1 correspondance between these and
 * aपंचांग_vcc's - each one of these represents an actual 2-way vcc, but
 * an aपंचांग_vcc can be 1-way and share with a 1-way vcc in the other
 * direction.  To make it weirder, there can even be 0-way vccs
 * bound to us, रुकोing to करो a change_qos
 */
काष्ठा lanai_vcc अणु
	bus_addr_t vbase;		/* Base of VCC's रेजिस्टरs */
	काष्ठा lanai_vcc_stats stats;
	पूर्णांक nref;			/* # of aपंचांग_vcc's who reference us */
	vci_t vci;
	काष्ठा अणु
		काष्ठा lanai_buffer buf;
		काष्ठा aपंचांग_vcc *aपंचांगvcc;	/* aपंचांग_vcc who is receiver */
	पूर्ण rx;
	काष्ठा अणु
		काष्ठा lanai_buffer buf;
		काष्ठा aपंचांग_vcc *aपंचांगvcc;	/* aपंचांग_vcc who is transmitter */
		पूर्णांक endptr;		/* last endptr from service entry */
		काष्ठा sk_buff_head backlog;
		व्योम (*unqueue)(काष्ठा lanai_dev *, काष्ठा lanai_vcc *, पूर्णांक);
	पूर्ण tx;
पूर्ण;

क्रमागत lanai_type अणु
	lanai2	= PCI_DEVICE_ID_EF_ATM_LANAI2,
	lanaihb	= PCI_DEVICE_ID_EF_ATM_LANAIHB
पूर्ण;

काष्ठा lanai_dev_stats अणु
	अचिन्हित ovfl_trash;	/* # of cells dropped - buffer overflow */
	अचिन्हित vci_trash;	/* # of cells dropped - बंदd vci */
	अचिन्हित hec_err;	/* # of cells dropped - bad HEC */
	अचिन्हित aपंचांग_ovfl;	/* # of cells dropped - rx fअगरo overflow */
	अचिन्हित pcierr_parity_detect;
	अचिन्हित pcierr_serr_set;
	अचिन्हित pcierr_master_पात;
	अचिन्हित pcierr_m_target_पात;
	अचिन्हित pcierr_s_target_पात;
	अचिन्हित pcierr_master_parity;
	अचिन्हित service_notx;
	अचिन्हित service_norx;
	अचिन्हित service_rxnotaal5;
	अचिन्हित dma_reenable;
	अचिन्हित card_reset;
पूर्ण;

काष्ठा lanai_dev अणु
	bus_addr_t base;
	काष्ठा lanai_dev_stats stats;
	काष्ठा lanai_buffer service;
	काष्ठा lanai_vcc **vccs;
#अगर_घोषित USE_POWERDOWN
	पूर्णांक nbound;			/* number of bound vccs */
#पूर्ण_अगर
	क्रमागत lanai_type type;
	vci_t num_vci;			/* Currently just NUM_VCI */
	u8 eeprom[LANAI_EEPROM_SIZE];
	u32 serialno, magicno;
	काष्ठा pci_dev *pci;
	DECLARE_BITMAP(backlog_vccs, NUM_VCI);   /* VCCs with tx backlog */
	DECLARE_BITMAP(transmit_पढ़ोy, NUM_VCI); /* VCCs with transmit space */
	काष्ठा समयr_list समयr;
	पूर्णांक naal0;
	काष्ठा lanai_buffer aal0buf;	/* AAL0 RX buffers */
	u32 conf1, conf2;		/* CONFIG[12] रेजिस्टरs */
	u32 status;			/* STATUS रेजिस्टर */
	spinlock_t endtxlock;
	spinlock_t servicelock;
	काष्ठा aपंचांग_vcc *cbrvcc;
	पूर्णांक number;
	पूर्णांक board_rev;
/* TODO - look at race conditions with मुख्यtence of conf1/conf2 */
/* TODO - transmit locking: should we use _irq not _irqsave? */
/* TODO - organize above in some rational fashion (see <यंत्र/cache.h>) */
पूर्ण;

/*
 * Each device has two biपंचांगaps क्रम each VCC (baclog_vccs and transmit_पढ़ोy)
 * This function iterates one of these, calling a given function क्रम each
 * vci with their bit set
 */
अटल व्योम vci_bitfield_iterate(काष्ठा lanai_dev *lanai,
	स्थिर अचिन्हित दीर्घ *lp,
	व्योम (*func)(काष्ठा lanai_dev *,vci_t vci))
अणु
	vci_t vci;

	क्रम_each_set_bit(vci, lp, NUM_VCI)
		func(lanai, vci);
पूर्ण

/* -------------------- BUFFER  UTILITIES: */

/*
 * Lanai needs DMA buffers aligned to 256 bytes of at least 1024 bytes -
 * usually any page allocation will करो.  Just to be safe in हाल
 * PAGE_SIZE is insanely tiny, though...
 */
#घोषणा LANAI_PAGE_SIZE   ((PAGE_SIZE >= 1024) ? PAGE_SIZE : 1024)

/*
 * Allocate a buffer in host RAM क्रम service list, RX, or TX
 * Returns buf->start==शून्य अगर no memory
 * Note that the size will be rounded up 2^n bytes, and
 * अगर we can't allocate that we'll settle क्रम something smaller
 * until minbytes
 */
अटल व्योम lanai_buf_allocate(काष्ठा lanai_buffer *buf,
	माप_प्रकार bytes, माप_प्रकार minbytes, काष्ठा pci_dev *pci)
अणु
	पूर्णांक size;

	अगर (bytes > (128 * 1024))	/* max lanai buffer size */
		bytes = 128 * 1024;
	क्रम (size = LANAI_PAGE_SIZE; size < bytes; size *= 2)
		;
	अगर (minbytes < LANAI_PAGE_SIZE)
		minbytes = LANAI_PAGE_SIZE;
	करो अणु
		/*
		 * Technically we could use non-consistent mappings क्रम
		 * everything, but the way the lanai uses DMA memory would
		 * make that a terrअगरic pain.  This is much simpler.
		 */
		buf->start = dma_alloc_coherent(&pci->dev,
						size, &buf->dmaaddr, GFP_KERNEL);
		अगर (buf->start != शून्य) अणु	/* Success */
			/* Lanai requires 256-byte alignment of DMA bufs */
			APRINTK((buf->dmaaddr & ~0xFFFFFF00) == 0,
			    "bad dmaaddr: 0x%lx\n",
			    (अचिन्हित दीर्घ) buf->dmaaddr);
			buf->ptr = buf->start;
			buf->end = (u32 *)
			    (&((अचिन्हित अक्षर *) buf->start)[size]);
			स_रखो(buf->start, 0, size);
			अवरोध;
		पूर्ण
		size /= 2;
	पूर्ण जबतक (size >= minbytes);
पूर्ण

/* size of buffer in bytes */
अटल अंतरभूत माप_प्रकार lanai_buf_size(स्थिर काष्ठा lanai_buffer *buf)
अणु
	वापस ((अचिन्हित दीर्घ) buf->end) - ((अचिन्हित दीर्घ) buf->start);
पूर्ण

अटल व्योम lanai_buf_deallocate(काष्ठा lanai_buffer *buf,
	काष्ठा pci_dev *pci)
अणु
	अगर (buf->start != शून्य) अणु
		dma_मुक्त_coherent(&pci->dev, lanai_buf_size(buf),
				  buf->start, buf->dmaaddr);
		buf->start = buf->end = buf->ptr = शून्य;
	पूर्ण
पूर्ण

/* size of buffer as "card order" (0=1k .. 7=128k) */
अटल पूर्णांक lanai_buf_size_carकरोrder(स्थिर काष्ठा lanai_buffer *buf)
अणु
	पूर्णांक order = get_order(lanai_buf_size(buf)) + (PAGE_SHIFT - 10);

	/* This can only happen अगर PAGE_SIZE is gigantic, but just in हाल */
	अगर (order > 7)
		order = 7;
	वापस order;
पूर्ण

/* -------------------- PORT I/O UTILITIES: */

/* Registers (and their bit-fields) */
क्रमागत lanai_रेजिस्टर अणु
	Reset_Reg		= 0x00,	/* Reset; पढ़ो क्रम chip type; bits: */
#घोषणा   RESET_GET_BOARD_REV(x)    (((x)>> 0)&0x03)	/* Board revision */
#घोषणा   RESET_GET_BOARD_ID(x)	    (((x)>> 2)&0x03)	/* Board ID */
#घोषणा     BOARD_ID_LANAI256		(0)	/* 25.6M adapter card */
	Endian_Reg		= 0x04,	/* Endian setting */
	IntStatus_Reg		= 0x08,	/* Interrupt status */
	IntStatusMasked_Reg	= 0x0C,	/* Interrupt status (masked) */
	IntAck_Reg		= 0x10,	/* Interrupt acknowledge */
	IntAckMasked_Reg	= 0x14,	/* Interrupt acknowledge (masked) */
	IntStatusSet_Reg	= 0x18,	/* Get status + enable/disable */
	IntStatusSetMasked_Reg	= 0x1C,	/* Get status + en/di (masked) */
	IntControlEna_Reg	= 0x20,	/* Interrupt control enable */
	IntControlDis_Reg	= 0x24,	/* Interrupt control disable */
	Status_Reg		= 0x28,	/* Status */
#घोषणा   STATUS_PROMDATA	 (0x00000001)	/* PROM_DATA pin */
#घोषणा   STATUS_WAITING	 (0x00000002)	/* Interrupt being delayed */
#घोषणा	  STATUS_SOOL		 (0x00000004)	/* SOOL alarm */
#घोषणा   STATUS_LOCD		 (0x00000008)	/* LOCD alarm */
#घोषणा	  STATUS_LED		 (0x00000010)	/* LED (HAPPI) output */
#घोषणा   STATUS_GPIN		 (0x00000020)	/* GPIN pin */
#घोषणा   STATUS_BUTTBUSY	 (0x00000040)	/* Butt रेजिस्टर is pending */
	Config1_Reg		= 0x2C,	/* Config word 1; bits: */
#घोषणा   CONFIG1_PROMDATA	 (0x00000001)	/* PROM_DATA pin */
#घोषणा   CONFIG1_PROMCLK	 (0x00000002)	/* PROM_CLK pin */
#घोषणा   CONFIG1_SET_READMODE(x) ((x)*0x004)	/* PCI BM पढ़ोs; values: */
#घोषणा     READMODE_PLAIN	    (0)		/*   Plain memory पढ़ो */
#घोषणा     READMODE_LINE	    (2)		/*   Memory पढ़ो line */
#घोषणा     READMODE_MULTIPLE	    (3)		/*   Memory पढ़ो multiple */
#घोषणा   CONFIG1_DMA_ENABLE	 (0x00000010)	/* Turn on DMA */
#घोषणा   CONFIG1_POWERDOWN	 (0x00000020)	/* Turn off घड़ीs */
#घोषणा   CONFIG1_SET_LOOPMODE(x) ((x)*0x080)	/* Clock&loop mode; values: */
#घोषणा     LOOPMODE_NORMAL	    (0)		/*   Normal - no loop */
#घोषणा     LOOPMODE_TIME	    (1)
#घोषणा     LOOPMODE_DIAG	    (2)
#घोषणा     LOOPMODE_LINE	    (3)
#घोषणा   CONFIG1_MASK_LOOPMODE  (0x00000180)
#घोषणा   CONFIG1_SET_LEDMODE(x) ((x)*0x0200)	/* Mode of LED; values: */
#घोषणा     LEDMODE_NOT_SOOL	    (0)		/*   !SOOL */
#घोषणा	    LEDMODE_OFF		    (1)		/*   0     */
#घोषणा	    LEDMODE_ON		    (2)		/*   1     */
#घोषणा	    LEDMODE_NOT_LOCD	    (3)		/*   !LOCD */
#घोषणा	    LEDMORE_GPIN	    (4)		/*   GPIN  */
#घोषणा     LEDMODE_NOT_GPIN	    (7)		/*   !GPIN */
#घोषणा   CONFIG1_MASK_LEDMODE	 (0x00000E00)
#घोषणा   CONFIG1_GPOUT1	 (0x00001000)	/* Toggle क्रम reset */
#घोषणा   CONFIG1_GPOUT2	 (0x00002000)	/* Loopback PHY */
#घोषणा   CONFIG1_GPOUT3	 (0x00004000)	/* Loopback lanai */
	Config2_Reg		= 0x30,	/* Config word 2; bits: */
#घोषणा   CONFIG2_HOWMANY	 (0x00000001)	/* >512 VCIs? */
#घोषणा   CONFIG2_PTI7_MODE	 (0x00000002)	/* Make PTI=7 RM, not OAM */
#घोषणा   CONFIG2_VPI_CHK_DIS	 (0x00000004)	/* Ignore RX VPI value */
#घोषणा   CONFIG2_HEC_DROP	 (0x00000008)	/* Drop cells w/ HEC errors */
#घोषणा   CONFIG2_VCI0_NORMAL	 (0x00000010)	/* Treat VCI=0 normally */
#घोषणा   CONFIG2_CBR_ENABLE	 (0x00000020)	/* Deal with CBR traffic */
#घोषणा   CONFIG2_TRASH_ALL	 (0x00000040)	/* Trashing incoming cells */
#घोषणा   CONFIG2_TX_DISABLE	 (0x00000080)	/* Trashing outgoing cells */
#घोषणा   CONFIG2_SET_TRASH	 (0x00000100)	/* Turn trashing on */
	Statistics_Reg		= 0x34,	/* Statistics; bits: */
#घोषणा   STATS_GET_FIFO_OVFL(x)    (((x)>> 0)&0xFF)	/* FIFO overflowed */
#घोषणा   STATS_GET_HEC_ERR(x)      (((x)>> 8)&0xFF)	/* HEC was bad */
#घोषणा   STATS_GET_BAD_VCI(x)      (((x)>>16)&0xFF)	/* VCI not खोलो */
#घोषणा   STATS_GET_BUF_OVFL(x)     (((x)>>24)&0xFF)	/* VCC buffer full */
	ServiceStuff_Reg	= 0x38,	/* Service stuff; bits: */
#घोषणा   SSTUFF_SET_SIZE(x) ((x)*0x20000000)	/* size of service buffer */
#घोषणा   SSTUFF_SET_ADDR(x)	    ((x)>>8)	/* set address of buffer */
	ServWrite_Reg		= 0x3C,	/* ServWrite Poपूर्णांकer */
	ServRead_Reg		= 0x40,	/* ServRead Poपूर्णांकer */
	TxDepth_Reg		= 0x44,	/* FIFO Transmit Depth */
	Butt_Reg		= 0x48,	/* Butt रेजिस्टर */
	CBR_ICG_Reg		= 0x50,
	CBR_PTR_Reg		= 0x54,
	PingCount_Reg		= 0x58,	/* Ping count */
	DMA_Addr_Reg		= 0x5C	/* DMA address */
पूर्ण;

अटल अंतरभूत bus_addr_t reg_addr(स्थिर काष्ठा lanai_dev *lanai,
	क्रमागत lanai_रेजिस्टर reg)
अणु
	वापस lanai->base + reg;
पूर्ण

अटल अंतरभूत u32 reg_पढ़ो(स्थिर काष्ठा lanai_dev *lanai,
	क्रमागत lanai_रेजिस्टर reg)
अणु
	u32 t;
	t = पढ़ोl(reg_addr(lanai, reg));
	RWDEBUG("R [0x%08X] 0x%02X = 0x%08X\n", (अचिन्हित पूर्णांक) lanai->base,
	    (पूर्णांक) reg, t);
	वापस t;
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखो(स्थिर काष्ठा lanai_dev *lanai, u32 val,
	क्रमागत lanai_रेजिस्टर reg)
अणु
	RWDEBUG("W [0x%08X] 0x%02X < 0x%08X\n", (अचिन्हित पूर्णांक) lanai->base,
	    (पूर्णांक) reg, val);
	ग_लिखोl(val, reg_addr(lanai, reg));
पूर्ण

अटल अंतरभूत व्योम conf1_ग_लिखो(स्थिर काष्ठा lanai_dev *lanai)
अणु
	reg_ग_लिखो(lanai, lanai->conf1, Config1_Reg);
पूर्ण

अटल अंतरभूत व्योम conf2_ग_लिखो(स्थिर काष्ठा lanai_dev *lanai)
अणु
	reg_ग_लिखो(lanai, lanai->conf2, Config2_Reg);
पूर्ण

/* Same as conf2_ग_लिखो(), but defers I/O अगर we're घातered करोwn */
अटल अंतरभूत व्योम conf2_ग_लिखो_अगर_घातerup(स्थिर काष्ठा lanai_dev *lanai)
अणु
#अगर_घोषित USE_POWERDOWN
	अगर (unlikely((lanai->conf1 & CONFIG1_POWERDOWN) != 0))
		वापस;
#पूर्ण_अगर /* USE_POWERDOWN */
	conf2_ग_लिखो(lanai);
पूर्ण

अटल अंतरभूत व्योम reset_board(स्थिर काष्ठा lanai_dev *lanai)
अणु
	DPRINTK("about to reset board\n");
	reg_ग_लिखो(lanai, 0, Reset_Reg);
	/*
	 * If we करोn't delay a little जबतक here then we can end up
	 * leaving the card in a VERY weird state and lock up the
	 * PCI bus.  This isn't documented anywhere but I've convinced
	 * myself after a lot of painful experimentation
	 */
	udelay(5);
पूर्ण

/* -------------------- CARD SRAM UTILITIES: */

/* The SRAM is mapped पूर्णांकo normal PCI memory space - the only catch is
 * that it is only 16-bits wide but must be accessed as 32-bit.  The
 * 16 high bits will be zero.  We करोn't hide this, since they get
 * programmed mostly like discrete रेजिस्टरs anyway
 */
#घोषणा SRAM_START (0x20000)
#घोषणा SRAM_BYTES (0x20000)	/* Again, half करोn't really exist */

अटल अंतरभूत bus_addr_t sram_addr(स्थिर काष्ठा lanai_dev *lanai, पूर्णांक offset)
अणु
	वापस lanai->base + SRAM_START + offset;
पूर्ण

अटल अंतरभूत u32 sram_पढ़ो(स्थिर काष्ठा lanai_dev *lanai, पूर्णांक offset)
अणु
	वापस पढ़ोl(sram_addr(lanai, offset));
पूर्ण

अटल अंतरभूत व्योम sram_ग_लिखो(स्थिर काष्ठा lanai_dev *lanai,
	u32 val, पूर्णांक offset)
अणु
	ग_लिखोl(val, sram_addr(lanai, offset));
पूर्ण

अटल पूर्णांक sram_test_word(स्थिर काष्ठा lanai_dev *lanai, पूर्णांक offset,
			  u32 pattern)
अणु
	u32 पढ़ोback;
	sram_ग_लिखो(lanai, pattern, offset);
	पढ़ोback = sram_पढ़ो(lanai, offset);
	अगर (likely(पढ़ोback == pattern))
		वापस 0;
	prपूर्णांकk(KERN_ERR DEV_LABEL
	    "(itf %d): SRAM word at %d bad: wrote 0x%X, read 0x%X\n",
	    lanai->number, offset,
	    (अचिन्हित पूर्णांक) pattern, (अचिन्हित पूर्णांक) पढ़ोback);
	वापस -EIO;
पूर्ण

अटल पूर्णांक sram_test_pass(स्थिर काष्ठा lanai_dev *lanai, u32 pattern)
अणु
	पूर्णांक offset, result = 0;
	क्रम (offset = 0; offset < SRAM_BYTES && result == 0; offset += 4)
		result = sram_test_word(lanai, offset, pattern);
	वापस result;
पूर्ण

अटल पूर्णांक sram_test_and_clear(स्थिर काष्ठा lanai_dev *lanai)
अणु
#अगर_घोषित FULL_MEMORY_TEST
	पूर्णांक result;
	DPRINTK("testing SRAM\n");
	अगर ((result = sram_test_pass(lanai, 0x5555)) != 0)
		वापस result;
	अगर ((result = sram_test_pass(lanai, 0xAAAA)) != 0)
		वापस result;
#पूर्ण_अगर
	DPRINTK("clearing SRAM\n");
	वापस sram_test_pass(lanai, 0x0000);
पूर्ण

/* -------------------- CARD-BASED VCC TABLE UTILITIES: */

/* vcc table */
क्रमागत lanai_vcc_offset अणु
	vcc_rxaddr1		= 0x00,	/* Location1, plus bits: */
#घोषणा   RXADDR1_SET_SIZE(x) ((x)*0x0000100)	/* size of RX buffer */
#घोषणा   RXADDR1_SET_RMMODE(x) ((x)*0x00800)	/* RM cell action; values: */
#घोषणा     RMMODE_TRASH	  (0)		/*   discard */
#घोषणा     RMMODE_PRESERVE	  (1)		/*   input as AAL0 */
#घोषणा     RMMODE_PIPE		  (2)		/*   pipe to coscheduler */
#घोषणा     RMMODE_PIPEALL	  (3)		/*   pipe non-RM too */
#घोषणा   RXADDR1_OAM_PRESERVE	 (0x00002000)	/* Input OAM cells as AAL0 */
#घोषणा   RXADDR1_SET_MODE(x) ((x)*0x0004000)	/* Reassembly mode */
#घोषणा     RXMODE_TRASH	  (0)		/*   discard */
#घोषणा     RXMODE_AAL0		  (1)		/*   non-AAL5 mode */
#घोषणा     RXMODE_AAL5		  (2)		/*   AAL5, पूर्णांकr. each PDU */
#घोषणा     RXMODE_AAL5_STREAM	  (3)		/*   AAL5 w/o per-PDU पूर्णांकr */
	vcc_rxaddr2		= 0x04,	/* Location2 */
	vcc_rxcrc1		= 0x08,	/* RX CRC claculation space */
	vcc_rxcrc2		= 0x0C,
	vcc_rxग_लिखोptr		= 0x10, /* RX ग_लिखोptr, plus bits: */
#घोषणा   RXWRITEPTR_LASTEFCI	 (0x00002000)	/* Last PDU had EFCI bit */
#घोषणा   RXWRITEPTR_DROPPING	 (0x00004000)	/* Had error, dropping */
#घोषणा   RXWRITEPTR_TRASHING	 (0x00008000)	/* Trashing */
	vcc_rxbufstart		= 0x14,	/* RX bufstart, plus bits: */
#घोषणा   RXBUFSTART_CLP	 (0x00004000)
#घोषणा   RXBUFSTART_CI		 (0x00008000)
	vcc_rxपढ़ोptr		= 0x18,	/* RX पढ़ोptr */
	vcc_txicg		= 0x1C, /* TX ICG */
	vcc_txaddr1		= 0x20,	/* Location1, plus bits: */
#घोषणा   TXADDR1_SET_SIZE(x) ((x)*0x0000100)	/* size of TX buffer */
#घोषणा   TXADDR1_ABR		 (0x00008000)	/* use ABR (करोesn't work) */
	vcc_txaddr2		= 0x24,	/* Location2 */
	vcc_txcrc1		= 0x28,	/* TX CRC claculation space */
	vcc_txcrc2		= 0x2C,
	vcc_txपढ़ोptr		= 0x30, /* TX Readptr, plus bits: */
#घोषणा   TXREADPTR_GET_PTR(x) ((x)&0x01FFF)
#घोषणा   TXREADPTR_MASK_DELTA	(0x0000E000)	/* ? */
	vcc_txendptr		= 0x34, /* TX Endptr, plus bits: */
#घोषणा   TXENDPTR_CLP		(0x00002000)
#घोषणा   TXENDPTR_MASK_PDUMODE	(0x0000C000)	/* PDU mode; values: */
#घोषणा     PDUMODE_AAL0	 (0*0x04000)
#घोषणा     PDUMODE_AAL5	 (2*0x04000)
#घोषणा     PDUMODE_AAL5STREAM	 (3*0x04000)
	vcc_txग_लिखोptr		= 0x38,	/* TX Writeptr */
#घोषणा   TXWRITEPTR_GET_PTR(x) ((x)&0x1FFF)
	vcc_txcbr_next		= 0x3C	/* # of next CBR VCI in ring */
#घोषणा   TXCBR_NEXT_BOZO	(0x00008000)	/* "bozo bit" */
पूर्ण;

#घोषणा CARDVCC_SIZE	(0x40)

अटल अंतरभूत bus_addr_t cardvcc_addr(स्थिर काष्ठा lanai_dev *lanai,
	vci_t vci)
अणु
	वापस sram_addr(lanai, vci * CARDVCC_SIZE);
पूर्ण

अटल अंतरभूत u32 cardvcc_पढ़ो(स्थिर काष्ठा lanai_vcc *lvcc,
	क्रमागत lanai_vcc_offset offset)
अणु
	u32 val;
	APRINTK(lvcc->vbase != शून्य, "cardvcc_read: unbound vcc!\n");
	val= पढ़ोl(lvcc->vbase + offset);
	RWDEBUG("VR vci=%04d 0x%02X = 0x%08X\n",
	    lvcc->vci, (पूर्णांक) offset, val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम cardvcc_ग_लिखो(स्थिर काष्ठा lanai_vcc *lvcc,
	u32 val, क्रमागत lanai_vcc_offset offset)
अणु
	APRINTK(lvcc->vbase != शून्य, "cardvcc_write: unbound vcc!\n");
	APRINTK((val & ~0xFFFF) == 0,
	    "cardvcc_write: bad val 0x%X (vci=%d, addr=0x%02X)\n",
	    (अचिन्हित पूर्णांक) val, lvcc->vci, (अचिन्हित पूर्णांक) offset);
	RWDEBUG("VW vci=%04d 0x%02X > 0x%08X\n",
	    lvcc->vci, (अचिन्हित पूर्णांक) offset, (अचिन्हित पूर्णांक) val);
	ग_लिखोl(val, lvcc->vbase + offset);
पूर्ण

/* -------------------- COMPUTE SIZE OF AN AAL5 PDU: */

/* How many bytes will an AAL5 PDU take to transmit - remember that:
 *   o  we need to add 8 bytes क्रम length, CPI, UU, and CRC
 *   o  we need to round up to 48 bytes क्रम cells
 */
अटल अंतरभूत पूर्णांक aal5_size(पूर्णांक size)
अणु
	पूर्णांक cells = (size + 8 + 47) / 48;
	वापस cells * 48;
पूर्ण

/* -------------------- FREE AN ATM SKB: */

अटल अंतरभूत व्योम lanai_मुक्त_skb(काष्ठा aपंचांग_vcc *aपंचांगvcc, काष्ठा sk_buff *skb)
अणु
	अगर (aपंचांगvcc->pop != शून्य)
		aपंचांगvcc->pop(aपंचांगvcc, skb);
	अन्यथा
		dev_kमुक्त_skb_any(skb);
पूर्ण

/* -------------------- TURN VCCS ON AND OFF: */

अटल व्योम host_vcc_start_rx(स्थिर काष्ठा lanai_vcc *lvcc)
अणु
	u32 addr1;
	अगर (lvcc->rx.aपंचांगvcc->qos.aal == ATM_AAL5) अणु
		dma_addr_t dmaaddr = lvcc->rx.buf.dmaaddr;
		cardvcc_ग_लिखो(lvcc, 0xFFFF, vcc_rxcrc1);
		cardvcc_ग_लिखो(lvcc, 0xFFFF, vcc_rxcrc2);
		cardvcc_ग_लिखो(lvcc, 0, vcc_rxग_लिखोptr);
		cardvcc_ग_लिखो(lvcc, 0, vcc_rxbufstart);
		cardvcc_ग_लिखो(lvcc, 0, vcc_rxपढ़ोptr);
		cardvcc_ग_लिखो(lvcc, (dmaaddr >> 16) & 0xFFFF, vcc_rxaddr2);
		addr1 = ((dmaaddr >> 8) & 0xFF) |
		    RXADDR1_SET_SIZE(lanai_buf_size_carकरोrder(&lvcc->rx.buf))|
		    RXADDR1_SET_RMMODE(RMMODE_TRASH) |	/* ??? */
		 /* RXADDR1_OAM_PRESERVE |	--- no OAM support yet */
		    RXADDR1_SET_MODE(RXMODE_AAL5);
	पूर्ण अन्यथा
		addr1 = RXADDR1_SET_RMMODE(RMMODE_PRESERVE) | /* ??? */
		    RXADDR1_OAM_PRESERVE |		      /* ??? */
		    RXADDR1_SET_MODE(RXMODE_AAL0);
	/* This one must be last! */
	cardvcc_ग_लिखो(lvcc, addr1, vcc_rxaddr1);
पूर्ण

अटल व्योम host_vcc_start_tx(स्थिर काष्ठा lanai_vcc *lvcc)
अणु
	dma_addr_t dmaaddr = lvcc->tx.buf.dmaaddr;
	cardvcc_ग_लिखो(lvcc, 0, vcc_txicg);
	cardvcc_ग_लिखो(lvcc, 0xFFFF, vcc_txcrc1);
	cardvcc_ग_लिखो(lvcc, 0xFFFF, vcc_txcrc2);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txपढ़ोptr);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txendptr);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txग_लिखोptr);
	cardvcc_ग_लिखो(lvcc,
		(lvcc->tx.aपंचांगvcc->qos.txtp.traffic_class == ATM_CBR) ?
		TXCBR_NEXT_BOZO | lvcc->vci : 0, vcc_txcbr_next);
	cardvcc_ग_लिखो(lvcc, (dmaaddr >> 16) & 0xFFFF, vcc_txaddr2);
	cardvcc_ग_लिखो(lvcc,
	    ((dmaaddr >> 8) & 0xFF) |
	    TXADDR1_SET_SIZE(lanai_buf_size_carकरोrder(&lvcc->tx.buf)),
	    vcc_txaddr1);
पूर्ण

/* Shutकरोwn receiving on card */
अटल व्योम lanai_shutकरोwn_rx_vci(स्थिर काष्ठा lanai_vcc *lvcc)
अणु
	अगर (lvcc->vbase == शून्य)	/* We were never bound to a VCI */
		वापस;
	/* 15.1.1 - set to trashing, रुको one cell समय (15us) */
	cardvcc_ग_लिखो(lvcc,
	    RXADDR1_SET_RMMODE(RMMODE_TRASH) |
	    RXADDR1_SET_MODE(RXMODE_TRASH), vcc_rxaddr1);
	udelay(15);
	/* 15.1.2 - clear rest of entries */
	cardvcc_ग_लिखो(lvcc, 0, vcc_rxaddr2);
	cardvcc_ग_लिखो(lvcc, 0, vcc_rxcrc1);
	cardvcc_ग_लिखो(lvcc, 0, vcc_rxcrc2);
	cardvcc_ग_लिखो(lvcc, 0, vcc_rxग_लिखोptr);
	cardvcc_ग_लिखो(lvcc, 0, vcc_rxbufstart);
	cardvcc_ग_लिखो(lvcc, 0, vcc_rxपढ़ोptr);
पूर्ण

/* Shutकरोwn transmitting on card.
 * Unक्रमtunately the lanai needs us to रुको until all the data
 * drains out of the buffer beक्रमe we can dealloc it, so this
 * can take aजबतक -- up to 370ms क्रम a full 128KB buffer
 * assuming everone अन्यथा is quiet.  In theory the समय is
 * boundless अगर there's a CBR VCC holding things up.
 */
अटल व्योम lanai_shutकरोwn_tx_vci(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_vcc *lvcc)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags, समयout;
	पूर्णांक पढ़ो, ग_लिखो, lastपढ़ो = -1;

	अगर (lvcc->vbase == शून्य)	/* We were never bound to a VCI */
		वापस;
	/* 15.2.1 - रुको क्रम queue to drain */
	जबतक ((skb = skb_dequeue(&lvcc->tx.backlog)) != शून्य)
		lanai_मुक्त_skb(lvcc->tx.aपंचांगvcc, skb);
	पढ़ो_lock_irqsave(&vcc_sklist_lock, flags);
	__clear_bit(lvcc->vci, lanai->backlog_vccs);
	पढ़ो_unlock_irqrestore(&vcc_sklist_lock, flags);
	/*
	 * We need to रुको क्रम the VCC to drain but करोn't रुको क्रमever.  We
	 * give each 1K of buffer size 1/128th of a second to clear out.
	 * TODO: maybe disable CBR अगर we're about to समयout?
	 */
	समयout = jअगरfies +
	    (((lanai_buf_size(&lvcc->tx.buf) / 1024) * HZ) >> 7);
	ग_लिखो = TXWRITEPTR_GET_PTR(cardvcc_पढ़ो(lvcc, vcc_txग_लिखोptr));
	क्रम (;;) अणु
		पढ़ो = TXREADPTR_GET_PTR(cardvcc_पढ़ो(lvcc, vcc_txपढ़ोptr));
		अगर (पढ़ो == ग_लिखो &&	   /* Is TX buffer empty? */
		    (lvcc->tx.aपंचांगvcc->qos.txtp.traffic_class != ATM_CBR ||
		    (cardvcc_पढ़ो(lvcc, vcc_txcbr_next) &
		    TXCBR_NEXT_BOZO) == 0))
			अवरोध;
		अगर (पढ़ो != lastपढ़ो) अणु	   /* Has there been any progress? */
			lastपढ़ो = पढ़ो;
			समयout += HZ / 10;
		पूर्ण
		अगर (unlikely(समय_after(jअगरfies, समयout))) अणु
			prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): Timed out on "
			    "backlog closing vci %d\n",
			    lvcc->tx.aपंचांगvcc->dev->number, lvcc->vci);
			DPRINTK("read, write = %d, %d\n", पढ़ो, ग_लिखो);
			अवरोध;
		पूर्ण
		msleep(40);
	पूर्ण
	/* 15.2.2 - clear out all tx रेजिस्टरs */
	cardvcc_ग_लिखो(lvcc, 0, vcc_txपढ़ोptr);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txग_लिखोptr);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txendptr);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txcrc1);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txcrc2);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txaddr2);
	cardvcc_ग_लिखो(lvcc, 0, vcc_txaddr1);
पूर्ण

/* -------------------- MANAGING AAL0 RX BUFFER: */

अटल अंतरभूत पूर्णांक aal0_buffer_allocate(काष्ठा lanai_dev *lanai)
अणु
	DPRINTK("aal0_buffer_allocate: allocating AAL0 RX buffer\n");
	lanai_buf_allocate(&lanai->aal0buf, AAL0_RX_BUFFER_SIZE, 80,
			   lanai->pci);
	वापस (lanai->aal0buf.start == शून्य) ? -ENOMEM : 0;
पूर्ण

अटल अंतरभूत व्योम aal0_buffer_मुक्त(काष्ठा lanai_dev *lanai)
अणु
	DPRINTK("aal0_buffer_allocate: freeing AAL0 RX buffer\n");
	lanai_buf_deallocate(&lanai->aal0buf, lanai->pci);
पूर्ण

/* -------------------- EEPROM UTILITIES: */

/* Offsets of data in the EEPROM */
#घोषणा EEPROM_COPYRIGHT	(0)
#घोषणा EEPROM_COPYRIGHT_LEN	(44)
#घोषणा EEPROM_CHECKSUM		(62)
#घोषणा EEPROM_CHECKSUM_REV	(63)
#घोषणा EEPROM_MAC		(64)
#घोषणा EEPROM_MAC_REV		(70)
#घोषणा EEPROM_SERIAL		(112)
#घोषणा EEPROM_SERIAL_REV	(116)
#घोषणा EEPROM_MAGIC		(120)
#घोषणा EEPROM_MAGIC_REV	(124)

#घोषणा EEPROM_MAGIC_VALUE	(0x5AB478D2)

#अगर_अघोषित READ_EEPROM

/* Stub functions to use अगर EEPROM पढ़ोing is disabled */
अटल पूर्णांक eeprom_पढ़ो(काष्ठा lanai_dev *lanai)
अणु
	prपूर्णांकk(KERN_INFO DEV_LABEL "(itf %d): *NOT* reading EEPROM\n",
	    lanai->number);
	स_रखो(&lanai->eeprom[EEPROM_MAC], 0, 6);
	वापस 0;
पूर्ण

अटल पूर्णांक eeprom_validate(काष्ठा lanai_dev *lanai)
अणु
	lanai->serialno = 0;
	lanai->magicno = EEPROM_MAGIC_VALUE;
	वापस 0;
पूर्ण

#अन्यथा /* READ_EEPROM */

अटल पूर्णांक eeprom_पढ़ो(काष्ठा lanai_dev *lanai)
अणु
	पूर्णांक i, address;
	u8 data;
	u32 पंचांगp;
#घोषणा set_config1(x)   करो अणु lanai->conf1 = x; conf1_ग_लिखो(lanai); \
			    पूर्ण जबतक (0)
#घोषणा घड़ी_h()	 set_config1(lanai->conf1 | CONFIG1_PROMCLK)
#घोषणा घड़ी_l()	 set_config1(lanai->conf1 &~ CONFIG1_PROMCLK)
#घोषणा data_h()	 set_config1(lanai->conf1 | CONFIG1_PROMDATA)
#घोषणा data_l()	 set_config1(lanai->conf1 &~ CONFIG1_PROMDATA)
#घोषणा pre_पढ़ो()	 करो अणु data_h(); घड़ी_h(); udelay(5); पूर्ण जबतक (0)
#घोषणा पढ़ो_pin()	 (reg_पढ़ो(lanai, Status_Reg) & STATUS_PROMDATA)
#घोषणा send_stop()	 करो अणु data_l(); udelay(5); घड़ी_h(); udelay(5); \
			      data_h(); udelay(5); पूर्ण जबतक (0)
	/* start with both घड़ी and data high */
	data_h(); घड़ी_h(); udelay(5);
	क्रम (address = 0; address < LANAI_EEPROM_SIZE; address++) अणु
		data = (address << 1) | 1;	/* Command=पढ़ो + address */
		/* send start bit */
		data_l(); udelay(5);
		घड़ी_l(); udelay(5);
		क्रम (i = 128; i != 0; i >>= 1) अणु   /* ग_लिखो command out */
			पंचांगp = (lanai->conf1 & ~CONFIG1_PROMDATA) |
			    ((data & i) ? CONFIG1_PROMDATA : 0);
			अगर (lanai->conf1 != पंचांगp) अणु
				set_config1(पंचांगp);
				udelay(5);	/* Let new data settle */
			पूर्ण
			घड़ी_h(); udelay(5); घड़ी_l(); udelay(5);
		पूर्ण
		/* look क्रम ack */
		data_h(); घड़ी_h(); udelay(5);
		अगर (पढ़ो_pin() != 0)
			जाओ error;	/* No ack seen */
		घड़ी_l(); udelay(5);
		/* पढ़ो back result */
		क्रम (data = 0, i = 7; i >= 0; i--) अणु
			data_h(); घड़ी_h(); udelay(5);
			data = (data << 1) | !!पढ़ो_pin();
			घड़ी_l(); udelay(5);
		पूर्ण
		/* look again क्रम ack */
		data_h(); घड़ी_h(); udelay(5);
		अगर (पढ़ो_pin() == 0)
			जाओ error;	/* Spurious ack */
		घड़ी_l(); udelay(5);
		send_stop();
		lanai->eeprom[address] = data;
		DPRINTK("EEPROM 0x%04X %02X\n",
		    (अचिन्हित पूर्णांक) address, (अचिन्हित पूर्णांक) data);
	पूर्ण
	वापस 0;
    error:
	घड़ी_l(); udelay(5);		/* finish पढ़ो */
	send_stop();
	prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): error reading EEPROM byte %d\n",
	    lanai->number, address);
	वापस -EIO;
#अघोषित set_config1
#अघोषित घड़ी_h
#अघोषित घड़ी_l
#अघोषित data_h
#अघोषित data_l
#अघोषित pre_पढ़ो
#अघोषित पढ़ो_pin
#अघोषित send_stop
पूर्ण

/* पढ़ो a big-endian 4-byte value out of eeprom */
अटल अंतरभूत u32 eeprom_be4(स्थिर काष्ठा lanai_dev *lanai, पूर्णांक address)
अणु
	वापस be32_to_cpup((स्थिर u32 *) &lanai->eeprom[address]);
पूर्ण

/* Checksum/validate EEPROM contents */
अटल पूर्णांक eeprom_validate(काष्ठा lanai_dev *lanai)
अणु
	पूर्णांक i, s;
	u32 v;
	स्थिर u8 *e = lanai->eeprom;
#अगर_घोषित DEBUG
	/* First, see अगर we can get an ASCIIZ string out of the copyright */
	क्रम (i = EEPROM_COPYRIGHT;
	    i < (EEPROM_COPYRIGHT + EEPROM_COPYRIGHT_LEN); i++)
		अगर (e[i] < 0x20 || e[i] > 0x7E)
			अवरोध;
	अगर ( i != EEPROM_COPYRIGHT &&
	    i != EEPROM_COPYRIGHT + EEPROM_COPYRIGHT_LEN && e[i] == '\0')
		DPRINTK("eeprom: copyright = \"%s\"\n",
		    (अक्षर *) &e[EEPROM_COPYRIGHT]);
	अन्यथा
		DPRINTK("eeprom: copyright not found\n");
#पूर्ण_अगर
	/* Validate checksum */
	क्रम (i = s = 0; i < EEPROM_CHECKSUM; i++)
		s += e[i];
	s &= 0xFF;
	अगर (s != e[EEPROM_CHECKSUM]) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): EEPROM checksum bad "
		    "(wanted 0x%02X, got 0x%02X)\n", lanai->number,
		    (अचिन्हित पूर्णांक) s, (अचिन्हित पूर्णांक) e[EEPROM_CHECKSUM]);
		वापस -EIO;
	पूर्ण
	s ^= 0xFF;
	अगर (s != e[EEPROM_CHECKSUM_REV]) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): EEPROM inverse checksum "
		    "bad (wanted 0x%02X, got 0x%02X)\n", lanai->number,
		    (अचिन्हित पूर्णांक) s, (अचिन्हित पूर्णांक) e[EEPROM_CHECKSUM_REV]);
		वापस -EIO;
	पूर्ण
	/* Verअगरy MAC address */
	क्रम (i = 0; i < 6; i++)
		अगर ((e[EEPROM_MAC + i] ^ e[EEPROM_MAC_REV + i]) != 0xFF) अणु
			prपूर्णांकk(KERN_ERR DEV_LABEL
			    "(itf %d) : EEPROM MAC addresses don't match "
			    "(0x%02X, inverse 0x%02X)\n", lanai->number,
			    (अचिन्हित पूर्णांक) e[EEPROM_MAC + i],
			    (अचिन्हित पूर्णांक) e[EEPROM_MAC_REV + i]);
			वापस -EIO;
		पूर्ण
	DPRINTK("eeprom: MAC address = %pM\n", &e[EEPROM_MAC]);
	/* Verअगरy serial number */
	lanai->serialno = eeprom_be4(lanai, EEPROM_SERIAL);
	v = eeprom_be4(lanai, EEPROM_SERIAL_REV);
	अगर ((lanai->serialno ^ v) != 0xFFFFFFFF) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): EEPROM serial numbers "
		    "don't match (0x%08X, inverse 0x%08X)\n", lanai->number,
		    (अचिन्हित पूर्णांक) lanai->serialno, (अचिन्हित पूर्णांक) v);
		वापस -EIO;
	पूर्ण
	DPRINTK("eeprom: Serial number = %d\n", (अचिन्हित पूर्णांक) lanai->serialno);
	/* Verअगरy magic number */
	lanai->magicno = eeprom_be4(lanai, EEPROM_MAGIC);
	v = eeprom_be4(lanai, EEPROM_MAGIC_REV);
	अगर ((lanai->magicno ^ v) != 0xFFFFFFFF) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): EEPROM magic numbers "
		    "don't match (0x%08X, inverse 0x%08X)\n", lanai->number,
		    lanai->magicno, v);
		वापस -EIO;
	पूर्ण
	DPRINTK("eeprom: Magic number = 0x%08X\n", lanai->magicno);
	अगर (lanai->magicno != EEPROM_MAGIC_VALUE)
		prपूर्णांकk(KERN_WARNING DEV_LABEL "(itf %d): warning - EEPROM "
		    "magic not what expected (got 0x%08X, not 0x%08X)\n",
		    lanai->number, (अचिन्हित पूर्णांक) lanai->magicno,
		    (अचिन्हित पूर्णांक) EEPROM_MAGIC_VALUE);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* READ_EEPROM */

अटल अंतरभूत स्थिर u8 *eeprom_mac(स्थिर काष्ठा lanai_dev *lanai)
अणु
	वापस &lanai->eeprom[EEPROM_MAC];
पूर्ण

/* -------------------- INTERRUPT HANDLING UTILITIES: */

/* Interrupt types */
#घोषणा INT_STATS	(0x00000002)	/* Statistics counter overflow */
#घोषणा INT_SOOL	(0x00000004)	/* SOOL changed state */
#घोषणा INT_LOCD	(0x00000008)	/* LOCD changed state */
#घोषणा INT_LED		(0x00000010)	/* LED (HAPPI) changed state */
#घोषणा INT_GPIN	(0x00000020)	/* GPIN changed state */
#घोषणा INT_PING	(0x00000040)	/* PING_COUNT fulfilled */
#घोषणा INT_WAKE	(0x00000080)	/* Lanai wants bus */
#घोषणा INT_CBR0	(0x00000100)	/* CBR sched hit VCI 0 */
#घोषणा INT_LOCK	(0x00000200)	/* Service list overflow */
#घोषणा INT_MISMATCH	(0x00000400)	/* TX magic list mismatch */
#घोषणा INT_AAL0_STR	(0x00000800)	/* Non-AAL5 buffer half filled */
#घोषणा INT_AAL0	(0x00001000)	/* Non-AAL5 data available */
#घोषणा INT_SERVICE	(0x00002000)	/* Service list entries available */
#घोषणा INT_TABORTSENT	(0x00004000)	/* Target पात sent by lanai */
#घोषणा INT_TABORTBM	(0x00008000)	/* Abort rcv'd as bus master */
#घोषणा INT_TIMEOUTBM	(0x00010000)	/* No response to bus master */
#घोषणा INT_PCIPARITY	(0x00020000)	/* Parity error on PCI */

/* Sets of the above */
#घोषणा INT_ALL		(0x0003FFFE)	/* All पूर्णांकerrupts */
#घोषणा INT_STATUS	(0x0000003C)	/* Some status pin changed */
#घोषणा INT_DMASHUT	(0x00038000)	/* DMA engine got shut करोwn */
#घोषणा INT_SEGSHUT	(0x00000700)	/* Segmentation got shut करोwn */

अटल अंतरभूत u32 पूर्णांकr_pending(स्थिर काष्ठा lanai_dev *lanai)
अणु
	वापस reg_पढ़ो(lanai, IntStatusMasked_Reg);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकr_enable(स्थिर काष्ठा lanai_dev *lanai, u32 i)
अणु
	reg_ग_लिखो(lanai, i, IntControlEna_Reg);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकr_disable(स्थिर काष्ठा lanai_dev *lanai, u32 i)
अणु
	reg_ग_लिखो(lanai, i, IntControlDis_Reg);
पूर्ण

/* -------------------- CARD/PCI STATUS: */

अटल व्योम status_message(पूर्णांक itf, स्थिर अक्षर *name, पूर्णांक status)
अणु
	अटल स्थिर अक्षर *onoff[2] = अणु "off to on", "on to off" पूर्ण;
	prपूर्णांकk(KERN_INFO DEV_LABEL "(itf %d): %s changed from %s\n",
	    itf, name, onoff[!status]);
पूर्ण

अटल व्योम lanai_check_status(काष्ठा lanai_dev *lanai)
अणु
	u32 new = reg_पढ़ो(lanai, Status_Reg);
	u32 changes = new ^ lanai->status;
	lanai->status = new;
#घोषणा e(flag, name) \
		अगर (changes & flag) \
			status_message(lanai->number, name, new & flag)
	e(STATUS_SOOL, "SOOL");
	e(STATUS_LOCD, "LOCD");
	e(STATUS_LED, "LED");
	e(STATUS_GPIN, "GPIN");
#अघोषित e
पूर्ण

अटल व्योम pcistatus_got(पूर्णांक itf, स्थिर अक्षर *name)
अणु
	prपूर्णांकk(KERN_INFO DEV_LABEL "(itf %d): PCI got %s error\n", itf, name);
पूर्ण

अटल व्योम pcistatus_check(काष्ठा lanai_dev *lanai, पूर्णांक clearonly)
अणु
	u16 s;
	पूर्णांक result;
	result = pci_पढ़ो_config_word(lanai->pci, PCI_STATUS, &s);
	अगर (result != PCIBIOS_SUCCESSFUL) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't read PCI_STATUS: "
		    "%d\n", lanai->number, result);
		वापस;
	पूर्ण
	s &= PCI_STATUS_DETECTED_PARITY | PCI_STATUS_SIG_SYSTEM_ERROR |
	    PCI_STATUS_REC_MASTER_ABORT | PCI_STATUS_REC_TARGET_ABORT |
	    PCI_STATUS_SIG_TARGET_ABORT | PCI_STATUS_PARITY;
	अगर (s == 0)
		वापस;
	result = pci_ग_लिखो_config_word(lanai->pci, PCI_STATUS, s);
	अगर (result != PCIBIOS_SUCCESSFUL)
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't write PCI_STATUS: "
		    "%d\n", lanai->number, result);
	अगर (clearonly)
		वापस;
#घोषणा e(flag, name, stat) \
		अगर (s & flag) अणु \
			pcistatus_got(lanai->number, name); \
			++lanai->stats.pcierr_##stat; \
		पूर्ण
	e(PCI_STATUS_DETECTED_PARITY, "parity", parity_detect);
	e(PCI_STATUS_SIG_SYSTEM_ERROR, "signalled system", serr_set);
	e(PCI_STATUS_REC_MASTER_ABORT, "master", master_पात);
	e(PCI_STATUS_REC_TARGET_ABORT, "master target", m_target_पात);
	e(PCI_STATUS_SIG_TARGET_ABORT, "slave", s_target_पात);
	e(PCI_STATUS_PARITY, "master parity", master_parity);
#अघोषित e
पूर्ण

/* -------------------- VCC TX BUFFER UTILITIES: */

/* space left in tx buffer in bytes */
अटल अंतरभूत पूर्णांक vcc_tx_space(स्थिर काष्ठा lanai_vcc *lvcc, पूर्णांक endptr)
अणु
	पूर्णांक r;
	r = endptr * 16;
	r -= ((अचिन्हित दीर्घ) lvcc->tx.buf.ptr) -
	    ((अचिन्हित दीर्घ) lvcc->tx.buf.start);
	r -= 16;	/* Leave "bubble" - अगर start==end it looks empty */
	अगर (r < 0)
		r += lanai_buf_size(&lvcc->tx.buf);
	वापस r;
पूर्ण

/* test अगर VCC is currently backlogged */
अटल अंतरभूत पूर्णांक vcc_is_backlogged(स्थिर काष्ठा lanai_vcc *lvcc)
अणु
	वापस !skb_queue_empty(&lvcc->tx.backlog);
पूर्ण

/* Bit fields in the segmentation buffer descriptor */
#घोषणा DESCRIPTOR_MAGIC	(0xD0000000)
#घोषणा DESCRIPTOR_AAL5		(0x00008000)
#घोषणा DESCRIPTOR_AAL5_STREAM	(0x00004000)
#घोषणा DESCRIPTOR_CLP		(0x00002000)

/* Add 32-bit descriptor with its padding */
अटल अंतरभूत व्योम vcc_tx_add_aal5_descriptor(काष्ठा lanai_vcc *lvcc,
	u32 flags, पूर्णांक len)
अणु
	पूर्णांक pos;
	APRINTK((((अचिन्हित दीर्घ) lvcc->tx.buf.ptr) & 15) == 0,
	    "vcc_tx_add_aal5_descriptor: bad ptr=%p\n", lvcc->tx.buf.ptr);
	lvcc->tx.buf.ptr += 4;	/* Hope the values REALLY करोn't matter */
	pos = ((अचिन्हित अक्षर *) lvcc->tx.buf.ptr) -
	    (अचिन्हित अक्षर *) lvcc->tx.buf.start;
	APRINTK((pos & ~0x0001FFF0) == 0,
	    "vcc_tx_add_aal5_descriptor: bad pos (%d) before, vci=%d, "
	    "start,ptr,end=%p,%p,%p\n", pos, lvcc->vci,
	    lvcc->tx.buf.start, lvcc->tx.buf.ptr, lvcc->tx.buf.end);
	pos = (pos + len) & (lanai_buf_size(&lvcc->tx.buf) - 1);
	APRINTK((pos & ~0x0001FFF0) == 0,
	    "vcc_tx_add_aal5_descriptor: bad pos (%d) after, vci=%d, "
	    "start,ptr,end=%p,%p,%p\n", pos, lvcc->vci,
	    lvcc->tx.buf.start, lvcc->tx.buf.ptr, lvcc->tx.buf.end);
	lvcc->tx.buf.ptr[-1] =
	    cpu_to_le32(DESCRIPTOR_MAGIC | DESCRIPTOR_AAL5 |
	    ((lvcc->tx.aपंचांगvcc->aपंचांग_options & ATM_ATMOPT_CLP) ?
	    DESCRIPTOR_CLP : 0) | flags | pos >> 4);
	अगर (lvcc->tx.buf.ptr >= lvcc->tx.buf.end)
		lvcc->tx.buf.ptr = lvcc->tx.buf.start;
पूर्ण

/* Add 32-bit AAL5 trailer and leave room क्रम its CRC */
अटल अंतरभूत व्योम vcc_tx_add_aal5_trailer(काष्ठा lanai_vcc *lvcc,
	पूर्णांक len, पूर्णांक cpi, पूर्णांक uu)
अणु
	APRINTK((((अचिन्हित दीर्घ) lvcc->tx.buf.ptr) & 15) == 8,
	    "vcc_tx_add_aal5_trailer: bad ptr=%p\n", lvcc->tx.buf.ptr);
	lvcc->tx.buf.ptr += 2;
	lvcc->tx.buf.ptr[-2] = cpu_to_be32((uu << 24) | (cpi << 16) | len);
	अगर (lvcc->tx.buf.ptr >= lvcc->tx.buf.end)
		lvcc->tx.buf.ptr = lvcc->tx.buf.start;
पूर्ण

अटल अंतरभूत व्योम vcc_tx_स_नकल(काष्ठा lanai_vcc *lvcc,
	स्थिर अचिन्हित अक्षर *src, पूर्णांक n)
अणु
	अचिन्हित अक्षर *e;
	पूर्णांक m;
	e = ((अचिन्हित अक्षर *) lvcc->tx.buf.ptr) + n;
	m = e - (अचिन्हित अक्षर *) lvcc->tx.buf.end;
	अगर (m < 0)
		m = 0;
	स_नकल(lvcc->tx.buf.ptr, src, n - m);
	अगर (m != 0) अणु
		स_नकल(lvcc->tx.buf.start, src + n - m, m);
		e = ((अचिन्हित अक्षर *) lvcc->tx.buf.start) + m;
	पूर्ण
	lvcc->tx.buf.ptr = (u32 *) e;
पूर्ण

अटल अंतरभूत व्योम vcc_tx_memzero(काष्ठा lanai_vcc *lvcc, पूर्णांक n)
अणु
	अचिन्हित अक्षर *e;
	पूर्णांक m;
	अगर (n == 0)
		वापस;
	e = ((अचिन्हित अक्षर *) lvcc->tx.buf.ptr) + n;
	m = e - (अचिन्हित अक्षर *) lvcc->tx.buf.end;
	अगर (m < 0)
		m = 0;
	स_रखो(lvcc->tx.buf.ptr, 0, n - m);
	अगर (m != 0) अणु
		स_रखो(lvcc->tx.buf.start, 0, m);
		e = ((अचिन्हित अक्षर *) lvcc->tx.buf.start) + m;
	पूर्ण
	lvcc->tx.buf.ptr = (u32 *) e;
पूर्ण

/* Update "butt" रेजिस्टर to specअगरy new WritePtr */
अटल अंतरभूत व्योम lanai_endtx(काष्ठा lanai_dev *lanai,
	स्थिर काष्ठा lanai_vcc *lvcc)
अणु
	पूर्णांक i, ptr = ((अचिन्हित अक्षर *) lvcc->tx.buf.ptr) -
	    (अचिन्हित अक्षर *) lvcc->tx.buf.start;
	APRINTK((ptr & ~0x0001FFF0) == 0,
	    "lanai_endtx: bad ptr (%d), vci=%d, start,ptr,end=%p,%p,%p\n",
	    ptr, lvcc->vci, lvcc->tx.buf.start, lvcc->tx.buf.ptr,
	    lvcc->tx.buf.end);

	/*
	 * Since the "butt register" is a shared resounce on the card we
	 * serialize all accesses to it through this spinlock.  This is
	 * mostly just paranoia since the रेजिस्टर is rarely "busy" anyway
	 * but is needed क्रम correctness.
	 */
	spin_lock(&lanai->endtxlock);
	/*
	 * We need to check अगर the "butt busy" bit is set beक्रमe
	 * updating the butt रेजिस्टर.  In theory this should
	 * never happen because the ATM card is plenty fast at
	 * updating the रेजिस्टर.  Still, we should make sure
	 */
	क्रम (i = 0; reg_पढ़ो(lanai, Status_Reg) & STATUS_BUTTBUSY; i++) अणु
		अगर (unlikely(i > 50)) अणु
			prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): butt register "
			    "always busy!\n", lanai->number);
			अवरोध;
		पूर्ण
		udelay(5);
	पूर्ण
	/*
	 * Beक्रमe we tall the card to start work we need to be sure 100% of
	 * the info in the service buffer has been written beक्रमe we tell
	 * the card about it
	 */
	wmb();
	reg_ग_लिखो(lanai, (ptr << 12) | lvcc->vci, Butt_Reg);
	spin_unlock(&lanai->endtxlock);
पूर्ण

/*
 * Add one AAL5 PDU to lvcc's transmit buffer.  Caller garauntees there's
 * space available.  "pdusize" is the number of bytes the PDU will take
 */
अटल व्योम lanai_send_one_aal5(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_vcc *lvcc, काष्ठा sk_buff *skb, पूर्णांक pdusize)
अणु
	पूर्णांक pad;
	APRINTK(pdusize == aal5_size(skb->len),
	    "lanai_send_one_aal5: wrong size packet (%d != %d)\n",
	    pdusize, aal5_size(skb->len));
	vcc_tx_add_aal5_descriptor(lvcc, 0, pdusize);
	pad = pdusize - skb->len - 8;
	APRINTK(pad >= 0, "pad is negative (%d)\n", pad);
	APRINTK(pad < 48, "pad is too big (%d)\n", pad);
	vcc_tx_स_नकल(lvcc, skb->data, skb->len);
	vcc_tx_memzero(lvcc, pad);
	vcc_tx_add_aal5_trailer(lvcc, skb->len, 0, 0);
	lanai_endtx(lanai, lvcc);
	lanai_मुक्त_skb(lvcc->tx.aपंचांगvcc, skb);
	atomic_inc(&lvcc->tx.aपंचांगvcc->stats->tx);
पूर्ण

/* Try to fill the buffer - करोn't call unless there is backlog */
अटल व्योम vcc_tx_unqueue_aal5(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_vcc *lvcc, पूर्णांक endptr)
अणु
	पूर्णांक n;
	काष्ठा sk_buff *skb;
	पूर्णांक space = vcc_tx_space(lvcc, endptr);
	APRINTK(vcc_is_backlogged(lvcc),
	    "vcc_tx_unqueue() called with empty backlog (vci=%d)\n",
	    lvcc->vci);
	जबतक (space >= 64) अणु
		skb = skb_dequeue(&lvcc->tx.backlog);
		अगर (skb == शून्य)
			जाओ no_backlog;
		n = aal5_size(skb->len);
		अगर (n + 16 > space) अणु
			/* No room क्रम this packet - put it back on queue */
			skb_queue_head(&lvcc->tx.backlog, skb);
			वापस;
		पूर्ण
		lanai_send_one_aal5(lanai, lvcc, skb, n);
		space -= n + 16;
	पूर्ण
	अगर (!vcc_is_backlogged(lvcc)) अणु
	    no_backlog:
		__clear_bit(lvcc->vci, lanai->backlog_vccs);
	पूर्ण
पूर्ण

/* Given an skb that we want to transmit either send it now or queue */
अटल व्योम vcc_tx_aal5(काष्ठा lanai_dev *lanai, काष्ठा lanai_vcc *lvcc,
	काष्ठा sk_buff *skb)
अणु
	पूर्णांक space, n;
	अगर (vcc_is_backlogged(lvcc))		/* Alपढ़ोy backlogged */
		जाओ queue_it;
	space = vcc_tx_space(lvcc,
		    TXREADPTR_GET_PTR(cardvcc_पढ़ो(lvcc, vcc_txपढ़ोptr)));
	n = aal5_size(skb->len);
	APRINTK(n + 16 >= 64, "vcc_tx_aal5: n too small (%d)\n", n);
	अगर (space < n + 16) अणु			/* No space क्रम this PDU */
		__set_bit(lvcc->vci, lanai->backlog_vccs);
	    queue_it:
		skb_queue_tail(&lvcc->tx.backlog, skb);
		वापस;
	पूर्ण
	lanai_send_one_aal5(lanai, lvcc, skb, n);
पूर्ण

अटल व्योम vcc_tx_unqueue_aal0(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_vcc *lvcc, पूर्णांक endptr)
अणु
	prपूर्णांकk(KERN_INFO DEV_LABEL
	    ": vcc_tx_unqueue_aal0: not implemented\n");
पूर्ण

अटल व्योम vcc_tx_aal0(काष्ठा lanai_dev *lanai, काष्ठा lanai_vcc *lvcc,
	काष्ठा sk_buff *skb)
अणु
	prपूर्णांकk(KERN_INFO DEV_LABEL ": vcc_tx_aal0: not implemented\n");
	/* Remember to increment lvcc->tx.aपंचांगvcc->stats->tx */
	lanai_मुक्त_skb(lvcc->tx.aपंचांगvcc, skb);
पूर्ण

/* -------------------- VCC RX BUFFER UTILITIES: */

/* unlike the _tx_ cousins, this करोesn't update ptr */
अटल अंतरभूत व्योम vcc_rx_स_नकल(अचिन्हित अक्षर *dest,
	स्थिर काष्ठा lanai_vcc *lvcc, पूर्णांक n)
अणु
	पूर्णांक m = ((स्थिर अचिन्हित अक्षर *) lvcc->rx.buf.ptr) + n -
	    ((स्थिर अचिन्हित अक्षर *) (lvcc->rx.buf.end));
	अगर (m < 0)
		m = 0;
	स_नकल(dest, lvcc->rx.buf.ptr, n - m);
	स_नकल(dest + n - m, lvcc->rx.buf.start, m);
	/* Make sure that these copies करोn't get reordered */
	barrier();
पूर्ण

/* Receive AAL5 data on a VCC with a particular endptr */
अटल व्योम vcc_rx_aal5(काष्ठा lanai_vcc *lvcc, पूर्णांक endptr)
अणु
	पूर्णांक size;
	काष्ठा sk_buff *skb;
	स्थिर u32 *x;
	u32 *end = &lvcc->rx.buf.start[endptr * 4];
	पूर्णांक n = ((अचिन्हित दीर्घ) end) - ((अचिन्हित दीर्घ) lvcc->rx.buf.ptr);
	अगर (n < 0)
		n += lanai_buf_size(&lvcc->rx.buf);
	APRINTK(n >= 0 && n < lanai_buf_size(&lvcc->rx.buf) && !(n & 15),
	    "vcc_rx_aal5: n out of range (%d/%zu)\n",
	    n, lanai_buf_size(&lvcc->rx.buf));
	/* Recover the second-to-last word to get true pdu length */
	अगर ((x = &end[-2]) < lvcc->rx.buf.start)
		x = &lvcc->rx.buf.end[-2];
	/*
	 * Beक्रमe we actually पढ़ो from the buffer, make sure the memory
	 * changes have arrived
	 */
	rmb();
	size = be32_to_cpup(x) & 0xffff;
	अगर (unlikely(n != aal5_size(size))) अणु
		/* Make sure size matches padding */
		prपूर्णांकk(KERN_INFO DEV_LABEL "(itf %d): Got bad AAL5 length "
		    "on vci=%d - size=%d n=%d\n",
		    lvcc->rx.aपंचांगvcc->dev->number, lvcc->vci, size, n);
		lvcc->stats.x.aal5.rx_badlen++;
		जाओ out;
	पूर्ण
	skb = aपंचांग_alloc_अक्षरge(lvcc->rx.aपंचांगvcc, size, GFP_ATOMIC);
	अगर (unlikely(skb == शून्य)) अणु
		lvcc->stats.rx_nomem++;
		जाओ out;
	पूर्ण
	skb_put(skb, size);
	vcc_rx_स_नकल(skb->data, lvcc, size);
	ATM_SKB(skb)->vcc = lvcc->rx.aपंचांगvcc;
	__net_बारtamp(skb);
	lvcc->rx.aपंचांगvcc->push(lvcc->rx.aपंचांगvcc, skb);
	atomic_inc(&lvcc->rx.aपंचांगvcc->stats->rx);
    out:
	lvcc->rx.buf.ptr = end;
	cardvcc_ग_लिखो(lvcc, endptr, vcc_rxपढ़ोptr);
पूर्ण

अटल व्योम vcc_rx_aal0(काष्ठा lanai_dev *lanai)
अणु
	prपूर्णांकk(KERN_INFO DEV_LABEL ": vcc_rx_aal0: not implemented\n");
	/* Remember to get पढ़ो_lock(&vcc_sklist_lock) जबतक looking up VC */
	/* Remember to increment lvcc->rx.aपंचांगvcc->stats->rx */
पूर्ण

/* -------------------- MANAGING HOST-BASED VCC TABLE: */

/* Decide whether to use vदो_स्मृति or get_zeroed_page क्रम VCC table */
#अगर (NUM_VCI * BITS_PER_LONG) <= PAGE_SIZE
#घोषणा VCCTABLE_GETFREEPAGE
#अन्यथा
#समावेश <linux/vदो_स्मृति.h>
#पूर्ण_अगर

अटल पूर्णांक vcc_table_allocate(काष्ठा lanai_dev *lanai)
अणु
#अगर_घोषित VCCTABLE_GETFREEPAGE
	APRINTK((lanai->num_vci) * माप(काष्ठा lanai_vcc *) <= PAGE_SIZE,
	    "vcc table > PAGE_SIZE!");
	lanai->vccs = (काष्ठा lanai_vcc **) get_zeroed_page(GFP_KERNEL);
	वापस (lanai->vccs == शून्य) ? -ENOMEM : 0;
#अन्यथा
	पूर्णांक bytes = (lanai->num_vci) * माप(काष्ठा lanai_vcc *);
	lanai->vccs = vzalloc(bytes);
	अगर (unlikely(lanai->vccs == शून्य))
		वापस -ENOMEM;
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम vcc_table_deallocate(स्थिर काष्ठा lanai_dev *lanai)
अणु
#अगर_घोषित VCCTABLE_GETFREEPAGE
	मुक्त_page((अचिन्हित दीर्घ) lanai->vccs);
#अन्यथा
	vमुक्त(lanai->vccs);
#पूर्ण_अगर
पूर्ण

/* Allocate a fresh lanai_vcc, with the appropriate things cleared */
अटल अंतरभूत काष्ठा lanai_vcc *new_lanai_vcc(व्योम)
अणु
	काष्ठा lanai_vcc *lvcc;
	lvcc =  kzalloc(माप(*lvcc), GFP_KERNEL);
	अगर (likely(lvcc != शून्य)) अणु
		skb_queue_head_init(&lvcc->tx.backlog);
#अगर_घोषित DEBUG
		lvcc->vci = -1;
#पूर्ण_अगर
	पूर्ण
	वापस lvcc;
पूर्ण

अटल पूर्णांक lanai_get_sized_buffer(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_buffer *buf, पूर्णांक max_sdu, पूर्णांक multiplier,
	स्थिर अक्षर *name)
अणु
	पूर्णांक size;
	अगर (unlikely(max_sdu < 1))
		max_sdu = 1;
	max_sdu = aal5_size(max_sdu);
	size = (max_sdu + 16) * multiplier + 16;
	lanai_buf_allocate(buf, size, max_sdu + 32, lanai->pci);
	अगर (unlikely(buf->start == शून्य))
		वापस -ENOMEM;
	अगर (unlikely(lanai_buf_size(buf) < size))
		prपूर्णांकk(KERN_WARNING DEV_LABEL "(itf %d): wanted %d bytes "
		    "for %s buffer, got only %zu\n", lanai->number, size,
		    name, lanai_buf_size(buf));
	DPRINTK("Allocated %zu byte %s buffer\n", lanai_buf_size(buf), name);
	वापस 0;
पूर्ण

/* Setup a RX buffer क्रम a currently unbound AAL5 vci */
अटल अंतरभूत पूर्णांक lanai_setup_rx_vci_aal5(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_vcc *lvcc, स्थिर काष्ठा aपंचांग_qos *qos)
अणु
	वापस lanai_get_sized_buffer(lanai, &lvcc->rx.buf,
	    qos->rxtp.max_sdu, AAL5_RX_MULTIPLIER, "RX");
पूर्ण

/* Setup a TX buffer क्रम a currently unbound AAL5 vci */
अटल पूर्णांक lanai_setup_tx_vci(काष्ठा lanai_dev *lanai, काष्ठा lanai_vcc *lvcc,
	स्थिर काष्ठा aपंचांग_qos *qos)
अणु
	पूर्णांक max_sdu, multiplier;
	अगर (qos->aal == ATM_AAL0) अणु
		lvcc->tx.unqueue = vcc_tx_unqueue_aal0;
		max_sdu = ATM_CELL_SIZE - 1;
		multiplier = AAL0_TX_MULTIPLIER;
	पूर्ण अन्यथा अणु
		lvcc->tx.unqueue = vcc_tx_unqueue_aal5;
		max_sdu = qos->txtp.max_sdu;
		multiplier = AAL5_TX_MULTIPLIER;
	पूर्ण
	वापस lanai_get_sized_buffer(lanai, &lvcc->tx.buf, max_sdu,
	    multiplier, "TX");
पूर्ण

अटल अंतरभूत व्योम host_vcc_bind(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_vcc *lvcc, vci_t vci)
अणु
	अगर (lvcc->vbase != शून्य)
		वापस;    /* We alपढ़ोy were bound in the other direction */
	DPRINTK("Binding vci %d\n", vci);
#अगर_घोषित USE_POWERDOWN
	अगर (lanai->nbound++ == 0) अणु
		DPRINTK("Coming out of powerdown\n");
		lanai->conf1 &= ~CONFIG1_POWERDOWN;
		conf1_ग_लिखो(lanai);
		conf2_ग_लिखो(lanai);
	पूर्ण
#पूर्ण_अगर
	lvcc->vbase = cardvcc_addr(lanai, vci);
	lanai->vccs[lvcc->vci = vci] = lvcc;
पूर्ण

अटल अंतरभूत व्योम host_vcc_unbind(काष्ठा lanai_dev *lanai,
	काष्ठा lanai_vcc *lvcc)
अणु
	अगर (lvcc->vbase == शून्य)
		वापस;	/* This vcc was never bound */
	DPRINTK("Unbinding vci %d\n", lvcc->vci);
	lvcc->vbase = शून्य;
	lanai->vccs[lvcc->vci] = शून्य;
#अगर_घोषित USE_POWERDOWN
	अगर (--lanai->nbound == 0) अणु
		DPRINTK("Going into powerdown\n");
		lanai->conf1 |= CONFIG1_POWERDOWN;
		conf1_ग_लिखो(lanai);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* -------------------- RESET CARD: */

अटल व्योम lanai_reset(काष्ठा lanai_dev *lanai)
अणु
	prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): *NOT* resetting - not "
	    "implemented\n", lanai->number);
	/* TODO */
	/* The following is just a hack until we ग_लिखो the real
	 * resetter - at least ack whatever पूर्णांकerrupt sent us
	 * here
	 */
	reg_ग_लिखो(lanai, INT_ALL, IntAck_Reg);
	lanai->stats.card_reset++;
पूर्ण

/* -------------------- SERVICE LIST UTILITIES: */

/*
 * Allocate service buffer and tell card about it
 */
अटल पूर्णांक service_buffer_allocate(काष्ठा lanai_dev *lanai)
अणु
	lanai_buf_allocate(&lanai->service, SERVICE_ENTRIES * 4, 8,
	    lanai->pci);
	अगर (unlikely(lanai->service.start == शून्य))
		वापस -ENOMEM;
	DPRINTK("allocated service buffer at %p, size %zu(%d)\n",
	    lanai->service.start,
	    lanai_buf_size(&lanai->service),
	    lanai_buf_size_carकरोrder(&lanai->service));
	/* Clear ServWrite रेजिस्टर to be safe */
	reg_ग_लिखो(lanai, 0, ServWrite_Reg);
	/* ServiceStuff रेजिस्टर contains size and address of buffer */
	reg_ग_लिखो(lanai,
	    SSTUFF_SET_SIZE(lanai_buf_size_carकरोrder(&lanai->service)) |
	    SSTUFF_SET_ADDR(lanai->service.dmaaddr),
	    ServiceStuff_Reg);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम service_buffer_deallocate(काष्ठा lanai_dev *lanai)
अणु
	lanai_buf_deallocate(&lanai->service, lanai->pci);
पूर्ण

/* Bitfields in service list */
#घोषणा SERVICE_TX	(0x80000000)	/* Was from transmission */
#घोषणा SERVICE_TRASH	(0x40000000)	/* RXed PDU was trashed */
#घोषणा SERVICE_CRCERR	(0x20000000)	/* RXed PDU had CRC error */
#घोषणा SERVICE_CI	(0x10000000)	/* RXed PDU had CI set */
#घोषणा SERVICE_CLP	(0x08000000)	/* RXed PDU had CLP set */
#घोषणा SERVICE_STREAM	(0x04000000)	/* RX Stream mode */
#घोषणा SERVICE_GET_VCI(x) (((x)>>16)&0x3FF)
#घोषणा SERVICE_GET_END(x) ((x)&0x1FFF)

/* Handle one thing from the service list - वापसs true अगर it marked a
 * VCC पढ़ोy क्रम xmit
 */
अटल पूर्णांक handle_service(काष्ठा lanai_dev *lanai, u32 s)
अणु
	vci_t vci = SERVICE_GET_VCI(s);
	काष्ठा lanai_vcc *lvcc;
	पढ़ो_lock(&vcc_sklist_lock);
	lvcc = lanai->vccs[vci];
	अगर (unlikely(lvcc == शून्य)) अणु
		पढ़ो_unlock(&vcc_sklist_lock);
		DPRINTK("(itf %d) got service entry 0x%X for nonexistent "
		    "vcc %d\n", lanai->number, (अचिन्हित पूर्णांक) s, vci);
		अगर (s & SERVICE_TX)
			lanai->stats.service_notx++;
		अन्यथा
			lanai->stats.service_norx++;
		वापस 0;
	पूर्ण
	अगर (s & SERVICE_TX) अणु			/* segmentation पूर्णांकerrupt */
		अगर (unlikely(lvcc->tx.aपंचांगvcc == शून्य)) अणु
			पढ़ो_unlock(&vcc_sklist_lock);
			DPRINTK("(itf %d) got service entry 0x%X for non-TX "
			    "vcc %d\n", lanai->number, (अचिन्हित पूर्णांक) s, vci);
			lanai->stats.service_notx++;
			वापस 0;
		पूर्ण
		__set_bit(vci, lanai->transmit_पढ़ोy);
		lvcc->tx.endptr = SERVICE_GET_END(s);
		पढ़ो_unlock(&vcc_sklist_lock);
		वापस 1;
	पूर्ण
	अगर (unlikely(lvcc->rx.aपंचांगvcc == शून्य)) अणु
		पढ़ो_unlock(&vcc_sklist_lock);
		DPRINTK("(itf %d) got service entry 0x%X for non-RX "
		    "vcc %d\n", lanai->number, (अचिन्हित पूर्णांक) s, vci);
		lanai->stats.service_norx++;
		वापस 0;
	पूर्ण
	अगर (unlikely(lvcc->rx.aपंचांगvcc->qos.aal != ATM_AAL5)) अणु
		पढ़ो_unlock(&vcc_sklist_lock);
		DPRINTK("(itf %d) got RX service entry 0x%X for non-AAL5 "
		    "vcc %d\n", lanai->number, (अचिन्हित पूर्णांक) s, vci);
		lanai->stats.service_rxnotaal5++;
		atomic_inc(&lvcc->rx.aपंचांगvcc->stats->rx_err);
		वापस 0;
	पूर्ण
	अगर (likely(!(s & (SERVICE_TRASH | SERVICE_STREAM | SERVICE_CRCERR)))) अणु
		vcc_rx_aal5(lvcc, SERVICE_GET_END(s));
		पढ़ो_unlock(&vcc_sklist_lock);
		वापस 0;
	पूर्ण
	अगर (s & SERVICE_TRASH) अणु
		पूर्णांक bytes;
		पढ़ो_unlock(&vcc_sklist_lock);
		DPRINTK("got trashed rx pdu on vci %d\n", vci);
		atomic_inc(&lvcc->rx.aपंचांगvcc->stats->rx_err);
		lvcc->stats.x.aal5.service_trash++;
		bytes = (SERVICE_GET_END(s) * 16) -
		    (((अचिन्हित दीर्घ) lvcc->rx.buf.ptr) -
		    ((अचिन्हित दीर्घ) lvcc->rx.buf.start)) + 47;
		अगर (bytes < 0)
			bytes += lanai_buf_size(&lvcc->rx.buf);
		lanai->stats.ovfl_trash += (bytes / 48);
		वापस 0;
	पूर्ण
	अगर (s & SERVICE_STREAM) अणु
		पढ़ो_unlock(&vcc_sklist_lock);
		atomic_inc(&lvcc->rx.aपंचांगvcc->stats->rx_err);
		lvcc->stats.x.aal5.service_stream++;
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): Got AAL5 stream "
		    "PDU on VCI %d!\n", lanai->number, vci);
		lanai_reset(lanai);
		वापस 0;
	पूर्ण
	DPRINTK("got rx crc error on vci %d\n", vci);
	atomic_inc(&lvcc->rx.aपंचांगvcc->stats->rx_err);
	lvcc->stats.x.aal5.service_rxcrc++;
	lvcc->rx.buf.ptr = &lvcc->rx.buf.start[SERVICE_GET_END(s) * 4];
	cardvcc_ग_लिखो(lvcc, SERVICE_GET_END(s), vcc_rxपढ़ोptr);
	पढ़ो_unlock(&vcc_sklist_lock);
	वापस 0;
पूर्ण

/* Try transmitting on all VCIs that we marked पढ़ोy to serve */
अटल व्योम iter_transmit(काष्ठा lanai_dev *lanai, vci_t vci)
अणु
	काष्ठा lanai_vcc *lvcc = lanai->vccs[vci];
	अगर (vcc_is_backlogged(lvcc))
		lvcc->tx.unqueue(lanai, lvcc, lvcc->tx.endptr);
पूर्ण

/* Run service queue -- called from पूर्णांकerrupt context or with
 * पूर्णांकerrupts otherwise disabled and with the lanai->servicelock
 * lock held
 */
अटल व्योम run_service(काष्ठा lanai_dev *lanai)
अणु
	पूर्णांक ntx = 0;
	u32 wreg = reg_पढ़ो(lanai, ServWrite_Reg);
	स्थिर u32 *end = lanai->service.start + wreg;
	जबतक (lanai->service.ptr != end) अणु
		ntx += handle_service(lanai,
		    le32_to_cpup(lanai->service.ptr++));
		अगर (lanai->service.ptr >= lanai->service.end)
			lanai->service.ptr = lanai->service.start;
	पूर्ण
	reg_ग_लिखो(lanai, wreg, ServRead_Reg);
	अगर (ntx != 0) अणु
		पढ़ो_lock(&vcc_sklist_lock);
		vci_bitfield_iterate(lanai, lanai->transmit_पढ़ोy,
		    iter_transmit);
		biपंचांगap_zero(lanai->transmit_पढ़ोy, NUM_VCI);
		पढ़ो_unlock(&vcc_sklist_lock);
	पूर्ण
पूर्ण

/* -------------------- GATHER STATISTICS: */

अटल व्योम get_statistics(काष्ठा lanai_dev *lanai)
अणु
	u32 statreg = reg_पढ़ो(lanai, Statistics_Reg);
	lanai->stats.aपंचांग_ovfl += STATS_GET_FIFO_OVFL(statreg);
	lanai->stats.hec_err += STATS_GET_HEC_ERR(statreg);
	lanai->stats.vci_trash += STATS_GET_BAD_VCI(statreg);
	lanai->stats.ovfl_trash += STATS_GET_BUF_OVFL(statreg);
पूर्ण

/* -------------------- POLLING TIMER: */

#अगर_अघोषित DEBUG_RW
/* Try to undequeue 1 backlogged vcc */
अटल व्योम iter_dequeue(काष्ठा lanai_dev *lanai, vci_t vci)
अणु
	काष्ठा lanai_vcc *lvcc = lanai->vccs[vci];
	पूर्णांक endptr;
	अगर (lvcc == शून्य || lvcc->tx.aपंचांगvcc == शून्य ||
	    !vcc_is_backlogged(lvcc)) अणु
		__clear_bit(vci, lanai->backlog_vccs);
		वापस;
	पूर्ण
	endptr = TXREADPTR_GET_PTR(cardvcc_पढ़ो(lvcc, vcc_txपढ़ोptr));
	lvcc->tx.unqueue(lanai, lvcc, endptr);
पूर्ण
#पूर्ण_अगर /* !DEBUG_RW */

अटल व्योम lanai_समयd_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा lanai_dev *lanai = from_समयr(lanai, t, समयr);
#अगर_अघोषित DEBUG_RW
	अचिन्हित दीर्घ flags;
#अगर_घोषित USE_POWERDOWN
	अगर (lanai->conf1 & CONFIG1_POWERDOWN)
		वापस;
#पूर्ण_अगर /* USE_POWERDOWN */
	local_irq_save(flags);
	/* If we can grab the spinlock, check अगर any services need to be run */
	अगर (spin_trylock(&lanai->servicelock)) अणु
		run_service(lanai);
		spin_unlock(&lanai->servicelock);
	पूर्ण
	/* ...and see अगर any backlogged VCs can make progress */
	/* unक्रमtunately linux has no पढ़ो_trylock() currently */
	पढ़ो_lock(&vcc_sklist_lock);
	vci_bitfield_iterate(lanai, lanai->backlog_vccs, iter_dequeue);
	पढ़ो_unlock(&vcc_sklist_lock);
	local_irq_restore(flags);

	get_statistics(lanai);
#पूर्ण_अगर /* !DEBUG_RW */
	mod_समयr(&lanai->समयr, jअगरfies + LANAI_POLL_PERIOD);
पूर्ण

अटल अंतरभूत व्योम lanai_समयd_poll_start(काष्ठा lanai_dev *lanai)
अणु
	समयr_setup(&lanai->समयr, lanai_समयd_poll, 0);
	lanai->समयr.expires = jअगरfies + LANAI_POLL_PERIOD;
	add_समयr(&lanai->समयr);
पूर्ण

अटल अंतरभूत व्योम lanai_समयd_poll_stop(काष्ठा lanai_dev *lanai)
अणु
	del_समयr_sync(&lanai->समयr);
पूर्ण

/* -------------------- INTERRUPT SERVICE: */

अटल अंतरभूत व्योम lanai_पूर्णांक_1(काष्ठा lanai_dev *lanai, u32 reason)
अणु
	u32 ack = 0;
	अगर (reason & INT_SERVICE) अणु
		ack = INT_SERVICE;
		spin_lock(&lanai->servicelock);
		run_service(lanai);
		spin_unlock(&lanai->servicelock);
	पूर्ण
	अगर (reason & (INT_AAL0_STR | INT_AAL0)) अणु
		ack |= reason & (INT_AAL0_STR | INT_AAL0);
		vcc_rx_aal0(lanai);
	पूर्ण
	/* The rest of the पूर्णांकerrupts are pretty rare */
	अगर (ack == reason)
		जाओ करोne;
	अगर (reason & INT_STATS) अणु
		reason &= ~INT_STATS;	/* No need to ack */
		get_statistics(lanai);
	पूर्ण
	अगर (reason & INT_STATUS) अणु
		ack |= reason & INT_STATUS;
		lanai_check_status(lanai);
	पूर्ण
	अगर (unlikely(reason & INT_DMASHUT)) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): driver error - DMA "
		    "shutdown, reason=0x%08X, address=0x%08X\n",
		    lanai->number, (अचिन्हित पूर्णांक) (reason & INT_DMASHUT),
		    (अचिन्हित पूर्णांक) reg_पढ़ो(lanai, DMA_Addr_Reg));
		अगर (reason & INT_TABORTBM) अणु
			lanai_reset(lanai);
			वापस;
		पूर्ण
		ack |= (reason & INT_DMASHUT);
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): re-enabling DMA\n",
		    lanai->number);
		conf1_ग_लिखो(lanai);
		lanai->stats.dma_reenable++;
		pcistatus_check(lanai, 0);
	पूर्ण
	अगर (unlikely(reason & INT_TABORTSENT)) अणु
		ack |= (reason & INT_TABORTSENT);
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): sent PCI target abort\n",
		    lanai->number);
		pcistatus_check(lanai, 0);
	पूर्ण
	अगर (unlikely(reason & INT_SEGSHUT)) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): driver error - "
		    "segmentation shutdown, reason=0x%08X\n", lanai->number,
		    (अचिन्हित पूर्णांक) (reason & INT_SEGSHUT));
		lanai_reset(lanai);
		वापस;
	पूर्ण
	अगर (unlikely(reason & (INT_PING | INT_WAKE))) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): driver error - "
		    "unexpected interrupt 0x%08X, resetting\n",
		    lanai->number,
		    (अचिन्हित पूर्णांक) (reason & (INT_PING | INT_WAKE)));
		lanai_reset(lanai);
		वापस;
	पूर्ण
#अगर_घोषित DEBUG
	अगर (unlikely(ack != reason)) अणु
		DPRINTK("unacked ints: 0x%08X\n",
		    (अचिन्हित पूर्णांक) (reason & ~ack));
		ack = reason;
	पूर्ण
#पूर्ण_अगर
   करोne:
	अगर (ack != 0)
		reg_ग_लिखो(lanai, ack, IntAck_Reg);
पूर्ण

अटल irqवापस_t lanai_पूर्णांक(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा lanai_dev *lanai = devid;
	u32 reason;

#अगर_घोषित USE_POWERDOWN
	/*
	 * If we're powered down we shouldn't be generating any पूर्णांकerrupts -
	 * so assume that this is a shared पूर्णांकerrupt line and it's क्रम someone
	 * अन्यथा
	 */
	अगर (unlikely(lanai->conf1 & CONFIG1_POWERDOWN))
		वापस IRQ_NONE;
#पूर्ण_अगर

	reason = पूर्णांकr_pending(lanai);
	अगर (reason == 0)
		वापस IRQ_NONE;	/* Must be क्रम someone अन्यथा */

	करो अणु
		अगर (unlikely(reason == 0xFFFFFFFF))
			अवरोध;		/* Maybe we've been unplugged? */
		lanai_पूर्णांक_1(lanai, reason);
		reason = पूर्णांकr_pending(lanai);
	पूर्ण जबतक (reason != 0);

	वापस IRQ_HANDLED;
पूर्ण

/* TODO - it would be nice अगर we could use the "delayed interrupt" प्रणाली
 *   to some advantage
 */

/* -------------------- CHECK BOARD ID/REV: */

/*
 * The board id and revision are stored both in the reset रेजिस्टर and
 * in the PCI configuration space - the करोcumentation says to check
 * each of them.  If revp!=शून्य we store the revision there
 */
अटल पूर्णांक check_board_id_and_rev(स्थिर अक्षर *name, u32 val, पूर्णांक *revp)
अणु
	DPRINTK("%s says board_id=%d, board_rev=%d\n", name,
		(पूर्णांक) RESET_GET_BOARD_ID(val),
		(पूर्णांक) RESET_GET_BOARD_REV(val));
	अगर (RESET_GET_BOARD_ID(val) != BOARD_ID_LANAI256) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL ": Found %s board-id %d -- not a "
		    "Lanai 25.6\n", name, (पूर्णांक) RESET_GET_BOARD_ID(val));
		वापस -ENODEV;
	पूर्ण
	अगर (revp != शून्य)
		*revp = RESET_GET_BOARD_REV(val);
	वापस 0;
पूर्ण

/* -------------------- PCI INITIALIZATION/SHUTDOWN: */

अटल पूर्णांक lanai_pci_start(काष्ठा lanai_dev *lanai)
अणु
	काष्ठा pci_dev *pci = lanai->pci;
	पूर्णांक result;

	अगर (pci_enable_device(pci) != 0) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't enable "
		    "PCI device", lanai->number);
		वापस -ENXIO;
	पूर्ण
	pci_set_master(pci);
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32)) != 0) अणु
		prपूर्णांकk(KERN_WARNING DEV_LABEL
		    "(itf %d): No suitable DMA available.\n", lanai->number);
		वापस -EBUSY;
	पूर्ण
	result = check_board_id_and_rev("PCI", pci->subप्रणाली_device, शून्य);
	अगर (result != 0)
		वापस result;
	/* Set latency समयr to zero as per lanai करोcs */
	result = pci_ग_लिखो_config_byte(pci, PCI_LATENCY_TIMER, 0);
	अगर (result != PCIBIOS_SUCCESSFUL) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't write "
		    "PCI_LATENCY_TIMER: %d\n", lanai->number, result);
		वापस -EINVAL;
	पूर्ण
	pcistatus_check(lanai, 1);
	pcistatus_check(lanai, 0);
	वापस 0;
पूर्ण

/* -------------------- VPI/VCI ALLOCATION: */

/*
 * We _can_ use VCI==0 क्रम normal traffic, but only क्रम UBR (or we'll
 * get a CBRZERO पूर्णांकerrupt), and we can use it only अगर no one is receiving
 * AAL0 traffic (since they will use the same queue) - according to the
 * करोcs we shouldn't even use it क्रम AAL0 traffic
 */
अटल अंतरभूत पूर्णांक vci0_is_ok(काष्ठा lanai_dev *lanai,
	स्थिर काष्ठा aपंचांग_qos *qos)
अणु
	अगर (qos->txtp.traffic_class == ATM_CBR || qos->aal == ATM_AAL0)
		वापस 0;
	अगर (qos->rxtp.traffic_class != ATM_NONE) अणु
		अगर (lanai->naal0 != 0)
			वापस 0;
		lanai->conf2 |= CONFIG2_VCI0_NORMAL;
		conf2_ग_लिखो_अगर_घातerup(lanai);
	पूर्ण
	वापस 1;
पूर्ण

/* वापस true अगर vci is currently unused, or अगर requested qos is
 * compatible
 */
अटल पूर्णांक vci_is_ok(काष्ठा lanai_dev *lanai, vci_t vci,
	स्थिर काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	स्थिर काष्ठा aपंचांग_qos *qos = &aपंचांगvcc->qos;
	स्थिर काष्ठा lanai_vcc *lvcc = lanai->vccs[vci];
	अगर (vci == 0 && !vci0_is_ok(lanai, qos))
		वापस 0;
	अगर (unlikely(lvcc != शून्य)) अणु
		अगर (qos->rxtp.traffic_class != ATM_NONE &&
		    lvcc->rx.aपंचांगvcc != शून्य && lvcc->rx.aपंचांगvcc != aपंचांगvcc)
			वापस 0;
		अगर (qos->txtp.traffic_class != ATM_NONE &&
		    lvcc->tx.aपंचांगvcc != शून्य && lvcc->tx.aपंचांगvcc != aपंचांगvcc)
			वापस 0;
		अगर (qos->txtp.traffic_class == ATM_CBR &&
		    lanai->cbrvcc != शून्य && lanai->cbrvcc != aपंचांगvcc)
			वापस 0;
	पूर्ण
	अगर (qos->aal == ATM_AAL0 && lanai->naal0 == 0 &&
	    qos->rxtp.traffic_class != ATM_NONE) अणु
		स्थिर काष्ठा lanai_vcc *vci0 = lanai->vccs[0];
		अगर (vci0 != शून्य && vci0->rx.aपंचांगvcc != शून्य)
			वापस 0;
		lanai->conf2 &= ~CONFIG2_VCI0_NORMAL;
		conf2_ग_लिखो_अगर_घातerup(lanai);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक lanai_normalize_ci(काष्ठा lanai_dev *lanai,
	स्थिर काष्ठा aपंचांग_vcc *aपंचांगvcc, लघु *vpip, vci_t *vcip)
अणु
	चयन (*vpip) अणु
		हाल ATM_VPI_ANY:
			*vpip = 0;
			fallthrough;
		हाल 0:
			अवरोध;
		शेष:
			वापस -EADDRINUSE;
	पूर्ण
	चयन (*vcip) अणु
		हाल ATM_VCI_ANY:
			क्रम (*vcip = ATM_NOT_RSV_VCI; *vcip < lanai->num_vci;
			    (*vcip)++)
				अगर (vci_is_ok(lanai, *vcip, aपंचांगvcc))
					वापस 0;
			वापस -EADDRINUSE;
		शेष:
			अगर (*vcip >= lanai->num_vci || *vcip < 0 ||
			    !vci_is_ok(lanai, *vcip, aपंचांगvcc))
				वापस -EADDRINUSE;
	पूर्ण
	वापस 0;
पूर्ण

/* -------------------- MANAGE CBR: */

/*
 * CBR ICG is stored as a fixed-poपूर्णांक number with 4 fractional bits.
 * Note that storing a number greater than 2046.0 will result in
 * incorrect shaping
 */
#घोषणा CBRICG_FRAC_BITS	(4)
#घोषणा CBRICG_MAX		(2046 << CBRICG_FRAC_BITS)

/*
 * ICG is related to PCR with the क्रमmula PCR = MAXPCR / (ICG + 1)
 * where MAXPCR is (according to the करोcs) 25600000/(54*8),
 * which is equal to (3125<<9)/27.
 *
 * Solving क्रम ICG, we get:
 *    ICG = MAXPCR/PCR - 1
 *    ICG = (3125<<9)/(27*PCR) - 1
 *    ICG = ((3125<<9) - (27*PCR)) / (27*PCR)
 *
 * The end result is supposed to be a fixed-poपूर्णांक number with FRAC_BITS
 * bits of a fractional part, so we keep everything in the numerator
 * shअगरted by that much as we compute
 *
 */
अटल पूर्णांक pcr_to_cbricg(स्थिर काष्ठा aपंचांग_qos *qos)
अणु
	पूर्णांक roundकरोwn = 0;	/* 1 = Round PCR करोwn, i.e. round ICG _up_ */
	पूर्णांक x, icg, pcr = aपंचांग_pcr_goal(&qos->txtp);
	अगर (pcr == 0)		/* Use maximum bandwidth */
		वापस 0;
	अगर (pcr < 0) अणु
		roundकरोwn = 1;
		pcr = -pcr;
	पूर्ण
	x = pcr * 27;
	icg = (3125 << (9 + CBRICG_FRAC_BITS)) - (x << CBRICG_FRAC_BITS);
	अगर (roundकरोwn)
		icg += x - 1;
	icg /= x;
	अगर (icg > CBRICG_MAX)
		icg = CBRICG_MAX;
	DPRINTK("pcr_to_cbricg: pcr=%d rounddown=%c icg=%d\n",
	    pcr, roundकरोwn ? 'Y' : 'N', icg);
	वापस icg;
पूर्ण

अटल अंतरभूत व्योम lanai_cbr_setup(काष्ठा lanai_dev *lanai)
अणु
	reg_ग_लिखो(lanai, pcr_to_cbricg(&lanai->cbrvcc->qos), CBR_ICG_Reg);
	reg_ग_लिखो(lanai, lanai->cbrvcc->vci, CBR_PTR_Reg);
	lanai->conf2 |= CONFIG2_CBR_ENABLE;
	conf2_ग_लिखो(lanai);
पूर्ण

अटल अंतरभूत व्योम lanai_cbr_shutकरोwn(काष्ठा lanai_dev *lanai)
अणु
	lanai->conf2 &= ~CONFIG2_CBR_ENABLE;
	conf2_ग_लिखो(lanai);
पूर्ण

/* -------------------- OPERATIONS: */

/* setup a newly detected device */
अटल पूर्णांक lanai_dev_खोलो(काष्ठा aपंचांग_dev *aपंचांगdev)
अणु
	काष्ठा lanai_dev *lanai = (काष्ठा lanai_dev *) aपंचांगdev->dev_data;
	अचिन्हित दीर्घ raw_base;
	पूर्णांक result;

	DPRINTK("In lanai_dev_open()\n");
	/* Basic device fields */
	lanai->number = aपंचांगdev->number;
	lanai->num_vci = NUM_VCI;
	biपंचांगap_zero(lanai->backlog_vccs, NUM_VCI);
	biपंचांगap_zero(lanai->transmit_पढ़ोy, NUM_VCI);
	lanai->naal0 = 0;
#अगर_घोषित USE_POWERDOWN
	lanai->nbound = 0;
#पूर्ण_अगर
	lanai->cbrvcc = शून्य;
	स_रखो(&lanai->stats, 0, माप lanai->stats);
	spin_lock_init(&lanai->endtxlock);
	spin_lock_init(&lanai->servicelock);
	aपंचांगdev->ci_range.vpi_bits = 0;
	aपंचांगdev->ci_range.vci_bits = 0;
	जबतक (1 << aपंचांगdev->ci_range.vci_bits < lanai->num_vci)
		aपंचांगdev->ci_range.vci_bits++;
	aपंचांगdev->link_rate = ATM_25_PCR;

	/* 3.2: PCI initialization */
	अगर ((result = lanai_pci_start(lanai)) != 0)
		जाओ error;
	raw_base = lanai->pci->resource[0].start;
	lanai->base = (bus_addr_t) ioremap(raw_base, LANAI_MAPPING_SIZE);
	अगर (lanai->base == शून्य) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL ": couldn't remap I/O space\n");
		result = -ENOMEM;
		जाओ error_pci;
	पूर्ण
	/* 3.3: Reset lanai and PHY */
	reset_board(lanai);
	lanai->conf1 = reg_पढ़ो(lanai, Config1_Reg);
	lanai->conf1 &= ~(CONFIG1_GPOUT1 | CONFIG1_POWERDOWN |
	    CONFIG1_MASK_LEDMODE);
	lanai->conf1 |= CONFIG1_SET_LEDMODE(LEDMODE_NOT_SOOL);
	reg_ग_लिखो(lanai, lanai->conf1 | CONFIG1_GPOUT1, Config1_Reg);
	udelay(1000);
	conf1_ग_लिखो(lanai);

	/*
	 * 3.4: Turn on endian mode क्रम big-endian hardware
	 *   We करोn't actually want to करो this - the actual bit fields
	 *   in the endian रेजिस्टर are not करोcumented anywhere.
	 *   Instead we करो the bit-flipping ourselves on big-endian
	 *   hardware.
	 *
	 * 3.5: get the board ID/rev by पढ़ोing the reset रेजिस्टर
	 */
	result = check_board_id_and_rev("register",
	    reg_पढ़ो(lanai, Reset_Reg), &lanai->board_rev);
	अगर (result != 0)
		जाओ error_unmap;

	/* 3.6: पढ़ो EEPROM */
	अगर ((result = eeprom_पढ़ो(lanai)) != 0)
		जाओ error_unmap;
	अगर ((result = eeprom_validate(lanai)) != 0)
		जाओ error_unmap;

	/* 3.7: re-reset PHY, करो loopback tests, setup PHY */
	reg_ग_लिखो(lanai, lanai->conf1 | CONFIG1_GPOUT1, Config1_Reg);
	udelay(1000);
	conf1_ग_लिखो(lanai);
	/* TODO - loopback tests */
	lanai->conf1 |= (CONFIG1_GPOUT2 | CONFIG1_GPOUT3 | CONFIG1_DMA_ENABLE);
	conf1_ग_लिखो(lanai);

	/* 3.8/3.9: test and initialize card SRAM */
	अगर ((result = sram_test_and_clear(lanai)) != 0)
		जाओ error_unmap;

	/* 3.10: initialize lanai रेजिस्टरs */
	lanai->conf1 |= CONFIG1_DMA_ENABLE;
	conf1_ग_लिखो(lanai);
	अगर ((result = service_buffer_allocate(lanai)) != 0)
		जाओ error_unmap;
	अगर ((result = vcc_table_allocate(lanai)) != 0)
		जाओ error_service;
	lanai->conf2 = (lanai->num_vci >= 512 ? CONFIG2_HOWMANY : 0) |
	    CONFIG2_HEC_DROP |	/* ??? */ CONFIG2_PTI7_MODE;
	conf2_ग_लिखो(lanai);
	reg_ग_लिखो(lanai, TX_FIFO_DEPTH, TxDepth_Reg);
	reg_ग_लिखो(lanai, 0, CBR_ICG_Reg);	/* CBR शेषs to no limit */
	अगर ((result = request_irq(lanai->pci->irq, lanai_पूर्णांक, IRQF_SHARED,
	    DEV_LABEL, lanai)) != 0) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL ": can't allocate interrupt\n");
		जाओ error_vcctable;
	पूर्ण
	mb();				/* Make sure that all that made it */
	पूर्णांकr_enable(lanai, INT_ALL & ~(INT_PING | INT_WAKE));
	/* 3.11: initialize loop mode (i.e. turn looping off) */
	lanai->conf1 = (lanai->conf1 & ~CONFIG1_MASK_LOOPMODE) |
	    CONFIG1_SET_LOOPMODE(LOOPMODE_NORMAL) |
	    CONFIG1_GPOUT2 | CONFIG1_GPOUT3;
	conf1_ग_लिखो(lanai);
	lanai->status = reg_पढ़ो(lanai, Status_Reg);
	/* We're now करोne initializing this card */
#अगर_घोषित USE_POWERDOWN
	lanai->conf1 |= CONFIG1_POWERDOWN;
	conf1_ग_लिखो(lanai);
#पूर्ण_अगर
	स_नकल(aपंचांगdev->esi, eeprom_mac(lanai), ESI_LEN);
	lanai_समयd_poll_start(lanai);
	prपूर्णांकk(KERN_NOTICE DEV_LABEL "(itf %d): rev.%d, base=%p, irq=%u "
		"(%pMF)\n", lanai->number, (पूर्णांक) lanai->pci->revision,
		lanai->base, lanai->pci->irq, aपंचांगdev->esi);
	prपूर्णांकk(KERN_NOTICE DEV_LABEL "(itf %d): LANAI%s, serialno=%u(0x%X), "
	    "board_rev=%d\n", lanai->number,
	    lanai->type==lanai2 ? "2" : "HB", (अचिन्हित पूर्णांक) lanai->serialno,
	    (अचिन्हित पूर्णांक) lanai->serialno, lanai->board_rev);
	वापस 0;

    error_vcctable:
	vcc_table_deallocate(lanai);
    error_service:
	service_buffer_deallocate(lanai);
    error_unmap:
	reset_board(lanai);
#अगर_घोषित USE_POWERDOWN
	lanai->conf1 = reg_पढ़ो(lanai, Config1_Reg) | CONFIG1_POWERDOWN;
	conf1_ग_लिखो(lanai);
#पूर्ण_अगर
	iounmap(lanai->base);
	lanai->base = शून्य;
    error_pci:
	pci_disable_device(lanai->pci);
    error:
	वापस result;
पूर्ण

/* called when device is being shutकरोwn, and all vcc's are gone - higher
 * levels will deallocate the aपंचांग device क्रम us
 */
अटल व्योम lanai_dev_बंद(काष्ठा aपंचांग_dev *aपंचांगdev)
अणु
	काष्ठा lanai_dev *lanai = (काष्ठा lanai_dev *) aपंचांगdev->dev_data;
	अगर (lanai->base==शून्य)
		वापस;
	prपूर्णांकk(KERN_INFO DEV_LABEL "(itf %d): shutting down interface\n",
	    lanai->number);
	lanai_समयd_poll_stop(lanai);
#अगर_घोषित USE_POWERDOWN
	lanai->conf1 = reg_पढ़ो(lanai, Config1_Reg) & ~CONFIG1_POWERDOWN;
	conf1_ग_लिखो(lanai);
#पूर्ण_अगर
	पूर्णांकr_disable(lanai, INT_ALL);
	मुक्त_irq(lanai->pci->irq, lanai);
	reset_board(lanai);
#अगर_घोषित USE_POWERDOWN
	lanai->conf1 |= CONFIG1_POWERDOWN;
	conf1_ग_लिखो(lanai);
#पूर्ण_अगर
	pci_disable_device(lanai->pci);
	vcc_table_deallocate(lanai);
	service_buffer_deallocate(lanai);
	iounmap(lanai->base);
	kमुक्त(lanai);
पूर्ण

/* बंद a vcc */
अटल व्योम lanai_बंद(काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	काष्ठा lanai_vcc *lvcc = (काष्ठा lanai_vcc *) aपंचांगvcc->dev_data;
	काष्ठा lanai_dev *lanai = (काष्ठा lanai_dev *) aपंचांगvcc->dev->dev_data;
	अगर (lvcc == शून्य)
		वापस;
	clear_bit(ATM_VF_READY, &aपंचांगvcc->flags);
	clear_bit(ATM_VF_PARTIAL, &aपंचांगvcc->flags);
	अगर (lvcc->rx.aपंचांगvcc == aपंचांगvcc) अणु
		lanai_shutकरोwn_rx_vci(lvcc);
		अगर (aपंचांगvcc->qos.aal == ATM_AAL0) अणु
			अगर (--lanai->naal0 <= 0)
				aal0_buffer_मुक्त(lanai);
		पूर्ण अन्यथा
			lanai_buf_deallocate(&lvcc->rx.buf, lanai->pci);
		lvcc->rx.aपंचांगvcc = शून्य;
	पूर्ण
	अगर (lvcc->tx.aपंचांगvcc == aपंचांगvcc) अणु
		अगर (aपंचांगvcc == lanai->cbrvcc) अणु
			अगर (lvcc->vbase != शून्य)
				lanai_cbr_shutकरोwn(lanai);
			lanai->cbrvcc = शून्य;
		पूर्ण
		lanai_shutकरोwn_tx_vci(lanai, lvcc);
		lanai_buf_deallocate(&lvcc->tx.buf, lanai->pci);
		lvcc->tx.aपंचांगvcc = शून्य;
	पूर्ण
	अगर (--lvcc->nref == 0) अणु
		host_vcc_unbind(lanai, lvcc);
		kमुक्त(lvcc);
	पूर्ण
	aपंचांगvcc->dev_data = शून्य;
	clear_bit(ATM_VF_ADDR, &aपंचांगvcc->flags);
पूर्ण

/* खोलो a vcc on the card to vpi/vci */
अटल पूर्णांक lanai_खोलो(काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	काष्ठा lanai_dev *lanai;
	काष्ठा lanai_vcc *lvcc;
	पूर्णांक result = 0;
	पूर्णांक vci = aपंचांगvcc->vci;
	लघु vpi = aपंचांगvcc->vpi;
	/* we करोn't support partial open - it's not really useful anyway */
	अगर ((test_bit(ATM_VF_PARTIAL, &aपंचांगvcc->flags)) ||
	    (vpi == ATM_VPI_UNSPEC) || (vci == ATM_VCI_UNSPEC))
		वापस -EINVAL;
	lanai = (काष्ठा lanai_dev *) aपंचांगvcc->dev->dev_data;
	result = lanai_normalize_ci(lanai, aपंचांगvcc, &vpi, &vci);
	अगर (unlikely(result != 0))
		जाओ out;
	set_bit(ATM_VF_ADDR, &aपंचांगvcc->flags);
	अगर (aपंचांगvcc->qos.aal != ATM_AAL0 && aपंचांगvcc->qos.aal != ATM_AAL5)
		वापस -EINVAL;
	DPRINTK(DEV_LABEL "(itf %d): open %d.%d\n", lanai->number,
	    (पूर्णांक) vpi, vci);
	lvcc = lanai->vccs[vci];
	अगर (lvcc == शून्य) अणु
		lvcc = new_lanai_vcc();
		अगर (unlikely(lvcc == शून्य))
			वापस -ENOMEM;
		aपंचांगvcc->dev_data = lvcc;
	पूर्ण
	lvcc->nref++;
	अगर (aपंचांगvcc->qos.rxtp.traffic_class != ATM_NONE) अणु
		APRINTK(lvcc->rx.aपंचांगvcc == शून्य, "rx.atmvcc!=NULL, vci=%d\n",
		    vci);
		अगर (aपंचांगvcc->qos.aal == ATM_AAL0) अणु
			अगर (lanai->naal0 == 0)
				result = aal0_buffer_allocate(lanai);
		पूर्ण अन्यथा
			result = lanai_setup_rx_vci_aal5(
			    lanai, lvcc, &aपंचांगvcc->qos);
		अगर (unlikely(result != 0))
			जाओ out_मुक्त;
		lvcc->rx.aपंचांगvcc = aपंचांगvcc;
		lvcc->stats.rx_nomem = 0;
		lvcc->stats.x.aal5.rx_badlen = 0;
		lvcc->stats.x.aal5.service_trash = 0;
		lvcc->stats.x.aal5.service_stream = 0;
		lvcc->stats.x.aal5.service_rxcrc = 0;
		अगर (aपंचांगvcc->qos.aal == ATM_AAL0)
			lanai->naal0++;
	पूर्ण
	अगर (aपंचांगvcc->qos.txtp.traffic_class != ATM_NONE) अणु
		APRINTK(lvcc->tx.aपंचांगvcc == शून्य, "tx.atmvcc!=NULL, vci=%d\n",
		    vci);
		result = lanai_setup_tx_vci(lanai, lvcc, &aपंचांगvcc->qos);
		अगर (unlikely(result != 0))
			जाओ out_मुक्त;
		lvcc->tx.aपंचांगvcc = aपंचांगvcc;
		अगर (aपंचांगvcc->qos.txtp.traffic_class == ATM_CBR) अणु
			APRINTK(lanai->cbrvcc == शून्य,
			    "cbrvcc!=NULL, vci=%d\n", vci);
			lanai->cbrvcc = aपंचांगvcc;
		पूर्ण
	पूर्ण
	host_vcc_bind(lanai, lvcc, vci);
	/*
	 * Make sure everything made it to RAM beक्रमe we tell the card about
	 * the VCC
	 */
	wmb();
	अगर (aपंचांगvcc == lvcc->rx.aपंचांगvcc)
		host_vcc_start_rx(lvcc);
	अगर (aपंचांगvcc == lvcc->tx.aपंचांगvcc) अणु
		host_vcc_start_tx(lvcc);
		अगर (lanai->cbrvcc == aपंचांगvcc)
			lanai_cbr_setup(lanai);
	पूर्ण
	set_bit(ATM_VF_READY, &aपंचांगvcc->flags);
	वापस 0;
    out_मुक्त:
	lanai_बंद(aपंचांगvcc);
    out:
	वापस result;
पूर्ण

अटल पूर्णांक lanai_send(काष्ठा aपंचांग_vcc *aपंचांगvcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा lanai_vcc *lvcc = (काष्ठा lanai_vcc *) aपंचांगvcc->dev_data;
	काष्ठा lanai_dev *lanai = (काष्ठा lanai_dev *) aपंचांगvcc->dev->dev_data;
	अचिन्हित दीर्घ flags;
	अगर (unlikely(lvcc == शून्य || lvcc->vbase == शून्य ||
	      lvcc->tx.aपंचांगvcc != aपंचांगvcc))
		जाओ einval;
#अगर_घोषित DEBUG
	अगर (unlikely(skb == शून्य)) अणु
		DPRINTK("lanai_send: skb==NULL for vci=%d\n", aपंचांगvcc->vci);
		जाओ einval;
	पूर्ण
	अगर (unlikely(lanai == शून्य)) अणु
		DPRINTK("lanai_send: lanai==NULL for vci=%d\n", aपंचांगvcc->vci);
		जाओ einval;
	पूर्ण
#पूर्ण_अगर
	ATM_SKB(skb)->vcc = aपंचांगvcc;
	चयन (aपंचांगvcc->qos.aal) अणु
		हाल ATM_AAL5:
			पढ़ो_lock_irqsave(&vcc_sklist_lock, flags);
			vcc_tx_aal5(lanai, lvcc, skb);
			पढ़ो_unlock_irqrestore(&vcc_sklist_lock, flags);
			वापस 0;
		हाल ATM_AAL0:
			अगर (unlikely(skb->len != ATM_CELL_SIZE-1))
				जाओ einval;
  /* NOTE - this next line is technically invalid - we haven't unshared skb */
			cpu_to_be32s((u32 *) skb->data);
			पढ़ो_lock_irqsave(&vcc_sklist_lock, flags);
			vcc_tx_aal0(lanai, lvcc, skb);
			पढ़ो_unlock_irqrestore(&vcc_sklist_lock, flags);
			वापस 0;
	पूर्ण
	DPRINTK("lanai_send: bad aal=%d on vci=%d\n", (पूर्णांक) aपंचांगvcc->qos.aal,
	    aपंचांगvcc->vci);
    einval:
	lanai_मुक्त_skb(aपंचांगvcc, skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक lanai_change_qos(काष्ठा aपंचांग_vcc *aपंचांगvcc,
	/*स्थिर*/ काष्ठा aपंचांग_qos *qos, पूर्णांक flags)
अणु
	वापस -EBUSY;		/* TODO: need to ग_लिखो this */
पूर्ण

#अगर_अघोषित CONFIG_PROC_FS
#घोषणा lanai_proc_पढ़ो शून्य
#अन्यथा
अटल पूर्णांक lanai_proc_पढ़ो(काष्ठा aपंचांग_dev *aपंचांगdev, loff_t *pos, अक्षर *page)
अणु
	काष्ठा lanai_dev *lanai = (काष्ठा lanai_dev *) aपंचांगdev->dev_data;
	loff_t left = *pos;
	काष्ठा lanai_vcc *lvcc;
	अगर (left-- == 0)
		वापस प्र_लिखो(page, DEV_LABEL "(itf %d): chip=LANAI%s, "
		    "serial=%u, magic=0x%08X, num_vci=%d\n",
		    aपंचांगdev->number, lanai->type==lanai2 ? "2" : "HB",
		    (अचिन्हित पूर्णांक) lanai->serialno,
		    (अचिन्हित पूर्णांक) lanai->magicno, lanai->num_vci);
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "revision: board=%d, pci_if=%d\n",
		    lanai->board_rev, (पूर्णांक) lanai->pci->revision);
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "EEPROM ESI: %pM\n",
		    &lanai->eeprom[EEPROM_MAC]);
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "status: SOOL=%d, LOCD=%d, LED=%d, "
		    "GPIN=%d\n", (lanai->status & STATUS_SOOL) ? 1 : 0,
		    (lanai->status & STATUS_LOCD) ? 1 : 0,
		    (lanai->status & STATUS_LED) ? 1 : 0,
		    (lanai->status & STATUS_GPIN) ? 1 : 0);
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "global buffer sizes: service=%zu, "
		    "aal0_rx=%zu\n", lanai_buf_size(&lanai->service),
		    lanai->naal0 ? lanai_buf_size(&lanai->aal0buf) : 0);
	अगर (left-- == 0) अणु
		get_statistics(lanai);
		वापस प्र_लिखो(page, "cells in error: overflow=%u, "
		    "closed_vci=%u, bad_HEC=%u, rx_fifo=%u\n",
		    lanai->stats.ovfl_trash, lanai->stats.vci_trash,
		    lanai->stats.hec_err, lanai->stats.aपंचांग_ovfl);
	पूर्ण
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "PCI errors: parity_detect=%u, "
		    "master_abort=%u, master_target_abort=%u,\n",
		    lanai->stats.pcierr_parity_detect,
		    lanai->stats.pcierr_serr_set,
		    lanai->stats.pcierr_m_target_पात);
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "            slave_target_abort=%u, "
		    "master_parity=%u\n", lanai->stats.pcierr_s_target_पात,
		    lanai->stats.pcierr_master_parity);
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "                     no_tx=%u, "
		    "no_rx=%u, bad_rx_aal=%u\n", lanai->stats.service_norx,
		    lanai->stats.service_notx,
		    lanai->stats.service_rxnotaal5);
	अगर (left-- == 0)
		वापस प्र_लिखो(page, "resets: dma=%u, card=%u\n",
		    lanai->stats.dma_reenable, lanai->stats.card_reset);
	/* At this poपूर्णांक, "left" should be the VCI we're looking क्रम */
	पढ़ो_lock(&vcc_sklist_lock);
	क्रम (; ; left++) अणु
		अगर (left >= NUM_VCI) अणु
			left = 0;
			जाओ out;
		पूर्ण
		अगर ((lvcc = lanai->vccs[left]) != शून्य)
			अवरोध;
		(*pos)++;
	पूर्ण
	/* Note that we re-use "left" here since we're करोne with it */
	left = प्र_लिखो(page, "VCI %4d: nref=%d, rx_nomem=%u",  (vci_t) left,
	    lvcc->nref, lvcc->stats.rx_nomem);
	अगर (lvcc->rx.aपंचांगvcc != शून्य) अणु
		left += प्र_लिखो(&page[left], ",\n          rx_AAL=%d",
		    lvcc->rx.aपंचांगvcc->qos.aal == ATM_AAL5 ? 5 : 0);
		अगर (lvcc->rx.aपंचांगvcc->qos.aal == ATM_AAL5)
			left += प्र_लिखो(&page[left], ", rx_buf_size=%zu, "
			    "rx_bad_len=%u,\n          rx_service_trash=%u, "
			    "rx_service_stream=%u, rx_bad_crc=%u",
			    lanai_buf_size(&lvcc->rx.buf),
			    lvcc->stats.x.aal5.rx_badlen,
			    lvcc->stats.x.aal5.service_trash,
			    lvcc->stats.x.aal5.service_stream,
			    lvcc->stats.x.aal5.service_rxcrc);
	पूर्ण
	अगर (lvcc->tx.aपंचांगvcc != शून्य)
		left += प्र_लिखो(&page[left], ",\n          tx_AAL=%d, "
		    "tx_buf_size=%zu, tx_qos=%cBR, tx_backlogged=%c",
		    lvcc->tx.aपंचांगvcc->qos.aal == ATM_AAL5 ? 5 : 0,
		    lanai_buf_size(&lvcc->tx.buf),
		    lvcc->tx.aपंचांगvcc == lanai->cbrvcc ? 'C' : 'U',
		    vcc_is_backlogged(lvcc) ? 'Y' : 'N');
	page[left++] = '\n';
	page[left] = '\0';
    out:
	पढ़ो_unlock(&vcc_sklist_lock);
	वापस left;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/* -------------------- HOOKS: */

अटल स्थिर काष्ठा aपंचांगdev_ops ops = अणु
	.dev_बंद	= lanai_dev_बंद,
	.खोलो		= lanai_खोलो,
	.बंद		= lanai_बंद,
	.send		= lanai_send,
	.phy_put	= शून्य,
	.phy_get	= शून्य,
	.change_qos	= lanai_change_qos,
	.proc_पढ़ो	= lanai_proc_पढ़ो,
	.owner		= THIS_MODULE
पूर्ण;

/* initialize one probed card */
अटल पूर्णांक lanai_init_one(काष्ठा pci_dev *pci,
			  स्थिर काष्ठा pci_device_id *ident)
अणु
	काष्ठा lanai_dev *lanai;
	काष्ठा aपंचांग_dev *aपंचांगdev;
	पूर्णांक result;

	lanai = kzalloc(माप(*lanai), GFP_KERNEL);
	अगर (lanai == शून्य) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL
		       ": couldn't allocate dev_data structure!\n");
		वापस -ENOMEM;
	पूर्ण

	aपंचांगdev = aपंचांग_dev_रेजिस्टर(DEV_LABEL, &pci->dev, &ops, -1, शून्य);
	अगर (aपंचांगdev == शून्य) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL
		    ": couldn't register atm device!\n");
		kमुक्त(lanai);
		वापस -EBUSY;
	पूर्ण

	aपंचांगdev->dev_data = lanai;
	lanai->pci = pci;
	lanai->type = (क्रमागत lanai_type) ident->device;

	result = lanai_dev_खोलो(aपंचांगdev);
	अगर (result != 0) अणु
		DPRINTK("lanai_start() failed, err=%d\n", -result);
		aपंचांग_dev_deरेजिस्टर(aपंचांगdev);
		kमुक्त(lanai);
	पूर्ण
	वापस result;
पूर्ण

अटल स्थिर काष्ठा pci_device_id lanai_pci_tbl[] = अणु
	अणु PCI_VDEVICE(EF, PCI_DEVICE_ID_EF_ATM_LANAI2) पूर्ण,
	अणु PCI_VDEVICE(EF, PCI_DEVICE_ID_EF_ATM_LANAIHB) पूर्ण,
	अणु 0, पूर्ण	/* terminal entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, lanai_pci_tbl);

अटल काष्ठा pci_driver lanai_driver = अणु
	.name     = DEV_LABEL,
	.id_table = lanai_pci_tbl,
	.probe    = lanai_init_one,
पूर्ण;

module_pci_driver(lanai_driver);

MODULE_AUTHOR("Mitchell Blank Jr <mitch@sfgoth.com>");
MODULE_DESCRIPTION("Efficient Networks Speedstream 3010 driver");
MODULE_LICENSE("GPL");
