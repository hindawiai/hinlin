<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2001 by David Brownell
 */

/* this file is part of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * There's basically three types of memory:
 *	- data used only by the HCD ... kदो_स्मृति is fine
 *	- async and periodic schedules, shared by HC and HCD ... these
 *	  need to use dma_pool or dma_alloc_coherent
 *	- driver buffers, पढ़ो/written by HC ... single shot DMA mapped
 *
 * There's also "register" data (e.g. PCI or SOC), which is memory mapped.
 * No memory seen by this driver is pageable.
 */

/*-------------------------------------------------------------------------*/

/* Allocate the key transfer काष्ठाures from the previously allocated pool */

अटल अंतरभूत व्योम ehci_qtd_init(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qtd *qtd,
				  dma_addr_t dma)
अणु
	स_रखो (qtd, 0, माप *qtd);
	qtd->qtd_dma = dma;
	qtd->hw_token = cpu_to_hc32(ehci, QTD_STS_HALT);
	qtd->hw_next = EHCI_LIST_END(ehci);
	qtd->hw_alt_next = EHCI_LIST_END(ehci);
	INIT_LIST_HEAD (&qtd->qtd_list);
पूर्ण

अटल काष्ठा ehci_qtd *ehci_qtd_alloc (काष्ठा ehci_hcd *ehci, gfp_t flags)
अणु
	काष्ठा ehci_qtd		*qtd;
	dma_addr_t		dma;

	qtd = dma_pool_alloc (ehci->qtd_pool, flags, &dma);
	अगर (qtd != शून्य) अणु
		ehci_qtd_init(ehci, qtd, dma);
	पूर्ण
	वापस qtd;
पूर्ण

अटल अंतरभूत व्योम ehci_qtd_मुक्त (काष्ठा ehci_hcd *ehci, काष्ठा ehci_qtd *qtd)
अणु
	dma_pool_मुक्त (ehci->qtd_pool, qtd, qtd->qtd_dma);
पूर्ण


अटल व्योम qh_destroy(काष्ठा ehci_hcd *ehci, काष्ठा ehci_qh *qh)
अणु
	/* clean qtds first, and know this is not linked */
	अगर (!list_empty (&qh->qtd_list) || qh->qh_next.ptr) अणु
		ehci_dbg (ehci, "unused qh not empty!\n");
		BUG ();
	पूर्ण
	अगर (qh->dummy)
		ehci_qtd_मुक्त (ehci, qh->dummy);
	dma_pool_मुक्त(ehci->qh_pool, qh->hw, qh->qh_dma);
	kमुक्त(qh);
पूर्ण

अटल काष्ठा ehci_qh *ehci_qh_alloc (काष्ठा ehci_hcd *ehci, gfp_t flags)
अणु
	काष्ठा ehci_qh		*qh;
	dma_addr_t		dma;

	qh = kzalloc(माप *qh, GFP_ATOMIC);
	अगर (!qh)
		जाओ करोne;
	qh->hw = (काष्ठा ehci_qh_hw *)
		dma_pool_alloc(ehci->qh_pool, flags, &dma);
	अगर (!qh->hw)
		जाओ fail;
	स_रखो(qh->hw, 0, माप *qh->hw);
	qh->qh_dma = dma;
	// INIT_LIST_HEAD (&qh->qh_list);
	INIT_LIST_HEAD (&qh->qtd_list);
	INIT_LIST_HEAD(&qh->unlink_node);

	/* dummy td enables safe urb queuing */
	qh->dummy = ehci_qtd_alloc (ehci, flags);
	अगर (qh->dummy == शून्य) अणु
		ehci_dbg (ehci, "no dummy td\n");
		जाओ fail1;
	पूर्ण
करोne:
	वापस qh;
fail1:
	dma_pool_मुक्त(ehci->qh_pool, qh->hw, qh->qh_dma);
fail:
	kमुक्त(qh);
	वापस शून्य;
पूर्ण

/*-------------------------------------------------------------------------*/

/* The queue heads and transfer descriptors are managed from pools tied
 * to each of the "per device" काष्ठाures.
 * This is the initialisation and cleanup code.
 */

