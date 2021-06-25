<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#घोषणा _GNU_SOURCE
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <fcntl.h>
#समावेश <sys/रुको.h>
#समावेश <sys/mount.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/पन.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/reboot.h>
#समावेश <sys/utsname.h>
#समावेश <sys/sendfile.h>
#समावेश <sys/sysmacros.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/version.h>

__attribute__((noवापस)) अटल व्योम घातeroff(व्योम)
अणु
	ख_साफ(मानक_निकास);
	ख_साफ(मानक_त्रुटि);
	reboot(RB_AUTOBOOT);
	sleep(30);
	ख_लिखो(मानक_त्रुटि, "\x1b[37m\x1b[41m\x1b[1mFailed to power off!!!\x1b[0m\n");
	निकास(1);
पूर्ण

अटल व्योम panic(स्थिर अक्षर *what)
अणु
	ख_लिखो(मानक_त्रुटि, "\n\n\x1b[37m\x1b[41m\x1b[1mSOMETHING WENT HORRIBLY WRONG\x1b[0m\n\n    \x1b[31m\x1b[1m%s: %s\x1b[0m\n\n\x1b[37m\x1b[44m\x1b[1mPower off...\x1b[0m\n\n", what, म_त्रुटि(त्रुटि_सं));
	घातeroff();
पूर्ण

#घोषणा pretty_message(msg) माला_दो("\x1b[32m\x1b[1m" msg "\x1b[0m")

अटल व्योम prपूर्णांक_banner(व्योम)
अणु
	काष्ठा utsname utsname;
	पूर्णांक len;

	अगर (uname(&utsname) < 0)
		panic("uname");

	len = म_माप("    WireGuard Test Suite on       ") + म_माप(utsname.sysname) + म_माप(utsname.release) + म_माप(utsname.machine);
	म_लिखो("\x1b[45m\x1b[33m\x1b[1m%*.s\x1b[0m\n\x1b[45m\x1b[33m\x1b[1m    WireGuard Test Suite on %s %s %s    \x1b[0m\n\x1b[45m\x1b[33m\x1b[1m%*.s\x1b[0m\n\n", len, "", utsname.sysname, utsname.release, utsname.machine, len, "");
पूर्ण

अटल व्योम seed_rng(व्योम)
अणु
	पूर्णांक fd;
	काष्ठा अणु
		पूर्णांक entropy_count;
		पूर्णांक buffer_size;
		अचिन्हित अक्षर buffer[256];
	पूर्ण entropy = अणु
		.entropy_count = माप(entropy.buffer) * 8,
		.buffer_size = माप(entropy.buffer),
		.buffer = "Adding real entropy is not actually important for these tests. Don't try this at home, kids!"
	पूर्ण;

	अगर (mknod("/dev/urandom", S_IFCHR | 0644, makedev(1, 9)))
		panic("mknod(/dev/urandom)");
	fd = खोलो("/dev/urandom", O_WRONLY);
	अगर (fd < 0)
		panic("open(urandom)");
	क्रम (पूर्णांक i = 0; i < 256; ++i) अणु
		अगर (ioctl(fd, RNDADDENTROPY, &entropy) < 0)
			panic("ioctl(urandom)");
	पूर्ण
	बंद(fd);
पूर्ण

अटल व्योम mount_fileप्रणालीs(व्योम)
अणु
	pretty_message("[+] Mounting filesystems...");
	सूची_गढ़ो("/dev", 0755);
	सूची_गढ़ो("/proc", 0755);
	सूची_गढ़ो("/sys", 0755);
	सूची_गढ़ो("/tmp", 0755);
	सूची_गढ़ो("/run", 0755);
	सूची_गढ़ो("/var", 0755);
	अगर (mount("none", "/dev", "devtmpfs", 0, शून्य))
		panic("devtmpfs mount");
	अगर (mount("none", "/proc", "proc", 0, शून्य))
		panic("procfs mount");
	अगर (mount("none", "/sys", "sysfs", 0, शून्य))
		panic("sysfs mount");
	अगर (mount("none", "/tmp", "tmpfs", 0, शून्य))
		panic("tmpfs mount");
	अगर (mount("none", "/run", "tmpfs", 0, शून्य))
		panic("tmpfs mount");
	अगर (mount("none", "/sys/kernel/debug", "debugfs", 0, शून्य))
		; /* Not a problem अगर it fails.*/
	अगर (symlink("/run", "/var/run"))
		panic("run symlink");
	अगर (symlink("/proc/self/fd", "/dev/fd"))
		panic("fd symlink");
पूर्ण

अटल व्योम enable_logging(व्योम)
अणु
	पूर्णांक fd;
	pretty_message("[+] Enabling logging...");
	fd = खोलो("/proc/sys/kernel/printk", O_WRONLY);
	अगर (fd >= 0) अणु
		अगर (ग_लिखो(fd, "9\n", 2) != 2)
			panic("write(printk)");
		बंद(fd);
	पूर्ण
	fd = खोलो("/proc/sys/debug/exception-trace", O_WRONLY);
	अगर (fd >= 0) अणु
		अगर (ग_लिखो(fd, "1\n", 2) != 2)
			panic("write(exception-trace)");
		बंद(fd);
	पूर्ण
	fd = खोलो("/proc/sys/kernel/panic_on_warn", O_WRONLY);
	अगर (fd >= 0) अणु
		अगर (ग_लिखो(fd, "1\n", 2) != 2)
			panic("write(panic_on_warn)");
		बंद(fd);
	पूर्ण
पूर्ण

