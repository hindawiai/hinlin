<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/nds32.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/l2_cache.h>
#समावेश <nds32_पूर्णांकrinsic.h>

#समावेश <यंत्र/cache_info.h>
बाह्य काष्ठा cache_info L1_cache_info[2];

पूर्णांक va_kernel_present(अचिन्हित दीर्घ addr)
अणु
	pmd_t *pmd;
	pte_t *ptep, pte;

	pmd = pmd_off_k(addr);
	अगर (!pmd_none(*pmd)) अणु
		ptep = pte_offset_map(pmd, addr);
		pte = *ptep;
		अगर (pte_present(pte))
			वापस pte;
	पूर्ण
	वापस 0;
पूर्ण

pte_t va_present(काष्ठा mm_काष्ठा * mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *ptep, pte;

	pgd = pgd_offset(mm, addr);
	अगर (!pgd_none(*pgd)) अणु
		p4d = p4d_offset(pgd, addr);
		अगर (!p4d_none(*p4d)) अणु
			pud = pud_offset(p4d, addr);
			अगर (!pud_none(*pud)) अणु
				pmd = pmd_offset(pud, addr);
				अगर (!pmd_none(*pmd)) अणु
					ptep = pte_offset_map(pmd, addr);
					pte = *ptep;
					अगर (pte_present(pte))
						वापस pte;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

पूर्ण

पूर्णांक va_पढ़ोable(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	pte_t pte;
	पूर्णांक ret = 0;

	अगर (user_mode(regs)) अणु
		/* user mode */
		pte = va_present(mm, addr);
		अगर (!pte && pte_पढ़ो(pte))
			ret = 1;
	पूर्ण अन्यथा अणु
		/* superuser mode is always पढ़ोable, so we can only
		 * check it is present or not*/
		वापस (! !va_kernel_present(addr));
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक va_writable(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	pte_t pte;
	पूर्णांक ret = 0;

	अगर (user_mode(regs)) अणु
		/* user mode */
		pte = va_present(mm, addr);
		अगर (!pte && pte_ग_लिखो(pte))
			ret = 1;
	पूर्ण अन्यथा अणु
		/* superuser mode */
		pte = va_kernel_present(addr);
		अगर (!pte && pte_kernel_ग_लिखो(pte))
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * All
 */
व्योम cpu_icache_inval_all(व्योम)
अणु
	अचिन्हित दीर्घ end, line_size;

	line_size = L1_cache_info[ICACHE].line_size;
	end =
	    line_size * L1_cache_info[ICACHE].ways * L1_cache_info[ICACHE].sets;

	करो अणु
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
	पूर्ण जबतक (end > 0);
	__nds32__isb();
पूर्ण

व्योम cpu_dcache_inval_all(व्योम)
अणु
	__nds32__cctl_l1d_invalall();
पूर्ण

#अगर_घोषित CONFIG_CACHE_L2
व्योम dcache_wb_all_level(व्योम)
अणु
	अचिन्हित दीर्घ flags, cmd;
	local_irq_save(flags);
	__nds32__cctl_l1d_wball_alvl();
	/* Section 1: Ensure the section 2 & 3 program code execution after */
	__nds32__cctlidx_पढ़ो(NDS32_CCTL_L1D_IX_RWD,0);

	/* Section 2: Confirm the ग_लिखोback all level is करोne in CPU and L2C */
	cmd = CCTL_CMD_L2_SYNC;
	L2_CMD_RDY();
	L2C_W_REG(L2_CCTL_CMD_OFF, cmd);
	L2_CMD_RDY();

	/* Section 3: Writeback whole L2 cache */
	cmd = CCTL_ALL_CMD | CCTL_CMD_L2_IX_WB;
	L2_CMD_RDY();
	L2C_W_REG(L2_CCTL_CMD_OFF, cmd);
	L2_CMD_RDY();
	__nds32__msync_all();
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(dcache_wb_all_level);
#पूर्ण_अगर

व्योम cpu_dcache_wb_all(व्योम)
अणु
	__nds32__cctl_l1d_wball_one_lvl();
	__nds32__cctlidx_पढ़ो(NDS32_CCTL_L1D_IX_RWD,0);
पूर्ण

व्योम cpu_dcache_wbinval_all(व्योम)
अणु
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
#पूर्ण_अगर
	cpu_dcache_wb_all();
	cpu_dcache_inval_all();
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण

/*
 * Page
 */
व्योम cpu_icache_inval_page(अचिन्हित दीर्घ start)
अणु
	अचिन्हित दीर्घ line_size, end;

	line_size = L1_cache_info[ICACHE].line_size;
	end = start + PAGE_SIZE;

	करो अणु
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_VA_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_VA_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_VA_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_VA_INVAL"::"r" (end));
	पूर्ण जबतक (end != start);
	__nds32__isb();
पूर्ण

व्योम cpu_dcache_inval_page(अचिन्हित दीर्घ start)
अणु
	अचिन्हित दीर्घ line_size, end;

	line_size = L1_cache_info[DCACHE].line_size;
	end = start + PAGE_SIZE;

	करो अणु
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
	पूर्ण जबतक (end != start);
पूर्ण

व्योम cpu_dcache_wb_page(अचिन्हित दीर्घ start)
अणु
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
	अचिन्हित दीर्घ line_size, end;

	line_size = L1_cache_info[DCACHE].line_size;
	end = start + PAGE_SIZE;

	करो अणु
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
		end -= line_size;
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
	पूर्ण जबतक (end != start);
	__nds32__cctlidx_पढ़ो(NDS32_CCTL_L1D_IX_RWD,0);
#पूर्ण_अगर
पूर्ण

व्योम cpu_dcache_wbinval_page(अचिन्हित दीर्घ start)
अणु
	अचिन्हित दीर्घ line_size, end;

	line_size = L1_cache_info[DCACHE].line_size;
	end = start + PAGE_SIZE;

	करो अणु
		end -= line_size;
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
#पूर्ण_अगर
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
		end -= line_size;
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
#पूर्ण_अगर
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
		end -= line_size;
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
#पूर्ण_अगर
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
		end -= line_size;
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (end));
#पूर्ण_अगर
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (end));
	पूर्ण जबतक (end != start);
	__nds32__cctlidx_पढ़ो(NDS32_CCTL_L1D_IX_RWD,0);
पूर्ण

व्योम cpu_cache_wbinval_page(अचिन्हित दीर्घ page, पूर्णांक flushi)
अणु
	cpu_dcache_wbinval_page(page);
	अगर (flushi)
		cpu_icache_inval_page(page);
पूर्ण

/*
 * Range
 */
व्योम cpu_icache_inval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ line_size;

	line_size = L1_cache_info[ICACHE].line_size;

	जबतक (end > start) अणु
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1I_VA_INVAL"::"r" (start));
		start += line_size;
	पूर्ण
	__nds32__isb();
पूर्ण

व्योम cpu_dcache_inval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ line_size;

	line_size = L1_cache_info[DCACHE].line_size;

	जबतक (end > start) अणु
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (start));
		start += line_size;
	पूर्ण
