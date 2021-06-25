<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/sysmacros.h>
#समावेश <sys/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <libgen.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <byteswap.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <linux/stringअगरy.h>

#समावेश "build-id.h"
#समावेश "event.h"
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "namespaces.h"
#समावेश "symbol.h"
#समावेश <elf.h>

#समावेश "tsc.h"
#समावेश "session.h"
#समावेश "jit.h"
#समावेश "jitdump.h"
#समावेश "genelf.h"
#समावेश "thread.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>

काष्ठा jit_buf_desc अणु
	काष्ठा perf_data *output;
	काष्ठा perf_session *session;
	काष्ठा machine *machine;
	काष्ठा nsinfo  *nsi;
	जोड़ jr_entry   *entry;
	व्योम             *buf;
	uपूर्णांक64_t	 sample_type;
	माप_प्रकार           bufsize;
	खाता             *in;
	bool		 needs_bswap; /* handles cross-endianness */
	bool		 use_arch_बारtamp;
	व्योम		 *debug_data;
	व्योम		 *unwinding_data;
	uपूर्णांक64_t	 unwinding_size;
	uपूर्णांक64_t	 unwinding_mapped_size;
	uपूर्णांक64_t         eh_frame_hdr_size;
	माप_प्रकार		 nr_debug_entries;
	uपूर्णांक32_t         code_load_count;
	u64		 bytes_written;
	काष्ठा rb_root   code_root;
	अक्षर		 dir[PATH_MAX];
पूर्ण;

काष्ठा debug_line_info अणु
	अचिन्हित दीर्घ vma;
	अचिन्हित पूर्णांक lineno;
	/* The filename क्रमmat is unspecअगरied, असलolute path, relative etc. */
	अक्षर स्थिर filename[];
पूर्ण;

काष्ठा jit_tool अणु
	काष्ठा perf_tool tool;
	काष्ठा perf_data	output;
	काष्ठा perf_data	input;
	u64 bytes_written;
पूर्ण;

#घोषणा hmax(a, b) ((a) > (b) ? (a) : (b))
#घोषणा get_jit_tool(t) (container_of(tool, काष्ठा jit_tool, tool))

अटल पूर्णांक
jit_emit_elf(काष्ठा jit_buf_desc *jd,
	     अक्षर *filename,
	     स्थिर अक्षर *sym,
	     uपूर्णांक64_t code_addr,
	     स्थिर व्योम *code,
	     पूर्णांक csize,
	     व्योम *debug,
	     पूर्णांक nr_debug_entries,
	     व्योम *unwinding,
	     uपूर्णांक32_t unwinding_header_size,
	     uपूर्णांक32_t unwinding_size)
अणु
	पूर्णांक ret, fd, saved_त्रुटि_सं;
	काष्ठा nscookie nsc;

	अगर (verbose > 0)
		ख_लिखो(मानक_त्रुटि, "write ELF image %s\n", filename);

	nsinfo__mountns_enter(jd->nsi, &nsc);
	fd = खोलो(filename, O_CREAT|O_TRUNC|O_WRONLY, 0644);
	saved_त्रुटि_सं = त्रुटि_सं;
	nsinfo__mountns_निकास(&nsc);
	अगर (fd == -1) अणु
		pr_warning("cannot create jit ELF %s: %s\n", filename, म_त्रुटि(saved_त्रुटि_सं));
		वापस -1;
	पूर्ण

	ret = jit_ग_लिखो_elf(fd, code_addr, sym, (स्थिर व्योम *)code, csize, debug, nr_debug_entries,
			    unwinding, unwinding_header_size, unwinding_size);

        बंद(fd);

	अगर (ret) अणु
		nsinfo__mountns_enter(jd->nsi, &nsc);
		unlink(filename);
		nsinfo__mountns_निकास(&nsc);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
jit_बंद(काष्ठा jit_buf_desc *jd)
अणु
	अगर (!(jd && jd->in))
		वापस;
	funlockfile(jd->in);
	ख_बंद(jd->in);
	jd->in = शून्य;
पूर्ण

अटल पूर्णांक
jit_validate_events(काष्ठा perf_session *session)
अणु
	काष्ठा evsel *evsel;

	/*
	 * check that all events use CLOCK_MONOTONIC
	 */
	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (evsel->core.attr.use_घड़ीid == 0 || evsel->core.attr.घड़ीid != CLOCK_MONOTONIC)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
