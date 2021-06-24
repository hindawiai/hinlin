<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Media Bus API header
 *
 * Copyright (C) 2009, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __LINUX_MEDIA_BUS_FORMAT_H
#घोषणा __LINUX_MEDIA_BUS_FORMAT_H

/*
 * These bus क्रमmats uniquely identअगरy data क्रमmats on the data bus. Format 0
 * is reserved, MEDIA_BUS_FMT_FIXED shall be used by host-client pairs, where
 * the data क्रमmat is fixed. Additionally, "2X8" means that one pixel is
 * transferred in two 8-bit samples, "BE" or "LE" specअगरy in which order those
 * samples are transferred over the bus: "LE" means that the least signअगरicant
 * bits are transferred first, "BE" means that the most signअगरicant bits are
 * transferred first, and "PADHI" and "PADLO" define which bits - low or high,
 * in the incomplete high byte, are filled with padding bits.
 *
 * The bus क्रमmats are grouped by type, bus_width, bits per component, samples
 * per pixel and order of subsamples. Numerical values are sorted using generic
 * numerical sort order (8 thus comes beक्रमe 10).
 *
 * As their value can't change when a new bus क्रमmat is inserted in the
 * क्रमागतeration, the bus क्रमmats are explicitly given a numerical value. The next
 * मुक्त values क्रम each category are listed below, update them when inserting
 * new pixel codes.
 */

#घोषणा MEDIA_BUS_FMT_FIXED			0x0001

/* RGB - next is	0x101e */
#घोषणा MEDIA_BUS_FMT_RGB444_1X12		0x1016
#घोषणा MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE	0x1001
#घोषणा MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE	0x1002
#घोषणा MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE	0x1003
#घोषणा MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE	0x1004
#घोषणा MEDIA_BUS_FMT_RGB565_1X16		0x1017
#घोषणा MEDIA_BUS_FMT_BGR565_2X8_BE		0x1005
#घोषणा MEDIA_BUS_FMT_BGR565_2X8_LE		0x1006
#घोषणा MEDIA_BUS_FMT_RGB565_2X8_BE		0x1007
#घोषणा MEDIA_BUS_FMT_RGB565_2X8_LE		0x1008
#घोषणा MEDIA_BUS_FMT_RGB666_1X18		0x1009
#घोषणा MEDIA_BUS_FMT_RBG888_1X24		0x100e
#घोषणा MEDIA_BUS_FMT_RGB666_1X24_CPADHI	0x1015
#घोषणा MEDIA_BUS_FMT_RGB666_1X7X3_SPWG		0x1010
#घोषणा MEDIA_BUS_FMT_BGR888_1X24		0x1013
#घोषणा MEDIA_BUS_FMT_BGR888_3X8		0x101b
#घोषणा MEDIA_BUS_FMT_GBR888_1X24		0x1014
#घोषणा MEDIA_BUS_FMT_RGB888_1X24		0x100a
#घोषणा MEDIA_BUS_FMT_RGB888_2X12_BE		0x100b
#घोषणा MEDIA_BUS_FMT_RGB888_2X12_LE		0x100c
#घोषणा MEDIA_BUS_FMT_RGB888_3X8		0x101c
#घोषणा MEDIA_BUS_FMT_RGB888_3X8_DELTA		0x101d
#घोषणा MEDIA_BUS_FMT_RGB888_1X7X4_SPWG		0x1011
#घोषणा MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA	0x1012
#घोषणा MEDIA_BUS_FMT_ARGB8888_1X32		0x100d
#घोषणा MEDIA_BUS_FMT_RGB888_1X32_PADHI		0x100f
#घोषणा MEDIA_BUS_FMT_RGB101010_1X30		0x1018
#घोषणा MEDIA_BUS_FMT_RGB121212_1X36		0x1019
#घोषणा MEDIA_BUS_FMT_RGB161616_1X48		0x101a

