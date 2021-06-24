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

#समावेश "qman_priv.h"

काष्ठा qman_portal *qman_dma_portal;
EXPORT_SYMBOL(qman_dma_portal);

/* Enable portal पूर्णांकerupts (as opposed to polling mode) */
#घोषणा CONFIG_FSL_DPA_PIRQ_SLOW  1
#घोषणा CONFIG_FSL_DPA_PIRQ_FAST  1

अटल काष्ठा cpumask portal_cpus;
अटल पूर्णांक __qman_portals_probed;
/* protect qman global रेजिस्टरs and global data shared among portals */
अटल DEFINE_SPINLOCK(qman_lock);

अटल व्योम portal_set_cpu(काष्ठा qm_portal_config *pcfg, पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_FSL_PAMU
	काष्ठा device *dev = pcfg->dev;
	पूर्णांक ret;

	pcfg->iommu_करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!pcfg->iommu_करोमुख्य) अणु
		dev_err(dev, "%s(): iommu_domain_alloc() failed", __func__);
		जाओ no_iommu;
	पूर्ण
	ret = fsl_pamu_configure_l1_stash(pcfg->iommu_करोमुख्य, cpu);
	अगर (ret < 0) अणु
		dev_err(dev, "%s(): fsl_pamu_configure_l1_stash() = %d",
			__func__, ret);
		जाओ out_करोमुख्य_मुक्त;
	पूर्ण
	ret = iommu_attach_device(pcfg->iommu_करोमुख्य, dev);
	अगर (ret < 0) अणु
		dev_err(dev, "%s(): iommu_device_attach() = %d", __func__,
			ret);
		जाओ out_करोमुख्य_मुक्त;
	पूर्ण

no_iommu:
#पूर्ण_अगर
	qman_set_sdest(pcfg->channel, cpu);

	वापस;

#अगर_घोषित CONFIG_FSL_PAMU
out_करोमुख्य_मुक्त:
	iommu_करोमुख्य_मुक्त(pcfg->iommu_करोमुख्य);
	pcfg->iommu_करोमुख्य = शून्य;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा qman_portal *init_pcfg(काष्ठा qm_portal_config *pcfg)
अणु
	काष्ठा qman_portal *p;
	u32 irq_sources = 0;

	/* We need the same LIODN offset क्रम all portals */
	qman_liodn_fixup(pcfg->channel);

	pcfg->iommu_करोमुख्य = शून्य;
	portal_set_cpu(pcfg, pcfg->cpu);

	p = qman_create_affine_portal(pcfg, शून्य);
	अगर (!p) अणु
		dev_crit(pcfg->dev, "%s: Portal failure on cpu %d\n",
			 __func__, pcfg->cpu);
		वापस शून्य;
	पूर्ण

	/* Determine what should be पूर्णांकerrupt-vs-poll driven */
#अगर_घोषित CONFIG_FSL_DPA_PIRQ_SLOW
	irq_sources |= QM_PIRQ_EQCI | QM_PIRQ_EQRI | QM_PIRQ_MRI |
		       QM_PIRQ_CSCI;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FSL_DPA_PIRQ_FAST
	irq_sources |= QM_PIRQ_DQRI;
#पूर्ण_अगर
	qman_p_irqsource_add(p, irq_sources);

	spin_lock(&qman_lock);
	अगर (cpumask_equal(&portal_cpus, cpu_possible_mask)) अणु
		/* all asचिन्हित portals are initialized now */
		qman_init_cgr_all();
	पूर्ण

	अगर (!qman_dma_portal)
		qman_dma_portal = p;

	spin_unlock(&qman_lock);

	dev_info(pcfg->dev, "Portal initialised, cpu %d\n", pcfg->cpu);

	वापस p;
पूर्ण