jit_खोलो(काष्ठा jit_buf_desc *jd, स्थिर अक्षर *name)
अणु
	काष्ठा jitheader header;
	काष्ठा nscookie nsc;
	काष्ठा jr_prefix *prefix;
	sमाप_प्रकार bs, bsz = 0;
	व्योम *n, *buf = शून्य;
	पूर्णांक ret, retval = -1;

	nsinfo__mountns_enter(jd->nsi, &nsc);
	jd->in = ख_खोलो(name, "r");
	nsinfo__mountns_निकास(&nsc);
	अगर (!jd->in)
		वापस -1;

	bsz = hmax(माप(header), माप(*prefix));

	buf = दो_स्मृति(bsz);
	अगर (!buf)
		जाओ error;

	/*
	 * protect from ग_लिखोr modअगरying the file जबतक we are पढ़ोing it
	 */
	flockfile(jd->in);

	ret = ख_पढ़ो(buf, माप(header), 1, jd->in);
	अगर (ret != 1)
		जाओ error;

	स_नकल(&header, buf, माप(header));

	अगर (header.magic != JITHEADER_MAGIC) अणु
		अगर (header.magic != JITHEADER_MAGIC_SW)
			जाओ error;
		jd->needs_bswap = true;
	पूर्ण

	अगर (jd->needs_bswap) अणु
		header.version    = bswap_32(header.version);
		header.total_size = bswap_32(header.total_size);
		header.pid	  = bswap_32(header.pid);
		header.elf_mach   = bswap_32(header.elf_mach);
		header.बारtamp  = bswap_64(header.बारtamp);
		header.flags      = bswap_64(header.flags);
	पूर्ण

	jd->use_arch_बारtamp = header.flags & JITDUMP_FLAGS_ARCH_TIMESTAMP;

	अगर (verbose > 2)
		pr_debug("version=%u\nhdr.size=%u\nts=0x%llx\npid=%d\nelf_mach=%d\nuse_arch_timestamp=%d\n",
			header.version,
			header.total_size,
			(अचिन्हित दीर्घ दीर्घ)header.बारtamp,
			header.pid,
			header.elf_mach,
			jd->use_arch_बारtamp);

	अगर (header.version > JITHEADER_VERSION) अणु
		pr_err("wrong jitdump version %u, expected " __stringअगरy(JITHEADER_VERSION),
			header.version);
		जाओ error;
	पूर्ण

	अगर (header.flags & JITDUMP_FLAGS_RESERVED) अणु
		pr_err("jitdump file contains invalid or unsupported flags 0x%llx\n",
		       (अचिन्हित दीर्घ दीर्घ)header.flags & JITDUMP_FLAGS_RESERVED);
		जाओ error;
	पूर्ण

	अगर (jd->use_arch_बारtamp && !jd->session->समय_conv.समय_mult) अणु
		pr_err("jitdump file uses arch timestamps but there is no timestamp conversion\n");
		जाओ error;
	पूर्ण

	/*
	 * validate event is using the correct घड़ीid
	 */
	अगर (!jd->use_arch_बारtamp && jit_validate_events(jd->session)) अणु
		pr_err("error, jitted code must be sampled with perf record -k 1\n");
		जाओ error;
	पूर्ण

	bs = header.total_size - माप(header);

	अगर (bs > bsz) अणु
		n = पुनः_स्मृति(buf, bs);
		अगर (!n)
			जाओ error;
		bsz = bs;
		buf = n;
		/* पढ़ो extra we करो not know about */
		ret = ख_पढ़ो(buf, bs - bsz, 1, jd->in);
		अगर (ret != 1)
			जाओ error;
	पूर्ण
	/*
	 * keep स_नाम क्रम generating files and mmap records
	 */
	म_नकल(jd->dir, name);
	स_नाम(jd->dir);

	वापस 0;
error:
	funlockfile(jd->in);
	ख_बंद(jd->in);
	वापस retval;
पूर्ण

