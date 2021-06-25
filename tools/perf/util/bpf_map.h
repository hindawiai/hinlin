<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
#अगर_अघोषित __PERF_BPF_MAP_H
#घोषणा __PERF_BPF_MAP_H 1

#समावेश <मानकपन.स>
#समावेश <linux/compiler.h>
काष्ठा bpf_map;

#अगर_घोषित HAVE_LIBBPF_SUPPORT

पूर्णांक bpf_map__ख_लिखो(काष्ठा bpf_map *map, खाता *fp);

#अन्यथा

अटल अंतरभूत पूर्णांक bpf_map__ख_लिखो(काष्ठा bpf_map *map __maybe_unused, खाता *fp __maybe_unused)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

#पूर्ण_अगर // __PERF_BPF_MAP_H
