<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2019 Netronome Systems, Inc. */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <net/अगर.h>
#समावेश <sys/utsname.h>

#समावेश <linux/btf.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>

#समावेश "bpf.h"
#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"

अटल bool grep(स्थिर अक्षर *buffer, स्थिर अक्षर *pattern)
अणु
	वापस !!म_माला(buffer, pattern);
पूर्ण

अटल पूर्णांक get_venकरोr_id(पूर्णांक अगरindex)
अणु
	अक्षर अगरname[IF_NAMESIZE], path[64], buf[8];
	sमाप_प्रकार len;
	पूर्णांक fd;

	अगर (!अगर_indextoname(अगरindex, अगरname))
		वापस -1;

	snम_लिखो(path, माप(path), "/sys/class/net/%s/device/vendor", अगरname);

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0)
		वापस -1;

	len = पढ़ो(fd, buf, माप(buf));
	बंद(fd);
	अगर (len < 0)
		वापस -1;
	अगर (len >= (sमाप_प्रकार)माप(buf))
		वापस -1;
	buf[len] = '\0';

	वापस म_से_दीर्घ(buf, शून्य, 0);
पूर्ण

अटल पूर्णांक get_kernel_version(व्योम)
अणु
	पूर्णांक version, subversion, patchlevel;
	काष्ठा utsname utsn;

	/* Return 0 on failure, and attempt to probe with empty kversion */
	अगर (uname(&utsn))
		वापस 0;

	अगर (माला_पूछो(utsn.release, "%d.%d.%d",
		   &version, &subversion, &patchlevel) != 3)
		वापस 0;

	वापस (version << 16) + (subversion << 8) + patchlevel;
पूर्ण

अटल व्योम
probe_load(क्रमागत bpf_prog_type prog_type, स्थिर काष्ठा bpf_insn *insns,
	   माप_प्रकार insns_cnt, अक्षर *buf, माप_प्रकार buf_len, __u32 अगरindex)
अणु
	काष्ठा bpf_load_program_attr xattr = अणुपूर्ण;
	पूर्णांक fd;

	चयन (prog_type) अणु
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		xattr.expected_attach_type = BPF_CGROUP_INET4_CONNECT;
		अवरोध;
	हाल BPF_PROG_TYPE_SK_LOOKUP:
		xattr.expected_attach_type = BPF_SK_LOOKUP;
		अवरोध;
	हाल BPF_PROG_TYPE_KPROBE:
		xattr.kern_version = get_kernel_version();
		अवरोध;
	हाल BPF_PROG_TYPE_UNSPEC:
	हाल BPF_PROG_TYPE_SOCKET_FILTER:
	हाल BPF_PROG_TYPE_SCHED_CLS:
	हाल BPF_PROG_TYPE_SCHED_ACT:
	हाल BPF_PROG_TYPE_TRACEPOINT:
	हाल BPF_PROG_TYPE_XDP:
	हाल BPF_PROG_TYPE_PERF_EVENT:
	हाल BPF_PROG_TYPE_CGROUP_SKB:
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
	हाल BPF_PROG_TYPE_LWT_IN:
	हाल BPF_PROG_TYPE_LWT_OUT:
	हाल BPF_PROG_TYPE_LWT_XMIT:
	हाल BPF_PROG_TYPE_SOCK_OPS:
	हाल BPF_PROG_TYPE_SK_SKB:
	हाल BPF_PROG_TYPE_CGROUP_DEVICE:
	हाल BPF_PROG_TYPE_SK_MSG:
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT:
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE:
	हाल BPF_PROG_TYPE_LWT_SEG6LOCAL:
	हाल BPF_PROG_TYPE_LIRC_MODE2:
	हाल BPF_PROG_TYPE_SK_REUSEPORT:
	हाल BPF_PROG_TYPE_FLOW_DISSECTOR:
	हाल BPF_PROG_TYPE_CGROUP_SYSCTL:
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
	हाल BPF_PROG_TYPE_TRACING:
	हाल BPF_PROG_TYPE_STRUCT_OPS:
	हाल BPF_PROG_TYPE_EXT:
	हाल BPF_PROG_TYPE_LSM:
	शेष:
		अवरोध;
	पूर्ण

	xattr.prog_type = prog_type;
	xattr.insns = insns;
	xattr.insns_cnt = insns_cnt;
	xattr.license = "GPL";
	xattr.prog_अगरindex = अगरindex;

	fd = bpf_load_program_xattr(&xattr, buf, buf_len);
	अगर (fd >= 0)
		बंद(fd);
पूर्ण