अटल जोड़ jr_entry *
jit_get_next_entry(काष्ठा jit_buf_desc *jd)
अणु
	काष्ठा jr_prefix *prefix;
	जोड़ jr_entry *jr;
	व्योम *addr;
	माप_प्रकार bs, size;
	पूर्णांक id, ret;

	अगर (!(jd && jd->in))
		वापस शून्य;

	अगर (jd->buf == शून्य) अणु
		माप_प्रकार sz = getpagesize();
		अगर (sz < माप(*prefix))
			sz = माप(*prefix);

		jd->buf = दो_स्मृति(sz);
		अगर (jd->buf == शून्य)
			वापस शून्य;

		jd->bufsize = sz;
	पूर्ण

	prefix = jd->buf;

	/*
	 * file is still locked at this poपूर्णांक
	 */
	ret = ख_पढ़ो(prefix, माप(*prefix), 1, jd->in);
	अगर (ret  != 1)
		वापस शून्य;

	अगर (jd->needs_bswap) अणु
		prefix->id   	   = bswap_32(prefix->id);
		prefix->total_size = bswap_32(prefix->total_size);
		prefix->बारtamp  = bswap_64(prefix->बारtamp);
	पूर्ण
	id   = prefix->id;
	size = prefix->total_size;

	bs = (माप_प्रकार)size;
	अगर (bs < माप(*prefix))
		वापस शून्य;

	अगर (id >= JIT_CODE_MAX) अणु
		pr_warning("next_entry: unknown record type %d, skipping\n", id);
	पूर्ण
	अगर (bs > jd->bufsize) अणु
		व्योम *n;
		n = पुनः_स्मृति(jd->buf, bs);
		अगर (!n)
			वापस शून्य;
		jd->buf = n;
		jd->bufsize = bs;
	पूर्ण

	addr = ((व्योम *)jd->buf) + माप(*prefix);

	ret = ख_पढ़ो(addr, bs - माप(*prefix), 1, jd->in);
	अगर (ret != 1)
		वापस शून्य;

	jr = (जोड़ jr_entry *)jd->buf;

	चयन(id) अणु
	हाल JIT_CODE_DEBUG_INFO:
		अगर (jd->needs_bswap) अणु
			uपूर्णांक64_t n;
			jr->info.code_addr = bswap_64(jr->info.code_addr);
			jr->info.nr_entry  = bswap_64(jr->info.nr_entry);
			क्रम (n = 0 ; n < jr->info.nr_entry; n++) अणु
				jr->info.entries[n].addr    = bswap_64(jr->info.entries[n].addr);
				jr->info.entries[n].lineno  = bswap_32(jr->info.entries[n].lineno);
				jr->info.entries[n].discrim = bswap_32(jr->info.entries[n].discrim);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल JIT_CODE_UNWINDING_INFO:
		अगर (jd->needs_bswap) अणु
			jr->unwinding.unwinding_size = bswap_64(jr->unwinding.unwinding_size);
			jr->unwinding.eh_frame_hdr_size = bswap_64(jr->unwinding.eh_frame_hdr_size);
			jr->unwinding.mapped_size = bswap_64(jr->unwinding.mapped_size);
		पूर्ण
		अवरोध;
	हाल JIT_CODE_CLOSE:
		अवरोध;
	हाल JIT_CODE_LOAD:
		अगर (jd->needs_bswap) अणु
			jr->load.pid       = bswap_32(jr->load.pid);
			jr->load.tid       = bswap_32(jr->load.tid);
			jr->load.vma       = bswap_64(jr->load.vma);
			jr->load.code_addr = bswap_64(jr->load.code_addr);
			jr->load.code_size = bswap_64(jr->load.code_size);
			jr->load.code_index= bswap_64(jr->load.code_index);
		पूर्ण
		jd->code_load_count++;
		अवरोध;
	हाल JIT_CODE_MOVE:
		अगर (jd->needs_bswap) अणु
			jr->move.pid           = bswap_32(jr->move.pid);
			jr->move.tid           = bswap_32(jr->move.tid);
			jr->move.vma           = bswap_64(jr->move.vma);
			jr->move.old_code_addr = bswap_64(jr->move.old_code_addr);
			jr->move.new_code_addr = bswap_64(jr->move.new_code_addr);
			jr->move.code_size     = bswap_64(jr->move.code_size);
			jr->move.code_index    = bswap_64(jr->move.code_index);
		पूर्ण
		अवरोध;
	हाल JIT_CODE_MAX:
	शेष:
		/* skip unknown record (we have पढ़ो them) */
		अवरोध;
	पूर्ण
	वापस jr;
पूर्ण

अटल पूर्णांक
jit_inject_event(काष्ठा jit_buf_desc *jd, जोड़ perf_event *event)
अणु
	sमाप_प्रकार size;

	size = perf_data__ग_लिखो(jd->output, event, event->header.size);
	अगर (size < 0)
		वापस -1;

	jd->bytes_written += size;
	वापस 0;
