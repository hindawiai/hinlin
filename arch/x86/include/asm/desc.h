<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_DESC_H
#घोषणा _ASM_X86_DESC_H

#समावेश <यंत्र/desc_defs.h>
#समावेश <यंत्र/ldt.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/irq_vectors.h>
#समावेश <यंत्र/cpu_entry_area.h>

#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>

अटल अंतरभूत व्योम fill_ldt(काष्ठा desc_काष्ठा *desc, स्थिर काष्ठा user_desc *info)
अणु
	desc->limit0		= info->limit & 0x0ffff;

	desc->base0		= (info->base_addr & 0x0000ffff);
	desc->base1		= (info->base_addr & 0x00ff0000) >> 16;

	desc->type		= (info->पढ़ो_exec_only ^ 1) << 1;
	desc->type	       |= info->contents << 2;
	/* Set the ACCESS bit so it can be mapped RO */
	desc->type	       |= 1;

	desc->s			= 1;
	desc->dpl		= 0x3;
	desc->p			= info->seg_not_present ^ 1;
	desc->limit1		= (info->limit & 0xf0000) >> 16;
	desc->avl		= info->useable;
	desc->d			= info->seg_32bit;
	desc->g			= info->limit_in_pages;

	desc->base2		= (info->base_addr & 0xff000000) >> 24;
	/*
	 * Don't allow setting of the lm bit. It would confuse
	 * user_64bit_mode and would get overridden by sysret anyway.
	 */
	desc->l			= 0;
पूर्ण

काष्ठा gdt_page अणु
	काष्ठा desc_काष्ठा gdt[GDT_ENTRIES];
पूर्ण __attribute__((aligned(PAGE_SIZE)));

DECLARE_PER_CPU_PAGE_ALIGNED(काष्ठा gdt_page, gdt_page);

/* Provide the original GDT */
अटल अंतरभूत काष्ठा desc_काष्ठा *get_cpu_gdt_rw(अचिन्हित पूर्णांक cpu)
अणु
	वापस per_cpu(gdt_page, cpu).gdt;
पूर्ण

/* Provide the current original GDT */
अटल अंतरभूत काष्ठा desc_काष्ठा *get_current_gdt_rw(व्योम)
अणु
	वापस this_cpu_ptr(&gdt_page)->gdt;
पूर्ण

/* Provide the fixmap address of the remapped GDT */
अटल अंतरभूत काष्ठा desc_काष्ठा *get_cpu_gdt_ro(पूर्णांक cpu)
अणु
	वापस (काष्ठा desc_काष्ठा *)&get_cpu_entry_area(cpu)->gdt;
पूर्ण

/* Provide the current पढ़ो-only GDT */
अटल अंतरभूत काष्ठा desc_काष्ठा *get_current_gdt_ro(व्योम)
अणु
	वापस get_cpu_gdt_ro(smp_processor_id());
पूर्ण

/* Provide the physical address of the GDT page. */
अटल अंतरभूत phys_addr_t get_cpu_gdt_paddr(अचिन्हित पूर्णांक cpu)
अणु
	वापस per_cpu_ptr_to_phys(get_cpu_gdt_rw(cpu));
पूर्ण

अटल अंतरभूत व्योम pack_gate(gate_desc *gate, अचिन्हित type, अचिन्हित दीर्घ func,
			     अचिन्हित dpl, अचिन्हित ist, अचिन्हित seg)
अणु
	gate->offset_low	= (u16) func;
	gate->bits.p		= 1;
	gate->bits.dpl		= dpl;
	gate->bits.zero		= 0;
	gate->bits.type		= type;
	gate->offset_middle	= (u16) (func >> 16);
#अगर_घोषित CONFIG_X86_64
	gate->segment		= __KERNEL_CS;
	gate->bits.ist		= ist;
	gate->reserved		= 0;
	gate->offset_high	= (u32) (func >> 32);
#अन्यथा
	gate->segment		= seg;
	gate->bits.ist		= 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक desc_empty(स्थिर व्योम *ptr)
अणु
	स्थिर u32 *desc = ptr;

	वापस !(desc[0] | desc[1]);
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा
#घोषणा load_TR_desc()				native_load_tr_desc()
#घोषणा load_gdt(dtr)				native_load_gdt(dtr)
#घोषणा load_idt(dtr)				native_load_idt(dtr)
#घोषणा load_tr(tr)				यंत्र अस्थिर("ltr %0"::"m" (tr))
#घोषणा load_ldt(ldt)				यंत्र अस्थिर("lldt %0"::"m" (ldt))

