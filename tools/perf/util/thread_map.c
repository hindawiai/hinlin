<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश "string2.h"
#समावेश "strlist.h"
#समावेश <माला.स>
#समावेश <api/fs/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश "asm/bug.h"
#समावेश "thread_map.h"
#समावेश "debug.h"
#समावेश "event.h"

/* Skip "." and ".." directories */
अटल पूर्णांक filter(स्थिर काष्ठा dirent *dir)
अणु
	अगर (dir->d_name[0] == '.')
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

#घोषणा thपढ़ो_map__alloc(__nr) perf_thपढ़ो_map__पुनः_स्मृति(शून्य, __nr)

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_pid(pid_t pid)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	अक्षर name[256];
	पूर्णांक items;
	काष्ठा dirent **namelist = शून्य;
	पूर्णांक i;

	प्र_लिखो(name, "/proc/%d/task", pid);
	items = scandir(name, &namelist, filter, शून्य);
	अगर (items <= 0)
		वापस शून्य;

	thपढ़ोs = thपढ़ो_map__alloc(items);
	अगर (thपढ़ोs != शून्य) अणु
		क्रम (i = 0; i < items; i++)
			perf_thपढ़ो_map__set_pid(thपढ़ोs, i, म_से_प(namelist[i]->d_name));
		thपढ़ोs->nr = items;
		refcount_set(&thपढ़ोs->refcnt, 1);
	पूर्ण

	क्रम (i=0; i<items; i++)
		zमुक्त(&namelist[i]);
	मुक्त(namelist);

	वापस thपढ़ोs;
पूर्ण

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_tid(pid_t tid)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = thपढ़ो_map__alloc(1);

	अगर (thपढ़ोs != शून्य) अणु
		perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, tid);
		thपढ़ोs->nr = 1;
		refcount_set(&thपढ़ोs->refcnt, 1);
	पूर्ण

	वापस thपढ़ोs;
पूर्ण

अटल काष्ठा perf_thपढ़ो_map *__thपढ़ो_map__new_all_cpus(uid_t uid)
अणु
	सूची *proc;
	पूर्णांक max_thपढ़ोs = 32, items, i;
	अक्षर path[NAME_MAX + 1 + 6];
	काष्ठा dirent *dirent, **namelist = शून्य;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = thपढ़ो_map__alloc(max_thपढ़ोs);

	अगर (thपढ़ोs == शून्य)
		जाओ out;

	proc = सूची_खोलो("/proc");
	अगर (proc == शून्य)
		जाओ out_मुक्त_thपढ़ोs;

	thपढ़ोs->nr = 0;
	refcount_set(&thपढ़ोs->refcnt, 1);

	जबतक ((dirent = सूची_पढ़ो(proc)) != शून्य) अणु
		अक्षर *end;
		bool grow = false;
		pid_t pid = म_से_दीर्घ(dirent->d_name, &end, 10);

		अगर (*end) /* only पूर्णांकerested in proper numerical dirents */
			जारी;

		snम_लिखो(path, माप(path), "/proc/%s", dirent->d_name);

		अगर (uid != अच_पूर्णांक_उच्च) अणु
			काष्ठा stat st;

			अगर (stat(path, &st) != 0 || st.st_uid != uid)
				जारी;
		पूर्ण

		snम_लिखो(path, माप(path), "/proc/%d/task", pid);
		items = scandir(path, &namelist, filter, शून्य);
		अगर (items <= 0)
			जाओ out_मुक्त_बंद_सूची;

		जबतक (thपढ़ोs->nr + items >= max_thपढ़ोs) अणु
			max_thपढ़ोs *= 2;
			grow = true;
		पूर्ण

		अगर (grow) अणु
			काष्ठा perf_thपढ़ो_map *पंचांगp;

			पंचांगp = perf_thपढ़ो_map__पुनः_स्मृति(thपढ़ोs, max_thपढ़ोs);
			अगर (पंचांगp == शून्य)
				जाओ out_मुक्त_namelist;

			thपढ़ोs = पंचांगp;
		पूर्ण

		क्रम (i = 0; i < items; i++) अणु
			perf_thपढ़ो_map__set_pid(thपढ़ोs, thपढ़ोs->nr + i,
						    म_से_प(namelist[i]->d_name));
		पूर्ण

		क्रम (i = 0; i < items; i++)
			zमुक्त(&namelist[i]);
		मुक्त(namelist);

		thपढ़ोs->nr += items;
	पूर्ण

out_बंद_सूची:
	बंद_सूची(proc);
out:
	वापस thपढ़ोs;

out_मुक्त_thपढ़ोs:
	मुक्त(thपढ़ोs);
	वापस शून्य;

out_मुक्त_namelist:
	क्रम (i = 0; i < items; i++)
		zमुक्त(&namelist[i]);
	मुक्त(namelist);

out_मुक्त_बंद_सूची:
	zमुक्त(&thपढ़ोs);
	जाओ out_बंद_सूची;
