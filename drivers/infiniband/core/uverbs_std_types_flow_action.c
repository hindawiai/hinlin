<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
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

#समावेश "rdma_core.h"
#समावेश "uverbs.h"
#समावेश <rdma/uverbs_std_types.h>

अटल पूर्णांक uverbs_मुक्त_flow_action(काष्ठा ib_uobject *uobject,
				   क्रमागत rdma_हटाओ_reason why,
				   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_flow_action *action = uobject->object;

	अगर (atomic_पढ़ो(&action->usecnt))
		वापस -EBUSY;

	वापस action->device->ops.destroy_flow_action(action);
पूर्ण

अटल u64 esp_flags_uverbs_to_verbs(काष्ठा uverbs_attr_bundle *attrs,
				     u32 flags, bool is_modअगरy)
अणु
	u64 verbs_flags = flags;

	अगर (uverbs_attr_is_valid(attrs, UVERBS_ATTR_FLOW_ACTION_ESP_ESN))
		verbs_flags |= IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED;

	अगर (is_modअगरy && uverbs_attr_is_valid(attrs,
					      UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS))
		verbs_flags |= IB_FLOW_ACTION_ESP_FLAGS_MOD_ESP_ATTRS;

	वापस verbs_flags;
पूर्ण;

अटल पूर्णांक validate_flow_action_esp_keymat_aes_gcm(काष्ठा ib_flow_action_attrs_esp_keymats *keymat)
अणु
	काष्ठा ib_uverbs_flow_action_esp_keymat_aes_gcm *aes_gcm =
		&keymat->keymat.aes_gcm;

	अगर (aes_gcm->iv_algo > IB_UVERBS_FLOW_ACTION_IV_ALGO_SEQ)
		वापस -EOPNOTSUPP;

	अगर (aes_gcm->key_len != 32 &&
	    aes_gcm->key_len != 24 &&
	    aes_gcm->key_len != 16)
		वापस -EINVAL;

	अगर (aes_gcm->icv_len != 16 &&
	    aes_gcm->icv_len != 8 &&
	    aes_gcm->icv_len != 12)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक (* स्थिर flow_action_esp_keymat_validate[])(काष्ठा ib_flow_action_attrs_esp_keymats *keymat) = अणु
	[IB_UVERBS_FLOW_ACTION_ESP_KEYMAT_AES_GCM] = validate_flow_action_esp_keymat_aes_gcm,
पूर्ण;

अटल पूर्णांक flow_action_esp_replay_none(काष्ठा ib_flow_action_attrs_esp_replays *replay,
				       bool is_modअगरy)
अणु
	/* This is used in order to modअगरy an esp flow action with an enabled
	 * replay protection to a disabled one. This is only supported via
	 * modअगरy, as in create verb we can simply drop the REPLAY attribute and
	 * achieve the same thing.
	 */
	वापस is_modअगरy ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक flow_action_esp_replay_def_ok(काष्ठा ib_flow_action_attrs_esp_replays *replay,
					 bool is_modअगरy)
अणु
	/* Some replay protections could always be enabled without validating
	 * anything.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक (* स्थिर flow_action_esp_replay_validate[])(काष्ठा ib_flow_action_attrs_esp_replays *replay,
						       bool is_modअगरy) = अणु
	[IB_UVERBS_FLOW_ACTION_ESP_REPLAY_NONE] = flow_action_esp_replay_none,
	[IB_UVERBS_FLOW_ACTION_ESP_REPLAY_BMP] = flow_action_esp_replay_def_ok,
पूर्ण;

अटल पूर्णांक parse_esp_ip(क्रमागत ib_flow_spec_type proto,
			स्थिर व्योम __user *val_ptr,
			माप_प्रकार len, जोड़ ib_flow_spec *out)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा ib_uverbs_flow_ipv4_filter ipv4 = अणु
		.src_ip = cpu_to_be32(0xffffffffUL),
		.dst_ip = cpu_to_be32(0xffffffffUL),
		.proto = 0xff,
		.tos = 0xff,
		.ttl = 0xff,
		.flags = 0xff,
	पूर्ण;
	स्थिर काष्ठा ib_uverbs_flow_ipv6_filter ipv6 = अणु
		.src_ip = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण,
		.dst_ip = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण,
		.flow_label = cpu_to_be32(0xffffffffUL),
		.next_hdr = 0xff,
		.traffic_class = 0xff,
		.hop_limit = 0xff,
	पूर्ण;
	जोड़ अणु
		काष्ठा ib_uverbs_flow_ipv4_filter ipv4;
		काष्ठा ib_uverbs_flow_ipv6_filter ipv6;
	पूर्ण user_val = अणुपूर्ण;
	स्थिर व्योम *user_pmask;
	माप_प्रकार val_len;

	/* If the flow IPv4/IPv6 flow specअगरications are extended, the mask
	 * should be changed as well.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा ib_uverbs_flow_ipv4_filter, flags) +
		     माप(ipv4.flags) != माप(ipv4));
	BUILD_BUG_ON(दुरत्व(काष्ठा ib_uverbs_flow_ipv6_filter, reserved) +
		     माप(ipv6.reserved) != माप(ipv6));

	चयन (proto) अणु
	हाल IB_FLOW_SPEC_IPV4:
		अगर (len > माप(user_val.ipv4) &&
		    !ib_is_buffer_cleared(val_ptr + माप(user_val.ipv4),
					  len - माप(user_val.ipv4)))
			वापस -EOPNOTSUPP;

		val_len = min_t(माप_प्रकार, len, माप(user_val.ipv4));
		ret = copy_from_user(&user_val.ipv4, val_ptr,
				     val_len);
		अगर (ret)
			वापस -EFAULT;

		user_pmask = &ipv4;
		अवरोध;
	हाल IB_FLOW_SPEC_IPV6:
		अगर (len > माप(user_val.ipv6) &&
		    !ib_is_buffer_cleared(val_ptr + माप(user_val.ipv6),
					  len - माप(user_val.ipv6)))
			वापस -EOPNOTSUPP;

		val_len = min_t(माप_प्रकार, len, माप(user_val.ipv6));
		ret = copy_from_user(&user_val.ipv6, val_ptr,
				     val_len);
		अगर (ret)
			वापस -EFAULT;

		user_pmask = &ipv6;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ib_uverbs_kern_spec_to_ib_spec_filter(proto, user_pmask,
						     &user_val,
						     val_len, out);
पूर्ण

अटल पूर्णांक flow_action_esp_get_encap(काष्ठा ib_flow_spec_list *out,
				     काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_flow_action_esp_encap uverbs_encap;
	पूर्णांक ret;

	ret = uverbs_copy_from(&uverbs_encap, attrs,
			       UVERBS_ATTR_FLOW_ACTION_ESP_ENCAP);
	अगर (ret)
		वापस ret;

	/* We currently support only one encap */
	अगर (uverbs_encap.next_ptr)
		वापस -EOPNOTSUPP;

	अगर (uverbs_encap.type != IB_FLOW_SPEC_IPV4 &&
	    uverbs_encap.type != IB_FLOW_SPEC_IPV6)
		वापस -EOPNOTSUPP;

	वापस parse_esp_ip(uverbs_encap.type,
			    u64_to_user_ptr(uverbs_encap.val_ptr),
			    uverbs_encap.len,
			    &out->spec);
पूर्ण

काष्ठा ib_flow_action_esp_attr अणु
	काष्ठा	ib_flow_action_attrs_esp		hdr;
	काष्ठा	ib_flow_action_attrs_esp_keymats	keymat;
	काष्ठा	ib_flow_action_attrs_esp_replays	replay;
	/* We currently support only one spec */
	काष्ठा	ib_flow_spec_list			encap;
पूर्ण;

#घोषणा ESP_LAST_SUPPORTED_FLAG		IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW
अटल पूर्णांक parse_flow_action_esp(काष्ठा ib_device *ib_dev,
				 काष्ठा uverbs_attr_bundle *attrs,
				 काष्ठा ib_flow_action_esp_attr *esp_attr,
				 bool is_modअगरy)
अणु
	काष्ठा ib_uverbs_flow_action_esp uverbs_esp = अणुपूर्ण;
	पूर्णांक ret;

	/* Optional param, अगर it करोesn't exist, we get -ENOENT and skip it */
	ret = uverbs_copy_from(&esp_attr->hdr.esn, attrs,
			       UVERBS_ATTR_FLOW_ACTION_ESP_ESN);
	अगर (IS_UVERBS_COPY_ERR(ret))
		वापस ret;

	/* This can be called from FLOW_ACTION_ESP_MODIFY where
	 * UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS is optional
	 */
	अगर (uverbs_attr_is_valid(attrs, UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS)) अणु
		ret = uverbs_copy_from_or_zero(&uverbs_esp, attrs,
					       UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS);
		अगर (ret)
			वापस ret;

		अगर (uverbs_esp.flags & ~((ESP_LAST_SUPPORTED_FLAG << 1) - 1))
			वापस -EOPNOTSUPP;

		esp_attr->hdr.spi = uverbs_esp.spi;
		esp_attr->hdr.seq = uverbs_esp.seq;
		esp_attr->hdr.tfc_pad = uverbs_esp.tfc_pad;
		esp_attr->hdr.hard_limit_pkts = uverbs_esp.hard_limit_pkts;
	पूर्ण
	esp_attr->hdr.flags = esp_flags_uverbs_to_verbs(attrs, uverbs_esp.flags,
							is_modअगरy);

	अगर (uverbs_attr_is_valid(attrs, UVERBS_ATTR_FLOW_ACTION_ESP_KEYMAT)) अणु
		esp_attr->keymat.protocol =
			uverbs_attr_get_क्रमागत_id(attrs,
						UVERBS_ATTR_FLOW_ACTION_ESP_KEYMAT);
		ret = uverbs_copy_from_or_zero(&esp_attr->keymat.keymat,
					       attrs,
					       UVERBS_ATTR_FLOW_ACTION_ESP_KEYMAT);
		अगर (ret)
			वापस ret;

		ret = flow_action_esp_keymat_validate[esp_attr->keymat.protocol](&esp_attr->keymat);
		अगर (ret)
			वापस ret;

		esp_attr->hdr.keymat = &esp_attr->keymat;
	पूर्ण

	अगर (uverbs_attr_is_valid(attrs, UVERBS_ATTR_FLOW_ACTION_ESP_REPLAY)) अणु
		esp_attr->replay.protocol =
			uverbs_attr_get_क्रमागत_id(attrs,
						UVERBS_ATTR_FLOW_ACTION_ESP_REPLAY);

		ret = uverbs_copy_from_or_zero(&esp_attr->replay.replay,
					       attrs,
					       UVERBS_ATTR_FLOW_ACTION_ESP_REPLAY);
		अगर (ret)
			वापस ret;

		ret = flow_action_esp_replay_validate[esp_attr->replay.protocol](&esp_attr->replay,
										 is_modअगरy);
		अगर (ret)
			वापस ret;

		esp_attr->hdr.replay = &esp_attr->replay;
	पूर्ण

	अगर (uverbs_attr_is_valid(attrs, UVERBS_ATTR_FLOW_ACTION_ESP_ENCAP)) अणु
		ret = flow_action_esp_get_encap(&esp_attr->encap, attrs);
		अगर (ret)
			वापस ret;

		esp_attr->hdr.encap = &esp_attr->encap;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_FLOW_ACTION_ESP_CREATE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, UVERBS_ATTR_CREATE_FLOW_ACTION_ESP_HANDLE);
	काष्ठा ib_device *ib_dev = attrs->context->device;
	पूर्णांक				  ret;
	काष्ठा ib_flow_action		  *action;
	काष्ठा ib_flow_action_esp_attr	  esp_attr = अणुपूर्ण;

	अगर (!ib_dev->ops.create_flow_action_esp)
		वापस -EOPNOTSUPP;

	ret = parse_flow_action_esp(ib_dev, attrs, &esp_attr, false);
	अगर (ret)
		वापस ret;

	/* No need to check as this attribute is marked as MANDATORY */
	action = ib_dev->ops.create_flow_action_esp(ib_dev, &esp_attr.hdr,
						    attrs);
	अगर (IS_ERR(action))
		वापस PTR_ERR(action);

	uverbs_flow_action_fill_action(action, uobj, ib_dev,
				       IB_FLOW_ACTION_ESP);

	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_FLOW_ACTION_ESP_MODIFY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, UVERBS_ATTR_MODIFY_FLOW_ACTION_ESP_HANDLE);
	काष्ठा ib_flow_action *action = uobj->object;
	पूर्णांक				  ret;
	काष्ठा ib_flow_action_esp_attr	  esp_attr = अणुपूर्ण;

	अगर (!action->device->ops.modअगरy_flow_action_esp)
		वापस -EOPNOTSUPP;

	ret = parse_flow_action_esp(action->device, attrs, &esp_attr, true);
	अगर (ret)
		वापस ret;

	अगर (action->type != IB_FLOW_ACTION_ESP)
		वापस -EINVAL;

	वापस action->device->ops.modअगरy_flow_action_esp(action,
							  &esp_attr.hdr,
							  attrs);
