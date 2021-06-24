<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <net/devlink.h>

#समावेश "spectrum.h"
#समावेश "spectrum_dpipe.h"
#समावेश "spectrum_router.h"

क्रमागत mlxsw_sp_field_metadata_id अणु
	MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT,
	MLXSW_SP_DPIPE_FIELD_METADATA_L3_FORWARD,
	MLXSW_SP_DPIPE_FIELD_METADATA_L3_DROP,
	MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_INDEX,
	MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_SIZE,
	MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_HASH_INDEX,
पूर्ण;

अटल काष्ठा devlink_dpipe_field mlxsw_sp_dpipe_fields_metadata[] = अणु
	अणु
		.name = "erif_port",
		.id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT,
		.bitwidth = 32,
		.mapping_type = DEVLINK_DPIPE_FIELD_MAPPING_TYPE_IFINDEX,
	पूर्ण,
	अणु
		.name = "l3_forward",
		.id = MLXSW_SP_DPIPE_FIELD_METADATA_L3_FORWARD,
		.bitwidth = 1,
	पूर्ण,
	अणु
		.name = "l3_drop",
		.id = MLXSW_SP_DPIPE_FIELD_METADATA_L3_DROP,
		.bitwidth = 1,
	पूर्ण,
	अणु
		.name = "adj_index",
		.id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_INDEX,
		.bitwidth = 32,
	पूर्ण,
	अणु
		.name = "adj_size",
		.id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_SIZE,
		.bitwidth = 32,
	पूर्ण,
	अणु
		.name = "adj_hash_index",
		.id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_HASH_INDEX,
		.bitwidth = 32,
	पूर्ण,
पूर्ण;

क्रमागत mlxsw_sp_dpipe_header_id अणु
	MLXSW_SP_DPIPE_HEADER_METADATA,
पूर्ण;

अटल काष्ठा devlink_dpipe_header mlxsw_sp_dpipe_header_metadata = अणु
	.name = "mlxsw_meta",
	.id = MLXSW_SP_DPIPE_HEADER_METADATA,
	.fields = mlxsw_sp_dpipe_fields_metadata,
	.fields_count = ARRAY_SIZE(mlxsw_sp_dpipe_fields_metadata),
पूर्ण;

अटल काष्ठा devlink_dpipe_header *mlxsw_dpipe_headers[] = अणु
	&mlxsw_sp_dpipe_header_metadata,
	&devlink_dpipe_header_ethernet,
	&devlink_dpipe_header_ipv4,
	&devlink_dpipe_header_ipv6,
पूर्ण;

अटल काष्ठा devlink_dpipe_headers mlxsw_sp_dpipe_headers = अणु
	.headers = mlxsw_dpipe_headers,
	.headers_count = ARRAY_SIZE(mlxsw_dpipe_headers),
पूर्ण;

अटल पूर्णांक mlxsw_sp_dpipe_table_erअगर_actions_dump(व्योम *priv,
						  काष्ठा sk_buff *skb)
अणु
	काष्ठा devlink_dpipe_action action = अणु0पूर्ण;
	पूर्णांक err;

	action.type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action.header = &mlxsw_sp_dpipe_header_metadata;
	action.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_L3_FORWARD;

	err = devlink_dpipe_action_put(skb, &action);
	अगर (err)
		वापस err;

	action.type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action.header = &mlxsw_sp_dpipe_header_metadata;
	action.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_L3_DROP;

	वापस devlink_dpipe_action_put(skb, &action);
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_erअगर_matches_dump(व्योम *priv,
						  काष्ठा sk_buff *skb)
अणु
	काष्ठा devlink_dpipe_match match = अणु0पूर्ण;

	match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match.header = &mlxsw_sp_dpipe_header_metadata;
	match.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;

	वापस devlink_dpipe_match_put(skb, &match);
पूर्ण

अटल व्योम
mlxsw_sp_erअगर_match_action_prepare(काष्ठा devlink_dpipe_match *match,
				   काष्ठा devlink_dpipe_action *action)
अणु
	action->type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action->header = &mlxsw_sp_dpipe_header_metadata;
	action->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_L3_FORWARD;

	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match->header = &mlxsw_sp_dpipe_header_metadata;
	match->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;
पूर्ण

अटल पूर्णांक mlxsw_sp_erअगर_entry_prepare(काष्ठा devlink_dpipe_entry *entry,
				       काष्ठा devlink_dpipe_value *match_value,
				       काष्ठा devlink_dpipe_match *match,
				       काष्ठा devlink_dpipe_value *action_value,
				       काष्ठा devlink_dpipe_action *action)
अणु
	entry->match_values = match_value;
	entry->match_values_count = 1;

	entry->action_values = action_value;
	entry->action_values_count = 1;

	match_value->match = match;
	match_value->value_size = माप(u32);
	match_value->value = kदो_स्मृति(match_value->value_size, GFP_KERNEL);
	अगर (!match_value->value)
		वापस -ENOMEM;

	action_value->action = action;
	action_value->value_size = माप(u32);
	action_value->value = kदो_स्मृति(action_value->value_size, GFP_KERNEL);
	अगर (!action_value->value)
		जाओ err_action_alloc;
	वापस 0;

err_action_alloc:
	kमुक्त(match_value->value);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक mlxsw_sp_erअगर_entry_get(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा devlink_dpipe_entry *entry,
				   काष्ठा mlxsw_sp_rअगर *rअगर,
				   bool counters_enabled)
