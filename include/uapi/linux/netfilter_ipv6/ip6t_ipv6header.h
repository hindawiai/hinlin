<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* ipv6header match - matches IPv6 packets based
on whether they contain certain headers */

/* Original idea: Brad Chapman 
 * Rewritten by: Andras Kis-Szabo <kisza@sch.bme.hu> */


#अगर_अघोषित __IPV6HEADER_H
#घोषणा __IPV6HEADER_H

#समावेश <linux/types.h>

काष्ठा ip6t_ipv6header_info अणु
	__u8 matchflags;
	__u8 invflags;
	__u8 modeflag;
पूर्ण;

#घोषणा MASK_HOPOPTS    128
#घोषणा MASK_DSTOPTS    64
#घोषणा MASK_ROUTING    32
#घोषणा MASK_FRAGMENT   16
#घोषणा MASK_AH         8
#घोषणा MASK_ESP        4
#घोषणा MASK_NONE       2
#घोषणा MASK_PROTO      1

#पूर्ण_अगर /* __IPV6HEADER_H */
