<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __SHARE_H__
#घोषणा __SHARE_H__

#समावेश "via_modesetting.h"

/* Define Bit Field */
#घोषणा BIT0    0x01
#घोषणा BIT1    0x02
#घोषणा BIT2    0x04
#घोषणा BIT3    0x08
#घोषणा BIT4    0x10
#घोषणा BIT5    0x20
#घोषणा BIT6    0x40
#घोषणा BIT7    0x80

/* Video Memory Size */
#घोषणा VIDEO_MEMORY_SIZE_16M    0x1000000

/*
 * Lengths of the VPIT काष्ठाure arrays.
 */
#घोषणा StdCR       0x19
#घोषणा StdSR       0x04
#घोषणा StdGR       0x09
#घोषणा StdAR       0x14

#घोषणा PatchCR     11

/* Display path */
#घोषणा IGA1        1
#घोषणा IGA2        2

/* Define Color Depth  */
#घोषणा MODE_8BPP       1
#घोषणा MODE_16BPP      2
#घोषणा MODE_32BPP      4

#घोषणा GR20    0x20
#घोषणा GR21    0x21
#घोषणा GR22    0x22

/* Sequencer Registers */
#घोषणा SR01    0x01
#घोषणा SR10    0x10
#घोषणा SR12    0x12
#घोषणा SR15    0x15
#घोषणा SR16    0x16
#घोषणा SR17    0x17
#घोषणा SR18    0x18
#घोषणा SR1B    0x1B
#घोषणा SR1A    0x1A
#घोषणा SR1C    0x1C
#घोषणा SR1D    0x1D
#घोषणा SR1E    0x1E
#घोषणा SR1F    0x1F
#घोषणा SR20    0x20
#घोषणा SR21    0x21
#घोषणा SR22    0x22
#घोषणा SR2A    0x2A
#घोषणा SR2D    0x2D
#घोषणा SR2E    0x2E

#घोषणा SR30    0x30
#घोषणा SR39    0x39
#घोषणा SR3D    0x3D
#घोषणा SR3E    0x3E
#घोषणा SR3F    0x3F
#घोषणा SR40    0x40
#घोषणा SR43    0x43
#घोषणा SR44    0x44
#घोषणा SR45    0x45
#घोषणा SR46    0x46
#घोषणा SR47    0x47
#घोषणा SR48    0x48
#घोषणा SR49    0x49
#घोषणा SR4A    0x4A
#घोषणा SR4B    0x4B
#घोषणा SR4C    0x4C
#घोषणा SR52    0x52
#घोषणा SR57	0x57
#घोषणा SR58	0x58
#घोषणा SR59	0x59
#घोषणा SR5D    0x5D
#घोषणा SR5E    0x5E
#घोषणा SR65    0x65

/* CRT Controller Registers */
#घोषणा CR00    0x00
#घोषणा CR01    0x01
#घोषणा CR02    0x02
#घोषणा CR03    0x03
#घोषणा CR04    0x04
#घोषणा CR05    0x05
#घोषणा CR06    0x06
#घोषणा CR07    0x07
#घोषणा CR08    0x08
#घोषणा CR09    0x09
#घोषणा CR0A    0x0A
#घोषणा CR0B    0x0B
#घोषणा CR0C    0x0C
#घोषणा CR0D    0x0D
#घोषणा CR0E    0x0E
#घोषणा CR0F    0x0F
#घोषणा CR10    0x10
#घोषणा CR11    0x11
#घोषणा CR12    0x12
#घोषणा CR13    0x13
#घोषणा CR14    0x14
#घोषणा CR15    0x15
#घोषणा CR16    0x16
#घोषणा CR17    0x17
#घोषणा CR18    0x18

