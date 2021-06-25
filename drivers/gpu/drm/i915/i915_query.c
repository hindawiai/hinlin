<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/nospec.h>

#समावेश "i915_drv.h"
#समावेश "i915_perf.h"
#समावेश "i915_query.h"
#समावेश <uapi/drm/i915_drm.h>

अटल पूर्णांक copy_query_item(व्योम *query_hdr, माप_प्रकार query_sz,
			   u32 total_length,
			   काष्ठा drm_i915_query_item *query_item)
अणु
	अगर (query_item->length == 0)
		वापस total_length;

	अगर (query_item->length < total_length)
		वापस -EINVAL;

	अगर (copy_from_user(query_hdr, u64_to_user_ptr(query_item->data_ptr),
			   query_sz))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक query_topology_info(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा drm_i915_query_item *query_item)
अणु
	स्थिर काष्ठा sseu_dev_info *sseu = &dev_priv->gt.info.sseu;
	काष्ठा drm_i915_query_topology_info topo;
	u32 slice_length, subslice_length, eu_length, total_length;
	पूर्णांक ret;

	अगर (query_item->flags != 0)
		वापस -EINVAL;

	अगर (sseu->max_slices == 0)
		वापस -ENODEV;

	BUILD_BUG_ON(माप(u8) != माप(sseu->slice_mask));

	slice_length = माप(sseu->slice_mask);
	subslice_length = sseu->max_slices * sseu->ss_stride;
	eu_length = sseu->max_slices * sseu->max_subslices * sseu->eu_stride;
	total_length = माप(topo) + slice_length + subslice_length +
		       eu_length;

	ret = copy_query_item(&topo, माप(topo), total_length,
			      query_item);
	अगर (ret != 0)
		वापस ret;

	अगर (topo.flags != 0)
		वापस -EINVAL;

	स_रखो(&topo, 0, माप(topo));
	topo.max_slices = sseu->max_slices;
	topo.max_subslices = sseu->max_subslices;
	topo.max_eus_per_subslice = sseu->max_eus_per_subslice;

	topo.subslice_offset = slice_length;
	topo.subslice_stride = sseu->ss_stride;
	topo.eu_offset = slice_length + subslice_length;
	topo.eu_stride = sseu->eu_stride;

	अगर (copy_to_user(u64_to_user_ptr(query_item->data_ptr),
			   &topo, माप(topo)))
		वापस -EFAULT;

	अगर (copy_to_user(u64_to_user_ptr(query_item->data_ptr + माप(topo)),
			   &sseu->slice_mask, slice_length))
		वापस -EFAULT;

	अगर (copy_to_user(u64_to_user_ptr(query_item->data_ptr +
					   माप(topo) + slice_length),
			   sseu->subslice_mask, subslice_length))
		वापस -EFAULT;

	अगर (copy_to_user(u64_to_user_ptr(query_item->data_ptr +
					   माप(topo) +
					   slice_length + subslice_length),
			   sseu->eu_mask, eu_length))
		वापस -EFAULT;

	वापस total_length;
पूर्ण

अटल पूर्णांक
query_engine_info(काष्ठा drm_i915_निजी *i915,
		  काष्ठा drm_i915_query_item *query_item)
