<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2004-2009  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 */


#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

#समावेश "cpufreq.h"
#समावेश "cpupower_intern.h"

/* CPUFREQ sysfs access **************************************************/

/* helper function to पढ़ो file from /sys पूर्णांकo given buffer */
/* fname is a relative path under "cpuX/cpufreq" dir */
अटल अचिन्हित पूर्णांक sysfs_cpufreq_पढ़ो_file(अचिन्हित पूर्णांक cpu, स्थिर अक्षर *fname,
					    अक्षर *buf, माप_प्रकार buflen)
अणु
	अक्षर path[SYSFS_PATH_MAX];

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/cpufreq/%s",
			 cpu, fname);
	वापस cpuघातer_पढ़ो_sysfs(path, buf, buflen);
पूर्ण

/* helper function to ग_लिखो a new value to a /sys file */
/* fname is a relative path under "cpuX/cpufreq" dir */
अटल अचिन्हित पूर्णांक sysfs_cpufreq_ग_लिखो_file(अचिन्हित पूर्णांक cpu,
					     स्थिर अक्षर *fname,
					     स्थिर अक्षर *value, माप_प्रकार len)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	पूर्णांक fd;
	sमाप_प्रकार numग_लिखो;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/cpufreq/%s",
			 cpu, fname);

	fd = खोलो(path, O_WRONLY);
	अगर (fd == -1)
		वापस 0;

	numग_लिखो = ग_लिखो(fd, value, len);
	अगर (numग_लिखो < 1) अणु
		बंद(fd);
		वापस 0;
	पूर्ण

	बंद(fd);

	वापस (अचिन्हित पूर्णांक) numग_लिखो;
पूर्ण

/* पढ़ो access to files which contain one numeric value */

क्रमागत cpufreq_value अणु
	CPUINFO_CUR_FREQ,
	CPUINFO_MIN_FREQ,
	CPUINFO_MAX_FREQ,
	CPUINFO_LATENCY,
	SCALING_CUR_FREQ,
	SCALING_MIN_FREQ,
	SCALING_MAX_FREQ,
	STATS_NUM_TRANSITIONS,
	MAX_CPUFREQ_VALUE_READ_खाताS
पूर्ण;

अटल स्थिर अक्षर *cpufreq_value_files[MAX_CPUFREQ_VALUE_READ_खाताS] = अणु
	[CPUINFO_CUR_FREQ] = "cpuinfo_cur_freq",
	[CPUINFO_MIN_FREQ] = "cpuinfo_min_freq",
	[CPUINFO_MAX_FREQ] = "cpuinfo_max_freq",
	[CPUINFO_LATENCY]  = "cpuinfo_transition_latency",
	[SCALING_CUR_FREQ] = "scaling_cur_freq",
	[SCALING_MIN_FREQ] = "scaling_min_freq",
	[SCALING_MAX_FREQ] = "scaling_max_freq",
	[STATS_NUM_TRANSITIONS] = "stats/total_trans"
पूर्ण;


अटल अचिन्हित दीर्घ sysfs_cpufreq_get_one_value(अचिन्हित पूर्णांक cpu,
						 क्रमागत cpufreq_value which)
अणु
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक len;
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर *endp;

	अगर (which >= MAX_CPUFREQ_VALUE_READ_खाताS)
		वापस 0;

	len = sysfs_cpufreq_पढ़ो_file(cpu, cpufreq_value_files[which],
				linebuf, माप(linebuf));

	अगर (len == 0)
		वापस 0;

	value = म_से_अदीर्घ(linebuf, &endp, 0);

	अगर (endp == linebuf || त्रुटि_सं == दुस्फल)
		वापस 0;

	वापस value;
पूर्ण

/* पढ़ो access to files which contain one string */

क्रमागत cpufreq_string अणु
	SCALING_DRIVER,
	SCALING_GOVERNOR,
	MAX_CPUFREQ_STRING_खाताS
पूर्ण;

अटल स्थिर अक्षर *cpufreq_string_files[MAX_CPUFREQ_STRING_खाताS] = अणु
	[SCALING_DRIVER] = "scaling_driver",
	[SCALING_GOVERNOR] = "scaling_governor",
पूर्ण;