पूर्ण

व्योम cpu_dcache_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
	अचिन्हित दीर्घ line_size;

	line_size = L1_cache_info[DCACHE].line_size;

	जबतक (end > start) अणु
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (start));
		start += line_size;
	पूर्ण
	__nds32__cctlidx_पढ़ो(NDS32_CCTL_L1D_IX_RWD,0);
#पूर्ण_अगर
पूर्ण

व्योम cpu_dcache_wbinval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ line_size;

	line_size = L1_cache_info[DCACHE].line_size;

	जबतक (end > start) अणु
#अगर_अघोषित CONFIG_CPU_DCACHE_WRITETHROUGH
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (start));
#पूर्ण_अगर
		__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_INVAL"::"r" (start));
		start += line_size;
	पूर्ण
	__nds32__cctlidx_पढ़ो(NDS32_CCTL_L1D_IX_RWD,0);
पूर्ण

व्योम cpu_cache_wbinval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक flushi)
अणु
	अचिन्हित दीर्घ line_size, align_start, align_end;

	line_size = L1_cache_info[DCACHE].line_size;
	align_start = start & ~(line_size - 1);
	align_end = (end + line_size - 1) & ~(line_size - 1);
	cpu_dcache_wbinval_range(align_start, align_end);

	अगर (flushi) अणु
		line_size = L1_cache_info[ICACHE].line_size;
		align_start = start & ~(line_size - 1);
		align_end = (end + line_size - 1) & ~(line_size - 1);
		cpu_icache_inval_range(align_start, align_end);
	पूर्ण
पूर्ण

व्योम cpu_cache_wbinval_range_check(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				   bool flushi, bool wbd)
अणु
	अचिन्हित दीर्घ line_size, t_start, t_end;

	अगर (!flushi && !wbd)
		वापस;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & ~(line_size - 1);
	end = (end + line_size - 1) & ~(line_size - 1);

	अगर ((end - start) > (8 * PAGE_SIZE)) अणु
		अगर (wbd)
			cpu_dcache_wbinval_all();
		अगर (flushi)
			cpu_icache_inval_all();
		वापस;
	पूर्ण

	t_start = (start + PAGE_SIZE) & PAGE_MASK;
	t_end = ((end - 1) & PAGE_MASK);

	अगर ((start & PAGE_MASK) == t_end) अणु
		अगर (va_present(vma->vm_mm, start)) अणु
			अगर (wbd)
				cpu_dcache_wbinval_range(start, end);
			अगर (flushi)
				cpu_icache_inval_range(start, end);
		पूर्ण
		वापस;
	पूर्ण

	अगर (va_present(vma->vm_mm, start)) अणु
		अगर (wbd)
			cpu_dcache_wbinval_range(start, t_start);
		अगर (flushi)
			cpu_icache_inval_range(start, t_start);
	पूर्ण

	अगर (va_present(vma->vm_mm, end - 1)) अणु
		अगर (wbd)
			cpu_dcache_wbinval_range(t_end, end);
		अगर (flushi)
			cpu_icache_inval_range(t_end, end);
	पूर्ण

	जबतक (t_start < t_end) अणु
		अगर (va_present(vma->vm_mm, t_start)) अणु
			अगर (wbd)
				cpu_dcache_wbinval_page(t_start);
			अगर (flushi)
				cpu_icache_inval_page(t_start);
		पूर्ण
		t_start += PAGE_SIZE;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CACHE_L2