/* Extend CRT Controller Registers */
#घोषणा CR30    0x30
#घोषणा CR31    0x31
#घोषणा CR32    0x32
#घोषणा CR33    0x33
#घोषणा CR34    0x34
#घोषणा CR35    0x35
#घोषणा CR36    0x36
#घोषणा CR37    0x37
#घोषणा CR38    0x38
#घोषणा CR39    0x39
#घोषणा CR3A    0x3A
#घोषणा CR3B    0x3B
#घोषणा CR3C    0x3C
#घोषणा CR3D    0x3D
#घोषणा CR3E    0x3E
#घोषणा CR3F    0x3F
#घोषणा CR40    0x40
#घोषणा CR41    0x41
#घोषणा CR42    0x42
#घोषणा CR43    0x43
#घोषणा CR44    0x44
#घोषणा CR45    0x45
#घोषणा CR46    0x46
#घोषणा CR47    0x47
#घोषणा CR48    0x48
#घोषणा CR49    0x49
#घोषणा CR4A    0x4A
#घोषणा CR4B    0x4B
#घोषणा CR4C    0x4C
#घोषणा CR4D    0x4D
#घोषणा CR4E    0x4E
#घोषणा CR4F    0x4F
#घोषणा CR50    0x50
#घोषणा CR51    0x51
#घोषणा CR52    0x52
#घोषणा CR53    0x53
#घोषणा CR54    0x54
#घोषणा CR55    0x55
#घोषणा CR56    0x56
#घोषणा CR57    0x57
#घोषणा CR58    0x58
#घोषणा CR59    0x59
#घोषणा CR5A    0x5A
#घोषणा CR5B    0x5B
#घोषणा CR5C    0x5C
#घोषणा CR5D    0x5D
#घोषणा CR5E    0x5E
#घोषणा CR5F    0x5F
#घोषणा CR60    0x60
#घोषणा CR61    0x61
#घोषणा CR62    0x62
#घोषणा CR63    0x63
#घोषणा CR64    0x64
#घोषणा CR65    0x65
#घोषणा CR66    0x66
#घोषणा CR67    0x67
#घोषणा CR68    0x68
#घोषणा CR69    0x69
#घोषणा CR6A    0x6A
#घोषणा CR6B    0x6B
#घोषणा CR6C    0x6C
#घोषणा CR6D    0x6D
#घोषणा CR6E    0x6E
#घोषणा CR6F    0x6F
#घोषणा CR70    0x70
#घोषणा CR71    0x71
#घोषणा CR72    0x72
#घोषणा CR73    0x73
#घोषणा CR74    0x74
#घोषणा CR75    0x75
#घोषणा CR76    0x76
#घोषणा CR77    0x77
#घोषणा CR78    0x78
#घोषणा CR79    0x79
#घोषणा CR7A    0x7A
#घोषणा CR7B    0x7B
#घोषणा CR7C    0x7C
#घोषणा CR7D    0x7D
#घोषणा CR7E    0x7E
#घोषणा CR7F    0x7F
#घोषणा CR80    0x80
#घोषणा CR81    0x81
#घोषणा CR82    0x82
#घोषणा CR83    0x83
#घोषणा CR84    0x84
#घोषणा CR85    0x85
#घोषणा CR86    0x86
#घोषणा CR87    0x87
#घोषणा CR88    0x88
#घोषणा CR89    0x89
#घोषणा CR8A    0x8A
#घोषणा CR8B    0x8B
#घोषणा CR8C    0x8C
#घोषणा CR8D    0x8D
#घोषणा CR8E    0x8E
#घोषणा CR8F    0x8F
#घोषणा CR90    0x90
#घोषणा CR91    0x91
#घोषणा CR92    0x92
#घोषणा CR93    0x93
#घोषणा CR94    0x94
#घोषणा CR95    0x95
#घोषणा CR96    0x96
#घोषणा CR97    0x97
#घोषणा CR98    0x98
#घोषणा CR99    0x99
#घोषणा CR9A    0x9A
#घोषणा CR9B    0x9B
#घोषणा CR9C    0x9C
#घोषणा CR9D    0x9D
#घोषणा CR9E    0x9E
#घोषणा CR9F    0x9F
#घोषणा CRA0    0xA0
#घोषणा CRA1    0xA1
#घोषणा CRA2    0xA2
#घोषणा CRA3    0xA3
#घोषणा CRD2    0xD2
#घोषणा CRD3    0xD3
#घोषणा CRD4    0xD4

