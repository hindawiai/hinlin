<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <bpf.h>

काष्ठा bpf_map SEC("maps") __bpf_मानक_निकास__ = अणु
       .type = BPF_MAP_TYPE_PERF_EVENT_ARRAY,
       .key_size = माप(पूर्णांक),
       .value_size = माप(u32),
       .max_entries = __NR_CPUS__,
पूर्ण;

#घोषणा माला_दो(from) \
	(अणु स्थिर पूर्णांक __len = माप(from); \
	   अक्षर __from[__len] = from; \
	   perf_event_output(args, &__bpf_मानक_निकास__, BPF_F_CURRENT_CPU, \
			  &__from, __len & (माप(from) - 1)); पूर्ण)
