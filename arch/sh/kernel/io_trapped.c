<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Trapped io support
 *
 * Copyright (C) 2008 Magnus Damm
 *
 * Intercept io operations by trapping.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/io_trapped.h>

#घोषणा TRAPPED_PAGES_MAX 16

#अगर_घोषित CONFIG_HAS_IOPORT_MAP
LIST_HEAD(trapped_io);
EXPORT_SYMBOL_GPL(trapped_io);
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAS_IOMEM
LIST_HEAD(trapped_mem);
EXPORT_SYMBOL_GPL(trapped_mem);
#पूर्ण_अगर
अटल DEFINE_SPINLOCK(trapped_lock);

अटल पूर्णांक trapped_io_disable __पढ़ो_mostly;

अटल पूर्णांक __init trapped_io_setup(अक्षर *__unused)
अणु
	trapped_io_disable = 1;
	वापस 1;
पूर्ण
__setup("noiotrap", trapped_io_setup);

पूर्णांक रेजिस्टर_trapped_io(काष्ठा trapped_io *tiop)
अणु
	काष्ठा resource *res;
	अचिन्हित दीर्घ len = 0, flags = 0;
	काष्ठा page *pages[TRAPPED_PAGES_MAX];
	पूर्णांक k, n;

	अगर (unlikely(trapped_io_disable))
		वापस 0;

	/* काष्ठाure must be page aligned */
	अगर ((अचिन्हित दीर्घ)tiop & (PAGE_SIZE - 1))
		जाओ bad;

	क्रम (k = 0; k < tiop->num_resources; k++) अणु
		res = tiop->resource + k;
		len += roundup(resource_size(res), PAGE_SIZE);
		flags |= res->flags;
	पूर्ण

	/* support IORESOURCE_IO _or_ MEM, not both */
	अगर (hweight_दीर्घ(flags) != 1)
		जाओ bad;

	n = len >> PAGE_SHIFT;

	अगर (n >= TRAPPED_PAGES_MAX)
		जाओ bad;

	क्रम (k = 0; k < n; k++)
		pages[k] = virt_to_page(tiop);

	tiop->virt_base = vmap(pages, n, VM_MAP, PAGE_NONE);
	अगर (!tiop->virt_base)
		जाओ bad;

	len = 0;
	क्रम (k = 0; k < tiop->num_resources; k++) अणु
		res = tiop->resource + k;
		pr_info("trapped io 0x%08lx overrides %s 0x%08lx\n",
		       (अचिन्हित दीर्घ)(tiop->virt_base + len),
		       res->flags & IORESOURCE_IO ? "io" : "mmio",
		       (अचिन्हित दीर्घ)res->start);
		len += roundup(resource_size(res), PAGE_SIZE);
	पूर्ण

	tiop->magic = IO_TRAPPED_MAGIC;
	INIT_LIST_HEAD(&tiop->list);
	spin_lock_irq(&trapped_lock);
#अगर_घोषित CONFIG_HAS_IOPORT_MAP
	अगर (flags & IORESOURCE_IO)
		list_add(&tiop->list, &trapped_io);
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAS_IOMEM
	अगर (flags & IORESOURCE_MEM)
		list_add(&tiop->list, &trapped_mem);
#पूर्ण_अगर
	spin_unlock_irq(&trapped_lock);

	वापस 0;
 bad:
	pr_warn("unable to install trapped io filter\n");
	वापस -1;
पूर्ण

व्योम __iomem *match_trapped_io_handler(काष्ठा list_head *list,
				       अचिन्हित दीर्घ offset,
				       अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ voffs;
	काष्ठा trapped_io *tiop;
	काष्ठा resource *res;
	पूर्णांक k, len;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&trapped_lock, flags);
	list_क्रम_each_entry(tiop, list, list) अणु
		voffs = 0;
		क्रम (k = 0; k < tiop->num_resources; k++) अणु
			res = tiop->resource + k;
			अगर (res->start == offset) अणु
				spin_unlock_irqrestore(&trapped_lock, flags);
				वापस tiop->virt_base + voffs;
			पूर्ण

			len = resource_size(res);
			voffs += roundup(len, PAGE_SIZE);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&trapped_lock, flags);
	वापस शून्य;
पूर्ण

