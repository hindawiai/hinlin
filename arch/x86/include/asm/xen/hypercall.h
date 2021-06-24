<शैली गुरु>
/******************************************************************************
 * hypercall.h
 *
 * Linux-specअगरic hypervisor handling.
 *
 * Copyright (c) 2002-2004, K A Fraser
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित _ASM_X86_XEN_HYPERCALL_H
#घोषणा _ASM_X86_XEN_HYPERCALL_H

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/pgtable.h>

#समावेश <trace/events/xen.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/smap.h>
#समावेश <यंत्र/nospec-branch.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/sched.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>
#समावेश <xen/पूर्णांकerface/xen-mca.h>

काष्ठा xen_dm_op_buf;

/*
 * The hypercall यंत्रs have to meet several स्थिरraपूर्णांकs:
 * - Work on 32- and 64-bit.
 *    The two architectures put their arguments in dअगरferent sets of
 *    रेजिस्टरs.
 *
 * - Work around यंत्र syntax quirks
 *    It isn't possible to specअगरy one of the rNN रेजिस्टरs in a
 *    स्थिरraपूर्णांक, so we use explicit रेजिस्टर variables to get the
 *    args पूर्णांकo the right place.
 *
 * - Mark all रेजिस्टरs as potentially clobbered
 *    Even unused parameters can be clobbered by the hypervisor, so we
 *    need to make sure gcc knows it.
 *
 * - Aव्योम compiler bugs.
 *    This is the tricky part.  Because x86_32 has such a स्थिरrained
 *    रेजिस्टर set, gcc versions below 4.3 have trouble generating
 *    code when all the arg रेजिस्टरs and memory are trashed by the
 *    यंत्र.  There are syntactically simpler ways of achieving the
 *    semantics below, but they cause the compiler to crash.
 *
 *    The only combination I found which works is:
 *     - assign the __argX variables first
 *     - list all actually used parameters as "+r" (__argX)
 *     - clobber the rest
 *
 * The result certainly isn't pretty, and it really shows up cpp's
 * weakness as a macro language.  Sorry.  (But let's just give thanks
 * there aren't more than 5 arguments...)
 */

बाह्य काष्ठा अणु अक्षर _entry[32]; पूर्ण hypercall_page[];

