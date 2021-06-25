<शैली गुरु>
/*
 * Simple memory allocator क्रम on-board SRAM
 *
 *
 * Maपूर्णांकainer : Sylvain Munaut <tnt@246tNt.com>
 *
 * Copyright (C) 2005 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu.h>

#समावेश <linux/fsl/bestcomm/sram.h>


/* Struct keeping our 'state' */
काष्ठा bcom_sram *bcom_sram = शून्य;
EXPORT_SYMBOL_GPL(bcom_sram);	/* needed क्रम अंतरभूत functions */


/* ======================================================================== */
/* Public API                                                               */
/* ======================================================================== */
/* DO NOT USE in पूर्णांकerrupts, अगर needed in irq handler, we should use the
   _irqsave version of the spin_locks */

पूर्णांक bcom_sram_init(काष्ठा device_node *sram_node, अक्षर *owner)
अणु
	पूर्णांक rv;
	स्थिर u32 *regaddr_p;
	u64 regaddr64, size64;
	अचिन्हित पूर्णांक psize;

	/* Create our state काष्ठा */
	अगर (bcom_sram) अणु
		prपूर्णांकk(KERN_ERR "%s: bcom_sram_init: "
			"Already initialized !\n", owner);
		वापस -EBUSY;
	पूर्ण

	bcom_sram = kदो_स्मृति(माप(काष्ठा bcom_sram), GFP_KERNEL);
	अगर (!bcom_sram) अणु
		prपूर्णांकk(KERN_ERR "%s: bcom_sram_init: "
			"Couldn't allocate internal state !\n", owner);
		वापस -ENOMEM;
	पूर्ण

	/* Get address and size of the sram */
	regaddr_p = of_get_address(sram_node, 0, &size64, शून्य);
	अगर (!regaddr_p) अणु
		prपूर्णांकk(KERN_ERR "%s: bcom_sram_init: "
			"Invalid device node !\n", owner);
		rv = -EINVAL;
		जाओ error_मुक्त;
	पूर्ण

	regaddr64 = of_translate_address(sram_node, regaddr_p);

	bcom_sram->base_phys = (phys_addr_t) regaddr64;
	bcom_sram->size = (अचिन्हित पूर्णांक) size64;

	/* Request region */
	अगर (!request_mem_region(bcom_sram->base_phys, bcom_sram->size, owner)) अणु
		prपूर्णांकk(KERN_ERR "%s: bcom_sram_init: "
			"Couldn't request region !\n", owner);
		rv = -EBUSY;
		जाओ error_मुक्त;
	पूर्ण

	/* Map SRAM */
		/* sram is not really __iomem */
	bcom_sram->base_virt = (व्योम*) ioremap(bcom_sram->base_phys, bcom_sram->size);

	अगर (!bcom_sram->base_virt) अणु
		prपूर्णांकk(KERN_ERR "%s: bcom_sram_init: "
			"Map error SRAM zone 0x%08lx (0x%0x)!\n",
			owner, (दीर्घ)bcom_sram->base_phys, bcom_sram->size );
		rv = -ENOMEM;
		जाओ error_release;
	पूर्ण

	/* Create an rheap (शेषs to 32 bits word alignment) */
	bcom_sram->rh = rh_create(4);

	/* Attach the मुक्त zones */
#अगर 0
	/* Currently disabled ... क्रम future use only */
	reg_addr_p = of_get_property(sram_node, "available", &psize);
#अन्यथा
	regaddr_p = शून्य;
	psize = 0;
#पूर्ण_अगर

	अगर (!regaddr_p || !psize) अणु
		/* Attach the whole zone */
		rh_attach_region(bcom_sram->rh, 0, bcom_sram->size);
	पूर्ण अन्यथा अणु
		/* Attach each zone independently */
		जबतक (psize >= 2 * माप(u32)) अणु
			phys_addr_t zbase = of_translate_address(sram_node, regaddr_p);
			rh_attach_region(bcom_sram->rh, zbase - bcom_sram->base_phys, regaddr_p[1]);
			regaddr_p += 2;
			psize -= 2 * माप(u32);
		पूर्ण
	पूर्ण

	/* Init our spinlock */
	spin_lock_init(&bcom_sram->lock);

	वापस 0;

error_release:
	release_mem_region(bcom_sram->base_phys, bcom_sram->size);
error_मुक्त:
	kमुक्त(bcom_sram);
	bcom_sram = शून्य;

	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_sram_init);

व्योम bcom_sram_cleanup(व्योम)
अणु
	/* Free resources */
	अगर (bcom_sram) अणु
		rh_destroy(bcom_sram->rh);
		iounmap((व्योम __iomem *)bcom_sram->base_virt);
		release_mem_region(bcom_sram->base_phys, bcom_sram->size);
		kमुक्त(bcom_sram);
		bcom_sram = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bcom_sram_cleanup);

व्योम* bcom_sram_alloc(पूर्णांक size, पूर्णांक align, phys_addr_t *phys)
अणु
	अचिन्हित दीर्घ offset;

	spin_lock(&bcom_sram->lock);
	offset = rh_alloc_align(bcom_sram->rh, size, align, शून्य);
	spin_unlock(&bcom_sram->lock);

	अगर (IS_ERR_VALUE(offset))
		वापस शून्य;

	*phys = bcom_sram->base_phys + offset;
	वापस bcom_sram->base_virt + offset;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_sram_alloc);

व्योम bcom_sram_मुक्त(व्योम *ptr)
अणु
	अचिन्हित दीर्घ offset;

	अगर (!ptr)
		वापस;

	offset = ptr - bcom_sram->base_virt;

	spin_lock(&bcom_sram->lock);
	rh_मुक्त(bcom_sram->rh, offset);
	spin_unlock(&bcom_sram->lock);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_sram_मुक्त);

