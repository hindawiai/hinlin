<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <regex.h>
#समावेश <मानककोष.स>
#समावेश "callchain.h"
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "env.h"
#समावेश "event.h"
#समावेश "evsel.h"
#समावेश "hist.h"
#समावेश "machine.h"
#समावेश "map.h"
#समावेश "map_symbol.h"
#समावेश "branch.h"
#समावेश "mem-events.h"
#समावेश "srcline.h"
#समावेश "symbol.h"
#समावेश "sort.h"
#समावेश "strlist.h"
#समावेश "target.h"
#समावेश "thread.h"
#समावेश "util.h"
#समावेश "vdso.h"
#समावेश <stdbool.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश "unwind.h"
#समावेश "linux/hash.h"
#समावेश "asm/bug.h"
#समावेश "bpf-event.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "cgroup.h"

#समावेश <linux/प्रकार.स>
#समावेश <symbol/kallsyms.h>
#समावेश <linux/mman.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

अटल व्योम __machine__हटाओ_thपढ़ो(काष्ठा machine *machine, काष्ठा thपढ़ो *th, bool lock);

अटल काष्ठा dso *machine__kernel_dso(काष्ठा machine *machine)
अणु
	वापस machine->vmlinux_map->dso;
पूर्ण

अटल व्योम dsos__init(काष्ठा dsos *dsos)
अणु
	INIT_LIST_HEAD(&dsos->head);
	dsos->root = RB_ROOT;
	init_rwsem(&dsos->lock);
पूर्ण

अटल व्योम machine__thपढ़ोs_init(काष्ठा machine *machine)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++) अणु
		काष्ठा thपढ़ोs *thपढ़ोs = &machine->thपढ़ोs[i];
		thपढ़ोs->entries = RB_ROOT_CACHED;
		init_rwsem(&thपढ़ोs->lock);
		thपढ़ोs->nr = 0;
		INIT_LIST_HEAD(&thपढ़ोs->dead);
		thपढ़ोs->last_match = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक machine__set_mmap_name(काष्ठा machine *machine)
अणु
	अगर (machine__is_host(machine))
		machine->mmap_name = strdup("[kernel.kallsyms]");
	अन्यथा अगर (machine__is_शेष_guest(machine))
		machine->mmap_name = strdup("[guest.kernel.kallsyms]");
	अन्यथा अगर (aप्र_लिखो(&machine->mmap_name, "[guest.kernel.kallsyms.%d]",
			  machine->pid) < 0)
		machine->mmap_name = शून्य;

	वापस machine->mmap_name ? 0 : -ENOMEM;
पूर्ण

पूर्णांक machine__init(काष्ठा machine *machine, स्थिर अक्षर *root_dir, pid_t pid)
अणु
	पूर्णांक err = -ENOMEM;

	स_रखो(machine, 0, माप(*machine));
	maps__init(&machine->kmaps, machine);
	RB_CLEAR_NODE(&machine->rb_node);
	dsos__init(&machine->dsos);

	machine__thपढ़ोs_init(machine);

	machine->vdso_info = शून्य;
	machine->env = शून्य;

	machine->pid = pid;

	machine->id_hdr_size = 0;
	machine->kptr_restrict_warned = false;
	machine->comm_exec = false;
	machine->kernel_start = 0;
	machine->vmlinux_map = शून्य;

	machine->root_dir = strdup(root_dir);
	अगर (machine->root_dir == शून्य)
		वापस -ENOMEM;

	अगर (machine__set_mmap_name(machine))
		जाओ out;

	अगर (pid != HOST_KERNEL_ID) अणु
		काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, -1,
								pid);
		अक्षर comm[64];

		अगर (thपढ़ो == शून्य)
			जाओ out;

		snम_लिखो(comm, माप(comm), "[guest/%d]", pid);
		thपढ़ो__set_comm(thपढ़ो, comm, 0);
		thपढ़ो__put(thपढ़ो);
	पूर्ण

	machine->current_tid = शून्य;
	err = 0;

out:
	अगर (err) अणु
		zमुक्त(&machine->root_dir);
		zमुक्त(&machine->mmap_name);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा machine *machine__new_host(व्योम)
अणु
	काष्ठा machine *machine = दो_स्मृति(माप(*machine));

	अगर (machine != शून्य) अणु
		machine__init(machine, "", HOST_KERNEL_ID);

		अगर (machine__create_kernel_maps(machine) < 0)
			जाओ out_delete;
	पूर्ण

	वापस machine;
out_delete:
	मुक्त(machine);
	वापस शून्य;
पूर्ण

काष्ठा machine *machine__new_kallsyms(व्योम)
अणु
	काष्ठा machine *machine = machine__new_host();
	/*
	 * FIXME:
	 * 1) We should चयन to machine__load_kallsyms(), i.e. not explicitly
	 *    ask क्रम not using the kcore parsing code, once this one is fixed
	 *    to create a map per module.
	 */
	अगर (machine && machine__load_kallsyms(machine, "/proc/kallsyms") <= 0) अणु
		machine__delete(machine);
		machine = शून्य;
	पूर्ण

	वापस machine;
पूर्ण

अटल व्योम dsos__purge(काष्ठा dsos *dsos)
अणु
	काष्ठा dso *pos, *n;

	करोwn_ग_लिखो(&dsos->lock);

	list_क्रम_each_entry_safe(pos, n, &dsos->head, node) अणु
		RB_CLEAR_NODE(&pos->rb_node);
		pos->root = शून्य;
		list_del_init(&pos->node);
		dso__put(pos);
	पूर्ण

	up_ग_लिखो(&dsos->lock);
पूर्ण

अटल व्योम dsos__निकास(काष्ठा dsos *dsos)
अणु
	dsos__purge(dsos);
	निकास_rwsem(&dsos->lock);
पूर्ण

व्योम machine__delete_thपढ़ोs(काष्ठा machine *machine)
अणु
	काष्ठा rb_node *nd;
	पूर्णांक i;

	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++) अणु
		काष्ठा thपढ़ोs *thपढ़ोs = &machine->thपढ़ोs[i];
		करोwn_ग_लिखो(&thपढ़ोs->lock);
		nd = rb_first_cached(&thपढ़ोs->entries);
		जबतक (nd) अणु
			काष्ठा thपढ़ो *t = rb_entry(nd, काष्ठा thपढ़ो, rb_node);

			nd = rb_next(nd);
			__machine__हटाओ_thपढ़ो(machine, t, false);
		पूर्ण
		up_ग_लिखो(&thपढ़ोs->lock);
	पूर्ण
पूर्ण

व्योम machine__निकास(काष्ठा machine *machine)
अणु
	पूर्णांक i;

	अगर (machine == शून्य)
		वापस;

	machine__destroy_kernel_maps(machine);
	maps__निकास(&machine->kmaps);
	dsos__निकास(&machine->dsos);
	machine__निकास_vdso(machine);
	zमुक्त(&machine->root_dir);
	zमुक्त(&machine->mmap_name);
	zमुक्त(&machine->current_tid);

	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++) अणु
		काष्ठा thपढ़ोs *thपढ़ोs = &machine->thपढ़ोs[i];
		काष्ठा thपढ़ो *thपढ़ो, *n;
		/*
		 * Forget about the dead, at this poपूर्णांक whatever thपढ़ोs were
		 * left in the dead lists better have a reference count taken
		 * by who is using them, and then, when they drop those references
		 * and it finally hits zero, thपढ़ो__put() will check and see that
		 * its not in the dead thपढ़ोs list and will not try to हटाओ it
		 * from there, just calling thपढ़ो__delete() straight away.
		 */
		list_क्रम_each_entry_safe(thपढ़ो, n, &thपढ़ोs->dead, node)
			list_del_init(&thपढ़ो->node);

		निकास_rwsem(&thपढ़ोs->lock);
	पूर्ण
पूर्ण

व्योम machine__delete(काष्ठा machine *machine)
अणु
	अगर (machine) अणु
		machine__निकास(machine);
		मुक्त(machine);
	पूर्ण
पूर्ण

व्योम machines__init(काष्ठा machines *machines)
अणु
	machine__init(&machines->host, "", HOST_KERNEL_ID);
	machines->guests = RB_ROOT_CACHED;
पूर्ण

व्योम machines__निकास(काष्ठा machines *machines)
अणु
	machine__निकास(&machines->host);
	/* XXX निकास guest */
पूर्ण

काष्ठा machine *machines__add(काष्ठा machines *machines, pid_t pid,
			      स्थिर अक्षर *root_dir)
अणु
	काष्ठा rb_node **p = &machines->guests.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा machine *pos, *machine = दो_स्मृति(माप(*machine));
	bool lefपंचांगost = true;

	अगर (machine == शून्य)
		वापस शून्य;

	अगर (machine__init(machine, root_dir, pid) != 0) अणु
		मुक्त(machine);
		वापस शून्य;
	पूर्ण

	जबतक (*p != शून्य) अणु
		parent = *p;
		pos = rb_entry(parent, काष्ठा machine, rb_node);
		अगर (pid < pos->pid)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&machine->rb_node, parent, p);
	rb_insert_color_cached(&machine->rb_node, &machines->guests, lefपंचांगost);

	वापस machine;
पूर्ण

व्योम machines__set_comm_exec(काष्ठा machines *machines, bool comm_exec)
अणु
	काष्ठा rb_node *nd;

	machines->host.comm_exec = comm_exec;

	क्रम (nd = rb_first_cached(&machines->guests); nd; nd = rb_next(nd)) अणु
		काष्ठा machine *machine = rb_entry(nd, काष्ठा machine, rb_node);

		machine->comm_exec = comm_exec;
	पूर्ण
पूर्ण

काष्ठा machine *machines__find(काष्ठा machines *machines, pid_t pid)
अणु
	काष्ठा rb_node **p = &machines->guests.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा machine *machine;
	काष्ठा machine *शेष_machine = शून्य;

	अगर (pid == HOST_KERNEL_ID)
		वापस &machines->host;

	जबतक (*p != शून्य) अणु
		parent = *p;
		machine = rb_entry(parent, काष्ठा machine, rb_node);
		अगर (pid < machine->pid)
			p = &(*p)->rb_left;
		अन्यथा अगर (pid > machine->pid)
			p = &(*p)->rb_right;
		अन्यथा
			वापस machine;
		अगर (!machine->pid)
			शेष_machine = machine;
	पूर्ण

	वापस शेष_machine;
पूर्ण

काष्ठा machine *machines__findnew(काष्ठा machines *machines, pid_t pid)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *root_dir = "";
	काष्ठा machine *machine = machines__find(machines, pid);

	अगर (machine && (machine->pid == pid))
		जाओ out;

	अगर ((pid != HOST_KERNEL_ID) &&
	    (pid != DEFAULT_GUEST_KERNEL_ID) &&
	    (symbol_conf.guesपंचांगount)) अणु
		प्र_लिखो(path, "%s/%d", symbol_conf.guesपंचांगount, pid);
		अगर (access(path, R_OK)) अणु
			अटल काष्ठा strlist *seen;

			अगर (!seen)
				seen = strlist__new(शून्य, शून्य);

			अगर (!strlist__has_entry(seen, path)) अणु
				pr_err("Can't access file %s\n", path);
				strlist__add(seen, path);
			पूर्ण
			machine = शून्य;
			जाओ out;
		पूर्ण
		root_dir = path;
	पूर्ण

	machine = machines__add(machines, pid, root_dir);
out:
	वापस machine;
पूर्ण

काष्ठा machine *machines__find_guest(काष्ठा machines *machines, pid_t pid)
अणु
	काष्ठा machine *machine = machines__find(machines, pid);

	अगर (!machine)
		machine = machines__findnew(machines, DEFAULT_GUEST_KERNEL_ID);
	वापस machine;
पूर्ण

व्योम machines__process_guests(काष्ठा machines *machines,
			      machine__process_t process, व्योम *data)
अणु
	काष्ठा rb_node *nd;

	क्रम (nd = rb_first_cached(&machines->guests); nd; nd = rb_next(nd)) अणु
		काष्ठा machine *pos = rb_entry(nd, काष्ठा machine, rb_node);
		process(pos, data);
	पूर्ण
पूर्ण

व्योम machines__set_id_hdr_size(काष्ठा machines *machines, u16 id_hdr_size)
अणु
	काष्ठा rb_node *node;
	काष्ठा machine *machine;

	machines->host.id_hdr_size = id_hdr_size;

	क्रम (node = rb_first_cached(&machines->guests); node;
	     node = rb_next(node)) अणु
		machine = rb_entry(node, काष्ठा machine, rb_node);
		machine->id_hdr_size = id_hdr_size;
	पूर्ण

	वापस;
पूर्ण

अटल व्योम machine__update_thपढ़ो_pid(काष्ठा machine *machine,
				       काष्ठा thपढ़ो *th, pid_t pid)
अणु
	काष्ठा thपढ़ो *leader;

	अगर (pid == th->pid_ || pid == -1 || th->pid_ != -1)
		वापस;

	th->pid_ = pid;

	अगर (th->pid_ == th->tid)
		वापस;

	leader = __machine__findnew_thपढ़ो(machine, th->pid_, th->pid_);
	अगर (!leader)
		जाओ out_err;

	अगर (!leader->maps)
		leader->maps = maps__new(machine);

	अगर (!leader->maps)
		जाओ out_err;

	अगर (th->maps == leader->maps)
		वापस;

	अगर (th->maps) अणु
		/*
		 * Maps are created from MMAP events which provide the pid and
		 * tid.  Consequently there never should be any maps on a thपढ़ो
		 * with an unknown pid.  Just prपूर्णांक an error अगर there are.
		 */
		अगर (!maps__empty(th->maps))
			pr_err("Discarding thread maps for %d:%d\n",
			       th->pid_, th->tid);
		maps__put(th->maps);
	पूर्ण

	th->maps = maps__get(leader->maps);
