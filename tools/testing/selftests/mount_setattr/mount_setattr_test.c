<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <pthपढ़ो.h>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/mount.h>
#समावेश <sys/रुको.h>
#समावेश <sys/vfs.h>
#समावेश <sys/statvfs.h>
#समावेश <sys/sysinfo.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <grp.h>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>

#समावेश "../kselftest_harness.h"

#अगर_अघोषित CLONE_NEWNS
#घोषणा CLONE_NEWNS 0x00020000
#पूर्ण_अगर

#अगर_अघोषित CLONE_NEWUSER
#घोषणा CLONE_NEWUSER 0x10000000
#पूर्ण_अगर

#अगर_अघोषित MS_REC
#घोषणा MS_REC 16384
#पूर्ण_अगर

#अगर_अघोषित MS_RELATIME
#घोषणा MS_RELATIME (1 << 21)
#पूर्ण_अगर

#अगर_अघोषित MS_STRICTATIME
#घोषणा MS_STRICTATIME (1 << 24)
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_RDONLY
#घोषणा MOUNT_ATTR_RDONLY 0x00000001
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_NOSUID
#घोषणा MOUNT_ATTR_NOSUID 0x00000002
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_NOEXEC
#घोषणा MOUNT_ATTR_NOEXEC 0x00000008
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_NOसूचीATIME
#घोषणा MOUNT_ATTR_NOसूचीATIME 0x00000080
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR__ATIME
#घोषणा MOUNT_ATTR__ATIME 0x00000070
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_RELATIME
#घोषणा MOUNT_ATTR_RELATIME 0x00000000
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_NOATIME
#घोषणा MOUNT_ATTR_NOATIME 0x00000010
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_STRICTATIME
#घोषणा MOUNT_ATTR_STRICTATIME 0x00000020
#पूर्ण_अगर

#अगर_अघोषित AT_RECURSIVE
#घोषणा AT_RECURSIVE 0x8000
#पूर्ण_अगर

#अगर_अघोषित MS_SHARED
#घोषणा MS_SHARED (1 << 20)
#पूर्ण_अगर

#घोषणा DEFAULT_THREADS 4
#घोषणा ptr_to_पूर्णांक(p) ((पूर्णांक)((पूर्णांकptr_t)(p)))
#घोषणा पूर्णांक_to_ptr(u) ((व्योम *)((पूर्णांकptr_t)(u)))

#अगर_अघोषित __NR_mount_setattr
	#अगर defined __alpha__
		#घोषणा __NR_mount_setattr 552
	#या_अगर defined _MIPS_SIM
		#अगर _MIPS_SIM == _MIPS_SIM_ABI32	/* o32 */
			#घोषणा __NR_mount_setattr (442 + 4000)
		#पूर्ण_अगर
		#अगर _MIPS_SIM == _MIPS_SIM_NABI32	/* n32 */
			#घोषणा __NR_mount_setattr (442 + 6000)
		#पूर्ण_अगर
		#अगर _MIPS_SIM == _MIPS_SIM_ABI64	/* n64 */
			#घोषणा __NR_mount_setattr (442 + 5000)
		#पूर्ण_अगर
	#या_अगर defined __ia64__
		#घोषणा __NR_mount_setattr (442 + 1024)
	#अन्यथा
		#घोषणा __NR_mount_setattr 442
	#पूर्ण_अगर

काष्ठा mount_attr अणु
	__u64 attr_set;
	__u64 attr_clr;
	__u64 propagation;
	__u64 userns_fd;
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित __NR_खोलो_tree
	#अगर defined __alpha__
		#घोषणा __NR_खोलो_tree 538
	#या_अगर defined _MIPS_SIM
		#अगर _MIPS_SIM == _MIPS_SIM_ABI32	/* o32 */
			#घोषणा __NR_खोलो_tree 4428
		#पूर्ण_अगर
		#अगर _MIPS_SIM == _MIPS_SIM_NABI32	/* n32 */
			#घोषणा __NR_खोलो_tree 6428
		#पूर्ण_अगर
		#अगर _MIPS_SIM == _MIPS_SIM_ABI64	/* n64 */
			#घोषणा __NR_खोलो_tree 5428
		#पूर्ण_अगर
	#या_अगर defined __ia64__
		#घोषणा __NR_खोलो_tree (428 + 1024)
	#अन्यथा
		#घोषणा __NR_खोलो_tree 428
	#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित MOUNT_ATTR_IDMAP
#घोषणा MOUNT_ATTR_IDMAP 0x00100000
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sys_mount_setattr(पूर्णांक dfd, स्थिर अक्षर *path, अचिन्हित पूर्णांक flags,
				    काष्ठा mount_attr *attr, माप_प्रकार size)
अणु
	वापस syscall(__NR_mount_setattr, dfd, path, flags, attr, size);
पूर्ण

#अगर_अघोषित OPEN_TREE_CLONE
#घोषणा OPEN_TREE_CLONE 1
#पूर्ण_अगर

#अगर_अघोषित OPEN_TREE_CLOEXEC
#घोषणा OPEN_TREE_CLOEXEC O_CLOEXEC
#पूर्ण_अगर

