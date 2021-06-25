<शैली गुरु>
/*
 * jvmti_agent.c: JVMTI agent पूर्णांकerface
 *
 * Adapted from the Oprofile code in opagent.c:
 * This library is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Copyright 2007 OProfile authors
 * Jens Wilke
 * Daniel Hansel
 * Copyright IBM Corporation 2007
 */
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स> /* क्रम सूची_गढ़ो() */
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <सीमा.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <समय.स>
#समावेश <sys/mman.h>
#समावेश <syscall.h> /* क्रम gettid() */
#समावेश <err.h>
#समावेश <linux/kernel.h>

#समावेश "jvmti_agent.h"
#समावेश "../util/jitdump.h"

#घोषणा JIT_LANG "java"

अटल अक्षर jit_path[PATH_MAX];
अटल व्योम *marker_addr;

#अगर_अघोषित HAVE_GETTID
अटल अंतरभूत pid_t gettid(व्योम)
अणु
	वापस (pid_t)syscall(__NR_gettid);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_e_machine(काष्ठा jitheader *hdr)
अणु
	sमाप_प्रकार sret;
	अक्षर id[16];
	पूर्णांक fd, ret = -1;
	काष्ठा अणु
		uपूर्णांक16_t e_type;
		uपूर्णांक16_t e_machine;
	पूर्ण info;

	fd = खोलो("/proc/self/exe", O_RDONLY);
	अगर (fd == -1)
		वापस -1;

	sret = पढ़ो(fd, id, माप(id));
	अगर (sret != माप(id))
		जाओ error;

	/* check ELF signature */
	अगर (id[0] != 0x7f || id[1] != 'E' || id[2] != 'L' || id[3] != 'F')
		जाओ error;

	sret = पढ़ो(fd, &info, माप(info));
	अगर (sret != माप(info))
		जाओ error;

	hdr->elf_mach = info.e_machine;
	ret = 0;
error:
	बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक use_arch_बारtamp;

अटल अंतरभूत uपूर्णांक64_t
get_arch_बारtamp(व्योम)
अणु
#अगर defined(__i386__) || defined(__x86_64__)
	अचिन्हित पूर्णांक low, high;

	यंत्र अस्थिर("rdtsc" : "=a" (low), "=d" (high));

	वापस low | ((uपूर्णांक64_t)high) << 32;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#घोषणा NSEC_PER_SEC	1000000000
अटल पूर्णांक perf_clk_id = CLOCK_MONOTONIC;

अटल अंतरभूत uपूर्णांक64_t
बारpec_to_ns(स्थिर काष्ठा बारpec *ts)
अणु
        वापस ((uपूर्णांक64_t) ts->tv_sec * NSEC_PER_SEC) + ts->tv_nsec;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t
perf_get_बारtamp(व्योम)
अणु
	काष्ठा बारpec ts;
	पूर्णांक ret;

	अगर (use_arch_बारtamp)
		वापस get_arch_बारtamp();

	ret = घड़ी_समय_लो(perf_clk_id, &ts);
	अगर (ret)
		वापस 0;

	वापस बारpec_to_ns(&ts);
पूर्ण

अटल पूर्णांक
create_jit_cache_dir(व्योम)
अणु
	अक्षर str[32];
	अक्षर *base, *p;
	काष्ठा पंचांग पंचांग;
	समय_प्रकार t;
	पूर्णांक ret;

	समय(&t);
	स_स्थानीय_r(&t, &पंचांग);

	base = दो_पर्या("JITDUMPDIR");
	अगर (!base)
		base = दो_पर्या("HOME");
	अगर (!base)
		base = ".";

	स_माला(str, माप(str), JIT_LANG"-jit-%Y%m%d", &पंचांग);

	ret = snम_लिखो(jit_path, PATH_MAX, "%s/.debug/", base);
	अगर (ret >= PATH_MAX) अणु
		warnx("jvmti: cannot generate jit cache dir because %s/.debug/"
			" is too long, please check the cwd, JITDUMPDIR, and"
			" HOME variables", base);
		वापस -1;
	पूर्ण
	ret = सूची_गढ़ो(jit_path, 0755);
	अगर (ret == -1) अणु
		अगर (त्रुटि_सं != EEXIST) अणु
			warn("jvmti: cannot create jit cache dir %s", jit_path);
			वापस -1;
		पूर्ण
	पूर्ण

	ret = snम_लिखो(jit_path, PATH_MAX, "%s/.debug/jit", base);
	अगर (ret >= PATH_MAX) अणु
		warnx("jvmti: cannot generate jit cache dir because"
			" %s/.debug/jit is too long, please check the cwd,"
			" JITDUMPDIR, and HOME variables", base);
		वापस -1;
	पूर्ण
	ret = सूची_गढ़ो(jit_path, 0755);
	अगर (ret == -1) अणु
		अगर (त्रुटि_सं != EEXIST) अणु
			warn("jvmti: cannot create jit cache dir %s", jit_path);
			वापस -1;
		पूर्ण
	पूर्ण

	ret = snम_लिखो(jit_path, PATH_MAX, "%s/.debug/jit/%s.XXXXXXXX", base, str);
	अगर (ret >= PATH_MAX) अणु
		warnx("jvmti: cannot generate jit cache dir because"
			" %s/.debug/jit/%s.XXXXXXXX is too long, please check"
			" the cwd, JITDUMPDIR, and HOME variables",
			base, str);
		वापस -1;
	पूर्ण
	p = mkdtemp(jit_path);
	अगर (p != jit_path) अणु
		warn("jvmti: cannot create jit cache dir %s", jit_path);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
