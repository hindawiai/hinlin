<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerPC64 LPAR Configuration Inक्रमmation Driver
 *
 * Dave Engebretsen engebret@us.ibm.com
 *    Copyright (c) 2003 Dave Engebretsen
 * Will Schmidt willschm@us.ibm.com
 *    SPLPAR updates, Copyright (c) 2003 Will Schmidt IBM Corporation.
 *    seq_file updates, Copyright (c) 2004 Will Schmidt IBM Corporation.
 * Nathan Lynch nathanl@austin.ibm.com
 *    Added lparcfg_ग_लिखो, Copyright (C) 2004 Nathan Lynch IBM Corporation.
 *
 * This driver creates a proc file at /proc/ppc64/lparcfg which contains
 * keyword - value pairs that specअगरy the configuration of the partition.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/lppaca.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/drस्मृति.स>

#समावेश "pseries.h"

/*
 * This isn't a module but we expose that to userspace
 * via /proc so leave the definitions here
 */
#घोषणा MODULE_VERS "1.9"
#घोषणा MODULE_NAME "lparcfg"

/* #घोषणा LPARCFG_DEBUG */

/*
 * Track sum of all purrs across all processors. This is used to further
 * calculate usage values by dअगरferent applications
 */
अटल व्योम cpu_get_purr(व्योम *arg)
अणु
	atomic64_t *sum = arg;

	atomic64_add(mfspr(SPRN_PURR), sum);
पूर्ण

अटल अचिन्हित दीर्घ get_purr(व्योम)
अणु
	atomic64_t purr = ATOMIC64_INIT(0);

	on_each_cpu(cpu_get_purr, &purr, 1);

	वापस atomic64_पढ़ो(&purr);
पूर्ण

/*
 * Methods used to fetch LPAR data when running on a pSeries platक्रमm.
 */

काष्ठा hvcall_ppp_data अणु
	u64	entitlement;
	u64	unallocated_entitlement;
	u16	group_num;
	u16	pool_num;
	u8	capped;
	u8	weight;
	u8	unallocated_weight;
	u16	active_procs_in_pool;
	u16	active_प्रणाली_procs;
	u16	phys_platक्रमm_procs;
	u32	max_proc_cap_avail;
	u32	entitled_proc_cap_avail;
पूर्ण;

/*
 * H_GET_PPP hcall वापसs info in 4 parms.
 *  entitled_capacity,unallocated_capacity,
 *  aggregation, resource_capability).
 *
 *  R4 = Entitled Processor Capacity Percentage.
 *  R5 = Unallocated Processor Capacity Percentage.
 *  R6 (AABBCCDDEEFFGGHH).
 *      XXXX - reserved (0)
 *          XXXX - reserved (0)
 *              XXXX - Group Number
 *                  XXXX - Pool Number.
 *  R7 (IIJJKKLLMMNNOOPP).
 *      XX - reserved. (0)
 *        XX - bit 0-6 reserved (0).   bit 7 is Capped indicator.
 *          XX - variable processor Capacity Weight
 *            XX - Unallocated Variable Processor Capacity Weight.
 *              XXXX - Active processors in Physical Processor Pool.
 *                  XXXX  - Processors active on platक्रमm.
 *  R8 (QQQQRRRRRRSSSSSS). अगर ibm,partition-perक्रमmance-parameters-level >= 1
 *	XXXX - Physical platक्रमm procs allocated to भवization.
 *	    XXXXXX - Max procs capacity % available to the partitions pool.
 *	          XXXXXX - Entitled procs capacity % available to the
 *			   partitions pool.
 */
अटल अचिन्हित पूर्णांक h_get_ppp(काष्ठा hvcall_ppp_data *ppp_data)
अणु
	अचिन्हित दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];

	rc = plpar_hcall9(H_GET_PPP, retbuf);

	ppp_data->entitlement = retbuf[0];
	ppp_data->unallocated_entitlement = retbuf[1];

	ppp_data->group_num = (retbuf[2] >> 2 * 8) & 0xffff;
	ppp_data->pool_num = retbuf[2] & 0xffff;

	ppp_data->capped = (retbuf[3] >> 6 * 8) & 0x01;
	ppp_data->weight = (retbuf[3] >> 5 * 8) & 0xff;
	ppp_data->unallocated_weight = (retbuf[3] >> 4 * 8) & 0xff;
	ppp_data->active_procs_in_pool = (retbuf[3] >> 2 * 8) & 0xffff;
	ppp_data->active_प्रणाली_procs = retbuf[3] & 0xffff;

	ppp_data->phys_platक्रमm_procs = retbuf[4] >> 6 * 8;
	ppp_data->max_proc_cap_avail = (retbuf[4] >> 3 * 8) & 0xffffff;
	ppp_data->entitled_proc_cap_avail = retbuf[4] & 0xffffff;

	वापस rc;
