<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित UTIL_H
#घोषणा UTIL_H

#समावेश <sys/socket.h>
#समावेश <linux/vm_sockets.h>

/* Tests can either run as the client or the server */
क्रमागत test_mode अणु
	TEST_MODE_UNSET,
	TEST_MODE_CLIENT,
	TEST_MODE_SERVER
पूर्ण;

/* Test runner options */
काष्ठा test_opts अणु
	क्रमागत test_mode mode;
	अचिन्हित पूर्णांक peer_cid;
पूर्ण;

/* A test हाल definition.  Test functions must prपूर्णांक failures to मानक_त्रुटि and
 * terminate with निकास(निकास_त्रुटि).
 */
काष्ठा test_हाल अणु
	स्थिर अक्षर *name; /* human-पढ़ोable name */

	/* Called when test mode is TEST_MODE_CLIENT */
	व्योम (*run_client)(स्थिर काष्ठा test_opts *opts);

	/* Called when test mode is TEST_MODE_SERVER */
	व्योम (*run_server)(स्थिर काष्ठा test_opts *opts);

	bool skip;
पूर्ण;

व्योम init_संकेतs(व्योम);
अचिन्हित पूर्णांक parse_cid(स्थिर अक्षर *str);
पूर्णांक vsock_stream_connect(अचिन्हित पूर्णांक cid, अचिन्हित पूर्णांक port);
पूर्णांक vsock_stream_accept(अचिन्हित पूर्णांक cid, अचिन्हित पूर्णांक port,
			काष्ठा sockaddr_vm *clientaddrp);
व्योम vsock_रुको_remote_बंद(पूर्णांक fd);
व्योम send_byte(पूर्णांक fd, पूर्णांक expected_ret, पूर्णांक flags);
व्योम recv_byte(पूर्णांक fd, पूर्णांक expected_ret, पूर्णांक flags);
व्योम run_tests(स्थिर काष्ठा test_हाल *test_हालs,
	       स्थिर काष्ठा test_opts *opts);
व्योम list_tests(स्थिर काष्ठा test_हाल *test_हालs);
व्योम skip_test(काष्ठा test_हाल *test_हालs, माप_प्रकार test_हालs_len,
	       स्थिर अक्षर *test_id_str);
#पूर्ण_अगर /* UTIL_H */
