<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
**  Device driver क्रम the PCI-SCSI NCR538XX controller family.
**
**  Copyright (C) 1994  Wolfgang Stanglmeier
**
**
**-----------------------------------------------------------------------------
**
**  This driver has been ported to Linux from the FreeBSD NCR53C8XX driver
**  and is currently मुख्यtained by
**
**          Gerard Roudier              <groudier@मुक्त.fr>
**
**  Being given that this driver originates from the FreeBSD version, and
**  in order to keep synergy on both, any suggested enhancements and corrections
**  received on Linux are स्वतःmatically a potential candidate क्रम the FreeBSD 
**  version.
**
**  The original driver has been written क्रम 386bsd and FreeBSD by
**          Wolfgang Stanglmeier        <wolf@cologne.de>
**          Stefan Esser                <se@mi.Uni-Koeln.de>
**
**  And has been ported to NetBSD by
**          Charles M. Hannum           <mycroft@gnu.ai.mit.edu>
**
**-----------------------------------------------------------------------------
**
**                     Brief history
**
**  December 10 1995 by Gerard Roudier:
**     Initial port to Linux.
**
**  June 23 1996 by Gerard Roudier:
**     Support क्रम 64 bits architectures (Alpha).
**
**  November 30 1996 by Gerard Roudier:
**     Support क्रम Fast-20 scsi.
**     Support क्रम large DMA fअगरo and 128 dwords bursting.
**
**  February 27 1997 by Gerard Roudier:
**     Support क्रम Fast-40 scsi.
**     Support क्रम on-Board RAM.
**
**  May 3 1997 by Gerard Roudier:
**     Full support क्रम scsi scripts inकाष्ठाions pre-fetching.
**
**  May 19 1997 by Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>:
**     Support क्रम NvRAM detection and पढ़ोing.
**
**  August 18 1997 by Cort <cort@cs.nmt.edu>:
**     Support क्रम Power/PC (Big Endian).
**
**  June 20 1998 by Gerard Roudier
**     Support क्रम up to 64 tags per lun.
**     O(1) everywhere (C and SCRIPTS) क्रम normal हालs.
**     Low PCI traffic क्रम command handling when on-chip RAM is present.
**     Aggressive SCSI SCRIPTS optimizations.
**
**  2005 by Matthew Wilcox and James Bottomley
**     PCI-ectomy.  This driver now supports only the 720 chip (see the
**     NCR_Q720 and zalon drivers क्रम the bus probe logic).
**
*******************************************************************************
*/

/*
**	Supported SCSI-II features:
**	    Synchronous negotiation
**	    Wide negotiation        (depends on the NCR Chip)
**	    Enable disconnection
**	    Tagged command queuing
**	    Parity checking
**	    Etc...
**
**	Supported NCR/SYMBIOS chips:
**		53C720		(Wide,   Fast SCSI-2, पूर्णांकfly problems)
*/

/* Name and version of the driver */
#घोषणा SCSI_NCR_DRIVER_NAME	"ncr53c8xx-3.4.3g"

#घोषणा SCSI_NCR_DEBUG_FLAGS	(0)

#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "ncr53c8xx.h"

#घोषणा NAME53C8XX		"ncr53c8xx"

/*==========================================================
**
**	Debugging tags
**
**==========================================================
*/

#घोषणा DEBUG_ALLOC    (0x0001)
#घोषणा DEBUG_PHASE    (0x0002)
#घोषणा DEBUG_QUEUE    (0x0008)
#घोषणा DEBUG_RESULT   (0x0010)
#घोषणा DEBUG_POINTER  (0x0020)
#घोषणा DEBUG_SCRIPT   (0x0040)
#घोषणा DEBUG_TINY     (0x0080)
#घोषणा DEBUG_TIMING   (0x0100)
#घोषणा DEBUG_NEGO     (0x0200)
#घोषणा DEBUG_TAGS     (0x0400)
#घोषणा DEBUG_SCATTER  (0x0800)
#घोषणा DEBUG_IC        (0x1000)

/*
**    Enable/Disable debug messages.
**    Can be changed at runसमय too.
*/

#अगर_घोषित SCSI_NCR_DEBUG_INFO_SUPPORT
अटल पूर्णांक ncr_debug = SCSI_NCR_DEBUG_FLAGS;
	#घोषणा DEBUG_FLAGS ncr_debug
#अन्यथा
	#घोषणा DEBUG_FLAGS	SCSI_NCR_DEBUG_FLAGS
#पूर्ण_अगर

/*
 * Locally used status flag
 */
#घोषणा SAM_STAT_ILLEGAL	0xff

अटल अंतरभूत काष्ठा list_head *ncr_list_pop(काष्ठा list_head *head)
अणु
	अगर (!list_empty(head)) अणु
		काष्ठा list_head *elem = head->next;

		list_del(elem);
		वापस elem;
	पूर्ण

	वापस शून्य;
पूर्ण

/*==========================================================
**
**	Simple घातer of two buddy-like allocator.
**
**	This simple code is not पूर्णांकended to be fast, but to 
**	provide घातer of 2 aligned memory allocations.
**	Since the SCRIPTS processor only supplies 8 bit 
**	arithmetic, this allocator allows simple and fast 
**	address calculations  from the SCRIPTS code.
**	In addition, cache line alignment is guaranteed क्रम 
**	घातer of 2 cache line size.
**	Enhanced in linux-2.3.44 to provide a memory pool 
**	per pcidev to support dynamic dma mapping. (I would 
**	have preferred a real bus असलtraction, btw).
**
**==========================================================
*/

#घोषणा MEMO_SHIFT	4	/* 16 bytes minimum memory chunk */
#अगर PAGE_SIZE >= 8192
#घोषणा MEMO_PAGE_ORDER	0	/* 1 PAGE  maximum */
#अन्यथा
#घोषणा MEMO_PAGE_ORDER	1	/* 2 PAGES maximum */
#पूर्ण_अगर
#घोषणा MEMO_FREE_UNUSED	/* Free unused pages immediately */
#घोषणा MEMO_WARN	1
#घोषणा MEMO_GFP_FLAGS	GFP_ATOMIC
#घोषणा MEMO_CLUSTER_SHIFT	(PAGE_SHIFT+MEMO_PAGE_ORDER)
#घोषणा MEMO_CLUSTER_SIZE	(1UL << MEMO_CLUSTER_SHIFT)
#घोषणा MEMO_CLUSTER_MASK	(MEMO_CLUSTER_SIZE-1)

प्रकार u_दीर्घ m_addr_t;	/* Enough bits to bit-hack addresses */
प्रकार काष्ठा device *m_bush_t;	/* Something that addresses DMAable */

प्रकार काष्ठा m_link अणु		/* Link between मुक्त memory chunks */
	काष्ठा m_link *next;
पूर्ण m_link_s;

प्रकार काष्ठा m_vtob अणु		/* Virtual to Bus address translation */
	काष्ठा m_vtob *next;
	m_addr_t vaddr;
	m_addr_t baddr;
पूर्ण m_vtob_s;
#घोषणा VTOB_HASH_SHIFT		5
#घोषणा VTOB_HASH_SIZE		(1UL << VTOB_HASH_SHIFT)
#घोषणा VTOB_HASH_MASK		(VTOB_HASH_SIZE-1)
#घोषणा VTOB_HASH_CODE(m)	\
	((((m_addr_t) (m)) >> MEMO_CLUSTER_SHIFT) & VTOB_HASH_MASK)

प्रकार काष्ठा m_pool अणु		/* Memory pool of a given kind */
	m_bush_t bush;
	m_addr_t (*getp)(काष्ठा m_pool *);
	व्योम (*मुक्तp)(काष्ठा m_pool *, m_addr_t);
	पूर्णांक nump;
	m_vtob_s *(vtob[VTOB_HASH_SIZE]);
	काष्ठा m_pool *next;
	काष्ठा m_link h[PAGE_SHIFT-MEMO_SHIFT+MEMO_PAGE_ORDER+1];
पूर्ण m_pool_s;

अटल व्योम *___m_alloc(m_pool_s *mp, पूर्णांक size)
अणु
	पूर्णांक i = 0;
	पूर्णांक s = (1 << MEMO_SHIFT);
	पूर्णांक j;
	m_addr_t a;
	m_link_s *h = mp->h;

	अगर (size > (PAGE_SIZE << MEMO_PAGE_ORDER))
		वापस शून्य;

	जबतक (size > s) अणु
		s <<= 1;
		++i;
	पूर्ण

	j = i;
	जबतक (!h[j].next) अणु
		अगर (s == (PAGE_SIZE << MEMO_PAGE_ORDER)) अणु
			h[j].next = (m_link_s *)mp->getp(mp);
			अगर (h[j].next)
				h[j].next->next = शून्य;
			अवरोध;
		पूर्ण
		++j;
		s <<= 1;
	पूर्ण
	a = (m_addr_t) h[j].next;
	अगर (a) अणु
		h[j].next = h[j].next->next;
		जबतक (j > i) अणु
			j -= 1;
			s >>= 1;
			h[j].next = (m_link_s *) (a+s);
			h[j].next->next = शून्य;
		पूर्ण
	पूर्ण
#अगर_घोषित DEBUG
	prपूर्णांकk("___m_alloc(%d) = %p\n", size, (व्योम *) a);
#पूर्ण_अगर
	वापस (व्योम *) a;
पूर्ण

अटल व्योम ___m_मुक्त(m_pool_s *mp, व्योम *ptr, पूर्णांक size)
अणु
	पूर्णांक i = 0;
	पूर्णांक s = (1 << MEMO_SHIFT);
	m_link_s *q;
	m_addr_t a, b;
	m_link_s *h = mp->h;

#अगर_घोषित DEBUG
	prपूर्णांकk("___m_free(%p, %d)\n", ptr, size);
#पूर्ण_अगर

	अगर (size > (PAGE_SIZE << MEMO_PAGE_ORDER))
		वापस;

	जबतक (size > s) अणु
		s <<= 1;
		++i;
	पूर्ण

	a = (m_addr_t) ptr;

	जबतक (1) अणु
#अगर_घोषित MEMO_FREE_UNUSED
		अगर (s == (PAGE_SIZE << MEMO_PAGE_ORDER)) अणु
			mp->मुक्तp(mp, a);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		b = a ^ s;
		q = &h[i];
		जबतक (q->next && q->next != (m_link_s *) b) अणु
			q = q->next;
		पूर्ण
		अगर (!q->next) अणु
			((m_link_s *) a)->next = h[i].next;
			h[i].next = (m_link_s *) a;
			अवरोध;
		पूर्ण
		q->next = q->next->next;
		a = a & b;
		s <<= 1;
		++i;
	पूर्ण
पूर्ण

अटल DEFINE_SPINLOCK(ncr53c8xx_lock);

अटल व्योम *__m_सुस्मृति2(m_pool_s *mp, पूर्णांक size, अक्षर *name, पूर्णांक uflags)
अणु
	व्योम *p;

	p = ___m_alloc(mp, size);

	अगर (DEBUG_FLAGS & DEBUG_ALLOC)
		prपूर्णांकk ("new %-10s[%4d] @%p.\n", name, size, p);

	अगर (p)
		स_रखो(p, 0, size);
	अन्यथा अगर (uflags & MEMO_WARN)
		prपूर्णांकk (NAME53C8XX ": failed to allocate %s[%d]\n", name, size);

	वापस p;
पूर्ण

#घोषणा __m_सुस्मृति(mp, s, n)	__m_सुस्मृति2(mp, s, n, MEMO_WARN)

अटल व्योम __m_मुक्त(m_pool_s *mp, व्योम *ptr, पूर्णांक size, अक्षर *name)
अणु
	अगर (DEBUG_FLAGS & DEBUG_ALLOC)
		prपूर्णांकk ("freeing %-10s[%4d] @%p.\n", name, size, ptr);

	___m_मुक्त(mp, ptr, size);

पूर्ण

/*
 * With pci bus iommu support, we use a शेष pool of unmapped memory 
 * क्रम memory we करोnnot need to DMA from/to and one pool per pcidev क्रम 
 * memory accessed by the PCI chip. `mp0' is the शेष not DMAable pool.
 */

अटल m_addr_t ___mp0_getp(m_pool_s *mp)
अणु
	m_addr_t m = __get_मुक्त_pages(MEMO_GFP_FLAGS, MEMO_PAGE_ORDER);
	अगर (m)
		++mp->nump;
	वापस m;
पूर्ण

अटल व्योम ___mp0_मुक्तp(m_pool_s *mp, m_addr_t m)
अणु
	मुक्त_pages(m, MEMO_PAGE_ORDER);
	--mp->nump;
पूर्ण

अटल m_pool_s mp0 = अणुशून्य, ___mp0_getp, ___mp0_मुक्तpपूर्ण;

/*
 * DMAable pools.
 */

/*
 * With pci bus iommu support, we मुख्यtain one pool per pcidev and a 
 * hashed reverse table क्रम भव to bus physical address translations.
 */
अटल m_addr_t ___dma_getp(m_pool_s *mp)
अणु
	m_addr_t vp;
	m_vtob_s *vbp;

	vbp = __m_सुस्मृति(&mp0, माप(*vbp), "VTOB");
	अगर (vbp) अणु
		dma_addr_t daddr;
		vp = (m_addr_t) dma_alloc_coherent(mp->bush,
						PAGE_SIZE<<MEMO_PAGE_ORDER,
						&daddr, GFP_ATOMIC);
		अगर (vp) अणु
			पूर्णांक hc = VTOB_HASH_CODE(vp);
			vbp->vaddr = vp;
			vbp->baddr = daddr;
			vbp->next = mp->vtob[hc];
			mp->vtob[hc] = vbp;
			++mp->nump;
			वापस vp;
		पूर्ण
	पूर्ण
	अगर (vbp)
		__m_मुक्त(&mp0, vbp, माप(*vbp), "VTOB");
	वापस 0;
पूर्ण

अटल व्योम ___dma_मुक्तp(m_pool_s *mp, m_addr_t m)
अणु
	m_vtob_s **vbpp, *vbp;
	पूर्णांक hc = VTOB_HASH_CODE(m);

	vbpp = &mp->vtob[hc];
	जबतक (*vbpp && (*vbpp)->vaddr != m)
		vbpp = &(*vbpp)->next;
	अगर (*vbpp) अणु
		vbp = *vbpp;
		*vbpp = (*vbpp)->next;
		dma_मुक्त_coherent(mp->bush, PAGE_SIZE<<MEMO_PAGE_ORDER,
				  (व्योम *)vbp->vaddr, (dma_addr_t)vbp->baddr);
		__m_मुक्त(&mp0, vbp, माप(*vbp), "VTOB");
		--mp->nump;
	पूर्ण
पूर्ण

अटल अंतरभूत m_pool_s *___get_dma_pool(m_bush_t bush)
अणु
	m_pool_s *mp;
	क्रम (mp = mp0.next; mp && mp->bush != bush; mp = mp->next);
	वापस mp;
पूर्ण

अटल m_pool_s *___cre_dma_pool(m_bush_t bush)
अणु
	m_pool_s *mp;
	mp = __m_सुस्मृति(&mp0, माप(*mp), "MPOOL");
	अगर (mp) अणु
		स_रखो(mp, 0, माप(*mp));
		mp->bush = bush;
		mp->getp = ___dma_getp;
		mp->मुक्तp = ___dma_मुक्तp;
		mp->next = mp0.next;
		mp0.next = mp;
	पूर्ण
	वापस mp;
पूर्ण

अटल व्योम ___del_dma_pool(m_pool_s *p)
अणु
	काष्ठा m_pool **pp = &mp0.next;

	जबतक (*pp && *pp != p)
		pp = &(*pp)->next;
	अगर (*pp) अणु
		*pp = (*pp)->next;
		__m_मुक्त(&mp0, p, माप(*p), "MPOOL");
	पूर्ण
पूर्ण

अटल व्योम *__m_सुस्मृति_dma(m_bush_t bush, पूर्णांक size, अक्षर *name)
अणु
	u_दीर्घ flags;
	काष्ठा m_pool *mp;
	व्योम *m = शून्य;

	spin_lock_irqsave(&ncr53c8xx_lock, flags);
	mp = ___get_dma_pool(bush);
	अगर (!mp)
		mp = ___cre_dma_pool(bush);
	अगर (mp)
		m = __m_सुस्मृति(mp, size, name);
	अगर (mp && !mp->nump)
		___del_dma_pool(mp);
	spin_unlock_irqrestore(&ncr53c8xx_lock, flags);

	वापस m;
पूर्ण

अटल व्योम __m_मुक्त_dma(m_bush_t bush, व्योम *m, पूर्णांक size, अक्षर *name)
अणु
	u_दीर्घ flags;
	काष्ठा m_pool *mp;

	spin_lock_irqsave(&ncr53c8xx_lock, flags);
	mp = ___get_dma_pool(bush);
	अगर (mp)
		__m_मुक्त(mp, m, size, name);
	अगर (mp && !mp->nump)
		___del_dma_pool(mp);
	spin_unlock_irqrestore(&ncr53c8xx_lock, flags);
पूर्ण

अटल m_addr_t __vtobus(m_bush_t bush, व्योम *m)
अणु
	u_दीर्घ flags;
	m_pool_s *mp;
	पूर्णांक hc = VTOB_HASH_CODE(m);
	m_vtob_s *vp = शून्य;
	m_addr_t a = ((m_addr_t) m) & ~MEMO_CLUSTER_MASK;

	spin_lock_irqsave(&ncr53c8xx_lock, flags);
	mp = ___get_dma_pool(bush);
	अगर (mp) अणु
		vp = mp->vtob[hc];
		जबतक (vp && (m_addr_t) vp->vaddr != a)
			vp = vp->next;
	पूर्ण
	spin_unlock_irqrestore(&ncr53c8xx_lock, flags);
	वापस vp ? vp->baddr + (((m_addr_t) m) - a) : 0;
पूर्ण

#घोषणा _m_सुस्मृति_dma(np, s, n)		__m_सुस्मृति_dma(np->dev, s, n)
#घोषणा _m_मुक्त_dma(np, p, s, n)	__m_मुक्त_dma(np->dev, p, s, n)
#घोषणा m_सुस्मृति_dma(s, n)		_m_सुस्मृति_dma(np, s, n)
#घोषणा m_मुक्त_dma(p, s, n)		_m_मुक्त_dma(np, p, s, n)
#घोषणा _vtobus(np, p)			__vtobus(np->dev, p)
#घोषणा vtobus(p)			_vtobus(np, p)

/*
 *  Deal with DMA mapping/unmapping.
 */

/* To keep track of the dma mapping (sg/single) that has been set */
#घोषणा __data_mapped	SCp.phase
#घोषणा __data_mapping	SCp.have_data_in

अटल व्योम __unmap_scsi_data(काष्ठा device *dev, काष्ठा scsi_cmnd *cmd)
अणु
	चयन(cmd->__data_mapped) अणु
	हाल 2:
		scsi_dma_unmap(cmd);
		अवरोध;
	पूर्ण
	cmd->__data_mapped = 0;
पूर्ण