पूर्ण

अटल व्योम show_gpci_data(काष्ठा seq_file *m)
अणु
	काष्ठा hv_gpci_request_buffer *buf;
	अचिन्हित पूर्णांक affinity_score;
	दीर्घ ret;

	buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
	अगर (buf == शून्य)
		वापस;

	/*
	 * Show the local LPAR's affinity score.
	 *
	 * 0xB1 selects the Affinity_Doमुख्य_Info_By_Partition subcall.
	 * The score is at byte 0xB in the output buffer.
	 */
	स_रखो(&buf->params, 0, माप(buf->params));
	buf->params.counter_request = cpu_to_be32(0xB1);
	buf->params.starting_index = cpu_to_be32(-1);	/* local LPAR */
	buf->params.counter_info_version_in = 0x5;	/* v5+ क्रम score */
	ret = plpar_hcall_norets(H_GET_PERF_COUNTER_INFO, virt_to_phys(buf),
				 माप(*buf));
	अगर (ret != H_SUCCESS) अणु
		pr_debug("hcall failed: H_GET_PERF_COUNTER_INFO: %ld, %x\n",
			 ret, be32_to_cpu(buf->params.detail_rc));
		जाओ out;
	पूर्ण
	affinity_score = buf->bytes[0xB];
	seq_म_लिखो(m, "partition_affinity_score=%u\n", affinity_score);
out:
	kमुक्त(buf);
पूर्ण

अटल अचिन्हित h_pic(अचिन्हित दीर्घ *pool_idle_समय,
		      अचिन्हित दीर्घ *num_procs)
अणु
	अचिन्हित दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall(H_PIC, retbuf);

	*pool_idle_समय = retbuf[0];
	*num_procs = retbuf[1];

	वापस rc;
पूर्ण

/*
 * parse_ppp_data
 * Parse out the data वापसed from h_get_ppp and h_pic
 */
अटल व्योम parse_ppp_data(काष्ठा seq_file *m)
अणु
	काष्ठा hvcall_ppp_data ppp_data;
	काष्ठा device_node *root;
	स्थिर __be32 *perf_level;
	पूर्णांक rc;

	rc = h_get_ppp(&ppp_data);
	अगर (rc)
		वापस;

	seq_म_लिखो(m, "partition_entitled_capacity=%lld\n",
	           ppp_data.entitlement);
	seq_म_लिखो(m, "group=%d\n", ppp_data.group_num);
	seq_म_लिखो(m, "system_active_processors=%d\n",
	           ppp_data.active_प्रणाली_procs);

	/* pool related entries are appropriate क्रम shared configs */
	अगर (lppaca_shared_proc(get_lppaca())) अणु
		अचिन्हित दीर्घ pool_idle_समय, pool_procs;

		seq_म_लिखो(m, "pool=%d\n", ppp_data.pool_num);

		/* report pool_capacity in percentage */
		seq_म_लिखो(m, "pool_capacity=%d\n",
			   ppp_data.active_procs_in_pool * 100);

		h_pic(&pool_idle_समय, &pool_procs);
		seq_म_लिखो(m, "pool_idle_time=%ld\n", pool_idle_समय);
		seq_म_लिखो(m, "pool_num_procs=%ld\n", pool_procs);
	पूर्ण

	seq_म_लिखो(m, "unallocated_capacity_weight=%d\n",
		   ppp_data.unallocated_weight);
	seq_म_लिखो(m, "capacity_weight=%d\n", ppp_data.weight);
	seq_म_लिखो(m, "capped=%d\n", ppp_data.capped);
	seq_म_लिखो(m, "unallocated_capacity=%lld\n",
		   ppp_data.unallocated_entitlement);

	/* The last bits of inक्रमmation वापसed from h_get_ppp are only
	 * valid अगर the ibm,partition-perक्रमmance-parameters-level
	 * property is >= 1.
	 */
	root = of_find_node_by_path("/");
	अगर (root) अणु
		perf_level = of_get_property(root,
				"ibm,partition-performance-parameters-level",
					     शून्य);
		अगर (perf_level && (be32_to_cpup(perf_level) >= 1)) अणु
			seq_म_लिखो(m,
			    "physical_procs_allocated_to_virtualization=%d\n",
				   ppp_data.phys_platक्रमm_procs);
			seq_म_लिखो(m, "max_proc_capacity_available=%d\n",
				   ppp_data.max_proc_cap_avail);
			seq_म_लिखो(m, "entitled_proc_capacity_available=%d\n",
				   ppp_data.entitled_proc_cap_avail);
		पूर्ण

		of_node_put(root);
	पूर्ण
