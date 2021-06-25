<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Equalizer Load-balancer क्रम serial network पूर्णांकerfaces.
 *
 * (c) Copyright 1995 Simon "Guru Aleph-Null" Janes
 * NCM: Network and Communications Management, Inc.
 *
 *
 *	This software may be used and distributed according to the terms
 *	of the GNU General Public License, incorporated herein by reference.
 * 
 * The author may be reached as simon@ncm.com, or C/O
 *    NCM
 *    Attn: Simon Janes
 *    6803 Whittier Ave
 *    McLean VA 22101
 *    Phone: 1-703-847-0040 ext 103
 */

#अगर_अघोषित _UAPI_LINUX_IF_EQL_H
#घोषणा _UAPI_LINUX_IF_EQL_H

#घोषणा EQL_DEFAULT_SLAVE_PRIORITY 28800
#घोषणा EQL_DEFAULT_MAX_SLAVES     4
#घोषणा EQL_DEFAULT_MTU            576
#घोषणा EQL_DEFAULT_RESCHED_IVAL   HZ

#घोषणा EQL_ENSLAVE     (SIOCDEVPRIVATE)
#घोषणा EQL_EMANCIPATE  (SIOCDEVPRIVATE + 1)

#घोषणा EQL_GETSLAVECFG (SIOCDEVPRIVATE + 2)
#घोषणा EQL_SETSLAVECFG (SIOCDEVPRIVATE + 3)

#घोषणा EQL_GETMASTRCFG (SIOCDEVPRIVATE + 4)
#घोषणा EQL_SETMASTRCFG (SIOCDEVPRIVATE + 5)


प्रकार काष्ठा master_config अणु
	अक्षर	master_name[16];
	पूर्णांक	max_slaves;
	पूर्णांक	min_slaves;
पूर्ण master_config_t;

प्रकार काष्ठा slave_config अणु
	अक्षर	slave_name[16];
	दीर्घ	priority;
पूर्ण slave_config_t;

प्रकार काष्ठा slaving_request अणु
	अक्षर	slave_name[16];
	दीर्घ	priority;
पूर्ण slaving_request_t;


#पूर्ण_अगर /* _UAPI_LINUX_IF_EQL_H */
