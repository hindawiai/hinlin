<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4/sq.c
 *
 * General management API क्रम SH-4 पूर्णांकegrated Store Queues
 *
 * Copyright (C) 2001 - 2006  Paul Mundt
 * Copyright (C) 2001, 2002  M. R. Brown
 */
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <cpu/sq.h>

काष्ठा sq_mapping;

काष्ठा sq_mapping अणु
	स्थिर अक्षर *name;

	अचिन्हित दीर्घ sq_addr;
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक size;

	काष्ठा sq_mapping *next;
पूर्ण;

अटल काष्ठा sq_mapping *sq_mapping_list;
अटल DEFINE_SPINLOCK(sq_mapping_lock);
अटल काष्ठा kmem_cache *sq_cache;
अटल अचिन्हित दीर्घ *sq_biपंचांगap;

#घोषणा store_queue_barrier()			\
करो अणु						\
	(व्योम)__raw_पढ़ोl(P4SEG_STORE_QUE);	\
	__raw_ग_लिखोl(0, P4SEG_STORE_QUE + 0);	\
	__raw_ग_लिखोl(0, P4SEG_STORE_QUE + 8);	\
पूर्ण जबतक (0);

/**
 * sq_flush_range - Flush (prefetch) a specअगरic SQ range
 * @start: the store queue address to start flushing from
 * @len: the length to flush
 *
 * Flushes the store queue cache from @start to @start + @len in a
 * linear fashion.
 */
