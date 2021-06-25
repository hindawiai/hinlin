<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_GRPH_OBJECT_DEFS_H__
#घोषणा __DAL_GRPH_OBJECT_DEFS_H__

#समावेश "grph_object_id.h"

/* ********************************************************************
 * ********************************************************************
 *
 *  These defines shared between All Graphics Objects
 *
 * ********************************************************************
 * ********************************************************************
 */

#घोषणा MAX_CONNECTOR_NUMBER_PER_SLOT	(16)
#घोषणा MAX_BOARD_SLOTS					(4)
#घोषणा INVALID_CONNECTOR_INDEX			((अचिन्हित पूर्णांक)(-1))

/* HPD unit id - HW direct translation */
क्रमागत hpd_source_id अणु
	HPD_SOURCEID1 = 0,
	HPD_SOURCEID2,
	HPD_SOURCEID3,
	HPD_SOURCEID4,
	HPD_SOURCEID5,
	HPD_SOURCEID6,

	HPD_SOURCEID_COUNT,
	HPD_SOURCEID_UNKNOWN
पूर्ण;

/* DDC unit id - HW direct translation */
क्रमागत channel_id अणु
	CHANNEL_ID_UNKNOWN = 0,
	CHANNEL_ID_DDC1,
	CHANNEL_ID_DDC2,
	CHANNEL_ID_DDC3,
	CHANNEL_ID_DDC4,
	CHANNEL_ID_DDC5,
	CHANNEL_ID_DDC6,
	CHANNEL_ID_DDC_VGA,
	CHANNEL_ID_I2C_PAD,
	CHANNEL_ID_COUNT
पूर्ण;

#घोषणा DECODE_CHANNEL_ID(ch_id) \
	(ch_id) == CHANNEL_ID_DDC1 ? "CHANNEL_ID_DDC1" : \
	(ch_id) == CHANNEL_ID_DDC2 ? "CHANNEL_ID_DDC2" : \
	(ch_id) == CHANNEL_ID_DDC3 ? "CHANNEL_ID_DDC3" : \
	(ch_id) == CHANNEL_ID_DDC4 ? "CHANNEL_ID_DDC4" : \
	(ch_id) == CHANNEL_ID_DDC5 ? "CHANNEL_ID_DDC5" : \
	(ch_id) == CHANNEL_ID_DDC6 ? "CHANNEL_ID_DDC6" : \
	(ch_id) == CHANNEL_ID_DDC_VGA ? "CHANNEL_ID_DDC_VGA" : \
	(ch_id) == CHANNEL_ID_I2C_PAD ? "CHANNEL_ID_I2C_PAD" : "Invalid"

क्रमागत transmitter अणु
	TRANSMITTER_UNKNOWN = (-1L),
	TRANSMITTER_UNIPHY_A,
	TRANSMITTER_UNIPHY_B,
	TRANSMITTER_UNIPHY_C,
	TRANSMITTER_UNIPHY_D,
	TRANSMITTER_UNIPHY_E,
	TRANSMITTER_UNIPHY_F,
	TRANSMITTER_NUTMEG_CRT,
	TRANSMITTER_TRAVIS_CRT,
	TRANSMITTER_TRAVIS_LCD,
	TRANSMITTER_UNIPHY_G,
	TRANSMITTER_COUNT
पूर्ण;

