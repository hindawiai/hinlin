<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश <drm/drm_crtc.h>

#समावेश "crc.h"
#समावेश "core.h"
#समावेश "disp.h"
#समावेश "head.h"

#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl907d.h>

#घोषणा CRC907D_MAX_ENTRIES 255

काष्ठा crc907d_notअगरier अणु
	u32 status;
	u32 :32; /* reserved */
	काष्ठा crc907d_entry अणु
		u32 status;
		u32 compositor_crc;
		u32 output_crc[2];
	पूर्ण entries[CRC907D_MAX_ENTRIES];
पूर्ण __packed;

अटल पूर्णांक
crc907d_set_src(काष्ठा nv50_head *head, पूर्णांक or,
		क्रमागत nv50_crc_source_type source,
		काष्ठा nv50_crc_notअगरier_ctx *ctx, u32 wndw)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	u32 crc_args = NVDEF(NV907D, HEAD_SET_CRC_CONTROL, CONTROLLING_CHANNEL, CORE) |
		       NVDEF(NV907D, HEAD_SET_CRC_CONTROL, EXPECT_BUFFER_COLLAPSE, FALSE) |
		       NVDEF(NV907D, HEAD_SET_CRC_CONTROL, TIMESTAMP_MODE, FALSE) |
		       NVDEF(NV907D, HEAD_SET_CRC_CONTROL, SECONDARY_OUTPUT, NONE) |
		       NVDEF(NV907D, HEAD_SET_CRC_CONTROL, CRC_DURING_SNOOZE, DISABLE);
	पूर्णांक ret;

	चयन (source) अणु
	हाल NV50_CRC_SOURCE_TYPE_SOR:
		crc_args |= NVDEF(NV907D, HEAD_SET_CRC_CONTROL, PRIMARY_OUTPUT, SOR(or));
		अवरोध;
	हाल NV50_CRC_SOURCE_TYPE_PIOR:
		crc_args |= NVDEF(NV907D, HEAD_SET_CRC_CONTROL, PRIMARY_OUTPUT, PIOR(or));
		अवरोध;
	हाल NV50_CRC_SOURCE_TYPE_DAC:
		crc_args |= NVDEF(NV907D, HEAD_SET_CRC_CONTROL, PRIMARY_OUTPUT, DAC(or));
		अवरोध;
	हाल NV50_CRC_SOURCE_TYPE_RG:
		crc_args |= NVDEF(NV907D, HEAD_SET_CRC_CONTROL, PRIMARY_OUTPUT, RG(i));
		अवरोध;
	हाल NV50_CRC_SOURCE_TYPE_SF:
		crc_args |= NVDEF(NV907D, HEAD_SET_CRC_CONTROL, PRIMARY_OUTPUT, SF(i));
		अवरोध;
	हाल NV50_CRC_SOURCE_NONE:
		crc_args |= NVDEF(NV907D, HEAD_SET_CRC_CONTROL, PRIMARY_OUTPUT, NONE);
		अवरोध;
	पूर्ण

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	अगर (source) अणु
		PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CRC(i), ctx->ntfy.handle);
		PUSH_MTHD(push, NV907D, HEAD_SET_CRC_CONTROL(i), crc_args);
	पूर्ण अन्यथा अणु
		PUSH_MTHD(push, NV907D, HEAD_SET_CRC_CONTROL(i), crc_args);
		PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CRC(i), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
crc907d_set_ctx(काष्ठा nv50_head *head, काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CRC(i), ctx ? ctx->ntfy.handle : 0);
	वापस 0;
पूर्ण

अटल u32 crc907d_get_entry(काष्ठा nv50_head *head,
			     काष्ठा nv50_crc_notअगरier_ctx *ctx,
			     क्रमागत nv50_crc_source source, पूर्णांक idx)
अणु
	काष्ठा crc907d_notअगरier __iomem *notअगरier = ctx->mem.object.map.ptr;

	वापस ioपढ़ो32_native(&notअगरier->entries[idx].output_crc[0]);
पूर्ण

अटल bool crc907d_ctx_finished(काष्ठा nv50_head *head,
				 काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(head->base.base.dev);
	काष्ठा crc907d_notअगरier __iomem *notअगरier = ctx->mem.object.map.ptr;
	स्थिर u32 status = ioपढ़ो32_native(&notअगरier->status);
	स्थिर u32 overflow = status & 0x0000003e;

	अगर (!(status & 0x00000001))
		वापस false;

	अगर (overflow) अणु
		स्थिर अक्षर *engine = शून्य;

		चयन (overflow) अणु
		हाल 0x00000004: engine = "DSI"; अवरोध;
		हाल 0x00000008: engine = "Compositor"; अवरोध;
		हाल 0x00000010: engine = "CRC output 1"; अवरोध;
		हाल 0x00000020: engine = "CRC output 2"; अवरोध;
		पूर्ण

		अगर (engine)
			NV_ERROR(drm,
				 "CRC notifier context for head %d overflowed on %s: %x\n",
				 head->base.index, engine, status);
		अन्यथा
			NV_ERROR(drm,
				 "CRC notifier context for head %d overflowed: %x\n",
				 head->base.index, status);
	पूर्ण

	NV_DEBUG(drm, "Head %d CRC context status: %x\n",
		 head->base.index, status);

	वापस true;
पूर्ण

स्थिर काष्ठा nv50_crc_func crc907d = अणु
	.set_src = crc907d_set_src,
	.set_ctx = crc907d_set_ctx,
	.get_entry = crc907d_get_entry,
	.ctx_finished = crc907d_ctx_finished,
	.flip_threshold = CRC907D_MAX_ENTRIES - 10,
	.num_entries = CRC907D_MAX_ENTRIES,
	.notअगरier_len = माप(काष्ठा crc907d_notअगरier),
पूर्ण;
