<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/parman.h>

#समावेश "reg.h"
#समावेश "spectrum.h"
#समावेश "core_acl_flex_actions.h"
#समावेश "spectrum_mr.h"

काष्ठा mlxsw_sp1_mr_tcam_region अणु
	काष्ठा mlxsw_sp *mlxsw_sp;
	क्रमागत mlxsw_reg_rtar_key_type rtar_key_type;
	काष्ठा parman *parman;
	काष्ठा parman_prio *parman_prios;
पूर्ण;

काष्ठा mlxsw_sp1_mr_tcam अणु
	काष्ठा mlxsw_sp1_mr_tcam_region tcam_regions[MLXSW_SP_L3_PROTO_MAX];
पूर्ण;

काष्ठा mlxsw_sp1_mr_tcam_route अणु
	काष्ठा parman_item parman_item;
	काष्ठा parman_prio *parman_prio;
पूर्ण;

अटल पूर्णांक mlxsw_sp1_mr_tcam_route_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा parman_item *parman_item,
					   काष्ठा mlxsw_sp_mr_route_key *key,
					   काष्ठा mlxsw_afa_block *afa_block)
अणु
	अक्षर rmft2_pl[MLXSW_REG_RMFT2_LEN];

	चयन (key->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_reg_rmft2_ipv4_pack(rmft2_pl, true, parman_item->index,
					  key->vrid,
					  MLXSW_REG_RMFT2_IRIF_MASK_IGNORE, 0,
					  ntohl(key->group.addr4),
					  ntohl(key->group_mask.addr4),
					  ntohl(key->source.addr4),
					  ntohl(key->source_mask.addr4),
					  mlxsw_afa_block_first_set(afa_block));
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_reg_rmft2_ipv6_pack(rmft2_pl, true, parman_item->index,
					  key->vrid,
					  MLXSW_REG_RMFT2_IRIF_MASK_IGNORE, 0,
					  key->group.addr6,
					  key->group_mask.addr6,
					  key->source.addr6,
					  key->source_mask.addr6,
					  mlxsw_afa_block_first_set(afa_block));
	पूर्ण

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rmft2), rmft2_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_mr_tcam_route_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा parman_item *parman_item,
					  काष्ठा mlxsw_sp_mr_route_key *key)
अणु
	काष्ठा in6_addr zero_addr = IN6ADDR_ANY_INIT;
	अक्षर rmft2_pl[MLXSW_REG_RMFT2_LEN];

	चयन (key->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_reg_rmft2_ipv4_pack(rmft2_pl, false, parman_item->index,
					  key->vrid, 0, 0, 0, 0, 0, 0, शून्य);
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_reg_rmft2_ipv6_pack(rmft2_pl, false, parman_item->index,
					  key->vrid, 0, 0, zero_addr, zero_addr,
					  zero_addr, zero_addr, शून्य);
		अवरोध;
	पूर्ण

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rmft2), rmft2_pl);
पूर्ण

अटल काष्ठा mlxsw_sp1_mr_tcam_region *
mlxsw_sp1_mr_tcam_protocol_region(काष्ठा mlxsw_sp1_mr_tcam *mr_tcam,
				  क्रमागत mlxsw_sp_l3proto proto)
अणु
	वापस &mr_tcam->tcam_regions[proto];
पूर्ण

अटल पूर्णांक
mlxsw_sp1_mr_tcam_route_parman_item_add(काष्ठा mlxsw_sp1_mr_tcam *mr_tcam,
					काष्ठा mlxsw_sp1_mr_tcam_route *route,
					काष्ठा mlxsw_sp_mr_route_key *key,
					क्रमागत mlxsw_sp_mr_route_prio prio)
अणु
	काष्ठा mlxsw_sp1_mr_tcam_region *tcam_region;
	पूर्णांक err;

	tcam_region = mlxsw_sp1_mr_tcam_protocol_region(mr_tcam, key->proto);
	err = parman_item_add(tcam_region->parman,
			      &tcam_region->parman_prios[prio],
			      &route->parman_item);
	अगर (err)
		वापस err;

	route->parman_prio = &tcam_region->parman_prios[prio];
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp1_mr_tcam_route_parman_item_हटाओ(काष्ठा mlxsw_sp1_mr_tcam *mr_tcam,
					   काष्ठा mlxsw_sp1_mr_tcam_route *route,
					   काष्ठा mlxsw_sp_mr_route_key *key)
अणु
	काष्ठा mlxsw_sp1_mr_tcam_region *tcam_region;

	tcam_region = mlxsw_sp1_mr_tcam_protocol_region(mr_tcam, key->proto);
	parman_item_हटाओ(tcam_region->parman,
			   route->parman_prio, &route->parman_item);
पूर्ण

अटल पूर्णांक
mlxsw_sp1_mr_tcam_route_create(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
			       व्योम *route_priv,
			       काष्ठा mlxsw_sp_mr_route_key *key,
			       काष्ठा mlxsw_afa_block *afa_block,
			       क्रमागत mlxsw_sp_mr_route_prio prio)
