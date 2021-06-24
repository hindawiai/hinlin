<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/ipv6.h>

#समावेश "reg.h"
#समावेश "spectrum.h"
#समावेश "spectrum_nve.h"

स्थिर काष्ठा mlxsw_sp_nve_ops *mlxsw_sp1_nve_ops_arr[] = अणु
	[MLXSW_SP_NVE_TYPE_VXLAN]	= &mlxsw_sp1_nve_vxlan_ops,
पूर्ण;

स्थिर काष्ठा mlxsw_sp_nve_ops *mlxsw_sp2_nve_ops_arr[] = अणु
	[MLXSW_SP_NVE_TYPE_VXLAN]	= &mlxsw_sp2_nve_vxlan_ops,
पूर्ण;

काष्ठा mlxsw_sp_nve_mc_entry;
काष्ठा mlxsw_sp_nve_mc_record;
काष्ठा mlxsw_sp_nve_mc_list;

काष्ठा mlxsw_sp_nve_mc_record_ops अणु
	क्रमागत mlxsw_reg_tnumt_record_type type;
	पूर्णांक (*entry_add)(काष्ठा mlxsw_sp_nve_mc_record *mc_record,
			 काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
			 स्थिर जोड़ mlxsw_sp_l3addr *addr);
	व्योम (*entry_del)(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
			  स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry);
	व्योम (*entry_set)(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
			  स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
			  अक्षर *tnumt_pl, अचिन्हित पूर्णांक entry_index);
	bool (*entry_compare)(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
			      स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
			      स्थिर जोड़ mlxsw_sp_l3addr *addr);
पूर्ण;

काष्ठा mlxsw_sp_nve_mc_list_key अणु
	u16 fid_index;
पूर्ण;

काष्ठा mlxsw_sp_nve_mc_ipv6_entry अणु
	काष्ठा in6_addr addr6;
	u32 addr6_kvdl_index;
पूर्ण;

काष्ठा mlxsw_sp_nve_mc_entry अणु
	जोड़ अणु
		__be32 addr4;
		काष्ठा mlxsw_sp_nve_mc_ipv6_entry ipv6_entry;
	पूर्ण;
	u8 valid:1;
पूर्ण;

काष्ठा mlxsw_sp_nve_mc_record अणु
	काष्ठा list_head list;
	क्रमागत mlxsw_sp_l3proto proto;
	अचिन्हित पूर्णांक num_entries;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_nve_mc_list *mc_list;
	स्थिर काष्ठा mlxsw_sp_nve_mc_record_ops *ops;
	u32 kvdl_index;
	काष्ठा mlxsw_sp_nve_mc_entry entries[];
पूर्ण;

काष्ठा mlxsw_sp_nve_mc_list अणु
	काष्ठा list_head records_list;
	काष्ठा rhash_head ht_node;
	काष्ठा mlxsw_sp_nve_mc_list_key key;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_nve_mc_list_ht_params = अणु
	.key_len = माप(काष्ठा mlxsw_sp_nve_mc_list_key),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_nve_mc_list, key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_nve_mc_list, ht_node),
पूर्ण;

अटल पूर्णांक
mlxsw_sp_nve_mc_record_ipv4_entry_add(काष्ठा mlxsw_sp_nve_mc_record *mc_record,
				      काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
				      स्थिर जोड़ mlxsw_sp_l3addr *addr)
अणु
	mc_entry->addr4 = addr->addr4;

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_ipv4_entry_del(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
				      स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry)
अणु
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_ipv4_entry_set(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
				      स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
				      अक्षर *tnumt_pl, अचिन्हित पूर्णांक entry_index)
अणु
	u32 udip = be32_to_cpu(mc_entry->addr4);

	mlxsw_reg_tnumt_udip_set(tnumt_pl, entry_index, udip);
पूर्ण

अटल bool
mlxsw_sp_nve_mc_record_ipv4_entry_compare(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
					  स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
					  स्थिर जोड़ mlxsw_sp_l3addr *addr)
अणु
	वापस mc_entry->addr4 == addr->addr4;
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_nve_mc_record_ops
mlxsw_sp_nve_mc_record_ipv4_ops = अणु
	.type		= MLXSW_REG_TNUMT_RECORD_TYPE_IPV4,
	.entry_add	= &mlxsw_sp_nve_mc_record_ipv4_entry_add,
	.entry_del	= &mlxsw_sp_nve_mc_record_ipv4_entry_del,
	.entry_set	= &mlxsw_sp_nve_mc_record_ipv4_entry_set,
	.entry_compare	= &mlxsw_sp_nve_mc_record_ipv4_entry_compare,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_nve_mc_record_ipv6_entry_add(काष्ठा mlxsw_sp_nve_mc_record *mc_record,
				      काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
				      स्थिर जोड़ mlxsw_sp_l3addr *addr)
