<शैली गुरु>
/******************************************************************* 
 *
 * Copyright (c) 2000 ATecoM GmbH 
 *
 * The author may be reached at ecd@atecom.com.
 *
 * This program is मुक्त software; you can redistribute  it and/or modअगरy it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR   IMPLIED
 * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT,  INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *******************************************************************/

#अगर_अघोषित _IDT77252_H
#घोषणा _IDT77252_H 1


#समावेश <linux/ptrace.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>

/*****************************************************************************/
/*                                                                           */
/* Makros                                                                    */
/*                                                                           */
/*****************************************************************************/
#घोषणा VPCI2VC(card, vpi, vci) \
        (((vpi) << card->vcibits) | ((vci) & card->vcimask))

/*****************************************************************************/
/*                                                                           */
/*   DEBUGGING definitions                                                   */
/*                                                                           */
/*****************************************************************************/

#घोषणा DBG_RAW_CELL	0x00000400
#घोषणा DBG_TINY	0x00000200
#घोषणा DBG_GENERAL     0x00000100
#घोषणा DBG_XGENERAL    0x00000080
#घोषणा DBG_INIT        0x00000040
#घोषणा DBG_DEINIT      0x00000020
#घोषणा DBG_INTERRUPT   0x00000010
#घोषणा DBG_OPEN_CONN   0x00000008
#घोषणा DBG_CLOSE_CONN  0x00000004
#घोषणा DBG_RX_DATA     0x00000002
#घोषणा DBG_TX_DATA     0x00000001

#अगर_घोषित CONFIG_ATM_IDT77252_DEBUG

#घोषणा CPRINTK(args...)   करो अणु अगर (debug & DBG_CLOSE_CONN) prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा OPRINTK(args...)   करो अणु अगर (debug & DBG_OPEN_CONN)  prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा IPRINTK(args...)   करो अणु अगर (debug & DBG_INIT)       prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा INTPRINTK(args...) करो अणु अगर (debug & DBG_INTERRUPT)  prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा DIPRINTK(args...)  करो अणु अगर (debug & DBG_DEINIT)     prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा TXPRINTK(args...)  करो अणु अगर (debug & DBG_TX_DATA)    prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा RXPRINTK(args...)  करो अणु अगर (debug & DBG_RX_DATA)    prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा XPRINTK(args...)   करो अणु अगर (debug & DBG_XGENERAL)   prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा DPRINTK(args...)   करो अणु अगर (debug & DBG_GENERAL)    prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा NPRINTK(args...)   करो अणु अगर (debug & DBG_TINY)	    prपूर्णांकk(args); पूर्ण जबतक(0)
#घोषणा RPRINTK(args...)   करो अणु अगर (debug & DBG_RAW_CELL)   prपूर्णांकk(args); पूर्ण जबतक(0)

#अन्यथा

#घोषणा CPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा OPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा IPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा INTPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा DIPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा TXPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा RXPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा XPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा DPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा NPRINTK(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा RPRINTK(args...)	करो अणु पूर्ण जबतक(0)

#पूर्ण_अगर

#घोषणा SCHED_UBR0		0
#घोषणा SCHED_UBR		1
#घोषणा SCHED_VBR		2
#घोषणा SCHED_ABR		3
#घोषणा SCHED_CBR		4

#घोषणा SCQFULL_TIMEOUT		HZ

/*****************************************************************************/
/*                                                                           */
/*   Free Buffer Queue Layout                                                */
/*                                                                           */
/*****************************************************************************/
#घोषणा SAR_FB_SIZE_0		(2048 - 256)
#घोषणा SAR_FB_SIZE_1		(4096 - 256)
#घोषणा SAR_FB_SIZE_2		(8192 - 256)
#घोषणा SAR_FB_SIZE_3		(16384 - 256)

#घोषणा SAR_FBQ0_LOW		4
#घोषणा SAR_FBQ0_HIGH		8
#घोषणा SAR_FBQ1_LOW		2
#घोषणा SAR_FBQ1_HIGH		4
#घोषणा SAR_FBQ2_LOW		1
#घोषणा SAR_FBQ2_HIGH		2
#घोषणा SAR_FBQ3_LOW		1
#घोषणा SAR_FBQ3_HIGH		2

#अगर 0
#घोषणा SAR_TST_RESERVED	44	/* Num TST reserved क्रम UBR/ABR/VBR */
#अन्यथा
#घोषणा SAR_TST_RESERVED	0	/* Num TST reserved क्रम UBR/ABR/VBR */
#पूर्ण_अगर

#घोषणा TCT_CBR			0x00000000
#घोषणा TCT_UBR			0x00000000
#घोषणा TCT_VBR			0x40000000
#घोषणा TCT_ABR			0x80000000
#घोषणा TCT_TYPE		0xc0000000

#घोषणा TCT_RR			0x20000000
#घोषणा TCT_LMCR		0x08000000
#घोषणा TCT_SCD_MASK		0x0007ffff

#घोषणा TCT_TSIF		0x00004000
#घोषणा TCT_HALT		0x80000000
#घोषणा TCT_IDLE		0x40000000
#घोषणा TCT_FLAG_UBR		0x80000000