bool bpf_probe_prog_type(क्रमागत bpf_prog_type prog_type, __u32 अगरindex)
अणु
	काष्ठा bpf_insn insns[2] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN()
	पूर्ण;

	अगर (अगरindex && prog_type == BPF_PROG_TYPE_SCHED_CLS)
		/* nfp वापसs -EINVAL on निकास(0) with TC offload */
		insns[0].imm = 2;

	त्रुटि_सं = 0;
	probe_load(prog_type, insns, ARRAY_SIZE(insns), शून्य, 0, अगरindex);

	वापस त्रुटि_सं != EINVAL && त्रुटि_सं != EOPNOTSUPP;
पूर्ण

पूर्णांक libbpf__load_raw_btf(स्थिर अक्षर *raw_types, माप_प्रकार types_len,
			 स्थिर अक्षर *str_sec, माप_प्रकार str_len)
अणु
	काष्ठा btf_header hdr = अणु
		.magic = BTF_MAGIC,
		.version = BTF_VERSION,
		.hdr_len = माप(काष्ठा btf_header),
		.type_len = types_len,
		.str_off = types_len,
		.str_len = str_len,
	पूर्ण;
	पूर्णांक btf_fd, btf_len;
	__u8 *raw_btf;

	btf_len = hdr.hdr_len + hdr.type_len + hdr.str_len;
	raw_btf = दो_स्मृति(btf_len);
	अगर (!raw_btf)
		वापस -ENOMEM;

	स_नकल(raw_btf, &hdr, माप(hdr));
	स_नकल(raw_btf + hdr.hdr_len, raw_types, hdr.type_len);
	स_नकल(raw_btf + hdr.hdr_len + hdr.type_len, str_sec, hdr.str_len);

	btf_fd = bpf_load_btf(raw_btf, btf_len, शून्य, 0, false);

	मुक्त(raw_btf);
	वापस btf_fd;
पूर्ण