अणु
	काष्ठा drm_i915_query_engine_info __user *query_ptr =
				u64_to_user_ptr(query_item->data_ptr);
	काष्ठा drm_i915_engine_info __user *info_ptr;
	काष्ठा drm_i915_query_engine_info query;
	काष्ठा drm_i915_engine_info info = अणु पूर्ण;
	अचिन्हित पूर्णांक num_uabi_engines = 0;
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक len, ret;

	अगर (query_item->flags)
		वापस -EINVAL;

	क्रम_each_uabi_engine(engine, i915)
		num_uabi_engines++;

	len = काष्ठा_size(query_ptr, engines, num_uabi_engines);

	ret = copy_query_item(&query, माप(query), len, query_item);
	अगर (ret != 0)
		वापस ret;

	अगर (query.num_engines || query.rsvd[0] || query.rsvd[1] ||
	    query.rsvd[2])
		वापस -EINVAL;

	info_ptr = &query_ptr->engines[0];

	क्रम_each_uabi_engine(engine, i915) अणु
		info.engine.engine_class = engine->uabi_class;
		info.engine.engine_instance = engine->uabi_instance;
		info.capabilities = engine->uabi_capabilities;

		अगर (copy_to_user(info_ptr, &info, माप(info)))
			वापस -EFAULT;

		query.num_engines++;
		info_ptr++;
	पूर्ण

	अगर (copy_to_user(query_ptr, &query, माप(query)))
		वापस -EFAULT;

	वापस len;
पूर्ण

अटल पूर्णांक can_copy_perf_config_रेजिस्टरs_or_number(u32 user_n_regs,
						    u64 user_regs_ptr,
						    u32 kernel_n_regs)
अणु
	/*
	 * We'll just put the number of registers, and won't copy the
	 * रेजिस्टर.
	 */
	अगर (user_n_regs == 0)
		वापस 0;

	अगर (user_n_regs < kernel_n_regs)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक copy_perf_config_रेजिस्टरs_or_number(स्थिर काष्ठा i915_oa_reg *kernel_regs,
						u32 kernel_n_regs,
						u64 user_regs_ptr,
						u32 *user_n_regs)
अणु
	u32 __user *p = u64_to_user_ptr(user_regs_ptr);
	u32 r;

	अगर (*user_n_regs == 0) अणु
		*user_n_regs = kernel_n_regs;
		वापस 0;
	पूर्ण

	*user_n_regs = kernel_n_regs;

	अगर (!user_ग_लिखो_access_begin(p, 2 * माप(u32) * kernel_n_regs))
		वापस -EFAULT;

	क्रम (r = 0; r < kernel_n_regs; r++, p += 2) अणु
		unsafe_put_user(i915_mmio_reg_offset(kernel_regs[r].addr),
				p, Efault);
		unsafe_put_user(kernel_regs[r].value, p + 1, Efault);
	पूर्ण
	user_ग_लिखो_access_end();
	वापस 0;
Efault:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक query_perf_config_data(काष्ठा drm_i915_निजी *i915,
				  काष्ठा drm_i915_query_item *query_item,
				  bool use_uuid)
