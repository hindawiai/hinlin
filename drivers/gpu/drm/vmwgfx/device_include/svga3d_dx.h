<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**********************************************************
 * Copyright 2012-2019 VMware, Inc.
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
 * svga3d_dx.h --
 *
 *       SVGA 3d hardware definitions क्रम DX10 support.
 */

#अगर_अघोषित _SVGA3D_DX_H_
#घोषणा _SVGA3D_DX_H_

#घोषणा INCLUDE_ALLOW_MODULE
#घोषणा INCLUDE_ALLOW_USERLEVEL
#घोषणा INCLUDE_ALLOW_VMCORE
#समावेश "includeCheck.h"

#समावेश "svga3d_limits.h"

#घोषणा SVGA3D_INPUT_MIN               0
#घोषणा SVGA3D_INPUT_PER_VERTEX_DATA   0
#घोषणा SVGA3D_INPUT_PER_INSTANCE_DATA 1
#घोषणा SVGA3D_INPUT_MAX               2
प्रकार uपूर्णांक32 SVGA3dInputClassअगरication;

#घोषणा SVGA3D_RESOURCE_TYPE_MIN      1
#घोषणा SVGA3D_RESOURCE_BUFFER        1
#घोषणा SVGA3D_RESOURCE_TEXTURE1D     2
#घोषणा SVGA3D_RESOURCE_TEXTURE2D     3
#घोषणा SVGA3D_RESOURCE_TEXTURE3D     4
#घोषणा SVGA3D_RESOURCE_TEXTURECUBE   5
#घोषणा SVGA3D_RESOURCE_TYPE_DX10_MAX 6
#घोषणा SVGA3D_RESOURCE_BUFFEREX      6
#घोषणा SVGA3D_RESOURCE_TYPE_MAX      7
प्रकार uपूर्णांक32 SVGA3dResourceType;

#घोषणा SVGA3D_COLOR_WRITE_ENABLE_RED     (1 << 0)
#घोषणा SVGA3D_COLOR_WRITE_ENABLE_GREEN   (1 << 1)
#घोषणा SVGA3D_COLOR_WRITE_ENABLE_BLUE    (1 << 2)
#घोषणा SVGA3D_COLOR_WRITE_ENABLE_ALPHA   (1 << 3)
#घोषणा SVGA3D_COLOR_WRITE_ENABLE_ALL     (SVGA3D_COLOR_WRITE_ENABLE_RED |   \
                                           SVGA3D_COLOR_WRITE_ENABLE_GREEN | \
                                           SVGA3D_COLOR_WRITE_ENABLE_BLUE |  \
                                           SVGA3D_COLOR_WRITE_ENABLE_ALPHA)
प्रकार uपूर्णांक8 SVGA3dColorWriteEnable;

#घोषणा SVGA3D_DEPTH_WRITE_MASK_ZERO   0
#घोषणा SVGA3D_DEPTH_WRITE_MASK_ALL    1
प्रकार uपूर्णांक8 SVGA3dDepthWriteMask;

#घोषणा SVGA3D_FILTER_MIP_LINEAR  (1 << 0)
#घोषणा SVGA3D_FILTER_MAG_LINEAR  (1 << 2)
#घोषणा SVGA3D_FILTER_MIN_LINEAR  (1 << 4)
#घोषणा SVGA3D_FILTER_ANISOTROPIC (1 << 6)
#घोषणा SVGA3D_FILTER_COMPARE     (1 << 7)
प्रकार uपूर्णांक32 SVGA3dFilter;

#घोषणा SVGA3D_CULL_INVALID 0
#घोषणा SVGA3D_CULL_MIN     1
#घोषणा SVGA3D_CULL_NONE    1
#घोषणा SVGA3D_CULL_FRONT   2
#घोषणा SVGA3D_CULL_BACK    3
#घोषणा SVGA3D_CULL_MAX     4
प्रकार uपूर्णांक8 SVGA3dCullMode;

#घोषणा SVGA3D_COMPARISON_INVALID         0
#घोषणा SVGA3D_COMPARISON_MIN             1
#घोषणा SVGA3D_COMPARISON_NEVER           1
#घोषणा SVGA3D_COMPARISON_LESS            2
#घोषणा SVGA3D_COMPARISON_EQUAL           3
#घोषणा SVGA3D_COMPARISON_LESS_EQUAL      4
#घोषणा SVGA3D_COMPARISON_GREATER         5
#घोषणा SVGA3D_COMPARISON_NOT_EQUAL       6
#घोषणा SVGA3D_COMPARISON_GREATER_EQUAL   7
#घोषणा SVGA3D_COMPARISON_ALWAYS          8
#घोषणा SVGA3D_COMPARISON_MAX             9
प्रकार uपूर्णांक8 SVGA3dComparisonFunc;

/*
 * SVGA3D_MULTISAMPLE_RAST_DISABLE disables MSAA क्रम all primitives.
 * SVGA3D_MULTISAMPLE_RAST_DISABLE_LINE, which is supported in SM41,
 * disables MSAA क्रम lines only.
 */
#घोषणा SVGA3D_MULTISAMPLE_RAST_DISABLE        0
#घोषणा SVGA3D_MULTISAMPLE_RAST_ENABLE         1
#घोषणा SVGA3D_MULTISAMPLE_RAST_DX_MAX         1
#घोषणा SVGA3D_MULTISAMPLE_RAST_DISABLE_LINE   2
#घोषणा SVGA3D_MULTISAMPLE_RAST_MAX            2
प्रकार uपूर्णांक8 SVGA3dMultisampleRastEnable;

#घोषणा SVGA3D_DX_MAX_VERTEXBUFFERS 32
#घोषणा SVGA3D_DX_MAX_VERTEXINPUTREGISTERS 16
#घोषणा SVGA3D_DX_SM41_MAX_VERTEXINPUTREGISTERS 32
#घोषणा SVGA3D_DX_MAX_SOTARGETS 4
#घोषणा SVGA3D_DX_MAX_SRVIEWS 128
#घोषणा SVGA3D_DX_MAX_CONSTBUFFERS 16
#घोषणा SVGA3D_DX_MAX_SAMPLERS 16
#घोषणा SVGA3D_DX_MAX_CLASS_INSTANCES 253

#घोषणा SVGA3D_DX_MAX_CONSTBUF_BINDING_SIZE (4096 * 4 * (uपूर्णांक32)माप(uपूर्णांक32))

प्रकार uपूर्णांक32 SVGA3dShaderResourceViewId;
प्रकार uपूर्णांक32 SVGA3dRenderTargetViewId;
प्रकार uपूर्णांक32 SVGA3dDepthStencilViewId;
प्रकार uपूर्णांक32 SVGA3dUAViewId;

प्रकार uपूर्णांक32 SVGA3dShaderId;
प्रकार uपूर्णांक32 SVGA3dElementLayoutId;
प्रकार uपूर्णांक32 SVGA3dSamplerId;
प्रकार uपूर्णांक32 SVGA3dBlendStateId;
प्रकार uपूर्णांक32 SVGA3dDepthStencilStateId;
प्रकार uपूर्णांक32 SVGA3dRasterizerStateId;
प्रकार uपूर्णांक32 SVGA3dQueryId;
प्रकार uपूर्णांक32 SVGA3dStreamOutputId;

प्रकार जोड़ अणु
   काष्ठा अणु
      भग्न r;
      भग्न g;
      भग्न b;
      भग्न a;
   पूर्ण;

   भग्न value[4];
पूर्ण SVGA3dRGBAFloat;

