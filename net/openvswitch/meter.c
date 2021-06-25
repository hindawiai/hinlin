<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/अगर.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/swap.h>

#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>

#समावेश "datapath.h"
#समावेश "meter.h"

अटल स्थिर काष्ठा nla_policy meter_policy[OVS_METER_ATTR_MAX + 1] = अणु
	[OVS_METER_ATTR_ID] = अणु .type = NLA_U32, पूर्ण,
	[OVS_METER_ATTR_KBPS] = अणु .type = NLA_FLAG पूर्ण,
	[OVS_METER_ATTR_STATS] = अणु .len = माप(काष्ठा ovs_flow_stats) पूर्ण,
	[OVS_METER_ATTR_BANDS] = अणु .type = NLA_NESTED पूर्ण,
	[OVS_METER_ATTR_USED] = अणु .type = NLA_U64 पूर्ण,
	[OVS_METER_ATTR_CLEAR] = अणु .type = NLA_FLAG पूर्ण,
	[OVS_METER_ATTR_MAX_METERS] = अणु .type = NLA_U32 पूर्ण,
	[OVS_METER_ATTR_MAX_BANDS] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy band_policy[OVS_BAND_ATTR_MAX + 1] = अणु
	[OVS_BAND_ATTR_TYPE] = अणु .type = NLA_U32, पूर्ण,
	[OVS_BAND_ATTR_RATE] = अणु .type = NLA_U32, पूर्ण,
	[OVS_BAND_ATTR_BURST] = अणु .type = NLA_U32, पूर्ण,
	[OVS_BAND_ATTR_STATS] = अणु .len = माप(काष्ठा ovs_flow_stats) पूर्ण,
पूर्ण;

अटल u32 meter_hash(काष्ठा dp_meter_instance *ti, u32 id)
अणु
	वापस id % ti->n_meters;
पूर्ण

अटल व्योम ovs_meter_मुक्त(काष्ठा dp_meter *meter)
अणु
	अगर (!meter)
		वापस;

	kमुक्त_rcu(meter, rcu);
पूर्ण

/* Call with ovs_mutex or RCU पढ़ो lock. */
अटल काष्ठा dp_meter *lookup_meter(स्थिर काष्ठा dp_meter_table *tbl,
				     u32 meter_id)
अणु
	काष्ठा dp_meter_instance *ti = rcu_dereference_ovsl(tbl->ti);
	u32 hash = meter_hash(ti, meter_id);
	काष्ठा dp_meter *meter;

	meter = rcu_dereference_ovsl(ti->dp_meters[hash]);
	अगर (meter && likely(meter->id == meter_id))
		वापस meter;

	वापस शून्य;
पूर्ण

अटल काष्ठा dp_meter_instance *dp_meter_instance_alloc(स्थिर u32 size)
अणु
	काष्ठा dp_meter_instance *ti;

	ti = kvzalloc(माप(*ti) +
		      माप(काष्ठा dp_meter *) * size,
		      GFP_KERNEL);
	अगर (!ti)
		वापस शून्य;

	ti->n_meters = size;

	वापस ti;
पूर्ण

अटल व्योम dp_meter_instance_मुक्त(काष्ठा dp_meter_instance *ti)
अणु
	kvमुक्त(ti);
पूर्ण

अटल व्योम dp_meter_instance_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा dp_meter_instance *ti;

	ti = container_of(rcu, काष्ठा dp_meter_instance, rcu);
	kvमुक्त(ti);
पूर्ण

अटल पूर्णांक
dp_meter_instance_पुनः_स्मृति(काष्ठा dp_meter_table *tbl, u32 size)
अणु
	काष्ठा dp_meter_instance *ti = rcu_dereference_ovsl(tbl->ti);
	पूर्णांक n_meters = min(size, ti->n_meters);
	काष्ठा dp_meter_instance *new_ti;
	पूर्णांक i;

	new_ti = dp_meter_instance_alloc(size);
	अगर (!new_ti)
		वापस -ENOMEM;

	क्रम (i = 0; i < n_meters; i++)
		अगर (rcu_dereference_ovsl(ti->dp_meters[i]))
			new_ti->dp_meters[i] = ti->dp_meters[i];

	rcu_assign_poपूर्णांकer(tbl->ti, new_ti);
	call_rcu(&ti->rcu, dp_meter_instance_मुक्त_rcu);

	वापस 0;
पूर्ण

अटल व्योम dp_meter_instance_insert(काष्ठा dp_meter_instance *ti,
				     काष्ठा dp_meter *meter)
