<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/tlbflush.h>
#समावेश <as-layout.h>
#समावेश <mem_user.h>
#समावेश <os.h>
#समावेश <skas.h>
#समावेश <kern_util.h>

काष्ठा host_vm_change अणु
	काष्ठा host_vm_op अणु
		क्रमागत अणु NONE, MMAP, MUNMAP, MPROTECT पूर्ण type;
		जोड़ अणु
			काष्ठा अणु
				अचिन्हित दीर्घ addr;
				अचिन्हित दीर्घ len;
				अचिन्हित पूर्णांक prot;
				पूर्णांक fd;
				__u64 offset;
			पूर्ण mmap;
			काष्ठा अणु
				अचिन्हित दीर्घ addr;
				अचिन्हित दीर्घ len;
			पूर्ण munmap;
			काष्ठा अणु
				अचिन्हित दीर्घ addr;
				अचिन्हित दीर्घ len;
				अचिन्हित पूर्णांक prot;
			पूर्ण mprotect;
		पूर्ण u;
	पूर्ण ops[1];
	पूर्णांक userspace;
	पूर्णांक index;
	काष्ठा mm_काष्ठा *mm;
	व्योम *data;
	पूर्णांक क्रमce;
पूर्ण;

#घोषणा INIT_HVC(mm, क्रमce, userspace) \
	((काष्ठा host_vm_change) \
	 अणु .ops		= अणु अणु .type = NONE पूर्ण पूर्ण,	\
	   .mm		= mm, \
       	   .data	= शून्य, \
	   .userspace	= userspace, \
	   .index	= 0, \
	   .क्रमce	= क्रमce पूर्ण)

अटल व्योम report_enomem(व्योम)
अणु
	prपूर्णांकk(KERN_ERR "UML ran out of memory on the host side! "
			"This can happen due to a memory limitation or "
			"vm.max_map_count has been reached.\n");
पूर्ण

अटल पूर्णांक करो_ops(काष्ठा host_vm_change *hvc, पूर्णांक end,
		  पूर्णांक finished)
अणु
	काष्ठा host_vm_op *op;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < end && !ret; i++) अणु
		op = &hvc->ops[i];
		चयन (op->type) अणु
		हाल MMAP:
			अगर (hvc->userspace)
				ret = map(&hvc->mm->context.id, op->u.mmap.addr,
					  op->u.mmap.len, op->u.mmap.prot,
					  op->u.mmap.fd,
					  op->u.mmap.offset, finished,
					  &hvc->data);
			अन्यथा
				map_memory(op->u.mmap.addr, op->u.mmap.offset,
					   op->u.mmap.len, 1, 1, 1);
			अवरोध;
		हाल MUNMAP:
			अगर (hvc->userspace)
				ret = unmap(&hvc->mm->context.id,
					    op->u.munmap.addr,
					    op->u.munmap.len, finished,
					    &hvc->data);
			अन्यथा
				ret = os_unmap_memory(
					(व्योम *) op->u.munmap.addr,
						      op->u.munmap.len);

			अवरोध;
		हाल MPROTECT:
			अगर (hvc->userspace)
				ret = protect(&hvc->mm->context.id,
					      op->u.mprotect.addr,
					      op->u.mprotect.len,
					      op->u.mprotect.prot,
					      finished, &hvc->data);
			अन्यथा
				ret = os_protect_memory(
					(व्योम *) op->u.mprotect.addr,
							op->u.mprotect.len,
							1, 1, 1);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "Unknown op type %d in do_ops\n",
			       op->type);
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret == -ENOMEM)
		report_enomem();

	वापस ret;
पूर्ण

अटल पूर्णांक add_mmap(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ phys, अचिन्हित दीर्घ len,
		    अचिन्हित पूर्णांक prot, काष्ठा host_vm_change *hvc)
