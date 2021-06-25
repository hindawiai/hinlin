<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997, 1999, 2000, 2001 Ralf Baechle
 * Copyright (C) 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_SOCKET_H
#घोषणा _ASM_SOCKET_H

#समावेश <uapi/यंत्र/socket.h>


/** sock_type - Socket types
 *
 * Please notice that क्रम binary compat reasons MIPS has to
 * override the क्रमागत sock_type in include/linux/net.h, so
 * we define ARCH_HAS_SOCKET_TYPES here.
 *
 * @SOCK_DGRAM - datagram (conn.less) socket
 * @SOCK_STREAM - stream (connection) socket
 * @SOCK_RAW - raw socket
 * @SOCK_RDM - reliably-delivered message
 * @SOCK_SEQPACKET - sequential packet socket
 * @SOCK_PACKET - linux specअगरic way of getting packets at the dev level.
 *		  For writing rarp and other similar things on the user level.
 */
क्रमागत sock_type अणु
	SOCK_DGRAM	= 1,
	SOCK_STREAM	= 2,
	SOCK_RAW	= 3,
	SOCK_RDM	= 4,
	SOCK_SEQPACKET	= 5,
	SOCK_DCCP	= 6,
	SOCK_PACKET	= 10,
पूर्ण;

#घोषणा SOCK_MAX (SOCK_PACKET + 1)
/* Mask which covers at least up to SOCK_MASK-1.  The
 *  * reमुख्यing bits are used as flags. */
#घोषणा SOCK_TYPE_MASK 0xf

/* Flags क्रम socket, socketpair, paccept */
#घोषणा SOCK_CLOEXEC	O_CLOEXEC
#घोषणा SOCK_NONBLOCK	O_NONBLOCK

#घोषणा ARCH_HAS_SOCKET_TYPES 1

#पूर्ण_अगर /* _ASM_SOCKET_H */
