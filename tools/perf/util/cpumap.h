<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_CPUMAP_H
#घोषणा __PERF_CPUMAP_H

#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश <perf/cpumap.h>

काष्ठा aggr_cpu_id अणु
	पूर्णांक thपढ़ो;
	पूर्णांक node;
	पूर्णांक socket;
	पूर्णांक die;
	पूर्णांक core;
पूर्ण;

काष्ठा cpu_aggr_map अणु
	refcount_t refcnt;
	पूर्णांक nr;
	काष्ठा aggr_cpu_id map[];
पूर्ण;

काष्ठा perf_record_cpu_map_data;

काष्ठा perf_cpu_map *perf_cpu_map__empty_new(पूर्णांक nr);
काष्ठा cpu_aggr_map *cpu_aggr_map__empty_new(पूर्णांक nr);

काष्ठा perf_cpu_map *cpu_map__new_data(काष्ठा perf_record_cpu_map_data *data);
माप_प्रकार cpu_map__snprपूर्णांक(काष्ठा perf_cpu_map *map, अक्षर *buf, माप_प्रकार size);
माप_प्रकार cpu_map__snprपूर्णांक_mask(काष्ठा perf_cpu_map *map, अक्षर *buf, माप_प्रकार size);
माप_प्रकार cpu_map__ख_लिखो(काष्ठा perf_cpu_map *map, खाता *fp);
पूर्णांक cpu_map__get_socket_id(पूर्णांक cpu);
काष्ठा aggr_cpu_id cpu_map__get_socket(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data);
पूर्णांक cpu_map__get_die_id(पूर्णांक cpu);
काष्ठा aggr_cpu_id cpu_map__get_die(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data);
पूर्णांक cpu_map__get_core_id(पूर्णांक cpu);
काष्ठा aggr_cpu_id cpu_map__get_core(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data);
पूर्णांक cpu_map__get_node_id(पूर्णांक cpu);
काष्ठा aggr_cpu_id  cpu_map__get_node(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data);
पूर्णांक cpu_map__build_socket_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **sockp);
पूर्णांक cpu_map__build_die_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **diep);
पूर्णांक cpu_map__build_core_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **corep);
पूर्णांक cpu_map__build_node_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **nodep);
स्थिर काष्ठा perf_cpu_map *cpu_map__online(व्योम); /* thपढ़ो unsafe */

अटल अंतरभूत पूर्णांक cpu_map__socket(काष्ठा perf_cpu_map *sock, पूर्णांक s)
अणु
	अगर (!sock || s > sock->nr || s < 0)
		वापस 0;
	वापस sock->map[s];
पूर्ण

पूर्णांक cpu__setup_cpunode_map(व्योम);

पूर्णांक cpu__max_node(व्योम);
पूर्णांक cpu__max_cpu(व्योम);
पूर्णांक cpu__max_present_cpu(व्योम);
पूर्णांक cpu__get_node(पूर्णांक cpu);

पूर्णांक cpu_map__build_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **res,
		       काष्ठा aggr_cpu_id (*f)(काष्ठा perf_cpu_map *map, पूर्णांक cpu, व्योम *data),
		       व्योम *data);

पूर्णांक cpu_map__cpu(काष्ठा perf_cpu_map *cpus, पूर्णांक idx);
bool cpu_map__has(काष्ठा perf_cpu_map *cpus, पूर्णांक cpu);

bool cpu_map__compare_aggr_cpu_id(काष्ठा aggr_cpu_id a, काष्ठा aggr_cpu_id b);
bool cpu_map__aggr_cpu_id_is_empty(काष्ठा aggr_cpu_id a);
काष्ठा aggr_cpu_id cpu_map__empty_aggr_cpu_id(व्योम);

#पूर्ण_अगर /* __PERF_CPUMAP_H */