अटल अक्षर *sysfs_cpufreq_get_one_string(अचिन्हित पूर्णांक cpu,
					   क्रमागत cpufreq_string which)
अणु
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर *result;
	अचिन्हित पूर्णांक len;

	अगर (which >= MAX_CPUFREQ_STRING_खाताS)
		वापस शून्य;

	len = sysfs_cpufreq_पढ़ो_file(cpu, cpufreq_string_files[which],
				linebuf, माप(linebuf));
	अगर (len == 0)
		वापस शून्य;

	result = strdup(linebuf);
	अगर (result == शून्य)
		वापस शून्य;

	अगर (result[म_माप(result) - 1] == '\n')
		result[म_माप(result) - 1] = '\0';

	वापस result;
पूर्ण

/* ग_लिखो access */

क्रमागत cpufreq_ग_लिखो अणु
	WRITE_SCALING_MIN_FREQ,
	WRITE_SCALING_MAX_FREQ,
	WRITE_SCALING_GOVERNOR,
	WRITE_SCALING_SET_SPEED,
	MAX_CPUFREQ_WRITE_खाताS
पूर्ण;

अटल स्थिर अक्षर *cpufreq_ग_लिखो_files[MAX_CPUFREQ_WRITE_खाताS] = अणु
	[WRITE_SCALING_MIN_FREQ] = "scaling_min_freq",
	[WRITE_SCALING_MAX_FREQ] = "scaling_max_freq",
	[WRITE_SCALING_GOVERNOR] = "scaling_governor",
	[WRITE_SCALING_SET_SPEED] = "scaling_setspeed",
पूर्ण;

अटल पूर्णांक sysfs_cpufreq_ग_लिखो_one_value(अचिन्हित पूर्णांक cpu,
					 क्रमागत cpufreq_ग_लिखो which,
					 स्थिर अक्षर *new_value, माप_प्रकार len)
अणु
	अगर (which >= MAX_CPUFREQ_WRITE_खाताS)
		वापस 0;

	अगर (sysfs_cpufreq_ग_लिखो_file(cpu, cpufreq_ग_लिखो_files[which],
					new_value, len) != len)
		वापस -ENODEV;

	वापस 0;
पूर्ण;

अचिन्हित दीर्घ cpufreq_get_freq_kernel(अचिन्हित पूर्णांक cpu)
अणु
	वापस sysfs_cpufreq_get_one_value(cpu, SCALING_CUR_FREQ);
पूर्ण

अचिन्हित दीर्घ cpufreq_get_freq_hardware(अचिन्हित पूर्णांक cpu)
अणु
	वापस sysfs_cpufreq_get_one_value(cpu, CPUINFO_CUR_FREQ);
पूर्ण

अचिन्हित दीर्घ cpufreq_get_transition_latency(अचिन्हित पूर्णांक cpu)
अणु
	वापस sysfs_cpufreq_get_one_value(cpu, CPUINFO_LATENCY);
पूर्ण

पूर्णांक cpufreq_get_hardware_limits(अचिन्हित पूर्णांक cpu,
				अचिन्हित दीर्घ *min,
				अचिन्हित दीर्घ *max)
अणु
	अगर ((!min) || (!max))
		वापस -EINVAL;

	*min = sysfs_cpufreq_get_one_value(cpu, CPUINFO_MIN_FREQ);
	अगर (!*min)
		वापस -ENODEV;

	*max = sysfs_cpufreq_get_one_value(cpu, CPUINFO_MAX_FREQ);
	अगर (!*max)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अक्षर *cpufreq_get_driver(अचिन्हित पूर्णांक cpu)
अणु
	वापस sysfs_cpufreq_get_one_string(cpu, SCALING_DRIVER);
पूर्ण

व्योम cpufreq_put_driver(अक्षर *ptr)
अणु
	अगर (!ptr)
		वापस;
	मुक्त(ptr);
पूर्ण

