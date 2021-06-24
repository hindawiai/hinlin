<शैली गुरु>
/*
 * Copyright (c) 2006, 2017 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/in.h>
#समावेश <linux/ipv6.h>

#समावेश "rds.h"
#समावेश "loop.h"

अटल अक्षर * स्थिर rds_trans_modules[] = अणु
	[RDS_TRANS_IB] = "rds_rdma",
	[RDS_TRANS_GAP] = शून्य,
	[RDS_TRANS_TCP] = "rds_tcp",
पूर्ण;

अटल काष्ठा rds_transport *transports[RDS_TRANS_COUNT];
अटल DECLARE_RWSEM(rds_trans_sem);

व्योम rds_trans_रेजिस्टर(काष्ठा rds_transport *trans)
अणु
	BUG_ON(म_माप(trans->t_name) + 1 > TRANSNAMSIZ);

	करोwn_ग_लिखो(&rds_trans_sem);

	अगर (transports[trans->t_type])
		prपूर्णांकk(KERN_ERR "RDS Transport type %d already registered\n",
			trans->t_type);
	अन्यथा अणु
		transports[trans->t_type] = trans;
		prपूर्णांकk(KERN_INFO "Registered RDS/%s transport\n", trans->t_name);
	पूर्ण

	up_ग_लिखो(&rds_trans_sem);
पूर्ण
EXPORT_SYMBOL_GPL(rds_trans_रेजिस्टर);

व्योम rds_trans_unरेजिस्टर(काष्ठा rds_transport *trans)
अणु
	करोwn_ग_लिखो(&rds_trans_sem);

	transports[trans->t_type] = शून्य;
	prपूर्णांकk(KERN_INFO "Unregistered RDS/%s transport\n", trans->t_name);

	up_ग_लिखो(&rds_trans_sem);
पूर्ण
EXPORT_SYMBOL_GPL(rds_trans_unरेजिस्टर);

व्योम rds_trans_put(काष्ठा rds_transport *trans)
अणु
	अगर (trans)
		module_put(trans->t_owner);
पूर्ण

काष्ठा rds_transport *rds_trans_get_preferred(काष्ठा net *net,
					      स्थिर काष्ठा in6_addr *addr,
					      __u32 scope_id)
अणु
	काष्ठा rds_transport *ret = शून्य;
	काष्ठा rds_transport *trans;
	अचिन्हित पूर्णांक i;

	अगर (ipv6_addr_v4mapped(addr)) अणु
		अगर (*(u_पूर्णांक8_t *)&addr->s6_addr32[3] == IN_LOOPBACKNET)
			वापस &rds_loop_transport;
	पूर्ण अन्यथा अगर (ipv6_addr_loopback(addr)) अणु
		वापस &rds_loop_transport;
	पूर्ण

	करोwn_पढ़ो(&rds_trans_sem);
	क्रम (i = 0; i < RDS_TRANS_COUNT; i++) अणु
		trans = transports[i];

		अगर (trans && (trans->laddr_check(net, addr, scope_id) == 0) &&
		    (!trans->t_owner || try_module_get(trans->t_owner))) अणु
			ret = trans;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&rds_trans_sem);

	वापस ret;
पूर्ण

काष्ठा rds_transport *rds_trans_get(पूर्णांक t_type)
अणु
	काष्ठा rds_transport *ret = शून्य;
	काष्ठा rds_transport *trans;

	करोwn_पढ़ो(&rds_trans_sem);
	trans = transports[t_type];
	अगर (!trans) अणु
		up_पढ़ो(&rds_trans_sem);
		अगर (rds_trans_modules[t_type])
			request_module(rds_trans_modules[t_type]);
		करोwn_पढ़ो(&rds_trans_sem);
		trans = transports[t_type];
	पूर्ण
	अगर (trans && trans->t_type == t_type &&
	    (!trans->t_owner || try_module_get(trans->t_owner)))
		ret = trans;

	up_पढ़ो(&rds_trans_sem);

	वापस ret;
पूर्ण

/*
 * This वापसs the number of stats entries in the snapshot and only
 * copies them using the iter अगर there is enough space क्रम them.  The
 * caller passes in the global stats so that we can size and copy जबतक
 * holding the lock.
 */
अचिन्हित पूर्णांक rds_trans_stats_info_copy(काष्ठा rds_info_iterator *iter,
				       अचिन्हित पूर्णांक avail)

अणु
	काष्ठा rds_transport *trans;
	अचिन्हित पूर्णांक total = 0;
	अचिन्हित पूर्णांक part;
	पूर्णांक i;

	rds_info_iter_unmap(iter);
	करोwn_पढ़ो(&rds_trans_sem);

	क्रम (i = 0; i < RDS_TRANS_COUNT; i++) अणु
		trans = transports[i];
		अगर (!trans || !trans->stats_info_copy)
			जारी;

		part = trans->stats_info_copy(iter, avail);
		avail -= min(avail, part);
		total += part;
	पूर्ण

	up_पढ़ो(&rds_trans_sem);

	वापस total;
पूर्ण
