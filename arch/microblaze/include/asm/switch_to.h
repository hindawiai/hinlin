<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_SWITCH_TO_H
#घोषणा _ASM_MICROBLAZE_SWITCH_TO_H

काष्ठा task_काष्ठा;
काष्ठा thपढ़ो_info;

बाह्य काष्ठा task_काष्ठा *_चयन_to(काष्ठा thपढ़ो_info *prev,
					काष्ठा thपढ़ो_info *next);

#घोषणा चयन_to(prev, next, last)					\
	करो अणु								\
		(last) = _चयन_to(task_thपढ़ो_info(prev),		\
					task_thपढ़ो_info(next));	\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_MICROBLAZE_SWITCH_TO_H */
