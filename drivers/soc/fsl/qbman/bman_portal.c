<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "bman_priv.h"

अटल काष्ठा bman_portal *affine_bportals[NR_CPUS];
अटल काष्ठा cpumask portal_cpus;
अटल पूर्णांक __bman_portals_probed;
/* protect bman global रेजिस्टरs and global data shared among portals */
अटल DEFINE_SPINLOCK(bman_lock);

अटल काष्ठा bman_portal *init_pcfg(काष्ठा bm_portal_config *pcfg)
अणु
	काष्ठा bman_portal *p = bman_create_affine_portal(pcfg);

	अगर (!p) अणु
		dev_crit(pcfg->dev, "%s: Portal failure on cpu %d\n",
			 __func__, pcfg->cpu);
		वापस शून्य;
	पूर्ण

	bman_p_irqsource_add(p, BM_PIRQ_RCRI);
	affine_bportals[pcfg->cpu] = p;

	dev_info(pcfg->dev, "Portal initialised, cpu %d\n", pcfg->cpu);

	वापस p;
पूर्ण

अटल पूर्णांक bman_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा bman_portal *p = affine_bportals[cpu];
	स्थिर काष्ठा bm_portal_config *pcfg;

	अगर (!p)
		वापस 0;

	pcfg = bman_get_bm_portal_config(p);
	अगर (!pcfg)
		वापस 0;

	/* use any other online CPU */
	cpu = cpumask_any_but(cpu_online_mask, cpu);
	irq_set_affinity(pcfg->irq, cpumask_of(cpu));
	वापस 0;
पूर्ण

अटल पूर्णांक bman_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा bman_portal *p = affine_bportals[cpu];
	स्थिर काष्ठा bm_portal_config *pcfg;

	अगर (!p)
		वापस 0;

	pcfg = bman_get_bm_portal_config(p);
	अगर (!pcfg)
		वापस 0;

	irq_set_affinity(pcfg->irq, cpumask_of(cpu));
	वापस 0;
पूर्ण

पूर्णांक bman_portals_probed(व्योम)
अणु
	वापस __bman_portals_probed;
पूर्ण
EXPORT_SYMBOL_GPL(bman_portals_probed);

अटल पूर्णांक bman_portal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा bm_portal_config *pcfg;
	काष्ठा resource *addr_phys[2];
	पूर्णांक irq, cpu, err, i;

	err = bman_is_probed();
	अगर (!err)
		वापस -EPROBE_DEFER;
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failing probe due to bman probe error\n");
		वापस -ENODEV;
	पूर्ण

	pcfg = devm_kदो_स्मृति(dev, माप(*pcfg), GFP_KERNEL);
	अगर (!pcfg) अणु
		__bman_portals_probed = -1;
		वापस -ENOMEM;
	पूर्ण

	pcfg->dev = dev;

	addr_phys[0] = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
					     DPAA_PORTAL_CE);
	अगर (!addr_phys[0]) अणु
		dev_err(dev, "Can't get %pOF property 'reg::CE'\n", node);
		जाओ err_ioremap1;
	पूर्ण

	addr_phys[1] = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
					     DPAA_PORTAL_CI);
	अगर (!addr_phys[1]) अणु
		dev_err(dev, "Can't get %pOF property 'reg::CI'\n", node);
		जाओ err_ioremap1;
	पूर्ण

	pcfg->cpu = -1;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		जाओ err_ioremap1;
	pcfg->irq = irq;

	pcfg->addr_virt_ce = memremap(addr_phys[0]->start,
					resource_size(addr_phys[0]),
					QBMAN_MEMREMAP_ATTR);
	अगर (!pcfg->addr_virt_ce) अणु
		dev_err(dev, "memremap::CE failed\n");
		जाओ err_ioremap1;
	पूर्ण

	pcfg->addr_virt_ci = ioremap(addr_phys[1]->start,
					resource_size(addr_phys[1]));
	अगर (!pcfg->addr_virt_ci) अणु
		dev_err(dev, "ioremap::CI failed\n");
		जाओ err_ioremap2;
	पूर्ण

	spin_lock(&bman_lock);
	cpu = cpumask_next_zero(-1, &portal_cpus);
	अगर (cpu >= nr_cpu_ids) अणु
		__bman_portals_probed = 1;
		/* unasचिन्हित portal, skip init */
		spin_unlock(&bman_lock);
		जाओ check_cleanup;
	पूर्ण

	cpumask_set_cpu(cpu, &portal_cpus);
	spin_unlock(&bman_lock);
	pcfg->cpu = cpu;

	अगर (!init_pcfg(pcfg)) अणु
		dev_err(dev, "portal init failed\n");
		जाओ err_portal_init;
	पूर्ण

	/* clear irq affinity अगर asचिन्हित cpu is offline */
	अगर (!cpu_online(cpu))
		bman_offline_cpu(cpu);

check_cleanup:
	अगर (__bman_portals_probed == 1 && bman_requires_cleanup()) अणु
		/*
		 * BMan wasn't reset prior to boot (Kexec क्रम example)
		 * Empty all the buffer pools so they are in reset state
		 */
		क्रम (i = 0; i < BM_POOL_MAX; i++) अणु
			err =  bm_shutकरोwn_pool(i);
			अगर (err) अणु
				dev_err(dev, "Failed to shutdown bpool %d\n",
					i);
				जाओ err_portal_init;
			पूर्ण
		पूर्ण
		bman_करोne_cleanup();
	पूर्ण

	वापस 0;

err_portal_init:
	iounmap(pcfg->addr_virt_ci);
err_ioremap2:
	memunmap(pcfg->addr_virt_ce);
err_ioremap1:
	 __bman_portals_probed = -1;

	वापस -ENXIO;
पूर्ण

अटल स्थिर काष्ठा of_device_id bman_portal_ids[] = अणु
	अणु
		.compatible = "fsl,bman-portal",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bman_portal_ids);

अटल काष्ठा platक्रमm_driver bman_portal_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = bman_portal_ids,
	पूर्ण,
	.probe = bman_portal_probe,
पूर्ण;

अटल पूर्णांक __init bman_portal_driver_रेजिस्टर(काष्ठा platक्रमm_driver *drv)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(drv);
	अगर (ret < 0)
		वापस ret;

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"soc/qbman_portal:online",
					bman_online_cpu, bman_offline_cpu);
	अगर (ret < 0) अणु
		pr_err("bman: failed to register hotplug callbacks.\n");
		platक्रमm_driver_unरेजिस्टर(drv);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

module_driver(bman_portal_driver,
	      bman_portal_driver_रेजिस्टर, platक्रमm_driver_unरेजिस्टर);
