<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* पूर्णांकerrupt handling
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-queue.h"
#समावेश "ivtv-udma.h"
#समावेश "ivtv-irq.h"
#समावेश "ivtv-mailbox.h"
#समावेश "ivtv-vbi.h"
#समावेश "ivtv-yuv.h"
#समावेश <media/v4l2-event.h>

#घोषणा DMA_MAGIC_COOKIE 0x000001fe

अटल व्योम ivtv_dma_dec_start(काष्ठा ivtv_stream *s);

अटल स्थिर पूर्णांक ivtv_stream_map[] = अणु
	IVTV_ENC_STREAM_TYPE_MPG,
	IVTV_ENC_STREAM_TYPE_YUV,
	IVTV_ENC_STREAM_TYPE_PCM,
	IVTV_ENC_STREAM_TYPE_VBI,
पूर्ण;

अटल व्योम ivtv_pcm_work_handler(काष्ठा ivtv *itv)
अणु
	काष्ठा ivtv_stream *s = &itv->streams[IVTV_ENC_STREAM_TYPE_PCM];
	काष्ठा ivtv_buffer *buf;

	/* Pass the PCM data to ivtv-alsa */

	जबतक (1) अणु
		/*
		 * Users should not be using both the ALSA and V4L2 PCM audio
		 * capture पूर्णांकerfaces at the same समय.  If the user is करोing
		 * this, there maybe a buffer in q_io to grab, use, and put
		 * back in rotation.
		 */
		buf = ivtv_dequeue(s, &s->q_io);
		अगर (buf == शून्य)
			buf = ivtv_dequeue(s, &s->q_full);
		अगर (buf == शून्य)
			अवरोध;

		अगर (buf->पढ़ोpos < buf->bytesused)
			itv->pcm_announce_callback(itv->alsa,
				(u8 *)(buf->buf + buf->पढ़ोpos),
				(माप_प्रकार)(buf->bytesused - buf->पढ़ोpos));

		ivtv_enqueue(s, buf, &s->q_मुक्त);
	पूर्ण
पूर्ण

अटल व्योम ivtv_pio_work_handler(काष्ठा ivtv *itv)
अणु
	काष्ठा ivtv_stream *s = &itv->streams[itv->cur_pio_stream];
	काष्ठा ivtv_buffer *buf;
	पूर्णांक i = 0;

	IVTV_DEBUG_HI_DMA("ivtv_pio_work_handler\n");
	अगर (itv->cur_pio_stream < 0 || itv->cur_pio_stream >= IVTV_MAX_STREAMS ||
			s->vdev.v4l2_dev == शून्य || !ivtv_use_pio(s)) अणु
		itv->cur_pio_stream = -1;
		/* trigger PIO complete user पूर्णांकerrupt */
		ग_लिखो_reg(IVTV_IRQ_ENC_PIO_COMPLETE, 0x44);
		वापस;
	पूर्ण
	IVTV_DEBUG_HI_DMA("Process PIO %s\n", s->name);
	list_क्रम_each_entry(buf, &s->q_dma.list, list) अणु
		u32 size = s->sg_processing[i].size & 0x3ffff;

		/* Copy the data from the card to the buffer */
		अगर (s->type == IVTV_DEC_STREAM_TYPE_VBI) अणु
			स_नकल_fromio(buf->buf, itv->dec_mem + s->sg_processing[i].src - IVTV_DECODER_OFFSET, size);
		पूर्ण
		अन्यथा अणु
			स_नकल_fromio(buf->buf, itv->enc_mem + s->sg_processing[i].src, size);
		पूर्ण
		i++;
		अगर (i == s->sg_processing_size)
			अवरोध;
	पूर्ण
	ग_लिखो_reg(IVTV_IRQ_ENC_PIO_COMPLETE, 0x44);
पूर्ण

