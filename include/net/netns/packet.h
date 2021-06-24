<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Packet network namespace
 */
#अगर_अघोषित __NETNS_PACKET_H__
#घोषणा __NETNS_PACKET_H__

#समावेश <linux/rculist.h>
#समावेश <linux/mutex.h>

काष्ठा netns_packet अणु
	काष्ठा mutex		sklist_lock;
	काष्ठा hlist_head	sklist;
पूर्ण;

#पूर्ण_अगर /* __NETNS_PACKET_H__ */
