<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश "trace_common.h"

#घोषणा MAX_ENTRIES 1000
#घोषणा MAX_NR_CPUS 1024

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
पूर्ण hash_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_HASH);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, 10000);
पूर्ण lru_hash_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_HASH);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, 10000);
	__uपूर्णांक(map_flags, BPF_F_NO_COMMON_LRU);
पूर्ण nocommon_lru_hash_map SEC(".maps");

काष्ठा inner_lru अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_HASH);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__uपूर्णांक(map_flags, BPF_F_NUMA_NODE);
	__uपूर्णांक(numa_node, 0);
पूर्ण inner_lru_hash_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, MAX_NR_CPUS);
	__uपूर्णांक(key_size, माप(u32));
	__array(values, काष्ठा inner_lru); /* use inner_lru as inner map */
पूर्ण array_of_lru_hashs SEC(".maps") = अणु
	/* अटलally initialize the first element */
	.values = अणु &inner_lru_hash_map पूर्ण,
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(दीर्घ));
	__uपूर्णांक(max_entries, MAX_ENTRIES);
पूर्ण percpu_hash_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
पूर्ण hash_map_alloc SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(दीर्घ));
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
पूर्ण percpu_hash_map_alloc SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LPM_TRIE);
	__uपूर्णांक(key_size, 8);
	__uपूर्णांक(value_size, माप(दीर्घ));
	__uपूर्णांक(max_entries, 10000);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
पूर्ण lpm_trie_map_alloc SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
पूर्ण array_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_HASH);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
पूर्ण lru_hash_lookup_map SEC(".maps");

SEC("kprobe/" SYSCALL(sys_getuid))
पूर्णांक stress_hmap(काष्ठा pt_regs *ctx)
अणु
	u32 key = bpf_get_current_pid_tgid();
	दीर्घ init_val = 1;
	दीर्घ *value;

	bpf_map_update_elem(&hash_map, &key, &init_val, BPF_ANY);
	value = bpf_map_lookup_elem(&hash_map, &key);
	अगर (value)
		bpf_map_delete_elem(&hash_map, &key);

	वापस 0;
पूर्ण

SEC("kprobe/" SYSCALL(sys_geteuid))
पूर्णांक stress_percpu_hmap(काष्ठा pt_regs *ctx)
अणु
	u32 key = bpf_get_current_pid_tgid();
	दीर्घ init_val = 1;
	दीर्घ *value;

	bpf_map_update_elem(&percpu_hash_map, &key, &init_val, BPF_ANY);
	value = bpf_map_lookup_elem(&percpu_hash_map, &key);
	अगर (value)
		bpf_map_delete_elem(&percpu_hash_map, &key);
	वापस 0;
पूर्ण

SEC("kprobe/" SYSCALL(sys_getgid))
पूर्णांक stress_hmap_alloc(काष्ठा pt_regs *ctx)
अणु
	u32 key = bpf_get_current_pid_tgid();
	दीर्घ init_val = 1;
	दीर्घ *value;

	bpf_map_update_elem(&hash_map_alloc, &key, &init_val, BPF_ANY);
	value = bpf_map_lookup_elem(&hash_map_alloc, &key);
	अगर (value)
		bpf_map_delete_elem(&hash_map_alloc, &key);
	वापस 0;
पूर्ण

SEC("kprobe/" SYSCALL(sys_getegid))
पूर्णांक stress_percpu_hmap_alloc(काष्ठा pt_regs *ctx)
अणु
	u32 key = bpf_get_current_pid_tgid();
	दीर्घ init_val = 1;
	दीर्घ *value;

	bpf_map_update_elem(&percpu_hash_map_alloc, &key, &init_val, BPF_ANY);
	value = bpf_map_lookup_elem(&percpu_hash_map_alloc, &key);
	अगर (value)
		bpf_map_delete_elem(&percpu_hash_map_alloc, &key);
	वापस 0;
पूर्ण

