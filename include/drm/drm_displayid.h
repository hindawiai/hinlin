<शैली गुरु>
/*
 * Copyright तऊ 2014 Red Hat Inc.
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
 */
#अगर_अघोषित DRM_DISPLAYID_H
#घोषणा DRM_DISPLAYID_H

#समावेश <linux/types.h>

काष्ठा edid;

#घोषणा DATA_BLOCK_PRODUCT_ID 0x00
#घोषणा DATA_BLOCK_DISPLAY_PARAMETERS 0x01
#घोषणा DATA_BLOCK_COLOR_CHARACTERISTICS 0x02
#घोषणा DATA_BLOCK_TYPE_1_DETAILED_TIMING 0x03
#घोषणा DATA_BLOCK_TYPE_2_DETAILED_TIMING 0x04
#घोषणा DATA_BLOCK_TYPE_3_SHORT_TIMING 0x05
#घोषणा DATA_BLOCK_TYPE_4_DMT_TIMING 0x06
#घोषणा DATA_BLOCK_VESA_TIMING 0x07
#घोषणा DATA_BLOCK_CEA_TIMING 0x08
#घोषणा DATA_BLOCK_VIDEO_TIMING_RANGE 0x09
#घोषणा DATA_BLOCK_PRODUCT_SERIAL_NUMBER 0x0a
#घोषणा DATA_BLOCK_GP_ASCII_STRING 0x0b
#घोषणा DATA_BLOCK_DISPLAY_DEVICE_DATA 0x0c
#घोषणा DATA_BLOCK_INTERFACE_POWER_SEQUENCING 0x0d
#घोषणा DATA_BLOCK_TRANSFER_CHARACTERISTICS 0x0e
#घोषणा DATA_BLOCK_DISPLAY_INTERFACE 0x0f
#घोषणा DATA_BLOCK_STEREO_DISPLAY_INTERFACE 0x10
#घोषणा DATA_BLOCK_TILED_DISPLAY 0x12
#घोषणा DATA_BLOCK_CTA 0x81

#घोषणा DATA_BLOCK_VENDOR_SPECIFIC 0x7f

#घोषणा PRODUCT_TYPE_EXTENSION 0
#घोषणा PRODUCT_TYPE_TEST 1
#घोषणा PRODUCT_TYPE_PANEL 2
#घोषणा PRODUCT_TYPE_MONITOR 3
#घोषणा PRODUCT_TYPE_TV 4
#घोषणा PRODUCT_TYPE_REPEATER 5
#घोषणा PRODUCT_TYPE_सूचीECT_DRIVE 6

काष्ठा displayid_header अणु
	u8 rev;
	u8 bytes;
	u8 prod_id;
	u8 ext_count;
पूर्ण __packed;

काष्ठा displayid_block अणु
	u8 tag;
	u8 rev;
	u8 num_bytes;
पूर्ण __packed;

काष्ठा displayid_tiled_block अणु
	काष्ठा displayid_block base;
	u8 tile_cap;
	u8 topo[3];
	u8 tile_size[4];
	u8 tile_pixel_bezel[5];
	u8 topology_id[8];
पूर्ण __packed;

काष्ठा displayid_detailed_timings_1 अणु
	u8 pixel_घड़ी[3];
	u8 flags;
	u8 hactive[2];
	u8 hblank[2];
	u8 hsync[2];
	u8 hsw[2];
	u8 vactive[2];
	u8 vblank[2];
	u8 vsync[2];
	u8 vsw[2];
पूर्ण __packed;

काष्ठा displayid_detailed_timing_block अणु
	काष्ठा displayid_block base;
	काष्ठा displayid_detailed_timings_1 timings[];
पूर्ण;

/* DisplayID iteration */
काष्ठा displayid_iter अणु
	स्थिर काष्ठा edid *edid;

	स्थिर u8 *section;
	पूर्णांक length;
	पूर्णांक idx;
	पूर्णांक ext_index;
पूर्ण;

व्योम displayid_iter_edid_begin(स्थिर काष्ठा edid *edid,
			       काष्ठा displayid_iter *iter);
स्थिर काष्ठा displayid_block *
__displayid_iter_next(काष्ठा displayid_iter *iter);
#घोषणा displayid_iter_क्रम_each(__block, __iter) \
	जबतक (((__block) = __displayid_iter_next(__iter)))
व्योम displayid_iter_end(काष्ठा displayid_iter *iter);

#पूर्ण_अगर
