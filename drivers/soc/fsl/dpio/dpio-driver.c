<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright NXP 2016
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/msi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/sys_soc.h>

#समावेश <linux/fsl/mc.h>
#समावेश <soc/fsl/dpaa2-पन.स>

#समावेश "qbman-portal.h"
#समावेश "dpio.h"
#समावेश "dpio-cmd.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Freescale Semiconductor, Inc");
MODULE_DESCRIPTION("DPIO Driver");

काष्ठा dpio_priv अणु
	काष्ठा dpaa2_io *io;
पूर्ण;

अटल cpumask_var_t cpus_unused_mask;

अटल स्थिर काष्ठा soc_device_attribute ls1088a_soc[] = अणु
	अणु.family = "QorIQ LS1088A"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute ls2080a_soc[] = अणु
	अणु.family = "QorIQ LS2080A"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute ls2088a_soc[] = अणु
	अणु.family = "QorIQ LS2088A"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute lx2160a_soc[] = अणु
	अणु.family = "QorIQ LX2160A"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक dpaa2_dpio_get_cluster_sdest(काष्ठा fsl_mc_device *dpio_dev, पूर्णांक cpu)
अणु
	पूर्णांक cluster_base, cluster_size;

	अगर (soc_device_match(ls1088a_soc)) अणु
		cluster_base = 2;
		cluster_size = 4;
	पूर्ण अन्यथा अगर (soc_device_match(ls2080a_soc) ||
		   soc_device_match(ls2088a_soc) ||
		   soc_device_match(lx2160a_soc)) अणु
		cluster_base = 0;
		cluster_size = 2;
	पूर्ण अन्यथा अणु
		dev_err(&dpio_dev->dev, "unknown SoC version\n");
		वापस -1;
	पूर्ण

	वापस cluster_base + cpu / cluster_size;
पूर्ण

अटल irqवापस_t dpio_irq_handler(पूर्णांक irq_num, व्योम *arg)
अणु
	काष्ठा device *dev = (काष्ठा device *)arg;
	काष्ठा dpio_priv *priv = dev_get_drvdata(dev);

	वापस dpaa2_io_irq(priv->io);
पूर्ण

अटल व्योम unरेजिस्टर_dpio_irq_handlers(काष्ठा fsl_mc_device *dpio_dev)
अणु
	काष्ठा fsl_mc_device_irq *irq;

	irq = dpio_dev->irqs[0];

	/* clear the affinity hपूर्णांक */
	irq_set_affinity_hपूर्णांक(irq->msi_desc->irq, शून्य);
पूर्ण