अणु
	u32 *action_value;
	u32 *rअगर_value;
	u64 cnt;
	पूर्णांक err;

	/* Set Match RIF index */
	rअगर_value = entry->match_values->value;
	*rअगर_value = mlxsw_sp_rअगर_index(rअगर);
	entry->match_values->mapping_value = mlxsw_sp_rअगर_dev_अगरindex(rअगर);
	entry->match_values->mapping_valid = true;

	/* Set Action Forwarding */
	action_value = entry->action_values->value;
	*action_value = 1;

	entry->counter_valid = false;
	entry->counter = 0;
	entry->index = mlxsw_sp_rअगर_index(rअगर);

	अगर (!counters_enabled)
		वापस 0;

	err = mlxsw_sp_rअगर_counter_value_get(mlxsw_sp, rअगर,
					     MLXSW_SP_RIF_COUNTER_EGRESS,
					     &cnt);
	अगर (!err) अणु
		entry->counter = cnt;
		entry->counter_valid = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_erअगर_entries_dump(व्योम *priv, bool counters_enabled,
				       काष्ठा devlink_dpipe_dump_ctx *dump_ctx)
अणु
	काष्ठा devlink_dpipe_value match_value, action_value;
	काष्ठा devlink_dpipe_action action = अणु0पूर्ण;
	काष्ठा devlink_dpipe_match match = अणु0पूर्ण;
	काष्ठा devlink_dpipe_entry entry = अणु0पूर्ण;
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	अचिन्हित पूर्णांक rअगर_count;
	पूर्णांक i, j;
	पूर्णांक err;

	स_रखो(&match_value, 0, माप(match_value));
	स_रखो(&action_value, 0, माप(action_value));

	mlxsw_sp_erअगर_match_action_prepare(&match, &action);
	err = mlxsw_sp_erअगर_entry_prepare(&entry, &match_value, &match,
					  &action_value, &action);
	अगर (err)
		वापस err;

	rअगर_count = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);
	mutex_lock(&mlxsw_sp->router->lock);
	i = 0;
start_again:
	err = devlink_dpipe_entry_ctx_prepare(dump_ctx);
	अगर (err)
		जाओ err_ctx_prepare;
	j = 0;
	क्रम (; i < rअगर_count; i++) अणु
		काष्ठा mlxsw_sp_rअगर *rअगर = mlxsw_sp_rअगर_by_index(mlxsw_sp, i);

		अगर (!rअगर || !mlxsw_sp_rअगर_dev(rअगर))
			जारी;
		err = mlxsw_sp_erअगर_entry_get(mlxsw_sp, &entry, rअगर,
					      counters_enabled);
		अगर (err)
			जाओ err_entry_get;
		err = devlink_dpipe_entry_ctx_append(dump_ctx, &entry);
		अगर (err) अणु
			अगर (err == -EMSGSIZE) अणु
				अगर (!j)
					जाओ err_entry_append;
				अवरोध;
			पूर्ण
			जाओ err_entry_append;
		पूर्ण
		j++;
	पूर्ण

	devlink_dpipe_entry_ctx_बंद(dump_ctx);
	अगर (i != rअगर_count)
		जाओ start_again;
	mutex_unlock(&mlxsw_sp->router->lock);

	devlink_dpipe_entry_clear(&entry);
	वापस 0;
err_entry_append:
err_entry_get:
err_ctx_prepare:
	mutex_unlock(&mlxsw_sp->router->lock);
	devlink_dpipe_entry_clear(&entry);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_erअगर_counters_update(व्योम *priv, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	पूर्णांक i;

	mutex_lock(&mlxsw_sp->router->lock);
	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++) अणु
		काष्ठा mlxsw_sp_rअगर *rअगर = mlxsw_sp_rअगर_by_index(mlxsw_sp, i);

		अगर (!rअगर)
			जारी;
		अगर (enable)
			mlxsw_sp_rअगर_counter_alloc(mlxsw_sp, rअगर,
						   MLXSW_SP_RIF_COUNTER_EGRESS);
		अन्यथा
			mlxsw_sp_rअगर_counter_मुक्त(mlxsw_sp, rअगर,
						  MLXSW_SP_RIF_COUNTER_EGRESS);
	पूर्ण
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस 0;
पूर्ण

अटल u64 mlxsw_sp_dpipe_table_erअगर_size_get(व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	वापस MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);
पूर्ण

अटल काष्ठा devlink_dpipe_table_ops mlxsw_sp_erअगर_ops = अणु
	.matches_dump = mlxsw_sp_dpipe_table_erअगर_matches_dump,
	.actions_dump = mlxsw_sp_dpipe_table_erअगर_actions_dump,
	.entries_dump = mlxsw_sp_dpipe_table_erअगर_entries_dump,
	.counters_set_update = mlxsw_sp_dpipe_table_erअगर_counters_update,
	.size_get = mlxsw_sp_dpipe_table_erअगर_size_get,
पूर्ण;

अटल पूर्णांक mlxsw_sp_dpipe_erअगर_table_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	वापस devlink_dpipe_table_रेजिस्टर(devlink,
					    MLXSW_SP_DPIPE_TABLE_NAME_ERIF,
					    &mlxsw_sp_erअगर_ops,
					    mlxsw_sp, false);
पूर्ण

