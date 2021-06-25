<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/unistd.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/रुको.h>
#समावेश "ptrace.h"

अक्षर data[16];

/* Overlapping address range */
अस्थिर __u64 *ptrace_data1 = (__u64 *)&data[0];
अस्थिर __u64 *perf_data1 = (__u64 *)&data[4];

/* Non-overlapping address range */
अस्थिर __u64 *ptrace_data2 = (__u64 *)&data[0];
अस्थिर __u64 *perf_data2 = (__u64 *)&data[8];

अटल अचिन्हित दीर्घ pid_max_addr(व्योम)
अणु
	खाता *fp;
	अक्षर *line, *c;
	अक्षर addr[100];
	माप_प्रकार len = 0;

	fp = ख_खोलो("/proc/kallsyms", "r");
	अगर (!fp) अणु
		म_लिखो("Failed to read /proc/kallsyms. Exiting..\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	जबतक (getline(&line, &len, fp) != -1) अणु
		अगर (!म_माला(line, "pid_max") || म_माला(line, "pid_max_max") ||
		    म_माला(line, "pid_max_min"))
			जारी;

		म_नकलन(addr, line, len < 100 ? len : 100);
		c = म_अक्षर(addr, ' ');
		*c = '\0';
		वापस म_से_अदीर्घ(addr, &c, 16);
	पूर्ण
	ख_बंद(fp);
	म_लिखो("Could not find pix_max. Exiting..\n");
	निकास(निकास_त्रुटि);
	वापस -1;
पूर्ण

अटल व्योम perf_user_event_attr_set(काष्ठा perf_event_attr *attr, __u64 addr, __u64 len)
अणु
	स_रखो(attr, 0, माप(काष्ठा perf_event_attr));
	attr->type           = PERF_TYPE_BREAKPOINT;
	attr->size           = माप(काष्ठा perf_event_attr);
	attr->bp_type        = HW_BREAKPOINT_R;
	attr->bp_addr        = addr;
	attr->bp_len         = len;
	attr->exclude_kernel = 1;
	attr->exclude_hv     = 1;
पूर्ण

अटल व्योम perf_kernel_event_attr_set(काष्ठा perf_event_attr *attr)
अणु
	स_रखो(attr, 0, माप(काष्ठा perf_event_attr));
	attr->type           = PERF_TYPE_BREAKPOINT;
	attr->size           = माप(काष्ठा perf_event_attr);
	attr->bp_type        = HW_BREAKPOINT_R;
	attr->bp_addr        = pid_max_addr();
	attr->bp_len         = माप(अचिन्हित दीर्घ);
	attr->exclude_user   = 1;
	attr->exclude_hv     = 1;
पूर्ण

अटल पूर्णांक perf_cpu_event_खोलो(पूर्णांक cpu, __u64 addr, __u64 len)
अणु
	काष्ठा perf_event_attr attr;

	perf_user_event_attr_set(&attr, addr, len);
	वापस syscall(__NR_perf_event_खोलो, &attr, -1, cpu, -1, 0);
पूर्ण

अटल पूर्णांक perf_thपढ़ो_event_खोलो(pid_t child_pid, __u64 addr, __u64 len)
अणु
	काष्ठा perf_event_attr attr;

	perf_user_event_attr_set(&attr, addr, len);
	वापस syscall(__NR_perf_event_खोलो, &attr, child_pid, -1, -1, 0);
पूर्ण

अटल पूर्णांक perf_thपढ़ो_cpu_event_खोलो(pid_t child_pid, पूर्णांक cpu, __u64 addr, __u64 len)
अणु
	काष्ठा perf_event_attr attr;

	perf_user_event_attr_set(&attr, addr, len);
	वापस syscall(__NR_perf_event_खोलो, &attr, child_pid, cpu, -1, 0);
पूर्ण

अटल पूर्णांक perf_thपढ़ो_kernel_event_खोलो(pid_t child_pid)
अणु
	काष्ठा perf_event_attr attr;

	perf_kernel_event_attr_set(&attr);
	वापस syscall(__NR_perf_event_खोलो, &attr, child_pid, -1, -1, 0);
पूर्ण

अटल पूर्णांक perf_cpu_kernel_event_खोलो(पूर्णांक cpu)
अणु
	काष्ठा perf_event_attr attr;

	perf_kernel_event_attr_set(&attr);
	वापस syscall(__NR_perf_event_खोलो, &attr, -1, cpu, -1, 0);
पूर्ण

अटल पूर्णांक child(व्योम)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_TRACEME, 0, शून्य, 0);
	अगर (ret) अणु
		म_लिखो("Error: PTRACE_TRACEME failed\n");
		वापस 0;
	पूर्ण
	समाप्त(getpid(), SIGUSR1); /* --> parent (SIGUSR1) */

	वापस 0;
