<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <यंत्र/unistd.h>
#समावेश <linux/समय_प्रकारypes.h>
#समावेश <poll.h>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <संकेत.स>
#समावेश <pthपढ़ो.h>
#समावेश <sys/epoll.h>
#समावेश <sys/socket.h>
#समावेश <sys/eventfd.h>
#समावेश "../../kselftest_harness.h"

काष्ठा epoll_mtcontext
अणु
	पूर्णांक efd[3];
	पूर्णांक sfd[4];
	अस्थिर पूर्णांक count;

	pthपढ़ो_t मुख्य;
	pthपढ़ो_t रुकोer;
पूर्ण;

#अगर_अघोषित __NR_epoll_pरुको2
#घोषणा __NR_epoll_pरुको2 -1
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sys_epoll_pरुको2(पूर्णांक fd, काष्ठा epoll_event *events,
				   पूर्णांक maxevents,
				   स्थिर काष्ठा __kernel_बारpec *समयout,
				   स्थिर sigset_t *sigset, माप_प्रकार sigsetsize)
अणु
	वापस syscall(__NR_epoll_pरुको2, fd, events, maxevents, समयout,
		       sigset, sigsetsize);
पूर्ण

अटल व्योम संकेत_handler(पूर्णांक signum)
अणु
पूर्ण

अटल व्योम समाप्त_समयout(काष्ठा epoll_mtcontext *ctx)
अणु
	usleep(1000000);
	pthपढ़ो_समाप्त(ctx->मुख्य, SIGUSR1);
	pthपढ़ो_समाप्त(ctx->रुकोer, SIGUSR1);
पूर्ण

अटल व्योम *रुकोer_entry1a(व्योम *data)
अणु
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext *ctx = data;

	अगर (epoll_रुको(ctx->efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx->count, 1);

	वापस शून्य;
पूर्ण

अटल व्योम *रुकोer_entry1ap(व्योम *data)
अणु
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext *ctx = data;

	pfd.fd = ctx->efd[0];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx->efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx->count, 1);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *रुकोer_entry1o(व्योम *data)
अणु
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext *ctx = data;

	अगर (epoll_रुको(ctx->efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_or(&ctx->count, 1);

	वापस शून्य;
पूर्ण

अटल व्योम *रुकोer_entry1op(व्योम *data)
अणु
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext *ctx = data;

	pfd.fd = ctx->efd[0];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx->efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_or(&ctx->count, 1);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *रुकोer_entry2a(व्योम *data)
अणु
	काष्ठा epoll_event events[2];
	काष्ठा epoll_mtcontext *ctx = data;

	अगर (epoll_रुको(ctx->efd[0], events, 2, -1) > 0)
		__sync_fetch_and_add(&ctx->count, 1);

	वापस शून्य;
पूर्ण

अटल व्योम *रुकोer_entry2ap(व्योम *data)
अणु
	काष्ठा pollfd pfd;
	काष्ठा epoll_event events[2];
	काष्ठा epoll_mtcontext *ctx = data;

	pfd.fd = ctx->efd[0];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx->efd[0], events, 2, 0) > 0)
			__sync_fetch_and_add(&ctx->count, 1);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *emitter_entry1(व्योम *data)
अणु
	काष्ठा epoll_mtcontext *ctx = data;

	usleep(100000);
	ग_लिखो(ctx->sfd[1], "w", 1);

	समाप्त_समयout(ctx);

	वापस शून्य;
पूर्ण

अटल व्योम *emitter_entry2(व्योम *data)
अणु
	काष्ठा epoll_mtcontext *ctx = data;

	usleep(100000);
	ग_लिखो(ctx->sfd[1], "w", 1);
	ग_लिखो(ctx->sfd[3], "w", 1);

	समाप्त_समयout(ctx);

	वापस शून्य;
पूर्ण

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (lt)
 *          s0
 */
TEST(epoll1)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd, &e, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd, &e, 1, 0), 1);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (et)
 *          s0
 */
