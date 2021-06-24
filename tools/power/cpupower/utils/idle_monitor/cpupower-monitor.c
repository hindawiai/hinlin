<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc.
 *
 *  Output क्रमmat inspired by Len Brown's <lenb@kernel.org> turbostat tool.
 */


#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <libgen.h>

#समावेश "idle_monitor/cpupower-monitor.h"
#समावेश "idle_monitor/idle_monitors.h"
#समावेश "helpers/helpers.h"

/* Define poपूर्णांकers to all monitors.  */
#घोषणा DEF(x) & x ## _monitor ,
काष्ठा cpuidle_monitor *all_monitors[] = अणु
#समावेश "idle_monitors.def"
0
पूर्ण;

पूर्णांक cpu_count;

अटल काष्ठा cpuidle_monitor *monitors[MONITORS_MAX];
अटल अचिन्हित पूर्णांक avail_monitors;

अटल अक्षर *progname;

क्रमागत operation_mode_e अणु list = 1, show, show_all पूर्ण;
अटल पूर्णांक mode;
अटल पूर्णांक पूर्णांकerval = 1;
अटल अक्षर *show_monitors_param;
अटल काष्ठा cpuघातer_topology cpu_top;
अटल अचिन्हित पूर्णांक wake_cpus;

/* ToDo: Document this in the manpage */
अटल अक्षर range_abbr[RANGE_MAX] = अणु 'T', 'C', 'P', 'M', पूर्ण;

अटल व्योम prपूर्णांक_wrong_arg_निकास(व्योम)
अणु
	म_लिखो(_("invalid or unknown argument\n"));
	निकास(निकास_त्रुटि);
पूर्ण

दीर्घ दीर्घ बारpec_dअगरf_us(काष्ठा बारpec start, काष्ठा बारpec end)
अणु
	काष्ठा बारpec temp;
	अगर ((end.tv_nsec - start.tv_nsec) < 0) अणु
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	पूर्ण अन्यथा अणु
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	पूर्ण
	वापस (temp.tv_sec * 1000000) + (temp.tv_nsec / 1000);
पूर्ण

व्योम prपूर्णांक_n_spaces(पूर्णांक n)
अणु
	पूर्णांक x;
	क्रम (x = 0; x < n; x++)
		म_लिखो(" ");
पूर्ण

/*s is filled with left and right spaces
 *to make its length atleast n+1
 */
पूर्णांक fill_string_with_spaces(अक्षर *s, पूर्णांक n)
अणु
	अक्षर *temp;
	पूर्णांक len = म_माप(s);

	अगर (len >= n)
		वापस -1;

	temp = दो_स्मृति(माप(अक्षर) * (n+1));
	क्रम (; len < n; len++)
		s[len] = ' ';
	s[len] = '\0';
	snम_लिखो(temp, n+1, " %s", s);
	म_नकल(s, temp);
	मुक्त(temp);
	वापस 0;
पूर्ण

#घोषणा MAX_COL_WIDTH 6
व्योम prपूर्णांक_header(पूर्णांक topology_depth)
अणु
	पूर्णांक अचिन्हित mon;
	पूर्णांक state, need_len;
	cstate_t s;
	अक्षर buf[128] = "";

	fill_string_with_spaces(buf, topology_depth * 5 - 1);
	म_लिखो("%s|", buf);

	क्रम (mon = 0; mon < avail_monitors; mon++) अणु
		need_len = monitors[mon]->hw_states_num * (MAX_COL_WIDTH + 1)
			- 1;
		अगर (mon != 0)
			म_लिखो("||");
		प्र_लिखो(buf, "%s", monitors[mon]->name);
		fill_string_with_spaces(buf, need_len);
		म_लिखो("%s", buf);
	पूर्ण
	म_लिखो("\n");

	अगर (topology_depth > 2)
		म_लिखो(" PKG|");
	अगर (topology_depth > 1)
		म_लिखो("CORE|");
	अगर (topology_depth > 0)
		म_लिखो(" CPU|");

	क्रम (mon = 0; mon < avail_monitors; mon++) अणु
		अगर (mon != 0)
			म_लिखो("||");
		क्रम (state = 0; state < monitors[mon]->hw_states_num; state++) अणु
			अगर (state != 0)
				म_लिखो("|");
			s = monitors[mon]->hw_states[state];
			प्र_लिखो(buf, "%s", s.name);
			fill_string_with_spaces(buf, MAX_COL_WIDTH);
			म_लिखो("%s", buf);
		पूर्ण
		म_लिखो(" ");
	पूर्ण
	म_लिखो("\n");
