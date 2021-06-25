<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only 

#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश "util/event.h"
#समावेश "util/evlist.h"
#समावेश "util/machine.h"
#समावेश "util/map.h"
#समावेश "util/map_symbol.h"
#समावेश "util/branch.h"
#समावेश "util/memswap.h"
#समावेश "util/namespaces.h"
#समावेश "util/session.h"
#समावेश "util/stat.h"
#समावेश "util/symbol.h"
#समावेश "util/synthetic-events.h"
#समावेश "util/target.h"
#समावेश "util/time-utils.h"
#समावेश "util/cgroup.h"
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/bug.h>
#समावेश <perf/evsel.h>
#समावेश <perf/cpumap.h>
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश <पूर्णांकernal/thपढ़ोmap.h>
#समावेश <perf/thपढ़ोmap.h>
#समावेश <symbol/kallsyms.h>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <uapi/linux/mman.h> /* To get things like MAP_HUGETLB even on older libc headers */
#समावेश <api/fs/fs.h>
#समावेश <api/पन.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

#घोषणा DEFAULT_PROC_MAP_PARSE_TIMEOUT 500

अचिन्हित पूर्णांक proc_map_समयout = DEFAULT_PROC_MAP_PARSE_TIMEOUT;

पूर्णांक perf_tool__process_synth_event(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा machine *machine,
				   perf_event__handler_t process)
अणु
	काष्ठा perf_sample synth_sample = अणु
		.pid	   = -1,
		.tid	   = -1,
		.समय	   = -1,
		.stream_id = -1,
		.cpu	   = -1,
		.period	   = 1,
		.cpumode   = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK,
	पूर्ण;

	वापस process(tool, event, &synth_sample, machine);
पूर्ण;

/*
 * Assumes that the first 4095 bytes of /proc/pid/stat contains
 * the comm, tgid and ppid.
 */
अटल पूर्णांक perf_event__get_comm_ids(pid_t pid, pid_t tid, अक्षर *comm, माप_प्रकार len,
				    pid_t *tgid, pid_t *ppid, bool *kernel)
अणु
	अक्षर bf[4096];
	पूर्णांक fd;
	माप_प्रकार size = 0;
	sमाप_प्रकार n;
	अक्षर *name, *tgids, *ppids, *vmpeak, *thपढ़ोs;

	*tgid = -1;
	*ppid = -1;

	अगर (pid)
		snम_लिखो(bf, माप(bf), "/proc/%d/task/%d/status", pid, tid);
	अन्यथा
		snम_लिखो(bf, माप(bf), "/proc/%d/status", tid);

	fd = खोलो(bf, O_RDONLY);
	अगर (fd < 0) अणु
		pr_debug("couldn't open %s\n", bf);
		वापस -1;
	पूर्ण

	n = पढ़ो(fd, bf, माप(bf) - 1);
	बंद(fd);
	अगर (n <= 0) अणु
		pr_warning("Couldn't get COMM, tigd and ppid for pid %d\n",
			   tid);
		वापस -1;
	पूर्ण
	bf[n] = '\0';

	name = म_माला(bf, "Name:");
	tgids = म_माला(name ?: bf, "Tgid:");
	ppids = म_माला(tgids ?: bf, "PPid:");
	vmpeak = म_माला(ppids ?: bf, "VmPeak:");

	अगर (vmpeak)
		thपढ़ोs = शून्य;
	अन्यथा
		thपढ़ोs = म_माला(ppids ?: bf, "Threads:");

	अगर (name) अणु
		अक्षर *nl;

		name = skip_spaces(name + 5);  /* म_माप("Name:") */
		nl = म_अक्षर(name, '\n');
		अगर (nl)
			*nl = '\0';

		size = म_माप(name);
		अगर (size >= len)
			size = len - 1;
		स_नकल(comm, name, size);
		comm[size] = '\0';
	पूर्ण अन्यथा अणु
		pr_debug("Name: string not found for pid %d\n", tid);
	पूर्ण

	अगर (tgids) अणु
		tgids += 5;  /* म_माप("Tgid:") */
		*tgid = म_से_प(tgids);
	पूर्ण अन्यथा अणु
		pr_debug("Tgid: string not found for pid %d\n", tid);
	पूर्ण

	अगर (ppids) अणु
		ppids += 5;  /* म_माप("PPid:") */
		*ppid = म_से_प(ppids);
	पूर्ण अन्यथा अणु
		pr_debug("PPid: string not found for pid %d\n", tid);
	पूर्ण

	अगर (!vmpeak && thपढ़ोs)
		*kernel = true;
	अन्यथा
		*kernel = false;

	वापस 0;
पूर्ण

अटल पूर्णांक perf_event__prepare_comm(जोड़ perf_event *event, pid_t pid, pid_t tid,
				    काष्ठा machine *machine,
				    pid_t *tgid, pid_t *ppid, bool *kernel)
अणु
	माप_प्रकार size;

	*ppid = -1;

	स_रखो(&event->comm, 0, माप(event->comm));

	अगर (machine__is_host(machine)) अणु
		अगर (perf_event__get_comm_ids(pid, tid, event->comm.comm,
					     माप(event->comm.comm),
					     tgid, ppid, kernel) != 0) अणु
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		*tgid = machine->pid;
	पूर्ण

	अगर (*tgid < 0)
		वापस -1;

	event->comm.pid = *tgid;
	event->comm.header.type = PERF_RECORD_COMM;

	size = म_माप(event->comm.comm) + 1;
	size = PERF_ALIGN(size, माप(u64));
	स_रखो(event->comm.comm + size, 0, machine->id_hdr_size);
	event->comm.header.size = (माप(event->comm) -
				(माप(event->comm.comm) - size) +
				machine->id_hdr_size);
	event->comm.tid = tid;

	वापस 0;
पूर्ण

pid_t perf_event__synthesize_comm(काष्ठा perf_tool *tool,
					 जोड़ perf_event *event, pid_t pid,
					 perf_event__handler_t process,
					 काष्ठा machine *machine)
अणु
	pid_t tgid, ppid;
	bool kernel_thपढ़ो;

	अगर (perf_event__prepare_comm(event, 0, pid, machine, &tgid, &ppid,
				     &kernel_thपढ़ो) != 0)
		वापस -1;

	अगर (perf_tool__process_synth_event(tool, event, machine, process) != 0)
		वापस -1;

	वापस tgid;
पूर्ण

अटल व्योम perf_event__get_ns_link_info(pid_t pid, स्थिर अक्षर *ns,
					 काष्ठा perf_ns_link_info *ns_link_info)
अणु
	काष्ठा stat64 st;
	अक्षर proc_ns[128];

	प्र_लिखो(proc_ns, "/proc/%u/ns/%s", pid, ns);
	अगर (stat64(proc_ns, &st) == 0) अणु
		ns_link_info->dev = st.st_dev;
		ns_link_info->ino = st.st_ino;
	पूर्ण
पूर्ण

पूर्णांक perf_event__synthesize_namespaces(काष्ठा perf_tool *tool,
				      जोड़ perf_event *event,
				      pid_t pid, pid_t tgid,
				      perf_event__handler_t process,
				      काष्ठा machine *machine)
