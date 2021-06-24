<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OPAL IMC पूर्णांकerface detection driver
 * Supported on POWERNV platक्रमm
 *
 * Copyright	(C) 2017 Madhavan Srinivasan, IBM Corporation.
 *		(C) 2017 Anju T Sudhakar, IBM Corporation.
 *		(C) 2017 Hemant K Shaw, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/crash_dump.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/imc-pmu.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/debugfs.h>

अटल काष्ठा dentry *imc_debugfs_parent;

/* Helpers to export imc command and mode via debugfs */
अटल पूर्णांक imc_mem_get(व्योम *data, u64 *val)
अणु
	*val = cpu_to_be64(*(u64 *)data);
	वापस 0;
पूर्ण

अटल पूर्णांक imc_mem_set(व्योम *data, u64 val)
अणु
	*(u64 *)data = cpu_to_be64(val);
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_imc_x64, imc_mem_get, imc_mem_set, "0x%016llx\n");

अटल व्योम imc_debugfs_create_x64(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, u64  *value)
अणु
	debugfs_create_file_unsafe(name, mode, parent, value, &fops_imc_x64);
पूर्ण

/*
 * export_imc_mode_and_cmd: Create a debugfs पूर्णांकerface
 *                     क्रम imc_cmd and imc_mode
 *                     क्रम each node in the प्रणाली.
 *  imc_mode and imc_cmd can be changed by echo पूर्णांकo
 *  this पूर्णांकerface.
 */
अटल व्योम export_imc_mode_and_cmd(काष्ठा device_node *node,
				    काष्ठा imc_pmu *pmu_ptr)
अणु
	अटल u64 loc, *imc_mode_addr, *imc_cmd_addr;
	अक्षर mode[16], cmd[16];
	u32 cb_offset;
	काष्ठा imc_mem_info *ptr = pmu_ptr->mem_info;

	imc_debugfs_parent = debugfs_create_dir("imc", घातerpc_debugfs_root);

	अगर (of_property_पढ़ो_u32(node, "cb_offset", &cb_offset))
		cb_offset = IMC_CNTL_BLK_OFFSET;

	जबतक (ptr->vbase != शून्य) अणु
		loc = (u64)(ptr->vbase) + cb_offset;
		imc_mode_addr = (u64 *)(loc + IMC_CNTL_BLK_MODE_OFFSET);
		प्र_लिखो(mode, "imc_mode_%d", (u32)(ptr->id));
		imc_debugfs_create_x64(mode, 0600, imc_debugfs_parent,
				       imc_mode_addr);

		imc_cmd_addr = (u64 *)(loc + IMC_CNTL_BLK_CMD_OFFSET);
		प्र_लिखो(cmd, "imc_cmd_%d", (u32)(ptr->id));
		imc_debugfs_create_x64(cmd, 0600, imc_debugfs_parent,
				       imc_cmd_addr);
		ptr++;
	पूर्ण
पूर्ण

/*
 * imc_get_mem_addr_nest: Function to get nest counter memory region
 * क्रम each chip
 */
अटल पूर्णांक imc_get_mem_addr_nest(काष्ठा device_node *node,
				 काष्ठा imc_pmu *pmu_ptr,
				 u32 offset)
अणु
	पूर्णांक nr_chips = 0, i;
	u64 *base_addr_arr, baddr;
	u32 *chipid_arr;

	nr_chips = of_property_count_u32_elems(node, "chip-id");
	अगर (nr_chips <= 0)
		वापस -ENODEV;

	base_addr_arr = kसुस्मृति(nr_chips, माप(*base_addr_arr), GFP_KERNEL);
	अगर (!base_addr_arr)
		वापस -ENOMEM;

	chipid_arr = kसुस्मृति(nr_chips, माप(*chipid_arr), GFP_KERNEL);
	अगर (!chipid_arr) अणु
		kमुक्त(base_addr_arr);
		वापस -ENOMEM;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(node, "chip-id", chipid_arr, nr_chips))
		जाओ error;

	अगर (of_property_पढ़ो_u64_array(node, "base-addr", base_addr_arr,
								nr_chips))
		जाओ error;

	pmu_ptr->mem_info = kसुस्मृति(nr_chips + 1, माप(*pmu_ptr->mem_info),
				    GFP_KERNEL);
	अगर (!pmu_ptr->mem_info)
		जाओ error;

	क्रम (i = 0; i < nr_chips; i++) अणु
		pmu_ptr->mem_info[i].id = chipid_arr[i];
		baddr = base_addr_arr[i] + offset;
		pmu_ptr->mem_info[i].vbase = phys_to_virt(baddr);
	पूर्ण

	pmu_ptr->imc_counter_mmaped = true;
	kमुक्त(base_addr_arr);
	kमुक्त(chipid_arr);
	वापस 0;

