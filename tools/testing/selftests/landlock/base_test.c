<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Landlock tests - Common user space base
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2019-2020 ANSSI
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/landlock.h>
#समावेश <माला.स>
#समावेश <sys/prctl.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>

#समावेश "common.h"

#अगर_अघोषित O_PATH
#घोषणा O_PATH		010000000
#पूर्ण_अगर

TEST(inconsistent_attr) अणु
	स्थिर दीर्घ page_size = sysconf(_SC_PAGESIZE);
	अक्षर *स्थिर buf = दो_स्मृति(page_size + 1);
	काष्ठा landlock_ruleset_attr *स्थिर ruleset_attr = (व्योम *)buf;

	ASSERT_NE(शून्य, buf);

	/* Checks copy_from_user(). */
	ASSERT_EQ(-1, landlock_create_ruleset(ruleset_attr, 0, 0));
	/* The size अगर less than माप(काष्ठा landlock_attr_enक्रमce). */
	ASSERT_EQ(EINVAL, त्रुटि_सं);
	ASSERT_EQ(-1, landlock_create_ruleset(ruleset_attr, 1, 0));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(शून्य, 1, 0));
	/* The size अगर less than माप(काष्ठा landlock_attr_enक्रमce). */
	ASSERT_EQ(EFAULT, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(शून्य,
				माप(काष्ठा landlock_ruleset_attr), 0));
	ASSERT_EQ(EFAULT, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(ruleset_attr, page_size + 1, 0));
	ASSERT_EQ(E2BIG, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(ruleset_attr,
				माप(काष्ठा landlock_ruleset_attr), 0));
	ASSERT_EQ(ENOMSG, त्रुटि_सं);
	ASSERT_EQ(-1, landlock_create_ruleset(ruleset_attr, page_size, 0));
	ASSERT_EQ(ENOMSG, त्रुटि_सं);

	/* Checks non-zero value. */
	buf[page_size - 2] = '.';
	ASSERT_EQ(-1, landlock_create_ruleset(ruleset_attr, page_size, 0));
	ASSERT_EQ(E2BIG, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(ruleset_attr, page_size + 1, 0));
	ASSERT_EQ(E2BIG, त्रुटि_सं);

	मुक्त(buf);
पूर्ण

TEST(abi_version) अणु
	स्थिर काष्ठा landlock_ruleset_attr ruleset_attr = अणु
		.handled_access_fs = LANDLOCK_ACCESS_FS_READ_खाता,
	पूर्ण;
	ASSERT_EQ(1, landlock_create_ruleset(शून्य, 0,
				LANDLOCK_CREATE_RULESET_VERSION));

	ASSERT_EQ(-1, landlock_create_ruleset(&ruleset_attr, 0,
				LANDLOCK_CREATE_RULESET_VERSION));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(शून्य, माप(ruleset_attr),
				LANDLOCK_CREATE_RULESET_VERSION));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(&ruleset_attr,
				माप(ruleset_attr),
				LANDLOCK_CREATE_RULESET_VERSION));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(शून्य, 0,
				LANDLOCK_CREATE_RULESET_VERSION | 1 << 31));
	ASSERT_EQ(EINVAL, त्रुटि_सं);
पूर्ण

TEST(inval_create_ruleset_flags) अणु
	स्थिर पूर्णांक last_flag = LANDLOCK_CREATE_RULESET_VERSION;
	स्थिर पूर्णांक invalid_flag = last_flag << 1;
	स्थिर काष्ठा landlock_ruleset_attr ruleset_attr = अणु
		.handled_access_fs = LANDLOCK_ACCESS_FS_READ_खाता,
	पूर्ण;

	ASSERT_EQ(-1, landlock_create_ruleset(शून्य, 0, invalid_flag));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(&ruleset_attr, 0, invalid_flag));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(शून्य, माप(ruleset_attr),
				invalid_flag));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(-1, landlock_create_ruleset(&ruleset_attr,
				माप(ruleset_attr), invalid_flag));
	ASSERT_EQ(EINVAL, त्रुटि_सं);