पूर्ण

अटल स्थिर काष्ठा uverbs_attr_spec uverbs_flow_action_esp_keymat[] = अणु
	[IB_UVERBS_FLOW_ACTION_ESP_KEYMAT_AES_GCM] = अणु
		.type = UVERBS_ATTR_TYPE_PTR_IN,
		UVERBS_ATTR_STRUCT(
			काष्ठा ib_uverbs_flow_action_esp_keymat_aes_gcm,
			aes_key),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा uverbs_attr_spec uverbs_flow_action_esp_replay[] = अणु
	[IB_UVERBS_FLOW_ACTION_ESP_REPLAY_NONE] = अणु
		.type = UVERBS_ATTR_TYPE_PTR_IN,
		UVERBS_ATTR_NO_DATA(),
	पूर्ण,
	[IB_UVERBS_FLOW_ACTION_ESP_REPLAY_BMP] = अणु
		.type = UVERBS_ATTR_TYPE_PTR_IN,
		UVERBS_ATTR_STRUCT(काष्ठा ib_uverbs_flow_action_esp_replay_bmp,
				   size),
	पूर्ण,
पूर्ण;

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_FLOW_ACTION_ESP_CREATE,
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_FLOW_ACTION_ESP_HANDLE,
			UVERBS_OBJECT_FLOW_ACTION,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS,
			   UVERBS_ATTR_STRUCT(काष्ठा ib_uverbs_flow_action_esp,
					      hard_limit_pkts),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_FLOW_ACTION_ESP_ESN,
			   UVERBS_ATTR_TYPE(__u32),
			   UA_OPTIONAL),
	UVERBS_ATTR_ENUM_IN(UVERBS_ATTR_FLOW_ACTION_ESP_KEYMAT,
			    uverbs_flow_action_esp_keymat,
			    UA_MANDATORY),
	UVERBS_ATTR_ENUM_IN(UVERBS_ATTR_FLOW_ACTION_ESP_REPLAY,
			    uverbs_flow_action_esp_replay,
			    UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(
		UVERBS_ATTR_FLOW_ACTION_ESP_ENCAP,
		UVERBS_ATTR_TYPE(काष्ठा ib_uverbs_flow_action_esp_encap),
		UA_OPTIONAL));

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_FLOW_ACTION_ESP_MODIFY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_MODIFY_FLOW_ACTION_ESP_HANDLE,
			UVERBS_OBJECT_FLOW_ACTION,
			UVERBS_ACCESS_WRITE,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS,
			   UVERBS_ATTR_STRUCT(काष्ठा ib_uverbs_flow_action_esp,
					      hard_limit_pkts),
			   UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_FLOW_ACTION_ESP_ESN,
			   UVERBS_ATTR_TYPE(__u32),
			   UA_OPTIONAL),
	UVERBS_ATTR_ENUM_IN(UVERBS_ATTR_FLOW_ACTION_ESP_KEYMAT,
			    uverbs_flow_action_esp_keymat,
			    UA_OPTIONAL),
	UVERBS_ATTR_ENUM_IN(UVERBS_ATTR_FLOW_ACTION_ESP_REPLAY,
			    uverbs_flow_action_esp_replay,
			    UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(
		UVERBS_ATTR_FLOW_ACTION_ESP_ENCAP,
		UVERBS_ATTR_TYPE(काष्ठा ib_uverbs_flow_action_esp_encap),
		UA_OPTIONAL));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_FLOW_ACTION_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_FLOW_ACTION_HANDLE,
			UVERBS_OBJECT_FLOW_ACTION,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	UVERBS_OBJECT_FLOW_ACTION,
	UVERBS_TYPE_ALLOC_IDR(uverbs_मुक्त_flow_action),
	&UVERBS_METHOD(UVERBS_METHOD_FLOW_ACTION_ESP_CREATE),
	&UVERBS_METHOD(UVERBS_METHOD_FLOW_ACTION_DESTROY),
	&UVERBS_METHOD(UVERBS_METHOD_FLOW_ACTION_ESP_MODIFY));

स्थिर काष्ठा uapi_definition uverbs_def_obj_flow_action[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		UVERBS_OBJECT_FLOW_ACTION,
		UAPI_DEF_OBJ_NEEDS_FN(destroy_flow_action)),
	अणुपूर्ण
पूर्ण;
