<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <net/अगर.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/btf.h>

#समावेश "json_writer.h"
#समावेश "main.h"

स्थिर अक्षर * स्थिर map_type_name[] = अणु
	[BPF_MAP_TYPE_UNSPEC]			= "unspec",
	[BPF_MAP_TYPE_HASH]			= "hash",
	[BPF_MAP_TYPE_ARRAY]			= "array",
	[BPF_MAP_TYPE_PROG_ARRAY]		= "prog_array",
	[BPF_MAP_TYPE_PERF_EVENT_ARRAY]		= "perf_event_array",
	[BPF_MAP_TYPE_PERCPU_HASH]		= "percpu_hash",
	[BPF_MAP_TYPE_PERCPU_ARRAY]		= "percpu_array",
	[BPF_MAP_TYPE_STACK_TRACE]		= "stack_trace",
	[BPF_MAP_TYPE_CGROUP_ARRAY]		= "cgroup_array",
	[BPF_MAP_TYPE_LRU_HASH]			= "lru_hash",
	[BPF_MAP_TYPE_LRU_PERCPU_HASH]		= "lru_percpu_hash",
	[BPF_MAP_TYPE_LPM_TRIE]			= "lpm_trie",
	[BPF_MAP_TYPE_ARRAY_OF_MAPS]		= "array_of_maps",
	[BPF_MAP_TYPE_HASH_OF_MAPS]		= "hash_of_maps",
	[BPF_MAP_TYPE_DEVMAP]			= "devmap",
	[BPF_MAP_TYPE_DEVMAP_HASH]		= "devmap_hash",
	[BPF_MAP_TYPE_SOCKMAP]			= "sockmap",
	[BPF_MAP_TYPE_CPUMAP]			= "cpumap",
	[BPF_MAP_TYPE_XSKMAP]			= "xskmap",
	[BPF_MAP_TYPE_SOCKHASH]			= "sockhash",
	[BPF_MAP_TYPE_CGROUP_STORAGE]		= "cgroup_storage",
	[BPF_MAP_TYPE_REUSEPORT_SOCKARRAY]	= "reuseport_sockarray",
	[BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE]	= "percpu_cgroup_storage",
	[BPF_MAP_TYPE_QUEUE]			= "queue",
	[BPF_MAP_TYPE_STACK]			= "stack",
	[BPF_MAP_TYPE_SK_STORAGE]		= "sk_storage",
	[BPF_MAP_TYPE_STRUCT_OPS]		= "struct_ops",
	[BPF_MAP_TYPE_RINGBUF]			= "ringbuf",
	[BPF_MAP_TYPE_INODE_STORAGE]		= "inode_storage",
	[BPF_MAP_TYPE_TASK_STORAGE]		= "task_storage",
पूर्ण;

स्थिर माप_प्रकार map_type_name_size = ARRAY_SIZE(map_type_name);

अटल bool map_is_per_cpu(__u32 type)
अणु
	वापस type == BPF_MAP_TYPE_PERCPU_HASH ||
	       type == BPF_MAP_TYPE_PERCPU_ARRAY ||
	       type == BPF_MAP_TYPE_LRU_PERCPU_HASH ||
	       type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE;
पूर्ण

अटल bool map_is_map_of_maps(__u32 type)
अणु
	वापस type == BPF_MAP_TYPE_ARRAY_OF_MAPS ||
	       type == BPF_MAP_TYPE_HASH_OF_MAPS;
पूर्ण

अटल bool map_is_map_of_progs(__u32 type)
अणु
	वापस type == BPF_MAP_TYPE_PROG_ARRAY;
पूर्ण

अटल पूर्णांक map_type_from_str(स्थिर अक्षर *type)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(map_type_name); i++)
		/* Don't allow prefixing in हाल of possible future shaकरोwing */
		अगर (map_type_name[i] && !म_भेद(map_type_name[i], type))
			वापस i;
	वापस -1;
पूर्ण

अटल व्योम *alloc_value(काष्ठा bpf_map_info *info)
अणु
	अगर (map_is_per_cpu(info->type))
		वापस दो_स्मृति(round_up(info->value_size, 8) *
			      get_possible_cpus());
	अन्यथा
		वापस दो_स्मृति(info->value_size);
पूर्ण

अटल पूर्णांक करो_dump_btf(स्थिर काष्ठा btf_dumper *d,
		       काष्ठा bpf_map_info *map_info, व्योम *key,
		       व्योम *value)
अणु
	__u32 value_id;
	पूर्णांक ret = 0;

	/* start of key-value pair */
	jsonw_start_object(d->jw);

	अगर (map_info->btf_key_type_id) अणु
		jsonw_name(d->jw, "key");

		ret = btf_dumper_type(d, map_info->btf_key_type_id, key);
		अगर (ret)
			जाओ err_end_obj;
	पूर्ण

	value_id = map_info->btf_vmlinux_value_type_id ?
		: map_info->btf_value_type_id;

	अगर (!map_is_per_cpu(map_info->type)) अणु
		jsonw_name(d->jw, "value");
		ret = btf_dumper_type(d, value_id, value);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i, n, step;

		jsonw_name(d->jw, "values");
		jsonw_start_array(d->jw);
		n = get_possible_cpus();
		step = round_up(map_info->value_size, 8);
		क्रम (i = 0; i < n; i++) अणु
			jsonw_start_object(d->jw);
			jsonw_पूर्णांक_field(d->jw, "cpu", i);
			jsonw_name(d->jw, "value");
			ret = btf_dumper_type(d, value_id, value + i * step);
			jsonw_end_object(d->jw);
			अगर (ret)
				अवरोध;
		पूर्ण
		jsonw_end_array(d->jw);
	पूर्ण

err_end_obj:
	/* end of key-value pair */
	jsonw_end_object(d->jw);

	वापस ret;
पूर्ण

अटल json_ग_लिखोr_t *get_btf_ग_लिखोr(व्योम)
अणु
	json_ग_लिखोr_t *jw = jsonw_new(मानक_निकास);

	अगर (!jw)
		वापस शून्य;
	jsonw_pretty(jw, true);

	वापस jw;
पूर्ण

