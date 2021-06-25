<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <linux/fs.h>

अटल पूर्णांक set_immutable(स्थिर अक्षर *path, पूर्णांक immutable)
अणु
	अचिन्हित पूर्णांक flags;
	पूर्णांक fd;
	पूर्णांक rc;
	पूर्णांक error;

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0)
		वापस fd;

	rc = ioctl(fd, FS_IOC_GETFLAGS, &flags);
	अगर (rc < 0) अणु
		error = त्रुटि_सं;
		बंद(fd);
		त्रुटि_सं = error;
		वापस rc;
	पूर्ण

	अगर (immutable)
		flags |= FS_IMMUTABLE_FL;
	अन्यथा
		flags &= ~FS_IMMUTABLE_FL;

	rc = ioctl(fd, FS_IOC_SETFLAGS, &flags);
	error = त्रुटि_सं;
	बंद(fd);
	त्रुटि_सं = error;
	वापस rc;
पूर्ण

अटल पूर्णांक get_immutable(स्थिर अक्षर *path)
अणु
	अचिन्हित पूर्णांक flags;
	पूर्णांक fd;
	पूर्णांक rc;
	पूर्णांक error;

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0)
		वापस fd;

	rc = ioctl(fd, FS_IOC_GETFLAGS, &flags);
	अगर (rc < 0) अणु
		error = त्रुटि_सं;
		बंद(fd);
		त्रुटि_सं = error;
		वापस rc;
	पूर्ण
	बंद(fd);
	अगर (flags & FS_IMMUTABLE_FL)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *path;
	अक्षर buf[5];
	पूर्णांक fd, rc;

	अगर (argc < 2) अणु
		ख_लिखो(मानक_त्रुटि, "usage: %s <path>\n", argv[0]);
		वापस निकास_त्रुटि;
	पूर्ण

	path = argv[1];

	/* attributes: EFI_VARIABLE_NON_VOLATILE |
	 *		EFI_VARIABLE_BOOTSERVICE_ACCESS |
	 *		EFI_VARIABLE_RUNTIME_ACCESS
	 */
	*(uपूर्णांक32_t *)buf = 0x7;
	buf[4] = 0;

	/* create a test variable */
	fd = खोलो(path, O_WRONLY | O_CREAT, 0600);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("open(O_WRONLY)");
		वापस निकास_त्रुटि;
	पूर्ण

	rc = ग_लिखो(fd, buf, माप(buf));
	अगर (rc != माप(buf)) अणु
		लिखो_त्रुटि("write");
		वापस निकास_त्रुटि;
	पूर्ण

	बंद(fd);

	rc = get_immutable(path);
	अगर (rc < 0) अणु
		लिखो_त्रुटि("ioctl(FS_IOC_GETFLAGS)");
		वापस निकास_त्रुटि;
	पूर्ण अन्यथा अगर (rc) अणु
		rc = set_immutable(path, 0);
		अगर (rc < 0) अणु
			लिखो_त्रुटि("ioctl(FS_IOC_SETFLAGS)");
			वापस निकास_त्रुटि;
		पूर्ण
	पूर्ण

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("open");
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (unlink(path) < 0) अणु
		लिखो_त्रुटि("unlink");
		वापस निकास_त्रुटि;
	पूर्ण

	rc = पढ़ो(fd, buf, माप(buf));
	अगर (rc > 0) अणु
		ख_लिखो(मानक_त्रुटि, "reading from an unlinked variable "
				"shouldn't be possible\n");
		वापस निकास_त्रुटि;
	पूर्ण

	वापस निकास_सफल;
पूर्ण