अणु
	WARN_ON(1);

	वापस -EINVAL;
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_ipv6_entry_del(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
				      स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry)
अणु
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_ipv6_entry_set(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
				      स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
				      अक्षर *tnumt_pl, अचिन्हित पूर्णांक entry_index)
अणु
	u32 udip_ptr = mc_entry->ipv6_entry.addr6_kvdl_index;

	mlxsw_reg_tnumt_udip_ptr_set(tnumt_pl, entry_index, udip_ptr);
पूर्ण

अटल bool
mlxsw_sp_nve_mc_record_ipv6_entry_compare(स्थिर काष्ठा mlxsw_sp_nve_mc_record *mc_record,
					  स्थिर काष्ठा mlxsw_sp_nve_mc_entry *mc_entry,
					  स्थिर जोड़ mlxsw_sp_l3addr *addr)
अणु
	वापस ipv6_addr_equal(&mc_entry->ipv6_entry.addr6, &addr->addr6);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_nve_mc_record_ops
mlxsw_sp_nve_mc_record_ipv6_ops = अणु
	.type		= MLXSW_REG_TNUMT_RECORD_TYPE_IPV6,
	.entry_add	= &mlxsw_sp_nve_mc_record_ipv6_entry_add,
	.entry_del	= &mlxsw_sp_nve_mc_record_ipv6_entry_del,
	.entry_set	= &mlxsw_sp_nve_mc_record_ipv6_entry_set,
	.entry_compare	= &mlxsw_sp_nve_mc_record_ipv6_entry_compare,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_nve_mc_record_ops *
mlxsw_sp_nve_mc_record_ops_arr[] = अणु
	[MLXSW_SP_L3_PROTO_IPV4] = &mlxsw_sp_nve_mc_record_ipv4_ops,
	[MLXSW_SP_L3_PROTO_IPV6] = &mlxsw_sp_nve_mc_record_ipv6_ops,
पूर्ण;

पूर्णांक mlxsw_sp_nve_learned_ip_resolve(काष्ठा mlxsw_sp *mlxsw_sp, u32 uip,
				    क्रमागत mlxsw_sp_l3proto proto,
				    जोड़ mlxsw_sp_l3addr *addr)
अणु
	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		addr->addr4 = cpu_to_be32(uip);
		वापस 0;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_list *
mlxsw_sp_nve_mc_list_find(काष्ठा mlxsw_sp *mlxsw_sp,
			  स्थिर काष्ठा mlxsw_sp_nve_mc_list_key *key)
अणु
	काष्ठा mlxsw_sp_nve *nve = mlxsw_sp->nve;

	वापस rhashtable_lookup_fast(&nve->mc_list_ht, key,
				      mlxsw_sp_nve_mc_list_ht_params);
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_list *
mlxsw_sp_nve_mc_list_create(काष्ठा mlxsw_sp *mlxsw_sp,
			    स्थिर काष्ठा mlxsw_sp_nve_mc_list_key *key)
अणु
	काष्ठा mlxsw_sp_nve *nve = mlxsw_sp->nve;
	काष्ठा mlxsw_sp_nve_mc_list *mc_list;
	पूर्णांक err;

	mc_list = kदो_स्मृति(माप(*mc_list), GFP_KERNEL);
	अगर (!mc_list)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&mc_list->records_list);
	mc_list->key = *key;

	err = rhashtable_insert_fast(&nve->mc_list_ht, &mc_list->ht_node,
				     mlxsw_sp_nve_mc_list_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	वापस mc_list;

err_rhashtable_insert:
	kमुक्त(mc_list);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_nve_mc_list_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_nve_mc_list *mc_list)
अणु
	काष्ठा mlxsw_sp_nve *nve = mlxsw_sp->nve;

	rhashtable_हटाओ_fast(&nve->mc_list_ht, &mc_list->ht_node,
			       mlxsw_sp_nve_mc_list_ht_params);
	WARN_ON(!list_empty(&mc_list->records_list));
	kमुक्त(mc_list);
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_list *
mlxsw_sp_nve_mc_list_get(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा mlxsw_sp_nve_mc_list_key *key)
अणु
	काष्ठा mlxsw_sp_nve_mc_list *mc_list;

	mc_list = mlxsw_sp_nve_mc_list_find(mlxsw_sp, key);
	अगर (mc_list)
		वापस mc_list;

	वापस mlxsw_sp_nve_mc_list_create(mlxsw_sp, key);
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_list_put(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा mlxsw_sp_nve_mc_list *mc_list)
अणु
	अगर (!list_empty(&mc_list->records_list))
		वापस;
	mlxsw_sp_nve_mc_list_destroy(mlxsw_sp, mc_list);
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_record *
mlxsw_sp_nve_mc_record_create(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_nve_mc_list *mc_list,
			      क्रमागत mlxsw_sp_l3proto proto)
