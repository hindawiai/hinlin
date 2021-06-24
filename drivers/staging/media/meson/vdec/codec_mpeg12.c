<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "codec_mpeg12.h"
#समावेश "dos_regs.h"
#समावेश "vdec_helpers.h"

#घोषणा SIZE_WORKSPACE		SZ_128K
/* Offset substracted by the firmware from the workspace paddr */
#घोषणा WORKSPACE_OFFSET	(5 * SZ_1K)

/* map firmware रेजिस्टरs to known MPEG1/2 functions */
#घोषणा MREG_SEQ_INFO		AV_SCRATCH_4
	#घोषणा MPEG2_SEQ_DAR_MASK	GENMASK(3, 0)
	#घोषणा MPEG2_DAR_4_3		2
	#घोषणा MPEG2_DAR_16_9		3
	#घोषणा MPEG2_DAR_221_100	4
#घोषणा MREG_PIC_INFO		AV_SCRATCH_5
#घोषणा MREG_PIC_WIDTH		AV_SCRATCH_6
#घोषणा MREG_PIC_HEIGHT		AV_SCRATCH_7
#घोषणा MREG_BUFFERIN		AV_SCRATCH_8
#घोषणा MREG_BUFFEROUT		AV_SCRATCH_9
#घोषणा MREG_CMD		AV_SCRATCH_A
#घोषणा MREG_CO_MV_START	AV_SCRATCH_B
#घोषणा MREG_ERROR_COUNT	AV_SCRATCH_C
#घोषणा MREG_FRAME_OFFSET	AV_SCRATCH_D
#घोषणा MREG_WAIT_BUFFER	AV_SCRATCH_E
#घोषणा MREG_FATAL_ERROR	AV_SCRATCH_F

#घोषणा PICINFO_PROG		0x00008000
#घोषणा PICINFO_TOP_FIRST	0x00002000

काष्ठा codec_mpeg12 अणु
	/* Buffer क्रम the MPEG1/2 Workspace */
	व्योम	  *workspace_vaddr;
	dma_addr_t workspace_paddr;
पूर्ण;

अटल स्थिर u8 eos_sequence[SZ_1K] = अणु 0x00, 0x00, 0x01, 0xB7 पूर्ण;

अटल स्थिर u8 *codec_mpeg12_eos_sequence(u32 *len)
अणु
	*len = ARRAY_SIZE(eos_sequence);
	वापस eos_sequence;
पूर्ण

अटल पूर्णांक codec_mpeg12_can_recycle(काष्ठा amvdec_core *core)
अणु
	वापस !amvdec_पढ़ो_करोs(core, MREG_BUFFERIN);
पूर्ण

अटल व्योम codec_mpeg12_recycle(काष्ठा amvdec_core *core, u32 buf_idx)
अणु
	amvdec_ग_लिखो_करोs(core, MREG_BUFFERIN, buf_idx + 1);
पूर्ण

