<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM xen

#अगर !defined(_TRACE_XEN_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_XEN_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/paravirt_types.h>
#समावेश <यंत्र/xen/trace_types.h>

काष्ठा multicall_entry;

/* Multicalls */
DECLARE_EVENT_CLASS(xen_mc__batch,
	    TP_PROTO(क्रमागत paravirt_lazy_mode mode),
	    TP_ARGS(mode),
	    TP_STRUCT__entry(
		    __field(क्रमागत paravirt_lazy_mode, mode)
		    ),
	    TP_fast_assign(__entry->mode = mode),
	    TP_prपूर्णांकk("start batch LAZY_%s",
		      (__entry->mode == PARAVIRT_LAZY_MMU) ? "MMU" :
		      (__entry->mode == PARAVIRT_LAZY_CPU) ? "CPU" : "NONE")
	);
#घोषणा DEFINE_XEN_MC_BATCH(name)			\
	DEFINE_EVENT(xen_mc__batch, name,		\
		TP_PROTO(क्रमागत paravirt_lazy_mode mode),	\
		     TP_ARGS(mode))

DEFINE_XEN_MC_BATCH(xen_mc_batch);
DEFINE_XEN_MC_BATCH(xen_mc_issue);

TRACE_DEFINE_SIZखातापूर्ण(uदीर्घ);

TRACE_EVENT(xen_mc_entry,
	    TP_PROTO(काष्ठा multicall_entry *mc, अचिन्हित nargs),
	    TP_ARGS(mc, nargs),
	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, op)
		    __field(अचिन्हित पूर्णांक, nargs)
		    __array(अचिन्हित दीर्घ, args, 6)
		    ),
	    TP_fast_assign(__entry->op = mc->op;
			   __entry->nargs = nargs;
			   स_नकल(__entry->args, mc->args, माप(uदीर्घ) * nargs);
			   स_रखो(__entry->args + nargs, 0, माप(uदीर्घ) * (6 - nargs));
		    ),
	    TP_prपूर्णांकk("op %u%s args [%lx, %lx, %lx, %lx, %lx, %lx]",
		      __entry->op, xen_hypercall_name(__entry->op),
		      __entry->args[0], __entry->args[1], __entry->args[2],
		      __entry->args[3], __entry->args[4], __entry->args[5])
	);

TRACE_EVENT(xen_mc_entry_alloc,
	    TP_PROTO(माप_प्रकार args),
	    TP_ARGS(args),
	    TP_STRUCT__entry(
		    __field(माप_प्रकार, args)
		    ),
	    TP_fast_assign(__entry->args = args),
	    TP_prपूर्णांकk("alloc entry %zu arg bytes", __entry->args)
	);

TRACE_EVENT(xen_mc_callback,
	    TP_PROTO(xen_mc_callback_fn_t fn, व्योम *data),
	    TP_ARGS(fn, data),
	    TP_STRUCT__entry(
		    /*
		     * Use field_काष्ठा to aव्योम is_चिन्हित_type()
		     * comparison of a function poपूर्णांकer.
		     */
		    __field_काष्ठा(xen_mc_callback_fn_t, fn)
		    __field(व्योम *, data)
		    ),
	    TP_fast_assign(
		    __entry->fn = fn;
		    __entry->data = data;
		    ),
	    TP_prपूर्णांकk("callback %ps, data %p",
		      __entry->fn, __entry->data)
	);

TRACE_EVENT(xen_mc_flush_reason,
	    TP_PROTO(क्रमागत xen_mc_flush_reason reason),
	    TP_ARGS(reason),
	    TP_STRUCT__entry(
		    __field(क्रमागत xen_mc_flush_reason, reason)
		    ),
	    TP_fast_assign(__entry->reason = reason),
	    TP_prपूर्णांकk("flush reason %s",
		      (__entry->reason == XEN_MC_FL_NONE) ? "NONE" :
		      (__entry->reason == XEN_MC_FL_BATCH) ? "BATCH" :
		      (__entry->reason == XEN_MC_FL_ARGS) ? "ARGS" :
		      (__entry->reason == XEN_MC_FL_CALLBACK) ? "CALLBACK" : "??")
	);

