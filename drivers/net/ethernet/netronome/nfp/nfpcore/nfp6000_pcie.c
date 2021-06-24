<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp6000_pcie.c
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 *
 * Multiplexes the NFP BARs between NFP पूर्णांकernal resources and
 * implements the PCIe specअगरic पूर्णांकerface क्रम generic CPP bus access.
 *
 * The BARs are managed with refcounts and are allocated/acquired
 * using target, token and offset/size matching.  The generic CPP bus
 * असलtraction builds upon this BAR पूर्णांकerface.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sort.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>

#समावेश "nfp_cpp.h"

#समावेश "nfp6000/nfp6000.h"

#समावेश "nfp6000_pcie.h"

#घोषणा NFP_PCIE_BAR(_pf)	(0x30000 + ((_pf) & 7) * 0xc0)
#घोषणा NFP_PCIE_BAR_EXPLICIT_BAR0(_x, _y) \
	(0x00000080 + (0x40 * ((_x) & 0x3)) + (0x10 * ((_y) & 0x3)))
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR0_SignalType(_x)     (((_x) & 0x3) << 30)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR0_SignalType_of(_x)  (((_x) >> 30) & 0x3)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR0_Token(_x)          (((_x) & 0x3) << 28)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR0_Token_of(_x)       (((_x) >> 28) & 0x3)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR0_Address(_x)        (((_x) & 0xffffff) << 0)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR0_Address_of(_x)     (((_x) >> 0) & 0xffffff)
#घोषणा NFP_PCIE_BAR_EXPLICIT_BAR1(_x, _y) \
	(0x00000084 + (0x40 * ((_x) & 0x3)) + (0x10 * ((_y) & 0x3)))
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR1_SignalRef(_x)      (((_x) & 0x7f) << 24)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR1_SignalRef_of(_x)   (((_x) >> 24) & 0x7f)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR1_DataMaster(_x)     (((_x) & 0x3ff) << 14)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR1_DataMaster_of(_x)  (((_x) >> 14) & 0x3ff)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR1_DataRef(_x)        (((_x) & 0x3fff) << 0)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR1_DataRef_of(_x)     (((_x) >> 0) & 0x3fff)
#घोषणा NFP_PCIE_BAR_EXPLICIT_BAR2(_x, _y) \
	(0x00000088 + (0x40 * ((_x) & 0x3)) + (0x10 * ((_y) & 0x3)))
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_Target(_x)         (((_x) & 0xf) << 28)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_Target_of(_x)      (((_x) >> 28) & 0xf)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_Action(_x)         (((_x) & 0x1f) << 23)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_Action_of(_x)      (((_x) >> 23) & 0x1f)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_Length(_x)         (((_x) & 0x1f) << 18)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_Length_of(_x)      (((_x) >> 18) & 0x1f)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_ByteMask(_x)       (((_x) & 0xff) << 10)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_ByteMask_of(_x)    (((_x) >> 10) & 0xff)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_SignalMaster(_x)   (((_x) & 0x3ff) << 0)
#घोषणा   NFP_PCIE_BAR_EXPLICIT_BAR2_SignalMaster_of(_x) (((_x) >> 0) & 0x3ff)

#घोषणा   NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress(_x)  (((_x) & 0x1f) << 16)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress_of(_x) (((_x) >> 16) & 0x1f)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_BaseAddress(_x)         (((_x) & 0xffff) << 0)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_BaseAddress_of(_x)      (((_x) >> 0) & 0xffff)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_LengthSelect(_x)        (((_x) & 0x3) << 27)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_LengthSelect_of(_x)     (((_x) >> 27) & 0x3)
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT    0
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_LengthSelect_64BIT    1
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_LengthSelect_0BYTE    3
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_MapType(_x)             (((_x) & 0x7) << 29)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_MapType_of(_x)          (((_x) >> 29) & 0x7)
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_FIXED         0
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_BULK          1
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_TARGET        2
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_GENERAL       3
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT0     4
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT1     5
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT2     6
#घोषणा     NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT3     7
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress(_x)  (((_x) & 0xf) << 23)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress_of(_x) (((_x) >> 23) & 0xf)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress(_x)   (((_x) & 0x3) << 21)
#घोषणा   NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress_of(_x) (((_x) >> 21) & 0x3)
#घोषणा NFP_PCIE_EM                                     0x020000
#घोषणा NFP_PCIE_SRAM                                   0x000000

/* Minimal size of the PCIe cfg memory we depend on being mapped,
 * queue controller and DMA controller करोn't have to be covered.
 */
#घोषणा NFP_PCI_MIN_MAP_SIZE				0x080000

#घोषणा NFP_PCIE_P2C_FIXED_SIZE(bar)               (1 << (bar)->bitsize)
#घोषणा NFP_PCIE_P2C_BULK_SIZE(bar)                (1 << (bar)->bitsize)
#घोषणा NFP_PCIE_P2C_GENERAL_TARGET_OFFSET(bar, x) ((x) << ((bar)->bitsize - 2))
#घोषणा NFP_PCIE_P2C_GENERAL_TOKEN_OFFSET(bar, x) ((x) << ((bar)->bitsize - 4))
#घोषणा NFP_PCIE_P2C_GENERAL_SIZE(bar)             (1 << ((bar)->bitsize - 4))

#घोषणा NFP_PCIE_CFG_BAR_PCIETOCPPEXPANSIONBAR(bar, slot) \
	(0x400 + ((bar) * 8 + (slot)) * 4)

#घोषणा NFP_PCIE_CPP_BAR_PCIETOCPPEXPANSIONBAR(bar, slot) \
	(((bar) * 8 + (slot)) * 4)

/* The number of explicit BARs to reserve.
 * Minimum is 0, maximum is 4 on the NFP6000.
 * The NFP3800 can have only one per PF.
 */
#घोषणा NFP_PCIE_EXPLICIT_BARS		2

काष्ठा nfp6000_pcie;
काष्ठा nfp6000_area_priv;

/**
 * काष्ठा nfp_bar - describes BAR configuration and usage
 * @nfp:	backlink to owner
 * @barcfg:	cached contents of BAR config CSR
 * @base:	the BAR's base CPP offset
 * @mask:       mask क्रम the BAR aperture (पढ़ो only)
 * @bitsize:	bitsize of BAR aperture (पढ़ो only)
 * @index:	index of the BAR
 * @refcnt:	number of current users
 * @iomem:	mapped IO memory
 * @resource:	iomem resource winकरोw
 */
काष्ठा nfp_bar अणु
	काष्ठा nfp6000_pcie *nfp;
	u32 barcfg;
	u64 base;          /* CPP address base */
	u64 mask;          /* Bit mask of the bar */
	u32 bitsize;       /* Bit size of the bar */
	पूर्णांक index;
	atomic_t refcnt;

	व्योम __iomem *iomem;
	काष्ठा resource *resource;
