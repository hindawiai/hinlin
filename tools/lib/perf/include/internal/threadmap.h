<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_THREADMAP_H
#घोषणा __LIBPERF_INTERNAL_THREADMAP_H

#समावेश <linux/refcount.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>

काष्ठा thपढ़ो_map_data अणु
	pid_t	 pid;
	अक्षर	*comm;
पूर्ण;

काष्ठा perf_thपढ़ो_map अणु
	refcount_t	refcnt;
	पूर्णांक		nr;
	पूर्णांक		err_thपढ़ो;
	काष्ठा thपढ़ो_map_data map[];
पूर्ण;

काष्ठा perf_thपढ़ो_map *perf_thपढ़ो_map__पुनः_स्मृति(काष्ठा perf_thपढ़ो_map *map, पूर्णांक nr);

#पूर्ण_अगर /* __LIBPERF_INTERNAL_THREADMAP_H */
