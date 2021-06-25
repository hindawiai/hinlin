<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test क्रम perf events with SIGTRAP across all thपढ़ोs.
 *
 * Copyright (C) 2021, Google LLC.
 */

#घोषणा _GNU_SOURCE

/* We need the latest siginfo from the kernel repo. */
#समावेश <sys/types.h>
#समावेश <यंत्र/siginfo.h>
#घोषणा __have_siginfo_t 1
#घोषणा __have_sigval_t 1
#घोषणा __have_sigevent_t 1
#घोषणा __siginfo_t_defined
#घोषणा __sigval_t_defined
#घोषणा __sigevent_t_defined
#घोषणा _BITS_SIGINFO_CONSTS_H 1
#घोषणा _BITS_SIGEVENT_CONSTS_H 1

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/perf_event.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>

#समावेश "../kselftest_harness.h"

#घोषणा NUM_THREADS 5

/* Data shared between test body, thपढ़ोs, and संकेत handler. */
अटल काष्ठा अणु
	पूर्णांक tids_want_संकेत;		/* Which thपढ़ोs still want a संकेत. */
	पूर्णांक संकेत_count;		/* Sanity check number of संकेतs received. */
	अस्थिर पूर्णांक iterate_on;	/* Variable to set अवरोधpoपूर्णांक on. */
	siginfo_t first_siginfo;	/* First observed siginfo_t. */
पूर्ण ctx;

/* Unique value to check si_perf_data is correctly set from perf_event_attr::sig_data. */
#घोषणा TEST_SIG_DATA(addr) (~(अचिन्हित दीर्घ)(addr))

अटल काष्ठा perf_event_attr make_event_attr(bool enabled, अस्थिर व्योम *addr)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type		= PERF_TYPE_BREAKPOINT,
		.size		= माप(attr),
		.sample_period	= 1,
		.disabled	= !enabled,
		.bp_addr	= (अचिन्हित दीर्घ)addr,
		.bp_type	= HW_BREAKPOINT_RW,
		.bp_len		= HW_BREAKPOINT_LEN_1,
		.inherit	= 1, /* Children inherit events ... */
		.inherit_thपढ़ो = 1, /* ... but only cloned with CLONE_THREAD. */
		.हटाओ_on_exec = 1, /* Required by sigtrap. */
		.sigtrap	= 1, /* Request synchronous SIGTRAP on event. */
		.sig_data	= TEST_SIG_DATA(addr),
	पूर्ण;
	वापस attr;
पूर्ण

अटल व्योम sigtrap_handler(पूर्णांक signum, siginfo_t *info, व्योम *ucontext)
अणु
	अगर (info->si_code != TRAP_PERF) अणु
		ख_लिखो(मानक_त्रुटि, "%s: unexpected si_code %d\n", __func__, info->si_code);
		वापस;
	पूर्ण

	/*
	 * The data in siginfo_t we're पूर्णांकerested in should all be the same
	 * across thपढ़ोs.
	 */
	अगर (!__atomic_fetch_add(&ctx.संकेत_count, 1, __ATOMIC_RELAXED))
		ctx.first_siginfo = *info;
	__atomic_fetch_sub(&ctx.tids_want_संकेत, syscall(__NR_gettid), __ATOMIC_RELAXED);
पूर्ण

अटल व्योम *test_thपढ़ो(व्योम *arg)
अणु
	pthपढ़ो_barrier_t *barrier = (pthपढ़ो_barrier_t *)arg;
	pid_t tid = syscall(__NR_gettid);
	पूर्णांक iter;
	पूर्णांक i;

	pthपढ़ो_barrier_रुको(barrier);

	__atomic_fetch_add(&ctx.tids_want_संकेत, tid, __ATOMIC_RELAXED);
	iter = ctx.iterate_on; /* पढ़ो */
	क्रम (i = 0; i < iter - 1; i++) अणु
		__atomic_fetch_add(&ctx.tids_want_संकेत, tid, __ATOMIC_RELAXED);
		ctx.iterate_on = iter; /* idempotent ग_लिखो */
	पूर्ण

	वापस शून्य;
पूर्ण

FIXTURE(sigtrap_thपढ़ोs)
अणु
	काष्ठा sigaction oldact;
	pthपढ़ो_t thपढ़ोs[NUM_THREADS];
	pthपढ़ो_barrier_t barrier;
	पूर्णांक fd;
पूर्ण;

