<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम dynamic reconfiguration क्रम PCI, Memory, and CPU
 * Hotplug and Dynamic Logical Partitioning on RPA platक्रमms.
 *
 * Copyright (C) 2009 Nathan Fontenot
 * Copyright (C) 2009 IBM Corporation
 */

#घोषणा pr_fmt(fmt)	"dlpar: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश "of_helpers.h"
#समावेश "pseries.h"

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/rtas.h>

अटल काष्ठा workqueue_काष्ठा *pseries_hp_wq;

काष्ठा pseries_hp_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा pseries_hp_errorlog *errlog;
पूर्ण;

काष्ठा cc_workarea अणु
	__be32	drc_index;
	__be32	zero;
	__be32	name_offset;
	__be32	prop_length;
	__be32	prop_offset;
पूर्ण;

व्योम dlpar_मुक्त_cc_property(काष्ठा property *prop)
अणु
	kमुक्त(prop->name);
	kमुक्त(prop->value);
	kमुक्त(prop);
पूर्ण

अटल काष्ठा property *dlpar_parse_cc_property(काष्ठा cc_workarea *ccwa)
अणु
	काष्ठा property *prop;
	अक्षर *name;
	अक्षर *value;

	prop = kzalloc(माप(*prop), GFP_KERNEL);
	अगर (!prop)
		वापस शून्य;

	name = (अक्षर *)ccwa + be32_to_cpu(ccwa->name_offset);
	prop->name = kstrdup(name, GFP_KERNEL);
	अगर (!prop->name) अणु
		dlpar_मुक्त_cc_property(prop);
		वापस शून्य;
	पूर्ण

	prop->length = be32_to_cpu(ccwa->prop_length);
	value = (अक्षर *)ccwa + be32_to_cpu(ccwa->prop_offset);
	prop->value = kmemdup(value, prop->length, GFP_KERNEL);
	अगर (!prop->value) अणु
		dlpar_मुक्त_cc_property(prop);
		वापस शून्य;
	पूर्ण

	वापस prop;
पूर्ण

अटल काष्ठा device_node *dlpar_parse_cc_node(काष्ठा cc_workarea *ccwa)
अणु
	काष्ठा device_node *dn;
	स्थिर अक्षर *name;

	dn = kzalloc(माप(*dn), GFP_KERNEL);
	अगर (!dn)
		वापस शून्य;

	name = (स्थिर अक्षर *)ccwa + be32_to_cpu(ccwa->name_offset);
	dn->full_name = kstrdup(name, GFP_KERNEL);
	अगर (!dn->full_name) अणु
		kमुक्त(dn);
		वापस शून्य;
	पूर्ण

	of_node_set_flag(dn, OF_DYNAMIC);
	of_node_init(dn);

	वापस dn;
पूर्ण

अटल व्योम dlpar_मुक्त_one_cc_node(काष्ठा device_node *dn)
अणु
	काष्ठा property *prop;

	जबतक (dn->properties) अणु
		prop = dn->properties;
		dn->properties = prop->next;
		dlpar_मुक्त_cc_property(prop);
	पूर्ण

	kमुक्त(dn->full_name);
	kमुक्त(dn);
पूर्ण

व्योम dlpar_मुक्त_cc_nodes(काष्ठा device_node *dn)
अणु
	अगर (dn->child)
		dlpar_मुक्त_cc_nodes(dn->child);

	अगर (dn->sibling)
		dlpar_मुक्त_cc_nodes(dn->sibling);

	dlpar_मुक्त_one_cc_node(dn);
पूर्ण

#घोषणा COMPLETE	0
#घोषणा NEXT_SIBLING    1
#घोषणा NEXT_CHILD      2
#घोषणा NEXT_PROPERTY   3
#घोषणा PREV_PARENT     4
#घोषणा MORE_MEMORY     5
#घोषणा ERR_CFG_USE     -9003

काष्ठा device_node *dlpar_configure_connector(__be32 drc_index,
					      काष्ठा device_node *parent)
