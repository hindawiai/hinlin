<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1

#अगर_अघोषित _PERF_BPF_PID_FILTER_
#घोषणा _PERF_BPF_PID_FILTER_

#समावेश <bpf.h>

#घोषणा pid_filter(name) pid_map(name, bool)

अटल पूर्णांक pid_filter__add(काष्ठा bpf_map *pids, pid_t pid)
अणु
	bool value = true;
	वापस bpf_map_update_elem(pids, &pid, &value, BPF_NOEXIST);
पूर्ण

अटल bool pid_filter__has(काष्ठा bpf_map *pids, pid_t pid)
अणु
	वापस bpf_map_lookup_elem(pids, &pid) != शून्य;
पूर्ण

#पूर्ण_अगर // _PERF_BPF_PID_FILTER_
