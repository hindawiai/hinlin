<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>

#समावेश <brcmu_utils.h>
#समावेश <aiutils.h>
#समावेश "types.h"
#समावेश "main.h"
#समावेश "dma.h"
#समावेश "soc.h"
#समावेश "scb.h"
#समावेश "ampdu.h"
#समावेश "debug.h"
#समावेश "brcms_trace_events.h"

/*
 * dma रेजिस्टर field offset calculation
 */
#घोषणा DMA64REGOFFS(field)		दुरत्व(काष्ठा dma64regs, field)
#घोषणा DMA64TXREGOFFS(di, field)	(di->d64txregbase + DMA64REGOFFS(field))
#घोषणा DMA64RXREGOFFS(di, field)	(di->d64rxregbase + DMA64REGOFFS(field))

/*
 * DMA hardware requires each descriptor ring to be 8kB aligned, and fit within
 * a contiguous 8kB physical address.
 */
#घोषणा D64RINGALIGN_BITS	13
#घोषणा	D64MAXRINGSZ		(1 << D64RINGALIGN_BITS)
#घोषणा	D64RINGALIGN		(1 << D64RINGALIGN_BITS)

#घोषणा	D64MAXDD	(D64MAXRINGSZ / माप(काष्ठा dma64desc))

/* transmit channel control */
#घोषणा	D64_XC_XE		0x00000001	/* transmit enable */
#घोषणा	D64_XC_SE		0x00000002	/* transmit suspend request */
#घोषणा	D64_XC_LE		0x00000004	/* loopback enable */
#घोषणा	D64_XC_FL		0x00000010	/* flush request */
#घोषणा	D64_XC_PD		0x00000800	/* parity check disable */
#घोषणा	D64_XC_AE		0x00030000	/* address extension bits */
#घोषणा	D64_XC_AE_SHIFT		16

/* transmit descriptor table poपूर्णांकer */
#घोषणा	D64_XP_LD_MASK		0x00000fff	/* last valid descriptor */

/* transmit channel status */
#घोषणा	D64_XS0_CD_MASK		0x00001fff	/* current descriptor poपूर्णांकer */
#घोषणा	D64_XS0_XS_MASK		0xf0000000	/* transmit state */
#घोषणा	D64_XS0_XS_SHIFT		28
#घोषणा	D64_XS0_XS_DISABLED	0x00000000	/* disabled */
#घोषणा	D64_XS0_XS_ACTIVE	0x10000000	/* active */
#घोषणा	D64_XS0_XS_IDLE		0x20000000	/* idle रुको */
#घोषणा	D64_XS0_XS_STOPPED	0x30000000	/* stopped */
#घोषणा	D64_XS0_XS_SUSP		0x40000000	/* suspend pending */

#घोषणा	D64_XS1_AD_MASK		0x00001fff	/* active descriptor */
#घोषणा	D64_XS1_XE_MASK		0xf0000000	/* transmit errors */
#घोषणा	D64_XS1_XE_SHIFT		28
#घोषणा	D64_XS1_XE_NOERR	0x00000000	/* no error */
#घोषणा	D64_XS1_XE_DPE		0x10000000	/* descriptor protocol error */
#घोषणा	D64_XS1_XE_DFU		0x20000000	/* data fअगरo underrun */
#घोषणा	D64_XS1_XE_DTE		0x30000000	/* data transfer error */
#घोषणा	D64_XS1_XE_DESRE	0x40000000	/* descriptor पढ़ो error */
#घोषणा	D64_XS1_XE_COREE	0x50000000	/* core error */

/* receive channel control */
/* receive enable */
#घोषणा	D64_RC_RE		0x00000001
/* receive frame offset */
#घोषणा	D64_RC_RO_MASK		0x000000fe
#घोषणा	D64_RC_RO_SHIFT		1
/* direct fअगरo receive (pio) mode */
#घोषणा	D64_RC_FM		0x00000100
/* separate rx header descriptor enable */
#घोषणा	D64_RC_SH		0x00000200
/* overflow जारी */
#घोषणा	D64_RC_OC		0x00000400
/* parity check disable */
#घोषणा	D64_RC_PD		0x00000800
/* address extension bits */
#घोषणा	D64_RC_AE		0x00030000
#घोषणा	D64_RC_AE_SHIFT		16

/* flags क्रम dma controller */
/* partity enable */
#घोषणा DMA_CTRL_PEN		(1 << 0)
/* rx overflow जारी */
#घोषणा DMA_CTRL_ROC		(1 << 1)
/* allow rx scatter to multiple descriptors */
#घोषणा DMA_CTRL_RXMULTI	(1 << 2)
/* Unframed Rx/Tx data */
#घोषणा DMA_CTRL_UNFRAMED	(1 << 3)

/* receive descriptor table poपूर्णांकer */
#घोषणा	D64_RP_LD_MASK		0x00000fff	/* last valid descriptor */

/* receive channel status */
#घोषणा	D64_RS0_CD_MASK		0x00001fff	/* current descriptor poपूर्णांकer */
#घोषणा	D64_RS0_RS_MASK		0xf0000000	/* receive state */
#घोषणा	D64_RS0_RS_SHIFT		28
#घोषणा	D64_RS0_RS_DISABLED	0x00000000	/* disabled */
#घोषणा	D64_RS0_RS_ACTIVE	0x10000000	/* active */
#घोषणा	D64_RS0_RS_IDLE		0x20000000	/* idle रुको */
#घोषणा	D64_RS0_RS_STOPPED	0x30000000	/* stopped */
#घोषणा	D64_RS0_RS_SUSP		0x40000000	/* suspend pending */

#घोषणा	D64_RS1_AD_MASK		0x0001ffff	/* active descriptor */
#घोषणा	D64_RS1_RE_MASK		0xf0000000	/* receive errors */
#घोषणा	D64_RS1_RE_SHIFT		28
#घोषणा	D64_RS1_RE_NOERR	0x00000000	/* no error */
#घोषणा	D64_RS1_RE_DPO		0x10000000	/* descriptor protocol error */
#घोषणा	D64_RS1_RE_DFU		0x20000000	/* data fअगरo overflow */
#घोषणा	D64_RS1_RE_DTE		0x30000000	/* data transfer error */
#घोषणा	D64_RS1_RE_DESRE	0x40000000	/* descriptor पढ़ो error */
#घोषणा	D64_RS1_RE_COREE	0x50000000	/* core error */

/* fअगरoaddr */
#घोषणा	D64_FA_OFF_MASK		0xffff	/* offset */
#घोषणा	D64_FA_SEL_MASK		0xf0000	/* select */
#घोषणा	D64_FA_SEL_SHIFT	16
#घोषणा	D64_FA_SEL_XDD		0x00000	/* transmit dma data */
#घोषणा	D64_FA_SEL_XDP		0x10000	/* transmit dma poपूर्णांकers */
#घोषणा	D64_FA_SEL_RDD		0x40000	/* receive dma data */
#घोषणा	D64_FA_SEL_RDP		0x50000	/* receive dma poपूर्णांकers */
#घोषणा	D64_FA_SEL_XFD		0x80000	/* transmit fअगरo data */
#घोषणा	D64_FA_SEL_XFP		0x90000	/* transmit fअगरo poपूर्णांकers */
#घोषणा	D64_FA_SEL_RFD		0xc0000	/* receive fअगरo data */
#घोषणा	D64_FA_SEL_RFP		0xd0000	/* receive fअगरo poपूर्णांकers */
#घोषणा	D64_FA_SEL_RSD		0xe0000	/* receive frame status data */
#घोषणा	D64_FA_SEL_RSP		0xf0000	/* receive frame status poपूर्णांकers */

