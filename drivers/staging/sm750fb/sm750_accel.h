<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ACCEL_H__
#घोषणा ACCEL_H__

#घोषणा HW_ROP2_COPY 0xc
#घोषणा HW_ROP2_XOR 0x6

/* notes: below address are the offset value from de_base_address (0x100000)*/

/* क्रम sm718/750/502 de_base is at mmreg_1mb*/
#घोषणा DE_BASE_ADDR_TYPE1 0x100000
/* क्रम sm712,de_base is at mmreg_32kb */
#घोषणा DE_BASE_ADDR_TYPE2  0x8000
/* क्रम sm722,de_base is at mmreg_0 */
#घोषणा DE_BASE_ADDR_TYPE3 0

/* type1 data port address is at mmreg_0x110000*/
#घोषणा DE_PORT_ADDR_TYPE1 0x110000
/* क्रम sm712,data port address is at mmreg_0 */
#घोषणा DE_PORT_ADDR_TYPE2 0x100000
/* क्रम sm722,data port address is at mmreg_1mb */
#घोषणा DE_PORT_ADDR_TYPE3 0x100000

#घोषणा DE_SOURCE                                       0x0
#घोषणा DE_SOURCE_WRAP                                  BIT(31)
#घोषणा DE_SOURCE_X_K1_SHIFT                            16
#घोषणा DE_SOURCE_X_K1_MASK                             (0x3fff << 16)
#घोषणा DE_SOURCE_X_K1_MONO_MASK			(0x1f << 16)
#घोषणा DE_SOURCE_Y_K2_MASK                             0xffff

#घोषणा DE_DESTINATION                                  0x4
#घोषणा DE_DESTINATION_WRAP                             BIT(31)
#घोषणा DE_DESTINATION_X_SHIFT                          16
#घोषणा DE_DESTINATION_X_MASK                           (0x1fff << 16)
#घोषणा DE_DESTINATION_Y_MASK                           0xffff

#घोषणा DE_DIMENSION                                    0x8
#घोषणा DE_DIMENSION_X_SHIFT                            16
#घोषणा DE_DIMENSION_X_MASK                             (0x1fff << 16)
#घोषणा DE_DIMENSION_Y_ET_MASK                          0x1fff

