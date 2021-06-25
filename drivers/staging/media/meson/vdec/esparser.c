<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 *
 * The Elementary Stream Parser is a HW bitstream parser.
 * It पढ़ोs bitstream buffers and feeds them to the VIFIFO
 */

#समावेश <linux/init.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "dos_regs.h"
#समावेश "esparser.h"
#समावेश "vdec_helpers.h"

/* PARSER REGS (CBUS) */
#घोषणा PARSER_CONTROL 0x00
	#घोषणा ES_PACK_SIZE_BIT	8
	#घोषणा ES_WRITE		BIT(5)
	#घोषणा ES_SEARCH		BIT(1)
	#घोषणा ES_PARSER_START		BIT(0)
#घोषणा PARSER_FETCH_ADDR	0x4
#घोषणा PARSER_FETCH_CMD	0x8
#घोषणा PARSER_CONFIG 0x14
	#घोषणा PS_CFG_MAX_FETCH_CYCLE_BIT	0
	#घोषणा PS_CFG_STARTCODE_WID_24_BIT	10
	#घोषणा PS_CFG_MAX_ES_WR_CYCLE_BIT	12
	#घोषणा PS_CFG_PFIFO_EMPTY_CNT_BIT	16
#घोषणा PFIFO_WR_PTR 0x18
#घोषणा PFIFO_RD_PTR 0x1c
#घोषणा PARSER_SEARCH_PATTERN 0x24
	#घोषणा ES_START_CODE_PATTERN 0x00000100
#घोषणा PARSER_SEARCH_MASK 0x28
	#घोषणा ES_START_CODE_MASK	0xffffff00
	#घोषणा FETCH_ENDIAN_BIT	27
#घोषणा PARSER_INT_ENABLE	0x2c
	#घोषणा PARSER_INT_HOST_EN_BIT	8
#घोषणा PARSER_INT_STATUS	0x30
	#घोषणा PARSER_INTSTAT_SC_FOUND	1
#घोषणा PARSER_ES_CONTROL	0x5c
#घोषणा PARSER_VIDEO_START_PTR	0x80
#घोषणा PARSER_VIDEO_END_PTR	0x84
#घोषणा PARSER_VIDEO_WP		0x88
#घोषणा PARSER_VIDEO_HOLE	0x90

#घोषणा SEARCH_PATTERN_LEN	512
#घोषणा VP9_HEADER_SIZE		16

अटल DECLARE_WAIT_QUEUE_HEAD(wq);
अटल पूर्णांक search_करोne;

