<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_ifc_vhca_event.h"
#समावेश "mlx5_core.h"
#समावेश "vhca_event.h"
#समावेश "ecpf.h"

काष्ठा mlx5_vhca_state_notअगरier अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_nb nb;
	काष्ठा blocking_notअगरier_head n_head;
पूर्ण;

काष्ठा mlx5_vhca_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlx5_vhca_state_notअगरier *notअगरier;
	काष्ठा mlx5_vhca_state_event event;
पूर्ण;

पूर्णांक mlx5_cmd_query_vhca_state(काष्ठा mlx5_core_dev *dev, u16 function_id, u32 *out, u32 outlen)
अणु
	u32 in[MLX5_ST_SZ_DW(query_vhca_state_in)] = अणुपूर्ण;

	MLX5_SET(query_vhca_state_in, in, opcode, MLX5_CMD_OP_QUERY_VHCA_STATE);
	MLX5_SET(query_vhca_state_in, in, function_id, function_id);
	MLX5_SET(query_vhca_state_in, in, embedded_cpu_function, 0);

	वापस mlx5_cmd_exec(dev, in, माप(in), out, outlen);
पूर्ण

अटल पूर्णांक mlx5_cmd_modअगरy_vhca_state(काष्ठा mlx5_core_dev *dev, u16 function_id,
				      u32 *in, u32 inlen)
अणु
	u32 out[MLX5_ST_SZ_DW(modअगरy_vhca_state_out)] = अणुपूर्ण;

	MLX5_SET(modअगरy_vhca_state_in, in, opcode, MLX5_CMD_OP_MODIFY_VHCA_STATE);
	MLX5_SET(modअगरy_vhca_state_in, in, function_id, function_id);
	MLX5_SET(modअगरy_vhca_state_in, in, embedded_cpu_function, 0);

	वापस mlx5_cmd_exec(dev, in, inlen, out, माप(out));
पूर्ण

पूर्णांक mlx5_modअगरy_vhca_sw_id(काष्ठा mlx5_core_dev *dev, u16 function_id, u32 sw_fn_id)
अणु
	u32 out[MLX5_ST_SZ_DW(modअगरy_vhca_state_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(modअगरy_vhca_state_in)] = अणुपूर्ण;

	MLX5_SET(modअगरy_vhca_state_in, in, opcode, MLX5_CMD_OP_MODIFY_VHCA_STATE);
	MLX5_SET(modअगरy_vhca_state_in, in, function_id, function_id);
	MLX5_SET(modअगरy_vhca_state_in, in, embedded_cpu_function, 0);
	MLX5_SET(modअगरy_vhca_state_in, in, vhca_state_field_select.sw_function_id, 1);
	MLX5_SET(modअगरy_vhca_state_in, in, vhca_state_context.sw_function_id, sw_fn_id);

	वापस mlx5_cmd_exec_inout(dev, modअगरy_vhca_state, in, out);
पूर्ण

पूर्णांक mlx5_vhca_event_arm(काष्ठा mlx5_core_dev *dev, u16 function_id)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_vhca_state_in)] = अणुपूर्ण;

	MLX5_SET(modअगरy_vhca_state_in, in, vhca_state_context.arm_change_event, 1);
	MLX5_SET(modअगरy_vhca_state_in, in, vhca_state_field_select.arm_change_event, 1);

	वापस mlx5_cmd_modअगरy_vhca_state(dev, function_id, in, माप(in));
पूर्ण

अटल व्योम
mlx5_vhca_event_notअगरy(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_vhca_state_event *event)
अणु
	u32 out[MLX5_ST_SZ_DW(query_vhca_state_out)] = अणुपूर्ण;
	पूर्णांक err;

	err = mlx5_cmd_query_vhca_state(dev, event->function_id, out, माप(out));
	अगर (err)
		वापस;

	event->sw_function_id = MLX5_GET(query_vhca_state_out, out,
					 vhca_state_context.sw_function_id);
	event->new_vhca_state = MLX5_GET(query_vhca_state_out, out,
					 vhca_state_context.vhca_state);

	mlx5_vhca_event_arm(dev, event->function_id);

	blocking_notअगरier_call_chain(&dev->priv.vhca_state_notअगरier->n_head, 0, event);
