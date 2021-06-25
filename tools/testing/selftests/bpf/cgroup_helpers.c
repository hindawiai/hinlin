<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <sys/mount.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <linux/सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/sched.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <ftw.h>


#समावेश "cgroup_helpers.h"

/*
 * To aव्योम relying on the प्रणाली setup, when setup_cgroup_env is called
 * we create a new mount namespace, and cgroup namespace. The cgroup2
 * root is mounted at CGROUP_MOUNT_PATH
 *
 * Unक्रमtunately, most people करोn't have cgroupv2 enabled at this poपूर्णांक in समय.
 * It's easier to create our own mount namespace and manage it ourselves.
 *
 * We assume /mnt exists.
 */

#घोषणा WALK_FD_LIMIT			16
#घोषणा CGROUP_MOUNT_PATH		"/mnt"
#घोषणा CGROUP_WORK_सूची			"/cgroup-test-work-dir"
#घोषणा क्रमmat_cgroup_path(buf, path) \
	snम_लिखो(buf, माप(buf), "%s%s%s", CGROUP_MOUNT_PATH, \
		 CGROUP_WORK_सूची, path)

/**
 * enable_all_controllers() - Enable all available cgroup v2 controllers
 *
 * Enable all available cgroup v2 controllers in order to increase
 * the code coverage.
 *
 * If successful, 0 is वापसed.
 */
अटल पूर्णांक enable_all_controllers(अक्षर *cgroup_path)
अणु
	अक्षर path[PATH_MAX + 1];
	अक्षर buf[PATH_MAX];
	अक्षर *c, *c2;
	पूर्णांक fd, cfd;
	sमाप_प्रकार len;

	snम_लिखो(path, माप(path), "%s/cgroup.controllers", cgroup_path);
	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0) अणु
		log_err("Opening cgroup.controllers: %s", path);
		वापस 1;
	पूर्ण

	len = पढ़ो(fd, buf, माप(buf) - 1);
	अगर (len < 0) अणु
		बंद(fd);
		log_err("Reading cgroup.controllers: %s", path);
		वापस 1;
	पूर्ण
	buf[len] = 0;
	बंद(fd);

	/* No controllers available? We're probably on cgroup v1. */
	अगर (len == 0)
		वापस 0;

	snम_लिखो(path, माप(path), "%s/cgroup.subtree_control", cgroup_path);
	cfd = खोलो(path, O_RDWR);
	अगर (cfd < 0) अणु
		log_err("Opening cgroup.subtree_control: %s", path);
		वापस 1;
	पूर्ण

	क्रम (c = म_मोहर_r(buf, " ", &c2); c; c = म_मोहर_r(शून्य, " ", &c2)) अणु
		अगर (dम_लिखो(cfd, "+%s\n", c) <= 0) अणु
			log_err("Enabling controller %s: %s", c, path);
			बंद(cfd);
			वापस 1;
		पूर्ण
	पूर्ण
	बंद(cfd);
	वापस 0;
पूर्ण

/**
 * setup_cgroup_environment() - Setup the cgroup environment
 *
 * After calling this function, cleanup_cgroup_environment should be called
 * once testing is complete.
 *
 * This function will prपूर्णांक an error to मानक_त्रुटि and वापस 1 अगर it is unable
 * to setup the cgroup environment. If setup is successful, 0 is वापसed.
 */
पूर्णांक setup_cgroup_environment(व्योम)
अणु
	अक्षर cgroup_workdir[PATH_MAX - 24];

	क्रमmat_cgroup_path(cgroup_workdir, "");

	अगर (unshare(CLONE_NEWNS)) अणु
		log_err("unshare");
		वापस 1;
	पूर्ण

	अगर (mount("none", "/", शून्य, MS_REC | MS_PRIVATE, शून्य)) अणु
		log_err("mount fakeroot");
		वापस 1;
	पूर्ण

	अगर (mount("none", CGROUP_MOUNT_PATH, "cgroup2", 0, शून्य) && त्रुटि_सं != EBUSY) अणु
		log_err("mount cgroup2");
		वापस 1;
	पूर्ण

	/* Cleanup existing failed runs, now that the environment is setup */
	cleanup_cgroup_environment();

	अगर (सूची_गढ़ो(cgroup_workdir, 0777) && त्रुटि_सं != EEXIST) अणु
		log_err("mkdir cgroup work dir");
		वापस 1;
	पूर्ण

	अगर (enable_all_controllers(cgroup_workdir))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक nftwfunc(स्थिर अक्षर *filename, स्थिर काष्ठा stat *statptr,
		    पूर्णांक fileflags, काष्ठा FTW *pfwt)
अणु
	अगर ((fileflags & FTW_D) && सूची_हटाओ(filename))
		log_err("Removing cgroup: %s", filename);
	वापस 0;
पूर्ण


अटल पूर्णांक join_cgroup_from_top(अक्षर *cgroup_path)
अणु
	अक्षर cgroup_procs_path[PATH_MAX + 1];
	pid_t pid = getpid();
	पूर्णांक fd, rc = 0;

	snम_लिखो(cgroup_procs_path, माप(cgroup_procs_path),
		 "%s/cgroup.procs", cgroup_path);

	fd = खोलो(cgroup_procs_path, O_WRONLY);
	अगर (fd < 0) अणु
		log_err("Opening Cgroup Procs: %s", cgroup_procs_path);
		वापस 1;
	पूर्ण

	अगर (dम_लिखो(fd, "%d\n", pid) < 0) अणु
		log_err("Joining Cgroup");
		rc = 1;
	पूर्ण

	बंद(fd);
	वापस rc;
