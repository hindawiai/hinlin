<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Sample code to test CAP protocol
 *
 * Copyright(c) 2016 Google Inc. All rights reserved.
 * Copyright(c) 2016 Linaro Ltd. All rights reserved.
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#समावेश "../../greybus_authentication.h"

काष्ठा cap_ioc_get_endpoपूर्णांक_uid uid;
काष्ठा cap_ioc_get_ims_certअगरicate cert = अणु
	.certअगरicate_class = 0,
	.certअगरicate_id = 0,
पूर्ण;

काष्ठा cap_ioc_authenticate authenticate = अणु
	.auth_type = 0,
	.challenge = अणु0पूर्ण,
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित पूर्णांक समयout = 10000;
	अक्षर *capdev;
	पूर्णांक fd, ret;

	/* Make sure arguments are correct */
	अगर (argc != 2) अणु
		म_लिखो("\nUsage: ./firmware <Path of the gb-cap-X dev>\n");
		वापस 0;
	पूर्ण

	capdev = argv[1];

	म_लिखो("Opening %s authentication device\n", capdev);

	fd = खोलो(capdev, O_RDWR);
	अगर (fd < 0) अणु
		म_लिखो("Failed to open: %s\n", capdev);
		वापस -1;
	पूर्ण

	/* Get UID */
	म_लिखो("Get UID\n");

	ret = ioctl(fd, CAP_IOC_GET_ENDPOINT_UID, &uid);
	अगर (ret < 0) अणु
		म_लिखो("Failed to get UID: %s (%d)\n", capdev, ret);
		ret = -1;
		जाओ बंद_fd;
	पूर्ण

	म_लिखो("UID received: 0x%llx\n", *(अचिन्हित दीर्घ दीर्घ पूर्णांक *)(uid.uid));

	/* Get certअगरicate */
	म_लिखो("Get IMS certificate\n");

	ret = ioctl(fd, CAP_IOC_GET_IMS_CERTIFICATE, &cert);
	अगर (ret < 0) अणु
		म_लिखो("Failed to get IMS certificate: %s (%d)\n", capdev, ret);
		ret = -1;
		जाओ बंद_fd;
	पूर्ण

	म_लिखो("IMS Certificate size: %d\n", cert.cert_size);

	/* Authenticate */
	म_लिखो("Authenticate module\n");

	स_नकल(authenticate.uid, uid.uid, 8);

	ret = ioctl(fd, CAP_IOC_AUTHENTICATE, &authenticate);
	अगर (ret < 0) अणु
		म_लिखो("Failed to authenticate module: %s (%d)\n", capdev, ret);
		ret = -1;
		जाओ बंद_fd;
	पूर्ण

	म_लिखो("Authenticated, result (%02x), sig-size (%02x)\n",
		authenticate.result_code, authenticate.signature_size);

बंद_fd:
	बंद(fd);

	वापस ret;
पूर्ण
