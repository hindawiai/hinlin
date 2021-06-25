<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
#अगर_अघोषित FLOW_DISSECTOR_LOAD
#घोषणा FLOW_DISSECTOR_LOAD

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

अटल अंतरभूत पूर्णांक bpf_flow_load(काष्ठा bpf_object **obj,
				स्थिर अक्षर *path,
				स्थिर अक्षर *section_name,
				स्थिर अक्षर *map_name,
				स्थिर अक्षर *keys_map_name,
				पूर्णांक *prog_fd,
				पूर्णांक *keys_fd)
अणु
	काष्ठा bpf_program *prog, *मुख्य_prog;
	काष्ठा bpf_map *prog_array, *keys;
	पूर्णांक prog_array_fd;
	पूर्णांक ret, fd, i;

	ret = bpf_prog_load(path, BPF_PROG_TYPE_FLOW_DISSECTOR, obj,
			    prog_fd);
	अगर (ret)
		वापस ret;

	मुख्य_prog = शून्य;
	bpf_object__क्रम_each_program(prog, *obj) अणु
		अगर (म_भेद(section_name, bpf_program__section_name(prog)) == 0) अणु
			मुख्य_prog = prog;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!मुख्य_prog)
		वापस -1;

	*prog_fd = bpf_program__fd(मुख्य_prog);
	अगर (*prog_fd < 0)
		वापस -1;

	prog_array = bpf_object__find_map_by_name(*obj, map_name);
	अगर (!prog_array)
		वापस -1;

	prog_array_fd = bpf_map__fd(prog_array);
	अगर (prog_array_fd < 0)
		वापस -1;

	अगर (keys_map_name && keys_fd) अणु
		keys = bpf_object__find_map_by_name(*obj, keys_map_name);
		अगर (!keys)
			वापस -1;

		*keys_fd = bpf_map__fd(keys);
		अगर (*keys_fd < 0)
			वापस -1;
	पूर्ण

	i = 0;
	bpf_object__क्रम_each_program(prog, *obj) अणु
		fd = bpf_program__fd(prog);
		अगर (fd < 0)
			वापस fd;

		अगर (fd != *prog_fd) अणु
			bpf_map_update_elem(prog_array_fd, &i, &fd, BPF_ANY);
			++i;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* FLOW_DISSECTOR_LOAD */
