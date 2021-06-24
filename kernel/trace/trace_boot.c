<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_boot.c
 * Tracing kernel boot-समय
 */

#घोषणा pr_fmt(fmt)	"trace_boot: " fmt

#समावेश <linux/bootconfig.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/trace.h>
#समावेश <linux/trace_events.h>

#समावेश "trace.h"

#घोषणा MAX_BUF_LEN 256

अटल व्योम __init
trace_boot_set_instance_options(काष्ठा trace_array *tr, काष्ठा xbc_node *node)
अणु
	काष्ठा xbc_node *anode;
	स्थिर अक्षर *p;
	अक्षर buf[MAX_BUF_LEN];
	अचिन्हित दीर्घ v = 0;

	/* Common ftrace options */
	xbc_node_क्रम_each_array_value(node, "options", anode, p) अणु
		अगर (strlcpy(buf, p, ARRAY_SIZE(buf)) >= ARRAY_SIZE(buf)) अणु
			pr_err("String is too long: %s\n", p);
			जारी;
		पूर्ण

		अगर (trace_set_options(tr, buf) < 0)
			pr_err("Failed to set option: %s\n", buf);
	पूर्ण

	p = xbc_node_find_value(node, "tracing_on", शून्य);
	अगर (p && *p != '\0') अणु
		अगर (kम_से_अदीर्घ(p, 10, &v))
			pr_err("Failed to set tracing on: %s\n", p);
		अगर (v)
			tracer_tracing_on(tr);
		अन्यथा
			tracer_tracing_off(tr);
	पूर्ण

	p = xbc_node_find_value(node, "trace_clock", शून्य);
	अगर (p && *p != '\0') अणु
		अगर (tracing_set_घड़ी(tr, p) < 0)
			pr_err("Failed to set trace clock: %s\n", p);
	पूर्ण

	p = xbc_node_find_value(node, "buffer_size", शून्य);
	अगर (p && *p != '\0') अणु
		v = memparse(p, शून्य);
		अगर (v < PAGE_SIZE)
			pr_err("Buffer size is too small: %s\n", p);
		अगर (tracing_resize_ring_buffer(tr, v, RING_BUFFER_ALL_CPUS) < 0)
			pr_err("Failed to resize trace buffer to %s\n", p);
	पूर्ण

	p = xbc_node_find_value(node, "cpumask", शून्य);
	अगर (p && *p != '\0') अणु
		cpumask_var_t new_mask;

		अगर (alloc_cpumask_var(&new_mask, GFP_KERNEL)) अणु
			अगर (cpumask_parse(p, new_mask) < 0 ||
			    tracing_set_cpumask(tr, new_mask) < 0)
				pr_err("Failed to set new CPU mask %s\n", p);
			मुक्त_cpumask_var(new_mask);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_EVENT_TRACING
अटल व्योम __init
trace_boot_enable_events(काष्ठा trace_array *tr, काष्ठा xbc_node *node)
अणु
	काष्ठा xbc_node *anode;
	अक्षर buf[MAX_BUF_LEN];
	स्थिर अक्षर *p;

	xbc_node_क्रम_each_array_value(node, "events", anode, p) अणु
		अगर (strlcpy(buf, p, ARRAY_SIZE(buf)) >= ARRAY_SIZE(buf)) अणु
			pr_err("String is too long: %s\n", p);
			जारी;
		पूर्ण

		अगर (ftrace_set_clr_event(tr, buf, 1) < 0)
			pr_err("Failed to enable event: %s\n", p);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KPROBE_EVENTS
अटल पूर्णांक __init
trace_boot_add_kprobe_event(काष्ठा xbc_node *node, स्थिर अक्षर *event)
अणु
	काष्ठा dynevent_cmd cmd;
	काष्ठा xbc_node *anode;
	अक्षर buf[MAX_BUF_LEN];
	स्थिर अक्षर *val;
	पूर्णांक ret = 0;

	xbc_node_क्रम_each_array_value(node, "probes", anode, val) अणु
		kprobe_event_cmd_init(&cmd, buf, MAX_BUF_LEN);

		ret = kprobe_event_gen_cmd_start(&cmd, event, val);
		अगर (ret) अणु
			pr_err("Failed to generate probe: %s\n", buf);
			अवरोध;
		पूर्ण

		ret = kprobe_event_gen_cmd_end(&cmd);
		अगर (ret) अणु
			pr_err("Failed to add probe: %s\n", buf);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक __init
