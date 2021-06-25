<शैली गुरु>
/*
 * Copyright (c) 2012 Mellanox Technologies. -  All rights reserved.
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
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>      /* For ARPHRD_xxx */
#समावेश <linux/module.h>
#समावेश <net/rtnetlink.h>
#समावेश "ipoib.h"

अटल स्थिर काष्ठा nla_policy ipoib_policy[IFLA_IPOIB_MAX + 1] = अणु
	[IFLA_IPOIB_PKEY]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPOIB_MODE]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPOIB_UMCAST]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक ipoib_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	u16 val;

	अगर (nla_put_u16(skb, IFLA_IPOIB_PKEY, priv->pkey))
		जाओ nla_put_failure;

	val = test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
	अगर (nla_put_u16(skb, IFLA_IPOIB_MODE, val))
		जाओ nla_put_failure;

	val = test_bit(IPOIB_FLAG_UMCAST, &priv->flags);
	अगर (nla_put_u16(skb, IFLA_IPOIB_UMCAST, val))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ipoib_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			    काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	u16 mode, umcast;
	पूर्णांक ret = 0;

	अगर (data[IFLA_IPOIB_MODE]) अणु
		mode  = nla_get_u16(data[IFLA_IPOIB_MODE]);
		अगर (mode == IPOIB_MODE_DATAGRAM)
			ret = ipoib_set_mode(dev, "datagram\n");
		अन्यथा अगर (mode == IPOIB_MODE_CONNECTED)
			ret = ipoib_set_mode(dev, "connected\n");
		अन्यथा
			ret = -EINVAL;

		अगर (ret < 0)
			जाओ out_err;
	पूर्ण

	अगर (data[IFLA_IPOIB_UMCAST]) अणु
		umcast = nla_get_u16(data[IFLA_IPOIB_UMCAST]);
		ipoib_set_umcast(dev, umcast);
	पूर्ण

out_err:
	वापस ret;
पूर्ण

अटल पूर्णांक ipoib_new_child_link(काष्ठा net *src_net, काष्ठा net_device *dev,
				काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *pdev;
	काष्ठा ipoib_dev_priv *ppriv;
	u16 child_pkey;
	पूर्णांक err;

	अगर (!tb[IFLA_LINK])
		वापस -EINVAL;

	pdev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	अगर (!pdev || pdev->type != ARPHRD_INFINIBAND)
		वापस -ENODEV;

	ppriv = ipoib_priv(pdev);

	अगर (test_bit(IPOIB_FLAG_SUBINTERFACE, &ppriv->flags)) अणु
		ipoib_warn(ppriv, "child creation disallowed for child devices\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!data || !data[IFLA_IPOIB_PKEY]) अणु
		ipoib_dbg(ppriv, "no pkey specified, using parent pkey\n");
		child_pkey  = ppriv->pkey;
	पूर्ण अन्यथा
		child_pkey  = nla_get_u16(data[IFLA_IPOIB_PKEY]);

	err = ipoib_पूर्णांकf_init(ppriv->ca, ppriv->port, dev->name, dev);
	अगर (err) अणु
		ipoib_warn(ppriv, "failed to initialize pkey device\n");
		वापस err;
	पूर्ण

	err = __ipoib_vlan_add(ppriv, ipoib_priv(dev),
			       child_pkey, IPOIB_RTNL_CHILD);
	अगर (err)
		वापस err;

	अगर (data) अणु
		err = ipoib_changelink(dev, tb, data, extack);
		अगर (err) अणु
			unरेजिस्टर_netdevice(dev);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipoib_del_child_link(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (!priv->parent)
		वापस;

	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल माप_प्रकार ipoib_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस nla_total_size(2) +	/* IFLA_IPOIB_PKEY   */
		nla_total_size(2) +	/* IFLA_IPOIB_MODE   */
		nla_total_size(2);	/* IFLA_IPOIB_UMCAST */
पूर्ण

अटल काष्ठा rtnl_link_ops ipoib_link_ops __पढ़ो_mostly = अणु
	.kind		= "ipoib",
	.netns_refund   = true,
	.maxtype	= IFLA_IPOIB_MAX,
	.policy		= ipoib_policy,
	.priv_size	= माप(काष्ठा ipoib_dev_priv),
	.setup		= ipoib_setup_common,
	.newlink	= ipoib_new_child_link,
	.dellink	= ipoib_del_child_link,
	.changelink	= ipoib_changelink,
	.get_size	= ipoib_get_size,
	.fill_info	= ipoib_fill_info,
पूर्ण;

काष्ठा rtnl_link_ops *ipoib_get_link_ops(व्योम)
अणु
	वापस &ipoib_link_ops;
पूर्ण

पूर्णांक __init ipoib_netlink_init(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&ipoib_link_ops);
पूर्ण

व्योम __निकास ipoib_netlink_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&ipoib_link_ops);
पूर्ण

MODULE_ALIAS_RTNL_LINK("ipoib");
