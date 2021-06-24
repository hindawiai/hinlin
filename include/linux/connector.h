<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * 	connector.h
 * 
 * 2004-2005 Copyright (c) Evgeniy Polyakov <zbr@ioremap.net>
 * All rights reserved.
 */
#अगर_अघोषित __CONNECTOR_H
#घोषणा __CONNECTOR_H


#समावेश <linux/refcount.h>

#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>

#समावेश <net/sock.h>
#समावेश <uapi/linux/connector.h>

#घोषणा CN_CBQ_NAMELEN		32

काष्ठा cn_queue_dev अणु
	atomic_t refcnt;
	अचिन्हित अक्षर name[CN_CBQ_NAMELEN];

	काष्ठा list_head queue_list;
	spinlock_t queue_lock;

	काष्ठा sock *nls;
पूर्ण;

काष्ठा cn_callback_id अणु
	अचिन्हित अक्षर name[CN_CBQ_NAMELEN];
	काष्ठा cb_id id;
पूर्ण;

काष्ठा cn_callback_entry अणु
	काष्ठा list_head callback_entry;
	refcount_t refcnt;
	काष्ठा cn_queue_dev *pdev;

	काष्ठा cn_callback_id id;
	व्योम (*callback) (काष्ठा cn_msg *, काष्ठा netlink_skb_parms *);

	u32 seq, group;
पूर्ण;

काष्ठा cn_dev अणु
	काष्ठा cb_id id;

	u32 seq, groups;
	काष्ठा sock *nls;

	काष्ठा cn_queue_dev *cbdev;
पूर्ण;

/**
 * cn_add_callback() - Registers new callback with connector core.
 *
 * @id:		unique connector's user identअगरier.
 *		It must be रेजिस्टरed in connector.h क्रम legal
 *		in-kernel users.
 * @name:	connector's callback symbolic name.
 * @callback:	connector's callback.
 * 		parameters are %cn_msg and the sender's credentials
 */
पूर्णांक cn_add_callback(स्थिर काष्ठा cb_id *id, स्थिर अक्षर *name,
		    व्योम (*callback)(काष्ठा cn_msg *, काष्ठा netlink_skb_parms *));
/**
 * cn_del_callback() - Unरेजिस्टरs new callback with connector core.
 *
 * @id:		unique connector's user identअगरier.
 */
व्योम cn_del_callback(स्थिर काष्ठा cb_id *id);


/**
 * cn_netlink_send_mult - Sends message to the specअगरied groups.
 *
 * @msg: 	message header(with attached data).
 * @len:	Number of @msg to be sent.
 * @portid:	destination port.
 *		If non-zero the message will be sent to the given port,
 *		which should be set to the original sender.
 * @group:	destination group.
 * 		If @portid and @group is zero, then appropriate group will
 *		be searched through all रेजिस्टरed connector users, and
 *		message will be delivered to the group which was created
 *		क्रम user with the same ID as in @msg.
 *		If @group is not zero, then message will be delivered
 *		to the specअगरied group.
 * @gfp_mask:	GFP mask.
 *
 * It can be safely called from softirq context, but may silently
 * fail under strong memory pressure.
 *
 * If there are no listeners क्रम given group %-ESRCH can be वापसed.
 */
पूर्णांक cn_netlink_send_mult(काष्ठा cn_msg *msg, u16 len, u32 portid, u32 group, gfp_t gfp_mask);

/**
 * cn_netlink_send - Sends message to the specअगरied groups.
 *
 * @msg:	message header(with attached data).
 * @portid:	destination port.
 *		If non-zero the message will be sent to the given port,
 *		which should be set to the original sender.
 * @group:	destination group.
 * 		If @portid and @group is zero, then appropriate group will
 *		be searched through all रेजिस्टरed connector users, and
 *		message will be delivered to the group which was created
 *		क्रम user with the same ID as in @msg.
 *		If @group is not zero, then message will be delivered
 *		to the specअगरied group.
 * @gfp_mask:	GFP mask.
 *
 * It can be safely called from softirq context, but may silently
 * fail under strong memory pressure.
 *
 * If there are no listeners क्रम given group %-ESRCH can be वापसed.
 */
पूर्णांक cn_netlink_send(काष्ठा cn_msg *msg, u32 portid, u32 group, gfp_t gfp_mask);

पूर्णांक cn_queue_add_callback(काष्ठा cn_queue_dev *dev, स्थिर अक्षर *name,
			  स्थिर काष्ठा cb_id *id,
			  व्योम (*callback)(काष्ठा cn_msg *, काष्ठा netlink_skb_parms *));
व्योम cn_queue_del_callback(काष्ठा cn_queue_dev *dev, स्थिर काष्ठा cb_id *id);
व्योम cn_queue_release_callback(काष्ठा cn_callback_entry *);

काष्ठा cn_queue_dev *cn_queue_alloc_dev(स्थिर अक्षर *name, काष्ठा sock *);
व्योम cn_queue_मुक्त_dev(काष्ठा cn_queue_dev *dev);

पूर्णांक cn_cb_equal(स्थिर काष्ठा cb_id *, स्थिर काष्ठा cb_id *);

#पूर्ण_अगर				/* __CONNECTOR_H */
