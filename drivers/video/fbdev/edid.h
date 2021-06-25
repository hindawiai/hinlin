<शैली गुरु>
/* 
 * drivers/video/edid.h - EDID/DDC Header
 *
 * Based on:
 *   1. XFree86 4.3.0, edid.h
 *      Copyright 1998 by Egbert Eich <Egbert.Eich@Physik.TU-Darmstadt.DE>
 * 
 *   2. John Fremlin <vii@users.sourceक्रमge.net> and 
 *      Ani Joshi <ajoshi@unixbox.com>
 *
 * DDC is a Trademark of VESA (Video Electronics Standard Association).
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
*/

#अगर_अघोषित __EDID_H__
#घोषणा __EDID_H__

#घोषणा EDID_LENGTH				0x80
#घोषणा EDID_HEADER				0x00
#घोषणा EDID_HEADER_END				0x07

#घोषणा ID_MANUFACTURER_NAME			0x08
#घोषणा ID_MANUFACTURER_NAME_END		0x09
#घोषणा ID_MODEL				0x0a

#घोषणा ID_SERIAL_NUMBER			0x0c

#घोषणा MANUFACTURE_WEEK			0x10
#घोषणा MANUFACTURE_YEAR			0x11

#घोषणा EDID_STRUCT_VERSION			0x12
#घोषणा EDID_STRUCT_REVISION			0x13

#घोषणा EDID_STRUCT_DISPLAY                     0x14

#घोषणा DPMS_FLAGS				0x18
#घोषणा ESTABLISHED_TIMING_1			0x23
#घोषणा ESTABLISHED_TIMING_2			0x24
#घोषणा MANUFACTURERS_TIMINGS			0x25

/* standard timings supported */
#घोषणा STD_TIMING                              8
#घोषणा STD_TIMING_DESCRIPTION_SIZE             2
#घोषणा STD_TIMING_DESCRIPTIONS_START           0x26

#घोषणा DETAILED_TIMING_DESCRIPTIONS_START	0x36
#घोषणा DETAILED_TIMING_DESCRIPTION_SIZE	18
#घोषणा NO_DETAILED_TIMING_DESCRIPTIONS		4

#घोषणा DETAILED_TIMING_DESCRIPTION_1		0x36
#घोषणा DETAILED_TIMING_DESCRIPTION_2		0x48
#घोषणा DETAILED_TIMING_DESCRIPTION_3		0x5a
#घोषणा DETAILED_TIMING_DESCRIPTION_4		0x6c

#घोषणा DESCRIPTOR_DATA				5

#घोषणा UPPER_NIBBLE( x ) \
        (((128|64|32|16) & (x)) >> 4)

#घोषणा LOWER_NIBBLE( x ) \
        ((1|2|4|8) & (x))

#घोषणा COMBINE_HI_8LO( hi, lo ) \
        ( (((अचिन्हित)hi) << 8) | (अचिन्हित)lo )

#घोषणा COMBINE_HI_4LO( hi, lo ) \
        ( (((अचिन्हित)hi) << 4) | (अचिन्हित)lo )

#घोषणा PIXEL_CLOCK_LO     (अचिन्हित)block[ 0 ]
#घोषणा PIXEL_CLOCK_HI     (अचिन्हित)block[ 1 ]
#घोषणा PIXEL_CLOCK	   (COMBINE_HI_8LO( PIXEL_CLOCK_HI,PIXEL_CLOCK_LO )*10000)
#घोषणा H_ACTIVE_LO        (अचिन्हित)block[ 2 ]
#घोषणा H_BLANKING_LO      (अचिन्हित)block[ 3 ]
#घोषणा H_ACTIVE_HI        UPPER_NIBBLE( (अचिन्हित)block[ 4 ] )
#घोषणा H_ACTIVE           COMBINE_HI_8LO( H_ACTIVE_HI, H_ACTIVE_LO )
#घोषणा H_BLANKING_HI      LOWER_NIBBLE( (अचिन्हित)block[ 4 ] )
#घोषणा H_BLANKING         COMBINE_HI_8LO( H_BLANKING_HI, H_BLANKING_LO )

