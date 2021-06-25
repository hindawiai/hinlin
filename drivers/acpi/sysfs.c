<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sysfs.c - ACPI sysfs पूर्णांकerface to userspace.
 */

#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/acpi.h>

#समावेश "internal.h"

#अगर_घोषित CONFIG_ACPI_DEBUG
/*
 * ACPI debug sysfs I/F, including:
 * /sys/modules/acpi/parameters/debug_layer
 * /sys/modules/acpi/parameters/debug_level
 * /sys/modules/acpi/parameters/trace_method_name
 * /sys/modules/acpi/parameters/trace_state
 * /sys/modules/acpi/parameters/trace_debug_layer
 * /sys/modules/acpi/parameters/trace_debug_level
 */

काष्ठा acpi_dlayer अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ value;
पूर्ण;
काष्ठा acpi_dlevel अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ value;
पूर्ण;
#घोषणा ACPI_DEBUG_INIT(v)	अणु .name = #v, .value = v पूर्ण

अटल स्थिर काष्ठा acpi_dlayer acpi_debug_layers[] = अणु
	ACPI_DEBUG_INIT(ACPI_UTILITIES),
	ACPI_DEBUG_INIT(ACPI_HARDWARE),
	ACPI_DEBUG_INIT(ACPI_EVENTS),
	ACPI_DEBUG_INIT(ACPI_TABLES),
	ACPI_DEBUG_INIT(ACPI_NAMESPACE),
	ACPI_DEBUG_INIT(ACPI_PARSER),
	ACPI_DEBUG_INIT(ACPI_DISPATCHER),
	ACPI_DEBUG_INIT(ACPI_EXECUTER),
	ACPI_DEBUG_INIT(ACPI_RESOURCES),
	ACPI_DEBUG_INIT(ACPI_CA_DEBUGGER),
	ACPI_DEBUG_INIT(ACPI_OS_SERVICES),
	ACPI_DEBUG_INIT(ACPI_CA_DISASSEMBLER),
	ACPI_DEBUG_INIT(ACPI_COMPILER),
	ACPI_DEBUG_INIT(ACPI_TOOLS),
पूर्ण;

अटल स्थिर काष्ठा acpi_dlevel acpi_debug_levels[] = अणु
	ACPI_DEBUG_INIT(ACPI_LV_INIT),
	ACPI_DEBUG_INIT(ACPI_LV_DEBUG_OBJECT),
	ACPI_DEBUG_INIT(ACPI_LV_INFO),
	ACPI_DEBUG_INIT(ACPI_LV_REPAIR),
	ACPI_DEBUG_INIT(ACPI_LV_TRACE_POINT),

	ACPI_DEBUG_INIT(ACPI_LV_INIT_NAMES),
	ACPI_DEBUG_INIT(ACPI_LV_PARSE),
	ACPI_DEBUG_INIT(ACPI_LV_LOAD),
	ACPI_DEBUG_INIT(ACPI_LV_DISPATCH),
	ACPI_DEBUG_INIT(ACPI_LV_EXEC),
	ACPI_DEBUG_INIT(ACPI_LV_NAMES),
	ACPI_DEBUG_INIT(ACPI_LV_OPREGION),
	ACPI_DEBUG_INIT(ACPI_LV_BFIELD),
	ACPI_DEBUG_INIT(ACPI_LV_TABLES),
	ACPI_DEBUG_INIT(ACPI_LV_VALUES),
	ACPI_DEBUG_INIT(ACPI_LV_OBJECTS),
	ACPI_DEBUG_INIT(ACPI_LV_RESOURCES),
	ACPI_DEBUG_INIT(ACPI_LV_USER_REQUESTS),
	ACPI_DEBUG_INIT(ACPI_LV_PACKAGE),

	ACPI_DEBUG_INIT(ACPI_LV_ALLOCATIONS),
	ACPI_DEBUG_INIT(ACPI_LV_FUNCTIONS),
	ACPI_DEBUG_INIT(ACPI_LV_OPTIMIZATIONS),

	ACPI_DEBUG_INIT(ACPI_LV_MUTEX),
	ACPI_DEBUG_INIT(ACPI_LV_THREADS),
	ACPI_DEBUG_INIT(ACPI_LV_IO),
	ACPI_DEBUG_INIT(ACPI_LV_INTERRUPTS),

	ACPI_DEBUG_INIT(ACPI_LV_AML_DISASSEMBLE),
	ACPI_DEBUG_INIT(ACPI_LV_VERBOSE_INFO),
	ACPI_DEBUG_INIT(ACPI_LV_FULL_TABLES),
	ACPI_DEBUG_INIT(ACPI_LV_EVENTS),
पूर्ण;

