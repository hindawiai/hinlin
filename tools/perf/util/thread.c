<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश "dso.h"
#समावेश "session.h"
#समावेश "thread.h"
#समावेश "thread-stack.h"
#समावेश "debug.h"
#समावेश "namespaces.h"
#समावेश "comm.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "unwind.h"
#समावेश "callchain.h"

#समावेश <api/fs/fs.h>

पूर्णांक thपढ़ो__init_maps(काष्ठा thपढ़ो *thपढ़ो, काष्ठा machine *machine)
अणु
	pid_t pid = thपढ़ो->pid_;

	अगर (pid == thपढ़ो->tid || pid == -1) अणु
		thपढ़ो->maps = maps__new(machine);
	पूर्ण अन्यथा अणु
		काष्ठा thपढ़ो *leader = __machine__findnew_thपढ़ो(machine, pid, pid);
		अगर (leader) अणु
			thपढ़ो->maps = maps__get(leader->maps);
			thपढ़ो__put(leader);
		पूर्ण
	पूर्ण

	वापस thपढ़ो->maps ? 0 : -1;
पूर्ण

काष्ठा thपढ़ो *thपढ़ो__new(pid_t pid, pid_t tid)
अणु
	अक्षर *comm_str;
	काष्ठा comm *comm;
	काष्ठा thपढ़ो *thपढ़ो = zalloc(माप(*thपढ़ो));

	अगर (thपढ़ो != शून्य) अणु
		thपढ़ो->pid_ = pid;
		thपढ़ो->tid = tid;
		thपढ़ो->ppid = -1;
		thपढ़ो->cpu = -1;
		thपढ़ो->lbr_stitch_enable = false;
		INIT_LIST_HEAD(&thपढ़ो->namespaces_list);
		INIT_LIST_HEAD(&thपढ़ो->comm_list);
		init_rwsem(&thपढ़ो->namespaces_lock);
		init_rwsem(&thपढ़ो->comm_lock);

		comm_str = दो_स्मृति(32);
		अगर (!comm_str)
			जाओ err_thपढ़ो;

		snम_लिखो(comm_str, 32, ":%d", tid);
		comm = comm__new(comm_str, 0, false);
		मुक्त(comm_str);
		अगर (!comm)
			जाओ err_thपढ़ो;

		list_add(&comm->list, &thपढ़ो->comm_list);
		refcount_set(&thपढ़ो->refcnt, 1);
		RB_CLEAR_NODE(&thपढ़ो->rb_node);
		/* Thपढ़ो holds first ref to nsdata. */
		thपढ़ो->nsinfo = nsinfo__new(pid);
		srccode_state_init(&thपढ़ो->srccode_state);
	पूर्ण

	वापस thपढ़ो;

err_thपढ़ो:
	मुक्त(thपढ़ो);
	वापस शून्य;
पूर्ण