#घोषणा V_ACTIVE_LO        (अचिन्हित)block[ 5 ]
#घोषणा V_BLANKING_LO      (अचिन्हित)block[ 6 ]
#घोषणा V_ACTIVE_HI        UPPER_NIBBLE( (अचिन्हित)block[ 7 ] )
#घोषणा V_ACTIVE           COMBINE_HI_8LO( V_ACTIVE_HI, V_ACTIVE_LO )
#घोषणा V_BLANKING_HI      LOWER_NIBBLE( (अचिन्हित)block[ 7 ] )
#घोषणा V_BLANKING         COMBINE_HI_8LO( V_BLANKING_HI, V_BLANKING_LO )

#घोषणा H_SYNC_OFFSET_LO   (अचिन्हित)block[ 8 ]
#घोषणा H_SYNC_WIDTH_LO    (अचिन्हित)block[ 9 ]

#घोषणा V_SYNC_OFFSET_LO   UPPER_NIBBLE( (अचिन्हित)block[ 10 ] )
#घोषणा V_SYNC_WIDTH_LO    LOWER_NIBBLE( (अचिन्हित)block[ 10 ] )

#घोषणा V_SYNC_WIDTH_HI    ((अचिन्हित)block[ 11 ] & (1|2))
#घोषणा V_SYNC_OFFSET_HI   (((अचिन्हित)block[ 11 ] & (4|8)) >> 2)

#घोषणा H_SYNC_WIDTH_HI    (((अचिन्हित)block[ 11 ] & (16|32)) >> 4)
#घोषणा H_SYNC_OFFSET_HI   (((अचिन्हित)block[ 11 ] & (64|128)) >> 6)

#घोषणा V_SYNC_WIDTH       COMBINE_HI_4LO( V_SYNC_WIDTH_HI, V_SYNC_WIDTH_LO )
#घोषणा V_SYNC_OFFSET      COMBINE_HI_4LO( V_SYNC_OFFSET_HI, V_SYNC_OFFSET_LO )

#घोषणा H_SYNC_WIDTH       COMBINE_HI_8LO( H_SYNC_WIDTH_HI, H_SYNC_WIDTH_LO )
#घोषणा H_SYNC_OFFSET      COMBINE_HI_8LO( H_SYNC_OFFSET_HI, H_SYNC_OFFSET_LO )

#घोषणा H_SIZE_LO          (अचिन्हित)block[ 12 ]
#घोषणा V_SIZE_LO          (अचिन्हित)block[ 13 ]

#घोषणा H_SIZE_HI          UPPER_NIBBLE( (अचिन्हित)block[ 14 ] )
#घोषणा V_SIZE_HI          LOWER_NIBBLE( (अचिन्हित)block[ 14 ] )

#घोषणा H_SIZE             COMBINE_HI_8LO( H_SIZE_HI, H_SIZE_LO )
#घोषणा V_SIZE             COMBINE_HI_8LO( V_SIZE_HI, V_SIZE_LO )

#घोषणा H_BORDER           (अचिन्हित)block[ 15 ]
#घोषणा V_BORDER           (अचिन्हित)block[ 16 ]

#घोषणा FLAGS              (अचिन्हित)block[ 17 ]

#घोषणा INTERLACED         (FLAGS&128)
#घोषणा SYNC_TYPE          (FLAGS&3<<3)	/* bits 4,3 */
#घोषणा SYNC_SEPARATE      (3<<3)
#घोषणा HSYNC_POSITIVE     (FLAGS & 4)
#घोषणा VSYNC_POSITIVE     (FLAGS & 2)

#घोषणा V_MIN_RATE              block[ 5 ]
#घोषणा V_MAX_RATE              block[ 6 ]
#घोषणा H_MIN_RATE              block[ 7 ]
#घोषणा H_MAX_RATE              block[ 8 ]
#घोषणा MAX_PIXEL_CLOCK         (((पूर्णांक)block[ 9 ]) * 10)
#घोषणा GTF_SUPPORT		block[10]

#घोषणा DPMS_ACTIVE_OFF		(1 << 5)
#घोषणा DPMS_SUSPEND		(1 << 6)
#घोषणा DPMS_STANDBY		(1 << 7)

#पूर्ण_अगर /* __EDID_H__ */