प्रकार जोड़ अणु
   काष्ठा अणु
      uपूर्णांक32 r;
      uपूर्णांक32 g;
      uपूर्णांक32 b;
      uपूर्णांक32 a;
   पूर्ण;

   uपूर्णांक32 value[4];
पूर्ण SVGA3dRGBAUपूर्णांक32;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 cid;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAOTableDXContextEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineContext;   /* SVGA_3D_CMD_DX_DEFINE_CONTEXT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyContext;   /* SVGA_3D_CMD_DX_DESTROY_CONTEXT */

/*
 * Bind a DX context.
 *
 * validContents should be set to 0 क्रम new contexts,
 * and 1 अगर this is an old context which is getting paged
 * back on to the device.
 *
 * For new contexts, it is recommended that the driver
 * issue commands to initialize all पूर्णांकeresting state
 * prior to rendering.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBindContext अणु
   uपूर्णांक32 cid;
   SVGAMobId mobid;
   uपूर्णांक32 validContents;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBindContext;   /* SVGA_3D_CMD_DX_BIND_CONTEXT */

/*
 * Readback a DX context.
 * (Request that the device flush the contents back पूर्णांकo guest memory.)
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXReadbackContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXReadbackContext;   /* SVGA_3D_CMD_DX_READBACK_CONTEXT */

/*
 * Invalidate a guest-backed context.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXInvalidateContext अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXInvalidateContext;   /* SVGA_3D_CMD_DX_INVALIDATE_CONTEXT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetSingleConstantBuffer अणु
   uपूर्णांक32 slot;
   SVGA3dShaderType type;
   SVGA3dSurfaceId sid;
   uपूर्णांक32 offsetInBytes;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetSingleConstantBuffer;
/* SVGA_3D_CMD_DX_SET_SINGLE_CONSTANT_BUFFER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetShaderResources अणु
   uपूर्णांक32 startView;
   SVGA3dShaderType type;

   /*
    * Followed by a variable number of SVGA3dShaderResourceViewId's.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetShaderResources; /* SVGA_3D_CMD_DX_SET_SHADER_RESOURCES */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetShader अणु
   SVGA3dShaderId shaderId;
   SVGA3dShaderType type;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetShader; /* SVGA_3D_CMD_DX_SET_SHADER */

प्रकार जोड़ अणु
   काष्ठा अणु
      uपूर्णांक32 cbOffset : 12;
      uपूर्णांक32 cbId     : 4;
      uपूर्णांक32 baseSamp : 4;
      uपूर्णांक32 baseTex  : 7;
      uपूर्णांक32 reserved : 5;
   पूर्ण;
   uपूर्णांक32 value;
पूर्ण SVGA3dIfaceData;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetShaderIface अणु
   SVGA3dShaderType type;
   uपूर्णांक32 numClassInstances;
   uपूर्णांक32 index;
   uपूर्णांक32 अगरace;
   SVGA3dIfaceData data;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetShaderIface; /* SVGA_3D_CMD_DX_SET_SHADER_IFACE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBindShaderIface अणु
   uपूर्णांक32 cid;
   SVGAMobId mobid;
   uपूर्णांक32 offsetInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBindShaderIface; /* SVGA_3D_CMD_DX_BIND_SHADER_IFACE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetSamplers अणु
   uपूर्णांक32 startSampler;
   SVGA3dShaderType type;

   /*
    * Followed by a variable number of SVGA3dSamplerId's.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetSamplers; /* SVGA_3D_CMD_DX_SET_SAMPLERS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDraw अणु
   uपूर्णांक32 vertexCount;
   uपूर्णांक32 startVertexLocation;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDraw; /* SVGA_3D_CMD_DX_DRAW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDrawIndexed अणु
   uपूर्णांक32 indexCount;
   uपूर्णांक32 startIndexLocation;
   पूर्णांक32  baseVertexLocation;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDrawIndexed; /* SVGA_3D_CMD_DX_DRAW_INDEXED */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDrawInstanced अणु
   uपूर्णांक32 vertexCountPerInstance;
   uपूर्णांक32 instanceCount;
   uपूर्णांक32 startVertexLocation;
   uपूर्णांक32 startInstanceLocation;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDrawInstanced; /* SVGA_3D_CMD_DX_DRAW_INSTANCED */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDrawIndexedInstanced अणु
   uपूर्णांक32 indexCountPerInstance;
   uपूर्णांक32 instanceCount;
   uपूर्णांक32 startIndexLocation;
   पूर्णांक32  baseVertexLocation;
   uपूर्णांक32 startInstanceLocation;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDrawIndexedInstanced; /* SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDrawIndexedInstancedIndirect अणु
   SVGA3dSurfaceId argsBufferSid;
   uपूर्णांक32 byteOffsetForArgs;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDrawIndexedInstancedIndirect;
/* SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED_INसूचीECT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDrawInstancedIndirect अणु
   SVGA3dSurfaceId argsBufferSid;
   uपूर्णांक32 byteOffsetForArgs;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDrawInstancedIndirect;
/* SVGA_3D_CMD_DX_DRAW_INSTANCED_INसूचीECT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDrawAuto अणु
   uपूर्णांक32 pad0;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDrawAuto; /* SVGA_3D_CMD_DX_DRAW_AUTO */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDispatch अणु
   uपूर्णांक32 thपढ़ोGroupCountX;
   uपूर्णांक32 thपढ़ोGroupCountY;
   uपूर्णांक32 thपढ़ोGroupCountZ;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDispatch;
/* SVGA_3D_CMD_DX_DISPATCH */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDispatchIndirect अणु
   SVGA3dSurfaceId argsBufferSid;
   uपूर्णांक32 byteOffsetForArgs;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDispatchIndirect;
/* SVGA_3D_CMD_DX_DISPATCH_INसूचीECT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetInputLayout अणु
   SVGA3dElementLayoutId elementLayoutId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetInputLayout; /* SVGA_3D_CMD_DX_SET_INPUT_LAYOUT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dVertexBuffer अणु
   SVGA3dSurfaceId sid;
   uपूर्णांक32 stride;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dVertexBuffer;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetVertexBuffers अणु
   uपूर्णांक32 startBuffer;
   /* Followed by a variable number of SVGA3dVertexBuffer's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetVertexBuffers; /* SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetIndexBuffer अणु
   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetIndexBuffer; /* SVGA_3D_CMD_DX_SET_INDEX_BUFFER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetTopology अणु
   SVGA3dPrimitiveType topology;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetTopology; /* SVGA_3D_CMD_DX_SET_TOPOLOGY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetRenderTarमाला_लो अणु
   SVGA3dDepthStencilViewId depthStencilViewId;
   /* Followed by a variable number of SVGA3dRenderTargetViewId's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetRenderTarमाला_लो; /* SVGA_3D_CMD_DX_SET_RENDERTARGETS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetBlendState अणु
   SVGA3dBlendStateId blendId;
   भग्न blendFactor[4];
   uपूर्णांक32 sampleMask;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetBlendState; /* SVGA_3D_CMD_DX_SET_BLEND_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetDepthStencilState अणु
   SVGA3dDepthStencilStateId depthStencilId;
   uपूर्णांक32 stencilRef;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetDepthStencilState; /* SVGA_3D_CMD_DX_SET_DEPTHSTENCIL_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetRasterizerState अणु
   SVGA3dRasterizerStateId rasterizerId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetRasterizerState; /* SVGA_3D_CMD_DX_SET_RASTERIZER_STATE */

#घोषणा SVGA3D_DXQUERY_FLAG_PREDICATEHINT (1 << 0)
प्रकार uपूर्णांक32 SVGA3dDXQueryFlags;

