<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <sys/समय.स>
#समावेश <समय.स>
#समावेश <मानककोष.स>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>
#समावेश <dlfcn.h>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <संकेत.स>
#समावेश <sys/ucontext.h>
#समावेश <त्रुटिसं.स>
#समावेश <err.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <समलाँघ.स>
#समावेश <sys/uपन.स>

#समावेश "helpers.h"

#अगर_घोषित __x86_64__
# define VSYS(x) (x)
#अन्यथा
# define VSYS(x) 0
#पूर्ण_अगर

#अगर_अघोषित SYS_अ_लोpu
# अगरdef __x86_64__
#  define SYS_अ_लोpu 309
# अन्यथा
#  define SYS_अ_लोpu 318
# endअगर
#पूर्ण_अगर

/* max length of lines in /proc/self/maps - anything दीर्घer is skipped here */
#घोषणा MAPS_LINE_LEN 128

अटल व्योम sethandler(पूर्णांक sig, व्योम (*handler)(पूर्णांक, siginfo_t *, व्योम *),
		       पूर्णांक flags)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | flags;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

/* vsyscalls and vDSO */
bool vsyscall_map_r = false, vsyscall_map_x = false;

प्रकार दीर्घ (*gtod_t)(काष्ठा समयval *tv, काष्ठा समयzone *tz);
स्थिर gtod_t vgtod = (gtod_t)VSYS(0xffffffffff600000);
gtod_t vdso_gtod;

प्रकार पूर्णांक (*vसमय_लो_t)(घड़ीid_t, काष्ठा बारpec *);
vसमय_लो_t vdso_समय_लो;

प्रकार दीर्घ (*समय_func_t)(समय_प्रकार *t);
स्थिर समय_func_t vसमय = (समय_func_t)VSYS(0xffffffffff600400);
समय_func_t vdso_समय;

प्रकार दीर्घ (*अ_लोpu_t)(अचिन्हित *, अचिन्हित *, व्योम *);
स्थिर अ_लोpu_t vअ_लोpu = (अ_लोpu_t)VSYS(0xffffffffff600800);
अ_लोpu_t vdso_अ_लोpu;

अटल व्योम init_vdso(व्योम)
अणु
	व्योम *vdso = dlखोलो("linux-vdso.so.1", RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso)
		vdso = dlखोलो("linux-gate.so.1", RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso) अणु
		म_लिखो("[WARN]\tfailed to find vDSO\n");
		वापस;
	पूर्ण

	vdso_gtod = (gtod_t)dlsym(vdso, "__vdso_gettimeofday");
	अगर (!vdso_gtod)
		म_लिखो("[WARN]\tfailed to find gettimeofday in vDSO\n");

	vdso_समय_लो = (vसमय_लो_t)dlsym(vdso, "__vdso_clock_gettime");
	अगर (!vdso_समय_लो)
		म_लिखो("[WARN]\tfailed to find clock_gettime in vDSO\n");

	vdso_समय = (समय_func_t)dlsym(vdso, "__vdso_time");
	अगर (!vdso_समय)
		म_लिखो("[WARN]\tfailed to find time in vDSO\n");

	vdso_अ_लोpu = (अ_लोpu_t)dlsym(vdso, "__vdso_getcpu");
	अगर (!vdso_अ_लोpu) अणु
		/* अ_लोpu() was never wired up in the 32-bit vDSO. */
		म_लिखो("[%s]\tfailed to find getcpu in vDSO\n",
		       माप(दीर्घ) == 8 ? "WARN" : "NOTE");
	पूर्ण
पूर्ण