TEST(epoll2)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd, &e, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd, &e, 1, 0), 0);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *           t0
 *            | (ew)
 *           e0
 *     (lt) /  \ (lt)
 *        s0    s2
 */
TEST(epoll3)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[4];
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 2);
	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 2);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *           t0
 *            | (ew)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoll4)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[4];
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 2);
	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 0);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *          t0
 *           | (p)
 *          e0
 *           | (lt)
 *          s0
 */
TEST(epoll5)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[2];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POLLIN;
	ASSERT_EQ(poll(&pfd, 1, 0), 1);
	ASSERT_EQ(epoll_रुको(efd, &e, 1, 0), 1);

	pfd.fd = efd;
	pfd.events = POLLIN;
	ASSERT_EQ(poll(&pfd, 1, 0), 1);
	ASSERT_EQ(epoll_रुको(efd, &e, 1, 0), 1);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *          t0
 *           | (p)
 *          e0
 *           | (et)
 *          s0
 */
TEST(epoll6)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[2];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POLLIN;
	ASSERT_EQ(poll(&pfd, 1, 0), 1);
	ASSERT_EQ(epoll_रुको(efd, &e, 1, 0), 1);

	pfd.fd = efd;
	pfd.events = POLLIN;
	ASSERT_EQ(poll(&pfd, 1, 0), 0);
	ASSERT_EQ(epoll_रुको(efd, &e, 1, 0), 0);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *           t0
 *            | (p)
 *           e0
 *     (lt) /  \ (lt)
 *        s0    s2
 */

TEST(epoll7)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[4];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 2);

	pfd.fd = efd;
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 2);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *           t0
 *            | (p)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoll8)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[4];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 2);

	pfd.fd = efd;
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 0);
	EXPECT_EQ(epoll_रुको(efd, events, 2, 0), 0);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (lt)
 *           s0
 */
TEST(epoll9)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (et)
 *           s0
 */
TEST(epoll10)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 1);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (lt) /  \ (lt)
 *        s0    s2
 */
TEST(epoll11)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event events[2];
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[2], events), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry2a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], events, 2, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoll12)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event events[2];
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[2], events), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], events, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (lt)
 *           s0
 */
TEST(epoll13)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (et)
 *           s0
 */
TEST(epoll14)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 1);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (lt) /  \ (lt)
 *        s0    s2
 */
TEST(epoll15)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event events[2];
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[2], events), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry2ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], events, 2, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoll16)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event events[2];
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[2], events), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], events, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (lt)
 *          e1
 *           | (lt)
 *          s0
 */
TEST(epoll17)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (lt)
 *          e1
 *           | (et)
 *          s0
 */
TEST(epoll18)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *           t0
 *            | (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll19)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 0);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *           t0
 *            | (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll20)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 0);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *          t0
 *           | (p)
 *          e0
 *           | (lt)
 *          e1
 *           | (lt)
 *          s0
 */
TEST(epoll21)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *          t0
 *           | (p)
 *          e0
 *           | (lt)
 *          e1
 *           | (et)
 *          s0
 */
TEST(epoll22)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *          t0
 *           | (p)
 *          e0
 *           | (et)
 *          e1
 *           | (lt)
 *          s0
 */
TEST(epoll23)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 0);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 0);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *          t0
 *           | (p)
 *          e0
 *           | (et)
 *          e1
 *           | (et)
 *          s0
 */
TEST(epoll24)
अणु
	पूर्णांक efd[2];
	पूर्णांक sfd[2];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 0);
	EXPECT_EQ(epoll_रुको(efd[0], &e, 1, 0), 0);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (lt)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll25)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (lt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll26)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll27)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 1);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll28)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 1);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (lt)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll29)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (lt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll30)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (et)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll31)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 1);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll32)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 1);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll33)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll34)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1o, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_or(&ctx.count, 2);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll35)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll36)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1o, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_or(&ctx.count, 2);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll37)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll38)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1o, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_or(&ctx.count, 2);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll39)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll40)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1o, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_or(&ctx.count, 2);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll41)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll42)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1op, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_or(&ctx.count, 2);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll43)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll44)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1op, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_or(&ctx.count, 2);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll45)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (lt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll46)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1op, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_or(&ctx.count, 2);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (lt)
 *           s0
 */