अटल व्योम kmod_selftests(व्योम)
अणु
	खाता *file;
	अक्षर line[2048], *start, *pass;
	bool success = true;
	pretty_message("[+] Module self-tests:");
	file = ख_खोलो("/proc/kmsg", "r");
	अगर (!file)
		panic("fopen(kmsg)");
	अगर (fcntl(fileno(file), F_SETFL, O_NONBLOCK) < 0)
		panic("fcntl(kmsg, nonblock)");
	जबतक (ख_माला_लो(line, माप(line), file)) अणु
		start = म_माला(line, "wireguard: ");
		अगर (!start)
			जारी;
		start += 11;
		*म_अक्षरnul(start, '\n') = '\0';
		अगर (म_माला(start, "www.wireguard.com"))
			अवरोध;
		pass = म_माला(start, ": pass");
		अगर (!pass || pass[6] != '\0') अणु
			success = false;
			म_लिखो(" \x1b[31m*  %s\x1b[0m\n", start);
		पूर्ण अन्यथा
			म_लिखो(" \x1b[32m*  %s\x1b[0m\n", start);
	पूर्ण
	ख_बंद(file);
	अगर (!success) अणु
		माला_दो("\x1b[31m\x1b[1m[-] Tests failed! \u2639\x1b[0m");
		घातeroff();
	पूर्ण
पूर्ण

अटल व्योम launch_tests(व्योम)
अणु
	अक्षर cmdline[4096], *success_dev;
	पूर्णांक status, fd;
	pid_t pid;

	pretty_message("[+] Launching tests...");
	pid = विभाजन();
	अगर (pid == -1)
		panic("fork");
	अन्यथा अगर (pid == 0) अणु
		execl("/init.sh", "init", शून्य);
		panic("exec");
	पूर्ण
	अगर (रुकोpid(pid, &status, 0) < 0)
		panic("waitpid");
	अगर (WIFEXITED(status) && WEXITSTATUS(status) == 0) अणु
		pretty_message("[+] Tests successful! :-)");
		fd = खोलो("/proc/cmdline", O_RDONLY);
		अगर (fd < 0)
			panic("open(/proc/cmdline)");
		अगर (पढ़ो(fd, cmdline, माप(cmdline) - 1) <= 0)
			panic("read(/proc/cmdline)");
		cmdline[माप(cmdline) - 1] = '\0';
		क्रम (success_dev = म_मोहर(cmdline, " \n"); success_dev; success_dev = म_मोहर(शून्य, " \n")) अणु
			अगर (म_भेदन(success_dev, "wg.success=", 11))
				जारी;
			स_नकल(success_dev + 11 - 5, "/dev/", 5);
			success_dev += 11 - 5;
			अवरोध;
		पूर्ण
		अगर (!success_dev || !म_माप(success_dev))
			panic("Unable to find success device");

		fd = खोलो(success_dev, O_WRONLY);
		अगर (fd < 0)
			panic("open(success_dev)");
		अगर (ग_लिखो(fd, "success\n", 8) != 8)
			panic("write(success_dev)");
		बंद(fd);
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *why = "unknown cause";
		पूर्णांक what = -1;

		अगर (WIFEXITED(status)) अणु
			why = "exit code";
			what = WEXITSTATUS(status);
		पूर्ण अन्यथा अगर (WIFSIGNALED(status)) अणु
			why = "signal";
			what = WTERMSIG(status);
		पूर्ण
		म_लिखो("\x1b[31m\x1b[1m[-] Tests failed with %s %d! \u2639\x1b[0m\n", why, what);
	पूर्ण
पूर्ण

अटल व्योम ensure_console(व्योम)
अणु
	क्रम (अचिन्हित पूर्णांक i = 0; i < 1000; ++i) अणु
		पूर्णांक fd = खोलो("/dev/console", O_RDWR);
		अगर (fd < 0) अणु
			usleep(50000);
			जारी;
		पूर्ण
		dup2(fd, 0);
		dup2(fd, 1);
		dup2(fd, 2);
		बंद(fd);
		अगर (ग_लिखो(1, "\0\0\0\0\n", 5) == 5)
			वापस;
	पूर्ण
	panic("Unable to open console device");
पूर्ण

अटल व्योम clear_leaks(व्योम)
अणु
	पूर्णांक fd;

	fd = खोलो("/sys/kernel/debug/kmemleak", O_WRONLY);
	अगर (fd < 0)
		वापस;
	pretty_message("[+] Starting memory leak detection...");
	ग_लिखो(fd, "clear\n", 5);
	बंद(fd);
पूर्ण

अटल व्योम check_leaks(व्योम)
अणु
	पूर्णांक fd;

	fd = खोलो("/sys/kernel/debug/kmemleak", O_WRONLY);
	अगर (fd < 0)
		वापस;
	pretty_message("[+] Scanning for memory leaks...");
	sleep(2); /* Wait क्रम any grace periods. */
	ग_लिखो(fd, "scan\n", 5);
	बंद(fd);

	fd = खोलो("/sys/kernel/debug/kmemleak", O_RDONLY);
	अगर (fd < 0)
		वापस;
	अगर (sendfile(1, fd, शून्य, 0x7ffff000) > 0)
		panic("Memory leaks encountered");
	बंद(fd);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	seed_rng();
	ensure_console();
	prपूर्णांक_banner();
	mount_fileप्रणालीs();
	kmod_selftests();
	enable_logging();
	clear_leaks();
	launch_tests();
	check_leaks();
	घातeroff();
	वापस 1;
पूर्ण
