<शैली गुरु>

 /***************************************************************************\
|*                                                                           *|
|*       Copyright 2003 NVIDIA, Corporation.  All rights reserved.           *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     पूर्णांकernational laws.  Users and possessors of this source code are     *|
|*     hereby granted a nonexclusive,  royalty-मुक्त copyright license to     *|
|*     use this code in inभागidual and commercial software.                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user करोcumenta-     *|
|*     tion and  पूर्णांकernal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*       Copyright 2003 NVIDIA, Corporation.  All rights reserved.           *|
|*                                                                           *|
|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|
|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"     *|
|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|
|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|
|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|
|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|
|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INसूचीECT,  INCI-     *|
|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|
|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|
|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|
|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|
|*                                                                           *|
|*     U.S. Government  End  Users.   This source code  is a "commercial     *|
|*     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|
|*     consisting  of "commercial  computer  software"  and  "commercial     *|
|*     computer  software  करोcumentation,"  as such  terms  are  used in     *|
|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|
|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|
|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|
|*     all U.S. Government End Users  acquire the source code  with only     *|
|*     those rights set क्रमth herein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*
 * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/
 * XFree86 'nv' driver, this source code is provided under MIT-style licensing
 * where the source code is provided "as is" without warranty of any kind.
 * The only usage restriction is क्रम the copyright notices to be retained
 * whenever code is used.
 *
 * Antonino Daplas <adaplas@pol.net> 2005-03-11
 */

#घोषणा SURFACE_FORMAT                                              0x00000300
#घोषणा SURFACE_FORMAT_DEPTH8                                       0x00000001
#घोषणा SURFACE_FORMAT_DEPTH15                                      0x00000002
#घोषणा SURFACE_FORMAT_DEPTH16                                      0x00000004
#घोषणा SURFACE_FORMAT_DEPTH24                                      0x00000006
#घोषणा SURFACE_PITCH                                               0x00000304
#घोषणा SURFACE_PITCH_SRC                                           15:0
#घोषणा SURFACE_PITCH_DST                                           31:16
#घोषणा SURFACE_OFFSET_SRC                                          0x00000308
#घोषणा SURFACE_OFFSET_DST                                          0x0000030C

#घोषणा ROP_SET                                                     0x00002300

#घोषणा PATTERN_FORMAT                                              0x00004300
#घोषणा PATTERN_FORMAT_DEPTH8                                       0x00000003
#घोषणा PATTERN_FORMAT_DEPTH16                                      0x00000001
#घोषणा PATTERN_FORMAT_DEPTH24                                      0x00000003
#घोषणा PATTERN_COLOR_0                                             0x00004310
#घोषणा PATTERN_COLOR_1                                             0x00004314
#घोषणा PATTERN_PATTERN_0                                           0x00004318
#घोषणा PATTERN_PATTERN_1                                           0x0000431C

#घोषणा CLIP_POINT                                                  0x00006300
#घोषणा CLIP_POINT_X                                                15:0
#घोषणा CLIP_POINT_Y                                                31:16
#घोषणा CLIP_SIZE                                                   0x00006304
#घोषणा CLIP_SIZE_WIDTH                                             15:0
#घोषणा CLIP_SIZE_HEIGHT                                            31:16

#घोषणा LINE_FORMAT                                                 0x00008300
#घोषणा LINE_FORMAT_DEPTH8                                          0x00000003
#घोषणा LINE_FORMAT_DEPTH16                                         0x00000001
#घोषणा LINE_FORMAT_DEPTH24                                         0x00000003
#घोषणा LINE_COLOR                                                  0x00008304
#घोषणा LINE_MAX_LINES                                              16
#घोषणा LINE_LINES(i)                                               0x00008400\
                                                                    +(i)*8
#घोषणा LINE_LINES_POINT0_X                                         15:0
#घोषणा LINE_LINES_POINT0_Y                                         31:16
#घोषणा LINE_LINES_POINT1_X                                         47:32
#घोषणा LINE_LINES_POINT1_Y                                         63:48

