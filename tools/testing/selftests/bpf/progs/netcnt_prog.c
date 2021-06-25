<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <linux/version.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश "netcnt_common.h"

#घोषणा MAX_BPS	(3 * 1024 * 1024)

#घोषणा REFRESH_TIME_NS	100000000
#घोषणा NS_PER_SEC	1000000000

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE);
	__type(key, काष्ठा bpf_cgroup_storage_key);
	__type(value, काष्ठा percpu_net_cnt);
पूर्ण percpu_netcnt SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_STORAGE);
	__type(key, काष्ठा bpf_cgroup_storage_key);
	__type(value, काष्ठा net_cnt);
पूर्ण netcnt SEC(".maps");

SEC("cgroup/skb")
पूर्णांक bpf_nextcnt(काष्ठा __sk_buff *skb)
अणु
	काष्ठा percpu_net_cnt *percpu_cnt;
	अक्षर fmt[] = "%d %llu %llu\n";
	काष्ठा net_cnt *cnt;
	__u64 ts, dt;
	पूर्णांक ret;

	cnt = bpf_get_local_storage(&netcnt, 0);
	percpu_cnt = bpf_get_local_storage(&percpu_netcnt, 0);

	percpu_cnt->packets++;
	percpu_cnt->bytes += skb->len;

	अगर (percpu_cnt->packets > MAX_PERCPU_PACKETS) अणु
		__sync_fetch_and_add(&cnt->packets,
				     percpu_cnt->packets);
		percpu_cnt->packets = 0;

		__sync_fetch_and_add(&cnt->bytes,
				     percpu_cnt->bytes);
		percpu_cnt->bytes = 0;
	पूर्ण

	ts = bpf_kसमय_get_ns();
	dt = ts - percpu_cnt->prev_ts;

	dt *= MAX_BPS;
	dt /= NS_PER_SEC;

	अगर (cnt->bytes + percpu_cnt->bytes - percpu_cnt->prev_bytes < dt)
		ret = 1;
	अन्यथा
		ret = 0;

	अगर (dt > REFRESH_TIME_NS) अणु
		percpu_cnt->prev_ts = ts;
		percpu_cnt->prev_packets = cnt->packets;
		percpu_cnt->prev_bytes = cnt->bytes;
	पूर्ण

	वापस !!ret;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = LINUX_VERSION_CODE;
