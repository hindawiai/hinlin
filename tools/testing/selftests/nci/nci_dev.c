<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2021 Samsung Electrnoics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 *
 * Test code क्रम nci
 */

#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <linux/genetlink.h>
#समावेश <sys/socket.h>
#समावेश <linux/nfc.h>

#समावेश "../kselftest_harness.h"

#घोषणा GENLMSG_DATA(glh)	((व्योम *)(NLMSG_DATA(glh) + GENL_HDRLEN))
#घोषणा GENLMSG_PAYLOAD(glh)	(NLMSG_PAYLOAD(glh, 0) - GENL_HDRLEN)
#घोषणा NLA_DATA(na)		((व्योम *)((अक्षर *)(na) + NLA_HDRLEN))
#घोषणा NLA_PAYLOAD(len)	((len) - NLA_HDRLEN)

#घोषणा MAX_MSG_SIZE	1024

#घोषणा IOCTL_GET_NCIDEV_IDX	0
#घोषणा VIRTUAL_NFC_PROTOCOLS	(NFC_PROTO_JEWEL_MASK | \
				 NFC_PROTO_MIFARE_MASK | \
				 NFC_PROTO_FELICA_MASK | \
				 NFC_PROTO_ISO14443_MASK | \
				 NFC_PROTO_ISO14443_B_MASK | \
				 NFC_PROTO_ISO15693_MASK)

स्थिर __u8 nci_reset_cmd[] = अणु0x20, 0x00, 0x01, 0x01पूर्ण;
स्थिर __u8 nci_init_cmd[] = अणु0x20, 0x01, 0x00पूर्ण;
स्थिर __u8 nci_rf_discovery_cmd[] = अणु0x21, 0x03, 0x09, 0x04, 0x00, 0x01,
				      0x01, 0x01, 0x02, 0x01, 0x06, 0x01पूर्ण;
स्थिर __u8 nci_init_cmd_v2[] = अणु0x20, 0x01, 0x02, 0x00, 0x00पूर्ण;
स्थिर __u8 nci_rf_disc_map_cmd[] = अणु0x21, 0x00, 0x07, 0x02, 0x04, 0x03,
				     0x02, 0x05, 0x03, 0x03पूर्ण;
स्थिर __u8 nci_rf_deact_cmd[] = अणु0x21, 0x06, 0x01, 0x00पूर्ण;
स्थिर __u8 nci_reset_rsp[] = अणु0x40, 0x00, 0x03, 0x00, 0x10, 0x01पूर्ण;
स्थिर __u8 nci_reset_rsp_v2[] = अणु0x40, 0x00, 0x01, 0x00पूर्ण;
स्थिर __u8 nci_reset_ntf[] = अणु0x60, 0x00, 0x09, 0x02, 0x01, 0x20, 0x0e,
			       0x04, 0x61, 0x00, 0x04, 0x02पूर्ण;
स्थिर __u8 nci_init_rsp[] = अणु0x40, 0x01, 0x14, 0x00, 0x02, 0x0e, 0x02,
			      0x00, 0x03, 0x01, 0x02, 0x03, 0x02, 0xc8,
			      0x00, 0xff, 0x10, 0x00, 0x0e, 0x12, 0x00,
			      0x00, 0x04पूर्ण;
स्थिर __u8 nci_init_rsp_v2[] = अणु0x40, 0x01, 0x1c, 0x00, 0x1a, 0x7e, 0x06,
				 0x00, 0x02, 0x92, 0x04, 0xff, 0xff, 0x01,
				 0x00, 0x40, 0x06, 0x00, 0x00, 0x01, 0x01,
				 0x00, 0x02, 0x00, 0x03, 0x01, 0x01, 0x06,
				 0x00, 0x80, 0x00पूर्ण;
स्थिर __u8 nci_rf_disc_map_rsp[] = अणु0x41, 0x00, 0x01, 0x00पूर्ण;
स्थिर __u8 nci_rf_disc_rsp[] = अणु0x41, 0x03, 0x01, 0x00पूर्ण;
स्थिर __u8 nci_rf_deact_rsp[] = अणु0x41, 0x06, 0x01, 0x00पूर्ण;

काष्ठा msgढाँचा अणु
	काष्ठा nlmsghdr n;
	काष्ठा genlmsghdr g;
	अक्षर buf[MAX_MSG_SIZE];
पूर्ण;

