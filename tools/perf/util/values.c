<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/zभाग.स>

#समावेश "values.h"
#समावेश "debug.h"

पूर्णांक perf_पढ़ो_values_init(काष्ठा perf_पढ़ो_values *values)
अणु
	values->thपढ़ोs_max = 16;
	values->pid = दो_स्मृति(values->thपढ़ोs_max * माप(*values->pid));
	values->tid = दो_स्मृति(values->thपढ़ोs_max * माप(*values->tid));
	values->value = zalloc(values->thपढ़ोs_max * माप(*values->value));
	अगर (!values->pid || !values->tid || !values->value) अणु
		pr_debug("failed to allocate read_values threads arrays");
		जाओ out_मुक्त_pid;
	पूर्ण
	values->thपढ़ोs = 0;

	values->counters_max = 16;
	values->counterrawid = दो_स्मृति(values->counters_max
				      * माप(*values->counterrawid));
	values->countername = दो_स्मृति(values->counters_max
				     * माप(*values->countername));
	अगर (!values->counterrawid || !values->countername) अणु
		pr_debug("failed to allocate read_values counters arrays");
		जाओ out_मुक्त_counter;
	पूर्ण
	values->counters = 0;

	वापस 0;

out_मुक्त_counter:
	zमुक्त(&values->counterrawid);
	zमुक्त(&values->countername);
out_मुक्त_pid:
	zमुक्त(&values->pid);
	zमुक्त(&values->tid);
	zमुक्त(&values->value);
	वापस -ENOMEM;
पूर्ण

व्योम perf_पढ़ो_values_destroy(काष्ठा perf_पढ़ो_values *values)
अणु
	पूर्णांक i;

	अगर (!values->thपढ़ोs_max || !values->counters_max)
		वापस;

	क्रम (i = 0; i < values->thपढ़ोs; i++)
		zमुक्त(&values->value[i]);
	zमुक्त(&values->value);
	zमुक्त(&values->pid);
	zमुक्त(&values->tid);
	zमुक्त(&values->counterrawid);
	क्रम (i = 0; i < values->counters; i++)
		zमुक्त(&values->countername[i]);
	zमुक्त(&values->countername);
पूर्ण

अटल पूर्णांक perf_पढ़ो_values__enlarge_thपढ़ोs(काष्ठा perf_पढ़ो_values *values)
अणु
	पूर्णांक nthपढ़ोs_max = values->thपढ़ोs_max * 2;
	व्योम *npid = पुनः_स्मृति(values->pid, nthपढ़ोs_max * माप(*values->pid)),
	     *ntid = पुनः_स्मृति(values->tid, nthपढ़ोs_max * माप(*values->tid)),
	     *nvalue = पुनः_स्मृति(values->value, nthपढ़ोs_max * माप(*values->value));

	अगर (!npid || !ntid || !nvalue)
		जाओ out_err;

	values->thपढ़ोs_max = nthपढ़ोs_max;
	values->pid = npid;
	values->tid = ntid;
	values->value = nvalue;
	वापस 0;
out_err:
	मुक्त(npid);
	मुक्त(ntid);
	मुक्त(nvalue);
	pr_debug("failed to enlarge read_values threads arrays");
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक perf_पढ़ो_values__findnew_thपढ़ो(काष्ठा perf_पढ़ो_values *values,
					    u32 pid, u32 tid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < values->thपढ़ोs; i++)
		अगर (values->pid[i] == pid && values->tid[i] == tid)
			वापस i;

	अगर (values->thपढ़ोs == values->thपढ़ोs_max) अणु
		i = perf_पढ़ो_values__enlarge_thपढ़ोs(values);
		अगर (i < 0)
			वापस i;
	पूर्ण

	i = values->thपढ़ोs;

	values->value[i] = zalloc(values->counters_max * माप(**values->value));
	अगर (!values->value[i]) अणु
		pr_debug("failed to allocate read_values counters array");
		वापस -ENOMEM;
	पूर्ण
	values->pid[i] = pid;
	values->tid[i] = tid;
	values->thपढ़ोs = i + 1;

	वापस i;
पूर्ण

अटल पूर्णांक perf_पढ़ो_values__enlarge_counters(काष्ठा perf_पढ़ो_values *values)
अणु
	अक्षर **countername;
	पूर्णांक i, counters_max = values->counters_max * 2;
	u64 *counterrawid = पुनः_स्मृति(values->counterrawid, counters_max * माप(*values->counterrawid));

	अगर (!counterrawid) अणु
		pr_debug("failed to enlarge read_values rawid array");
		जाओ out_enomem;
	पूर्ण

	countername = पुनः_स्मृति(values->countername, counters_max * माप(*values->countername));
	अगर (!countername) अणु
		pr_debug("failed to enlarge read_values rawid array");
		जाओ out_मुक्त_rawid;
	पूर्ण

	क्रम (i = 0; i < values->thपढ़ोs; i++) अणु
		u64 *value = पुनः_स्मृति(values->value[i], counters_max * माप(**values->value));
		पूर्णांक j;

		अगर (!value) अणु
			pr_debug("failed to enlarge read_values ->values array");
			जाओ out_मुक्त_name;
		पूर्ण

		क्रम (j = values->counters_max; j < counters_max; j++)
			value[j] = 0;

		values->value[i] = value;
	पूर्ण

	values->counters_max = counters_max;
	values->counterrawid = counterrawid;
	values->countername  = countername;

	वापस 0;
out_मुक्त_name:
	मुक्त(countername);
out_मुक्त_rawid:
	मुक्त(counterrawid);