पूर्ण;

#घोषणा NFP_PCI_BAR_MAX    (PCI_64BIT_BAR_COUNT * 8)

काष्ठा nfp6000_pcie अणु
	काष्ठा pci_dev *pdev;
	काष्ठा device *dev;

	/* PCI BAR management */
	spinlock_t bar_lock;		/* Protect the PCI2CPP BAR cache */
	पूर्णांक bars;
	काष्ठा nfp_bar bar[NFP_PCI_BAR_MAX];
	रुको_queue_head_t bar_रुकोers;

	/* Reserved BAR access */
	काष्ठा अणु
		व्योम __iomem *csr;
		व्योम __iomem *em;
		व्योम __iomem *expl[4];
	पूर्ण iomem;

	/* Explicit IO access */
	काष्ठा अणु
		काष्ठा mutex mutex; /* Lock access to this explicit group */
		u8 master_id;
		u8 संकेत_ref;
		व्योम __iomem *data;
		काष्ठा अणु
			व्योम __iomem *addr;
			पूर्णांक bitsize;
			पूर्णांक मुक्त[4];
		पूर्ण group[4];
	पूर्ण expl;
पूर्ण;

अटल u32 nfp_bar_maptype(काष्ठा nfp_bar *bar)
अणु
	वापस NFP_PCIE_BAR_PCIE2CPP_MapType_of(bar->barcfg);
पूर्ण

अटल resource_माप_प्रकार nfp_bar_resource_len(काष्ठा nfp_bar *bar)
अणु
	वापस pci_resource_len(bar->nfp->pdev, (bar->index / 8) * 2) / 8;
पूर्ण

अटल resource_माप_प्रकार nfp_bar_resource_start(काष्ठा nfp_bar *bar)
अणु
	वापस pci_resource_start(bar->nfp->pdev, (bar->index / 8) * 2)
		+ nfp_bar_resource_len(bar) * (bar->index & 7);
पूर्ण

#घोषणा TARGET_WIDTH_32    4
#घोषणा TARGET_WIDTH_64    8

अटल पूर्णांक
compute_bar(स्थिर काष्ठा nfp6000_pcie *nfp, स्थिर काष्ठा nfp_bar *bar,
	    u32 *bar_config, u64 *bar_base,
	    पूर्णांक tgt, पूर्णांक act, पूर्णांक tok, u64 offset, माप_प्रकार size, पूर्णांक width)
अणु
	पूर्णांक bitsize;
	u32 newcfg;

	अगर (tgt >= NFP_CPP_NUM_TARGETS)
		वापस -EINVAL;

	चयन (width) अणु
	हाल 8:
		newcfg = NFP_PCIE_BAR_PCIE2CPP_LengthSelect(
			NFP_PCIE_BAR_PCIE2CPP_LengthSelect_64BIT);
		अवरोध;
	हाल 4:
		newcfg = NFP_PCIE_BAR_PCIE2CPP_LengthSelect(
			NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT);
		अवरोध;
	हाल 0:
		newcfg = NFP_PCIE_BAR_PCIE2CPP_LengthSelect(
			NFP_PCIE_BAR_PCIE2CPP_LengthSelect_0BYTE);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (act != NFP_CPP_ACTION_RW && act != 0) अणु
		/* Fixed CPP mapping with specअगरic action */
		u64 mask = ~(NFP_PCIE_P2C_FIXED_SIZE(bar) - 1);

		newcfg |= NFP_PCIE_BAR_PCIE2CPP_MapType(
			  NFP_PCIE_BAR_PCIE2CPP_MapType_FIXED);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress(tgt);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress(act);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress(tok);

		अगर ((offset & mask) != ((offset + size - 1) & mask))
			वापस -EINVAL;
		offset &= mask;

		bitsize = 40 - 16;
	पूर्ण अन्यथा अणु
		u64 mask = ~(NFP_PCIE_P2C_BULK_SIZE(bar) - 1);

		/* Bulk mapping */
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_BULK);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress(tgt);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress(tok);

		अगर ((offset & mask) != ((offset + size - 1) & mask))
			वापस -EINVAL;

		offset &= mask;

		bitsize = 40 - 21;
	पूर्ण

	अगर (bar->bitsize < bitsize)
		वापस -EINVAL;

	newcfg |= offset >> bitsize;

	अगर (bar_base)
		*bar_base = offset;

	अगर (bar_config)
		*bar_config = newcfg;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp6000_bar_ग_लिखो(काष्ठा nfp6000_pcie *nfp, काष्ठा nfp_bar *bar, u32 newcfg)
अणु
	पूर्णांक base, slot;
	पूर्णांक xbar;

	base = bar->index >> 3;
	slot = bar->index & 7;

	अगर (nfp->iomem.csr) अणु
		xbar = NFP_PCIE_CPP_BAR_PCIETOCPPEXPANSIONBAR(base, slot);
		ग_लिखोl(newcfg, nfp->iomem.csr + xbar);
		/* Readback to ensure BAR is flushed */
		पढ़ोl(nfp->iomem.csr + xbar);
	पूर्ण अन्यथा अणु
		xbar = NFP_PCIE_CFG_BAR_PCIETOCPPEXPANSIONBAR(base, slot);
		pci_ग_लिखो_config_dword(nfp->pdev, xbar, newcfg);
	पूर्ण

	bar->barcfg = newcfg;

	वापस 0;
पूर्ण

अटल पूर्णांक
reconfigure_bar(काष्ठा nfp6000_pcie *nfp, काष्ठा nfp_bar *bar,
		पूर्णांक tgt, पूर्णांक act, पूर्णांक tok, u64 offset, माप_प्रकार size, पूर्णांक width)
अणु
	u64 newbase;
	u32 newcfg;
	पूर्णांक err;

	err = compute_bar(nfp, bar, &newcfg, &newbase,
			  tgt, act, tok, offset, size, width);
	अगर (err)
		वापस err;

	bar->base = newbase;

	वापस nfp6000_bar_ग_लिखो(nfp, bar, newcfg);
पूर्ण

/* Check अगर BAR can be used with the given parameters. */
अटल पूर्णांक matching_bar(काष्ठा nfp_bar *bar, u32 tgt, u32 act, u32 tok,
			u64 offset, माप_प्रकार size, पूर्णांक width)