#अगर_अघोषित AT_RECURSIVE
#घोषणा AT_RECURSIVE 0x8000 /* Apply to the entire subtree */
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sys_खोलो_tree(पूर्णांक dfd, स्थिर अक्षर *filename, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_खोलो_tree, dfd, filename, flags);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_noपूर्णांकr(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	करो अणु
		ret = ग_लिखो(fd, buf, count);
	पूर्ण जबतक (ret < 0 && त्रुटि_सं == EINTR);

	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_file(स्थिर अक्षर *path, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	पूर्णांक fd;
	sमाप_प्रकार ret;

	fd = खोलो(path, O_WRONLY | O_CLOEXEC | O_NOCTTY | O_NOFOLLOW);
	अगर (fd < 0)
		वापस -1;

	ret = ग_लिखो_noपूर्णांकr(fd, buf, count);
	बंद(fd);
	अगर (ret < 0 || (माप_प्रकार)ret != count)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक create_and_enter_userns(व्योम)
अणु
	uid_t uid;
	gid_t gid;
	अक्षर map[100];

	uid = getuid();
	gid = getgid();

	अगर (unshare(CLONE_NEWUSER))
		वापस -1;

	अगर (ग_लिखो_file("/proc/self/setgroups", "deny", माप("deny") - 1) &&
	    त्रुटि_सं != ENOENT)
		वापस -1;

	snम_लिखो(map, माप(map), "0 %d 1", uid);
	अगर (ग_लिखो_file("/proc/self/uid_map", map, म_माप(map)))
		वापस -1;


	snम_लिखो(map, माप(map), "0 %d 1", gid);
	अगर (ग_लिखो_file("/proc/self/gid_map", map, म_माप(map)))
		वापस -1;

	अगर (setgid(0))
		वापस -1;

	अगर (setuid(0))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक prepare_unpriv_mountns(व्योम)
अणु
	अगर (create_and_enter_userns())
		वापस -1;

	अगर (unshare(CLONE_NEWNS))
		वापस -1;

	अगर (mount(शून्य, "/", शून्य, MS_REC | MS_PRIVATE, 0))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_mnt_flags(स्थिर अक्षर *path)
अणु
	पूर्णांक ret;
	काष्ठा statvfs stat;
	अचिन्हित पूर्णांक mnt_flags;

	ret = statvfs(path, &stat);
	अगर (ret != 0)
		वापस -EINVAL;

	अगर (stat.f_flag &
	    ~(ST_RDONLY | ST_NOSUID | ST_NODEV | ST_NOEXEC | ST_NOATIME |
	      ST_NOसूचीATIME | ST_RELATIME | ST_SYNCHRONOUS | ST_MANDLOCK))
		वापस -EINVAL;

	mnt_flags = 0;
	अगर (stat.f_flag & ST_RDONLY)
		mnt_flags |= MS_RDONLY;
	अगर (stat.f_flag & ST_NOSUID)
		mnt_flags |= MS_NOSUID;
	अगर (stat.f_flag & ST_NODEV)
		mnt_flags |= MS_NODEV;
	अगर (stat.f_flag & ST_NOEXEC)
		mnt_flags |= MS_NOEXEC;
	अगर (stat.f_flag & ST_NOATIME)
		mnt_flags |= MS_NOATIME;
	अगर (stat.f_flag & ST_NOसूचीATIME)
		mnt_flags |= MS_NOसूचीATIME;
	अगर (stat.f_flag & ST_RELATIME)
		mnt_flags |= MS_RELATIME;
	अगर (stat.f_flag & ST_SYNCHRONOUS)
		mnt_flags |= MS_SYNCHRONOUS;
	अगर (stat.f_flag & ST_MANDLOCK)
		mnt_flags |= ST_MANDLOCK;

	वापस mnt_flags;
पूर्ण

अटल अक्षर *get_field(अक्षर *src, पूर्णांक nfields)
अणु
	पूर्णांक i;
	अक्षर *p = src;

	क्रम (i = 0; i < nfields; i++) अणु
		जबतक (*p && *p != ' ' && *p != '\t')
			p++;

		अगर (!*p)
			अवरोध;

		p++;
	पूर्ण

	वापस p;
पूर्ण

अटल व्योम null_enकरोfword(अक्षर *word)
अणु
	जबतक (*word && *word != ' ' && *word != '\t')
		word++;
	*word = '\0';
पूर्ण

अटल bool is_shared_mount(स्थिर अक्षर *path)
अणु
	माप_प्रकार len = 0;
	अक्षर *line = शून्य;
	खाता *f = शून्य;

	f = ख_खोलो("/proc/self/mountinfo", "re");
	अगर (!f)
		वापस false;

	जबतक (getline(&line, &len, f) != -1) अणु
		अक्षर *opts, *target;

		target = get_field(line, 4);
		अगर (!target)
			जारी;

		opts = get_field(target, 2);
		अगर (!opts)
			जारी;

		null_enकरोfword(target);

		अगर (म_भेद(target, path) != 0)
			जारी;

		null_enकरोfword(opts);
		अगर (म_माला(opts, "shared:"))
			वापस true;
	पूर्ण

	मुक्त(line);
	ख_बंद(f);

	वापस false;
पूर्ण

अटल व्योम *mount_setattr_thपढ़ो(व्योम *data)
अणु
	काष्ठा mount_attr attr = अणु
		.attr_set	= MOUNT_ATTR_RDONLY | MOUNT_ATTR_NOSUID,
		.attr_clr	= 0,
		.propagation	= MS_SHARED,
	पूर्ण;

	अगर (sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)))
		pthपढ़ो_निकास(पूर्णांक_to_ptr(-1));

	pthपढ़ो_निकास(पूर्णांक_to_ptr(0));