व्योम ivtv_irq_work_handler(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा ivtv *itv = container_of(work, काष्ठा ivtv, irq_work);

	अगर (test_and_clear_bit(IVTV_F_I_WORK_HANDLER_PIO, &itv->i_flags))
		ivtv_pio_work_handler(itv);

	अगर (test_and_clear_bit(IVTV_F_I_WORK_HANDLER_VBI, &itv->i_flags))
		ivtv_vbi_work_handler(itv);

	अगर (test_and_clear_bit(IVTV_F_I_WORK_HANDLER_YUV, &itv->i_flags))
		ivtv_yuv_work_handler(itv);

	अगर (test_and_clear_bit(IVTV_F_I_WORK_HANDLER_PCM, &itv->i_flags))
		ivtv_pcm_work_handler(itv);
पूर्ण

/* Determine the required DMA size, setup enough buffers in the predma queue and
   actually copy the data from the card to the buffers in हाल a PIO transfer is
   required क्रम this stream.
 */
अटल पूर्णांक stream_enc_dma_append(काष्ठा ivtv_stream *s, u32 data[CX2341X_MBOX_MAX_DATA])
अणु
	काष्ठा ivtv *itv = s->itv;
	काष्ठा ivtv_buffer *buf;
	u32 bytes_needed = 0;
	u32 offset, size;
	u32 UVoffset = 0, UVsize = 0;
	पूर्णांक skip_bufs = s->q_predma.buffers;
	पूर्णांक idx = s->sg_pending_size;
	पूर्णांक rc;

	/* sanity checks */
	अगर (s->vdev.v4l2_dev == शून्य) अणु
		IVTV_DEBUG_WARN("Stream %s not started\n", s->name);
		वापस -1;
	पूर्ण
	अगर (!test_bit(IVTV_F_S_CLAIMED, &s->s_flags)) अणु
		IVTV_DEBUG_WARN("Stream %s not open\n", s->name);
		वापस -1;
	पूर्ण

	/* determine offset, size and PTS क्रम the various streams */
	चयन (s->type) अणु
		हाल IVTV_ENC_STREAM_TYPE_MPG:
			offset = data[1];
			size = data[2];
			s->pending_pts = 0;
			अवरोध;

		हाल IVTV_ENC_STREAM_TYPE_YUV:
			offset = data[1];
			size = data[2];
			UVoffset = data[3];
			UVsize = data[4];
			s->pending_pts = ((u64) data[5] << 32) | data[6];
			अवरोध;

		हाल IVTV_ENC_STREAM_TYPE_PCM:
			offset = data[1] + 12;
			size = data[2] - 12;
			s->pending_pts = पढ़ो_dec(offset - 8) |
				((u64)(पढ़ो_dec(offset - 12)) << 32);
			अगर (itv->has_cx23415)
				offset += IVTV_DECODER_OFFSET;
			अवरोध;

		हाल IVTV_ENC_STREAM_TYPE_VBI:
			size = itv->vbi.enc_size * itv->vbi.fpi;
			offset = पढ़ो_enc(itv->vbi.enc_start - 4) + 12;
			अगर (offset == 12) अणु
				IVTV_DEBUG_INFO("VBI offset == 0\n");
				वापस -1;
			पूर्ण
			s->pending_pts = पढ़ो_enc(offset - 4) | ((u64)पढ़ो_enc(offset - 8) << 32);
			अवरोध;

		हाल IVTV_DEC_STREAM_TYPE_VBI:
			size = पढ़ो_dec(itv->vbi.dec_start + 4) + 8;
			offset = पढ़ो_dec(itv->vbi.dec_start) + itv->vbi.dec_start;
			s->pending_pts = 0;
			offset += IVTV_DECODER_OFFSET;
			अवरोध;
		शेष:
			/* shouldn't happen */
			वापस -1;
	पूर्ण

	/* अगर this is the start of the DMA then fill in the magic cookie */
	अगर (s->sg_pending_size == 0 && ivtv_use_dma(s)) अणु
		अगर (itv->has_cx23415 && (s->type == IVTV_ENC_STREAM_TYPE_PCM ||
		    s->type == IVTV_DEC_STREAM_TYPE_VBI)) अणु
			s->pending_backup = पढ़ो_dec(offset - IVTV_DECODER_OFFSET);
			ग_लिखो_dec_sync(DMA_MAGIC_COOKIE, offset - IVTV_DECODER_OFFSET);
		पूर्ण
		अन्यथा अणु
			s->pending_backup = पढ़ो_enc(offset);
			ग_लिखो_enc_sync(DMA_MAGIC_COOKIE, offset);
		पूर्ण
		s->pending_offset = offset;
	पूर्ण

	bytes_needed = size;
	अगर (s->type == IVTV_ENC_STREAM_TYPE_YUV) अणु
		/* The size क्रम the Y samples needs to be rounded upwards to a
		   multiple of the buf_size. The UV samples then start in the
		   next buffer. */
		bytes_needed = s->buf_size * ((bytes_needed + s->buf_size - 1) / s->buf_size);
		bytes_needed += UVsize;
	पूर्ण

	IVTV_DEBUG_HI_DMA("%s %s: 0x%08x bytes at 0x%08x\n",
		ivtv_use_pio(s) ? "PIO" : "DMA", s->name, bytes_needed, offset);

	rc = ivtv_queue_move(s, &s->q_मुक्त, &s->q_full, &s->q_predma, bytes_needed);
	अगर (rc < 0) अणु /* Insufficient buffers */
		IVTV_DEBUG_WARN("Cannot obtain %d bytes for %s data transfer\n",
				bytes_needed, s->name);
		वापस -1;
	पूर्ण
	अगर (rc && !s->buffers_stolen && test_bit(IVTV_F_S_APPL_IO, &s->s_flags)) अणु
		IVTV_WARN("All %s stream buffers are full. Dropping data.\n", s->name);
		IVTV_WARN("Cause: the application is not reading fast enough.\n");
	पूर्ण
	s->buffers_stolen = rc;

	/* got the buffers, now fill in sg_pending */
	buf = list_entry(s->q_predma.list.next, काष्ठा ivtv_buffer, list);
	स_रखो(buf->buf, 0, 128);
	list_क्रम_each_entry(buf, &s->q_predma.list, list) अणु
		अगर (skip_bufs-- > 0)
			जारी;
		s->sg_pending[idx].dst = buf->dma_handle;
		s->sg_pending[idx].src = offset;
		s->sg_pending[idx].size = s->buf_size;
		buf->bytesused = min(size, s->buf_size);
		buf->dma_xfer_cnt = s->dma_xfer_cnt;

		s->q_predma.bytesused += buf->bytesused;
		size -= buf->bytesused;
		offset += s->buf_size;

		/* Sync SG buffers */
		ivtv_buf_sync_क्रम_device(s, buf);

		अगर (size == 0) अणु	/* YUV */
			/* process the UV section */
			offset = UVoffset;
			size = UVsize;
		पूर्ण
		idx++;
	पूर्ण
	s->sg_pending_size = idx;
	वापस 0;
पूर्ण

अटल व्योम dma_post(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;
	काष्ठा ivtv_buffer *buf = शून्य;
	काष्ठा list_head *p;
	u32 offset;
	__le32 *u32buf;
	पूर्णांक x = 0;

	IVTV_DEBUG_HI_DMA("%s %s completed (%x)\n", ivtv_use_pio(s) ? "PIO" : "DMA",
			s->name, s->dma_offset);
	list_क्रम_each(p, &s->q_dma.list) अणु
		buf = list_entry(p, काष्ठा ivtv_buffer, list);
		u32buf = (__le32 *)buf->buf;

		/* Sync Buffer */
		ivtv_buf_sync_क्रम_cpu(s, buf);

		अगर (x == 0 && ivtv_use_dma(s)) अणु
			offset = s->dma_last_offset;
			अगर (le32_to_cpu(u32buf[offset / 4]) != DMA_MAGIC_COOKIE)
			अणु
				क्रम (offset = 0; offset < 64; offset++)
					अगर (le32_to_cpu(u32buf[offset]) == DMA_MAGIC_COOKIE)
						अवरोध;
				offset *= 4;
				अगर (offset == 256) अणु
					IVTV_DEBUG_WARN("%s: Couldn't find start of buffer within the first 256 bytes\n", s->name);
					offset = s->dma_last_offset;
				पूर्ण
				अगर (s->dma_last_offset != offset)
					IVTV_DEBUG_WARN("%s: offset %d -> %d\n", s->name, s->dma_last_offset, offset);
				s->dma_last_offset = offset;
			पूर्ण
			अगर (itv->has_cx23415 && (s->type == IVTV_ENC_STREAM_TYPE_PCM ||
						s->type == IVTV_DEC_STREAM_TYPE_VBI)) अणु
				ग_लिखो_dec_sync(0, s->dma_offset - IVTV_DECODER_OFFSET);
			पूर्ण
			अन्यथा अणु
				ग_लिखो_enc_sync(0, s->dma_offset);
			पूर्ण
			अगर (offset) अणु
				buf->bytesused -= offset;
				स_नकल(buf->buf, buf->buf + offset, buf->bytesused + offset);
			पूर्ण
			*u32buf = cpu_to_le32(s->dma_backup);
		पूर्ण
		x++;
		/* flag byteswap ABCD -> DCBA क्रम MPG & VBI data outside irq */
		अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG ||
		    s->type == IVTV_ENC_STREAM_TYPE_VBI)
			buf->b_flags |= IVTV_F_B_NEED_BUF_SWAP;
	पूर्ण
	अगर (buf)
		buf->bytesused += s->dma_last_offset;
	अगर (buf && s->type == IVTV_DEC_STREAM_TYPE_VBI) अणु
		list_क्रम_each_entry(buf, &s->q_dma.list, list) अणु
			/* Parse and Groom VBI Data */
			s->q_dma.bytesused -= buf->bytesused;
			ivtv_process_vbi_data(itv, buf, 0, s->type);
			s->q_dma.bytesused += buf->bytesused;
		पूर्ण
		अगर (s->fh == शून्य) अणु
			ivtv_queue_move(s, &s->q_dma, शून्य, &s->q_मुक्त, 0);
			वापस;
		पूर्ण
	पूर्ण

	ivtv_queue_move(s, &s->q_dma, शून्य, &s->q_full, s->q_dma.bytesused);

	अगर (s->type == IVTV_ENC_STREAM_TYPE_PCM &&
	    itv->pcm_announce_callback != शून्य) अणु
		/*
		 * Set up the work handler to pass the data to ivtv-alsa.
		 *
		 * We just use q_full and let the work handler race with users
		 * making ivtv-fileops.c calls on the PCM device node.
		 *
		 * Users should not be using both the ALSA and V4L2 PCM audio
		 * capture पूर्णांकerfaces at the same समय.  If the user करोes this,
		 * fragments of data will just go out each पूर्णांकerface as they
		 * race क्रम PCM data.
		 */
		set_bit(IVTV_F_I_WORK_HANDLER_PCM, &itv->i_flags);
		set_bit(IVTV_F_I_HAVE_WORK, &itv->i_flags);
	पूर्ण

	अगर (s->fh)
		wake_up(&s->रुकोq);
पूर्ण

व्योम ivtv_dma_stream_dec_prepare(काष्ठा ivtv_stream *s, u32 offset, पूर्णांक lock)
अणु
	काष्ठा ivtv *itv = s->itv;
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	u8 frame = yi->draw_frame;
	काष्ठा yuv_frame_info *f = &yi->new_frame_info[frame];
	काष्ठा ivtv_buffer *buf;
	u32 y_size = 720 * ((f->src_h + 31) & ~31);
	u32 uv_offset = offset + IVTV_YUV_BUFFER_UV_OFFSET;
	पूर्णांक y_करोne = 0;
	पूर्णांक bytes_written = 0;
	पूर्णांक idx = 0;

	IVTV_DEBUG_HI_DMA("DEC PREPARE DMA %s: %08x %08x\n", s->name, s->q_predma.bytesused, offset);

	/* Insert buffer block क्रम YUV अगर needed */
	अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV && f->offset_y) अणु
		अगर (yi->blanking_dmaptr) अणु
			s->sg_pending[idx].src = yi->blanking_dmaptr;
			s->sg_pending[idx].dst = offset;
			s->sg_pending[idx].size = 720 * 16;
		पूर्ण
		offset += 720 * 16;
		idx++;
	पूर्ण

	list_क्रम_each_entry(buf, &s->q_predma.list, list) अणु
		/* YUV UV Offset from Y Buffer */
		अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV && !y_करोne &&
				(bytes_written + buf->bytesused) >= y_size) अणु
			s->sg_pending[idx].src = buf->dma_handle;
			s->sg_pending[idx].dst = offset;
			s->sg_pending[idx].size = y_size - bytes_written;
			offset = uv_offset;
			अगर (s->sg_pending[idx].size != buf->bytesused) अणु
				idx++;
				s->sg_pending[idx].src =
				  buf->dma_handle + s->sg_pending[idx - 1].size;
				s->sg_pending[idx].dst = offset;
				s->sg_pending[idx].size =
				   buf->bytesused - s->sg_pending[idx - 1].size;
				offset += s->sg_pending[idx].size;
			पूर्ण
			y_करोne = 1;
		पूर्ण अन्यथा अणु
			s->sg_pending[idx].src = buf->dma_handle;
			s->sg_pending[idx].dst = offset;
			s->sg_pending[idx].size = buf->bytesused;
			offset += buf->bytesused;
		पूर्ण
		bytes_written += buf->bytesused;

		/* Sync SG buffers */
		ivtv_buf_sync_क्रम_device(s, buf);
		idx++;
	पूर्ण
	s->sg_pending_size = idx;

	/* Sync Hardware SG List of buffers */
	ivtv_stream_sync_क्रम_device(s);
	अगर (lock) अणु
		अचिन्हित दीर्घ flags = 0;

		spin_lock_irqsave(&itv->dma_reg_lock, flags);
		अगर (!test_bit(IVTV_F_I_DMA, &itv->i_flags))
			ivtv_dma_dec_start(s);
		अन्यथा
			set_bit(IVTV_F_S_DMA_PENDING, &s->s_flags);
		spin_unlock_irqrestore(&itv->dma_reg_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (!test_bit(IVTV_F_I_DMA, &itv->i_flags))
			ivtv_dma_dec_start(s);
		अन्यथा
			set_bit(IVTV_F_S_DMA_PENDING, &s->s_flags);
	पूर्ण
पूर्ण

अटल व्योम ivtv_dma_enc_start_xfer(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;

	s->sg_dma->src = cpu_to_le32(s->sg_processing[s->sg_processed].src);
	s->sg_dma->dst = cpu_to_le32(s->sg_processing[s->sg_processed].dst);
	s->sg_dma->size = cpu_to_le32(s->sg_processing[s->sg_processed].size | 0x80000000);
	s->sg_processed++;
	/* Sync Hardware SG List of buffers */
	ivtv_stream_sync_क्रम_device(s);
	ग_लिखो_reg(s->sg_handle, IVTV_REG_ENCDMAADDR);
	ग_लिखो_reg_sync(पढ़ो_reg(IVTV_REG_DMAXFER) | 0x02, IVTV_REG_DMAXFER);
	itv->dma_समयr.expires = jअगरfies + msecs_to_jअगरfies(300);
	add_समयr(&itv->dma_समयr);
पूर्ण

अटल व्योम ivtv_dma_dec_start_xfer(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;

	s->sg_dma->src = cpu_to_le32(s->sg_processing[s->sg_processed].src);
	s->sg_dma->dst = cpu_to_le32(s->sg_processing[s->sg_processed].dst);
	s->sg_dma->size = cpu_to_le32(s->sg_processing[s->sg_processed].size | 0x80000000);
	s->sg_processed++;
	/* Sync Hardware SG List of buffers */
	ivtv_stream_sync_क्रम_device(s);
	ग_लिखो_reg(s->sg_handle, IVTV_REG_DECDMAADDR);
	ग_लिखो_reg_sync(पढ़ो_reg(IVTV_REG_DMAXFER) | 0x01, IVTV_REG_DMAXFER);
	itv->dma_समयr.expires = jअगरfies + msecs_to_jअगरfies(300);
	add_समयr(&itv->dma_समयr);
पूर्ण

/* start the encoder DMA */
अटल व्योम ivtv_dma_enc_start(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;
	काष्ठा ivtv_stream *s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
	पूर्णांक i;

	IVTV_DEBUG_HI_DMA("start %s for %s\n", ivtv_use_dma(s) ? "DMA" : "PIO", s->name);

	अगर (s->q_predma.bytesused)
		ivtv_queue_move(s, &s->q_predma, शून्य, &s->q_dma, s->q_predma.bytesused);

	अगर (ivtv_use_dma(s))
		s->sg_pending[s->sg_pending_size - 1].size += 256;

	/* If this is an MPEG stream, and VBI data is also pending, then append the
	   VBI DMA to the MPEG DMA and transfer both sets of data at once.

	   VBI DMA is a second class citizen compared to MPEG and mixing them together
	   will confuse the firmware (the end of a VBI DMA is seen as the end of a
	   MPEG DMA, thus effectively dropping an MPEG frame). So instead we make
	   sure we only use the MPEG DMA to transfer the VBI DMA अगर both are in
	   use. This way no conflicts occur. */
	clear_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags);
	अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG && s_vbi->sg_pending_size &&
			s->sg_pending_size + s_vbi->sg_pending_size <= s->buffers) अणु
		ivtv_queue_move(s_vbi, &s_vbi->q_predma, शून्य, &s_vbi->q_dma, s_vbi->q_predma.bytesused);
		अगर (ivtv_use_dma(s_vbi))
			s_vbi->sg_pending[s_vbi->sg_pending_size - 1].size += 256;
		क्रम (i = 0; i < s_vbi->sg_pending_size; i++) अणु
			s->sg_pending[s->sg_pending_size++] = s_vbi->sg_pending[i];
		पूर्ण
		s_vbi->dma_offset = s_vbi->pending_offset;
		s_vbi->sg_pending_size = 0;
		s_vbi->dma_xfer_cnt++;
		set_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags);
		IVTV_DEBUG_HI_DMA("include DMA for %s\n", s_vbi->name);
	पूर्ण

	s->dma_xfer_cnt++;
	स_नकल(s->sg_processing, s->sg_pending, माप(काष्ठा ivtv_sg_host_element) * s->sg_pending_size);
	s->sg_processing_size = s->sg_pending_size;
	s->sg_pending_size = 0;
	s->sg_processed = 0;
	s->dma_offset = s->pending_offset;
	s->dma_backup = s->pending_backup;
	s->dma_pts = s->pending_pts;

	अगर (ivtv_use_pio(s)) अणु
		set_bit(IVTV_F_I_WORK_HANDLER_PIO, &itv->i_flags);
		set_bit(IVTV_F_I_HAVE_WORK, &itv->i_flags);
		set_bit(IVTV_F_I_PIO, &itv->i_flags);
		itv->cur_pio_stream = s->type;
	पूर्ण
	अन्यथा अणु
		itv->dma_retries = 0;
		ivtv_dma_enc_start_xfer(s);
		set_bit(IVTV_F_I_DMA, &itv->i_flags);
		itv->cur_dma_stream = s->type;
	पूर्ण
पूर्ण

अटल व्योम ivtv_dma_dec_start(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;

	अगर (s->q_predma.bytesused)
		ivtv_queue_move(s, &s->q_predma, शून्य, &s->q_dma, s->q_predma.bytesused);
	s->dma_xfer_cnt++;
	स_नकल(s->sg_processing, s->sg_pending, माप(काष्ठा ivtv_sg_host_element) * s->sg_pending_size);
	s->sg_processing_size = s->sg_pending_size;
	s->sg_pending_size = 0;
	s->sg_processed = 0;

	IVTV_DEBUG_HI_DMA("start DMA for %s\n", s->name);
	itv->dma_retries = 0;
	ivtv_dma_dec_start_xfer(s);
	set_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = s->type;
पूर्ण

अटल व्योम ivtv_irq_dma_पढ़ो(काष्ठा ivtv *itv)
अणु
	काष्ठा ivtv_stream *s = शून्य;
	काष्ठा ivtv_buffer *buf;
	पूर्णांक hw_stream_type = 0;

	IVTV_DEBUG_HI_IRQ("DEC DMA READ\n");

	del_समयr(&itv->dma_समयr);

	अगर (!test_bit(IVTV_F_I_UDMA, &itv->i_flags) && itv->cur_dma_stream < 0)
		वापस;

	अगर (!test_bit(IVTV_F_I_UDMA, &itv->i_flags)) अणु
		s = &itv->streams[itv->cur_dma_stream];
		ivtv_stream_sync_क्रम_cpu(s);

		अगर (पढ़ो_reg(IVTV_REG_DMASTATUS) & 0x14) अणु
			IVTV_DEBUG_WARN("DEC DMA ERROR %x (xfer %d of %d, retry %d)\n",
					पढ़ो_reg(IVTV_REG_DMASTATUS),
					s->sg_processed, s->sg_processing_size, itv->dma_retries);
			ग_लिखो_reg(पढ़ो_reg(IVTV_REG_DMASTATUS) & 3, IVTV_REG_DMASTATUS);
			अगर (itv->dma_retries == 3) अणु
				/* Too many retries, give up on this frame */
				itv->dma_retries = 0;
				s->sg_processed = s->sg_processing_size;
			पूर्ण
			अन्यथा अणु
				/* Retry, starting with the first xfer segment.
				   Just retrying the current segment is not sufficient. */
				s->sg_processed = 0;
				itv->dma_retries++;
			पूर्ण
		पूर्ण
		अगर (s->sg_processed < s->sg_processing_size) अणु
			/* DMA next buffer */
			ivtv_dma_dec_start_xfer(s);
			वापस;
		पूर्ण
		अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV)
			hw_stream_type = 2;
		IVTV_DEBUG_HI_DMA("DEC DATA READ %s: %d\n", s->name, s->q_dma.bytesused);

		/* For some reason must kick the firmware, like PIO mode,
		   I think this tells the firmware we are करोne and the size
		   of the xfer so it can calculate what we need next.
		   I think we can करो this part ourselves but would have to
		   fully calculate xfer info ourselves and not use पूर्णांकerrupts
		 */
		ivtv_vapi(itv, CX2341X_DEC_SCHED_DMA_FROM_HOST, 3, 0, s->q_dma.bytesused,
				hw_stream_type);

		/* Free last DMA call */
		जबतक ((buf = ivtv_dequeue(s, &s->q_dma)) != शून्य) अणु
			ivtv_buf_sync_क्रम_cpu(s, buf);
			ivtv_enqueue(s, buf, &s->q_मुक्त);
		पूर्ण
		wake_up(&s->रुकोq);
	पूर्ण
	clear_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	wake_up(&itv->dma_रुकोq);
पूर्ण

अटल व्योम ivtv_irq_enc_dma_complete(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा ivtv_stream *s;

	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA_END, 2, data);
	IVTV_DEBUG_HI_IRQ("ENC DMA COMPLETE %x %d (%d)\n", data[0], data[1], itv->cur_dma_stream);

	del_समयr(&itv->dma_समयr);

	अगर (itv->cur_dma_stream < 0)
		वापस;

	s = &itv->streams[itv->cur_dma_stream];
	ivtv_stream_sync_क्रम_cpu(s);

	अगर (data[0] & 0x18) अणु
		IVTV_DEBUG_WARN("ENC DMA ERROR %x (offset %08x, xfer %d of %d, retry %d)\n", data[0],
			s->dma_offset, s->sg_processed, s->sg_processing_size, itv->dma_retries);
		ग_लिखो_reg(पढ़ो_reg(IVTV_REG_DMASTATUS) & 3, IVTV_REG_DMASTATUS);
		अगर (itv->dma_retries == 3) अणु
			/* Too many retries, give up on this frame */
			itv->dma_retries = 0;
			s->sg_processed = s->sg_processing_size;
		पूर्ण
		अन्यथा अणु
			/* Retry, starting with the first xfer segment.
			   Just retrying the current segment is not sufficient. */
			s->sg_processed = 0;
			itv->dma_retries++;
		पूर्ण
	पूर्ण
	अगर (s->sg_processed < s->sg_processing_size) अणु
		/* DMA next buffer */
		ivtv_dma_enc_start_xfer(s);
		वापस;
	पूर्ण
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	dma_post(s);
	अगर (test_and_clear_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags)) अणु
		s = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
		dma_post(s);
	पूर्ण
	s->sg_processing_size = 0;
	s->sg_processed = 0;
	wake_up(&itv->dma_रुकोq);
