<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Copyright IBM Corp. 2010, 2017
 * Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>,
 *	      Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 *
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>
#समावेश <मानककोष.स>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <माला.स>
#समावेश <dwarf-regs.h>
#समावेश "dwarf-regs-table.h"

स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	वापस (n >= ARRAY_SIZE(s390_dwarf_regs)) ? शून्य : s390_dwarf_regs[n];
पूर्ण

/*
 * Convert the रेजिस्टर name पूर्णांकo an offset to काष्ठा pt_regs (kernel).
 * This is required by the BPF prologue generator.  The BPF
 * program is called in the BPF overflow handler in the perf
 * core.
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ gpr;

	अगर (!name || म_भेदन(name, "%r", 2))
		वापस -EINVAL;

	त्रुटि_सं = 0;
	gpr = म_से_अदीर्घ(name + 2, शून्य, 10);
	अगर (त्रुटि_सं || gpr >= 16)
		वापस -EINVAL;

	वापस दुरत्व(user_pt_regs, gprs) + 8 * gpr;
पूर्ण
