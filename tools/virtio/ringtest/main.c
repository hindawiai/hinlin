<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * Command line processing and common functions क्रम ring benchmarking.
 */
#घोषणा _GNU_SOURCE
#समावेश <getopt.h>
#समावेश <pthपढ़ो.h>
#समावेश <निश्चित.स>
#समावेश <sched.h>
#समावेश "main.h"
#समावेश <sys/eventfd.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <सीमा.स>

पूर्णांक runcycles = 10000000;
पूर्णांक max_outstanding = पूर्णांक_उच्च;
पूर्णांक batch = 1;
पूर्णांक param = 0;

bool करो_sleep = false;
bool करो_relax = false;
bool करो_निकास = true;

अचिन्हित ring_size = 256;

अटल पूर्णांक kickfd = -1;
अटल पूर्णांक callfd = -1;

व्योम notअगरy(पूर्णांक fd)
अणु
	अचिन्हित दीर्घ दीर्घ v = 1;
	पूर्णांक r;

	vmनिकास();
	r = ग_लिखो(fd, &v, माप v);
	निश्चित(r == माप v);
	vmentry();
पूर्ण

व्योम रुको_क्रम_notअगरy(पूर्णांक fd)
अणु
	अचिन्हित दीर्घ दीर्घ v = 1;
	पूर्णांक r;

	vmनिकास();
	r = पढ़ो(fd, &v, माप v);
	निश्चित(r == माप v);
	vmentry();
पूर्ण

व्योम kick(व्योम)
अणु
	notअगरy(kickfd);
पूर्ण

व्योम रुको_क्रम_kick(व्योम)
अणु
	रुको_क्रम_notअगरy(kickfd);
पूर्ण

व्योम call(व्योम)
अणु
	notअगरy(callfd);
पूर्ण

व्योम रुको_क्रम_call(व्योम)
अणु
	रुको_क्रम_notअगरy(callfd);
पूर्ण

व्योम set_affinity(स्थिर अक्षर *arg)
अणु
	cpu_set_t cpuset;
	पूर्णांक ret;
	pthपढ़ो_t self;
	दीर्घ पूर्णांक cpu;
	अक्षर *endptr;

	अगर (!arg)
		वापस;

	cpu = म_से_दीर्घ(arg, &endptr, 0);
	निश्चित(!*endptr);

	निश्चित(cpu >= 0 && cpu < CPU_SETSIZE);

	self = pthपढ़ो_self();
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	ret = pthपढ़ो_setaffinity_np(self, माप(cpu_set_t), &cpuset);
	निश्चित(!ret);
पूर्ण

व्योम poll_used(व्योम)
अणु
	जबतक (used_empty())
		busy_रुको();
पूर्ण

अटल व्योम __attribute__((__flatten__)) run_guest(व्योम)
अणु
	पूर्णांक completed_beक्रमe;
	पूर्णांक completed = 0;
	पूर्णांक started = 0;
	पूर्णांक bufs = runcycles;
	पूर्णांक spurious = 0;
	पूर्णांक r;
	अचिन्हित len;
	व्योम *buf;
	पूर्णांक tokick = batch;

	क्रम (;;) अणु
		अगर (करो_sleep)
			disable_call();
		completed_beक्रमe = completed;
		करो अणु
			अगर (started < bufs &&
			    started - completed < max_outstanding) अणु
				r = add_inbuf(0, "Buffer\n", "Hello, world!");
				अगर (__builtin_expect(r == 0, true)) अणु
					++started;
					अगर (!--tokick) अणु
						tokick = batch;
						अगर (करो_sleep)
							kick_available();
					पूर्ण

				पूर्ण
			पूर्ण अन्यथा
				r = -1;

			/* Flush out completed bufs अगर any */
			अगर (get_buf(&len, &buf)) अणु
				++completed;
				अगर (__builtin_expect(completed == bufs, false))
					वापस;
				r = 0;
			पूर्ण
		पूर्ण जबतक (r == 0);
		अगर (completed == completed_beक्रमe)
			++spurious;
		निश्चित(completed <= bufs);
		निश्चित(started <= bufs);
		अगर (करो_sleep) अणु
			अगर (used_empty() && enable_call())
				रुको_क्रम_call();
		पूर्ण अन्यथा अणु
			poll_used();
		पूर्ण
	पूर्ण
पूर्ण

व्योम poll_avail(व्योम)
अणु
	जबतक (avail_empty())
		busy_रुको();
पूर्ण

अटल व्योम __attribute__((__flatten__)) run_host(व्योम)
अणु
	पूर्णांक completed_beक्रमe;
	पूर्णांक completed = 0;
	पूर्णांक spurious = 0;
	पूर्णांक bufs = runcycles;
	अचिन्हित len;
	व्योम *buf;

	क्रम (;;) अणु
		अगर (करो_sleep) अणु
			अगर (avail_empty() && enable_kick())
				रुको_क्रम_kick();
		पूर्ण अन्यथा अणु
			poll_avail();
		पूर्ण
		अगर (करो_sleep)
			disable_kick();
		completed_beक्रमe = completed;
		जबतक (__builtin_expect(use_buf(&len, &buf), true)) अणु
			अगर (करो_sleep)
				call_used();
			++completed;
			अगर (__builtin_expect(completed == bufs, false))
				वापस;
		पूर्ण
		अगर (completed == completed_beक्रमe)
			++spurious;
		निश्चित(completed <= bufs);
		अगर (completed == bufs)
			अवरोध;
	पूर्ण
