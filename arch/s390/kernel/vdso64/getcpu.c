<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright IBM Corp. 2020 */

#समावेश <linux/compiler.h>
#समावेश <linux/अ_लोpu.h>
#समावेश <यंत्र/समयx.h>
#समावेश "vdso.h"

पूर्णांक __s390_vdso_अ_लोpu(अचिन्हित *cpu, अचिन्हित *node, काष्ठा अ_लोpu_cache *unused)
अणु
	जोड़ tod_घड़ी clk;

	/* CPU number is stored in the programmable field of the TOD घड़ी */
	store_tod_घड़ी_ext(&clk);
	अगर (cpu)
		*cpu = clk.pf;
	/* NUMA node is always zero */
	अगर (node)
		*node = 0;
	वापस 0;
पूर्ण