#घोषणा BLIT_POINT_SRC                                              0x0000A300
#घोषणा BLIT_POINT_SRC_X                                            15:0
#घोषणा BLIT_POINT_SRC_Y                                            31:16
#घोषणा BLIT_POINT_DST                                              0x0000A304
#घोषणा BLIT_POINT_DST_X                                            15:0
#घोषणा BLIT_POINT_DST_Y                                            31:16
#घोषणा BLIT_SIZE                                                   0x0000A308
#घोषणा BLIT_SIZE_WIDTH                                             15:0
#घोषणा BLIT_SIZE_HEIGHT                                            31:16

#घोषणा RECT_FORMAT                                                 0x0000C300
#घोषणा RECT_FORMAT_DEPTH8                                          0x00000003
#घोषणा RECT_FORMAT_DEPTH16                                         0x00000001
#घोषणा RECT_FORMAT_DEPTH24                                         0x00000003
#घोषणा RECT_SOLID_COLOR                                            0x0000C3FC
#घोषणा RECT_SOLID_RECTS_MAX_RECTS                                  32
#घोषणा RECT_SOLID_RECTS(i)                                         0x0000C400\
                                                                    +(i)*8
#घोषणा RECT_SOLID_RECTS_Y                                          15:0
#घोषणा RECT_SOLID_RECTS_X                                          31:16
#घोषणा RECT_SOLID_RECTS_HEIGHT                                     47:32
#घोषणा RECT_SOLID_RECTS_WIDTH                                      63:48

#घोषणा RECT_EXPAND_ONE_COLOR_CLIP                                  0x0000C7EC
#घोषणा RECT_EXPAND_ONE_COLOR_CLIP_POINT0_X                         15:0
#घोषणा RECT_EXPAND_ONE_COLOR_CLIP_POINT0_Y                         31:16
#घोषणा RECT_EXPAND_ONE_COLOR_CLIP_POINT1_X                         47:32
#घोषणा RECT_EXPAND_ONE_COLOR_CLIP_POINT1_Y                         63:48
#घोषणा RECT_EXPAND_ONE_COLOR_COLOR                                 0x0000C7F4
#घोषणा RECT_EXPAND_ONE_COLOR_SIZE                                  0x0000C7F8
#घोषणा RECT_EXPAND_ONE_COLOR_SIZE_WIDTH                            15:0
#घोषणा RECT_EXPAND_ONE_COLOR_SIZE_HEIGHT                           31:16
#घोषणा RECT_EXPAND_ONE_COLOR_POINT                                 0x0000C7FC
#घोषणा RECT_EXPAND_ONE_COLOR_POINT_X                               15:0
#घोषणा RECT_EXPAND_ONE_COLOR_POINT_Y                               31:16
#घोषणा RECT_EXPAND_ONE_COLOR_DATA_MAX_DWORDS                       128
#घोषणा RECT_EXPAND_ONE_COLOR_DATA(i)                               0x0000C800\
                                                                    +(i)*4

#घोषणा RECT_EXPAND_TWO_COLOR_CLIP                                  0x0000CBE4
#घोषणा RECT_EXPAND_TWO_COLOR_CLIP_POINT0_X                         15:0
#घोषणा RECT_EXPAND_TWO_COLOR_CLIP_POINT0_Y                         31:16
#घोषणा RECT_EXPAND_TWO_COLOR_CLIP_POINT1_X                         47:32
#घोषणा RECT_EXPAND_TWO_COLOR_CLIP_POINT1_Y                         63:48
#घोषणा RECT_EXPAND_TWO_COLOR_COLOR_0                               0x0000CBEC
#घोषणा RECT_EXPAND_TWO_COLOR_COLOR_1                               0x0000CBF0
#घोषणा RECT_EXPAND_TWO_COLOR_SIZE_IN                               0x0000CBF4
#घोषणा RECT_EXPAND_TWO_COLOR_SIZE_IN_WIDTH                         15:0
#घोषणा RECT_EXPAND_TWO_COLOR_SIZE_IN_HEIGHT                        31:16
#घोषणा RECT_EXPAND_TWO_COLOR_SIZE_OUT                              0x0000CBF8
#घोषणा RECT_EXPAND_TWO_COLOR_SIZE_OUT_WIDTH                        15:0
#घोषणा RECT_EXPAND_TWO_COLOR_SIZE_OUT_HEIGHT                       31:16
#घोषणा RECT_EXPAND_TWO_COLOR_POINT                                 0x0000CBFC
#घोषणा RECT_EXPAND_TWO_COLOR_POINT_X                               15:0
#घोषणा RECT_EXPAND_TWO_COLOR_POINT_Y                               31:16
#घोषणा RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS                       128
#घोषणा RECT_EXPAND_TWO_COLOR_DATA(i)                               0x0000CC00\
                                                                    +(i)*4

