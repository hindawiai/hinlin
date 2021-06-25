<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * video_device_test - Video Device Test
 *
 * Copyright (c) 2016 Shuah Khan <shuahkh@osg.samsung.com>
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 *
 */

/*
 * This file adds a test क्रम Video Device. This test should not be included
 * in the Kselftest run. This test should be run when hardware and driver
 * that makes use of V4L2 API is present.
 *
 * This test खोलोs user specअगरied Video Device and calls video ioctls in a
 * loop once every 10 seconds.
 *
 * Usage:
 *	suकरो ./video_device_test -d /dev/videoX
 *
 *	While test is running, हटाओ the device or unbind the driver and
 *	ensure there are no use after मुक्त errors and other Oops in the
 *	dmesg.
 *	When possible, enable KaSan kernel config option क्रम use-after-मुक्त
 *	error detection.
*/

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <समय.स>
#समावेश <linux/videodev2.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt;
	अक्षर video_dev[256];
	पूर्णांक count;
	काष्ठा v4l2_tuner vtuner;
	काष्ठा v4l2_capability vcap;
	पूर्णांक ret;
	पूर्णांक fd;

	अगर (argc < 2) अणु
		म_लिखो("Usage: %s [-d </dev/videoX>]\n", argv[0]);
		निकास(-1);
	पूर्ण

	/* Process arguments */
	जबतक ((opt = getopt(argc, argv, "d:")) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			म_नकलन(video_dev, optarg, माप(video_dev) - 1);
			video_dev[माप(video_dev)-1] = '\0';
			अवरोध;
		शेष:
			म_लिखो("Usage: %s [-d </dev/videoX>]\n", argv[0]);
			निकास(-1);
		पूर्ण
	पूर्ण

	/* Generate अक्रमom number of पूर्णांकerations */
	बेक्रम((अचिन्हित पूर्णांक) समय(शून्य));
	count = अक्रम();

	/* Open Video device and keep it खोलो */
	fd = खोलो(video_dev, O_RDWR);
	अगर (fd == -1) अणु
		म_लिखो("Video Device open errno %s\n", म_त्रुटि(त्रुटि_सं));
		निकास(-1);
	पूर्ण

	म_लिखो("\nNote:\n"
	       "While test is running, remove the device or unbind\n"
	       "driver and ensure there are no use after free errors\n"
	       "and other Oops in the dmesg. When possible, enable KaSan\n"
	       "kernel config option for use-after-free error detection.\n\n");

	जबतक (count > 0) अणु
		ret = ioctl(fd, VIDIOC_QUERYCAP, &vcap);
		अगर (ret < 0)
			म_लिखो("VIDIOC_QUERYCAP errno %s\n", म_त्रुटि(त्रुटि_सं));
		अन्यथा
			म_लिखो("Video device driver %s\n", vcap.driver);

		ret = ioctl(fd, VIDIOC_G_TUNER, &vtuner);
		अगर (ret < 0)
			म_लिखो("VIDIOC_G_TUNER, errno %s\n", म_त्रुटि(त्रुटि_सं));
		अन्यथा
			म_लिखो("type %d rangelow %d rangehigh %d\n",
				vtuner.type, vtuner.rangelow, vtuner.rangehigh);
		sleep(10);
		count--;
	पूर्ण
पूर्ण
