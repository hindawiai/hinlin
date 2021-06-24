<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_rlimit.h"
#समावेश "flow_dissector_load.h"

स्थिर अक्षर *cfg_pin_path = "/sys/fs/bpf/flow_dissector";
स्थिर अक्षर *cfg_map_name = "jmp_table";
bool cfg_attach = true;
अक्षर *cfg_section_name;
अक्षर *cfg_path_name;

अटल व्योम load_and_attach_program(व्योम)
अणु
	पूर्णांक prog_fd, ret;
	काष्ठा bpf_object *obj;

	ret = bpf_flow_load(&obj, cfg_path_name, cfg_section_name,
			    cfg_map_name, शून्य, &prog_fd, शून्य);
	अगर (ret)
		error(1, 0, "bpf_flow_load %s", cfg_path_name);

	ret = bpf_prog_attach(prog_fd, 0 /* Ignore */, BPF_FLOW_DISSECTOR, 0);
	अगर (ret)
		error(1, 0, "bpf_prog_attach %s", cfg_path_name);

	ret = bpf_object__pin(obj, cfg_pin_path);
	अगर (ret)
		error(1, 0, "bpf_object__pin %s", cfg_pin_path);
पूर्ण

अटल व्योम detach_program(व्योम)
अणु
	अक्षर command[64];
	पूर्णांक ret;

	ret = bpf_prog_detach(0, BPF_FLOW_DISSECTOR);
	अगर (ret)
		error(1, 0, "bpf_prog_detach");

	/* To unpin, it is necessary and sufficient to just हटाओ this dir */
	प्र_लिखो(command, "rm -r %s", cfg_pin_path);
	ret = प्रणाली(command);
	अगर (ret)
		error(1, त्रुटि_सं, "%s", command);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	bool attach = false;
	bool detach = false;
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "adp:s:")) != -1) अणु
		चयन (c) अणु
		हाल 'a':
			अगर (detach)
				error(1, 0, "attach/detach are exclusive");
			attach = true;
			अवरोध;
		हाल 'd':
			अगर (attach)
				error(1, 0, "attach/detach are exclusive");
			detach = true;
			अवरोध;
		हाल 'p':
			अगर (cfg_path_name)
				error(1, 0, "only one prog name can be given");

			cfg_path_name = optarg;
			अवरोध;
		हाल 's':
			अगर (cfg_section_name)
				error(1, 0, "only one section can be given");

			cfg_section_name = optarg;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (detach)
		cfg_attach = false;

	अगर (cfg_attach && !cfg_path_name)
		error(1, 0, "must provide a path to the BPF program");

	अगर (cfg_attach && !cfg_section_name)
		error(1, 0, "must provide a section name");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_opts(argc, argv);
	अगर (cfg_attach)
		load_and_attach_program();
	अन्यथा
		detach_program();
	वापस 0;
पूर्ण
