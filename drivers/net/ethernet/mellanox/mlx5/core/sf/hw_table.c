<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd */
#समावेश <linux/mlx5/driver.h>
#समावेश "vhca_event.h"
#समावेश "priv.h"
#समावेश "sf.h"
#समावेश "mlx5_ifc_vhca_event.h"
#समावेश "ecpf.h"
#समावेश "vhca_event.h"
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"

काष्ठा mlx5_sf_hw अणु
	u32 usr_sfnum;
	u8 allocated: 1;
	u8 pending_delete: 1;
पूर्ण;

काष्ठा mlx5_sf_hwc_table अणु
	काष्ठा mlx5_sf_hw *sfs;
	पूर्णांक max_fn;
	u16 start_fn_id;
पूर्ण;

क्रमागत mlx5_sf_hwc_index अणु
	MLX5_SF_HWC_LOCAL,
	MLX5_SF_HWC_EXTERNAL,
	MLX5_SF_HWC_MAX,
पूर्ण;

काष्ठा mlx5_sf_hw_table अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mutex table_lock; /* Serializes sf deletion and vhca state change handler. */
	काष्ठा notअगरier_block vhca_nb;
	काष्ठा mlx5_sf_hwc_table hwc[MLX5_SF_HWC_MAX];
पूर्ण;

अटल काष्ठा mlx5_sf_hwc_table *
mlx5_sf_controller_to_hwc(काष्ठा mlx5_core_dev *dev, u32 controller)
अणु
	पूर्णांक idx = !!controller;

	वापस &dev->priv.sf_hw_table->hwc[idx];
पूर्ण

u16 mlx5_sf_sw_to_hw_id(काष्ठा mlx5_core_dev *dev, u32 controller, u16 sw_id)
अणु
	काष्ठा mlx5_sf_hwc_table *hwc;

	hwc = mlx5_sf_controller_to_hwc(dev, controller);
	वापस hwc->start_fn_id + sw_id;
पूर्ण

अटल u16 mlx5_sf_hw_to_sw_id(काष्ठा mlx5_sf_hwc_table *hwc, u16 hw_id)
अणु
	वापस hw_id - hwc->start_fn_id;
पूर्ण