/*
 * The SVGADXQueryDeviceState and SVGADXQueryDeviceBits are used by the device
 * to track query state transitions, but are not पूर्णांकended to be used by the
 * driver.
 */
#घोषणा SVGADX_QDSTATE_INVALID   ((uपूर्णांक8)-1) /* Query has no state */
#घोषणा SVGADX_QDSTATE_MIN       0
#घोषणा SVGADX_QDSTATE_IDLE      0   /* Query hasn't started yet */
#घोषणा SVGADX_QDSTATE_ACTIVE    1   /* Query is actively gathering data */
#घोषणा SVGADX_QDSTATE_PENDING   2   /* Query is रुकोing क्रम results */
#घोषणा SVGADX_QDSTATE_FINISHED  3   /* Query has completed */
#घोषणा SVGADX_QDSTATE_MAX       4
प्रकार uपूर्णांक8 SVGADXQueryDeviceState;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dQueryTypeUपूर्णांक8 type;
   uपूर्णांक16 pad0;
   SVGADXQueryDeviceState state;
   SVGA3dDXQueryFlags flags;
   SVGAMobId mobid;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXQueryEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineQuery अणु
   SVGA3dQueryId queryId;
   SVGA3dQueryType type;
   SVGA3dDXQueryFlags flags;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineQuery; /* SVGA_3D_CMD_DX_DEFINE_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyQuery अणु
   SVGA3dQueryId queryId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyQuery; /* SVGA_3D_CMD_DX_DESTROY_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBindQuery अणु
   SVGA3dQueryId queryId;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBindQuery; /* SVGA_3D_CMD_DX_BIND_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetQueryOffset अणु
   SVGA3dQueryId queryId;
   uपूर्णांक32 mobOffset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetQueryOffset; /* SVGA_3D_CMD_DX_SET_QUERY_OFFSET */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBeginQuery अणु
   SVGA3dQueryId queryId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBeginQuery; /* SVGA_3D_CMD_DX_QUERY_BEGIN */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXEndQuery अणु
   SVGA3dQueryId queryId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXEndQuery; /* SVGA_3D_CMD_DX_QUERY_END */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXReadbackQuery अणु
   SVGA3dQueryId queryId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXReadbackQuery; /* SVGA_3D_CMD_DX_READBACK_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXMoveQuery अणु
   SVGA3dQueryId queryId;
   SVGAMobId mobid;
   uपूर्णांक32 mobOffset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXMoveQuery; /* SVGA_3D_CMD_DX_MOVE_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBindAllQuery अणु
   uपूर्णांक32 cid;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBindAllQuery; /* SVGA_3D_CMD_DX_BIND_ALL_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXReadbackAllQuery अणु
   uपूर्णांक32 cid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXReadbackAllQuery; /* SVGA_3D_CMD_DX_READBACK_ALL_QUERY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetPredication अणु
   SVGA3dQueryId queryId;
   uपूर्णांक32 predicateValue;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetPredication; /* SVGA_3D_CMD_DX_SET_PREDICATION */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा MKS3dDXSOState अणु
   uपूर्णांक32 offset;       /* Starting offset */
   uपूर्णांक32 पूर्णांकOffset;    /* Internal offset */
   uपूर्णांक32 vertexCount;  /* vertices written */
   uपूर्णांक32 dead;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dDXSOState;

/* Set the offset field to this value to append SO values to the buffer */
#घोषणा SVGA3D_DX_SO_OFFSET_APPEND ((uपूर्णांक32) ~0u)

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dSoTarget अणु
   SVGA3dSurfaceId sid;
   uपूर्णांक32 offset;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dSoTarget;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetSOTarमाला_लो अणु
   uपूर्णांक32 pad0;
   /* Followed by a variable number of SVGA3dSOTarget's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetSOTarमाला_लो; /* SVGA_3D_CMD_DX_SET_SOTARGETS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dViewport
अणु
   भग्न x;
   भग्न y;
   भग्न width;
   भग्न height;
   भग्न minDepth;
   भग्न maxDepth;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dViewport;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetViewports अणु
   uपूर्णांक32 pad0;
   /* Followed by a variable number of SVGA3dViewport's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetViewports; /* SVGA_3D_CMD_DX_SET_VIEWPORTS */

#घोषणा SVGA3D_DX_MAX_VIEWPORTS  16

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetScissorRects अणु
   uपूर्णांक32 pad0;
   /* Followed by a variable number of SVGASignedRect's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetScissorRects; /* SVGA_3D_CMD_DX_SET_SCISSORRECTS */

#घोषणा SVGA3D_DX_MAX_SCISSORRECTS  16

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXClearRenderTargetView अणु
   SVGA3dRenderTargetViewId renderTargetViewId;
   SVGA3dRGBAFloat rgba;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXClearRenderTargetView; /* SVGA_3D_CMD_DX_CLEAR_RENDERTARGET_VIEW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXClearDepthStencilView अणु
   uपूर्णांक16 flags;
   uपूर्णांक16 stencil;
   SVGA3dDepthStencilViewId depthStencilViewId;
   भग्न depth;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXClearDepthStencilView; /* SVGA_3D_CMD_DX_CLEAR_DEPTHSTENCIL_VIEW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXPredCopyRegion अणु
   SVGA3dSurfaceId dstSid;
   uपूर्णांक32 dstSubResource;
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcSubResource;
   SVGA3dCopyBox box;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXPredCopyRegion;
/* SVGA_3D_CMD_DX_PRED_COPY_REGION */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXPredCopy अणु
   SVGA3dSurfaceId dstSid;
   SVGA3dSurfaceId srcSid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXPredCopy; /* SVGA_3D_CMD_DX_PRED_COPY */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXPredConvertRegion अणु
   SVGA3dSurfaceId dstSid;
   uपूर्णांक32 dstSubResource;
   SVGA3dBox destBox;
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcSubResource;
   SVGA3dBox srcBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXPredConvertRegion; /* SVGA_3D_CMD_DX_PRED_CONVERT_REGION */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXPredConvert अणु
   SVGA3dSurfaceId dstSid;
   SVGA3dSurfaceId srcSid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXPredConvert; /* SVGA_3D_CMD_DX_PRED_CONVERT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBufferCopy अणु
   SVGA3dSurfaceId dest;
   SVGA3dSurfaceId src;
   uपूर्णांक32 destX;
   uपूर्णांक32 srcX;
   uपूर्णांक32 width;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBufferCopy;
/* SVGA_3D_CMD_DX_BUFFER_COPY */

/*
 * Perक्रमm a surface copy between a multisample, and a non-multisampled
 * surface.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceId dstSid;
   uपूर्णांक32 dstSubResource;
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcSubResource;
   SVGA3dSurfaceFormat copyFormat;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXResolveCopy;               /* SVGA_3D_CMD_DX_RESOLVE_COPY */

/*
 * Perक्रमm a predicated surface copy between a multisample, and a
 * non-multisampled surface.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceId dstSid;
   uपूर्णांक32 dstSubResource;
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcSubResource;
   SVGA3dSurfaceFormat copyFormat;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXPredResolveCopy;           /* SVGA_3D_CMD_DX_PRED_RESOLVE_COPY */

