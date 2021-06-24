<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB

/**
 * ibumad BPF sample user side
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * Copyright(c) 2018 Ira Weiny, Intel Corporation
 */

#समावेश <linux/bpf.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <सीमा.स>

#समावेश <sys/resource.h>
#समावेश <getopt.h>
#समावेश <net/अगर.h>

#समावेश <bpf/bpf.h>
#समावेश "bpf_util.h"
#समावेश <bpf/libbpf.h>

अटल काष्ठा bpf_link *tp_links[3];
अटल काष्ठा bpf_object *obj;
अटल पूर्णांक map_fd[2];
अटल पूर्णांक tp_cnt;

अटल व्योम dump_counts(पूर्णांक fd)
अणु
	__u32 key;
	__u64 value;

	क्रम (key = 0; key < 256; key++) अणु
		अगर (bpf_map_lookup_elem(fd, &key, &value)) अणु
			म_लिखो("failed to read key %u\n", key);
			जारी;
		पूर्ण
		अगर (value)
			म_लिखो("0x%02x : %llu\n", key, value);
	पूर्ण
पूर्ण

अटल व्योम dump_all_counts(व्योम)
अणु
	म_लिखो("Read 'Class : count'\n");
	dump_counts(map_fd[0]);
	म_लिखो("Write 'Class : count'\n");
	dump_counts(map_fd[1]);
पूर्ण

अटल व्योम dump_निकास(पूर्णांक sig)
अणु
	dump_all_counts();
	/* Detach tracepoपूर्णांकs */
	जबतक (tp_cnt)
		bpf_link__destroy(tp_links[--tp_cnt]);

	bpf_object__बंद(obj);
	निकास(0);
पूर्ण

अटल स्थिर काष्ठा option दीर्घ_options[] = अणु
	अणु"help",      no_argument,       शून्य, 'h'पूर्ण,
	अणु"delay",     required_argument, शून्य, 'd'पूर्ण,
पूर्ण;

अटल व्योम usage(अक्षर *cmd)
अणु
	म_लिखो("eBPF test program to count packets from various IP addresses\n"
		"Usage: %s <options>\n"
		"       --help,   -h  this menu\n"
		"       --delay,  -d  <delay>  wait <delay> sec between prints [1 - 1000000]\n"
		, cmd
		);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_program *prog;
	अचिन्हित दीर्घ delay = 5;
	अक्षर filename[256];
	पूर्णांक दीर्घindex = 0;
	पूर्णांक opt, err = -1;

	जबतक ((opt = getopt_दीर्घ(argc, argv, "hd:rSw",
				  दीर्घ_options, &दीर्घindex)) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			delay = म_से_अदीर्घ(optarg, शून्य, 0);
			अगर (delay == अच_दीर्घ_उच्च || delay < 0 ||
			    delay > 1000000) अणु
				ख_लिखो(मानक_त्रुटि, "ERROR: invalid delay : %s\n",
					optarg);
				usage(argv[0]);
				वापस 1;
			पूर्ण
			अवरोध;
		शेष:
		हाल 'h':
			usage(argv[0]);
			वापस 1;
		पूर्ण
	पूर्ण

	/* Do one final dump when निकासing */
	संकेत(संक_विघ्न, dump_निकास);
	संकेत(संक_इति, dump_निकास);

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस err;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "read_count");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "write_count");
	अगर (map_fd[0] < 0 || map_fd[1] < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		tp_links[tp_cnt] = bpf_program__attach(prog);
		अगर (libbpf_get_error(tp_links[tp_cnt])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			tp_links[tp_cnt] = शून्य;
			जाओ cleanup;
		पूर्ण
		tp_cnt++;
	पूर्ण

	जबतक (1) अणु
		sleep(delay);
		dump_all_counts();
	पूर्ण
	err = 0;

cleanup:
	/* Detach tracepoपूर्णांकs */
	जबतक (tp_cnt)
		bpf_link__destroy(tp_links[--tp_cnt]);

	bpf_object__बंद(obj);
	वापस err;
पूर्ण