व्योम thपढ़ो__delete(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा namespaces *namespaces, *पंचांगp_namespaces;
	काष्ठा comm *comm, *पंचांगp_comm;

	BUG_ON(!RB_EMPTY_NODE(&thपढ़ो->rb_node));

	thपढ़ो_stack__मुक्त(thपढ़ो);

	अगर (thपढ़ो->maps) अणु
		maps__put(thपढ़ो->maps);
		thपढ़ो->maps = शून्य;
	पूर्ण
	करोwn_ग_लिखो(&thपढ़ो->namespaces_lock);
	list_क्रम_each_entry_safe(namespaces, पंचांगp_namespaces,
				 &thपढ़ो->namespaces_list, list) अणु
		list_del_init(&namespaces->list);
		namespaces__मुक्त(namespaces);
	पूर्ण
	up_ग_लिखो(&thपढ़ो->namespaces_lock);

	करोwn_ग_लिखो(&thपढ़ो->comm_lock);
	list_क्रम_each_entry_safe(comm, पंचांगp_comm, &thपढ़ो->comm_list, list) अणु
		list_del_init(&comm->list);
		comm__मुक्त(comm);
	पूर्ण
	up_ग_लिखो(&thपढ़ो->comm_lock);

	nsinfo__zput(thपढ़ो->nsinfo);
	srccode_state_मुक्त(&thपढ़ो->srccode_state);

	निकास_rwsem(&thपढ़ो->namespaces_lock);
	निकास_rwsem(&thपढ़ो->comm_lock);
	thपढ़ो__मुक्त_stitch_list(thपढ़ो);
	मुक्त(thपढ़ो);
पूर्ण

काष्ठा thपढ़ो *thपढ़ो__get(काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (thपढ़ो)
		refcount_inc(&thपढ़ो->refcnt);
	वापस thपढ़ो;
पूर्ण

व्योम thपढ़ो__put(काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (thपढ़ो && refcount_dec_and_test(&thपढ़ो->refcnt)) अणु
		/*
		 * Remove it from the dead thपढ़ोs list, as last reference is
		 * gone, अगर it is in a dead thपढ़ोs list.
		 *
		 * We may not be there anymore अगर say, the machine where it was
		 * stored was alपढ़ोy deleted, so we alपढ़ोy हटाओd it from
		 * the dead thपढ़ोs and some other piece of code still keeps a
		 * reference.
		 *
		 * This is what 'perf sched' करोes and finally drops it in
		 * perf_sched__lat(), where it calls perf_sched__पढ़ो_events(),
		 * that processes the events by creating a session and deleting
		 * it, which ends up destroying the list heads क्रम the dead
		 * thपढ़ोs, but beक्रमe it करोes that it हटाओs all thपढ़ोs from
		 * it using list_del_init().
		 *
		 * So we need to check here अगर it is in a dead thपढ़ोs list and
		 * अगर so, हटाओ it beक्रमe finally deleting the thपढ़ो, to aव्योम
		 * an use after मुक्त situation.
		 */
		अगर (!list_empty(&thपढ़ो->node))
			list_del_init(&thपढ़ो->node);
		thपढ़ो__delete(thपढ़ो);
	पूर्ण
पूर्ण

अटल काष्ठा namespaces *__thपढ़ो__namespaces(स्थिर काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (list_empty(&thपढ़ो->namespaces_list))
		वापस शून्य;

	वापस list_first_entry(&thपढ़ो->namespaces_list, काष्ठा namespaces, list);
पूर्ण

काष्ठा namespaces *thपढ़ो__namespaces(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा namespaces *ns;

	करोwn_पढ़ो(&thपढ़ो->namespaces_lock);
	ns = __thपढ़ो__namespaces(thपढ़ो);
	up_पढ़ो(&thपढ़ो->namespaces_lock);

	वापस ns;
पूर्ण

अटल पूर्णांक __thपढ़ो__set_namespaces(काष्ठा thपढ़ो *thपढ़ो, u64 बारtamp,
				    काष्ठा perf_record_namespaces *event)
अणु
	काष्ठा namespaces *new, *curr = __thपढ़ो__namespaces(thपढ़ो);

	new = namespaces__new(event);
	अगर (!new)
		वापस -ENOMEM;

	list_add(&new->list, &thपढ़ो->namespaces_list);

	अगर (बारtamp && curr) अणु
		/*
		 * setns syscall must have changed few or all the namespaces
		 * of this thपढ़ो. Update end समय क्रम the namespaces
		 * previously used.
		 */
		curr = list_next_entry(new, list);
		curr->end_समय = बारtamp;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक thपढ़ो__set_namespaces(काष्ठा thपढ़ो *thपढ़ो, u64 बारtamp,
			   काष्ठा perf_record_namespaces *event)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&thपढ़ो->namespaces_lock);
	ret = __thपढ़ो__set_namespaces(thपढ़ो, बारtamp, event);
	up_ग_लिखो(&thपढ़ो->namespaces_lock);
	वापस ret;
पूर्ण

काष्ठा comm *thपढ़ो__comm(स्थिर काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (list_empty(&thपढ़ो->comm_list))
		वापस शून्य;

	वापस list_first_entry(&thपढ़ो->comm_list, काष्ठा comm, list);
पूर्ण

काष्ठा comm *thपढ़ो__exec_comm(स्थिर काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा comm *comm, *last = शून्य, *second_last = शून्य;

	list_क्रम_each_entry(comm, &thपढ़ो->comm_list, list) अणु
		अगर (comm->exec)
			वापस comm;
		second_last = last;
		last = comm;
	पूर्ण

	/*
	 * 'last' with no start time might be the parent's comm of a synthesized
	 * thपढ़ो (created by processing a synthesized विभाजन event). For a मुख्य
	 * thपढ़ो, that is very probably wrong. Prefer a later comm to aव्योम
	 * that हाल.
	 */
	अगर (second_last && !last->start && thपढ़ो->pid_ == thपढ़ो->tid)
		वापस second_last;

	वापस last;
पूर्ण

अटल पूर्णांक ____thपढ़ो__set_comm(काष्ठा thपढ़ो *thपढ़ो, स्थिर अक्षर *str,
				u64 बारtamp, bool exec)
अणु
	काष्ठा comm *new, *curr = thपढ़ो__comm(thपढ़ो);

	/* Override the शेष :tid entry */
	अगर (!thपढ़ो->comm_set) अणु
		पूर्णांक err = comm__override(curr, str, बारtamp, exec);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		new = comm__new(str, बारtamp, exec);
		अगर (!new)
			वापस -ENOMEM;
		list_add(&new->list, &thपढ़ो->comm_list);

		अगर (exec)
			unwind__flush_access(thपढ़ो->maps);
	पूर्ण

	thपढ़ो->comm_set = true;

	वापस 0;
पूर्ण

पूर्णांक __thपढ़ो__set_comm(काष्ठा thपढ़ो *thपढ़ो, स्थिर अक्षर *str, u64 बारtamp,
		       bool exec)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&thपढ़ो->comm_lock);
	ret = ____thपढ़ो__set_comm(thपढ़ो, str, बारtamp, exec);
	up_ग_लिखो(&thपढ़ो->comm_lock);
	वापस ret;
पूर्ण

पूर्णांक thपढ़ो__set_comm_from_proc(काष्ठा thपढ़ो *thपढ़ो)
अणु
	अक्षर path[64];
	अक्षर *comm = शून्य;
	माप_प्रकार sz;
	पूर्णांक err = -1;

	अगर (!(snम_लिखो(path, माप(path), "%d/task/%d/comm",
		       thपढ़ो->pid_, thपढ़ो->tid) >= (पूर्णांक)माप(path)) &&
	    procfs__पढ़ो_str(path, &comm, &sz) == 0) अणु
		comm[sz - 1] = '\0';
		err = thपढ़ो__set_comm(thपढ़ो, comm, 0);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर अक्षर *__thपढ़ो__comm_str(स्थिर काष्ठा thपढ़ो *thपढ़ो)
अणु
	स्थिर काष्ठा comm *comm = thपढ़ो__comm(thपढ़ो);

	अगर (!comm)
		वापस शून्य;

	वापस comm__str(comm);
पूर्ण

स्थिर अक्षर *thपढ़ो__comm_str(काष्ठा thपढ़ो *thपढ़ो)
अणु
	स्थिर अक्षर *str;

	करोwn_पढ़ो(&thपढ़ो->comm_lock);
	str = __thपढ़ो__comm_str(thपढ़ो);
	up_पढ़ो(&thपढ़ो->comm_lock);

	वापस str;
पूर्ण

/* CHECKME: it should probably better वापस the max comm len from its comm list */
पूर्णांक thपढ़ो__comm_len(काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (!thपढ़ो->comm_len) अणु
		स्थिर अक्षर *comm = thपढ़ो__comm_str(thपढ़ो);
		अगर (!comm)
			वापस 0;
		thपढ़ो->comm_len = म_माप(comm);
	पूर्ण

	वापस thपढ़ो->comm_len;
पूर्ण

माप_प्रकार thपढ़ो__ख_लिखो(काष्ठा thपढ़ो *thपढ़ो, खाता *fp)
अणु
	वापस ख_लिखो(fp, "Thread %d %s\n", thपढ़ो->tid, thपढ़ो__comm_str(thपढ़ो)) +
	       maps__ख_लिखो(thपढ़ो->maps, fp);
पूर्ण

पूर्णांक thपढ़ो__insert_map(काष्ठा thपढ़ो *thपढ़ो, काष्ठा map *map)
अणु
	पूर्णांक ret;

	ret = unwind__prepare_access(thपढ़ो->maps, map, शून्य);
	अगर (ret)
		वापस ret;

	maps__fixup_overlappings(thपढ़ो->maps, map, मानक_त्रुटि);
	maps__insert(thपढ़ो->maps, map);

	वापस 0;
पूर्ण

अटल पूर्णांक __thपढ़ो__prepare_access(काष्ठा thपढ़ो *thपढ़ो)
अणु
	bool initialized = false;
	पूर्णांक err = 0;
	काष्ठा maps *maps = thपढ़ो->maps;
	काष्ठा map *map;

	करोwn_पढ़ो(&maps->lock);

	maps__क्रम_each_entry(maps, map) अणु
		err = unwind__prepare_access(thपढ़ो->maps, map, &initialized);
		अगर (err || initialized)
			अवरोध;
	पूर्ण

	up_पढ़ो(&maps->lock);

	वापस err;
पूर्ण

अटल पूर्णांक thपढ़ो__prepare_access(काष्ठा thपढ़ो *thपढ़ो)
अणु
	पूर्णांक err = 0;

	अगर (dwarf_callchain_users)
		err = __thपढ़ो__prepare_access(thपढ़ो);

	वापस err;
पूर्ण

अटल पूर्णांक thपढ़ो__clone_maps(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो *parent, bool करो_maps_clone)
अणु
	/* This is new thपढ़ो, we share map groups क्रम process. */
	अगर (thपढ़ो->pid_ == parent->pid_)
		वापस thपढ़ो__prepare_access(thपढ़ो);

	अगर (thपढ़ो->maps == parent->maps) अणु
		pr_debug("broken map groups on thread %d/%d parent %d/%d\n",
			 thपढ़ो->pid_, thपढ़ो->tid, parent->pid_, parent->tid);
		वापस 0;
	पूर्ण
	/* But this one is new process, copy maps. */
	वापस करो_maps_clone ? maps__clone(thपढ़ो, parent->maps) : 0;
पूर्ण

पूर्णांक thपढ़ो__विभाजन(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो *parent, u64 बारtamp, bool करो_maps_clone)
अणु
	अगर (parent->comm_set) अणु
		स्थिर अक्षर *comm = thपढ़ो__comm_str(parent);
		पूर्णांक err;
		अगर (!comm)
			वापस -ENOMEM;
		err = thपढ़ो__set_comm(thपढ़ो, comm, बारtamp);
		अगर (err)
			वापस err;
	पूर्ण

	thपढ़ो->ppid = parent->tid;
	वापस thपढ़ो__clone_maps(thपढ़ो, parent, करो_maps_clone);
पूर्ण

व्योम thपढ़ो__find_cpumode_addr_location(काष्ठा thपढ़ो *thपढ़ो, u64 addr,
					काष्ठा addr_location *al)
अणु
	माप_प्रकार i;
	स्थिर u8 cpumodes[] = अणु
		PERF_RECORD_MISC_USER,
		PERF_RECORD_MISC_KERNEL,
		PERF_RECORD_MISC_GUEST_USER,
		PERF_RECORD_MISC_GUEST_KERNEL
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(cpumodes); i++) अणु
		thपढ़ो__find_symbol(thपढ़ो, cpumodes[i], addr, al);
		अगर (al->map)
			अवरोध;
	पूर्ण
पूर्ण

काष्ठा thपढ़ो *thपढ़ो__मुख्य_thपढ़ो(काष्ठा machine *machine, काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (thपढ़ो->pid_ == thपढ़ो->tid)
		वापस thपढ़ो__get(thपढ़ो);

	अगर (thपढ़ो->pid_ == -1)
		वापस शून्य;

	वापस machine__find_thपढ़ो(machine, thपढ़ो->pid_, thपढ़ो->pid_);
पूर्ण

पूर्णांक thपढ़ो__स_नकल(काष्ठा thपढ़ो *thपढ़ो, काष्ठा machine *machine,
		   व्योम *buf, u64 ip, पूर्णांक len, bool *is64bit)
अणु
       u8 cpumode = PERF_RECORD_MISC_USER;
       काष्ठा addr_location al;
       दीर्घ offset;

       अगर (machine__kernel_ip(machine, ip))
               cpumode = PERF_RECORD_MISC_KERNEL;

       अगर (!thपढ़ो__find_map(thपढ़ो, cpumode, ip, &al) || !al.map->dso ||
	   al.map->dso->data.status == DSO_DATA_STATUS_ERROR ||
	   map__load(al.map) < 0)
               वापस -1;

       offset = al.map->map_ip(al.map, ip);
       अगर (is64bit)
               *is64bit = al.map->dso->is_64_bit;

       वापस dso__data_पढ़ो_offset(al.map->dso, machine, offset, buf, len);
पूर्ण

व्योम thपढ़ो__मुक्त_stitch_list(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा lbr_stitch *lbr_stitch = thपढ़ो->lbr_stitch;
	काष्ठा stitch_list *pos, *पंचांगp;

	अगर (!lbr_stitch)
		वापस;

	list_क्रम_each_entry_safe(pos, पंचांगp, &lbr_stitch->lists, node) अणु
		list_del_init(&pos->node);
		मुक्त(pos);
	पूर्ण

	list_क्रम_each_entry_safe(pos, पंचांगp, &lbr_stitch->मुक्त_lists, node) अणु
		list_del_init(&pos->node);
		मुक्त(pos);
	पूर्ण

	zमुक्त(&lbr_stitch->prev_lbr_cursor);
	zमुक्त(&thपढ़ो->lbr_stitch);
पूर्ण
