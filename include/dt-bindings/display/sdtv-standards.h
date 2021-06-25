<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only or X11 */
/*
 * Copyright 2019 Pengutronix, Marco Felsch <kernel@pengutronix.de>
 */

#अगर_अघोषित _DT_BINDINGS_DISPLAY_SDTV_STDS_H
#घोषणा _DT_BINDINGS_DISPLAY_SDTV_STDS_H

/*
 * Attention: Keep the SDTV_STD_* bit definitions in sync with
 * include/uapi/linux/videodev2.h V4L2_STD_* bit definitions.
 */
/* One bit क्रम each standard */
#घोषणा SDTV_STD_PAL_B		0x00000001
#घोषणा SDTV_STD_PAL_B1		0x00000002
#घोषणा SDTV_STD_PAL_G		0x00000004
#घोषणा SDTV_STD_PAL_H		0x00000008
#घोषणा SDTV_STD_PAL_I		0x00000010
#घोषणा SDTV_STD_PAL_D		0x00000020
#घोषणा SDTV_STD_PAL_D1		0x00000040
#घोषणा SDTV_STD_PAL_K		0x00000080

#घोषणा SDTV_STD_PAL		(SDTV_STD_PAL_B		| \
				 SDTV_STD_PAL_B1	| \
				 SDTV_STD_PAL_G		| \
				 SDTV_STD_PAL_H		| \
				 SDTV_STD_PAL_I		| \
				 SDTV_STD_PAL_D		| \
				 SDTV_STD_PAL_D1	| \
				 SDTV_STD_PAL_K)

#घोषणा SDTV_STD_PAL_M		0x00000100
#घोषणा SDTV_STD_PAL_N		0x00000200
#घोषणा SDTV_STD_PAL_Nc		0x00000400
#घोषणा SDTV_STD_PAL_60		0x00000800

#घोषणा SDTV_STD_NTSC_M		0x00001000	/* BTSC */
#घोषणा SDTV_STD_NTSC_M_JP	0x00002000	/* EIA-J */
#घोषणा SDTV_STD_NTSC_443	0x00004000
#घोषणा SDTV_STD_NTSC_M_KR	0x00008000	/* FM A2 */

#घोषणा SDTV_STD_NTSC		(SDTV_STD_NTSC_M	| \
				 SDTV_STD_NTSC_M_JP	| \
				 SDTV_STD_NTSC_M_KR)

#घोषणा SDTV_STD_SECAM_B	0x00010000
#घोषणा SDTV_STD_SECAM_D	0x00020000
#घोषणा SDTV_STD_SECAM_G	0x00040000
#घोषणा SDTV_STD_SECAM_H	0x00080000
#घोषणा SDTV_STD_SECAM_K	0x00100000
#घोषणा SDTV_STD_SECAM_K1	0x00200000
#घोषणा SDTV_STD_SECAM_L	0x00400000
#घोषणा SDTV_STD_SECAM_LC	0x00800000

#घोषणा SDTV_STD_SECAM		(SDTV_STD_SECAM_B	| \
				 SDTV_STD_SECAM_D	| \
				 SDTV_STD_SECAM_G	| \
				 SDTV_STD_SECAM_H	| \
				 SDTV_STD_SECAM_K	| \
				 SDTV_STD_SECAM_K1	| \
				 SDTV_STD_SECAM_L	| \
				 SDTV_STD_SECAM_LC)

/* Standards क्रम Countries with 60Hz Line frequency */
#घोषणा SDTV_STD_525_60		(SDTV_STD_PAL_M		| \
				 SDTV_STD_PAL_60	| \
				 SDTV_STD_NTSC		| \
				 SDTV_STD_NTSC_443)

/* Standards क्रम Countries with 50Hz Line frequency */
#घोषणा SDTV_STD_625_50		(SDTV_STD_PAL		| \
				 SDTV_STD_PAL_N		| \
				 SDTV_STD_PAL_Nc	| \
				 SDTV_STD_SECAM)

#पूर्ण_अगर /* _DT_BINDINGS_DISPLAY_SDTV_STDS_H */
