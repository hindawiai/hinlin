<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <kunit/test.h>

#समावेश "protocol.h"

अटल काष्ठा mptcp_subflow_request_sock *build_req_sock(काष्ठा kunit *test)
अणु
	काष्ठा mptcp_subflow_request_sock *req;

	req = kunit_kzalloc(test, माप(काष्ठा mptcp_subflow_request_sock),
			    GFP_USER);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, req);
	mptcp_token_init_request((काष्ठा request_sock *)req);
	वापस req;
पूर्ण

अटल व्योम mptcp_token_test_req_basic(काष्ठा kunit *test)
अणु
	काष्ठा mptcp_subflow_request_sock *req = build_req_sock(test);
	काष्ठा mptcp_sock *null_msk = शून्य;

	KUNIT_ASSERT_EQ(test, 0,
			mptcp_token_new_request((काष्ठा request_sock *)req));
	KUNIT_EXPECT_NE(test, 0, (पूर्णांक)req->token);
	KUNIT_EXPECT_PTR_EQ(test, null_msk, mptcp_token_get_sock(req->token));

	/* cleanup */
	mptcp_token_destroy_request((काष्ठा request_sock *)req);
पूर्ण

अटल काष्ठा inet_connection_sock *build_icsk(काष्ठा kunit *test)
अणु
	काष्ठा inet_connection_sock *icsk;

	icsk = kunit_kzalloc(test, माप(काष्ठा inet_connection_sock),
			     GFP_USER);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, icsk);
	वापस icsk;
पूर्ण

अटल काष्ठा mptcp_subflow_context *build_ctx(काष्ठा kunit *test)
अणु
	काष्ठा mptcp_subflow_context *ctx;

	ctx = kunit_kzalloc(test, माप(काष्ठा mptcp_subflow_context),
			    GFP_USER);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, ctx);
	वापस ctx;
पूर्ण

अटल काष्ठा mptcp_sock *build_msk(काष्ठा kunit *test)
अणु
	काष्ठा mptcp_sock *msk;

	msk = kunit_kzalloc(test, माप(काष्ठा mptcp_sock), GFP_USER);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, msk);
	refcount_set(&((काष्ठा sock *)msk)->sk_refcnt, 1);
	वापस msk;
पूर्ण

अटल व्योम mptcp_token_test_msk_basic(काष्ठा kunit *test)
अणु
	काष्ठा inet_connection_sock *icsk = build_icsk(test);
	काष्ठा mptcp_subflow_context *ctx = build_ctx(test);
	काष्ठा mptcp_sock *msk = build_msk(test);
	काष्ठा mptcp_sock *null_msk = शून्य;
	काष्ठा sock *sk;

	rcu_assign_poपूर्णांकer(icsk->icsk_ulp_data, ctx);
	ctx->conn = (काष्ठा sock *)msk;
	sk = (काष्ठा sock *)msk;

	KUNIT_ASSERT_EQ(test, 0,
			mptcp_token_new_connect((काष्ठा sock *)icsk));
	KUNIT_EXPECT_NE(test, 0, (पूर्णांक)ctx->token);
	KUNIT_EXPECT_EQ(test, ctx->token, msk->token);
	KUNIT_EXPECT_PTR_EQ(test, msk, mptcp_token_get_sock(ctx->token));
	KUNIT_EXPECT_EQ(test, 2, (पूर्णांक)refcount_पढ़ो(&sk->sk_refcnt));

	mptcp_token_destroy(msk);
	KUNIT_EXPECT_PTR_EQ(test, null_msk, mptcp_token_get_sock(ctx->token));
पूर्ण

अटल व्योम mptcp_token_test_accept(काष्ठा kunit *test)
अणु
	काष्ठा mptcp_subflow_request_sock *req = build_req_sock(test);
	काष्ठा mptcp_sock *msk = build_msk(test);

	KUNIT_ASSERT_EQ(test, 0,
			mptcp_token_new_request((काष्ठा request_sock *)req));
	msk->token = req->token;
	mptcp_token_accept(req, msk);
	KUNIT_EXPECT_PTR_EQ(test, msk, mptcp_token_get_sock(msk->token));

	/* this is now a no-op */
	mptcp_token_destroy_request((काष्ठा request_sock *)req);
	KUNIT_EXPECT_PTR_EQ(test, msk, mptcp_token_get_sock(msk->token));

	/* cleanup */
	mptcp_token_destroy(msk);
पूर्ण

अटल व्योम mptcp_token_test_destroyed(काष्ठा kunit *test)
अणु
	काष्ठा mptcp_subflow_request_sock *req = build_req_sock(test);
	काष्ठा mptcp_sock *msk = build_msk(test);
	काष्ठा mptcp_sock *null_msk = शून्य;
	काष्ठा sock *sk;

	sk = (काष्ठा sock *)msk;

	KUNIT_ASSERT_EQ(test, 0,
			mptcp_token_new_request((काष्ठा request_sock *)req));
	msk->token = req->token;
	mptcp_token_accept(req, msk);

	/* simulate race on removal */
	refcount_set(&sk->sk_refcnt, 0);
	KUNIT_EXPECT_PTR_EQ(test, null_msk, mptcp_token_get_sock(msk->token));

	/* cleanup */
	mptcp_token_destroy(msk);
पूर्ण

अटल काष्ठा kunit_हाल mptcp_token_test_हालs[] = अणु
	KUNIT_CASE(mptcp_token_test_req_basic),
	KUNIT_CASE(mptcp_token_test_msk_basic),
	KUNIT_CASE(mptcp_token_test_accept),
	KUNIT_CASE(mptcp_token_test_destroyed),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite mptcp_token_suite = अणु
	.name = "mptcp-token",
	.test_हालs = mptcp_token_test_हालs,
पूर्ण;

kunit_test_suite(mptcp_token_suite);

MODULE_LICENSE("GPL");