अटल पूर्णांक __map_scsi_sg_data(काष्ठा device *dev, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक use_sg;

	use_sg = scsi_dma_map(cmd);
	अगर (!use_sg)
		वापस 0;

	cmd->__data_mapped = 2;
	cmd->__data_mapping = use_sg;

	वापस use_sg;
पूर्ण

#घोषणा unmap_scsi_data(np, cmd)	__unmap_scsi_data(np->dev, cmd)
#घोषणा map_scsi_sg_data(np, cmd)	__map_scsi_sg_data(np->dev, cmd)

/*==========================================================
**
**	Driver setup.
**
**	This काष्ठाure is initialized from linux config 
**	options. It can be overridden at boot-up by the boot 
**	command line.
**
**==========================================================
*/
अटल काष्ठा ncr_driver_setup
	driver_setup			= SCSI_NCR_DRIVER_SETUP;

#अगर_अघोषित MODULE
#अगर_घोषित	SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
अटल काष्ठा ncr_driver_setup
	driver_safe_setup __initdata	= SCSI_NCR_DRIVER_SAFE_SETUP;
#पूर्ण_अगर
#पूर्ण_अगर /* !MODULE */

#घोषणा initverbose (driver_setup.verbose)
#घोषणा bootverbose (np->verbose)


/*===================================================================
**
**	Driver setup from the boot command line
**
**===================================================================
*/

#अगर_घोषित MODULE
#घोषणा	ARG_SEP	' '
#अन्यथा
#घोषणा	ARG_SEP	','
#पूर्ण_अगर

#घोषणा OPT_TAGS		1
#घोषणा OPT_MASTER_PARITY	2
#घोषणा OPT_SCSI_PARITY		3
#घोषणा OPT_DISCONNECTION	4
#घोषणा OPT_SPECIAL_FEATURES	5
#घोषणा OPT_UNUSED_1		6
#घोषणा OPT_FORCE_SYNC_NEGO	7
#घोषणा OPT_REVERSE_PROBE	8
#घोषणा OPT_DEFAULT_SYNC	9
#घोषणा OPT_VERBOSE		10
#घोषणा OPT_DEBUG		11
#घोषणा OPT_BURST_MAX		12
#घोषणा OPT_LED_PIN		13
#घोषणा OPT_MAX_WIDE		14
#घोषणा OPT_SETTLE_DELAY	15
#घोषणा OPT_DIFF_SUPPORT	16
#घोषणा OPT_IRQM		17
#घोषणा OPT_PCI_FIX_UP		18
#घोषणा OPT_BUS_CHECK		19
#घोषणा OPT_OPTIMIZE		20
#घोषणा OPT_RECOVERY		21
#घोषणा OPT_SAFE_SETUP		22
#घोषणा OPT_USE_NVRAM		23
#घोषणा OPT_EXCLUDE		24
#घोषणा OPT_HOST_ID		25

#अगर_घोषित SCSI_NCR_IARB_SUPPORT
#घोषणा OPT_IARB		26
#पूर्ण_अगर

#अगर_घोषित MODULE
#घोषणा	ARG_SEP	' '
#अन्यथा
#घोषणा	ARG_SEP	','
#पूर्ण_अगर

#अगर_अघोषित MODULE
अटल अक्षर setup_token[] __initdata = 
	"tags:"   "mpar:"
	"spar:"   "disc:"
	"specf:"  "ultra:"
	"fsn:"    "revprob:"
	"sync:"   "verb:"
	"debug:"  "burst:"
	"led:"    "wide:"
	"settle:" "diff:"
	"irqm:"   "pcifix:"
	"buschk:" "optim:"
	"recovery:"
	"safe:"   "nvram:"
	"excl:"   "hostid:"
#अगर_घोषित SCSI_NCR_IARB_SUPPORT
	"iarb:"
#पूर्ण_अगर
	;	/* DONNOT REMOVE THIS ';' */

अटल पूर्णांक __init get_setup_token(अक्षर *p)
अणु
	अक्षर *cur = setup_token;
	अक्षर *pc;
	पूर्णांक i = 0;

	जबतक (cur != शून्य && (pc = म_अक्षर(cur, ':')) != शून्य) अणु
		++pc;
		++i;
		अगर (!म_भेदन(p, cur, pc - cur))
			वापस i;
		cur = pc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init sym53c8xx__setup(अक्षर *str)
अणु
#अगर_घोषित SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
	अक्षर *cur = str;
	अक्षर *pc, *pv;
	पूर्णांक i, val, c;
	पूर्णांक xi = 0;

	जबतक (cur != शून्य && (pc = म_अक्षर(cur, ':')) != शून्य) अणु
		अक्षर *pe;

		val = 0;
		pv = pc;
		c = *++pv;

		अगर	(c == 'n')
			val = 0;
		अन्यथा अगर	(c == 'y')
			val = 1;
		अन्यथा
			val = (पूर्णांक) simple_म_से_अदीर्घ(pv, &pe, 0);

		चयन (get_setup_token(cur)) अणु
		हाल OPT_TAGS:
			driver_setup.शेष_tags = val;
			अगर (pe && *pe == '/') अणु
				i = 0;
				जबतक (*pe && *pe != ARG_SEP && 
					i < माप(driver_setup.tag_ctrl)-1) अणु
					driver_setup.tag_ctrl[i++] = *pe++;
				पूर्ण
				driver_setup.tag_ctrl[i] = '\0';
			पूर्ण
			अवरोध;
		हाल OPT_MASTER_PARITY:
			driver_setup.master_parity = val;
			अवरोध;
		हाल OPT_SCSI_PARITY:
			driver_setup.scsi_parity = val;
			अवरोध;
		हाल OPT_DISCONNECTION:
			driver_setup.disconnection = val;
			अवरोध;
		हाल OPT_SPECIAL_FEATURES:
			driver_setup.special_features = val;
			अवरोध;
		हाल OPT_FORCE_SYNC_NEGO:
			driver_setup.क्रमce_sync_nego = val;
			अवरोध;
		हाल OPT_REVERSE_PROBE:
			driver_setup.reverse_probe = val;
			अवरोध;
		हाल OPT_DEFAULT_SYNC:
			driver_setup.शेष_sync = val;
			अवरोध;
		हाल OPT_VERBOSE:
			driver_setup.verbose = val;
			अवरोध;
		हाल OPT_DEBUG:
			driver_setup.debug = val;
			अवरोध;
		हाल OPT_BURST_MAX:
			driver_setup.burst_max = val;
			अवरोध;
		हाल OPT_LED_PIN:
			driver_setup.led_pin = val;
			अवरोध;
		हाल OPT_MAX_WIDE:
			driver_setup.max_wide = val? 1:0;
			अवरोध;
		हाल OPT_SETTLE_DELAY:
			driver_setup.settle_delay = val;
			अवरोध;
		हाल OPT_DIFF_SUPPORT:
			driver_setup.dअगरf_support = val;
			अवरोध;
		हाल OPT_IRQM:
			driver_setup.irqm = val;
			अवरोध;
		हाल OPT_PCI_FIX_UP:
			driver_setup.pci_fix_up	= val;
			अवरोध;
		हाल OPT_BUS_CHECK:
			driver_setup.bus_check = val;
			अवरोध;
		हाल OPT_OPTIMIZE:
			driver_setup.optimize = val;
			अवरोध;
		हाल OPT_RECOVERY:
			driver_setup.recovery = val;
			अवरोध;
		हाल OPT_USE_NVRAM:
			driver_setup.use_nvram = val;
			अवरोध;
		हाल OPT_SAFE_SETUP:
			स_नकल(&driver_setup, &driver_safe_setup,
				माप(driver_setup));
			अवरोध;
		हाल OPT_EXCLUDE:
			अगर (xi < SCSI_NCR_MAX_EXCLUDES)
				driver_setup.excludes[xi++] = val;
			अवरोध;
		हाल OPT_HOST_ID:
			driver_setup.host_id = val;
			अवरोध;
#अगर_घोषित SCSI_NCR_IARB_SUPPORT
		हाल OPT_IARB:
			driver_setup.iarb = val;
			अवरोध;
#पूर्ण_अगर
		शेष:
			prपूर्णांकk("sym53c8xx_setup: unexpected boot option '%.*s' ignored\n", (पूर्णांक)(pc-cur+1), cur);
			अवरोध;
		पूर्ण

		अगर ((cur = म_अक्षर(cur, ARG_SEP)) != शून्य)
			++cur;
	पूर्ण
#पूर्ण_अगर /* SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT */
	वापस 1;
पूर्ण
#पूर्ण_अगर /* !MODULE */

/*===================================================================
**
**	Get device queue depth from boot command line.
**
**===================================================================
*/
#घोषणा DEF_DEPTH	(driver_setup.शेष_tags)
#घोषणा ALL_TARGETS	-2
#घोषणा NO_TARGET	-1
#घोषणा ALL_LUNS	-2
#घोषणा NO_LUN		-1

अटल पूर्णांक device_queue_depth(पूर्णांक unit, पूर्णांक target, पूर्णांक lun)
अणु
	पूर्णांक c, h, t, u, v;
	अक्षर *p = driver_setup.tag_ctrl;
	अक्षर *ep;

	h = -1;
	t = NO_TARGET;
	u = NO_LUN;
	जबतक ((c = *p++) != 0) अणु
		v = simple_म_से_अदीर्घ(p, &ep, 0);
		चयन(c) अणु
		हाल '/':
			++h;
			t = ALL_TARGETS;
			u = ALL_LUNS;
			अवरोध;
		हाल 't':
			अगर (t != target)
				t = (target == v) ? v : NO_TARGET;
			u = ALL_LUNS;
			अवरोध;
		हाल 'u':
			अगर (u != lun)
				u = (lun == v) ? v : NO_LUN;
			अवरोध;
		हाल 'q':
			अगर (h == unit &&
				(t == ALL_TARGETS || t == target) &&
				(u == ALL_LUNS    || u == lun))
				वापस v;
			अवरोध;
		हाल '-':
			t = ALL_TARGETS;
			u = ALL_LUNS;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		p = ep;
	पूर्ण
	वापस DEF_DEPTH;
पूर्ण


/*==========================================================
**
**	The CCB करोne queue uses an array of CCB भव 
**	addresses. Empty entries are flagged using the bogus 
**	भव address 0xffffffff.
**
**	Since PCI ensures that only aligned DWORDs are accessed 
**	atomically, 64 bit little-endian architecture requires 
**	to test the high order DWORD of the entry to determine 
**	अगर it is empty or valid.
**
**	BTW, I will make things dअगरferently as soon as I will 
**	have a better idea, but this is simple and should work.
**
**==========================================================
*/
 
#घोषणा SCSI_NCR_CCB_DONE_SUPPORT
#अगर_घोषित  SCSI_NCR_CCB_DONE_SUPPORT

#घोषणा MAX_DONE 24
#घोषणा CCB_DONE_EMPTY 0xffffffffUL

/* All 32 bit architectures */
#अगर BITS_PER_LONG == 32
#घोषणा CCB_DONE_VALID(cp)  (((u_दीर्घ) cp) != CCB_DONE_EMPTY)

/* All > 32 bit (64 bit) architectures regardless endian-ness */
#अन्यथा
#घोषणा CCB_DONE_VALID(cp)  \
	((((u_दीर्घ) cp) & 0xffffffff00000000ul) && 	\
	 (((u_दीर्घ) cp) & 0xfffffffful) != CCB_DONE_EMPTY)
#पूर्ण_अगर

#पूर्ण_अगर /* SCSI_NCR_CCB_DONE_SUPPORT */

/*==========================================================
**
**	Configuration and Debugging
**
**==========================================================
*/

/*
**    SCSI address of this device.
**    The boot routines should have set it.
**    If not, use this.
*/

#अगर_अघोषित SCSI_NCR_MYADDR
#घोषणा SCSI_NCR_MYADDR      (7)
#पूर्ण_अगर

/*
**    The maximum number of tags per logic unit.
**    Used only क्रम disk devices that support tags.
*/

#अगर_अघोषित SCSI_NCR_MAX_TAGS
#घोषणा SCSI_NCR_MAX_TAGS    (8)
#पूर्ण_अगर

/*
**    TAGS are actually limited to 64 tags/lun.
**    We need to deal with घातer of 2, क्रम alignment स्थिरraपूर्णांकs.
*/
#अगर	SCSI_NCR_MAX_TAGS > 64
#घोषणा	MAX_TAGS (64)
#अन्यथा
#घोषणा	MAX_TAGS SCSI_NCR_MAX_TAGS
#पूर्ण_अगर

#घोषणा NO_TAG	(255)

/*
**	Choose appropriate type क्रम tag biपंचांगap.
*/
#अगर	MAX_TAGS > 32
प्रकार u64 tagmap_t;
#अन्यथा
प्रकार u32 tagmap_t;
#पूर्ण_अगर

/*
**    Number of tarमाला_लो supported by the driver.
**    n permits target numbers 0..n-1.
**    Default is 16, meaning tarमाला_लो #0..#15.
**    #7 .. is myself.
*/

#अगर_घोषित SCSI_NCR_MAX_TARGET
#घोषणा MAX_TARGET  (SCSI_NCR_MAX_TARGET)
#अन्यथा
#घोषणा MAX_TARGET  (16)
#पूर्ण_अगर

/*
**    Number of logic units supported by the driver.
**    n enables logic unit numbers 0..n-1.
**    The common SCSI devices require only
**    one lun, so take 1 as the शेष.
*/

#अगर_घोषित SCSI_NCR_MAX_LUN
#घोषणा MAX_LUN    SCSI_NCR_MAX_LUN
#अन्यथा
#घोषणा MAX_LUN    (1)
#पूर्ण_अगर

/*
**    Asynchronous pre-scaler (ns). Shall be 40
*/
 
#अगर_अघोषित SCSI_NCR_MIN_ASYNC
#घोषणा SCSI_NCR_MIN_ASYNC (40)
#पूर्ण_अगर

/*
**    The maximum number of jobs scheduled क्रम starting.
**    There should be one slot per target, and one slot
**    क्रम each tag of each target in use.
**    The calculation below is actually quite silly ...
*/

#अगर_घोषित SCSI_NCR_CAN_QUEUE
#घोषणा MAX_START   (SCSI_NCR_CAN_QUEUE + 4)
#अन्यथा
#घोषणा MAX_START   (MAX_TARGET + 7 * MAX_TAGS)
#पूर्ण_अगर

/*
**   We limit the max number of pending IO to 250.
**   since we करोnnot want to allocate more than 1 
**   PAGE क्रम 'scripth'.
*/
#अगर	MAX_START > 250
#अघोषित	MAX_START
#घोषणा	MAX_START 250
#पूर्ण_अगर

/*
**    The maximum number of segments a transfer is split पूर्णांकo.
**    We support up to 127 segments क्रम both पढ़ो and ग_लिखो.
**    The data scripts are broken पूर्णांकo 2 sub-scripts.
**    80 (MAX_SCATTERL) segments are moved from a sub-script
**    in on-chip RAM. This makes data transfers लघुer than 
**    80k (assuming 1k fs) as fast as possible.
*/

#घोषणा MAX_SCATTER (SCSI_NCR_MAX_SCATTER)

#अगर (MAX_SCATTER > 80)
#घोषणा MAX_SCATTERL	80
#घोषणा	MAX_SCATTERH	(MAX_SCATTER - MAX_SCATTERL)
#अन्यथा
#घोषणा MAX_SCATTERL	(MAX_SCATTER-1)
#घोषणा	MAX_SCATTERH	1
#पूर्ण_अगर

/*
**	other
*/

#घोषणा NCR_SNOOP_TIMEOUT (1000000)

/*
**	Other definitions
*/

#घोषणा initverbose (driver_setup.verbose)
#घोषणा bootverbose (np->verbose)

/*==========================================================
**
**	Command control block states.
**
**==========================================================
*/

#घोषणा HS_IDLE		(0)
#घोषणा HS_BUSY		(1)
#घोषणा HS_NEGOTIATE	(2)	/* sync/wide data transfer*/
#घोषणा HS_DISCONNECT	(3)	/* Disconnected by target */

#घोषणा HS_DONEMASK	(0x80)
#घोषणा HS_COMPLETE	(4|HS_DONEMASK)
#घोषणा HS_SEL_TIMEOUT	(5|HS_DONEMASK)	/* Selection समयout      */
#घोषणा HS_RESET	(6|HS_DONEMASK)	/* SCSI reset	          */
#घोषणा HS_ABORTED	(7|HS_DONEMASK)	/* Transfer पातed       */
#घोषणा HS_TIMEOUT	(8|HS_DONEMASK)	/* Software समयout       */
#घोषणा HS_FAIL		(9|HS_DONEMASK)	/* SCSI or PCI bus errors */
#घोषणा HS_UNEXPECTED	(10|HS_DONEMASK)/* Unexpected disconnect  */

/*
**	Invalid host status values used by the SCRIPTS processor 
**	when the nexus is not fully identअगरied.
**	Shall never appear in a CCB.
*/

#घोषणा HS_INVALMASK	(0x40)
#घोषणा	HS_SELECTING	(0|HS_INVALMASK)
#घोषणा	HS_IN_RESELECT	(1|HS_INVALMASK)
#घोषणा	HS_STARTING	(2|HS_INVALMASK)

/*
**	Flags set by the SCRIPT processor क्रम commands 
**	that have been skipped.
*/
#घोषणा HS_SKIPMASK	(0x20)

/*==========================================================
**
**	Software Interrupt Codes
**
**==========================================================
*/

#घोषणा	SIR_BAD_STATUS		(1)
#घोषणा	SIR_XXXXXXXXXX		(2)
#घोषणा	SIR_NEGO_SYNC		(3)
#घोषणा	SIR_NEGO_WIDE		(4)
#घोषणा	SIR_NEGO_FAILED		(5)
#घोषणा	SIR_NEGO_PROTO		(6)
#घोषणा	SIR_REJECT_RECEIVED	(7)
#घोषणा	SIR_REJECT_SENT		(8)
#घोषणा	SIR_IGN_RESIDUE		(9)
#घोषणा	SIR_MISSING_SAVE	(10)
#घोषणा	SIR_RESEL_NO_MSG_IN	(11)
#घोषणा	SIR_RESEL_NO_IDENTIFY	(12)
#घोषणा	SIR_RESEL_BAD_LUN	(13)
#घोषणा	SIR_RESEL_BAD_TARGET	(14)
#घोषणा	SIR_RESEL_BAD_I_T_L	(15)
#घोषणा	SIR_RESEL_BAD_I_T_L_Q	(16)
#घोषणा	SIR_DONE_OVERFLOW	(17)
#घोषणा	SIR_INTFLY		(18)
#घोषणा	SIR_MAX			(18)

/*==========================================================
**
**	Extended error codes.
**	xerr_status field of काष्ठा ccb.
**
**==========================================================
*/

#घोषणा	XE_OK		(0)
#घोषणा	XE_EXTRA_DATA	(1)	/* unexpected data phase */
#घोषणा	XE_BAD_PHASE	(2)	/* illegal phase (4/5)   */

/*==========================================================
**
**	Negotiation status.
**	nego_status field	of काष्ठा ccb.
**
**==========================================================
*/

#घोषणा NS_NOCHANGE	(0)
#घोषणा NS_SYNC		(1)
#घोषणा NS_WIDE		(2)
#घोषणा NS_PPR		(4)

/*==========================================================
**
**	Misc.
**
**==========================================================
*/

#घोषणा CCB_MAGIC	(0xf2691ad2)

/*==========================================================
**
**	Declaration of काष्ठाs.
**
**==========================================================
*/

अटल काष्ठा scsi_transport_ढाँचा *ncr53c8xx_transport_ढाँचा = शून्य;

काष्ठा tcb;
काष्ठा lcb;
काष्ठा ccb;
काष्ठा ncb;
काष्ठा script;

काष्ठा link अणु
	ncrcmd	l_cmd;
	ncrcmd	l_paddr;
पूर्ण;

काष्ठा	usrcmd अणु
	u_दीर्घ	target;
	u_दीर्घ	lun;
	u_दीर्घ	data;
	u_दीर्घ	cmd;
पूर्ण;

#घोषणा UC_SETSYNC      10
#घोषणा UC_SETTAGS	11
#घोषणा UC_SETDEBUG	12
#घोषणा UC_SETORDER	13
#घोषणा UC_SETWIDE	14
#घोषणा UC_SETFLAG	15
#घोषणा UC_SETVERBOSE	17

#घोषणा	UF_TRACE	(0x01)
#घोषणा	UF_NODISC	(0x02)
#घोषणा	UF_NOSCAN	(0x04)

/*========================================================================
**
**	Declaration of काष्ठाs:		target control block
**
**========================================================================
*/
काष्ठा tcb अणु
	/*----------------------------------------------------------------
	**	During reselection the ncr jumps to this poपूर्णांक with SFBR 
	**	set to the encoded target number with bit 7 set.
	**	अगर it's not this target, jump to the next.
	**
	**	JUMP  IF (SFBR != #target#), @(next tcb)
	**----------------------------------------------------------------
	*/
	काष्ठा link   jump_tcb;

	/*----------------------------------------------------------------
	**	Load the actual values क्रम the sxfer and the scntl3
	**	रेजिस्टर (sync/wide mode).
	**
	**	SCR_COPY (1), @(sval field of this tcb), @(sxfer  रेजिस्टर)
	**	SCR_COPY (1), @(wval field of this tcb), @(scntl3 रेजिस्टर)
	**----------------------------------------------------------------
	*/
	ncrcmd	माला_लोcr[6];

	/*----------------------------------------------------------------
	**	Get the IDENTIFY message and load the LUN to SFBR.
	**
	**	CALL, <RESEL_LUN>
	**----------------------------------------------------------------
	*/
	काष्ठा link   call_lun;

	/*----------------------------------------------------------------
	**	Now look क्रम the right lun.
	**
	**	For i = 0 to 3
	**		SCR_JUMP ^ IFTRUE(MASK(i, 3)), @(first lcb mod. i)
	**
	**	Recent chips will prefetch the 4 JUMPS using only 1 burst.
	**	It is kind of hashcoding.
	**----------------------------------------------------------------
	*/
	काष्ठा link     jump_lcb[4];	/* JUMPs क्रम reselection	*/
	काष्ठा lcb *	lp[MAX_LUN];	/* The lcb's of this tcb	*/

	/*----------------------------------------------------------------
	**	Poपूर्णांकer to the ccb used क्रम negotiation.
	**	Prevent from starting a negotiation क्रम all queued commands 
	**	when tagged command queuing is enabled.
	**----------------------------------------------------------------
	*/
	काष्ठा ccb *   nego_cp;

	/*----------------------------------------------------------------
	**	statistical data
	**----------------------------------------------------------------
	*/
	u_दीर्घ	transfers;
	u_दीर्घ	bytes;

	/*----------------------------------------------------------------
	**	negotiation of wide and synch transfer and device quirks.
	**----------------------------------------------------------------
	*/
#अगर_घोषित SCSI_NCR_BIG_ENDIAN
/*0*/	u16	period;
/*2*/	u_अक्षर	sval;
/*3*/	u_अक्षर	minsync;
/*0*/	u_अक्षर	wval;
/*1*/	u_अक्षर	wideकरोne;
/*2*/	u_अक्षर	quirks;
/*3*/	u_अक्षर	maxoffs;
#अन्यथा
/*0*/	u_अक्षर	minsync;
/*1*/	u_अक्षर	sval;
/*2*/	u16	period;
/*0*/	u_अक्षर	maxoffs;
/*1*/	u_अक्षर	quirks;
/*2*/	u_अक्षर	wideकरोne;
/*3*/	u_अक्षर	wval;
#पूर्ण_अगर

	/* User settable limits and options.  */
	u_अक्षर	usrsync;
	u_अक्षर	usrwide;
	u_अक्षर	usrtags;
	u_अक्षर	usrflag;
	काष्ठा scsi_target *starget;
पूर्ण;

/*========================================================================
**
**	Declaration of काष्ठाs:		lun control block
**
**========================================================================
*/
काष्ठा lcb अणु
	/*----------------------------------------------------------------
	**	During reselection the ncr jumps to this poपूर्णांक
	**	with SFBR set to the "Identify" message.
	**	अगर it's not this lun, jump to the next.
	**
	**	JUMP  IF (SFBR != #lun#), @(next lcb of this target)
	**
	**	It is this lun. Load TEMP with the nexus jumps table 
	**	address and jump to RESEL_TAG (or RESEL_NOTAG).
	**
	**		SCR_COPY (4), p_jump_ccb, TEMP,
	**		SCR_JUMP, <RESEL_TAG>
	**----------------------------------------------------------------
	*/
	काष्ठा link	jump_lcb;
	ncrcmd		load_jump_ccb[3];
	काष्ठा link	jump_tag;
	ncrcmd		p_jump_ccb;	/* Jump table bus address	*/

	/*----------------------------------------------------------------
	**	Jump table used by the script processor to directly jump 
	**	to the CCB corresponding to the reselected nexus.
	**	Address is allocated on 256 bytes boundary in order to 
	**	allow 8 bit calculation of the tag jump entry क्रम up to 
	**	64 possible tags.
	**----------------------------------------------------------------
	*/
	u32		jump_ccb_0;	/* Default table अगर no tags	*/
	u32		*jump_ccb;	/* Virtual address		*/

	/*----------------------------------------------------------------
	**	CCB queue management.
	**----------------------------------------------------------------
	*/
	काष्ठा list_head मुक्त_ccbq;	/* Queue of available CCBs	*/
	काष्ठा list_head busy_ccbq;	/* Queue of busy CCBs		*/
	काष्ठा list_head रुको_ccbq;	/* Queue of रुकोing क्रम IO CCBs	*/
	काष्ठा list_head skip_ccbq;	/* Queue of skipped CCBs	*/
	u_अक्षर		actccbs;	/* Number of allocated CCBs	*/
	u_अक्षर		busyccbs;	/* CCBs busy क्रम this lun	*/
	u_अक्षर		queuedccbs;	/* CCBs queued to the controller*/
	u_अक्षर		queuedepth;	/* Queue depth क्रम this lun	*/
	u_अक्षर		scdev_depth;	/* SCSI device queue depth	*/
	u_अक्षर		maxnxs;		/* Max possible nexuses		*/

	/*----------------------------------------------------------------
	**	Control of tagged command queuing.
	**	Tags allocation is perक्रमmed using a circular buffer.
	**	This aव्योमs using a loop क्रम tag allocation.
	**----------------------------------------------------------------
	*/
	u_अक्षर		ia_tag;		/* Allocation index		*/
	u_अक्षर		अगर_tag;		/* Freeing index		*/
	u_अक्षर cb_tags[MAX_TAGS];	/* Circular tags buffer	*/
	u_अक्षर		usetags;	/* Command queuing is active	*/
	u_अक्षर		maxtags;	/* Max nr of tags asked by user	*/
	u_अक्षर		numtags;	/* Current number of tags	*/

	/*----------------------------------------------------------------
	**	QUEUE FULL control and ORDERED tag control.
	**----------------------------------------------------------------
	*/
	/*----------------------------------------------------------------
	**	QUEUE FULL and ORDERED tag control.
	**----------------------------------------------------------------
	*/
	u16		num_good;	/* Nr of GOOD since QUEUE FULL	*/
	tagmap_t	tags_umap;	/* Used tags biपंचांगap		*/
	tagmap_t	tags_smap;	/* Tags in use at 'tag_stime'	*/
	u_दीर्घ		tags_sसमय;	/* Last समय we set smap=umap	*/
	काष्ठा ccb *	held_ccb;	/* CCB held क्रम QUEUE FULL	*/
पूर्ण;

/*========================================================================
**
**      Declaration of काष्ठाs:     the launch script.
**
**========================================================================
**
**	It is part of the CCB and is called by the scripts processor to 
**	start or restart the data काष्ठाure (nexus).
**	This 6 DWORDs mini script makes use of prefetching.
**
**------------------------------------------------------------------------
*/
काष्ठा launch अणु
	/*----------------------------------------------------------------
	**	SCR_COPY(4),	@(p_phys), @(dsa रेजिस्टर)
	**	SCR_JUMP,	@(scheduler_poपूर्णांक)
	**----------------------------------------------------------------
	*/
	ncrcmd		setup_dsa[3];	/* Copy 'phys' address to dsa	*/
	काष्ठा link	schedule;	/* Jump to scheduler poपूर्णांक	*/
	ncrcmd		p_phys;		/* 'phys' header bus address	*/
पूर्ण;

/*========================================================================
**
**      Declaration of काष्ठाs:     global HEADER.
**
**========================================================================
**
**	This subकाष्ठाure is copied from the ccb to a global address after 
**	selection (or reselection) and copied back beक्रमe disconnect.
**
**	These fields are accessible to the script processor.
**
**------------------------------------------------------------------------
*/

काष्ठा head अणु
	/*----------------------------------------------------------------
	**	Saved data poपूर्णांकer.
	**	Poपूर्णांकs to the position in the script responsible क्रम the
	**	actual transfer transfer of data.
	**	It's written after reception of a SAVE_DATA_POINTER message.
	**	The goalpoपूर्णांकer poपूर्णांकs after the last transfer command.
	**----------------------------------------------------------------
	*/
	u32		savep;
	u32		lastp;
	u32		goalp;

	/*----------------------------------------------------------------
	**	Alternate data poपूर्णांकer.
	**	They are copied back to savep/lastp/goalp by the SCRIPTS 
	**	when the direction is unknown and the device claims data out.
	**----------------------------------------------------------------
	*/
	u32		wlastp;
	u32		wgoalp;

	/*----------------------------------------------------------------
	**	The भव address of the ccb containing this header.
	**----------------------------------------------------------------
	*/
	काष्ठा ccb *	cp;

	/*----------------------------------------------------------------
	**	Status fields.
	**----------------------------------------------------------------
	*/
	u_अक्षर		scr_st[4];	/* script status		*/
	u_अक्षर		status[4];	/* host status. must be the 	*/
					/*  last DWORD of the header.	*/
पूर्ण;

/*
**	The status bytes are used by the host and the script processor.
**
**	The byte corresponding to the host_status must be stored in the 
**	last DWORD of the CCB header since it is used क्रम command 
**	completion (ncr_wakeup()). Doing so, we are sure that the header 
**	has been entirely copied back to the CCB when the host_status is 
**	seen complete by the CPU.
**
**	The last four bytes (status[4]) are copied to the scratchb रेजिस्टर
**	(declared as scr0..scr3 in ncr_reg.h) just after the select/reselect,
**	and copied back just after disconnecting.
**	Inside the script the XX_REG are used.
**
**	The first four bytes (scr_st[4]) are used inside the script by 
**	"COPY" commands.
**	Because source and destination must have the same alignment
**	in a DWORD, the fields HAVE to be at the chosen offsets.
**		xerr_st		0	(0x34)	scratcha
**		sync_st		1	(0x05)	sxfer
**		wide_st		3	(0x03)	scntl3
*/

/*
**	Last four bytes (script)
*/
#घोषणा  QU_REG	scr0
#घोषणा  HS_REG	scr1
#घोषणा  HS_PRT	nc_scr1
#घोषणा  SS_REG	scr2
#घोषणा  SS_PRT	nc_scr2
#घोषणा  PS_REG	scr3

/*
**	Last four bytes (host)
*/
#अगर_घोषित SCSI_NCR_BIG_ENDIAN
#घोषणा  actualquirks  phys.header.status[3]
#घोषणा  host_status   phys.header.status[2]
#घोषणा  scsi_status   phys.header.status[1]
#घोषणा  parity_status phys.header.status[0]
#अन्यथा
#घोषणा  actualquirks  phys.header.status[0]
#घोषणा  host_status   phys.header.status[1]
#घोषणा  scsi_status   phys.header.status[2]
#घोषणा  parity_status phys.header.status[3]
#पूर्ण_अगर

/*
**	First four bytes (script)
*/
#घोषणा  xerr_st       header.scr_st[0]
#घोषणा  sync_st       header.scr_st[1]
#घोषणा  nego_st       header.scr_st[2]
#घोषणा  wide_st       header.scr_st[3]

/*
**	First four bytes (host)
*/
#घोषणा  xerr_status   phys.xerr_st
#घोषणा  nego_status   phys.nego_st

#अगर 0
#घोषणा  sync_status   phys.sync_st
#घोषणा  wide_status   phys.wide_st
#पूर्ण_अगर

/*==========================================================
**
**      Declaration of काष्ठाs:     Data काष्ठाure block
**
**==========================================================
**
**	During execution of a ccb by the script processor,
**	the DSA (data काष्ठाure address) रेजिस्टर poपूर्णांकs
**	to this subकाष्ठाure of the ccb.
**	This subकाष्ठाure contains the header with
**	the script-processor-changeable data and
**	data blocks क्रम the indirect move commands.
**
**----------------------------------------------------------
*/

काष्ठा dsb अणु

	/*
	**	Header.
	*/

	काष्ठा head	header;

	/*
	**	Table data क्रम Script
	*/

	काष्ठा scr_tblsel  select;
	काष्ठा scr_tblmove smsg  ;
	काष्ठा scr_tblmove cmd   ;
	काष्ठा scr_tblmove sense ;
	काष्ठा scr_tblmove data[MAX_SCATTER];
पूर्ण;


/*========================================================================
**
**      Declaration of काष्ठाs:     Command control block.
**
**========================================================================
*/
काष्ठा ccb अणु
	/*----------------------------------------------------------------
	**	This is the data काष्ठाure which is poपूर्णांकed by the DSA 
	**	रेजिस्टर when it is executed by the script processor.
	**	It must be the first entry because it contains the header 
	**	as first entry that must be cache line aligned.
	**----------------------------------------------------------------
	*/
	काष्ठा dsb	phys;

	/*----------------------------------------------------------------
	**	Mini-script used at CCB execution start-up.
	**	Load the DSA with the data काष्ठाure address (phys) and 
	**	jump to SELECT. Jump to CANCEL अगर CCB is to be canceled.
	**----------------------------------------------------------------
	*/
	काष्ठा launch	start;

	/*----------------------------------------------------------------
	**	Mini-script used at CCB relection to restart the nexus.
	**	Load the DSA with the data काष्ठाure address (phys) and 
	**	jump to RESEL_DSA. Jump to ABORT अगर CCB is to be पातed.
	**----------------------------------------------------------------
	*/
	काष्ठा launch	restart;

	/*----------------------------------------------------------------
	**	If a data transfer phase is terminated too early
	**	(after reception of a message (i.e. DISCONNECT)),
	**	we have to prepare a mini script to transfer
	**	the rest of the data.
	**----------------------------------------------------------------
	*/
	ncrcmd		patch[8];

	/*----------------------------------------------------------------
	**	The general SCSI driver provides a
	**	poपूर्णांकer to a control block.
	**----------------------------------------------------------------
	*/
	काष्ठा scsi_cmnd	*cmd;		/* SCSI command 		*/
	u_अक्षर		cdb_buf[16];	/* Copy of CDB			*/
	u_अक्षर		sense_buf[64];
	पूर्णांक		data_len;	/* Total data length		*/

	/*----------------------------------------------------------------
	**	Message areas.
	**	We prepare a message to be sent after selection.
	**	We may use a second one अगर the command is rescheduled 
	**	due to GETCC or QFULL.
	**      Contents are IDENTIFY and SIMPLE_TAG.
	**	While negotiating sync or wide transfer,
	**	a SDTR or WDTR message is appended.
	**----------------------------------------------------------------
	*/
	u_अक्षर		scsi_smsg [8];
	u_अक्षर		scsi_smsg2[8];

	/*----------------------------------------------------------------
	**	Other fields.
	**----------------------------------------------------------------
	*/
	u_दीर्घ		p_ccb;		/* BUS address of this CCB	*/
	u_अक्षर		sensecmd[6];	/* Sense command		*/
	u_अक्षर		tag;		/* Tag क्रम this transfer	*/
					/*  255 means no tag		*/
	u_अक्षर		target;
	u_अक्षर		lun;
	u_अक्षर		queued;
	u_अक्षर		स्वतः_sense;
	काष्ठा ccb *	link_ccb;	/* Host adapter CCB chain	*/
	काष्ठा list_head link_ccbq;	/* Link to unit CCB queue	*/
	u32		startp;		/* Initial data poपूर्णांकer		*/
	u_दीर्घ		magic;		/* Free / busy  CCB flag	*/
पूर्ण;

#घोषणा CCB_PHYS(cp,lbl)	(cp->p_ccb + दुरत्व(काष्ठा ccb, lbl))


/*========================================================================
**
**      Declaration of काष्ठाs:     NCR device descriptor
**
**========================================================================
*/
काष्ठा ncb अणु
	/*----------------------------------------------------------------
	**	The global header.
	**	It is accessible to both the host and the script processor.
	**	Must be cache line size aligned (32 क्रम x86) in order to 
	**	allow cache line bursting when it is copied to/from CCB.
	**----------------------------------------------------------------
	*/
	काष्ठा head     header;

	/*----------------------------------------------------------------
	**	CCBs management queues.
	**----------------------------------------------------------------
	*/
	काष्ठा scsi_cmnd	*रुकोing_list;	/* Commands रुकोing क्रम a CCB	*/
					/*  when lcb is not allocated.	*/
	काष्ठा scsi_cmnd	*करोne_list;	/* Commands रुकोing क्रम करोne()  */
					/* callback to be invoked.      */ 
	spinlock_t	smp_lock;	/* Lock क्रम SMP thपढ़ोing       */

	/*----------------------------------------------------------------
	**	Chip and controller identअगरication.
	**----------------------------------------------------------------
	*/
	पूर्णांक		unit;		/* Unit number			*/
	अक्षर		inst_name[16];	/* ncb instance name		*/

	/*----------------------------------------------------------------
	**	Initial value of some IO रेजिस्टर bits.
	**	These values are assumed to have been set by BIOS, and may 
	**	be used क्रम probing adapter implementation dअगरferences.
	**----------------------------------------------------------------
	*/
	u_अक्षर	sv_scntl0, sv_scntl3, sv_dmode, sv_dcntl, sv_ctest0, sv_ctest3,
		sv_ctest4, sv_ctest5, sv_gpcntl, sv_stest2, sv_stest4;

	/*----------------------------------------------------------------
	**	Actual initial value of IO रेजिस्टर bits used by the 
	**	driver. They are loaded at initialisation according to  
	**	features that are to be enabled.
	**----------------------------------------------------------------
	*/
	u_अक्षर	rv_scntl0, rv_scntl3, rv_dmode, rv_dcntl, rv_ctest0, rv_ctest3,
		rv_ctest4, rv_ctest5, rv_stest2;

	/*----------------------------------------------------------------
	**	Tarमाला_लो management.
	**	During reselection the ncr jumps to jump_tcb.
	**	The SFBR रेजिस्टर is loaded with the encoded target id.
	**	For i = 0 to 3
	**		SCR_JUMP ^ IFTRUE(MASK(i, 3)), @(next tcb mod. i)
	**
	**	Recent chips will prefetch the 4 JUMPS using only 1 burst.
	**	It is kind of hashcoding.
	**----------------------------------------------------------------
	*/
	काष्ठा link     jump_tcb[4];	/* JUMPs क्रम reselection	*/
	काष्ठा tcb  target[MAX_TARGET];	/* Target data			*/

	/*----------------------------------------------------------------
	**	Virtual and physical bus addresses of the chip.
	**----------------------------------------------------------------
	*/
	व्योम __iomem *vaddr;		/* Virtual and bus address of	*/
	अचिन्हित दीर्घ	paddr;		/*  chip's IO रेजिस्टरs.	*/
	अचिन्हित दीर्घ	paddr2;		/* On-chip RAM bus address.	*/
	अस्थिर			/* Poपूर्णांकer to अस्थिर क्रम 	*/
	काष्ठा ncr_reg	__iomem *reg;	/*  memory mapped IO.		*/

	/*----------------------------------------------------------------
	**	SCRIPTS भव and physical bus addresses.
	**	'script'  is loaded in the on-chip RAM अगर present.
	**	'scripth' stays in मुख्य memory.
	**----------------------------------------------------------------
	*/
	काष्ठा script	*script0;	/* Copies of script and scripth	*/
	काष्ठा scripth	*scripth0;	/*  relocated क्रम this ncb.	*/
	काष्ठा scripth	*scripth;	/* Actual scripth virt. address	*/
	u_दीर्घ		p_script;	/* Actual script and scripth	*/
	u_दीर्घ		p_scripth;	/*  bus addresses.		*/

	/*----------------------------------------------------------------
	**	General controller parameters and configuration.
	**----------------------------------------------------------------
	*/
	काष्ठा device	*dev;
	u_अक्षर		revision_id;	/* PCI device revision id	*/
	u32		irq;		/* IRQ level			*/
	u32		features;	/* Chip features map		*/
	u_अक्षर		myaddr;		/* SCSI id of the adapter	*/
	u_अक्षर		maxburst;	/* log base 2 of dwords burst	*/
	u_अक्षर		maxwide;	/* Maximum transfer width	*/
	u_अक्षर		minsync;	/* Minimum sync period factor	*/
	u_अक्षर		maxsync;	/* Maximum sync period factor	*/
	u_अक्षर		maxoffs;	/* Max scsi offset		*/
	u_अक्षर		multiplier;	/* Clock multiplier (1,2,4)	*/
	u_अक्षर		घड़ी_भागn;	/* Number of घड़ी भागisors	*/
	u_दीर्घ		घड़ी_khz;	/* SCSI घड़ी frequency in KHz	*/

	/*----------------------------------------------------------------
	**	Start queue management.
	**	It is filled up by the host processor and accessed by the 
	**	SCRIPTS processor in order to start SCSI commands.
	**----------------------------------------------------------------
	*/
	u16		squeueput;	/* Next मुक्त slot of the queue	*/
	u16		actccbs;	/* Number of allocated CCBs	*/
	u16		queuedccbs;	/* Number of CCBs in start queue*/
	u16		queuedepth;	/* Start queue depth		*/

	/*----------------------------------------------------------------
	**	Timeout handler.
	**----------------------------------------------------------------
	*/
	काष्ठा समयr_list समयr;	/* Timer handler link header	*/
	u_दीर्घ		lastसमय;
	u_दीर्घ		settle_समय;	/* Resetting the SCSI BUS	*/

	/*----------------------------------------------------------------
	**	Debugging and profiling.
	**----------------------------------------------------------------
	*/
	काष्ठा ncr_reg	regdump;	/* Register dump		*/
	u_दीर्घ		regसमय;	/* Time it has been करोne	*/

	/*----------------------------------------------------------------
	**	Miscellaneous buffers accessed by the scripts-processor.
	**	They shall be DWORD aligned, because they may be पढ़ो or 
	**	written with a SCR_COPY script command.
	**----------------------------------------------------------------
	*/
	u_अक्षर		msgout[8];	/* Buffer क्रम MESSAGE OUT 	*/
	u_अक्षर		msgin [8];	/* Buffer क्रम MESSAGE IN	*/
	u32		lasपंचांगsg;	/* Last SCSI message sent	*/
	u_अक्षर		scratch;	/* Scratch क्रम SCSI receive	*/

	/*----------------------------------------------------------------
	**	Miscellaneous configuration and status parameters.
	**----------------------------------------------------------------
	*/
	u_अक्षर		disc;		/* Disconnection allowed	*/
	u_अक्षर		scsi_mode;	/* Current SCSI BUS mode	*/
	u_अक्षर		order;		/* Tag order to use		*/
	u_अक्षर		verbose;	/* Verbosity क्रम this controller*/
	पूर्णांक		ncr_cache;	/* Used क्रम cache test at init.	*/
	u_दीर्घ		p_ncb;		/* BUS address of this NCB	*/

	/*----------------------------------------------------------------
	**	Command completion handling.
	**----------------------------------------------------------------
	*/
#अगर_घोषित SCSI_NCR_CCB_DONE_SUPPORT
	काष्ठा ccb	*(ccb_करोne[MAX_DONE]);
	पूर्णांक		ccb_करोne_ic;
#पूर्ण_अगर
	/*----------------------------------------------------------------
	**	Fields that should be हटाओd or changed.
	**----------------------------------------------------------------
	*/
	काष्ठा ccb	*ccb;		/* Global CCB			*/
	काष्ठा usrcmd	user;		/* Command from user		*/
	अस्थिर u_अक्षर	release_stage;	/* Synchronisation stage on release  */
पूर्ण;

#घोषणा NCB_SCRIPT_PHYS(np,lbl)	 (np->p_script  + दुरत्व (काष्ठा script, lbl))
#घोषणा NCB_SCRIPTH_PHYS(np,lbl) (np->p_scripth + दुरत्व (काष्ठा scripth,lbl))

/*==========================================================
**
**
**      Script क्रम NCR-Processor.
**
**	Use ncr_script_fill() to create the variable parts.
**	Use ncr_script_copy_and_bind() to make a copy and
**	bind to physical addresses.
**
**
**==========================================================
**
**	We have to know the offsets of all labels beक्रमe
**	we reach them (क्रम क्रमward jumps).
**	Thereक्रमe we declare a काष्ठा here.
**	If you make changes inside the script,
**	DONT FORGET TO CHANGE THE LENGTHS HERE!
**
**----------------------------------------------------------
*/

/*
**	For HP Zalon/53c720 प्रणालीs, the Zalon पूर्णांकerface
**	between CPU and 53c720 करोes prefetches, which causes
**	problems with self modअगरying scripts.  The problem
**	is overcome by calling a dummy subroutine after each
**	modअगरication, to क्रमce a refetch of the script on
**	वापस from the subroutine.
*/

#अगर_घोषित CONFIG_NCR53C8XX_PREFETCH
#घोषणा PREFETCH_FLUSH_CNT	2
#घोषणा PREFETCH_FLUSH		SCR_CALL, PADDRH (रुको_dma),
#अन्यथा
#घोषणा PREFETCH_FLUSH_CNT	0
#घोषणा PREFETCH_FLUSH
#पूर्ण_अगर

/*
**	Script fragments which are loaded पूर्णांकo the on-chip RAM 
**	of 825A, 875 and 895 chips.
*/
काष्ठा script अणु
	ncrcmd	start		[  5];
	ncrcmd  startpos	[  1];
	ncrcmd	select		[  6];
	ncrcmd	select2		[  9 + PREFETCH_FLUSH_CNT];
	ncrcmd	loadpos		[  4];
	ncrcmd	send_ident	[  9];
	ncrcmd	prepare		[  6];
	ncrcmd	prepare2	[  7];
	ncrcmd  command		[  6];
	ncrcmd  dispatch	[ 32];
	ncrcmd  clrack		[  4];
	ncrcmd	no_data		[ 17];
	ncrcmd  status		[  8];
	ncrcmd  msg_in		[  2];
	ncrcmd  msg_in2		[ 16];
	ncrcmd  msg_bad		[  4];
	ncrcmd	seपंचांगsg		[  7];
	ncrcmd	cleanup		[  6];
	ncrcmd  complete	[  9];
	ncrcmd	cleanup_ok	[  8 + PREFETCH_FLUSH_CNT];
	ncrcmd	cleanup0	[  1];
#अगर_अघोषित SCSI_NCR_CCB_DONE_SUPPORT
	ncrcmd	संकेत		[ 12];
#अन्यथा
	ncrcmd	संकेत		[  9];
	ncrcmd	करोne_pos	[  1];
	ncrcmd	करोne_plug	[  2];
	ncrcmd	करोne_end	[  7];
#पूर्ण_अगर
	ncrcmd  save_dp		[  7];
	ncrcmd  restore_dp	[  5];
	ncrcmd  disconnect	[ 10];
	ncrcmd	msg_out		[  9];
	ncrcmd	msg_out_करोne	[  7];
	ncrcmd  idle		[  2];
	ncrcmd	reselect	[  8];
	ncrcmd	reselected	[  8];
	ncrcmd	resel_dsa	[  6 + PREFETCH_FLUSH_CNT];
	ncrcmd	loadpos1	[  4];
	ncrcmd  resel_lun	[  6];
	ncrcmd	resel_tag	[  6];
	ncrcmd	jump_to_nexus	[  4 + PREFETCH_FLUSH_CNT];
	ncrcmd	nexus_indirect	[  4];
	ncrcmd	resel_notag	[  4];
	ncrcmd  data_in		[MAX_SCATTERL * 4];
	ncrcmd  data_in2	[  4];
	ncrcmd  data_out	[MAX_SCATTERL * 4];
	ncrcmd  data_out2	[  4];
पूर्ण;

/*
**	Script fragments which stay in मुख्य memory क्रम all chips.
*/
काष्ठा scripth अणु
	ncrcmd  tryloop		[MAX_START*2];
	ncrcmd  tryloop2	[  2];
#अगर_घोषित SCSI_NCR_CCB_DONE_SUPPORT
	ncrcmd  करोne_queue	[MAX_DONE*5];
	ncrcmd  करोne_queue2	[  2];
#पूर्ण_अगर
	ncrcmd	select_no_atn	[  8];
	ncrcmd	cancel		[  4];
	ncrcmd	skip		[  9 + PREFETCH_FLUSH_CNT];
	ncrcmd	skip2		[ 19];
	ncrcmd	par_err_data_in	[  6];
	ncrcmd	par_err_other	[  4];
	ncrcmd	msg_reject	[  8];
	ncrcmd	msg_ign_residue	[ 24];
	ncrcmd  msg_extended	[ 10];
	ncrcmd  msg_ext_2	[ 10];
	ncrcmd	msg_wdtr	[ 14];
	ncrcmd	send_wdtr	[  7];
	ncrcmd  msg_ext_3	[ 10];
	ncrcmd	msg_sdtr	[ 14];
	ncrcmd	send_sdtr	[  7];
	ncrcmd	nego_bad_phase	[  4];
	ncrcmd	msg_out_पात	[ 10];
	ncrcmd  hdata_in	[MAX_SCATTERH * 4];
	ncrcmd  hdata_in2	[  2];
	ncrcmd  hdata_out	[MAX_SCATTERH * 4];
	ncrcmd  hdata_out2	[  2];
	ncrcmd	reset		[  4];
	ncrcmd	पातtag	[  4];
	ncrcmd	पात		[  2];
	ncrcmd	पात_resel	[ 20];
	ncrcmd	resend_ident	[  4];
	ncrcmd	clratn_go_on	[  3];
	ncrcmd	nxtdsp_go_on	[  1];
	ncrcmd	sdata_in	[  8];
	ncrcmd  data_io		[ 18];
	ncrcmd	bad_identअगरy	[ 12];
	ncrcmd	bad_i_t_l	[  4];
	ncrcmd	bad_i_t_l_q	[  4];
	ncrcmd	bad_target	[  8];
	ncrcmd	bad_status	[  8];
	ncrcmd	start_ram	[  4 + PREFETCH_FLUSH_CNT];
	ncrcmd	start_ram0	[  4];
	ncrcmd	sto_restart	[  5];
	ncrcmd	रुको_dma	[  2];
	ncrcmd	snooptest	[  9];
	ncrcmd	snoखोलोd	[  2];
पूर्ण;

/*==========================================================
**
**
**      Function headers.
**
**
**==========================================================
*/

अटल	व्योम	ncr_alloc_ccb	(काष्ठा ncb *np, u_अक्षर tn, u_अक्षर ln);
अटल	व्योम	ncr_complete	(काष्ठा ncb *np, काष्ठा ccb *cp);
अटल	व्योम	ncr_exception	(काष्ठा ncb *np);
अटल	व्योम	ncr_मुक्त_ccb	(काष्ठा ncb *np, काष्ठा ccb *cp);
अटल	व्योम	ncr_init_ccb	(काष्ठा ncb *np, काष्ठा ccb *cp);
अटल	व्योम	ncr_init_tcb	(काष्ठा ncb *np, u_अक्षर tn);
अटल	काष्ठा lcb *	ncr_alloc_lcb	(काष्ठा ncb *np, u_अक्षर tn, u_अक्षर ln);
अटल	काष्ठा lcb *	ncr_setup_lcb	(काष्ठा ncb *np, काष्ठा scsi_device *sdev);
अटल	व्योम	ncr_अ_लोlock	(काष्ठा ncb *np, पूर्णांक mult);
अटल	व्योम	ncr_selectघड़ी	(काष्ठा ncb *np, u_अक्षर scntl3);
अटल	काष्ठा ccb *ncr_get_ccb	(काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd);
अटल	व्योम	ncr_chip_reset	(काष्ठा ncb *np, पूर्णांक delay);
अटल	व्योम	ncr_init	(काष्ठा ncb *np, पूर्णांक reset, अक्षर * msg, u_दीर्घ code);
अटल	पूर्णांक	ncr_पूर्णांक_sbmc	(काष्ठा ncb *np);
अटल	पूर्णांक	ncr_पूर्णांक_par	(काष्ठा ncb *np);
अटल	व्योम	ncr_पूर्णांक_ma	(काष्ठा ncb *np);
अटल	व्योम	ncr_पूर्णांक_sir	(काष्ठा ncb *np);
अटल  व्योम    ncr_पूर्णांक_sto     (काष्ठा ncb *np);
अटल	व्योम	ncr_negotiate	(काष्ठा ncb* np, काष्ठा tcb* tp);
अटल	पूर्णांक	ncr_prepare_nego(काष्ठा ncb *np, काष्ठा ccb *cp, u_अक्षर *msgptr);

अटल	व्योम	ncr_script_copy_and_bind
				(काष्ठा ncb *np, ncrcmd *src, ncrcmd *dst, पूर्णांक len);
अटल  व्योम    ncr_script_fill (काष्ठा script * scr, काष्ठा scripth * scripth);
अटल	पूर्णांक	ncr_scatter	(काष्ठा ncb *np, काष्ठा ccb *cp, काष्ठा scsi_cmnd *cmd);
अटल	व्योम	ncr_माला_लोync	(काष्ठा ncb *np, u_अक्षर sfac, u_अक्षर *fakp, u_अक्षर *scntl3p);
अटल	व्योम	ncr_setsync	(काष्ठा ncb *np, काष्ठा ccb *cp, u_अक्षर scntl3, u_अक्षर sxfer);
अटल	व्योम	ncr_setup_tags	(काष्ठा ncb *np, काष्ठा scsi_device *sdev);
अटल	व्योम	ncr_setwide	(काष्ठा ncb *np, काष्ठा ccb *cp, u_अक्षर wide, u_अक्षर ack);
अटल	पूर्णांक	ncr_snooptest	(काष्ठा ncb *np);
अटल	व्योम	ncr_समयout	(काष्ठा ncb *np);
अटल  व्योम    ncr_wakeup      (काष्ठा ncb *np, u_दीर्घ code);
अटल  व्योम    ncr_wakeup_करोne (काष्ठा ncb *np);
अटल	व्योम	ncr_start_next_ccb (काष्ठा ncb *np, काष्ठा lcb * lp, पूर्णांक maxn);
अटल	व्योम	ncr_put_start_queue(काष्ठा ncb *np, काष्ठा ccb *cp);

अटल व्योम insert_पूर्णांकo_रुकोing_list(काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd);
अटल काष्ठा scsi_cmnd *retrieve_from_रुकोing_list(पूर्णांक to_हटाओ, काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd);
अटल व्योम process_रुकोing_list(काष्ठा ncb *np, पूर्णांक sts);

#घोषणा हटाओ_from_रुकोing_list(np, cmd) \
		retrieve_from_रुकोing_list(1, (np), (cmd))
#घोषणा requeue_रुकोing_list(np) process_रुकोing_list((np), DID_OK)
#घोषणा reset_रुकोing_list(np) process_रुकोing_list((np), DID_RESET)

अटल अंतरभूत अक्षर *ncr_name (काष्ठा ncb *np)
अणु
	वापस np->inst_name;
पूर्ण


/*==========================================================
**
**
**      Scripts क्रम NCR-Processor.
**
**      Use ncr_script_bind क्रम binding to physical addresses.
**
**
**==========================================================
**
**	NADDR generates a reference to a field of the controller data.
**	PADDR generates a reference to another part of the script.
**	RADDR generates a reference to a script processor रेजिस्टर.
**	FADDR generates a reference to a script processor रेजिस्टर
**		with offset.
**
**----------------------------------------------------------
*/

#घोषणा	RELOC_SOFTC	0x40000000
#घोषणा	RELOC_LABEL	0x50000000
#घोषणा	RELOC_REGISTER	0x60000000
#अगर 0
#घोषणा	RELOC_KVAR	0x70000000
#पूर्ण_अगर
#घोषणा	RELOC_LABELH	0x80000000
#घोषणा	RELOC_MASK	0xf0000000

#घोषणा	NADDR(label)	(RELOC_SOFTC | दुरत्व(काष्ठा ncb, label))
#घोषणा PADDR(label)    (RELOC_LABEL | दुरत्व(काष्ठा script, label))
#घोषणा PADDRH(label)   (RELOC_LABELH | दुरत्व(काष्ठा scripth, label))
#घोषणा	RADDR(label)	(RELOC_REGISTER | REG(label))
#घोषणा	FADDR(label,ofs)(RELOC_REGISTER | ((REG(label))+(ofs)))
#अगर 0
#घोषणा	KVAR(which)	(RELOC_KVAR | (which))
#पूर्ण_अगर

#अगर 0
#घोषणा	SCRIPT_KVAR_JIFFIES	(0)
#घोषणा	SCRIPT_KVAR_FIRST		SCRIPT_KVAR_JIFFIES
#घोषणा	SCRIPT_KVAR_LAST		SCRIPT_KVAR_JIFFIES
/*
 * Kernel variables referenced in the scripts.
 * THESE MUST ALL BE ALIGNED TO A 4-BYTE BOUNDARY.
 */
अटल व्योम *script_kvars[] __initdata =
	अणु (व्योम *)&jअगरfies पूर्ण;
#पूर्ण_अगर

अटल	काष्ठा script script0 __initdata = अणु
/*--------------------------< START >-----------------------*/ अणु
	/*
	**	This NOP will be patched with LED ON
	**	SCR_REG_REG (gpreg, SCR_AND, 0xfe)
	*/
	SCR_NO_OP,
		0,
	/*
	**      Clear SIGP.
	*/
	SCR_FROM_REG (ctest2),
		0,
	/*
	**	Then jump to a certain poपूर्णांक in tryloop.
	**	Due to the lack of indirect addressing the code
	**	is self modअगरying here.
	*/
	SCR_JUMP,
पूर्ण/*-------------------------< STARTPOS >--------------------*/,अणु
		PADDRH(tryloop),

पूर्ण/*-------------------------< SELECT >----------------------*/,अणु
	/*
	**	DSA	contains the address of a scheduled
	**		data काष्ठाure.
	**
	**	SCRATCHA contains the address of the script,
	**		which starts the next entry.
	**
	**	Set Initiator mode.
	**
	**	(Target mode is left as an exercise क्रम the पढ़ोer)
	*/

	SCR_CLR (SCR_TRG),
		0,
	SCR_LOAD_REG (HS_REG, HS_SELECTING),
		0,

	/*
	**      And try to select this target.
	*/
	SCR_SEL_TBL_ATN ^ दुरत्व (काष्ठा dsb, select),
		PADDR (reselect),

पूर्ण/*-------------------------< SELECT2 >----------------------*/,अणु
	/*
	**	Now there are 4 possibilities:
	**
	**	(1) The ncr loses arbitration.
	**	This is ok, because it will try again,
	**	when the bus becomes idle.
	**	(But beware of the समयout function!)
	**
	**	(2) The ncr is reselected.
	**	Then the script processor takes the jump
	**	to the RESELECT label.
	**
	**	(3) The ncr wins arbitration.
	**	Then it will execute SCRIPTS inकाष्ठाion until 
	**	the next inकाष्ठाion that checks SCSI phase.
	**	Then will stop and रुको क्रम selection to be 
	**	complete or selection समय-out to occur.
	**	As a result the SCRIPTS inकाष्ठाions until 
	**	LOADPOS + 2 should be executed in parallel with 
	**	the SCSI core perक्रमming selection.
	*/

	/*
	**	The MESSAGE_REJECT problem seems to be due to a selection 
	**	timing problem.
	**	Wait immediately क्रम the selection to complete. 
	**	(2.5x behaves so)
	*/
	SCR_JUMPR ^ IFFALSE (WHEN (SCR_MSG_OUT)),
		0,

	/*
	**	Next समय use the next slot.
	*/
	SCR_COPY (4),
		RADDR (temp),
		PADDR (startpos),
	/*
	**      The ncr करोesn't have an indirect load
	**	or store command. So we have to
	**	copy part of the control block to a
	**	fixed place, where we can access it.
	**
	**	We patch the address part of a
	**	COPY command with the DSA-रेजिस्टर.
	*/
	SCR_COPY_F (4),
		RADDR (dsa),
		PADDR (loadpos),
	/*
	**	Flush script prefetch अगर required
	*/
	PREFETCH_FLUSH
	/*
	**	then we करो the actual copy.
	*/
	SCR_COPY (माप (काष्ठा head)),
	/*
	**	जारीd after the next label ...
	*/
पूर्ण/*-------------------------< LOADPOS >---------------------*/,अणु
		0,
		NADDR (header),
	/*
	**	Wait क्रम the next phase or the selection
	**	to complete or समय-out.
	*/
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_OUT)),
		PADDR (prepare),