अणु
	काष्ठा device_node *dn;
	काष्ठा device_node *first_dn = शून्य;
	काष्ठा device_node *last_dn = शून्य;
	काष्ठा property *property;
	काष्ठा property *last_property = शून्य;
	काष्ठा cc_workarea *ccwa;
	अक्षर *data_buf;
	पूर्णांक cc_token;
	पूर्णांक rc = -1;

	cc_token = rtas_token("ibm,configure-connector");
	अगर (cc_token == RTAS_UNKNOWN_SERVICE)
		वापस शून्य;

	data_buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!data_buf)
		वापस शून्य;

	ccwa = (काष्ठा cc_workarea *)&data_buf[0];
	ccwa->drc_index = drc_index;
	ccwa->zero = 0;

	करो अणु
		/* Since we release the rtas_data_buf lock between configure
		 * connector calls we want to re-populate the rtas_data_buffer
		 * with the contents of the previous call.
		 */
		spin_lock(&rtas_data_buf_lock);

		स_नकल(rtas_data_buf, data_buf, RTAS_DATA_BUF_SIZE);
		rc = rtas_call(cc_token, 2, 1, शून्य, rtas_data_buf, शून्य);
		स_नकल(data_buf, rtas_data_buf, RTAS_DATA_BUF_SIZE);

		spin_unlock(&rtas_data_buf_lock);

		अगर (rtas_busy_delay(rc))
			जारी;

		चयन (rc) अणु
		हाल COMPLETE:
			अवरोध;

		हाल NEXT_SIBLING:
			dn = dlpar_parse_cc_node(ccwa);
			अगर (!dn)
				जाओ cc_error;

			dn->parent = last_dn->parent;
			last_dn->sibling = dn;
			last_dn = dn;
			अवरोध;

		हाल NEXT_CHILD:
			dn = dlpar_parse_cc_node(ccwa);
			अगर (!dn)
				जाओ cc_error;

			अगर (!first_dn) अणु
				dn->parent = parent;
				first_dn = dn;
			पूर्ण अन्यथा अणु
				dn->parent = last_dn;
				अगर (last_dn)
					last_dn->child = dn;
			पूर्ण

			last_dn = dn;
			अवरोध;

		हाल NEXT_PROPERTY:
			property = dlpar_parse_cc_property(ccwa);
			अगर (!property)
				जाओ cc_error;

			अगर (!last_dn->properties)
				last_dn->properties = property;
			अन्यथा
				last_property->next = property;

			last_property = property;
			अवरोध;

		हाल PREV_PARENT:
			last_dn = last_dn->parent;
			अवरोध;

		हाल MORE_MEMORY:
		हाल ERR_CFG_USE:
		शेष:
			prपूर्णांकk(KERN_ERR "Unexpected Error (%d) "
			       "returned from configure-connector\n", rc);
			जाओ cc_error;
		पूर्ण
	पूर्ण जबतक (rc);

cc_error:
	kमुक्त(data_buf);

	अगर (rc) अणु
		अगर (first_dn)
			dlpar_मुक्त_cc_nodes(first_dn);

		वापस शून्य;
	पूर्ण

	वापस first_dn;
पूर्ण

पूर्णांक dlpar_attach_node(काष्ठा device_node *dn, काष्ठा device_node *parent)
अणु
	पूर्णांक rc;

	dn->parent = parent;

	rc = of_attach_node(dn);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failed to add device node %pOF\n", dn);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dlpar_detach_node(काष्ठा device_node *dn)
अणु
	काष्ठा device_node *child;
	पूर्णांक rc;

	child = of_get_next_child(dn, शून्य);
	जबतक (child) अणु
		dlpar_detach_node(child);
		child = of_get_next_child(dn, child);
	पूर्ण

	rc = of_detach_node(dn);
	अगर (rc)
		वापस rc;

	of_node_put(dn);

	वापस 0;
पूर्ण

#घोषणा DR_ENTITY_SENSE		9003
#घोषणा DR_ENTITY_PRESENT	1
#घोषणा DR_ENTITY_UNUSABLE	2
#घोषणा ALLOCATION_STATE	9003
#घोषणा ALLOC_UNUSABLE		0
#घोषणा ALLOC_USABLE		1
#घोषणा ISOLATION_STATE		9001
#घोषणा ISOLATE			0
#घोषणा UNISOLATE		1

पूर्णांक dlpar_acquire_drc(u32 drc_index)
अणु
	पूर्णांक dr_status, rc;

	rc = rtas_call(rtas_token("get-sensor-state"), 2, 2, &dr_status,
		       DR_ENTITY_SENSE, drc_index);
	अगर (rc || dr_status != DR_ENTITY_UNUSABLE)
		वापस -1;

	rc = rtas_set_indicator(ALLOCATION_STATE, drc_index, ALLOC_USABLE);
	अगर (rc)
		वापस rc;

	rc = rtas_set_indicator(ISOLATION_STATE, drc_index, UNISOLATE);
	अगर (rc) अणु
		rtas_set_indicator(ALLOCATION_STATE, drc_index, ALLOC_UNUSABLE);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dlpar_release_drc(u32 drc_index)
