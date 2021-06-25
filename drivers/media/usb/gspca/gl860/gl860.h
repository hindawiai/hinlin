<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* GSPCA subdrivers क्रम Genesys Logic webcams with the GL860 chip
 * Subdriver declarations
 *
 * 2009/10/14 Olivier LORIN <o.lorin@laposte.net>
 */
#अगर_अघोषित GL860_DEV_H
#घोषणा GL860_DEV_H

#समावेश "gspca.h"

#घोषणा MODULE_NAME "gspca_gl860"
#घोषणा DRIVER_VERSION "0.9d10"

#घोषणा ctrl_in  gl860_RTx
#घोषणा ctrl_out gl860_RTx

#घोषणा ID_MI1320   1
#घोषणा ID_OV2640   2
#घोषणा ID_OV9655   4
#घोषणा ID_MI2020   8

#घोषणा _MI1320_  (((काष्ठा sd *) gspca_dev)->sensor == ID_MI1320)
#घोषणा _MI2020_  (((काष्ठा sd *) gspca_dev)->sensor == ID_MI2020)
#घोषणा _OV2640_  (((काष्ठा sd *) gspca_dev)->sensor == ID_OV2640)
#घोषणा _OV9655_  (((काष्ठा sd *) gspca_dev)->sensor == ID_OV9655)

#घोषणा IMAGE_640   0
#घोषणा IMAGE_800   1
#घोषणा IMAGE_1280  2
#घोषणा IMAGE_1600  3

काष्ठा sd_gl860 अणु
	u16 backlight;
	u16 brightness;
	u16 sharpness;
	u16 contrast;
	u16 gamma;
	u16 hue;
	u16 saturation;
	u16 whitebal;
	u8  mirror;
	u8  flip;
	u8  AC50Hz;
पूर्ण;

/* Specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	काष्ठा sd_gl860 vcur;
	काष्ठा sd_gl860 vold;
	काष्ठा sd_gl860 vmax;

	पूर्णांक  (*dev_configure_alt)  (काष्ठा gspca_dev *);
	पूर्णांक  (*dev_init_at_startup)(काष्ठा gspca_dev *);
	पूर्णांक  (*dev_init_pre_alt)   (काष्ठा gspca_dev *);
	व्योम (*dev_post_unset_alt) (काष्ठा gspca_dev *);
	पूर्णांक  (*dev_camera_settings)(काष्ठा gspca_dev *);

	u8   swapRB;
	u8   mirrorMask;
	u8   sensor;
	s32  nbIm;
	s32  nbRightUp;
	u8   रुकोSet;
पूर्ण;

काष्ठा validx अणु
	u16 val;
	u16 idx;
पूर्ण;

काष्ठा idxdata अणु
	u8 idx;
	u8 data[3];
पूर्ण;

पूर्णांक fetch_validx(काष्ठा gspca_dev *gspca_dev, काष्ठा validx *tbl, पूर्णांक len);
पूर्णांक keep_on_fetching_validx(काष्ठा gspca_dev *gspca_dev, काष्ठा validx *tbl,
				पूर्णांक len, पूर्णांक n);
व्योम fetch_idxdata(काष्ठा gspca_dev *gspca_dev, काष्ठा idxdata *tbl, पूर्णांक len);

पूर्णांक gl860_RTx(काष्ठा gspca_dev *gspca_dev,
			अचिन्हित अक्षर pref, u32 req, u16 val, u16 index,
			s32 len, व्योम *pdata);

व्योम mi1320_init_settings(काष्ठा gspca_dev *);
व्योम ov2640_init_settings(काष्ठा gspca_dev *);
व्योम ov9655_init_settings(काष्ठा gspca_dev *);
व्योम mi2020_init_settings(काष्ठा gspca_dev *);

#पूर्ण_अगर
