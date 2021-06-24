<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *	Include file क्रम Alchemy Semiconductor's Au1550 Descriptor
 *	Based DMA Controller.
 *
 * Copyright 2004 Embedded Edge, LLC
 *	dan@embeddededge.com
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * Specअगरics क्रम the Au1xxx Descriptor-Based DMA Controller,
 * first seen in the AU1550 part.
 */
#अगर_अघोषित _AU1000_DBDMA_H_
#घोषणा _AU1000_DBDMA_H_

#अगर_अघोषित _LANGUAGE_ASSEMBLY

प्रकार अस्थिर काष्ठा dbdma_global अणु
	u32	ddma_config;
	u32	ddma_पूर्णांकstat;
	u32	ddma_throttle;
	u32	ddma_पूर्णांकen;
पूर्ण dbdma_global_t;

/* General Configuration. */
#घोषणा DDMA_CONFIG_AF		(1 << 2)
#घोषणा DDMA_CONFIG_AH		(1 << 1)
#घोषणा DDMA_CONFIG_AL		(1 << 0)

#घोषणा DDMA_THROTTLE_EN	(1 << 31)

/* The काष्ठाure of a DMA Channel. */
प्रकार अस्थिर काष्ठा au1xxx_dma_channel अणु
	u32	ddma_cfg;	/* See below */
	u32	ddma_desptr;	/* 32-byte aligned poपूर्णांकer to descriptor */
	u32	ddma_statptr;	/* word aligned poपूर्णांकer to status word */
	u32	ddma_dbell;	/* A ग_लिखो activates channel operation */
	u32	ddma_irq;	/* If bit 0 set, पूर्णांकerrupt pending */
	u32	ddma_stat;	/* See below */
	u32	ddma_bytecnt;	/* Byte count, valid only when chan idle */
	/* Reमुख्यder, up to the 256 byte boundary, is reserved. */
पूर्ण au1x_dma_chan_t;

#घोषणा DDMA_CFG_SED	(1 << 9)	/* source DMA level/edge detect */
#घोषणा DDMA_CFG_SP	(1 << 8)	/* source DMA polarity */
#घोषणा DDMA_CFG_DED	(1 << 7)	/* destination DMA level/edge detect */
#घोषणा DDMA_CFG_DP	(1 << 6)	/* destination DMA polarity */
#घोषणा DDMA_CFG_SYNC	(1 << 5)	/* Sync अटल bus controller */
#घोषणा DDMA_CFG_PPR	(1 << 4)	/* PCI posted पढ़ो/ग_लिखो control */
#घोषणा DDMA_CFG_DFN	(1 << 3)	/* Descriptor fetch non-coherent */
#घोषणा DDMA_CFG_SBE	(1 << 2)	/* Source big endian */
#घोषणा DDMA_CFG_DBE	(1 << 1)	/* Destination big endian */
#घोषणा DDMA_CFG_EN	(1 << 0)	/* Channel enable */

/*
 * Always set when descriptor processing करोne, regardless of
 * पूर्णांकerrupt enable state.  Reflected in global पूर्णांकstat, करोn't
 * clear this until global पूर्णांकstat is पढ़ो/used.
 */
#घोषणा DDMA_IRQ_IN	(1 << 0)

#घोषणा DDMA_STAT_DB	(1 << 2)	/* Doorbell pushed */
#घोषणा DDMA_STAT_V	(1 << 1)	/* Descriptor valid */
#घोषणा DDMA_STAT_H	(1 << 0)	/* Channel Halted */

/*
 * "Standard" DDMA Descriptor.
 * Must be 32-byte aligned.
 */
प्रकार अस्थिर काष्ठा au1xxx_ddma_desc अणु
	u32	dscr_cmd0;		/* See below */
	u32	dscr_cmd1;		/* See below */
	u32	dscr_source0;		/* source phys address */
	u32	dscr_source1;		/* See below */
	u32	dscr_dest0;		/* Destination address */
	u32	dscr_dest1;		/* See below */
	u32	dscr_stat;		/* completion status */
	u32	dscr_nxtptr;		/* Next descriptor poपूर्णांकer (mostly) */
	/*
	 * First 32 bytes are HW specअगरic!!!
	 * Let's have some SW data following -- make sure it's 32 bytes.
	 */
	u32	sw_status;
	u32	sw_context;
	u32	sw_reserved[6];
पूर्ण au1x_ddma_desc_t;