अणु
	u32 hash;

	hash = meter_hash(ti, meter->id);
	rcu_assign_poपूर्णांकer(ti->dp_meters[hash], meter);
पूर्ण

अटल व्योम dp_meter_instance_हटाओ(काष्ठा dp_meter_instance *ti,
				     काष्ठा dp_meter *meter)
अणु
	u32 hash;

	hash = meter_hash(ti, meter->id);
	RCU_INIT_POINTER(ti->dp_meters[hash], शून्य);
पूर्ण

अटल पूर्णांक attach_meter(काष्ठा dp_meter_table *tbl, काष्ठा dp_meter *meter)
अणु
	काष्ठा dp_meter_instance *ti = rcu_dereference_ovsl(tbl->ti);
	u32 hash = meter_hash(ti, meter->id);
	पूर्णांक err;

	/* In generally, slots selected should be empty, because
	 * OvS uses id-pool to fetch a available id.
	 */
	अगर (unlikely(rcu_dereference_ovsl(ti->dp_meters[hash])))
		वापस -EBUSY;

	dp_meter_instance_insert(ti, meter);

	/* That function is thपढ़ो-safe. */
	tbl->count++;
	अगर (tbl->count >= tbl->max_meters_allowed) अणु
		err = -EFBIG;
		जाओ attach_err;
	पूर्ण

	अगर (tbl->count >= ti->n_meters &&
	    dp_meter_instance_पुनः_स्मृति(tbl, ti->n_meters * 2)) अणु
		err = -ENOMEM;
		जाओ attach_err;
	पूर्ण

	वापस 0;

attach_err:
	dp_meter_instance_हटाओ(ti, meter);
	tbl->count--;
	वापस err;
पूर्ण

अटल पूर्णांक detach_meter(काष्ठा dp_meter_table *tbl, काष्ठा dp_meter *meter)
अणु
	काष्ठा dp_meter_instance *ti;

	ASSERT_OVSL();
	अगर (!meter)
		वापस 0;

	ti = rcu_dereference_ovsl(tbl->ti);
	dp_meter_instance_हटाओ(ti, meter);

	tbl->count--;

	/* Shrink the meter array अगर necessary. */
	अगर (ti->n_meters > DP_METER_ARRAY_SIZE_MIN &&
	    tbl->count <= (ti->n_meters / 4)) अणु
		पूर्णांक half_size = ti->n_meters / 2;
		पूर्णांक i;

		/* Aव्योम hash collision, करोn't move slots to other place.
		 * Make sure there are no references of meters in array
		 * which will be released.
		 */
		क्रम (i = half_size; i < ti->n_meters; i++)
			अगर (rcu_dereference_ovsl(ti->dp_meters[i]))
				जाओ out;

		अगर (dp_meter_instance_पुनः_स्मृति(tbl, half_size))
			जाओ shrink_err;
	पूर्ण

out:
	वापस 0;

shrink_err:
	dp_meter_instance_insert(ti, meter);
	tbl->count++;
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा sk_buff *
ovs_meter_cmd_reply_start(काष्ठा genl_info *info, u8 cmd,
			  काष्ठा ovs_header **ovs_reply_header)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ovs_header *ovs_header = info->userhdr;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	*ovs_reply_header = genlmsg_put(skb, info->snd_portid,
					info->snd_seq,
					&dp_meter_genl_family, 0, cmd);
	अगर (!*ovs_reply_header) अणु
		nlmsg_मुक्त(skb);
		वापस ERR_PTR(-EMSGSIZE);
	पूर्ण
	(*ovs_reply_header)->dp_अगरindex = ovs_header->dp_अगरindex;

	वापस skb;
पूर्ण

अटल पूर्णांक ovs_meter_cmd_reply_stats(काष्ठा sk_buff *reply, u32 meter_id,
				     काष्ठा dp_meter *meter)
