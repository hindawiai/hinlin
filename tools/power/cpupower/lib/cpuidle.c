<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2004-2009  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 *  (C) 2011       Thomas Renninger <trenn@novell.com> Novell Inc.
 */

#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

#समावेश "cpuidle.h"
#समावेश "cpupower_intern.h"

/*
 * helper function to check whether a file under "../cpuX/cpuidle/stateX/" dir
 * exists.
 * For example the functionality to disable c-states was पूर्णांकroduced in later
 * kernel versions, this function can be used to explicitly check क्रम this
 * feature.
 *
 * वापसs 1 अगर the file exists, 0 otherwise.
 */
अटल
अचिन्हित पूर्णांक cpuidle_state_file_exists(अचिन्हित पूर्णांक cpu,
				       अचिन्हित पूर्णांक idlestate,
				       स्थिर अक्षर *fname)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	काष्ठा stat statbuf;


	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/cpuidle/state%u/%s",
		 cpu, idlestate, fname);
	अगर (stat(path, &statbuf) != 0)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * helper function to पढ़ो file from /sys पूर्णांकo given buffer
 * fname is a relative path under "cpuX/cpuidle/stateX/" dir
 * cstates starting with 0, C0 is not counted as cstate.
 * This means अगर you want C1 info, pass 0 as idlestate param
 */
अटल
अचिन्हित पूर्णांक cpuidle_state_पढ़ो_file(अचिन्हित पूर्णांक cpu,
					    अचिन्हित पूर्णांक idlestate,
					    स्थिर अक्षर *fname, अक्षर *buf,
					    माप_प्रकार buflen)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	पूर्णांक fd;
	sमाप_प्रकार numपढ़ो;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/cpuidle/state%u/%s",
		 cpu, idlestate, fname);

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस 0;

	numपढ़ो = पढ़ो(fd, buf, buflen - 1);
	अगर (numपढ़ो < 1) अणु
		बंद(fd);
		वापस 0;
	पूर्ण

	buf[numपढ़ो] = '\0';
	बंद(fd);

	वापस (अचिन्हित पूर्णांक) numपढ़ो;
पूर्ण

/*
 * helper function to ग_लिखो a new value to a /sys file
 * fname is a relative path under "../cpuX/cpuidle/cstateY/" dir
 *
 * Returns the number of bytes written or 0 on error
 */
अटल
अचिन्हित पूर्णांक cpuidle_state_ग_लिखो_file(अचिन्हित पूर्णांक cpu,
				      अचिन्हित पूर्णांक idlestate,
				      स्थिर अक्षर *fname,
				      स्थिर अक्षर *value, माप_प्रकार len)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	पूर्णांक fd;
	sमाप_प्रकार numग_लिखो;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/cpuidle/state%u/%s",
		 cpu, idlestate, fname);

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

क्रमागत idlestate_value अणु
	IDLESTATE_USAGE,
	IDLESTATE_POWER,
	IDLESTATE_LATENCY,
	IDLESTATE_TIME,
	IDLESTATE_DISABLE,
	MAX_IDLESTATE_VALUE_खाताS
पूर्ण;

अटल स्थिर अक्षर *idlestate_value_files[MAX_IDLESTATE_VALUE_खाताS] = अणु
	[IDLESTATE_USAGE] = "usage",
	[IDLESTATE_POWER] = "power",
	[IDLESTATE_LATENCY] = "latency",
	[IDLESTATE_TIME]  = "time",
	[IDLESTATE_DISABLE]  = "disable",
पूर्ण;

अटल
अचिन्हित दीर्घ दीर्घ cpuidle_state_get_one_value(अचिन्हित पूर्णांक cpu,
					       अचिन्हित पूर्णांक idlestate,
					       क्रमागत idlestate_value which)
