<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Helper module क्रम board specअगरic I2C bus registration
 *
 * Copyright (C) 2009 Nokia Corporation.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP1_I2C_H
#घोषणा __ARCH_ARM_MACH_OMAP1_I2C_H

काष्ठा i2c_board_info;
काष्ठा omap_i2c_bus_platक्रमm_data;

पूर्णांक omap_i2c_add_bus(काष्ठा omap_i2c_bus_platक्रमm_data *i2c_pdata,
			पूर्णांक bus_id);

#अगर defined(CONFIG_I2C_OMAP) || defined(CONFIG_I2C_OMAP_MODULE)
बाह्य पूर्णांक omap_रेजिस्टर_i2c_bus(पूर्णांक bus_id, u32 clkrate,
				 काष्ठा i2c_board_info स्थिर *info,
				 अचिन्हित len);
बाह्य पूर्णांक omap_रेजिस्टर_i2c_bus_cmdline(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap_रेजिस्टर_i2c_bus(पूर्णांक bus_id, u32 clkrate,
				 काष्ठा i2c_board_info स्थिर *info,
				 अचिन्हित len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक omap_रेजिस्टर_i2c_bus_cmdline(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ARCH_ARM_MACH_OMAP1_I2C_H */
