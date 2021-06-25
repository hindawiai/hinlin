<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mount.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <linux/android/binder.h>
#समावेश <linux/android/binderfs.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक fd, ret, saved_त्रुटि_सं;
	काष्ठा binderfs_device device = अणु 0 पूर्ण;

	ret = unshare(CLONE_NEWNS);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to unshare mount namespace\n",
			म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = mount(शून्य, "/", शून्य, MS_REC | MS_PRIVATE, 0);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to mount / as private\n",
			म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = सूची_गढ़ो("/dev/binderfs", 0755);
	अगर (ret < 0 && त्रुटि_सं != EEXIST) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to create binderfs mountpoint\n",
			म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = mount(शून्य, "/dev/binderfs", "binder", 0, 0);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to mount binderfs\n",
			म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	स_नकल(device.name, "my-binder", म_माप("my-binder"));

	fd = खोलो("/dev/binderfs/binder-control", O_RDONLY | O_CLOEXEC);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to open binder-control device\n",
			म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = ioctl(fd, BINDER_CTL_ADD, &device);
	saved_त्रुटि_सं = त्रुटि_सं;
	बंद(fd);
	त्रुटि_सं = saved_त्रुटि_सं;
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to allocate new binder device\n",
			म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	म_लिखो("Allocated new binder device with major %d, minor %d, and name %s\n",
	       device.major, device.minor, device.name);

	ret = unlink("/dev/binderfs/my-binder");
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s - Failed to delete binder device\n",
			म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Cleanup happens when the mount namespace dies. */
	निकास(निकास_सफल);
पूर्ण