पूर्ण/*-------------------------< SEND_IDENT >----------------------*/,अणु
	/*
	**	Selection complete.
	**	Send the IDENTIFY and SIMPLE_TAG messages
	**	(and the EXTENDED_SDTR message)
	*/
	SCR_MOVE_TBL ^ SCR_MSG_OUT,
		दुरत्व (काष्ठा dsb, smsg),
	SCR_JUMP ^ IFTRUE (WHEN (SCR_MSG_OUT)),
		PADDRH (resend_ident),
	SCR_LOAD_REG (scratcha, 0x80),
		0,
	SCR_COPY (1),
		RADDR (scratcha),
		NADDR (lasपंचांगsg),
पूर्ण/*-------------------------< PREPARE >----------------------*/,अणु
	/*
	**      load the savep (saved poपूर्णांकer) पूर्णांकo
	**      the TEMP रेजिस्टर (actual poपूर्णांकer)
	*/
	SCR_COPY (4),
		NADDR (header.savep),
		RADDR (temp),
	/*
	**      Initialize the status रेजिस्टरs
	*/
	SCR_COPY (4),
		NADDR (header.status),
		RADDR (scr0),
पूर्ण/*-------------------------< PREPARE2 >---------------------*/,अणु
	/*
	**	Initialize the msgout buffer with a NOOP message.
	*/
	SCR_LOAD_REG (scratcha, NOP),
		0,
	SCR_COPY (1),
		RADDR (scratcha),
		NADDR (msgout),
#अगर 0
	SCR_COPY (1),
		RADDR (scratcha),
		NADDR (msgin),
#पूर्ण_अगर
	/*
	**	Anticipate the COMMAND phase.
	**	This is the normal हाल क्रम initial selection.
	*/
	SCR_JUMP ^ IFFALSE (WHEN (SCR_COMMAND)),
		PADDR (dispatch),

पूर्ण/*-------------------------< COMMAND >--------------------*/,अणु
	/*
	**	... and send the command
	*/
	SCR_MOVE_TBL ^ SCR_COMMAND,
		दुरत्व (काष्ठा dsb, cmd),
	/*
	**	If status is still HS_NEGOTIATE, negotiation failed.
	**	We check this here, since we want to करो that 
	**	only once.
	*/
	SCR_FROM_REG (HS_REG),
		0,
	SCR_INT ^ IFTRUE (DATA (HS_NEGOTIATE)),
		SIR_NEGO_FAILED,

पूर्ण/*-----------------------< DISPATCH >----------------------*/,अणु
	/*
	**	MSG_IN is the only phase that shall be 
	**	entered at least once क्रम each (re)selection.
	**	So we test it first.
	*/
	SCR_JUMP ^ IFTRUE (WHEN (SCR_MSG_IN)),
		PADDR (msg_in),

	SCR_RETURN ^ IFTRUE (IF (SCR_DATA_OUT)),
		0,
	/*
	**	DEL 397 - 53C875 Rev 3 - Part Number 609-0392410 - ITEM 4.
	**	Possible data corruption during Memory Write and Invalidate.
	**	This work-around resets the addressing logic prior to the 
	**	start of the first MOVE of a DATA IN phase.
	**	(See Documentation/scsi/ncr53c8xx.rst क्रम more inक्रमmation)
	*/
	SCR_JUMPR ^ IFFALSE (IF (SCR_DATA_IN)),
		20,
	SCR_COPY (4),
		RADDR (scratcha),
		RADDR (scratcha),
	SCR_RETURN,
 		0,
	SCR_JUMP ^ IFTRUE (IF (SCR_STATUS)),
		PADDR (status),
	SCR_JUMP ^ IFTRUE (IF (SCR_COMMAND)),
		PADDR (command),
	SCR_JUMP ^ IFTRUE (IF (SCR_MSG_OUT)),
		PADDR (msg_out),
	/*
	**      Discard one illegal phase byte, अगर required.
	*/
	SCR_LOAD_REG (scratcha, XE_BAD_PHASE),
		0,
	SCR_COPY (1),
		RADDR (scratcha),
		NADDR (xerr_st),
	SCR_JUMPR ^ IFFALSE (IF (SCR_ILG_OUT)),
		8,
	SCR_MOVE_ABS (1) ^ SCR_ILG_OUT,
		NADDR (scratch),
	SCR_JUMPR ^ IFFALSE (IF (SCR_ILG_IN)),
		8,
	SCR_MOVE_ABS (1) ^ SCR_ILG_IN,
		NADDR (scratch),
	SCR_JUMP,
		PADDR (dispatch),

पूर्ण/*-------------------------< CLRACK >----------------------*/,अणु
	/*
	**	Terminate possible pending message phase.
	*/
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP,
		PADDR (dispatch),

पूर्ण/*-------------------------< NO_DATA >--------------------*/,अणु
	/*
	**	The target wants to tranfer too much data
	**	or in the wrong direction.
	**      Remember that in extended error.
	*/
	SCR_LOAD_REG (scratcha, XE_EXTRA_DATA),
		0,
	SCR_COPY (1),
		RADDR (scratcha),
		NADDR (xerr_st),
	/*
	**      Discard one data byte, अगर required.
	*/
	SCR_JUMPR ^ IFFALSE (WHEN (SCR_DATA_OUT)),
		8,
	SCR_MOVE_ABS (1) ^ SCR_DATA_OUT,
		NADDR (scratch),
	SCR_JUMPR ^ IFFALSE (IF (SCR_DATA_IN)),
		8,
	SCR_MOVE_ABS (1) ^ SCR_DATA_IN,
		NADDR (scratch),
	/*
	**      .. and repeat as required.
	*/
	SCR_CALL,
		PADDR (dispatch),
	SCR_JUMP,
		PADDR (no_data),

पूर्ण/*-------------------------< STATUS >--------------------*/,अणु
	/*
	**	get the status
	*/
	SCR_MOVE_ABS (1) ^ SCR_STATUS,
		NADDR (scratch),
	/*
	**	save status to scsi_status.
	**	mark as complete.
	*/
	SCR_TO_REG (SS_REG),
		0,
	SCR_LOAD_REG (HS_REG, HS_COMPLETE),
		0,
	SCR_JUMP,
		PADDR (dispatch),
पूर्ण/*-------------------------< MSG_IN >--------------------*/,अणु
	/*
	**	Get the first byte of the message
	**	and save it to SCRATCHA.
	**
	**	The script processor करोesn't negate the
	**	ACK संकेत after this transfer.
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin[0]),
पूर्ण/*-------------------------< MSG_IN2 >--------------------*/,अणु
	/*
	**	Handle this message.
	*/
	SCR_JUMP ^ IFTRUE (DATA (COMMAND_COMPLETE)),
		PADDR (complete),
	SCR_JUMP ^ IFTRUE (DATA (DISCONNECT)),
		PADDR (disconnect),
	SCR_JUMP ^ IFTRUE (DATA (SAVE_POINTERS)),
		PADDR (save_dp),
	SCR_JUMP ^ IFTRUE (DATA (RESTORE_POINTERS)),
		PADDR (restore_dp),
	SCR_JUMP ^ IFTRUE (DATA (EXTENDED_MESSAGE)),
		PADDRH (msg_extended),
	SCR_JUMP ^ IFTRUE (DATA (NOP)),
		PADDR (clrack),
	SCR_JUMP ^ IFTRUE (DATA (MESSAGE_REJECT)),
		PADDRH (msg_reject),
	SCR_JUMP ^ IFTRUE (DATA (IGNORE_WIDE_RESIDUE)),
		PADDRH (msg_ign_residue),
	/*
	**	Rest of the messages left as
	**	an exercise ...
	**
	**	Unimplemented messages:
	**	fall through to MSG_BAD.
	*/
पूर्ण/*-------------------------< MSG_BAD >------------------*/,अणु
	/*
	**	unimplemented message - reject it.
	*/
	SCR_INT,
		SIR_REJECT_SENT,
	SCR_LOAD_REG (scratcha, MESSAGE_REJECT),
		0,
पूर्ण/*-------------------------< SETMSG >----------------------*/,अणु
	SCR_COPY (1),
		RADDR (scratcha),
		NADDR (msgout),
	SCR_SET (SCR_ATN),
		0,
	SCR_JUMP,
		PADDR (clrack),
पूर्ण/*-------------------------< CLEANUP >-------------------*/,अणु
	/*
	**      dsa:    Poपूर्णांकer to ccb
	**	      or xxxxxxFF (no ccb)
	**
	**      HS_REG:   Host-Status (<>0!)
	*/
	SCR_FROM_REG (dsa),
		0,
	SCR_JUMP ^ IFTRUE (DATA (0xff)),
		PADDR (start),
	/*
	**      dsa is valid.
	**	complete the cleanup.
	*/
	SCR_JUMP,
		PADDR (cleanup_ok),

पूर्ण/*-------------------------< COMPLETE >-----------------*/,अणु
	/*
	**	Complete message.
	**
	**	Copy TEMP रेजिस्टर to LASTP in header.
	*/
	SCR_COPY (4),
		RADDR (temp),
		NADDR (header.lastp),
	/*
	**	When we terminate the cycle by clearing ACK,
	**	the target may disconnect immediately.
	**
	**	We करोn't want to be told of an
	**	"unexpected disconnect",
	**	so we disable this feature.
	*/
	SCR_REG_REG (scntl2, SCR_AND, 0x7f),
		0,
	/*
	**	Terminate cycle ...
	*/
	SCR_CLR (SCR_ACK|SCR_ATN),
		0,
	/*
	**	... and रुको क्रम the disconnect.
	*/
	SCR_WAIT_DISC,
		0,
पूर्ण/*-------------------------< CLEANUP_OK >----------------*/,अणु
	/*
	**	Save host status to header.
	*/
	SCR_COPY (4),
		RADDR (scr0),
		NADDR (header.status),
	/*
	**	and copy back the header to the ccb.
	*/
	SCR_COPY_F (4),
		RADDR (dsa),
		PADDR (cleanup0),
	/*
	**	Flush script prefetch अगर required
	*/
	PREFETCH_FLUSH
	SCR_COPY (माप (काष्ठा head)),
		NADDR (header),
पूर्ण/*-------------------------< CLEANUP0 >--------------------*/,अणु
		0,
पूर्ण/*-------------------------< SIGNAL >----------------------*/,अणु
	/*
	**	अगर job not completed ...
	*/
	SCR_FROM_REG (HS_REG),
		0,
	/*
	**	... start the next command.
	*/
	SCR_JUMP ^ IFTRUE (MASK (0, (HS_DONEMASK|HS_SKIPMASK))),
		PADDR(start),
	/*
	**	If command resulted in not GOOD status,
	**	call the C code अगर needed.
	*/
	SCR_FROM_REG (SS_REG),
		0,
	SCR_CALL ^ IFFALSE (DATA (SAM_STAT_GOOD)),
		PADDRH (bad_status),

#अगर_अघोषित	SCSI_NCR_CCB_DONE_SUPPORT

	/*
	**	... संकेत completion to the host
	*/
	SCR_INT,
		SIR_INTFLY,
	/*
	**	Auf zu neuen Schandtaten!
	*/
	SCR_JUMP,
		PADDR(start),

#अन्यथा	/* defined SCSI_NCR_CCB_DONE_SUPPORT */

	/*
	**	... संकेत completion to the host
	*/
	SCR_JUMP,
पूर्ण/*------------------------< DONE_POS >---------------------*/,अणु
		PADDRH (करोne_queue),
पूर्ण/*------------------------< DONE_PLUG >--------------------*/,अणु
	SCR_INT,
		SIR_DONE_OVERFLOW,
पूर्ण/*------------------------< DONE_END >---------------------*/,अणु
	SCR_INT,
		SIR_INTFLY,
	SCR_COPY (4),
		RADDR (temp),
		PADDR (करोne_pos),
	SCR_JUMP,
		PADDR (start),

#पूर्ण_अगर	/* SCSI_NCR_CCB_DONE_SUPPORT */

पूर्ण/*-------------------------< SAVE_DP >------------------*/,अणु
	/*
	**	SAVE_DP message:
	**	Copy TEMP रेजिस्टर to SAVEP in header.
	*/
	SCR_COPY (4),
		RADDR (temp),
		NADDR (header.savep),
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP,
		PADDR (dispatch),
पूर्ण/*-------------------------< RESTORE_DP >---------------*/,अणु
	/*
	**	RESTORE_DP message:
	**	Copy SAVEP in header to TEMP रेजिस्टर.
	*/
	SCR_COPY (4),
		NADDR (header.savep),
		RADDR (temp),
	SCR_JUMP,
		PADDR (clrack),

पूर्ण/*-------------------------< DISCONNECT >---------------*/,अणु
	/*
	**	DISCONNECTing  ...
	**
	**	disable the "unexpected disconnect" feature,
	**	and हटाओ the ACK संकेत.
	*/
	SCR_REG_REG (scntl2, SCR_AND, 0x7f),
		0,
	SCR_CLR (SCR_ACK|SCR_ATN),
		0,
	/*
	**	Wait क्रम the disconnect.
	*/
	SCR_WAIT_DISC,
		0,
	/*
	**	Status is: DISCONNECTED.
	*/
	SCR_LOAD_REG (HS_REG, HS_DISCONNECT),
		0,
	SCR_JUMP,
		PADDR (cleanup_ok),

पूर्ण/*-------------------------< MSG_OUT >-------------------*/,अणु
	/*
	**	The target requests a message.
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_OUT,
		NADDR (msgout),
	SCR_COPY (1),
		NADDR (msgout),
		NADDR (lasपंचांगsg),
	/*
	**	If it was no ABORT message ...
	*/
	SCR_JUMP ^ IFTRUE (DATA (ABORT_TASK_SET)),
		PADDRH (msg_out_पात),
	/*
	**	... रुको क्रम the next phase
	**	अगर it's a message out, send it again, ...
	*/
	SCR_JUMP ^ IFTRUE (WHEN (SCR_MSG_OUT)),
		PADDR (msg_out),
पूर्ण/*-------------------------< MSG_OUT_DONE >--------------*/,अणु
	/*
	**	... अन्यथा clear the message ...
	*/
	SCR_LOAD_REG (scratcha, NOP),
		0,
	SCR_COPY (4),
		RADDR (scratcha),
		NADDR (msgout),
	/*
	**	... and process the next phase
	*/
	SCR_JUMP,
		PADDR (dispatch),
पूर्ण/*-------------------------< IDLE >------------------------*/,अणु
	/*
	**	Nothing to करो?
	**	Wait क्रम reselect.
	**	This NOP will be patched with LED OFF
	**	SCR_REG_REG (gpreg, SCR_OR, 0x01)
	*/
	SCR_NO_OP,
		0,
पूर्ण/*-------------------------< RESELECT >--------------------*/,अणु
	/*
	**	make the DSA invalid.
	*/
	SCR_LOAD_REG (dsa, 0xff),
		0,
	SCR_CLR (SCR_TRG),
		0,
	SCR_LOAD_REG (HS_REG, HS_IN_RESELECT),
		0,
	/*
	**	Sleep रुकोing क्रम a reselection.
	**	If SIGP is set, special treaपंचांगent.
	**
	**	Zu allem bereit ..
	*/
	SCR_WAIT_RESEL,
		PADDR(start),
पूर्ण/*-------------------------< RESELECTED >------------------*/,अणु
	/*
	**	This NOP will be patched with LED ON
	**	SCR_REG_REG (gpreg, SCR_AND, 0xfe)
	*/
	SCR_NO_OP,
		0,
	/*
	**	... zu nichts zu gebrauchen ?
	**
	**      load the target id पूर्णांकo the SFBR
	**	and jump to the control block.
	**
	**	Look at the declarations of
	**	- काष्ठा ncb
	**	- काष्ठा tcb
	**	- काष्ठा lcb
	**	- काष्ठा ccb
	**	to understand what's going on.
	*/
	SCR_REG_SFBR (ssid, SCR_AND, 0x8F),
		0,
	SCR_TO_REG (sdid),
		0,
	SCR_JUMP,
		NADDR (jump_tcb),

पूर्ण/*-------------------------< RESEL_DSA >-------------------*/,अणु
	/*
	**	Ack the IDENTIFY or TAG previously received.
	*/
	SCR_CLR (SCR_ACK),
		0,
	/*
	**      The ncr करोesn't have an indirect load
	**	or store command. So we have to
	**	copy part of the control block to a
	**	fixed place, where we can access it.
	**
	**	We patch the address part of a
	**	COPY command with the DSA-रेजिस्टर.
	*/
	SCR_COPY_F (4),
		RADDR (dsa),
		PADDR (loadpos1),
	/*
	**	Flush script prefetch अगर required
	*/
	PREFETCH_FLUSH
	/*
	**	then we करो the actual copy.
	*/
	SCR_COPY (माप (काष्ठा head)),
	/*
	**	जारीd after the next label ...
	*/

पूर्ण/*-------------------------< LOADPOS1 >-------------------*/,अणु
		0,
		NADDR (header),
	/*
	**	The DSA contains the data काष्ठाure address.
	*/
	SCR_JUMP,
		PADDR (prepare),

पूर्ण/*-------------------------< RESEL_LUN >-------------------*/,अणु
	/*
	**	come back to this poपूर्णांक
	**	to get an IDENTIFY message
	**	Wait क्रम a msg_in phase.
	*/
	SCR_INT ^ IFFALSE (WHEN (SCR_MSG_IN)),
		SIR_RESEL_NO_MSG_IN,
	/*
	**	message phase.
	**	Read the data directly from the BUS DATA lines.
	**	This helps to support very old SCSI devices that 
	**	may reselect without sending an IDENTIFY.
	*/
	SCR_FROM_REG (sbdl),
		0,
	/*
	**	It should be an Identअगरy message.
	*/
	SCR_RETURN,
		0,
पूर्ण/*-------------------------< RESEL_TAG >-------------------*/,अणु
	/*
	**	Read IDENTIFY + SIMPLE + TAG using a single MOVE.
	**	Aggressive optimization, is'nt it?
	**	No need to test the SIMPLE TAG message, since the 
	**	driver only supports conक्रमmant devices क्रम tags. ;-)
	*/
	SCR_MOVE_ABS (3) ^ SCR_MSG_IN,
		NADDR (msgin),
	/*
	**	Read the TAG from the SIDL.
	**	Still an aggressive optimization. ;-)
	**	Compute the CCB indirect jump address which 
	**	is (#TAG*2 & 0xfc) due to tag numbering using 
	**	1,3,5..MAXTAGS*2+1 actual values.
	*/
	SCR_REG_SFBR (sidl, SCR_SHL, 0),
		0,
	SCR_SFBR_REG (temp, SCR_AND, 0xfc),
		0,
पूर्ण/*-------------------------< JUMP_TO_NEXUS >-------------------*/,अणु
	SCR_COPY_F (4),
		RADDR (temp),
		PADDR (nexus_indirect),
	/*
	**	Flush script prefetch अगर required
	*/
	PREFETCH_FLUSH
	SCR_COPY (4),
पूर्ण/*-------------------------< NEXUS_INसूचीECT >-------------------*/,अणु
		0,
		RADDR (temp),
	SCR_RETURN,
		0,
पूर्ण/*-------------------------< RESEL_NOTAG >-------------------*/,अणु
	/*
	**	No tag expected.
	**	Read an throw away the IDENTIFY.
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin),
	SCR_JUMP,
		PADDR (jump_to_nexus),
पूर्ण/*-------------------------< DATA_IN >--------------------*/,अणु
/*
**	Because the size depends on the
**	#घोषणा MAX_SCATTERL parameter,
**	it is filled in at runसमय.
**
**  ##===========< i=0; i<MAX_SCATTERL >=========
**  ||	SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_IN)),
**  ||		PADDR (dispatch),
**  ||	SCR_MOVE_TBL ^ SCR_DATA_IN,
**  ||		दुरत्व (काष्ठा dsb, data[ i]),
**  ##==========================================
**
**---------------------------------------------------------
*/
0
पूर्ण/*-------------------------< DATA_IN2 >-------------------*/,अणु
	SCR_CALL,
		PADDR (dispatch),
	SCR_JUMP,
		PADDR (no_data),
पूर्ण/*-------------------------< DATA_OUT >--------------------*/,अणु
/*
**	Because the size depends on the
**	#घोषणा MAX_SCATTERL parameter,
**	it is filled in at runसमय.
**
**  ##===========< i=0; i<MAX_SCATTERL >=========
**  ||	SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_OUT)),
**  ||		PADDR (dispatch),
**  ||	SCR_MOVE_TBL ^ SCR_DATA_OUT,
**  ||		दुरत्व (काष्ठा dsb, data[ i]),
**  ##==========================================
**
**---------------------------------------------------------
*/
0
पूर्ण/*-------------------------< DATA_OUT2 >-------------------*/,अणु
	SCR_CALL,
		PADDR (dispatch),
	SCR_JUMP,
		PADDR (no_data),
पूर्ण/*--------------------------------------------------------*/
पूर्ण;

अटल	काष्ठा scripth scripth0 __initdata = अणु
/*-------------------------< TRYLOOP >---------------------*/अणु
/*
**	Start the next entry.
**	Called addresses poपूर्णांक to the launch script in the CCB.
**	They are patched by the मुख्य processor.
**
**	Because the size depends on the
**	#घोषणा MAX_START parameter, it is filled
**	in at runसमय.
**
**-----------------------------------------------------------
**
**  ##===========< I=0; i<MAX_START >===========
**  ||	SCR_CALL,
**  ||		PADDR (idle),
**  ##==========================================
**
**-----------------------------------------------------------
*/
0
पूर्ण/*------------------------< TRYLOOP2 >---------------------*/,अणु
	SCR_JUMP,
		PADDRH(tryloop),

#अगर_घोषित SCSI_NCR_CCB_DONE_SUPPORT

पूर्ण/*------------------------< DONE_QUEUE >-------------------*/,अणु
/*
**	Copy the CCB address to the next करोne entry.
**	Because the size depends on the
**	#घोषणा MAX_DONE parameter, it is filled
**	in at runसमय.
**
**-----------------------------------------------------------
**
**  ##===========< I=0; i<MAX_DONE >===========
**  ||	SCR_COPY (माप(काष्ठा ccb *),
**  ||		NADDR (header.cp),
**  ||		NADDR (ccb_करोne[i]),
**  ||	SCR_CALL,
**  ||		PADDR (करोne_end),
**  ##==========================================
**
**-----------------------------------------------------------
*/
0
पूर्ण/*------------------------< DONE_QUEUE2 >------------------*/,अणु
	SCR_JUMP,
		PADDRH (करोne_queue),

#पूर्ण_अगर /* SCSI_NCR_CCB_DONE_SUPPORT */
पूर्ण/*------------------------< SELECT_NO_ATN >-----------------*/,अणु
	/*
	**	Set Initiator mode.
	**      And try to select this target without ATN.
	*/

	SCR_CLR (SCR_TRG),
		0,
	SCR_LOAD_REG (HS_REG, HS_SELECTING),
		0,
	SCR_SEL_TBL ^ दुरत्व (काष्ठा dsb, select),
		PADDR (reselect),
	SCR_JUMP,
		PADDR (select2),

पूर्ण/*-------------------------< CANCEL >------------------------*/,अणु

	SCR_LOAD_REG (scratcha, HS_ABORTED),
		0,
	SCR_JUMPR,
		8,
पूर्ण/*-------------------------< SKIP >------------------------*/,अणु
	SCR_LOAD_REG (scratcha, 0),
		0,
	/*
	**	This entry has been canceled.
	**	Next समय use the next slot.
	*/
	SCR_COPY (4),
		RADDR (temp),
		PADDR (startpos),
	/*
	**      The ncr करोesn't have an indirect load
	**	or store command. So we have to
	**	copy part of the control block to a
	**	fixed place, where we can access it.
	**
	**	We patch the address part of a
	**	COPY command with the DSA-रेजिस्टर.
	*/
	SCR_COPY_F (4),
		RADDR (dsa),
		PADDRH (skip2),
	/*
	**	Flush script prefetch अगर required
	*/
	PREFETCH_FLUSH
	/*
	**	then we करो the actual copy.
	*/
	SCR_COPY (माप (काष्ठा head)),
	/*
	**	जारीd after the next label ...
	*/
पूर्ण/*-------------------------< SKIP2 >---------------------*/,अणु
		0,
		NADDR (header),
	/*
	**      Initialize the status रेजिस्टरs
	*/
	SCR_COPY (4),
		NADDR (header.status),
		RADDR (scr0),
	/*
	**	Force host status.
	*/
	SCR_FROM_REG (scratcha),
		0,
	SCR_JUMPR ^ IFFALSE (MASK (0, HS_DONEMASK)),
		16,
	SCR_REG_REG (HS_REG, SCR_OR, HS_SKIPMASK),
		0,
	SCR_JUMPR,
		8,
	SCR_TO_REG (HS_REG),
		0,
	SCR_LOAD_REG (SS_REG, SAM_STAT_GOOD),
		0,
	SCR_JUMP,
		PADDR (cleanup_ok),

पूर्ण,/*-------------------------< PAR_ERR_DATA_IN >---------------*/अणु
	/*
	**	Ignore all data in byte, until next phase
	*/
	SCR_JUMP ^ IFFALSE (WHEN (SCR_DATA_IN)),
		PADDRH (par_err_other),
	SCR_MOVE_ABS (1) ^ SCR_DATA_IN,
		NADDR (scratch),
	SCR_JUMPR,
		-24,
पूर्ण,/*-------------------------< PAR_ERR_OTHER >------------------*/अणु
	/*
	**	count it.
	*/
	SCR_REG_REG (PS_REG, SCR_ADD, 0x01),
		0,
	/*
	**	jump to dispatcher.
	*/
	SCR_JUMP,
		PADDR (dispatch),
पूर्ण/*-------------------------< MSG_REJECT >---------------*/,अणु
	/*
	**	If a negotiation was in progress,
	**	negotiation failed.
	**	Otherwise, let the C code prपूर्णांक 
	**	some message.
	*/
	SCR_FROM_REG (HS_REG),
		0,
	SCR_INT ^ IFFALSE (DATA (HS_NEGOTIATE)),
		SIR_REJECT_RECEIVED,
	SCR_INT ^ IFTRUE (DATA (HS_NEGOTIATE)),
		SIR_NEGO_FAILED,
	SCR_JUMP,
		PADDR (clrack),

पूर्ण/*-------------------------< MSG_IGN_RESIDUE >----------*/,अणु
	/*
	**	Terminate cycle
	*/
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_IN)),
		PADDR (dispatch),
	/*
	**	get residue size.
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin[1]),
	/*
	**	Size is 0 .. ignore message.
	*/
	SCR_JUMP ^ IFTRUE (DATA (0)),
		PADDR (clrack),
	/*
	**	Size is not 1 .. have to पूर्णांकerrupt.
	*/
	SCR_JUMPR ^ IFFALSE (DATA (1)),
		40,
	/*
	**	Check क्रम residue byte in swide रेजिस्टर
	*/
	SCR_FROM_REG (scntl2),
		0,
	SCR_JUMPR ^ IFFALSE (MASK (WSR, WSR)),
		16,
	/*
	**	There IS data in the swide रेजिस्टर.
	**	Discard it.
	*/
	SCR_REG_REG (scntl2, SCR_OR, WSR),
		0,
	SCR_JUMP,
		PADDR (clrack),
	/*
	**	Load again the size to the sfbr रेजिस्टर.
	*/
	SCR_FROM_REG (scratcha),
		0,
	SCR_INT,
		SIR_IGN_RESIDUE,
	SCR_JUMP,
		PADDR (clrack),

पूर्ण/*-------------------------< MSG_EXTENDED >-------------*/,अणु
	/*
	**	Terminate cycle
	*/
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_IN)),
		PADDR (dispatch),
	/*
	**	get length.
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin[1]),
	/*
	*/
	SCR_JUMP ^ IFTRUE (DATA (3)),
		PADDRH (msg_ext_3),
	SCR_JUMP ^ IFFALSE (DATA (2)),
		PADDR (msg_bad),
पूर्ण/*-------------------------< MSG_EXT_2 >----------------*/,अणु
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_IN)),
		PADDR (dispatch),
	/*
	**	get extended message code.
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin[2]),
	SCR_JUMP ^ IFTRUE (DATA (EXTENDED_WDTR)),
		PADDRH (msg_wdtr),
	/*
	**	unknown extended message
	*/
	SCR_JUMP,
		PADDR (msg_bad)
पूर्ण/*-------------------------< MSG_WDTR >-----------------*/,अणु
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_IN)),
		PADDR (dispatch),
	/*
	**	get data bus width
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin[3]),
	/*
	**	let the host करो the real work.
	*/
	SCR_INT,
		SIR_NEGO_WIDE,
	/*
	**	let the target fetch our answer.
	*/
	SCR_SET (SCR_ATN),
		0,
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_OUT)),
		PADDRH (nego_bad_phase),

पूर्ण/*-------------------------< SEND_WDTR >----------------*/,अणु
	/*
	**	Send the EXTENDED_WDTR
	*/
	SCR_MOVE_ABS (4) ^ SCR_MSG_OUT,
		NADDR (msgout),
	SCR_COPY (1),
		NADDR (msgout),
		NADDR (lasपंचांगsg),
	SCR_JUMP,
		PADDR (msg_out_करोne),

पूर्ण/*-------------------------< MSG_EXT_3 >----------------*/,अणु
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_IN)),
		PADDR (dispatch),
	/*
	**	get extended message code.
	*/
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin[2]),
	SCR_JUMP ^ IFTRUE (DATA (EXTENDED_SDTR)),
		PADDRH (msg_sdtr),
	/*
	**	unknown extended message
	*/
	SCR_JUMP,
		PADDR (msg_bad)

पूर्ण/*-------------------------< MSG_SDTR >-----------------*/,अणु
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_IN)),
		PADDR (dispatch),
	/*
	**	get period and offset
	*/
	SCR_MOVE_ABS (2) ^ SCR_MSG_IN,
		NADDR (msgin[3]),
	/*
	**	let the host करो the real work.
	*/
	SCR_INT,
		SIR_NEGO_SYNC,
	/*
	**	let the target fetch our answer.
	*/
	SCR_SET (SCR_ATN),
		0,
	SCR_CLR (SCR_ACK),
		0,
	SCR_JUMP ^ IFFALSE (WHEN (SCR_MSG_OUT)),
		PADDRH (nego_bad_phase),

पूर्ण/*-------------------------< SEND_SDTR >-------------*/,अणु
	/*
	**	Send the EXTENDED_SDTR
	*/
	SCR_MOVE_ABS (5) ^ SCR_MSG_OUT,
		NADDR (msgout),
	SCR_COPY (1),
		NADDR (msgout),
		NADDR (lasपंचांगsg),
	SCR_JUMP,
		PADDR (msg_out_करोne),

पूर्ण/*-------------------------< NEGO_BAD_PHASE >------------*/,अणु
	SCR_INT,
		SIR_NEGO_PROTO,
	SCR_JUMP,
		PADDR (dispatch),

पूर्ण/*-------------------------< MSG_OUT_ABORT >-------------*/,अणु
	/*
	**	After ABORT message,
	**
	**	expect an immediate disconnect, ...
	*/
	SCR_REG_REG (scntl2, SCR_AND, 0x7f),
		0,
	SCR_CLR (SCR_ACK|SCR_ATN),
		0,
	SCR_WAIT_DISC,
		0,
	/*
	**	... and set the status to "ABORTED"
	*/
	SCR_LOAD_REG (HS_REG, HS_ABORTED),
		0,
	SCR_JUMP,
		PADDR (cleanup),

पूर्ण/*-------------------------< HDATA_IN >-------------------*/,अणु
/*
**	Because the size depends on the
**	#घोषणा MAX_SCATTERH parameter,
**	it is filled in at runसमय.
**
**  ##==< i=MAX_SCATTERL; i<MAX_SCATTERL+MAX_SCATTERH >==
**  ||	SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_IN)),
**  ||		PADDR (dispatch),
**  ||	SCR_MOVE_TBL ^ SCR_DATA_IN,
**  ||		दुरत्व (काष्ठा dsb, data[ i]),
**  ##===================================================
**
**---------------------------------------------------------
*/
0
पूर्ण/*-------------------------< HDATA_IN2 >------------------*/,अणु
	SCR_JUMP,
		PADDR (data_in),

पूर्ण/*-------------------------< HDATA_OUT >-------------------*/,अणु
/*
**	Because the size depends on the
**	#घोषणा MAX_SCATTERH parameter,
**	it is filled in at runसमय.
**
**  ##==< i=MAX_SCATTERL; i<MAX_SCATTERL+MAX_SCATTERH >==
**  ||	SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_OUT)),
**  ||		PADDR (dispatch),
**  ||	SCR_MOVE_TBL ^ SCR_DATA_OUT,
**  ||		दुरत्व (काष्ठा dsb, data[ i]),
**  ##===================================================
**
**---------------------------------------------------------
*/
0
पूर्ण/*-------------------------< HDATA_OUT2 >------------------*/,अणु
	SCR_JUMP,
		PADDR (data_out),

पूर्ण/*-------------------------< RESET >----------------------*/,अणु
	/*
	**      Send a TARGET_RESET message अगर bad IDENTIFY 
	**	received on reselection.
	*/
	SCR_LOAD_REG (scratcha, ABORT_TASK),
		0,
	SCR_JUMP,
		PADDRH (पात_resel),
पूर्ण/*-------------------------< ABORTTAG >-------------------*/,अणु
	/*
	**      Abort a wrong tag received on reselection.
	*/
	SCR_LOAD_REG (scratcha, ABORT_TASK),
		0,
	SCR_JUMP,
		PADDRH (पात_resel),
पूर्ण/*-------------------------< ABORT >----------------------*/,अणु
	/*
	**      Abort a reselection when no active CCB.
	*/
	SCR_LOAD_REG (scratcha, ABORT_TASK_SET),
		0,
पूर्ण/*-------------------------< ABORT_RESEL >----------------*/,अणु
	SCR_COPY (1),
		RADDR (scratcha),
		NADDR (msgout),
	SCR_SET (SCR_ATN),
		0,
	SCR_CLR (SCR_ACK),
		0,
	/*
	**	and send it.
	**	we expect an immediate disconnect
	*/
	SCR_REG_REG (scntl2, SCR_AND, 0x7f),
		0,
	SCR_MOVE_ABS (1) ^ SCR_MSG_OUT,
		NADDR (msgout),
	SCR_COPY (1),
		NADDR (msgout),
		NADDR (lasपंचांगsg),
	SCR_CLR (SCR_ACK|SCR_ATN),
		0,
	SCR_WAIT_DISC,
		0,
	SCR_JUMP,
		PADDR (start),