#घोषणा DE_CONTROL                                      0xC
#घोषणा DE_CONTROL_STATUS                               BIT(31)
#घोषणा DE_CONTROL_PATTERN                              BIT(30)
#घोषणा DE_CONTROL_UPDATE_DESTINATION_X                 BIT(29)
#घोषणा DE_CONTROL_QUICK_START                          BIT(28)
#घोषणा DE_CONTROL_सूचीECTION                            BIT(27)
#घोषणा DE_CONTROL_MAJOR                                BIT(26)
#घोषणा DE_CONTROL_STEP_X                               BIT(25)
#घोषणा DE_CONTROL_STEP_Y                               BIT(24)
#घोषणा DE_CONTROL_STRETCH                              BIT(23)
#घोषणा DE_CONTROL_HOST                                 BIT(22)
#घोषणा DE_CONTROL_LAST_PIXEL                           BIT(21)
#घोषणा DE_CONTROL_COMMAND_SHIFT                        16
#घोषणा DE_CONTROL_COMMAND_MASK                         (0x1f << 16)
#घोषणा DE_CONTROL_COMMAND_BITBLT                       (0x0 << 16)
#घोषणा DE_CONTROL_COMMAND_RECTANGLE_FILL               (0x1 << 16)
#घोषणा DE_CONTROL_COMMAND_DE_TILE                      (0x2 << 16)
#घोषणा DE_CONTROL_COMMAND_TRAPEZOID_FILL               (0x3 << 16)
#घोषणा DE_CONTROL_COMMAND_ALPHA_BLEND                  (0x4 << 16)
#घोषणा DE_CONTROL_COMMAND_RLE_STRIP                    (0x5 << 16)
#घोषणा DE_CONTROL_COMMAND_SHORT_STROKE                 (0x6 << 16)
#घोषणा DE_CONTROL_COMMAND_LINE_DRAW                    (0x7 << 16)
#घोषणा DE_CONTROL_COMMAND_HOST_WRITE                   (0x8 << 16)
#घोषणा DE_CONTROL_COMMAND_HOST_READ                    (0x9 << 16)
#घोषणा DE_CONTROL_COMMAND_HOST_WRITE_BOTTOM_UP         (0xa << 16)
#घोषणा DE_CONTROL_COMMAND_ROTATE                       (0xb << 16)
#घोषणा DE_CONTROL_COMMAND_FONT                         (0xc << 16)
#घोषणा DE_CONTROL_COMMAND_TEXTURE_LOAD                 (0xe << 16)
#घोषणा DE_CONTROL_ROP_SELECT                           BIT(15)
#घोषणा DE_CONTROL_ROP2_SOURCE                          BIT(14)
#घोषणा DE_CONTROL_MONO_DATA_SHIFT                      12
#घोषणा DE_CONTROL_MONO_DATA_MASK                       (0x3 << 12)
#घोषणा DE_CONTROL_MONO_DATA_NOT_PACKED                 (0x0 << 12)
#घोषणा DE_CONTROL_MONO_DATA_8_PACKED                   (0x1 << 12)
#घोषणा DE_CONTROL_MONO_DATA_16_PACKED                  (0x2 << 12)
#घोषणा DE_CONTROL_MONO_DATA_32_PACKED                  (0x3 << 12)
#घोषणा DE_CONTROL_REPEAT_ROTATE                        BIT(11)
#घोषणा DE_CONTROL_TRANSPARENCY_MATCH                   BIT(10)
#घोषणा DE_CONTROL_TRANSPARENCY_SELECT                  BIT(9)
#घोषणा DE_CONTROL_TRANSPARENCY                         BIT(8)
#घोषणा DE_CONTROL_ROP_MASK                             0xff

/* Pseuकरो fields. */

#घोषणा DE_CONTROL_SHORT_STROKE_सूची_MASK                (0xf << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_225                 (0x0 << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_135                 (0x1 << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_315                 (0x2 << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_45                  (0x3 << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_270                 (0x4 << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_90                  (0x5 << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_180                 (0x8 << 24)
#घोषणा DE_CONTROL_SHORT_STROKE_सूची_0                   (0xa << 24)
#घोषणा DE_CONTROL_ROTATION_MASK                        (0x3 << 24)
#घोषणा DE_CONTROL_ROTATION_0                           (0x0 << 24)
#घोषणा DE_CONTROL_ROTATION_270                         (0x1 << 24)
#घोषणा DE_CONTROL_ROTATION_90                          (0x2 << 24)
#घोषणा DE_CONTROL_ROTATION_180                         (0x3 << 24)

#घोषणा DE_PITCH                                        0x000010
#घोषणा DE_PITCH_DESTINATION_SHIFT                      16
#घोषणा DE_PITCH_DESTINATION_MASK                       (0x1fff << 16)
#घोषणा DE_PITCH_SOURCE_MASK                            0x1fff

#घोषणा DE_FOREGROUND                                   0x000014
#घोषणा DE_FOREGROUND_COLOR_MASK                        0xffffffff

#घोषणा DE_BACKGROUND                                   0x000018
#घोषणा DE_BACKGROUND_COLOR_MASK                        0xffffffff

