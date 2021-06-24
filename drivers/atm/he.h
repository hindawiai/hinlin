<शैली गुरु>
/*

  he.h

  ForeRunnerHE ATM Adapter driver क्रम ATM on Linux
  Copyright (C) 1999-2001  Naval Research Laboratory

  This library is मुक्त software; you can redistribute it and/or
  modअगरy it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License क्रम more details.

  You should have received a copy of the GNU Lesser General Public
  License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*

  he.h

  ForeRunnerHE ATM Adapter driver क्रम ATM on Linux
  Copyright (C) 1999-2000  Naval Research Laboratory

  Permission to use, copy, modअगरy and distribute this software and its
  करोcumentation is hereby granted, provided that both the copyright
  notice and this permission notice appear in all copies of the software,
  derivative works or modअगरied versions, and any portions thereof, and
  that both notices appear in supporting करोcumentation.

  NRL ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION AND
  DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER
  RESULTING FROM THE USE OF THIS SOFTWARE.

 */

#अगर_अघोषित _HE_H_
#घोषणा _HE_H_

#घोषणा DEV_LABEL       "he"

#घोषणा CONFIG_DEFAULT_VCIBITS	12
#घोषणा CONFIG_DEFAULT_VPIBITS	0

#घोषणा CONFIG_IRQ_SIZE		128
#घोषणा CONFIG_IRQ_THRESH	(CONFIG_IRQ_SIZE/2)

#घोषणा CONFIG_TPDRQ_SIZE	512
#घोषणा TPDRQ_MASK(x)		(((अचिन्हित दीर्घ)(x))&((CONFIG_TPDRQ_SIZE<<3)-1))

#घोषणा CONFIG_RBRQ_SIZE	512
#घोषणा CONFIG_RBRQ_THRESH	400
#घोषणा RBRQ_MASK(x)		(((अचिन्हित दीर्घ)(x))&((CONFIG_RBRQ_SIZE<<3)-1))

#घोषणा CONFIG_TBRQ_SIZE	512
#घोषणा CONFIG_TBRQ_THRESH	400
#घोषणा TBRQ_MASK(x)		(((अचिन्हित दीर्घ)(x))&((CONFIG_TBRQ_SIZE<<2)-1))

#घोषणा CONFIG_RBPL_SIZE	512
#घोषणा CONFIG_RBPL_THRESH	64
#घोषणा CONFIG_RBPL_बफ_मानE	4096
#घोषणा RBPL_MASK(x)		(((अचिन्हित दीर्घ)(x))&((CONFIG_RBPL_SIZE<<3)-1))

/* 5.1.3 initialize connection memory */

#घोषणा CONFIG_RSRA		0x00000
#घोषणा CONFIG_RCMLBM		0x08000
#घोषणा CONFIG_RCMABR		0x0d800
#घोषणा CONFIG_RSRB		0x0e000

#घोषणा CONFIG_TSRA		0x00000
#घोषणा CONFIG_TSRB		0x08000
#घोषणा CONFIG_TSRC		0x0c000
#घोषणा CONFIG_TSRD		0x0e000
#घोषणा CONFIG_TMABR		0x0f000
#घोषणा CONFIG_TPDBA		0x10000

#घोषणा HE_MAXCIDBITS		12

/* 2.9.3.3 पूर्णांकerrupt encodings */

काष्ठा he_irq अणु
	अस्थिर u32 isw;
पूर्ण;

#घोषणा IRQ_ALIGNMENT		0x1000

#घोषणा NEXT_ENTRY(base, tail, mask) \
				(((अचिन्हित दीर्घ)base)|(((अचिन्हित दीर्घ)(tail+1))&mask))

#घोषणा ITYPE_INVALID		0xffffffff
#घोषणा ITYPE_TBRQ_THRESH	(0<<3)
#घोषणा ITYPE_TPD_COMPLETE	(1<<3)
#घोषणा ITYPE_RBPS_THRESH	(2<<3)
#घोषणा ITYPE_RBPL_THRESH	(3<<3)
#घोषणा ITYPE_RBRQ_THRESH	(4<<3)
#घोषणा ITYPE_RBRQ_TIMER	(5<<3)
#घोषणा ITYPE_PHY		(6<<3)
#घोषणा ITYPE_OTHER		0x80
#घोषणा ITYPE_PARITY		0x81
#घोषणा ITYPE_ABORT		0x82

#घोषणा ITYPE_GROUP(x)		(x & 0x7)
#घोषणा ITYPE_TYPE(x)		(x & 0xf8)

#घोषणा HE_NUM_GROUPS 8

/* 2.1.4 transmit packet descriptor */

काष्ठा he_tpd अणु

	/* पढ़ो by the adapter */

	अस्थिर u32 status;
	अस्थिर u32 reserved;

