<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#समावेश "sym_glue.h"

/*
 *  Simple घातer of two buddy-like generic allocator.
 *  Provides naturally aligned memory chunks.
 *
 *  This simple code is not पूर्णांकended to be fast, but to 
 *  provide घातer of 2 aligned memory allocations.
 *  Since the SCRIPTS processor only supplies 8 bit arithmetic, 
 *  this allocator allows simple and fast address calculations  
 *  from the SCRIPTS code. In addition, cache line alignment 
 *  is guaranteed क्रम घातer of 2 cache line size.
 *
 *  This allocator has been developed क्रम the Linux sym53c8xx  
 *  driver, since this O/S करोes not provide naturally aligned 
 *  allocations.
 *  It has the advantage of allowing the driver to use निजी 
 *  pages of memory that will be useful अगर we ever need to deal 
 *  with IO MMUs क्रम PCI.
 */
अटल व्योम *___sym_दो_स्मृति(m_pool_p mp, पूर्णांक size)
अणु
	पूर्णांक i = 0;
	पूर्णांक s = (1 << SYM_MEM_SHIFT);
	पूर्णांक j;
	व्योम *a;
	m_link_p h = mp->h;

	अगर (size > SYM_MEM_CLUSTER_SIZE)
		वापस शून्य;

	जबतक (size > s) अणु
		s <<= 1;
		++i;
	पूर्ण

	j = i;
	जबतक (!h[j].next) अणु
		अगर (s == SYM_MEM_CLUSTER_SIZE) अणु
			h[j].next = (m_link_p) M_GET_MEM_CLUSTER();
			अगर (h[j].next)
				h[j].next->next = शून्य;
			अवरोध;
		पूर्ण
		++j;
		s <<= 1;
	पूर्ण
	a = h[j].next;
	अगर (a) अणु
		h[j].next = h[j].next->next;
		जबतक (j > i) अणु
			j -= 1;
			s >>= 1;
			h[j].next = (m_link_p) (a+s);
			h[j].next->next = शून्य;
		पूर्ण
	पूर्ण
#अगर_घोषित DEBUG
	म_लिखो("___sym_malloc(%d) = %p\n", size, (व्योम *) a);
#पूर्ण_अगर
	वापस a;
पूर्ण

/*
 *  Counter-part of the generic allocator.
 */
अटल व्योम ___sym_mमुक्त(m_pool_p mp, व्योम *ptr, पूर्णांक size)
अणु
	पूर्णांक i = 0;
	पूर्णांक s = (1 << SYM_MEM_SHIFT);
	m_link_p q;
	अचिन्हित दीर्घ a, b;
	m_link_p h = mp->h;

#अगर_घोषित DEBUG
	म_लिखो("___sym_mfree(%p, %d)\n", ptr, size);
#पूर्ण_अगर

	अगर (size > SYM_MEM_CLUSTER_SIZE)
		वापस;

	जबतक (size > s) अणु
		s <<= 1;
		++i;
	पूर्ण

	a = (अचिन्हित दीर्घ)ptr;

	जबतक (1) अणु
		अगर (s == SYM_MEM_CLUSTER_SIZE) अणु
#अगर_घोषित SYM_MEM_FREE_UNUSED
			M_FREE_MEM_CLUSTER((व्योम *)a);
#अन्यथा
			((m_link_p) a)->next = h[i].next;
			h[i].next = (m_link_p) a;
#पूर्ण_अगर
			अवरोध;
		पूर्ण
		b = a ^ s;
		q = &h[i];
		जबतक (q->next && q->next != (m_link_p) b) अणु
			q = q->next;
		पूर्ण
		अगर (!q->next) अणु
			((m_link_p) a)->next = h[i].next;
			h[i].next = (m_link_p) a;
			अवरोध;
		पूर्ण
		q->next = q->next->next;
		a = a & b;
		s <<= 1;
		++i;
	पूर्ण
पूर्ण

/*
 *  Verbose and zeroing allocator that wrapps to the generic allocator.
 */