अटल व्योम mlxsw_sp_dpipe_erअगर_table_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	devlink_dpipe_table_unरेजिस्टर(devlink, MLXSW_SP_DPIPE_TABLE_NAME_ERIF);
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_host_matches_dump(काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा devlink_dpipe_match match = अणु0पूर्ण;
	पूर्णांक err;

	match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match.header = &mlxsw_sp_dpipe_header_metadata;
	match.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;

	err = devlink_dpipe_match_put(skb, &match);
	अगर (err)
		वापस err;

	चयन (type) अणु
	हाल AF_INET:
		match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
		match.header = &devlink_dpipe_header_ipv4;
		match.field_id = DEVLINK_DPIPE_FIELD_IPV4_DST_IP;
		अवरोध;
	हाल AF_INET6:
		match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
		match.header = &devlink_dpipe_header_ipv6;
		match.field_id = DEVLINK_DPIPE_FIELD_IPV6_DST_IP;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	वापस devlink_dpipe_match_put(skb, &match);
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host4_matches_dump(व्योम *priv, काष्ठा sk_buff *skb)
अणु
	वापस mlxsw_sp_dpipe_table_host_matches_dump(skb, AF_INET);
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host_actions_dump(व्योम *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा devlink_dpipe_action action = अणु0पूर्ण;

	action.type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action.header = &devlink_dpipe_header_ethernet;
	action.field_id = DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC;

	वापस devlink_dpipe_action_put(skb, &action);
पूर्ण

क्रमागत mlxsw_sp_dpipe_table_host_match अणु
	MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF,
	MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP,
	MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT,
पूर्ण;

अटल व्योम
mlxsw_sp_dpipe_table_host_match_action_prepare(काष्ठा devlink_dpipe_match *matches,
					       काष्ठा devlink_dpipe_action *action,
					       पूर्णांक type)
अणु
	काष्ठा devlink_dpipe_match *match;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];
	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match->header = &mlxsw_sp_dpipe_header_metadata;
	match->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];
	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	चयन (type) अणु
	हाल AF_INET:
		match->header = &devlink_dpipe_header_ipv4;
		match->field_id = DEVLINK_DPIPE_FIELD_IPV4_DST_IP;
		अवरोध;
	हाल AF_INET6:
		match->header = &devlink_dpipe_header_ipv6;
		match->field_id = DEVLINK_DPIPE_FIELD_IPV6_DST_IP;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	action->type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action->header = &devlink_dpipe_header_ethernet;
	action->field_id = DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host_entry_prepare(काष्ठा devlink_dpipe_entry *entry,
					काष्ठा devlink_dpipe_value *match_values,
					काष्ठा devlink_dpipe_match *matches,
					काष्ठा devlink_dpipe_value *action_value,
					काष्ठा devlink_dpipe_action *action,
					पूर्णांक type)
अणु
	काष्ठा devlink_dpipe_value *match_value;
	काष्ठा devlink_dpipe_match *match;

	entry->match_values = match_values;
	entry->match_values_count = MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT;

	entry->action_values = action_value;
	entry->action_values_count = 1;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];
	match_value = &match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];

	match_value->match = match;
	match_value->value_size = माप(u32);
	match_value->value = kदो_स्मृति(match_value->value_size, GFP_KERNEL);
	अगर (!match_value->value)
		वापस -ENOMEM;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];
	match_value = &match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];

	match_value->match = match;
	चयन (type) अणु
	हाल AF_INET:
		match_value->value_size = माप(u32);
		अवरोध;
	हाल AF_INET6:
		match_value->value_size = माप(काष्ठा in6_addr);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	match_value->value = kदो_स्मृति(match_value->value_size, GFP_KERNEL);
	अगर (!match_value->value)
		वापस -ENOMEM;

	action_value->action = action;
	action_value->value_size = माप(u64);
	action_value->value = kदो_स्मृति(action_value->value_size, GFP_KERNEL);
	अगर (!action_value->value)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम
__mlxsw_sp_dpipe_table_host_entry_fill(काष्ठा devlink_dpipe_entry *entry,
				       काष्ठा mlxsw_sp_rअगर *rअगर,
				       अचिन्हित अक्षर *ha, व्योम *dip)
अणु
	काष्ठा devlink_dpipe_value *value;
	u32 *rअगर_value;
	u8 *ha_value;

	/* Set Match RIF index */
	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];

	rअगर_value = value->value;
	*rअगर_value = mlxsw_sp_rअगर_index(rअगर);
	value->mapping_value = mlxsw_sp_rअगर_dev_अगरindex(rअगर);
	value->mapping_valid = true;

	/* Set Match DIP */
	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];
	स_नकल(value->value, dip, value->value_size);

	/* Set Action DMAC */
	value = entry->action_values;
	ha_value = value->value;
	ether_addr_copy(ha_value, ha);
पूर्ण

