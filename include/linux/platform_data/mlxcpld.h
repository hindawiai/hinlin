<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/*
 * Mellanox I2C multiplexer support in CPLD
 *
 * Copyright (C) 2016-2020 Mellanox Technologies
 */

#अगर_अघोषित _LINUX_I2C_MLXCPLD_H
#घोषणा _LINUX_I2C_MLXCPLD_H

/* Platक्रमm data क्रम the CPLD I2C multiplexers */

/* mlxcpld_mux_plat_data - per mux data, used with i2c_रेजिस्टर_board_info
 * @chan_ids - channels array
 * @num_adaps - number of adapters
 * @sel_reg_addr - mux select रेजिस्टर offset in CPLD space
 * @reg_size: रेजिस्टर size in bytes
 * @handle: handle to be passed by callback
 * @completion_notअगरy: callback to notअगरy when all the adapters are created
 */
काष्ठा mlxcpld_mux_plat_data अणु
	पूर्णांक *chan_ids;
	पूर्णांक num_adaps;
	पूर्णांक sel_reg_addr;
	u8 reg_size;
	व्योम *handle;
	पूर्णांक (*completion_notअगरy)(व्योम *handle, काष्ठा i2c_adapter *parent,
				 काष्ठा i2c_adapter *adapters[]);
पूर्ण;

#पूर्ण_अगर /* _LINUX_I2C_MLXCPLD_H */