अटल पूर्णांक load_local_storage_btf(व्योम)
अणु
	स्थिर अक्षर strs[] = "\0bpf_spin_lock\0val\0cnt\0l";
	/* काष्ठा bpf_spin_lock अणु
	 *   पूर्णांक val;
	 * पूर्ण;
	 * काष्ठा val अणु
	 *   पूर्णांक cnt;
	 *   काष्ठा bpf_spin_lock l;
	 * पूर्ण;
	 */
	__u32 types[] = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* काष्ठा bpf_spin_lock */                      /* [2] */
		BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),
		BTF_MEMBER_ENC(15, 1, 0), /* पूर्णांक val; */
		/* काष्ठा val */                                /* [3] */
		BTF_TYPE_ENC(15, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
		BTF_MEMBER_ENC(19, 1, 0), /* पूर्णांक cnt; */
		BTF_MEMBER_ENC(23, 2, 32),/* काष्ठा bpf_spin_lock l; */
	पूर्ण;

	वापस libbpf__load_raw_btf((अक्षर *)types, माप(types),
				     strs, माप(strs));
पूर्ण

bool bpf_probe_map_type(क्रमागत bpf_map_type map_type, __u32 अगरindex)
अणु
	पूर्णांक key_size, value_size, max_entries, map_flags;
	__u32 btf_key_type_id = 0, btf_value_type_id = 0;
	काष्ठा bpf_create_map_attr attr = अणुपूर्ण;
	पूर्णांक fd = -1, btf_fd = -1, fd_inner;

	key_size	= माप(__u32);
	value_size	= माप(__u32);
	max_entries	= 1;
	map_flags	= 0;

	चयन (map_type) अणु
	हाल BPF_MAP_TYPE_STACK_TRACE:
		value_size	= माप(__u64);
		अवरोध;
	हाल BPF_MAP_TYPE_LPM_TRIE:
		key_size	= माप(__u64);
		value_size	= माप(__u64);
		map_flags	= BPF_F_NO_PREALLOC;
		अवरोध;
	हाल BPF_MAP_TYPE_CGROUP_STORAGE:
	हाल BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE:
		key_size	= माप(काष्ठा bpf_cgroup_storage_key);
		value_size	= माप(__u64);
		max_entries	= 0;
		अवरोध;
	हाल BPF_MAP_TYPE_QUEUE:
	हाल BPF_MAP_TYPE_STACK:
		key_size	= 0;
		अवरोध;
	हाल BPF_MAP_TYPE_SK_STORAGE:
	हाल BPF_MAP_TYPE_INODE_STORAGE:
	हाल BPF_MAP_TYPE_TASK_STORAGE:
		btf_key_type_id = 1;
		btf_value_type_id = 3;
		value_size = 8;
		max_entries = 0;
		map_flags = BPF_F_NO_PREALLOC;
		btf_fd = load_local_storage_btf();
		अगर (btf_fd < 0)
			वापस false;
		अवरोध;
	हाल BPF_MAP_TYPE_RINGBUF:
		key_size = 0;
		value_size = 0;
		max_entries = 4096;
		अवरोध;
	हाल BPF_MAP_TYPE_UNSPEC:
	हाल BPF_MAP_TYPE_HASH:
	हाल BPF_MAP_TYPE_ARRAY:
	हाल BPF_MAP_TYPE_PROG_ARRAY:
	हाल BPF_MAP_TYPE_PERF_EVENT_ARRAY:
	हाल BPF_MAP_TYPE_PERCPU_HASH:
	हाल BPF_MAP_TYPE_PERCPU_ARRAY:
	हाल BPF_MAP_TYPE_CGROUP_ARRAY:
	हाल BPF_MAP_TYPE_LRU_HASH:
	हाल BPF_MAP_TYPE_LRU_PERCPU_HASH:
	हाल BPF_MAP_TYPE_ARRAY_OF_MAPS:
	हाल BPF_MAP_TYPE_HASH_OF_MAPS:
	हाल BPF_MAP_TYPE_DEVMAP:
	हाल BPF_MAP_TYPE_DEVMAP_HASH:
	हाल BPF_MAP_TYPE_SOCKMAP:
	हाल BPF_MAP_TYPE_CPUMAP:
	हाल BPF_MAP_TYPE_XSKMAP:
	हाल BPF_MAP_TYPE_SOCKHASH:
	हाल BPF_MAP_TYPE_REUSEPORT_SOCKARRAY:
	हाल BPF_MAP_TYPE_STRUCT_OPS:
	शेष:
		अवरोध;
	पूर्ण

	अगर (map_type == BPF_MAP_TYPE_ARRAY_OF_MAPS ||
	    map_type == BPF_MAP_TYPE_HASH_OF_MAPS) अणु
		/* TODO: probe क्रम device, once libbpf has a function to create
		 * map-in-map क्रम offload
		 */
		अगर (अगरindex)
			वापस false;

		fd_inner = bpf_create_map(BPF_MAP_TYPE_HASH,
					  माप(__u32), माप(__u32), 1, 0);
		अगर (fd_inner < 0)
			वापस false;
		fd = bpf_create_map_in_map(map_type, शून्य, माप(__u32),
					   fd_inner, 1, 0);
		बंद(fd_inner);
	पूर्ण अन्यथा अणु
		/* Note: No other restriction on map type probes क्रम offload */
		attr.map_type = map_type;
		attr.key_size = key_size;
		attr.value_size = value_size;
		attr.max_entries = max_entries;
		attr.map_flags = map_flags;
		attr.map_अगरindex = अगरindex;
		अगर (btf_fd >= 0) अणु
			attr.btf_fd = btf_fd;
			attr.btf_key_type_id = btf_key_type_id;
			attr.btf_value_type_id = btf_value_type_id;
		पूर्ण

		fd = bpf_create_map_xattr(&attr);
	पूर्ण
	अगर (fd >= 0)
		बंद(fd);
	अगर (btf_fd >= 0)
		बंद(btf_fd);

	वापस fd >= 0;
पूर्ण

bool bpf_probe_helper(क्रमागत bpf_func_id id, क्रमागत bpf_prog_type prog_type,
		      __u32 अगरindex)
अणु
	काष्ठा bpf_insn insns[2] = अणु
		BPF_EMIT_CALL(id),
		BPF_EXIT_INSN()
	पूर्ण;
	अक्षर buf[4096] = अणुपूर्ण;
	bool res;

	probe_load(prog_type, insns, ARRAY_SIZE(insns), buf, माप(buf),
		   अगरindex);
	res = !grep(buf, "invalid func ") && !grep(buf, "unknown func ");

	अगर (अगरindex) अणु
		चयन (get_venकरोr_id(अगरindex)) अणु
		हाल 0x19ee: /* Netronome specअगरic */
			res = res && !grep(buf, "not supported by FW") &&
				!grep(buf, "unsupported function id");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

/*
 * Probe क्रम availability of kernel commit (5.3):
 *
 * c04c0d2b968a ("bpf: increase complexity limit and maximum program size")
 */
bool bpf_probe_large_insn_limit(__u32 अगरindex)
अणु
	काष्ठा bpf_insn insns[BPF_MAXINSNS + 1];
	पूर्णांक i;

	क्रम (i = 0; i < BPF_MAXINSNS; i++)
		insns[i] = BPF_MOV64_IMM(BPF_REG_0, 1);
	insns[BPF_MAXINSNS] = BPF_EXIT_INSN();

	त्रुटि_सं = 0;
	probe_load(BPF_PROG_TYPE_SCHED_CLS, insns, ARRAY_SIZE(insns), शून्य, 0,
		   अगरindex);

	वापस त्रुटि_सं != E2BIG && त्रुटि_सं != EINVAL;
पूर्ण
