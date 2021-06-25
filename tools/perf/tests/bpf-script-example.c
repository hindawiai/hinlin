<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bpf-script-example.c
 * Test basic LLVM building
 */
#अगर_अघोषित LINUX_VERSION_CODE
# error Need LINUX_VERSION_CODE
# error Example: क्रम 4.2 kernel, put 'clang-opt="-DLINUX_VERSION_CODE=0x40200" into llvm section of ~/.perfconfig'
#पूर्ण_अगर
#घोषणा BPF_ANY 0
#घोषणा BPF_MAP_TYPE_ARRAY 2
#घोषणा BPF_FUNC_map_lookup_elem 1
#घोषणा BPF_FUNC_map_update_elem 2

अटल व्योम *(*bpf_map_lookup_elem)(व्योम *map, व्योम *key) =
	(व्योम *) BPF_FUNC_map_lookup_elem;
अटल व्योम *(*bpf_map_update_elem)(व्योम *map, व्योम *key, व्योम *value, पूर्णांक flags) =
	(व्योम *) BPF_FUNC_map_update_elem;

काष्ठा bpf_map_def अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक key_size;
	अचिन्हित पूर्णांक value_size;
	अचिन्हित पूर्णांक max_entries;
पूर्ण;

#घोषणा SEC(NAME) __attribute__((section(NAME), used))
काष्ठा bpf_map_def SEC("maps") flip_table = अणु
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.max_entries = 1,
पूर्ण;

SEC("func=do_epoll_wait")
पूर्णांक bpf_func__SyS_epoll_pरुको(व्योम *ctx)
अणु
	पूर्णांक ind =0;
	पूर्णांक *flag = bpf_map_lookup_elem(&flip_table, &ind);
	पूर्णांक new_flag;
	अगर (!flag)
		वापस 0;
	/* flip flag and store back */
	new_flag = !*flag;
	bpf_map_update_elem(&flip_table, &ind, &new_flag, BPF_ANY);
	वापस new_flag;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = LINUX_VERSION_CODE;
