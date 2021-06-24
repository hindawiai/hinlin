<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-record.c
 *
 * Builtin record command: Record the profile of a workload
 * (or a CPU, or a PID) पूर्णांकo the perf.data output file - क्रम
 * later analysis via perf report.
 */
#समावेश "builtin.h"

#समावेश "util/build-id.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/parse-events.h"
#समावेश "util/config.h"

#समावेश "util/callchain.h"
#समावेश "util/cgroup.h"
#समावेश "util/header.h"
#समावेश "util/event.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/debug.h"
#समावेश "util/mmap.h"
#समावेश "util/target.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/symbol.h"
#समावेश "util/record.h"
#समावेश "util/cpumap.h"
#समावेश "util/thread_map.h"
#समावेश "util/data.h"
#समावेश "util/perf_regs.h"
#समावेश "util/auxtrace.h"
#समावेश "util/tsc.h"
#समावेश "util/parse-branch-options.h"
#समावेश "util/parse-regs-options.h"
#समावेश "util/perf_api_probe.h"
#समावेश "util/llvm-utils.h"
#समावेश "util/bpf-loader.h"
#समावेश "util/trigger.h"
#समावेश "util/perf-hooks.h"
#समावेश "util/cpu-set-sched.h"
#समावेश "util/synthetic-events.h"
#समावेश "util/time-utils.h"
#समावेश "util/units.h"
#समावेश "util/bpf-event.h"
#समावेश "util/util.h"
#समावेश "util/pfm.h"
#समावेश "util/clockid.h"
#समावेश "util/pmu-hybrid.h"
#समावेश "util/evlist-hybrid.h"
#समावेश "asm/bug.h"
#समावेश "perf.h"

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <क्षेत्र.स>
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <unistd.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#अगर_घोषित HAVE_EVENTFD_SUPPORT
#समावेश <sys/eventfd.h>
#पूर्ण_अगर
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <sys/समय.स>

काष्ठा चयन_output अणु
	bool		 enabled;
	bool		 संकेत;
	अचिन्हित दीर्घ	 size;
	अचिन्हित दीर्घ	 समय;
	स्थिर अक्षर	*str;
	bool		 set;
	अक्षर		 **filenames;
	पूर्णांक		 num_files;
	पूर्णांक		 cur_file;
पूर्ण;

काष्ठा record अणु
	काष्ठा perf_tool	tool;
	काष्ठा record_opts	opts;
	u64			bytes_written;
	काष्ठा perf_data	data;
	काष्ठा auxtrace_record	*itr;
	काष्ठा evlist	*evlist;
	काष्ठा perf_session	*session;
	काष्ठा evlist		*sb_evlist;
	pthपढ़ो_t		thपढ़ो_id;
	पूर्णांक			realसमय_prio;
	bool			चयन_output_event_set;
	bool			no_buildid;
	bool			no_buildid_set;
	bool			no_buildid_cache;
	bool			no_buildid_cache_set;
	bool			buildid_all;
	bool			buildid_mmap;
	bool			बारtamp_filename;
	bool			बारtamp_boundary;
	काष्ठा चयन_output	चयन_output;
	अचिन्हित दीर्घ दीर्घ	samples;
	काष्ठा mmap_cpu_mask	affinity_mask;
	अचिन्हित दीर्घ		output_max_size;	/* = 0: unlimited */
पूर्ण;

अटल अस्थिर पूर्णांक करोne;

अटल अस्थिर पूर्णांक auxtrace_record__snapshot_started;
अटल DEFINE_TRIGGER(auxtrace_snapshot_trigger);
अटल DEFINE_TRIGGER(चयन_output_trigger);

अटल स्थिर अक्षर *affinity_tags[PERF_AFFINITY_MAX] = अणु
	"SYS", "NODE", "CPU"
पूर्ण;

अटल bool चयन_output_संकेत(काष्ठा record *rec)
अणु
	वापस rec->चयन_output.संकेत &&
	       trigger_is_पढ़ोy(&चयन_output_trigger);
पूर्ण

अटल bool चयन_output_size(काष्ठा record *rec)
अणु
	वापस rec->चयन_output.size &&
	       trigger_is_पढ़ोy(&चयन_output_trigger) &&
	       (rec->bytes_written >= rec->चयन_output.size);
पूर्ण

अटल bool चयन_output_समय(काष्ठा record *rec)
अणु
	वापस rec->चयन_output.समय &&
	       trigger_is_पढ़ोy(&चयन_output_trigger);
पूर्ण

अटल bool record__output_max_size_exceeded(काष्ठा record *rec)
अणु
	वापस rec->output_max_size &&
	       (rec->bytes_written >= rec->output_max_size);
पूर्ण

अटल पूर्णांक record__ग_लिखो(काष्ठा record *rec, काष्ठा mmap *map __maybe_unused,
			 व्योम *bf, माप_प्रकार size)
अणु
	काष्ठा perf_data_file *file = &rec->session->data->file;

	अगर (perf_data_file__ग_लिखो(file, bf, size) < 0) अणु
		pr_err("failed to write perf data, error: %m\n");
		वापस -1;
	पूर्ण

	rec->bytes_written += size;

	अगर (record__output_max_size_exceeded(rec) && !करोne) अणु
		ख_लिखो(मानक_त्रुटि, "[ perf record: perf size limit reached (%" PRIu64 " KB),"
				" stopping session ]\n",
				rec->bytes_written >> 10);
		करोne = 1;
	पूर्ण

	अगर (चयन_output_size(rec))
		trigger_hit(&चयन_output_trigger);

	वापस 0;
पूर्ण

अटल पूर्णांक record__aio_enabled(काष्ठा record *rec);
अटल पूर्णांक record__comp_enabled(काष्ठा record *rec);
अटल माप_प्रकार zstd_compress(काष्ठा perf_session *session, व्योम *dst, माप_प्रकार dst_size,
			    व्योम *src, माप_प्रकार src_size);

#अगर_घोषित HAVE_AIO_SUPPORT
अटल पूर्णांक record__aio_ग_लिखो(काष्ठा aiocb *cblock, पूर्णांक trace_fd,
		व्योम *buf, माप_प्रकार size, off_t off)
अणु
	पूर्णांक rc;

	cblock->aio_fildes = trace_fd;
	cblock->aio_buf    = buf;
	cblock->aio_nbytes = size;
	cblock->aio_offset = off;
	cblock->aio_sigevent.sigev_notअगरy = SIGEV_NONE;

	करो अणु
		rc = aio_ग_लिखो(cblock);
		अगर (rc == 0) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (त्रुटि_सं != EAGAIN) अणु
			cblock->aio_fildes = -1;
			pr_err("failed to queue perf data, error: %m\n");
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	वापस rc;
पूर्ण

अटल पूर्णांक record__aio_complete(काष्ठा mmap *md, काष्ठा aiocb *cblock)
अणु
	व्योम *rem_buf;
	off_t rem_off;
	माप_प्रकार rem_size;
	पूर्णांक rc, aio_त्रुटि_सं;
	sमाप_प्रकार aio_ret, written;

	aio_त्रुटि_सं = aio_error(cblock);
	अगर (aio_त्रुटि_सं == EINPROGRESS)
		वापस 0;

	written = aio_ret = aio_वापस(cblock);
	अगर (aio_ret < 0) अणु
		अगर (aio_त्रुटि_सं != EINTR)
			pr_err("failed to write perf data, error: %m\n");
		written = 0;
	पूर्ण

	rem_size = cblock->aio_nbytes - written;

	अगर (rem_size == 0) अणु
		cblock->aio_fildes = -1;
		/*
		 * md->refcount is incremented in record__aio_pushfn() क्रम
		 * every aio ग_लिखो request started in record__aio_push() so
		 * decrement it because the request is now complete.
		 */
		perf_mmap__put(&md->core);
		rc = 1;
	पूर्ण अन्यथा अणु
		/*
		 * aio ग_लिखो request may require restart with the
		 * reminder अगर the kernel didn't ग_लिखो whole
		 * chunk at once.
		 */
		rem_off = cblock->aio_offset + written;
		rem_buf = (व्योम *)(cblock->aio_buf + written);
		record__aio_ग_लिखो(cblock, cblock->aio_fildes,
				rem_buf, rem_size, rem_off);
		rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक record__aio_sync(काष्ठा mmap *md, bool sync_all)
अणु
	काष्ठा aiocb **aiocb = md->aio.aiocb;
	काष्ठा aiocb *cblocks = md->aio.cblocks;
	काष्ठा बारpec समयout = अणु 0, 1000 * 1000  * 1 पूर्ण; /* 1ms */
	पूर्णांक i, करो_suspend;

	करो अणु
		करो_suspend = 0;
		क्रम (i = 0; i < md->aio.nr_cblocks; ++i) अणु
			अगर (cblocks[i].aio_fildes == -1 || record__aio_complete(md, &cblocks[i])) अणु
				अगर (sync_all)
					aiocb[i] = शून्य;
				अन्यथा
					वापस i;
			पूर्ण अन्यथा अणु
				/*
				 * Started aio ग_लिखो is not complete yet
				 * so it has to be रुकोed beक्रमe the
				 * next allocation.
				 */
				aiocb[i] = &cblocks[i];
				करो_suspend = 1;
			पूर्ण
		पूर्ण
		अगर (!करो_suspend)
			वापस -1;

		जबतक (aio_suspend((स्थिर काष्ठा aiocb **)aiocb, md->aio.nr_cblocks, &समयout)) अणु
			अगर (!(त्रुटि_सं == EAGAIN || त्रुटि_सं == EINTR))
				pr_err("failed to sync perf data, error: %m\n");
		पूर्ण
	पूर्ण जबतक (1);
पूर्ण

काष्ठा record_aio अणु
	काष्ठा record	*rec;
	व्योम		*data;
	माप_प्रकार		size;
पूर्ण;