#घोषणा DSCR_CMD0_V		(1 << 31)	/* Descriptor valid */
#घोषणा DSCR_CMD0_MEM		(1 << 30)	/* mem-mem transfer */
#घोषणा DSCR_CMD0_SID_MASK	(0x1f << 25)	/* Source ID */
#घोषणा DSCR_CMD0_DID_MASK	(0x1f << 20)	/* Destination ID */
#घोषणा DSCR_CMD0_SW_MASK	(0x3 << 18)	/* Source Width */
#घोषणा DSCR_CMD0_DW_MASK	(0x3 << 16)	/* Destination Width */
#घोषणा DSCR_CMD0_ARB		(0x1 << 15)	/* Set क्रम Hi Pri */
#घोषणा DSCR_CMD0_DT_MASK	(0x3 << 13)	/* Descriptor Type */
#घोषणा DSCR_CMD0_SN		(0x1 << 12)	/* Source non-coherent */
#घोषणा DSCR_CMD0_DN		(0x1 << 11)	/* Destination non-coherent */
#घोषणा DSCR_CMD0_SM		(0x1 << 10)	/* Stride mode */
#घोषणा DSCR_CMD0_IE		(0x1 << 8)	/* Interrupt Enable */
#घोषणा DSCR_CMD0_SP		(0x1 << 4)	/* Status poपूर्णांकer select */
#घोषणा DSCR_CMD0_CV		(0x1 << 2)	/* Clear Valid when करोne */
#घोषणा DSCR_CMD0_ST_MASK	(0x3 << 0)	/* Status inकाष्ठाion */

#घोषणा SW_STATUS_INUSE		(1 << 0)

/* Command 0 device IDs. */
#घोषणा AU1550_DSCR_CMD0_UART0_TX	0
#घोषणा AU1550_DSCR_CMD0_UART0_RX	1
#घोषणा AU1550_DSCR_CMD0_UART3_TX	2
#घोषणा AU1550_DSCR_CMD0_UART3_RX	3
#घोषणा AU1550_DSCR_CMD0_DMA_REQ0	4
#घोषणा AU1550_DSCR_CMD0_DMA_REQ1	5
#घोषणा AU1550_DSCR_CMD0_DMA_REQ2	6
#घोषणा AU1550_DSCR_CMD0_DMA_REQ3	7
#घोषणा AU1550_DSCR_CMD0_USBDEV_RX0	8
#घोषणा AU1550_DSCR_CMD0_USBDEV_TX0	9
#घोषणा AU1550_DSCR_CMD0_USBDEV_TX1	10
#घोषणा AU1550_DSCR_CMD0_USBDEV_TX2	11
#घोषणा AU1550_DSCR_CMD0_USBDEV_RX3	12
#घोषणा AU1550_DSCR_CMD0_USBDEV_RX4	13
#घोषणा AU1550_DSCR_CMD0_PSC0_TX	14
#घोषणा AU1550_DSCR_CMD0_PSC0_RX	15
#घोषणा AU1550_DSCR_CMD0_PSC1_TX	16
#घोषणा AU1550_DSCR_CMD0_PSC1_RX	17
#घोषणा AU1550_DSCR_CMD0_PSC2_TX	18
#घोषणा AU1550_DSCR_CMD0_PSC2_RX	19
#घोषणा AU1550_DSCR_CMD0_PSC3_TX	20
#घोषणा AU1550_DSCR_CMD0_PSC3_RX	21
#घोषणा AU1550_DSCR_CMD0_PCI_WRITE	22
#घोषणा AU1550_DSCR_CMD0_न_अंकD_FLASH	23
#घोषणा AU1550_DSCR_CMD0_MAC0_RX	24
#घोषणा AU1550_DSCR_CMD0_MAC0_TX	25
#घोषणा AU1550_DSCR_CMD0_MAC1_RX	26
#घोषणा AU1550_DSCR_CMD0_MAC1_TX	27

