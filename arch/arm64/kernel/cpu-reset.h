<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * CPU reset routines
 *
 * Copyright (C) 2015 Huawei Futurewei Technologies.
 */

#अगर_अघोषित _ARM64_CPU_RESET_H
#घोषणा _ARM64_CPU_RESET_H

#समावेश <यंत्र/virt.h>

व्योम __cpu_soft_restart(अचिन्हित दीर्घ el2_चयन, अचिन्हित दीर्घ entry,
	अचिन्हित दीर्घ arg0, अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2);

अटल अंतरभूत व्योम __noवापस __nocfi cpu_soft_restart(अचिन्हित दीर्घ entry,
						       अचिन्हित दीर्घ arg0,
						       अचिन्हित दीर्घ arg1,
						       अचिन्हित दीर्घ arg2)
अणु
	typeof(__cpu_soft_restart) *restart;

	अचिन्हित दीर्घ el2_चयन = !is_kernel_in_hyp_mode() &&
		is_hyp_mode_available();
	restart = (व्योम *)__pa_symbol(function_nocfi(__cpu_soft_restart));

	cpu_install_idmap();
	restart(el2_चयन, entry, arg0, arg1, arg2);
	unreachable();
पूर्ण

#पूर्ण_अगर
