<शैली गुरु>
#अगर_अघोषित __NET_FIB_NOTIFIER_H
#घोषणा __NET_FIB_NOTIFIER_H

#समावेश <linux/types.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/net_namespace.h>

काष्ठा module;

काष्ठा fib_notअगरier_info अणु
	पूर्णांक family;
	काष्ठा netlink_ext_ack  *extack;
पूर्ण;

क्रमागत fib_event_type अणु
	FIB_EVENT_ENTRY_REPLACE,
	FIB_EVENT_ENTRY_APPEND,
	FIB_EVENT_ENTRY_ADD,
	FIB_EVENT_ENTRY_DEL,
	FIB_EVENT_RULE_ADD,
	FIB_EVENT_RULE_DEL,
	FIB_EVENT_NH_ADD,
	FIB_EVENT_NH_DEL,
	FIB_EVENT_VIF_ADD,
	FIB_EVENT_VIF_DEL,
पूर्ण;

काष्ठा fib_notअगरier_ops अणु
	पूर्णांक family;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक (*fib_seq_पढ़ो)(काष्ठा net *net);
	पूर्णांक (*fib_dump)(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			काष्ठा netlink_ext_ack *extack);
	काष्ठा module *owner;
	काष्ठा rcu_head rcu;
पूर्ण;

पूर्णांक call_fib_notअगरier(काष्ठा notअगरier_block *nb,
		      क्रमागत fib_event_type event_type,
		      काष्ठा fib_notअगरier_info *info);
पूर्णांक call_fib_notअगरiers(काष्ठा net *net, क्रमागत fib_event_type event_type,
		       काष्ठा fib_notअगरier_info *info);
पूर्णांक रेजिस्टर_fib_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			  व्योम (*cb)(काष्ठा notअगरier_block *nb),
			  काष्ठा netlink_ext_ack *extack);
पूर्णांक unरेजिस्टर_fib_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb);
काष्ठा fib_notअगरier_ops *
fib_notअगरier_ops_रेजिस्टर(स्थिर काष्ठा fib_notअगरier_ops *पंचांगpl, काष्ठा net *net);
व्योम fib_notअगरier_ops_unरेजिस्टर(काष्ठा fib_notअगरier_ops *ops);

#पूर्ण_अगर
