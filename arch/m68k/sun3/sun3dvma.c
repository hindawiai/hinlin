<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/m68k/sun3/sun3dvma.c
 *
 * Copyright (C) 2000 Sam Creasey
 *
 * Contains common routines क्रम sun3/sun3x DVMA management.
 */

#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/list.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/dvma.h>

#अघोषित DVMA_DEBUG

#अगर_घोषित CONFIG_SUN3X
बाह्य व्योम dvma_unmap_iommu(अचिन्हित दीर्घ baddr, पूर्णांक len);
#अन्यथा
अटल अंतरभूत व्योम dvma_unmap_iommu(अचिन्हित दीर्घ a, पूर्णांक b)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SUN3
बाह्य व्योम sun3_dvma_init(व्योम);
#पूर्ण_अगर

अटल अचिन्हित दीर्घ *iommu_use;

#घोषणा dvma_index(baddr) ((baddr - DVMA_START) >> DVMA_PAGE_SHIFT)

#घोषणा dvma_entry_use(baddr)		(iommu_use[dvma_index(baddr)])

काष्ठा hole अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ size;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा list_head hole_list;
अटल काष्ठा list_head hole_cache;
अटल काष्ठा hole initholes[64];

#अगर_घोषित DVMA_DEBUG

अटल अचिन्हित दीर्घ dvma_allocs;
अटल अचिन्हित दीर्घ dvma_मुक्तs;
अटल अचिन्हित दीर्घ दीर्घ dvma_alloc_bytes;
अटल अचिन्हित दीर्घ दीर्घ dvma_मुक्त_bytes;

अटल व्योम prपूर्णांक_use(व्योम)
अणु

	पूर्णांक i;
	पूर्णांक j = 0;

	pr_info("dvma entry usage:\n");

	क्रम(i = 0; i < IOMMU_TOTAL_ENTRIES; i++) अणु
		अगर(!iommu_use[i])
			जारी;

		j++;

		pr_info("dvma entry: %08x len %08lx\n",
			(i << DVMA_PAGE_SHIFT) + DVMA_START, iommu_use[i]);
	पूर्ण

	pr_info("%d entries in use total\n", j);

	pr_info("allocation/free calls: %lu/%lu\n", dvma_allocs, dvma_मुक्तs);
	pr_info("allocation/free bytes: %Lx/%Lx\n", dvma_alloc_bytes,
		dvma_मुक्त_bytes);
पूर्ण

अटल व्योम prपूर्णांक_holes(काष्ठा list_head *holes)
अणु

	काष्ठा list_head *cur;
	काष्ठा hole *hole;

	pr_info("listing dvma holes\n");
	list_क्रम_each(cur, holes) अणु
		hole = list_entry(cur, काष्ठा hole, list);

		अगर((hole->start == 0) && (hole->end == 0) && (hole->size == 0))
			जारी;

		pr_info("hole: start %08lx end %08lx size %08lx\n",
			hole->start, hole->end, hole->size);
	पूर्ण

	pr_info("end of hole listing...\n");
पूर्ण
#पूर्ण_अगर /* DVMA_DEBUG */

अटल अंतरभूत पूर्णांक refill(व्योम)
अणु

	काष्ठा hole *hole;
	काष्ठा hole *prev = शून्य;
	काष्ठा list_head *cur;
	पूर्णांक ret = 0;

	list_क्रम_each(cur, &hole_list) अणु
		hole = list_entry(cur, काष्ठा hole, list);

		अगर(!prev) अणु
			prev = hole;
			जारी;
		पूर्ण

		अगर(hole->end == prev->start) अणु
			hole->size += prev->size;
			hole->end = prev->end;
			list_move(&(prev->list), &hole_cache);
			ret++;
		पूर्ण

	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा hole *rmcache(व्योम)
अणु
	काष्ठा hole *ret;

	अगर(list_empty(&hole_cache)) अणु
		अगर(!refill()) अणु
			pr_crit("out of dvma hole cache!\n");
			BUG();
		पूर्ण
	पूर्ण

	ret = list_entry(hole_cache.next, काष्ठा hole, list);
	list_del(&(ret->list));

	वापस ret;

पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_baddr(पूर्णांक len, अचिन्हित दीर्घ align)
अणु

	काष्ठा list_head *cur;
	काष्ठा hole *hole;

	अगर(list_empty(&hole_list)) अणु
#अगर_घोषित DVMA_DEBUG
		pr_crit("out of dvma holes! (printing hole cache)\n");
		prपूर्णांक_holes(&hole_cache);
		prपूर्णांक_use();
#पूर्ण_अगर
		BUG();
	पूर्ण

	list_क्रम_each(cur, &hole_list) अणु
		अचिन्हित दीर्घ newlen;

		hole = list_entry(cur, काष्ठा hole, list);

		अगर(align > DVMA_PAGE_SIZE)
			newlen = len + ((hole->end - len) & (align-1));
		अन्यथा
			newlen = len;

		अगर(hole->size > newlen) अणु
			hole->end -= newlen;
			hole->size -= newlen;
			dvma_entry_use(hole->end) = newlen;
#अगर_घोषित DVMA_DEBUG
			dvma_allocs++;
			dvma_alloc_bytes += newlen;
#पूर्ण_अगर
			वापस hole->end;
		पूर्ण अन्यथा अगर(hole->size == newlen) अणु
			list_move(&(hole->list), &hole_cache);
			dvma_entry_use(hole->start) = newlen;
#अगर_घोषित DVMA_DEBUG
			dvma_allocs++;
			dvma_alloc_bytes += newlen;
