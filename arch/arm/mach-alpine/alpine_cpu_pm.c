<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Low-level घातer-management support क्रम Alpine platक्रमm.
 *
 * Copyright (C) 2015 Annapurna Lअसल Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "alpine_cpu_pm.h"
#समावेश "alpine_cpu_resume.h"

/* NB रेजिस्टरs */
#घोषणा AL_SYSFAB_POWER_CONTROL(cpu)	(0x2000 + (cpu)*0x100 + 0x20)

अटल काष्ठा regmap *al_sysfabric;
अटल काष्ठा al_cpu_resume_regs __iomem *al_cpu_resume_regs;
अटल पूर्णांक wakeup_supported;

पूर्णांक alpine_cpu_wakeup(अचिन्हित पूर्णांक phys_cpu, uपूर्णांक32_t phys_resume_addr)
अणु
	अगर (!wakeup_supported)
		वापस -ENOSYS;

	/*
	 * Set CPU resume address -
	 * secure firmware running on boot will jump to this address
	 * after setting proper CPU mode, and initialiing e.g. secure
	 * regs (the same mode all CPUs are booted to - usually HYP)
	 */
	ग_लिखोl(phys_resume_addr,
	       &al_cpu_resume_regs->per_cpu[phys_cpu].resume_addr);

	/* Power-up the CPU */
	regmap_ग_लिखो(al_sysfabric, AL_SYSFAB_POWER_CONTROL(phys_cpu), 0);

	वापस 0;
पूर्ण

व्योम __init alpine_cpu_pm_init(व्योम)
अणु
	काष्ठा device_node *np;
	uपूर्णांक32_t watermark;

	al_sysfabric = syscon_regmap_lookup_by_compatible("al,alpine-sysfabric-service");

	np = of_find_compatible_node(शून्य, शून्य, "al,alpine-cpu-resume");
	al_cpu_resume_regs = of_iomap(np, 0);

	wakeup_supported = !IS_ERR(al_sysfabric) && al_cpu_resume_regs;

	अगर (wakeup_supported) अणु
		watermark = पढ़ोl(&al_cpu_resume_regs->watermark);
		wakeup_supported = (watermark & AL_CPU_RESUME_MAGIC_NUM_MASK)
				    == AL_CPU_RESUME_MAGIC_NUM;
	पूर्ण
पूर्ण