पूर्ण

TEST(empty_path_beneath_attr) अणु
	स्थिर काष्ठा landlock_ruleset_attr ruleset_attr = अणु
		.handled_access_fs = LANDLOCK_ACCESS_FS_EXECUTE,
	पूर्ण;
	स्थिर पूर्णांक ruleset_fd = landlock_create_ruleset(&ruleset_attr,
			माप(ruleset_attr), 0);

	ASSERT_LE(0, ruleset_fd);

	/* Similar to काष्ठा landlock_path_beneath_attr.parent_fd = 0 */
	ASSERT_EQ(-1, landlock_add_rule(ruleset_fd, LANDLOCK_RULE_PATH_BENEATH,
				शून्य, 0));
	ASSERT_EQ(EFAULT, त्रुटि_सं);
	ASSERT_EQ(0, बंद(ruleset_fd));
पूर्ण

TEST(inval_fd_enक्रमce) अणु
	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0));

	ASSERT_EQ(-1, landlock_restrict_self(-1, 0));
	ASSERT_EQ(EBADF, त्रुटि_सं);
पूर्ण

TEST(unpriv_enक्रमce_without_no_new_privs) अणु
	पूर्णांक err;

	drop_caps(_metadata);
	err = landlock_restrict_self(-1, 0);
	ASSERT_EQ(EPERM, त्रुटि_सं);
	ASSERT_EQ(err, -1);
पूर्ण

TEST(ruleset_fd_io)
अणु
	काष्ठा landlock_ruleset_attr ruleset_attr = अणु
		.handled_access_fs = LANDLOCK_ACCESS_FS_READ_खाता,
	पूर्ण;
	पूर्णांक ruleset_fd;
	अक्षर buf;

	drop_caps(_metadata);
	ruleset_fd = landlock_create_ruleset(&ruleset_attr,
			माप(ruleset_attr), 0);
	ASSERT_LE(0, ruleset_fd);

	ASSERT_EQ(-1, ग_लिखो(ruleset_fd, ".", 1));
	ASSERT_EQ(EINVAL, त्रुटि_सं);
	ASSERT_EQ(-1, पढ़ो(ruleset_fd, &buf, 1));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	ASSERT_EQ(0, बंद(ruleset_fd));
पूर्ण