काष्ठा cpufreq_policy *cpufreq_get_policy(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy;

	policy = दो_स्मृति(माप(काष्ठा cpufreq_policy));
	अगर (!policy)
		वापस शून्य;

	policy->governor = sysfs_cpufreq_get_one_string(cpu, SCALING_GOVERNOR);
	अगर (!policy->governor) अणु
		मुक्त(policy);
		वापस शून्य;
	पूर्ण
	policy->min = sysfs_cpufreq_get_one_value(cpu, SCALING_MIN_FREQ);
	policy->max = sysfs_cpufreq_get_one_value(cpu, SCALING_MAX_FREQ);
	अगर ((!policy->min) || (!policy->max)) अणु
		मुक्त(policy->governor);
		मुक्त(policy);
		वापस शून्य;
	पूर्ण

	वापस policy;
पूर्ण

व्योम cpufreq_put_policy(काष्ठा cpufreq_policy *policy)
अणु
	अगर ((!policy) || (!policy->governor))
		वापस;

	मुक्त(policy->governor);
	policy->governor = शून्य;
	मुक्त(policy);
पूर्ण

काष्ठा cpufreq_available_governors *cpufreq_get_available_governors(अचिन्हित
								पूर्णांक cpu)
अणु
	काष्ठा cpufreq_available_governors *first = शून्य;
	काष्ठा cpufreq_available_governors *current = शून्य;
	अक्षर linebuf[MAX_LINE_LEN];
	अचिन्हित पूर्णांक pos, i;
	अचिन्हित पूर्णांक len;

	len = sysfs_cpufreq_पढ़ो_file(cpu, "scaling_available_governors",
				linebuf, माप(linebuf));
	अगर (len == 0)
		वापस शून्य;

	pos = 0;
	क्रम (i = 0; i < len; i++) अणु
		अगर (linebuf[i] == ' ' || linebuf[i] == '\n') अणु
			अगर (i - pos < 2)
				जारी;
			अगर (current) अणु
				current->next = दो_स्मृति(माप(*current));
				अगर (!current->next)
					जाओ error_out;
				current = current->next;
			पूर्ण अन्यथा अणु
				first = दो_स्मृति(माप(*first));
				अगर (!first)
					वापस शून्य;
				current = first;
			पूर्ण
			current->first = first;
			current->next = शून्य;

			current->governor = दो_स्मृति(i - pos + 1);
			अगर (!current->governor)
				जाओ error_out;

			स_नकल(current->governor, linebuf + pos, i - pos);
			current->governor[i - pos] = '\0';
			pos = i + 1;
		पूर्ण
	पूर्ण

	वापस first;

 error_out:
	जबतक (first) अणु
		current = first->next;
		अगर (first->governor)
			मुक्त(first->governor);
		मुक्त(first);
		first = current;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम cpufreq_put_available_governors(काष्ठा cpufreq_available_governors *any)
अणु
	काष्ठा cpufreq_available_governors *पंचांगp, *next;

	अगर (!any)
		वापस;

	पंचांगp = any->first;
	जबतक (पंचांगp) अणु
		next = पंचांगp->next;
		अगर (पंचांगp->governor)
			मुक्त(पंचांगp->governor);
		मुक्त(पंचांगp);
		पंचांगp = next;
	पूर्ण
पूर्ण


काष्ठा cpufreq_available_frequencies
*cpufreq_get_available_frequencies(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_available_frequencies *first = शून्य;
	काष्ठा cpufreq_available_frequencies *current = शून्य;
	अक्षर one_value[SYSFS_PATH_MAX];
	अक्षर linebuf[MAX_LINE_LEN];
	अचिन्हित पूर्णांक pos, i;
	अचिन्हित पूर्णांक len;

	len = sysfs_cpufreq_पढ़ो_file(cpu, "scaling_available_frequencies",
				      linebuf, माप(linebuf));
	अगर (len == 0)
		वापस शून्य;

	pos = 0;
	क्रम (i = 0; i < len; i++) अणु
		अगर (linebuf[i] == ' ' || linebuf[i] == '\n') अणु
			अगर (i - pos < 2)
				जारी;
			अगर (i - pos >= SYSFS_PATH_MAX)
				जाओ error_out;
			अगर (current) अणु
				current->next = दो_स्मृति(माप(*current));
				अगर (!current->next)
					जाओ error_out;
				current = current->next;
			पूर्ण अन्यथा अणु
				first = दो_स्मृति(माप(*first));
				अगर (!first)
					वापस शून्य;
				current = first;
			पूर्ण
			current->first = first;
			current->next = शून्य;

			स_नकल(one_value, linebuf + pos, i - pos);
			one_value[i - pos] = '\0';
			अगर (माला_पूछो(one_value, "%lu", &current->frequency) != 1)
				जाओ error_out;

			pos = i + 1;
		पूर्ण
	पूर्ण

	वापस first;

 error_out:
	जबतक (first) अणु
		current = first->next;
		मुक्त(first);
		first = current;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा cpufreq_available_frequencies
*cpufreq_get_boost_frequencies(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_available_frequencies *first = शून्य;
	काष्ठा cpufreq_available_frequencies *current = शून्य;
	अक्षर one_value[SYSFS_PATH_MAX];
	अक्षर linebuf[MAX_LINE_LEN];
	अचिन्हित पूर्णांक pos, i;
	अचिन्हित पूर्णांक len;

	len = sysfs_cpufreq_पढ़ो_file(cpu, "scaling_boost_frequencies",
				      linebuf, माप(linebuf));
	अगर (len == 0)
		वापस शून्य;

	pos = 0;
	क्रम (i = 0; i < len; i++) अणु
		अगर (linebuf[i] == ' ' || linebuf[i] == '\n') अणु
			अगर (i - pos < 2)
				जारी;
			अगर (i - pos >= SYSFS_PATH_MAX)
				जाओ error_out;
			अगर (current) अणु
				current->next = दो_स्मृति(माप(*current));
				अगर (!current->next)
					जाओ error_out;
				current = current->next;
			पूर्ण अन्यथा अणु
				first = दो_स्मृति(माप(*first));
				अगर (!first)
					वापस शून्य;
				current = first;
			पूर्ण
			current->first = first;
			current->next = शून्य;

			स_नकल(one_value, linebuf + pos, i - pos);
			one_value[i - pos] = '\0';
			अगर (माला_पूछो(one_value, "%lu", &current->frequency) != 1)
				जाओ error_out;

			pos = i + 1;
		पूर्ण
	पूर्ण

	वापस first;

 error_out:
	जबतक (first) अणु
		current = first->next;
		मुक्त(first);
		first = current;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम cpufreq_put_available_frequencies(काष्ठा cpufreq_available_frequencies *any)
अणु
	काष्ठा cpufreq_available_frequencies *पंचांगp, *next;

	अगर (!any)
		वापस;

	पंचांगp = any->first;
	जबतक (पंचांगp) अणु
		next = पंचांगp->next;
		मुक्त(पंचांगp);
		पंचांगp = next;
	पूर्ण
पूर्ण

व्योम cpufreq_put_boost_frequencies(काष्ठा cpufreq_available_frequencies *any)
अणु
	cpufreq_put_available_frequencies(any);
पूर्ण

अटल काष्ठा cpufreq_affected_cpus *sysfs_get_cpu_list(अचिन्हित पूर्णांक cpu,
							स्थिर अक्षर *file)
अणु
	काष्ठा cpufreq_affected_cpus *first = शून्य;
	काष्ठा cpufreq_affected_cpus *current = शून्य;
	अक्षर one_value[SYSFS_PATH_MAX];
	अक्षर linebuf[MAX_LINE_LEN];
	अचिन्हित पूर्णांक pos, i;
	अचिन्हित पूर्णांक len;

	len = sysfs_cpufreq_पढ़ो_file(cpu, file, linebuf, माप(linebuf));
	अगर (len == 0)
		वापस शून्य;

	pos = 0;
	क्रम (i = 0; i < len; i++) अणु
		अगर (i == len || linebuf[i] == ' ' || linebuf[i] == '\n') अणु
			अगर (i - pos  < 1)
				जारी;
			अगर (i - pos >= SYSFS_PATH_MAX)
				जाओ error_out;
			अगर (current) अणु
				current->next = दो_स्मृति(माप(*current));
				अगर (!current->next)
					जाओ error_out;
				current = current->next;
			पूर्ण अन्यथा अणु
				first = दो_स्मृति(माप(*first));
				अगर (!first)
					वापस शून्य;
				current = first;
			पूर्ण
			current->first = first;
			current->next = शून्य;

			स_नकल(one_value, linebuf + pos, i - pos);
			one_value[i - pos] = '\0';

			अगर (माला_पूछो(one_value, "%u", &current->cpu) != 1)
				जाओ error_out;

			pos = i + 1;
		पूर्ण
	पूर्ण

	वापस first;

 error_out:
	जबतक (first) अणु
		current = first->next;
		मुक्त(first);
		first = current;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा cpufreq_affected_cpus *cpufreq_get_affected_cpus(अचिन्हित पूर्णांक cpu)
अणु
	वापस sysfs_get_cpu_list(cpu, "affected_cpus");
पूर्ण

व्योम cpufreq_put_affected_cpus(काष्ठा cpufreq_affected_cpus *any)
अणु
	काष्ठा cpufreq_affected_cpus *पंचांगp, *next;

	अगर (!any)
		वापस;

	पंचांगp = any->first;
	जबतक (पंचांगp) अणु
		next = पंचांगp->next;
		मुक्त(पंचांगp);
		पंचांगp = next;
	पूर्ण
पूर्ण


काष्ठा cpufreq_affected_cpus *cpufreq_get_related_cpus(अचिन्हित पूर्णांक cpu)
अणु
	वापस sysfs_get_cpu_list(cpu, "related_cpus");
पूर्ण

व्योम cpufreq_put_related_cpus(काष्ठा cpufreq_affected_cpus *any)
अणु
	cpufreq_put_affected_cpus(any);
पूर्ण

अटल पूर्णांक verअगरy_gov(अक्षर *new_gov, अक्षर *passed_gov)
अणु
	अचिन्हित पूर्णांक i, j = 0;

	अगर (!passed_gov || (म_माप(passed_gov) > 19))
		वापस -EINVAL;

	म_नकलन(new_gov, passed_gov, 20);
	क्रम (i = 0; i < 20; i++) अणु
		अगर (j) अणु
			new_gov[i] = '\0';
			जारी;
		पूर्ण
		अगर ((new_gov[i] >= 'a') && (new_gov[i] <= 'z'))
			जारी;

		अगर ((new_gov[i] >= 'A') && (new_gov[i] <= 'Z'))
			जारी;

		अगर (new_gov[i] == '-')
			जारी;

		अगर (new_gov[i] == '_')
			जारी;

		अगर (new_gov[i] == '\0') अणु
			j = 1;
			जारी;
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	new_gov[19] = '\0';
	वापस 0;
पूर्ण

पूर्णांक cpufreq_set_policy(अचिन्हित पूर्णांक cpu, काष्ठा cpufreq_policy *policy)
अणु
	अक्षर min[SYSFS_PATH_MAX];
	अक्षर max[SYSFS_PATH_MAX];
	अक्षर gov[SYSFS_PATH_MAX];
	पूर्णांक ret;
	अचिन्हित दीर्घ old_min;
	पूर्णांक ग_लिखो_max_first;

	अगर (!policy || !(policy->governor))
		वापस -EINVAL;

	अगर (policy->max < policy->min)
		वापस -EINVAL;

	अगर (verअगरy_gov(gov, policy->governor))
		वापस -EINVAL;

	snम_लिखो(min, SYSFS_PATH_MAX, "%lu", policy->min);
	snम_लिखो(max, SYSFS_PATH_MAX, "%lu", policy->max);

	old_min = sysfs_cpufreq_get_one_value(cpu, SCALING_MIN_FREQ);
	ग_लिखो_max_first = (old_min && (policy->max < old_min) ? 0 : 1);

	अगर (ग_लिखो_max_first) अणु
		ret = sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_MAX_FREQ,
						    max, म_माप(max));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_MIN_FREQ, min,
					    म_माप(min));
	अगर (ret)
		वापस ret;

	अगर (!ग_लिखो_max_first) अणु
		ret = sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_MAX_FREQ,
						    max, म_माप(max));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_GOVERNOR,
					     gov, म_माप(gov));
