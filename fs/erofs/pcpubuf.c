<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Gao Xiang <xiang@kernel.org>
 *
 * For low-latency decompression algorithms (e.g. lz4), reserve consecutive
 * per-CPU भव memory (in pages) in advance to store such inplace I/O
 * data अगर inplace decompression is failed (due to unmet inplace margin क्रम
 * example).
 */
#समावेश "internal.h"

काष्ठा erofs_pcpubuf अणु
	raw_spinlock_t lock;
	व्योम *ptr;
	काष्ठा page **pages;
	अचिन्हित पूर्णांक nrpages;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा erofs_pcpubuf, erofs_pcb);

व्योम *erofs_get_pcpubuf(अचिन्हित पूर्णांक requiredpages)
	__acquires(pcb->lock)
अणु
	काष्ठा erofs_pcpubuf *pcb = &get_cpu_var(erofs_pcb);

	raw_spin_lock(&pcb->lock);
	/* check अगर the per-CPU buffer is too small */
	अगर (requiredpages > pcb->nrpages) अणु
		raw_spin_unlock(&pcb->lock);
		put_cpu_var(erofs_pcb);
		/* (क्रम sparse checker) pretend pcb->lock is still taken */
		__acquire(pcb->lock);
		वापस शून्य;
	पूर्ण
	वापस pcb->ptr;
पूर्ण

व्योम erofs_put_pcpubuf(व्योम *ptr) __releases(pcb->lock)
अणु
	काष्ठा erofs_pcpubuf *pcb = &per_cpu(erofs_pcb, smp_processor_id());

	DBG_BUGON(pcb->ptr != ptr);
	raw_spin_unlock(&pcb->lock);
	put_cpu_var(erofs_pcb);
पूर्ण

/* the next step: support per-CPU page buffers hotplug */
पूर्णांक erofs_pcpubuf_growsize(अचिन्हित पूर्णांक nrpages)
अणु
	अटल DEFINE_MUTEX(pcb_resize_mutex);
	अटल अचिन्हित पूर्णांक pcb_nrpages;
	LIST_HEAD(pagepool);
	पूर्णांक delta, cpu, ret, i;

	mutex_lock(&pcb_resize_mutex);
	delta = nrpages - pcb_nrpages;
	ret = 0;
	/* aव्योम shrinking pcpubuf, since no idea how many fses rely on */
	अगर (delta <= 0)
		जाओ out;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा erofs_pcpubuf *pcb = &per_cpu(erofs_pcb, cpu);
		काष्ठा page **pages, **oldpages;
		व्योम *ptr, *old_ptr;

		pages = kदो_स्मृति_array(nrpages, माप(*pages), GFP_KERNEL);
		अगर (!pages) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < nrpages; ++i) अणु
			pages[i] = erofs_allocpage(&pagepool, GFP_KERNEL);
			अगर (!pages[i]) अणु
				ret = -ENOMEM;
				oldpages = pages;
				जाओ मुक्त_pagearray;
			पूर्ण
		पूर्ण
		ptr = vmap(pages, nrpages, VM_MAP, PAGE_KERNEL);
		अगर (!ptr) अणु
			ret = -ENOMEM;
			oldpages = pages;
			जाओ मुक्त_pagearray;
		पूर्ण
		raw_spin_lock(&pcb->lock);
		old_ptr = pcb->ptr;
		pcb->ptr = ptr;
		oldpages = pcb->pages;
		pcb->pages = pages;
		i = pcb->nrpages;
		pcb->nrpages = nrpages;
		raw_spin_unlock(&pcb->lock);

		अगर (!oldpages) अणु
			DBG_BUGON(old_ptr);
			जारी;
		पूर्ण

		अगर (old_ptr)
			vunmap(old_ptr);
मुक्त_pagearray:
		जबतक (i)
			list_add(&oldpages[--i]->lru, &pagepool);
		kमुक्त(oldpages);
		अगर (ret)
			अवरोध;
	पूर्ण
	pcb_nrpages = nrpages;
	put_pages_list(&pagepool);
out:
	mutex_unlock(&pcb_resize_mutex);
	वापस ret;
पूर्ण

व्योम erofs_pcpubuf_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा erofs_pcpubuf *pcb = &per_cpu(erofs_pcb, cpu);

		raw_spin_lock_init(&pcb->lock);
	पूर्ण
पूर्ण

व्योम erofs_pcpubuf_निकास(व्योम)
अणु
	पूर्णांक cpu, i;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा erofs_pcpubuf *pcb = &per_cpu(erofs_pcb, cpu);

		अगर (pcb->ptr) अणु
			vunmap(pcb->ptr);
			pcb->ptr = शून्य;
		पूर्ण
		अगर (!pcb->pages)
			जारी;

		क्रम (i = 0; i < pcb->nrpages; ++i)
			अगर (pcb->pages[i])
				put_page(pcb->pages[i]);
		kमुक्त(pcb->pages);
		pcb->pages = शून्य;
	पूर्ण
पूर्ण