#घोषणा TPD_MAXIOV	3
	काष्ठा अणु
		u32 addr, len;
	पूर्ण iovec[TPD_MAXIOV];

#घोषणा address0 iovec[0].addr
#घोषणा length0 iovec[0].len

	/* linux-aपंचांग extensions */

	काष्ठा sk_buff *skb;
	काष्ठा aपंचांग_vcc *vcc;

	काष्ठा list_head entry;
पूर्ण;

#घोषणा TPD_ALIGNMENT	64
#घोषणा TPD_LEN_MASK	0xffff

#घोषणा TPD_ADDR_SHIFT  6
#घोषणा TPD_MASK	0xffffffc0
#घोषणा TPD_ADDR(x)	((x) & TPD_MASK)
#घोषणा TPD_INDEX(x)	(TPD_ADDR(x) >> TPD_ADDR_SHIFT)


/* table 2.3 transmit buffer वापस elements */

काष्ठा he_tbrq अणु
	अस्थिर u32 tbre;
पूर्ण;

#घोषणा TBRQ_ALIGNMENT	CONFIG_TBRQ_SIZE

#घोषणा TBRQ_TPD(tbrq)		((tbrq)->tbre & 0xffffffc0)
#घोषणा TBRQ_EOS(tbrq)		((tbrq)->tbre & (1<<3))
#घोषणा TBRQ_MULTIPLE(tbrq)	((tbrq)->tbre & (1))

/* table 2.21 receive buffer वापस queue element field organization */

काष्ठा he_rbrq अणु
	अस्थिर u32 addr;
	अस्थिर u32 cidlen;
पूर्ण;

#घोषणा RBRQ_ALIGNMENT	CONFIG_RBRQ_SIZE

#घोषणा RBRQ_ADDR(rbrq)		((rbrq)->addr & 0xffffffc0)
#घोषणा RBRQ_CRC_ERR(rbrq)	((rbrq)->addr & (1<<5))
#घोषणा RBRQ_LEN_ERR(rbrq)	((rbrq)->addr & (1<<4))
#घोषणा RBRQ_END_PDU(rbrq)	((rbrq)->addr & (1<<3))
#घोषणा RBRQ_AAL5_PROT(rbrq)	((rbrq)->addr & (1<<2))
#घोषणा RBRQ_CON_CLOSED(rbrq)	((rbrq)->addr & (1<<1))
#घोषणा RBRQ_HBUF_ERR(rbrq)	((rbrq)->addr & 1)
#घोषणा RBRQ_CID(rbrq)		(((rbrq)->cidlen >> 16) & 0x1fff)
#घोषणा RBRQ_BUFLEN(rbrq)	((rbrq)->cidlen & 0xffff)

/* figure 2.3 transmit packet descriptor पढ़ोy queue */

काष्ठा he_tpdrq अणु
	अस्थिर u32 tpd;
	अस्थिर u32 cid;
पूर्ण;

#घोषणा TPDRQ_ALIGNMENT CONFIG_TPDRQ_SIZE

/* table 2.30 host status page detail */

#घोषणा HSP_ALIGNMENT	0x400		/* must align on 1k boundary */

काष्ठा he_hsp अणु
	काष्ठा he_hsp_entry अणु
		अस्थिर u32 tbrq_tail; 
		अस्थिर u32 reserved1[15];
		अस्थिर u32 rbrq_tail; 
		अस्थिर u32 reserved2[15];
	पूर्ण group[HE_NUM_GROUPS];
पूर्ण;

/*
 * figure 2.9 receive buffer pools
 *
 * since a भव address might be more than 32 bits, we store an index
 * in the virt member of he_rbp.  NOTE: the lower six bits in the  rbrq
 * addr member are used क्रम buffer status further limiting us to 26 bits.
 */

काष्ठा he_rbp अणु
	अस्थिर u32 phys;
	अस्थिर u32 idx;	/* virt */
पूर्ण;

#घोषणा RBP_IDX_OFFSET 6

/*
 * the he dma engine will try to hold an extra 16 buffers in its local
 * caches.  and add a couple buffers क्रम safety.
 */

#घोषणा RBPL_TABLE_SIZE (CONFIG_RBPL_SIZE + 16 + 2)

काष्ठा he_buff अणु
	काष्ठा list_head entry;
	dma_addr_t mapping;
	अचिन्हित दीर्घ len;
	u8 data[];
पूर्ण;

#अगर_घोषित notyet
काष्ठा he_group अणु
	u32 rpbl_size, rpbl_qsize;
	काष्ठा he_rpb_entry *rbpl_ba;
पूर्ण;
#पूर्ण_अगर

#घोषणा HE_LOOKUP_VCC(dev, cid) ((dev)->he_vcc_table[(cid)].vcc)

काष्ठा he_vcc_table 
अणु
	काष्ठा aपंचांग_vcc *vcc;
पूर्ण;

