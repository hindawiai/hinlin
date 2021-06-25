<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Check अगर we can fully utilize 4-tuples क्रम connect().
 *
 * Rules to bind sockets to the same port when all ephemeral ports are
 * exhausted.
 *
 *   1. अगर there are TCP_LISTEN sockets on the port, fail to bind.
 *   2. अगर there are sockets without SO_REUSEADDR, fail to bind.
 *   3. अगर SO_REUSEADDR is disabled, fail to bind.
 *   4. अगर SO_REUSEADDR is enabled and SO_REUSEPORT is disabled,
 *        succeed to bind.
 *   5. अगर SO_REUSEADDR and SO_REUSEPORT are enabled and
 *        there is no socket having the both options and the same EUID,
 *        succeed to bind.
 *   6. fail to bind.
 *
 * Author: Kuniyuki Iwashima <kuniyu@amazon.co.jp>
 */
#समावेश <arpa/inet.h>
#समावेश <netinet/in.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश "../kselftest_harness.h"

काष्ठा reuse_opts अणु
	पूर्णांक reuseaddr[2];
	पूर्णांक reuseport[2];
पूर्ण;

काष्ठा reuse_opts unreusable_opts[12] = अणु
	अणुअणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,
	अणुअणु0, 0पूर्ण, अणु0, 1पूर्णपूर्ण,
	अणुअणु0, 0पूर्ण, अणु1, 0पूर्णपूर्ण,
	अणुअणु0, 0पूर्ण, अणु1, 1पूर्णपूर्ण,
	अणुअणु0, 1पूर्ण, अणु0, 0पूर्णपूर्ण,
	अणुअणु0, 1पूर्ण, अणु0, 1पूर्णपूर्ण,
	अणुअणु0, 1पूर्ण, अणु1, 0पूर्णपूर्ण,
	अणुअणु0, 1पूर्ण, अणु1, 1पूर्णपूर्ण,
	अणुअणु1, 0पूर्ण, अणु0, 0पूर्णपूर्ण,
	अणुअणु1, 0पूर्ण, अणु0, 1पूर्णपूर्ण,
	अणुअणु1, 0पूर्ण, अणु1, 0पूर्णपूर्ण,
	अणुअणु1, 0पूर्ण, अणु1, 1पूर्णपूर्ण,
पूर्ण;

काष्ठा reuse_opts reusable_opts[4] = अणु
	अणुअणु1, 1पूर्ण, अणु0, 0पूर्णपूर्ण,
	अणुअणु1, 1पूर्ण, अणु0, 1पूर्णपूर्ण,
	अणुअणु1, 1पूर्ण, अणु1, 0पूर्णपूर्ण,
	अणुअणु1, 1पूर्ण, अणु1, 1पूर्णपूर्ण,
पूर्ण;

पूर्णांक bind_port(काष्ठा __test_metadata *_metadata, पूर्णांक reuseaddr, पूर्णांक reuseport)
अणु
	काष्ठा sockaddr_in local_addr;
	पूर्णांक len = माप(local_addr);
	पूर्णांक fd, ret;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	ASSERT_NE(-1, fd) TH_LOG("failed to open socket.");

	ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, माप(पूर्णांक));
	ASSERT_EQ(0, ret) TH_LOG("failed to setsockopt: SO_REUSEADDR.");

	ret = setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &reuseport, माप(पूर्णांक));
	ASSERT_EQ(0, ret) TH_LOG("failed to setsockopt: SO_REUSEPORT.");

	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	local_addr.sin_port = 0;

	अगर (bind(fd, (काष्ठा sockaddr *)&local_addr, len) == -1) अणु
		बंद(fd);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

TEST(reuseaddr_ports_exhausted_unreusable)
अणु
	काष्ठा reuse_opts *opts;
	पूर्णांक i, j, fd[2];

	क्रम (i = 0; i < 12; i++) अणु
		opts = &unreusable_opts[i];

		क्रम (j = 0; j < 2; j++)
			fd[j] = bind_port(_metadata, opts->reuseaddr[j], opts->reuseport[j]);

		ASSERT_NE(-1, fd[0]) TH_LOG("failed to bind.");
		EXPECT_EQ(-1, fd[1]) TH_LOG("should fail to bind.");

		क्रम (j = 0; j < 2; j++)
			अगर (fd[j] != -1)
				बंद(fd[j]);
	पूर्ण
पूर्ण

TEST(reuseaddr_ports_exhausted_reusable_same_euid)
अणु
	काष्ठा reuse_opts *opts;
	पूर्णांक i, j, fd[2];

	क्रम (i = 0; i < 4; i++) अणु
		opts = &reusable_opts[i];

		क्रम (j = 0; j < 2; j++)
			fd[j] = bind_port(_metadata, opts->reuseaddr[j], opts->reuseport[j]);

		ASSERT_NE(-1, fd[0]) TH_LOG("failed to bind.");

		अगर (opts->reuseport[0] && opts->reuseport[1]) अणु
			EXPECT_EQ(-1, fd[1]) TH_LOG("should fail to bind because both sockets succeed to be listened.");
		पूर्ण अन्यथा अणु
			EXPECT_NE(-1, fd[1]) TH_LOG("should succeed to bind to connect to different destinations.");
		पूर्ण

		क्रम (j = 0; j < 2; j++)
			अगर (fd[j] != -1)
				बंद(fd[j]);
	पूर्ण
पूर्ण

TEST(reuseaddr_ports_exhausted_reusable_dअगरferent_euid)
अणु
	काष्ठा reuse_opts *opts;
	पूर्णांक i, j, ret, fd[2];
	uid_t euid[2] = अणु10, 20पूर्ण;

	क्रम (i = 0; i < 4; i++) अणु
		opts = &reusable_opts[i];

		क्रम (j = 0; j < 2; j++) अणु
			ret = seteuid(euid[j]);
			ASSERT_EQ(0, ret) TH_LOG("failed to seteuid: %d.", euid[j]);

			fd[j] = bind_port(_metadata, opts->reuseaddr[j], opts->reuseport[j]);

			ret = seteuid(0);
			ASSERT_EQ(0, ret) TH_LOG("failed to seteuid: 0.");
		पूर्ण

		ASSERT_NE(-1, fd[0]) TH_LOG("failed to bind.");
		EXPECT_NE(-1, fd[1]) TH_LOG("should succeed to bind because one socket can be bound in each euid.");

		अगर (fd[1] != -1) अणु
			ret = listen(fd[0], 5);
			ASSERT_EQ(0, ret) TH_LOG("failed to listen.");

			ret = listen(fd[1], 5);
			EXPECT_EQ(-1, ret) TH_LOG("should fail to listen because only one uid reserves the port in TCP_LISTEN.");
		पूर्ण

		क्रम (j = 0; j < 2; j++)
			अगर (fd[j] != -1)
				बंद(fd[j]);
	पूर्ण
पूर्ण

TEST_HARNESS_MAIN
