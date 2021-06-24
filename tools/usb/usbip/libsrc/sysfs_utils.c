<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>

#समावेश "sysfs_utils.h"
#समावेश "usbip_common.h"

पूर्णांक ग_लिखो_sysfs_attribute(स्थिर अक्षर *attr_path, स्थिर अक्षर *new_value,
			  माप_प्रकार len)
अणु
	पूर्णांक fd;
	पूर्णांक length;

	fd = खोलो(attr_path, O_WRONLY);
	अगर (fd < 0) अणु
		dbg("error opening attribute %s", attr_path);
		वापस -1;
	पूर्ण

	length = ग_लिखो(fd, new_value, len);
	अगर (length < 0) अणु
		dbg("error writing to attribute %s", attr_path);
		बंद(fd);
		वापस -1;
	पूर्ण

	बंद(fd);

	वापस 0;
पूर्ण
