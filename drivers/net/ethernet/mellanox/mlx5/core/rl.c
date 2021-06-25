<शैली गुरु>
/*
 * Copyright (c) 2013-2016, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"

/* Scheduling element fw management */
पूर्णांक mlx5_create_scheduling_element_cmd(काष्ठा mlx5_core_dev *dev, u8 hierarchy,
				       व्योम *ctx, u32 *element_id)
अणु
	u32 out[MLX5_ST_SZ_DW(create_scheduling_element_in)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(create_scheduling_element_in)] = अणुपूर्ण;
	व्योम *schedc;
	पूर्णांक err;

	schedc = MLX5_ADDR_OF(create_scheduling_element_in, in,
			      scheduling_context);
	MLX5_SET(create_scheduling_element_in, in, opcode,
		 MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT);
	MLX5_SET(create_scheduling_element_in, in, scheduling_hierarchy,
		 hierarchy);
	स_नकल(schedc, ctx, MLX5_ST_SZ_BYTES(scheduling_context));

	err = mlx5_cmd_exec_inout(dev, create_scheduling_element, in, out);
	अगर (err)
		वापस err;

	*element_id = MLX5_GET(create_scheduling_element_out, out,
			       scheduling_element_id);
	वापस 0;
पूर्ण

पूर्णांक mlx5_modअगरy_scheduling_element_cmd(काष्ठा mlx5_core_dev *dev, u8 hierarchy,
				       व्योम *ctx, u32 element_id,
				       u32 modअगरy_biपंचांगask)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_scheduling_element_in)] = अणुपूर्ण;
	व्योम *schedc;

	schedc = MLX5_ADDR_OF(modअगरy_scheduling_element_in, in,
			      scheduling_context);
	MLX5_SET(modअगरy_scheduling_element_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT);
	MLX5_SET(modअगरy_scheduling_element_in, in, scheduling_element_id,
		 element_id);
	MLX5_SET(modअगरy_scheduling_element_in, in, modअगरy_biपंचांगask,
		 modअगरy_biपंचांगask);
	MLX5_SET(modअगरy_scheduling_element_in, in, scheduling_hierarchy,
		 hierarchy);
	स_नकल(schedc, ctx, MLX5_ST_SZ_BYTES(scheduling_context));

	वापस mlx5_cmd_exec_in(dev, modअगरy_scheduling_element, in);
पूर्ण

पूर्णांक mlx5_destroy_scheduling_element_cmd(काष्ठा mlx5_core_dev *dev, u8 hierarchy,
					u32 element_id)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_scheduling_element_in)] = अणुपूर्ण;

	MLX5_SET(destroy_scheduling_element_in, in, opcode,
		 MLX5_CMD_OP_DESTROY_SCHEDULING_ELEMENT);
	MLX5_SET(destroy_scheduling_element_in, in, scheduling_element_id,
		 element_id);
	MLX5_SET(destroy_scheduling_element_in, in, scheduling_hierarchy,
		 hierarchy);

	वापस mlx5_cmd_exec_in(dev, destroy_scheduling_element, in);
पूर्ण

अटल bool mlx5_rl_are_equal_raw(काष्ठा mlx5_rl_entry *entry, व्योम *rl_in,
				  u16 uid)
अणु
	वापस (!स_भेद(entry->rl_raw, rl_in, माप(entry->rl_raw)) &&
		entry->uid == uid);
पूर्ण

/* Finds an entry where we can रेजिस्टर the given rate
 * If the rate alपढ़ोy exists, वापस the entry where it is रेजिस्टरed,
 * otherwise वापस the first available entry.
 * If the table is full, वापस शून्य
 */
अटल काष्ठा mlx5_rl_entry *find_rl_entry(काष्ठा mlx5_rl_table *table,
					   व्योम *rl_in, u16 uid, bool dedicated)
अणु
	काष्ठा mlx5_rl_entry *ret_entry = शून्य;
	bool empty_found = false;
	पूर्णांक i;

	lockdep_निश्चित_held(&table->rl_lock);
	WARN_ON(!table->rl_entry);

	क्रम (i = 0; i < table->max_size; i++) अणु
		अगर (dedicated) अणु
			अगर (!table->rl_entry[i].refcount)
				वापस &table->rl_entry[i];
			जारी;
		पूर्ण

		अगर (table->rl_entry[i].refcount) अणु
			अगर (table->rl_entry[i].dedicated)
				जारी;
			अगर (mlx5_rl_are_equal_raw(&table->rl_entry[i], rl_in,
						  uid))
				वापस &table->rl_entry[i];
		पूर्ण अन्यथा अगर (!empty_found) अणु
			empty_found = true;
			ret_entry = &table->rl_entry[i];
		पूर्ण
	पूर्ण

	वापस ret_entry;
पूर्ण

अटल पूर्णांक mlx5_set_pp_rate_limit_cmd(काष्ठा mlx5_core_dev *dev,
				      काष्ठा mlx5_rl_entry *entry, bool set)
