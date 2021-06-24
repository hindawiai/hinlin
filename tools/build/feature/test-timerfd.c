<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * test क्रम समयrfd functions used by perf-kvm-stat-live
 */
#समावेश <sys/समयrfd.h>

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा iसमयrspec new_value;

	पूर्णांक fd = समयrfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
	अगर (fd < 0)
		वापस 1;

	अगर (समयrfd_समय_रखो(fd, 0, &new_value, शून्य) != 0)
		वापस 1;

	वापस 0;
पूर्ण