पूर्ण

/**
 * parse_mpp_data
 * Parse out data वापसed from h_get_mpp
 */
अटल व्योम parse_mpp_data(काष्ठा seq_file *m)
अणु
	काष्ठा hvcall_mpp_data mpp_data;
	पूर्णांक rc;

	rc = h_get_mpp(&mpp_data);
	अगर (rc)
		वापस;

	seq_म_लिखो(m, "entitled_memory=%ld\n", mpp_data.entitled_mem);

	अगर (mpp_data.mapped_mem != -1)
		seq_म_लिखो(m, "mapped_entitled_memory=%ld\n",
		           mpp_data.mapped_mem);

	seq_म_लिखो(m, "entitled_memory_group_number=%d\n", mpp_data.group_num);
	seq_म_लिखो(m, "entitled_memory_pool_number=%d\n", mpp_data.pool_num);

	seq_म_लिखो(m, "entitled_memory_weight=%d\n", mpp_data.mem_weight);
	seq_म_लिखो(m, "unallocated_entitled_memory_weight=%d\n",
	           mpp_data.unallocated_mem_weight);
	seq_म_लिखो(m, "unallocated_io_mapping_entitlement=%ld\n",
	           mpp_data.unallocated_entitlement);

	अगर (mpp_data.pool_size != -1)
		seq_म_लिखो(m, "entitled_memory_pool_size=%ld bytes\n",
		           mpp_data.pool_size);

	seq_म_लिखो(m, "entitled_memory_loan_request=%ld\n",
	           mpp_data.loan_request);

	seq_म_लिखो(m, "backing_memory=%ld bytes\n", mpp_data.backing_mem);
पूर्ण

/**
 * parse_mpp_x_data
 * Parse out data वापसed from h_get_mpp_x
 */
अटल व्योम parse_mpp_x_data(काष्ठा seq_file *m)
अणु
	काष्ठा hvcall_mpp_x_data mpp_x_data;

	अगर (!firmware_has_feature(FW_FEATURE_XCMO))
		वापस;
	अगर (h_get_mpp_x(&mpp_x_data))
		वापस;

	seq_म_लिखो(m, "coalesced_bytes=%ld\n", mpp_x_data.coalesced_bytes);

	अगर (mpp_x_data.pool_coalesced_bytes)
		seq_म_लिखो(m, "pool_coalesced_bytes=%ld\n",
			   mpp_x_data.pool_coalesced_bytes);
	अगर (mpp_x_data.pool_purr_cycles)
		seq_म_लिखो(m, "coalesce_pool_purr=%ld\n", mpp_x_data.pool_purr_cycles);
	अगर (mpp_x_data.pool_spurr_cycles)
		seq_म_लिखो(m, "coalesce_pool_spurr=%ld\n", mpp_x_data.pool_spurr_cycles);
पूर्ण

#घोषणा SPLPAR_CHARACTERISTICS_TOKEN 20
#घोषणा SPLPAR_MAXLENGTH 1026*(माप(अक्षर))

/*
 * parse_प्रणाली_parameter_string()
 * Retrieve the potential_processors, max_entitled_capacity and मित्रs
 * through the get-प्रणाली-parameter rtas call.  Replace keyword strings as
 * necessary.
 */
