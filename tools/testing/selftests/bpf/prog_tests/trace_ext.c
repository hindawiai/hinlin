<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/sched.h>
#समावेश <sys/syscall.h>

#समावेश "test_pkt_md_access.skel.h"
#समावेश "test_trace_ext.skel.h"
#समावेश "test_trace_ext_tracing.skel.h"

अटल __u32 duration;

व्योम test_trace_ext(व्योम)
अणु
	काष्ठा test_pkt_md_access *skel_pkt = शून्य;
	काष्ठा test_trace_ext_tracing *skel_trace = शून्य;
	काष्ठा test_trace_ext_tracing__bss *bss_trace;
	काष्ठा test_trace_ext *skel_ext = शून्य;
	काष्ठा test_trace_ext__bss *bss_ext;
	पूर्णांक err, pkt_fd, ext_fd;
	काष्ठा bpf_program *prog;
	अक्षर buf[100];
	__u32 retval;
	__u64 len;

	/* खोलो/load/attach test_pkt_md_access */
	skel_pkt = test_pkt_md_access__खोलो_and_load();
	अगर (CHECK(!skel_pkt, "setup", "classifier/test_pkt_md_access open failed\n"))
		जाओ cleanup;

	err = test_pkt_md_access__attach(skel_pkt);
	अगर (CHECK(err, "setup", "classifier/test_pkt_md_access attach failed: %d\n", err))
		जाओ cleanup;

	prog = skel_pkt->progs.test_pkt_md_access;
	pkt_fd = bpf_program__fd(prog);

	/* खोलो extension */
	skel_ext = test_trace_ext__खोलो();
	अगर (CHECK(!skel_ext, "setup", "freplace/test_pkt_md_access open failed\n"))
		जाओ cleanup;

	/* set extension's attach target - test_pkt_md_access  */
	prog = skel_ext->progs.test_pkt_md_access_new;
	bpf_program__set_attach_target(prog, pkt_fd, "test_pkt_md_access");

	/* load/attach extension */
	err = test_trace_ext__load(skel_ext);
	अगर (CHECK(err, "setup", "freplace/test_pkt_md_access load failed\n")) अणु
		libbpf_म_त्रुटि(err, buf, माप(buf));
		ख_लिखो(मानक_त्रुटि, "%s\n", buf);
		जाओ cleanup;
	पूर्ण

	err = test_trace_ext__attach(skel_ext);
	अगर (CHECK(err, "setup", "freplace/test_pkt_md_access attach failed: %d\n", err))
		जाओ cleanup;

	prog = skel_ext->progs.test_pkt_md_access_new;
	ext_fd = bpf_program__fd(prog);

	/* खोलो tracing  */
	skel_trace = test_trace_ext_tracing__खोलो();
	अगर (CHECK(!skel_trace, "setup", "tracing/test_pkt_md_access_new open failed\n"))
		जाओ cleanup;

	/* set tracing's attach target - fentry */
	prog = skel_trace->progs.fentry;
	bpf_program__set_attach_target(prog, ext_fd, "test_pkt_md_access_new");

	/* set tracing's attach target - fनिकास */
	prog = skel_trace->progs.fनिकास;
	bpf_program__set_attach_target(prog, ext_fd, "test_pkt_md_access_new");

	/* load/attach tracing */
	err = test_trace_ext_tracing__load(skel_trace);
	अगर (CHECK(err, "setup", "tracing/test_pkt_md_access_new load failed\n")) अणु
		libbpf_म_त्रुटि(err, buf, माप(buf));
		ख_लिखो(मानक_त्रुटि, "%s\n", buf);
		जाओ cleanup;
	पूर्ण

	err = test_trace_ext_tracing__attach(skel_trace);
	अगर (CHECK(err, "setup", "tracing/test_pkt_md_access_new attach failed: %d\n", err))
		जाओ cleanup;

	/* trigger the test */
	err = bpf_prog_test_run(pkt_fd, 1, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, &retval, &duration);
	CHECK(err || retval, "run", "err %d errno %d retval %d\n", err, त्रुटि_सं, retval);

	bss_ext = skel_ext->bss;
	bss_trace = skel_trace->bss;

	len = bss_ext->ext_called;

	CHECK(bss_ext->ext_called == 0,
		"check", "failed to trigger freplace/test_pkt_md_access\n");
	CHECK(bss_trace->fentry_called != len,
		"check", "failed to trigger fentry/test_pkt_md_access_new\n");
	CHECK(bss_trace->fनिकास_called != len,
		"check", "failed to trigger fexit/test_pkt_md_access_new\n");

cleanup:
	test_trace_ext_tracing__destroy(skel_trace);
	test_trace_ext__destroy(skel_ext);
	test_pkt_md_access__destroy(skel_pkt);
पूर्ण