अटल पूर्णांक init_vsys(व्योम)
अणु
#अगर_घोषित __x86_64__
	पूर्णांक nerrs = 0;
	खाता *maps;
	अक्षर line[MAPS_LINE_LEN];
	bool found = false;

	maps = ख_खोलो("/proc/self/maps", "r");
	अगर (!maps) अणु
		म_लिखो("[WARN]\tCould not open /proc/self/maps -- assuming vsyscall is r-x\n");
		vsyscall_map_r = true;
		वापस 0;
	पूर्ण

	जबतक (ख_माला_लो(line, MAPS_LINE_LEN, maps)) अणु
		अक्षर r, x;
		व्योम *start, *end;
		अक्षर name[MAPS_LINE_LEN];

		/* माला_पूछो() is safe here as म_माप(name) >= म_माप(line) */
		अगर (माला_पूछो(line, "%p-%p %c-%cp %*x %*x:%*x %*u %s",
			   &start, &end, &r, &x, name) != 5)
			जारी;

		अगर (म_भेद(name, "[vsyscall]"))
			जारी;

		म_लिखो("\tvsyscall map: %s", line);

		अगर (start != (व्योम *)0xffffffffff600000 ||
		    end != (व्योम *)0xffffffffff601000) अणु
			म_लिखो("[FAIL]\taddress range is nonsense\n");
			nerrs++;
		पूर्ण

		म_लिखो("\tvsyscall permissions are %c-%c\n", r, x);
		vsyscall_map_r = (r == 'r');
		vsyscall_map_x = (x == 'x');

		found = true;
		अवरोध;
	पूर्ण

	ख_बंद(maps);

	अगर (!found) अणु
		म_लिखो("\tno vsyscall map in /proc/self/maps\n");
		vsyscall_map_r = false;
		vsyscall_map_x = false;
	पूर्ण

	वापस nerrs;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* syscalls */
अटल अंतरभूत दीर्घ sys_gtod(काष्ठा समयval *tv, काष्ठा समयzone *tz)
अणु
	वापस syscall(SYS_समय_लोofday, tv, tz);
पूर्ण

अटल अंतरभूत पूर्णांक sys_घड़ी_समय_लो(घड़ीid_t id, काष्ठा बारpec *ts)
अणु
	वापस syscall(SYS_घड़ी_समय_लो, id, ts);
पूर्ण

अटल अंतरभूत दीर्घ sys_समय(समय_प्रकार *t)
अणु
	वापस syscall(SYS_समय, t);
पूर्ण

अटल अंतरभूत दीर्घ sys_अ_लोpu(अचिन्हित * cpu, अचिन्हित * node,
			      व्योम* cache)
अणु
	वापस syscall(SYS_अ_लोpu, cpu, node, cache);
पूर्ण

अटल लाँघ_बफ jmpbuf;
अटल अस्थिर अचिन्हित दीर्घ segv_err;

अटल व्योम sigsegv(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t *)ctx_व्योम;

	segv_err =  ctx->uc_mcontext.gregs[REG_ERR];
	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

अटल द्विगुन tv_dअगरf(स्थिर काष्ठा समयval *a, स्थिर काष्ठा समयval *b)
अणु
	वापस (द्विगुन)(a->tv_sec - b->tv_sec) +
		(द्विगुन)((पूर्णांक)a->tv_usec - (पूर्णांक)b->tv_usec) * 1e-6;
पूर्ण

अटल पूर्णांक check_gtod(स्थिर काष्ठा समयval *tv_sys1,
		      स्थिर काष्ठा समयval *tv_sys2,
		      स्थिर काष्ठा समयzone *tz_sys,
		      स्थिर अक्षर *which,
		      स्थिर काष्ठा समयval *tv_other,
		      स्थिर काष्ठा समयzone *tz_other)
अणु
	पूर्णांक nerrs = 0;
	द्विगुन d1, d2;

	अगर (tz_other && (tz_sys->tz_minuteswest != tz_other->tz_minuteswest || tz_sys->tz_dstसमय != tz_other->tz_dstसमय)) अणु
		म_लिखो("[FAIL] %s tz mismatch\n", which);
		nerrs++;
	पूर्ण

	d1 = tv_dअगरf(tv_other, tv_sys1);
	d2 = tv_dअगरf(tv_sys2, tv_other); 
	म_लिखो("\t%s time offsets: %lf %lf\n", which, d1, d2);

	अगर (d1 < 0 || d2 < 0) अणु
		म_लिखो("[FAIL]\t%s time was inconsistent with the syscall\n", which);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\t%s gettimeofday()'s timeval was okay\n", which);
	पूर्ण

	वापस nerrs;
पूर्ण

