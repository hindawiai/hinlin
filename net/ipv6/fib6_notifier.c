<शैली गुरु>
#समावेश <linux/notअगरier.h>
#समावेश <linux/socket.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <net/netns/ipv6.h>
#समावेश <net/ip6_fib.h>

पूर्णांक call_fib6_notअगरier(काष्ठा notअगरier_block *nb,
		       क्रमागत fib_event_type event_type,
		       काष्ठा fib_notअगरier_info *info)
अणु
	info->family = AF_INET6;
	वापस call_fib_notअगरier(nb, event_type, info);
पूर्ण

पूर्णांक call_fib6_notअगरiers(काष्ठा net *net, क्रमागत fib_event_type event_type,
			काष्ठा fib_notअगरier_info *info)
अणु
	info->family = AF_INET6;
	वापस call_fib_notअगरiers(net, event_type, info);
पूर्ण

अटल अचिन्हित पूर्णांक fib6_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस fib6_tables_seq_पढ़ो(net) + fib6_rules_seq_पढ़ो(net);
पूर्ण

अटल पूर्णांक fib6_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = fib6_rules_dump(net, nb, extack);
	अगर (err)
		वापस err;

	वापस fib6_tables_dump(net, nb, extack);
पूर्ण

अटल स्थिर काष्ठा fib_notअगरier_ops fib6_notअगरier_ops_ढाँचा = अणु
	.family		= AF_INET6,
	.fib_seq_पढ़ो	= fib6_seq_पढ़ो,
	.fib_dump	= fib6_dump,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक __net_init fib6_notअगरier_init(काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_ops *ops;

	ops = fib_notअगरier_ops_रेजिस्टर(&fib6_notअगरier_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);
	net->ipv6.notअगरier_ops = ops;

	वापस 0;
पूर्ण

व्योम __net_निकास fib6_notअगरier_निकास(काष्ठा net *net)
अणु
	fib_notअगरier_ops_unरेजिस्टर(net->ipv6.notअगरier_ops);
पूर्ण