#घोषणा DE_STRETCH_FORMAT                               0x00001C
#घोषणा DE_STRETCH_FORMAT_PATTERN_XY                    BIT(30)
#घोषणा DE_STRETCH_FORMAT_PATTERN_Y_SHIFT               27
#घोषणा DE_STRETCH_FORMAT_PATTERN_Y_MASK                (0x7 << 27)
#घोषणा DE_STRETCH_FORMAT_PATTERN_X_SHIFT               23
#घोषणा DE_STRETCH_FORMAT_PATTERN_X_MASK                (0x7 << 23)
#घोषणा DE_STRETCH_FORMAT_PIXEL_FORMAT_SHIFT            20
#घोषणा DE_STRETCH_FORMAT_PIXEL_FORMAT_MASK             (0x3 << 20)
#घोषणा DE_STRETCH_FORMAT_PIXEL_FORMAT_8                (0x0 << 20)
#घोषणा DE_STRETCH_FORMAT_PIXEL_FORMAT_16               (0x1 << 20)
#घोषणा DE_STRETCH_FORMAT_PIXEL_FORMAT_32               (0x2 << 20)
#घोषणा DE_STRETCH_FORMAT_PIXEL_FORMAT_24               (0x3 << 20)
#घोषणा DE_STRETCH_FORMAT_ADDRESSING_SHIFT              16
#घोषणा DE_STRETCH_FORMAT_ADDRESSING_MASK               (0xf << 16)
#घोषणा DE_STRETCH_FORMAT_ADDRESSING_XY                 (0x0 << 16)
#घोषणा DE_STRETCH_FORMAT_ADDRESSING_LINEAR             (0xf << 16)
#घोषणा DE_STRETCH_FORMAT_SOURCE_HEIGHT_MASK            0xfff

#घोषणा DE_COLOR_COMPARE                                0x000020
#घोषणा DE_COLOR_COMPARE_COLOR_MASK                     0xffffff

#घोषणा DE_COLOR_COMPARE_MASK                           0x000024
#घोषणा DE_COLOR_COMPARE_MASK_MASK                      0xffffff

#घोषणा DE_MASKS                                        0x000028
#घोषणा DE_MASKS_BYTE_MASK                              (0xffff << 16)
#घोषणा DE_MASKS_BIT_MASK                               0xffff

#घोषणा DE_CLIP_TL                                      0x00002C
#घोषणा DE_CLIP_TL_TOP_MASK                             (0xffff << 16)
#घोषणा DE_CLIP_TL_STATUS                               BIT(13)
#घोषणा DE_CLIP_TL_INHIBIT                              BIT(12)
#घोषणा DE_CLIP_TL_LEFT_MASK                            0xfff

#घोषणा DE_CLIP_BR                                      0x000030
#घोषणा DE_CLIP_BR_BOTTOM_MASK                          (0xffff << 16)
#घोषणा DE_CLIP_BR_RIGHT_MASK                           0x1fff

#घोषणा DE_MONO_PATTERN_LOW                             0x000034
#घोषणा DE_MONO_PATTERN_LOW_PATTERN_MASK                0xffffffff

#घोषणा DE_MONO_PATTERN_HIGH                            0x000038
#घोषणा DE_MONO_PATTERN_HIGH_PATTERN_MASK               0xffffffff

#घोषणा DE_WINDOW_WIDTH                                 0x00003C
#घोषणा DE_WINDOW_WIDTH_DST_SHIFT                       16
#घोषणा DE_WINDOW_WIDTH_DST_MASK                        (0x1fff << 16)
#घोषणा DE_WINDOW_WIDTH_SRC_MASK                        0x1fff

#घोषणा DE_WINDOW_SOURCE_BASE                           0x000040
#घोषणा DE_WINDOW_SOURCE_BASE_EXT                       BIT(27)
#घोषणा DE_WINDOW_SOURCE_BASE_CS                        BIT(26)
#घोषणा DE_WINDOW_SOURCE_BASE_ADDRESS_MASK              0x3ffffff

#घोषणा DE_WINDOW_DESTINATION_BASE                      0x000044
#घोषणा DE_WINDOW_DESTINATION_BASE_EXT                  BIT(27)
#घोषणा DE_WINDOW_DESTINATION_BASE_CS                   BIT(26)
#घोषणा DE_WINDOW_DESTINATION_BASE_ADDRESS_MASK         0x3ffffff