अटल पूर्णांक test_gtod(व्योम)
अणु
	काष्ठा समयval tv_sys1, tv_sys2, tv_vdso, tv_vsys;
	काष्ठा समयzone tz_sys, tz_vdso, tz_vsys;
	दीर्घ ret_vdso = -1;
	दीर्घ ret_vsys = -1;
	पूर्णांक nerrs = 0;

	म_लिखो("[RUN]\ttest gettimeofday()\n");

	अगर (sys_gtod(&tv_sys1, &tz_sys) != 0)
		err(1, "syscall gettimeofday");
	अगर (vdso_gtod)
		ret_vdso = vdso_gtod(&tv_vdso, &tz_vdso);
	अगर (vsyscall_map_x)
		ret_vsys = vgtod(&tv_vsys, &tz_vsys);
	अगर (sys_gtod(&tv_sys2, &tz_sys) != 0)
		err(1, "syscall gettimeofday");

	अगर (vdso_gtod) अणु
		अगर (ret_vdso == 0) अणु
			nerrs += check_gtod(&tv_sys1, &tv_sys2, &tz_sys, "vDSO", &tv_vdso, &tz_vdso);
		पूर्ण अन्यथा अणु
			म_लिखो("[FAIL]\tvDSO gettimeofday() failed: %ld\n", ret_vdso);
			nerrs++;
		पूर्ण
	पूर्ण

	अगर (vsyscall_map_x) अणु
		अगर (ret_vsys == 0) अणु
			nerrs += check_gtod(&tv_sys1, &tv_sys2, &tz_sys, "vsyscall", &tv_vsys, &tz_vsys);
		पूर्ण अन्यथा अणु
			म_लिखो("[FAIL]\tvsys gettimeofday() failed: %ld\n", ret_vsys);
			nerrs++;
		पूर्ण
	पूर्ण

	वापस nerrs;
पूर्ण

अटल पूर्णांक test_समय(व्योम) अणु
	पूर्णांक nerrs = 0;

	म_लिखो("[RUN]\ttest time()\n");
	दीर्घ t_sys1, t_sys2, t_vdso = 0, t_vsys = 0;
	दीर्घ t2_sys1 = -1, t2_sys2 = -1, t2_vdso = -1, t2_vsys = -1;
	t_sys1 = sys_समय(&t2_sys1);
	अगर (vdso_समय)
		t_vdso = vdso_समय(&t2_vdso);
	अगर (vsyscall_map_x)
		t_vsys = vसमय(&t2_vsys);
	t_sys2 = sys_समय(&t2_sys2);
	अगर (t_sys1 < 0 || t_sys1 != t2_sys1 || t_sys2 < 0 || t_sys2 != t2_sys2) अणु
		म_लिखो("[FAIL]\tsyscall failed (ret1:%ld output1:%ld ret2:%ld output2:%ld)\n", t_sys1, t2_sys1, t_sys2, t2_sys2);
		nerrs++;
		वापस nerrs;
	पूर्ण

	अगर (vdso_समय) अणु
		अगर (t_vdso < 0 || t_vdso != t2_vdso) अणु
			म_लिखो("[FAIL]\tvDSO failed (ret:%ld output:%ld)\n", t_vdso, t2_vdso);
			nerrs++;
		पूर्ण अन्यथा अगर (t_vdso < t_sys1 || t_vdso > t_sys2) अणु
			म_लिखो("[FAIL]\tvDSO returned the wrong time (%ld %ld %ld)\n", t_sys1, t_vdso, t_sys2);
			nerrs++;
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\tvDSO time() is okay\n");
		पूर्ण
	पूर्ण

	अगर (vsyscall_map_x) अणु
		अगर (t_vsys < 0 || t_vsys != t2_vsys) अणु
			म_लिखो("[FAIL]\tvsyscall failed (ret:%ld output:%ld)\n", t_vsys, t2_vsys);
			nerrs++;
		पूर्ण अन्यथा अगर (t_vsys < t_sys1 || t_vsys > t_sys2) अणु
			म_लिखो("[FAIL]\tvsyscall returned the wrong time (%ld %ld %ld)\n", t_sys1, t_vsys, t_sys2);
			nerrs++;
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\tvsyscall time() is okay\n");
		पूर्ण
	पूर्ण

	वापस nerrs;
पूर्ण

