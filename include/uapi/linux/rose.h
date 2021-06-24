<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * These are the खुला elements of the Linux kernel Rose implementation.
 * For kernel AX.25 see the file ax25.h. This file requires ax25.h क्रम the
 * definition of the ax25_address काष्ठाure.
 */

#अगर_अघोषित	ROSE_KERNEL_H
#घोषणा	ROSE_KERNEL_H

#समावेश <linux/socket.h>
#समावेश <linux/ax25.h>

#घोषणा ROSE_MTU	251

#घोषणा ROSE_MAX_DIGIS 6

#घोषणा	ROSE_DEFER	1
#घोषणा ROSE_T1		2
#घोषणा	ROSE_T2		3
#घोषणा	ROSE_T3		4
#घोषणा	ROSE_IDLE	5
#घोषणा	ROSE_QBITINCL	6
#घोषणा	ROSE_HOLDBACK	7

#घोषणा	SIOCRSGCAUSE		(SIOCPROTOPRIVATE+0)
#घोषणा	SIOCRSSCAUSE		(SIOCPROTOPRIVATE+1)
#घोषणा	SIOCRSL2CALL		(SIOCPROTOPRIVATE+2)
#घोषणा	SIOCRSSL2CALL		(SIOCPROTOPRIVATE+2)
#घोषणा	SIOCRSACCEPT		(SIOCPROTOPRIVATE+3)
#घोषणा	SIOCRSCLRRT		(SIOCPROTOPRIVATE+4)
#घोषणा	SIOCRSGL2CALL		(SIOCPROTOPRIVATE+5)
#घोषणा	SIOCRSGFACILITIES	(SIOCPROTOPRIVATE+6)

#घोषणा	ROSE_DTE_ORIGINATED	0x00
#घोषणा	ROSE_NUMBER_BUSY	0x01
#घोषणा	ROSE_INVALID_FACILITY	0x03
#घोषणा	ROSE_NETWORK_CONGESTION	0x05
#घोषणा	ROSE_OUT_OF_ORDER	0x09
#घोषणा	ROSE_ACCESS_BARRED	0x0B
#घोषणा	ROSE_NOT_OBTAINABLE	0x0D
#घोषणा	ROSE_REMOTE_PROCEDURE	0x11
#घोषणा	ROSE_LOCAL_PROCEDURE	0x13
#घोषणा	ROSE_SHIP_ABSENT	0x39

प्रकार काष्ठा अणु
	अक्षर		rose_addr[5];
पूर्ण rose_address;

काष्ठा sockaddr_rose अणु
	__kernel_sa_family_t srose_family;
	rose_address	srose_addr;
	ax25_address	srose_call;
	पूर्णांक		srose_ndigis;
	ax25_address	srose_digi;
पूर्ण;

काष्ठा full_sockaddr_rose अणु
	__kernel_sa_family_t srose_family;
	rose_address	srose_addr;
	ax25_address	srose_call;
	अचिन्हित पूर्णांक	srose_ndigis;
	ax25_address	srose_digis[ROSE_MAX_DIGIS];
पूर्ण;

काष्ठा rose_route_काष्ठा अणु
	rose_address	address;
	अचिन्हित लघु	mask;
	ax25_address	neighbour;
	अक्षर		device[16];
	अचिन्हित अक्षर	ndigis;
	ax25_address	digipeaters[AX25_MAX_DIGIS];
पूर्ण;

काष्ठा rose_cause_काष्ठा अणु
	अचिन्हित अक्षर	cause;
	अचिन्हित अक्षर	diagnostic;
पूर्ण;

काष्ठा rose_facilities_काष्ठा अणु
	rose_address	source_addr,   dest_addr;
	ax25_address	source_call,   dest_call;
	अचिन्हित अक्षर	source_ndigis, dest_ndigis;
	ax25_address	source_digis[ROSE_MAX_DIGIS];
	ax25_address	dest_digis[ROSE_MAX_DIGIS];
	अचिन्हित पूर्णांक	अक्रम;
	rose_address	fail_addr;
	ax25_address	fail_call;
पूर्ण;

#पूर्ण_अगर