अणु
	__u64 offset;
	काष्ठा host_vm_op *last;
	पूर्णांक fd = -1, ret = 0;

	अगर (hvc->userspace)
		fd = phys_mapping(phys, &offset);
	अन्यथा
		offset = phys;
	अगर (hvc->index != 0) अणु
		last = &hvc->ops[hvc->index - 1];
		अगर ((last->type == MMAP) &&
		   (last->u.mmap.addr + last->u.mmap.len == virt) &&
		   (last->u.mmap.prot == prot) && (last->u.mmap.fd == fd) &&
		   (last->u.mmap.offset + last->u.mmap.len == offset)) अणु
			last->u.mmap.len += len;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (hvc->index == ARRAY_SIZE(hvc->ops)) अणु
		ret = करो_ops(hvc, ARRAY_SIZE(hvc->ops), 0);
		hvc->index = 0;
	पूर्ण

	hvc->ops[hvc->index++] = ((काष्ठा host_vm_op)
				  अणु .type	= MMAP,
				    .u = अणु .mmap = अणु .addr	= virt,
						     .len	= len,
						     .prot	= prot,
						     .fd	= fd,
						     .offset	= offset पूर्ण
			   पूर्ण पूर्ण);
	वापस ret;
पूर्ण

अटल पूर्णांक add_munmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		      काष्ठा host_vm_change *hvc)
अणु
	काष्ठा host_vm_op *last;
	पूर्णांक ret = 0;

	अगर (hvc->index != 0) अणु
		last = &hvc->ops[hvc->index - 1];
		अगर ((last->type == MUNMAP) &&
		   (last->u.munmap.addr + last->u.mmap.len == addr)) अणु
			last->u.munmap.len += len;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (hvc->index == ARRAY_SIZE(hvc->ops)) अणु
		ret = करो_ops(hvc, ARRAY_SIZE(hvc->ops), 0);
		hvc->index = 0;
	पूर्ण

	hvc->ops[hvc->index++] = ((काष्ठा host_vm_op)
				  अणु .type	= MUNMAP,
			     	    .u = अणु .munmap = अणु .addr	= addr,
						       .len	= len पूर्ण पूर्ण पूर्ण);
	वापस ret;
पूर्ण

अटल पूर्णांक add_mprotect(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			अचिन्हित पूर्णांक prot, काष्ठा host_vm_change *hvc)
अणु
	काष्ठा host_vm_op *last;
	पूर्णांक ret = 0;

	अगर (hvc->index != 0) अणु
		last = &hvc->ops[hvc->index - 1];
		अगर ((last->type == MPROTECT) &&
		   (last->u.mprotect.addr + last->u.mprotect.len == addr) &&
		   (last->u.mprotect.prot == prot)) अणु
			last->u.mprotect.len += len;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (hvc->index == ARRAY_SIZE(hvc->ops)) अणु
		ret = करो_ops(hvc, ARRAY_SIZE(hvc->ops), 0);
		hvc->index = 0;
	पूर्ण

	hvc->ops[hvc->index++] = ((काष्ठा host_vm_op)
				  अणु .type	= MPROTECT,
			     	    .u = अणु .mprotect = अणु .addr	= addr,
							 .len	= len,
							 .prot	= prot पूर्ण पूर्ण पूर्ण);
	वापस ret;
पूर्ण

#घोषणा ADD_ROUND(n, inc) (((n) + (inc)) & ~((inc) - 1))

अटल अंतरभूत पूर्णांक update_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr,
				   अचिन्हित दीर्घ end,
				   काष्ठा host_vm_change *hvc)
