<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/fsuid.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mount.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/sysinfo.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <linux/android/binder.h>
#समावेश <linux/android/binderfs.h>

#समावेश "../../kselftest_harness.h"

#घोषणा DEFAULT_THREADS 4

#घोषणा PTR_TO_INT(p) ((पूर्णांक)((पूर्णांकptr_t)(p)))
#घोषणा INT_TO_PTR(u) ((व्योम *)((पूर्णांकptr_t)(u)))

#घोषणा बंद_prot_त्रुटि_सं_disarm(fd) \
	अगर (fd >= 0) अणु              \
		पूर्णांक _e_ = त्रुटि_सं;    \
		बंद(fd);          \
		त्रुटि_सं = _e_;        \
		fd = -EBADF;        \
	पूर्ण

अटल व्योम change_mountns(काष्ठा __test_metadata *_metadata)
अणु
	पूर्णांक ret;

	ret = unshare(CLONE_NEWNS);
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to unshare mount namespace",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ret = mount(शून्य, "/", शून्य, MS_REC | MS_PRIVATE, 0);
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to mount / as private",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

अटल पूर्णांक __करो_binderfs_test(काष्ठा __test_metadata *_metadata)
अणु
	पूर्णांक fd, ret, saved_त्रुटि_सं, result = 1;
	माप_प्रकार len;
	sमाप_प्रकार wret;
	काष्ठा binderfs_device device = अणु 0 पूर्ण;
	काष्ठा binder_version version = अणु 0 पूर्ण;
	अक्षर binderfs_mntpt[] = P_पंचांगpdir "/binderfs_XXXXXX",
		device_path[माप(P_पंचांगpdir "/binderfs_XXXXXX/") + BINDERFS_MAX_NAME];

	change_mountns(_metadata);

	EXPECT_NE(mkdtemp(binderfs_mntpt), शून्य) अणु
		TH_LOG("%s - Failed to create binderfs mountpoint",
			म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	ret = mount(शून्य, binderfs_mntpt, "binder", 0, 0);
	EXPECT_EQ(ret, 0) अणु
		अगर (त्रुटि_सं == ENODEV)
			SKIP(जाओ out, "binderfs missing");
		TH_LOG("%s - Failed to mount binderfs", म_त्रुटि(त्रुटि_सं));
		जाओ सूची_हटाओ;
	पूर्ण

	/* success: binderfs mounted */

	स_नकल(device.name, "my-binder", म_माप("my-binder"));

	snम_लिखो(device_path, माप(device_path), "%s/binder-control", binderfs_mntpt);
	fd = खोलो(device_path, O_RDONLY | O_CLOEXEC);
	EXPECT_GE(fd, 0) अणु
		TH_LOG("%s - Failed to open binder-control device",
			म_त्रुटि(त्रुटि_सं));
		जाओ umount;
	पूर्ण

	ret = ioctl(fd, BINDER_CTL_ADD, &device);
	saved_त्रुटि_सं = त्रुटि_सं;
	बंद(fd);
	त्रुटि_सं = saved_त्रुटि_सं;
	EXPECT_GE(ret, 0) अणु
		TH_LOG("%s - Failed to allocate new binder device",
			म_त्रुटि(त्रुटि_सं));
		जाओ umount;
	पूर्ण

	TH_LOG("Allocated new binder device with major %d, minor %d, and name %s",
		device.major, device.minor, device.name);

	/* success: binder device allocation */

	snम_लिखो(device_path, माप(device_path), "%s/my-binder", binderfs_mntpt);
	fd = खोलो(device_path, O_CLOEXEC | O_RDONLY);
	EXPECT_GE(fd, 0) अणु
		TH_LOG("%s - Failed to open my-binder device",
			म_त्रुटि(त्रुटि_सं));
		जाओ umount;
	पूर्ण

	ret = ioctl(fd, BINDER_VERSION, &version);
	saved_त्रुटि_सं = त्रुटि_सं;
	बंद(fd);
	त्रुटि_सं = saved_त्रुटि_सं;
	EXPECT_GE(ret, 0) अणु
		TH_LOG("%s - Failed to open perform BINDER_VERSION request",
			म_त्रुटि(त्रुटि_सं));
		जाओ umount;
	पूर्ण

	TH_LOG("Detected binder version: %d", version.protocol_version);

	/* success: binder transaction with binderfs binder device */

	ret = unlink(device_path);
	EXPECT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to delete binder device",
			म_त्रुटि(त्रुटि_सं));
		जाओ umount;
	पूर्ण

	/* success: binder device removal */

	snम_लिखो(device_path, माप(device_path), "%s/binder-control", binderfs_mntpt);
	ret = unlink(device_path);
	EXPECT_NE(ret, 0) अणु
		TH_LOG("Managed to delete binder-control device");
		जाओ umount;
	पूर्ण
	EXPECT_EQ(त्रुटि_सं, EPERM) अणु
		TH_LOG("%s - Failed to delete binder-control device but exited with unexpected error code",
			म_त्रुटि(त्रुटि_सं));
		जाओ umount;
	पूर्ण

	/* success: binder-control device removal failed as expected */
	result = 0;

