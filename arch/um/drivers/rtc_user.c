<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Intel Corporation
 * Author: Johannes Berg <johannes@sipsolutions.net>
 */
#समावेश <os.h>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <unistd.h>
#समावेश <kern_util.h>
#समावेश <sys/select.h>
#समावेश <मानकपन.स>
#समावेश <sys/समयrfd.h>
#समावेश "rtc.h"

अटल पूर्णांक uml_rtc_irq_fds[2];

व्योम uml_rtc_send_समयtravel_alarm(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ c = 1;

	CATCH_EINTR(ग_लिखो(uml_rtc_irq_fds[1], &c, माप(c)));
पूर्ण

पूर्णांक uml_rtc_start(bool समयtravel)
अणु
	पूर्णांक err;

	अगर (समयtravel) अणु
		पूर्णांक err = os_pipe(uml_rtc_irq_fds, 1, 1);
		अगर (err)
			जाओ fail;
	पूर्ण अन्यथा अणु
		uml_rtc_irq_fds[0] = समयrfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
		अगर (uml_rtc_irq_fds[0] < 0) अणु
			err = -त्रुटि_सं;
			जाओ fail;
		पूर्ण

		/* apparently समयrfd won't send SIGIO, use workaround */
		sigio_broken(uml_rtc_irq_fds[0]);
		err = add_sigio_fd(uml_rtc_irq_fds[0]);
		अगर (err < 0) अणु
			बंद(uml_rtc_irq_fds[0]);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस uml_rtc_irq_fds[0];
fail:
	uml_rtc_stop(समयtravel);
	वापस err;
पूर्ण

पूर्णांक uml_rtc_enable_alarm(अचिन्हित दीर्घ दीर्घ delta_seconds)
अणु
	काष्ठा iसमयrspec it = अणु
		.it_value = अणु
			.tv_sec = delta_seconds,
		पूर्ण,
	पूर्ण;

	अगर (समयrfd_समय_रखो(uml_rtc_irq_fds[0], 0, &it, शून्य))
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

व्योम uml_rtc_disable_alarm(व्योम)
अणु
	uml_rtc_enable_alarm(0);
पूर्ण

व्योम uml_rtc_stop(bool समयtravel)
अणु
	अगर (समयtravel)
		os_बंद_file(uml_rtc_irq_fds[1]);
	अन्यथा
		ignore_sigio_fd(uml_rtc_irq_fds[0]);
	os_बंद_file(uml_rtc_irq_fds[0]);
पूर्ण