/* descriptor control flags 1 */
#घोषणा D64_CTRL_COREFLAGS	0x0ff00000	/* core specअगरic flags */
#घोषणा	D64_CTRL1_EOT		((u32)1 << 28)	/* end of descriptor table */
#घोषणा	D64_CTRL1_IOC		((u32)1 << 29)	/* पूर्णांकerrupt on completion */
#घोषणा	D64_CTRL1_खातापूर्ण		((u32)1 << 30)	/* end of frame */
#घोषणा	D64_CTRL1_SOF		((u32)1 << 31)	/* start of frame */

/* descriptor control flags 2 */
/* buffer byte count. real data len must <= 16KB */
#घोषणा	D64_CTRL2_BC_MASK	0x00007fff
/* address extension bits */
#घोषणा	D64_CTRL2_AE		0x00030000
#घोषणा	D64_CTRL2_AE_SHIFT	16
/* parity bit */
#घोषणा D64_CTRL2_PARITY	0x00040000

/* control flags in the range [27:20] are core-specअगरic and not defined here */
#घोषणा	D64_CTRL_CORE_MASK	0x0ff00000

#घोषणा D64_RX_FRM_STS_LEN	0x0000ffff	/* frame length mask */
#घोषणा D64_RX_FRM_STS_OVFL	0x00800000	/* RxOverFlow */
#घोषणा D64_RX_FRM_STS_DSCRCNT	0x0f000000  /* no. of descriptors used - 1 */
#घोषणा D64_RX_FRM_STS_DATATYPE	0xf0000000	/* core-dependent data type */

/*
 * packet headroom necessary to accommodate the largest header
 * in the प्रणाली, (i.e TXOFF). By करोing, we aव्योम the need to
 * allocate an extra buffer क्रम the header when bridging to WL.
 * There is a compile समय check in wlc.c which ensure that this
 * value is at least as big as TXOFF. This value is used in
 * dma_rxfill().
 */

#घोषणा BCMEXTRAHDROOM 172

#घोषणा	MAXNAMEL	8	/* 8 अक्षर names */

/* macros to convert between byte offsets and indexes */
#घोषणा	B2I(bytes, type)	((bytes) / माप(type))
#घोषणा	I2B(index, type)	((index) * माप(type))

#घोषणा	PCI32ADDR_HIGH		0xc0000000	/* address[31:30] */
#घोषणा	PCI32ADDR_HIGH_SHIFT	30	/* address[31:30] */

#घोषणा	PCI64ADDR_HIGH		0x80000000	/* address[63] */
#घोषणा	PCI64ADDR_HIGH_SHIFT	31	/* address[63] */

/*
 * DMA Descriptor
 * Descriptors are only पढ़ो by the hardware, never written back.
 */
काष्ठा dma64desc अणु
	__le32 ctrl1;	/* misc control bits & bufcount */
	__le32 ctrl2;	/* buffer count and address extension */
	__le32 addrlow;	/* memory address of the date buffer, bits 31:0 */
	__le32 addrhigh; /* memory address of the date buffer, bits 63:32 */
पूर्ण;

/* dma engine software state */
काष्ठा dma_info अणु
	काष्ठा dma_pub dma; /* exported काष्ठाure */
	अक्षर name[MAXNAMEL];	/* callers name क्रम diag msgs */

	काष्ठा bcma_device *core;
	काष्ठा device *dmadev;

	/* session inक्रमmation क्रम AMPDU */
	काष्ठा brcms_ampdu_session ampdu_session;

	bool dma64;	/* this dma engine is operating in 64-bit mode */
	bool addrext;	/* this dma engine supports DmaExtendedAddrChanges */

	/* 64-bit dma tx engine रेजिस्टरs */
	uपूर्णांक d64txregbase;
	/* 64-bit dma rx engine रेजिस्टरs */
	uपूर्णांक d64rxregbase;
	/* poपूर्णांकer to dma64 tx descriptor ring */
	काष्ठा dma64desc *txd64;
	/* poपूर्णांकer to dma64 rx descriptor ring */
	काष्ठा dma64desc *rxd64;

	u16 dmadesc_align;	/* alignment requirement क्रम dma descriptors */

	u16 ntxd;		/* # tx descriptors tunable */
	u16 txin;		/* index of next descriptor to reclaim */
	u16 txout;		/* index of next descriptor to post */
	/* poपूर्णांकer to parallel array of poपूर्णांकers to packets */
	काष्ठा sk_buff **txp;
	/* Aligned physical address of descriptor ring */
	dma_addr_t txdpa;
	/* Original physical address of descriptor ring */
	dma_addr_t txdpaorig;
	u16 txdalign;	/* #bytes added to alloc'd mem to align txd */
	u32 txdalloc;	/* #bytes allocated क्रम the ring */
	u32 xmtptrbase;	/* When using unaligned descriptors, the ptr रेजिस्टर
			 * is not just an index, it needs all 13 bits to be
			 * an offset from the addr रेजिस्टर.
			 */

	u16 nrxd;	/* # rx descriptors tunable */
	u16 rxin;	/* index of next descriptor to reclaim */
	u16 rxout;	/* index of next descriptor to post */
	/* poपूर्णांकer to parallel array of poपूर्णांकers to packets */
	काष्ठा sk_buff **rxp;
	/* Aligned physical address of descriptor ring */
	dma_addr_t rxdpa;
	/* Original physical address of descriptor ring */
	dma_addr_t rxdpaorig;
	u16 rxdalign;	/* #bytes added to alloc'd mem to align rxd */
	u32 rxdalloc;	/* #bytes allocated क्रम the ring */
	u32 rcvptrbase;	/* Base क्रम ptr reg when using unaligned descriptors */

	/* tunables */
	अचिन्हित पूर्णांक rxbufsize;	/* rx buffer size in bytes, not including
				 * the extra headroom
				 */
	uपूर्णांक rxextrahdrroom;	/* extra rx headroom, reverseved to assist upper
				 * stack, e.g. some rx pkt buffers will be
				 * bridged to tx side without byte copying.
				 * The extra headroom needs to be large enough
				 * to fit txheader needs. Some करोngle driver may
				 * not need it.
				 */
	uपूर्णांक nrxpost;		/* # rx buffers to keep posted */
	अचिन्हित पूर्णांक rxoffset;	/* rxcontrol offset */
	/* add to get dma address of descriptor ring, low 32 bits */
	uपूर्णांक dकरोffsetlow;
	/*   high 32 bits */
	uपूर्णांक dकरोffsethigh;
	/* add to get dma address of data buffer, low 32 bits */
	uपूर्णांक dataoffsetlow;
	/*   high 32 bits */
	uपूर्णांक dataoffsethigh;
	/* descriptor base need to be aligned or not */
	bool aligndesc_4k;
पूर्ण;

/* Check क्रम odd number of 1's */
अटल u32 parity32(__le32 data)
अणु
	/* no swap needed क्रम counting 1's */
	u32 par_data = *(u32 *)&data;

	par_data ^= par_data >> 16;
	par_data ^= par_data >> 8;
	par_data ^= par_data >> 4;
	par_data ^= par_data >> 2;
	par_data ^= par_data >> 1;

	वापस par_data & 1;
पूर्ण

अटल bool dma64_dd_parity(काष्ठा dma64desc *dd)
अणु
	वापस parity32(dd->addrlow ^ dd->addrhigh ^ dd->ctrl1 ^ dd->ctrl2);
पूर्ण

/* descriptor bumping functions */

अटल uपूर्णांक xxd(uपूर्णांक x, uपूर्णांक n)
अणु
	वापस x & (n - 1); /* faster than %, but n must be घातer of 2 */
