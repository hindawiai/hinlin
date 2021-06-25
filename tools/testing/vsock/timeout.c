<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Timeout API क्रम single-thपढ़ोed programs that use blocking
 * syscalls (पढ़ो/ग_लिखो/send/recv/connect/accept).
 *
 * Copyright (C) 2017 Red Hat, Inc.
 *
 * Author: Stefan Hajnoczi <stefanha@redhat.com>
 */

/* Use the following pattern:
 *
 *   समयout_begin(TIMEOUT);
 *   करो अणु
 *       ret = accept(...);
 *       समयout_check("accept");
 *   पूर्ण जबतक (ret < 0 && ret == EINTR);
 *   समयout_end();
 */

#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश "timeout.h"

अटल अस्थिर bool समयout;

/* SIGALRM handler function.  Do not use sleep(2), alarm(2), or
 * setiसमयr(2) जबतक using this API - they may पूर्णांकerfere with each
 * other.
 */
व्योम sigalrm(पूर्णांक signo)
अणु
	समयout = true;
पूर्ण

/* Start a समयout.  Call समयout_check() to verअगरy that the समयout hasn't
 * expired.  समयout_end() must be called to stop the समयout.  Timeouts cannot
 * be nested.
 */
व्योम समयout_begin(अचिन्हित पूर्णांक seconds)
अणु
	alarm(seconds);
पूर्ण

/* Exit with an error message अगर the समयout has expired */
व्योम समयout_check(स्थिर अक्षर *operation)
अणु
	अगर (समयout) अणु
		ख_लिखो(मानक_त्रुटि, "%s timed out\n", operation);
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

/* Stop a समयout */
व्योम समयout_end(व्योम)
अणु
	alarm(0);
	समयout = false;
पूर्ण
