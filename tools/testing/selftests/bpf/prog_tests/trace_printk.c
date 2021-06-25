<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Oracle and/or its affiliates. */

#समावेश <test_progs.h>

#समावेश "trace_printk.skel.h"

#घोषणा TRACEBUF	"/sys/kernel/debug/tracing/trace_pipe"
#घोषणा SEARCHMSG	"testing,testing"

व्योम test_trace_prपूर्णांकk(व्योम)
अणु
	पूर्णांक err, iter = 0, duration = 0, found = 0;
	काष्ठा trace_prपूर्णांकk__bss *bss;
	काष्ठा trace_prपूर्णांकk *skel;
	अक्षर *buf = शून्य;
	खाता *fp = शून्य;
	माप_प्रकार buflen;

	skel = trace_prपूर्णांकk__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	err = trace_prपूर्णांकk__load(skel);
	अगर (CHECK(err, "skel_load", "failed to load skeleton: %d\n", err))
		जाओ cleanup;

	bss = skel->bss;

	err = trace_prपूर्णांकk__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	fp = ख_खोलो(TRACEBUF, "r");
	अगर (CHECK(fp == शून्य, "could not open trace buffer",
		  "error %d opening %s", त्रुटि_सं, TRACEBUF))
		जाओ cleanup;

	/* We करो not want to रुको क्रमever अगर this test fails... */
	fcntl(fileno(fp), F_SETFL, O_NONBLOCK);

	/* रुको क्रम tracepoपूर्णांक to trigger */
	usleep(1);
	trace_prपूर्णांकk__detach(skel);

	अगर (CHECK(bss->trace_prपूर्णांकk_ran == 0,
		  "bpf_trace_printk never ran",
		  "ran == %d", bss->trace_prपूर्णांकk_ran))
		जाओ cleanup;

	अगर (CHECK(bss->trace_prपूर्णांकk_ret <= 0,
		  "bpf_trace_printk returned <= 0 value",
		  "got %d", bss->trace_prपूर्णांकk_ret))
		जाओ cleanup;

	/* verअगरy our search string is in the trace buffer */
	जबतक (getline(&buf, &buflen, fp) >= 0 || त्रुटि_सं == EAGAIN) अणु
		अगर (म_माला(buf, SEARCHMSG) != शून्य)
			found++;
		अगर (found == bss->trace_prपूर्णांकk_ran)
			अवरोध;
		अगर (++iter > 1000)
			अवरोध;
	पूर्ण

	अगर (CHECK(!found, "message from bpf_trace_printk not found",
		  "no instance of %s in %s", SEARCHMSG, TRACEBUF))
		जाओ cleanup;

cleanup:
	trace_prपूर्णांकk__destroy(skel);
	मुक्त(buf);
	अगर (fp)
		ख_बंद(fp);
पूर्ण