पूर्ण

/* Attempt to de-conflict with the selftests tree. */
#अगर_अघोषित SKIP
#घोषणा SKIP(s, ...)	XFAIL(s, ##__VA_ARGS__)
#पूर्ण_अगर

अटल bool mount_setattr_supported(व्योम)
अणु
	पूर्णांक ret;

	ret = sys_mount_setattr(-EBADF, "", AT_EMPTY_PATH, शून्य, 0);
	अगर (ret < 0 && त्रुटि_सं == ENOSYS)
		वापस false;

	वापस true;
पूर्ण

FIXTURE(mount_setattr) अणु
पूर्ण;

FIXTURE_SETUP(mount_setattr)
अणु
	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	ASSERT_EQ(prepare_unpriv_mountns(), 0);

	(व्योम)umount2("/mnt", MNT_DETACH);
	(व्योम)umount2("/tmp", MNT_DETACH);

	ASSERT_EQ(mount("testing", "/tmp", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/tmp/B", 0777), 0);

	ASSERT_EQ(mount("testing", "/tmp/B", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/tmp/B/BB", 0777), 0);

	ASSERT_EQ(mount("testing", "/tmp/B/BB", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(mount("testing", "/mnt", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/A", 0777), 0);

	ASSERT_EQ(mount("testing", "/mnt/A", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/A/AA", 0777), 0);

	ASSERT_EQ(mount("/tmp", "/mnt/A/AA", शून्य, MS_BIND | MS_REC, शून्य), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/B", 0777), 0);

	ASSERT_EQ(mount("testing", "/mnt/B", "ramfs",
			MS_NOATIME | MS_NODEV | MS_NOSUID, 0), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/B/BB", 0777), 0);

	ASSERT_EQ(mount("testing", "/tmp/B/BB", "devpts",
			MS_RELATIME | MS_NOEXEC | MS_RDONLY, 0), 0);
पूर्ण

FIXTURE_TEARDOWN(mount_setattr)
अणु
	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	(व्योम)umount2("/mnt/A", MNT_DETACH);
	(व्योम)umount2("/tmp", MNT_DETACH);
पूर्ण

TEST_F(mount_setattr, invalid_attributes)
अणु
	काष्ठा mount_attr invalid_attr = अणु
		.attr_set = (1U << 31),
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &invalid_attr,
				    माप(invalid_attr)), 0);

	invalid_attr.attr_set	= 0;
	invalid_attr.attr_clr	= (1U << 31);
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &invalid_attr,
				    माप(invalid_attr)), 0);

	invalid_attr.attr_clr		= 0;
	invalid_attr.propagation	= (1U << 31);
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &invalid_attr,
				    माप(invalid_attr)), 0);

	invalid_attr.attr_set		= (1U << 31);
	invalid_attr.attr_clr		= (1U << 31);
	invalid_attr.propagation	= (1U << 31);
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &invalid_attr,
				    माप(invalid_attr)), 0);

	ASSERT_NE(sys_mount_setattr(-1, "mnt/A", AT_RECURSIVE, &invalid_attr,
				    माप(invalid_attr)), 0);
पूर्ण

TEST_F(mount_setattr, extensibility)
अणु
	अचिन्हित पूर्णांक old_flags = 0, new_flags = 0, expected_flags = 0;
	अक्षर *s = "dummy";
	काष्ठा mount_attr invalid_attr = अणुपूर्ण;
	काष्ठा mount_attr_large अणु
		काष्ठा mount_attr attr1;
		काष्ठा mount_attr attr2;
		काष्ठा mount_attr attr3;
	पूर्ण large_attr = अणुपूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	old_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_GT(old_flags, 0);

	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, शून्य,
				    माप(invalid_attr)), 0);
	ASSERT_EQ(त्रुटि_सं, EFAULT);

	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, (व्योम *)s,
				    माप(invalid_attr)), 0);
	ASSERT_EQ(त्रुटि_सं, EINVAL);

	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &invalid_attr, 0), 0);
	ASSERT_EQ(त्रुटि_सं, EINVAL);

	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &invalid_attr,
				    माप(invalid_attr) / 2), 0);
	ASSERT_EQ(त्रुटि_सं, EINVAL);

	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &invalid_attr,
				    माप(invalid_attr) / 2), 0);
	ASSERT_EQ(त्रुटि_सं, EINVAL);

	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE,
				    (व्योम *)&large_attr, माप(large_attr)), 0);

	large_attr.attr3.attr_set = MOUNT_ATTR_RDONLY;
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE,
				    (व्योम *)&large_attr, माप(large_attr)), 0);

	large_attr.attr3.attr_set = 0;
	large_attr.attr1.attr_set = MOUNT_ATTR_RDONLY;
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE,
				    (व्योम *)&large_attr, माप(large_attr)), 0);

	expected_flags = old_flags;
	expected_flags |= MS_RDONLY;

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);
पूर्ण