error:
	kमुक्त(base_addr_arr);
	kमुक्त(chipid_arr);
	वापस -1;
पूर्ण

/*
 * imc_pmu_create : Takes the parent device which is the pmu unit, pmu_index
 *		    and करोमुख्य as the inमाला_दो.
 * Allocates memory क्रम the काष्ठा imc_pmu, sets up its करोमुख्य, size and offsets
 */
अटल काष्ठा imc_pmu *imc_pmu_create(काष्ठा device_node *parent, पूर्णांक pmu_index, पूर्णांक करोमुख्य)
अणु
	पूर्णांक ret = 0;
	काष्ठा imc_pmu *pmu_ptr;
	u32 offset;

	/* Return क्रम unknown करोमुख्य */
	अगर (करोमुख्य < 0)
		वापस शून्य;

	/* memory क्रम pmu */
	pmu_ptr = kzalloc(माप(*pmu_ptr), GFP_KERNEL);
	अगर (!pmu_ptr)
		वापस शून्य;

	/* Set the करोमुख्य */
	pmu_ptr->करोमुख्य = करोमुख्य;

	ret = of_property_पढ़ो_u32(parent, "size", &pmu_ptr->counter_mem_size);
	अगर (ret)
		जाओ मुक्त_pmu;

	अगर (!of_property_पढ़ो_u32(parent, "offset", &offset)) अणु
		अगर (imc_get_mem_addr_nest(parent, pmu_ptr, offset))
			जाओ मुक्त_pmu;
	पूर्ण

	/* Function to रेजिस्टर IMC pmu */
	ret = init_imc_pmu(parent, pmu_ptr, pmu_index);
	अगर (ret) अणु
		pr_err("IMC PMU %s Register failed\n", pmu_ptr->pmu.name);
		kमुक्त(pmu_ptr->pmu.name);
		अगर (pmu_ptr->करोमुख्य == IMC_DOMAIN_NEST)
			kमुक्त(pmu_ptr->mem_info);
		kमुक्त(pmu_ptr);
		वापस शून्य;
	पूर्ण

	वापस pmu_ptr;

मुक्त_pmu:
	kमुक्त(pmu_ptr);
	वापस शून्य;
पूर्ण

अटल व्योम disable_nest_pmu_counters(व्योम)
अणु
	पूर्णांक nid, cpu;
	स्थिर काष्ठा cpumask *l_cpumask;

	get_online_cpus();
	क्रम_each_node_with_cpus(nid) अणु
		l_cpumask = cpumask_of_node(nid);
		cpu = cpumask_first_and(l_cpumask, cpu_online_mask);
		अगर (cpu >= nr_cpu_ids)
			जारी;
		opal_imc_counters_stop(OPAL_IMC_COUNTERS_NEST,
				       get_hard_smp_processor_id(cpu));
	पूर्ण
	put_online_cpus();
पूर्ण

अटल व्योम disable_core_pmu_counters(व्योम)
अणु
	cpumask_t cores_map;
	पूर्णांक cpu, rc;

	get_online_cpus();
	/* Disable the IMC Core functions */
	cores_map = cpu_online_cores_map();
	क्रम_each_cpu(cpu, &cores_map) अणु
		rc = opal_imc_counters_stop(OPAL_IMC_COUNTERS_CORE,
					    get_hard_smp_processor_id(cpu));
		अगर (rc)
			pr_err("%s: Failed to stop Core (cpu = %d)\n",
				__FUNCTION__, cpu);
	पूर्ण
	put_online_cpus();