#घोषणा AU1200_DSCR_CMD0_UART0_TX	0
#घोषणा AU1200_DSCR_CMD0_UART0_RX	1
#घोषणा AU1200_DSCR_CMD0_UART1_TX	2
#घोषणा AU1200_DSCR_CMD0_UART1_RX	3
#घोषणा AU1200_DSCR_CMD0_DMA_REQ0	4
#घोषणा AU1200_DSCR_CMD0_DMA_REQ1	5
#घोषणा AU1200_DSCR_CMD0_MAE_BE		6
#घोषणा AU1200_DSCR_CMD0_MAE_FE		7
#घोषणा AU1200_DSCR_CMD0_SDMS_TX0	8
#घोषणा AU1200_DSCR_CMD0_SDMS_RX0	9
#घोषणा AU1200_DSCR_CMD0_SDMS_TX1	10
#घोषणा AU1200_DSCR_CMD0_SDMS_RX1	11
#घोषणा AU1200_DSCR_CMD0_AES_TX		13
#घोषणा AU1200_DSCR_CMD0_AES_RX		12
#घोषणा AU1200_DSCR_CMD0_PSC0_TX	14
#घोषणा AU1200_DSCR_CMD0_PSC0_RX	15
#घोषणा AU1200_DSCR_CMD0_PSC1_TX	16
#घोषणा AU1200_DSCR_CMD0_PSC1_RX	17
#घोषणा AU1200_DSCR_CMD0_CIM_RXA	18
#घोषणा AU1200_DSCR_CMD0_CIM_RXB	19
#घोषणा AU1200_DSCR_CMD0_CIM_RXC	20
#घोषणा AU1200_DSCR_CMD0_MAE_BOTH	21
#घोषणा AU1200_DSCR_CMD0_LCD		22
#घोषणा AU1200_DSCR_CMD0_न_अंकD_FLASH	23
#घोषणा AU1200_DSCR_CMD0_PSC0_SYNC	24
#घोषणा AU1200_DSCR_CMD0_PSC1_SYNC	25
#घोषणा AU1200_DSCR_CMD0_CIM_SYNC	26

#घोषणा AU1300_DSCR_CMD0_UART0_TX      0
#घोषणा AU1300_DSCR_CMD0_UART0_RX      1
#घोषणा AU1300_DSCR_CMD0_UART1_TX      2
#घोषणा AU1300_DSCR_CMD0_UART1_RX      3
#घोषणा AU1300_DSCR_CMD0_UART2_TX      4
#घोषणा AU1300_DSCR_CMD0_UART2_RX      5
#घोषणा AU1300_DSCR_CMD0_UART3_TX      6
#घोषणा AU1300_DSCR_CMD0_UART3_RX      7
#घोषणा AU1300_DSCR_CMD0_SDMS_TX0      8
#घोषणा AU1300_DSCR_CMD0_SDMS_RX0      9
#घोषणा AU1300_DSCR_CMD0_SDMS_TX1      10
#घोषणा AU1300_DSCR_CMD0_SDMS_RX1      11
#घोषणा AU1300_DSCR_CMD0_AES_TX	       12
#घोषणा AU1300_DSCR_CMD0_AES_RX	       13
#घोषणा AU1300_DSCR_CMD0_PSC0_TX       14
#घोषणा AU1300_DSCR_CMD0_PSC0_RX       15
#घोषणा AU1300_DSCR_CMD0_PSC1_TX       16
#घोषणा AU1300_DSCR_CMD0_PSC1_RX       17
#घोषणा AU1300_DSCR_CMD0_PSC2_TX       18
#घोषणा AU1300_DSCR_CMD0_PSC2_RX       19
#घोषणा AU1300_DSCR_CMD0_PSC3_TX       20
#घोषणा AU1300_DSCR_CMD0_PSC3_RX       21
#घोषणा AU1300_DSCR_CMD0_LCD	       22
#घोषणा AU1300_DSCR_CMD0_न_अंकD_FLASH    23
#घोषणा AU1300_DSCR_CMD0_SDMS_TX2      24
#घोषणा AU1300_DSCR_CMD0_SDMS_RX2      25
#घोषणा AU1300_DSCR_CMD0_CIM_SYNC      26
#घोषणा AU1300_DSCR_CMD0_UDMA	       27
#घोषणा AU1300_DSCR_CMD0_DMA_REQ0      28
#घोषणा AU1300_DSCR_CMD0_DMA_REQ1      29

#घोषणा DSCR_CMD0_THROTTLE	30
#घोषणा DSCR_CMD0_ALWAYS	31
#घोषणा DSCR_NDEV_IDS		32
/* This macro is used to find/create custom device types */
#घोषणा DSCR_DEV2CUSTOM_ID(x, d) (((((x) & 0xFFFF) << 8) | 0x32000000) | \
				  ((d) & 0xFF))
#घोषणा DSCR_CUSTOM2DEV_ID(x)	((x) & 0xFF)

#घोषणा DSCR_CMD0_SID(x)	(((x) & 0x1f) << 25)
#घोषणा DSCR_CMD0_DID(x)	(((x) & 0x1f) << 20)

