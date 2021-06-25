<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SiS 300/540/630[S]/730[S],
 * SiS 315[E|PRO]/550/[M]650/651/[M]661[F|M]X/740/[M]741[GX]/330/[M]760[GX],
 * XGI V3XT/V5/V8, Z7
 * frame buffer driver क्रम Linux kernels >= 2.4.14 and >=2.6.3
 *
 * 2D acceleration part
 *
 * Based on the X driver's sis300_accel.h which is
 *     Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria
 * and sis310_accel.h which is
 *     Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria
 *
 * Author:   Thomas Winischhofer <thomas@winischhofer.net>:
 *			(see http://www.winischhofer.net/
 *			क्रम more inक्रमmation and updates)
 */

#अगर_अघोषित _SISFB_ACCEL_H
#घोषणा _SISFB_ACCEL_H

/* Guard accelerator accesses with spin_lock_irqsave? Works well without. */
#अघोषित SISFB_USE_SPINLOCKS

#अगर_घोषित SISFB_USE_SPINLOCKS
#समावेश <linux/spinlock.h>
#घोषणा CRITBEGIN  spin_lock_irqsave(&ivideo->lockaccel, critflags);
#घोषणा CRITEND	   spin_unlock_irqrestore(&ivideo->lockaccel, critflags);
#घोषणा CRITFLAGS  अचिन्हित दीर्घ critflags;
#अन्यथा
#घोषणा CRITBEGIN
#घोषणा CRITEND
#घोषणा CRITFLAGS
#पूर्ण_अगर

/* Definitions क्रम the SIS engine communication. */

#घोषणा PATREGSIZE      384  /* Pattern रेजिस्टर size. 384 bytes @ 0x8300 */
#घोषणा BR(x)   (0x8200 | (x) << 2)
#घोषणा PBR(x)  (0x8300 | (x) << 2)

/* SiS300 engine commands */
#घोषणा BITBLT                  0x00000000  /* Blit */
#घोषणा COLOREXP                0x00000001  /* Color expand */
#घोषणा ENCOLOREXP              0x00000002  /* Enhanced color expand */
#घोषणा MULTIPLE_SCANLINE       0x00000003  /* ? */
#घोषणा LINE                    0x00000004  /* Draw line */
#घोषणा TRAPAZOID_FILL          0x00000005  /* Fill trapezoid */
#घोषणा TRANSPARENT_BITBLT      0x00000006  /* Transparent Blit */

/* Additional engine commands क्रम 315 */
#घोषणा ALPHA_BLEND		0x00000007  /* Alpha blend ? */
#घोषणा A3D_FUNCTION		0x00000008  /* 3D command ? */
#घोषणा	CLEAR_Z_BUFFER		0x00000009  /* ? */
#घोषणा GRADIENT_FILL		0x0000000A  /* Gradient fill */

/* source select */
#घोषणा SRCVIDEO                0x00000000  /* source is video RAM */
#घोषणा SRCSYSTEM               0x00000010  /* source is प्रणाली memory */
#घोषणा SRCCPUBLITBUF           SRCSYSTEM   /* source is CPU-driven BitBuffer (क्रम color expand) */
#घोषणा SRCAGP                  0x00000020  /* source is AGP memory (?) */

/* Pattern flags */
#घोषणा PATFG                   0x00000000  /* क्रमeground color */
#घोषणा PATPATREG               0x00000040  /* pattern in pattern buffer (0x8300) */
#घोषणा PATMONO                 0x00000080  /* mono pattern */

/* blitting direction (300 series only) */
#घोषणा X_INC                   0x00010000
#घोषणा X_DEC                   0x00000000
#घोषणा Y_INC                   0x00020000
#घोषणा Y_DEC                   0x00000000

/* Clipping flags */
#घोषणा NOCLIP                  0x00000000
#घोषणा NOMERGECLIP             0x04000000
#घोषणा CLIPENABLE              0x00040000
#घोषणा CLIPWITHOUTMERGE        0x04040000

/* Transparency */
#घोषणा OPAQUE                  0x00000000
#घोषणा TRANSPARENT             0x00100000

/* ? */
#घोषणा DSTAGP                  0x02000000
#घोषणा DSTVIDEO                0x02000000

/* Subfunctions क्रम Color/Enhanced Color Expansion (315 only) */
#घोषणा COLOR_TO_MONO		0x00100000
#घोषणा AA_TEXT			0x00200000

/* Some general रेजिस्टरs क्रम 315 series */
#घोषणा SRC_ADDR		0x8200
#घोषणा SRC_PITCH		0x8204
#घोषणा AGP_BASE		0x8206 /* color-depth dependent value */
#घोषणा SRC_Y			0x8208
#घोषणा SRC_X			0x820A
#घोषणा DST_Y			0x820C
#घोषणा DST_X			0x820E
#घोषणा DST_ADDR		0x8210
#घोषणा DST_PITCH		0x8214
#घोषणा DST_HEIGHT		0x8216
#घोषणा RECT_WIDTH		0x8218
#घोषणा RECT_HEIGHT		0x821A
#घोषणा PAT_FGCOLOR		0x821C
#घोषणा PAT_BGCOLOR		0x8220
#घोषणा SRC_FGCOLOR		0x8224
#घोषणा SRC_BGCOLOR		0x8228
#घोषणा MONO_MASK		0x822C
#घोषणा LEFT_CLIP		0x8234
#घोषणा TOP_CLIP		0x8236
#घोषणा RIGHT_CLIP		0x8238
#घोषणा BOTTOM_CLIP		0x823A
#घोषणा COMMAND_READY		0x823C
#घोषणा FIRE_TRIGGER      	0x8240