पूर्ण

अटल uपूर्णांक txd(काष्ठा dma_info *di, uपूर्णांक x)
अणु
	वापस xxd(x, di->ntxd);
पूर्ण

अटल uपूर्णांक rxd(काष्ठा dma_info *di, uपूर्णांक x)
अणु
	वापस xxd(x, di->nrxd);
पूर्ण

अटल uपूर्णांक nexttxd(काष्ठा dma_info *di, uपूर्णांक i)
अणु
	वापस txd(di, i + 1);
पूर्ण

अटल uपूर्णांक prevtxd(काष्ठा dma_info *di, uपूर्णांक i)
अणु
	वापस txd(di, i - 1);
पूर्ण

अटल uपूर्णांक nextrxd(काष्ठा dma_info *di, uपूर्णांक i)
अणु
	वापस rxd(di, i + 1);
पूर्ण

अटल uपूर्णांक ntxdactive(काष्ठा dma_info *di, uपूर्णांक h, uपूर्णांक t)
अणु
	वापस txd(di, t-h);
पूर्ण

अटल uपूर्णांक nrxdactive(काष्ठा dma_info *di, uपूर्णांक h, uपूर्णांक t)
अणु
	वापस rxd(di, t-h);
पूर्ण

अटल uपूर्णांक _dma_ctrlflags(काष्ठा dma_info *di, uपूर्णांक mask, uपूर्णांक flags)
अणु
	uपूर्णांक dmactrlflags;

	अगर (di == शून्य)
		वापस 0;

	dmactrlflags = di->dma.dmactrlflags;
	dmactrlflags &= ~mask;
	dmactrlflags |= flags;

	/* If trying to enable parity, check अगर parity is actually supported */
	अगर (dmactrlflags & DMA_CTRL_PEN) अणु
		u32 control;

		control = bcma_पढ़ो32(di->core, DMA64TXREGOFFS(di, control));
		bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, control),
		      control | D64_XC_PD);
		अगर (bcma_पढ़ो32(di->core, DMA64TXREGOFFS(di, control)) &
		    D64_XC_PD)
			/* We *can* disable it so it is supported,
			 * restore control रेजिस्टर
			 */
			bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, control),
				     control);
		अन्यथा
			/* Not supported, करोn't allow it to be enabled */
			dmactrlflags &= ~DMA_CTRL_PEN;
	पूर्ण

	di->dma.dmactrlflags = dmactrlflags;

	वापस dmactrlflags;
पूर्ण

अटल bool _dma64_addrext(काष्ठा dma_info *di, uपूर्णांक ctrl_offset)
अणु
	u32 w;
	bcma_set32(di->core, ctrl_offset, D64_XC_AE);
	w = bcma_पढ़ो32(di->core, ctrl_offset);
	bcma_mask32(di->core, ctrl_offset, ~D64_XC_AE);
	वापस (w & D64_XC_AE) == D64_XC_AE;
पूर्ण

/*
 * वापस true अगर this dma engine supports DmaExtendedAddrChanges,
 * otherwise false
 */
अटल bool _dma_isaddrext(काष्ठा dma_info *di)
अणु
	/* DMA64 supports full 32- or 64-bit operation. AE is always valid */

	/* not all tx or rx channel are available */
	अगर (di->d64txregbase != 0) अणु
		अगर (!_dma64_addrext(di, DMA64TXREGOFFS(di, control)))
			brcms_dbg_dma(di->core,
				      "%s: DMA64 tx doesn't have AE set\n",
				      di->name);
		वापस true;
	पूर्ण अन्यथा अगर (di->d64rxregbase != 0) अणु
		अगर (!_dma64_addrext(di, DMA64RXREGOFFS(di, control)))
			brcms_dbg_dma(di->core,
				      "%s: DMA64 rx doesn't have AE set\n",
				      di->name);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool _dma_descriptor_align(काष्ठा dma_info *di)
अणु
	u32 addrl;

	/* Check to see अगर the descriptors need to be aligned on 4K/8K or not */
	अगर (di->d64txregbase != 0) अणु
		bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, addrlow), 0xff0);
		addrl = bcma_पढ़ो32(di->core, DMA64TXREGOFFS(di, addrlow));
		अगर (addrl != 0)
			वापस false;
	पूर्ण अन्यथा अगर (di->d64rxregbase != 0) अणु
		bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, addrlow), 0xff0);
		addrl = bcma_पढ़ो32(di->core, DMA64RXREGOFFS(di, addrlow));
		अगर (addrl != 0)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Descriptor table must start at the DMA hardware dictated alignment, so
 * allocated memory must be large enough to support this requirement.
 */
अटल व्योम *dma_alloc_consistent(काष्ठा dma_info *di, uपूर्णांक size,
				  u16 align_bits, uपूर्णांक *alloced,
				  dma_addr_t *pap)
अणु
	अगर (align_bits) अणु
		u16 align = (1 << align_bits);
		अगर (!IS_ALIGNED(PAGE_SIZE, align))
			size += align;
		*alloced = size;
	पूर्ण
	वापस dma_alloc_coherent(di->dmadev, size, pap, GFP_ATOMIC);
पूर्ण

अटल
u8 dma_align_sizetobits(uपूर्णांक size)
अणु
	u8 bitpos = 0;
	जबतक (size >>= 1)
		bitpos++;
	वापस bitpos;
पूर्ण

/* This function ensures that the DMA descriptor ring will not get allocated
 * across Page boundary. If the allocation is करोne across the page boundary
 * at the first समय, then it is मुक्तd and the allocation is करोne at
 * descriptor ring size aligned location. This will ensure that the ring will
 * not cross page boundary
 */
अटल व्योम *dma_ringalloc(काष्ठा dma_info *di, u32 boundary, uपूर्णांक size,
			   u16 *alignbits, uपूर्णांक *alloced,
			   dma_addr_t *descpa)
अणु
	व्योम *va;
	u32 desc_strtaddr;
	u32 alignbytes = 1 << *alignbits;

	va = dma_alloc_consistent(di, size, *alignbits, alloced, descpa);

	अगर (शून्य == va)
		वापस शून्य;

	desc_strtaddr = (u32) roundup((अचिन्हित दीर्घ)va, alignbytes);
	अगर (((desc_strtaddr + size - 1) & boundary) != (desc_strtaddr
							& boundary)) अणु
		*alignbits = dma_align_sizetobits(size);
		dma_मुक्त_coherent(di->dmadev, size, va, *descpa);
		va = dma_alloc_consistent(di, size, *alignbits,
			alloced, descpa);
	पूर्ण
	वापस va;
पूर्ण

