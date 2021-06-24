<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * JSON export.
 *
 * Copyright (C) 2021, CodeWeavers Inc. <nfraser@codeweavers.com>
 */

#समावेश "data-convert.h"

#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

#समावेश "linux/compiler.h"
#समावेश "linux/err.h"
#समावेश "util/auxtrace.h"
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश "util/event.h"
#समावेश "util/evsel.h"
#समावेश "util/evlist.h"
#समावेश "util/header.h"
#समावेश "util/map.h"
#समावेश "util/session.h"
#समावेश "util/symbol.h"
#समावेश "util/thread.h"
#समावेश "util/tool.h"

काष्ठा convert_json अणु
	काष्ठा perf_tool tool;
	खाता *out;
	bool first;
	u64 events_count;
पूर्ण;

// Outमाला_दो a JSON-encoded string surrounded by quotes with अक्षरacters escaped.
अटल व्योम output_json_string(खाता *out, स्थिर अक्षर *s)
अणु
	ख_अक्षर_दो('"', out);
	जबतक (*s) अणु
		चयन (*s) अणु

		// required escapes with special क्रमms as per RFC 8259
		हाल '"':  ख_माला_दो("\\\"", out); अवरोध;
		हाल '\\': ख_माला_दो("\\\\", out); अवरोध;
		हाल '\b': ख_माला_दो("\\b", out);  अवरोध;
		हाल '\f': ख_माला_दो("\\f", out);  अवरोध;
		हाल '\n': ख_माला_दो("\\n", out);  अवरोध;
		हाल '\r': ख_माला_दो("\\r", out);  अवरोध;
		हाल '\t': ख_माला_दो("\\t", out);  अवरोध;

		शेष:
			// all other control अक्षरacters must be escaped by hex code
			अगर (*s <= 0x1f)
				ख_लिखो(out, "\\u%04x", *s);
			अन्यथा
				ख_अक्षर_दो(*s, out);
			अवरोध;
		पूर्ण

		++s;
	पूर्ण
	ख_अक्षर_दो('"', out);
पूर्ण

// Outमाला_दो an optional comma, newline and indentation to delimit a new value
// from the previous one in a JSON object or array.
अटल व्योम output_json_delimiters(खाता *out, bool comma, पूर्णांक depth)
अणु
	पूर्णांक i;

	अगर (comma)
		ख_अक्षर_दो(',', out);
	ख_अक्षर_दो('\n', out);
	क्रम (i = 0; i < depth; ++i)
		ख_अक्षर_दो('\t', out);
पूर्ण

