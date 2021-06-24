<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  net/dccp/qpolicy.c
 *
 *  Policy-based packet dequeueing पूर्णांकerface क्रम DCCP.
 *
 *  Copyright (c) 2008 Tomasz Grobelny <tomasz@grobelny.oswiecenia.net>
 */
#समावेश "dccp.h"

/*
 *	Simple Dequeueing Policy:
 *	If tx_qlen is dअगरferent from 0, enqueue up to tx_qlen elements.
 */
अटल व्योम qpolicy_simple_push(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
पूर्ण

अटल bool qpolicy_simple_full(काष्ठा sock *sk)
अणु
	वापस dccp_sk(sk)->dccps_tx_qlen &&
	       sk->sk_ग_लिखो_queue.qlen >= dccp_sk(sk)->dccps_tx_qlen;
पूर्ण

अटल काष्ठा sk_buff *qpolicy_simple_top(काष्ठा sock *sk)
अणु
	वापस skb_peek(&sk->sk_ग_लिखो_queue);
पूर्ण

/*
 *	Priority-based Dequeueing Policy:
 *	If tx_qlen is dअगरferent from 0 and the queue has reached its upper bound
 *	of tx_qlen elements, replace older packets lowest-priority-first.
 */
अटल काष्ठा sk_buff *qpolicy_prio_best_skb(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *best = शून्य;

	skb_queue_walk(&sk->sk_ग_लिखो_queue, skb)
		अगर (best == शून्य || skb->priority > best->priority)
			best = skb;
	वापस best;
पूर्ण

अटल काष्ठा sk_buff *qpolicy_prio_worst_skb(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *worst = शून्य;

	skb_queue_walk(&sk->sk_ग_लिखो_queue, skb)
		अगर (worst == शून्य || skb->priority < worst->priority)
			worst = skb;
	वापस worst;
पूर्ण

अटल bool qpolicy_prio_full(काष्ठा sock *sk)
अणु
	अगर (qpolicy_simple_full(sk))
		dccp_qpolicy_drop(sk, qpolicy_prio_worst_skb(sk));
	वापस false;
पूर्ण

/**
 * काष्ठा dccp_qpolicy_operations  -  TX Packet Dequeueing Interface
 * @push: add a new @skb to the ग_लिखो queue
 * @full: indicates that no more packets will be admitted
 * @top:  peeks at whatever the queueing policy defines as its `top'
 * @params: parameter passed to policy operation
 */
काष्ठा dccp_qpolicy_operations अणु
	व्योम		(*push)	(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	bool		(*full) (काष्ठा sock *sk);
	काष्ठा sk_buff*	(*top)  (काष्ठा sock *sk);
	__be32		params;
पूर्ण;

अटल काष्ठा dccp_qpolicy_operations qpol_table[DCCPQ_POLICY_MAX] = अणु
	[DCCPQ_POLICY_SIMPLE] = अणु
		.push   = qpolicy_simple_push,
		.full   = qpolicy_simple_full,
		.top    = qpolicy_simple_top,
		.params = 0,
	पूर्ण,
	[DCCPQ_POLICY_PRIO] = अणु
		.push   = qpolicy_simple_push,
		.full   = qpolicy_prio_full,
		.top    = qpolicy_prio_best_skb,
		.params = DCCP_SCM_PRIORITY,
	पूर्ण,
पूर्ण;

/*
 *	Externally visible पूर्णांकerface
 */
व्योम dccp_qpolicy_push(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	qpol_table[dccp_sk(sk)->dccps_qpolicy].push(sk, skb);
पूर्ण

bool dccp_qpolicy_full(काष्ठा sock *sk)
अणु
	वापस qpol_table[dccp_sk(sk)->dccps_qpolicy].full(sk);
पूर्ण

व्योम dccp_qpolicy_drop(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (skb != शून्य) अणु
		skb_unlink(skb, &sk->sk_ग_लिखो_queue);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

काष्ठा sk_buff *dccp_qpolicy_top(काष्ठा sock *sk)
अणु
	वापस qpol_table[dccp_sk(sk)->dccps_qpolicy].top(sk);
पूर्ण

काष्ठा sk_buff *dccp_qpolicy_pop(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb = dccp_qpolicy_top(sk);

	अगर (skb != शून्य) अणु
		/* Clear any skb fields that we used पूर्णांकernally */
		skb->priority = 0;
		skb_unlink(skb, &sk->sk_ग_लिखो_queue);
	पूर्ण
	वापस skb;
पूर्ण

bool dccp_qpolicy_param_ok(काष्ठा sock *sk, __be32 param)
अणु
	/* check अगर exactly one bit is set */
	अगर (!param || (param & (param - 1)))
		वापस false;
	वापस (qpol_table[dccp_sk(sk)->dccps_qpolicy].params & param) == param;
पूर्ण