पूर्ण

अटल pid_t jr_entry_pid(काष्ठा jit_buf_desc *jd, जोड़ jr_entry *jr)
अणु
	अगर (jd->nsi && jd->nsi->in_pidns)
		वापस jd->nsi->tgid;
	वापस jr->load.pid;
पूर्ण

अटल pid_t jr_entry_tid(काष्ठा jit_buf_desc *jd, जोड़ jr_entry *jr)
अणु
	अगर (jd->nsi && jd->nsi->in_pidns)
		वापस jd->nsi->pid;
	वापस jr->load.tid;
पूर्ण

अटल uपूर्णांक64_t convert_बारtamp(काष्ठा jit_buf_desc *jd, uपूर्णांक64_t बारtamp)
अणु
	काष्ठा perf_tsc_conversion tc = अणु .समय_shअगरt = 0, पूर्ण;
	काष्ठा perf_record_समय_conv *समय_conv = &jd->session->समय_conv;

	अगर (!jd->use_arch_बारtamp)
		वापस बारtamp;

	tc.समय_shअगरt = समय_conv->समय_shअगरt;
	tc.समय_mult  = समय_conv->समय_mult;
	tc.समय_zero  = समय_conv->समय_zero;

	/*
	 * The event TIME_CONV was extended क्रम the fields from "time_cycles"
	 * when supported cap_user_समय_लघु, क्रम backward compatibility,
	 * checks the event size and assigns these extended fields अगर these
	 * fields are contained in the event.
	 */
	अगर (event_contains(*समय_conv, समय_cycles)) अणु
		tc.समय_cycles	       = समय_conv->समय_cycles;
		tc.समय_mask	       = समय_conv->समय_mask;
		tc.cap_user_समय_zero  = समय_conv->cap_user_समय_zero;
		tc.cap_user_समय_लघु = समय_conv->cap_user_समय_लघु;

		अगर (!tc.cap_user_समय_zero)
			वापस 0;
	पूर्ण

	वापस tsc_to_perf_समय(बारtamp, &tc);
पूर्ण

