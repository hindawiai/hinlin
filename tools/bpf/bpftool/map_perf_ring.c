<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */
/* This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <bpf/libbpf.h>
#समावेश <poll.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <linux/bpf.h>
#समावेश <linux/perf_event.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/syscall.h>

#समावेश <bpf/bpf.h>
#समावेश <perf-sys.h>

#समावेश "main.h"

#घोषणा MMAP_PAGE_CNT	16

अटल अस्थिर bool stop;

काष्ठा event_ring_info अणु
	पूर्णांक fd;
	पूर्णांक key;
	अचिन्हित पूर्णांक cpu;
	व्योम *mem;
पूर्ण;

काष्ठा perf_event_sample अणु
	काष्ठा perf_event_header header;
	__u64 समय;
	__u32 size;
	अचिन्हित अक्षर data[];
पूर्ण;

काष्ठा perf_event_lost अणु
	काष्ठा perf_event_header header;
	__u64 id;
	__u64 lost;
पूर्ण;

अटल व्योम पूर्णांक_निकास(पूर्णांक signo)
अणु
	ख_लिखो(मानक_त्रुटि, "Stopping...\n");
	stop = true;
पूर्ण

काष्ठा event_pipe_ctx अणु
	bool all_cpus;
	पूर्णांक cpu;
	पूर्णांक idx;
पूर्ण;

अटल क्रमागत bpf_perf_event_ret
prपूर्णांक_bpf_output(व्योम *निजी_data, पूर्णांक cpu, काष्ठा perf_event_header *event)
अणु
	काष्ठा perf_event_sample *e = container_of(event,
						   काष्ठा perf_event_sample,
						   header);
	काष्ठा perf_event_lost *lost = container_of(event,
						    काष्ठा perf_event_lost,
						    header);
	काष्ठा event_pipe_ctx *ctx = निजी_data;
	पूर्णांक idx = ctx->all_cpus ? cpu : ctx->idx;

	अगर (json_output) अणु
		jsonw_start_object(json_wtr);
		jsonw_name(json_wtr, "type");
		jsonw_uपूर्णांक(json_wtr, e->header.type);
		jsonw_name(json_wtr, "cpu");
		jsonw_uपूर्णांक(json_wtr, cpu);
		jsonw_name(json_wtr, "index");
		jsonw_uपूर्णांक(json_wtr, idx);
		अगर (e->header.type == PERF_RECORD_SAMPLE) अणु
			jsonw_name(json_wtr, "timestamp");
			jsonw_uपूर्णांक(json_wtr, e->समय);
			jsonw_name(json_wtr, "data");
			prपूर्णांक_data_json(e->data, e->size);
		पूर्ण अन्यथा अगर (e->header.type == PERF_RECORD_LOST) अणु
			jsonw_name(json_wtr, "lost");
			jsonw_start_object(json_wtr);
			jsonw_name(json_wtr, "id");
			jsonw_uपूर्णांक(json_wtr, lost->id);
			jsonw_name(json_wtr, "count");
			jsonw_uपूर्णांक(json_wtr, lost->lost);
			jsonw_end_object(json_wtr);
		पूर्ण
		jsonw_end_object(json_wtr);
	पूर्ण अन्यथा अणु
		अगर (e->header.type == PERF_RECORD_SAMPLE) अणु
			म_लिखो("== @%lld.%09lld CPU: %d index: %d =====\n",
			       e->समय / 1000000000ULL, e->समय % 1000000000ULL,
			       cpu, idx);
			fprपूर्णांक_hex(मानक_निकास, e->data, e->size, " ");
			म_लिखो("\n");
		पूर्ण अन्यथा अगर (e->header.type == PERF_RECORD_LOST) अणु
			म_लिखो("lost %lld events\n", lost->lost);
		पूर्ण अन्यथा अणु
			म_लिखो("unknown event type=%d size=%d\n",
			       e->header.type, e->header.size);
		पूर्ण
	पूर्ण

	वापस LIBBPF_PERF_EVENT_CONT;
पूर्ण

पूर्णांक करो_event_pipe(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा perf_event_attr perf_attr = अणु
		.sample_type = PERF_SAMPLE_RAW | PERF_SAMPLE_TIME,
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_BPF_OUTPUT,
		.sample_period = 1,
		.wakeup_events = 1,
	पूर्ण;
	काष्ठा bpf_map_info map_info = अणुपूर्ण;
	काष्ठा perf_buffer_raw_opts opts = अणुपूर्ण;
	काष्ठा event_pipe_ctx ctx = अणु
		.all_cpus = true,
		.cpu = -1,
		.idx = -1,
	पूर्ण;
	काष्ठा perf_buffer *pb;
	__u32 map_info_len;
	पूर्णांक err, map_fd;

	map_info_len = माप(map_info);
	map_fd = map_parse_fd_and_info(&argc, &argv, &map_info, &map_info_len);
	अगर (map_fd < 0)
		वापस -1;

	अगर (map_info.type != BPF_MAP_TYPE_PERF_EVENT_ARRAY) अणु
		p_err("map is not a perf event array");
		जाओ err_बंद_map;
	पूर्ण

	जबतक (argc) अणु
		अगर (argc < 2) अणु
			BAD_ARG();
			जाओ err_बंद_map;
		पूर्ण

		अगर (is_prefix(*argv, "cpu")) अणु
			अक्षर *endptr;

			NEXT_ARG();
			ctx.cpu = म_से_अदीर्घ(*argv, &endptr, 0);
			अगर (*endptr) अणु
				p_err("can't parse %s as CPU ID", *argv);
				जाओ err_बंद_map;
			पूर्ण

			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "index")) अणु
			अक्षर *endptr;

			NEXT_ARG();
			ctx.idx = म_से_अदीर्घ(*argv, &endptr, 0);
			अगर (*endptr) अणु
				p_err("can't parse %s as index", *argv);
				जाओ err_बंद_map;
			पूर्ण

			NEXT_ARG();
		पूर्ण अन्यथा अणु
			BAD_ARG();
			जाओ err_बंद_map;
		पूर्ण

		ctx.all_cpus = false;
	पूर्ण

	अगर (!ctx.all_cpus) अणु
		अगर (ctx.idx == -1 || ctx.cpu == -1) अणु
			p_err("cpu and index must be specified together");
			जाओ err_बंद_map;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctx.cpu = 0;
		ctx.idx = 0;
	पूर्ण

	opts.attr = &perf_attr;
	opts.event_cb = prपूर्णांक_bpf_output;
	opts.ctx = &ctx;
	opts.cpu_cnt = ctx.all_cpus ? 0 : 1;
	opts.cpus = &ctx.cpu;
	opts.map_keys = &ctx.idx;

	pb = perf_buffer__new_raw(map_fd, MMAP_PAGE_CNT, &opts);
	err = libbpf_get_error(pb);
	अगर (err) अणु
		p_err("failed to create perf buffer: %s (%d)",
		      म_त्रुटि(err), err);
		जाओ err_बंद_map;
	पूर्ण

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(SIGHUP, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	अगर (json_output)
		jsonw_start_array(json_wtr);

	जबतक (!stop) अणु
		err = perf_buffer__poll(pb, 200);
		अगर (err < 0 && err != -EINTR) अणु
			p_err("perf buffer polling failed: %s (%d)",
			      म_त्रुटि(err), err);
			जाओ err_बंद_pb;
		पूर्ण
	पूर्ण

	अगर (json_output)
		jsonw_end_array(json_wtr);

	perf_buffer__मुक्त(pb);
	बंद(map_fd);

	वापस 0;

err_बंद_pb:
	perf_buffer__मुक्त(pb);
err_बंद_map:
	बंद(map_fd);
	वापस -1;
पूर्ण