अटल पूर्णांक param_get_debug_layer(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;

	result = प्र_लिखो(buffer, "%-25s\tHex        SET\n", "Description");

	क्रम (i = 0; i < ARRAY_SIZE(acpi_debug_layers); i++) अणु
		result += प्र_लिखो(buffer + result, "%-25s\t0x%08lX [%c]\n",
				  acpi_debug_layers[i].name,
				  acpi_debug_layers[i].value,
				  (acpi_dbg_layer & acpi_debug_layers[i].value)
				  ? '*' : ' ');
	पूर्ण
	result +=
	    प्र_लिखो(buffer + result, "%-25s\t0x%08X [%c]\n", "ACPI_ALL_DRIVERS",
		    ACPI_ALL_DRIVERS,
		    (acpi_dbg_layer & ACPI_ALL_DRIVERS) ==
		    ACPI_ALL_DRIVERS ? '*' : (acpi_dbg_layer & ACPI_ALL_DRIVERS)
		    == 0 ? ' ' : '-');
	result +=
	    प्र_लिखो(buffer + result,
		    "--\ndebug_layer = 0x%08X ( * = enabled)\n",
		    acpi_dbg_layer);

	वापस result;
पूर्ण

अटल पूर्णांक param_get_debug_level(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;

	result = प्र_लिखो(buffer, "%-25s\tHex        SET\n", "Description");

	क्रम (i = 0; i < ARRAY_SIZE(acpi_debug_levels); i++) अणु
		result += प्र_लिखो(buffer + result, "%-25s\t0x%08lX [%c]\n",
				  acpi_debug_levels[i].name,
				  acpi_debug_levels[i].value,
				  (acpi_dbg_level & acpi_debug_levels[i].value)
				  ? '*' : ' ');
	पूर्ण
	result +=
	    प्र_लिखो(buffer + result, "--\ndebug_level = 0x%08X (* = enabled)\n",
		    acpi_dbg_level);

	वापस result;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_debug_layer = अणु
	.set = param_set_uपूर्णांक,
	.get = param_get_debug_layer,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_debug_level = अणु
	.set = param_set_uपूर्णांक,
	.get = param_get_debug_level,
पूर्ण;

module_param_cb(debug_layer, &param_ops_debug_layer, &acpi_dbg_layer, 0644);
module_param_cb(debug_level, &param_ops_debug_level, &acpi_dbg_level, 0644);

अटल अक्षर trace_method_name[1024];

अटल पूर्णांक param_set_trace_method_name(स्थिर अक्षर *val,
				       स्थिर काष्ठा kernel_param *kp)
अणु
	u32 saved_flags = 0;
	bool is_असल_path = true;

	अगर (*val != '\\')
		is_असल_path = false;

	अगर ((is_असल_path && म_माप(val) > 1023) ||
	    (!is_असल_path && म_माप(val) > 1022)) अणु
		pr_err("%s: string parameter too long\n", kp->name);
		वापस -ENOSPC;
	पूर्ण

	/*
	 * It's not safe to update acpi_gbl_trace_method_name without
	 * having the tracer stopped, so we save the original tracer
	 * state and disable it.
	 */
	saved_flags = acpi_gbl_trace_flags;
	(व्योम)acpi_debug_trace(शून्य,
			       acpi_gbl_trace_dbg_level,
			       acpi_gbl_trace_dbg_layer,
			       0);

	/* This is a hack.  We can't kदो_स्मृति in early boot. */
	अगर (is_असल_path)
		म_नकल(trace_method_name, val);
	अन्यथा अणु
		trace_method_name[0] = '\\';
		म_नकल(trace_method_name+1, val);
	पूर्ण

	/* Restore the original tracer state */
	(व्योम)acpi_debug_trace(trace_method_name,
			       acpi_gbl_trace_dbg_level,
			       acpi_gbl_trace_dbg_layer,
			       saved_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक param_get_trace_method_name(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", acpi_gbl_trace_method_name);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_trace_method = अणु
	.set = param_set_trace_method_name,
	.get = param_get_trace_method_name,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_trace_attrib = अणु
	.set = param_set_uपूर्णांक,
	.get = param_get_uपूर्णांक,
पूर्ण;

module_param_cb(trace_method_name, &param_ops_trace_method, &trace_method_name, 0644);
module_param_cb(trace_debug_layer, &param_ops_trace_attrib, &acpi_gbl_trace_dbg_layer, 0644);
module_param_cb(trace_debug_level, &param_ops_trace_attrib, &acpi_gbl_trace_dbg_level, 0644);

अटल पूर्णांक param_set_trace_state(स्थिर अक्षर *val,
				 स्थिर काष्ठा kernel_param *kp)
अणु
	acpi_status status;
	स्थिर अक्षर *method = trace_method_name;
	u32 flags = 0;

/* So "xxx-once" comparison should go prior than "xxx" comparison */
#घोषणा acpi_compare_param(val, key)	\
	म_भेदन((val), (key), माप(key) - 1)

	अगर (!acpi_compare_param(val, "enable")) अणु
		method = शून्य;
		flags = ACPI_TRACE_ENABLED;
	पूर्ण अन्यथा अगर (!acpi_compare_param(val, "disable"))
		method = शून्य;
	अन्यथा अगर (!acpi_compare_param(val, "method-once"))
		flags = ACPI_TRACE_ENABLED | ACPI_TRACE_ONESHOT;
	अन्यथा अगर (!acpi_compare_param(val, "method"))
		flags = ACPI_TRACE_ENABLED;
	अन्यथा अगर (!acpi_compare_param(val, "opcode-once"))
		flags = ACPI_TRACE_ENABLED | ACPI_TRACE_ONESHOT | ACPI_TRACE_OPCODE;
	अन्यथा अगर (!acpi_compare_param(val, "opcode"))
		flags = ACPI_TRACE_ENABLED | ACPI_TRACE_OPCODE;
	अन्यथा
		वापस -EINVAL;

	status = acpi_debug_trace(method,
				  acpi_gbl_trace_dbg_level,
				  acpi_gbl_trace_dbg_layer,
				  flags);
	अगर (ACPI_FAILURE(status))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक param_get_trace_state(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!(acpi_gbl_trace_flags & ACPI_TRACE_ENABLED))
		वापस प्र_लिखो(buffer, "disable\n");
	अन्यथा अणु
		अगर (acpi_gbl_trace_method_name) अणु
			अगर (acpi_gbl_trace_flags & ACPI_TRACE_ONESHOT)
				वापस प्र_लिखो(buffer, "method-once\n");
			अन्यथा
				वापस प्र_लिखो(buffer, "method\n");
		पूर्ण अन्यथा
			वापस प्र_लिखो(buffer, "enable\n");
	पूर्ण
	वापस 0;
पूर्ण

module_param_call(trace_state, param_set_trace_state, param_get_trace_state,
		  शून्य, 0644);
#पूर्ण_अगर /* CONFIG_ACPI_DEBUG */


/* /sys/modules/acpi/parameters/aml_debug_output */

module_param_named(aml_debug_output, acpi_gbl_enable_aml_debug_object,
		   byte, 0644);
MODULE_PARM_DESC(aml_debug_output,
		 "To enable/disable the ACPI Debug Object output.");

/* /sys/module/acpi/parameters/acpica_version */
अटल पूर्णांक param_get_acpica_version(अक्षर *buffer,
				    स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक result;

	result = प्र_लिखो(buffer, "%x\n", ACPI_CA_VERSION);

	वापस result;
पूर्ण

module_param_call(acpica_version, शून्य, param_get_acpica_version, शून्य, 0444);

/*
 * ACPI table sysfs I/F:
 * /sys/firmware/acpi/tables/
 * /sys/firmware/acpi/tables/data/
 * /sys/firmware/acpi/tables/dynamic/
 */

अटल LIST_HEAD(acpi_table_attr_list);
अटल काष्ठा kobject *tables_kobj;
अटल काष्ठा kobject *tables_data_kobj;
अटल काष्ठा kobject *dynamic_tables_kobj;
अटल काष्ठा kobject *hotplug_kobj;

#घोषणा ACPI_MAX_TABLE_INSTANCES	999
#घोषणा ACPI_INST_SIZE			4 /* including trailing 0 */

काष्ठा acpi_table_attr अणु
	काष्ठा bin_attribute attr;
	अक्षर name[ACPI_NAMESEG_SIZE];
	पूर्णांक instance;
	अक्षर filename[ACPI_NAMESEG_SIZE+ACPI_INST_SIZE];
	काष्ठा list_head node;
पूर्ण;

काष्ठा acpi_data_attr अणु
	काष्ठा bin_attribute attr;
	u64	addr;
पूर्ण;

अटल sमाप_प्रकार acpi_table_show(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			       loff_t offset, माप_प्रकार count)
अणु
	काष्ठा acpi_table_attr *table_attr =
	    container_of(bin_attr, काष्ठा acpi_table_attr, attr);
	काष्ठा acpi_table_header *table_header = शून्य;
	acpi_status status;
	sमाप_प्रकार rc;

	status = acpi_get_table(table_attr->name, table_attr->instance,
				&table_header);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	rc = memory_पढ़ो_from_buffer(buf, count, &offset, table_header,
			table_header->length);
	acpi_put_table(table_header);
	वापस rc;
पूर्ण

अटल पूर्णांक acpi_table_attr_init(काष्ठा kobject *tables_obj,
				काष्ठा acpi_table_attr *table_attr,
				काष्ठा acpi_table_header *table_header)
अणु
	काष्ठा acpi_table_header *header = शून्य;
	काष्ठा acpi_table_attr *attr = शून्य;
	अक्षर instance_str[ACPI_INST_SIZE];

	sysfs_attr_init(&table_attr->attr.attr);
	ACPI_COPY_NAMESEG(table_attr->name, table_header->signature);

	list_क्रम_each_entry(attr, &acpi_table_attr_list, node) अणु
		अगर (ACPI_COMPARE_NAMESEG(table_attr->name, attr->name))
			अगर (table_attr->instance < attr->instance)
				table_attr->instance = attr->instance;
	पूर्ण
	table_attr->instance++;
	अगर (table_attr->instance > ACPI_MAX_TABLE_INSTANCES) अणु
		pr_warn("%4.4s: too many table instances\n",
			table_attr->name);
		वापस -दुस्फल;
	पूर्ण

	ACPI_COPY_NAMESEG(table_attr->filename, table_header->signature);
	table_attr->filename[ACPI_NAMESEG_SIZE] = '\0';
	अगर (table_attr->instance > 1 || (table_attr->instance == 1 &&
					 !acpi_get_table
					 (table_header->signature, 2, &header))) अणु
		snम_लिखो(instance_str, माप(instance_str), "%u",
			 table_attr->instance);
		म_जोड़ो(table_attr->filename, instance_str);
	पूर्ण

	table_attr->attr.size = table_header->length;
	table_attr->attr.पढ़ो = acpi_table_show;
	table_attr->attr.attr.name = table_attr->filename;
	table_attr->attr.attr.mode = 0400;

	वापस sysfs_create_bin_file(tables_obj, &table_attr->attr);
पूर्ण

acpi_status acpi_sysfs_table_handler(u32 event, व्योम *table, व्योम *context)
अणु
	काष्ठा acpi_table_attr *table_attr;

	चयन (event) अणु
	हाल ACPI_TABLE_EVENT_INSTALL:
		table_attr =
		    kzalloc(माप(काष्ठा acpi_table_attr), GFP_KERNEL);
		अगर (!table_attr)
			वापस AE_NO_MEMORY;

		अगर (acpi_table_attr_init(dynamic_tables_kobj,
					 table_attr, table)) अणु
			kमुक्त(table_attr);
			वापस AE_ERROR;
		पूर्ण
		list_add_tail(&table_attr->node, &acpi_table_attr_list);
		अवरोध;
	हाल ACPI_TABLE_EVENT_LOAD:
	हाल ACPI_TABLE_EVENT_UNLOAD:
	हाल ACPI_TABLE_EVENT_UNINSTALL:
		/*
		 * we करो not need to करो anything right now
		 * because the table is not deleted from the
		 * global table list when unloading it.
		 */
		अवरोध;
	शेष:
		वापस AE_BAD_PARAMETER;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल sमाप_प्रकार acpi_data_show(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			      loff_t offset, माप_प्रकार count)
अणु
	काष्ठा acpi_data_attr *data_attr;
	व्योम __iomem *base;
	sमाप_प्रकार rc;

	data_attr = container_of(bin_attr, काष्ठा acpi_data_attr, attr);

	base = acpi_os_map_memory(data_attr->addr, data_attr->attr.size);
	अगर (!base)
		वापस -ENOMEM;
	rc = memory_पढ़ो_from_buffer(buf, count, &offset, base,
				     data_attr->attr.size);
	acpi_os_unmap_memory(base, data_attr->attr.size);

	वापस rc;
पूर्ण

अटल पूर्णांक acpi_bert_data_init(व्योम *th, काष्ठा acpi_data_attr *data_attr)
अणु
	काष्ठा acpi_table_bert *bert = th;

	अगर (bert->header.length < माप(काष्ठा acpi_table_bert) ||
	    bert->region_length < माप(काष्ठा acpi_hest_generic_status)) अणु
		kमुक्त(data_attr);
		वापस -EINVAL;
	पूर्ण
	data_attr->addr = bert->address;
	data_attr->attr.size = bert->region_length;
	data_attr->attr.attr.name = "BERT";

	वापस sysfs_create_bin_file(tables_data_kobj, &data_attr->attr);
पूर्ण

अटल काष्ठा acpi_data_obj अणु
	अक्षर *name;
	पूर्णांक (*fn)(व्योम *, काष्ठा acpi_data_attr *);
पूर्ण acpi_data_objs[] = अणु
	अणु ACPI_SIG_BERT, acpi_bert_data_init पूर्ण,
पूर्ण;

#घोषणा NUM_ACPI_DATA_OBJS ARRAY_SIZE(acpi_data_objs)

अटल पूर्णांक acpi_table_data_init(काष्ठा acpi_table_header *th)
अणु
	काष्ठा acpi_data_attr *data_attr;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ACPI_DATA_OBJS; i++) अणु
		अगर (ACPI_COMPARE_NAMESEG(th->signature, acpi_data_objs[i].name)) अणु
			data_attr = kzalloc(माप(*data_attr), GFP_KERNEL);
			अगर (!data_attr)
				वापस -ENOMEM;
			sysfs_attr_init(&data_attr->attr.attr);
			data_attr->attr.पढ़ो = acpi_data_show;
			data_attr->attr.attr.mode = 0400;
			वापस acpi_data_objs[i].fn(th, data_attr);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_tables_sysfs_init(व्योम)
अणु
	काष्ठा acpi_table_attr *table_attr;
	काष्ठा acpi_table_header *table_header = शून्य;
	पूर्णांक table_index;
	acpi_status status;
	पूर्णांक ret;

	tables_kobj = kobject_create_and_add("tables", acpi_kobj);
	अगर (!tables_kobj)
		जाओ err;

	tables_data_kobj = kobject_create_and_add("data", tables_kobj);
	अगर (!tables_data_kobj)
		जाओ err_tables_data;

	dynamic_tables_kobj = kobject_create_and_add("dynamic", tables_kobj);
	अगर (!dynamic_tables_kobj)
		जाओ err_dynamic_tables;

	क्रम (table_index = 0;; table_index++) अणु
		status = acpi_get_table_by_index(table_index, &table_header);

		अगर (status == AE_BAD_PARAMETER)
			अवरोध;

		अगर (ACPI_FAILURE(status))
			जारी;

		table_attr = kzalloc(माप(*table_attr), GFP_KERNEL);
		अगर (!table_attr)
			वापस -ENOMEM;

		ret = acpi_table_attr_init(tables_kobj,
					   table_attr, table_header);
		अगर (ret) अणु
			kमुक्त(table_attr);
			वापस ret;
		पूर्ण
		list_add_tail(&table_attr->node, &acpi_table_attr_list);
		acpi_table_data_init(table_header);
	पूर्ण

	kobject_uevent(tables_kobj, KOBJ_ADD);
	kobject_uevent(tables_data_kobj, KOBJ_ADD);
	kobject_uevent(dynamic_tables_kobj, KOBJ_ADD);

	वापस 0;
err_dynamic_tables:
	kobject_put(tables_data_kobj);
err_tables_data:
	kobject_put(tables_kobj);
err:
	वापस -ENOMEM;
पूर्ण

/*
 * Detailed ACPI IRQ counters:
 * /sys/firmware/acpi/पूर्णांकerrupts/
 */

u32 acpi_irq_handled;
u32 acpi_irq_not_handled;

#घोषणा COUNT_GPE 0
#घोषणा COUNT_SCI 1		/* acpi_irq_handled */
#घोषणा COUNT_SCI_NOT 2		/* acpi_irq_not_handled */
#घोषणा COUNT_ERROR 3		/* other */
#घोषणा NUM_COUNTERS_EXTRA 4

काष्ठा event_counter अणु
	u32 count;
	u32 flags;
पूर्ण;

अटल काष्ठा event_counter *all_counters;
अटल u32 num_gpes;
अटल u32 num_counters;
अटल काष्ठा attribute **all_attrs;
अटल u32 acpi_gpe_count;

अटल काष्ठा attribute_group पूर्णांकerrupt_stats_attr_group = अणु
	.name = "interrupts",
पूर्ण;

अटल काष्ठा kobj_attribute *counter_attrs;

अटल व्योम delete_gpe_attr_array(व्योम)
अणु
	काष्ठा event_counter *पंचांगp = all_counters;

	all_counters = शून्य;
	kमुक्त(पंचांगp);

	अगर (counter_attrs) अणु
		पूर्णांक i;

		क्रम (i = 0; i < num_gpes; i++)
			kमुक्त(counter_attrs[i].attr.name);

		kमुक्त(counter_attrs);
	पूर्ण
	kमुक्त(all_attrs);

	वापस;
पूर्ण

अटल व्योम gpe_count(u32 gpe_number)
अणु
	acpi_gpe_count++;

	अगर (!all_counters)
		वापस;

	अगर (gpe_number < num_gpes)
		all_counters[gpe_number].count++;
	अन्यथा
		all_counters[num_gpes + ACPI_NUM_FIXED_EVENTS +
			     COUNT_ERROR].count++;

	वापस;
पूर्ण

अटल व्योम fixed_event_count(u32 event_number)
अणु
	अगर (!all_counters)
		वापस;

	अगर (event_number < ACPI_NUM_FIXED_EVENTS)
		all_counters[num_gpes + event_number].count++;
	अन्यथा
		all_counters[num_gpes + ACPI_NUM_FIXED_EVENTS +
			     COUNT_ERROR].count++;

	वापस;
पूर्ण

अटल व्योम acpi_global_event_handler(u32 event_type, acpi_handle device,
	u32 event_number, व्योम *context)
अणु
	अगर (event_type == ACPI_EVENT_TYPE_GPE) अणु
		gpe_count(event_number);
		pr_debug("GPE event 0x%02x\n", event_number);
	पूर्ण अन्यथा अगर (event_type == ACPI_EVENT_TYPE_FIXED) अणु
		fixed_event_count(event_number);
		pr_debug("Fixed event 0x%02x\n", event_number);
	पूर्ण अन्यथा अणु
		pr_debug("Other event 0x%02x\n", event_number);
	पूर्ण
पूर्ण

अटल पूर्णांक get_status(u32 index, acpi_event_status *ret,
		      acpi_handle *handle)
अणु
	acpi_status status;

	अगर (index >= num_gpes + ACPI_NUM_FIXED_EVENTS)
		वापस -EINVAL;

	अगर (index < num_gpes) अणु
		status = acpi_get_gpe_device(index, handle);
		अगर (ACPI_FAILURE(status)) अणु
			pr_warn("Invalid GPE 0x%x", index);
			वापस -ENXIO;
		पूर्ण
		status = acpi_get_gpe_status(*handle, index, ret);
	पूर्ण अन्यथा अणु
		status = acpi_get_event_status(index - num_gpes, ret);
	पूर्ण
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार counter_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index = attr - counter_attrs;
	पूर्णांक size;
	acpi_handle handle;
	acpi_event_status status;
	पूर्णांक result = 0;

	all_counters[num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI].count =
	    acpi_irq_handled;
	all_counters[num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI_NOT].count =
	    acpi_irq_not_handled;
	all_counters[num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_GPE].count =
	    acpi_gpe_count;
	size = प्र_लिखो(buf, "%8u", all_counters[index].count);

	/* "gpe_all" or "sci" */
	अगर (index >= num_gpes + ACPI_NUM_FIXED_EVENTS)
		जाओ end;

	result = get_status(index, &status, &handle);
	अगर (result)
		जाओ end;

	अगर (status & ACPI_EVENT_FLAG_ENABLE_SET)
		size += प्र_लिखो(buf + size, "  EN");
	अन्यथा
		size += प्र_लिखो(buf + size, "    ");
	अगर (status & ACPI_EVENT_FLAG_STATUS_SET)
		size += प्र_लिखो(buf + size, " STS");
	अन्यथा
		size += प्र_लिखो(buf + size, "    ");

	अगर (!(status & ACPI_EVENT_FLAG_HAS_HANDLER))
		size += प्र_लिखो(buf + size, " invalid     ");
	अन्यथा अगर (status & ACPI_EVENT_FLAG_ENABLED)
		size += प्र_लिखो(buf + size, " enabled     ");
	अन्यथा अगर (status & ACPI_EVENT_FLAG_WAKE_ENABLED)
		size += प्र_लिखो(buf + size, " wake_enabled");
	अन्यथा
		size += प्र_लिखो(buf + size, " disabled    ");
	अगर (status & ACPI_EVENT_FLAG_MASKED)
		size += प्र_लिखो(buf + size, " masked  ");
	अन्यथा
		size += प्र_लिखो(buf + size, " unmasked");

end:
	size += प्र_लिखो(buf + size, "\n");
	वापस result ? result : size;
पूर्ण

/*
 * counter_set() sets the specअगरied counter.
 * setting the total "sci" file to any value clears all counters.
 * enable/disable/clear a gpe/fixed event in user space.
 */
अटल sमाप_प्रकार counter_set(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf,
			   माप_प्रकार size)
अणु
	पूर्णांक index = attr - counter_attrs;
	acpi_event_status status;
	acpi_handle handle;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ पंचांगp;

	अगर (index == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI) अणु
		पूर्णांक i;
		क्रम (i = 0; i < num_counters; ++i)
			all_counters[i].count = 0;
		acpi_gpe_count = 0;
		acpi_irq_handled = 0;
		acpi_irq_not_handled = 0;
		जाओ end;
	पूर्ण

	/* show the event status क्रम both GPEs and Fixed Events */
	result = get_status(index, &status, &handle);
	अगर (result)
		जाओ end;

	अगर (!(status & ACPI_EVENT_FLAG_HAS_HANDLER)) अणु
		prपूर्णांकk(KERN_WARNING PREFIX
		       "Can not change Invalid GPE/Fixed Event status\n");
		वापस -EINVAL;
	पूर्ण

	अगर (index < num_gpes) अणु
		अगर (!म_भेद(buf, "disable\n") &&
		    (status & ACPI_EVENT_FLAG_ENABLED))
			result = acpi_disable_gpe(handle, index);
		अन्यथा अगर (!म_भेद(buf, "enable\n") &&
			 !(status & ACPI_EVENT_FLAG_ENABLED))
			result = acpi_enable_gpe(handle, index);
		अन्यथा अगर (!म_भेद(buf, "clear\n") &&
			 (status & ACPI_EVENT_FLAG_STATUS_SET))
			result = acpi_clear_gpe(handle, index);
		अन्यथा अगर (!म_भेद(buf, "mask\n"))
			result = acpi_mask_gpe(handle, index, TRUE);
		अन्यथा अगर (!म_भेद(buf, "unmask\n"))
			result = acpi_mask_gpe(handle, index, FALSE);
		अन्यथा अगर (!kम_से_अदीर्घ(buf, 0, &पंचांगp))
			all_counters[index].count = पंचांगp;
		अन्यथा
			result = -EINVAL;
	पूर्ण अन्यथा अगर (index < num_gpes + ACPI_NUM_FIXED_EVENTS) अणु
		पूर्णांक event = index - num_gpes;
		अगर (!म_भेद(buf, "disable\n") &&
		    (status & ACPI_EVENT_FLAG_ENABLE_SET))
			result = acpi_disable_event(event, ACPI_NOT_ISR);
		अन्यथा अगर (!म_भेद(buf, "enable\n") &&
			 !(status & ACPI_EVENT_FLAG_ENABLE_SET))
			result = acpi_enable_event(event, ACPI_NOT_ISR);
		अन्यथा अगर (!म_भेद(buf, "clear\n") &&
			 (status & ACPI_EVENT_FLAG_STATUS_SET))
			result = acpi_clear_event(event);
		अन्यथा अगर (!kम_से_अदीर्घ(buf, 0, &पंचांगp))
			all_counters[index].count = पंचांगp;
		अन्यथा
			result = -EINVAL;
	पूर्ण अन्यथा
		all_counters[index].count = म_से_अदीर्घ(buf, शून्य, 0);

	अगर (ACPI_FAILURE(result))
		result = -EINVAL;
end:
	वापस result ? result : size;
पूर्ण

/*
 * A Quirk Mechanism क्रम GPE Flooding Prevention:
 *
 * Quirks may be needed to prevent GPE flooding on a specअगरic GPE. The
 * flooding typically cannot be detected and स्वतःmatically prevented by
 * ACPI_GPE_DISPATCH_NONE check because there is a _Lxx/_Exx prepared in
 * the AML tables. This normally indicates a feature gap in Linux, thus
 * instead of providing endless quirk tables, we provide a boot parameter
 * क्रम those who want this quirk. For example, अगर the users want to prevent
 * the GPE flooding क्रम GPE 00, they need to specअगरy the following boot
 * parameter:
 *   acpi_mask_gpe=0x00
 * The masking status can be modअगरied by the following runसमय controlling
 * पूर्णांकerface:
 *   echo unmask > /sys/firmware/acpi/पूर्णांकerrupts/gpe00
 */
#घोषणा ACPI_MASKABLE_GPE_MAX	0x100
अटल DECLARE_BITMAP(acpi_masked_gpes_map, ACPI_MASKABLE_GPE_MAX) __initdata;

अटल पूर्णांक __init acpi_gpe_set_masked_gpes(अक्षर *val)
अणु
	u8 gpe;

	अगर (kstrtou8(val, 0, &gpe))
		वापस -EINVAL;
	set_bit(gpe, acpi_masked_gpes_map);

	वापस 1;
पूर्ण
__setup("acpi_mask_gpe=", acpi_gpe_set_masked_gpes);

व्योम __init acpi_gpe_apply_masked_gpes(व्योम)
अणु
	acpi_handle handle;
	acpi_status status;
	u16 gpe;

	क्रम_each_set_bit(gpe, acpi_masked_gpes_map, ACPI_MASKABLE_GPE_MAX) अणु
		status = acpi_get_gpe_device(gpe, &handle);
		अगर (ACPI_SUCCESS(status)) अणु
			pr_info("Masking GPE 0x%x.\n", gpe);
			(व्योम)acpi_mask_gpe(handle, gpe, TRUE);
		पूर्ण
	पूर्ण
पूर्ण

व्योम acpi_irq_stats_init(व्योम)
अणु
	acpi_status status;
	पूर्णांक i;

	अगर (all_counters)
		वापस;

	num_gpes = acpi_current_gpe_count;
	num_counters = num_gpes + ACPI_NUM_FIXED_EVENTS + NUM_COUNTERS_EXTRA;

	all_attrs = kसुस्मृति(num_counters + 1, माप(काष्ठा attribute *),
			    GFP_KERNEL);
	अगर (all_attrs == शून्य)
		वापस;

	all_counters = kसुस्मृति(num_counters, माप(काष्ठा event_counter),
			       GFP_KERNEL);
	अगर (all_counters == शून्य)
		जाओ fail;

	status = acpi_install_global_event_handler(acpi_global_event_handler, शून्य);
	अगर (ACPI_FAILURE(status))
		जाओ fail;

	counter_attrs = kसुस्मृति(num_counters, माप(काष्ठा kobj_attribute),
				GFP_KERNEL);
	अगर (counter_attrs == शून्य)
		जाओ fail;

	क्रम (i = 0; i < num_counters; ++i) अणु
		अक्षर buffer[12];
		अक्षर *name;

		अगर (i < num_gpes)
			प्र_लिखो(buffer, "gpe%02X", i);
		अन्यथा अगर (i == num_gpes + ACPI_EVENT_PMTIMER)
			प्र_लिखो(buffer, "ff_pmtimer");
		अन्यथा अगर (i == num_gpes + ACPI_EVENT_GLOBAL)
			प्र_लिखो(buffer, "ff_gbl_lock");
		अन्यथा अगर (i == num_gpes + ACPI_EVENT_POWER_BUTTON)
			प्र_लिखो(buffer, "ff_pwr_btn");
		अन्यथा अगर (i == num_gpes + ACPI_EVENT_SLEEP_BUTTON)
			प्र_लिखो(buffer, "ff_slp_btn");
		अन्यथा अगर (i == num_gpes + ACPI_EVENT_RTC)
			प्र_लिखो(buffer, "ff_rt_clk");
		अन्यथा अगर (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_GPE)
			प्र_लिखो(buffer, "gpe_all");
		अन्यथा अगर (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI)
			प्र_लिखो(buffer, "sci");
		अन्यथा अगर (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI_NOT)
			प्र_लिखो(buffer, "sci_not");
		अन्यथा अगर (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_ERROR)
			प्र_लिखो(buffer, "error");
		अन्यथा
			प्र_लिखो(buffer, "bug%02X", i);

		name = kstrdup(buffer, GFP_KERNEL);
		अगर (name == शून्य)
			जाओ fail;

		sysfs_attr_init(&counter_attrs[i].attr);
		counter_attrs[i].attr.name = name;
		counter_attrs[i].attr.mode = 0644;
		counter_attrs[i].show = counter_show;
		counter_attrs[i].store = counter_set;

		all_attrs[i] = &counter_attrs[i].attr;
	पूर्ण

	पूर्णांकerrupt_stats_attr_group.attrs = all_attrs;
	अगर (!sysfs_create_group(acpi_kobj, &पूर्णांकerrupt_stats_attr_group))
		वापस;

fail:
	delete_gpe_attr_array();
	वापस;
पूर्ण

अटल व्योम __निकास पूर्णांकerrupt_stats_निकास(व्योम)
अणु
	sysfs_हटाओ_group(acpi_kobj, &पूर्णांकerrupt_stats_attr_group);

	delete_gpe_attr_array();

	वापस;
पूर्ण

अटल sमाप_प्रकार
acpi_show_profile(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", acpi_gbl_FADT.preferred_profile);
पूर्ण

अटल स्थिर काष्ठा kobj_attribute pm_profile_attr =
	__ATTR(pm_profile, S_IRUGO, acpi_show_profile, शून्य);

अटल sमाप_प्रकार hotplug_enabled_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_hotplug_profile *hotplug = to_acpi_hotplug_profile(kobj);

	वापस प्र_लिखो(buf, "%d\n", hotplug->enabled);
पूर्ण

अटल sमाप_प्रकार hotplug_enabled_store(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा acpi_hotplug_profile *hotplug = to_acpi_hotplug_profile(kobj);
	अचिन्हित पूर्णांक val;

	अगर (kstrtouपूर्णांक(buf, 10, &val) || val > 1)
		वापस -EINVAL;

	acpi_scan_hotplug_enabled(hotplug, val);
	वापस size;
पूर्ण

अटल काष्ठा kobj_attribute hotplug_enabled_attr =
	__ATTR(enabled, S_IRUGO | S_IWUSR, hotplug_enabled_show,
		hotplug_enabled_store);

अटल काष्ठा attribute *hotplug_profile_attrs[] = अणु
	&hotplug_enabled_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा kobj_type acpi_hotplug_profile_ktype = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.शेष_attrs = hotplug_profile_attrs,
पूर्ण;

व्योम acpi_sysfs_add_hotplug_profile(काष्ठा acpi_hotplug_profile *hotplug,
				    स्थिर अक्षर *name)
अणु
	पूर्णांक error;

	अगर (!hotplug_kobj)
		जाओ err_out;

	error = kobject_init_and_add(&hotplug->kobj,
		&acpi_hotplug_profile_ktype, hotplug_kobj, "%s", name);
	अगर (error) अणु
		kobject_put(&hotplug->kobj);
		जाओ err_out;
	पूर्ण

	kobject_uevent(&hotplug->kobj, KOBJ_ADD);
	वापस;

 err_out:
	pr_err(PREFIX "Unable to add hotplug profile '%s'\n", name);
पूर्ण

अटल sमाप_प्रकार क्रमce_हटाओ_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", 0);
पूर्ण

अटल sमाप_प्रकार क्रमce_हटाओ_store(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	bool val;
	पूर्णांक ret;

	ret = strtobool(buf, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val) अणु
		pr_err("Enabling force_remove is not supported anymore. Please report to linux-acpi@vger.kernel.org if you depend on this functionality\n");
		वापस -EINVAL;
	पूर्ण
	वापस size;
पूर्ण

अटल स्थिर काष्ठा kobj_attribute क्रमce_हटाओ_attr =
	__ATTR(क्रमce_हटाओ, S_IRUGO | S_IWUSR, क्रमce_हटाओ_show,
	       क्रमce_हटाओ_store);

पूर्णांक __init acpi_sysfs_init(व्योम)
अणु
	पूर्णांक result;

	result = acpi_tables_sysfs_init();
	अगर (result)
		वापस result;

	hotplug_kobj = kobject_create_and_add("hotplug", acpi_kobj);
	अगर (!hotplug_kobj)
		वापस -ENOMEM;

	result = sysfs_create_file(hotplug_kobj, &क्रमce_हटाओ_attr.attr);
	अगर (result)
		वापस result;

	result = sysfs_create_file(acpi_kobj, &pm_profile_attr.attr);
	वापस result;
पूर्ण
