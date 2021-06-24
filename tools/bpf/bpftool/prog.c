<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <net/अगर.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>

#समावेश <linux/err.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/sizes.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/btf.h>
#समावेश <bpf/libbpf.h>

#समावेश "cfg.h"
#समावेश "main.h"
#समावेश "xlated_dumper.h"

#घोषणा BPF_METADATA_PREFIX "bpf_metadata_"
#घोषणा BPF_METADATA_PREFIX_LEN (माप(BPF_METADATA_PREFIX) - 1)

स्थिर अक्षर * स्थिर prog_type_name[] = अणु
	[BPF_PROG_TYPE_UNSPEC]			= "unspec",
	[BPF_PROG_TYPE_SOCKET_FILTER]		= "socket_filter",
	[BPF_PROG_TYPE_KPROBE]			= "kprobe",
	[BPF_PROG_TYPE_SCHED_CLS]		= "sched_cls",
	[BPF_PROG_TYPE_SCHED_ACT]		= "sched_act",
	[BPF_PROG_TYPE_TRACEPOINT]		= "tracepoint",
	[BPF_PROG_TYPE_XDP]			= "xdp",
	[BPF_PROG_TYPE_PERF_EVENT]		= "perf_event",
	[BPF_PROG_TYPE_CGROUP_SKB]		= "cgroup_skb",
	[BPF_PROG_TYPE_CGROUP_SOCK]		= "cgroup_sock",
	[BPF_PROG_TYPE_LWT_IN]			= "lwt_in",
	[BPF_PROG_TYPE_LWT_OUT]			= "lwt_out",
	[BPF_PROG_TYPE_LWT_XMIT]		= "lwt_xmit",
	[BPF_PROG_TYPE_SOCK_OPS]		= "sock_ops",
	[BPF_PROG_TYPE_SK_SKB]			= "sk_skb",
	[BPF_PROG_TYPE_CGROUP_DEVICE]		= "cgroup_device",
	[BPF_PROG_TYPE_SK_MSG]			= "sk_msg",
	[BPF_PROG_TYPE_RAW_TRACEPOINT]		= "raw_tracepoint",
	[BPF_PROG_TYPE_CGROUP_SOCK_ADDR]	= "cgroup_sock_addr",
	[BPF_PROG_TYPE_LWT_SEG6LOCAL]		= "lwt_seg6local",
	[BPF_PROG_TYPE_LIRC_MODE2]		= "lirc_mode2",
	[BPF_PROG_TYPE_SK_REUSEPORT]		= "sk_reuseport",
	[BPF_PROG_TYPE_FLOW_DISSECTOR]		= "flow_dissector",
	[BPF_PROG_TYPE_CGROUP_SYSCTL]		= "cgroup_sysctl",
	[BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE]	= "raw_tracepoint_writable",
	[BPF_PROG_TYPE_CGROUP_SOCKOPT]		= "cgroup_sockopt",
	[BPF_PROG_TYPE_TRACING]			= "tracing",
	[BPF_PROG_TYPE_STRUCT_OPS]		= "struct_ops",
	[BPF_PROG_TYPE_EXT]			= "ext",
	[BPF_PROG_TYPE_LSM]			= "lsm",
	[BPF_PROG_TYPE_SK_LOOKUP]		= "sk_lookup",
पूर्ण;

स्थिर माप_प्रकार prog_type_name_size = ARRAY_SIZE(prog_type_name);

क्रमागत dump_mode अणु
	DUMP_JITED,
	DUMP_XLATED,
पूर्ण;

अटल स्थिर अक्षर * स्थिर attach_type_strings[] = अणु
	[BPF_SK_SKB_STREAM_PARSER] = "stream_parser",
	[BPF_SK_SKB_STREAM_VERDICT] = "stream_verdict",
	[BPF_SK_SKB_VERDICT] = "skb_verdict",
	[BPF_SK_MSG_VERDICT] = "msg_verdict",
	[BPF_FLOW_DISSECTOR] = "flow_dissector",
	[__MAX_BPF_ATTACH_TYPE] = शून्य,
पूर्ण;

अटल क्रमागत bpf_attach_type parse_attach_type(स्थिर अक्षर *str)
अणु
	क्रमागत bpf_attach_type type;

	क्रम (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) अणु
		अगर (attach_type_strings[type] &&
		    is_prefix(str, attach_type_strings[type]))
			वापस type;
	पूर्ण

	वापस __MAX_BPF_ATTACH_TYPE;
पूर्ण