अणु
	पूर्णांक bartgt, baract, bartok;
	पूर्णांक barwidth;
	u32 maptype;

	maptype = NFP_PCIE_BAR_PCIE2CPP_MapType_of(bar->barcfg);
	bartgt = NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress_of(bar->barcfg);
	bartok = NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress_of(bar->barcfg);
	baract = NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress_of(bar->barcfg);

	barwidth = NFP_PCIE_BAR_PCIE2CPP_LengthSelect_of(bar->barcfg);
	चयन (barwidth) अणु
	हाल NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT:
		barwidth = 4;
		अवरोध;
	हाल NFP_PCIE_BAR_PCIE2CPP_LengthSelect_64BIT:
		barwidth = 8;
		अवरोध;
	हाल NFP_PCIE_BAR_PCIE2CPP_LengthSelect_0BYTE:
		barwidth = 0;
		अवरोध;
	शेष:
		barwidth = -1;
		अवरोध;
	पूर्ण

	चयन (maptype) अणु
	हाल NFP_PCIE_BAR_PCIE2CPP_MapType_TARGET:
		bartok = -1;
		fallthrough;
	हाल NFP_PCIE_BAR_PCIE2CPP_MapType_BULK:
		baract = NFP_CPP_ACTION_RW;
		अगर (act == 0)
			act = NFP_CPP_ACTION_RW;
		fallthrough;
	हाल NFP_PCIE_BAR_PCIE2CPP_MapType_FIXED:
		अवरोध;
	शेष:
		/* We करोn't match explicit bars through the area पूर्णांकerface */
		वापस 0;
	पूर्ण

	/* Make sure to match up the width */
	अगर (barwidth != width)
		वापस 0;

	अगर ((bartgt < 0 || bartgt == tgt) &&
	    (bartok < 0 || bartok == tok) &&
	    (baract == act) &&
	    bar->base <= offset &&
	    (bar->base + (1 << bar->bitsize)) >= (offset + size))
		वापस 1;

	/* No match */
	वापस 0;
पूर्ण

अटल पूर्णांक
find_matching_bar(काष्ठा nfp6000_pcie *nfp,
		  u32 tgt, u32 act, u32 tok, u64 offset, माप_प्रकार size, पूर्णांक width)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < nfp->bars; n++) अणु
		काष्ठा nfp_bar *bar = &nfp->bar[n];

		अगर (matching_bar(bar, tgt, act, tok, offset, size, width))
			वापस n;
	पूर्ण

	वापस -1;
पूर्ण

/* Return EAGAIN अगर no resource is available */
अटल पूर्णांक
find_unused_bar_noblock(स्थिर काष्ठा nfp6000_pcie *nfp,
			पूर्णांक tgt, पूर्णांक act, पूर्णांक tok,
			u64 offset, माप_प्रकार size, पूर्णांक width)
अणु
	पूर्णांक n, busy = 0;

	क्रम (n = 0; n < nfp->bars; n++) अणु
		स्थिर काष्ठा nfp_bar *bar = &nfp->bar[n];
		पूर्णांक err;

		अगर (!bar->bitsize)
			जारी;

		/* Just check to see अगर we can make it fit... */
		err = compute_bar(nfp, bar, शून्य, शून्य,
				  tgt, act, tok, offset, size, width);
		अगर (err)
			जारी;

		अगर (!atomic_पढ़ो(&bar->refcnt))
			वापस n;

		busy++;
	पूर्ण

	अगर (WARN(!busy, "No suitable BAR found for request tgt:0x%x act:0x%x tok:0x%x off:0x%llx size:%zd width:%d\n",
		 tgt, act, tok, offset, size, width))
		वापस -EINVAL;

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक
find_unused_bar_and_lock(काष्ठा nfp6000_pcie *nfp,
			 पूर्णांक tgt, पूर्णांक act, पूर्णांक tok,
			 u64 offset, माप_प्रकार size, पूर्णांक width)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक n;

	spin_lock_irqsave(&nfp->bar_lock, flags);

	n = find_unused_bar_noblock(nfp, tgt, act, tok, offset, size, width);
	अगर (n < 0)
		spin_unlock_irqrestore(&nfp->bar_lock, flags);
	अन्यथा
		__release(&nfp->bar_lock);

	वापस n;
पूर्ण

अटल व्योम nfp_bar_get(काष्ठा nfp6000_pcie *nfp, काष्ठा nfp_bar *bar)
अणु
	atomic_inc(&bar->refcnt);
पूर्ण

अटल व्योम nfp_bar_put(काष्ठा nfp6000_pcie *nfp, काष्ठा nfp_bar *bar)
अणु
	अगर (atomic_dec_and_test(&bar->refcnt))
		wake_up_पूर्णांकerruptible(&nfp->bar_रुकोers);
पूर्ण

अटल पूर्णांक
nfp_रुको_क्रम_bar(काष्ठा nfp6000_pcie *nfp, पूर्णांक *barnum,
		 u32 tgt, u32 act, u32 tok, u64 offset, माप_प्रकार size, पूर्णांक width)
अणु
	वापस रुको_event_पूर्णांकerruptible(nfp->bar_रुकोers,
		(*barnum = find_unused_bar_and_lock(nfp, tgt, act, tok,
						    offset, size, width))
					!= -EAGAIN);
पूर्ण

अटल पूर्णांक
nfp_alloc_bar(काष्ठा nfp6000_pcie *nfp,
	      u32 tgt, u32 act, u32 tok,
	      u64 offset, माप_प्रकार size, पूर्णांक width, पूर्णांक nonblocking)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक barnum, retval;

	अगर (size > (1 << 24))
		वापस -EINVAL;

	spin_lock_irqsave(&nfp->bar_lock, irqflags);
	barnum = find_matching_bar(nfp, tgt, act, tok, offset, size, width);
	अगर (barnum >= 0) अणु
		/* Found a perfect match. */
		nfp_bar_get(nfp, &nfp->bar[barnum]);
		spin_unlock_irqrestore(&nfp->bar_lock, irqflags);
		वापस barnum;
	पूर्ण

	barnum = find_unused_bar_noblock(nfp, tgt, act, tok,
					 offset, size, width);
	अगर (barnum < 0) अणु
		अगर (nonblocking)
			जाओ err_nobar;

		/* Wait until a BAR becomes available.  The
		 * find_unused_bar function will reclaim the bar_lock
		 * अगर a मुक्त BAR is found.
		 */
		spin_unlock_irqrestore(&nfp->bar_lock, irqflags);
		retval = nfp_रुको_क्रम_bar(nfp, &barnum, tgt, act, tok,
					  offset, size, width);
		अगर (retval)
			वापस retval;
		__acquire(&nfp->bar_lock);
	पूर्ण

	nfp_bar_get(nfp, &nfp->bar[barnum]);
	retval = reconfigure_bar(nfp, &nfp->bar[barnum],
				 tgt, act, tok, offset, size, width);
	अगर (retval < 0) अणु
		nfp_bar_put(nfp, &nfp->bar[barnum]);
		barnum = retval;
	पूर्ण