पूर्ण

अटल व्योम ivtv_irq_enc_pio_complete(काष्ठा ivtv *itv)
अणु
	काष्ठा ivtv_stream *s;

	अगर (itv->cur_pio_stream < 0 || itv->cur_pio_stream >= IVTV_MAX_STREAMS) अणु
		itv->cur_pio_stream = -1;
		वापस;
	पूर्ण
	s = &itv->streams[itv->cur_pio_stream];
	IVTV_DEBUG_HI_IRQ("ENC PIO COMPLETE %s\n", s->name);
	clear_bit(IVTV_F_I_PIO, &itv->i_flags);
	itv->cur_pio_stream = -1;
	dma_post(s);
	अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 0);
	अन्यथा अगर (s->type == IVTV_ENC_STREAM_TYPE_YUV)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 1);
	अन्यथा अगर (s->type == IVTV_ENC_STREAM_TYPE_PCM)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 2);
	clear_bit(IVTV_F_I_PIO, &itv->i_flags);
	अगर (test_and_clear_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags)) अणु
		s = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
		dma_post(s);
	पूर्ण
	wake_up(&itv->dma_रुकोq);
पूर्ण

अटल व्योम ivtv_irq_dma_err(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	u32 status;

	del_समयr(&itv->dma_समयr);

	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA_END, 2, data);
	status = पढ़ो_reg(IVTV_REG_DMASTATUS);
	IVTV_DEBUG_WARN("DMA ERROR %08x %08x %08x %d\n", data[0], data[1],
				status, itv->cur_dma_stream);
	/*
	 * We करो *not* ग_लिखो back to the IVTV_REG_DMASTATUS रेजिस्टर to
	 * clear the error status, अगर either the encoder ग_लिखो (0x02) or
	 * decoder पढ़ो (0x01) bus master DMA operation करो not indicate
	 * completed.  We can race with the DMA engine, which may have
	 * transitioned to completed status *after* we पढ़ो the रेजिस्टर.
	 * Setting a IVTV_REG_DMASTATUS flag back to "busy" status, after the
	 * DMA engine has completed, will cause the DMA engine to stop working.
	 */
	status &= 0x3;
	अगर (status == 0x3)
		ग_लिखो_reg(status, IVTV_REG_DMASTATUS);

	अगर (!test_bit(IVTV_F_I_UDMA, &itv->i_flags) &&
	    itv->cur_dma_stream >= 0 && itv->cur_dma_stream < IVTV_MAX_STREAMS) अणु
		काष्ठा ivtv_stream *s = &itv->streams[itv->cur_dma_stream];

		अगर (s->type >= IVTV_DEC_STREAM_TYPE_MPG) अणु
			/* retry */
			/*
			 * FIXME - handle हालs of DMA error similar to
			 * encoder below, except conditioned on status & 0x1
			 */
			ivtv_dma_dec_start(s);
			वापस;
		पूर्ण अन्यथा अणु
			अगर ((status & 0x2) == 0) अणु
				/*
				 * CX2341x Bus Master DMA ग_लिखो is ongoing.
				 * Reset the समयr and let it complete.
				 */
				itv->dma_समयr.expires =
						jअगरfies + msecs_to_jअगरfies(600);
				add_समयr(&itv->dma_समयr);
				वापस;
			पूर्ण

			अगर (itv->dma_retries < 3) अणु
				/*
				 * CX2341x Bus Master DMA ग_लिखो has ended.
				 * Retry the ग_लिखो, starting with the first
				 * xfer segment. Just retrying the current
				 * segment is not sufficient.
				 */
				s->sg_processed = 0;
				itv->dma_retries++;
				ivtv_dma_enc_start_xfer(s);
				वापस;
			पूर्ण
			/* Too many retries, give up on this one */
		पूर्ण

	पूर्ण
	अगर (test_bit(IVTV_F_I_UDMA, &itv->i_flags)) अणु
		ivtv_udma_start(itv);
		वापस;
	पूर्ण
	clear_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	wake_up(&itv->dma_रुकोq);
