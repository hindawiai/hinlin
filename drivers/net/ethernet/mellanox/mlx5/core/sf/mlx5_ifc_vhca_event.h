<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#अगर_अघोषित __MLX5_IFC_VHCA_EVENT_H__
#घोषणा __MLX5_IFC_VHCA_EVENT_H__

क्रमागत mlx5_अगरc_vhca_state अणु
	MLX5_VHCA_STATE_INVALID = 0x0,
	MLX5_VHCA_STATE_ALLOCATED = 0x1,
	MLX5_VHCA_STATE_ACTIVE = 0x2,
	MLX5_VHCA_STATE_IN_USE = 0x3,
	MLX5_VHCA_STATE_TEARDOWN_REQUEST = 0x4,
पूर्ण;

काष्ठा mlx5_अगरc_vhca_state_context_bits अणु
	u8         arm_change_event[0x1];
	u8         reserved_at_1[0xb];
	u8         vhca_state[0x4];
	u8         reserved_at_10[0x10];

	u8         sw_function_id[0x20];

	u8         reserved_at_40[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_query_vhca_state_out_bits अणु
	u8         status[0x8];
	u8         reserved_at_8[0x18];

	u8         syndrome[0x20];

	u8         reserved_at_40[0x40];

	काष्ठा mlx5_अगरc_vhca_state_context_bits vhca_state_context;
पूर्ण;

काष्ठा mlx5_अगरc_query_vhca_state_in_bits अणु
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         reserved_at_20[0x10];
	u8         op_mod[0x10];

	u8         embedded_cpu_function[0x1];
	u8         reserved_at_41[0xf];
	u8         function_id[0x10];

	u8         reserved_at_60[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_vhca_state_field_select_bits अणु
	u8         reserved_at_0[0x1e];
	u8         sw_function_id[0x1];
	u8         arm_change_event[0x1];
पूर्ण;

काष्ठा mlx5_अगरc_modअगरy_vhca_state_out_bits अणु
	u8         status[0x8];
	u8         reserved_at_8[0x18];

	u8         syndrome[0x20];

	u8         reserved_at_40[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_modअगरy_vhca_state_in_bits अणु
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         reserved_at_20[0x10];
	u8         op_mod[0x10];

	u8         embedded_cpu_function[0x1];
	u8         reserved_at_41[0xf];
	u8         function_id[0x10];

	काष्ठा mlx5_अगरc_vhca_state_field_select_bits vhca_state_field_select;

	काष्ठा mlx5_अगरc_vhca_state_context_bits vhca_state_context;
पूर्ण;

#पूर्ण_अगर
