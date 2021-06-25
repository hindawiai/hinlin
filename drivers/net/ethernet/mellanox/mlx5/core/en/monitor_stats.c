<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018 Mellanox Technologies. */

#समावेश "en.h"
#समावेश "monitor_stats.h"
#समावेश "lib/eq.h"

/* Driver will set the following watch counters list:
 * Ppcnt.802_3:
 * a_in_range_length_errors      Type: 0x0, Counter:  0x0, group_id = N/A
 * a_out_of_range_length_field   Type: 0x0, Counter:  0x1, group_id = N/A
 * a_frame_too_दीर्घ_errors       Type: 0x0, Counter:  0x2, group_id = N/A
 * a_frame_check_sequence_errors Type: 0x0, Counter:  0x3, group_id = N/A
 * a_alignment_errors            Type: 0x0, Counter:  0x4, group_id = N/A
 * अगर_out_discards               Type: 0x0, Counter:  0x5, group_id = N/A
 * Q_Counters:
 * Q[index].rx_out_of_buffer   Type: 0x1, Counter:  0x4, group_id = counter_ix
 */

#घोषणा NUM_REQ_PPCNT_COUNTER_S1 MLX5_CMD_SET_MONITOR_NUM_PPCNT_COUNTER_SET1
#घोषणा NUM_REQ_Q_COUNTERS_S1    MLX5_CMD_SET_MONITOR_NUM_Q_COUNTERS_SET1