प्रकार uपूर्णांक32 SVGA3dDXPresentBltMode;
#घोषणा SVGADX_PRESENTBLT_LINEAR           (1 << 0)
#घोषणा SVGADX_PRESENTBLT_FORCE_SRC_SRGB   (1 << 1)
#घोषणा SVGADX_PRESENTBLT_FORCE_SRC_XRBIAS (1 << 2)
#घोषणा SVGADX_PRESENTBLT_MODE_MAX         (1 << 3)

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXPresentBlt अणु
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcSubResource;
   SVGA3dSurfaceId dstSid;
   uपूर्णांक32 destSubResource;
   SVGA3dBox boxSrc;
   SVGA3dBox boxDest;
   SVGA3dDXPresentBltMode mode;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXPresentBlt; /* SVGA_3D_CMD_DX_PRESENTBLT*/

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXGenMips अणु
   SVGA3dShaderResourceViewId shaderResourceViewId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXGenMips; /* SVGA_3D_CMD_DX_GENMIPS */

/*
 * Update a sub-resource in a guest-backed resource.
 * (Inक्रमm the device that the guest-contents have been updated.)
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXUpdateSubResource अणु
   SVGA3dSurfaceId sid;
   uपूर्णांक32 subResource;
   SVGA3dBox box;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXUpdateSubResource;   /* SVGA_3D_CMD_DX_UPDATE_SUBRESOURCE */

/*
 * Readback a subresource in a guest-backed resource.
 * (Request the device to flush the dirty contents पूर्णांकo the guest.)
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXReadbackSubResource अणु
   SVGA3dSurfaceId sid;
   uपूर्णांक32 subResource;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXReadbackSubResource;   /* SVGA_3D_CMD_DX_READBACK_SUBRESOURCE */

/*
 * Invalidate an image in a guest-backed surface.
 * (Notअगरy the device that the contents can be lost.)
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXInvalidateSubResource अणु
   SVGA3dSurfaceId sid;
   uपूर्णांक32 subResource;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXInvalidateSubResource;   /* SVGA_3D_CMD_DX_INVALIDATE_SUBRESOURCE */


/*
 * Raw byte wise transfer from a buffer surface पूर्णांकo another surface
 * of the requested box.  Supported अगर 3d is enabled and SVGA_CAP_DX
 * is set.  This command करोes not take a context.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXTransferFromBuffer अणु
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcOffset;
   uपूर्णांक32 srcPitch;
   uपूर्णांक32 srcSlicePitch;
   SVGA3dSurfaceId destSid;
   uपूर्णांक32 destSubResource;
   SVGA3dBox destBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXTransferFromBuffer;   /* SVGA_3D_CMD_DX_TRANSFER_FROM_BUFFER */


#घोषणा SVGA3D_TRANSFER_TO_BUFFER_READBACK   (1 << 0)
#घोषणा SVGA3D_TRANSFER_TO_BUFFER_FLAGS_MASK (1 << 0)
प्रकार uपूर्णांक32 SVGA3dTransferToBufferFlags;

/*
 * Raw byte wise transfer to a buffer surface from another surface
 * of the requested box.  Supported अगर SVGA_CAP_DX2 is set.  This
 * command करोes not take a context.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXTransferToBuffer अणु
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcSubResource;
   SVGA3dBox srcBox;
   SVGA3dSurfaceId destSid;
   uपूर्णांक32 destOffset;
   uपूर्णांक32 destPitch;
   uपूर्णांक32 destSlicePitch;
   SVGA3dTransferToBufferFlags flags;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXTransferToBuffer;   /* SVGA_3D_CMD_DX_TRANSFER_TO_BUFFER */


/*
 * Raw byte wise transfer from a buffer surface पूर्णांकo another surface
 * of the requested box.  Supported अगर SVGA3D_DEVCAP_DXCONTEXT is set.
 * The context is implied from the command buffer header.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXPredTransferFromBuffer अणु
   SVGA3dSurfaceId srcSid;
   uपूर्णांक32 srcOffset;
   uपूर्णांक32 srcPitch;
   uपूर्णांक32 srcSlicePitch;
   SVGA3dSurfaceId destSid;
   uपूर्णांक32 destSubResource;
   SVGA3dBox destBox;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXPredTransferFromBuffer;
/* SVGA_3D_CMD_DX_PRED_TRANSFER_FROM_BUFFER */


प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSurfaceCopyAndReadback अणु
   SVGA3dSurfaceId srcSid;
   SVGA3dSurfaceId destSid;
   SVGA3dCopyBox box;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSurfaceCopyAndReadback;
/* SVGA_3D_CMD_DX_SURFACE_COPY_AND_READBACK */

/*
 * SVGA_DX_HINT_NONE: Does nothing.
 *
 * SVGA_DX_HINT_PREFETCH_OBJECT:
 * SVGA_DX_HINT_PREEVICT_OBJECT:
 *      Consumes a SVGAObjectRef, and hपूर्णांकs that the host should consider
 *      fetching/evicting the specअगरied object.
 *
 *      An id of SVGA3D_INVALID_ID can be used अगर the guest isn't sure
 *      what object was affected.  (For instance, अगर the guest knows that
 *      it is about to evict a DXShader, but करोesn't know precisely which one,
 *      the device can still use this to help limit it's search, or track
 *      how many page-outs have happened.)
 *
 * SVGA_DX_HINT_PREFETCH_COBJECT:
 * SVGA_DX_HINT_PREEVICT_COBJECT:
 *      Same as the above, except they consume an SVGACObjectRef.
 */
प्रकार uपूर्णांक32 SVGADXHपूर्णांकId;
#घोषणा SVGA_DX_HINT_NONE              0
#घोषणा SVGA_DX_HINT_PREFETCH_OBJECT   1
#घोषणा SVGA_DX_HINT_PREEVICT_OBJECT   2
#घोषणा SVGA_DX_HINT_PREFETCH_COBJECT  3
#घोषणा SVGA_DX_HINT_PREEVICT_COBJECT  4
#घोषणा SVGA_DX_Hपूर्णांक_उच्च               5

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGAObjectRef अणु
   SVGAOTableType type;
   uपूर्णांक32 id;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGAObjectRef;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGACObjectRef अणु
   SVGACOTableType type;
   uपूर्णांक32 cid;
   uपूर्णांक32 id;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACObjectRef;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXHपूर्णांक अणु
   SVGADXHपूर्णांकId hपूर्णांकId;

   /*
    * Followed by variable sized data depending on the hपूर्णांकId.
    */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXHपूर्णांक;
/* SVGA_3D_CMD_DX_HINT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBufferUpdate अणु
   SVGA3dSurfaceId sid;
   uपूर्णांक32 x;
   uपूर्णांक32 width;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBufferUpdate;
/* SVGA_3D_CMD_DX_BUFFER_UPDATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetConstantBufferOffset अणु
   uपूर्णांक32 slot;
   uपूर्णांक32 offsetInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetConstantBufferOffset;

प्रकार SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetVSConstantBufferOffset;
/* SVGA_3D_CMD_DX_SET_VS_CONSTANT_BUFFER_OFFSET */

प्रकार SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetPSConstantBufferOffset;
/* SVGA_3D_CMD_DX_SET_PS_CONSTANT_BUFFER_OFFSET */

प्रकार SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetGSConstantBufferOffset;
/* SVGA_3D_CMD_DX_SET_GS_CONSTANT_BUFFER_OFFSET */

प्रकार SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetHSConstantBufferOffset;
/* SVGA_3D_CMD_DX_SET_HS_CONSTANT_BUFFER_OFFSET */

प्रकार SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetDSConstantBufferOffset;
/* SVGA_3D_CMD_DX_SET_DS_CONSTANT_BUFFER_OFFSET */

प्रकार SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetCSConstantBufferOffset;
/* SVGA_3D_CMD_DX_SET_CS_CONSTANT_BUFFER_OFFSET */