अणु
	अचिन्हित पूर्णांक num_max_entries = mlxsw_sp->nve->num_max_mc_entries[proto];
	काष्ठा mlxsw_sp_nve_mc_record *mc_record;
	पूर्णांक err;

	mc_record = kzalloc(काष्ठा_size(mc_record, entries, num_max_entries),
			    GFP_KERNEL);
	अगर (!mc_record)
		वापस ERR_PTR(-ENOMEM);

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_TNUMT, 1,
				  &mc_record->kvdl_index);
	अगर (err)
		जाओ err_kvdl_alloc;

	mc_record->ops = mlxsw_sp_nve_mc_record_ops_arr[proto];
	mc_record->mlxsw_sp = mlxsw_sp;
	mc_record->mc_list = mc_list;
	mc_record->proto = proto;
	list_add_tail(&mc_record->list, &mc_list->records_list);

	वापस mc_record;

err_kvdl_alloc:
	kमुक्त(mc_record);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_destroy(काष्ठा mlxsw_sp_nve_mc_record *mc_record)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mc_record->mlxsw_sp;

	list_del(&mc_record->list);
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_TNUMT, 1,
			   mc_record->kvdl_index);
	WARN_ON(mc_record->num_entries);
	kमुक्त(mc_record);
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_record *
mlxsw_sp_nve_mc_record_get(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_nve_mc_list *mc_list,
			   क्रमागत mlxsw_sp_l3proto proto)
अणु
	काष्ठा mlxsw_sp_nve_mc_record *mc_record;

	list_क्रम_each_entry_reverse(mc_record, &mc_list->records_list, list) अणु
		अचिन्हित पूर्णांक num_entries = mc_record->num_entries;
		काष्ठा mlxsw_sp_nve *nve = mlxsw_sp->nve;

		अगर (mc_record->proto == proto &&
		    num_entries < nve->num_max_mc_entries[proto])
			वापस mc_record;
	पूर्ण

	वापस mlxsw_sp_nve_mc_record_create(mlxsw_sp, mc_list, proto);
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_put(काष्ठा mlxsw_sp_nve_mc_record *mc_record)
अणु
	अगर (mc_record->num_entries != 0)
		वापस;

	mlxsw_sp_nve_mc_record_destroy(mc_record);
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_entry *
mlxsw_sp_nve_mc_मुक्त_entry_find(काष्ठा mlxsw_sp_nve_mc_record *mc_record)
अणु
	काष्ठा mlxsw_sp_nve *nve = mc_record->mlxsw_sp->nve;
	अचिन्हित पूर्णांक num_max_entries;
	पूर्णांक i;

	num_max_entries = nve->num_max_mc_entries[mc_record->proto];
	क्रम (i = 0; i < num_max_entries; i++) अणु
		अगर (mc_record->entries[i].valid)
			जारी;
		वापस &mc_record->entries[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nve_mc_record_refresh(काष्ठा mlxsw_sp_nve_mc_record *mc_record)
अणु
	क्रमागत mlxsw_reg_tnumt_record_type type = mc_record->ops->type;
	काष्ठा mlxsw_sp_nve_mc_list *mc_list = mc_record->mc_list;
	काष्ठा mlxsw_sp *mlxsw_sp = mc_record->mlxsw_sp;
	अक्षर tnumt_pl[MLXSW_REG_TNUMT_LEN];
	अचिन्हित पूर्णांक num_max_entries;
	अचिन्हित पूर्णांक num_entries = 0;
	u32 next_kvdl_index = 0;
	bool next_valid = false;
	पूर्णांक i;

	अगर (!list_is_last(&mc_record->list, &mc_list->records_list)) अणु
		काष्ठा mlxsw_sp_nve_mc_record *next_record;

		next_record = list_next_entry(mc_record, list);
		next_kvdl_index = next_record->kvdl_index;
		next_valid = true;
	पूर्ण

	mlxsw_reg_tnumt_pack(tnumt_pl, type, MLXSW_REG_TUNNEL_PORT_NVE,
			     mc_record->kvdl_index, next_valid,
			     next_kvdl_index, mc_record->num_entries);

	num_max_entries = mlxsw_sp->nve->num_max_mc_entries[mc_record->proto];
	क्रम (i = 0; i < num_max_entries; i++) अणु
		काष्ठा mlxsw_sp_nve_mc_entry *mc_entry;

		mc_entry = &mc_record->entries[i];
		अगर (!mc_entry->valid)
			जारी;
		mc_record->ops->entry_set(mc_record, mc_entry, tnumt_pl,
					  num_entries++);
	पूर्ण

	WARN_ON(num_entries != mc_record->num_entries);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tnumt), tnumt_pl);