अणु
	u32 idx;
	काष्ठा perf_ns_link_info *ns_link_info;

	अगर (!tool || !tool->namespace_events)
		वापस 0;

	स_रखो(&event->namespaces, 0, (माप(event->namespaces) +
	       (NR_NAMESPACES * माप(काष्ठा perf_ns_link_info)) +
	       machine->id_hdr_size));

	event->namespaces.pid = tgid;
	event->namespaces.tid = pid;

	event->namespaces.nr_namespaces = NR_NAMESPACES;

	ns_link_info = event->namespaces.link_info;

	क्रम (idx = 0; idx < event->namespaces.nr_namespaces; idx++)
		perf_event__get_ns_link_info(pid, perf_ns__name(idx),
					     &ns_link_info[idx]);

	event->namespaces.header.type = PERF_RECORD_NAMESPACES;

	event->namespaces.header.size = (माप(event->namespaces) +
			(NR_NAMESPACES * माप(काष्ठा perf_ns_link_info)) +
			machine->id_hdr_size);

	अगर (perf_tool__process_synth_event(tool, event, machine, process) != 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक perf_event__synthesize_विभाजन(काष्ठा perf_tool *tool,
				       जोड़ perf_event *event,
				       pid_t pid, pid_t tgid, pid_t ppid,
				       perf_event__handler_t process,
				       काष्ठा machine *machine)
अणु
	स_रखो(&event->विभाजन, 0, माप(event->विभाजन) + machine->id_hdr_size);

	/*
	 * क्रम मुख्य thपढ़ो set parent to ppid from status file. For other
	 * thपढ़ोs set parent pid to मुख्य thपढ़ो. ie., assume मुख्य thपढ़ो
	 * spawns all thपढ़ोs in a process
	*/
	अगर (tgid == pid) अणु
		event->विभाजन.ppid = ppid;
		event->विभाजन.ptid = ppid;
	पूर्ण अन्यथा अणु
		event->विभाजन.ppid = tgid;
		event->विभाजन.ptid = tgid;
	पूर्ण
	event->विभाजन.pid  = tgid;
	event->विभाजन.tid  = pid;
	event->विभाजन.header.type = PERF_RECORD_FORK;
	event->विभाजन.header.misc = PERF_RECORD_MISC_FORK_EXEC;

	event->विभाजन.header.size = (माप(event->विभाजन) + machine->id_hdr_size);

	अगर (perf_tool__process_synth_event(tool, event, machine, process) != 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल bool पढ़ो_proc_maps_line(काष्ठा io *io, __u64 *start, __u64 *end,
				u32 *prot, u32 *flags, __u64 *offset,
				u32 *maj, u32 *min,
				__u64 *inode,
				sमाप_प्रकार pathname_size, अक्षर *pathname)
अणु
	__u64 temp;
	पूर्णांक ch;
	अक्षर *start_pathname = pathname;

	अगर (io__get_hex(io, start) != '-')
		वापस false;
	अगर (io__get_hex(io, end) != ' ')
		वापस false;

	/* map protection and flags bits */
	*prot = 0;
	ch = io__get_अक्षर(io);
	अगर (ch == 'r')
		*prot |= PROT_READ;
	अन्यथा अगर (ch != '-')
		वापस false;
	ch = io__get_अक्षर(io);
	अगर (ch == 'w')
		*prot |= PROT_WRITE;
	अन्यथा अगर (ch != '-')
		वापस false;
	ch = io__get_अक्षर(io);
	अगर (ch == 'x')
		*prot |= PROT_EXEC;
	अन्यथा अगर (ch != '-')
		वापस false;
	ch = io__get_अक्षर(io);
	अगर (ch == 's')
		*flags = MAP_SHARED;
	अन्यथा अगर (ch == 'p')
		*flags = MAP_PRIVATE;
	अन्यथा
		वापस false;
	अगर (io__get_अक्षर(io) != ' ')
		वापस false;

	अगर (io__get_hex(io, offset) != ' ')
		वापस false;

	अगर (io__get_hex(io, &temp) != ':')
		वापस false;
	*maj = temp;
	अगर (io__get_hex(io, &temp) != ' ')
		वापस false;
	*min = temp;

	ch = io__get_dec(io, inode);
	अगर (ch != ' ') अणु
		*pathname = '\0';
		वापस ch == '\n';
	पूर्ण
	करो अणु
		ch = io__get_अक्षर(io);
	पूर्ण जबतक (ch == ' ');
	जबतक (true) अणु
		अगर (ch < 0)
			वापस false;
		अगर (ch == '\0' || ch == '\n' ||
		    (pathname + 1 - start_pathname) >= pathname_size) अणु
			*pathname = '\0';
			वापस true;
		पूर्ण
		*pathname++ = ch;
		ch = io__get_अक्षर(io);
	पूर्ण
पूर्ण

अटल व्योम perf_record_mmap2__पढ़ो_build_id(काष्ठा perf_record_mmap2 *event,
					     bool is_kernel)
अणु
	काष्ठा build_id bid;
	पूर्णांक rc;

	अगर (is_kernel)
		rc = sysfs__पढ़ो_build_id("/sys/kernel/notes", &bid);
	अन्यथा
		rc = filename__पढ़ो_build_id(event->filename, &bid) > 0 ? 0 : -1;

	अगर (rc == 0) अणु
		स_नकल(event->build_id, bid.data, माप(bid.data));
		event->build_id_size = (u8) bid.size;
		event->header.misc |= PERF_RECORD_MISC_MMAP_BUILD_ID;
		event->__reserved_1 = 0;
		event->__reserved_2 = 0;
	पूर्ण अन्यथा अणु
		अगर (event->filename[0] == '/') अणु
			pr_debug2("Failed to read build ID for %s\n",
				  event->filename);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक perf_event__synthesize_mmap_events(काष्ठा perf_tool *tool,
				       जोड़ perf_event *event,
				       pid_t pid, pid_t tgid,
				       perf_event__handler_t process,
				       काष्ठा machine *machine,
				       bool mmap_data)
अणु
	अचिन्हित दीर्घ दीर्घ t;
	अक्षर bf[बफ_मान];
	काष्ठा io io;
	bool truncation = false;
	अचिन्हित दीर्घ दीर्घ समयout = proc_map_समयout * 1000000ULL;
	पूर्णांक rc = 0;
	स्थिर अक्षर *hugetlbfs_mnt = hugetlbfs__mountpoपूर्णांक();
	पूर्णांक hugetlbfs_mnt_len = hugetlbfs_mnt ? म_माप(hugetlbfs_mnt) : 0;

	अगर (machine__is_शेष_guest(machine))
		वापस 0;

	snम_लिखो(bf, माप(bf), "%s/proc/%d/task/%d/maps",
		machine->root_dir, pid, pid);

	io.fd = खोलो(bf, O_RDONLY, 0);
	अगर (io.fd < 0) अणु
		/*
		 * We raced with a task निकासing - just वापस:
		 */
		pr_debug("couldn't open %s\n", bf);
		वापस -1;
	पूर्ण
	io__init(&io, io.fd, bf, माप(bf));

	event->header.type = PERF_RECORD_MMAP2;
	t = rdघड़ी();

	जबतक (!io.eof) अणु
		अटल स्थिर अक्षर anonstr[] = "//anon";
		माप_प्रकार size, aligned_size;

		/* ensure null termination since stack will be reused. */
		event->mmap2.filename[0] = '\0';

		/* 00400000-0040c000 r-xp 00000000 fd:01 41038  /bin/cat */
		अगर (!पढ़ो_proc_maps_line(&io,
					&event->mmap2.start,
					&event->mmap2.len,
					&event->mmap2.prot,
					&event->mmap2.flags,
					&event->mmap2.pgoff,
					&event->mmap2.maj,
					&event->mmap2.min,
					&event->mmap2.ino,
					माप(event->mmap2.filename),
					event->mmap2.filename))
			जारी;

		अगर ((rdघड़ी() - t) > समयout) अणु
			pr_warning("Reading %s/proc/%d/task/%d/maps time out. "
				   "You may want to increase "
				   "the time limit by --proc-map-timeout\n",
				   machine->root_dir, pid, pid);
			truncation = true;
			जाओ out;
		पूर्ण

		event->mmap2.ino_generation = 0;

		/*
		 * Just like the kernel, see __perf_event_mmap in kernel/perf_event.c
		 */
		अगर (machine__is_host(machine))
			event->header.misc = PERF_RECORD_MISC_USER;
		अन्यथा
			event->header.misc = PERF_RECORD_MISC_GUEST_USER;

		अगर ((event->mmap2.prot & PROT_EXEC) == 0) अणु
			अगर (!mmap_data || (event->mmap2.prot & PROT_READ) == 0)
				जारी;

			event->header.misc |= PERF_RECORD_MISC_MMAP_DATA;
		पूर्ण

out:
		अगर (truncation)
			event->header.misc |= PERF_RECORD_MISC_PROC_MAP_PARSE_TIMEOUT;

		अगर (!म_भेद(event->mmap2.filename, ""))
			म_नकल(event->mmap2.filename, anonstr);

		अगर (hugetlbfs_mnt_len &&
		    !म_भेदन(event->mmap2.filename, hugetlbfs_mnt,
			     hugetlbfs_mnt_len)) अणु
			म_नकल(event->mmap2.filename, anonstr);
			event->mmap2.flags |= MAP_HUGETLB;
		पूर्ण

		size = म_माप(event->mmap2.filename) + 1;
		aligned_size = PERF_ALIGN(size, माप(u64));
		event->mmap2.len -= event->mmap.start;
		event->mmap2.header.size = (माप(event->mmap2) -
					(माप(event->mmap2.filename) - aligned_size));
		स_रखो(event->mmap2.filename + size, 0, machine->id_hdr_size +
			(aligned_size - size));
		event->mmap2.header.size += machine->id_hdr_size;
		event->mmap2.pid = tgid;
		event->mmap2.tid = pid;

		अगर (symbol_conf.buildid_mmap2)
			perf_record_mmap2__पढ़ो_build_id(&event->mmap2, false);

		अगर (perf_tool__process_synth_event(tool, event, machine, process) != 0) अणु
			rc = -1;
			अवरोध;
		पूर्ण

		अगर (truncation)
			अवरोध;
	पूर्ण

	बंद(io.fd);
	वापस rc;
पूर्ण

#अगर_घोषित HAVE_खाता_HANDLE
अटल पूर्णांक perf_event__synthesize_cgroup(काष्ठा perf_tool *tool,
					 जोड़ perf_event *event,
					 अक्षर *path, माप_प्रकार mount_len,
					 perf_event__handler_t process,
					 काष्ठा machine *machine)
अणु
	माप_प्रकार event_size = माप(event->cgroup) - माप(event->cgroup.path);
	माप_प्रकार path_len = म_माप(path) - mount_len + 1;
	काष्ठा अणु
		काष्ठा file_handle fh;
		uपूर्णांक64_t cgroup_id;
	पूर्ण handle;
	पूर्णांक mount_id;

	जबतक (path_len % माप(u64))
		path[mount_len + path_len++] = '\0';

	स_रखो(&event->cgroup, 0, event_size);

	event->cgroup.header.type = PERF_RECORD_CGROUP;
	event->cgroup.header.size = event_size + path_len + machine->id_hdr_size;

	handle.fh.handle_bytes = माप(handle.cgroup_id);
	अगर (name_to_handle_at(AT_FDCWD, path, &handle.fh, &mount_id, 0) < 0) अणु
		pr_debug("stat failed: %s\n", path);
		वापस -1;
	पूर्ण

	event->cgroup.id = handle.cgroup_id;
	म_नकलन(event->cgroup.path, path + mount_len, path_len);
	स_रखो(event->cgroup.path + path_len, 0, machine->id_hdr_size);

	अगर (perf_tool__process_synth_event(tool, event, machine, process) < 0) अणु
		pr_debug("process synth event failed\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_event__walk_cgroup_tree(काष्ठा perf_tool *tool,
					जोड़ perf_event *event,
					अक्षर *path, माप_प्रकार mount_len,
					perf_event__handler_t process,
					काष्ठा machine *machine)
अणु
	माप_प्रकार pos = म_माप(path);
	सूची *d;
	काष्ठा dirent *dent;
	पूर्णांक ret = 0;

	अगर (perf_event__synthesize_cgroup(tool, event, path, mount_len,
					  process, machine) < 0)
		वापस -1;

	d = सूची_खोलो(path);
	अगर (d == शून्य) अणु
		pr_debug("failed to open directory: %s\n", path);
		वापस -1;
	पूर्ण

	जबतक ((dent = सूची_पढ़ो(d)) != शून्य) अणु
		अगर (dent->d_type != DT_सूची)
			जारी;
		अगर (!म_भेद(dent->d_name, ".") ||
		    !म_भेद(dent->d_name, ".."))
			जारी;

		/* any sane path should be less than PATH_MAX */
		अगर (म_माप(path) + म_माप(dent->d_name) + 1 >= PATH_MAX)
			जारी;

		अगर (path[pos - 1] != '/')
			म_जोड़ो(path, "/");
		म_जोड़ो(path, dent->d_name);

		ret = perf_event__walk_cgroup_tree(tool, event, path,
						   mount_len, process, machine);
		अगर (ret < 0)
			अवरोध;

		path[pos] = '\0';
	पूर्ण

	बंद_सूची(d);
	वापस ret;
पूर्ण

पूर्णांक perf_event__synthesize_cgroups(काष्ठा perf_tool *tool,
				   perf_event__handler_t process,
				   काष्ठा machine *machine)
अणु
	जोड़ perf_event event;
	अक्षर cgrp_root[PATH_MAX];
	माप_प्रकार mount_len;  /* length of mount poपूर्णांक in the path */

	अगर (!tool || !tool->cgroup_events)
		वापस 0;

	अगर (cgroupfs_find_mountpoपूर्णांक(cgrp_root, PATH_MAX, "perf_event") < 0) अणु
		pr_debug("cannot find cgroup mount point\n");
		वापस -1;
	पूर्ण

	mount_len = म_माप(cgrp_root);
	/* make sure the path starts with a slash (after mount poपूर्णांक) */
	म_जोड़ो(cgrp_root, "/");

	अगर (perf_event__walk_cgroup_tree(tool, &event, cgrp_root, mount_len,
					 process, machine) < 0)
		वापस -1;

	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक perf_event__synthesize_cgroups(काष्ठा perf_tool *tool __maybe_unused,
				   perf_event__handler_t process __maybe_unused,
				   काष्ठा machine *machine __maybe_unused)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

पूर्णांक perf_event__synthesize_modules(काष्ठा perf_tool *tool, perf_event__handler_t process,
				   काष्ठा machine *machine)
अणु
	पूर्णांक rc = 0;
	काष्ठा map *pos;
	काष्ठा maps *maps = machine__kernel_maps(machine);
	जोड़ perf_event *event;
	माप_प्रकार size = symbol_conf.buildid_mmap2 ?
			माप(event->mmap2) : माप(event->mmap);

	event = zalloc(size + machine->id_hdr_size);
	अगर (event == शून्य) अणु
		pr_debug("Not enough memory synthesizing mmap event "
			 "for kernel modules\n");
		वापस -1;
	पूर्ण

	/*
	 * kernel uses 0 क्रम user space maps, see kernel/perf_event.c
	 * __perf_event_mmap
	 */
	अगर (machine__is_host(machine))
		event->header.misc = PERF_RECORD_MISC_KERNEL;
	अन्यथा
		event->header.misc = PERF_RECORD_MISC_GUEST_KERNEL;

	maps__क्रम_each_entry(maps, pos) अणु
		अगर (!__map__is_kmodule(pos))
			जारी;

		अगर (symbol_conf.buildid_mmap2) अणु
			size = PERF_ALIGN(pos->dso->दीर्घ_name_len + 1, माप(u64));
			event->mmap2.header.type = PERF_RECORD_MMAP2;
			event->mmap2.header.size = (माप(event->mmap2) -
						(माप(event->mmap2.filename) - size));
			स_रखो(event->mmap2.filename + size, 0, machine->id_hdr_size);
			event->mmap2.header.size += machine->id_hdr_size;
			event->mmap2.start = pos->start;
			event->mmap2.len   = pos->end - pos->start;
			event->mmap2.pid   = machine->pid;

			स_नकल(event->mmap2.filename, pos->dso->दीर्घ_name,
			       pos->dso->दीर्घ_name_len + 1);

			perf_record_mmap2__पढ़ो_build_id(&event->mmap2, false);
		पूर्ण अन्यथा अणु
			size = PERF_ALIGN(pos->dso->दीर्घ_name_len + 1, माप(u64));
			event->mmap.header.type = PERF_RECORD_MMAP;
			event->mmap.header.size = (माप(event->mmap) -
						(माप(event->mmap.filename) - size));
			स_रखो(event->mmap.filename + size, 0, machine->id_hdr_size);
			event->mmap.header.size += machine->id_hdr_size;
			event->mmap.start = pos->start;
			event->mmap.len   = pos->end - pos->start;
			event->mmap.pid   = machine->pid;

			स_नकल(event->mmap.filename, pos->dso->दीर्घ_name,
			       pos->dso->दीर्घ_name_len + 1);
		पूर्ण

		अगर (perf_tool__process_synth_event(tool, event, machine, process) != 0) अणु
			rc = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(event);
	वापस rc;
पूर्ण

अटल पूर्णांक filter_task(स्थिर काष्ठा dirent *dirent)
अणु
	वापस है_अंक(dirent->d_name[0]);
पूर्ण

अटल पूर्णांक __event__syntheमाप_प्रकारhपढ़ो(जोड़ perf_event *comm_event,
				      जोड़ perf_event *mmap_event,
				      जोड़ perf_event *विभाजन_event,
				      जोड़ perf_event *namespaces_event,
				      pid_t pid, पूर्णांक full, perf_event__handler_t process,
				      काष्ठा perf_tool *tool, काष्ठा machine *machine, bool mmap_data)
अणु
	अक्षर filename[PATH_MAX];
	काष्ठा dirent **dirent;
	pid_t tgid, ppid;
	पूर्णांक rc = 0;
	पूर्णांक i, n;

	/* special हाल: only send one comm event using passed in pid */
	अगर (!full) अणु
		tgid = perf_event__synthesize_comm(tool, comm_event, pid,
						   process, machine);

		अगर (tgid == -1)
			वापस -1;

		अगर (perf_event__synthesize_namespaces(tool, namespaces_event, pid,
						      tgid, process, machine) < 0)
			वापस -1;

		/*
		 * send mmap only क्रम thपढ़ो group leader
		 * see thपढ़ो__init_maps()
		 */
		अगर (pid == tgid &&
		    perf_event__synthesize_mmap_events(tool, mmap_event, pid, tgid,
						       process, machine, mmap_data))
			वापस -1;

		वापस 0;
	पूर्ण

	अगर (machine__is_शेष_guest(machine))
		वापस 0;

	snम_लिखो(filename, माप(filename), "%s/proc/%d/task",
		 machine->root_dir, pid);

	n = scandir(filename, &dirent, filter_task, alphasort);
	अगर (n < 0)
		वापस n;

	क्रम (i = 0; i < n; i++) अणु
		अक्षर *end;
		pid_t _pid;
		bool kernel_thपढ़ो = false;

		_pid = म_से_दीर्घ(dirent[i]->d_name, &end, 10);
		अगर (*end)
			जारी;

		rc = -1;
		अगर (perf_event__prepare_comm(comm_event, pid, _pid, machine,
					     &tgid, &ppid, &kernel_thपढ़ो) != 0)
			अवरोध;

		अगर (perf_event__synthesize_विभाजन(tool, विभाजन_event, _pid, tgid,
						ppid, process, machine) < 0)
			अवरोध;

		अगर (perf_event__synthesize_namespaces(tool, namespaces_event, _pid,
						      tgid, process, machine) < 0)
			अवरोध;

		/*
		 * Send the prepared comm event
		 */
		अगर (perf_tool__process_synth_event(tool, comm_event, machine, process) != 0)
			अवरोध;

		rc = 0;
		अगर (_pid == pid && !kernel_thपढ़ो) अणु
			/* process the parent's maps too */
			rc = perf_event__synthesize_mmap_events(tool, mmap_event, pid, tgid,
						process, machine, mmap_data);
			अगर (rc)
				अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < n; i++)
		zमुक्त(&dirent[i]);
	मुक्त(dirent);

	वापस rc;
पूर्ण

पूर्णांक perf_event__syntheमाप_प्रकारhपढ़ो_map(काष्ठा perf_tool *tool,
				      काष्ठा perf_thपढ़ो_map *thपढ़ोs,
				      perf_event__handler_t process,
				      काष्ठा machine *machine,
				      bool mmap_data)
अणु
	जोड़ perf_event *comm_event, *mmap_event, *विभाजन_event;
	जोड़ perf_event *namespaces_event;
	पूर्णांक err = -1, thपढ़ो, j;

	comm_event = दो_स्मृति(माप(comm_event->comm) + machine->id_hdr_size);
	अगर (comm_event == शून्य)
		जाओ out;

	mmap_event = दो_स्मृति(माप(mmap_event->mmap2) + machine->id_hdr_size);
	अगर (mmap_event == शून्य)
		जाओ out_मुक्त_comm;

	विभाजन_event = दो_स्मृति(माप(विभाजन_event->विभाजन) + machine->id_hdr_size);
	अगर (विभाजन_event == शून्य)
		जाओ out_मुक्त_mmap;

	namespaces_event = दो_स्मृति(माप(namespaces_event->namespaces) +
				  (NR_NAMESPACES * माप(काष्ठा perf_ns_link_info)) +
				  machine->id_hdr_size);
	अगर (namespaces_event == शून्य)
		जाओ out_मुक्त_विभाजन;

	err = 0;
	क्रम (thपढ़ो = 0; thपढ़ो < thपढ़ोs->nr; ++thपढ़ो) अणु
		अगर (__event__syntheमाप_प्रकारhपढ़ो(comm_event, mmap_event,
					       विभाजन_event, namespaces_event,
					       perf_thपढ़ो_map__pid(thपढ़ोs, thपढ़ो), 0,
					       process, tool, machine,
					       mmap_data)) अणु
			err = -1;
			अवरोध;
		पूर्ण

		/*
		 * comm.pid is set to thपढ़ो group id by
		 * perf_event__synthesize_comm
		 */
		अगर ((पूर्णांक) comm_event->comm.pid != perf_thपढ़ो_map__pid(thपढ़ोs, thपढ़ो)) अणु
			bool need_leader = true;

			/* is thपढ़ो group leader in thपढ़ो_map? */
			क्रम (j = 0; j < thपढ़ोs->nr; ++j) अणु
				अगर ((पूर्णांक) comm_event->comm.pid == perf_thपढ़ो_map__pid(thपढ़ोs, j)) अणु
					need_leader = false;
					अवरोध;
				पूर्ण
			पूर्ण

			/* अगर not, generate events क्रम it */
			अगर (need_leader &&
			    __event__syntheमाप_प्रकारhपढ़ो(comm_event, mmap_event,
						       विभाजन_event, namespaces_event,
						       comm_event->comm.pid, 0,
						       process, tool, machine,
						       mmap_data)) अणु
				err = -1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	मुक्त(namespaces_event);
out_मुक्त_विभाजन:
	मुक्त(विभाजन_event);
out_मुक्त_mmap:
	मुक्त(mmap_event);
out_मुक्त_comm:
	मुक्त(comm_event);
out:
	वापस err;
पूर्ण

अटल पूर्णांक __perf_event__syntheमाप_प्रकारhपढ़ोs(काष्ठा perf_tool *tool,
					    perf_event__handler_t process,
					    काष्ठा machine *machine,
					    bool mmap_data,
					    काष्ठा dirent **dirent,
					    पूर्णांक start,
					    पूर्णांक num)
अणु
	जोड़ perf_event *comm_event, *mmap_event, *विभाजन_event;
	जोड़ perf_event *namespaces_event;
	पूर्णांक err = -1;
	अक्षर *end;
	pid_t pid;
	पूर्णांक i;

	comm_event = दो_स्मृति(माप(comm_event->comm) + machine->id_hdr_size);
	अगर (comm_event == शून्य)
		जाओ out;

	mmap_event = दो_स्मृति(माप(mmap_event->mmap2) + machine->id_hdr_size);
	अगर (mmap_event == शून्य)
		जाओ out_मुक्त_comm;

	विभाजन_event = दो_स्मृति(माप(विभाजन_event->विभाजन) + machine->id_hdr_size);
	अगर (विभाजन_event == शून्य)
		जाओ out_मुक्त_mmap;

	namespaces_event = दो_स्मृति(माप(namespaces_event->namespaces) +
				  (NR_NAMESPACES * माप(काष्ठा perf_ns_link_info)) +
				  machine->id_hdr_size);
	अगर (namespaces_event == शून्य)
		जाओ out_मुक्त_विभाजन;

	क्रम (i = start; i < start + num; i++) अणु
		अगर (!है_अंक(dirent[i]->d_name[0]))
			जारी;

		pid = (pid_t)म_से_दीर्घ(dirent[i]->d_name, &end, 10);
		/* only पूर्णांकerested in proper numerical dirents */
		अगर (*end)
			जारी;
		/*
		 * We may race with निकासing thपढ़ो, so करोn't stop just because
		 * one thपढ़ो couldn't be synthesized.
		 */
		__event__syntheमाप_प्रकारhपढ़ो(comm_event, mmap_event, विभाजन_event,
					   namespaces_event, pid, 1, process,
					   tool, machine, mmap_data);
	पूर्ण
	err = 0;

	मुक्त(namespaces_event);
out_मुक्त_विभाजन:
	मुक्त(विभाजन_event);
out_मुक्त_mmap:
	मुक्त(mmap_event);
out_मुक्त_comm:
	मुक्त(comm_event);
out:
	वापस err;
पूर्ण

काष्ठा syntheमाप_प्रकारhपढ़ोs_arg अणु
	काष्ठा perf_tool *tool;
	perf_event__handler_t process;
	काष्ठा machine *machine;
	bool mmap_data;
	काष्ठा dirent **dirent;
	पूर्णांक num;
	पूर्णांक start;
पूर्ण;

अटल व्योम *syntheमाप_प्रकारhपढ़ोs_worker(व्योम *arg)
अणु
	काष्ठा syntheमाप_प्रकारhपढ़ोs_arg *args = arg;

	__perf_event__syntheमाप_प्रकारhपढ़ोs(args->tool, args->process,
					 args->machine, args->mmap_data,
					 args->dirent,
					 args->start, args->num);
	वापस शून्य;
पूर्ण

पूर्णांक perf_event__syntheमाप_प्रकारhपढ़ोs(काष्ठा perf_tool *tool,
				   perf_event__handler_t process,
				   काष्ठा machine *machine,
				   bool mmap_data,
				   अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize)
अणु
	काष्ठा syntheमाप_प्रकारhपढ़ोs_arg *args = शून्य;
	pthपढ़ो_t *syntheमाप_प्रकारhपढ़ोs = शून्य;
	अक्षर proc_path[PATH_MAX];
	काष्ठा dirent **dirent;
	पूर्णांक num_per_thपढ़ो;
	पूर्णांक m, n, i, j;
	पूर्णांक thपढ़ो_nr;
	पूर्णांक base = 0;
	पूर्णांक err = -1;


	अगर (machine__is_शेष_guest(machine))
		वापस 0;

	snम_लिखो(proc_path, माप(proc_path), "%s/proc", machine->root_dir);
	n = scandir(proc_path, &dirent, filter_task, alphasort);
	अगर (n < 0)
		वापस err;

	अगर (nr_thपढ़ोs_synthesize == अच_पूर्णांक_उच्च)
		thपढ़ो_nr = sysconf(_SC_NPROCESSORS_ONLN);
	अन्यथा
		thपढ़ो_nr = nr_thपढ़ोs_synthesize;

	अगर (thपढ़ो_nr <= 1) अणु
		err = __perf_event__syntheमाप_प्रकारhपढ़ोs(tool, process,
						       machine, mmap_data,
						       dirent, base, n);
		जाओ मुक्त_dirent;
	पूर्ण
	अगर (thपढ़ो_nr > n)
		thपढ़ो_nr = n;

	syntheमाप_प्रकारhपढ़ोs = सुस्मृति(माप(pthपढ़ो_t), thपढ़ो_nr);
	अगर (syntheमाप_प्रकारhपढ़ोs == शून्य)
		जाओ मुक्त_dirent;

	args = सुस्मृति(माप(*args), thपढ़ो_nr);
	अगर (args == शून्य)
		जाओ मुक्त_thपढ़ोs;

	num_per_thपढ़ो = n / thपढ़ो_nr;
	m = n % thपढ़ो_nr;
	क्रम (i = 0; i < thपढ़ो_nr; i++) अणु
		args[i].tool = tool;
		args[i].process = process;
		args[i].machine = machine;
		args[i].mmap_data = mmap_data;
		args[i].dirent = dirent;
	पूर्ण
	क्रम (i = 0; i < m; i++) अणु
		args[i].num = num_per_thपढ़ो + 1;
		args[i].start = i * args[i].num;
	पूर्ण
	अगर (i != 0)
		base = args[i-1].start + args[i-1].num;
	क्रम (j = i; j < thपढ़ो_nr; j++) अणु
		args[j].num = num_per_thपढ़ो;
		args[j].start = base + (j - i) * args[i].num;
	पूर्ण

	क्रम (i = 0; i < thपढ़ो_nr; i++) अणु
		अगर (pthपढ़ो_create(&syntheमाप_प्रकारhपढ़ोs[i], शून्य,
				   syntheमाप_प्रकारhपढ़ोs_worker, &args[i]))
			जाओ out_join;
	पूर्ण
	err = 0;
out_join:
	क्रम (i = 0; i < thपढ़ो_nr; i++)
		pthपढ़ो_join(syntheमाप_प्रकारhपढ़ोs[i], शून्य);
	मुक्त(args);
मुक्त_thपढ़ोs:
	मुक्त(syntheमाप_प्रकारhपढ़ोs);
मुक्त_dirent:
	क्रम (i = 0; i < n; i++)
		zमुक्त(&dirent[i]);
	मुक्त(dirent);

	वापस err;
पूर्ण

पूर्णांक __weak perf_event__synthesize_extra_kmaps(काष्ठा perf_tool *tool __maybe_unused,
					      perf_event__handler_t process __maybe_unused,
					      काष्ठा machine *machine __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __perf_event__synthesize_kernel_mmap(काष्ठा perf_tool *tool,
						perf_event__handler_t process,
						काष्ठा machine *machine)
अणु
	जोड़ perf_event *event;
	माप_प्रकार size = symbol_conf.buildid_mmap2 ?
			माप(event->mmap2) : माप(event->mmap);
	काष्ठा map *map = machine__kernel_map(machine);
	काष्ठा kmap *kmap;
	पूर्णांक err;

	अगर (map == शून्य)
		वापस -1;

	kmap = map__kmap(map);
	अगर (!kmap->ref_reloc_sym)
		वापस -1;

	/*
	 * We should get this from /sys/kernel/sections/.text, but till that is
	 * available use this, and after it is use this as a fallback क्रम older
	 * kernels.
	 */
	event = zalloc(size + machine->id_hdr_size);
	अगर (event == शून्य) अणु
		pr_debug("Not enough memory synthesizing mmap event "
			 "for kernel modules\n");
		वापस -1;
	पूर्ण

	अगर (machine__is_host(machine)) अणु
		/*
		 * kernel uses PERF_RECORD_MISC_USER क्रम user space maps,
		 * see kernel/perf_event.c __perf_event_mmap
		 */
		event->header.misc = PERF_RECORD_MISC_KERNEL;
	पूर्ण अन्यथा अणु
		event->header.misc = PERF_RECORD_MISC_GUEST_KERNEL;
	पूर्ण

	अगर (symbol_conf.buildid_mmap2) अणु
		size = snम_लिखो(event->mmap2.filename, माप(event->mmap2.filename),
				"%s%s", machine->mmap_name, kmap->ref_reloc_sym->name) + 1;
		size = PERF_ALIGN(size, माप(u64));
		event->mmap2.header.type = PERF_RECORD_MMAP2;
		event->mmap2.header.size = (माप(event->mmap2) -
				(माप(event->mmap2.filename) - size) + machine->id_hdr_size);
		event->mmap2.pgoff = kmap->ref_reloc_sym->addr;
		event->mmap2.start = map->start;
		event->mmap2.len   = map->end - event->mmap.start;
		event->mmap2.pid   = machine->pid;

		perf_record_mmap2__पढ़ो_build_id(&event->mmap2, true);
	पूर्ण अन्यथा अणु
		size = snम_लिखो(event->mmap.filename, माप(event->mmap.filename),
				"%s%s", machine->mmap_name, kmap->ref_reloc_sym->name) + 1;
		size = PERF_ALIGN(size, माप(u64));
		event->mmap.header.type = PERF_RECORD_MMAP;
		event->mmap.header.size = (माप(event->mmap) -
				(माप(event->mmap.filename) - size) + machine->id_hdr_size);
		event->mmap.pgoff = kmap->ref_reloc_sym->addr;
		event->mmap.start = map->start;
		event->mmap.len   = map->end - event->mmap.start;
		event->mmap.pid   = machine->pid;
	पूर्ण

	err = perf_tool__process_synth_event(tool, event, machine, process);
	मुक्त(event);

	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_kernel_mmap(काष्ठा perf_tool *tool,
				       perf_event__handler_t process,
				       काष्ठा machine *machine)
अणु
	पूर्णांक err;

	err = __perf_event__synthesize_kernel_mmap(tool, process, machine);
	अगर (err < 0)
		वापस err;

	वापस perf_event__synthesize_extra_kmaps(tool, process, machine);
पूर्ण

पूर्णांक perf_event__syntheमाप_प्रकारhपढ़ो_map2(काष्ठा perf_tool *tool,
				      काष्ठा perf_thपढ़ो_map *thपढ़ोs,
				      perf_event__handler_t process,
				      काष्ठा machine *machine)
अणु
	जोड़ perf_event *event;
	पूर्णांक i, err, size;

	size  = माप(event->thपढ़ो_map);
	size +=	thपढ़ोs->nr * माप(event->thपढ़ो_map.entries[0]);

	event = zalloc(size);
	अगर (!event)
		वापस -ENOMEM;

	event->header.type = PERF_RECORD_THREAD_MAP;
	event->header.size = size;
	event->thपढ़ो_map.nr = thपढ़ोs->nr;

	क्रम (i = 0; i < thपढ़ोs->nr; i++) अणु
		काष्ठा perf_record_thपढ़ो_map_entry *entry = &event->thपढ़ो_map.entries[i];
		अक्षर *comm = perf_thपढ़ो_map__comm(thपढ़ोs, i);

		अगर (!comm)
			comm = (अक्षर *) "";

		entry->pid = perf_thपढ़ो_map__pid(thपढ़ोs, i);
		म_नकलन((अक्षर *) &entry->comm, comm, माप(entry->comm));
	पूर्ण

	err = process(tool, event, शून्य, machine);

	मुक्त(event);
	वापस err;
पूर्ण

अटल व्योम synthesize_cpus(काष्ठा cpu_map_entries *cpus,
			    काष्ठा perf_cpu_map *map)
अणु
	पूर्णांक i;

	cpus->nr = map->nr;

	क्रम (i = 0; i < map->nr; i++)
		cpus->cpu[i] = map->map[i];
पूर्ण

अटल व्योम synthesize_mask(काष्ठा perf_record_record_cpu_map *mask,
			    काष्ठा perf_cpu_map *map, पूर्णांक max)
अणु
	पूर्णांक i;

	mask->nr = BITS_TO_LONGS(max);
	mask->दीर्घ_size = माप(दीर्घ);

	क्रम (i = 0; i < map->nr; i++)
		set_bit(map->map[i], mask->mask);
पूर्ण

अटल माप_प्रकार cpus_size(काष्ठा perf_cpu_map *map)
अणु
	वापस माप(काष्ठा cpu_map_entries) + map->nr * माप(u16);
पूर्ण

अटल माप_प्रकार mask_size(काष्ठा perf_cpu_map *map, पूर्णांक *max)
अणु
	पूर्णांक i;

	*max = 0;

	क्रम (i = 0; i < map->nr; i++) अणु
		/* bit position of the cpu is + 1 */
		पूर्णांक bit = map->map[i] + 1;

		अगर (bit > *max)
			*max = bit;
	पूर्ण

	वापस माप(काष्ठा perf_record_record_cpu_map) + BITS_TO_LONGS(*max) * माप(दीर्घ);
पूर्ण

व्योम *cpu_map_data__alloc(काष्ठा perf_cpu_map *map, माप_प्रकार *size, u16 *type, पूर्णांक *max)
अणु
	माप_प्रकार size_cpus, size_mask;
	bool is_dummy = perf_cpu_map__empty(map);

	/*
	 * Both array and mask data have variable size based
	 * on the number of cpus and their actual values.
	 * The size of the 'struct perf_record_cpu_map_data' is:
	 *
	 *   array = size of 'struct cpu_map_entries' +
	 *           number of cpus * माप(u64)
	 *
	 *   mask  = size of 'struct perf_record_record_cpu_map' +
	 *           maximum cpu bit converted to size of दीर्घs
	 *
	 * and finally + the size of 'struct perf_record_cpu_map_data'.
	 */
	size_cpus = cpus_size(map);
	size_mask = mask_size(map, max);

	अगर (is_dummy || (size_cpus < size_mask)) अणु
		*size += size_cpus;
		*type  = PERF_CPU_MAP__CPUS;
	पूर्ण अन्यथा अणु
		*size += size_mask;
		*type  = PERF_CPU_MAP__MASK;
	पूर्ण

	*size += माप(काष्ठा perf_record_cpu_map_data);
	*size = PERF_ALIGN(*size, माप(u64));
	वापस zalloc(*size);
पूर्ण

व्योम cpu_map_data__synthesize(काष्ठा perf_record_cpu_map_data *data, काष्ठा perf_cpu_map *map,
			      u16 type, पूर्णांक max)
अणु
	data->type = type;

	चयन (type) अणु
	हाल PERF_CPU_MAP__CPUS:
		synthesize_cpus((काष्ठा cpu_map_entries *) data->data, map);
		अवरोध;
	हाल PERF_CPU_MAP__MASK:
		synthesize_mask((काष्ठा perf_record_record_cpu_map *)data->data, map, max);
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा perf_record_cpu_map *cpu_map_event__new(काष्ठा perf_cpu_map *map)
अणु
	माप_प्रकार size = माप(काष्ठा perf_record_cpu_map);
	काष्ठा perf_record_cpu_map *event;
	पूर्णांक max;
	u16 type;

	event = cpu_map_data__alloc(map, &size, &type, &max);
	अगर (!event)
		वापस शून्य;

	event->header.type = PERF_RECORD_CPU_MAP;
	event->header.size = size;
	event->data.type   = type;

	cpu_map_data__synthesize(&event->data, map, type, max);
	वापस event;
पूर्ण

पूर्णांक perf_event__synthesize_cpu_map(काष्ठा perf_tool *tool,
				   काष्ठा perf_cpu_map *map,
				   perf_event__handler_t process,
				   काष्ठा machine *machine)
अणु
	काष्ठा perf_record_cpu_map *event;
	पूर्णांक err;

	event = cpu_map_event__new(map);
	अगर (!event)
		वापस -ENOMEM;

	err = process(tool, (जोड़ perf_event *) event, शून्य, machine);

	मुक्त(event);
	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_stat_config(काष्ठा perf_tool *tool,
				       काष्ठा perf_stat_config *config,
				       perf_event__handler_t process,
				       काष्ठा machine *machine)
अणु
	काष्ठा perf_record_stat_config *event;
	पूर्णांक size, i = 0, err;

	size  = माप(*event);
	size += (PERF_STAT_CONFIG_TERM__MAX * माप(event->data[0]));

	event = zalloc(size);
	अगर (!event)
		वापस -ENOMEM;

	event->header.type = PERF_RECORD_STAT_CONFIG;
	event->header.size = size;
	event->nr          = PERF_STAT_CONFIG_TERM__MAX;

#घोषणा ADD(__term, __val)					\
	event->data[i].tag = PERF_STAT_CONFIG_TERM__##__term;	\
	event->data[i].val = __val;				\
	i++;

	ADD(AGGR_MODE,	config->aggr_mode)
	ADD(INTERVAL,	config->पूर्णांकerval)
	ADD(SCALE,	config->scale)

	WARN_ONCE(i != PERF_STAT_CONFIG_TERM__MAX,
		  "stat config terms unbalanced\n");
#अघोषित ADD

	err = process(tool, (जोड़ perf_event *) event, शून्य, machine);

	मुक्त(event);
	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_stat(काष्ठा perf_tool *tool,
				u32 cpu, u32 thपढ़ो, u64 id,
				काष्ठा perf_counts_values *count,
				perf_event__handler_t process,
				काष्ठा machine *machine)
अणु
	काष्ठा perf_record_stat event;

	event.header.type = PERF_RECORD_STAT;
	event.header.size = माप(event);
	event.header.misc = 0;

	event.id        = id;
	event.cpu       = cpu;
	event.thपढ़ो    = thपढ़ो;
	event.val       = count->val;
	event.ena       = count->ena;
	event.run       = count->run;

	वापस process(tool, (जोड़ perf_event *) &event, शून्य, machine);
पूर्ण

पूर्णांक perf_event__synthesize_stat_round(काष्ठा perf_tool *tool,
				      u64 evसमय, u64 type,
				      perf_event__handler_t process,
				      काष्ठा machine *machine)
अणु
	काष्ठा perf_record_stat_round event;

	event.header.type = PERF_RECORD_STAT_ROUND;
	event.header.size = माप(event);
	event.header.misc = 0;

	event.समय = evसमय;
	event.type = type;

	वापस process(tool, (जोड़ perf_event *) &event, शून्य, machine);
पूर्ण

माप_प्रकार perf_event__sample_event_size(स्थिर काष्ठा perf_sample *sample, u64 type, u64 पढ़ो_क्रमmat)
अणु
	माप_प्रकार sz, result = माप(काष्ठा perf_record_sample);

	अगर (type & PERF_SAMPLE_IDENTIFIER)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_IP)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_TID)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_TIME)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_ADDR)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_ID)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_STREAM_ID)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_CPU)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_PERIOD)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_READ) अणु
		result += माप(u64);
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
			result += माप(u64);
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
			result += माप(u64);
		/* PERF_FORMAT_ID is क्रमced क्रम PERF_SAMPLE_READ */
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
			sz = sample->पढ़ो.group.nr *
			     माप(काष्ठा sample_पढ़ो_value);
			result += sz;
		पूर्ण अन्यथा अणु
			result += माप(u64);
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_CALLCHAIN) अणु
		sz = (sample->callchain->nr + 1) * माप(u64);
		result += sz;
	पूर्ण

	अगर (type & PERF_SAMPLE_RAW) अणु
		result += माप(u32);
		result += sample->raw_size;
	पूर्ण

	अगर (type & PERF_SAMPLE_BRANCH_STACK) अणु
		sz = sample->branch_stack->nr * माप(काष्ठा branch_entry);
		/* nr, hw_idx */
		sz += 2 * माप(u64);
		result += sz;
	पूर्ण

	अगर (type & PERF_SAMPLE_REGS_USER) अणु
		अगर (sample->user_regs.abi) अणु
			result += माप(u64);
			sz = hweight64(sample->user_regs.mask) * माप(u64);
			result += sz;
		पूर्ण अन्यथा अणु
			result += माप(u64);
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_STACK_USER) अणु
		sz = sample->user_stack.size;
		result += माप(u64);
		अगर (sz) अणु
			result += sz;
			result += माप(u64);
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_WEIGHT_TYPE)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_DATA_SRC)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_TRANSACTION)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_REGS_INTR) अणु
		अगर (sample->पूर्णांकr_regs.abi) अणु
			result += माप(u64);
			sz = hweight64(sample->पूर्णांकr_regs.mask) * माप(u64);
			result += sz;
		पूर्ण अन्यथा अणु
			result += माप(u64);
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_PHYS_ADDR)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_CGROUP)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_DATA_PAGE_SIZE)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_CODE_PAGE_SIZE)
		result += माप(u64);

	अगर (type & PERF_SAMPLE_AUX) अणु
		result += माप(u64);
		result += sample->aux_sample.size;
	पूर्ण

	वापस result;