अटल व्योम
mlxsw_sp_dpipe_table_host4_entry_fill(काष्ठा devlink_dpipe_entry *entry,
				      काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
				      काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	अचिन्हित अक्षर *ha;
	u32 dip;

	ha = mlxsw_sp_neigh_entry_ha(neigh_entry);
	dip = mlxsw_sp_neigh4_entry_dip(neigh_entry);
	__mlxsw_sp_dpipe_table_host_entry_fill(entry, rअगर, ha, &dip);
पूर्ण

अटल व्योम
mlxsw_sp_dpipe_table_host6_entry_fill(काष्ठा devlink_dpipe_entry *entry,
				      काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
				      काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा in6_addr *dip;
	अचिन्हित अक्षर *ha;

	ha = mlxsw_sp_neigh_entry_ha(neigh_entry);
	dip = mlxsw_sp_neigh6_entry_dip(neigh_entry);

	__mlxsw_sp_dpipe_table_host_entry_fill(entry, rअगर, ha, dip);
पूर्ण

अटल व्योम
mlxsw_sp_dpipe_table_host_entry_fill(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा devlink_dpipe_entry *entry,
				     काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
				     काष्ठा mlxsw_sp_rअगर *rअगर,
				     पूर्णांक type)
अणु
	पूर्णांक err;

	चयन (type) अणु
	हाल AF_INET:
		mlxsw_sp_dpipe_table_host4_entry_fill(entry, neigh_entry, rअगर);
		अवरोध;
	हाल AF_INET6:
		mlxsw_sp_dpipe_table_host6_entry_fill(entry, neigh_entry, rअगर);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	err = mlxsw_sp_neigh_counter_get(mlxsw_sp, neigh_entry,
					 &entry->counter);
	अगर (!err)
		entry->counter_valid = true;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host_entries_get(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा devlink_dpipe_entry *entry,
				      bool counters_enabled,
				      काष्ठा devlink_dpipe_dump_ctx *dump_ctx,
				      पूर्णांक type)
अणु
	पूर्णांक rअगर_neigh_count = 0;
	पूर्णांक rअगर_neigh_skip = 0;
	पूर्णांक neigh_count = 0;
	पूर्णांक rअगर_count;
	पूर्णांक i, j;
	पूर्णांक err;

	mutex_lock(&mlxsw_sp->router->lock);
	i = 0;
	rअगर_count = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);
start_again:
	err = devlink_dpipe_entry_ctx_prepare(dump_ctx);
	अगर (err)
		जाओ err_ctx_prepare;
	j = 0;
	rअगर_neigh_skip = rअगर_neigh_count;
	क्रम (; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++) अणु
		काष्ठा mlxsw_sp_rअगर *rअगर = mlxsw_sp_rअगर_by_index(mlxsw_sp, i);
		काष्ठा mlxsw_sp_neigh_entry *neigh_entry;

		अगर (!rअगर)
			जारी;

		rअगर_neigh_count = 0;
		mlxsw_sp_rअगर_neigh_क्रम_each(neigh_entry, rअगर) अणु
			पूर्णांक neigh_type = mlxsw_sp_neigh_entry_type(neigh_entry);

			अगर (neigh_type != type)
				जारी;

			अगर (neigh_type == AF_INET6 &&
			    mlxsw_sp_neigh_ipv6_ignore(neigh_entry))
				जारी;

			अगर (rअगर_neigh_count < rअगर_neigh_skip)
				जाओ skip;

			mlxsw_sp_dpipe_table_host_entry_fill(mlxsw_sp, entry,
							     neigh_entry, rअगर,
							     type);
			entry->index = neigh_count;
			err = devlink_dpipe_entry_ctx_append(dump_ctx, entry);
			अगर (err) अणु
				अगर (err == -EMSGSIZE) अणु
					अगर (!j)
						जाओ err_entry_append;
					अन्यथा
						जाओ out;
				पूर्ण
				जाओ err_entry_append;
			पूर्ण
			neigh_count++;
			j++;
skip:
			rअगर_neigh_count++;
		पूर्ण
		rअगर_neigh_skip = 0;
	पूर्ण
out:
	devlink_dpipe_entry_ctx_बंद(dump_ctx);
	अगर (i != rअगर_count)
		जाओ start_again;

	mutex_unlock(&mlxsw_sp->router->lock);
	वापस 0;

err_ctx_prepare:
err_entry_append:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host_entries_dump(काष्ठा mlxsw_sp *mlxsw_sp,
				       bool counters_enabled,
				       काष्ठा devlink_dpipe_dump_ctx *dump_ctx,
				       पूर्णांक type)
अणु
	काष्ठा devlink_dpipe_value match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT];
	काष्ठा devlink_dpipe_match matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT];
	काष्ठा devlink_dpipe_value action_value;
	काष्ठा devlink_dpipe_action action = अणु0पूर्ण;
	काष्ठा devlink_dpipe_entry entry = अणु0पूर्ण;
	पूर्णांक err;

	स_रखो(matches, 0, MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT *
			   माप(matches[0]));
	स_रखो(match_values, 0, MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT *
				माप(match_values[0]));
	स_रखो(&action_value, 0, माप(action_value));

	mlxsw_sp_dpipe_table_host_match_action_prepare(matches, &action, type);
	err = mlxsw_sp_dpipe_table_host_entry_prepare(&entry, match_values,
						      matches, &action_value,
						      &action, type);
	अगर (err)
		जाओ out;

	err = mlxsw_sp_dpipe_table_host_entries_get(mlxsw_sp, &entry,
						    counters_enabled, dump_ctx,
						    type);
out:
	devlink_dpipe_entry_clear(&entry);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host4_entries_dump(व्योम *priv, bool counters_enabled,
					काष्ठा devlink_dpipe_dump_ctx *dump_ctx)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	वापस mlxsw_sp_dpipe_table_host_entries_dump(mlxsw_sp,
						      counters_enabled,
						      dump_ctx, AF_INET);
पूर्ण

अटल व्योम
mlxsw_sp_dpipe_table_host_counters_update(काष्ठा mlxsw_sp *mlxsw_sp,
					  bool enable, पूर्णांक type)