/* LUT Table*/
#घोषणा LUT_DATA             0x3C9	/* DACDATA */
#घोषणा LUT_INDEX_READ       0x3C7	/* DACRX */
#घोषणा LUT_INDEX_WRITE      0x3C8	/* DACWX */
#घोषणा DACMASK              0x3C6

/* Definition Device */
#घोषणा DEVICE_CRT  0x01
#घोषणा DEVICE_DVI  0x03
#घोषणा DEVICE_LCD  0x04

/* Device output पूर्णांकerface */
#घोषणा INTERFACE_NONE          0x00
#घोषणा INTERFACE_ANALOG_RGB    0x01
#घोषणा INTERFACE_DVP0          0x02
#घोषणा INTERFACE_DVP1          0x03
#घोषणा INTERFACE_DFP_HIGH      0x04
#घोषणा INTERFACE_DFP_LOW       0x05
#घोषणा INTERFACE_DFP           0x06
#घोषणा INTERFACE_LVDS0         0x07
#घोषणा INTERFACE_LVDS1         0x08
#घोषणा INTERFACE_LVDS0LVDS1    0x09
#घोषणा INTERFACE_TMDS          0x0A

#घोषणा HW_LAYOUT_LCD_ONLY      0x01
#घोषणा HW_LAYOUT_DVI_ONLY      0x02
#घोषणा HW_LAYOUT_LCD_DVI       0x03
#घोषणा HW_LAYOUT_LCD1_LCD2     0x04
#घोषणा HW_LAYOUT_LCD_EXTERNAL_LCD2 0x10

/* Definition CRTC Timing Index */
#घोषणा H_TOTAL_INDEX               0
#घोषणा H_ADDR_INDEX                1
#घोषणा H_BLANK_START_INDEX         2
#घोषणा H_BLANK_END_INDEX           3
#घोषणा H_SYNC_START_INDEX          4
#घोषणा H_SYNC_END_INDEX            5
#घोषणा V_TOTAL_INDEX               6
#घोषणा V_ADDR_INDEX                7
#घोषणा V_BLANK_START_INDEX         8
#घोषणा V_BLANK_END_INDEX           9
#घोषणा V_SYNC_START_INDEX          10
#घोषणा V_SYNC_END_INDEX            11
#घोषणा H_TOTAL_SHADOW_INDEX        12
#घोषणा H_BLANK_END_SHADOW_INDEX    13
#घोषणा V_TOTAL_SHADOW_INDEX        14
#घोषणा V_ADDR_SHADOW_INDEX         15
#घोषणा V_BLANK_SATRT_SHADOW_INDEX  16
#घोषणा V_BLANK_END_SHADOW_INDEX    17
#घोषणा V_SYNC_SATRT_SHADOW_INDEX   18
#घोषणा V_SYNC_END_SHADOW_INDEX     19

/* LCD display method
*/
#घोषणा     LCD_EXPANDSION              0x00
#घोषणा     LCD_CENTERING               0x01

/* LCD mode
*/
#घोषणा     LCD_OPENLDI               0x00
#घोषणा     LCD_SPWG                  0x01

काष्ठा crt_mode_table अणु
	पूर्णांक refresh_rate;
	पूर्णांक h_sync_polarity;
	पूर्णांक v_sync_polarity;
	काष्ठा via_display_timing crtc;
पूर्ण;

काष्ठा io_reg अणु
	पूर्णांक port;
	u8 index;
	u8 mask;
	u8 value;
पूर्ण;

#पूर्ण_अगर /* __SHARE_H__ */