काष्ठा he_cs_stper
अणु
	दीर्घ pcr;
	पूर्णांक inuse;
पूर्ण;

#घोषणा HE_NUM_CS_STPER		16

काष्ठा he_dev अणु
	अचिन्हित पूर्णांक number;
	अचिन्हित पूर्णांक irq;
	व्योम __iomem *membase;

	अक्षर prod_id[30];
	अक्षर mac_addr[6];
	पूर्णांक media;

	अचिन्हित पूर्णांक vcibits, vpibits;
	अचिन्हित पूर्णांक cells_per_row;
	अचिन्हित पूर्णांक bytes_per_row;
	अचिन्हित पूर्णांक cells_per_lbuf;
	अचिन्हित पूर्णांक r0_numrows, r0_startrow, r0_numbuffs;
	अचिन्हित पूर्णांक r1_numrows, r1_startrow, r1_numbuffs;
	अचिन्हित पूर्णांक tx_numrows, tx_startrow, tx_numbuffs;
	अचिन्हित पूर्णांक buffer_limit;

	काष्ठा he_vcc_table *he_vcc_table;

#अगर_घोषित notyet
	काष्ठा he_group group[HE_NUM_GROUPS];
#पूर्ण_अगर
	काष्ठा he_cs_stper cs_stper[HE_NUM_CS_STPER];
	अचिन्हित total_bw;

	dma_addr_t irq_phys;
	काष्ठा he_irq *irq_base, *irq_head, *irq_tail;
	अस्थिर अचिन्हित *irq_tailoffset;
	पूर्णांक irq_peak;

	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा dma_pool *tpd_pool;
	काष्ठा list_head outstanding_tpds;

	dma_addr_t tpdrq_phys;
	काष्ठा he_tpdrq *tpdrq_base, *tpdrq_tail, *tpdrq_head;

	spinlock_t global_lock;		/* 8.1.5 pci transaction ordering
					  error problem */
	dma_addr_t rbrq_phys;
	काष्ठा he_rbrq *rbrq_base, *rbrq_head;
	पूर्णांक rbrq_peak;

	काष्ठा he_buff **rbpl_virt;
	अचिन्हित दीर्घ *rbpl_table;
	अचिन्हित दीर्घ rbpl_hपूर्णांक;
	काष्ठा dma_pool *rbpl_pool;
	dma_addr_t rbpl_phys;
	काष्ठा he_rbp *rbpl_base, *rbpl_tail;
	काष्ठा list_head rbpl_outstanding;
	पूर्णांक rbpl_peak;

	dma_addr_t tbrq_phys;
	काष्ठा he_tbrq *tbrq_base, *tbrq_head;
	पूर्णांक tbrq_peak;

	dma_addr_t hsp_phys;
	काष्ठा he_hsp *hsp;

	काष्ठा pci_dev *pci_dev;
	काष्ठा aपंचांग_dev *aपंचांग_dev;
	काष्ठा he_dev *next;
पूर्ण;

#घोषणा HE_MAXIOV 20

काष्ठा he_vcc
अणु
	काष्ठा list_head buffers;
	पूर्णांक pdu_len;
	पूर्णांक rc_index;

	रुको_queue_head_t rx_रुकोq;
	रुको_queue_head_t tx_रुकोq;
पूर्ण;

#घोषणा HE_VCC(vcc)	((काष्ठा he_vcc *)(vcc->dev_data))

#घोषणा PCI_VENDOR_ID_FORE	0x1127
#घोषणा PCI_DEVICE_ID_FORE_HE	0x400

#घोषणा GEN_CNTL_0				0x40
#घोषणा  INT_PROC_ENBL		(1<<25)
#घोषणा  SLAVE_ENDIAN_MODE	(1<<16)
#घोषणा  MRL_ENB		(1<<5)
#घोषणा  MRM_ENB		(1<<4)
#घोषणा  INIT_ENB		(1<<2)
#घोषणा  IGNORE_TIMEOUT		(1<<1)
#घोषणा  ENBL_64		(1<<0)

#घोषणा MIN_PCI_LATENCY		32	/* errata 8.1.3 */

#घोषणा HE_DEV(dev) ((काष्ठा he_dev *) (dev)->dev_data)

#घोषणा he_is622(dev)	((dev)->media & 0x1)
#घोषणा he_isMM(dev)	((dev)->media & 0x20)

#घोषणा HE_REGMAP_SIZE	0x100000

#घोषणा RESET_CNTL	0x80000
#घोषणा  BOARD_RST_STATUS	(1<<6)