अटल व्योम prपूर्णांक_entry_json(काष्ठा bpf_map_info *info, अचिन्हित अक्षर *key,
			     अचिन्हित अक्षर *value, काष्ठा btf *btf)
अणु
	jsonw_start_object(json_wtr);

	अगर (!map_is_per_cpu(info->type)) अणु
		jsonw_name(json_wtr, "key");
		prपूर्णांक_hex_data_json(key, info->key_size);
		jsonw_name(json_wtr, "value");
		prपूर्णांक_hex_data_json(value, info->value_size);
		अगर (btf) अणु
			काष्ठा btf_dumper d = अणु
				.btf = btf,
				.jw = json_wtr,
				.is_plain_text = false,
			पूर्ण;

			jsonw_name(json_wtr, "formatted");
			करो_dump_btf(&d, info, key, value);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i, n, step;

		n = get_possible_cpus();
		step = round_up(info->value_size, 8);

		jsonw_name(json_wtr, "key");
		prपूर्णांक_hex_data_json(key, info->key_size);

		jsonw_name(json_wtr, "values");
		jsonw_start_array(json_wtr);
		क्रम (i = 0; i < n; i++) अणु
			jsonw_start_object(json_wtr);

			jsonw_पूर्णांक_field(json_wtr, "cpu", i);

			jsonw_name(json_wtr, "value");
			prपूर्णांक_hex_data_json(value + i * step,
					    info->value_size);

			jsonw_end_object(json_wtr);
		पूर्ण
		jsonw_end_array(json_wtr);
		अगर (btf) अणु
			काष्ठा btf_dumper d = अणु
				.btf = btf,
				.jw = json_wtr,
				.is_plain_text = false,
			पूर्ण;

			jsonw_name(json_wtr, "formatted");
			करो_dump_btf(&d, info, key, value);
		पूर्ण
	पूर्ण

	jsonw_end_object(json_wtr);
पूर्ण

अटल व्योम
prपूर्णांक_entry_error_msg(काष्ठा bpf_map_info *info, अचिन्हित अक्षर *key,
		      स्थिर अक्षर *error_msg)
अणु
	पूर्णांक msg_size = म_माप(error_msg);
	bool single_line, अवरोध_names;

	अवरोध_names = info->key_size > 16 || msg_size > 16;
	single_line = info->key_size + msg_size <= 24 && !अवरोध_names;

	म_लिखो("key:%c", अवरोध_names ? '\n' : ' ');
	fprपूर्णांक_hex(मानक_निकास, key, info->key_size, " ");

	म_लिखो(single_line ? "  " : "\n");

	म_लिखो("value:%c%s", अवरोध_names ? '\n' : ' ', error_msg);

	म_लिखो("\n");
पूर्ण

अटल व्योम
prपूर्णांक_entry_error(काष्ठा bpf_map_info *map_info, व्योम *key, पूर्णांक lookup_त्रुटि_सं)
अणु
	/* For prog_array maps or arrays of maps, failure to lookup the value
	 * means there is no entry क्रम that key. Do not prपूर्णांक an error message
	 * in that हाल.
	 */
	अगर ((map_is_map_of_maps(map_info->type) ||
	     map_is_map_of_progs(map_info->type)) && lookup_त्रुटि_सं == ENOENT)
		वापस;

	अगर (json_output) अणु
		jsonw_start_object(json_wtr);	/* entry */
		jsonw_name(json_wtr, "key");
		prपूर्णांक_hex_data_json(key, map_info->key_size);
		jsonw_name(json_wtr, "value");
		jsonw_start_object(json_wtr);	/* error */
		jsonw_string_field(json_wtr, "error", म_त्रुटि(lookup_त्रुटि_सं));
		jsonw_end_object(json_wtr);	/* error */
		jsonw_end_object(json_wtr);	/* entry */
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *msg = शून्य;

		अगर (lookup_त्रुटि_सं == ENOENT)
			msg = "<no entry>";
		अन्यथा अगर (lookup_त्रुटि_सं == ENOSPC &&
			 map_info->type == BPF_MAP_TYPE_REUSEPORT_SOCKARRAY)
			msg = "<cannot read>";

		prपूर्णांक_entry_error_msg(map_info, key,
				      msg ? : म_त्रुटि(lookup_त्रुटि_सं));
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_entry_plain(काष्ठा bpf_map_info *info, अचिन्हित अक्षर *key,
			      अचिन्हित अक्षर *value)