अटल पूर्णांक create_nl_socket(व्योम)
अणु
	पूर्णांक fd;
	काष्ठा sockaddr_nl local;

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
	अगर (fd < 0)
		वापस -1;

	स_रखो(&local, 0, माप(local));
	local.nl_family = AF_NETLINK;

	अगर (bind(fd, (काष्ठा sockaddr *)&local, माप(local)) < 0)
		जाओ error;

	वापस fd;
error:
	बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक send_cmd_mt_nla(पूर्णांक sd, __u16 nlmsg_type, __u32 nlmsg_pid,
			   __u8 genl_cmd, पूर्णांक nla_num, __u16 nla_type[],
			   व्योम *nla_data[], पूर्णांक nla_len[])
अणु
	काष्ठा sockaddr_nl nladdr;
	काष्ठा msgढाँचा msg;
	काष्ठा nlattr *na;
	पूर्णांक cnt, prv_len;
	पूर्णांक r, buflen;
	अक्षर *buf;

	msg.n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
	msg.n.nlmsg_type = nlmsg_type;
	msg.n.nlmsg_flags = NLM_F_REQUEST;
	msg.n.nlmsg_seq = 0;
	msg.n.nlmsg_pid = nlmsg_pid;
	msg.g.cmd = genl_cmd;
	msg.g.version = 0x1;

	prv_len = 0;
	क्रम (cnt = 0; cnt < nla_num; cnt++) अणु
		na = (काष्ठा nlattr *)(GENLMSG_DATA(&msg) + prv_len);
		na->nla_type = nla_type[cnt];
		na->nla_len = nla_len[cnt] + NLA_HDRLEN;

		अगर (nla_len > 0)
			स_नकल(NLA_DATA(na), nla_data[cnt], nla_len[cnt]);

		msg.n.nlmsg_len += NLMSG_ALIGN(na->nla_len);
		prv_len = na->nla_len;
	पूर्ण

	buf = (अक्षर *)&msg;
	buflen = msg.n.nlmsg_len;
	स_रखो(&nladdr, 0, माप(nladdr));
	nladdr.nl_family = AF_NETLINK;

	जबतक ((r = sendto(sd, buf, buflen, 0, (काष्ठा sockaddr *)&nladdr,
			   माप(nladdr))) < buflen) अणु
		अगर (r > 0) अणु
			buf += r;
			buflen -= r;
		पूर्ण अन्यथा अगर (त्रुटि_सं != EAGAIN) अणु
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक send_get_nfc_family(पूर्णांक sd, __u32 pid)
अणु
	__u16 nla_get_family_type = CTRL_ATTR_FAMILY_NAME;
	व्योम *nla_get_family_data;
	पूर्णांक nla_get_family_len;
	अक्षर family_name[100];

	nla_get_family_len = म_माप(NFC_GENL_NAME) + 1;
	म_नकल(family_name, NFC_GENL_NAME);
	nla_get_family_data = family_name;

	वापस send_cmd_mt_nla(sd, GENL_ID_CTRL, pid, CTRL_CMD_GETFAMILY,
				1, &nla_get_family_type,
				&nla_get_family_data, &nla_get_family_len);
पूर्ण

अटल पूर्णांक get_family_id(पूर्णांक sd, __u32 pid)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr n;
		काष्ठा genlmsghdr g;
		अक्षर buf[512];
	पूर्ण ans;
	काष्ठा nlattr *na;
	पूर्णांक rep_len;
	__u16 id;
	पूर्णांक rc;

	rc = send_get_nfc_family(sd, pid);

	अगर (rc < 0)
		वापस 0;

	rep_len = recv(sd, &ans, माप(ans), 0);

	अगर (ans.n.nlmsg_type == NLMSG_ERROR || rep_len < 0 ||
	    !NLMSG_OK(&ans.n, rep_len))
		वापस 0;

	na = (काष्ठा nlattr *)GENLMSG_DATA(&ans);
	na = (काष्ठा nlattr *)((अक्षर *)na + NLA_ALIGN(na->nla_len));
	अगर (na->nla_type == CTRL_ATTR_FAMILY_ID)
		id = *(__u16 *)NLA_DATA(na);

	वापस id;
पूर्ण

अटल पूर्णांक send_cmd_with_idx(पूर्णांक sd, __u16 nlmsg_type, __u32 nlmsg_pid,
			     __u8 genl_cmd, पूर्णांक dev_id)