perf_खोलो_marker_file(पूर्णांक fd)
अणु
	दीर्घ pgsz;

	pgsz = sysconf(_SC_PAGESIZE);
	अगर (pgsz == -1)
		वापस -1;

	/*
	 * we mmap the jitdump to create an MMAP RECORD in perf.data file.
	 * The mmap is captured either live (perf record running when we mmap)
	 * or  in deferred mode, via /proc/PID/maps
	 * the MMAP record is used as a marker of a jitdump file क्रम more meta
	 * data info about the jitted code. Perf report/annotate detect this
	 * special filename and process the jitdump file.
	 *
	 * mapping must be PROT_EXEC to ensure it is captured by perf record
	 * even when not using -d option
	 */
	marker_addr = mmap(शून्य, pgsz, PROT_READ|PROT_EXEC, MAP_PRIVATE, fd, 0);
	वापस (marker_addr == MAP_FAILED) ? -1 : 0;
पूर्ण

अटल व्योम
perf_बंद_marker_file(व्योम)
अणु
	दीर्घ pgsz;

	अगर (!marker_addr)
		वापस;

	pgsz = sysconf(_SC_PAGESIZE);
	अगर (pgsz == -1)
		वापस;

	munmap(marker_addr, pgsz);
पूर्ण

अटल व्योम
init_arch_बारtamp(व्योम)
अणु
	अक्षर *str = दो_पर्या("JITDUMP_USE_ARCH_TIMESTAMP");

	अगर (!str || !*str || !म_भेद(str, "0"))
		वापस;

	use_arch_बारtamp = 1;
पूर्ण

व्योम *jvmti_खोलो(व्योम)
अणु
	अक्षर dump_path[PATH_MAX];
	काष्ठा jitheader header;
	पूर्णांक fd, ret;
	खाता *fp;

	init_arch_बारtamp();

	/*
	 * check अगर घड़ीid is supported
	 */
	अगर (!perf_get_बारtamp()) अणु
		अगर (use_arch_बारtamp)
			warnx("jvmti: arch timestamp not supported");
		अन्यथा
			warnx("jvmti: kernel does not support %d clock id", perf_clk_id);
	पूर्ण

	स_रखो(&header, 0, माप(header));

	/*
	 * jitdump file dir
	 */
	अगर (create_jit_cache_dir() < 0)
		वापस शून्य;

	/*
	 * jitdump file name
	 */
	ret = snम_लिखो(dump_path, PATH_MAX, "%s/jit-%i.dump", jit_path, getpid());
	अगर (ret >= PATH_MAX) अणु
		warnx("jvmti: cannot generate jitdump file full path because"
			" %s/jit-%i.dump is too long, please check the cwd,"
			" JITDUMPDIR, and HOME variables", jit_path, getpid());
		वापस शून्य;
	पूर्ण

	fd = खोलो(dump_path, O_CREAT|O_TRUNC|O_RDWR, 0666);
	अगर (fd == -1)
		वापस शून्य;

	/*
	 * create perf.data maker क्रम the jitdump file
	 */
	अगर (perf_खोलो_marker_file(fd)) अणु
		warnx("jvmti: failed to create marker file");
		वापस शून्य;
	पूर्ण

	fp = fकरोpen(fd, "w+");
	अगर (!fp) अणु
		warn("jvmti: cannot create %s", dump_path);
		बंद(fd);
		जाओ error;
	पूर्ण

	warnx("jvmti: jitdump in %s", dump_path);

	अगर (get_e_machine(&header)) अणु
		warn("get_e_machine failed\n");
		जाओ error;
	पूर्ण

	header.magic      = JITHEADER_MAGIC;
	header.version    = JITHEADER_VERSION;
	header.total_size = माप(header);
	header.pid        = getpid();

	header.बारtamp = perf_get_बारtamp();

	अगर (use_arch_बारtamp)
		header.flags |= JITDUMP_FLAGS_ARCH_TIMESTAMP;

	अगर (!ख_डालो(&header, माप(header), 1, fp)) अणु
		warn("jvmti: cannot write dumpfile header");
		जाओ error;
	पूर्ण
	वापस fp;
error:
	ख_बंद(fp);
	वापस शून्य;
पूर्ण

