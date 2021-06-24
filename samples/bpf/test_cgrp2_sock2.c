<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* eBPF example program:
 *
 * - Loads eBPF program
 *
 *   The eBPF program loads a filter from file and attaches the
 *   program to a cgroup using BPF_PROG_ATTACH
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <net/अगर.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_insn.h"

अटल पूर्णांक usage(स्थिर अक्षर *argv0)
अणु
	म_लिखो("Usage: %s cg-path filter-path [filter-id]\n", argv0);
	वापस निकास_त्रुटि;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक cg_fd, err, ret = निकास_त्रुटि, filter_id = 0, prog_cnt = 0;
	स्थिर अक्षर *link_pin_path = "/sys/fs/bpf/test_cgrp2_sock2";
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *progs[2];
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;

	अगर (argc < 3)
		वापस usage(argv[0]);

	अगर (argc > 3)
		filter_id = म_से_प(argv[3]);

	cg_fd = खोलो(argv[1], O_सूचीECTORY | O_RDONLY);
	अगर (cg_fd < 0) अणु
		म_लिखो("Failed to open cgroup path: '%s'\n", म_त्रुटि(त्रुटि_सं));
		वापस ret;
	पूर्ण

	obj = bpf_object__खोलो_file(argv[2], शून्य);
	अगर (libbpf_get_error(obj)) अणु
		म_लिखो("ERROR: opening BPF object file failed\n");
		वापस ret;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		progs[prog_cnt] = prog;
		prog_cnt++;
	पूर्ण

	अगर (filter_id >= prog_cnt) अणु
		म_लिखो("Invalid program id; program not found in file\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		म_लिखो("ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	link = bpf_program__attach_cgroup(progs[filter_id], cg_fd);
	अगर (libbpf_get_error(link)) अणु
		म_लिखो("ERROR: bpf_program__attach failed\n");
		link = शून्य;
		जाओ cleanup;
	पूर्ण

	err = bpf_link__pin(link, link_pin_path);
	अगर (err < 0) अणु
		म_लिखो("ERROR: bpf_link__pin failed: %d\n", err);
		जाओ cleanup;
	पूर्ण

	ret = निकास_सफल;

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस ret;
पूर्ण
