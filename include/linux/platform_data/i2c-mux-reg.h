<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * I2C multiplexer using a single रेजिस्टर
 *
 * Copyright 2015 Freescale Semiconductor
 * York Sun <yorksun@मुक्तscale.com>
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_I2C_MUX_REG_H
#घोषणा __LINUX_PLATFORM_DATA_I2C_MUX_REG_H

/**
 * काष्ठा i2c_mux_reg_platक्रमm_data - Platक्रमm-dependent data क्रम i2c-mux-reg
 * @parent: Parent I2C bus adapter number
 * @base_nr: Base I2C bus number to number adapters from or zero क्रम dynamic
 * @values: Array of value क्रम each channel
 * @n_values: Number of multiplexer channels
 * @little_endian: Indicating अगर the रेजिस्टर is in little endian
 * @ग_लिखो_only: Reading the रेजिस्टर is not allowed by hardware
 * @classes: Optional I2C स्वतः-detection classes
 * @idle: Value to ग_लिखो to mux when idle
 * @idle_in_use: indicate अगर idle value is in use
 * @reg: Virtual address of the रेजिस्टर to चयन channel
 * @reg_size: रेजिस्टर size in bytes
 */
काष्ठा i2c_mux_reg_platक्रमm_data अणु
	पूर्णांक parent;
	पूर्णांक base_nr;
	स्थिर अचिन्हित पूर्णांक *values;
	पूर्णांक n_values;
	bool little_endian;
	bool ग_लिखो_only;
	स्थिर अचिन्हित पूर्णांक *classes;
	u32 idle;
	bool idle_in_use;
	व्योम __iomem *reg;
	resource_माप_प्रकार reg_size;
पूर्ण;

#पूर्ण_अगर	/* __LINUX_PLATFORM_DATA_I2C_MUX_REG_H */