पूर्ण


पूर्णांक cpufreq_modअगरy_policy_min(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ min_freq)
अणु
	अक्षर value[SYSFS_PATH_MAX];

	snम_लिखो(value, SYSFS_PATH_MAX, "%lu", min_freq);

	वापस sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_MIN_FREQ,
					     value, म_माप(value));
पूर्ण


पूर्णांक cpufreq_modअगरy_policy_max(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ max_freq)
अणु
	अक्षर value[SYSFS_PATH_MAX];

	snम_लिखो(value, SYSFS_PATH_MAX, "%lu", max_freq);

	वापस sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_MAX_FREQ,
					     value, म_माप(value));
पूर्ण

पूर्णांक cpufreq_modअगरy_policy_governor(अचिन्हित पूर्णांक cpu, अक्षर *governor)
अणु
	अक्षर new_gov[SYSFS_PATH_MAX];

	अगर ((!governor) || (म_माप(governor) > 19))
		वापस -EINVAL;

	अगर (verअगरy_gov(new_gov, governor))
		वापस -EINVAL;

	वापस sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_GOVERNOR,
					     new_gov, म_माप(new_gov));
पूर्ण

पूर्णांक cpufreq_set_frequency(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ target_frequency)
अणु
	काष्ठा cpufreq_policy *pol = cpufreq_get_policy(cpu);
	अक्षर userspace_gov[] = "userspace";
	अक्षर freq[SYSFS_PATH_MAX];
	पूर्णांक ret;

	अगर (!pol)
		वापस -ENODEV;

	अगर (म_भेदन(pol->governor, userspace_gov, 9) != 0) अणु
		ret = cpufreq_modअगरy_policy_governor(cpu, userspace_gov);
		अगर (ret) अणु
			cpufreq_put_policy(pol);
			वापस ret;
		पूर्ण
	पूर्ण

	cpufreq_put_policy(pol);

	snम_लिखो(freq, SYSFS_PATH_MAX, "%lu", target_frequency);

	वापस sysfs_cpufreq_ग_लिखो_one_value(cpu, WRITE_SCALING_SET_SPEED,
					     freq, म_माप(freq));
