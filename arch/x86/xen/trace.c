<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ftrace.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/xen-mca.h>

#घोषणा HYPERCALL(x)	[__HYPERVISOR_##x] = "("#x")",
अटल स्थिर अक्षर *xen_hypercall_names[] = अणु
#समावेश <यंत्र/xen-hypercalls.h>
पूर्ण;
#अघोषित HYPERCALL

अटल स्थिर अक्षर *xen_hypercall_name(अचिन्हित op)
अणु
	अगर (op < ARRAY_SIZE(xen_hypercall_names) && xen_hypercall_names[op] != शून्य)
		वापस xen_hypercall_names[op];

	वापस "";
पूर्ण

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/xen.h>
