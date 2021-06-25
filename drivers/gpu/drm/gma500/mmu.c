<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2007, Intel Corporation.
 *
 **************************************************************************/

#समावेश <linux/highस्मृति.स>

#समावेश "mmu.h"
#समावेश "psb_drv.h"
#समावेश "psb_reg.h"

/*
 * Code क्रम the SGX MMU:
 */

/*
 * clflush on one processor only:
 * clflush should apparently flush the cache line on all processors in an
 * SMP प्रणाली.
 */

/*
 * kmap atomic:
 * The usage of the slots must be completely encapsulated within a spinlock, and
 * no other functions that may be using the locks क्रम other purposed may be
 * called from within the locked region.
 * Since the slots are per processor, this will guarantee that we are the only
 * user.
 */

/*
 * TODO: Inserting ptes from an पूर्णांकerrupt handler:
 * This may be desirable क्रम some SGX functionality where the GPU can fault in
 * needed pages. For that, we need to make an atomic insert_pages function, that
 * may fail.
 * If it fails, the caller need to insert the page using a workqueue function,
 * but on average it should be fast.
 */

अटल अंतरभूत uपूर्णांक32_t psb_mmu_pt_index(uपूर्णांक32_t offset)
अणु
	वापस (offset >> PSB_PTE_SHIFT) & 0x3FF;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t psb_mmu_pd_index(uपूर्णांक32_t offset)
अणु
	वापस offset >> PSB_PDE_SHIFT;
पूर्ण

