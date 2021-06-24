<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_KFR2R09_H
#घोषणा __ASM_SH_KFR2R09_H

#समावेश <video/sh_mobile_lcdc.h>

#अगर defined(CONFIG_FB_SH_MOBILE_LCDC) || defined(CONFIG_FB_SH_MOBILE_LCDC_MODULE)
पूर्णांक kfr2r09_lcd_setup(व्योम *sys_ops_handle,
		      काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops);
व्योम kfr2r09_lcd_start(व्योम *sys_ops_handle,
		       काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops);
#अन्यथा
अटल पूर्णांक kfr2r09_lcd_setup(व्योम *sys_ops_handle,
				काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops)
अणु
	वापस -ENODEV;
पूर्ण
अटल व्योम kfr2r09_lcd_start(व्योम *sys_ops_handle,
				काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_KFR2R09_H */