TRACE_EVENT(xen_mc_flush,
	    TP_PROTO(अचिन्हित mcidx, अचिन्हित argidx, अचिन्हित cbidx),
	    TP_ARGS(mcidx, argidx, cbidx),
	    TP_STRUCT__entry(
		    __field(अचिन्हित, mcidx)
		    __field(अचिन्हित, argidx)
		    __field(अचिन्हित, cbidx)
		    ),
	    TP_fast_assign(__entry->mcidx = mcidx;
			   __entry->argidx = argidx;
			   __entry->cbidx = cbidx),
	    TP_prपूर्णांकk("flushing %u hypercalls, %u arg bytes, %u callbacks",
		      __entry->mcidx, __entry->argidx, __entry->cbidx)
	);

TRACE_EVENT(xen_mc_extend_args,
	    TP_PROTO(अचिन्हित दीर्घ op, माप_प्रकार args, क्रमागत xen_mc_extend_args res),
	    TP_ARGS(op, args, res),
	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, op)
		    __field(माप_प्रकार, args)
		    __field(क्रमागत xen_mc_extend_args, res)
		    ),
	    TP_fast_assign(__entry->op = op;
			   __entry->args = args;
			   __entry->res = res),
	    TP_prपूर्णांकk("extending op %u%s by %zu bytes res %s",
		      __entry->op, xen_hypercall_name(__entry->op),
		      __entry->args,
		      __entry->res == XEN_MC_XE_OK ? "OK" :
		      __entry->res == XEN_MC_XE_BAD_OP ? "BAD_OP" :
		      __entry->res == XEN_MC_XE_NO_SPACE ? "NO_SPACE" : "???")
	);

TRACE_DEFINE_SIZखातापूर्ण(pteval_t);
/* mmu */
DECLARE_EVENT_CLASS(xen_mmu__set_pte,
	    TP_PROTO(pte_t *ptep, pte_t pteval),
	    TP_ARGS(ptep, pteval),
	    TP_STRUCT__entry(
		    __field(pte_t *, ptep)
		    __field(pteval_t, pteval)
		    ),
	    TP_fast_assign(__entry->ptep = ptep;
			   __entry->pteval = pteval.pte),
	    TP_prपूर्णांकk("ptep %p pteval %0*llx (raw %0*llx)",
		      __entry->ptep,
		      (पूर्णांक)माप(pteval_t) * 2, (अचिन्हित दीर्घ दीर्घ)pte_val(native_make_pte(__entry->pteval)),
		      (पूर्णांक)माप(pteval_t) * 2, (अचिन्हित दीर्घ दीर्घ)__entry->pteval)
	);

#घोषणा DEFINE_XEN_MMU_SET_PTE(name)				\
	DEFINE_EVENT(xen_mmu__set_pte, name,			\
		     TP_PROTO(pte_t *ptep, pte_t pteval),	\
		     TP_ARGS(ptep, pteval))

DEFINE_XEN_MMU_SET_PTE(xen_mmu_set_pte);

TRACE_DEFINE_SIZखातापूर्ण(pmdval_t);

TRACE_EVENT(xen_mmu_set_pmd,
	    TP_PROTO(pmd_t *pmdp, pmd_t pmdval),
	    TP_ARGS(pmdp, pmdval),
	    TP_STRUCT__entry(
		    __field(pmd_t *, pmdp)
		    __field(pmdval_t, pmdval)
		    ),
	    TP_fast_assign(__entry->pmdp = pmdp;
			   __entry->pmdval = pmdval.pmd),
	    TP_prपूर्णांकk("pmdp %p pmdval %0*llx (raw %0*llx)",
		      __entry->pmdp,
		      (पूर्णांक)माप(pmdval_t) * 2, (अचिन्हित दीर्घ दीर्घ)pmd_val(native_make_pmd(__entry->pmdval)),
		      (पूर्णांक)माप(pmdval_t) * 2, (अचिन्हित दीर्घ दीर्घ)__entry->pmdval)
	);

#अगर_घोषित CONFIG_X86_PAE
DEFINE_XEN_MMU_SET_PTE(xen_mmu_set_pte_atomic);

TRACE_EVENT(xen_mmu_pte_clear,
	    TP_PROTO(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep),
	    TP_ARGS(mm, addr, ptep),
	    TP_STRUCT__entry(
		    __field(काष्ठा mm_काष्ठा *, mm)
		    __field(अचिन्हित दीर्घ, addr)
		    __field(pte_t *, ptep)
		    ),
	    TP_fast_assign(__entry->mm = mm;
			   __entry->addr = addr;
			   __entry->ptep = ptep),
	    TP_prपूर्णांकk("mm %p addr %lx ptep %p",
		      __entry->mm, __entry->addr, __entry->ptep)
	);