अणु
	काष्ठा nlattr *nla;
	काष्ठा dp_meter_band *band;
	u16 i;

	अगर (nla_put_u32(reply, OVS_METER_ATTR_ID, meter_id))
		जाओ error;

	अगर (nla_put(reply, OVS_METER_ATTR_STATS,
		    माप(काष्ठा ovs_flow_stats), &meter->stats))
		जाओ error;

	अगर (nla_put_u64_64bit(reply, OVS_METER_ATTR_USED, meter->used,
			      OVS_METER_ATTR_PAD))
		जाओ error;

	nla = nla_nest_start_noflag(reply, OVS_METER_ATTR_BANDS);
	अगर (!nla)
		जाओ error;

	band = meter->bands;

	क्रम (i = 0; i < meter->n_bands; ++i, ++band) अणु
		काष्ठा nlattr *band_nla;

		band_nla = nla_nest_start_noflag(reply, OVS_BAND_ATTR_UNSPEC);
		अगर (!band_nla || nla_put(reply, OVS_BAND_ATTR_STATS,
					 माप(काष्ठा ovs_flow_stats),
					 &band->stats))
			जाओ error;
		nla_nest_end(reply, band_nla);
	पूर्ण
	nla_nest_end(reply, nla);

	वापस 0;
error:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ovs_meter_cmd_features(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा ovs_header *ovs_reply_header;
	काष्ठा nlattr *nla, *band_nla;
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	पूर्णांक err = -EMSGSIZE;

	reply = ovs_meter_cmd_reply_start(info, OVS_METER_CMD_FEATURES,
					  &ovs_reply_header);
	अगर (IS_ERR(reply))
		वापस PTR_ERR(reply);

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (!dp) अणु
		err = -ENODEV;
		जाओ निकास_unlock;
	पूर्ण

	अगर (nla_put_u32(reply, OVS_METER_ATTR_MAX_METERS,
			dp->meter_tbl.max_meters_allowed))
		जाओ निकास_unlock;

	ovs_unlock();

	अगर (nla_put_u32(reply, OVS_METER_ATTR_MAX_BANDS, DP_MAX_BANDS))
		जाओ nla_put_failure;

	nla = nla_nest_start_noflag(reply, OVS_METER_ATTR_BANDS);
	अगर (!nla)
		जाओ nla_put_failure;

	band_nla = nla_nest_start_noflag(reply, OVS_BAND_ATTR_UNSPEC);
	अगर (!band_nla)
		जाओ nla_put_failure;
	/* Currently only DROP band type is supported. */
	अगर (nla_put_u32(reply, OVS_BAND_ATTR_TYPE, OVS_METER_BAND_TYPE_DROP))
		जाओ nla_put_failure;
	nla_nest_end(reply, band_nla);
	nla_nest_end(reply, nla);

	genlmsg_end(reply, ovs_reply_header);
	वापस genlmsg_reply(reply, info);

निकास_unlock:
	ovs_unlock();
nla_put_failure:
	nlmsg_मुक्त(reply);
	वापस err;
पूर्ण

अटल काष्ठा dp_meter *dp_meter_create(काष्ठा nlattr **a)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक rem;
	u16 n_bands = 0;
	काष्ठा dp_meter *meter;
	काष्ठा dp_meter_band *band;
	पूर्णांक err;

	/* Validate attributes, count the bands. */
	अगर (!a[OVS_METER_ATTR_BANDS])
		वापस ERR_PTR(-EINVAL);

	nla_क्रम_each_nested(nla, a[OVS_METER_ATTR_BANDS], rem)
		अगर (++n_bands > DP_MAX_BANDS)
			वापस ERR_PTR(-EINVAL);

	/* Allocate and set up the meter beक्रमe locking anything. */
	meter = kzalloc(काष्ठा_size(meter, bands, n_bands), GFP_KERNEL);
	अगर (!meter)
		वापस ERR_PTR(-ENOMEM);

	meter->id = nla_get_u32(a[OVS_METER_ATTR_ID]);
	meter->used = भाग_u64(kसमय_get_ns(), 1000 * 1000);
	meter->kbps = a[OVS_METER_ATTR_KBPS] ? 1 : 0;
	meter->keep_stats = !a[OVS_METER_ATTR_CLEAR];
	spin_lock_init(&meter->lock);
	अगर (meter->keep_stats && a[OVS_METER_ATTR_STATS]) अणु
		meter->stats = *(काष्ठा ovs_flow_stats *)
			nla_data(a[OVS_METER_ATTR_STATS]);
	पूर्ण
	meter->n_bands = n_bands;

	/* Set up meter bands. */
	band = meter->bands;
	nla_क्रम_each_nested(nla, a[OVS_METER_ATTR_BANDS], rem) अणु
		काष्ठा nlattr *attr[OVS_BAND_ATTR_MAX + 1];
		u32 band_max_delta_t;

		err = nla_parse_deprecated((काष्ठा nlattr **)&attr,
					   OVS_BAND_ATTR_MAX, nla_data(nla),
					   nla_len(nla), band_policy, शून्य);
		अगर (err)
			जाओ निकास_मुक्त_meter;

		अगर (!attr[OVS_BAND_ATTR_TYPE] ||
		    !attr[OVS_BAND_ATTR_RATE] ||
		    !attr[OVS_BAND_ATTR_BURST]) अणु
			err = -EINVAL;
			जाओ निकास_मुक्त_meter;
		पूर्ण

		band->type = nla_get_u32(attr[OVS_BAND_ATTR_TYPE]);
		band->rate = nla_get_u32(attr[OVS_BAND_ATTR_RATE]);
		अगर (band->rate == 0) अणु
			err = -EINVAL;
			जाओ निकास_मुक्त_meter;
		पूर्ण

		band->burst_size = nla_get_u32(attr[OVS_BAND_ATTR_BURST]);
		/* Figure out max delta_t that is enough to fill any bucket.
		 * Keep max_delta_t size to the bucket units:
		 * pkts => 1/1000 packets, kilobits => bits.
		 *
		 * Start with a full bucket.
		 */
		band->bucket = band->burst_size * 1000ULL;
		band_max_delta_t = भाग_u64(band->bucket, band->rate);
		अगर (band_max_delta_t > meter->max_delta_t)
			meter->max_delta_t = band_max_delta_t;
		band++;
	पूर्ण

	वापस meter;

निकास_मुक्त_meter:
	kमुक्त(meter);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक ovs_meter_cmd_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा dp_meter *meter, *old_meter;
	काष्ठा sk_buff *reply;
	काष्ठा ovs_header *ovs_reply_header;
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा dp_meter_table *meter_tbl;
	काष्ठा datapath *dp;
	पूर्णांक err;
	u32 meter_id;
	bool failed;

	अगर (!a[OVS_METER_ATTR_ID])
		वापस -EINVAL;

	meter = dp_meter_create(a);
	अगर (IS_ERR(meter))
		वापस PTR_ERR(meter);

	reply = ovs_meter_cmd_reply_start(info, OVS_METER_CMD_SET,
					  &ovs_reply_header);
	अगर (IS_ERR(reply)) अणु
		err = PTR_ERR(reply);
		जाओ निकास_मुक्त_meter;
	पूर्ण

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (!dp) अणु
		err = -ENODEV;
		जाओ निकास_unlock;
	पूर्ण

	meter_tbl = &dp->meter_tbl;
	meter_id = nla_get_u32(a[OVS_METER_ATTR_ID]);

	old_meter = lookup_meter(meter_tbl, meter_id);
	err = detach_meter(meter_tbl, old_meter);
	अगर (err)
		जाओ निकास_unlock;

	err = attach_meter(meter_tbl, meter);
	अगर (err)
		जाओ निकास_unlock;

	ovs_unlock();

	/* Build response with the meter_id and stats from
	 * the old meter, अगर any.
	 */
	failed = nla_put_u32(reply, OVS_METER_ATTR_ID, meter_id);
	WARN_ON(failed);
	अगर (old_meter) अणु
		spin_lock_bh(&old_meter->lock);
		अगर (old_meter->keep_stats) अणु
			err = ovs_meter_cmd_reply_stats(reply, meter_id,
							old_meter);
			WARN_ON(err);
		पूर्ण
		spin_unlock_bh(&old_meter->lock);
		ovs_meter_मुक्त(old_meter);
	पूर्ण

	genlmsg_end(reply, ovs_reply_header);
	वापस genlmsg_reply(reply, info);

निकास_unlock:
	ovs_unlock();
	nlmsg_मुक्त(reply);
निकास_मुक्त_meter:
	kमुक्त(meter);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_meter_cmd_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा ovs_header *ovs_reply_header;
	काष्ठा nlattr **a = info->attrs;
	काष्ठा dp_meter *meter;
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	u32 meter_id;
	पूर्णांक err;

	अगर (!a[OVS_METER_ATTR_ID])
		वापस -EINVAL;

	meter_id = nla_get_u32(a[OVS_METER_ATTR_ID]);

	reply = ovs_meter_cmd_reply_start(info, OVS_METER_CMD_GET,
					  &ovs_reply_header);
	अगर (IS_ERR(reply))
		वापस PTR_ERR(reply);

	ovs_lock();

	dp = get_dp(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (!dp) अणु
		err = -ENODEV;
		जाओ निकास_unlock;
	पूर्ण

	/* Locate meter, copy stats. */
	meter = lookup_meter(&dp->meter_tbl, meter_id);
	अगर (!meter) अणु
		err = -ENOENT;
		जाओ निकास_unlock;
	पूर्ण

	spin_lock_bh(&meter->lock);
	err = ovs_meter_cmd_reply_stats(reply, meter_id, meter);
	spin_unlock_bh(&meter->lock);
	अगर (err)
		जाओ निकास_unlock;

	ovs_unlock();

	genlmsg_end(reply, ovs_reply_header);
	वापस genlmsg_reply(reply, info);

निकास_unlock:
	ovs_unlock();
	nlmsg_मुक्त(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_meter_cmd_del(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा ovs_header *ovs_reply_header;
	काष्ठा nlattr **a = info->attrs;
	काष्ठा dp_meter *old_meter;
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	u32 meter_id;
	पूर्णांक err;

	अगर (!a[OVS_METER_ATTR_ID])
		वापस -EINVAL;

	reply = ovs_meter_cmd_reply_start(info, OVS_METER_CMD_DEL,
					  &ovs_reply_header);
	अगर (IS_ERR(reply))
		वापस PTR_ERR(reply);

	ovs_lock();

	dp = get_dp(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (!dp) अणु
		err = -ENODEV;
		जाओ निकास_unlock;
	पूर्ण

	meter_id = nla_get_u32(a[OVS_METER_ATTR_ID]);
	old_meter = lookup_meter(&dp->meter_tbl, meter_id);
	अगर (old_meter) अणु
		spin_lock_bh(&old_meter->lock);
		err = ovs_meter_cmd_reply_stats(reply, meter_id, old_meter);
		WARN_ON(err);
		spin_unlock_bh(&old_meter->lock);

		err = detach_meter(&dp->meter_tbl, old_meter);
		अगर (err)
			जाओ निकास_unlock;
	पूर्ण

	ovs_unlock();
	ovs_meter_मुक्त(old_meter);
	genlmsg_end(reply, ovs_reply_header);
	वापस genlmsg_reply(reply, info);

निकास_unlock:
	ovs_unlock();
	nlmsg_मुक्त(reply);
	वापस err;
पूर्ण

/* Meter action execution.
 *
 * Return true 'meter_id' drop band is triggered. The 'skb' should be
 * dropped by the caller'.
 */
bool ovs_meter_execute(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
		       काष्ठा sw_flow_key *key, u32 meter_id)
अणु
	दीर्घ दीर्घ पूर्णांक now_ms = भाग_u64(kसमय_get_ns(), 1000 * 1000);
	दीर्घ दीर्घ पूर्णांक दीर्घ_delta_ms;
	काष्ठा dp_meter_band *band;
	काष्ठा dp_meter *meter;
	पूर्णांक i, band_exceeded_max = -1;
	u32 band_exceeded_rate = 0;
	u32 delta_ms;
	u32 cost;

	meter = lookup_meter(&dp->meter_tbl, meter_id);
	/* Do not drop the packet when there is no meter. */
	अगर (!meter)
		वापस false;

	/* Lock the meter जबतक using it. */
	spin_lock(&meter->lock);

	दीर्घ_delta_ms = (now_ms - meter->used); /* ms */
	अगर (दीर्घ_delta_ms < 0) अणु
		/* This condition means that we have several thपढ़ोs fighting
		 * क्रम a meter lock, and the one who received the packets a
		 * bit later wins. Assuming that all racing thपढ़ोs received
		 * packets at the same समय to aव्योम overflow.
		 */
		दीर्घ_delta_ms = 0;
	पूर्ण

	/* Make sure delta_ms will not be too large, so that bucket will not
	 * wrap around below.
	 */
	delta_ms = (दीर्घ_delta_ms > (दीर्घ दीर्घ पूर्णांक)meter->max_delta_t)
		   ? meter->max_delta_t : (u32)दीर्घ_delta_ms;

	/* Update meter statistics.
	 */
	meter->used = now_ms;
	meter->stats.n_packets += 1;
	meter->stats.n_bytes += skb->len;

	/* Bucket rate is either in kilobits per second, or in packets per
	 * second.  We मुख्यtain the bucket in the units of either bits or
	 * 1/1000th of a packet, correspondingly.
	 * Then, when rate is multiplied with milliseconds, we get the
	 * bucket units:
	 * msec * kbps = bits, and
	 * msec * packets/sec = 1/1000 packets.
	 *
	 * 'cost' is the number of bucket units in this packet.
	 */
	cost = (meter->kbps) ? skb->len * 8 : 1000;

	/* Update all bands and find the one hit with the highest rate. */
	क्रम (i = 0; i < meter->n_bands; ++i) अणु
		दीर्घ दीर्घ पूर्णांक max_bucket_size;

		band = &meter->bands[i];
		max_bucket_size = band->burst_size * 1000LL;

		band->bucket += delta_ms * band->rate;
		अगर (band->bucket > max_bucket_size)
			band->bucket = max_bucket_size;

		अगर (band->bucket >= cost) अणु
			band->bucket -= cost;
		पूर्ण अन्यथा अगर (band->rate > band_exceeded_rate) अणु
			band_exceeded_rate = band->rate;
			band_exceeded_max = i;
		पूर्ण
	पूर्ण

	अगर (band_exceeded_max >= 0) अणु
		/* Update band statistics. */
		band = &meter->bands[band_exceeded_max];
		band->stats.n_packets += 1;
		band->stats.n_bytes += skb->len;

		/* Drop band triggered, let the caller drop the 'skb'.  */
		अगर (band->type == OVS_METER_BAND_TYPE_DROP) अणु
			spin_unlock(&meter->lock);
			वापस true;
		पूर्ण
	पूर्ण

	spin_unlock(&meter->lock);
	वापस false;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops dp_meter_genl_ops[] = अणु
	अणु .cmd = OVS_METER_CMD_FEATURES,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = 0,		  /* OK क्रम unprivileged users. */
		.करोit = ovs_meter_cmd_features
	पूर्ण,
	अणु .cmd = OVS_METER_CMD_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM, /* Requires CAP_NET_ADMIN
					   *  privilege.
					   */
		.करोit = ovs_meter_cmd_set,
	पूर्ण,
	अणु .cmd = OVS_METER_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = 0,		  /* OK क्रम unprivileged users. */
		.करोit = ovs_meter_cmd_get,
	पूर्ण,
	अणु .cmd = OVS_METER_CMD_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM, /* Requires CAP_NET_ADMIN
					   *  privilege.
					   */
		.करोit = ovs_meter_cmd_del
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group ovs_meter_multicast_group = अणु
	.name = OVS_METER_MCGROUP,
पूर्ण;

काष्ठा genl_family dp_meter_genl_family __ro_after_init = अणु
	.hdrsize = माप(काष्ठा ovs_header),
	.name = OVS_METER_FAMILY,
	.version = OVS_METER_VERSION,
	.maxattr = OVS_METER_ATTR_MAX,
	.policy = meter_policy,
	.netnsok = true,
	.parallel_ops = true,
	.small_ops = dp_meter_genl_ops,
	.n_small_ops = ARRAY_SIZE(dp_meter_genl_ops),
	.mcgrps = &ovs_meter_multicast_group,
	.n_mcgrps = 1,
	.module = THIS_MODULE,
पूर्ण;

पूर्णांक ovs_meters_init(काष्ठा datapath *dp)
अणु
	काष्ठा dp_meter_table *tbl = &dp->meter_tbl;
	काष्ठा dp_meter_instance *ti;
	अचिन्हित दीर्घ मुक्त_mem_bytes;

	ti = dp_meter_instance_alloc(DP_METER_ARRAY_SIZE_MIN);
	अगर (!ti)
		वापस -ENOMEM;

	/* Allow meters in a datapath to use ~3.12% of physical memory. */
	मुक्त_mem_bytes = nr_मुक्त_buffer_pages() * (PAGE_SIZE >> 5);
	tbl->max_meters_allowed = min(मुक्त_mem_bytes / माप(काष्ठा dp_meter),
				      DP_METER_NUM_MAX);
	अगर (!tbl->max_meters_allowed)
		जाओ out_err;

	rcu_assign_poपूर्णांकer(tbl->ti, ti);
	tbl->count = 0;

	वापस 0;

out_err:
	dp_meter_instance_मुक्त(ti);
	वापस -ENOMEM;
पूर्ण

व्योम ovs_meters_निकास(काष्ठा datapath *dp)
अणु
	काष्ठा dp_meter_table *tbl = &dp->meter_tbl;
	काष्ठा dp_meter_instance *ti = rcu_dereference_raw(tbl->ti);
	पूर्णांक i;

	क्रम (i = 0; i < ti->n_meters; i++)
		ovs_meter_मुक्त(rcu_dereference_raw(ti->dp_meters[i]));

	dp_meter_instance_मुक्त(ti);
पूर्ण