#घोषणा STRETCH_BLIT_FORMAT                                         0x0000E300
#घोषणा STRETCH_BLIT_FORMAT_DEPTH8                                  0x00000004
#घोषणा STRETCH_BLIT_FORMAT_DEPTH16                                 0x00000007
#घोषणा STRETCH_BLIT_FORMAT_DEPTH24                                 0x00000004
#घोषणा STRETCH_BLIT_FORMAT_X8R8G8B8                                0x00000004
#घोषणा STRETCH_BLIT_FORMAT_YUYV                                    0x00000005
#घोषणा STRETCH_BLIT_FORMAT_UYVY                                    0x00000006
#घोषणा STRETCH_BLIT_CLIP_POINT                                     0x0000E308
#घोषणा STRETCH_BLIT_CLIP_POINT_X                                   15:0
#घोषणा STRETCH_BLIT_CLIP_POINT_Y                                   31:16
#घोषणा STRETCH_BLIT_CLIP_POINT                                     0x0000E308
#घोषणा STRETCH_BLIT_CLIP_SIZE                                      0x0000E30C
#घोषणा STRETCH_BLIT_CLIP_SIZE_WIDTH                                15:0
#घोषणा STRETCH_BLIT_CLIP_SIZE_HEIGHT                               31:16
#घोषणा STRETCH_BLIT_DST_POINT                                      0x0000E310
#घोषणा STRETCH_BLIT_DST_POINT_X                                    15:0
#घोषणा STRETCH_BLIT_DST_POINT_Y                                    31:16
#घोषणा STRETCH_BLIT_DST_SIZE                                       0x0000E314
#घोषणा STRETCH_BLIT_DST_SIZE_WIDTH                                 15:0
#घोषणा STRETCH_BLIT_DST_SIZE_HEIGHT                                31:16
#घोषणा STRETCH_BLIT_DU_DX                                          0x0000E318
#घोषणा STRETCH_BLIT_DV_DY                                          0x0000E31C
#घोषणा STRETCH_BLIT_SRC_SIZE                                       0x0000E400
#घोषणा STRETCH_BLIT_SRC_SIZE_WIDTH                                 15:0
#घोषणा STRETCH_BLIT_SRC_SIZE_HEIGHT                                31:16
#घोषणा STRETCH_BLIT_SRC_FORMAT                                     0x0000E404
#घोषणा STRETCH_BLIT_SRC_FORMAT_PITCH                               15:0
#घोषणा STRETCH_BLIT_SRC_FORMAT_ORIGIN                              23:16
#घोषणा STRETCH_BLIT_SRC_FORMAT_ORIGIN_CENTER                       0x00000001
#घोषणा STRETCH_BLIT_SRC_FORMAT_ORIGIN_CORNER                       0x00000002
#घोषणा STRETCH_BLIT_SRC_FORMAT_FILTER                              31:24
#घोषणा STRETCH_BLIT_SRC_FORMAT_FILTER_POINT_SAMPLE                 0x00000000
#घोषणा STRETCH_BLIT_SRC_FORMAT_FILTER_BILINEAR                     0x00000001
#घोषणा STRETCH_BLIT_SRC_OFFSET                                     0x0000E408
#घोषणा STRETCH_BLIT_SRC_POINT                                      0x0000E40C
#घोषणा STRETCH_BLIT_SRC_POINT_U                                    15:0
#घोषणा STRETCH_BLIT_SRC_POINT_V                                    31:16
