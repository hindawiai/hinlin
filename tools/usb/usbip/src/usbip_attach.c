<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#समावेश <sys/स्थिति.स>

#समावेश <सीमा.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश <fcntl.h>
#समावेश <getopt.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>

#समावेश "vhci_driver.h"
#समावेश "usbip_common.h"
#समावेश "usbip_network.h"
#समावेश "usbip.h"

अटल स्थिर अक्षर usbip_attach_usage_string[] =
	"usbip attach <args>\n"
	"    -r, --remote=<host>      The machine with exported USB devices\n"
	"    -b, --busid=<busid>    Busid of the device on <host>\n"
	"    -d, --device=<devid>    Id of the virtual UDC on <host>\n";

व्योम usbip_attach_usage(व्योम)
अणु
	म_लिखो("usage: %s", usbip_attach_usage_string);
पूर्ण

#घोषणा MAX_BUFF 100
अटल पूर्णांक record_connection(अक्षर *host, अक्षर *port, अक्षर *busid, पूर्णांक rhport)
अणु
	पूर्णांक fd;
	अक्षर path[PATH_MAX+1];
	अक्षर buff[MAX_BUFF+1];
	पूर्णांक ret;

	ret = सूची_गढ़ो(VHCI_STATE_PATH, 0700);
	अगर (ret < 0) अणु
		/* अगर VHCI_STATE_PATH exists, then it better be a directory */
		अगर (त्रुटि_सं == EEXIST) अणु
			काष्ठा stat s;

			ret = stat(VHCI_STATE_PATH, &s);
			अगर (ret < 0)
				वापस -1;
			अगर (!(s.st_mode & S_IFसूची))
				वापस -1;
		पूर्ण अन्यथा
			वापस -1;
	पूर्ण

	snम_लिखो(path, PATH_MAX, VHCI_STATE_PATH"/port%d", rhport);

	fd = खोलो(path, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
	अगर (fd < 0)
		वापस -1;

	snम_लिखो(buff, MAX_BUFF, "%s %s %s\n",
			host, port, busid);

	ret = ग_लिखो(fd, buff, म_माप(buff));
	अगर (ret != (sमाप_प्रकार) म_माप(buff)) अणु
		बंद(fd);
		वापस -1;
	पूर्ण

	बंद(fd);

	वापस 0;
पूर्ण

अटल पूर्णांक import_device(पूर्णांक sockfd, काष्ठा usbip_usb_device *udev)
अणु
	पूर्णांक rc;
	पूर्णांक port;
	uपूर्णांक32_t speed = udev->speed;

	rc = usbip_vhci_driver_खोलो();
	अगर (rc < 0) अणु
		err("open vhci_driver");
		जाओ err_out;
	पूर्ण

	करो अणु
		port = usbip_vhci_get_मुक्त_port(speed);
		अगर (port < 0) अणु
			err("no free port");
			जाओ err_driver_बंद;
		पूर्ण

		dbg("got free port %d", port);

		rc = usbip_vhci_attach_device(port, sockfd, udev->busnum,
					      udev->devnum, udev->speed);
		अगर (rc < 0 && त्रुटि_सं != EBUSY) अणु
			err("import device");
			जाओ err_driver_बंद;
		पूर्ण
	पूर्ण जबतक (rc < 0);

	usbip_vhci_driver_बंद();

	वापस port;

err_driver_बंद:
	usbip_vhci_driver_बंद();
err_out:
	वापस -1;
पूर्ण

अटल पूर्णांक query_import_device(पूर्णांक sockfd, अक्षर *busid)
अणु
	पूर्णांक rc;
	काष्ठा op_import_request request;
	काष्ठा op_import_reply   reply;
	uपूर्णांक16_t code = OP_REP_IMPORT;
	पूर्णांक status;

	स_रखो(&request, 0, माप(request));
	स_रखो(&reply, 0, माप(reply));

	/* send a request */
	rc = usbip_net_send_op_common(sockfd, OP_REQ_IMPORT, 0);
	अगर (rc < 0) अणु
		err("send op_common");
		वापस -1;
	पूर्ण

	म_नकलन(request.busid, busid, SYSFS_BUS_ID_SIZE-1);

	PACK_OP_IMPORT_REQUEST(0, &request);

	rc = usbip_net_send(sockfd, (व्योम *) &request, माप(request));
	अगर (rc < 0) अणु
		err("send op_import_request");
		वापस -1;
	पूर्ण

	/* receive a reply */
	rc = usbip_net_recv_op_common(sockfd, &code, &status);
	अगर (rc < 0) अणु
		err("Attach Request for %s failed - %s\n",
		    busid, usbip_op_common_status_string(status));
		वापस -1;
	पूर्ण

	rc = usbip_net_recv(sockfd, (व्योम *) &reply, माप(reply));
	अगर (rc < 0) अणु
		err("recv op_import_reply");
		वापस -1;
	पूर्ण

	PACK_OP_IMPORT_REPLY(0, &reply);

	/* check the reply */
	अगर (म_भेदन(reply.udev.busid, busid, SYSFS_BUS_ID_SIZE)) अणु
		err("recv different busid %s", reply.udev.busid);
		वापस -1;
	पूर्ण

	/* import a device */
	वापस import_device(sockfd, &reply.udev);
पूर्ण

अटल पूर्णांक attach_device(अक्षर *host, अक्षर *busid)
अणु
	पूर्णांक sockfd;
	पूर्णांक rc;
	पूर्णांक rhport;

	sockfd = usbip_net_tcp_connect(host, usbip_port_string);
	अगर (sockfd < 0) अणु
		err("tcp connect");
		वापस -1;
	पूर्ण

	rhport = query_import_device(sockfd, busid);
	अगर (rhport < 0)
		वापस -1;

	बंद(sockfd);

	rc = record_connection(host, usbip_port_string, busid, rhport);
	अगर (rc < 0) अणु
		err("record connection");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक usbip_attach(पूर्णांक argc, अक्षर *argv[])
अणु
	अटल स्थिर काष्ठा option opts[] = अणु
		अणु "remote", required_argument, शून्य, 'r' पूर्ण,
		अणु "busid",  required_argument, शून्य, 'b' पूर्ण,
		अणु "device",  required_argument, शून्य, 'd' पूर्ण,
		अणु शून्य, 0,  शून्य, 0 पूर्ण
	पूर्ण;
	अक्षर *host = शून्य;
	अक्षर *busid = शून्य;
	पूर्णांक opt;
	पूर्णांक ret = -1;

	क्रम (;;) अणु
		opt = getopt_दीर्घ(argc, argv, "d:r:b:", opts, शून्य);

		अगर (opt == -1)
			अवरोध;

		चयन (opt) अणु
		हाल 'r':
			host = optarg;
			अवरोध;
		हाल 'd':
		हाल 'b':
			busid = optarg;
			अवरोध;
		शेष:
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (!host || !busid)
		जाओ err_out;

	ret = attach_device(host, busid);
	जाओ out;

err_out:
	usbip_attach_usage();
out:
	वापस ret;
पूर्ण