अणु
	काष्ठा mlxsw_sp1_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_sp1_mr_tcam *mr_tcam = priv;
	पूर्णांक err;

	err = mlxsw_sp1_mr_tcam_route_parman_item_add(mr_tcam, route,
						      key, prio);
	अगर (err)
		वापस err;

	err = mlxsw_sp1_mr_tcam_route_replace(mlxsw_sp, &route->parman_item,
					      key, afa_block);
	अगर (err)
		जाओ err_route_replace;
	वापस 0;

err_route_replace:
	mlxsw_sp1_mr_tcam_route_parman_item_हटाओ(mr_tcam, route, key);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp1_mr_tcam_route_destroy(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				व्योम *route_priv,
				काष्ठा mlxsw_sp_mr_route_key *key)
अणु
	काष्ठा mlxsw_sp1_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_sp1_mr_tcam *mr_tcam = priv;

	mlxsw_sp1_mr_tcam_route_हटाओ(mlxsw_sp, &route->parman_item, key);
	mlxsw_sp1_mr_tcam_route_parman_item_हटाओ(mr_tcam, route, key);
पूर्ण

अटल पूर्णांक
mlxsw_sp1_mr_tcam_route_update(काष्ठा mlxsw_sp *mlxsw_sp,
			       व्योम *route_priv,
			       काष्ठा mlxsw_sp_mr_route_key *key,
			       काष्ठा mlxsw_afa_block *afa_block)
अणु
	काष्ठा mlxsw_sp1_mr_tcam_route *route = route_priv;

	वापस mlxsw_sp1_mr_tcam_route_replace(mlxsw_sp, &route->parman_item,
					       key, afa_block);
पूर्ण

#घोषणा MLXSW_SP1_MR_TCAM_REGION_BASE_COUNT 16
#घोषणा MLXSW_SP1_MR_TCAM_REGION_RESIZE_STEP 16

अटल पूर्णांक
mlxsw_sp1_mr_tcam_region_alloc(काष्ठा mlxsw_sp1_mr_tcam_region *mr_tcam_region)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_tcam_region->mlxsw_sp;
	अक्षर rtar_pl[MLXSW_REG_RTAR_LEN];

	mlxsw_reg_rtar_pack(rtar_pl, MLXSW_REG_RTAR_OP_ALLOCATE,
			    mr_tcam_region->rtar_key_type,
			    MLXSW_SP1_MR_TCAM_REGION_BASE_COUNT);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rtar), rtar_pl);
पूर्ण

अटल व्योम
mlxsw_sp1_mr_tcam_region_मुक्त(काष्ठा mlxsw_sp1_mr_tcam_region *mr_tcam_region)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_tcam_region->mlxsw_sp;
	अक्षर rtar_pl[MLXSW_REG_RTAR_LEN];

	mlxsw_reg_rtar_pack(rtar_pl, MLXSW_REG_RTAR_OP_DEALLOCATE,
			    mr_tcam_region->rtar_key_type, 0);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rtar), rtar_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_mr_tcam_region_parman_resize(व्योम *priv,
						  अचिन्हित दीर्घ new_count)
अणु
	काष्ठा mlxsw_sp1_mr_tcam_region *mr_tcam_region = priv;
	काष्ठा mlxsw_sp *mlxsw_sp = mr_tcam_region->mlxsw_sp;
	अक्षर rtar_pl[MLXSW_REG_RTAR_LEN];
	u64 max_tcam_rules;

	max_tcam_rules = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_TCAM_RULES);
	अगर (new_count > max_tcam_rules)
		वापस -EINVAL;
	mlxsw_reg_rtar_pack(rtar_pl, MLXSW_REG_RTAR_OP_RESIZE,
			    mr_tcam_region->rtar_key_type, new_count);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rtar), rtar_pl);
पूर्ण

अटल व्योम mlxsw_sp1_mr_tcam_region_parman_move(व्योम *priv,
						 अचिन्हित दीर्घ from_index,
						 अचिन्हित दीर्घ to_index,
						 अचिन्हित दीर्घ count)
अणु
	काष्ठा mlxsw_sp1_mr_tcam_region *mr_tcam_region = priv;
	काष्ठा mlxsw_sp *mlxsw_sp = mr_tcam_region->mlxsw_sp;
	अक्षर rrcr_pl[MLXSW_REG_RRCR_LEN];

	mlxsw_reg_rrcr_pack(rrcr_pl, MLXSW_REG_RRCR_OP_MOVE,
			    from_index, count,
			    mr_tcam_region->rtar_key_type, to_index);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rrcr), rrcr_pl);
पूर्ण