#घोषणा SVGA3D_BUFFEREX_SRV_RAW        (1 << 0)
#घोषणा SVGA3D_BUFFEREX_SRV_FLAGS_MAX  (1 << 1)
#घोषणा SVGA3D_BUFFEREX_SRV_FLAGS_MASK (SVGA3D_BUFFEREX_SRV_FLAGS_MAX - 1)
प्रकार uपूर्णांक32 SVGA3dBufferExFlags;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   जोड़ अणु
      काष्ठा अणु
         uपूर्णांक32 firstElement;
         uपूर्णांक32 numElements;
         uपूर्णांक32 pad0;
         uपूर्णांक32 pad1;
      पूर्ण buffer;
      काष्ठा अणु
         uपूर्णांक32 mostDetailedMip;
         uपूर्णांक32 firstArraySlice;
         uपूर्णांक32 mipLevels;
         uपूर्णांक32 arraySize;
      पूर्ण tex; /* 1d, 2d, 3d, cube */
      काष्ठा अणु
         uपूर्णांक32 firstElement;
         uपूर्णांक32 numElements;
         SVGA3dBufferExFlags flags;
         uपूर्णांक32 pad0;
      पूर्ण bufferex;
   पूर्ण;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dShaderResourceViewDesc;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;
   SVGA3dShaderResourceViewDesc desc;
   uपूर्णांक32 pad;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXSRViewEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineShaderResourceView अणु
   SVGA3dShaderResourceViewId shaderResourceViewId;

   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;

   SVGA3dShaderResourceViewDesc desc;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineShaderResourceView;
/* SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyShaderResourceView अणु
   SVGA3dShaderResourceViewId shaderResourceViewId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyShaderResourceView;
/* SVGA_3D_CMD_DX_DESTROY_SHADERRESOURCE_VIEW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dRenderTargetViewDesc अणु
   जोड़ अणु
      काष्ठा अणु
         uपूर्णांक32 firstElement;
         uपूर्णांक32 numElements;
         uपूर्णांक32 padding0;
      पूर्ण buffer;
      काष्ठा अणु
         uपूर्णांक32 mipSlice;
         uपूर्णांक32 firstArraySlice;
         uपूर्णांक32 arraySize;
      पूर्ण tex;                    /* 1d, 2d, cube */
      काष्ठा अणु
         uपूर्णांक32 mipSlice;
         uपूर्णांक32 firstW;
         uपूर्णांक32 wSize;
      पूर्ण tex3D;
   पूर्ण;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dRenderTargetViewDesc;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;
   SVGA3dRenderTargetViewDesc desc;
   uपूर्णांक32 pad[2];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXRTViewEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineRenderTargetView अणु
   SVGA3dRenderTargetViewId renderTargetViewId;

   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;

   SVGA3dRenderTargetViewDesc desc;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineRenderTargetView;
/* SVGA_3D_CMD_DX_DEFINE_RENDERTARGET_VIEW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyRenderTargetView अणु
   SVGA3dRenderTargetViewId renderTargetViewId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyRenderTargetView;
/* SVGA_3D_CMD_DX_DESTROY_RENDERTARGET_VIEW */

/*
 */
#घोषणा SVGA3D_DXDSVIEW_CREATE_READ_ONLY_DEPTH   0x01
#घोषणा SVGA3D_DXDSVIEW_CREATE_READ_ONLY_STENCIL 0x02
#घोषणा SVGA3D_DXDSVIEW_CREATE_FLAG_MASK         0x03
प्रकार uपूर्णांक8 SVGA3DCreateDSViewFlags;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;
   uपूर्णांक32 mipSlice;
   uपूर्णांक32 firstArraySlice;
   uपूर्णांक32 arraySize;
   SVGA3DCreateDSViewFlags flags;
   uपूर्णांक8 pad0;
   uपूर्णांक16 pad1;
   uपूर्णांक32 pad2;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXDSViewEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineDepthStencilView अणु
   SVGA3dDepthStencilViewId depthStencilViewId;

   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;
   uपूर्णांक32 mipSlice;
   uपूर्णांक32 firstArraySlice;
   uपूर्णांक32 arraySize;
   SVGA3DCreateDSViewFlags flags;
   uपूर्णांक8 pad0;
   uपूर्णांक16 pad1;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineDepthStencilView;
/* SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW */

/*
 * Version 2 needed in order to start validating and using the flags
 * field.  Unक्रमtunately the device wasn't validating or using the
 * flags field and the driver wasn't initializing it in shipped code,
 * so a new version of the command is needed to allow that code to
 * जारी to work.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineDepthStencilView_v2 अणु
   SVGA3dDepthStencilViewId depthStencilViewId;

   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;
   uपूर्णांक32 mipSlice;
   uपूर्णांक32 firstArraySlice;
   uपूर्णांक32 arraySize;
   SVGA3DCreateDSViewFlags flags;
   uपूर्णांक8 pad0;
   uपूर्णांक16 pad1;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineDepthStencilView_v2;
/* SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW_V2 */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyDepthStencilView अणु
   SVGA3dDepthStencilViewId depthStencilViewId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyDepthStencilView;
/* SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_VIEW */


#घोषणा SVGA3D_UABUFFER_RAW     (1 << 0)
#घोषणा SVGA3D_UABUFFER_APPEND  (1 << 1)
#घोषणा SVGA3D_UABUFFER_COUNTER (1 << 2)
प्रकार uपूर्णांक32 SVGA3dUABufferFlags;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   जोड़ अणु
      काष्ठा अणु
         uपूर्णांक32 firstElement;
         uपूर्णांक32 numElements;
         SVGA3dUABufferFlags flags;
         uपूर्णांक32 padding0;
         uपूर्णांक32 padding1;
      पूर्ण buffer;
      काष्ठा अणु
         uपूर्णांक32 mipSlice;
         uपूर्णांक32 firstArraySlice;
         uपूर्णांक32 arraySize;
         uपूर्णांक32 padding0;
         uपूर्णांक32 padding1;
      पूर्ण tex;  /* 1d, 2d */
      काष्ठा अणु
         uपूर्णांक32 mipSlice;
         uपूर्णांक32 firstW;
         uपूर्णांक32 wSize;
         uपूर्णांक32 padding0;
         uपूर्णांक32 padding1;
      पूर्ण tex3D;
   पूर्ण;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dUAViewDesc;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;
   SVGA3dUAViewDesc desc;
   uपूर्णांक32 काष्ठाureCount;
   uपूर्णांक32 pad[7];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXUAViewEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineUAView अणु
   SVGA3dUAViewId uaViewId;

   SVGA3dSurfaceId sid;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dResourceType resourceDimension;

   SVGA3dUAViewDesc desc;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineUAView;
/* SVGA_3D_CMD_DX_DEFINE_UA_VIEW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyUAView अणु
   SVGA3dUAViewId uaViewId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyUAView;
/* SVGA_3D_CMD_DX_DESTROY_UA_VIEW */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXClearUAViewUपूर्णांक अणु
   SVGA3dUAViewId uaViewId;
   SVGA3dRGBAUपूर्णांक32 value;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXClearUAViewUपूर्णांक;