err_nobar:
	spin_unlock_irqrestore(&nfp->bar_lock, irqflags);
	वापस barnum;
पूर्ण

अटल व्योम disable_bars(काष्ठा nfp6000_pcie *nfp);

अटल पूर्णांक bar_cmp(स्थिर व्योम *aptr, स्थिर व्योम *bptr)
अणु
	स्थिर काष्ठा nfp_bar *a = aptr, *b = bptr;

	अगर (a->bitsize == b->bitsize)
		वापस a->index - b->index;
	अन्यथा
		वापस a->bitsize - b->bitsize;
पूर्ण

/* Map all PCI bars and fetch the actual BAR configurations from the
 * board.  We assume that the BAR with the PCIe config block is
 * alपढ़ोy mapped.
 *
 * BAR0.0: Reserved क्रम General Mapping (क्रम MSI-X access to PCIe SRAM)
 * BAR0.1: Reserved क्रम XPB access (क्रम MSI-X access to PCIe PBA)
 * BAR0.2: --
 * BAR0.3: --
 * BAR0.4: Reserved क्रम Explicit 0.0-0.3 access
 * BAR0.5: Reserved क्रम Explicit 1.0-1.3 access
 * BAR0.6: Reserved क्रम Explicit 2.0-2.3 access
 * BAR0.7: Reserved क्रम Explicit 3.0-3.3 access
 *
 * BAR1.0-BAR1.7: --
 * BAR2.0-BAR2.7: --
 */
अटल पूर्णांक enable_bars(काष्ठा nfp6000_pcie *nfp, u16 पूर्णांकerface)
अणु
	स्थिर u32 barcfg_msix_general =
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_GENERAL) |
		NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT;
	स्थिर u32 barcfg_msix_xpb =
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_BULK) |
		NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT |
		NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress(
			NFP_CPP_TARGET_ISLAND_XPB);
	स्थिर u32 barcfg_explicit[4] = अणु
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT0),
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT1),
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT2),
		NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_EXPLICIT3),
	पूर्ण;
	अक्षर status_msg[196] = अणुपूर्ण;
	पूर्णांक i, err, bars_मुक्त;
	काष्ठा nfp_bar *bar;
	पूर्णांक expl_groups;
	अक्षर *msg, *end;

	msg = status_msg +
		snम_लिखो(status_msg, माप(status_msg) - 1, "RESERVED BARs: ");
	end = status_msg + माप(status_msg) - 1;

	bar = &nfp->bar[0];
	क्रम (i = 0; i < ARRAY_SIZE(nfp->bar); i++, bar++) अणु
		काष्ठा resource *res;

		res = &nfp->pdev->resource[(i >> 3) * 2];

		/* Skip over BARs that are not IORESOURCE_MEM */
		अगर (!(resource_type(res) & IORESOURCE_MEM)) अणु
			bar--;
			जारी;
		पूर्ण

		bar->resource = res;
		bar->barcfg = 0;

		bar->nfp = nfp;
		bar->index = i;
		bar->mask = nfp_bar_resource_len(bar) - 1;
		bar->bitsize = fls(bar->mask);
		bar->base = 0;
		bar->iomem = शून्य;
	पूर्ण

	nfp->bars = bar - &nfp->bar[0];
	अगर (nfp->bars < 8) अणु
		dev_err(nfp->dev, "No usable BARs found!\n");
		वापस -EINVAL;
	पूर्ण

	bars_मुक्त = nfp->bars;

	/* Convert unit ID (0..3) to संकेत master/data master ID (0x40..0x70)
	 */
	mutex_init(&nfp->expl.mutex);

	nfp->expl.master_id = ((NFP_CPP_INTERFACE_UNIT_of(पूर्णांकerface) & 3) + 4)
		<< 4;
	nfp->expl.संकेत_ref = 0x10;

	/* Configure, and lock, BAR0.0 क्रम General Target use (MSI-X SRAM) */
	bar = &nfp->bar[0];
	अगर (nfp_bar_resource_len(bar) >= NFP_PCI_MIN_MAP_SIZE)
		bar->iomem = ioremap(nfp_bar_resource_start(bar),
					     nfp_bar_resource_len(bar));
	अगर (bar->iomem) अणु
		पूर्णांक pf;

		msg += scnम_लिखो(msg, end - msg, "0.0: General/MSI-X SRAM, ");
		atomic_inc(&bar->refcnt);
		bars_मुक्त--;

		nfp6000_bar_ग_लिखो(nfp, bar, barcfg_msix_general);

		nfp->expl.data = bar->iomem + NFP_PCIE_SRAM + 0x1000;

		चयन (nfp->pdev->device) अणु
		हाल PCI_DEVICE_ID_NETRONOME_NFP3800:
			pf = nfp->pdev->devfn & 7;
			nfp->iomem.csr = bar->iomem + NFP_PCIE_BAR(pf);
			अवरोध;
		हाल PCI_DEVICE_ID_NETRONOME_NFP4000:
		हाल PCI_DEVICE_ID_NETRONOME_NFP5000:
		हाल PCI_DEVICE_ID_NETRONOME_NFP6000:
			nfp->iomem.csr = bar->iomem + NFP_PCIE_BAR(0);
			अवरोध;
		शेष:
			dev_err(nfp->dev, "Unsupported device ID: %04hx!\n",
				nfp->pdev->device);
			err = -EINVAL;
			जाओ err_unmap_bar0;
		पूर्ण
		nfp->iomem.em = bar->iomem + NFP_PCIE_EM;
	पूर्ण

	चयन (nfp->pdev->device) अणु
	हाल PCI_DEVICE_ID_NETRONOME_NFP3800:
		expl_groups = 1;
		अवरोध;
	हाल PCI_DEVICE_ID_NETRONOME_NFP4000:
	हाल PCI_DEVICE_ID_NETRONOME_NFP5000:
	हाल PCI_DEVICE_ID_NETRONOME_NFP6000:
		expl_groups = 4;
		अवरोध;
	शेष:
		dev_err(nfp->dev, "Unsupported device ID: %04hx!\n",
			nfp->pdev->device);
		err = -EINVAL;
		जाओ err_unmap_bar0;
	पूर्ण

	/* Configure, and lock, BAR0.1 क्रम PCIe XPB (MSI-X PBA) */
	bar = &nfp->bar[1];
	msg += scnम_लिखो(msg, end - msg, "0.1: PCIe XPB/MSI-X PBA, ");
	atomic_inc(&bar->refcnt);
	bars_मुक्त--;

	nfp6000_bar_ग_लिखो(nfp, bar, barcfg_msix_xpb);

	/* Use BAR0.4..BAR0.7 क्रम EXPL IO */
	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक j;

		अगर (i >= NFP_PCIE_EXPLICIT_BARS || i >= expl_groups) अणु
			nfp->expl.group[i].bitsize = 0;
			जारी;
		पूर्ण

		bar = &nfp->bar[4 + i];
		bar->iomem = ioremap(nfp_bar_resource_start(bar),
					     nfp_bar_resource_len(bar));
		अगर (bar->iomem) अणु
			msg += scnम_लिखो(msg, end - msg,
					 "0.%d: Explicit%d, ", 4 + i, i);
			atomic_inc(&bar->refcnt);
			bars_मुक्त--;

			nfp->expl.group[i].bitsize = bar->bitsize;
			nfp->expl.group[i].addr = bar->iomem;
			nfp6000_bar_ग_लिखो(nfp, bar, barcfg_explicit[i]);

			क्रम (j = 0; j < 4; j++)
				nfp->expl.group[i].मुक्त[j] = true;
		पूर्ण
		nfp->iomem.expl[i] = bar->iomem;
	पूर्ण

	/* Sort bars by bit size - use the smallest possible first. */
	sort(&nfp->bar[0], nfp->bars, माप(nfp->bar[0]),
	     bar_cmp, शून्य);

	dev_info(nfp->dev, "%sfree: %d/%d\n", status_msg, bars_मुक्त, nfp->bars);

	वापस 0;