अटल स्थिर काष्ठा parman_ops mlxsw_sp1_mr_tcam_region_parman_ops = अणु
	.base_count	= MLXSW_SP1_MR_TCAM_REGION_BASE_COUNT,
	.resize_step	= MLXSW_SP1_MR_TCAM_REGION_RESIZE_STEP,
	.resize		= mlxsw_sp1_mr_tcam_region_parman_resize,
	.move		= mlxsw_sp1_mr_tcam_region_parman_move,
	.algo		= PARMAN_ALGO_TYPE_LSORT,
पूर्ण;

अटल पूर्णांक
mlxsw_sp1_mr_tcam_region_init(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp1_mr_tcam_region *mr_tcam_region,
			      क्रमागत mlxsw_reg_rtar_key_type rtar_key_type)
अणु
	काष्ठा parman_prio *parman_prios;
	काष्ठा parman *parman;
	पूर्णांक err;
	पूर्णांक i;

	mr_tcam_region->rtar_key_type = rtar_key_type;
	mr_tcam_region->mlxsw_sp = mlxsw_sp;

	err = mlxsw_sp1_mr_tcam_region_alloc(mr_tcam_region);
	अगर (err)
		वापस err;

	parman = parman_create(&mlxsw_sp1_mr_tcam_region_parman_ops,
			       mr_tcam_region);
	अगर (!parman) अणु
		err = -ENOMEM;
		जाओ err_parman_create;
	पूर्ण
	mr_tcam_region->parman = parman;

	parman_prios = kदो_स्मृति_array(MLXSW_SP_MR_ROUTE_PRIO_MAX + 1,
				     माप(*parman_prios), GFP_KERNEL);
	अगर (!parman_prios) अणु
		err = -ENOMEM;
		जाओ err_parman_prios_alloc;
	पूर्ण
	mr_tcam_region->parman_prios = parman_prios;

	क्रम (i = 0; i < MLXSW_SP_MR_ROUTE_PRIO_MAX + 1; i++)
		parman_prio_init(mr_tcam_region->parman,
				 &mr_tcam_region->parman_prios[i], i);
	वापस 0;

err_parman_prios_alloc:
	parman_destroy(parman);
err_parman_create:
	mlxsw_sp1_mr_tcam_region_मुक्त(mr_tcam_region);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp1_mr_tcam_region_fini(काष्ठा mlxsw_sp1_mr_tcam_region *mr_tcam_region)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP_MR_ROUTE_PRIO_MAX + 1; i++)
		parman_prio_fini(&mr_tcam_region->parman_prios[i]);
	kमुक्त(mr_tcam_region->parman_prios);
	parman_destroy(mr_tcam_region->parman);
	mlxsw_sp1_mr_tcam_region_मुक्त(mr_tcam_region);
पूर्ण

अटल पूर्णांक mlxsw_sp1_mr_tcam_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	काष्ठा mlxsw_sp1_mr_tcam *mr_tcam = priv;
	काष्ठा mlxsw_sp1_mr_tcam_region *region = &mr_tcam->tcam_regions[0];
	u32 rtar_key;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_TCAM_RULES))
		वापस -EIO;

	rtar_key = MLXSW_REG_RTAR_KEY_TYPE_IPV4_MULTICAST;
	err = mlxsw_sp1_mr_tcam_region_init(mlxsw_sp,
					    &region[MLXSW_SP_L3_PROTO_IPV4],
					    rtar_key);
	अगर (err)
		वापस err;

	rtar_key = MLXSW_REG_RTAR_KEY_TYPE_IPV6_MULTICAST;
	err = mlxsw_sp1_mr_tcam_region_init(mlxsw_sp,
					    &region[MLXSW_SP_L3_PROTO_IPV6],
					    rtar_key);
	अगर (err)
		जाओ err_ipv6_region_init;

	वापस 0;

err_ipv6_region_init:
	mlxsw_sp1_mr_tcam_region_fini(&region[MLXSW_SP_L3_PROTO_IPV4]);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp1_mr_tcam_fini(व्योम *priv)
अणु
	काष्ठा mlxsw_sp1_mr_tcam *mr_tcam = priv;
	काष्ठा mlxsw_sp1_mr_tcam_region *region = &mr_tcam->tcam_regions[0];

	mlxsw_sp1_mr_tcam_region_fini(&region[MLXSW_SP_L3_PROTO_IPV6]);
	mlxsw_sp1_mr_tcam_region_fini(&region[MLXSW_SP_L3_PROTO_IPV4]);
पूर्ण

स्थिर काष्ठा mlxsw_sp_mr_tcam_ops mlxsw_sp1_mr_tcam_ops = अणु
	.priv_size = माप(काष्ठा mlxsw_sp1_mr_tcam),
	.init = mlxsw_sp1_mr_tcam_init,
	.fini = mlxsw_sp1_mr_tcam_fini,
	.route_priv_size = माप(काष्ठा mlxsw_sp1_mr_tcam_route),
	.route_create = mlxsw_sp1_mr_tcam_route_create,
	.route_destroy = mlxsw_sp1_mr_tcam_route_destroy,
	.route_update = mlxsw_sp1_mr_tcam_route_update,
पूर्ण;