अटल अंतरभूत व्योम psb_clflush(व्योम *addr)
अणु
	__यंत्र__ __अस्थिर__("clflush (%0)\n" : : "r"(addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम psb_mmu_clflush(काष्ठा psb_mmu_driver *driver, व्योम *addr)
अणु
	अगर (!driver->has_clflush)
		वापस;

	mb();
	psb_clflush(addr);
	mb();
पूर्ण

अटल व्योम psb_mmu_flush_pd_locked(काष्ठा psb_mmu_driver *driver, पूर्णांक क्रमce)
अणु
	काष्ठा drm_device *dev = driver->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	अगर (atomic_पढ़ो(&driver->needs_tlbflush) || क्रमce) अणु
		uपूर्णांक32_t val = PSB_RSGX32(PSB_CR_BIF_CTRL);
		PSB_WSGX32(val | _PSB_CB_CTRL_INVALDC, PSB_CR_BIF_CTRL);

		/* Make sure data cache is turned off beक्रमe enabling it */
		wmb();
		PSB_WSGX32(val & ~_PSB_CB_CTRL_INVALDC, PSB_CR_BIF_CTRL);
		(व्योम)PSB_RSGX32(PSB_CR_BIF_CTRL);
		अगर (driver->msvdx_mmu_invaldc)
			atomic_set(driver->msvdx_mmu_invaldc, 1);
	पूर्ण
	atomic_set(&driver->needs_tlbflush, 0);
पूर्ण

#अगर 0
अटल व्योम psb_mmu_flush_pd(काष्ठा psb_mmu_driver *driver, पूर्णांक क्रमce)
अणु
	करोwn_ग_लिखो(&driver->sem);
	psb_mmu_flush_pd_locked(driver, क्रमce);
	up_ग_लिखो(&driver->sem);
पूर्ण
#पूर्ण_अगर

व्योम psb_mmu_flush(काष्ठा psb_mmu_driver *driver)
अणु
	काष्ठा drm_device *dev = driver->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	uपूर्णांक32_t val;

	करोwn_ग_लिखो(&driver->sem);
	val = PSB_RSGX32(PSB_CR_BIF_CTRL);
	अगर (atomic_पढ़ो(&driver->needs_tlbflush))
		PSB_WSGX32(val | _PSB_CB_CTRL_INVALDC, PSB_CR_BIF_CTRL);
	अन्यथा
		PSB_WSGX32(val | _PSB_CB_CTRL_FLUSH, PSB_CR_BIF_CTRL);

	/* Make sure data cache is turned off and MMU is flushed beक्रमe
	   restoring bank पूर्णांकerface control रेजिस्टर */
	wmb();
	PSB_WSGX32(val & ~(_PSB_CB_CTRL_FLUSH | _PSB_CB_CTRL_INVALDC),
		   PSB_CR_BIF_CTRL);
	(व्योम)PSB_RSGX32(PSB_CR_BIF_CTRL);

	atomic_set(&driver->needs_tlbflush, 0);
	अगर (driver->msvdx_mmu_invaldc)
		atomic_set(driver->msvdx_mmu_invaldc, 1);
	up_ग_लिखो(&driver->sem);
पूर्ण

व्योम psb_mmu_set_pd_context(काष्ठा psb_mmu_pd *pd, पूर्णांक hw_context)
अणु
	काष्ठा drm_device *dev = pd->driver->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	uपूर्णांक32_t offset = (hw_context == 0) ? PSB_CR_BIF_सूची_LIST_BASE0 :
			  PSB_CR_BIF_सूची_LIST_BASE1 + hw_context * 4;

	करोwn_ग_लिखो(&pd->driver->sem);
	PSB_WSGX32(page_to_pfn(pd->p) << PAGE_SHIFT, offset);
	wmb();
	psb_mmu_flush_pd_locked(pd->driver, 1);
	pd->hw_context = hw_context;
	up_ग_लिखो(&pd->driver->sem);

पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ psb_pd_addr_end(अचिन्हित दीर्घ addr,
					    अचिन्हित दीर्घ end)
अणु
	addr = (addr + PSB_PDE_MASK + 1) & ~PSB_PDE_MASK;
	वापस (addr < end) ? addr : end;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t psb_mmu_mask_pte(uपूर्णांक32_t pfn, पूर्णांक type)
अणु
	uपूर्णांक32_t mask = PSB_PTE_VALID;

	अगर (type & PSB_MMU_CACHED_MEMORY)
		mask |= PSB_PTE_CACHED;
	अगर (type & PSB_MMU_RO_MEMORY)
		mask |= PSB_PTE_RO;
	अगर (type & PSB_MMU_WO_MEMORY)
		mask |= PSB_PTE_WO;

	वापस (pfn << PAGE_SHIFT) | mask;
पूर्ण

काष्ठा psb_mmu_pd *psb_mmu_alloc_pd(काष्ठा psb_mmu_driver *driver,
				    पूर्णांक trap_pagefaults, पूर्णांक invalid_type)
अणु
	काष्ठा psb_mmu_pd *pd = kदो_स्मृति(माप(*pd), GFP_KERNEL);
	uपूर्णांक32_t *v;
	पूर्णांक i;

	अगर (!pd)
		वापस शून्य;

	pd->p = alloc_page(GFP_DMA32);
	अगर (!pd->p)
		जाओ out_err1;
	pd->dummy_pt = alloc_page(GFP_DMA32);
	अगर (!pd->dummy_pt)
		जाओ out_err2;
	pd->dummy_page = alloc_page(GFP_DMA32);
	अगर (!pd->dummy_page)
		जाओ out_err3;

	अगर (!trap_pagefaults) अणु
		pd->invalid_pde = psb_mmu_mask_pte(page_to_pfn(pd->dummy_pt),
						   invalid_type);
		pd->invalid_pte = psb_mmu_mask_pte(page_to_pfn(pd->dummy_page),
						   invalid_type);
	पूर्ण अन्यथा अणु
		pd->invalid_pde = 0;
		pd->invalid_pte = 0;
	पूर्ण

	v = kmap(pd->dummy_pt);
	क्रम (i = 0; i < (PAGE_SIZE / माप(uपूर्णांक32_t)); ++i)
		v[i] = pd->invalid_pte;

	kunmap(pd->dummy_pt);

	v = kmap(pd->p);
	क्रम (i = 0; i < (PAGE_SIZE / माप(uपूर्णांक32_t)); ++i)
		v[i] = pd->invalid_pde;

	kunmap(pd->p);

	clear_page(kmap(pd->dummy_page));
	kunmap(pd->dummy_page);

	pd->tables = vदो_स्मृति_user(माप(काष्ठा psb_mmu_pt *) * 1024);
	अगर (!pd->tables)
		जाओ out_err4;

	pd->hw_context = -1;
	pd->pd_mask = PSB_PTE_VALID;
	pd->driver = driver;

	वापस pd;

out_err4:
	__मुक्त_page(pd->dummy_page);
out_err3:
	__मुक्त_page(pd->dummy_pt);
out_err2:
	__मुक्त_page(pd->p);
out_err1:
	kमुक्त(pd);
	वापस शून्य;
पूर्ण

अटल व्योम psb_mmu_मुक्त_pt(काष्ठा psb_mmu_pt *pt)
अणु
	__मुक्त_page(pt->p);
	kमुक्त(pt);
पूर्ण

व्योम psb_mmu_मुक्त_pagedir(काष्ठा psb_mmu_pd *pd)
अणु
	काष्ठा psb_mmu_driver *driver = pd->driver;
	काष्ठा drm_device *dev = driver->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_mmu_pt *pt;
	पूर्णांक i;

	करोwn_ग_लिखो(&driver->sem);
	अगर (pd->hw_context != -1) अणु
		PSB_WSGX32(0, PSB_CR_BIF_सूची_LIST_BASE0 + pd->hw_context * 4);
		psb_mmu_flush_pd_locked(driver, 1);
	पूर्ण

	/* Should take the spinlock here, but we करोn't need to करो that
	   since we have the semaphore in ग_लिखो mode. */

	क्रम (i = 0; i < 1024; ++i) अणु
		pt = pd->tables[i];
		अगर (pt)
			psb_mmu_मुक्त_pt(pt);
	पूर्ण

	vमुक्त(pd->tables);
	__मुक्त_page(pd->dummy_page);
	__मुक्त_page(pd->dummy_pt);
	__मुक्त_page(pd->p);
	kमुक्त(pd);
	up_ग_लिखो(&driver->sem);
पूर्ण

अटल काष्ठा psb_mmu_pt *psb_mmu_alloc_pt(काष्ठा psb_mmu_pd *pd)
अणु
	काष्ठा psb_mmu_pt *pt = kदो_स्मृति(माप(*pt), GFP_KERNEL);
	व्योम *v;
	uपूर्णांक32_t clflush_add = pd->driver->clflush_add >> PAGE_SHIFT;
	uपूर्णांक32_t clflush_count = PAGE_SIZE / clflush_add;
	spinlock_t *lock = &pd->driver->lock;
	uपूर्णांक8_t *clf;
	uपूर्णांक32_t *ptes;
	पूर्णांक i;

	अगर (!pt)
		वापस शून्य;

	pt->p = alloc_page(GFP_DMA32);
	अगर (!pt->p) अणु
		kमुक्त(pt);
		वापस शून्य;
	पूर्ण

	spin_lock(lock);

	v = kmap_atomic(pt->p);
	clf = (uपूर्णांक8_t *) v;
	ptes = (uपूर्णांक32_t *) v;
	क्रम (i = 0; i < (PAGE_SIZE / माप(uपूर्णांक32_t)); ++i)
		*ptes++ = pd->invalid_pte;

	अगर (pd->driver->has_clflush && pd->hw_context != -1) अणु
		mb();
		क्रम (i = 0; i < clflush_count; ++i) अणु
			psb_clflush(clf);
			clf += clflush_add;
		पूर्ण
		mb();
	पूर्ण
	kunmap_atomic(v);
	spin_unlock(lock);

	pt->count = 0;
	pt->pd = pd;
	pt->index = 0;

	वापस pt;
पूर्ण

अटल काष्ठा psb_mmu_pt *psb_mmu_pt_alloc_map_lock(काष्ठा psb_mmu_pd *pd,
						    अचिन्हित दीर्घ addr)
अणु
	uपूर्णांक32_t index = psb_mmu_pd_index(addr);
	काष्ठा psb_mmu_pt *pt;
	uपूर्णांक32_t *v;
	spinlock_t *lock = &pd->driver->lock;

	spin_lock(lock);
	pt = pd->tables[index];
	जबतक (!pt) अणु
		spin_unlock(lock);
		pt = psb_mmu_alloc_pt(pd);
		अगर (!pt)
			वापस शून्य;
		spin_lock(lock);

		अगर (pd->tables[index]) अणु
			spin_unlock(lock);
			psb_mmu_मुक्त_pt(pt);
			spin_lock(lock);
			pt = pd->tables[index];
			जारी;
		पूर्ण

		v = kmap_atomic(pd->p);
		pd->tables[index] = pt;
		v[index] = (page_to_pfn(pt->p) << 12) | pd->pd_mask;
		pt->index = index;
		kunmap_atomic((व्योम *) v);

		अगर (pd->hw_context != -1) अणु
			psb_mmu_clflush(pd->driver, (व्योम *)&v[index]);
			atomic_set(&pd->driver->needs_tlbflush, 1);
		पूर्ण
	पूर्ण
	pt->v = kmap_atomic(pt->p);
	वापस pt;
पूर्ण

अटल काष्ठा psb_mmu_pt *psb_mmu_pt_map_lock(काष्ठा psb_mmu_pd *pd,
					      अचिन्हित दीर्घ addr)
अणु
	uपूर्णांक32_t index = psb_mmu_pd_index(addr);
	काष्ठा psb_mmu_pt *pt;
	spinlock_t *lock = &pd->driver->lock;

	spin_lock(lock);
	pt = pd->tables[index];
	अगर (!pt) अणु
		spin_unlock(lock);
		वापस शून्य;
	पूर्ण
	pt->v = kmap_atomic(pt->p);
	वापस pt;
पूर्ण

अटल व्योम psb_mmu_pt_unmap_unlock(काष्ठा psb_mmu_pt *pt)
अणु
	काष्ठा psb_mmu_pd *pd = pt->pd;
	uपूर्णांक32_t *v;

	kunmap_atomic(pt->v);
	अगर (pt->count == 0) अणु
		v = kmap_atomic(pd->p);
		v[pt->index] = pd->invalid_pde;
		pd->tables[pt->index] = शून्य;

		अगर (pd->hw_context != -1) अणु
			psb_mmu_clflush(pd->driver, (व्योम *)&v[pt->index]);
			atomic_set(&pd->driver->needs_tlbflush, 1);
		पूर्ण
		kunmap_atomic(v);
		spin_unlock(&pd->driver->lock);
		psb_mmu_मुक्त_pt(pt);
		वापस;
	पूर्ण
	spin_unlock(&pd->driver->lock);
पूर्ण

अटल अंतरभूत व्योम psb_mmu_set_pte(काष्ठा psb_mmu_pt *pt, अचिन्हित दीर्घ addr,
				   uपूर्णांक32_t pte)
अणु
	pt->v[psb_mmu_pt_index(addr)] = pte;
पूर्ण

अटल अंतरभूत व्योम psb_mmu_invalidate_pte(काष्ठा psb_mmu_pt *pt,
					  अचिन्हित दीर्घ addr)
अणु
	pt->v[psb_mmu_pt_index(addr)] = pt->pd->invalid_pte;
पूर्ण

काष्ठा psb_mmu_pd *psb_mmu_get_शेष_pd(काष्ठा psb_mmu_driver *driver)
अणु
	काष्ठा psb_mmu_pd *pd;

	करोwn_पढ़ो(&driver->sem);
	pd = driver->शेष_pd;
	up_पढ़ो(&driver->sem);

	वापस pd;
पूर्ण

व्योम psb_mmu_driver_takeकरोwn(काष्ठा psb_mmu_driver *driver)
अणु
	काष्ठा drm_device *dev = driver->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	PSB_WSGX32(driver->bअगर_ctrl, PSB_CR_BIF_CTRL);
	psb_mmu_मुक्त_pagedir(driver->शेष_pd);
	kमुक्त(driver);
पूर्ण

काष्ठा psb_mmu_driver *psb_mmu_driver_init(काष्ठा drm_device *dev,
					   पूर्णांक trap_pagefaults,
					   पूर्णांक invalid_type,
					   atomic_t *msvdx_mmu_invaldc)
अणु
	काष्ठा psb_mmu_driver *driver;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	driver = kदो_स्मृति(माप(*driver), GFP_KERNEL);

	अगर (!driver)
		वापस शून्य;

	driver->dev = dev;
	driver->शेष_pd = psb_mmu_alloc_pd(driver, trap_pagefaults,
					      invalid_type);
	अगर (!driver->शेष_pd)
		जाओ out_err1;

	spin_lock_init(&driver->lock);
	init_rwsem(&driver->sem);
	करोwn_ग_लिखो(&driver->sem);
	atomic_set(&driver->needs_tlbflush, 1);
	driver->msvdx_mmu_invaldc = msvdx_mmu_invaldc;

	driver->bअगर_ctrl = PSB_RSGX32(PSB_CR_BIF_CTRL);
	PSB_WSGX32(driver->bअगर_ctrl | _PSB_CB_CTRL_CLEAR_FAULT,
		   PSB_CR_BIF_CTRL);
	PSB_WSGX32(driver->bअगर_ctrl & ~_PSB_CB_CTRL_CLEAR_FAULT,
		   PSB_CR_BIF_CTRL);

	driver->has_clflush = 0;

	अगर (boot_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		uपूर्णांक32_t tfms, misc, cap0, cap4, clflush_size;

		/*
		 * clflush size is determined at kernel setup क्रम x86_64 but not
		 * क्रम i386. We have to करो it here.
		 */

		cpuid(0x00000001, &tfms, &misc, &cap0, &cap4);
		clflush_size = ((misc >> 8) & 0xff) * 8;
		driver->has_clflush = 1;
		driver->clflush_add =
		    PAGE_SIZE * clflush_size / माप(uपूर्णांक32_t);
		driver->clflush_mask = driver->clflush_add - 1;
		driver->clflush_mask = ~driver->clflush_mask;
	पूर्ण

	up_ग_लिखो(&driver->sem);
	वापस driver;

out_err1:
	kमुक्त(driver);
	वापस शून्य;
पूर्ण

अटल व्योम psb_mmu_flush_ptes(काष्ठा psb_mmu_pd *pd, अचिन्हित दीर्घ address,
			       uपूर्णांक32_t num_pages, uपूर्णांक32_t desired_tile_stride,
			       uपूर्णांक32_t hw_tile_stride)
अणु
	काष्ठा psb_mmu_pt *pt;
	uपूर्णांक32_t rows = 1;
	uपूर्णांक32_t i;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ add;
	अचिन्हित दीर्घ row_add;
	अचिन्हित दीर्घ clflush_add = pd->driver->clflush_add;
	अचिन्हित दीर्घ clflush_mask = pd->driver->clflush_mask;

	अगर (!pd->driver->has_clflush)
		वापस;

	अगर (hw_tile_stride)
		rows = num_pages / desired_tile_stride;
	अन्यथा
		desired_tile_stride = num_pages;

	add = desired_tile_stride << PAGE_SHIFT;
	row_add = hw_tile_stride << PAGE_SHIFT;
	mb();
	क्रम (i = 0; i < rows; ++i) अणु

		addr = address;
		end = addr + add;

		करो अणु
			next = psb_pd_addr_end(addr, end);
			pt = psb_mmu_pt_map_lock(pd, addr);
			अगर (!pt)
				जारी;
			करो अणु
				psb_clflush(&pt->v[psb_mmu_pt_index(addr)]);
			पूर्ण जबतक (addr += clflush_add,
				 (addr & clflush_mask) < next);

			psb_mmu_pt_unmap_unlock(pt);
		पूर्ण जबतक (addr = next, next != end);
		address += row_add;
	पूर्ण
	mb();
पूर्ण

व्योम psb_mmu_हटाओ_pfn_sequence(काष्ठा psb_mmu_pd *pd,
				 अचिन्हित दीर्घ address, uपूर्णांक32_t num_pages)
अणु
	काष्ठा psb_mmu_pt *pt;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ f_address = address;

	करोwn_पढ़ो(&pd->driver->sem);

	addr = address;
	end = addr + (num_pages << PAGE_SHIFT);

	करो अणु
		next = psb_pd_addr_end(addr, end);
		pt = psb_mmu_pt_alloc_map_lock(pd, addr);
		अगर (!pt)
			जाओ out;
		करो अणु
			psb_mmu_invalidate_pte(pt, addr);
			--pt->count;
		पूर्ण जबतक (addr += PAGE_SIZE, addr < next);
		psb_mmu_pt_unmap_unlock(pt);

	पूर्ण जबतक (addr = next, next != end);

out:
	अगर (pd->hw_context != -1)
		psb_mmu_flush_ptes(pd, f_address, num_pages, 1, 1);

	up_पढ़ो(&pd->driver->sem);

	अगर (pd->hw_context != -1)
		psb_mmu_flush(pd->driver);

	वापस;
पूर्ण

व्योम psb_mmu_हटाओ_pages(काष्ठा psb_mmu_pd *pd, अचिन्हित दीर्घ address,
			  uपूर्णांक32_t num_pages, uपूर्णांक32_t desired_tile_stride,
			  uपूर्णांक32_t hw_tile_stride)
अणु
	काष्ठा psb_mmu_pt *pt;
	uपूर्णांक32_t rows = 1;
	uपूर्णांक32_t i;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ add;
	अचिन्हित दीर्घ row_add;
	अचिन्हित दीर्घ f_address = address;

	अगर (hw_tile_stride)
		rows = num_pages / desired_tile_stride;
	अन्यथा
		desired_tile_stride = num_pages;

	add = desired_tile_stride << PAGE_SHIFT;
	row_add = hw_tile_stride << PAGE_SHIFT;

	करोwn_पढ़ो(&pd->driver->sem);

	/* Make sure we only need to flush this processor's cache */

	क्रम (i = 0; i < rows; ++i) अणु

		addr = address;
		end = addr + add;

		करो अणु
			next = psb_pd_addr_end(addr, end);
			pt = psb_mmu_pt_map_lock(pd, addr);
			अगर (!pt)
				जारी;
			करो अणु
				psb_mmu_invalidate_pte(pt, addr);
				--pt->count;

			पूर्ण जबतक (addr += PAGE_SIZE, addr < next);
			psb_mmu_pt_unmap_unlock(pt);

		पूर्ण जबतक (addr = next, next != end);
		address += row_add;
	पूर्ण
	अगर (pd->hw_context != -1)
		psb_mmu_flush_ptes(pd, f_address, num_pages,
				   desired_tile_stride, hw_tile_stride);

	up_पढ़ो(&pd->driver->sem);

	अगर (pd->hw_context != -1)
		psb_mmu_flush(pd->driver);
पूर्ण

पूर्णांक psb_mmu_insert_pfn_sequence(काष्ठा psb_mmu_pd *pd, uपूर्णांक32_t start_pfn,
				अचिन्हित दीर्घ address, uपूर्णांक32_t num_pages,
				पूर्णांक type)
अणु
	काष्ठा psb_mmu_pt *pt;
	uपूर्णांक32_t pte;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ f_address = address;
	पूर्णांक ret = -ENOMEM;

	करोwn_पढ़ो(&pd->driver->sem);

	addr = address;
	end = addr + (num_pages << PAGE_SHIFT);

	करो अणु
		next = psb_pd_addr_end(addr, end);
		pt = psb_mmu_pt_alloc_map_lock(pd, addr);
		अगर (!pt) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		करो अणु
			pte = psb_mmu_mask_pte(start_pfn++, type);
			psb_mmu_set_pte(pt, addr, pte);
			pt->count++;
		पूर्ण जबतक (addr += PAGE_SIZE, addr < next);
		psb_mmu_pt_unmap_unlock(pt);

	पूर्ण जबतक (addr = next, next != end);
	ret = 0;

out:
	अगर (pd->hw_context != -1)
		psb_mmu_flush_ptes(pd, f_address, num_pages, 1, 1);

	up_पढ़ो(&pd->driver->sem);

	अगर (pd->hw_context != -1)
		psb_mmu_flush(pd->driver);

	वापस ret;
पूर्ण

पूर्णांक psb_mmu_insert_pages(काष्ठा psb_mmu_pd *pd, काष्ठा page **pages,
			 अचिन्हित दीर्घ address, uपूर्णांक32_t num_pages,
			 uपूर्णांक32_t desired_tile_stride, uपूर्णांक32_t hw_tile_stride,
			 पूर्णांक type)
अणु
	काष्ठा psb_mmu_pt *pt;
	uपूर्णांक32_t rows = 1;
	uपूर्णांक32_t i;
	uपूर्णांक32_t pte;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ add;
	अचिन्हित दीर्घ row_add;
	अचिन्हित दीर्घ f_address = address;
	पूर्णांक ret = -ENOMEM;

	अगर (hw_tile_stride) अणु
		अगर (num_pages % desired_tile_stride != 0)
			वापस -EINVAL;
		rows = num_pages / desired_tile_stride;
	पूर्ण अन्यथा अणु
		desired_tile_stride = num_pages;
	पूर्ण

	add = desired_tile_stride << PAGE_SHIFT;
	row_add = hw_tile_stride << PAGE_SHIFT;

	करोwn_पढ़ो(&pd->driver->sem);

	क्रम (i = 0; i < rows; ++i) अणु

		addr = address;
		end = addr + add;

		करो अणु
			next = psb_pd_addr_end(addr, end);
			pt = psb_mmu_pt_alloc_map_lock(pd, addr);
			अगर (!pt)
				जाओ out;
			करो अणु
				pte = psb_mmu_mask_pte(page_to_pfn(*pages++),
						       type);
				psb_mmu_set_pte(pt, addr, pte);
				pt->count++;
			पूर्ण जबतक (addr += PAGE_SIZE, addr < next);
			psb_mmu_pt_unmap_unlock(pt);

		पूर्ण जबतक (addr = next, next != end);

		address += row_add;
	पूर्ण

	ret = 0;
out:
	अगर (pd->hw_context != -1)
		psb_mmu_flush_ptes(pd, f_address, num_pages,
				   desired_tile_stride, hw_tile_stride);

	up_पढ़ो(&pd->driver->sem);

	अगर (pd->hw_context != -1)
		psb_mmu_flush(pd->driver);

	वापस ret;
पूर्ण

पूर्णांक psb_mmu_भव_to_pfn(काष्ठा psb_mmu_pd *pd, uपूर्णांक32_t भव,
			   अचिन्हित दीर्घ *pfn)
अणु
	पूर्णांक ret;
	काष्ठा psb_mmu_pt *pt;
	uपूर्णांक32_t पंचांगp;
	spinlock_t *lock = &pd->driver->lock;

	करोwn_पढ़ो(&pd->driver->sem);
	pt = psb_mmu_pt_map_lock(pd, भव);
	अगर (!pt) अणु
		uपूर्णांक32_t *v;

		spin_lock(lock);
		v = kmap_atomic(pd->p);
		पंचांगp = v[psb_mmu_pd_index(भव)];
		kunmap_atomic(v);
		spin_unlock(lock);

		अगर (पंचांगp != pd->invalid_pde || !(पंचांगp & PSB_PTE_VALID) ||
		    !(pd->invalid_pte & PSB_PTE_VALID)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = 0;
		*pfn = pd->invalid_pte >> PAGE_SHIFT;
		जाओ out;
	पूर्ण
	पंचांगp = pt->v[psb_mmu_pt_index(भव)];
	अगर (!(पंचांगp & PSB_PTE_VALID)) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = 0;
		*pfn = पंचांगp >> PAGE_SHIFT;
	पूर्ण
	psb_mmu_pt_unmap_unlock(pt);
out:
	up_पढ़ो(&pd->driver->sem);
	वापस ret;
पूर्ण
