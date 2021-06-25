<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/fault-inject.h>

/*
 * setup_fault_attr() is a helper function क्रम various __setup handlers, so it
 * वापसs 0 on error, because that is what __setup handlers करो.
 */
पूर्णांक setup_fault_attr(काष्ठा fault_attr *attr, अक्षर *str)
अणु
	अचिन्हित दीर्घ probability;
	अचिन्हित दीर्घ पूर्णांकerval;
	पूर्णांक बार;
	पूर्णांक space;

	/* "<interval>,<probability>,<space>,<times>" */
	अगर (माला_पूछो(str, "%lu,%lu,%d,%d",
			&पूर्णांकerval, &probability, &space, &बार) < 4) अणु
		prपूर्णांकk(KERN_WARNING
			"FAULT_INJECTION: failed to parse arguments\n");
		वापस 0;
	पूर्ण

	attr->probability = probability;
	attr->पूर्णांकerval = पूर्णांकerval;
	atomic_set(&attr->बार, बार);
	atomic_set(&attr->space, space);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(setup_fault_attr);

अटल व्योम fail_dump(काष्ठा fault_attr *attr)
अणु
	अगर (attr->verbose > 0 && __ratelimit(&attr->ratelimit_state)) अणु
		prपूर्णांकk(KERN_NOTICE "FAULT_INJECTION: forcing a failure.\n"
		       "name %pd, interval %lu, probability %lu, "
		       "space %d, times %d\n", attr->dname,
		       attr->पूर्णांकerval, attr->probability,
		       atomic_पढ़ो(&attr->space),
		       atomic_पढ़ो(&attr->बार));
		अगर (attr->verbose > 1)
			dump_stack();
	पूर्ण
पूर्ण

#घोषणा atomic_dec_not_zero(v)		atomic_add_unless((v), -1, 0)

अटल bool fail_task(काष्ठा fault_attr *attr, काष्ठा task_काष्ठा *task)
अणु
	वापस in_task() && task->make_it_fail;
पूर्ण

#घोषणा MAX_STACK_TRACE_DEPTH 32

#अगर_घोषित CONFIG_FAULT_INJECTION_STACKTRACE_FILTER

अटल bool fail_stacktrace(काष्ठा fault_attr *attr)
अणु
	पूर्णांक depth = attr->stacktrace_depth;
	अचिन्हित दीर्घ entries[MAX_STACK_TRACE_DEPTH];
	पूर्णांक n, nr_entries;
	bool found = (attr->require_start == 0 && attr->require_end == अच_दीर्घ_उच्च);

	अगर (depth == 0)
		वापस found;

	nr_entries = stack_trace_save(entries, depth, 1);
	क्रम (n = 0; n < nr_entries; n++) अणु
		अगर (attr->reject_start <= entries[n] &&
			       entries[n] < attr->reject_end)
			वापस false;
		अगर (attr->require_start <= entries[n] &&
			       entries[n] < attr->require_end)
			found = true;
	पूर्ण
	वापस found;
पूर्ण

#अन्यथा

अटल अंतरभूत bool fail_stacktrace(काष्ठा fault_attr *attr)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_STACKTRACE_FILTER */

/*
 * This code is stolen from failदो_स्मृति-1.0
 * http://www.nongnu.org/failदो_स्मृति/
 */

bool should_fail(काष्ठा fault_attr *attr, sमाप_प्रकार size)
अणु
	अगर (in_task()) अणु
		अचिन्हित पूर्णांक fail_nth = READ_ONCE(current->fail_nth);

		अगर (fail_nth) अणु
			fail_nth--;
			WRITE_ONCE(current->fail_nth, fail_nth);
			अगर (!fail_nth)
				जाओ fail;

			वापस false;
		पूर्ण
	पूर्ण

	/* No need to check any other properties अगर the probability is 0 */
	अगर (attr->probability == 0)
		वापस false;

	अगर (attr->task_filter && !fail_task(attr, current))
		वापस false;

	अगर (atomic_पढ़ो(&attr->बार) == 0)
		वापस false;

	अगर (atomic_पढ़ो(&attr->space) > size) अणु
		atomic_sub(size, &attr->space);
		वापस false;
	पूर्ण

	अगर (attr->पूर्णांकerval > 1) अणु
		attr->count++;
		अगर (attr->count % attr->पूर्णांकerval)
			वापस false;
	पूर्ण

	अगर (attr->probability <= pअक्रमom_u32() % 100)
		वापस false;

	अगर (!fail_stacktrace(attr))
		वापस false;