err_unmap_bar0:
	अगर (nfp->bar[0].iomem)
		iounmap(nfp->bar[0].iomem);
	वापस err;
पूर्ण

अटल व्योम disable_bars(काष्ठा nfp6000_pcie *nfp)
अणु
	काष्ठा nfp_bar *bar = &nfp->bar[0];
	पूर्णांक n;

	क्रम (n = 0; n < nfp->bars; n++, bar++) अणु
		अगर (bar->iomem) अणु
			iounmap(bar->iomem);
			bar->iomem = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Generic CPP bus access पूर्णांकerface.
 */

काष्ठा nfp6000_area_priv अणु
	atomic_t refcnt;

	काष्ठा nfp_bar *bar;
	u32 bar_offset;

	u32 target;
	u32 action;
	u32 token;
	u64 offset;
	काष्ठा अणु
		पूर्णांक पढ़ो;
		पूर्णांक ग_लिखो;
		पूर्णांक bar;
	पूर्ण width;
	माप_प्रकार size;

	व्योम __iomem *iomem;
	phys_addr_t phys;
	काष्ठा resource resource;
पूर्ण;

अटल पूर्णांक nfp6000_area_init(काष्ठा nfp_cpp_area *area, u32 dest,
			     अचिन्हित दीर्घ दीर्घ address, अचिन्हित दीर्घ size)
अणु
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);
	u32 target = NFP_CPP_ID_TARGET_of(dest);
	u32 action = NFP_CPP_ID_ACTION_of(dest);
	u32 token = NFP_CPP_ID_TOKEN_of(dest);
	पूर्णांक pp;

	pp = nfp_target_pushpull(NFP_CPP_ID(target, action, token), address);
	अगर (pp < 0)
		वापस pp;

	priv->width.पढ़ो = PUSH_WIDTH(pp);
	priv->width.ग_लिखो = PULL_WIDTH(pp);
	अगर (priv->width.पढ़ो > 0 &&
	    priv->width.ग_लिखो > 0 &&
	    priv->width.पढ़ो != priv->width.ग_लिखो) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (priv->width.पढ़ो > 0)
		priv->width.bar = priv->width.पढ़ो;
	अन्यथा
		priv->width.bar = priv->width.ग_लिखो;

	atomic_set(&priv->refcnt, 0);
	priv->bar = शून्य;

	priv->target = target;
	priv->action = action;
	priv->token = token;
	priv->offset = address;
	priv->size = size;
	स_रखो(&priv->resource, 0, माप(priv->resource));

	वापस 0;
पूर्ण

अटल व्योम nfp6000_area_cleanup(काष्ठा nfp_cpp_area *area)
अणु
पूर्ण

अटल व्योम priv_area_get(काष्ठा nfp_cpp_area *area)
अणु
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);

	atomic_inc(&priv->refcnt);
पूर्ण

अटल पूर्णांक priv_area_put(काष्ठा nfp_cpp_area *area)
अणु
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);

	अगर (WARN_ON(!atomic_पढ़ो(&priv->refcnt)))
		वापस 0;

	वापस atomic_dec_and_test(&priv->refcnt);
पूर्ण

अटल पूर्णांक nfp6000_area_acquire(काष्ठा nfp_cpp_area *area)
अणु
	काष्ठा nfp6000_pcie *nfp = nfp_cpp_priv(nfp_cpp_area_cpp(area));
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);
	पूर्णांक barnum, err;

	अगर (priv->bar) अणु
		/* Alपढ़ोy allocated. */
		priv_area_get(area);
		वापस 0;
	पूर्ण

	barnum = nfp_alloc_bar(nfp, priv->target, priv->action, priv->token,
			       priv->offset, priv->size, priv->width.bar, 1);

	अगर (barnum < 0) अणु
		err = barnum;
		जाओ err_alloc_bar;
	पूर्ण
	priv->bar = &nfp->bar[barnum];

	/* Calculate offset पूर्णांकo BAR. */
	अगर (nfp_bar_maptype(priv->bar) ==
	    NFP_PCIE_BAR_PCIE2CPP_MapType_GENERAL) अणु
		priv->bar_offset = priv->offset &
			(NFP_PCIE_P2C_GENERAL_SIZE(priv->bar) - 1);
		priv->bar_offset += NFP_PCIE_P2C_GENERAL_TARGET_OFFSET(
			priv->bar, priv->target);
		priv->bar_offset += NFP_PCIE_P2C_GENERAL_TOKEN_OFFSET(
			priv->bar, priv->token);
	पूर्ण अन्यथा अणु
		priv->bar_offset = priv->offset & priv->bar->mask;
	पूर्ण

	/* We करोn't actually try to acquire the resource area using
	 * request_resource.  This would prevent sharing the mapped
	 * BAR between multiple CPP areas and prevent us from
	 * effectively utilizing the limited amount of BAR resources.
	 */
	priv->phys = nfp_bar_resource_start(priv->bar) + priv->bar_offset;
	priv->resource.name = nfp_cpp_area_name(area);
	priv->resource.start = priv->phys;
	priv->resource.end = priv->resource.start + priv->size - 1;
	priv->resource.flags = IORESOURCE_MEM;

	/* If the bar is alपढ़ोy mapped in, use its mapping */
	अगर (priv->bar->iomem)
		priv->iomem = priv->bar->iomem + priv->bar_offset;
	अन्यथा
		/* Must have been too big. Sub-allocate. */
		priv->iomem = ioremap(priv->phys, priv->size);

	अगर (IS_ERR_OR_शून्य(priv->iomem)) अणु
		dev_err(nfp->dev, "Can't ioremap() a %d byte region of BAR %d\n",
			(पूर्णांक)priv->size, priv->bar->index);
		err = !priv->iomem ? -ENOMEM : PTR_ERR(priv->iomem);
		priv->iomem = शून्य;
		जाओ err_iomem_remap;
	पूर्ण

	priv_area_get(area);
	वापस 0;