अटल व्योम parse_प्रणाली_parameter_string(काष्ठा seq_file *m)
अणु
	पूर्णांक call_status;

	अचिन्हित अक्षर *local_buffer = kदो_स्मृति(SPLPAR_MAXLENGTH, GFP_KERNEL);
	अगर (!local_buffer) अणु
		prपूर्णांकk(KERN_ERR "%s %s kmalloc failure at line %d\n",
		       __खाता__, __func__, __LINE__);
		वापस;
	पूर्ण

	spin_lock(&rtas_data_buf_lock);
	स_रखो(rtas_data_buf, 0, SPLPAR_MAXLENGTH);
	call_status = rtas_call(rtas_token("ibm,get-system-parameter"), 3, 1,
				शून्य,
				SPLPAR_CHARACTERISTICS_TOKEN,
				__pa(rtas_data_buf),
				RTAS_DATA_BUF_SIZE);
	स_नकल(local_buffer, rtas_data_buf, SPLPAR_MAXLENGTH);
	local_buffer[SPLPAR_MAXLENGTH - 1] = '\0';
	spin_unlock(&rtas_data_buf_lock);

	अगर (call_status != 0) अणु
		prपूर्णांकk(KERN_INFO
		       "%s %s Error calling get-system-parameter (0x%x)\n",
		       __खाता__, __func__, call_status);
	पूर्ण अन्यथा अणु
		पूर्णांक splpar_म_माप;
		पूर्णांक idx, w_idx;
		अक्षर *workbuffer = kzalloc(SPLPAR_MAXLENGTH, GFP_KERNEL);
		अगर (!workbuffer) अणु
			prपूर्णांकk(KERN_ERR "%s %s kmalloc failure at line %d\n",
			       __खाता__, __func__, __LINE__);
			kमुक्त(local_buffer);
			वापस;
		पूर्ण
#अगर_घोषित LPARCFG_DEBUG
		prपूर्णांकk(KERN_INFO "success calling get-system-parameter\n");
#पूर्ण_अगर
		splpar_म_माप = local_buffer[0] * 256 + local_buffer[1];
		local_buffer += 2;	/* step over म_माप value */

		w_idx = 0;
		idx = 0;
		जबतक ((*local_buffer) && (idx < splpar_म_माप)) अणु
			workbuffer[w_idx++] = local_buffer[idx++];
			अगर ((local_buffer[idx] == ',')
			    || (local_buffer[idx] == '\0')) अणु
				workbuffer[w_idx] = '\0';
				अगर (w_idx) अणु
					/* aव्योम the empty string */
					seq_म_लिखो(m, "%s\n", workbuffer);
				पूर्ण
				स_रखो(workbuffer, 0, SPLPAR_MAXLENGTH);
				idx++;	/* skip the comma */
				w_idx = 0;
			पूर्ण अन्यथा अगर (local_buffer[idx] == '=') अणु
				/* code here to replace workbuffer contents
				   with dअगरferent keyword strings */
				अगर (0 == म_भेद(workbuffer, "MaxEntCap")) अणु
					म_नकल(workbuffer,
					       "partition_max_entitled_capacity");
					w_idx = म_माप(workbuffer);
				पूर्ण
				अगर (0 == म_भेद(workbuffer, "MaxPlatProcs")) अणु
					म_नकल(workbuffer,
					       "system_potential_processors");
					w_idx = म_माप(workbuffer);
				पूर्ण
			पूर्ण
		पूर्ण
		kमुक्त(workbuffer);
		local_buffer -= 2;	/* back up over म_माप value */
	पूर्ण
	kमुक्त(local_buffer);
पूर्ण

/* Return the number of processors in the प्रणाली.
 * This function पढ़ोs through the device tree and counts
 * the भव processors, this करोes not include thपढ़ोs.
 */
अटल पूर्णांक lparcfg_count_active_processors(व्योम)
अणु
	काष्ठा device_node *cpus_dn;
	पूर्णांक count = 0;

	क्रम_each_node_by_type(cpus_dn, "cpu") अणु
#अगर_घोषित LPARCFG_DEBUG
		prपूर्णांकk(KERN_ERR "cpus_dn %p\n", cpus_dn);
#पूर्ण_अगर
		count++;
	पूर्ण
	वापस count;
पूर्ण

