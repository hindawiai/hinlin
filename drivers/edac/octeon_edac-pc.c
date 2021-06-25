<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 Cavium, Inc.
 *
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/edac.h>

#समावेश "edac_module.h"

#समावेश <यंत्र/octeon/cvmx.h>
#समावेश <यंत्र/mipsregs.h>

बाह्य पूर्णांक रेजिस्टर_co_cache_error_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक unरेजिस्टर_co_cache_error_notअगरier(काष्ठा notअगरier_block *nb);

बाह्य अचिन्हित दीर्घ दीर्घ cache_err_dcache[NR_CPUS];

काष्ठा co_cache_error अणु
	काष्ठा notअगरier_block notअगरier;
	काष्ठा edac_device_ctl_info *ed;
पूर्ण;

/**
 * EDAC CPU cache error callback
 *
 * @event: non-zero अगर unrecoverable.
 */
अटल पूर्णांक  co_cache_error_event(काष्ठा notअगरier_block *this,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा co_cache_error *p = container_of(this, काष्ठा co_cache_error,
						notअगरier);

	अचिन्हित पूर्णांक core = cvmx_get_core_num();
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u64 icache_err = पढ़ो_octeon_c0_icacheerr();
	u64 dcache_err;

	अगर (event) अणु
		dcache_err = cache_err_dcache[core];
		cache_err_dcache[core] = 0;
	पूर्ण अन्यथा अणु
		dcache_err = पढ़ो_octeon_c0_dcacheerr();
	पूर्ण

	अगर (icache_err & 1) अणु
		edac_device_prपूर्णांकk(p->ed, KERN_ERR,
				   "CacheErr (Icache):%llx, core %d/cpu %d, cp0_errorepc == %lx\n",
				   (अचिन्हित दीर्घ दीर्घ)icache_err, core, cpu,
				   पढ़ो_c0_errorepc());
		ग_लिखो_octeon_c0_icacheerr(0);
		edac_device_handle_ce(p->ed, cpu, 1, "icache");
	पूर्ण
	अगर (dcache_err & 1) अणु
		edac_device_prपूर्णांकk(p->ed, KERN_ERR,
				   "CacheErr (Dcache):%llx, core %d/cpu %d, cp0_errorepc == %lx\n",
				   (अचिन्हित दीर्घ दीर्घ)dcache_err, core, cpu,
				   पढ़ो_c0_errorepc());
		अगर (event)
			edac_device_handle_ue(p->ed, cpu, 0, "dcache");
		अन्यथा
			edac_device_handle_ce(p->ed, cpu, 0, "dcache");

		/* Clear the error indication */
		अगर (OCTEON_IS_OCTEON2())
			ग_लिखो_octeon_c0_dcacheerr(1);
		अन्यथा
			ग_लिखो_octeon_c0_dcacheerr(0);
	पूर्ण

	वापस NOTIFY_STOP;
पूर्ण

अटल पूर्णांक co_cache_error_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा co_cache_error *p = devm_kzalloc(&pdev->dev, माप(*p),
						GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->notअगरier.notअगरier_call = co_cache_error_event;
	platक्रमm_set_drvdata(pdev, p);

	p->ed = edac_device_alloc_ctl_info(0, "cpu", num_possible_cpus(),
					   "cache", 2, 0, शून्य, 0,
					   edac_device_alloc_index());
	अगर (!p->ed)
		जाओ err;

	p->ed->dev = &pdev->dev;

	p->ed->dev_name = dev_name(&pdev->dev);

	p->ed->mod_name = "octeon-cpu";
	p->ed->ctl_name = "cache";

	अगर (edac_device_add_device(p->ed)) अणु
		pr_err("%s: edac_device_add_device() failed\n", __func__);
		जाओ err1;
	पूर्ण

	रेजिस्टर_co_cache_error_notअगरier(&p->notअगरier);

	वापस 0;

err1:
	edac_device_मुक्त_ctl_info(p->ed);
err:
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक co_cache_error_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा co_cache_error *p = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_co_cache_error_notअगरier(&p->notअगरier);
	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(p->ed);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver co_cache_error_driver = अणु
	.probe = co_cache_error_probe,
	.हटाओ = co_cache_error_हटाओ,
	.driver = अणु
		   .name = "octeon_pc_edac",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(co_cache_error_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