अटल bool dma64_alloc(काष्ठा dma_info *di, uपूर्णांक direction)
अणु
	u16 size;
	uपूर्णांक ddlen;
	व्योम *va;
	uपूर्णांक alloced = 0;
	u16 align;
	u16 align_bits;

	ddlen = माप(काष्ठा dma64desc);

	size = (direction == DMA_TX) ? (di->ntxd * ddlen) : (di->nrxd * ddlen);
	align_bits = di->dmadesc_align;
	align = (1 << align_bits);

	अगर (direction == DMA_TX) अणु
		va = dma_ringalloc(di, D64RINGALIGN, size, &align_bits,
			&alloced, &di->txdpaorig);
		अगर (va == शून्य) अणु
			brcms_dbg_dma(di->core,
				      "%s: DMA_ALLOC_CONSISTENT(ntxd) failed\n",
				      di->name);
			वापस false;
		पूर्ण
		align = (1 << align_bits);
		di->txd64 = (काष्ठा dma64desc *)
					roundup((अचिन्हित दीर्घ)va, align);
		di->txdalign = (uपूर्णांक) ((s8 *)di->txd64 - (s8 *) va);
		di->txdpa = di->txdpaorig + di->txdalign;
		di->txdalloc = alloced;
	पूर्ण अन्यथा अणु
		va = dma_ringalloc(di, D64RINGALIGN, size, &align_bits,
			&alloced, &di->rxdpaorig);
		अगर (va == शून्य) अणु
			brcms_dbg_dma(di->core,
				      "%s: DMA_ALLOC_CONSISTENT(nrxd) failed\n",
				      di->name);
			वापस false;
		पूर्ण
		align = (1 << align_bits);
		di->rxd64 = (काष्ठा dma64desc *)
					roundup((अचिन्हित दीर्घ)va, align);
		di->rxdalign = (uपूर्णांक) ((s8 *)di->rxd64 - (s8 *) va);
		di->rxdpa = di->rxdpaorig + di->rxdalign;
		di->rxdalloc = alloced;
	पूर्ण

	वापस true;
पूर्ण

अटल bool _dma_alloc(काष्ठा dma_info *di, uपूर्णांक direction)
अणु
	वापस dma64_alloc(di, direction);
पूर्ण

काष्ठा dma_pub *dma_attach(अक्षर *name, काष्ठा brcms_c_info *wlc,
			   uपूर्णांक txregbase, uपूर्णांक rxregbase, uपूर्णांक ntxd, uपूर्णांक nrxd,
			   uपूर्णांक rxbufsize, पूर्णांक rxextheadroom,
			   uपूर्णांक nrxpost, uपूर्णांक rxoffset)
अणु
	काष्ठा si_pub *sih = wlc->hw->sih;
	काष्ठा bcma_device *core = wlc->hw->d11core;
	काष्ठा dma_info *di;
	u8 rev = core->id.rev;
	uपूर्णांक size;
	काष्ठा si_info *sii = container_of(sih, काष्ठा si_info, pub);

	/* allocate निजी info काष्ठाure */
	di = kzalloc(माप(काष्ठा dma_info), GFP_ATOMIC);
	अगर (di == शून्य)
		वापस शून्य;

	di->dma64 =
		((bcma_aपढ़ो32(core, BCMA_IOST) & SISF_DMA64) == SISF_DMA64);

	/* init dma reg info */
	di->core = core;
	di->d64txregbase = txregbase;
	di->d64rxregbase = rxregbase;

	/*
	 * Default flags (which can be changed by the driver calling
	 * dma_ctrlflags beक्रमe enable): For backwards compatibility
	 * both Rx Overflow Continue and Parity are DISABLED.
	 */
	_dma_ctrlflags(di, DMA_CTRL_ROC | DMA_CTRL_PEN, 0);

	brcms_dbg_dma(di->core, "%s: %s flags 0x%x ntxd %d nrxd %d "
		      "rxbufsize %d rxextheadroom %d nrxpost %d rxoffset %d "
		      "txregbase %u rxregbase %u\n", name, "DMA64",
		      di->dma.dmactrlflags, ntxd, nrxd, rxbufsize,
		      rxextheadroom, nrxpost, rxoffset, txregbase, rxregbase);

	/* make a निजी copy of our callers name */
	म_नकलन(di->name, name, MAXNAMEL);
	di->name[MAXNAMEL - 1] = '\0';

	di->dmadev = core->dma_dev;

	/* save tunables */
	di->ntxd = (u16) ntxd;
	di->nrxd = (u16) nrxd;

	/* the actual dma size करोesn't include the extra headroom */
	di->rxextrahdrroom =
	    (rxextheadroom == -1) ? BCMEXTRAHDROOM : rxextheadroom;
	अगर (rxbufsize > BCMEXTRAHDROOM)
		di->rxbufsize = (u16) (rxbufsize - di->rxextrahdrroom);
	अन्यथा
		di->rxbufsize = (u16) rxbufsize;

	di->nrxpost = (u16) nrxpost;
	di->rxoffset = (u8) rxoffset;

	/*
	 * figure out the DMA physical address offset क्रम dd and data
	 *     PCI/PCIE: they map silicon backplace address to zero
	 *     based memory, need offset
	 *     Other bus: use zero SI_BUS BIGENDIAN kludge: use sdram
	 *     swapped region क्रम data buffer, not descriptor
	 */
	di->dकरोffsetlow = 0;
	di->dataoffsetlow = 0;
	/* क्रम pci bus, add offset */
	अगर (sii->icbus->hosttype == BCMA_HOSTTYPE_PCI) अणु
		/* add offset क्रम pcie with DMA64 bus */
		di->dकरोffsetlow = 0;
		di->dकरोffsethigh = SI_PCIE_DMA_H32;
	पूर्ण
	di->dataoffsetlow = di->dकरोffsetlow;
	di->dataoffsethigh = di->dकरोffsethigh;

	/* WAR64450 : DMACtl.Addr ext fields are not supported in SDIOD core. */
	अगर ((core->id.id == BCMA_CORE_SDIO_DEV)
	    && ((rev > 0) && (rev <= 2)))
		di->addrext = false;
	अन्यथा अगर ((core->id.id == BCMA_CORE_I2S) &&
		 ((rev == 0) || (rev == 1)))
		di->addrext = false;
	अन्यथा
		di->addrext = _dma_isaddrext(di);

	/* करोes the descriptor need to be aligned and अगर yes, on 4K/8K or not */
	di->aligndesc_4k = _dma_descriptor_align(di);
	अगर (di->aligndesc_4k) अणु
		di->dmadesc_align = D64RINGALIGN_BITS;
		अगर ((ntxd < D64MAXDD / 2) && (nrxd < D64MAXDD / 2))
			/* क्रम smaller dd table, HW relax alignment reqmnt */
			di->dmadesc_align = D64RINGALIGN_BITS - 1;
	पूर्ण अन्यथा अणु
		di->dmadesc_align = 4;	/* 16 byte alignment */
	पूर्ण

	brcms_dbg_dma(di->core, "DMA descriptor align_needed %d, align %d\n",
		      di->aligndesc_4k, di->dmadesc_align);

	/* allocate tx packet poपूर्णांकer vector */
	अगर (ntxd) अणु
		size = ntxd * माप(व्योम *);
		di->txp = kzalloc(size, GFP_ATOMIC);
		अगर (di->txp == शून्य)
			जाओ fail;
	पूर्ण

	/* allocate rx packet poपूर्णांकer vector */
	अगर (nrxd) अणु
		size = nrxd * माप(व्योम *);
		di->rxp = kzalloc(size, GFP_ATOMIC);
		अगर (di->rxp == शून्य)
			जाओ fail;
	पूर्ण

	/*
	 * allocate transmit descriptor ring, only need ntxd descriptors
	 * but it must be aligned
	 */
	अगर (ntxd) अणु
		अगर (!_dma_alloc(di, DMA_TX))
			जाओ fail;
	पूर्ण

	/*
	 * allocate receive descriptor ring, only need nrxd descriptors
	 * but it must be aligned
	 */
	अगर (nrxd) अणु
		अगर (!_dma_alloc(di, DMA_RX))
			जाओ fail;
	पूर्ण

	अगर ((di->dकरोffsetlow != 0) && !di->addrext) अणु
		अगर (di->txdpa > SI_PCI_DMA_SZ) अणु
			brcms_dbg_dma(di->core,
				      "%s: txdpa 0x%x: addrext not supported\n",
				      di->name, (u32)di->txdpa);
			जाओ fail;
		पूर्ण
		अगर (di->rxdpa > SI_PCI_DMA_SZ) अणु
			brcms_dbg_dma(di->core,
				      "%s: rxdpa 0x%x: addrext not supported\n",
				      di->name, (u32)di->rxdpa);
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Initialize AMPDU session */
	brcms_c_ampdu_reset_session(&di->ampdu_session, wlc);

	brcms_dbg_dma(di->core,
		      "ddoffsetlow 0x%x ddoffsethigh 0x%x dataoffsetlow 0x%x dataoffsethigh 0x%x addrext %d\n",
		      di->dकरोffsetlow, di->dकरोffsethigh,
		      di->dataoffsetlow, di->dataoffsethigh,
		      di->addrext);

	वापस (काष्ठा dma_pub *) di;

 fail:
	dma_detach((काष्ठा dma_pub *)di);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
