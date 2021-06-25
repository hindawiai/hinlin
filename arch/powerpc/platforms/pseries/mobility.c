<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम Partition Mobility/Migration
 *
 * Copyright (C) 2010 Nathan Fontenot
 * Copyright (C) 2010 IBM Corporation
 */


#घोषणा pr_fmt(fmt) "mobility: " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/stop_machine.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/stringअगरy.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश "pseries.h"
#समावेश "../../kernel/cacheinfo.h"

अटल काष्ठा kobject *mobility_kobj;

काष्ठा update_props_workarea अणु
	__be32 phandle;
	__be32 state;
	__be64 reserved;
	__be32 nprops;
पूर्ण __packed;

#घोषणा NODE_ACTION_MASK	0xff000000
#घोषणा NODE_COUNT_MASK		0x00ffffff

#घोषणा DELETE_DT_NODE	0x01000000
#घोषणा UPDATE_DT_NODE	0x02000000
#घोषणा ADD_DT_NODE	0x03000000

#घोषणा MIGRATION_SCOPE	(1)
#घोषणा PRRN_SCOPE -2

अटल पूर्णांक mobility_rtas_call(पूर्णांक token, अक्षर *buf, s32 scope)
अणु
	पूर्णांक rc;

	spin_lock(&rtas_data_buf_lock);

	स_नकल(rtas_data_buf, buf, RTAS_DATA_BUF_SIZE);
	rc = rtas_call(token, 2, 1, शून्य, rtas_data_buf, scope);
	स_नकल(buf, rtas_data_buf, RTAS_DATA_BUF_SIZE);

	spin_unlock(&rtas_data_buf_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक delete_dt_node(काष्ठा device_node *dn)
अणु
	pr_debug("removing node %pOFfp\n", dn);
	dlpar_detach_node(dn);
	वापस 0;
पूर्ण

अटल पूर्णांक update_dt_property(काष्ठा device_node *dn, काष्ठा property **prop,
			      स्थिर अक्षर *name, u32 vd, अक्षर *value)
अणु
	काष्ठा property *new_prop = *prop;
	पूर्णांक more = 0;

	/* A negative 'vd' value indicates that only part of the new property
	 * value is contained in the buffer and we need to call
	 * ibm,update-properties again to get the rest of the value.
	 *
	 * A negative value is also the two's compliment of the actual value.
	 */
	अगर (vd & 0x80000000) अणु
		vd = ~vd + 1;
		more = 1;
	पूर्ण

	अगर (new_prop) अणु
		/* partial property fixup */
		अक्षर *new_data = kzalloc(new_prop->length + vd, GFP_KERNEL);
		अगर (!new_data)
			वापस -ENOMEM;

		स_नकल(new_data, new_prop->value, new_prop->length);
		स_नकल(new_data + new_prop->length, value, vd);

		kमुक्त(new_prop->value);
		new_prop->value = new_data;
		new_prop->length += vd;
	पूर्ण अन्यथा अणु
		new_prop = kzalloc(माप(*new_prop), GFP_KERNEL);
		अगर (!new_prop)
			वापस -ENOMEM;

		new_prop->name = kstrdup(name, GFP_KERNEL);
		अगर (!new_prop->name) अणु
			kमुक्त(new_prop);
			वापस -ENOMEM;
		पूर्ण

		new_prop->length = vd;
		new_prop->value = kzalloc(new_prop->length, GFP_KERNEL);
		अगर (!new_prop->value) अणु
			kमुक्त(new_prop->name);
			kमुक्त(new_prop);
			वापस -ENOMEM;
		पूर्ण

		स_नकल(new_prop->value, value, vd);
		*prop = new_prop;
	पूर्ण

	अगर (!more) अणु
		pr_debug("updating node %pOF property %s\n", dn, name);
		of_update_property(dn, new_prop);
		*prop = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक update_dt_node(काष्ठा device_node *dn, s32 scope)
अणु
	काष्ठा update_props_workarea *upwa;
	काष्ठा property *prop = शून्य;
	पूर्णांक i, rc, rtas_rc;
	अक्षर *prop_data;
	अक्षर *rtas_buf;
	पूर्णांक update_properties_token;
	u32 nprops;
	u32 vd;

	update_properties_token = rtas_token("ibm,update-properties");
	अगर (update_properties_token == RTAS_UNKNOWN_SERVICE)
		वापस -EINVAL;

	rtas_buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!rtas_buf)
		वापस -ENOMEM;

	upwa = (काष्ठा update_props_workarea *)&rtas_buf[0];
	upwa->phandle = cpu_to_be32(dn->phandle);

	करो अणु
		rtas_rc = mobility_rtas_call(update_properties_token, rtas_buf,
					scope);
		अगर (rtas_rc < 0)
			अवरोध;

		prop_data = rtas_buf + माप(*upwa);
		nprops = be32_to_cpu(upwa->nprops);

		/* On the first call to ibm,update-properties क्रम a node the
		 * the first property value descriptor contains an empty
		 * property name, the property value length encoded as u32,
		 * and the property value is the node path being updated.
		 */
		अगर (*prop_data == 0) अणु
			prop_data++;
			vd = be32_to_cpu(*(__be32 *)prop_data);
			prop_data += vd + माप(vd);
			nprops--;
		पूर्ण

		क्रम (i = 0; i < nprops; i++) अणु
			अक्षर *prop_name;

			prop_name = prop_data;
			prop_data += म_माप(prop_name) + 1;
			vd = be32_to_cpu(*(__be32 *)prop_data);
			prop_data += माप(vd);

			चयन (vd) अणु
			हाल 0x00000000:
				/* name only property, nothing to करो */
				अवरोध;

			हाल 0x80000000:
				of_हटाओ_property(dn, of_find_property(dn,
							prop_name, शून्य));
				prop = शून्य;
				अवरोध;

			शेष:
				rc = update_dt_property(dn, &prop, prop_name,
							vd, prop_data);
				अगर (rc) अणु
					pr_err("updating %s property failed: %d\n",
					       prop_name, rc);
				पूर्ण

				prop_data += vd;
				अवरोध;
			पूर्ण

			cond_resched();
		पूर्ण

		cond_resched();
	पूर्ण जबतक (rtas_rc == 1);

	kमुक्त(rtas_buf);
	वापस 0;