TEST_F(mount_setattr, basic)
अणु
	अचिन्हित पूर्णांक old_flags = 0, new_flags = 0, expected_flags = 0;
	काष्ठा mount_attr attr = अणु
		.attr_set	= MOUNT_ATTR_RDONLY | MOUNT_ATTR_NOEXEC | MOUNT_ATTR_RELATIME,
		.attr_clr	= MOUNT_ATTR__ATIME,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	old_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_GT(old_flags, 0);

	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", 0, &attr, माप(attr)), 0);

	expected_flags = old_flags;
	expected_flags |= MS_RDONLY;
	expected_flags |= MS_NOEXEC;
	expected_flags &= ~MS_NOATIME;
	expected_flags |= MS_RELATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, old_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, old_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, old_flags);
पूर्ण

TEST_F(mount_setattr, basic_recursive)
अणु
	पूर्णांक fd;
	अचिन्हित पूर्णांक old_flags = 0, new_flags = 0, expected_flags = 0;
	काष्ठा mount_attr attr = अणु
		.attr_set	= MOUNT_ATTR_RDONLY | MOUNT_ATTR_NOEXEC | MOUNT_ATTR_RELATIME,
		.attr_clr	= MOUNT_ATTR__ATIME,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	old_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_GT(old_flags, 0);

	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags = old_flags;
	expected_flags |= MS_RDONLY;
	expected_flags |= MS_NOEXEC;
	expected_flags &= ~MS_NOATIME;
	expected_flags |= MS_RELATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	स_रखो(&attr, 0, माप(attr));
	attr.attr_clr = MOUNT_ATTR_RDONLY;
	attr.propagation = MS_SHARED;
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags &= ~MS_RDONLY;
	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B/BB"), true);

	fd = खोलो("/mnt/A/AA/B/b", O_RDWR | O_CLOEXEC | O_CREAT | O_EXCL, 0777);
	ASSERT_GE(fd, 0);

	/*
	 * We're holding a fd खोलो क्रम writing so this needs to fail somewhere
	 * in the middle and the mount options need to be unchanged.
	 */
	attr.attr_set = MOUNT_ATTR_RDONLY;
	ASSERT_LT(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B/BB"), true);

	EXPECT_EQ(बंद(fd), 0);
पूर्ण

TEST_F(mount_setattr, mount_has_ग_लिखोrs)
अणु
	पूर्णांक fd, dfd;
	अचिन्हित पूर्णांक old_flags = 0, new_flags = 0;
	काष्ठा mount_attr attr = अणु
		.attr_set	= MOUNT_ATTR_RDONLY | MOUNT_ATTR_NOEXEC | MOUNT_ATTR_RELATIME,
		.attr_clr	= MOUNT_ATTR__ATIME,
		.propagation	= MS_SHARED,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	old_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_GT(old_flags, 0);

	fd = खोलो("/mnt/A/AA/B/b", O_RDWR | O_CLOEXEC | O_CREAT | O_EXCL, 0777);
	ASSERT_GE(fd, 0);

	/*
	 * We're holding a fd खोलो to a mount somwhere in the middle so this
	 * needs to fail somewhere in the middle. After this the mount options
	 * need to be unchanged.
	 */
	ASSERT_LT(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, old_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A"), false);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, old_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA"), false);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, old_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B"), false);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, old_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B/BB"), false);

	dfd = खोलो("/mnt/A/AA/B", O_सूचीECTORY | O_CLOEXEC);
	ASSERT_GE(dfd, 0);
	EXPECT_EQ(fsync(dfd), 0);
	EXPECT_EQ(बंद(dfd), 0);

	EXPECT_EQ(fsync(fd), 0);
	EXPECT_EQ(बंद(fd), 0);

	/* All ग_लिखोrs are gone so this should succeed. */
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);
पूर्ण

TEST_F(mount_setattr, mixed_mount_options)
अणु
	अचिन्हित पूर्णांक old_flags1 = 0, old_flags2 = 0, new_flags = 0, expected_flags = 0;
	काष्ठा mount_attr attr = अणु
		.attr_clr = MOUNT_ATTR_RDONLY | MOUNT_ATTR_NOSUID | MOUNT_ATTR_NOEXEC | MOUNT_ATTR__ATIME,
		.attr_set = MOUNT_ATTR_RELATIME,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	old_flags1 = पढ़ो_mnt_flags("/mnt/B");
	ASSERT_GT(old_flags1, 0);

	old_flags2 = पढ़ो_mnt_flags("/mnt/B/BB");
	ASSERT_GT(old_flags2, 0);

	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/B", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags = old_flags2;
	expected_flags &= ~(MS_RDONLY | MS_NOEXEC | MS_NOATIME | MS_NOSUID);
	expected_flags |= MS_RELATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/B");
	ASSERT_EQ(new_flags, expected_flags);

	expected_flags = old_flags2;
	expected_flags &= ~(MS_RDONLY | MS_NOEXEC | MS_NOATIME | MS_NOSUID);
	expected_flags |= MS_RELATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/B/BB");
	ASSERT_EQ(new_flags, expected_flags);
पूर्ण