अटल पूर्णांक codec_mpeg12_start(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_mpeg12 *mpeg12;
	पूर्णांक ret;

	mpeg12 = kzalloc(माप(*mpeg12), GFP_KERNEL);
	अगर (!mpeg12)
		वापस -ENOMEM;

	/* Allocate some memory क्रम the MPEG1/2 decoder's state */
	mpeg12->workspace_vaddr = dma_alloc_coherent(core->dev, SIZE_WORKSPACE,
						     &mpeg12->workspace_paddr,
						     GFP_KERNEL);
	अगर (!mpeg12->workspace_vaddr) अणु
		dev_err(core->dev, "Failed to request MPEG 1/2 Workspace\n");
		ret = -ENOMEM;
		जाओ मुक्त_mpeg12;
	पूर्ण

	ret = amvdec_set_canvases(sess, (u32[])अणु AV_SCRATCH_0, 0 पूर्ण,
					(u32[])अणु 8, 0 पूर्ण);
	अगर (ret)
		जाओ मुक्त_workspace;

	amvdec_ग_लिखो_करोs(core, POWER_CTL_VLD, BIT(4));
	amvdec_ग_लिखो_करोs(core, MREG_CO_MV_START,
			 mpeg12->workspace_paddr + WORKSPACE_OFFSET);

	amvdec_ग_लिखो_करोs(core, MPEG1_2_REG, 0);
	amvdec_ग_लिखो_करोs(core, PSCALE_CTRL, 0);
	amvdec_ग_लिखो_करोs(core, PIC_HEAD_INFO, 0x380);
	amvdec_ग_लिखो_करोs(core, M4_CONTROL_REG, 0);
	amvdec_ग_लिखो_करोs(core, MREG_BUFFERIN, 0);
	amvdec_ग_लिखो_करोs(core, MREG_BUFFEROUT, 0);
	amvdec_ग_लिखो_करोs(core, MREG_CMD, (sess->width << 16) | sess->height);
	amvdec_ग_लिखो_करोs(core, MREG_ERROR_COUNT, 0);
	amvdec_ग_लिखो_करोs(core, MREG_FATAL_ERROR, 0);
	amvdec_ग_लिखो_करोs(core, MREG_WAIT_BUFFER, 0);

	sess->keyframe_found = 1;
	sess->priv = mpeg12;

	वापस 0;

मुक्त_workspace:
	dma_मुक्त_coherent(core->dev, SIZE_WORKSPACE, mpeg12->workspace_vaddr,
			  mpeg12->workspace_paddr);
मुक्त_mpeg12:
	kमुक्त(mpeg12);

	वापस ret;
पूर्ण

अटल पूर्णांक codec_mpeg12_stop(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_mpeg12 *mpeg12 = sess->priv;
	काष्ठा amvdec_core *core = sess->core;

	अगर (mpeg12->workspace_vaddr)
		dma_मुक्त_coherent(core->dev, SIZE_WORKSPACE,
				  mpeg12->workspace_vaddr,
				  mpeg12->workspace_paddr);

	वापस 0;
पूर्ण

अटल व्योम codec_mpeg12_update_dar(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 seq = amvdec_पढ़ो_करोs(core, MREG_SEQ_INFO);
	u32 ar = seq & MPEG2_SEQ_DAR_MASK;

	चयन (ar) अणु
	हाल MPEG2_DAR_4_3:
		amvdec_set_par_from_dar(sess, 4, 3);
		अवरोध;
	हाल MPEG2_DAR_16_9:
		amvdec_set_par_from_dar(sess, 16, 9);
		अवरोध;
	हाल MPEG2_DAR_221_100:
		amvdec_set_par_from_dar(sess, 221, 100);
		अवरोध;
	शेष:
		sess->pixelaspect.numerator = 1;
		sess->pixelaspect.denominator = 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t codec_mpeg12_thपढ़ोed_isr(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 reg;
	u32 pic_info;
	u32 is_progressive;
	u32 buffer_index;
	u32 field = V4L2_FIELD_NONE;
	u32 offset;

	amvdec_ग_लिखो_करोs(core, ASSIST_MBOX1_CLR_REG, 1);
	reg = amvdec_पढ़ो_करोs(core, MREG_FATAL_ERROR);
	अगर (reg == 1) अणु
		dev_err(core->dev, "MPEG1/2 fatal error\n");
		amvdec_पात(sess);
		वापस IRQ_HANDLED;
	पूर्ण

	reg = amvdec_पढ़ो_करोs(core, MREG_BUFFEROUT);
	अगर (!reg)
		वापस IRQ_HANDLED;

	/* Unclear what this means */
	अगर ((reg & GENMASK(23, 17)) == GENMASK(23, 17))
		जाओ end;

	pic_info = amvdec_पढ़ो_करोs(core, MREG_PIC_INFO);
	is_progressive = pic_info & PICINFO_PROG;

	अगर (!is_progressive)
		field = (pic_info & PICINFO_TOP_FIRST) ?
			V4L2_FIELD_INTERLACED_TB :
			V4L2_FIELD_INTERLACED_BT;

	codec_mpeg12_update_dar(sess);
	buffer_index = ((reg & 0xf) - 1) & 7;
	offset = amvdec_पढ़ो_करोs(core, MREG_FRAME_OFFSET);
	amvdec_dst_buf_करोne_idx(sess, buffer_index, offset, field);

end:
	amvdec_ग_लिखो_करोs(core, MREG_BUFFEROUT, 0);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t codec_mpeg12_isr(काष्ठा amvdec_session *sess)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

काष्ठा amvdec_codec_ops codec_mpeg12_ops = अणु
	.start = codec_mpeg12_start,
	.stop = codec_mpeg12_stop,
	.isr = codec_mpeg12_isr,
	.thपढ़ोed_isr = codec_mpeg12_thपढ़ोed_isr,
	.can_recycle = codec_mpeg12_can_recycle,
	.recycle = codec_mpeg12_recycle,
	.eos_sequence = codec_mpeg12_eos_sequence,
पूर्ण;
