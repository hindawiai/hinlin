<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __GLOBAL_H__
#घोषणा __GLOBAL_H__

#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/console.h>
#समावेश <linux/समयr.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/olpc.h>
#अन्यथा
#घोषणा machine_is_olpc(x) 0
#पूर्ण_अगर

#समावेश "debug.h"

#समावेश "viafbdev.h"
#समावेश "chip.h"
#समावेश "accel.h"
#समावेश "share.h"
#समावेश "dvi.h"
#समावेश "viamode.h"
#समावेश "hw.h"

#समावेश "lcd.h"
#समावेश "ioctl.h"
#समावेश "via_utility.h"
#समावेश "vt1636.h"
#समावेश "tblDPASetting.h"

/* External काष्ठा*/

बाह्य पूर्णांक viafb_platक्रमm_epia_dvi;
बाह्य पूर्णांक viafb_device_lcd_dualedge;
बाह्य पूर्णांक viafb_bus_width;
बाह्य पूर्णांक viafb_display_hardware_layout;
बाह्य काष्ठा offset offset_reg;
बाह्य काष्ठा viafb_par *viaparinfo;
बाह्य काष्ठा viafb_par *viaparinfo1;
बाह्य काष्ठा fb_info *viafbinfo;
बाह्य काष्ठा fb_info *viafbinfo1;
बाह्य पूर्णांक viafb_DeviceStatus;
बाह्य पूर्णांक viafb_refresh;
बाह्य पूर्णांक viafb_refresh1;
बाह्य पूर्णांक viafb_lcd_dsp_method;
बाह्य पूर्णांक viafb_lcd_mode;

बाह्य पूर्णांक viafb_CRT_ON;
बाह्य अचिन्हित पूर्णांक viafb_second_xres;
बाह्य अचिन्हित पूर्णांक viafb_second_yres;
बाह्य पूर्णांक viafb_hotplug_Xres;
बाह्य पूर्णांक viafb_hotplug_Yres;
बाह्य पूर्णांक viafb_hotplug_bpp;
बाह्य पूर्णांक viafb_hotplug_refresh;
बाह्य पूर्णांक viafb_primary_dev;

बाह्य पूर्णांक viafb_lcd_panel_id;

#पूर्ण_अगर /* __GLOBAL_H__ */