TEST_F(mount_setattr, समय_changes)
अणु
	अचिन्हित पूर्णांक old_flags = 0, new_flags = 0, expected_flags = 0;
	काष्ठा mount_attr attr = अणु
		.attr_set	= MOUNT_ATTR_NOसूचीATIME | MOUNT_ATTR_NOATIME,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	attr.attr_set = MOUNT_ATTR_STRICTATIME;
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	attr.attr_set = MOUNT_ATTR_STRICTATIME | MOUNT_ATTR_NOATIME;
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	attr.attr_set = MOUNT_ATTR_STRICTATIME | MOUNT_ATTR_NOATIME;
	attr.attr_clr = MOUNT_ATTR__ATIME;
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	attr.attr_set = 0;
	attr.attr_clr = MOUNT_ATTR_STRICTATIME;
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	attr.attr_clr = MOUNT_ATTR_NOATIME;
	ASSERT_NE(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	old_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_GT(old_flags, 0);

	attr.attr_set = MOUNT_ATTR_NOसूचीATIME | MOUNT_ATTR_NOATIME;
	attr.attr_clr = MOUNT_ATTR__ATIME;
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags = old_flags;
	expected_flags |= MS_NOATIME;
	expected_flags |= MS_NOसूचीATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	स_रखो(&attr, 0, माप(attr));
	attr.attr_set &= ~MOUNT_ATTR_NOATIME;
	attr.attr_set |= MOUNT_ATTR_RELATIME;
	attr.attr_clr |= MOUNT_ATTR__ATIME;
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags &= ~MS_NOATIME;
	expected_flags |= MS_RELATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	स_रखो(&attr, 0, माप(attr));
	attr.attr_set &= ~MOUNT_ATTR_RELATIME;
	attr.attr_set |= MOUNT_ATTR_STRICTATIME;
	attr.attr_clr |= MOUNT_ATTR__ATIME;
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags &= ~MS_RELATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	स_रखो(&attr, 0, माप(attr));
	attr.attr_set &= ~MOUNT_ATTR_STRICTATIME;
	attr.attr_set |= MOUNT_ATTR_NOATIME;
	attr.attr_clr |= MOUNT_ATTR__ATIME;
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags |= MS_NOATIME;
	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	स_रखो(&attr, 0, माप(attr));
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	स_रखो(&attr, 0, माप(attr));
	attr.attr_clr = MOUNT_ATTR_NOसूचीATIME;
	ASSERT_EQ(sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr)), 0);

	expected_flags &= ~MS_NOसूचीATIME;

	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);
पूर्ण

TEST_F(mount_setattr, multi_thपढ़ोed)
अणु
	पूर्णांक i, j, nthपढ़ोs, ret = 0;
	अचिन्हित पूर्णांक old_flags = 0, new_flags = 0, expected_flags = 0;
	pthपढ़ो_attr_t pattr;
	pthपढ़ो_t thपढ़ोs[DEFAULT_THREADS];

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	old_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_GT(old_flags, 0);

	/* Try to change mount options from multiple thपढ़ोs. */
	nthपढ़ोs = get_nprocs_conf();
	अगर (nthपढ़ोs > DEFAULT_THREADS)
		nthपढ़ोs = DEFAULT_THREADS;

	pthपढ़ो_attr_init(&pattr);
	क्रम (i = 0; i < nthपढ़ोs; i++)
		ASSERT_EQ(pthपढ़ो_create(&thपढ़ोs[i], &pattr, mount_setattr_thपढ़ो, शून्य), 0);

	क्रम (j = 0; j < i; j++) अणु
		व्योम *retptr = शून्य;

		EXPECT_EQ(pthपढ़ो_join(thपढ़ोs[j], &retptr), 0);

		ret += ptr_to_पूर्णांक(retptr);
		EXPECT_EQ(ret, 0);
	पूर्ण
	pthपढ़ो_attr_destroy(&pattr);

	ASSERT_EQ(ret, 0);

	expected_flags = old_flags;
	expected_flags |= MS_RDONLY;
	expected_flags |= MS_NOSUID;
	new_flags = पढ़ो_mnt_flags("/mnt/A");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B"), true);

	new_flags = पढ़ो_mnt_flags("/mnt/A/AA/B/BB");
	ASSERT_EQ(new_flags, expected_flags);

	ASSERT_EQ(is_shared_mount("/mnt/A/AA/B/BB"), true);
पूर्ण

TEST_F(mount_setattr, wrong_user_namespace)
अणु
	पूर्णांक ret;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_RDONLY,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	EXPECT_EQ(create_and_enter_userns(), 0);
	ret = sys_mount_setattr(-1, "/mnt/A", AT_RECURSIVE, &attr, माप(attr));
	ASSERT_LT(ret, 0);
	ASSERT_EQ(त्रुटि_सं, EPERM);
पूर्ण

TEST_F(mount_setattr, wrong_mount_namespace)
अणु
	पूर्णांक fd, ret;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_RDONLY,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	fd = खोलो("/mnt/A", O_सूचीECTORY | O_CLOEXEC);
	ASSERT_GE(fd, 0);

	ASSERT_EQ(unshare(CLONE_NEWNS), 0);

	ret = sys_mount_setattr(fd, "", AT_EMPTY_PATH | AT_RECURSIVE, &attr, माप(attr));
	ASSERT_LT(ret, 0);
	ASSERT_EQ(त्रुटि_सं, EINVAL);
पूर्ण

FIXTURE(mount_setattr_idmapped) अणु
पूर्ण;