dma64_dd_upd(काष्ठा dma_info *di, काष्ठा dma64desc *ddring,
	     dma_addr_t pa, uपूर्णांक outidx, u32 *flags, u32 bufcount)
अणु
	u32 ctrl2 = bufcount & D64_CTRL2_BC_MASK;

	/* PCI bus with big(>1G) physical address, use address extension */
	अगर ((di->dataoffsetlow == 0) || !(pa & PCI32ADDR_HIGH)) अणु
		ddring[outidx].addrlow = cpu_to_le32(pa + di->dataoffsetlow);
		ddring[outidx].addrhigh = cpu_to_le32(di->dataoffsethigh);
		ddring[outidx].ctrl1 = cpu_to_le32(*flags);
		ddring[outidx].ctrl2 = cpu_to_le32(ctrl2);
	पूर्ण अन्यथा अणु
		/* address extension क्रम 32-bit PCI */
		u32 ae;

		ae = (pa & PCI32ADDR_HIGH) >> PCI32ADDR_HIGH_SHIFT;
		pa &= ~PCI32ADDR_HIGH;

		ctrl2 |= (ae << D64_CTRL2_AE_SHIFT) & D64_CTRL2_AE;
		ddring[outidx].addrlow = cpu_to_le32(pa + di->dataoffsetlow);
		ddring[outidx].addrhigh = cpu_to_le32(di->dataoffsethigh);
		ddring[outidx].ctrl1 = cpu_to_le32(*flags);
		ddring[outidx].ctrl2 = cpu_to_le32(ctrl2);
	पूर्ण
	अगर (di->dma.dmactrlflags & DMA_CTRL_PEN) अणु
		अगर (dma64_dd_parity(&ddring[outidx]))
			ddring[outidx].ctrl2 =
			     cpu_to_le32(ctrl2 | D64_CTRL2_PARITY);
	पूर्ण
पूर्ण

/* !! may be called with core in reset */
व्योम dma_detach(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	/* मुक्त dma descriptor rings */
	अगर (di->txd64)
		dma_मुक्त_coherent(di->dmadev, di->txdalloc,
				  ((s8 *)di->txd64 - di->txdalign),
				  (di->txdpaorig));
	अगर (di->rxd64)
		dma_मुक्त_coherent(di->dmadev, di->rxdalloc,
				  ((s8 *)di->rxd64 - di->rxdalign),
				  (di->rxdpaorig));

	/* मुक्त packet poपूर्णांकer vectors */
	kमुक्त(di->txp);
	kमुक्त(di->rxp);

	/* मुक्त our निजी info काष्ठाure */
	kमुक्त(di);

पूर्ण

/* initialize descriptor table base address */
अटल व्योम
_dma_ddtable_init(काष्ठा dma_info *di, uपूर्णांक direction, dma_addr_t pa)
अणु
	अगर (!di->aligndesc_4k) अणु
		अगर (direction == DMA_TX)
			di->xmtptrbase = pa;
		अन्यथा
			di->rcvptrbase = pa;
	पूर्ण

	अगर ((di->dकरोffsetlow == 0)
	    || !(pa & PCI32ADDR_HIGH)) अणु
		अगर (direction == DMA_TX) अणु
			bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, addrlow),
				     pa + di->dकरोffsetlow);
			bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, addrhigh),
				     di->dकरोffsethigh);
		पूर्ण अन्यथा अणु
			bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, addrlow),
				     pa + di->dकरोffsetlow);
			bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, addrhigh),
				     di->dकरोffsethigh);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* DMA64 32bits address extension */
		u32 ae;

		/* shअगरt the high bit(s) from pa to ae */
		ae = (pa & PCI32ADDR_HIGH) >> PCI32ADDR_HIGH_SHIFT;
		pa &= ~PCI32ADDR_HIGH;

		अगर (direction == DMA_TX) अणु
			bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, addrlow),
				     pa + di->dकरोffsetlow);
			bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, addrhigh),
				     di->dकरोffsethigh);
			bcma_maskset32(di->core, DMA64TXREGOFFS(di, control),
				       D64_XC_AE, (ae << D64_XC_AE_SHIFT));
		पूर्ण अन्यथा अणु
			bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, addrlow),
				     pa + di->dकरोffsetlow);
			bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, addrhigh),
				     di->dकरोffsethigh);
			bcma_maskset32(di->core, DMA64RXREGOFFS(di, control),
				       D64_RC_AE, (ae << D64_RC_AE_SHIFT));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _dma_rxenable(काष्ठा dma_info *di)
अणु
	uपूर्णांक dmactrlflags = di->dma.dmactrlflags;
	u32 control;

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	control = D64_RC_RE | (bcma_पढ़ो32(di->core,
					   DMA64RXREGOFFS(di, control)) &
			       D64_RC_AE);

	अगर ((dmactrlflags & DMA_CTRL_PEN) == 0)
		control |= D64_RC_PD;

	अगर (dmactrlflags & DMA_CTRL_ROC)
		control |= D64_RC_OC;

	bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, control),
		((di->rxoffset << D64_RC_RO_SHIFT) | control));
पूर्ण