अणु
	__u16 nla_type = NFC_ATTR_DEVICE_INDEX;
	व्योम *nla_data = &dev_id;
	पूर्णांक nla_len = 4;

	वापस send_cmd_mt_nla(sd, nlmsg_type, nlmsg_pid, genl_cmd, 1,
				&nla_type, &nla_data, &nla_len);
पूर्ण

अटल पूर्णांक get_nci_devid(पूर्णांक sd, __u16 fid, __u32 pid, पूर्णांक dev_id, काष्ठा msgढाँचा *msg)
अणु
	पूर्णांक rc, rep_len;

	rc = send_cmd_with_idx(sd, fid, pid, NFC_CMD_GET_DEVICE, dev_id);
	अगर (rc < 0) अणु
		rc = -1;
		जाओ error;
	पूर्ण

	rep_len = recv(sd, msg, माप(*msg), 0);
	अगर (rep_len < 0) अणु
		rc = -2;
		जाओ error;
	पूर्ण

	अगर (msg->n.nlmsg_type == NLMSG_ERROR ||
	    !NLMSG_OK(&msg->n, rep_len)) अणु
		rc = -3;
		जाओ error;
	पूर्ण

	वापस 0;
error:
	वापस rc;
पूर्ण

अटल __u8 get_dev_enable_state(काष्ठा msgढाँचा *msg)
अणु
	काष्ठा nlattr *na;
	पूर्णांक rep_len;
	पूर्णांक len;

	rep_len = GENLMSG_PAYLOAD(&msg->n);
	na = (काष्ठा nlattr *)GENLMSG_DATA(msg);
	len = 0;

	जबतक (len < rep_len) अणु
		len += NLA_ALIGN(na->nla_len);
		अगर (na->nla_type == NFC_ATTR_DEVICE_POWERED)
			वापस *(अक्षर *)NLA_DATA(na);
		na = (काष्ठा nlattr *)(GENLMSG_DATA(msg) + len);
	पूर्ण

	वापस rep_len;
पूर्ण

FIXTURE(NCI) अणु
	पूर्णांक भव_nci_fd;
	bool खोलो_state;
	पूर्णांक dev_idex;
	bool isNCI2;
	पूर्णांक proto;
	__u32 pid;
	__u16 fid;
	पूर्णांक sd;
पूर्ण;

FIXTURE_VARIANT(NCI) अणु
	bool isNCI2;
पूर्ण;

FIXTURE_VARIANT_ADD(NCI, NCI1_0) अणु
	.isNCI2 = false,
पूर्ण;

FIXTURE_VARIANT_ADD(NCI, NCI2_0) अणु
	.isNCI2 = true,
पूर्ण;