पूर्ण

अटल bool
mlxsw_sp_nve_mc_record_is_first(काष्ठा mlxsw_sp_nve_mc_record *mc_record)
अणु
	काष्ठा mlxsw_sp_nve_mc_list *mc_list = mc_record->mc_list;
	काष्ठा mlxsw_sp_nve_mc_record *first_record;

	first_record = list_first_entry(&mc_list->records_list,
					काष्ठा mlxsw_sp_nve_mc_record, list);

	वापस mc_record == first_record;
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_entry *
mlxsw_sp_nve_mc_entry_find(काष्ठा mlxsw_sp_nve_mc_record *mc_record,
			   जोड़ mlxsw_sp_l3addr *addr)
अणु
	काष्ठा mlxsw_sp_nve *nve = mc_record->mlxsw_sp->nve;
	अचिन्हित पूर्णांक num_max_entries;
	पूर्णांक i;

	num_max_entries = nve->num_max_mc_entries[mc_record->proto];
	क्रम (i = 0; i < num_max_entries; i++) अणु
		काष्ठा mlxsw_sp_nve_mc_entry *mc_entry;

		mc_entry = &mc_record->entries[i];
		अगर (!mc_entry->valid)
			जारी;
		अगर (mc_record->ops->entry_compare(mc_record, mc_entry, addr))
			वापस mc_entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nve_mc_record_ip_add(काष्ठा mlxsw_sp_nve_mc_record *mc_record,
			      जोड़ mlxsw_sp_l3addr *addr)
अणु
	काष्ठा mlxsw_sp_nve_mc_entry *mc_entry = शून्य;
	पूर्णांक err;

	mc_entry = mlxsw_sp_nve_mc_मुक्त_entry_find(mc_record);
	अगर (WARN_ON(!mc_entry))
		वापस -EINVAL;

	err = mc_record->ops->entry_add(mc_record, mc_entry, addr);
	अगर (err)
		वापस err;
	mc_record->num_entries++;
	mc_entry->valid = true;

	err = mlxsw_sp_nve_mc_record_refresh(mc_record);
	अगर (err)
		जाओ err_record_refresh;

	/* If this is a new record and not the first one, then we need to
	 * update the next poपूर्णांकer of the previous entry
	 */
	अगर (mc_record->num_entries != 1 ||
	    mlxsw_sp_nve_mc_record_is_first(mc_record))
		वापस 0;

	err = mlxsw_sp_nve_mc_record_refresh(list_prev_entry(mc_record, list));
	अगर (err)
		जाओ err_prev_record_refresh;

	वापस 0;

err_prev_record_refresh:
err_record_refresh:
	mc_entry->valid = false;
	mc_record->num_entries--;
	mc_record->ops->entry_del(mc_record, mc_entry);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_entry_del(काष्ठा mlxsw_sp_nve_mc_record *mc_record,
				 काष्ठा mlxsw_sp_nve_mc_entry *mc_entry)
अणु
	काष्ठा mlxsw_sp_nve_mc_list *mc_list = mc_record->mc_list;

	mc_entry->valid = false;
	mc_record->num_entries--;

	/* When the record जारीs to exist we only need to invalidate
	 * the requested entry
	 */
	अगर (mc_record->num_entries != 0) अणु
		mlxsw_sp_nve_mc_record_refresh(mc_record);
		mc_record->ops->entry_del(mc_record, mc_entry);
		वापस;
	पूर्ण

	/* If the record needs to be deleted, but it is not the first,
	 * then we need to make sure that the previous record no दीर्घer
	 * poपूर्णांकs to it. Remove deleted record from the list to reflect
	 * that and then re-add it at the end, so that it could be
	 * properly हटाओd by the record deकाष्ठाion code
	 */
	अगर (!mlxsw_sp_nve_mc_record_is_first(mc_record)) अणु
		काष्ठा mlxsw_sp_nve_mc_record *prev_record;

		prev_record = list_prev_entry(mc_record, list);
		list_del(&mc_record->list);
		mlxsw_sp_nve_mc_record_refresh(prev_record);
		list_add_tail(&mc_record->list, &mc_list->records_list);
		mc_record->ops->entry_del(mc_record, mc_entry);
		वापस;
	पूर्ण

	/* If the first record needs to be deleted, but the list is not
	 * singular, then the second record needs to be written in the
	 * first record's address, as this address is stored as a property
	 * of the FID
	 */
	अगर (mlxsw_sp_nve_mc_record_is_first(mc_record) &&
	    !list_is_singular(&mc_list->records_list)) अणु
		काष्ठा mlxsw_sp_nve_mc_record *next_record;

		next_record = list_next_entry(mc_record, list);
		swap(mc_record->kvdl_index, next_record->kvdl_index);
		mlxsw_sp_nve_mc_record_refresh(next_record);
		mc_record->ops->entry_del(mc_record, mc_entry);
		वापस;
	पूर्ण

	/* This is the last हाल where the last reमुख्यing record needs to
	 * be deleted. Simply delete the entry
	 */
	mc_record->ops->entry_del(mc_record, mc_entry);
