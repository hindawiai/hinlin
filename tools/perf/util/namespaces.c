<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2017 Hari Bathini, IBM Corporation
 */

#समावेश "namespaces.h"
#समावेश "event.h"
#समावेश "get_current_dir_name.h"
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <sched.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <यंत्र/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>

अटल स्थिर अक्षर *perf_ns__names[] = अणु
	[NET_NS_INDEX]		= "net",
	[UTS_NS_INDEX]		= "uts",
	[IPC_NS_INDEX]		= "ipc",
	[PID_NS_INDEX]		= "pid",
	[USER_NS_INDEX]		= "user",
	[MNT_NS_INDEX]		= "mnt",
	[CGROUP_NS_INDEX]	= "cgroup",
पूर्ण;

स्थिर अक्षर *perf_ns__name(अचिन्हित पूर्णांक id)
अणु
	अगर (id >= ARRAY_SIZE(perf_ns__names))
		वापस "UNKNOWN";
	वापस perf_ns__names[id];
पूर्ण

काष्ठा namespaces *namespaces__new(काष्ठा perf_record_namespaces *event)
अणु
	काष्ठा namespaces *namespaces;
	u64 link_info_size = ((event ? event->nr_namespaces : NR_NAMESPACES) *
			      माप(काष्ठा perf_ns_link_info));

	namespaces = zalloc(माप(काष्ठा namespaces) + link_info_size);
	अगर (!namespaces)
		वापस शून्य;

	namespaces->end_समय = -1;

	अगर (event)
		स_नकल(namespaces->link_info, event->link_info, link_info_size);

	वापस namespaces;
पूर्ण

व्योम namespaces__मुक्त(काष्ठा namespaces *namespaces)
अणु
	मुक्त(namespaces);
पूर्ण

पूर्णांक nsinfo__init(काष्ठा nsinfo *nsi)
अणु
	अक्षर oldns[PATH_MAX];
	अक्षर spath[PATH_MAX];
	अक्षर *newns = शून्य;
	अक्षर *statln = शून्य;
	अक्षर *nspid;
	काष्ठा stat old_stat;
	काष्ठा stat new_stat;
	खाता *f = शून्य;
	माप_प्रकार linesz = 0;
	पूर्णांक rv = -1;

	अगर (snम_लिखो(oldns, PATH_MAX, "/proc/self/ns/mnt") >= PATH_MAX)
		वापस rv;

	अगर (aप्र_लिखो(&newns, "/proc/%d/ns/mnt", nsi->pid) == -1)
		वापस rv;

	अगर (stat(oldns, &old_stat) < 0)
		जाओ out;

	अगर (stat(newns, &new_stat) < 0)
		जाओ out;

	/* Check अगर the mount namespaces dअगरfer, अगर so then indicate that we
	 * want to चयन as part of looking up dso/map data.
	 */
	अगर (old_stat.st_ino != new_stat.st_ino) अणु
		nsi->need_setns = true;
		nsi->mntns_path = newns;
		newns = शून्य;
	पूर्ण

	/* If we're dealing with a process that is in a dअगरferent PID namespace,
	 * attempt to work out the innermost tgid क्रम the process.
	 */
	अगर (snम_लिखो(spath, PATH_MAX, "/proc/%d/status", nsi->pid) >= PATH_MAX)
		जाओ out;

	f = ख_खोलो(spath, "r");
	अगर (f == शून्य)
		जाओ out;

	जबतक (getline(&statln, &linesz, f) != -1) अणु
		/* Use tgid अगर CONFIG_PID_NS is not defined. */
		अगर (म_माला(statln, "Tgid:") != शून्य) अणु
			nsi->tgid = (pid_t)म_से_दीर्घ(म_खोजप(statln, '\t'),
						     शून्य, 10);
			nsi->nstgid = nsi->tgid;
		पूर्ण

		अगर (म_माला(statln, "NStgid:") != शून्य) अणु
			nspid = म_खोजप(statln, '\t');
			nsi->nstgid = (pid_t)म_से_दीर्घ(nspid, शून्य, 10);
			/* If innermost tgid is not the first, process is in a dअगरferent
			 * PID namespace.
			 */
			nsi->in_pidns = (statln + माप("NStgid:") - 1) != nspid;
			अवरोध;
		पूर्ण
	पूर्ण
	rv = 0;

out:
	अगर (f != शून्य)
		(व्योम) ख_बंद(f);
	मुक्त(statln);
	मुक्त(newns);
	वापस rv;
पूर्ण

