<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Sample application क्रम SMBIOS communication over WMI पूर्णांकerface
 *  Perक्रमms the following:
 *  - Simple cmd_class/cmd_select lookup क्रम TPM inक्रमmation
 *  - Simple query of known tokens and their values
 *  - Simple activation of a token
 *
 *  Copyright (C) 2017 Dell, Inc.
 */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/ioctl.h>
#समावेश <unistd.h>

/* अगर uapi header isn't installed, this might not yet exist */
#अगर_अघोषित __packed
#घोषणा __packed __attribute__((packed))
#पूर्ण_अगर
#समावेश <linux/wmi.h>

/* It would be better to discover these using udev, but क्रम a simple
 * application they're hardcoded
 */
अटल स्थिर अक्षर *ioctl_devfs = "/dev/wmi/dell-smbios";
अटल स्थिर अक्षर *token_sysfs =
			"/sys/bus/platform/devices/dell-smbios.0/tokens";

अटल व्योम show_buffer(काष्ठा dell_wmi_smbios_buffer *buffer)
अणु
	म_लिखो("Call: %x/%x [%x,%x,%x,%x]\nResults: [%8x,%8x,%8x,%8x]\n",
	buffer->std.cmd_class, buffer->std.cmd_select,
	buffer->std.input[0], buffer->std.input[1],
	buffer->std.input[2], buffer->std.input[3],
	buffer->std.output[0], buffer->std.output[1],
	buffer->std.output[2], buffer->std.output[3]);
पूर्ण

अटल पूर्णांक run_wmi_smbios_cmd(काष्ठा dell_wmi_smbios_buffer *buffer)
अणु
	पूर्णांक fd;
	पूर्णांक ret;

	fd = खोलो(ioctl_devfs, O_NONBLOCK);
	ret = ioctl(fd, DELL_WMI_SMBIOS_CMD, buffer);
	बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक find_token(__u16 token, __u16 *location, __u16 *value)
अणु
	अक्षर location_sysfs[60];
	अक्षर value_sysfs[57];
	अक्षर buf[4096];
	खाता *f;
	पूर्णांक ret;

	ret = प्र_लिखो(value_sysfs, "%s/%04x_value", token_sysfs, token);
	अगर (ret < 0) अणु
		म_लिखो("sprintf value failed\n");
		वापस 2;
	पूर्ण
	f = ख_खोलो(value_sysfs, "rb");
	अगर (!f) अणु
		म_लिखो("failed to open %s\n", value_sysfs);
		वापस 2;
	पूर्ण
	ख_पढ़ो(buf, 1, 4096, f);
	ख_बंद(f);
	*value = (__u16) म_से_दीर्घ(buf, शून्य, 16);

	ret = प्र_लिखो(location_sysfs, "%s/%04x_location", token_sysfs, token);
	अगर (ret < 0) अणु
		म_लिखो("sprintf location failed\n");
		वापस 1;
	पूर्ण
	f = ख_खोलो(location_sysfs, "rb");
	अगर (!f) अणु
		म_लिखो("failed to open %s\n", location_sysfs);
		वापस 2;
	पूर्ण
	ख_पढ़ो(buf, 1, 4096, f);
	ख_बंद(f);
	*location = (__u16) म_से_दीर्घ(buf, शून्य, 16);

	अगर (*location)
		वापस 0;
	वापस 2;
पूर्ण

अटल पूर्णांक token_is_active(__u16 *location, __u16 *cmpvalue,
			   काष्ठा dell_wmi_smbios_buffer *buffer)
अणु
	पूर्णांक ret;

	buffer->std.cmd_class = CLASS_TOKEN_READ;
	buffer->std.cmd_select = SELECT_TOKEN_STD;
	buffer->std.input[0] = *location;
	ret = run_wmi_smbios_cmd(buffer);
	अगर (ret != 0 || buffer->std.output[0] != 0)
		वापस ret;
	ret = (buffer->std.output[1] == *cmpvalue);
	वापस ret;
पूर्ण

अटल पूर्णांक query_token(__u16 token, काष्ठा dell_wmi_smbios_buffer *buffer)
अणु
	__u16 location;
	__u16 value;
	पूर्णांक ret;

	ret = find_token(token, &location, &value);
	अगर (ret != 0) अणु
		म_लिखो("unable to find token %04x\n", token);
		वापस 1;
	पूर्ण
	वापस token_is_active(&location, &value, buffer);
पूर्ण

अटल पूर्णांक activate_token(काष्ठा dell_wmi_smbios_buffer *buffer,
		   __u16 token)
अणु
	__u16 location;
	__u16 value;
	पूर्णांक ret;

	ret = find_token(token, &location, &value);
	अगर (ret != 0) अणु
		म_लिखो("unable to find token %04x\n", token);
		वापस 1;
	पूर्ण
	buffer->std.cmd_class = CLASS_TOKEN_WRITE;
	buffer->std.cmd_select = SELECT_TOKEN_STD;
	buffer->std.input[0] = location;
	buffer->std.input[1] = 1;
	ret = run_wmi_smbios_cmd(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक query_buffer_size(__u64 *buffer_size)
अणु
	खाता *f;

	f = ख_खोलो(ioctl_devfs, "rb");
	अगर (!f)
		वापस -EINVAL;
	ख_पढ़ो(buffer_size, माप(__u64), 1, f);
	ख_बंद(f);
	वापस निकास_सफल;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा dell_wmi_smbios_buffer *buffer;
	पूर्णांक ret;
	__u64 value = 0;

	ret = query_buffer_size(&value);
	अगर (ret == निकास_त्रुटि || !value) अणु
		म_लिखो("Unable to read buffer size\n");
		जाओ out;
	पूर्ण
	म_लिखो("Detected required buffer size %lld\n", value);

	buffer = दो_स्मृति(value);
	अगर (buffer == शून्य) अणु
		म_लिखो("failed to alloc memory for ioctl\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	buffer->length = value;

	/* simple SMBIOS call क्रम looking up TPM info */
	buffer->std.cmd_class = CLASS_FLASH_INTERFACE;
	buffer->std.cmd_select = SELECT_FLASH_INTERFACE;
	buffer->std.input[0] = 2;
	ret = run_wmi_smbios_cmd(buffer);
	अगर (ret) अणु
		म_लिखो("smbios ioctl failed: %d\n", ret);
		ret = निकास_त्रुटि;
		जाओ out;
	पूर्ण
	show_buffer(buffer);

	/* query some tokens */
	ret = query_token(CAPSULE_EN_TOKEN, buffer);
	म_लिखो("UEFI Capsule enabled token is: %d\n", ret);
	ret = query_token(CAPSULE_DIS_TOKEN, buffer);
	म_लिखो("UEFI Capsule disabled token is: %d\n", ret);

	/* activate UEFI capsule token अगर disabled */
	अगर (ret) अणु
		म_लिखो("Enabling UEFI capsule token");
		अगर (activate_token(buffer, CAPSULE_EN_TOKEN)) अणु
			म_लिखो("activate failed\n");
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण
	ret = निकास_सफल;
out:
	मुक्त(buffer);
	वापस ret;
पूर्ण