#पूर्ण_अगर
			वापस hole->start;
		पूर्ण

	पूर्ण

	pr_crit("unable to find dvma hole!\n");
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक मुक्त_baddr(अचिन्हित दीर्घ baddr)
अणु

	अचिन्हित दीर्घ len;
	काष्ठा hole *hole;
	काष्ठा list_head *cur;
	अचिन्हित दीर्घ orig_baddr;

	orig_baddr = baddr;
	len = dvma_entry_use(baddr);
	dvma_entry_use(baddr) = 0;
	baddr &= DVMA_PAGE_MASK;
	dvma_unmap_iommu(baddr, len);

#अगर_घोषित DVMA_DEBUG
	dvma_मुक्तs++;
	dvma_मुक्त_bytes += len;
#पूर्ण_अगर

	list_क्रम_each(cur, &hole_list) अणु
		hole = list_entry(cur, काष्ठा hole, list);

		अगर(hole->end == baddr) अणु
			hole->end += len;
			hole->size += len;
			वापस 0;
		पूर्ण अन्यथा अगर(hole->start == (baddr + len)) अणु
			hole->start = baddr;
			hole->size += len;
			वापस 0;
		पूर्ण

	पूर्ण

	hole = rmcache();

	hole->start = baddr;
	hole->end = baddr + len;
	hole->size = len;

//	list_add_tail(&(hole->list), cur);
	list_add(&(hole->list), cur);

	वापस 0;

पूर्ण

व्योम __init dvma_init(व्योम)
अणु

	काष्ठा hole *hole;
	पूर्णांक i;

	INIT_LIST_HEAD(&hole_list);
	INIT_LIST_HEAD(&hole_cache);

	/* prepare the hole cache */
	क्रम(i = 0; i < 64; i++)
		list_add(&(initholes[i].list), &hole_cache);

	hole = rmcache();
	hole->start = DVMA_START;
	hole->end = DVMA_END;
	hole->size = DVMA_SIZE;

	list_add(&(hole->list), &hole_list);

	iommu_use = memblock_alloc(IOMMU_TOTAL_ENTRIES * माप(अचिन्हित दीर्घ),
				   SMP_CACHE_BYTES);
	अगर (!iommu_use)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      IOMMU_TOTAL_ENTRIES * माप(अचिन्हित दीर्घ));

	dvma_unmap_iommu(DVMA_START, DVMA_SIZE);

#अगर_घोषित CONFIG_SUN3
	sun3_dvma_init();
#पूर्ण_अगर

पूर्ण

अचिन्हित दीर्घ dvma_map_align(अचिन्हित दीर्घ kaddr, पूर्णांक len, पूर्णांक align)
अणु

	अचिन्हित दीर्घ baddr;
	अचिन्हित दीर्घ off;

	अगर(!len)
		len = 0x800;

	अगर(!kaddr || !len) अणु
//		pr_err("error: kaddr %lx len %x\n", kaddr, len);
//		*(पूर्णांक *)4 = 0;
		वापस 0;
	पूर्ण

	pr_debug("dvma_map request %08x bytes from %08lx\n", len, kaddr);
	off = kaddr & ~DVMA_PAGE_MASK;
	kaddr &= PAGE_MASK;
	len += off;
	len = ((len + (DVMA_PAGE_SIZE-1)) & DVMA_PAGE_MASK);

	अगर(align == 0)
		align = DVMA_PAGE_SIZE;
	अन्यथा
		align = ((align + (DVMA_PAGE_SIZE-1)) & DVMA_PAGE_MASK);

	baddr = get_baddr(len, align);
//	pr_info("using baddr %lx\n", baddr);

	अगर(!dvma_map_iommu(kaddr, baddr, len))
		वापस (baddr + off);

	pr_crit("dvma_map failed kaddr %lx baddr %lx len %x\n", kaddr, baddr,
	len);
	BUG();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvma_map_align);

व्योम dvma_unmap(व्योम *baddr)
अणु
	अचिन्हित दीर्घ addr;

	addr = (अचिन्हित दीर्घ)baddr;
	/* check अगर this is a vme mapping */
	अगर(!(addr & 0x00f00000))
		addr |= 0xf00000;

	मुक्त_baddr(addr);

	वापस;

पूर्ण
EXPORT_SYMBOL(dvma_unmap);

व्योम *dvma_दो_स्मृति_align(अचिन्हित दीर्घ len, अचिन्हित दीर्घ align)
अणु
	अचिन्हित दीर्घ kaddr;
	अचिन्हित दीर्घ baddr;
	अचिन्हित दीर्घ vaddr;

	अगर(!len)
		वापस शून्य;

	pr_debug("dvma_malloc request %lx bytes\n", len);
	len = ((len + (DVMA_PAGE_SIZE-1)) & DVMA_PAGE_MASK);

        अगर((kaddr = __get_मुक्त_pages(GFP_ATOMIC, get_order(len))) == 0)
		वापस शून्य;

	अगर((baddr = (अचिन्हित दीर्घ)dvma_map_align(kaddr, len, align)) == 0) अणु
		मुक्त_pages(kaddr, get_order(len));
		वापस शून्य;
	पूर्ण

	vaddr = dvma_btov(baddr);

	अगर(dvma_map_cpu(kaddr, vaddr, len) < 0) अणु
		dvma_unmap((व्योम *)baddr);
		मुक्त_pages(kaddr, get_order(len));
		वापस शून्य;
	पूर्ण

	pr_debug("mapped %08lx bytes %08lx kern -> %08lx bus\n", len, kaddr,
		 baddr);

	वापस (व्योम *)vaddr;

पूर्ण
EXPORT_SYMBOL(dvma_दो_स्मृति_align);

व्योम dvma_मुक्त(व्योम *vaddr)
अणु

	वापस;

पूर्ण
EXPORT_SYMBOL(dvma_मुक्त);
