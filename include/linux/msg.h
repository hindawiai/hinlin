<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MSG_H
#घोषणा _LINUX_MSG_H

#समावेश <linux/list.h>
#समावेश <uapi/linux/msg.h>

/* one msg_msg काष्ठाure क्रम each message */
काष्ठा msg_msg अणु
	काष्ठा list_head m_list;
	दीर्घ m_type;
	माप_प्रकार m_ts;		/* message text size */
	काष्ठा msg_msgseg *next;
	व्योम *security;
	/* the actual message follows immediately */
पूर्ण;

#पूर्ण_अगर /* _LINUX_MSG_H */
