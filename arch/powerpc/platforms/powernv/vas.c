<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016-17 IBM Corp.
 */

#घोषणा pr_fmt(fmt) "vas: " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/xive.h>

#समावेश "vas.h"

DEFINE_MUTEX(vas_mutex);
अटल LIST_HEAD(vas_instances);

अटल DEFINE_PER_CPU(पूर्णांक, cpu_vas_id);

अटल पूर्णांक vas_irq_fault_winकरोw_setup(काष्ठा vas_instance *vinst)
अणु
	पूर्णांक rc = 0;

	rc = request_thपढ़ोed_irq(vinst->virq, vas_fault_handler,
				vas_fault_thपढ़ो_fn, 0, vinst->name, vinst);

	अगर (rc) अणु
		pr_err("VAS[%d]: Request IRQ(%d) failed with %d\n",
				vinst->vas_id, vinst->virq, rc);
		जाओ out;
	पूर्ण

	rc = vas_setup_fault_winकरोw(vinst);
	अगर (rc)
		मुक्त_irq(vinst->virq, vinst);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक init_vas_instance(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा vas_instance *vinst;
	काष्ठा xive_irq_data *xd;
	uपूर्णांक32_t chipid, hwirq;
	काष्ठा resource *res;
	पूर्णांक rc, cpu, vasid;

	rc = of_property_पढ़ो_u32(dn, "ibm,vas-id", &vasid);
	अगर (rc) अणु
		pr_err("No ibm,vas-id property for %s?\n", pdev->name);
		वापस -ENODEV;
	पूर्ण

	rc = of_property_पढ़ो_u32(dn, "ibm,chip-id", &chipid);
	अगर (rc) अणु
		pr_err("No ibm,chip-id property for %s?\n", pdev->name);
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->num_resources != 4) अणु
		pr_err("Unexpected DT configuration for [%s, %d]\n",
				pdev->name, vasid);
		वापस -ENODEV;
	पूर्ण

	vinst = kzalloc(माप(*vinst), GFP_KERNEL);
	अगर (!vinst)
		वापस -ENOMEM;

	vinst->name = kaप्र_लिखो(GFP_KERNEL, "vas-%d", vasid);
	अगर (!vinst->name) अणु
		kमुक्त(vinst);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&vinst->node);
	ida_init(&vinst->ida);
	mutex_init(&vinst->mutex);
	vinst->vas_id = vasid;
	vinst->pdev = pdev;

	res = &pdev->resource[0];
	vinst->hvwc_bar_start = res->start;

	res = &pdev->resource[1];
	vinst->uwc_bar_start = res->start;

	res = &pdev->resource[2];
	vinst->paste_base_addr = res->start;

	res = &pdev->resource[3];
	अगर (res->end > 62) अणु
		pr_err("Bad 'paste_win_id_shift' in DT, %llx\n", res->end);
		जाओ मुक्त_vinst;
	पूर्ण

	vinst->paste_win_id_shअगरt = 63 - res->end;

	hwirq = xive_native_alloc_irq_on_chip(chipid);
	अगर (!hwirq) अणु
		pr_err("Inst%d: Unable to allocate global irq for chip %d\n",
				vinst->vas_id, chipid);
		वापस -ENOENT;
	पूर्ण

	vinst->virq = irq_create_mapping(शून्य, hwirq);
	अगर (!vinst->virq) अणु
		pr_err("Inst%d: Unable to map global irq %d\n",
				vinst->vas_id, hwirq);
		वापस -EINVAL;
	पूर्ण

	xd = irq_get_handler_data(vinst->virq);
	अगर (!xd) अणु
		pr_err("Inst%d: Invalid virq %d\n",
				vinst->vas_id, vinst->virq);
		वापस -EINVAL;
	पूर्ण

	vinst->irq_port = xd->trig_page;
	pr_devel("Initialized instance [%s, %d] paste_base 0x%llx paste_win_id_shift 0x%llx IRQ %d Port 0x%llx\n",
			pdev->name, vasid, vinst->paste_base_addr,
			vinst->paste_win_id_shअगरt, vinst->virq,
			vinst->irq_port);

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu_to_chip_id(cpu) == of_get_ibm_chip_id(dn))
			per_cpu(cpu_vas_id, cpu) = vasid;
	पूर्ण

	mutex_lock(&vas_mutex);
	list_add(&vinst->node, &vas_instances);
	mutex_unlock(&vas_mutex);

	spin_lock_init(&vinst->fault_lock);
	/*
	 * IRQ and fault handling setup is needed only क्रम user space
	 * send winकरोws.
	 */
	अगर (vinst->virq) अणु
		rc = vas_irq_fault_winकरोw_setup(vinst);
		/*
		 * Fault winकरोw is used only क्रम user space send winकरोws.
		 * So अगर vinst->virq is शून्य, tx_win_खोलो वापसs -ENODEV
		 * क्रम user space.
		 */
		अगर (rc)
			vinst->virq = 0;
	पूर्ण

	vas_instance_init_dbgdir(vinst);

	dev_set_drvdata(&pdev->dev, vinst);

	वापस 0;

मुक्त_vinst:
	kमुक्त(vinst->name);
	kमुक्त(vinst);
	वापस -ENODEV;

पूर्ण

/*
 * Although this is पढ़ो/used multiple बार, it is written to only
 * during initialization.
 */
काष्ठा vas_instance *find_vas_instance(पूर्णांक vasid)
अणु
	काष्ठा list_head *ent;
	काष्ठा vas_instance *vinst;

	mutex_lock(&vas_mutex);

	अगर (vasid == -1)
		vasid = per_cpu(cpu_vas_id, smp_processor_id());

	list_क्रम_each(ent, &vas_instances) अणु
		vinst = list_entry(ent, काष्ठा vas_instance, node);
		अगर (vinst->vas_id == vasid) अणु
			mutex_unlock(&vas_mutex);
			वापस vinst;
		पूर्ण
	पूर्ण
	mutex_unlock(&vas_mutex);

	pr_devel("Instance %d not found\n", vasid);
	वापस शून्य;
पूर्ण

पूर्णांक chip_to_vas_id(पूर्णांक chipid)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu_to_chip_id(cpu) == chipid)
			वापस per_cpu(cpu_vas_id, cpu);
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL(chip_to_vas_id);

अटल पूर्णांक vas_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस init_vas_instance(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id घातernv_vas_match[] = अणु
	अणु .compatible = "ibm,vas",पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver vas_driver = अणु
	.driver = अणु
		.name = "vas",
		.of_match_table = घातernv_vas_match,
	पूर्ण,
	.probe = vas_probe,
पूर्ण;

अटल पूर्णांक __init vas_init(व्योम)
अणु
	पूर्णांक found = 0;
	काष्ठा device_node *dn;

	platक्रमm_driver_रेजिस्टर(&vas_driver);

	क्रम_each_compatible_node(dn, शून्य, "ibm,vas") अणु
		of_platक्रमm_device_create(dn, शून्य, शून्य);
		found++;
	पूर्ण

	अगर (!found) अणु
		platक्रमm_driver_unरेजिस्टर(&vas_driver);
		वापस -ENODEV;
	पूर्ण

	pr_devel("Found %d instances\n", found);

	वापस 0;
पूर्ण
device_initcall(vas_init);
