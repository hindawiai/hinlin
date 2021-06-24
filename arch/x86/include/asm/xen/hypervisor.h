<शैली गुरु>
/******************************************************************************
 * hypervisor.h
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

#अगर_अघोषित _ASM_X86_XEN_HYPERVISOR_H
#घोषणा _ASM_X86_XEN_HYPERVISOR_H

बाह्य काष्ठा shared_info *HYPERVISOR_shared_info;
बाह्य काष्ठा start_info *xen_start_info;

#समावेश <यंत्र/processor.h>

अटल अंतरभूत uपूर्णांक32_t xen_cpuid_base(व्योम)
अणु
	वापस hypervisor_cpuid_base("XenVMMXenVMM", 2);
पूर्ण

#अगर_घोषित CONFIG_XEN
बाह्य bool __init xen_hvm_need_lapic(व्योम);

अटल अंतरभूत bool __init xen_x2apic_para_available(व्योम)
अणु
	वापस xen_hvm_need_lapic();
पूर्ण
#अन्यथा
अटल अंतरभूत bool __init xen_x2apic_para_available(व्योम)
अणु
	वापस (xen_cpuid_base() != 0);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम xen_arch_रेजिस्टर_cpu(पूर्णांक num);
व्योम xen_arch_unरेजिस्टर_cpu(पूर्णांक num);
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_XEN_HYPERVISOR_H */
