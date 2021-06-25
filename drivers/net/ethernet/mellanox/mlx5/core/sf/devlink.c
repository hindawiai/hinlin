<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#समावेश <linux/mlx5/driver.h>
#समावेश "eswitch.h"
#समावेश "priv.h"
#समावेश "sf/dev/dev.h"
#समावेश "mlx5_ifc_vhca_event.h"
#समावेश "vhca_event.h"
#समावेश "ecpf.h"

काष्ठा mlx5_sf अणु
	काष्ठा devlink_port dl_port;
	अचिन्हित पूर्णांक port_index;
	u32 controller;
	u16 id;
	u16 hw_fn_id;
	u16 hw_state;
पूर्ण;

काष्ठा mlx5_sf_table अणु
	काष्ठा mlx5_core_dev *dev; /* To refer from notअगरier context. */
	काष्ठा xarray port_indices; /* port index based lookup. */
	refcount_t refcount;
	काष्ठा completion disable_complete;
	काष्ठा mutex sf_state_lock; /* Serializes sf state among user cmds & vhca event handler. */
	काष्ठा notअगरier_block esw_nb;
	काष्ठा notअगरier_block vhca_nb;
	u8 ecpu: 1;
पूर्ण;

अटल काष्ठा mlx5_sf *
mlx5_sf_lookup_by_index(काष्ठा mlx5_sf_table *table, अचिन्हित पूर्णांक port_index)
अणु
	वापस xa_load(&table->port_indices, port_index);
पूर्ण

अटल काष्ठा mlx5_sf *
mlx5_sf_lookup_by_function_id(काष्ठा mlx5_sf_table *table, अचिन्हित पूर्णांक fn_id)
अणु
	अचिन्हित दीर्घ index;
	काष्ठा mlx5_sf *sf;

	xa_क्रम_each(&table->port_indices, index, sf) अणु
		अगर (sf->hw_fn_id == fn_id)
			वापस sf;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlx5_sf_id_insert(काष्ठा mlx5_sf_table *table, काष्ठा mlx5_sf *sf)
अणु
	वापस xa_insert(&table->port_indices, sf->port_index, sf, GFP_KERNEL);
पूर्ण

अटल व्योम mlx5_sf_id_erase(काष्ठा mlx5_sf_table *table, काष्ठा mlx5_sf *sf)
अणु
	xa_erase(&table->port_indices, sf->port_index);
पूर्ण