अटल व्योम *__sym_सुस्मृति2(m_pool_p mp, पूर्णांक size, अक्षर *name, पूर्णांक uflags)
अणु
	व्योम *p;

	p = ___sym_दो_स्मृति(mp, size);

	अगर (DEBUG_FLAGS & DEBUG_ALLOC) अणु
		म_लिखो ("new %-10s[%4d] @%p.\n", name, size, p);
	पूर्ण

	अगर (p)
		स_रखो(p, 0, size);
	अन्यथा अगर (uflags & SYM_MEM_WARN)
		म_लिखो ("__sym_calloc2: failed to allocate %s[%d]\n", name, size);
	वापस p;
पूर्ण
#घोषणा __sym_सुस्मृति(mp, s, n)	__sym_सुस्मृति2(mp, s, n, SYM_MEM_WARN)

/*
 *  Its counter-part.
 */
अटल व्योम __sym_mमुक्त(m_pool_p mp, व्योम *ptr, पूर्णांक size, अक्षर *name)
अणु
	अगर (DEBUG_FLAGS & DEBUG_ALLOC)
		म_लिखो ("freeing %-10s[%4d] @%p.\n", name, size, ptr);

	___sym_mमुक्त(mp, ptr, size);
पूर्ण

/*
 *  Default memory pool we करोnnot need to involve in DMA.
 *
 *  With DMA असलtraction, we use functions (methods), to 
 *  distinguish between non DMAable memory and DMAable memory.
 */
अटल व्योम *___mp0_get_mem_cluster(m_pool_p mp)
अणु
	व्योम *m = sym_get_mem_cluster();
	अगर (m)
		++mp->nump;
	वापस m;
पूर्ण

#अगर_घोषित	SYM_MEM_FREE_UNUSED
अटल व्योम ___mp0_मुक्त_mem_cluster(m_pool_p mp, व्योम *m)
अणु
	sym_मुक्त_mem_cluster(m);
	--mp->nump;
पूर्ण
#अन्यथा
#घोषणा ___mp0_मुक्त_mem_cluster शून्य
#पूर्ण_अगर

अटल काष्ठा sym_m_pool mp0 = अणु
	शून्य,
	___mp0_get_mem_cluster,
	___mp0_मुक्त_mem_cluster
पूर्ण;

/*
 *  Methods that मुख्यtains DMAable pools according to user allocations.
 *  New pools are created on the fly when a new pool id is provided.
 *  They are deleted on the fly when they get emptied.
 */
/* Get a memory cluster that matches the DMA स्थिरraपूर्णांकs of a given pool */
अटल व्योम * ___get_dma_mem_cluster(m_pool_p mp)
अणु
	m_vtob_p vbp;
	व्योम *vaddr;

	vbp = __sym_सुस्मृति(&mp0, माप(*vbp), "VTOB");
	अगर (!vbp)
		जाओ out_err;

	vaddr = sym_m_get_dma_mem_cluster(mp, vbp);
	अगर (vaddr) अणु
		पूर्णांक hc = VTOB_HASH_CODE(vaddr);
		vbp->next = mp->vtob[hc];
		mp->vtob[hc] = vbp;
		++mp->nump;
	पूर्ण
	वापस vaddr;
out_err:
	वापस शून्य;
पूर्ण

#अगर_घोषित	SYM_MEM_FREE_UNUSED
/* Free a memory cluster and associated resources क्रम DMA */
अटल व्योम ___मुक्त_dma_mem_cluster(m_pool_p mp, व्योम *m)
अणु
	m_vtob_p *vbpp, vbp;
	पूर्णांक hc = VTOB_HASH_CODE(m);

	vbpp = &mp->vtob[hc];
	जबतक (*vbpp && (*vbpp)->vaddr != m)
		vbpp = &(*vbpp)->next;
	अगर (*vbpp) अणु
		vbp = *vbpp;
		*vbpp = (*vbpp)->next;
		sym_m_मुक्त_dma_mem_cluster(mp, vbp);
		__sym_mमुक्त(&mp0, vbp, माप(*vbp), "VTOB");
		--mp->nump;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* Fetch the memory pool क्रम a given pool id (i.e. DMA स्थिरraपूर्णांकs) */
अटल अंतरभूत m_pool_p ___get_dma_pool(m_pool_ident_t dev_dmat)
अणु
	m_pool_p mp;
	क्रम (mp = mp0.next;
		mp && !sym_m_pool_match(mp->dev_dmat, dev_dmat);
			mp = mp->next);
	वापस mp;