अणु
	पूर्णांक i;

	mutex_lock(&mlxsw_sp->router->lock);
	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++) अणु
		काष्ठा mlxsw_sp_rअगर *rअगर = mlxsw_sp_rअगर_by_index(mlxsw_sp, i);
		काष्ठा mlxsw_sp_neigh_entry *neigh_entry;

		अगर (!rअगर)
			जारी;
		mlxsw_sp_rअगर_neigh_क्रम_each(neigh_entry, rअगर) अणु
			पूर्णांक neigh_type = mlxsw_sp_neigh_entry_type(neigh_entry);

			अगर (neigh_type != type)
				जारी;

			अगर (neigh_type == AF_INET6 &&
			    mlxsw_sp_neigh_ipv6_ignore(neigh_entry))
				जारी;

			mlxsw_sp_neigh_entry_counter_update(mlxsw_sp,
							    neigh_entry,
							    enable);
		पूर्ण
	पूर्ण
	mutex_unlock(&mlxsw_sp->router->lock);
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_host4_counters_update(व्योम *priv, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_dpipe_table_host_counters_update(mlxsw_sp, enable, AF_INET);
	वापस 0;
पूर्ण

अटल u64
mlxsw_sp_dpipe_table_host_size_get(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक type)
अणु
	u64 size = 0;
	पूर्णांक i;

	mutex_lock(&mlxsw_sp->router->lock);
	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++) अणु
		काष्ठा mlxsw_sp_rअगर *rअगर = mlxsw_sp_rअगर_by_index(mlxsw_sp, i);
		काष्ठा mlxsw_sp_neigh_entry *neigh_entry;

		अगर (!rअगर)
			जारी;
		mlxsw_sp_rअगर_neigh_क्रम_each(neigh_entry, rअगर) अणु
			पूर्णांक neigh_type = mlxsw_sp_neigh_entry_type(neigh_entry);

			अगर (neigh_type != type)
				जारी;

			अगर (neigh_type == AF_INET6 &&
			    mlxsw_sp_neigh_ipv6_ignore(neigh_entry))
				जारी;

			size++;
		पूर्ण
	पूर्ण
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस size;
पूर्ण