अटल पूर्णांक record__aio_pushfn(काष्ठा mmap *map, व्योम *to, व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा record_aio *aio = to;

	/*
	 * map->core.base data poपूर्णांकed by buf is copied पूर्णांकo मुक्त map->aio.data[] buffer
	 * to release space in the kernel buffer as fast as possible, calling
	 * perf_mmap__consume() from perf_mmap__push() function.
	 *
	 * That lets the kernel to proceed with storing more profiling data पूर्णांकo
	 * the kernel buffer earlier than other per-cpu kernel buffers are handled.
	 *
	 * Coping can be करोne in two steps in हाल the chunk of profiling data
	 * crosses the upper bound of the kernel buffer. In this हाल we first move
	 * part of data from map->start till the upper bound and then the reminder
	 * from the beginning of the kernel buffer till the end of the data chunk.
	 */

	अगर (record__comp_enabled(aio->rec)) अणु
		size = zstd_compress(aio->rec->session, aio->data + aio->size,
				     mmap__mmap_len(map) - aio->size,
				     buf, size);
	पूर्ण अन्यथा अणु
		स_नकल(aio->data + aio->size, buf, size);
	पूर्ण

	अगर (!aio->size) अणु
		/*
		 * Increment map->refcount to guard map->aio.data[] buffer
		 * from premature deallocation because map object can be
		 * released earlier than aio ग_लिखो request started on
		 * map->aio.data[] buffer is complete.
		 *
		 * perf_mmap__put() is करोne at record__aio_complete()
		 * after started aio request completion or at record__aio_push()
		 * अगर the request failed to start.
		 */
		perf_mmap__get(&map->core);
	पूर्ण

	aio->size += size;

	वापस size;
पूर्ण

अटल पूर्णांक record__aio_push(काष्ठा record *rec, काष्ठा mmap *map, off_t *off)
अणु
	पूर्णांक ret, idx;
	पूर्णांक trace_fd = rec->session->data->file.fd;
	काष्ठा record_aio aio = अणु .rec = rec, .size = 0 पूर्ण;

	/*
	 * Call record__aio_sync() to रुको till map->aio.data[] buffer
	 * becomes available after previous aio ग_लिखो operation.
	 */

	idx = record__aio_sync(map, false);
	aio.data = map->aio.data[idx];
	ret = perf_mmap__push(map, &aio, record__aio_pushfn);
	अगर (ret != 0) /* ret > 0 - no data, ret < 0 - error */
		वापस ret;

	rec->samples++;
	ret = record__aio_ग_लिखो(&(map->aio.cblocks[idx]), trace_fd, aio.data, aio.size, *off);
	अगर (!ret) अणु
		*off += aio.size;
		rec->bytes_written += aio.size;
		अगर (चयन_output_size(rec))
			trigger_hit(&चयन_output_trigger);
	पूर्ण अन्यथा अणु
		/*
		 * Decrement map->refcount incremented in record__aio_pushfn()
		 * back अगर record__aio_ग_लिखो() operation failed to start, otherwise
		 * map->refcount is decremented in record__aio_complete() after
		 * aio ग_लिखो operation finishes successfully.
		 */
		perf_mmap__put(&map->core);
	पूर्ण

	वापस ret;
पूर्ण

अटल off_t record__aio_get_pos(पूर्णांक trace_fd)
अणु
	वापस lseek(trace_fd, 0, प्रस्तुत_से);
पूर्ण

अटल व्योम record__aio_set_pos(पूर्णांक trace_fd, off_t pos)
अणु
	lseek(trace_fd, pos, शुरू_से);
पूर्ण

अटल व्योम record__aio_mmap_पढ़ो_sync(काष्ठा record *rec)
अणु
	पूर्णांक i;
	काष्ठा evlist *evlist = rec->evlist;
	काष्ठा mmap *maps = evlist->mmap;

	अगर (!record__aio_enabled(rec))
		वापस;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		काष्ठा mmap *map = &maps[i];

		अगर (map->core.base)
			record__aio_sync(map, true);
	पूर्ण
पूर्ण

अटल पूर्णांक nr_cblocks_शेष = 1;
अटल पूर्णांक nr_cblocks_max = 4;

अटल पूर्णांक record__aio_parse(स्थिर काष्ठा option *opt,
			     स्थिर अक्षर *str,
			     पूर्णांक unset)
अणु
	काष्ठा record_opts *opts = (काष्ठा record_opts *)opt->value;

	अगर (unset) अणु
		opts->nr_cblocks = 0;
	पूर्ण अन्यथा अणु
		अगर (str)
			opts->nr_cblocks = म_से_दीर्घ(str, शून्य, 0);
		अगर (!opts->nr_cblocks)
			opts->nr_cblocks = nr_cblocks_शेष;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा /* HAVE_AIO_SUPPORT */
अटल पूर्णांक nr_cblocks_max = 0;

अटल पूर्णांक record__aio_push(काष्ठा record *rec __maybe_unused, काष्ठा mmap *map __maybe_unused,
			    off_t *off __maybe_unused)
अणु
	वापस -1;
पूर्ण

अटल off_t record__aio_get_pos(पूर्णांक trace_fd __maybe_unused)
अणु
	वापस -1;
पूर्ण

अटल व्योम record__aio_set_pos(पूर्णांक trace_fd __maybe_unused, off_t pos __maybe_unused)
अणु
पूर्ण

अटल व्योम record__aio_mmap_पढ़ो_sync(काष्ठा record *rec __maybe_unused)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक record__aio_enabled(काष्ठा record *rec)
अणु
	वापस rec->opts.nr_cblocks > 0;
पूर्ण

#घोषणा MMAP_FLUSH_DEFAULT 1
अटल पूर्णांक record__mmap_flush_parse(स्थिर काष्ठा option *opt,
				    स्थिर अक्षर *str,
				    पूर्णांक unset)
अणु
	पूर्णांक flush_max;
	काष्ठा record_opts *opts = (काष्ठा record_opts *)opt->value;
	अटल काष्ठा parse_tag tags[] = अणु
			अणु .tag  = 'B', .mult = 1       पूर्ण,
			अणु .tag  = 'K', .mult = 1 << 10 पूर्ण,
			अणु .tag  = 'M', .mult = 1 << 20 पूर्ण,
			अणु .tag  = 'G', .mult = 1 << 30 पूर्ण,
			अणु .tag  = 0 पूर्ण,
	पूर्ण;

	अगर (unset)
		वापस 0;

	अगर (str) अणु
		opts->mmap_flush = parse_tag_value(str, tags);
		अगर (opts->mmap_flush == (पूर्णांक)-1)
			opts->mmap_flush = म_से_दीर्घ(str, शून्य, 0);
	पूर्ण

	अगर (!opts->mmap_flush)
		opts->mmap_flush = MMAP_FLUSH_DEFAULT;

	flush_max = evlist__mmap_size(opts->mmap_pages);
	flush_max /= 4;
	अगर (opts->mmap_flush > flush_max)
		opts->mmap_flush = flush_max;

	वापस 0;
पूर्ण

#अगर_घोषित HAVE_ZSTD_SUPPORT
अटल अचिन्हित पूर्णांक comp_level_शेष = 1;

अटल पूर्णांक record__parse_comp_level(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	काष्ठा record_opts *opts = opt->value;

	अगर (unset) अणु
		opts->comp_level = 0;
	पूर्ण अन्यथा अणु
		अगर (str)
			opts->comp_level = म_से_दीर्घ(str, शून्य, 0);
		अगर (!opts->comp_level)
			opts->comp_level = comp_level_शेष;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल अचिन्हित पूर्णांक comp_level_max = 22;

अटल पूर्णांक record__comp_enabled(काष्ठा record *rec)
अणु
	वापस rec->opts.comp_level > 0;
पूर्ण

अटल पूर्णांक process_synthesized_event(काष्ठा perf_tool *tool,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample __maybe_unused,
				     काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा record *rec = container_of(tool, काष्ठा record, tool);
	वापस record__ग_लिखो(rec, शून्य, event, event->header.size);
पूर्ण

अटल पूर्णांक process_locked_synthesized_event(काष्ठा perf_tool *tool,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample __maybe_unused,
				     काष्ठा machine *machine __maybe_unused)
अणु
	अटल pthपढ़ो_mutex_t synth_lock = PTHREAD_MUTEX_INITIALIZER;
	पूर्णांक ret;

	pthपढ़ो_mutex_lock(&synth_lock);
	ret = process_synthesized_event(tool, event, sample, machine);
	pthपढ़ो_mutex_unlock(&synth_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक record__pushfn(काष्ठा mmap *map, व्योम *to, व्योम *bf, माप_प्रकार size)
अणु
	काष्ठा record *rec = to;

	अगर (record__comp_enabled(rec)) अणु
		size = zstd_compress(rec->session, map->data, mmap__mmap_len(map), bf, size);
		bf   = map->data;
	पूर्ण

	rec->samples++;
	वापस record__ग_लिखो(rec, map, bf, size);
पूर्ण

अटल अस्थिर पूर्णांक signr = -1;
अटल अस्थिर पूर्णांक child_finished;
#अगर_घोषित HAVE_EVENTFD_SUPPORT
अटल पूर्णांक करोne_fd = -1;
#पूर्ण_अगर

अटल व्योम sig_handler(पूर्णांक sig)
अणु
	अगर (sig == SIGCHLD)
		child_finished = 1;
	अन्यथा
		signr = sig;

	करोne = 1;
#अगर_घोषित HAVE_EVENTFD_SUPPORT
अणु
	u64 पंचांगp = 1;
	/*
	 * It is possible क्रम this संकेत handler to run after करोne is checked
	 * in the मुख्य loop, but beक्रमe the perf counter fds are polled. If this
	 * happens, the poll() will जारी to रुको even though करोne is set,
	 * and will only अवरोध out अगर either another संकेत is received, or the
	 * counters are पढ़ोy क्रम पढ़ो. To ensure the poll() करोesn't sleep when
	 * करोne is set, use an eventfd (करोne_fd) to wake up the poll().
	 */
	अगर (ग_लिखो(करोne_fd, &पंचांगp, माप(पंचांगp)) < 0)
		pr_err("failed to signal wakeup fd, error: %m\n");
पूर्ण
#पूर्ण_अगर // HAVE_EVENTFD_SUPPORT
पूर्ण

अटल व्योम sigsegv_handler(पूर्णांक sig)
अणु
	perf_hooks__recover();
	sighandler_dump_stack(sig);
पूर्ण

अटल व्योम record__sig_निकास(व्योम)
अणु
	अगर (signr == -1)
		वापस;

	संकेत(signr, संक_पूर्व);
	उठाओ(signr);
पूर्ण

#अगर_घोषित HAVE_AUXTRACE_SUPPORT

अटल पूर्णांक record__process_auxtrace(काष्ठा perf_tool *tool,
				    काष्ठा mmap *map,
				    जोड़ perf_event *event, व्योम *data1,
				    माप_प्रकार len1, व्योम *data2, माप_प्रकार len2)
अणु
	काष्ठा record *rec = container_of(tool, काष्ठा record, tool);
	काष्ठा perf_data *data = &rec->data;
	माप_प्रकार padding;
	u8 pad[8] = अणु0पूर्ण;

	अगर (!perf_data__is_pipe(data) && perf_data__is_single_file(data)) अणु
		off_t file_offset;
		पूर्णांक fd = perf_data__fd(data);
		पूर्णांक err;

		file_offset = lseek(fd, 0, प्रस्तुत_से);
		अगर (file_offset == -1)
			वापस -1;
		err = auxtrace_index__auxtrace_event(&rec->session->auxtrace_index,
						     event, file_offset);
		अगर (err)
			वापस err;
	पूर्ण

	/* event.auxtrace.size includes padding, see __auxtrace_mmap__पढ़ो() */
	padding = (len1 + len2) & 7;
	अगर (padding)
		padding = 8 - padding;

	record__ग_लिखो(rec, map, event, event->header.size);
	record__ग_लिखो(rec, map, data1, len1);
	अगर (len2)
		record__ग_लिखो(rec, map, data2, len2);
	record__ग_लिखो(rec, map, &pad, padding);

	वापस 0;
पूर्ण

अटल पूर्णांक record__auxtrace_mmap_पढ़ो(काष्ठा record *rec,
				      काष्ठा mmap *map)
अणु
	पूर्णांक ret;

	ret = auxtrace_mmap__पढ़ो(map, rec->itr, &rec->tool,
				  record__process_auxtrace);
	अगर (ret < 0)
		वापस ret;

	अगर (ret)
		rec->samples++;

	वापस 0;
पूर्ण

अटल पूर्णांक record__auxtrace_mmap_पढ़ो_snapshot(काष्ठा record *rec,
					       काष्ठा mmap *map)
अणु
	पूर्णांक ret;

	ret = auxtrace_mmap__पढ़ो_snapshot(map, rec->itr, &rec->tool,
					   record__process_auxtrace,
					   rec->opts.auxtrace_snapshot_size);
	अगर (ret < 0)
		वापस ret;

	अगर (ret)
		rec->samples++;

	वापस 0;
पूर्ण

अटल पूर्णांक record__auxtrace_पढ़ो_snapshot_all(काष्ठा record *rec)
अणु
	पूर्णांक i;
	पूर्णांक rc = 0;

	क्रम (i = 0; i < rec->evlist->core.nr_mmaps; i++) अणु
		काष्ठा mmap *map = &rec->evlist->mmap[i];

		अगर (!map->auxtrace_mmap.base)
			जारी;

		अगर (record__auxtrace_mmap_पढ़ो_snapshot(rec, map) != 0) अणु
			rc = -1;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल व्योम record__पढ़ो_auxtrace_snapshot(काष्ठा record *rec, bool on_निकास)
अणु
	pr_debug("Recording AUX area tracing snapshot\n");
	अगर (record__auxtrace_पढ़ो_snapshot_all(rec) < 0) अणु
		trigger_error(&auxtrace_snapshot_trigger);
	पूर्ण अन्यथा अणु
		अगर (auxtrace_record__snapshot_finish(rec->itr, on_निकास))
			trigger_error(&auxtrace_snapshot_trigger);
		अन्यथा
			trigger_पढ़ोy(&auxtrace_snapshot_trigger);
	पूर्ण
पूर्ण

अटल पूर्णांक record__auxtrace_snapshot_निकास(काष्ठा record *rec)
अणु
	अगर (trigger_is_error(&auxtrace_snapshot_trigger))
		वापस 0;

	अगर (!auxtrace_record__snapshot_started &&
	    auxtrace_record__snapshot_start(rec->itr))
		वापस -1;

	record__पढ़ो_auxtrace_snapshot(rec, true);
	अगर (trigger_is_error(&auxtrace_snapshot_trigger))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक record__auxtrace_init(काष्ठा record *rec)
अणु
	पूर्णांक err;

	अगर (!rec->itr) अणु
		rec->itr = auxtrace_record__init(rec->evlist, &err);
		अगर (err)
			वापस err;
	पूर्ण

	err = auxtrace_parse_snapshot_options(rec->itr, &rec->opts,
					      rec->opts.auxtrace_snapshot_opts);
	अगर (err)
		वापस err;

	err = auxtrace_parse_sample_options(rec->itr, rec->evlist, &rec->opts,
					    rec->opts.auxtrace_sample_opts);
	अगर (err)
		वापस err;

	auxtrace_regroup_aux_output(rec->evlist);

	वापस auxtrace_parse_filters(rec->evlist);
पूर्ण

#अन्यथा

अटल अंतरभूत
पूर्णांक record__auxtrace_mmap_पढ़ो(काष्ठा record *rec __maybe_unused,
			       काष्ठा mmap *map __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम record__पढ़ो_auxtrace_snapshot(काष्ठा record *rec __maybe_unused,
				    bool on_निकास __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace_record__snapshot_start(काष्ठा auxtrace_record *itr __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक record__auxtrace_snapshot_निकास(काष्ठा record *rec __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक record__auxtrace_init(काष्ठा record *rec __maybe_unused)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक record__config_text_poke(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err;

	/* Nothing to करो अगर text poke is alपढ़ोy configured */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.text_poke)
			वापस 0;
	पूर्ण

	err = parse_events(evlist, "dummy:u", शून्य);
	अगर (err)
		वापस err;

	evsel = evlist__last(evlist);

	evsel->core.attr.freq = 0;
	evsel->core.attr.sample_period = 1;
	evsel->core.attr.text_poke = 1;
	evsel->core.attr.ksymbol = 1;

	evsel->core.प्रणाली_wide = true;
	evsel->no_aux_samples = true;
	evsel->immediate = true;

	/* Text poke must be collected on all CPUs */
	perf_cpu_map__put(evsel->core.own_cpus);
	evsel->core.own_cpus = perf_cpu_map__new(शून्य);
	perf_cpu_map__put(evsel->core.cpus);
	evsel->core.cpus = perf_cpu_map__get(evsel->core.own_cpus);

	evsel__set_sample_bit(evsel, TIME);

	वापस 0;
पूर्ण

अटल bool record__kcore_पढ़ोable(काष्ठा machine *machine)
अणु
	अक्षर kcore[PATH_MAX];
	पूर्णांक fd;

	scnम_लिखो(kcore, माप(kcore), "%s/proc/kcore", machine->root_dir);

	fd = खोलो(kcore, O_RDONLY);
	अगर (fd < 0)
		वापस false;

	बंद(fd);

	वापस true;
पूर्ण

अटल पूर्णांक record__kcore_copy(काष्ठा machine *machine, काष्ठा perf_data *data)
अणु
	अक्षर from_dir[PATH_MAX];
	अक्षर kcore_dir[PATH_MAX];
	पूर्णांक ret;

	snम_लिखो(from_dir, माप(from_dir), "%s/proc", machine->root_dir);

	ret = perf_data__make_kcore_dir(data, kcore_dir, माप(kcore_dir));
	अगर (ret)
		वापस ret;

	वापस kcore_copy(from_dir, kcore_dir);
पूर्ण

अटल पूर्णांक record__mmap_evlist(काष्ठा record *rec,
			       काष्ठा evlist *evlist)
अणु
	काष्ठा record_opts *opts = &rec->opts;
	bool auxtrace_overग_लिखो = opts->auxtrace_snapshot_mode ||
				  opts->auxtrace_sample_mode;
	अक्षर msg[512];

	अगर (opts->affinity != PERF_AFFINITY_SYS)
		cpu__setup_cpunode_map();

	अगर (evlist__mmap_ex(evlist, opts->mmap_pages,
				 opts->auxtrace_mmap_pages,
				 auxtrace_overग_लिखो,
				 opts->nr_cblocks, opts->affinity,
				 opts->mmap_flush, opts->comp_level) < 0) अणु
		अगर (त्रुटि_सं == EPERM) अणु
			pr_err("Permission error mapping pages.\n"
			       "Consider increasing "
			       "/proc/sys/kernel/perf_event_mlock_kb,\n"
			       "or try again with a smaller value of -m/--mmap_pages.\n"
			       "(current value: %u,%u)\n",
			       opts->mmap_pages, opts->auxtrace_mmap_pages);
			वापस -त्रुटि_सं;
		पूर्ण अन्यथा अणु
			pr_err("failed to mmap with %d (%s)\n", त्रुटि_सं,
				str_error_r(त्रुटि_सं, msg, माप(msg)));
			अगर (त्रुटि_सं)
				वापस -त्रुटि_सं;
			अन्यथा
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक record__mmap(काष्ठा record *rec)
अणु
	वापस record__mmap_evlist(rec, rec->evlist);
पूर्ण

अटल पूर्णांक record__खोलो(काष्ठा record *rec)
अणु
	अक्षर msg[बफ_मान];
	काष्ठा evsel *pos;
	काष्ठा evlist *evlist = rec->evlist;
	काष्ठा perf_session *session = rec->session;
	काष्ठा record_opts *opts = &rec->opts;
	पूर्णांक rc = 0;

	/*
	 * For initial_delay or प्रणाली wide, we need to add a dummy event so
	 * that we can track PERF_RECORD_MMAP to cover the delay of रुकोing or
	 * event synthesis.
	 */
	अगर (opts->initial_delay || target__has_cpu(&opts->target)) अणु
		pos = evlist__get_tracking_event(evlist);
		अगर (!evsel__is_dummy_event(pos)) अणु
			/* Set up dummy event. */
			अगर (evlist__add_dummy(evlist))
				वापस -ENOMEM;
			pos = evlist__last(evlist);
			evlist__set_tracking_event(evlist, pos);
		पूर्ण

		/*
		 * Enable the dummy event when the process is विभाजनed क्रम
		 * initial_delay, immediately क्रम प्रणाली wide.
		 */
		अगर (opts->initial_delay && !pos->immediate)
			pos->core.attr.enable_on_exec = 1;
		अन्यथा
			pos->immediate = 1;
	पूर्ण

	evlist__config(evlist, opts, &callchain_param);

	evlist__क्रम_each_entry(evlist, pos) अणु
try_again:
		अगर (evsel__खोलो(pos, pos->core.cpus, pos->core.thपढ़ोs) < 0) अणु
			अगर (evsel__fallback(pos, त्रुटि_सं, msg, माप(msg))) अणु
				अगर (verbose > 0)
					ui__warning("%s\n", msg);
				जाओ try_again;
			पूर्ण
			अगर ((त्रुटि_सं == EINVAL || त्रुटि_सं == EBADF) &&
			    pos->leader != pos &&
			    pos->weak_group) अणु
			        pos = evlist__reset_weak_group(evlist, pos, true);
				जाओ try_again;
			पूर्ण
			rc = -त्रुटि_सं;
			evsel__खोलो_म_त्रुटि(pos, &opts->target, त्रुटि_सं, msg, माप(msg));
			ui__error("%s\n", msg);
			जाओ out;
		पूर्ण

		pos->supported = true;
	पूर्ण

	अगर (symbol_conf.kptr_restrict && !evlist__exclude_kernel(evlist)) अणु
		pr_warning(
"WARNING: Kernel address maps (/proc/{kallsyms,modules}) are restricted,\n"
"check /proc/sys/kernel/kptr_restrict and /proc/sys/kernel/perf_event_paranoid.\n\n"
"Samples in kernel functions may not be resolved if a suitable vmlinux\n"
"file is not found in the buildid cache or in the vmlinux path.\n\n"
"Samples in kernel modules won't be resolved at all.\n\n"
"If some relocation was applied (e.g. kexec) symbols may be misresolved\n"
"even with a suitable vmlinux or kallsyms file.\n\n");
	पूर्ण

	अगर (evlist__apply_filters(evlist, &pos)) अणु
		pr_err("failed to set filter \"%s\" on event %s with %d (%s)\n",
			pos->filter, evsel__name(pos), त्रुटि_सं,
			str_error_r(त्रुटि_सं, msg, माप(msg)));
		rc = -1;
		जाओ out;
	पूर्ण

	rc = record__mmap(rec);
	अगर (rc)
		जाओ out;

	session->evlist = evlist;
	perf_session__set_id_hdr_size(session);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	काष्ठा record *rec = container_of(tool, काष्ठा record, tool);

	अगर (rec->evlist->first_sample_समय == 0)
		rec->evlist->first_sample_समय = sample->समय;

	rec->evlist->last_sample_समय = sample->समय;

	अगर (rec->buildid_all)
		वापस 0;

	rec->samples++;
	वापस build_id__mark_dso_hit(tool, event, sample, evsel, machine);
पूर्ण

अटल पूर्णांक process_buildids(काष्ठा record *rec)
अणु
	काष्ठा perf_session *session = rec->session;

	अगर (perf_data__size(&rec->data) == 0)
		वापस 0;

	/*
	 * During this process, it'll load kernel map and replace the
	 * dso->दीर्घ_name to a real pathname it found.  In this हाल
	 * we prefer the vmlinux path like
	 *   /lib/modules/3.16.4/build/vmlinux
	 *
	 * rather than build-id path (in debug directory).
	 *   $HOME/.debug/.build-id/f0/6e17aa50adf4d00b88925e03775de107611551
	 */
	symbol_conf.ignore_vmlinux_buildid = true;

	/*
	 * If --buildid-all is given, it marks all DSO regardless of hits,
	 * so no need to process samples. But अगर बारtamp_boundary is enabled,
	 * it still needs to walk on all samples to get the बारtamps of
	 * first/last samples.
	 */
	अगर (rec->buildid_all && !rec->बारtamp_boundary)
		rec->tool.sample = शून्य;

	वापस perf_session__process_events(session);
पूर्ण

अटल व्योम perf_event__synthesize_guest_os(काष्ठा machine *machine, व्योम *data)
अणु
	पूर्णांक err;
	काष्ठा perf_tool *tool = data;
	/*
	 *As क्रम guest kernel when processing subcommand record&report,
	 *we arrange module mmap prior to guest kernel mmap and trigger
	 *a preload dso because शेष guest module symbols are loaded
	 *from guest kallsyms instead of /lib/modules/XXX/XXX. This
	 *method is used to aव्योम symbol missing when the first addr is
	 *in module instead of in guest kernel.
	 */
	err = perf_event__synthesize_modules(tool, process_synthesized_event,
					     machine);
	अगर (err < 0)
		pr_err("Couldn't record guest kernel [%d]'s reference"
		       " relocation symbol.\n", machine->pid);

	/*
	 * We use _stext क्रम guest kernel because guest kernel's /proc/kallsyms
	 * have no _text someबार.
	 */
	err = perf_event__synthesize_kernel_mmap(tool, process_synthesized_event,
						 machine);
	अगर (err < 0)
		pr_err("Couldn't record guest kernel [%d]'s reference"
		       " relocation symbol.\n", machine->pid);
पूर्ण

अटल काष्ठा perf_event_header finished_round_event = अणु
	.size = माप(काष्ठा perf_event_header),
	.type = PERF_RECORD_FINISHED_ROUND,
पूर्ण;

अटल व्योम record__adjust_affinity(काष्ठा record *rec, काष्ठा mmap *map)
अणु
	अगर (rec->opts.affinity != PERF_AFFINITY_SYS &&
	    !biपंचांगap_equal(rec->affinity_mask.bits, map->affinity_mask.bits,
			  rec->affinity_mask.nbits)) अणु
		biपंचांगap_zero(rec->affinity_mask.bits, rec->affinity_mask.nbits);
		biपंचांगap_or(rec->affinity_mask.bits, rec->affinity_mask.bits,
			  map->affinity_mask.bits, rec->affinity_mask.nbits);
		sched_setaffinity(0, MMAP_CPU_MASK_BYTES(&rec->affinity_mask),
				  (cpu_set_t *)rec->affinity_mask.bits);
		अगर (verbose == 2)
			mmap_cpu_mask__scnम_लिखो(&rec->affinity_mask, "thread");
	पूर्ण
पूर्ण

अटल माप_प्रकार process_comp_header(व्योम *record, माप_प्रकार increment)
अणु
	काष्ठा perf_record_compressed *event = record;
	माप_प्रकार size = माप(*event);

	अगर (increment) अणु
		event->header.size += increment;
		वापस increment;
	पूर्ण

	event->header.type = PERF_RECORD_COMPRESSED;
	event->header.size = size;

	वापस size;
पूर्ण

अटल माप_प्रकार zstd_compress(काष्ठा perf_session *session, व्योम *dst, माप_प्रकार dst_size,
			    व्योम *src, माप_प्रकार src_size)
अणु
	माप_प्रकार compressed;
	माप_प्रकार max_record_size = PERF_SAMPLE_MAX_SIZE - माप(काष्ठा perf_record_compressed) - 1;

	compressed = zstd_compress_stream_to_records(&session->zstd_data, dst, dst_size, src, src_size,
						     max_record_size, process_comp_header);

	session->bytes_transferred += src_size;
	session->bytes_compressed  += compressed;

	वापस compressed;
पूर्ण

अटल पूर्णांक record__mmap_पढ़ो_evlist(काष्ठा record *rec, काष्ठा evlist *evlist,
				    bool overग_लिखो, bool synch)
अणु
	u64 bytes_written = rec->bytes_written;
	पूर्णांक i;
	पूर्णांक rc = 0;
	काष्ठा mmap *maps;
	पूर्णांक trace_fd = rec->data.file.fd;
	off_t off = 0;

	अगर (!evlist)
		वापस 0;

	maps = overग_लिखो ? evlist->overग_लिखो_mmap : evlist->mmap;
	अगर (!maps)
		वापस 0;

	अगर (overग_लिखो && evlist->bkw_mmap_state != BKW_MMAP_DATA_PENDING)
		वापस 0;

	अगर (record__aio_enabled(rec))
		off = record__aio_get_pos(trace_fd);

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		u64 flush = 0;
		काष्ठा mmap *map = &maps[i];

		अगर (map->core.base) अणु
			record__adjust_affinity(rec, map);
			अगर (synch) अणु
				flush = map->core.flush;
				map->core.flush = 1;
			पूर्ण
			अगर (!record__aio_enabled(rec)) अणु
				अगर (perf_mmap__push(map, rec, record__pushfn) < 0) अणु
					अगर (synch)
						map->core.flush = flush;
					rc = -1;
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (record__aio_push(rec, map, &off) < 0) अणु
					record__aio_set_pos(trace_fd, off);
					अगर (synch)
						map->core.flush = flush;
					rc = -1;
					जाओ out;
				पूर्ण
			पूर्ण
			अगर (synch)
				map->core.flush = flush;
		पूर्ण

		अगर (map->auxtrace_mmap.base && !rec->opts.auxtrace_snapshot_mode &&
		    !rec->opts.auxtrace_sample_mode &&
		    record__auxtrace_mmap_पढ़ो(rec, map) != 0) अणु
			rc = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (record__aio_enabled(rec))
		record__aio_set_pos(trace_fd, off);

	/*
	 * Mark the round finished in हाल we wrote
	 * at least one event.
	 */
	अगर (bytes_written != rec->bytes_written)
		rc = record__ग_लिखो(rec, शून्य, &finished_round_event, माप(finished_round_event));

	अगर (overग_लिखो)
		evlist__toggle_bkw_mmap(evlist, BKW_MMAP_EMPTY);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक record__mmap_पढ़ो_all(काष्ठा record *rec, bool synch)
अणु
	पूर्णांक err;

	err = record__mmap_पढ़ो_evlist(rec, rec->evlist, false, synch);
	अगर (err)
		वापस err;

	वापस record__mmap_पढ़ो_evlist(rec, rec->evlist, true, synch);
पूर्ण

अटल व्योम record__init_features(काष्ठा record *rec)
अणु
	काष्ठा perf_session *session = rec->session;
	पूर्णांक feat;

	क्रम (feat = HEADER_FIRST_FEATURE; feat < HEADER_LAST_FEATURE; feat++)
		perf_header__set_feat(&session->header, feat);

	अगर (rec->no_buildid)
		perf_header__clear_feat(&session->header, HEADER_BUILD_ID);

	अगर (!have_tracepoपूर्णांकs(&rec->evlist->core.entries))
		perf_header__clear_feat(&session->header, HEADER_TRACING_DATA);

	अगर (!rec->opts.branch_stack)
		perf_header__clear_feat(&session->header, HEADER_BRANCH_STACK);

	अगर (!rec->opts.full_auxtrace)
		perf_header__clear_feat(&session->header, HEADER_AUXTRACE);

	अगर (!(rec->opts.use_घड़ीid && rec->opts.घड़ीid_res_ns))
		perf_header__clear_feat(&session->header, HEADER_CLOCKID);

	अगर (!rec->opts.use_घड़ीid)
		perf_header__clear_feat(&session->header, HEADER_CLOCK_DATA);

	perf_header__clear_feat(&session->header, HEADER_सूची_FORMAT);
	अगर (!record__comp_enabled(rec))
		perf_header__clear_feat(&session->header, HEADER_COMPRESSED);

	perf_header__clear_feat(&session->header, HEADER_STAT);
पूर्ण

अटल व्योम
record__finish_output(काष्ठा record *rec)
अणु
	काष्ठा perf_data *data = &rec->data;
	पूर्णांक fd = perf_data__fd(data);

	अगर (data->is_pipe)
		वापस;

	rec->session->header.data_size += rec->bytes_written;
	data->file.size = lseek(perf_data__fd(data), 0, प्रस्तुत_से);

	अगर (!rec->no_buildid) अणु
		process_buildids(rec);

		अगर (rec->buildid_all)
			dsos__hit_all(rec->session);
	पूर्ण
	perf_session__ग_लिखो_header(rec->session, rec->evlist, fd, true);

	वापस;
पूर्ण

अटल पूर्णांक record__synthesize_workload(काष्ठा record *rec, bool tail)
अणु
	पूर्णांक err;
	काष्ठा perf_thपढ़ो_map *thपढ़ो_map;

	अगर (rec->opts.tail_synthesize != tail)
		वापस 0;

	thपढ़ो_map = thपढ़ो_map__new_by_tid(rec->evlist->workload.pid);
	अगर (thपढ़ो_map == शून्य)
		वापस -1;

	err = perf_event__syntheमाप_प्रकारhपढ़ो_map(&rec->tool, thपढ़ो_map,
						 process_synthesized_event,
						 &rec->session->machines.host,
						 rec->opts.sample_address);
	perf_thपढ़ो_map__put(thपढ़ो_map);
	वापस err;
पूर्ण

अटल पूर्णांक record__synthesize(काष्ठा record *rec, bool tail);

अटल पूर्णांक
record__चयन_output(काष्ठा record *rec, bool at_निकास)
अणु
	काष्ठा perf_data *data = &rec->data;
	पूर्णांक fd, err;
	अक्षर *new_filename;

	/* Same Size:      "2015122520103046"*/
	अक्षर बारtamp[] = "InvalidTimestamp";

	record__aio_mmap_पढ़ो_sync(rec);

	record__synthesize(rec, true);
	अगर (target__none(&rec->opts.target))
		record__synthesize_workload(rec, true);

	rec->samples = 0;
	record__finish_output(rec);
	err = fetch_current_बारtamp(बारtamp, माप(बारtamp));
	अगर (err) अणु
		pr_err("Failed to get current timestamp\n");
		वापस -EINVAL;
	पूर्ण

	fd = perf_data__चयन(data, बारtamp,
				    rec->session->header.data_offset,
				    at_निकास, &new_filename);
	अगर (fd >= 0 && !at_निकास) अणु
		rec->bytes_written = 0;
		rec->session->header.data_size = 0;
	पूर्ण

	अगर (!quiet)
		ख_लिखो(मानक_त्रुटि, "[ perf record: Dump %s.%s ]\n",
			data->path, बारtamp);

	अगर (rec->चयन_output.num_files) अणु
		पूर्णांक n = rec->चयन_output.cur_file + 1;

		अगर (n >= rec->चयन_output.num_files)
			n = 0;
		rec->चयन_output.cur_file = n;
		अगर (rec->चयन_output.filenames[n]) अणु
			हटाओ(rec->चयन_output.filenames[n]);
			zमुक्त(&rec->चयन_output.filenames[n]);
		पूर्ण
		rec->चयन_output.filenames[n] = new_filename;
	पूर्ण अन्यथा अणु
		मुक्त(new_filename);
	पूर्ण

	/* Output tracking events */
	अगर (!at_निकास) अणु
		record__synthesize(rec, false);

		/*
		 * In 'perf record --switch-output' without -a,
		 * record__synthesize() in record__चयन_output() won't
		 * generate tracking events because there's no thपढ़ो_map
		 * in evlist. Which causes newly created perf.data करोesn't
		 * contain map and comm inक्रमmation.
		 * Create a fake thपढ़ो_map and directly call
		 * perf_event__syntheमाप_प्रकारhपढ़ो_map() क्रम those events.
		 */
		अगर (target__none(&rec->opts.target))
			record__synthesize_workload(rec, false);
	पूर्ण
	वापस fd;
पूर्ण

अटल अस्थिर पूर्णांक workload_exec_त्रुटि_सं;

/*
 * evlist__prepare_workload will send a SIGUSR1
 * अगर the विभाजन fails, since we asked by setting its
 * want_संकेत to true.
 */
अटल व्योम workload_exec_failed_संकेत(पूर्णांक signo __maybe_unused,
					siginfo_t *info,
					व्योम *ucontext __maybe_unused)
अणु
	workload_exec_त्रुटि_सं = info->si_value.sival_पूर्णांक;
	करोne = 1;
	child_finished = 1;
पूर्ण

अटल व्योम snapshot_sig_handler(पूर्णांक sig);
अटल व्योम alarm_sig_handler(पूर्णांक sig);

अटल स्थिर काष्ठा perf_event_mmap_page *evlist__pick_pc(काष्ठा evlist *evlist)
अणु
	अगर (evlist) अणु
		अगर (evlist->mmap && evlist->mmap[0].core.base)
			वापस evlist->mmap[0].core.base;
		अगर (evlist->overग_लिखो_mmap && evlist->overग_लिखो_mmap[0].core.base)
			वापस evlist->overग_लिखो_mmap[0].core.base;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा perf_event_mmap_page *record__pick_pc(काष्ठा record *rec)
अणु
	स्थिर काष्ठा perf_event_mmap_page *pc = evlist__pick_pc(rec->evlist);
	अगर (pc)
		वापस pc;
	वापस शून्य;
पूर्ण

अटल पूर्णांक record__synthesize(काष्ठा record *rec, bool tail)
अणु
	काष्ठा perf_session *session = rec->session;
	काष्ठा machine *machine = &session->machines.host;
	काष्ठा perf_data *data = &rec->data;
	काष्ठा record_opts *opts = &rec->opts;
	काष्ठा perf_tool *tool = &rec->tool;
	पूर्णांक fd = perf_data__fd(data);
	पूर्णांक err = 0;
	event_op f = process_synthesized_event;

	अगर (rec->opts.tail_synthesize != tail)
		वापस 0;

	अगर (data->is_pipe) अणु
		/*
		 * We need to synthesize events first, because some
		 * features works on top of them (on report side).
		 */
		err = perf_event__synthesize_attrs(tool, rec->evlist,
						   process_synthesized_event);
		अगर (err < 0) अणु
			pr_err("Couldn't synthesize attrs.\n");
			जाओ out;
		पूर्ण

		err = perf_event__synthesize_features(tool, session, rec->evlist,
						      process_synthesized_event);
		अगर (err < 0) अणु
			pr_err("Couldn't synthesize features.\n");
			वापस err;
		पूर्ण

		अगर (have_tracepoपूर्णांकs(&rec->evlist->core.entries)) अणु
			/*
			 * FIXME err <= 0 here actually means that
			 * there were no tracepoपूर्णांकs so its not really
			 * an error, just that we करोn't need to
			 * synthesize anything.  We really have to
			 * वापस this more properly and also
			 * propagate errors that now are calling die()
			 */
			err = perf_event__syntheमाप_प्रकारracing_data(tool,	fd, rec->evlist,
								  process_synthesized_event);
			अगर (err <= 0) अणु
				pr_err("Couldn't record tracing data.\n");
				जाओ out;
			पूर्ण
			rec->bytes_written += err;
		पूर्ण
	पूर्ण

	err = perf_event__synth_समय_conv(record__pick_pc(rec), tool,
					  process_synthesized_event, machine);
	अगर (err)
		जाओ out;

	/* Synthesize id_index beक्रमe auxtrace_info */
	अगर (rec->opts.auxtrace_sample_mode) अणु
		err = perf_event__synthesize_id_index(tool,
						      process_synthesized_event,
						      session->evlist, machine);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (rec->opts.full_auxtrace) अणु
		err = perf_event__synthesize_auxtrace_info(rec->itr, tool,
					session, process_synthesized_event);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (!evlist__exclude_kernel(rec->evlist)) अणु
		err = perf_event__synthesize_kernel_mmap(tool, process_synthesized_event,
							 machine);
		WARN_ONCE(err < 0, "Couldn't record kernel reference relocation symbol\n"
				   "Symbol resolution may be skewed if relocation was used (e.g. kexec).\n"
				   "Check /proc/kallsyms permission or run as root.\n");

		err = perf_event__synthesize_modules(tool, process_synthesized_event,
						     machine);
		WARN_ONCE(err < 0, "Couldn't record kernel module information.\n"
				   "Symbol resolution may be skewed if relocation was used (e.g. kexec).\n"
				   "Check /proc/modules permission or run as root.\n");
	पूर्ण

	अगर (perf_guest) अणु
		machines__process_guests(&session->machines,
					 perf_event__synthesize_guest_os, tool);
	पूर्ण

	err = perf_event__synthesize_extra_attr(&rec->tool,
						rec->evlist,
						process_synthesized_event,
						data->is_pipe);
	अगर (err)
		जाओ out;

	err = perf_event__syntheमाप_प्रकारhपढ़ो_map2(&rec->tool, rec->evlist->core.thपढ़ोs,
						 process_synthesized_event,
						शून्य);
	अगर (err < 0) अणु
		pr_err("Couldn't synthesize thread map.\n");
		वापस err;
	पूर्ण

	err = perf_event__synthesize_cpu_map(&rec->tool, rec->evlist->core.cpus,
					     process_synthesized_event, शून्य);
	अगर (err < 0) अणु
		pr_err("Couldn't synthesize cpu map.\n");
		वापस err;
	पूर्ण

	err = perf_event__synthesize_bpf_events(session, process_synthesized_event,
						machine, opts);
	अगर (err < 0)
		pr_warning("Couldn't synthesize bpf events.\n");

	err = perf_event__synthesize_cgroups(tool, process_synthesized_event,
					     machine);
	अगर (err < 0)
		pr_warning("Couldn't synthesize cgroup events.\n");

	अगर (rec->opts.nr_thपढ़ोs_synthesize > 1) अणु
		perf_set_multithपढ़ोed();
		f = process_locked_synthesized_event;
	पूर्ण

	err = __machine__syntheमाप_प्रकारhपढ़ोs(machine, tool, &opts->target, rec->evlist->core.thपढ़ोs,
					    f, opts->sample_address,
					    rec->opts.nr_thपढ़ोs_synthesize);

	अगर (rec->opts.nr_thपढ़ोs_synthesize > 1)
		perf_set_singlethपढ़ोed();

out:
	वापस err;
पूर्ण

अटल पूर्णांक record__process_संकेत_event(जोड़ perf_event *event __maybe_unused, व्योम *data)
अणु
	काष्ठा record *rec = data;
	pthपढ़ो_समाप्त(rec->thपढ़ो_id, SIGUSR2);
	वापस 0;
पूर्ण

अटल पूर्णांक record__setup_sb_evlist(काष्ठा record *rec)
अणु
	काष्ठा record_opts *opts = &rec->opts;

	अगर (rec->sb_evlist != शून्य) अणु
		/*
		 * We get here अगर --चयन-output-event populated the
		 * sb_evlist, so associate a callback that will send a SIGUSR2
		 * to the मुख्य thपढ़ो.
		 */
		evlist__set_cb(rec->sb_evlist, record__process_संकेत_event, rec);
		rec->thपढ़ो_id = pthपढ़ो_self();
	पूर्ण
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	अगर (!opts->no_bpf_event) अणु
		अगर (rec->sb_evlist == शून्य) अणु
			rec->sb_evlist = evlist__new();

			अगर (rec->sb_evlist == शून्य) अणु
				pr_err("Couldn't create side band evlist.\n.");
				वापस -1;
			पूर्ण
		पूर्ण

		अगर (evlist__add_bpf_sb_event(rec->sb_evlist, &rec->session->header.env)) अणु
			pr_err("Couldn't ask for PERF_RECORD_BPF_EVENT side band events.\n.");
			वापस -1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (evlist__start_sb_thपढ़ो(rec->sb_evlist, &rec->opts.target)) अणु
		pr_debug("Couldn't start the BPF side band thread:\nBPF programs starting from now on won't be annotatable\n");
		opts->no_bpf_event = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक record__init_घड़ी(काष्ठा record *rec)
अणु
	काष्ठा perf_session *session = rec->session;
	काष्ठा बारpec ref_घड़ीid;
	काष्ठा समयval ref_tod;
	u64 ref;

	अगर (!rec->opts.use_घड़ीid)
		वापस 0;

	अगर (rec->opts.use_घड़ीid && rec->opts.घड़ीid_res_ns)
		session->header.env.घड़ी.घड़ीid_res_ns = rec->opts.घड़ीid_res_ns;

	session->header.env.घड़ी.घड़ीid = rec->opts.घड़ीid;

	अगर (समय_लोofday(&ref_tod, शून्य) != 0) अणु
		pr_err("gettimeofday failed, cannot set reference time.\n");
		वापस -1;
	पूर्ण

	अगर (घड़ी_समय_लो(rec->opts.घड़ीid, &ref_घड़ीid)) अणु
		pr_err("clock_gettime failed, cannot set reference time.\n");
		वापस -1;
	पूर्ण

	ref = (u64) ref_tod.tv_sec * NSEC_PER_SEC +
	      (u64) ref_tod.tv_usec * NSEC_PER_USEC;

	session->header.env.घड़ी.tod_ns = ref;

	ref = (u64) ref_घड़ीid.tv_sec * NSEC_PER_SEC +
	      (u64) ref_घड़ीid.tv_nsec;

	session->header.env.घड़ी.घड़ीid_ns = ref;
	वापस 0;
पूर्ण

अटल व्योम hit_auxtrace_snapshot_trigger(काष्ठा record *rec)
अणु
	अगर (trigger_is_पढ़ोy(&auxtrace_snapshot_trigger)) अणु
		trigger_hit(&auxtrace_snapshot_trigger);
		auxtrace_record__snapshot_started = 1;
		अगर (auxtrace_record__snapshot_start(rec->itr))
			trigger_error(&auxtrace_snapshot_trigger);
	पूर्ण
पूर्ण

अटल व्योम record__uniquअगरy_name(काष्ठा record *rec)
अणु
	काष्ठा evsel *pos;
	काष्ठा evlist *evlist = rec->evlist;
	अक्षर *new_name;
	पूर्णांक ret;

	अगर (!perf_pmu__has_hybrid())
		वापस;

	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (!evsel__is_hybrid(pos))
			जारी;

		अगर (म_अक्षर(pos->name, '/'))
			जारी;

		ret = aप्र_लिखो(&new_name, "%s/%s/",
			       pos->pmu_name, pos->name);
		अगर (ret) अणु
			मुक्त(pos->name);
			pos->name = new_name;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __cmd_record(काष्ठा record *rec, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक err;
	पूर्णांक status = 0;
	अचिन्हित दीर्घ waking = 0;
	स्थिर bool विभाजनs = argc > 0;
	काष्ठा perf_tool *tool = &rec->tool;
	काष्ठा record_opts *opts = &rec->opts;
	काष्ठा perf_data *data = &rec->data;
	काष्ठा perf_session *session;
	bool disabled = false, draining = false;
	पूर्णांक fd;
	भग्न ratio = 0;
	क्रमागत evlist_ctl_cmd cmd = EVLIST_CTL_CMD_UNSUPPORTED;

	निकास_पर(record__sig_निकास);
	संकेत(SIGCHLD, sig_handler);
	संकेत(संक_विघ्न, sig_handler);
	संकेत(संक_इति, sig_handler);
	संकेत(संक_अंश, sigsegv_handler);

	अगर (rec->opts.record_namespaces)
		tool->namespace_events = true;

	अगर (rec->opts.record_cgroup) अणु
#अगर_घोषित HAVE_खाता_HANDLE
		tool->cgroup_events = true;
#अन्यथा
		pr_err("cgroup tracking is not supported\n");
		वापस -1;
#पूर्ण_अगर
	पूर्ण

	अगर (rec->opts.auxtrace_snapshot_mode || rec->चयन_output.enabled) अणु
		संकेत(SIGUSR2, snapshot_sig_handler);
		अगर (rec->opts.auxtrace_snapshot_mode)
			trigger_on(&auxtrace_snapshot_trigger);
		अगर (rec->चयन_output.enabled)
			trigger_on(&चयन_output_trigger);
	पूर्ण अन्यथा अणु
		संकेत(SIGUSR2, संक_छोड़ो);
	पूर्ण

	session = perf_session__new(data, false, tool);
	अगर (IS_ERR(session)) अणु
		pr_err("Perf session creation failed.\n");
		वापस PTR_ERR(session);
	पूर्ण

	fd = perf_data__fd(data);
	rec->session = session;

	अगर (zstd_init(&session->zstd_data, rec->opts.comp_level) < 0) अणु
		pr_err("Compression initialization failed.\n");
		वापस -1;
	पूर्ण
#अगर_घोषित HAVE_EVENTFD_SUPPORT
	करोne_fd = eventfd(0, EFD_NONBLOCK);
	अगर (करोne_fd < 0) अणु
		pr_err("Failed to create wakeup eventfd, error: %m\n");
		status = -1;
		जाओ out_delete_session;
	पूर्ण
	err = evlist__add_wakeup_eventfd(rec->evlist, करोne_fd);
	अगर (err < 0) अणु
		pr_err("Failed to add wakeup eventfd to poll list\n");
		status = err;
		जाओ out_delete_session;
	पूर्ण
#पूर्ण_अगर // HAVE_EVENTFD_SUPPORT

	session->header.env.comp_type  = PERF_COMP_ZSTD;
	session->header.env.comp_level = rec->opts.comp_level;

	अगर (rec->opts.kcore &&
	    !record__kcore_पढ़ोable(&session->machines.host)) अणु
		pr_err("ERROR: kcore is not readable.\n");
		वापस -1;
	पूर्ण

	अगर (record__init_घड़ी(rec))
		वापस -1;

	record__init_features(rec);

	अगर (विभाजनs) अणु
		err = evlist__prepare_workload(rec->evlist, &opts->target, argv, data->is_pipe,
					       workload_exec_failed_संकेत);
		अगर (err < 0) अणु
			pr_err("Couldn't run the workload!\n");
			status = err;
			जाओ out_delete_session;
		पूर्ण
	पूर्ण

	/*
	 * If we have just single event and are sending data
	 * through pipe, we need to क्रमce the ids allocation,
	 * because we synthesize event name through the pipe
	 * and need the id क्रम that.
	 */
	अगर (data->is_pipe && rec->evlist->core.nr_entries == 1)
		rec->opts.sample_id = true;

	record__uniquअगरy_name(rec);

	अगर (record__खोलो(rec) != 0) अणु
		err = -1;
		जाओ out_child;
	पूर्ण
	session->header.env.comp_mmap_len = session->evlist->core.mmap_len;

	अगर (rec->opts.kcore) अणु
		err = record__kcore_copy(&session->machines.host, data);
		अगर (err) अणु
			pr_err("ERROR: Failed to copy kcore\n");
			जाओ out_child;
		पूर्ण
	पूर्ण

	err = bpf__apply_obj_config();
	अगर (err) अणु
		अक्षर errbuf[बफ_मान];

		bpf__म_त्रुटि_apply_obj_config(err, errbuf, माप(errbuf));
		pr_err("ERROR: Apply config to BPF failed: %s\n",
			 errbuf);
		जाओ out_child;
	पूर्ण

	/*
	 * Normally perf_session__new would करो this, but it करोesn't have the
	 * evlist.
	 */
	अगर (rec->tool.ordered_events && !evlist__sample_id_all(rec->evlist)) अणु
		pr_warning("WARNING: No sample_id_all support, falling back to unordered processing\n");
		rec->tool.ordered_events = false;
	पूर्ण

	अगर (!rec->evlist->nr_groups)
		perf_header__clear_feat(&session->header, HEADER_GROUP_DESC);

	अगर (data->is_pipe) अणु
		err = perf_header__ग_लिखो_pipe(fd);
		अगर (err < 0)
			जाओ out_child;
	पूर्ण अन्यथा अणु
		err = perf_session__ग_लिखो_header(session, rec->evlist, fd, false);
		अगर (err < 0)
			जाओ out_child;
	पूर्ण

	err = -1;
	अगर (!rec->no_buildid
	    && !perf_header__has_feat(&session->header, HEADER_BUILD_ID)) अणु
		pr_err("Couldn't generate buildids. "
		       "Use --no-buildid to profile anyway.\n");
		जाओ out_child;
	पूर्ण

	err = record__setup_sb_evlist(rec);
	अगर (err)
		जाओ out_child;

	err = record__synthesize(rec, false);
	अगर (err < 0)
		जाओ out_child;

	अगर (rec->realसमय_prio) अणु
		काष्ठा sched_param param;

		param.sched_priority = rec->realसमय_prio;
		अगर (sched_setscheduler(0, SCHED_FIFO, &param)) अणु
			pr_err("Could not set realtime priority.\n");
			err = -1;
			जाओ out_child;
		पूर्ण
	पूर्ण

	/*
	 * When perf is starting the traced process, all the events
	 * (apart from group members) have enable_on_exec=1 set,
	 * so करोn't spoil it by prematurely enabling them.
	 */
	अगर (!target__none(&opts->target) && !opts->initial_delay)
		evlist__enable(rec->evlist);

	/*
	 * Let the child rip
	 */
	अगर (विभाजनs) अणु
		काष्ठा machine *machine = &session->machines.host;
		जोड़ perf_event *event;
		pid_t tgid;

		event = दो_स्मृति(माप(event->comm) + machine->id_hdr_size);
		अगर (event == शून्य) अणु
			err = -ENOMEM;
			जाओ out_child;
		पूर्ण

		/*
		 * Some H/W events are generated beक्रमe COMM event
		 * which is emitted during exec(), so perf script
		 * cannot see a correct process name क्रम those events.
		 * Synthesize COMM event to prevent it.
		 */
		tgid = perf_event__synthesize_comm(tool, event,
						   rec->evlist->workload.pid,
						   process_synthesized_event,
						   machine);
		मुक्त(event);

		अगर (tgid == -1)
			जाओ out_child;

		event = दो_स्मृति(माप(event->namespaces) +
			       (NR_NAMESPACES * माप(काष्ठा perf_ns_link_info)) +
			       machine->id_hdr_size);
		अगर (event == शून्य) अणु
			err = -ENOMEM;
			जाओ out_child;
		पूर्ण

		/*
		 * Synthesize NAMESPACES event क्रम the command specअगरied.
		 */
		perf_event__synthesize_namespaces(tool, event,
						  rec->evlist->workload.pid,
						  tgid, process_synthesized_event,
						  machine);
		मुक्त(event);

		evlist__start_workload(rec->evlist);
	पूर्ण

	अगर (evlist__initialize_ctlfd(rec->evlist, opts->ctl_fd, opts->ctl_fd_ack))
		जाओ out_child;

	अगर (opts->initial_delay) अणु
		pr_info(EVLIST_DISABLED_MSG);
		अगर (opts->initial_delay > 0) अणु
			usleep(opts->initial_delay * USEC_PER_MSEC);
			evlist__enable(rec->evlist);
			pr_info(EVLIST_ENABLED_MSG);
		पूर्ण
	पूर्ण

	trigger_पढ़ोy(&auxtrace_snapshot_trigger);
	trigger_पढ़ोy(&चयन_output_trigger);
	perf_hooks__invoke_record_start();
	क्रम (;;) अणु
		अचिन्हित दीर्घ दीर्घ hits = rec->samples;

		/*
		 * rec->evlist->bkw_mmap_state is possible to be
		 * BKW_MMAP_EMPTY here: when करोne == true and
		 * hits != rec->samples in previous round.
		 *
		 * evlist__toggle_bkw_mmap ensure we never
		 * convert BKW_MMAP_EMPTY to BKW_MMAP_DATA_PENDING.
		 */
		अगर (trigger_is_hit(&चयन_output_trigger) || करोne || draining)
			evlist__toggle_bkw_mmap(rec->evlist, BKW_MMAP_DATA_PENDING);

		अगर (record__mmap_पढ़ो_all(rec, false) < 0) अणु
			trigger_error(&auxtrace_snapshot_trigger);
			trigger_error(&चयन_output_trigger);
			err = -1;
			जाओ out_child;
		पूर्ण

		अगर (auxtrace_record__snapshot_started) अणु
			auxtrace_record__snapshot_started = 0;
			अगर (!trigger_is_error(&auxtrace_snapshot_trigger))
				record__पढ़ो_auxtrace_snapshot(rec, false);
			अगर (trigger_is_error(&auxtrace_snapshot_trigger)) अणु
				pr_err("AUX area tracing snapshot failed\n");
				err = -1;
				जाओ out_child;
			पूर्ण
		पूर्ण

		अगर (trigger_is_hit(&चयन_output_trigger)) अणु
			/*
			 * If चयन_output_trigger is hit, the data in
			 * overwritable ring buffer should have been collected,
			 * so bkw_mmap_state should be set to BKW_MMAP_EMPTY.
			 *
			 * If SIGUSR2 उठाओ after or during record__mmap_पढ़ो_all(),
			 * record__mmap_पढ़ो_all() didn't collect data from
			 * overwritable ring buffer. Read again.
			 */
			अगर (rec->evlist->bkw_mmap_state == BKW_MMAP_RUNNING)
				जारी;
			trigger_पढ़ोy(&चयन_output_trigger);

			/*
			 * Reenable events in overग_लिखो ring buffer after
			 * record__mmap_पढ़ो_all(): we should have collected
			 * data from it.
			 */
			evlist__toggle_bkw_mmap(rec->evlist, BKW_MMAP_RUNNING);

			अगर (!quiet)
				ख_लिखो(मानक_त्रुटि, "[ perf record: dump data: Woken up %ld times ]\n",
					waking);
			waking = 0;
			fd = record__चयन_output(rec, false);
			अगर (fd < 0) अणु
				pr_err("Failed to switch to new file\n");
				trigger_error(&चयन_output_trigger);
				err = fd;
				जाओ out_child;
			पूर्ण

			/* re-arm the alarm */
			अगर (rec->चयन_output.समय)
				alarm(rec->चयन_output.समय);
		पूर्ण

		अगर (hits == rec->samples) अणु
			अगर (करोne || draining)
				अवरोध;
			err = evlist__poll(rec->evlist, -1);
			/*
			 * Propagate error, only अगर there's any. Ignore positive
			 * number of वापसed events and पूर्णांकerrupt error.
			 */
			अगर (err > 0 || (err < 0 && त्रुटि_सं == EINTR))
				err = 0;
			waking++;

			अगर (evlist__filter_pollfd(rec->evlist, POLLERR | POLLHUP) == 0)
				draining = true;
		पूर्ण

		अगर (evlist__ctlfd_process(rec->evlist, &cmd) > 0) अणु
			चयन (cmd) अणु
			हाल EVLIST_CTL_CMD_SNAPSHOT:
				hit_auxtrace_snapshot_trigger(rec);
				evlist__ctlfd_ack(rec->evlist);
				अवरोध;
			हाल EVLIST_CTL_CMD_STOP:
				करोne = 1;
				अवरोध;
			हाल EVLIST_CTL_CMD_ACK:
			हाल EVLIST_CTL_CMD_UNSUPPORTED:
			हाल EVLIST_CTL_CMD_ENABLE:
			हाल EVLIST_CTL_CMD_DISABLE:
			हाल EVLIST_CTL_CMD_EVLIST:
			हाल EVLIST_CTL_CMD_PING:
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * When perf is starting the traced process, at the end events
		 * die with the process and we रुको क्रम that. Thus no need to
		 * disable events in this हाल.
		 */
		अगर (करोne && !disabled && !target__none(&opts->target)) अणु
			trigger_off(&auxtrace_snapshot_trigger);
			evlist__disable(rec->evlist);
			disabled = true;
		पूर्ण
	पूर्ण

	trigger_off(&auxtrace_snapshot_trigger);
	trigger_off(&चयन_output_trigger);

	अगर (opts->auxtrace_snapshot_on_निकास)
		record__auxtrace_snapshot_निकास(rec);

	अगर (विभाजनs && workload_exec_त्रुटि_सं) अणु
		अक्षर msg[STRERR_बफ_मानE], strevsels[2048];
		स्थिर अक्षर *emsg = str_error_r(workload_exec_त्रुटि_सं, msg, माप(msg));

		evlist__scnम_लिखो_evsels(rec->evlist, माप(strevsels), strevsels);

		pr_err("Failed to collect '%s' for the '%s' workload: %s\n",
			strevsels, argv[0], emsg);
		err = -1;
		जाओ out_child;
	पूर्ण

	अगर (!quiet)
		ख_लिखो(मानक_त्रुटि, "[ perf record: Woken up %ld times to write data ]\n", waking);

	अगर (target__none(&rec->opts.target))
		record__synthesize_workload(rec, true);

out_child:
	evlist__finalize_ctlfd(rec->evlist);
	record__mmap_पढ़ो_all(rec, true);
	record__aio_mmap_पढ़ो_sync(rec);

	अगर (rec->session->bytes_transferred && rec->session->bytes_compressed) अणु
		ratio = (भग्न)rec->session->bytes_transferred/(भग्न)rec->session->bytes_compressed;
		session->header.env.comp_ratio = ratio + 0.5;
	पूर्ण

	अगर (विभाजनs) अणु
		पूर्णांक निकास_status;

		अगर (!child_finished)
			समाप्त(rec->evlist->workload.pid, संक_इति);

		रुको(&निकास_status);

		अगर (err < 0)
			status = err;
		अन्यथा अगर (WIFEXITED(निकास_status))
			status = WEXITSTATUS(निकास_status);
		अन्यथा अगर (WIFSIGNALED(निकास_status))
			signr = WTERMSIG(निकास_status);
	पूर्ण अन्यथा
		status = err;

	record__synthesize(rec, true);
	/* this will be recalculated during process_buildids() */
	rec->samples = 0;

	अगर (!err) अणु
		अगर (!rec->बारtamp_filename) अणु
			record__finish_output(rec);
		पूर्ण अन्यथा अणु
			fd = record__चयन_output(rec, true);
			अगर (fd < 0) अणु
				status = fd;
				जाओ out_delete_session;
			पूर्ण
		पूर्ण
	पूर्ण

	perf_hooks__invoke_record_end();

	अगर (!err && !quiet) अणु
		अक्षर samples[128];
		स्थिर अक्षर *postfix = rec->बारtamp_filename ?
					".<timestamp>" : "";

		अगर (rec->samples && !rec->opts.full_auxtrace)
			scnम_लिखो(samples, माप(samples),
				  " (%" PRIu64 " samples)", rec->samples);
		अन्यथा
			samples[0] = '\0';

		ख_लिखो(मानक_त्रुटि,	"[ perf record: Captured and wrote %.3f MB %s%s%s",
			perf_data__size(data) / 1024.0 / 1024.0,
			data->path, postfix, samples);
		अगर (ratio) अणु
			ख_लिखो(मानक_त्रुटि,	", compressed (original %.3f MB, ratio is %.3f)",
					rec->session->bytes_transferred / 1024.0 / 1024.0,
					ratio);
		पूर्ण
		ख_लिखो(मानक_त्रुटि, " ]\n");
	पूर्ण

out_delete_session:
#अगर_घोषित HAVE_EVENTFD_SUPPORT
	अगर (करोne_fd >= 0)
		बंद(करोne_fd);
#पूर्ण_अगर
	zstd_fini(&session->zstd_data);
	perf_session__delete(session);

	अगर (!opts->no_bpf_event)
		evlist__stop_sb_thपढ़ो(rec->sb_evlist);
	वापस status;
पूर्ण

अटल व्योम callchain_debug(काष्ठा callchain_param *callchain)
अणु
	अटल स्थिर अक्षर *str[CALLCHAIN_MAX] = अणु "NONE", "FP", "DWARF", "LBR" पूर्ण;

	pr_debug("callchain: type %s\n", str[callchain->record_mode]);

	अगर (callchain->record_mode == CALLCHAIN_DWARF)
		pr_debug("callchain: stack dump size %d\n",
			 callchain->dump_size);
पूर्ण

पूर्णांक record_opts__parse_callchain(काष्ठा record_opts *record,
				 काष्ठा callchain_param *callchain,
				 स्थिर अक्षर *arg, bool unset)
अणु
	पूर्णांक ret;
	callchain->enabled = !unset;

	/* --no-call-graph */
	अगर (unset) अणु
		callchain->record_mode = CALLCHAIN_NONE;
		pr_debug("callchain: disabled\n");
		वापस 0;
	पूर्ण

	ret = parse_callchain_record_opt(arg, callchain);
	अगर (!ret) अणु
		/* Enable data address sampling क्रम DWARF unwind. */
		अगर (callchain->record_mode == CALLCHAIN_DWARF)
			record->sample_address = true;
		callchain_debug(callchain);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक record_parse_callchain_opt(स्थिर काष्ठा option *opt,
			       स्थिर अक्षर *arg,
			       पूर्णांक unset)
अणु
	वापस record_opts__parse_callchain(opt->value, &callchain_param, arg, unset);
पूर्ण

पूर्णांक record_callchain_opt(स्थिर काष्ठा option *opt,
			 स्थिर अक्षर *arg __maybe_unused,
			 पूर्णांक unset __maybe_unused)
अणु
	काष्ठा callchain_param *callchain = opt->value;

	callchain->enabled = true;

	अगर (callchain->record_mode == CALLCHAIN_NONE)
		callchain->record_mode = CALLCHAIN_FP;

	callchain_debug(callchain);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_record_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	काष्ठा record *rec = cb;

	अगर (!म_भेद(var, "record.build-id")) अणु
		अगर (!म_भेद(value, "cache"))
			rec->no_buildid_cache = false;
		अन्यथा अगर (!म_भेद(value, "no-cache"))
			rec->no_buildid_cache = true;
		अन्यथा अगर (!म_भेद(value, "skip"))
			rec->no_buildid = true;
		अन्यथा अगर (!म_भेद(value, "mmap"))
			rec->buildid_mmap = true;
		अन्यथा
			वापस -1;
		वापस 0;
	पूर्ण
	अगर (!म_भेद(var, "record.call-graph")) अणु
		var = "call-graph.record-mode";
		वापस perf_शेष_config(var, value, cb);
	पूर्ण
#अगर_घोषित HAVE_AIO_SUPPORT
	अगर (!म_भेद(var, "record.aio")) अणु
		rec->opts.nr_cblocks = म_से_दीर्घ(value, शून्य, 0);
		अगर (!rec->opts.nr_cblocks)
			rec->opts.nr_cblocks = nr_cblocks_शेष;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण


अटल पूर्णांक record__parse_affinity(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	काष्ठा record_opts *opts = (काष्ठा record_opts *)opt->value;

	अगर (unset || !str)
		वापस 0;

	अगर (!strहालcmp(str, "node"))
		opts->affinity = PERF_AFFINITY_NODE;
	अन्यथा अगर (!strहालcmp(str, "cpu"))
		opts->affinity = PERF_AFFINITY_CPU;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_output_max_size(स्थिर काष्ठा option *opt,
				 स्थिर अक्षर *str, पूर्णांक unset)
अणु
	अचिन्हित दीर्घ *s = (अचिन्हित दीर्घ *)opt->value;
	अटल काष्ठा parse_tag tags_size[] = अणु
		अणु .tag  = 'B', .mult = 1       पूर्ण,
		अणु .tag  = 'K', .mult = 1 << 10 पूर्ण,
		अणु .tag  = 'M', .mult = 1 << 20 पूर्ण,
		अणु .tag  = 'G', .mult = 1 << 30 पूर्ण,
		अणु .tag  = 0 पूर्ण,
	पूर्ण;
	अचिन्हित दीर्घ val;

	अगर (unset) अणु
		*s = 0;
		वापस 0;
	पूर्ण

	val = parse_tag_value(str, tags_size);
	अगर (val != (अचिन्हित दीर्घ) -1) अणु
		*s = val;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक record__parse_mmap_pages(स्थिर काष्ठा option *opt,
				    स्थिर अक्षर *str,
				    पूर्णांक unset __maybe_unused)
अणु
	काष्ठा record_opts *opts = opt->value;
	अक्षर *s, *p;
	अचिन्हित पूर्णांक mmap_pages;
	पूर्णांक ret;

	अगर (!str)
		वापस -EINVAL;

	s = strdup(str);
	अगर (!s)
		वापस -ENOMEM;

	p = म_अक्षर(s, ',');
	अगर (p)
		*p = '\0';

	अगर (*s) अणु
		ret = __evlist__parse_mmap_pages(&mmap_pages, s);
		अगर (ret)
			जाओ out_मुक्त;
		opts->mmap_pages = mmap_pages;
	पूर्ण

	अगर (!p) अणु
		ret = 0;
		जाओ out_मुक्त;
	पूर्ण

	ret = __evlist__parse_mmap_pages(&mmap_pages, p + 1);
	अगर (ret)
		जाओ out_मुक्त;

	opts->auxtrace_mmap_pages = mmap_pages;

out_मुक्त:
	मुक्त(s);
	वापस ret;
पूर्ण

अटल पूर्णांक parse_control_option(स्थिर काष्ठा option *opt,
				स्थिर अक्षर *str,
				पूर्णांक unset __maybe_unused)
अणु
	काष्ठा record_opts *opts = opt->value;

	वापस evlist__parse_control(str, &opts->ctl_fd, &opts->ctl_fd_ack, &opts->ctl_fd_बंद);
पूर्ण

अटल व्योम चयन_output_size_warn(काष्ठा record *rec)
अणु
	u64 wakeup_size = evlist__mmap_size(rec->opts.mmap_pages);
	काष्ठा चयन_output *s = &rec->चयन_output;

	wakeup_size /= 2;

	अगर (s->size < wakeup_size) अणु
		अक्षर buf[100];

		unit_number__scnम_लिखो(buf, माप(buf), wakeup_size);
		pr_warning("WARNING: switch-output data size lower than "
			   "wakeup kernel buffer size (%s) "
			   "expect bigger perf.data sizes\n", buf);
	पूर्ण
पूर्ण

अटल पूर्णांक चयन_output_setup(काष्ठा record *rec)
अणु
	काष्ठा चयन_output *s = &rec->चयन_output;
	अटल काष्ठा parse_tag tags_size[] = अणु
		अणु .tag  = 'B', .mult = 1       पूर्ण,
		अणु .tag  = 'K', .mult = 1 << 10 पूर्ण,
		अणु .tag  = 'M', .mult = 1 << 20 पूर्ण,
		अणु .tag  = 'G', .mult = 1 << 30 पूर्ण,
		अणु .tag  = 0 पूर्ण,
	पूर्ण;
	अटल काष्ठा parse_tag tags_समय[] = अणु
		अणु .tag  = 's', .mult = 1        पूर्ण,
		अणु .tag  = 'm', .mult = 60       पूर्ण,
		अणु .tag  = 'h', .mult = 60*60    पूर्ण,
		अणु .tag  = 'd', .mult = 60*60*24 पूर्ण,
		अणु .tag  = 0 पूर्ण,
	पूर्ण;
	अचिन्हित दीर्घ val;

	/*
	 * If we're using --चयन-output-events, then we imply its 
	 * --चयन-output=संकेत, as we'll send a SIGUSR2 from the side band
	 *  thपढ़ो to its parent.
	 */
	अगर (rec->चयन_output_event_set)
		जाओ करो_संकेत;

	अगर (!s->set)
		वापस 0;

	अगर (!म_भेद(s->str, "signal")) अणु
करो_संकेत:
		s->संकेत = true;
		pr_debug("switch-output with SIGUSR2 signal\n");
		जाओ enabled;
	पूर्ण

	val = parse_tag_value(s->str, tags_size);
	अगर (val != (अचिन्हित दीर्घ) -1) अणु
		s->size = val;
		pr_debug("switch-output with %s size threshold\n", s->str);
		जाओ enabled;
	पूर्ण

	val = parse_tag_value(s->str, tags_समय);
	अगर (val != (अचिन्हित दीर्घ) -1) अणु
		s->समय = val;
		pr_debug("switch-output with %s time threshold (%lu seconds)\n",
			 s->str, s->समय);
		जाओ enabled;
	पूर्ण

	वापस -1;

enabled:
	rec->बारtamp_filename = true;
	s->enabled              = true;

	अगर (s->size && !rec->opts.no_buffering)
		चयन_output_size_warn(rec);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर __record_usage[] = अणु
	"perf record [<options>] [<command>]",
	"perf record [<options>] -- <command> [<options>]",
	शून्य
पूर्ण;
स्थिर अक्षर * स्थिर *record_usage = __record_usage;

अटल पूर्णांक build_id__process_mmap(काष्ठा perf_tool *tool, जोड़ perf_event *event,
				  काष्ठा perf_sample *sample, काष्ठा machine *machine)
अणु
	/*
	 * We alपढ़ोy have the kernel maps, put in place via perf_session__create_kernel_maps()
	 * no need to add them twice.
	 */
	अगर (!(event->header.misc & PERF_RECORD_MISC_USER))
		वापस 0;
	वापस perf_event__process_mmap(tool, event, sample, machine);
पूर्ण

अटल पूर्णांक build_id__process_mmap2(काष्ठा perf_tool *tool, जोड़ perf_event *event,
				   काष्ठा perf_sample *sample, काष्ठा machine *machine)
अणु
	/*
	 * We alपढ़ोy have the kernel maps, put in place via perf_session__create_kernel_maps()
	 * no need to add them twice.
	 */
	अगर (!(event->header.misc & PERF_RECORD_MISC_USER))
		वापस 0;

	वापस perf_event__process_mmap2(tool, event, sample, machine);
पूर्ण

/*
 * XXX Ideally would be local to cmd_record() and passed to a record__new
 * because we need to have access to it in record__निकास, that is called
 * after cmd_record() निकासs, but since record_options need to be accessible to
 * builtin-script, leave it here.
 *
 * At least we करोn't ouch it in all the other functions here directly.
 *
 * Just say no to tons of global variables, sigh.
 */
अटल काष्ठा record record = अणु
	.opts = अणु
		.sample_समय	     = true,
		.mmap_pages	     = अच_पूर्णांक_उच्च,
		.user_freq	     = अच_पूर्णांक_उच्च,
		.user_पूर्णांकerval	     = ULदीर्घ_उच्च,
		.freq		     = 4000,
		.target		     = अणु
			.uses_mmap   = true,
			.शेष_per_cpu = true,
		पूर्ण,
		.mmap_flush          = MMAP_FLUSH_DEFAULT,
		.nr_thपढ़ोs_synthesize = 1,
		.ctl_fd              = -1,
		.ctl_fd_ack          = -1,
	पूर्ण,
	.tool = अणु
		.sample		= process_sample_event,
		.विभाजन		= perf_event__process_विभाजन,
		.निकास		= perf_event__process_निकास,
		.comm		= perf_event__process_comm,
		.namespaces	= perf_event__process_namespaces,
		.mmap		= build_id__process_mmap,
		.mmap2		= build_id__process_mmap2,
		.ordered_events	= true,
	पूर्ण,
पूर्ण;

स्थिर अक्षर record_callchain_help[] = CALLCHAIN_RECORD_HELP
	"\n\t\t\t\tDefault: fp";

अटल bool dry_run;

/*
 * XXX Will stay a global variable till we fix builtin-script.c to stop messing
 * with it and चयन to use the library functions in perf_evlist that came
 * from builtin-record.c, i.e. use record_opts,
 * evlist__prepare_workload, etc instead of विभाजन+exec'in 'perf record',
 * using pipes, etc.
 */
अटल काष्ठा option __record_options[] = अणु
	OPT_CALLBACK('e', "event", &record.evlist, "event",
		     "event selector. use 'perf list' to list available events",
		     parse_events_option),
	OPT_CALLBACK(0, "filter", &record.evlist, "filter",
		     "event filter", parse_filter),
	OPT_CALLBACK_NOOPT(0, "exclude-perf", &record.evlist,
			   शून्य, "don't record events from perf itself",
			   exclude_perf),
	OPT_STRING('p', "pid", &record.opts.target.pid, "pid",
		    "record events on existing process id"),
	OPT_STRING('t', "tid", &record.opts.target.tid, "tid",
		    "record events on existing thread id"),
	OPT_INTEGER('r', "realtime", &record.realसमय_prio,
		    "collect data with this RT SCHED_FIFO priority"),
	OPT_BOOLEAN(0, "no-buffering", &record.opts.no_buffering,
		    "collect data without buffering"),
	OPT_BOOLEAN('R', "raw-samples", &record.opts.raw_samples,
		    "collect raw sample records from all opened counters"),
	OPT_BOOLEAN('a', "all-cpus", &record.opts.target.प्रणाली_wide,
			    "system-wide collection from all CPUs"),
	OPT_STRING('C', "cpu", &record.opts.target.cpu_list, "cpu",
		    "list of cpus to monitor"),
	OPT_U64('c', "count", &record.opts.user_पूर्णांकerval, "event period to sample"),
	OPT_STRING('o', "output", &record.data.path, "file",
		    "output file name"),
	OPT_BOOLEAN_SET('i', "no-inherit", &record.opts.no_inherit,
			&record.opts.no_inherit_set,
			"child tasks do not inherit counters"),
	OPT_BOOLEAN(0, "tail-synthesize", &record.opts.tail_synthesize,
		    "synthesize non-sample events at the end of output"),
	OPT_BOOLEAN(0, "overwrite", &record.opts.overग_लिखो, "use overwrite mode"),
	OPT_BOOLEAN(0, "no-bpf-event", &record.opts.no_bpf_event, "do not record bpf events"),
	OPT_BOOLEAN(0, "strict-freq", &record.opts.strict_freq,
		    "Fail if the specified frequency can't be used"),
	OPT_CALLBACK('F', "freq", &record.opts, "freq or 'max'",
		     "profile at this frequency",
		      record__parse_freq),
	OPT_CALLBACK('m', "mmap-pages", &record.opts, "pages[,pages]",
		     "number of mmap data pages and AUX area tracing mmap pages",
		     record__parse_mmap_pages),
	OPT_CALLBACK(0, "mmap-flush", &record.opts, "number",
		     "Minimal number of bytes that is extracted from mmap data pages (default: 1)",
		     record__mmap_flush_parse),
	OPT_BOOLEAN(0, "group", &record.opts.group,
		    "put the counters into a counter group"),
	OPT_CALLBACK_NOOPT('g', शून्य, &callchain_param,
			   शून्य, "enables call-graph recording" ,
			   &record_callchain_opt),
	OPT_CALLBACK(0, "call-graph", &record.opts,
		     "record_mode[,record_size]", record_callchain_help,
		     &record_parse_callchain_opt),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show counter open errors, etc)"),
	OPT_BOOLEAN('q', "quiet", &quiet, "don't prपूर्णांक any message"),
	OPT_BOOLEAN('s', "stat", &record.opts.inherit_stat,
		    "per thread counts"),
	OPT_BOOLEAN('d', "data", &record.opts.sample_address, "Record the sample addresses"),
	OPT_BOOLEAN(0, "phys-data", &record.opts.sample_phys_addr,
		    "Record the sample physical addresses"),
	OPT_BOOLEAN(0, "data-page-size", &record.opts.sample_data_page_size,
		    "Record the sampled data address data page size"),
	OPT_BOOLEAN(0, "code-page-size", &record.opts.sample_code_page_size,
		    "Record the sampled code address (ip) page size"),
	OPT_BOOLEAN(0, "sample-cpu", &record.opts.sample_cpu, "Record the sample cpu"),
	OPT_BOOLEAN_SET('T', "timestamp", &record.opts.sample_समय,
			&record.opts.sample_समय_set,
			"Record the sample timestamps"),
	OPT_BOOLEAN_SET('P', "period", &record.opts.period, &record.opts.period_set,
			"Record the sample period"),
	OPT_BOOLEAN('n', "no-samples", &record.opts.no_samples,
		    "don't sample"),
	OPT_BOOLEAN_SET('N', "no-buildid-cache", &record.no_buildid_cache,
			&record.no_buildid_cache_set,
			"do not update the buildid cache"),
	OPT_BOOLEAN_SET('B', "no-buildid", &record.no_buildid,
			&record.no_buildid_set,
			"do not collect buildids in perf.data"),
	OPT_CALLBACK('G', "cgroup", &record.evlist, "name",
		     "monitor event in cgroup name only",
		     parse_cgroups),
	OPT_INTEGER('D', "delay", &record.opts.initial_delay,
		  "ms to wait before starting measurement after program start (-1: start with events disabled)"),
	OPT_BOOLEAN(0, "kcore", &record.opts.kcore, "copy /proc/kcore"),
	OPT_STRING('u', "uid", &record.opts.target.uid_str, "user",
		   "user to profile"),

	OPT_CALLBACK_NOOPT('b', "branch-any", &record.opts.branch_stack,
		     "branch any", "sample any taken branches",
		     parse_branch_stack),

	OPT_CALLBACK('j', "branch-filter", &record.opts.branch_stack,
		     "branch filter mask", "branch stack filter modes",
		     parse_branch_stack),
	OPT_BOOLEAN('W', "weight", &record.opts.sample_weight,
		    "sample by weight (on special events only)"),
	OPT_BOOLEAN(0, "transaction", &record.opts.sample_transaction,
		    "sample transaction flags (special events only)"),
	OPT_BOOLEAN(0, "per-thread", &record.opts.target.per_thपढ़ो,
		    "use per-thread mmaps"),
	OPT_CALLBACK_OPTARG('I', "intr-regs", &record.opts.sample_पूर्णांकr_regs, शून्य, "any register",
		    "sample selected machine registers on interrupt,"
		    " use '-I?' to list register names", parse_पूर्णांकr_regs),
	OPT_CALLBACK_OPTARG(0, "user-regs", &record.opts.sample_user_regs, शून्य, "any register",
		    "sample selected machine registers on interrupt,"
		    " use '--user-regs=?' to list register names", parse_user_regs),
	OPT_BOOLEAN(0, "running-time", &record.opts.running_समय,
		    "Record running/enabled time of read (:S) events"),
	OPT_CALLBACK('k', "clockid", &record.opts,
	"clockid", "clockid to use for events, see clock_gettime()",
	parse_घड़ीid),
	OPT_STRING_OPTARG('S', "snapshot", &record.opts.auxtrace_snapshot_opts,
			  "opts", "AUX area tracing Snapshot Mode", ""),
	OPT_STRING_OPTARG(0, "aux-sample", &record.opts.auxtrace_sample_opts,
			  "opts", "sample AUX area", ""),
	OPT_UINTEGER(0, "proc-map-timeout", &proc_map_समयout,
			"per thread proc mmap processing timeout in ms"),
	OPT_BOOLEAN(0, "namespaces", &record.opts.record_namespaces,
		    "Record namespaces events"),
	OPT_BOOLEAN(0, "all-cgroups", &record.opts.record_cgroup,
		    "Record cgroup events"),
	OPT_BOOLEAN_SET(0, "switch-events", &record.opts.record_चयन_events,
			&record.opts.record_चयन_events_set,
			"Record context switch events"),
	OPT_BOOLEAN_FLAG(0, "all-kernel", &record.opts.all_kernel,
			 "Configure all used events to run in kernel space.",
			 PARSE_OPT_EXCLUSIVE),
	OPT_BOOLEAN_FLAG(0, "all-user", &record.opts.all_user,
			 "Configure all used events to run in user space.",
			 PARSE_OPT_EXCLUSIVE),
	OPT_BOOLEAN(0, "kernel-callchains", &record.opts.kernel_callchains,
		    "collect kernel callchains"),
	OPT_BOOLEAN(0, "user-callchains", &record.opts.user_callchains,
		    "collect user callchains"),
	OPT_STRING(0, "clang-path", &llvm_param.clang_path, "clang path",
		   "clang binary to use for compiling BPF scriptlets"),
	OPT_STRING(0, "clang-opt", &llvm_param.clang_opt, "clang options",
		   "options passed to clang when compiling BPF scriptlets"),
	OPT_STRING(0, "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_BOOLEAN(0, "buildid-all", &record.buildid_all,
		    "Record build-id of all DSOs regardless of hits"),
	OPT_BOOLEAN(0, "buildid-mmap", &record.buildid_mmap,
		    "Record build-id in map events"),
	OPT_BOOLEAN(0, "timestamp-filename", &record.बारtamp_filename,
		    "append timestamp to output filename"),
	OPT_BOOLEAN(0, "timestamp-boundary", &record.बारtamp_boundary,
		    "Record timestamp boundary (time of first/last samples)"),
	OPT_STRING_OPTARG_SET(0, "switch-output", &record.चयन_output.str,
			  &record.चयन_output.set, "signal or size[BKMG] or time[smhd]",
			  "Switch output when receiving SIGUSR2 (signal) or cross a size or time threshold",
			  "signal"),
	OPT_CALLBACK_SET(0, "switch-output-event", &record.sb_evlist, &record.चयन_output_event_set, "switch output event",
			 "switch output event selector. use 'perf list' to list available events",
			 parse_events_option_new_evlist),
	OPT_INTEGER(0, "switch-max-files", &record.चयन_output.num_files,
		   "Limit number of switch output generated files"),
	OPT_BOOLEAN(0, "dry-run", &dry_run,
		    "Parse options then exit"),
#अगर_घोषित HAVE_AIO_SUPPORT
	OPT_CALLBACK_OPTARG(0, "aio", &record.opts,
		     &nr_cblocks_शेष, "n", "Use <n> control blocks in asynchronous trace writing mode (default: 1, max: 4)",
		     record__aio_parse),
#पूर्ण_अगर
	OPT_CALLBACK(0, "affinity", &record.opts, "node|cpu",
		     "Set affinity mask of trace reading thread to NUMA node cpu mask or cpu of processed mmap buffer",
		     record__parse_affinity),
#अगर_घोषित HAVE_ZSTD_SUPPORT
	OPT_CALLBACK_OPTARG('z', "compression-level", &record.opts, &comp_level_शेष,
			    "n", "Compressed records using specified level (default: 1 - fastest compression, 22 - greatest compression)",
			    record__parse_comp_level),
#पूर्ण_अगर
	OPT_CALLBACK(0, "max-size", &record.output_max_size,
		     "size", "Limit the maximum size of the output file", parse_output_max_size),
	OPT_UINTEGER(0, "num-thread-synthesize",
		     &record.opts.nr_thपढ़ोs_synthesize,
		     "number of threads to run for event synthesis"),
#अगर_घोषित HAVE_LIBPFM
	OPT_CALLBACK(0, "pfm-events", &record.evlist, "event",
		"libpfm4 event selector. use 'perf list' to list available events",
		parse_libpfm_events_option),
#पूर्ण_अगर
	OPT_CALLBACK(0, "control", &record.opts, "fd:ctl-fd[,ack-fd] or fifo:ctl-fifo[,ack-fifo]",
		     "Listen on ctl-fd descriptor for command to control measurement ('enable': enable events, 'disable': disable events,\n"
		     "\t\t\t  'snapshot': AUX area tracing snapshot).\n"
		     "\t\t\t  Optionally send control command completion ('ack\\n') to ack-fd descriptor.\n"
		     "\t\t\t  Alternatively, ctl-fifo / ack-fifo will be opened and used as ctl-fd / ack-fd.",
		      parse_control_option),
	OPT_END()
पूर्ण;

काष्ठा option *record_options = __record_options;

पूर्णांक cmd_record(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक err;
	काष्ठा record *rec = &record;
	अक्षर errbuf[बफ_मान];

	रखो_क्षेत्र(LC_ALL, "");

#अगर_अघोषित HAVE_LIBBPF_SUPPORT
# define set_nobuild(s, l, c) set_option_nobuild(record_options, s, l, "NO_LIBBPF=1", c)
	set_nobuild('\0', "clang-path", true);
	set_nobuild('\0', "clang-opt", true);
# undef set_nobuild
#पूर्ण_अगर

#अगर_अघोषित HAVE_BPF_PROLOGUE
# अगर !defined (HAVE_DWARF_SUPPORT)
#  define REASON  "NO_DWARF=1"
# elअगर !defined (HAVE_LIBBPF_SUPPORT)
#  define REASON  "NO_LIBBPF=1"
# अन्यथा
#  define REASON  "this architecture doesn't support BPF prologue"
# endअगर
# define set_nobuild(s, l, c) set_option_nobuild(record_options, s, l, REASON, c)
	set_nobuild('\0', "vmlinux", true);
# undef set_nobuild
# undef REASON
#पूर्ण_अगर

	rec->opts.affinity = PERF_AFFINITY_SYS;

	rec->evlist = evlist__new();
	अगर (rec->evlist == शून्य)
		वापस -ENOMEM;

	err = perf_config(perf_record_config, rec);
	अगर (err)
		वापस err;

	argc = parse_options(argc, argv, record_options, record_usage,
			    PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (quiet)
		perf_quiet_option();

	/* Make प्रणाली wide (-a) the शेष target. */
	अगर (!argc && target__none(&rec->opts.target))
		rec->opts.target.प्रणाली_wide = true;

	अगर (nr_cgroups && !rec->opts.target.प्रणाली_wide) अणु
		usage_with_options_msg(record_usage, record_options,
			"cgroup monitoring only available in system-wide mode");

	पूर्ण

	अगर (rec->buildid_mmap) अणु
		अगर (!perf_can_record_build_id()) अणु
			pr_err("Failed: no support to record build id in mmap events, update your kernel.\n");
			err = -EINVAL;
			जाओ out_opts;
		पूर्ण
		pr_debug("Enabling build id in mmap2 events.\n");
		/* Enable mmap build id synthesizing. */
		symbol_conf.buildid_mmap2 = true;
		/* Enable perf_event_attr::build_id bit. */
		rec->opts.build_id = true;
		/* Disable build id cache. */
		rec->no_buildid = true;
	पूर्ण

	अगर (rec->opts.record_cgroup && !perf_can_record_cgroup()) अणु
		pr_err("Kernel has no cgroup sampling support.\n");
		err = -EINVAL;
		जाओ out_opts;
	पूर्ण

	अगर (rec->opts.kcore)
		rec->data.is_dir = true;

	अगर (rec->opts.comp_level != 0) अणु
		pr_debug("Compression enabled, disabling build id collection at the end of the session.\n");
		rec->no_buildid = true;
	पूर्ण

	अगर (rec->opts.record_चयन_events &&
	    !perf_can_record_चयन_events()) अणु
		ui__error("kernel does not support recording context switch events\n");
		parse_options_usage(record_usage, record_options, "switch-events", 0);
		err = -EINVAL;
		जाओ out_opts;
	पूर्ण

	अगर (चयन_output_setup(rec)) अणु
		parse_options_usage(record_usage, record_options, "switch-output", 0);
		err = -EINVAL;
		जाओ out_opts;
	पूर्ण

	अगर (rec->चयन_output.समय) अणु
		संकेत(SIGALRM, alarm_sig_handler);
		alarm(rec->चयन_output.समय);
	पूर्ण

	अगर (rec->चयन_output.num_files) अणु
		rec->चयन_output.filenames = सुस्मृति(माप(अक्षर *),
						      rec->चयन_output.num_files);
		अगर (!rec->चयन_output.filenames) अणु
			err = -EINVAL;
			जाओ out_opts;
		पूर्ण
	पूर्ण

	/*
	 * Allow aliases to facilitate the lookup of symbols क्रम address
	 * filters. Refer to auxtrace_parse_filters().
	 */
	symbol_conf.allow_aliases = true;

	symbol__init(शून्य);

	अगर (rec->opts.affinity != PERF_AFFINITY_SYS) अणु
		rec->affinity_mask.nbits = cpu__max_cpu();
		rec->affinity_mask.bits = biपंचांगap_alloc(rec->affinity_mask.nbits);
		अगर (!rec->affinity_mask.bits) अणु
			pr_err("Failed to allocate thread mask for %zd cpus\n", rec->affinity_mask.nbits);
			err = -ENOMEM;
			जाओ out_opts;
		पूर्ण
		pr_debug2("thread mask[%zd]: empty\n", rec->affinity_mask.nbits);
	पूर्ण

	err = record__auxtrace_init(rec);
	अगर (err)
		जाओ out;

	अगर (dry_run)
		जाओ out;

	err = bpf__setup_मानक_निकास(rec->evlist);
	अगर (err) अणु
		bpf__म_त्रुटि_setup_मानक_निकास(rec->evlist, err, errbuf, माप(errbuf));
		pr_err("ERROR: Setup BPF stdout failed: %s\n",
			 errbuf);
		जाओ out;
	पूर्ण

	err = -ENOMEM;

	अगर (rec->no_buildid_cache || rec->no_buildid) अणु
		disable_buildid_cache();
	पूर्ण अन्यथा अगर (rec->चयन_output.enabled) अणु
		/*
		 * In 'perf record --switch-output', disable buildid
		 * generation by शेष to reduce data file चयनing
		 * overhead. Still generate buildid अगर they are required
		 * explicitly using
		 *
		 *  perf record --चयन-output --no-no-buildid \
		 *              --no-no-buildid-cache
		 *
		 * Following code equals to:
		 *
		 * अगर ((rec->no_buildid || !rec->no_buildid_set) &&
		 *     (rec->no_buildid_cache || !rec->no_buildid_cache_set))
		 *         disable_buildid_cache();
		 */
		bool disable = true;

		अगर (rec->no_buildid_set && !rec->no_buildid)
			disable = false;
		अगर (rec->no_buildid_cache_set && !rec->no_buildid_cache)
			disable = false;
		अगर (disable) अणु
			rec->no_buildid = true;
			rec->no_buildid_cache = true;
			disable_buildid_cache();
		पूर्ण
	पूर्ण

	अगर (record.opts.overग_लिखो)
		record.opts.tail_synthesize = true;

	अगर (rec->evlist->core.nr_entries == 0) अणु
		अगर (perf_pmu__has_hybrid()) अणु
			err = evlist__add_शेष_hybrid(rec->evlist,
							 !record.opts.no_samples);
		पूर्ण अन्यथा अणु
			err = __evlist__add_शेष(rec->evlist,
						    !record.opts.no_samples);
		पूर्ण

		अगर (err < 0) अणु
			pr_err("Not enough memory for event selector list\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rec->opts.target.tid && !rec->opts.no_inherit_set)
		rec->opts.no_inherit = true;

	err = target__validate(&rec->opts.target);
	अगर (err) अणु
		target__म_त्रुटि(&rec->opts.target, err, errbuf, बफ_मान);
		ui__warning("%s\n", errbuf);
	पूर्ण

	err = target__parse_uid(&rec->opts.target);
	अगर (err) अणु
		पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;

		target__म_त्रुटि(&rec->opts.target, err, errbuf, बफ_मान);
		ui__error("%s", errbuf);

		err = -saved_त्रुटि_सं;
		जाओ out;
	पूर्ण

	/* Enable ignoring missing thपढ़ोs when -u/-p option is defined. */
	rec->opts.ignore_missing_thपढ़ो = rec->opts.target.uid != अच_पूर्णांक_उच्च || rec->opts.target.pid;

	err = -ENOMEM;
	अगर (evlist__create_maps(rec->evlist, &rec->opts.target) < 0)
		usage_with_options(record_usage, record_options);

	err = auxtrace_record__options(rec->itr, rec->evlist, &rec->opts);
	अगर (err)
		जाओ out;

	/*
	 * We take all buildids when the file contains
	 * AUX area tracing data because we करो not decode the
	 * trace because it would take too दीर्घ.
	 */
	अगर (rec->opts.full_auxtrace)
		rec->buildid_all = true;

	अगर (rec->opts.text_poke) अणु
		err = record__config_text_poke(rec->evlist);
		अगर (err) अणु
			pr_err("record__config_text_poke failed, error %d\n", err);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (record_opts__config(&rec->opts)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (rec->opts.nr_cblocks > nr_cblocks_max)
		rec->opts.nr_cblocks = nr_cblocks_max;
	pr_debug("nr_cblocks: %d\n", rec->opts.nr_cblocks);

	pr_debug("affinity: %s\n", affinity_tags[rec->opts.affinity]);
	pr_debug("mmap flush: %d\n", rec->opts.mmap_flush);

	अगर (rec->opts.comp_level > comp_level_max)
		rec->opts.comp_level = comp_level_max;
	pr_debug("comp level: %d\n", rec->opts.comp_level);

	err = __cmd_record(&record, argc, argv);
out:
	biपंचांगap_मुक्त(rec->affinity_mask.bits);
	evlist__delete(rec->evlist);
	symbol__निकास();
	auxtrace_record__मुक्त(rec->itr);
out_opts:
	evlist__बंद_control(rec->opts.ctl_fd, rec->opts.ctl_fd_ack, &rec->opts.ctl_fd_बंद);
	वापस err;
पूर्ण

अटल व्योम snapshot_sig_handler(पूर्णांक sig __maybe_unused)
अणु
	काष्ठा record *rec = &record;

	hit_auxtrace_snapshot_trigger(rec);

	अगर (चयन_output_संकेत(rec))
		trigger_hit(&चयन_output_trigger);
पूर्ण

अटल व्योम alarm_sig_handler(पूर्णांक sig __maybe_unused)
अणु
	काष्ठा record *rec = &record;

	अगर (चयन_output_समय(rec))
		trigger_hit(&चयन_output_trigger);
पूर्ण