अटल पूर्णांक test_अ_लोpu(पूर्णांक cpu)
अणु
	पूर्णांक nerrs = 0;
	दीर्घ ret_sys, ret_vdso = -1, ret_vsys = -1;

	म_लिखो("[RUN]\tgetcpu() on CPU %d\n", cpu);

	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0) अणु
		म_लिखो("[SKIP]\tfailed to force CPU %d\n", cpu);
		वापस nerrs;
	पूर्ण

	अचिन्हित cpu_sys, cpu_vdso, cpu_vsys, node_sys, node_vdso, node_vsys;
	अचिन्हित node = 0;
	bool have_node = false;
	ret_sys = sys_अ_लोpu(&cpu_sys, &node_sys, 0);
	अगर (vdso_अ_लोpu)
		ret_vdso = vdso_अ_लोpu(&cpu_vdso, &node_vdso, 0);
	अगर (vsyscall_map_x)
		ret_vsys = vअ_लोpu(&cpu_vsys, &node_vsys, 0);

	अगर (ret_sys == 0) अणु
		अगर (cpu_sys != cpu) अणु
			म_लिखो("[FAIL]\tsyscall reported CPU %hu but should be %d\n", cpu_sys, cpu);
			nerrs++;
		पूर्ण

		have_node = true;
		node = node_sys;
	पूर्ण

	अगर (vdso_अ_लोpu) अणु
		अगर (ret_vdso) अणु
			म_लिखो("[FAIL]\tvDSO getcpu() failed\n");
			nerrs++;
		पूर्ण अन्यथा अणु
			अगर (!have_node) अणु
				have_node = true;
				node = node_vdso;
			पूर्ण

			अगर (cpu_vdso != cpu) अणु
				म_लिखो("[FAIL]\tvDSO reported CPU %hu but should be %d\n", cpu_vdso, cpu);
				nerrs++;
			पूर्ण अन्यथा अणु
				म_लिखो("[OK]\tvDSO reported correct CPU\n");
			पूर्ण

			अगर (node_vdso != node) अणु
				म_लिखो("[FAIL]\tvDSO reported node %hu but should be %hu\n", node_vdso, node);
				nerrs++;
			पूर्ण अन्यथा अणु
				म_लिखो("[OK]\tvDSO reported correct node\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (vsyscall_map_x) अणु
		अगर (ret_vsys) अणु
			म_लिखो("[FAIL]\tvsyscall getcpu() failed\n");
			nerrs++;
		पूर्ण अन्यथा अणु
			अगर (!have_node) अणु
				have_node = true;
				node = node_vsys;
			पूर्ण

			अगर (cpu_vsys != cpu) अणु
				म_लिखो("[FAIL]\tvsyscall reported CPU %hu but should be %d\n", cpu_vsys, cpu);
				nerrs++;
			पूर्ण अन्यथा अणु
				म_लिखो("[OK]\tvsyscall reported correct CPU\n");
			पूर्ण

			अगर (node_vsys != node) अणु
				म_लिखो("[FAIL]\tvsyscall reported node %hu but should be %hu\n", node_vsys, node);
				nerrs++;
			पूर्ण अन्यथा अणु
				म_लिखो("[OK]\tvsyscall reported correct node\n");
			पूर्ण
		पूर्ण
	पूर्ण

	वापस nerrs;
पूर्ण

अटल पूर्णांक test_vsys_r(व्योम)
अणु
#अगर_घोषित __x86_64__
	म_लिखो("[RUN]\tChecking read access to the vsyscall page\n");
	bool can_पढ़ो;
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		*(अस्थिर पूर्णांक *)0xffffffffff600000;
		can_पढ़ो = true;
	पूर्ण अन्यथा अणु
		can_पढ़ो = false;
	पूर्ण

	अगर (can_पढ़ो && !vsyscall_map_r) अणु
		म_लिखो("[FAIL]\tWe have read access, but we shouldn't\n");
		वापस 1;
	पूर्ण अन्यथा अगर (!can_पढ़ो && vsyscall_map_r) अणु
		म_लिखो("[FAIL]\tWe don't have read access, but we should\n");
		वापस 1;
	पूर्ण अन्यथा अगर (can_पढ़ो) अणु
		म_लिखो("[OK]\tWe have read access\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tWe do not have read access: #PF(0x%lx)\n",
		       segv_err);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक test_vsys_x(व्योम)
अणु
#अगर_घोषित __x86_64__
	अगर (vsyscall_map_x) अणु
		/* We alपढ़ोy tested this adequately. */
		वापस 0;
	पूर्ण

	म_लिखो("[RUN]\tMake sure that vsyscalls really page fault\n");

	bool can_exec;
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		vgtod(शून्य, शून्य);
		can_exec = true;
	पूर्ण अन्यथा अणु
		can_exec = false;
	पूर्ण

	अगर (can_exec) अणु
		म_लिखो("[FAIL]\tExecuting the vsyscall did not page fault\n");
		वापस 1;
	पूर्ण अन्यथा अगर (segv_err & (1 << 4)) अणु /* INSTR */
		म_लिखो("[OK]\tExecuting the vsyscall page failed: #PF(0x%lx)\n",
		       segv_err);
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\tExecution failed with the wrong error: #PF(0x%lx)\n",
		       segv_err);
		वापस 1;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * Debuggers expect ptrace() to be able to peek at the vsyscall page.
 * Use process_vm_पढ़ोv() as a proxy क्रम ptrace() to test this.  We
 * want it to work in the vsyscall=emulate हाल and to fail in the
 * vsyscall=xonly हाल.
 *
 * It's worth noting that this ABI is a bit nutty.  write(2) can't
 * पढ़ो from the vsyscall page on any kernel version or mode.  The
 * fact that ptrace() ever worked was a nice courtesy of old kernels,
 * but the code to support it is fairly gross.
 */
