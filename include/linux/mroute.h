<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MROUTE_H
#घोषणा __LINUX_MROUTE_H

#समावेश <linux/in.h>
#समावेश <linux/pim.h>
#समावेश <net/fib_rules.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <uapi/linux/mroute.h>
#समावेश <linux/mroute_base.h>
#समावेश <linux/sockptr.h>

#अगर_घोषित CONFIG_IP_MROUTE
अटल अंतरभूत पूर्णांक ip_mroute_opt(पूर्णांक opt)
अणु
	वापस opt >= MRT_BASE && opt <= MRT_MAX;
पूर्ण

पूर्णांक ip_mroute_setsockopt(काष्ठा sock *, पूर्णांक, sockptr_t, अचिन्हित पूर्णांक);
पूर्णांक ip_mroute_माला_लोockopt(काष्ठा sock *, पूर्णांक, अक्षर __user *, पूर्णांक __user *);
पूर्णांक ipmr_ioctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *arg);
पूर्णांक ipmr_compat_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
पूर्णांक ip_mr_init(व्योम);
bool ipmr_rule_शेष(स्थिर काष्ठा fib_rule *rule);
#अन्यथा
अटल अंतरभूत पूर्णांक ip_mroute_setsockopt(काष्ठा sock *sock, पूर्णांक optname,
				       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	वापस -ENOPROTOOPT;
पूर्ण

अटल अंतरभूत पूर्णांक ip_mroute_माला_लोockopt(काष्ठा sock *sock, पूर्णांक optname,
				       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	वापस -ENOPROTOOPT;
पूर्ण

अटल अंतरभूत पूर्णांक ipmr_ioctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *arg)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

अटल अंतरभूत पूर्णांक ip_mr_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ip_mroute_opt(पूर्णांक opt)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool ipmr_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#घोषणा VIFF_STATIC 0x8000

काष्ठा mfc_cache_cmp_arg अणु
	__be32 mfc_mcastgrp;
	__be32 mfc_origin;
पूर्ण;

/**
 * काष्ठा mfc_cache - multicast routing entries
 * @_c: Common multicast routing inक्रमmation; has to be first [क्रम casting]
 * @mfc_mcastgrp: destination multicast group address
 * @mfc_origin: source address
 * @cmparg: used क्रम rhashtable comparisons
 */
काष्ठा mfc_cache अणु
	काष्ठा mr_mfc _c;
	जोड़ अणु
		काष्ठा अणु
			__be32 mfc_mcastgrp;
			__be32 mfc_origin;
		पूर्ण;
		काष्ठा mfc_cache_cmp_arg cmparg;
	पूर्ण;
पूर्ण;

काष्ठा rपंचांगsg;
पूर्णांक ipmr_get_route(काष्ठा net *net, काष्ठा sk_buff *skb,
		   __be32 saddr, __be32 daddr,
		   काष्ठा rपंचांगsg *rपंचांग, u32 portid);
#पूर्ण_अगर