TRACE_EVENT(xen_mmu_pmd_clear,
	    TP_PROTO(pmd_t *pmdp),
	    TP_ARGS(pmdp),
	    TP_STRUCT__entry(
		    __field(pmd_t *, pmdp)
		    ),
	    TP_fast_assign(__entry->pmdp = pmdp),
	    TP_prपूर्णांकk("pmdp %p", __entry->pmdp)
	);
#पूर्ण_अगर

#अगर CONFIG_PGTABLE_LEVELS >= 4

TRACE_DEFINE_SIZखातापूर्ण(pudval_t);

TRACE_EVENT(xen_mmu_set_pud,
	    TP_PROTO(pud_t *pudp, pud_t pudval),
	    TP_ARGS(pudp, pudval),
	    TP_STRUCT__entry(
		    __field(pud_t *, pudp)
		    __field(pudval_t, pudval)
		    ),
	    TP_fast_assign(__entry->pudp = pudp;
			   __entry->pudval = native_pud_val(pudval)),
	    TP_prपूर्णांकk("pudp %p pudval %0*llx (raw %0*llx)",
		      __entry->pudp,
		      (पूर्णांक)माप(pudval_t) * 2, (अचिन्हित दीर्घ दीर्घ)pud_val(native_make_pud(__entry->pudval)),
		      (पूर्णांक)माप(pudval_t) * 2, (अचिन्हित दीर्घ दीर्घ)__entry->pudval)
	);

TRACE_DEFINE_SIZखातापूर्ण(p4dval_t);

TRACE_EVENT(xen_mmu_set_p4d,
	    TP_PROTO(p4d_t *p4dp, p4d_t *user_p4dp, p4d_t p4dval),
	    TP_ARGS(p4dp, user_p4dp, p4dval),
	    TP_STRUCT__entry(
		    __field(p4d_t *, p4dp)
		    __field(p4d_t *, user_p4dp)
		    __field(p4dval_t, p4dval)
		    ),
	    TP_fast_assign(__entry->p4dp = p4dp;
			   __entry->user_p4dp = user_p4dp;
			   __entry->p4dval = p4d_val(p4dval)),
	    TP_prपूर्णांकk("p4dp %p user_p4dp %p p4dval %0*llx (raw %0*llx)",
		      __entry->p4dp, __entry->user_p4dp,
		      (पूर्णांक)माप(p4dval_t) * 2, (अचिन्हित दीर्घ दीर्घ)pgd_val(native_make_pgd(__entry->p4dval)),
		      (पूर्णांक)माप(p4dval_t) * 2, (अचिन्हित दीर्घ दीर्घ)__entry->p4dval)
	);
#अन्यथा

TRACE_EVENT(xen_mmu_set_pud,
	    TP_PROTO(pud_t *pudp, pud_t pudval),
	    TP_ARGS(pudp, pudval),
	    TP_STRUCT__entry(
		    __field(pud_t *, pudp)
		    __field(pudval_t, pudval)
		    ),
	    TP_fast_assign(__entry->pudp = pudp;
			   __entry->pudval = native_pud_val(pudval)),
	    TP_prपूर्णांकk("pudp %p pudval %0*llx (raw %0*llx)",
		      __entry->pudp,
		      (पूर्णांक)माप(pudval_t) * 2, (अचिन्हित दीर्घ दीर्घ)pgd_val(native_make_pgd(__entry->pudval)),
		      (पूर्णांक)माप(pudval_t) * 2, (अचिन्हित दीर्घ दीर्घ)__entry->pudval)
	);

#पूर्ण_अगर

DECLARE_EVENT_CLASS(xen_mmu_ptep_modअगरy_prot,
	    TP_PROTO(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t pteval),
	    TP_ARGS(mm, addr, ptep, pteval),
	    TP_STRUCT__entry(
		    __field(काष्ठा mm_काष्ठा *, mm)
		    __field(अचिन्हित दीर्घ, addr)
		    __field(pte_t *, ptep)
		    __field(pteval_t, pteval)
		    ),
	    TP_fast_assign(__entry->mm = mm;
			   __entry->addr = addr;
			   __entry->ptep = ptep;
			   __entry->pteval = pteval.pte),
	    TP_prपूर्णांकk("mm %p addr %lx ptep %p pteval %0*llx (raw %0*llx)",
		      __entry->mm, __entry->addr, __entry->ptep,
		      (पूर्णांक)माप(pteval_t) * 2, (अचिन्हित दीर्घ दीर्घ)pte_val(native_make_pte(__entry->pteval)),
		      (पूर्णांक)माप(pteval_t) * 2, (अचिन्हित दीर्घ दीर्घ)__entry->pteval)
	);
