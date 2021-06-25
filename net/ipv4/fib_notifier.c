<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/rtnetlink.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/socket.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <net/netns/ipv4.h>
#समावेश <net/ip_fib.h>

पूर्णांक call_fib4_notअगरier(काष्ठा notअगरier_block *nb,
		       क्रमागत fib_event_type event_type,
		       काष्ठा fib_notअगरier_info *info)
अणु
	info->family = AF_INET;
	वापस call_fib_notअगरier(nb, event_type, info);
पूर्ण

पूर्णांक call_fib4_notअगरiers(काष्ठा net *net, क्रमागत fib_event_type event_type,
			काष्ठा fib_notअगरier_info *info)
अणु
	ASSERT_RTNL();

	info->family = AF_INET;
	net->ipv4.fib_seq++;
	वापस call_fib_notअगरiers(net, event_type, info);
पूर्ण

अटल अचिन्हित पूर्णांक fib4_seq_पढ़ो(काष्ठा net *net)
अणु
	ASSERT_RTNL();

	वापस net->ipv4.fib_seq + fib4_rules_seq_पढ़ो(net);
पूर्ण

अटल पूर्णांक fib4_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = fib4_rules_dump(net, nb, extack);
	अगर (err)
		वापस err;

	वापस fib_notअगरy(net, nb, extack);
पूर्ण

अटल स्थिर काष्ठा fib_notअगरier_ops fib4_notअगरier_ops_ढाँचा = अणु
	.family		= AF_INET,
	.fib_seq_पढ़ो	= fib4_seq_पढ़ो,
	.fib_dump	= fib4_dump,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक __net_init fib4_notअगरier_init(काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_ops *ops;

	net->ipv4.fib_seq = 0;

	ops = fib_notअगरier_ops_रेजिस्टर(&fib4_notअगरier_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);
	net->ipv4.notअगरier_ops = ops;

	वापस 0;
पूर्ण

व्योम __net_निकास fib4_notअगरier_निकास(काष्ठा net *net)
अणु
	fib_notअगरier_ops_unरेजिस्टर(net->ipv4.notअगरier_ops);
पूर्ण