#घोषणा HOST_CNTL	0x80004
#घोषणा  PCI_BUS_SIZE64			(1<<27)
#घोषणा  DESC_RD_STATIC_64		(1<<26)
#घोषणा  DATA_RD_STATIC_64		(1<<25)
#घोषणा  DATA_WR_STATIC_64		(1<<24)
#घोषणा  ID_CS				(1<<12)
#घोषणा  ID_WREN			(1<<11)
#घोषणा  ID_DOUT			(1<<10)
#घोषणा   ID_DOFFSET			10
#घोषणा  ID_DIN				(1<<9)
#घोषणा  ID_CLOCK			(1<<8)
#घोषणा  QUICK_RD_RETRY			(1<<7)
#घोषणा  QUICK_WR_RETRY			(1<<6)
#घोषणा  OUTFF_ENB			(1<<5)
#घोषणा  CMDFF_ENB			(1<<4)
#घोषणा  PERR_INT_ENB			(1<<2)
#घोषणा  IGNORE_INTR			(1<<0)

#घोषणा LB_SWAP		0x80008
#घोषणा  SWAP_RNUM_MAX(x)	(x<<27)
#घोषणा  DATA_WR_SWAP		(1<<20)
#घोषणा  DESC_RD_SWAP		(1<<19)
#घोषणा  DATA_RD_SWAP		(1<<18)
#घोषणा  INTR_SWAP		(1<<17)
#घोषणा  DESC_WR_SWAP		(1<<16)
#घोषणा  SDRAM_INIT		(1<<15)
#घोषणा  BIG_ENDIAN_HOST	(1<<14)
#घोषणा  XFER_SIZE		(1<<7)

#घोषणा LB_MEM_ADDR	0x8000c
#घोषणा LB_MEM_DATA	0x80010

#घोषणा LB_MEM_ACCESS	0x80014
#घोषणा  LB_MEM_HNDSHK		(1<<30)
#घोषणा  LM_MEM_WRITE		(0x7)
#घोषणा  LM_MEM_READ		(0x3)

#घोषणा SDRAM_CTL	0x80018
#घोषणा  LB_64_ENB		(1<<3)
#घोषणा  LB_TWR			(1<<2)
#घोषणा  LB_TRP			(1<<1)
#घोषणा  LB_TRAS		(1<<0)

#घोषणा INT_FIFO	0x8001c
#घोषणा  INT_MASK_D		(1<<15)
#घोषणा  INT_MASK_C		(1<<14)
#घोषणा  INT_MASK_B		(1<<13)
#घोषणा  INT_MASK_A		(1<<12)
#घोषणा  INT_CLEAR_D		(1<<11)
#घोषणा  INT_CLEAR_C		(1<<10)
#घोषणा  INT_CLEAR_B		(1<<9)
#घोषणा  INT_CLEAR_A		(1<<8)

#घोषणा ABORT_ADDR	0x80020

#घोषणा IRQ0_BASE	0x80080
#घोषणा  IRQ_BASE(x)		(x<<12)
#घोषणा  IRQ_MASK		((CONFIG_IRQ_SIZE<<2)-1)	/* was 0x3ff */
#घोषणा  IRQ_TAIL(x)		(((अचिन्हित दीर्घ)(x)) & IRQ_MASK)
#घोषणा IRQ0_HEAD	0x80084
#घोषणा  IRQ_SIZE(x)		(x<<22)
#घोषणा  IRQ_THRESH(x)		(x<<12)
#घोषणा  IRQ_HEAD(x)		(x<<2)
/* #घोषणा  IRQ_PENDING		(1) 		conflict with linux/irq.h */
#घोषणा IRQ0_CNTL	0x80088
#घोषणा  IRQ_ADDRSEL(x)		(x<<2)
#घोषणा  IRQ_INT_A		(0<<2)
#घोषणा  IRQ_INT_B		(1<<2)
#घोषणा  IRQ_INT_C		(2<<2)
#घोषणा  IRQ_INT_D		(3<<2)
#घोषणा  IRQ_TYPE_ADDR		0x1
#घोषणा  IRQ_TYPE_LINE		0x0
#घोषणा IRQ0_DATA	0x8008c

#घोषणा IRQ1_BASE	0x80090
#घोषणा IRQ1_HEAD	0x80094
#घोषणा IRQ1_CNTL	0x80098
#घोषणा IRQ1_DATA	0x8009c

#घोषणा IRQ2_BASE	0x800a0
#घोषणा IRQ2_HEAD	0x800a4
#घोषणा IRQ2_CNTL	0x800a8
#घोषणा IRQ2_DATA	0x800ac

#घोषणा IRQ3_BASE	0x800b0
#घोषणा IRQ3_HEAD	0x800b4
#घोषणा IRQ3_CNTL	0x800b8
#घोषणा IRQ3_DATA	0x800bc

#घोषणा GRP_10_MAP	0x800c0
#घोषणा GRP_32_MAP	0x800c4
#घोषणा GRP_54_MAP	0x800c8
#घोषणा GRP_76_MAP	0x800cc