पूर्ण

/* Create a new memory DMAable pool (when fetch failed) */
अटल m_pool_p ___cre_dma_pool(m_pool_ident_t dev_dmat)
अणु
	m_pool_p mp = __sym_सुस्मृति(&mp0, माप(*mp), "MPOOL");
	अगर (mp) अणु
		mp->dev_dmat = dev_dmat;
		mp->get_mem_cluster = ___get_dma_mem_cluster;
#अगर_घोषित	SYM_MEM_FREE_UNUSED
		mp->मुक्त_mem_cluster = ___मुक्त_dma_mem_cluster;
#पूर्ण_अगर
		mp->next = mp0.next;
		mp0.next = mp;
		वापस mp;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित	SYM_MEM_FREE_UNUSED
/* Destroy a DMAable memory pool (when got emptied) */
अटल व्योम ___del_dma_pool(m_pool_p p)
अणु
	m_pool_p *pp = &mp0.next;

	जबतक (*pp && *pp != p)
		pp = &(*pp)->next;
	अगर (*pp) अणु
		*pp = (*pp)->next;
		__sym_mमुक्त(&mp0, p, माप(*p), "MPOOL");
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* This lock protects only the memory allocation/मुक्त.  */
अटल DEFINE_SPINLOCK(sym53c8xx_lock);

/*
 *  Actual allocator क्रम DMAable memory.
 */
व्योम *__sym_सुस्मृति_dma(m_pool_ident_t dev_dmat, पूर्णांक size, अक्षर *name)
अणु
	अचिन्हित दीर्घ flags;
	m_pool_p mp;
	व्योम *m = शून्य;

	spin_lock_irqsave(&sym53c8xx_lock, flags);
	mp = ___get_dma_pool(dev_dmat);
	अगर (!mp)
		mp = ___cre_dma_pool(dev_dmat);
	अगर (!mp)
		जाओ out;
	m = __sym_सुस्मृति(mp, size, name);
#अगर_घोषित	SYM_MEM_FREE_UNUSED
	अगर (!mp->nump)
		___del_dma_pool(mp);
#पूर्ण_अगर

 out:
	spin_unlock_irqrestore(&sym53c8xx_lock, flags);
	वापस m;
पूर्ण

व्योम __sym_mमुक्त_dma(m_pool_ident_t dev_dmat, व्योम *m, पूर्णांक size, अक्षर *name)
अणु
	अचिन्हित दीर्घ flags;
	m_pool_p mp;

	spin_lock_irqsave(&sym53c8xx_lock, flags);
	mp = ___get_dma_pool(dev_dmat);
	अगर (!mp)
		जाओ out;
	__sym_mमुक्त(mp, m, size, name);
#अगर_घोषित	SYM_MEM_FREE_UNUSED
	अगर (!mp->nump)
		___del_dma_pool(mp);
#पूर्ण_अगर
 out:
	spin_unlock_irqrestore(&sym53c8xx_lock, flags);
पूर्ण

/*
 *  Actual भव to bus physical address translator 
 *  क्रम 32 bit addressable DMAable memory.
 */
dma_addr_t __vtobus(m_pool_ident_t dev_dmat, व्योम *m)
अणु
	अचिन्हित दीर्घ flags;
	m_pool_p mp;
	पूर्णांक hc = VTOB_HASH_CODE(m);
	m_vtob_p vp = शून्य;
	व्योम *a = (व्योम *)((अचिन्हित दीर्घ)m & ~SYM_MEM_CLUSTER_MASK);
	dma_addr_t b;

	spin_lock_irqsave(&sym53c8xx_lock, flags);
	mp = ___get_dma_pool(dev_dmat);
	अगर (mp) अणु
		vp = mp->vtob[hc];
		जबतक (vp && vp->vaddr != a)
			vp = vp->next;
	पूर्ण
	अगर (!vp)
		panic("sym: VTOBUS FAILED!\n");
	b = vp->baddr + (m - a);
	spin_unlock_irqrestore(&sym53c8xx_lock, flags);
	वापस b;
पूर्ण
