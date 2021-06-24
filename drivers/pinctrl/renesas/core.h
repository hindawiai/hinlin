<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * SuperH Pin Function Controller support.
 *
 * Copyright (C) 2012  Renesas Solutions Corp.
 */
#अगर_अघोषित __SH_PFC_CORE_H__
#घोषणा __SH_PFC_CORE_H__

#समावेश <linux/types.h>

#समावेश "sh_pfc.h"

काष्ठा sh_pfc_pin_range अणु
	u16 start;
	u16 end;
पूर्ण;

पूर्णांक sh_pfc_रेजिस्टर_gpiochip(काष्ठा sh_pfc *pfc);

पूर्णांक sh_pfc_रेजिस्टर_pinctrl(काष्ठा sh_pfc *pfc);

u32 sh_pfc_पढ़ो_raw_reg(व्योम __iomem *mapped_reg, अचिन्हित पूर्णांक reg_width);
व्योम sh_pfc_ग_लिखो_raw_reg(व्योम __iomem *mapped_reg, अचिन्हित पूर्णांक reg_width,
			  u32 data);
u32 sh_pfc_पढ़ो(काष्ठा sh_pfc *pfc, u32 reg);
व्योम sh_pfc_ग_लिखो(काष्ठा sh_pfc *pfc, u32 reg, u32 data);

पूर्णांक sh_pfc_get_pin_index(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin);
पूर्णांक sh_pfc_config_mux(काष्ठा sh_pfc *pfc, अचिन्हित mark, पूर्णांक pinmux_type);

#पूर्ण_अगर /* __SH_PFC_CORE_H__ */