/*****************************************************************************/
/*                                                                           */
/*   Structure describing an IDT77252                                        */
/*                                                                           */
/*****************************************************************************/

काष्ठा scqe
अणु
	u32		word_1;
	u32		word_2;
	u32		word_3;
	u32		word_4;
पूर्ण;

#घोषणा SCQ_ENTRIES	64
#घोषणा SCQ_SIZE	(SCQ_ENTRIES * माप(काष्ठा scqe))
#घोषणा SCQ_MASK	(SCQ_SIZE - 1)

काष्ठा scq_info
अणु
	काष्ठा scqe		*base;
	काष्ठा scqe		*next;
	काष्ठा scqe		*last;
	dma_addr_t		paddr;
	spinlock_t		lock;
	atomic_t		used;
	अचिन्हित दीर्घ		trans_start;
        अचिन्हित दीर्घ		scd;
	spinlock_t		skblock;
	काष्ठा sk_buff_head	transmit;
	काष्ठा sk_buff_head	pending;
पूर्ण;

काष्ठा rx_pool अणु
	काष्ठा sk_buff_head	queue;
	अचिन्हित पूर्णांक		len;
पूर्ण;

काष्ठा aal1 अणु
	अचिन्हित पूर्णांक		total;
	अचिन्हित पूर्णांक		count;
	काष्ठा sk_buff		*data;
	अचिन्हित अक्षर		sequence;
पूर्ण;

काष्ठा vc_map;

काष्ठा rate_estimator अणु
	काष्ठा समयr_list	समयr;
	अचिन्हित पूर्णांक		पूर्णांकerval;
	अचिन्हित पूर्णांक		ewma_log;
	u64			cells;
	u64			last_cells;
	दीर्घ			avcps;
	u32			cps;
	u32			maxcps;
	काष्ठा vc_map		*vc;
पूर्ण;

काष्ठा vc_map अणु
	अचिन्हित पूर्णांक		index;
	अचिन्हित दीर्घ		flags;
#घोषणा VCF_TX		0
#घोषणा VCF_RX		1
#घोषणा VCF_IDLE	2
#घोषणा VCF_RSV		3
	अचिन्हित पूर्णांक		class;
	u8			init_er;
	u8			lacr;
	u8			max_er;
	अचिन्हित पूर्णांक		ntste;
	spinlock_t		lock;
	काष्ठा aपंचांग_vcc		*tx_vcc;
	काष्ठा aपंचांग_vcc		*rx_vcc;
	काष्ठा idt77252_dev	*card;
	काष्ठा scq_info		*scq;		/* To keep track of the SCQ */
	काष्ठा rate_estimator	*estimator;
	पूर्णांक			scd_index;
	जोड़ अणु
		काष्ठा rx_pool	rx_pool;
		काष्ठा aal1	aal1;
	पूर्ण rcv;
पूर्ण;

/*****************************************************************************/
/*                                                                           */
/*   RCTE - Receive Connection Table Entry                                   */
/*                                                                           */
/*****************************************************************************/

काष्ठा rct_entry
अणु
	u32		word_1;
	u32		buffer_handle;
	u32		dma_address;
	u32		aal5_crc32;
पूर्ण;

/*****************************************************************************/
/*                                                                           */
/*   RSQ - Receive Status Queue                                              */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_RSQE_VALID      0x80000000
#घोषणा SAR_RSQE_IDLE       0x40000000
#घोषणा SAR_RSQE_BUF_MASK   0x00030000
#घोषणा SAR_RSQE_BUF_ASGN   0x00008000
#घोषणा SAR_RSQE_NZGFC      0x00004000
#घोषणा SAR_RSQE_EPDU       0x00002000
#घोषणा SAR_RSQE_BUF_CONT   0x00001000
#घोषणा SAR_RSQE_EFCIE      0x00000800
#घोषणा SAR_RSQE_CLP        0x00000400
#घोषणा SAR_RSQE_CRC        0x00000200
#घोषणा SAR_RSQE_CELLCNT    0x000001FF


#घोषणा RSQSIZE            8192
#घोषणा RSQ_NUM_ENTRIES    (RSQSIZE / 16)
#घोषणा RSQ_ALIGNMENT      8192

काष्ठा rsq_entry अणु
	u32			word_1;
	u32			word_2;
	u32			word_3;
	u32			word_4;
पूर्ण;

काष्ठा rsq_info अणु
	काष्ठा rsq_entry	*base;
	काष्ठा rsq_entry	*next;
	काष्ठा rsq_entry	*last;
	dma_addr_t		paddr;
पूर्ण;


/*****************************************************************************/
/*                                                                           */
/*   TSQ - Transmit Status Queue                                             */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_TSQE_INVALID         0x80000000
#घोषणा SAR_TSQE_TIMESTAMP       0x00FFFFFF
#घोषणा SAR_TSQE_TYPE		 0x60000000
#घोषणा SAR_TSQE_TYPE_TIMER      0x00000000
#घोषणा SAR_TSQE_TYPE_TSR        0x20000000
#घोषणा SAR_TSQE_TYPE_IDLE       0x40000000
#घोषणा SAR_TSQE_TYPE_TBD_COMP   0x60000000

#घोषणा SAR_TSQE_TAG(stat)	(((stat) >> 24) & 0x1f)