FIXTURE_SETUP(sigtrap_thपढ़ोs)
अणु
	काष्ठा perf_event_attr attr = make_event_attr(false, &ctx.iterate_on);
	काष्ठा sigaction action = अणुपूर्ण;
	पूर्णांक i;

	स_रखो(&ctx, 0, माप(ctx));

	/* Initialize sigtrap handler. */
	action.sa_flags = SA_SIGINFO | SA_NODEFER;
	action.sa_sigaction = sigtrap_handler;
	sigemptyset(&action.sa_mask);
	ASSERT_EQ(sigaction(SIGTRAP, &action, &self->oldact), 0);

	/* Initialize perf event. */
	self->fd = syscall(__NR_perf_event_खोलो, &attr, 0, -1, -1, PERF_FLAG_FD_CLOEXEC);
	ASSERT_NE(self->fd, -1);

	/* Spawn thपढ़ोs inheriting perf event. */
	pthपढ़ो_barrier_init(&self->barrier, शून्य, NUM_THREADS + 1);
	क्रम (i = 0; i < NUM_THREADS; i++)
		ASSERT_EQ(pthपढ़ो_create(&self->thपढ़ोs[i], शून्य, test_thपढ़ो, &self->barrier), 0);
पूर्ण

FIXTURE_TEARDOWN(sigtrap_thपढ़ोs)
अणु
	pthपढ़ो_barrier_destroy(&self->barrier);
	बंद(self->fd);
	sigaction(SIGTRAP, &self->oldact, शून्य);
पूर्ण

अटल व्योम run_test_thपढ़ोs(काष्ठा __test_metadata *_metadata,
			     FIXTURE_DATA(sigtrap_thपढ़ोs) *self)
अणु
	पूर्णांक i;

	pthपढ़ो_barrier_रुको(&self->barrier);
	क्रम (i = 0; i < NUM_THREADS; i++)
		ASSERT_EQ(pthपढ़ो_join(self->thपढ़ोs[i], शून्य), 0);
पूर्ण

TEST_F(sigtrap_thपढ़ोs, reमुख्य_disabled)
अणु
	run_test_thपढ़ोs(_metadata, self);
	EXPECT_EQ(ctx.संकेत_count, 0);
	EXPECT_NE(ctx.tids_want_संकेत, 0);
पूर्ण

TEST_F(sigtrap_thपढ़ोs, enable_event)
अणु
	EXPECT_EQ(ioctl(self->fd, PERF_EVENT_IOC_ENABLE, 0), 0);
	run_test_thपढ़ोs(_metadata, self);

	EXPECT_EQ(ctx.संकेत_count, NUM_THREADS);
	EXPECT_EQ(ctx.tids_want_संकेत, 0);
	EXPECT_EQ(ctx.first_siginfo.si_addr, &ctx.iterate_on);
	EXPECT_EQ(ctx.first_siginfo.si_perf_type, PERF_TYPE_BREAKPOINT);
	EXPECT_EQ(ctx.first_siginfo.si_perf_data, TEST_SIG_DATA(&ctx.iterate_on));

	/* Check enabled क्रम parent. */
	ctx.iterate_on = 0;
	EXPECT_EQ(ctx.संकेत_count, NUM_THREADS + 1);
पूर्ण

/* Test that modअगरication propagates to all inherited events. */
TEST_F(sigtrap_thपढ़ोs, modअगरy_and_enable_event)
अणु
	काष्ठा perf_event_attr new_attr = make_event_attr(true, &ctx.iterate_on);

	EXPECT_EQ(ioctl(self->fd, PERF_EVENT_IOC_MODIFY_ATTRIBUTES, &new_attr), 0);
	run_test_thपढ़ोs(_metadata, self);

	EXPECT_EQ(ctx.संकेत_count, NUM_THREADS);
	EXPECT_EQ(ctx.tids_want_संकेत, 0);
	EXPECT_EQ(ctx.first_siginfo.si_addr, &ctx.iterate_on);
	EXPECT_EQ(ctx.first_siginfo.si_perf_type, PERF_TYPE_BREAKPOINT);
	EXPECT_EQ(ctx.first_siginfo.si_perf_data, TEST_SIG_DATA(&ctx.iterate_on));

	/* Check enabled क्रम parent. */
	ctx.iterate_on = 0;
	EXPECT_EQ(ctx.संकेत_count, NUM_THREADS + 1);
पूर्ण

/* Stress test event + संकेत handling. */
TEST_F(sigtrap_thपढ़ोs, संकेत_stress)
अणु
	ctx.iterate_on = 3000;

	EXPECT_EQ(ioctl(self->fd, PERF_EVENT_IOC_ENABLE, 0), 0);
	run_test_thपढ़ोs(_metadata, self);
	EXPECT_EQ(ioctl(self->fd, PERF_EVENT_IOC_DISABLE, 0), 0);

	EXPECT_EQ(ctx.संकेत_count, NUM_THREADS * ctx.iterate_on);
	EXPECT_EQ(ctx.tids_want_संकेत, 0);
	EXPECT_EQ(ctx.first_siginfo.si_addr, &ctx.iterate_on);
	EXPECT_EQ(ctx.first_siginfo.si_perf_type, PERF_TYPE_BREAKPOINT);
	EXPECT_EQ(ctx.first_siginfo.si_perf_data, TEST_SIG_DATA(&ctx.iterate_on));
पूर्ण

TEST_HARNESS_MAIN
