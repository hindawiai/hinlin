<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश "string2.h"
#समावेश <sys/param.h>
#समावेश <sys/types.h>
#समावेश <byteswap.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/zभाग.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/utsname.h>
#समावेश <linux/समय64.h>
#समावेश <dirent.h>
#अगर_घोषित HAVE_LIBBPF_SUPPORT
#समावेश <bpf/libbpf.h>
#पूर्ण_अगर
#समावेश <perf/cpumap.h>

#समावेश "dso.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "header.h"
#समावेश "memswap.h"
#समावेश "trace-event.h"
#समावेश "session.h"
#समावेश "symbol.h"
#समावेश "debug.h"
#समावेश "cpumap.h"
#समावेश "pmu.h"
#समावेश "vdso.h"
#समावेश "strbuf.h"
#समावेश "build-id.h"
#समावेश "data.h"
#समावेश <api/fs/fs.h>
#समावेश "asm/bug.h"
#समावेश "tool.h"
#समावेश "time-utils.h"
#समावेश "units.h"
#समावेश "util/util.h" // perf_exe()
#समावेश "cputopo.h"
#समावेश "bpf-event.h"
#समावेश "clockid.h"

#समावेश <linux/प्रकार.स>
#समावेश <पूर्णांकernal/lib.h>

/*
 * magic2 = "PERFILE2"
 * must be a numerical value to let the endianness
 * determine the memory layout. That way we are able
 * to detect endianness when पढ़ोing the perf.data file
 * back.
 *
 * we check क्रम legacy (PERFखाता) क्रमmat.
 */
अटल स्थिर अक्षर *__perf_magic1 = "PERFFILE";
अटल स्थिर u64 __perf_magic2    = 0x32454c4946524550ULL;
अटल स्थिर u64 __perf_magic2_sw = 0x50455246494c4532ULL;

#घोषणा PERF_MAGIC	__perf_magic2

स्थिर अक्षर perf_version_string[] = PERF_VERSION;

काष्ठा perf_file_attr अणु
	काष्ठा perf_event_attr	attr;
	काष्ठा perf_file_section	ids;
पूर्ण;

व्योम perf_header__set_feat(काष्ठा perf_header *header, पूर्णांक feat)
अणु
	set_bit(feat, header->adds_features);
पूर्ण

व्योम perf_header__clear_feat(काष्ठा perf_header *header, पूर्णांक feat)
अणु
	clear_bit(feat, header->adds_features);
पूर्ण

bool perf_header__has_feat(स्थिर काष्ठा perf_header *header, पूर्णांक feat)
अणु
	वापस test_bit(feat, header->adds_features);
पूर्ण

अटल पूर्णांक __करो_ग_लिखो_fd(काष्ठा feat_fd *ff, स्थिर व्योम *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार ret = ग_लिखोn(ff->fd, buf, size);

	अगर (ret != (sमाप_प्रकार)size)
		वापस ret < 0 ? (पूर्णांक)ret : -1;
	वापस 0;
पूर्ण

अटल पूर्णांक __करो_ग_लिखो_buf(काष्ठा feat_fd *ff,  स्थिर व्योम *buf, माप_प्रकार size)
अणु
	/* काष्ठा perf_event_header::size is u16 */
	स्थिर माप_प्रकार max_size = 0xffff - माप(काष्ठा perf_event_header);
	माप_प्रकार new_size = ff->size;
	व्योम *addr;

	अगर (size + ff->offset > max_size)
		वापस -E2BIG;

	जबतक (size > (new_size - ff->offset))
		new_size <<= 1;
	new_size = min(max_size, new_size);

	अगर (ff->size < new_size) अणु
		addr = पुनः_स्मृति(ff->buf, new_size);
		अगर (!addr)
			वापस -ENOMEM;
		ff->buf = addr;
		ff->size = new_size;
	पूर्ण

	स_नकल(ff->buf + ff->offset, buf, size);
	ff->offset += size;

	वापस 0;
पूर्ण

/* Return: 0 अगर succeeded, -ERR अगर failed. */
पूर्णांक करो_ग_लिखो(काष्ठा feat_fd *ff, स्थिर व्योम *buf, माप_प्रकार size)
अणु
	अगर (!ff->buf)
		वापस __करो_ग_लिखो_fd(ff, buf, size);
	वापस __करो_ग_लिखो_buf(ff, buf, size);
पूर्ण

/* Return: 0 अगर succeeded, -ERR अगर failed. */
अटल पूर्णांक करो_ग_लिखो_biपंचांगap(काष्ठा feat_fd *ff, अचिन्हित दीर्घ *set, u64 size)
अणु
	u64 *p = (u64 *) set;
	पूर्णांक i, ret;

	ret = करो_ग_लिखो(ff, &size, माप(size));
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; (u64) i < BITS_TO_U64(size); i++) अणु
		ret = करो_ग_लिखो(ff, p + i, माप(*p));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Return: 0 अगर succeeded, -ERR अगर failed. */
पूर्णांक ग_लिखो_padded(काष्ठा feat_fd *ff, स्थिर व्योम *bf,
		 माप_प्रकार count, माप_प्रकार count_aligned)
अणु
	अटल स्थिर अक्षर zero_buf[NAME_ALIGN];
	पूर्णांक err = करो_ग_लिखो(ff, bf, count);

	अगर (!err)
		err = करो_ग_लिखो(ff, zero_buf, count_aligned - count);

	वापस err;
पूर्ण

#घोषणा string_size(str)						\
	(PERF_ALIGN((म_माप(str) + 1), NAME_ALIGN) + माप(u32))

/* Return: 0 अगर succeeded, -ERR अगर failed. */
अटल पूर्णांक करो_ग_लिखो_string(काष्ठा feat_fd *ff, स्थिर अक्षर *str)
अणु
	u32 len, olen;
	पूर्णांक ret;

	olen = म_माप(str) + 1;
	len = PERF_ALIGN(olen, NAME_ALIGN);

	/* ग_लिखो len, incl. \0 */
	ret = करो_ग_लिखो(ff, &len, माप(len));
	अगर (ret < 0)
		वापस ret;

	वापस ग_लिखो_padded(ff, str, olen, len);
पूर्ण

अटल पूर्णांक __करो_पढ़ो_fd(काष्ठा feat_fd *ff, व्योम *addr, sमाप_प्रकार size)
अणु
	sमाप_प्रकार ret = पढ़ोn(ff->fd, addr, size);

	अगर (ret != size)
		वापस ret < 0 ? (पूर्णांक)ret : -1;
	वापस 0;
पूर्ण

अटल पूर्णांक __करो_पढ़ो_buf(काष्ठा feat_fd *ff, व्योम *addr, sमाप_प्रकार size)
अणु
	अगर (size > (sमाप_प्रकार)ff->size - ff->offset)
		वापस -1;

	स_नकल(addr, ff->buf + ff->offset, size);
	ff->offset += size;

	वापस 0;

पूर्ण

अटल पूर्णांक __करो_पढ़ो(काष्ठा feat_fd *ff, व्योम *addr, sमाप_प्रकार size)
अणु
	अगर (!ff->buf)
		वापस __करो_पढ़ो_fd(ff, addr, size);
	वापस __करो_पढ़ो_buf(ff, addr, size);
पूर्ण

अटल पूर्णांक करो_पढ़ो_u32(काष्ठा feat_fd *ff, u32 *addr)
अणु
	पूर्णांक ret;

	ret = __करो_पढ़ो(ff, addr, माप(*addr));
	अगर (ret)
		वापस ret;

	अगर (ff->ph->needs_swap)
		*addr = bswap_32(*addr);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_पढ़ो_u64(काष्ठा feat_fd *ff, u64 *addr)
अणु
	पूर्णांक ret;

	ret = __करो_पढ़ो(ff, addr, माप(*addr));
	अगर (ret)
		वापस ret;

	अगर (ff->ph->needs_swap)
		*addr = bswap_64(*addr);
	वापस 0;
पूर्ण

अटल अक्षर *करो_पढ़ो_string(काष्ठा feat_fd *ff)
अणु
	u32 len;
	अक्षर *buf;

	अगर (करो_पढ़ो_u32(ff, &len))
		वापस शून्य;

	buf = दो_स्मृति(len);
	अगर (!buf)
		वापस शून्य;

	अगर (!__करो_पढ़ो(ff, buf, len)) अणु
		/*
		 * strings are padded by zeroes
		 * thus the actual म_माप of buf
		 * may be less than len
		 */
		वापस buf;
	पूर्ण

	मुक्त(buf);
	वापस शून्य;
पूर्ण

/* Return: 0 अगर succeeded, -ERR अगर failed. */
अटल पूर्णांक करो_पढ़ो_biपंचांगap(काष्ठा feat_fd *ff, अचिन्हित दीर्घ **pset, u64 *psize)
अणु
	अचिन्हित दीर्घ *set;
	u64 size, *p;
	पूर्णांक i, ret;

	ret = करो_पढ़ो_u64(ff, &size);
	अगर (ret)
		वापस ret;

	set = biपंचांगap_alloc(size);
	अगर (!set)
		वापस -ENOMEM;

	p = (u64 *) set;

	क्रम (i = 0; (u64) i < BITS_TO_U64(size); i++) अणु
		ret = करो_पढ़ो_u64(ff, p + i);
		अगर (ret < 0) अणु
			मुक्त(set);
			वापस ret;
		पूर्ण
	पूर्ण

	*pset  = set;
	*psize = size;
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_tracing_data(काष्ठा feat_fd *ff,
			      काष्ठा evlist *evlist)
अणु
	अगर (WARN(ff->buf, "Error: calling %s in pipe-mode.\n", __func__))
		वापस -1;

	वापस पढ़ो_tracing_data(ff->fd, &evlist->core.entries);
पूर्ण