trace_boot_add_kprobe_event(काष्ठा xbc_node *node, स्थिर अक्षर *event)
अणु
	pr_err("Kprobe event is not supported.\n");
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYNTH_EVENTS
अटल पूर्णांक __init
trace_boot_add_synth_event(काष्ठा xbc_node *node, स्थिर अक्षर *event)
अणु
	काष्ठा dynevent_cmd cmd;
	काष्ठा xbc_node *anode;
	अक्षर buf[MAX_BUF_LEN];
	स्थिर अक्षर *p;
	पूर्णांक ret;

	synth_event_cmd_init(&cmd, buf, MAX_BUF_LEN);

	ret = synth_event_gen_cmd_start(&cmd, event, शून्य);
	अगर (ret)
		वापस ret;

	xbc_node_क्रम_each_array_value(node, "fields", anode, p) अणु
		ret = synth_event_add_field_str(&cmd, p);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = synth_event_gen_cmd_end(&cmd);
	अगर (ret < 0)
		pr_err("Failed to add synthetic event: %s\n", buf);

	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक __init
trace_boot_add_synth_event(काष्ठा xbc_node *node, स्थिर अक्षर *event)
अणु
	pr_err("Synthetic event is not supported.\n");
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init
trace_boot_init_one_event(काष्ठा trace_array *tr, काष्ठा xbc_node *gnode,
			  काष्ठा xbc_node *enode)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा xbc_node *anode;
	अक्षर buf[MAX_BUF_LEN];
	स्थिर अक्षर *p, *group, *event;

	group = xbc_node_get_data(gnode);
	event = xbc_node_get_data(enode);

	अगर (!म_भेद(group, "kprobes"))
		अगर (trace_boot_add_kprobe_event(enode, event) < 0)
			वापस;
	अगर (!म_भेद(group, "synthetic"))
		अगर (trace_boot_add_synth_event(enode, event) < 0)
			वापस;

	mutex_lock(&event_mutex);
	file = find_event_file(tr, group, event);
	अगर (!file) अणु
		pr_err("Failed to find event: %s:%s\n", group, event);
		जाओ out;
	पूर्ण

	p = xbc_node_find_value(enode, "filter", शून्य);
	अगर (p && *p != '\0') अणु
		अगर (strlcpy(buf, p, ARRAY_SIZE(buf)) >= ARRAY_SIZE(buf))
			pr_err("filter string is too long: %s\n", p);
		अन्यथा अगर (apply_event_filter(file, buf) < 0)
			pr_err("Failed to apply filter: %s\n", buf);
	पूर्ण

	xbc_node_क्रम_each_array_value(enode, "actions", anode, p) अणु
		अगर (strlcpy(buf, p, ARRAY_SIZE(buf)) >= ARRAY_SIZE(buf))
			pr_err("action string is too long: %s\n", p);
		अन्यथा अगर (trigger_process_regex(file, buf) < 0)
			pr_err("Failed to apply an action: %s\n", buf);
	पूर्ण

	अगर (xbc_node_find_value(enode, "enable", शून्य)) अणु
		अगर (trace_event_enable_disable(file, 1, 0) < 0)
			pr_err("Failed to enable event node: %s:%s\n",
				group, event);
	पूर्ण
out:
	mutex_unlock(&event_mutex);
पूर्ण

अटल व्योम __init
trace_boot_init_events(काष्ठा trace_array *tr, काष्ठा xbc_node *node)
अणु
	काष्ठा xbc_node *gnode, *enode;

	node = xbc_node_find_child(node, "event");
	अगर (!node)
		वापस;
	/* per-event key starts with "event.GROUP.EVENT" */
	xbc_node_क्रम_each_child(node, gnode)
		xbc_node_क्रम_each_child(gnode, enode)
			trace_boot_init_one_event(tr, gnode, enode);