अणु
	u32 in[MLX5_ST_SZ_DW(set_pp_rate_limit_in)] = अणुपूर्ण;
	व्योम *pp_context;

	pp_context = MLX5_ADDR_OF(set_pp_rate_limit_in, in, ctx);
	MLX5_SET(set_pp_rate_limit_in, in, opcode,
		 MLX5_CMD_OP_SET_PP_RATE_LIMIT);
	MLX5_SET(set_pp_rate_limit_in, in, uid, entry->uid);
	MLX5_SET(set_pp_rate_limit_in, in, rate_limit_index, entry->index);
	अगर (set)
		स_नकल(pp_context, entry->rl_raw, माप(entry->rl_raw));
	वापस mlx5_cmd_exec_in(dev, set_pp_rate_limit, in);
पूर्ण

bool mlx5_rl_is_in_range(काष्ठा mlx5_core_dev *dev, u32 rate)
अणु
	काष्ठा mlx5_rl_table *table = &dev->priv.rl_table;

	वापस (rate <= table->max_rate && rate >= table->min_rate);
पूर्ण
EXPORT_SYMBOL(mlx5_rl_is_in_range);

bool mlx5_rl_are_equal(काष्ठा mlx5_rate_limit *rl_0,
		       काष्ठा mlx5_rate_limit *rl_1)
अणु
	वापस ((rl_0->rate == rl_1->rate) &&
		(rl_0->max_burst_sz == rl_1->max_burst_sz) &&
		(rl_0->typical_pkt_sz == rl_1->typical_pkt_sz));
पूर्ण
EXPORT_SYMBOL(mlx5_rl_are_equal);

अटल पूर्णांक mlx5_rl_table_get(काष्ठा mlx5_rl_table *table)
अणु
	पूर्णांक i;

	lockdep_निश्चित_held(&table->rl_lock);

	अगर (table->rl_entry) अणु
		table->refcount++;
		वापस 0;
	पूर्ण

	table->rl_entry = kसुस्मृति(table->max_size, माप(काष्ठा mlx5_rl_entry),
				  GFP_KERNEL);
	अगर (!table->rl_entry)
		वापस -ENOMEM;

	/* The index represents the index in HW rate limit table
	 * Index 0 is reserved क्रम unlimited rate
	 */
	क्रम (i = 0; i < table->max_size; i++)
		table->rl_entry[i].index = i + 1;

	table->refcount++;
	वापस 0;
पूर्ण

अटल व्योम mlx5_rl_table_put(काष्ठा mlx5_rl_table *table)
अणु
	lockdep_निश्चित_held(&table->rl_lock);
	अगर (--table->refcount)
		वापस;

	kमुक्त(table->rl_entry);
	table->rl_entry = शून्य;
पूर्ण

अटल व्योम mlx5_rl_table_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rl_table *table)
अणु
	पूर्णांक i;

	अगर (!table->rl_entry)
		वापस;

	/* Clear all configured rates */
	क्रम (i = 0; i < table->max_size; i++)
		अगर (table->rl_entry[i].refcount)
			mlx5_set_pp_rate_limit_cmd(dev, &table->rl_entry[i], false);
	kमुक्त(table->rl_entry);
पूर्ण

अटल व्योम mlx5_rl_entry_get(काष्ठा mlx5_rl_entry *entry)
अणु
	entry->refcount++;
पूर्ण

अटल व्योम
mlx5_rl_entry_put(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rl_entry *entry)
अणु
	entry->refcount--;
	अगर (!entry->refcount)
		mlx5_set_pp_rate_limit_cmd(dev, entry, false);
पूर्ण

पूर्णांक mlx5_rl_add_rate_raw(काष्ठा mlx5_core_dev *dev, व्योम *rl_in, u16 uid,
			 bool dedicated_entry, u16 *index)
अणु
	काष्ठा mlx5_rl_table *table = &dev->priv.rl_table;
	काष्ठा mlx5_rl_entry *entry;
	u32 rate;
	पूर्णांक err;

	अगर (!table->max_size)
		वापस -EOPNOTSUPP;

	rate = MLX5_GET(set_pp_rate_limit_context, rl_in, rate_limit);
	अगर (!rate || !mlx5_rl_is_in_range(dev, rate)) अणु
		mlx5_core_err(dev, "Invalid rate: %u, should be %u to %u\n",
			      rate, table->min_rate, table->max_rate);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&table->rl_lock);
	err = mlx5_rl_table_get(table);
	अगर (err)
		जाओ out;

	entry = find_rl_entry(table, rl_in, uid, dedicated_entry);
	अगर (!entry) अणु
		mlx5_core_err(dev, "Max number of %u rates reached\n",
			      table->max_size);
		err = -ENOSPC;
		जाओ rl_err;
	पूर्ण
	अगर (!entry->refcount) अणु
		/* new rate limit */
		स_नकल(entry->rl_raw, rl_in, माप(entry->rl_raw));
		entry->uid = uid;
		err = mlx5_set_pp_rate_limit_cmd(dev, entry, true);
		अगर (err) अणु
			mlx5_core_err(
				dev,
				"Failed configuring rate limit(err %d): rate %u, max_burst_sz %u, typical_pkt_sz %u\n",
				err, rate,
				MLX5_GET(set_pp_rate_limit_context, rl_in,
					 burst_upper_bound),
				MLX5_GET(set_pp_rate_limit_context, rl_in,
					 typical_packet_size));
			जाओ rl_err;
		पूर्ण

		entry->dedicated = dedicated_entry;
	पूर्ण
	mlx5_rl_entry_get(entry);
	*index = entry->index;
	mutex_unlock(&table->rl_lock);
	वापस 0;