व्योम sq_flush_range(अचिन्हित दीर्घ start, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ *sq = (अचिन्हित दीर्घ *)start;

	/* Flush the queues */
	क्रम (len >>= 5; len--; sq += 8)
		prefetchw(sq);

	/* Wait क्रम completion */
	store_queue_barrier();
पूर्ण
EXPORT_SYMBOL(sq_flush_range);

अटल अंतरभूत व्योम sq_mapping_list_add(काष्ठा sq_mapping *map)
अणु
	काष्ठा sq_mapping **p, *पंचांगp;

	spin_lock_irq(&sq_mapping_lock);

	p = &sq_mapping_list;
	जबतक ((पंचांगp = *p) != शून्य)
		p = &पंचांगp->next;

	map->next = पंचांगp;
	*p = map;

	spin_unlock_irq(&sq_mapping_lock);
पूर्ण

अटल अंतरभूत व्योम sq_mapping_list_del(काष्ठा sq_mapping *map)
अणु
	काष्ठा sq_mapping **p, *पंचांगp;

	spin_lock_irq(&sq_mapping_lock);

	क्रम (p = &sq_mapping_list; (पंचांगp = *p); p = &पंचांगp->next)
		अगर (पंचांगp == map) अणु
			*p = पंचांगp->next;
			अवरोध;
		पूर्ण

	spin_unlock_irq(&sq_mapping_lock);
पूर्ण

अटल पूर्णांक __sq_remap(काष्ठा sq_mapping *map, pgprot_t prot)
अणु
#अगर defined(CONFIG_MMU)
	काष्ठा vm_काष्ठा *vma;

	vma = __get_vm_area_caller(map->size, VM_ALLOC, map->sq_addr,
			SQ_ADDRMAX, __builtin_वापस_address(0));
	अगर (!vma)
		वापस -ENOMEM;

	vma->phys_addr = map->addr;

	अगर (ioremap_page_range((अचिन्हित दीर्घ)vma->addr,
			       (अचिन्हित दीर्घ)vma->addr + map->size,
			       vma->phys_addr, prot)) अणु
		vunmap(vma->addr);
		वापस -EAGAIN;
	पूर्ण
#अन्यथा
	/*
	 * Without an MMU (or with it turned off), this is much more
	 * straightक्रमward, as we can just load up each queue's QACR with
	 * the physical address appropriately masked.
	 */
	__raw_ग_लिखोl(((map->addr >> 26) << 2) & 0x1c, SQ_QACR0);
	__raw_ग_लिखोl(((map->addr >> 26) << 2) & 0x1c, SQ_QACR1);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * sq_remap - Map a physical address through the Store Queues
 * @phys: Physical address of mapping.
 * @size: Length of mapping.
 * @name: User invoking mapping.
 * @prot: Protection bits.
 *
 * Remaps the physical address @phys through the next available store queue
 * address of @size length. @name is logged at boot समय as well as through
 * the sysfs पूर्णांकerface.
 */
अचिन्हित दीर्घ sq_remap(अचिन्हित दीर्घ phys, अचिन्हित पूर्णांक size,
		       स्थिर अक्षर *name, pgprot_t prot)
अणु
	काष्ठा sq_mapping *map;
	अचिन्हित दीर्घ end;
	अचिन्हित पूर्णांक psz;
	पूर्णांक ret, page;

	/* Don't allow wraparound or zero size */
	end = phys + size - 1;
	अगर (unlikely(!size || end < phys))
		वापस -EINVAL;
	/* Don't allow anyone to remap normal memory.. */
	अगर (unlikely(phys < virt_to_phys(high_memory)))
		वापस -EINVAL;

	phys &= PAGE_MASK;
	size = PAGE_ALIGN(end + 1) - phys;

	map = kmem_cache_alloc(sq_cache, GFP_KERNEL);
	अगर (unlikely(!map))
		वापस -ENOMEM;

	map->addr = phys;
	map->size = size;
	map->name = name;

	page = biपंचांगap_find_मुक्त_region(sq_biपंचांगap, 0x04000000 >> PAGE_SHIFT,
				       get_order(map->size));
	अगर (unlikely(page < 0)) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	map->sq_addr = P4SEG_STORE_QUE + (page << PAGE_SHIFT);

	ret = __sq_remap(map, prot);
	अगर (unlikely(ret != 0))
		जाओ out;

	psz = (size + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	pr_info("sqremap: %15s  [%4d page%s]  va 0x%08lx   pa 0x%08lx\n",
		likely(map->name) ? map->name : "???",
		psz, psz == 1 ? " " : "s",
		map->sq_addr, map->addr);

	sq_mapping_list_add(map);

	वापस map->sq_addr;

out:
	kmem_cache_मुक्त(sq_cache, map);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sq_remap);

/**
 * sq_unmap - Unmap a Store Queue allocation
 * @vaddr: Pre-allocated Store Queue mapping.
 *
 * Unmaps the store queue allocation @map that was previously created by
 * sq_remap(). Also मुक्तs up the pte that was previously inserted पूर्णांकo
 * the kernel page table and discards the UTLB translation.
 */
व्योम sq_unmap(अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा sq_mapping **p, *map;
	पूर्णांक page;

	क्रम (p = &sq_mapping_list; (map = *p); p = &map->next)
		अगर (map->sq_addr == vaddr)
			अवरोध;

	अगर (unlikely(!map)) अणु
		prपूर्णांकk("%s: bad store queue address 0x%08lx\n",
		       __func__, vaddr);
		वापस;
	पूर्ण

	page = (map->sq_addr - P4SEG_STORE_QUE) >> PAGE_SHIFT;
	biपंचांगap_release_region(sq_biपंचांगap, page, get_order(map->size));

#अगर_घोषित CONFIG_MMU
	अणु
		/*
		 * Tear करोwn the VMA in the MMU हाल.
		 */
		काष्ठा vm_काष्ठा *vma;

		vma = हटाओ_vm_area((व्योम *)(map->sq_addr & PAGE_MASK));
		अगर (!vma) अणु
			prपूर्णांकk(KERN_ERR "%s: bad address 0x%08lx\n",
			       __func__, map->sq_addr);
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	sq_mapping_list_del(map);

	kmem_cache_मुक्त(sq_cache, map);
पूर्ण
EXPORT_SYMBOL(sq_unmap);

/*
 * Needlessly complex sysfs पूर्णांकerface. Unक्रमtunately it करोesn't seem like
 * there is any other easy way to add things on a per-cpu basis without
 * putting the directory entries somewhere stupid and having to create
 * links in sysfs by hand back in to the per-cpu directories.
 *
 * Some day we may want to have an additional असलtraction per store
 * queue, but considering the kobject hell we alपढ़ोy have to deal with,
 * it's simply not worth the trouble.
 */
अटल काष्ठा kobject *sq_kobject[NR_CPUS];

काष्ठा sq_sysfs_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(अक्षर *buf);
	sमाप_प्रकार (*store)(स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

#घोषणा to_sq_sysfs_attr(a)	container_of(a, काष्ठा sq_sysfs_attr, attr)

अटल sमाप_प्रकार sq_sysfs_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा sq_sysfs_attr *sattr = to_sq_sysfs_attr(attr);

	अगर (likely(sattr->show))
		वापस sattr->show(buf);

	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार sq_sysfs_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sq_sysfs_attr *sattr = to_sq_sysfs_attr(attr);

	अगर (likely(sattr->store))
		वापस sattr->store(buf, count);

	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार mapping_show(अक्षर *buf)
अणु
	काष्ठा sq_mapping **list, *entry;
	अक्षर *p = buf;

	क्रम (list = &sq_mapping_list; (entry = *list); list = &entry->next)
		p += प्र_लिखो(p, "%08lx-%08lx [%08lx]: %s\n",
			     entry->sq_addr, entry->sq_addr + entry->size,
			     entry->addr, entry->name);

	वापस p - buf;
पूर्ण

अटल sमाप_प्रकार mapping_store(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ base = 0, len = 0;

	माला_पूछो(buf, "%lx %lx", &base, &len);
	अगर (!base)
		वापस -EIO;

	अगर (likely(len)) अणु
		पूर्णांक ret = sq_remap(base, len, "Userspace", PAGE_SHARED);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा
		sq_unmap(base);

	वापस count;
पूर्ण

अटल काष्ठा sq_sysfs_attr mapping_attr =
	__ATTR(mapping, 0644, mapping_show, mapping_store);

अटल काष्ठा attribute *sq_sysfs_attrs[] = अणु
	&mapping_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops sq_sysfs_ops = अणु
	.show	= sq_sysfs_show,
	.store	= sq_sysfs_store,
पूर्ण;

अटल काष्ठा kobj_type ktype_percpu_entry = अणु
	.sysfs_ops	= &sq_sysfs_ops,
	.शेष_attrs	= sq_sysfs_attrs,
पूर्ण;

अटल पूर्णांक sq_dev_add(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	अचिन्हित पूर्णांक cpu = dev->id;
	काष्ठा kobject *kobj;
	पूर्णांक error;

	sq_kobject[cpu] = kzalloc(माप(काष्ठा kobject), GFP_KERNEL);
	अगर (unlikely(!sq_kobject[cpu]))
		वापस -ENOMEM;

	kobj = sq_kobject[cpu];
	error = kobject_init_and_add(kobj, &ktype_percpu_entry, &dev->kobj,
				     "%s", "sq");
	अगर (!error)
		kobject_uevent(kobj, KOBJ_ADD);
	वापस error;
पूर्ण

अटल व्योम sq_dev_हटाओ(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	अचिन्हित पूर्णांक cpu = dev->id;
	काष्ठा kobject *kobj = sq_kobject[cpu];

	kobject_put(kobj);
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface sq_पूर्णांकerface = अणु
	.name		= "sq",
	.subsys		= &cpu_subsys,
	.add_dev	= sq_dev_add,
	.हटाओ_dev	= sq_dev_हटाओ,
पूर्ण;

अटल पूर्णांक __init sq_api_init(व्योम)
अणु
	अचिन्हित पूर्णांक nr_pages = 0x04000000 >> PAGE_SHIFT;
	अचिन्हित पूर्णांक size = (nr_pages + (BITS_PER_LONG - 1)) / BITS_PER_LONG;
	पूर्णांक ret = -ENOMEM;

	prपूर्णांकk(KERN_NOTICE "sq: Registering store queue API.\n");

	sq_cache = kmem_cache_create("store_queue_cache",
				माप(काष्ठा sq_mapping), 0, 0, शून्य);
	अगर (unlikely(!sq_cache))
		वापस ret;

	sq_biपंचांगap = kzalloc(size, GFP_KERNEL);
	अगर (unlikely(!sq_biपंचांगap))
		जाओ out;

	ret = subsys_पूर्णांकerface_रेजिस्टर(&sq_पूर्णांकerface);
	अगर (unlikely(ret != 0))
		जाओ out;

	वापस 0;

out:
	kमुक्त(sq_biपंचांगap);
	kmem_cache_destroy(sq_cache);

	वापस ret;
पूर्ण

अटल व्योम __निकास sq_api_निकास(व्योम)
अणु
	subsys_पूर्णांकerface_unरेजिस्टर(&sq_पूर्णांकerface);
	kमुक्त(sq_biपंचांगap);
	kmem_cache_destroy(sq_cache);
पूर्ण

module_init(sq_api_init);
module_निकास(sq_api_निकास);

MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>, M. R. Brown <mrbrown@0xd6.org>");
MODULE_DESCRIPTION("Simple API for SH-4 integrated Store Queues");
MODULE_LICENSE("GPL");
