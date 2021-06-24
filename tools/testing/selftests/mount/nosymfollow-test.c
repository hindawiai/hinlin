<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <sched.h>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mount.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/vfs.h>
#समावेश <unistd.h>

#अगर_अघोषित MS_NOSYMFOLLOW
# define MS_NOSYMFOLLOW 256     /* Do not follow symlinks */
#पूर्ण_अगर

#अगर_अघोषित ST_NOSYMFOLLOW
# define ST_NOSYMFOLLOW 0x2000  /* Do not follow symlinks */
#पूर्ण_अगर

#घोषणा DATA "/tmp/data"
#घोषणा LINK "/tmp/symlink"
#घोषणा TMP  "/tmp"

अटल व्योम die(अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	बहु_पूर्ण(ap);
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम vmaybe_ग_लिखो_file(bool enoent_ok, अक्षर *filename, अक्षर *fmt,
		बहु_सूची ap)
अणु
	sमाप_प्रकार written;
	अक्षर buf[4096];
	पूर्णांक buf_len;
	पूर्णांक fd;

	buf_len = vsnम_लिखो(buf, माप(buf), fmt, ap);
	अगर (buf_len < 0)
		die("vsnprintf failed: %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (buf_len >= माप(buf))
		die("vsnprintf output truncated\n");

	fd = खोलो(filename, O_WRONLY);
	अगर (fd < 0) अणु
		अगर ((त्रुटि_सं == ENOENT) && enoent_ok)
			वापस;
		die("open of %s failed: %s\n", filename, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	written = ग_लिखो(fd, buf, buf_len);
	अगर (written != buf_len) अणु
		अगर (written >= 0) अणु
			die("short write to %s\n", filename);
		पूर्ण अन्यथा अणु
			die("write to %s failed: %s\n",
				filename, म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण

	अगर (बंद(fd) != 0)
		die("close of %s failed: %s\n", filename, म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम maybe_ग_लिखो_file(अक्षर *filename, अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	vmaybe_ग_लिखो_file(true, filename, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम ग_लिखो_file(अक्षर *filename, अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	vmaybe_ग_लिखो_file(false, filename, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम create_and_enter_ns(व्योम)
अणु
	uid_t uid = getuid();
	gid_t gid = getgid();

	अगर (unshare(CLONE_NEWUSER) != 0)
		die("unshare(CLONE_NEWUSER) failed: %s\n", म_त्रुटि(त्रुटि_सं));

	maybe_ग_लिखो_file("/proc/self/setgroups", "deny");
	ग_लिखो_file("/proc/self/uid_map", "0 %d 1", uid);
	ग_लिखो_file("/proc/self/gid_map", "0 %d 1", gid);

	अगर (setgid(0) != 0)
		die("setgid(0) failed %s\n", म_त्रुटि(त्रुटि_सं));
	अगर (setuid(0) != 0)
		die("setuid(0) failed %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (unshare(CLONE_NEWNS) != 0)
		die("unshare(CLONE_NEWNS) failed: %s\n", म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम setup_symlink(व्योम)
अणु
	पूर्णांक data, err;

	data = creat(DATA, O_RDWR);
	अगर (data < 0)
		die("creat failed: %s\n", म_त्रुटि(त्रुटि_सं));

	err = symlink(DATA, LINK);
	अगर (err < 0)
		die("symlink failed: %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (बंद(data) != 0)
		die("close of %s failed: %s\n", DATA, म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम test_link_traversal(bool nosymfollow)
अणु
	पूर्णांक link;

	link = खोलो(LINK, 0, O_RDWR);
	अगर (nosymfollow) अणु
		अगर ((link != -1 || त्रुटि_सं != ELOOP)) अणु
			die("link traversal unexpected result: %d, %s\n",
					link, म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (link < 0)
			die("link traversal failed: %s\n", म_त्रुटि(त्रुटि_सं));

		अगर (बंद(link) != 0)
			die("close of link failed: %s\n", म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

अटल व्योम test_पढ़ोlink(व्योम)
अणु
	अक्षर buf[4096];
	sमाप_प्रकार ret;

	bzero(buf, माप(buf));

	ret = पढ़ोlink(LINK, buf, माप(buf));
	अगर (ret < 0)
		die("readlink failed: %s\n", म_त्रुटि(त्रुटि_सं));
	अगर (म_भेद(buf, DATA) != 0)
		die("readlink strcmp failed: '%s' '%s'\n", buf, DATA);
पूर्ण

अटल व्योम test_realpath(व्योम)
अणु
	अक्षर *path = realpath(LINK, शून्य);

	अगर (!path)
		die("realpath failed: %s\n", म_त्रुटि(त्रुटि_सं));
	अगर (म_भेद(path, DATA) != 0)
		die("realpath strcmp failed\n");

	मुक्त(path);
पूर्ण

अटल व्योम test_statfs(bool nosymfollow)
अणु
	काष्ठा statfs buf;
	पूर्णांक ret;

	ret = statfs(TMP, &buf);
	अगर (ret)
		die("statfs failed: %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (nosymfollow) अणु
		अगर ((buf.f_flags & ST_NOSYMFOLLOW) == 0)
			die("ST_NOSYMFOLLOW not set on %s\n", TMP);
	पूर्ण अन्यथा अणु
		अगर ((buf.f_flags & ST_NOSYMFOLLOW) != 0)
			die("ST_NOSYMFOLLOW set on %s\n", TMP);
	पूर्ण
पूर्ण

अटल व्योम run_tests(bool nosymfollow)
अणु
	test_link_traversal(nosymfollow);
	test_पढ़ोlink();
	test_realpath();
	test_statfs(nosymfollow);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	create_and_enter_ns();

	अगर (mount("testing", TMP, "ramfs", 0, शून्य) != 0)
		die("mount failed: %s\n", म_त्रुटि(त्रुटि_सं));

	setup_symlink();
	run_tests(false);

	अगर (mount("testing", TMP, "ramfs", MS_REMOUNT|MS_NOSYMFOLLOW, शून्य) != 0)
		die("remount failed: %s\n", म_त्रुटि(त्रुटि_सं));

	run_tests(true);

	वापस निकास_सफल;
पूर्ण
