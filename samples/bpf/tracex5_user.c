<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <linux/filter.h>
#समावेश <linux/seccomp.h>
#समावेश <sys/prctl.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <sys/resource.h>
#समावेश "trace_helpers.h"

#अगर_घोषित __mips__
#घोषणा	MAX_ENTRIES  6000 /* MIPS n64 syscalls start at 5000 */
#अन्यथा
#घोषणा	MAX_ENTRIES  1024
#पूर्ण_अगर

/* install fake seccomp program to enable seccomp code path inside the kernel,
 * so that our kprobe attached to seccomp_phase1() can be triggered
 */
अटल व्योम install_accept_all_seccomp(व्योम)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)(माप(filter)/माप(filter[0])),
		.filter = filter,
	पूर्ण;
	अगर (prctl(PR_SET_SECCOMP, 2, &prog))
		लिखो_त्रुटि("prctl");
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	पूर्णांक key, fd, progs_fd;
	स्थिर अक्षर *section;
	अक्षर filename[256];
	खाता *f;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "bpf_prog1");
	अगर (!prog) अणु
		म_लिखो("finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	link = bpf_program__attach(prog);
	अगर (libbpf_get_error(link)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
		link = शून्य;
		जाओ cleanup;
	पूर्ण

	progs_fd = bpf_object__find_map_fd_by_name(obj, "progs");
	अगर (progs_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		section = bpf_program__section_name(prog);
		/* रेजिस्टर only syscalls to PROG_ARRAY */
		अगर (माला_पूछो(section, "kprobe/%d", &key) != 1)
			जारी;

		fd = bpf_program__fd(prog);
		bpf_map_update_elem(progs_fd, &key, &fd, BPF_ANY);
	पूर्ण

	install_accept_all_seccomp();

	f = pखोलो("dd if=/dev/zero of=/dev/null count=5", "r");
	(व्योम) f;

	पढ़ो_trace_pipe();

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