अटल व्योम pseries_cmo_data(काष्ठा seq_file *m)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ cmo_faults = 0;
	अचिन्हित दीर्घ cmo_fault_समय = 0;

	seq_म_लिखो(m, "cmo_enabled=%d\n", firmware_has_feature(FW_FEATURE_CMO));

	अगर (!firmware_has_feature(FW_FEATURE_CMO))
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		cmo_faults += be64_to_cpu(lppaca_of(cpu).cmo_faults);
		cmo_fault_समय += be64_to_cpu(lppaca_of(cpu).cmo_fault_समय);
	पूर्ण

	seq_म_लिखो(m, "cmo_faults=%lu\n", cmo_faults);
	seq_म_लिखो(m, "cmo_fault_time_usec=%lu\n",
		   cmo_fault_समय / tb_ticks_per_usec);
	seq_म_लिखो(m, "cmo_primary_psp=%d\n", cmo_get_primary_psp());
	seq_म_लिखो(m, "cmo_secondary_psp=%d\n", cmo_get_secondary_psp());
	seq_म_लिखो(m, "cmo_page_size=%lu\n", cmo_get_page_size());
पूर्ण

अटल व्योम splpar_dispatch_data(काष्ठा seq_file *m)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ dispatches = 0;
	अचिन्हित दीर्घ dispatch_dispersions = 0;

	क्रम_each_possible_cpu(cpu) अणु
		dispatches += be32_to_cpu(lppaca_of(cpu).yield_count);
		dispatch_dispersions +=
			be32_to_cpu(lppaca_of(cpu).dispersion_count);
	पूर्ण

	seq_म_लिखो(m, "dispatches=%lu\n", dispatches);
	seq_म_लिखो(m, "dispatch_dispersions=%lu\n", dispatch_dispersions);
पूर्ण

अटल व्योम parse_em_data(काष्ठा seq_file *m)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	अगर (firmware_has_feature(FW_FEATURE_LPAR) &&
	    plpar_hcall(H_GET_EM_PARMS, retbuf) == H_SUCCESS)
		seq_म_लिखो(m, "power_mode_data=%016lx\n", retbuf[0]);
पूर्ण

अटल व्योम maxmem_data(काष्ठा seq_file *m)
अणु
	अचिन्हित दीर्घ maxmem = 0;

	maxmem += (अचिन्हित दीर्घ)drmem_info->n_lmbs * drmem_info->lmb_size;
	maxmem += hugetlb_total_pages() * PAGE_SIZE;

	seq_म_लिखो(m, "MaxMem=%lu\n", maxmem);
पूर्ण

