<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

/**
 * DOC: Enclave lअगरeसमय management driver क्रम Nitro Enclaves (NE).
 * Nitro is a hypervisor that has been developed by Amazon.
 */

#समावेश <linux/anon_inodes.h>
#समावेश <linux/capability.h>
#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nitro_enclaves.h>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/vm_sockets.h>

#समावेश "ne_misc_dev.h"
#समावेश "ne_pci_dev.h"

/**
 * NE_CPUS_SIZE - Size क्रम max 128 CPUs, क्रम now, in a cpu-list string, comma
 *		  separated. The NE CPU pool includes CPUs from a single NUMA
 *		  node.
 */
#घोषणा NE_CPUS_SIZE		(512)

/**
 * NE_EIF_LOAD_OFFSET - The offset where to copy the Enclave Image Format (EIF)
 *			image in enclave memory.
 */
#घोषणा NE_EIF_LOAD_OFFSET	(8 * 1024UL * 1024UL)

/**
 * NE_MIN_ENCLAVE_MEM_SIZE - The minimum memory size an enclave can be launched
 *			     with.
 */
#घोषणा NE_MIN_ENCLAVE_MEM_SIZE	(64 * 1024UL * 1024UL)

/**
 * NE_MIN_MEM_REGION_SIZE - The minimum size of an enclave memory region.
 */
#घोषणा NE_MIN_MEM_REGION_SIZE	(2 * 1024UL * 1024UL)

/**
 * NE_PARENT_VM_CID - The CID क्रम the vsock device of the primary / parent VM.
 */
#घोषणा NE_PARENT_VM_CID	(3)

अटल दीर्घ ne_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

अटल स्थिर काष्ठा file_operations ne_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= noop_llseek,
	.unlocked_ioctl	= ne_ioctl,
पूर्ण;

अटल काष्ठा miscdevice ne_misc_dev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "nitro_enclaves",
	.fops	= &ne_fops,
	.mode	= 0660,
पूर्ण;

काष्ठा ne_devs ne_devs = अणु
	.ne_misc_dev	= &ne_misc_dev,
पूर्ण;

/*
 * TODO: Update logic to create new sysfs entries instead of using
 * a kernel parameter e.g. अगर multiple sysfs files needed.
 */
अटल पूर्णांक ne_set_kernel_param(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);

अटल स्थिर काष्ठा kernel_param_ops ne_cpu_pool_ops = अणु
	.get	= param_get_string,
	.set	= ne_set_kernel_param,
पूर्ण;

अटल अक्षर ne_cpus[NE_CPUS_SIZE];
अटल काष्ठा kparam_string ne_cpus_arg = अणु
	.maxlen	= माप(ne_cpus),
	.string	= ne_cpus,
पूर्ण;

module_param_cb(ne_cpus, &ne_cpu_pool_ops, &ne_cpus_arg, 0644);
/* https://www.kernel.org/करोc/hपंचांगl/latest/admin-guide/kernel-parameters.hपंचांगl#cpu-lists */
MODULE_PARM_DESC(ne_cpus, "<cpu-list> - CPU pool used for Nitro Enclaves");

/**
 * काष्ठा ne_cpu_pool - CPU pool used क्रम Nitro Enclaves.
 * @avail_thपढ़ोs_per_core:	Available full CPU cores to be dedicated to
 *				enclave(s). The cpumasks from the array, indexed
 *				by core id, contain all the thपढ़ोs from the
 *				available cores, that are not set क्रम created
 *				enclave(s). The full CPU cores are part of the
 *				NE CPU pool.
 * @mutex:			Mutex क्रम the access to the NE CPU pool.
 * @nr_parent_vm_cores :	The size of the available thपढ़ोs per core array.
 *				The total number of CPU cores available on the
 *				primary / parent VM.
 * @nr_thपढ़ोs_per_core:	The number of thपढ़ोs that a full CPU core has.
 * @numa_node:			NUMA node of the CPUs in the pool.
 */
काष्ठा ne_cpu_pool अणु
	cpumask_var_t	*avail_thपढ़ोs_per_core;
	काष्ठा mutex	mutex;
	अचिन्हित पूर्णांक	nr_parent_vm_cores;
	अचिन्हित पूर्णांक	nr_thपढ़ोs_per_core;
	पूर्णांक		numa_node;
पूर्ण;

अटल काष्ठा ne_cpu_pool ne_cpu_pool;

/**
 * ne_check_enclaves_created() - Verअगरy अगर at least one enclave has been created.
 * @व्योम:	No parameters provided.
 *
 * Context: Process context.
 * Return:
 * * True अगर at least one enclave is created.
 * * False otherwise.
 */
अटल bool ne_check_enclaves_created(व्योम)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = ne_devs.ne_pci_dev;
	bool ret = false;

	अगर (!ne_pci_dev)
		वापस ret;

	mutex_lock(&ne_pci_dev->enclaves_list_mutex);

	अगर (!list_empty(&ne_pci_dev->enclaves_list))
		ret = true;

	mutex_unlock(&ne_pci_dev->enclaves_list_mutex);

	वापस ret;
पूर्ण