पूर्ण

अटल व्योम mlx5_vhca_state_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा mlx5_vhca_event_work *work = container_of(_work, काष्ठा mlx5_vhca_event_work, work);
	काष्ठा mlx5_vhca_state_notअगरier *notअगरier = work->notअगरier;
	काष्ठा mlx5_core_dev *dev = notअगरier->dev;

	mlx5_vhca_event_notअगरy(dev, &work->event);
	kमुक्त(work);
पूर्ण

अटल पूर्णांक
mlx5_vhca_state_change_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_vhca_state_notअगरier *notअगरier =
				mlx5_nb_cof(nb, काष्ठा mlx5_vhca_state_notअगरier, nb);
	काष्ठा mlx5_vhca_event_work *work;
	काष्ठा mlx5_eqe *eqe = data;

	work = kzalloc(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस NOTIFY_DONE;
	INIT_WORK(&work->work, &mlx5_vhca_state_work_handler);
	work->notअगरier = notअगरier;
	work->event.function_id = be16_to_cpu(eqe->data.vhca_state.function_id);
	mlx5_events_work_enqueue(notअगरier->dev, &work->work);
	वापस NOTIFY_OK;
पूर्ण

व्योम mlx5_vhca_state_cap_handle(काष्ठा mlx5_core_dev *dev, व्योम *set_hca_cap)
अणु
	अगर (!mlx5_vhca_event_supported(dev))
		वापस;

	MLX5_SET(cmd_hca_cap, set_hca_cap, vhca_state, 1);
	MLX5_SET(cmd_hca_cap, set_hca_cap, event_on_vhca_state_allocated, 1);
	MLX5_SET(cmd_hca_cap, set_hca_cap, event_on_vhca_state_active, 1);
	MLX5_SET(cmd_hca_cap, set_hca_cap, event_on_vhca_state_in_use, 1);
	MLX5_SET(cmd_hca_cap, set_hca_cap, event_on_vhca_state_tearकरोwn_request, 1);
पूर्ण

पूर्णांक mlx5_vhca_event_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_vhca_state_notअगरier *notअगरier;

	अगर (!mlx5_vhca_event_supported(dev))
		वापस 0;

	notअगरier = kzalloc(माप(*notअगरier), GFP_KERNEL);
	अगर (!notअगरier)
		वापस -ENOMEM;

	dev->priv.vhca_state_notअगरier = notअगरier;
	notअगरier->dev = dev;
	BLOCKING_INIT_NOTIFIER_HEAD(&notअगरier->n_head);
	MLX5_NB_INIT(&notअगरier->nb, mlx5_vhca_state_change_notअगरier, VHCA_STATE_CHANGE);
	वापस 0;
पूर्ण

व्योम mlx5_vhca_event_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_vhca_event_supported(dev))
		वापस;

	kमुक्त(dev->priv.vhca_state_notअगरier);
	dev->priv.vhca_state_notअगरier = शून्य;
पूर्ण

व्योम mlx5_vhca_event_start(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_vhca_state_notअगरier *notअगरier;

	अगर (!dev->priv.vhca_state_notअगरier)
		वापस;

	notअगरier = dev->priv.vhca_state_notअगरier;
	mlx5_eq_notअगरier_रेजिस्टर(dev, &notअगरier->nb);
पूर्ण

व्योम mlx5_vhca_event_stop(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_vhca_state_notअगरier *notअगरier;

	अगर (!dev->priv.vhca_state_notअगरier)
		वापस;

	notअगरier = dev->priv.vhca_state_notअगरier;
	mlx5_eq_notअगरier_unरेजिस्टर(dev, &notअगरier->nb);
पूर्ण

पूर्णांक mlx5_vhca_event_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb)
अणु
	अगर (!dev->priv.vhca_state_notअगरier)
		वापस -EOPNOTSUPP;
	वापस blocking_notअगरier_chain_रेजिस्टर(&dev->priv.vhca_state_notअगरier->n_head, nb);
पूर्ण

व्योम mlx5_vhca_event_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&dev->priv.vhca_state_notअगरier->n_head, nb);
पूर्ण
