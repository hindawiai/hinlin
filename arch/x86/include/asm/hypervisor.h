<शैली गुरु>
/*
 * Copyright (C) 2008, VMware, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 */
#अगर_अघोषित _ASM_X86_HYPERVISOR_H
#घोषणा _ASM_X86_HYPERVISOR_H

/* x86 hypervisor types  */
क्रमागत x86_hypervisor_type अणु
	X86_HYPER_NATIVE = 0,
	X86_HYPER_VMWARE,
	X86_HYPER_MS_HYPERV,
	X86_HYPER_XEN_PV,
	X86_HYPER_XEN_HVM,
	X86_HYPER_KVM,
	X86_HYPER_JAILHOUSE,
	X86_HYPER_ACRN,
पूर्ण;

#अगर_घोषित CONFIG_HYPERVISOR_GUEST

#समावेश <यंत्र/kvm_para.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/xen/hypervisor.h>

काष्ठा hypervisor_x86 अणु
	/* Hypervisor name */
	स्थिर अक्षर	*name;

	/* Detection routine */
	uपूर्णांक32_t	(*detect)(व्योम);

	/* Hypervisor type */
	क्रमागत x86_hypervisor_type type;

	/* init समय callbacks */
	काष्ठा x86_hyper_init init;

	/* runसमय callbacks */
	काष्ठा x86_hyper_runसमय runसमय;

	/* ignore nopv parameter */
	bool ignore_nopv;
पूर्ण;

बाह्य स्थिर काष्ठा hypervisor_x86 x86_hyper_vmware;
बाह्य स्थिर काष्ठा hypervisor_x86 x86_hyper_ms_hyperv;
बाह्य स्थिर काष्ठा hypervisor_x86 x86_hyper_xen_pv;
बाह्य स्थिर काष्ठा hypervisor_x86 x86_hyper_kvm;
बाह्य स्थिर काष्ठा hypervisor_x86 x86_hyper_jailhouse;
बाह्य स्थिर काष्ठा hypervisor_x86 x86_hyper_acrn;
बाह्य काष्ठा hypervisor_x86 x86_hyper_xen_hvm;

बाह्य bool nopv;
बाह्य क्रमागत x86_hypervisor_type x86_hyper_type;
बाह्य व्योम init_hypervisor_platक्रमm(व्योम);
अटल अंतरभूत bool hypervisor_is_type(क्रमागत x86_hypervisor_type type)
अणु
	वापस x86_hyper_type == type;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम init_hypervisor_platक्रमm(व्योम) अणु पूर्ण
अटल अंतरभूत bool hypervisor_is_type(क्रमागत x86_hypervisor_type type)
अणु
	वापस type == X86_HYPER_NATIVE;
पूर्ण
#पूर्ण_अगर /* CONFIG_HYPERVISOR_GUEST */
#पूर्ण_अगर /* _ASM_X86_HYPERVISOR_H */