पूर्ण

अटल काष्ठा mlxsw_sp_nve_mc_record *
mlxsw_sp_nve_mc_record_find(काष्ठा mlxsw_sp_nve_mc_list *mc_list,
			    क्रमागत mlxsw_sp_l3proto proto,
			    जोड़ mlxsw_sp_l3addr *addr,
			    काष्ठा mlxsw_sp_nve_mc_entry **mc_entry)
अणु
	काष्ठा mlxsw_sp_nve_mc_record *mc_record;

	list_क्रम_each_entry(mc_record, &mc_list->records_list, list) अणु
		अगर (mc_record->proto != proto)
			जारी;

		*mc_entry = mlxsw_sp_nve_mc_entry_find(mc_record, addr);
		अगर (*mc_entry)
			वापस mc_record;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_mc_list_ip_add(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_nve_mc_list *mc_list,
				       क्रमागत mlxsw_sp_l3proto proto,
				       जोड़ mlxsw_sp_l3addr *addr)
अणु
	काष्ठा mlxsw_sp_nve_mc_record *mc_record;
	पूर्णांक err;

	mc_record = mlxsw_sp_nve_mc_record_get(mlxsw_sp, mc_list, proto);
	अगर (IS_ERR(mc_record))
		वापस PTR_ERR(mc_record);

	err = mlxsw_sp_nve_mc_record_ip_add(mc_record, addr);
	अगर (err)
		जाओ err_ip_add;

	वापस 0;

err_ip_add:
	mlxsw_sp_nve_mc_record_put(mc_record);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_nve_mc_list_ip_del(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_nve_mc_list *mc_list,
					क्रमागत mlxsw_sp_l3proto proto,
					जोड़ mlxsw_sp_l3addr *addr)
अणु
	काष्ठा mlxsw_sp_nve_mc_record *mc_record;
	काष्ठा mlxsw_sp_nve_mc_entry *mc_entry;

	mc_record = mlxsw_sp_nve_mc_record_find(mc_list, proto, addr,
						&mc_entry);
	अगर (!mc_record)
		वापस;

	mlxsw_sp_nve_mc_record_entry_del(mc_record, mc_entry);
	mlxsw_sp_nve_mc_record_put(mc_record);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nve_fid_flood_index_set(काष्ठा mlxsw_sp_fid *fid,
				 काष्ठा mlxsw_sp_nve_mc_list *mc_list)
अणु
	काष्ठा mlxsw_sp_nve_mc_record *mc_record;

	/* The address of the first record in the list is a property of
	 * the FID and we never change it. It only needs to be set when
	 * a new list is created
	 */
	अगर (mlxsw_sp_fid_nve_flood_index_is_set(fid))
		वापस 0;

	mc_record = list_first_entry(&mc_list->records_list,
				     काष्ठा mlxsw_sp_nve_mc_record, list);

	वापस mlxsw_sp_fid_nve_flood_index_set(fid, mc_record->kvdl_index);
पूर्ण

अटल व्योम
mlxsw_sp_nve_fid_flood_index_clear(काष्ठा mlxsw_sp_fid *fid,
				   काष्ठा mlxsw_sp_nve_mc_list *mc_list)
अणु
	काष्ठा mlxsw_sp_nve_mc_record *mc_record;

	/* The address of the first record needs to be invalidated only when
	 * the last record is about to be हटाओd
	 */
	अगर (!list_is_singular(&mc_list->records_list))
		वापस;

	mc_record = list_first_entry(&mc_list->records_list,
				     काष्ठा mlxsw_sp_nve_mc_record, list);
	अगर (mc_record->num_entries != 1)
		वापस;

	वापस mlxsw_sp_fid_nve_flood_index_clear(fid);
पूर्ण

पूर्णांक mlxsw_sp_nve_flood_ip_add(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_fid *fid,
			      क्रमागत mlxsw_sp_l3proto proto,
			      जोड़ mlxsw_sp_l3addr *addr)