पूर्ण

पूर्णांक get_max_nest_dev(व्योम)
अणु
	काष्ठा device_node *node;
	u32 pmu_units = 0, type;

	क्रम_each_compatible_node(node, शून्य, IMC_DTB_UNIT_COMPAT) अणु
		अगर (of_property_पढ़ो_u32(node, "type", &type))
			जारी;

		अगर (type == IMC_TYPE_CHIP)
			pmu_units++;
	पूर्ण

	वापस pmu_units;
पूर्ण

अटल पूर्णांक opal_imc_counters_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *imc_dev = pdev->dev.of_node;
	काष्ठा imc_pmu *pmu;
	पूर्णांक pmu_count = 0, करोमुख्य;
	bool core_imc_reg = false, thपढ़ो_imc_reg = false;
	u32 type;

	/*
	 * Check whether this is kdump kernel. If yes, क्रमce the engines to
	 * stop and वापस.
	 */
	अगर (is_kdump_kernel()) अणु
		disable_nest_pmu_counters();
		disable_core_pmu_counters();
		वापस -ENODEV;
	पूर्ण

	क्रम_each_compatible_node(imc_dev, शून्य, IMC_DTB_UNIT_COMPAT) अणु
		pmu = शून्य;
		अगर (of_property_पढ़ो_u32(imc_dev, "type", &type)) अणु
			pr_warn("IMC Device without type property\n");
			जारी;
		पूर्ण

		चयन (type) अणु
		हाल IMC_TYPE_CHIP:
			करोमुख्य = IMC_DOMAIN_NEST;
			अवरोध;
		हाल IMC_TYPE_CORE:
			करोमुख्य =IMC_DOMAIN_CORE;
			अवरोध;
		हाल IMC_TYPE_THREAD:
			करोमुख्य = IMC_DOMAIN_THREAD;
			अवरोध;
		हाल IMC_TYPE_TRACE:
			करोमुख्य = IMC_DOMAIN_TRACE;
			अवरोध;
		शेष:
			pr_warn("IMC Unknown Device type \n");
			करोमुख्य = -1;
			अवरोध;
		पूर्ण

		pmu = imc_pmu_create(imc_dev, pmu_count, करोमुख्य);
		अगर (pmu != शून्य) अणु
			अगर (करोमुख्य == IMC_DOMAIN_NEST) अणु
				अगर (!imc_debugfs_parent)
					export_imc_mode_and_cmd(imc_dev, pmu);
				pmu_count++;
			पूर्ण
			अगर (करोमुख्य == IMC_DOMAIN_CORE)
				core_imc_reg = true;
			अगर (करोमुख्य == IMC_DOMAIN_THREAD)
				thपढ़ो_imc_reg = true;
		पूर्ण
	पूर्ण

	/* If core imc is not रेजिस्टरed, unरेजिस्टर thपढ़ो-imc */
	अगर (!core_imc_reg && thपढ़ो_imc_reg)
		unरेजिस्टर_thपढ़ो_imc();

	वापस 0;
पूर्ण

अटल व्योम opal_imc_counters_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * Function only stops the engines which is bare minimum.
	 * TODO: Need to handle proper memory cleanup and pmu
	 * unरेजिस्टर.
	 */
	disable_nest_pmu_counters();
	disable_core_pmu_counters();
पूर्ण

अटल स्थिर काष्ठा of_device_id opal_imc_match[] = अणु
	अणु .compatible = IMC_DTB_COMPAT पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver opal_imc_driver = अणु
	.driver = अणु
		.name = "opal-imc-counters",
		.of_match_table = opal_imc_match,
	पूर्ण,
	.probe = opal_imc_counters_probe,
	.shutकरोwn = opal_imc_counters_shutकरोwn,
पूर्ण;

builtin_platक्रमm_driver(opal_imc_driver);