#घोषणा PATTERN_REG		0x8300  /* 384 bytes pattern buffer */

/* Transparent bitblit रेजिस्टरs */
#घोषणा TRANS_DST_KEY_HIGH	PAT_FGCOLOR
#घोषणा TRANS_DST_KEY_LOW	PAT_BGCOLOR
#घोषणा TRANS_SRC_KEY_HIGH	SRC_FGCOLOR
#घोषणा TRANS_SRC_KEY_LOW	SRC_BGCOLOR

/* Store queue length in par */
#घोषणा CmdQueLen ivideo->cmdqueuelength

/* ------------- SiS 300 series -------------- */

/* BR(16) (0x8240):

   bit 31 2D engine: 1 is idle,
   bit 30 3D engine: 1 is idle,
   bit 29 Command queue: 1 is empty
   bits 28:24: Current CPU driven BitBlt buffer stage bit[4:0]
   bits 15:0:  Current command queue length

*/

#घोषणा SiS300Idle \
  अणु \
	जबतक((MMIO_IN16(ivideo->mmio_vbase, BR(16)+2) & 0xE000) != 0xE000)अणुपूर्ण \
	जबतक((MMIO_IN16(ivideo->mmio_vbase, BR(16)+2) & 0xE000) != 0xE000)अणुपूर्ण \
	जबतक((MMIO_IN16(ivideo->mmio_vbase, BR(16)+2) & 0xE000) != 0xE000)अणुपूर्ण \
  	CmdQueLen = MMIO_IN16(ivideo->mmio_vbase, 0x8240); \
  पूर्ण
/* (करो three बार, because 2D engine seems quite unsure about whether or not it's idle) */

#घोषणा SiS300SetupSRCBase(base) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(0), base);\
	CmdQueLen--;

#घोषणा SiS300SetupSRCPitch(pitch) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT16(ivideo->mmio_vbase, BR(1), pitch);\
	CmdQueLen--;

#घोषणा SiS300SetupSRCXY(x,y) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(2), (x)<<16 | (y) );\
	CmdQueLen--;

#घोषणा SiS300SetupDSTBase(base) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(4), base);\
	CmdQueLen--;

#घोषणा SiS300SetupDSTXY(x,y) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(3), (x)<<16 | (y) );\
	CmdQueLen--;

#घोषणा SiS300SetupDSTRect(x,y) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(5), (y)<<16 | (x) );\
	CmdQueLen--;

#घोषणा SiS300SetupDSTColorDepth(bpp) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT16(ivideo->mmio_vbase, BR(1)+2, bpp);\
	CmdQueLen--;

#घोषणा SiS300SetupRect(w,h) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(6), (h)<<16 | (w) );\
	CmdQueLen--;

#घोषणा SiS300SetupPATFG(color) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(7), color);\
	CmdQueLen--;

#घोषणा SiS300SetupPATBG(color) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(8), color);\
	CmdQueLen--;

#घोषणा SiS300SetupSRCFG(color) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(9), color);\
	CmdQueLen--;

#घोषणा SiS300SetupSRCBG(color) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(10), color);\
	CmdQueLen--;

/* 0x8224 src colorkey high */
/* 0x8228 src colorkey low */
/* 0x821c dest colorkey high */
/* 0x8220 dest colorkey low */
#घोषणा SiS300SetupSRCTrans(color) \
	अगर(CmdQueLen <= 1) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, 0x8224, color);\
	MMIO_OUT32(ivideo->mmio_vbase, 0x8228, color);\
	CmdQueLen -= 2;

#घोषणा SiS300SetupDSTTrans(color) \
	अगर(CmdQueLen <= 1) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, 0x821C, color); \
	MMIO_OUT32(ivideo->mmio_vbase, 0x8220, color); \
	CmdQueLen -= 2;

#घोषणा SiS300SetupMONOPAT(p0,p1) \
	अगर(CmdQueLen <= 1) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(11), p0);\
	MMIO_OUT32(ivideo->mmio_vbase, BR(12), p1);\
	CmdQueLen -= 2;

#घोषणा SiS300SetupClipLT(left,top) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(13), ((left) & 0xFFFF) | (top)<<16 );\
	CmdQueLen--;

#घोषणा SiS300SetupClipRB(right,bottom) \
	अगर(CmdQueLen <= 0) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(14), ((right) & 0xFFFF) | (bottom)<<16 );\
	CmdQueLen--;

/* General */
#घोषणा SiS300SetupROP(rop) \
	ivideo->CommandReg = (rop) << 8;

#घोषणा SiS300SetupCMDFlag(flags) \
	ivideo->CommandReg |= (flags);