#घोषणा TSQSIZE            8192
#घोषणा TSQ_NUM_ENTRIES    1024
#घोषणा TSQ_ALIGNMENT      8192

काष्ठा tsq_entry
अणु
	u32			word_1;
	u32			word_2;
पूर्ण;

काष्ठा tsq_info
अणु
	काष्ठा tsq_entry	*base;
	काष्ठा tsq_entry	*next;
	काष्ठा tsq_entry	*last;
	dma_addr_t		paddr;
पूर्ण;

काष्ठा tst_info
अणु
	काष्ठा vc_map		*vc;
	u32			tste;
पूर्ण;

#घोषणा TSTE_MASK		0x601fffff

#घोषणा TSTE_OPC_MASK		0x60000000
#घोषणा TSTE_OPC_शून्य		0x00000000
#घोषणा TSTE_OPC_CBR		0x20000000
#घोषणा TSTE_OPC_VAR		0x40000000
#घोषणा TSTE_OPC_JMP		0x60000000

#घोषणा TSTE_PUSH_IDLE		0x01000000
#घोषणा TSTE_PUSH_ACTIVE	0x02000000

#घोषणा TST_SWITCH_DONE		0
#घोषणा TST_SWITCH_PENDING	1
#घोषणा TST_SWITCH_WAIT		2

#घोषणा FBQ_SHIFT		9
#घोषणा FBQ_SIZE		(1 << FBQ_SHIFT)
#घोषणा FBQ_MASK		(FBQ_SIZE - 1)

काष्ठा sb_pool
अणु
	अचिन्हित पूर्णांक		index;
	काष्ठा sk_buff		*skb[FBQ_SIZE];
पूर्ण;

#घोषणा POOL_HANDLE(queue, index)	(((queue + 1) << 16) | (index))
#घोषणा POOL_QUEUE(handle)		(((handle) >> 16) - 1)
#घोषणा POOL_INDEX(handle)		((handle) & 0xffff)

काष्ठा idt77252_dev
अणु
        काष्ठा tsq_info		tsq;		/* Transmit Status Queue */
        काष्ठा rsq_info		rsq;		/* Receive Status Queue */

	काष्ठा pci_dev		*pcidev;	/* PCI handle (desriptor) */
	काष्ठा aपंचांग_dev		*aपंचांगdev;	/* ATM device desriptor */

	व्योम __iomem		*membase;	/* SAR's memory base address */
	अचिन्हित दीर्घ		srambase;	/* SAR's sram  base address */
	व्योम __iomem		*fbq[4];	/* FBQ fill addresses */

	काष्ठा mutex		mutex;
	spinlock_t		cmd_lock;	/* क्रम r/w utility/sram */

	अचिन्हित दीर्घ		softstat;
	अचिन्हित दीर्घ		flags;		/* see blow */

	काष्ठा work_काष्ठा	tqueue;

	अचिन्हित दीर्घ		tct_base;	/* TCT base address in SRAM */
        अचिन्हित दीर्घ		rct_base;	/* RCT base address in SRAM */
        अचिन्हित दीर्घ		rt_base;	/* Rate Table base in SRAM */
        अचिन्हित दीर्घ		scd_base;	/* SCD base address in SRAM */
        अचिन्हित दीर्घ		tst[2];		/* TST base address in SRAM */
	अचिन्हित दीर्घ		abrst_base;	/* ABRST base address in SRAM */
        अचिन्हित दीर्घ		fअगरo_base;	/* RX FIFO base in SRAM */

	अचिन्हित दीर्घ		irqstat[16];

	अचिन्हित पूर्णांक		sramsize;	/* SAR's sram size */

        अचिन्हित पूर्णांक		tct_size;	/* total TCT entries */
        अचिन्हित पूर्णांक		rct_size;	/* total RCT entries */
        अचिन्हित पूर्णांक		scd_size;	/* length of SCD */
        अचिन्हित पूर्णांक		tst_size;	/* total TST entries */
        अचिन्हित पूर्णांक		tst_मुक्त;	/* मुक्त TSTEs in TST */
        अचिन्हित पूर्णांक		abrst_size;	/* size of ABRST in words */
        अचिन्हित पूर्णांक		fअगरo_size;	/* size of RX FIFO in words */

        अचिन्हित पूर्णांक		vpibits;	/* Bits used क्रम VPI index */
        अचिन्हित पूर्णांक		vcibits;	/* Bits used क्रम VCI index */
        अचिन्हित पूर्णांक		vcimask;	/* Mask क्रम VCI index */

	अचिन्हित पूर्णांक		utopia_pcr;	/* Utopia Itf's Cell Rate */
	अचिन्हित पूर्णांक		link_pcr;	/* PHY's Peek Cell Rate */

	काष्ठा vc_map		**vcs;		/* Open Connections */
	काष्ठा vc_map		**scd2vc;	/* SCD to Connection map */

	काष्ठा tst_info		*soft_tst;	/* TST to Connection map */
	अचिन्हित पूर्णांक		tst_index;	/* Current TST in use */
	काष्ठा समयr_list	tst_समयr;
	spinlock_t		tst_lock;
	अचिन्हित दीर्घ		tst_state;

	काष्ठा sb_pool		sbpool[4];	/* Pool of RX skbuffs */
	काष्ठा sk_buff		*raw_cell_head; /* Poपूर्णांकer to raw cell queue */
	u32			*raw_cell_hnd;	/* Poपूर्णांकer to RCQ handle */
	dma_addr_t		raw_cell_paddr;

	पूर्णांक			index;		/* SAR's ID */
	पूर्णांक			revision;	/* chip revision */

	अक्षर			name[16];	/* Device name */

	काष्ठा idt77252_dev	*next;
