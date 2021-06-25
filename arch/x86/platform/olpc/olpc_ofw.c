<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/init.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/special_insns.h>
#समावेश <यंत्र/olpc_ofw.h>

/* address of OFW callback पूर्णांकerface; will be शून्य अगर OFW isn't found */
अटल पूर्णांक (*olpc_ofw_cअगर)(पूर्णांक *);

/* page dir entry containing OFW's pgdir table; filled in by head_32.S */
u32 olpc_ofw_pgd __initdata;

अटल DEFINE_SPINLOCK(ofw_lock);

#घोषणा MAXARGS 10

व्योम __init setup_olpc_ofw_pgd(व्योम)
अणु
	pgd_t *base, *ofw_pde;

	अगर (!olpc_ofw_cअगर)
		वापस;

	/* fetch OFW's PDE */
	base = early_ioremap(olpc_ofw_pgd, माप(olpc_ofw_pgd) * PTRS_PER_PGD);
	अगर (!base) अणु
		prपूर्णांकk(KERN_ERR "failed to remap OFW's pgd - disabling OFW!\n");
		olpc_ofw_cअगर = शून्य;
		वापस;
	पूर्ण
	ofw_pde = &base[OLPC_OFW_PDE_NR];

	/* install OFW's PDE permanently into the kernel's pgtable */
	set_pgd(&swapper_pg_dir[OLPC_OFW_PDE_NR], *ofw_pde);
	/* implicit optimization barrier here due to unअंतरभूत function वापस */

	early_iounmap(base, माप(olpc_ofw_pgd) * PTRS_PER_PGD);
पूर्ण

पूर्णांक __olpc_ofw(स्थिर अक्षर *name, पूर्णांक nr_args, स्थिर व्योम **args, पूर्णांक nr_res,
		व्योम **res)
अणु
	पूर्णांक ofw_args[MAXARGS + 3];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, i, *p;

	BUG_ON(nr_args + nr_res > MAXARGS);

	अगर (!olpc_ofw_cअगर)
		वापस -EIO;

	ofw_args[0] = (पूर्णांक)name;
	ofw_args[1] = nr_args;
	ofw_args[2] = nr_res;

	p = &ofw_args[3];
	क्रम (i = 0; i < nr_args; i++, p++)
		*p = (पूर्णांक)args[i];

	/* call पूर्णांकo ofw */
	spin_lock_irqsave(&ofw_lock, flags);
	ret = olpc_ofw_cअगर(ofw_args);
	spin_unlock_irqrestore(&ofw_lock, flags);

	अगर (!ret) अणु
		क्रम (i = 0; i < nr_res; i++, p++)
			*((पूर्णांक *)res[i]) = *p;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__olpc_ofw);

bool olpc_ofw_present(व्योम)
अणु
	वापस olpc_ofw_cअगर != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ofw_present);

/* OFW cअगर _should_ be above this address */
#घोषणा OFW_MIN 0xff000000

/* OFW starts on a 1MB boundary */
#घोषणा OFW_BOUND (1<<20)

व्योम __init olpc_ofw_detect(व्योम)
अणु
	काष्ठा olpc_ofw_header *hdr = &boot_params.olpc_ofw_header;
	अचिन्हित दीर्घ start;

	/* ensure OFW booted us by checking क्रम "OFW " string */
	अगर (hdr->ofw_magic != OLPC_OFW_SIG)
		वापस;

	olpc_ofw_cअगर = (पूर्णांक (*)(पूर्णांक *))hdr->cअगर_handler;

	अगर ((अचिन्हित दीर्घ)olpc_ofw_cअगर < OFW_MIN) अणु
		prपूर्णांकk(KERN_ERR "OFW detected, but cif has invalid address 0x%lx - disabling.\n",
				(अचिन्हित दीर्घ)olpc_ofw_cअगर);
		olpc_ofw_cअगर = शून्य;
		वापस;
	पूर्ण

	/* determine where OFW starts in memory */
	start = round_करोwn((अचिन्हित दीर्घ)olpc_ofw_cअगर, OFW_BOUND);
	prपूर्णांकk(KERN_INFO "OFW detected in memory, cif @ 0x%lx (reserving top %ldMB)\n",
			(अचिन्हित दीर्घ)olpc_ofw_cअगर, (-start) >> 20);
	reserve_top_address(-start);
पूर्ण

bool __init olpc_ofw_is_installed(व्योम)
अणु
	वापस olpc_ofw_cअगर != शून्य;
पूर्ण
