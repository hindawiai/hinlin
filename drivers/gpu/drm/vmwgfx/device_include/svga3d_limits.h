<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**********************************************************
 * Copyright 2007-2019 VMware, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person
 * obtaining a copy of this software and associated करोcumentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************/

/*
 * svga3d_सीमा.स --
 *
 *       SVGA 3d hardware limits
 */

#अगर_अघोषित _SVGA3D_LIMITS_H_
#घोषणा _SVGA3D_LIMITS_H_

#घोषणा INCLUDE_ALLOW_MODULE
#घोषणा INCLUDE_ALLOW_USERLEVEL
#घोषणा INCLUDE_ALLOW_VMCORE

#समावेश "includeCheck.h"

#घोषणा SVGA3D_NUM_CLIPPLANES                   6
#घोषणा SVGA3D_MAX_CONTEXT_IDS                  256
#घोषणा SVGA3D_MAX_SURFACE_IDS                  (32 * 1024)

/*
 * While there are separate bind-poपूर्णांकs क्रम RenderTargetViews and
 * UnorderedAccessViews in a DXContext, there is in fact one shared
 * semantic space that the guest-driver can use on any given draw call.
 * So there are really only 8 slots that can be spilt up between them, with the
 * spliceIndex controlling where the UAV's sit in the collapsed array.
 */
#घोषणा SVGA3D_MAX_RENDER_TARGETS               8
#घोषणा SVGA3D_MAX_SIMULTANEOUS_RENDER_TARGETS  (SVGA3D_MAX_RENDER_TARGETS)
#घोषणा SVGA3D_MAX_UAVIEWS                      8
#घोषणा SVGA3D_DX11_1_MAX_UAVIEWS               64

/*
 * Maximum canonical size of a surface in host-backed mode (pre-GBObjects).
 */
#घोषणा SVGA3D_HB_MAX_SURFACE_SIZE MBYTES_2_BYTES(128)

/*
 * Maximum ID a shader can be asचिन्हित on a given context.
 */
#घोषणा SVGA3D_MAX_SHADERIDS                    5000
/*
 * Maximum number of shaders of a given type that can be defined
 * (including all contexts).
 */
#घोषणा SVGA3D_MAX_SIMULTANEOUS_SHADERS         20000

#घोषणा SVGA3D_NUM_TEXTURE_UNITS                32
#घोषणा SVGA3D_NUM_LIGHTS                       8

#घोषणा SVGA3D_MAX_VIDEOPROCESSOR_SAMPLERS      32

/*
 * Maximum size in dwords of shader text the SVGA device will allow.
 * Currently 8 MB.
 */
#घोषणा SVGA3D_MAX_SHADER_MEMORY_BYTES (8 * 1024 * 1024)
#घोषणा SVGA3D_MAX_SHADER_MEMORY  (SVGA3D_MAX_SHADER_MEMORY_BYTES / \
                                   माप(uपूर्णांक32))

/*
 * The maximum value of thपढ़ोGroupCount in each dimension
 */
#घोषणा SVGA3D_MAX_SHADER_THREAD_GROUPS 65535

#घोषणा SVGA3D_MAX_CLIP_PLANES    6

/*
 * This is the limit to the number of fixed-function texture
 * transक्रमms and texture coordinates we can support. It करोes *not*
 * correspond to the number of texture image units (samplers) we
 * support!
 */
#घोषणा SVGA3D_MAX_TEXTURE_COORDS 8

/*
 * Number of faces in a cubemap.
 */
#घोषणा SVGA3D_MAX_SURFACE_FACES 6

/*
 * Maximum number of array indexes in a GB surface (with DX enabled).
 */
#घोषणा SVGA3D_SM4_MAX_SURFACE_ARRAYSIZE 512
#घोषणा SVGA3D_SM5_MAX_SURFACE_ARRAYSIZE 2048
#घोषणा SVGA3D_MAX_SURFACE_ARRAYSIZE SVGA3D_SM5_MAX_SURFACE_ARRAYSIZE

/*
 * The maximum number of vertex arrays we're guaranteed to support in
 * SVGA_3D_CMD_DRAWPRIMITIVES.
 */
#घोषणा SVGA3D_MAX_VERTEX_ARRAYS   32

/*
 * The maximum number of primitive ranges we're guaranteed to support
 * in SVGA_3D_CMD_DRAWPRIMITIVES.
 */
#घोषणा SVGA3D_MAX_DRAW_PRIMITIVE_RANGES 32

/*
 * The maximum number of samples that can be contained in a surface.
 */
#घोषणा SVGA3D_MAX_SAMPLES 8

#पूर्ण_अगर /* _SVGA3D_LIMITS_H_ */