अटल पूर्णांक ग_लिखो_build_id(काष्ठा feat_fd *ff,
			  काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा perf_session *session;
	पूर्णांक err;

	session = container_of(ff->ph, काष्ठा perf_session, header);

	अगर (!perf_session__पढ़ो_build_ids(session, true))
		वापस -1;

	अगर (WARN(ff->buf, "Error: calling %s in pipe-mode.\n", __func__))
		वापस -1;

	err = perf_session__ग_लिखो_buildid_table(session, ff);
	अगर (err < 0) अणु
		pr_debug("failed to write buildid table\n");
		वापस err;
	पूर्ण
	perf_session__cache_build_ids(session);

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_hostname(काष्ठा feat_fd *ff,
			  काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा utsname uts;
	पूर्णांक ret;

	ret = uname(&uts);
	अगर (ret < 0)
		वापस -1;

	वापस करो_ग_लिखो_string(ff, uts.nodename);
पूर्ण

अटल पूर्णांक ग_लिखो_osrelease(काष्ठा feat_fd *ff,
			   काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा utsname uts;
	पूर्णांक ret;

	ret = uname(&uts);
	अगर (ret < 0)
		वापस -1;

	वापस करो_ग_लिखो_string(ff, uts.release);
पूर्ण

अटल पूर्णांक ग_लिखो_arch(काष्ठा feat_fd *ff,
		      काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा utsname uts;
	पूर्णांक ret;

	ret = uname(&uts);
	अगर (ret < 0)
		वापस -1;

	वापस करो_ग_लिखो_string(ff, uts.machine);
पूर्ण

अटल पूर्णांक ग_लिखो_version(काष्ठा feat_fd *ff,
			 काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस करो_ग_लिखो_string(ff, perf_version_string);
पूर्ण

अटल पूर्णांक __ग_लिखो_cpudesc(काष्ठा feat_fd *ff, स्थिर अक्षर *cpuinfo_proc)
अणु
	खाता *file;
	अक्षर *buf = शून्य;
	अक्षर *s, *p;
	स्थिर अक्षर *search = cpuinfo_proc;
	माप_प्रकार len = 0;
	पूर्णांक ret = -1;

	अगर (!search)
		वापस -1;

	file = ख_खोलो("/proc/cpuinfo", "r");
	अगर (!file)
		वापस -1;

	जबतक (getline(&buf, &len, file) > 0) अणु
		ret = म_भेदन(buf, search, म_माप(search));
		अगर (!ret)
			अवरोध;
	पूर्ण

	अगर (ret) अणु
		ret = -1;
		जाओ करोne;
	पूर्ण

	s = buf;

	p = म_अक्षर(buf, ':');
	अगर (p && *(p+1) == ' ' && *(p+2))
		s = p + 2;
	p = म_अक्षर(s, '\n');
	अगर (p)
		*p = '\0';

	/* squash extra space अक्षरacters (bअक्रमing string) */
	p = s;
	जबतक (*p) अणु
		अगर (है_खाली(*p)) अणु
			अक्षर *r = p + 1;
			अक्षर *q = skip_spaces(r);
			*p = ' ';
			अगर (q != (p+1))
				जबतक ((*r++ = *q++));
		पूर्ण
		p++;
	पूर्ण
	ret = करो_ग_लिखो_string(ff, s);
करोne:
	मुक्त(buf);
	ख_बंद(file);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_cpudesc(काष्ठा feat_fd *ff,
		       काष्ठा evlist *evlist __maybe_unused)
अणु
#अगर defined(__घातerpc__) || defined(__hppa__) || defined(__sparc__)
#घोषणा CPUINFO_PROC	अणु "cpu", पूर्ण
#या_अगर defined(__s390__)
#घोषणा CPUINFO_PROC	अणु "vendor_id", पूर्ण
#या_अगर defined(__sh__)
#घोषणा CPUINFO_PROC	अणु "cpu type", पूर्ण
#या_अगर defined(__alpha__) || defined(__mips__)
#घोषणा CPUINFO_PROC	अणु "cpu model", पूर्ण
#या_अगर defined(__arm__)
#घोषणा CPUINFO_PROC	अणु "model name", "Processor", पूर्ण
#या_अगर defined(__arc__)
#घोषणा CPUINFO_PROC	अणु "Processor", पूर्ण
#या_अगर defined(__xtensa__)
#घोषणा CPUINFO_PROC	अणु "core ID", पूर्ण
#अन्यथा
#घोषणा CPUINFO_PROC	अणु "model name", पूर्ण
#पूर्ण_अगर
	स्थिर अक्षर *cpuinfo_procs[] = CPUINFO_PROC;
#अघोषित CPUINFO_PROC
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cpuinfo_procs); i++) अणु
		पूर्णांक ret;
		ret = __ग_लिखो_cpudesc(ff, cpuinfo_procs[i]);
		अगर (ret >= 0)
			वापस ret;
	पूर्ण
	वापस -1;
पूर्ण


अटल पूर्णांक ग_लिखो_nrcpus(काष्ठा feat_fd *ff,
			काष्ठा evlist *evlist __maybe_unused)
अणु
	दीर्घ nr;
	u32 nrc, nra;
	पूर्णांक ret;

	nrc = cpu__max_present_cpu();

	nr = sysconf(_SC_NPROCESSORS_ONLN);
	अगर (nr < 0)
		वापस -1;

	nra = (u32)(nr & अच_पूर्णांक_उच्च);

	ret = करो_ग_लिखो(ff, &nrc, माप(nrc));
	अगर (ret < 0)
		वापस ret;

	वापस करो_ग_लिखो(ff, &nra, माप(nra));
पूर्ण

अटल पूर्णांक ग_लिखो_event_desc(काष्ठा feat_fd *ff,
			    काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	u32 nre, nri, sz;
	पूर्णांक ret;

	nre = evlist->core.nr_entries;

	/*
	 * ग_लिखो number of events
	 */
	ret = करो_ग_लिखो(ff, &nre, माप(nre));
	अगर (ret < 0)
		वापस ret;

	/*
	 * size of perf_event_attr काष्ठा
	 */
	sz = (u32)माप(evsel->core.attr);
	ret = करो_ग_लिखो(ff, &sz, माप(sz));
	अगर (ret < 0)
		वापस ret;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		ret = करो_ग_लिखो(ff, &evsel->core.attr, sz);
		अगर (ret < 0)
			वापस ret;
		/*
		 * ग_लिखो number of unique id per event
		 * there is one id per instance of an event
		 *
		 * copy पूर्णांकo an nri to be independent of the
		 * type of ids,
		 */
		nri = evsel->core.ids;
		ret = करो_ग_लिखो(ff, &nri, माप(nri));
		अगर (ret < 0)
			वापस ret;

		/*
		 * ग_लिखो event string as passed on cmdline
		 */
		ret = करो_ग_लिखो_string(ff, evsel__name(evsel));
		अगर (ret < 0)
			वापस ret;
		/*
		 * ग_लिखो unique ids क्रम this event
		 */
		ret = करो_ग_लिखो(ff, evsel->core.id, evsel->core.ids * माप(u64));
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_cmdline(काष्ठा feat_fd *ff,
			 काष्ठा evlist *evlist __maybe_unused)
अणु
	अक्षर pbuf[MAXPATHLEN], *buf;
	पूर्णांक i, ret, n;

	/* actual path to perf binary */
	buf = perf_exe(pbuf, MAXPATHLEN);

	/* account क्रम binary path */
	n = perf_env.nr_cmdline + 1;

	ret = करो_ग_लिखो(ff, &n, माप(n));
	अगर (ret < 0)
		वापस ret;

	ret = करो_ग_लिखो_string(ff, buf);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0 ; i < perf_env.nr_cmdline; i++) अणु
		ret = करो_ग_लिखो_string(ff, perf_env.cmdline_argv[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक ग_लिखो_cpu_topology(काष्ठा feat_fd *ff,
			      काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा cpu_topology *tp;
	u32 i;
	पूर्णांक ret, j;

	tp = cpu_topology__new();
	अगर (!tp)
		वापस -1;

	ret = करो_ग_लिखो(ff, &tp->core_sib, माप(tp->core_sib));
	अगर (ret < 0)
		जाओ करोne;

	क्रम (i = 0; i < tp->core_sib; i++) अणु
		ret = करो_ग_लिखो_string(ff, tp->core_siblings[i]);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण
	ret = करो_ग_लिखो(ff, &tp->thपढ़ो_sib, माप(tp->thपढ़ो_sib));
	अगर (ret < 0)
		जाओ करोne;

	क्रम (i = 0; i < tp->thपढ़ो_sib; i++) अणु
		ret = करो_ग_लिखो_string(ff, tp->thपढ़ो_siblings[i]);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	ret = perf_env__पढ़ो_cpu_topology_map(&perf_env);
	अगर (ret < 0)
		जाओ करोne;

	क्रम (j = 0; j < perf_env.nr_cpus_avail; j++) अणु
		ret = करो_ग_लिखो(ff, &perf_env.cpu[j].core_id,
			       माप(perf_env.cpu[j].core_id));
		अगर (ret < 0)
			वापस ret;
		ret = करो_ग_लिखो(ff, &perf_env.cpu[j].socket_id,
			       माप(perf_env.cpu[j].socket_id));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!tp->die_sib)
		जाओ करोne;

	ret = करो_ग_लिखो(ff, &tp->die_sib, माप(tp->die_sib));
	अगर (ret < 0)
		जाओ करोne;

	क्रम (i = 0; i < tp->die_sib; i++) अणु
		ret = करो_ग_लिखो_string(ff, tp->die_siblings[i]);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	क्रम (j = 0; j < perf_env.nr_cpus_avail; j++) अणु
		ret = करो_ग_लिखो(ff, &perf_env.cpu[j].die_id,
			       माप(perf_env.cpu[j].die_id));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

करोne:
	cpu_topology__delete(tp);
	वापस ret;
पूर्ण



अटल पूर्णांक ग_लिखो_total_mem(काष्ठा feat_fd *ff,
			   काष्ठा evlist *evlist __maybe_unused)
अणु
	अक्षर *buf = शून्य;
	खाता *fp;
	माप_प्रकार len = 0;
	पूर्णांक ret = -1, n;
	uपूर्णांक64_t mem;

	fp = ख_खोलो("/proc/meminfo", "r");
	अगर (!fp)
		वापस -1;

	जबतक (getline(&buf, &len, fp) > 0) अणु
		ret = म_भेदन(buf, "MemTotal:", 9);
		अगर (!ret)
			अवरोध;
	पूर्ण
	अगर (!ret) अणु
		n = माला_पूछो(buf, "%*s %"PRIu64, &mem);
		अगर (n == 1)
			ret = करो_ग_लिखो(ff, &mem, माप(mem));
	पूर्ण अन्यथा
		ret = -1;
	मुक्त(buf);
	ख_बंद(fp);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_numa_topology(काष्ठा feat_fd *ff,
			       काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा numa_topology *tp;
	पूर्णांक ret = -1;
	u32 i;

	tp = numa_topology__new();
	अगर (!tp)
		वापस -ENOMEM;

	ret = करो_ग_लिखो(ff, &tp->nr, माप(u32));
	अगर (ret < 0)
		जाओ err;

	क्रम (i = 0; i < tp->nr; i++) अणु
		काष्ठा numa_topology_node *n = &tp->nodes[i];

		ret = करो_ग_लिखो(ff, &n->node, माप(u32));
		अगर (ret < 0)
			जाओ err;

		ret = करो_ग_लिखो(ff, &n->mem_total, माप(u64));
		अगर (ret)
			जाओ err;

		ret = करो_ग_लिखो(ff, &n->mem_मुक्त, माप(u64));
		अगर (ret)
			जाओ err;

		ret = करो_ग_लिखो_string(ff, n->cpus);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	ret = 0;

err:
	numa_topology__delete(tp);
	वापस ret;
पूर्ण

/*
 * File क्रमmat:
 *
 * काष्ठा pmu_mappings अणु
 *	u32	pmu_num;
 *	काष्ठा pmu_map अणु
 *		u32	type;
 *		अक्षर	name[];
 *	पूर्ण[pmu_num];
 * पूर्ण;
 */

अटल पूर्णांक ग_लिखो_pmu_mappings(काष्ठा feat_fd *ff,
			      काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा perf_pmu *pmu = शून्य;
	u32 pmu_num = 0;
	पूर्णांक ret;

	/*
	 * Do a first pass to count number of pmu to aव्योम lseek so this
	 * works in pipe mode as well.
	 */
	जबतक ((pmu = perf_pmu__scan(pmu))) अणु
		अगर (!pmu->name)
			जारी;
		pmu_num++;
	पूर्ण

	ret = करो_ग_लिखो(ff, &pmu_num, माप(pmu_num));
	अगर (ret < 0)
		वापस ret;

	जबतक ((pmu = perf_pmu__scan(pmu))) अणु
		अगर (!pmu->name)
			जारी;

		ret = करो_ग_लिखो(ff, &pmu->type, माप(pmu->type));
		अगर (ret < 0)
			वापस ret;

		ret = करो_ग_लिखो_string(ff, pmu->name);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * File क्रमmat:
 *
 * काष्ठा group_descs अणु
 *	u32	nr_groups;
 *	काष्ठा group_desc अणु
 *		अक्षर	name[];
 *		u32	leader_idx;
 *		u32	nr_members;
 *	पूर्ण[nr_groups];
 * पूर्ण;
 */
अटल पूर्णांक ग_लिखो_group_desc(काष्ठा feat_fd *ff,
			    काष्ठा evlist *evlist)
अणु
	u32 nr_groups = evlist->nr_groups;
	काष्ठा evsel *evsel;
	पूर्णांक ret;

	ret = करो_ग_लिखो(ff, &nr_groups, माप(nr_groups));
	अगर (ret < 0)
		वापस ret;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__is_group_leader(evsel) && evsel->core.nr_members > 1) अणु
			स्थिर अक्षर *name = evsel->group_name ?: "{anon_group}";
			u32 leader_idx = evsel->idx;
			u32 nr_members = evsel->core.nr_members;

			ret = करो_ग_लिखो_string(ff, name);
			अगर (ret < 0)
				वापस ret;

			ret = करो_ग_लिखो(ff, &leader_idx, माप(leader_idx));
			अगर (ret < 0)
				वापस ret;

			ret = करो_ग_लिखो(ff, &nr_members, माप(nr_members));
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return the CPU id as a raw string.
 *
 * Each architecture should provide a more precise id string that
 * can be use to match the architecture's "mapfile".
 */
अक्षर * __weak get_cpuid_str(काष्ठा perf_pmu *pmu __maybe_unused)
अणु
	वापस शून्य;
पूर्ण

/* Return zero when the cpuid from the mapfile.csv matches the
 * cpuid string generated on this platक्रमm.
 * Otherwise वापस non-zero.
 */
पूर्णांक __weak म_भेद_cpuid_str(स्थिर अक्षर *mapcpuid, स्थिर अक्षर *cpuid)
अणु
	regex_t re;
	regmatch_t pmatch[1];
	पूर्णांक match;

	अगर (regcomp(&re, mapcpuid, REG_EXTENDED) != 0) अणु
		/* Warn unable to generate match particular string. */
		pr_info("Invalid regular expression %s\n", mapcpuid);
		वापस 1;
	पूर्ण

	match = !regexec(&re, cpuid, 1, pmatch, 0);
	regमुक्त(&re);
	अगर (match) अणु
		माप_प्रकार match_len = (pmatch[0].rm_eo - pmatch[0].rm_so);

		/* Verअगरy the entire string matched. */
		अगर (match_len == म_माप(cpuid))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * शेष get_cpuid(): nothing माला_लो recorded
 * actual implementation must be in arch/$(SRCARCH)/util/header.c
 */
पूर्णांक __weak get_cpuid(अक्षर *buffer __maybe_unused, माप_प्रकार sz __maybe_unused)
अणु
	वापस ENOSYS; /* Not implemented */
पूर्ण

अटल पूर्णांक ग_लिखो_cpuid(काष्ठा feat_fd *ff,
		       काष्ठा evlist *evlist __maybe_unused)
अणु
	अक्षर buffer[64];
	पूर्णांक ret;

	ret = get_cpuid(buffer, माप(buffer));
	अगर (ret)
		वापस -1;

	वापस करो_ग_लिखो_string(ff, buffer);
पूर्ण

अटल पूर्णांक ग_लिखो_branch_stack(काष्ठा feat_fd *ff __maybe_unused,
			      काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_auxtrace(काष्ठा feat_fd *ff,
			  काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा perf_session *session;
	पूर्णांक err;

	अगर (WARN(ff->buf, "Error: calling %s in pipe-mode.\n", __func__))
		वापस -1;

	session = container_of(ff->ph, काष्ठा perf_session, header);

	err = auxtrace_index__ग_लिखो(ff->fd, &session->auxtrace_index);
	अगर (err < 0)
		pr_err("Failed to write auxtrace index\n");
	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_घड़ीid(काष्ठा feat_fd *ff,
			 काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस करो_ग_लिखो(ff, &ff->ph->env.घड़ी.घड़ीid_res_ns,
			माप(ff->ph->env.घड़ी.घड़ीid_res_ns));
पूर्ण

अटल पूर्णांक ग_लिखो_घड़ी_data(काष्ठा feat_fd *ff,
			    काष्ठा evlist *evlist __maybe_unused)
अणु
	u64 *data64;
	u32 data32;
	पूर्णांक ret;

	/* version */
	data32 = 1;

	ret = करो_ग_लिखो(ff, &data32, माप(data32));
	अगर (ret < 0)
		वापस ret;

	/* घड़ीid */
	data32 = ff->ph->env.घड़ी.घड़ीid;

	ret = करो_ग_लिखो(ff, &data32, माप(data32));
	अगर (ret < 0)
		वापस ret;

	/* TOD ref समय */
	data64 = &ff->ph->env.घड़ी.tod_ns;

	ret = करो_ग_लिखो(ff, data64, माप(*data64));
	अगर (ret < 0)
		वापस ret;

	/* घड़ीid ref समय */
	data64 = &ff->ph->env.घड़ी.घड़ीid_ns;

	वापस करो_ग_लिखो(ff, data64, माप(*data64));
पूर्ण

अटल पूर्णांक ग_लिखो_dir_क्रमmat(काष्ठा feat_fd *ff,
			    काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा perf_session *session;
	काष्ठा perf_data *data;

	session = container_of(ff->ph, काष्ठा perf_session, header);
	data = session->data;

	अगर (WARN_ON(!perf_data__is_dir(data)))
		वापस -1;

	वापस करो_ग_लिखो(ff, &data->dir.version, माप(data->dir.version));
पूर्ण

#अगर_घोषित HAVE_LIBBPF_SUPPORT
अटल पूर्णांक ग_लिखो_bpf_prog_info(काष्ठा feat_fd *ff,
			       काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा perf_env *env = &ff->ph->env;
	काष्ठा rb_root *root;
	काष्ठा rb_node *next;
	पूर्णांक ret;

	करोwn_पढ़ो(&env->bpf_progs.lock);

	ret = करो_ग_लिखो(ff, &env->bpf_progs.infos_cnt,
		       माप(env->bpf_progs.infos_cnt));
	अगर (ret < 0)
		जाओ out;

	root = &env->bpf_progs.infos;
	next = rb_first(root);
	जबतक (next) अणु
		काष्ठा bpf_prog_info_node *node;
		माप_प्रकार len;

		node = rb_entry(next, काष्ठा bpf_prog_info_node, rb_node);
		next = rb_next(&node->rb_node);
		len = माप(काष्ठा bpf_prog_info_linear) +
			node->info_linear->data_len;

		/* beक्रमe writing to file, translate address to offset */
		bpf_program__bpil_addr_to_offs(node->info_linear);
		ret = करो_ग_लिखो(ff, node->info_linear, len);
		/*
		 * translate back to address even when करो_ग_लिखो() fails,
		 * so that this function never changes the data.
		 */
		bpf_program__bpil_offs_to_addr(node->info_linear);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
out:
	up_पढ़ो(&env->bpf_progs.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_bpf_btf(काष्ठा feat_fd *ff,
			 काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा perf_env *env = &ff->ph->env;
	काष्ठा rb_root *root;
	काष्ठा rb_node *next;
	पूर्णांक ret;

	करोwn_पढ़ो(&env->bpf_progs.lock);

	ret = करो_ग_लिखो(ff, &env->bpf_progs.btfs_cnt,
		       माप(env->bpf_progs.btfs_cnt));

	अगर (ret < 0)
		जाओ out;

	root = &env->bpf_progs.btfs;
	next = rb_first(root);
	जबतक (next) अणु
		काष्ठा btf_node *node;

		node = rb_entry(next, काष्ठा btf_node, rb_node);
		next = rb_next(&node->rb_node);
		ret = करो_ग_लिखो(ff, &node->id,
			       माप(u32) * 2 + node->data_size);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
out:
	up_पढ़ो(&env->bpf_progs.lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

अटल पूर्णांक cpu_cache_level__sort(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	काष्ठा cpu_cache_level *cache_a = (काष्ठा cpu_cache_level *)a;
	काष्ठा cpu_cache_level *cache_b = (काष्ठा cpu_cache_level *)b;

	वापस cache_a->level - cache_b->level;
पूर्ण

अटल bool cpu_cache_level__cmp(काष्ठा cpu_cache_level *a, काष्ठा cpu_cache_level *b)
अणु
	अगर (a->level != b->level)
		वापस false;

	अगर (a->line_size != b->line_size)
		वापस false;

	अगर (a->sets != b->sets)
		वापस false;

	अगर (a->ways != b->ways)
		वापस false;

	अगर (म_भेद(a->type, b->type))
		वापस false;

	अगर (म_भेद(a->size, b->size))
		वापस false;

	अगर (म_भेद(a->map, b->map))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक cpu_cache_level__पढ़ो(काष्ठा cpu_cache_level *cache, u32 cpu, u16 level)
अणु
	अक्षर path[PATH_MAX], file[PATH_MAX];
	काष्ठा stat st;
	माप_प्रकार len;

	scnम_लिखो(path, PATH_MAX, "devices/system/cpu/cpu%d/cache/index%d/", cpu, level);
	scnम_लिखो(file, PATH_MAX, "%s/%s", sysfs__mountpoपूर्णांक(), path);

	अगर (stat(file, &st))
		वापस 1;

	scnम_लिखो(file, PATH_MAX, "%s/level", path);
	अगर (sysfs__पढ़ो_पूर्णांक(file, (पूर्णांक *) &cache->level))
		वापस -1;

	scnम_लिखो(file, PATH_MAX, "%s/coherency_line_size", path);
	अगर (sysfs__पढ़ो_पूर्णांक(file, (पूर्णांक *) &cache->line_size))
		वापस -1;

	scnम_लिखो(file, PATH_MAX, "%s/number_of_sets", path);
	अगर (sysfs__पढ़ो_पूर्णांक(file, (पूर्णांक *) &cache->sets))
		वापस -1;

	scnम_लिखो(file, PATH_MAX, "%s/ways_of_associativity", path);
	अगर (sysfs__पढ़ो_पूर्णांक(file, (पूर्णांक *) &cache->ways))
		वापस -1;

	scnम_लिखो(file, PATH_MAX, "%s/type", path);
	अगर (sysfs__पढ़ो_str(file, &cache->type, &len))
		वापस -1;

	cache->type[len] = 0;
	cache->type = strim(cache->type);

	scnम_लिखो(file, PATH_MAX, "%s/size", path);
	अगर (sysfs__पढ़ो_str(file, &cache->size, &len)) अणु
		zमुक्त(&cache->type);
		वापस -1;
	पूर्ण

	cache->size[len] = 0;
	cache->size = strim(cache->size);

	scnम_लिखो(file, PATH_MAX, "%s/shared_cpu_list", path);
	अगर (sysfs__पढ़ो_str(file, &cache->map, &len)) अणु
		zमुक्त(&cache->size);
		zमुक्त(&cache->type);
		वापस -1;
	पूर्ण

	cache->map[len] = 0;
	cache->map = strim(cache->map);
	वापस 0;
पूर्ण

अटल व्योम cpu_cache_level__ख_लिखो(खाता *out, काष्ठा cpu_cache_level *c)
अणु
	ख_लिखो(out, "L%d %-15s %8s [%s]\n", c->level, c->type, c->size, c->map);
पूर्ण

#घोषणा MAX_CACHE_LVL 4

अटल पूर्णांक build_caches(काष्ठा cpu_cache_level caches[], u32 *cntp)
अणु
	u32 i, cnt = 0;
	u32 nr, cpu;
	u16 level;

	nr = cpu__max_cpu();

	क्रम (cpu = 0; cpu < nr; cpu++) अणु
		क्रम (level = 0; level < MAX_CACHE_LVL; level++) अणु
			काष्ठा cpu_cache_level c;
			पूर्णांक err;

			err = cpu_cache_level__पढ़ो(&c, cpu, level);
			अगर (err < 0)
				वापस err;

			अगर (err == 1)
				अवरोध;

			क्रम (i = 0; i < cnt; i++) अणु
				अगर (cpu_cache_level__cmp(&c, &caches[i]))
					अवरोध;
			पूर्ण

			अगर (i == cnt)
				caches[cnt++] = c;
			अन्यथा
				cpu_cache_level__मुक्त(&c);
		पूर्ण
	पूर्ण
	*cntp = cnt;
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_cache(काष्ठा feat_fd *ff,
		       काष्ठा evlist *evlist __maybe_unused)
अणु
	u32 max_caches = cpu__max_cpu() * MAX_CACHE_LVL;
	काष्ठा cpu_cache_level caches[max_caches];
	u32 cnt = 0, i, version = 1;
	पूर्णांक ret;

	ret = build_caches(caches, &cnt);
	अगर (ret)
		जाओ out;

	क्विक(&caches, cnt, माप(काष्ठा cpu_cache_level), cpu_cache_level__sort);

	ret = करो_ग_लिखो(ff, &version, माप(u32));
	अगर (ret < 0)
		जाओ out;

	ret = करो_ग_लिखो(ff, &cnt, माप(u32));
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा cpu_cache_level *c = &caches[i];

		#घोषणा _W(v)					\
			ret = करो_ग_लिखो(ff, &c->v, माप(u32));	\
			अगर (ret < 0)				\
				जाओ out;

		_W(level)
		_W(line_size)
		_W(sets)
		_W(ways)
		#अघोषित _W

		#घोषणा _W(v)						\
			ret = करो_ग_लिखो_string(ff, (स्थिर अक्षर *) c->v);	\
			अगर (ret < 0)					\
				जाओ out;

		_W(type)
		_W(size)
		_W(map)
		#अघोषित _W
	पूर्ण

out:
	क्रम (i = 0; i < cnt; i++)
		cpu_cache_level__मुक्त(&caches[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_stat(काष्ठा feat_fd *ff __maybe_unused,
		      काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_sample_समय(काष्ठा feat_fd *ff,
			     काष्ठा evlist *evlist)
अणु
	पूर्णांक ret;

	ret = करो_ग_लिखो(ff, &evlist->first_sample_समय,
		       माप(evlist->first_sample_समय));
	अगर (ret < 0)
		वापस ret;

	वापस करो_ग_लिखो(ff, &evlist->last_sample_समय,
			माप(evlist->last_sample_समय));
पूर्ण


अटल पूर्णांक memory_node__पढ़ो(काष्ठा memory_node *n, अचिन्हित दीर्घ idx)
अणु
	अचिन्हित पूर्णांक phys, size = 0;
	अक्षर path[PATH_MAX];
	काष्ठा dirent *ent;
	सूची *dir;

#घोषणा क्रम_each_memory(mem, dir)					\
	जबतक ((ent = सूची_पढ़ो(dir)))					\
		अगर (म_भेद(ent->d_name, ".") &&				\
		    म_भेद(ent->d_name, "..") &&			\
		    माला_पूछो(ent->d_name, "memory%u", &mem) == 1)

	scnम_लिखो(path, PATH_MAX,
		  "%s/devices/system/node/node%lu",
		  sysfs__mountpoपूर्णांक(), idx);

	dir = सूची_खोलो(path);
	अगर (!dir) अणु
		pr_warning("failed: cant' open memory sysfs data\n");
		वापस -1;
	पूर्ण

	क्रम_each_memory(phys, dir) अणु
		size = max(phys, size);
	पूर्ण

	size++;

	n->set = biपंचांगap_alloc(size);
	अगर (!n->set) अणु
		बंद_सूची(dir);
		वापस -ENOMEM;
	पूर्ण

	n->node = idx;
	n->size = size;

	सूची_शुरु(dir);

	क्रम_each_memory(phys, dir) अणु
		set_bit(phys, n->set);
	पूर्ण

	बंद_सूची(dir);
	वापस 0;
पूर्ण

अटल पूर्णांक memory_node__sort(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा memory_node *na = a;
	स्थिर काष्ठा memory_node *nb = b;

	वापस na->node - nb->node;
पूर्ण

अटल पूर्णांक build_mem_topology(काष्ठा memory_node *nodes, u64 size, u64 *cntp)
अणु
	अक्षर path[PATH_MAX];
	काष्ठा dirent *ent;
	सूची *dir;
	u64 cnt = 0;
	पूर्णांक ret = 0;

	scnम_लिखो(path, PATH_MAX, "%s/devices/system/node/",
		  sysfs__mountpoपूर्णांक());

	dir = सूची_खोलो(path);
	अगर (!dir) अणु
		pr_debug2("%s: could't read %s, does this arch have topology information?\n",
			  __func__, path);
		वापस -1;
	पूर्ण

	जबतक (!ret && (ent = सूची_पढ़ो(dir))) अणु
		अचिन्हित पूर्णांक idx;
		पूर्णांक r;

		अगर (!म_भेद(ent->d_name, ".") ||
		    !म_भेद(ent->d_name, ".."))
			जारी;

		r = माला_पूछो(ent->d_name, "node%u", &idx);
		अगर (r != 1)
			जारी;

		अगर (WARN_ONCE(cnt >= size,
			"failed to write MEM_TOPOLOGY, way too many nodes\n")) अणु
			बंद_सूची(dir);
			वापस -1;
		पूर्ण

		ret = memory_node__पढ़ो(&nodes[cnt++], idx);
	पूर्ण

	*cntp = cnt;
	बंद_सूची(dir);

	अगर (!ret)
		क्विक(nodes, cnt, माप(nodes[0]), memory_node__sort);

	वापस ret;
पूर्ण

#घोषणा MAX_MEMORY_NODES 2000

/*
 * The MEM_TOPOLOGY holds physical memory map क्रम every
 * node in प्रणाली. The क्रमmat of data is as follows:
 *
 *  0 - version          | क्रम future changes
 *  8 - block_size_bytes | /sys/devices/प्रणाली/memory/block_size_bytes
 * 16 - count            | number of nodes
 *
 * For each node we store map of physical indexes क्रम
 * each node:
 *
 * 32 - node id          | node index
 * 40 - size             | size of biपंचांगap
 * 48 - biपंचांगap           | biपंचांगap of memory indexes that beदीर्घs to node
 */
अटल पूर्णांक ग_लिखो_mem_topology(काष्ठा feat_fd *ff __maybe_unused,
			      काष्ठा evlist *evlist __maybe_unused)
अणु
	अटल काष्ठा memory_node nodes[MAX_MEMORY_NODES];
	u64 bsize, version = 1, i, nr;
	पूर्णांक ret;

	ret = sysfs__पढ़ो_xll("devices/system/memory/block_size_bytes",
			      (अचिन्हित दीर्घ दीर्घ *) &bsize);
	अगर (ret)
		वापस ret;

	ret = build_mem_topology(&nodes[0], MAX_MEMORY_NODES, &nr);
	अगर (ret)
		वापस ret;

	ret = करो_ग_लिखो(ff, &version, माप(version));
	अगर (ret < 0)
		जाओ out;

	ret = करो_ग_लिखो(ff, &bsize, माप(bsize));
	अगर (ret < 0)
		जाओ out;

	ret = करो_ग_लिखो(ff, &nr, माप(nr));
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा memory_node *n = &nodes[i];

		#घोषणा _W(v)						\
			ret = करो_ग_लिखो(ff, &n->v, माप(n->v));	\
			अगर (ret < 0)					\
				जाओ out;

		_W(node)
		_W(size)

		#अघोषित _W

		ret = करो_ग_लिखो_biपंचांगap(ff, n->set, n->size);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_compressed(काष्ठा feat_fd *ff __maybe_unused,
			    काष्ठा evlist *evlist __maybe_unused)
अणु
	पूर्णांक ret;

	ret = करो_ग_लिखो(ff, &(ff->ph->env.comp_ver), माप(ff->ph->env.comp_ver));
	अगर (ret)
		वापस ret;

	ret = करो_ग_लिखो(ff, &(ff->ph->env.comp_type), माप(ff->ph->env.comp_type));
	अगर (ret)
		वापस ret;

	ret = करो_ग_लिखो(ff, &(ff->ph->env.comp_level), माप(ff->ph->env.comp_level));
	अगर (ret)
		वापस ret;

	ret = करो_ग_लिखो(ff, &(ff->ph->env.comp_ratio), माप(ff->ph->env.comp_ratio));
	अगर (ret)
		वापस ret;

	वापस करो_ग_लिखो(ff, &(ff->ph->env.comp_mmap_len), माप(ff->ph->env.comp_mmap_len));
पूर्ण

अटल पूर्णांक ग_लिखो_cpu_pmu_caps(काष्ठा feat_fd *ff,
			      काष्ठा evlist *evlist __maybe_unused)
अणु
	काष्ठा perf_pmu *cpu_pmu = perf_pmu__find("cpu");
	काष्ठा perf_pmu_caps *caps = शून्य;
	पूर्णांक nr_caps;
	पूर्णांक ret;

	अगर (!cpu_pmu)
		वापस -ENOENT;

	nr_caps = perf_pmu__caps_parse(cpu_pmu);
	अगर (nr_caps < 0)
		वापस nr_caps;

	ret = करो_ग_लिखो(ff, &nr_caps, माप(nr_caps));
	अगर (ret < 0)
		वापस ret;

	list_क्रम_each_entry(caps, &cpu_pmu->caps, list) अणु
		ret = करो_ग_लिखो_string(ff, caps->name);
		अगर (ret < 0)
			वापस ret;

		ret = करो_ग_लिखो_string(ff, caps->value);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम prपूर्णांक_hostname(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# hostname : %s\n", ff->ph->env.hostname);
पूर्ण

अटल व्योम prपूर्णांक_osrelease(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# os release : %s\n", ff->ph->env.os_release);
पूर्ण

अटल व्योम prपूर्णांक_arch(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# arch : %s\n", ff->ph->env.arch);
पूर्ण

अटल व्योम prपूर्णांक_cpudesc(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# cpudesc : %s\n", ff->ph->env.cpu_desc);
पूर्ण

अटल व्योम prपूर्णांक_nrcpus(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# nrcpus online : %u\n", ff->ph->env.nr_cpus_online);
	ख_लिखो(fp, "# nrcpus avail : %u\n", ff->ph->env.nr_cpus_avail);
पूर्ण

अटल व्योम prपूर्णांक_version(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# perf version : %s\n", ff->ph->env.version);
पूर्ण

अटल व्योम prपूर्णांक_cmdline(काष्ठा feat_fd *ff, खाता *fp)
अणु
	पूर्णांक nr, i;

	nr = ff->ph->env.nr_cmdline;

	ख_लिखो(fp, "# cmdline : ");

	क्रम (i = 0; i < nr; i++) अणु
		अक्षर *argv_i = strdup(ff->ph->env.cmdline_argv[i]);
		अगर (!argv_i) अणु
			ख_लिखो(fp, "%s ", ff->ph->env.cmdline_argv[i]);
		पूर्ण अन्यथा अणु
			अक्षर *mem = argv_i;
			करो अणु
				अक्षर *quote = म_अक्षर(argv_i, '\'');
				अगर (!quote)
					अवरोध;
				*quote++ = '\0';
				ख_लिखो(fp, "%s\\\'", argv_i);
				argv_i = quote;
			पूर्ण जबतक (1);
			ख_लिखो(fp, "%s ", argv_i);
			मुक्त(mem);
		पूर्ण
	पूर्ण
	ख_अक्षर_दो('\n', fp);
पूर्ण

अटल व्योम prपूर्णांक_cpu_topology(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा perf_header *ph = ff->ph;
	पूर्णांक cpu_nr = ph->env.nr_cpus_avail;
	पूर्णांक nr, i;
	अक्षर *str;

	nr = ph->env.nr_sibling_cores;
	str = ph->env.sibling_cores;

	क्रम (i = 0; i < nr; i++) अणु
		ख_लिखो(fp, "# sibling sockets : %s\n", str);
		str += म_माप(str) + 1;
	पूर्ण

	अगर (ph->env.nr_sibling_dies) अणु
		nr = ph->env.nr_sibling_dies;
		str = ph->env.sibling_dies;

		क्रम (i = 0; i < nr; i++) अणु
			ख_लिखो(fp, "# sibling dies    : %s\n", str);
			str += म_माप(str) + 1;
		पूर्ण
	पूर्ण

	nr = ph->env.nr_sibling_thपढ़ोs;
	str = ph->env.sibling_thपढ़ोs;

	क्रम (i = 0; i < nr; i++) अणु
		ख_लिखो(fp, "# sibling threads : %s\n", str);
		str += म_माप(str) + 1;
	पूर्ण

	अगर (ph->env.nr_sibling_dies) अणु
		अगर (ph->env.cpu != शून्य) अणु
			क्रम (i = 0; i < cpu_nr; i++)
				ख_लिखो(fp, "# CPU %d: Core ID %d, "
					    "Die ID %d, Socket ID %d\n",
					    i, ph->env.cpu[i].core_id,
					    ph->env.cpu[i].die_id,
					    ph->env.cpu[i].socket_id);
		पूर्ण अन्यथा
			ख_लिखो(fp, "# Core ID, Die ID and Socket ID "
				    "information is not available\n");
	पूर्ण अन्यथा अणु
		अगर (ph->env.cpu != शून्य) अणु
			क्रम (i = 0; i < cpu_nr; i++)
				ख_लिखो(fp, "# CPU %d: Core ID %d, "
					    "Socket ID %d\n",
					    i, ph->env.cpu[i].core_id,
					    ph->env.cpu[i].socket_id);
		पूर्ण अन्यथा
			ख_लिखो(fp, "# Core ID and Socket ID "
				    "information is not available\n");
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_घड़ीid(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# clockid frequency: %"PRIu64" MHz\n",
		ff->ph->env.घड़ी.घड़ीid_res_ns * 1000);
पूर्ण

अटल व्योम prपूर्णांक_घड़ी_data(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा बारpec घड़ीid_ns;
	अक्षर tstr[64], date[64];
	काष्ठा समयval tod_ns;
	घड़ीid_t घड़ीid;
	काष्ठा पंचांग lसमय;
	u64 ref;

	अगर (!ff->ph->env.घड़ी.enabled) अणु
		ख_लिखो(fp, "# reference time disabled\n");
		वापस;
	पूर्ण

	/* Compute TOD समय. */
	ref = ff->ph->env.घड़ी.tod_ns;
	tod_ns.tv_sec = ref / NSEC_PER_SEC;
	ref -= tod_ns.tv_sec * NSEC_PER_SEC;
	tod_ns.tv_usec = ref / NSEC_PER_USEC;

	/* Compute घड़ीid समय. */
	ref = ff->ph->env.घड़ी.घड़ीid_ns;
	घड़ीid_ns.tv_sec = ref / NSEC_PER_SEC;
	ref -= घड़ीid_ns.tv_sec * NSEC_PER_SEC;
	घड़ीid_ns.tv_nsec = ref;

	घड़ीid = ff->ph->env.घड़ी.घड़ीid;

	अगर (स_स्थानीय_r(&tod_ns.tv_sec, &lसमय) == शून्य)
		snम_लिखो(tstr, माप(tstr), "<error>");
	अन्यथा अणु
		स_माला(date, माप(date), "%F %T", &lसमय);
		scnम_लिखो(tstr, माप(tstr), "%s.%06d",
			  date, (पूर्णांक) tod_ns.tv_usec);
	पूर्ण

	ख_लिखो(fp, "# clockid: %s (%u)\n", घड़ीid_name(घड़ीid), घड़ीid);
	ख_लिखो(fp, "# reference time: %s = %ld.%06d (TOD) = %ld.%09ld (%s)\n",
		    tstr, (दीर्घ) tod_ns.tv_sec, (पूर्णांक) tod_ns.tv_usec,
		    (दीर्घ) घड़ीid_ns.tv_sec, घड़ीid_ns.tv_nsec,
		    घड़ीid_name(घड़ीid));
पूर्ण

अटल व्योम prपूर्णांक_dir_क्रमmat(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा perf_session *session;
	काष्ठा perf_data *data;

	session = container_of(ff->ph, काष्ठा perf_session, header);
	data = session->data;

	ख_लिखो(fp, "# directory data version : %"PRIu64"\n", data->dir.version);
पूर्ण

#अगर_घोषित HAVE_LIBBPF_SUPPORT
अटल व्योम prपूर्णांक_bpf_prog_info(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा perf_env *env = &ff->ph->env;
	काष्ठा rb_root *root;
	काष्ठा rb_node *next;

	करोwn_पढ़ो(&env->bpf_progs.lock);

	root = &env->bpf_progs.infos;
	next = rb_first(root);

	जबतक (next) अणु
		काष्ठा bpf_prog_info_node *node;

		node = rb_entry(next, काष्ठा bpf_prog_info_node, rb_node);
		next = rb_next(&node->rb_node);

		bpf_event__prपूर्णांक_bpf_prog_info(&node->info_linear->info,
					       env, fp);
	पूर्ण

	up_पढ़ो(&env->bpf_progs.lock);
पूर्ण

अटल व्योम prपूर्णांक_bpf_btf(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा perf_env *env = &ff->ph->env;
	काष्ठा rb_root *root;
	काष्ठा rb_node *next;

	करोwn_पढ़ो(&env->bpf_progs.lock);

	root = &env->bpf_progs.btfs;
	next = rb_first(root);

	जबतक (next) अणु
		काष्ठा btf_node *node;

		node = rb_entry(next, काष्ठा btf_node, rb_node);
		next = rb_next(&node->rb_node);
		ख_लिखो(fp, "# btf info of id %u\n", node->id);
	पूर्ण

	up_पढ़ो(&env->bpf_progs.lock);
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

अटल व्योम मुक्त_event_desc(काष्ठा evsel *events)
अणु
	काष्ठा evsel *evsel;

	अगर (!events)
		वापस;

	क्रम (evsel = events; evsel->core.attr.size; evsel++) अणु
		zमुक्त(&evsel->name);
		zमुक्त(&evsel->core.id);
	पूर्ण

	मुक्त(events);
पूर्ण

अटल bool perf_attr_check(काष्ठा perf_event_attr *attr)
अणु
	अगर (attr->__reserved_1 || attr->__reserved_2 || attr->__reserved_3) अणु
		pr_warning("Reserved bits are set unexpectedly. "
			   "Please update perf tool.\n");
		वापस false;
	पूर्ण

	अगर (attr->sample_type & ~(PERF_SAMPLE_MAX-1)) अणु
		pr_warning("Unknown sample type (0x%llx) is detected. "
			   "Please update perf tool.\n",
			   attr->sample_type);
		वापस false;
	पूर्ण

	अगर (attr->पढ़ो_क्रमmat & ~(PERF_FORMAT_MAX-1)) अणु
		pr_warning("Unknown read format (0x%llx) is detected. "
			   "Please update perf tool.\n",
			   attr->पढ़ो_क्रमmat);
		वापस false;
	पूर्ण

	अगर ((attr->sample_type & PERF_SAMPLE_BRANCH_STACK) &&
	    (attr->branch_sample_type & ~(PERF_SAMPLE_BRANCH_MAX-1))) अणु
		pr_warning("Unknown branch sample type (0x%llx) is detected. "
			   "Please update perf tool.\n",
			   attr->branch_sample_type);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा evsel *पढ़ो_event_desc(काष्ठा feat_fd *ff)
अणु
	काष्ठा evsel *evsel, *events = शून्य;
	u64 *id;
	व्योम *buf = शून्य;
	u32 nre, sz, nr, i, j;
	माप_प्रकार msz;

	/* number of events */
	अगर (करो_पढ़ो_u32(ff, &nre))
		जाओ error;

	अगर (करो_पढ़ो_u32(ff, &sz))
		जाओ error;

	/* buffer to hold on file attr काष्ठा */
	buf = दो_स्मृति(sz);
	अगर (!buf)
		जाओ error;

	/* the last event terminates with evsel->core.attr.size == 0: */
	events = सुस्मृति(nre + 1, माप(*events));
	अगर (!events)
		जाओ error;

	msz = माप(evsel->core.attr);
	अगर (sz < msz)
		msz = sz;

	क्रम (i = 0, evsel = events; i < nre; evsel++, i++) अणु
		evsel->idx = i;

		/*
		 * must पढ़ो entire on-file attr काष्ठा to
		 * sync up with layout.
		 */
		अगर (__करो_पढ़ो(ff, buf, sz))
			जाओ error;

		अगर (ff->ph->needs_swap)
			perf_event__attr_swap(buf);

		स_नकल(&evsel->core.attr, buf, msz);

		अगर (!perf_attr_check(&evsel->core.attr))
			जाओ error;

		अगर (करो_पढ़ो_u32(ff, &nr))
			जाओ error;

		अगर (ff->ph->needs_swap)
			evsel->needs_swap = true;

		evsel->name = करो_पढ़ो_string(ff);
		अगर (!evsel->name)
			जाओ error;

		अगर (!nr)
			जारी;

		id = सुस्मृति(nr, माप(*id));
		अगर (!id)
			जाओ error;
		evsel->core.ids = nr;
		evsel->core.id = id;

		क्रम (j = 0 ; j < nr; j++) अणु
			अगर (करो_पढ़ो_u64(ff, id))
				जाओ error;
			id++;
		पूर्ण
	पूर्ण
out:
	मुक्त(buf);
	वापस events;
error:
	मुक्त_event_desc(events);
	events = शून्य;
	जाओ out;
पूर्ण

अटल पूर्णांक __desc_attr__ख_लिखो(खाता *fp, स्थिर अक्षर *name, स्थिर अक्षर *val,
				व्योम *priv __maybe_unused)
अणु
	वापस ख_लिखो(fp, ", %s = %s", name, val);
पूर्ण

अटल व्योम prपूर्णांक_event_desc(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा evsel *evsel, *events;
	u32 j;
	u64 *id;

	अगर (ff->events)
		events = ff->events;
	अन्यथा
		events = पढ़ो_event_desc(ff);

	अगर (!events) अणु
		ख_लिखो(fp, "# event desc: not available or unable to read\n");
		वापस;
	पूर्ण

	क्रम (evsel = events; evsel->core.attr.size; evsel++) अणु
		ख_लिखो(fp, "# event : name = %s, ", evsel->name);

		अगर (evsel->core.ids) अणु
			ख_लिखो(fp, ", id = {");
			क्रम (j = 0, id = evsel->core.id; j < evsel->core.ids; j++, id++) अणु
				अगर (j)
					ख_अक्षर_दो(',', fp);
				ख_लिखो(fp, " %"PRIu64, *id);
			पूर्ण
			ख_लिखो(fp, " }");
		पूर्ण

		perf_event_attr__ख_लिखो(fp, &evsel->core.attr, __desc_attr__ख_लिखो, शून्य);

		ख_अक्षर_दो('\n', fp);
	पूर्ण

	मुक्त_event_desc(events);
	ff->events = शून्य;
पूर्ण

अटल व्योम prपूर्णांक_total_mem(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# total memory : %llu kB\n", ff->ph->env.total_mem);
पूर्ण

अटल व्योम prपूर्णांक_numa_topology(काष्ठा feat_fd *ff, खाता *fp)
अणु
	पूर्णांक i;
	काष्ठा numa_node *n;

	क्रम (i = 0; i < ff->ph->env.nr_numa_nodes; i++) अणु
		n = &ff->ph->env.numa_nodes[i];

		ख_लिखो(fp, "# node%u meminfo  : total = %"PRIu64" kB,"
			    " free = %"PRIu64" kB\n",
			n->node, n->mem_total, n->mem_मुक्त);

		ख_लिखो(fp, "# node%u cpu list : ", n->node);
		cpu_map__ख_लिखो(n->map, fp);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_cpuid(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# cpuid : %s\n", ff->ph->env.cpuid);
पूर्ण

अटल व्योम prपूर्णांक_branch_stack(काष्ठा feat_fd *ff __maybe_unused, खाता *fp)
अणु
	ख_लिखो(fp, "# contains samples with branch stack\n");
पूर्ण

अटल व्योम prपूर्णांक_auxtrace(काष्ठा feat_fd *ff __maybe_unused, खाता *fp)
अणु
	ख_लिखो(fp, "# contains AUX area data (e.g. instruction trace)\n");
पूर्ण

अटल व्योम prपूर्णांक_stat(काष्ठा feat_fd *ff __maybe_unused, खाता *fp)
अणु
	ख_लिखो(fp, "# contains stat data\n");
पूर्ण

अटल व्योम prपूर्णांक_cache(काष्ठा feat_fd *ff, खाता *fp __maybe_unused)
अणु
	पूर्णांक i;

	ख_लिखो(fp, "# CPU cache info:\n");
	क्रम (i = 0; i < ff->ph->env.caches_cnt; i++) अणु
		ख_लिखो(fp, "#  ");
		cpu_cache_level__ख_लिखो(fp, &ff->ph->env.caches[i]);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_compressed(काष्ठा feat_fd *ff, खाता *fp)
अणु
	ख_लिखो(fp, "# compressed : %s, level = %d, ratio = %d\n",
		ff->ph->env.comp_type == PERF_COMP_ZSTD ? "Zstd" : "Unknown",
		ff->ph->env.comp_level, ff->ph->env.comp_ratio);
पूर्ण

अटल व्योम prपूर्णांक_cpu_pmu_caps(काष्ठा feat_fd *ff, खाता *fp)
अणु
	स्थिर अक्षर *delimiter = "# cpu pmu capabilities: ";
	u32 nr_caps = ff->ph->env.nr_cpu_pmu_caps;
	अक्षर *str;

	अगर (!nr_caps) अणु
		ख_लिखो(fp, "# cpu pmu capabilities: not available\n");
		वापस;
	पूर्ण

	str = ff->ph->env.cpu_pmu_caps;
	जबतक (nr_caps--) अणु
		ख_लिखो(fp, "%s%s", delimiter, str);
		delimiter = ", ";
		str += म_माप(str) + 1;
	पूर्ण

	ख_लिखो(fp, "\n");
पूर्ण

अटल व्योम prपूर्णांक_pmu_mappings(काष्ठा feat_fd *ff, खाता *fp)
अणु
	स्थिर अक्षर *delimiter = "# pmu mappings: ";
	अक्षर *str, *पंचांगp;
	u32 pmu_num;
	u32 type;

	pmu_num = ff->ph->env.nr_pmu_mappings;
	अगर (!pmu_num) अणु
		ख_लिखो(fp, "# pmu mappings: not available\n");
		वापस;
	पूर्ण

	str = ff->ph->env.pmu_mappings;

	जबतक (pmu_num) अणु
		type = म_से_अदीर्घ(str, &पंचांगp, 0);
		अगर (*पंचांगp != ':')
			जाओ error;

		str = पंचांगp + 1;
		ख_लिखो(fp, "%s%s = %" PRIu32, delimiter, str, type);

		delimiter = ", ";
		str += म_माप(str) + 1;
		pmu_num--;
	पूर्ण

	ख_लिखो(fp, "\n");

	अगर (!pmu_num)
		वापस;
error:
	ख_लिखो(fp, "# pmu mappings: unable to read\n");
पूर्ण

अटल व्योम prपूर्णांक_group_desc(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा perf_session *session;
	काष्ठा evsel *evsel;
	u32 nr = 0;

	session = container_of(ff->ph, काष्ठा perf_session, header);

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (evsel__is_group_leader(evsel) && evsel->core.nr_members > 1) अणु
			ख_लिखो(fp, "# group: %s{%s", evsel->group_name ?: "", evsel__name(evsel));

			nr = evsel->core.nr_members - 1;
		पूर्ण अन्यथा अगर (nr) अणु
			ख_लिखो(fp, ",%s", evsel__name(evsel));

			अगर (--nr == 0)
				ख_लिखो(fp, "}\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_sample_समय(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा perf_session *session;
	अक्षर समय_buf[32];
	द्विगुन d;

	session = container_of(ff->ph, काष्ठा perf_session, header);

	बारtamp__scnम_लिखो_usec(session->evlist->first_sample_समय,
				  समय_buf, माप(समय_buf));
	ख_लिखो(fp, "# time of first sample : %s\n", समय_buf);

	बारtamp__scnम_लिखो_usec(session->evlist->last_sample_समय,
				  समय_buf, माप(समय_buf));
	ख_लिखो(fp, "# time of last sample : %s\n", समय_buf);

	d = (द्विगुन)(session->evlist->last_sample_समय -
		session->evlist->first_sample_समय) / NSEC_PER_MSEC;

	ख_लिखो(fp, "# sample duration : %10.3f ms\n", d);
पूर्ण

अटल व्योम memory_node__ख_लिखो(काष्ठा memory_node *n,
				 अचिन्हित दीर्घ दीर्घ bsize, खाता *fp)
अणु
	अक्षर buf_map[100], buf_size[50];
	अचिन्हित दीर्घ दीर्घ size;

	size = bsize * biपंचांगap_weight(n->set, n->size);
	unit_number__scnम_लिखो(buf_size, 50, size);

	biपंचांगap_scnम_लिखो(n->set, n->size, buf_map, 100);
	ख_लिखो(fp, "#  %3" PRIu64 " [%s]: %s\n", n->node, buf_size, buf_map);
पूर्ण

अटल व्योम prपूर्णांक_mem_topology(काष्ठा feat_fd *ff, खाता *fp)
अणु
	काष्ठा memory_node *nodes;
	पूर्णांक i, nr;

	nodes = ff->ph->env.memory_nodes;
	nr    = ff->ph->env.nr_memory_nodes;

	ख_लिखो(fp, "# memory nodes (nr %d, block size 0x%llx):\n",
		nr, ff->ph->env.memory_bsize);

	क्रम (i = 0; i < nr; i++) अणु
		memory_node__ख_लिखो(&nodes[i], ff->ph->env.memory_bsize, fp);
	पूर्ण
पूर्ण

अटल पूर्णांक __event_process_build_id(काष्ठा perf_record_header_build_id *bev,
				    अक्षर *filename,
				    काष्ठा perf_session *session)
अणु
	पूर्णांक err = -1;
	काष्ठा machine *machine;
	u16 cpumode;
	काष्ठा dso *dso;
	क्रमागत dso_space_type dso_space;

	machine = perf_session__findnew_machine(session, bev->pid);
	अगर (!machine)
		जाओ out;

	cpumode = bev->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;

	चयन (cpumode) अणु
	हाल PERF_RECORD_MISC_KERNEL:
		dso_space = DSO_SPACE__KERNEL;
		अवरोध;
	हाल PERF_RECORD_MISC_GUEST_KERNEL:
		dso_space = DSO_SPACE__KERNEL_GUEST;
		अवरोध;
	हाल PERF_RECORD_MISC_USER:
	हाल PERF_RECORD_MISC_GUEST_USER:
		dso_space = DSO_SPACE__USER;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	dso = machine__findnew_dso(machine, filename);
	अगर (dso != शून्य) अणु
		अक्षर sbuild_id[SBUILD_ID_SIZE];
		काष्ठा build_id bid;
		माप_प्रकार size = BUILD_ID_SIZE;

		अगर (bev->header.misc & PERF_RECORD_MISC_BUILD_ID_SIZE)
			size = bev->size;

		build_id__init(&bid, bev->data, size);
		dso__set_build_id(dso, &bid);

		अगर (dso_space != DSO_SPACE__USER) अणु
			काष्ठा kmod_path m = अणु .name = शून्य, पूर्ण;

			अगर (!kmod_path__parse_name(&m, filename) && m.kmod)
				dso__set_module_info(dso, &m, machine);

			dso->kernel = dso_space;
			मुक्त(m.name);
		पूर्ण

		build_id__प्र_लिखो(&dso->bid, sbuild_id);
		pr_debug("build id event received for %s: %s [%zu]\n",
			 dso->दीर्घ_name, sbuild_id, size);
		dso__put(dso);
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक perf_header__पढ़ो_build_ids_abi_quirk(काष्ठा perf_header *header,
						 पूर्णांक input, u64 offset, u64 size)
अणु
	काष्ठा perf_session *session = container_of(header, काष्ठा perf_session, header);
	काष्ठा अणु
		काष्ठा perf_event_header   header;
		u8			   build_id[PERF_ALIGN(BUILD_ID_SIZE, माप(u64))];
		अक्षर			   filename[0];
	पूर्ण old_bev;
	काष्ठा perf_record_header_build_id bev;
	अक्षर filename[PATH_MAX];
	u64 limit = offset + size;

	जबतक (offset < limit) अणु
		sमाप_प्रकार len;

		अगर (पढ़ोn(input, &old_bev, माप(old_bev)) != माप(old_bev))
			वापस -1;

		अगर (header->needs_swap)
			perf_event_header__bswap(&old_bev.header);

		len = old_bev.header.size - माप(old_bev);
		अगर (पढ़ोn(input, filename, len) != len)
			वापस -1;

		bev.header = old_bev.header;

		/*
		 * As the pid is the missing value, we need to fill
		 * it properly. The header.misc value give us nice hपूर्णांक.
		 */
		bev.pid	= HOST_KERNEL_ID;
		अगर (bev.header.misc == PERF_RECORD_MISC_GUEST_USER ||
		    bev.header.misc == PERF_RECORD_MISC_GUEST_KERNEL)
			bev.pid	= DEFAULT_GUEST_KERNEL_ID;

		स_नकल(bev.build_id, old_bev.build_id, माप(bev.build_id));
		__event_process_build_id(&bev, filename, session);

		offset += bev.header.size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_header__पढ़ो_build_ids(काष्ठा perf_header *header,
				       पूर्णांक input, u64 offset, u64 size)
अणु
	काष्ठा perf_session *session = container_of(header, काष्ठा perf_session, header);
	काष्ठा perf_record_header_build_id bev;
	अक्षर filename[PATH_MAX];
	u64 limit = offset + size, orig_offset = offset;
	पूर्णांक err = -1;

	जबतक (offset < limit) अणु
		sमाप_प्रकार len;

		अगर (पढ़ोn(input, &bev, माप(bev)) != माप(bev))
			जाओ out;

		अगर (header->needs_swap)
			perf_event_header__bswap(&bev.header);

		len = bev.header.size - माप(bev);
		अगर (पढ़ोn(input, filename, len) != len)
			जाओ out;
		/*
		 * The a1645ce1 changeset:
		 *
		 * "perf: 'perf kvm' tool for monitoring guest performance from host"
		 *
		 * Added a field to काष्ठा perf_record_header_build_id that broke the file
		 * क्रमmat.
		 *
		 * Since the kernel build-id is the first entry, process the
		 * table using the old क्रमmat अगर the well known
		 * '[kernel.kallsyms]' string क्रम the kernel build-id has the
		 * first 4 अक्षरacters chopped off (where the pid_t sits).
		 */
		अगर (स_भेद(filename, "nel.kallsyms]", 13) == 0) अणु
			अगर (lseek(input, orig_offset, शुरू_से) == (off_t)-1)
				वापस -1;
			वापस perf_header__पढ़ो_build_ids_abi_quirk(header, input, offset, size);
		पूर्ण

		__event_process_build_id(&bev, filename, session);

		offset += bev.header.size;
	पूर्ण
	err = 0;
out:
	वापस err;
पूर्ण

/* Macro क्रम features that simply need to पढ़ो and store a string. */
#घोषणा FEAT_PROCESS_STR_FUN(__feat, __feat_env) \
अटल पूर्णांक process_##__feat(काष्ठा feat_fd *ff, व्योम *data __maybe_unused) \
अणु\
	ff->ph->env.__feat_env = करो_पढ़ो_string(ff); \
	वापस ff->ph->env.__feat_env ? 0 : -ENOMEM; \
पूर्ण

FEAT_PROCESS_STR_FUN(hostname, hostname);
FEAT_PROCESS_STR_FUN(osrelease, os_release);
FEAT_PROCESS_STR_FUN(version, version);
FEAT_PROCESS_STR_FUN(arch, arch);
FEAT_PROCESS_STR_FUN(cpudesc, cpu_desc);
FEAT_PROCESS_STR_FUN(cpuid, cpuid);

अटल पूर्णांक process_tracing_data(काष्ठा feat_fd *ff, व्योम *data)
अणु
	sमाप_प्रकार ret = trace_report(ff->fd, data, false);

	वापस ret < 0 ? -1 : 0;
पूर्ण

अटल पूर्णांक process_build_id(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	अगर (perf_header__पढ़ो_build_ids(ff->ph, ff->fd, ff->offset, ff->size))
		pr_debug("Failed to read buildids, continuing...\n");
	वापस 0;
पूर्ण

अटल पूर्णांक process_nrcpus(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	पूर्णांक ret;
	u32 nr_cpus_avail, nr_cpus_online;

	ret = करो_पढ़ो_u32(ff, &nr_cpus_avail);
	अगर (ret)
		वापस ret;

	ret = करो_पढ़ो_u32(ff, &nr_cpus_online);
	अगर (ret)
		वापस ret;
	ff->ph->env.nr_cpus_avail = (पूर्णांक)nr_cpus_avail;
	ff->ph->env.nr_cpus_online = (पूर्णांक)nr_cpus_online;
	वापस 0;
पूर्ण

अटल पूर्णांक process_total_mem(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	u64 total_mem;
	पूर्णांक ret;

	ret = करो_पढ़ो_u64(ff, &total_mem);
	अगर (ret)
		वापस -1;
	ff->ph->env.total_mem = (अचिन्हित दीर्घ दीर्घ)total_mem;
	वापस 0;
पूर्ण

अटल काष्ठा evsel *evlist__find_by_index(काष्ठा evlist *evlist, पूर्णांक idx)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->idx == idx)
			वापस evsel;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम evlist__set_event_name(काष्ठा evlist *evlist, काष्ठा evsel *event)
अणु
	काष्ठा evsel *evsel;

	अगर (!event->name)
		वापस;

	evsel = evlist__find_by_index(evlist, event->idx);
	अगर (!evsel)
		वापस;

	अगर (evsel->name)
		वापस;

	evsel->name = strdup(event->name);
पूर्ण

अटल पूर्णांक
process_event_desc(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	काष्ठा perf_session *session;
	काष्ठा evsel *evsel, *events = पढ़ो_event_desc(ff);

	अगर (!events)
		वापस 0;

	session = container_of(ff->ph, काष्ठा perf_session, header);

	अगर (session->data->is_pipe) अणु
		/* Save events क्रम पढ़ोing later by prपूर्णांक_event_desc,
		 * since they can't be पढ़ो again in pipe mode. */
		ff->events = events;
	पूर्ण

	क्रम (evsel = events; evsel->core.attr.size; evsel++)
		evlist__set_event_name(session->evlist, evsel);

	अगर (!session->data->is_pipe)
		मुक्त_event_desc(events);

	वापस 0;
पूर्ण

अटल पूर्णांक process_cmdline(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	अक्षर *str, *cmdline = शून्य, **argv = शून्य;
	u32 nr, i, len = 0;

	अगर (करो_पढ़ो_u32(ff, &nr))
		वापस -1;

	ff->ph->env.nr_cmdline = nr;

	cmdline = zalloc(ff->size + nr + 1);
	अगर (!cmdline)
		वापस -1;

	argv = zalloc(माप(अक्षर *) * (nr + 1));
	अगर (!argv)
		जाओ error;

	क्रम (i = 0; i < nr; i++) अणु
		str = करो_पढ़ो_string(ff);
		अगर (!str)
			जाओ error;

		argv[i] = cmdline + len;
		स_नकल(argv[i], str, म_माप(str) + 1);
		len += म_माप(str) + 1;
		मुक्त(str);
	पूर्ण
	ff->ph->env.cmdline = cmdline;
	ff->ph->env.cmdline_argv = (स्थिर अक्षर **) argv;
	वापस 0;

error:
	मुक्त(argv);
	मुक्त(cmdline);
	वापस -1;
पूर्ण

अटल पूर्णांक process_cpu_topology(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	u32 nr, i;
	अक्षर *str;
	काष्ठा strbuf sb;
	पूर्णांक cpu_nr = ff->ph->env.nr_cpus_avail;
	u64 size = 0;
	काष्ठा perf_header *ph = ff->ph;
	bool करो_core_id_test = true;

	ph->env.cpu = सुस्मृति(cpu_nr, माप(*ph->env.cpu));
	अगर (!ph->env.cpu)
		वापस -1;

	अगर (करो_पढ़ो_u32(ff, &nr))
		जाओ मुक्त_cpu;

	ph->env.nr_sibling_cores = nr;
	size += माप(u32);
	अगर (strbuf_init(&sb, 128) < 0)
		जाओ मुक्त_cpu;

	क्रम (i = 0; i < nr; i++) अणु
		str = करो_पढ़ो_string(ff);
		अगर (!str)
			जाओ error;

		/* include a शून्य अक्षरacter at the end */
		अगर (strbuf_add(&sb, str, म_माप(str) + 1) < 0)
			जाओ error;
		size += string_size(str);
		मुक्त(str);
	पूर्ण
	ph->env.sibling_cores = strbuf_detach(&sb, शून्य);

	अगर (करो_पढ़ो_u32(ff, &nr))
		वापस -1;

	ph->env.nr_sibling_thपढ़ोs = nr;
	size += माप(u32);

	क्रम (i = 0; i < nr; i++) अणु
		str = करो_पढ़ो_string(ff);
		अगर (!str)
			जाओ error;

		/* include a शून्य अक्षरacter at the end */
		अगर (strbuf_add(&sb, str, म_माप(str) + 1) < 0)
			जाओ error;
		size += string_size(str);
		मुक्त(str);
	पूर्ण
	ph->env.sibling_thपढ़ोs = strbuf_detach(&sb, शून्य);

	/*
	 * The header may be from old perf,
	 * which करोesn't include core id and socket id inक्रमmation.
	 */
	अगर (ff->size <= size) अणु
		zमुक्त(&ph->env.cpu);
		वापस 0;
	पूर्ण

	/* On s390 the socket_id number is not related to the numbers of cpus.
	 * The socket_id number might be higher than the numbers of cpus.
	 * This depends on the configuration.
	 * AArch64 is the same.
	 */
	अगर (ph->env.arch && (!म_भेदन(ph->env.arch, "s390", 4)
			  || !म_भेदन(ph->env.arch, "aarch64", 7)))
		करो_core_id_test = false;

	क्रम (i = 0; i < (u32)cpu_nr; i++) अणु
		अगर (करो_पढ़ो_u32(ff, &nr))
			जाओ मुक्त_cpu;

		ph->env.cpu[i].core_id = nr;
		size += माप(u32);

		अगर (करो_पढ़ो_u32(ff, &nr))
			जाओ मुक्त_cpu;

		अगर (करो_core_id_test && nr != (u32)-1 && nr > (u32)cpu_nr) अणु
			pr_debug("socket_id number is too big."
				 "You may need to upgrade the perf tool.\n");
			जाओ मुक्त_cpu;
		पूर्ण

		ph->env.cpu[i].socket_id = nr;
		size += माप(u32);
	पूर्ण

	/*
	 * The header may be from old perf,
	 * which करोesn't include die inक्रमmation.
	 */
	अगर (ff->size <= size)
		वापस 0;

	अगर (करो_पढ़ो_u32(ff, &nr))
		वापस -1;

	ph->env.nr_sibling_dies = nr;
	size += माप(u32);

	क्रम (i = 0; i < nr; i++) अणु
		str = करो_पढ़ो_string(ff);
		अगर (!str)
			जाओ error;

		/* include a शून्य अक्षरacter at the end */
		अगर (strbuf_add(&sb, str, म_माप(str) + 1) < 0)
			जाओ error;
		size += string_size(str);
		मुक्त(str);
	पूर्ण
	ph->env.sibling_dies = strbuf_detach(&sb, शून्य);

	क्रम (i = 0; i < (u32)cpu_nr; i++) अणु
		अगर (करो_पढ़ो_u32(ff, &nr))
			जाओ मुक्त_cpu;

		ph->env.cpu[i].die_id = nr;
	पूर्ण

	वापस 0;

error:
	strbuf_release(&sb);
मुक्त_cpu:
	zमुक्त(&ph->env.cpu);
	वापस -1;
पूर्ण

अटल पूर्णांक process_numa_topology(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	काष्ठा numa_node *nodes, *n;
	u32 nr, i;
	अक्षर *str;

	/* nr nodes */
	अगर (करो_पढ़ो_u32(ff, &nr))
		वापस -1;

	nodes = zalloc(माप(*nodes) * nr);
	अगर (!nodes)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr; i++) अणु
		n = &nodes[i];

		/* node number */
		अगर (करो_पढ़ो_u32(ff, &n->node))
			जाओ error;

		अगर (करो_पढ़ो_u64(ff, &n->mem_total))
			जाओ error;

		अगर (करो_पढ़ो_u64(ff, &n->mem_मुक्त))
			जाओ error;

		str = करो_पढ़ो_string(ff);
		अगर (!str)
			जाओ error;

		n->map = perf_cpu_map__new(str);
		अगर (!n->map)
			जाओ error;

		मुक्त(str);
	पूर्ण
	ff->ph->env.nr_numa_nodes = nr;
	ff->ph->env.numa_nodes = nodes;
	वापस 0;

error:
	मुक्त(nodes);
	वापस -1;
पूर्ण

अटल पूर्णांक process_pmu_mappings(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	अक्षर *name;
	u32 pmu_num;
	u32 type;
	काष्ठा strbuf sb;

	अगर (करो_पढ़ो_u32(ff, &pmu_num))
		वापस -1;

	अगर (!pmu_num) अणु
		pr_debug("pmu mappings not available\n");
		वापस 0;
	पूर्ण

	ff->ph->env.nr_pmu_mappings = pmu_num;
	अगर (strbuf_init(&sb, 128) < 0)
		वापस -1;

	जबतक (pmu_num) अणु
		अगर (करो_पढ़ो_u32(ff, &type))
			जाओ error;

		name = करो_पढ़ो_string(ff);
		अगर (!name)
			जाओ error;

		अगर (strbuf_addf(&sb, "%u:%s", type, name) < 0)
			जाओ error;
		/* include a शून्य अक्षरacter at the end */
		अगर (strbuf_add(&sb, "", 1) < 0)
			जाओ error;

		अगर (!म_भेद(name, "msr"))
			ff->ph->env.msr_pmu_type = type;

		मुक्त(name);
		pmu_num--;
	पूर्ण
	ff->ph->env.pmu_mappings = strbuf_detach(&sb, शून्य);
	वापस 0;

error:
	strbuf_release(&sb);
	वापस -1;
पूर्ण

अटल पूर्णांक process_group_desc(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	माप_प्रकार ret = -1;
	u32 i, nr, nr_groups;
	काष्ठा perf_session *session;
	काष्ठा evsel *evsel, *leader = शून्य;
	काष्ठा group_desc अणु
		अक्षर *name;
		u32 leader_idx;
		u32 nr_members;
	पूर्ण *desc;

	अगर (करो_पढ़ो_u32(ff, &nr_groups))
		वापस -1;

	ff->ph->env.nr_groups = nr_groups;
	अगर (!nr_groups) अणु
		pr_debug("group desc not available\n");
		वापस 0;
	पूर्ण

	desc = सुस्मृति(nr_groups, माप(*desc));
	अगर (!desc)
		वापस -1;

	क्रम (i = 0; i < nr_groups; i++) अणु
		desc[i].name = करो_पढ़ो_string(ff);
		अगर (!desc[i].name)
			जाओ out_मुक्त;

		अगर (करो_पढ़ो_u32(ff, &desc[i].leader_idx))
			जाओ out_मुक्त;

		अगर (करो_पढ़ो_u32(ff, &desc[i].nr_members))
			जाओ out_मुक्त;
	पूर्ण

	/*
	 * Rebuild group relationship based on the group_desc
	 */
	session = container_of(ff->ph, काष्ठा perf_session, header);
	session->evlist->nr_groups = nr_groups;

	i = nr = 0;
	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (evsel->idx == (पूर्णांक) desc[i].leader_idx) अणु
			evsel->leader = evsel;
			/* अणुanon_groupपूर्ण is a dummy name */
			अगर (म_भेद(desc[i].name, "{anon_group}")) अणु
				evsel->group_name = desc[i].name;
				desc[i].name = शून्य;
			पूर्ण
			evsel->core.nr_members = desc[i].nr_members;

			अगर (i >= nr_groups || nr > 0) अणु
				pr_debug("invalid group desc\n");
				जाओ out_मुक्त;
			पूर्ण

			leader = evsel;
			nr = evsel->core.nr_members - 1;
			i++;
		पूर्ण अन्यथा अगर (nr) अणु
			/* This is a group member */
			evsel->leader = leader;

			nr--;
		पूर्ण
	पूर्ण

	अगर (i != nr_groups || nr != 0) अणु
		pr_debug("invalid group desc\n");
		जाओ out_मुक्त;
	पूर्ण

	ret = 0;
out_मुक्त:
	क्रम (i = 0; i < nr_groups; i++)
		zमुक्त(&desc[i].name);
	मुक्त(desc);

	वापस ret;
पूर्ण

अटल पूर्णांक process_auxtrace(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	काष्ठा perf_session *session;
	पूर्णांक err;

	session = container_of(ff->ph, काष्ठा perf_session, header);

	err = auxtrace_index__process(ff->fd, ff->size, session,
				      ff->ph->needs_swap);
	अगर (err < 0)
		pr_err("Failed to process auxtrace index\n");
	वापस err;
पूर्ण

अटल पूर्णांक process_cache(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	काष्ठा cpu_cache_level *caches;
	u32 cnt, i, version;

	अगर (करो_पढ़ो_u32(ff, &version))
		वापस -1;

	अगर (version != 1)
		वापस -1;

	अगर (करो_पढ़ो_u32(ff, &cnt))
		वापस -1;

	caches = zalloc(माप(*caches) * cnt);
	अगर (!caches)
		वापस -1;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा cpu_cache_level c;

		#घोषणा _R(v)						\
			अगर (करो_पढ़ो_u32(ff, &c.v))\
				जाओ out_मुक्त_caches;			\

		_R(level)
		_R(line_size)
		_R(sets)
		_R(ways)
		#अघोषित _R

		#घोषणा _R(v)					\
			c.v = करो_पढ़ो_string(ff);		\
			अगर (!c.v)				\
				जाओ out_मुक्त_caches;

		_R(type)
		_R(size)
		_R(map)
		#अघोषित _R

		caches[i] = c;
	पूर्ण

	ff->ph->env.caches = caches;
	ff->ph->env.caches_cnt = cnt;
	वापस 0;
out_मुक्त_caches:
	मुक्त(caches);
	वापस -1;
पूर्ण

अटल पूर्णांक process_sample_समय(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	काष्ठा perf_session *session;
	u64 first_sample_समय, last_sample_समय;
	पूर्णांक ret;

	session = container_of(ff->ph, काष्ठा perf_session, header);

	ret = करो_पढ़ो_u64(ff, &first_sample_समय);
	अगर (ret)
		वापस -1;

	ret = करो_पढ़ो_u64(ff, &last_sample_समय);
	अगर (ret)
		वापस -1;

	session->evlist->first_sample_समय = first_sample_समय;
	session->evlist->last_sample_समय = last_sample_समय;
	वापस 0;
पूर्ण

अटल पूर्णांक process_mem_topology(काष्ठा feat_fd *ff,
				व्योम *data __maybe_unused)
अणु
	काष्ठा memory_node *nodes;
	u64 version, i, nr, bsize;
	पूर्णांक ret = -1;

	अगर (करो_पढ़ो_u64(ff, &version))
		वापस -1;

	अगर (version != 1)
		वापस -1;

	अगर (करो_पढ़ो_u64(ff, &bsize))
		वापस -1;

	अगर (करो_पढ़ो_u64(ff, &nr))
		वापस -1;

	nodes = zalloc(माप(*nodes) * nr);
	अगर (!nodes)
		वापस -1;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा memory_node n;

		#घोषणा _R(v)				\
			अगर (करो_पढ़ो_u64(ff, &n.v))	\
				जाओ out;		\

		_R(node)
		_R(size)

		#अघोषित _R

		अगर (करो_पढ़ो_biपंचांगap(ff, &n.set, &n.size))
			जाओ out;

		nodes[i] = n;
	पूर्ण

	ff->ph->env.memory_bsize    = bsize;
	ff->ph->env.memory_nodes    = nodes;
	ff->ph->env.nr_memory_nodes = nr;
	ret = 0;

out:
	अगर (ret)
		मुक्त(nodes);
	वापस ret;
पूर्ण

अटल पूर्णांक process_घड़ीid(काष्ठा feat_fd *ff,
			   व्योम *data __maybe_unused)
अणु
	अगर (करो_पढ़ो_u64(ff, &ff->ph->env.घड़ी.घड़ीid_res_ns))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक process_घड़ी_data(काष्ठा feat_fd *ff,
			      व्योम *_data __maybe_unused)
अणु
	u32 data32;
	u64 data64;

	/* version */
	अगर (करो_पढ़ो_u32(ff, &data32))
		वापस -1;

	अगर (data32 != 1)
		वापस -1;

	/* घड़ीid */
	अगर (करो_पढ़ो_u32(ff, &data32))
		वापस -1;

	ff->ph->env.घड़ी.घड़ीid = data32;

	/* TOD ref समय */
	अगर (करो_पढ़ो_u64(ff, &data64))
		वापस -1;

	ff->ph->env.घड़ी.tod_ns = data64;

	/* घड़ीid ref समय */
	अगर (करो_पढ़ो_u64(ff, &data64))
		वापस -1;

	ff->ph->env.घड़ी.घड़ीid_ns = data64;
	ff->ph->env.घड़ी.enabled = true;
	वापस 0;
पूर्ण

अटल पूर्णांक process_dir_क्रमmat(काष्ठा feat_fd *ff,
			      व्योम *_data __maybe_unused)
अणु
	काष्ठा perf_session *session;
	काष्ठा perf_data *data;

	session = container_of(ff->ph, काष्ठा perf_session, header);
	data = session->data;

	अगर (WARN_ON(!perf_data__is_dir(data)))
		वापस -1;

	वापस करो_पढ़ो_u64(ff, &data->dir.version);
पूर्ण

#अगर_घोषित HAVE_LIBBPF_SUPPORT
अटल पूर्णांक process_bpf_prog_info(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_prog_info_node *info_node;
	काष्ठा perf_env *env = &ff->ph->env;
	u32 count, i;
	पूर्णांक err = -1;

	अगर (ff->ph->needs_swap) अणु
		pr_warning("interpreting bpf_prog_info from systems with endianness is not yet supported\n");
		वापस 0;
	पूर्ण

	अगर (करो_पढ़ो_u32(ff, &count))
		वापस -1;

	करोwn_ग_लिखो(&env->bpf_progs.lock);

	क्रम (i = 0; i < count; ++i) अणु
		u32 info_len, data_len;

		info_linear = शून्य;
		info_node = शून्य;
		अगर (करो_पढ़ो_u32(ff, &info_len))
			जाओ out;
		अगर (करो_पढ़ो_u32(ff, &data_len))
			जाओ out;

		अगर (info_len > माप(काष्ठा bpf_prog_info)) अणु
			pr_warning("detected invalid bpf_prog_info\n");
			जाओ out;
		पूर्ण

		info_linear = दो_स्मृति(माप(काष्ठा bpf_prog_info_linear) +
				     data_len);
		अगर (!info_linear)
			जाओ out;
		info_linear->info_len = माप(काष्ठा bpf_prog_info);
		info_linear->data_len = data_len;
		अगर (करो_पढ़ो_u64(ff, (u64 *)(&info_linear->arrays)))
			जाओ out;
		अगर (__करो_पढ़ो(ff, &info_linear->info, info_len))
			जाओ out;
		अगर (info_len < माप(काष्ठा bpf_prog_info))
			स_रखो(((व्योम *)(&info_linear->info)) + info_len, 0,
			       माप(काष्ठा bpf_prog_info) - info_len);

		अगर (__करो_पढ़ो(ff, info_linear->data, data_len))
			जाओ out;

		info_node = दो_स्मृति(माप(काष्ठा bpf_prog_info_node));
		अगर (!info_node)
			जाओ out;

		/* after पढ़ोing from file, translate offset to address */
		bpf_program__bpil_offs_to_addr(info_linear);
		info_node->info_linear = info_linear;
		perf_env__insert_bpf_prog_info(env, info_node);
	पूर्ण

	up_ग_लिखो(&env->bpf_progs.lock);
	वापस 0;
out:
	मुक्त(info_linear);
	मुक्त(info_node);
	up_ग_लिखो(&env->bpf_progs.lock);
	वापस err;
पूर्ण

अटल पूर्णांक process_bpf_btf(काष्ठा feat_fd *ff, व्योम *data __maybe_unused)
अणु
	काष्ठा perf_env *env = &ff->ph->env;
	काष्ठा btf_node *node = शून्य;
	u32 count, i;
	पूर्णांक err = -1;

	अगर (ff->ph->needs_swap) अणु
		pr_warning("interpreting btf from systems with endianness is not yet supported\n");
		वापस 0;
	पूर्ण

	अगर (करो_पढ़ो_u32(ff, &count))
		वापस -1;

	करोwn_ग_लिखो(&env->bpf_progs.lock);

	क्रम (i = 0; i < count; ++i) अणु
		u32 id, data_size;

		अगर (करो_पढ़ो_u32(ff, &id))
			जाओ out;
		अगर (करो_पढ़ो_u32(ff, &data_size))
			जाओ out;

		node = दो_स्मृति(माप(काष्ठा btf_node) + data_size);
		अगर (!node)
			जाओ out;

		node->id = id;
		node->data_size = data_size;

		अगर (__करो_पढ़ो(ff, node->data, data_size))
			जाओ out;

		perf_env__insert_btf(env, node);
		node = शून्य;
	पूर्ण

	err = 0;
out:
	up_ग_लिखो(&env->bpf_progs.lock);
	मुक्त(node);
	वापस err;
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

अटल पूर्णांक process_compressed(काष्ठा feat_fd *ff,
			      व्योम *data __maybe_unused)
अणु
	अगर (करो_पढ़ो_u32(ff, &(ff->ph->env.comp_ver)))
		वापस -1;

	अगर (करो_पढ़ो_u32(ff, &(ff->ph->env.comp_type)))
		वापस -1;

	अगर (करो_पढ़ो_u32(ff, &(ff->ph->env.comp_level)))
		वापस -1;

	अगर (करो_पढ़ो_u32(ff, &(ff->ph->env.comp_ratio)))
		वापस -1;

	अगर (करो_पढ़ो_u32(ff, &(ff->ph->env.comp_mmap_len)))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक process_cpu_pmu_caps(काष्ठा feat_fd *ff,
				व्योम *data __maybe_unused)
अणु
	अक्षर *name, *value;
	काष्ठा strbuf sb;
	u32 nr_caps;

	अगर (करो_पढ़ो_u32(ff, &nr_caps))
		वापस -1;

	अगर (!nr_caps) अणु
		pr_debug("cpu pmu capabilities not available\n");
		वापस 0;
	पूर्ण

	ff->ph->env.nr_cpu_pmu_caps = nr_caps;

	अगर (strbuf_init(&sb, 128) < 0)
		वापस -1;

	जबतक (nr_caps--) अणु
		name = करो_पढ़ो_string(ff);
		अगर (!name)
			जाओ error;

		value = करो_पढ़ो_string(ff);
		अगर (!value)
			जाओ मुक्त_name;

		अगर (strbuf_addf(&sb, "%s=%s", name, value) < 0)
			जाओ मुक्त_value;

		/* include a शून्य अक्षरacter at the end */
		अगर (strbuf_add(&sb, "", 1) < 0)
			जाओ मुक्त_value;

		अगर (!म_भेद(name, "branches"))
			ff->ph->env.max_branches = म_से_प(value);

		मुक्त(value);
		मुक्त(name);
	पूर्ण
	ff->ph->env.cpu_pmu_caps = strbuf_detach(&sb, शून्य);
	वापस 0;

मुक्त_value:
	मुक्त(value);
मुक्त_name:
	मुक्त(name);
error:
	strbuf_release(&sb);
	वापस -1;
पूर्ण

#घोषणा FEAT_OPR(n, func, __full_only) \
	[HEADER_##n] = अणु					\
		.name	    = __stringअगरy(n),			\
		.ग_लिखो	    = ग_लिखो_##func,			\
		.prपूर्णांक	    = prपूर्णांक_##func,			\
		.full_only  = __full_only,			\
		.process    = process_##func,			\
		.synthesize = true				\
	पूर्ण

#घोषणा FEAT_OPN(n, func, __full_only) \
	[HEADER_##n] = अणु					\
		.name	    = __stringअगरy(n),			\
		.ग_लिखो	    = ग_लिखो_##func,			\
		.prपूर्णांक	    = prपूर्णांक_##func,			\
		.full_only  = __full_only,			\
		.process    = process_##func			\
	पूर्ण

/* feature_ops not implemented: */
#घोषणा prपूर्णांक_tracing_data	शून्य
#घोषणा prपूर्णांक_build_id		शून्य

#घोषणा process_branch_stack	शून्य
#घोषणा process_stat		शून्य

// Only used in util/synthetic-events.c
स्थिर काष्ठा perf_header_feature_ops feat_ops[HEADER_LAST_FEATURE];

स्थिर काष्ठा perf_header_feature_ops feat_ops[HEADER_LAST_FEATURE] = अणु
	FEAT_OPN(TRACING_DATA,	tracing_data,	false),
	FEAT_OPN(BUILD_ID,	build_id,	false),
	FEAT_OPR(HOSTNAME,	hostname,	false),
	FEAT_OPR(OSRELEASE,	osrelease,	false),
	FEAT_OPR(VERSION,	version,	false),
	FEAT_OPR(ARCH,		arch,		false),
	FEAT_OPR(NRCPUS,	nrcpus,		false),
	FEAT_OPR(CPUDESC,	cpudesc,	false),
	FEAT_OPR(CPUID,		cpuid,		false),
	FEAT_OPR(TOTAL_MEM,	total_mem,	false),
	FEAT_OPR(EVENT_DESC,	event_desc,	false),
	FEAT_OPR(CMDLINE,	cmdline,	false),
	FEAT_OPR(CPU_TOPOLOGY,	cpu_topology,	true),
	FEAT_OPR(NUMA_TOPOLOGY,	numa_topology,	true),
	FEAT_OPN(BRANCH_STACK,	branch_stack,	false),
	FEAT_OPR(PMU_MAPPINGS,	pmu_mappings,	false),
	FEAT_OPR(GROUP_DESC,	group_desc,	false),
	FEAT_OPN(AUXTRACE,	auxtrace,	false),
	FEAT_OPN(STAT,		stat,		false),
	FEAT_OPN(CACHE,		cache,		true),
	FEAT_OPR(SAMPLE_TIME,	sample_समय,	false),
	FEAT_OPR(MEM_TOPOLOGY,	mem_topology,	true),
	FEAT_OPR(CLOCKID,	घड़ीid,	false),
	FEAT_OPN(सूची_FORMAT,	dir_क्रमmat,	false),
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	FEAT_OPR(BPF_PROG_INFO, bpf_prog_info,  false),
	FEAT_OPR(BPF_BTF,       bpf_btf,        false),
#पूर्ण_अगर
	FEAT_OPR(COMPRESSED,	compressed,	false),
	FEAT_OPR(CPU_PMU_CAPS,	cpu_pmu_caps,	false),
	FEAT_OPR(CLOCK_DATA,	घड़ी_data,	false),
पूर्ण;

काष्ठा header_prपूर्णांक_data अणु
	खाता *fp;
	bool full; /* extended list of headers */
पूर्ण;

अटल पूर्णांक perf_file_section__ख_लिखो_info(काष्ठा perf_file_section *section,
					   काष्ठा perf_header *ph,
					   पूर्णांक feat, पूर्णांक fd, व्योम *data)
अणु
	काष्ठा header_prपूर्णांक_data *hd = data;
	काष्ठा feat_fd ff;

	अगर (lseek(fd, section->offset, शुरू_से) == (off_t)-1) अणु
		pr_debug("Failed to lseek to %" PRIu64 " offset for feature "
				"%d, continuing...\n", section->offset, feat);
		वापस 0;
	पूर्ण
	अगर (feat >= HEADER_LAST_FEATURE) अणु
		pr_warning("unknown feature %d\n", feat);
		वापस 0;
	पूर्ण
	अगर (!feat_ops[feat].prपूर्णांक)
		वापस 0;

	ff = (काष्ठा  feat_fd) अणु
		.fd = fd,
		.ph = ph,
	पूर्ण;

	अगर (!feat_ops[feat].full_only || hd->full)
		feat_ops[feat].prपूर्णांक(&ff, hd->fp);
	अन्यथा
		ख_लिखो(hd->fp, "# %s info available, use -I to display\n",
			feat_ops[feat].name);

	वापस 0;
पूर्ण

पूर्णांक perf_header__ख_लिखो_info(काष्ठा perf_session *session, खाता *fp, bool full)
अणु
	काष्ठा header_prपूर्णांक_data hd;
	काष्ठा perf_header *header = &session->header;
	पूर्णांक fd = perf_data__fd(session->data);
	काष्ठा stat st;
	समय_प्रकार stस_समय;
	पूर्णांक ret, bit;

	hd.fp = fp;
	hd.full = full;

	ret = ख_स्थिति(fd, &st);
	अगर (ret == -1)
		वापस -1;

	stस_समय = st.st_mसमय;
	ख_लिखो(fp, "# captured on    : %s", स_समय(&stस_समय));

	ख_लिखो(fp, "# header version : %u\n", header->version);
	ख_लिखो(fp, "# data offset    : %" PRIu64 "\n", header->data_offset);
	ख_लिखो(fp, "# data size      : %" PRIu64 "\n", header->data_size);
	ख_लिखो(fp, "# feat offset    : %" PRIu64 "\n", header->feat_offset);

	perf_header__process_sections(header, fd, &hd,
				      perf_file_section__ख_लिखो_info);

	अगर (session->data->is_pipe)
		वापस 0;

	ख_लिखो(fp, "# missing features: ");
	क्रम_each_clear_bit(bit, header->adds_features, HEADER_LAST_FEATURE) अणु
		अगर (bit)
			ख_लिखो(fp, "%s ", feat_ops[bit].name);
	पूर्ण

	ख_लिखो(fp, "\n");
	वापस 0;
पूर्ण

अटल पूर्णांक करो_ग_लिखो_feat(काष्ठा feat_fd *ff, पूर्णांक type,
			 काष्ठा perf_file_section **p,
			 काष्ठा evlist *evlist)
अणु
	पूर्णांक err;
	पूर्णांक ret = 0;

	अगर (perf_header__has_feat(ff->ph, type)) अणु
		अगर (!feat_ops[type].ग_लिखो)
			वापस -1;

		अगर (WARN(ff->buf, "Error: calling %s in pipe-mode.\n", __func__))
			वापस -1;

		(*p)->offset = lseek(ff->fd, 0, प्रस्तुत_से);

		err = feat_ops[type].ग_लिखो(ff, evlist);
		अगर (err < 0) अणु
			pr_debug("failed to write feature %s\n", feat_ops[type].name);

			/* unकरो anything written */
			lseek(ff->fd, (*p)->offset, शुरू_से);

			वापस -1;
		पूर्ण
		(*p)->size = lseek(ff->fd, 0, प्रस्तुत_से) - (*p)->offset;
		(*p)++;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक perf_header__adds_ग_लिखो(काष्ठा perf_header *header,
				   काष्ठा evlist *evlist, पूर्णांक fd)
अणु
	पूर्णांक nr_sections;
	काष्ठा feat_fd ff;
	काष्ठा perf_file_section *feat_sec, *p;
	पूर्णांक sec_size;
	u64 sec_start;
	पूर्णांक feat;
	पूर्णांक err;

	ff = (काष्ठा feat_fd)अणु
		.fd  = fd,
		.ph = header,
	पूर्ण;

	nr_sections = biपंचांगap_weight(header->adds_features, HEADER_FEAT_BITS);
	अगर (!nr_sections)
		वापस 0;

	feat_sec = p = सुस्मृति(nr_sections, माप(*feat_sec));
	अगर (feat_sec == शून्य)
		वापस -ENOMEM;

	sec_size = माप(*feat_sec) * nr_sections;

	sec_start = header->feat_offset;
	lseek(fd, sec_start + sec_size, शुरू_से);

	क्रम_each_set_bit(feat, header->adds_features, HEADER_FEAT_BITS) अणु
		अगर (करो_ग_लिखो_feat(&ff, feat, &p, evlist))
			perf_header__clear_feat(header, feat);
	पूर्ण

	lseek(fd, sec_start, शुरू_से);
	/*
	 * may ग_लिखो more than needed due to dropped feature, but
	 * this is okay, पढ़ोer will skip the missing entries
	 */
	err = करो_ग_लिखो(&ff, feat_sec, sec_size);
	अगर (err < 0)
		pr_debug("failed to write feature section\n");
	मुक्त(feat_sec);
	वापस err;
पूर्ण

पूर्णांक perf_header__ग_लिखो_pipe(पूर्णांक fd)
अणु
	काष्ठा perf_pipe_file_header f_header;
	काष्ठा feat_fd ff;
	पूर्णांक err;

	ff = (काष्ठा feat_fd)अणु .fd = fd पूर्ण;

	f_header = (काष्ठा perf_pipe_file_header)अणु
		.magic	   = PERF_MAGIC,
		.size	   = माप(f_header),
	पूर्ण;

	err = करो_ग_लिखो(&ff, &f_header, माप(f_header));
	अगर (err < 0) अणु
		pr_debug("failed to write perf pipe header\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_session__ग_लिखो_header(काष्ठा perf_session *session,
			       काष्ठा evlist *evlist,
			       पूर्णांक fd, bool at_निकास)
अणु
	काष्ठा perf_file_header f_header;
	काष्ठा perf_file_attr   f_attr;
	काष्ठा perf_header *header = &session->header;
	काष्ठा evsel *evsel;
	काष्ठा feat_fd ff;
	u64 attr_offset;
	पूर्णांक err;

	ff = (काष्ठा feat_fd)अणु .fd = fdपूर्ण;
	lseek(fd, माप(f_header), शुरू_से);

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		evsel->id_offset = lseek(fd, 0, प्रस्तुत_से);
		err = करो_ग_लिखो(&ff, evsel->core.id, evsel->core.ids * माप(u64));
		अगर (err < 0) अणु
			pr_debug("failed to write perf header\n");
			वापस err;
		पूर्ण
	पूर्ण

	attr_offset = lseek(ff.fd, 0, प्रस्तुत_से);

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.size < माप(evsel->core.attr)) अणु
			/*
			 * We are likely in "perf inject" and have पढ़ो
			 * from an older file. Update attr size so that
			 * पढ़ोer माला_लो the right offset to the ids.
			 */
			evsel->core.attr.size = माप(evsel->core.attr);
		पूर्ण
		f_attr = (काष्ठा perf_file_attr)अणु
			.attr = evsel->core.attr,
			.ids  = अणु
				.offset = evsel->id_offset,
				.size   = evsel->core.ids * माप(u64),
			पूर्ण
		पूर्ण;
		err = करो_ग_लिखो(&ff, &f_attr, माप(f_attr));
		अगर (err < 0) अणु
			pr_debug("failed to write perf header attribute\n");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!header->data_offset)
		header->data_offset = lseek(fd, 0, प्रस्तुत_से);
	header->feat_offset = header->data_offset + header->data_size;

	अगर (at_निकास) अणु
		err = perf_header__adds_ग_लिखो(header, evlist, fd);
		अगर (err < 0)
			वापस err;
	पूर्ण

	f_header = (काष्ठा perf_file_header)अणु
		.magic	   = PERF_MAGIC,
		.size	   = माप(f_header),
		.attr_size = माप(f_attr),
		.attrs = अणु
			.offset = attr_offset,
			.size   = evlist->core.nr_entries * माप(f_attr),
		पूर्ण,
		.data = अणु
			.offset = header->data_offset,
			.size	= header->data_size,
		पूर्ण,
		/* event_types is ignored, store zeros */
	पूर्ण;

	स_नकल(&f_header.adds_features, &header->adds_features, माप(header->adds_features));

	lseek(fd, 0, शुरू_से);
	err = करो_ग_लिखो(&ff, &f_header, माप(f_header));
	अगर (err < 0) अणु
		pr_debug("failed to write perf header\n");
		वापस err;
	पूर्ण
	lseek(fd, header->data_offset + header->data_size, शुरू_से);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_header__getbuffer64(काष्ठा perf_header *header,
				    पूर्णांक fd, व्योम *buf, माप_प्रकार size)
अणु
	अगर (पढ़ोn(fd, buf, size) <= 0)
		वापस -1;

	अगर (header->needs_swap)
		mem_bswap_64(buf, size);

	वापस 0;
पूर्ण

पूर्णांक perf_header__process_sections(काष्ठा perf_header *header, पूर्णांक fd,
				  व्योम *data,
				  पूर्णांक (*process)(काष्ठा perf_file_section *section,
						 काष्ठा perf_header *ph,
						 पूर्णांक feat, पूर्णांक fd, व्योम *data))
अणु
	काष्ठा perf_file_section *feat_sec, *sec;
	पूर्णांक nr_sections;
	पूर्णांक sec_size;
	पूर्णांक feat;
	पूर्णांक err;

	nr_sections = biपंचांगap_weight(header->adds_features, HEADER_FEAT_BITS);
	अगर (!nr_sections)
		वापस 0;

	feat_sec = sec = सुस्मृति(nr_sections, माप(*feat_sec));
	अगर (!feat_sec)
		वापस -1;

	sec_size = माप(*feat_sec) * nr_sections;

	lseek(fd, header->feat_offset, शुरू_से);

	err = perf_header__getbuffer64(header, fd, feat_sec, sec_size);
	अगर (err < 0)
		जाओ out_मुक्त;

	क्रम_each_set_bit(feat, header->adds_features, HEADER_LAST_FEATURE) अणु
		err = process(sec++, header, feat, fd, data);
		अगर (err < 0)
			जाओ out_मुक्त;
	पूर्ण
	err = 0;
out_मुक्त:
	मुक्त(feat_sec);
	वापस err;
पूर्ण

अटल स्थिर पूर्णांक attr_file_abi_sizes[] = अणु
	[0] = PERF_ATTR_SIZE_VER0,
	[1] = PERF_ATTR_SIZE_VER1,
	[2] = PERF_ATTR_SIZE_VER2,
	[3] = PERF_ATTR_SIZE_VER3,
	[4] = PERF_ATTR_SIZE_VER4,
	0,
पूर्ण;

/*
 * In the legacy file क्रमmat, the magic number is not used to encode endianness.
 * hdr_sz was used to encode endianness. But given that hdr_sz can vary based
 * on ABI revisions, we need to try all combinations क्रम all endianness to
 * detect the endianness.
 */
अटल पूर्णांक try_all_file_abis(uपूर्णांक64_t hdr_sz, काष्ठा perf_header *ph)
अणु
	uपूर्णांक64_t ref_size, attr_size;
	पूर्णांक i;

	क्रम (i = 0 ; attr_file_abi_sizes[i]; i++) अणु
		ref_size = attr_file_abi_sizes[i]
			 + माप(काष्ठा perf_file_section);
		अगर (hdr_sz != ref_size) अणु
			attr_size = bswap_64(hdr_sz);
			अगर (attr_size != ref_size)
				जारी;

			ph->needs_swap = true;
		पूर्ण
		pr_debug("ABI%d perf.data file detected, need_swap=%d\n",
			 i,
			 ph->needs_swap);
		वापस 0;
	पूर्ण
	/* could not determine endianness */
	वापस -1;
पूर्ण

#घोषणा PERF_PIPE_HDR_VER0	16

अटल स्थिर माप_प्रकार attr_pipe_abi_sizes[] = अणु
	[0] = PERF_PIPE_HDR_VER0,
	0,
पूर्ण;

/*
 * In the legacy pipe क्रमmat, there is an implicit assumption that endianness
 * between host recording the samples, and host parsing the samples is the
 * same. This is not always the हाल given that the pipe output may always be
 * redirected पूर्णांकo a file and analyzed on a dअगरferent machine with possibly a
 * dअगरferent endianness and perf_event ABI revisions in the perf tool itself.
 */
अटल पूर्णांक try_all_pipe_abis(uपूर्णांक64_t hdr_sz, काष्ठा perf_header *ph)
अणु
	u64 attr_size;
	पूर्णांक i;

	क्रम (i = 0 ; attr_pipe_abi_sizes[i]; i++) अणु
		अगर (hdr_sz != attr_pipe_abi_sizes[i]) अणु
			attr_size = bswap_64(hdr_sz);
			अगर (attr_size != hdr_sz)
				जारी;

			ph->needs_swap = true;
		पूर्ण
		pr_debug("Pipe ABI%d perf.data file detected\n", i);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

bool is_perf_magic(u64 magic)
अणु
	अगर (!स_भेद(&magic, __perf_magic1, माप(magic))
		|| magic == __perf_magic2
		|| magic == __perf_magic2_sw)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक check_magic_endian(u64 magic, uपूर्णांक64_t hdr_sz,
			      bool is_pipe, काष्ठा perf_header *ph)
अणु
	पूर्णांक ret;

	/* check क्रम legacy क्रमmat */
	ret = स_भेद(&magic, __perf_magic1, माप(magic));
	अगर (ret == 0) अणु
		ph->version = PERF_HEADER_VERSION_1;
		pr_debug("legacy perf.data format\n");
		अगर (is_pipe)
			वापस try_all_pipe_abis(hdr_sz, ph);

		वापस try_all_file_abis(hdr_sz, ph);
	पूर्ण
	/*
	 * the new magic number serves two purposes:
	 * - unique number to identअगरy actual perf.data files
	 * - encode endianness of file
	 */
	ph->version = PERF_HEADER_VERSION_2;

	/* check magic number with one endianness */
	अगर (magic == __perf_magic2)
		वापस 0;

	/* check magic number with opposite endianness */
	अगर (magic != __perf_magic2_sw)
		वापस -1;

	ph->needs_swap = true;

	वापस 0;
पूर्ण

पूर्णांक perf_file_header__पढ़ो(काष्ठा perf_file_header *header,
			   काष्ठा perf_header *ph, पूर्णांक fd)
अणु
	sमाप_प्रकार ret;

	lseek(fd, 0, शुरू_से);

	ret = पढ़ोn(fd, header, माप(*header));
	अगर (ret <= 0)
		वापस -1;

	अगर (check_magic_endian(header->magic,
			       header->attr_size, false, ph) < 0) अणु
		pr_debug("magic/endian check failed\n");
		वापस -1;
	पूर्ण

	अगर (ph->needs_swap) अणु
		mem_bswap_64(header, दुरत्व(काष्ठा perf_file_header,
			     adds_features));
	पूर्ण

	अगर (header->size != माप(*header)) अणु
		/* Support the previous क्रमmat */
		अगर (header->size == दुरत्व(typeof(*header), adds_features))
			biपंचांगap_zero(header->adds_features, HEADER_FEAT_BITS);
		अन्यथा
			वापस -1;
	पूर्ण अन्यथा अगर (ph->needs_swap) अणु
		/*
		 * feature biपंचांगap is declared as an array of अचिन्हित दीर्घs --
		 * not good since its size can dअगरfer between the host that
		 * generated the data file and the host analyzing the file.
		 *
		 * We need to handle endianness, but we करोn't know the size of
		 * the अचिन्हित दीर्घ where the file was generated. Take a best
		 * guess at determining it: try 64-bit swap first (ie., file
		 * created on a 64-bit host), and check अगर the hostname feature
		 * bit is set (this feature bit is क्रमced on as of fbe96f2).
		 * If the bit is not, unकरो the 64-bit swap and try a 32-bit
		 * swap. If the hostname bit is still not set (e.g., older data
		 * file), punt and fallback to the original behavior --
		 * clearing all feature bits and setting buildid.
		 */
		mem_bswap_64(&header->adds_features,
			    BITS_TO_U64(HEADER_FEAT_BITS));

		अगर (!test_bit(HEADER_HOSTNAME, header->adds_features)) अणु
			/* unswap as u64 */
			mem_bswap_64(&header->adds_features,
				    BITS_TO_U64(HEADER_FEAT_BITS));

			/* unswap as u32 */
			mem_bswap_32(&header->adds_features,
				    BITS_TO_U32(HEADER_FEAT_BITS));
		पूर्ण

		अगर (!test_bit(HEADER_HOSTNAME, header->adds_features)) अणु
			biपंचांगap_zero(header->adds_features, HEADER_FEAT_BITS);
			set_bit(HEADER_BUILD_ID, header->adds_features);
		पूर्ण
	पूर्ण

	स_नकल(&ph->adds_features, &header->adds_features,
	       माप(ph->adds_features));

	ph->data_offset  = header->data.offset;
	ph->data_size	 = header->data.size;
	ph->feat_offset  = header->data.offset + header->data.size;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_file_section__process(काष्ठा perf_file_section *section,
				      काष्ठा perf_header *ph,
				      पूर्णांक feat, पूर्णांक fd, व्योम *data)
अणु
	काष्ठा feat_fd fdd = अणु
		.fd	= fd,
		.ph	= ph,
		.size	= section->size,
		.offset	= section->offset,
	पूर्ण;

	अगर (lseek(fd, section->offset, शुरू_से) == (off_t)-1) अणु
		pr_debug("Failed to lseek to %" PRIu64 " offset for feature "
			  "%d, continuing...\n", section->offset, feat);
		वापस 0;
	पूर्ण

	अगर (feat >= HEADER_LAST_FEATURE) अणु
		pr_debug("unknown feature %d, continuing...\n", feat);
		वापस 0;
	पूर्ण

	अगर (!feat_ops[feat].process)
		वापस 0;

	वापस feat_ops[feat].process(&fdd, data);
पूर्ण

अटल पूर्णांक perf_file_header__पढ़ो_pipe(काष्ठा perf_pipe_file_header *header,
				       काष्ठा perf_header *ph,
				       काष्ठा perf_data* data,
				       bool repipe)
अणु
	काष्ठा feat_fd ff = अणु
		.fd = STDOUT_खाताNO,
		.ph = ph,
	पूर्ण;
	sमाप_प्रकार ret;

	ret = perf_data__पढ़ो(data, header, माप(*header));
	अगर (ret <= 0)
		वापस -1;

	अगर (check_magic_endian(header->magic, header->size, true, ph) < 0) अणु
		pr_debug("endian/magic failed\n");
		वापस -1;
	पूर्ण

	अगर (ph->needs_swap)
		header->size = bswap_64(header->size);

	अगर (repipe && करो_ग_लिखो(&ff, header, माप(*header)) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक perf_header__पढ़ो_pipe(काष्ठा perf_session *session)
अणु
	काष्ठा perf_header *header = &session->header;
	काष्ठा perf_pipe_file_header f_header;

	अगर (perf_file_header__पढ़ो_pipe(&f_header, header, session->data,
					session->repipe) < 0) अणु
		pr_debug("incompatible file format\n");
		वापस -EINVAL;
	पूर्ण

	वापस f_header.size == माप(f_header) ? 0 : -1;
पूर्ण

अटल पूर्णांक पढ़ो_attr(पूर्णांक fd, काष्ठा perf_header *ph,
		     काष्ठा perf_file_attr *f_attr)
अणु
	काष्ठा perf_event_attr *attr = &f_attr->attr;
	माप_प्रकार sz, left;
	माप_प्रकार our_sz = माप(f_attr->attr);
	sमाप_प्रकार ret;

	स_रखो(f_attr, 0, माप(*f_attr));

	/* पढ़ो minimal guaranteed काष्ठाure */
	ret = पढ़ोn(fd, attr, PERF_ATTR_SIZE_VER0);
	अगर (ret <= 0) अणु
		pr_debug("cannot read %d bytes of header attr\n",
			 PERF_ATTR_SIZE_VER0);
		वापस -1;
	पूर्ण

	/* on file perf_event_attr size */
	sz = attr->size;

	अगर (ph->needs_swap)
		sz = bswap_32(sz);

	अगर (sz == 0) अणु
		/* assume ABI0 */
		sz =  PERF_ATTR_SIZE_VER0;
	पूर्ण अन्यथा अगर (sz > our_sz) अणु
		pr_debug("file uses a more recent and unsupported ABI"
			 " (%zu bytes extra)\n", sz - our_sz);
		वापस -1;
	पूर्ण
	/* what we have not yet पढ़ो and that we know about */
	left = sz - PERF_ATTR_SIZE_VER0;
	अगर (left) अणु
		व्योम *ptr = attr;
		ptr += PERF_ATTR_SIZE_VER0;

		ret = पढ़ोn(fd, ptr, left);
	पूर्ण
	/* पढ़ो perf_file_section, ids are पढ़ो in caller */
	ret = पढ़ोn(fd, &f_attr->ids, माप(f_attr->ids));

	वापस ret <= 0 ? -1 : 0;
पूर्ण

अटल पूर्णांक evsel__prepare_tracepoपूर्णांक_event(काष्ठा evsel *evsel, काष्ठा tep_handle *pevent)
अणु
	काष्ठा tep_event *event;
	अक्षर bf[128];

	/* alपढ़ोy prepared */
	अगर (evsel->tp_क्रमmat)
		वापस 0;

	अगर (pevent == शून्य) अणु
		pr_debug("broken or missing trace data\n");
		वापस -1;
	पूर्ण

	event = tep_find_event(pevent, evsel->core.attr.config);
	अगर (event == शून्य) अणु
		pr_debug("cannot find event format for %d\n", (पूर्णांक)evsel->core.attr.config);
		वापस -1;
	पूर्ण

	अगर (!evsel->name) अणु
		snम_लिखो(bf, माप(bf), "%s:%s", event->प्रणाली, event->name);
		evsel->name = strdup(bf);
		अगर (evsel->name == शून्य)
			वापस -1;
	पूर्ण

	evsel->tp_क्रमmat = event;
	वापस 0;
पूर्ण

अटल पूर्णांक evlist__prepare_tracepoपूर्णांक_events(काष्ठा evlist *evlist, काष्ठा tep_handle *pevent)
अणु
	काष्ठा evsel *pos;

	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (pos->core.attr.type == PERF_TYPE_TRACEPOINT &&
		    evsel__prepare_tracepoपूर्णांक_event(pos, pevent))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_session__पढ़ो_header(काष्ठा perf_session *session)
अणु
	काष्ठा perf_data *data = session->data;
	काष्ठा perf_header *header = &session->header;
	काष्ठा perf_file_header	f_header;
	काष्ठा perf_file_attr	f_attr;
	u64			f_id;
	पूर्णांक nr_attrs, nr_ids, i, j, err;
	पूर्णांक fd = perf_data__fd(data);

	session->evlist = evlist__new();
	अगर (session->evlist == शून्य)
		वापस -ENOMEM;

	session->evlist->env = &header->env;
	session->machines.host.env = &header->env;

	/*
	 * We can पढ़ो 'pipe' data event from regular file,
	 * check क्रम the pipe header regardless of source.
	 */
	err = perf_header__पढ़ो_pipe(session);
	अगर (!err || perf_data__is_pipe(data)) अणु
		data->is_pipe = true;
		वापस err;
	पूर्ण

	अगर (perf_file_header__पढ़ो(&f_header, header, fd) < 0)
		वापस -EINVAL;

	/*
	 * Sanity check that perf.data was written cleanly; data size is
	 * initialized to 0 and updated only अगर the on_निकास function is run.
	 * If data size is still 0 then the file contains only partial
	 * inक्रमmation.  Just warn user and process it as much as it can.
	 */
	अगर (f_header.data.size == 0) अणु
		pr_warning("WARNING: The %s file's data size field is 0 which is unexpected.\n"
			   "Was the 'perf record' command properly terminated?\n",
			   data->file.path);
	पूर्ण

	अगर (f_header.attr_size == 0) अणु
		pr_err("ERROR: The %s file's attr size field is 0 which is unexpected.\n"
		       "Was the 'perf record' command properly terminated?\n",
		       data->file.path);
		वापस -EINVAL;
	पूर्ण

	nr_attrs = f_header.attrs.size / f_header.attr_size;
	lseek(fd, f_header.attrs.offset, शुरू_से);

	क्रम (i = 0; i < nr_attrs; i++) अणु
		काष्ठा evsel *evsel;
		off_t पंचांगp;

		अगर (पढ़ो_attr(fd, header, &f_attr) < 0)
			जाओ out_त्रुटि_सं;

		अगर (header->needs_swap) अणु
			f_attr.ids.size   = bswap_64(f_attr.ids.size);
			f_attr.ids.offset = bswap_64(f_attr.ids.offset);
			perf_event__attr_swap(&f_attr.attr);
		पूर्ण

		पंचांगp = lseek(fd, 0, प्रस्तुत_से);
		evsel = evsel__new(&f_attr.attr);

		अगर (evsel == शून्य)
			जाओ out_delete_evlist;

		evsel->needs_swap = header->needs_swap;
		/*
		 * Do it beक्रमe so that अगर perf_evsel__alloc_id fails, this
		 * entry माला_लो purged too at evlist__delete().
		 */
		evlist__add(session->evlist, evsel);

		nr_ids = f_attr.ids.size / माप(u64);
		/*
		 * We करोn't have the cpu and thपढ़ो maps on the header, so
		 * क्रम allocating the perf_sample_id table we fake 1 cpu and
		 * hattr->ids thपढ़ोs.
		 */
		अगर (perf_evsel__alloc_id(&evsel->core, 1, nr_ids))
			जाओ out_delete_evlist;

		lseek(fd, f_attr.ids.offset, शुरू_से);

		क्रम (j = 0; j < nr_ids; j++) अणु
			अगर (perf_header__getbuffer64(header, fd, &f_id, माप(f_id)))
				जाओ out_त्रुटि_सं;

			perf_evlist__id_add(&session->evlist->core, &evsel->core, 0, j, f_id);
		पूर्ण

		lseek(fd, पंचांगp, शुरू_से);
	पूर्ण

	perf_header__process_sections(header, fd, &session->tevent,
				      perf_file_section__process);

	अगर (evlist__prepare_tracepoपूर्णांक_events(session->evlist, session->tevent.pevent))
		जाओ out_delete_evlist;

	वापस 0;
out_त्रुटि_सं:
	वापस -त्रुटि_सं;

out_delete_evlist:
	evlist__delete(session->evlist);
	session->evlist = शून्य;
	वापस -ENOMEM;
पूर्ण

पूर्णांक perf_event__process_feature(काष्ठा perf_session *session,
				जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा feat_fd ff = अणु .fd = 0 पूर्ण;
	काष्ठा perf_record_header_feature *fe = (काष्ठा perf_record_header_feature *)event;
	पूर्णांक type = fe->header.type;
	u64 feat = fe->feat_id;

	अगर (type < 0 || type >= PERF_RECORD_HEADER_MAX) अणु
		pr_warning("invalid record type %d in pipe-mode\n", type);
		वापस 0;
	पूर्ण
	अगर (feat == HEADER_RESERVED || feat >= HEADER_LAST_FEATURE) अणु
		pr_warning("invalid record type %d in pipe-mode\n", type);
		वापस -1;
	पूर्ण

	अगर (!feat_ops[feat].process)
		वापस 0;

	ff.buf  = (व्योम *)fe->data;
	ff.size = event->header.size - माप(*fe);
	ff.ph = &session->header;

	अगर (feat_ops[feat].process(&ff, शून्य))
		वापस -1;

	अगर (!feat_ops[feat].prपूर्णांक || !tool->show_feat_hdr)
		वापस 0;

	अगर (!feat_ops[feat].full_only ||
	    tool->show_feat_hdr >= SHOW_FEAT_HEADER_FULL_INFO) अणु
		feat_ops[feat].prपूर्णांक(&ff, मानक_निकास);
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_निकास, "# %s info available, use -I to display\n",
			feat_ops[feat].name);
	पूर्ण

	वापस 0;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_event_update(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_record_event_update *ev = &event->event_update;
	काष्ठा perf_record_event_update_scale *ev_scale;
	काष्ठा perf_record_event_update_cpus *ev_cpus;
	काष्ठा perf_cpu_map *map;
	माप_प्रकार ret;

	ret = ख_लिखो(fp, "\n... id:    %" PRI_lu64 "\n", ev->id);

	चयन (ev->type) अणु
	हाल PERF_EVENT_UPDATE__SCALE:
		ev_scale = (काष्ठा perf_record_event_update_scale *)ev->data;
		ret += ख_लिखो(fp, "... scale: %f\n", ev_scale->scale);
		अवरोध;
	हाल PERF_EVENT_UPDATE__UNIT:
		ret += ख_लिखो(fp, "... unit:  %s\n", ev->data);
		अवरोध;
	हाल PERF_EVENT_UPDATE__NAME:
		ret += ख_लिखो(fp, "... name:  %s\n", ev->data);
		अवरोध;
	हाल PERF_EVENT_UPDATE__CPUS:
		ev_cpus = (काष्ठा perf_record_event_update_cpus *)ev->data;
		ret += ख_लिखो(fp, "... ");

		map = cpu_map__new_data(&ev_cpus->cpus);
		अगर (map)
			ret += cpu_map__ख_लिखो(map, fp);
		अन्यथा
			ret += ख_लिखो(fp, "failed to get cpus\n");
		अवरोध;
	शेष:
		ret += ख_लिखो(fp, "... unknown type\n");
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक perf_event__process_attr(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा evlist **pevlist)
अणु
	u32 i, ids, n_ids;
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist = *pevlist;

	अगर (evlist == शून्य) अणु
		*pevlist = evlist = evlist__new();
		अगर (evlist == शून्य)
			वापस -ENOMEM;
	पूर्ण

	evsel = evsel__new(&event->attr.attr);
	अगर (evsel == शून्य)
		वापस -ENOMEM;

	evlist__add(evlist, evsel);

	ids = event->header.size;
	ids -= (व्योम *)&event->attr.id - (व्योम *)event;
	n_ids = ids / माप(u64);
	/*
	 * We करोn't have the cpu and thपढ़ो maps on the header, so
	 * क्रम allocating the perf_sample_id table we fake 1 cpu and
	 * hattr->ids thपढ़ोs.
	 */
	अगर (perf_evsel__alloc_id(&evsel->core, 1, n_ids))
		वापस -ENOMEM;

	क्रम (i = 0; i < n_ids; i++) अणु
		perf_evlist__id_add(&evlist->core, &evsel->core, 0, i, event->attr.id[i]);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_event__process_event_update(काष्ठा perf_tool *tool __maybe_unused,
				     जोड़ perf_event *event,
				     काष्ठा evlist **pevlist)
अणु
	काष्ठा perf_record_event_update *ev = &event->event_update;
	काष्ठा perf_record_event_update_scale *ev_scale;
	काष्ठा perf_record_event_update_cpus *ev_cpus;
	काष्ठा evlist *evlist;
	काष्ठा evsel *evsel;
	काष्ठा perf_cpu_map *map;

	अगर (!pevlist || *pevlist == शून्य)
		वापस -EINVAL;

	evlist = *pevlist;

	evsel = evlist__id2evsel(evlist, ev->id);
	अगर (evsel == शून्य)
		वापस -EINVAL;

	चयन (ev->type) अणु
	हाल PERF_EVENT_UPDATE__UNIT:
		evsel->unit = strdup(ev->data);
		अवरोध;
	हाल PERF_EVENT_UPDATE__NAME:
		evsel->name = strdup(ev->data);
		अवरोध;
	हाल PERF_EVENT_UPDATE__SCALE:
		ev_scale = (काष्ठा perf_record_event_update_scale *)ev->data;
		evsel->scale = ev_scale->scale;
		अवरोध;
	हाल PERF_EVENT_UPDATE__CPUS:
		ev_cpus = (काष्ठा perf_record_event_update_cpus *)ev->data;

		map = cpu_map__new_data(&ev_cpus->cpus);
		अगर (map)
			evsel->core.own_cpus = map;
		अन्यथा
			pr_err("failed to get event_update cpus\n");
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_event__process_tracing_data(काष्ठा perf_session *session,
				     जोड़ perf_event *event)
अणु
	sमाप_प्रकार size_पढ़ो, padding, size = event->tracing_data.size;
	पूर्णांक fd = perf_data__fd(session->data);
	अक्षर buf[बफ_मान];

	/*
	 * The pipe fd is alपढ़ोy in proper place and in any हाल
	 * we can't move it, and we'd screw the हाल where we पढ़ो
	 * 'pipe' data from regular file. The trace_report पढ़ोs
	 * data from 'fd' so we need to set it directly behind the
	 * event, where the tracing data starts.
	 */
	अगर (!perf_data__is_pipe(session->data)) अणु
		off_t offset = lseek(fd, 0, प्रस्तुत_से);

		/* setup क्रम पढ़ोing amidst mmap */
		lseek(fd, offset + माप(काष्ठा perf_record_header_tracing_data),
		      शुरू_से);
	पूर्ण

	size_पढ़ो = trace_report(fd, &session->tevent,
				 session->repipe);
	padding = PERF_ALIGN(size_पढ़ो, माप(u64)) - size_पढ़ो;

	अगर (पढ़ोn(fd, buf, padding) < 0) अणु
		pr_err("%s: reading input file", __func__);
		वापस -1;
	पूर्ण
	अगर (session->repipe) अणु
		पूर्णांक retw = ग_लिखो(STDOUT_खाताNO, buf, padding);
		अगर (retw <= 0 || retw != padding) अणु
			pr_err("%s: repiping tracing data padding", __func__);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (size_पढ़ो + padding != size) अणु
		pr_err("%s: tracing data size mismatch", __func__);
		वापस -1;
	पूर्ण

	evlist__prepare_tracepoपूर्णांक_events(session->evlist, session->tevent.pevent);

	वापस size_पढ़ो + padding;
पूर्ण

पूर्णांक perf_event__process_build_id(काष्ठा perf_session *session,
				 जोड़ perf_event *event)
अणु
	__event_process_build_id(&event->build_id,
				 event->build_id.filename,
				 session);
	वापस 0;
पूर्ण