पूर्ण

अटल पूर्णांक add_dt_node(काष्ठा device_node *parent_dn, __be32 drc_index)
अणु
	काष्ठा device_node *dn;
	पूर्णांक rc;

	dn = dlpar_configure_connector(drc_index, parent_dn);
	अगर (!dn)
		वापस -ENOENT;

	rc = dlpar_attach_node(dn, parent_dn);
	अगर (rc)
		dlpar_मुक्त_cc_nodes(dn);

	pr_debug("added node %pOFfp\n", dn);

	वापस rc;
पूर्ण

पूर्णांक pseries_devicetree_update(s32 scope)
अणु
	अक्षर *rtas_buf;
	__be32 *data;
	पूर्णांक update_nodes_token;
	पूर्णांक rc;

	update_nodes_token = rtas_token("ibm,update-nodes");
	अगर (update_nodes_token == RTAS_UNKNOWN_SERVICE)
		वापस 0;

	rtas_buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!rtas_buf)
		वापस -ENOMEM;

	करो अणु
		rc = mobility_rtas_call(update_nodes_token, rtas_buf, scope);
		अगर (rc && rc != 1)
			अवरोध;

		data = (__be32 *)rtas_buf + 4;
		जबतक (be32_to_cpu(*data) & NODE_ACTION_MASK) अणु
			पूर्णांक i;
			u32 action = be32_to_cpu(*data) & NODE_ACTION_MASK;
			u32 node_count = be32_to_cpu(*data) & NODE_COUNT_MASK;

			data++;

			क्रम (i = 0; i < node_count; i++) अणु
				काष्ठा device_node *np;
				__be32 phandle = *data++;
				__be32 drc_index;

				np = of_find_node_by_phandle(be32_to_cpu(phandle));
				अगर (!np) अणु
					pr_warn("Failed lookup: phandle 0x%x for action 0x%x\n",
						be32_to_cpu(phandle), action);
					जारी;
				पूर्ण

				चयन (action) अणु
				हाल DELETE_DT_NODE:
					delete_dt_node(np);
					अवरोध;
				हाल UPDATE_DT_NODE:
					update_dt_node(np, scope);
					अवरोध;
				हाल ADD_DT_NODE:
					drc_index = *data++;
					add_dt_node(np, drc_index);
					अवरोध;
				पूर्ण

				of_node_put(np);
				cond_resched();
			पूर्ण
		पूर्ण

		cond_resched();
	पूर्ण जबतक (rc == 1);

	kमुक्त(rtas_buf);
	वापस rc;