#घोषणा DEFINE_XEN_MMU_PTEP_MODIFY_PROT(name)				\
	DEFINE_EVENT(xen_mmu_ptep_modअगरy_prot, name,			\
		     TP_PROTO(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,	\
			      pte_t *ptep, pte_t pteval),		\
		     TP_ARGS(mm, addr, ptep, pteval))

DEFINE_XEN_MMU_PTEP_MODIFY_PROT(xen_mmu_ptep_modअगरy_prot_start);
DEFINE_XEN_MMU_PTEP_MODIFY_PROT(xen_mmu_ptep_modअगरy_prot_commit);

TRACE_EVENT(xen_mmu_alloc_ptpage,
	    TP_PROTO(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn, अचिन्हित level, bool pinned),
	    TP_ARGS(mm, pfn, level, pinned),
	    TP_STRUCT__entry(
		    __field(काष्ठा mm_काष्ठा *, mm)
		    __field(अचिन्हित दीर्घ, pfn)
		    __field(अचिन्हित, level)
		    __field(bool, pinned)
		    ),
	    TP_fast_assign(__entry->mm = mm;
			   __entry->pfn = pfn;
			   __entry->level = level;
			   __entry->pinned = pinned),
	    TP_prपूर्णांकk("mm %p  pfn %lx  level %d  %spinned",
		      __entry->mm, __entry->pfn, __entry->level,
		      __entry->pinned ? "" : "un")
	);

TRACE_EVENT(xen_mmu_release_ptpage,
	    TP_PROTO(अचिन्हित दीर्घ pfn, अचिन्हित level, bool pinned),
	    TP_ARGS(pfn, level, pinned),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, pfn)
		    __field(अचिन्हित, level)
		    __field(bool, pinned)
		    ),
	    TP_fast_assign(__entry->pfn = pfn;
			   __entry->level = level;
			   __entry->pinned = pinned),
	    TP_prपूर्णांकk("pfn %lx  level %d  %spinned",
		      __entry->pfn, __entry->level,
		      __entry->pinned ? "" : "un")
	);

DECLARE_EVENT_CLASS(xen_mmu_pgd,
	    TP_PROTO(काष्ठा mm_काष्ठा *mm, pgd_t *pgd),
	    TP_ARGS(mm, pgd),
	    TP_STRUCT__entry(
		    __field(काष्ठा mm_काष्ठा *, mm)
		    __field(pgd_t *, pgd)
		    ),
	    TP_fast_assign(__entry->mm = mm;
			   __entry->pgd = pgd),
	    TP_prपूर्णांकk("mm %p pgd %p", __entry->mm, __entry->pgd)
	);
#घोषणा DEFINE_XEN_MMU_PGD_EVENT(name)				\
	DEFINE_EVENT(xen_mmu_pgd, name,				\
		TP_PROTO(काष्ठा mm_काष्ठा *mm, pgd_t *pgd),	\
		     TP_ARGS(mm, pgd))

DEFINE_XEN_MMU_PGD_EVENT(xen_mmu_pgd_pin);
DEFINE_XEN_MMU_PGD_EVENT(xen_mmu_pgd_unpin);

TRACE_EVENT(xen_mmu_flush_tlb_one_user,
	    TP_PROTO(अचिन्हित दीर्घ addr),
	    TP_ARGS(addr),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, addr)
		    ),
	    TP_fast_assign(__entry->addr = addr),
	    TP_prपूर्णांकk("addr %lx", __entry->addr)
	);

TRACE_EVENT(xen_mmu_flush_tlb_multi,
	    TP_PROTO(स्थिर काष्ठा cpumask *cpus, काष्ठा mm_काष्ठा *mm,
		     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end),
	    TP_ARGS(cpus, mm, addr, end),
	    TP_STRUCT__entry(
		    __field(अचिन्हित, ncpus)
		    __field(काष्ठा mm_काष्ठा *, mm)
		    __field(अचिन्हित दीर्घ, addr)
		    __field(अचिन्हित दीर्घ, end)
		    ),
	    TP_fast_assign(__entry->ncpus = cpumask_weight(cpus);
			   __entry->mm = mm;
			   __entry->addr = addr,
			   __entry->end = end),
	    TP_prपूर्णांकk("ncpus %d mm %p addr %lx, end %lx",
		      __entry->ncpus, __entry->mm, __entry->addr, __entry->end)
	);