पूर्ण
#अन्यथा
#घोषणा trace_boot_enable_events(tr, node) करो अणुपूर्ण जबतक (0)
#घोषणा trace_boot_init_events(tr, node) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
अटल व्योम __init
trace_boot_set_ftrace_filter(काष्ठा trace_array *tr, काष्ठा xbc_node *node)
अणु
	काष्ठा xbc_node *anode;
	स्थिर अक्षर *p;
	अक्षर *q;

	xbc_node_क्रम_each_array_value(node, "ftrace.filters", anode, p) अणु
		q = kstrdup(p, GFP_KERNEL);
		अगर (!q)
			वापस;
		अगर (ftrace_set_filter(tr->ops, q, म_माप(q), 0) < 0)
			pr_err("Failed to add %s to ftrace filter\n", p);
		अन्यथा
			ftrace_filter_param = true;
		kमुक्त(q);
	पूर्ण
	xbc_node_क्रम_each_array_value(node, "ftrace.notraces", anode, p) अणु
		q = kstrdup(p, GFP_KERNEL);
		अगर (!q)
			वापस;
		अगर (ftrace_set_notrace(tr->ops, q, म_माप(q), 0) < 0)
			pr_err("Failed to add %s to ftrace filter\n", p);
		अन्यथा
			ftrace_filter_param = true;
		kमुक्त(q);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा trace_boot_set_ftrace_filter(tr, node) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम __init
trace_boot_enable_tracer(काष्ठा trace_array *tr, काष्ठा xbc_node *node)
अणु
	स्थिर अक्षर *p;

	trace_boot_set_ftrace_filter(tr, node);

	p = xbc_node_find_value(node, "tracer", शून्य);
	अगर (p && *p != '\0') अणु
		अगर (tracing_set_tracer(tr, p) < 0)
			pr_err("Failed to set given tracer: %s\n", p);
	पूर्ण

	/* Since tracer can मुक्त snapshot buffer, allocate snapshot here.*/
	अगर (xbc_node_find_value(node, "alloc_snapshot", शून्य)) अणु
		अगर (tracing_alloc_snapshot_instance(tr) < 0)
			pr_err("Failed to allocate snapshot buffer\n");
	पूर्ण
पूर्ण

अटल व्योम __init
trace_boot_init_one_instance(काष्ठा trace_array *tr, काष्ठा xbc_node *node)
अणु
	trace_boot_set_instance_options(tr, node);
	trace_boot_init_events(tr, node);
	trace_boot_enable_events(tr, node);
	trace_boot_enable_tracer(tr, node);
पूर्ण

अटल व्योम __init
trace_boot_init_instances(काष्ठा xbc_node *node)
अणु
	काष्ठा xbc_node *inode;
	काष्ठा trace_array *tr;
	स्थिर अक्षर *p;

	node = xbc_node_find_child(node, "instance");
	अगर (!node)
		वापस;

	xbc_node_क्रम_each_child(node, inode) अणु
		p = xbc_node_get_data(inode);
		अगर (!p || *p == '\0')
			जारी;

		tr = trace_array_get_by_name(p);
		अगर (!tr) अणु
			pr_err("Failed to get trace instance %s\n", p);
			जारी;
		पूर्ण
		trace_boot_init_one_instance(tr, inode);
		trace_array_put(tr);
	पूर्ण
पूर्ण

अटल पूर्णांक __init trace_boot_init(व्योम)
अणु
	काष्ठा xbc_node *trace_node;
	काष्ठा trace_array *tr;

	trace_node = xbc_find_node("ftrace");
	अगर (!trace_node)
		वापस 0;

	tr = top_trace_array();
	अगर (!tr)
		वापस 0;

	/* Global trace array is also one instance */
	trace_boot_init_one_instance(tr, trace_node);
	trace_boot_init_instances(trace_node);

	disable_tracing_selftest("running boot-time tracing");

	वापस 0;
पूर्ण
/*
 * Start tracing at the end of core-initcall, so that it starts tracing
 * from the beginning of postcore_initcall.
 */
core_initcall_sync(trace_boot_init);
