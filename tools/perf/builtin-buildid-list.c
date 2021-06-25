<शैली गुरु>
/*
 * builtin-buildid-list.c
 *
 * Builtin buildid-list command: list buildids in perf.data, in the running
 * kernel and in ELF files.
 *
 * Copyright (C) 2009, Red Hat Inc.
 * Copyright (C) 2009, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */
#समावेश "builtin.h"
#समावेश "perf.h"
#समावेश "util/build-id.h"
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/session.h"
#समावेश "util/symbol.h"
#समावेश "util/data.h"
#समावेश <त्रुटिसं.स>
#समावेश <linux/err.h>

अटल पूर्णांक sysfs__ख_लिखो_build_id(खाता *fp)
अणु
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	पूर्णांक ret;

	ret = sysfs__प्र_लिखो_build_id("/", sbuild_id);
	अगर (ret != माप(sbuild_id))
		वापस ret < 0 ? ret : -EINVAL;

	वापस ख_लिखो(fp, "%s\n", sbuild_id);
पूर्ण

अटल पूर्णांक filename__ख_लिखो_build_id(स्थिर अक्षर *name, खाता *fp)
अणु
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	पूर्णांक ret;

	ret = filename__प्र_लिखो_build_id(name, sbuild_id);
	अगर (ret != माप(sbuild_id))
		वापस ret < 0 ? ret : -EINVAL;

	वापस ख_लिखो(fp, "%s\n", sbuild_id);
पूर्ण

अटल bool dso__skip_buildid(काष्ठा dso *dso, पूर्णांक with_hits)
अणु
	वापस with_hits && !dso->hit;
पूर्ण

अटल पूर्णांक perf_session__list_build_ids(bool क्रमce, bool with_hits)
अणु
	काष्ठा perf_session *session;
	काष्ठा perf_data data = अणु
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = क्रमce,
	पूर्ण;

	symbol__elf_init();
	/*
	 * See अगर this is an ELF file first:
	 */
	अगर (filename__ख_लिखो_build_id(input_name, मानक_निकास) > 0)
		जाओ out;

	session = perf_session__new(&data, false, &build_id__mark_dso_hit_ops);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	/*
	 * We take all buildids when the file contains AUX area tracing data
	 * because we करो not decode the trace because it would take too दीर्घ.
	 */
	अगर (!perf_data__is_pipe(&data) &&
	    perf_header__has_feat(&session->header, HEADER_AUXTRACE))
		with_hits = false;

	अगर (!perf_header__has_feat(&session->header, HEADER_BUILD_ID))
		with_hits = true;

	अगर (zstd_init(&(session->zstd_data), 0) < 0)
		pr_warning("Decompression initialization failed. Reported data may be incomplete.\n");

	/*
	 * in pipe-mode, the only way to get the buildids is to parse
	 * the record stream. Buildids are stored as RECORD_HEADER_BUILD_ID
	 */
	अगर (with_hits || perf_data__is_pipe(&data))
		perf_session__process_events(session);

	perf_session__ख_लिखो_dsos_buildid(session, मानक_निकास, dso__skip_buildid, with_hits);
	perf_session__delete(session);
out:
	वापस 0;
पूर्ण

पूर्णांक cmd_buildid_list(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	bool show_kernel = false;
	bool with_hits = false;
	bool क्रमce = false;
	स्थिर काष्ठा option options[] = अणु
	OPT_BOOLEAN('H', "with-hits", &with_hits, "Show only DSOs with hits"),
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_BOOLEAN('f', "force", &force, "don't complain, करो it"),
	OPT_BOOLEAN('k', "kernel", &show_kernel, "Show current kernel build id"),
	OPT_INCR('v', "verbose", &verbose, "be more verbose"),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर buildid_list_usage[] = अणु
		"perf buildid-list [<options>]",
		शून्य
	पूर्ण;

	argc = parse_options(argc, argv, options, buildid_list_usage, 0);
	setup_pager();

	अगर (show_kernel)
		वापस !(sysfs__ख_लिखो_build_id(मानक_निकास) > 0);

	वापस perf_session__list_build_ids(क्रमce, with_hits);
पूर्ण
