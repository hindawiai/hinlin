<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानकघोष.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <sys/vfs.h>
#समावेश <linux/magic.h>
#समावेश <init.h>
#समावेश <os.h>

/* Set by make_tempfile() during early boot. */
अटल अक्षर *tempdir = शून्य;

/* Check अगर dir is on पंचांगpfs. Return 0 अगर yes, -1 अगर no or error. */
अटल पूर्णांक __init check_पंचांगpfs(स्थिर अक्षर *dir)
अणु
	काष्ठा statfs st;

	os_info("Checking if %s is on tmpfs...", dir);
	अगर (statfs(dir, &st) < 0) अणु
		os_info("%s\n", म_त्रुटि(त्रुटि_सं));
	पूर्ण अन्यथा अगर (st.f_type != TMPFS_MAGIC) अणु
		os_info("no\n");
	पूर्ण अन्यथा अणु
		os_info("OK\n");
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

/*
 * Choose the tempdir to use. We want something on पंचांगpfs so that our memory is
 * not subject to the host's vm.dirty_ratio. If a tempdir is specअगरied in the
 * environment, we use that even अगर it's not on पंचांगpfs, but we warn the user.
 * Otherwise, we try common पंचांगpfs locations, and अगर no पंचांगpfs directory is found
 * then we fall back to /पंचांगp.
 */
अटल अक्षर * __init choose_tempdir(व्योम)
अणु
	अटल स्थिर अक्षर * स्थिर vars[] = अणु
		"TMPDIR",
		"TMP",
		"TEMP",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर fallback_dir[] = "/tmp";
	अटल स्थिर अक्षर * स्थिर पंचांगpfs_dirs[] = अणु
		"/dev/shm",
		fallback_dir,
		शून्य
	पूर्ण;
	पूर्णांक i;
	स्थिर अक्षर *dir;

	os_info("Checking environment variables for a tempdir...");
	क्रम (i = 0; vars[i]; i++) अणु
		dir = दो_पर्या(vars[i]);
		अगर ((dir != शून्य) && (*dir != '\0')) अणु
			os_info("%s\n", dir);
			अगर (check_पंचांगpfs(dir) >= 0)
				जाओ करोne;
			अन्यथा
				जाओ warn;
		पूर्ण
	पूर्ण
	os_info("none found\n");

	क्रम (i = 0; पंचांगpfs_dirs[i]; i++) अणु
		dir = पंचांगpfs_dirs[i];
		अगर (check_पंचांगpfs(dir) >= 0)
			जाओ करोne;
	पूर्ण

	dir = fallback_dir;
warn:
	os_warn("Warning: tempdir %s is not on tmpfs\n", dir);
करोne:
	/* Make a copy since दो_पर्या results may not reमुख्य valid क्रमever. */
	वापस strdup(dir);
पूर्ण

/*
 * Create an unlinked tempfile in a suitable tempdir. ढाँचा must be the
 * basename part of the ढाँचा with a leading '/'.
 */
अटल पूर्णांक __init make_tempfile(स्थिर अक्षर *ढाँचा)
अणु
	अक्षर *tempname;
	पूर्णांक fd;

	अगर (tempdir == शून्य) अणु
		tempdir = choose_tempdir();
		अगर (tempdir == शून्य) अणु
			os_warn("Failed to choose tempdir: %s\n",
				म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण
	पूर्ण

#अगर_घोषित O_TMPखाता
	fd = खोलो(tempdir, O_CLOEXEC | O_RDWR | O_EXCL | O_TMPखाता, 0700);
	/*
	 * If the running प्रणाली करोes not support O_TMPखाता flag then retry
	 * without it.
	 */
	अगर (fd != -1 || (त्रुटि_सं != EINVAL && त्रुटि_सं != EISसूची &&
			त्रुटि_सं != EOPNOTSUPP))
		वापस fd;
#पूर्ण_अगर

	tempname = दो_स्मृति(म_माप(tempdir) + म_माप(ढाँचा) + 1);
	अगर (tempname == शून्य)
		वापस -1;

	म_नकल(tempname, tempdir);
	म_जोड़ो(tempname, ढाँचा);
	fd = mkstemp(tempname);
	अगर (fd < 0) अणु
		os_warn("open - cannot create %s: %s\n", tempname,
			म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण
	अगर (unlink(tempname) < 0) अणु
		लिखो_त्रुटि("unlink");
		जाओ बंद;
	पूर्ण
	मुक्त(tempname);
	वापस fd;
बंद:
	बंद(fd);
out:
	मुक्त(tempname);
	वापस -1;
पूर्ण

#घोषणा TEMPNAME_TEMPLATE "/vm_file-XXXXXX"

अटल पूर्णांक __init create_पंचांगp_file(अचिन्हित दीर्घ दीर्घ len)
अणु
	पूर्णांक fd, err;
	अक्षर zero;

	fd = make_tempfile(TEMPNAME_TEMPLATE);
	अगर (fd < 0)
		निकास(1);

	/*
	 * Seek to len - 1 because writing a अक्षरacter there will
	 * increase the file size by one byte, to the desired length.
	 */
	अगर (lseek64(fd, len - 1, शुरू_से) < 0) अणु
		लिखो_त्रुटि("lseek64");
		निकास(1);
	पूर्ण

	zero = 0;

	err = ग_लिखो(fd, &zero, 1);
	अगर (err != 1) अणु
		लिखो_त्रुटि("write");
		निकास(1);
	पूर्ण

	वापस fd;
पूर्ण

पूर्णांक __init create_mem_file(अचिन्हित दीर्घ दीर्घ len)
अणु
	पूर्णांक err, fd;

	fd = create_पंचांगp_file(len);

	err = os_set_exec_बंद(fd);
	अगर (err < 0) अणु
		त्रुटि_सं = -err;
		लिखो_त्रुटि("exec_close");
	पूर्ण
	वापस fd;
पूर्ण

व्योम __init check_पंचांगpexec(व्योम)
अणु
	व्योम *addr;
	पूर्णांक err, fd = create_पंचांगp_file(UM_KERN_PAGE_SIZE);

	addr = mmap(शून्य, UM_KERN_PAGE_SIZE,
		    PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
	os_info("Checking PROT_EXEC mmap in %s...", tempdir);
	अगर (addr == MAP_FAILED) अणु
		err = त्रुटि_सं;
		os_warn("%s\n", म_त्रुटि(err));
		बंद(fd);
		अगर (err == EPERM)
			os_warn("%s must be not mounted noexec\n", tempdir);
		निकास(1);
	पूर्ण
	os_info("OK\n");
	munmap(addr, UM_KERN_PAGE_SIZE);

	बंद(fd);
पूर्ण