पूर्ण

व्योम post_mobility_fixup(व्योम)
अणु
	पूर्णांक rc;

	rtas_activate_firmware();

	/*
	 * We करोn't want CPUs to go online/offline जबतक the device
	 * tree is being updated.
	 */
	cpus_पढ़ो_lock();

	/*
	 * It's common क्रम the destination firmware to replace cache
	 * nodes.  Release all of the cacheinfo hierarchy's references
	 * beक्रमe updating the device tree.
	 */
	cacheinfo_tearकरोwn();

	rc = pseries_devicetree_update(MIGRATION_SCOPE);
	अगर (rc)
		pr_err("device tree update failed: %d\n", rc);

	cacheinfo_rebuild();

	cpus_पढ़ो_unlock();

	/* Possibly चयन to a new L1 flush type */
	pseries_setup_security_mitigations();

	/* Reinitialise प्रणाली inक्रमmation क्रम hv-24x7 */
	पढ़ो_24x7_sys_info();

	वापस;
पूर्ण

अटल पूर्णांक poll_vasi_state(u64 handle, अचिन्हित दीर्घ *res)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ hvrc;
	पूर्णांक ret;

	hvrc = plpar_hcall(H_VASI_STATE, retbuf, handle);
	चयन (hvrc) अणु
	हाल H_SUCCESS:
		ret = 0;
		*res = retbuf[0];
		अवरोध;
	हाल H_PARAMETER:
		ret = -EINVAL;
		अवरोध;
	हाल H_FUNCTION:
		ret = -EOPNOTSUPP;
		अवरोध;
	हाल H_HARDWARE:
	शेष:
		pr_err("unexpected H_VASI_STATE result %ld\n", hvrc);
		ret = -EIO;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक रुको_क्रम_vasi_session_suspending(u64 handle)
अणु
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	/*
	 * Wait क्रम transition from H_VASI_ENABLED to
	 * H_VASI_SUSPENDING. Treat anything अन्यथा as an error.
	 */
	जबतक (true) अणु
		ret = poll_vasi_state(handle, &state);

		अगर (ret != 0 || state == H_VASI_SUSPENDING) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (state == H_VASI_ENABLED) अणु
			ssleep(1);
		पूर्ण अन्यथा अणु
			pr_err("unexpected H_VASI_STATE result %lu\n", state);
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Proceed even अगर H_VASI_STATE is unavailable. If H_JOIN or
	 * ibm,suspend-me are also unimplemented, we'll recover then.
	 */
	अगर (ret == -EOPNOTSUPP)
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम prod_single(अचिन्हित पूर्णांक target_cpu)
अणु
	दीर्घ hvrc;
	पूर्णांक hwid;

	hwid = get_hard_smp_processor_id(target_cpu);
	hvrc = plpar_hcall_norets(H_PROD, hwid);
	अगर (hvrc == H_SUCCESS)
		वापस;
	pr_err_ratelimited("H_PROD of CPU %u (hwid %d) error: %ld\n",
			   target_cpu, hwid, hvrc);
पूर्ण

अटल व्योम prod_others(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu != smp_processor_id())
			prod_single(cpu);
	पूर्ण
पूर्ण

अटल u16 clamp_slb_size(व्योम)
अणु
	u16 prev = mmu_slb_size;

	slb_set_size(SLB_MIN_SIZE);

	वापस prev;
पूर्ण

