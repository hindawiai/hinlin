<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#अगर_अघोषित __VIAUTILITY_H__
#घोषणा __VIAUTILITY_H__

/* These functions are used to get inक्रमmation about device's state */
व्योम viafb_get_device_support_state(u32 *support_state);
व्योम viafb_get_device_connect_state(u32 *connect_state);
bool viafb_lcd_get_support_expand_state(u32 xres, u32 yres);

/* These function are used to access gamma table */
व्योम viafb_set_gamma_table(पूर्णांक bpp, अचिन्हित पूर्णांक *gamma_table);
व्योम viafb_get_gamma_table(अचिन्हित पूर्णांक *gamma_table);
व्योम viafb_get_gamma_support_state(पूर्णांक bpp, अचिन्हित पूर्णांक *support_state);

#पूर्ण_अगर /* __VIAUTILITY_H__ */