पूर्ण

अटल व्योम ptrace_ppc_hw_अवरोधpoपूर्णांक(काष्ठा ppc_hw_अवरोधpoपूर्णांक *info, पूर्णांक type,
				     __u64 addr, पूर्णांक len)
अणु
	info->version = 1;
	info->trigger_type = type;
	info->condition_mode = PPC_BREAKPOINT_CONDITION_NONE;
	info->addr = addr;
	info->addr2 = addr + len;
	info->condition_value = 0;
	अगर (!len)
		info->addr_mode = PPC_BREAKPOINT_MODE_EXACT;
	अन्यथा
		info->addr_mode = PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE;
पूर्ण

अटल पूर्णांक ptrace_खोलो(pid_t child_pid, __u64 wp_addr, पूर्णांक len)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info;

	ptrace_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_RW, wp_addr, len);
	वापस ptrace(PPC_PTRACE_SETHWDEBUG, child_pid, 0, &info);
पूर्ण

अटल पूर्णांक test1(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by ptrace)
	 *	अगर (existing cpu event by perf)
	 *		अगर (addr range overlaps)
	 *			fail;
	 */

	perf_fd = perf_cpu_event_खोलो(0, (__u64)perf_data1, माप(*perf_data1));
	अगर (perf_fd < 0)
		वापस -1;

	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd > 0 || त्रुटि_सं != ENOSPC)
		ret = -1;

	बंद(perf_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test2(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by ptrace)
	 *	अगर (existing cpu event by perf)
	 *		अगर (addr range करोes not overlaps)
	 *			allow;
	 */

	perf_fd = perf_cpu_event_खोलो(0, (__u64)perf_data2, माप(*perf_data2));
	अगर (perf_fd < 0)
		वापस -1;

	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data2, माप(*ptrace_data2));
	अगर (ptrace_fd < 0) अणु
		ret = -1;
		जाओ perf_बंद;
	पूर्ण
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);

perf_बंद:
	बंद(perf_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test3(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by ptrace)
	 *	अगर (existing thपढ़ो event by perf on the same thपढ़ो)
	 *		अगर (addr range overlaps)
	 *			fail;
	 */
	perf_fd = perf_thपढ़ो_event_खोलो(child_pid, (__u64)perf_data1,
					 माप(*perf_data1));
	अगर (perf_fd < 0)
		वापस -1;

	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd > 0 || त्रुटि_सं != ENOSPC)
		ret = -1;

	बंद(perf_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test4(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by ptrace)
	 *	अगर (existing thपढ़ो event by perf on the same thपढ़ो)
	 *		अगर (addr range करोes not overlaps)
	 *			fail;
	 */
	perf_fd = perf_thपढ़ो_event_खोलो(child_pid, (__u64)perf_data2,
					 माप(*perf_data2));
	अगर (perf_fd < 0)
		वापस -1;

	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data2, माप(*ptrace_data2));
	अगर (ptrace_fd < 0) अणु
		ret = -1;
		जाओ perf_बंद;
	पूर्ण
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);

perf_बंद:
	बंद(perf_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test5(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक cpid;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by ptrace)
	 *	अगर (existing thपढ़ो event by perf on the dअगरferent thपढ़ो)
	 *		allow;
	 */
	cpid = विभाजन();
	अगर (!cpid) अणु
		/* Temporary Child */
		छोड़ो();
		निकास(निकास_सफल);
	पूर्ण

	perf_fd = perf_thपढ़ो_event_खोलो(cpid, (__u64)perf_data1, माप(*perf_data1));
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ समाप्त_child;
	पूर्ण

	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd < 0) अणु
		ret = -1;
		जाओ perf_बंद;
	पूर्ण

	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
perf_बंद:
	बंद(perf_fd);