अटल पूर्णांक jit_repipe_code_load(काष्ठा jit_buf_desc *jd, जोड़ jr_entry *jr)
अणु
	काष्ठा perf_sample sample;
	जोड़ perf_event *event;
	काष्ठा perf_tool *tool = jd->session->tool;
	uपूर्णांक64_t code, addr;
	uपूर्णांकptr_t uaddr;
	अक्षर *filename;
	काष्ठा stat st;
	माप_प्रकार size;
	u16 idr_size;
	स्थिर अक्षर *sym;
	uपूर्णांक64_t count;
	पूर्णांक ret, csize, usize;
	pid_t nspid, pid, tid;
	काष्ठा अणु
		u32 pid, tid;
		u64 समय;
	पूर्ण *id;

	nspid = jr->load.pid;
	pid   = jr_entry_pid(jd, jr);
	tid   = jr_entry_tid(jd, jr);
	csize = jr->load.code_size;
	usize = jd->unwinding_mapped_size;
	addr  = jr->load.code_addr;
	sym   = (व्योम *)((अचिन्हित दीर्घ)jr + माप(jr->load));
	code  = (अचिन्हित दीर्घ)jr + jr->load.p.total_size - csize;
	count = jr->load.code_index;
	idr_size = jd->machine->id_hdr_size;

	event = सुस्मृति(1, माप(*event) + idr_size);
	अगर (!event)
		वापस -1;

	filename = event->mmap2.filename;
	size = snम_लिखो(filename, PATH_MAX, "%s/jitted-%d-%" PRIu64 ".so",
			jd->dir,
			nspid,
			count);

	size++; /* क्रम \0 */

	size = PERF_ALIGN(size, माप(u64));
	uaddr = (uपूर्णांकptr_t)code;
	ret = jit_emit_elf(jd, filename, sym, addr, (स्थिर व्योम *)uaddr, csize, jd->debug_data, jd->nr_debug_entries,
			   jd->unwinding_data, jd->eh_frame_hdr_size, jd->unwinding_size);

	अगर (jd->debug_data && jd->nr_debug_entries) अणु
		zमुक्त(&jd->debug_data);
		jd->nr_debug_entries = 0;
	पूर्ण

	अगर (jd->unwinding_data && jd->eh_frame_hdr_size) अणु
		zमुक्त(&jd->unwinding_data);
		jd->eh_frame_hdr_size = 0;
		jd->unwinding_mapped_size = 0;
		jd->unwinding_size = 0;
	पूर्ण

	अगर (ret) अणु
		मुक्त(event);
		वापस -1;
	पूर्ण
	अगर (nsinfo__stat(filename, &st, jd->nsi))
		स_रखो(&st, 0, माप(st));

	event->mmap2.header.type = PERF_RECORD_MMAP2;
	event->mmap2.header.misc = PERF_RECORD_MISC_USER;
	event->mmap2.header.size = (माप(event->mmap2) -
			(माप(event->mmap2.filename) - size) + idr_size);

	event->mmap2.pgoff = GEN_ELF_TEXT_OFFSET;
	event->mmap2.start = addr;
	event->mmap2.len   = usize ? ALIGN_8(csize) + usize : csize;
	event->mmap2.pid   = pid;
	event->mmap2.tid   = tid;
	event->mmap2.ino   = st.st_ino;
	event->mmap2.maj   = major(st.st_dev);
	event->mmap2.min   = minor(st.st_dev);
	event->mmap2.prot  = st.st_mode;
	event->mmap2.flags = MAP_SHARED;
	event->mmap2.ino_generation = 1;

	id = (व्योम *)((अचिन्हित दीर्घ)event + event->mmap.header.size - idr_size);
	अगर (jd->sample_type & PERF_SAMPLE_TID) अणु
		id->pid  = pid;
		id->tid  = tid;
	पूर्ण
	अगर (jd->sample_type & PERF_SAMPLE_TIME)
		id->समय = convert_बारtamp(jd, jr->load.p.बारtamp);

	/*
	 * create pseuकरो sample to induce dso hit increment
	 * use first address as sample address
	 */
	स_रखो(&sample, 0, माप(sample));
	sample.cpumode = PERF_RECORD_MISC_USER;
	sample.pid  = pid;
	sample.tid  = tid;
	sample.समय = id->समय;
	sample.ip   = addr;

	ret = perf_event__process_mmap2(tool, event, &sample, jd->machine);
	अगर (ret)
		वापस ret;

	ret = jit_inject_event(jd, event);
	/*
	 * mark dso as use to generate buildid in the header
	 */
	अगर (!ret)
		build_id__mark_dso_hit(tool, event, &sample, शून्य, jd->machine);

	वापस ret;
पूर्ण

अटल पूर्णांक jit_repipe_code_move(काष्ठा jit_buf_desc *jd, जोड़ jr_entry *jr)
अणु
	काष्ठा perf_sample sample;
	जोड़ perf_event *event;
	काष्ठा perf_tool *tool = jd->session->tool;
	अक्षर *filename;
	माप_प्रकार size;
	काष्ठा stat st;
	पूर्णांक usize;
	u16 idr_size;
	पूर्णांक ret;
	pid_t nspid, pid, tid;
	काष्ठा अणु
		u32 pid, tid;
		u64 समय;
	पूर्ण *id;

	nspid = jr->load.pid;
	pid   = jr_entry_pid(jd, jr);
	tid   = jr_entry_tid(jd, jr);
	usize = jd->unwinding_mapped_size;
	idr_size = jd->machine->id_hdr_size;

	/*
	 * +16 to account क्रम sample_id_all (hack)
	 */
	event = सुस्मृति(1, माप(*event) + 16);
	अगर (!event)
		वापस -1;

	filename = event->mmap2.filename;
	size = snम_लिखो(filename, PATH_MAX, "%s/jitted-%d-%" PRIu64 ".so",
	         jd->dir,
		 nspid,
		 jr->move.code_index);

	size++; /* क्रम \0 */

	अगर (nsinfo__stat(filename, &st, jd->nsi))
		स_रखो(&st, 0, माप(st));

	size = PERF_ALIGN(size, माप(u64));

	event->mmap2.header.type = PERF_RECORD_MMAP2;
	event->mmap2.header.misc = PERF_RECORD_MISC_USER;
	event->mmap2.header.size = (माप(event->mmap2) -
			(माप(event->mmap2.filename) - size) + idr_size);
	event->mmap2.pgoff = GEN_ELF_TEXT_OFFSET;
	event->mmap2.start = jr->move.new_code_addr;
	event->mmap2.len   = usize ? ALIGN_8(jr->move.code_size) + usize
				   : jr->move.code_size;
	event->mmap2.pid   = pid;
	event->mmap2.tid   = tid;
	event->mmap2.ino   = st.st_ino;
	event->mmap2.maj   = major(st.st_dev);
	event->mmap2.min   = minor(st.st_dev);
	event->mmap2.prot  = st.st_mode;
	event->mmap2.flags = MAP_SHARED;
	event->mmap2.ino_generation = 1;

	id = (व्योम *)((अचिन्हित दीर्घ)event + event->mmap.header.size - idr_size);
	अगर (jd->sample_type & PERF_SAMPLE_TID) अणु
		id->pid  = pid;
		id->tid  = tid;
	पूर्ण
	अगर (jd->sample_type & PERF_SAMPLE_TIME)
		id->समय = convert_बारtamp(jd, jr->load.p.बारtamp);

	/*
	 * create pseuकरो sample to induce dso hit increment
	 * use first address as sample address
	 */
	स_रखो(&sample, 0, माप(sample));
	sample.cpumode = PERF_RECORD_MISC_USER;
	sample.pid  = pid;
	sample.tid  = tid;
	sample.समय = id->समय;
	sample.ip   = jr->move.new_code_addr;

	ret = perf_event__process_mmap2(tool, event, &sample, jd->machine);
	अगर (ret)
		वापस ret;

	ret = jit_inject_event(jd, event);
	अगर (!ret)
		build_id__mark_dso_hit(tool, event, &sample, शून्य, jd->machine);

	वापस ret;