err_iomem_remap:
	nfp_bar_put(nfp, priv->bar);
	priv->bar = शून्य;
err_alloc_bar:
	वापस err;
पूर्ण

अटल व्योम nfp6000_area_release(काष्ठा nfp_cpp_area *area)
अणु
	काष्ठा nfp6000_pcie *nfp = nfp_cpp_priv(nfp_cpp_area_cpp(area));
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);

	अगर (!priv_area_put(area))
		वापस;

	अगर (!priv->bar->iomem)
		iounmap(priv->iomem);

	nfp_bar_put(nfp, priv->bar);

	priv->bar = शून्य;
	priv->iomem = शून्य;
पूर्ण

अटल phys_addr_t nfp6000_area_phys(काष्ठा nfp_cpp_area *area)
अणु
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);

	वापस priv->phys;
पूर्ण

अटल व्योम __iomem *nfp6000_area_iomem(काष्ठा nfp_cpp_area *area)
अणु
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);

	वापस priv->iomem;
पूर्ण

अटल काष्ठा resource *nfp6000_area_resource(काष्ठा nfp_cpp_area *area)
अणु
	/* Use the BAR resource as the resource क्रम the CPP area.
	 * This enables us to share the BAR among multiple CPP areas
	 * without resource conflicts.
	 */
	काष्ठा nfp6000_area_priv *priv = nfp_cpp_area_priv(area);

	वापस priv->bar->resource;
पूर्ण

अटल पूर्णांक nfp6000_area_पढ़ो(काष्ठा nfp_cpp_area *area, व्योम *kernel_vaddr,
			     अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक length)
अणु
	u64 __maybe_unused *wrptr64 = kernel_vaddr;
	स्थिर u64 __iomem __maybe_unused *rdptr64;
	काष्ठा nfp6000_area_priv *priv;
	u32 *wrptr32 = kernel_vaddr;
	स्थिर u32 __iomem *rdptr32;
	पूर्णांक n, width;

	priv = nfp_cpp_area_priv(area);
	rdptr64 = priv->iomem + offset;
	rdptr32 = priv->iomem + offset;

	अगर (offset + length > priv->size)
		वापस -EFAULT;

	width = priv->width.पढ़ो;
	अगर (width <= 0)
		वापस -EINVAL;

	/* MU पढ़ोs via a PCIe2CPP BAR support 32bit (and other) lengths */
	अगर (priv->target == (NFP_CPP_TARGET_MU & NFP_CPP_TARGET_ID_MASK) &&
	    priv->action == NFP_CPP_ACTION_RW &&
	    (offset % माप(u64) == 4 || length % माप(u64) == 4))
		width = TARGET_WIDTH_32;

	/* Unaligned? Translate to an explicit access */
	अगर ((priv->offset + offset) & (width - 1))
		वापस nfp_cpp_explicit_पढ़ो(nfp_cpp_area_cpp(area),
					     NFP_CPP_ID(priv->target,
							priv->action,
							priv->token),
					     priv->offset + offset,
					     kernel_vaddr, length, width);

	अगर (WARN_ON(!priv->bar))
		वापस -EFAULT;

	चयन (width) अणु
	हाल TARGET_WIDTH_32:
		अगर (offset % माप(u32) != 0 || length % माप(u32) != 0)
			वापस -EINVAL;

		क्रम (n = 0; n < length; n += माप(u32))
			*wrptr32++ = __raw_पढ़ोl(rdptr32++);
		वापस n;
#अगर_घोषित __raw_पढ़ोq
	हाल TARGET_WIDTH_64:
		अगर (offset % माप(u64) != 0 || length % माप(u64) != 0)
			वापस -EINVAL;

		क्रम (n = 0; n < length; n += माप(u64))
			*wrptr64++ = __raw_पढ़ोq(rdptr64++);
		वापस n;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp6000_area_ग_लिखो(काष्ठा nfp_cpp_area *area,
		   स्थिर व्योम *kernel_vaddr,
		   अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक length)
अणु
	स्थिर u64 __maybe_unused *rdptr64 = kernel_vaddr;
	u64 __iomem __maybe_unused *wrptr64;
	स्थिर u32 *rdptr32 = kernel_vaddr;
	काष्ठा nfp6000_area_priv *priv;
	u32 __iomem *wrptr32;
	पूर्णांक n, width;

	priv = nfp_cpp_area_priv(area);
	wrptr64 = priv->iomem + offset;
	wrptr32 = priv->iomem + offset;

	अगर (offset + length > priv->size)
		वापस -EFAULT;

	width = priv->width.ग_लिखो;
	अगर (width <= 0)
		वापस -EINVAL;

	/* MU ग_लिखोs via a PCIe2CPP BAR support 32bit (and other) lengths */
	अगर (priv->target == (NFP_CPP_TARGET_ID_MASK & NFP_CPP_TARGET_MU) &&
	    priv->action == NFP_CPP_ACTION_RW &&
	    (offset % माप(u64) == 4 || length % माप(u64) == 4))
		width = TARGET_WIDTH_32;

	/* Unaligned? Translate to an explicit access */
	अगर ((priv->offset + offset) & (width - 1))
		वापस nfp_cpp_explicit_ग_लिखो(nfp_cpp_area_cpp(area),
					      NFP_CPP_ID(priv->target,
							 priv->action,
							 priv->token),
					      priv->offset + offset,
					      kernel_vaddr, length, width);

	अगर (WARN_ON(!priv->bar))
		वापस -EFAULT;

	चयन (width) अणु
	हाल TARGET_WIDTH_32:
		अगर (offset % माप(u32) != 0 || length % माप(u32) != 0)
			वापस -EINVAL;

		क्रम (n = 0; n < length; n += माप(u32)) अणु
			__raw_ग_लिखोl(*rdptr32++, wrptr32++);
			wmb();
		पूर्ण
		वापस n;
#अगर_घोषित __raw_ग_लिखोq
	हाल TARGET_WIDTH_64:
		अगर (offset % माप(u64) != 0 || length % माप(u64) != 0)
			वापस -EINVAL;

		क्रम (n = 0; n < length; n += माप(u64)) अणु
			__raw_ग_लिखोq(*rdptr64++, wrptr64++);
			wmb();
		पूर्ण
		वापस n;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

