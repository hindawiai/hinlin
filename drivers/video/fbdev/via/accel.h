<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __ACCEL_H__
#घोषणा __ACCEL_H__

#घोषणा FB_ACCEL_VIA_UNICHROME  50

/* MMIO Base Address Definition */
#घोषणा MMIO_VGABASE                0x8000
#घोषणा MMIO_CR_READ                (MMIO_VGABASE + 0x3D4)
#घोषणा MMIO_CR_WRITE               (MMIO_VGABASE + 0x3D5)
#घोषणा MMIO_SR_READ                (MMIO_VGABASE + 0x3C4)
#घोषणा MMIO_SR_WRITE               (MMIO_VGABASE + 0x3C5)

/* HW Cursor Status Define */
#घोषणा HW_Cursor_ON    0
#घोषणा HW_Cursor_OFF   1

#घोषणा CURSOR_SIZE     (8 * 1024)
#घोषणा VQ_SIZE         (256 * 1024)

#घोषणा VIA_MMIO_BLTBASE        0x200000
#घोषणा VIA_MMIO_BLTSIZE        0x200000

/* Defines क्रम 2D रेजिस्टरs */
#घोषणा VIA_REG_GECMD           0x000
#घोषणा VIA_REG_GEMODE          0x004
#घोषणा VIA_REG_SRCPOS          0x008
#घोषणा VIA_REG_DSTPOS          0x00C
/* width and height */
#घोषणा VIA_REG_DIMENSION       0x010
#घोषणा VIA_REG_PATADDR         0x014
#घोषणा VIA_REG_FGCOLOR         0x018
#घोषणा VIA_REG_BGCOLOR         0x01C
/* top and left of clipping */
#घोषणा VIA_REG_CLIPTL          0x020
/* bottom and right of clipping */
#घोषणा VIA_REG_CLIPBR          0x024
#घोषणा VIA_REG_OFFSET          0x028
/* color key control */
#घोषणा VIA_REG_KEYCONTROL      0x02C
#घोषणा VIA_REG_SRCBASE         0x030
#घोषणा VIA_REG_DSTBASE         0x034
/* pitch of src and dst */
#घोषणा VIA_REG_PITCH           0x038
#घोषणा VIA_REG_MONOPAT0        0x03C
#घोषणा VIA_REG_MONOPAT1        0x040
/* from 0x100 to 0x1ff */
#घोषणा VIA_REG_COLORPAT        0x100

/* defines क्रम VIA 2D रेजिस्टरs क्रम vt3353/3409 (M1 engine)*/
#घोषणा VIA_REG_GECMD_M1        0x000
#घोषणा VIA_REG_GEMODE_M1       0x004
#घोषणा VIA_REG_GESTATUS_M1     0x004       /* as same as VIA_REG_GEMODE */
#घोषणा VIA_REG_PITCH_M1        0x008       /* pitch of src and dst */
#घोषणा VIA_REG_DIMENSION_M1    0x00C       /* width and height */
#घोषणा VIA_REG_DSTPOS_M1       0x010
#घोषणा VIA_REG_LINE_XY_M1      0x010
#घोषणा VIA_REG_DSTBASE_M1      0x014
#घोषणा VIA_REG_SRCPOS_M1       0x018
#घोषणा VIA_REG_LINE_K1K2_M1    0x018
#घोषणा VIA_REG_SRCBASE_M1      0x01C
#घोषणा VIA_REG_PATADDR_M1      0x020
#घोषणा VIA_REG_MONOPAT0_M1     0x024
#घोषणा VIA_REG_MONOPAT1_M1     0x028
#घोषणा VIA_REG_OFFSET_M1       0x02C
#घोषणा VIA_REG_LINE_ERROR_M1   0x02C
#घोषणा VIA_REG_CLIPTL_M1       0x040       /* top and left of clipping */
#घोषणा VIA_REG_CLIPBR_M1       0x044       /* bottom and right of clipping */
#घोषणा VIA_REG_KEYCONTROL_M1   0x048       /* color key control */
#घोषणा VIA_REG_FGCOLOR_M1      0x04C
#घोषणा VIA_REG_DSTCOLORKEY_M1  0x04C       /* as same as VIA_REG_FG */
#घोषणा VIA_REG_BGCOLOR_M1      0x050
#घोषणा VIA_REG_SRCCOLORKEY_M1  0x050       /* as same as VIA_REG_BG */
#घोषणा VIA_REG_MONOPATFGC_M1   0x058       /* Add BG color of Pattern. */
#घोषणा VIA_REG_MONOPATBGC_M1   0x05C       /* Add FG color of Pattern. */
#घोषणा VIA_REG_COLORPAT_M1     0x100       /* from 0x100 to 0x1ff */

/* VIA_REG_PITCH(0x38): Pitch Setting */
#घोषणा VIA_PITCH_ENABLE        0x80000000

/* defines क्रम VIA HW cursor रेजिस्टरs */
#घोषणा VIA_REG_CURSOR_MODE     0x2D0
#घोषणा VIA_REG_CURSOR_POS      0x2D4
#घोषणा VIA_REG_CURSOR_ORG      0x2D8
#घोषणा VIA_REG_CURSOR_BG       0x2DC
#घोषणा VIA_REG_CURSOR_FG       0x2E0

/* VIA_REG_GEMODE(0x04): GE mode */
#घोषणा VIA_GEM_8bpp            0x00000000
#घोषणा VIA_GEM_16bpp           0x00000100
#घोषणा VIA_GEM_32bpp           0x00000300