/* Tests enक्रमcement of a ruleset FD transferred through a UNIX socket. */
TEST(ruleset_fd_transfer)
अणु
	काष्ठा landlock_ruleset_attr ruleset_attr = अणु
		.handled_access_fs = LANDLOCK_ACCESS_FS_READ_सूची,
	पूर्ण;
	काष्ठा landlock_path_beneath_attr path_beneath_attr = अणु
		.allowed_access = LANDLOCK_ACCESS_FS_READ_सूची,
	पूर्ण;
	पूर्णांक ruleset_fd_tx, dir_fd;
	जोड़ अणु
		/* Aligned ancillary data buffer. */
		अक्षर buf[CMSG_SPACE(माप(ruleset_fd_tx))];
		काष्ठा cmsghdr _align;
	पूर्ण cmsg_tx = अणुपूर्ण;
	अक्षर data_tx = '.';
	काष्ठा iovec io = अणु
		.iov_base = &data_tx,
		.iov_len = माप(data_tx),
	पूर्ण;
	काष्ठा msghdr msg = अणु
		.msg_iov = &io,
		.msg_iovlen = 1,
		.msg_control = &cmsg_tx.buf,
		.msg_controllen = माप(cmsg_tx.buf),
	पूर्ण;
	काष्ठा cmsghdr *cmsg;
	पूर्णांक socket_fds[2];
	pid_t child;
	पूर्णांक status;

	drop_caps(_metadata);

	/* Creates a test ruleset with a simple rule. */
	ruleset_fd_tx = landlock_create_ruleset(&ruleset_attr,
			माप(ruleset_attr), 0);
	ASSERT_LE(0, ruleset_fd_tx);
	path_beneath_attr.parent_fd = खोलो("/tmp", O_PATH | O_NOFOLLOW |
			O_सूचीECTORY | O_CLOEXEC);
	ASSERT_LE(0, path_beneath_attr.parent_fd);
	ASSERT_EQ(0, landlock_add_rule(ruleset_fd_tx, LANDLOCK_RULE_PATH_BENEATH,
				&path_beneath_attr, 0));
	ASSERT_EQ(0, बंद(path_beneath_attr.parent_fd));

	cmsg = CMSG_FIRSTHDR(&msg);
	ASSERT_NE(शून्य, cmsg);
	cmsg->cmsg_len = CMSG_LEN(माप(ruleset_fd_tx));
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	स_नकल(CMSG_DATA(cmsg), &ruleset_fd_tx, माप(ruleset_fd_tx));

	/* Sends the ruleset FD over a socketpair and then बंद it. */
	ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, socket_fds));
	ASSERT_EQ(माप(data_tx), sendmsg(socket_fds[0], &msg, 0));
	ASSERT_EQ(0, बंद(socket_fds[0]));
	ASSERT_EQ(0, बंद(ruleset_fd_tx));

	child = विभाजन();
	ASSERT_LE(0, child);
	अगर (child == 0) अणु
		पूर्णांक ruleset_fd_rx;

		*(अक्षर *)msg.msg_iov->iov_base = '\0';
		ASSERT_EQ(माप(data_tx), recvmsg(socket_fds[1], &msg, MSG_CMSG_CLOEXEC));
		ASSERT_EQ('.', *(अक्षर *)msg.msg_iov->iov_base);
		ASSERT_EQ(0, बंद(socket_fds[1]));
		cmsg = CMSG_FIRSTHDR(&msg);
		ASSERT_EQ(cmsg->cmsg_len, CMSG_LEN(माप(ruleset_fd_tx)));
		स_नकल(&ruleset_fd_rx, CMSG_DATA(cmsg), माप(ruleset_fd_tx));

		/* Enक्रमces the received ruleset on the child. */
		ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0));
		ASSERT_EQ(0, landlock_restrict_self(ruleset_fd_rx, 0));
		ASSERT_EQ(0, बंद(ruleset_fd_rx));

		/* Checks that the ruleset enक्रमcement. */
		ASSERT_EQ(-1, खोलो("/", O_RDONLY | O_सूचीECTORY | O_CLOEXEC));
		ASSERT_EQ(EACCES, त्रुटि_सं);
		dir_fd = खोलो("/tmp", O_RDONLY | O_सूचीECTORY | O_CLOEXEC);
		ASSERT_LE(0, dir_fd);
		ASSERT_EQ(0, बंद(dir_fd));
		_निकास(_metadata->passed ? निकास_सफल : निकास_त्रुटि);
		वापस;
	पूर्ण

	ASSERT_EQ(0, बंद(socket_fds[1]));

	/* Checks that the parent is unrestricted. */
	dir_fd = खोलो("/", O_RDONLY | O_सूचीECTORY | O_CLOEXEC);
	ASSERT_LE(0, dir_fd);
	ASSERT_EQ(0, बंद(dir_fd));
	dir_fd = खोलो("/tmp", O_RDONLY | O_सूचीECTORY | O_CLOEXEC);
	ASSERT_LE(0, dir_fd);
	ASSERT_EQ(0, बंद(dir_fd));

	ASSERT_EQ(child, रुकोpid(child, &status, 0));
	ASSERT_EQ(1, WIFEXITED(status));
	ASSERT_EQ(निकास_सफल, WEXITSTATUS(status));
पूर्ण

TEST_HARNESS_MAIN