// Outमाला_दो a म_लिखो क्रमmat string (with delimiter) as a JSON value.
__म_लिखो(4, 5)
अटल व्योम output_json_क्रमmat(खाता *out, bool comma, पूर्णांक depth, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;

	output_json_delimiters(out, comma, depth);
	बहु_शुरू(args, क्रमmat);
	भख_लिखो(out,  क्रमmat, args);
	बहु_पूर्ण(args);
पूर्ण

// Outमाला_दो a JSON key-value pair where the value is a string.
अटल व्योम output_json_key_string(खाता *out, bool comma, पूर्णांक depth,
		स्थिर अक्षर *key, स्थिर अक्षर *value)
अणु
	output_json_delimiters(out, comma, depth);
	output_json_string(out, key);
	ख_माला_दो(": ", out);
	output_json_string(out, value);
पूर्ण

// Outमाला_दो a JSON key-value pair where the value is a म_लिखो क्रमmat string.
__म_लिखो(5, 6)
अटल व्योम output_json_key_क्रमmat(खाता *out, bool comma, पूर्णांक depth,
		स्थिर अक्षर *key, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;

	output_json_delimiters(out, comma, depth);
	output_json_string(out, key);
	ख_माला_दो(": ", out);
	बहु_शुरू(args, क्रमmat);
	भख_लिखो(out,  क्रमmat, args);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम output_sample_callchain_entry(काष्ठा perf_tool *tool,
		u64 ip, काष्ठा addr_location *al)
अणु
	काष्ठा convert_json *c = container_of(tool, काष्ठा convert_json, tool);
	खाता *out = c->out;

	output_json_क्रमmat(out, false, 4, "{");
	output_json_key_क्रमmat(out, false, 5, "ip", "\"0x%" PRIx64 "\"", ip);

	अगर (al && al->sym && al->sym->namelen) अणु
		ख_अक्षर_दो(',', out);
		output_json_key_string(out, false, 5, "symbol", al->sym->name);

		अगर (al->map && al->map->dso) अणु
			स्थिर अक्षर *dso = al->map->dso->लघु_name;

			अगर (dso && म_माप(dso) > 0) अणु
				ख_अक्षर_दो(',', out);
				output_json_key_string(out, false, 5, "dso", dso);
			पूर्ण
		पूर्ण
	पूर्ण

	output_json_क्रमmat(out, false, 4, "}");
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event __maybe_unused,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel __maybe_unused,
				काष्ठा machine *machine)
अणु
	काष्ठा convert_json *c = container_of(tool, काष्ठा convert_json, tool);
	खाता *out = c->out;
	काष्ठा addr_location al, tal;
	u8 cpumode = PERF_RECORD_MISC_USER;

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		pr_err("Sample resolution failed!\n");
		वापस -1;
	पूर्ण

	++c->events_count;

	अगर (c->first)
		c->first = false;
	अन्यथा
		ख_अक्षर_दो(',', out);
	output_json_क्रमmat(out, false, 2, "{");

	output_json_key_क्रमmat(out, false, 3, "timestamp", "%" PRIi64, sample->समय);
	output_json_key_क्रमmat(out, true, 3, "pid", "%i", al.thपढ़ो->pid_);
	output_json_key_क्रमmat(out, true, 3, "tid", "%i", al.thपढ़ो->tid);

	अगर (al.thपढ़ो->cpu >= 0)
		output_json_key_क्रमmat(out, true, 3, "cpu", "%i", al.thपढ़ो->cpu);

	output_json_key_string(out, true, 3, "comm", thपढ़ो__comm_str(al.thपढ़ो));

	output_json_key_क्रमmat(out, true, 3, "callchain", "[");
	अगर (sample->callchain) अणु
		अचिन्हित पूर्णांक i;
		bool ok;
		bool first_callchain = true;

		क्रम (i = 0; i < sample->callchain->nr; ++i) अणु
			u64 ip = sample->callchain->ips[i];

			अगर (ip >= PERF_CONTEXT_MAX) अणु
				चयन (ip) अणु
				हाल PERF_CONTEXT_HV:
					cpumode = PERF_RECORD_MISC_HYPERVISOR;
					अवरोध;
				हाल PERF_CONTEXT_KERNEL:
					cpumode = PERF_RECORD_MISC_KERNEL;
					अवरोध;
				हाल PERF_CONTEXT_USER:
					cpumode = PERF_RECORD_MISC_USER;
					अवरोध;
				शेष:
					pr_debug("invalid callchain context: %"
							PRId64 "\n", (s64) ip);
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण

			अगर (first_callchain)
				first_callchain = false;
			अन्यथा
				ख_अक्षर_दो(',', out);

			ok = thपढ़ो__find_symbol(al.thपढ़ो, cpumode, ip, &tal);
			output_sample_callchain_entry(tool, ip, ok ? &tal : शून्य);
		पूर्ण
	पूर्ण अन्यथा अणु
		output_sample_callchain_entry(tool, sample->ip, &al);
	पूर्ण
	output_json_क्रमmat(out, false, 3, "]");

	output_json_क्रमmat(out, false, 2, "}");
	वापस 0;
पूर्ण

अटल व्योम output_headers(काष्ठा perf_session *session, काष्ठा convert_json *c)
अणु
	काष्ठा stat st;
	काष्ठा perf_header *header = &session->header;
	पूर्णांक ret;
	पूर्णांक fd = perf_data__fd(session->data);
	पूर्णांक i;
	खाता *out = c->out;

	output_json_key_क्रमmat(out, false, 2, "header-version", "%u", header->version);

	ret = ख_स्थिति(fd, &st);
	अगर (ret >= 0) अणु
		समय_प्रकार stस_समय = st.st_mसमय;
		अक्षर buf[256];

		स_माला(buf, माप(buf), "%FT%TZ", स_जमट(&stस_समय));
		output_json_key_string(out, true, 2, "captured-on", buf);
	पूर्ण अन्यथा अणु
		pr_debug("Failed to get mtime of source file, not writing captured-on");
	पूर्ण

	output_json_key_क्रमmat(out, true, 2, "data-offset", "%" PRIu64, header->data_offset);
	output_json_key_क्रमmat(out, true, 2, "data-size", "%" PRIu64, header->data_size);
	output_json_key_क्रमmat(out, true, 2, "feat-offset", "%" PRIu64, header->feat_offset);

	output_json_key_string(out, true, 2, "hostname", header->env.hostname);
	output_json_key_string(out, true, 2, "os-release", header->env.os_release);
	output_json_key_string(out, true, 2, "arch", header->env.arch);

	output_json_key_string(out, true, 2, "cpu-desc", header->env.cpu_desc);
	output_json_key_string(out, true, 2, "cpuid", header->env.cpuid);
	output_json_key_क्रमmat(out, true, 2, "nrcpus-online", "%u", header->env.nr_cpus_online);
	output_json_key_क्रमmat(out, true, 2, "nrcpus-avail", "%u", header->env.nr_cpus_avail);

	अगर (header->env.घड़ी.enabled) अणु
		output_json_key_क्रमmat(out, true, 2, "clockid",
				"%u", header->env.घड़ी.घड़ीid);
		output_json_key_क्रमmat(out, true, 2, "clock-time",
				"%" PRIu64, header->env.घड़ी.घड़ीid_ns);
		output_json_key_क्रमmat(out, true, 2, "real-time",
				"%" PRIu64, header->env.घड़ी.tod_ns);
	पूर्ण

	output_json_key_string(out, true, 2, "perf-version", header->env.version);

	output_json_key_क्रमmat(out, true, 2, "cmdline", "[");
	क्रम (i = 0; i < header->env.nr_cmdline; i++) अणु
		output_json_delimiters(out, i != 0, 3);
		output_json_string(c->out, header->env.cmdline_argv[i]);
	पूर्ण
	output_json_क्रमmat(out, false, 2, "]");
पूर्ण

पूर्णांक bt_convert__perf2json(स्थिर अक्षर *input_name, स्थिर अक्षर *output_name,
		काष्ठा perf_data_convert_opts *opts __maybe_unused)
अणु
	काष्ठा perf_session *session;
	पूर्णांक fd;
	पूर्णांक ret = -1;

	काष्ठा convert_json c = अणु
		.tool = अणु
			.sample         = process_sample_event,
			.mmap           = perf_event__process_mmap,
			.mmap2          = perf_event__process_mmap2,
			.comm           = perf_event__process_comm,
			.namespaces     = perf_event__process_namespaces,
			.cgroup         = perf_event__process_cgroup,
			.निकास           = perf_event__process_निकास,
			.विभाजन           = perf_event__process_विभाजन,
			.lost           = perf_event__process_lost,
			.tracing_data   = perf_event__process_tracing_data,
			.build_id       = perf_event__process_build_id,
			.id_index       = perf_event__process_id_index,
			.auxtrace_info  = perf_event__process_auxtrace_info,
			.auxtrace       = perf_event__process_auxtrace,
			.event_update   = perf_event__process_event_update,
			.ordered_events = true,
			.ordering_requires_बारtamps = true,
		पूर्ण,
		.first = true,
		.events_count = 0,
	पूर्ण;

	काष्ठा perf_data data = अणु
		.mode = PERF_DATA_MODE_READ,
		.path = input_name,
		.क्रमce = opts->क्रमce,
	पूर्ण;

	अगर (opts->all) अणु
		pr_err("--all is currently unsupported for JSON output.\n");
		जाओ err;
	पूर्ण
	अगर (opts->tod) अणु
		pr_err("--tod is currently unsupported for JSON output.\n");
		जाओ err;
	पूर्ण

	fd = खोलो(output_name, O_CREAT | O_WRONLY | (opts->क्रमce ? O_TRUNC : O_EXCL), 0666);
	अगर (fd == -1) अणु
		अगर (त्रुटि_सं == EEXIST)
			pr_err("Output file exists. Use --force to overwrite it.\n");
		अन्यथा
			pr_err("Error opening output file!\n");
		जाओ err;
	पूर्ण

	c.out = fकरोpen(fd, "w");
	अगर (!c.out) अणु
		ख_लिखो(मानक_त्रुटि, "Error opening output file!\n");
		बंद(fd);
		जाओ err;
	पूर्ण

	session = perf_session__new(&data, false, &c.tool);
	अगर (IS_ERR(session)) अणु
		ख_लिखो(मानक_त्रुटि, "Error creating perf session!\n");
		जाओ err_ख_बंद;
	पूर्ण

	अगर (symbol__init(&session->header.env) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Symbol init error!\n");
		जाओ err_session_delete;
	पूर्ण

	// The खोलोing brace is prपूर्णांकed manually because it isn't delimited from a
	// previous value (i.e. we करोn't want a leading newline)
	ख_अक्षर_दो('{', c.out);

	// Version number क्रम future-proofing. Most additions should be able to be
	// करोne in a backwards-compatible way so this should only need to be bumped
	// अगर some major अवरोधing change must be made.
	output_json_क्रमmat(c.out, false, 1, "\"linux-perf-json-version\": 1");

	// Output headers
	output_json_क्रमmat(c.out, true, 1, "\"headers\": {");
	output_headers(session, &c);
	output_json_क्रमmat(c.out, false, 1, "}");

	// Output samples
	output_json_क्रमmat(c.out, true, 1, "\"samples\": [");
	perf_session__process_events(session);
	output_json_क्रमmat(c.out, false, 1, "]");
	output_json_क्रमmat(c.out, false, 0, "}");
	ख_अक्षर_दो('\n', c.out);

	ख_लिखो(मानक_त्रुटि,
			"[ perf data convert: Converted '%s' into JSON data '%s' ]\n",
			data.path, output_name);

	ख_लिखो(मानक_त्रुटि,
			"[ perf data convert: Converted and wrote %.3f MB (%" PRIu64 " samples) ]\n",
			(ख_बताओ(c.out)) / 1024.0 / 1024.0, c.events_count);

	ret = 0;
err_session_delete:
	perf_session__delete(session);
err_ख_बंद:
	ख_बंद(c.out);
err:
	वापस ret;
पूर्ण