out_put:
	thपढ़ो__put(leader);
	वापस;
out_err:
	pr_err("Failed to join map groups for %d:%d\n", th->pid_, th->tid);
	जाओ out_put;
पूर्ण

/*
 * Front-end cache - TID lookups come in blocks,
 * so most of the समय we करोnt have to look up
 * the full rbtree:
 */
अटल काष्ठा thपढ़ो*
__thपढ़ोs__get_last_match(काष्ठा thपढ़ोs *thपढ़ोs, काष्ठा machine *machine,
			  पूर्णांक pid, पूर्णांक tid)
अणु
	काष्ठा thपढ़ो *th;

	th = thपढ़ोs->last_match;
	अगर (th != शून्य) अणु
		अगर (th->tid == tid) अणु
			machine__update_thपढ़ो_pid(machine, th, pid);
			वापस thपढ़ो__get(th);
		पूर्ण

		thपढ़ोs->last_match = शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा thपढ़ो*
thपढ़ोs__get_last_match(काष्ठा thपढ़ोs *thपढ़ोs, काष्ठा machine *machine,
			पूर्णांक pid, पूर्णांक tid)
अणु
	काष्ठा thपढ़ो *th = शून्य;

	अगर (perf_singlethपढ़ोed)
		th = __thपढ़ोs__get_last_match(thपढ़ोs, machine, pid, tid);

	वापस th;
पूर्ण

अटल व्योम
__thपढ़ोs__set_last_match(काष्ठा thपढ़ोs *thपढ़ोs, काष्ठा thपढ़ो *th)
अणु
	thपढ़ोs->last_match = th;
पूर्ण

अटल व्योम
thपढ़ोs__set_last_match(काष्ठा thपढ़ोs *thपढ़ोs, काष्ठा thपढ़ो *th)
अणु
	अगर (perf_singlethपढ़ोed)
		__thपढ़ोs__set_last_match(thपढ़ोs, th);
पूर्ण

/*
 * Caller must eventually drop thपढ़ो->refcnt वापसed with a successful
 * lookup/new thपढ़ो inserted.
 */
अटल काष्ठा thपढ़ो *____machine__findnew_thपढ़ो(काष्ठा machine *machine,
						  काष्ठा thपढ़ोs *thपढ़ोs,
						  pid_t pid, pid_t tid,
						  bool create)
अणु
	काष्ठा rb_node **p = &thपढ़ोs->entries.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा thपढ़ो *th;
	bool lefपंचांगost = true;

	th = thपढ़ोs__get_last_match(thपढ़ोs, machine, pid, tid);
	अगर (th)
		वापस th;

	जबतक (*p != शून्य) अणु
		parent = *p;
		th = rb_entry(parent, काष्ठा thपढ़ो, rb_node);

		अगर (th->tid == tid) अणु
			thपढ़ोs__set_last_match(thपढ़ोs, th);
			machine__update_thपढ़ो_pid(machine, th, pid);
			वापस thपढ़ो__get(th);
		पूर्ण

		अगर (tid < th->tid)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	अगर (!create)
		वापस शून्य;

	th = thपढ़ो__new(pid, tid);
	अगर (th != शून्य) अणु
		rb_link_node(&th->rb_node, parent, p);
		rb_insert_color_cached(&th->rb_node, &thपढ़ोs->entries, lefपंचांगost);

		/*
		 * We have to initialize maps separately after rb tree is updated.
		 *
		 * The reason is that we call machine__findnew_thपढ़ो
		 * within thपढ़ो__init_maps to find the thपढ़ो
		 * leader and that would screwed the rb tree.
		 */
		अगर (thपढ़ो__init_maps(th, machine)) अणु
			rb_erase_cached(&th->rb_node, &thपढ़ोs->entries);
			RB_CLEAR_NODE(&th->rb_node);
			thपढ़ो__put(th);
			वापस शून्य;
		पूर्ण
		/*
		 * It is now in the rbtree, get a ref
		 */
		thपढ़ो__get(th);
		thपढ़ोs__set_last_match(thपढ़ोs, th);
		++thपढ़ोs->nr;
	पूर्ण

	वापस th;
पूर्ण

काष्ठा thपढ़ो *__machine__findnew_thपढ़ो(काष्ठा machine *machine, pid_t pid, pid_t tid)
अणु
	वापस ____machine__findnew_thपढ़ो(machine, machine__thपढ़ोs(machine, tid), pid, tid, true);
पूर्ण

काष्ठा thपढ़ो *machine__findnew_thपढ़ो(काष्ठा machine *machine, pid_t pid,
				       pid_t tid)
अणु
	काष्ठा thपढ़ोs *thपढ़ोs = machine__thपढ़ोs(machine, tid);
	काष्ठा thपढ़ो *th;

	करोwn_ग_लिखो(&thपढ़ोs->lock);
	th = __machine__findnew_thपढ़ो(machine, pid, tid);
	up_ग_लिखो(&thपढ़ोs->lock);
	वापस th;
पूर्ण

काष्ठा thपढ़ो *machine__find_thपढ़ो(काष्ठा machine *machine, pid_t pid,
				    pid_t tid)
अणु
	काष्ठा thपढ़ोs *thपढ़ोs = machine__thपढ़ोs(machine, tid);
	काष्ठा thपढ़ो *th;

	करोwn_पढ़ो(&thपढ़ोs->lock);
	th =  ____machine__findnew_thपढ़ो(machine, thपढ़ोs, pid, tid, false);
	up_पढ़ो(&thपढ़ोs->lock);
	वापस th;
पूर्ण

/*
 * Thपढ़ोs are identअगरied by pid and tid, and the idle task has pid == tid == 0.
 * So here a single thपढ़ो is created क्रम that, but actually there is a separate
 * idle task per cpu, so there should be one 'struct thread' per cpu, but there
 * is only 1. That causes problems क्रम some tools, requiring workarounds. For
 * example get_idle_thपढ़ो() in builtin-sched.c, or thपढ़ो_stack__per_cpu().
 */
काष्ठा thपढ़ो *machine__idle_thपढ़ो(काष्ठा machine *machine)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, 0, 0);

	अगर (!thपढ़ो || thपढ़ो__set_comm(thपढ़ो, "swapper", 0) ||
	    thपढ़ो__set_namespaces(thपढ़ो, 0, शून्य))
		pr_err("problem inserting idle task for machine pid %d\n", machine->pid);

	वापस thपढ़ो;
पूर्ण

काष्ठा comm *machine__thपढ़ो_exec_comm(काष्ठा machine *machine,
				       काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (machine->comm_exec)
		वापस thपढ़ो__exec_comm(thपढ़ो);
	अन्यथा
		वापस thपढ़ो__comm(thपढ़ो);
पूर्ण

पूर्णांक machine__process_comm_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine,
							event->comm.pid,
							event->comm.tid);
	bool exec = event->header.misc & PERF_RECORD_MISC_COMM_EXEC;
	पूर्णांक err = 0;

	अगर (exec)
		machine->comm_exec = true;

	अगर (dump_trace)
		perf_event__ख_लिखो_comm(event, मानक_निकास);

	अगर (thपढ़ो == शून्य ||
	    __thपढ़ो__set_comm(thपढ़ो, event->comm.comm, sample->समय, exec)) अणु
		dump_म_लिखो("problem processing PERF_RECORD_COMM, skipping event.\n");
		err = -1;
	पूर्ण

	thपढ़ो__put(thपढ़ो);

	वापस err;
पूर्ण

पूर्णांक machine__process_namespaces_event(काष्ठा machine *machine __maybe_unused,
				      जोड़ perf_event *event,
				      काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine,
							event->namespaces.pid,
							event->namespaces.tid);
	पूर्णांक err = 0;

	WARN_ONCE(event->namespaces.nr_namespaces > NR_NAMESPACES,
		  "\nWARNING: kernel seems to support more namespaces than perf"
		  " tool.\nTry updating the perf tool..\n\n");

	WARN_ONCE(event->namespaces.nr_namespaces < NR_NAMESPACES,
		  "\nWARNING: perf tool seems to support more namespaces than"
		  " the kernel.\nTry updating the kernel..\n\n");

	अगर (dump_trace)
		perf_event__ख_लिखो_namespaces(event, मानक_निकास);

	अगर (thपढ़ो == शून्य ||
	    thपढ़ो__set_namespaces(thपढ़ो, sample->समय, &event->namespaces)) अणु
		dump_म_लिखो("problem processing PERF_RECORD_NAMESPACES, skipping event.\n");
		err = -1;
	पूर्ण

	thपढ़ो__put(thपढ़ो);

	वापस err;
पूर्ण