पूर्ण

काष्ठा cpufreq_stats *cpufreq_get_stats(अचिन्हित पूर्णांक cpu,
					अचिन्हित दीर्घ दीर्घ *total_समय)
अणु
	काष्ठा cpufreq_stats *first = शून्य;
	काष्ठा cpufreq_stats *current = शून्य;
	अक्षर one_value[SYSFS_PATH_MAX];
	अक्षर linebuf[MAX_LINE_LEN];
	अचिन्हित पूर्णांक pos, i;
	अचिन्हित पूर्णांक len;

	len = sysfs_cpufreq_पढ़ो_file(cpu, "stats/time_in_state",
				linebuf, माप(linebuf));
	अगर (len == 0)
		वापस शून्य;

	*total_समय = 0;
	pos = 0;
	क्रम (i = 0; i < len; i++) अणु
		अगर (i == म_माप(linebuf) || linebuf[i] == '\n')	अणु
			अगर (i - pos < 2)
				जारी;
			अगर ((i - pos) >= SYSFS_PATH_MAX)
				जाओ error_out;
			अगर (current) अणु
				current->next = दो_स्मृति(माप(*current));
				अगर (!current->next)
					जाओ error_out;
				current = current->next;
			पूर्ण अन्यथा अणु
				first = दो_स्मृति(माप(*first));
				अगर (!first)
					वापस शून्य;
				current = first;
			पूर्ण
			current->first = first;
			current->next = शून्य;

			स_नकल(one_value, linebuf + pos, i - pos);
			one_value[i - pos] = '\0';
			अगर (माला_पूछो(one_value, "%lu %llu",
					&current->frequency,
					&current->समय_in_state) != 2)
				जाओ error_out;

			*total_समय = *total_समय + current->समय_in_state;
			pos = i + 1;
		पूर्ण
	पूर्ण

	वापस first;

 error_out:
	जबतक (first) अणु
		current = first->next;
		मुक्त(first);
		first = current;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम cpufreq_put_stats(काष्ठा cpufreq_stats *any)
अणु
	काष्ठा cpufreq_stats *पंचांगp, *next;

	अगर (!any)
		वापस;

	पंचांगp = any->first;
	जबतक (पंचांगp) अणु
		next = पंचांगp->next;
		मुक्त(पंचांगp);
		पंचांगp = next;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ cpufreq_get_transitions(अचिन्हित पूर्णांक cpu)
अणु
	वापस sysfs_cpufreq_get_one_value(cpu, STATS_NUM_TRANSITIONS);
पूर्ण
