<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * linux/can/core.h
 *
 * Prototypes and definitions क्रम CAN protocol modules using the PF_CAN core
 *
 * Authors: Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
 *          Urs Thuermann   <urs.thuermann@volkswagen.de>
 * Copyright (c) 2002-2017 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 */

#अगर_अघोषित _CAN_CORE_H
#घोषणा _CAN_CORE_H

#समावेश <linux/can.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>

#घोषणा DNAME(dev) ((dev) ? (dev)->name : "any")

/**
 * काष्ठा can_proto - CAN protocol काष्ठाure
 * @type:       type argument in socket() syscall, e.g. SOCK_DGRAM.
 * @protocol:   protocol number in socket() syscall.
 * @ops:        poपूर्णांकer to काष्ठा proto_ops क्रम sock->ops.
 * @prot:       poपूर्णांकer to काष्ठा proto काष्ठाure.
 */
काष्ठा can_proto अणु
	पूर्णांक type;
	पूर्णांक protocol;
	स्थिर काष्ठा proto_ops *ops;
	काष्ठा proto *prot;
पूर्ण;

/* required_size
 * macro to find the minimum size of a काष्ठा
 * that includes a requested member
 */
#घोषणा CAN_REQUIRED_SIZE(काष्ठा_type, member) \
	(दुरत्व(typeof(काष्ठा_type), member) + \
	 माप(((typeof(काष्ठा_type) *)(शून्य))->member))

/* function prototypes क्रम the CAN networklayer core (af_can.c) */

बाह्य पूर्णांक  can_proto_रेजिस्टर(स्थिर काष्ठा can_proto *cp);
बाह्य व्योम can_proto_unरेजिस्टर(स्थिर काष्ठा can_proto *cp);

पूर्णांक can_rx_रेजिस्टर(काष्ठा net *net, काष्ठा net_device *dev,
		    canid_t can_id, canid_t mask,
		    व्योम (*func)(काष्ठा sk_buff *, व्योम *),
		    व्योम *data, अक्षर *ident, काष्ठा sock *sk);

बाह्य व्योम can_rx_unरेजिस्टर(काष्ठा net *net, काष्ठा net_device *dev,
			      canid_t can_id, canid_t mask,
			      व्योम (*func)(काष्ठा sk_buff *, व्योम *),
			      व्योम *data);

बाह्य पूर्णांक can_send(काष्ठा sk_buff *skb, पूर्णांक loop);
व्योम can_sock_deकाष्ठा(काष्ठा sock *sk);

#पूर्ण_अगर /* !_CAN_CORE_H */