#घोषणा __HYPERCALL		"call hypercall_page+%c[offset]"
#घोषणा __HYPERCALL_ENTRY(x)						\
	[offset] "i" (__HYPERVISOR_##x * माप(hypercall_page[0]))

#अगर_घोषित CONFIG_X86_32
#घोषणा __HYPERCALL_RETREG	"eax"
#घोषणा __HYPERCALL_ARG1REG	"ebx"
#घोषणा __HYPERCALL_ARG2REG	"ecx"
#घोषणा __HYPERCALL_ARG3REG	"edx"
#घोषणा __HYPERCALL_ARG4REG	"esi"
#घोषणा __HYPERCALL_ARG5REG	"edi"
#अन्यथा
#घोषणा __HYPERCALL_RETREG	"rax"
#घोषणा __HYPERCALL_ARG1REG	"rdi"
#घोषणा __HYPERCALL_ARG2REG	"rsi"
#घोषणा __HYPERCALL_ARG3REG	"rdx"
#घोषणा __HYPERCALL_ARG4REG	"r10"
#घोषणा __HYPERCALL_ARG5REG	"r8"
#पूर्ण_अगर

#घोषणा __HYPERCALL_DECLS						\
	रेजिस्टर अचिन्हित दीर्घ __res  यंत्र(__HYPERCALL_RETREG);		\
	रेजिस्टर अचिन्हित दीर्घ __arg1 यंत्र(__HYPERCALL_ARG1REG) = __arg1; \
	रेजिस्टर अचिन्हित दीर्घ __arg2 यंत्र(__HYPERCALL_ARG2REG) = __arg2; \
	रेजिस्टर अचिन्हित दीर्घ __arg3 यंत्र(__HYPERCALL_ARG3REG) = __arg3; \
	रेजिस्टर अचिन्हित दीर्घ __arg4 यंत्र(__HYPERCALL_ARG4REG) = __arg4; \
	रेजिस्टर अचिन्हित दीर्घ __arg5 यंत्र(__HYPERCALL_ARG5REG) = __arg5;

#घोषणा __HYPERCALL_0PARAM	"=r" (__res), ASM_CALL_CONSTRAINT
#घोषणा __HYPERCALL_1PARAM	__HYPERCALL_0PARAM, "+r" (__arg1)
#घोषणा __HYPERCALL_2PARAM	__HYPERCALL_1PARAM, "+r" (__arg2)
#घोषणा __HYPERCALL_3PARAM	__HYPERCALL_2PARAM, "+r" (__arg3)
#घोषणा __HYPERCALL_4PARAM	__HYPERCALL_3PARAM, "+r" (__arg4)
#घोषणा __HYPERCALL_5PARAM	__HYPERCALL_4PARAM, "+r" (__arg5)

#घोषणा __HYPERCALL_0ARG()
#घोषणा __HYPERCALL_1ARG(a1)						\
	__HYPERCALL_0ARG()		__arg1 = (अचिन्हित दीर्घ)(a1);
#घोषणा __HYPERCALL_2ARG(a1,a2)						\
	__HYPERCALL_1ARG(a1)		__arg2 = (अचिन्हित दीर्घ)(a2);
#घोषणा __HYPERCALL_3ARG(a1,a2,a3)					\
	__HYPERCALL_2ARG(a1,a2)		__arg3 = (अचिन्हित दीर्घ)(a3);
#घोषणा __HYPERCALL_4ARG(a1,a2,a3,a4)					\
	__HYPERCALL_3ARG(a1,a2,a3)	__arg4 = (अचिन्हित दीर्घ)(a4);
#घोषणा __HYPERCALL_5ARG(a1,a2,a3,a4,a5)				\
	__HYPERCALL_4ARG(a1,a2,a3,a4)	__arg5 = (अचिन्हित दीर्घ)(a5);

#घोषणा __HYPERCALL_CLOBBER5	"memory"
#घोषणा __HYPERCALL_CLOBBER4	__HYPERCALL_CLOBBER5, __HYPERCALL_ARG5REG
#घोषणा __HYPERCALL_CLOBBER3	__HYPERCALL_CLOBBER4, __HYPERCALL_ARG4REG
#घोषणा __HYPERCALL_CLOBBER2	__HYPERCALL_CLOBBER3, __HYPERCALL_ARG3REG
#घोषणा __HYPERCALL_CLOBBER1	__HYPERCALL_CLOBBER2, __HYPERCALL_ARG2REG
#घोषणा __HYPERCALL_CLOBBER0	__HYPERCALL_CLOBBER1, __HYPERCALL_ARG1REG

#घोषणा _hypercall0(type, name)						\
(अणु									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_0ARG();						\
	यंत्र अस्थिर (__HYPERCALL					\
		      : __HYPERCALL_0PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER0);				\
	(type)__res;							\
पूर्ण)

#घोषणा _hypercall1(type, name, a1)					\
(अणु									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_1ARG(a1);						\
	यंत्र अस्थिर (__HYPERCALL					\
		      : __HYPERCALL_1PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER1);				\
	(type)__res;							\
पूर्ण)

#घोषणा _hypercall2(type, name, a1, a2)					\
(अणु									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_2ARG(a1, a2);					\
	यंत्र अस्थिर (__HYPERCALL					\
		      : __HYPERCALL_2PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER2);				\
	(type)__res;							\
पूर्ण)

#घोषणा _hypercall3(type, name, a1, a2, a3)				\
(अणु									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_3ARG(a1, a2, a3);					\
	यंत्र अस्थिर (__HYPERCALL					\
		      : __HYPERCALL_3PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER3);				\
	(type)__res;							\
पूर्ण)

#घोषणा _hypercall4(type, name, a1, a2, a3, a4)				\
(अणु									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_4ARG(a1, a2, a3, a4);				\
	यंत्र अस्थिर (__HYPERCALL					\
		      : __HYPERCALL_4PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER4);				\
	(type)__res;							\
पूर्ण)

अटल अंतरभूत दीर्घ
xen_single_call(अचिन्हित पूर्णांक call,
		अचिन्हित दीर्घ a1, अचिन्हित दीर्घ a2,
		अचिन्हित दीर्घ a3, अचिन्हित दीर्घ a4,
		अचिन्हित दीर्घ a5)
अणु
	__HYPERCALL_DECLS;
	__HYPERCALL_5ARG(a1, a2, a3, a4, a5);

	अगर (call >= PAGE_SIZE / माप(hypercall_page[0]))
		वापस -EINVAL;

	यंत्र अस्थिर(CALL_NOSPEC
		     : __HYPERCALL_5PARAM
		     : [thunk_target] "a" (&hypercall_page[call])
		     : __HYPERCALL_CLOBBER5);

	वापस (दीर्घ)__res;
पूर्ण

अटल __always_अंतरभूत व्योम __xen_stac(व्योम)
अणु
	/*
	 * Suppress objtool seeing the STAC/CLAC and getting confused about it
	 * calling अक्रमom code with AC=1.
	 */
	यंत्र अस्थिर(ANNOTATE_IGNORE_ALTERNATIVE
		     ASM_STAC ::: "memory", "flags");
पूर्ण

अटल __always_अंतरभूत व्योम __xen_clac(व्योम)
अणु
	यंत्र अस्थिर(ANNOTATE_IGNORE_ALTERNATIVE
		     ASM_CLAC ::: "memory", "flags");
पूर्ण

अटल अंतरभूत दीर्घ
privcmd_call(अचिन्हित पूर्णांक call,
	     अचिन्हित दीर्घ a1, अचिन्हित दीर्घ a2,
	     अचिन्हित दीर्घ a3, अचिन्हित दीर्घ a4,
	     अचिन्हित दीर्घ a5)
अणु
	दीर्घ res;

	__xen_stac();
	res = xen_single_call(call, a1, a2, a3, a4, a5);
	__xen_clac();

	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_set_trap_table(काष्ठा trap_info *table)
अणु
	वापस _hypercall1(पूर्णांक, set_trap_table, table);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_mmu_update(काष्ठा mmu_update *req, पूर्णांक count,
		      पूर्णांक *success_count, करोmid_t करोmid)
अणु
	वापस _hypercall4(पूर्णांक, mmu_update, req, count, success_count, करोmid);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_mmuext_op(काष्ठा mmuext_op *op, पूर्णांक count,
		     पूर्णांक *success_count, करोmid_t करोmid)
अणु
	वापस _hypercall4(पूर्णांक, mmuext_op, op, count, success_count, करोmid);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_set_gdt(अचिन्हित दीर्घ *frame_list, पूर्णांक entries)
अणु
	वापस _hypercall2(पूर्णांक, set_gdt, frame_list, entries);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_callback_op(पूर्णांक cmd, व्योम *arg)
अणु
	वापस _hypercall2(पूर्णांक, callback_op, cmd, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_sched_op(पूर्णांक cmd, व्योम *arg)
अणु
	वापस _hypercall2(पूर्णांक, sched_op, cmd, arg);
पूर्ण

अटल अंतरभूत दीर्घ
HYPERVISOR_set_समयr_op(u64 समयout)
अणु
	अचिन्हित दीर्घ समयout_hi = (अचिन्हित दीर्घ)(समयout>>32);
	अचिन्हित दीर्घ समयout_lo = (अचिन्हित दीर्घ)समयout;
	वापस _hypercall2(दीर्घ, set_समयr_op, समयout_lo, समयout_hi);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_mca(काष्ठा xen_mc *mc_op)
अणु
	mc_op->पूर्णांकerface_version = XEN_MCA_INTERFACE_VERSION;
	वापस _hypercall1(पूर्णांक, mca, mc_op);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_platक्रमm_op(काष्ठा xen_platक्रमm_op *op)
अणु
	op->पूर्णांकerface_version = XENPF_INTERFACE_VERSION;
	वापस _hypercall1(पूर्णांक, platक्रमm_op, op);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_set_debugreg(पूर्णांक reg, अचिन्हित दीर्घ value)
अणु
	वापस _hypercall2(पूर्णांक, set_debugreg, reg, value);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
HYPERVISOR_get_debugreg(पूर्णांक reg)
अणु
	वापस _hypercall1(अचिन्हित दीर्घ, get_debugreg, reg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_update_descriptor(u64 ma, u64 desc)
अणु
	अगर (माप(u64) == माप(दीर्घ))
		वापस _hypercall2(पूर्णांक, update_descriptor, ma, desc);
	वापस _hypercall4(पूर्णांक, update_descriptor, ma, ma>>32, desc, desc>>32);
पूर्ण

अटल अंतरभूत दीर्घ
HYPERVISOR_memory_op(अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	वापस _hypercall2(दीर्घ, memory_op, cmd, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_multicall(व्योम *call_list, uपूर्णांक32_t nr_calls)
अणु
	वापस _hypercall2(पूर्णांक, multicall, call_list, nr_calls);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_update_va_mapping(अचिन्हित दीर्घ va, pte_t new_val,
			     अचिन्हित दीर्घ flags)
अणु
	अगर (माप(new_val) == माप(दीर्घ))
		वापस _hypercall3(पूर्णांक, update_va_mapping, va,
				   new_val.pte, flags);
	अन्यथा
		वापस _hypercall4(पूर्णांक, update_va_mapping, va,
				   new_val.pte, new_val.pte >> 32, flags);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_event_channel_op(पूर्णांक cmd, व्योम *arg)
अणु
	वापस _hypercall2(पूर्णांक, event_channel_op, cmd, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_xen_version(पूर्णांक cmd, व्योम *arg)
अणु
	वापस _hypercall2(पूर्णांक, xen_version, cmd, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_console_io(पूर्णांक cmd, पूर्णांक count, अक्षर *str)
अणु
	वापस _hypercall3(पूर्णांक, console_io, cmd, count, str);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_physdev_op(पूर्णांक cmd, व्योम *arg)
अणु
	वापस _hypercall2(पूर्णांक, physdev_op, cmd, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_grant_table_op(अचिन्हित पूर्णांक cmd, व्योम *uop, अचिन्हित पूर्णांक count)
अणु
	वापस _hypercall3(पूर्णांक, grant_table_op, cmd, uop, count);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_vm_assist(अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक type)
अणु
	वापस _hypercall2(पूर्णांक, vm_assist, cmd, type);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_vcpu_op(पूर्णांक cmd, पूर्णांक vcpuid, व्योम *extra_args)
अणु
	वापस _hypercall3(पूर्णांक, vcpu_op, cmd, vcpuid, extra_args);
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल अंतरभूत पूर्णांक
HYPERVISOR_set_segment_base(पूर्णांक reg, अचिन्हित दीर्घ value)
अणु
	वापस _hypercall2(पूर्णांक, set_segment_base, reg, value);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
HYPERVISOR_suspend(अचिन्हित दीर्घ start_info_mfn)
अणु
	काष्ठा sched_shutकरोwn r = अणु .reason = SHUTDOWN_suspend पूर्ण;

	/*
	 * For a PV guest the tools require that the start_info mfn be
	 * present in rdx/edx when the hypercall is made. Per the
	 * hypercall calling convention this is the third hypercall
	 * argument, which is start_info_mfn here.
	 */
	वापस _hypercall3(पूर्णांक, sched_op, SCHEDOP_shutकरोwn, &r, start_info_mfn);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __must_check
HYPERVISOR_hvm_op(पूर्णांक op, व्योम *arg)
अणु
       वापस _hypercall2(अचिन्हित दीर्घ, hvm_op, op, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_पंचांगem_op(
	काष्ठा पंचांगem_op *op)
अणु
	वापस _hypercall1(पूर्णांक, पंचांगem_op, op);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_xenpmu_op(अचिन्हित पूर्णांक op, व्योम *arg)
अणु
	वापस _hypercall2(पूर्णांक, xenpmu_op, op, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
HYPERVISOR_dm_op(
	करोmid_t करोm, अचिन्हित पूर्णांक nr_bufs, काष्ठा xen_dm_op_buf *bufs)
अणु
	पूर्णांक ret;
	__xen_stac();
	ret = _hypercall3(पूर्णांक, dm_op, करोm, nr_bufs, bufs);
	__xen_clac();
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
MULTI_fpu_taskचयन(काष्ठा multicall_entry *mcl, पूर्णांक set)
अणु
	mcl->op = __HYPERVISOR_fpu_taskचयन;
	mcl->args[0] = set;

	trace_xen_mc_entry(mcl, 1);
पूर्ण

अटल अंतरभूत व्योम
MULTI_update_va_mapping(काष्ठा multicall_entry *mcl, अचिन्हित दीर्घ va,
			pte_t new_val, अचिन्हित दीर्घ flags)
अणु
	mcl->op = __HYPERVISOR_update_va_mapping;
	mcl->args[0] = va;
	अगर (माप(new_val) == माप(दीर्घ)) अणु
		mcl->args[1] = new_val.pte;
		mcl->args[2] = flags;
	पूर्ण अन्यथा अणु
		mcl->args[1] = new_val.pte;
		mcl->args[2] = new_val.pte >> 32;
		mcl->args[3] = flags;
	पूर्ण

	trace_xen_mc_entry(mcl, माप(new_val) == माप(दीर्घ) ? 3 : 4);
पूर्ण

अटल अंतरभूत व्योम
MULTI_update_descriptor(काष्ठा multicall_entry *mcl, u64 maddr,
			काष्ठा desc_काष्ठा desc)
अणु
	mcl->op = __HYPERVISOR_update_descriptor;
	अगर (माप(maddr) == माप(दीर्घ)) अणु
		mcl->args[0] = maddr;
		mcl->args[1] = *(अचिन्हित दीर्घ *)&desc;
	पूर्ण अन्यथा अणु
		u32 *p = (u32 *)&desc;

		mcl->args[0] = maddr;
		mcl->args[1] = maddr >> 32;
		mcl->args[2] = *p++;
		mcl->args[3] = *p;
	पूर्ण

	trace_xen_mc_entry(mcl, माप(maddr) == माप(दीर्घ) ? 2 : 4);
पूर्ण

अटल अंतरभूत व्योम
MULTI_mmu_update(काष्ठा multicall_entry *mcl, काष्ठा mmu_update *req,
		 पूर्णांक count, पूर्णांक *success_count, करोmid_t करोmid)
अणु
	mcl->op = __HYPERVISOR_mmu_update;
	mcl->args[0] = (अचिन्हित दीर्घ)req;
	mcl->args[1] = count;
	mcl->args[2] = (अचिन्हित दीर्घ)success_count;
	mcl->args[3] = करोmid;

	trace_xen_mc_entry(mcl, 4);
पूर्ण

अटल अंतरभूत व्योम
MULTI_mmuext_op(काष्ठा multicall_entry *mcl, काष्ठा mmuext_op *op, पूर्णांक count,
		पूर्णांक *success_count, करोmid_t करोmid)
अणु
	mcl->op = __HYPERVISOR_mmuext_op;
	mcl->args[0] = (अचिन्हित दीर्घ)op;
	mcl->args[1] = count;
	mcl->args[2] = (अचिन्हित दीर्घ)success_count;
	mcl->args[3] = करोmid;

	trace_xen_mc_entry(mcl, 4);
पूर्ण

अटल अंतरभूत व्योम
MULTI_stack_चयन(काष्ठा multicall_entry *mcl,
		   अचिन्हित दीर्घ ss, अचिन्हित दीर्घ esp)
अणु
	mcl->op = __HYPERVISOR_stack_चयन;
	mcl->args[0] = ss;
	mcl->args[1] = esp;

	trace_xen_mc_entry(mcl, 2);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_XEN_HYPERCALL_H */
