<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/bpf.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयkeeping.h>

#समावेश "../ccm.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_net.h"
#समावेश "fw.h"
#समावेश "main.h"

अटल काष्ठा sk_buff *
nfp_bpf_cmsg_alloc(काष्ठा nfp_app_bpf *bpf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;

	skb = nfp_app_ctrl_msg_alloc(bpf->app, size, GFP_KERNEL);
	skb_put(skb, size);

	वापस skb;
पूर्ण

अटल अचिन्हित पूर्णांक
nfp_bpf_cmsg_map_req_size(काष्ठा nfp_app_bpf *bpf, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक size;

	size = माप(काष्ठा cmsg_req_map_op);
	size += (bpf->cmsg_key_sz + bpf->cmsg_val_sz) * n;

	वापस size;
पूर्ण

अटल काष्ठा sk_buff *
nfp_bpf_cmsg_map_req_alloc(काष्ठा nfp_app_bpf *bpf, अचिन्हित पूर्णांक n)
अणु
	वापस nfp_bpf_cmsg_alloc(bpf, nfp_bpf_cmsg_map_req_size(bpf, n));
पूर्ण

अटल अचिन्हित पूर्णांक
nfp_bpf_cmsg_map_reply_size(काष्ठा nfp_app_bpf *bpf, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक size;

	size = माप(काष्ठा cmsg_reply_map_op);
	size += (bpf->cmsg_key_sz + bpf->cmsg_val_sz) * n;

	वापस size;
पूर्ण

अटल पूर्णांक
nfp_bpf_ctrl_rc_to_त्रुटि_सं(काष्ठा nfp_app_bpf *bpf,
			 काष्ठा cmsg_reply_map_simple *reply)
अणु
	अटल स्थिर पूर्णांक res_table[] = अणु
		[CMSG_RC_SUCCESS]	= 0,
		[CMSG_RC_ERR_MAP_FD]	= -EBADFD,
		[CMSG_RC_ERR_MAP_NOENT]	= -ENOENT,
		[CMSG_RC_ERR_MAP_ERR]	= -EINVAL,
		[CMSG_RC_ERR_MAP_PARSE]	= -EIO,
		[CMSG_RC_ERR_MAP_EXIST]	= -EEXIST,
		[CMSG_RC_ERR_MAP_NOMEM]	= -ENOMEM,
		[CMSG_RC_ERR_MAP_E2BIG]	= -E2BIG,
	पूर्ण;
	u32 rc;

	rc = be32_to_cpu(reply->rc);
	अगर (rc >= ARRAY_SIZE(res_table)) अणु
		cmsg_warn(bpf, "FW responded with invalid status: %u\n", rc);
		वापस -EIO;
	पूर्ण

	वापस res_table[rc];
पूर्ण

दीर्घ दीर्घ पूर्णांक
nfp_bpf_ctrl_alloc_map(काष्ठा nfp_app_bpf *bpf, काष्ठा bpf_map *map)
अणु
	काष्ठा cmsg_reply_map_alloc_tbl *reply;
	काष्ठा cmsg_req_map_alloc_tbl *req;
	काष्ठा sk_buff *skb;
	u32 tid;
	पूर्णांक err;

	skb = nfp_bpf_cmsg_alloc(bpf, माप(*req));
	अगर (!skb)
		वापस -ENOMEM;

	req = (व्योम *)skb->data;
	req->key_size = cpu_to_be32(map->key_size);
	req->value_size = cpu_to_be32(map->value_size);
	req->max_entries = cpu_to_be32(map->max_entries);
	req->map_type = cpu_to_be32(map->map_type);
	req->map_flags = 0;

	skb = nfp_ccm_communicate(&bpf->ccm, skb, NFP_CCM_TYPE_BPF_MAP_ALLOC,
				  माप(*reply));
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	reply = (व्योम *)skb->data;
	err = nfp_bpf_ctrl_rc_to_त्रुटि_सं(bpf, &reply->reply_hdr);
	अगर (err)
		जाओ err_मुक्त;

	tid = be32_to_cpu(reply->tid);
	dev_consume_skb_any(skb);

	वापस tid;
err_मुक्त:
	dev_kमुक्त_skb_any(skb);
	वापस err;
पूर्ण

व्योम nfp_bpf_ctrl_मुक्त_map(काष्ठा nfp_app_bpf *bpf, काष्ठा nfp_bpf_map *nfp_map)
अणु
	काष्ठा cmsg_reply_map_मुक्त_tbl *reply;
	काष्ठा cmsg_req_map_मुक्त_tbl *req;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nfp_bpf_cmsg_alloc(bpf, माप(*req));
	अगर (!skb) अणु
		cmsg_warn(bpf, "leaking map - failed to allocate msg\n");
		वापस;
	पूर्ण

	req = (व्योम *)skb->data;
	req->tid = cpu_to_be32(nfp_map->tid);

	skb = nfp_ccm_communicate(&bpf->ccm, skb, NFP_CCM_TYPE_BPF_MAP_FREE,
				  माप(*reply));
	अगर (IS_ERR(skb)) अणु
		cmsg_warn(bpf, "leaking map - I/O error\n");
		वापस;
	पूर्ण

	reply = (व्योम *)skb->data;
	err = nfp_bpf_ctrl_rc_to_त्रुटि_सं(bpf, &reply->reply_hdr);
	अगर (err)
		cmsg_warn(bpf, "leaking map - FW responded with: %d\n", err);

	dev_consume_skb_any(skb);
पूर्ण

अटल व्योम *
nfp_bpf_ctrl_req_key(काष्ठा nfp_app_bpf *bpf, काष्ठा cmsg_req_map_op *req,
		     अचिन्हित पूर्णांक n)
अणु
	वापस &req->data[bpf->cmsg_key_sz * n + bpf->cmsg_val_sz * n];
पूर्ण

अटल व्योम *
nfp_bpf_ctrl_req_val(काष्ठा nfp_app_bpf *bpf, काष्ठा cmsg_req_map_op *req,
		     अचिन्हित पूर्णांक n)
अणु
	वापस &req->data[bpf->cmsg_key_sz * (n + 1) + bpf->cmsg_val_sz * n];
पूर्ण

अटल व्योम *
nfp_bpf_ctrl_reply_key(काष्ठा nfp_app_bpf *bpf, काष्ठा cmsg_reply_map_op *reply,
		       अचिन्हित पूर्णांक n)
अणु
	वापस &reply->data[bpf->cmsg_key_sz * n + bpf->cmsg_val_sz * n];
पूर्ण

अटल व्योम *
nfp_bpf_ctrl_reply_val(काष्ठा nfp_app_bpf *bpf, काष्ठा cmsg_reply_map_op *reply,
		       अचिन्हित पूर्णांक n)
अणु
	वापस &reply->data[bpf->cmsg_key_sz * (n + 1) + bpf->cmsg_val_sz * n];
पूर्ण

अटल bool nfp_bpf_ctrl_op_cache_invalidate(क्रमागत nfp_ccm_type op)
अणु
	वापस op == NFP_CCM_TYPE_BPF_MAP_UPDATE ||
	       op == NFP_CCM_TYPE_BPF_MAP_DELETE;
पूर्ण

अटल bool nfp_bpf_ctrl_op_cache_capable(क्रमागत nfp_ccm_type op)
अणु
	वापस op == NFP_CCM_TYPE_BPF_MAP_LOOKUP ||
	       op == NFP_CCM_TYPE_BPF_MAP_GETNEXT;
पूर्ण

अटल bool nfp_bpf_ctrl_op_cache_fill(क्रमागत nfp_ccm_type op)
अणु
	वापस op == NFP_CCM_TYPE_BPF_MAP_GETFIRST ||
	       op == NFP_CCM_TYPE_BPF_MAP_GETNEXT;
पूर्ण

अटल अचिन्हित पूर्णांक
nfp_bpf_ctrl_op_cache_get(काष्ठा nfp_bpf_map *nfp_map, क्रमागत nfp_ccm_type op,
			  स्थिर u8 *key, u8 *out_key, u8 *out_value,
			  u32 *cache_gen)
अणु
	काष्ठा bpf_map *map = &nfp_map->offmap->map;
	काष्ठा nfp_app_bpf *bpf = nfp_map->bpf;
	अचिन्हित पूर्णांक i, count, n_entries;
	काष्ठा cmsg_reply_map_op *reply;

	n_entries = nfp_bpf_ctrl_op_cache_fill(op) ? bpf->cmsg_cache_cnt : 1;

	spin_lock(&nfp_map->cache_lock);
	*cache_gen = nfp_map->cache_gen;
	अगर (nfp_map->cache_blockers)
		n_entries = 1;

	अगर (nfp_bpf_ctrl_op_cache_invalidate(op))
		जाओ निकास_block;
	अगर (!nfp_bpf_ctrl_op_cache_capable(op))
		जाओ निकास_unlock;

	अगर (!nfp_map->cache)
		जाओ निकास_unlock;
	अगर (nfp_map->cache_to < kसमय_get_ns())
		जाओ निकास_invalidate;

	reply = (व्योम *)nfp_map->cache->data;
	count = be32_to_cpu(reply->count);

	क्रम (i = 0; i < count; i++) अणु
		व्योम *cached_key;

		cached_key = nfp_bpf_ctrl_reply_key(bpf, reply, i);
		अगर (स_भेद(cached_key, key, map->key_size))
			जारी;

		अगर (op == NFP_CCM_TYPE_BPF_MAP_LOOKUP)
			स_नकल(out_value, nfp_bpf_ctrl_reply_val(bpf, reply, i),
			       map->value_size);
		अगर (op == NFP_CCM_TYPE_BPF_MAP_GETNEXT) अणु
			अगर (i + 1 == count)
				अवरोध;

			स_नकल(out_key,
			       nfp_bpf_ctrl_reply_key(bpf, reply, i + 1),
			       map->key_size);
		पूर्ण

		n_entries = 0;
		जाओ निकास_unlock;
	पूर्ण
	जाओ निकास_unlock;

निकास_block:
	nfp_map->cache_blockers++;
निकास_invalidate:
	dev_consume_skb_any(nfp_map->cache);
	nfp_map->cache = शून्य;
निकास_unlock:
	spin_unlock(&nfp_map->cache_lock);
	वापस n_entries;
पूर्ण

अटल व्योम
nfp_bpf_ctrl_op_cache_put(काष्ठा nfp_bpf_map *nfp_map, क्रमागत nfp_ccm_type op,
			  काष्ठा sk_buff *skb, u32 cache_gen)
अणु
	bool blocker, filler;

	blocker = nfp_bpf_ctrl_op_cache_invalidate(op);
	filler = nfp_bpf_ctrl_op_cache_fill(op);
	अगर (blocker || filler) अणु
		u64 to = 0;

		अगर (filler)
			to = kसमय_get_ns() + NFP_BPF_MAP_CACHE_TIME_NS;

		spin_lock(&nfp_map->cache_lock);
		अगर (blocker) अणु
			nfp_map->cache_blockers--;
			nfp_map->cache_gen++;
		पूर्ण
		अगर (filler && !nfp_map->cache_blockers &&
		    nfp_map->cache_gen == cache_gen) अणु
			nfp_map->cache_to = to;
			swap(nfp_map->cache, skb);
		पूर्ण
		spin_unlock(&nfp_map->cache_lock);
	पूर्ण

	dev_consume_skb_any(skb);
पूर्ण

अटल पूर्णांक
nfp_bpf_ctrl_entry_op(काष्ठा bpf_offloaded_map *offmap, क्रमागत nfp_ccm_type op,
		      u8 *key, u8 *value, u64 flags, u8 *out_key, u8 *out_value)
अणु
	काष्ठा nfp_bpf_map *nfp_map = offmap->dev_priv;
	अचिन्हित पूर्णांक n_entries, reply_entries, count;
	काष्ठा nfp_app_bpf *bpf = nfp_map->bpf;
	काष्ठा bpf_map *map = &offmap->map;
	काष्ठा cmsg_reply_map_op *reply;
	काष्ठा cmsg_req_map_op *req;
	काष्ठा sk_buff *skb;
	u32 cache_gen;
	पूर्णांक err;

	/* FW messages have no space क्रम more than 32 bits of flags */
	अगर (flags >> 32)
		वापस -EOPNOTSUPP;

	/* Handle op cache */
	n_entries = nfp_bpf_ctrl_op_cache_get(nfp_map, op, key, out_key,
					      out_value, &cache_gen);
	अगर (!n_entries)
		वापस 0;

	skb = nfp_bpf_cmsg_map_req_alloc(bpf, 1);
	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ err_cache_put;
	पूर्ण

	req = (व्योम *)skb->data;
	req->tid = cpu_to_be32(nfp_map->tid);
	req->count = cpu_to_be32(n_entries);
	req->flags = cpu_to_be32(flags);

	/* Copy inमाला_दो */
	अगर (key)
		स_नकल(nfp_bpf_ctrl_req_key(bpf, req, 0), key, map->key_size);
	अगर (value)
		स_नकल(nfp_bpf_ctrl_req_val(bpf, req, 0), value,
		       map->value_size);

	skb = nfp_ccm_communicate(&bpf->ccm, skb, op, 0);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		जाओ err_cache_put;
	पूर्ण

	अगर (skb->len < माप(*reply)) अणु
		cmsg_warn(bpf, "cmsg drop - type 0x%02x too short %d!\n",
			  op, skb->len);
		err = -EIO;
		जाओ err_मुक्त;
	पूर्ण

	reply = (व्योम *)skb->data;
	count = be32_to_cpu(reply->count);
	err = nfp_bpf_ctrl_rc_to_त्रुटि_सं(bpf, &reply->reply_hdr);
	/* FW responds with message sized to hold the good entries,
	 * plus one extra entry अगर there was an error.
	 */
	reply_entries = count + !!err;
	अगर (n_entries > 1 && count)
		err = 0;
	अगर (err)
		जाओ err_मुक्त;

	अगर (skb->len != nfp_bpf_cmsg_map_reply_size(bpf, reply_entries)) अणु
		cmsg_warn(bpf, "cmsg drop - type 0x%02x too short %d for %d entries!\n",
			  op, skb->len, reply_entries);
		err = -EIO;
		जाओ err_मुक्त;
	पूर्ण

	/* Copy outमाला_दो */
	अगर (out_key)
		स_नकल(out_key, nfp_bpf_ctrl_reply_key(bpf, reply, 0),
		       map->key_size);
	अगर (out_value)
		स_नकल(out_value, nfp_bpf_ctrl_reply_val(bpf, reply, 0),
		       map->value_size);

	nfp_bpf_ctrl_op_cache_put(nfp_map, op, skb, cache_gen);

	वापस 0;
err_मुक्त:
	dev_kमुक्त_skb_any(skb);
err_cache_put:
	nfp_bpf_ctrl_op_cache_put(nfp_map, op, शून्य, cache_gen);
	वापस err;
पूर्ण

पूर्णांक nfp_bpf_ctrl_update_entry(काष्ठा bpf_offloaded_map *offmap,
			      व्योम *key, व्योम *value, u64 flags)
अणु
	वापस nfp_bpf_ctrl_entry_op(offmap, NFP_CCM_TYPE_BPF_MAP_UPDATE,
				     key, value, flags, शून्य, शून्य);
पूर्ण

पूर्णांक nfp_bpf_ctrl_del_entry(काष्ठा bpf_offloaded_map *offmap, व्योम *key)
अणु
	वापस nfp_bpf_ctrl_entry_op(offmap, NFP_CCM_TYPE_BPF_MAP_DELETE,
				     key, शून्य, 0, शून्य, शून्य);
पूर्ण

पूर्णांक nfp_bpf_ctrl_lookup_entry(काष्ठा bpf_offloaded_map *offmap,
			      व्योम *key, व्योम *value)
अणु
	वापस nfp_bpf_ctrl_entry_op(offmap, NFP_CCM_TYPE_BPF_MAP_LOOKUP,
				     key, शून्य, 0, शून्य, value);
पूर्ण

पूर्णांक nfp_bpf_ctrl_getfirst_entry(काष्ठा bpf_offloaded_map *offmap,
				व्योम *next_key)
अणु
	वापस nfp_bpf_ctrl_entry_op(offmap, NFP_CCM_TYPE_BPF_MAP_GETFIRST,
				     शून्य, शून्य, 0, next_key, शून्य);
पूर्ण

पूर्णांक nfp_bpf_ctrl_getnext_entry(काष्ठा bpf_offloaded_map *offmap,
			       व्योम *key, व्योम *next_key)
अणु
	वापस nfp_bpf_ctrl_entry_op(offmap, NFP_CCM_TYPE_BPF_MAP_GETNEXT,
				     key, शून्य, 0, next_key, शून्य);
पूर्ण

अचिन्हित पूर्णांक nfp_bpf_ctrl_cmsg_min_mtu(काष्ठा nfp_app_bpf *bpf)
अणु
	वापस max(nfp_bpf_cmsg_map_req_size(bpf, 1),
		   nfp_bpf_cmsg_map_reply_size(bpf, 1));
पूर्ण

अचिन्हित पूर्णांक nfp_bpf_ctrl_cmsg_mtu(काष्ठा nfp_app_bpf *bpf)
अणु
	वापस max3(NFP_NET_DEFAULT_MTU,
		    nfp_bpf_cmsg_map_req_size(bpf, NFP_BPF_MAP_CACHE_CNT),
		    nfp_bpf_cmsg_map_reply_size(bpf, NFP_BPF_MAP_CACHE_CNT));
पूर्ण

अचिन्हित पूर्णांक nfp_bpf_ctrl_cmsg_cache_cnt(काष्ठा nfp_app_bpf *bpf)
अणु
	अचिन्हित पूर्णांक mtu, req_max, reply_max, entry_sz;

	mtu = bpf->app->ctrl->dp.mtu;
	entry_sz = bpf->cmsg_key_sz + bpf->cmsg_val_sz;
	req_max = (mtu - माप(काष्ठा cmsg_req_map_op)) / entry_sz;
	reply_max = (mtu - माप(काष्ठा cmsg_reply_map_op)) / entry_sz;

	वापस min3(req_max, reply_max, NFP_BPF_MAP_CACHE_CNT);
पूर्ण

व्योम nfp_bpf_ctrl_msg_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_app_bpf *bpf = app->priv;

	अगर (unlikely(skb->len < माप(काष्ठा cmsg_reply_map_simple))) अणु
		cmsg_warn(bpf, "cmsg drop - too short %d!\n", skb->len);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	अगर (nfp_ccm_get_type(skb) == NFP_CCM_TYPE_BPF_BPF_EVENT) अणु
		अगर (!nfp_bpf_event_output(bpf, skb->data, skb->len))
			dev_consume_skb_any(skb);
		अन्यथा
			dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	nfp_ccm_rx(&bpf->ccm, skb);
पूर्ण

व्योम
nfp_bpf_ctrl_msg_rx_raw(काष्ठा nfp_app *app, स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा nfp_ccm_hdr *hdr = data;
	काष्ठा nfp_app_bpf *bpf = app->priv;

	अगर (unlikely(len < माप(काष्ठा cmsg_reply_map_simple))) अणु
		cmsg_warn(bpf, "cmsg drop - too short %d!\n", len);
		वापस;
	पूर्ण

	अगर (hdr->type == NFP_CCM_TYPE_BPF_BPF_EVENT)
		nfp_bpf_event_output(bpf, data, len);
	अन्यथा
		cmsg_warn(bpf, "cmsg drop - msg type %d with raw buffer!\n",
			  hdr->type);
पूर्ण