पूर्ण


व्योम prपूर्णांक_results(पूर्णांक topology_depth, पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक mon;
	पूर्णांक state, ret;
	द्विगुन percent;
	अचिन्हित दीर्घ दीर्घ result;
	cstate_t s;

	/* Be careful CPUs may got resorted क्रम pkg value करो not just use cpu */
	अगर (!biपंचांगask_isbitset(cpus_chosen, cpu_top.core_info[cpu].cpu))
		वापस;
	अगर (!cpu_top.core_info[cpu].is_online &&
	    cpu_top.core_info[cpu].pkg == -1)
		वापस;

	अगर (topology_depth > 2)
		म_लिखो("%4d|", cpu_top.core_info[cpu].pkg);
	अगर (topology_depth > 1)
		म_लिखो("%4d|", cpu_top.core_info[cpu].core);
	अगर (topology_depth > 0)
		म_लिखो("%4d|", cpu_top.core_info[cpu].cpu);

	क्रम (mon = 0; mon < avail_monitors; mon++) अणु
		अगर (mon != 0)
			म_लिखो("||");

		क्रम (state = 0; state < monitors[mon]->hw_states_num; state++) अणु
			अगर (state != 0)
				म_लिखो("|");

			s = monitors[mon]->hw_states[state];

			अगर (s.get_count_percent) अणु
				ret = s.get_count_percent(s.id, &percent,
						  cpu_top.core_info[cpu].cpu);
				अगर (ret)
					म_लिखो("******");
				अन्यथा अगर (percent >= 100.0)
					म_लिखो("%6.1f", percent);
				अन्यथा
					म_लिखो("%6.2f", percent);
			पूर्ण अन्यथा अगर (s.get_count) अणु
				ret = s.get_count(s.id, &result,
						  cpu_top.core_info[cpu].cpu);
				अगर (ret)
					म_लिखो("******");
				अन्यथा
					म_लिखो("%6llu", result);
			पूर्ण अन्यथा अणु
				म_लिखो(_("Monitor %s, Counter %s has no count "
					 "function. Implementation error\n"),
				       monitors[mon]->name, s.name);
				निकास(निकास_त्रुटि);
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * The monitor could still provide useful data, क्रम example
	 * AMD HW counters partly sit in PCI config space.
	 * It's up to the monitor plug-in to check .is_online, this one
	 * is just क्रम additional info.
	 */
	अगर (!cpu_top.core_info[cpu].is_online &&
	    cpu_top.core_info[cpu].pkg != -1) अणु
		म_लिखो(_(" *is offline\n"));
		वापस;
	पूर्ण अन्यथा
		म_लिखो("\n");
पूर्ण


/* param: string passed by -m param (The list of monitors to show)
 *
 * Monitors must have been रेजिस्टरed alपढ़ोy, matching monitors
 * are picked out and available monitors array is overridden
 * with matching ones
 *
 * Monitors get sorted in the same order the user passes them
*/

अटल व्योम parse_monitor_param(अक्षर *param)
अणु
	अचिन्हित पूर्णांक num;
	पूर्णांक mon, hits = 0;
	अक्षर *पंचांगp = param, *token;
	काष्ठा cpuidle_monitor *पंचांगp_mons[MONITORS_MAX];


	क्रम (mon = 0; mon < MONITORS_MAX; mon++, पंचांगp = शून्य) अणु
		token = म_मोहर(पंचांगp, ",");
		अगर (token == शून्य)
			अवरोध;
		अगर (म_माप(token) >= MONITOR_NAME_LEN) अणु
			म_लिखो(_("%s: max monitor name length"
				 " (%d) exceeded\n"), token, MONITOR_NAME_LEN);
			जारी;
		पूर्ण

		क्रम (num = 0; num < avail_monitors; num++) अणु
			अगर (!म_भेद(monitors[num]->name, token)) अणु
				dprपूर्णांक("Found requested monitor: %s\n", token);
				पंचांगp_mons[hits] = monitors[num];
				hits++;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (hits == 0) अणु
		म_लिखो(_("No matching monitor found in %s, "
			 "try -l option\n"), param);
		निकास(निकास_त्रुटि);
	पूर्ण
	/* Override detected/रेजिस्टरd monitors array with requested one */
	स_नकल(monitors, पंचांगp_mons,
		माप(काष्ठा cpuidle_monitor *) * MONITORS_MAX);
	avail_monitors = hits;
पूर्ण

व्योम list_monitors(व्योम)
अणु
	अचिन्हित पूर्णांक mon;
	पूर्णांक state;
	cstate_t s;

	क्रम (mon = 0; mon < avail_monitors; mon++) अणु
		म_लिखो(_("Monitor \"%s\" (%d states) - Might overflow after %u "
			 "s\n"),
			monitors[mon]->name, monitors[mon]->hw_states_num,
			monitors[mon]->overflow_s);

		क्रम (state = 0; state < monitors[mon]->hw_states_num; state++) अणु
			s = monitors[mon]->hw_states[state];
			/*
			 * ToDo show more state capabilities:
			 * percent, समय (granlarity)
			 */
			म_लिखो("%s\t[%c] -> %s\n", s.name, range_abbr[s.range],
			       gettext(s.desc));
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक विभाजन_it(अक्षर **argv)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक num;
	अचिन्हित दीर्घ दीर्घ समयdअगरf;
	pid_t child_pid;
	काष्ठा बारpec start, end;

	child_pid = विभाजन();
	घड़ी_समय_लो(CLOCK_REALTIME, &start);

	क्रम (num = 0; num < avail_monitors; num++)
		monitors[num]->start();

	अगर (!child_pid) अणु
		/* child */
		execvp(argv[0], argv);
	पूर्ण अन्यथा अणु
		/* parent */
		अगर (child_pid == -1) अणु
			लिखो_त्रुटि("fork");
			निकास(1);
		पूर्ण

		संकेत(संक_विघ्न, संक_छोड़ो);
		संकेत(SIGQUIT, संक_छोड़ो);
		अगर (रुकोpid(child_pid, &status, 0) == -1) अणु
			लिखो_त्रुटि("wait");
			निकास(1);
		पूर्ण
	पूर्ण
	घड़ी_समय_लो(CLOCK_REALTIME, &end);
	क्रम (num = 0; num < avail_monitors; num++)
		monitors[num]->stop();

	समयdअगरf = बारpec_dअगरf_us(start, end);
	अगर (WIFEXITED(status))
		म_लिखो(_("%s took %.5f seconds and exited with status %d\n"),
			argv[0], समयdअगरf / (1000.0 * 1000),
			WEXITSTATUS(status));
	वापस 0;
पूर्ण

पूर्णांक करो_पूर्णांकerval_measure(पूर्णांक i)
अणु
	अचिन्हित पूर्णांक num;
	पूर्णांक cpu;

	अगर (wake_cpus)
		क्रम (cpu = 0; cpu < cpu_count; cpu++)
			bind_cpu(cpu);

	क्रम (num = 0; num < avail_monitors; num++) अणु
		dprपूर्णांक("HW C-state residency monitor: %s - States: %d\n",
		       monitors[num]->name, monitors[num]->hw_states_num);
		monitors[num]->start();
	पूर्ण

	sleep(i);

	अगर (wake_cpus)
		क्रम (cpu = 0; cpu < cpu_count; cpu++)
			bind_cpu(cpu);

	क्रम (num = 0; num < avail_monitors; num++)
		monitors[num]->stop();


	वापस 0;
पूर्ण

अटल व्योम cmdline(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक opt;
	progname = basename(argv[0]);

	जबतक ((opt = getopt(argc, argv, "+lci:m:")) != -1) अणु
		चयन (opt) अणु
		हाल 'l':
			अगर (mode)
				prपूर्णांक_wrong_arg_निकास();
			mode = list;
			अवरोध;
		हाल 'i':
			/* only allow -i with -m or no option */
			अगर (mode && mode != show)
				prपूर्णांक_wrong_arg_निकास();
			पूर्णांकerval = म_से_प(optarg);
			अवरोध;
		हाल 'm':
			अगर (mode)
				prपूर्णांक_wrong_arg_निकास();
			mode = show;
			show_monitors_param = optarg;
			अवरोध;
		हाल 'c':
			wake_cpus = 1;
			अवरोध;
		शेष:
			prपूर्णांक_wrong_arg_निकास();
		पूर्ण
	पूर्ण
	अगर (!mode)
		mode = show_all;
पूर्ण

पूर्णांक cmd_monitor(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक num;
	काष्ठा cpuidle_monitor *test_mon;
	पूर्णांक cpu;

	cmdline(argc, argv);
	cpu_count = get_cpu_topology(&cpu_top);
	अगर (cpu_count < 0) अणु
		म_लिखो(_("Cannot read number of available processors\n"));
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (!cpu_top.core_info[0].is_online)
		म_लिखो("WARNING: at least one cpu is offline\n");

	/* Default is: monitor all CPUs */
	अगर (biपंचांगask_isallclear(cpus_chosen))
		biपंचांगask_setall(cpus_chosen);

	dprपूर्णांक("System has up to %d CPU cores\n", cpu_count);

	क्रम (num = 0; all_monitors[num]; num++) अणु
		dprपूर्णांक("Try to register: %s\n", all_monitors[num]->name);
		test_mon = all_monitors[num]->करो_रेजिस्टर();
		अगर (test_mon) अणु
			अगर (test_mon->flags.needs_root && !run_as_root) अणु
				ख_लिखो(मानक_त्रुटि, _("Available monitor %s needs "
					  "root access\n"), test_mon->name);
				जारी;
			पूर्ण
			monitors[avail_monitors] = test_mon;
			dprपूर्णांक("%s registered\n", all_monitors[num]->name);
			avail_monitors++;
		पूर्ण
	पूर्ण

	अगर (avail_monitors == 0) अणु
		म_लिखो(_("No HW Cstate monitors found\n"));
		वापस 1;
	पूर्ण

	अगर (mode == list) अणु
		list_monitors();
		निकास(निकास_सफल);
	पूर्ण

	अगर (mode == show)
		parse_monitor_param(show_monitors_param);

	dprपूर्णांक("Packages: %d - Cores: %d - CPUs: %d\n",
	       cpu_top.pkgs, cpu_top.cores, cpu_count);

	/*
	 * अगर any params left, it must be a command to विभाजन
	 */
	अगर (argc - optind)
		विभाजन_it(argv + optind);
	अन्यथा
		करो_पूर्णांकerval_measure(पूर्णांकerval);

	/* ToDo: Topology parsing needs fixing first to करो
	   this more generically */
	अगर (cpu_top.pkgs > 1)
		prपूर्णांक_header(3);
	अन्यथा
		prपूर्णांक_header(1);

	क्रम (cpu = 0; cpu < cpu_count; cpu++) अणु
		अगर (cpu_top.pkgs > 1)
			prपूर्णांक_results(3, cpu);
		अन्यथा
			prपूर्णांक_results(1, cpu);
	पूर्ण

	क्रम (num = 0; num < avail_monitors; num++)
		monitors[num]->unरेजिस्टर();

	cpu_topology_release(cpu_top);
	वापस 0;
पूर्ण