पूर्ण

व्योम *start_guest(व्योम *arg)
अणु
	set_affinity(arg);
	run_guest();
	pthपढ़ो_निकास(शून्य);
पूर्ण

व्योम *start_host(व्योम *arg)
अणु
	set_affinity(arg);
	run_host();
	pthपढ़ो_निकास(शून्य);
पूर्ण

अटल स्थिर अक्षर optstring[] = "";
अटल स्थिर काष्ठा option दीर्घopts[] = अणु
	अणु
		.name = "help",
		.has_arg = no_argument,
		.val = 'h',
	पूर्ण,
	अणु
		.name = "host-affinity",
		.has_arg = required_argument,
		.val = 'H',
	पूर्ण,
	अणु
		.name = "guest-affinity",
		.has_arg = required_argument,
		.val = 'G',
	पूर्ण,
	अणु
		.name = "ring-size",
		.has_arg = required_argument,
		.val = 'R',
	पूर्ण,
	अणु
		.name = "run-cycles",
		.has_arg = required_argument,
		.val = 'C',
	पूर्ण,
	अणु
		.name = "outstanding",
		.has_arg = required_argument,
		.val = 'o',
	पूर्ण,
	अणु
		.name = "batch",
		.has_arg = required_argument,
		.val = 'b',
	पूर्ण,
	अणु
		.name = "param",
		.has_arg = required_argument,
		.val = 'p',
	पूर्ण,
	अणु
		.name = "sleep",
		.has_arg = no_argument,
		.val = 's',
	पूर्ण,
	अणु
		.name = "relax",
		.has_arg = no_argument,
		.val = 'x',
	पूर्ण,
	अणु
		.name = "exit",
		.has_arg = no_argument,
		.val = 'e',
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल व्योम help(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: <test> [--help]"
		" [--host-affinity H]"
		" [--guest-affinity G]"
		" [--ring-size R (default: %d)]"
		" [--run-cycles C (default: %d)]"
		" [--batch b]"
		" [--outstanding o]"
		" [--param p]"
		" [--sleep]"
		" [--relax]"
		" [--exit]"
		"\n",
		ring_size,
		runcycles);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ret;
	pthपढ़ो_t host, guest;
	व्योम *tret;
	अक्षर *host_arg = शून्य;
	अक्षर *guest_arg = शून्य;
	अक्षर *endptr;
	दीर्घ पूर्णांक c;

	kickfd = eventfd(0, 0);
	निश्चित(kickfd >= 0);
	callfd = eventfd(0, 0);
	निश्चित(callfd >= 0);

	क्रम (;;) अणु
		पूर्णांक o = getopt_दीर्घ(argc, argv, optstring, दीर्घopts, शून्य);
		चयन (o) अणु
		हाल -1:
			जाओ करोne;
		हाल '?':
			help();
			निकास(2);
		हाल 'H':
			host_arg = optarg;
			अवरोध;
		हाल 'G':
			guest_arg = optarg;
			अवरोध;
		हाल 'R':
			ring_size = म_से_दीर्घ(optarg, &endptr, 0);
			निश्चित(ring_size && !(ring_size & (ring_size - 1)));
			निश्चित(!*endptr);
			अवरोध;
		हाल 'C':
			c = म_से_दीर्घ(optarg, &endptr, 0);
			निश्चित(!*endptr);
			निश्चित(c > 0 && c < पूर्णांक_उच्च);
			runcycles = c;
			अवरोध;
		हाल 'o':
			c = म_से_दीर्घ(optarg, &endptr, 0);
			निश्चित(!*endptr);
			निश्चित(c > 0 && c < पूर्णांक_उच्च);
			max_outstanding = c;
			अवरोध;
		हाल 'p':
			c = म_से_दीर्घ(optarg, &endptr, 0);
			निश्चित(!*endptr);
			निश्चित(c > 0 && c < पूर्णांक_उच्च);
			param = c;
			अवरोध;
		हाल 'b':
			c = म_से_दीर्घ(optarg, &endptr, 0);
			निश्चित(!*endptr);
			निश्चित(c > 0 && c < पूर्णांक_उच्च);
			batch = c;
			अवरोध;
		हाल 's':
			करो_sleep = true;
			अवरोध;
		हाल 'x':
			करो_relax = true;
			अवरोध;
		हाल 'e':
			करो_निकास = true;
			अवरोध;
		शेष:
			help();
			निकास(4);
			अवरोध;
		पूर्ण
	पूर्ण

	/* करोes nothing here, used to make sure all smp APIs compile */
	smp_acquire();
	smp_release();
	smp_mb();
करोne:

	अगर (batch > max_outstanding)
		batch = max_outstanding;

	अगर (optind < argc) अणु
		help();
		निकास(4);
	पूर्ण
	alloc_ring();

	ret = pthपढ़ो_create(&host, शून्य, start_host, host_arg);
	निश्चित(!ret);
	ret = pthपढ़ो_create(&guest, शून्य, start_guest, guest_arg);
	निश्चित(!ret);

	ret = pthपढ़ो_join(guest, &tret);
	निश्चित(!ret);
	ret = pthपढ़ो_join(host, &tret);
	निश्चित(!ret);
	वापस 0;
पूर्ण
