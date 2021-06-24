<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_blackhole.c	Black hole queue
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 *
 * Note: Quantum tunneling is not supported.
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_sched.h>

अटल पूर्णांक blackhole_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			     काष्ठा sk_buff **to_मुक्त)
अणु
	qdisc_drop(skb, sch, to_मुक्त);
	वापस NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
पूर्ण

अटल काष्ठा sk_buff *blackhole_dequeue(काष्ठा Qdisc *sch)
अणु
	वापस शून्य;
पूर्ण

अटल काष्ठा Qdisc_ops blackhole_qdisc_ops __पढ़ो_mostly = अणु
	.id		= "blackhole",
	.priv_size	= 0,
	.enqueue	= blackhole_enqueue,
	.dequeue	= blackhole_dequeue,
	.peek		= blackhole_dequeue,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init blackhole_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&blackhole_qdisc_ops);
पूर्ण
device_initcall(blackhole_init)
