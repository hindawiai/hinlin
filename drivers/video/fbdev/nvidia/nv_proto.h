<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $XFree86: xc/programs/Xserver/hw/xमुक्त86/drivers/nv/nv_proto.h,v 1.10 2003/07/31 20:24:29 mvojkovi Exp $ */

#अगर_अघोषित __NV_PROTO_H__
#घोषणा __NV_PROTO_H__

/* in nv_setup.c */
पूर्णांक NVCommonSetup(काष्ठा fb_info *info);
व्योम NVWriteCrtc(काष्ठा nvidia_par *par, u8 index, u8 value);
u8 NVReadCrtc(काष्ठा nvidia_par *par, u8 index);
व्योम NVWriteGr(काष्ठा nvidia_par *par, u8 index, u8 value);
u8 NVReadGr(काष्ठा nvidia_par *par, u8 index);
व्योम NVWriteSeq(काष्ठा nvidia_par *par, u8 index, u8 value);
u8 NVReadSeq(काष्ठा nvidia_par *par, u8 index);
व्योम NVWriteAttr(काष्ठा nvidia_par *par, u8 index, u8 value);
u8 NVReadAttr(काष्ठा nvidia_par *par, u8 index);
व्योम NVWriteMiscOut(काष्ठा nvidia_par *par, u8 value);
u8 NVReadMiscOut(काष्ठा nvidia_par *par);
व्योम NVWriteDacMask(काष्ठा nvidia_par *par, u8 value);
व्योम NVWriteDacReadAddr(काष्ठा nvidia_par *par, u8 value);
व्योम NVWriteDacWriteAddr(काष्ठा nvidia_par *par, u8 value);
व्योम NVWriteDacData(काष्ठा nvidia_par *par, u8 value);
u8 NVReadDacData(काष्ठा nvidia_par *par);

/* in nv_hw.c */
व्योम NVCalcStateExt(काष्ठा nvidia_par *par, काष्ठा _riva_hw_state *,
		    पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);
व्योम NVLoadStateExt(काष्ठा nvidia_par *par, काष्ठा _riva_hw_state *);
व्योम NVUnloadStateExt(काष्ठा nvidia_par *par, काष्ठा _riva_hw_state *);
व्योम NVSetStartAddress(काष्ठा nvidia_par *par, u32);
पूर्णांक NVShowHideCursor(काष्ठा nvidia_par *par, पूर्णांक);
व्योम NVLockUnlock(काष्ठा nvidia_par *par, पूर्णांक);

/* in nvidia-i2c.c */
#अगर_घोषित CONFIG_FB_NVIDIA_I2C
व्योम nvidia_create_i2c_busses(काष्ठा nvidia_par *par);
व्योम nvidia_delete_i2c_busses(काष्ठा nvidia_par *par);
पूर्णांक nvidia_probe_i2c_connector(काष्ठा fb_info *info, पूर्णांक conn,
			       u8 ** out_edid);
#अन्यथा
#घोषणा nvidia_create_i2c_busses(...)
#घोषणा nvidia_delete_i2c_busses(...)
#घोषणा nvidia_probe_i2c_connector(p, c, edid) (-1)
#पूर्ण_अगर

पूर्णांक nvidia_probe_of_connector(काष्ठा fb_info *info, पूर्णांक conn,
			      u8 ** out_edid);

/* in nv_accel.c */
बाह्य व्योम NVResetGraphics(काष्ठा fb_info *info);
बाह्य व्योम nvidiafb_copyarea(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_copyarea *region);
बाह्य व्योम nvidiafb_fillrect(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_fillrect *rect);
बाह्य व्योम nvidiafb_imageblit(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_image *image);
बाह्य पूर्णांक nvidiafb_sync(काष्ठा fb_info *info);

/* in nv_backlight.h */
#अगर_घोषित CONFIG_FB_NVIDIA_BACKLIGHT
बाह्य व्योम nvidia_bl_init(काष्ठा nvidia_par *par);
बाह्य व्योम nvidia_bl_निकास(काष्ठा nvidia_par *par);
#अन्यथा
अटल अंतरभूत व्योम nvidia_bl_init(काष्ठा nvidia_par *par) अणुपूर्ण
अटल अंतरभूत व्योम nvidia_bl_निकास(काष्ठा nvidia_par *par) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* __NV_PROTO_H__ */