पूर्ण;


/* definition क्रम flag field above */
#घोषणा IDT77252_BIT_INIT		1
#घोषणा IDT77252_BIT_INTERRUPT		2


#घोषणा ATM_CELL_PAYLOAD         48

#घोषणा FREEBUF_ALIGNMENT        16

/*****************************************************************************/
/*                                                                           */
/* Makros                                                                    */
/*                                                                           */
/*****************************************************************************/
#घोषणा ALIGN_ADDRESS(addr, alignment) \
        ((((u32)(addr)) + (((u32)(alignment))-1)) & ~(((u32)(alignment)) - 1))


/*****************************************************************************/
/*                                                                           */
/*   ABR SAR Network operation Register                                      */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_REG_DR0	(card->membase + 0x00)
#घोषणा SAR_REG_DR1	(card->membase + 0x04)
#घोषणा SAR_REG_DR2	(card->membase + 0x08)
#घोषणा SAR_REG_DR3	(card->membase + 0x0C)
#घोषणा SAR_REG_CMD	(card->membase + 0x10)
#घोषणा SAR_REG_CFG	(card->membase + 0x14)
#घोषणा SAR_REG_STAT	(card->membase + 0x18)
#घोषणा SAR_REG_RSQB	(card->membase + 0x1C)
#घोषणा SAR_REG_RSQT	(card->membase + 0x20)
#घोषणा SAR_REG_RSQH	(card->membase + 0x24)
#घोषणा SAR_REG_CDC	(card->membase + 0x28)
#घोषणा SAR_REG_VPEC	(card->membase + 0x2C)
#घोषणा SAR_REG_ICC	(card->membase + 0x30)
#घोषणा SAR_REG_RAWCT	(card->membase + 0x34)
#घोषणा SAR_REG_TMR	(card->membase + 0x38)
#घोषणा SAR_REG_TSTB	(card->membase + 0x3C)
#घोषणा SAR_REG_TSQB	(card->membase + 0x40)
#घोषणा SAR_REG_TSQT	(card->membase + 0x44)
#घोषणा SAR_REG_TSQH	(card->membase + 0x48)
#घोषणा SAR_REG_GP	(card->membase + 0x4C)
#घोषणा SAR_REG_VPM	(card->membase + 0x50)
#घोषणा SAR_REG_RXFD	(card->membase + 0x54)
#घोषणा SAR_REG_RXFT	(card->membase + 0x58)
#घोषणा SAR_REG_RXFH	(card->membase + 0x5C)
#घोषणा SAR_REG_RAWHND	(card->membase + 0x60)
#घोषणा SAR_REG_RXSTAT	(card->membase + 0x64)
#घोषणा SAR_REG_ABRSTD	(card->membase + 0x68)
#घोषणा SAR_REG_ABRRQ	(card->membase + 0x6C)
#घोषणा SAR_REG_VBRRQ	(card->membase + 0x70)
#घोषणा SAR_REG_RTBL	(card->membase + 0x74)
#घोषणा SAR_REG_MDFCT	(card->membase + 0x78)
#घोषणा SAR_REG_TXSTAT	(card->membase + 0x7C)
#घोषणा SAR_REG_TCMDQ	(card->membase + 0x80)
#घोषणा SAR_REG_IRCP	(card->membase + 0x84)
#घोषणा SAR_REG_FBQP0	(card->membase + 0x88)
#घोषणा SAR_REG_FBQP1	(card->membase + 0x8C)
#घोषणा SAR_REG_FBQP2	(card->membase + 0x90)
#घोषणा SAR_REG_FBQP3	(card->membase + 0x94)
#घोषणा SAR_REG_FBQS0	(card->membase + 0x98)
#घोषणा SAR_REG_FBQS1	(card->membase + 0x9C)
#घोषणा SAR_REG_FBQS2	(card->membase + 0xA0)
#घोषणा SAR_REG_FBQS3	(card->membase + 0xA4)
#घोषणा SAR_REG_FBQWP0	(card->membase + 0xA8)
#घोषणा SAR_REG_FBQWP1	(card->membase + 0xAC)
#घोषणा SAR_REG_FBQWP2	(card->membase + 0xB0)
#घोषणा SAR_REG_FBQWP3	(card->membase + 0xB4)
#घोषणा SAR_REG_NOW	(card->membase + 0xB8)


/*****************************************************************************/
/*                                                                           */
/*   Commands                                                                */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_CMD_NO_OPERATION         0x00000000
#घोषणा SAR_CMD_OPENCLOSE_CONNECTION 0x20000000
#घोषणा SAR_CMD_WRITE_SRAM           0x40000000
#घोषणा SAR_CMD_READ_SRAM            0x50000000
#घोषणा SAR_CMD_READ_UTILITY         0x80000000
#घोषणा SAR_CMD_WRITE_UTILITY        0x90000000

