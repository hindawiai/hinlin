<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
#अगर_अघोषित __LIBPERF_BPF_PERF_H
#घोषणा __LIBPERF_BPF_PERF_H

#समावेश <linux/types.h>  /* क्रम __u32 */

/*
 * bpf_perf uses a hashmap, the attr_map, to track all the leader programs.
 * The hashmap is pinned in bpffs. flock() on this file is used to ensure
 * no concurrent access to the attr_map.  The key of attr_map is काष्ठा
 * perf_event_attr, and the value is काष्ठा perf_event_attr_map_entry.
 *
 * काष्ठा perf_event_attr_map_entry contains two __u32 IDs, bpf_link of the
 * leader prog, and the dअगरf_map. Each perf-stat session holds a reference
 * to the bpf_link to make sure the leader prog is attached to sched_चयन
 * tracepoपूर्णांक.
 *
 * Since the hashmap only contains IDs of the bpf_link and dअगरf_map, it
 * करोes not hold any references to the leader program. Once all perf-stat
 * sessions of these events निकास, the leader prog, its maps, and the
 * perf_events will be मुक्तd.
 */
काष्ठा perf_event_attr_map_entry अणु
	__u32 link_id;
	__u32 dअगरf_map_id;
पूर्ण;

/* शेष attr_map name */
#घोषणा BPF_PERF_DEFAULT_ATTR_MAP_PATH "perf_attr_map"

#पूर्ण_अगर /* __LIBPERF_BPF_PERF_H */