पूर्ण

व्योम __weak arch_perf_synthesize_sample_weight(स्थिर काष्ठा perf_sample *data,
					       __u64 *array, u64 type __maybe_unused)
अणु
	*array = data->weight;
पूर्ण

पूर्णांक perf_event__synthesize_sample(जोड़ perf_event *event, u64 type, u64 पढ़ो_क्रमmat,
				  स्थिर काष्ठा perf_sample *sample)
अणु
	__u64 *array;
	माप_प्रकार sz;
	/*
	 * used क्रम cross-endian analysis. See git commit 65014ab3
	 * क्रम why this goofiness is needed.
	 */
	जोड़ u64_swap u;

	array = event->sample.array;

	अगर (type & PERF_SAMPLE_IDENTIFIER) अणु
		*array = sample->id;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_IP) अणु
		*array = sample->ip;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_TID) अणु
		u.val32[0] = sample->pid;
		u.val32[1] = sample->tid;
		*array = u.val64;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_TIME) अणु
		*array = sample->समय;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_ADDR) अणु
		*array = sample->addr;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_ID) अणु
		*array = sample->id;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_STREAM_ID) अणु
		*array = sample->stream_id;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_CPU) अणु
		u.val32[0] = sample->cpu;
		u.val32[1] = 0;
		*array = u.val64;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_PERIOD) अणु
		*array = sample->period;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_READ) अणु
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
			*array = sample->पढ़ो.group.nr;
		अन्यथा
			*array = sample->पढ़ो.one.value;
		array++;

		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED) अणु
			*array = sample->पढ़ो.समय_enabled;
			array++;
		पूर्ण

		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING) अणु
			*array = sample->पढ़ो.समय_running;
			array++;
		पूर्ण

		/* PERF_FORMAT_ID is क्रमced क्रम PERF_SAMPLE_READ */
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
			sz = sample->पढ़ो.group.nr *
			     माप(काष्ठा sample_पढ़ो_value);
			स_नकल(array, sample->पढ़ो.group.values, sz);
			array = (व्योम *)array + sz;
		पूर्ण अन्यथा अणु
			*array = sample->पढ़ो.one.id;
			array++;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_CALLCHAIN) अणु
		sz = (sample->callchain->nr + 1) * माप(u64);
		स_नकल(array, sample->callchain, sz);
		array = (व्योम *)array + sz;
	पूर्ण

	अगर (type & PERF_SAMPLE_RAW) अणु
		u.val32[0] = sample->raw_size;
		*array = u.val64;
		array = (व्योम *)array + माप(u32);

		स_नकल(array, sample->raw_data, sample->raw_size);
		array = (व्योम *)array + sample->raw_size;
	पूर्ण

	अगर (type & PERF_SAMPLE_BRANCH_STACK) अणु
		sz = sample->branch_stack->nr * माप(काष्ठा branch_entry);
		/* nr, hw_idx */
		sz += 2 * माप(u64);
		स_नकल(array, sample->branch_stack, sz);
		array = (व्योम *)array + sz;
	पूर्ण

	अगर (type & PERF_SAMPLE_REGS_USER) अणु
		अगर (sample->user_regs.abi) अणु
			*array++ = sample->user_regs.abi;
			sz = hweight64(sample->user_regs.mask) * माप(u64);
			स_नकल(array, sample->user_regs.regs, sz);
			array = (व्योम *)array + sz;
		पूर्ण अन्यथा अणु
			*array++ = 0;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_STACK_USER) अणु
		sz = sample->user_stack.size;
		*array++ = sz;
		अगर (sz) अणु
			स_नकल(array, sample->user_stack.data, sz);
			array = (व्योम *)array + sz;
			*array++ = sz;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_WEIGHT_TYPE) अणु
		arch_perf_synthesize_sample_weight(sample, array, type);
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_DATA_SRC) अणु
		*array = sample->data_src;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_TRANSACTION) अणु
		*array = sample->transaction;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_REGS_INTR) अणु
		अगर (sample->पूर्णांकr_regs.abi) अणु
			*array++ = sample->पूर्णांकr_regs.abi;
			sz = hweight64(sample->पूर्णांकr_regs.mask) * माप(u64);
			स_नकल(array, sample->पूर्णांकr_regs.regs, sz);
			array = (व्योम *)array + sz;
		पूर्ण अन्यथा अणु
			*array++ = 0;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_PHYS_ADDR) अणु
		*array = sample->phys_addr;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_CGROUP) अणु
		*array = sample->cgroup;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_DATA_PAGE_SIZE) अणु
		*array = sample->data_page_size;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_CODE_PAGE_SIZE) अणु
		*array = sample->code_page_size;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_AUX) अणु
		sz = sample->aux_sample.size;
		*array++ = sz;
		स_नकल(array, sample->aux_sample.data, sz);
		array = (व्योम *)array + sz;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_event__synthesize_id_index(काष्ठा perf_tool *tool, perf_event__handler_t process,
				    काष्ठा evlist *evlist, काष्ठा machine *machine)