#घोषणा	G0_RBPS_S	0x80400
#घोषणा G0_RBPS_T	0x80404
#घोषणा  RBP_TAIL(x)		((x)<<3)
#घोषणा  RBP_MASK(x)		((x)|0x1fff)
#घोषणा G0_RBPS_QI	0x80408
#घोषणा  RBP_QSIZE(x)		((x)<<14)
#घोषणा  RBP_INT_ENB		(1<<13)
#घोषणा  RBP_THRESH(x)		(x)
#घोषणा G0_RBPS_BS	0x8040c
#घोषणा G0_RBPL_S	0x80410
#घोषणा G0_RBPL_T	0x80414
#घोषणा G0_RBPL_QI	0x80418 
#घोषणा G0_RBPL_BS	0x8041c

#घोषणा	G1_RBPS_S	0x80420
#घोषणा G1_RBPS_T	0x80424
#घोषणा G1_RBPS_QI	0x80428
#घोषणा G1_RBPS_BS	0x8042c
#घोषणा G1_RBPL_S	0x80430
#घोषणा G1_RBPL_T	0x80434
#घोषणा G1_RBPL_QI	0x80438
#घोषणा G1_RBPL_BS	0x8043c

#घोषणा	G2_RBPS_S	0x80440
#घोषणा G2_RBPS_T	0x80444
#घोषणा G2_RBPS_QI	0x80448
#घोषणा G2_RBPS_BS	0x8044c
#घोषणा G2_RBPL_S	0x80450
#घोषणा G2_RBPL_T	0x80454
#घोषणा G2_RBPL_QI	0x80458
#घोषणा G2_RBPL_BS	0x8045c

#घोषणा	G3_RBPS_S	0x80460
#घोषणा G3_RBPS_T	0x80464
#घोषणा G3_RBPS_QI	0x80468
#घोषणा G3_RBPS_BS	0x8046c
#घोषणा G3_RBPL_S	0x80470
#घोषणा G3_RBPL_T	0x80474
#घोषणा G3_RBPL_QI	0x80478
#घोषणा G3_RBPL_BS	0x8047c

#घोषणा	G4_RBPS_S	0x80480
#घोषणा G4_RBPS_T	0x80484
#घोषणा G4_RBPS_QI	0x80488
#घोषणा G4_RBPS_BS	0x8048c
#घोषणा G4_RBPL_S	0x80490
#घोषणा G4_RBPL_T	0x80494
#घोषणा G4_RBPL_QI	0x80498
#घोषणा G4_RBPL_BS	0x8049c

#घोषणा	G5_RBPS_S	0x804a0
#घोषणा G5_RBPS_T	0x804a4
#घोषणा G5_RBPS_QI	0x804a8
#घोषणा G5_RBPS_BS	0x804ac
#घोषणा G5_RBPL_S	0x804b0
#घोषणा G5_RBPL_T	0x804b4
#घोषणा G5_RBPL_QI	0x804b8
#घोषणा G5_RBPL_BS	0x804bc

#घोषणा	G6_RBPS_S	0x804c0
#घोषणा G6_RBPS_T	0x804c4
#घोषणा G6_RBPS_QI	0x804c8
#घोषणा G6_RBPS_BS	0x804cc
#घोषणा G6_RBPL_S	0x804d0
#घोषणा G6_RBPL_T	0x804d4
#घोषणा G6_RBPL_QI	0x804d8
#घोषणा G6_RBPL_BS	0x804dc

#घोषणा	G7_RBPS_S	0x804e0
#घोषणा G7_RBPS_T	0x804e4
#घोषणा G7_RBPS_QI	0x804e8
#घोषणा G7_RBPS_BS	0x804ec

#घोषणा G7_RBPL_S	0x804f0
#घोषणा G7_RBPL_T	0x804f4
#घोषणा G7_RBPL_QI	0x804f8
#घोषणा G7_RBPL_BS	0x804fc

#घोषणा G0_RBRQ_ST	0x80500
#घोषणा G0_RBRQ_H	0x80504
#घोषणा G0_RBRQ_Q	0x80508
#घोषणा  RBRQ_THRESH(x)		((x)<<13)
#घोषणा  RBRQ_SIZE(x)		(x)
#घोषणा G0_RBRQ_I	0x8050c
#घोषणा  RBRQ_TIME(x)		((x)<<8)
#घोषणा  RBRQ_COUNT(x)		(x)

/* fill in 1 ... 7 later */

#घोषणा G0_TBRQ_B_T	0x80600
#घोषणा G0_TBRQ_H	0x80604
#घोषणा G0_TBRQ_S	0x80608
#घोषणा G0_TBRQ_THRESH	0x8060c
#घोषणा  TBRQ_THRESH(x)		(x)

/* fill in 1 ... 7 later */

#घोषणा RH_CONFIG	0x805c0
#घोषणा  PHY_INT_ENB	(1<<10)
#घोषणा  OAM_GID(x)	(x<<7)
#घोषणा  PTMR_PRE(x)	(x)

