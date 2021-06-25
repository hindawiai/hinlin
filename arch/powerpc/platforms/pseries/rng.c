<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013, Michael Ellerman, IBM Corporation.
 */

#घोषणा pr_fmt(fmt)	"pseries-rng: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/archअक्रमom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/plpar_wrappers.h>


अटल पूर्णांक pseries_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	अगर (plpar_hcall(H_RANDOM, retbuf) == H_SUCCESS) अणु
		*v = retbuf[0];
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल __init पूर्णांक rng_init(व्योम)
अणु
	काष्ठा device_node *dn;

	dn = of_find_compatible_node(शून्य, शून्य, "ibm,random");
	अगर (!dn)
		वापस -ENODEV;

	pr_info("Registering arch random hook.\n");

	ppc_md.get_अक्रमom_seed = pseries_get_अक्रमom_दीर्घ;

	of_node_put(dn);
	वापस 0;
पूर्ण
machine_subsys_initcall(pseries, rng_init);