अटल पूर्णांक करो_suspend(व्योम)
अणु
	u16 saved_slb_size;
	पूर्णांक status;
	पूर्णांक ret;

	pr_info("calling ibm,suspend-me on CPU %i\n", smp_processor_id());

	/*
	 * The destination processor model may have fewer SLB entries
	 * than the source. We reduce mmu_slb_size to a safe minimum
	 * beक्रमe suspending in order to minimize the possibility of
	 * programming non-existent entries on the destination. If
	 * suspend fails, we restore it beक्रमe वापसing. On success
	 * the OF reconfig path will update it from the new device
	 * tree after resuming on the destination.
	 */
	saved_slb_size = clamp_slb_size();

	ret = rtas_ibm_suspend_me(&status);
	अगर (ret != 0) अणु
		pr_err("ibm,suspend-me error: %d\n", status);
		slb_set_size(saved_slb_size);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * काष्ठा pseries_suspend_info - State shared between CPUs क्रम join/suspend.
 * @counter: Thपढ़ोs are to increment this upon resuming from suspend
 *           or अगर an error is received from H_JOIN. The thपढ़ो which perक्रमms
 *           the first increment (i.e. sets it to 1) is responsible क्रम
 *           waking the other thपढ़ोs.
 * @करोne: False अगर join/suspend is in progress. True अगर the operation is
 *        complete (successful or not).
 */
काष्ठा pseries_suspend_info अणु
	atomic_t counter;
	bool करोne;
पूर्ण;

अटल पूर्णांक करो_join(व्योम *arg)
अणु
	काष्ठा pseries_suspend_info *info = arg;
	atomic_t *counter = &info->counter;
	दीर्घ hvrc;
	पूर्णांक ret;

retry:
	/* Must ensure MSR.EE off क्रम H_JOIN. */
	hard_irq_disable();
	hvrc = plpar_hcall_norets(H_JOIN);

	चयन (hvrc) अणु
	हाल H_CONTINUE:
		/*
		 * All other CPUs are offline or in H_JOIN. This CPU
		 * attempts the suspend.
		 */
		ret = करो_suspend();
		अवरोध;
	हाल H_SUCCESS:
		/*
		 * The suspend is complete and this cpu has received a
		 * prod, or we've received a stray prod from unrelated
		 * code (e.g. paravirt spinlocks) and we need to join
		 * again.
		 *
		 * This barrier orders the वापस from H_JOIN above vs
		 * the load of info->करोne. It pairs with the barrier
		 * in the wakeup/prod path below.
		 */
		smp_mb();
		अगर (READ_ONCE(info->करोne) == false) अणु
			pr_info_ratelimited("premature return from H_JOIN on CPU %i, retrying",
					    smp_processor_id());
			जाओ retry;
		पूर्ण
		ret = 0;
		अवरोध;
	हाल H_BAD_MODE:
	हाल H_HARDWARE:
	शेष:
		ret = -EIO;
		pr_err_ratelimited("H_JOIN error %ld on CPU %i\n",
				   hvrc, smp_processor_id());
		अवरोध;
	पूर्ण

	अगर (atomic_inc_वापस(counter) == 1) अणु
		pr_info("CPU %u waking all threads\n", smp_processor_id());
		WRITE_ONCE(info->करोne, true);
		/*
		 * This barrier orders the store to info->करोne vs subsequent
		 * H_PRODs to wake the other CPUs. It pairs with the barrier
		 * in the H_SUCCESS हाल above.
		 */
		smp_mb();
		prod_others();
	पूर्ण
	/*
	 * Execution may have been suspended क्रम several seconds, so
	 * reset the watchकरोg.
	 */
	touch_nmi_watchकरोg();
	वापस ret;
पूर्ण

/*
 * Abort reason code byte 0. We use only the 'Migrating partition' value.
 */
क्रमागत vasi_पातing_entity अणु
	ORCHESTRATOR        = 1,
	VSP_SOURCE          = 2,
	PARTITION_FIRMWARE  = 3,
	PLATFORM_FIRMWARE   = 4,
	VSP_TARGET          = 5,
	MIGRATING_PARTITION = 6,
पूर्ण;

अटल व्योम pseries_cancel_migration(u64 handle, पूर्णांक err)
अणु
	u32 reason_code;
	u32 detail;
	u8 entity;
	दीर्घ hvrc;

	entity = MIGRATING_PARTITION;
	detail = असल(err) & 0xffffff;
	reason_code = (entity << 24) | detail;

	hvrc = plpar_hcall_norets(H_VASI_SIGNAL, handle,
				  H_VASI_SIGNAL_CANCEL, reason_code);
	अगर (hvrc)
		pr_err("H_VASI_SIGNAL error: %ld\n", hvrc);
