<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_CAP_H
#घोषणा __PERF_CAP_H

#समावेश <stdbool.h>
#समावेश <linux/capability.h>
#समावेश <linux/compiler.h>

#अगर_घोषित HAVE_LIBCAP_SUPPORT

#समावेश <sys/capability.h>

bool perf_cap__capable(cap_value_t cap);

#अन्यथा

#समावेश <unistd.h>
#समावेश <sys/types.h>

अटल अंतरभूत bool perf_cap__capable(पूर्णांक cap __maybe_unused)
अणु
	वापस geteuid() == 0;
पूर्ण

#पूर्ण_अगर /* HAVE_LIBCAP_SUPPORT */

/* For older प्रणालीs */
#अगर_अघोषित CAP_SYSLOG
#घोषणा CAP_SYSLOG	34
#पूर्ण_अगर

#अगर_अघोषित CAP_PERFMON
#घोषणा CAP_PERFMON	38
#पूर्ण_अगर

#पूर्ण_अगर /* __PERF_CAP_H */
