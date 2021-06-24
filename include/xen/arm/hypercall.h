<शैली गुरु>
/******************************************************************************
 * hypercall.h
 *
 * Linux-specअगरic hypervisor handling.
 *
 * Stefano Stabellini <stefano.stabellini@eu.citrix.com>, Citrix, 2012
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

#अगर_अघोषित _ASM_ARM_XEN_HYPERCALL_H
#घोषणा _ASM_ARM_XEN_HYPERCALL_H

#समावेश <linux/bug.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/sched.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>

काष्ठा xen_dm_op_buf;

दीर्घ privcmd_call(अचिन्हित call, अचिन्हित दीर्घ a1,
		अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3,
		अचिन्हित दीर्घ a4, अचिन्हित दीर्घ a5);
पूर्णांक HYPERVISOR_xen_version(पूर्णांक cmd, व्योम *arg);
पूर्णांक HYPERVISOR_console_io(पूर्णांक cmd, पूर्णांक count, अक्षर *str);
पूर्णांक HYPERVISOR_grant_table_op(अचिन्हित पूर्णांक cmd, व्योम *uop, अचिन्हित पूर्णांक count);
पूर्णांक HYPERVISOR_sched_op(पूर्णांक cmd, व्योम *arg);
पूर्णांक HYPERVISOR_event_channel_op(पूर्णांक cmd, व्योम *arg);
अचिन्हित दीर्घ HYPERVISOR_hvm_op(पूर्णांक op, व्योम *arg);
पूर्णांक HYPERVISOR_memory_op(अचिन्हित पूर्णांक cmd, व्योम *arg);
पूर्णांक HYPERVISOR_physdev_op(पूर्णांक cmd, व्योम *arg);
पूर्णांक HYPERVISOR_vcpu_op(पूर्णांक cmd, पूर्णांक vcpuid, व्योम *extra_args);
पूर्णांक HYPERVISOR_पंचांगem_op(व्योम *arg);
पूर्णांक HYPERVISOR_vm_assist(अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक type);
पूर्णांक HYPERVISOR_dm_op(करोmid_t करोmid, अचिन्हित पूर्णांक nr_bufs,
		     काष्ठा xen_dm_op_buf *bufs);
पूर्णांक HYPERVISOR_platक्रमm_op_raw(व्योम *arg);
अटल अंतरभूत पूर्णांक HYPERVISOR_platक्रमm_op(काष्ठा xen_platक्रमm_op *op)
अणु
	op->पूर्णांकerface_version = XENPF_INTERFACE_VERSION;
	वापस HYPERVISOR_platक्रमm_op_raw(op);
पूर्ण
पूर्णांक HYPERVISOR_multicall(काष्ठा multicall_entry *calls, uपूर्णांक32_t nr);

अटल अंतरभूत पूर्णांक
HYPERVISOR_suspend(अचिन्हित दीर्घ start_info_mfn)
अणु
	काष्ठा sched_shutकरोwn r = अणु .reason = SHUTDOWN_suspend पूर्ण;

	/* start_info_mfn is unused on ARM */
	वापस HYPERVISOR_sched_op(SCHEDOP_shutकरोwn, &r);
पूर्ण

अटल अंतरभूत व्योम
MULTI_update_va_mapping(काष्ठा multicall_entry *mcl, अचिन्हित दीर्घ va,
			अचिन्हित पूर्णांक new_val, अचिन्हित दीर्घ flags)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम
MULTI_mmu_update(काष्ठा multicall_entry *mcl, काष्ठा mmu_update *req,
		 पूर्णांक count, पूर्णांक *success_count, करोmid_t करोmid)
अणु
	BUG();
पूर्ण

#पूर्ण_अगर /* _ASM_ARM_XEN_HYPERCALL_H */
