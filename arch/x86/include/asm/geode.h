<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Geode definitions
 * Copyright (C) 2006, Advanced Micro Devices, Inc.
 */

#अगर_अघोषित _ASM_X86_GEODE_H
#घोषणा _ASM_X86_GEODE_H

#समावेश <यंत्र/processor.h>
#समावेश <linux/पन.स>
#समावेश <linux/cs5535.h>

अटल अंतरभूत पूर्णांक is_geode_gx(व्योम)
अणु
	वापस ((boot_cpu_data.x86_venकरोr == X86_VENDOR_NSC) &&
		(boot_cpu_data.x86 == 5) &&
		(boot_cpu_data.x86_model == 5));
पूर्ण

अटल अंतरभूत पूर्णांक is_geode_lx(व्योम)
अणु
	वापस ((boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD) &&
		(boot_cpu_data.x86 == 5) &&
		(boot_cpu_data.x86_model == 10));
पूर्ण

अटल अंतरभूत पूर्णांक is_geode(व्योम)
अणु
	वापस (is_geode_gx() || is_geode_lx());
पूर्ण

#पूर्ण_अगर /* _ASM_X86_GEODE_H */