अणु
	अगर (!map_is_per_cpu(info->type)) अणु
		bool single_line, अवरोध_names;

		अवरोध_names = info->key_size > 16 || info->value_size > 16;
		single_line = info->key_size + info->value_size <= 24 &&
			!अवरोध_names;

		अगर (info->key_size) अणु
			म_लिखो("key:%c", अवरोध_names ? '\n' : ' ');
			fprपूर्णांक_hex(मानक_निकास, key, info->key_size, " ");

			म_लिखो(single_line ? "  " : "\n");
		पूर्ण

		अगर (info->value_size) अणु
			म_लिखो("value:%c", अवरोध_names ? '\n' : ' ');
			fprपूर्णांक_hex(मानक_निकास, value, info->value_size, " ");
		पूर्ण

		म_लिखो("\n");
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i, n, step;

		n = get_possible_cpus();
		step = round_up(info->value_size, 8);

		अगर (info->key_size) अणु
			म_लिखो("key:\n");
			fprपूर्णांक_hex(मानक_निकास, key, info->key_size, " ");
			म_लिखो("\n");
		पूर्ण
		अगर (info->value_size) अणु
			क्रम (i = 0; i < n; i++) अणु
				म_लिखो("value (CPU %02d):%c",
				       i, info->value_size > 16 ? '\n' : ' ');
				fprपूर्णांक_hex(मानक_निकास, value + i * step,
					   info->value_size, " ");
				म_लिखो("\n");
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अक्षर **parse_bytes(अक्षर **argv, स्थिर अक्षर *name, अचिन्हित अक्षर *val,
			  अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i = 0, base = 0;
	अक्षर *endptr;

	अगर (is_prefix(*argv, "hex")) अणु
		base = 16;
		argv++;
	पूर्ण

	जबतक (i < n && argv[i]) अणु
		val[i] = म_से_अदीर्घ(argv[i], &endptr, base);
		अगर (*endptr) अणु
			p_err("error parsing byte: %s", argv[i]);
			वापस शून्य;
		पूर्ण
		i++;
	पूर्ण

	अगर (i != n) अणु
		p_err("%s expected %d bytes got %d", name, n, i);
		वापस शून्य;
	पूर्ण

	वापस argv + i;
पूर्ण

/* on per cpu maps we must copy the provided value on all value instances */
अटल व्योम fill_per_cpu_value(काष्ठा bpf_map_info *info, व्योम *value)
अणु
	अचिन्हित पूर्णांक i, n, step;

	अगर (!map_is_per_cpu(info->type))
		वापस;

	n = get_possible_cpus();
	step = round_up(info->value_size, 8);
	क्रम (i = 1; i < n; i++)
		स_नकल(value + i * step, value, info->value_size);
पूर्ण

अटल पूर्णांक parse_elem(अक्षर **argv, काष्ठा bpf_map_info *info,
		      व्योम *key, व्योम *value, __u32 key_size, __u32 value_size,
		      __u32 *flags, __u32 **value_fd)
अणु
	अगर (!*argv) अणु
		अगर (!key && !value)
			वापस 0;
		p_err("did not find %s", key ? "key" : "value");
		वापस -1;
	पूर्ण

	अगर (is_prefix(*argv, "key")) अणु
		अगर (!key) अणु
			अगर (key_size)
				p_err("duplicate key");
			अन्यथा
				p_err("unnecessary key");
			वापस -1;
		पूर्ण

		argv = parse_bytes(argv + 1, "key", key, key_size);
		अगर (!argv)
			वापस -1;

		वापस parse_elem(argv, info, शून्य, value, key_size, value_size,
				  flags, value_fd);
	पूर्ण अन्यथा अगर (is_prefix(*argv, "value")) अणु
		पूर्णांक fd;

		अगर (!value) अणु
			अगर (value_size)
				p_err("duplicate value");
			अन्यथा
				p_err("unnecessary value");
			वापस -1;
		पूर्ण

		argv++;

		अगर (map_is_map_of_maps(info->type)) अणु
			पूर्णांक argc = 2;

			अगर (value_size != 4) अणु
				p_err("value smaller than 4B for map in map?");
				वापस -1;
			पूर्ण
			अगर (!argv[0] || !argv[1]) अणु
				p_err("not enough value arguments for map in map");
				वापस -1;
			पूर्ण

			fd = map_parse_fd(&argc, &argv);
			अगर (fd < 0)
				वापस -1;

			*value_fd = value;
			**value_fd = fd;
		पूर्ण अन्यथा अगर (map_is_map_of_progs(info->type)) अणु
			पूर्णांक argc = 2;

			अगर (value_size != 4) अणु
				p_err("value smaller than 4B for map of progs?");
				वापस -1;
			पूर्ण
			अगर (!argv[0] || !argv[1]) अणु
				p_err("not enough value arguments for map of progs");
				वापस -1;
			पूर्ण
			अगर (is_prefix(*argv, "id"))
				p_info("Warning: updating program array via MAP_ID, make sure this map is kept open\n"
				       "         by some process or pinned otherwise update will be lost");

			fd = prog_parse_fd(&argc, &argv);
			अगर (fd < 0)
				वापस -1;

			*value_fd = value;
			**value_fd = fd;
		पूर्ण अन्यथा अणु
			argv = parse_bytes(argv, "value", value, value_size);
			अगर (!argv)
				वापस -1;

			fill_per_cpu_value(info, value);
		पूर्ण

		वापस parse_elem(argv, info, key, शून्य, key_size, value_size,
				  flags, शून्य);
	पूर्ण अन्यथा अगर (is_prefix(*argv, "any") || is_prefix(*argv, "noexist") ||
		   is_prefix(*argv, "exist")) अणु
		अगर (!flags) अणु
			p_err("flags specified multiple times: %s", *argv);
			वापस -1;
		पूर्ण

		अगर (is_prefix(*argv, "any"))
			*flags = BPF_ANY;
		अन्यथा अगर (is_prefix(*argv, "noexist"))
			*flags = BPF_NOEXIST;
		अन्यथा अगर (is_prefix(*argv, "exist"))
			*flags = BPF_EXIST;

		वापस parse_elem(argv + 1, info, key, value, key_size,
				  value_size, शून्य, value_fd);
	पूर्ण

	p_err("expected key or value, got: %s", *argv);
	वापस -1;
पूर्ण

अटल व्योम show_map_header_json(काष्ठा bpf_map_info *info, json_ग_लिखोr_t *wtr)
अणु
	jsonw_uपूर्णांक_field(wtr, "id", info->id);
	अगर (info->type < ARRAY_SIZE(map_type_name))
		jsonw_string_field(wtr, "type", map_type_name[info->type]);
	अन्यथा
		jsonw_uपूर्णांक_field(wtr, "type", info->type);

	अगर (*info->name)
		jsonw_string_field(wtr, "name", info->name);

	jsonw_name(wtr, "flags");
	jsonw_म_लिखो(wtr, "%d", info->map_flags);
पूर्ण

अटल पूर्णांक show_map_बंद_json(पूर्णांक fd, काष्ठा bpf_map_info *info)
अणु
	अक्षर *memlock, *frozen_str;
	पूर्णांक frozen = 0;

	memlock = get_fdinfo(fd, "memlock");
	frozen_str = get_fdinfo(fd, "frozen");

	jsonw_start_object(json_wtr);

	show_map_header_json(info, json_wtr);

	prपूर्णांक_dev_json(info->अगरindex, info->netns_dev, info->netns_ino);

	jsonw_uपूर्णांक_field(json_wtr, "bytes_key", info->key_size);
	jsonw_uपूर्णांक_field(json_wtr, "bytes_value", info->value_size);
	jsonw_uपूर्णांक_field(json_wtr, "max_entries", info->max_entries);

	अगर (memlock)
		jsonw_पूर्णांक_field(json_wtr, "bytes_memlock", म_से_प(memlock));
	मुक्त(memlock);

	अगर (info->type == BPF_MAP_TYPE_PROG_ARRAY) अणु
		अक्षर *owner_prog_type = get_fdinfo(fd, "owner_prog_type");
		अक्षर *owner_jited = get_fdinfo(fd, "owner_jited");

		अगर (owner_prog_type) अणु
			अचिन्हित पूर्णांक prog_type = म_से_प(owner_prog_type);

			अगर (prog_type < prog_type_name_size)
				jsonw_string_field(json_wtr, "owner_prog_type",
						   prog_type_name[prog_type]);
			अन्यथा
				jsonw_uपूर्णांक_field(json_wtr, "owner_prog_type",
						 prog_type);
		पूर्ण
		अगर (owner_jited)
			jsonw_bool_field(json_wtr, "owner_jited",
					 !!म_से_प(owner_jited));

		मुक्त(owner_prog_type);
		मुक्त(owner_jited);
	पूर्ण
	बंद(fd);

	अगर (frozen_str) अणु
		frozen = म_से_प(frozen_str);
		मुक्त(frozen_str);
	पूर्ण
	jsonw_पूर्णांक_field(json_wtr, "frozen", frozen);

	अगर (info->btf_id)
		jsonw_पूर्णांक_field(json_wtr, "btf_id", info->btf_id);

	अगर (!hash_empty(map_table.table)) अणु
		काष्ठा pinned_obj *obj;

		jsonw_name(json_wtr, "pinned");
		jsonw_start_array(json_wtr);
		hash_क्रम_each_possible(map_table.table, obj, hash, info->id) अणु
			अगर (obj->id == info->id)
				jsonw_string(json_wtr, obj->path);
		पूर्ण
		jsonw_end_array(json_wtr);
	पूर्ण

	emit_obj_refs_json(&refs_table, info->id, json_wtr);

	jsonw_end_object(json_wtr);

	वापस 0;
पूर्ण

अटल व्योम show_map_header_plain(काष्ठा bpf_map_info *info)
अणु
	म_लिखो("%u: ", info->id);
	अगर (info->type < ARRAY_SIZE(map_type_name))
		म_लिखो("%s  ", map_type_name[info->type]);
	अन्यथा
		म_लिखो("type %u  ", info->type);

	अगर (*info->name)
		म_लिखो("name %s  ", info->name);

	म_लिखो("flags 0x%x", info->map_flags);
	prपूर्णांक_dev_plain(info->अगरindex, info->netns_dev, info->netns_ino);
	म_लिखो("\n");
पूर्ण

अटल पूर्णांक show_map_बंद_plain(पूर्णांक fd, काष्ठा bpf_map_info *info)
अणु
	अक्षर *memlock, *frozen_str;
	पूर्णांक frozen = 0;

	memlock = get_fdinfo(fd, "memlock");
	frozen_str = get_fdinfo(fd, "frozen");

	show_map_header_plain(info);
	म_लिखो("\tkey %uB  value %uB  max_entries %u",
	       info->key_size, info->value_size, info->max_entries);

	अगर (memlock)
		म_लिखो("  memlock %sB", memlock);
	मुक्त(memlock);

	अगर (info->type == BPF_MAP_TYPE_PROG_ARRAY) अणु
		अक्षर *owner_prog_type = get_fdinfo(fd, "owner_prog_type");
		अक्षर *owner_jited = get_fdinfo(fd, "owner_jited");

		अगर (owner_prog_type || owner_jited)
			म_लिखो("\n\t");
		अगर (owner_prog_type) अणु
			अचिन्हित पूर्णांक prog_type = म_से_प(owner_prog_type);

			अगर (prog_type < prog_type_name_size)
				म_लिखो("owner_prog_type %s  ",
				       prog_type_name[prog_type]);
			अन्यथा
				म_लिखो("owner_prog_type %d  ", prog_type);
		पूर्ण
		अगर (owner_jited)
			म_लिखो("owner%s jited",
			       म_से_प(owner_jited) ? "" : " not");

		मुक्त(owner_prog_type);
		मुक्त(owner_jited);
	पूर्ण
	बंद(fd);

	अगर (!hash_empty(map_table.table)) अणु
		काष्ठा pinned_obj *obj;

		hash_क्रम_each_possible(map_table.table, obj, hash, info->id) अणु
			अगर (obj->id == info->id)
				म_लिखो("\n\tpinned %s", obj->path);
		पूर्ण
	पूर्ण
	म_लिखो("\n");

	अगर (frozen_str) अणु
		frozen = म_से_प(frozen_str);
		मुक्त(frozen_str);
	पूर्ण

	अगर (!info->btf_id && !frozen)
		वापस 0;

	म_लिखो("\t");

	अगर (info->btf_id)
		म_लिखो("btf_id %d", info->btf_id);

	अगर (frozen)
		म_लिखो("%sfrozen", info->btf_id ? "  " : "");

	emit_obj_refs_plain(&refs_table, info->id, "\n\tpids ");

	म_लिखो("\n");
	वापस 0;
पूर्ण

अटल पूर्णांक करो_show_subset(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	पूर्णांक *fds = शून्य;
	पूर्णांक nb_fds, i;
	पूर्णांक err = -1;

	fds = दो_स्मृति(माप(पूर्णांक));
	अगर (!fds) अणु
		p_err("mem alloc failed");
		वापस -1;
	पूर्ण
	nb_fds = map_parse_fds(&argc, &argv, &fds);
	अगर (nb_fds < 1)
		जाओ निकास_मुक्त;

	अगर (json_output && nb_fds > 1)
		jsonw_start_array(json_wtr);	/* root array */
	क्रम (i = 0; i < nb_fds; i++) अणु
		err = bpf_obj_get_info_by_fd(fds[i], &info, &len);
		अगर (err) अणु
			p_err("can't get map info: %s",
			      म_त्रुटि(त्रुटि_सं));
			क्रम (; i < nb_fds; i++)
				बंद(fds[i]);
			अवरोध;
		पूर्ण

		अगर (json_output)
			show_map_बंद_json(fds[i], &info);
		अन्यथा
			show_map_बंद_plain(fds[i], &info);

		बंद(fds[i]);
	पूर्ण
	अगर (json_output && nb_fds > 1)
		jsonw_end_array(json_wtr);	/* root array */

निकास_मुक्त:
	मुक्त(fds);
	वापस err;
पूर्ण

अटल पूर्णांक करो_show(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	__u32 id = 0;
	पूर्णांक err;
	पूर्णांक fd;

	अगर (show_pinned)
		build_pinned_obj_table(&map_table, BPF_OBJ_MAP);
	build_obj_refs_table(&refs_table, BPF_OBJ_MAP);

	अगर (argc == 2)
		वापस करो_show_subset(argc, argv);

	अगर (argc)
		वापस BAD_ARG();

	अगर (json_output)
		jsonw_start_array(json_wtr);
	जबतक (true) अणु
		err = bpf_map_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT)
				अवरोध;
			p_err("can't get next map: %s%s", म_त्रुटि(त्रुटि_सं),
			      त्रुटि_सं == EINVAL ? " -- kernel too old?" : "");
			अवरोध;
		पूर्ण

		fd = bpf_map_get_fd_by_id(id);
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी;
			p_err("can't get map by id (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			अवरोध;
		पूर्ण

		err = bpf_obj_get_info_by_fd(fd, &info, &len);
		अगर (err) अणु
			p_err("can't get map info: %s", म_त्रुटि(त्रुटि_सं));
			बंद(fd);
			अवरोध;
		पूर्ण

		अगर (json_output)
			show_map_बंद_json(fd, &info);
		अन्यथा
			show_map_बंद_plain(fd, &info);
	पूर्ण
	अगर (json_output)
		jsonw_end_array(json_wtr);

	delete_obj_refs_table(&refs_table);

	वापस त्रुटि_सं == ENOENT ? 0 : -1;
पूर्ण

अटल पूर्णांक dump_map_elem(पूर्णांक fd, व्योम *key, व्योम *value,
			 काष्ठा bpf_map_info *map_info, काष्ठा btf *btf,
			 json_ग_लिखोr_t *btf_wtr)
अणु
	अगर (bpf_map_lookup_elem(fd, key, value)) अणु
		prपूर्णांक_entry_error(map_info, key, त्रुटि_सं);
		वापस -1;
	पूर्ण

	अगर (json_output) अणु
		prपूर्णांक_entry_json(map_info, key, value, btf);
	पूर्ण अन्यथा अगर (btf) अणु
		काष्ठा btf_dumper d = अणु
			.btf = btf,
			.jw = btf_wtr,
			.is_plain_text = true,
		पूर्ण;

		करो_dump_btf(&d, map_info, key, value);
	पूर्ण अन्यथा अणु
		prपूर्णांक_entry_plain(map_info, key, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक maps_have_btf(पूर्णांक *fds, पूर्णांक nb_fds)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	पूर्णांक err, i;

	क्रम (i = 0; i < nb_fds; i++) अणु
		err = bpf_obj_get_info_by_fd(fds[i], &info, &len);
		अगर (err) अणु
			p_err("can't get map info: %s", म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण

		अगर (!info.btf_id)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा btf *btf_vmlinux;

अटल काष्ठा btf *get_map_kv_btf(स्थिर काष्ठा bpf_map_info *info)
अणु
	काष्ठा btf *btf = शून्य;

	अगर (info->btf_vmlinux_value_type_id) अणु
		अगर (!btf_vmlinux) अणु
			btf_vmlinux = libbpf_find_kernel_btf();
			अगर (IS_ERR(btf_vmlinux))
				p_err("failed to get kernel btf");
		पूर्ण
		वापस btf_vmlinux;
	पूर्ण अन्यथा अगर (info->btf_value_type_id) अणु
		पूर्णांक err;

		err = btf__get_from_id(info->btf_id, &btf);
		अगर (err || !btf) अणु
			p_err("failed to get btf");
			btf = err ? ERR_PTR(err) : ERR_PTR(-ESRCH);
		पूर्ण
	पूर्ण

	वापस btf;
पूर्ण

अटल व्योम मुक्त_map_kv_btf(काष्ठा btf *btf)
अणु
	अगर (!IS_ERR(btf) && btf != btf_vmlinux)
		btf__मुक्त(btf);
पूर्ण

अटल व्योम मुक्त_btf_vmlinux(व्योम)
अणु
	अगर (!IS_ERR(btf_vmlinux))
		btf__मुक्त(btf_vmlinux);
पूर्ण

अटल पूर्णांक
map_dump(पूर्णांक fd, काष्ठा bpf_map_info *info, json_ग_लिखोr_t *wtr,
	 bool show_header)
अणु
	व्योम *key, *value, *prev_key;
	अचिन्हित पूर्णांक num_elems = 0;
	काष्ठा btf *btf = शून्य;
	पूर्णांक err;

	key = दो_स्मृति(info->key_size);
	value = alloc_value(info);
	अगर (!key || !value) अणु
		p_err("mem alloc failed");
		err = -1;
		जाओ निकास_मुक्त;
	पूर्ण

	prev_key = शून्य;

	अगर (wtr) अणु
		btf = get_map_kv_btf(info);
		अगर (IS_ERR(btf)) अणु
			err = PTR_ERR(btf);
			जाओ निकास_मुक्त;
		पूर्ण

		अगर (show_header) अणु
			jsonw_start_object(wtr);	/* map object */
			show_map_header_json(info, wtr);
			jsonw_name(wtr, "elements");
		पूर्ण
		jsonw_start_array(wtr);		/* elements */
	पूर्ण अन्यथा अगर (show_header) अणु
		show_map_header_plain(info);
	पूर्ण

	अगर (info->type == BPF_MAP_TYPE_REUSEPORT_SOCKARRAY &&
	    info->value_size != 8)
		p_info("Warning: cannot read values from %s map with value_size != 8",
		       map_type_name[info->type]);
	जबतक (true) अणु
		err = bpf_map_get_next_key(fd, prev_key, key);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT)
				err = 0;
			अवरोध;
		पूर्ण
		अगर (!dump_map_elem(fd, key, value, info, btf, wtr))
			num_elems++;
		prev_key = key;
	पूर्ण

	अगर (wtr) अणु
		jsonw_end_array(wtr);	/* elements */
		अगर (show_header)
			jsonw_end_object(wtr);	/* map object */
	पूर्ण अन्यथा अणु
		म_लिखो("Found %u element%s\n", num_elems,
		       num_elems != 1 ? "s" : "");
	पूर्ण

निकास_मुक्त:
	मुक्त(key);
	मुक्त(value);
	बंद(fd);
	मुक्त_map_kv_btf(btf);

	वापस err;
पूर्ण

अटल पूर्णांक करो_dump(पूर्णांक argc, अक्षर **argv)
अणु
	json_ग_लिखोr_t *wtr = शून्य, *btf_wtr = शून्य;
	काष्ठा bpf_map_info info = अणुपूर्ण;
	पूर्णांक nb_fds, i = 0;
	__u32 len = माप(info);
	पूर्णांक *fds = शून्य;
	पूर्णांक err = -1;

	अगर (argc != 2)
		usage();

	fds = दो_स्मृति(माप(पूर्णांक));
	अगर (!fds) अणु
		p_err("mem alloc failed");
		वापस -1;
	पूर्ण
	nb_fds = map_parse_fds(&argc, &argv, &fds);
	अगर (nb_fds < 1)
		जाओ निकास_मुक्त;

	अगर (json_output) अणु
		wtr = json_wtr;
	पूर्ण अन्यथा अणु
		पूर्णांक करो_plain_btf;

		करो_plain_btf = maps_have_btf(fds, nb_fds);
		अगर (करो_plain_btf < 0)
			जाओ निकास_बंद;

		अगर (करो_plain_btf) अणु
			btf_wtr = get_btf_ग_लिखोr();
			wtr = btf_wtr;
			अगर (!btf_wtr)
				p_info("failed to create json writer for btf. falling back to plain output");
		पूर्ण
	पूर्ण

	अगर (wtr && nb_fds > 1)
		jsonw_start_array(wtr);	/* root array */
	क्रम (i = 0; i < nb_fds; i++) अणु
		अगर (bpf_obj_get_info_by_fd(fds[i], &info, &len)) अणु
			p_err("can't get map info: %s", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		पूर्ण
		err = map_dump(fds[i], &info, wtr, nb_fds > 1);
		अगर (!wtr && i != nb_fds - 1)
			म_लिखो("\n");

		अगर (err)
			अवरोध;
		बंद(fds[i]);
	पूर्ण
	अगर (wtr && nb_fds > 1)
		jsonw_end_array(wtr);	/* root array */

	अगर (btf_wtr)
		jsonw_destroy(&btf_wtr);
निकास_बंद:
	क्रम (; i < nb_fds; i++)
		बंद(fds[i]);
निकास_मुक्त:
	मुक्त(fds);
	मुक्त_btf_vmlinux();
	वापस err;
पूर्ण

अटल पूर्णांक alloc_key_value(काष्ठा bpf_map_info *info, व्योम **key, व्योम **value)
अणु
	*key = शून्य;
	*value = शून्य;

	अगर (info->key_size) अणु
		*key = दो_स्मृति(info->key_size);
		अगर (!*key) अणु
			p_err("key mem alloc failed");
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (info->value_size) अणु
		*value = alloc_value(info);
		अगर (!*value) अणु
			p_err("value mem alloc failed");
			मुक्त(*key);
			*key = शून्य;
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_update(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	__u32 *value_fd = शून्य;
	__u32 flags = BPF_ANY;
	व्योम *key, *value;
	पूर्णांक fd, err;

	अगर (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	अगर (fd < 0)
		वापस -1;

	err = alloc_key_value(&info, &key, &value);
	अगर (err)
		जाओ निकास_मुक्त;

	err = parse_elem(argv, &info, key, value, info.key_size,
			 info.value_size, &flags, &value_fd);
	अगर (err)
		जाओ निकास_मुक्त;

	err = bpf_map_update_elem(fd, key, value, flags);
	अगर (err) अणु
		p_err("update failed: %s", म_त्रुटि(त्रुटि_सं));
		जाओ निकास_मुक्त;
	पूर्ण

निकास_मुक्त:
	अगर (value_fd)
		बंद(*value_fd);
	मुक्त(key);
	मुक्त(value);
	बंद(fd);

	अगर (!err && json_output)
		jsonw_null(json_wtr);
	वापस err;
पूर्ण

अटल व्योम prपूर्णांक_key_value(काष्ठा bpf_map_info *info, व्योम *key,
			    व्योम *value)
अणु
	json_ग_लिखोr_t *btf_wtr;
	काष्ठा btf *btf = शून्य;
	पूर्णांक err;

	err = btf__get_from_id(info->btf_id, &btf);
	अगर (err) अणु
		p_err("failed to get btf");
		वापस;
	पूर्ण

	अगर (json_output) अणु
		prपूर्णांक_entry_json(info, key, value, btf);
	पूर्ण अन्यथा अगर (btf) अणु
		/* अगर here json_wtr wouldn't have been initialised,
		 * so let's create separate ग_लिखोr क्रम btf
		 */
		btf_wtr = get_btf_ग_लिखोr();
		अगर (!btf_wtr) अणु
			p_info("failed to create json writer for btf. falling back to plain output");
			btf__मुक्त(btf);
			btf = शून्य;
			prपूर्णांक_entry_plain(info, key, value);
		पूर्ण अन्यथा अणु
			काष्ठा btf_dumper d = अणु
				.btf = btf,
				.jw = btf_wtr,
				.is_plain_text = true,
			पूर्ण;

			करो_dump_btf(&d, info, key, value);
			jsonw_destroy(&btf_wtr);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांक_entry_plain(info, key, value);
	पूर्ण
	btf__मुक्त(btf);
पूर्ण

अटल पूर्णांक करो_lookup(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	व्योम *key, *value;
	पूर्णांक err;
	पूर्णांक fd;

	अगर (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	अगर (fd < 0)
		वापस -1;

	err = alloc_key_value(&info, &key, &value);
	अगर (err)
		जाओ निकास_मुक्त;

	err = parse_elem(argv, &info, key, शून्य, info.key_size, 0, शून्य, शून्य);
	अगर (err)
		जाओ निकास_मुक्त;

	err = bpf_map_lookup_elem(fd, key, value);
	अगर (err) अणु
		अगर (त्रुटि_सं == ENOENT) अणु
			अगर (json_output) अणु
				jsonw_null(json_wtr);
			पूर्ण अन्यथा अणु
				म_लिखो("key:\n");
				fprपूर्णांक_hex(मानक_निकास, key, info.key_size, " ");
				म_लिखो("\n\nNot found\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			p_err("lookup failed: %s", म_त्रुटि(त्रुटि_सं));
		पूर्ण

		जाओ निकास_मुक्त;
	पूर्ण

	/* here means bpf_map_lookup_elem() succeeded */
	prपूर्णांक_key_value(&info, key, value);

निकास_मुक्त:
	मुक्त(key);
	मुक्त(value);
	बंद(fd);

	वापस err;
पूर्ण

अटल पूर्णांक करो_getnext(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	व्योम *key, *nextkey;
	पूर्णांक err;
	पूर्णांक fd;

	अगर (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	अगर (fd < 0)
		वापस -1;

	key = दो_स्मृति(info.key_size);
	nextkey = दो_स्मृति(info.key_size);
	अगर (!key || !nextkey) अणु
		p_err("mem alloc failed");
		err = -1;
		जाओ निकास_मुक्त;
	पूर्ण

	अगर (argc) अणु
		err = parse_elem(argv, &info, key, शून्य, info.key_size, 0,
				 शून्य, शून्य);
		अगर (err)
			जाओ निकास_मुक्त;
	पूर्ण अन्यथा अणु
		मुक्त(key);
		key = शून्य;
	पूर्ण

	err = bpf_map_get_next_key(fd, key, nextkey);
	अगर (err) अणु
		p_err("can't get next key: %s", म_त्रुटि(त्रुटि_सं));
		जाओ निकास_मुक्त;
	पूर्ण

	अगर (json_output) अणु
		jsonw_start_object(json_wtr);
		अगर (key) अणु
			jsonw_name(json_wtr, "key");
			prपूर्णांक_hex_data_json(key, info.key_size);
		पूर्ण अन्यथा अणु
			jsonw_null_field(json_wtr, "key");
		पूर्ण
		jsonw_name(json_wtr, "next_key");
		prपूर्णांक_hex_data_json(nextkey, info.key_size);
		jsonw_end_object(json_wtr);
	पूर्ण अन्यथा अणु
		अगर (key) अणु
			म_लिखो("key:\n");
			fprपूर्णांक_hex(मानक_निकास, key, info.key_size, " ");
			म_लिखो("\n");
		पूर्ण अन्यथा अणु
			म_लिखो("key: None\n");
		पूर्ण
		म_लिखो("next key:\n");
		fprपूर्णांक_hex(मानक_निकास, nextkey, info.key_size, " ");
		म_लिखो("\n");
	पूर्ण

निकास_मुक्त:
	मुक्त(nextkey);
	मुक्त(key);
	बंद(fd);

	वापस err;
पूर्ण

अटल पूर्णांक करो_delete(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	व्योम *key;
	पूर्णांक err;
	पूर्णांक fd;

	अगर (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	अगर (fd < 0)
		वापस -1;

	key = दो_स्मृति(info.key_size);
	अगर (!key) अणु
		p_err("mem alloc failed");
		err = -1;
		जाओ निकास_मुक्त;
	पूर्ण

	err = parse_elem(argv, &info, key, शून्य, info.key_size, 0, शून्य, शून्य);
	अगर (err)
		जाओ निकास_मुक्त;

	err = bpf_map_delete_elem(fd, key);
	अगर (err)
		p_err("delete failed: %s", म_त्रुटि(त्रुटि_सं));

निकास_मुक्त:
	मुक्त(key);
	बंद(fd);

	अगर (!err && json_output)
		jsonw_null(json_wtr);
	वापस err;
पूर्ण

अटल पूर्णांक करो_pin(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक err;

	err = करो_pin_any(argc, argv, map_parse_fd);
	अगर (!err && json_output)
		jsonw_null(json_wtr);
	वापस err;
पूर्ण

अटल पूर्णांक करो_create(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_create_map_attr attr = अणु शून्य, पूर्ण;
	स्थिर अक्षर *pinfile;
	पूर्णांक err = -1, fd;

	अगर (!REQ_ARGS(7))
		वापस -1;
	pinfile = GET_ARG();

	जबतक (argc) अणु
		अगर (!REQ_ARGS(2))
			वापस -1;

		अगर (is_prefix(*argv, "type")) अणु
			NEXT_ARG();

			अगर (attr.map_type) अणु
				p_err("map type already specified");
				जाओ निकास;
			पूर्ण

			attr.map_type = map_type_from_str(*argv);
			अगर ((पूर्णांक)attr.map_type < 0) अणु
				p_err("unrecognized map type: %s", *argv);
				जाओ निकास;
			पूर्ण
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "name")) अणु
			NEXT_ARG();
			attr.name = GET_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "key")) अणु
			अगर (parse_u32_arg(&argc, &argv, &attr.key_size,
					  "key size"))
				जाओ निकास;
		पूर्ण अन्यथा अगर (is_prefix(*argv, "value")) अणु
			अगर (parse_u32_arg(&argc, &argv, &attr.value_size,
					  "value size"))
				जाओ निकास;
		पूर्ण अन्यथा अगर (is_prefix(*argv, "entries")) अणु
			अगर (parse_u32_arg(&argc, &argv, &attr.max_entries,
					  "max entries"))
				जाओ निकास;
		पूर्ण अन्यथा अगर (is_prefix(*argv, "flags")) अणु
			अगर (parse_u32_arg(&argc, &argv, &attr.map_flags,
					  "flags"))
				जाओ निकास;
		पूर्ण अन्यथा अगर (is_prefix(*argv, "dev")) अणु
			NEXT_ARG();

			अगर (attr.map_अगरindex) अणु
				p_err("offload device already specified");
				जाओ निकास;
			पूर्ण

			attr.map_अगरindex = अगर_nametoindex(*argv);
			अगर (!attr.map_अगरindex) अणु
				p_err("unrecognized netdevice '%s': %s",
				      *argv, म_त्रुटि(त्रुटि_सं));
				जाओ निकास;
			पूर्ण
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "inner_map")) अणु
			काष्ठा bpf_map_info info = अणुपूर्ण;
			__u32 len = माप(info);
			पूर्णांक inner_map_fd;

			NEXT_ARG();
			अगर (!REQ_ARGS(2))
				usage();
			inner_map_fd = map_parse_fd_and_info(&argc, &argv,
							     &info, &len);
			अगर (inner_map_fd < 0)
				वापस -1;
			attr.inner_map_fd = inner_map_fd;
		पूर्ण अन्यथा अणु
			p_err("unknown arg %s", *argv);
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (!attr.name) अणु
		p_err("map name not specified");
		जाओ निकास;
	पूर्ण

	set_max_rlimit();

	fd = bpf_create_map_xattr(&attr);
	अगर (fd < 0) अणु
		p_err("map create failed: %s", म_त्रुटि(त्रुटि_सं));
		जाओ निकास;
	पूर्ण

	err = करो_pin_fd(fd, pinfile);
	बंद(fd);
	अगर (err)
		जाओ निकास;

	अगर (json_output)
		jsonw_null(json_wtr);

निकास:
	अगर (attr.inner_map_fd > 0)
		बंद(attr.inner_map_fd);

	वापस err;
पूर्ण

अटल पूर्णांक करो_pop_dequeue(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	__u32 len = माप(info);
	व्योम *key, *value;
	पूर्णांक err;
	पूर्णांक fd;

	अगर (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	अगर (fd < 0)
		वापस -1;

	err = alloc_key_value(&info, &key, &value);
	अगर (err)
		जाओ निकास_मुक्त;

	err = bpf_map_lookup_and_delete_elem(fd, key, value);
	अगर (err) अणु
		अगर (त्रुटि_सं == ENOENT) अणु
			अगर (json_output)
				jsonw_null(json_wtr);
			अन्यथा
				म_लिखो("Error: empty map\n");
		पूर्ण अन्यथा अणु
			p_err("pop failed: %s", म_त्रुटि(त्रुटि_सं));
		पूर्ण

		जाओ निकास_मुक्त;
	पूर्ण

	prपूर्णांक_key_value(&info, key, value);

निकास_मुक्त:
	मुक्त(key);
	मुक्त(value);
	बंद(fd);

	वापस err;
पूर्ण

अटल पूर्णांक करो_मुक्तze(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक err, fd;

	अगर (!REQ_ARGS(2))
		वापस -1;

	fd = map_parse_fd(&argc, &argv);
	अगर (fd < 0)
		वापस -1;

	अगर (argc) अणु
		बंद(fd);
		वापस BAD_ARG();
	पूर्ण

	err = bpf_map_मुक्तze(fd);
	बंद(fd);
	अगर (err) अणु
		p_err("failed to freeze map: %s", म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s { show | list }   [MAP]\n"
		"       %1$s %2$s create     FILE type TYPE key KEY_SIZE value VALUE_SIZE \\\n"
		"                                  entries MAX_ENTRIES name NAME [flags FLAGS] \\\n"
		"                                  [inner_map MAP] [dev NAME]\n"
		"       %1$s %2$s dump       MAP\n"
		"       %1$s %2$s update     MAP [key DATA] [value VALUE] [UPDATE_FLAGS]\n"
		"       %1$s %2$s lookup     MAP [key DATA]\n"
		"       %1$s %2$s getnext    MAP [key DATA]\n"
		"       %1$s %2$s delete     MAP  key DATA\n"
		"       %1$s %2$s pin        MAP  FILE\n"
		"       %1$s %2$s event_pipe MAP [cpu N index M]\n"
		"       %1$s %2$s peek       MAP\n"
		"       %1$s %2$s push       MAP value VALUE\n"
		"       %1$s %2$s pop        MAP\n"
		"       %1$s %2$s enqueue    MAP value VALUE\n"
		"       %1$s %2$s dequeue    MAP\n"
		"       %1$s %2$s freeze     MAP\n"
		"       %1$s %2$s help\n"
		"\n"
		"       " HELP_SPEC_MAP "\n"
		"       DATA := { [hex] BYTES }\n"
		"       " HELP_SPEC_PROGRAM "\n"
		"       VALUE := { DATA | MAP | PROG }\n"
		"       UPDATE_FLAGS := { any | exist | noexist }\n"
		"       TYPE := { hash | array | prog_array | perf_event_array | percpu_hash |\n"
		"                 percpu_array | stack_trace | cgroup_array | lru_hash |\n"
		"                 lru_percpu_hash | lpm_trie | array_of_maps | hash_of_maps |\n"
		"                 devmap | devmap_hash | sockmap | cpumap | xskmap | sockhash |\n"
		"                 cgroup_storage | reuseport_sockarray | percpu_cgroup_storage |\n"
		"                 queue | stack | sk_storage | struct_ops | ringbuf | inode_storage |\n"
		"		  task_storage }\n"
		"       " HELP_SPEC_OPTIONS "\n"
		"",
		bin_name, argv[-2]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "show",	करो_show पूर्ण,
	अणु "list",	करो_show पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु "dump",	करो_dump पूर्ण,
	अणु "update",	करो_update पूर्ण,
	अणु "lookup",	करो_lookup पूर्ण,
	अणु "getnext",	करो_getnext पूर्ण,
	अणु "delete",	करो_delete पूर्ण,
	अणु "pin",	करो_pin पूर्ण,
	अणु "event_pipe",	करो_event_pipe पूर्ण,
	अणु "create",	करो_create पूर्ण,
	अणु "peek",	करो_lookup पूर्ण,
	अणु "push",	करो_update पूर्ण,
	अणु "enqueue",	करो_update पूर्ण,
	अणु "pop",	करो_pop_dequeue पूर्ण,
	अणु "dequeue",	करो_pop_dequeue पूर्ण,
	अणु "freeze",	करो_मुक्तze पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_map(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