fail:
	fail_dump(attr);

	अगर (atomic_पढ़ो(&attr->बार) != -1)
		atomic_dec_not_zero(&attr->बार);

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(should_fail);

#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS

अटल पूर्णांक debugfs_ul_set(व्योम *data, u64 val)
अणु
	*(अचिन्हित दीर्घ *)data = val;
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_ul_get(व्योम *data, u64 *val)
अणु
	*val = *(अचिन्हित दीर्घ *)data;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(fops_ul, debugfs_ul_get, debugfs_ul_set, "%llu\n");

अटल व्योम debugfs_create_ul(स्थिर अक्षर *name, umode_t mode,
			      काष्ठा dentry *parent, अचिन्हित दीर्घ *value)
अणु
	debugfs_create_file(name, mode, parent, value, &fops_ul);
पूर्ण

#अगर_घोषित CONFIG_FAULT_INJECTION_STACKTRACE_FILTER

अटल पूर्णांक debugfs_stacktrace_depth_set(व्योम *data, u64 val)
अणु
	*(अचिन्हित दीर्घ *)data =
		min_t(अचिन्हित दीर्घ, val, MAX_STACK_TRACE_DEPTH);

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(fops_stacktrace_depth, debugfs_ul_get,
			debugfs_stacktrace_depth_set, "%llu\n");

अटल व्योम debugfs_create_stacktrace_depth(स्थिर अक्षर *name, umode_t mode,
					    काष्ठा dentry *parent,
					    अचिन्हित दीर्घ *value)
अणु
	debugfs_create_file(name, mode, parent, value, &fops_stacktrace_depth);
पूर्ण

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_STACKTRACE_FILTER */

काष्ठा dentry *fault_create_debugfs_attr(स्थिर अक्षर *name,
			काष्ठा dentry *parent, काष्ठा fault_attr *attr)
अणु
	umode_t mode = S_IFREG | S_IRUSR | S_IWUSR;
	काष्ठा dentry *dir;

	dir = debugfs_create_dir(name, parent);
	अगर (IS_ERR(dir))
		वापस dir;

	debugfs_create_ul("probability", mode, dir, &attr->probability);
	debugfs_create_ul("interval", mode, dir, &attr->पूर्णांकerval);
	debugfs_create_atomic_t("times", mode, dir, &attr->बार);
	debugfs_create_atomic_t("space", mode, dir, &attr->space);
	debugfs_create_ul("verbose", mode, dir, &attr->verbose);
	debugfs_create_u32("verbose_ratelimit_interval_ms", mode, dir,
			   &attr->ratelimit_state.पूर्णांकerval);
	debugfs_create_u32("verbose_ratelimit_burst", mode, dir,
			   &attr->ratelimit_state.burst);
	debugfs_create_bool("task-filter", mode, dir, &attr->task_filter);

#अगर_घोषित CONFIG_FAULT_INJECTION_STACKTRACE_FILTER
	debugfs_create_stacktrace_depth("stacktrace-depth", mode, dir,
					&attr->stacktrace_depth);
	debugfs_create_ul("require-start", mode, dir, &attr->require_start);
	debugfs_create_ul("require-end", mode, dir, &attr->require_end);
	debugfs_create_ul("reject-start", mode, dir, &attr->reject_start);
	debugfs_create_ul("reject-end", mode, dir, &attr->reject_end);
#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_STACKTRACE_FILTER */

	attr->dname = dget(dir);
	वापस dir;
पूर्ण
EXPORT_SYMBOL_GPL(fault_create_debugfs_attr);

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_DEBUG_FS */