अटल व्योम qman_portal_update_sdest(स्थिर काष्ठा qm_portal_config *pcfg,
							अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_FSL_PAMU /* TODO */
	अगर (pcfg->iommu_करोमुख्य) अणु
		अगर (fsl_pamu_configure_l1_stash(pcfg->iommu_करोमुख्य, cpu) < 0) अणु
			dev_err(pcfg->dev,
				"Failed to update pamu stash setting\n");
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	qman_set_sdest(pcfg->channel, cpu);
पूर्ण

अटल पूर्णांक qman_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा qman_portal *p;
	स्थिर काष्ठा qm_portal_config *pcfg;

	p = affine_portals[cpu];
	अगर (p) अणु
		pcfg = qman_get_qm_portal_config(p);
		अगर (pcfg) अणु
			/* select any other online CPU */
			cpu = cpumask_any_but(cpu_online_mask, cpu);
			irq_set_affinity(pcfg->irq, cpumask_of(cpu));
			qman_portal_update_sdest(pcfg, cpu);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qman_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा qman_portal *p;
	स्थिर काष्ठा qm_portal_config *pcfg;

	p = affine_portals[cpu];
	अगर (p) अणु
		pcfg = qman_get_qm_portal_config(p);
		अगर (pcfg) अणु
			irq_set_affinity(pcfg->irq, cpumask_of(cpu));
			qman_portal_update_sdest(pcfg, cpu);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qman_portals_probed(व्योम)
अणु
	वापस __qman_portals_probed;
पूर्ण
EXPORT_SYMBOL_GPL(qman_portals_probed);

अटल पूर्णांक qman_portal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा qm_portal_config *pcfg;
	काष्ठा resource *addr_phys[2];
	पूर्णांक irq, cpu, err, i;
	u32 val;

	err = qman_is_probed();
	अगर (!err)
		वापस -EPROBE_DEFER;
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failing probe due to qman probe error\n");
		वापस -ENODEV;
	पूर्ण

	pcfg = devm_kदो_स्मृति(dev, माप(*pcfg), GFP_KERNEL);
	अगर (!pcfg) अणु
		__qman_portals_probed = -1;
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

	err = of_property_पढ़ो_u32(node, "cell-index", &val);
	अगर (err) अणु
		dev_err(dev, "Can't get %pOF property 'cell-index'\n", node);
		__qman_portals_probed = -1;
		वापस err;
	पूर्ण
	pcfg->channel = val;
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

	pcfg->pools = qm_get_pools_sdqcr();

	spin_lock(&qman_lock);
	cpu = cpumask_next_zero(-1, &portal_cpus);
	अगर (cpu >= nr_cpu_ids) अणु
		__qman_portals_probed = 1;
		/* unasचिन्हित portal, skip init */
		spin_unlock(&qman_lock);
		जाओ check_cleanup;
	पूर्ण

	cpumask_set_cpu(cpu, &portal_cpus);
	spin_unlock(&qman_lock);
	pcfg->cpu = cpu;

	अगर (dma_set_mask(dev, DMA_BIT_MASK(40))) अणु
		dev_err(dev, "dma_set_mask() failed\n");
		जाओ err_portal_init;
	पूर्ण

	अगर (!init_pcfg(pcfg)) अणु
		dev_err(dev, "portal init failed\n");
		जाओ err_portal_init;
	पूर्ण

	/* clear irq affinity अगर asचिन्हित cpu is offline */
	अगर (!cpu_online(cpu))
		qman_offline_cpu(cpu);

check_cleanup:
	अगर (__qman_portals_probed == 1 && qman_requires_cleanup()) अणु
		/*
		 * QMan wasn't reset prior to boot (Kexec क्रम example)
		 * Empty all the frame queues so they are in reset state
		 */
		क्रम (i = 0; i < qm_get_fqid_maxcnt(); i++) अणु
			err =  qman_shutकरोwn_fq(i);
			अगर (err) अणु
				dev_err(dev, "Failed to shutdown frame queue %d\n",
					i);
				जाओ err_portal_init;
			पूर्ण
		पूर्ण
		qman_करोne_cleanup();
	पूर्ण

	वापस 0;

err_portal_init:
	iounmap(pcfg->addr_virt_ci);
err_ioremap2:
	memunmap(pcfg->addr_virt_ce);
err_ioremap1:
	__qman_portals_probed = -1;

	वापस -ENXIO;
पूर्ण

अटल स्थिर काष्ठा of_device_id qman_portal_ids[] = अणु
	अणु
		.compatible = "fsl,qman-portal",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qman_portal_ids);

अटल काष्ठा platक्रमm_driver qman_portal_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = qman_portal_ids,
	पूर्ण,
	.probe = qman_portal_probe,
पूर्ण;

अटल पूर्णांक __init qman_portal_driver_रेजिस्टर(काष्ठा platक्रमm_driver *drv)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(drv);
	अगर (ret < 0)
		वापस ret;

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"soc/qman_portal:online",
					qman_online_cpu, qman_offline_cpu);
	अगर (ret < 0) अणु
		pr_err("qman: failed to register hotplug callbacks.\n");
		platक्रमm_driver_unरेजिस्टर(drv);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

module_driver(qman_portal_driver,
	      qman_portal_driver_रेजिस्टर, platक्रमm_driver_unरेजिस्टर);