अटल काष्ठा trapped_io *lookup_tiop(अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd_k;
	p4d_t *p4d_k;
	pud_t *pud_k;
	pmd_t *pmd_k;
	pte_t *pte_k;
	pte_t entry;

	pgd_k = swapper_pg_dir + pgd_index(address);
	अगर (!pgd_present(*pgd_k))
		वापस शून्य;

	p4d_k = p4d_offset(pgd_k, address);
	अगर (!p4d_present(*p4d_k))
		वापस शून्य;

	pud_k = pud_offset(p4d_k, address);
	अगर (!pud_present(*pud_k))
		वापस शून्य;

	pmd_k = pmd_offset(pud_k, address);
	अगर (!pmd_present(*pmd_k))
		वापस शून्य;

	pte_k = pte_offset_kernel(pmd_k, address);
	entry = *pte_k;

	वापस pfn_to_kaddr(pte_pfn(entry));
पूर्ण

अटल अचिन्हित दीर्घ lookup_address(काष्ठा trapped_io *tiop,
				    अचिन्हित दीर्घ address)
अणु
	काष्ठा resource *res;
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)tiop->virt_base;
	अचिन्हित दीर्घ len;
	पूर्णांक k;

	क्रम (k = 0; k < tiop->num_resources; k++) अणु
		res = tiop->resource + k;
		len = roundup(resource_size(res), PAGE_SIZE);
		अगर (address < (vaddr + len))
			वापस res->start + (address - vaddr);
		vaddr += len;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ copy_word(अचिन्हित दीर्घ src_addr, पूर्णांक src_len,
				    अचिन्हित दीर्घ dst_addr, पूर्णांक dst_len)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp = 0;

	चयन (src_len) अणु
	हाल 1:
		पंचांगp = __raw_पढ़ोb(src_addr);
		अवरोध;
	हाल 2:
		पंचांगp = __raw_पढ़ोw(src_addr);
		अवरोध;
	हाल 4:
		पंचांगp = __raw_पढ़ोl(src_addr);
		अवरोध;
	हाल 8:
		पंचांगp = __raw_पढ़ोq(src_addr);
		अवरोध;
	पूर्ण

	चयन (dst_len) अणु
	हाल 1:
		__raw_ग_लिखोb(पंचांगp, dst_addr);
		अवरोध;
	हाल 2:
		__raw_ग_लिखोw(पंचांगp, dst_addr);
		अवरोध;
	हाल 4:
		__raw_ग_लिखोl(पंचांगp, dst_addr);
		अवरोध;
	हाल 8:
		__raw_ग_लिखोq(पंचांगp, dst_addr);
		अवरोध;
	पूर्ण

	वापस पंचांगp;
पूर्ण

अटल अचिन्हित दीर्घ from_device(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ cnt)
अणु
	काष्ठा trapped_io *tiop;
	अचिन्हित दीर्घ src_addr = (अचिन्हित दीर्घ)src;
	अचिन्हित दीर्घ दीर्घ पंचांगp;

	pr_debug("trapped io read 0x%08lx (%ld)\n", src_addr, cnt);
	tiop = lookup_tiop(src_addr);
	WARN_ON(!tiop || (tiop->magic != IO_TRAPPED_MAGIC));

	src_addr = lookup_address(tiop, src_addr);
	अगर (!src_addr)
		वापस cnt;

	पंचांगp = copy_word(src_addr,
			max_t(अचिन्हित दीर्घ, cnt,
			      (tiop->minimum_bus_width / 8)),
			(अचिन्हित दीर्घ)dst, cnt);

	pr_debug("trapped io read 0x%08lx -> 0x%08llx\n", src_addr, पंचांगp);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ to_device(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ cnt)
अणु
	काष्ठा trapped_io *tiop;
	अचिन्हित दीर्घ dst_addr = (अचिन्हित दीर्घ)dst;
	अचिन्हित दीर्घ दीर्घ पंचांगp;

	pr_debug("trapped io write 0x%08lx (%ld)\n", dst_addr, cnt);
	tiop = lookup_tiop(dst_addr);
	WARN_ON(!tiop || (tiop->magic != IO_TRAPPED_MAGIC));

	dst_addr = lookup_address(tiop, dst_addr);
	अगर (!dst_addr)
		वापस cnt;

	पंचांगp = copy_word((अचिन्हित दीर्घ)src, cnt,
			dst_addr, max_t(अचिन्हित दीर्घ, cnt,
					(tiop->minimum_bus_width / 8)));

	pr_debug("trapped io write 0x%08lx -> 0x%08llx\n", dst_addr, पंचांगp);
	वापस 0;
पूर्ण

अटल काष्ठा mem_access trapped_io_access = अणु
	from_device,
	to_device,
पूर्ण;

पूर्णांक handle_trapped_io(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	mm_segment_t oldfs;
	insn_माप_प्रकार inकाष्ठाion;
	पूर्णांक पंचांगp;

	अगर (trapped_io_disable)
		वापस 0;
	अगर (!lookup_tiop(address))
		वापस 0;

	WARN_ON(user_mode(regs));

	oldfs = get_fs();
	set_fs(KERNEL_DS);
	अगर (copy_from_user(&inकाष्ठाion, (व्योम *)(regs->pc),
			   माप(inकाष्ठाion))) अणु
		set_fs(oldfs);
		वापस 0;
	पूर्ण

	पंचांगp = handle_unaligned_access(inकाष्ठाion, regs,
				      &trapped_io_access, 1, address);
	set_fs(oldfs);
	वापस पंचांगp == 0;
पूर्ण