अणु
	काष्ठा mlxsw_sp_nve_mc_list_key key = अणु 0 पूर्ण;
	काष्ठा mlxsw_sp_nve_mc_list *mc_list;
	पूर्णांक err;

	key.fid_index = mlxsw_sp_fid_index(fid);
	mc_list = mlxsw_sp_nve_mc_list_get(mlxsw_sp, &key);
	अगर (IS_ERR(mc_list))
		वापस PTR_ERR(mc_list);

	err = mlxsw_sp_nve_mc_list_ip_add(mlxsw_sp, mc_list, proto, addr);
	अगर (err)
		जाओ err_add_ip;

	err = mlxsw_sp_nve_fid_flood_index_set(fid, mc_list);
	अगर (err)
		जाओ err_fid_flood_index_set;

	वापस 0;

err_fid_flood_index_set:
	mlxsw_sp_nve_mc_list_ip_del(mlxsw_sp, mc_list, proto, addr);
err_add_ip:
	mlxsw_sp_nve_mc_list_put(mlxsw_sp, mc_list);
	वापस err;
पूर्ण

व्योम mlxsw_sp_nve_flood_ip_del(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_fid *fid,
			       क्रमागत mlxsw_sp_l3proto proto,
			       जोड़ mlxsw_sp_l3addr *addr)
अणु
	काष्ठा mlxsw_sp_nve_mc_list_key key = अणु 0 पूर्ण;
	काष्ठा mlxsw_sp_nve_mc_list *mc_list;

	key.fid_index = mlxsw_sp_fid_index(fid);
	mc_list = mlxsw_sp_nve_mc_list_find(mlxsw_sp, &key);
	अगर (!mc_list)
		वापस;

	mlxsw_sp_nve_fid_flood_index_clear(fid, mc_list);
	mlxsw_sp_nve_mc_list_ip_del(mlxsw_sp, mc_list, proto, addr);
	mlxsw_sp_nve_mc_list_put(mlxsw_sp, mc_list);
पूर्ण

अटल व्योम
mlxsw_sp_nve_mc_record_delete(काष्ठा mlxsw_sp_nve_mc_record *mc_record)
अणु
	काष्ठा mlxsw_sp_nve *nve = mc_record->mlxsw_sp->nve;
	अचिन्हित पूर्णांक num_max_entries;
	पूर्णांक i;

	num_max_entries = nve->num_max_mc_entries[mc_record->proto];
	क्रम (i = 0; i < num_max_entries; i++) अणु
		काष्ठा mlxsw_sp_nve_mc_entry *mc_entry = &mc_record->entries[i];

		अगर (!mc_entry->valid)
			जारी;
		mlxsw_sp_nve_mc_record_entry_del(mc_record, mc_entry);
	पूर्ण

	WARN_ON(mc_record->num_entries);
	mlxsw_sp_nve_mc_record_put(mc_record);
पूर्ण

अटल व्योम mlxsw_sp_nve_flood_ip_flush(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fid *fid)
अणु
	काष्ठा mlxsw_sp_nve_mc_record *mc_record, *पंचांगp;
	काष्ठा mlxsw_sp_nve_mc_list_key key = अणु 0 पूर्ण;
	काष्ठा mlxsw_sp_nve_mc_list *mc_list;

	अगर (!mlxsw_sp_fid_nve_flood_index_is_set(fid))
		वापस;

	mlxsw_sp_fid_nve_flood_index_clear(fid);

	key.fid_index = mlxsw_sp_fid_index(fid);
	mc_list = mlxsw_sp_nve_mc_list_find(mlxsw_sp, &key);
	अगर (WARN_ON(!mc_list))
		वापस;

	list_क्रम_each_entry_safe(mc_record, पंचांगp, &mc_list->records_list, list)
		mlxsw_sp_nve_mc_record_delete(mc_record);

	WARN_ON(!list_empty(&mc_list->records_list));
	mlxsw_sp_nve_mc_list_put(mlxsw_sp, mc_list);
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_tunnel_init(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_nve_config *config)
अणु
	काष्ठा mlxsw_sp_nve *nve = mlxsw_sp->nve;
	स्थिर काष्ठा mlxsw_sp_nve_ops *ops;
	पूर्णांक err;

	अगर (nve->num_nve_tunnels++ != 0)
		वापस 0;

	nve->config = *config;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
				  &nve->tunnel_index);
	अगर (err)
		जाओ err_kvdl_alloc;

	ops = nve->nve_ops_arr[config->type];
	err = ops->init(nve, config);
	अगर (err)
		जाओ err_ops_init;

	वापस 0;

err_ops_init:
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
			   nve->tunnel_index);