अटल u64 mlxsw_sp_dpipe_table_host4_size_get(व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	वापस mlxsw_sp_dpipe_table_host_size_get(mlxsw_sp, AF_INET);
पूर्ण

अटल काष्ठा devlink_dpipe_table_ops mlxsw_sp_host4_ops = अणु
	.matches_dump = mlxsw_sp_dpipe_table_host4_matches_dump,
	.actions_dump = mlxsw_sp_dpipe_table_host_actions_dump,
	.entries_dump = mlxsw_sp_dpipe_table_host4_entries_dump,
	.counters_set_update = mlxsw_sp_dpipe_table_host4_counters_update,
	.size_get = mlxsw_sp_dpipe_table_host4_size_get,
पूर्ण;

#घोषणा MLXSW_SP_DPIPE_TABLE_RESOURCE_UNIT_HOST4 1

अटल पूर्णांक mlxsw_sp_dpipe_host4_table_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	पूर्णांक err;

	err = devlink_dpipe_table_रेजिस्टर(devlink,
					   MLXSW_SP_DPIPE_TABLE_NAME_HOST4,
					   &mlxsw_sp_host4_ops,
					   mlxsw_sp, false);
	अगर (err)
		वापस err;

	err = devlink_dpipe_table_resource_set(devlink,
					       MLXSW_SP_DPIPE_TABLE_NAME_HOST4,
					       MLXSW_SP_RESOURCE_KVD_HASH_SINGLE,
					       MLXSW_SP_DPIPE_TABLE_RESOURCE_UNIT_HOST4);
	अगर (err)
		जाओ err_resource_set;

	वापस 0;

err_resource_set:
	devlink_dpipe_table_unरेजिस्टर(devlink,
				       MLXSW_SP_DPIPE_TABLE_NAME_HOST4);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_dpipe_host4_table_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	devlink_dpipe_table_unरेजिस्टर(devlink,
				       MLXSW_SP_DPIPE_TABLE_NAME_HOST4);
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host6_matches_dump(व्योम *priv, काष्ठा sk_buff *skb)
अणु
	वापस mlxsw_sp_dpipe_table_host_matches_dump(skb, AF_INET6);
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_host6_entries_dump(व्योम *priv, bool counters_enabled,
					काष्ठा devlink_dpipe_dump_ctx *dump_ctx)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	वापस mlxsw_sp_dpipe_table_host_entries_dump(mlxsw_sp,
						      counters_enabled,
						      dump_ctx, AF_INET6);
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_host6_counters_update(व्योम *priv, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_dpipe_table_host_counters_update(mlxsw_sp, enable, AF_INET6);
	वापस 0;
पूर्ण

अटल u64 mlxsw_sp_dpipe_table_host6_size_get(व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	वापस mlxsw_sp_dpipe_table_host_size_get(mlxsw_sp, AF_INET6);
पूर्ण

अटल काष्ठा devlink_dpipe_table_ops mlxsw_sp_host6_ops = अणु
	.matches_dump = mlxsw_sp_dpipe_table_host6_matches_dump,
	.actions_dump = mlxsw_sp_dpipe_table_host_actions_dump,
	.entries_dump = mlxsw_sp_dpipe_table_host6_entries_dump,
	.counters_set_update = mlxsw_sp_dpipe_table_host6_counters_update,
	.size_get = mlxsw_sp_dpipe_table_host6_size_get,
पूर्ण;

#घोषणा MLXSW_SP_DPIPE_TABLE_RESOURCE_UNIT_HOST6 2

अटल पूर्णांक mlxsw_sp_dpipe_host6_table_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	पूर्णांक err;

	err = devlink_dpipe_table_रेजिस्टर(devlink,
					   MLXSW_SP_DPIPE_TABLE_NAME_HOST6,
					   &mlxsw_sp_host6_ops,
					   mlxsw_sp, false);
	अगर (err)
		वापस err;

	err = devlink_dpipe_table_resource_set(devlink,
					       MLXSW_SP_DPIPE_TABLE_NAME_HOST6,
					       MLXSW_SP_RESOURCE_KVD_HASH_DOUBLE,
					       MLXSW_SP_DPIPE_TABLE_RESOURCE_UNIT_HOST6);
	अगर (err)
		जाओ err_resource_set;

	वापस 0;

err_resource_set:
	devlink_dpipe_table_unरेजिस्टर(devlink,
				       MLXSW_SP_DPIPE_TABLE_NAME_HOST6);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_dpipe_host6_table_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	devlink_dpipe_table_unरेजिस्टर(devlink,
				       MLXSW_SP_DPIPE_TABLE_NAME_HOST6);
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_adj_matches_dump(व्योम *priv,
						 काष्ठा sk_buff *skb)
अणु
	काष्ठा devlink_dpipe_match match = अणु0पूर्ण;
	पूर्णांक err;

	match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match.header = &mlxsw_sp_dpipe_header_metadata;
	match.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_INDEX;

	err = devlink_dpipe_match_put(skb, &match);
	अगर (err)
		वापस err;

	match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match.header = &mlxsw_sp_dpipe_header_metadata;
	match.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_SIZE;

	err = devlink_dpipe_match_put(skb, &match);
	अगर (err)
		वापस err;

	match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match.header = &mlxsw_sp_dpipe_header_metadata;
	match.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_HASH_INDEX;

	वापस devlink_dpipe_match_put(skb, &match);
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_adj_actions_dump(व्योम *priv,
						 काष्ठा sk_buff *skb)
अणु
	काष्ठा devlink_dpipe_action action = अणु0पूर्ण;
	पूर्णांक err;

	action.type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action.header = &devlink_dpipe_header_ethernet;
	action.field_id = DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC;

	err = devlink_dpipe_action_put(skb, &action);
	अगर (err)
		वापस err;

	action.type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action.header = &mlxsw_sp_dpipe_header_metadata;
	action.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;

	वापस devlink_dpipe_action_put(skb, &action);
पूर्ण

अटल u64 mlxsw_sp_dpipe_table_adj_size(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_nexthop *nh;
	u64 size = 0;

	mlxsw_sp_nexthop_क्रम_each(nh, mlxsw_sp->router)
		अगर (mlxsw_sp_nexthop_is_क्रमward(nh) &&
		    !mlxsw_sp_nexthop_group_has_ipip(nh))
			size++;
	वापस size;
पूर्ण

क्रमागत mlxsw_sp_dpipe_table_adj_match अणु
	MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_INDEX,
	MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_SIZE,
	MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_HASH_INDEX,
	MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_COUNT,
पूर्ण;

क्रमागत mlxsw_sp_dpipe_table_adj_action अणु
	MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_DST_MAC,
	MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_ERIF_PORT,
	MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_COUNT,
पूर्ण;

अटल व्योम
mlxsw_sp_dpipe_table_adj_match_action_prepare(काष्ठा devlink_dpipe_match *matches,
					      काष्ठा devlink_dpipe_action *actions)
अणु
	काष्ठा devlink_dpipe_action *action;
	काष्ठा devlink_dpipe_match *match;

	match = &matches[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_INDEX];
	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match->header = &mlxsw_sp_dpipe_header_metadata;
	match->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_INDEX;

	match = &matches[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_SIZE];
	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match->header = &mlxsw_sp_dpipe_header_metadata;
	match->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_SIZE;

	match = &matches[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_HASH_INDEX];
	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match->header = &mlxsw_sp_dpipe_header_metadata;
	match->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ADJ_HASH_INDEX;

	action = &actions[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_DST_MAC];
	action->type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action->header = &devlink_dpipe_header_ethernet;
	action->field_id = DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC;

	action = &actions[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_ERIF_PORT];
	action->type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action->header = &mlxsw_sp_dpipe_header_metadata;
	action->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_adj_entry_prepare(काष्ठा devlink_dpipe_entry *entry,
				       काष्ठा devlink_dpipe_value *match_values,
				       काष्ठा devlink_dpipe_match *matches,
				       काष्ठा devlink_dpipe_value *action_values,
				       काष्ठा devlink_dpipe_action *actions)
अणु	काष्ठा devlink_dpipe_value *action_value;
	काष्ठा devlink_dpipe_value *match_value;
	काष्ठा devlink_dpipe_action *action;
	काष्ठा devlink_dpipe_match *match;

	entry->match_values = match_values;
	entry->match_values_count = MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_COUNT;

	entry->action_values = action_values;
	entry->action_values_count = MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_COUNT;

	match = &matches[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_INDEX];
	match_value = &match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_INDEX];

	match_value->match = match;
	match_value->value_size = माप(u32);
	match_value->value = kदो_स्मृति(match_value->value_size, GFP_KERNEL);
	अगर (!match_value->value)
		वापस -ENOMEM;

	match = &matches[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_SIZE];
	match_value = &match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_SIZE];

	match_value->match = match;
	match_value->value_size = माप(u32);
	match_value->value = kदो_स्मृति(match_value->value_size, GFP_KERNEL);
	अगर (!match_value->value)
		वापस -ENOMEM;

	match = &matches[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_HASH_INDEX];
	match_value = &match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_HASH_INDEX];

	match_value->match = match;
	match_value->value_size = माप(u32);
	match_value->value = kदो_स्मृति(match_value->value_size, GFP_KERNEL);
	अगर (!match_value->value)
		वापस -ENOMEM;

	action = &actions[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_DST_MAC];
	action_value = &action_values[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_DST_MAC];

	action_value->action = action;
	action_value->value_size = माप(u64);
	action_value->value = kदो_स्मृति(action_value->value_size, GFP_KERNEL);
	अगर (!action_value->value)
		वापस -ENOMEM;

	action = &actions[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_ERIF_PORT];
	action_value = &action_values[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_ERIF_PORT];

	action_value->action = action;
	action_value->value_size = माप(u32);
	action_value->value = kदो_स्मृति(action_value->value_size, GFP_KERNEL);
	अगर (!action_value->value)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम
__mlxsw_sp_dpipe_table_adj_entry_fill(काष्ठा devlink_dpipe_entry *entry,
				      u32 adj_index, u32 adj_size,
				      u32 adj_hash_index, अचिन्हित अक्षर *ha,
				      काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा devlink_dpipe_value *value;
	u32 *p_rअगर_value;
	u32 *p_index;

	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_INDEX];
	p_index = value->value;
	*p_index = adj_index;

	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_SIZE];
	p_index = value->value;
	*p_index = adj_size;

	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_HASH_INDEX];
	p_index = value->value;
	*p_index = adj_hash_index;

	value = &entry->action_values[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_DST_MAC];
	ether_addr_copy(value->value, ha);

	value = &entry->action_values[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_ERIF_PORT];
	p_rअगर_value = value->value;
	*p_rअगर_value = mlxsw_sp_rअगर_index(rअगर);
	value->mapping_value = mlxsw_sp_rअगर_dev_अगरindex(rअगर);
	value->mapping_valid = true;