TEST(epoll47)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoll48)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1op, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry1, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_or(&ctx.count, 2);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_TRUE((ctx.count == 2) || (ctx.count == 3));

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

/*
 *           t0
 *            | (ew)
 *           e0
 *     (lt) /  \ (lt)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll49)
अणु
	पूर्णांक efd[3];
	पूर्णांक sfd[4];
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	efd[2] = epoll_create(1);
	ASSERT_GE(efd[2], 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[2], EPOLL_CTL_ADD, sfd[2], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 2);
	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 2);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(efd[2]);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *           t0
 *            | (ew)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll50)
अणु
	पूर्णांक efd[3];
	पूर्णांक sfd[4];
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	efd[2] = epoll_create(1);
	ASSERT_GE(efd[2], 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[2], EPOLL_CTL_ADD, sfd[2], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 2);
	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 0);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(efd[2]);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *           t0
 *            | (p)
 *           e0
 *     (lt) /  \ (lt)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll51)
अणु
	पूर्णांक efd[3];
	पूर्णांक sfd[4];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	efd[2] = epoll_create(1);
	ASSERT_GE(efd[2], 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[2], EPOLL_CTL_ADD, sfd[2], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 2);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 2);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(efd[2]);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *           t0
 *            | (p)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll52)
अणु
	पूर्णांक efd[3];
	पूर्णांक sfd[4];
	काष्ठा pollfd pfd;
	काष्ठा epoll_event events[2];

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &sfd[2]), 0);

	efd[0] = epoll_create(1);
	ASSERT_GE(efd[0], 0);

	efd[1] = epoll_create(1);
	ASSERT_GE(efd[1], 0);

	efd[2] = epoll_create(1);
	ASSERT_GE(efd[2], 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[1], EPOLL_CTL_ADD, sfd[0], events), 0);

	events[0].events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd[2], EPOLL_CTL_ADD, sfd[2], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[1], events), 0);

	events[0].events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(efd[0], EPOLL_CTL_ADD, efd[2], events), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);
	ASSERT_EQ(ग_लिखो(sfd[3], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 1);
	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 2);

	pfd.fd = efd[0];
	pfd.events = POLLIN;
	EXPECT_EQ(poll(&pfd, 1, 0), 0);
	EXPECT_EQ(epoll_रुको(efd[0], events, 2, 0), 0);

	बंद(efd[0]);
	बंद(efd[1]);
	बंद(efd[2]);
	बंद(sfd[0]);
	बंद(sfd[1]);
	बंद(sfd[2]);
	बंद(sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (lt) /  \ (lt)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll53)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoll_create(1);
	ASSERT_GE(ctx.efd[2], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[2], EPOLL_CTL_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[2], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.efd[2]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll54)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoll_create(1);
	ASSERT_GE(ctx.efd[2], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[2], EPOLL_CTL_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[2], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.efd[2]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (lt) /  \ (lt)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll55)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoll_create(1);
	ASSERT_GE(ctx.efd[2], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[2], EPOLL_CTL_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[2], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.efd[2]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll56)
अणु
	pthपढ़ो_t emitter;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoll_create(1);
	ASSERT_GE(ctx.efd[2], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[2], EPOLL_CTL_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[2], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	अगर (epoll_रुको(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.efd[2]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *      (p) \  / (p)
 *           e0
 *     (lt) /  \ (lt)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll57)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoll_create(1);
	ASSERT_GE(ctx.efd[2], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[2], EPOLL_CTL_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[2], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	pfd.fd = ctx.efd[0];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.efd[2]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

/*
 *        t0    t1
 *      (p) \  / (p)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (lt) |     | (lt)
 *        s0    s2
 */