पूर्ण

अटल व्योम ivtv_irq_enc_start_cap(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा ivtv_stream *s;

	/* Get DMA destination and size arguments from card */
	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA, 7, data);
	IVTV_DEBUG_HI_IRQ("ENC START CAP %d: %08x %08x\n", data[0], data[1], data[2]);

	अगर (data[0] > 2 || data[1] == 0 || data[2] == 0) अणु
		IVTV_DEBUG_WARN("Unknown input: %08x %08x %08x\n",
				data[0], data[1], data[2]);
		वापस;
	पूर्ण
	s = &itv->streams[ivtv_stream_map[data[0]]];
	अगर (!stream_enc_dma_append(s, data)) अणु
		set_bit(ivtv_use_pio(s) ? IVTV_F_S_PIO_PENDING : IVTV_F_S_DMA_PENDING, &s->s_flags);
	पूर्ण
पूर्ण

अटल व्योम ivtv_irq_enc_vbi_cap(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा ivtv_stream *s;

	IVTV_DEBUG_HI_IRQ("ENC START VBI CAP\n");
	s = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];

	अगर (!stream_enc_dma_append(s, data))
		set_bit(ivtv_use_pio(s) ? IVTV_F_S_PIO_PENDING : IVTV_F_S_DMA_PENDING, &s->s_flags);
