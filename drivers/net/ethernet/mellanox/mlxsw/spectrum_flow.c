<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2020 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <net/net_namespace.h>

#समावेश "spectrum.h"

काष्ठा mlxsw_sp_flow_block *
mlxsw_sp_flow_block_create(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा net *net)
अणु
	काष्ठा mlxsw_sp_flow_block *block;

	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (!block)
		वापस शून्य;
	INIT_LIST_HEAD(&block->binding_list);
	INIT_LIST_HEAD(&block->mall.list);
	block->mlxsw_sp = mlxsw_sp;
	block->net = net;
	वापस block;
पूर्ण

व्योम mlxsw_sp_flow_block_destroy(काष्ठा mlxsw_sp_flow_block *block)
अणु
	WARN_ON(!list_empty(&block->binding_list));
	kमुक्त(block);
पूर्ण

अटल काष्ठा mlxsw_sp_flow_block_binding *
mlxsw_sp_flow_block_lookup(काष्ठा mlxsw_sp_flow_block *block,
			   काष्ठा mlxsw_sp_port *mlxsw_sp_port, bool ingress)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;

	list_क्रम_each_entry(binding, &block->binding_list, list)
		अगर (binding->mlxsw_sp_port == mlxsw_sp_port &&
		    binding->ingress == ingress)
			वापस binding;
	वापस शून्य;
पूर्ण

अटल bool
mlxsw_sp_flow_block_ruleset_bound(स्थिर काष्ठा mlxsw_sp_flow_block *block)
अणु
	वापस block->ruleset_zero;
पूर्ण

अटल पूर्णांक mlxsw_sp_flow_block_bind(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_flow_block *block,
				    काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    bool ingress,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;
	पूर्णांक err;

	अगर (WARN_ON(mlxsw_sp_flow_block_lookup(block, mlxsw_sp_port, ingress)))
		वापस -EEXIST;

	अगर (ingress && block->ingress_blocker_rule_count) अणु
		NL_SET_ERR_MSG_MOD(extack, "Block cannot be bound to ingress because it contains unsupported rules");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!ingress && block->egress_blocker_rule_count) अणु
		NL_SET_ERR_MSG_MOD(extack, "Block cannot be bound to egress because it contains unsupported rules");
		वापस -EOPNOTSUPP;
	पूर्ण

	err = mlxsw_sp_mall_port_bind(block, mlxsw_sp_port, extack);
	अगर (err)
		वापस err;

	binding = kzalloc(माप(*binding), GFP_KERNEL);
	अगर (!binding) अणु
		err = -ENOMEM;
		जाओ err_binding_alloc;
	पूर्ण
	binding->mlxsw_sp_port = mlxsw_sp_port;
	binding->ingress = ingress;

	अगर (mlxsw_sp_flow_block_ruleset_bound(block)) अणु
		err = mlxsw_sp_acl_ruleset_bind(mlxsw_sp, block, binding);
		अगर (err)
			जाओ err_ruleset_bind;
	पूर्ण

	अगर (ingress)
		block->ingress_binding_count++;
	अन्यथा
		block->egress_binding_count++;
	list_add(&binding->list, &block->binding_list);
	वापस 0;

err_ruleset_bind:
	kमुक्त(binding);
