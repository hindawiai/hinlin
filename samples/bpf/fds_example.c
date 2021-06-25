<शैली गुरु>
#समावेश <linux/unistd.h>
#समावेश <linux/bpf.h>

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>

#समावेश <sys/types.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf.h>

#समावेश <bpf/libbpf.h>
#समावेश "bpf_insn.h"
#समावेश "sock_example.h"

#घोषणा BPF_F_PIN	(1 << 0)
#घोषणा BPF_F_GET	(1 << 1)
#घोषणा BPF_F_PIN_GET	(BPF_F_PIN | BPF_F_GET)

#घोषणा BPF_F_KEY	(1 << 2)
#घोषणा BPF_F_VAL	(1 << 3)
#घोषणा BPF_F_KEY_VAL	(BPF_F_KEY | BPF_F_VAL)

#घोषणा BPF_M_UNSPEC	0
#घोषणा BPF_M_MAP	1
#घोषणा BPF_M_PROG	2

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

अटल व्योम usage(व्योम)
अणु
	म_लिखो("Usage: fds_example [...]\n");
	म_लिखो("       -F <file>   File to pin/get object\n");
	म_लिखो("       -P          |- pin object\n");
	म_लिखो("       -G          `- get object\n");
	म_लिखो("       -m          eBPF map mode\n");
	म_लिखो("       -k <key>    |- map key\n");
	म_लिखो("       -v <value>  `- map value\n");
	म_लिखो("       -p          eBPF prog mode\n");
	म_लिखो("       -o <object> `- object file\n");
	म_लिखो("       -h          Display this help.\n");
पूर्ण

अटल पूर्णांक bpf_map_create(व्योम)
अणु
	वापस bpf_create_map(BPF_MAP_TYPE_ARRAY, माप(uपूर्णांक32_t),
			      माप(uपूर्णांक32_t), 1024, 0);
पूर्ण

अटल पूर्णांक bpf_prog_create(स्थिर अक्षर *object)
अणु
	अटल काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt = माप(insns) / माप(काष्ठा bpf_insn);
	काष्ठा bpf_object *obj;
	पूर्णांक prog_fd;

	अगर (object) अणु
		निश्चित(!bpf_prog_load(object, BPF_PROG_TYPE_UNSPEC,
				      &obj, &prog_fd));
		वापस prog_fd;
	पूर्ण अन्यथा अणु
		वापस bpf_load_program(BPF_PROG_TYPE_SOCKET_FILTER,
					insns, insns_cnt, "GPL", 0,
					bpf_log_buf, BPF_LOG_BUF_SIZE);
	पूर्ण
पूर्ण

अटल पूर्णांक bpf_करो_map(स्थिर अक्षर *file, uपूर्णांक32_t flags, uपूर्णांक32_t key,
		      uपूर्णांक32_t value)
अणु
	पूर्णांक fd, ret;

	अगर (flags & BPF_F_PIN) अणु
		fd = bpf_map_create();
		म_लिखो("bpf: map fd:%d (%s)\n", fd, म_त्रुटि(त्रुटि_सं));
		निश्चित(fd > 0);

		ret = bpf_obj_pin(fd, file);
		म_लिखो("bpf: pin ret:(%d,%s)\n", ret, म_त्रुटि(त्रुटि_सं));
		निश्चित(ret == 0);
	पूर्ण अन्यथा अणु
		fd = bpf_obj_get(file);
		म_लिखो("bpf: get fd:%d (%s)\n", fd, म_त्रुटि(त्रुटि_सं));
		निश्चित(fd > 0);
	पूर्ण

	अगर ((flags & BPF_F_KEY_VAL) == BPF_F_KEY_VAL) अणु
		ret = bpf_map_update_elem(fd, &key, &value, 0);
		म_लिखो("bpf: fd:%d u->(%u:%u) ret:(%d,%s)\n", fd, key, value,
		       ret, म_त्रुटि(त्रुटि_सं));
		निश्चित(ret == 0);
	पूर्ण अन्यथा अगर (flags & BPF_F_KEY) अणु
		ret = bpf_map_lookup_elem(fd, &key, &value);
		म_लिखो("bpf: fd:%d l->(%u):%u ret:(%d,%s)\n", fd, key, value,
		       ret, म_त्रुटि(त्रुटि_सं));
		निश्चित(ret == 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_करो_prog(स्थिर अक्षर *file, uपूर्णांक32_t flags, स्थिर अक्षर *object)
अणु
	पूर्णांक fd, sock, ret;

	अगर (flags & BPF_F_PIN) अणु
		fd = bpf_prog_create(object);
		म_लिखो("bpf: prog fd:%d (%s)\n", fd, म_त्रुटि(त्रुटि_सं));
		निश्चित(fd > 0);

		ret = bpf_obj_pin(fd, file);
		म_लिखो("bpf: pin ret:(%d,%s)\n", ret, म_त्रुटि(त्रुटि_सं));
		निश्चित(ret == 0);
	पूर्ण अन्यथा अणु
		fd = bpf_obj_get(file);
		म_लिखो("bpf: get fd:%d (%s)\n", fd, म_त्रुटि(त्रुटि_सं));
		निश्चित(fd > 0);
	पूर्ण

	sock = खोलो_raw_sock("lo");
	निश्चित(sock > 0);

	ret = setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &fd, माप(fd));
	म_लिखो("bpf: sock:%d <- fd:%d attached ret:(%d,%s)\n", sock, fd,
	       ret, म_त्रुटि(त्रुटि_सं));
	निश्चित(ret == 0);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *file = शून्य, *object = शून्य;
	uपूर्णांक32_t key = 0, value = 0, flags = 0;
	पूर्णांक opt, mode = BPF_M_UNSPEC;

	जबतक ((opt = getopt(argc, argv, "F:PGmk:v:po:")) != -1) अणु
		चयन (opt) अणु
		/* General args */
		हाल 'F':
			file = optarg;
			अवरोध;
		हाल 'P':
			flags |= BPF_F_PIN;
			अवरोध;
		हाल 'G':
			flags |= BPF_F_GET;
			अवरोध;
		/* Map-related args */
		हाल 'm':
			mode = BPF_M_MAP;
			अवरोध;
		हाल 'k':
			key = म_से_अदीर्घ(optarg, शून्य, 0);
			flags |= BPF_F_KEY;
			अवरोध;
		हाल 'v':
			value = म_से_अदीर्घ(optarg, शून्य, 0);
			flags |= BPF_F_VAL;
			अवरोध;
		/* Prog-related args */
		हाल 'p':
			mode = BPF_M_PROG;
			अवरोध;
		हाल 'o':
			object = optarg;
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!(flags & BPF_F_PIN_GET) || !file)
		जाओ out;

	चयन (mode) अणु
	हाल BPF_M_MAP:
		वापस bpf_करो_map(file, flags, key, value);
	हाल BPF_M_PROG:
		वापस bpf_करो_prog(file, flags, object);
	पूर्ण
out:
	usage();
	वापस -1;
पूर्ण