अटल पूर्णांक pseries_lparcfg_data(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक partition_potential_processors;
	पूर्णांक partition_active_processors;
	काष्ठा device_node *rtas_node;
	स्थिर __be32 *lrdrp = शून्य;

	rtas_node = of_find_node_by_path("/rtas");
	अगर (rtas_node)
		lrdrp = of_get_property(rtas_node, "ibm,lrdr-capacity", शून्य);

	अगर (lrdrp == शून्य) अणु
		partition_potential_processors = vdso_data->processorCount;
	पूर्ण अन्यथा अणु
		partition_potential_processors = be32_to_cpup(lrdrp + 4);
	पूर्ण
	of_node_put(rtas_node);

	partition_active_processors = lparcfg_count_active_processors();

	अगर (firmware_has_feature(FW_FEATURE_SPLPAR)) अणु
		/* this call handles the ibm,get-प्रणाली-parameter contents */
		parse_प्रणाली_parameter_string(m);
		parse_ppp_data(m);
		parse_mpp_data(m);
		parse_mpp_x_data(m);
		pseries_cmo_data(m);
		splpar_dispatch_data(m);

		seq_म_लिखो(m, "purr=%ld\n", get_purr());
		seq_म_लिखो(m, "tbr=%ld\n", mftb());
	पूर्ण अन्यथा अणु		/* non SPLPAR हाल */

		seq_म_लिखो(m, "system_active_processors=%d\n",
			   partition_potential_processors);

		seq_म_लिखो(m, "system_potential_processors=%d\n",
			   partition_potential_processors);

		seq_म_लिखो(m, "partition_max_entitled_capacity=%d\n",
			   partition_potential_processors * 100);

		seq_म_लिखो(m, "partition_entitled_capacity=%d\n",
			   partition_active_processors * 100);
	पूर्ण

	show_gpci_data(m);

	seq_म_लिखो(m, "partition_active_processors=%d\n",
		   partition_active_processors);

	seq_म_लिखो(m, "partition_potential_processors=%d\n",
		   partition_potential_processors);

	seq_म_लिखो(m, "shared_processor_mode=%d\n",
		   lppaca_shared_proc(get_lppaca()));

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	seq_म_लिखो(m, "slb_size=%d\n", mmu_slb_size);
#पूर्ण_अगर
	parse_em_data(m);
	maxmem_data(m);

	seq_म_लिखो(m, "security_flavor=%u\n", pseries_security_flavor);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार update_ppp(u64 *entitlement, u8 *weight)
अणु
	काष्ठा hvcall_ppp_data ppp_data;
	u8 new_weight;
	u64 new_entitled;
	sमाप_प्रकार retval;

	/* Get our current parameters */
	retval = h_get_ppp(&ppp_data);
	अगर (retval)
		वापस retval;

	अगर (entitlement) अणु
		new_weight = ppp_data.weight;
		new_entitled = *entitlement;
	पूर्ण अन्यथा अगर (weight) अणु
		new_weight = *weight;
		new_entitled = ppp_data.entitlement;
	पूर्ण अन्यथा
		वापस -EINVAL;

	pr_debug("%s: current_entitled = %llu, current_weight = %u\n",
		 __func__, ppp_data.entitlement, ppp_data.weight);

	pr_debug("%s: new_entitled = %llu, new_weight = %u\n",
		 __func__, new_entitled, new_weight);

	retval = plpar_hcall_norets(H_SET_PPP, new_entitled, new_weight);
	वापस retval;
पूर्ण

/**
 * update_mpp
 *
 * Update the memory entitlement and weight क्रम the partition.  Caller must
 * specअगरy either a new entitlement or weight, not both, to be updated
 * since the h_set_mpp call takes both entitlement and weight as parameters.
 */
अटल sमाप_प्रकार update_mpp(u64 *entitlement, u8 *weight)
अणु
	काष्ठा hvcall_mpp_data mpp_data;
	u64 new_entitled;
	u8 new_weight;
	sमाप_प्रकार rc;

	अगर (entitlement) अणु
		/* Check with vio to ensure the new memory entitlement
		 * can be handled.
		 */
		rc = vio_cmo_entitlement_update(*entitlement);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = h_get_mpp(&mpp_data);
	अगर (rc)
		वापस rc;

	अगर (entitlement) अणु
		new_weight = mpp_data.mem_weight;
		new_entitled = *entitlement;
	पूर्ण अन्यथा अगर (weight) अणु
		new_weight = *weight;
		new_entitled = mpp_data.entitled_mem;
	पूर्ण अन्यथा
		वापस -EINVAL;

	pr_debug("%s: current_entitled = %lu, current_weight = %u\n",
	         __func__, mpp_data.entitled_mem, mpp_data.mem_weight);

	pr_debug("%s: new_entitled = %llu, new_weight = %u\n",
		 __func__, new_entitled, new_weight);

	rc = plpar_hcall_norets(H_SET_MPP, new_entitled, new_weight);
	वापस rc;
पूर्ण

/*
 * Interface क्रम changing प्रणाली parameters (variable capacity weight
 * and entitled capacity).  Format of input is "param_name=value";
 * anything after value is ignored.  Valid parameters at this समय are
 * "partition_entitled_capacity" and "capacity_weight".  We use
 * H_SET_PPP to alter parameters.
 *
 * This function should be invoked only on प्रणालीs with
 * FW_FEATURE_SPLPAR.
 */
अटल sमाप_प्रकार lparcfg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user * buf,
			     माप_प्रकार count, loff_t * off)