पूर्ण

अटल पूर्णांक jit_repipe_debug_info(काष्ठा jit_buf_desc *jd, जोड़ jr_entry *jr)
अणु
	व्योम *data;
	माप_प्रकार sz;

	अगर (!(jd && jr))
		वापस -1;

	sz  = jr->prefix.total_size - माप(jr->info);
	data = दो_स्मृति(sz);
	अगर (!data)
		वापस -1;

	स_नकल(data, &jr->info.entries, sz);

	jd->debug_data       = data;

	/*
	 * we must use nr_entry instead of size here because
	 * we cannot distinguish actual entry from padding otherwise
	 */
	jd->nr_debug_entries = jr->info.nr_entry;

	वापस 0;
पूर्ण

अटल पूर्णांक
jit_repipe_unwinding_info(काष्ठा jit_buf_desc *jd, जोड़ jr_entry *jr)
अणु
	व्योम *unwinding_data;
	uपूर्णांक32_t unwinding_data_size;

	अगर (!(jd && jr))
		वापस -1;

	unwinding_data_size  = jr->prefix.total_size - माप(jr->unwinding);
	unwinding_data = दो_स्मृति(unwinding_data_size);
	अगर (!unwinding_data)
		वापस -1;

	स_नकल(unwinding_data, &jr->unwinding.unwinding_data,
	       unwinding_data_size);

	jd->eh_frame_hdr_size = jr->unwinding.eh_frame_hdr_size;
	jd->unwinding_size = jr->unwinding.unwinding_size;
	jd->unwinding_mapped_size = jr->unwinding.mapped_size;
	jd->unwinding_data = unwinding_data;

	वापस 0;
पूर्ण

अटल पूर्णांक
jit_process_dump(काष्ठा jit_buf_desc *jd)
अणु
	जोड़ jr_entry *jr;
	पूर्णांक ret = 0;

	जबतक ((jr = jit_get_next_entry(jd))) अणु
		चयन(jr->prefix.id) अणु
		हाल JIT_CODE_LOAD:
			ret = jit_repipe_code_load(jd, jr);
			अवरोध;
		हाल JIT_CODE_MOVE:
			ret = jit_repipe_code_move(jd, jr);
			अवरोध;
		हाल JIT_CODE_DEBUG_INFO:
			ret = jit_repipe_debug_info(jd, jr);
			अवरोध;
		हाल JIT_CODE_UNWINDING_INFO:
			ret = jit_repipe_unwinding_info(jd, jr);
			अवरोध;
		शेष:
			ret = 0;
			जारी;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
