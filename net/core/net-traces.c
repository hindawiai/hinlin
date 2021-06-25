<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * consolidates trace poपूर्णांक definitions
 *
 * Copyright (C) 2009 Neil Horman <nhorman@tuxdriver.com>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/netlink.h>
#समावेश <linux/net_dropmon.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/bitops.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/skb.h>
#समावेश <trace/events/net.h>
#समावेश <trace/events/napi.h>
#समावेश <trace/events/sock.h>
#समावेश <trace/events/udp.h>
#समावेश <trace/events/tcp.h>
#समावेश <trace/events/fib.h>
#समावेश <trace/events/qdisc.h>
#अगर IS_ENABLED(CONFIG_BRIDGE)
#समावेश <trace/events/bridge.h>
EXPORT_TRACEPOINT_SYMBOL_GPL(br_fdb_add);
EXPORT_TRACEPOINT_SYMBOL_GPL(br_fdb_बाह्यal_learn_add);
EXPORT_TRACEPOINT_SYMBOL_GPL(fdb_delete);
EXPORT_TRACEPOINT_SYMBOL_GPL(br_fdb_update);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_PAGE_POOL)
#समावेश <trace/events/page_pool.h>
#पूर्ण_अगर

#समावेश <trace/events/neigh.h>
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_update);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_update_करोne);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_समयr_handler);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_event_send_करोne);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_event_send_dead);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_cleanup_and_release);

EXPORT_TRACEPOINT_SYMBOL_GPL(kमुक्त_skb);

EXPORT_TRACEPOINT_SYMBOL_GPL(napi_poll);

EXPORT_TRACEPOINT_SYMBOL_GPL(tcp_send_reset);