/**
 * ne_setup_cpu_pool() - Set the NE CPU pool after handling sanity checks such
 *			 as not sharing CPU cores with the primary / parent VM
 *			 or not using CPU 0, which should reमुख्य available क्रम
 *			 the primary / parent VM. Offline the CPUs from the
 *			 pool after the checks passed.
 * @ne_cpu_list:	The CPU list used क्रम setting NE CPU pool.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_setup_cpu_pool(स्थिर अक्षर *ne_cpu_list)
अणु
	पूर्णांक core_id = -1;
	अचिन्हित पूर्णांक cpu = 0;
	cpumask_var_t cpu_pool;
	अचिन्हित पूर्णांक cpu_sibling = 0;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक numa_node = -1;
	पूर्णांक rc = -EINVAL;

	अगर (!zalloc_cpumask_var(&cpu_pool, GFP_KERNEL))
		वापस -ENOMEM;

	mutex_lock(&ne_cpu_pool.mutex);

	rc = cpulist_parse(ne_cpu_list, cpu_pool);
	अगर (rc < 0) अणु
		pr_err("%s: Error in cpulist parse [rc=%d]\n", ne_misc_dev.name, rc);

		जाओ मुक्त_pool_cpumask;
	पूर्ण

	cpu = cpumask_any(cpu_pool);
	अगर (cpu >= nr_cpu_ids) अणु
		pr_err("%s: No CPUs available in CPU pool\n", ne_misc_dev.name);

		rc = -EINVAL;

		जाओ मुक्त_pool_cpumask;
	पूर्ण

	/*
	 * Check अगर the CPUs are online, to further get info about them
	 * e.g. numa node, core id, siblings.
	 */
	क्रम_each_cpu(cpu, cpu_pool)
		अगर (cpu_is_offline(cpu)) अणु
			pr_err("%s: CPU %d is offline, has to be online to get its metadata\n",
			       ne_misc_dev.name, cpu);

			rc = -EINVAL;

			जाओ मुक्त_pool_cpumask;
		पूर्ण

	/*
	 * Check अगर the CPUs from the NE CPU pool are from the same NUMA node.
	 */
	क्रम_each_cpu(cpu, cpu_pool)
		अगर (numa_node < 0) अणु
			numa_node = cpu_to_node(cpu);
			अगर (numa_node < 0) अणु
				pr_err("%s: Invalid NUMA node %d\n",
				       ne_misc_dev.name, numa_node);

				rc = -EINVAL;

				जाओ मुक्त_pool_cpumask;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (numa_node != cpu_to_node(cpu)) अणु
				pr_err("%s: CPUs with different NUMA nodes\n",
				       ne_misc_dev.name);

				rc = -EINVAL;

				जाओ मुक्त_pool_cpumask;
			पूर्ण
		पूर्ण

	/*
	 * Check अगर CPU 0 and its siblings are included in the provided CPU pool
	 * They should reमुख्य available क्रम the primary / parent VM.
	 */
	अगर (cpumask_test_cpu(0, cpu_pool)) अणु
		pr_err("%s: CPU 0 has to remain available\n", ne_misc_dev.name);

		rc = -EINVAL;

		जाओ मुक्त_pool_cpumask;
	पूर्ण

	क्रम_each_cpu(cpu_sibling, topology_sibling_cpumask(0)) अणु
		अगर (cpumask_test_cpu(cpu_sibling, cpu_pool)) अणु
			pr_err("%s: CPU sibling %d for CPU 0 is in CPU pool\n",
			       ne_misc_dev.name, cpu_sibling);

			rc = -EINVAL;

			जाओ मुक्त_pool_cpumask;
		पूर्ण
	पूर्ण

	/*
	 * Check अगर CPU siblings are included in the provided CPU pool. The
	 * expectation is that full CPU cores are made available in the CPU pool
	 * क्रम enclaves.
	 */
	क्रम_each_cpu(cpu, cpu_pool) अणु
		क्रम_each_cpu(cpu_sibling, topology_sibling_cpumask(cpu)) अणु
			अगर (!cpumask_test_cpu(cpu_sibling, cpu_pool)) अणु
				pr_err("%s: CPU %d is not in CPU pool\n",
				       ne_misc_dev.name, cpu_sibling);

				rc = -EINVAL;

				जाओ मुक्त_pool_cpumask;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Calculate the number of thपढ़ोs from a full CPU core. */
	cpu = cpumask_any(cpu_pool);
	क्रम_each_cpu(cpu_sibling, topology_sibling_cpumask(cpu))
		ne_cpu_pool.nr_thपढ़ोs_per_core++;

	ne_cpu_pool.nr_parent_vm_cores = nr_cpu_ids / ne_cpu_pool.nr_thपढ़ोs_per_core;

	ne_cpu_pool.avail_thपढ़ोs_per_core = kसुस्मृति(ne_cpu_pool.nr_parent_vm_cores,
					     माप(*ne_cpu_pool.avail_thपढ़ोs_per_core),
					     GFP_KERNEL);
	अगर (!ne_cpu_pool.avail_thपढ़ोs_per_core) अणु
		rc = -ENOMEM;

		जाओ मुक्त_pool_cpumask;
	पूर्ण

	क्रम (i = 0; i < ne_cpu_pool.nr_parent_vm_cores; i++)
		अगर (!zalloc_cpumask_var(&ne_cpu_pool.avail_thपढ़ोs_per_core[i], GFP_KERNEL)) अणु
			rc = -ENOMEM;

			जाओ मुक्त_cores_cpumask;
		पूर्ण

	/*
	 * Split the NE CPU pool in thपढ़ोs per core to keep the CPU topology
	 * after offlining the CPUs.
	 */
	क्रम_each_cpu(cpu, cpu_pool) अणु
		core_id = topology_core_id(cpu);
		अगर (core_id < 0 || core_id >= ne_cpu_pool.nr_parent_vm_cores) अणु
			pr_err("%s: Invalid core id  %d for CPU %d\n",
			       ne_misc_dev.name, core_id, cpu);

			rc = -EINVAL;

			जाओ clear_cpumask;
		पूर्ण

		cpumask_set_cpu(cpu, ne_cpu_pool.avail_thपढ़ोs_per_core[core_id]);
	पूर्ण

	/*
	 * CPUs that are given to enclave(s) should not be considered online
	 * by Linux anymore, as the hypervisor will degrade them to भग्नing.
	 * The physical CPUs (full cores) are carved out of the primary / parent
	 * VM and given to the enclave VM. The same number of vCPUs would run
	 * on less pCPUs क्रम the primary / parent VM.
	 *
	 * We offline them here, to not degrade perक्रमmance and expose correct
	 * topology to Linux and user space.
	 */
	क्रम_each_cpu(cpu, cpu_pool) अणु
		rc = हटाओ_cpu(cpu);
		अगर (rc != 0) अणु
			pr_err("%s: CPU %d is not offlined [rc=%d]\n",
			       ne_misc_dev.name, cpu, rc);

			जाओ online_cpus;
		पूर्ण
	पूर्ण

	मुक्त_cpumask_var(cpu_pool);

	ne_cpu_pool.numa_node = numa_node;

	mutex_unlock(&ne_cpu_pool.mutex);

	वापस 0;

online_cpus:
	क्रम_each_cpu(cpu, cpu_pool)
		add_cpu(cpu);
clear_cpumask:
	क्रम (i = 0; i < ne_cpu_pool.nr_parent_vm_cores; i++)
		cpumask_clear(ne_cpu_pool.avail_thपढ़ोs_per_core[i]);
मुक्त_cores_cpumask:
	क्रम (i = 0; i < ne_cpu_pool.nr_parent_vm_cores; i++)
		मुक्त_cpumask_var(ne_cpu_pool.avail_thपढ़ोs_per_core[i]);
	kमुक्त(ne_cpu_pool.avail_thपढ़ोs_per_core);
मुक्त_pool_cpumask:
	मुक्त_cpumask_var(cpu_pool);
	ne_cpu_pool.nr_parent_vm_cores = 0;
	ne_cpu_pool.nr_thपढ़ोs_per_core = 0;
	ne_cpu_pool.numa_node = -1;
	mutex_unlock(&ne_cpu_pool.mutex);

	वापस rc;
पूर्ण

/**
 * ne_tearकरोwn_cpu_pool() - Online the CPUs from the NE CPU pool and cleanup the
 *			    CPU pool.
 * @व्योम:	No parameters provided.
 *
 * Context: Process context.
 */