पूर्णांक machine__process_cgroup_event(काष्ठा machine *machine,
				  जोड़ perf_event *event,
				  काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा cgroup *cgrp;

	अगर (dump_trace)
		perf_event__ख_लिखो_cgroup(event, मानक_निकास);

	cgrp = cgroup__findnew(machine->env, event->cgroup.id, event->cgroup.path);
	अगर (cgrp == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक machine__process_lost_event(काष्ठा machine *machine __maybe_unused,
				जोड़ perf_event *event, काष्ठा perf_sample *sample __maybe_unused)
अणु
	dump_म_लिखो(": id:%" PRI_lu64 ": lost:%" PRI_lu64 "\n",
		    event->lost.id, event->lost.lost);
	वापस 0;
पूर्ण

पूर्णांक machine__process_lost_samples_event(काष्ठा machine *machine __maybe_unused,
					जोड़ perf_event *event, काष्ठा perf_sample *sample)
अणु
	dump_म_लिखो(": id:%" PRIu64 ": lost samples :%" PRI_lu64 "\n",
		    sample->id, event->lost_samples.lost);
	वापस 0;
पूर्ण

अटल काष्ठा dso *machine__findnew_module_dso(काष्ठा machine *machine,
					       काष्ठा kmod_path *m,
					       स्थिर अक्षर *filename)
अणु
	काष्ठा dso *dso;

	करोwn_ग_लिखो(&machine->dsos.lock);

	dso = __dsos__find(&machine->dsos, m->name, true);
	अगर (!dso) अणु
		dso = __dsos__addnew(&machine->dsos, m->name);
		अगर (dso == शून्य)
			जाओ out_unlock;

		dso__set_module_info(dso, m, machine);
		dso__set_दीर्घ_name(dso, strdup(filename), true);
		dso->kernel = DSO_SPACE__KERNEL;
	पूर्ण

	dso__get(dso);
out_unlock:
	up_ग_लिखो(&machine->dsos.lock);
	वापस dso;
पूर्ण

पूर्णांक machine__process_aux_event(काष्ठा machine *machine __maybe_unused,
			       जोड़ perf_event *event)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_aux(event, मानक_निकास);
	वापस 0;
पूर्ण

पूर्णांक machine__process_itrace_start_event(काष्ठा machine *machine __maybe_unused,
					जोड़ perf_event *event)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_itrace_start(event, मानक_निकास);
	वापस 0;
पूर्ण

पूर्णांक machine__process_चयन_event(काष्ठा machine *machine __maybe_unused,
				  जोड़ perf_event *event)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_चयन(event, मानक_निकास);
	वापस 0;
पूर्ण

अटल पूर्णांक machine__process_ksymbol_रेजिस्टर(काष्ठा machine *machine,
					     जोड़ perf_event *event,
					     काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा symbol *sym;
	काष्ठा map *map = maps__find(&machine->kmaps, event->ksymbol.addr);

	अगर (!map) अणु
		काष्ठा dso *dso = dso__new(event->ksymbol.name);

		अगर (dso) अणु
			dso->kernel = DSO_SPACE__KERNEL;
			map = map__new2(0, dso);
			dso__put(dso);
		पूर्ण

		अगर (!dso || !map) अणु
			वापस -ENOMEM;
		पूर्ण

		अगर (event->ksymbol.ksym_type == PERF_RECORD_KSYMBOL_TYPE_OOL) अणु
			map->dso->binary_type = DSO_BINARY_TYPE__OOL;
			map->dso->data.file_size = event->ksymbol.len;
			dso__set_loaded(map->dso);
		पूर्ण

		map->start = event->ksymbol.addr;
		map->end = map->start + event->ksymbol.len;
		maps__insert(&machine->kmaps, map);
		map__put(map);
		dso__set_loaded(dso);

		अगर (is_bpf_image(event->ksymbol.name)) अणु
			dso->binary_type = DSO_BINARY_TYPE__BPF_IMAGE;
			dso__set_दीर्घ_name(dso, "", false);
		पूर्ण
	पूर्ण

	sym = symbol__new(map->map_ip(map, map->start),
			  event->ksymbol.len,
			  0, 0, event->ksymbol.name);
	अगर (!sym)
		वापस -ENOMEM;
	dso__insert_symbol(map->dso, sym);
	वापस 0;
पूर्ण

अटल पूर्णांक machine__process_ksymbol_unरेजिस्टर(काष्ठा machine *machine,
					       जोड़ perf_event *event,
					       काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा symbol *sym;
	काष्ठा map *map;

	map = maps__find(&machine->kmaps, event->ksymbol.addr);
	अगर (!map)
		वापस 0;

	अगर (map != machine->vmlinux_map)
		maps__हटाओ(&machine->kmaps, map);
	अन्यथा अणु
		sym = dso__find_symbol(map->dso, map->map_ip(map, map->start));
		अगर (sym)
			dso__delete_symbol(map->dso, sym);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक machine__process_ksymbol(काष्ठा machine *machine __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample)
अणु
	अगर (dump_trace)
		perf_event__ख_लिखो_ksymbol(event, मानक_निकास);

	अगर (event->ksymbol.flags & PERF_RECORD_KSYMBOL_FLAGS_UNREGISTER)
		वापस machine__process_ksymbol_unरेजिस्टर(machine, event,
							   sample);
	वापस machine__process_ksymbol_रेजिस्टर(machine, event, sample);
पूर्ण

पूर्णांक machine__process_text_poke(काष्ठा machine *machine, जोड़ perf_event *event,
			       काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा map *map = maps__find(&machine->kmaps, event->text_poke.addr);
	u8 cpumode = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;

	अगर (dump_trace)
		perf_event__ख_लिखो_text_poke(event, machine, मानक_निकास);

	अगर (!event->text_poke.new_len)
		वापस 0;

	अगर (cpumode != PERF_RECORD_MISC_KERNEL) अणु
		pr_debug("%s: unsupported cpumode - ignoring\n", __func__);
		वापस 0;
	पूर्ण

	अगर (map && map->dso) अणु
		u8 *new_bytes = event->text_poke.bytes + event->text_poke.old_len;
		पूर्णांक ret;

		/*
		 * Kernel maps might be changed when loading symbols so loading
		 * must be करोne prior to using kernel maps.
		 */
		map__load(map);
		ret = dso__data_ग_लिखो_cache_addr(map->dso, map, machine,
						 event->text_poke.addr,
						 new_bytes,
						 event->text_poke.new_len);
		अगर (ret != event->text_poke.new_len)
			pr_debug("Failed to write kernel text poke at %#" PRI_lx64 "\n",
				 event->text_poke.addr);
	पूर्ण अन्यथा अणु
		pr_debug("Failed to find kernel text poke address map for %#" PRI_lx64 "\n",
			 event->text_poke.addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा map *machine__addnew_module_map(काष्ठा machine *machine, u64 start,
					      स्थिर अक्षर *filename)
अणु
	काष्ठा map *map = शून्य;
	काष्ठा kmod_path m;
	काष्ठा dso *dso;

	अगर (kmod_path__parse_name(&m, filename))
		वापस शून्य;

	dso = machine__findnew_module_dso(machine, &m, filename);
	अगर (dso == शून्य)
		जाओ out;

	map = map__new2(start, dso);
	अगर (map == शून्य)
		जाओ out;

	maps__insert(&machine->kmaps, map);

	/* Put the map here because maps__insert alपढ़ोy got it */
	map__put(map);
out:
	/* put the dso here, corresponding to  machine__findnew_module_dso */
	dso__put(dso);
	zमुक्त(&m.name);
	वापस map;
पूर्ण

माप_प्रकार machines__ख_लिखो_dsos(काष्ठा machines *machines, खाता *fp)
अणु
	काष्ठा rb_node *nd;
	माप_प्रकार ret = __dsos__ख_लिखो(&machines->host.dsos.head, fp);

	क्रम (nd = rb_first_cached(&machines->guests); nd; nd = rb_next(nd)) अणु
		काष्ठा machine *pos = rb_entry(nd, काष्ठा machine, rb_node);
		ret += __dsos__ख_लिखो(&pos->dsos.head, fp);
	पूर्ण

	वापस ret;
पूर्ण

माप_प्रकार machine__ख_लिखो_dsos_buildid(काष्ठा machine *m, खाता *fp,
				     bool (skip)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm)
अणु
	वापस __dsos__ख_लिखो_buildid(&m->dsos.head, fp, skip, parm);
पूर्ण

माप_प्रकार machines__ख_लिखो_dsos_buildid(काष्ठा machines *machines, खाता *fp,
				     bool (skip)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm)
अणु
	काष्ठा rb_node *nd;
	माप_प्रकार ret = machine__ख_लिखो_dsos_buildid(&machines->host, fp, skip, parm);

	क्रम (nd = rb_first_cached(&machines->guests); nd; nd = rb_next(nd)) अणु
		काष्ठा machine *pos = rb_entry(nd, काष्ठा machine, rb_node);
		ret += machine__ख_लिखो_dsos_buildid(pos, fp, skip, parm);
	पूर्ण
	वापस ret;
पूर्ण

माप_प्रकार machine__ख_लिखो_vmlinux_path(काष्ठा machine *machine, खाता *fp)
अणु
	पूर्णांक i;
	माप_प्रकार prपूर्णांकed = 0;
	काष्ठा dso *kdso = machine__kernel_dso(machine);

	अगर (kdso->has_build_id) अणु
		अक्षर filename[PATH_MAX];
		अगर (dso__build_id_filename(kdso, filename, माप(filename),
					   false))
			prपूर्णांकed += ख_लिखो(fp, "[0] %s\n", filename);
	पूर्ण

	क्रम (i = 0; i < vmlinux_path__nr_entries; ++i)
		prपूर्णांकed += ख_लिखो(fp, "[%d] %s\n",
				   i + kdso->has_build_id, vmlinux_path[i]);

	वापस prपूर्णांकed;
पूर्ण

माप_प्रकार machine__ख_लिखो(काष्ठा machine *machine, खाता *fp)
अणु
	काष्ठा rb_node *nd;
	माप_प्रकार ret;
	पूर्णांक i;

	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++) अणु
		काष्ठा thपढ़ोs *thपढ़ोs = &machine->thपढ़ोs[i];

		करोwn_पढ़ो(&thपढ़ोs->lock);

		ret = ख_लिखो(fp, "Threads: %u\n", thपढ़ोs->nr);

		क्रम (nd = rb_first_cached(&thपढ़ोs->entries); nd;
		     nd = rb_next(nd)) अणु
			काष्ठा thपढ़ो *pos = rb_entry(nd, काष्ठा thपढ़ो, rb_node);

			ret += thपढ़ो__ख_लिखो(pos, fp);
		पूर्ण

		up_पढ़ो(&thपढ़ोs->lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा dso *machine__get_kernel(काष्ठा machine *machine)
अणु
	स्थिर अक्षर *vmlinux_name = machine->mmap_name;
	काष्ठा dso *kernel;

	अगर (machine__is_host(machine)) अणु
		अगर (symbol_conf.vmlinux_name)
			vmlinux_name = symbol_conf.vmlinux_name;

		kernel = machine__findnew_kernel(machine, vmlinux_name,
						 "[kernel]", DSO_SPACE__KERNEL);
	पूर्ण अन्यथा अणु
		अगर (symbol_conf.शेष_guest_vmlinux_name)
			vmlinux_name = symbol_conf.शेष_guest_vmlinux_name;

		kernel = machine__findnew_kernel(machine, vmlinux_name,
						 "[guest.kernel]",
						 DSO_SPACE__KERNEL_GUEST);
	पूर्ण

	अगर (kernel != शून्य && (!kernel->has_build_id))
		dso__पढ़ो_running_kernel_build_id(kernel, machine);

	वापस kernel;
पूर्ण

काष्ठा process_args अणु
	u64 start;
पूर्ण;

व्योम machine__get_kallsyms_filename(काष्ठा machine *machine, अक्षर *buf,
				    माप_प्रकार bufsz)
अणु
	अगर (machine__is_शेष_guest(machine))
		scnम_लिखो(buf, bufsz, "%s", symbol_conf.शेष_guest_kallsyms);
	अन्यथा
		scnम_लिखो(buf, bufsz, "%s/proc/kallsyms", machine->root_dir);
पूर्ण

स्थिर अक्षर *ref_reloc_sym_names[] = अणु"_text", "_stext", शून्यपूर्ण;

/* Figure out the start address of kernel map from /proc/kallsyms.
 * Returns the name of the start symbol in *symbol_name. Pass in शून्य as
 * symbol_name अगर it's not that important.
 */
अटल पूर्णांक machine__get_running_kernel_start(काष्ठा machine *machine,
					     स्थिर अक्षर **symbol_name,
					     u64 *start, u64 *end)
अणु
	अक्षर filename[PATH_MAX];
	पूर्णांक i, err = -1;
	स्थिर अक्षर *name;
	u64 addr = 0;

	machine__get_kallsyms_filename(machine, filename, PATH_MAX);

	अगर (symbol__restricted_filename(filename, "/proc/kallsyms"))
		वापस 0;

	क्रम (i = 0; (name = ref_reloc_sym_names[i]) != शून्य; i++) अणु
		err = kallsyms__get_function_start(filename, name, &addr);
		अगर (!err)
			अवरोध;
	पूर्ण

	अगर (err)
		वापस -1;

	अगर (symbol_name)
		*symbol_name = name;

	*start = addr;

	err = kallsyms__get_function_start(filename, "_etext", &addr);
	अगर (!err)
		*end = addr;

	वापस 0;
पूर्ण

पूर्णांक machine__create_extra_kernel_map(काष्ठा machine *machine,
				     काष्ठा dso *kernel,
				     काष्ठा extra_kernel_map *xm)
अणु
	काष्ठा kmap *kmap;
	काष्ठा map *map;

	map = map__new2(xm->start, kernel);
	अगर (!map)
		वापस -1;

	map->end   = xm->end;
	map->pgoff = xm->pgoff;

	kmap = map__kmap(map);

	strlcpy(kmap->name, xm->name, KMAP_NAME_LEN);

	maps__insert(&machine->kmaps, map);

	pr_debug2("Added extra kernel map %s %" PRIx64 "-%" PRIx64 "\n",
		  kmap->name, map->start, map->end);

	map__put(map);

	वापस 0;
पूर्ण

अटल u64 find_entry_trampoline(काष्ठा dso *dso)
अणु
	/* Duplicates are हटाओd so lookup all aliases */
	स्थिर अक्षर *syms[] = अणु
		"_entry_trampoline",
		"__entry_trampoline_start",
		"entry_SYSCALL_64_trampoline",
	पूर्ण;
	काष्ठा symbol *sym = dso__first_symbol(dso);
	अचिन्हित पूर्णांक i;

	क्रम (; sym; sym = dso__next_symbol(sym)) अणु
		अगर (sym->binding != STB_GLOBAL)
			जारी;
		क्रम (i = 0; i < ARRAY_SIZE(syms); i++) अणु
			अगर (!म_भेद(sym->name, syms[i]))
				वापस sym->start;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * These values can be used क्रम kernels that करो not have symbols क्रम the entry
 * trampolines in kallsyms.
 */
#घोषणा X86_64_CPU_ENTRY_AREA_PER_CPU	0xfffffe0000000000ULL
#घोषणा X86_64_CPU_ENTRY_AREA_SIZE	0x2c000
#घोषणा X86_64_ENTRY_TRAMPOLINE		0x6000

/* Map x86_64 PTI entry trampolines */
पूर्णांक machine__map_x86_64_entry_trampolines(काष्ठा machine *machine,
					  काष्ठा dso *kernel)
अणु
	काष्ठा maps *kmaps = &machine->kmaps;
	पूर्णांक nr_cpus_avail, cpu;
	bool found = false;
	काष्ठा map *map;
	u64 pgoff;

	/*
	 * In the vmlinux हाल, pgoff is a भव address which must now be
	 * mapped to a vmlinux offset.
	 */
	maps__क्रम_each_entry(kmaps, map) अणु
		काष्ठा kmap *kmap = __map__kmap(map);
		काष्ठा map *dest_map;

		अगर (!kmap || !is_entry_trampoline(kmap->name))
			जारी;

		dest_map = maps__find(kmaps, map->pgoff);
		अगर (dest_map != map)
			map->pgoff = dest_map->map_ip(dest_map, map->pgoff);
		found = true;
	पूर्ण
	अगर (found || machine->trampolines_mapped)
		वापस 0;

	pgoff = find_entry_trampoline(kernel);
	अगर (!pgoff)
		वापस 0;

	nr_cpus_avail = machine__nr_cpus_avail(machine);

	/* Add a 1 page map क्रम each CPU's entry trampoline */
	क्रम (cpu = 0; cpu < nr_cpus_avail; cpu++) अणु
		u64 va = X86_64_CPU_ENTRY_AREA_PER_CPU +
			 cpu * X86_64_CPU_ENTRY_AREA_SIZE +
			 X86_64_ENTRY_TRAMPOLINE;
		काष्ठा extra_kernel_map xm = अणु
			.start = va,
			.end   = va + page_size,
			.pgoff = pgoff,
		पूर्ण;

		strlcpy(xm.name, ENTRY_TRAMPOLINE_NAME, KMAP_NAME_LEN);

		अगर (machine__create_extra_kernel_map(machine, kernel, &xm) < 0)
			वापस -1;
	पूर्ण

	machine->trampolines_mapped = nr_cpus_avail;

	वापस 0;
पूर्ण

पूर्णांक __weak machine__create_extra_kernel_maps(काष्ठा machine *machine __maybe_unused,
					     काष्ठा dso *kernel __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
__machine__create_kernel_maps(काष्ठा machine *machine, काष्ठा dso *kernel)
अणु
	/* In हाल of renewal the kernel map, destroy previous one */
	machine__destroy_kernel_maps(machine);

	machine->vmlinux_map = map__new2(0, kernel);
	अगर (machine->vmlinux_map == शून्य)
		वापस -1;

	machine->vmlinux_map->map_ip = machine->vmlinux_map->unmap_ip = identity__map_ip;
	maps__insert(&machine->kmaps, machine->vmlinux_map);
	वापस 0;
पूर्ण

व्योम machine__destroy_kernel_maps(काष्ठा machine *machine)
अणु
	काष्ठा kmap *kmap;
	काष्ठा map *map = machine__kernel_map(machine);

	अगर (map == शून्य)
		वापस;

	kmap = map__kmap(map);
	maps__हटाओ(&machine->kmaps, map);
	अगर (kmap && kmap->ref_reloc_sym) अणु
		zमुक्त((अक्षर **)&kmap->ref_reloc_sym->name);
		zमुक्त(&kmap->ref_reloc_sym);
	पूर्ण

	map__zput(machine->vmlinux_map);
पूर्ण

पूर्णांक machines__create_guest_kernel_maps(काष्ठा machines *machines)
अणु
	पूर्णांक ret = 0;
	काष्ठा dirent **namelist = शून्य;
	पूर्णांक i, items = 0;
	अक्षर path[PATH_MAX];
	pid_t pid;
	अक्षर *endp;

	अगर (symbol_conf.शेष_guest_vmlinux_name ||
	    symbol_conf.शेष_guest_modules ||
	    symbol_conf.शेष_guest_kallsyms) अणु
		machines__create_kernel_maps(machines, DEFAULT_GUEST_KERNEL_ID);
	पूर्ण

	अगर (symbol_conf.guesपंचांगount) अणु
		items = scandir(symbol_conf.guesपंचांगount, &namelist, शून्य, शून्य);
		अगर (items <= 0)
			वापस -ENOENT;
		क्रम (i = 0; i < items; i++) अणु
			अगर (!है_अंक(namelist[i]->d_name[0])) अणु
				/* Filter out . and .. */
				जारी;
			पूर्ण
			pid = (pid_t)म_से_दीर्घ(namelist[i]->d_name, &endp, 10);
			अगर ((*endp != '\0') ||
			    (endp == namelist[i]->d_name) ||
			    (त्रुटि_सं == दुस्फल)) अणु
				pr_debug("invalid directory (%s). Skipping.\n",
					 namelist[i]->d_name);
				जारी;
			पूर्ण
			प्र_लिखो(path, "%s/%s/proc/kallsyms",
				symbol_conf.guesपंचांगount,
				namelist[i]->d_name);
			ret = access(path, R_OK);
			अगर (ret) अणु
				pr_debug("Can't access file %s\n", path);
				जाओ failure;
			पूर्ण
			machines__create_kernel_maps(machines, pid);
		पूर्ण
failure:
		मुक्त(namelist);
	पूर्ण

	वापस ret;
पूर्ण

व्योम machines__destroy_kernel_maps(काष्ठा machines *machines)
अणु
	काष्ठा rb_node *next = rb_first_cached(&machines->guests);

	machine__destroy_kernel_maps(&machines->host);

	जबतक (next) अणु
		काष्ठा machine *pos = rb_entry(next, काष्ठा machine, rb_node);

		next = rb_next(&pos->rb_node);
		rb_erase_cached(&pos->rb_node, &machines->guests);
		machine__delete(pos);
	पूर्ण
पूर्ण

पूर्णांक machines__create_kernel_maps(काष्ठा machines *machines, pid_t pid)
अणु
	काष्ठा machine *machine = machines__findnew(machines, pid);

	अगर (machine == शून्य)
		वापस -1;

	वापस machine__create_kernel_maps(machine);
पूर्ण

पूर्णांक machine__load_kallsyms(काष्ठा machine *machine, स्थिर अक्षर *filename)
अणु
	काष्ठा map *map = machine__kernel_map(machine);
	पूर्णांक ret = __dso__load_kallsyms(map->dso, filename, map, true);

	अगर (ret > 0) अणु
		dso__set_loaded(map->dso);
		/*
		 * Since /proc/kallsyms will have multiple sessions क्रम the
		 * kernel, with modules between them, fixup the end of all
		 * sections.
		 */
		maps__fixup_end(&machine->kmaps);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक machine__load_vmlinux_path(काष्ठा machine *machine)
अणु
	काष्ठा map *map = machine__kernel_map(machine);
	पूर्णांक ret = dso__load_vmlinux_path(map->dso, map);

	अगर (ret > 0)
		dso__set_loaded(map->dso);

	वापस ret;
पूर्ण

अटल अक्षर *get_kernel_version(स्थिर अक्षर *root_dir)
अणु
	अक्षर version[PATH_MAX];
	खाता *file;
	अक्षर *name, *पंचांगp;
	स्थिर अक्षर *prefix = "Linux version ";

	प्र_लिखो(version, "%s/proc/version", root_dir);
	file = ख_खोलो(version, "r");
	अगर (!file)
		वापस शून्य;

	पंचांगp = ख_माला_लो(version, माप(version), file);
	ख_बंद(file);
	अगर (!पंचांगp)
		वापस शून्य;

	name = म_माला(version, prefix);
	अगर (!name)
		वापस शून्य;
	name += म_माप(prefix);
	पंचांगp = म_अक्षर(name, ' ');
	अगर (पंचांगp)
		*पंचांगp = '\0';

	वापस strdup(name);
पूर्ण

अटल bool is_kmod_dso(काष्ठा dso *dso)
अणु
	वापस dso->symtab_type == DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE ||
	       dso->symtab_type == DSO_BINARY_TYPE__GUEST_KMODULE;
पूर्ण

अटल पूर्णांक maps__set_module_path(काष्ठा maps *maps, स्थिर अक्षर *path, काष्ठा kmod_path *m)
अणु
	अक्षर *दीर्घ_name;
	काष्ठा map *map = maps__find_by_name(maps, m->name);

	अगर (map == शून्य)
		वापस 0;

	दीर्घ_name = strdup(path);
	अगर (दीर्घ_name == शून्य)
		वापस -ENOMEM;

	dso__set_दीर्घ_name(map->dso, दीर्घ_name, true);
	dso__kernel_module_get_build_id(map->dso, "");

	/*
	 * Full name could reveal us kmod compression, so
	 * we need to update the symtab_type अगर needed.
	 */
	अगर (m->comp && is_kmod_dso(map->dso)) अणु
		map->dso->symtab_type++;
		map->dso->comp = m->comp;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक maps__set_modules_path_dir(काष्ठा maps *maps, स्थिर अक्षर *dir_name, पूर्णांक depth)
अणु
	काष्ठा dirent *dent;
	सूची *dir = सूची_खोलो(dir_name);
	पूर्णांक ret = 0;

	अगर (!dir) अणु
		pr_debug("%s: cannot open %s dir\n", __func__, dir_name);
		वापस -1;
	पूर्ण

	जबतक ((dent = सूची_पढ़ो(dir)) != शून्य) अणु
		अक्षर path[PATH_MAX];
		काष्ठा stat st;

		/*sshfs might वापस bad dent->d_type, so we have to stat*/
		snम_लिखो(path, माप(path), "%s/%s", dir_name, dent->d_name);
		अगर (stat(path, &st))
			जारी;

		अगर (S_ISसूची(st.st_mode)) अणु
			अगर (!म_भेद(dent->d_name, ".") ||
			    !म_भेद(dent->d_name, ".."))
				जारी;

			/* Do not follow top-level source and build symlinks */
			अगर (depth == 0) अणु
				अगर (!म_भेद(dent->d_name, "source") ||
				    !म_भेद(dent->d_name, "build"))
					जारी;
			पूर्ण

			ret = maps__set_modules_path_dir(maps, path, depth + 1);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अणु
			काष्ठा kmod_path m;

			ret = kmod_path__parse_name(&m, dent->d_name);
			अगर (ret)
				जाओ out;

			अगर (m.kmod)
				ret = maps__set_module_path(maps, path, &m);

			zमुक्त(&m.name);

			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	बंद_सूची(dir);
	वापस ret;
पूर्ण

अटल पूर्णांक machine__set_modules_path(काष्ठा machine *machine)
अणु
	अक्षर *version;
	अक्षर modules_path[PATH_MAX];

	version = get_kernel_version(machine->root_dir);
	अगर (!version)
		वापस -1;

	snम_लिखो(modules_path, माप(modules_path), "%s/lib/modules/%s",
		 machine->root_dir, version);
	मुक्त(version);

	वापस maps__set_modules_path_dir(&machine->kmaps, modules_path, 0);
पूर्ण
पूर्णांक __weak arch__fix_module_text_start(u64 *start __maybe_unused,
				u64 *size __maybe_unused,
				स्थिर अक्षर *name __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक machine__create_module(व्योम *arg, स्थिर अक्षर *name, u64 start,
				  u64 size)
अणु
	काष्ठा machine *machine = arg;
	काष्ठा map *map;

	अगर (arch__fix_module_text_start(&start, &size, name) < 0)
		वापस -1;

	map = machine__addnew_module_map(machine, start, name);
	अगर (map == शून्य)
		वापस -1;
	map->end = start + size;

	dso__kernel_module_get_build_id(map->dso, machine->root_dir);

	वापस 0;
पूर्ण

अटल पूर्णांक machine__create_modules(काष्ठा machine *machine)
अणु
	स्थिर अक्षर *modules;
	अक्षर path[PATH_MAX];

	अगर (machine__is_शेष_guest(machine)) अणु
		modules = symbol_conf.शेष_guest_modules;
	पूर्ण अन्यथा अणु
		snम_लिखो(path, PATH_MAX, "%s/proc/modules", machine->root_dir);
		modules = path;
	पूर्ण

	अगर (symbol__restricted_filename(modules, "/proc/modules"))
		वापस -1;

	अगर (modules__parse(modules, machine, machine__create_module))
		वापस -1;

	अगर (!machine__set_modules_path(machine))
		वापस 0;

	pr_debug("Problems setting modules path maps, continuing anyway...\n");

	वापस 0;
पूर्ण

अटल व्योम machine__set_kernel_mmap(काष्ठा machine *machine,
				     u64 start, u64 end)
अणु
	machine->vmlinux_map->start = start;
	machine->vmlinux_map->end   = end;
	/*
	 * Be a bit paranoid here, some perf.data file came with
	 * a zero sized synthesized MMAP event क्रम the kernel.
	 */
	अगर (start == 0 && end == 0)
		machine->vmlinux_map->end = ~0ULL;
पूर्ण

अटल व्योम machine__update_kernel_mmap(काष्ठा machine *machine,
				     u64 start, u64 end)
अणु
	काष्ठा map *map = machine__kernel_map(machine);

	map__get(map);
	maps__हटाओ(&machine->kmaps, map);

	machine__set_kernel_mmap(machine, start, end);

	maps__insert(&machine->kmaps, map);
	map__put(map);
पूर्ण

पूर्णांक machine__create_kernel_maps(काष्ठा machine *machine)
अणु
	काष्ठा dso *kernel = machine__get_kernel(machine);
	स्थिर अक्षर *name = शून्य;
	काष्ठा map *map;
	u64 start = 0, end = ~0ULL;
	पूर्णांक ret;

	अगर (kernel == शून्य)
		वापस -1;

	ret = __machine__create_kernel_maps(machine, kernel);
	अगर (ret < 0)
		जाओ out_put;

	अगर (symbol_conf.use_modules && machine__create_modules(machine) < 0) अणु
		अगर (machine__is_host(machine))
			pr_debug("Problems creating module maps, "
				 "continuing anyway...\n");
		अन्यथा
			pr_debug("Problems creating module maps for guest %d, "
				 "continuing anyway...\n", machine->pid);
	पूर्ण

	अगर (!machine__get_running_kernel_start(machine, &name, &start, &end)) अणु
		अगर (name &&
		    map__set_kallsyms_ref_reloc_sym(machine->vmlinux_map, name, start)) अणु
			machine__destroy_kernel_maps(machine);
			ret = -1;
			जाओ out_put;
		पूर्ण

		/*
		 * we have a real start address now, so re-order the kmaps
		 * assume it's the last in the kmaps
		 */
		machine__update_kernel_mmap(machine, start, end);
	पूर्ण

	अगर (machine__create_extra_kernel_maps(machine, kernel))
		pr_debug("Problems creating extra kernel maps, continuing anyway...\n");

	अगर (end == ~0ULL) अणु
		/* update end address of the kernel map using adjacent module address */
		map = map__next(machine__kernel_map(machine));
		अगर (map)
			machine__set_kernel_mmap(machine, start, map->start);
	पूर्ण

out_put:
	dso__put(kernel);
	वापस ret;
पूर्ण

अटल bool machine__uses_kcore(काष्ठा machine *machine)
अणु
	काष्ठा dso *dso;

	list_क्रम_each_entry(dso, &machine->dsos.head, node) अणु
		अगर (dso__is_kcore(dso))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool perf_event__is_extra_kernel_mmap(काष्ठा machine *machine,
					     काष्ठा extra_kernel_map *xm)
अणु
	वापस machine__is(machine, "x86_64") &&
	       is_entry_trampoline(xm->name);
पूर्ण

अटल पूर्णांक machine__process_extra_kernel_map(काष्ठा machine *machine,
					     काष्ठा extra_kernel_map *xm)
अणु
	काष्ठा dso *kernel = machine__kernel_dso(machine);

	अगर (kernel == शून्य)
		वापस -1;

	वापस machine__create_extra_kernel_map(machine, kernel, xm);
पूर्ण

अटल पूर्णांक machine__process_kernel_mmap_event(काष्ठा machine *machine,
					      काष्ठा extra_kernel_map *xm,
					      काष्ठा build_id *bid)
अणु
	काष्ठा map *map;
	क्रमागत dso_space_type dso_space;
	bool is_kernel_mmap;

	/* If we have maps from kcore then we करो not need or want any others */
	अगर (machine__uses_kcore(machine))
		वापस 0;

	अगर (machine__is_host(machine))
		dso_space = DSO_SPACE__KERNEL;
	अन्यथा
		dso_space = DSO_SPACE__KERNEL_GUEST;

	is_kernel_mmap = स_भेद(xm->name, machine->mmap_name,
				म_माप(machine->mmap_name) - 1) == 0;
	अगर (xm->name[0] == '/' ||
	    (!is_kernel_mmap && xm->name[0] == '[')) अणु
		map = machine__addnew_module_map(machine, xm->start,
						 xm->name);
		अगर (map == शून्य)
			जाओ out_problem;

		map->end = map->start + xm->end - xm->start;

		अगर (build_id__is_defined(bid))
			dso__set_build_id(map->dso, bid);

	पूर्ण अन्यथा अगर (is_kernel_mmap) अणु
		स्थिर अक्षर *symbol_name = (xm->name + म_माप(machine->mmap_name));
		/*
		 * Should be there alपढ़ोy, from the build-id table in
		 * the header.
		 */
		काष्ठा dso *kernel = शून्य;
		काष्ठा dso *dso;

		करोwn_पढ़ो(&machine->dsos.lock);

		list_क्रम_each_entry(dso, &machine->dsos.head, node) अणु

			/*
			 * The cpumode passed to is_kernel_module is not the
			 * cpumode of *this* event. If we insist on passing
			 * correct cpumode to is_kernel_module, we should
			 * record the cpumode when we adding this dso to the
			 * linked list.
			 *
			 * However we करोn't really need passing correct
			 * cpumode.  We know the correct cpumode must be kernel
			 * mode (अगर not, we should not link it onto kernel_dsos
			 * list).
			 *
			 * Thereक्रमe, we pass PERF_RECORD_MISC_CPUMODE_UNKNOWN.
			 * is_kernel_module() treats it as a kernel cpumode.
			 */

			अगर (!dso->kernel ||
			    is_kernel_module(dso->दीर्घ_name,
					     PERF_RECORD_MISC_CPUMODE_UNKNOWN))
				जारी;


			kernel = dso;
			अवरोध;
		पूर्ण

		up_पढ़ो(&machine->dsos.lock);

		अगर (kernel == शून्य)
			kernel = machine__findnew_dso(machine, machine->mmap_name);
		अगर (kernel == शून्य)
			जाओ out_problem;

		kernel->kernel = dso_space;
		अगर (__machine__create_kernel_maps(machine, kernel) < 0) अणु
			dso__put(kernel);
			जाओ out_problem;
		पूर्ण

		अगर (म_माला(kernel->दीर्घ_name, "vmlinux"))
			dso__set_लघु_name(kernel, "[kernel.vmlinux]", false);

		machine__update_kernel_mmap(machine, xm->start, xm->end);

		अगर (build_id__is_defined(bid))
			dso__set_build_id(kernel, bid);

		/*
		 * Aव्योम using a zero address (kptr_restrict) क्रम the ref reloc
		 * symbol. Effectively having zero here means that at record
		 * समय /proc/sys/kernel/kptr_restrict was non zero.
		 */
		अगर (xm->pgoff != 0) अणु
			map__set_kallsyms_ref_reloc_sym(machine->vmlinux_map,
							symbol_name,
							xm->pgoff);
		पूर्ण

		अगर (machine__is_शेष_guest(machine)) अणु
			/*
			 * preload dso of guest kernel and modules
			 */
			dso__load(kernel, machine__kernel_map(machine));
		पूर्ण
	पूर्ण अन्यथा अगर (perf_event__is_extra_kernel_mmap(machine, xm)) अणु
		वापस machine__process_extra_kernel_map(machine, xm);
	पूर्ण
	वापस 0;
out_problem:
	वापस -1;
पूर्ण

पूर्णांक machine__process_mmap2_event(काष्ठा machine *machine,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा map *map;
	काष्ठा dso_id dso_id = अणु
		.maj = event->mmap2.maj,
		.min = event->mmap2.min,
		.ino = event->mmap2.ino,
		.ino_generation = event->mmap2.ino_generation,
	पूर्ण;
	काष्ठा build_id __bid, *bid = शून्य;
	पूर्णांक ret = 0;

	अगर (dump_trace)
		perf_event__ख_लिखो_mmap2(event, मानक_निकास);

	अगर (event->header.misc & PERF_RECORD_MISC_MMAP_BUILD_ID) अणु
		bid = &__bid;
		build_id__init(bid, event->mmap2.build_id, event->mmap2.build_id_size);
	पूर्ण

	अगर (sample->cpumode == PERF_RECORD_MISC_GUEST_KERNEL ||
	    sample->cpumode == PERF_RECORD_MISC_KERNEL) अणु
		काष्ठा extra_kernel_map xm = अणु
			.start = event->mmap2.start,
			.end   = event->mmap2.start + event->mmap2.len,
			.pgoff = event->mmap2.pgoff,
		पूर्ण;

		strlcpy(xm.name, event->mmap2.filename, KMAP_NAME_LEN);
		ret = machine__process_kernel_mmap_event(machine, &xm, bid);
		अगर (ret < 0)
			जाओ out_problem;
		वापस 0;
	पूर्ण

	thपढ़ो = machine__findnew_thपढ़ो(machine, event->mmap2.pid,
					event->mmap2.tid);
	अगर (thपढ़ो == शून्य)
		जाओ out_problem;

	map = map__new(machine, event->mmap2.start,
			event->mmap2.len, event->mmap2.pgoff,
			&dso_id, event->mmap2.prot,
			event->mmap2.flags, bid,
			event->mmap2.filename, thपढ़ो);

	अगर (map == शून्य)
		जाओ out_problem_map;

	ret = thपढ़ो__insert_map(thपढ़ो, map);
	अगर (ret)
		जाओ out_problem_insert;

	thपढ़ो__put(thपढ़ो);
	map__put(map);
	वापस 0;

out_problem_insert:
	map__put(map);
out_problem_map:
	thपढ़ो__put(thपढ़ो);
out_problem:
	dump_म_लिखो("problem processing PERF_RECORD_MMAP2, skipping event.\n");
	वापस 0;
पूर्ण

पूर्णांक machine__process_mmap_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा map *map;
	u32 prot = 0;
	पूर्णांक ret = 0;

	अगर (dump_trace)
		perf_event__ख_लिखो_mmap(event, मानक_निकास);

	अगर (sample->cpumode == PERF_RECORD_MISC_GUEST_KERNEL ||
	    sample->cpumode == PERF_RECORD_MISC_KERNEL) अणु
		काष्ठा extra_kernel_map xm = अणु
			.start = event->mmap.start,
			.end   = event->mmap.start + event->mmap.len,
			.pgoff = event->mmap.pgoff,
		पूर्ण;

		strlcpy(xm.name, event->mmap.filename, KMAP_NAME_LEN);
		ret = machine__process_kernel_mmap_event(machine, &xm, शून्य);
		अगर (ret < 0)
			जाओ out_problem;
		वापस 0;
	पूर्ण

	thपढ़ो = machine__findnew_thपढ़ो(machine, event->mmap.pid,
					 event->mmap.tid);
	अगर (thपढ़ो == शून्य)
		जाओ out_problem;

	अगर (!(event->header.misc & PERF_RECORD_MISC_MMAP_DATA))
		prot = PROT_EXEC;

	map = map__new(machine, event->mmap.start,
			event->mmap.len, event->mmap.pgoff,
			शून्य, prot, 0, शून्य, event->mmap.filename, thपढ़ो);

	अगर (map == शून्य)
		जाओ out_problem_map;

	ret = thपढ़ो__insert_map(thपढ़ो, map);
	अगर (ret)
		जाओ out_problem_insert;

	thपढ़ो__put(thपढ़ो);
	map__put(map);
	वापस 0;

out_problem_insert:
	map__put(map);
out_problem_map:
	thपढ़ो__put(thपढ़ो);
out_problem:
	dump_म_लिखो("problem processing PERF_RECORD_MMAP, skipping event.\n");
	वापस 0;
पूर्ण

अटल व्योम __machine__हटाओ_thपढ़ो(काष्ठा machine *machine, काष्ठा thपढ़ो *th, bool lock)
अणु
	काष्ठा thपढ़ोs *thपढ़ोs = machine__thपढ़ोs(machine, th->tid);

	अगर (thपढ़ोs->last_match == th)
		thपढ़ोs__set_last_match(thपढ़ोs, शून्य);

	अगर (lock)
		करोwn_ग_लिखो(&thपढ़ोs->lock);

	BUG_ON(refcount_पढ़ो(&th->refcnt) == 0);

	rb_erase_cached(&th->rb_node, &thपढ़ोs->entries);
	RB_CLEAR_NODE(&th->rb_node);
	--thपढ़ोs->nr;
	/*
	 * Move it first to the dead_thपढ़ोs list, then drop the reference,
	 * अगर this is the last reference, then the thपढ़ो__delete deकाष्ठाor
	 * will be called and we will हटाओ it from the dead_thपढ़ोs list.
	 */
	list_add_tail(&th->node, &thपढ़ोs->dead);

	/*
	 * We need to करो the put here because अगर this is the last refcount,
	 * then we will be touching the thपढ़ोs->dead head when removing the
	 * thपढ़ो.
	 */
	thपढ़ो__put(th);

	अगर (lock)
		up_ग_लिखो(&thपढ़ोs->lock);
पूर्ण

व्योम machine__हटाओ_thपढ़ो(काष्ठा machine *machine, काष्ठा thपढ़ो *th)
अणु
	वापस __machine__हटाओ_thपढ़ो(machine, th, true);
पूर्ण

पूर्णांक machine__process_विभाजन_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__find_thपढ़ो(machine,
						     event->विभाजन.pid,
						     event->विभाजन.tid);
	काष्ठा thपढ़ो *parent = machine__findnew_thपढ़ो(machine,
							event->विभाजन.ppid,
							event->विभाजन.ptid);
	bool करो_maps_clone = true;
	पूर्णांक err = 0;

	अगर (dump_trace)
		perf_event__ख_लिखो_task(event, मानक_निकास);

	/*
	 * There may be an existing thपढ़ो that is not actually the parent,
	 * either because we are processing events out of order, or because the
	 * (विभाजन) event that would have हटाओd the thपढ़ो was lost. Assume the
	 * latter हाल and जारी on as best we can.
	 */
	अगर (parent->pid_ != (pid_t)event->विभाजन.ppid) अणु
		dump_म_लिखो("removing erroneous parent thread %d/%d\n",
			    parent->pid_, parent->tid);
		machine__हटाओ_thपढ़ो(machine, parent);
		thपढ़ो__put(parent);
		parent = machine__findnew_thपढ़ो(machine, event->विभाजन.ppid,
						 event->विभाजन.ptid);
	पूर्ण

	/* अगर a thपढ़ो currently exists क्रम the thपढ़ो id हटाओ it */
	अगर (thपढ़ो != शून्य) अणु
		machine__हटाओ_thपढ़ो(machine, thपढ़ो);
		thपढ़ो__put(thपढ़ो);
	पूर्ण

	thपढ़ो = machine__findnew_thपढ़ो(machine, event->विभाजन.pid,
					 event->विभाजन.tid);
	/*
	 * When synthesizing FORK events, we are trying to create thपढ़ो
	 * objects क्रम the alपढ़ोy running tasks on the machine.
	 *
	 * Normally, क्रम a kernel FORK event, we want to clone the parent's
	 * maps because that is what the kernel just did.
	 *
	 * But when synthesizing, this should not be करोne.  If we करो, we end up
	 * with overlapping maps as we process the synthesized MMAP2 events that
	 * get delivered लघुly thereafter.
	 *
	 * Use the FORK event misc flags in an पूर्णांकernal way to संकेत this
	 * situation, so we can elide the map clone when appropriate.
	 */
	अगर (event->विभाजन.header.misc & PERF_RECORD_MISC_FORK_EXEC)
		करो_maps_clone = false;

	अगर (thपढ़ो == शून्य || parent == शून्य ||
	    thपढ़ो__विभाजन(thपढ़ो, parent, sample->समय, करो_maps_clone) < 0) अणु
		dump_म_लिखो("problem processing PERF_RECORD_FORK, skipping event.\n");
		err = -1;
	पूर्ण
	thपढ़ो__put(thपढ़ो);
	thपढ़ो__put(parent);

	वापस err;
पूर्ण

पूर्णांक machine__process_निकास_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__find_thपढ़ो(machine,
						     event->विभाजन.pid,
						     event->विभाजन.tid);

	अगर (dump_trace)
		perf_event__ख_लिखो_task(event, मानक_निकास);

	अगर (thपढ़ो != शून्य) अणु
		thपढ़ो__निकासed(thपढ़ो);
		thपढ़ो__put(thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक machine__process_event(काष्ठा machine *machine, जोड़ perf_event *event,
			   काष्ठा perf_sample *sample)
अणु
	पूर्णांक ret;

	चयन (event->header.type) अणु
	हाल PERF_RECORD_COMM:
		ret = machine__process_comm_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_MMAP:
		ret = machine__process_mmap_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_NAMESPACES:
		ret = machine__process_namespaces_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_CGROUP:
		ret = machine__process_cgroup_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_MMAP2:
		ret = machine__process_mmap2_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_FORK:
		ret = machine__process_विभाजन_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_EXIT:
		ret = machine__process_निकास_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_LOST:
		ret = machine__process_lost_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_AUX:
		ret = machine__process_aux_event(machine, event); अवरोध;
	हाल PERF_RECORD_ITRACE_START:
		ret = machine__process_itrace_start_event(machine, event); अवरोध;
	हाल PERF_RECORD_LOST_SAMPLES:
		ret = machine__process_lost_samples_event(machine, event, sample); अवरोध;
	हाल PERF_RECORD_SWITCH:
	हाल PERF_RECORD_SWITCH_CPU_WIDE:
		ret = machine__process_चयन_event(machine, event); अवरोध;
	हाल PERF_RECORD_KSYMBOL:
		ret = machine__process_ksymbol(machine, event, sample); अवरोध;
	हाल PERF_RECORD_BPF_EVENT:
		ret = machine__process_bpf(machine, event, sample); अवरोध;
	हाल PERF_RECORD_TEXT_POKE:
		ret = machine__process_text_poke(machine, event, sample); अवरोध;
	शेष:
		ret = -1;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool symbol__match_regex(काष्ठा symbol *sym, regex_t *regex)
अणु
	अगर (!regexec(regex, sym->name, 0, शून्य, 0))
		वापस true;
	वापस false;
पूर्ण

अटल व्योम ip__resolve_ams(काष्ठा thपढ़ो *thपढ़ो,
			    काष्ठा addr_map_symbol *ams,
			    u64 ip)
अणु
	काष्ठा addr_location al;

	स_रखो(&al, 0, माप(al));
	/*
	 * We cannot use the header.misc hपूर्णांक to determine whether a
	 * branch stack address is user, kernel, guest, hypervisor.
	 * Branches may straddle the kernel/user/hypervisor boundaries.
	 * Thus, we have to try consecutively until we find a match
	 * or अन्यथा, the symbol is unknown
	 */
	thपढ़ो__find_cpumode_addr_location(thपढ़ो, ip, &al);

	ams->addr = ip;
	ams->al_addr = al.addr;
	ams->ms.maps = al.maps;
	ams->ms.sym = al.sym;
	ams->ms.map = al.map;
	ams->phys_addr = 0;
	ams->data_page_size = 0;
पूर्ण

अटल व्योम ip__resolve_data(काष्ठा thपढ़ो *thपढ़ो,
			     u8 m, काष्ठा addr_map_symbol *ams,
			     u64 addr, u64 phys_addr, u64 daddr_page_size)
अणु
	काष्ठा addr_location al;

	स_रखो(&al, 0, माप(al));

	thपढ़ो__find_symbol(thपढ़ो, m, addr, &al);

	ams->addr = addr;
	ams->al_addr = al.addr;
	ams->ms.maps = al.maps;
	ams->ms.sym = al.sym;
	ams->ms.map = al.map;
	ams->phys_addr = phys_addr;
	ams->data_page_size = daddr_page_size;
पूर्ण

काष्ठा mem_info *sample__resolve_mem(काष्ठा perf_sample *sample,
				     काष्ठा addr_location *al)
अणु
	काष्ठा mem_info *mi = mem_info__new();

	अगर (!mi)
		वापस शून्य;

	ip__resolve_ams(al->thपढ़ो, &mi->iaddr, sample->ip);
	ip__resolve_data(al->thपढ़ो, al->cpumode, &mi->daddr,
			 sample->addr, sample->phys_addr,
			 sample->data_page_size);
	mi->data_src.val = sample->data_src;

	वापस mi;
पूर्ण

अटल अक्षर *callchain_srcline(काष्ठा map_symbol *ms, u64 ip)
अणु
	काष्ठा map *map = ms->map;
	अक्षर *srcline = शून्य;

	अगर (!map || callchain_param.key == CCKEY_FUNCTION)
		वापस srcline;

	srcline = srcline__tree_find(&map->dso->srclines, ip);
	अगर (!srcline) अणु
		bool show_sym = false;
		bool show_addr = callchain_param.key == CCKEY_ADDRESS;

		srcline = get_srcline(map->dso, map__rip_2objdump(map, ip),
				      ms->sym, show_sym, show_addr, ip);
		srcline__tree_insert(&map->dso->srclines, ip, srcline);
	पूर्ण

	वापस srcline;
पूर्ण

काष्ठा iterations अणु
	पूर्णांक nr_loop_iter;
	u64 cycles;
पूर्ण;

अटल पूर्णांक add_callchain_ip(काष्ठा thपढ़ो *thपढ़ो,
			    काष्ठा callchain_cursor *cursor,
			    काष्ठा symbol **parent,
			    काष्ठा addr_location *root_al,
			    u8 *cpumode,
			    u64 ip,
			    bool branch,
			    काष्ठा branch_flags *flags,
			    काष्ठा iterations *iter,
			    u64 branch_from)
अणु
	काष्ठा map_symbol ms;
	काष्ठा addr_location al;
	पूर्णांक nr_loop_iter = 0;
	u64 iter_cycles = 0;
	स्थिर अक्षर *srcline = शून्य;

	al.filtered = 0;
	al.sym = शून्य;
	अगर (!cpumode) अणु
		thपढ़ो__find_cpumode_addr_location(thपढ़ो, ip, &al);
	पूर्ण अन्यथा अणु
		अगर (ip >= PERF_CONTEXT_MAX) अणु
			चयन (ip) अणु
			हाल PERF_CONTEXT_HV:
				*cpumode = PERF_RECORD_MISC_HYPERVISOR;
				अवरोध;
			हाल PERF_CONTEXT_KERNEL:
				*cpumode = PERF_RECORD_MISC_KERNEL;
				अवरोध;
			हाल PERF_CONTEXT_USER:
				*cpumode = PERF_RECORD_MISC_USER;
				अवरोध;
			शेष:
				pr_debug("invalid callchain context: "
					 "%"PRId64"\n", (s64) ip);
				/*
				 * It seems the callchain is corrupted.
				 * Discard all.
				 */
				callchain_cursor_reset(cursor);
				वापस 1;
			पूर्ण
			वापस 0;
		पूर्ण
		thपढ़ो__find_symbol(thपढ़ो, *cpumode, ip, &al);
	पूर्ण

	अगर (al.sym != शून्य) अणु
		अगर (perf_hpp_list.parent && !*parent &&
		    symbol__match_regex(al.sym, &parent_regex))
			*parent = al.sym;
		अन्यथा अगर (have_ignore_callees && root_al &&
		  symbol__match_regex(al.sym, &ignore_callees_regex)) अणु
			/* Treat this symbol as the root,
			   क्रमgetting its callees. */
			*root_al = al;
			callchain_cursor_reset(cursor);
		पूर्ण
	पूर्ण

	अगर (symbol_conf.hide_unresolved && al.sym == शून्य)
		वापस 0;

	अगर (iter) अणु
		nr_loop_iter = iter->nr_loop_iter;
		iter_cycles = iter->cycles;
	पूर्ण

	ms.maps = al.maps;
	ms.map = al.map;
	ms.sym = al.sym;
	srcline = callchain_srcline(&ms, al.addr);
	वापस callchain_cursor_append(cursor, ip, &ms,
				       branch, flags, nr_loop_iter,
				       iter_cycles, branch_from, srcline);
पूर्ण

काष्ठा branch_info *sample__resolve_bstack(काष्ठा perf_sample *sample,
					   काष्ठा addr_location *al)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा branch_stack *bs = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	काष्ठा branch_info *bi = सुस्मृति(bs->nr, माप(काष्ठा branch_info));

	अगर (!bi)
		वापस शून्य;

	क्रम (i = 0; i < bs->nr; i++) अणु
		ip__resolve_ams(al->thपढ़ो, &bi[i].to, entries[i].to);
		ip__resolve_ams(al->thपढ़ो, &bi[i].from, entries[i].from);
		bi[i].flags = entries[i].flags;
	पूर्ण
	वापस bi;
पूर्ण

अटल व्योम save_iterations(काष्ठा iterations *iter,
			    काष्ठा branch_entry *be, पूर्णांक nr)
अणु
	पूर्णांक i;

	iter->nr_loop_iter++;
	iter->cycles = 0;

	क्रम (i = 0; i < nr; i++)
		iter->cycles += be[i].flags.cycles;
पूर्ण

#घोषणा CHASHSZ 127
#घोषणा CHASHBITS 7
#घोषणा NO_ENTRY 0xff

#घोषणा PERF_MAX_BRANCH_DEPTH 127

/* Remove loops. */
अटल पूर्णांक हटाओ_loops(काष्ठा branch_entry *l, पूर्णांक nr,
			काष्ठा iterations *iter)
अणु
	पूर्णांक i, j, off;
	अचिन्हित अक्षर chash[CHASHSZ];

	स_रखो(chash, NO_ENTRY, माप(chash));

	BUG_ON(PERF_MAX_BRANCH_DEPTH > 255);

	क्रम (i = 0; i < nr; i++) अणु
		पूर्णांक h = hash_64(l[i].from, CHASHBITS) % CHASHSZ;

		/* no collision handling क्रम now */
		अगर (chash[h] == NO_ENTRY) अणु
			chash[h] = i;
		पूर्ण अन्यथा अगर (l[chash[h]].from == l[i].from) अणु
			bool is_loop = true;
			/* check अगर it is a real loop */
			off = 0;
			क्रम (j = chash[h]; j < i && i + off < nr; j++, off++)
				अगर (l[j].from != l[i + off].from) अणु
					is_loop = false;
					अवरोध;
				पूर्ण
			अगर (is_loop) अणु
				j = nr - (i + off);
				अगर (j > 0) अणु
					save_iterations(iter + i + off,
						l + i, off);

					स_हटाओ(iter + i, iter + i + off,
						j * माप(*iter));

					स_हटाओ(l + i, l + i + off,
						j * माप(*l));
				पूर्ण

				nr -= off;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस nr;
पूर्ण

अटल पूर्णांक lbr_callchain_add_kernel_ip(काष्ठा thपढ़ो *thपढ़ो,
				       काष्ठा callchain_cursor *cursor,
				       काष्ठा perf_sample *sample,
				       काष्ठा symbol **parent,
				       काष्ठा addr_location *root_al,
				       u64 branch_from,
				       bool callee, पूर्णांक end)
अणु
	काष्ठा ip_callchain *chain = sample->callchain;
	u8 cpumode = PERF_RECORD_MISC_USER;
	पूर्णांक err, i;

	अगर (callee) अणु
		क्रम (i = 0; i < end + 1; i++) अणु
			err = add_callchain_ip(thपढ़ो, cursor, parent,
					       root_al, &cpumode, chain->ips[i],
					       false, शून्य, शून्य, branch_from);
			अगर (err)
				वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	क्रम (i = end; i >= 0; i--) अणु
		err = add_callchain_ip(thपढ़ो, cursor, parent,
				       root_al, &cpumode, chain->ips[i],
				       false, शून्य, शून्य, branch_from);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम save_lbr_cursor_node(काष्ठा thपढ़ो *thपढ़ो,
				 काष्ठा callchain_cursor *cursor,
				 पूर्णांक idx)
अणु
	काष्ठा lbr_stitch *lbr_stitch = thपढ़ो->lbr_stitch;

	अगर (!lbr_stitch)
		वापस;

	अगर (cursor->pos == cursor->nr) अणु
		lbr_stitch->prev_lbr_cursor[idx].valid = false;
		वापस;
	पूर्ण

	अगर (!cursor->curr)
		cursor->curr = cursor->first;
	अन्यथा
		cursor->curr = cursor->curr->next;
	स_नकल(&lbr_stitch->prev_lbr_cursor[idx], cursor->curr,
	       माप(काष्ठा callchain_cursor_node));

	lbr_stitch->prev_lbr_cursor[idx].valid = true;
	cursor->pos++;
पूर्ण

अटल पूर्णांक lbr_callchain_add_lbr_ip(काष्ठा thपढ़ो *thपढ़ो,
				    काष्ठा callchain_cursor *cursor,
				    काष्ठा perf_sample *sample,
				    काष्ठा symbol **parent,
				    काष्ठा addr_location *root_al,
				    u64 *branch_from,
				    bool callee)
अणु
	काष्ठा branch_stack *lbr_stack = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	u8 cpumode = PERF_RECORD_MISC_USER;
	पूर्णांक lbr_nr = lbr_stack->nr;
	काष्ठा branch_flags *flags;
	पूर्णांक err, i;
	u64 ip;

	/*
	 * The curr and pos are not used in writing session. They are cleared
	 * in callchain_cursor_commit() when the writing session is बंदd.
	 * Using curr and pos to track the current cursor node.
	 */
	अगर (thपढ़ो->lbr_stitch) अणु
		cursor->curr = शून्य;
		cursor->pos = cursor->nr;
		अगर (cursor->nr) अणु
			cursor->curr = cursor->first;
			क्रम (i = 0; i < (पूर्णांक)(cursor->nr - 1); i++)
				cursor->curr = cursor->curr->next;
		पूर्ण
	पूर्ण

	अगर (callee) अणु
		/* Add LBR ip from first entries.to */
		ip = entries[0].to;
		flags = &entries[0].flags;
		*branch_from = entries[0].from;
		err = add_callchain_ip(thपढ़ो, cursor, parent,
				       root_al, &cpumode, ip,
				       true, flags, शून्य,
				       *branch_from);
		अगर (err)
			वापस err;

		/*
		 * The number of cursor node increases.
		 * Move the current cursor node.
		 * But करोes not need to save current cursor node क्रम entry 0.
		 * It's impossible to stitch the whole LBRs of previous sample.
		 */
		अगर (thपढ़ो->lbr_stitch && (cursor->pos != cursor->nr)) अणु
			अगर (!cursor->curr)
				cursor->curr = cursor->first;
			अन्यथा
				cursor->curr = cursor->curr->next;
			cursor->pos++;
		पूर्ण

		/* Add LBR ip from entries.from one by one. */
		क्रम (i = 0; i < lbr_nr; i++) अणु
			ip = entries[i].from;
			flags = &entries[i].flags;
			err = add_callchain_ip(thपढ़ो, cursor, parent,
					       root_al, &cpumode, ip,
					       true, flags, शून्य,
					       *branch_from);
			अगर (err)
				वापस err;
			save_lbr_cursor_node(thपढ़ो, cursor, i);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Add LBR ip from entries.from one by one. */
	क्रम (i = lbr_nr - 1; i >= 0; i--) अणु
		ip = entries[i].from;
		flags = &entries[i].flags;
		err = add_callchain_ip(thपढ़ो, cursor, parent,
				       root_al, &cpumode, ip,
				       true, flags, शून्य,
				       *branch_from);
		अगर (err)
			वापस err;
		save_lbr_cursor_node(thपढ़ो, cursor, i);
	पूर्ण

	/* Add LBR ip from first entries.to */
	ip = entries[0].to;
	flags = &entries[0].flags;
	*branch_from = entries[0].from;
	err = add_callchain_ip(thपढ़ो, cursor, parent,
			       root_al, &cpumode, ip,
			       true, flags, शून्य,
			       *branch_from);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक lbr_callchain_add_stitched_lbr_ip(काष्ठा thपढ़ो *thपढ़ो,
					     काष्ठा callchain_cursor *cursor)
अणु
	काष्ठा lbr_stitch *lbr_stitch = thपढ़ो->lbr_stitch;
	काष्ठा callchain_cursor_node *cnode;
	काष्ठा stitch_list *stitch_node;
	पूर्णांक err;

	list_क्रम_each_entry(stitch_node, &lbr_stitch->lists, node) अणु
		cnode = &stitch_node->cursor;

		err = callchain_cursor_append(cursor, cnode->ip,
					      &cnode->ms,
					      cnode->branch,
					      &cnode->branch_flags,
					      cnode->nr_loop_iter,
					      cnode->iter_cycles,
					      cnode->branch_from,
					      cnode->srcline);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा stitch_list *get_stitch_node(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा lbr_stitch *lbr_stitch = thपढ़ो->lbr_stitch;
	काष्ठा stitch_list *stitch_node;

	अगर (!list_empty(&lbr_stitch->मुक्त_lists)) अणु
		stitch_node = list_first_entry(&lbr_stitch->मुक्त_lists,
					       काष्ठा stitch_list, node);
		list_del(&stitch_node->node);

		वापस stitch_node;
	पूर्ण

	वापस दो_स्मृति(माप(काष्ठा stitch_list));
पूर्ण

अटल bool has_stitched_lbr(काष्ठा thपढ़ो *thपढ़ो,
			     काष्ठा perf_sample *cur,
			     काष्ठा perf_sample *prev,
			     अचिन्हित पूर्णांक max_lbr,
			     bool callee)
अणु
	काष्ठा branch_stack *cur_stack = cur->branch_stack;
	काष्ठा branch_entry *cur_entries = perf_sample__branch_entries(cur);
	काष्ठा branch_stack *prev_stack = prev->branch_stack;
	काष्ठा branch_entry *prev_entries = perf_sample__branch_entries(prev);
	काष्ठा lbr_stitch *lbr_stitch = thपढ़ो->lbr_stitch;
	पूर्णांक i, j, nr_identical_branches = 0;
	काष्ठा stitch_list *stitch_node;
	u64 cur_base, distance;

	अगर (!cur_stack || !prev_stack)
		वापस false;

	/* Find the physical index of the base-of-stack क्रम current sample. */
	cur_base = max_lbr - cur_stack->nr + cur_stack->hw_idx + 1;

	distance = (prev_stack->hw_idx > cur_base) ? (prev_stack->hw_idx - cur_base) :
						     (max_lbr + prev_stack->hw_idx - cur_base);
	/* Previous sample has लघुer stack. Nothing can be stitched. */
	अगर (distance + 1 > prev_stack->nr)
		वापस false;

	/*
	 * Check अगर there are identical LBRs between two samples.
	 * Identical LBRs must have same from, to and flags values. Also,
	 * they have to be saved in the same LBR रेजिस्टरs (same physical
	 * index).
	 *
	 * Starts from the base-of-stack of current sample.
	 */
	क्रम (i = distance, j = cur_stack->nr - 1; (i >= 0) && (j >= 0); i--, j--) अणु
		अगर ((prev_entries[i].from != cur_entries[j].from) ||
		    (prev_entries[i].to != cur_entries[j].to) ||
		    (prev_entries[i].flags.value != cur_entries[j].flags.value))
			अवरोध;
		nr_identical_branches++;
	पूर्ण

	अगर (!nr_identical_branches)
		वापस false;

	/*
	 * Save the LBRs between the base-of-stack of previous sample
	 * and the base-of-stack of current sample पूर्णांकo lbr_stitch->lists.
	 * These LBRs will be stitched later.
	 */
	क्रम (i = prev_stack->nr - 1; i > (पूर्णांक)distance; i--) अणु

		अगर (!lbr_stitch->prev_lbr_cursor[i].valid)
			जारी;

		stitch_node = get_stitch_node(thपढ़ो);
		अगर (!stitch_node)
			वापस false;

		स_नकल(&stitch_node->cursor, &lbr_stitch->prev_lbr_cursor[i],
		       माप(काष्ठा callchain_cursor_node));

		अगर (callee)
			list_add(&stitch_node->node, &lbr_stitch->lists);
		अन्यथा
			list_add_tail(&stitch_node->node, &lbr_stitch->lists);
	पूर्ण

	वापस true;
पूर्ण

अटल bool alloc_lbr_stitch(काष्ठा thपढ़ो *thपढ़ो, अचिन्हित पूर्णांक max_lbr)
अणु
	अगर (thपढ़ो->lbr_stitch)
		वापस true;

	thपढ़ो->lbr_stitch = zalloc(माप(*thपढ़ो->lbr_stitch));
	अगर (!thपढ़ो->lbr_stitch)
		जाओ err;

	thपढ़ो->lbr_stitch->prev_lbr_cursor = सुस्मृति(max_lbr + 1, माप(काष्ठा callchain_cursor_node));
	अगर (!thपढ़ो->lbr_stitch->prev_lbr_cursor)
		जाओ मुक्त_lbr_stitch;

	INIT_LIST_HEAD(&thपढ़ो->lbr_stitch->lists);
	INIT_LIST_HEAD(&thपढ़ो->lbr_stitch->मुक्त_lists);

	वापस true;

मुक्त_lbr_stitch:
	zमुक्त(&thपढ़ो->lbr_stitch);
err:
	pr_warning("Failed to allocate space for stitched LBRs. Disable LBR stitch\n");
	thपढ़ो->lbr_stitch_enable = false;
	वापस false;
पूर्ण

/*
 * Resolve LBR callstack chain sample
 * Return:
 * 1 on success get LBR callchain inक्रमmation
 * 0 no available LBR callchain inक्रमmation, should try fp
 * negative error code on other errors.
 */
अटल पूर्णांक resolve_lbr_callchain_sample(काष्ठा thपढ़ो *thपढ़ो,
					काष्ठा callchain_cursor *cursor,
					काष्ठा perf_sample *sample,
					काष्ठा symbol **parent,
					काष्ठा addr_location *root_al,
					पूर्णांक max_stack,
					अचिन्हित पूर्णांक max_lbr)
अणु
	bool callee = (callchain_param.order == ORDER_CALLEE);
	काष्ठा ip_callchain *chain = sample->callchain;
	पूर्णांक chain_nr = min(max_stack, (पूर्णांक)chain->nr), i;
	काष्ठा lbr_stitch *lbr_stitch;
	bool stitched_lbr = false;
	u64 branch_from = 0;
	पूर्णांक err;

	क्रम (i = 0; i < chain_nr; i++) अणु
		अगर (chain->ips[i] == PERF_CONTEXT_USER)
			अवरोध;
	पूर्ण

	/* LBR only affects the user callchain */
	अगर (i == chain_nr)
		वापस 0;

	अगर (thपढ़ो->lbr_stitch_enable && !sample->no_hw_idx &&
	    (max_lbr > 0) && alloc_lbr_stitch(thपढ़ो, max_lbr)) अणु
		lbr_stitch = thपढ़ो->lbr_stitch;

		stitched_lbr = has_stitched_lbr(thपढ़ो, sample,
						&lbr_stitch->prev_sample,
						max_lbr, callee);

		अगर (!stitched_lbr && !list_empty(&lbr_stitch->lists)) अणु
			list_replace_init(&lbr_stitch->lists,
					  &lbr_stitch->मुक्त_lists);
		पूर्ण
		स_नकल(&lbr_stitch->prev_sample, sample, माप(*sample));
	पूर्ण

	अगर (callee) अणु
		/* Add kernel ip */
		err = lbr_callchain_add_kernel_ip(thपढ़ो, cursor, sample,
						  parent, root_al, branch_from,
						  true, i);
		अगर (err)
			जाओ error;

		err = lbr_callchain_add_lbr_ip(thपढ़ो, cursor, sample, parent,
					       root_al, &branch_from, true);
		अगर (err)
			जाओ error;

		अगर (stitched_lbr) अणु
			err = lbr_callchain_add_stitched_lbr_ip(thपढ़ो, cursor);
			अगर (err)
				जाओ error;
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (stitched_lbr) अणु
			err = lbr_callchain_add_stitched_lbr_ip(thपढ़ो, cursor);
			अगर (err)
				जाओ error;
		पूर्ण
		err = lbr_callchain_add_lbr_ip(thपढ़ो, cursor, sample, parent,
					       root_al, &branch_from, false);
		अगर (err)
			जाओ error;

		/* Add kernel ip */
		err = lbr_callchain_add_kernel_ip(thपढ़ो, cursor, sample,
						  parent, root_al, branch_from,
						  false, i);
		अगर (err)
			जाओ error;
	पूर्ण
	वापस 1;

error:
	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक find_prev_cpumode(काष्ठा ip_callchain *chain, काष्ठा thपढ़ो *thपढ़ो,
			     काष्ठा callchain_cursor *cursor,
			     काष्ठा symbol **parent,
			     काष्ठा addr_location *root_al,
			     u8 *cpumode, पूर्णांक ent)
अणु
	पूर्णांक err = 0;

	जबतक (--ent >= 0) अणु
		u64 ip = chain->ips[ent];

		अगर (ip >= PERF_CONTEXT_MAX) अणु
			err = add_callchain_ip(thपढ़ो, cursor, parent,
					       root_al, cpumode, ip,
					       false, शून्य, शून्य, 0);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक thपढ़ो__resolve_callchain_sample(काष्ठा thपढ़ो *thपढ़ो,
					    काष्ठा callchain_cursor *cursor,
					    काष्ठा evsel *evsel,
					    काष्ठा perf_sample *sample,
					    काष्ठा symbol **parent,
					    काष्ठा addr_location *root_al,
					    पूर्णांक max_stack)
अणु
	काष्ठा branch_stack *branch = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	काष्ठा ip_callchain *chain = sample->callchain;
	पूर्णांक chain_nr = 0;
	u8 cpumode = PERF_RECORD_MISC_USER;
	पूर्णांक i, j, err, nr_entries;
	पूर्णांक skip_idx = -1;
	पूर्णांक first_call = 0;

	अगर (chain)
		chain_nr = chain->nr;

	अगर (evsel__has_branch_callstack(evsel)) अणु
		काष्ठा perf_env *env = evsel__env(evsel);

		err = resolve_lbr_callchain_sample(thपढ़ो, cursor, sample, parent,
						   root_al, max_stack,
						   !env ? 0 : env->max_branches);
		अगर (err)
			वापस (err < 0) ? err : 0;
	पूर्ण

	/*
	 * Based on DWARF debug inक्रमmation, some architectures skip
	 * a callchain entry saved by the kernel.
	 */
	skip_idx = arch_skip_callchain_idx(thपढ़ो, chain);

	/*
	 * Add branches to call stack क्रम easier browsing. This gives
	 * more context क्रम a sample than just the callers.
	 *
	 * This uses inभागidual histograms of paths compared to the
	 * aggregated histograms the normal LBR mode uses.
	 *
	 * Limitations क्रम now:
	 * - No extra filters
	 * - No annotations (should annotate somehow)
	 */

	अगर (branch && callchain_param.branch_callstack) अणु
		पूर्णांक nr = min(max_stack, (पूर्णांक)branch->nr);
		काष्ठा branch_entry be[nr];
		काष्ठा iterations iter[nr];

		अगर (branch->nr > PERF_MAX_BRANCH_DEPTH) अणु
			pr_warning("corrupted branch chain. skipping...\n");
			जाओ check_calls;
		पूर्ण

		क्रम (i = 0; i < nr; i++) अणु
			अगर (callchain_param.order == ORDER_CALLEE) अणु
				be[i] = entries[i];

				अगर (chain == शून्य)
					जारी;

				/*
				 * Check क्रम overlap पूर्णांकo the callchain.
				 * The वापस address is one off compared to
				 * the branch entry. To adjust क्रम this
				 * assume the calling inकाष्ठाion is not दीर्घer
				 * than 8 bytes.
				 */
				अगर (i == skip_idx ||
				    chain->ips[first_call] >= PERF_CONTEXT_MAX)
					first_call++;
				अन्यथा अगर (be[i].from < chain->ips[first_call] &&
				    be[i].from >= chain->ips[first_call] - 8)
					first_call++;
			पूर्ण अन्यथा
				be[i] = entries[branch->nr - i - 1];
		पूर्ण

		स_रखो(iter, 0, माप(काष्ठा iterations) * nr);
		nr = हटाओ_loops(be, nr, iter);

		क्रम (i = 0; i < nr; i++) अणु
			err = add_callchain_ip(thपढ़ो, cursor, parent,
					       root_al,
					       शून्य, be[i].to,
					       true, &be[i].flags,
					       शून्य, be[i].from);

			अगर (!err)
				err = add_callchain_ip(thपढ़ो, cursor, parent, root_al,
						       शून्य, be[i].from,
						       true, &be[i].flags,
						       &iter[i], 0);
			अगर (err == -EINVAL)
				अवरोध;
			अगर (err)
				वापस err;
		पूर्ण

		अगर (chain_nr == 0)
			वापस 0;

		chain_nr -= nr;
	पूर्ण

check_calls:
	अगर (chain && callchain_param.order != ORDER_CALLEE) अणु
		err = find_prev_cpumode(chain, thपढ़ो, cursor, parent, root_al,
					&cpumode, chain->nr - first_call);
		अगर (err)
			वापस (err < 0) ? err : 0;
	पूर्ण
	क्रम (i = first_call, nr_entries = 0;
	     i < chain_nr && nr_entries < max_stack; i++) अणु
		u64 ip;

		अगर (callchain_param.order == ORDER_CALLEE)
			j = i;
		अन्यथा
			j = chain->nr - i - 1;

#अगर_घोषित HAVE_SKIP_CALLCHAIN_IDX
		अगर (j == skip_idx)
			जारी;
#पूर्ण_अगर
		ip = chain->ips[j];
		अगर (ip < PERF_CONTEXT_MAX)
                       ++nr_entries;
		अन्यथा अगर (callchain_param.order != ORDER_CALLEE) अणु
			err = find_prev_cpumode(chain, thपढ़ो, cursor, parent,
						root_al, &cpumode, j);
			अगर (err)
				वापस (err < 0) ? err : 0;
			जारी;
		पूर्ण

		err = add_callchain_ip(thपढ़ो, cursor, parent,
				       root_al, &cpumode, ip,
				       false, शून्य, शून्य, 0);

		अगर (err)
			वापस (err < 0) ? err : 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक append_अंतरभूतs(काष्ठा callchain_cursor *cursor, काष्ठा map_symbol *ms, u64 ip)
अणु
	काष्ठा symbol *sym = ms->sym;
	काष्ठा map *map = ms->map;
	काष्ठा अंतरभूत_node *अंतरभूत_node;
	काष्ठा अंतरभूत_list *ilist;
	u64 addr;
	पूर्णांक ret = 1;

	अगर (!symbol_conf.अंतरभूत_name || !map || !sym)
		वापस ret;

	addr = map__map_ip(map, ip);
	addr = map__rip_2objdump(map, addr);

	अंतरभूत_node = अंतरभूतs__tree_find(&map->dso->अंतरभूतd_nodes, addr);
	अगर (!अंतरभूत_node) अणु
		अंतरभूत_node = dso__parse_addr_अंतरभूतs(map->dso, addr, sym);
		अगर (!अंतरभूत_node)
			वापस ret;
		अंतरभूतs__tree_insert(&map->dso->अंतरभूतd_nodes, अंतरभूत_node);
	पूर्ण

	list_क्रम_each_entry(ilist, &अंतरभूत_node->val, list) अणु
		काष्ठा map_symbol ilist_ms = अणु
			.maps = ms->maps,
			.map = map,
			.sym = ilist->symbol,
		पूर्ण;
		ret = callchain_cursor_append(cursor, ip, &ilist_ms, false,
					      शून्य, 0, 0, 0, ilist->srcline);

		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक unwind_entry(काष्ठा unwind_entry *entry, व्योम *arg)
अणु
	काष्ठा callchain_cursor *cursor = arg;
	स्थिर अक्षर *srcline = शून्य;
	u64 addr = entry->ip;

	अगर (symbol_conf.hide_unresolved && entry->ms.sym == शून्य)
		वापस 0;

	अगर (append_अंतरभूतs(cursor, &entry->ms, entry->ip) == 0)
		वापस 0;

	/*
	 * Convert entry->ip from a भव address to an offset in
	 * its corresponding binary.
	 */
	अगर (entry->ms.map)
		addr = map__map_ip(entry->ms.map, entry->ip);

	srcline = callchain_srcline(&entry->ms, addr);
	वापस callchain_cursor_append(cursor, entry->ip, &entry->ms,
				       false, शून्य, 0, 0, 0, srcline);
पूर्ण

अटल पूर्णांक thपढ़ो__resolve_callchain_unwind(काष्ठा thपढ़ो *thपढ़ो,
					    काष्ठा callchain_cursor *cursor,
					    काष्ठा evsel *evsel,
					    काष्ठा perf_sample *sample,
					    पूर्णांक max_stack)
अणु
	/* Can we करो dwarf post unwind? */
	अगर (!((evsel->core.attr.sample_type & PERF_SAMPLE_REGS_USER) &&
	      (evsel->core.attr.sample_type & PERF_SAMPLE_STACK_USER)))
		वापस 0;

	/* Bail out अगर nothing was captured. */
	अगर ((!sample->user_regs.regs) ||
	    (!sample->user_stack.size))
		वापस 0;

	वापस unwind__get_entries(unwind_entry, cursor,
				   thपढ़ो, sample, max_stack);
पूर्ण

पूर्णांक thपढ़ो__resolve_callchain(काष्ठा thपढ़ो *thपढ़ो,
			      काष्ठा callchain_cursor *cursor,
			      काष्ठा evsel *evsel,
			      काष्ठा perf_sample *sample,
			      काष्ठा symbol **parent,
			      काष्ठा addr_location *root_al,
			      पूर्णांक max_stack)
अणु
	पूर्णांक ret = 0;

	callchain_cursor_reset(cursor);

	अगर (callchain_param.order == ORDER_CALLEE) अणु
		ret = thपढ़ो__resolve_callchain_sample(thपढ़ो, cursor,
						       evsel, sample,
						       parent, root_al,
						       max_stack);
		अगर (ret)
			वापस ret;
		ret = thपढ़ो__resolve_callchain_unwind(thपढ़ो, cursor,
						       evsel, sample,
						       max_stack);
	पूर्ण अन्यथा अणु
		ret = thपढ़ो__resolve_callchain_unwind(thपढ़ो, cursor,
						       evsel, sample,
						       max_stack);
		अगर (ret)
			वापस ret;
		ret = thपढ़ो__resolve_callchain_sample(thपढ़ो, cursor,
						       evsel, sample,
						       parent, root_al,
						       max_stack);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक machine__क्रम_each_thपढ़ो(काष्ठा machine *machine,
			     पूर्णांक (*fn)(काष्ठा thपढ़ो *thपढ़ो, व्योम *p),
			     व्योम *priv)
अणु
	काष्ठा thपढ़ोs *thपढ़ोs;
	काष्ठा rb_node *nd;
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक rc = 0;
	पूर्णांक i;

	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++) अणु
		thपढ़ोs = &machine->thपढ़ोs[i];
		क्रम (nd = rb_first_cached(&thपढ़ोs->entries); nd;
		     nd = rb_next(nd)) अणु
			thपढ़ो = rb_entry(nd, काष्ठा thपढ़ो, rb_node);
			rc = fn(thपढ़ो, priv);
			अगर (rc != 0)
				वापस rc;
		पूर्ण

		list_क्रम_each_entry(thपढ़ो, &thपढ़ोs->dead, node) अणु
			rc = fn(thपढ़ो, priv);
			अगर (rc != 0)
				वापस rc;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक machines__क्रम_each_thपढ़ो(काष्ठा machines *machines,
			      पूर्णांक (*fn)(काष्ठा thपढ़ो *thपढ़ो, व्योम *p),
			      व्योम *priv)
अणु
	काष्ठा rb_node *nd;
	पूर्णांक rc = 0;

	rc = machine__क्रम_each_thपढ़ो(&machines->host, fn, priv);
	अगर (rc != 0)
		वापस rc;

	क्रम (nd = rb_first_cached(&machines->guests); nd; nd = rb_next(nd)) अणु
		काष्ठा machine *machine = rb_entry(nd, काष्ठा machine, rb_node);

		rc = machine__क्रम_each_thपढ़ो(machine, fn, priv);
		अगर (rc != 0)
			वापस rc;
	पूर्ण
	वापस rc;
पूर्ण

pid_t machine__get_current_tid(काष्ठा machine *machine, पूर्णांक cpu)
अणु
	पूर्णांक nr_cpus = min(machine->env->nr_cpus_avail, MAX_NR_CPUS);

	अगर (cpu < 0 || cpu >= nr_cpus || !machine->current_tid)
		वापस -1;

	वापस machine->current_tid[cpu];
पूर्ण

पूर्णांक machine__set_current_tid(काष्ठा machine *machine, पूर्णांक cpu, pid_t pid,
			     pid_t tid)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक nr_cpus = min(machine->env->nr_cpus_avail, MAX_NR_CPUS);

	अगर (cpu < 0)
		वापस -EINVAL;

	अगर (!machine->current_tid) अणु
		पूर्णांक i;

		machine->current_tid = सुस्मृति(nr_cpus, माप(pid_t));
		अगर (!machine->current_tid)
			वापस -ENOMEM;
		क्रम (i = 0; i < nr_cpus; i++)
			machine->current_tid[i] = -1;
	पूर्ण

	अगर (cpu >= nr_cpus) अणु
		pr_err("Requested CPU %d too large. ", cpu);
		pr_err("Consider raising MAX_NR_CPUS\n");
		वापस -EINVAL;
	पूर्ण

	machine->current_tid[cpu] = tid;

	thपढ़ो = machine__findnew_thपढ़ो(machine, pid, tid);
	अगर (!thपढ़ो)
		वापस -ENOMEM;

	thपढ़ो->cpu = cpu;
	thपढ़ो__put(thपढ़ो);

	वापस 0;
पूर्ण

/*
 * Compares the raw arch string. N.B. see instead perf_env__arch() अगर a
 * normalized arch is needed.
 */
bool machine__is(काष्ठा machine *machine, स्थिर अक्षर *arch)
अणु
	वापस machine && !म_भेद(perf_env__raw_arch(machine->env), arch);
पूर्ण

पूर्णांक machine__nr_cpus_avail(काष्ठा machine *machine)
अणु
	वापस machine ? perf_env__nr_cpus_avail(machine->env) : 0;
पूर्ण

पूर्णांक machine__get_kernel_start(काष्ठा machine *machine)
अणु
	काष्ठा map *map = machine__kernel_map(machine);
	पूर्णांक err = 0;

	/*
	 * The only addresses above 2^63 are kernel addresses of a 64-bit
	 * kernel.  Note that addresses are अचिन्हित so that on a 32-bit प्रणाली
	 * all addresses including kernel addresses are less than 2^32.  In
	 * that हाल (32-bit प्रणाली), अगर the kernel mapping is unknown, all
	 * addresses will be assumed to be in user space - see
	 * machine__kernel_ip().
	 */
	machine->kernel_start = 1ULL << 63;
	अगर (map) अणु
		err = map__load(map);
		/*
		 * On x86_64, PTI entry trampolines are less than the
		 * start of kernel text, but still above 2^63. So leave
		 * kernel_start = 1ULL << 63 क्रम x86_64.
		 */
		अगर (!err && !machine__is(machine, "x86_64"))
			machine->kernel_start = map->start;
	पूर्ण
	वापस err;
पूर्ण

u8 machine__addr_cpumode(काष्ठा machine *machine, u8 cpumode, u64 addr)
अणु
	u8 addr_cpumode = cpumode;
	bool kernel_ip;

	अगर (!machine->single_address_space)
		जाओ out;

	kernel_ip = machine__kernel_ip(machine, addr);
	चयन (cpumode) अणु
	हाल PERF_RECORD_MISC_KERNEL:
	हाल PERF_RECORD_MISC_USER:
		addr_cpumode = kernel_ip ? PERF_RECORD_MISC_KERNEL :
					   PERF_RECORD_MISC_USER;
		अवरोध;
	हाल PERF_RECORD_MISC_GUEST_KERNEL:
	हाल PERF_RECORD_MISC_GUEST_USER:
		addr_cpumode = kernel_ip ? PERF_RECORD_MISC_GUEST_KERNEL :
					   PERF_RECORD_MISC_GUEST_USER;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out:
	वापस addr_cpumode;
पूर्ण

काष्ठा dso *machine__findnew_dso_id(काष्ठा machine *machine, स्थिर अक्षर *filename, काष्ठा dso_id *id)
अणु
	वापस dsos__findnew_id(&machine->dsos, filename, id);
पूर्ण

काष्ठा dso *machine__findnew_dso(काष्ठा machine *machine, स्थिर अक्षर *filename)
अणु
	वापस machine__findnew_dso_id(machine, filename, शून्य);
पूर्ण

अक्षर *machine__resolve_kernel_addr(व्योम *vmachine, अचिन्हित दीर्घ दीर्घ *addrp, अक्षर **modp)
अणु
	काष्ठा machine *machine = vmachine;
	काष्ठा map *map;
	काष्ठा symbol *sym = machine__find_kernel_symbol(machine, *addrp, &map);

	अगर (sym == शून्य)
		वापस शून्य;

	*modp = __map__is_kmodule(map) ? (अक्षर *)map->dso->लघु_name : शून्य;
	*addrp = map->unmap_ip(map, sym->start);
	वापस sym->name;
पूर्ण

पूर्णांक machine__क्रम_each_dso(काष्ठा machine *machine, machine__dso_t fn, व्योम *priv)
अणु
	काष्ठा dso *pos;
	पूर्णांक err = 0;

	list_क्रम_each_entry(pos, &machine->dsos.head, node) अणु
		अगर (fn(pos, machine, priv))
			err = -1;
	पूर्ण
	वापस err;
पूर्ण