#घोषणा SAR_CMD_OPEN_CONNECTION     (SAR_CMD_OPENCLOSE_CONNECTION | 0x00080000)
#घोषणा SAR_CMD_CLOSE_CONNECTION     SAR_CMD_OPENCLOSE_CONNECTION


/*****************************************************************************/
/*                                                                           */
/*   Configuration Register bits                                             */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_CFG_SWRST          0x80000000  /* Software reset                 */
#घोषणा SAR_CFG_LOOP           0x40000000  /* Internal Loopback              */
#घोषणा SAR_CFG_RXPTH          0x20000000  /* Receive Path Enable            */
#घोषणा SAR_CFG_IDLE_CLP       0x10000000  /* SAR set CLP Bits of Null Cells */
#घोषणा SAR_CFG_TX_FIFO_SIZE_1 0x04000000  /* TX FIFO Size = 1 cell          */
#घोषणा SAR_CFG_TX_FIFO_SIZE_2 0x08000000  /* TX FIFO Size = 2 cells         */
#घोषणा SAR_CFG_TX_FIFO_SIZE_4 0x0C000000  /* TX FIFO Size = 4 cells         */
#घोषणा SAR_CFG_TX_FIFO_SIZE_9 0x00000000  /* TX FIFO Size = 9 cells (full)  */
#घोषणा SAR_CFG_NO_IDLE        0x02000000  /* SAR sends no Null Cells        */
#घोषणा SAR_CFG_RSVD1          0x01000000  /* Reserved                       */
#घोषणा SAR_CFG_RXSTQ_SIZE_2k  0x00000000  /* RX Stat Queue Size = 2048 byte */
#घोषणा SAR_CFG_RXSTQ_SIZE_4k  0x00400000  /* RX Stat Queue Size = 4096 byte */
#घोषणा SAR_CFG_RXSTQ_SIZE_8k  0x00800000  /* RX Stat Queue Size = 8192 byte */
#घोषणा SAR_CFG_RXSTQ_SIZE_R   0x00C00000  /* RX Stat Queue Size = reserved  */
#घोषणा SAR_CFG_ICAPT          0x00200000  /* accept Invalid Cells           */
#घोषणा SAR_CFG_IGGFC          0x00100000  /* Ignore GFC                     */
#घोषणा SAR_CFG_VPVCS_0        0x00000000  /* VPI/VCI Select bit range       */
#घोषणा SAR_CFG_VPVCS_1        0x00040000  /* VPI/VCI Select bit range       */
#घोषणा SAR_CFG_VPVCS_2        0x00080000  /* VPI/VCI Select bit range       */
#घोषणा SAR_CFG_VPVCS_8        0x000C0000  /* VPI/VCI Select bit range       */
#घोषणा SAR_CFG_CNTBL_1k       0x00000000  /* Connection Table Size          */
#घोषणा SAR_CFG_CNTBL_4k       0x00010000  /* Connection Table Size          */
#घोषणा SAR_CFG_CNTBL_16k      0x00020000  /* Connection Table Size          */
#घोषणा SAR_CFG_CNTBL_512      0x00030000  /* Connection Table Size          */
#घोषणा SAR_CFG_VPECA          0x00008000  /* VPI/VCI Error Cell Accept      */
#घोषणा SAR_CFG_RXINT_NOINT    0x00000000  /* No Interrupt on PDU received   */
#घोषणा SAR_CFG_RXINT_NODELAY  0x00001000  /* Interrupt without delay to host*/
#घोषणा SAR_CFG_RXINT_256US    0x00002000  /* Interrupt with delay 256 usec  */
#घोषणा SAR_CFG_RXINT_505US    0x00003000  /* Interrupt with delay 505 usec  */
#घोषणा SAR_CFG_RXINT_742US    0x00004000  /* Interrupt with delay 742 usec  */
#घोषणा SAR_CFG_RAWIE          0x00000800  /* Raw Cell Queue Interrupt Enable*/
#घोषणा SAR_CFG_RQFIE          0x00000400  /* RSQ Almost Full Int Enable     */
#घोषणा SAR_CFG_RSVD2          0x00000200  /* Reserved                       */
#घोषणा SAR_CFG_CACHE          0x00000100  /* DMA on Cache Line Boundary     */
#घोषणा SAR_CFG_TMOIE          0x00000080  /* Timer Roll Over Int Enable     */
#घोषणा SAR_CFG_FBIE           0x00000040  /* Free Buffer Queue Int Enable   */
#घोषणा SAR_CFG_TXEN           0x00000020  /* Transmit Operation Enable      */
#घोषणा SAR_CFG_TXINT          0x00000010  /* Transmit status Int Enable     */
#घोषणा SAR_CFG_TXUIE          0x00000008  /* Transmit underrun Int Enable   */
#घोषणा SAR_CFG_UMODE          0x00000004  /* Utopia Mode Select             */
#घोषणा SAR_CFG_TXSFI          0x00000002  /* Transmit status Full Int Enable*/
#घोषणा SAR_CFG_PHYIE          0x00000001  /* PHY Interrupt Enable           */

