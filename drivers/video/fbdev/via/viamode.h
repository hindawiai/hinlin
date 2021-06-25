<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __VIAMODE_H__
#घोषणा __VIAMODE_H__

#समावेश "global.h"

काष्ठा VPITTable अणु
	अचिन्हित अक्षर Misc;
	अचिन्हित अक्षर SR[StdSR];
	अचिन्हित अक्षर GR[StdGR];
	अचिन्हित अक्षर AR[StdAR];
पूर्ण;

काष्ठा patch_table अणु
	पूर्णांक table_length;
	काष्ठा io_reg *io_reg_table;
पूर्ण;

बाह्य पूर्णांक NUM_TOTAL_CN400_ModeXregs;
बाह्य पूर्णांक NUM_TOTAL_CN700_ModeXregs;
बाह्य पूर्णांक NUM_TOTAL_KM400_ModeXregs;
बाह्य पूर्णांक NUM_TOTAL_CX700_ModeXregs;
बाह्य पूर्णांक NUM_TOTAL_VX855_ModeXregs;
बाह्य पूर्णांक NUM_TOTAL_CLE266_ModeXregs;
बाह्य पूर्णांक NUM_TOTAL_PATCH_MODE;

बाह्य काष्ठा io_reg CN400_ModeXregs[];
बाह्य काष्ठा io_reg CN700_ModeXregs[];
बाह्य काष्ठा io_reg KM400_ModeXregs[];
बाह्य काष्ठा io_reg CX700_ModeXregs[];
बाह्य काष्ठा io_reg VX800_ModeXregs[];
बाह्य काष्ठा io_reg VX855_ModeXregs[];
बाह्य काष्ठा io_reg CLE266_ModeXregs[];
बाह्य काष्ठा io_reg PM1024x768[];
बाह्य काष्ठा patch_table res_patch_table[];
बाह्य काष्ठा VPITTable VPIT;

स्थिर काष्ठा fb_videomode *viafb_get_best_mode(पूर्णांक hres, पूर्णांक vres,
	पूर्णांक refresh);
स्थिर काष्ठा fb_videomode *viafb_get_best_rb_mode(पूर्णांक hres, पूर्णांक vres,
	पूर्णांक refresh);

#पूर्ण_अगर /* __VIAMODE_H__ */