FIXTURE_SETUP(mount_setattr_idmapped)
अणु
	पूर्णांक img_fd = -EBADF;

	ASSERT_EQ(unshare(CLONE_NEWNS), 0);

	ASSERT_EQ(mount(शून्य, "/", शून्य, MS_REC | MS_PRIVATE, 0), 0);

	(व्योम)umount2("/mnt", MNT_DETACH);
	(व्योम)umount2("/tmp", MNT_DETACH);

	ASSERT_EQ(mount("testing", "/tmp", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/tmp/B", 0777), 0);
	ASSERT_EQ(mknodat(-EBADF, "/tmp/B/b", S_IFREG | 0644, 0), 0);
	ASSERT_EQ(chown("/tmp/B/b", 0, 0), 0);

	ASSERT_EQ(mount("testing", "/tmp/B", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/tmp/B/BB", 0777), 0);
	ASSERT_EQ(mknodat(-EBADF, "/tmp/B/BB/b", S_IFREG | 0644, 0), 0);
	ASSERT_EQ(chown("/tmp/B/BB/b", 0, 0), 0);

	ASSERT_EQ(mount("testing", "/tmp/B/BB", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(mount("testing", "/mnt", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/A", 0777), 0);

	ASSERT_EQ(mount("testing", "/mnt/A", "tmpfs", MS_NOATIME | MS_NODEV,
			"size=100000,mode=700"), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/A/AA", 0777), 0);

	ASSERT_EQ(mount("/tmp", "/mnt/A/AA", शून्य, MS_BIND | MS_REC, शून्य), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/B", 0777), 0);

	ASSERT_EQ(mount("testing", "/mnt/B", "ramfs",
			MS_NOATIME | MS_NODEV | MS_NOSUID, 0), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/B/BB", 0777), 0);

	ASSERT_EQ(mount("testing", "/tmp/B/BB", "devpts",
			MS_RELATIME | MS_NOEXEC | MS_RDONLY, 0), 0);

	ASSERT_EQ(सूची_गढ़ो("/mnt/C", 0777), 0);
	ASSERT_EQ(सूची_गढ़ो("/mnt/D", 0777), 0);
	img_fd = खोलोat(-EBADF, "/mnt/C/ext4.img", O_CREAT | O_WRONLY, 0600);
	ASSERT_GE(img_fd, 0);
	ASSERT_EQ(ftruncate(img_fd, 1024 * 2048), 0);
	ASSERT_EQ(प्रणाली("mkfs.ext4 -q /mnt/C/ext4.img"), 0);
	ASSERT_EQ(प्रणाली("mount -o loop -t ext4 /mnt/C/ext4.img /mnt/D/"), 0);
	ASSERT_EQ(बंद(img_fd), 0);
पूर्ण

FIXTURE_TEARDOWN(mount_setattr_idmapped)
अणु
	(व्योम)umount2("/mnt/A", MNT_DETACH);
	(व्योम)umount2("/tmp", MNT_DETACH);
पूर्ण

/**
 * Validate that negative fd values are rejected.
 */
TEST_F(mount_setattr_idmapped, invalid_fd_negative)
अणु
	काष्ठा mount_attr attr = अणु
		.attr_set	= MOUNT_ATTR_IDMAP,
		.userns_fd	= -EBADF,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	ASSERT_NE(sys_mount_setattr(-1, "/", 0, &attr, माप(attr)), 0) अणु
		TH_LOG("failure: created idmapped mount with negative fd");
	पूर्ण
पूर्ण

/**
 * Validate that excessively large fd values are rejected.
 */
TEST_F(mount_setattr_idmapped, invalid_fd_large)
अणु
	काष्ठा mount_attr attr = अणु
		.attr_set	= MOUNT_ATTR_IDMAP,
		.userns_fd	= INT64_MAX,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	ASSERT_NE(sys_mount_setattr(-1, "/", 0, &attr, माप(attr)), 0) अणु
		TH_LOG("failure: created idmapped mount with too large fd value");
	पूर्ण
पूर्ण

/**
 * Validate that बंदd fd values are rejected.
 */
TEST_F(mount_setattr_idmapped, invalid_fd_बंदd)
अणु
	पूर्णांक fd;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	fd = खोलो("/dev/null", O_RDONLY | O_CLOEXEC);
	ASSERT_GE(fd, 0);
	ASSERT_GE(बंद(fd), 0);

	attr.userns_fd = fd;
	ASSERT_NE(sys_mount_setattr(-1, "/", 0, &attr, माप(attr)), 0) अणु
		TH_LOG("failure: created idmapped mount with closed fd");
	पूर्ण
पूर्ण

/**
 * Validate that the initial user namespace is rejected.
 */
TEST_F(mount_setattr_idmapped, invalid_fd_initial_userns)
अणु
	पूर्णांक खोलो_tree_fd = -EBADF;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	खोलो_tree_fd = sys_खोलो_tree(-EBADF, "/mnt/D",
				     AT_NO_AUTOMOUNT |
				     AT_SYMLINK_NOFOLLOW |
				     OPEN_TREE_CLOEXEC | OPEN_TREE_CLONE);
	ASSERT_GE(खोलो_tree_fd, 0);

	attr.userns_fd = खोलो("/proc/1/ns/user", O_RDONLY | O_CLOEXEC);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_NE(sys_mount_setattr(खोलो_tree_fd, "", AT_EMPTY_PATH, &attr, माप(attr)), 0);
	ASSERT_EQ(त्रुटि_सं, EPERM);
	ASSERT_EQ(बंद(attr.userns_fd), 0);
	ASSERT_EQ(बंद(खोलो_tree_fd), 0);
पूर्ण

अटल पूर्णांक map_ids(pid_t pid, अचिन्हित दीर्घ nsid, अचिन्हित दीर्घ hostid,
		   अचिन्हित दीर्घ range)
अणु
	अक्षर map[100], procfile[256];

	snम_लिखो(procfile, माप(procfile), "/proc/%d/uid_map", pid);
	snम_लिखो(map, माप(map), "%lu %lu %lu", nsid, hostid, range);
	अगर (ग_लिखो_file(procfile, map, म_माप(map)))
		वापस -1;


	snम_लिखो(procfile, माप(procfile), "/proc/%d/gid_map", pid);
	snम_लिखो(map, माप(map), "%lu %lu %lu", nsid, hostid, range);
	अगर (ग_लिखो_file(procfile, map, म_माप(map)))
		वापस -1;

	वापस 0;
पूर्ण

#घोषणा __STACK_SIZE (8 * 1024 * 1024)
अटल pid_t करो_clone(पूर्णांक (*fn)(व्योम *), व्योम *arg, पूर्णांक flags)
अणु
	व्योम *stack;

	stack = दो_स्मृति(__STACK_SIZE);
	अगर (!stack)
		वापस -ENOMEM;

#अगर_घोषित __ia64__
	वापस __clone2(fn, stack, __STACK_SIZE, flags | SIGCHLD, arg, शून्य);
#अन्यथा
	वापस clone(fn, stack + __STACK_SIZE, flags | SIGCHLD, arg, शून्य);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक get_userns_fd_cb(व्योम *data)
अणु
	वापस समाप्त(getpid(), SIGSTOP);
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

अटल पूर्णांक get_userns_fd(अचिन्हित दीर्घ nsid, अचिन्हित दीर्घ hostid, अचिन्हित दीर्घ range)
अणु
	पूर्णांक ret;
	pid_t pid;
	अक्षर path[256];

	pid = करो_clone(get_userns_fd_cb, शून्य, CLONE_NEWUSER);
	अगर (pid < 0)
		वापस -त्रुटि_सं;

	ret = map_ids(pid, nsid, hostid, range);
	अगर (ret < 0)
		वापस ret;

	snम_लिखो(path, माप(path), "/proc/%d/ns/user", pid);
	ret = खोलो(path, O_RDONLY | O_CLOEXEC);
	समाप्त(pid, SIGKILL);
	रुको_क्रम_pid(pid);
	वापस ret;
पूर्ण

/**
 * Validate that an attached mount in our mount namespace can be idmapped.
 * (The kernel enक्रमces that the mount's mount namespace and the caller's mount
 *  namespace match.)
 */
TEST_F(mount_setattr_idmapped, attached_mount_inside_current_mount_namespace)
अणु
	पूर्णांक खोलो_tree_fd = -EBADF;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	खोलो_tree_fd = sys_खोलो_tree(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMLINK_NOFOLLOW |
				     OPEN_TREE_CLOEXEC);
	ASSERT_GE(खोलो_tree_fd, 0);

	attr.userns_fd	= get_userns_fd(0, 10000, 10000);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_EQ(sys_mount_setattr(खोलो_tree_fd, "", AT_EMPTY_PATH, &attr, माप(attr)), 0);
	ASSERT_EQ(बंद(attr.userns_fd), 0);
	ASSERT_EQ(बंद(खोलो_tree_fd), 0);
पूर्ण

/**
 * Validate that idmapping a mount is rejected अगर the mount's mount namespace
 * and our mount namespace करोn't match.
 * (The kernel enक्रमces that the mount's mount namespace and the caller's mount
 *  namespace match.)
 */
TEST_F(mount_setattr_idmapped, attached_mount_outside_current_mount_namespace)
अणु
	पूर्णांक खोलो_tree_fd = -EBADF;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	खोलो_tree_fd = sys_खोलो_tree(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMLINK_NOFOLLOW |
				     OPEN_TREE_CLOEXEC);
	ASSERT_GE(खोलो_tree_fd, 0);

	ASSERT_EQ(unshare(CLONE_NEWNS), 0);

	attr.userns_fd	= get_userns_fd(0, 10000, 10000);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_NE(sys_mount_setattr(खोलो_tree_fd, "", AT_EMPTY_PATH, &attr,
				    माप(attr)), 0);
	ASSERT_EQ(बंद(attr.userns_fd), 0);
	ASSERT_EQ(बंद(खोलो_tree_fd), 0);
पूर्ण

/**
 * Validate that an attached mount in our mount namespace can be idmapped.
 */
TEST_F(mount_setattr_idmapped, detached_mount_inside_current_mount_namespace)
अणु
	पूर्णांक खोलो_tree_fd = -EBADF;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	खोलो_tree_fd = sys_खोलो_tree(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMLINK_NOFOLLOW |
				     OPEN_TREE_CLOEXEC |
				     OPEN_TREE_CLONE);
	ASSERT_GE(खोलो_tree_fd, 0);

	/* Changing mount properties on a detached mount. */
	attr.userns_fd	= get_userns_fd(0, 10000, 10000);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_EQ(sys_mount_setattr(खोलो_tree_fd, "",
				    AT_EMPTY_PATH, &attr, माप(attr)), 0);
	ASSERT_EQ(बंद(attr.userns_fd), 0);
	ASSERT_EQ(बंद(खोलो_tree_fd), 0);
पूर्ण

/**
 * Validate that a detached mount not in our mount namespace can be idmapped.
 */
TEST_F(mount_setattr_idmapped, detached_mount_outside_current_mount_namespace)
अणु
	पूर्णांक खोलो_tree_fd = -EBADF;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	खोलो_tree_fd = sys_खोलो_tree(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMLINK_NOFOLLOW |
				     OPEN_TREE_CLOEXEC |
				     OPEN_TREE_CLONE);
	ASSERT_GE(खोलो_tree_fd, 0);

	ASSERT_EQ(unshare(CLONE_NEWNS), 0);

	/* Changing mount properties on a detached mount. */
	attr.userns_fd	= get_userns_fd(0, 10000, 10000);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_EQ(sys_mount_setattr(खोलो_tree_fd, "",
				    AT_EMPTY_PATH, &attr, माप(attr)), 0);
	ASSERT_EQ(बंद(attr.userns_fd), 0);
	ASSERT_EQ(बंद(खोलो_tree_fd), 0);
पूर्ण

/**
 * Validate that currently changing the idmapping of an idmapped mount fails.
 */
TEST_F(mount_setattr_idmapped, change_idmapping)
अणु
	पूर्णांक खोलो_tree_fd = -EBADF;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	खोलो_tree_fd = sys_खोलो_tree(-EBADF, "/mnt/D",
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMLINK_NOFOLLOW |
				     OPEN_TREE_CLOEXEC |
				     OPEN_TREE_CLONE);
	ASSERT_GE(खोलो_tree_fd, 0);

	attr.userns_fd	= get_userns_fd(0, 10000, 10000);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_EQ(sys_mount_setattr(खोलो_tree_fd, "",
				    AT_EMPTY_PATH, &attr, माप(attr)), 0);
	ASSERT_EQ(बंद(attr.userns_fd), 0);

	/* Change idmapping on a detached mount that is alपढ़ोy idmapped. */
	attr.userns_fd	= get_userns_fd(0, 20000, 10000);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_NE(sys_mount_setattr(खोलो_tree_fd, "", AT_EMPTY_PATH, &attr, माप(attr)), 0);
	ASSERT_EQ(बंद(attr.userns_fd), 0);
	ASSERT_EQ(बंद(खोलो_tree_fd), 0);
पूर्ण

अटल bool expected_uid_gid(पूर्णांक dfd, स्थिर अक्षर *path, पूर्णांक flags,
			     uid_t expected_uid, gid_t expected_gid)
अणु
	पूर्णांक ret;
	काष्ठा stat st;

	ret = ख_स्थितिat(dfd, path, &st, flags);
	अगर (ret < 0)
		वापस false;

	वापस st.st_uid == expected_uid && st.st_gid == expected_gid;
पूर्ण

TEST_F(mount_setattr_idmapped, idmap_mount_tree_invalid)
अणु
	पूर्णांक खोलो_tree_fd = -EBADF;
	काष्ठा mount_attr attr = अणु
		.attr_set = MOUNT_ATTR_IDMAP,
	पूर्ण;

	अगर (!mount_setattr_supported())
		SKIP(वापस, "mount_setattr syscall not supported");

	ASSERT_EQ(expected_uid_gid(-EBADF, "/tmp/B/b", 0, 0, 0), 0);
	ASSERT_EQ(expected_uid_gid(-EBADF, "/tmp/B/BB/b", 0, 0, 0), 0);

	खोलो_tree_fd = sys_खोलो_tree(-EBADF, "/mnt/A",
				     AT_RECURSIVE |
				     AT_EMPTY_PATH |
				     AT_NO_AUTOMOUNT |
				     AT_SYMLINK_NOFOLLOW |
				     OPEN_TREE_CLOEXEC |
				     OPEN_TREE_CLONE);
	ASSERT_GE(खोलो_tree_fd, 0);

	attr.userns_fd	= get_userns_fd(0, 10000, 10000);
	ASSERT_GE(attr.userns_fd, 0);
	ASSERT_NE(sys_mount_setattr(खोलो_tree_fd, "", AT_EMPTY_PATH, &attr, माप(attr)), 0);
	ASSERT_EQ(बंद(attr.userns_fd), 0);
	ASSERT_EQ(बंद(खोलो_tree_fd), 0);

	ASSERT_EQ(expected_uid_gid(-EBADF, "/tmp/B/b", 0, 0, 0), 0);
	ASSERT_EQ(expected_uid_gid(-EBADF, "/tmp/B/BB/b", 0, 0, 0), 0);
	ASSERT_EQ(expected_uid_gid(खोलो_tree_fd, "B/b", 0, 0, 0), 0);
	ASSERT_EQ(expected_uid_gid(खोलो_tree_fd, "B/BB/b", 0, 0, 0), 0);
पूर्ण

TEST_HARNESS_MAIN
