<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Handles hot and cold plug of persistent memory regions on pseries.
 */

#घोषणा pr_fmt(fmt)     "pseries-pmem: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>	/* क्रम idle_task_निकास */
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/topology.h>

#समावेश "pseries.h"

अटल काष्ठा device_node *pmem_node;

अटल sमाप_प्रकार pmem_drc_add_node(u32 drc_index)
अणु
	काष्ठा device_node *dn;
	पूर्णांक rc;

	pr_debug("Attempting to add pmem node, drc index: %x\n", drc_index);

	rc = dlpar_acquire_drc(drc_index);
	अगर (rc) अणु
		pr_err("Failed to acquire DRC, rc: %d, drc index: %x\n",
			rc, drc_index);
		वापस -EINVAL;
	पूर्ण

	dn = dlpar_configure_connector(cpu_to_be32(drc_index), pmem_node);
	अगर (!dn) अणु
		pr_err("configure-connector failed for drc %x\n", drc_index);
		dlpar_release_drc(drc_index);
		वापस -EINVAL;
	पूर्ण

	/* NB: The of reconfig notअगरier creates platक्रमm device from the node */
	rc = dlpar_attach_node(dn, pmem_node);
	अगर (rc) अणु
		pr_err("Failed to attach node %pOF, rc: %d, drc index: %x\n",
			dn, rc, drc_index);

		अगर (dlpar_release_drc(drc_index))
			dlpar_मुक्त_cc_nodes(dn);

		वापस rc;
	पूर्ण

	pr_info("Successfully added %pOF, drc index: %x\n", dn, drc_index);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pmem_drc_हटाओ_node(u32 drc_index)
अणु
	काष्ठा device_node *dn;
	uपूर्णांक32_t index;
	पूर्णांक rc;

	क्रम_each_child_of_node(pmem_node, dn) अणु
		अगर (of_property_पढ़ो_u32(dn, "ibm,my-drc-index", &index))
			जारी;
		अगर (index == drc_index)
			अवरोध;
	पूर्ण

	अगर (!dn) अणु
		pr_err("Attempting to remove unused DRC index %x\n", drc_index);
		वापस -ENODEV;
	पूर्ण

	pr_debug("Attempting to remove %pOF, drc index: %x\n", dn, drc_index);

	/* * NB: tears करोwn the ibm,pmemory device as a side-effect */
	rc = dlpar_detach_node(dn);
	अगर (rc)
		वापस rc;

	rc = dlpar_release_drc(drc_index);
	अगर (rc) अणु
		pr_err("Failed to release drc (%x) for CPU %pOFn, rc: %d\n",
			drc_index, dn, rc);
		dlpar_attach_node(dn, pmem_node);
		वापस rc;
	पूर्ण

	pr_info("Successfully removed PMEM with drc index: %x\n", drc_index);

	वापस 0;
पूर्ण

पूर्णांक dlpar_hp_pmem(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	u32 drc_index;
	पूर्णांक rc;

	/* slim chance, but we might get a hotplug event जबतक booting */
	अगर (!pmem_node)
		pmem_node = of_find_node_by_type(शून्य, "ibm,persistent-memory");
	अगर (!pmem_node) अणु
		pr_err("Hotplug event for a pmem device, but none exists\n");
		वापस -ENODEV;
	पूर्ण

	अगर (hp_elog->id_type != PSERIES_HP_ELOG_ID_DRC_INDEX) अणु
		pr_err("Unsupported hotplug event type %d\n",
				hp_elog->id_type);
		वापस -EINVAL;
	पूर्ण

	drc_index = hp_elog->_drc_u.drc_index;

	lock_device_hotplug();

	अगर (hp_elog->action == PSERIES_HP_ELOG_ACTION_ADD) अणु
		rc = pmem_drc_add_node(drc_index);
	पूर्ण अन्यथा अगर (hp_elog->action == PSERIES_HP_ELOG_ACTION_REMOVE) अणु
		rc = pmem_drc_हटाओ_node(drc_index);
	पूर्ण अन्यथा अणु
		pr_err("Unsupported hotplug action (%d)\n", hp_elog->action);
		rc = -EINVAL;
	पूर्ण

	unlock_device_hotplug();
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा of_device_id drc_pmem_match[] = अणु
	अणु .type = "ibm,persistent-memory", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक pseries_pmem_init(व्योम)
अणु
	/*
	 * Only supported on POWER8 and above.
	 */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस 0;

	pmem_node = of_find_node_by_type(शून्य, "ibm,persistent-memory");
	अगर (!pmem_node)
		वापस 0;

	/*
	 * The generic OF bus probe/populate handles creating platक्रमm devices
	 * from the child (ibm,pmemory) nodes. The generic code रेजिस्टरs an of
	 * reconfig notअगरier to handle the hot-add/हटाओ हालs too.
	 */
	of_platक्रमm_bus_probe(pmem_node, drc_pmem_match, शून्य);

	वापस 0;
पूर्ण
machine_arch_initcall(pseries, pseries_pmem_init);