अणु
	जोड़ perf_event *ev;
	काष्ठा evsel *evsel;
	माप_प्रकार nr = 0, i = 0, sz, max_nr, n;
	पूर्णांक err;

	pr_debug2("Synthesizing id index\n");

	max_nr = (UINT16_MAX - माप(काष्ठा perf_record_id_index)) /
		 माप(काष्ठा id_index_entry);

	evlist__क्रम_each_entry(evlist, evsel)
		nr += evsel->core.ids;

	n = nr > max_nr ? max_nr : nr;
	sz = माप(काष्ठा perf_record_id_index) + n * माप(काष्ठा id_index_entry);
	ev = zalloc(sz);
	अगर (!ev)
		वापस -ENOMEM;

	ev->id_index.header.type = PERF_RECORD_ID_INDEX;
	ev->id_index.header.size = sz;
	ev->id_index.nr = n;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		u32 j;

		क्रम (j = 0; j < evsel->core.ids; j++) अणु
			काष्ठा id_index_entry *e;
			काष्ठा perf_sample_id *sid;

			अगर (i >= n) अणु
				err = process(tool, ev, शून्य, machine);
				अगर (err)
					जाओ out_err;
				nr -= n;
				i = 0;
			पूर्ण

			e = &ev->id_index.entries[i++];

			e->id = evsel->core.id[j];

			sid = evlist__id2sid(evlist, e->id);
			अगर (!sid) अणु
				मुक्त(ev);
				वापस -ENOENT;
			पूर्ण

			e->idx = sid->idx;
			e->cpu = sid->cpu;
			e->tid = sid->tid;
		पूर्ण
	पूर्ण

	sz = माप(काष्ठा perf_record_id_index) + nr * माप(काष्ठा id_index_entry);
	ev->id_index.header.size = sz;
	ev->id_index.nr = nr;

	err = process(tool, ev, शून्य, machine);