#घोषणा SiS300DoCMD \
	अगर(CmdQueLen <= 1) SiS300Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, BR(15), ivideo->CommandReg); \
	MMIO_OUT32(ivideo->mmio_vbase, BR(16), 0);\
	CmdQueLen -= 2;

/* -------------- SiS 315/330 series --------------- */

/* Q_STATUS:
   bit 31 = 1: All engines idle and all queues empty
   bit 30 = 1: Hardware Queue (=HW CQ, 2D queue, 3D queue) empty
   bit 29 = 1: 2D engine is idle
   bit 28 = 1: 3D engine is idle
   bit 27 = 1: HW command queue empty
   bit 26 = 1: 2D queue empty
   bit 25 = 1: 3D queue empty
   bit 24 = 1: SW command queue empty
   bits 23:16: 2D counter 3
   bits 15:8:  2D counter 2
   bits 7:0:   2D counter 1
*/

#घोषणा SiS310Idle \
  अणु \
	जबतक( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000)अणुपूर्ण \
	जबतक( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000)अणुपूर्ण \
	जबतक( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000)अणुपूर्ण \
	जबतक( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000)अणुपूर्ण \
  	CmdQueLen = 0; \
  पूर्ण

#घोषणा SiS310SetupSRCBase(base) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, SRC_ADDR, base);\
	CmdQueLen--;

#घोषणा SiS310SetupSRCPitch(pitch) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT16(ivideo->mmio_vbase, SRC_PITCH, pitch);\
	CmdQueLen--;

#घोषणा SiS310SetupSRCXY(x,y) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, SRC_Y, (x)<<16 | (y) );\
	CmdQueLen--;

#घोषणा SiS310SetupDSTBase(base) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, DST_ADDR, base);\
	CmdQueLen--;

#घोषणा SiS310SetupDSTXY(x,y) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, DST_Y, (x)<<16 | (y) );\
	CmdQueLen--;

#घोषणा SiS310SetupDSTRect(x,y) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, DST_PITCH, (y)<<16 | (x) );\
	CmdQueLen--;

#घोषणा SiS310SetupDSTColorDepth(bpp) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT16(ivideo->mmio_vbase, AGP_BASE, bpp);\
	CmdQueLen--;

#घोषणा SiS310SetupRect(w,h) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, RECT_WIDTH, (h)<<16 | (w) );\
	CmdQueLen--;

#घोषणा SiS310SetupPATFG(color) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, PAT_FGCOLOR, color);\
	CmdQueLen--;

#घोषणा SiS310SetupPATBG(color) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, PAT_BGCOLOR, color);\
	CmdQueLen--;

#घोषणा SiS310SetupSRCFG(color) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, SRC_FGCOLOR, color);\
	CmdQueLen--;

#घोषणा SiS310SetupSRCBG(color) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, SRC_BGCOLOR, color);\
	CmdQueLen--;

#घोषणा SiS310SetupSRCTrans(color) \
	अगर(CmdQueLen <= 1) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, TRANS_SRC_KEY_HIGH, color);\
	MMIO_OUT32(ivideo->mmio_vbase, TRANS_SRC_KEY_LOW, color);\
	CmdQueLen -= 2;

#घोषणा SiS310SetupDSTTrans(color) \
	अगर(CmdQueLen <= 1) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, TRANS_DST_KEY_HIGH, color); \
	MMIO_OUT32(ivideo->mmio_vbase, TRANS_DST_KEY_LOW, color); \
	CmdQueLen -= 2;

#घोषणा SiS310SetupMONOPAT(p0,p1) \
	अगर(CmdQueLen <= 1) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, MONO_MASK, p0);\
	MMIO_OUT32(ivideo->mmio_vbase, MONO_MASK+4, p1);\
	CmdQueLen -= 2;

#घोषणा SiS310SetupClipLT(left,top) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, LEFT_CLIP, ((left) & 0xFFFF) | (top)<<16 );\
	CmdQueLen--;

#घोषणा SiS310SetupClipRB(right,bottom) \
	अगर(CmdQueLen <= 0) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, RIGHT_CLIP, ((right) & 0xFFFF) | (bottom)<<16 );\
	CmdQueLen--;

#घोषणा SiS310SetupROP(rop) \
	ivideo->CommandReg = (rop) << 8;

#घोषणा SiS310SetupCMDFlag(flags) \
	ivideo->CommandReg |= (flags);

#घोषणा SiS310DoCMD \
	अगर(CmdQueLen <= 1) SiS310Idle;\
	MMIO_OUT32(ivideo->mmio_vbase, COMMAND_READY, ivideo->CommandReg); \
	MMIO_OUT32(ivideo->mmio_vbase, FIRE_TRIGGER, 0); \
	CmdQueLen -= 2;

पूर्णांक  sisfb_initaccel(काष्ठा sis_video_info *ivideo);
व्योम sisfb_syncaccel(काष्ठा sis_video_info *ivideo);

पूर्णांक  fbcon_sis_sync(काष्ठा fb_info *info);
व्योम fbcon_sis_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
व्योम fbcon_sis_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area);

#पूर्ण_अगर