out_enomem:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक perf_पढ़ो_values__findnew_counter(काष्ठा perf_पढ़ो_values *values,
					     u64 rawid, स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < values->counters; i++)
		अगर (values->counterrawid[i] == rawid)
			वापस i;

	अगर (values->counters == values->counters_max) अणु
		i = perf_पढ़ो_values__enlarge_counters(values);
		अगर (i)
			वापस i;
	पूर्ण

	i = values->counters++;
	values->counterrawid[i] = rawid;
	values->countername[i] = strdup(name);

	वापस i;
पूर्ण

पूर्णांक perf_पढ़ो_values_add_value(काष्ठा perf_पढ़ो_values *values,
				u32 pid, u32 tid,
				u64 rawid, स्थिर अक्षर *name, u64 value)
अणु
	पूर्णांक tindex, cindex;

	tindex = perf_पढ़ो_values__findnew_thपढ़ो(values, pid, tid);
	अगर (tindex < 0)
		वापस tindex;
	cindex = perf_पढ़ो_values__findnew_counter(values, rawid, name);
	अगर (cindex < 0)
		वापस cindex;

	values->value[tindex][cindex] += value;
	वापस 0;
पूर्ण

अटल व्योम perf_पढ़ो_values__display_pretty(खाता *fp,
					     काष्ठा perf_पढ़ो_values *values)
अणु
	पूर्णांक i, j;
	पूर्णांक pidwidth, tidwidth;
	पूर्णांक *counterwidth;

	counterwidth = दो_स्मृति(values->counters * माप(*counterwidth));
	अगर (!counterwidth) अणु
		ख_लिखो(fp, "INTERNAL ERROR: Failed to allocate counterwidth array\n");
		वापस;
	पूर्ण
	tidwidth = 3;
	pidwidth = 3;
	क्रम (j = 0; j < values->counters; j++)
		counterwidth[j] = म_माप(values->countername[j]);
	क्रम (i = 0; i < values->thपढ़ोs; i++) अणु
		पूर्णांक width;

		width = snम_लिखो(शून्य, 0, "%d", values->pid[i]);
		अगर (width > pidwidth)
			pidwidth = width;
		width = snम_लिखो(शून्य, 0, "%d", values->tid[i]);
		अगर (width > tidwidth)
			tidwidth = width;
		क्रम (j = 0; j < values->counters; j++) अणु
			width = snम_लिखो(शून्य, 0, "%" PRIu64, values->value[i][j]);
			अगर (width > counterwidth[j])
				counterwidth[j] = width;
		पूर्ण
	पूर्ण

	ख_लिखो(fp, "# %*s  %*s", pidwidth, "PID", tidwidth, "TID");
	क्रम (j = 0; j < values->counters; j++)
		ख_लिखो(fp, "  %*s", counterwidth[j], values->countername[j]);
	ख_लिखो(fp, "\n");

	क्रम (i = 0; i < values->thपढ़ोs; i++) अणु
		ख_लिखो(fp, "  %*d  %*d", pidwidth, values->pid[i],
			tidwidth, values->tid[i]);
		क्रम (j = 0; j < values->counters; j++)
			ख_लिखो(fp, "  %*" PRIu64,
				counterwidth[j], values->value[i][j]);
		ख_लिखो(fp, "\n");
	पूर्ण
	मुक्त(counterwidth);
पूर्ण

अटल व्योम perf_पढ़ो_values__display_raw(खाता *fp,
					  काष्ठा perf_पढ़ो_values *values)
अणु
	पूर्णांक width, pidwidth, tidwidth, namewidth, rawwidth, countwidth;
	पूर्णांक i, j;

	tidwidth = 3; /* TID */
	pidwidth = 3; /* PID */
	namewidth = 4; /* "Name" */
	rawwidth = 3; /* "Raw" */
	countwidth = 5; /* "Count" */

	क्रम (i = 0; i < values->thपढ़ोs; i++) अणु
		width = snम_लिखो(शून्य, 0, "%d", values->pid[i]);
		अगर (width > pidwidth)
			pidwidth = width;
		width = snम_लिखो(शून्य, 0, "%d", values->tid[i]);
		अगर (width > tidwidth)
			tidwidth = width;
	पूर्ण
	क्रम (j = 0; j < values->counters; j++) अणु
		width = म_माप(values->countername[j]);
		अगर (width > namewidth)
			namewidth = width;
		width = snम_लिखो(शून्य, 0, "%" PRIx64, values->counterrawid[j]);
		अगर (width > rawwidth)
			rawwidth = width;
	पूर्ण
	क्रम (i = 0; i < values->thपढ़ोs; i++) अणु
		क्रम (j = 0; j < values->counters; j++) अणु
			width = snम_लिखो(शून्य, 0, "%" PRIu64, values->value[i][j]);
			अगर (width > countwidth)
				countwidth = width;
		पूर्ण
	पूर्ण

	ख_लिखो(fp, "# %*s  %*s  %*s  %*s  %*s\n",
		pidwidth, "PID", tidwidth, "TID",
		namewidth, "Name", rawwidth, "Raw",
		countwidth, "Count");
	क्रम (i = 0; i < values->thपढ़ोs; i++)
		क्रम (j = 0; j < values->counters; j++)
			ख_लिखो(fp, "  %*d  %*d  %*s  %*" PRIx64 "  %*" PRIu64,
				pidwidth, values->pid[i],
				tidwidth, values->tid[i],
				namewidth, values->countername[j],
				rawwidth, values->counterrawid[j],
				countwidth, values->value[i][j]);
पूर्ण

व्योम perf_पढ़ो_values_display(खाता *fp, काष्ठा perf_पढ़ो_values *values, पूर्णांक raw)
अणु
	अगर (raw)
		perf_पढ़ो_values__display_raw(fp, values);
	अन्यथा
		perf_पढ़ो_values__display_pretty(fp, values);
पूर्ण