अणु
	काष्ठा drm_i915_query_perf_config __user *user_query_config_ptr =
		u64_to_user_ptr(query_item->data_ptr);
	काष्ठा drm_i915_perf_oa_config __user *user_config_ptr =
		u64_to_user_ptr(query_item->data_ptr +
				माप(काष्ठा drm_i915_query_perf_config));
	काष्ठा drm_i915_perf_oa_config user_config;
	काष्ठा i915_perf *perf = &i915->perf;
	काष्ठा i915_oa_config *oa_config;
	अक्षर uuid[UUID_STRING_LEN + 1];
	u64 config_id;
	u32 flags, total_size;
	पूर्णांक ret;

	अगर (!perf->i915)
		वापस -ENODEV;

	total_size =
		माप(काष्ठा drm_i915_query_perf_config) +
		माप(काष्ठा drm_i915_perf_oa_config);

	अगर (query_item->length == 0)
		वापस total_size;

	अगर (query_item->length < total_size) अणु
		DRM_DEBUG("Invalid query config data item size=%u expected=%u\n",
			  query_item->length, total_size);
		वापस -EINVAL;
	पूर्ण

	अगर (get_user(flags, &user_query_config_ptr->flags))
		वापस -EFAULT;

	अगर (flags != 0)
		वापस -EINVAL;

	अगर (use_uuid) अणु
		काष्ठा i915_oa_config *पंचांगp;
		पूर्णांक id;

		BUILD_BUG_ON(माप(user_query_config_ptr->uuid) >= माप(uuid));

		स_रखो(&uuid, 0, माप(uuid));
		अगर (copy_from_user(uuid, user_query_config_ptr->uuid,
				     माप(user_query_config_ptr->uuid)))
			वापस -EFAULT;

		oa_config = शून्य;
		rcu_पढ़ो_lock();
		idr_क्रम_each_entry(&perf->metrics_idr, पंचांगp, id) अणु
			अगर (!म_भेद(पंचांगp->uuid, uuid)) अणु
				oa_config = i915_oa_config_get(पंचांगp);
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		अगर (get_user(config_id, &user_query_config_ptr->config))
			वापस -EFAULT;

		oa_config = i915_perf_get_oa_config(perf, config_id);
	पूर्ण
	अगर (!oa_config)
		वापस -ENOENT;

	अगर (copy_from_user(&user_config, user_config_ptr, माप(user_config))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = can_copy_perf_config_रेजिस्टरs_or_number(user_config.n_boolean_regs,
						       user_config.boolean_regs_ptr,
						       oa_config->b_counter_regs_len);
	अगर (ret)
		जाओ out;

	ret = can_copy_perf_config_रेजिस्टरs_or_number(user_config.n_flex_regs,
						       user_config.flex_regs_ptr,
						       oa_config->flex_regs_len);
	अगर (ret)
		जाओ out;

	ret = can_copy_perf_config_रेजिस्टरs_or_number(user_config.n_mux_regs,
						       user_config.mux_regs_ptr,
						       oa_config->mux_regs_len);
	अगर (ret)
		जाओ out;

	ret = copy_perf_config_रेजिस्टरs_or_number(oa_config->b_counter_regs,
						   oa_config->b_counter_regs_len,
						   user_config.boolean_regs_ptr,
						   &user_config.n_boolean_regs);
	अगर (ret)
		जाओ out;

	ret = copy_perf_config_रेजिस्टरs_or_number(oa_config->flex_regs,
						   oa_config->flex_regs_len,
						   user_config.flex_regs_ptr,
						   &user_config.n_flex_regs);
	अगर (ret)
		जाओ out;

	ret = copy_perf_config_रेजिस्टरs_or_number(oa_config->mux_regs,
						   oa_config->mux_regs_len,
						   user_config.mux_regs_ptr,
						   &user_config.n_mux_regs);
	अगर (ret)
		जाओ out;

	स_नकल(user_config.uuid, oa_config->uuid, माप(user_config.uuid));

	अगर (copy_to_user(user_config_ptr, &user_config, माप(user_config))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = total_size;

out:
	i915_oa_config_put(oa_config);
	वापस ret;
पूर्ण

अटल माप_प्रकार माप_perf_config_list(माप_प्रकार count)
अणु
	वापस माप(काष्ठा drm_i915_query_perf_config) + माप(u64) * count;
पूर्ण

अटल माप_प्रकार माप_perf_metrics(काष्ठा i915_perf *perf)
अणु
	काष्ठा i915_oa_config *पंचांगp;
	माप_प्रकार i;
	पूर्णांक id;

	i = 1;
	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&perf->metrics_idr, पंचांगp, id)
		i++;
	rcu_पढ़ो_unlock();

	वापस माप_perf_config_list(i);
पूर्ण

अटल पूर्णांक query_perf_config_list(काष्ठा drm_i915_निजी *i915,
				  काष्ठा drm_i915_query_item *query_item)
अणु
	काष्ठा drm_i915_query_perf_config __user *user_query_config_ptr =
		u64_to_user_ptr(query_item->data_ptr);
	काष्ठा i915_perf *perf = &i915->perf;
	u64 *oa_config_ids = शून्य;
	पूर्णांक alloc, n_configs;
	u32 flags;
	पूर्णांक ret;

	अगर (!perf->i915)
		वापस -ENODEV;

	अगर (query_item->length == 0)
		वापस माप_perf_metrics(perf);

	अगर (get_user(flags, &user_query_config_ptr->flags))
		वापस -EFAULT;

	अगर (flags != 0)
		वापस -EINVAL;

	n_configs = 1;
	करो अणु
		काष्ठा i915_oa_config *पंचांगp;
		u64 *ids;
		पूर्णांक id;

		ids = kपुनः_स्मृति(oa_config_ids,
			       n_configs * माप(*oa_config_ids),
			       GFP_KERNEL);
		अगर (!ids)
			वापस -ENOMEM;

		alloc = fetch_and_zero(&n_configs);

		ids[n_configs++] = 1ull; /* reserved क्रम test_config */
		rcu_पढ़ो_lock();
		idr_क्रम_each_entry(&perf->metrics_idr, पंचांगp, id) अणु
			अगर (n_configs < alloc)
				ids[n_configs] = id;
			n_configs++;
		पूर्ण
		rcu_पढ़ो_unlock();

		oa_config_ids = ids;
	पूर्ण जबतक (n_configs > alloc);

	अगर (query_item->length < माप_perf_config_list(n_configs)) अणु
		DRM_DEBUG("Invalid query config list item size=%u expected=%zu\n",
			  query_item->length,
			  माप_perf_config_list(n_configs));
		kमुक्त(oa_config_ids);
		वापस -EINVAL;
	पूर्ण

	अगर (put_user(n_configs, &user_query_config_ptr->config)) अणु
		kमुक्त(oa_config_ids);
		वापस -EFAULT;
	पूर्ण

	ret = copy_to_user(user_query_config_ptr + 1,
			   oa_config_ids,
			   n_configs * माप(*oa_config_ids));
	kमुक्त(oa_config_ids);
	अगर (ret)
		वापस -EFAULT;

	वापस माप_perf_config_list(n_configs);
पूर्ण

अटल पूर्णांक query_perf_config(काष्ठा drm_i915_निजी *i915,
			     काष्ठा drm_i915_query_item *query_item)
अणु
	चयन (query_item->flags) अणु
	हाल DRM_I915_QUERY_PERF_CONFIG_LIST:
		वापस query_perf_config_list(i915, query_item);
	हाल DRM_I915_QUERY_PERF_CONFIG_DATA_FOR_UUID:
		वापस query_perf_config_data(i915, query_item, true);
	हाल DRM_I915_QUERY_PERF_CONFIG_DATA_FOR_ID:
		वापस query_perf_config_data(i915, query_item, false);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक (* स्थिर i915_query_funcs[])(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा drm_i915_query_item *query_item) = अणु
	query_topology_info,
	query_engine_info,
	query_perf_config,
पूर्ण;

पूर्णांक i915_query_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_i915_query *args = data;
	काष्ठा drm_i915_query_item __user *user_item_ptr =
		u64_to_user_ptr(args->items_ptr);
	u32 i;

	अगर (args->flags != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < args->num_items; i++, user_item_ptr++) अणु
		काष्ठा drm_i915_query_item item;
		अचिन्हित दीर्घ func_idx;
		पूर्णांक ret;

		अगर (copy_from_user(&item, user_item_ptr, माप(item)))
			वापस -EFAULT;

		अगर (item.query_id == 0)
			वापस -EINVAL;

		अगर (overflows_type(item.query_id - 1, अचिन्हित दीर्घ))
			वापस -EINVAL;

		func_idx = item.query_id - 1;

		ret = -EINVAL;
		अगर (func_idx < ARRAY_SIZE(i915_query_funcs)) अणु
			func_idx = array_index_nospec(func_idx,
						      ARRAY_SIZE(i915_query_funcs));
			ret = i915_query_funcs[func_idx](dev_priv, &item);
		पूर्ण

		/* Only ग_लिखो the length back to userspace अगर they dअगरfer. */
		अगर (ret != item.length && put_user(ret, &user_item_ptr->length))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण
