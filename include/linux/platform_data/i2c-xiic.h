<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * i2c-xiic.h
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * Xilinx IIC
 */

#अगर_अघोषित _LINUX_I2C_XIIC_H
#घोषणा _LINUX_I2C_XIIC_H

/**
 * काष्ठा xiic_i2c_platक्रमm_data - Platक्रमm data of the Xilinx I2C driver
 * @num_devices:	Number of devices that shall be added when the driver
 *			is probed.
 * @devices:		The actuall devices to add.
 *
 * This purpose of this platक्रमm data काष्ठा is to be able to provide a number
 * of devices that should be added to the I2C bus. The reason is that someबार
 * the I2C board info is not enough, a new PCI board can क्रम instance be
 * plugged पूर्णांकo a standard PC, and the bus number might be unknown at
 * early init समय.
 */
काष्ठा xiic_i2c_platक्रमm_data अणु
	u8				num_devices;
	काष्ठा i2c_board_info स्थिर	*devices;
पूर्ण;

#पूर्ण_अगर /* _LINUX_I2C_XIIC_H */