TEST(epoll58)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[0]), 0);
	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoll_create(1);
	ASSERT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoll_create(1);
	ASSERT_GE(ctx.efd[2], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[1], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[2], EPOLL_CTL_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[1], &e), 0);

	e.events = EPOLLIN | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.efd[2], &e), 0);

	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&ctx.रुकोer, शून्य, रुकोer_entry1ap, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, emitter_entry2, &ctx), 0);

	pfd.fd = ctx.efd[0];
	pfd.events = POLLIN;
	अगर (poll(&pfd, 1, -1) > 0) अणु
		अगर (epoll_रुको(ctx.efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	पूर्ण

	ASSERT_EQ(pthपढ़ो_join(ctx.रुकोer, शून्य), 0);
	EXPECT_EQ(ctx.count, 2);

	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण

	बंद(ctx.efd[0]);
	बंद(ctx.efd[1]);
	बंद(ctx.efd[2]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
	बंद(ctx.sfd[2]);
	बंद(ctx.sfd[3]);
पूर्ण

अटल व्योम *epoll59_thपढ़ो(व्योम *ctx_)
अणु
	काष्ठा epoll_mtcontext *ctx = ctx_;
	काष्ठा epoll_event e;
	पूर्णांक i;

	क्रम (i = 0; i < 100000; i++) अणु
		जबतक (ctx->count == 0)
			;

		e.events = EPOLLIN | EPOLLERR | EPOLLET;
		epoll_ctl(ctx->efd[0], EPOLL_CTL_MOD, ctx->sfd[0], &e);
		ctx->count = 0;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 *        t0
 *      (p) \
 *           e0
 *     (et) /
 *        e0
 *
 * Based on https://bugzilla.kernel.org/show_bug.cgi?id=205933
 */
TEST(epoll59)
अणु
	pthपढ़ो_t emitter;
	काष्ठा pollfd pfd;
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;
	पूर्णांक i, ret;

	संकेत(SIGUSR1, संकेत_handler);

	ctx.efd[0] = epoll_create1(0);
	ASSERT_GE(ctx.efd[0], 0);

	ctx.sfd[0] = eventfd(1, 0);
	ASSERT_GE(ctx.sfd[0], 0);

	e.events = EPOLLIN | EPOLLERR | EPOLLET;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	ASSERT_EQ(pthपढ़ो_create(&emitter, शून्य, epoll59_thपढ़ो, &ctx), 0);

	क्रम (i = 0; i < 100000; i++) अणु
		ret = epoll_रुको(ctx.efd[0], &e, 1, 1000);
		ASSERT_GT(ret, 0);

		जबतक (ctx.count != 0)
			;
		ctx.count = 1;
	पूर्ण
	अगर (pthपढ़ो_tryjoin_np(emitter, शून्य) < 0) अणु
		pthपढ़ो_समाप्त(emitter, SIGUSR1);
		pthपढ़ो_join(emitter, शून्य);
	पूर्ण
	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
पूर्ण

क्रमागत अणु
	EPOLL60_EVENTS_NR = 10,
पूर्ण;

काष्ठा epoll60_ctx अणु
	अस्थिर पूर्णांक stopped;
	पूर्णांक पढ़ोy;
	पूर्णांक रुकोers;
	पूर्णांक epfd;
	पूर्णांक evfd[EPOLL60_EVENTS_NR];
पूर्ण;

अटल व्योम *epoll60_रुको_thपढ़ो(व्योम *ctx_)
अणु
	काष्ठा epoll60_ctx *ctx = ctx_;
	काष्ठा epoll_event e;
	sigset_t sigmask;
	uपूर्णांक64_t v;
	पूर्णांक ret;

	/* Block SIGUSR1 */
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSR1);
	sigprocmask(SIG_SETMASK, &sigmask, शून्य);

	/* Prepare empty mask क्रम epoll_pरुको() */
	sigemptyset(&sigmask);

	जबतक (!ctx->stopped) अणु
		/* Mark we are पढ़ोy */
		__atomic_fetch_add(&ctx->पढ़ोy, 1, __ATOMIC_ACQUIRE);

		/* Start when all are पढ़ोy */
		जबतक (__atomic_load_n(&ctx->पढ़ोy, __ATOMIC_ACQUIRE) &&
		       !ctx->stopped);

		/* Account this रुकोer */
		__atomic_fetch_add(&ctx->रुकोers, 1, __ATOMIC_ACQUIRE);

		ret = epoll_pरुको(ctx->epfd, &e, 1, 2000, &sigmask);
		अगर (ret != 1) अणु
			/* We expect only संकेत delivery on stop */
			निश्चित(ret < 0 && त्रुटि_सं == EINTR && "Lost wakeup!\n");
			निश्चित(ctx->stopped);
			अवरोध;
		पूर्ण

		ret = पढ़ो(e.data.fd, &v, माप(v));
		/* Since we are on ET mode, thus each thपढ़ो माला_लो its own fd. */
		निश्चित(ret == माप(v));

		__atomic_fetch_sub(&ctx->रुकोers, 1, __ATOMIC_RELEASE);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ msecs(व्योम)
अणु
	काष्ठा बारpec ts;
	अचिन्हित दीर्घ दीर्घ msecs;

	घड़ी_समय_लो(CLOCK_REALTIME, &ts);
	msecs = ts.tv_sec * 1000ull;
	msecs += ts.tv_nsec / 1000000ull;

	वापस msecs;
पूर्ण

अटल अंतरभूत पूर्णांक count_रुकोers(काष्ठा epoll60_ctx *ctx)
अणु
	वापस __atomic_load_n(&ctx->रुकोers, __ATOMIC_ACQUIRE);
पूर्ण

TEST(epoll60)
अणु
	काष्ठा epoll60_ctx ctx = अणु 0 पूर्ण;
	pthपढ़ो_t रुकोers[ARRAY_SIZE(ctx.evfd)];
	काष्ठा epoll_event e;
	पूर्णांक i, n, ret;

	संकेत(SIGUSR1, संकेत_handler);

	ctx.epfd = epoll_create1(0);
	ASSERT_GE(ctx.epfd, 0);

	/* Create event fds */
	क्रम (i = 0; i < ARRAY_SIZE(ctx.evfd); i++) अणु
		ctx.evfd[i] = eventfd(0, EFD_NONBLOCK);
		ASSERT_GE(ctx.evfd[i], 0);

		e.events = EPOLLIN | EPOLLET;
		e.data.fd = ctx.evfd[i];
		ASSERT_EQ(epoll_ctl(ctx.epfd, EPOLL_CTL_ADD, ctx.evfd[i], &e), 0);
	पूर्ण

	/* Create रुकोer thपढ़ोs */
	क्रम (i = 0; i < ARRAY_SIZE(रुकोers); i++)
		ASSERT_EQ(pthपढ़ो_create(&रुकोers[i], शून्य,
					 epoll60_रुको_thपढ़ो, &ctx), 0);

	क्रम (i = 0; i < 300; i++) अणु
		uपूर्णांक64_t v = 1, ms;

		/* Wait क्रम all to be पढ़ोy */
		जबतक (__atomic_load_n(&ctx.पढ़ोy, __ATOMIC_ACQUIRE) !=
		       ARRAY_SIZE(ctx.evfd))
			;

		/* Steady, go */
		__atomic_fetch_sub(&ctx.पढ़ोy, ARRAY_SIZE(ctx.evfd),
				   __ATOMIC_ACQUIRE);

		/* Wait all have gone to kernel */
		जबतक (count_रुकोers(&ctx) != ARRAY_SIZE(ctx.evfd))
			;

		/* 1ms should be enough to schedule away */
		usleep(1000);

		/* Quickly संकेत all handles at once */
		क्रम (n = 0; n < ARRAY_SIZE(ctx.evfd); n++) अणु
			ret = ग_लिखो(ctx.evfd[n], &v, माप(v));
			ASSERT_EQ(ret, माप(v));
		पूर्ण

		/* Busy loop क्रम 1s and रुको क्रम all रुकोers to wake up */
		ms = msecs();
		जबतक (count_रुकोers(&ctx) && msecs() < ms + 1000)
			;

		ASSERT_EQ(count_रुकोers(&ctx), 0);
	पूर्ण
	ctx.stopped = 1;
	/* Stop रुकोers */
	क्रम (i = 0; i < ARRAY_SIZE(रुकोers); i++)
		ret = pthपढ़ो_समाप्त(रुकोers[i], SIGUSR1);
	क्रम (i = 0; i < ARRAY_SIZE(रुकोers); i++)
		pthपढ़ो_join(रुकोers[i], शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(रुकोers); i++)
		बंद(ctx.evfd[i]);
	बंद(ctx.epfd);
पूर्ण

काष्ठा epoll61_ctx अणु
	पूर्णांक epfd;
	पूर्णांक evfd;
पूर्ण;

अटल व्योम *epoll61_ग_लिखो_eventfd(व्योम *ctx_)
अणु
	काष्ठा epoll61_ctx *ctx = ctx_;
	पूर्णांक64_t l = 1;

	usleep(10950);
	ग_लिखो(ctx->evfd, &l, माप(l));
	वापस शून्य;
पूर्ण

अटल व्योम *epoll61_epoll_with_समयout(व्योम *ctx_)
अणु
	काष्ठा epoll61_ctx *ctx = ctx_;
	काष्ठा epoll_event events[1];
	पूर्णांक n;

	n = epoll_रुको(ctx->epfd, events, 1, 11);
	/*
	 * If epoll वापसed the eventfd, ग_लिखो on the eventfd to wake up the
	 * blocking poller.
	 */
	अगर (n == 1) अणु
		पूर्णांक64_t l = 1;

		ग_लिखो(ctx->evfd, &l, माप(l));
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *epoll61_blocking_epoll(व्योम *ctx_)
अणु
	काष्ठा epoll61_ctx *ctx = ctx_;
	काष्ठा epoll_event events[1];

	epoll_रुको(ctx->epfd, events, 1, -1);
	वापस शून्य;
पूर्ण

TEST(epoll61)
अणु
	काष्ठा epoll61_ctx ctx;
	काष्ठा epoll_event ev;
	पूर्णांक i, r;

	ctx.epfd = epoll_create1(0);
	ASSERT_GE(ctx.epfd, 0);
	ctx.evfd = eventfd(0, EFD_NONBLOCK);
	ASSERT_GE(ctx.evfd, 0);

	ev.events = EPOLLIN | EPOLLET | EPOLLERR | EPOLLHUP;
	ev.data.ptr = शून्य;
	r = epoll_ctl(ctx.epfd, EPOLL_CTL_ADD, ctx.evfd, &ev);
	ASSERT_EQ(r, 0);

	/*
	 * We are testing a race.  Repeat the test हाल 1000 बार to make it
	 * more likely to fail in हाल of a bug.
	 */
	क्रम (i = 0; i < 1000; i++) अणु
		pthपढ़ो_t thपढ़ोs[3];
		पूर्णांक n;

		/*
		 * Start 3 thपढ़ोs:
		 * Thपढ़ो 1 sleeps क्रम 10.9ms and ग_लिखोs to the evenfd.
		 * Thपढ़ो 2 calls epoll with a समयout of 11ms.
		 * Thपढ़ो 3 calls epoll with a समयout of -1.
		 *
		 * The eventfd ग_लिखो by Thपढ़ो 1 should either wakeup Thपढ़ो 2
		 * or Thपढ़ो 3.  If it wakes up Thपढ़ो 2, Thपढ़ो 2 ग_लिखोs on the
		 * eventfd to wake up Thपढ़ो 3.
		 *
		 * If no events are missed, all three thपढ़ोs should eventually
		 * be joinable.
		 */
		ASSERT_EQ(pthपढ़ो_create(&thपढ़ोs[0], शून्य,
					 epoll61_ग_लिखो_eventfd, &ctx), 0);
		ASSERT_EQ(pthपढ़ो_create(&thपढ़ोs[1], शून्य,
					 epoll61_epoll_with_समयout, &ctx), 0);
		ASSERT_EQ(pthपढ़ो_create(&thपढ़ोs[2], शून्य,
					 epoll61_blocking_epoll, &ctx), 0);

		क्रम (n = 0; n < ARRAY_SIZE(thपढ़ोs); ++n)
			ASSERT_EQ(pthपढ़ो_join(thपढ़ोs[n], शून्य), 0);
	पूर्ण

	बंद(ctx.epfd);
	बंद(ctx.evfd);
पूर्ण

/* Equivalent to basic test epoll1, but exercising epoll_pरुको2. */
TEST(epoll62)
अणु
	पूर्णांक efd;
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], &e), 0);

	ASSERT_EQ(ग_लिखो(sfd[1], "w", 1), 1);

	EXPECT_EQ(sys_epoll_pरुको2(efd, &e, 1, शून्य, शून्य, 0), 1);
	EXPECT_EQ(sys_epoll_pरुको2(efd, &e, 1, शून्य, शून्य, 0), 1);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/* Epoll_pरुको2 basic समयout test. */
