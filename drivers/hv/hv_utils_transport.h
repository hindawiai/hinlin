<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Kernel/userspace transport असलtraction क्रम Hyper-V util driver.
 *
 * Copyright (C) 2015, Vitaly Kuznetsov <vkuznets@redhat.com>
 */

#अगर_अघोषित _HV_UTILS_TRANSPORT_H
#घोषणा _HV_UTILS_TRANSPORT_H

#समावेश <linux/connector.h>
#समावेश <linux/miscdevice.h>

क्रमागत hvutil_transport_mode अणु
	HVUTIL_TRANSPORT_INIT = 0,
	HVUTIL_TRANSPORT_NETLINK,
	HVUTIL_TRANSPORT_CHARDEV,
	HVUTIL_TRANSPORT_DESTROY,
पूर्ण;

काष्ठा hvutil_transport अणु
	पूर्णांक mode;                           /* hvutil_transport_mode */
	काष्ठा file_operations fops;        /* file operations */
	काष्ठा miscdevice mdev;             /* misc device */
	काष्ठा cb_id cn_id;                 /* CN_*_IDX/CN_*_VAL */
	काष्ठा list_head list;              /* hvt_list */
	पूर्णांक (*on_msg)(व्योम *, पूर्णांक);         /* callback on new user message */
	व्योम (*on_reset)(व्योम);             /* callback when userspace drops */
	व्योम (*on_पढ़ो)(व्योम);              /* callback on message पढ़ो */
	u8 *ouपंचांगsg;                         /* message to the userspace */
	पूर्णांक ouपंचांगsg_len;                     /* its length */
	रुको_queue_head_t ouपंचांगsg_q;         /* poll/पढ़ो रुको queue */
	काष्ठा mutex lock;                  /* protects काष्ठा members */
	काष्ठा completion release;          /* synchronize with fd release */
पूर्ण;

काष्ठा hvutil_transport *hvutil_transport_init(स्थिर अक्षर *name,
					       u32 cn_idx, u32 cn_val,
					       पूर्णांक (*on_msg)(व्योम *, पूर्णांक),
					       व्योम (*on_reset)(व्योम));
पूर्णांक hvutil_transport_send(काष्ठा hvutil_transport *hvt, व्योम *msg, पूर्णांक len,
			  व्योम (*on_पढ़ो_cb)(व्योम));
व्योम hvutil_transport_destroy(काष्ठा hvutil_transport *hvt);

#पूर्ण_अगर /* _HV_UTILS_TRANSPORT_H */
