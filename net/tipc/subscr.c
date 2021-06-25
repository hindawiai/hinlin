<शैली गुरु>
/*
 * net/tipc/subscr.c: TIPC network topology service
 *
 * Copyright (c) 2000-2017, Ericsson AB
 * Copyright (c) 2005-2007, 2010-2013, Wind River Systems
 * Copyright (c) 2020-2021, Red Hat Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "core.h"
#समावेश "name_table.h"
#समावेश "subscr.h"

अटल व्योम tipc_sub_send_event(काष्ठा tipc_subscription *sub,
				काष्ठा खुलाation *p,
				u32 event)
अणु
	काष्ठा tipc_subscr *s = &sub->evt.s;
	काष्ठा tipc_event *evt = &sub->evt;

	अगर (sub->inactive)
		वापस;
	tipc_evt_ग_लिखो(evt, event, event);
	अगर (p) अणु
		tipc_evt_ग_लिखो(evt, found_lower, p->sr.lower);
		tipc_evt_ग_लिखो(evt, found_upper, p->sr.upper);
		tipc_evt_ग_लिखो(evt, port.ref, p->sk.ref);
		tipc_evt_ग_लिखो(evt, port.node, p->sk.node);
	पूर्ण अन्यथा अणु
		tipc_evt_ग_लिखो(evt, found_lower, s->seq.lower);
		tipc_evt_ग_लिखो(evt, found_upper, s->seq.upper);
		tipc_evt_ग_लिखो(evt, port.ref, 0);
		tipc_evt_ग_लिखो(evt, port.node, 0);
	पूर्ण
	tipc_topsrv_queue_evt(sub->net, sub->conid, event, evt);
पूर्ण

/**
 * tipc_sub_check_overlap - test क्रम subscription overlap with the given values
 * @subscribed: the service range subscribed क्रम
 * @found: the service range we are checning क्रम match
 *
 * Returns true अगर there is overlap, otherwise false.
 */
अटल bool tipc_sub_check_overlap(काष्ठा tipc_service_range *subscribed,
				   काष्ठा tipc_service_range *found)
अणु
	u32 found_lower = found->lower;
	u32 found_upper = found->upper;

	अगर (found_lower < subscribed->lower)
		found_lower = subscribed->lower;
	अगर (found_upper > subscribed->upper)
		found_upper = subscribed->upper;
	वापस found_lower <= found_upper;
पूर्ण

व्योम tipc_sub_report_overlap(काष्ठा tipc_subscription *sub,
			     काष्ठा खुलाation *p,
			     u32 event, bool must)
अणु
	काष्ठा tipc_service_range *sr = &sub->s.seq;
	u32 filter = sub->s.filter;

	अगर (!tipc_sub_check_overlap(sr, &p->sr))
		वापस;
	अगर (!must && !(filter & TIPC_SUB_PORTS))
		वापस;
	अगर (filter & TIPC_SUB_CLUSTER_SCOPE && p->scope == TIPC_NODE_SCOPE)
		वापस;
	अगर (filter & TIPC_SUB_NODE_SCOPE && p->scope != TIPC_NODE_SCOPE)
		वापस;
	spin_lock(&sub->lock);
	tipc_sub_send_event(sub, p, event);
	spin_unlock(&sub->lock);
पूर्ण

अटल व्योम tipc_sub_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा tipc_subscription *sub = from_समयr(sub, t, समयr);

	spin_lock(&sub->lock);
	tipc_sub_send_event(sub, शून्य, TIPC_SUBSCR_TIMEOUT);
	sub->inactive = true;
	spin_unlock(&sub->lock);
पूर्ण

अटल व्योम tipc_sub_kref_release(काष्ठा kref *kref)
अणु
	kमुक्त(container_of(kref, काष्ठा tipc_subscription, kref));
पूर्ण

व्योम tipc_sub_put(काष्ठा tipc_subscription *subscription)
अणु
	kref_put(&subscription->kref, tipc_sub_kref_release);
पूर्ण

व्योम tipc_sub_get(काष्ठा tipc_subscription *subscription)
अणु
	kref_get(&subscription->kref);
पूर्ण

काष्ठा tipc_subscription *tipc_sub_subscribe(काष्ठा net *net,
					     काष्ठा tipc_subscr *s,
					     पूर्णांक conid)
अणु
	u32 lower = tipc_sub_पढ़ो(s, seq.lower);
	u32 upper = tipc_sub_पढ़ो(s, seq.upper);
	u32 filter = tipc_sub_पढ़ो(s, filter);
	काष्ठा tipc_subscription *sub;
	u32 समयout;

	अगर ((filter & TIPC_SUB_PORTS && filter & TIPC_SUB_SERVICE) ||
	    lower > upper) अणु
		pr_warn("Subscription rejected, illegal request\n");
		वापस शून्य;
	पूर्ण
	sub = kदो_स्मृति(माप(*sub), GFP_ATOMIC);
	अगर (!sub) अणु
		pr_warn("Subscription rejected, no memory\n");
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&sub->service_list);
	INIT_LIST_HEAD(&sub->sub_list);
	sub->net = net;
	sub->conid = conid;
	sub->inactive = false;
	स_नकल(&sub->evt.s, s, माप(*s));
	sub->s.seq.type = tipc_sub_पढ़ो(s, seq.type);
	sub->s.seq.lower = lower;
	sub->s.seq.upper = upper;
	sub->s.filter = filter;
	sub->s.समयout = tipc_sub_पढ़ो(s, समयout);
	स_नकल(sub->s.usr_handle, s->usr_handle, 8);
	spin_lock_init(&sub->lock);
	kref_init(&sub->kref);
	अगर (!tipc_nametbl_subscribe(sub)) अणु
		kमुक्त(sub);
		वापस शून्य;
	पूर्ण
	समयr_setup(&sub->समयr, tipc_sub_समयout, 0);
	समयout = tipc_sub_पढ़ो(&sub->evt.s, समयout);
	अगर (समयout != TIPC_WAIT_FOREVER)
		mod_समयr(&sub->समयr, jअगरfies + msecs_to_jअगरfies(समयout));
	वापस sub;
पूर्ण

व्योम tipc_sub_unsubscribe(काष्ठा tipc_subscription *sub)
अणु
	tipc_nametbl_unsubscribe(sub);
	अगर (sub->evt.s.समयout != TIPC_WAIT_FOREVER)
		del_समयr_sync(&sub->समयr);
	list_del(&sub->sub_list);
	tipc_sub_put(sub);
पूर्ण
