<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_ATALK_H__
#घोषणा _UAPI__LINUX_ATALK_H__

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/socket.h>

/*
 * AppleTalk networking काष्ठाures
 *
 * The following are directly referenced from the University Of Michigan
 * netatalk क्रम compatibility reasons.
 */
#घोषणा ATPORT_FIRST	1
#घोषणा ATPORT_RESERVED	128
#घोषणा ATPORT_LAST	254		/* 254 is only legal on localtalk */ 
#घोषणा ATADDR_ANYNET	(__u16)0
#घोषणा ATADDR_ANYNODE	(__u8)0
#घोषणा ATADDR_ANYPORT  (__u8)0
#घोषणा ATADDR_BCAST	(__u8)255
#घोषणा DDP_MAXSZ	587
#घोषणा DDP_MAXHOPS     15		/* 4 bits of hop counter */

#घोषणा SIOCATALKDIFADDR       (SIOCPROTOPRIVATE + 0)

काष्ठा atalk_addr अणु
	__be16	s_net;
	__u8	s_node;
पूर्ण;

काष्ठा sockaddr_at अणु
	__kernel_sa_family_t sat_family;
	__u8		  sat_port;
	काष्ठा atalk_addr sat_addr;
	अक्षर		  sat_zero[8];
पूर्ण;

काष्ठा atalk_netrange अणु
	__u8	nr_phase;
	__be16	nr_firstnet;
	__be16	nr_lastnet;
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_ATALK_H__ */