अटल irqवापस_t esparser_isr(पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक पूर्णांक_status;
	काष्ठा amvdec_core *core = dev;

	पूर्णांक_status = amvdec_पढ़ो_parser(core, PARSER_INT_STATUS);
	amvdec_ग_लिखो_parser(core, PARSER_INT_STATUS, पूर्णांक_status);

	अगर (पूर्णांक_status & PARSER_INTSTAT_SC_FOUND) अणु
		amvdec_ग_लिखो_parser(core, PFIFO_RD_PTR, 0);
		amvdec_ग_लिखो_parser(core, PFIFO_WR_PTR, 0);
		search_करोne = 1;
		wake_up_पूर्णांकerruptible(&wq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * VP9 frame headers need to be appended by a 16-byte दीर्घ
 * Amlogic custom header
 */
अटल पूर्णांक vp9_update_header(काष्ठा amvdec_core *core, काष्ठा vb2_buffer *buf)
अणु
	u8 *dp;
	u8 marker;
	पूर्णांक dsize;
	पूर्णांक num_frames, cur_frame;
	पूर्णांक cur_mag, mag, mag_ptr;
	पूर्णांक frame_size[8], tot_frame_size[8];
	पूर्णांक total_datasize = 0;
	पूर्णांक new_frame_size;
	अचिन्हित अक्षर *old_header = शून्य;

	dp = (uपूर्णांक8_t *)vb2_plane_vaddr(buf, 0);
	dsize = vb2_get_plane_payload(buf, 0);

	अगर (dsize == vb2_plane_size(buf, 0)) अणु
		dev_warn(core->dev, "%s: unable to update header\n", __func__);
		वापस 0;
	पूर्ण

	marker = dp[dsize - 1];
	अगर ((marker & 0xe0) == 0xc0) अणु
		num_frames = (marker & 0x7) + 1;
		mag = ((marker >> 3) & 0x3) + 1;
		mag_ptr = dsize - mag * num_frames - 2;
		अगर (dp[mag_ptr] != marker)
			वापस 0;

		mag_ptr++;
		क्रम (cur_frame = 0; cur_frame < num_frames; cur_frame++) अणु
			frame_size[cur_frame] = 0;
			क्रम (cur_mag = 0; cur_mag < mag; cur_mag++) अणु
				frame_size[cur_frame] |=
					(dp[mag_ptr] << (cur_mag * 8));
				mag_ptr++;
			पूर्ण
			अगर (cur_frame == 0)
				tot_frame_size[cur_frame] =
					frame_size[cur_frame];
			अन्यथा
				tot_frame_size[cur_frame] =
					tot_frame_size[cur_frame - 1] +
					frame_size[cur_frame];
			total_datasize += frame_size[cur_frame];
		पूर्ण
	पूर्ण अन्यथा अणु
		num_frames = 1;
		frame_size[0] = dsize;
		tot_frame_size[0] = dsize;
		total_datasize = dsize;
	पूर्ण

	new_frame_size = total_datasize + num_frames * VP9_HEADER_SIZE;

	अगर (new_frame_size >= vb2_plane_size(buf, 0)) अणु
		dev_warn(core->dev, "%s: unable to update header\n", __func__);
		वापस 0;
	पूर्ण

	क्रम (cur_frame = num_frames - 1; cur_frame >= 0; cur_frame--) अणु
		पूर्णांक framesize = frame_size[cur_frame];
		पूर्णांक framesize_header = framesize + 4;
		पूर्णांक oldframeoff = tot_frame_size[cur_frame] - framesize;
		पूर्णांक outheaderoff =  oldframeoff + cur_frame * VP9_HEADER_SIZE;
		u8 *fdata = dp + outheaderoff;
		u8 *old_framedata = dp + oldframeoff;

		स_हटाओ(fdata + VP9_HEADER_SIZE, old_framedata, framesize);

		fdata[0] = (framesize_header >> 24) & 0xff;
		fdata[1] = (framesize_header >> 16) & 0xff;
		fdata[2] = (framesize_header >> 8) & 0xff;
		fdata[3] = (framesize_header >> 0) & 0xff;
		fdata[4] = ((framesize_header >> 24) & 0xff) ^ 0xff;
		fdata[5] = ((framesize_header >> 16) & 0xff) ^ 0xff;
		fdata[6] = ((framesize_header >> 8) & 0xff) ^ 0xff;
		fdata[7] = ((framesize_header >> 0) & 0xff) ^ 0xff;
		fdata[8] = 0;
		fdata[9] = 0;
		fdata[10] = 0;
		fdata[11] = 1;
		fdata[12] = 'A';
		fdata[13] = 'M';
		fdata[14] = 'L';
		fdata[15] = 'V';

		अगर (!old_header) अणु
			/* nothing */
		पूर्ण अन्यथा अगर (old_header > fdata + 16 + framesize) अणु
			dev_dbg(core->dev, "%s: data has gaps, setting to 0\n",
				__func__);
			स_रखो(fdata + 16 + framesize, 0,
			       (old_header - fdata + 16 + framesize));
		पूर्ण अन्यथा अगर (old_header < fdata + 16 + framesize) अणु
			dev_err(core->dev, "%s: data overwritten\n", __func__);
		पूर्ण
		old_header = fdata;
	पूर्ण

	वापस new_frame_size;
पूर्ण

/* Pad the packet to at least 4KiB bytes otherwise the VDEC unit won't trigger
 * ISRs.
 * Also append a start code 000001ff at the end to trigger
 * the ESPARSER पूर्णांकerrupt.
 */
अटल u32 esparser_pad_start_code(काष्ठा amvdec_core *core,
				   काष्ठा vb2_buffer *vb,
				   u32 payload_size)
अणु
	u32 pad_size = 0;
	u8 *vaddr = vb2_plane_vaddr(vb, 0);

	अगर (payload_size < ESPARSER_MIN_PACKET_SIZE) अणु
		pad_size = ESPARSER_MIN_PACKET_SIZE - payload_size;
		स_रखो(vaddr + payload_size, 0, pad_size);
	पूर्ण

	अगर ((payload_size + pad_size + SEARCH_PATTERN_LEN) >
						vb2_plane_size(vb, 0)) अणु
		dev_warn(core->dev, "%s: unable to pad start code\n", __func__);
		वापस pad_size;
	पूर्ण

	स_रखो(vaddr + payload_size + pad_size, 0, SEARCH_PATTERN_LEN);
	vaddr[payload_size + pad_size]     = 0x00;
	vaddr[payload_size + pad_size + 1] = 0x00;
	vaddr[payload_size + pad_size + 2] = 0x01;
	vaddr[payload_size + pad_size + 3] = 0xff;

	वापस pad_size;
पूर्ण

अटल पूर्णांक
esparser_ग_लिखो_data(काष्ठा amvdec_core *core, dma_addr_t addr, u32 size)
अणु
	amvdec_ग_लिखो_parser(core, PFIFO_RD_PTR, 0);
	amvdec_ग_लिखो_parser(core, PFIFO_WR_PTR, 0);
	amvdec_ग_लिखो_parser(core, PARSER_CONTROL,
			    ES_WRITE |
			    ES_PARSER_START |
			    ES_SEARCH |
			    (size << ES_PACK_SIZE_BIT));

	amvdec_ग_लिखो_parser(core, PARSER_FETCH_ADDR, addr);
	amvdec_ग_लिखो_parser(core, PARSER_FETCH_CMD,
			    (7 << FETCH_ENDIAN_BIT) |
			    (size + SEARCH_PATTERN_LEN));

	search_करोne = 0;
	वापस रुको_event_पूर्णांकerruptible_समयout(wq, search_करोne, (HZ / 5));
पूर्ण

अटल u32 esparser_vअगरअगरo_get_मुक्त_space(काष्ठा amvdec_session *sess)
अणु
	u32 vअगरअगरo_usage;
	काष्ठा amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;
	काष्ठा amvdec_core *core = sess->core;

	vअगरअगरo_usage  = vdec_ops->vअगरअगरo_level(sess);
	vअगरअगरo_usage += amvdec_पढ़ो_parser(core, PARSER_VIDEO_HOLE);
	vअगरअगरo_usage += (6 * SZ_1K); // 6 KiB पूर्णांकernal fअगरo

	अगर (vअगरअगरo_usage > sess->vअगरअगरo_size) अणु
		dev_warn(sess->core->dev,
			 "VIFIFO usage (%u) > VIFIFO size (%u)\n",
			 vअगरअगरo_usage, sess->vअगरअगरo_size);
		वापस 0;
	पूर्ण

	वापस sess->vअगरअगरo_size - vअगरअगरo_usage;
पूर्ण

पूर्णांक esparser_queue_eos(काष्ठा amvdec_core *core, स्थिर u8 *data, u32 len)
अणु
	काष्ठा device *dev = core->dev;
	व्योम *eos_vaddr;
	dma_addr_t eos_paddr;
	पूर्णांक ret;

	eos_vaddr = dma_alloc_coherent(dev, len + SEARCH_PATTERN_LEN,
				       &eos_paddr, GFP_KERNEL);
	अगर (!eos_vaddr)
		वापस -ENOMEM;

	स_नकल(eos_vaddr, data, len);
	ret = esparser_ग_लिखो_data(core, eos_paddr, len);
	dma_मुक्त_coherent(dev, len + SEARCH_PATTERN_LEN,
			  eos_vaddr, eos_paddr);

	वापस ret;
पूर्ण

अटल u32 esparser_get_offset(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 offset = amvdec_पढ़ो_parser(core, PARSER_VIDEO_WP) -
		     sess->vअगरअगरo_paddr;

	अगर (offset < sess->last_offset)
		sess->wrap_count++;

	sess->last_offset = offset;
	offset += (sess->wrap_count * sess->vअगरअगरo_size);

	वापस offset;
पूर्ण

अटल पूर्णांक
esparser_queue(काष्ठा amvdec_session *sess, काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	पूर्णांक ret;
	काष्ठा vb2_buffer *vb = &vbuf->vb2_buf;
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	u32 payload_size = vb2_get_plane_payload(vb, 0);
	dma_addr_t phy = vb2_dma_contig_plane_dma_addr(vb, 0);
	u32 num_dst_bufs = 0;
	u32 offset;
	u32 pad_size;

	/*
	 * When max ref frame is held by VP9, this should be -= 3 to prevent a
	 * लघुage of CAPTURE buffers on the decoder side.
	 * For the future, a good enhancement of the way this is handled could
	 * be to notअगरy new capture buffers to the decoding modules, so that
	 * they could छोड़ो when there is no capture buffer available and
	 * resume on this notअगरication.
	 */
	अगर (sess->fmt_out->pixfmt == V4L2_PIX_FMT_VP9) अणु
		अगर (codec_ops->num_pending_bufs)
			num_dst_bufs = codec_ops->num_pending_bufs(sess);

		num_dst_bufs += v4l2_m2m_num_dst_bufs_पढ़ोy(sess->m2m_ctx);
		अगर (sess->fmt_out->pixfmt == V4L2_PIX_FMT_VP9)
			num_dst_bufs -= 3;

		अगर (esparser_vअगरअगरo_get_मुक्त_space(sess) < payload_size ||
		    atomic_पढ़ो(&sess->esparser_queued_bufs) >= num_dst_bufs)
			वापस -EAGAIN;
	पूर्ण अन्यथा अगर (esparser_vअगरअगरo_get_मुक्त_space(sess) < payload_size) अणु
		वापस -EAGAIN;
	पूर्ण

	v4l2_m2m_src_buf_हटाओ_by_buf(sess->m2m_ctx, vbuf);

	offset = esparser_get_offset(sess);

	amvdec_add_ts(sess, vb->बारtamp, vbuf->समयcode, offset, vbuf->flags);
	dev_dbg(core->dev, "esparser: ts = %llu pld_size = %u offset = %08X flags = %08X\n",
		vb->बारtamp, payload_size, offset, vbuf->flags);

	vbuf->flags = 0;
	vbuf->field = V4L2_FIELD_NONE;
	vbuf->sequence = sess->sequence_out++;

	अगर (sess->fmt_out->pixfmt == V4L2_PIX_FMT_VP9) अणु
		payload_size = vp9_update_header(core, vb);

		/* If unable to alter buffer to add headers */
		अगर (payload_size == 0) अणु
			amvdec_हटाओ_ts(sess, vb->बारtamp);
			v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);

			वापस 0;
		पूर्ण
	पूर्ण

	pad_size = esparser_pad_start_code(core, vb, payload_size);
	ret = esparser_ग_लिखो_data(core, phy, payload_size + pad_size);

	अगर (ret <= 0) अणु
		dev_warn(core->dev, "esparser: input parsing error\n");
		amvdec_हटाओ_ts(sess, vb->बारtamp);
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
		amvdec_ग_लिखो_parser(core, PARSER_FETCH_CMD, 0);

		वापस 0;
	पूर्ण

	atomic_inc(&sess->esparser_queued_bufs);
	v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_DONE);

	वापस 0;
पूर्ण

व्योम esparser_queue_all_src(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा v4l2_m2m_buffer *buf, *n;
	काष्ठा amvdec_session *sess =
		container_of(work, काष्ठा amvdec_session, esparser_queue_work);

	mutex_lock(&sess->lock);
	v4l2_m2m_क्रम_each_src_buf_safe(sess->m2m_ctx, buf, n) अणु
		अगर (sess->should_stop)
			अवरोध;

		अगर (esparser_queue(sess, &buf->vb) < 0)
			अवरोध;
	पूर्ण
	mutex_unlock(&sess->lock);
पूर्ण

पूर्णांक esparser_घातer_up(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;

	reset_control_reset(core->esparser_reset);
	amvdec_ग_लिखो_parser(core, PARSER_CONFIG,
			    (10 << PS_CFG_PFIFO_EMPTY_CNT_BIT) |
			    (1  << PS_CFG_MAX_ES_WR_CYCLE_BIT) |
			    (16 << PS_CFG_MAX_FETCH_CYCLE_BIT));

	amvdec_ग_लिखो_parser(core, PFIFO_RD_PTR, 0);
	amvdec_ग_लिखो_parser(core, PFIFO_WR_PTR, 0);

	amvdec_ग_लिखो_parser(core, PARSER_SEARCH_PATTERN,
			    ES_START_CODE_PATTERN);
	amvdec_ग_लिखो_parser(core, PARSER_SEARCH_MASK, ES_START_CODE_MASK);

	amvdec_ग_लिखो_parser(core, PARSER_CONFIG,
			    (10 << PS_CFG_PFIFO_EMPTY_CNT_BIT) |
			    (1  << PS_CFG_MAX_ES_WR_CYCLE_BIT) |
			    (16 << PS_CFG_MAX_FETCH_CYCLE_BIT) |
			    (2  << PS_CFG_STARTCODE_WID_24_BIT));

	amvdec_ग_लिखो_parser(core, PARSER_CONTROL,
			    (ES_SEARCH | ES_PARSER_START));

	amvdec_ग_लिखो_parser(core, PARSER_VIDEO_START_PTR, sess->vअगरअगरo_paddr);
	amvdec_ग_लिखो_parser(core, PARSER_VIDEO_END_PTR,
			    sess->vअगरअगरo_paddr + sess->vअगरअगरo_size - 8);
	amvdec_ग_लिखो_parser(core, PARSER_ES_CONTROL,
			    amvdec_पढ़ो_parser(core, PARSER_ES_CONTROL) & ~1);

	अगर (vdec_ops->conf_esparser)
		vdec_ops->conf_esparser(sess);

	amvdec_ग_लिखो_parser(core, PARSER_INT_STATUS, 0xffff);
	amvdec_ग_लिखो_parser(core, PARSER_INT_ENABLE,
			    BIT(PARSER_INT_HOST_EN_BIT));

	वापस 0;
पूर्ण

पूर्णांक esparser_init(काष्ठा platक्रमm_device *pdev, काष्ठा amvdec_core *core)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	पूर्णांक irq;

	irq = platक्रमm_get_irq_byname(pdev, "esparser");
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, esparser_isr, IRQF_SHARED,
			       "esparserirq", core);
	अगर (ret) अणु
		dev_err(dev, "Failed requesting ESPARSER IRQ\n");
		वापस ret;
	पूर्ण

	core->esparser_reset =
		devm_reset_control_get_exclusive(dev, "esparser");
	अगर (IS_ERR(core->esparser_reset)) अणु
		dev_err(dev, "Failed to get esparser_reset\n");
		वापस PTR_ERR(core->esparser_reset);
	पूर्ण

	वापस 0;
पूर्ण