out_err:
	मुक्त(ev);

	वापस err;
पूर्ण

पूर्णांक __machine__syntheमाप_प्रकारhपढ़ोs(काष्ठा machine *machine, काष्ठा perf_tool *tool,
				  काष्ठा target *target, काष्ठा perf_thपढ़ो_map *thपढ़ोs,
				  perf_event__handler_t process, bool data_mmap,
				  अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize)
अणु
	अगर (target__has_task(target))
		वापस perf_event__syntheमाप_प्रकारhपढ़ो_map(tool, thपढ़ोs, process, machine, data_mmap);
	अन्यथा अगर (target__has_cpu(target))
		वापस perf_event__syntheमाप_प्रकारhपढ़ोs(tool, process,
						      machine, data_mmap,
						      nr_thपढ़ोs_synthesize);
	/* command specअगरied */
	वापस 0;
पूर्ण

पूर्णांक machine__syntheमाप_प्रकारhपढ़ोs(काष्ठा machine *machine, काष्ठा target *target,
				काष्ठा perf_thपढ़ो_map *thपढ़ोs, bool data_mmap,
				अचिन्हित पूर्णांक nr_thपढ़ोs_synthesize)
अणु
	वापस __machine__syntheमाप_प्रकारhपढ़ोs(machine, शून्य, target, thपढ़ोs,
					     perf_event__process, data_mmap,
					     nr_thपढ़ोs_synthesize);