काष्ठा nsinfo *nsinfo__new(pid_t pid)
अणु
	काष्ठा nsinfo *nsi;

	अगर (pid == 0)
		वापस शून्य;

	nsi = सुस्मृति(1, माप(*nsi));
	अगर (nsi != शून्य) अणु
		nsi->pid = pid;
		nsi->tgid = pid;
		nsi->nstgid = pid;
		nsi->need_setns = false;
		nsi->in_pidns = false;
		/* Init may fail अगर the process निकासs जबतक we're trying to look
		 * at its proc inक्रमmation.  In that हाल, save the pid but
		 * करोn't try to enter the namespace.
		 */
		अगर (nsinfo__init(nsi) == -1)
			nsi->need_setns = false;

		refcount_set(&nsi->refcnt, 1);
	पूर्ण

	वापस nsi;
पूर्ण

काष्ठा nsinfo *nsinfo__copy(काष्ठा nsinfo *nsi)
अणु
	काष्ठा nsinfo *nnsi;

	अगर (nsi == शून्य)
		वापस शून्य;

	nnsi = सुस्मृति(1, माप(*nnsi));
	अगर (nnsi != शून्य) अणु
		nnsi->pid = nsi->pid;
		nnsi->tgid = nsi->tgid;
		nnsi->nstgid = nsi->nstgid;
		nnsi->need_setns = nsi->need_setns;
		nnsi->in_pidns = nsi->in_pidns;
		अगर (nsi->mntns_path) अणु
			nnsi->mntns_path = strdup(nsi->mntns_path);
			अगर (!nnsi->mntns_path) अणु
				मुक्त(nnsi);
				वापस शून्य;
			पूर्ण
		पूर्ण
		refcount_set(&nnsi->refcnt, 1);
	पूर्ण

	वापस nnsi;
पूर्ण

व्योम nsinfo__delete(काष्ठा nsinfo *nsi)
अणु
	zमुक्त(&nsi->mntns_path);
	मुक्त(nsi);
पूर्ण

काष्ठा nsinfo *nsinfo__get(काष्ठा nsinfo *nsi)
अणु
	अगर (nsi)
		refcount_inc(&nsi->refcnt);
	वापस nsi;
पूर्ण

व्योम nsinfo__put(काष्ठा nsinfo *nsi)
अणु
	अगर (nsi && refcount_dec_and_test(&nsi->refcnt))
		nsinfo__delete(nsi);
पूर्ण

व्योम nsinfo__mountns_enter(काष्ठा nsinfo *nsi,
				  काष्ठा nscookie *nc)
अणु
	अक्षर curpath[PATH_MAX];
	पूर्णांक oldns = -1;
	पूर्णांक newns = -1;
	अक्षर *oldcwd = शून्य;

	अगर (nc == शून्य)
		वापस;

	nc->oldns = -1;
	nc->newns = -1;

	अगर (!nsi || !nsi->need_setns)
		वापस;

	अगर (snम_लिखो(curpath, PATH_MAX, "/proc/self/ns/mnt") >= PATH_MAX)
		वापस;

	oldcwd = get_current_dir_name();
	अगर (!oldcwd)
		वापस;

	oldns = खोलो(curpath, O_RDONLY);
	अगर (oldns < 0)
		जाओ errout;

	newns = खोलो(nsi->mntns_path, O_RDONLY);
	अगर (newns < 0)
		जाओ errout;

	अगर (setns(newns, CLONE_NEWNS) < 0)
		जाओ errout;

	nc->oldcwd = oldcwd;
	nc->oldns = oldns;
	nc->newns = newns;
	वापस;

errout:
	मुक्त(oldcwd);
	अगर (oldns > -1)
		बंद(oldns);
	अगर (newns > -1)
		बंद(newns);
पूर्ण

व्योम nsinfo__mountns_निकास(काष्ठा nscookie *nc)
अणु
	अगर (nc == शून्य || nc->oldns == -1 || nc->newns == -1 || !nc->oldcwd)
		वापस;

	setns(nc->oldns, CLONE_NEWNS);

	अगर (nc->oldcwd) अणु
		WARN_ON_ONCE(स_बदलो(nc->oldcwd));
		zमुक्त(&nc->oldcwd);
	पूर्ण

	अगर (nc->oldns > -1) अणु
		बंद(nc->oldns);
		nc->oldns = -1;
	पूर्ण

	अगर (nc->newns > -1) अणु
		बंद(nc->newns);
		nc->newns = -1;
	पूर्ण
पूर्ण

अक्षर *nsinfo__realpath(स्थिर अक्षर *path, काष्ठा nsinfo *nsi)
अणु
	अक्षर *rpath;
	काष्ठा nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	rpath = realpath(path, शून्य);
	nsinfo__mountns_निकास(&nsc);

	वापस rpath;
पूर्ण

पूर्णांक nsinfo__stat(स्थिर अक्षर *filename, काष्ठा stat *st, काष्ठा nsinfo *nsi)
अणु
	पूर्णांक ret;
	काष्ठा nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	ret = stat(filename, st);
	nsinfo__mountns_निकास(&nsc);

	वापस ret;
पूर्ण