पूर्णांक mlx5e_monitor_counter_supported(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (!MLX5_CAP_GEN(mdev, max_num_of_monitor_counters))
		वापस false;
	अगर (MLX5_CAP_PCAM_REG(mdev, ppcnt) &&
	    MLX5_CAP_GEN(mdev, num_ppcnt_monitor_counters) <
	    NUM_REQ_PPCNT_COUNTER_S1)
		वापस false;
	अगर (MLX5_CAP_GEN(mdev, num_q_monitor_counters) <
	    NUM_REQ_Q_COUNTERS_S1)
		वापस false;
	वापस true;
पूर्ण

व्योम mlx5e_monitor_counter_arm(काष्ठा mlx5e_priv *priv)
अणु
	u32 in[MLX5_ST_SZ_DW(arm_monitor_counter_in)] = अणुपूर्ण;

	MLX5_SET(arm_monitor_counter_in, in, opcode,
		 MLX5_CMD_OP_ARM_MONITOR_COUNTER);
	mlx5_cmd_exec_in(priv->mdev, arm_monitor_counter, in);
पूर्ण

अटल व्योम mlx5e_monitor_counters_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_priv *priv = container_of(work, काष्ठा mlx5e_priv,
					       monitor_counters_work);

	mutex_lock(&priv->state_lock);
	mlx5e_stats_update_nकरो_stats(priv);
	mutex_unlock(&priv->state_lock);
	mlx5e_monitor_counter_arm(priv);
पूर्ण

अटल पूर्णांक mlx5e_monitor_event_handler(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ event, व्योम *eqe)
अणु
	काष्ठा mlx5e_priv *priv = mlx5_nb_cof(nb, काष्ठा mlx5e_priv,
					      monitor_counters_nb);
	queue_work(priv->wq, &priv->monitor_counters_work);
	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक fill_monitor_counter_ppcnt_set1(पूर्णांक cnt, u32 *in)
अणु
	क्रमागत mlx5_monitor_counter_ppcnt ppcnt_cnt;

	क्रम (ppcnt_cnt = 0;
	     ppcnt_cnt < NUM_REQ_PPCNT_COUNTER_S1;
	     ppcnt_cnt++, cnt++) अणु
		MLX5_SET(set_monitor_counter_in, in,
			 monitor_counter[cnt].type,
			 MLX5_QUERY_MONITOR_CNT_TYPE_PPCNT);
		MLX5_SET(set_monitor_counter_in, in,
			 monitor_counter[cnt].counter,
			 ppcnt_cnt);
	पूर्ण
	वापस ppcnt_cnt;
पूर्ण

अटल पूर्णांक fill_monitor_counter_q_counter_set1(पूर्णांक cnt, पूर्णांक q_counter, u32 *in)
अणु
	MLX5_SET(set_monitor_counter_in, in,
		 monitor_counter[cnt].type,
		 MLX5_QUERY_MONITOR_CNT_TYPE_Q_COUNTER);
	MLX5_SET(set_monitor_counter_in, in,
		 monitor_counter[cnt].counter,
		 MLX5_QUERY_MONITOR_Q_COUNTER_RX_OUT_OF_BUFFER);
	MLX5_SET(set_monitor_counter_in, in,
		 monitor_counter[cnt].counter_group_id,
		 q_counter);
	वापस 1;
पूर्ण

/* check अगर mlx5e_monitor_counter_supported beक्रमe calling this function*/
अटल व्योम mlx5e_set_monitor_counter(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक max_num_of_counters = MLX5_CAP_GEN(mdev, max_num_of_monitor_counters);
	पूर्णांक num_q_counters      = MLX5_CAP_GEN(mdev, num_q_monitor_counters);
	पूर्णांक num_ppcnt_counters  = !MLX5_CAP_PCAM_REG(mdev, ppcnt) ? 0 :
				  MLX5_CAP_GEN(mdev, num_ppcnt_monitor_counters);
	u32 in[MLX5_ST_SZ_DW(set_monitor_counter_in)] = अणुपूर्ण;
	पूर्णांक q_counter = priv->q_counter;
	पूर्णांक cnt	= 0;

	अगर (num_ppcnt_counters  >=  NUM_REQ_PPCNT_COUNTER_S1 &&
	    max_num_of_counters >= (NUM_REQ_PPCNT_COUNTER_S1 + cnt))
		cnt += fill_monitor_counter_ppcnt_set1(cnt, in);

	अगर (num_q_counters      >=  NUM_REQ_Q_COUNTERS_S1 &&
	    max_num_of_counters >= (NUM_REQ_Q_COUNTERS_S1 + cnt) &&
	    q_counter)
		cnt += fill_monitor_counter_q_counter_set1(cnt, q_counter, in);

	MLX5_SET(set_monitor_counter_in, in, num_of_counters, cnt);
	MLX5_SET(set_monitor_counter_in, in, opcode,
		 MLX5_CMD_OP_SET_MONITOR_COUNTER);

	mlx5_cmd_exec_in(mdev, set_monitor_counter, in);
पूर्ण

/* check अगर mlx5e_monitor_counter_supported beक्रमe calling this function*/
व्योम mlx5e_monitor_counter_init(काष्ठा mlx5e_priv *priv)
अणु
	INIT_WORK(&priv->monitor_counters_work, mlx5e_monitor_counters_work);
	MLX5_NB_INIT(&priv->monitor_counters_nb, mlx5e_monitor_event_handler,
		     MONITOR_COUNTER);
	mlx5_eq_notअगरier_रेजिस्टर(priv->mdev, &priv->monitor_counters_nb);

	mlx5e_set_monitor_counter(priv);
	mlx5e_monitor_counter_arm(priv);
	queue_work(priv->wq, &priv->update_stats_work);
पूर्ण

/* check अगर mlx5e_monitor_counter_supported beक्रमe calling this function*/
व्योम mlx5e_monitor_counter_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	u32 in[MLX5_ST_SZ_DW(set_monitor_counter_in)] = अणुपूर्ण;

	MLX5_SET(set_monitor_counter_in, in, opcode,
		 MLX5_CMD_OP_SET_MONITOR_COUNTER);

	mlx5_cmd_exec_in(priv->mdev, set_monitor_counter, in);
	mlx5_eq_notअगरier_unरेजिस्टर(priv->mdev, &priv->monitor_counters_nb);
	cancel_work_sync(&priv->monitor_counters_work);
पूर्ण
