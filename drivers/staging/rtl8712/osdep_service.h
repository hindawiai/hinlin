<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __OSDEP_SERVICE_H_
#घोषणा __OSDEP_SERVICE_H_

#घोषणा _SUCCESS	1
#घोषणा _FAIL		0

#समावेश <linux/spinlock.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sem.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/iw_handler.h>
#समावेश <linux/proc_fs.h>      /* Necessary because we use the proc fs */

#समावेश "basic_types.h"

काष्ठा	__queue	अणु
	काष्ठा	list_head	queue;
	spinlock_t lock;
पूर्ण;

#घोषणा _pkt काष्ठा sk_buff
#घोषणा _buffer अचिन्हित अक्षर
#घोषणा thपढ़ो_निकास() complete_and_निकास(शून्य, 0)

#घोषणा _init_queue(pqueue)				\
	करो अणु						\
		INIT_LIST_HEAD(&((pqueue)->queue));	\
		spin_lock_init(&((pqueue)->lock));	\
	पूर्ण जबतक (0)

अटल अंतरभूत u32 end_of_queue_search(काष्ठा list_head *head,
		काष्ठा list_head *plist)
अणु
	वापस (head == plist);
पूर्ण

अटल अंतरभूत व्योम flush_संकेतs_thपढ़ो(व्योम)
अणु
	अगर (संकेत_pending(current))
		flush_संकेतs(current);
पूर्ण

#पूर्ण_अगर

