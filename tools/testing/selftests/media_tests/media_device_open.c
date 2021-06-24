<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * media_device_खोलो.c - Media Controller Device Open Test
 *
 * Copyright (c) 2016 Shuah Khan <shuahkh@osg.samsung.com>
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 *
 */

/*
 * This file adds a test क्रम Media Controller API.
 * This test should be run as root and should not be
 * included in the Kselftest run. This test should be
 * run when hardware and driver that makes use Media
 * Controller API are present in the प्रणाली.
 *
 * This test खोलोs user specअगरied Media Device and calls
 * MEDIA_IOC_DEVICE_INFO ioctl, बंदs the file, and निकासs.
 *
 * Usage:
 *	suकरो ./media_device_खोलो -d /dev/mediaX
 *
 *	Run this test is a loop and run bind/unbind on the driver.
*/

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/media.h>

#समावेश "../kselftest.h"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt;
	अक्षर media_device[256];
	पूर्णांक count = 0;
	काष्ठा media_device_info mdi;
	पूर्णांक ret;
	पूर्णांक fd;

	अगर (argc < 2) अणु
		म_लिखो("Usage: %s [-d </dev/mediaX>]\n", argv[0]);
		निकास(-1);
	पूर्ण

	/* Process arguments */
	जबतक ((opt = getopt(argc, argv, "d:")) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			म_नकलन(media_device, optarg, माप(media_device) - 1);
			media_device[माप(media_device)-1] = '\0';
			अवरोध;
		शेष:
			म_लिखो("Usage: %s [-d </dev/mediaX>]\n", argv[0]);
			निकास(-1);
		पूर्ण
	पूर्ण

	अगर (getuid() != 0)
		ksft_निकास_skip("Please run the test as root - Exiting.\n");

	/* Open Media device and keep it खोलो */
	fd = खोलो(media_device, O_RDWR);
	अगर (fd == -1) अणु
		म_लिखो("Media Device open errno %s\n", म_त्रुटि(त्रुटि_सं));
		निकास(-1);
	पूर्ण

	ret = ioctl(fd, MEDIA_IOC_DEVICE_INFO, &mdi);
	अगर (ret < 0)
		म_लिखो("Media Device Info errno %s\n", म_त्रुटि(त्रुटि_सं));
	अन्यथा
		म_लिखो("Media device model %s driver %s\n",
			mdi.model, mdi.driver);
पूर्ण