#घोषणा SAR_CFG_TX_FIFO_SIZE_MASK 0x0C000000  /* TX FIFO Size Mask           */
#घोषणा SAR_CFG_RXSTQSIZE_MASK 0x00C00000
#घोषणा SAR_CFG_CNTBL_MASK     0x00030000
#घोषणा SAR_CFG_RXINT_MASK     0x00007000


/*****************************************************************************/
/*                                                                           */
/*   Status Register bits                                                    */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_STAT_FRAC_3     0xF0000000 /* Fraction of Free Buffer Queue 3 */
#घोषणा SAR_STAT_FRAC_2     0x0F000000 /* Fraction of Free Buffer Queue 2 */
#घोषणा SAR_STAT_FRAC_1     0x00F00000 /* Fraction of Free Buffer Queue 1 */
#घोषणा SAR_STAT_FRAC_0     0x000F0000 /* Fraction of Free Buffer Queue 0 */
#घोषणा SAR_STAT_TSIF       0x00008000 /* Transmit Status Indicator       */
#घोषणा SAR_STAT_TXICP      0x00004000 /* Transmit Status Indicator       */
#घोषणा SAR_STAT_RSVD1      0x00002000 /* Reserved                        */
#घोषणा SAR_STAT_TSQF       0x00001000 /* Transmit Status Queue full      */
#घोषणा SAR_STAT_TMROF      0x00000800 /* Timer overflow                  */
#घोषणा SAR_STAT_PHYI       0x00000400 /* PHY device Interrupt flag       */
#घोषणा SAR_STAT_CMDBZ      0x00000200 /* ABR SAR Command Busy Flag       */
#घोषणा SAR_STAT_FBQ3A      0x00000100 /* Free Buffer Queue 3 Attention   */
#घोषणा SAR_STAT_FBQ2A      0x00000080 /* Free Buffer Queue 2 Attention   */
#घोषणा SAR_STAT_RSQF       0x00000040 /* Receive Status Queue full       */
#घोषणा SAR_STAT_EPDU       0x00000020 /* End Of PDU Flag                 */
#घोषणा SAR_STAT_RAWCF      0x00000010 /* Raw Cell Flag                   */ 
#घोषणा SAR_STAT_FBQ1A      0x00000008 /* Free Buffer Queue 1 Attention   */
#घोषणा SAR_STAT_FBQ0A      0x00000004 /* Free Buffer Queue 0 Attention   */
#घोषणा SAR_STAT_RSQAF      0x00000002 /* Receive Status Queue almost full*/  
#घोषणा SAR_STAT_RSVD2      0x00000001 /* Reserved                        */


/*****************************************************************************/
/*                                                                           */
/*   General Purpose Register bits                                           */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_GP_TXNCC_MASK   0xff000000  /* Transmit Negative Credit Count   */
#घोषणा SAR_GP_EEDI         0x00010000  /* EEPROM Data In                   */
#घोषणा SAR_GP_BIGE         0x00008000  /* Big Endian Operation             */
#घोषणा SAR_GP_RM_NORMAL    0x00000000  /* Normal handling of RM cells      */
#घोषणा SAR_GP_RM_TO_RCQ    0x00002000  /* put RM cells पूर्णांकo Raw Cell Queue */
#घोषणा SAR_GP_RM_RSVD      0x00004000  /* Reserved                         */
#घोषणा SAR_GP_RM_INHIBIT   0x00006000  /* Inhibit update of Connection tab */
#घोषणा SAR_GP_PHY_RESET    0x00000008  /* PHY Reset                        */
#घोषणा SAR_GP_EESCLK	    0x00000004	/* EEPROM SCLK			    */
#घोषणा SAR_GP_EECS	    0x00000002	/* EEPROM Chip Select		    */
#घोषणा SAR_GP_EEDO	    0x00000001	/* EEPROM Data Out		    */


/*****************************************************************************/
/*                                                                           */
/*   SAR local SRAM layout क्रम 128k work SRAM                                */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_SRAM_SCD_SIZE        12
#घोषणा SAR_SRAM_TCT_SIZE         8
#घोषणा SAR_SRAM_RCT_SIZE         4

#घोषणा SAR_SRAM_TCT_128_BASE    0x00000
#घोषणा SAR_SRAM_TCT_128_TOP     0x01fff
#घोषणा SAR_SRAM_RCT_128_BASE    0x02000
#घोषणा SAR_SRAM_RCT_128_TOP     0x02fff
#घोषणा SAR_SRAM_FB0_128_BASE    0x03000
#घोषणा SAR_SRAM_FB0_128_TOP     0x033ff
#घोषणा SAR_SRAM_FB1_128_BASE    0x03400
#घोषणा SAR_SRAM_FB1_128_TOP     0x037ff
#घोषणा SAR_SRAM_FB2_128_BASE    0x03800
#घोषणा SAR_SRAM_FB2_128_TOP     0x03bff
#घोषणा SAR_SRAM_FB3_128_BASE    0x03c00
#घोषणा SAR_SRAM_FB3_128_TOP     0x03fff
#घोषणा SAR_SRAM_SCD_128_BASE    0x04000
#घोषणा SAR_SRAM_SCD_128_TOP     0x07fff
#घोषणा SAR_SRAM_TST1_128_BASE   0x08000
#घोषणा SAR_SRAM_TST1_128_TOP    0x0bfff
#घोषणा SAR_SRAM_TST2_128_BASE   0x0c000
#घोषणा SAR_SRAM_TST2_128_TOP    0x0ffff
#घोषणा SAR_SRAM_ABRSTD_128_BASE 0x10000
#घोषणा SAR_SRAM_ABRSTD_128_TOP  0x13fff
#घोषणा SAR_SRAM_RT_128_BASE     0x14000
#घोषणा SAR_SRAM_RT_128_TOP      0x15fff