पूर्ण

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_all_cpus(व्योम)
अणु
	वापस __thपढ़ो_map__new_all_cpus(अच_पूर्णांक_उच्च);
पूर्ण

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_uid(uid_t uid)
अणु
	वापस __thपढ़ो_map__new_all_cpus(uid);
पूर्ण

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new(pid_t pid, pid_t tid, uid_t uid)
अणु
	अगर (pid != -1)
		वापस thपढ़ो_map__new_by_pid(pid);

	अगर (tid == -1 && uid != अच_पूर्णांक_उच्च)
		वापस thपढ़ो_map__new_by_uid(uid);

	वापस thपढ़ो_map__new_by_tid(tid);
पूर्ण

अटल काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_pid_str(स्थिर अक्षर *pid_str)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य, *nt;
	अक्षर name[256];
	पूर्णांक items, total_tasks = 0;
	काष्ठा dirent **namelist = शून्य;
	पूर्णांक i, j = 0;
	pid_t pid, prev_pid = पूर्णांक_उच्च;
	अक्षर *end_ptr;
	काष्ठा str_node *pos;
	काष्ठा strlist_config slist_config = अणु .करोnt_dupstr = true, पूर्ण;
	काष्ठा strlist *slist = strlist__new(pid_str, &slist_config);

	अगर (!slist)
		वापस शून्य;

	strlist__क्रम_each_entry(pos, slist) अणु
		pid = म_से_दीर्घ(pos->s, &end_ptr, 10);

		अगर (pid == पूर्णांक_न्यून || pid == पूर्णांक_उच्च ||
		    (*end_ptr != '\0' && *end_ptr != ','))
			जाओ out_मुक्त_thपढ़ोs;

		अगर (pid == prev_pid)
			जारी;

		प्र_लिखो(name, "/proc/%d/task", pid);
		items = scandir(name, &namelist, filter, शून्य);
		अगर (items <= 0)
			जाओ out_मुक्त_thपढ़ोs;

		total_tasks += items;
		nt = perf_thपढ़ो_map__पुनः_स्मृति(thपढ़ोs, total_tasks);
		अगर (nt == शून्य)
			जाओ out_मुक्त_namelist;

		thपढ़ोs = nt;

		क्रम (i = 0; i < items; i++) अणु
			perf_thपढ़ो_map__set_pid(thपढ़ोs, j++, म_से_प(namelist[i]->d_name));
			zमुक्त(&namelist[i]);
		पूर्ण
		thपढ़ोs->nr = total_tasks;
		मुक्त(namelist);
	पूर्ण

out:
	strlist__delete(slist);
	अगर (thपढ़ोs)
		refcount_set(&thपढ़ोs->refcnt, 1);
	वापस thपढ़ोs;

out_मुक्त_namelist:
	क्रम (i = 0; i < items; i++)
		zमुक्त(&namelist[i]);
	मुक्त(namelist);

out_मुक्त_thपढ़ोs:
	zमुक्त(&thपढ़ोs);
	जाओ out;
पूर्ण

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_by_tid_str(स्थिर अक्षर *tid_str)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य, *nt;
	पूर्णांक ntasks = 0;
	pid_t tid, prev_tid = पूर्णांक_उच्च;
	अक्षर *end_ptr;
	काष्ठा str_node *pos;
	काष्ठा strlist_config slist_config = अणु .करोnt_dupstr = true, पूर्ण;
	काष्ठा strlist *slist;

	/* perf-stat expects thपढ़ोs to be generated even अगर tid not given */
	अगर (!tid_str)
		वापस perf_thपढ़ो_map__new_dummy();

	slist = strlist__new(tid_str, &slist_config);
	अगर (!slist)
		वापस शून्य;

	strlist__क्रम_each_entry(pos, slist) अणु
		tid = म_से_दीर्घ(pos->s, &end_ptr, 10);

		अगर (tid == पूर्णांक_न्यून || tid == पूर्णांक_उच्च ||
		    (*end_ptr != '\0' && *end_ptr != ','))
			जाओ out_मुक्त_thपढ़ोs;

		अगर (tid == prev_tid)
			जारी;

		ntasks++;
		nt = perf_thपढ़ो_map__पुनः_स्मृति(thपढ़ोs, ntasks);

		अगर (nt == शून्य)
			जाओ out_मुक्त_thपढ़ोs;

		thपढ़ोs = nt;
		perf_thपढ़ो_map__set_pid(thपढ़ोs, ntasks - 1, tid);
		thपढ़ोs->nr = ntasks;
	पूर्ण
out:
	अगर (thपढ़ोs)
		refcount_set(&thपढ़ोs->refcnt, 1);
	वापस thपढ़ोs;

out_मुक्त_thपढ़ोs:
	zमुक्त(&thपढ़ोs);
	strlist__delete(slist);
	जाओ out;