अटल व्योम prपूर्णांक_boot_समय(__u64 nsecs, अक्षर *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा बारpec real_समय_प्रकारs, boot_समय_प्रकारs;
	समय_प्रकार wallघड़ी_secs;
	काष्ठा पंचांग load_पंचांग;

	buf[--size] = '\0';

	अगर (घड़ी_समय_लो(CLOCK_REALTIME, &real_समय_प्रकारs) ||
	    घड़ी_समय_लो(CLOCK_BOOTTIME, &boot_समय_प्रकारs)) अणु
		लिखो_त्रुटि("Can't read clocks");
		snम_लिखो(buf, size, "%llu", nsecs / 1000000000);
		वापस;
	पूर्ण

	wallघड़ी_secs = (real_समय_प्रकारs.tv_sec - boot_समय_प्रकारs.tv_sec) +
		(real_समय_प्रकारs.tv_nsec - boot_समय_प्रकारs.tv_nsec + nsecs) /
		1000000000;


	अगर (!स_स्थानीय_r(&wallघड़ी_secs, &load_पंचांग)) अणु
		snम_लिखो(buf, size, "%llu", nsecs / 1000000000);
		वापस;
	पूर्ण

	अगर (json_output)
		स_माला(buf, size, "%s", &load_पंचांग);
	अन्यथा
		स_माला(buf, size, "%FT%T%z", &load_पंचांग);
पूर्ण

अटल व्योम show_prog_maps(पूर्णांक fd, __u32 num_maps)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 len = माप(info);
	__u32 map_ids[num_maps];
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	info.nr_map_ids = num_maps;
	info.map_ids = ptr_to_u64(map_ids);

	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	अगर (err || !info.nr_map_ids)
		वापस;

	अगर (json_output) अणु
		jsonw_name(json_wtr, "map_ids");
		jsonw_start_array(json_wtr);
		क्रम (i = 0; i < info.nr_map_ids; i++)
			jsonw_uपूर्णांक(json_wtr, map_ids[i]);
		jsonw_end_array(json_wtr);
	पूर्ण अन्यथा अणु
		म_लिखो("  map_ids ");
		क्रम (i = 0; i < info.nr_map_ids; i++)
			म_लिखो("%u%s", map_ids[i],
			       i == info.nr_map_ids - 1 ? "" : ",");
	पूर्ण
पूर्ण

अटल व्योम *find_metadata(पूर्णांक prog_fd, काष्ठा bpf_map_info *map_info)
अणु
	काष्ठा bpf_prog_info prog_info;
	__u32 prog_info_len;
	__u32 map_info_len;
	व्योम *value = शून्य;
	__u32 *map_ids;
	पूर्णांक nr_maps;
	पूर्णांक key = 0;
	पूर्णांक map_fd;
	पूर्णांक ret;
	__u32 i;

	स_रखो(&prog_info, 0, माप(prog_info));
	prog_info_len = माप(prog_info);
	ret = bpf_obj_get_info_by_fd(prog_fd, &prog_info, &prog_info_len);
	अगर (ret)
		वापस शून्य;

	अगर (!prog_info.nr_map_ids)
		वापस शून्य;

	map_ids = सुस्मृति(prog_info.nr_map_ids, माप(__u32));
	अगर (!map_ids)
		वापस शून्य;

	nr_maps = prog_info.nr_map_ids;
	स_रखो(&prog_info, 0, माप(prog_info));
	prog_info.nr_map_ids = nr_maps;
	prog_info.map_ids = ptr_to_u64(map_ids);
	prog_info_len = माप(prog_info);

	ret = bpf_obj_get_info_by_fd(prog_fd, &prog_info, &prog_info_len);
	अगर (ret)
		जाओ मुक्त_map_ids;

	क्रम (i = 0; i < prog_info.nr_map_ids; i++) अणु
		map_fd = bpf_map_get_fd_by_id(map_ids[i]);
		अगर (map_fd < 0)
			जाओ मुक्त_map_ids;

		स_रखो(map_info, 0, माप(*map_info));
		map_info_len = माप(*map_info);
		ret = bpf_obj_get_info_by_fd(map_fd, map_info, &map_info_len);
		अगर (ret < 0) अणु
			बंद(map_fd);
			जाओ मुक्त_map_ids;
		पूर्ण

		अगर (map_info->type != BPF_MAP_TYPE_ARRAY ||
		    map_info->key_size != माप(पूर्णांक) ||
		    map_info->max_entries != 1 ||
		    !map_info->btf_value_type_id ||
		    !म_माला(map_info->name, ".rodata")) अणु
			बंद(map_fd);
			जारी;
		पूर्ण

		value = दो_स्मृति(map_info->value_size);
		अगर (!value) अणु
			बंद(map_fd);
			जाओ मुक्त_map_ids;
		पूर्ण

		अगर (bpf_map_lookup_elem(map_fd, &key, value)) अणु
			बंद(map_fd);
			मुक्त(value);
			value = शून्य;
			जाओ मुक्त_map_ids;
		पूर्ण

		बंद(map_fd);
		अवरोध;
	पूर्ण

मुक्त_map_ids:
	मुक्त(map_ids);
	वापस value;
पूर्ण

अटल bool has_metadata_prefix(स्थिर अक्षर *s)
अणु
	वापस म_भेदन(s, BPF_METADATA_PREFIX, BPF_METADATA_PREFIX_LEN) == 0;
पूर्ण

अटल व्योम show_prog_metadata(पूर्णांक fd, __u32 num_maps)
अणु
	स्थिर काष्ठा btf_type *t_datasec, *t_var;
	काष्ठा bpf_map_info map_info;
	काष्ठा btf_var_secinfo *vsi;
	bool prपूर्णांकed_header = false;
	काष्ठा btf *btf = शून्य;
	अचिन्हित पूर्णांक i, vlen;
	व्योम *value = शून्य;
	स्थिर अक्षर *name;
	पूर्णांक err;

	अगर (!num_maps)
		वापस;

	स_रखो(&map_info, 0, माप(map_info));
	value = find_metadata(fd, &map_info);
	अगर (!value)
		वापस;

	err = btf__get_from_id(map_info.btf_id, &btf);
	अगर (err || !btf)
		जाओ out_मुक्त;

	t_datasec = btf__type_by_id(btf, map_info.btf_value_type_id);
	अगर (!btf_is_datasec(t_datasec))
		जाओ out_मुक्त;

	vlen = btf_vlen(t_datasec);
	vsi = btf_var_secinfos(t_datasec);

	/* We करोn't proceed to check the kinds of the elements of the DATASEC.
	 * The verअगरier enक्रमces them to be BTF_KIND_VAR.
	 */

	अगर (json_output) अणु
		काष्ठा btf_dumper d = अणु
			.btf = btf,
			.jw = json_wtr,
			.is_plain_text = false,
		पूर्ण;

		क्रम (i = 0; i < vlen; i++, vsi++) अणु
			t_var = btf__type_by_id(btf, vsi->type);
			name = btf__name_by_offset(btf, t_var->name_off);

			अगर (!has_metadata_prefix(name))
				जारी;

			अगर (!prपूर्णांकed_header) अणु
				jsonw_name(json_wtr, "metadata");
				jsonw_start_object(json_wtr);
				prपूर्णांकed_header = true;
			पूर्ण

			jsonw_name(json_wtr, name + BPF_METADATA_PREFIX_LEN);
			err = btf_dumper_type(&d, t_var->type, value + vsi->offset);
			अगर (err) अणु
				p_err("btf dump failed: %d", err);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (prपूर्णांकed_header)
			jsonw_end_object(json_wtr);
	पूर्ण अन्यथा अणु
		json_ग_लिखोr_t *btf_wtr = jsonw_new(मानक_निकास);
		काष्ठा btf_dumper d = अणु
			.btf = btf,
			.jw = btf_wtr,
			.is_plain_text = true,
		पूर्ण;

		अगर (!btf_wtr) अणु
			p_err("jsonw alloc failed");
			जाओ out_मुक्त;
		पूर्ण

		क्रम (i = 0; i < vlen; i++, vsi++) अणु
			t_var = btf__type_by_id(btf, vsi->type);
			name = btf__name_by_offset(btf, t_var->name_off);

			अगर (!has_metadata_prefix(name))
				जारी;

			अगर (!prपूर्णांकed_header) अणु
				म_लिखो("\tmetadata:");
				prपूर्णांकed_header = true;
			पूर्ण

			म_लिखो("\n\t\t%s = ", name + BPF_METADATA_PREFIX_LEN);

			jsonw_reset(btf_wtr);
			err = btf_dumper_type(&d, t_var->type, value + vsi->offset);
			अगर (err) अणु
				p_err("btf dump failed: %d", err);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (prपूर्णांकed_header)
			jsonw_destroy(&btf_wtr);
	पूर्ण

out_मुक्त:
	btf__मुक्त(btf);
	मुक्त(value);
पूर्ण

अटल व्योम prपूर्णांक_prog_header_json(काष्ठा bpf_prog_info *info)
अणु
	jsonw_uपूर्णांक_field(json_wtr, "id", info->id);
	अगर (info->type < ARRAY_SIZE(prog_type_name))
		jsonw_string_field(json_wtr, "type",
				   prog_type_name[info->type]);
	अन्यथा
		jsonw_uपूर्णांक_field(json_wtr, "type", info->type);

	अगर (*info->name)
		jsonw_string_field(json_wtr, "name", info->name);

	jsonw_name(json_wtr, "tag");
	jsonw_म_लिखो(json_wtr, "\"" BPF_TAG_FMT "\"",
		     info->tag[0], info->tag[1], info->tag[2], info->tag[3],
		     info->tag[4], info->tag[5], info->tag[6], info->tag[7]);

	jsonw_bool_field(json_wtr, "gpl_compatible", info->gpl_compatible);
	अगर (info->run_समय_ns) अणु
		jsonw_uपूर्णांक_field(json_wtr, "run_time_ns", info->run_समय_ns);
		jsonw_uपूर्णांक_field(json_wtr, "run_cnt", info->run_cnt);
	पूर्ण
	अगर (info->recursion_misses)
		jsonw_uपूर्णांक_field(json_wtr, "recursion_misses", info->recursion_misses);
पूर्ण

अटल व्योम prपूर्णांक_prog_json(काष्ठा bpf_prog_info *info, पूर्णांक fd)
अणु
	अक्षर *memlock;

	jsonw_start_object(json_wtr);
	prपूर्णांक_prog_header_json(info);
	prपूर्णांक_dev_json(info->अगरindex, info->netns_dev, info->netns_ino);

	अगर (info->load_समय) अणु
		अक्षर buf[32];

		prपूर्णांक_boot_समय(info->load_समय, buf, माप(buf));

		/* Piggy back on load_समय, since 0 uid is a valid one */
		jsonw_name(json_wtr, "loaded_at");
		jsonw_म_लिखो(json_wtr, "%s", buf);
		jsonw_uपूर्णांक_field(json_wtr, "uid", info->created_by_uid);
	पूर्ण

	jsonw_uपूर्णांक_field(json_wtr, "bytes_xlated", info->xlated_prog_len);

	अगर (info->jited_prog_len) अणु
		jsonw_bool_field(json_wtr, "jited", true);
		jsonw_uपूर्णांक_field(json_wtr, "bytes_jited", info->jited_prog_len);
	पूर्ण अन्यथा अणु
		jsonw_bool_field(json_wtr, "jited", false);
	पूर्ण

	memlock = get_fdinfo(fd, "memlock");
	अगर (memlock)
		jsonw_पूर्णांक_field(json_wtr, "bytes_memlock", म_से_प(memlock));
	मुक्त(memlock);

	अगर (info->nr_map_ids)
		show_prog_maps(fd, info->nr_map_ids);

	अगर (info->btf_id)
		jsonw_पूर्णांक_field(json_wtr, "btf_id", info->btf_id);

	अगर (!hash_empty(prog_table.table)) अणु
		काष्ठा pinned_obj *obj;

		jsonw_name(json_wtr, "pinned");
		jsonw_start_array(json_wtr);
		hash_क्रम_each_possible(prog_table.table, obj, hash, info->id) अणु
			अगर (obj->id == info->id)
				jsonw_string(json_wtr, obj->path);
		पूर्ण
		jsonw_end_array(json_wtr);
	पूर्ण

	emit_obj_refs_json(&refs_table, info->id, json_wtr);

	show_prog_metadata(fd, info->nr_map_ids);

	jsonw_end_object(json_wtr);
पूर्ण

अटल व्योम prपूर्णांक_prog_header_plain(काष्ठा bpf_prog_info *info)
अणु
	म_लिखो("%u: ", info->id);
	अगर (info->type < ARRAY_SIZE(prog_type_name))
		म_लिखो("%s  ", prog_type_name[info->type]);
	अन्यथा
		म_लिखो("type %u  ", info->type);

	अगर (*info->name)
		म_लिखो("name %s  ", info->name);

	म_लिखो("tag ");
	fprपूर्णांक_hex(मानक_निकास, info->tag, BPF_TAG_SIZE, "");
	prपूर्णांक_dev_plain(info->अगरindex, info->netns_dev, info->netns_ino);
	म_लिखो("%s", info->gpl_compatible ? "  gpl" : "");
	अगर (info->run_समय_ns)
		म_लिखो(" run_time_ns %lld run_cnt %lld",
		       info->run_समय_ns, info->run_cnt);
	अगर (info->recursion_misses)
		म_लिखो(" recursion_misses %lld", info->recursion_misses);
	म_लिखो("\n");
पूर्ण

अटल व्योम prपूर्णांक_prog_plain(काष्ठा bpf_prog_info *info, पूर्णांक fd)
अणु
	अक्षर *memlock;

	prपूर्णांक_prog_header_plain(info);

	अगर (info->load_समय) अणु
		अक्षर buf[32];

		prपूर्णांक_boot_समय(info->load_समय, buf, माप(buf));

		/* Piggy back on load_समय, since 0 uid is a valid one */
		म_लिखो("\tloaded_at %s  uid %u\n", buf, info->created_by_uid);
	पूर्ण

	म_लिखो("\txlated %uB", info->xlated_prog_len);

	अगर (info->jited_prog_len)
		म_लिखो("  jited %uB", info->jited_prog_len);
	अन्यथा
		म_लिखो("  not jited");

	memlock = get_fdinfo(fd, "memlock");
	अगर (memlock)
		म_लिखो("  memlock %sB", memlock);
	मुक्त(memlock);

	अगर (info->nr_map_ids)
		show_prog_maps(fd, info->nr_map_ids);

	अगर (!hash_empty(prog_table.table)) अणु
		काष्ठा pinned_obj *obj;

		hash_क्रम_each_possible(prog_table.table, obj, hash, info->id) अणु
			अगर (obj->id == info->id)
				म_लिखो("\n\tpinned %s", obj->path);
		पूर्ण
	पूर्ण

	अगर (info->btf_id)
		म_लिखो("\n\tbtf_id %d", info->btf_id);

	emit_obj_refs_plain(&refs_table, info->id, "\n\tpids ");

	म_लिखो("\n");

	show_prog_metadata(fd, info->nr_map_ids);
पूर्ण

अटल पूर्णांक show_prog(पूर्णांक fd)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 len = माप(info);
	पूर्णांक err;

	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	अगर (err) अणु
		p_err("can't get prog info: %s", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	अगर (json_output)
		prपूर्णांक_prog_json(&info, fd);
	अन्यथा
		prपूर्णांक_prog_plain(&info, fd);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_show_subset(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक *fds = शून्य;
	पूर्णांक nb_fds, i;
	पूर्णांक err = -1;

	fds = दो_स्मृति(माप(पूर्णांक));
	अगर (!fds) अणु
		p_err("mem alloc failed");
		वापस -1;
	पूर्ण
	nb_fds = prog_parse_fds(&argc, &argv, &fds);
	अगर (nb_fds < 1)
		जाओ निकास_मुक्त;

	अगर (json_output && nb_fds > 1)
		jsonw_start_array(json_wtr);	/* root array */
	क्रम (i = 0; i < nb_fds; i++) अणु
		err = show_prog(fds[i]);
		अगर (err) अणु
			क्रम (; i < nb_fds; i++)
				बंद(fds[i]);
			अवरोध;
		पूर्ण
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
	__u32 id = 0;
	पूर्णांक err;
	पूर्णांक fd;

	अगर (show_pinned)
		build_pinned_obj_table(&prog_table, BPF_OBJ_PROG);
	build_obj_refs_table(&refs_table, BPF_OBJ_PROG);

	अगर (argc == 2)
		वापस करो_show_subset(argc, argv);

	अगर (argc)
		वापस BAD_ARG();

	अगर (json_output)
		jsonw_start_array(json_wtr);
	जबतक (true) अणु
		err = bpf_prog_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT) अणु
				err = 0;
				अवरोध;
			पूर्ण
			p_err("can't get next program: %s%s", म_त्रुटि(त्रुटि_सं),
			      त्रुटि_सं == EINVAL ? " -- kernel too old?" : "");
			err = -1;
			अवरोध;
		पूर्ण

		fd = bpf_prog_get_fd_by_id(id);
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी;
			p_err("can't get prog by id (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			err = -1;
			अवरोध;
		पूर्ण

		err = show_prog(fd);
		बंद(fd);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (json_output)
		jsonw_end_array(json_wtr);

	delete_obj_refs_table(&refs_table);

	वापस err;
पूर्ण

अटल पूर्णांक
prog_dump(काष्ठा bpf_prog_info *info, क्रमागत dump_mode mode,
	  अक्षर *filepath, bool opcodes, bool visual, bool linum)
अणु
	काष्ठा bpf_prog_linfo *prog_linfo = शून्य;
	स्थिर अक्षर *disयंत्र_opt = शून्य;
	काष्ठा dump_data dd = अणुपूर्ण;
	व्योम *func_info = शून्य;
	काष्ठा btf *btf = शून्य;
	अक्षर func_sig[1024];
	अचिन्हित अक्षर *buf;
	__u32 member_len;
	sमाप_प्रकार n;
	पूर्णांक fd;

	अगर (mode == DUMP_JITED) अणु
		अगर (info->jited_prog_len == 0 || !info->jited_prog_insns) अणु
			p_info("no instructions returned");
			वापस -1;
		पूर्ण
		buf = u64_to_ptr(info->jited_prog_insns);
		member_len = info->jited_prog_len;
	पूर्ण अन्यथा अणु	/* DUMP_XLATED */
		अगर (info->xlated_prog_len == 0 || !info->xlated_prog_insns) अणु
			p_err("error retrieving insn dump: kernel.kptr_restrict set?");
			वापस -1;
		पूर्ण
		buf = u64_to_ptr(info->xlated_prog_insns);
		member_len = info->xlated_prog_len;
	पूर्ण

	अगर (info->btf_id && btf__get_from_id(info->btf_id, &btf)) अणु
		p_err("failed to get btf");
		वापस -1;
	पूर्ण

	func_info = u64_to_ptr(info->func_info);

	अगर (info->nr_line_info) अणु
		prog_linfo = bpf_prog_linfo__new(info);
		अगर (!prog_linfo)
			p_info("error in processing bpf_line_info.  continue without it.");
	पूर्ण

	अगर (filepath) अणु
		fd = खोलो(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		अगर (fd < 0) अणु
			p_err("can't open file %s: %s", filepath,
			      म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण

		n = ग_लिखो(fd, buf, member_len);
		बंद(fd);
		अगर (n != (sमाप_प्रकार)member_len) अणु
			p_err("error writing output file: %s",
			      n < 0 ? म_त्रुटि(त्रुटि_सं) : "short write");
			वापस -1;
		पूर्ण

		अगर (json_output)
			jsonw_null(json_wtr);
	पूर्ण अन्यथा अगर (mode == DUMP_JITED) अणु
		स्थिर अक्षर *name = शून्य;

		अगर (info->अगरindex) अणु
			name = अगरindex_to_bfd_params(info->अगरindex,
						     info->netns_dev,
						     info->netns_ino,
						     &disयंत्र_opt);
			अगर (!name)
				वापस -1;
		पूर्ण

		अगर (info->nr_jited_func_lens && info->jited_func_lens) अणु
			काष्ठा kernel_sym *sym = शून्य;
			काष्ठा bpf_func_info *record;
			अक्षर sym_name[SYM_MAX_NAME];
			अचिन्हित अक्षर *img = buf;
			__u64 *ksyms = शून्य;
			__u32 *lens;
			__u32 i;
			अगर (info->nr_jited_ksyms) अणु
				kernel_syms_load(&dd);
				ksyms = u64_to_ptr(info->jited_ksyms);
			पूर्ण

			अगर (json_output)
				jsonw_start_array(json_wtr);

			lens = u64_to_ptr(info->jited_func_lens);
			क्रम (i = 0; i < info->nr_jited_func_lens; i++) अणु
				अगर (ksyms) अणु
					sym = kernel_syms_search(&dd, ksyms[i]);
					अगर (sym)
						प्र_लिखो(sym_name, "%s", sym->name);
					अन्यथा
						प्र_लिखो(sym_name, "0x%016llx", ksyms[i]);
				पूर्ण अन्यथा अणु
					म_नकल(sym_name, "unknown");
				पूर्ण

				अगर (func_info) अणु
					record = func_info + i * info->func_info_rec_size;
					btf_dumper_type_only(btf, record->type_id,
							     func_sig,
							     माप(func_sig));
				पूर्ण

				अगर (json_output) अणु
					jsonw_start_object(json_wtr);
					अगर (func_info && func_sig[0] != '\0') अणु
						jsonw_name(json_wtr, "proto");
						jsonw_string(json_wtr, func_sig);
					पूर्ण
					jsonw_name(json_wtr, "name");
					jsonw_string(json_wtr, sym_name);
					jsonw_name(json_wtr, "insns");
				पूर्ण अन्यथा अणु
					अगर (func_info && func_sig[0] != '\0')
						म_लिखो("%s:\n", func_sig);
					म_लिखो("%s:\n", sym_name);
				पूर्ण

				disयंत्र_prपूर्णांक_insn(img, lens[i], opcodes,
						  name, disयंत्र_opt, btf,
						  prog_linfo, ksyms[i], i,
						  linum);

				img += lens[i];

				अगर (json_output)
					jsonw_end_object(json_wtr);
				अन्यथा
					म_लिखो("\n");
			पूर्ण

			अगर (json_output)
				jsonw_end_array(json_wtr);
		पूर्ण अन्यथा अणु
			disयंत्र_prपूर्णांक_insn(buf, member_len, opcodes, name,
					  disयंत्र_opt, btf, शून्य, 0, 0, false);
		पूर्ण
	पूर्ण अन्यथा अगर (visual) अणु
		अगर (json_output)
			jsonw_null(json_wtr);
		अन्यथा
			dump_xlated_cfg(buf, member_len);
	पूर्ण अन्यथा अणु
		kernel_syms_load(&dd);
		dd.nr_jited_ksyms = info->nr_jited_ksyms;
		dd.jited_ksyms = u64_to_ptr(info->jited_ksyms);
		dd.btf = btf;
		dd.func_info = func_info;
		dd.finfo_rec_size = info->func_info_rec_size;
		dd.prog_linfo = prog_linfo;

		अगर (json_output)
			dump_xlated_json(&dd, buf, member_len, opcodes,
					 linum);
		अन्यथा
			dump_xlated_plain(&dd, buf, member_len, opcodes,
					  linum);
		kernel_syms_destroy(&dd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_dump(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	अक्षर *filepath = शून्य;
	bool opcodes = false;
	bool visual = false;
	क्रमागत dump_mode mode;
	bool linum = false;
	पूर्णांक *fds = शून्य;
	पूर्णांक nb_fds, i = 0;
	पूर्णांक err = -1;
	__u64 arrays;

	अगर (is_prefix(*argv, "jited")) अणु
		अगर (disयंत्र_init())
			वापस -1;
		mode = DUMP_JITED;
	पूर्ण अन्यथा अगर (is_prefix(*argv, "xlated")) अणु
		mode = DUMP_XLATED;
	पूर्ण अन्यथा अणु
		p_err("expected 'xlated' or 'jited', got: %s", *argv);
		वापस -1;
	पूर्ण
	NEXT_ARG();

	अगर (argc < 2)
		usage();

	fds = दो_स्मृति(माप(पूर्णांक));
	अगर (!fds) अणु
		p_err("mem alloc failed");
		वापस -1;
	पूर्ण
	nb_fds = prog_parse_fds(&argc, &argv, &fds);
	अगर (nb_fds < 1)
		जाओ निकास_मुक्त;

	अगर (is_prefix(*argv, "file")) अणु
		NEXT_ARG();
		अगर (!argc) अणु
			p_err("expected file path");
			जाओ निकास_बंद;
		पूर्ण
		अगर (nb_fds > 1) अणु
			p_err("several programs matched");
			जाओ निकास_बंद;
		पूर्ण

		filepath = *argv;
		NEXT_ARG();
	पूर्ण अन्यथा अगर (is_prefix(*argv, "opcodes")) अणु
		opcodes = true;
		NEXT_ARG();
	पूर्ण अन्यथा अगर (is_prefix(*argv, "visual")) अणु
		अगर (nb_fds > 1) अणु
			p_err("several programs matched");
			जाओ निकास_बंद;
		पूर्ण

		visual = true;
		NEXT_ARG();
	पूर्ण अन्यथा अगर (is_prefix(*argv, "linum")) अणु
		linum = true;
		NEXT_ARG();
	पूर्ण

	अगर (argc) अणु
		usage();
		जाओ निकास_बंद;
	पूर्ण

	अगर (mode == DUMP_JITED)
		arrays = 1UL << BPF_PROG_INFO_JITED_INSNS;
	अन्यथा
		arrays = 1UL << BPF_PROG_INFO_XLATED_INSNS;

	arrays |= 1UL << BPF_PROG_INFO_JITED_KSYMS;
	arrays |= 1UL << BPF_PROG_INFO_JITED_FUNC_LENS;
	arrays |= 1UL << BPF_PROG_INFO_FUNC_INFO;
	arrays |= 1UL << BPF_PROG_INFO_LINE_INFO;
	arrays |= 1UL << BPF_PROG_INFO_JITED_LINE_INFO;

	अगर (json_output && nb_fds > 1)
		jsonw_start_array(json_wtr);	/* root array */
	क्रम (i = 0; i < nb_fds; i++) अणु
		info_linear = bpf_program__get_prog_info_linear(fds[i], arrays);
		अगर (IS_ERR_OR_शून्य(info_linear)) अणु
			p_err("can't get prog info: %s", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		पूर्ण

		अगर (json_output && nb_fds > 1) अणु
			jsonw_start_object(json_wtr);	/* prog object */
			prपूर्णांक_prog_header_json(&info_linear->info);
			jsonw_name(json_wtr, "insns");
		पूर्ण अन्यथा अगर (nb_fds > 1) अणु
			prपूर्णांक_prog_header_plain(&info_linear->info);
		पूर्ण

		err = prog_dump(&info_linear->info, mode, filepath, opcodes,
				visual, linum);

		अगर (json_output && nb_fds > 1)
			jsonw_end_object(json_wtr);	/* prog object */
		अन्यथा अगर (i != nb_fds - 1 && nb_fds > 1)
			म_लिखो("\n");

		मुक्त(info_linear);
		अगर (err)
			अवरोध;
		बंद(fds[i]);
	पूर्ण
	अगर (json_output && nb_fds > 1)
		jsonw_end_array(json_wtr);	/* root array */

निकास_बंद:
	क्रम (; i < nb_fds; i++)
		बंद(fds[i]);
निकास_मुक्त:
	मुक्त(fds);
	वापस err;
पूर्ण

अटल पूर्णांक करो_pin(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक err;

	err = करो_pin_any(argc, argv, prog_parse_fd);
	अगर (!err && json_output)
		jsonw_null(json_wtr);
	वापस err;
पूर्ण

काष्ठा map_replace अणु
	पूर्णांक idx;
	पूर्णांक fd;
	अक्षर *name;
पूर्ण;

अटल पूर्णांक map_replace_compar(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा map_replace *a = p1, *b = p2;

	वापस a->idx - b->idx;
पूर्ण

अटल पूर्णांक parse_attach_detach_args(पूर्णांक argc, अक्षर **argv, पूर्णांक *progfd,
				    क्रमागत bpf_attach_type *attach_type,
				    पूर्णांक *mapfd)
अणु
	अगर (!REQ_ARGS(3))
		वापस -EINVAL;

	*progfd = prog_parse_fd(&argc, &argv);
	अगर (*progfd < 0)
		वापस *progfd;

	*attach_type = parse_attach_type(*argv);
	अगर (*attach_type == __MAX_BPF_ATTACH_TYPE) अणु
		p_err("invalid attach/detach type");
		वापस -EINVAL;
	पूर्ण

	अगर (*attach_type == BPF_FLOW_DISSECTOR) अणु
		*mapfd = 0;
		वापस 0;
	पूर्ण

	NEXT_ARG();
	अगर (!REQ_ARGS(2))
		वापस -EINVAL;

	*mapfd = map_parse_fd(&argc, &argv);
	अगर (*mapfd < 0)
		वापस *mapfd;

	वापस 0;
पूर्ण

अटल पूर्णांक करो_attach(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत bpf_attach_type attach_type;
	पूर्णांक err, progfd;
	पूर्णांक mapfd;

	err = parse_attach_detach_args(argc, argv,
				       &progfd, &attach_type, &mapfd);
	अगर (err)
		वापस err;

	err = bpf_prog_attach(progfd, mapfd, attach_type, 0);
	अगर (err) अणु
		p_err("failed prog attach to map");
		वापस -EINVAL;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_detach(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत bpf_attach_type attach_type;
	पूर्णांक err, progfd;
	पूर्णांक mapfd;

	err = parse_attach_detach_args(argc, argv,
				       &progfd, &attach_type, &mapfd);
	अगर (err)
		वापस err;

	err = bpf_prog_detach2(progfd, mapfd, attach_type);
	अगर (err) अणु
		p_err("failed prog detach from map");
		वापस -EINVAL;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);
	वापस 0;
पूर्ण

अटल पूर्णांक check_single_मानक_निवेश(अक्षर *file_data_in, अक्षर *file_ctx_in)
अणु
	अगर (file_data_in && file_ctx_in &&
	    !म_भेद(file_data_in, "-") && !म_भेद(file_ctx_in, "-")) अणु
		p_err("cannot use standard input for both data_in and ctx_in");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_run_data(स्थिर अक्षर *fname, व्योम **data_ptr, अचिन्हित पूर्णांक *size)
अणु
	माप_प्रकार block_size = 256;
	माप_प्रकार buf_size = block_size;
	माप_प्रकार nb_पढ़ो = 0;
	व्योम *पंचांगp;
	खाता *f;

	अगर (!fname) अणु
		*data_ptr = शून्य;
		*size = 0;
		वापस 0;
	पूर्ण

	अगर (!म_भेद(fname, "-"))
		f = मानक_निवेश;
	अन्यथा
		f = ख_खोलो(fname, "r");
	अगर (!f) अणु
		p_err("failed to open %s: %s", fname, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	*data_ptr = दो_स्मृति(block_size);
	अगर (!*data_ptr) अणु
		p_err("failed to allocate memory for data_in/ctx_in: %s",
		      म_त्रुटि(त्रुटि_सं));
		जाओ err_ख_बंद;
	पूर्ण

	जबतक ((nb_पढ़ो += ख_पढ़ो(*data_ptr + nb_पढ़ो, 1, block_size, f))) अणु
		अगर (ख_पूर्ण(f))
			अवरोध;
		अगर (ख_त्रुटि(f)) अणु
			p_err("failed to read data_in/ctx_in from %s: %s",
			      fname, म_त्रुटि(त्रुटि_सं));
			जाओ err_मुक्त;
		पूर्ण
		अगर (nb_पढ़ो > buf_size - block_size) अणु
			अगर (buf_size == UINT32_MAX) अणु
				p_err("data_in/ctx_in is too long (max: %d)",
				      UINT32_MAX);
				जाओ err_मुक्त;
			पूर्ण
			/* No space क्रम ख_पढ़ो()-ing next chunk; पुनः_स्मृति() */
			buf_size *= 2;
			पंचांगp = पुनः_स्मृति(*data_ptr, buf_size);
			अगर (!पंचांगp) अणु
				p_err("failed to reallocate data_in/ctx_in: %s",
				      म_त्रुटि(त्रुटि_सं));
				जाओ err_मुक्त;
			पूर्ण
			*data_ptr = पंचांगp;
		पूर्ण
	पूर्ण
	अगर (f != मानक_निवेश)
		ख_बंद(f);

	*size = nb_पढ़ो;
	वापस 0;

err_मुक्त:
	मुक्त(*data_ptr);
	*data_ptr = शून्य;
err_ख_बंद:
	अगर (f != मानक_निवेश)
		ख_बंद(f);
	वापस -1;
पूर्ण

अटल व्योम hex_prपूर्णांक(व्योम *data, अचिन्हित पूर्णांक size, खाता *f)
अणु
	माप_प्रकार i, j;
	अक्षर c;

	क्रम (i = 0; i < size; i += 16) अणु
		/* Row offset */
		ख_लिखो(f, "%07zx\t", i);

		/* Hexadecimal values */
		क्रम (j = i; j < i + 16 && j < size; j++)
			ख_लिखो(f, "%02x%s", *(uपूर्णांक8_t *)(data + j),
				j % 2 ? " " : "");
		क्रम (; j < i + 16; j++)
			ख_लिखो(f, "  %s", j % 2 ? " " : "");

		/* ASCII values (अगर relevant), '.' otherwise */
		ख_लिखो(f, "| ");
		क्रम (j = i; j < i + 16 && j < size; j++) अणु
			c = *(अक्षर *)(data + j);
			अगर (c < ' ' || c > '~')
				c = '.';
			ख_लिखो(f, "%c%s", c, j == i + 7 ? " " : "");
		पूर्ण

		ख_लिखो(f, "\n");
	पूर्ण
पूर्ण

अटल पूर्णांक
prपूर्णांक_run_output(व्योम *data, अचिन्हित पूर्णांक size, स्थिर अक्षर *fname,
		 स्थिर अक्षर *json_key)
अणु
	माप_प्रकार nb_written;
	खाता *f;

	अगर (!fname)
		वापस 0;

	अगर (!म_भेद(fname, "-")) अणु
		f = मानक_निकास;
		अगर (json_output) अणु
			jsonw_name(json_wtr, json_key);
			prपूर्णांक_data_json(data, size);
		पूर्ण अन्यथा अणु
			hex_prपूर्णांक(data, size, f);
		पूर्ण
		वापस 0;
	पूर्ण

	f = ख_खोलो(fname, "w");
	अगर (!f) अणु
		p_err("failed to open %s: %s", fname, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	nb_written = ख_डालो(data, 1, size, f);
	ख_बंद(f);
	अगर (nb_written != size) अणु
		p_err("failed to write output data/ctx: %s", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_run_data(व्योम **data_ptr, अचिन्हित पूर्णांक size_out)
अणु
	*data_ptr = सुस्मृति(size_out, 1);
	अगर (!*data_ptr) अणु
		p_err("failed to allocate memory for output data/ctx: %s",
		      म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_run(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *data_fname_in = शून्य, *data_fname_out = शून्य;
	अक्षर *ctx_fname_in = शून्य, *ctx_fname_out = शून्य;
	काष्ठा bpf_prog_test_run_attr test_attr = अणु0पूर्ण;
	स्थिर अचिन्हित पूर्णांक शेष_size = SZ_32K;
	व्योम *data_in = शून्य, *data_out = शून्य;
	व्योम *ctx_in = शून्य, *ctx_out = शून्य;
	अचिन्हित पूर्णांक repeat = 1;
	पूर्णांक fd, err;

	अगर (!REQ_ARGS(4))
		वापस -1;

	fd = prog_parse_fd(&argc, &argv);
	अगर (fd < 0)
		वापस -1;

	जबतक (argc) अणु
		अगर (detect_common_prefix(*argv, "data_in", "data_out",
					 "data_size_out", शून्य))
			वापस -1;
		अगर (detect_common_prefix(*argv, "ctx_in", "ctx_out",
					 "ctx_size_out", शून्य))
			वापस -1;

		अगर (is_prefix(*argv, "data_in")) अणु
			NEXT_ARG();
			अगर (!REQ_ARGS(1))
				वापस -1;

			data_fname_in = GET_ARG();
			अगर (check_single_मानक_निवेश(data_fname_in, ctx_fname_in))
				वापस -1;
		पूर्ण अन्यथा अगर (is_prefix(*argv, "data_out")) अणु
			NEXT_ARG();
			अगर (!REQ_ARGS(1))
				वापस -1;

			data_fname_out = GET_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "data_size_out")) अणु
			अक्षर *endptr;

			NEXT_ARG();
			अगर (!REQ_ARGS(1))
				वापस -1;

			test_attr.data_size_out = म_से_अदीर्घ(*argv, &endptr, 0);
			अगर (*endptr) अणु
				p_err("can't parse %s as output data size",
				      *argv);
				वापस -1;
			पूर्ण
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "ctx_in")) अणु
			NEXT_ARG();
			अगर (!REQ_ARGS(1))
				वापस -1;

			ctx_fname_in = GET_ARG();
			अगर (check_single_मानक_निवेश(data_fname_in, ctx_fname_in))
				वापस -1;
		पूर्ण अन्यथा अगर (is_prefix(*argv, "ctx_out")) अणु
			NEXT_ARG();
			अगर (!REQ_ARGS(1))
				वापस -1;

			ctx_fname_out = GET_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "ctx_size_out")) अणु
			अक्षर *endptr;

			NEXT_ARG();
			अगर (!REQ_ARGS(1))
				वापस -1;

			test_attr.ctx_size_out = म_से_अदीर्घ(*argv, &endptr, 0);
			अगर (*endptr) अणु
				p_err("can't parse %s as output context size",
				      *argv);
				वापस -1;
			पूर्ण
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "repeat")) अणु
			अक्षर *endptr;

			NEXT_ARG();
			अगर (!REQ_ARGS(1))
				वापस -1;

			repeat = म_से_अदीर्घ(*argv, &endptr, 0);
			अगर (*endptr) अणु
				p_err("can't parse %s as repeat number",
				      *argv);
				वापस -1;
			पूर्ण
			NEXT_ARG();
		पूर्ण अन्यथा अणु
			p_err("expected no more arguments, 'data_in', 'data_out', 'data_size_out', 'ctx_in', 'ctx_out', 'ctx_size_out' or 'repeat', got: '%s'?",
			      *argv);
			वापस -1;
		पूर्ण
	पूर्ण

	err = get_run_data(data_fname_in, &data_in, &test_attr.data_size_in);
	अगर (err)
		वापस -1;

	अगर (data_in) अणु
		अगर (!test_attr.data_size_out)
			test_attr.data_size_out = शेष_size;
		err = alloc_run_data(&data_out, test_attr.data_size_out);
		अगर (err)
			जाओ मुक्त_data_in;
	पूर्ण

	err = get_run_data(ctx_fname_in, &ctx_in, &test_attr.ctx_size_in);
	अगर (err)
		जाओ मुक्त_data_out;

	अगर (ctx_in) अणु
		अगर (!test_attr.ctx_size_out)
			test_attr.ctx_size_out = शेष_size;
		err = alloc_run_data(&ctx_out, test_attr.ctx_size_out);
		अगर (err)
			जाओ मुक्त_ctx_in;
	पूर्ण

	test_attr.prog_fd	= fd;
	test_attr.repeat	= repeat;
	test_attr.data_in	= data_in;
	test_attr.data_out	= data_out;
	test_attr.ctx_in	= ctx_in;
	test_attr.ctx_out	= ctx_out;

	err = bpf_prog_test_run_xattr(&test_attr);
	अगर (err) अणु
		p_err("failed to run program: %s", म_त्रुटि(त्रुटि_सं));
		जाओ मुक्त_ctx_out;
	पूर्ण

	err = 0;

	अगर (json_output)
		jsonw_start_object(json_wtr);	/* root */

	/* Do not निकास on errors occurring when prपूर्णांकing output data/context,
	 * we still want to prपूर्णांक वापस value and duration क्रम program run.
	 */
	अगर (test_attr.data_size_out)
		err += prपूर्णांक_run_output(test_attr.data_out,
					test_attr.data_size_out,
					data_fname_out, "data_out");
	अगर (test_attr.ctx_size_out)
		err += prपूर्णांक_run_output(test_attr.ctx_out,
					test_attr.ctx_size_out,
					ctx_fname_out, "ctx_out");

	अगर (json_output) अणु
		jsonw_uपूर्णांक_field(json_wtr, "retval", test_attr.retval);
		jsonw_uपूर्णांक_field(json_wtr, "duration", test_attr.duration);
		jsonw_end_object(json_wtr);	/* root */
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_निकास, "Return value: %u, duration%s: %uns\n",
			test_attr.retval,
			repeat > 1 ? " (average)" : "", test_attr.duration);
	पूर्ण

मुक्त_ctx_out:
	मुक्त(ctx_out);
मुक्त_ctx_in:
	मुक्त(ctx_in);
मुक्त_data_out:
	मुक्त(data_out);
मुक्त_data_in:
	मुक्त(data_in);

	वापस err;
पूर्ण

अटल पूर्णांक
get_prog_type_by_name(स्थिर अक्षर *name, क्रमागत bpf_prog_type *prog_type,
		      क्रमागत bpf_attach_type *expected_attach_type)
अणु
	libbpf_prपूर्णांक_fn_t prपूर्णांक_backup;
	पूर्णांक ret;

	ret = libbpf_prog_type_by_name(name, prog_type, expected_attach_type);
	अगर (!ret)
		वापस ret;

	/* libbpf_prog_type_by_name() failed, let's re-run with debug level */
	prपूर्णांक_backup = libbpf_set_prपूर्णांक(prपूर्णांक_all_levels);
	ret = libbpf_prog_type_by_name(name, prog_type, expected_attach_type);
	libbpf_set_prपूर्णांक(prपूर्णांक_backup);

	वापस ret;
पूर्ण

अटल पूर्णांक load_with_options(पूर्णांक argc, अक्षर **argv, bool first_prog_only)
अणु
	क्रमागत bpf_prog_type common_prog_type = BPF_PROG_TYPE_UNSPEC;
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, खोलो_opts,
		.relaxed_maps = relaxed_maps,
	);
	काष्ठा bpf_object_load_attr load_attr = अणु 0 पूर्ण;
	क्रमागत bpf_attach_type expected_attach_type;
	काष्ठा map_replace *map_replace = शून्य;
	काष्ठा bpf_program *prog = शून्य, *pos;
	अचिन्हित पूर्णांक old_map_fds = 0;
	स्थिर अक्षर *pinmaps = शून्य;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	स्थिर अक्षर *pinfile;
	अचिन्हित पूर्णांक i, j;
	__u32 अगरindex = 0;
	स्थिर अक्षर *file;
	पूर्णांक idx, err;


	अगर (!REQ_ARGS(2))
		वापस -1;
	file = GET_ARG();
	pinfile = GET_ARG();

	जबतक (argc) अणु
		अगर (is_prefix(*argv, "type")) अणु
			अक्षर *type;

			NEXT_ARG();

			अगर (common_prog_type != BPF_PROG_TYPE_UNSPEC) अणु
				p_err("program type already specified");
				जाओ err_मुक्त_reuse_maps;
			पूर्ण
			अगर (!REQ_ARGS(1))
				जाओ err_मुक्त_reuse_maps;

			/* Put a '/' at the end of type to appease libbpf */
			type = दो_स्मृति(म_माप(*argv) + 2);
			अगर (!type) अणु
				p_err("mem alloc failed");
				जाओ err_मुक्त_reuse_maps;
			पूर्ण
			*type = 0;
			म_जोड़ो(type, *argv);
			म_जोड़ो(type, "/");

			err = get_prog_type_by_name(type, &common_prog_type,
						    &expected_attach_type);
			मुक्त(type);
			अगर (err < 0)
				जाओ err_मुक्त_reuse_maps;

			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "map")) अणु
			व्योम *new_map_replace;
			अक्षर *endptr, *name;
			पूर्णांक fd;

			NEXT_ARG();

			अगर (!REQ_ARGS(4))
				जाओ err_मुक्त_reuse_maps;

			अगर (is_prefix(*argv, "idx")) अणु
				NEXT_ARG();

				idx = म_से_अदीर्घ(*argv, &endptr, 0);
				अगर (*endptr) अणु
					p_err("can't parse %s as IDX", *argv);
					जाओ err_मुक्त_reuse_maps;
				पूर्ण
				name = शून्य;
			पूर्ण अन्यथा अगर (is_prefix(*argv, "name")) अणु
				NEXT_ARG();

				name = *argv;
				idx = -1;
			पूर्ण अन्यथा अणु
				p_err("expected 'idx' or 'name', got: '%s'?",
				      *argv);
				जाओ err_मुक्त_reuse_maps;
			पूर्ण
			NEXT_ARG();

			fd = map_parse_fd(&argc, &argv);
			अगर (fd < 0)
				जाओ err_मुक्त_reuse_maps;

			new_map_replace = पुनः_स्मृतिarray(map_replace,
						       old_map_fds + 1,
						       माप(*map_replace));
			अगर (!new_map_replace) अणु
				p_err("mem alloc failed");
				जाओ err_मुक्त_reuse_maps;
			पूर्ण
			map_replace = new_map_replace;

			map_replace[old_map_fds].idx = idx;
			map_replace[old_map_fds].name = name;
			map_replace[old_map_fds].fd = fd;
			old_map_fds++;
		पूर्ण अन्यथा अगर (is_prefix(*argv, "dev")) अणु
			NEXT_ARG();

			अगर (अगरindex) अणु
				p_err("offload device already specified");
				जाओ err_मुक्त_reuse_maps;
			पूर्ण
			अगर (!REQ_ARGS(1))
				जाओ err_मुक्त_reuse_maps;

			अगरindex = अगर_nametoindex(*argv);
			अगर (!अगरindex) अणु
				p_err("unrecognized netdevice '%s': %s",
				      *argv, म_त्रुटि(त्रुटि_सं));
				जाओ err_मुक्त_reuse_maps;
			पूर्ण
			NEXT_ARG();
		पूर्ण अन्यथा अगर (is_prefix(*argv, "pinmaps")) अणु
			NEXT_ARG();

			अगर (!REQ_ARGS(1))
				जाओ err_मुक्त_reuse_maps;

			pinmaps = GET_ARG();
		पूर्ण अन्यथा अणु
			p_err("expected no more arguments, 'type', 'map' or 'dev', got: '%s'?",
			      *argv);
			जाओ err_मुक्त_reuse_maps;
		पूर्ण
	पूर्ण

	set_max_rlimit();

	obj = bpf_object__खोलो_file(file, &खोलो_opts);
	अगर (IS_ERR_OR_शून्य(obj)) अणु
		p_err("failed to open object file");
		जाओ err_मुक्त_reuse_maps;
	पूर्ण

	bpf_object__क्रम_each_program(pos, obj) अणु
		क्रमागत bpf_prog_type prog_type = common_prog_type;

		अगर (prog_type == BPF_PROG_TYPE_UNSPEC) अणु
			स्थिर अक्षर *sec_name = bpf_program__section_name(pos);

			err = get_prog_type_by_name(sec_name, &prog_type,
						    &expected_attach_type);
			अगर (err < 0)
				जाओ err_बंद_obj;
		पूर्ण

		bpf_program__set_अगरindex(pos, अगरindex);
		bpf_program__set_type(pos, prog_type);
		bpf_program__set_expected_attach_type(pos, expected_attach_type);
	पूर्ण

	क्विक(map_replace, old_map_fds, माप(*map_replace),
	      map_replace_compar);

	/* After the sort maps by name will be first on the list, because they
	 * have idx == -1.  Resolve them.
	 */
	j = 0;
	जबतक (j < old_map_fds && map_replace[j].name) अणु
		i = 0;
		bpf_object__क्रम_each_map(map, obj) अणु
			अगर (!म_भेद(bpf_map__name(map), map_replace[j].name)) अणु
				map_replace[j].idx = i;
				अवरोध;
			पूर्ण
			i++;
		पूर्ण
		अगर (map_replace[j].idx == -1) अणु
			p_err("unable to find map '%s'", map_replace[j].name);
			जाओ err_बंद_obj;
		पूर्ण
		j++;
	पूर्ण
	/* Resort अगर any names were resolved */
	अगर (j)
		क्विक(map_replace, old_map_fds, माप(*map_replace),
		      map_replace_compar);

	/* Set अगरindex and name reuse */
	j = 0;
	idx = 0;
	bpf_object__क्रम_each_map(map, obj) अणु
		अगर (!bpf_map__is_offload_neutral(map))
			bpf_map__set_अगरindex(map, अगरindex);

		अगर (j < old_map_fds && idx == map_replace[j].idx) अणु
			err = bpf_map__reuse_fd(map, map_replace[j++].fd);
			अगर (err) अणु
				p_err("unable to set up map reuse: %d", err);
				जाओ err_बंद_obj;
			पूर्ण

			/* Next reuse wants to apply to the same map */
			अगर (j < old_map_fds && map_replace[j].idx == idx) अणु
				p_err("replacement for map idx %d specified more than once",
				      idx);
				जाओ err_बंद_obj;
			पूर्ण
		पूर्ण

		idx++;
	पूर्ण
	अगर (j < old_map_fds) अणु
		p_err("map idx '%d' not used", map_replace[j].idx);
		जाओ err_बंद_obj;
	पूर्ण

	load_attr.obj = obj;
	अगर (verअगरier_logs)
		/* log_level1 + log_level2 + stats, but not stable UAPI */
		load_attr.log_level = 1 + 2 + 4;

	err = bpf_object__load_xattr(&load_attr);
	अगर (err) अणु
		p_err("failed to load object file");
		जाओ err_बंद_obj;
	पूर्ण

	err = mount_bpffs_क्रम_pin(pinfile);
	अगर (err)
		जाओ err_बंद_obj;

	अगर (first_prog_only) अणु
		prog = bpf_program__next(शून्य, obj);
		अगर (!prog) अणु
			p_err("object file doesn't contain any bpf program");
			जाओ err_बंद_obj;
		पूर्ण

		err = bpf_obj_pin(bpf_program__fd(prog), pinfile);
		अगर (err) अणु
			p_err("failed to pin program %s",
			      bpf_program__section_name(prog));
			जाओ err_बंद_obj;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = bpf_object__pin_programs(obj, pinfile);
		अगर (err) अणु
			p_err("failed to pin all programs");
			जाओ err_बंद_obj;
		पूर्ण
	पूर्ण

	अगर (pinmaps) अणु
		err = bpf_object__pin_maps(obj, pinmaps);
		अगर (err) अणु
			p_err("failed to pin all maps");
			जाओ err_unpin;
		पूर्ण
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);

	bpf_object__बंद(obj);
	क्रम (i = 0; i < old_map_fds; i++)
		बंद(map_replace[i].fd);
	मुक्त(map_replace);

	वापस 0;

err_unpin:
	अगर (first_prog_only)
		unlink(pinfile);
	अन्यथा
		bpf_object__unpin_programs(obj, pinfile);
err_बंद_obj:
	bpf_object__बंद(obj);
err_मुक्त_reuse_maps:
	क्रम (i = 0; i < old_map_fds; i++)
		बंद(map_replace[i].fd);
	मुक्त(map_replace);
	वापस -1;
पूर्ण

अटल पूर्णांक करो_load(पूर्णांक argc, अक्षर **argv)
अणु
	वापस load_with_options(argc, argv, true);
पूर्ण

अटल पूर्णांक करो_loadall(पूर्णांक argc, अक्षर **argv)
अणु
	वापस load_with_options(argc, argv, false);
पूर्ण

#अगर_घोषित BPFTOOL_WITHOUT_SKELETONS

अटल पूर्णांक करो_profile(पूर्णांक argc, अक्षर **argv)
अणु
	p_err("bpftool prog profile command is not supported. Please build bpftool with clang >= 10.0.0");
	वापस 0;
पूर्ण

#अन्यथा /* BPFTOOL_WITHOUT_SKELETONS */

#समावेश "profiler.skel.h"

काष्ठा profile_metric अणु
	स्थिर अक्षर *name;
	काष्ठा bpf_perf_event_value val;
	काष्ठा perf_event_attr attr;
	bool selected;

	/* calculate ratios like inकाष्ठाions per cycle */
	स्थिर पूर्णांक ratio_metric; /* 0 क्रम N/A, 1 क्रम index 0 (cycles) */
	स्थिर अक्षर *ratio_desc;
	स्थिर भग्न ratio_mul;
पूर्ण metrics[] = अणु
	अणु
		.name = "cycles",
		.attr = अणु
			.type = PERF_TYPE_HARDWARE,
			.config = PERF_COUNT_HW_CPU_CYCLES,
			.exclude_user = 1,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "instructions",
		.attr = अणु
			.type = PERF_TYPE_HARDWARE,
			.config = PERF_COUNT_HW_INSTRUCTIONS,
			.exclude_user = 1,
		पूर्ण,
		.ratio_metric = 1,
		.ratio_desc = "insns per cycle",
		.ratio_mul = 1.0,
	पूर्ण,
	अणु
		.name = "l1d_loads",
		.attr = अणु
			.type = PERF_TYPE_HW_CACHE,
			.config =
				PERF_COUNT_HW_CACHE_L1D |
				(PERF_COUNT_HW_CACHE_OP_READ << 8) |
				(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16),
			.exclude_user = 1,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "llc_misses",
		.attr = अणु
			.type = PERF_TYPE_HW_CACHE,
			.config =
				PERF_COUNT_HW_CACHE_LL |
				(PERF_COUNT_HW_CACHE_OP_READ << 8) |
				(PERF_COUNT_HW_CACHE_RESULT_MISS << 16),
			.exclude_user = 1
		पूर्ण,
		.ratio_metric = 2,
		.ratio_desc = "LLC misses per million insns",
		.ratio_mul = 1e6,
	पूर्ण,
	अणु
		.name = "itlb_misses",
		.attr = अणु
			.type = PERF_TYPE_HW_CACHE,
			.config =
				PERF_COUNT_HW_CACHE_ITLB |
				(PERF_COUNT_HW_CACHE_OP_READ << 8) |
				(PERF_COUNT_HW_CACHE_RESULT_MISS << 16),
			.exclude_user = 1
		पूर्ण,
		.ratio_metric = 2,
		.ratio_desc = "itlb misses per million insns",
		.ratio_mul = 1e6,
	पूर्ण,
	अणु
		.name = "dtlb_misses",
		.attr = अणु
			.type = PERF_TYPE_HW_CACHE,
			.config =
				PERF_COUNT_HW_CACHE_DTLB |
				(PERF_COUNT_HW_CACHE_OP_READ << 8) |
				(PERF_COUNT_HW_CACHE_RESULT_MISS << 16),
			.exclude_user = 1
		पूर्ण,
		.ratio_metric = 2,
		.ratio_desc = "dtlb misses per million insns",
		.ratio_mul = 1e6,
	पूर्ण,
पूर्ण;

अटल __u64 profile_total_count;

#घोषणा MAX_NUM_PROखाता_METRICS 4

अटल पूर्णांक profile_parse_metrics(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक metric_cnt;
	पूर्णांक selected_cnt = 0;
	अचिन्हित पूर्णांक i;

	metric_cnt = माप(metrics) / माप(काष्ठा profile_metric);

	जबतक (argc > 0) अणु
		क्रम (i = 0; i < metric_cnt; i++) अणु
			अगर (is_prefix(argv[0], metrics[i].name)) अणु
				अगर (!metrics[i].selected)
					selected_cnt++;
				metrics[i].selected = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == metric_cnt) अणु
			p_err("unknown metric %s", argv[0]);
			वापस -1;
		पूर्ण
		NEXT_ARG();
	पूर्ण
	अगर (selected_cnt > MAX_NUM_PROखाता_METRICS) अणु
		p_err("too many (%d) metrics, please specify no more than %d metrics at at time",
		      selected_cnt, MAX_NUM_PROखाता_METRICS);
		वापस -1;
	पूर्ण
	वापस selected_cnt;
पूर्ण

अटल व्योम profile_पढ़ो_values(काष्ठा profiler_bpf *obj)
अणु
	__u32 m, cpu, num_cpu = obj->rodata->num_cpu;
	पूर्णांक पढ़ोing_map_fd, count_map_fd;
	__u64 counts[num_cpu];
	__u32 key = 0;
	पूर्णांक err;

	पढ़ोing_map_fd = bpf_map__fd(obj->maps.accum_पढ़ोings);
	count_map_fd = bpf_map__fd(obj->maps.counts);
	अगर (पढ़ोing_map_fd < 0 || count_map_fd < 0) अणु
		p_err("failed to get fd for map");
		वापस;
	पूर्ण

	err = bpf_map_lookup_elem(count_map_fd, &key, counts);
	अगर (err) अणु
		p_err("failed to read count_map: %s", म_त्रुटि(त्रुटि_सं));
		वापस;
	पूर्ण

	profile_total_count = 0;
	क्रम (cpu = 0; cpu < num_cpu; cpu++)
		profile_total_count += counts[cpu];

	क्रम (m = 0; m < ARRAY_SIZE(metrics); m++) अणु
		काष्ठा bpf_perf_event_value values[num_cpu];

		अगर (!metrics[m].selected)
			जारी;

		err = bpf_map_lookup_elem(पढ़ोing_map_fd, &key, values);
		अगर (err) अणु
			p_err("failed to read reading_map: %s",
			      म_त्रुटि(त्रुटि_सं));
			वापस;
		पूर्ण
		क्रम (cpu = 0; cpu < num_cpu; cpu++) अणु
			metrics[m].val.counter += values[cpu].counter;
			metrics[m].val.enabled += values[cpu].enabled;
			metrics[m].val.running += values[cpu].running;
		पूर्ण
		key++;
	पूर्ण
पूर्ण

अटल व्योम profile_prपूर्णांक_पढ़ोings_json(व्योम)
अणु
	__u32 m;

	jsonw_start_array(json_wtr);
	क्रम (m = 0; m < ARRAY_SIZE(metrics); m++) अणु
		अगर (!metrics[m].selected)
			जारी;
		jsonw_start_object(json_wtr);
		jsonw_string_field(json_wtr, "metric", metrics[m].name);
		jsonw_lluपूर्णांक_field(json_wtr, "run_cnt", profile_total_count);
		jsonw_lluपूर्णांक_field(json_wtr, "value", metrics[m].val.counter);
		jsonw_lluपूर्णांक_field(json_wtr, "enabled", metrics[m].val.enabled);
		jsonw_lluपूर्णांक_field(json_wtr, "running", metrics[m].val.running);

		jsonw_end_object(json_wtr);
	पूर्ण
	jsonw_end_array(json_wtr);
पूर्ण

अटल व्योम profile_prपूर्णांक_पढ़ोings_plain(व्योम)
अणु
	__u32 m;

	म_लिखो("\n%18llu %-20s\n", profile_total_count, "run_cnt");
	क्रम (m = 0; m < ARRAY_SIZE(metrics); m++) अणु
		काष्ठा bpf_perf_event_value *val = &metrics[m].val;
		पूर्णांक r;

		अगर (!metrics[m].selected)
			जारी;
		म_लिखो("%18llu %-20s", val->counter, metrics[m].name);

		r = metrics[m].ratio_metric - 1;
		अगर (r >= 0 && metrics[r].selected &&
		    metrics[r].val.counter > 0) अणु
			म_लिखो("# %8.2f %-30s",
			       val->counter * metrics[m].ratio_mul /
			       metrics[r].val.counter,
			       metrics[m].ratio_desc);
		पूर्ण अन्यथा अणु
			म_लिखो("%-41s", "");
		पूर्ण

		अगर (val->enabled > val->running)
			म_लिखो("(%4.2f%%)",
			       val->running * 100.0 / val->enabled);
		म_लिखो("\n");
	पूर्ण
पूर्ण

अटल व्योम profile_prपूर्णांक_पढ़ोings(व्योम)
अणु
	अगर (json_output)
		profile_prपूर्णांक_पढ़ोings_json();
	अन्यथा
		profile_prपूर्णांक_पढ़ोings_plain();
पूर्ण

अटल अक्षर *profile_target_name(पूर्णांक tgt_fd)
अणु
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_func_info *func_info;
	स्थिर काष्ठा btf_type *t;
	अक्षर *name = शून्य;
	काष्ठा btf *btf;

	info_linear = bpf_program__get_prog_info_linear(
		tgt_fd, 1UL << BPF_PROG_INFO_FUNC_INFO);
	अगर (IS_ERR_OR_शून्य(info_linear)) अणु
		p_err("failed to get info_linear for prog FD %d", tgt_fd);
		वापस शून्य;
	पूर्ण

	अगर (info_linear->info.btf_id == 0 ||
	    btf__get_from_id(info_linear->info.btf_id, &btf)) अणु
		p_err("prog FD %d doesn't have valid btf", tgt_fd);
		जाओ out;
	पूर्ण

	func_info = u64_to_ptr(info_linear->info.func_info);
	t = btf__type_by_id(btf, func_info[0].type_id);
	अगर (!t) अणु
		p_err("btf %d doesn't have type %d",
		      info_linear->info.btf_id, func_info[0].type_id);
		जाओ out;
	पूर्ण
	name = strdup(btf__name_by_offset(btf, t->name_off));
out:
	मुक्त(info_linear);
	वापस name;
पूर्ण

अटल काष्ठा profiler_bpf *profile_obj;
अटल पूर्णांक profile_tgt_fd = -1;
अटल अक्षर *profile_tgt_name;
अटल पूर्णांक *profile_perf_events;
अटल पूर्णांक profile_perf_event_cnt;

अटल व्योम profile_बंद_perf_events(काष्ठा profiler_bpf *obj)
अणु
	पूर्णांक i;

	क्रम (i = profile_perf_event_cnt - 1; i >= 0; i--)
		बंद(profile_perf_events[i]);

	मुक्त(profile_perf_events);
	profile_perf_event_cnt = 0;
पूर्ण

अटल पूर्णांक profile_खोलो_perf_events(काष्ठा profiler_bpf *obj)
अणु
	अचिन्हित पूर्णांक cpu, m;
	पूर्णांक map_fd, pmu_fd;

	profile_perf_events = सुस्मृति(
		माप(पूर्णांक), obj->rodata->num_cpu * obj->rodata->num_metric);
	अगर (!profile_perf_events) अणु
		p_err("failed to allocate memory for perf_event array: %s",
		      म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	map_fd = bpf_map__fd(obj->maps.events);
	अगर (map_fd < 0) अणु
		p_err("failed to get fd for events map");
		वापस -1;
	पूर्ण

	क्रम (m = 0; m < ARRAY_SIZE(metrics); m++) अणु
		अगर (!metrics[m].selected)
			जारी;
		क्रम (cpu = 0; cpu < obj->rodata->num_cpu; cpu++) अणु
			pmu_fd = syscall(__NR_perf_event_खोलो, &metrics[m].attr,
					 -1/*pid*/, cpu, -1/*group_fd*/, 0);
			अगर (pmu_fd < 0 ||
			    bpf_map_update_elem(map_fd, &profile_perf_event_cnt,
						&pmu_fd, BPF_ANY) ||
			    ioctl(pmu_fd, PERF_EVENT_IOC_ENABLE, 0)) अणु
				p_err("failed to create event %s on cpu %d",
				      metrics[m].name, cpu);
				वापस -1;
			पूर्ण
			profile_perf_events[profile_perf_event_cnt++] = pmu_fd;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम profile_prपूर्णांक_and_cleanup(व्योम)
अणु
	profile_बंद_perf_events(profile_obj);
	profile_पढ़ो_values(profile_obj);
	profile_prपूर्णांक_पढ़ोings();
	profiler_bpf__destroy(profile_obj);

	बंद(profile_tgt_fd);
	मुक्त(profile_tgt_name);
पूर्ण

अटल व्योम पूर्णांक_निकास(पूर्णांक signo)
अणु
	profile_prपूर्णांक_and_cleanup();
	निकास(0);
पूर्ण

अटल पूर्णांक करो_profile(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक num_metric, num_cpu, err = -1;
	काष्ठा bpf_program *prog;
	अचिन्हित दीर्घ duration;
	अक्षर *endptr;

	/* we at least need two args क्रम the prog and one metric */
	अगर (!REQ_ARGS(3))
		वापस -EINVAL;

	/* parse target fd */
	profile_tgt_fd = prog_parse_fd(&argc, &argv);
	अगर (profile_tgt_fd < 0) अणु
		p_err("failed to parse fd");
		वापस -1;
	पूर्ण

	/* parse profiling optional duration */
	अगर (argc > 2 && is_prefix(argv[0], "duration")) अणु
		NEXT_ARG();
		duration = म_से_अदीर्घ(*argv, &endptr, 0);
		अगर (*endptr)
			usage();
		NEXT_ARG();
	पूर्ण अन्यथा अणु
		duration = अच_पूर्णांक_उच्च;
	पूर्ण

	num_metric = profile_parse_metrics(argc, argv);
	अगर (num_metric <= 0)
		जाओ out;

	num_cpu = libbpf_num_possible_cpus();
	अगर (num_cpu <= 0) अणु
		p_err("failed to identify number of CPUs");
		जाओ out;
	पूर्ण

	profile_obj = profiler_bpf__खोलो();
	अगर (!profile_obj) अणु
		p_err("failed to open and/or load BPF object");
		जाओ out;
	पूर्ण

	profile_obj->rodata->num_cpu = num_cpu;
	profile_obj->rodata->num_metric = num_metric;

	/* adjust map sizes */
	bpf_map__resize(profile_obj->maps.events, num_metric * num_cpu);
	bpf_map__resize(profile_obj->maps.fentry_पढ़ोings, num_metric);
	bpf_map__resize(profile_obj->maps.accum_पढ़ोings, num_metric);
	bpf_map__resize(profile_obj->maps.counts, 1);

	/* change target name */
	profile_tgt_name = profile_target_name(profile_tgt_fd);
	अगर (!profile_tgt_name)
		जाओ out;

	bpf_object__क्रम_each_program(prog, profile_obj->obj) अणु
		err = bpf_program__set_attach_target(prog, profile_tgt_fd,
						     profile_tgt_name);
		अगर (err) अणु
			p_err("failed to set attach target\n");
			जाओ out;
		पूर्ण
	पूर्ण

	set_max_rlimit();
	err = profiler_bpf__load(profile_obj);
	अगर (err) अणु
		p_err("failed to load profile_obj");
		जाओ out;
	पूर्ण

	err = profile_खोलो_perf_events(profile_obj);
	अगर (err)
		जाओ out;

	err = profiler_bpf__attach(profile_obj);
	अगर (err) अणु
		p_err("failed to attach profile_obj");
		जाओ out;
	पूर्ण
	संकेत(संक_विघ्न, पूर्णांक_निकास);

	sleep(duration);
	profile_prपूर्णांक_and_cleanup();
	वापस 0;

out:
	profile_बंद_perf_events(profile_obj);
	अगर (profile_obj)
		profiler_bpf__destroy(profile_obj);
	बंद(profile_tgt_fd);
	मुक्त(profile_tgt_name);
	वापस err;
पूर्ण

#पूर्ण_अगर /* BPFTOOL_WITHOUT_SKELETONS */

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s { show | list } [PROG]\n"
		"       %1$s %2$s dump xlated PROG [{ file FILE | opcodes | visual | linum }]\n"
		"       %1$s %2$s dump jited  PROG [{ file FILE | opcodes | linum }]\n"
		"       %1$s %2$s pin   PROG FILE\n"
		"       %1$s %2$s { load | loadall } OBJ  PATH \\\n"
		"                         [type TYPE] [dev NAME] \\\n"
		"                         [map { idx IDX | name NAME } MAP]\\\n"
		"                         [pinmaps MAP_DIR]\n"
		"       %1$s %2$s attach PROG ATTACH_TYPE [MAP]\n"
		"       %1$s %2$s detach PROG ATTACH_TYPE [MAP]\n"
		"       %1$s %2$s run PROG \\\n"
		"                         data_in FILE \\\n"
		"                         [data_out FILE [data_size_out L]] \\\n"
		"                         [ctx_in FILE [ctx_out FILE [ctx_size_out M]]] \\\n"
		"                         [repeat N]\n"
		"       %1$s %2$s profile PROG [duration DURATION] METRICs\n"
		"       %1$s %2$s tracelog\n"
		"       %1$s %2$s help\n"
		"\n"
		"       " HELP_SPEC_MAP "\n"
		"       " HELP_SPEC_PROGRAM "\n"
		"       TYPE := { socket | kprobe | kretprobe | classifier | action |\n"
		"                 tracepoint | raw_tracepoint | xdp | perf_event | cgroup/skb |\n"
		"                 cgroup/sock | cgroup/dev | lwt_in | lwt_out | lwt_xmit |\n"
		"                 lwt_seg6local | sockops | sk_skb | sk_msg | lirc_mode2 |\n"
		"                 sk_reuseport | flow_dissector | cgroup/sysctl |\n"
		"                 cgroup/bind4 | cgroup/bind6 | cgroup/post_bind4 |\n"
		"                 cgroup/post_bind6 | cgroup/connect4 | cgroup/connect6 |\n"
		"                 cgroup/getpeername4 | cgroup/getpeername6 |\n"
		"                 cgroup/getsockname4 | cgroup/getsockname6 | cgroup/sendmsg4 |\n"
		"                 cgroup/sendmsg6 | cgroup/recvmsg4 | cgroup/recvmsg6 |\n"
		"                 cgroup/getsockopt | cgroup/setsockopt | cgroup/sock_release |\n"
		"                 struct_ops | fentry | fexit | freplace | sk_lookup }\n"
		"       ATTACH_TYPE := { msg_verdict | stream_verdict | stream_parser |\n"
		"                        flow_dissector }\n"
		"       METRIC := { cycles | instructions | l1d_loads | llc_misses | itlb_misses | dtlb_misses }\n"
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
	अणु "pin",	करो_pin पूर्ण,
	अणु "load",	करो_load पूर्ण,
	अणु "loadall",	करो_loadall पूर्ण,
	अणु "attach",	करो_attach पूर्ण,
	अणु "detach",	करो_detach पूर्ण,
	अणु "tracelog",	करो_tracelog पूर्ण,
	अणु "run",	करो_run पूर्ण,
	अणु "profile",	करो_profile पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_prog(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