अटल अंतरभूत व्योम cpu_l2cache_op(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, अचिन्हित दीर्घ op)
अणु
	अगर (atl2c_base) अणु
		अचिन्हित दीर्घ p_start = __pa(start);
		अचिन्हित दीर्घ p_end = __pa(end);
		अचिन्हित दीर्घ cmd;
		अचिन्हित दीर्घ line_size;
		/* TODO Can Use PAGE Mode to optimize अगर range large than PAGE_SIZE */
		line_size = L2_CACHE_LINE_SIZE();
		p_start = p_start & (~(line_size - 1));
		p_end = (p_end + line_size - 1) & (~(line_size - 1));
		cmd =
		    (p_start & ~(line_size - 1)) | op |
		    CCTL_SINGLE_CMD;
		करो अणु
			L2_CMD_RDY();
			L2C_W_REG(L2_CCTL_CMD_OFF, cmd);
			cmd += line_size;
			p_start += line_size;
		पूर्ण जबतक (p_end > p_start);
		cmd = CCTL_CMD_L2_SYNC;
		L2_CMD_RDY();
		L2C_W_REG(L2_CCTL_CMD_OFF, cmd);
		L2_CMD_RDY();
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा cpu_l2cache_op(start,end,op) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
/*
 * DMA
 */
व्योम cpu_dma_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ line_size;
	अचिन्हित दीर्घ flags;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & (~(line_size - 1));
	end = (end + line_size - 1) & (~(line_size - 1));
	अगर (unlikely(start == end))
		वापस;

	local_irq_save(flags);
	cpu_dcache_wb_range(start, end);
	cpu_l2cache_op(start, end, CCTL_CMD_L2_PA_WB);
	__nds32__msync_all();
	local_irq_restore(flags);
पूर्ण

व्योम cpu_dma_inval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ line_size;
	अचिन्हित दीर्घ old_start = start;
	अचिन्हित दीर्घ old_end = end;
	अचिन्हित दीर्घ flags;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & (~(line_size - 1));
	end = (end + line_size - 1) & (~(line_size - 1));
	अगर (unlikely(start == end))
		वापस;
	local_irq_save(flags);
	अगर (start != old_start) अणु
		cpu_dcache_wbinval_range(start, start + line_size);
		cpu_l2cache_op(start, start + line_size, CCTL_CMD_L2_PA_WBINVAL);
	पूर्ण
	अगर (end != old_end) अणु
		cpu_dcache_wbinval_range(end - line_size, end);
		cpu_l2cache_op(end - line_size, end, CCTL_CMD_L2_PA_WBINVAL);
	पूर्ण
	cpu_dcache_inval_range(start, end);
	cpu_l2cache_op(start, end, CCTL_CMD_L2_PA_INVAL);
	__nds32__msync_all();
	local_irq_restore(flags);

पूर्ण

व्योम cpu_dma_wbinval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ line_size;
	अचिन्हित दीर्घ flags;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & (~(line_size - 1));
	end = (end + line_size - 1) & (~(line_size - 1));
	अगर (unlikely(start == end))
		वापस;

	local_irq_save(flags);
	cpu_dcache_wbinval_range(start, end);
	cpu_l2cache_op(start, end, CCTL_CMD_L2_PA_WBINVAL);
	__nds32__msync_all();
	local_irq_restore(flags);
पूर्ण

व्योम cpu_proc_init(व्योम)
अणु
पूर्ण

व्योम cpu_proc_fin(व्योम)
अणु
पूर्ण

व्योम cpu_करो_idle(व्योम)
अणु
	__nds32__standby_no_wake_grant();
पूर्ण

व्योम cpu_reset(अचिन्हित दीर्घ reset)
अणु
	u32 पंचांगp;
	GIE_DISABLE();
	पंचांगp = __nds32__mfsr(NDS32_SR_CACHE_CTL);
	पंचांगp &= ~(CACHE_CTL_mskIC_EN | CACHE_CTL_mskDC_EN);
	__nds32__mtsr_isb(पंचांगp, NDS32_SR_CACHE_CTL);
	cpu_dcache_wbinval_all();
	cpu_icache_inval_all();

	__यंत्र__ __अस्थिर__("jr.toff %0\n\t"::"r"(reset));
पूर्ण

व्योम cpu_चयन_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ cid;
	cid = __nds32__mfsr(NDS32_SR_TLB_MISC);
	cid = (cid & ~TLB_MISC_mskCID) | mm->context.id;
	__nds32__mtsr_dsb(cid, NDS32_SR_TLB_MISC);
	__nds32__mtsr_isb(__pa(mm->pgd), NDS32_SR_L1_PPTB);
पूर्ण