पूर्ण/*-------------------------< RESEND_IDENT >-------------------*/,अणु
	/*
	**	The target stays in MSG OUT phase after having acked 
	**	Identअगरy [+ Tag [+ Extended message ]]. Tarमाला_लो shall
	**	behave this way on parity error.
	**	We must send it again all the messages.
	*/
	SCR_SET (SCR_ATN), /* Shall be निश्चितed 2 deskew delays beक्रमe the  */
		0,         /* 1rst ACK = 90 ns. Hope the NCR is'nt too fast */
	SCR_JUMP,
		PADDR (send_ident),
पूर्ण/*-------------------------< CLRATN_GO_ON >-------------------*/,अणु
	SCR_CLR (SCR_ATN),
		0,
	SCR_JUMP,
पूर्ण/*-------------------------< NXTDSP_GO_ON >-------------------*/,अणु
		0,
पूर्ण/*-------------------------< SDATA_IN >-------------------*/,अणु
	SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_IN)),
		PADDR (dispatch),
	SCR_MOVE_TBL ^ SCR_DATA_IN,
		दुरत्व (काष्ठा dsb, sense),
	SCR_CALL,
		PADDR (dispatch),
	SCR_JUMP,
		PADDR (no_data),
पूर्ण/*-------------------------< DATA_IO >--------------------*/,अणु
	/*
	**	We jump here अगर the data direction was unknown at the 
	**	समय we had to queue the command to the scripts processor.
	**	Poपूर्णांकers had been set as follow in this situation:
	**	  savep   -->   DATA_IO
	**	  lastp   -->   start poपूर्णांकer when DATA_IN
	**	  goalp   -->   goal  poपूर्णांकer when DATA_IN
	**	  wlastp  -->   start poपूर्णांकer when DATA_OUT
	**	  wgoalp  -->   goal  poपूर्णांकer when DATA_OUT
	**	This script sets savep/lastp/goalp according to the 
	**	direction chosen by the target.
	*/
	SCR_JUMPR ^ IFTRUE (WHEN (SCR_DATA_OUT)),
		32,
	/*
	**	Direction is DATA IN.
	**	Warning: we jump here, even when phase is DATA OUT.
	*/
	SCR_COPY (4),
		NADDR (header.lastp),
		NADDR (header.savep),

	/*
	**	Jump to the SCRIPTS according to actual direction.
	*/
	SCR_COPY (4),
		NADDR (header.savep),
		RADDR (temp),
	SCR_RETURN,
		0,
	/*
	**	Direction is DATA OUT.
	*/
	SCR_COPY (4),
		NADDR (header.wlastp),
		NADDR (header.lastp),
	SCR_COPY (4),
		NADDR (header.wgoalp),
		NADDR (header.goalp),
	SCR_JUMPR,
		-64,
पूर्ण/*-------------------------< BAD_IDENTIFY >---------------*/,अणु
	/*
	**	If message phase but not an IDENTIFY,
	**	get some help from the C code.
	**	Old SCSI device may behave so.
	*/
	SCR_JUMPR ^ IFTRUE (MASK (0x80, 0x80)),
		16,
	SCR_INT,
		SIR_RESEL_NO_IDENTIFY,
	SCR_JUMP,
		PADDRH (reset),
	/*
	**	Message is an IDENTIFY, but lun is unknown.
	**	Read the message, since we got it directly 
	**	from the SCSI BUS data lines.
	**	Signal problem to C code क्रम logging the event.
	**	Send an ABORT_TASK_SET to clear all pending tasks.
	*/
	SCR_INT,
		SIR_RESEL_BAD_LUN,
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin),
	SCR_JUMP,
		PADDRH (पात),
पूर्ण/*-------------------------< BAD_I_T_L >------------------*/,अणु
	/*
	**	We करोnnot have a task क्रम that I_T_L.
	**	Signal problem to C code क्रम logging the event.
	**	Send an ABORT_TASK_SET message.
	*/
	SCR_INT,
		SIR_RESEL_BAD_I_T_L,
	SCR_JUMP,
		PADDRH (पात),
पूर्ण/*-------------------------< BAD_I_T_L_Q >----------------*/,अणु
	/*
	**	We करोnnot have a task that matches the tag.
	**	Signal problem to C code क्रम logging the event.
	**	Send an ABORT_TASK message.
	*/
	SCR_INT,
		SIR_RESEL_BAD_I_T_L_Q,
	SCR_JUMP,
		PADDRH (पातtag),
पूर्ण/*-------------------------< BAD_TARGET >-----------------*/,अणु
	/*
	**	We करोnnot know the target that reselected us.
	**	Grab the first message अगर any (IDENTIFY).
	**	Signal problem to C code क्रम logging the event.
	**	TARGET_RESET message.
	*/
	SCR_INT,
		SIR_RESEL_BAD_TARGET,
	SCR_JUMPR ^ IFFALSE (WHEN (SCR_MSG_IN)),
		8,
	SCR_MOVE_ABS (1) ^ SCR_MSG_IN,
		NADDR (msgin),
	SCR_JUMP,
		PADDRH (reset),
पूर्ण/*-------------------------< BAD_STATUS >-----------------*/,अणु
	/*
	**	If command resulted in either TASK_SET FULL,
	**	CHECK CONDITION or COMMAND TERMINATED,
	**	call the C code.
	*/
	SCR_INT ^ IFTRUE (DATA (SAM_STAT_TASK_SET_FULL)),
		SIR_BAD_STATUS,
	SCR_INT ^ IFTRUE (DATA (SAM_STAT_CHECK_CONDITION)),
		SIR_BAD_STATUS,
	SCR_INT ^ IFTRUE (DATA (SAM_STAT_COMMAND_TERMINATED)),
		SIR_BAD_STATUS,
	SCR_RETURN,
		0,
पूर्ण/*-------------------------< START_RAM >-------------------*/,अणु
	/*
	**	Load the script पूर्णांकo on-chip RAM, 
	**	and jump to start poपूर्णांक.
	*/
	SCR_COPY_F (4),
		RADDR (scratcha),
		PADDRH (start_ram0),
	/*
	**	Flush script prefetch अगर required
	*/
	PREFETCH_FLUSH
	SCR_COPY (माप (काष्ठा script)),
पूर्ण/*-------------------------< START_RAM0 >--------------------*/,अणु
		0,
		PADDR (start),
	SCR_JUMP,
		PADDR (start),
पूर्ण/*-------------------------< STO_RESTART >-------------------*/,अणु
	/*
	**
	**	Repair start queue (e.g. next समय use the next slot) 
	**	and jump to start poपूर्णांक.
	*/
	SCR_COPY (4),
		RADDR (temp),
		PADDR (startpos),
	SCR_JUMP,
		PADDR (start),
पूर्ण/*-------------------------< WAIT_DMA >-------------------*/,अणु
	/*
	**	For HP Zalon/53c720 प्रणालीs, the Zalon पूर्णांकerface
	**	between CPU and 53c720 करोes prefetches, which causes
	**	problems with self modअगरying scripts.  The problem
	**	is overcome by calling a dummy subroutine after each
	**	modअगरication, to क्रमce a refetch of the script on
	**	वापस from the subroutine.
	*/
	SCR_RETURN,
		0,
पूर्ण/*-------------------------< SNOOPTEST >-------------------*/,अणु
	/*
	**	Read the variable.
	*/
	SCR_COPY (4),
		NADDR(ncr_cache),
		RADDR (scratcha),
	/*
	**	Write the variable.
	*/
	SCR_COPY (4),
		RADDR (temp),
		NADDR(ncr_cache),
	/*
	**	Read back the variable.
	*/
	SCR_COPY (4),
		NADDR(ncr_cache),
		RADDR (temp),
पूर्ण/*-------------------------< SNOOPEND >-------------------*/,अणु
	/*
	**	And stop.
	*/
	SCR_INT,
		99,
पूर्ण/*--------------------------------------------------------*/
पूर्ण;

/*==========================================================
**
**
**	Fill in #घोषणा dependent parts of the script
**
**
**==========================================================
*/

व्योम __init ncr_script_fill (काष्ठा script * scr, काष्ठा scripth * scrh)
अणु
	पूर्णांक	i;
	ncrcmd	*p;

	p = scrh->tryloop;
	क्रम (i=0; i<MAX_START; i++) अणु
		*p++ =SCR_CALL;
		*p++ =PADDR (idle);
	पूर्ण

	BUG_ON((u_दीर्घ)p != (u_दीर्घ)&scrh->tryloop + माप (scrh->tryloop));

#अगर_घोषित SCSI_NCR_CCB_DONE_SUPPORT

	p = scrh->करोne_queue;
	क्रम (i = 0; i<MAX_DONE; i++) अणु
		*p++ =SCR_COPY (माप(काष्ठा ccb *));
		*p++ =NADDR (header.cp);
		*p++ =NADDR (ccb_करोne[i]);
		*p++ =SCR_CALL;
		*p++ =PADDR (करोne_end);
	पूर्ण

	BUG_ON((u_दीर्घ)p != (u_दीर्घ)&scrh->करोne_queue+माप(scrh->करोne_queue));

#पूर्ण_अगर /* SCSI_NCR_CCB_DONE_SUPPORT */

	p = scrh->hdata_in;
	क्रम (i=0; i<MAX_SCATTERH; i++) अणु
		*p++ =SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_IN));
		*p++ =PADDR (dispatch);
		*p++ =SCR_MOVE_TBL ^ SCR_DATA_IN;
		*p++ =दुरत्व (काष्ठा dsb, data[i]);
	पूर्ण

	BUG_ON((u_दीर्घ)p != (u_दीर्घ)&scrh->hdata_in + माप (scrh->hdata_in));

	p = scr->data_in;
	क्रम (i=MAX_SCATTERH; i<MAX_SCATTERH+MAX_SCATTERL; i++) अणु
		*p++ =SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_IN));
		*p++ =PADDR (dispatch);
		*p++ =SCR_MOVE_TBL ^ SCR_DATA_IN;
		*p++ =दुरत्व (काष्ठा dsb, data[i]);
	पूर्ण

	BUG_ON((u_दीर्घ)p != (u_दीर्घ)&scr->data_in + माप (scr->data_in));

	p = scrh->hdata_out;
	क्रम (i=0; i<MAX_SCATTERH; i++) अणु
		*p++ =SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_OUT));
		*p++ =PADDR (dispatch);
		*p++ =SCR_MOVE_TBL ^ SCR_DATA_OUT;
		*p++ =दुरत्व (काष्ठा dsb, data[i]);
	पूर्ण

	BUG_ON((u_दीर्घ)p != (u_दीर्घ)&scrh->hdata_out + माप (scrh->hdata_out));

	p = scr->data_out;
	क्रम (i=MAX_SCATTERH; i<MAX_SCATTERH+MAX_SCATTERL; i++) अणु
		*p++ =SCR_CALL ^ IFFALSE (WHEN (SCR_DATA_OUT));
		*p++ =PADDR (dispatch);
		*p++ =SCR_MOVE_TBL ^ SCR_DATA_OUT;
		*p++ =दुरत्व (काष्ठा dsb, data[i]);
	पूर्ण

	BUG_ON((u_दीर्घ) p != (u_दीर्घ)&scr->data_out + माप (scr->data_out));
पूर्ण

/*==========================================================
**
**
**	Copy and rebind a script.
**
**
**==========================================================
*/

अटल व्योम __init 
ncr_script_copy_and_bind (काष्ठा ncb *np, ncrcmd *src, ncrcmd *dst, पूर्णांक len)
अणु
	ncrcmd  opcode, new, old, पंचांगp1, पंचांगp2;
	ncrcmd	*start, *end;
	पूर्णांक relocs;
	पूर्णांक opchanged = 0;

	start = src;
	end = src + len/4;

	जबतक (src < end) अणु

		opcode = *src++;
		*dst++ = cpu_to_scr(opcode);

		/*
		**	If we क्रमget to change the length
		**	in काष्ठा script, a field will be
		**	padded with 0. This is an illegal
		**	command.
		*/

		अगर (opcode == 0) अणु
			prपूर्णांकk (KERN_ERR "%s: ERROR0 IN SCRIPT at %d.\n",
				ncr_name(np), (पूर्णांक) (src-start-1));
			mdelay(1000);
		पूर्ण

		अगर (DEBUG_FLAGS & DEBUG_SCRIPT)
			prपूर्णांकk (KERN_DEBUG "%p:  <%x>\n",
				(src-1), (अचिन्हित)opcode);

		/*
		**	We करोn't have to decode ALL commands
		*/
		चयन (opcode >> 28) अणु

		हाल 0xc:
			/*
			**	COPY has TWO arguments.
			*/
			relocs = 2;
			पंचांगp1 = src[0];
#अगर_घोषित	RELOC_KVAR
			अगर ((पंचांगp1 & RELOC_MASK) == RELOC_KVAR)
				पंचांगp1 = 0;
#पूर्ण_अगर
			पंचांगp2 = src[1];
#अगर_घोषित	RELOC_KVAR
			अगर ((पंचांगp2 & RELOC_MASK) == RELOC_KVAR)
				पंचांगp2 = 0;
#पूर्ण_अगर
			अगर ((पंचांगp1 ^ पंचांगp2) & 3) अणु
				prपूर्णांकk (KERN_ERR"%s: ERROR1 IN SCRIPT at %d.\n",
					ncr_name(np), (पूर्णांक) (src-start-1));
				mdelay(1000);
			पूर्ण
			/*
			**	If PREFETCH feature not enabled, हटाओ 
			**	the NO FLUSH bit अगर present.
			*/
			अगर ((opcode & SCR_NO_FLUSH) && !(np->features & FE_PFEN)) अणु
				dst[-1] = cpu_to_scr(opcode & ~SCR_NO_FLUSH);
				++opchanged;
			पूर्ण
			अवरोध;

		हाल 0x0:
			/*
			**	MOVE (असलolute address)
			*/
			relocs = 1;
			अवरोध;

		हाल 0x8:
			/*
			**	JUMP / CALL
			**	करोn't relocate अगर relative :-)
			*/
			अगर (opcode & 0x00800000)
				relocs = 0;
			अन्यथा
				relocs = 1;
			अवरोध;

		हाल 0x4:
		हाल 0x5:
		हाल 0x6:
		हाल 0x7:
			relocs = 1;
			अवरोध;

		शेष:
			relocs = 0;
			अवरोध;
		पूर्ण

		अगर (relocs) अणु
			जबतक (relocs--) अणु
				old = *src++;

				चयन (old & RELOC_MASK) अणु
				हाल RELOC_REGISTER:
					new = (old & ~RELOC_MASK) + np->paddr;
					अवरोध;
				हाल RELOC_LABEL:
					new = (old & ~RELOC_MASK) + np->p_script;
					अवरोध;
				हाल RELOC_LABELH:
					new = (old & ~RELOC_MASK) + np->p_scripth;
					अवरोध;
				हाल RELOC_SOFTC:
					new = (old & ~RELOC_MASK) + np->p_ncb;
					अवरोध;
#अगर_घोषित	RELOC_KVAR
				हाल RELOC_KVAR:
					अगर (((old & ~RELOC_MASK) <
					     SCRIPT_KVAR_FIRST) ||
					    ((old & ~RELOC_MASK) >
					     SCRIPT_KVAR_LAST))
						panic("ncr KVAR out of range");
					new = vtophys(script_kvars[old &
					    ~RELOC_MASK]);
					अवरोध;
#पूर्ण_अगर
				हाल 0:
					/* Don't relocate a 0 address. */
					अगर (old == 0) अणु
						new = old;
						अवरोध;
					पूर्ण
					fallthrough;
				शेष:
					panic("ncr_script_copy_and_bind: weird relocation %x\n", old);
					अवरोध;
				पूर्ण

				*dst++ = cpu_to_scr(new);
			पूर्ण
		पूर्ण अन्यथा
			*dst++ = cpu_to_scr(*src++);

	पूर्ण
पूर्ण

/*
**	Linux host data काष्ठाure
*/

काष्ठा host_data अणु
     काष्ठा ncb *ncb;
पूर्ण;

#घोषणा PRINT_ADDR(cmd, arg...) dev_info(&cmd->device->sdev_gendev , ## arg)

अटल व्योम ncr_prपूर्णांक_msg(काष्ठा ccb *cp, अक्षर *label, u_अक्षर *msg)
अणु
	PRINT_ADDR(cp->cmd, "%s: ", label);

	spi_prपूर्णांक_msg(msg);
	prपूर्णांकk("\n");
पूर्ण

/*==========================================================
**
**	NCR chip घड़ी भागisor table.
**	Divisors are multiplied by 10,000,000 in order to make 
**	calculations more simple.
**
**==========================================================
*/

#घोषणा _5M 5000000
अटल u_दीर्घ भाग_10M[] =
	अणु2*_5M, 3*_5M, 4*_5M, 6*_5M, 8*_5M, 12*_5M, 16*_5Mपूर्ण;


/*===============================================================
**
**	Prepare io रेजिस्टर values used by ncr_init() according 
**	to selected and supported features.
**
**	NCR chips allow burst lengths of 2, 4, 8, 16, 32, 64, 128 
**	transfers. 32,64,128 are only supported by 875 and 895 chips.
**	We use log base 2 (burst length) as पूर्णांकernal code, with 
**	value 0 meaning "burst disabled".
**
**===============================================================
*/

/*
 *	Burst length from burst code.
 */
#घोषणा burst_length(bc) (!(bc))? 0 : 1 << (bc)

/*
 *	Burst code from io रेजिस्टर bits.  Burst enable is ctest0 क्रम c720
 */
#घोषणा burst_code(dmode, ctest0) \
	(ctest0) & 0x80 ? 0 : (((dmode) & 0xc0) >> 6) + 1

/*
 *	Set initial io रेजिस्टर bits from burst code.
 */
अटल अंतरभूत व्योम ncr_init_burst(काष्ठा ncb *np, u_अक्षर bc)
अणु
	u_अक्षर *be = &np->rv_ctest0;
	*be		&= ~0x80;
	np->rv_dmode	&= ~(0x3 << 6);
	np->rv_ctest5	&= ~0x4;

	अगर (!bc) अणु
		*be		|= 0x80;
	पूर्ण अन्यथा अणु
		--bc;
		np->rv_dmode	|= ((bc & 0x3) << 6);
		np->rv_ctest5	|= (bc & 0x4);
	पूर्ण
पूर्ण

अटल व्योम __init ncr_prepare_setting(काष्ठा ncb *np)
अणु
	u_अक्षर	burst_max;
	u_दीर्घ	period;
	पूर्णांक i;

	/*
	**	Save assumed BIOS setting
	*/

	np->sv_scntl0	= INB(nc_scntl0) & 0x0a;
	np->sv_scntl3	= INB(nc_scntl3) & 0x07;
	np->sv_dmode	= INB(nc_dmode)  & 0xce;
	np->sv_dcntl	= INB(nc_dcntl)  & 0xa8;
	np->sv_ctest0	= INB(nc_ctest0) & 0x84;
	np->sv_ctest3	= INB(nc_ctest3) & 0x01;
	np->sv_ctest4	= INB(nc_ctest4) & 0x80;
	np->sv_ctest5	= INB(nc_ctest5) & 0x24;
	np->sv_gpcntl	= INB(nc_gpcntl);
	np->sv_stest2	= INB(nc_stest2) & 0x20;
	np->sv_stest4	= INB(nc_stest4);

	/*
	**	Wide ?
	*/

	np->maxwide	= (np->features & FE_WIDE)? 1 : 0;

 	/*
	 *  Guess the frequency of the chip's घड़ी.
	 */
	अगर (np->features & FE_ULTRA)
		np->घड़ी_khz = 80000;
	अन्यथा
		np->घड़ी_khz = 40000;

	/*
	 *  Get the घड़ी multiplier factor.
 	 */
	अगर	(np->features & FE_QUAD)
		np->multiplier	= 4;
	अन्यथा अगर	(np->features & FE_DBLR)
		np->multiplier	= 2;
	अन्यथा
		np->multiplier	= 1;

	/*
	 *  Measure SCSI घड़ी frequency क्रम chips 
	 *  it may vary from assumed one.
	 */
	अगर (np->features & FE_VARCLK)
		ncr_अ_लोlock(np, np->multiplier);

	/*
	 * Divisor to be used क्रम async (समयr pre-scaler).
	 */
	i = np->घड़ी_भागn - 1;
	जबतक (--i >= 0) अणु
		अगर (10ul * SCSI_NCR_MIN_ASYNC * np->घड़ी_khz > भाग_10M[i]) अणु
			++i;
			अवरोध;
		पूर्ण
	पूर्ण
	np->rv_scntl3 = i+1;

	/*
	 * Minimum synchronous period factor supported by the chip.
	 * Btw, 'period' is in tenths of nanoseconds.
	 */

	period = (4 * भाग_10M[0] + np->घड़ी_khz - 1) / np->घड़ी_khz;
	अगर	(period <= 250)		np->minsync = 10;
	अन्यथा अगर	(period <= 303)		np->minsync = 11;
	अन्यथा अगर	(period <= 500)		np->minsync = 12;
	अन्यथा				np->minsync = (period + 40 - 1) / 40;

	/*
	 * Check against chip SCSI standard support (SCSI-2,ULTRA,ULTRA2).
	 */

	अगर	(np->minsync < 25 && !(np->features & FE_ULTRA))
		np->minsync = 25;

	/*
	 * Maximum synchronous period factor supported by the chip.
	 */

	period = (11 * भाग_10M[np->घड़ी_भागn - 1]) / (4 * np->घड़ी_khz);
	np->maxsync = period > 2540 ? 254 : period / 10;

	/*
	**	Prepare initial value of other IO रेजिस्टरs
	*/
#अगर defined SCSI_NCR_TRUST_BIOS_SETTING
	np->rv_scntl0	= np->sv_scntl0;
	np->rv_dmode	= np->sv_dmode;
	np->rv_dcntl	= np->sv_dcntl;
	np->rv_ctest0	= np->sv_ctest0;
	np->rv_ctest3	= np->sv_ctest3;
	np->rv_ctest4	= np->sv_ctest4;
	np->rv_ctest5	= np->sv_ctest5;
	burst_max	= burst_code(np->sv_dmode, np->sv_ctest0);
#अन्यथा

	/*
	**	Select burst length (dwords)
	*/
	burst_max	= driver_setup.burst_max;
	अगर (burst_max == 255)
		burst_max = burst_code(np->sv_dmode, np->sv_ctest0);
	अगर (burst_max > 7)
		burst_max = 7;
	अगर (burst_max > np->maxburst)
		burst_max = np->maxburst;

	/*
	**	Select all supported special features
	*/
	अगर (np->features & FE_ERL)
		np->rv_dmode	|= ERL;		/* Enable Read Line */
	अगर (np->features & FE_BOF)
		np->rv_dmode	|= BOF;		/* Burst Opcode Fetch */
	अगर (np->features & FE_ERMP)
		np->rv_dmode	|= ERMP;	/* Enable Read Multiple */
	अगर (np->features & FE_PFEN)
		np->rv_dcntl	|= PFEN;	/* Prefetch Enable */
	अगर (np->features & FE_CLSE)
		np->rv_dcntl	|= CLSE;	/* Cache Line Size Enable */
	अगर (np->features & FE_WRIE)
		np->rv_ctest3	|= WRIE;	/* Write and Invalidate */
	अगर (np->features & FE_DFS)
		np->rv_ctest5	|= DFS;		/* Dma Fअगरo Size */
	अगर (np->features & FE_MUX)
		np->rv_ctest4	|= MUX;		/* Host bus multiplex mode */
	अगर (np->features & FE_EA)
		np->rv_dcntl	|= EA;		/* Enable ACK */
	अगर (np->features & FE_EHP)
		np->rv_ctest0	|= EHP;		/* Even host parity */

	/*
	**	Select some other
	*/
	अगर (driver_setup.master_parity)
		np->rv_ctest4	|= MPEE;	/* Master parity checking */
	अगर (driver_setup.scsi_parity)
		np->rv_scntl0	|= 0x0a;	/*  full arb., ena parity, par->ATN  */

	/*
	**  Get SCSI addr of host adapter (set by bios?).
	*/
	अगर (np->myaddr == 255) अणु
		np->myaddr = INB(nc_scid) & 0x07;
		अगर (!np->myaddr)
			np->myaddr = SCSI_NCR_MYADDR;
	पूर्ण

#पूर्ण_अगर /* SCSI_NCR_TRUST_BIOS_SETTING */

	/*
	 *	Prepare initial io रेजिस्टर bits क्रम burst length
	 */
	ncr_init_burst(np, burst_max);

	/*
	**	Set SCSI BUS mode.
	**
	**	- ULTRA2 chips (895/895A/896) report the current 
	**	  BUS mode through the STEST4 IO रेजिस्टर.
	**	- For previous generation chips (825/825A/875), 
	**	  user has to tell us how to check against HVD, 
	**	  since a 100% safe algorithm is not possible.
	*/
	np->scsi_mode = SMODE_SE;
	अगर (np->features & FE_DIFF) अणु
		चयन(driver_setup.dअगरf_support) अणु
		हाल 4:	/* Trust previous settings अगर present, then GPIO3 */
			अगर (np->sv_scntl3) अणु
				अगर (np->sv_stest2 & 0x20)
					np->scsi_mode = SMODE_HVD;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 3:	/* SYMBIOS controllers report HVD through GPIO3 */
			अगर (INB(nc_gpreg) & 0x08)
				अवरोध;
			fallthrough;
		हाल 2:	/* Set HVD unconditionally */
			np->scsi_mode = SMODE_HVD;
			fallthrough;
		हाल 1:	/* Trust previous settings क्रम HVD */
			अगर (np->sv_stest2 & 0x20)
				np->scsi_mode = SMODE_HVD;
			अवरोध;
		शेष:/* Don't care about HVD */	
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (np->scsi_mode == SMODE_HVD)
		np->rv_stest2 |= 0x20;

	/*
	**	Set LED support from SCRIPTS.
	**	Ignore this feature क्रम boards known to use a 
	**	specअगरic GPIO wiring and क्रम the 895A or 896 
	**	that drive the LED directly.
	**	Also probe initial setting of GPIO0 as output.
	*/
	अगर ((driver_setup.led_pin) &&
	    !(np->features & FE_LEDC) && !(np->sv_gpcntl & 0x01))
		np->features |= FE_LED0;

	/*
	**	Set irq mode.
	*/
	चयन(driver_setup.irqm & 3) अणु
	हाल 2:
		np->rv_dcntl	|= IRQM;
		अवरोध;
	हाल 1:
		np->rv_dcntl	|= (np->sv_dcntl & IRQM);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	**	Configure tarमाला_लो according to driver setup.
	**	Allow to override sync, wide and NOSCAN from 
	**	boot command line.
	*/
	क्रम (i = 0 ; i < MAX_TARGET ; i++) अणु
		काष्ठा tcb *tp = &np->target[i];

		tp->usrsync = driver_setup.शेष_sync;
		tp->usrwide = driver_setup.max_wide;
		tp->usrtags = MAX_TAGS;
		tp->period = 0xffff;
		अगर (!driver_setup.disconnection)
			np->target[i].usrflag = UF_NODISC;
	पूर्ण

	/*
	**	Announce all that stuff to user.
	*/

	prपूर्णांकk(KERN_INFO "%s: ID %d, Fast-%d%s%s\n", ncr_name(np),
		np->myaddr,
		np->minsync < 12 ? 40 : (np->minsync < 25 ? 20 : 10),
		(np->rv_scntl0 & 0xa)	? ", Parity Checking"	: ", NO Parity",
		(np->rv_stest2 & 0x20)	? ", Differential"	: "");

	अगर (bootverbose > 1) अणु
		prपूर्णांकk (KERN_INFO "%s: initial SCNTL3/DMODE/DCNTL/CTEST3/4/5 = "
			"(hex) %02x/%02x/%02x/%02x/%02x/%02x\n",
			ncr_name(np), np->sv_scntl3, np->sv_dmode, np->sv_dcntl,
			np->sv_ctest3, np->sv_ctest4, np->sv_ctest5);

		prपूर्णांकk (KERN_INFO "%s: final   SCNTL3/DMODE/DCNTL/CTEST3/4/5 = "
			"(hex) %02x/%02x/%02x/%02x/%02x/%02x\n",
			ncr_name(np), np->rv_scntl3, np->rv_dmode, np->rv_dcntl,
			np->rv_ctest3, np->rv_ctest4, np->rv_ctest5);
	पूर्ण

	अगर (bootverbose && np->paddr2)
		prपूर्णांकk (KERN_INFO "%s: on-chip RAM at 0x%lx\n",
			ncr_name(np), np->paddr2);
पूर्ण

/*==========================================================
**
**
**	Done SCSI commands list management.
**
**	We करोnnot enter the scsi_करोne() callback immediately 
**	after a command has been seen as completed but we 
**	insert it पूर्णांकo a list which is flushed outside any kind 
**	of driver critical section.
**	This allows to करो minimal stuff under पूर्णांकerrupt and 
**	inside critical sections and to also aव्योम locking up 
**	on recursive calls to driver entry poपूर्णांकs under SMP.
**	In fact, the only kernel poपूर्णांक which is entered by the 
**	driver with a driver lock set is kदो_स्मृति(GFP_ATOMIC) 
**	that shall not reenter the driver under any circumstances,
**	AFAIK.
**
**==========================================================
*/
अटल अंतरभूत व्योम ncr_queue_करोne_cmd(काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd)
अणु
	unmap_scsi_data(np, cmd);
	cmd->host_scribble = (अक्षर *) np->करोne_list;
	np->करोne_list = cmd;
पूर्ण

अटल अंतरभूत व्योम ncr_flush_करोne_cmds(काष्ठा scsi_cmnd *lcmd)
अणु
	काष्ठा scsi_cmnd *cmd;

	जबतक (lcmd) अणु
		cmd = lcmd;
		lcmd = (काष्ठा scsi_cmnd *) cmd->host_scribble;
		cmd->scsi_करोne(cmd);
	पूर्ण
पूर्ण

/*==========================================================
**
**
**	Prepare the next negotiation message अगर needed.
**
**	Fill in the part of message buffer that contains the 
**	negotiation and the nego_status field of the CCB.
**	Returns the size of the message in bytes.
**
**
**==========================================================
*/


अटल पूर्णांक ncr_prepare_nego(काष्ठा ncb *np, काष्ठा ccb *cp, u_अक्षर *msgptr)
अणु
	काष्ठा tcb *tp = &np->target[cp->target];
	पूर्णांक msglen = 0;
	पूर्णांक nego = 0;
	काष्ठा scsi_target *starget = tp->starget;

	/* negotiate wide transfers ?  */
	अगर (!tp->wideकरोne) अणु
		अगर (spi_support_wide(starget)) अणु
			nego = NS_WIDE;
		पूर्ण अन्यथा
			tp->wideकरोne=1;
	पूर्ण

	/* negotiate synchronous transfers?  */
	अगर (!nego && !tp->period) अणु
		अगर (spi_support_sync(starget)) अणु
			nego = NS_SYNC;
		पूर्ण अन्यथा अणु
			tp->period  =0xffff;
			dev_info(&starget->dev, "target did not report SYNC.\n");
		पूर्ण
	पूर्ण

	चयन (nego) अणु
	हाल NS_SYNC:
		msglen += spi_populate_sync_msg(msgptr + msglen,
				tp->maxoffs ? tp->minsync : 0, tp->maxoffs);
		अवरोध;
	हाल NS_WIDE:
		msglen += spi_populate_width_msg(msgptr + msglen, tp->usrwide);
		अवरोध;
	पूर्ण

	cp->nego_status = nego;

	अगर (nego) अणु
		tp->nego_cp = cp;
		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			ncr_prपूर्णांक_msg(cp, nego == NS_WIDE ?
					  "wide msgout":"sync_msgout", msgptr);
		पूर्ण
	पूर्ण

	वापस msglen;
पूर्ण