/* YUV (including grey) - next is	0x202e */
#घोषणा MEDIA_BUS_FMT_Y8_1X8			0x2001
#घोषणा MEDIA_BUS_FMT_UV8_1X8			0x2015
#घोषणा MEDIA_BUS_FMT_UYVY8_1_5X8		0x2002
#घोषणा MEDIA_BUS_FMT_VYUY8_1_5X8		0x2003
#घोषणा MEDIA_BUS_FMT_YUYV8_1_5X8		0x2004
#घोषणा MEDIA_BUS_FMT_YVYU8_1_5X8		0x2005
#घोषणा MEDIA_BUS_FMT_UYVY8_2X8			0x2006
#घोषणा MEDIA_BUS_FMT_VYUY8_2X8			0x2007
#घोषणा MEDIA_BUS_FMT_YUYV8_2X8			0x2008
#घोषणा MEDIA_BUS_FMT_YVYU8_2X8			0x2009
#घोषणा MEDIA_BUS_FMT_Y10_1X10			0x200a
#घोषणा MEDIA_BUS_FMT_Y10_2X8_PADHI_LE		0x202c
#घोषणा MEDIA_BUS_FMT_UYVY10_2X10		0x2018
#घोषणा MEDIA_BUS_FMT_VYUY10_2X10		0x2019
#घोषणा MEDIA_BUS_FMT_YUYV10_2X10		0x200b
#घोषणा MEDIA_BUS_FMT_YVYU10_2X10		0x200c
#घोषणा MEDIA_BUS_FMT_Y12_1X12			0x2013
#घोषणा MEDIA_BUS_FMT_UYVY12_2X12		0x201c
#घोषणा MEDIA_BUS_FMT_VYUY12_2X12		0x201d
#घोषणा MEDIA_BUS_FMT_YUYV12_2X12		0x201e
#घोषणा MEDIA_BUS_FMT_YVYU12_2X12		0x201f
#घोषणा MEDIA_BUS_FMT_Y14_1X14			0x202d
#घोषणा MEDIA_BUS_FMT_UYVY8_1X16		0x200f
#घोषणा MEDIA_BUS_FMT_VYUY8_1X16		0x2010
#घोषणा MEDIA_BUS_FMT_YUYV8_1X16		0x2011
#घोषणा MEDIA_BUS_FMT_YVYU8_1X16		0x2012
#घोषणा MEDIA_BUS_FMT_YDYUYDYV8_1X16		0x2014
#घोषणा MEDIA_BUS_FMT_UYVY10_1X20		0x201a
#घोषणा MEDIA_BUS_FMT_VYUY10_1X20		0x201b
#घोषणा MEDIA_BUS_FMT_YUYV10_1X20		0x200d
#घोषणा MEDIA_BUS_FMT_YVYU10_1X20		0x200e
#घोषणा MEDIA_BUS_FMT_VUY8_1X24			0x2024
#घोषणा MEDIA_BUS_FMT_YUV8_1X24			0x2025
#घोषणा MEDIA_BUS_FMT_UYYVYY8_0_5X24		0x2026
#घोषणा MEDIA_BUS_FMT_UYVY12_1X24		0x2020
#घोषणा MEDIA_BUS_FMT_VYUY12_1X24		0x2021
#घोषणा MEDIA_BUS_FMT_YUYV12_1X24		0x2022
#घोषणा MEDIA_BUS_FMT_YVYU12_1X24		0x2023
#घोषणा MEDIA_BUS_FMT_YUV10_1X30		0x2016
#घोषणा MEDIA_BUS_FMT_UYYVYY10_0_5X30		0x2027
#घोषणा MEDIA_BUS_FMT_AYUV8_1X32		0x2017
#घोषणा MEDIA_BUS_FMT_UYYVYY12_0_5X36		0x2028
#घोषणा MEDIA_BUS_FMT_YUV12_1X36		0x2029
#घोषणा MEDIA_BUS_FMT_YUV16_1X48		0x202a
#घोषणा MEDIA_BUS_FMT_UYYVYY16_0_5X48		0x202b

/* Bayer - next is	0x3021 */
#घोषणा MEDIA_BUS_FMT_SBGGR8_1X8		0x3001
#घोषणा MEDIA_BUS_FMT_SGBRG8_1X8		0x3013
#घोषणा MEDIA_BUS_FMT_SGRBG8_1X8		0x3002
#घोषणा MEDIA_BUS_FMT_SRGGB8_1X8		0x3014
#घोषणा MEDIA_BUS_FMT_SBGGR10_ALAW8_1X8		0x3015
#घोषणा MEDIA_BUS_FMT_SGBRG10_ALAW8_1X8		0x3016
#घोषणा MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8		0x3017
#घोषणा MEDIA_BUS_FMT_SRGGB10_ALAW8_1X8		0x3018
#घोषणा MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8		0x300b
#घोषणा MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8		0x300c
#घोषणा MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8		0x3009
#घोषणा MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8		0x300d
#घोषणा MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE	0x3003
#घोषणा MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE	0x3004
#घोषणा MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_BE	0x3005
#घोषणा MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_LE	0x3006
#घोषणा MEDIA_BUS_FMT_SBGGR10_1X10		0x3007
#घोषणा MEDIA_BUS_FMT_SGBRG10_1X10		0x300e
#घोषणा MEDIA_BUS_FMT_SGRBG10_1X10		0x300a
#घोषणा MEDIA_BUS_FMT_SRGGB10_1X10		0x300f
#घोषणा MEDIA_BUS_FMT_SBGGR12_1X12		0x3008
#घोषणा MEDIA_BUS_FMT_SGBRG12_1X12		0x3010
#घोषणा MEDIA_BUS_FMT_SGRBG12_1X12		0x3011
#घोषणा MEDIA_BUS_FMT_SRGGB12_1X12		0x3012
#घोषणा MEDIA_BUS_FMT_SBGGR14_1X14		0x3019
#घोषणा MEDIA_BUS_FMT_SGBRG14_1X14		0x301a
#घोषणा MEDIA_BUS_FMT_SGRBG14_1X14		0x301b
#घोषणा MEDIA_BUS_FMT_SRGGB14_1X14		0x301c
#घोषणा MEDIA_BUS_FMT_SBGGR16_1X16		0x301d
#घोषणा MEDIA_BUS_FMT_SGBRG16_1X16		0x301e
#घोषणा MEDIA_BUS_FMT_SGRBG16_1X16		0x301f
#घोषणा MEDIA_BUS_FMT_SRGGB16_1X16		0x3020

/* JPEG compressed क्रमmats - next is	0x4002 */
#घोषणा MEDIA_BUS_FMT_JPEG_1X8			0x4001

/* Venकरोr specअगरic क्रमmats - next is	0x5002 */

/* S5C73M3 sensor specअगरic पूर्णांकerleaved UYVY and JPEG */
#घोषणा MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8		0x5001

/* HSV - next is	0x6002 */
#घोषणा MEDIA_BUS_FMT_AHSV8888_1X32		0x6001

/*
 * This क्रमmat should be used when the same driver handles
 * both sides of the link and the bus क्रमmat is a fixed
 * metadata क्रमmat that is not configurable from userspace.
 * Width and height will be set to 0 क्रम this क्रमmat.
 */
#घोषणा MEDIA_BUS_FMT_METADATA_FIXED		0x7001

#पूर्ण_अगर /* __LINUX_MEDIA_BUS_FORMAT_H */