err_binding_alloc:
	mlxsw_sp_mall_port_unbind(block, mlxsw_sp_port);

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_flow_block_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_flow_block *block,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      bool ingress)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;

	binding = mlxsw_sp_flow_block_lookup(block, mlxsw_sp_port, ingress);
	अगर (!binding)
		वापस -ENOENT;

	list_del(&binding->list);

	अगर (ingress)
		block->ingress_binding_count--;
	अन्यथा
		block->egress_binding_count--;

	अगर (mlxsw_sp_flow_block_ruleset_bound(block))
		mlxsw_sp_acl_ruleset_unbind(mlxsw_sp, block, binding);

	kमुक्त(binding);

	mlxsw_sp_mall_port_unbind(block, mlxsw_sp_port);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_flow_block_mall_cb(काष्ठा mlxsw_sp_flow_block *flow_block,
				       काष्ठा tc_cls_matchall_offload *f)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_flow_block_mlxsw_sp(flow_block);

	चयन (f->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस mlxsw_sp_mall_replace(mlxsw_sp, flow_block, f);
	हाल TC_CLSMATCHALL_DESTROY:
		mlxsw_sp_mall_destroy(flow_block, f);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_flow_block_flower_cb(काष्ठा mlxsw_sp_flow_block *flow_block,
					 काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_flow_block_mlxsw_sp(flow_block);

	चयन (f->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस mlxsw_sp_flower_replace(mlxsw_sp, flow_block, f);
	हाल FLOW_CLS_DESTROY:
		mlxsw_sp_flower_destroy(mlxsw_sp, flow_block, f);
		वापस 0;
	हाल FLOW_CLS_STATS:
		वापस mlxsw_sp_flower_stats(mlxsw_sp, flow_block, f);
	हाल FLOW_CLS_TMPLT_CREATE:
		वापस mlxsw_sp_flower_पंचांगplt_create(mlxsw_sp, flow_block, f);
	हाल FLOW_CLS_TMPLT_DESTROY:
		mlxsw_sp_flower_पंचांगplt_destroy(mlxsw_sp, flow_block, f);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_flow_block_cb(क्रमागत tc_setup_type type,
				  व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा mlxsw_sp_flow_block *flow_block = cb_priv;

	अगर (mlxsw_sp_flow_block_disabled(flow_block))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSMATCHALL:
		वापस mlxsw_sp_flow_block_mall_cb(flow_block, type_data);
	हाल TC_SETUP_CLSFLOWER:
		वापस mlxsw_sp_flow_block_flower_cb(flow_block, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_tc_block_release(व्योम *cb_priv)
अणु
	काष्ठा mlxsw_sp_flow_block *flow_block = cb_priv;

	mlxsw_sp_flow_block_destroy(flow_block);
पूर्ण

अटल LIST_HEAD(mlxsw_sp_block_cb_list);

अटल पूर्णांक mlxsw_sp_setup_tc_block_bind(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					काष्ठा flow_block_offload *f,
					bool ingress)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_flow_block *flow_block;
	काष्ठा flow_block_cb *block_cb;
	bool रेजिस्टर_block = false;
	पूर्णांक err;

	block_cb = flow_block_cb_lookup(f->block, mlxsw_sp_flow_block_cb,
					mlxsw_sp);
	अगर (!block_cb) अणु
		flow_block = mlxsw_sp_flow_block_create(mlxsw_sp, f->net);
		अगर (!flow_block)
			वापस -ENOMEM;
		block_cb = flow_block_cb_alloc(mlxsw_sp_flow_block_cb,
					       mlxsw_sp, flow_block,
					       mlxsw_sp_tc_block_release);
		अगर (IS_ERR(block_cb)) अणु
			mlxsw_sp_flow_block_destroy(flow_block);
			वापस PTR_ERR(block_cb);
		पूर्ण
		रेजिस्टर_block = true;
	पूर्ण अन्यथा अणु
		flow_block = flow_block_cb_priv(block_cb);
	पूर्ण
	flow_block_cb_incref(block_cb);
	err = mlxsw_sp_flow_block_bind(mlxsw_sp, flow_block,
				       mlxsw_sp_port, ingress, f->extack);
	अगर (err)
		जाओ err_block_bind;

	अगर (ingress)
		mlxsw_sp_port->ing_flow_block = flow_block;
	अन्यथा
		mlxsw_sp_port->eg_flow_block = flow_block;

	अगर (रेजिस्टर_block) अणु
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &mlxsw_sp_block_cb_list);
	पूर्ण

	वापस 0;

err_block_bind:
	अगर (!flow_block_cb_decref(block_cb))
		flow_block_cb_मुक्त(block_cb);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_setup_tc_block_unbind(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					   काष्ठा flow_block_offload *f,
					   bool ingress)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_flow_block *flow_block;
	काष्ठा flow_block_cb *block_cb;
	पूर्णांक err;

	block_cb = flow_block_cb_lookup(f->block, mlxsw_sp_flow_block_cb,
					mlxsw_sp);
	अगर (!block_cb)
		वापस;

	अगर (ingress)
		mlxsw_sp_port->ing_flow_block = शून्य;
	अन्यथा
		mlxsw_sp_port->eg_flow_block = शून्य;

	flow_block = flow_block_cb_priv(block_cb);
	err = mlxsw_sp_flow_block_unbind(mlxsw_sp, flow_block,
					 mlxsw_sp_port, ingress);
	अगर (!err && !flow_block_cb_decref(block_cb)) अणु
		flow_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_setup_tc_block_clsact(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा flow_block_offload *f,
				   bool ingress)
अणु
	f->driver_block_list = &mlxsw_sp_block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		वापस mlxsw_sp_setup_tc_block_bind(mlxsw_sp_port, f, ingress);
	हाल FLOW_BLOCK_UNBIND:
		mlxsw_sp_setup_tc_block_unbind(mlxsw_sp_port, f, ingress);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
