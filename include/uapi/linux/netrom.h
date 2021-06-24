<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * These are the खुला elements of the Linux kernel NET/ROM implementation.
 * For kernel AX.25 see the file ax25.h. This file requires ax25.h क्रम the
 * definition of the ax25_address काष्ठाure.
 */

#अगर_अघोषित	NETROM_KERNEL_H
#घोषणा	NETROM_KERNEL_H

#समावेश <linux/ax25.h>

#घोषणा NETROM_MTU	236

#घोषणा NETROM_T1	1
#घोषणा NETROM_T2	2
#घोषणा NETROM_N2	3
#घोषणा	NETROM_T4	6
#घोषणा	NETROM_IDLE	7

#घोषणा	SIOCNRDECOBS		(SIOCPROTOPRIVATE+2)

काष्ठा nr_route_काष्ठा अणु
#घोषणा	NETROM_NEIGH	0
#घोषणा	NETROM_NODE	1
	पूर्णांक		type;
	ax25_address	callsign;
	अक्षर		device[16];
	अचिन्हित पूर्णांक	quality;
	अक्षर		mnemonic[7];
	ax25_address	neighbour;
	अचिन्हित पूर्णांक	obs_count;
	अचिन्हित पूर्णांक	ndigis;
	ax25_address	digipeaters[AX25_MAX_DIGIS];
पूर्ण;

#पूर्ण_अगर