पूर्ण

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_str(स्थिर अक्षर *pid, स्थिर अक्षर *tid,
				       uid_t uid, bool all_thपढ़ोs)
अणु
	अगर (pid)
		वापस thपढ़ो_map__new_by_pid_str(pid);

	अगर (!tid && uid != अच_पूर्णांक_उच्च)
		वापस thपढ़ो_map__new_by_uid(uid);

	अगर (all_thपढ़ोs)
		वापस thपढ़ो_map__new_all_cpus();

	वापस thपढ़ो_map__new_by_tid_str(tid);
पूर्ण

माप_प्रकार thपढ़ो_map__ख_लिखो(काष्ठा perf_thपढ़ो_map *thपढ़ोs, खाता *fp)
अणु
	पूर्णांक i;
	माप_प्रकार prपूर्णांकed = ख_लिखो(fp, "%d thread%s: ",
				 thपढ़ोs->nr, thपढ़ोs->nr > 1 ? "s" : "");
	क्रम (i = 0; i < thपढ़ोs->nr; ++i)
		prपूर्णांकed += ख_लिखो(fp, "%s%d", i ? ", " : "", perf_thपढ़ो_map__pid(thपढ़ोs, i));

	वापस prपूर्णांकed + ख_लिखो(fp, "\n");
पूर्ण

अटल पूर्णांक get_comm(अक्षर **comm, pid_t pid)
अणु
	अक्षर *path;
	माप_प्रकार size;
	पूर्णांक err;

	अगर (aप्र_लिखो(&path, "%s/%d/comm", procfs__mountpoपूर्णांक(), pid) == -1)
		वापस -ENOMEM;

	err = filename__पढ़ो_str(path, comm, &size);
	अगर (!err) अणु
		/*
		 * We're पढ़ोing 16 bytes, जबतक filename__पढ़ो_str
		 * allocates data per बफ_मान bytes, so we can safely
		 * mark the end of the string.
		 */
		(*comm)[size] = 0;
		strim(*comm);
	पूर्ण

	मुक्त(path);
	वापस err;
पूर्ण

अटल व्योम comm_init(काष्ठा perf_thपढ़ो_map *map, पूर्णांक i)
अणु
	pid_t pid = perf_thपढ़ो_map__pid(map, i);
	अक्षर *comm = शून्य;

	/* dummy pid comm initialization */
	अगर (pid == -1) अणु
		map->map[i].comm = strdup("dummy");
		वापस;
	पूर्ण

	/*
	 * The comm name is like extra bonus ;-),
	 * so just warn अगर we fail क्रम any reason.
	 */
	अगर (get_comm(&comm, pid))
		pr_warning("Couldn't resolve comm name for pid %d\n", pid);

	map->map[i].comm = comm;
पूर्ण

व्योम thपढ़ो_map__पढ़ो_comms(काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < thपढ़ोs->nr; ++i)
		comm_init(thपढ़ोs, i);
पूर्ण

अटल व्योम thपढ़ो_map__copy_event(काष्ठा perf_thपढ़ो_map *thपढ़ोs,
				   काष्ठा perf_record_thपढ़ो_map *event)
अणु
	अचिन्हित i;

	thपढ़ोs->nr = (पूर्णांक) event->nr;

	क्रम (i = 0; i < event->nr; i++) अणु
		perf_thपढ़ो_map__set_pid(thपढ़ोs, i, (pid_t) event->entries[i].pid);
		thपढ़ोs->map[i].comm = strndup(event->entries[i].comm, 16);
	पूर्ण

	refcount_set(&thपढ़ोs->refcnt, 1);
पूर्ण

काष्ठा perf_thपढ़ो_map *thपढ़ो_map__new_event(काष्ठा perf_record_thपढ़ो_map *event)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;

	thपढ़ोs = thपढ़ो_map__alloc(event->nr);
	अगर (thपढ़ोs)
		thपढ़ो_map__copy_event(thपढ़ोs, event);

	वापस thपढ़ोs;
पूर्ण

bool thपढ़ो_map__has(काष्ठा perf_thपढ़ो_map *thपढ़ोs, pid_t pid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < thपढ़ोs->nr; ++i) अणु
		अगर (thपढ़ोs->map[i].pid == pid)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक thपढ़ो_map__हटाओ(काष्ठा perf_thपढ़ो_map *thपढ़ोs, पूर्णांक idx)
अणु
	पूर्णांक i;

	अगर (thपढ़ोs->nr < 1)
		वापस -EINVAL;

	अगर (idx >= thपढ़ोs->nr)
		वापस -EINVAL;

	/*
	 * Free the 'idx' item and shअगरt the rest up.
	 */
	zमुक्त(&thपढ़ोs->map[idx].comm);

	क्रम (i = idx; i < thपढ़ोs->nr - 1; i++)
		thपढ़ोs->map[i] = thपढ़ोs->map[i + 1];

	thपढ़ोs->nr--;
	वापस 0;
पूर्ण
