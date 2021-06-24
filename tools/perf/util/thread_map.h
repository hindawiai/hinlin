<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_THREAD_MAP_H
#घोषणा __PERF_THREAD_MAP_H

#समावेश <sys/types.h>
#समावेश <मानकपन.स>
#समावेश <linux/refcount.h>
#समावेश <पूर्णांकernal/thपढ़ोmap.h>
#समावेश <perf/thपढ़ोmap.h>

काष्ठा perf_record_thपढ़ो_map;

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_dummy(व्योम);
काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_pid(pid_t pid);
काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_tid(pid_t tid);
काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_uid(uid_t uid);
काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_all_cpus(व्योम);
काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new(pid_t pid, pid_t tid, uid_t uid);
काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_event(काष्ठा perf_record_thपढ़ो_map *event);

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_str(स्थिर अक्षर *pid,
		स्थिर अक्षर *tid, uid_t uid, bool all_thपढ़ोs);

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_tid_str(स्थिर अक्षर *tid_str);

माप_प्रकार thपढ़ो_map__ख_लिखो(काष्ठा perf_thपढ़ो_map *thपढ़ोs, खाता *fp);

व्योम thपढ़ो_map__पढ़ो_comms(काष्ठा perf_thपढ़ो_map *thपढ़ोs);
bool thपढ़ो_map__has(काष्ठा perf_thपढ़ो_map *thपढ़ोs, pid_t pid);
पूर्णांक thपढ़ो_map__हटाओ(काष्ठा perf_thपढ़ो_map *thपढ़ोs, पूर्णांक idx);
#पूर्ण_अगर	/* __PERF_THREAD_MAP_H */
