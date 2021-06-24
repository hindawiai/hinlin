<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013, Michael Ellerman, IBM Corporation.
 */

#घोषणा pr_fmt(fmt)	"powernv-rng: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/archअक्रमom.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/smp.h>

#घोषणा DARN_ERR 0xFFFFFFFFFFFFFFFFul

काष्ठा घातernv_rng अणु
	व्योम __iomem *regs;
	व्योम __iomem *regs_real;
	अचिन्हित दीर्घ mask;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा घातernv_rng *, घातernv_rng);


पूर्णांक घातernv_hwrng_present(व्योम)
अणु
	काष्ठा घातernv_rng *rng;

	rng = get_cpu_var(घातernv_rng);
	put_cpu_var(rng);
	वापस rng != शून्य;
पूर्ण

अटल अचिन्हित दीर्घ rng_whiten(काष्ठा घातernv_rng *rng, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ parity;

	/* Calculate the parity of the value */
	यंत्र ("popcntd %0,%1" : "=r" (parity) : "r" (val));

	/* xor our value with the previous mask */
	val ^= rng->mask;

	/* update the mask based on the parity of this value */
	rng->mask = (rng->mask << 1) | (parity & 1);

	वापस val;
पूर्ण

पूर्णांक घातernv_get_अक्रमom_real_mode(अचिन्हित दीर्घ *v)
अणु
	काष्ठा घातernv_rng *rng;

	rng = raw_cpu_पढ़ो(घातernv_rng);

	*v = rng_whiten(rng, __raw_rm_पढ़ोq(rng->regs_real));

	वापस 1;
पूर्ण

अटल पूर्णांक घातernv_get_अक्रमom_darn(अचिन्हित दीर्घ *v)
अणु
	अचिन्हित दीर्घ val;

	/* Using DARN with L=1 - 64-bit conditioned अक्रमom number */
	यंत्र अस्थिर(PPC_DARN(%0, 1) : "=r"(val));

	अगर (val == DARN_ERR)
		वापस 0;

	*v = val;

	वापस 1;
पूर्ण

अटल पूर्णांक initialise_darn(व्योम)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		वापस -ENODEV;

	क्रम (i = 0; i < 10; i++) अणु
		अगर (घातernv_get_अक्रमom_darn(&val)) अणु
			ppc_md.get_अक्रमom_seed = घातernv_get_अक्रमom_darn;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_warn("Unable to use DARN for get_random_seed()\n");

	वापस -EIO;
पूर्ण

पूर्णांक घातernv_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	काष्ठा घातernv_rng *rng;

	rng = get_cpu_var(घातernv_rng);

	*v = rng_whiten(rng, in_be64(rng->regs));

	put_cpu_var(rng);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(घातernv_get_अक्रमom_दीर्घ);

अटल __init व्योम rng_init_per_cpu(काष्ठा घातernv_rng *rng,
				    काष्ठा device_node *dn)
अणु
	पूर्णांक chip_id, cpu;

	chip_id = of_get_ibm_chip_id(dn);
	अगर (chip_id == -1)
		pr_warn("No ibm,chip-id found for %pOF.\n", dn);

	क्रम_each_possible_cpu(cpu) अणु
		अगर (per_cpu(घातernv_rng, cpu) == शून्य ||
		    cpu_to_chip_id(cpu) == chip_id) अणु
			per_cpu(घातernv_rng, cpu) = rng;
		पूर्ण
	पूर्ण
पूर्ण

अटल __init पूर्णांक rng_create(काष्ठा device_node *dn)
अणु
	काष्ठा घातernv_rng *rng;
	काष्ठा resource res;
	अचिन्हित दीर्घ val;

	rng = kzalloc(माप(*rng), GFP_KERNEL);
	अगर (!rng)
		वापस -ENOMEM;

	अगर (of_address_to_resource(dn, 0, &res)) अणु
		kमुक्त(rng);
		वापस -ENXIO;
	पूर्ण

	rng->regs_real = (व्योम __iomem *)res.start;

	rng->regs = of_iomap(dn, 0);
	अगर (!rng->regs) अणु
		kमुक्त(rng);
		वापस -ENXIO;
	पूर्ण

	val = in_be64(rng->regs);
	rng->mask = val;

	rng_init_per_cpu(rng, dn);

	pr_info_once("Registering arch random hook.\n");

	ppc_md.get_अक्रमom_seed = घातernv_get_अक्रमom_दीर्घ;

	वापस 0;
पूर्ण

अटल __init पूर्णांक rng_init(व्योम)
अणु
	काष्ठा device_node *dn;
	पूर्णांक rc;

	क्रम_each_compatible_node(dn, शून्य, "ibm,power-rng") अणु
		rc = rng_create(dn);
		अगर (rc) अणु
			pr_err("Failed creating rng for %pOF (%d).\n",
				dn, rc);
			जारी;
		पूर्ण

		/* Create devices क्रम hwrng driver */
		of_platक्रमm_device_create(dn, शून्य, शून्य);
	पूर्ण

	initialise_darn();

	वापस 0;
पूर्ण
machine_subsys_initcall(घातernv, rng_init);