#घोषणा DE_ALPHA                                        0x000048
#घोषणा DE_ALPHA_VALUE_MASK                             0xff

#घोषणा DE_WRAP                                         0x00004C
#घोषणा DE_WRAP_X_MASK                                  (0xffff << 16)
#घोषणा DE_WRAP_Y_MASK                                  0xffff

#घोषणा DE_STATUS                                       0x000050
#घोषणा DE_STATUS_CSC                                   BIT(1)
#घोषणा DE_STATUS_2D                                    BIT(0)

/* blt direction */
#घोषणा TOP_TO_BOTTOM 0
#घोषणा LEFT_TO_RIGHT 0
#घोषणा BOTTOM_TO_TOP 1
#घोषणा RIGHT_TO_LEFT 1

व्योम sm750_hw_set2dक्रमmat(काष्ठा lynx_accel *accel, पूर्णांक fmt);

व्योम sm750_hw_de_init(काष्ठा lynx_accel *accel);

पूर्णांक sm750_hw_fillrect(काष्ठा lynx_accel *accel,
		      u32 base, u32 pitch, u32 Bpp,
		      u32 x, u32 y, u32 width, u32 height,
		      u32 color, u32 rop);

/**
 * sm750_hm_copyarea
 * @sBase: Address of source: offset in frame buffer
 * @sPitch: Pitch value of source surface in BYTE
 * @sx: Starting x coordinate of source surface
 * @sy: Starting y coordinate of source surface
 * @dBase: Address of destination: offset in frame buffer
 * @dPitch: Pitch value of destination surface in BYTE
 * @Bpp: Color depth of destination surface
 * @dx: Starting x coordinate of destination surface
 * @dy: Starting y coordinate of destination surface
 * @width: width of rectangle in pixel value
 * @height: height of rectangle in pixel value
 * @rop2: ROP value
 */
पूर्णांक sm750_hw_copyarea(काष्ठा lynx_accel *accel,
		      अचिन्हित पूर्णांक sBase, अचिन्हित पूर्णांक sPitch,
		      अचिन्हित पूर्णांक sx, अचिन्हित पूर्णांक sy,
		      अचिन्हित पूर्णांक dBase, अचिन्हित पूर्णांक dPitch,
		      अचिन्हित पूर्णांक Bpp, अचिन्हित पूर्णांक dx, अचिन्हित पूर्णांक dy,
		      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
		      अचिन्हित पूर्णांक rop2);

/**
 * sm750_hw_imageblit
 * @pSrcbuf: poपूर्णांकer to start of source buffer in प्रणाली memory
 * @srcDelta: Pitch value (in bytes) of the source buffer, +ive means top करोwn
 *>-----      and -ive mean button up
 * @startBit: Mono data can start at any bit in a byte, this value should be
 *>-----      0 to 7
 * @dBase: Address of destination: offset in frame buffer
 * @dPitch: Pitch value of destination surface in BYTE
 * @bytePerPixel: Color depth of destination surface
 * @dx: Starting x coordinate of destination surface
 * @dy: Starting y coordinate of destination surface
 * @width: width of rectangle in pixel value
 * @height: height of rectangle in pixel value
 * @fColor: Foreground color (corresponding to a 1 in the monochrome data
 * @bColor: Background color (corresponding to a 0 in the monochrome data
 * @rop2: ROP value
 */
पूर्णांक sm750_hw_imageblit(काष्ठा lynx_accel *accel, स्थिर अक्षर *pSrcbuf,
		       u32 srcDelta, u32 startBit, u32 dBase, u32 dPitch,
		       u32 bytePerPixel, u32 dx, u32 dy, u32 width,
		       u32 height, u32 fColor, u32 bColor, u32 rop2);

#पूर्ण_अगर