/* SVGA_3D_CMD_DX_CLEAR_UA_VIEW_UINT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXClearUAViewFloat अणु
   SVGA3dUAViewId uaViewId;
   SVGA3dRGBAFloat value;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXClearUAViewFloat;
/* SVGA_3D_CMD_DX_CLEAR_UA_VIEW_FLOAT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXCopyStructureCount अणु
   SVGA3dUAViewId srcUAViewId;
   SVGA3dSurfaceId destSid;
   uपूर्णांक32 destByteOffset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXCopyStructureCount;
/* SVGA_3D_CMD_DX_COPY_STRUCTURE_COUNT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetStructureCount अणु
   SVGA3dUAViewId uaViewId;
   uपूर्णांक32 काष्ठाureCount;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetStructureCount;
/* SVGA_3D_CMD_DX_SET_STRUCTURE_COUNT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetUAViews अणु
   uपूर्णांक32 uavSpliceIndex;
   /* Followed by a variable number of SVGA3dUAViewId's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetUAViews; /* SVGA_3D_CMD_DX_SET_UA_VIEWS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetCSUAViews अणु
   uपूर्णांक32 startIndex;
   /* Followed by a variable number of SVGA3dUAViewId's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetCSUAViews; /* SVGA_3D_CMD_DX_SET_CS_UA_VIEWS */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dInputElementDesc अणु
   uपूर्णांक32 inputSlot;
   uपूर्णांक32 alignedByteOffset;
   SVGA3dSurfaceFormat क्रमmat;
   SVGA3dInputClassअगरication inputSlotClass;
   uपूर्णांक32 instanceDataStepRate;
   uपूर्णांक32 inputRegister;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dInputElementDesc;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक32 elid;
   uपूर्णांक32 numDescs;
   SVGA3dInputElementDesc descs[32];
   uपूर्णांक32 pad[62];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXElementLayoutEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineElementLayout अणु
   SVGA3dElementLayoutId elementLayoutId;
   /* Followed by a variable number of SVGA3dInputElementDesc's. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineElementLayout;
/* SVGA_3D_CMD_DX_DEFINE_ELEMENTLAYOUT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyElementLayout अणु
   SVGA3dElementLayoutId elementLayoutId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyElementLayout;
/* SVGA_3D_CMD_DX_DESTROY_ELEMENTLAYOUT */


#घोषणा SVGA3D_DX_MAX_RENDER_TARGETS 8

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dDXBlendStatePerRT अणु
      uपूर्णांक8 blendEnable;
      uपूर्णांक8 srcBlend;
      uपूर्णांक8 destBlend;
      uपूर्णांक8 blendOp;
      uपूर्णांक8 srcBlendAlpha;
      uपूर्णांक8 destBlendAlpha;
      uपूर्णांक8 blendOpAlpha;
      SVGA3dColorWriteEnable renderTargetWriteMask;
      uपूर्णांक8 logicOpEnable;
      uपूर्णांक8 logicOp;
      uपूर्णांक16 pad0;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dDXBlendStatePerRT;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक8 alphaToCoverageEnable;
   uपूर्णांक8 independentBlendEnable;
   uपूर्णांक16 pad0;
   SVGA3dDXBlendStatePerRT perRT[SVGA3D_MAX_RENDER_TARGETS];
   uपूर्णांक32 pad1[7];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXBlendStateEntry;

/*
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineBlendState अणु
   SVGA3dBlendStateId blendId;
   uपूर्णांक8 alphaToCoverageEnable;
   uपूर्णांक8 independentBlendEnable;
   uपूर्णांक16 pad0;
   SVGA3dDXBlendStatePerRT perRT[SVGA3D_MAX_RENDER_TARGETS];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineBlendState; /* SVGA_3D_CMD_DX_DEFINE_BLEND_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyBlendState अणु
   SVGA3dBlendStateId blendId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyBlendState; /* SVGA_3D_CMD_DX_DESTROY_BLEND_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक8 depthEnable;
   SVGA3dDepthWriteMask depthWriteMask;
   SVGA3dComparisonFunc depthFunc;
   uपूर्णांक8 stencilEnable;
   uपूर्णांक8 frontEnable;
   uपूर्णांक8 backEnable;
   uपूर्णांक8 stencilReadMask;
   uपूर्णांक8 stencilWriteMask;

   uपूर्णांक8 frontStencilFailOp;
   uपूर्णांक8 frontStencilDepthFailOp;
   uपूर्णांक8 frontStencilPassOp;
   SVGA3dComparisonFunc frontStencilFunc;

   uपूर्णांक8 backStencilFailOp;
   uपूर्णांक8 backStencilDepthFailOp;
   uपूर्णांक8 backStencilPassOp;
   SVGA3dComparisonFunc backStencilFunc;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXDepthStencilEntry;

/*
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineDepthStencilState अणु
   SVGA3dDepthStencilStateId depthStencilId;

   uपूर्णांक8 depthEnable;
   SVGA3dDepthWriteMask depthWriteMask;
   SVGA3dComparisonFunc depthFunc;
   uपूर्णांक8 stencilEnable;
   uपूर्णांक8 frontEnable;
   uपूर्णांक8 backEnable;
   uपूर्णांक8 stencilReadMask;
   uपूर्णांक8 stencilWriteMask;

   uपूर्णांक8 frontStencilFailOp;
   uपूर्णांक8 frontStencilDepthFailOp;
   uपूर्णांक8 frontStencilPassOp;
   SVGA3dComparisonFunc frontStencilFunc;

   uपूर्णांक8 backStencilFailOp;
   uपूर्णांक8 backStencilDepthFailOp;
   uपूर्णांक8 backStencilPassOp;
   SVGA3dComparisonFunc backStencilFunc;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineDepthStencilState;
/* SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyDepthStencilState अणु
   SVGA3dDepthStencilStateId depthStencilId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyDepthStencilState;
/* SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक8 fillMode;
   SVGA3dCullMode cullMode;
   uपूर्णांक8 frontCounterClockwise;
   uपूर्णांक8 provokingVertexLast;
   पूर्णांक32 depthBias;
   भग्न depthBiasClamp;
   भग्न slopeScaledDepthBias;
   uपूर्णांक8 depthClipEnable;
   uपूर्णांक8 scissorEnable;
   SVGA3dMultisampleRastEnable multisampleEnable;
   uपूर्णांक8 antialiasedLineEnable;
   भग्न lineWidth;
   uपूर्णांक8 lineStippleEnable;
   uपूर्णांक8 lineStippleFactor;
   uपूर्णांक16 lineStipplePattern;
   uपूर्णांक8 क्रमcedSampleCount;
   uपूर्णांक8 mustBeZero[3];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXRasterizerStateEntry;

/*
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineRasterizerState अणु
   SVGA3dRasterizerStateId rasterizerId;

   uपूर्णांक8 fillMode;
   SVGA3dCullMode cullMode;
   uपूर्णांक8 frontCounterClockwise;
   uपूर्णांक8 provokingVertexLast;
   पूर्णांक32 depthBias;
   भग्न depthBiasClamp;
   भग्न slopeScaledDepthBias;
   uपूर्णांक8 depthClipEnable;
   uपूर्णांक8 scissorEnable;
   SVGA3dMultisampleRastEnable multisampleEnable;
   uपूर्णांक8 antialiasedLineEnable;
   भग्न lineWidth;
   uपूर्णांक8 lineStippleEnable;
   uपूर्णांक8 lineStippleFactor;
   uपूर्णांक16 lineStipplePattern;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineRasterizerState;
/* SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyRasterizerState अणु
   SVGA3dRasterizerStateId rasterizerId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyRasterizerState;
/* SVGA_3D_CMD_DX_DESTROY_RASTERIZER_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   SVGA3dFilter filter;
   uपूर्णांक8 addressU;
   uपूर्णांक8 addressV;
   uपूर्णांक8 addressW;
   uपूर्णांक8 pad0;
   भग्न mipLODBias;
   uपूर्णांक8 maxAnisotropy;
   SVGA3dComparisonFunc comparisonFunc;
   uपूर्णांक16 pad1;
   SVGA3dRGBAFloat borderColor;
   भग्न minLOD;
   भग्न maxLOD;
   uपूर्णांक32 pad2[6];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXSamplerEntry;

/*
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineSamplerState अणु
   SVGA3dSamplerId samplerId;
   SVGA3dFilter filter;
   uपूर्णांक8 addressU;
   uपूर्णांक8 addressV;
   uपूर्णांक8 addressW;
   uपूर्णांक8 pad0;
   भग्न mipLODBias;
   uपूर्णांक8 maxAnisotropy;
   SVGA3dComparisonFunc comparisonFunc;
   uपूर्णांक16 pad1;
   SVGA3dRGBAFloat borderColor;
   भग्न minLOD;
   भग्न maxLOD;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineSamplerState; /* SVGA_3D_CMD_DX_DEFINE_SAMPLER_STATE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroySamplerState अणु
   SVGA3dSamplerId samplerId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroySamplerState; /* SVGA_3D_CMD_DX_DESTROY_SAMPLER_STATE */


