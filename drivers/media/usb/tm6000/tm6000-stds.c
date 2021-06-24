<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// पंचांग6000-stds.c - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
//
// Copyright (c) 2007 Mauro Carvalho Chehab <mchehab@kernel.org>

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश "tm6000.h"
#समावेश "tm6000-regs.h"

अटल अचिन्हित पूर्णांक पंचांग6010_a_mode;
module_param(पंचांग6010_a_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(पंचांग6010_a_mode, "set tm6010 sif audio mode");

काष्ठा पंचांग6000_reg_settings अणु
	अचिन्हित अक्षर req;
	अचिन्हित अक्षर reg;
	अचिन्हित अक्षर value;
पूर्ण;


काष्ठा पंचांग6000_std_settings अणु
	v4l2_std_id id;
	काष्ठा पंचांग6000_reg_settings *common;
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings composite_pal_m[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x04 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x00 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x83 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0x0a पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xe0 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x88 पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x20 पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0x61 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x0c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x52 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdc पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings composite_pal_nc[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x36 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x02 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x91 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0x1f पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0x0c पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x8c पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x2c पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0xc1 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x0c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x52 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdc पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings composite_pal[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x32 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x02 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x25 पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0xd5 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0x63 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0x50 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x8c पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x2c पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0xc1 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x0c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x52 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdc पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings composite_secam[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x38 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x02 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x24 पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x92 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0xe8 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xed पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x8c पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x2c पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0xc1 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x2c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x18 पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x42 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0xff पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings composite_ntsc[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x00 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0f पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x00 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x8b पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0xa2 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xe9 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x88 पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x22 पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0x61 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x42 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdd पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_std_settings composite_stds[] = अणु
	अणु .id = V4L2_STD_PAL_M, .common = composite_pal_m, पूर्ण,
	अणु .id = V4L2_STD_PAL_Nc, .common = composite_pal_nc, पूर्ण,
	अणु .id = V4L2_STD_PAL, .common = composite_pal, पूर्ण,
	अणु .id = V4L2_STD_SECAM, .common = composite_secam, पूर्ण,
	अणु .id = V4L2_STD_NTSC, .common = composite_ntsc, पूर्ण,
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings svideo_pal_m[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x05 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x04 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x83 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0x0a पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xe0 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x88 पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x22 पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0x61 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x0c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x52 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdc पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings svideo_pal_nc[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x37 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x04 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x91 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0x1f पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0x0c पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x88 पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x22 पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0xc1 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x0c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x52 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdc पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings svideo_pal[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x33 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x04 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x30 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x25 पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0xd5 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0x63 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0x50 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x8c पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x2a पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0xc1 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x0c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x52 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdc पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings svideo_secam[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x39 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0e पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x03 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x31 पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x24 पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x92 पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0xe8 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xed पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x8c पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x2a पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0xc1 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x2c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x18 पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x42 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0xff पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_reg_settings svideo_ntsc[] = अणु
	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x01 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x0f पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x03 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x30 पूर्ण,
	अणु TM6010_REQ07_R17_HLOOP_MAXSTATE, 0x8b पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x8b पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0xa2 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xe9 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x88 पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x22 पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0x61 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x42 पूर्ण,
	अणु TM6010_REQ07_R83_CHROMA_LOCK_CONFIG, 0x6f पूर्ण,
	अणु TM6010_REQ07_R04_LUMA_HAGC_CONTROL, 0xdd पूर्ण,
	अणु TM6010_REQ07_R0D_CHROMA_KILL_LEVEL, 0x07 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा पंचांग6000_std_settings svideo_stds[] = अणु
	अणु .id = V4L2_STD_PAL_M, .common = svideo_pal_m, पूर्ण,
	अणु .id = V4L2_STD_PAL_Nc, .common = svideo_pal_nc, पूर्ण,
	अणु .id = V4L2_STD_PAL, .common = svideo_pal, पूर्ण,
	अणु .id = V4L2_STD_SECAM, .common = svideo_secam, पूर्ण,
	अणु .id = V4L2_STD_NTSC, .common = svideo_ntsc, पूर्ण,
पूर्ण;

अटल पूर्णांक पंचांग6000_set_audio_std(काष्ठा पंचांग6000_core *dev)
अणु
	uपूर्णांक8_t areg_02 = 0x04; /* GC1 Fixed gain 0dB */
	uपूर्णांक8_t areg_05 = 0x01; /* Auto 4.5 = M Japan, Auto 6.5 = DK */
	uपूर्णांक8_t areg_06 = 0x02; /* Auto de-emphasis, manual channel mode */

	अगर (dev->radio) अणु
		पंचांग6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x00);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R02_A_FIX_GAIN_CTRL, 0x04);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R03_A_AUTO_GAIN_CTRL, 0x00);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R04_A_SIF_AMP_CTRL, 0x80);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R05_A_STANDARD_MOD, 0x0c);
		/* set mono or stereo */
		अगर (dev->amode == V4L2_TUNER_MODE_MONO)
			पंचांग6000_set_reg(dev, TM6010_REQ08_R06_A_SOUND_MOD, 0x00);
		अन्यथा अगर (dev->amode == V4L2_TUNER_MODE_STEREO)
			पंचांग6000_set_reg(dev, TM6010_REQ08_R06_A_SOUND_MOD, 0x02);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R09_A_MAIN_VOL, 0x18);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R0C_A_ASD_THRES2, 0x0a);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R0D_A_AMD_THRES, 0x40);
		पंचांग6000_set_reg(dev, TM6010_REQ08_RF1_AADC_POWER_DOWN, 0xfe);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R1E_A_GAIN_DEEMPH_OUT, 0x13);
		पंचांग6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x80);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RFE_POWER_DOWN, 0xff);
		वापस 0;
	पूर्ण

	/*
	 * STD/MN shouldn't be affected by tm6010_a_mode, as there's just one
	 * audio standard क्रम each V4L2_STD type.
	 */
	अगर ((dev->norm & V4L2_STD_NTSC) == V4L2_STD_NTSC_M_KR) अणु
		areg_05 |= 0x04;
	पूर्ण अन्यथा अगर ((dev->norm & V4L2_STD_NTSC) == V4L2_STD_NTSC_M_JP) अणु
		areg_05 |= 0x43;
	पूर्ण अन्यथा अगर (dev->norm & V4L2_STD_MN) अणु
		areg_05 |= 0x22;
	पूर्ण अन्यथा चयन (पंचांग6010_a_mode) अणु
	/* स्वतः */
	हाल 0:
		अगर ((dev->norm & V4L2_STD_SECAM) == V4L2_STD_SECAM_L)
			areg_05 |= 0x00;
		अन्यथा	/* Other PAL/SECAM standards */
			areg_05 |= 0x10;
		अवरोध;
	/* A2 */
	हाल 1:
		अगर (dev->norm & V4L2_STD_DK)
			areg_05 = 0x09;
		अन्यथा
			areg_05 = 0x05;
		अवरोध;
	/* NICAM */
	हाल 2:
		अगर (dev->norm & V4L2_STD_DK) अणु
			areg_05 = 0x06;
		पूर्ण अन्यथा अगर (dev->norm & V4L2_STD_PAL_I) अणु
			areg_05 = 0x08;
		पूर्ण अन्यथा अगर (dev->norm & V4L2_STD_SECAM_L) अणु
			areg_05 = 0x0a;
			areg_02 = 0x02;
		पूर्ण अन्यथा अणु
			areg_05 = 0x07;
		पूर्ण
		अवरोध;
	/* other */
	हाल 3:
		अगर (dev->norm & V4L2_STD_DK) अणु
			areg_05 = 0x0b;
		पूर्ण अन्यथा अणु
			areg_05 = 0x02;
		पूर्ण
		अवरोध;
	पूर्ण

	पंचांग6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x00);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R02_A_FIX_GAIN_CTRL, areg_02);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R03_A_AUTO_GAIN_CTRL, 0x00);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R04_A_SIF_AMP_CTRL, 0xa0);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R05_A_STANDARD_MOD, areg_05);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R06_A_SOUND_MOD, areg_06);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R07_A_LEFT_VOL, 0x00);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R08_A_RIGHT_VOL, 0x00);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R09_A_MAIN_VOL, 0x08);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R0A_A_I2S_MOD, 0x91);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R0B_A_ASD_THRES1, 0x20);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R0C_A_ASD_THRES2, 0x12);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R0D_A_AMD_THRES, 0x20);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R0E_A_MONO_THRES1, 0xf0);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R0F_A_MONO_THRES2, 0x80);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R10_A_MUTE_THRES1, 0xc0);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R11_A_MUTE_THRES2, 0x80);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R12_A_AGC_U, 0x12);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R13_A_AGC_ERR_T, 0xfe);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R14_A_AGC_GAIN_INIT, 0x20);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R15_A_AGC_STEP_THR, 0x14);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R16_A_AGC_GAIN_MAX, 0xfe);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R17_A_AGC_GAIN_MIN, 0x01);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R18_A_TR_CTRL, 0xa0);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R19_A_FH_2FH_GAIN, 0x32);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R1A_A_NICAM_SER_MAX, 0x64);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R1B_A_NICAM_SER_MIN, 0x20);
	पंचांग6000_set_reg(dev, REQ_08_SET_GET_AVREG_BIT, 0x1c, 0x00);
	पंचांग6000_set_reg(dev, REQ_08_SET_GET_AVREG_BIT, 0x1d, 0x00);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R1E_A_GAIN_DEEMPH_OUT, 0x13);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R1F_A_TEST_INTF_SEL, 0x00);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R20_A_TEST_PIN_SEL, 0x00);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x80);

	वापस 0;
