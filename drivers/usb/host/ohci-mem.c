<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 *
 * This file is licenced under the GPL.
 */

/*-------------------------------------------------------------------------*/

/*
 * OHCI deals with three types of memory:
 *	- data used only by the HCD ... kदो_स्मृति is fine
 *	- async and periodic schedules, shared by HC and HCD ... these
 *	  need to use dma_pool or dma_alloc_coherent
 *	- driver buffers, पढ़ो/written by HC ... the hcd glue or the
 *	  device driver provides us with dma addresses
 *
 * There's also "register" data, which is memory mapped.
 * No memory seen by this driver (or any HCD) may be paged out.
 */

/*-------------------------------------------------------------------------*/

अटल व्योम ohci_hcd_init (काष्ठा ohci_hcd *ohci)
अणु
	ohci->next_statechange = jअगरfies;
	spin_lock_init (&ohci->lock);
	INIT_LIST_HEAD (&ohci->pending);
	INIT_LIST_HEAD(&ohci->eds_in_use);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ohci_mem_init (काष्ठा ohci_hcd *ohci)
अणु
	/*
	 * HCs with local memory allocate from localmem_pool so there's
	 * no need to create the below dma pools.
	 */
	अगर (ohci_to_hcd(ohci)->localmem_pool)
		वापस 0;

	ohci->td_cache = dma_pool_create ("ohci_td",
		ohci_to_hcd(ohci)->self.controller,
		माप (काष्ठा td),
		32 /* byte alignment */,
		0 /* no page-crossing issues */);
	अगर (!ohci->td_cache)
		वापस -ENOMEM;
	ohci->ed_cache = dma_pool_create ("ohci_ed",
		ohci_to_hcd(ohci)->self.controller,
		माप (काष्ठा ed),
		16 /* byte alignment */,
		0 /* no page-crossing issues */);
	अगर (!ohci->ed_cache) अणु
		dma_pool_destroy (ohci->td_cache);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ohci_mem_cleanup (काष्ठा ohci_hcd *ohci)
अणु
	dma_pool_destroy(ohci->td_cache);
	ohci->td_cache = शून्य;
	dma_pool_destroy(ohci->ed_cache);
	ohci->ed_cache = शून्य;
पूर्ण

/*-------------------------------------------------------------------------*/

/* ohci "done list" processing needs this mapping */
अटल अंतरभूत काष्ठा td *
dma_to_td (काष्ठा ohci_hcd *hc, dma_addr_t td_dma)
अणु
	काष्ठा td *td;

	td_dma &= TD_MASK;
	td = hc->td_hash [TD_HASH_FUNC(td_dma)];
	जबतक (td && td->td_dma != td_dma)
		td = td->td_hash;
	वापस td;
पूर्ण

/* TDs ... */
अटल काष्ठा td *
td_alloc (काष्ठा ohci_hcd *hc, gfp_t mem_flags)
अणु
	dma_addr_t	dma;
	काष्ठा td	*td;
	काष्ठा usb_hcd	*hcd = ohci_to_hcd(hc);

	अगर (hcd->localmem_pool)
		td = gen_pool_dma_zalloc_align(hcd->localmem_pool,
				माप(*td), &dma, 32);
	अन्यथा
		td = dma_pool_zalloc(hc->td_cache, mem_flags, &dma);
	अगर (td) अणु
		/* in हाल hc fetches it, make it look dead */
		td->hwNextTD = cpu_to_hc32 (hc, dma);
		td->td_dma = dma;
		/* hashed in td_fill */
	पूर्ण
	वापस td;
पूर्ण

अटल व्योम
td_मुक्त (काष्ठा ohci_hcd *hc, काष्ठा td *td)
अणु
	काष्ठा td	**prev = &hc->td_hash [TD_HASH_FUNC (td->td_dma)];
	काष्ठा usb_hcd	*hcd = ohci_to_hcd(hc);

	जबतक (*prev && *prev != td)
		prev = &(*prev)->td_hash;
	अगर (*prev)
		*prev = td->td_hash;
	अन्यथा अगर ((td->hwINFO & cpu_to_hc32(hc, TD_DONE)) != 0)
		ohci_dbg (hc, "no hash for td %p\n", td);

	अगर (hcd->localmem_pool)
		gen_pool_मुक्त(hcd->localmem_pool, (अचिन्हित दीर्घ)td,
			      माप(*td));
	अन्यथा
		dma_pool_मुक्त(hc->td_cache, td, td->td_dma);
पूर्ण

/*-------------------------------------------------------------------------*/

/* EDs ... */
अटल काष्ठा ed *
ed_alloc (काष्ठा ohci_hcd *hc, gfp_t mem_flags)
अणु
	dma_addr_t	dma;
	काष्ठा ed	*ed;
	काष्ठा usb_hcd	*hcd = ohci_to_hcd(hc);

	अगर (hcd->localmem_pool)
		ed = gen_pool_dma_zalloc_align(hcd->localmem_pool,
				माप(*ed), &dma, 16);
	अन्यथा
		ed = dma_pool_zalloc(hc->ed_cache, mem_flags, &dma);
	अगर (ed) अणु
		INIT_LIST_HEAD (&ed->td_list);
		ed->dma = dma;
	पूर्ण
	वापस ed;
पूर्ण

अटल व्योम
ed_मुक्त (काष्ठा ohci_hcd *hc, काष्ठा ed *ed)
अणु
	काष्ठा usb_hcd	*hcd = ohci_to_hcd(hc);

	अगर (hcd->localmem_pool)
		gen_pool_मुक्त(hcd->localmem_pool, (अचिन्हित दीर्घ)ed,
			      माप(*ed));
	अन्यथा
		dma_pool_मुक्त(hc->ed_cache, ed, ed->dma);
पूर्ण