व्योम dma_rxinit(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	अगर (di->nrxd == 0)
		वापस;

	di->rxin = di->rxout = 0;

	/* clear rx descriptor ring */
	स_रखो(di->rxd64, '\0', di->nrxd * माप(काष्ठा dma64desc));

	/* DMA engine with out alignment requirement requires table to be inited
	 * beक्रमe enabling the engine
	 */
	अगर (!di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_RX, di->rxdpa);

	_dma_rxenable(di);

	अगर (di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_RX, di->rxdpa);
पूर्ण

अटल काष्ठा sk_buff *dma64_getnextrxp(काष्ठा dma_info *di, bool क्रमceall)
अणु
	uपूर्णांक i, curr;
	काष्ठा sk_buff *rxp;
	dma_addr_t pa;

	i = di->rxin;

	/* वापस अगर no packets posted */
	अगर (i == di->rxout)
		वापस शून्य;

	curr =
	    B2I(((bcma_पढ़ो32(di->core,
			      DMA64RXREGOFFS(di, status0)) & D64_RS0_CD_MASK) -
		 di->rcvptrbase) & D64_RS0_CD_MASK, काष्ठा dma64desc);

	/* ignore curr अगर क्रमceall */
	अगर (!क्रमceall && (i == curr))
		वापस शून्य;

	/* get the packet poपूर्णांकer that corresponds to the rx descriptor */
	rxp = di->rxp[i];
	di->rxp[i] = शून्य;

	pa = le32_to_cpu(di->rxd64[i].addrlow) - di->dataoffsetlow;

	/* clear this packet from the descriptor ring */
	dma_unmap_single(di->dmadev, pa, di->rxbufsize, DMA_FROM_DEVICE);

	di->rxd64[i].addrlow = cpu_to_le32(0xdeadbeef);
	di->rxd64[i].addrhigh = cpu_to_le32(0xdeadbeef);

	di->rxin = nextrxd(di, i);

	वापस rxp;
पूर्ण

अटल काष्ठा sk_buff *_dma_getnextrxp(काष्ठा dma_info *di, bool क्रमceall)
अणु
	अगर (di->nrxd == 0)
		वापस शून्य;

	वापस dma64_getnextrxp(di, क्रमceall);
पूर्ण

/*
 * !! rx entry routine
 * वापसs the number packages in the next frame, or 0 अगर there are no more
 *   अगर DMA_CTRL_RXMULTI is defined, DMA scattering(multiple buffers) is
 *   supported with pkts chain
 *   otherwise, it's treated as giant pkt and will be tossed.
 *   The DMA scattering starts with normal DMA header, followed by first
 *   buffer data. After it reaches the max size of buffer, the data जारीs
 *   in next DMA descriptor buffer WITHOUT DMA header
 */
पूर्णांक dma_rx(काष्ठा dma_pub *pub, काष्ठा sk_buff_head *skb_list)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	काष्ठा sk_buff_head dma_frames;
	काष्ठा sk_buff *p, *next;
	uपूर्णांक len;
	uपूर्णांक pkt_len;
	पूर्णांक resid = 0;
	पूर्णांक pktcnt = 1;

	skb_queue_head_init(&dma_frames);
 next_frame:
	p = _dma_getnextrxp(di, false);
	अगर (p == शून्य)
		वापस 0;

	len = le16_to_cpu(*(__le16 *) (p->data));
	brcms_dbg_dma(di->core, "%s: dma_rx len %d\n", di->name, len);
	dma_spin_क्रम_len(len, p);

	/* set actual length */
	pkt_len = min((di->rxoffset + len), di->rxbufsize);
	__skb_trim(p, pkt_len);
	skb_queue_tail(&dma_frames, p);
	resid = len - (di->rxbufsize - di->rxoffset);

	/* check क्रम single or multi-buffer rx */
	अगर (resid > 0) अणु
		जबतक ((resid > 0) && (p = _dma_getnextrxp(di, false))) अणु
			pkt_len = min_t(uपूर्णांक, resid, di->rxbufsize);
			__skb_trim(p, pkt_len);
			skb_queue_tail(&dma_frames, p);
			resid -= di->rxbufsize;
			pktcnt++;
		पूर्ण

#अगर_घोषित DEBUG
		अगर (resid > 0) अणु
			uपूर्णांक cur;
			cur =
			    B2I(((bcma_पढ़ो32(di->core,
					      DMA64RXREGOFFS(di, status0)) &
				  D64_RS0_CD_MASK) - di->rcvptrbase) &
				D64_RS0_CD_MASK, काष्ठा dma64desc);
			brcms_dbg_dma(di->core,
				      "rxin %d rxout %d, hw_curr %d\n",
				      di->rxin, di->rxout, cur);
		पूर्ण
#पूर्ण_अगर				/* DEBUG */

		अगर ((di->dma.dmactrlflags & DMA_CTRL_RXMULTI) == 0) अणु
			brcms_dbg_dma(di->core, "%s: bad frame length (%d)\n",
				      di->name, len);
			skb_queue_walk_safe(&dma_frames, p, next) अणु
				skb_unlink(p, &dma_frames);
				brcmu_pkt_buf_मुक्त_skb(p);
			पूर्ण
			di->dma.rxgiants++;
			pktcnt = 1;
			जाओ next_frame;
		पूर्ण
	पूर्ण

	skb_queue_splice_tail(&dma_frames, skb_list);
	वापस pktcnt;
पूर्ण

अटल bool dma64_rxidle(काष्ठा dma_info *di)
अणु
	brcms_dbg_dma(di->core, "%s:\n", di->name);

	अगर (di->nrxd == 0)
		वापस true;

	वापस ((bcma_पढ़ो32(di->core,
			     DMA64RXREGOFFS(di, status0)) & D64_RS0_CD_MASK) ==
		(bcma_पढ़ो32(di->core, DMA64RXREGOFFS(di, ptr)) &
		 D64_RS0_CD_MASK));
पूर्ण

अटल bool dma64_txidle(काष्ठा dma_info *di)
अणु
	अगर (di->ntxd == 0)
		वापस true;

	वापस ((bcma_पढ़ो32(di->core,
			     DMA64TXREGOFFS(di, status0)) & D64_XS0_CD_MASK) ==
		(bcma_पढ़ो32(di->core, DMA64TXREGOFFS(di, ptr)) &
		 D64_XS0_CD_MASK));
पूर्ण

/*
 * post receive buffers
 *  Return false अगर refill failed completely or dma mapping failed. The ring
 *  is empty, which will stall the rx dma and user might want to call rxfill
 *  again asap. This is unlikely to happen on a memory-rich NIC, but often on
 *  memory-स्थिरrained करोngle.
 */
bool dma_rxfill(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	काष्ठा sk_buff *p;
	u16 rxin, rxout;
	u32 flags = 0;
	uपूर्णांक n;
	uपूर्णांक i;
	dma_addr_t pa;
	uपूर्णांक extra_offset = 0;
	bool ring_empty;

	ring_empty = false;

	/*
	 * Determine how many receive buffers we're lacking
	 * from the full complement, allocate, initialize,
	 * and post them, then update the chip rx lastdscr.
	 */

	rxin = di->rxin;
	rxout = di->rxout;

	n = di->nrxpost - nrxdactive(di, rxin, rxout);

	brcms_dbg_dma(di->core, "%s: post %d\n", di->name, n);

	अगर (di->rxbufsize > BCMEXTRAHDROOM)
		extra_offset = di->rxextrahdrroom;

	क्रम (i = 0; i < n; i++) अणु
		/*
		 * the di->rxbufsize करोesn't include the extra headroom,
		 * we need to add it to the size to be allocated
		 */
		p = brcmu_pkt_buf_get_skb(di->rxbufsize + extra_offset);

		अगर (p == शून्य) अणु
			brcms_dbg_dma(di->core, "%s: out of rxbufs\n",
				      di->name);
			अगर (i == 0 && dma64_rxidle(di)) अणु
				brcms_dbg_dma(di->core, "%s: ring is empty !\n",
					      di->name);
				ring_empty = true;
			पूर्ण
			di->dma.rxnobuf++;
			अवरोध;
		पूर्ण
		/* reserve an extra headroom, अगर applicable */
		अगर (extra_offset)
			skb_pull(p, extra_offset);

		/* Do a cached ग_लिखो instead of uncached ग_लिखो since DMA_MAP
		 * will flush the cache.
		 */
		*(u32 *) (p->data) = 0;

		pa = dma_map_single(di->dmadev, p->data, di->rxbufsize,
				    DMA_FROM_DEVICE);
		अगर (dma_mapping_error(di->dmadev, pa)) अणु
			brcmu_pkt_buf_मुक्त_skb(p);
			वापस false;
		पूर्ण

		/* save the मुक्त packet poपूर्णांकer */
		di->rxp[rxout] = p;

		/* reset flags क्रम each descriptor */
		flags = 0;
		अगर (rxout == (di->nrxd - 1))
			flags = D64_CTRL1_EOT;

		dma64_dd_upd(di, di->rxd64, pa, rxout, &flags,
			     di->rxbufsize);
		rxout = nextrxd(di, rxout);
	पूर्ण

	di->rxout = rxout;

	/* update the chip lastdscr poपूर्णांकer */
	bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, ptr),
	      di->rcvptrbase + I2B(rxout, काष्ठा dma64desc));

	वापस ring_empty;
पूर्ण