पूर्ण

अटल व्योम ivtv_irq_dec_vbi_reinsert(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा ivtv_stream *s = &itv->streams[IVTV_DEC_STREAM_TYPE_VBI];

	IVTV_DEBUG_HI_IRQ("DEC VBI REINSERT\n");
	अगर (test_bit(IVTV_F_S_CLAIMED, &s->s_flags) &&
			!stream_enc_dma_append(s, data)) अणु
		set_bit(IVTV_F_S_PIO_PENDING, &s->s_flags);
	पूर्ण
पूर्ण

अटल व्योम ivtv_irq_dec_data_req(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा ivtv_stream *s;

	/* YUV or MPG */

	अगर (test_bit(IVTV_F_I_DEC_YUV, &itv->i_flags)) अणु
		ivtv_api_get_data(&itv->dec_mbox, IVTV_MBOX_DMA, 2, data);
		itv->dma_data_req_size =
				 1080 * ((itv->yuv_info.v4l2_src_h + 31) & ~31);
		itv->dma_data_req_offset = data[1];
		अगर (atomic_पढ़ो(&itv->yuv_info.next_dma_frame) >= 0)
			ivtv_yuv_frame_complete(itv);
		s = &itv->streams[IVTV_DEC_STREAM_TYPE_YUV];
	पूर्ण
	अन्यथा अणु
		ivtv_api_get_data(&itv->dec_mbox, IVTV_MBOX_DMA, 3, data);
		itv->dma_data_req_size = min_t(u32, data[2], 0x10000);
		itv->dma_data_req_offset = data[1];
		s = &itv->streams[IVTV_DEC_STREAM_TYPE_MPG];
	पूर्ण
	IVTV_DEBUG_HI_IRQ("DEC DATA REQ %s: %d %08x %u\n", s->name, s->q_full.bytesused,
		       itv->dma_data_req_offset, itv->dma_data_req_size);
	अगर (itv->dma_data_req_size == 0 || s->q_full.bytesused < itv->dma_data_req_size) अणु
		set_bit(IVTV_F_S_NEEDS_DATA, &s->s_flags);
	पूर्ण
	अन्यथा अणु
		अगर (test_bit(IVTV_F_I_DEC_YUV, &itv->i_flags))
			ivtv_yuv_setup_stream_frame(itv);
		clear_bit(IVTV_F_S_NEEDS_DATA, &s->s_flags);
		ivtv_queue_move(s, &s->q_full, शून्य, &s->q_predma, itv->dma_data_req_size);
		ivtv_dma_stream_dec_prepare(s, itv->dma_data_req_offset + IVTV_DECODER_OFFSET, 0);
	पूर्ण
पूर्ण

अटल व्योम ivtv_irq_vsync(काष्ठा ivtv *itv)
अणु
	/* The vsync पूर्णांकerrupt is unusual in that it won't clear until
	 * the end of the first line क्रम the current field, at which
	 * poपूर्णांक it clears itself. This can result in repeated vsync
	 * पूर्णांकerrupts, or a missed vsync. Read some of the रेजिस्टरs
	 * to determine the line being displayed and ensure we handle
	 * one vsync per frame.
	 */
	अचिन्हित पूर्णांक frame = पढ़ो_reg(IVTV_REG_DEC_LINE_FIELD) & 1;
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	पूर्णांक last_dma_frame = atomic_पढ़ो(&yi->next_dma_frame);
	काष्ठा yuv_frame_info *f = &yi->new_frame_info[last_dma_frame];

	अगर (0) IVTV_DEBUG_IRQ("DEC VSYNC\n");

	अगर (((frame ^ f->sync_field) == 0 &&
		((itv->last_vsync_field & 1) ^ f->sync_field)) ||
			(frame != (itv->last_vsync_field & 1) && !f->पूर्णांकerlaced)) अणु
		पूर्णांक next_dma_frame = last_dma_frame;

		अगर (!(f->पूर्णांकerlaced && f->delay && yi->fields_lapsed < 1)) अणु
			अगर (next_dma_frame >= 0 && next_dma_frame != atomic_पढ़ो(&yi->next_fill_frame)) अणु
				ग_लिखो_reg(yuv_offset[next_dma_frame] >> 4, 0x82c);
				ग_लिखो_reg((yuv_offset[next_dma_frame] + IVTV_YUV_BUFFER_UV_OFFSET) >> 4, 0x830);
				ग_लिखो_reg(yuv_offset[next_dma_frame] >> 4, 0x834);
				ग_लिखो_reg((yuv_offset[next_dma_frame] + IVTV_YUV_BUFFER_UV_OFFSET) >> 4, 0x838);
				next_dma_frame = (next_dma_frame + 1) % IVTV_YUV_BUFFERS;
				atomic_set(&yi->next_dma_frame, next_dma_frame);
				yi->fields_lapsed = -1;
				yi->running = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (frame != (itv->last_vsync_field & 1)) अणु
		अटल स्थिर काष्ठा v4l2_event evtop = अणु
			.type = V4L2_EVENT_VSYNC,
			.u.vsync.field = V4L2_FIELD_TOP,
		पूर्ण;
		अटल स्थिर काष्ठा v4l2_event evbottom = अणु
			.type = V4L2_EVENT_VSYNC,
			.u.vsync.field = V4L2_FIELD_BOTTOM,
		पूर्ण;
		काष्ठा ivtv_stream *s = ivtv_get_output_stream(itv);

		itv->last_vsync_field += 1;
		अगर (frame == 0) अणु
			clear_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags);
			clear_bit(IVTV_F_I_EV_VSYNC_FIELD, &itv->i_flags);
		पूर्ण
		अन्यथा अणु
			set_bit(IVTV_F_I_EV_VSYNC_FIELD, &itv->i_flags);
		पूर्ण
		अगर (test_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags)) अणु
			set_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags);
			wake_up(&itv->event_रुकोq);
			अगर (s)
				wake_up(&s->रुकोq);
		पूर्ण
		अगर (s && s->vdev.v4l2_dev)
			v4l2_event_queue(&s->vdev, frame ? &evtop : &evbottom);
		wake_up(&itv->vsync_रुकोq);

		/* Send VBI to saa7127 */
		अगर (frame && (itv->output_mode == OUT_PASSTHROUGH ||
			test_bit(IVTV_F_I_UPDATE_WSS, &itv->i_flags) ||
			test_bit(IVTV_F_I_UPDATE_VPS, &itv->i_flags) ||
			test_bit(IVTV_F_I_UPDATE_CC, &itv->i_flags))) अणु
			set_bit(IVTV_F_I_WORK_HANDLER_VBI, &itv->i_flags);
			set_bit(IVTV_F_I_HAVE_WORK, &itv->i_flags);
		पूर्ण

		/* Check अगर we need to update the yuv रेजिस्टरs */
		अगर (yi->running && (yi->yuv_क्रमced_update || f->update)) अणु
			अगर (!f->update) अणु
				last_dma_frame =
					(u8)(atomic_पढ़ो(&yi->next_dma_frame) -
						 1) % IVTV_YUV_BUFFERS;
				f = &yi->new_frame_info[last_dma_frame];
			पूर्ण

			अगर (f->src_w) अणु
				yi->update_frame = last_dma_frame;
				f->update = 0;
				yi->yuv_क्रमced_update = 0;
				set_bit(IVTV_F_I_WORK_HANDLER_YUV, &itv->i_flags);
				set_bit(IVTV_F_I_HAVE_WORK, &itv->i_flags);
			पूर्ण
		पूर्ण

		yi->fields_lapsed++;
	पूर्ण
