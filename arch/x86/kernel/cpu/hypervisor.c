<शैली गुरु>
/*
 * Common hypervisor code
 *
 * Copyright (C) 2008, VMware, Inc.
 * Author : Alok N Kataria <akataria@vmware.com>
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

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/hypervisor.h>

अटल स्थिर __initस्थिर काष्ठा hypervisor_x86 * स्थिर hypervisors[] =
अणु
#अगर_घोषित CONFIG_XEN_PV
	&x86_hyper_xen_pv,
#पूर्ण_अगर
#अगर_घोषित CONFIG_XEN_PVHVM
	&x86_hyper_xen_hvm,
#पूर्ण_अगर
	&x86_hyper_vmware,
	&x86_hyper_ms_hyperv,
#अगर_घोषित CONFIG_KVM_GUEST
	&x86_hyper_kvm,
#पूर्ण_अगर
#अगर_घोषित CONFIG_JAILHOUSE_GUEST
	&x86_hyper_jailhouse,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACRN_GUEST
	&x86_hyper_acrn,
#पूर्ण_अगर
पूर्ण;

क्रमागत x86_hypervisor_type x86_hyper_type;
EXPORT_SYMBOL(x86_hyper_type);

bool __initdata nopv;
अटल __init पूर्णांक parse_nopv(अक्षर *arg)
अणु
	nopv = true;
	वापस 0;
पूर्ण
early_param("nopv", parse_nopv);

अटल अंतरभूत स्थिर काष्ठा hypervisor_x86 * __init
detect_hypervisor_venकरोr(व्योम)
अणु
	स्थिर काष्ठा hypervisor_x86 *h = शून्य, * स्थिर *p;
	uपूर्णांक32_t pri, max_pri = 0;

	क्रम (p = hypervisors; p < hypervisors + ARRAY_SIZE(hypervisors); p++) अणु
		अगर (unlikely(nopv) && !(*p)->ignore_nopv)
			जारी;

		pri = (*p)->detect();
		अगर (pri > max_pri) अणु
			max_pri = pri;
			h = *p;
		पूर्ण
	पूर्ण

	अगर (h)
		pr_info("Hypervisor detected: %s\n", h->name);

	वापस h;
पूर्ण

अटल व्योम __init copy_array(स्थिर व्योम *src, व्योम *target, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i, n = size / माप(व्योम *);
	स्थिर व्योम * स्थिर *from = (स्थिर व्योम * स्थिर *)src;
	स्थिर व्योम **to = (स्थिर व्योम **)target;

	क्रम (i = 0; i < n; i++)
		अगर (from[i])
			to[i] = from[i];
पूर्ण

व्योम __init init_hypervisor_platक्रमm(व्योम)
अणु
	स्थिर काष्ठा hypervisor_x86 *h;

	h = detect_hypervisor_venकरोr();

	अगर (!h)
		वापस;

	copy_array(&h->init, &x86_init.hyper, माप(h->init));
	copy_array(&h->runसमय, &x86_platक्रमm.hyper, माप(h->runसमय));

	x86_hyper_type = h->type;
	x86_init.hyper.init_platक्रमm();
पूर्ण