काष्ठा nfp6000_explicit_priv अणु
	काष्ठा nfp6000_pcie *nfp;
	काष्ठा अणु
		पूर्णांक group;
		पूर्णांक area;
	पूर्ण bar;
	पूर्णांक bitsize;
	व्योम __iomem *data;
	व्योम __iomem *addr;
पूर्ण;

अटल पूर्णांक nfp6000_explicit_acquire(काष्ठा nfp_cpp_explicit *expl)
अणु
	काष्ठा nfp6000_pcie *nfp = nfp_cpp_priv(nfp_cpp_explicit_cpp(expl));
	काष्ठा nfp6000_explicit_priv *priv = nfp_cpp_explicit_priv(expl);
	पूर्णांक i, j;

	mutex_lock(&nfp->expl.mutex);
	क्रम (i = 0; i < ARRAY_SIZE(nfp->expl.group); i++) अणु
		अगर (!nfp->expl.group[i].bitsize)
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(nfp->expl.group[i].मुक्त); j++) अणु
			u16 data_offset;

			अगर (!nfp->expl.group[i].मुक्त[j])
				जारी;

			priv->nfp = nfp;
			priv->bar.group = i;
			priv->bar.area = j;
			priv->bitsize = nfp->expl.group[i].bitsize - 2;

			data_offset = (priv->bar.group << 9) +
				(priv->bar.area << 7);
			priv->data = nfp->expl.data + data_offset;
			priv->addr = nfp->expl.group[i].addr +
				(priv->bar.area << priv->bitsize);
			nfp->expl.group[i].मुक्त[j] = false;

			mutex_unlock(&nfp->expl.mutex);
			वापस 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&nfp->expl.mutex);

	वापस -EAGAIN;
पूर्ण

अटल व्योम nfp6000_explicit_release(काष्ठा nfp_cpp_explicit *expl)
अणु
	काष्ठा nfp6000_explicit_priv *priv = nfp_cpp_explicit_priv(expl);
	काष्ठा nfp6000_pcie *nfp = priv->nfp;

	mutex_lock(&nfp->expl.mutex);
	nfp->expl.group[priv->bar.group].मुक्त[priv->bar.area] = true;
	mutex_unlock(&nfp->expl.mutex);
पूर्ण

अटल पूर्णांक nfp6000_explicit_put(काष्ठा nfp_cpp_explicit *expl,
				स्थिर व्योम *buff, माप_प्रकार len)
अणु
	काष्ठा nfp6000_explicit_priv *priv = nfp_cpp_explicit_priv(expl);
	स्थिर u32 *src = buff;
	माप_प्रकार i;

	क्रम (i = 0; i < len; i += माप(u32))
		ग_लिखोl(*(src++), priv->data + i);

	वापस i;
पूर्ण

अटल पूर्णांक
nfp6000_explicit_करो(काष्ठा nfp_cpp_explicit *expl,
		    स्थिर काष्ठा nfp_cpp_explicit_command *cmd, u64 address)
अणु
	काष्ठा nfp6000_explicit_priv *priv = nfp_cpp_explicit_priv(expl);
	u8 संकेत_master, संकेत_ref, data_master;
	काष्ठा nfp6000_pcie *nfp = priv->nfp;
	पूर्णांक sigmask = 0;
	u16 data_ref;
	u32 csr[3];

	अगर (cmd->siga_mode)
		sigmask |= 1 << cmd->siga;
	अगर (cmd->sigb_mode)
		sigmask |= 1 << cmd->sigb;

	संकेत_master = cmd->संकेत_master;
	अगर (!संकेत_master)
		संकेत_master = nfp->expl.master_id;

	संकेत_ref = cmd->संकेत_ref;
	अगर (संकेत_master == nfp->expl.master_id)
		संकेत_ref = nfp->expl.संकेत_ref +
			((priv->bar.group * 4 + priv->bar.area) << 1);

	data_master = cmd->data_master;
	अगर (!data_master)
		data_master = nfp->expl.master_id;

	data_ref = cmd->data_ref;
	अगर (data_master == nfp->expl.master_id)
		data_ref = 0x1000 +
			(priv->bar.group << 9) + (priv->bar.area << 7);

	csr[0] = NFP_PCIE_BAR_EXPLICIT_BAR0_SignalType(sigmask) |
		NFP_PCIE_BAR_EXPLICIT_BAR0_Token(
			NFP_CPP_ID_TOKEN_of(cmd->cpp_id)) |
		NFP_PCIE_BAR_EXPLICIT_BAR0_Address(address >> 16);

	csr[1] = NFP_PCIE_BAR_EXPLICIT_BAR1_SignalRef(संकेत_ref) |
		NFP_PCIE_BAR_EXPLICIT_BAR1_DataMaster(data_master) |
		NFP_PCIE_BAR_EXPLICIT_BAR1_DataRef(data_ref);

	csr[2] = NFP_PCIE_BAR_EXPLICIT_BAR2_Target(
			NFP_CPP_ID_TARGET_of(cmd->cpp_id)) |
		NFP_PCIE_BAR_EXPLICIT_BAR2_Action(
			NFP_CPP_ID_ACTION_of(cmd->cpp_id)) |
		NFP_PCIE_BAR_EXPLICIT_BAR2_Length(cmd->len) |
		NFP_PCIE_BAR_EXPLICIT_BAR2_ByteMask(cmd->byte_mask) |
		NFP_PCIE_BAR_EXPLICIT_BAR2_SignalMaster(संकेत_master);

	अगर (nfp->iomem.csr) अणु
		ग_लिखोl(csr[0], nfp->iomem.csr +
		       NFP_PCIE_BAR_EXPLICIT_BAR0(priv->bar.group,
						  priv->bar.area));
		ग_लिखोl(csr[1], nfp->iomem.csr +
		       NFP_PCIE_BAR_EXPLICIT_BAR1(priv->bar.group,
						  priv->bar.area));
		ग_लिखोl(csr[2], nfp->iomem.csr +
		       NFP_PCIE_BAR_EXPLICIT_BAR2(priv->bar.group,
						  priv->bar.area));
		/* Readback to ensure BAR is flushed */
		पढ़ोl(nfp->iomem.csr +
		      NFP_PCIE_BAR_EXPLICIT_BAR0(priv->bar.group,
						 priv->bar.area));
		पढ़ोl(nfp->iomem.csr +
		      NFP_PCIE_BAR_EXPLICIT_BAR1(priv->bar.group,
						 priv->bar.area));
		पढ़ोl(nfp->iomem.csr +
		      NFP_PCIE_BAR_EXPLICIT_BAR2(priv->bar.group,
						 priv->bar.area));
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_dword(nfp->pdev, 0x400 +
				       NFP_PCIE_BAR_EXPLICIT_BAR0(
					       priv->bar.group, priv->bar.area),
				       csr[0]);

		pci_ग_लिखो_config_dword(nfp->pdev, 0x400 +
				       NFP_PCIE_BAR_EXPLICIT_BAR1(
					       priv->bar.group, priv->bar.area),
				       csr[1]);

		pci_ग_लिखो_config_dword(nfp->pdev, 0x400 +
				       NFP_PCIE_BAR_EXPLICIT_BAR2(
					       priv->bar.group, priv->bar.area),
				       csr[2]);
	पूर्ण

	/* Issue the 'kickoff' transaction */
	पढ़ोb(priv->addr + (address & ((1 << priv->bitsize) - 1)));

	वापस sigmask;