अटल व्योम *भव_dev_खोलो(व्योम *data)
अणु
	अक्षर buf[258];
	पूर्णांक dev_fd;
	पूर्णांक len;

	dev_fd = *(पूर्णांक *)data;

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_reset_cmd))
		जाओ error;
	अगर (स_भेद(nci_reset_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_reset_rsp, माप(nci_reset_rsp));

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_init_cmd))
		जाओ error;
	अगर (स_भेद(nci_init_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_init_rsp, माप(nci_init_rsp));

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_rf_disc_map_cmd))
		जाओ error;
	अगर (स_भेद(nci_rf_disc_map_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_rf_disc_map_rsp, माप(nci_rf_disc_map_rsp));

	वापस (व्योम *)0;
error:
	वापस (व्योम *)-1;
पूर्ण

अटल व्योम *भव_dev_खोलो_v2(व्योम *data)
अणु
	अक्षर buf[258];
	पूर्णांक dev_fd;
	पूर्णांक len;

	dev_fd = *(पूर्णांक *)data;

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_reset_cmd))
		जाओ error;
	अगर (स_भेद(nci_reset_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_reset_rsp_v2, माप(nci_reset_rsp_v2));
	ग_लिखो(dev_fd, nci_reset_ntf, माप(nci_reset_ntf));

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_init_cmd_v2))
		जाओ error;
	अगर (स_भेद(nci_init_cmd_v2, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_init_rsp_v2, माप(nci_init_rsp_v2));

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_rf_disc_map_cmd))
		जाओ error;
	अगर (स_भेद(nci_rf_disc_map_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_rf_disc_map_rsp, माप(nci_rf_disc_map_rsp));

	वापस (व्योम *)0;
error:
	वापस (व्योम *)-1;
पूर्ण

FIXTURE_SETUP(NCI)
अणु
	काष्ठा msgढाँचा msg;
	pthपढ़ो_t thपढ़ो_t;
	पूर्णांक status;
	पूर्णांक rc;

	self->खोलो_state = false;
	self->proto = VIRTUAL_NFC_PROTOCOLS;
	self->isNCI2 = variant->isNCI2;

	self->sd = create_nl_socket();
	ASSERT_NE(self->sd, -1);

	self->pid = getpid();
	self->fid = get_family_id(self->sd, self->pid);
	ASSERT_NE(self->fid, -1);

	self->भव_nci_fd = खोलो("/dev/virtual_nci", O_RDWR);
	ASSERT_GT(self->भव_nci_fd, -1);

	rc = ioctl(self->भव_nci_fd, IOCTL_GET_NCIDEV_IDX, &self->dev_idex);
	ASSERT_EQ(rc, 0);

	rc = get_nci_devid(self->sd, self->fid, self->pid, self->dev_idex, &msg);
	ASSERT_EQ(rc, 0);
	EXPECT_EQ(get_dev_enable_state(&msg), 0);

	अगर (self->isNCI2)
		rc = pthपढ़ो_create(&thपढ़ो_t, शून्य, भव_dev_खोलो_v2,
				    (व्योम *)&self->भव_nci_fd);
	अन्यथा
		rc = pthपढ़ो_create(&thपढ़ो_t, शून्य, भव_dev_खोलो,
				    (व्योम *)&self->भव_nci_fd);
	ASSERT_GT(rc, -1);

	rc = send_cmd_with_idx(self->sd, self->fid, self->pid,
			       NFC_CMD_DEV_UP, self->dev_idex);
	EXPECT_EQ(rc, 0);

	pthपढ़ो_join(thपढ़ो_t, (व्योम **)&status);
	ASSERT_EQ(status, 0);
	self->खोलो_state = true;
पूर्ण

अटल व्योम *भव_deinit(व्योम *data)
अणु
	अक्षर buf[258];
	पूर्णांक dev_fd;
	पूर्णांक len;

	dev_fd = *(पूर्णांक *)data;

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_reset_cmd))
		जाओ error;
	अगर (स_भेद(nci_reset_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_reset_rsp, माप(nci_reset_rsp));

	वापस (व्योम *)0;
error:
	वापस (व्योम *)-1;
पूर्ण

अटल व्योम *भव_deinit_v2(व्योम *data)
अणु
	अक्षर buf[258];
	पूर्णांक dev_fd;
	पूर्णांक len;

	dev_fd = *(पूर्णांक *)data;

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_reset_cmd))
		जाओ error;
	अगर (स_भेद(nci_reset_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_reset_rsp_v2, माप(nci_reset_rsp_v2));
	ग_लिखो(dev_fd, nci_reset_ntf, माप(nci_reset_ntf));

	वापस (व्योम *)0;
error:
	वापस (व्योम *)-1;
पूर्ण

FIXTURE_TEARDOWN(NCI)
अणु
	pthपढ़ो_t thपढ़ो_t;
	पूर्णांक status;
	पूर्णांक rc;

	अगर (self->खोलो_state) अणु
		अगर (self->isNCI2)
			rc = pthपढ़ो_create(&thपढ़ो_t, शून्य,
					    भव_deinit_v2,
					    (व्योम *)&self->भव_nci_fd);
		अन्यथा
			rc = pthपढ़ो_create(&thपढ़ो_t, शून्य, भव_deinit,
					    (व्योम *)&self->भव_nci_fd);

		ASSERT_GT(rc, -1);
		rc = send_cmd_with_idx(self->sd, self->fid, self->pid,
				       NFC_CMD_DEV_DOWN, self->dev_idex);
		EXPECT_EQ(rc, 0);

		pthपढ़ो_join(thपढ़ो_t, (व्योम **)&status);
		ASSERT_EQ(status, 0);
	पूर्ण

	बंद(self->sd);
	बंद(self->भव_nci_fd);
	self->खोलो_state = false;
पूर्ण

TEST_F(NCI, init)
अणु
	काष्ठा msgढाँचा msg;
	पूर्णांक rc;

	rc = get_nci_devid(self->sd, self->fid, self->pid, self->dev_idex,
			   &msg);
	ASSERT_EQ(rc, 0);
	EXPECT_EQ(get_dev_enable_state(&msg), 1);
पूर्ण

अटल व्योम *भव_poll_start(व्योम *data)
अणु
	अक्षर buf[258];
	पूर्णांक dev_fd;
	पूर्णांक len;

	dev_fd = *(पूर्णांक *)data;

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_rf_discovery_cmd))
		जाओ error;
	अगर (स_भेद(nci_rf_discovery_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_rf_disc_rsp, माप(nci_rf_disc_rsp))
		;

	वापस (व्योम *)0;
error:
	वापस (व्योम *)-1;
पूर्ण

अटल व्योम *भव_poll_stop(व्योम *data)
अणु
	अक्षर buf[258];
	पूर्णांक dev_fd;
	पूर्णांक len;

	dev_fd = *(पूर्णांक *)data;

	जबतक ((len = पढ़ो(dev_fd, buf, 258)) == 0)
		;
	अगर (len <= 0)
		जाओ error;
	अगर (len != माप(nci_rf_deact_cmd))
		जाओ error;
	अगर (स_भेद(nci_rf_deact_cmd, buf, len))
		जाओ error;
	ग_लिखो(dev_fd, nci_rf_deact_rsp, माप(nci_rf_deact_rsp));

	वापस (व्योम *)0;
error:
	वापस (व्योम *)-1;
पूर्ण

TEST_F(NCI, start_poll)
अणु
	__u16 nla_start_poll_type[2] = अणुNFC_ATTR_DEVICE_INDEX,
					 NFC_ATTR_PROTOCOLSपूर्ण;
	व्योम *nla_start_poll_data[2] = अणु&self->dev_idex, &self->protoपूर्ण;
	पूर्णांक nla_start_poll_len[2] = अणु4, 4पूर्ण;
	pthपढ़ो_t thपढ़ो_t;
	पूर्णांक status;
	पूर्णांक rc;

	rc = pthपढ़ो_create(&thपढ़ो_t, शून्य, भव_poll_start,
			    (व्योम *)&self->भव_nci_fd);
	ASSERT_GT(rc, -1);

	rc = send_cmd_mt_nla(self->sd, self->fid, self->pid,
			     NFC_CMD_START_POLL, 2, nla_start_poll_type,
			     nla_start_poll_data, nla_start_poll_len);
	EXPECT_EQ(rc, 0);

	pthपढ़ो_join(thपढ़ो_t, (व्योम **)&status);
	ASSERT_EQ(status, 0);

	rc = pthपढ़ो_create(&thपढ़ो_t, शून्य, भव_poll_stop,
			    (व्योम *)&self->भव_nci_fd);
	ASSERT_GT(rc, -1);

	rc = send_cmd_with_idx(self->sd, self->fid, self->pid,
			       NFC_CMD_STOP_POLL, self->dev_idex);
	EXPECT_EQ(rc, 0);

	pthपढ़ो_join(thपढ़ो_t, (व्योम **)&status);
	ASSERT_EQ(status, 0);
पूर्ण

TEST_F(NCI, deinit)
अणु
	काष्ठा msgढाँचा msg;
	pthपढ़ो_t thपढ़ो_t;
	पूर्णांक status;
	पूर्णांक rc;

	rc = get_nci_devid(self->sd, self->fid, self->pid, self->dev_idex,
			   &msg);
	ASSERT_EQ(rc, 0);
	EXPECT_EQ(get_dev_enable_state(&msg), 1);

	अगर (self->isNCI2)
		rc = pthपढ़ो_create(&thपढ़ो_t, शून्य, भव_deinit_v2,
				    (व्योम *)&self->भव_nci_fd);
	अन्यथा
		rc = pthपढ़ो_create(&thपढ़ो_t, शून्य, भव_deinit,
				    (व्योम *)&self->भव_nci_fd);
	ASSERT_GT(rc, -1);

	rc = send_cmd_with_idx(self->sd, self->fid, self->pid,
			       NFC_CMD_DEV_DOWN, self->dev_idex);
	EXPECT_EQ(rc, 0);

	pthपढ़ो_join(thपढ़ो_t, (व्योम **)&status);
	self->खोलो_state = 0;
	ASSERT_EQ(status, 0);

	rc = get_nci_devid(self->sd, self->fid, self->pid, self->dev_idex,
			   &msg);
	ASSERT_EQ(rc, 0);
	EXPECT_EQ(get_dev_enable_state(&msg), 0);
पूर्ण

TEST_HARNESS_MAIN