#घोषणा SAR_SRAM_FIFO_128_BASE   0x18000
#घोषणा SAR_SRAM_FIFO_128_TOP    0x1ffff


/*****************************************************************************/
/*                                                                           */
/*   SAR local SRAM layout क्रम 32k work SRAM                                 */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_SRAM_TCT_32_BASE     0x00000
#घोषणा SAR_SRAM_TCT_32_TOP      0x00fff
#घोषणा SAR_SRAM_RCT_32_BASE     0x01000
#घोषणा SAR_SRAM_RCT_32_TOP      0x017ff
#घोषणा SAR_SRAM_FB0_32_BASE     0x01800
#घोषणा SAR_SRAM_FB0_32_TOP      0x01bff
#घोषणा SAR_SRAM_FB1_32_BASE     0x01c00
#घोषणा SAR_SRAM_FB1_32_TOP      0x01fff
#घोषणा SAR_SRAM_FB2_32_BASE     0x02000
#घोषणा SAR_SRAM_FB2_32_TOP      0x023ff
#घोषणा SAR_SRAM_FB3_32_BASE     0x02400
#घोषणा SAR_SRAM_FB3_32_TOP      0x027ff
#घोषणा SAR_SRAM_SCD_32_BASE     0x02800
#घोषणा SAR_SRAM_SCD_32_TOP      0x03fff
#घोषणा SAR_SRAM_TST1_32_BASE    0x04000
#घोषणा SAR_SRAM_TST1_32_TOP     0x04fff
#घोषणा SAR_SRAM_TST2_32_BASE    0x05000
#घोषणा SAR_SRAM_TST2_32_TOP     0x05fff
#घोषणा SAR_SRAM_ABRSTD_32_BASE  0x06000
#घोषणा SAR_SRAM_ABRSTD_32_TOP   0x067ff
#घोषणा SAR_SRAM_RT_32_BASE      0x06800
#घोषणा SAR_SRAM_RT_32_TOP       0x06fff
#घोषणा SAR_SRAM_FIFO_32_BASE    0x07000
#घोषणा SAR_SRAM_FIFO_32_TOP     0x07fff


/*****************************************************************************/
/*                                                                           */
/*   TSR - Transmit Status Request                                           */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_TSR_TYPE_TSR  0x80000000
#घोषणा SAR_TSR_TYPE_TBD  0x00000000
#घोषणा SAR_TSR_TSIF      0x20000000
#घोषणा SAR_TSR_TAG_MASK  0x01F00000


/*****************************************************************************/
/*                                                                           */
/*   TBD - Transmit Buffer Descriptor                                        */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_TBD_EPDU      0x40000000
#घोषणा SAR_TBD_TSIF      0x20000000
#घोषणा SAR_TBD_OAM       0x10000000
#घोषणा SAR_TBD_AAL0      0x00000000
#घोषणा SAR_TBD_AAL34     0x04000000
#घोषणा SAR_TBD_AAL5      0x08000000
#घोषणा SAR_TBD_GTSI      0x02000000
#घोषणा SAR_TBD_TAG_MASK  0x01F00000

#घोषणा SAR_TBD_VPI_MASK  0x0FF00000
#घोषणा SAR_TBD_VCI_MASK  0x000FFFF0
#घोषणा SAR_TBD_VC_MASK   (SAR_TBD_VPI_MASK | SAR_TBD_VCI_MASK)

#घोषणा SAR_TBD_VPI_SHIFT 20
#घोषणा SAR_TBD_VCI_SHIFT 4


/*****************************************************************************/
/*                                                                           */
/*   RXFD - Receive FIFO Descriptor                                          */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_RXFD_SIZE_MASK     0x0F000000
#घोषणा SAR_RXFD_SIZE_512      0x00000000  /* 512 words                      */
#घोषणा SAR_RXFD_SIZE_1K       0x01000000  /* 1k words                       */
#घोषणा SAR_RXFD_SIZE_2K       0x02000000  /* 2k words                       */
#घोषणा SAR_RXFD_SIZE_4K       0x03000000  /* 4k words                       */
#घोषणा SAR_RXFD_SIZE_8K       0x04000000  /* 8k words                       */
#घोषणा SAR_RXFD_SIZE_16K      0x05000000  /* 16k words                      */
#घोषणा SAR_RXFD_SIZE_32K      0x06000000  /* 32k words                      */
#घोषणा SAR_RXFD_SIZE_64K      0x07000000  /* 64k words                      */
#घोषणा SAR_RXFD_SIZE_128K     0x08000000  /* 128k words                     */
#घोषणा SAR_RXFD_SIZE_256K     0x09000000  /* 256k words                     */
#घोषणा SAR_RXFD_ADDR_MASK     0x001ffc00