अणु
	अचिन्हित दीर्घ दीर्घ value;
	अचिन्हित पूर्णांक len;
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर *endp;

	अगर (which >= MAX_IDLESTATE_VALUE_खाताS)
		वापस 0;

	len = cpuidle_state_पढ़ो_file(cpu, idlestate,
				      idlestate_value_files[which],
				      linebuf, माप(linebuf));
	अगर (len == 0)
		वापस 0;

	value = म_से_अदीर्घl(linebuf, &endp, 0);

	अगर (endp == linebuf || त्रुटि_सं == दुस्फल)
		वापस 0;

	वापस value;
पूर्ण

/* पढ़ो access to files which contain one string */

क्रमागत idlestate_string अणु
	IDLESTATE_DESC,
	IDLESTATE_NAME,
	MAX_IDLESTATE_STRING_खाताS
पूर्ण;

अटल स्थिर अक्षर *idlestate_string_files[MAX_IDLESTATE_STRING_खाताS] = अणु
	[IDLESTATE_DESC] = "desc",
	[IDLESTATE_NAME] = "name",
पूर्ण;


अटल अक्षर *cpuidle_state_get_one_string(अचिन्हित पूर्णांक cpu,
					अचिन्हित पूर्णांक idlestate,
					क्रमागत idlestate_string which)
