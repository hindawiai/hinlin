<शैली गुरु>
#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <bpf/libbpf.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	अक्षर command[256];
	पूर्णांक ret = 0;
	खाता *f;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "bpf_prog1");
	अगर (!prog) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a prog in obj file failed\n");
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

	snम_लिखो(command, 256, "mount %s tmpmnt/", argv[1]);
	f = pखोलो(command, "r");
	ret = pबंद(f);

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस ret ? 0 : 1;
पूर्ण