jit_inject(काष्ठा jit_buf_desc *jd, अक्षर *path)
अणु
	पूर्णांक ret;

	अगर (verbose > 0)
		ख_लिखो(मानक_त्रुटि, "injecting: %s\n", path);

	ret = jit_खोलो(jd, path);
	अगर (ret)
		वापस -1;

	ret = jit_process_dump(jd);

	jit_बंद(jd);

	अगर (verbose > 0)
		ख_लिखो(मानक_त्रुटि, "injected: %s (%d)\n", path, ret);

	वापस 0;
पूर्ण

/*
 * File must be with pattern .../jit-XXXX.dump
 * where XXXX is the PID of the process which did the mmap()
 * as captured in the RECORD_MMAP record
 */
अटल पूर्णांक
jit_detect(अक्षर *mmap_name, pid_t pid, काष्ठा nsinfo *nsi)
 अणु
	अक्षर *p;
	अक्षर *end = शून्य;
	pid_t pid2;

	अगर (verbose > 2)
		ख_लिखो(मानक_त्रुटि, "jit marker trying : %s\n", mmap_name);
	/*
	 * get file name
	 */
	p = म_खोजप(mmap_name, '/');
	अगर (!p)
		वापस -1;

	/*
	 * match prefix
	 */
	अगर (म_भेदन(p, "/jit-", 5))
		वापस -1;

	/*
	 * skip prefix
	 */
	p += 5;

	/*
	 * must be followed by a pid
	 */
	अगर (!है_अंक(*p))
		वापस -1;

	pid2 = (पूर्णांक)म_से_दीर्घ(p, &end, 10);
	अगर (!end)
		वापस -1;

	/*
	 * pid करोes not match mmap pid
	 * pid==0 in प्रणाली-wide mode (synthesized)
	 */
	अगर (pid && pid2 != nsi->nstgid)
		वापस -1;
	/*
	 * validate suffix
	 */
	अगर (म_भेद(end, ".dump"))
		वापस -1;

	अगर (verbose > 0)
		ख_लिखो(मानक_त्रुटि, "jit marker found: %s\n", mmap_name);

	वापस 0;
पूर्ण

अटल व्योम jit_add_pid(काष्ठा machine *machine, pid_t pid)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, pid, pid);

	अगर (!thपढ़ो) अणु
		pr_err("%s: thread %d not found or created\n", __func__, pid);
		वापस;
	पूर्ण

	thपढ़ो->priv = (व्योम *)1;
पूर्ण

अटल bool jit_has_pid(काष्ठा machine *machine, pid_t pid)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__find_thपढ़ो(machine, pid, pid);

	अगर (!thपढ़ो)
		वापस 0;

	वापस (bool)thपढ़ो->priv;
पूर्ण

पूर्णांक
jit_process(काष्ठा perf_session *session,
	    काष्ठा perf_data *output,
	    काष्ठा machine *machine,
	    अक्षर *filename,
	    pid_t pid,
	    pid_t tid,
	    u64 *nbytes)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा nsinfo *nsi;
	काष्ठा evsel *first;
	काष्ठा jit_buf_desc jd;
	पूर्णांक ret;

	thपढ़ो = machine__findnew_thपढ़ो(machine, pid, tid);
	अगर (thपढ़ो == शून्य) अणु
		pr_err("problem processing JIT mmap event, skipping it.\n");
		वापस 0;
	पूर्ण

	nsi = nsinfo__get(thपढ़ो->nsinfo);
	thपढ़ो__put(thपढ़ो);

	/*
	 * first, detect marker mmap (i.e., the jitdump mmap)
	 */
	अगर (jit_detect(filename, pid, nsi)) अणु
		nsinfo__put(nsi);

		// Strip //anon* mmaps अगर we processed a jitdump क्रम this pid
		अगर (jit_has_pid(machine, pid) && (म_भेदन(filename, "//anon", 6) == 0))
			वापस 1;

		वापस 0;
	पूर्ण

	स_रखो(&jd, 0, माप(jd));

	jd.session = session;
	jd.output  = output;
	jd.machine = machine;
	jd.nsi = nsi;

	/*
	 * track sample_type to compute id_all layout
	 * perf sets the same sample type to all events as of now
	 */
	first = evlist__first(session->evlist);
	jd.sample_type = first->core.attr.sample_type;

	*nbytes = 0;

	ret = jit_inject(&jd, filename);
	अगर (!ret) अणु
		jit_add_pid(machine, pid);
		*nbytes = jd.bytes_written;
		ret = 1;
	पूर्ण

	nsinfo__put(jd.nsi);

	वापस ret;
पूर्ण