अटल काष्ठा mlx5_sf_hwc_table *
mlx5_sf_table_fn_to_hwc(काष्ठा mlx5_sf_hw_table *table, u16 fn_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(table->hwc); i++) अणु
		अगर (table->hwc[i].max_fn &&
		    fn_id >= table->hwc[i].start_fn_id &&
		    fn_id < (table->hwc[i].start_fn_id + table->hwc[i].max_fn))
			वापस &table->hwc[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlx5_sf_hw_table_id_alloc(काष्ठा mlx5_sf_hw_table *table, u32 controller,
				     u32 usr_sfnum)
अणु
	काष्ठा mlx5_sf_hwc_table *hwc;
	पूर्णांक i;

	hwc = mlx5_sf_controller_to_hwc(table->dev, controller);
	अगर (!hwc->sfs)
		वापस -ENOSPC;

	/* Check अगर sf with same sfnum alपढ़ोy exists or not. */
	क्रम (i = 0; i < hwc->max_fn; i++) अणु
		अगर (hwc->sfs[i].allocated && hwc->sfs[i].usr_sfnum == usr_sfnum)
			वापस -EEXIST;
	पूर्ण
	/* Find the मुक्त entry and allocate the entry from the array */
	क्रम (i = 0; i < hwc->max_fn; i++) अणु
		अगर (!hwc->sfs[i].allocated) अणु
			hwc->sfs[i].usr_sfnum = usr_sfnum;
			hwc->sfs[i].allocated = true;
			वापस i;
		पूर्ण
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल व्योम mlx5_sf_hw_table_id_मुक्त(काष्ठा mlx5_sf_hw_table *table, u32 controller, पूर्णांक id)
अणु
	काष्ठा mlx5_sf_hwc_table *hwc;

	hwc = mlx5_sf_controller_to_hwc(table->dev, controller);
	hwc->sfs[id].allocated = false;
	hwc->sfs[id].pending_delete = false;
पूर्ण

पूर्णांक mlx5_sf_hw_table_sf_alloc(काष्ठा mlx5_core_dev *dev, u32 controller, u32 usr_sfnum)
अणु
	काष्ठा mlx5_sf_hw_table *table = dev->priv.sf_hw_table;
	u16 hw_fn_id;
	पूर्णांक sw_id;
	पूर्णांक err;

	अगर (!table)
		वापस -EOPNOTSUPP;

	mutex_lock(&table->table_lock);
	sw_id = mlx5_sf_hw_table_id_alloc(table, controller, usr_sfnum);
	अगर (sw_id < 0) अणु
		err = sw_id;
		जाओ exist_err;
	पूर्ण

	hw_fn_id = mlx5_sf_sw_to_hw_id(dev, controller, sw_id);
	err = mlx5_cmd_alloc_sf(dev, hw_fn_id);
	अगर (err)
		जाओ err;

	err = mlx5_modअगरy_vhca_sw_id(dev, hw_fn_id, usr_sfnum);
	अगर (err)
		जाओ vhca_err;

	अगर (controller) अणु
		/* If this SF is क्रम बाह्यal controller, SF manager
		 * needs to arm firmware to receive the events.
		 */
		err = mlx5_vhca_event_arm(dev, hw_fn_id);
		अगर (err)
			जाओ vhca_err;
	पूर्ण

	mutex_unlock(&table->table_lock);
	वापस sw_id;

vhca_err:
	mlx5_cmd_dealloc_sf(dev, hw_fn_id);
err:
	mlx5_sf_hw_table_id_मुक्त(table, controller, sw_id);
exist_err:
	mutex_unlock(&table->table_lock);
	वापस err;
पूर्ण

व्योम mlx5_sf_hw_table_sf_मुक्त(काष्ठा mlx5_core_dev *dev, u32 controller, u16 id)
अणु
	काष्ठा mlx5_sf_hw_table *table = dev->priv.sf_hw_table;
	u16 hw_fn_id;

	mutex_lock(&table->table_lock);
	hw_fn_id = mlx5_sf_sw_to_hw_id(dev, controller, id);
	mlx5_cmd_dealloc_sf(dev, hw_fn_id);
	mlx5_sf_hw_table_id_मुक्त(table, controller, id);
	mutex_unlock(&table->table_lock);
पूर्ण

अटल व्योम mlx5_sf_hw_table_hwc_sf_मुक्त(काष्ठा mlx5_core_dev *dev,
					 काष्ठा mlx5_sf_hwc_table *hwc, पूर्णांक idx)
अणु
	mlx5_cmd_dealloc_sf(dev, hwc->start_fn_id + idx);
	hwc->sfs[idx].allocated = false;
	hwc->sfs[idx].pending_delete = false;
पूर्ण

व्योम mlx5_sf_hw_table_sf_deferred_मुक्त(काष्ठा mlx5_core_dev *dev, u32 controller, u16 id)
अणु
	काष्ठा mlx5_sf_hw_table *table = dev->priv.sf_hw_table;
	u32 out[MLX5_ST_SZ_DW(query_vhca_state_out)] = अणुपूर्ण;
	काष्ठा mlx5_sf_hwc_table *hwc;
	u16 hw_fn_id;
	u8 state;
	पूर्णांक err;

	hw_fn_id = mlx5_sf_sw_to_hw_id(dev, controller, id);
	hwc = mlx5_sf_controller_to_hwc(dev, controller);
	mutex_lock(&table->table_lock);
	err = mlx5_cmd_query_vhca_state(dev, hw_fn_id, out, माप(out));
	अगर (err)
		जाओ err;
	state = MLX5_GET(query_vhca_state_out, out, vhca_state_context.vhca_state);
	अगर (state == MLX5_VHCA_STATE_ALLOCATED) अणु
		mlx5_cmd_dealloc_sf(dev, hw_fn_id);
		hwc->sfs[id].allocated = false;
	पूर्ण अन्यथा अणु
		hwc->sfs[id].pending_delete = true;
	पूर्ण
err:
	mutex_unlock(&table->table_lock);
पूर्ण

अटल व्योम mlx5_sf_hw_table_hwc_dealloc_all(काष्ठा mlx5_core_dev *dev,
					     काष्ठा mlx5_sf_hwc_table *hwc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hwc->max_fn; i++) अणु
		अगर (hwc->sfs[i].allocated)
			mlx5_sf_hw_table_hwc_sf_मुक्त(dev, hwc, i);
	पूर्ण
पूर्ण

अटल व्योम mlx5_sf_hw_table_dealloc_all(काष्ठा mlx5_sf_hw_table *table)
अणु
	mlx5_sf_hw_table_hwc_dealloc_all(table->dev, &table->hwc[MLX5_SF_HWC_EXTERNAL]);
	mlx5_sf_hw_table_hwc_dealloc_all(table->dev, &table->hwc[MLX5_SF_HWC_LOCAL]);
पूर्ण

अटल पूर्णांक mlx5_sf_hw_table_hwc_init(काष्ठा mlx5_sf_hwc_table *hwc, u16 max_fn, u16 base_id)
अणु
	काष्ठा mlx5_sf_hw *sfs;

	अगर (!max_fn)
		वापस 0;

	sfs = kसुस्मृति(max_fn, माप(*sfs), GFP_KERNEL);
	अगर (!sfs)
		वापस -ENOMEM;

	hwc->sfs = sfs;
	hwc->max_fn = max_fn;
	hwc->start_fn_id = base_id;
	वापस 0;
पूर्ण

अटल व्योम mlx5_sf_hw_table_hwc_cleanup(काष्ठा mlx5_sf_hwc_table *hwc)
अणु
	kमुक्त(hwc->sfs);
पूर्ण

पूर्णांक mlx5_sf_hw_table_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_hw_table *table;
	u16 max_ext_fn = 0;
	u16 ext_base_id;
	u16 max_fn = 0;
	u16 base_id;
	पूर्णांक err;

	अगर (!mlx5_vhca_event_supported(dev))
		वापस 0;

	अगर (mlx5_sf_supported(dev))
		max_fn = mlx5_sf_max_functions(dev);

	err = mlx5_esw_sf_max_hpf_functions(dev, &max_ext_fn, &ext_base_id);
	अगर (err)
		वापस err;

	अगर (!max_fn && !max_ext_fn)
		वापस 0;

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	mutex_init(&table->table_lock);
	table->dev = dev;
	dev->priv.sf_hw_table = table;

	base_id = mlx5_sf_start_function_id(dev);
	err = mlx5_sf_hw_table_hwc_init(&table->hwc[MLX5_SF_HWC_LOCAL], max_fn, base_id);
	अगर (err)
		जाओ table_err;

	err = mlx5_sf_hw_table_hwc_init(&table->hwc[MLX5_SF_HWC_EXTERNAL],
					max_ext_fn, ext_base_id);
	अगर (err)
		जाओ ext_err;

	mlx5_core_dbg(dev, "SF HW table: max sfs = %d, ext sfs = %d\n", max_fn, max_ext_fn);
	वापस 0;

ext_err:
	mlx5_sf_hw_table_hwc_cleanup(&table->hwc[MLX5_SF_HWC_LOCAL]);
table_err:
	mutex_destroy(&table->table_lock);
	kमुक्त(table);
	वापस err;
पूर्ण

व्योम mlx5_sf_hw_table_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_hw_table *table = dev->priv.sf_hw_table;

	अगर (!table)
		वापस;

	mutex_destroy(&table->table_lock);
	mlx5_sf_hw_table_hwc_cleanup(&table->hwc[MLX5_SF_HWC_EXTERNAL]);
	mlx5_sf_hw_table_hwc_cleanup(&table->hwc[MLX5_SF_HWC_LOCAL]);
	kमुक्त(table);
पूर्ण

अटल पूर्णांक mlx5_sf_hw_vhca_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ opcode, व्योम *data)
अणु
	काष्ठा mlx5_sf_hw_table *table = container_of(nb, काष्ठा mlx5_sf_hw_table, vhca_nb);
	स्थिर काष्ठा mlx5_vhca_state_event *event = data;
	काष्ठा mlx5_sf_hwc_table *hwc;
	काष्ठा mlx5_sf_hw *sf_hw;
	u16 sw_id;

	अगर (event->new_vhca_state != MLX5_VHCA_STATE_ALLOCATED)
		वापस 0;

	hwc = mlx5_sf_table_fn_to_hwc(table, event->function_id);
	अगर (!hwc)
		वापस 0;

	sw_id = mlx5_sf_hw_to_sw_id(hwc, event->function_id);
	sf_hw = &hwc->sfs[sw_id];

	mutex_lock(&table->table_lock);
	/* SF driver notअगरied through firmware that SF is finally detached.
	 * Hence recycle the sf hardware id क्रम reuse.
	 */
	अगर (sf_hw->allocated && sf_hw->pending_delete)
		mlx5_sf_hw_table_hwc_sf_मुक्त(table->dev, hwc, sw_id);
	mutex_unlock(&table->table_lock);
	वापस 0;
पूर्ण

पूर्णांक mlx5_sf_hw_table_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_hw_table *table = dev->priv.sf_hw_table;

	अगर (!table)
		वापस 0;

	table->vhca_nb.notअगरier_call = mlx5_sf_hw_vhca_event;
	वापस mlx5_vhca_event_notअगरier_रेजिस्टर(dev, &table->vhca_nb);
पूर्ण

व्योम mlx5_sf_hw_table_destroy(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_hw_table *table = dev->priv.sf_hw_table;

	अगर (!table)
		वापस;

	mlx5_vhca_event_notअगरier_unरेजिस्टर(dev, &table->vhca_nb);
	/* Dealloc SFs whose firmware event has been missed. */
	mlx5_sf_hw_table_dealloc_all(table);
पूर्ण

bool mlx5_sf_hw_table_supported(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस !!dev->priv.sf_hw_table;
पूर्ण