पूर्ण

अटल व्योम mlxsw_sp_dpipe_table_adj_entry_fill(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_nexthop *nh,
						काष्ठा devlink_dpipe_entry *entry)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर = mlxsw_sp_nexthop_rअगर(nh);
	अचिन्हित अक्षर *ha = mlxsw_sp_nexthop_ha(nh);
	u32 adj_hash_index = 0;
	u32 adj_index = 0;
	u32 adj_size = 0;
	पूर्णांक err;

	mlxsw_sp_nexthop_indexes(nh, &adj_index, &adj_size, &adj_hash_index);
	__mlxsw_sp_dpipe_table_adj_entry_fill(entry, adj_index, adj_size,
					      adj_hash_index, ha, rअगर);
	err = mlxsw_sp_nexthop_counter_get(mlxsw_sp, nh, &entry->counter);
	अगर (!err)
		entry->counter_valid = true;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_adj_entries_get(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा devlink_dpipe_entry *entry,
				     bool counters_enabled,
				     काष्ठा devlink_dpipe_dump_ctx *dump_ctx)
अणु
	काष्ठा mlxsw_sp_nexthop *nh;
	पूर्णांक entry_index = 0;
	पूर्णांक nh_count_max;
	पूर्णांक nh_count = 0;
	पूर्णांक nh_skip;
	पूर्णांक j;
	पूर्णांक err;

	mutex_lock(&mlxsw_sp->router->lock);
	nh_count_max = mlxsw_sp_dpipe_table_adj_size(mlxsw_sp);
start_again:
	err = devlink_dpipe_entry_ctx_prepare(dump_ctx);
	अगर (err)
		जाओ err_ctx_prepare;
	j = 0;
	nh_skip = nh_count;
	nh_count = 0;
	mlxsw_sp_nexthop_क्रम_each(nh, mlxsw_sp->router) अणु
		अगर (!mlxsw_sp_nexthop_is_क्रमward(nh) ||
		    mlxsw_sp_nexthop_group_has_ipip(nh))
			जारी;

		अगर (nh_count < nh_skip)
			जाओ skip;

		mlxsw_sp_dpipe_table_adj_entry_fill(mlxsw_sp, nh, entry);
		entry->index = entry_index;
		err = devlink_dpipe_entry_ctx_append(dump_ctx, entry);
		अगर (err) अणु
			अगर (err == -EMSGSIZE) अणु
				अगर (!j)
					जाओ err_entry_append;
				अवरोध;
			पूर्ण
			जाओ err_entry_append;
		पूर्ण
		entry_index++;
		j++;
skip:
		nh_count++;
	पूर्ण

	devlink_dpipe_entry_ctx_बंद(dump_ctx);
	अगर (nh_count != nh_count_max)
		जाओ start_again;
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस 0;

err_ctx_prepare:
err_entry_append:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_dpipe_table_adj_entries_dump(व्योम *priv, bool counters_enabled,
				      काष्ठा devlink_dpipe_dump_ctx *dump_ctx)
अणु
	काष्ठा devlink_dpipe_value action_values[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_COUNT];
	काष्ठा devlink_dpipe_value match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_COUNT];
	काष्ठा devlink_dpipe_action actions[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_COUNT];
	काष्ठा devlink_dpipe_match matches[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_COUNT];
	काष्ठा devlink_dpipe_entry entry = अणु0पूर्ण;
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	पूर्णांक err;

	स_रखो(matches, 0, MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_COUNT *
			   माप(matches[0]));
	स_रखो(match_values, 0, MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_COUNT *
				माप(match_values[0]));
	स_रखो(actions, 0, MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_COUNT *
			   माप(actions[0]));
	स_रखो(action_values, 0, MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_COUNT *
				 माप(action_values[0]));

	mlxsw_sp_dpipe_table_adj_match_action_prepare(matches, actions);
	err = mlxsw_sp_dpipe_table_adj_entry_prepare(&entry,
						     match_values, matches,
						     action_values, actions);
	अगर (err)
		जाओ out;

	err = mlxsw_sp_dpipe_table_adj_entries_get(mlxsw_sp, &entry,
						   counters_enabled, dump_ctx);