/*==========================================================
**
**
**	Start execution of a SCSI command.
**	This is called from the generic SCSI driver.
**
**
**==========================================================
*/
अटल पूर्णांक ncr_queue_command (काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा tcb *tp = &np->target[sdev->id];
	काष्ठा lcb *lp = tp->lp[sdev->lun];
	काष्ठा ccb *cp;

	पूर्णांक	segments;
	u_अक्षर	idmsg, *msgptr;
	u32	msglen;
	पूर्णांक	direction;
	u32	lastp, goalp;

	/*---------------------------------------------
	**
	**      Some लघुcuts ...
	**
	**---------------------------------------------
	*/
	अगर ((sdev->id == np->myaddr	  ) ||
		(sdev->id >= MAX_TARGET) ||
		(sdev->lun    >= MAX_LUN   )) अणु
		वापस(DID_BAD_TARGET);
	पूर्ण

	/*---------------------------------------------
	**
	**	Complete the 1st TEST UNIT READY command
	**	with error condition अगर the device is 
	**	flagged NOSCAN, in order to speed up 
	**	the boot.
	**
	**---------------------------------------------
	*/
	अगर ((cmd->cmnd[0] == 0 || cmd->cmnd[0] == 0x12) && 
	    (tp->usrflag & UF_NOSCAN)) अणु
		tp->usrflag &= ~UF_NOSCAN;
		वापस DID_BAD_TARGET;
	पूर्ण

	अगर (DEBUG_FLAGS & DEBUG_TINY) अणु
		PRINT_ADDR(cmd, "CMD=%x ", cmd->cmnd[0]);
	पूर्ण

	/*---------------------------------------------------
	**
	**	Assign a ccb / bind cmd.
	**	If resetting, लघुen settle_समय अगर necessary
	**	in order to aव्योम spurious समयouts.
	**	If resetting or no मुक्त ccb,
	**	insert cmd पूर्णांकo the रुकोing list.
	**
	**----------------------------------------------------
	*/
	अगर (np->settle_समय && cmd->request->समयout >= HZ) अणु
		u_दीर्घ tlimit = jअगरfies + cmd->request->समयout - HZ;
		अगर (समय_after(np->settle_समय, tlimit))
			np->settle_समय = tlimit;
	पूर्ण

	अगर (np->settle_समय || !(cp=ncr_get_ccb (np, cmd))) अणु
		insert_पूर्णांकo_रुकोing_list(np, cmd);
		वापस(DID_OK);
	पूर्ण
	cp->cmd = cmd;

	/*----------------------------------------------------
	**
	**	Build the identअगरy / tag / sdtr message
	**
	**----------------------------------------------------
	*/

	idmsg = IDENTIFY(0, sdev->lun);

	अगर (cp ->tag != NO_TAG ||
		(cp != np->ccb && np->disc && !(tp->usrflag & UF_NODISC)))
		idmsg |= 0x40;

	msgptr = cp->scsi_smsg;
	msglen = 0;
	msgptr[msglen++] = idmsg;

	अगर (cp->tag != NO_TAG) अणु
		अक्षर order = np->order;

		/*
		**	Force ordered tag अगर necessary to aव्योम समयouts 
		**	and to preserve पूर्णांकeractivity.
		*/
		अगर (lp && समय_after(jअगरfies, lp->tags_sसमय)) अणु
			अगर (lp->tags_smap) अणु
				order = ORDERED_QUEUE_TAG;
				अगर ((DEBUG_FLAGS & DEBUG_TAGS)||bootverbose>2)अणु 
					PRINT_ADDR(cmd,
						"ordered tag forced.\n");
				पूर्ण
			पूर्ण
			lp->tags_sसमय = jअगरfies + 3*HZ;
			lp->tags_smap = lp->tags_umap;
		पूर्ण

		अगर (order == 0) अणु
			/*
			**	Ordered ग_लिखो ops, unordered पढ़ो ops.
			*/
			चयन (cmd->cmnd[0]) अणु
			हाल 0x08:  /* READ_SMALL (6) */
			हाल 0x28:  /* READ_BIG  (10) */
			हाल 0xa8:  /* READ_HUGE (12) */
				order = SIMPLE_QUEUE_TAG;
				अवरोध;
			शेष:
				order = ORDERED_QUEUE_TAG;
			पूर्ण
		पूर्ण
		msgptr[msglen++] = order;
		/*
		**	Actual tags are numbered 1,3,5,..2*MAXTAGS+1,
		**	since we may have to deal with devices that have 
		**	problems with #TAG 0 or too great #TAG numbers.
		*/
		msgptr[msglen++] = (cp->tag << 1) + 1;
	पूर्ण

	/*----------------------------------------------------
	**
	**	Build the data descriptors
	**
	**----------------------------------------------------
	*/

	direction = cmd->sc_data_direction;
	अगर (direction != DMA_NONE) अणु
		segments = ncr_scatter(np, cp, cp->cmd);
		अगर (segments < 0) अणु
			ncr_मुक्त_ccb(np, cp);
			वापस(DID_ERROR);
		पूर्ण
	पूर्ण
	अन्यथा अणु
		cp->data_len = 0;
		segments = 0;
	पूर्ण

	/*---------------------------------------------------
	**
	**	negotiation required?
	**
	**	(nego_status is filled by ncr_prepare_nego())
	**
	**---------------------------------------------------
	*/

	cp->nego_status = 0;

	अगर ((!tp->wideकरोne || !tp->period) && !tp->nego_cp && lp) अणु
		msglen += ncr_prepare_nego (np, cp, msgptr + msglen);
	पूर्ण

	/*----------------------------------------------------
	**
	**	Determine xfer direction.
	**
	**----------------------------------------------------
	*/
	अगर (!cp->data_len)
		direction = DMA_NONE;

	/*
	**	If data direction is BIसूचीECTIONAL, speculate FROM_DEVICE
	**	but prepare alternate poपूर्णांकers क्रम TO_DEVICE in हाल 
	**	of our speculation will be just wrong.
	**	SCRIPTS will swap values अगर needed.
	*/
	चयन(direction) अणु
	हाल DMA_BIसूचीECTIONAL:
	हाल DMA_TO_DEVICE:
		goalp = NCB_SCRIPT_PHYS (np, data_out2) + 8;
		अगर (segments <= MAX_SCATTERL)
			lastp = goalp - 8 - (segments * 16);
		अन्यथा अणु
			lastp = NCB_SCRIPTH_PHYS (np, hdata_out2);
			lastp -= (segments - MAX_SCATTERL) * 16;
		पूर्ण
		अगर (direction != DMA_BIसूचीECTIONAL)
			अवरोध;
		cp->phys.header.wgoalp	= cpu_to_scr(goalp);
		cp->phys.header.wlastp	= cpu_to_scr(lastp);
		fallthrough;
	हाल DMA_FROM_DEVICE:
		goalp = NCB_SCRIPT_PHYS (np, data_in2) + 8;
		अगर (segments <= MAX_SCATTERL)
			lastp = goalp - 8 - (segments * 16);
		अन्यथा अणु
			lastp = NCB_SCRIPTH_PHYS (np, hdata_in2);
			lastp -= (segments - MAX_SCATTERL) * 16;
		पूर्ण
		अवरोध;
	शेष:
	हाल DMA_NONE:
		lastp = goalp = NCB_SCRIPT_PHYS (np, no_data);
		अवरोध;
	पूर्ण

	/*
	**	Set all poपूर्णांकers values needed by SCRIPTS.
	**	If direction is unknown, start at data_io.
	*/
	cp->phys.header.lastp = cpu_to_scr(lastp);
	cp->phys.header.goalp = cpu_to_scr(goalp);

	अगर (direction == DMA_BIसूचीECTIONAL)
		cp->phys.header.savep = 
			cpu_to_scr(NCB_SCRIPTH_PHYS (np, data_io));
	अन्यथा
		cp->phys.header.savep= cpu_to_scr(lastp);

	/*
	**	Save the initial data poपूर्णांकer in order to be able 
	**	to reकरो the command.
	*/
	cp->startp = cp->phys.header.savep;

	/*----------------------------------------------------
	**
	**	fill in ccb
	**
	**----------------------------------------------------
	**
	**
	**	physical -> भव backlink
	**	Generic SCSI command
	*/

	/*
	**	Startqueue
	*/
	cp->start.schedule.l_paddr   = cpu_to_scr(NCB_SCRIPT_PHYS (np, select));
	cp->restart.schedule.l_paddr = cpu_to_scr(NCB_SCRIPT_PHYS (np, resel_dsa));
	/*
	**	select
	*/
	cp->phys.select.sel_id		= sdev_id(sdev);
	cp->phys.select.sel_scntl3	= tp->wval;
	cp->phys.select.sel_sxfer	= tp->sval;
	/*
	**	message
	*/
	cp->phys.smsg.addr		= cpu_to_scr(CCB_PHYS (cp, scsi_smsg));
	cp->phys.smsg.size		= cpu_to_scr(msglen);

	/*
	**	command
	*/
	स_नकल(cp->cdb_buf, cmd->cmnd, min_t(पूर्णांक, cmd->cmd_len, माप(cp->cdb_buf)));
	cp->phys.cmd.addr		= cpu_to_scr(CCB_PHYS (cp, cdb_buf[0]));
	cp->phys.cmd.size		= cpu_to_scr(cmd->cmd_len);

	/*
	**	status
	*/
	cp->actualquirks		= 0;
	cp->host_status			= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;
	cp->scsi_status			= SAM_STAT_ILLEGAL;
	cp->parity_status		= 0;

	cp->xerr_status			= XE_OK;
#अगर 0
	cp->sync_status			= tp->sval;
	cp->wide_status			= tp->wval;
#पूर्ण_अगर

	/*----------------------------------------------------
	**
	**	Critical region: start this job.
	**
	**----------------------------------------------------
	*/

	/* activate this job.  */
	cp->magic		= CCB_MAGIC;

	/*
	**	insert next CCBs पूर्णांकo start queue.
	**	2 max at a समय is enough to flush the CCB रुको queue.
	*/
	cp->स्वतः_sense = 0;
	अगर (lp)
		ncr_start_next_ccb(np, lp, 2);
	अन्यथा
		ncr_put_start_queue(np, cp);

	/* Command is successfully queued.  */

	वापस DID_OK;
पूर्ण


/*==========================================================
**
**
**	Insert a CCB पूर्णांकo the start queue and wake up the 
**	SCRIPTS processor.
**
**
**==========================================================
*/

अटल व्योम ncr_start_next_ccb(काष्ठा ncb *np, काष्ठा lcb *lp, पूर्णांक maxn)
अणु
	काष्ठा list_head *qp;
	काष्ठा ccb *cp;

	अगर (lp->held_ccb)
		वापस;

	जबतक (maxn-- && lp->queuedccbs < lp->queuedepth) अणु
		qp = ncr_list_pop(&lp->रुको_ccbq);
		अगर (!qp)
			अवरोध;
		++lp->queuedccbs;
		cp = list_entry(qp, काष्ठा ccb, link_ccbq);
		list_add_tail(qp, &lp->busy_ccbq);
		lp->jump_ccb[cp->tag == NO_TAG ? 0 : cp->tag] =
			cpu_to_scr(CCB_PHYS (cp, restart));
		ncr_put_start_queue(np, cp);
	पूर्ण
पूर्ण

अटल व्योम ncr_put_start_queue(काष्ठा ncb *np, काष्ठा ccb *cp)
अणु
	u16	qidx;

	/*
	**	insert पूर्णांकo start queue.
	*/
	अगर (!np->squeueput) np->squeueput = 1;
	qidx = np->squeueput + 2;
	अगर (qidx >= MAX_START + MAX_START) qidx = 1;

	np->scripth->tryloop [qidx] = cpu_to_scr(NCB_SCRIPT_PHYS (np, idle));
	MEMORY_BARRIER();
	np->scripth->tryloop [np->squeueput] = cpu_to_scr(CCB_PHYS (cp, start));

	np->squeueput = qidx;
	++np->queuedccbs;
	cp->queued = 1;

	अगर (DEBUG_FLAGS & DEBUG_QUEUE)
		prपूर्णांकk ("%s: queuepos=%d.\n", ncr_name (np), np->squeueput);

	/*
	**	Script processor may be रुकोing क्रम reselect.
	**	Wake it up.
	*/
	MEMORY_BARRIER();
	OUTB (nc_istat, SIGP);
पूर्ण


अटल पूर्णांक ncr_reset_scsi_bus(काष्ठा ncb *np, पूर्णांक enab_पूर्णांक, पूर्णांक settle_delay)
अणु
	u32 term;
	पूर्णांक retv = 0;

	np->settle_समय	= jअगरfies + settle_delay * HZ;

	अगर (bootverbose > 1)
		prपूर्णांकk("%s: resetting, "
			"command processing suspended for %d seconds\n",
			ncr_name(np), settle_delay);

	ncr_chip_reset(np, 100);
	udelay(2000);	/* The 895 needs समय क्रम the bus mode to settle */
	अगर (enab_पूर्णांक)
		OUTW (nc_sien, RST);
	/*
	**	Enable Tolerant, reset IRQD अगर present and 
	**	properly set IRQ mode, prior to resetting the bus.
	*/
	OUTB (nc_stest3, TE);
	OUTB (nc_scntl1, CRST);
	udelay(200);

	अगर (!driver_setup.bus_check)
		जाओ out;
	/*
	**	Check क्रम no terminators or SCSI bus लघुs to ground.
	**	Read SCSI data bus, data parity bits and control संकेतs.
	**	We are expecting RESET to be TRUE and other संकेतs to be 
	**	FALSE.
	*/

	term =	INB(nc_sstat0);
	term =	((term & 2) << 7) + ((term & 1) << 17);	/* rst sdp0 */
	term |= ((INB(nc_sstat2) & 0x01) << 26) |	/* sdp1     */
		((INW(nc_sbdl) & 0xff)   << 9)  |	/* d7-0     */
		((INW(nc_sbdl) & 0xff00) << 10) |	/* d15-8    */
		INB(nc_sbcl);	/* req ack bsy sel atn msg cd io    */

	अगर (!(np->features & FE_WIDE))
		term &= 0x3ffff;

	अगर (term != (2<<7)) अणु
		prपूर्णांकk("%s: suspicious SCSI data while resetting the BUS.\n",
			ncr_name(np));
		prपूर्णांकk("%s: %sdp0,d7-0,rst,req,ack,bsy,sel,atn,msg,c/d,i/o = "
			"0x%lx, expecting 0x%lx\n",
			ncr_name(np),
			(np->features & FE_WIDE) ? "dp1,d15-8," : "",
			(u_दीर्घ)term, (u_दीर्घ)(2<<7));
		अगर (driver_setup.bus_check == 1)
			retv = 1;
	पूर्ण
out:
	OUTB (nc_scntl1, 0);
	वापस retv;
पूर्ण

/*
 * Start reset process.
 * If reset in progress करो nothing.
 * The पूर्णांकerrupt handler will reinitialize the chip.
 * The समयout handler will रुको क्रम settle_समय beक्रमe 
 * clearing it and so resuming command processing.
 */
अटल व्योम ncr_start_reset(काष्ठा ncb *np)
अणु
	अगर (!np->settle_समय) अणु
		ncr_reset_scsi_bus(np, 1, driver_setup.settle_delay);
 	पूर्ण
पूर्ण
 
/*==========================================================
**
**
**	Reset the SCSI BUS.
**	This is called from the generic SCSI driver.
**
**
**==========================================================
*/
अटल पूर्णांक ncr_reset_bus (काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd, पूर्णांक sync_reset)
अणु
/*	काष्ठा scsi_device        *device    = cmd->device; */
	काष्ठा ccb *cp;
	पूर्णांक found;

/*
 * Return immediately अगर reset is in progress.
 */
	अगर (np->settle_समय) अणु
		वापस FAILED;
	पूर्ण
/*
 * Start the reset process.
 * The script processor is then assumed to be stopped.
 * Commands will now be queued in the रुकोing list until a settle 
 * delay of 2 seconds will be completed.
 */
	ncr_start_reset(np);
/*
 * First, look in the wakeup list
 */
	क्रम (found=0, cp=np->ccb; cp; cp=cp->link_ccb) अणु
		/*
		**	look क्रम the ccb of this command.
		*/
		अगर (cp->host_status == HS_IDLE) जारी;
		अगर (cp->cmd == cmd) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
/*
 * Then, look in the रुकोing list
 */
	अगर (!found && retrieve_from_रुकोing_list(0, np, cmd))
		found = 1;
/*
 * Wake-up all aरुकोing commands with DID_RESET.
 */
	reset_रुकोing_list(np);
/*
 * Wake-up all pending commands with HS_RESET -> DID_RESET.
 */
	ncr_wakeup(np, HS_RESET);
/*
 * If the involved command was not in a driver queue, and the 
 * scsi driver told us reset is synchronous, and the command is not 
 * currently in the रुकोing list, complete it with DID_RESET status,
 * in order to keep it alive.
 */
	अगर (!found && sync_reset && !retrieve_from_रुकोing_list(0, np, cmd)) अणु
		set_host_byte(cmd, DID_RESET);
		ncr_queue_करोne_cmd(np, cmd);
	पूर्ण

	वापस SUCCESS;
पूर्ण

#अगर 0 /* unused and broken.. */
/*==========================================================
**
**
**	Abort an SCSI command.
**	This is called from the generic SCSI driver.
**
**
**==========================================================
*/
अटल पूर्णांक ncr_पात_command (काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd)
अणु
/*	काष्ठा scsi_device        *device    = cmd->device; */
	काष्ठा ccb *cp;
	पूर्णांक found;
	पूर्णांक retv;

/*
 * First, look क्रम the scsi command in the रुकोing list
 */
	अगर (हटाओ_from_रुकोing_list(np, cmd)) अणु
		set_host_byte(cmd, DID_ABORT);
		ncr_queue_करोne_cmd(np, cmd);
		वापस SCSI_ABORT_SUCCESS;
	पूर्ण

/*
 * Then, look in the wakeup list
 */
	क्रम (found=0, cp=np->ccb; cp; cp=cp->link_ccb) अणु
		/*
		**	look क्रम the ccb of this command.
		*/
		अगर (cp->host_status == HS_IDLE) जारी;
		अगर (cp->cmd == cmd) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		वापस SCSI_ABORT_NOT_RUNNING;
	पूर्ण

	अगर (np->settle_समय) अणु
		वापस SCSI_ABORT_SNOOZE;
	पूर्ण

	/*
	**	If the CCB is active, patch schedule jumps क्रम the 
	**	script to पात the command.
	*/

	चयन(cp->host_status) अणु
	हाल HS_BUSY:
	हाल HS_NEGOTIATE:
		prपूर्णांकk ("%s: abort ccb=%p (cancel)\n", ncr_name (np), cp);
			cp->start.schedule.l_paddr =
				cpu_to_scr(NCB_SCRIPTH_PHYS (np, cancel));
		retv = SCSI_ABORT_PENDING;
		अवरोध;
	हाल HS_DISCONNECT:
		cp->restart.schedule.l_paddr =
				cpu_to_scr(NCB_SCRIPTH_PHYS (np, पात));
		retv = SCSI_ABORT_PENDING;
		अवरोध;
	शेष:
		retv = SCSI_ABORT_NOT_RUNNING;
		अवरोध;

	पूर्ण

	/*
	**      If there are no requests, the script
	**      processor will sleep on SEL_WAIT_RESEL.
	**      Let's wake it up, since it may have to work.
	*/
	OUTB (nc_istat, SIGP);

	वापस retv;
पूर्ण
#पूर्ण_अगर

अटल व्योम ncr_detach(काष्ठा ncb *np)
अणु
	काष्ठा ccb *cp;
	काष्ठा tcb *tp;
	काष्ठा lcb *lp;
	पूर्णांक target, lun;
	पूर्णांक i;
	अक्षर inst_name[16];

	/* Local copy so we करोn't access np after मुक्तing it! */
	strlcpy(inst_name, ncr_name(np), माप(inst_name));

	prपूर्णांकk("%s: releasing host resources\n", ncr_name(np));

/*
**	Stop the ncr_समयout process
**	Set release_stage to 1 and रुको that ncr_समयout() set it to 2.
*/

#अगर_घोषित DEBUG_NCR53C8XX
	prपूर्णांकk("%s: stopping the timer\n", ncr_name(np));
#पूर्ण_अगर
	np->release_stage = 1;
	क्रम (i = 50 ; i && np->release_stage != 2 ; i--)
		mdelay(100);
	अगर (np->release_stage != 2)
		prपूर्णांकk("%s: the timer seems to be already stopped\n", ncr_name(np));
	अन्यथा np->release_stage = 2;

/*
**	Disable chip पूर्णांकerrupts
*/

#अगर_घोषित DEBUG_NCR53C8XX
	prपूर्णांकk("%s: disabling chip interrupts\n", ncr_name(np));
#पूर्ण_अगर
	OUTW (nc_sien , 0);
	OUTB (nc_dien , 0);

	/*
	**	Reset NCR chip
	**	Restore bios setting क्रम स्वतःmatic घड़ी detection.
	*/

	prपूर्णांकk("%s: resetting chip\n", ncr_name(np));
	ncr_chip_reset(np, 100);

	OUTB(nc_dmode,	np->sv_dmode);
	OUTB(nc_dcntl,	np->sv_dcntl);
	OUTB(nc_ctest0,	np->sv_ctest0);
	OUTB(nc_ctest3,	np->sv_ctest3);
	OUTB(nc_ctest4,	np->sv_ctest4);
	OUTB(nc_ctest5,	np->sv_ctest5);
	OUTB(nc_gpcntl,	np->sv_gpcntl);
	OUTB(nc_stest2,	np->sv_stest2);

	ncr_selectघड़ी(np, np->sv_scntl3);

	/*
	**	Free allocated ccb(s)
	*/

	जबतक ((cp=np->ccb->link_ccb) != शून्य) अणु
		np->ccb->link_ccb = cp->link_ccb;
		अगर (cp->host_status) अणु
		prपूर्णांकk("%s: shall free an active ccb (host_status=%d)\n",
			ncr_name(np), cp->host_status);
		पूर्ण
#अगर_घोषित DEBUG_NCR53C8XX
	prपूर्णांकk("%s: freeing ccb (%lx)\n", ncr_name(np), (u_दीर्घ) cp);
#पूर्ण_अगर
		m_मुक्त_dma(cp, माप(*cp), "CCB");
	पूर्ण

	/* Free allocated tp(s) */

	क्रम (target = 0; target < MAX_TARGET ; target++) अणु
		tp=&np->target[target];
		क्रम (lun = 0 ; lun < MAX_LUN ; lun++) अणु
			lp = tp->lp[lun];
			अगर (lp) अणु
#अगर_घोषित DEBUG_NCR53C8XX
	prपूर्णांकk("%s: freeing lp (%lx)\n", ncr_name(np), (u_दीर्घ) lp);
#पूर्ण_अगर
				अगर (lp->jump_ccb != &lp->jump_ccb_0)
					m_मुक्त_dma(lp->jump_ccb,256,"JUMP_CCB");
				m_मुक्त_dma(lp, माप(*lp), "LCB");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (np->scripth0)
		m_मुक्त_dma(np->scripth0, माप(काष्ठा scripth), "SCRIPTH");
	अगर (np->script0)
		m_मुक्त_dma(np->script0, माप(काष्ठा script), "SCRIPT");
	अगर (np->ccb)
		m_मुक्त_dma(np->ccb, माप(काष्ठा ccb), "CCB");
	m_मुक्त_dma(np, माप(काष्ठा ncb), "NCB");

	prपूर्णांकk("%s: host resources successfully released\n", inst_name);
पूर्ण

/*==========================================================
**
**
**	Complete execution of a SCSI command.
**	Signal completion to the generic SCSI driver.
**
**
**==========================================================
*/

व्योम ncr_complete (काष्ठा ncb *np, काष्ठा ccb *cp)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा tcb *tp;
	काष्ठा lcb *lp;

	/*
	**	Sanity check
	*/

	अगर (!cp || cp->magic != CCB_MAGIC || !cp->cmd)
		वापस;

	/*
	**	Prपूर्णांक minimal debug inक्रमmation.
	*/

	अगर (DEBUG_FLAGS & DEBUG_TINY)
		prपूर्णांकk ("CCB=%lx STAT=%x/%x\n", (अचिन्हित दीर्घ)cp,
			cp->host_status,cp->scsi_status);

	/*
	**	Get command, target and lun poपूर्णांकers.
	*/

	cmd = cp->cmd;
	cp->cmd = शून्य;
	tp = &np->target[cmd->device->id];
	lp = tp->lp[cmd->device->lun];

	/*
	**	We करोnnot queue more than 1 ccb per target 
	**	with negotiation at any समय. If this ccb was 
	**	used क्रम negotiation, clear this info in the tcb.
	*/

	अगर (cp == tp->nego_cp)
		tp->nego_cp = शून्य;

	/*
	**	If स्वतः-sense perक्रमmed, change scsi status.
	*/
	अगर (cp->स्वतः_sense) अणु
		cp->scsi_status = cp->स्वतः_sense;
	पूर्ण

	/*
	**	If we were recovering from queue full or perक्रमming 
	**	स्वतः-sense, requeue skipped CCBs to the रुको queue.
	*/

	अगर (lp && lp->held_ccb) अणु
		अगर (cp == lp->held_ccb) अणु
			list_splice_init(&lp->skip_ccbq, &lp->रुको_ccbq);
			lp->held_ccb = शून्य;
		पूर्ण
	पूर्ण

	/*
	**	Check क्रम parity errors.
	*/

	अगर (cp->parity_status > 1) अणु
		PRINT_ADDR(cmd, "%d parity error(s).\n",cp->parity_status);
	पूर्ण

	/*
	**	Check क्रम extended errors.
	*/

	अगर (cp->xerr_status != XE_OK) अणु
		चयन (cp->xerr_status) अणु
		हाल XE_EXTRA_DATA:
			PRINT_ADDR(cmd, "extraneous data discarded.\n");
			अवरोध;
		हाल XE_BAD_PHASE:
			PRINT_ADDR(cmd, "invalid scsi phase (4/5).\n");
			अवरोध;
		शेष:
			PRINT_ADDR(cmd, "extended error %d.\n",
					cp->xerr_status);
			अवरोध;
		पूर्ण
		अगर (cp->host_status==HS_COMPLETE)
			cp->host_status = HS_FAIL;
	पूर्ण

	/*
	**	Prपूर्णांक out any error क्रम debugging purpose.
	*/
	अगर (DEBUG_FLAGS & (DEBUG_RESULT|DEBUG_TINY)) अणु
		अगर (cp->host_status != HS_COMPLETE ||
		    cp->scsi_status != SAM_STAT_GOOD) अणु
			PRINT_ADDR(cmd, "ERROR: cmd=%x host_status=%x "
					"scsi_status=%x\n", cmd->cmnd[0],
					cp->host_status, cp->scsi_status);
		पूर्ण
	पूर्ण

	/*
	**	Check the status.
	*/
	cmd->result = 0;
	अगर (   (cp->host_status == HS_COMPLETE)
		&& (cp->scsi_status == SAM_STAT_GOOD ||
		    cp->scsi_status == SAM_STAT_CONDITION_MET)) अणु
		/*
		 *	All went well (GOOD status).
		 *	CONDITION MET status is वापसed on
		 *	`Pre-Fetch' or `Search data' success.
		 */
		set_status_byte(cmd, cp->scsi_status);

		/*
		**	@RESID@
		**	Could dig out the correct value क्रम resid,
		**	but it would be quite complicated.
		*/
		/* अगर (cp->phys.header.lastp != cp->phys.header.goalp) */

		/*
		**	Allocate the lcb अगर not yet.
		*/
		अगर (!lp)
			ncr_alloc_lcb (np, cmd->device->id, cmd->device->lun);

		tp->bytes     += cp->data_len;
		tp->transfers ++;

		/*
		**	If tags was reduced due to queue full,
		**	increase tags अगर 1000 good status received.
		*/
		अगर (lp && lp->usetags && lp->numtags < lp->maxtags) अणु
			++lp->num_good;
			अगर (lp->num_good >= 1000) अणु
				lp->num_good = 0;
				++lp->numtags;
				ncr_setup_tags (np, cmd->device);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर ((cp->host_status == HS_COMPLETE)
		&& (cp->scsi_status == SAM_STAT_CHECK_CONDITION)) अणु
		/*
		**   Check condition code
		*/
		set_status_byte(cmd, SAM_STAT_CHECK_CONDITION);

		/*
		**	Copy back sense data to caller's buffer.
		*/
		स_नकल(cmd->sense_buffer, cp->sense_buf,
		       min_t(माप_प्रकार, SCSI_SENSE_BUFFERSIZE,
			     माप(cp->sense_buf)));

		अगर (DEBUG_FLAGS & (DEBUG_RESULT|DEBUG_TINY)) अणु
			u_अक्षर *p = cmd->sense_buffer;
			पूर्णांक i;
			PRINT_ADDR(cmd, "sense data:");
			क्रम (i=0; i<14; i++) prपूर्णांकk (" %x", *p++);
			prपूर्णांकk (".\n");
		पूर्ण
	पूर्ण अन्यथा अगर ((cp->host_status == HS_COMPLETE)
		&& (cp->scsi_status == SAM_STAT_RESERVATION_CONFLICT)) अणु
		/*
		**   Reservation Conflict condition code
		*/
		set_status_byte(cmd, SAM_STAT_RESERVATION_CONFLICT);

	पूर्ण अन्यथा अगर ((cp->host_status == HS_COMPLETE)
		&& (cp->scsi_status == SAM_STAT_BUSY ||
		    cp->scsi_status == SAM_STAT_TASK_SET_FULL)) अणु

		/*
		**   Target is busy.
		*/
		set_status_byte(cmd, cp->scsi_status);

	पूर्ण अन्यथा अगर ((cp->host_status == HS_SEL_TIMEOUT)
		|| (cp->host_status == HS_TIMEOUT)) अणु

		/*
		**   No response
		*/
		set_status_byte(cmd, cp->scsi_status);
		set_host_byte(cmd, DID_TIME_OUT);

	पूर्ण अन्यथा अगर (cp->host_status == HS_RESET) अणु

		/*
		**   SCSI bus reset
		*/
		set_status_byte(cmd, cp->scsi_status);
		set_host_byte(cmd, DID_RESET);

	पूर्ण अन्यथा अगर (cp->host_status == HS_ABORTED) अणु

		/*
		**   Transfer पातed
		*/
		set_status_byte(cmd, cp->scsi_status);
		set_host_byte(cmd, DID_ABORT);

	पूर्ण अन्यथा अणु

		/*
		**  Other protocol messes
		*/
		PRINT_ADDR(cmd, "COMMAND FAILED (%x %x) @%p.\n",
			cp->host_status, cp->scsi_status, cp);

		set_status_byte(cmd, cp->scsi_status);
		set_host_byte(cmd, DID_ERROR);
	पूर्ण

	/*
	**	trace output
	*/

	अगर (tp->usrflag & UF_TRACE) अणु
		u_अक्षर * p;
		पूर्णांक i;
		PRINT_ADDR(cmd, " CMD:");
		p = (u_अक्षर*) &cmd->cmnd[0];
		क्रम (i=0; i<cmd->cmd_len; i++) prपूर्णांकk (" %x", *p++);

		अगर (cp->host_status==HS_COMPLETE) अणु
			चयन (cp->scsi_status) अणु
			हाल SAM_STAT_GOOD:
				prपूर्णांकk ("  GOOD");
				अवरोध;
			हाल SAM_STAT_CHECK_CONDITION:
				prपूर्णांकk ("  SENSE:");
				p = (u_अक्षर*) &cmd->sense_buffer;
				क्रम (i=0; i<14; i++)
					prपूर्णांकk (" %x", *p++);
				अवरोध;
			शेष:
				prपूर्णांकk ("  STAT: %x\n", cp->scsi_status);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा prपूर्णांकk ("  HOSTERROR: %x", cp->host_status);
		prपूर्णांकk ("\n");
	पूर्ण

	/*
	**	Free this ccb
	*/
	ncr_मुक्त_ccb (np, cp);

	/*
	**	requeue aरुकोing scsi commands क्रम this lun.
	*/
	अगर (lp && lp->queuedccbs < lp->queuedepth &&
	    !list_empty(&lp->रुको_ccbq))
		ncr_start_next_ccb(np, lp, 2);

	/*
	**	requeue aरुकोing scsi commands क्रम this controller.
	*/
	अगर (np->रुकोing_list)
		requeue_रुकोing_list(np);

	/*
	**	संकेत completion to generic driver.
	*/
	ncr_queue_करोne_cmd(np, cmd);
पूर्ण

/*==========================================================
**
**
**	Signal all (or one) control block करोne.
**
**
**==========================================================
*/

/*
**	This CCB has been skipped by the NCR.
**	Queue it in the corresponding unit queue.
*/
अटल व्योम ncr_ccb_skipped(काष्ठा ncb *np, काष्ठा ccb *cp)
अणु
	काष्ठा tcb *tp = &np->target[cp->target];
	काष्ठा lcb *lp = tp->lp[cp->lun];

	अगर (lp && cp != np->ccb) अणु
		cp->host_status &= ~HS_SKIPMASK;
		cp->start.schedule.l_paddr = 
			cpu_to_scr(NCB_SCRIPT_PHYS (np, select));
		list_move_tail(&cp->link_ccbq, &lp->skip_ccbq);
		अगर (cp->queued) अणु
			--lp->queuedccbs;
		पूर्ण
	पूर्ण
	अगर (cp->queued) अणु
		--np->queuedccbs;
		cp->queued = 0;
	पूर्ण
पूर्ण

/*
**	The NCR has completed CCBs.
**	Look at the DONE QUEUE अगर enabled, otherwise scan all CCBs
*/
व्योम ncr_wakeup_करोne (काष्ठा ncb *np)
अणु
	काष्ठा ccb *cp;
#अगर_घोषित SCSI_NCR_CCB_DONE_SUPPORT
	पूर्णांक i, j;

	i = np->ccb_करोne_ic;
	जबतक (1) अणु
		j = i+1;
		अगर (j >= MAX_DONE)
			j = 0;

		cp = np->ccb_करोne[j];
		अगर (!CCB_DONE_VALID(cp))
			अवरोध;

		np->ccb_करोne[j] = (काष्ठा ccb *)CCB_DONE_EMPTY;
		np->scripth->करोne_queue[5*j + 4] =
				cpu_to_scr(NCB_SCRIPT_PHYS (np, करोne_plug));
		MEMORY_BARRIER();
		np->scripth->करोne_queue[5*i + 4] =
				cpu_to_scr(NCB_SCRIPT_PHYS (np, करोne_end));

		अगर (cp->host_status & HS_DONEMASK)
			ncr_complete (np, cp);
		अन्यथा अगर (cp->host_status & HS_SKIPMASK)
			ncr_ccb_skipped (np, cp);

		i = j;
	पूर्ण
	np->ccb_करोne_ic = i;
#अन्यथा
	cp = np->ccb;
	जबतक (cp) अणु
		अगर (cp->host_status & HS_DONEMASK)
			ncr_complete (np, cp);
		अन्यथा अगर (cp->host_status & HS_SKIPMASK)
			ncr_ccb_skipped (np, cp);
		cp = cp->link_ccb;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
**	Complete all active CCBs.
*/
व्योम ncr_wakeup (काष्ठा ncb *np, u_दीर्घ code)
अणु
	काष्ठा ccb *cp = np->ccb;

	जबतक (cp) अणु
		अगर (cp->host_status != HS_IDLE) अणु
			cp->host_status = code;
			ncr_complete (np, cp);
		पूर्ण
		cp = cp->link_ccb;
	पूर्ण
पूर्ण

/*
** Reset ncr chip.
*/

/* Some initialisation must be करोne immediately following reset, क्रम 53c720,
 * at least.  EA (dcntl bit 5) isn't set here as it is set once only in
 * the _detect function.
 */
अटल व्योम ncr_chip_reset(काष्ठा ncb *np, पूर्णांक delay)
अणु
	OUTB (nc_istat,  SRST);
	udelay(delay);
	OUTB (nc_istat,  0   );

	अगर (np->features & FE_EHP)
		OUTB (nc_ctest0, EHP);
	अगर (np->features & FE_MUX)
		OUTB (nc_ctest4, MUX);
पूर्ण


/*==========================================================
**
**
**	Start NCR chip.
**
**
**==========================================================
*/

व्योम ncr_init (काष्ठा ncb *np, पूर्णांक reset, अक्षर * msg, u_दीर्घ code)
अणु
 	पूर्णांक	i;

 	/*
	**	Reset chip अगर asked, otherwise just clear fअगरos.
 	*/

	अगर (reset) अणु
		OUTB (nc_istat,  SRST);
		udelay(100);
	पूर्ण
	अन्यथा अणु
		OUTB (nc_stest3, TE|CSF);
		OUTONB (nc_ctest3, CLF);
	पूर्ण
 
	/*
	**	Message.
	*/

	अगर (msg) prपूर्णांकk (KERN_INFO "%s: restart (%s).\n", ncr_name (np), msg);

	/*
	**	Clear Start Queue
	*/
	np->queuedepth = MAX_START - 1;	/* 1 entry needed as end marker */
	क्रम (i = 1; i < MAX_START + MAX_START; i += 2)
		np->scripth0->tryloop[i] =
				cpu_to_scr(NCB_SCRIPT_PHYS (np, idle));

	/*
	**	Start at first entry.
	*/
	np->squeueput = 0;
	np->script0->startpos[0] = cpu_to_scr(NCB_SCRIPTH_PHYS (np, tryloop));

#अगर_घोषित SCSI_NCR_CCB_DONE_SUPPORT
	/*
	**	Clear Done Queue
	*/
	क्रम (i = 0; i < MAX_DONE; i++) अणु
		np->ccb_करोne[i] = (काष्ठा ccb *)CCB_DONE_EMPTY;
		np->scripth0->करोne_queue[5*i + 4] =
			cpu_to_scr(NCB_SCRIPT_PHYS (np, करोne_end));
	पूर्ण
#पूर्ण_अगर

	/*
	**	Start at first entry.
	*/
	np->script0->करोne_pos[0] = cpu_to_scr(NCB_SCRIPTH_PHYS (np,करोne_queue));
	np->ccb_करोne_ic = MAX_DONE-1;
	np->scripth0->करोne_queue[5*(MAX_DONE-1) + 4] =
			cpu_to_scr(NCB_SCRIPT_PHYS (np, करोne_plug));

	/*
	**	Wakeup all pending jobs.
	*/
	ncr_wakeup (np, code);

	/*
	**	Init chip.
	*/

	/*
	** Remove reset; big delay because the 895 needs समय क्रम the
	** bus mode to settle
	*/
	ncr_chip_reset(np, 2000);

	OUTB (nc_scntl0, np->rv_scntl0 | 0xc0);
					/*  full arb., ena parity, par->ATN  */
	OUTB (nc_scntl1, 0x00);		/*  odd parity, and हटाओ CRST!! */

	ncr_selectघड़ी(np, np->rv_scntl3);	/* Select SCSI घड़ी */

	OUTB (nc_scid  , RRE|np->myaddr);	/* Adapter SCSI address */
	OUTW (nc_respid, 1ul<<np->myaddr);	/* Id to respond to */
	OUTB (nc_istat , SIGP	);		/*  Signal Process */
	OUTB (nc_dmode , np->rv_dmode);		/* Burst length, dma mode */
	OUTB (nc_ctest5, np->rv_ctest5);	/* Large fअगरo + large burst */

	OUTB (nc_dcntl , NOCOM|np->rv_dcntl);	/* Protect SFBR */
	OUTB (nc_ctest0, np->rv_ctest0);	/* 720: CDIS and EHP */
	OUTB (nc_ctest3, np->rv_ctest3);	/* Write and invalidate */
	OUTB (nc_ctest4, np->rv_ctest4);	/* Master parity checking */

	OUTB (nc_stest2, EXT|np->rv_stest2);	/* Extended Sreq/Sack filtering */
	OUTB (nc_stest3, TE);			/* TolerANT enable */
	OUTB (nc_sसमय0, 0x0c	);		/* HTH disabled  STO 0.25 sec */

	/*
	**	Disable disconnects.
	*/

	np->disc = 0;

	/*
	**    Enable GPIO0 pin क्रम writing अगर LED support.
	*/

	अगर (np->features & FE_LED0) अणु
		OUTOFFB (nc_gpcntl, 0x01);
	पूर्ण

	/*
	**      enable पूर्णांकs
	*/

	OUTW (nc_sien , STO|HTH|MA|SGE|UDC|RST|PAR);
	OUTB (nc_dien , MDPE|BF|ABRT|SSI|SIR|IID);

	/*
	**	Fill in target काष्ठाure.
	**	Reinitialize usrsync.
	**	Reinitialize usrwide.
	**	Prepare sync negotiation according to actual SCSI bus mode.
	*/

	क्रम (i=0;i<MAX_TARGET;i++) अणु
		काष्ठा tcb *tp = &np->target[i];

		tp->sval    = 0;
		tp->wval    = np->rv_scntl3;

		अगर (tp->usrsync != 255) अणु
			अगर (tp->usrsync <= np->maxsync) अणु
				अगर (tp->usrsync < np->minsync) अणु
					tp->usrsync = np->minsync;
				पूर्ण
			पूर्ण
			अन्यथा
				tp->usrsync = 255;
		पूर्ण

		अगर (tp->usrwide > np->maxwide)
			tp->usrwide = np->maxwide;

	पूर्ण

	/*
	**    Start script processor.
	*/
	अगर (np->paddr2) अणु
		अगर (bootverbose)
			prपूर्णांकk ("%s: Downloading SCSI SCRIPTS.\n",
				ncr_name(np));
		OUTL (nc_scratcha, vtobus(np->script0));
		OUTL_DSP (NCB_SCRIPTH_PHYS (np, start_ram));
	पूर्ण
	अन्यथा
		OUTL_DSP (NCB_SCRIPT_PHYS (np, start));
पूर्ण

/*==========================================================
**
**	Prepare the negotiation values क्रम wide and
**	synchronous transfers.
**
**==========================================================
*/

अटल व्योम ncr_negotiate (काष्ठा ncb* np, काष्ठा tcb* tp)
अणु
	/*
	**	minsync unit is 4ns !
	*/

	u_दीर्घ minsync = tp->usrsync;

	/*
	**	SCSI bus mode limit
	*/

	अगर (np->scsi_mode && np->scsi_mode == SMODE_SE) अणु
		अगर (minsync < 12) minsync = 12;
	पूर्ण

	/*
	**	our limit ..
	*/

	अगर (minsync < np->minsync)
		minsync = np->minsync;

	/*
	**	भागider limit
	*/

	अगर (minsync > np->maxsync)
		minsync = 255;

	अगर (tp->maxoffs > np->maxoffs)
		tp->maxoffs = np->maxoffs;

	tp->minsync = minsync;
	tp->maxoffs = (minsync<255 ? tp->maxoffs : 0);

	/*
	**	period=0: has to negotiate sync transfer
	*/

	tp->period=0;

	/*
	**	wideकरोne=0: has to negotiate wide transfer
	*/
	tp->wideकरोne=0;
पूर्ण

/*==========================================================
**
**	Get घड़ी factor and sync भागisor क्रम a given 
**	synchronous factor period.
**	Returns the घड़ी factor (in sxfer) and scntl3 
**	synchronous भागisor field.
**
**==========================================================
*/

अटल व्योम ncr_माला_लोync(काष्ठा ncb *np, u_अक्षर sfac, u_अक्षर *fakp, u_अक्षर *scntl3p)
अणु
	u_दीर्घ	clk = np->घड़ी_khz;	/* SCSI घड़ी frequency in kHz	*/
	पूर्णांक	भाग = np->घड़ी_भागn;	/* Number of भागisors supported	*/
	u_दीर्घ	fak;			/* Sync factor in sxfer		*/
	u_दीर्घ	per;			/* Period in tenths of ns	*/
	u_दीर्घ	kpc;			/* (per * clk)			*/

	/*
	**	Compute the synchronous period in tenths of nano-seconds
	*/
	अगर	(sfac <= 10)	per = 250;
	अन्यथा अगर	(sfac == 11)	per = 303;
	अन्यथा अगर	(sfac == 12)	per = 500;
	अन्यथा			per = 40 * sfac;

	/*
	**	Look क्रम the greatest घड़ी भागisor that allows an 
	**	input speed faster than the period.
	*/
	kpc = per * clk;
	जबतक (--भाग > 0)
		अगर (kpc >= (भाग_10M[भाग] << 2)) अवरोध;

	/*
	**	Calculate the lowest घड़ी factor that allows an output 
	**	speed not faster than the period.
	*/
	fak = (kpc - 1) / भाग_10M[भाग] + 1;

#अगर 0	/* This optimization करोes not seem very useful */

	per = (fak * भाग_10M[भाग]) / clk;

	/*
	**	Why not to try the immediate lower भागisor and to choose 
	**	the one that allows the fastest output speed ?
	**	We करोn't want input speed too much greater than output speed.
	*/
	अगर (भाग >= 1 && fak < 8) अणु
		u_दीर्घ fak2, per2;
		fak2 = (kpc - 1) / भाग_10M[भाग-1] + 1;
		per2 = (fak2 * भाग_10M[भाग-1]) / clk;
		अगर (per2 < per && fak2 <= 8) अणु
			fak = fak2;
			per = per2;
			--भाग;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (fak < 4) fak = 4;	/* Should never happen, too bad ... */

	/*
	**	Compute and वापस sync parameters क्रम the ncr
	*/
	*fakp		= fak - 4;
	*scntl3p	= ((भाग+1) << 4) + (sfac < 25 ? 0x80 : 0);
पूर्ण


/*==========================================================
**
**	Set actual values, sync status and patch all ccbs of 
**	a target according to new sync/wide agreement.
**
**==========================================================
*/

अटल व्योम ncr_set_sync_wide_status (काष्ठा ncb *np, u_अक्षर target)
अणु
	काष्ठा ccb *cp;
	काष्ठा tcb *tp = &np->target[target];

	/*
	**	set actual value and sync_status
	*/
	OUTB (nc_sxfer, tp->sval);
	np->sync_st = tp->sval;
	OUTB (nc_scntl3, tp->wval);
	np->wide_st = tp->wval;

	/*
	**	patch ALL ccbs of this target.
	*/
	क्रम (cp = np->ccb; cp; cp = cp->link_ccb) अणु
		अगर (!cp->cmd) जारी;
		अगर (scmd_id(cp->cmd) != target) जारी;
#अगर 0
		cp->sync_status = tp->sval;
		cp->wide_status = tp->wval;
#पूर्ण_अगर
		cp->phys.select.sel_scntl3 = tp->wval;
		cp->phys.select.sel_sxfer  = tp->sval;
	पूर्ण
पूर्ण

/*==========================================================
**
**	Switch sync mode क्रम current job and it's target
**
**==========================================================
*/

अटल व्योम ncr_setsync (काष्ठा ncb *np, काष्ठा ccb *cp, u_अक्षर scntl3, u_अक्षर sxfer)
अणु
	काष्ठा scsi_cmnd *cmd = cp->cmd;
	काष्ठा tcb *tp;
	u_अक्षर target = INB (nc_sdid) & 0x0f;
	u_अक्षर iभाग;

	BUG_ON(target != (scmd_id(cmd) & 0xf));

	tp = &np->target[target];

	अगर (!scntl3 || !(sxfer & 0x1f))
		scntl3 = np->rv_scntl3;
	scntl3 = (scntl3 & 0xf0) | (tp->wval & EWS) | (np->rv_scntl3 & 0x07);

	/*
	**	Deduce the value of controller sync period from scntl3.
	**	period is in tenths of nano-seconds.
	*/

	iभाग = ((scntl3 >> 4) & 0x7);
	अगर ((sxfer & 0x1f) && iभाग)
		tp->period = (((sxfer>>5)+4)*भाग_10M[iभाग-1])/np->घड़ी_khz;
	अन्यथा
		tp->period = 0xffff;

	/* Stop there अगर sync parameters are unchanged */
	अगर (tp->sval == sxfer && tp->wval == scntl3)
		वापस;
	tp->sval = sxfer;
	tp->wval = scntl3;

	अगर (sxfer & 0x01f) अणु
		/* Disable extended Sreq/Sack filtering */
		अगर (tp->period <= 2000)
			OUTOFFB(nc_stest2, EXT);
	पूर्ण
 
	spi_display_xfer_agreement(tp->starget);

	/*
	**	set actual value and sync_status
	**	patch ALL ccbs of this target.
	*/
	ncr_set_sync_wide_status(np, target);
पूर्ण

/*==========================================================
**
**	Switch wide mode क्रम current job and it's target
**	SCSI specs say: a SCSI device that accepts a WDTR 
**	message shall reset the synchronous agreement to 
**	asynchronous mode.
**
**==========================================================
*/

अटल व्योम ncr_setwide (काष्ठा ncb *np, काष्ठा ccb *cp, u_अक्षर wide, u_अक्षर ack)
अणु
	काष्ठा scsi_cmnd *cmd = cp->cmd;
	u16 target = INB (nc_sdid) & 0x0f;
	काष्ठा tcb *tp;
	u_अक्षर	scntl3;
	u_अक्षर	sxfer;

	BUG_ON(target != (scmd_id(cmd) & 0xf));

	tp = &np->target[target];
	tp->wideकरोne  =  wide+1;
	scntl3 = (tp->wval & (~EWS)) | (wide ? EWS : 0);

	sxfer = ack ? 0 : tp->sval;

	/*
	**	 Stop there अगर sync/wide parameters are unchanged
	*/
	अगर (tp->sval == sxfer && tp->wval == scntl3) वापस;
	tp->sval = sxfer;
	tp->wval = scntl3;

	/*
	**	Bells and whistles   ;-)
	*/
	अगर (bootverbose >= 2) अणु
		dev_info(&cmd->device->sdev_target->dev, "WIDE SCSI %sabled.\n",
				(scntl3 & EWS) ? "en" : "dis");
	पूर्ण

	/*
	**	set actual value and sync_status
	**	patch ALL ccbs of this target.
	*/
	ncr_set_sync_wide_status(np, target);
पूर्ण

/*==========================================================
**
**	Switch tagged mode क्रम a target.
**
**==========================================================
*/

अटल व्योम ncr_setup_tags (काष्ठा ncb *np, काष्ठा scsi_device *sdev)
अणु
	अचिन्हित अक्षर tn = sdev->id, ln = sdev->lun;
	काष्ठा tcb *tp = &np->target[tn];
	काष्ठा lcb *lp = tp->lp[ln];
	u_अक्षर   reqtags, maxdepth;

	/*
	**	Just in हाल ...
	*/
	अगर ((!tp) || (!lp) || !sdev)
		वापस;

	/*
	**	If SCSI device queue depth is not yet set, leave here.
	*/
	अगर (!lp->scdev_depth)
		वापस;

	/*
	**	Donnot allow more tags than the SCSI driver can queue 
	**	क्रम this device.
	**	Donnot allow more tags than we can handle.
	*/
	maxdepth = lp->scdev_depth;
	अगर (maxdepth > lp->maxnxs)	maxdepth    = lp->maxnxs;
	अगर (lp->maxtags > maxdepth)	lp->maxtags = maxdepth;
	अगर (lp->numtags > maxdepth)	lp->numtags = maxdepth;

	/*
	**	only devices conक्रमmant to ANSI Version >= 2
	**	only devices capable of tagged commands
	**	only अगर enabled by user ..
	*/
	अगर (sdev->tagged_supported && lp->numtags > 1) अणु
		reqtags = lp->numtags;
	पूर्ण अन्यथा अणु
		reqtags = 1;
	पूर्ण

	/*
	**	Update max number of tags
	*/
	lp->numtags = reqtags;
	अगर (lp->numtags > lp->maxtags)
		lp->maxtags = lp->numtags;

	/*
	**	If we want to चयन tag mode, we must रुको 
	**	क्रम no CCB to be active.
	*/
	अगर	(reqtags > 1 && lp->usetags) अणु	 /* Stay in tagged mode    */
		अगर (lp->queuedepth == reqtags)	 /* Alपढ़ोy announced	   */
			वापस;
		lp->queuedepth	= reqtags;
	पूर्ण
	अन्यथा अगर	(reqtags <= 1 && !lp->usetags) अणु /* Stay in untagged mode  */
		lp->queuedepth	= reqtags;
		वापस;
	पूर्ण
	अन्यथा अणु					 /* Want to चयन tag mode */
		अगर (lp->busyccbs)		 /* If not yet safe, वापस */
			वापस;
		lp->queuedepth	= reqtags;
		lp->usetags	= reqtags > 1 ? 1 : 0;
	पूर्ण

	/*
	**	Patch the lun mini-script, according to tag mode.
	*/
	lp->jump_tag.l_paddr = lp->usetags?
			cpu_to_scr(NCB_SCRIPT_PHYS(np, resel_tag)) :
			cpu_to_scr(NCB_SCRIPT_PHYS(np, resel_notag));

	/*
	**	Announce change to user.
	*/
	अगर (bootverbose) अणु
		अगर (lp->usetags) अणु
			dev_info(&sdev->sdev_gendev,
				"tagged command queue depth set to %d\n",
				reqtags);
		पूर्ण अन्यथा अणु
			dev_info(&sdev->sdev_gendev,
					"tagged command queueing disabled\n");
		पूर्ण
	पूर्ण
पूर्ण

/*==========================================================
**
**
**	ncr समयout handler.
**
**
**==========================================================
**
**	Misused to keep the driver running when
**	पूर्णांकerrupts are not configured correctly.
**
**----------------------------------------------------------
*/

अटल व्योम ncr_समयout (काष्ठा ncb *np)
अणु
	u_दीर्घ	thisसमय = jअगरfies;

	/*
	**	If release process in progress, let's go
	**	Set the release stage from 1 to 2 to synchronize
	**	with the release process.
	*/

	अगर (np->release_stage) अणु
		अगर (np->release_stage == 1) np->release_stage = 2;
		वापस;
	पूर्ण

	np->समयr.expires = jअगरfies + SCSI_NCR_TIMER_INTERVAL;
	add_समयr(&np->समयr);

	/*
	**	If we are resetting the ncr, रुको क्रम settle_समय beक्रमe 
	**	clearing it. Then command processing will be resumed.
	*/
	अगर (np->settle_समय) अणु
		अगर (np->settle_समय <= thisसमय) अणु
			अगर (bootverbose > 1)
				prपूर्णांकk("%s: command processing resumed\n", ncr_name(np));
			np->settle_समय	= 0;
			np->disc	= 1;
			requeue_रुकोing_list(np);
		पूर्ण
		वापस;
	पूर्ण

	/*
	**	Since the generic scsi driver only allows us 0.5 second 
	**	to perक्रमm पात of a command, we must look at ccbs about 
	**	every 0.25 second.
	*/
	अगर (np->lastसमय + 4*HZ < thisसमय) अणु
		/*
		**	block ncr पूर्णांकerrupts
		*/
		np->lastसमय = thisसमय;
	पूर्ण

#अगर_घोषित SCSI_NCR_BROKEN_INTR
	अगर (INB(nc_istat) & (INTF|SIP|DIP)) अणु

		/*
		**	Process pending पूर्णांकerrupts.
		*/
		अगर (DEBUG_FLAGS & DEBUG_TINY) prपूर्णांकk ("{");
		ncr_exception (np);
		अगर (DEBUG_FLAGS & DEBUG_TINY) prपूर्णांकk ("}");
	पूर्ण
#पूर्ण_अगर /* SCSI_NCR_BROKEN_INTR */
पूर्ण

/*==========================================================
**
**	log message क्रम real hard errors
**
**	"ncr0 targ 0?: ERROR (ds:si) (so-si-sd) (sxfer/scntl3) @ name (dsp:dbc)."
**	"	      reg: r0 r1 r2 r3 r4 r5 r6 ..... rf."
**
**	exception रेजिस्टर:
**		ds:	dstat
**		si:	sist
**
**	SCSI bus lines:
**		so:	control lines as driver by NCR.
**		si:	control lines as seen by NCR.
**		sd:	scsi data lines as seen by NCR.
**
**	wide/fasपंचांगode:
**		sxfer:	(see the manual)
**		scntl3:	(see the manual)
**
**	current script command:
**		dsp:	script address (relative to start of script).
**		dbc:	first word of script command.
**
**	First 16 रेजिस्टर of the chip:
**		r0..rf
**
**==========================================================
*/

अटल व्योम ncr_log_hard_error(काष्ठा ncb *np, u16 sist, u_अक्षर dstat)
अणु
	u32	dsp;
	पूर्णांक	script_ofs;
	पूर्णांक	script_size;
	अक्षर	*script_name;
	u_अक्षर	*script_base;
	पूर्णांक	i;

	dsp	= INL (nc_dsp);

	अगर (dsp > np->p_script && dsp <= np->p_script + माप(काष्ठा script)) अणु
		script_ofs	= dsp - np->p_script;
		script_size	= माप(काष्ठा script);
		script_base	= (u_अक्षर *) np->script0;
		script_name	= "script";
	पूर्ण
	अन्यथा अगर (np->p_scripth < dsp && 
		 dsp <= np->p_scripth + माप(काष्ठा scripth)) अणु
		script_ofs	= dsp - np->p_scripth;
		script_size	= माप(काष्ठा scripth);
		script_base	= (u_अक्षर *) np->scripth0;
		script_name	= "scripth";
	पूर्ण अन्यथा अणु
		script_ofs	= dsp;
		script_size	= 0;
		script_base	= शून्य;
		script_name	= "mem";
	पूर्ण

	prपूर्णांकk ("%s:%d: ERROR (%x:%x) (%x-%x-%x) (%x/%x) @ (%s %x:%08x).\n",
		ncr_name (np), (अचिन्हित)INB (nc_sdid)&0x0f, dstat, sist,
		(अचिन्हित)INB (nc_socl), (अचिन्हित)INB (nc_sbcl), (अचिन्हित)INB (nc_sbdl),
		(अचिन्हित)INB (nc_sxfer),(अचिन्हित)INB (nc_scntl3), script_name, script_ofs,
		(अचिन्हित)INL (nc_dbc));

	अगर (((script_ofs & 3) == 0) &&
	    (अचिन्हित)script_ofs < script_size) अणु
		prपूर्णांकk ("%s: script cmd = %08x\n", ncr_name(np),
			scr_to_cpu((पूर्णांक) *(ncrcmd *)(script_base + script_ofs)));
	पूर्ण

	prपूर्णांकk ("%s: regdump:", ncr_name(np));
	क्रम (i=0; i<16;i++)
            prपूर्णांकk (" %02x", (अचिन्हित)INB_OFF(i));
	prपूर्णांकk (".\n");
पूर्ण

/*============================================================
**
**	ncr chip exception handler.
**
**============================================================
**
**	In normal हालs, पूर्णांकerrupt conditions occur one at a 
**	समय. The ncr is able to stack in some extra रेजिस्टरs 
**	other पूर्णांकerrupts that will occur after the first one.
**	But, several पूर्णांकerrupts may occur at the same समय.
**
**	We probably should only try to deal with the normal 
**	हाल, but it seems that multiple पूर्णांकerrupts occur in 
**	some हालs that are not abnormal at all.
**
**	The most frequent पूर्णांकerrupt condition is Phase Mismatch.
**	We should want to service this पूर्णांकerrupt quickly.
**	A SCSI parity error may be delivered at the same समय.
**	The SIR पूर्णांकerrupt is not very frequent in this driver, 
**	since the INTFLY is likely used क्रम command completion 
**	संकेतing.
**	The Selection Timeout पूर्णांकerrupt may be triggered with 
**	IID and/or UDC.
**	The SBMC पूर्णांकerrupt (SCSI Bus Mode Change) may probably 
**	occur at any समय.
**
**	This handler try to deal as cleverly as possible with all
**	the above.
**
**============================================================
*/

व्योम ncr_exception (काष्ठा ncb *np)
अणु
	u_अक्षर	istat, dstat;
	u16	sist;
	पूर्णांक	i;

	/*
	**	पूर्णांकerrupt on the fly ?
	**	Since the global header may be copied back to a CCB 
	**	using a posted PCI memory ग_लिखो, the last operation on 
	**	the istat रेजिस्टर is a READ in order to flush posted 
	**	PCI ग_लिखो commands.
	*/
	istat = INB (nc_istat);
	अगर (istat & INTF) अणु
		OUTB (nc_istat, (istat & SIGP) | INTF);
		istat = INB (nc_istat);
		अगर (DEBUG_FLAGS & DEBUG_TINY) prपूर्णांकk ("F ");
		ncr_wakeup_करोne (np);
	पूर्ण

	अगर (!(istat & (SIP|DIP)))
		वापस;

	अगर (istat & CABRT)
		OUTB (nc_istat, CABRT);

	/*
	**	Steinbach's Guideline क्रम Systems Programming:
	**	Never test क्रम an error condition you करोn't know how to handle.
	*/

	sist  = (istat & SIP) ? INW (nc_sist)  : 0;
	dstat = (istat & DIP) ? INB (nc_dstat) : 0;

	अगर (DEBUG_FLAGS & DEBUG_TINY)
		prपूर्णांकk ("<%d|%x:%x|%x:%x>",
			(पूर्णांक)INB(nc_scr0),
			dstat,sist,
			(अचिन्हित)INL(nc_dsp),
			(अचिन्हित)INL(nc_dbc));

	/*========================================================
	**	First, पूर्णांकerrupts we want to service cleanly.
	**
	**	Phase mismatch is the most frequent पूर्णांकerrupt, and 
	**	so we have to service it as quickly and as cleanly 
	**	as possible.
	**	Programmed पूर्णांकerrupts are rarely used in this driver,
	**	but we must handle them cleanly anyway.
	**	We try to deal with PAR and SBMC combined with 
	**	some other पूर्णांकerrupt(s).
	**=========================================================
	*/

	अगर (!(sist  & (STO|GEN|HTH|SGE|UDC|RST)) &&
	    !(dstat & (MDPE|BF|ABRT|IID))) अणु
		अगर ((sist & SBMC) && ncr_पूर्णांक_sbmc (np))
			वापस;
		अगर ((sist & PAR)  && ncr_पूर्णांक_par  (np))
			वापस;
		अगर (sist & MA) अणु
			ncr_पूर्णांक_ma (np);
			वापस;
		पूर्ण
		अगर (dstat & SIR) अणु
			ncr_पूर्णांक_sir (np);
			वापस;
		पूर्ण
		/*
		**  DEL 397 - 53C875 Rev 3 - Part Number 609-0392410 - ITEM 2.
		*/
		अगर (!(sist & (SBMC|PAR)) && !(dstat & SSI)) अणु
			prपूर्णांकk(	"%s: unknown interrupt(s) ignored, "
				"ISTAT=%x DSTAT=%x SIST=%x\n",
				ncr_name(np), istat, dstat, sist);
			वापस;
		पूर्ण
		OUTONB_STD ();
		वापस;
	पूर्ण

	/*========================================================
	**	Now, पूर्णांकerrupts that need some fixing up.
	**	Order and multiple पूर्णांकerrupts is so less important.
	**
	**	If SRST has been निश्चितed, we just reset the chip.
	**
	**	Selection is पूर्णांकirely handled by the chip. If the 
	**	chip says STO, we trust it. Seems some other 
	**	पूर्णांकerrupts may occur at the same समय (UDC, IID), so 
	**	we ignore them. In any हाल we करो enough fix-up 
	**	in the service routine.
	**	We just exclude some fatal dma errors.
	**=========================================================
	*/

	अगर (sist & RST) अणु
		ncr_init (np, 1, bootverbose ? "scsi reset" : शून्य, HS_RESET);
		वापस;
	पूर्ण

	अगर ((sist & STO) &&
		!(dstat & (MDPE|BF|ABRT))) अणु
	/*
	**	DEL 397 - 53C875 Rev 3 - Part Number 609-0392410 - ITEM 1.
	*/
		OUTONB (nc_ctest3, CLF);

		ncr_पूर्णांक_sto (np);
		वापस;
	पूर्ण

	/*=========================================================
	**	Now, पूर्णांकerrupts we are not able to recover cleanly.
	**	(At least क्रम the moment).
	**
	**	Do the रेजिस्टर dump.
	**	Log message क्रम real hard errors.
	**	Clear all fअगरos.
	**	For MDPE, BF, ABORT, IID, SGE and HTH we reset the 
	**	BUS and the chip.
	**	We are more soft क्रम UDC.
	**=========================================================
	*/

	अगर (समय_after(jअगरfies, np->regसमय)) अणु
		np->regसमय = jअगरfies + 10*HZ;
		क्रम (i = 0; i<माप(np->regdump); i++)
			((अक्षर*)&np->regdump)[i] = INB_OFF(i);
		np->regdump.nc_dstat = dstat;
		np->regdump.nc_sist  = sist;
	पूर्ण

	ncr_log_hard_error(np, sist, dstat);

	prपूर्णांकk ("%s: have to clear fifos.\n", ncr_name (np));
	OUTB (nc_stest3, TE|CSF);
	OUTONB (nc_ctest3, CLF);

	अगर ((sist & (SGE)) ||
		(dstat & (MDPE|BF|ABRT|IID))) अणु
		ncr_start_reset(np);
		वापस;
	पूर्ण

	अगर (sist & HTH) अणु
		prपूर्णांकk ("%s: handshake timeout\n", ncr_name(np));
		ncr_start_reset(np);
		वापस;
	पूर्ण

	अगर (sist & UDC) अणु
		prपूर्णांकk ("%s: unexpected disconnect\n", ncr_name(np));
		OUTB (HS_PRT, HS_UNEXPECTED);
		OUTL_DSP (NCB_SCRIPT_PHYS (np, cleanup));
		वापस;
	पूर्ण

	/*=========================================================
	**	We just miss the cause of the पूर्णांकerrupt. :(
	**	Prपूर्णांक a message. The समयout will करो the real work.
	**=========================================================
	*/
	prपूर्णांकk ("%s: unknown interrupt\n", ncr_name(np));
पूर्ण

/*==========================================================
**
**	ncr chip exception handler क्रम selection समयout
**
**==========================================================
**
**	There seems to be a bug in the 53c810.
**	Although a STO-Interrupt is pending,
**	it जारीs executing script commands.
**	But it will fail and पूर्णांकerrupt (IID) on
**	the next inकाष्ठाion where it's looking
**	क्रम a valid phase.
**
**----------------------------------------------------------
*/

व्योम ncr_पूर्णांक_sto (काष्ठा ncb *np)
अणु
	u_दीर्घ dsa;
	काष्ठा ccb *cp;
	अगर (DEBUG_FLAGS & DEBUG_TINY) prपूर्णांकk ("T");

	/*
	**	look क्रम ccb and set the status.
	*/

	dsa = INL (nc_dsa);
	cp = np->ccb;
	जबतक (cp && (CCB_PHYS (cp, phys) != dsa))
		cp = cp->link_ccb;

	अगर (cp) अणु
		cp-> host_status = HS_SEL_TIMEOUT;
		ncr_complete (np, cp);
	पूर्ण

	/*
	**	repair start queue and jump to start poपूर्णांक.
	*/

	OUTL_DSP (NCB_SCRIPTH_PHYS (np, sto_restart));
	वापस;
पूर्ण

/*==========================================================
**
**	ncr chip exception handler क्रम SCSI bus mode change
**
**==========================================================
**
**	spi2-r12 11.2.3 says a transceiver mode change must 
**	generate a reset event and a device that detects a reset 
**	event shall initiate a hard reset. It says also that a
**	device that detects a mode change shall set data transfer 
**	mode to eight bit asynchronous, etc...
**	So, just resetting should be enough.
**	 
**
**----------------------------------------------------------
*/

अटल पूर्णांक ncr_पूर्णांक_sbmc (काष्ठा ncb *np)
अणु
	u_अक्षर scsi_mode = INB (nc_stest4) & SMODE;

	अगर (scsi_mode != np->scsi_mode) अणु
		prपूर्णांकk("%s: SCSI bus mode change from %x to %x.\n",
			ncr_name(np), np->scsi_mode, scsi_mode);

		np->scsi_mode = scsi_mode;


		/*
		**	Suspend command processing क्रम 1 second and 
		**	reinitialize all except the chip.
		*/
		np->settle_समय	= jअगरfies + HZ;
		ncr_init (np, 0, bootverbose ? "scsi mode change" : शून्य, HS_RESET);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*==========================================================
**
**	ncr chip exception handler क्रम SCSI parity error.
**
**==========================================================
**
**
**----------------------------------------------------------
*/

अटल पूर्णांक ncr_पूर्णांक_par (काष्ठा ncb *np)
अणु
	u_अक्षर	hsts	= INB (HS_PRT);
	u32	dbc	= INL (nc_dbc);
	u_अक्षर	sstat1	= INB (nc_sstat1);
	पूर्णांक phase	= -1;
	पूर्णांक msg		= -1;
	u32 jmp;

	prपूर्णांकk("%s: SCSI parity error detected: SCR1=%d DBC=%x SSTAT1=%x\n",
		ncr_name(np), hsts, dbc, sstat1);

	/*
	 *	Ignore the पूर्णांकerrupt अगर the NCR is not connected 
	 *	to the SCSI bus, since the right work should have  
	 *	been करोne on unexpected disconnection handling.
	 */
	अगर (!(INB (nc_scntl1) & ISCON))
		वापस 0;

	/*
	 *	If the nexus is not clearly identअगरied, reset the bus.
	 *	We will try to करो better later.
	 */
	अगर (hsts & HS_INVALMASK)
		जाओ reset_all;

	/*
	 *	If the SCSI parity error occurs in MSG IN phase, prepare a 
	 *	MSG PARITY message. Otherwise, prepare a INITIATOR DETECTED 
	 *	ERROR message and let the device decide to retry the command 
	 *	or to terminate with check condition. If we were in MSG IN 
	 *	phase रुकोing क्रम the response of a negotiation, we will 
	 *	get SIR_NEGO_FAILED at dispatch.
	 */
	अगर (!(dbc & 0xc0000000))
		phase = (dbc >> 24) & 7;
	अगर (phase == 7)
		msg = MSG_PARITY_ERROR;
	अन्यथा
		msg = INITIATOR_ERROR;


	/*
	 *	If the NCR stopped on a MOVE ^ DATA_IN, we jump to a 
	 *	script that will ignore all data in bytes until phase 
	 *	change, since we are not sure the chip will रुको the phase 
	 *	change prior to delivering the पूर्णांकerrupt.
	 */
	अगर (phase == 1)
		jmp = NCB_SCRIPTH_PHYS (np, par_err_data_in);
	अन्यथा
		jmp = NCB_SCRIPTH_PHYS (np, par_err_other);

	OUTONB (nc_ctest3, CLF );	/* clear dma fअगरo  */
	OUTB (nc_stest3, TE|CSF);	/* clear scsi fअगरo */

	np->msgout[0] = msg;
	OUTL_DSP (jmp);
	वापस 1;

reset_all:
	ncr_start_reset(np);
	वापस 1;
पूर्ण

/*==========================================================
**
**
**	ncr chip exception handler क्रम phase errors.
**
**
**==========================================================
**
**	We have to स्थिरruct a new transfer descriptor,
**	to transfer the rest of the current block.
**
**----------------------------------------------------------
*/

अटल व्योम ncr_पूर्णांक_ma (काष्ठा ncb *np)
अणु
	u32	dbc;
	u32	rest;
	u32	dsp;
	u32	dsa;
	u32	nxtdsp;
	u32	newपंचांगp;
	u32	*vdsp;
	u32	oadr, olen;
	u32	*tblp;
	ncrcmd *newcmd;
	u_अक्षर	cmd, sbcl;
	काष्ठा ccb *cp;

	dsp	= INL (nc_dsp);
	dbc	= INL (nc_dbc);
	sbcl	= INB (nc_sbcl);

	cmd	= dbc >> 24;
	rest	= dbc & 0xffffff;

	/*
	**	Take पूर्णांकo account dma fअगरo and various buffers and latches,
	**	only अगर the पूर्णांकerrupted phase is an OUTPUT phase.
	*/

	अगर ((cmd & 1) == 0) अणु
		u_अक्षर	ctest5, ss0, ss2;
		u16	delta;

		ctest5 = (np->rv_ctest5 & DFS) ? INB (nc_ctest5) : 0;
		अगर (ctest5 & DFS)
			delta=(((ctest5 << 8) | (INB (nc_dfअगरo) & 0xff)) - rest) & 0x3ff;
		अन्यथा
			delta=(INB (nc_dfअगरo) - rest) & 0x7f;

		/*
		**	The data in the dma fअगरo has not been transferred to
		**	the target -> add the amount to the rest
		**	and clear the data.
		**	Check the sstat2 रेजिस्टर in हाल of wide transfer.
		*/

		rest += delta;
		ss0  = INB (nc_sstat0);
		अगर (ss0 & OLF) rest++;
		अगर (ss0 & ORF) rest++;
		अगर (INB(nc_scntl3) & EWS) अणु
			ss2 = INB (nc_sstat2);
			अगर (ss2 & OLF1) rest++;
			अगर (ss2 & ORF1) rest++;
		पूर्ण

		अगर (DEBUG_FLAGS & (DEBUG_TINY|DEBUG_PHASE))
			prपूर्णांकk ("P%x%x RL=%d D=%d SS0=%x ", cmd&7, sbcl&7,
				(अचिन्हित) rest, (अचिन्हित) delta, ss0);

	पूर्ण अन्यथा	अणु
		अगर (DEBUG_FLAGS & (DEBUG_TINY|DEBUG_PHASE))
			prपूर्णांकk ("P%x%x RL=%d ", cmd&7, sbcl&7, rest);
	पूर्ण

	/*
	**	Clear fअगरos.
	*/
	OUTONB (nc_ctest3, CLF );	/* clear dma fअगरo  */
	OUTB (nc_stest3, TE|CSF);	/* clear scsi fअगरo */

	/*
	**	locate matching cp.
	**	अगर the पूर्णांकerrupted phase is DATA IN or DATA OUT,
	**	trust the global header.
	*/
	dsa = INL (nc_dsa);
	अगर (!(cmd & 6)) अणु
		cp = np->header.cp;
		अगर (CCB_PHYS(cp, phys) != dsa)
			cp = शून्य;
	पूर्ण अन्यथा अणु
		cp  = np->ccb;
		जबतक (cp && (CCB_PHYS (cp, phys) != dsa))
			cp = cp->link_ccb;
	पूर्ण

	/*
	**	try to find the पूर्णांकerrupted script command,
	**	and the address at which to जारी.
	*/
	vdsp	= शून्य;
	nxtdsp	= 0;
	अगर	(dsp >  np->p_script &&
		 dsp <= np->p_script + माप(काष्ठा script)) अणु
		vdsp = (u32 *)((अक्षर*)np->script0 + (dsp-np->p_script-8));
		nxtdsp = dsp;
	पूर्ण
	अन्यथा अगर	(dsp >  np->p_scripth &&
		 dsp <= np->p_scripth + माप(काष्ठा scripth)) अणु
		vdsp = (u32 *)((अक्षर*)np->scripth0 + (dsp-np->p_scripth-8));
		nxtdsp = dsp;
	पूर्ण
	अन्यथा अगर (cp) अणु
		अगर	(dsp == CCB_PHYS (cp, patch[2])) अणु
			vdsp = &cp->patch[0];
			nxtdsp = scr_to_cpu(vdsp[3]);
		पूर्ण
		अन्यथा अगर (dsp == CCB_PHYS (cp, patch[6])) अणु
			vdsp = &cp->patch[4];
			nxtdsp = scr_to_cpu(vdsp[3]);
		पूर्ण
	पूर्ण

	/*
	**	log the inक्रमmation
	*/

	अगर (DEBUG_FLAGS & DEBUG_PHASE) अणु
		prपूर्णांकk ("\nCP=%p CP2=%p DSP=%x NXT=%x VDSP=%p CMD=%x ",
			cp, np->header.cp,
			(अचिन्हित)dsp,
			(अचिन्हित)nxtdsp, vdsp, cmd);
	पूर्ण

	/*
	**	cp=0 means that the DSA करोes not poपूर्णांक to a valid control 
	**	block. This should not happen since we करोnnot use multi-byte 
	**	move जबतक we are being reselected ot after command complete.
	**	We are not able to recover from such a phase error.
	*/
	अगर (!cp) अणु
		prपूर्णांकk ("%s: SCSI phase error fixup: "
			"CCB already dequeued (0x%08lx)\n", 
			ncr_name (np), (u_दीर्घ) np->header.cp);
		जाओ reset_all;
	पूर्ण

	/*
	**	get old startaddress and old length.
	*/

	oadr = scr_to_cpu(vdsp[1]);

	अगर (cmd & 0x10) अणु	/* Table indirect */
		tblp = (u32 *) ((अक्षर*) &cp->phys + oadr);
		olen = scr_to_cpu(tblp[0]);
		oadr = scr_to_cpu(tblp[1]);
	पूर्ण अन्यथा अणु
		tblp = (u32 *) 0;
		olen = scr_to_cpu(vdsp[0]) & 0xffffff;
	पूर्ण

	अगर (DEBUG_FLAGS & DEBUG_PHASE) अणु
		prपूर्णांकk ("OCMD=%x\nTBLP=%p OLEN=%x OADR=%x\n",
			(अचिन्हित) (scr_to_cpu(vdsp[0]) >> 24),
			tblp,
			(अचिन्हित) olen,
			(अचिन्हित) oadr);
	पूर्ण

	/*
	**	check cmd against assumed पूर्णांकerrupted script command.
	*/

	अगर (cmd != (scr_to_cpu(vdsp[0]) >> 24)) अणु
		PRINT_ADDR(cp->cmd, "internal error: cmd=%02x != %02x=(vdsp[0] "
				">> 24)\n", cmd, scr_to_cpu(vdsp[0]) >> 24);

		जाओ reset_all;
	पूर्ण

	/*
	**	cp != np->header.cp means that the header of the CCB 
	**	currently being processed has not yet been copied to 
	**	the global header area. That may happen अगर the device did 
	**	not accept all our messages after having been selected.
	*/
	अगर (cp != np->header.cp) अणु
		prपूर्णांकk ("%s: SCSI phase error fixup: "
			"CCB address mismatch (0x%08lx != 0x%08lx)\n", 
			ncr_name (np), (u_दीर्घ) cp, (u_दीर्घ) np->header.cp);
	पूर्ण

	/*
	**	अगर old phase not dataphase, leave here.
	*/

	अगर (cmd & 0x06) अणु
		PRINT_ADDR(cp->cmd, "phase change %x-%x %d@%08x resid=%d.\n",
			cmd&7, sbcl&7, (अचिन्हित)olen,
			(अचिन्हित)oadr, (अचिन्हित)rest);
		जाओ unexpected_phase;
	पूर्ण

	/*
	**	choose the correct patch area.
	**	अगर savep poपूर्णांकs to one, choose the other.
	*/

	newcmd = cp->patch;
	newपंचांगp = CCB_PHYS (cp, patch);
	अगर (newपंचांगp == scr_to_cpu(cp->phys.header.savep)) अणु
		newcmd = &cp->patch[4];
		newपंचांगp = CCB_PHYS (cp, patch[4]);
	पूर्ण

	/*
	**	fillin the commands
	*/

	newcmd[0] = cpu_to_scr(((cmd & 0x0f) << 24) | rest);
	newcmd[1] = cpu_to_scr(oadr + olen - rest);
	newcmd[2] = cpu_to_scr(SCR_JUMP);
	newcmd[3] = cpu_to_scr(nxtdsp);

	अगर (DEBUG_FLAGS & DEBUG_PHASE) अणु
		PRINT_ADDR(cp->cmd, "newcmd[%d] %x %x %x %x.\n",
			(पूर्णांक) (newcmd - cp->patch),
			(अचिन्हित)scr_to_cpu(newcmd[0]),
			(अचिन्हित)scr_to_cpu(newcmd[1]),
			(अचिन्हित)scr_to_cpu(newcmd[2]),
			(अचिन्हित)scr_to_cpu(newcmd[3]));
	पूर्ण
	/*
	**	fake the वापस address (to the patch).
	**	and restart script processor at dispatcher.
	*/
	OUTL (nc_temp, newपंचांगp);
	OUTL_DSP (NCB_SCRIPT_PHYS (np, dispatch));
	वापस;

	/*
	**	Unexpected phase changes that occurs when the current phase 
	**	is not a DATA IN or DATA OUT phase are due to error conditions.
	**	Such event may only happen when the SCRIPTS is using a 
	**	multibyte SCSI MOVE.
	**
	**	Phase change		Some possible cause
	**
	**	COMMAND  --> MSG IN	SCSI parity error detected by target.
	**	COMMAND  --> STATUS	Bad command or refused by target.
	**	MSG OUT  --> MSG IN     Message rejected by target.
	**	MSG OUT  --> COMMAND    Bogus target that discards extended
	**				negotiation messages.
	**
	**	The code below करोes not care of the new phase and so 
	**	trusts the target. Why to annoy it ?
	**	If the पूर्णांकerrupted phase is COMMAND phase, we restart at
	**	dispatcher.
	**	If a target करोes not get all the messages after selection, 
	**	the code assumes blindly that the target discards extended 
	**	messages and clears the negotiation status.
	**	If the target करोes not want all our response to negotiation,
	**	we क्रमce a SIR_NEGO_PROTO पूर्णांकerrupt (it is a hack that aव्योमs 
	**	bloat क्रम such a should_not_happen situation).
	**	In all other situation, we reset the BUS.
	**	Are these assumptions reasonable ? (Wait and see ...)
	*/
unexpected_phase:
	dsp -= 8;
	nxtdsp = 0;

	चयन (cmd & 7) अणु
	हाल 2:	/* COMMAND phase */
		nxtdsp = NCB_SCRIPT_PHYS (np, dispatch);
		अवरोध;
#अगर 0
	हाल 3:	/* STATUS  phase */
		nxtdsp = NCB_SCRIPT_PHYS (np, dispatch);
		अवरोध;
#पूर्ण_अगर
	हाल 6:	/* MSG OUT phase */
		np->scripth->nxtdsp_go_on[0] = cpu_to_scr(dsp + 8);
		अगर	(dsp == NCB_SCRIPT_PHYS (np, send_ident)) अणु
			cp->host_status = HS_BUSY;
			nxtdsp = NCB_SCRIPTH_PHYS (np, clratn_go_on);
		पूर्ण
		अन्यथा अगर	(dsp == NCB_SCRIPTH_PHYS (np, send_wdtr) ||
			 dsp == NCB_SCRIPTH_PHYS (np, send_sdtr)) अणु
			nxtdsp = NCB_SCRIPTH_PHYS (np, nego_bad_phase);
		पूर्ण
		अवरोध;
#अगर 0
	हाल 7:	/* MSG IN  phase */
		nxtdsp = NCB_SCRIPT_PHYS (np, clrack);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (nxtdsp) अणु
		OUTL_DSP (nxtdsp);
		वापस;
	पूर्ण

reset_all:
	ncr_start_reset(np);
पूर्ण


अटल व्योम ncr_sir_to_reकरो(काष्ठा ncb *np, पूर्णांक num, काष्ठा ccb *cp)
अणु
	काष्ठा scsi_cmnd *cmd	= cp->cmd;
	काष्ठा tcb *tp	= &np->target[cmd->device->id];
	काष्ठा lcb *lp	= tp->lp[cmd->device->lun];
	काष्ठा list_head *qp;
	काष्ठा ccb *	cp2;
	पूर्णांक		disc_cnt = 0;
	पूर्णांक		busy_cnt = 0;
	u32		startp;
	u_अक्षर		s_status = INB (SS_PRT);

	/*
	**	Let the SCRIPTS processor skip all not yet started CCBs,
	**	and count disconnected CCBs. Since the busy queue is in 
	**	the same order as the chip start queue, disconnected CCBs 
	**	are beक्रमe cp and busy ones after.
	*/
	अगर (lp) अणु
		qp = lp->busy_ccbq.prev;
		जबतक (qp != &lp->busy_ccbq) अणु
			cp2 = list_entry(qp, काष्ठा ccb, link_ccbq);
			qp  = qp->prev;
			++busy_cnt;
			अगर (cp2 == cp)
				अवरोध;
			cp2->start.schedule.l_paddr =
			cpu_to_scr(NCB_SCRIPTH_PHYS (np, skip));
		पूर्ण
		lp->held_ccb = cp;	/* Requeue when this one completes */
		disc_cnt = lp->queuedccbs - busy_cnt;
	पूर्ण

	चयन(s_status) अणु
	शेष:	/* Just क्रम safety, should never happen */
	हाल SAM_STAT_TASK_SET_FULL:
		/*
		**	Decrease number of tags to the number of 
		**	disconnected commands.
		*/
		अगर (!lp)
			जाओ out;
		अगर (bootverbose >= 1) अणु
			PRINT_ADDR(cmd, "QUEUE FULL! %d busy, %d disconnected "
					"CCBs\n", busy_cnt, disc_cnt);
		पूर्ण
		अगर (disc_cnt < lp->numtags) अणु
			lp->numtags	= disc_cnt > 2 ? disc_cnt : 2;
			lp->num_good	= 0;
			ncr_setup_tags (np, cmd->device);
		पूर्ण
		/*
		**	Requeue the command to the start queue.
		**	If any disconnected commands,
		**		Clear SIGP.
		**		Jump to reselect.
		*/
		cp->phys.header.savep = cp->startp;
		cp->host_status = HS_BUSY;
		cp->scsi_status = SAM_STAT_ILLEGAL;

		ncr_put_start_queue(np, cp);
		अगर (disc_cnt)
			INB (nc_ctest2);		/* Clear SIGP */
		OUTL_DSP (NCB_SCRIPT_PHYS (np, reselect));
		वापस;
	हाल SAM_STAT_COMMAND_TERMINATED:
	हाल SAM_STAT_CHECK_CONDITION:
		/*
		**	If we were requesting sense, give up.
		*/
		अगर (cp->स्वतः_sense)
			जाओ out;

		/*
		**	Device वापसed CHECK CONDITION status.
		**	Prepare all needed data strutures क्रम getting 
		**	sense data.
		**
		**	identअगरy message
		*/
		cp->scsi_smsg2[0]	= IDENTIFY(0, cmd->device->lun);
		cp->phys.smsg.addr	= cpu_to_scr(CCB_PHYS (cp, scsi_smsg2));
		cp->phys.smsg.size	= cpu_to_scr(1);

		/*
		**	sense command
		*/
		cp->phys.cmd.addr	= cpu_to_scr(CCB_PHYS (cp, sensecmd));
		cp->phys.cmd.size	= cpu_to_scr(6);

		/*
		**	patch requested size पूर्णांकo sense command
		*/
		cp->sensecmd[0]		= 0x03;
		cp->sensecmd[1]		= (cmd->device->lun & 0x7) << 5;
		cp->sensecmd[4]		= माप(cp->sense_buf);

		/*
		**	sense data
		*/
		स_रखो(cp->sense_buf, 0, माप(cp->sense_buf));
		cp->phys.sense.addr	= cpu_to_scr(CCB_PHYS(cp,sense_buf[0]));
		cp->phys.sense.size	= cpu_to_scr(माप(cp->sense_buf));

		/*
		**	requeue the command.
		*/
		startp = cpu_to_scr(NCB_SCRIPTH_PHYS (np, sdata_in));

		cp->phys.header.savep	= startp;
		cp->phys.header.goalp	= startp + 24;
		cp->phys.header.lastp	= startp;
		cp->phys.header.wgoalp	= startp + 24;
		cp->phys.header.wlastp	= startp;

		cp->host_status = HS_BUSY;
		cp->scsi_status = SAM_STAT_ILLEGAL;
		cp->स्वतः_sense	= s_status;

		cp->start.schedule.l_paddr =
			cpu_to_scr(NCB_SCRIPT_PHYS (np, select));

		/*
		**	Select without ATN क्रम quirky devices.
		*/
		अगर (cmd->device->select_no_atn)
			cp->start.schedule.l_paddr =
			cpu_to_scr(NCB_SCRIPTH_PHYS (np, select_no_atn));

		ncr_put_start_queue(np, cp);

		OUTL_DSP (NCB_SCRIPT_PHYS (np, start));
		वापस;
	पूर्ण

out:
	OUTONB_STD ();
	वापस;
पूर्ण


/*==========================================================
**
**
**      ncr chip exception handler क्रम programmed पूर्णांकerrupts.
**
**
**==========================================================
*/

व्योम ncr_पूर्णांक_sir (काष्ठा ncb *np)
अणु
	u_अक्षर scntl3;
	u_अक्षर chg, ofs, per, fak, wide;
	u_अक्षर num = INB (nc_dsps);
	काष्ठा ccb *cp=शून्य;
	u_दीर्घ	dsa    = INL (nc_dsa);
	u_अक्षर	target = INB (nc_sdid) & 0x0f;
	काष्ठा tcb *tp     = &np->target[target];
	काष्ठा scsi_target *starget = tp->starget;

	अगर (DEBUG_FLAGS & DEBUG_TINY) prपूर्णांकk ("I#%d", num);

	चयन (num) अणु
	हाल SIR_INTFLY:
		/*
		**	This is used क्रम HP Zalon/53c720 where INTFLY
		**	operation is currently broken.
		*/
		ncr_wakeup_करोne(np);
#अगर_घोषित SCSI_NCR_CCB_DONE_SUPPORT
		OUTL(nc_dsp, NCB_SCRIPT_PHYS (np, करोne_end) + 8);
#अन्यथा
		OUTL(nc_dsp, NCB_SCRIPT_PHYS (np, start));
#पूर्ण_अगर
		वापस;
	हाल SIR_RESEL_NO_MSG_IN:
	हाल SIR_RESEL_NO_IDENTIFY:
		/*
		**	If devices reselecting without sending an IDENTIFY 
		**	message still exist, this should help.
		**	We just assume lun=0, 1 CCB, no tag.
		*/
		अगर (tp->lp[0]) अणु 
			OUTL_DSP (scr_to_cpu(tp->lp[0]->jump_ccb[0]));
			वापस;
		पूर्ण
		fallthrough;
	हाल SIR_RESEL_BAD_TARGET:	/* Will send a TARGET RESET message */
	हाल SIR_RESEL_BAD_LUN:		/* Will send a TARGET RESET message */
	हाल SIR_RESEL_BAD_I_T_L_Q:	/* Will send an ABORT TAG message   */
	हाल SIR_RESEL_BAD_I_T_L:	/* Will send an ABORT message	    */
		prपूर्णांकk ("%s:%d: SIR %d, "
			"incorrect nexus identification on reselection\n",
			ncr_name (np), target, num);
		जाओ out;
	हाल SIR_DONE_OVERFLOW:
		prपूर्णांकk ("%s:%d: SIR %d, "
			"CCB done queue overflow\n",
			ncr_name (np), target, num);
		जाओ out;
	हाल SIR_BAD_STATUS:
		cp = np->header.cp;
		अगर (!cp || CCB_PHYS (cp, phys) != dsa)
			जाओ out;
		ncr_sir_to_reकरो(np, num, cp);
		वापस;
	शेष:
		/*
		**	lookup the ccb
		*/
		cp = np->ccb;
		जबतक (cp && (CCB_PHYS (cp, phys) != dsa))
			cp = cp->link_ccb;

		BUG_ON(!cp);
		BUG_ON(cp != np->header.cp);

		अगर (!cp || cp != np->header.cp)
			जाओ out;
	पूर्ण

	चयन (num) अणु
/*-----------------------------------------------------------------------------
**
**	Was Sie schon immer ueber transfermode negotiation wissen wollten ...
**	("Everything you've always wanted to know about transfer mode
**	  negotiation")
**
**	We try to negotiate sync and wide transfer only after
**	a successful inquire command. We look at byte 7 of the
**	inquire data to determine the capabilities of the target.
**
**	When we try to negotiate, we append the negotiation message
**	to the identअगरy and (maybe) simple tag message.
**	The host status field is set to HS_NEGOTIATE to mark this
**	situation.
**
**	If the target करोesn't answer this message immediately
**	(as required by the standard), the SIR_NEGO_FAIL पूर्णांकerrupt
**	will be उठाओd eventually.
**	The handler हटाओs the HS_NEGOTIATE status, and sets the
**	negotiated value to the शेष (async / nowide).
**
**	If we receive a matching answer immediately, we check it
**	क्रम validity, and set the values.
**
**	If we receive a Reject message immediately, we assume the
**	negotiation has failed, and fall back to standard values.
**
**	If we receive a negotiation message जबतक not in HS_NEGOTIATE
**	state, it's a target initiated negotiation. We prepare a
**	(hopefully) valid answer, set our parameters, and send back 
**	this answer to the target.
**
**	If the target करोesn't fetch the answer (no message out phase),
**	we assume the negotiation has failed, and fall back to शेष
**	settings.
**
**	When we set the values, we adjust them in all ccbs beदीर्घing 
**	to this target, in the controller's रेजिस्टर, and in the "phys"
**	field of the controller's काष्ठा ncb.
**
**	Possible हालs:		   hs  sir   msg_in value  send   जाओ
**	We try to negotiate:
**	-> target करोesn't msgin    NEG FAIL  noop   defa.  -      dispatch
**	-> target rejected our msg NEG FAIL  reject defa.  -      dispatch
**	-> target answered  (ok)   NEG SYNC  sdtr   set    -      clrack
**	-> target answered (!ok)   NEG SYNC  sdtr   defa.  REJ--->msg_bad
**	-> target answered  (ok)   NEG WIDE  wdtr   set    -      clrack
**	-> target answered (!ok)   NEG WIDE  wdtr   defa.  REJ--->msg_bad
**	-> any other msgin	   NEG FAIL  noop   defa.  -      dispatch
**
**	Target tries to negotiate:
**	-> incoming message	   --- SYNC  sdtr   set    SDTR   -
**	-> incoming message	   --- WIDE  wdtr   set    WDTR   -
**      We sent our answer:
**	-> target करोesn't msgout   --- PROTO ?      defa.  -      dispatch
**
**-----------------------------------------------------------------------------
*/

	हाल SIR_NEGO_FAILED:
		/*-------------------------------------------------------
		**
		**	Negotiation failed.
		**	Target करोesn't send an answer message,
		**	or target rejected our message.
		**
		**      Remove negotiation request.
		**
		**-------------------------------------------------------
		*/
		OUTB (HS_PRT, HS_BUSY);

		fallthrough;

	हाल SIR_NEGO_PROTO:
		/*-------------------------------------------------------
		**
		**	Negotiation failed.
		**	Target करोesn't fetch the answer message.
		**
		**-------------------------------------------------------
		*/

		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			PRINT_ADDR(cp->cmd, "negotiation failed sir=%x "
					"status=%x.\n", num, cp->nego_status);
		पूर्ण

		/*
		**	any error in negotiation:
		**	fall back to शेष mode.
		*/
		चयन (cp->nego_status) अणु

		हाल NS_SYNC:
			spi_period(starget) = 0;
			spi_offset(starget) = 0;
			ncr_setsync (np, cp, 0, 0xe0);
			अवरोध;

		हाल NS_WIDE:
			spi_width(starget) = 0;
			ncr_setwide (np, cp, 0, 0);
			अवरोध;

		पूर्ण
		np->msgin [0] = NOP;
		np->msgout[0] = NOP;
		cp->nego_status = 0;
		अवरोध;

	हाल SIR_NEGO_SYNC:
		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			ncr_prपूर्णांक_msg(cp, "sync msgin", np->msgin);
		पूर्ण

		chg = 0;
		per = np->msgin[3];
		ofs = np->msgin[4];
		अगर (ofs==0) per=255;

		/*
		**      अगर target sends SDTR message,
		**	      it CAN transfer synch.
		*/

		अगर (ofs && starget)
			spi_support_sync(starget) = 1;

		/*
		**	check values against driver limits.
		*/

		अगर (per < np->minsync)
			अणुchg = 1; per = np->minsync;पूर्ण
		अगर (per < tp->minsync)
			अणुchg = 1; per = tp->minsync;पूर्ण
		अगर (ofs > tp->maxoffs)
			अणुchg = 1; ofs = tp->maxoffs;पूर्ण

		/*
		**	Check against controller limits.
		*/
		fak	= 7;
		scntl3	= 0;
		अगर (ofs != 0) अणु
			ncr_माला_लोync(np, per, &fak, &scntl3);
			अगर (fak > 7) अणु
				chg = 1;
				ofs = 0;
			पूर्ण
		पूर्ण
		अगर (ofs == 0) अणु
			fak	= 7;
			per	= 0;
			scntl3	= 0;
			tp->minsync = 0;
		पूर्ण

		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			PRINT_ADDR(cp->cmd, "sync: per=%d scntl3=0x%x ofs=%d "
				"fak=%d chg=%d.\n", per, scntl3, ofs, fak, chg);
		पूर्ण

		अगर (INB (HS_PRT) == HS_NEGOTIATE) अणु
			OUTB (HS_PRT, HS_BUSY);
			चयन (cp->nego_status) अणु

			हाल NS_SYNC:
				/* This was an answer message */
				अगर (chg) अणु
					/* Answer wasn't acceptable.  */
					spi_period(starget) = 0;
					spi_offset(starget) = 0;
					ncr_setsync(np, cp, 0, 0xe0);
					OUTL_DSP(NCB_SCRIPT_PHYS (np, msg_bad));
				पूर्ण अन्यथा अणु
					/* Answer is ok.  */
					spi_period(starget) = per;
					spi_offset(starget) = ofs;
					ncr_setsync(np, cp, scntl3, (fak<<5)|ofs);
					OUTL_DSP(NCB_SCRIPT_PHYS (np, clrack));
				पूर्ण
				वापस;

			हाल NS_WIDE:
				spi_width(starget) = 0;
				ncr_setwide(np, cp, 0, 0);
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		**	It was a request. Set value and
		**      prepare an answer message
		*/

		spi_period(starget) = per;
		spi_offset(starget) = ofs;
		ncr_setsync(np, cp, scntl3, (fak<<5)|ofs);

		spi_populate_sync_msg(np->msgout, per, ofs);
		cp->nego_status = NS_SYNC;

		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			ncr_prपूर्णांक_msg(cp, "sync msgout", np->msgout);
		पूर्ण

		अगर (!ofs) अणु
			OUTL_DSP (NCB_SCRIPT_PHYS (np, msg_bad));
			वापस;
		पूर्ण
		np->msgin [0] = NOP;

		अवरोध;

	हाल SIR_NEGO_WIDE:
		/*
		**	Wide request message received.
		*/
		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			ncr_prपूर्णांक_msg(cp, "wide msgin", np->msgin);
		पूर्ण

		/*
		**	get requested values.
		*/

		chg  = 0;
		wide = np->msgin[3];

		/*
		**      अगर target sends WDTR message,
		**	      it CAN transfer wide.
		*/

		अगर (wide && starget)
			spi_support_wide(starget) = 1;

		/*
		**	check values against driver limits.
		*/

		अगर (wide > tp->usrwide)
			अणुchg = 1; wide = tp->usrwide;पूर्ण

		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			PRINT_ADDR(cp->cmd, "wide: wide=%d chg=%d.\n", wide,
					chg);
		पूर्ण

		अगर (INB (HS_PRT) == HS_NEGOTIATE) अणु
			OUTB (HS_PRT, HS_BUSY);
			चयन (cp->nego_status) अणु

			हाल NS_WIDE:
				/*
				**      This was an answer message
				*/
				अगर (chg) अणु
					/* Answer wasn't acceptable.  */
					spi_width(starget) = 0;
					ncr_setwide(np, cp, 0, 1);
					OUTL_DSP (NCB_SCRIPT_PHYS (np, msg_bad));
				पूर्ण अन्यथा अणु
					/* Answer is ok.  */
					spi_width(starget) = wide;
					ncr_setwide(np, cp, wide, 1);
					OUTL_DSP (NCB_SCRIPT_PHYS (np, clrack));
				पूर्ण
				वापस;

			हाल NS_SYNC:
				spi_period(starget) = 0;
				spi_offset(starget) = 0;
				ncr_setsync(np, cp, 0, 0xe0);
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		**	It was a request, set value and
		**      prepare an answer message
		*/

		spi_width(starget) = wide;
		ncr_setwide(np, cp, wide, 1);
		spi_populate_width_msg(np->msgout, wide);

		np->msgin [0] = NOP;

		cp->nego_status = NS_WIDE;

		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			ncr_prपूर्णांक_msg(cp, "wide msgout", np->msgin);
		पूर्ण
		अवरोध;

/*--------------------------------------------------------------------
**
**	Processing of special messages
**
**--------------------------------------------------------------------
*/

	हाल SIR_REJECT_RECEIVED:
		/*-----------------------------------------------
		**
		**	We received a MESSAGE_REJECT.
		**
		**-----------------------------------------------
		*/

		PRINT_ADDR(cp->cmd, "MESSAGE_REJECT received (%x:%x).\n",
			(अचिन्हित)scr_to_cpu(np->lasपंचांगsg), np->msgout[0]);
		अवरोध;

	हाल SIR_REJECT_SENT:
		/*-----------------------------------------------
		**
		**	We received an unknown message
		**
		**-----------------------------------------------
		*/

		ncr_prपूर्णांक_msg(cp, "MESSAGE_REJECT sent for", np->msgin);
		अवरोध;

/*--------------------------------------------------------------------
**
**	Processing of special messages
**
**--------------------------------------------------------------------
*/

	हाल SIR_IGN_RESIDUE:
		/*-----------------------------------------------
		**
		**	We received an IGNORE RESIDUE message,
		**	which couldn't be handled by the script.
		**
		**-----------------------------------------------
		*/

		PRINT_ADDR(cp->cmd, "IGNORE_WIDE_RESIDUE received, but not yet "
				"implemented.\n");
		अवरोध;
#अगर 0
	हाल SIR_MISSING_SAVE:
		/*-----------------------------------------------
		**
		**	We received an DISCONNECT message,
		**	but the datapoपूर्णांकer wasn't saved beक्रमe.
		**
		**-----------------------------------------------
		*/

		PRINT_ADDR(cp->cmd, "DISCONNECT received, but datapointer "
				"not saved: data=%x save=%x goal=%x.\n",
			(अचिन्हित) INL (nc_temp),
			(अचिन्हित) scr_to_cpu(np->header.savep),
			(अचिन्हित) scr_to_cpu(np->header.goalp));
		अवरोध;
#पूर्ण_अगर
	पूर्ण

out:
	OUTONB_STD ();
पूर्ण

/*==========================================================
**
**
**	Acquire a control block
**
**
**==========================================================
*/

अटल काष्ठा ccb *ncr_get_ccb(काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd)
अणु
	u_अक्षर tn = cmd->device->id;
	u_अक्षर ln = cmd->device->lun;
	काष्ठा tcb *tp = &np->target[tn];
	काष्ठा lcb *lp = tp->lp[ln];
	u_अक्षर tag = NO_TAG;
	काष्ठा ccb *cp = शून्य;

	/*
	**	Lun काष्ठाure available ?
	*/
	अगर (lp) अणु
		काष्ठा list_head *qp;
		/*
		**	Keep from using more tags than we can handle.
		*/
		अगर (lp->usetags && lp->busyccbs >= lp->maxnxs)
			वापस शून्य;

		/*
		**	Allocate a new CCB अगर needed.
		*/
		अगर (list_empty(&lp->मुक्त_ccbq))
			ncr_alloc_ccb(np, tn, ln);

		/*
		**	Look क्रम मुक्त CCB
		*/
		qp = ncr_list_pop(&lp->मुक्त_ccbq);
		अगर (qp) अणु
			cp = list_entry(qp, काष्ठा ccb, link_ccbq);
			अगर (cp->magic) अणु
				PRINT_ADDR(cmd, "ccb free list corrupted "
						"(@%p)\n", cp);
				cp = शून्य;
			पूर्ण अन्यथा अणु
				list_add_tail(qp, &lp->रुको_ccbq);
				++lp->busyccbs;
			पूर्ण
		पूर्ण

		/*
		**	If a CCB is available,
		**	Get a tag क्रम this nexus अगर required.
		*/
		अगर (cp) अणु
			अगर (lp->usetags)
				tag = lp->cb_tags[lp->ia_tag];
		पूर्ण
		अन्यथा अगर (lp->actccbs > 0)
			वापस शून्य;
	पूर्ण

	/*
	**	अगर nothing available, take the शेष.
	*/
	अगर (!cp)
		cp = np->ccb;

	/*
	**	Wait until available.
	*/
#अगर 0
	जबतक (cp->magic) अणु
		अगर (flags & SCSI_NOSLEEP) अवरोध;
		अगर (tsleep ((caddr_t)cp, PRIBIO|PCATCH, "ncr", 0))
			अवरोध;
	पूर्ण
#पूर्ण_अगर

	अगर (cp->magic)
		वापस शून्य;

	cp->magic = 1;

	/*
	**	Move to next available tag अगर tag used.
	*/
	अगर (lp) अणु
		अगर (tag != NO_TAG) अणु
			++lp->ia_tag;
			अगर (lp->ia_tag == MAX_TAGS)
				lp->ia_tag = 0;
			lp->tags_umap |= (((tagmap_t) 1) << tag);
		पूर्ण
	पूर्ण

	/*
	**	Remember all inक्रमmations needed to मुक्त this CCB.
	*/
	cp->tag	   = tag;
	cp->target = tn;
	cp->lun    = ln;

	अगर (DEBUG_FLAGS & DEBUG_TAGS) अणु
		PRINT_ADDR(cmd, "ccb @%p using tag %d.\n", cp, tag);
	पूर्ण

	वापस cp;
पूर्ण

/*==========================================================
**
**
**	Release one control block
**
**
**==========================================================
*/

अटल व्योम ncr_मुक्त_ccb (काष्ठा ncb *np, काष्ठा ccb *cp)
अणु
	काष्ठा tcb *tp = &np->target[cp->target];
	काष्ठा lcb *lp = tp->lp[cp->lun];

	अगर (DEBUG_FLAGS & DEBUG_TAGS) अणु
		PRINT_ADDR(cp->cmd, "ccb @%p freeing tag %d.\n", cp, cp->tag);
	पूर्ण

	/*
	**	If lun control block available,
	**	decrement active commands and increment credit, 
	**	मुक्त the tag अगर any and हटाओ the JUMP क्रम reselect.
	*/
	अगर (lp) अणु
		अगर (cp->tag != NO_TAG) अणु
			lp->cb_tags[lp->अगर_tag++] = cp->tag;
			अगर (lp->अगर_tag == MAX_TAGS)
				lp->अगर_tag = 0;
			lp->tags_umap &= ~(((tagmap_t) 1) << cp->tag);
			lp->tags_smap &= lp->tags_umap;
			lp->jump_ccb[cp->tag] =
				cpu_to_scr(NCB_SCRIPTH_PHYS(np, bad_i_t_l_q));
		पूर्ण अन्यथा अणु
			lp->jump_ccb[0] =
				cpu_to_scr(NCB_SCRIPTH_PHYS(np, bad_i_t_l));
		पूर्ण
	पूर्ण

	/*
	**	Make this CCB available.
	*/

	अगर (lp) अणु
		अगर (cp != np->ccb)
			list_move(&cp->link_ccbq, &lp->मुक्त_ccbq);
		--lp->busyccbs;
		अगर (cp->queued) अणु
			--lp->queuedccbs;
		पूर्ण
	पूर्ण
	cp -> host_status = HS_IDLE;
	cp -> magic = 0;
	अगर (cp->queued) अणु
		--np->queuedccbs;
		cp->queued = 0;
	पूर्ण

#अगर 0
	अगर (cp == np->ccb)
		wakeup ((caddr_t) cp);
#पूर्ण_अगर
पूर्ण


#घोषणा ncr_reg_bus_addr(r) (np->paddr + दुरत्व (काष्ठा ncr_reg, r))

/*------------------------------------------------------------------------
**	Initialize the fixed part of a CCB काष्ठाure.
**------------------------------------------------------------------------
**------------------------------------------------------------------------
*/
अटल व्योम ncr_init_ccb(काष्ठा ncb *np, काष्ठा ccb *cp)
अणु
	ncrcmd copy_4 = np->features & FE_PFEN ? SCR_COPY(4) : SCR_COPY_F(4);

	/*
	**	Remember भव and bus address of this ccb.
	*/
	cp->p_ccb 	   = vtobus(cp);
	cp->phys.header.cp = cp;

	/*
	**	This allows list_del to work क्रम the शेष ccb.
	*/
	INIT_LIST_HEAD(&cp->link_ccbq);

	/*
	**	Initialyze the start and restart launch script.
	**
	**	COPY(4) @(...p_phys), @(dsa)
	**	JUMP @(sched_poपूर्णांक)
	*/
	cp->start.setup_dsa[0]	 = cpu_to_scr(copy_4);
	cp->start.setup_dsa[1]	 = cpu_to_scr(CCB_PHYS(cp, start.p_phys));
	cp->start.setup_dsa[2]	 = cpu_to_scr(ncr_reg_bus_addr(nc_dsa));
	cp->start.schedule.l_cmd = cpu_to_scr(SCR_JUMP);
	cp->start.p_phys	 = cpu_to_scr(CCB_PHYS(cp, phys));

	स_नकल(&cp->restart, &cp->start, माप(cp->restart));

	cp->start.schedule.l_paddr   = cpu_to_scr(NCB_SCRIPT_PHYS (np, idle));
	cp->restart.schedule.l_paddr = cpu_to_scr(NCB_SCRIPTH_PHYS (np, पात));
पूर्ण


/*------------------------------------------------------------------------
**	Allocate a CCB and initialize its fixed part.
**------------------------------------------------------------------------
**------------------------------------------------------------------------
*/
अटल व्योम ncr_alloc_ccb(काष्ठा ncb *np, u_अक्षर tn, u_अक्षर ln)
अणु
	काष्ठा tcb *tp = &np->target[tn];
	काष्ठा lcb *lp = tp->lp[ln];
	काष्ठा ccb *cp = शून्य;

	/*
	**	Allocate memory क्रम this CCB.
	*/
	cp = m_सुस्मृति_dma(माप(काष्ठा ccb), "CCB");
	अगर (!cp)
		वापस;

	/*
	**	Count it and initialyze it.
	*/
	lp->actccbs++;
	np->actccbs++;
	स_रखो(cp, 0, माप (*cp));
	ncr_init_ccb(np, cp);

	/*
	**	Chain पूर्णांकo wakeup list and मुक्त ccb queue and take it 
	**	पूर्णांकo account क्रम tagged commands.
	*/
	cp->link_ccb      = np->ccb->link_ccb;
	np->ccb->link_ccb = cp;

	list_add(&cp->link_ccbq, &lp->मुक्त_ccbq);
पूर्ण

/*==========================================================
**
**
**      Allocation of resources क्रम Tarमाला_लो/Luns/Tags.
**
**
**==========================================================
*/


/*------------------------------------------------------------------------
**	Target control block initialisation.
**------------------------------------------------------------------------
**	This data काष्ठाure is fully initialized after a SCSI command 
**	has been successfully completed क्रम this target.
**	It contains a SCRIPT that is called on target reselection.
**------------------------------------------------------------------------
*/
अटल व्योम ncr_init_tcb (काष्ठा ncb *np, u_अक्षर tn)
अणु
	काष्ठा tcb *tp = &np->target[tn];
	ncrcmd copy_1 = np->features & FE_PFEN ? SCR_COPY(1) : SCR_COPY_F(1);
	पूर्णांक th = tn & 3;
	पूर्णांक i;

	/*
	**	Jump to next tcb अगर SFBR करोes not match this target.
	**	JUMP  IF (SFBR != #target#), @(next tcb)
	*/
	tp->jump_tcb.l_cmd   =
		cpu_to_scr((SCR_JUMP ^ IFFALSE (DATA (0x80 + tn))));
	tp->jump_tcb.l_paddr = np->jump_tcb[th].l_paddr;

	/*
	**	Load the synchronous transfer रेजिस्टर.
	**	COPY @(tp->sval), @(sxfer)
	*/
	tp->माला_लोcr[0] =	cpu_to_scr(copy_1);
	tp->माला_लोcr[1] = cpu_to_scr(vtobus (&tp->sval));
#अगर_घोषित SCSI_NCR_BIG_ENDIAN
	tp->माला_लोcr[2] = cpu_to_scr(ncr_reg_bus_addr(nc_sxfer) ^ 3);
#अन्यथा
	tp->माला_लोcr[2] = cpu_to_scr(ncr_reg_bus_addr(nc_sxfer));
#पूर्ण_अगर

	/*
	**	Load the timing रेजिस्टर.
	**	COPY @(tp->wval), @(scntl3)
	*/
	tp->माला_लोcr[3] =	cpu_to_scr(copy_1);
	tp->माला_लोcr[4] = cpu_to_scr(vtobus (&tp->wval));
#अगर_घोषित SCSI_NCR_BIG_ENDIAN
	tp->माला_लोcr[5] = cpu_to_scr(ncr_reg_bus_addr(nc_scntl3) ^ 3);
#अन्यथा
	tp->माला_लोcr[5] = cpu_to_scr(ncr_reg_bus_addr(nc_scntl3));
#पूर्ण_अगर

	/*
	**	Get the IDENTIFY message and the lun.
	**	CALL @script(resel_lun)
	*/
	tp->call_lun.l_cmd   = cpu_to_scr(SCR_CALL);
	tp->call_lun.l_paddr = cpu_to_scr(NCB_SCRIPT_PHYS (np, resel_lun));

	/*
	**	Look क्रम the lun control block of this nexus.
	**	For i = 0 to 3
	**		JUMP ^ IFTRUE (MASK (i, 3)), @(next_lcb)
	*/
	क्रम (i = 0 ; i < 4 ; i++) अणु
		tp->jump_lcb[i].l_cmd   =
				cpu_to_scr((SCR_JUMP ^ IFTRUE (MASK (i, 3))));
		tp->jump_lcb[i].l_paddr =
				cpu_to_scr(NCB_SCRIPTH_PHYS (np, bad_identअगरy));
	पूर्ण

	/*
	**	Link this target control block to the JUMP chain.
	*/
	np->jump_tcb[th].l_paddr = cpu_to_scr(vtobus (&tp->jump_tcb));

	/*
	**	These निश्चित's should be moved at driver initialisations.
	*/
#अगर_घोषित SCSI_NCR_BIG_ENDIAN
	BUG_ON(((दुरत्व(काष्ठा ncr_reg, nc_sxfer) ^
		 दुरत्व(काष्ठा tcb    , sval    )) &3) != 3);
	BUG_ON(((दुरत्व(काष्ठा ncr_reg, nc_scntl3) ^
		 दुरत्व(काष्ठा tcb    , wval    )) &3) != 3);
#अन्यथा
	BUG_ON(((दुरत्व(काष्ठा ncr_reg, nc_sxfer) ^
		 दुरत्व(काष्ठा tcb    , sval    )) &3) != 0);
	BUG_ON(((दुरत्व(काष्ठा ncr_reg, nc_scntl3) ^
		 दुरत्व(काष्ठा tcb    , wval    )) &3) != 0);
#पूर्ण_अगर
पूर्ण


/*------------------------------------------------------------------------
**	Lun control block allocation and initialization.
**------------------------------------------------------------------------
**	This data काष्ठाure is allocated and initialized after a SCSI 
**	command has been successfully completed क्रम this target/lun.
**------------------------------------------------------------------------
*/
अटल काष्ठा lcb *ncr_alloc_lcb (काष्ठा ncb *np, u_अक्षर tn, u_अक्षर ln)
अणु
	काष्ठा tcb *tp = &np->target[tn];
	काष्ठा lcb *lp = tp->lp[ln];
	ncrcmd copy_4 = np->features & FE_PFEN ? SCR_COPY(4) : SCR_COPY_F(4);
	पूर्णांक lh = ln & 3;

	/*
	**	Alपढ़ोy करोne, वापस.
	*/
	अगर (lp)
		वापस lp;

	/*
	**	Allocate the lcb.
	*/
	lp = m_सुस्मृति_dma(माप(काष्ठा lcb), "LCB");
	अगर (!lp)
		जाओ fail;
	स_रखो(lp, 0, माप(*lp));
	tp->lp[ln] = lp;

	/*
	**	Initialize the target control block अगर not yet.
	*/
	अगर (!tp->jump_tcb.l_cmd)
		ncr_init_tcb(np, tn);

	/*
	**	Initialize the CCB queue headers.
	*/
	INIT_LIST_HEAD(&lp->मुक्त_ccbq);
	INIT_LIST_HEAD(&lp->busy_ccbq);
	INIT_LIST_HEAD(&lp->रुको_ccbq);
	INIT_LIST_HEAD(&lp->skip_ccbq);

	/*
	**	Set max CCBs to 1 and use the शेष 1 entry 
	**	jump table by शेष.
	*/
	lp->maxnxs	= 1;
	lp->jump_ccb	= &lp->jump_ccb_0;
	lp->p_jump_ccb	= cpu_to_scr(vtobus(lp->jump_ccb));

	/*
	**	Initilialyze the reselect script:
	**
	**	Jump to next lcb अगर SFBR करोes not match this lun.
	**	Load TEMP with the CCB direct jump table bus address.
	**	Get the SIMPLE TAG message and the tag.
	**
	**	JUMP  IF (SFBR != #lun#), @(next lcb)
	**	COPY @(lp->p_jump_ccb),	  @(temp)
	**	JUMP @script(resel_notag)
	*/
	lp->jump_lcb.l_cmd   =
		cpu_to_scr((SCR_JUMP ^ IFFALSE (MASK (0x80+ln, 0xff))));
	lp->jump_lcb.l_paddr = tp->jump_lcb[lh].l_paddr;

	lp->load_jump_ccb[0] = cpu_to_scr(copy_4);
	lp->load_jump_ccb[1] = cpu_to_scr(vtobus (&lp->p_jump_ccb));
	lp->load_jump_ccb[2] = cpu_to_scr(ncr_reg_bus_addr(nc_temp));

	lp->jump_tag.l_cmd   = cpu_to_scr(SCR_JUMP);
	lp->jump_tag.l_paddr = cpu_to_scr(NCB_SCRIPT_PHYS (np, resel_notag));

	/*
	**	Link this lun control block to the JUMP chain.
	*/
	tp->jump_lcb[lh].l_paddr = cpu_to_scr(vtobus (&lp->jump_lcb));

	/*
	**	Initialize command queuing control.
	*/
	lp->busyccbs	= 1;
	lp->queuedccbs	= 1;
	lp->queuedepth	= 1;
fail:
	वापस lp;
पूर्ण


/*------------------------------------------------------------------------
**	Lun control block setup on INQUIRY data received.
**------------------------------------------------------------------------
**	We only support WIDE, SYNC क्रम tarमाला_लो and CMDQ क्रम logical units.
**	This setup is करोne on each INQUIRY since we are expecting user 
**	will play with CHANGE DEFINITION commands. :-)
**------------------------------------------------------------------------
*/
अटल काष्ठा lcb *ncr_setup_lcb (काष्ठा ncb *np, काष्ठा scsi_device *sdev)
अणु
	अचिन्हित अक्षर tn = sdev->id, ln = sdev->lun;
	काष्ठा tcb *tp = &np->target[tn];
	काष्ठा lcb *lp = tp->lp[ln];

	/* If no lcb, try to allocate it.  */
	अगर (!lp && !(lp = ncr_alloc_lcb(np, tn, ln)))
		जाओ fail;

	/*
	**	If unit supports tagged commands, allocate the 
	**	CCB JUMP table अगर not yet.
	*/
	अगर (sdev->tagged_supported && lp->jump_ccb == &lp->jump_ccb_0) अणु
		पूर्णांक i;
		lp->jump_ccb = m_सुस्मृति_dma(256, "JUMP_CCB");
		अगर (!lp->jump_ccb) अणु
			lp->jump_ccb = &lp->jump_ccb_0;
			जाओ fail;
		पूर्ण
		lp->p_jump_ccb = cpu_to_scr(vtobus(lp->jump_ccb));
		क्रम (i = 0 ; i < 64 ; i++)
			lp->jump_ccb[i] =
				cpu_to_scr(NCB_SCRIPTH_PHYS (np, bad_i_t_l_q));
		क्रम (i = 0 ; i < MAX_TAGS ; i++)
			lp->cb_tags[i] = i;
		lp->maxnxs = MAX_TAGS;
		lp->tags_sसमय = jअगरfies + 3*HZ;
		ncr_setup_tags (np, sdev);
	पूर्ण


fail:
	वापस lp;
पूर्ण

/*==========================================================
**
**
**	Build Scatter Gather Block
**
**
**==========================================================
**
**	The transfer area may be scattered among
**	several non adjacent physical pages.
**
**	We may use MAX_SCATTER blocks.
**
**----------------------------------------------------------
*/

/*
**	We try to reduce the number of पूर्णांकerrupts caused
**	by unexpected phase changes due to disconnects.
**	A typical harddisk may disconnect beक्रमe ANY block.
**	If we wanted to aव्योम unexpected phase changes at all
**	we had to use a अवरोध poपूर्णांक every 512 bytes.
**	Of course the number of scatter/gather blocks is
**	limited.
**	Under Linux, the scatter/gatter blocks are provided by 
**	the generic driver. We just have to copy addresses and 
**	sizes to the data segment array.
*/

अटल पूर्णांक ncr_scatter(काष्ठा ncb *np, काष्ठा ccb *cp, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक segment	= 0;
	पूर्णांक use_sg	= scsi_sg_count(cmd);

	cp->data_len	= 0;

	use_sg = map_scsi_sg_data(np, cmd);
	अगर (use_sg > 0) अणु
		काष्ठा scatterlist *sg;
		काष्ठा scr_tblmove *data;

		अगर (use_sg > MAX_SCATTER) अणु
			unmap_scsi_data(np, cmd);
			वापस -1;
		पूर्ण

		data = &cp->phys.data[MAX_SCATTER - use_sg];

		scsi_क्रम_each_sg(cmd, sg, use_sg, segment) अणु
			dma_addr_t baddr = sg_dma_address(sg);
			अचिन्हित पूर्णांक len = sg_dma_len(sg);

			ncr_build_sge(np, &data[segment], baddr, len);
			cp->data_len += len;
		पूर्ण
	पूर्ण अन्यथा
		segment = -2;

	वापस segment;
पूर्ण

/*==========================================================
**
**
**	Test the bus snoop logic :-(
**
**	Has to be called with पूर्णांकerrupts disabled.
**
**
**==========================================================
*/

अटल पूर्णांक __init ncr_regtest (काष्ठा ncb* np)
अणु
	रेजिस्टर अस्थिर u32 data;
	/*
	**	ncr रेजिस्टरs may NOT be cached.
	**	ग_लिखो 0xffffffff to a पढ़ो only रेजिस्टर area,
	**	and try to पढ़ो it back.
	*/
	data = 0xffffffff;
	OUTL_OFF(दुरत्व(काष्ठा ncr_reg, nc_dstat), data);
	data = INL_OFF(दुरत्व(काष्ठा ncr_reg, nc_dstat));
#अगर 1
	अगर (data == 0xffffffff) अणु
#अन्यथा
	अगर ((data & 0xe2f0fffd) != 0x02000080) अणु
#पूर्ण_अगर
		prपूर्णांकk ("CACHE TEST FAILED: reg dstat-sstat2 readback %x.\n",
			(अचिन्हित) data);
		वापस (0x10);
	पूर्ण
	वापस (0);
पूर्ण

अटल पूर्णांक __init ncr_snooptest (काष्ठा ncb* np)
अणु
	u32	ncr_rd, ncr_wr, ncr_bk, host_rd, host_wr, pc;
	पूर्णांक	i, err=0;
	अगर (np->reg) अणु
		err |= ncr_regtest (np);
		अगर (err)
			वापस (err);
	पूर्ण

	/* init */
	pc  = NCB_SCRIPTH_PHYS (np, snooptest);
	host_wr = 1;
	ncr_wr  = 2;
	/*
	**	Set memory and रेजिस्टर.
	*/
	np->ncr_cache = cpu_to_scr(host_wr);
	OUTL (nc_temp, ncr_wr);
	/*
	**	Start script (exchange values)
	*/
	OUTL_DSP (pc);
	/*
	**	Wait 'til करोne (with समयout)
	*/
	क्रम (i=0; i<NCR_SNOOP_TIMEOUT; i++)
		अगर (INB(nc_istat) & (INTF|SIP|DIP))
			अवरोध;
	/*
	**	Save termination position.
	*/
	pc = INL (nc_dsp);
	/*
	**	Read memory and रेजिस्टर.
	*/
	host_rd = scr_to_cpu(np->ncr_cache);
	ncr_rd  = INL (nc_scratcha);
	ncr_bk  = INL (nc_temp);
	/*
	**	Reset ncr chip
	*/
	ncr_chip_reset(np, 100);
	/*
	**	check क्रम समयout
	*/
	अगर (i>=NCR_SNOOP_TIMEOUT) अणु
		prपूर्णांकk ("CACHE TEST FAILED: timeout.\n");
		वापस (0x20);
	पूर्ण
	/*
	**	Check termination position.
	*/
	अगर (pc != NCB_SCRIPTH_PHYS (np, snoखोलोd)+8) अणु
		prपूर्णांकk ("CACHE TEST FAILED: script execution failed.\n");
		prपूर्णांकk ("start=%08lx, pc=%08lx, end=%08lx\n", 
			(u_दीर्घ) NCB_SCRIPTH_PHYS (np, snooptest), (u_दीर्घ) pc,
			(u_दीर्घ) NCB_SCRIPTH_PHYS (np, snoखोलोd) +8);
		वापस (0x40);
	पूर्ण
	/*
	**	Show results.
	*/
	अगर (host_wr != ncr_rd) अणु
		prपूर्णांकk ("CACHE TEST FAILED: host wrote %d, ncr read %d.\n",
			(पूर्णांक) host_wr, (पूर्णांक) ncr_rd);
		err |= 1;
	पूर्ण
	अगर (host_rd != ncr_wr) अणु
		prपूर्णांकk ("CACHE TEST FAILED: ncr wrote %d, host read %d.\n",
			(पूर्णांक) ncr_wr, (पूर्णांक) host_rd);
		err |= 2;
	पूर्ण
	अगर (ncr_bk != ncr_wr) अणु
		prपूर्णांकk ("CACHE TEST FAILED: ncr wrote %d, read back %d.\n",
			(पूर्णांक) ncr_wr, (पूर्णांक) ncr_bk);
		err |= 4;
	पूर्ण
	वापस (err);
पूर्ण

/*==========================================================
**
**	Determine the ncr's घड़ी frequency.
**	This is essential क्रम the negotiation
**	of the synchronous transfer rate.
**
**==========================================================
**
**	Note: we have to वापस the correct value.
**	THERE IS NO SAFE DEFAULT VALUE.
**
**	Most NCR/SYMBIOS boards are delivered with a 40 Mhz घड़ी.
**	53C860 and 53C875 rev. 1 support fast20 transfers but 
**	करो not have a घड़ी द्विगुनr and so are provided with a 
**	80 MHz घड़ी. All other fast20 boards incorporate a द्विगुनr 
**	and so should be delivered with a 40 MHz घड़ी.
**	The future fast40 chips (895/895) use a 40 Mhz base घड़ी 
**	and provide a घड़ी quadrupler (160 Mhz). The code below 
**	tries to deal as cleverly as possible with all this stuff.
**
**----------------------------------------------------------
*/

/*
 *	Select NCR SCSI घड़ी frequency
 */
अटल व्योम ncr_selectघड़ी(काष्ठा ncb *np, u_अक्षर scntl3)
अणु
	अगर (np->multiplier < 2) अणु
		OUTB(nc_scntl3,	scntl3);
		वापस;
	पूर्ण

	अगर (bootverbose >= 2)
		prपूर्णांकk ("%s: enabling clock multiplier\n", ncr_name(np));

	OUTB(nc_stest1, DBLEN);	   /* Enable घड़ी multiplier		  */
	अगर (np->multiplier > 2) अणु  /* Poll bit 5 of stest4 क्रम quadrupler */
		पूर्णांक i = 20;
		जबतक (!(INB(nc_stest4) & LCKFRQ) && --i > 0)
			udelay(20);
		अगर (!i)
			prपूर्णांकk("%s: the chip cannot lock the frequency\n", ncr_name(np));
	पूर्ण अन्यथा			/* Wait 20 micro-seconds क्रम द्विगुनr	*/
		udelay(20);
	OUTB(nc_stest3, HSC);		/* Halt the scsi घड़ी		*/
	OUTB(nc_scntl3,	scntl3);
	OUTB(nc_stest1, (DBLEN|DBLSEL));/* Select घड़ी multiplier	*/
	OUTB(nc_stest3, 0x00);		/* Restart scsi घड़ी 		*/
पूर्ण


/*
 *	calculate NCR SCSI घड़ी frequency (in KHz)
 */
अटल अचिन्हित __init ncrgetfreq (काष्ठा ncb *np, पूर्णांक gen)
अणु
	अचिन्हित ms = 0;
	अक्षर count = 0;

	/*
	 * Measure GEN समयr delay in order 
	 * to calculate SCSI घड़ी frequency
	 *
	 * This code will never execute too
	 * many loop iterations (अगर DELAY is 
	 * reasonably correct). It could get
	 * too low a delay (too high a freq.)
	 * अगर the CPU is slow executing the 
	 * loop क्रम some reason (an NMI, क्रम
	 * example). For this reason we will
	 * अगर multiple measurements are to be 
	 * perक्रमmed trust the higher delay 
	 * (lower frequency वापसed).
	 */
	OUTB (nc_stest1, 0);	/* make sure घड़ी द्विगुनr is OFF */
	OUTW (nc_sien , 0);	/* mask all scsi पूर्णांकerrupts */
	(व्योम) INW (nc_sist);	/* clear pending scsi पूर्णांकerrupt */
	OUTB (nc_dien , 0);	/* mask all dma पूर्णांकerrupts */
	(व्योम) INW (nc_sist);	/* another one, just to be sure :) */
	OUTB (nc_scntl3, 4);	/* set pre-scaler to भागide by 3 */
	OUTB (nc_sसमय1, 0);	/* disable general purpose समयr */
	OUTB (nc_sसमय1, gen);	/* set to nominal delay of 1<<gen * 125us */
	जबतक (!(INW(nc_sist) & GEN) && ms++ < 100000) अणु
		क्रम (count = 0; count < 10; count ++)
			udelay(100);	/* count ms */
	पूर्ण
	OUTB (nc_sसमय1, 0);	/* disable general purpose समयr */
 	/*
 	 * set prescaler to भागide by whatever 0 means
 	 * 0 ought to choose भागide by 2, but appears
 	 * to set भागide by 3.5 mode in my 53c810 ...
 	 */
 	OUTB (nc_scntl3, 0);

	अगर (bootverbose >= 2)
		prपूर्णांकk ("%s: Delay (GEN=%d): %u msec\n", ncr_name(np), gen, ms);
  	/*
 	 * adjust क्रम prescaler, and convert पूर्णांकo KHz 
  	 */
	वापस ms ? ((1 << gen) * 4340) / ms : 0;
पूर्ण

/*
 *	Get/probe NCR SCSI घड़ी frequency
 */
अटल व्योम __init ncr_अ_लोlock (काष्ठा ncb *np, पूर्णांक mult)
अणु
	अचिन्हित अक्षर scntl3 = INB(nc_scntl3);
	अचिन्हित अक्षर stest1 = INB(nc_stest1);
	अचिन्हित f1;

	np->multiplier = 1;
	f1 = 40000;

	/*
	**	True with 875 or 895 with घड़ी multiplier selected
	*/
	अगर (mult > 1 && (stest1 & (DBLEN+DBLSEL)) == DBLEN+DBLSEL) अणु
		अगर (bootverbose >= 2)
			prपूर्णांकk ("%s: clock multiplier found\n", ncr_name(np));
		np->multiplier = mult;
	पूर्ण

	/*
	**	If multiplier not found or scntl3 not 7,5,3,
	**	reset chip and get frequency from general purpose समयr.
	**	Otherwise trust scntl3 BIOS setting.
	*/
	अगर (np->multiplier != mult || (scntl3 & 7) < 3 || !(scntl3 & 1)) अणु
		अचिन्हित f2;

		ncr_chip_reset(np, 5);

		(व्योम) ncrgetfreq (np, 11);	/* throw away first result */
		f1 = ncrgetfreq (np, 11);
		f2 = ncrgetfreq (np, 11);

		अगर(bootverbose)
			prपूर्णांकk ("%s: NCR clock is %uKHz, %uKHz\n", ncr_name(np), f1, f2);

		अगर (f1 > f2) f1 = f2;		/* trust lower result	*/

		अगर	(f1 <	45000)		f1 =  40000;
		अन्यथा अगर (f1 <	55000)		f1 =  50000;
		अन्यथा				f1 =  80000;

		अगर (f1 < 80000 && mult > 1) अणु
			अगर (bootverbose >= 2)
				prपूर्णांकk ("%s: clock multiplier assumed\n", ncr_name(np));
			np->multiplier	= mult;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर	((scntl3 & 7) == 3)	f1 =  40000;
		अन्यथा अगर	((scntl3 & 7) == 5)	f1 =  80000;
		अन्यथा 				f1 = 160000;

		f1 /= np->multiplier;
	पूर्ण

	/*
	**	Compute controller synchronous parameters.
	*/
	f1		*= np->multiplier;
	np->घड़ी_khz	= f1;
पूर्ण

/*===================== LINUX ENTRY POINTS SECTION ==========================*/

अटल पूर्णांक ncr53c8xx_slave_alloc(काष्ठा scsi_device *device)
अणु
	काष्ठा Scsi_Host *host = device->host;
	काष्ठा ncb *np = ((काष्ठा host_data *) host->hostdata)->ncb;
	काष्ठा tcb *tp = &np->target[device->id];
	tp->starget = device->sdev_target;

	वापस 0;
पूर्ण

अटल पूर्णांक ncr53c8xx_slave_configure(काष्ठा scsi_device *device)
अणु
	काष्ठा Scsi_Host *host = device->host;
	काष्ठा ncb *np = ((काष्ठा host_data *) host->hostdata)->ncb;
	काष्ठा tcb *tp = &np->target[device->id];
	काष्ठा lcb *lp = tp->lp[device->lun];
	पूर्णांक numtags, depth_to_use;

	ncr_setup_lcb(np, device);

	/*
	**	Select queue depth from driver setup.
	**	Donnot use more than configured by user.
	**	Use at least 2.
	**	Donnot use more than our maximum.
	*/
	numtags = device_queue_depth(np->unit, device->id, device->lun);
	अगर (numtags > tp->usrtags)
		numtags = tp->usrtags;
	अगर (!device->tagged_supported)
		numtags = 1;
	depth_to_use = numtags;
	अगर (depth_to_use < 2)
		depth_to_use = 2;
	अगर (depth_to_use > MAX_TAGS)
		depth_to_use = MAX_TAGS;

	scsi_change_queue_depth(device, depth_to_use);

	/*
	**	Since the queue depth is not tunable under Linux,
	**	we need to know this value in order not to 
	**	announce stupid things to user.
	**
	**	XXX(hch): As of Linux 2.6 it certainly _is_ tunable..
	**		  In fact we just tuned it, or did I miss
	**		  something important? :)
	*/
	अगर (lp) अणु
		lp->numtags = lp->maxtags = numtags;
		lp->scdev_depth = depth_to_use;
	पूर्ण
	ncr_setup_tags (np, device);

#अगर_घोषित DEBUG_NCR53C8XX
	prपूर्णांकk("ncr53c8xx_select_queue_depth: host=%d, id=%d, lun=%d, depth=%d\n",
	       np->unit, device->id, device->lun, depth_to_use);
#पूर्ण_अगर

	अगर (spi_support_sync(device->sdev_target) &&
	    !spi_initial_dv(device->sdev_target))
		spi_dv_device(device);
	वापस 0;
पूर्ण

अटल पूर्णांक ncr53c8xx_queue_command_lck (काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
     काष्ठा ncb *np = ((काष्ठा host_data *) cmd->device->host->hostdata)->ncb;
     अचिन्हित दीर्घ flags;
     पूर्णांक sts;

#अगर_घोषित DEBUG_NCR53C8XX
prपूर्णांकk("ncr53c8xx_queue_command\n");
#पूर्ण_अगर

     cmd->scsi_करोne     = करोne;
     cmd->host_scribble = शून्य;
     cmd->__data_mapped = 0;
     cmd->__data_mapping = 0;

     spin_lock_irqsave(&np->smp_lock, flags);

     अगर ((sts = ncr_queue_command(np, cmd)) != DID_OK) अणु
	     set_host_byte(cmd, sts);
#अगर_घोषित DEBUG_NCR53C8XX
prपूर्णांकk("ncr53c8xx : command not queued - result=%d\n", sts);
#पूर्ण_अगर
     पूर्ण
#अगर_घोषित DEBUG_NCR53C8XX
     अन्यथा
prपूर्णांकk("ncr53c8xx : command successfully queued\n");
#पूर्ण_अगर

     spin_unlock_irqrestore(&np->smp_lock, flags);

     अगर (sts != DID_OK) अणु
          unmap_scsi_data(np, cmd);
          करोne(cmd);
	  sts = 0;
     पूर्ण

     वापस sts;
पूर्ण

अटल DEF_SCSI_QCMD(ncr53c8xx_queue_command)

irqवापस_t ncr53c8xx_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
     अचिन्हित दीर्घ flags;
     काष्ठा Scsi_Host *shost = (काष्ठा Scsi_Host *)dev_id;
     काष्ठा host_data *host_data = (काष्ठा host_data *)shost->hostdata;
     काष्ठा ncb *np = host_data->ncb;
     काष्ठा scsi_cmnd *करोne_list;

#अगर_घोषित DEBUG_NCR53C8XX
     prपूर्णांकk("ncr53c8xx : interrupt received\n");
#पूर्ण_अगर

     अगर (DEBUG_FLAGS & DEBUG_TINY) prपूर्णांकk ("[");

     spin_lock_irqsave(&np->smp_lock, flags);
     ncr_exception(np);
     करोne_list     = np->करोne_list;
     np->करोne_list = शून्य;
     spin_unlock_irqrestore(&np->smp_lock, flags);

     अगर (DEBUG_FLAGS & DEBUG_TINY) prपूर्णांकk ("]\n");

     अगर (करोne_list)
	     ncr_flush_करोne_cmds(करोne_list);
     वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ncr53c8xx_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ncb *np = from_समयr(np, t, समयr);
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_cmnd *करोne_list;

	spin_lock_irqsave(&np->smp_lock, flags);
	ncr_समयout(np);
	करोne_list     = np->करोne_list;
	np->करोne_list = शून्य;
	spin_unlock_irqrestore(&np->smp_lock, flags);

	अगर (करोne_list)
		ncr_flush_करोne_cmds(करोne_list);
पूर्ण

अटल पूर्णांक ncr53c8xx_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ncb *np = ((काष्ठा host_data *) cmd->device->host->hostdata)->ncb;
	पूर्णांक sts;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_cmnd *करोne_list;

	/*
	 * If the mid-level driver told us reset is synchronous, it seems 
	 * that we must call the करोne() callback क्रम the involved command, 
	 * even अगर this command was not queued to the low-level driver, 
	 * beक्रमe वापसing SUCCESS.
	 */

	spin_lock_irqsave(&np->smp_lock, flags);
	sts = ncr_reset_bus(np, cmd, 1);

	करोne_list     = np->करोne_list;
	np->करोne_list = शून्य;
	spin_unlock_irqrestore(&np->smp_lock, flags);

	ncr_flush_करोne_cmds(करोne_list);

	वापस sts;
पूर्ण

#अगर 0 /* unused and broken */
अटल पूर्णांक ncr53c8xx_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ncb *np = ((काष्ठा host_data *) cmd->device->host->hostdata)->ncb;
	पूर्णांक sts;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_cmnd *करोne_list;

	prपूर्णांकk("ncr53c8xx_abort\n");

	NCR_LOCK_NCB(np, flags);

	sts = ncr_पात_command(np, cmd);
out:
	करोne_list     = np->करोne_list;
	np->करोne_list = शून्य;
	NCR_UNLOCK_NCB(np, flags);

	ncr_flush_करोne_cmds(करोne_list);

	वापस sts;
पूर्ण
#पूर्ण_अगर


/*
**	Scsi command रुकोing list management.
**
**	It may happen that we cannot insert a scsi command पूर्णांकo the start queue,
**	in the following circumstances.
** 		Too few pपुनः_स्मृतिated ccb(s), 
**		maxtags < cmd_per_lun of the Linux host control block,
**		etc...
**	Such scsi commands are inserted पूर्णांकo a रुकोing list.
**	When a scsi command complete, we try to requeue the commands of the
**	रुकोing list.
*/

#घोषणा next_wcmd host_scribble

अटल व्योम insert_पूर्णांकo_रुकोing_list(काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_cmnd *wcmd;

#अगर_घोषित DEBUG_WAITING_LIST
	prपूर्णांकk("%s: cmd %lx inserted into waiting list\n", ncr_name(np), (u_दीर्घ) cmd);
#पूर्ण_अगर
	cmd->next_wcmd = शून्य;
	अगर (!(wcmd = np->रुकोing_list)) np->रुकोing_list = cmd;
	अन्यथा अणु
		जबतक (wcmd->next_wcmd)
			wcmd = (काष्ठा scsi_cmnd *) wcmd->next_wcmd;
		wcmd->next_wcmd = (अक्षर *) cmd;
	पूर्ण
पूर्ण

अटल काष्ठा scsi_cmnd *retrieve_from_रुकोing_list(पूर्णांक to_हटाओ, काष्ठा ncb *np, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_cmnd **pcmd = &np->रुकोing_list;

	जबतक (*pcmd) अणु
		अगर (cmd == *pcmd) अणु
			अगर (to_हटाओ) अणु
				*pcmd = (काष्ठा scsi_cmnd *) cmd->next_wcmd;
				cmd->next_wcmd = शून्य;
			पूर्ण
#अगर_घोषित DEBUG_WAITING_LIST
	prपूर्णांकk("%s: cmd %lx retrieved from waiting list\n", ncr_name(np), (u_दीर्घ) cmd);
#पूर्ण_अगर
			वापस cmd;
		पूर्ण
		pcmd = (काष्ठा scsi_cmnd **) &(*pcmd)->next_wcmd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम process_रुकोing_list(काष्ठा ncb *np, पूर्णांक sts)
अणु
	काष्ठा scsi_cmnd *रुकोing_list, *wcmd;

	रुकोing_list = np->रुकोing_list;
	np->रुकोing_list = शून्य;

#अगर_घोषित DEBUG_WAITING_LIST
	अगर (रुकोing_list) prपूर्णांकk("%s: waiting_list=%lx processing sts=%d\n", ncr_name(np), (u_दीर्घ) रुकोing_list, sts);
#पूर्ण_अगर
	जबतक ((wcmd = रुकोing_list) != शून्य) अणु
		रुकोing_list = (काष्ठा scsi_cmnd *) wcmd->next_wcmd;
		wcmd->next_wcmd = शून्य;
		अगर (sts == DID_OK) अणु
#अगर_घोषित DEBUG_WAITING_LIST
	prपूर्णांकk("%s: cmd %lx trying to requeue\n", ncr_name(np), (u_दीर्घ) wcmd);
#पूर्ण_अगर
			sts = ncr_queue_command(np, wcmd);
		पूर्ण
		अगर (sts != DID_OK) अणु
#अगर_घोषित DEBUG_WAITING_LIST
	prपूर्णांकk("%s: cmd %lx done forced sts=%d\n", ncr_name(np), (u_दीर्घ) wcmd, sts);
#पूर्ण_अगर
			set_host_byte(wcmd, sts);
			ncr_queue_करोne_cmd(np, wcmd);
		पूर्ण
	पूर्ण
पूर्ण

#अघोषित next_wcmd

अटल sमाप_प्रकार show_ncr53c8xx_revision(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा host_data *host_data = (काष्ठा host_data *)host->hostdata;
  
	वापस snम_लिखो(buf, 20, "0x%x\n", host_data->ncb->revision_id);
पूर्ण
  
अटल काष्ठा device_attribute ncr53c8xx_revision_attr = अणु
	.attr	= अणु .name = "revision", .mode = S_IRUGO, पूर्ण,
	.show	= show_ncr53c8xx_revision,
पूर्ण;
  
अटल काष्ठा device_attribute *ncr53c8xx_host_attrs[] = अणु
	&ncr53c8xx_revision_attr,
	शून्य
पूर्ण;

/*==========================================================
**
**	Boot command line.
**
**==========================================================
*/
#अगर_घोषित	MODULE
अक्षर *ncr53c8xx;	/* command line passed by insmod */
module_param(ncr53c8xx, अक्षरp, 0);
#पूर्ण_अगर

#अगर_अघोषित MODULE
अटल पूर्णांक __init ncr53c8xx_setup(अक्षर *str)
अणु
	वापस sym53c8xx__setup(str);
पूर्ण

__setup("ncr53c8xx=", ncr53c8xx_setup);
#पूर्ण_अगर


/*
 *	Host attach and initialisations.
 *
 *	Allocate host data and ncb काष्ठाure.
 *	Request IO region and remap MMIO region.
 *	Do chip initialization.
 *	If all is OK, install पूर्णांकerrupt handling and
 *	start the समयr daemon.
 */
काष्ठा Scsi_Host * __init ncr_attach(काष्ठा scsi_host_ढाँचा *tpnt,
					पूर्णांक unit, काष्ठा ncr_device *device)
अणु
	काष्ठा host_data *host_data;
	काष्ठा ncb *np = शून्य;
	काष्ठा Scsi_Host *instance = शून्य;
	u_दीर्घ flags = 0;
	पूर्णांक i;

	अगर (!tpnt->name)
		tpnt->name	= SCSI_NCR_DRIVER_NAME;
	अगर (!tpnt->shost_attrs)
		tpnt->shost_attrs = ncr53c8xx_host_attrs;

	tpnt->queuecommand	= ncr53c8xx_queue_command;
	tpnt->slave_configure	= ncr53c8xx_slave_configure;
	tpnt->slave_alloc	= ncr53c8xx_slave_alloc;
	tpnt->eh_bus_reset_handler = ncr53c8xx_bus_reset;
	tpnt->can_queue		= SCSI_NCR_CAN_QUEUE;
	tpnt->this_id		= 7;
	tpnt->sg_tablesize	= SCSI_NCR_SG_TABLESIZE;
	tpnt->cmd_per_lun	= SCSI_NCR_CMD_PER_LUN;

	अगर (device->dअगरferential)
		driver_setup.dअगरf_support = device->dअगरferential;

	prपूर्णांकk(KERN_INFO "ncr53c720-%d: rev 0x%x irq %d\n",
		unit, device->chip.revision_id, device->slot.irq);

	instance = scsi_host_alloc(tpnt, माप(*host_data));
	अगर (!instance)
	        जाओ attach_error;
	host_data = (काष्ठा host_data *) instance->hostdata;

	np = __m_सुस्मृति_dma(device->dev, माप(काष्ठा ncb), "NCB");
	अगर (!np)
		जाओ attach_error;
	spin_lock_init(&np->smp_lock);
	np->dev = device->dev;
	np->p_ncb = vtobus(np);
	host_data->ncb = np;

	np->ccb = m_सुस्मृति_dma(माप(काष्ठा ccb), "CCB");
	अगर (!np->ccb)
		जाओ attach_error;

	/* Store input inक्रमmation in the host data काष्ठाure.  */
	np->unit	= unit;
	np->verbose	= driver_setup.verbose;
	प्र_लिखो(np->inst_name, "ncr53c720-%d", np->unit);
	np->revision_id	= device->chip.revision_id;
	np->features	= device->chip.features;
	np->घड़ी_भागn	= device->chip.nr_भागisor;
	np->maxoffs	= device->chip.offset_max;
	np->maxburst	= device->chip.burst_max;
	np->myaddr	= device->host_id;

	/* Allocate SCRIPTS areas.  */
	np->script0 = m_सुस्मृति_dma(माप(काष्ठा script), "SCRIPT");
	अगर (!np->script0)
		जाओ attach_error;
	np->scripth0 = m_सुस्मृति_dma(माप(काष्ठा scripth), "SCRIPTH");
	अगर (!np->scripth0)
		जाओ attach_error;

	समयr_setup(&np->समयr, ncr53c8xx_समयout, 0);

	/* Try to map the controller chip to भव and physical memory. */

	np->paddr	= device->slot.base;
	np->paddr2	= (np->features & FE_RAM) ? device->slot.base_2 : 0;

	अगर (device->slot.base_v)
		np->vaddr = device->slot.base_v;
	अन्यथा
		np->vaddr = ioremap(device->slot.base_c, 128);

	अगर (!np->vaddr) अणु
		prपूर्णांकk(KERN_ERR
			"%s: can't map memory mapped IO region\n",ncr_name(np));
		जाओ attach_error;
	पूर्ण अन्यथा अणु
		अगर (bootverbose > 1)
			prपूर्णांकk(KERN_INFO
				"%s: using memory mapped IO at virtual address 0x%lx\n", ncr_name(np), (u_दीर्घ) np->vaddr);
	पूर्ण

	/* Make the controller's रेजिस्टरs available.  Now the INB INW INL
	 * OUTB OUTW OUTL macros can be used safely.
	 */

	np->reg = (काष्ठा ncr_reg __iomem *)np->vaddr;

	/* Do chip dependent initialization.  */
	ncr_prepare_setting(np);

	अगर (np->paddr2 && माप(काष्ठा script) > 4096) अणु
		np->paddr2 = 0;
		prपूर्णांकk(KERN_WARNING "%s: script too large, NOT using on chip RAM.\n",
			ncr_name(np));
	पूर्ण

	instance->max_channel	= 0;
	instance->this_id       = np->myaddr;
	instance->max_id	= np->maxwide ? 16 : 8;
	instance->max_lun	= SCSI_NCR_MAX_LUN;
	instance->base		= (अचिन्हित दीर्घ) np->reg;
	instance->irq		= device->slot.irq;
	instance->unique_id	= device->slot.base;
	instance->dma_channel	= 0;
	instance->cmd_per_lun	= MAX_TAGS;
	instance->can_queue	= (MAX_START-4);
	/* This can happen अगर you क्रमget to call ncr53c8xx_init from
	 * your module_init */
	BUG_ON(!ncr53c8xx_transport_ढाँचा);
	instance->transportt	= ncr53c8xx_transport_ढाँचा;

	/* Patch script to physical addresses */
	ncr_script_fill(&script0, &scripth0);

	np->scripth	= np->scripth0;
	np->p_scripth	= vtobus(np->scripth);
	np->p_script	= (np->paddr2) ?  np->paddr2 : vtobus(np->script0);

	ncr_script_copy_and_bind(np, (ncrcmd *) &script0,
			(ncrcmd *) np->script0, माप(काष्ठा script));
	ncr_script_copy_and_bind(np, (ncrcmd *) &scripth0,
			(ncrcmd *) np->scripth0, माप(काष्ठा scripth));
	np->ccb->p_ccb	= vtobus (np->ccb);

	/* Patch the script क्रम LED support.  */

	अगर (np->features & FE_LED0) अणु
		np->script0->idle[0]  =
				cpu_to_scr(SCR_REG_REG(gpreg, SCR_OR,  0x01));
		np->script0->reselected[0] =
				cpu_to_scr(SCR_REG_REG(gpreg, SCR_AND, 0xfe));
		np->script0->start[0] =
				cpu_to_scr(SCR_REG_REG(gpreg, SCR_AND, 0xfe));
	पूर्ण

	/*
	 * Look क्रम the target control block of this nexus.
	 * For i = 0 to 3
	 *   JUMP ^ IFTRUE (MASK (i, 3)), @(next_lcb)
	 */
	क्रम (i = 0 ; i < 4 ; i++) अणु
		np->jump_tcb[i].l_cmd   =
				cpu_to_scr((SCR_JUMP ^ IFTRUE (MASK (i, 3))));
		np->jump_tcb[i].l_paddr =
				cpu_to_scr(NCB_SCRIPTH_PHYS (np, bad_target));
	पूर्ण

	ncr_chip_reset(np, 100);

	/* Now check the cache handling of the chipset.  */

	अगर (ncr_snooptest(np)) अणु
		prपूर्णांकk(KERN_ERR "CACHE INCORRECTLY CONFIGURED.\n");
		जाओ attach_error;
	पूर्ण

	/* Install the पूर्णांकerrupt handler.  */
	np->irq = device->slot.irq;

	/* Initialize the fixed part of the शेष ccb.  */
	ncr_init_ccb(np, np->ccb);

	/*
	 * After SCSI devices have been खोलोed, we cannot reset the bus
	 * safely, so we करो it here.  Interrupt handler करोes the real work.
	 * Process the reset exception अगर पूर्णांकerrupts are not enabled yet.
	 * Then enable disconnects.
	 */
	spin_lock_irqsave(&np->smp_lock, flags);
	अगर (ncr_reset_scsi_bus(np, 0, driver_setup.settle_delay) != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: FATAL ERROR: CHECK SCSI BUS - CABLES, TERMINATION, DEVICE POWER etc.!\n", ncr_name(np));

		spin_unlock_irqrestore(&np->smp_lock, flags);
		जाओ attach_error;
	पूर्ण
	ncr_exception(np);

	np->disc = 1;

	/*
	 * The middle-level SCSI driver करोes not रुको क्रम devices to settle.
	 * Wait synchronously अगर more than 2 seconds.
	 */
	अगर (driver_setup.settle_delay > 2) अणु
		prपूर्णांकk(KERN_INFO "%s: waiting %d seconds for scsi devices to settle...\n",
			ncr_name(np), driver_setup.settle_delay);
		mdelay(1000 * driver_setup.settle_delay);
	पूर्ण

	/* start the समयout daemon */
	np->lastसमय=0;
	ncr_समयout (np);

	/* use SIMPLE TAG messages by शेष */
#अगर_घोषित SCSI_NCR_ALWAYS_SIMPLE_TAG
	np->order = SIMPLE_QUEUE_TAG;
#पूर्ण_अगर

	spin_unlock_irqrestore(&np->smp_lock, flags);

	वापस instance;

 attach_error:
	अगर (!instance)
		वापस शून्य;
	prपूर्णांकk(KERN_INFO "%s: detaching...\n", ncr_name(np));
	अगर (!np)
		जाओ unरेजिस्टर;
	अगर (np->scripth0)
		m_मुक्त_dma(np->scripth0, माप(काष्ठा scripth), "SCRIPTH");
	अगर (np->script0)
		m_मुक्त_dma(np->script0, माप(काष्ठा script), "SCRIPT");
	अगर (np->ccb)
		m_मुक्त_dma(np->ccb, माप(काष्ठा ccb), "CCB");
	m_मुक्त_dma(np, माप(काष्ठा ncb), "NCB");
	host_data->ncb = शून्य;

 unरेजिस्टर:
	scsi_host_put(instance);

	वापस शून्य;
पूर्ण


व्योम ncr53c8xx_release(काष्ठा Scsi_Host *host)
अणु
	काष्ठा host_data *host_data = shost_priv(host);
#अगर_घोषित DEBUG_NCR53C8XX
	prपूर्णांकk("ncr53c8xx: release\n");
#पूर्ण_अगर
	अगर (host_data->ncb)
		ncr_detach(host_data->ncb);
	scsi_host_put(host);
पूर्ण

अटल व्योम ncr53c8xx_set_period(काष्ठा scsi_target *starget, पूर्णांक period)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ncb *np = ((काष्ठा host_data *)shost->hostdata)->ncb;
	काष्ठा tcb *tp = &np->target[starget->id];

	अगर (period > np->maxsync)
		period = np->maxsync;
	अन्यथा अगर (period < np->minsync)
		period = np->minsync;

	tp->usrsync = period;

	ncr_negotiate(np, tp);
पूर्ण

अटल व्योम ncr53c8xx_set_offset(काष्ठा scsi_target *starget, पूर्णांक offset)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ncb *np = ((काष्ठा host_data *)shost->hostdata)->ncb;
	काष्ठा tcb *tp = &np->target[starget->id];

	अगर (offset > np->maxoffs)
		offset = np->maxoffs;
	अन्यथा अगर (offset < 0)
		offset = 0;

	tp->maxoffs = offset;

	ncr_negotiate(np, tp);
पूर्ण

अटल व्योम ncr53c8xx_set_width(काष्ठा scsi_target *starget, पूर्णांक width)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ncb *np = ((काष्ठा host_data *)shost->hostdata)->ncb;
	काष्ठा tcb *tp = &np->target[starget->id];

	अगर (width > np->maxwide)
		width = np->maxwide;
	अन्यथा अगर (width < 0)
		width = 0;

	tp->usrwide = width;

	ncr_negotiate(np, tp);
पूर्ण

अटल व्योम ncr53c8xx_get_संकेतling(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ncb *np = ((काष्ठा host_data *)shost->hostdata)->ncb;
	क्रमागत spi_संकेत_type type;

	चयन (np->scsi_mode) अणु
	हाल SMODE_SE:
		type = SPI_SIGNAL_SE;
		अवरोध;
	हाल SMODE_HVD:
		type = SPI_SIGNAL_HVD;
		अवरोध;
	शेष:
		type = SPI_SIGNAL_UNKNOWN;
		अवरोध;
	पूर्ण
	spi_संकेतling(shost) = type;
पूर्ण

अटल काष्ठा spi_function_ढाँचा ncr53c8xx_transport_functions =  अणु
	.set_period	= ncr53c8xx_set_period,
	.show_period	= 1,
	.set_offset	= ncr53c8xx_set_offset,
	.show_offset	= 1,
	.set_width	= ncr53c8xx_set_width,
	.show_width	= 1,
	.get_संकेतling	= ncr53c8xx_get_संकेतling,
पूर्ण;

पूर्णांक __init ncr53c8xx_init(व्योम)
अणु
	ncr53c8xx_transport_ढाँचा = spi_attach_transport(&ncr53c8xx_transport_functions);
	अगर (!ncr53c8xx_transport_ढाँचा)
		वापस -ENODEV;
	वापस 0;
पूर्ण

व्योम ncr53c8xx_निकास(व्योम)
अणु
	spi_release_transport(ncr53c8xx_transport_ढाँचा);
पूर्ण
