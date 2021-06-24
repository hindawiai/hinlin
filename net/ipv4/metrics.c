<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/types.h>
#समावेश <net/ip.h>
#समावेश <net/net_namespace.h>
#समावेश <net/tcp.h>

अटल पूर्णांक ip_metrics_convert(काष्ठा net *net, काष्ठा nlattr *fc_mx,
			      पूर्णांक fc_mx_len, u32 *metrics,
			      काष्ठा netlink_ext_ack *extack)
अणु
	bool ecn_ca = false;
	काष्ठा nlattr *nla;
	पूर्णांक reमुख्यing;

	अगर (!fc_mx)
		वापस 0;

	nla_क्रम_each_attr(nla, fc_mx, fc_mx_len, reमुख्यing) अणु
		पूर्णांक type = nla_type(nla);
		u32 val;

		अगर (!type)
			जारी;
		अगर (type > RTAX_MAX) अणु
			NL_SET_ERR_MSG(extack, "Invalid metric type");
			वापस -EINVAL;
		पूर्ण

		अगर (type == RTAX_CC_ALGO) अणु
			अक्षर पंचांगp[TCP_CA_NAME_MAX];

			nla_strscpy(पंचांगp, nla, माप(पंचांगp));
			val = tcp_ca_get_key_by_name(net, पंचांगp, &ecn_ca);
			अगर (val == TCP_CA_UNSPEC) अणु
				NL_SET_ERR_MSG(extack, "Unknown tcp congestion algorithm");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (nla_len(nla) != माप(u32)) अणु
				NL_SET_ERR_MSG_ATTR(extack, nla,
						    "Invalid attribute in metrics");
				वापस -EINVAL;
			पूर्ण
			val = nla_get_u32(nla);
		पूर्ण
		अगर (type == RTAX_ADVMSS && val > 65535 - 40)
			val = 65535 - 40;
		अगर (type == RTAX_MTU && val > 65535 - 15)
			val = 65535 - 15;
		अगर (type == RTAX_HOPLIMIT && val > 255)
			val = 255;
		अगर (type == RTAX_FEATURES && (val & ~RTAX_FEATURE_MASK)) अणु
			NL_SET_ERR_MSG(extack, "Unknown flag set in feature mask in metrics attribute");
			वापस -EINVAL;
		पूर्ण
		metrics[type - 1] = val;
	पूर्ण

	अगर (ecn_ca)
		metrics[RTAX_FEATURES - 1] |= DST_FEATURE_ECN_CA;

	वापस 0;
पूर्ण

काष्ठा dst_metrics *ip_fib_metrics_init(काष्ठा net *net, काष्ठा nlattr *fc_mx,
					पूर्णांक fc_mx_len,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dst_metrics *fib_metrics;
	पूर्णांक err;

	अगर (!fc_mx)
		वापस (काष्ठा dst_metrics *)&dst_शेष_metrics;

	fib_metrics = kzalloc(माप(*fib_metrics), GFP_KERNEL);
	अगर (unlikely(!fib_metrics))
		वापस ERR_PTR(-ENOMEM);

	err = ip_metrics_convert(net, fc_mx, fc_mx_len, fib_metrics->metrics,
				 extack);
	अगर (!err) अणु
		refcount_set(&fib_metrics->refcnt, 1);
	पूर्ण अन्यथा अणु
		kमुक्त(fib_metrics);
		fib_metrics = ERR_PTR(err);
	पूर्ण

	वापस fib_metrics;
पूर्ण
EXPORT_SYMBOL_GPL(ip_fib_metrics_init);