err_kvdl_alloc:
	स_रखो(&nve->config, 0, माप(nve->config));
	nve->num_nve_tunnels--;
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_nve_tunnel_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_nve *nve = mlxsw_sp->nve;
	स्थिर काष्ठा mlxsw_sp_nve_ops *ops;

	ops = nve->nve_ops_arr[nve->config.type];

	अगर (mlxsw_sp->nve->num_nve_tunnels == 1) अणु
		ops->fini(nve);
		mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
				   nve->tunnel_index);
		स_रखो(&nve->config, 0, माप(nve->config));
	पूर्ण
	nve->num_nve_tunnels--;
पूर्ण

अटल व्योम mlxsw_sp_nve_fdb_flush_by_fid(काष्ठा mlxsw_sp *mlxsw_sp,
					  u16 fid_index)
अणु
	अक्षर sfdf_pl[MLXSW_REG_SFDF_LEN];

	mlxsw_reg_sfdf_pack(sfdf_pl, MLXSW_REG_SFDF_FLUSH_PER_NVE_AND_FID);
	mlxsw_reg_sfdf_fid_set(sfdf_pl, fid_index);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfdf), sfdf_pl);
पूर्ण

अटल व्योम mlxsw_sp_nve_fdb_clear_offload(काष्ठा mlxsw_sp *mlxsw_sp,
					   स्थिर काष्ठा mlxsw_sp_fid *fid,
					   स्थिर काष्ठा net_device *nve_dev,
					   __be32 vni)
अणु
	स्थिर काष्ठा mlxsw_sp_nve_ops *ops;
	क्रमागत mlxsw_sp_nve_type type;

	अगर (WARN_ON(mlxsw_sp_fid_nve_type(fid, &type)))
		वापस;

	ops = mlxsw_sp->nve->nve_ops_arr[type];
	ops->fdb_clear_offload(nve_dev, vni);
पूर्ण

पूर्णांक mlxsw_sp_nve_fid_enable(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा mlxsw_sp_fid *fid,
			    काष्ठा mlxsw_sp_nve_params *params,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_nve *nve = mlxsw_sp->nve;
	स्थिर काष्ठा mlxsw_sp_nve_ops *ops;
	काष्ठा mlxsw_sp_nve_config config;
	पूर्णांक err;

	ops = nve->nve_ops_arr[params->type];

	अगर (!ops->can_offload(nve, params, extack))
		वापस -EINVAL;

	स_रखो(&config, 0, माप(config));
	ops->nve_config(nve, params, &config);
	अगर (nve->num_nve_tunnels &&
	    स_भेद(&config, &nve->config, माप(config))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Conflicting NVE tunnels configuration");
		वापस -EINVAL;
	पूर्ण

	err = mlxsw_sp_nve_tunnel_init(mlxsw_sp, &config);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to initialize NVE tunnel");
		वापस err;
	पूर्ण

	err = mlxsw_sp_fid_vni_set(fid, params->type, params->vni,
				   params->dev->अगरindex);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to set VNI on FID");
		जाओ err_fid_vni_set;
	पूर्ण

	err = ops->fdb_replay(params->dev, params->vni, extack);
	अगर (err)
		जाओ err_fdb_replay;

	वापस 0;

err_fdb_replay:
	mlxsw_sp_fid_vni_clear(fid);
err_fid_vni_set:
	mlxsw_sp_nve_tunnel_fini(mlxsw_sp);
	वापस err;
पूर्ण

व्योम mlxsw_sp_nve_fid_disable(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_fid *fid)
अणु
	u16 fid_index = mlxsw_sp_fid_index(fid);
	काष्ठा net_device *nve_dev;
	पूर्णांक nve_अगरindex;
	__be32 vni;

	mlxsw_sp_nve_flood_ip_flush(mlxsw_sp, fid);
	mlxsw_sp_nve_fdb_flush_by_fid(mlxsw_sp, fid_index);

	अगर (WARN_ON(mlxsw_sp_fid_nve_अगरindex(fid, &nve_अगरindex) ||
		    mlxsw_sp_fid_vni(fid, &vni)))
		जाओ out;

	nve_dev = dev_get_by_index(mlxsw_sp_net(mlxsw_sp), nve_अगरindex);
	अगर (!nve_dev)
		जाओ out;

	mlxsw_sp_nve_fdb_clear_offload(mlxsw_sp, fid, nve_dev, vni);
	mlxsw_sp_fid_fdb_clear_offload(fid, nve_dev);

	dev_put(nve_dev);

out:
	mlxsw_sp_fid_vni_clear(fid);
	mlxsw_sp_nve_tunnel_fini(mlxsw_sp);
पूर्ण

पूर्णांक mlxsw_sp_port_nve_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर tnqdr_pl[MLXSW_REG_TNQDR_LEN];

	mlxsw_reg_tnqdr_pack(tnqdr_pl, mlxsw_sp_port->local_port);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tnqdr), tnqdr_pl);
