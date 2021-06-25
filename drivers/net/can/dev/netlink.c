<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2005 Marc Kleine-Budde, Pengutronix
 * Copyright (C) 2006 Andrey Volkov, Varma Electronics
 * Copyright (C) 2008-2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#समावेश <linux/can/dev.h>
#समावेश <net/rtnetlink.h>

अटल स्थिर काष्ठा nla_policy can_policy[IFLA_CAN_MAX + 1] = अणु
	[IFLA_CAN_STATE] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_CAN_CTRLMODE] = अणु .len = माप(काष्ठा can_ctrlmode) पूर्ण,
	[IFLA_CAN_RESTART_MS] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_CAN_RESTART] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_CAN_BITTIMING] = अणु .len = माप(काष्ठा can_bittiming) पूर्ण,
	[IFLA_CAN_BITTIMING_CONST] = अणु .len = माप(काष्ठा can_bittiming_स्थिर) पूर्ण,
	[IFLA_CAN_CLOCK] = अणु .len = माप(काष्ठा can_घड़ी) पूर्ण,
	[IFLA_CAN_BERR_COUNTER] = अणु .len = माप(काष्ठा can_berr_counter) पूर्ण,
	[IFLA_CAN_DATA_BITTIMING] = अणु .len = माप(काष्ठा can_bittiming) पूर्ण,
	[IFLA_CAN_DATA_BITTIMING_CONST]	= अणु .len = माप(काष्ठा can_bittiming_स्थिर) पूर्ण,
	[IFLA_CAN_TERMINATION] = अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक can_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	bool is_can_fd = false;

	/* Make sure that valid CAN FD configurations always consist of
	 * - nominal/arbitration bittiming
	 * - data bittiming
	 * - control mode with CAN_CTRLMODE_FD set
	 */

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_CAN_CTRLMODE]) अणु
		काष्ठा can_ctrlmode *cm = nla_data(data[IFLA_CAN_CTRLMODE]);

		is_can_fd = cm->flags & cm->mask & CAN_CTRLMODE_FD;
	पूर्ण

	अगर (is_can_fd) अणु
		अगर (!data[IFLA_CAN_BITTIMING] || !data[IFLA_CAN_DATA_BITTIMING])
			वापस -EOPNOTSUPP;
	पूर्ण

	अगर (data[IFLA_CAN_DATA_BITTIMING]) अणु
		अगर (!is_can_fd || !data[IFLA_CAN_BITTIMING])
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक can_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			  काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	/* We need synchronization with dev->stop() */
	ASSERT_RTNL();

	अगर (data[IFLA_CAN_BITTIMING]) अणु
		काष्ठा can_bittiming bt;

		/* Do not allow changing bittiming जबतक running */
		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		/* Calculate bittiming parameters based on
		 * bittiming_स्थिर अगर set, otherwise pass bitrate
		 * directly via करो_set_bitrate(). Bail out अगर neither
		 * is given.
		 */
		अगर (!priv->bittiming_स्थिर && !priv->करो_set_bittiming)
			वापस -EOPNOTSUPP;

		स_नकल(&bt, nla_data(data[IFLA_CAN_BITTIMING]), माप(bt));
		err = can_get_bittiming(dev, &bt,
					priv->bittiming_स्थिर,
					priv->bitrate_स्थिर,
					priv->bitrate_स्थिर_cnt);
		अगर (err)
			वापस err;

		अगर (priv->bitrate_max && bt.bitrate > priv->bitrate_max) अणु
			netdev_err(dev, "arbitration bitrate surpasses transceiver capabilities of %d bps\n",
				   priv->bitrate_max);
			वापस -EINVAL;
		पूर्ण

		स_नकल(&priv->bittiming, &bt, माप(bt));

		अगर (priv->करो_set_bittiming) अणु
			/* Finally, set the bit-timing रेजिस्टरs */
			err = priv->करो_set_bittiming(dev);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_CAN_CTRLMODE]) अणु
		काष्ठा can_ctrlmode *cm;
		u32 ctrlअटल;
		u32 maskedflags;

		/* Do not allow changing controller mode जबतक running */
		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;
		cm = nla_data(data[IFLA_CAN_CTRLMODE]);
		ctrlअटल = priv->ctrlmode_अटल;
		maskedflags = cm->flags & cm->mask;

		/* check whether provided bits are allowed to be passed */
		अगर (cm->mask & ~(priv->ctrlmode_supported | ctrlअटल))
			वापस -EOPNOTSUPP;

		/* करो not check क्रम अटल fd-non-iso अगर 'fd' is disabled */
		अगर (!(maskedflags & CAN_CTRLMODE_FD))
			ctrlअटल &= ~CAN_CTRLMODE_FD_NON_ISO;

		/* make sure अटल options are provided by configuration */
		अगर ((maskedflags & ctrlअटल) != ctrlअटल)
			वापस -EOPNOTSUPP;

		/* clear bits to be modअगरied and copy the flag values */
		priv->ctrlmode &= ~cm->mask;
		priv->ctrlmode |= maskedflags;

		/* CAN_CTRLMODE_FD can only be set when driver supports FD */
		अगर (priv->ctrlmode & CAN_CTRLMODE_FD)
			dev->mtu = CANFD_MTU;
		अन्यथा
			dev->mtu = CAN_MTU;
	पूर्ण

	अगर (data[IFLA_CAN_RESTART_MS]) अणु
		/* Do not allow changing restart delay जबतक running */
		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;
		priv->restart_ms = nla_get_u32(data[IFLA_CAN_RESTART_MS]);
	पूर्ण

	अगर (data[IFLA_CAN_RESTART]) अणु
		/* Do not allow a restart जबतक not running */
		अगर (!(dev->flags & IFF_UP))
			वापस -EINVAL;
		err = can_restart_now(dev);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_CAN_DATA_BITTIMING]) अणु
		काष्ठा can_bittiming dbt;

		/* Do not allow changing bittiming जबतक running */
		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		/* Calculate bittiming parameters based on
		 * data_bittiming_स्थिर अगर set, otherwise pass bitrate
		 * directly via करो_set_bitrate(). Bail out अगर neither
		 * is given.
		 */
		अगर (!priv->data_bittiming_स्थिर && !priv->करो_set_data_bittiming)
			वापस -EOPNOTSUPP;

		स_नकल(&dbt, nla_data(data[IFLA_CAN_DATA_BITTIMING]),
		       माप(dbt));
		err = can_get_bittiming(dev, &dbt,
					priv->data_bittiming_स्थिर,
					priv->data_bitrate_स्थिर,
					priv->data_bitrate_स्थिर_cnt);
		अगर (err)
			वापस err;

		अगर (priv->bitrate_max && dbt.bitrate > priv->bitrate_max) अणु
			netdev_err(dev, "canfd data bitrate surpasses transceiver capabilities of %d bps\n",
				   priv->bitrate_max);
			वापस -EINVAL;
		पूर्ण

		स_नकल(&priv->data_bittiming, &dbt, माप(dbt));

		can_calc_tdco(dev);

		अगर (priv->करो_set_data_bittiming) अणु
			/* Finally, set the bit-timing रेजिस्टरs */
			err = priv->करो_set_data_bittiming(dev);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_CAN_TERMINATION]) अणु
		स्थिर u16 termval = nla_get_u16(data[IFLA_CAN_TERMINATION]);
		स्थिर अचिन्हित पूर्णांक num_term = priv->termination_स्थिर_cnt;
		अचिन्हित पूर्णांक i;

		अगर (!priv->करो_set_termination)
			वापस -EOPNOTSUPP;

		/* check whether given value is supported by the पूर्णांकerface */
		क्रम (i = 0; i < num_term; i++) अणु
			अगर (termval == priv->termination_स्थिर[i])
				अवरोध;
		पूर्ण
		अगर (i >= num_term)
			वापस -EINVAL;

		/* Finally, set the termination value */
		err = priv->करो_set_termination(dev, termval);
		अगर (err)
			वापस err;

		priv->termination = termval;
	पूर्ण

	वापस 0;
