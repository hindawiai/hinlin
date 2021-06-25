<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB

/**
 * ibumad BPF sample kernel side
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * Copyright(c) 2018 Ira Weiny, Intel Corporation
 */

#घोषणा KBUILD_MODNAME "ibumad_count_pkts_by_class"
#समावेश <uapi/linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>


काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32); /* class; u32 required */
	__type(value, u64); /* count of mads पढ़ो */
	__uपूर्णांक(max_entries, 256); /* Room क्रम all Classes */
पूर्ण पढ़ो_count SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32); /* class; u32 required */
	__type(value, u64); /* count of mads written */
	__uपूर्णांक(max_entries, 256); /* Room क्रम all Classes */
पूर्ण ग_लिखो_count SEC(".maps");

#अघोषित DEBUG
#अगर_अघोषित DEBUG
#अघोषित bpf_prपूर्णांकk
#घोषणा bpf_prपूर्णांकk(fmt, ...)
#पूर्ण_अगर

/* Taken from the current क्रमmat defined in
 * include/trace/events/ib_umad.h
 * and
 * /sys/kernel/debug/tracing/events/ib_umad/ib_umad_पढ़ो/क्रमmat
 * /sys/kernel/debug/tracing/events/ib_umad/ib_umad_ग_लिखो/क्रमmat
 */
काष्ठा ib_umad_rw_args अणु
	u64 pad;
	u8 port_num;
	u8 sl;
	u8 path_bits;
	u8 grh_present;
	u32 id;
	u32 status;
	u32 समयout_ms;
	u32 retires;
	u32 length;
	u32 qpn;
	u32 qkey;
	u8 gid_index;
	u8 hop_limit;
	u16 lid;
	u16 attr_id;
	u16 pkey_index;
	u8 base_version;
	u8 mgmt_class;
	u8 class_version;
	u8 method;
	u32 flow_label;
	u16 mad_status;
	u16 class_specअगरic;
	u32 attr_mod;
	u64 tid;
	u8 gid[16];
	u32 dev_index;
	u8 traffic_class;
पूर्ण;

SEC("tracepoint/ib_umad/ib_umad_read_recv")
पूर्णांक on_ib_umad_पढ़ो_recv(काष्ठा ib_umad_rw_args *ctx)
अणु
	u64 zero = 0, *val;
	u8 class = ctx->mgmt_class;

	bpf_prपूर्णांकk("ib_umad read recv : class 0x%x\n", class);

	val = bpf_map_lookup_elem(&पढ़ो_count, &class);
	अगर (!val) अणु
		bpf_map_update_elem(&पढ़ो_count, &class, &zero, BPF_NOEXIST);
		val = bpf_map_lookup_elem(&पढ़ो_count, &class);
		अगर (!val)
			वापस 0;
	पूर्ण

	(*val) += 1;

	वापस 0;
पूर्ण
SEC("tracepoint/ib_umad/ib_umad_read_send")
पूर्णांक on_ib_umad_पढ़ो_send(काष्ठा ib_umad_rw_args *ctx)
अणु
	u64 zero = 0, *val;
	u8 class = ctx->mgmt_class;

	bpf_prपूर्णांकk("ib_umad read send : class 0x%x\n", class);

	val = bpf_map_lookup_elem(&पढ़ो_count, &class);
	अगर (!val) अणु
		bpf_map_update_elem(&पढ़ो_count, &class, &zero, BPF_NOEXIST);
		val = bpf_map_lookup_elem(&पढ़ो_count, &class);
		अगर (!val)
			वापस 0;
	पूर्ण

	(*val) += 1;

	वापस 0;
पूर्ण
SEC("tracepoint/ib_umad/ib_umad_write")
पूर्णांक on_ib_umad_ग_लिखो(काष्ठा ib_umad_rw_args *ctx)
अणु
	u64 zero = 0, *val;
	u8 class = ctx->mgmt_class;

	bpf_prपूर्णांकk("ib_umad write : class 0x%x\n", class);

	val = bpf_map_lookup_elem(&ग_लिखो_count, &class);
	अगर (!val) अणु
		bpf_map_update_elem(&ग_लिखो_count, &class, &zero, BPF_NOEXIST);
		val = bpf_map_lookup_elem(&ग_लिखो_count, &class);
		अगर (!val)
			वापस 0;
	पूर्ण

	(*val) += 1;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