अणु
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर *result;
	अचिन्हित पूर्णांक len;

	अगर (which >= MAX_IDLESTATE_STRING_खाताS)
		वापस शून्य;

	len = cpuidle_state_पढ़ो_file(cpu, idlestate,
				      idlestate_string_files[which],
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

/*
 * Returns:
 *    1  अगर disabled
 *    0  अगर enabled
 *    -1 अगर idlestate is not available
 *    -2 अगर disabling is not supported by the kernel
 */
पूर्णांक cpuidle_is_state_disabled(अचिन्हित पूर्णांक cpu,
				अचिन्हित पूर्णांक idlestate)
अणु
	अगर (cpuidle_state_count(cpu) <= idlestate)
		वापस -1;

	अगर (!cpuidle_state_file_exists(cpu, idlestate,
				 idlestate_value_files[IDLESTATE_DISABLE]))
		वापस -2;
	वापस cpuidle_state_get_one_value(cpu, idlestate, IDLESTATE_DISABLE);
पूर्ण

/*
 * Pass 1 as last argument to disable or 0 to enable the state
 * Returns:
 *    0  on success
 *    negative values on error, क्रम example:
 *      -1 अगर idlestate is not available
 *      -2 अगर disabling is not supported by the kernel
 *      -3 No ग_लिखो access to disable/enable C-states
 */
पूर्णांक cpuidle_state_disable(अचिन्हित पूर्णांक cpu,
			    अचिन्हित पूर्णांक idlestate,
			    अचिन्हित पूर्णांक disable)
अणु
	अक्षर value[SYSFS_PATH_MAX];
	पूर्णांक bytes_written;

	अगर (cpuidle_state_count(cpu) <= idlestate)
		वापस -1;

	अगर (!cpuidle_state_file_exists(cpu, idlestate,
				 idlestate_value_files[IDLESTATE_DISABLE]))
		वापस -2;

	snम_लिखो(value, SYSFS_PATH_MAX, "%u", disable);

	bytes_written = cpuidle_state_ग_लिखो_file(cpu, idlestate, "disable",
						   value, माप(disable));
	अगर (bytes_written)
		वापस 0;
	वापस -3;
पूर्ण

अचिन्हित दीर्घ cpuidle_state_latency(अचिन्हित पूर्णांक cpu,
					  अचिन्हित पूर्णांक idlestate)
अणु
	वापस cpuidle_state_get_one_value(cpu, idlestate, IDLESTATE_LATENCY);
पूर्ण

अचिन्हित दीर्घ cpuidle_state_usage(अचिन्हित पूर्णांक cpu,
					अचिन्हित पूर्णांक idlestate)
अणु
	वापस cpuidle_state_get_one_value(cpu, idlestate, IDLESTATE_USAGE);
पूर्ण

अचिन्हित दीर्घ दीर्घ cpuidle_state_समय(अचिन्हित पूर्णांक cpu,
					अचिन्हित पूर्णांक idlestate)
अणु
	वापस cpuidle_state_get_one_value(cpu, idlestate, IDLESTATE_TIME);
पूर्ण

अक्षर *cpuidle_state_name(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक idlestate)
अणु
	वापस cpuidle_state_get_one_string(cpu, idlestate, IDLESTATE_NAME);
पूर्ण

अक्षर *cpuidle_state_desc(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक idlestate)
अणु
	वापस cpuidle_state_get_one_string(cpu, idlestate, IDLESTATE_DESC);
पूर्ण

/*
 * Returns number of supported C-states of CPU core cpu
 * Negativ in error हाल
 * Zero अगर cpuidle करोes not export any C-states
 */
अचिन्हित पूर्णांक cpuidle_state_count(अचिन्हित पूर्णांक cpu)
अणु
	अक्षर file[SYSFS_PATH_MAX];
	काष्ठा stat statbuf;
	पूर्णांक idlestates = 1;


	snम_लिखो(file, SYSFS_PATH_MAX, PATH_TO_CPU "cpuidle");
	अगर (stat(file, &statbuf) != 0 || !S_ISसूची(statbuf.st_mode))
		वापस 0;

	snम_लिखो(file, SYSFS_PATH_MAX, PATH_TO_CPU "cpu%u/cpuidle/state0", cpu);
	अगर (stat(file, &statbuf) != 0 || !S_ISसूची(statbuf.st_mode))
		वापस 0;

	जबतक (stat(file, &statbuf) == 0 && S_ISसूची(statbuf.st_mode)) अणु
		snम_लिखो(file, SYSFS_PATH_MAX, PATH_TO_CPU
			 "cpu%u/cpuidle/state%d", cpu, idlestates);
		idlestates++;
	पूर्ण
	idlestates--;
	वापस idlestates;
पूर्ण

/* CPUidle general /sys/devices/प्रणाली/cpu/cpuidle/ sysfs access ********/

/*
 * helper function to पढ़ो file from /sys पूर्णांकo given buffer
 * fname is a relative path under "cpu/cpuidle/" dir
 */
अटल अचिन्हित पूर्णांक sysfs_cpuidle_पढ़ो_file(स्थिर अक्षर *fname, अक्षर *buf,
					    माप_प्रकार buflen)
अणु
	अक्षर path[SYSFS_PATH_MAX];

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpuidle/%s", fname);

	वापस cpuघातer_पढ़ो_sysfs(path, buf, buflen);
पूर्ण



/* पढ़ो access to files which contain one string */

क्रमागत cpuidle_string अणु
	CPUIDLE_GOVERNOR,
	CPUIDLE_GOVERNOR_RO,
	CPUIDLE_DRIVER,
	MAX_CPUIDLE_STRING_खाताS
पूर्ण;

अटल स्थिर अक्षर *cpuidle_string_files[MAX_CPUIDLE_STRING_खाताS] = अणु
	[CPUIDLE_GOVERNOR]	= "current_governor",
	[CPUIDLE_GOVERNOR_RO]	= "current_governor_ro",
	[CPUIDLE_DRIVER]	= "current_driver",
पूर्ण;


अटल अक्षर *sysfs_cpuidle_get_one_string(क्रमागत cpuidle_string which)
अणु
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर *result;
	अचिन्हित पूर्णांक len;

	अगर (which >= MAX_CPUIDLE_STRING_खाताS)
		वापस शून्य;

	len = sysfs_cpuidle_पढ़ो_file(cpuidle_string_files[which],
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

अक्षर *cpuidle_get_governor(व्योम)
अणु
	अक्षर *पंचांगp = sysfs_cpuidle_get_one_string(CPUIDLE_GOVERNOR_RO);
	अगर (!पंचांगp)
		वापस sysfs_cpuidle_get_one_string(CPUIDLE_GOVERNOR);
	अन्यथा
		वापस पंचांगp;
पूर्ण

अक्षर *cpuidle_get_driver(व्योम)
अणु
	वापस sysfs_cpuidle_get_one_string(CPUIDLE_DRIVER);
पूर्ण
/* CPUidle idlestate specअगरic /sys/devices/प्रणाली/cpu/cpuX/cpuidle/ access */