#घोषणा G0_INMQ_S	0x80580
#घोषणा G0_INMQ_L	0x80584
#घोषणा G1_INMQ_S	0x80588
#घोषणा G1_INMQ_L	0x8058c
#घोषणा G2_INMQ_S	0x80590
#घोषणा G2_INMQ_L	0x80594
#घोषणा G3_INMQ_S	0x80598
#घोषणा G3_INMQ_L	0x8059c
#घोषणा G4_INMQ_S	0x805a0
#घोषणा G4_INMQ_L	0x805a4
#घोषणा G5_INMQ_S	0x805a8
#घोषणा G5_INMQ_L	0x805ac
#घोषणा G6_INMQ_S	0x805b0
#घोषणा G6_INMQ_L	0x805b4
#घोषणा G7_INMQ_S	0x805b8
#घोषणा G7_INMQ_L	0x805bc

#घोषणा TPDRQ_B_H	0x80680
#घोषणा TPDRQ_T		0x80684
#घोषणा TPDRQ_S		0x80688

#घोषणा UBUFF_BA	0x8068c

#घोषणा RLBF0_H		0x806c0
#घोषणा RLBF0_T		0x806c4
#घोषणा RLBF1_H		0x806c8
#घोषणा RLBF1_T		0x806cc
#घोषणा RLBC_H		0x806d0
#घोषणा RLBC_T		0x806d4
#घोषणा RLBC_H2		0x806d8
#घोषणा TLBF_H		0x806e0
#घोषणा TLBF_T		0x806e4
#घोषणा RLBF0_C		0x806e8
#घोषणा RLBF1_C		0x806ec
#घोषणा RXTHRSH		0x806f0
#घोषणा LITHRSH		0x806f4

#घोषणा LBARB		0x80700
#घोषणा  SLICE_X(x)		 (x<<28)
#घोषणा  ARB_RNUM_MAX(x)	 (x<<23)
#घोषणा  TH_PRTY(x)		 (x<<21)
#घोषणा  RH_PRTY(x)		 (x<<19)
#घोषणा  TL_PRTY(x)		 (x<<17)
#घोषणा  RL_PRTY(x)		 (x<<15)
#घोषणा  BUS_MULTI(x)		 (x<<8)
#घोषणा  NET_PREF(x)		 (x)

#घोषणा SDRAMCON	0x80704
#घोषणा	 BANK_ON		(1<<14)
#घोषणा	 WIDE_DATA		(1<<13)
#घोषणा	 TWR_WAIT		(1<<12)
#घोषणा	 TRP_WAIT		(1<<11)
#घोषणा	 TRAS_WAIT		(1<<10)
#घोषणा	 REF_RATE(x)		(x)

#घोषणा LBSTAT		0x80708

#घोषणा RCC_STAT	0x8070c
#घोषणा  RCC_BUSY		(1)

#घोषणा TCMCONFIG	0x80740
#घोषणा  TM_DESL2		(1<<10)
#घोषणा	 TM_BANK_WAIT(x)	(x<<6)
#घोषणा	 TM_ADD_BANK4(x)	(x<<4)
#घोषणा  TM_PAR_CHECK(x)	(x<<3)
#घोषणा  TM_RW_WAIT(x)		(x<<2)
#घोषणा  TM_SRAM_TYPE(x)	(x)

#घोषणा TSRB_BA		0x80744	
#घोषणा TSRC_BA		0x80748	
#घोषणा TMABR_BA	0x8074c	
#घोषणा TPD_BA		0x80750	
#घोषणा TSRD_BA		0x80758	

#घोषणा TX_CONFIG	0x80760
#घोषणा  DRF_THRESH(x)		(x<<22)
#घोषणा  TX_UT_MODE(x)		(x<<21)
#घोषणा  TX_VCI_MASK(x)		(x<<17)
#घोषणा  LBFREE_CNT(x)		(x)

#घोषणा TXAAL5_PROTO	0x80764
#घोषणा  CPCS_UU(x)		(x<<8)
#घोषणा  CPI(x)			(x)

#घोषणा RCMCONFIG	0x80780
#घोषणा  RM_DESL2(x)		(x<<10)
#घोषणा  RM_BANK_WAIT(x)	(x<<6)
#घोषणा  RM_ADD_BANK(x)		(x<<4)
#घोषणा  RM_PAR_CHECK(x)	(x<<3)
#घोषणा  RM_RW_WAIT(x)		(x<<2)
#घोषणा  RM_SRAM_TYPE(x)	(x)

#घोषणा RCMRSRB_BA	0x80784
#घोषणा RCMLBM_BA	0x80788
#घोषणा RCMABR_BA	0x8078c