व्योम dma_rxreclaim(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	काष्ठा sk_buff *p;

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	जबतक ((p = _dma_getnextrxp(di, true)))
		brcmu_pkt_buf_मुक्त_skb(p);
पूर्ण

व्योम dma_counterreset(काष्ठा dma_pub *pub)
अणु
	/* reset all software counters */
	pub->rxgiants = 0;
	pub->rxnobuf = 0;
	pub->txnobuf = 0;
पूर्ण

/* get the address of the var in order to change later */
अचिन्हित दीर्घ dma_getvar(काष्ठा dma_pub *pub, स्थिर अक्षर *name)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);

	अगर (!म_भेद(name, "&txavail"))
		वापस (अचिन्हित दीर्घ)&(di->dma.txavail);
	वापस 0;
पूर्ण

/* 64-bit DMA functions */

व्योम dma_txinit(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	u32 control = D64_XC_XE;

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	अगर (di->ntxd == 0)
		वापस;

	di->txin = di->txout = 0;
	di->dma.txavail = di->ntxd - 1;

	/* clear tx descriptor ring */
	स_रखो(di->txd64, '\0', (di->ntxd * माप(काष्ठा dma64desc)));

	/* DMA engine with out alignment requirement requires table to be inited
	 * beक्रमe enabling the engine
	 */
	अगर (!di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_TX, di->txdpa);

	अगर ((di->dma.dmactrlflags & DMA_CTRL_PEN) == 0)
		control |= D64_XC_PD;
	bcma_set32(di->core, DMA64TXREGOFFS(di, control), control);

	/* DMA engine with alignment requirement requires table to be inited
	 * beक्रमe enabling the engine
	 */
	अगर (di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_TX, di->txdpa);
पूर्ण

व्योम dma_txsuspend(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	अगर (di->ntxd == 0)
		वापस;

	bcma_set32(di->core, DMA64TXREGOFFS(di, control), D64_XC_SE);
पूर्ण

व्योम dma_txresume(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	अगर (di->ntxd == 0)
		वापस;

	bcma_mask32(di->core, DMA64TXREGOFFS(di, control), ~D64_XC_SE);
पूर्ण

bool dma_txsuspended(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);

	वापस (di->ntxd == 0) ||
	       ((bcma_पढ़ो32(di->core,
			     DMA64TXREGOFFS(di, control)) & D64_XC_SE) ==
		D64_XC_SE);
पूर्ण

व्योम dma_txreclaim(काष्ठा dma_pub *pub, क्रमागत txd_range range)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	काष्ठा sk_buff *p;

	brcms_dbg_dma(di->core, "%s: %s\n",
		      di->name,
		      range == DMA_RANGE_ALL ? "all" :
		      range == DMA_RANGE_TRANSMITTED ? "transmitted" :
		      "transferred");

	अगर (di->txin == di->txout)
		वापस;

	जबतक ((p = dma_getnexttxp(pub, range))) अणु
		/* For unframed data, we करोn't have any packets to मुक्त */
		अगर (!(di->dma.dmactrlflags & DMA_CTRL_UNFRAMED))
			brcmu_pkt_buf_मुक्त_skb(p);
	पूर्ण
पूर्ण

bool dma_txreset(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	u32 status;

	अगर (di->ntxd == 0)
		वापस true;

	/* suspend tx DMA first */
	bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, control), D64_XC_SE);
	SPINWAIT(((status =
		   (bcma_पढ़ो32(di->core, DMA64TXREGOFFS(di, status0)) &
		    D64_XS0_XS_MASK)) != D64_XS0_XS_DISABLED) &&
		  (status != D64_XS0_XS_IDLE) && (status != D64_XS0_XS_STOPPED),
		 10000);

	bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, control), 0);
	SPINWAIT(((status =
		   (bcma_पढ़ो32(di->core, DMA64TXREGOFFS(di, status0)) &
		    D64_XS0_XS_MASK)) != D64_XS0_XS_DISABLED), 10000);

	/* रुको क्रम the last transaction to complete */
	udelay(300);

	वापस status == D64_XS0_XS_DISABLED;
पूर्ण

bool dma_rxreset(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	u32 status;

	अगर (di->nrxd == 0)
		वापस true;

	bcma_ग_लिखो32(di->core, DMA64RXREGOFFS(di, control), 0);
	SPINWAIT(((status =
		   (bcma_पढ़ो32(di->core, DMA64RXREGOFFS(di, status0)) &
		    D64_RS0_RS_MASK)) != D64_RS0_RS_DISABLED), 10000);

	वापस status == D64_RS0_RS_DISABLED;
पूर्ण

अटल व्योम dma_txenq(काष्ठा dma_info *di, काष्ठा sk_buff *p)
अणु
	अचिन्हित अक्षर *data;
	uपूर्णांक len;
	u16 txout;
	u32 flags = 0;
	dma_addr_t pa;

	txout = di->txout;

	अगर (WARN_ON(nexttxd(di, txout) == di->txin))
		वापस;

	/*
	 * obtain and initialize transmit descriptor entry.
	 */
	data = p->data;
	len = p->len;

	/* get physical address of buffer start */
	pa = dma_map_single(di->dmadev, data, len, DMA_TO_DEVICE);
	/* अगर mapping failed, मुक्त skb */
	अगर (dma_mapping_error(di->dmadev, pa)) अणु
		brcmu_pkt_buf_मुक्त_skb(p);
		वापस;
	पूर्ण
	/* With a DMA segment list, Descriptor table is filled
	 * using the segment list instead of looping over
	 * buffers in multi-chain DMA. Thereक्रमe, खातापूर्ण क्रम SGLIST
	 * is when end of segment list is reached.
	 */
	flags = D64_CTRL1_SOF | D64_CTRL1_IOC | D64_CTRL1_खातापूर्ण;
	अगर (txout == (di->ntxd - 1))
		flags |= D64_CTRL1_EOT;

	dma64_dd_upd(di, di->txd64, pa, txout, &flags, len);

	txout = nexttxd(di, txout);

	/* save the packet */
	di->txp[prevtxd(di, txout)] = p;

	/* bump the tx descriptor index */
	di->txout = txout;
पूर्ण

अटल व्योम ampdu_finalize(काष्ठा dma_info *di)
अणु
	काष्ठा brcms_ampdu_session *session = &di->ampdu_session;
	काष्ठा sk_buff *p;

	trace_brcms_ampdu_session(&session->wlc->hw->d11core->dev,
				  session->max_ampdu_len,
				  session->max_ampdu_frames,
				  session->ampdu_len,
				  skb_queue_len(&session->skb_list),
				  session->dma_len);

	अगर (WARN_ON(skb_queue_empty(&session->skb_list)))
		वापस;

	brcms_c_ampdu_finalize(session);

	जबतक (!skb_queue_empty(&session->skb_list)) अणु
		p = skb_dequeue(&session->skb_list);
		dma_txenq(di, p);
	पूर्ण

	bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, ptr),
		     di->xmtptrbase + I2B(di->txout, काष्ठा dma64desc));
	brcms_c_ampdu_reset_session(session, session->wlc);
पूर्ण

अटल व्योम prep_ampdu_frame(काष्ठा dma_info *di, काष्ठा sk_buff *p)
अणु
	काष्ठा brcms_ampdu_session *session = &di->ampdu_session;
	पूर्णांक ret;

	ret = brcms_c_ampdu_add_frame(session, p);
	अगर (ret == -ENOSPC) अणु
		/*
		 * AMPDU cannot accomodate this frame. Close out the in-
		 * progress AMPDU session and start a new one.
		 */
		ampdu_finalize(di);
		ret = brcms_c_ampdu_add_frame(session, p);
	पूर्ण

	WARN_ON(ret);