SEC("kprobe/" SYSCALL(sys_connect))
पूर्णांक stress_lru_hmap_alloc(काष्ठा pt_regs *ctx)
अणु
	काष्ठा pt_regs *real_regs = (काष्ठा pt_regs *)PT_REGS_PARM1_CORE(ctx);
	अक्षर fmt[] = "Failed at stress_lru_hmap_alloc. ret:%dn";
	जोड़ अणु
		u16 dst6[8];
		काष्ठा अणु
			u16 magic0;
			u16 magic1;
			u16 tहाल;
			u16 unused16;
			u32 unused32;
			u32 key;
		पूर्ण;
	पूर्ण test_params;
	काष्ठा sockaddr_in6 *in6;
	u16 test_हाल;
	पूर्णांक addrlen, ret;
	दीर्घ val = 1;
	u32 key = 0;

	in6 = (काष्ठा sockaddr_in6 *)PT_REGS_PARM2_CORE(real_regs);
	addrlen = (पूर्णांक)PT_REGS_PARM3_CORE(real_regs);

	अगर (addrlen != माप(*in6))
		वापस 0;

	ret = bpf_probe_पढ़ो_user(test_params.dst6, माप(test_params.dst6),
				  &in6->sin6_addr);
	अगर (ret)
		जाओ करोne;

	अगर (test_params.magic0 != 0xdead ||
	    test_params.magic1 != 0xbeef)
		वापस 0;

	test_हाल = test_params.tहाल;
	अगर (test_हाल != 3)
		key = bpf_get_pअक्रमom_u32();

	अगर (test_हाल == 0) अणु
		ret = bpf_map_update_elem(&lru_hash_map, &key, &val, BPF_ANY);
	पूर्ण अन्यथा अगर (test_हाल == 1) अणु
		ret = bpf_map_update_elem(&nocommon_lru_hash_map, &key, &val,
					  BPF_ANY);
	पूर्ण अन्यथा अगर (test_हाल == 2) अणु
		व्योम *nolocal_lru_map;
		पूर्णांक cpu = bpf_get_smp_processor_id();

		nolocal_lru_map = bpf_map_lookup_elem(&array_of_lru_hashs,
						      &cpu);
		अगर (!nolocal_lru_map) अणु
			ret = -ENOENT;
			जाओ करोne;
		पूर्ण

		ret = bpf_map_update_elem(nolocal_lru_map, &key, &val,
					  BPF_ANY);
	पूर्ण अन्यथा अगर (test_हाल == 3) अणु
		u32 i;

		key = test_params.key;

#आशय clang loop unroll(full)
		क्रम (i = 0; i < 32; i++) अणु
			bpf_map_lookup_elem(&lru_hash_lookup_map, &key);
			key++;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

करोne:
	अगर (ret)
		bpf_trace_prपूर्णांकk(fmt, माप(fmt), ret);

	वापस 0;
पूर्ण

SEC("kprobe/" SYSCALL(sys_gettid))
पूर्णांक stress_lpm_trie_map_alloc(काष्ठा pt_regs *ctx)
अणु
	जोड़ अणु
		u32 b32[2];
		u8 b8[8];
	पूर्ण key;
	अचिन्हित पूर्णांक i;

	key.b32[0] = 32;
	key.b8[4] = 192;
	key.b8[5] = 168;
	key.b8[6] = 0;
	key.b8[7] = 1;

#आशय clang loop unroll(full)
	क्रम (i = 0; i < 32; ++i)
		bpf_map_lookup_elem(&lpm_trie_map_alloc, &key);

	वापस 0;
पूर्ण

SEC("kprobe/" SYSCALL(sys_getpgid))
पूर्णांक stress_hash_map_lookup(काष्ठा pt_regs *ctx)
अणु
	u32 key = 1, i;
	दीर्घ *value;

#आशय clang loop unroll(full)
	क्रम (i = 0; i < 64; ++i)
		value = bpf_map_lookup_elem(&hash_map, &key);

	वापस 0;
पूर्ण

SEC("kprobe/" SYSCALL(sys_getppid))
पूर्णांक stress_array_map_lookup(काष्ठा pt_regs *ctx)
अणु
	u32 key = 1, i;
	दीर्घ *value;

#आशय clang loop unroll(full)
	क्रम (i = 0; i < 64; ++i)
		value = bpf_map_lookup_elem(&array_map, &key);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