/* Source/Destination transfer width. */
#घोषणा DSCR_CMD0_BYTE		0
#घोषणा DSCR_CMD0_HALFWORD	1
#घोषणा DSCR_CMD0_WORD		2

#घोषणा DSCR_CMD0_SW(x)		(((x) & 0x3) << 18)
#घोषणा DSCR_CMD0_DW(x)		(((x) & 0x3) << 16)

/* DDMA Descriptor Type. */
#घोषणा DSCR_CMD0_STANDARD	0
#घोषणा DSCR_CMD0_LITERAL	1
#घोषणा DSCR_CMD0_CMP_BRANCH	2

#घोषणा DSCR_CMD0_DT(x)		(((x) & 0x3) << 13)

/* Status Inकाष्ठाion. */
#घोषणा DSCR_CMD0_ST_NOCHANGE	0	/* Don't change */
#घोषणा DSCR_CMD0_ST_CURRENT	1	/* Write current status */
#घोषणा DSCR_CMD0_ST_CMD0	2	/* Write cmd0 with V cleared */
#घोषणा DSCR_CMD0_ST_BYTECNT	3	/* Write reमुख्यing byte count */

#घोषणा DSCR_CMD0_ST(x)		(((x) & 0x3) << 0)

/* Descriptor Command 1. */
#घोषणा DSCR_CMD1_SUPTR_MASK	(0xf << 28)	/* upper 4 bits of src addr */
#घोषणा DSCR_CMD1_DUPTR_MASK	(0xf << 24)	/* upper 4 bits of dest addr */
#घोषणा DSCR_CMD1_FL_MASK	(0x3 << 22)	/* Flag bits */
#घोषणा DSCR_CMD1_BC_MASK	(0x3fffff)	/* Byte count */

/* Flag description. */
#घोषणा DSCR_CMD1_FL_MEM_STRIDE0	0
#घोषणा DSCR_CMD1_FL_MEM_STRIDE1	1
#घोषणा DSCR_CMD1_FL_MEM_STRIDE2	2

#घोषणा DSCR_CMD1_FL(x)		(((x) & 0x3) << 22)

/* Source1, 1-dimensional stride. */
#घोषणा DSCR_SRC1_STS_MASK	(3 << 30)	/* Src xfer size */
#घोषणा DSCR_SRC1_SAM_MASK	(3 << 28)	/* Src xfer movement */
#घोषणा DSCR_SRC1_SB_MASK	(0x3fff << 14)	/* Block size */
#घोषणा DSCR_SRC1_SB(x)		(((x) & 0x3fff) << 14)
#घोषणा DSCR_SRC1_SS_MASK	(0x3fff << 0)	/* Stride */
#घोषणा DSCR_SRC1_SS(x)		(((x) & 0x3fff) << 0)

/* Dest1, 1-dimensional stride. */
#घोषणा DSCR_DEST1_DTS_MASK	(3 << 30)	/* Dest xfer size */
#घोषणा DSCR_DEST1_DAM_MASK	(3 << 28)	/* Dest xfer movement */
#घोषणा DSCR_DEST1_DB_MASK	(0x3fff << 14)	/* Block size */
#घोषणा DSCR_DEST1_DB(x)	(((x) & 0x3fff) << 14)
#घोषणा DSCR_DEST1_DS_MASK	(0x3fff << 0)	/* Stride */
#घोषणा DSCR_DEST1_DS(x)	(((x) & 0x3fff) << 0)

#घोषणा DSCR_xTS_SIZE1		0
#घोषणा DSCR_xTS_SIZE2		1
#घोषणा DSCR_xTS_SIZE4		2
#घोषणा DSCR_xTS_SIZE8		3
#घोषणा DSCR_SRC1_STS(x)	(((x) & 3) << 30)
#घोषणा DSCR_DEST1_DTS(x)	(((x) & 3) << 30)

#घोषणा DSCR_xAM_INCREMENT	0
#घोषणा DSCR_xAM_DECREMENT	1
#घोषणा DSCR_xAM_STATIC		2
#घोषणा DSCR_xAM_BURST		3
#घोषणा DSCR_SRC1_SAM(x)	(((x) & 3) << 28)
#घोषणा DSCR_DEST1_DAM(x)	(((x) & 3) << 28)