पूर्ण

व्योम पंचांग6000_get_std_res(काष्ठा पंचांग6000_core *dev)
अणु
	/* Currently, those are the only supported resoltions */
	अगर (dev->norm & V4L2_STD_525_60)
		dev->height = 480;
	अन्यथा
		dev->height = 576;

	dev->width = 720;
पूर्ण

अटल पूर्णांक पंचांग6000_load_std(काष्ठा पंचांग6000_core *dev, काष्ठा पंचांग6000_reg_settings *set)
अणु
	पूर्णांक i, rc;

	/* Load board's initialization table */
	क्रम (i = 0; set[i].req; i++) अणु
		rc = पंचांग6000_set_reg(dev, set[i].req, set[i].reg, set[i].value);
		अगर (rc < 0) अणु
			prपूर्णांकk(KERN_ERR "Error %i while setting req %d, reg %d to value %d\n",
			       rc, set[i].req, set[i].reg, set[i].value);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पंचांग6000_set_standard(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_input *input;
	पूर्णांक i, rc = 0;
	u8 reg_07_fe = 0x8a;
	u8 reg_08_f1 = 0xfc;
	u8 reg_08_e2 = 0xf0;
	u8 reg_08_e6 = 0x0f;

	पंचांग6000_get_std_res(dev);

	अगर (!dev->radio)
		input = &dev->vinput[dev->input];
	अन्यथा
		input = &dev->rinput;

	अगर (dev->dev_type == TM6010) अणु
		चयन (input->vmux) अणु
		हाल TM6000_VMUX_VIDEO_A:
			पंचांग6000_set_reg(dev, TM6010_REQ08_RE3_ADC_IN1_SEL, 0xf4);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REA_BUFF_DRV_CTRL, 0xf1);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REB_SIF_GAIN_CTRL, 0xe0);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REC_REVERSE_YC_CTRL, 0xc2);
			पंचांग6000_set_reg(dev, TM6010_REQ08_RED_GAIN_SEL, 0xe8);
			reg_07_fe |= 0x01;
			अवरोध;
		हाल TM6000_VMUX_VIDEO_B:
			पंचांग6000_set_reg(dev, TM6010_REQ08_RE3_ADC_IN1_SEL, 0xf8);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REA_BUFF_DRV_CTRL, 0xf1);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REB_SIF_GAIN_CTRL, 0xe0);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REC_REVERSE_YC_CTRL, 0xc2);
			पंचांग6000_set_reg(dev, TM6010_REQ08_RED_GAIN_SEL, 0xe8);
			reg_07_fe |= 0x01;
			अवरोध;
		हाल TM6000_VMUX_VIDEO_AB:
			पंचांग6000_set_reg(dev, TM6010_REQ08_RE3_ADC_IN1_SEL, 0xfc);
			पंचांग6000_set_reg(dev, TM6010_REQ08_RE4_ADC_IN2_SEL, 0xf8);
			reg_08_e6 = 0x00;
			पंचांग6000_set_reg(dev, TM6010_REQ08_REA_BUFF_DRV_CTRL, 0xf2);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REB_SIF_GAIN_CTRL, 0xf0);
			पंचांग6000_set_reg(dev, TM6010_REQ08_REC_REVERSE_YC_CTRL, 0xc2);
			पंचांग6000_set_reg(dev, TM6010_REQ08_RED_GAIN_SEL, 0xe0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		चयन (input->amux) अणु
		हाल TM6000_AMUX_ADC1:
			पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x00, 0x0f);
			/* Mux overflow workaround */
			पंचांग6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x10, 0xf0);
			अवरोध;
		हाल TM6000_AMUX_ADC2:
			पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x08, 0x0f);
			/* Mux overflow workaround */
			पंचांग6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x10, 0xf0);
			अवरोध;
		हाल TM6000_AMUX_SIF1:
			reg_08_e2 |= 0x02;
			reg_08_e6 = 0x08;
			reg_07_fe |= 0x40;
			reg_08_f1 |= 0x02;
			पंचांग6000_set_reg(dev, TM6010_REQ08_RE4_ADC_IN2_SEL, 0xf3);
			पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x02, 0x0f);
			/* Mux overflow workaround */
			पंचांग6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x30, 0xf0);
			अवरोध;
		हाल TM6000_AMUX_SIF2:
			reg_08_e2 |= 0x02;
			reg_08_e6 = 0x08;
			reg_07_fe |= 0x40;
			reg_08_f1 |= 0x02;
			पंचांग6000_set_reg(dev, TM6010_REQ08_RE4_ADC_IN2_SEL, 0xf7);
			पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x02, 0x0f);
			/* Mux overflow workaround */
			पंचांग6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x30, 0xf0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		पंचांग6000_set_reg(dev, TM6010_REQ08_RE2_POWER_DOWN_CTRL1, reg_08_e2);
		पंचांग6000_set_reg(dev, TM6010_REQ08_RE6_POWER_DOWN_CTRL2, reg_08_e6);
		पंचांग6000_set_reg(dev, TM6010_REQ08_RF1_AADC_POWER_DOWN, reg_08_f1);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RFE_POWER_DOWN, reg_07_fe);
	पूर्ण अन्यथा अणु
		चयन (input->vmux) अणु
		हाल TM6000_VMUX_VIDEO_A:
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE3_VADC_INP_LPF_SEL1, 0x10);
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE5_VADC_INP_LPF_SEL2, 0x00);
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0x0f);
			पंचांग6000_set_reg(dev,
			    REQ_03_SET_GET_MCU_PIN, input->v_gpio, 0);
			अवरोध;
		हाल TM6000_VMUX_VIDEO_B:
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE3_VADC_INP_LPF_SEL1, 0x00);
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE5_VADC_INP_LPF_SEL2, 0x00);
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0x0f);
			पंचांग6000_set_reg(dev,
			    REQ_03_SET_GET_MCU_PIN, input->v_gpio, 0);
			अवरोध;
		हाल TM6000_VMUX_VIDEO_AB:
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE3_VADC_INP_LPF_SEL1, 0x10);
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE5_VADC_INP_LPF_SEL2, 0x10);
			पंचांग6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0x00);
			पंचांग6000_set_reg(dev,
			    REQ_03_SET_GET_MCU_PIN, input->v_gpio, 1);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		चयन (input->amux) अणु
		हाल TM6000_AMUX_ADC1:
			पंचांग6000_set_reg_mask(dev,
				TM6000_REQ07_REB_VADC_AADC_MODE, 0x00, 0x0f);
			अवरोध;
		हाल TM6000_AMUX_ADC2:
			पंचांग6000_set_reg_mask(dev,
				TM6000_REQ07_REB_VADC_AADC_MODE, 0x04, 0x0f);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (input->type == TM6000_INPUT_SVIDEO) अणु
		क्रम (i = 0; i < ARRAY_SIZE(svideo_stds); i++) अणु
			अगर (dev->norm & svideo_stds[i].id) अणु
				rc = पंचांग6000_load_std(dev, svideo_stds[i].common);
				जाओ ret;
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(composite_stds); i++) अणु
			अगर (dev->norm & composite_stds[i].id) अणु
				rc = पंचांग6000_load_std(dev, composite_stds[i].common);
				जाओ ret;
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	पूर्ण

ret:
	अगर (rc < 0)
		वापस rc;

	अगर ((dev->dev_type == TM6010) &&
	    ((input->amux == TM6000_AMUX_SIF1) ||
	    (input->amux == TM6000_AMUX_SIF2)))
		पंचांग6000_set_audio_std(dev);

	msleep(40);

	वापस 0;
पूर्ण
