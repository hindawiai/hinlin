<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_UNWIND_LIBDW_H
#घोषणा __PERF_UNWIND_LIBDW_H

#समावेश <elfutils/libdwfl.h>
#समावेश "unwind.h"

काष्ठा machine;
काष्ठा perf_sample;
काष्ठा thपढ़ो;

bool libdw__arch_set_initial_रेजिस्टरs(Dwfl_Thपढ़ो *thपढ़ो, व्योम *arg);

काष्ठा unwind_info अणु
	Dwfl			*dwfl;
	काष्ठा perf_sample      *sample;
	काष्ठा machine          *machine;
	काष्ठा thपढ़ो           *thपढ़ो;
	unwind_entry_cb_t	cb;
	व्योम			*arg;
	पूर्णांक			max_stack;
	पूर्णांक			idx;
	काष्ठा unwind_entry	entries[];
पूर्ण;

#पूर्ण_अगर /* __PERF_UNWIND_LIBDW_H */