पूर्णांक
jvmti_बंद(व्योम *agent)
अणु
	काष्ठा jr_code_बंद rec;
	खाता *fp = agent;

	अगर (!fp) अणु
		warnx("jvmti: invalid fd in close_agent");
		वापस -1;
	पूर्ण

	rec.p.id = JIT_CODE_CLOSE;
	rec.p.total_size = माप(rec);

	rec.p.बारtamp = perf_get_बारtamp();

	अगर (!ख_डालो(&rec, माप(rec), 1, fp))
		वापस -1;

	ख_बंद(fp);

	fp = शून्य;

	perf_बंद_marker_file();

	वापस 0;
पूर्ण

पूर्णांक
jvmti_ग_लिखो_code(व्योम *agent, अक्षर स्थिर *sym,
	uपूर्णांक64_t vma, व्योम स्थिर *code, अचिन्हित पूर्णांक स्थिर size)
अणु
	अटल पूर्णांक code_generation = 1;
	काष्ठा jr_code_load rec;
	माप_प्रकार sym_len;
	खाता *fp = agent;
	पूर्णांक ret = -1;

	/* करोn't care about 0 length function, no samples */
	अगर (size == 0)
		वापस 0;

	अगर (!fp) अणु
		warnx("jvmti: invalid fd in write_native_code");
		वापस -1;
	पूर्ण

	sym_len = म_माप(sym) + 1;

	rec.p.id           = JIT_CODE_LOAD;
	rec.p.total_size   = माप(rec) + sym_len;
	rec.p.बारtamp    = perf_get_बारtamp();

	rec.code_size  = size;
	rec.vma        = vma;
	rec.code_addr  = vma;
	rec.pid	       = getpid();
	rec.tid	       = gettid();

	अगर (code)
		rec.p.total_size += size;

	/*
	 * If JVM is multi-thपढ़ोed, multiple concurrent calls to agent
	 * may be possible, so protect file ग_लिखोs
	 */
	flockfile(fp);

	/*
	 * get code index inside lock to aव्योम race condition
	 */
	rec.code_index = code_generation++;

	ret = ख_डालो_unlocked(&rec, माप(rec), 1, fp);
	ख_डालो_unlocked(sym, sym_len, 1, fp);

	अगर (code)
		ख_डालो_unlocked(code, size, 1, fp);

	funlockfile(fp);

	ret = 0;

	वापस ret;
पूर्ण

पूर्णांक
jvmti_ग_लिखो_debug_info(व्योम *agent, uपूर्णांक64_t code,
    पूर्णांक nr_lines, jvmti_line_info_t *li,
    स्थिर अक्षर * स्थिर * file_names)
अणु
	काष्ठा jr_code_debug_info rec;
	माप_प्रकार sret, len, size, flen = 0;
	uपूर्णांक64_t addr;
	खाता *fp = agent;
	पूर्णांक i;

	/*
	 * no entry to ग_लिखो
	 */
	अगर (!nr_lines)
		वापस 0;

	अगर (!fp) अणु
		warnx("jvmti: invalid fd in write_debug_info");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < nr_lines; ++i) अणु
	    flen += म_माप(file_names[i]) + 1;
	पूर्ण

	rec.p.id        = JIT_CODE_DEBUG_INFO;
	size            = माप(rec);
	rec.p.बारtamp = perf_get_बारtamp();
	rec.code_addr   = (uपूर्णांक64_t)(uपूर्णांकptr_t)code;
	rec.nr_entry    = nr_lines;

	/*
	 * on disk source line info layout:
	 * uपूर्णांक64_t : addr
	 * पूर्णांक      : line number
	 * पूर्णांक      : column discriminator
	 * file[]   : source file name
	 */
	size += nr_lines * माप(काष्ठा debug_entry);
	size += flen;
	rec.p.total_size = size;

	/*
	 * If JVM is multi-thपढ़ोed, multiple concurrent calls to agent
	 * may be possible, so protect file ग_लिखोs
	 */
	flockfile(fp);

	sret = ख_डालो_unlocked(&rec, माप(rec), 1, fp);
	अगर (sret != 1)
		जाओ error;

	क्रम (i = 0; i < nr_lines; i++) अणु

		addr = (uपूर्णांक64_t)li[i].pc;
		len  = माप(addr);
		sret = ख_डालो_unlocked(&addr, len, 1, fp);
		अगर (sret != 1)
			जाओ error;

		len  = माप(li[0].line_number);
		sret = ख_डालो_unlocked(&li[i].line_number, len, 1, fp);
		अगर (sret != 1)
			जाओ error;

		len  = माप(li[0].discrim);
		sret = ख_डालो_unlocked(&li[i].discrim, len, 1, fp);
		अगर (sret != 1)
			जाओ error;

		sret = ख_डालो_unlocked(file_names[i], म_माप(file_names[i]) + 1, 1, fp);
		अगर (sret != 1)
			जाओ error;
	पूर्ण
	funlockfile(fp);
	वापस 0;
error:
	funlockfile(fp);
	वापस -1;
पूर्ण