पूर्ण

अटल पूर्णांक pseries_suspend(u64 handle)
अणु
	स्थिर अचिन्हित पूर्णांक max_attempts = 5;
	अचिन्हित पूर्णांक retry_पूर्णांकerval_ms = 1;
	अचिन्हित पूर्णांक attempt = 1;
	पूर्णांक ret;

	जबतक (true) अणु
		काष्ठा pseries_suspend_info info;
		अचिन्हित दीर्घ vasi_state;
		पूर्णांक vasi_err;

		info = (काष्ठा pseries_suspend_info) अणु
			.counter = ATOMIC_INIT(0),
			.करोne = false,
		पूर्ण;

		ret = stop_machine(करो_join, &info, cpu_online_mask);
		अगर (ret == 0)
			अवरोध;
		/*
		 * Encountered an error. If the VASI stream is still
		 * in Suspending state, it's likely a transient
		 * condition related to some device in the partition
		 * and we can retry in the hope that the cause has
		 * cleared after some delay.
		 *
		 * A better design would allow drivers etc to prepare
		 * क्रम the suspend and aव्योम conditions which prevent
		 * the suspend from succeeding. For now, we have this
		 * mitigation.
		 */
		pr_notice("Partition suspend attempt %u of %u error: %d\n",
			  attempt, max_attempts, ret);

		अगर (attempt == max_attempts)
			अवरोध;

		vasi_err = poll_vasi_state(handle, &vasi_state);
		अगर (vasi_err == 0) अणु
			अगर (vasi_state != H_VASI_SUSPENDING) अणु
				pr_notice("VASI state %lu after failed suspend\n",
					  vasi_state);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (vasi_err != -EOPNOTSUPP) अणु
			pr_err("VASI state poll error: %d", vasi_err);
			अवरोध;
		पूर्ण

		pr_notice("Will retry partition suspend after %u ms\n",
			  retry_पूर्णांकerval_ms);

		msleep(retry_पूर्णांकerval_ms);
		retry_पूर्णांकerval_ms *= 10;
		attempt++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pseries_migrate_partition(u64 handle)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_vasi_session_suspending(handle);
	अगर (ret)
		वापस ret;

	ret = pseries_suspend(handle);
	अगर (ret == 0)
		post_mobility_fixup();
	अन्यथा
		pseries_cancel_migration(handle, ret);

	वापस ret;
पूर्ण

पूर्णांक rtas_syscall_dispatch_ibm_suspend_me(u64 handle)
अणु
	वापस pseries_migrate_partition(handle);
पूर्ण

अटल sमाप_प्रकार migration_store(काष्ठा class *class,
			       काष्ठा class_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	u64 streamid;
	पूर्णांक rc;

	rc = kstrtou64(buf, 0, &streamid);
	अगर (rc)
		वापस rc;

	rc = pseries_migrate_partition(streamid);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

/*
 * Used by drmgr to determine the kernel behavior of the migration पूर्णांकerface.
 *
 * Version 1: Perक्रमms all PAPR requirements क्रम migration including
 *	firmware activation and device tree update.
 */
#घोषणा MIGRATION_API_VERSION	1

अटल CLASS_ATTR_WO(migration);
अटल CLASS_ATTR_STRING(api_version, 0444, __stringअगरy(MIGRATION_API_VERSION));

अटल पूर्णांक __init mobility_sysfs_init(व्योम)
अणु
	पूर्णांक rc;

	mobility_kobj = kobject_create_and_add("mobility", kernel_kobj);
	अगर (!mobility_kobj)
		वापस -ENOMEM;

	rc = sysfs_create_file(mobility_kobj, &class_attr_migration.attr);
	अगर (rc)
		pr_err("unable to create migration sysfs file (%d)\n", rc);

	rc = sysfs_create_file(mobility_kobj, &class_attr_api_version.attr.attr);
	अगर (rc)
		pr_err("unable to create api_version sysfs file (%d)\n", rc);

	वापस 0;
पूर्ण
machine_device_initcall(pseries, mobility_sysfs_init);
