<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Generic task चयन macro wrapper.
 *
 * It should be possible to use these on really simple architectures,
 * but it serves more as a starting poपूर्णांक क्रम new ports.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अगर_अघोषित __ASM_GENERIC_SWITCH_TO_H
#घोषणा __ASM_GENERIC_SWITCH_TO_H

#समावेश <linux/thपढ़ो_info.h>

/*
 * Context चयनing is now perक्रमmed out-of-line in चयन_to.S
 */
बाह्य काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *,
				       काष्ठा task_काष्ठा *);

#घोषणा चयन_to(prev, next, last)					\
	करो अणु								\
		((last) = __चयन_to((prev), (next)));			\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_GENERIC_SWITCH_TO_H */
