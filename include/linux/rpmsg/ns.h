<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_RPMSG_NS_H
#घोषणा _LINUX_RPMSG_NS_H

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/rpmsg/byteorder.h>
#समावेश <linux/types.h>

/**
 * काष्ठा rpmsg_ns_msg - dynamic name service announcement message
 * @name: name of remote service that is published
 * @addr: address of remote service that is published
 * @flags: indicates whether service is created or destroyed
 *
 * This message is sent across to publish a new service, or announce
 * about its removal. When we receive these messages, an appropriate
 * rpmsg channel (i.e device) is created/destroyed. In turn, the ->probe()
 * or ->हटाओ() handler of the appropriate rpmsg driver will be invoked
 * (अगर/as-soon-as one is रेजिस्टरed).
 */
काष्ठा rpmsg_ns_msg अणु
	अक्षर name[RPMSG_NAME_SIZE];
	__rpmsg32 addr;
	__rpmsg32 flags;
पूर्ण __packed;

/**
 * क्रमागत rpmsg_ns_flags - dynamic name service announcement flags
 *
 * @RPMSG_NS_CREATE: a new remote service was just created
 * @RPMSG_NS_DESTROY: a known remote service was just destroyed
 */
क्रमागत rpmsg_ns_flags अणु
	RPMSG_NS_CREATE		= 0,
	RPMSG_NS_DESTROY	= 1,
पूर्ण;

/* Address 53 is reserved क्रम advertising remote services */
#घोषणा RPMSG_NS_ADDR			(53)

पूर्णांक rpmsg_ns_रेजिस्टर_device(काष्ठा rpmsg_device *rpdev);

#पूर्ण_अगर