अटल व्योम ne_tearकरोwn_cpu_pool(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = 0;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक rc = -EINVAL;

	mutex_lock(&ne_cpu_pool.mutex);

	अगर (!ne_cpu_pool.nr_parent_vm_cores) अणु
		mutex_unlock(&ne_cpu_pool.mutex);

		वापस;
	पूर्ण

	क्रम (i = 0; i < ne_cpu_pool.nr_parent_vm_cores; i++) अणु
		क्रम_each_cpu(cpu, ne_cpu_pool.avail_thपढ़ोs_per_core[i]) अणु
			rc = add_cpu(cpu);
			अगर (rc != 0)
				pr_err("%s: CPU %d is not onlined [rc=%d]\n",
				       ne_misc_dev.name, cpu, rc);
		पूर्ण

		cpumask_clear(ne_cpu_pool.avail_thपढ़ोs_per_core[i]);

		मुक्त_cpumask_var(ne_cpu_pool.avail_thपढ़ोs_per_core[i]);
	पूर्ण

	kमुक्त(ne_cpu_pool.avail_thपढ़ोs_per_core);
	ne_cpu_pool.nr_parent_vm_cores = 0;
	ne_cpu_pool.nr_thपढ़ोs_per_core = 0;
	ne_cpu_pool.numa_node = -1;

	mutex_unlock(&ne_cpu_pool.mutex);
पूर्ण

/**
 * ne_set_kernel_param() - Set the NE CPU pool value via the NE kernel parameter.
 * @val:	NE CPU pool string value.
 * @kp :	NE kernel parameter associated with the NE CPU pool.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_set_kernel_param(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अक्षर error_val[] = "";
	पूर्णांक rc = -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (ne_check_enclaves_created()) अणु
		pr_err("%s: The CPU pool is used by enclave(s)\n", ne_misc_dev.name);

		वापस -EPERM;
	पूर्ण

	ne_tearकरोwn_cpu_pool();

	rc = ne_setup_cpu_pool(val);
	अगर (rc < 0) अणु
		pr_err("%s: Error in setup CPU pool [rc=%d]\n", ne_misc_dev.name, rc);

		param_set_copystring(error_val, kp);

		वापस rc;
	पूर्ण

	rc = param_set_copystring(val, kp);
	अगर (rc < 0) अणु
		pr_err("%s: Error in param set copystring [rc=%d]\n", ne_misc_dev.name, rc);

		ne_tearकरोwn_cpu_pool();

		param_set_copystring(error_val, kp);

		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_करोnated_cpu() - Check अगर the provided CPU is alपढ़ोy used by the enclave.
 * @ne_enclave :	Private data associated with the current enclave.
 * @cpu:		CPU to check अगर alपढ़ोy used.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * True अगर the provided CPU is alपढ़ोy used by the enclave.
 * * False otherwise.
 */
अटल bool ne_करोnated_cpu(काष्ठा ne_enclave *ne_enclave, अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpumask_test_cpu(cpu, ne_enclave->vcpu_ids))
		वापस true;

	वापस false;
पूर्ण

/**
 * ne_get_unused_core_from_cpu_pool() - Get the id of a full core from the
 *					NE CPU pool.
 * @व्योम:	No parameters provided.
 *
 * Context: Process context. This function is called with the ne_enclave and
 *	    ne_cpu_pool mutexes held.
 * Return:
 * * Core id.
 * * -1 अगर no CPU core available in the pool.
 */
अटल पूर्णांक ne_get_unused_core_from_cpu_pool(व्योम)
अणु
	पूर्णांक core_id = -1;
	अचिन्हित पूर्णांक i = 0;

	क्रम (i = 0; i < ne_cpu_pool.nr_parent_vm_cores; i++)
		अगर (!cpumask_empty(ne_cpu_pool.avail_thपढ़ोs_per_core[i])) अणु
			core_id = i;

			अवरोध;
		पूर्ण

	वापस core_id;
पूर्ण

/**
 * ne_set_enclave_thपढ़ोs_per_core() - Set the thपढ़ोs of the provided core in
 *				       the enclave data काष्ठाure.
 * @ne_enclave :	Private data associated with the current enclave.
 * @core_id:		Core id to get its thपढ़ोs from the NE CPU pool.
 * @vcpu_id:		vCPU id part of the provided core.
 *
 * Context: Process context. This function is called with the ne_enclave and
 *	    ne_cpu_pool mutexes held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_set_enclave_thपढ़ोs_per_core(काष्ठा ne_enclave *ne_enclave,
					   पूर्णांक core_id, u32 vcpu_id)
अणु
	अचिन्हित पूर्णांक cpu = 0;

	अगर (core_id < 0 && vcpu_id == 0) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "No CPUs available in NE CPU pool\n");

		वापस -NE_ERR_NO_CPUS_AVAIL_IN_POOL;
	पूर्ण

	अगर (core_id < 0) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "CPU %d is not in NE CPU pool\n", vcpu_id);

		वापस -NE_ERR_VCPU_NOT_IN_CPU_POOL;
	पूर्ण

	अगर (core_id >= ne_enclave->nr_parent_vm_cores) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Invalid core id %d - ne_enclave\n", core_id);

		वापस -NE_ERR_VCPU_INVALID_CPU_CORE;
	पूर्ण

	क्रम_each_cpu(cpu, ne_cpu_pool.avail_thपढ़ोs_per_core[core_id])
		cpumask_set_cpu(cpu, ne_enclave->thपढ़ोs_per_core[core_id]);

	cpumask_clear(ne_cpu_pool.avail_thपढ़ोs_per_core[core_id]);

	वापस 0;
पूर्ण

/**
 * ne_get_cpu_from_cpu_pool() - Get a CPU from the NE CPU pool, either from the
 *				reमुख्यing sibling(s) of a CPU core or the first
 *				sibling of a new CPU core.
 * @ne_enclave :	Private data associated with the current enclave.
 * @vcpu_id:		vCPU to get from the NE CPU pool.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_get_cpu_from_cpu_pool(काष्ठा ne_enclave *ne_enclave, u32 *vcpu_id)
अणु
	पूर्णांक core_id = -1;
	अचिन्हित पूर्णांक cpu = 0;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक rc = -EINVAL;

	/*
	 * If previously allocated a thपढ़ो of a core to this enclave, first
	 * check reमुख्यing sibling(s) क्रम new CPU allocations, so that full
	 * CPU cores are used क्रम the enclave.
	 */
	क्रम (i = 0; i < ne_enclave->nr_parent_vm_cores; i++)
		क्रम_each_cpu(cpu, ne_enclave->thपढ़ोs_per_core[i])
			अगर (!ne_करोnated_cpu(ne_enclave, cpu)) अणु
				*vcpu_id = cpu;

				वापस 0;
			पूर्ण

	mutex_lock(&ne_cpu_pool.mutex);

	/*
	 * If no reमुख्यing siblings, get a core from the NE CPU pool and keep
	 * track of all the thपढ़ोs in the enclave thपढ़ोs per core data काष्ठाure.
	 */
	core_id = ne_get_unused_core_from_cpu_pool();

	rc = ne_set_enclave_thपढ़ोs_per_core(ne_enclave, core_id, *vcpu_id);
	अगर (rc < 0)
		जाओ unlock_mutex;

	*vcpu_id = cpumask_any(ne_enclave->thपढ़ोs_per_core[core_id]);

	rc = 0;

unlock_mutex:
	mutex_unlock(&ne_cpu_pool.mutex);

	वापस rc;
पूर्ण

/**
 * ne_get_vcpu_core_from_cpu_pool() - Get from the NE CPU pool the id of the
 *				      core associated with the provided vCPU.
 * @vcpu_id:	Provided vCPU id to get its associated core id.
 *
 * Context: Process context. This function is called with the ne_enclave and
 *	    ne_cpu_pool mutexes held.
 * Return:
 * * Core id.
 * * -1 अगर the provided vCPU is not in the pool.
 */
अटल पूर्णांक ne_get_vcpu_core_from_cpu_pool(u32 vcpu_id)
अणु
	पूर्णांक core_id = -1;
	अचिन्हित पूर्णांक i = 0;

	क्रम (i = 0; i < ne_cpu_pool.nr_parent_vm_cores; i++)
		अगर (cpumask_test_cpu(vcpu_id, ne_cpu_pool.avail_thपढ़ोs_per_core[i])) अणु
			core_id = i;

			अवरोध;
	पूर्ण

	वापस core_id;
पूर्ण

/**
 * ne_check_cpu_in_cpu_pool() - Check अगर the given vCPU is in the available CPUs
 *				from the pool.
 * @ne_enclave :	Private data associated with the current enclave.
 * @vcpu_id:		ID of the vCPU to check अगर available in the NE CPU pool.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_check_cpu_in_cpu_pool(काष्ठा ne_enclave *ne_enclave, u32 vcpu_id)
अणु
	पूर्णांक core_id = -1;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक rc = -EINVAL;

	अगर (ne_करोnated_cpu(ne_enclave, vcpu_id)) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "CPU %d already used\n", vcpu_id);

		वापस -NE_ERR_VCPU_ALREADY_USED;
	पूर्ण

	/*
	 * If previously allocated a thपढ़ो of a core to this enclave, but not
	 * the full core, first check reमुख्यing sibling(s).
	 */
	क्रम (i = 0; i < ne_enclave->nr_parent_vm_cores; i++)
		अगर (cpumask_test_cpu(vcpu_id, ne_enclave->thपढ़ोs_per_core[i]))
			वापस 0;

	mutex_lock(&ne_cpu_pool.mutex);

	/*
	 * If no reमुख्यing siblings, get from the NE CPU pool the core
	 * associated with the vCPU and keep track of all the thपढ़ोs in the
	 * enclave thपढ़ोs per core data काष्ठाure.
	 */
	core_id = ne_get_vcpu_core_from_cpu_pool(vcpu_id);

	rc = ne_set_enclave_thपढ़ोs_per_core(ne_enclave, core_id, vcpu_id);
	अगर (rc < 0)
		जाओ unlock_mutex;

	rc = 0;

unlock_mutex:
	mutex_unlock(&ne_cpu_pool.mutex);

	वापस rc;
पूर्ण

/**
 * ne_add_vcpu_ioctl() - Add a vCPU to the slot associated with the current
 *			 enclave.
 * @ne_enclave :	Private data associated with the current enclave.
 * @vcpu_id:		ID of the CPU to be associated with the given slot,
 *			apic id on x86.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_add_vcpu_ioctl(काष्ठा ne_enclave *ne_enclave, u32 vcpu_id)
अणु
	काष्ठा ne_pci_dev_cmd_reply cmd_reply = अणुपूर्ण;
	काष्ठा pci_dev *pdev = ne_devs.ne_pci_dev->pdev;
	पूर्णांक rc = -EINVAL;
	काष्ठा slot_add_vcpu_req slot_add_vcpu_req = अणुपूर्ण;

	अगर (ne_enclave->mm != current->mm)
		वापस -EIO;

	slot_add_vcpu_req.slot_uid = ne_enclave->slot_uid;
	slot_add_vcpu_req.vcpu_id = vcpu_id;

	rc = ne_करो_request(pdev, SLOT_ADD_VCPU,
			   &slot_add_vcpu_req, माप(slot_add_vcpu_req),
			   &cmd_reply, माप(cmd_reply));
	अगर (rc < 0) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Error in slot add vCPU [rc=%d]\n", rc);

		वापस rc;
	पूर्ण

	cpumask_set_cpu(vcpu_id, ne_enclave->vcpu_ids);

	ne_enclave->nr_vcpus++;

	वापस 0;
पूर्ण

/**
 * ne_sanity_check_user_mem_region() - Sanity check the user space memory
 *				       region received during the set user
 *				       memory region ioctl call.
 * @ne_enclave :	Private data associated with the current enclave.
 * @mem_region :	User space memory region to be sanity checked.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_sanity_check_user_mem_region(काष्ठा ne_enclave *ne_enclave,
	काष्ठा ne_user_memory_region mem_region)
अणु
	काष्ठा ne_mem_region *ne_mem_region = शून्य;

	अगर (ne_enclave->mm != current->mm)
		वापस -EIO;

	अगर (mem_region.memory_size & (NE_MIN_MEM_REGION_SIZE - 1)) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "User space memory size is not multiple of 2 MiB\n");

		वापस -NE_ERR_INVALID_MEM_REGION_SIZE;
	पूर्ण

	अगर (!IS_ALIGNED(mem_region.userspace_addr, NE_MIN_MEM_REGION_SIZE)) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "User space address is not 2 MiB aligned\n");

		वापस -NE_ERR_UNALIGNED_MEM_REGION_ADDR;
	पूर्ण

	अगर ((mem_region.userspace_addr & (NE_MIN_MEM_REGION_SIZE - 1)) ||
	    !access_ok((व्योम __user *)(अचिन्हित दीर्घ)mem_region.userspace_addr,
		       mem_region.memory_size)) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Invalid user space address range\n");

		वापस -NE_ERR_INVALID_MEM_REGION_ADDR;
	पूर्ण

	list_क्रम_each_entry(ne_mem_region, &ne_enclave->mem_regions_list,
			    mem_region_list_entry) अणु
		u64 memory_size = ne_mem_region->memory_size;
		u64 userspace_addr = ne_mem_region->userspace_addr;

		अगर ((userspace_addr <= mem_region.userspace_addr &&
		    mem_region.userspace_addr < (userspace_addr + memory_size)) ||
		    (mem_region.userspace_addr <= userspace_addr &&
		    (mem_region.userspace_addr + mem_region.memory_size) > userspace_addr)) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "User space memory region already used\n");

			वापस -NE_ERR_MEM_REGION_ALREADY_USED;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_sanity_check_user_mem_region_page() - Sanity check a page from the user space
 *					    memory region received during the set
 *					    user memory region ioctl call.
 * @ne_enclave :	Private data associated with the current enclave.
 * @mem_region_page:	Page from the user space memory region to be sanity checked.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_sanity_check_user_mem_region_page(काष्ठा ne_enclave *ne_enclave,
						काष्ठा page *mem_region_page)
अणु
	अगर (!PageHuge(mem_region_page)) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Not a hugetlbfs page\n");

		वापस -NE_ERR_MEM_NOT_HUGE_PAGE;
	पूर्ण

	अगर (page_size(mem_region_page) & (NE_MIN_MEM_REGION_SIZE - 1)) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Page size not multiple of 2 MiB\n");

		वापस -NE_ERR_INVALID_PAGE_SIZE;
	पूर्ण

	अगर (ne_enclave->numa_node != page_to_nid(mem_region_page)) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Page is not from NUMA node %d\n",
				    ne_enclave->numa_node);

		वापस -NE_ERR_MEM_DIFFERENT_NUMA_NODE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_set_user_memory_region_ioctl() - Add user space memory region to the slot
 *				       associated with the current enclave.
 * @ne_enclave :	Private data associated with the current enclave.
 * @mem_region :	User space memory region to be associated with the given slot.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_set_user_memory_region_ioctl(काष्ठा ne_enclave *ne_enclave,
	काष्ठा ne_user_memory_region mem_region)
अणु
	दीर्घ gup_rc = 0;
	अचिन्हित दीर्घ i = 0;
	अचिन्हित दीर्घ max_nr_pages = 0;
	अचिन्हित दीर्घ memory_size = 0;
	काष्ठा ne_mem_region *ne_mem_region = शून्य;
	अचिन्हित दीर्घ nr_phys_contig_mem_regions = 0;
	काष्ठा pci_dev *pdev = ne_devs.ne_pci_dev->pdev;
	काष्ठा page **phys_contig_mem_regions = शून्य;
	पूर्णांक rc = -EINVAL;

	rc = ne_sanity_check_user_mem_region(ne_enclave, mem_region);
	अगर (rc < 0)
		वापस rc;

	ne_mem_region = kzalloc(माप(*ne_mem_region), GFP_KERNEL);
	अगर (!ne_mem_region)
		वापस -ENOMEM;

	max_nr_pages = mem_region.memory_size / NE_MIN_MEM_REGION_SIZE;

	ne_mem_region->pages = kसुस्मृति(max_nr_pages, माप(*ne_mem_region->pages),
				       GFP_KERNEL);
	अगर (!ne_mem_region->pages) अणु
		rc = -ENOMEM;

		जाओ मुक्त_mem_region;
	पूर्ण

	phys_contig_mem_regions = kसुस्मृति(max_nr_pages, माप(*phys_contig_mem_regions),
					  GFP_KERNEL);
	अगर (!phys_contig_mem_regions) अणु
		rc = -ENOMEM;

		जाओ मुक्त_mem_region;
	पूर्ण

	करो अणु
		i = ne_mem_region->nr_pages;

		अगर (i == max_nr_pages) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Reached max nr of pages in the pages data struct\n");

			rc = -ENOMEM;

			जाओ put_pages;
		पूर्ण

		gup_rc = get_user_pages(mem_region.userspace_addr + memory_size, 1, FOLL_GET,
					ne_mem_region->pages + i, शून्य);
		अगर (gup_rc < 0) अणु
			rc = gup_rc;

			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Error in get user pages [rc=%d]\n", rc);

			जाओ put_pages;
		पूर्ण

		rc = ne_sanity_check_user_mem_region_page(ne_enclave, ne_mem_region->pages[i]);
		अगर (rc < 0)
			जाओ put_pages;

		/*
		 * TODO: Update once handled non-contiguous memory regions
		 * received from user space or contiguous physical memory regions
		 * larger than 2 MiB e.g. 8 MiB.
		 */
		phys_contig_mem_regions[i] = ne_mem_region->pages[i];

		memory_size += page_size(ne_mem_region->pages[i]);

		ne_mem_region->nr_pages++;
	पूर्ण जबतक (memory_size < mem_region.memory_size);

	/*
	 * TODO: Update once handled non-contiguous memory regions received
	 * from user space or contiguous physical memory regions larger than
	 * 2 MiB e.g. 8 MiB.
	 */
	nr_phys_contig_mem_regions = ne_mem_region->nr_pages;

	अगर ((ne_enclave->nr_mem_regions + nr_phys_contig_mem_regions) >
	    ne_enclave->max_mem_regions) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Reached max memory regions %lld\n",
				    ne_enclave->max_mem_regions);

		rc = -NE_ERR_MEM_MAX_REGIONS;

		जाओ put_pages;
	पूर्ण

	क्रम (i = 0; i < nr_phys_contig_mem_regions; i++) अणु
		u64 phys_region_addr = page_to_phys(phys_contig_mem_regions[i]);
		u64 phys_region_size = page_size(phys_contig_mem_regions[i]);

		अगर (phys_region_size & (NE_MIN_MEM_REGION_SIZE - 1)) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Physical mem region size is not multiple of 2 MiB\n");

			rc = -EINVAL;

			जाओ put_pages;
		पूर्ण

		अगर (!IS_ALIGNED(phys_region_addr, NE_MIN_MEM_REGION_SIZE)) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Physical mem region address is not 2 MiB aligned\n");

			rc = -EINVAL;

			जाओ put_pages;
		पूर्ण
	पूर्ण

	ne_mem_region->memory_size = mem_region.memory_size;
	ne_mem_region->userspace_addr = mem_region.userspace_addr;

	list_add(&ne_mem_region->mem_region_list_entry, &ne_enclave->mem_regions_list);

	क्रम (i = 0; i < nr_phys_contig_mem_regions; i++) अणु
		काष्ठा ne_pci_dev_cmd_reply cmd_reply = अणुपूर्ण;
		काष्ठा slot_add_mem_req slot_add_mem_req = अणुपूर्ण;

		slot_add_mem_req.slot_uid = ne_enclave->slot_uid;
		slot_add_mem_req.paddr = page_to_phys(phys_contig_mem_regions[i]);
		slot_add_mem_req.size = page_size(phys_contig_mem_regions[i]);

		rc = ne_करो_request(pdev, SLOT_ADD_MEM,
				   &slot_add_mem_req, माप(slot_add_mem_req),
				   &cmd_reply, माप(cmd_reply));
		अगर (rc < 0) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Error in slot add mem [rc=%d]\n", rc);

			kमुक्त(phys_contig_mem_regions);

			/*
			 * Exit here without put pages as memory regions may
			 * alपढ़ोy been added.
			 */
			वापस rc;
		पूर्ण

		ne_enclave->mem_size += slot_add_mem_req.size;
		ne_enclave->nr_mem_regions++;
	पूर्ण

	kमुक्त(phys_contig_mem_regions);

	वापस 0;