समाप्त_child:
	समाप्त(cpid, संक_विघ्न);
	वापस ret;
पूर्ण

अटल पूर्णांक test6(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो kernel event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the same thपढ़ो)
	 *		allow;
	 * -- OR --
	 * अगर (new per cpu kernel event by perf)
	 *	अगर (existing thपढ़ो event by ptrace)
	 *		allow;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd < 0)
		वापस -1;

	perf_fd = perf_thपढ़ो_kernel_event_खोलो(child_pid);
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ ptrace_बंद;
	पूर्ण
	बंद(perf_fd);

	perf_fd = perf_cpu_kernel_event_खोलो(0);
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ ptrace_बंद;
	पूर्ण
	बंद(perf_fd);

ptrace_बंद:
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test7(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the same thपढ़ो)
	 *		अगर (addr range overlaps)
	 *			fail;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd < 0)
		वापस -1;

	perf_fd = perf_thपढ़ो_event_खोलो(child_pid, (__u64)perf_data1,
					 माप(*perf_data1));
	अगर (perf_fd > 0 || त्रुटि_सं != ENOSPC)
		ret = -1;

	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test8(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the same thपढ़ो)
	 *		अगर (addr range करोes not overlaps)
	 *			allow;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data2, माप(*ptrace_data2));
	अगर (ptrace_fd < 0)
		वापस -1;

	perf_fd = perf_thपढ़ो_event_खोलो(child_pid, (__u64)perf_data2,
					 माप(*perf_data2));
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ ptrace_बंद;
	पूर्ण
	बंद(perf_fd);

ptrace_बंद:
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test9(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक cpid;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the other thपढ़ो)
	 *		allow;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd < 0)
		वापस -1;

	cpid = विभाजन();
	अगर (!cpid) अणु
		/* Temporary Child */
		छोड़ो();
		निकास(निकास_सफल);
	पूर्ण

	perf_fd = perf_thपढ़ो_event_खोलो(cpid, (__u64)perf_data1, माप(*perf_data1));
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ समाप्त_child;
	पूर्ण
	बंद(perf_fd);

समाप्त_child:
	समाप्त(cpid, संक_विघ्न);
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test10(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per cpu event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the same thपढ़ो)
	 *		अगर (addr range overlaps)
	 *			fail;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd < 0)
		वापस -1;

	perf_fd = perf_cpu_event_खोलो(0, (__u64)perf_data1, माप(*perf_data1));
	अगर (perf_fd > 0 || त्रुटि_सं != ENOSPC)
		ret = -1;

	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test11(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per cpu event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the same thपढ़ो)
	 *		अगर (addr range करोes not overlap)
	 *			allow;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data2, माप(*ptrace_data2));
	अगर (ptrace_fd < 0)
		वापस -1;

	perf_fd = perf_cpu_event_खोलो(0, (__u64)perf_data2, माप(*perf_data2));
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ ptrace_बंद;
	पूर्ण
	बंद(perf_fd);

ptrace_बंद:
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test12(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो and per cpu event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the same thपढ़ो)
	 *		अगर (addr range overlaps)
	 *			fail;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd < 0)
		वापस -1;

	perf_fd = perf_thपढ़ो_cpu_event_खोलो(child_pid, 0, (__u64)perf_data1, माप(*perf_data1));
	अगर (perf_fd > 0 || त्रुटि_सं != ENOSPC)
		ret = -1;

	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test13(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो and per cpu event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the same thपढ़ो)
	 *		अगर (addr range करोes not overlap)
	 *			allow;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data2, माप(*ptrace_data2));
	अगर (ptrace_fd < 0)
		वापस -1;

	perf_fd = perf_thपढ़ो_cpu_event_खोलो(child_pid, 0, (__u64)perf_data2, माप(*perf_data2));
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ ptrace_बंद;
	पूर्ण
	बंद(perf_fd);