TEST(epoll63)
अणु
	स्थिर पूर्णांक cfg_delay_ms = 10;
	अचिन्हित दीर्घ दीर्घ tdअगरf;
	काष्ठा __kernel_बारpec ts;
	पूर्णांक efd;
	पूर्णांक sfd[2];
	काष्ठा epoll_event e;

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sfd), 0);

	efd = epoll_create(1);
	ASSERT_GE(efd, 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(efd, EPOLL_CTL_ADD, sfd[0], &e), 0);

	ts.tv_sec = 0;
	ts.tv_nsec = cfg_delay_ms * 1000 * 1000;

	tdअगरf = msecs();
	EXPECT_EQ(sys_epoll_pरुको2(efd, &e, 1, &ts, शून्य, 0), 0);
	tdअगरf = msecs() - tdअगरf;

	EXPECT_GE(tdअगरf, cfg_delay_ms);

	बंद(efd);
	बंद(sfd[0]);
	बंद(sfd[1]);
पूर्ण

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (lt)
 *           s0
 */
TEST(epoll64)
अणु
	pthपढ़ो_t रुकोer[2];
	काष्ठा epoll_event e;
	काष्ठा epoll_mtcontext ctx = अणु 0 पूर्ण;

	संकेत(SIGUSR1, संकेत_handler);

	ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoll_create(1);
	ASSERT_GE(ctx.efd[0], 0);

	e.events = EPOLLIN;
	ASSERT_EQ(epoll_ctl(ctx.efd[0], EPOLL_CTL_ADD, ctx.sfd[0], &e), 0);

	/*
	 * मुख्य will act as the emitter once both रुकोer thपढ़ोs are
	 * blocked and expects to both be awoken upon the पढ़ोy event.
	 */
	ctx.मुख्य = pthपढ़ो_self();
	ASSERT_EQ(pthपढ़ो_create(&रुकोer[0], शून्य, रुकोer_entry1a, &ctx), 0);
	ASSERT_EQ(pthपढ़ो_create(&रुकोer[1], शून्य, रुकोer_entry1a, &ctx), 0);

	usleep(100000);
	ASSERT_EQ(ग_लिखो(ctx.sfd[1], "w", 1), 1);

	ASSERT_EQ(pthपढ़ो_join(रुकोer[0], शून्य), 0);
	ASSERT_EQ(pthपढ़ो_join(रुकोer[1], शून्य), 0);

	EXPECT_EQ(ctx.count, 2);

	बंद(ctx.efd[0]);
	बंद(ctx.sfd[0]);
	बंद(ctx.sfd[1]);
पूर्ण

TEST_HARNESS_MAIN