#घोषणा RC_CONFIG	0x807c0
#घोषणा  UT_RD_DELAY(x)		(x<<11)
#घोषणा  WRAP_MODE(x)		(x<<10)
#घोषणा  RC_UT_MODE(x)		(x<<9)
#घोषणा  RX_ENABLE		(1<<8)
#घोषणा  RX_VALVP(x)		(x<<4)
#घोषणा  RX_VALVC(x)		(x)

#घोषणा MCC		0x807c4
#घोषणा OEC		0x807c8
#घोषणा DCC		0x807cc
#घोषणा CEC		0x807d0

#घोषणा HSP_BA		0x807f0

#घोषणा LB_CONFIG	0x807f4
#घोषणा  LB_SIZE(x)		(x)

#घोषणा CON_DAT		0x807f8
#घोषणा CON_CTL		0x807fc
#घोषणा  CON_CTL_MBOX		(2<<30)
#घोषणा  CON_CTL_TCM		(1<<30)
#घोषणा  CON_CTL_RCM		(0<<30)
#घोषणा  CON_CTL_WRITE		(1<<29)
#घोषणा  CON_CTL_READ		(0<<29)
#घोषणा  CON_CTL_BUSY		(1<<28)
#घोषणा  CON_BYTE_DISABLE_3	(1<<22)		/* 24..31 */
#घोषणा  CON_BYTE_DISABLE_2	(1<<21)		/* 16..23 */
#घोषणा  CON_BYTE_DISABLE_1	(1<<20)		/* 8..15 */
#घोषणा  CON_BYTE_DISABLE_0	(1<<19)		/* 0..7 */
#घोषणा  CON_CTL_ADDR(x)	(x)

#घोषणा FRAMER		0x80800		/* to 0x80bfc */

/* 3.3 network controller (पूर्णांकernal) mailbox रेजिस्टरs */

#घोषणा CS_STPER0	0x0
	/* ... */
#घोषणा CS_STPER31	0x01f

#घोषणा CS_STTIM0	0x020
	/* ... */
#घोषणा CS_STTIM31	0x03f

#घोषणा CS_TGRLD0	0x040
	/* ... */
#घोषणा CS_TGRLD15	0x04f

#घोषणा CS_ERTHR0	0x050
#घोषणा CS_ERTHR1	0x051
#घोषणा CS_ERTHR2	0x052
#घोषणा CS_ERTHR3	0x053
#घोषणा CS_ERTHR4	0x054
#घोषणा CS_ERCTL0	0x055
#घोषणा  TX_ENABLE		(1<<28)
#घोषणा  ER_ENABLE		(1<<27)
#घोषणा CS_ERCTL1	0x056
#घोषणा CS_ERCTL2	0x057
#घोषणा CS_ERSTAT0	0x058
#घोषणा CS_ERSTAT1	0x059

#घोषणा CS_RTCCT	0x060
#घोषणा CS_RTFWC	0x061
#घोषणा CS_RTFWR	0x062
#घोषणा CS_RTFTC	0x063
#घोषणा CS_RTATR	0x064

#घोषणा CS_TFBSET	0x070
#घोषणा CS_TFBADD	0x071
#घोषणा CS_TFBSUB	0x072
#घोषणा CS_WCRMAX	0x073
#घोषणा CS_WCRMIN	0x074
#घोषणा CS_WCRINC	0x075
#घोषणा CS_WCRDEC	0x076
#घोषणा CS_WCRCEIL	0x077
#घोषणा CS_BWDCNT	0x078

#घोषणा CS_OTPPER	0x080
#घोषणा CS_OTWPER	0x081
#घोषणा CS_OTTLIM	0x082
#घोषणा CS_OTTCNT	0x083

#घोषणा CS_HGRRT0	0x090
	/* ... */
#घोषणा CS_HGRRT7	0x097

#घोषणा CS_ORPTRS	0x0a0

#घोषणा RXCON_CLOSE	0x100


#घोषणा RCM_MEM_SIZE	0x10000		/* 1M of 32-bit रेजिस्टरs */
#घोषणा TCM_MEM_SIZE	0x20000		/* 2M of 32-bit रेजिस्टरs */

/* 2.5 transmit connection memory रेजिस्टरs */

#घोषणा TSR0_CONN_STATE(x)	((x>>28) & 0x7)
#घोषणा TSR0_USE_WMIN		(1<<23)
#घोषणा TSR0_GROUP(x)		((x & 0x7)<<18)
#घोषणा TSR0_ABR		(2<<16)
#घोषणा TSR0_UBR		(1<<16)
#घोषणा TSR0_CBR		(0<<16)
#घोषणा TSR0_PROT		(1<<15)
#घोषणा TSR0_AAL0_SDU		(2<<12)
#घोषणा TSR0_AAL0		(1<<12)
#घोषणा TSR0_AAL5		(0<<12)
#घोषणा TSR0_HALT_ER		(1<<11)
#घोषणा TSR0_MARK_CI		(1<<10)
#घोषणा TSR0_MARK_ER		(1<<9)
#घोषणा TSR0_UPDATE_GER		(1<<8)
#घोषणा TSR0_RC_INDEX(x)	(x & 0x1F)