#घोषणा store_gdt(dtr)				native_store_gdt(dtr)
#घोषणा store_tr(tr)				(tr = native_store_tr())

#घोषणा load_TLS(t, cpu)			native_load_tls(t, cpu)
#घोषणा set_ldt					native_set_ldt

#घोषणा ग_लिखो_ldt_entry(dt, entry, desc)	native_ग_लिखो_ldt_entry(dt, entry, desc)
#घोषणा ग_लिखो_gdt_entry(dt, entry, desc, type)	native_ग_लिखो_gdt_entry(dt, entry, desc, type)
#घोषणा ग_लिखो_idt_entry(dt, entry, g)		native_ग_लिखो_idt_entry(dt, entry, g)

अटल अंतरभूत व्योम paravirt_alloc_ldt(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries)
अणु
पूर्ण

अटल अंतरभूत व्योम paravirt_मुक्त_ldt(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_PARAVIRT_XXL */

#घोषणा store_ldt(ldt) यंत्र("sldt %0" : "=m"(ldt))

अटल अंतरभूत व्योम native_ग_लिखो_idt_entry(gate_desc *idt, पूर्णांक entry, स्थिर gate_desc *gate)
अणु
	स_नकल(&idt[entry], gate, माप(*gate));
पूर्ण

अटल अंतरभूत व्योम native_ग_लिखो_ldt_entry(काष्ठा desc_काष्ठा *ldt, पूर्णांक entry, स्थिर व्योम *desc)
अणु
	स_नकल(&ldt[entry], desc, 8);
पूर्ण

अटल अंतरभूत व्योम
native_ग_लिखो_gdt_entry(काष्ठा desc_काष्ठा *gdt, पूर्णांक entry, स्थिर व्योम *desc, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक size;

	चयन (type) अणु
	हाल DESC_TSS:	size = माप(tss_desc);	अवरोध;
	हाल DESC_LDT:	size = माप(ldt_desc);	अवरोध;
	शेष:	size = माप(*gdt);		अवरोध;
	पूर्ण

	स_नकल(&gdt[entry], desc, size);
पूर्ण

अटल अंतरभूत व्योम set_tssldt_descriptor(व्योम *d, अचिन्हित दीर्घ addr,
					 अचिन्हित type, अचिन्हित size)
अणु
	काष्ठा ldttss_desc *desc = d;

	स_रखो(desc, 0, माप(*desc));

	desc->limit0		= (u16) size;
	desc->base0		= (u16) addr;
	desc->base1		= (addr >> 16) & 0xFF;
	desc->type		= type;
	desc->p			= 1;
	desc->limit1		= (size >> 16) & 0xF;
	desc->base2		= (addr >> 24) & 0xFF;
#अगर_घोषित CONFIG_X86_64
	desc->base3		= (u32) (addr >> 32);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __set_tss_desc(अचिन्हित cpu, अचिन्हित पूर्णांक entry, काष्ठा x86_hw_tss *addr)
अणु
	काष्ठा desc_काष्ठा *d = get_cpu_gdt_rw(cpu);
	tss_desc tss;

	set_tssldt_descriptor(&tss, (अचिन्हित दीर्घ)addr, DESC_TSS,
			      __KERNEL_TSS_LIMIT);
	ग_लिखो_gdt_entry(d, entry, &tss, DESC_TSS);
पूर्ण

#घोषणा set_tss_desc(cpu, addr) __set_tss_desc(cpu, GDT_ENTRY_TSS, addr)

अटल अंतरभूत व्योम native_set_ldt(स्थिर व्योम *addr, अचिन्हित पूर्णांक entries)
अणु
	अगर (likely(entries == 0))
		यंत्र अस्थिर("lldt %w0"::"q" (0));
	अन्यथा अणु
		अचिन्हित cpu = smp_processor_id();
		ldt_desc ldt;

		set_tssldt_descriptor(&ldt, (अचिन्हित दीर्घ)addr, DESC_LDT,
				      entries * LDT_ENTRY_SIZE - 1);
		ग_लिखो_gdt_entry(get_cpu_gdt_rw(cpu), GDT_ENTRY_LDT,
				&ldt, DESC_LDT);
		यंत्र अस्थिर("lldt %w0"::"q" (GDT_ENTRY_LDT*8));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम native_load_gdt(स्थिर काष्ठा desc_ptr *dtr)
अणु
	यंत्र अस्थिर("lgdt %0"::"m" (*dtr));
पूर्ण

अटल __always_अंतरभूत व्योम native_load_idt(स्थिर काष्ठा desc_ptr *dtr)
अणु
	यंत्र अस्थिर("lidt %0"::"m" (*dtr));
पूर्ण

अटल अंतरभूत व्योम native_store_gdt(काष्ठा desc_ptr *dtr)
अणु
	यंत्र अस्थिर("sgdt %0":"=m" (*dtr));
पूर्ण

अटल अंतरभूत व्योम store_idt(काष्ठा desc_ptr *dtr)
अणु
	यंत्र अस्थिर("sidt %0":"=m" (*dtr));
पूर्ण

/*
 * The LTR inकाष्ठाion marks the TSS GDT entry as busy. On 64-bit, the GDT is
 * a पढ़ो-only remapping. To prevent a page fault, the GDT is चयनed to the
 * original ग_लिखोable version when needed.
 */
#अगर_घोषित CONFIG_X86_64
अटल अंतरभूत व्योम native_load_tr_desc(व्योम)
अणु
	काष्ठा desc_ptr gdt;
	पूर्णांक cpu = raw_smp_processor_id();
	bool restore = 0;
	काष्ठा desc_काष्ठा *fixmap_gdt;

	native_store_gdt(&gdt);
	fixmap_gdt = get_cpu_gdt_ro(cpu);

	/*
	 * If the current GDT is the पढ़ो-only fixmap, swap to the original
	 * ग_लिखोable version. Swap back at the end.
	 */
	अगर (gdt.address == (अचिन्हित दीर्घ)fixmap_gdt) अणु
		load_direct_gdt(cpu);
		restore = 1;
	पूर्ण
	यंत्र अस्थिर("ltr %w0"::"q" (GDT_ENTRY_TSS*8));
	अगर (restore)
		load_fixmap_gdt(cpu);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम native_load_tr_desc(व्योम)
अणु
	यंत्र अस्थिर("ltr %w0"::"q" (GDT_ENTRY_TSS*8));
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ native_store_tr(व्योम)
अणु
	अचिन्हित दीर्घ tr;

	यंत्र अस्थिर("str %0":"=r" (tr));

	वापस tr;
पूर्ण

अटल अंतरभूत व्योम native_load_tls(काष्ठा thपढ़ो_काष्ठा *t, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा desc_काष्ठा *gdt = get_cpu_gdt_rw(cpu);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < GDT_ENTRY_TLS_ENTRIES; i++)
		gdt[GDT_ENTRY_TLS_MIN + i] = t->tls_array[i];
पूर्ण

DECLARE_PER_CPU(bool, __tss_limit_invalid);

अटल अंतरभूत व्योम क्रमce_reload_TR(व्योम)
अणु
	काष्ठा desc_काष्ठा *d = get_current_gdt_rw();
	tss_desc tss;

	स_नकल(&tss, &d[GDT_ENTRY_TSS], माप(tss_desc));

	/*
	 * LTR requires an available TSS, and the TSS is currently
	 * busy.  Make it be available so that LTR will work.
	 */
	tss.type = DESC_TSS;
	ग_लिखो_gdt_entry(d, GDT_ENTRY_TSS, &tss, DESC_TSS);

	load_TR_desc();
	this_cpu_ग_लिखो(__tss_limit_invalid, false);
पूर्ण

/*
 * Call this अगर you need the TSS limit to be correct, which should be the हाल
 * अगर and only अगर you have TIF_IO_BITMAP set or you're चयनing to a task
 * with TIF_IO_BITMAP set.
 */
अटल अंतरभूत व्योम refresh_tss_limit(व्योम)
अणु
	DEBUG_LOCKS_WARN_ON(preemptible());

	अगर (unlikely(this_cpu_पढ़ो(__tss_limit_invalid)))
		क्रमce_reload_TR();
पूर्ण

/*
 * If you करो something evil that corrupts the cached TSS limit (I'm looking
 * at you, VMX निकासs), call this function.
 *
 * The optimization here is that the TSS limit only matters क्रम Linux अगर the
 * IO biपंचांगap is in use.  If the TSS limit माला_लो क्रमced to its minimum value,
 * everything works except that IO biपंचांगap will be ignored and all CPL 3 IO
 * inकाष्ठाions will #GP, which is exactly what we want क्रम normal tasks.
 */
अटल अंतरभूत व्योम invalidate_tss_limit(व्योम)
अणु
	DEBUG_LOCKS_WARN_ON(preemptible());

	अगर (unlikely(test_thपढ़ो_flag(TIF_IO_BITMAP)))
		क्रमce_reload_TR();
	अन्यथा
		this_cpu_ग_लिखो(__tss_limit_invalid, true);
पूर्ण

/* This पूर्णांकentionally ignores lm, since 32-bit apps करोn't have that field. */
#घोषणा LDT_empty(info)					\
	((info)->base_addr		== 0	&&	\
	 (info)->limit			== 0	&&	\
	 (info)->contents		== 0	&&	\
	 (info)->पढ़ो_exec_only		== 1	&&	\
	 (info)->seg_32bit		== 0	&&	\
	 (info)->limit_in_pages		== 0	&&	\
	 (info)->seg_not_present	== 1	&&	\
	 (info)->useable		== 0)

/* Lots of programs expect an all-zero user_desc to mean "no segment at all". */
अटल अंतरभूत bool LDT_zero(स्थिर काष्ठा user_desc *info)
अणु
	वापस (info->base_addr		== 0 &&
		info->limit		== 0 &&
		info->contents		== 0 &&
		info->पढ़ो_exec_only	== 0 &&
		info->seg_32bit		== 0 &&
		info->limit_in_pages	== 0 &&
		info->seg_not_present	== 0 &&
		info->useable		== 0);
पूर्ण

अटल अंतरभूत व्योम clear_LDT(व्योम)
अणु
	set_ldt(शून्य, 0);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_desc_base(स्थिर काष्ठा desc_काष्ठा *desc)
अणु
	वापस (अचिन्हित)(desc->base0 | ((desc->base1) << 16) | ((desc->base2) << 24));
पूर्ण

अटल अंतरभूत व्योम set_desc_base(काष्ठा desc_काष्ठा *desc, अचिन्हित दीर्घ base)
अणु
	desc->base0 = base & 0xffff;
	desc->base1 = (base >> 16) & 0xff;
	desc->base2 = (base >> 24) & 0xff;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_desc_limit(स्थिर काष्ठा desc_काष्ठा *desc)
अणु
	वापस desc->limit0 | (desc->limit1 << 16);
पूर्ण

अटल अंतरभूत व्योम set_desc_limit(काष्ठा desc_काष्ठा *desc, अचिन्हित दीर्घ limit)
अणु
	desc->limit0 = limit & 0xffff;
	desc->limit1 = (limit >> 16) & 0xf;
पूर्ण

व्योम alloc_पूर्णांकr_gate(अचिन्हित पूर्णांक n, स्थिर व्योम *addr);

अटल अंतरभूत व्योम init_idt_data(काष्ठा idt_data *data, अचिन्हित पूर्णांक n,
				 स्थिर व्योम *addr)
अणु
	BUG_ON(n > 0xFF);

	स_रखो(data, 0, माप(*data));
	data->vector	= n;
	data->addr	= addr;
	data->segment	= __KERNEL_CS;
	data->bits.type	= GATE_INTERRUPT;
	data->bits.p	= 1;
पूर्ण

अटल अंतरभूत व्योम idt_init_desc(gate_desc *gate, स्थिर काष्ठा idt_data *d)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) d->addr;

	gate->offset_low	= (u16) addr;
	gate->segment		= (u16) d->segment;
	gate->bits		= d->bits;
	gate->offset_middle	= (u16) (addr >> 16);
#अगर_घोषित CONFIG_X86_64
	gate->offset_high	= (u32) (addr >> 32);
	gate->reserved		= 0;
#पूर्ण_अगर
पूर्ण

बाह्य अचिन्हित दीर्घ प्रणाली_vectors[];

बाह्य व्योम load_current_idt(व्योम);
बाह्य व्योम idt_setup_early_handler(व्योम);
बाह्य व्योम idt_setup_early_traps(व्योम);
बाह्य व्योम idt_setup_traps(व्योम);
बाह्य व्योम idt_setup_apic_and_irq_gates(व्योम);
बाह्य bool idt_is_f00f_address(अचिन्हित दीर्घ address);

#अगर_घोषित CONFIG_X86_64
बाह्य व्योम idt_setup_early_pf(व्योम);
बाह्य व्योम idt_setup_ist_traps(व्योम);
#अन्यथा
अटल अंतरभूत व्योम idt_setup_early_pf(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम idt_setup_ist_traps(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम idt_invalidate(व्योम *addr);

#पूर्ण_अगर /* _ASM_X86_DESC_H */