पूर्ण

व्योम mlxsw_sp_port_nve_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_qos_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर tnqcr_pl[MLXSW_REG_TNQCR_LEN];

	mlxsw_reg_tnqcr_pack(tnqcr_pl);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tnqcr), tnqcr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_ecn_encap_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i;

	/* Iterate over inner ECN values */
	क्रम (i = INET_ECN_NOT_ECT; i <= INET_ECN_CE; i++) अणु
		u8 outer_ecn = INET_ECN_encapsulate(0, i);
		अक्षर tneem_pl[MLXSW_REG_TNEEM_LEN];
		पूर्णांक err;

		mlxsw_reg_tneem_pack(tneem_pl, i, outer_ecn);
		err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tneem),
				      tneem_pl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mlxsw_sp_nve_ecn_decap_init(काष्ठा mlxsw_sp *mlxsw_sp,
					 u8 inner_ecn, u8 outer_ecn)
अणु
	अक्षर tndem_pl[MLXSW_REG_TNDEM_LEN];
	u8 new_inner_ecn;
	bool trap_en;

	new_inner_ecn = mlxsw_sp_tunnel_ecn_decap(outer_ecn, inner_ecn,
						  &trap_en);
	mlxsw_reg_tndem_pack(tndem_pl, outer_ecn, inner_ecn, new_inner_ecn,
			     trap_en, trap_en ? MLXSW_TRAP_ID_DECAP_ECN0 : 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tndem), tndem_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_ecn_decap_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i;

	/* Iterate over inner ECN values */
	क्रम (i = INET_ECN_NOT_ECT; i <= INET_ECN_CE; i++) अणु
		पूर्णांक j;

		/* Iterate over outer ECN values */
		क्रम (j = INET_ECN_NOT_ECT; j <= INET_ECN_CE; j++) अणु
			पूर्णांक err;

			err = __mlxsw_sp_nve_ecn_decap_init(mlxsw_sp, i, j);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_ecn_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक err;

	err = mlxsw_sp_nve_ecn_encap_init(mlxsw_sp);
	अगर (err)
		वापस err;

	वापस mlxsw_sp_nve_ecn_decap_init(mlxsw_sp);
पूर्ण

अटल पूर्णांक mlxsw_sp_nve_resources_query(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित पूर्णांक max;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_NVE_MC_ENTRIES_IPV4) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_NVE_MC_ENTRIES_IPV6))
		वापस -EIO;
	max = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_NVE_MC_ENTRIES_IPV4);
	mlxsw_sp->nve->num_max_mc_entries[MLXSW_SP_L3_PROTO_IPV4] = max;
	max = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_NVE_MC_ENTRIES_IPV6);
	mlxsw_sp->nve->num_max_mc_entries[MLXSW_SP_L3_PROTO_IPV6] = max;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_nve_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_nve *nve;
	पूर्णांक err;

	nve = kzalloc(माप(*mlxsw_sp->nve), GFP_KERNEL);
	अगर (!nve)
		वापस -ENOMEM;
	mlxsw_sp->nve = nve;
	nve->mlxsw_sp = mlxsw_sp;
	nve->nve_ops_arr = mlxsw_sp->nve_ops_arr;

	err = rhashtable_init(&nve->mc_list_ht,
			      &mlxsw_sp_nve_mc_list_ht_params);
	अगर (err)
		जाओ err_rhashtable_init;

	err = mlxsw_sp_nve_qos_init(mlxsw_sp);
	अगर (err)
		जाओ err_nve_qos_init;

	err = mlxsw_sp_nve_ecn_init(mlxsw_sp);
	अगर (err)
		जाओ err_nve_ecn_init;

	err = mlxsw_sp_nve_resources_query(mlxsw_sp);
	अगर (err)
		जाओ err_nve_resources_query;

	वापस 0;

err_nve_resources_query:
err_nve_ecn_init:
err_nve_qos_init:
	rhashtable_destroy(&nve->mc_list_ht);
err_rhashtable_init:
	mlxsw_sp->nve = शून्य;
	kमुक्त(nve);
	वापस err;
पूर्ण

व्योम mlxsw_sp_nve_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	WARN_ON(mlxsw_sp->nve->num_nve_tunnels);
	rhashtable_destroy(&mlxsw_sp->nve->mc_list_ht);
	kमुक्त(mlxsw_sp->nve);
	mlxsw_sp->nve = शून्य;
पूर्ण