TRACE_EVENT(xen_mmu_ग_लिखो_cr3,
	    TP_PROTO(bool kernel, अचिन्हित दीर्घ cr3),
	    TP_ARGS(kernel, cr3),
	    TP_STRUCT__entry(
		    __field(bool, kernel)
		    __field(अचिन्हित दीर्घ, cr3)
		    ),
	    TP_fast_assign(__entry->kernel = kernel;
			   __entry->cr3 = cr3),
	    TP_prपूर्णांकk("%s cr3 %lx",
		      __entry->kernel ? "kernel" : "user", __entry->cr3)
	);


/* CPU */
TRACE_EVENT(xen_cpu_ग_लिखो_ldt_entry,
	    TP_PROTO(काष्ठा desc_काष्ठा *dt, पूर्णांक entrynum, u64 desc),
	    TP_ARGS(dt, entrynum, desc),
	    TP_STRUCT__entry(
		    __field(काष्ठा desc_काष्ठा *, dt)
		    __field(पूर्णांक, entrynum)
		    __field(u64, desc)
		    ),
	    TP_fast_assign(__entry->dt = dt;
			   __entry->entrynum = entrynum;
			   __entry->desc = desc;
		    ),
	    TP_prपूर्णांकk("dt %p  entrynum %d  entry %016llx",
		      __entry->dt, __entry->entrynum,
		      (अचिन्हित दीर्घ दीर्घ)__entry->desc)
	);

TRACE_EVENT(xen_cpu_ग_लिखो_idt_entry,
	    TP_PROTO(gate_desc *dt, पूर्णांक entrynum, स्थिर gate_desc *ent),
	    TP_ARGS(dt, entrynum, ent),
	    TP_STRUCT__entry(
		    __field(gate_desc *, dt)
		    __field(पूर्णांक, entrynum)
		    ),
	    TP_fast_assign(__entry->dt = dt;
			   __entry->entrynum = entrynum;
		    ),
	    TP_prपूर्णांकk("dt %p  entrynum %d",
		      __entry->dt, __entry->entrynum)
	);

TRACE_EVENT(xen_cpu_load_idt,
	    TP_PROTO(स्थिर काष्ठा desc_ptr *desc),
	    TP_ARGS(desc),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, addr)
		    ),
	    TP_fast_assign(__entry->addr = desc->address),
	    TP_prपूर्णांकk("addr %lx", __entry->addr)
	);

TRACE_EVENT(xen_cpu_ग_लिखो_gdt_entry,
	    TP_PROTO(काष्ठा desc_काष्ठा *dt, पूर्णांक entrynum, स्थिर व्योम *desc, पूर्णांक type),
	    TP_ARGS(dt, entrynum, desc, type),
	    TP_STRUCT__entry(
		    __field(u64, desc)
		    __field(काष्ठा desc_काष्ठा *, dt)
		    __field(पूर्णांक, entrynum)
		    __field(पूर्णांक, type)
		    ),
	    TP_fast_assign(__entry->dt = dt;
			   __entry->entrynum = entrynum;
			   __entry->desc = *(u64 *)desc;
			   __entry->type = type;
		    ),
	    TP_prपूर्णांकk("dt %p  entrynum %d  type %d  desc %016llx",
		      __entry->dt, __entry->entrynum, __entry->type,
		      (अचिन्हित दीर्घ दीर्घ)__entry->desc)
	);

TRACE_EVENT(xen_cpu_set_ldt,
	    TP_PROTO(स्थिर व्योम *addr, अचिन्हित entries),
	    TP_ARGS(addr, entries),
	    TP_STRUCT__entry(
		    __field(स्थिर व्योम *, addr)
		    __field(अचिन्हित, entries)
		    ),
	    TP_fast_assign(__entry->addr = addr;
			   __entry->entries = entries),
	    TP_prपूर्णांकk("addr %p  entries %u",
		      __entry->addr, __entry->entries)
	);


#पूर्ण_अगर /*  _TRACE_XEN_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
