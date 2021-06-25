<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ePAPR para-भवization support.
 *
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <यंत्र/epapr_hcalls.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/inst.h>

#अगर !defined(CONFIG_64BIT) || defined(CONFIG_PPC_BOOK3E_64)
बाह्य व्योम epapr_ev_idle(व्योम);
बाह्य u32 epapr_ev_idle_start[];
#पूर्ण_अगर

bool epapr_paravirt_enabled;
अटल bool __maybe_unused epapr_has_idle;

अटल पूर्णांक __init early_init_dt_scan_epapr(अचिन्हित दीर्घ node,
					   स्थिर अक्षर *uname,
					   पूर्णांक depth, व्योम *data)
अणु
	स्थिर u32 *insts;
	पूर्णांक len;
	पूर्णांक i;

	insts = of_get_flat_dt_prop(node, "hcall-instructions", &len);
	अगर (!insts)
		वापस 0;

	अगर (len % 4 || len > (4 * 4))
		वापस -1;

	क्रम (i = 0; i < (len / 4); i++) अणु
		काष्ठा ppc_inst inst = ppc_inst(be32_to_cpu(insts[i]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(epapr_hypercall_start + i), inst);
#अगर !defined(CONFIG_64BIT) || defined(CONFIG_PPC_BOOK3E_64)
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(epapr_ev_idle_start + i), inst);
#पूर्ण_अगर
	पूर्ण

#अगर !defined(CONFIG_64BIT) || defined(CONFIG_PPC_BOOK3E_64)
	अगर (of_get_flat_dt_prop(node, "has-idle", शून्य))
		epapr_has_idle = true;
#पूर्ण_अगर

	epapr_paravirt_enabled = true;

	वापस 1;
पूर्ण

पूर्णांक __init epapr_paravirt_early_init(व्योम)
अणु
	of_scan_flat_dt(early_init_dt_scan_epapr, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक __init epapr_idle_init(व्योम)
अणु
#अगर !defined(CONFIG_64BIT) || defined(CONFIG_PPC_BOOK3E_64)
	अगर (epapr_has_idle)
		ppc_md.घातer_save = epapr_ev_idle;
#पूर्ण_अगर

	वापस 0;
पूर्ण

postcore_initcall(epapr_idle_init);
