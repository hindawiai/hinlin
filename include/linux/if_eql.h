<शैली गुरु>
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
#अगर_अघोषित _LINUX_IF_EQL_H
#घोषणा _LINUX_IF_EQL_H


#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <uapi/linux/अगर_eql.h>

प्रकार काष्ठा slave अणु
	काष्ठा list_head	list;
	काष्ठा net_device	*dev;
	दीर्घ			priority;
	दीर्घ			priority_bps;
	दीर्घ			priority_Bps;
	दीर्घ			bytes_queued;
पूर्ण slave_t;

प्रकार काष्ठा slave_queue अणु
	spinlock_t		lock;
	काष्ठा list_head	all_slaves;
	पूर्णांक			num_slaves;
	काष्ठा net_device	*master_dev;
पूर्ण slave_queue_t;

प्रकार काष्ठा equalizer अणु
	slave_queue_t		queue;
	पूर्णांक			min_slaves;
	पूर्णांक			max_slaves;
	काष्ठा समयr_list	समयr;
पूर्ण equalizer_t;  

#पूर्ण_अगर /* _LINUX_EQL_H */
