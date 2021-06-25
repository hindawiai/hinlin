<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_PORT_H
#घोषणा _MLXSW_PORT_H

#समावेश <linux/types.h>

#घोषणा MLXSW_PORT_MAX_MTU		10000

#घोषणा MLXSW_PORT_DEFAULT_VID		1

#घोषणा MLXSW_PORT_SWID_DISABLED_PORT	255
#घोषणा MLXSW_PORT_SWID_ALL_SWIDS	254
#घोषणा MLXSW_PORT_SWID_TYPE_IB		1
#घोषणा MLXSW_PORT_SWID_TYPE_ETH	2

#घोषणा MLXSW_PORT_MID			0xd000

#घोषणा MLXSW_PORT_MAX_IB_PHY_PORTS	36
#घोषणा MLXSW_PORT_MAX_IB_PORTS		(MLXSW_PORT_MAX_IB_PHY_PORTS + 1)

#घोषणा MLXSW_PORT_CPU_PORT		0x0

#घोषणा MLXSW_PORT_DONT_CARE		0xFF

क्रमागत mlxsw_port_admin_status अणु
	MLXSW_PORT_ADMIN_STATUS_UP = 1,
	MLXSW_PORT_ADMIN_STATUS_DOWN = 2,
	MLXSW_PORT_ADMIN_STATUS_UP_ONCE = 3,
	MLXSW_PORT_ADMIN_STATUS_DISABLED = 4,
पूर्ण;

क्रमागत mlxsw_reg_pude_oper_status अणु
	MLXSW_PORT_OPER_STATUS_UP = 1,
	MLXSW_PORT_OPER_STATUS_DOWN = 2,
	MLXSW_PORT_OPER_STATUS_FAILURE = 4,	/* Can be set to up again. */
पूर्ण;

#पूर्ण_अगर /* _MLXSW_PORT_H */