अणु
	अक्षर kbuf[64];
	अक्षर *पंचांगp;
	u64 new_entitled, *new_entitled_ptr = &new_entitled;
	u8 new_weight, *new_weight_ptr = &new_weight;
	sमाप_प्रकार retval;

	अगर (!firmware_has_feature(FW_FEATURE_SPLPAR))
		वापस -EINVAL;

	अगर (count > माप(kbuf))
		वापस -EINVAL;

	अगर (copy_from_user(kbuf, buf, count))
		वापस -EFAULT;

	kbuf[count - 1] = '\0';
	पंचांगp = म_अक्षर(kbuf, '=');
	अगर (!पंचांगp)
		वापस -EINVAL;

	*पंचांगp++ = '\0';

	अगर (!म_भेद(kbuf, "partition_entitled_capacity")) अणु
		अक्षर *endp;
		*new_entitled_ptr = (u64) simple_म_से_अदीर्घ(पंचांगp, &endp, 10);
		अगर (endp == पंचांगp)
			वापस -EINVAL;

		retval = update_ppp(new_entitled_ptr, शून्य);
	पूर्ण अन्यथा अगर (!म_भेद(kbuf, "capacity_weight")) अणु
		अक्षर *endp;
		*new_weight_ptr = (u8) simple_म_से_अदीर्घ(पंचांगp, &endp, 10);
		अगर (endp == पंचांगp)
			वापस -EINVAL;

		retval = update_ppp(शून्य, new_weight_ptr);
	पूर्ण अन्यथा अगर (!म_भेद(kbuf, "entitled_memory")) अणु
		अक्षर *endp;
		*new_entitled_ptr = (u64) simple_म_से_अदीर्घ(पंचांगp, &endp, 10);
		अगर (endp == पंचांगp)
			वापस -EINVAL;

		retval = update_mpp(new_entitled_ptr, शून्य);
	पूर्ण अन्यथा अगर (!म_भेद(kbuf, "entitled_memory_weight")) अणु
		अक्षर *endp;
		*new_weight_ptr = (u8) simple_म_से_अदीर्घ(पंचांगp, &endp, 10);
		अगर (endp == पंचांगp)
			वापस -EINVAL;

		retval = update_mpp(शून्य, new_weight_ptr);
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (retval == H_SUCCESS || retval == H_CONSTRAINED) अणु
		retval = count;
	पूर्ण अन्यथा अगर (retval == H_BUSY) अणु
		retval = -EBUSY;
	पूर्ण अन्यथा अगर (retval == H_HARDWARE) अणु
		retval = -EIO;
	पूर्ण अन्यथा अगर (retval == H_PARAMETER) अणु
		retval = -EINVAL;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक lparcfg_data(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा device_node *rootdn;
	स्थिर अक्षर *model = "";
	स्थिर अक्षर *प्रणाली_id = "";
	स्थिर अक्षर *पंचांगp;
	स्थिर __be32 *lp_index_ptr;
	अचिन्हित पूर्णांक lp_index = 0;

	seq_म_लिखो(m, "%s %s\n", MODULE_NAME, MODULE_VERS);

	rootdn = of_find_node_by_path("/");
	अगर (rootdn) अणु
		पंचांगp = of_get_property(rootdn, "model", शून्य);
		अगर (पंचांगp)
			model = पंचांगp;
		पंचांगp = of_get_property(rootdn, "system-id", शून्य);
		अगर (पंचांगp)
			प्रणाली_id = पंचांगp;
		lp_index_ptr = of_get_property(rootdn, "ibm,partition-no",
					शून्य);
		अगर (lp_index_ptr)
			lp_index = be32_to_cpup(lp_index_ptr);
		of_node_put(rootdn);
	पूर्ण
	seq_म_लिखो(m, "serial_number=%s\n", प्रणाली_id);
	seq_म_लिखो(m, "system_type=%s\n", model);
	seq_म_लिखो(m, "partition_id=%d\n", (पूर्णांक)lp_index);

	वापस pseries_lparcfg_data(m, v);
पूर्ण

अटल पूर्णांक lparcfg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, lparcfg_data, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops lparcfg_proc_ops = अणु
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= lparcfg_ग_लिखो,
	.proc_खोलो	= lparcfg_खोलो,
	.proc_release	= single_release,
	.proc_lseek	= seq_lseek,
पूर्ण;

अटल पूर्णांक __init lparcfg_init(व्योम)
अणु
	umode_t mode = 0444;

	/* Allow writing अगर we have FW_FEATURE_SPLPAR */
	अगर (firmware_has_feature(FW_FEATURE_SPLPAR))
		mode |= 0200;

	अगर (!proc_create("powerpc/lparcfg", mode, शून्य, &lparcfg_proc_ops)) अणु
		prपूर्णांकk(KERN_ERR "Failed to create powerpc/lparcfg\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण
machine_device_initcall(pseries, lparcfg_init);