/* VIA_REG_GECMD(0x00): 2D Engine Command  */
#घोषणा VIA_GEC_NOOP            0x00000000
#घोषणा VIA_GEC_BLT             0x00000001
#घोषणा VIA_GEC_LINE            0x00000005

/* Rotate Command */
#घोषणा VIA_GEC_ROT             0x00000008

#घोषणा VIA_GEC_SRC_XY          0x00000000
#घोषणा VIA_GEC_SRC_LINEAR      0x00000010
#घोषणा VIA_GEC_DST_XY          0x00000000
#घोषणा VIA_GEC_DST_LINRAT      0x00000020

#घोषणा VIA_GEC_SRC_FB          0x00000000
#घोषणा VIA_GEC_SRC_SYS         0x00000040
#घोषणा VIA_GEC_DST_FB          0x00000000
#घोषणा VIA_GEC_DST_SYS         0x00000080

/* source is mono */
#घोषणा VIA_GEC_SRC_MONO        0x00000100
/* pattern is mono */
#घोषणा VIA_GEC_PAT_MONO        0x00000200
/* mono src is opaque */
#घोषणा VIA_GEC_MSRC_OPAQUE     0x00000000
/* mono src is transparent */
#घोषणा VIA_GEC_MSRC_TRANS      0x00000400
/* pattern is in frame buffer */
#घोषणा VIA_GEC_PAT_FB          0x00000000
/* pattern is from reg setting */
#घोषणा VIA_GEC_PAT_REG         0x00000800

#घोषणा VIA_GEC_CLIP_DISABLE    0x00000000
#घोषणा VIA_GEC_CLIP_ENABLE     0x00001000

#घोषणा VIA_GEC_FIXCOLOR_PAT    0x00002000

#घोषणा VIA_GEC_INCX            0x00000000
#घोषणा VIA_GEC_DECY            0x00004000
#घोषणा VIA_GEC_INCY            0x00000000
#घोषणा VIA_GEC_DECX            0x00008000
/* mono pattern is opaque */
#घोषणा VIA_GEC_MPAT_OPAQUE     0x00000000
/* mono pattern is transparent */
#घोषणा VIA_GEC_MPAT_TRANS      0x00010000

#घोषणा VIA_GEC_MONO_UNPACK     0x00000000
#घोषणा VIA_GEC_MONO_PACK       0x00020000
#घोषणा VIA_GEC_MONO_DWORD      0x00000000
#घोषणा VIA_GEC_MONO_WORD       0x00040000
#घोषणा VIA_GEC_MONO_BYTE       0x00080000

#घोषणा VIA_GEC_LASTPIXEL_ON    0x00000000
#घोषणा VIA_GEC_LASTPIXEL_OFF   0x00100000
#घोषणा VIA_GEC_X_MAJOR         0x00000000
#घोषणा VIA_GEC_Y_MAJOR         0x00200000
#घोषणा VIA_GEC_QUICK_START     0x00800000

/* defines क्रम VIA 3D रेजिस्टरs */
#घोषणा VIA_REG_STATUS          0x400
#घोषणा VIA_REG_CR_TRANSET      0x41C
#घोषणा VIA_REG_CR_TRANSPACE	0x420
#घोषणा VIA_REG_TRANSET         0x43C
#घोषणा VIA_REG_TRANSPACE       0x440

/* VIA_REG_STATUS(0x400): Engine Status */

/* Command Regulator is busy */
#घोषणा VIA_CMD_RGTR_BUSY       0x00000080
/* 2D Engine is busy */
#घोषणा VIA_2D_ENG_BUSY         0x00000002
/* 3D Engine is busy */
#घोषणा VIA_3D_ENG_BUSY         0x00000001
/* Virtual Queue is busy */
#घोषणा VIA_VR_QUEUE_BUSY       0x00020000

/* VIA_REG_STATUS(0x400): Engine Status क्रम H5 */
#घोषणा VIA_CMD_RGTR_BUSY_H5   0x00000010  /* Command Regulator is busy */
#घोषणा VIA_2D_ENG_BUSY_H5     0x00000002  /* 2D Engine is busy */
#घोषणा VIA_3D_ENG_BUSY_H5     0x00001FE1  /* 3D Engine is busy */
#घोषणा VIA_VR_QUEUE_BUSY_H5   0x00000004  /* Virtual Queue is busy */

/* VIA_REG_STATUS(0x400): Engine Status क्रम VT3353/3409 */
#घोषणा VIA_CMD_RGTR_BUSY_M1   0x00000010  /* Command Regulator is busy */
#घोषणा VIA_2D_ENG_BUSY_M1     0x00000002  /* 2D Engine is busy */
#घोषणा VIA_3D_ENG_BUSY_M1     0x00001FE1  /* 3D Engine is busy */
#घोषणा VIA_VR_QUEUE_BUSY_M1   0x00000004  /* Virtual Queue is busy */

#घोषणा MAXLOOP                 0xFFFFFF

#घोषणा VIA_BITBLT_COLOR	1
#घोषणा VIA_BITBLT_MONO		2
#घोषणा VIA_BITBLT_FILL		3

पूर्णांक viafb_setup_engine(काष्ठा fb_info *info);
व्योम viafb_reset_engine(काष्ठा viafb_par *viapar);
व्योम viafb_show_hw_cursor(काष्ठा fb_info *info, पूर्णांक Status);
व्योम viafb_रुको_engine_idle(काष्ठा fb_info *info);

#पूर्ण_अगर /* __ACCEL_H__ */