put_pages:
	क्रम (i = 0; i < ne_mem_region->nr_pages; i++)
		put_page(ne_mem_region->pages[i]);
मुक्त_mem_region:
	kमुक्त(phys_contig_mem_regions);
	kमुक्त(ne_mem_region->pages);
	kमुक्त(ne_mem_region);

	वापस rc;
पूर्ण

/**
 * ne_start_enclave_ioctl() - Trigger enclave start after the enclave resources,
 *			      such as memory and CPU, have been set.
 * @ne_enclave :		Private data associated with the current enclave.
 * @enclave_start_info :	Enclave info that includes enclave cid and flags.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_start_enclave_ioctl(काष्ठा ne_enclave *ne_enclave,
	काष्ठा ne_enclave_start_info *enclave_start_info)
अणु
	काष्ठा ne_pci_dev_cmd_reply cmd_reply = अणुपूर्ण;
	अचिन्हित पूर्णांक cpu = 0;
	काष्ठा enclave_start_req enclave_start_req = अणुपूर्ण;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा pci_dev *pdev = ne_devs.ne_pci_dev->pdev;
	पूर्णांक rc = -EINVAL;

	अगर (!ne_enclave->nr_mem_regions) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Enclave has no mem regions\n");

		वापस -NE_ERR_NO_MEM_REGIONS_ADDED;
	पूर्ण

	अगर (ne_enclave->mem_size < NE_MIN_ENCLAVE_MEM_SIZE) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Enclave memory is less than %ld\n",
				    NE_MIN_ENCLAVE_MEM_SIZE);

		वापस -NE_ERR_ENCLAVE_MEM_MIN_SIZE;
	पूर्ण

	अगर (!ne_enclave->nr_vcpus) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Enclave has no vCPUs\n");

		वापस -NE_ERR_NO_VCPUS_ADDED;
	पूर्ण

	क्रम (i = 0; i < ne_enclave->nr_parent_vm_cores; i++)
		क्रम_each_cpu(cpu, ne_enclave->thपढ़ोs_per_core[i])
			अगर (!cpumask_test_cpu(cpu, ne_enclave->vcpu_ids)) अणु
				dev_err_ratelimited(ne_misc_dev.this_device,
						    "Full CPU cores not used\n");

				वापस -NE_ERR_FULL_CORES_NOT_USED;
			पूर्ण

	enclave_start_req.enclave_cid = enclave_start_info->enclave_cid;
	enclave_start_req.flags = enclave_start_info->flags;
	enclave_start_req.slot_uid = ne_enclave->slot_uid;

	rc = ne_करो_request(pdev, ENCLAVE_START,
			   &enclave_start_req, माप(enclave_start_req),
			   &cmd_reply, माप(cmd_reply));
	अगर (rc < 0) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Error in enclave start [rc=%d]\n", rc);

		वापस rc;
	पूर्ण

	ne_enclave->state = NE_STATE_RUNNING;

	enclave_start_info->enclave_cid = cmd_reply.enclave_cid;

	वापस 0;
पूर्ण

/**
 * ne_enclave_ioctl() - Ioctl function provided by the enclave file.
 * @file:	File associated with this ioctl function.
 * @cmd:	The command that is set क्रम the ioctl call.
 * @arg:	The argument that is provided क्रम the ioctl call.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल दीर्घ ne_enclave_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ne_enclave *ne_enclave = file->निजी_data;

	चयन (cmd) अणु
	हाल NE_ADD_VCPU: अणु
		पूर्णांक rc = -EINVAL;
		u32 vcpu_id = 0;

		अगर (copy_from_user(&vcpu_id, (व्योम __user *)arg, माप(vcpu_id)))
			वापस -EFAULT;

		mutex_lock(&ne_enclave->enclave_info_mutex);

		अगर (ne_enclave->state != NE_STATE_INIT) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Enclave is not in init state\n");

			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस -NE_ERR_NOT_IN_INIT_STATE;
		पूर्ण

		अगर (vcpu_id >= (ne_enclave->nr_parent_vm_cores *
		    ne_enclave->nr_thपढ़ोs_per_core)) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "vCPU id higher than max CPU id\n");

			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस -NE_ERR_INVALID_VCPU;
		पूर्ण

		अगर (!vcpu_id) अणु
			/* Use the CPU pool क्रम choosing a CPU क्रम the enclave. */
			rc = ne_get_cpu_from_cpu_pool(ne_enclave, &vcpu_id);
			अगर (rc < 0) अणु
				dev_err_ratelimited(ne_misc_dev.this_device,
						    "Error in get CPU from pool [rc=%d]\n",
						    rc);

				mutex_unlock(&ne_enclave->enclave_info_mutex);

				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Check अगर the provided vCPU is available in the NE CPU pool. */
			rc = ne_check_cpu_in_cpu_pool(ne_enclave, vcpu_id);
			अगर (rc < 0) अणु
				dev_err_ratelimited(ne_misc_dev.this_device,
						    "Error in check CPU %d in pool [rc=%d]\n",
						    vcpu_id, rc);

				mutex_unlock(&ne_enclave->enclave_info_mutex);

				वापस rc;
			पूर्ण
		पूर्ण

		rc = ne_add_vcpu_ioctl(ne_enclave, vcpu_id);
		अगर (rc < 0) अणु
			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस rc;
		पूर्ण

		mutex_unlock(&ne_enclave->enclave_info_mutex);

		अगर (copy_to_user((व्योम __user *)arg, &vcpu_id, माप(vcpu_id)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल NE_GET_IMAGE_LOAD_INFO: अणु
		काष्ठा ne_image_load_info image_load_info = अणुपूर्ण;

		अगर (copy_from_user(&image_load_info, (व्योम __user *)arg, माप(image_load_info)))
			वापस -EFAULT;

		mutex_lock(&ne_enclave->enclave_info_mutex);

		अगर (ne_enclave->state != NE_STATE_INIT) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Enclave is not in init state\n");

			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस -NE_ERR_NOT_IN_INIT_STATE;
		पूर्ण

		mutex_unlock(&ne_enclave->enclave_info_mutex);

		अगर (!image_load_info.flags ||
		    image_load_info.flags >= NE_IMAGE_LOAD_MAX_FLAG_VAL) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Incorrect flag in enclave image load info\n");

			वापस -NE_ERR_INVALID_FLAG_VALUE;
		पूर्ण

		अगर (image_load_info.flags == NE_EIF_IMAGE)
			image_load_info.memory_offset = NE_EIF_LOAD_OFFSET;

		अगर (copy_to_user((व्योम __user *)arg, &image_load_info, माप(image_load_info)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल NE_SET_USER_MEMORY_REGION: अणु
		काष्ठा ne_user_memory_region mem_region = अणुपूर्ण;
		पूर्णांक rc = -EINVAL;

		अगर (copy_from_user(&mem_region, (व्योम __user *)arg, माप(mem_region)))
			वापस -EFAULT;

		अगर (mem_region.flags >= NE_MEMORY_REGION_MAX_FLAG_VAL) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Incorrect flag for user memory region\n");

			वापस -NE_ERR_INVALID_FLAG_VALUE;
		पूर्ण

		mutex_lock(&ne_enclave->enclave_info_mutex);

		अगर (ne_enclave->state != NE_STATE_INIT) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Enclave is not in init state\n");

			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस -NE_ERR_NOT_IN_INIT_STATE;
		पूर्ण

		rc = ne_set_user_memory_region_ioctl(ne_enclave, mem_region);
		अगर (rc < 0) अणु
			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस rc;
		पूर्ण

		mutex_unlock(&ne_enclave->enclave_info_mutex);

		वापस 0;
	पूर्ण

	हाल NE_START_ENCLAVE: अणु
		काष्ठा ne_enclave_start_info enclave_start_info = अणुपूर्ण;
		पूर्णांक rc = -EINVAL;

		अगर (copy_from_user(&enclave_start_info, (व्योम __user *)arg,
				   माप(enclave_start_info)))
			वापस -EFAULT;

		अगर (enclave_start_info.flags >= NE_ENCLAVE_START_MAX_FLAG_VAL) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Incorrect flag in enclave start info\n");

			वापस -NE_ERR_INVALID_FLAG_VALUE;
		पूर्ण

		/*
		 * Do not use well-known CIDs - 0, 1, 2 - क्रम enclaves.
		 * VMADDR_CID_ANY = -1U
		 * VMADDR_CID_HYPERVISOR = 0
		 * VMADDR_CID_LOCAL = 1
		 * VMADDR_CID_HOST = 2
		 * Note: 0 is used as a placeholder to स्वतः-generate an enclave CID.
		 * http://man7.org/linux/man-pages/man7/vsock.7.hपंचांगl
		 */
		अगर (enclave_start_info.enclave_cid > 0 &&
		    enclave_start_info.enclave_cid <= VMADDR_CID_HOST) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Well-known CID value, not to be used for enclaves\n");

			वापस -NE_ERR_INVALID_ENCLAVE_CID;
		पूर्ण

		अगर (enclave_start_info.enclave_cid == U32_MAX) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Well-known CID value, not to be used for enclaves\n");

			वापस -NE_ERR_INVALID_ENCLAVE_CID;
		पूर्ण

		/*
		 * Do not use the CID of the primary / parent VM क्रम enclaves.
		 */
		अगर (enclave_start_info.enclave_cid == NE_PARENT_VM_CID) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "CID of the parent VM, not to be used for enclaves\n");

			वापस -NE_ERR_INVALID_ENCLAVE_CID;
		पूर्ण

		/* 64-bit CIDs are not yet supported क्रम the vsock device. */
		अगर (enclave_start_info.enclave_cid > U32_MAX) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "64-bit CIDs not yet supported for the vsock device\n");

			वापस -NE_ERR_INVALID_ENCLAVE_CID;
		पूर्ण

		mutex_lock(&ne_enclave->enclave_info_mutex);

		अगर (ne_enclave->state != NE_STATE_INIT) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Enclave is not in init state\n");

			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस -NE_ERR_NOT_IN_INIT_STATE;
		पूर्ण

		rc = ne_start_enclave_ioctl(ne_enclave, &enclave_start_info);
		अगर (rc < 0) अणु
			mutex_unlock(&ne_enclave->enclave_info_mutex);

			वापस rc;
		पूर्ण

		mutex_unlock(&ne_enclave->enclave_info_mutex);

		अगर (copy_to_user((व्योम __user *)arg, &enclave_start_info,
				 माप(enclave_start_info)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_enclave_हटाओ_all_mem_region_entries() - Remove all memory region entries
 *						from the enclave data काष्ठाure.
 * @ne_enclave :	Private data associated with the current enclave.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 */
अटल व्योम ne_enclave_हटाओ_all_mem_region_entries(काष्ठा ne_enclave *ne_enclave)
अणु
	अचिन्हित दीर्घ i = 0;
	काष्ठा ne_mem_region *ne_mem_region = शून्य;
	काष्ठा ne_mem_region *ne_mem_region_पंचांगp = शून्य;

	list_क्रम_each_entry_safe(ne_mem_region, ne_mem_region_पंचांगp,
				 &ne_enclave->mem_regions_list,
				 mem_region_list_entry) अणु
		list_del(&ne_mem_region->mem_region_list_entry);

		क्रम (i = 0; i < ne_mem_region->nr_pages; i++)
			put_page(ne_mem_region->pages[i]);

		kमुक्त(ne_mem_region->pages);

		kमुक्त(ne_mem_region);
	पूर्ण
पूर्ण

/**
 * ne_enclave_हटाओ_all_vcpu_id_entries() - Remove all vCPU id entries from
 *					     the enclave data काष्ठाure.
 * @ne_enclave :	Private data associated with the current enclave.
 *
 * Context: Process context. This function is called with the ne_enclave mutex held.
 */
अटल व्योम ne_enclave_हटाओ_all_vcpu_id_entries(काष्ठा ne_enclave *ne_enclave)
अणु
	अचिन्हित पूर्णांक cpu = 0;
	अचिन्हित पूर्णांक i = 0;

	mutex_lock(&ne_cpu_pool.mutex);

	क्रम (i = 0; i < ne_enclave->nr_parent_vm_cores; i++) अणु
		क्रम_each_cpu(cpu, ne_enclave->thपढ़ोs_per_core[i])
			/* Update the available NE CPU pool. */
			cpumask_set_cpu(cpu, ne_cpu_pool.avail_thपढ़ोs_per_core[i]);

		मुक्त_cpumask_var(ne_enclave->thपढ़ोs_per_core[i]);
	पूर्ण

	mutex_unlock(&ne_cpu_pool.mutex);

	kमुक्त(ne_enclave->thपढ़ोs_per_core);

	मुक्त_cpumask_var(ne_enclave->vcpu_ids);
पूर्ण

/**
 * ne_pci_dev_हटाओ_enclave_entry() - Remove the enclave entry from the data
 *				       काष्ठाure that is part of the NE PCI
 *				       device निजी data.
 * @ne_enclave :	Private data associated with the current enclave.
 * @ne_pci_dev :	Private data associated with the PCI device.
 *
 * Context: Process context. This function is called with the ne_pci_dev enclave
 *	    mutex held.
 */
अटल व्योम ne_pci_dev_हटाओ_enclave_entry(काष्ठा ne_enclave *ne_enclave,
					    काष्ठा ne_pci_dev *ne_pci_dev)
अणु
	काष्ठा ne_enclave *ne_enclave_entry = शून्य;
	काष्ठा ne_enclave *ne_enclave_entry_पंचांगp = शून्य;

	list_क्रम_each_entry_safe(ne_enclave_entry, ne_enclave_entry_पंचांगp,
				 &ne_pci_dev->enclaves_list, enclave_list_entry) अणु
		अगर (ne_enclave_entry->slot_uid == ne_enclave->slot_uid) अणु
			list_del(&ne_enclave_entry->enclave_list_entry);

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ne_enclave_release() - Release function provided by the enclave file.
 * @inode:	Inode associated with this file release function.
 * @file:	File associated with this release function.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_enclave_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ne_pci_dev_cmd_reply cmd_reply = अणुपूर्ण;
	काष्ठा enclave_stop_req enclave_stop_request = अणुपूर्ण;
	काष्ठा ne_enclave *ne_enclave = file->निजी_data;
	काष्ठा ne_pci_dev *ne_pci_dev = ne_devs.ne_pci_dev;
	काष्ठा pci_dev *pdev = ne_pci_dev->pdev;
	पूर्णांक rc = -EINVAL;
	काष्ठा slot_मुक्त_req slot_मुक्त_req = अणुपूर्ण;

	अगर (!ne_enclave)
		वापस 0;

	/*
	 * Early निकास in हाल there is an error in the enclave creation logic
	 * and fput() is called on the cleanup path.
	 */
	अगर (!ne_enclave->slot_uid)
		वापस 0;

	/*
	 * Acquire the enclave list mutex beक्रमe the enclave mutex
	 * in order to aव्योम deadlocks with @ref ne_event_work_handler.
	 */
	mutex_lock(&ne_pci_dev->enclaves_list_mutex);
	mutex_lock(&ne_enclave->enclave_info_mutex);

	अगर (ne_enclave->state != NE_STATE_INIT && ne_enclave->state != NE_STATE_STOPPED) अणु
		enclave_stop_request.slot_uid = ne_enclave->slot_uid;

		rc = ne_करो_request(pdev, ENCLAVE_STOP,
				   &enclave_stop_request, माप(enclave_stop_request),
				   &cmd_reply, माप(cmd_reply));
		अगर (rc < 0) अणु
			dev_err_ratelimited(ne_misc_dev.this_device,
					    "Error in enclave stop [rc=%d]\n", rc);

			जाओ unlock_mutex;
		पूर्ण

		स_रखो(&cmd_reply, 0, माप(cmd_reply));
	पूर्ण

	slot_मुक्त_req.slot_uid = ne_enclave->slot_uid;

	rc = ne_करो_request(pdev, SLOT_FREE,
			   &slot_मुक्त_req, माप(slot_मुक्त_req),
			   &cmd_reply, माप(cmd_reply));
	अगर (rc < 0) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Error in slot free [rc=%d]\n", rc);

		जाओ unlock_mutex;
	पूर्ण

	ne_pci_dev_हटाओ_enclave_entry(ne_enclave, ne_pci_dev);
	ne_enclave_हटाओ_all_mem_region_entries(ne_enclave);
	ne_enclave_हटाओ_all_vcpu_id_entries(ne_enclave);

	mutex_unlock(&ne_enclave->enclave_info_mutex);
	mutex_unlock(&ne_pci_dev->enclaves_list_mutex);

	kमुक्त(ne_enclave);

	वापस 0;

unlock_mutex:
	mutex_unlock(&ne_enclave->enclave_info_mutex);
	mutex_unlock(&ne_pci_dev->enclaves_list_mutex);

	वापस rc;
पूर्ण

/**
 * ne_enclave_poll() - Poll functionality used क्रम enclave out-of-band events.
 * @file:	File associated with this poll function.
 * @रुको:	Poll table data काष्ठाure.
 *
 * Context: Process context.
 * Return:
 * * Poll mask.
 */
अटल __poll_t ne_enclave_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = 0;
	काष्ठा ne_enclave *ne_enclave = file->निजी_data;

	poll_रुको(file, &ne_enclave->eventq, रुको);

	अगर (ne_enclave->has_event)
		mask |= EPOLLHUP;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations ne_enclave_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= noop_llseek,
	.poll		= ne_enclave_poll,
	.unlocked_ioctl	= ne_enclave_ioctl,
	.release	= ne_enclave_release,
पूर्ण;

/**
 * ne_create_vm_ioctl() - Alloc slot to be associated with an enclave. Create
 *			  enclave file descriptor to be further used क्रम enclave
 *			  resources handling e.g. memory regions and CPUs.
 * @ne_pci_dev :	Private data associated with the PCI device.
 * @slot_uid:		User poपूर्णांकer to store the generated unique slot id
 *			associated with an enclave to.
 *
 * Context: Process context. This function is called with the ne_pci_dev enclave
 *	    mutex held.
 * Return:
 * * Enclave fd on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_create_vm_ioctl(काष्ठा ne_pci_dev *ne_pci_dev, u64 __user *slot_uid)
अणु
	काष्ठा ne_pci_dev_cmd_reply cmd_reply = अणुपूर्ण;
	पूर्णांक enclave_fd = -1;
	काष्ठा file *enclave_file = शून्य;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा ne_enclave *ne_enclave = शून्य;
	काष्ठा pci_dev *pdev = ne_pci_dev->pdev;
	पूर्णांक rc = -EINVAL;
	काष्ठा slot_alloc_req slot_alloc_req = अणुपूर्ण;

	mutex_lock(&ne_cpu_pool.mutex);

	क्रम (i = 0; i < ne_cpu_pool.nr_parent_vm_cores; i++)
		अगर (!cpumask_empty(ne_cpu_pool.avail_thपढ़ोs_per_core[i]))
			अवरोध;

	अगर (i == ne_cpu_pool.nr_parent_vm_cores) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "No CPUs available in CPU pool\n");

		mutex_unlock(&ne_cpu_pool.mutex);

		वापस -NE_ERR_NO_CPUS_AVAIL_IN_POOL;
	पूर्ण

	mutex_unlock(&ne_cpu_pool.mutex);

	ne_enclave = kzalloc(माप(*ne_enclave), GFP_KERNEL);
	अगर (!ne_enclave)
		वापस -ENOMEM;

	mutex_lock(&ne_cpu_pool.mutex);

	ne_enclave->nr_parent_vm_cores = ne_cpu_pool.nr_parent_vm_cores;
	ne_enclave->nr_thपढ़ोs_per_core = ne_cpu_pool.nr_thपढ़ोs_per_core;
	ne_enclave->numa_node = ne_cpu_pool.numa_node;

	mutex_unlock(&ne_cpu_pool.mutex);

	ne_enclave->thपढ़ोs_per_core = kसुस्मृति(ne_enclave->nr_parent_vm_cores,
		माप(*ne_enclave->thपढ़ोs_per_core), GFP_KERNEL);
	अगर (!ne_enclave->thपढ़ोs_per_core) अणु
		rc = -ENOMEM;

		जाओ मुक्त_ne_enclave;
	पूर्ण

	क्रम (i = 0; i < ne_enclave->nr_parent_vm_cores; i++)
		अगर (!zalloc_cpumask_var(&ne_enclave->thपढ़ोs_per_core[i], GFP_KERNEL)) अणु
			rc = -ENOMEM;

			जाओ मुक्त_cpumask;
		पूर्ण

	अगर (!zalloc_cpumask_var(&ne_enclave->vcpu_ids, GFP_KERNEL)) अणु
		rc = -ENOMEM;

		जाओ मुक्त_cpumask;
	पूर्ण

	enclave_fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (enclave_fd < 0) अणु
		rc = enclave_fd;

		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Error in getting unused fd [rc=%d]\n", rc);

		जाओ मुक्त_cpumask;
	पूर्ण

	enclave_file = anon_inode_getfile("ne-vm", &ne_enclave_fops, ne_enclave, O_RDWR);
	अगर (IS_ERR(enclave_file)) अणु
		rc = PTR_ERR(enclave_file);

		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Error in anon inode get file [rc=%d]\n", rc);

		जाओ put_fd;
	पूर्ण

	rc = ne_करो_request(pdev, SLOT_ALLOC,
			   &slot_alloc_req, माप(slot_alloc_req),
			   &cmd_reply, माप(cmd_reply));
	अगर (rc < 0) अणु
		dev_err_ratelimited(ne_misc_dev.this_device,
				    "Error in slot alloc [rc=%d]\n", rc);

		जाओ put_file;
	पूर्ण

	init_रुकोqueue_head(&ne_enclave->eventq);
	ne_enclave->has_event = false;
	mutex_init(&ne_enclave->enclave_info_mutex);
	ne_enclave->max_mem_regions = cmd_reply.mem_regions;
	INIT_LIST_HEAD(&ne_enclave->mem_regions_list);
	ne_enclave->mm = current->mm;
	ne_enclave->slot_uid = cmd_reply.slot_uid;
	ne_enclave->state = NE_STATE_INIT;

	list_add(&ne_enclave->enclave_list_entry, &ne_pci_dev->enclaves_list);

	अगर (copy_to_user(slot_uid, &ne_enclave->slot_uid, माप(ne_enclave->slot_uid))) अणु
		/*
		 * As we're holding the only reference to 'enclave_file', fput()
		 * will call ne_enclave_release() which will करो a proper cleanup
		 * of all so far allocated resources, leaving only the unused fd
		 * क्रम us to मुक्त.
		 */
		fput(enclave_file);
		put_unused_fd(enclave_fd);

		वापस -EFAULT;
	पूर्ण

	fd_install(enclave_fd, enclave_file);

	वापस enclave_fd;

put_file:
	fput(enclave_file);
put_fd:
	put_unused_fd(enclave_fd);
मुक्त_cpumask:
	मुक्त_cpumask_var(ne_enclave->vcpu_ids);
	क्रम (i = 0; i < ne_enclave->nr_parent_vm_cores; i++)
		मुक्त_cpumask_var(ne_enclave->thपढ़ोs_per_core[i]);
	kमुक्त(ne_enclave->thपढ़ोs_per_core);
मुक्त_ne_enclave:
	kमुक्त(ne_enclave);

	वापस rc;
पूर्ण

/**
 * ne_ioctl() - Ioctl function provided by the NE misc device.
 * @file:	File associated with this ioctl function.
 * @cmd:	The command that is set क्रम the ioctl call.
 * @arg:	The argument that is provided क्रम the ioctl call.
 *
 * Context: Process context.
 * Return:
 * * Ioctl result (e.g. enclave file descriptor) on success.
 * * Negative वापस value on failure.
 */
अटल दीर्घ ne_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल NE_CREATE_VM: अणु
		पूर्णांक enclave_fd = -1;
		काष्ठा ne_pci_dev *ne_pci_dev = ne_devs.ne_pci_dev;
		u64 __user *slot_uid = (व्योम __user *)arg;

		mutex_lock(&ne_pci_dev->enclaves_list_mutex);
		enclave_fd = ne_create_vm_ioctl(ne_pci_dev, slot_uid);
		mutex_unlock(&ne_pci_dev->enclaves_list_mutex);

		वापस enclave_fd;
	पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init ne_init(व्योम)
अणु
	mutex_init(&ne_cpu_pool.mutex);

	वापस pci_रेजिस्टर_driver(&ne_pci_driver);
पूर्ण

अटल व्योम __निकास ne_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ne_pci_driver);

	ne_tearकरोwn_cpu_pool();
पूर्ण

module_init(ne_init);
module_निकास(ne_निकास);

MODULE_AUTHOR("Amazon.com, Inc. or its affiliates");
MODULE_DESCRIPTION("Nitro Enclaves Driver");
MODULE_LICENSE("GPL v2");