अटल पूर्णांक test_process_vm_पढ़ोv(व्योम)
अणु
#अगर_घोषित __x86_64__
	अक्षर buf[4096];
	काष्ठा iovec local, remote;
	पूर्णांक ret;

	म_लिखो("[RUN]\tprocess_vm_readv() from vsyscall page\n");

	local.iov_base = buf;
	local.iov_len = 4096;
	remote.iov_base = (व्योम *)0xffffffffff600000;
	remote.iov_len = 4096;
	ret = process_vm_पढ़ोv(getpid(), &local, 1, &remote, 1, 0);
	अगर (ret != 4096) अणु
		/*
		 * We expect process_vm_पढ़ोv() to work अगर and only अगर the
		 * vsyscall page is पढ़ोable.
		 */
		म_लिखो("[%s]\tprocess_vm_readv() failed (ret = %d, errno = %d)\n", vsyscall_map_r ? "FAIL" : "OK", ret, त्रुटि_सं);
		वापस vsyscall_map_r ? 1 : 0;
	पूर्ण

	अगर (vsyscall_map_r) अणु
		अगर (!स_भेद(buf, (स्थिर व्योम *)0xffffffffff600000, 4096)) अणु
			म_लिखो("[OK]\tIt worked and read correct data\n");
		पूर्ण अन्यथा अणु
			म_लिखो("[FAIL]\tIt worked but returned incorrect data\n");
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\tprocess_rm_readv() succeeded, but it should have failed in this configuration\n");
		वापस 1;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

#अगर_घोषित __x86_64__
अटल अस्थिर संक_पूर्ण_प्रकार num_vsyscall_traps;

अटल व्योम sigtrap(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t *)ctx_व्योम;
	अचिन्हित दीर्घ ip = ctx->uc_mcontext.gregs[REG_RIP];

	अगर (((ip ^ 0xffffffffff600000UL) & ~0xfffUL) == 0)
		num_vsyscall_traps++;
पूर्ण

अटल पूर्णांक test_emulation(व्योम)
अणु
	समय_प्रकार पंचांगp;
	bool is_native;

	अगर (!vsyscall_map_x)
		वापस 0;

	म_लिखो("[RUN]\tchecking that vsyscalls are emulated\n");
	sethandler(SIGTRAP, sigtrap, 0);
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	vसमय(&पंचांगp);
	set_eflags(get_eflags() & ~X86_EFLAGS_TF);

	/*
	 * If vsyscalls are emulated, we expect a single trap in the
	 * vsyscall page -- the call inकाष्ठाion will trap with RIP
	 * poपूर्णांकing to the entry poपूर्णांक beक्रमe emulation takes over.
	 * In native mode, we expect two traps, since whatever code
	 * the vsyscall page contains will be more than just a ret
	 * inकाष्ठाion.
	 */
	is_native = (num_vsyscall_traps > 1);

	म_लिखो("[%s]\tvsyscalls are %s (%d instructions in vsyscall page)\n",
	       (is_native ? "FAIL" : "OK"),
	       (is_native ? "native" : "emulated"),
	       (पूर्णांक)num_vsyscall_traps);

	वापस is_native;
पूर्ण
#पूर्ण_अगर

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक nerrs = 0;

	init_vdso();
	nerrs += init_vsys();

	nerrs += test_gtod();
	nerrs += test_समय();
	nerrs += test_अ_लोpu(0);
	nerrs += test_अ_लोpu(1);

	sethandler(संक_अंश, sigsegv, 0);
	nerrs += test_vsys_r();
	nerrs += test_vsys_x();

	nerrs += test_process_vm_पढ़ोv();

#अगर_घोषित __x86_64__
	nerrs += test_emulation();
#पूर्ण_अगर

	वापस nerrs ? 1 : 0;
पूर्ण