/* The next descriptor poपूर्णांकer. */
#घोषणा DSCR_NXTPTR_MASK	(0x07ffffff)
#घोषणा DSCR_NXTPTR(x)		((x) >> 5)
#घोषणा DSCR_GET_NXTPTR(x)	((x) << 5)
#घोषणा DSCR_NXTPTR_MS		(1 << 27)

/* The number of DBDMA channels. */
#घोषणा NUM_DBDMA_CHANS 16

/*
 * DDMA API definitions
 * FIXME: may not fit to this header file
 */
प्रकार काष्ठा dbdma_device_table अणु
	u32	dev_id;
	u32	dev_flags;
	u32	dev_tsize;
	u32	dev_devwidth;
	u32	dev_physaddr;		/* If FIFO */
	u32	dev_पूर्णांकlevel;
	u32	dev_पूर्णांकpolarity;
पूर्ण dbdev_tab_t;


प्रकार काष्ठा dbdma_chan_config अणु
	spinlock_t	lock;

	u32			chan_flags;
	u32			chan_index;
	dbdev_tab_t		*chan_src;
	dbdev_tab_t		*chan_dest;
	au1x_dma_chan_t		*chan_ptr;
	au1x_ddma_desc_t	*chan_desc_base;
	u32			cdb_membase; /* kदो_स्मृति base of above */
	au1x_ddma_desc_t	*get_ptr, *put_ptr, *cur_ptr;
	व्योम			*chan_callparam;
	व्योम			(*chan_callback)(पूर्णांक, व्योम *);
पूर्ण chan_tab_t;

#घोषणा DEV_FLAGS_INUSE		(1 << 0)
#घोषणा DEV_FLAGS_ANYUSE	(1 << 1)
#घोषणा DEV_FLAGS_OUT		(1 << 2)
#घोषणा DEV_FLAGS_IN		(1 << 3)
#घोषणा DEV_FLAGS_BURSTABLE	(1 << 4)
#घोषणा DEV_FLAGS_SYNC		(1 << 5)
/* end DDMA API definitions */

/*
 * External functions क्रम drivers to use.
 * Use this to allocate a DBDMA channel.  The device IDs are one of
 * the DSCR_CMD0 devices IDs, which is usually redefined to a more
 * meaningful name.  The 'callback' is called during DMA completion
 * पूर्णांकerrupt.
 */
बाह्य u32 au1xxx_dbdma_chan_alloc(u32 srcid, u32 destid,
				   व्योम (*callback)(पूर्णांक, व्योम *),
				   व्योम *callparam);

#घोषणा DBDMA_MEM_CHAN	DSCR_CMD0_ALWAYS

/* Set the device width of an in/out FIFO. */
u32 au1xxx_dbdma_set_devwidth(u32 chanid, पूर्णांक bits);

/* Allocate a ring of descriptors क्रम DBDMA. */
u32 au1xxx_dbdma_ring_alloc(u32 chanid, पूर्णांक entries);

/* Put buffers on source/destination descriptors. */
u32 au1xxx_dbdma_put_source(u32 chanid, dma_addr_t buf, पूर्णांक nbytes, u32 flags);
u32 au1xxx_dbdma_put_dest(u32 chanid, dma_addr_t buf, पूर्णांक nbytes, u32 flags);

/* Get a buffer from the destination descriptor. */
u32 au1xxx_dbdma_get_dest(u32 chanid, व्योम **buf, पूर्णांक *nbytes);

व्योम au1xxx_dbdma_stop(u32 chanid);
व्योम au1xxx_dbdma_start(u32 chanid);
व्योम au1xxx_dbdma_reset(u32 chanid);
u32 au1xxx_get_dma_residue(u32 chanid);

व्योम au1xxx_dbdma_chan_मुक्त(u32 chanid);
व्योम au1xxx_dbdma_dump(u32 chanid);

u32 au1xxx_dbdma_put_dscr(u32 chanid, au1x_ddma_desc_t *dscr);

u32 au1xxx_ddma_add_device(dbdev_tab_t *dev);
बाह्य व्योम au1xxx_ddma_del_device(u32 devid);
व्योम *au1xxx_ddma_get_nextptr_virt(au1x_ddma_desc_t *dp);

/*
 *	Flags क्रम the put_source/put_dest functions.
 */
#घोषणा DDMA_FLAGS_IE	(1 << 0)
#घोषणा DDMA_FLAGS_NOIE (1 << 1)

#पूर्ण_अगर /* _LANGUAGE_ASSEMBLY */
#पूर्ण_अगर /* _AU1000_DBDMA_H_ */