#घोषणा TSR1_PCR(x)		((x & 0x7FFF)<<16)
#घोषणा TSR1_MCR(x)		(x & 0x7FFF)

#घोषणा TSR2_ACR(x)		((x & 0x7FFF)<<16)

#घोषणा TSR3_NRM_CNT(x)		((x & 0xFF)<<24)
#घोषणा TSR3_CRM_CNT(x)		(x & 0xFFFF)

#घोषणा TSR4_FLUSH_CONN		(1<<31)
#घोषणा TSR4_SESSION_ENDED	(1<<30)
#घोषणा TSR4_CRC10		(1<<28)
#घोषणा TSR4_शून्य_CRC10		(1<<27)
#घोषणा TSR4_PROT		(1<<26)
#घोषणा TSR4_AAL0_SDU		(2<<23)
#घोषणा TSR4_AAL0		(1<<23)
#घोषणा TSR4_AAL5		(0<<23)

#घोषणा TSR9_OPEN_CONN		(1<<20)

#घोषणा TSR11_ICR(x)		((x & 0x7FFF)<<16)
#घोषणा TSR11_TRM(x)		((x & 0x7)<<13)
#घोषणा TSR11_NRM(x)		((x & 0x7)<<10)
#घोषणा TSR11_ADTF(x)		(x & 0x3FF)

#घोषणा TSR13_RDF(x)		((x & 0xF)<<23)
#घोषणा TSR13_RIF(x)		((x & 0xF)<<19)
#घोषणा TSR13_CDF(x)		((x & 0x7)<<16)
#घोषणा TSR13_CRM(x)		(x & 0xFFFF)

#घोषणा TSR14_DELETE		(1<<31)
#घोषणा TSR14_ABR_CLOSE		(1<<16)

/* 2.7.1 per connection receieve state रेजिस्टरs */

#घोषणा RSR0_START_PDU	(1<<10)
#घोषणा RSR0_OPEN_CONN	(1<<6)
#घोषणा RSR0_CLOSE_CONN	(0<<6)
#घोषणा RSR0_PPD_ENABLE	(1<<5)
#घोषणा RSR0_EPD_ENABLE	(1<<4)
#घोषणा RSR0_TCP_CKSUM	(1<<3)
#घोषणा RSR0_AAL5		(0)
#घोषणा RSR0_AAL0		(1)
#घोषणा RSR0_AAL0_SDU		(2)
#घोषणा RSR0_RAWCELL		(3)
#घोषणा RSR0_RAWCELL_CRC10	(4)

#घोषणा RSR1_AQI_ENABLE	(1<<20)
#घोषणा RSR1_RBPL_ONLY	(1<<19)
#घोषणा RSR1_GROUP(x)	((x)<<16)

#घोषणा RSR4_AQI_ENABLE (1<<30)
#घोषणा RSR4_GROUP(x)	((x)<<27)
#घोषणा RSR4_RBPL_ONLY	(1<<26)

/* 2.1.4 transmit packet descriptor */

#घोषणा	TPD_USERCELL		0x0
#घोषणा	TPD_SEGMENT_OAMF5	0x4
#घोषणा	TPD_END2END_OAMF5	0x5
#घोषणा	TPD_RMCELL		0x6
#घोषणा TPD_CELLTYPE(x)		(x<<3)
#घोषणा TPD_EOS			(1<<2)
#घोषणा TPD_CLP			(1<<1)
#घोषणा TPD_INT			(1<<0)
#घोषणा TPD_LST		(1<<31)

/* table 4.3 serial eeprom inक्रमmation */

#घोषणा PROD_ID		0x08	/* अक्षर[] */
#घोषणा  PROD_ID_LEN	30
#घोषणा HW_REV		0x26	/* अक्षर[] */
#घोषणा M_SN		0x3a	/* पूर्णांकeger */
#घोषणा MEDIA		0x3e	/* पूर्णांकeger */
#घोषणा  HE155MM	0x26
#घोषणा  HE622MM	0x27
#घोषणा  HE155SM	0x46
#घोषणा  HE622SM	0x47
#घोषणा MAC_ADDR	0x42	/* अक्षर[] */

#घोषणा CS_LOW		0x0
#घोषणा CS_HIGH		ID_CS /* HOST_CNTL_ID_PROM_SEL */
#घोषणा CLK_LOW		0x0
#घोषणा CLK_HIGH	ID_CLOCK /* HOST_CNTL_ID_PROM_CLOCK */
#घोषणा SI_HIGH		ID_DIN /* HOST_CNTL_ID_PROM_DATA_IN */
#घोषणा EEPROM_DELAY	400 /* microseconds */

#पूर्ण_अगर /* _HE_H_ */
