<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश <drm/drm_crtc.h>

#समावेश "crc.h"
#समावेश "core.h"
#समावेश "disp.h"
#समावेश "head.h"

#समावेश <nvअगर/pushc37b.h>

#समावेश <nvhw/class/clc37d.h>

#घोषणा CRCC37D_MAX_ENTRIES 2047

काष्ठा crcc37d_notअगरier अणु
	u32 status;

	/* reserved */
	u32 :32;
	u32 :32;
	u32 :32;
	u32 :32;
	u32 :32;
	u32 :32;
	u32 :32;

	काष्ठा crcc37d_entry अणु
		u32 status[2];
		u32 :32; /* reserved */
		u32 compositor_crc;
		u32 rg_crc;
		u32 output_crc[2];
		u32 :32; /* reserved */
	पूर्ण entries[CRCC37D_MAX_ENTRIES];
पूर्ण __packed;

अटल पूर्णांक
crcc37d_set_src(काष्ठा nv50_head *head, पूर्णांक or,
		क्रमागत nv50_crc_source_type source,
		काष्ठा nv50_crc_notअगरier_ctx *ctx, u32 wndw)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	u32 crc_args = NVVAL(NVC37D, HEAD_SET_CRC_CONTROL, CONTROLLING_CHANNEL, wndw) |
		       NVDEF(NVC37D, HEAD_SET_CRC_CONTROL, EXPECT_BUFFER_COLLAPSE, FALSE) |
		       NVDEF(NVC37D, HEAD_SET_CRC_CONTROL, SECONDARY_CRC, NONE) |
		       NVDEF(NVC37D, HEAD_SET_CRC_CONTROL, CRC_DURING_SNOOZE, DISABLE);
	पूर्णांक ret;

	चयन (source) अणु
	हाल NV50_CRC_SOURCE_TYPE_SOR:
		crc_args |= NVDEF(NVC37D, HEAD_SET_CRC_CONTROL, PRIMARY_CRC, SOR(or));
		अवरोध;
	हाल NV50_CRC_SOURCE_TYPE_PIOR:
		crc_args |= NVDEF(NVC37D, HEAD_SET_CRC_CONTROL, PRIMARY_CRC, PIOR(or));
		अवरोध;
	हाल NV50_CRC_SOURCE_TYPE_SF:
		crc_args |= NVDEF(NVC37D, HEAD_SET_CRC_CONTROL, PRIMARY_CRC, SF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	अगर (source) अणु
		PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CRC(i), ctx->ntfy.handle);
		PUSH_MTHD(push, NVC37D, HEAD_SET_CRC_CONTROL(i), crc_args);
	पूर्ण अन्यथा अणु
		PUSH_MTHD(push, NVC37D, HEAD_SET_CRC_CONTROL(i), 0);
		PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CRC(i), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
crcc37d_set_ctx(काष्ठा nv50_head *head, काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CRC(i), ctx ? ctx->ntfy.handle : 0);
	वापस 0;
पूर्ण

अटल u32 crcc37d_get_entry(काष्ठा nv50_head *head,
			     काष्ठा nv50_crc_notअगरier_ctx *ctx,
			     क्रमागत nv50_crc_source source, पूर्णांक idx)
अणु
	काष्ठा crcc37d_notअगरier __iomem *notअगरier = ctx->mem.object.map.ptr;
	काष्ठा crcc37d_entry __iomem *entry = &notअगरier->entries[idx];
	u32 __iomem *crc_addr;

	अगर (source == NV50_CRC_SOURCE_RG)
		crc_addr = &entry->rg_crc;
	अन्यथा
		crc_addr = &entry->output_crc[0];

	वापस ioपढ़ो32_native(crc_addr);
पूर्ण

अटल bool crcc37d_ctx_finished(काष्ठा nv50_head *head,
				 काष्ठा nv50_crc_notअगरier_ctx *ctx)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(head->base.base.dev);
	काष्ठा crcc37d_notअगरier __iomem *notअगरier = ctx->mem.object.map.ptr;
	स्थिर u32 status = ioपढ़ो32_native(&notअगरier->status);
	स्थिर u32 overflow = status & 0x0000007e;

	अगर (!(status & 0x00000001))
		वापस false;

	अगर (overflow) अणु
		स्थिर अक्षर *engine = शून्य;

		चयन (overflow) अणु
		हाल 0x00000004: engine = "Front End"; अवरोध;
		हाल 0x00000008: engine = "Compositor"; अवरोध;
		हाल 0x00000010: engine = "RG"; अवरोध;
		हाल 0x00000020: engine = "CRC output 1"; अवरोध;
		हाल 0x00000040: engine = "CRC output 2"; अवरोध;
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

स्थिर काष्ठा nv50_crc_func crcc37d = अणु
	.set_src = crcc37d_set_src,
	.set_ctx = crcc37d_set_ctx,
	.get_entry = crcc37d_get_entry,
	.ctx_finished = crcc37d_ctx_finished,
	.flip_threshold = CRCC37D_MAX_ENTRIES - 30,
	.num_entries = CRCC37D_MAX_ENTRIES,
	.notअगरier_len = माप(काष्ठा crcc37d_notअगरier),
पूर्ण;