ptrace_बंद:
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक test14(pid_t child_pid)
अणु
	पूर्णांक perf_fd;
	पूर्णांक ptrace_fd;
	पूर्णांक cpid;
	पूर्णांक ret = 0;

	/* Test:
	 * अगर (new per thपढ़ो and per cpu event by perf)
	 *	अगर (existing thपढ़ो event by ptrace on the other thपढ़ो)
	 *		allow;
	 */
	ptrace_fd = ptrace_खोलो(child_pid, (__u64)ptrace_data1, माप(*ptrace_data1));
	अगर (ptrace_fd < 0)
		वापस -1;

	cpid = विभाजन();
	अगर (!cpid) अणु
		/* Temporary Child */
		छोड़ो();
		निकास(निकास_सफल);
	पूर्ण

	perf_fd = perf_thपढ़ो_cpu_event_खोलो(cpid, 0, (__u64)perf_data1,
					     माप(*perf_data1));
	अगर (perf_fd < 0) अणु
		ret = -1;
		जाओ समाप्त_child;
	पूर्ण
	बंद(perf_fd);

समाप्त_child:
	समाप्त(cpid, संक_विघ्न);
	ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, ptrace_fd);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_test(स्थिर अक्षर *msg, पूर्णांक (*fun)(pid_t arg), pid_t arg)
अणु
	पूर्णांक ret;

	ret = fun(arg);
	अगर (ret)
		म_लिखो("%s: Error\n", msg);
	अन्यथा
		म_लिखो("%s: Ok\n", msg);
	वापस ret;
पूर्ण

अक्षर *desc[14] = अणु
	"perf cpu event -> ptrace thread event (Overlapping)",
	"perf cpu event -> ptrace thread event (Non-overlapping)",
	"perf thread event -> ptrace same thread event (Overlapping)",
	"perf thread event -> ptrace same thread event (Non-overlapping)",
	"perf thread event -> ptrace other thread event",
	"ptrace thread event -> perf kernel event",
	"ptrace thread event -> perf same thread event (Overlapping)",
	"ptrace thread event -> perf same thread event (Non-overlapping)",
	"ptrace thread event -> perf other thread event",
	"ptrace thread event -> perf cpu event (Overlapping)",
	"ptrace thread event -> perf cpu event (Non-overlapping)",
	"ptrace thread event -> perf same thread & cpu event (Overlapping)",
	"ptrace thread event -> perf same thread & cpu event (Non-overlapping)",
	"ptrace thread event -> perf other thread & cpu event",
पूर्ण;

अटल पूर्णांक test(pid_t child_pid)
अणु
	पूर्णांक ret = TEST_PASS;

	ret |= करो_test(desc[0], test1, child_pid);
	ret |= करो_test(desc[1], test2, child_pid);
	ret |= करो_test(desc[2], test3, child_pid);
	ret |= करो_test(desc[3], test4, child_pid);
	ret |= करो_test(desc[4], test5, child_pid);
	ret |= करो_test(desc[5], test6, child_pid);
	ret |= करो_test(desc[6], test7, child_pid);
	ret |= करो_test(desc[7], test8, child_pid);
	ret |= करो_test(desc[8], test9, child_pid);
	ret |= करो_test(desc[9], test10, child_pid);
	ret |= करो_test(desc[10], test11, child_pid);
	ret |= करो_test(desc[11], test12, child_pid);
	ret |= करो_test(desc[12], test13, child_pid);
	ret |= करो_test(desc[13], test14, child_pid);

	वापस ret;
पूर्ण

अटल व्योम get_dbginfo(pid_t child_pid, काष्ठा ppc_debug_info *dbginfo)
अणु
	अगर (ptrace(PPC_PTRACE_GETHWDBGINFO, child_pid, शून्य, dbginfo)) अणु
		लिखो_त्रुटि("Can't get breakpoint info");
		निकास(-1);
	पूर्ण
पूर्ण

अटल पूर्णांक ptrace_perf_hwअवरोध(व्योम)
अणु
	पूर्णांक ret;
	pid_t child_pid;
	काष्ठा ppc_debug_info dbginfo;

	child_pid = विभाजन();
	अगर (!child_pid)
		वापस child();

	/* parent */
	रुको(शून्य); /* <-- child (SIGUSR1) */

	get_dbginfo(child_pid, &dbginfo);
	SKIP_IF(dbginfo.num_data_bps <= 1);

	ret = perf_cpu_event_खोलो(0, (__u64)perf_data1, माप(*perf_data1));
	SKIP_IF(ret < 0);
	बंद(ret);

	ret = test(child_pid);

	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(ptrace_perf_hwअवरोध, "ptrace-perf-hwbreak");
पूर्ण