#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_UNDEFINED                          0
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_POSITION                           1
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_CLIP_DISTANCE                      2
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_CULL_DISTANCE                      3
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_RENDER_TARGET_ARRAY_INDEX          4
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_VIEWPORT_ARRAY_INDEX               5
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_VERTEX_ID                          6
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_PRIMITIVE_ID                       7
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_INSTANCE_ID                        8
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_IS_FRONT_FACE                      9
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_SAMPLE_INDEX                       10
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_U_EQ_0_EDGE_TESSFACTOR  11
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_V_EQ_0_EDGE_TESSFACTOR  12
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_U_EQ_1_EDGE_TESSFACTOR  13
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_V_EQ_1_EDGE_TESSFACTOR  14
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_U_INSIDE_TESSFACTOR     15
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_V_INSIDE_TESSFACTOR     16
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_U_EQ_0_EDGE_TESSFACTOR   17
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_V_EQ_0_EDGE_TESSFACTOR   18
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_W_EQ_0_EDGE_TESSFACTOR   19
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_INSIDE_TESSFACTOR        20
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_LINE_DETAIL_TESSFACTOR       21
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_LINE_DENSITY_TESSFACTOR      22
#घोषणा SVGADX_SIGNATURE_SEMANTIC_NAME_MAX                                23
प्रकार uपूर्णांक32 SVGA3dDXSignatureSemanticName;

#घोषणा SVGADX_SIGNATURE_REGISTER_COMPONENT_UNKNOWN 0
प्रकार uपूर्णांक32 SVGA3dDXSignatureRegisterComponentType;

#घोषणा SVGADX_SIGNATURE_MIN_PRECISION_DEFAULT 0
प्रकार uपूर्णांक32 SVGA3dDXSignatureMinPrecision;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dDXSignatureEntry अणु
   uपूर्णांक32 रेजिस्टरIndex;
   SVGA3dDXSignatureSemanticName semanticName;
   uपूर्णांक32 mask; /* Lower 4 bits represent X, Y, Z, W channels */
   SVGA3dDXSignatureRegisterComponentType componentType;
   SVGA3dDXSignatureMinPrecision minPrecision;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dDXShaderSignatureEntry;

#घोषणा SVGADX_SIGNATURE_HEADER_VERSION_0 0x08a92d12

/*
 * The SVGA3dDXSignatureHeader काष्ठाure is added after the shader
 * body in the mob that is bound to the shader.  It is followed by the
 * specअगरied number of SVGA3dDXSignatureEntry काष्ठाures क्रम each of
 * the three types of signatures in the order (input, output, patch
 * स्थिरants).
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dDXSignatureHeader अणु
   uपूर्णांक32 headerVersion;
   uपूर्णांक32 numInputSignatures;
   uपूर्णांक32 numOutputSignatures;
   uपूर्णांक32 numPatchConstantSignatures;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dDXShaderSignatureHeader;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineShader अणु
   SVGA3dShaderId shaderId;
   SVGA3dShaderType type;
   uपूर्णांक32 sizeInBytes; /* Number of bytes of shader text. */
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineShader; /* SVGA_3D_CMD_DX_DEFINE_SHADER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGACOTableDXShaderEntry अणु
   SVGA3dShaderType type;
   uपूर्णांक32 sizeInBytes;
   uपूर्णांक32 offsetInBytes;
   SVGAMobId mobid;
   uपूर्णांक32 pad[4];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXShaderEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyShader अणु
   SVGA3dShaderId shaderId;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyShader; /* SVGA_3D_CMD_DX_DESTROY_SHADER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBindShader अणु
   uपूर्णांक32 cid;
   uपूर्णांक32 shid;
   SVGAMobId mobid;
   uपूर्णांक32 offsetInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBindShader;   /* SVGA_3D_CMD_DX_BIND_SHADER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBindAllShader अणु
   uपूर्णांक32 cid;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBindAllShader;   /* SVGA_3D_CMD_DX_BIND_ALL_SHADER */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXCondBindAllShader अणु
   uपूर्णांक32 cid;
   SVGAMobId testMobid;
   SVGAMobId mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXCondBindAllShader;   /* SVGA_3D_CMD_DX_COND_BIND_ALL_SHADER */

/*
 * The maximum number of streamout decl's in each streamout entry.
 */
#घोषणा SVGA3D_MAX_DX10_STREAMOUT_DECLS 64
#घोषणा SVGA3D_MAX_STREAMOUT_DECLS 512

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dStreamOutputDeclarationEntry अणु
   uपूर्णांक32 outputSlot;
   uपूर्णांक32 रेजिस्टरIndex;
   uपूर्णांक8  रेजिस्टरMask;
   uपूर्णांक8  pad0;
   uपूर्णांक16 pad1;
   uपूर्णांक32 stream;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dStreamOutputDeclarationEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGAOTableStreamOutputEntry अणु
   uपूर्णांक32 numOutputStreamEntries;
   SVGA3dStreamOutputDeclarationEntry decl[SVGA3D_MAX_DX10_STREAMOUT_DECLS];
   uपूर्णांक32 streamOutputStrideInBytes[SVGA3D_DX_MAX_SOTARGETS];
   uपूर्णांक32 rasterizedStream;
   uपूर्णांक32 numOutputStreamStrides;
   uपूर्णांक32 mobid;
   uपूर्णांक32 offsetInBytes;
   uपूर्णांक8 usesMob;
   uपूर्णांक8 pad0;
   uपूर्णांक16 pad1;
   uपूर्णांक32 pad2[246];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGACOTableDXStreamOutputEntry;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineStreamOutput अणु
   SVGA3dStreamOutputId soid;
   uपूर्णांक32 numOutputStreamEntries;
   SVGA3dStreamOutputDeclarationEntry decl[SVGA3D_MAX_DX10_STREAMOUT_DECLS];
   uपूर्णांक32 streamOutputStrideInBytes[SVGA3D_DX_MAX_SOTARGETS];
   uपूर्णांक32 rasterizedStream;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineStreamOutput; /* SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT */

/*
 * Version 2 needed in order to start validating and using the
 * rasterizedStream field.  Unक्रमtunately the device wasn't validating
 * or using this field and the driver wasn't initializing it in shipped
 * code, so a new version of the command is needed to allow that code
 * to जारी to work.  Also added new numOutputStreamStrides field.
 */

