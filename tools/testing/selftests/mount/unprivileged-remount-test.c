<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/mount.h>
#समावेश <sys/रुको.h>
#समावेश <sys/vfs.h>
#समावेश <sys/statvfs.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <grp.h>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>

#अगर_अघोषित CLONE_NEWNS
# define CLONE_NEWNS 0x00020000
#पूर्ण_अगर
#अगर_अघोषित CLONE_NEWUTS
# define CLONE_NEWUTS 0x04000000
#पूर्ण_अगर
#अगर_अघोषित CLONE_NEWIPC
# define CLONE_NEWIPC 0x08000000
#पूर्ण_अगर
#अगर_अघोषित CLONE_NEWNET
# define CLONE_NEWNET 0x40000000
#पूर्ण_अगर
#अगर_अघोषित CLONE_NEWUSER
# define CLONE_NEWUSER 0x10000000
#पूर्ण_अगर
#अगर_अघोषित CLONE_NEWPID
# define CLONE_NEWPID 0x20000000
#पूर्ण_अगर

#अगर_अघोषित MS_REC
# define MS_REC 16384
#पूर्ण_अगर
#अगर_अघोषित MS_RELATIME
# define MS_RELATIME (1 << 21)
#पूर्ण_अगर
#अगर_अघोषित MS_STRICTATIME
# define MS_STRICTATIME (1 << 24)
#पूर्ण_अगर