पूर्ण

अटल माप_प्रकार can_get_size(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	माप_प्रकार size = 0;

	अगर (priv->bittiming.bitrate)				/* IFLA_CAN_BITTIMING */
		size += nla_total_size(माप(काष्ठा can_bittiming));
	अगर (priv->bittiming_स्थिर)				/* IFLA_CAN_BITTIMING_CONST */
		size += nla_total_size(माप(काष्ठा can_bittiming_स्थिर));
	size += nla_total_size(माप(काष्ठा can_घड़ी));	/* IFLA_CAN_CLOCK */
	size += nla_total_size(माप(u32));			/* IFLA_CAN_STATE */
	size += nla_total_size(माप(काष्ठा can_ctrlmode));	/* IFLA_CAN_CTRLMODE */
	size += nla_total_size(माप(u32));			/* IFLA_CAN_RESTART_MS */
	अगर (priv->करो_get_berr_counter)				/* IFLA_CAN_BERR_COUNTER */
		size += nla_total_size(माप(काष्ठा can_berr_counter));
	अगर (priv->data_bittiming.bitrate)			/* IFLA_CAN_DATA_BITTIMING */
		size += nla_total_size(माप(काष्ठा can_bittiming));
	अगर (priv->data_bittiming_स्थिर)				/* IFLA_CAN_DATA_BITTIMING_CONST */
		size += nla_total_size(माप(काष्ठा can_bittiming_स्थिर));
	अगर (priv->termination_स्थिर) अणु
		size += nla_total_size(माप(priv->termination));		/* IFLA_CAN_TERMINATION */
		size += nla_total_size(माप(*priv->termination_स्थिर) *	/* IFLA_CAN_TERMINATION_CONST */
				       priv->termination_स्थिर_cnt);
	पूर्ण
	अगर (priv->bitrate_स्थिर)				/* IFLA_CAN_BITRATE_CONST */
		size += nla_total_size(माप(*priv->bitrate_स्थिर) *
				       priv->bitrate_स्थिर_cnt);
	अगर (priv->data_bitrate_स्थिर)				/* IFLA_CAN_DATA_BITRATE_CONST */
		size += nla_total_size(माप(*priv->data_bitrate_स्थिर) *
				       priv->data_bitrate_स्थिर_cnt);
	size += माप(priv->bitrate_max);			/* IFLA_CAN_BITRATE_MAX */

	वापस size;
पूर्ण

अटल पूर्णांक can_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	काष्ठा can_ctrlmode cm = अणु.flags = priv->ctrlmodeपूर्ण;
	काष्ठा can_berr_counter bec = अणु पूर्ण;
	क्रमागत can_state state = priv->state;

	अगर (priv->करो_get_state)
		priv->करो_get_state(dev, &state);

	अगर ((priv->bittiming.bitrate &&
	     nla_put(skb, IFLA_CAN_BITTIMING,
		     माप(priv->bittiming), &priv->bittiming)) ||

	    (priv->bittiming_स्थिर &&
	     nla_put(skb, IFLA_CAN_BITTIMING_CONST,
		     माप(*priv->bittiming_स्थिर), priv->bittiming_स्थिर)) ||

	    nla_put(skb, IFLA_CAN_CLOCK, माप(priv->घड़ी), &priv->घड़ी) ||
	    nla_put_u32(skb, IFLA_CAN_STATE, state) ||
	    nla_put(skb, IFLA_CAN_CTRLMODE, माप(cm), &cm) ||
	    nla_put_u32(skb, IFLA_CAN_RESTART_MS, priv->restart_ms) ||

	    (priv->करो_get_berr_counter &&
	     !priv->करो_get_berr_counter(dev, &bec) &&
	     nla_put(skb, IFLA_CAN_BERR_COUNTER, माप(bec), &bec)) ||

	    (priv->data_bittiming.bitrate &&
	     nla_put(skb, IFLA_CAN_DATA_BITTIMING,
		     माप(priv->data_bittiming), &priv->data_bittiming)) ||

	    (priv->data_bittiming_स्थिर &&
	     nla_put(skb, IFLA_CAN_DATA_BITTIMING_CONST,
		     माप(*priv->data_bittiming_स्थिर),
		     priv->data_bittiming_स्थिर)) ||

	    (priv->termination_स्थिर &&
	     (nla_put_u16(skb, IFLA_CAN_TERMINATION, priv->termination) ||
	      nla_put(skb, IFLA_CAN_TERMINATION_CONST,
		      माप(*priv->termination_स्थिर) *
		      priv->termination_स्थिर_cnt,
		      priv->termination_स्थिर))) ||

	    (priv->bitrate_स्थिर &&
	     nla_put(skb, IFLA_CAN_BITRATE_CONST,
		     माप(*priv->bitrate_स्थिर) *
		     priv->bitrate_स्थिर_cnt,
		     priv->bitrate_स्थिर)) ||

	    (priv->data_bitrate_स्थिर &&
	     nla_put(skb, IFLA_CAN_DATA_BITRATE_CONST,
		     माप(*priv->data_bitrate_स्थिर) *
		     priv->data_bitrate_स्थिर_cnt,
		     priv->data_bitrate_स्थिर)) ||

	    (nla_put(skb, IFLA_CAN_BITRATE_MAX,
		     माप(priv->bitrate_max),
		     &priv->bitrate_max))
	    )

		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल माप_प्रकार can_get_xstats_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस माप(काष्ठा can_device_stats);
पूर्ण

अटल पूर्णांक can_fill_xstats(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	अगर (nla_put(skb, IFLA_INFO_XSTATS,
		    माप(priv->can_stats), &priv->can_stats))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक can_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
		       काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		       काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम can_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
पूर्ण

काष्ठा rtnl_link_ops can_link_ops __पढ़ो_mostly = अणु
	.kind		= "can",
	.netns_refund	= true,
	.maxtype	= IFLA_CAN_MAX,
	.policy		= can_policy,
	.setup		= can_setup,
	.validate	= can_validate,
	.newlink	= can_newlink,
	.changelink	= can_changelink,
	.dellink	= can_dellink,
	.get_size	= can_get_size,
	.fill_info	= can_fill_info,
	.get_xstats_size = can_get_xstats_size,
	.fill_xstats	= can_fill_xstats,
पूर्ण;

पूर्णांक can_netlink_रेजिस्टर(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&can_link_ops);
पूर्ण

व्योम can_netlink_unरेजिस्टर(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&can_link_ops);
पूर्ण