#घोषणा SVGA3D_DX_SO_NO_RASTERIZED_STREAM 0xFFFFFFFF

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDefineStreamOutputWithMob अणु
   SVGA3dStreamOutputId soid;
   uपूर्णांक32 numOutputStreamEntries;
   uपूर्णांक32 numOutputStreamStrides;
   uपूर्णांक32 streamOutputStrideInBytes[SVGA3D_DX_MAX_SOTARGETS];
   uपूर्णांक32 rasterizedStream;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDefineStreamOutputWithMob;
/* SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT_WITH_MOB */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXBindStreamOutput अणु
   SVGA3dStreamOutputId soid;
   uपूर्णांक32 mobid;
   uपूर्णांक32 offsetInBytes;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXBindStreamOutput; /* SVGA_3D_CMD_DX_BIND_STREAMOUTPUT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXDestroyStreamOutput अणु
   SVGA3dStreamOutputId soid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXDestroyStreamOutput; /* SVGA_3D_CMD_DX_DESTROY_STREAMOUTPUT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetStreamOutput अणु
   SVGA3dStreamOutputId soid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetStreamOutput; /* SVGA_3D_CMD_DX_SET_STREAMOUTPUT */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetMinLOD अणु
   SVGA3dSurfaceId sid;
   भग्न minLOD;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetMinLOD; /* SVGA_3D_CMD_DX_SET_MIN_LOD */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा अणु
   uपूर्णांक64 value;
   uपूर्णांक32 mobId;
   uपूर्णांक32 mobOffset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXMobFence64;  /* SVGA_3D_CMD_DX_MOB_FENCE_64 */

/*
 * SVGA3dCmdSetCOTable --
 *
 * This command allows the guest to bind a mob to a context-object table.
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXSetCOTable अणु
   uपूर्णांक32 cid;
   uपूर्णांक32 mobid;
   SVGACOTableType type;
   uपूर्णांक32 validSizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXSetCOTable; /* SVGA_3D_CMD_DX_SET_COTABLE */

/*
 * Guests using SVGA_3D_CMD_DX_GROW_COTABLE are promising that
 * the new COTable contains the same contents as the old one, except possibly
 * क्रम some new invalid entries at the end.
 *
 * If there is an old cotable mob bound, it also has to still be valid.
 *
 * (Otherwise, guests should use the DXSetCOTableBase command.)
 */
प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXGrowCOTable अणु
   uपूर्णांक32 cid;
   uपूर्णांक32 mobid;
   SVGACOTableType type;
   uपूर्णांक32 validSizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXGrowCOTable; /* SVGA_3D_CMD_DX_GROW_COTABLE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXReadbackCOTable अणु
   uपूर्णांक32 cid;
   SVGACOTableType type;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXReadbackCOTable; /* SVGA_3D_CMD_DX_READBACK_COTABLE */

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCOTableData अणु
   uपूर्णांक32 mobid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCOTableData;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dBufferBinding अणु
   uपूर्णांक32 bufferId;
   uपूर्णांक32 stride;
   uपूर्णांक32 offset;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dBufferBinding;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dConstantBufferBinding अणु
   uपूर्णांक32 sid;
   uपूर्णांक32 offsetInBytes;
   uपूर्णांक32 sizeInBytes;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dConstantBufferBinding;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGADXInputAssemblyMobFormat अणु
   uपूर्णांक32 layoutId;
   SVGA3dBufferBinding vertexBuffers[SVGA3D_DX_MAX_VERTEXBUFFERS];
   uपूर्णांक32 indexBufferSid;
   uपूर्णांक32 pad;
   uपूर्णांक32 indexBufferOffset;
   uपूर्णांक32 indexBufferFormat;
   uपूर्णांक32 topology;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGADXInputAssemblyMobFormat;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGADXContextMobFormat अणु
   SVGADXInputAssemblyMobFormat inputAssembly;

   काष्ठा अणु
      uपूर्णांक32 blendStateId;
      uपूर्णांक32 blendFactor[4];
      uपूर्णांक32 sampleMask;
      uपूर्णांक32 depthStencilStateId;
      uपूर्णांक32 stencilRef;
      uपूर्णांक32 rasterizerStateId;
      uपूर्णांक32 depthStencilViewId;
      uपूर्णांक32 renderTargetViewIds[SVGA3D_MAX_SIMULTANEOUS_RENDER_TARGETS];
   पूर्ण renderState;

   uपूर्णांक32 pad0[8];

   काष्ठा अणु
      uपूर्णांक32 tarमाला_लो[SVGA3D_DX_MAX_SOTARGETS];
      uपूर्णांक32 soid;
   पूर्ण streamOut;

   uपूर्णांक32 pad1[10];

   uपूर्णांक32 uavSpliceIndex;

   uपूर्णांक8 numViewports;
   uपूर्णांक8 numScissorRects;
   uपूर्णांक16 pad2[1];

   uपूर्णांक32 pad3[3];

   SVGA3dViewport viewports[SVGA3D_DX_MAX_VIEWPORTS];
   uपूर्णांक32 pad4[32];

   SVGASignedRect scissorRects[SVGA3D_DX_MAX_SCISSORRECTS];
   uपूर्णांक32 pad5[64];

   काष्ठा अणु
      uपूर्णांक32 queryID;
      uपूर्णांक32 value;
   पूर्ण predication;

   SVGAMobId shaderIfaceMobid;
   uपूर्णांक32 shaderIfaceOffset;
   काष्ठा अणु
      uपूर्णांक32 shaderId;
      SVGA3dConstantBufferBinding स्थिरantBuffers[SVGA3D_DX_MAX_CONSTBUFFERS];
      uपूर्णांक32 shaderResources[SVGA3D_DX_MAX_SRVIEWS];
      uपूर्णांक32 samplers[SVGA3D_DX_MAX_SAMPLERS];
   पूर्ण shaderState[SVGA3D_NUM_SHADERTYPE];
   uपूर्णांक32 pad6[26];

   SVGA3dQueryId queryID[SVGA3D_MAX_QUERY];

   SVGA3dCOTableData cotables[SVGA_COTABLE_MAX];

   uपूर्णांक32 pad7[64];

   uपूर्णांक32 uaViewIds[SVGA3D_DX11_1_MAX_UAVIEWS];
   uपूर्णांक32 csuaViewIds[SVGA3D_DX11_1_MAX_UAVIEWS];

   uपूर्णांक32 pad8[188];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGADXContextMobFormat;

/*
 * There is conflicting करोcumentation on max class instances (253 vs 256).  The
 * lower value is the one used throughout the device, but since mob क्रमmat is
 * more involved to increase अगर needed, conservatively use the higher one here.
 */
#घोषणा SVGA3D_DX_MAX_CLASS_INSTANCES_PADDED 256

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGADXShaderIfaceMobFormat अणु
   काष्ठा अणु
      uपूर्णांक32 numClassInstances;
      uपूर्णांक32 अगरace[SVGA3D_DX_MAX_CLASS_INSTANCES_PADDED];
      SVGA3dIfaceData data[SVGA3D_DX_MAX_CLASS_INSTANCES_PADDED];
   पूर्ण shaderIfaceState[SVGA3D_NUM_SHADERTYPE];

   uपूर्णांक32 pad0[1018];
पूर्ण
#समावेश "vmware_pack_end.h"
SVGADXShaderIfaceMobFormat;

प्रकार
#समावेश "vmware_pack_begin.h"
काष्ठा SVGA3dCmdDXTempSetContext अणु
   uपूर्णांक32 dxcid;
पूर्ण
#समावेश "vmware_pack_end.h"
SVGA3dCmdDXTempSetContext; /* SVGA_3D_CMD_DX_TEMP_SET_CONTEXT */

#पूर्ण_अगर /* _SVGA3D_DX_H_ */