पूर्ण

#घोषणा IVTV_IRQ_DMA (IVTV_IRQ_DMA_READ | IVTV_IRQ_ENC_DMA_COMPLETE | IVTV_IRQ_DMA_ERR | IVTV_IRQ_ENC_START_CAP | IVTV_IRQ_ENC_VBI_CAP | IVTV_IRQ_DEC_DATA_REQ | IVTV_IRQ_DEC_VBI_RE_INSERT)

irqवापस_t ivtv_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ivtv *itv = (काष्ठा ivtv *)dev_id;
	u32 combo;
	u32 stat;
	पूर्णांक i;
	u8 vsync_क्रमce = 0;

	spin_lock(&itv->dma_reg_lock);
	/* get contents of irq status रेजिस्टर */
	stat = पढ़ो_reg(IVTV_REG_IRQSTATUS);

	combo = ~itv->irqmask & stat;

	/* Clear out IRQ */
	अगर (combo) ग_लिखो_reg(combo, IVTV_REG_IRQSTATUS);

	अगर (0 == combo) अणु
		/* The vsync पूर्णांकerrupt is unusual and clears itself. If we
		 * took too दीर्घ, we may have missed it. Do some checks
		 */
		अगर (~itv->irqmask & IVTV_IRQ_DEC_VSYNC) अणु
			/* vsync is enabled, see अगर we're in a new field */
			अगर ((itv->last_vsync_field & 1) !=
			    (पढ़ो_reg(IVTV_REG_DEC_LINE_FIELD) & 1)) अणु
				/* New field, looks like we missed it */
				IVTV_DEBUG_YUV("VSync interrupt missed %d\n",
				       पढ़ो_reg(IVTV_REG_DEC_LINE_FIELD) >> 16);
				vsync_क्रमce = 1;
			पूर्ण
		पूर्ण

		अगर (!vsync_क्रमce) अणु
			/* No Vsync expected, wasn't क्रम us */
			spin_unlock(&itv->dma_reg_lock);
			वापस IRQ_NONE;
		पूर्ण
	पूर्ण

	/* Exclude पूर्णांकerrupts noted below from the output, otherwise the log is flooded with
	   these messages */
	अगर (combo & ~0xff6d0400)
		IVTV_DEBUG_HI_IRQ("======= valid IRQ bits: 0x%08x ======\n", combo);

	अगर (combo & IVTV_IRQ_DEC_DMA_COMPLETE) अणु
		IVTV_DEBUG_HI_IRQ("DEC DMA COMPLETE\n");
	पूर्ण

	अगर (combo & IVTV_IRQ_DMA_READ) अणु
		ivtv_irq_dma_पढ़ो(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_ENC_DMA_COMPLETE) अणु
		ivtv_irq_enc_dma_complete(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_ENC_PIO_COMPLETE) अणु
		ivtv_irq_enc_pio_complete(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_DMA_ERR) अणु
		ivtv_irq_dma_err(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_ENC_START_CAP) अणु
		ivtv_irq_enc_start_cap(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_ENC_VBI_CAP) अणु
		ivtv_irq_enc_vbi_cap(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_DEC_VBI_RE_INSERT) अणु
		ivtv_irq_dec_vbi_reinsert(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_ENC_EOS) अणु
		IVTV_DEBUG_IRQ("ENC EOS\n");
		set_bit(IVTV_F_I_EOS, &itv->i_flags);
		wake_up(&itv->eos_रुकोq);
	पूर्ण

	अगर (combo & IVTV_IRQ_DEC_DATA_REQ) अणु
		ivtv_irq_dec_data_req(itv);
	पूर्ण

	/* Decoder Vertical Sync - We can't rely on 'combo', so check अगर vsync enabled */
	अगर (~itv->irqmask & IVTV_IRQ_DEC_VSYNC) अणु
		ivtv_irq_vsync(itv);
	पूर्ण

	अगर (combo & IVTV_IRQ_ENC_VIM_RST) अणु
		IVTV_DEBUG_IRQ("VIM RST\n");
		/*ivtv_vapi(itv, CX2341X_ENC_REFRESH_INPUT, 0); */
	पूर्ण

	अगर (combo & IVTV_IRQ_DEC_AUD_MODE_CHG) अणु
		IVTV_DEBUG_INFO("Stereo mode changed\n");
	पूर्ण

	अगर ((combo & IVTV_IRQ_DMA) && !test_bit(IVTV_F_I_DMA, &itv->i_flags)) अणु
		itv->irq_rr_idx++;
		क्रम (i = 0; i < IVTV_MAX_STREAMS; i++) अणु
			पूर्णांक idx = (i + itv->irq_rr_idx) % IVTV_MAX_STREAMS;
			काष्ठा ivtv_stream *s = &itv->streams[idx];

			अगर (!test_and_clear_bit(IVTV_F_S_DMA_PENDING, &s->s_flags))
				जारी;
			अगर (s->type >= IVTV_DEC_STREAM_TYPE_MPG)
				ivtv_dma_dec_start(s);
			अन्यथा
				ivtv_dma_enc_start(s);
			अवरोध;
		पूर्ण

		अगर (i == IVTV_MAX_STREAMS &&
		    test_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags))
			ivtv_udma_start(itv);
	पूर्ण

	अगर ((combo & IVTV_IRQ_DMA) && !test_bit(IVTV_F_I_PIO, &itv->i_flags)) अणु
		itv->irq_rr_idx++;
		क्रम (i = 0; i < IVTV_MAX_STREAMS; i++) अणु
			पूर्णांक idx = (i + itv->irq_rr_idx) % IVTV_MAX_STREAMS;
			काष्ठा ivtv_stream *s = &itv->streams[idx];

			अगर (!test_and_clear_bit(IVTV_F_S_PIO_PENDING, &s->s_flags))
				जारी;
			अगर (s->type == IVTV_DEC_STREAM_TYPE_VBI || s->type < IVTV_DEC_STREAM_TYPE_MPG)
				ivtv_dma_enc_start(s);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(IVTV_F_I_HAVE_WORK, &itv->i_flags)) अणु
		kthपढ़ो_queue_work(&itv->irq_worker, &itv->irq_work);
	पूर्ण

	spin_unlock(&itv->dma_reg_lock);

	/* If we've just handled a 'forced' vsync, it's safest to say it
	 * wasn't ours. Another device may have triggered it at just
	 * the right समय.
	 */
	वापस vsync_क्रमce ? IRQ_NONE : IRQ_HANDLED;
पूर्ण

व्योम ivtv_unfinished_dma(काष्ठा समयr_list *t)
अणु
	काष्ठा ivtv *itv = from_समयr(itv, t, dma_समयr);

	अगर (!test_bit(IVTV_F_I_DMA, &itv->i_flags))
		वापस;
	IVTV_ERR("DMA TIMEOUT %08x %d\n", पढ़ो_reg(IVTV_REG_DMASTATUS), itv->cur_dma_stream);

	ग_लिखो_reg(पढ़ो_reg(IVTV_REG_DMASTATUS) & 3, IVTV_REG_DMASTATUS);
	clear_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	wake_up(&itv->dma_रुकोq);
पूर्ण
