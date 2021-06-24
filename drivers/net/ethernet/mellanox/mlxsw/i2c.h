<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_I2C_H
#घोषणा _MLXSW_I2C_H

#समावेश <linux/i2c.h>

#अगर IS_ENABLED(CONFIG_MLXSW_I2C)

पूर्णांक mlxsw_i2c_driver_रेजिस्टर(काष्ठा i2c_driver *i2c_driver);
व्योम mlxsw_i2c_driver_unरेजिस्टर(काष्ठा i2c_driver *i2c_driver);

#अन्यथा

अटल अंतरभूत पूर्णांक
mlxsw_i2c_driver_रेजिस्टर(काष्ठा i2c_driver *i2c_driver)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम
mlxsw_i2c_driver_unरेजिस्टर(काष्ठा i2c_driver *i2c_driver)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
