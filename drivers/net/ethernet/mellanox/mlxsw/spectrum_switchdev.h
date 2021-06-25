<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/netdevice.h>

काष्ठा mlxsw_sp_bridge;
काष्ठा mlxsw_sp_bridge_port;

काष्ठा mlxsw_sp_bridge_port *
mlxsw_sp_bridge_port_find(काष्ठा mlxsw_sp_bridge *bridge,
			  काष्ठा net_device *brport_dev);

u8 mlxsw_sp_bridge_port_stp_state(काष्ठा mlxsw_sp_bridge_port *bridge_port);