अणु
	पूर्णांक dr_status, rc;

	rc = rtas_call(rtas_token("get-sensor-state"), 2, 2, &dr_status,
		       DR_ENTITY_SENSE, drc_index);
	अगर (rc || dr_status != DR_ENTITY_PRESENT)
		वापस -1;

	rc = rtas_set_indicator(ISOLATION_STATE, drc_index, ISOLATE);
	अगर (rc)
		वापस rc;

	rc = rtas_set_indicator(ALLOCATION_STATE, drc_index, ALLOC_UNUSABLE);
	अगर (rc) अणु
		rtas_set_indicator(ISOLATION_STATE, drc_index, UNISOLATE);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dlpar_unisolate_drc(u32 drc_index)
अणु
	पूर्णांक dr_status, rc;

	rc = rtas_call(rtas_token("get-sensor-state"), 2, 2, &dr_status,
				DR_ENTITY_SENSE, drc_index);
	अगर (rc || dr_status != DR_ENTITY_PRESENT)
		वापस -1;

	rtas_set_indicator(ISOLATION_STATE, drc_index, UNISOLATE);

	वापस 0;
पूर्ण

पूर्णांक handle_dlpar_errorlog(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	पूर्णांक rc;

	/* pseries error logs are in BE क्रमmat, convert to cpu type */
	चयन (hp_elog->id_type) अणु
	हाल PSERIES_HP_ELOG_ID_DRC_COUNT:
		hp_elog->_drc_u.drc_count =
				be32_to_cpu(hp_elog->_drc_u.drc_count);
		अवरोध;
	हाल PSERIES_HP_ELOG_ID_DRC_INDEX:
		hp_elog->_drc_u.drc_index =
				be32_to_cpu(hp_elog->_drc_u.drc_index);
		अवरोध;
	हाल PSERIES_HP_ELOG_ID_DRC_IC:
		hp_elog->_drc_u.ic.count =
				be32_to_cpu(hp_elog->_drc_u.ic.count);
		hp_elog->_drc_u.ic.index =
				be32_to_cpu(hp_elog->_drc_u.ic.index);
	पूर्ण

	चयन (hp_elog->resource) अणु
	हाल PSERIES_HP_ELOG_RESOURCE_MEM:
		rc = dlpar_memory(hp_elog);
		अवरोध;
	हाल PSERIES_HP_ELOG_RESOURCE_CPU:
		rc = dlpar_cpu(hp_elog);
		अवरोध;
	हाल PSERIES_HP_ELOG_RESOURCE_PMEM:
		rc = dlpar_hp_pmem(hp_elog);
		अवरोध;

	शेष:
		pr_warn_ratelimited("Invalid resource (%d) specified\n",
				    hp_elog->resource);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम pseries_hp_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pseries_hp_work *hp_work =
			container_of(work, काष्ठा pseries_hp_work, work);

	handle_dlpar_errorlog(hp_work->errlog);

	kमुक्त(hp_work->errlog);
	kमुक्त((व्योम *)work);
पूर्ण

व्योम queue_hotplug_event(काष्ठा pseries_hp_errorlog *hp_errlog)
अणु
	काष्ठा pseries_hp_work *work;
	काष्ठा pseries_hp_errorlog *hp_errlog_copy;

	hp_errlog_copy = kmemdup(hp_errlog, माप(*hp_errlog), GFP_ATOMIC);
	अगर (!hp_errlog_copy)
		वापस;

	work = kदो_स्मृति(माप(काष्ठा pseries_hp_work), GFP_ATOMIC);
	अगर (work) अणु
		INIT_WORK((काष्ठा work_काष्ठा *)work, pseries_hp_work_fn);
		work->errlog = hp_errlog_copy;
		queue_work(pseries_hp_wq, (काष्ठा work_काष्ठा *)work);
	पूर्ण अन्यथा अणु
		kमुक्त(hp_errlog_copy);
	पूर्ण
पूर्ण

अटल पूर्णांक dlpar_parse_resource(अक्षर **cmd, काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	अक्षर *arg;

	arg = strsep(cmd, " ");
	अगर (!arg)
		वापस -EINVAL;

	अगर (sysfs_streq(arg, "memory")) अणु
		hp_elog->resource = PSERIES_HP_ELOG_RESOURCE_MEM;
	पूर्ण अन्यथा अगर (sysfs_streq(arg, "cpu")) अणु
		hp_elog->resource = PSERIES_HP_ELOG_RESOURCE_CPU;
	पूर्ण अन्यथा अणु
		pr_err("Invalid resource specified.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dlpar_parse_action(अक्षर **cmd, काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	अक्षर *arg;

	arg = strsep(cmd, " ");
	अगर (!arg)
		वापस -EINVAL;

	अगर (sysfs_streq(arg, "add")) अणु
		hp_elog->action = PSERIES_HP_ELOG_ACTION_ADD;
	पूर्ण अन्यथा अगर (sysfs_streq(arg, "remove")) अणु
		hp_elog->action = PSERIES_HP_ELOG_ACTION_REMOVE;
	पूर्ण अन्यथा अणु
		pr_err("Invalid action specified.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dlpar_parse_id_type(अक्षर **cmd, काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	अक्षर *arg;
	u32 count, index;

	arg = strsep(cmd, " ");
	अगर (!arg)
		वापस -EINVAL;

	अगर (sysfs_streq(arg, "indexed-count")) अणु
		hp_elog->id_type = PSERIES_HP_ELOG_ID_DRC_IC;
		arg = strsep(cmd, " ");
		अगर (!arg) अणु
			pr_err("No DRC count specified.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (kstrtou32(arg, 0, &count)) अणु
			pr_err("Invalid DRC count specified.\n");
			वापस -EINVAL;
		पूर्ण

		arg = strsep(cmd, " ");
		अगर (!arg) अणु
			pr_err("No DRC Index specified.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (kstrtou32(arg, 0, &index)) अणु
			pr_err("Invalid DRC Index specified.\n");
			वापस -EINVAL;
		पूर्ण

		hp_elog->_drc_u.ic.count = cpu_to_be32(count);
		hp_elog->_drc_u.ic.index = cpu_to_be32(index);
	पूर्ण अन्यथा अगर (sysfs_streq(arg, "index")) अणु
		hp_elog->id_type = PSERIES_HP_ELOG_ID_DRC_INDEX;
		arg = strsep(cmd, " ");
		अगर (!arg) अणु
			pr_err("No DRC Index specified.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (kstrtou32(arg, 0, &index)) अणु
			pr_err("Invalid DRC Index specified.\n");
			वापस -EINVAL;
		पूर्ण

		hp_elog->_drc_u.drc_index = cpu_to_be32(index);
	पूर्ण अन्यथा अगर (sysfs_streq(arg, "count")) अणु
		hp_elog->id_type = PSERIES_HP_ELOG_ID_DRC_COUNT;
		arg = strsep(cmd, " ");
		अगर (!arg) अणु
			pr_err("No DRC count specified.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (kstrtou32(arg, 0, &count)) अणु
			pr_err("Invalid DRC count specified.\n");
			वापस -EINVAL;
		पूर्ण

		hp_elog->_drc_u.drc_count = cpu_to_be32(count);
	पूर्ण अन्यथा अणु
		pr_err("Invalid id_type specified.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dlpar_store(काष्ठा class *class, काष्ठा class_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pseries_hp_errorlog hp_elog;
	अक्षर *argbuf;
	अक्षर *args;
	पूर्णांक rc;

	args = argbuf = kstrdup(buf, GFP_KERNEL);
	अगर (!argbuf)
		वापस -ENOMEM;

	/*
	 * Parse out the request from the user, this will be in the क्रमm:
	 * <resource> <action> <id_type> <id>
	 */
	rc = dlpar_parse_resource(&args, &hp_elog);
	अगर (rc)
		जाओ dlpar_store_out;

	rc = dlpar_parse_action(&args, &hp_elog);
	अगर (rc)
		जाओ dlpar_store_out;

	rc = dlpar_parse_id_type(&args, &hp_elog);
	अगर (rc)
		जाओ dlpar_store_out;

	rc = handle_dlpar_errorlog(&hp_elog);

dlpar_store_out:
	kमुक्त(argbuf);

	अगर (rc)
		pr_err("Could not handle DLPAR request \"%s\"\n", buf);

	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार dlpar_show(काष्ठा class *class, काष्ठा class_attribute *attr,
			  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", "memory,cpu");
पूर्ण

अटल CLASS_ATTR_RW(dlpar);

पूर्णांक __init dlpar_workqueue_init(व्योम)
अणु
	अगर (pseries_hp_wq)
		वापस 0;

	pseries_hp_wq = alloc_workqueue("pseries hotplug workqueue",
			WQ_UNBOUND, 1);

	वापस pseries_hp_wq ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक __init dlpar_sysfs_init(व्योम)
अणु
	पूर्णांक rc;

	rc = dlpar_workqueue_init();
	अगर (rc)
		वापस rc;

	वापस sysfs_create_file(kernel_kobj, &class_attr_dlpar.attr);
पूर्ण
machine_device_initcall(pseries, dlpar_sysfs_init);