पूर्ण

अटल काष्ठा perf_record_event_update *event_update_event__new(माप_प्रकार size, u64 type, u64 id)
अणु
	काष्ठा perf_record_event_update *ev;

	size += माप(*ev);
	size  = PERF_ALIGN(size, माप(u64));

	ev = zalloc(size);
	अगर (ev) अणु
		ev->header.type = PERF_RECORD_EVENT_UPDATE;
		ev->header.size = (u16)size;
		ev->type	= type;
		ev->id		= id;
	पूर्ण
	वापस ev;
पूर्ण

पूर्णांक perf_event__synthesize_event_update_unit(काष्ठा perf_tool *tool, काष्ठा evsel *evsel,
					     perf_event__handler_t process)
अणु
	माप_प्रकार size = म_माप(evsel->unit);
	काष्ठा perf_record_event_update *ev;
	पूर्णांक err;

	ev = event_update_event__new(size + 1, PERF_EVENT_UPDATE__UNIT, evsel->core.id[0]);
	अगर (ev == शून्य)
		वापस -ENOMEM;

	strlcpy(ev->data, evsel->unit, size + 1);
	err = process(tool, (जोड़ perf_event *)ev, शून्य, शून्य);
	मुक्त(ev);
	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_event_update_scale(काष्ठा perf_tool *tool, काष्ठा evsel *evsel,
					      perf_event__handler_t process)