/*****************************************************************************/
/*                                                                           */
/*   ABRSTD - ABR + VBR Schedule Tables                                      */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_ABRSTD_SIZE_MASK   0x07000000
#घोषणा SAR_ABRSTD_SIZE_512    0x00000000  /* 512 words                      */
#घोषणा SAR_ABRSTD_SIZE_1K     0x01000000  /* 1k words                       */
#घोषणा SAR_ABRSTD_SIZE_2K     0x02000000  /* 2k words                       */
#घोषणा SAR_ABRSTD_SIZE_4K     0x03000000  /* 4k words                       */
#घोषणा SAR_ABRSTD_SIZE_8K     0x04000000  /* 8k words                       */
#घोषणा SAR_ABRSTD_SIZE_16K    0x05000000  /* 16k words                      */
#घोषणा SAR_ABRSTD_ADDR_MASK   0x001ffc00


/*****************************************************************************/
/*                                                                           */
/*   RCTE - Receive Connection Table Entry                                   */
/*                                                                           */
/*****************************************************************************/

#घोषणा SAR_RCTE_IL_MASK       0xE0000000  /* inactivity limit               */
#घोषणा SAR_RCTE_IC_MASK       0x1C000000  /* inactivity count               */
#घोषणा SAR_RCTE_RSVD          0x02000000  /* reserved                       */
#घोषणा SAR_RCTE_LCD           0x01000000  /* last cell data                 */
#घोषणा SAR_RCTE_CI_VC         0x00800000  /* EFCI in previous cell of VC    */
#घोषणा SAR_RCTE_FBP_01        0x00000000  /* 1. cell->FBQ0, others->FBQ1    */
#घोषणा SAR_RCTE_FBP_1         0x00200000  /* use FBQ 1 क्रम all cells        */
#घोषणा SAR_RCTE_FBP_2         0x00400000  /* use FBQ 2 क्रम all cells        */
#घोषणा SAR_RCTE_FBP_3         0x00600000  /* use FBQ 3 क्रम all cells        */
#घोषणा SAR_RCTE_NZ_GFC        0x00100000  /* non zero GFC in all cell of VC */
#घोषणा SAR_RCTE_CONNECTOPEN   0x00080000  /* VC is खोलो                     */
#घोषणा SAR_RCTE_AAL_MASK      0x00070000  /* mask क्रम AAL type field s.b.   */
#घोषणा SAR_RCTE_RAWCELLINTEN  0x00008000  /* raw cell पूर्णांकerrupt enable      */
#घोषणा SAR_RCTE_RXCONCELLADDR 0x00004000  /* RX स्थिरant cell address       */
#घोषणा SAR_RCTE_BUFFSTAT_MASK 0x00003000  /* buffer status                  */
#घोषणा SAR_RCTE_EFCI          0x00000800  /* EFCI Congestion flag           */
#घोषणा SAR_RCTE_CLP           0x00000400  /* Cell Loss Priority flag        */
#घोषणा SAR_RCTE_CRC           0x00000200  /* Received CRC Error             */
#घोषणा SAR_RCTE_CELLCNT_MASK  0x000001FF  /* cell Count                     */

#घोषणा SAR_RCTE_AAL0          0x00000000  /* AAL types क्रम ALL field        */
#घोषणा SAR_RCTE_AAL34         0x00010000
#घोषणा SAR_RCTE_AAL5          0x00020000
#घोषणा SAR_RCTE_RCQ           0x00030000
#घोषणा SAR_RCTE_OAM           0x00040000

#घोषणा TCMDQ_START		0x01000000
#घोषणा TCMDQ_LACR		0x02000000
#घोषणा TCMDQ_START_LACR	0x03000000
#घोषणा TCMDQ_INIT_ER		0x04000000
#घोषणा TCMDQ_HALT		0x05000000


काष्ठा idt77252_skb_prv अणु
	काष्ठा scqe	tbd;	/* Transmit Buffer Descriptor */
	dma_addr_t	paddr;	/* DMA handle */
	u32		pool;	/* sb_pool handle */
पूर्ण __packed;

#घोषणा IDT77252_PRV_TBD(skb)	\
	(((काष्ठा idt77252_skb_prv *)(ATM_SKB(skb)+1))->tbd)
#घोषणा IDT77252_PRV_PADDR(skb)	\
	(((काष्ठा idt77252_skb_prv *)(ATM_SKB(skb)+1))->paddr)
#घोषणा IDT77252_PRV_POOL(skb)	\
	(((काष्ठा idt77252_skb_prv *)(ATM_SKB(skb)+1))->pool)

/*****************************************************************************/
/*                                                                           */
/*   PCI related items                                                       */
/*                                                                           */
/*****************************************************************************/

#अगर_अघोषित PCI_VENDOR_ID_IDT
#घोषणा PCI_VENDOR_ID_IDT 0x111D
#पूर्ण_अगर /* PCI_VENDOR_ID_IDT */

#अगर_अघोषित PCI_DEVICE_ID_IDT_IDT77252
#घोषणा PCI_DEVICE_ID_IDT_IDT77252 0x0003
#पूर्ण_अगर /* PCI_DEVICE_ID_IDT_IDT772052 */


#पूर्ण_अगर /* !(_IDT77252_H) */