अटल काष्ठा mlx5_sf *
mlx5_sf_alloc(काष्ठा mlx5_sf_table *table, काष्ठा mlx5_eचयन *esw,
	      u32 controller, u32 sfnum, काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक dl_port_index;
	काष्ठा mlx5_sf *sf;
	u16 hw_fn_id;
	पूर्णांक id_err;
	पूर्णांक err;

	अगर (!mlx5_esw_offloads_controller_valid(esw, controller)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid controller number");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	id_err = mlx5_sf_hw_table_sf_alloc(table->dev, controller, sfnum);
	अगर (id_err < 0) अणु
		err = id_err;
		जाओ id_err;
	पूर्ण

	sf = kzalloc(माप(*sf), GFP_KERNEL);
	अगर (!sf) अणु
		err = -ENOMEM;
		जाओ alloc_err;
	पूर्ण
	sf->id = id_err;
	hw_fn_id = mlx5_sf_sw_to_hw_id(table->dev, controller, sf->id);
	dl_port_index = mlx5_esw_vport_to_devlink_port_index(table->dev, hw_fn_id);
	sf->port_index = dl_port_index;
	sf->hw_fn_id = hw_fn_id;
	sf->hw_state = MLX5_VHCA_STATE_ALLOCATED;
	sf->controller = controller;

	err = mlx5_sf_id_insert(table, sf);
	अगर (err)
		जाओ insert_err;

	वापस sf;

insert_err:
	kमुक्त(sf);
alloc_err:
	mlx5_sf_hw_table_sf_मुक्त(table->dev, controller, id_err);
id_err:
	अगर (err == -EEXIST)
		NL_SET_ERR_MSG_MOD(extack, "SF already exist. Choose different sfnum");
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlx5_sf_मुक्त(काष्ठा mlx5_sf_table *table, काष्ठा mlx5_sf *sf)
अणु
	mlx5_sf_id_erase(table, sf);
	mlx5_sf_hw_table_sf_मुक्त(table->dev, sf->controller, sf->id);
	kमुक्त(sf);
पूर्ण

अटल काष्ठा mlx5_sf_table *mlx5_sf_table_try_get(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_table *table = dev->priv.sf_table;

	अगर (!table)
		वापस शून्य;

	वापस refcount_inc_not_zero(&table->refcount) ? table : शून्य;
पूर्ण

अटल व्योम mlx5_sf_table_put(काष्ठा mlx5_sf_table *table)
अणु
	अगर (refcount_dec_and_test(&table->refcount))
		complete(&table->disable_complete);
पूर्ण

अटल क्रमागत devlink_port_fn_state mlx5_sf_to_devlink_state(u8 hw_state)
अणु
	चयन (hw_state) अणु
	हाल MLX5_VHCA_STATE_ACTIVE:
	हाल MLX5_VHCA_STATE_IN_USE:
		वापस DEVLINK_PORT_FN_STATE_ACTIVE;
	हाल MLX5_VHCA_STATE_INVALID:
	हाल MLX5_VHCA_STATE_ALLOCATED:
	हाल MLX5_VHCA_STATE_TEARDOWN_REQUEST:
	शेष:
		वापस DEVLINK_PORT_FN_STATE_INACTIVE;
	पूर्ण
पूर्ण

अटल क्रमागत devlink_port_fn_opstate mlx5_sf_to_devlink_opstate(u8 hw_state)
अणु
	चयन (hw_state) अणु
	हाल MLX5_VHCA_STATE_IN_USE:
	हाल MLX5_VHCA_STATE_TEARDOWN_REQUEST:
		वापस DEVLINK_PORT_FN_OPSTATE_ATTACHED;
	हाल MLX5_VHCA_STATE_INVALID:
	हाल MLX5_VHCA_STATE_ALLOCATED:
	हाल MLX5_VHCA_STATE_ACTIVE:
	शेष:
		वापस DEVLINK_PORT_FN_OPSTATE_DETACHED;
	पूर्ण
पूर्ण

अटल bool mlx5_sf_is_active(स्थिर काष्ठा mlx5_sf *sf)
अणु
	वापस sf->hw_state == MLX5_VHCA_STATE_ACTIVE || sf->hw_state == MLX5_VHCA_STATE_IN_USE;
पूर्ण

पूर्णांक mlx5_devlink_sf_port_fn_state_get(काष्ठा devlink *devlink, काष्ठा devlink_port *dl_port,
				      क्रमागत devlink_port_fn_state *state,
				      क्रमागत devlink_port_fn_opstate *opstate,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_sf_table *table;
	काष्ठा mlx5_sf *sf;
	पूर्णांक err = 0;

	table = mlx5_sf_table_try_get(dev);
	अगर (!table)
		वापस -EOPNOTSUPP;

	sf = mlx5_sf_lookup_by_index(table, dl_port->index);
	अगर (!sf) अणु
		err = -EOPNOTSUPP;
		जाओ sf_err;
	पूर्ण
	mutex_lock(&table->sf_state_lock);
	*state = mlx5_sf_to_devlink_state(sf->hw_state);
	*opstate = mlx5_sf_to_devlink_opstate(sf->hw_state);
	mutex_unlock(&table->sf_state_lock);
sf_err:
	mlx5_sf_table_put(table);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_sf_activate(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_sf *sf,
			    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (mlx5_sf_is_active(sf))
		वापस 0;
	अगर (sf->hw_state != MLX5_VHCA_STATE_ALLOCATED) अणु
		NL_SET_ERR_MSG_MOD(extack, "SF is inactivated but it is still attached");
		वापस -EBUSY;
	पूर्ण

	err = mlx5_cmd_sf_enable_hca(dev, sf->hw_fn_id);
	अगर (err)
		वापस err;

	sf->hw_state = MLX5_VHCA_STATE_ACTIVE;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_sf_deactivate(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_sf *sf)
अणु
	पूर्णांक err;

	अगर (!mlx5_sf_is_active(sf))
		वापस 0;

	err = mlx5_cmd_sf_disable_hca(dev, sf->hw_fn_id);
	अगर (err)
		वापस err;

	sf->hw_state = MLX5_VHCA_STATE_TEARDOWN_REQUEST;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_sf_state_set(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_sf_table *table,
			     काष्ठा mlx5_sf *sf,
			     क्रमागत devlink_port_fn_state state,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = 0;

	mutex_lock(&table->sf_state_lock);
	अगर (state == mlx5_sf_to_devlink_state(sf->hw_state))
		जाओ out;
	अगर (state == DEVLINK_PORT_FN_STATE_ACTIVE)
		err = mlx5_sf_activate(dev, sf, extack);
	अन्यथा अगर (state == DEVLINK_PORT_FN_STATE_INACTIVE)
		err = mlx5_sf_deactivate(dev, sf);
	अन्यथा
		err = -EINVAL;
out:
	mutex_unlock(&table->sf_state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_devlink_sf_port_fn_state_set(काष्ठा devlink *devlink, काष्ठा devlink_port *dl_port,
				      क्रमागत devlink_port_fn_state state,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_sf_table *table;
	काष्ठा mlx5_sf *sf;
	पूर्णांक err;

	table = mlx5_sf_table_try_get(dev);
	अगर (!table) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Port state set is only supported in eswitch switchdev mode or SF ports are disabled.");
		वापस -EOPNOTSUPP;
	पूर्ण
	sf = mlx5_sf_lookup_by_index(table, dl_port->index);
	अगर (!sf) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = mlx5_sf_state_set(dev, table, sf, state, extack);
out:
	mlx5_sf_table_put(table);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_sf_add(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_sf_table *table,
		       स्थिर काष्ठा devlink_port_new_attrs *new_attr,
		       काष्ठा netlink_ext_ack *extack,
		       अचिन्हित पूर्णांक *new_port_index)
अणु
	काष्ठा mlx5_eचयन *esw = dev->priv.eचयन;
	काष्ठा mlx5_sf *sf;
	पूर्णांक err;

	sf = mlx5_sf_alloc(table, esw, new_attr->controller, new_attr->sfnum, extack);
	अगर (IS_ERR(sf))
		वापस PTR_ERR(sf);

	err = mlx5_esw_offloads_sf_vport_enable(esw, &sf->dl_port, sf->hw_fn_id,
						new_attr->controller, new_attr->sfnum);
	अगर (err)
		जाओ esw_err;
	*new_port_index = sf->port_index;
	वापस 0;

esw_err:
	mlx5_sf_मुक्त(table, sf);
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5_sf_new_check_attr(काष्ठा mlx5_core_dev *dev, स्थिर काष्ठा devlink_port_new_attrs *new_attr,
		       काष्ठा netlink_ext_ack *extack)
अणु
	अगर (new_attr->flavour != DEVLINK_PORT_FLAVOUR_PCI_SF) अणु
		NL_SET_ERR_MSG_MOD(extack, "Driver supports only SF port addition");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (new_attr->port_index_valid) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Driver does not support user defined port index assignment");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (!new_attr->sfnum_valid) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "User must provide unique sfnum. Driver does not support auto assignment");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (new_attr->controller_valid && new_attr->controller &&
	    !mlx5_core_is_ecpf_esw_manager(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "External controller is unsupported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (new_attr->pfnum != PCI_FUNC(dev->pdev->devfn)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid pfnum supplied");
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlx5_devlink_sf_port_new(काष्ठा devlink *devlink,
			     स्थिर काष्ठा devlink_port_new_attrs *new_attr,
			     काष्ठा netlink_ext_ack *extack,
			     अचिन्हित पूर्णांक *new_port_index)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_sf_table *table;
	पूर्णांक err;

	err = mlx5_sf_new_check_attr(dev, new_attr, extack);
	अगर (err)
		वापस err;

	table = mlx5_sf_table_try_get(dev);
	अगर (!table) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Port add is only supported in eswitch switchdev mode or SF ports are disabled.");
		वापस -EOPNOTSUPP;
	पूर्ण
	err = mlx5_sf_add(dev, table, new_attr, extack, new_port_index);
	mlx5_sf_table_put(table);
	वापस err;
पूर्ण

अटल व्योम mlx5_sf_dealloc(काष्ठा mlx5_sf_table *table, काष्ठा mlx5_sf *sf)
अणु
	अगर (sf->hw_state == MLX5_VHCA_STATE_ALLOCATED) अणु
		mlx5_sf_मुक्त(table, sf);
	पूर्ण अन्यथा अगर (mlx5_sf_is_active(sf)) अणु
		/* Even अगर its active, it is treated as in_use because by the समय,
		 * it is disabled here, it may getting used. So it is safe to
		 * always look क्रम the event to ensure that it is recycled only after
		 * firmware gives confirmation that it is detached by the driver.
		 */
		mlx5_cmd_sf_disable_hca(table->dev, sf->hw_fn_id);
		mlx5_sf_hw_table_sf_deferred_मुक्त(table->dev, sf->controller, sf->id);
		kमुक्त(sf);
	पूर्ण अन्यथा अणु
		mlx5_sf_hw_table_sf_deferred_मुक्त(table->dev, sf->controller, sf->id);
		kमुक्त(sf);
	पूर्ण
पूर्ण

पूर्णांक mlx5_devlink_sf_port_del(काष्ठा devlink *devlink, अचिन्हित पूर्णांक port_index,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_eचयन *esw = dev->priv.eचयन;
	काष्ठा mlx5_sf_table *table;
	काष्ठा mlx5_sf *sf;
	पूर्णांक err = 0;

	table = mlx5_sf_table_try_get(dev);
	अगर (!table) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Port del is only supported in eswitch switchdev mode or SF ports are disabled.");
		वापस -EOPNOTSUPP;
	पूर्ण
	sf = mlx5_sf_lookup_by_index(table, port_index);
	अगर (!sf) अणु
		err = -ENODEV;
		जाओ sf_err;
	पूर्ण

	mlx5_esw_offloads_sf_vport_disable(esw, sf->hw_fn_id);
	mlx5_sf_id_erase(table, sf);

	mutex_lock(&table->sf_state_lock);
	mlx5_sf_dealloc(table, sf);
	mutex_unlock(&table->sf_state_lock);
sf_err:
	mlx5_sf_table_put(table);
	वापस err;
पूर्ण

अटल bool mlx5_sf_state_update_check(स्थिर काष्ठा mlx5_sf *sf, u8 new_state)
अणु
	अगर (sf->hw_state == MLX5_VHCA_STATE_ACTIVE && new_state == MLX5_VHCA_STATE_IN_USE)
		वापस true;

	अगर (sf->hw_state == MLX5_VHCA_STATE_IN_USE && new_state == MLX5_VHCA_STATE_ACTIVE)
		वापस true;

	अगर (sf->hw_state == MLX5_VHCA_STATE_TEARDOWN_REQUEST &&
	    new_state == MLX5_VHCA_STATE_ALLOCATED)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक mlx5_sf_vhca_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ opcode, व्योम *data)
अणु
	काष्ठा mlx5_sf_table *table = container_of(nb, काष्ठा mlx5_sf_table, vhca_nb);
	स्थिर काष्ठा mlx5_vhca_state_event *event = data;
	bool update = false;
	काष्ठा mlx5_sf *sf;

	table = mlx5_sf_table_try_get(table->dev);
	अगर (!table)
		वापस 0;

	mutex_lock(&table->sf_state_lock);
	sf = mlx5_sf_lookup_by_function_id(table, event->function_id);
	अगर (!sf)
		जाओ sf_err;

	/* When driver is attached or detached to a function, an event
	 * notअगरies such state change.
	 */
	update = mlx5_sf_state_update_check(sf, event->new_vhca_state);
	अगर (update)
		sf->hw_state = event->new_vhca_state;
sf_err:
	mutex_unlock(&table->sf_state_lock);
	mlx5_sf_table_put(table);
	वापस 0;
पूर्ण

अटल व्योम mlx5_sf_table_enable(काष्ठा mlx5_sf_table *table)
अणु
	init_completion(&table->disable_complete);
	refcount_set(&table->refcount, 1);
पूर्ण

अटल व्योम mlx5_sf_deactivate_all(काष्ठा mlx5_sf_table *table)
अणु
	काष्ठा mlx5_eचयन *esw = table->dev->priv.eचयन;
	अचिन्हित दीर्घ index;
	काष्ठा mlx5_sf *sf;

	/* At this poपूर्णांक, no new user commands can start and no vhca event can
	 * arrive. It is safe to destroy all user created SFs.
	 */
	xa_क्रम_each(&table->port_indices, index, sf) अणु
		mlx5_esw_offloads_sf_vport_disable(esw, sf->hw_fn_id);
		mlx5_sf_id_erase(table, sf);
		mlx5_sf_dealloc(table, sf);
	पूर्ण
पूर्ण

अटल व्योम mlx5_sf_table_disable(काष्ठा mlx5_sf_table *table)
अणु
	अगर (!refcount_पढ़ो(&table->refcount))
		वापस;

	/* Balances with refcount_set; drop the reference so that new user cmd cannot start
	 * and new vhca event handler cannnot run.
	 */
	mlx5_sf_table_put(table);
	रुको_क्रम_completion(&table->disable_complete);

	mlx5_sf_deactivate_all(table);
पूर्ण

अटल पूर्णांक mlx5_sf_esw_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा mlx5_sf_table *table = container_of(nb, काष्ठा mlx5_sf_table, esw_nb);
	स्थिर काष्ठा mlx5_esw_event_info *mode = data;

	चयन (mode->new_mode) अणु
	हाल MLX5_ESWITCH_OFFLOADS:
		mlx5_sf_table_enable(table);
		अवरोध;
	हाल MLX5_ESWITCH_NONE:
		mlx5_sf_table_disable(table);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool mlx5_sf_table_supported(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->priv.eचयन && MLX5_ESWITCH_MANAGER(dev) &&
	       mlx5_sf_hw_table_supported(dev);
पूर्ण

पूर्णांक mlx5_sf_table_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_table *table;
	पूर्णांक err;

	अगर (!mlx5_sf_table_supported(dev) || !mlx5_vhca_event_supported(dev))
		वापस 0;

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	mutex_init(&table->sf_state_lock);
	table->dev = dev;
	xa_init(&table->port_indices);
	dev->priv.sf_table = table;
	refcount_set(&table->refcount, 0);
	table->esw_nb.notअगरier_call = mlx5_sf_esw_event;
	err = mlx5_esw_event_notअगरier_रेजिस्टर(dev->priv.eचयन, &table->esw_nb);
	अगर (err)
		जाओ reg_err;

	table->vhca_nb.notअगरier_call = mlx5_sf_vhca_event;
	err = mlx5_vhca_event_notअगरier_रेजिस्टर(table->dev, &table->vhca_nb);
	अगर (err)
		जाओ vhca_err;

	वापस 0;

vhca_err:
	mlx5_esw_event_notअगरier_unरेजिस्टर(dev->priv.eचयन, &table->esw_nb);
reg_err:
	mutex_destroy(&table->sf_state_lock);
	kमुक्त(table);
	dev->priv.sf_table = शून्य;
	वापस err;
पूर्ण

व्योम mlx5_sf_table_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_table *table = dev->priv.sf_table;

	अगर (!table)
		वापस;

	mlx5_vhca_event_notअगरier_unरेजिस्टर(table->dev, &table->vhca_nb);
	mlx5_esw_event_notअगरier_unरेजिस्टर(dev->priv.eचयन, &table->esw_nb);
	WARN_ON(refcount_पढ़ो(&table->refcount));
	mutex_destroy(&table->sf_state_lock);
	WARN_ON(!xa_empty(&table->port_indices));
	kमुक्त(table);
पूर्ण