out:
	devlink_dpipe_entry_clear(&entry);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_dpipe_table_adj_counters_update(व्योम *priv, bool enable)
अणु
	अक्षर ratr_pl[MLXSW_REG_RATR_LEN];
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	काष्ठा mlxsw_sp_nexthop *nh;
	u32 adj_hash_index = 0;
	u32 adj_index = 0;
	u32 adj_size = 0;

	mlxsw_sp_nexthop_क्रम_each(nh, mlxsw_sp->router) अणु
		अगर (!mlxsw_sp_nexthop_is_क्रमward(nh) ||
		    mlxsw_sp_nexthop_group_has_ipip(nh))
			जारी;

		mlxsw_sp_nexthop_indexes(nh, &adj_index, &adj_size,
					 &adj_hash_index);
		अगर (enable)
			mlxsw_sp_nexthop_counter_alloc(mlxsw_sp, nh);
		अन्यथा
			mlxsw_sp_nexthop_counter_मुक्त(mlxsw_sp, nh);
		mlxsw_sp_nexthop_eth_update(mlxsw_sp,
					    adj_index + adj_hash_index, nh,
					    true, ratr_pl);
	पूर्ण
	वापस 0;
पूर्ण

अटल u64
mlxsw_sp_dpipe_table_adj_size_get(व्योम *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	u64 size;

	mutex_lock(&mlxsw_sp->router->lock);
	size = mlxsw_sp_dpipe_table_adj_size(mlxsw_sp);
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस size;
पूर्ण

अटल काष्ठा devlink_dpipe_table_ops mlxsw_sp_dpipe_table_adj_ops = अणु
	.matches_dump = mlxsw_sp_dpipe_table_adj_matches_dump,
	.actions_dump = mlxsw_sp_dpipe_table_adj_actions_dump,
	.entries_dump = mlxsw_sp_dpipe_table_adj_entries_dump,
	.counters_set_update = mlxsw_sp_dpipe_table_adj_counters_update,
	.size_get = mlxsw_sp_dpipe_table_adj_size_get,
पूर्ण;

#घोषणा MLXSW_SP_DPIPE_TABLE_RESOURCE_UNIT_ADJ 1

अटल पूर्णांक mlxsw_sp_dpipe_adj_table_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	पूर्णांक err;

	err = devlink_dpipe_table_रेजिस्टर(devlink,
					   MLXSW_SP_DPIPE_TABLE_NAME_ADJ,
					   &mlxsw_sp_dpipe_table_adj_ops,
					   mlxsw_sp, false);
	अगर (err)
		वापस err;

	err = devlink_dpipe_table_resource_set(devlink,
					       MLXSW_SP_DPIPE_TABLE_NAME_ADJ,
					       MLXSW_SP_RESOURCE_KVD_LINEAR,
					       MLXSW_SP_DPIPE_TABLE_RESOURCE_UNIT_ADJ);
	अगर (err)
		जाओ err_resource_set;

	वापस 0;

err_resource_set:
	devlink_dpipe_table_unरेजिस्टर(devlink,
				       MLXSW_SP_DPIPE_TABLE_NAME_ADJ);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_dpipe_adj_table_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	devlink_dpipe_table_unरेजिस्टर(devlink,
				       MLXSW_SP_DPIPE_TABLE_NAME_ADJ);
पूर्ण

पूर्णांक mlxsw_sp_dpipe_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	पूर्णांक err;

	err = devlink_dpipe_headers_रेजिस्टर(devlink,
					     &mlxsw_sp_dpipe_headers);
	अगर (err)
		वापस err;
	err = mlxsw_sp_dpipe_erअगर_table_init(mlxsw_sp);
	अगर (err)
		जाओ err_erअगर_table_init;

	err = mlxsw_sp_dpipe_host4_table_init(mlxsw_sp);
	अगर (err)
		जाओ err_host4_table_init;

	err = mlxsw_sp_dpipe_host6_table_init(mlxsw_sp);
	अगर (err)
		जाओ err_host6_table_init;

	err = mlxsw_sp_dpipe_adj_table_init(mlxsw_sp);
	अगर (err)
		जाओ err_adj_table_init;

	वापस 0;
err_adj_table_init:
	mlxsw_sp_dpipe_host6_table_fini(mlxsw_sp);
err_host6_table_init:
	mlxsw_sp_dpipe_host4_table_fini(mlxsw_sp);
err_host4_table_init:
	mlxsw_sp_dpipe_erअगर_table_fini(mlxsw_sp);
err_erअगर_table_init:
	devlink_dpipe_headers_unरेजिस्टर(priv_to_devlink(mlxsw_sp->core));
	वापस err;
पूर्ण

व्योम mlxsw_sp_dpipe_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	mlxsw_sp_dpipe_adj_table_fini(mlxsw_sp);
	mlxsw_sp_dpipe_host6_table_fini(mlxsw_sp);
	mlxsw_sp_dpipe_host4_table_fini(mlxsw_sp);
	mlxsw_sp_dpipe_erअगर_table_fini(mlxsw_sp);
	devlink_dpipe_headers_unरेजिस्टर(devlink);
पूर्ण