पूर्ण

अटल पूर्णांक nfp6000_explicit_get(काष्ठा nfp_cpp_explicit *expl,
				व्योम *buff, माप_प्रकार len)
अणु
	काष्ठा nfp6000_explicit_priv *priv = nfp_cpp_explicit_priv(expl);
	u32 *dst = buff;
	माप_प्रकार i;

	क्रम (i = 0; i < len; i += माप(u32))
		*(dst++) = पढ़ोl(priv->data + i);

	वापस i;
पूर्ण

अटल पूर्णांक nfp6000_init(काष्ठा nfp_cpp *cpp)
अणु
	nfp_cpp_area_cache_add(cpp, SZ_64K);
	nfp_cpp_area_cache_add(cpp, SZ_64K);
	nfp_cpp_area_cache_add(cpp, SZ_256K);

	वापस 0;
पूर्ण

अटल व्योम nfp6000_मुक्त(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp6000_pcie *nfp = nfp_cpp_priv(cpp);

	disable_bars(nfp);
	kमुक्त(nfp);
पूर्ण

अटल पूर्णांक nfp6000_पढ़ो_serial(काष्ठा device *dev, u8 *serial)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u64 dsn;

	dsn = pci_get_dsn(pdev);
	अगर (!dsn) अणु
		dev_err(dev, "can't find PCIe Serial Number Capability\n");
		वापस -EINVAL;
	पूर्ण

	put_unaligned_be32((u32)(dsn >> 32), serial);
	put_unaligned_be16((u16)(dsn >> 16), serial + 4);

	वापस 0;
पूर्ण

अटल पूर्णांक nfp6000_get_पूर्णांकerface(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u64 dsn;

	dsn = pci_get_dsn(pdev);
	अगर (!dsn) अणु
		dev_err(dev, "can't find PCIe Serial Number Capability\n");
		वापस -EINVAL;
	पूर्ण

	वापस dsn & 0xffff;
पूर्ण

अटल स्थिर काष्ठा nfp_cpp_operations nfp6000_pcie_ops = अणु
	.owner			= THIS_MODULE,

	.init			= nfp6000_init,
	.मुक्त			= nfp6000_मुक्त,

	.पढ़ो_serial		= nfp6000_पढ़ो_serial,
	.get_पूर्णांकerface		= nfp6000_get_पूर्णांकerface,

	.area_priv_size		= माप(काष्ठा nfp6000_area_priv),
	.area_init		= nfp6000_area_init,
	.area_cleanup		= nfp6000_area_cleanup,
	.area_acquire		= nfp6000_area_acquire,
	.area_release		= nfp6000_area_release,
	.area_phys		= nfp6000_area_phys,
	.area_iomem		= nfp6000_area_iomem,
	.area_resource		= nfp6000_area_resource,
	.area_पढ़ो		= nfp6000_area_पढ़ो,
	.area_ग_लिखो		= nfp6000_area_ग_लिखो,

	.explicit_priv_size	= माप(काष्ठा nfp6000_explicit_priv),
	.explicit_acquire	= nfp6000_explicit_acquire,
	.explicit_release	= nfp6000_explicit_release,
	.explicit_put		= nfp6000_explicit_put,
	.explicit_करो		= nfp6000_explicit_करो,
	.explicit_get		= nfp6000_explicit_get,
पूर्ण;

/**
 * nfp_cpp_from_nfp6000_pcie() - Build a NFP CPP bus from a NFP6000 PCI device
 * @pdev:	NFP6000 PCI device
 *
 * Return: NFP CPP handle
 */
काष्ठा nfp_cpp *nfp_cpp_from_nfp6000_pcie(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nfp6000_pcie *nfp;
	u16 पूर्णांकerface;
	पूर्णांक err;

	/*  Finished with card initialization. */
	dev_info(&pdev->dev,
		 "Netronome Flow Processor NFP4000/NFP5000/NFP6000 PCIe Card Probe\n");
	pcie_prपूर्णांक_link_status(pdev);

	nfp = kzalloc(माप(*nfp), GFP_KERNEL);
	अगर (!nfp) अणु
		err = -ENOMEM;
		जाओ err_ret;
	पूर्ण

	nfp->dev = &pdev->dev;
	nfp->pdev = pdev;
	init_रुकोqueue_head(&nfp->bar_रुकोers);
	spin_lock_init(&nfp->bar_lock);

	पूर्णांकerface = nfp6000_get_पूर्णांकerface(&pdev->dev);

	अगर (NFP_CPP_INTERFACE_TYPE_of(पूर्णांकerface) !=
	    NFP_CPP_INTERFACE_TYPE_PCI) अणु
		dev_err(&pdev->dev,
			"Interface type %d is not the expected %d\n",
			NFP_CPP_INTERFACE_TYPE_of(पूर्णांकerface),
			NFP_CPP_INTERFACE_TYPE_PCI);
		err = -ENODEV;
		जाओ err_मुक्त_nfp;
	पूर्ण

	अगर (NFP_CPP_INTERFACE_CHANNEL_of(पूर्णांकerface) !=
	    NFP_CPP_INTERFACE_CHANNEL_PEROPENER) अणु
		dev_err(&pdev->dev, "Interface channel %d is not the expected %d\n",
			NFP_CPP_INTERFACE_CHANNEL_of(पूर्णांकerface),
			NFP_CPP_INTERFACE_CHANNEL_PEROPENER);
		err = -ENODEV;
		जाओ err_मुक्त_nfp;
	पूर्ण

	err = enable_bars(nfp, पूर्णांकerface);
	अगर (err)
		जाओ err_मुक्त_nfp;

	/* Probe क्रम all the common NFP devices */
	वापस nfp_cpp_from_operations(&nfp6000_pcie_ops, &pdev->dev, nfp);

err_मुक्त_nfp:
	kमुक्त(nfp);
err_ret:
	dev_err(&pdev->dev, "NFP6000 PCI setup failed\n");
	वापस ERR_PTR(err);
पूर्ण