पूर्ण

/**
 * join_cgroup() - Join a cgroup
 * @path: The cgroup path, relative to the workdir, to join
 *
 * This function expects a cgroup to alपढ़ोy be created, relative to the cgroup
 * work dir, and it joins it. For example, passing "/my-cgroup" as the path
 * would actually put the calling process पूर्णांकo the cgroup
 * "/cgroup-test-work-dir/my-cgroup"
 *
 * On success, it वापसs 0, otherwise on failure it वापसs 1.
 */
पूर्णांक join_cgroup(स्थिर अक्षर *path)
अणु
	अक्षर cgroup_path[PATH_MAX + 1];

	क्रमmat_cgroup_path(cgroup_path, path);
	वापस join_cgroup_from_top(cgroup_path);
पूर्ण

/**
 * cleanup_cgroup_environment() - Cleanup Cgroup Testing Environment
 *
 * This is an idempotent function to delete all temporary cgroups that
 * have been created during the test, including the cgroup testing work
 * directory.
 *
 * At call समय, it moves the calling process to the root cgroup, and then
 * runs the deletion process. It is idempotent, and should not fail, unless
 * a process is lingering.
 *
 * On failure, it will prपूर्णांक an error to मानक_त्रुटि, and try to जारी.
 */
व्योम cleanup_cgroup_environment(व्योम)
अणु
	अक्षर cgroup_workdir[PATH_MAX + 1];

	क्रमmat_cgroup_path(cgroup_workdir, "");
	join_cgroup_from_top(CGROUP_MOUNT_PATH);
	nftw(cgroup_workdir, nftwfunc, WALK_FD_LIMIT, FTW_DEPTH | FTW_MOUNT);
पूर्ण

/**
 * create_and_get_cgroup() - Create a cgroup, relative to workdir, and get the FD
 * @path: The cgroup path, relative to the workdir, to join
 *
 * This function creates a cgroup under the top level workdir and वापसs the
 * file descriptor. It is idempotent.
 *
 * On success, it वापसs the file descriptor. On failure it वापसs -1.
 * If there is a failure, it prपूर्णांकs the error to मानक_त्रुटि.
 */
पूर्णांक create_and_get_cgroup(स्थिर अक्षर *path)
अणु
	अक्षर cgroup_path[PATH_MAX + 1];
	पूर्णांक fd;

	क्रमmat_cgroup_path(cgroup_path, path);
	अगर (सूची_गढ़ो(cgroup_path, 0777) && त्रुटि_सं != EEXIST) अणु
		log_err("mkdiring cgroup %s .. %s", path, cgroup_path);
		वापस -1;
	पूर्ण

	fd = खोलो(cgroup_path, O_RDONLY);
	अगर (fd < 0) अणु
		log_err("Opening Cgroup");
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

/**
 * get_cgroup_id() - Get cgroup id क्रम a particular cgroup path
 * @path: The cgroup path, relative to the workdir, to join
 *
 * On success, it वापसs the cgroup id. On failure it वापसs 0,
 * which is an invalid cgroup id.
 * If there is a failure, it prपूर्णांकs the error to मानक_त्रुटि.
 */
अचिन्हित दीर्घ दीर्घ get_cgroup_id(स्थिर अक्षर *path)
अणु
	पूर्णांक dirfd, err, flags, mount_id, fhsize;
	जोड़ अणु
		अचिन्हित दीर्घ दीर्घ cgid;
		अचिन्हित अक्षर raw_bytes[8];
	पूर्ण id;
	अक्षर cgroup_workdir[PATH_MAX + 1];
	काष्ठा file_handle *fhp, *fhp2;
	अचिन्हित दीर्घ दीर्घ ret = 0;

	क्रमmat_cgroup_path(cgroup_workdir, path);

	dirfd = AT_FDCWD;
	flags = 0;
	fhsize = माप(*fhp);
	fhp = सुस्मृति(1, fhsize);
	अगर (!fhp) अणु
		log_err("calloc");
		वापस 0;
	पूर्ण
	err = name_to_handle_at(dirfd, cgroup_workdir, fhp, &mount_id, flags);
	अगर (err >= 0 || fhp->handle_bytes != 8) अणु
		log_err("name_to_handle_at");
		जाओ मुक्त_mem;
	पूर्ण

	fhsize = माप(काष्ठा file_handle) + fhp->handle_bytes;
	fhp2 = पुनः_स्मृति(fhp, fhsize);
	अगर (!fhp2) अणु
		log_err("realloc");
		जाओ मुक्त_mem;
	पूर्ण
	err = name_to_handle_at(dirfd, cgroup_workdir, fhp2, &mount_id, flags);
	fhp = fhp2;
	अगर (err < 0) अणु
		log_err("name_to_handle_at");
		जाओ मुक्त_mem;
	पूर्ण

	स_नकल(id.raw_bytes, fhp->f_handle, 8);
	ret = id.cgid;

मुक्त_mem:
	मुक्त(fhp);
	वापस ret;
पूर्ण

पूर्णांक cgroup_setup_and_join(स्थिर अक्षर *path) अणु
	पूर्णांक cg_fd;

	अगर (setup_cgroup_environment()) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to setup cgroup environment\n");
		वापस -EINVAL;
	पूर्ण

	cg_fd = create_and_get_cgroup(path);
	अगर (cg_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to create test cgroup\n");
		cleanup_cgroup_environment();
		वापस cg_fd;
	पूर्ण

	अगर (join_cgroup(path)) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to join cgroup\n");
		cleanup_cgroup_environment();
		वापस -EINVAL;
	पूर्ण
	वापस cg_fd;
पूर्ण