rl_err:
	mlx5_rl_table_put(table);
out:
	mutex_unlock(&table->rl_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_rl_add_rate_raw);

व्योम mlx5_rl_हटाओ_rate_raw(काष्ठा mlx5_core_dev *dev, u16 index)
अणु
	काष्ठा mlx5_rl_table *table = &dev->priv.rl_table;
	काष्ठा mlx5_rl_entry *entry;

	mutex_lock(&table->rl_lock);
	entry = &table->rl_entry[index - 1];
	mlx5_rl_entry_put(dev, entry);
	mlx5_rl_table_put(table);
	mutex_unlock(&table->rl_lock);
पूर्ण
EXPORT_SYMBOL(mlx5_rl_हटाओ_rate_raw);

पूर्णांक mlx5_rl_add_rate(काष्ठा mlx5_core_dev *dev, u16 *index,
		     काष्ठा mlx5_rate_limit *rl)
अणु
	u8 rl_raw[MLX5_ST_SZ_BYTES(set_pp_rate_limit_context)] = अणुपूर्ण;

	MLX5_SET(set_pp_rate_limit_context, rl_raw, rate_limit, rl->rate);
	MLX5_SET(set_pp_rate_limit_context, rl_raw, burst_upper_bound,
		 rl->max_burst_sz);
	MLX5_SET(set_pp_rate_limit_context, rl_raw, typical_packet_size,
		 rl->typical_pkt_sz);

	वापस mlx5_rl_add_rate_raw(dev, rl_raw,
				    MLX5_CAP_QOS(dev, packet_pacing_uid) ?
					MLX5_SHARED_RESOURCE_UID : 0,
				    false, index);
पूर्ण
EXPORT_SYMBOL(mlx5_rl_add_rate);

व्योम mlx5_rl_हटाओ_rate(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rate_limit *rl)
अणु
	u8 rl_raw[MLX5_ST_SZ_BYTES(set_pp_rate_limit_context)] = अणुपूर्ण;
	काष्ठा mlx5_rl_table *table = &dev->priv.rl_table;
	काष्ठा mlx5_rl_entry *entry = शून्य;

	/* 0 is a reserved value क्रम unlimited rate */
	अगर (rl->rate == 0)
		वापस;

	MLX5_SET(set_pp_rate_limit_context, rl_raw, rate_limit, rl->rate);
	MLX5_SET(set_pp_rate_limit_context, rl_raw, burst_upper_bound,
		 rl->max_burst_sz);
	MLX5_SET(set_pp_rate_limit_context, rl_raw, typical_packet_size,
		 rl->typical_pkt_sz);

	mutex_lock(&table->rl_lock);
	entry = find_rl_entry(table, rl_raw,
			      MLX5_CAP_QOS(dev, packet_pacing_uid) ?
				MLX5_SHARED_RESOURCE_UID : 0, false);
	अगर (!entry || !entry->refcount) अणु
		mlx5_core_warn(dev, "Rate %u, max_burst_sz %u typical_pkt_sz %u are not configured\n",
			       rl->rate, rl->max_burst_sz, rl->typical_pkt_sz);
		जाओ out;
	पूर्ण
	mlx5_rl_entry_put(dev, entry);
	mlx5_rl_table_put(table);
out:
	mutex_unlock(&table->rl_lock);
पूर्ण
EXPORT_SYMBOL(mlx5_rl_हटाओ_rate);

पूर्णांक mlx5_init_rl_table(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_rl_table *table = &dev->priv.rl_table;

	अगर (!MLX5_CAP_GEN(dev, qos) || !MLX5_CAP_QOS(dev, packet_pacing)) अणु
		table->max_size = 0;
		वापस 0;
	पूर्ण

	mutex_init(&table->rl_lock);

	/* First entry is reserved क्रम unlimited rate */
	table->max_size = MLX5_CAP_QOS(dev, packet_pacing_rate_table_size) - 1;
	table->max_rate = MLX5_CAP_QOS(dev, packet_pacing_max_rate);
	table->min_rate = MLX5_CAP_QOS(dev, packet_pacing_min_rate);

	mlx5_core_info(dev, "Rate limit: %u rates are supported, range: %uMbps to %uMbps\n",
		       table->max_size,
		       table->min_rate >> 10,
		       table->max_rate >> 10);

	वापस 0;
पूर्ण

व्योम mlx5_cleanup_rl_table(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_rl_table *table = &dev->priv.rl_table;

	अगर (!MLX5_CAP_GEN(dev, qos) || !MLX5_CAP_QOS(dev, packet_pacing))
		वापस;

	mlx5_rl_table_मुक्त(dev, table);
	mutex_destroy(&table->rl_lock);
पूर्ण