अटल व्योम ehci_mem_cleanup (काष्ठा ehci_hcd *ehci)
अणु
	अगर (ehci->async)
		qh_destroy(ehci, ehci->async);
	ehci->async = शून्य;

	अगर (ehci->dummy)
		qh_destroy(ehci, ehci->dummy);
	ehci->dummy = शून्य;

	/* DMA consistent memory and pools */
	dma_pool_destroy(ehci->qtd_pool);
	ehci->qtd_pool = शून्य;
	dma_pool_destroy(ehci->qh_pool);
	ehci->qh_pool = शून्य;
	dma_pool_destroy(ehci->itd_pool);
	ehci->itd_pool = शून्य;
	dma_pool_destroy(ehci->sitd_pool);
	ehci->sitd_pool = शून्य;

	अगर (ehci->periodic)
		dma_मुक्त_coherent(ehci_to_hcd(ehci)->self.sysdev,
			ehci->periodic_size * माप (u32),
			ehci->periodic, ehci->periodic_dma);
	ehci->periodic = शून्य;

	/* shaकरोw periodic table */
	kमुक्त(ehci->pshaकरोw);
	ehci->pshaकरोw = शून्य;
पूर्ण

/* remember to add cleanup code (above) अगर you add anything here */
अटल पूर्णांक ehci_mem_init (काष्ठा ehci_hcd *ehci, gfp_t flags)
अणु
	पूर्णांक i;

	/* QTDs क्रम control/bulk/पूर्णांकr transfers */
	ehci->qtd_pool = dma_pool_create ("ehci_qtd",
			ehci_to_hcd(ehci)->self.sysdev,
			माप (काष्ठा ehci_qtd),
			32 /* byte alignment (क्रम hw parts) */,
			4096 /* can't cross 4K */);
	अगर (!ehci->qtd_pool) अणु
		जाओ fail;
	पूर्ण

	/* QHs क्रम control/bulk/पूर्णांकr transfers */
	ehci->qh_pool = dma_pool_create ("ehci_qh",
			ehci_to_hcd(ehci)->self.sysdev,
			माप(काष्ठा ehci_qh_hw),
			32 /* byte alignment (क्रम hw parts) */,
			4096 /* can't cross 4K */);
	अगर (!ehci->qh_pool) अणु
		जाओ fail;
	पूर्ण
	ehci->async = ehci_qh_alloc (ehci, flags);
	अगर (!ehci->async) अणु
		जाओ fail;
	पूर्ण

	/* ITD क्रम high speed ISO transfers */
	ehci->itd_pool = dma_pool_create ("ehci_itd",
			ehci_to_hcd(ehci)->self.sysdev,
			माप (काष्ठा ehci_itd),
			32 /* byte alignment (क्रम hw parts) */,
			4096 /* can't cross 4K */);
	अगर (!ehci->itd_pool) अणु
		जाओ fail;
	पूर्ण

	/* SITD क्रम full/low speed split ISO transfers */
	ehci->sitd_pool = dma_pool_create ("ehci_sitd",
			ehci_to_hcd(ehci)->self.sysdev,
			माप (काष्ठा ehci_sitd),
			32 /* byte alignment (क्रम hw parts) */,
			4096 /* can't cross 4K */);
	अगर (!ehci->sitd_pool) अणु
		जाओ fail;
	पूर्ण

	/* Hardware periodic table */
	ehci->periodic = (__le32 *)
		dma_alloc_coherent(ehci_to_hcd(ehci)->self.sysdev,
			ehci->periodic_size * माप(__le32),
			&ehci->periodic_dma, flags);
	अगर (ehci->periodic == शून्य) अणु
		जाओ fail;
	पूर्ण

	अगर (ehci->use_dummy_qh) अणु
		काष्ठा ehci_qh_hw	*hw;
		ehci->dummy = ehci_qh_alloc(ehci, flags);
		अगर (!ehci->dummy)
			जाओ fail;

		hw = ehci->dummy->hw;
		hw->hw_next = EHCI_LIST_END(ehci);
		hw->hw_qtd_next = EHCI_LIST_END(ehci);
		hw->hw_alt_next = EHCI_LIST_END(ehci);
		ehci->dummy->hw = hw;

		क्रम (i = 0; i < ehci->periodic_size; i++)
			ehci->periodic[i] = cpu_to_hc32(ehci,
					ehci->dummy->qh_dma);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ehci->periodic_size; i++)
			ehci->periodic[i] = EHCI_LIST_END(ehci);
	पूर्ण

	/* software shaकरोw of hardware table */
	ehci->pshaकरोw = kसुस्मृति(ehci->periodic_size, माप(व्योम *), flags);
	अगर (ehci->pshaकरोw != शून्य)
		वापस 0;

fail:
	ehci_dbg (ehci, "couldn't init memory\n");
	ehci_mem_cleanup (ehci);
	वापस -ENOMEM;
पूर्ण