अणु
	pte_t *pte;
	पूर्णांक r, w, x, prot, ret = 0;

	pte = pte_offset_kernel(pmd, addr);
	करो अणु
		r = pte_पढ़ो(*pte);
		w = pte_ग_लिखो(*pte);
		x = pte_exec(*pte);
		अगर (!pte_young(*pte)) अणु
			r = 0;
			w = 0;
		पूर्ण अन्यथा अगर (!pte_dirty(*pte))
			w = 0;

		prot = ((r ? UM_PROT_READ : 0) | (w ? UM_PROT_WRITE : 0) |
			(x ? UM_PROT_EXEC : 0));
		अगर (hvc->क्रमce || pte_newpage(*pte)) अणु
			अगर (pte_present(*pte)) अणु
				अगर (pte_newpage(*pte))
					ret = add_mmap(addr, pte_val(*pte) & PAGE_MASK,
						       PAGE_SIZE, prot, hvc);
			पूर्ण अन्यथा
				ret = add_munmap(addr, PAGE_SIZE, hvc);
		पूर्ण अन्यथा अगर (pte_newprot(*pte))
			ret = add_mprotect(addr, PAGE_SIZE, prot, hvc);
		*pte = pte_mkuptodate(*pte);
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, ((addr < end) && !ret));
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक update_pmd_range(pud_t *pud, अचिन्हित दीर्घ addr,
				   अचिन्हित दीर्घ end,
				   काष्ठा host_vm_change *hvc)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	पूर्णांक ret = 0;

	pmd = pmd_offset(pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (!pmd_present(*pmd)) अणु
			अगर (hvc->क्रमce || pmd_newpage(*pmd)) अणु
				ret = add_munmap(addr, next - addr, hvc);
				pmd_mkuptodate(*pmd);
			पूर्ण
		पूर्ण
		अन्यथा ret = update_pte_range(pmd, addr, next, hvc);
	पूर्ण जबतक (pmd++, addr = next, ((addr < end) && !ret));
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक update_pud_range(p4d_t *p4d, अचिन्हित दीर्घ addr,
				   अचिन्हित दीर्घ end,
				   काष्ठा host_vm_change *hvc)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	पूर्णांक ret = 0;

	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (!pud_present(*pud)) अणु
			अगर (hvc->क्रमce || pud_newpage(*pud)) अणु
				ret = add_munmap(addr, next - addr, hvc);
				pud_mkuptodate(*pud);
			पूर्ण
		पूर्ण
		अन्यथा ret = update_pmd_range(pud, addr, next, hvc);
	पूर्ण जबतक (pud++, addr = next, ((addr < end) && !ret));
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक update_p4d_range(pgd_t *pgd, अचिन्हित दीर्घ addr,
				   अचिन्हित दीर्घ end,
				   काष्ठा host_vm_change *hvc)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	पूर्णांक ret = 0;

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (!p4d_present(*p4d)) अणु
			अगर (hvc->क्रमce || p4d_newpage(*p4d)) अणु
				ret = add_munmap(addr, next - addr, hvc);
				p4d_mkuptodate(*p4d);
			पूर्ण
		पूर्ण अन्यथा
			ret = update_pud_range(p4d, addr, next, hvc);
	पूर्ण जबतक (p4d++, addr = next, ((addr < end) && !ret));
	वापस ret;
पूर्ण

व्योम fix_range_common(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start_addr,
		      अचिन्हित दीर्घ end_addr, पूर्णांक क्रमce)
अणु
	pgd_t *pgd;
	काष्ठा host_vm_change hvc;
	अचिन्हित दीर्घ addr = start_addr, next;
	पूर्णांक ret = 0, userspace = 1;

	hvc = INIT_HVC(mm, क्रमce, userspace);
	pgd = pgd_offset(mm, addr);
	करो अणु
		next = pgd_addr_end(addr, end_addr);
		अगर (!pgd_present(*pgd)) अणु
			अगर (क्रमce || pgd_newpage(*pgd)) अणु
				ret = add_munmap(addr, next - addr, &hvc);
				pgd_mkuptodate(*pgd);
			पूर्ण
		पूर्ण अन्यथा
			ret = update_p4d_range(pgd, addr, next, &hvc);
	पूर्ण जबतक (pgd++, addr = next, ((addr < end_addr) && !ret));

	अगर (!ret)
		ret = करो_ops(&hvc, hvc.index, 1);

	/* This is not an अन्यथा because ret is modअगरied above */
	अगर (ret) अणु
		काष्ठा mm_id *mm_idp = &current->mm->context.id;

		prपूर्णांकk(KERN_ERR "fix_range_common: failed, killing current "
		       "process: %d\n", task_tgid_vnr(current));
		mm_idp->समाप्त = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक flush_tlb_kernel_range_common(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	अचिन्हित दीर्घ addr, last;
	पूर्णांक updated = 0, err = 0, क्रमce = 0, userspace = 0;
	काष्ठा host_vm_change hvc;

	mm = &init_mm;
	hvc = INIT_HVC(mm, क्रमce, userspace);
	क्रम (addr = start; addr < end;) अणु
		pgd = pgd_offset(mm, addr);
		अगर (!pgd_present(*pgd)) अणु
			last = ADD_ROUND(addr, PGसूची_SIZE);
			अगर (last > end)
				last = end;
			अगर (pgd_newpage(*pgd)) अणु
				updated = 1;
				err = add_munmap(addr, last - addr, &hvc);
				अगर (err < 0)
					panic("munmap failed, errno = %d\n",
					      -err);
			पूर्ण
			addr = last;
			जारी;
		पूर्ण

		p4d = p4d_offset(pgd, addr);
		अगर (!p4d_present(*p4d)) अणु
			last = ADD_ROUND(addr, P4D_SIZE);
			अगर (last > end)
				last = end;
			अगर (p4d_newpage(*p4d)) अणु
				updated = 1;
				err = add_munmap(addr, last - addr, &hvc);
				अगर (err < 0)
					panic("munmap failed, errno = %d\n",
					      -err);
			पूर्ण
			addr = last;
			जारी;
		पूर्ण

		pud = pud_offset(p4d, addr);
		अगर (!pud_present(*pud)) अणु
			last = ADD_ROUND(addr, PUD_SIZE);
			अगर (last > end)
				last = end;
			अगर (pud_newpage(*pud)) अणु
				updated = 1;
				err = add_munmap(addr, last - addr, &hvc);
				अगर (err < 0)
					panic("munmap failed, errno = %d\n",
					      -err);
			पूर्ण
			addr = last;
			जारी;
		पूर्ण

		pmd = pmd_offset(pud, addr);
		अगर (!pmd_present(*pmd)) अणु
			last = ADD_ROUND(addr, PMD_SIZE);
			अगर (last > end)
				last = end;
			अगर (pmd_newpage(*pmd)) अणु
				updated = 1;
				err = add_munmap(addr, last - addr, &hvc);
				अगर (err < 0)
					panic("munmap failed, errno = %d\n",
					      -err);
			पूर्ण
			addr = last;
			जारी;
		पूर्ण

		pte = pte_offset_kernel(pmd, addr);
		अगर (!pte_present(*pte) || pte_newpage(*pte)) अणु
			updated = 1;
			err = add_munmap(addr, PAGE_SIZE, &hvc);
			अगर (err < 0)
				panic("munmap failed, errno = %d\n",
				      -err);
			अगर (pte_present(*pte))
				err = add_mmap(addr, pte_val(*pte) & PAGE_MASK,
					       PAGE_SIZE, 0, &hvc);
		पूर्ण
		अन्यथा अगर (pte_newprot(*pte)) अणु
			updated = 1;
			err = add_mprotect(addr, PAGE_SIZE, 0, &hvc);
		पूर्ण
		addr += PAGE_SIZE;
	पूर्ण
	अगर (!err)
		err = करो_ops(&hvc, hvc.index, 1);

	अगर (err < 0)
		panic("flush_tlb_kernel failed, errno = %d\n", err);
	वापस updated;
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	व्योम *flush = शून्य;
	पूर्णांक r, w, x, prot, err = 0;
	काष्ठा mm_id *mm_id;

	address &= PAGE_MASK;

	pgd = pgd_offset(mm, address);
	अगर (!pgd_present(*pgd))
		जाओ समाप्त;

	p4d = p4d_offset(pgd, address);
	अगर (!p4d_present(*p4d))
		जाओ समाप्त;

	pud = pud_offset(p4d, address);
	अगर (!pud_present(*pud))
		जाओ समाप्त;

	pmd = pmd_offset(pud, address);
	अगर (!pmd_present(*pmd))
		जाओ समाप्त;

	pte = pte_offset_kernel(pmd, address);

	r = pte_पढ़ो(*pte);
	w = pte_ग_लिखो(*pte);
	x = pte_exec(*pte);
	अगर (!pte_young(*pte)) अणु
		r = 0;
		w = 0;
	पूर्ण अन्यथा अगर (!pte_dirty(*pte)) अणु
		w = 0;
	पूर्ण

	mm_id = &mm->context.id;
	prot = ((r ? UM_PROT_READ : 0) | (w ? UM_PROT_WRITE : 0) |
		(x ? UM_PROT_EXEC : 0));
	अगर (pte_newpage(*pte)) अणु
		अगर (pte_present(*pte)) अणु
			अचिन्हित दीर्घ दीर्घ offset;
			पूर्णांक fd;

			fd = phys_mapping(pte_val(*pte) & PAGE_MASK, &offset);
			err = map(mm_id, address, PAGE_SIZE, prot, fd, offset,
				  1, &flush);
		पूर्ण
		अन्यथा err = unmap(mm_id, address, PAGE_SIZE, 1, &flush);
	पूर्ण
	अन्यथा अगर (pte_newprot(*pte))
		err = protect(mm_id, address, PAGE_SIZE, prot, 1, &flush);

	अगर (err) अणु
		अगर (err == -ENOMEM)
			report_enomem();

		जाओ समाप्त;
	पूर्ण

	*pte = pte_mkuptodate(*pte);

	वापस;

समाप्त:
	prपूर्णांकk(KERN_ERR "Failed to flush page for address 0x%lx\n", address);
	क्रमce_sig(SIGKILL);
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	/*
	 * Don't bother flushing अगर this address space is about to be
	 * destroyed.
	 */
	अगर (atomic_पढ़ो(&current->mm->mm_users) == 0)
		वापस;

	flush_tlb_mm(current->mm);
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	flush_tlb_kernel_range_common(start, end);
पूर्ण

व्योम flush_tlb_kernel_vm(व्योम)
अणु
	flush_tlb_kernel_range_common(start_vm, end_vm);
पूर्ण

व्योम __flush_tlb_one(अचिन्हित दीर्घ addr)
अणु
	flush_tlb_kernel_range_common(addr, addr + PAGE_SIZE);
पूर्ण

अटल व्योम fix_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start_addr,
		      अचिन्हित दीर्घ end_addr, पूर्णांक क्रमce)
अणु
	/*
	 * Don't bother flushing अगर this address space is about to be
	 * destroyed.
	 */
	अगर (atomic_पढ़ो(&mm->mm_users) == 0)
		वापस;

	fix_range_common(mm, start_addr, end_addr, क्रमce);
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end)
अणु
	अगर (vma->vm_mm == शून्य)
		flush_tlb_kernel_range_common(start, end);
	अन्यथा fix_range(vma->vm_mm, start, end, 0);
पूर्ण
EXPORT_SYMBOL(flush_tlb_range);

व्योम flush_tlb_mm_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	fix_range(mm, start, end, 0);
पूर्ण

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma = mm->mmap;

	जबतक (vma != शून्य) अणु
		fix_range(mm, vma->vm_start, vma->vm_end, 0);
		vma = vma->vm_next;
	पूर्ण
पूर्ण

व्योम क्रमce_flush_all(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma = mm->mmap;

	जबतक (vma != शून्य) अणु
		fix_range(mm, vma->vm_start, vma->vm_end, 1);
		vma = vma->vm_next;
	पूर्ण
पूर्ण
