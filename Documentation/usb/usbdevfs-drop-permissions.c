<शैली गुरु>
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <unistd.h>

#समावेश <linux/usbdevice_fs.h>

/* For building without an updated set of headers */
#अगर_अघोषित USBDEVFS_DROP_PRIVILEGES
#घोषणा USBDEVFS_DROP_PRIVILEGES		_IOW('U', 30, __u32)
#घोषणा USBDEVFS_CAP_DROP_PRIVILEGES		0x40
#पूर्ण_अगर

व्योम drop_privileges(पूर्णांक fd, uपूर्णांक32_t mask)
अणु
	पूर्णांक res;

	res = ioctl(fd, USBDEVFS_DROP_PRIVILEGES, &mask);
	अगर (res)
		म_लिखो("ERROR: USBDEVFS_DROP_PRIVILEGES returned %d\n", res);
	अन्यथा
		म_लिखो("OK: privileges dropped!\n");
पूर्ण

व्योम reset_device(पूर्णांक fd)
अणु
	पूर्णांक res;

	res = ioctl(fd, USBDEVFS_RESET);
	अगर (!res)
		म_लिखो("OK: USBDEVFS_RESET succeeded\n");
	अन्यथा
		म_लिखो("ERROR: reset failed! (%d - %s)\n",
		       -res, म_त्रुटि(-res));
पूर्ण

व्योम claim_some_पूर्णांकf(पूर्णांक fd)
अणु
	पूर्णांक i, res;

	क्रम (i = 0; i < 4; i++) अणु
		res = ioctl(fd, USBDEVFS_CLAIMINTERFACE, &i);
		अगर (!res)
			म_लिखो("OK: claimed if %d\n", i);
		अन्यथा
			म_लिखो("ERROR claiming if %d (%d - %s)\n",
			       i, -res, म_त्रुटि(-res));
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	uपूर्णांक32_t mask, caps;
	पूर्णांक c, fd;

	fd = खोलो(argv[1], O_RDWR);
	अगर (fd < 0) अणु
		म_लिखो("Failed to open file\n");
		जाओ err_fd;
	पूर्ण

	/*
	 * check अगर dropping privileges is supported,
	 * bail on प्रणालीs where the capability is not present
	 */
	ioctl(fd, USBDEVFS_GET_CAPABILITIES, &caps);
	अगर (!(caps & USBDEVFS_CAP_DROP_PRIVILEGES)) अणु
		म_लिखो("DROP_PRIVILEGES not supported\n");
		जाओ err;
	पूर्ण

	/*
	 * Drop privileges but keep the ability to claim all
	 * मुक्त पूर्णांकerfaces (i.e., those not used by kernel drivers)
	 */
	drop_privileges(fd, -1U);

	म_लिखो("Available options:\n"
		"[0] Exit now\n"
		"[1] Reset device. Should fail if device is in use\n"
		"[2] Claim 4 interfaces. Should succeed where not in use\n"
		"[3] Narrow interface permission mask\n"
		"Which option shall I run?: ");

	जबतक (म_पूछो("%d", &c) == 1) अणु
		चयन (c) अणु
		हाल 0:
			जाओ निकास;
		हाल 1:
			reset_device(fd);
			अवरोध;
		हाल 2:
			claim_some_पूर्णांकf(fd);
			अवरोध;
		हाल 3:
			म_लिखो("Insert new mask: ");
			म_पूछो("%x", &mask);
			drop_privileges(fd, mask);
			अवरोध;
		शेष:
			म_लिखो("I don't recognize that\n");
		पूर्ण

		म_लिखो("Which test shall I run next?: ");
	पूर्ण

निकास:
	बंद(fd);
	वापस 0;

err:
	बंद(fd);
err_fd:
	वापस 1;
पूर्ण
