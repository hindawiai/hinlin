<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/smem_state.h>

अटल LIST_HEAD(smem_states);
अटल DEFINE_MUTEX(list_lock);

/**
 * काष्ठा qcom_smem_state - state context
 * @refcount:	refcount क्रम the state
 * @orphan:	boolean indicator that this state has been unरेजिस्टरed
 * @list:	entry in smem_states list
 * @of_node:	of_node to use क्रम matching the state in DT
 * @priv:	implementation निजी data
 * @ops:	ops क्रम the state
 */
काष्ठा qcom_smem_state अणु
	काष्ठा kref refcount;
	bool orphan;

	काष्ठा list_head list;
	काष्ठा device_node *of_node;

	व्योम *priv;

	काष्ठा qcom_smem_state_ops ops;
पूर्ण;

/**
 * qcom_smem_state_update_bits() - update the masked bits in state with value
 * @state:	state handle acquired by calling qcom_smem_state_get()
 * @mask:	bit mask क्रम the change
 * @value:	new value क्रम the masked bits
 *
 * Returns 0 on success, otherwise negative त्रुटि_सं.
 */
पूर्णांक qcom_smem_state_update_bits(काष्ठा qcom_smem_state *state,
				u32 mask,
				u32 value)
अणु
	अगर (state->orphan)
		वापस -ENXIO;

	अगर (!state->ops.update_bits)
		वापस -ENOTSUPP;

	वापस state->ops.update_bits(state->priv, mask, value);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_smem_state_update_bits);

अटल काष्ठा qcom_smem_state *of_node_to_state(काष्ठा device_node *np)
अणु
	काष्ठा qcom_smem_state *state;

	mutex_lock(&list_lock);

	list_क्रम_each_entry(state, &smem_states, list) अणु
		अगर (state->of_node == np) अणु
			kref_get(&state->refcount);
			जाओ unlock;
		पूर्ण
	पूर्ण
	state = ERR_PTR(-EPROBE_DEFER);

unlock:
	mutex_unlock(&list_lock);

	वापस state;
पूर्ण

/**
 * qcom_smem_state_get() - acquire handle to a state
 * @dev:	client device poपूर्णांकer
 * @con_id:	name of the state to lookup
 * @bit:	flags from the state reference, indicating which bit's affected
 *
 * Returns handle to the state, or ERR_PTR(). qcom_smem_state_put() must be
 * called to release the वापसed state handle.
 */
काष्ठा qcom_smem_state *qcom_smem_state_get(काष्ठा device *dev,
					    स्थिर अक्षर *con_id,
					    अचिन्हित *bit)
अणु
	काष्ठा qcom_smem_state *state;
	काष्ठा of_phandle_args args;
	पूर्णांक index = 0;
	पूर्णांक ret;

	अगर (con_id) अणु
		index = of_property_match_string(dev->of_node,
						 "qcom,smem-state-names",
						 con_id);
		अगर (index < 0) अणु
			dev_err(dev, "missing qcom,smem-state-names\n");
			वापस ERR_PTR(index);
		पूर्ण
	पूर्ण

	ret = of_parse_phandle_with_args(dev->of_node,
					 "qcom,smem-states",
					 "#qcom,smem-state-cells",
					 index,
					 &args);
	अगर (ret) अणु
		dev_err(dev, "failed to parse qcom,smem-states property\n");
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (args.args_count != 1) अणु
		dev_err(dev, "invalid #qcom,smem-state-cells\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	state = of_node_to_state(args.np);
	अगर (IS_ERR(state))
		जाओ put;

	*bit = args.args[0];

put:
	of_node_put(args.np);
	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_smem_state_get);

अटल व्योम qcom_smem_state_release(काष्ठा kref *ref)
अणु
	काष्ठा qcom_smem_state *state = container_of(ref, काष्ठा qcom_smem_state, refcount);

	list_del(&state->list);
	kमुक्त(state);
पूर्ण

/**
 * qcom_smem_state_put() - release state handle
 * @state:	state handle to be released
 */
व्योम qcom_smem_state_put(काष्ठा qcom_smem_state *state)
अणु
	mutex_lock(&list_lock);
	kref_put(&state->refcount, qcom_smem_state_release);
	mutex_unlock(&list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_smem_state_put);

/**
 * qcom_smem_state_रेजिस्टर() - रेजिस्टर a new state
 * @of_node:	of_node used क्रम matching client lookups
 * @ops:	implementation ops
 * @priv:	implementation specअगरic निजी data
 */
काष्ठा qcom_smem_state *qcom_smem_state_रेजिस्टर(काष्ठा device_node *of_node,
						 स्थिर काष्ठा qcom_smem_state_ops *ops,
						 व्योम *priv)
अणु
	काष्ठा qcom_smem_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&state->refcount);

	state->of_node = of_node;
	state->ops = *ops;
	state->priv = priv;

	mutex_lock(&list_lock);
	list_add(&state->list, &smem_states);
	mutex_unlock(&list_lock);

	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_smem_state_रेजिस्टर);

/**
 * qcom_smem_state_unरेजिस्टर() - unरेजिस्टर a रेजिस्टरed state
 * @state:	state handle to be unरेजिस्टरed
 */
व्योम qcom_smem_state_unरेजिस्टर(काष्ठा qcom_smem_state *state)
अणु
	state->orphan = true;
	qcom_smem_state_put(state);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_smem_state_unरेजिस्टर);