अटल व्योम die(अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	बहु_पूर्ण(ap);
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम vmaybe_ग_लिखो_file(bool enoent_ok, अक्षर *filename, अक्षर *fmt, बहु_सूची ap)
अणु
	अक्षर buf[4096];
	पूर्णांक fd;
	sमाप_प्रकार written;
	पूर्णांक buf_len;

	buf_len = vsnम_लिखो(buf, माप(buf), fmt, ap);
	अगर (buf_len < 0) अणु
		die("vsnprintf failed: %s\n",
		    म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (buf_len >= माप(buf)) अणु
		die("vsnprintf output truncated\n");
	पूर्ण

	fd = खोलो(filename, O_WRONLY);
	अगर (fd < 0) अणु
		अगर ((त्रुटि_सं == ENOENT) && enoent_ok)
			वापस;
		die("open of %s failed: %s\n",
		    filename, म_त्रुटि(त्रुटि_सं));
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
	अगर (बंद(fd) != 0) अणु
		die("close of %s failed: %s\n",
			filename, म_त्रुटि(त्रुटि_सं));
	पूर्ण
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

अटल पूर्णांक पढ़ो_mnt_flags(स्थिर अक्षर *path)
अणु
	पूर्णांक ret;
	काष्ठा statvfs stat;
	पूर्णांक mnt_flags;

	ret = statvfs(path, &stat);
	अगर (ret != 0) अणु
		die("statvfs of %s failed: %s\n",
			path, म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (stat.f_flag & ~(ST_RDONLY | ST_NOSUID | ST_NODEV | \
			ST_NOEXEC | ST_NOATIME | ST_NOसूचीATIME | ST_RELATIME | \
			ST_SYNCHRONOUS | ST_MANDLOCK)) अणु
		die("Unrecognized mount flags\n");
	पूर्ण
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

अटल व्योम create_and_enter_userns(व्योम)
अणु
	uid_t uid;
	gid_t gid;

	uid = getuid();
	gid = getgid();

	अगर (unshare(CLONE_NEWUSER) !=0) अणु
		die("unshare(CLONE_NEWUSER) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	maybe_ग_लिखो_file("/proc/self/setgroups", "deny");
	ग_लिखो_file("/proc/self/uid_map", "0 %d 1", uid);
	ग_लिखो_file("/proc/self/gid_map", "0 %d 1", gid);

	अगर (setgid(0) != 0) अणु
		die ("setgid(0) failed %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (setuid(0) != 0) अणु
		die("setuid(0) failed %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

अटल
bool test_unpriv_remount(स्थिर अक्षर *fstype, स्थिर अक्षर *mount_options,
			 पूर्णांक mount_flags, पूर्णांक remount_flags, पूर्णांक invalid_flags)
अणु
	pid_t child;

	child = विभाजन();
	अगर (child == -1) अणु
		die("fork failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (child != 0) अणु /* parent */
		pid_t pid;
		पूर्णांक status;
		pid = रुकोpid(child, &status, 0);
		अगर (pid == -1) अणु
			die("waitpid failed: %s\n",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण
		अगर (pid != child) अणु
			die("waited for %d got %d\n",
				child, pid);
		पूर्ण
		अगर (!WIFEXITED(status)) अणु
			die("child did not terminate cleanly\n");
		पूर्ण
		वापस WEXITSTATUS(status) == निकास_सफल ? true : false;
	पूर्ण

	create_and_enter_userns();
	अगर (unshare(CLONE_NEWNS) != 0) अणु
		die("unshare(CLONE_NEWNS) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (mount("testing", "/tmp", fstype, mount_flags, mount_options) != 0) अणु
		die("mount of %s with options '%s' on /tmp failed: %s\n",
		    fstype,
		    mount_options? mount_options : "",
		    म_त्रुटि(त्रुटि_सं));
	पूर्ण

	create_and_enter_userns();

	अगर (unshare(CLONE_NEWNS) != 0) अणु
		die("unshare(CLONE_NEWNS) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (mount("/tmp", "/tmp", "none",
		  MS_REMOUNT | MS_BIND | remount_flags, शून्य) != 0) अणु
		/* प्रणाली("cat /proc/self/mounts"); */
		die("remount of /tmp failed: %s\n",
		    म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (mount("/tmp", "/tmp", "none",
		  MS_REMOUNT | MS_BIND | invalid_flags, शून्य) == 0) अणु
		/* प्रणाली("cat /proc/self/mounts"); */
		die("remount of /tmp with invalid flags "
		    "succeeded unexpectedly\n");
	पूर्ण
	निकास(निकास_सफल);
पूर्ण

अटल bool test_unpriv_remount_simple(पूर्णांक mount_flags)
अणु
	वापस test_unpriv_remount("ramfs", शून्य, mount_flags, mount_flags, 0);
पूर्ण

अटल bool test_unpriv_remount_aसमय(पूर्णांक mount_flags, पूर्णांक invalid_flags)
अणु
	वापस test_unpriv_remount("ramfs", शून्य, mount_flags, mount_flags,
				   invalid_flags);
पूर्ण

अटल bool test_priv_mount_unpriv_remount(व्योम)
अणु
	pid_t child;
	पूर्णांक ret;
	स्थिर अक्षर *orig_path = "/dev";
	स्थिर अक्षर *dest_path = "/tmp";
	पूर्णांक orig_mnt_flags, remount_mnt_flags;

	child = विभाजन();
	अगर (child == -1) अणु
		die("fork failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (child != 0) अणु /* parent */
		pid_t pid;
		पूर्णांक status;
		pid = रुकोpid(child, &status, 0);
		अगर (pid == -1) अणु
			die("waitpid failed: %s\n",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण
		अगर (pid != child) अणु
			die("waited for %d got %d\n",
				child, pid);
		पूर्ण
		अगर (!WIFEXITED(status)) अणु
			die("child did not terminate cleanly\n");
		पूर्ण
		वापस WEXITSTATUS(status) == निकास_सफल ? true : false;
	पूर्ण

	orig_mnt_flags = पढ़ो_mnt_flags(orig_path);

	create_and_enter_userns();
	ret = unshare(CLONE_NEWNS);
	अगर (ret != 0) अणु
		die("unshare(CLONE_NEWNS) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ret = mount(orig_path, dest_path, "bind", MS_BIND | MS_REC, शून्य);
	अगर (ret != 0) अणु
		die("recursive bind mount of %s onto %s failed: %s\n",
			orig_path, dest_path, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ret = mount(dest_path, dest_path, "none",
		    MS_REMOUNT | MS_BIND | orig_mnt_flags , शून्य);
	अगर (ret != 0) अणु
		/* प्रणाली("cat /proc/self/mounts"); */
		die("remount of /tmp failed: %s\n",
		    म_त्रुटि(त्रुटि_सं));
	पूर्ण

	remount_mnt_flags = पढ़ो_mnt_flags(dest_path);
	अगर (orig_mnt_flags != remount_mnt_flags) अणु
		die("Mount flags unexpectedly changed during remount of %s originally mounted on %s\n",
			dest_path, orig_path);
	पूर्ण
	निकास(निकास_सफल);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (!test_unpriv_remount_simple(MS_RDONLY)) अणु
		die("MS_RDONLY malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount("devpts", "newinstance", MS_NODEV, MS_NODEV, 0)) अणु
		die("MS_NODEV malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_simple(MS_NOSUID)) अणु
		die("MS_NOSUID malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_simple(MS_NOEXEC)) अणु
		die("MS_NOEXEC malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_aसमय(MS_RELATIME,
				       MS_NOATIME))
	अणु
		die("MS_RELATIME malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_aसमय(MS_STRICTATIME,
				       MS_NOATIME))
	अणु
		die("MS_STRICTATIME malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_aसमय(MS_NOATIME,
				       MS_STRICTATIME))
	अणु
		die("MS_NOATIME malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_aसमय(MS_RELATIME|MS_NOसूचीATIME,
				       MS_NOATIME))
	अणु
		die("MS_RELATIME|MS_NODIRATIME malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_aसमय(MS_STRICTATIME|MS_NOसूचीATIME,
				       MS_NOATIME))
	अणु
		die("MS_STRICTATIME|MS_NODIRATIME malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount_aसमय(MS_NOATIME|MS_NOसूचीATIME,
				       MS_STRICTATIME))
	अणु
		die("MS_NOATIME|MS_DIRATIME malfunctions\n");
	पूर्ण
	अगर (!test_unpriv_remount("ramfs", शून्य, MS_STRICTATIME, 0, MS_NOATIME))
	अणु
		die("Default atime malfunctions\n");
	पूर्ण
	अगर (!test_priv_mount_unpriv_remount()) अणु
		die("Mount flags unexpectedly changed after remount\n");
	पूर्ण
	वापस निकास_सफल;
पूर्ण