अणु
	काष्ठा perf_record_event_update *ev;
	काष्ठा perf_record_event_update_scale *ev_data;
	पूर्णांक err;

	ev = event_update_event__new(माप(*ev_data), PERF_EVENT_UPDATE__SCALE, evsel->core.id[0]);
	अगर (ev == शून्य)
		वापस -ENOMEM;

	ev_data = (काष्ठा perf_record_event_update_scale *)ev->data;
	ev_data->scale = evsel->scale;
	err = process(tool, (जोड़ perf_event *)ev, शून्य, शून्य);
	मुक्त(ev);
	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_event_update_name(काष्ठा perf_tool *tool, काष्ठा evsel *evsel,
					     perf_event__handler_t process)
अणु
	काष्ठा perf_record_event_update *ev;
	माप_प्रकार len = म_माप(evsel->name);
	पूर्णांक err;

	ev = event_update_event__new(len + 1, PERF_EVENT_UPDATE__NAME, evsel->core.id[0]);
	अगर (ev == शून्य)
		वापस -ENOMEM;

	strlcpy(ev->data, evsel->name, len + 1);
	err = process(tool, (जोड़ perf_event *)ev, शून्य, शून्य);
	मुक्त(ev);
	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_event_update_cpus(काष्ठा perf_tool *tool, काष्ठा evsel *evsel,
					     perf_event__handler_t process)
अणु
	माप_प्रकार size = माप(काष्ठा perf_record_event_update);
	काष्ठा perf_record_event_update *ev;
	पूर्णांक max, err;
	u16 type;

	अगर (!evsel->core.own_cpus)
		वापस 0;

	ev = cpu_map_data__alloc(evsel->core.own_cpus, &size, &type, &max);
	अगर (!ev)
		वापस -ENOMEM;

	ev->header.type = PERF_RECORD_EVENT_UPDATE;
	ev->header.size = (u16)size;
	ev->type	= PERF_EVENT_UPDATE__CPUS;
	ev->id		= evsel->core.id[0];

	cpu_map_data__synthesize((काष्ठा perf_record_cpu_map_data *)ev->data,
				 evsel->core.own_cpus, type, max);

	err = process(tool, (जोड़ perf_event *)ev, शून्य, शून्य);
	मुक्त(ev);
	वापस err;
पूर्ण