पूर्ण

/* Update count of available tx descriptors based on current DMA state */
अटल व्योम dma_update_txavail(काष्ठा dma_info *di)
अणु
	/*
	 * Available space is number of descriptors less the number of
	 * active descriptors and the number of queued AMPDU frames.
	 */
	di->dma.txavail = di->ntxd - ntxdactive(di, di->txin, di->txout) -
			  skb_queue_len(&di->ampdu_session.skb_list) - 1;
पूर्ण

/*
 * !! tx entry routine
 * WARNING: call must check the वापस value क्रम error.
 *   the error(toss frames) could be fatal and cause many subsequent hard
 *   to debug problems
 */
पूर्णांक dma_txfast(काष्ठा brcms_c_info *wlc, काष्ठा dma_pub *pub,
	       काष्ठा sk_buff *p)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	काष्ठा brcms_ampdu_session *session = &di->ampdu_session;
	काष्ठा ieee80211_tx_info *tx_info;
	bool is_ampdu;

	/* no use to transmit a zero length packet */
	अगर (p->len == 0)
		वापस 0;

	/* वापस nonzero अगर out of tx descriptors */
	अगर (di->dma.txavail == 0 || nexttxd(di, di->txout) == di->txin)
		जाओ outoftxd;

	tx_info = IEEE80211_SKB_CB(p);
	is_ampdu = tx_info->flags & IEEE80211_TX_CTL_AMPDU;
	अगर (is_ampdu)
		prep_ampdu_frame(di, p);
	अन्यथा
		dma_txenq(di, p);

	/* tx flow control */
	dma_update_txavail(di);

	/* kick the chip */
	अगर (is_ampdu) अणु
		/*
		 * Start sending data अगर we've got a full AMPDU, there's
		 * no more space in the DMA ring, or the ring isn't
		 * currently transmitting.
		 */
		अगर (skb_queue_len(&session->skb_list) == session->max_ampdu_frames ||
		    di->dma.txavail == 0 || dma64_txidle(di))
			ampdu_finalize(di);
	पूर्ण अन्यथा अणु
		bcma_ग_लिखो32(di->core, DMA64TXREGOFFS(di, ptr),
			     di->xmtptrbase + I2B(di->txout, काष्ठा dma64desc));
	पूर्ण

	वापस 0;

 outoftxd:
	brcms_dbg_dma(di->core, "%s: out of txds !!!\n", di->name);
	brcmu_pkt_buf_मुक्त_skb(p);
	di->dma.txavail = 0;
	di->dma.txnobuf++;
	वापस -ENOSPC;
पूर्ण

व्योम dma_txflush(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	काष्ठा brcms_ampdu_session *session = &di->ampdu_session;

	अगर (!skb_queue_empty(&session->skb_list))
		ampdu_finalize(di);
पूर्ण

पूर्णांक dma_txpending(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	वापस ntxdactive(di, di->txin, di->txout);
पूर्ण

/*
 * If we have an active AMPDU session and are not transmitting,
 * this function will क्रमce tx to start.
 */
व्योम dma_kick_tx(काष्ठा dma_pub *pub)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	काष्ठा brcms_ampdu_session *session = &di->ampdu_session;

	अगर (!skb_queue_empty(&session->skb_list) && dma64_txidle(di))
		ampdu_finalize(di);
पूर्ण

/*
 * Reclaim next completed txd (txds अगर using chained buffers) in the range
 * specअगरied and वापस associated packet.
 * If range is DMA_RANGE_TRANSMITTED, reclaim descriptors that have be
 * transmitted as noted by the hardware "CurrDescr" poपूर्णांकer.
 * If range is DMA_RANGE_TRANSFERED, reclaim descriptors that have be
 * transferred by the DMA as noted by the hardware "ActiveDescr" poपूर्णांकer.
 * If range is DMA_RANGE_ALL, reclaim all txd(s) posted to the ring and
 * वापस associated packet regardless of the value of hardware poपूर्णांकers.
 */
काष्ठा sk_buff *dma_getnexttxp(काष्ठा dma_pub *pub, क्रमागत txd_range range)
अणु
	काष्ठा dma_info *di = container_of(pub, काष्ठा dma_info, dma);
	u16 start, end, i;
	u16 active_desc;
	काष्ठा sk_buff *txp;

	brcms_dbg_dma(di->core, "%s: %s\n",
		      di->name,
		      range == DMA_RANGE_ALL ? "all" :
		      range == DMA_RANGE_TRANSMITTED ? "transmitted" :
		      "transferred");

	अगर (di->ntxd == 0)
		वापस शून्य;

	txp = शून्य;

	start = di->txin;
	अगर (range == DMA_RANGE_ALL)
		end = di->txout;
	अन्यथा अणु
		end = (u16) (B2I(((bcma_पढ़ो32(di->core,
					       DMA64TXREGOFFS(di, status0)) &
				   D64_XS0_CD_MASK) - di->xmtptrbase) &
				 D64_XS0_CD_MASK, काष्ठा dma64desc));

		अगर (range == DMA_RANGE_TRANSFERED) अणु
			active_desc =
				(u16)(bcma_पढ़ो32(di->core,
						  DMA64TXREGOFFS(di, status1)) &
				      D64_XS1_AD_MASK);
			active_desc =
			    (active_desc - di->xmtptrbase) & D64_XS0_CD_MASK;
			active_desc = B2I(active_desc, काष्ठा dma64desc);
			अगर (end != active_desc)
				end = prevtxd(di, active_desc);
		पूर्ण
	पूर्ण

	अगर ((start == 0) && (end > di->txout))
		जाओ bogus;

	क्रम (i = start; i != end && !txp; i = nexttxd(di, i)) अणु
		dma_addr_t pa;
		uपूर्णांक size;

		pa = le32_to_cpu(di->txd64[i].addrlow) - di->dataoffsetlow;

		size =
		    (le32_to_cpu(di->txd64[i].ctrl2) &
		     D64_CTRL2_BC_MASK);

		di->txd64[i].addrlow = cpu_to_le32(0xdeadbeef);
		di->txd64[i].addrhigh = cpu_to_le32(0xdeadbeef);

		txp = di->txp[i];
		di->txp[i] = शून्य;

		dma_unmap_single(di->dmadev, pa, size, DMA_TO_DEVICE);
	पूर्ण

	di->txin = i;

	/* tx flow control */
	dma_update_txavail(di);

	वापस txp;

 bogus:
	brcms_dbg_dma(di->core, "bogus curr: start %d end %d txout %d\n",
		      start, end, di->txout);
	वापस शून्य;
पूर्ण

/*
 * Mac80211 initiated actions someबार require packets in the DMA queue to be
 * modअगरied. The modअगरied portion of the packet is not under control of the DMA
 * engine. This function calls a caller-supplied function क्रम each packet in
 * the caller specअगरied dma chain.
 */
व्योम dma_walk_packets(काष्ठा dma_pub *dmah, व्योम (*callback_fnc)
		      (व्योम *pkt, व्योम *arg_a), व्योम *arg_a)
अणु
	काष्ठा dma_info *di = container_of(dmah, काष्ठा dma_info, dma);
	uपूर्णांक i =   di->txin;
	uपूर्णांक end = di->txout;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *tx_info;

	जबतक (i != end) अणु
		skb = di->txp[i];
		अगर (skb != शून्य) अणु
			tx_info = (काष्ठा ieee80211_tx_info *)skb->cb;
			(callback_fnc)(tx_info, arg_a);
		पूर्ण
		i = nexttxd(di, i);
	पूर्ण
पूर्ण