अटल पूर्णांक रेजिस्टर_dpio_irq_handlers(काष्ठा fsl_mc_device *dpio_dev, पूर्णांक cpu)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_device_irq *irq;

	irq = dpio_dev->irqs[0];
	error = devm_request_irq(&dpio_dev->dev,
				 irq->msi_desc->irq,
				 dpio_irq_handler,
				 0,
				 dev_name(&dpio_dev->dev),
				 &dpio_dev->dev);
	अगर (error < 0) अणु
		dev_err(&dpio_dev->dev,
			"devm_request_irq() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	/* set the affinity hपूर्णांक */
	अगर (irq_set_affinity_hपूर्णांक(irq->msi_desc->irq, cpumask_of(cpu)))
		dev_err(&dpio_dev->dev,
			"irq_set_affinity failed irq %d cpu %d\n",
			irq->msi_desc->irq, cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_dpio_probe(काष्ठा fsl_mc_device *dpio_dev)
अणु
	काष्ठा dpio_attr dpio_attrs;
	काष्ठा dpaa2_io_desc desc;
	काष्ठा dpio_priv *priv;
	पूर्णांक err = -ENOMEM;
	काष्ठा device *dev = &dpio_dev->dev;
	पूर्णांक possible_next_cpu;
	पूर्णांक sdest;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		जाओ err_priv_alloc;

	dev_set_drvdata(dev, priv);

	err = fsl_mc_portal_allocate(dpio_dev, 0, &dpio_dev->mc_io);
	अगर (err) अणु
		dev_dbg(dev, "MC portal allocation failed\n");
		err = -EPROBE_DEFER;
		जाओ err_priv_alloc;
	पूर्ण

	err = dpio_खोलो(dpio_dev->mc_io, 0, dpio_dev->obj_desc.id,
			&dpio_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpio_open() failed\n");
		जाओ err_खोलो;
	पूर्ण

	err = dpio_reset(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpio_reset() failed\n");
		जाओ err_reset;
	पूर्ण

	err = dpio_get_attributes(dpio_dev->mc_io, 0, dpio_dev->mc_handle,
				  &dpio_attrs);
	अगर (err) अणु
		dev_err(dev, "dpio_get_attributes() failed %d\n", err);
		जाओ err_get_attr;
	पूर्ण
	desc.qman_version = dpio_attrs.qbman_version;

	err = dpio_enable(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpio_enable() failed %d\n", err);
		जाओ err_get_attr;
	पूर्ण

	/* initialize DPIO descriptor */
	desc.receives_notअगरications = dpio_attrs.num_priorities ? 1 : 0;
	desc.has_8prio = dpio_attrs.num_priorities == 8 ? 1 : 0;
	desc.dpio_id = dpio_dev->obj_desc.id;

	/* get the cpu to use क्रम the affinity hपूर्णांक */
	possible_next_cpu = cpumask_first(cpus_unused_mask);
	अगर (possible_next_cpu >= nr_cpu_ids) अणु
		dev_err(dev, "probe failed. Number of DPIOs exceeds NR_CPUS.\n");
		err = -दुस्फल;
		जाओ err_allocate_irqs;
	पूर्ण
	desc.cpu = possible_next_cpu;
	cpumask_clear_cpu(possible_next_cpu, cpus_unused_mask);

	sdest = dpaa2_dpio_get_cluster_sdest(dpio_dev, desc.cpu);
	अगर (sdest >= 0) अणु
		err = dpio_set_stashing_destination(dpio_dev->mc_io, 0,
						    dpio_dev->mc_handle,
						    sdest);
		अगर (err)
			dev_err(dev, "dpio_set_stashing_destination failed for cpu%d\n",
				desc.cpu);
	पूर्ण

	अगर (dpio_dev->obj_desc.region_count < 3) अणु
		/* No support क्रम DDR backed portals, use classic mapping */
		/*
		 * Set the CENA regs to be the cache inhibited area of the
		 * portal to aव्योम coherency issues अगर a user migrates to
		 * another core.
		 */
		desc.regs_cena = devm_memremap(dev, dpio_dev->regions[1].start,
					resource_size(&dpio_dev->regions[1]),
					MEMREMAP_WC);
	पूर्ण अन्यथा अणु
		desc.regs_cena = devm_memremap(dev, dpio_dev->regions[2].start,
					resource_size(&dpio_dev->regions[2]),
					MEMREMAP_WB);
	पूर्ण

	अगर (IS_ERR(desc.regs_cena)) अणु
		dev_err(dev, "devm_memremap failed\n");
		err = PTR_ERR(desc.regs_cena);
		जाओ err_allocate_irqs;
	पूर्ण

	desc.regs_cinh = devm_ioremap(dev, dpio_dev->regions[1].start,
				      resource_size(&dpio_dev->regions[1]));
	अगर (!desc.regs_cinh) अणु
		err = -ENOMEM;
		dev_err(dev, "devm_ioremap failed\n");
		जाओ err_allocate_irqs;
	पूर्ण

	err = fsl_mc_allocate_irqs(dpio_dev);
	अगर (err) अणु
		dev_err(dev, "fsl_mc_allocate_irqs failed. err=%d\n", err);
		जाओ err_allocate_irqs;
	पूर्ण

	priv->io = dpaa2_io_create(&desc, dev);
	अगर (!priv->io) अणु
		dev_err(dev, "dpaa2_io_create failed\n");
		err = -ENOMEM;
		जाओ err_dpaa2_io_create;
	पूर्ण

	err = रेजिस्टर_dpio_irq_handlers(dpio_dev, desc.cpu);
	अगर (err)
		जाओ err_रेजिस्टर_dpio_irq;

	dev_info(dev, "probed\n");
	dev_dbg(dev, "   receives_notifications = %d\n",
		desc.receives_notअगरications);
	dpio_बंद(dpio_dev->mc_io, 0, dpio_dev->mc_handle);

	वापस 0;

err_dpaa2_io_create:
	unरेजिस्टर_dpio_irq_handlers(dpio_dev);
err_रेजिस्टर_dpio_irq:
	fsl_mc_मुक्त_irqs(dpio_dev);
err_allocate_irqs:
	dpio_disable(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
err_get_attr:
err_reset:
	dpio_बंद(dpio_dev->mc_io, 0, dpio_dev->mc_handle);
err_खोलो:
	fsl_mc_portal_मुक्त(dpio_dev->mc_io);
err_priv_alloc:
	वापस err;
पूर्ण

/* Tear करोwn पूर्णांकerrupts क्रम a given DPIO object */
अटल व्योम dpio_tearकरोwn_irqs(काष्ठा fsl_mc_device *dpio_dev)
अणु
	unरेजिस्टर_dpio_irq_handlers(dpio_dev);
	fsl_mc_मुक्त_irqs(dpio_dev);
पूर्ण

अटल पूर्णांक dpaa2_dpio_हटाओ(काष्ठा fsl_mc_device *dpio_dev)
अणु
	काष्ठा device *dev;
	काष्ठा dpio_priv *priv;
	पूर्णांक err = 0, cpu;

	dev = &dpio_dev->dev;
	priv = dev_get_drvdata(dev);
	cpu = dpaa2_io_get_cpu(priv->io);

	dpaa2_io_करोwn(priv->io);

	dpio_tearकरोwn_irqs(dpio_dev);

	cpumask_set_cpu(cpu, cpus_unused_mask);

	err = dpio_खोलो(dpio_dev->mc_io, 0, dpio_dev->obj_desc.id,
			&dpio_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpio_open() failed\n");
		जाओ err_खोलो;
	पूर्ण

	dpio_disable(dpio_dev->mc_io, 0, dpio_dev->mc_handle);

	dpio_बंद(dpio_dev->mc_io, 0, dpio_dev->mc_handle);

	fsl_mc_portal_मुक्त(dpio_dev->mc_io);

	वापस 0;

err_खोलो:
	fsl_mc_portal_मुक्त(dpio_dev->mc_io);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा fsl_mc_device_id dpaa2_dpio_match_id_table[] = अणु
	अणु
		.venकरोr = FSL_MC_VENDOR_FREESCALE,
		.obj_type = "dpio",
	पूर्ण,
	अणु .venकरोr = 0x0 पूर्ण
पूर्ण;

अटल काष्ठा fsl_mc_driver dpaa2_dpio_driver = अणु
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.owner		= THIS_MODULE,
	पूर्ण,
	.probe		= dpaa2_dpio_probe,
	.हटाओ		= dpaa2_dpio_हटाओ,
	.match_id_table = dpaa2_dpio_match_id_table
पूर्ण;

अटल पूर्णांक dpio_driver_init(व्योम)
अणु
	अगर (!zalloc_cpumask_var(&cpus_unused_mask, GFP_KERNEL))
		वापस -ENOMEM;
	cpumask_copy(cpus_unused_mask, cpu_online_mask);

	वापस fsl_mc_driver_रेजिस्टर(&dpaa2_dpio_driver);
पूर्ण

अटल व्योम dpio_driver_निकास(व्योम)
अणु
	मुक्त_cpumask_var(cpus_unused_mask);
	fsl_mc_driver_unरेजिस्टर(&dpaa2_dpio_driver);
पूर्ण
module_init(dpio_driver_init);
module_निकास(dpio_driver_निकास);