/* Generic source of the synchronisation input/output संकेत */
/* Can be used क्रम flow control, stereo sync, timing sync, frame sync, etc */
क्रमागत sync_source अणु
	SYNC_SOURCE_NONE = 0,

	/* Source based on controllers */
	SYNC_SOURCE_CONTROLLER0,
	SYNC_SOURCE_CONTROLLER1,
	SYNC_SOURCE_CONTROLLER2,
	SYNC_SOURCE_CONTROLLER3,
	SYNC_SOURCE_CONTROLLER4,
	SYNC_SOURCE_CONTROLLER5,

	/* Source based on GSL group */
	SYNC_SOURCE_GSL_GROUP0,
	SYNC_SOURCE_GSL_GROUP1,
	SYNC_SOURCE_GSL_GROUP2,

	/* Source based on GSL IOs */
	/* These IOs normally used as GSL input/output */
	SYNC_SOURCE_GSL_IO_FIRST,
	SYNC_SOURCE_GSL_IO_GENLOCK_CLOCK = SYNC_SOURCE_GSL_IO_FIRST,
	SYNC_SOURCE_GSL_IO_GENLOCK_VSYNC,
	SYNC_SOURCE_GSL_IO_SWAPLOCK_A,
	SYNC_SOURCE_GSL_IO_SWAPLOCK_B,
	SYNC_SOURCE_GSL_IO_LAST = SYNC_SOURCE_GSL_IO_SWAPLOCK_B,

	/* Source based on regular IOs */
	SYNC_SOURCE_IO_FIRST,
	SYNC_SOURCE_IO_GENERIC_A = SYNC_SOURCE_IO_FIRST,
	SYNC_SOURCE_IO_GENERIC_B,
	SYNC_SOURCE_IO_GENERIC_C,
	SYNC_SOURCE_IO_GENERIC_D,
	SYNC_SOURCE_IO_GENERIC_E,
	SYNC_SOURCE_IO_GENERIC_F,
	SYNC_SOURCE_IO_HPD1,
	SYNC_SOURCE_IO_HPD2,
	SYNC_SOURCE_IO_HSYNC_A,
	SYNC_SOURCE_IO_VSYNC_A,
	SYNC_SOURCE_IO_HSYNC_B,
	SYNC_SOURCE_IO_VSYNC_B,
	SYNC_SOURCE_IO_LAST = SYNC_SOURCE_IO_VSYNC_B,

	/* Misc. flow control sources */
	SYNC_SOURCE_DUAL_GPU_PIN
पूर्ण;

/* connector sizes in millimeters - from BiosParserTypes.hpp */
#घोषणा CONNECTOR_SIZE_DVI			40
#घोषणा CONNECTOR_SIZE_VGA			32
#घोषणा CONNECTOR_SIZE_HDMI			16
#घोषणा CONNECTOR_SIZE_DP			16
#घोषणा CONNECTOR_SIZE_MINI_DP			9
#घोषणा CONNECTOR_SIZE_UNKNOWN			30

क्रमागत connector_layout_type अणु
	CONNECTOR_LAYOUT_TYPE_UNKNOWN,
	CONNECTOR_LAYOUT_TYPE_DVI_D,
	CONNECTOR_LAYOUT_TYPE_DVI_I,
	CONNECTOR_LAYOUT_TYPE_VGA,
	CONNECTOR_LAYOUT_TYPE_HDMI,
	CONNECTOR_LAYOUT_TYPE_DP,
	CONNECTOR_LAYOUT_TYPE_MINI_DP,
पूर्ण;
काष्ठा connector_layout_info अणु
	काष्ठा graphics_object_id connector_id;
	क्रमागत connector_layout_type connector_type;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक position;  /* offset in mm from right side of the board */
पूर्ण;

/* length and width in mm */
काष्ठा slot_layout_info अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक num_of_connectors;
	काष्ठा connector_layout_info connectors[MAX_CONNECTOR_NUMBER_PER_SLOT];
पूर्ण;

काष्ठा board_layout_info अणु
	अचिन्हित पूर्णांक num_of_slots;

	/* indicates valid inक्रमmation in bracket layout काष्ठाure. */
	अचिन्हित पूर्णांक is_number_of_slots_valid : 1;
	अचिन्हित पूर्णांक is_slots_size_valid : 1;
	अचिन्हित पूर्णांक is_connector_offsets_valid : 1;
	अचिन्हित पूर्णांक is_connector_lengths_valid : 1;

	काष्ठा slot_layout_info slots[MAX_BOARD_SLOTS];
पूर्ण;
#पूर्ण_अगर
