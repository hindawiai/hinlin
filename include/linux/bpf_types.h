<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* पूर्णांकernal file - करो not include directly */

#अगर_घोषित CONFIG_NET
BPF_PROG_TYPE(BPF_PROG_TYPE_SOCKET_FILTER, sk_filter,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_SCHED_CLS, tc_cls_act,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_SCHED_ACT, tc_cls_act,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_XDP, xdp,
	      काष्ठा xdp_md, काष्ठा xdp_buff)
#अगर_घोषित CONFIG_CGROUP_BPF
BPF_PROG_TYPE(BPF_PROG_TYPE_CGROUP_SKB, cg_skb,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_CGROUP_SOCK, cg_sock,
	      काष्ठा bpf_sock, काष्ठा sock)
BPF_PROG_TYPE(BPF_PROG_TYPE_CGROUP_SOCK_ADDR, cg_sock_addr,
	      काष्ठा bpf_sock_addr, काष्ठा bpf_sock_addr_kern)
#पूर्ण_अगर
BPF_PROG_TYPE(BPF_PROG_TYPE_LWT_IN, lwt_in,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_LWT_OUT, lwt_out,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_LWT_XMIT, lwt_xmit,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_LWT_SEG6LOCAL, lwt_seg6local,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_SOCK_OPS, sock_ops,
	      काष्ठा bpf_sock_ops, काष्ठा bpf_sock_ops_kern)
BPF_PROG_TYPE(BPF_PROG_TYPE_SK_SKB, sk_skb,
	      काष्ठा __sk_buff, काष्ठा sk_buff)
BPF_PROG_TYPE(BPF_PROG_TYPE_SK_MSG, sk_msg,
	      काष्ठा sk_msg_md, काष्ठा sk_msg)
BPF_PROG_TYPE(BPF_PROG_TYPE_FLOW_DISSECTOR, flow_dissector,
	      काष्ठा __sk_buff, काष्ठा bpf_flow_dissector)
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_EVENTS
BPF_PROG_TYPE(BPF_PROG_TYPE_KPROBE, kprobe,
	      bpf_user_pt_regs_t, काष्ठा pt_regs)
BPF_PROG_TYPE(BPF_PROG_TYPE_TRACEPOINT, tracepoपूर्णांक,
	      __u64, u64)
BPF_PROG_TYPE(BPF_PROG_TYPE_PERF_EVENT, perf_event,
	      काष्ठा bpf_perf_event_data, काष्ठा bpf_perf_event_data_kern)
BPF_PROG_TYPE(BPF_PROG_TYPE_RAW_TRACEPOINT, raw_tracepoपूर्णांक,
	      काष्ठा bpf_raw_tracepoपूर्णांक_args, u64)
BPF_PROG_TYPE(BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE, raw_tracepoपूर्णांक_writable,
	      काष्ठा bpf_raw_tracepoपूर्णांक_args, u64)
BPF_PROG_TYPE(BPF_PROG_TYPE_TRACING, tracing,
	      व्योम *, व्योम *)
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_BPF
BPF_PROG_TYPE(BPF_PROG_TYPE_CGROUP_DEVICE, cg_dev,
	      काष्ठा bpf_cgroup_dev_ctx, काष्ठा bpf_cgroup_dev_ctx)
BPF_PROG_TYPE(BPF_PROG_TYPE_CGROUP_SYSCTL, cg_sysctl,
	      काष्ठा bpf_sysctl, काष्ठा bpf_sysctl_kern)
BPF_PROG_TYPE(BPF_PROG_TYPE_CGROUP_SOCKOPT, cg_sockopt,
	      काष्ठा bpf_sockopt, काष्ठा bpf_sockopt_kern)
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_LIRC_MODE2
BPF_PROG_TYPE(BPF_PROG_TYPE_LIRC_MODE2, lirc_mode2,
	      __u32, u32)
#पूर्ण_अगर
#अगर_घोषित CONFIG_INET
BPF_PROG_TYPE(BPF_PROG_TYPE_SK_REUSEPORT, sk_reuseport,
	      काष्ठा sk_reuseport_md, काष्ठा sk_reuseport_kern)
BPF_PROG_TYPE(BPF_PROG_TYPE_SK_LOOKUP, sk_lookup,
	      काष्ठा bpf_sk_lookup, काष्ठा bpf_sk_lookup_kern)
