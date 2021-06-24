<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DMA memory management क्रम framework level HCD code (hc_driver)
 *
 * This implementation plugs in through generic "usb_bus" level methods,
 * and should work with all USB controllers, regardless of bus type.
 *
 * Released under the GPLv2 only.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>


/*
 * DMA-Coherent Buffers
 */

/* FIXME tune these based on pool statistics ... */
अटल माप_प्रकार pool_max[HCD_BUFFER_POOLS] = अणु
	32, 128, 512, 2048,
पूर्ण;

व्योम __init usb_init_pool_max(व्योम)
अणु
	/*
	 * The pool_max values must never be smaller than
	 * ARCH_KMALLOC_MINALIGN.
	 */
	अगर (ARCH_KMALLOC_MINALIGN <= 32)
		;			/* Original value is okay */
	अन्यथा अगर (ARCH_KMALLOC_MINALIGN <= 64)
		pool_max[0] = 64;
	अन्यथा अगर (ARCH_KMALLOC_MINALIGN <= 128)
		pool_max[0] = 0;	/* Don't use this pool */
	अन्यथा
		BUILD_BUG();		/* We करोn't allow this */
पूर्ण

/* SETUP primitives */

/**
 * hcd_buffer_create - initialize buffer pools
 * @hcd: the bus whose buffer pools are to be initialized
 *
 * Context: task context, might sleep
 *
 * Call this as part of initializing a host controller that uses the dma
 * memory allocators.  It initializes some pools of dma-coherent memory that
 * will be shared by all drivers using that controller.
 *
 * Call hcd_buffer_destroy() to clean up after using those pools.
 *
 * Return: 0 अगर successful. A negative त्रुटि_सं value otherwise.
 */
पूर्णांक hcd_buffer_create(काष्ठा usb_hcd *hcd)
अणु
	अक्षर		name[16];
	पूर्णांक		i, size;

	अगर (hcd->localmem_pool || !hcd_uses_dma(hcd))
		वापस 0;

	क्रम (i = 0; i < HCD_BUFFER_POOLS; i++) अणु
		size = pool_max[i];
		अगर (!size)
			जारी;
		snम_लिखो(name, माप(name), "buffer-%d", size);
		hcd->pool[i] = dma_pool_create(name, hcd->self.sysdev,
				size, size, 0);
		अगर (!hcd->pool[i]) अणु
			hcd_buffer_destroy(hcd);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/**
 * hcd_buffer_destroy - deallocate buffer pools
 * @hcd: the bus whose buffer pools are to be destroyed
 *
 * Context: task context, might sleep
 *
 * This मुक्तs the buffer pools created by hcd_buffer_create().
 */
व्योम hcd_buffer_destroy(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_HAS_DMA))
		वापस;

	क्रम (i = 0; i < HCD_BUFFER_POOLS; i++) अणु
		dma_pool_destroy(hcd->pool[i]);
		hcd->pool[i] = शून्य;
	पूर्ण
पूर्ण


/* someबार alloc/मुक्त could use kदो_स्मृति with GFP_DMA, क्रम
 * better sharing and to leverage mm/slab.c पूर्णांकelligence.
 */

व्योम *hcd_buffer_alloc(
	काष्ठा usb_bus		*bus,
	माप_प्रकार			size,
	gfp_t			mem_flags,
	dma_addr_t		*dma
)
अणु
	काष्ठा usb_hcd		*hcd = bus_to_hcd(bus);
	पूर्णांक			i;

	अगर (size == 0)
		वापस शून्य;

	अगर (hcd->localmem_pool)
		वापस gen_pool_dma_alloc(hcd->localmem_pool, size, dma);

	/* some USB hosts just use PIO */
	अगर (!hcd_uses_dma(hcd)) अणु
		*dma = ~(dma_addr_t) 0;
		वापस kदो_स्मृति(size, mem_flags);
	पूर्ण

	क्रम (i = 0; i < HCD_BUFFER_POOLS; i++) अणु
		अगर (size <= pool_max[i])
			वापस dma_pool_alloc(hcd->pool[i], mem_flags, dma);
	पूर्ण
	वापस dma_alloc_coherent(hcd->self.sysdev, size, dma, mem_flags);
पूर्ण

व्योम hcd_buffer_मुक्त(
	काष्ठा usb_bus		*bus,
	माप_प्रकार			size,
	व्योम			*addr,
	dma_addr_t		dma
)
अणु
	काष्ठा usb_hcd		*hcd = bus_to_hcd(bus);
	पूर्णांक			i;

	अगर (!addr)
		वापस;

	अगर (hcd->localmem_pool) अणु
		gen_pool_मुक्त(hcd->localmem_pool, (अचिन्हित दीर्घ)addr, size);
		वापस;
	पूर्ण

	अगर (!hcd_uses_dma(hcd)) अणु
		kमुक्त(addr);
		वापस;
	पूर्ण

	क्रम (i = 0; i < HCD_BUFFER_POOLS; i++) अणु
		अगर (size <= pool_max[i]) अणु
			dma_pool_मुक्त(hcd->pool[i], addr, dma);
			वापस;
		पूर्ण
	पूर्ण
	dma_मुक्त_coherent(hcd->self.sysdev, size, addr, dma);
पूर्ण