पूर्णांक perf_event__synthesize_attrs(काष्ठा perf_tool *tool, काष्ठा evlist *evlist,
				 perf_event__handler_t process)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err = 0;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		err = perf_event__synthesize_attr(tool, &evsel->core.attr, evsel->core.ids,
						  evsel->core.id, process);
		अगर (err) अणु
			pr_debug("failed to create perf header attribute\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल bool has_unit(काष्ठा evsel *evsel)
अणु
	वापस evsel->unit && *evsel->unit;
पूर्ण

अटल bool has_scale(काष्ठा evsel *evsel)
अणु
	वापस evsel->scale != 1;
पूर्ण

पूर्णांक perf_event__synthesize_extra_attr(काष्ठा perf_tool *tool, काष्ठा evlist *evsel_list,
				      perf_event__handler_t process, bool is_pipe)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err;

	/*
	 * Synthesize other events stuff not carried within
	 * attr event - unit, scale, name
	 */
	evlist__क्रम_each_entry(evsel_list, evsel) अणु
		अगर (!evsel->supported)
			जारी;

		/*
		 * Synthesize unit and scale only अगर it's defined.
		 */
		अगर (has_unit(evsel)) अणु
			err = perf_event__synthesize_event_update_unit(tool, evsel, process);
			अगर (err < 0) अणु
				pr_err("Couldn't synthesize evsel unit.\n");
				वापस err;
			पूर्ण
		पूर्ण

		अगर (has_scale(evsel)) अणु
			err = perf_event__synthesize_event_update_scale(tool, evsel, process);
			अगर (err < 0) अणु
				pr_err("Couldn't synthesize evsel evsel.\n");
				वापस err;
			पूर्ण
		पूर्ण

		अगर (evsel->core.own_cpus) अणु
			err = perf_event__synthesize_event_update_cpus(tool, evsel, process);
			अगर (err < 0) अणु
				pr_err("Couldn't synthesize evsel cpus.\n");
				वापस err;
			पूर्ण
		पूर्ण

		/*
		 * Name is needed only क्रम pipe output,
		 * perf.data carries event names.
		 */
		अगर (is_pipe) अणु
			err = perf_event__synthesize_event_update_name(tool, evsel, process);
			अगर (err < 0) अणु
				pr_err("Couldn't synthesize evsel name.\n");
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक perf_event__synthesize_attr(काष्ठा perf_tool *tool, काष्ठा perf_event_attr *attr,
				u32 ids, u64 *id, perf_event__handler_t process)
अणु
	जोड़ perf_event *ev;
	माप_प्रकार size;
	पूर्णांक err;

	size = माप(काष्ठा perf_event_attr);
	size = PERF_ALIGN(size, माप(u64));
	size += माप(काष्ठा perf_event_header);
	size += ids * माप(u64);

	ev = zalloc(size);

	अगर (ev == शून्य)
		वापस -ENOMEM;

	ev->attr.attr = *attr;
	स_नकल(ev->attr.id, id, ids * माप(u64));

	ev->attr.header.type = PERF_RECORD_HEADER_ATTR;
	ev->attr.header.size = (u16)size;

	अगर (ev->attr.header.size == size)
		err = process(tool, ev, शून्य, शून्य);
	अन्यथा
		err = -E2BIG;

	मुक्त(ev);

	वापस err;
पूर्ण

पूर्णांक perf_event__syntheमाप_प्रकारracing_data(काष्ठा perf_tool *tool, पूर्णांक fd, काष्ठा evlist *evlist,
					perf_event__handler_t process)
अणु
	जोड़ perf_event ev;
	काष्ठा tracing_data *tdata;
	sमाप_प्रकार size = 0, aligned_size = 0, padding;
	काष्ठा feat_fd ff;

	/*
	 * We are going to store the size of the data followed
	 * by the data contents. Since the fd descriptor is a pipe,
	 * we cannot seek back to store the size of the data once
	 * we know it. Instead we:
	 *
	 * - ग_लिखो the tracing data to the temp file
	 * - get/ग_लिखो the data size to pipe
	 * - ग_लिखो the tracing data from the temp file
	 *   to the pipe
	 */
	tdata = tracing_data_get(&evlist->core.entries, fd, true);
	अगर (!tdata)
		वापस -1;

	स_रखो(&ev, 0, माप(ev));

	ev.tracing_data.header.type = PERF_RECORD_HEADER_TRACING_DATA;
	size = tdata->size;
	aligned_size = PERF_ALIGN(size, माप(u64));
	padding = aligned_size - size;
	ev.tracing_data.header.size = माप(ev.tracing_data);
	ev.tracing_data.size = aligned_size;

	process(tool, &ev, शून्य, शून्य);

	/*
	 * The put function will copy all the tracing data
	 * stored in temp file to the pipe.
	 */
	tracing_data_put(tdata);

	ff = (काष्ठा feat_fd)अणु .fd = fd पूर्ण;
	अगर (ग_लिखो_padded(&ff, शून्य, 0, padding))
		वापस -1;

	वापस aligned_size;
पूर्ण

पूर्णांक perf_event__synthesize_build_id(काष्ठा perf_tool *tool, काष्ठा dso *pos, u16 misc,
				    perf_event__handler_t process, काष्ठा machine *machine)
अणु
	जोड़ perf_event ev;
	माप_प्रकार len;

	अगर (!pos->hit)
		वापस 0;

	स_रखो(&ev, 0, माप(ev));

	len = pos->दीर्घ_name_len + 1;
	len = PERF_ALIGN(len, NAME_ALIGN);
	स_नकल(&ev.build_id.build_id, pos->bid.data, माप(pos->bid.data));
	ev.build_id.header.type = PERF_RECORD_HEADER_BUILD_ID;
	ev.build_id.header.misc = misc;
	ev.build_id.pid = machine->pid;
	ev.build_id.header.size = माप(ev.build_id) + len;
	स_नकल(&ev.build_id.filename, pos->दीर्घ_name, pos->दीर्घ_name_len);

	वापस process(tool, &ev, शून्य, machine);
पूर्ण

पूर्णांक perf_event__synthesize_stat_events(काष्ठा perf_stat_config *config, काष्ठा perf_tool *tool,
				       काष्ठा evlist *evlist, perf_event__handler_t process, bool attrs)
अणु
	पूर्णांक err;

	अगर (attrs) अणु
		err = perf_event__synthesize_attrs(tool, evlist, process);
		अगर (err < 0) अणु
			pr_err("Couldn't synthesize attrs.\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = perf_event__synthesize_extra_attr(tool, evlist, process, attrs);
	err = perf_event__syntheमाप_प्रकारhपढ़ो_map2(tool, evlist->core.thपढ़ोs, process, शून्य);
	अगर (err < 0) अणु
		pr_err("Couldn't synthesize thread map.\n");
		वापस err;
	पूर्ण

	err = perf_event__synthesize_cpu_map(tool, evlist->core.cpus, process, शून्य);
	अगर (err < 0) अणु
		pr_err("Couldn't synthesize thread map.\n");
		वापस err;
	पूर्ण

	err = perf_event__synthesize_stat_config(tool, config, process, शून्य);
	अगर (err < 0) अणु
		pr_err("Couldn't synthesize config.\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

बाह्य स्थिर काष्ठा perf_header_feature_ops feat_ops[HEADER_LAST_FEATURE];

पूर्णांक perf_event__synthesize_features(काष्ठा perf_tool *tool, काष्ठा perf_session *session,
				    काष्ठा evlist *evlist, perf_event__handler_t process)
अणु
	काष्ठा perf_header *header = &session->header;
	काष्ठा perf_record_header_feature *fe;
	काष्ठा feat_fd ff;
	माप_प्रकार sz, sz_hdr;
	पूर्णांक feat, ret;

	sz_hdr = माप(fe->header);
	sz = माप(जोड़ perf_event);
	/* get a nice alignment */
	sz = PERF_ALIGN(sz, page_size);

	स_रखो(&ff, 0, माप(ff));

	ff.buf = दो_स्मृति(sz);
	अगर (!ff.buf)
		वापस -ENOMEM;

	ff.size = sz - sz_hdr;
	ff.ph = &session->header;

	क्रम_each_set_bit(feat, header->adds_features, HEADER_FEAT_BITS) अणु
		अगर (!feat_ops[feat].synthesize) अणु
			pr_debug("No record header feature for header :%d\n", feat);
			जारी;
		पूर्ण

		ff.offset = माप(*fe);

		ret = feat_ops[feat].ग_लिखो(&ff, evlist);
		अगर (ret || ff.offset <= (sमाप_प्रकार)माप(*fe)) अणु
			pr_debug("Error writing feature\n");
			जारी;
		पूर्ण
		/* ff.buf may have changed due to पुनः_स्मृति in करो_ग_लिखो() */
		fe = ff.buf;
		स_रखो(fe, 0, माप(*fe));

		fe->feat_id = feat;
		fe->header.type = PERF_RECORD_HEADER_FEATURE;
		fe->header.size = ff.offset;

		ret = process(tool, ff.buf, शून्य, शून्य);
		अगर (ret) अणु
			मुक्त(ff.buf);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Send HEADER_LAST_FEATURE mark. */
	fe = ff.buf;
	fe->feat_id     = HEADER_LAST_FEATURE;
	fe->header.type = PERF_RECORD_HEADER_FEATURE;
	fe->header.size = माप(*fe);

	ret = process(tool, ff.buf, शून्य, शून्य);

	मुक्त(ff.buf);
	वापस ret;
पूर्ण