#पूर्ण_अगर
#अगर defined(CONFIG_BPF_JIT)
BPF_PROG_TYPE(BPF_PROG_TYPE_STRUCT_OPS, bpf_काष्ठा_ops,
	      व्योम *, व्योम *)
BPF_PROG_TYPE(BPF_PROG_TYPE_EXT, bpf_extension,
	      व्योम *, व्योम *)
#अगर_घोषित CONFIG_BPF_LSM
BPF_PROG_TYPE(BPF_PROG_TYPE_LSM, lsm,
	       व्योम *, व्योम *)
#पूर्ण_अगर /* CONFIG_BPF_LSM */
#पूर्ण_अगर

BPF_MAP_TYPE(BPF_MAP_TYPE_ARRAY, array_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PERCPU_ARRAY, percpu_array_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PROG_ARRAY, prog_array_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PERF_EVENT_ARRAY, perf_event_array_map_ops)
#अगर_घोषित CONFIG_CGROUPS
BPF_MAP_TYPE(BPF_MAP_TYPE_CGROUP_ARRAY, cgroup_array_map_ops)
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_BPF
BPF_MAP_TYPE(BPF_MAP_TYPE_CGROUP_STORAGE, cgroup_storage_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE, cgroup_storage_map_ops)
#पूर्ण_अगर
BPF_MAP_TYPE(BPF_MAP_TYPE_HASH, htab_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PERCPU_HASH, htab_percpu_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_LRU_HASH, htab_lru_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_LRU_PERCPU_HASH, htab_lru_percpu_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_LPM_TRIE, trie_map_ops)
#अगर_घोषित CONFIG_PERF_EVENTS
BPF_MAP_TYPE(BPF_MAP_TYPE_STACK_TRACE, stack_trace_map_ops)
#पूर्ण_अगर
BPF_MAP_TYPE(BPF_MAP_TYPE_ARRAY_OF_MAPS, array_of_maps_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_HASH_OF_MAPS, htab_of_maps_map_ops)
#अगर_घोषित CONFIG_NET
BPF_MAP_TYPE(BPF_MAP_TYPE_DEVMAP, dev_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_DEVMAP_HASH, dev_map_hash_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_SK_STORAGE, sk_storage_map_ops)
#अगर_घोषित CONFIG_BPF_LSM
BPF_MAP_TYPE(BPF_MAP_TYPE_INODE_STORAGE, inode_storage_map_ops)
#पूर्ण_अगर
BPF_MAP_TYPE(BPF_MAP_TYPE_TASK_STORAGE, task_storage_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_CPUMAP, cpu_map_ops)
#अगर defined(CONFIG_XDP_SOCKETS)
BPF_MAP_TYPE(BPF_MAP_TYPE_XSKMAP, xsk_map_ops)
#पूर्ण_अगर
#अगर_घोषित CONFIG_INET
BPF_MAP_TYPE(BPF_MAP_TYPE_SOCKMAP, sock_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_SOCKHASH, sock_hash_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY, reuseport_array_ops)
#पूर्ण_अगर
#पूर्ण_अगर
BPF_MAP_TYPE(BPF_MAP_TYPE_QUEUE, queue_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_STACK, stack_map_ops)
#अगर defined(CONFIG_BPF_JIT)
BPF_MAP_TYPE(BPF_MAP_TYPE_STRUCT_OPS, bpf_काष्ठा_ops_map_ops)
#पूर्ण_अगर
BPF_MAP_TYPE(BPF_MAP_TYPE_RINGBUF, ringbuf_map_ops)

BPF_LINK_TYPE(BPF_LINK_TYPE_RAW_TRACEPOINT, raw_tracepoपूर्णांक)
BPF_LINK_TYPE(BPF_LINK_TYPE_TRACING, tracing)
#अगर_घोषित CONFIG_CGROUP_BPF
BPF_LINK_TYPE(BPF_LINK_TYPE_CGROUP, cgroup)
#पूर्ण_अगर
BPF_LINK_TYPE(BPF_LINK_TYPE_ITER, iter)
#अगर_घोषित CONFIG_NET
BPF_LINK_TYPE(BPF_LINK_TYPE_NETNS, netns)
#पूर्ण_अगर