umount:
	ret = umount2(binderfs_mntpt, MNT_DETACH);
	EXPECT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to unmount binderfs", म_त्रुटि(त्रुटि_सं));
	पूर्ण
सूची_हटाओ:
	ret = सूची_हटाओ(binderfs_mntpt);
	EXPECT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to rmdir binderfs mount", म_त्रुटि(त्रुटि_सं));
	पूर्ण
out:
	वापस result;
पूर्ण

अटल पूर्णांक रुको_क्रम_pid(pid_t pid)
अणु
	पूर्णांक status, ret;

again:
	ret = रुकोpid(pid, &status, 0);
	अगर (ret == -1) अणु
		अगर (त्रुटि_सं == EINTR)
			जाओ again;

		वापस -1;
	पूर्ण

	अगर (!WIFEXITED(status))
		वापस -1;

	वापस WEXITSTATUS(status);
पूर्ण

अटल पूर्णांक setid_userns_root(व्योम)
अणु
	अगर (setuid(0))
		वापस -1;
	अगर (setgid(0))
		वापस -1;

	setfsuid(0);
	setfsgid(0);

	वापस 0;
पूर्ण

क्रमागत idmap_type अणु
	UID_MAP,
	GID_MAP,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_noपूर्णांकr(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;
again:
	ret = पढ़ो(fd, buf, count);
	अगर (ret < 0 && त्रुटि_सं == EINTR)
		जाओ again;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_noपूर्णांकr(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;
again:
	ret = ग_लिखो(fd, buf, count);
	अगर (ret < 0 && त्रुटि_सं == EINTR)
		जाओ again;

	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_id_mapping(क्रमागत idmap_type type, pid_t pid, स्थिर अक्षर *buf,
			    माप_प्रकार buf_size)
अणु
	पूर्णांक fd;
	पूर्णांक ret;
	अक्षर path[4096];

	अगर (type == GID_MAP) अणु
		पूर्णांक setgroups_fd;

		snम_लिखो(path, माप(path), "/proc/%d/setgroups", pid);
		setgroups_fd = खोलो(path, O_WRONLY | O_CLOEXEC | O_NOFOLLOW);
		अगर (setgroups_fd < 0 && त्रुटि_सं != ENOENT)
			वापस -1;

		अगर (setgroups_fd >= 0) अणु
			ret = ग_लिखो_noपूर्णांकr(setgroups_fd, "deny", माप("deny") - 1);
			बंद_prot_त्रुटि_सं_disarm(setgroups_fd);
			अगर (ret != माप("deny") - 1)
				वापस -1;
		पूर्ण
	पूर्ण

	चयन (type) अणु
	हाल UID_MAP:
		ret = snम_लिखो(path, माप(path), "/proc/%d/uid_map", pid);
		अवरोध;
	हाल GID_MAP:
		ret = snम_लिखो(path, माप(path), "/proc/%d/gid_map", pid);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	अगर (ret < 0 || ret >= माप(path))
		वापस -E2BIG;

	fd = खोलो(path, O_WRONLY | O_CLOEXEC | O_NOFOLLOW);
	अगर (fd < 0)
		वापस -1;

	ret = ग_लिखो_noपूर्णांकr(fd, buf, buf_size);
	बंद_prot_त्रुटि_सं_disarm(fd);
	अगर (ret != buf_size)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम change_userns(काष्ठा __test_metadata *_metadata, पूर्णांक syncfds[2])
अणु
	पूर्णांक ret;
	अक्षर buf;

	बंद_prot_त्रुटि_सं_disarm(syncfds[1]);

	ret = unshare(CLONE_NEWUSER);
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to unshare user namespace",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ret = ग_लिखो_noपूर्णांकr(syncfds[0], "1", 1);
	ASSERT_EQ(ret, 1) अणु
		TH_LOG("write_nointr() failed");
	पूर्ण

	ret = पढ़ो_noपूर्णांकr(syncfds[0], &buf, 1);
	ASSERT_EQ(ret, 1) अणु
		TH_LOG("read_nointr() failed");
	पूर्ण

	बंद_prot_त्रुटि_सं_disarm(syncfds[0]);

	ASSERT_EQ(setid_userns_root(), 0) अणु
		TH_LOG("setid_userns_root() failed");
	पूर्ण
पूर्ण

अटल व्योम change_idmaps(काष्ठा __test_metadata *_metadata, पूर्णांक syncfds[2], pid_t pid)
अणु
	पूर्णांक ret;
	अक्षर buf;
	अक्षर id_map[4096];

	बंद_prot_त्रुटि_सं_disarm(syncfds[0]);

	ret = पढ़ो_noपूर्णांकr(syncfds[1], &buf, 1);
	ASSERT_EQ(ret, 1) अणु
		TH_LOG("read_nointr() failed");
	पूर्ण

	snम_लिखो(id_map, माप(id_map), "0 %d 1\n", getuid());
	ret = ग_लिखो_id_mapping(UID_MAP, pid, id_map, म_माप(id_map));
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("write_id_mapping(UID_MAP) failed");
	पूर्ण

	snम_लिखो(id_map, माप(id_map), "0 %d 1\n", getgid());
	ret = ग_लिखो_id_mapping(GID_MAP, pid, id_map, म_माप(id_map));
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("write_id_mapping(GID_MAP) failed");
	पूर्ण

	ret = ग_लिखो_noपूर्णांकr(syncfds[1], "1", 1);
	ASSERT_EQ(ret, 1) अणु
		TH_LOG("write_nointr() failed");
	पूर्ण

	बंद_prot_त्रुटि_सं_disarm(syncfds[1]);
पूर्ण

काष्ठा __test_metadata *_thपढ़ो_metadata;
अटल व्योम *binder_version_thपढ़ो(व्योम *data)
अणु
	काष्ठा __test_metadata *_metadata = _thपढ़ो_metadata;
	पूर्णांक fd = PTR_TO_INT(data);
	काष्ठा binder_version version = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = ioctl(fd, BINDER_VERSION, &version);
	अगर (ret < 0)
		TH_LOG("%s - Failed to open perform BINDER_VERSION request\n",
			म_त्रुटि(त्रुटि_सं));

	pthपढ़ो_निकास(data);
पूर्ण

/*
 * Regression test:
 * 2669b8b0c798 ("binder: prevent UAF for binderfs devices")
 * f0fe2c0f050d ("binder: prevent UAF for binderfs devices II")
 * 211b64e4b5b6 ("binderfs: use refcount for binder control devices too")
 */
TEST(binderfs_stress)
अणु
	पूर्णांक fds[1000];
	पूर्णांक syncfds[2];
	pid_t pid;
	पूर्णांक fd, ret;
	माप_प्रकार len;
	काष्ठा binderfs_device device = अणु 0 पूर्ण;
	अक्षर binderfs_mntpt[] = P_पंचांगpdir "/binderfs_XXXXXX",
		device_path[माप(P_पंचांगpdir "/binderfs_XXXXXX/") + BINDERFS_MAX_NAME];

	ret = socketpair(PF_LOCAL, SOCK_STREAM | SOCK_CLOEXEC, 0, syncfds);
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to create socket pair", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	pid = विभाजन();
	ASSERT_GE(pid, 0) अणु
		TH_LOG("%s - Failed to fork", म_त्रुटि(त्रुटि_सं));
		बंद_prot_त्रुटि_सं_disarm(syncfds[0]);
		बंद_prot_त्रुटि_सं_disarm(syncfds[1]);
	पूर्ण

	अगर (pid == 0) अणु
		पूर्णांक i, j, k, nthपढ़ोs;
		pthपढ़ो_attr_t attr;
		pthपढ़ो_t thपढ़ोs[DEFAULT_THREADS];
		change_userns(_metadata, syncfds);
		change_mountns(_metadata);

		ASSERT_NE(mkdtemp(binderfs_mntpt), शून्य) अणु
			TH_LOG("%s - Failed to create binderfs mountpoint",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण

		ret = mount(शून्य, binderfs_mntpt, "binder", 0, 0);
		ASSERT_EQ(ret, 0) अणु
			TH_LOG("%s - Failed to mount binderfs", म_त्रुटि(त्रुटि_सं));
		पूर्ण

		क्रम (पूर्णांक i = 0; i < ARRAY_SIZE(fds); i++) अणु

			snम_लिखो(device_path, माप(device_path),
				 "%s/binder-control", binderfs_mntpt);
			fd = खोलो(device_path, O_RDONLY | O_CLOEXEC);
			ASSERT_GE(fd, 0) अणु
				TH_LOG("%s - Failed to open binder-control device",
					म_त्रुटि(त्रुटि_सं));
			पूर्ण

			स_रखो(&device, 0, माप(device));
			snम_लिखो(device.name, माप(device.name), "%d", i);
			ret = ioctl(fd, BINDER_CTL_ADD, &device);
			बंद_prot_त्रुटि_सं_disarm(fd);
			ASSERT_EQ(ret, 0) अणु
				TH_LOG("%s - Failed to allocate new binder device",
					म_त्रुटि(त्रुटि_सं));
			पूर्ण

			snम_लिखो(device_path, माप(device_path), "%s/%d",
				 binderfs_mntpt, i);
			fds[i] = खोलो(device_path, O_RDONLY | O_CLOEXEC);
			ASSERT_GE(fds[i], 0) अणु
				TH_LOG("%s - Failed to open binder device", म_त्रुटि(त्रुटि_सं));
			पूर्ण
		पूर्ण

		ret = umount2(binderfs_mntpt, MNT_DETACH);
		ASSERT_EQ(ret, 0) अणु
			TH_LOG("%s - Failed to unmount binderfs", म_त्रुटि(त्रुटि_सं));
			सूची_हटाओ(binderfs_mntpt);
		पूर्ण

		nthपढ़ोs = get_nprocs_conf();
		अगर (nthपढ़ोs > DEFAULT_THREADS)
			nthपढ़ोs = DEFAULT_THREADS;

		_thपढ़ो_metadata = _metadata;
		pthपढ़ो_attr_init(&attr);
		क्रम (k = 0; k < ARRAY_SIZE(fds); k++) अणु
			क्रम (i = 0; i < nthपढ़ोs; i++) अणु
				ret = pthपढ़ो_create(&thपढ़ोs[i], &attr, binder_version_thपढ़ो, INT_TO_PTR(fds[k]));
				अगर (ret) अणु
					TH_LOG("%s - Failed to create thread %d",
						म_त्रुटि(त्रुटि_सं), i);
					अवरोध;
				पूर्ण
			पूर्ण

			क्रम (j = 0; j < i; j++) अणु
				व्योम *fdptr = शून्य;

				ret = pthपढ़ो_join(thपढ़ोs[j], &fdptr);
				अगर (ret)
					TH_LOG("%s - Failed to join thread %d for fd %d",
						म_त्रुटि(त्रुटि_सं), j, PTR_TO_INT(fdptr));
			पूर्ण
		पूर्ण
		pthपढ़ो_attr_destroy(&attr);

		क्रम (k = 0; k < ARRAY_SIZE(fds); k++)
			बंद(fds[k]);

		निकास(निकास_सफल);
	पूर्ण

	change_idmaps(_metadata, syncfds, pid);

	ret = रुको_क्रम_pid(pid);
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("wait_for_pid() failed");
	पूर्ण
पूर्ण

TEST(binderfs_test_privileged)
अणु
	अगर (geteuid() != 0)
		SKIP(वापस, "Tests are not run as root. Skipping privileged tests");

	अगर (__करो_binderfs_test(_metadata))
		SKIP(वापस, "The Android binderfs filesystem is not available");
पूर्ण

TEST(binderfs_test_unprivileged)
अणु
	पूर्णांक ret;
	पूर्णांक syncfds[2];
	pid_t pid;

	ret = socketpair(PF_LOCAL, SOCK_STREAM | SOCK_CLOEXEC, 0, syncfds);
	ASSERT_EQ(ret, 0) अणु
		TH_LOG("%s - Failed to create socket pair", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	pid = विभाजन();
	ASSERT_GE(pid, 0) अणु
		बंद_prot_त्रुटि_सं_disarm(syncfds[0]);
		बंद_prot_त्रुटि_सं_disarm(syncfds[1]);
		TH_LOG("%s - Failed to fork", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (pid == 0) अणु
		change_userns(_metadata, syncfds);
		अगर (__करो_binderfs_test(_metadata))
			निकास(2);
		निकास(निकास_सफल);
	पूर्ण

	change_idmaps(_metadata, syncfds, pid);

	ret = रुको_क्रम_pid(pid);
	अगर (ret) अणु
		अगर (ret == 2)
			SKIP(वापस, "The Android binderfs filesystem is not available");
		ASSERT_EQ(ret, 0) अणु
			TH_LOG("wait_for_pid() failed");
		पूर्ण
	पूर्ण
पूर्ण

TEST_HARNESS_MAIN
