<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    file operation functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-fileops.h"
#समावेश "ivtv-i2c.h"
#समावेश "ivtv-queue.h"
#समावेश "ivtv-udma.h"
#समावेश "ivtv-irq.h"
#समावेश "ivtv-vbi.h"
#समावेश "ivtv-mailbox.h"
#समावेश "ivtv-routing.h"
#समावेश "ivtv-streams.h"
#समावेश "ivtv-yuv.h"
#समावेश "ivtv-ioctl.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-firmware.h"
#समावेश <media/v4l2-event.h>
#समावेश <media/i2c/saa7115.h>

/* This function tries to claim the stream क्रम a specअगरic file descriptor.
   If no one अन्यथा is using this stream then the stream is claimed and
   associated VBI streams are also स्वतःmatically claimed.
   Possible error वापसs: -EBUSY अगर someone अन्यथा has claimed
   the stream or 0 on success. */
पूर्णांक ivtv_claim_stream(काष्ठा ivtv_खोलो_id *id, पूर्णांक type)
अणु
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[type];
	काष्ठा ivtv_stream *s_vbi;
	पूर्णांक vbi_type;

	अगर (test_and_set_bit(IVTV_F_S_CLAIMED, &s->s_flags)) अणु
		/* someone alपढ़ोy claimed this stream */
		अगर (s->fh == &id->fh) अणु
			/* yes, this file descriptor did. So that's OK. */
			वापस 0;
		पूर्ण
		अगर (s->fh == शून्य && (type == IVTV_DEC_STREAM_TYPE_VBI ||
					 type == IVTV_ENC_STREAM_TYPE_VBI)) अणु
			/* VBI is handled alपढ़ोy पूर्णांकernally, now also assign
			   the file descriptor to this stream क्रम बाह्यal
			   पढ़ोing of the stream. */
			s->fh = &id->fh;
			IVTV_DEBUG_INFO("Start Read VBI\n");
			वापस 0;
		पूर्ण
		/* someone अन्यथा is using this stream alपढ़ोy */
		IVTV_DEBUG_INFO("Stream %d is busy\n", type);
		वापस -EBUSY;
	पूर्ण
	s->fh = &id->fh;
	अगर (type == IVTV_DEC_STREAM_TYPE_VBI) अणु
		/* Enable reinsertion पूर्णांकerrupt */
		ivtv_clear_irq_mask(itv, IVTV_IRQ_DEC_VBI_RE_INSERT);
	पूर्ण

	/* IVTV_DEC_STREAM_TYPE_MPG needs to claim IVTV_DEC_STREAM_TYPE_VBI,
	   IVTV_ENC_STREAM_TYPE_MPG needs to claim IVTV_ENC_STREAM_TYPE_VBI
	   (provided VBI insertion is on and sliced VBI is selected), क्रम all
	   other streams we're करोne */
	अगर (type == IVTV_DEC_STREAM_TYPE_MPG) अणु
		vbi_type = IVTV_DEC_STREAM_TYPE_VBI;
	पूर्ण अन्यथा अगर (type == IVTV_ENC_STREAM_TYPE_MPG &&
		   itv->vbi.insert_mpeg && !ivtv_raw_vbi(itv)) अणु
		vbi_type = IVTV_ENC_STREAM_TYPE_VBI;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
	s_vbi = &itv->streams[vbi_type];

	अगर (!test_and_set_bit(IVTV_F_S_CLAIMED, &s_vbi->s_flags)) अणु
		/* Enable reinsertion पूर्णांकerrupt */
		अगर (vbi_type == IVTV_DEC_STREAM_TYPE_VBI)
			ivtv_clear_irq_mask(itv, IVTV_IRQ_DEC_VBI_RE_INSERT);
	पूर्ण
	/* mark that it is used पूर्णांकernally */
	set_bit(IVTV_F_S_INTERNAL_USE, &s_vbi->s_flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ivtv_claim_stream);

/* This function releases a previously claimed stream. It will take पूर्णांकo
   account associated VBI streams. */
व्योम ivtv_release_stream(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;
	काष्ठा ivtv_stream *s_vbi;

	s->fh = शून्य;
	अगर ((s->type == IVTV_DEC_STREAM_TYPE_VBI || s->type == IVTV_ENC_STREAM_TYPE_VBI) &&
		test_bit(IVTV_F_S_INTERNAL_USE, &s->s_flags)) अणु
		/* this stream is still in use पूर्णांकernally */
		वापस;
	पूर्ण
	अगर (!test_and_clear_bit(IVTV_F_S_CLAIMED, &s->s_flags)) अणु
		IVTV_DEBUG_WARN("Release stream %s not in use!\n", s->name);
		वापस;
	पूर्ण

	ivtv_flush_queues(s);

	/* disable reinsertion पूर्णांकerrupt */
	अगर (s->type == IVTV_DEC_STREAM_TYPE_VBI)
		ivtv_set_irq_mask(itv, IVTV_IRQ_DEC_VBI_RE_INSERT);

	/* IVTV_DEC_STREAM_TYPE_MPG needs to release IVTV_DEC_STREAM_TYPE_VBI,
	   IVTV_ENC_STREAM_TYPE_MPG needs to release IVTV_ENC_STREAM_TYPE_VBI,
	   क्रम all other streams we're करोne */
	अगर (s->type == IVTV_DEC_STREAM_TYPE_MPG)
		s_vbi = &itv->streams[IVTV_DEC_STREAM_TYPE_VBI];
	अन्यथा अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG)
		s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
	अन्यथा
		वापस;

	/* clear पूर्णांकernal use flag */
	अगर (!test_and_clear_bit(IVTV_F_S_INTERNAL_USE, &s_vbi->s_flags)) अणु
		/* was alपढ़ोy cleared */
		वापस;
	पूर्ण
	अगर (s_vbi->fh) अणु
		/* VBI stream still claimed by a file descriptor */
		वापस;
	पूर्ण
	/* disable reinsertion पूर्णांकerrupt */
	अगर (s_vbi->type == IVTV_DEC_STREAM_TYPE_VBI)
		ivtv_set_irq_mask(itv, IVTV_IRQ_DEC_VBI_RE_INSERT);
	clear_bit(IVTV_F_S_CLAIMED, &s_vbi->s_flags);
	ivtv_flush_queues(s_vbi);
पूर्ण
EXPORT_SYMBOL(ivtv_release_stream);

अटल व्योम ivtv_dualwatch(काष्ठा ivtv *itv)
अणु
	काष्ठा v4l2_tuner vt;
	u32 new_stereo_mode;
	स्थिर u32 dual = 0x02;

	new_stereo_mode = v4l2_ctrl_g_ctrl(itv->cxhdl.audio_mode);
	स_रखो(&vt, 0, माप(vt));
	ivtv_call_all(itv, tuner, g_tuner, &vt);
	अगर (vt.audmode == V4L2_TUNER_MODE_LANG1_LANG2 && (vt.rxsubchans & V4L2_TUNER_SUB_LANG2))
		new_stereo_mode = dual;

	अगर (new_stereo_mode == itv->dualwatch_stereo_mode)
		वापस;

	IVTV_DEBUG_INFO("dualwatch: change stereo flag from 0x%x to 0x%x.\n",
			   itv->dualwatch_stereo_mode, new_stereo_mode);
	अगर (v4l2_ctrl_s_ctrl(itv->cxhdl.audio_mode, new_stereo_mode))
		IVTV_DEBUG_INFO("dualwatch: changing stereo flag failed\n");
पूर्ण

अटल व्योम ivtv_update_pgm_info(काष्ठा ivtv *itv)
अणु
	u32 wr_idx = (पढ़ो_enc(itv->pgm_info_offset) - itv->pgm_info_offset - 4) / 24;
	पूर्णांक cnt;
	पूर्णांक i = 0;

	अगर (wr_idx >= itv->pgm_info_num) अणु
		IVTV_DEBUG_WARN("Invalid PGM index %d (>= %d)\n", wr_idx, itv->pgm_info_num);
		वापस;
	पूर्ण
	cnt = (wr_idx + itv->pgm_info_num - itv->pgm_info_ग_लिखो_idx) % itv->pgm_info_num;
	जबतक (i < cnt) अणु
		पूर्णांक idx = (itv->pgm_info_ग_लिखो_idx + i) % itv->pgm_info_num;
		काष्ठा v4l2_enc_idx_entry *e = itv->pgm_info + idx;
		u32 addr = itv->pgm_info_offset + 4 + idx * 24;
		स्थिर पूर्णांक mapping[8] = अणु -1, V4L2_ENC_IDX_FRAME_I, V4L2_ENC_IDX_FRAME_P, -1,
			V4L2_ENC_IDX_FRAME_B, -1, -1, -1 पूर्ण;
					// 1=I, 2=P, 4=B

		e->offset = पढ़ो_enc(addr + 4) + ((u64)पढ़ो_enc(addr + 8) << 32);
		अगर (e->offset > itv->mpg_data_received) अणु
			अवरोध;
		पूर्ण
		e->offset += itv->vbi_data_inserted;
		e->length = पढ़ो_enc(addr);
		e->pts = पढ़ो_enc(addr + 16) + ((u64)(पढ़ो_enc(addr + 20) & 1) << 32);
		e->flags = mapping[पढ़ो_enc(addr + 12) & 7];
		i++;
	पूर्ण
	itv->pgm_info_ग_लिखो_idx = (itv->pgm_info_ग_लिखो_idx + i) % itv->pgm_info_num;
पूर्ण

अटल काष्ठा ivtv_buffer *ivtv_get_buffer(काष्ठा ivtv_stream *s, पूर्णांक non_block, पूर्णांक *err)
अणु
	काष्ठा ivtv *itv = s->itv;
	काष्ठा ivtv_stream *s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
	काष्ठा ivtv_buffer *buf;
	DEFINE_WAIT(रुको);

	*err = 0;
	जबतक (1) अणु
		अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG) अणु
			/* Process pending program info updates and pending VBI data */
			ivtv_update_pgm_info(itv);

			अगर (समय_after(jअगरfies,
				       itv->dualwatch_jअगरfies +
				       msecs_to_jअगरfies(1000))) अणु
				itv->dualwatch_jअगरfies = jअगरfies;
				ivtv_dualwatch(itv);
			पूर्ण

			अगर (test_bit(IVTV_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
			    !test_bit(IVTV_F_S_APPL_IO, &s_vbi->s_flags)) अणु
				जबतक ((buf = ivtv_dequeue(s_vbi, &s_vbi->q_full))) अणु
					/* byteswap and process VBI data */
					ivtv_process_vbi_data(itv, buf, s_vbi->dma_pts, s_vbi->type);
					ivtv_enqueue(s_vbi, buf, &s_vbi->q_मुक्त);
				पूर्ण
			पूर्ण
			buf = &itv->vbi.sliced_mpeg_buf;
			अगर (buf->पढ़ोpos != buf->bytesused) अणु
				वापस buf;
			पूर्ण
		पूर्ण

		/* करो we have leftover data? */
		buf = ivtv_dequeue(s, &s->q_io);
		अगर (buf)
			वापस buf;

		/* करो we have new data? */
		buf = ivtv_dequeue(s, &s->q_full);
		अगर (buf) अणु
			अगर ((buf->b_flags & IVTV_F_B_NEED_BUF_SWAP) == 0)
				वापस buf;
			buf->b_flags &= ~IVTV_F_B_NEED_BUF_SWAP;
			अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG)
				/* byteswap MPG data */
				ivtv_buf_swap(buf);
			अन्यथा अगर (s->type != IVTV_DEC_STREAM_TYPE_VBI) अणु
				/* byteswap and process VBI data */
				ivtv_process_vbi_data(itv, buf, s->dma_pts, s->type);
			पूर्ण
			वापस buf;
		पूर्ण

		/* वापस अगर end of stream */
		अगर (s->type != IVTV_DEC_STREAM_TYPE_VBI && !test_bit(IVTV_F_S_STREAMING, &s->s_flags)) अणु
			IVTV_DEBUG_INFO("EOS %s\n", s->name);
			वापस शून्य;
		पूर्ण

		/* वापस अगर file was खोलोed with O_NONBLOCK */
		अगर (non_block) अणु
			*err = -EAGAIN;
			वापस शून्य;
		पूर्ण

		/* रुको क्रम more data to arrive */
		mutex_unlock(&itv->serialize_lock);
		prepare_to_रुको(&s->रुकोq, &रुको, TASK_INTERRUPTIBLE);
		/* New buffers might have become available beक्रमe we were added to the रुकोqueue */
		अगर (!s->q_full.buffers)
			schedule();
		finish_रुको(&s->रुकोq, &रुको);
		mutex_lock(&itv->serialize_lock);
		अगर (संकेत_pending(current)) अणु
			/* वापस अगर a संकेत was received */
			IVTV_DEBUG_INFO("User stopped %s\n", s->name);
			*err = -EINTR;
			वापस शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ivtv_setup_sliced_vbi_buf(काष्ठा ivtv *itv)
अणु
	पूर्णांक idx = itv->vbi.inserted_frame % IVTV_VBI_FRAMES;

	itv->vbi.sliced_mpeg_buf.buf = itv->vbi.sliced_mpeg_data[idx];
	itv->vbi.sliced_mpeg_buf.bytesused = itv->vbi.sliced_mpeg_size[idx];
	itv->vbi.sliced_mpeg_buf.पढ़ोpos = 0;
पूर्ण

अटल माप_प्रकार ivtv_copy_buf_to_user(काष्ठा ivtv_stream *s, काष्ठा ivtv_buffer *buf,
		अक्षर __user *ubuf, माप_प्रकार ucount)
अणु
	काष्ठा ivtv *itv = s->itv;
	माप_प्रकार len = buf->bytesused - buf->पढ़ोpos;

	अगर (len > ucount) len = ucount;
	अगर (itv->vbi.insert_mpeg && s->type == IVTV_ENC_STREAM_TYPE_MPG &&
	    !ivtv_raw_vbi(itv) && buf != &itv->vbi.sliced_mpeg_buf) अणु
		स्थिर अक्षर *start = buf->buf + buf->पढ़ोpos;
		स्थिर अक्षर *p = start + 1;
		स्थिर u8 *q;
		u8 ch = itv->search_pack_header ? 0xba : 0xe0;
		पूर्णांक stuffing, i;

		जबतक (start + len > p && (q = स_प्रथम(p, 0, start + len - p))) अणु
			p = q + 1;
			अगर ((अक्षर *)q + 15 >= buf->buf + buf->bytesused ||
			    q[1] != 0 || q[2] != 1 || q[3] != ch) अणु
				जारी;
			पूर्ण
			अगर (!itv->search_pack_header) अणु
				अगर ((q[6] & 0xc0) != 0x80)
					जारी;
				अगर (((q[7] & 0xc0) == 0x80 && (q[9] & 0xf0) == 0x20) ||
				    ((q[7] & 0xc0) == 0xc0 && (q[9] & 0xf0) == 0x30)) अणु
					ch = 0xba;
					itv->search_pack_header = 1;
					p = q + 9;
				पूर्ण
				जारी;
			पूर्ण
			stuffing = q[13] & 7;
			/* all stuffing bytes must be 0xff */
			क्रम (i = 0; i < stuffing; i++)
				अगर (q[14 + i] != 0xff)
					अवरोध;
			अगर (i == stuffing && (q[4] & 0xc4) == 0x44 && (q[12] & 3) == 3 &&
					q[14 + stuffing] == 0 && q[15 + stuffing] == 0 &&
					q[16 + stuffing] == 1) अणु
				itv->search_pack_header = 0;
				len = (अक्षर *)q - start;
				ivtv_setup_sliced_vbi_buf(itv);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (copy_to_user(ubuf, (u8 *)buf->buf + buf->पढ़ोpos, len)) अणु
		IVTV_DEBUG_WARN("copy %zd bytes to user failed for %s\n", len, s->name);
		वापस -EFAULT;
	पूर्ण
	/*IVTV_INFO("copied %lld %d %d %d %d %d vbi %d\n", itv->mpg_data_received, len, ucount,
			buf->पढ़ोpos, buf->bytesused, buf->bytesused - buf->पढ़ोpos - len,
			buf == &itv->vbi.sliced_mpeg_buf); */
	buf->पढ़ोpos += len;
	अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG && buf != &itv->vbi.sliced_mpeg_buf)
		itv->mpg_data_received += len;
	वापस len;
पूर्ण

अटल sमाप_प्रकार ivtv_पढ़ो(काष्ठा ivtv_stream *s, अक्षर __user *ubuf, माप_प्रकार tot_count, पूर्णांक non_block)
अणु
	काष्ठा ivtv *itv = s->itv;
	माप_प्रकार tot_written = 0;
	पूर्णांक single_frame = 0;

	अगर (atomic_पढ़ो(&itv->capturing) == 0 && s->fh == शून्य) अणु
		/* shouldn't happen */
		IVTV_DEBUG_WARN("Stream %s not initialized before read\n", s->name);
		वापस -EIO;
	पूर्ण

	/* Each VBI buffer is one frame, the v4l2 API says that क्रम VBI the frames should
	   arrive one-by-one, so make sure we never output more than one VBI frame at a समय */
	अगर (s->type == IVTV_DEC_STREAM_TYPE_VBI ||
	    (s->type == IVTV_ENC_STREAM_TYPE_VBI && !ivtv_raw_vbi(itv)))
		single_frame = 1;

	क्रम (;;) अणु
		काष्ठा ivtv_buffer *buf;
		पूर्णांक rc;

		buf = ivtv_get_buffer(s, non_block, &rc);
		/* अगर there is no data available... */
		अगर (buf == शून्य) अणु
			/* अगर we got data, then वापस that regardless */
			अगर (tot_written)
				अवरोध;
			/* EOS condition */
			अगर (rc == 0) अणु
				clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);
				clear_bit(IVTV_F_S_APPL_IO, &s->s_flags);
				ivtv_release_stream(s);
			पूर्ण
			/* set त्रुटि_सं */
			वापस rc;
		पूर्ण
		rc = ivtv_copy_buf_to_user(s, buf, ubuf + tot_written, tot_count - tot_written);
		अगर (buf != &itv->vbi.sliced_mpeg_buf) अणु
			ivtv_enqueue(s, buf, (buf->पढ़ोpos == buf->bytesused) ? &s->q_मुक्त : &s->q_io);
		पूर्ण
		अन्यथा अगर (buf->पढ़ोpos == buf->bytesused) अणु
			पूर्णांक idx = itv->vbi.inserted_frame % IVTV_VBI_FRAMES;
			itv->vbi.sliced_mpeg_size[idx] = 0;
			itv->vbi.inserted_frame++;
			itv->vbi_data_inserted += buf->bytesused;
		पूर्ण
		अगर (rc < 0)
			वापस rc;
		tot_written += rc;

		अगर (tot_written == tot_count || single_frame)
			अवरोध;
	पूर्ण
	वापस tot_written;
पूर्ण

अटल sमाप_प्रकार ivtv_पढ़ो_pos(काष्ठा ivtv_stream *s, अक्षर __user *ubuf, माप_प्रकार count,
			loff_t *pos, पूर्णांक non_block)
अणु
	sमाप_प्रकार rc = count ? ivtv_पढ़ो(s, ubuf, count, non_block) : 0;
	काष्ठा ivtv *itv = s->itv;

	IVTV_DEBUG_HI_खाता("read %zd from %s, got %zd\n", count, s->name, rc);
	अगर (rc > 0)
		*pos += rc;
	वापस rc;
पूर्ण

पूर्णांक ivtv_start_capture(काष्ठा ivtv_खोलो_id *id)
अणु
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];
	काष्ठा ivtv_stream *s_vbi;

	अगर (s->type == IVTV_ENC_STREAM_TYPE_RAD ||
	    s->type == IVTV_DEC_STREAM_TYPE_MPG ||
	    s->type == IVTV_DEC_STREAM_TYPE_YUV ||
	    s->type == IVTV_DEC_STREAM_TYPE_VOUT) अणु
		/* you cannot पढ़ो from these stream types. */
		वापस -EINVAL;
	पूर्ण

	/* Try to claim this stream. */
	अगर (ivtv_claim_stream(id, s->type))
		वापस -EBUSY;

	/* This stream करोes not need to start capturing */
	अगर (s->type == IVTV_DEC_STREAM_TYPE_VBI) अणु
		set_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		वापस 0;
	पूर्ण

	/* If capture is alपढ़ोy in progress, then we also have to
	   करो nothing extra. */
	अगर (test_bit(IVTV_F_S_STREAMOFF, &s->s_flags) || test_and_set_bit(IVTV_F_S_STREAMING, &s->s_flags)) अणु
		set_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		वापस 0;
	पूर्ण

	/* Start VBI capture अगर required */
	s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
	अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG &&
	    test_bit(IVTV_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
	    !test_and_set_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags)) अणु
		/* Note: the IVTV_ENC_STREAM_TYPE_VBI is claimed
		   स्वतःmatically when the MPG stream is claimed.
		   We only need to start the VBI capturing. */
		अगर (ivtv_start_v4l2_encode_stream(s_vbi)) अणु
			IVTV_DEBUG_WARN("VBI capture start failed\n");

			/* Failure, clean up and वापस an error */
			clear_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags);
			clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
			/* also releases the associated VBI stream */
			ivtv_release_stream(s);
			वापस -EIO;
		पूर्ण
		IVTV_DEBUG_INFO("VBI insertion started\n");
	पूर्ण

	/* Tell the card to start capturing */
	अगर (!ivtv_start_v4l2_encode_stream(s)) अणु
		/* We're करोne */
		set_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		/* Resume a possibly छोड़ोd encoder */
		अगर (test_and_clear_bit(IVTV_F_I_ENC_PAUSED, &itv->i_flags))
			ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODER, 1, 1);
		वापस 0;
	पूर्ण

	/* failure, clean up */
	IVTV_DEBUG_WARN("Failed to start capturing for stream %s\n", s->name);

	/* Note: the IVTV_ENC_STREAM_TYPE_VBI is released
	   स्वतःmatically when the MPG stream is released.
	   We only need to stop the VBI capturing. */
	अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG &&
	    test_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags)) अणु
		ivtv_stop_v4l2_encode_stream(s_vbi, 0);
		clear_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags);
	पूर्ण
	clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
	ivtv_release_stream(s);
	वापस -EIO;
पूर्ण

sमाप_प्रकार ivtv_v4l2_पढ़ो(काष्ठा file * filp, अक्षर __user *buf, माप_प्रकार count, loff_t * pos)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(filp->निजी_data);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];
	sमाप_प्रकार rc;

	IVTV_DEBUG_HI_खाता("read %zd bytes from %s\n", count, s->name);

	अगर (mutex_lock_पूर्णांकerruptible(&itv->serialize_lock))
		वापस -ERESTARTSYS;
	rc = ivtv_start_capture(id);
	अगर (!rc)
		rc = ivtv_पढ़ो_pos(s, buf, count, pos, filp->f_flags & O_NONBLOCK);
	mutex_unlock(&itv->serialize_lock);
	वापस rc;
पूर्ण

पूर्णांक ivtv_start_decoding(काष्ठा ivtv_खोलो_id *id, पूर्णांक speed)
अणु
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];
	पूर्णांक rc;

	अगर (atomic_पढ़ो(&itv->decoding) == 0) अणु
		अगर (ivtv_claim_stream(id, s->type)) अणु
			/* someone अन्यथा is using this stream alपढ़ोy */
			IVTV_DEBUG_WARN("start decode, stream already claimed\n");
			वापस -EBUSY;
		पूर्ण
		rc = ivtv_start_v4l2_decode_stream(s, 0);
		अगर (rc < 0) अणु
			अगर (rc == -EAGAIN)
				rc = ivtv_start_v4l2_decode_stream(s, 0);
			अगर (rc < 0)
				वापस rc;
		पूर्ण
	पूर्ण
	अगर (s->type == IVTV_DEC_STREAM_TYPE_MPG)
		वापस ivtv_set_speed(itv, speed);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ivtv_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(filp->निजी_data);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	काष्ठा ivtv_buffer *buf;
	काष्ठा ivtv_queue q;
	पूर्णांक bytes_written = 0;
	पूर्णांक mode;
	पूर्णांक rc;
	DEFINE_WAIT(रुको);

	IVTV_DEBUG_HI_खाता("write %zd bytes to %s\n", count, s->name);

	अगर (s->type != IVTV_DEC_STREAM_TYPE_MPG &&
	    s->type != IVTV_DEC_STREAM_TYPE_YUV &&
	    s->type != IVTV_DEC_STREAM_TYPE_VOUT)
		/* not decoder streams */
		वापस -EINVAL;

	/* Try to claim this stream */
	अगर (ivtv_claim_stream(id, s->type))
		वापस -EBUSY;

	/* This stream करोes not need to start any decoding */
	अगर (s->type == IVTV_DEC_STREAM_TYPE_VOUT) अणु
		पूर्णांक elems = count / माप(काष्ठा v4l2_sliced_vbi_data);

		set_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		वापस ivtv_ग_लिखो_vbi_from_user(itv,
		   (स्थिर काष्ठा v4l2_sliced_vbi_data __user *)user_buf, elems);
	पूर्ण

	mode = s->type == IVTV_DEC_STREAM_TYPE_MPG ? OUT_MPG : OUT_YUV;

	अगर (ivtv_set_output_mode(itv, mode) != mode) अणु
	    ivtv_release_stream(s);
	    वापस -EBUSY;
	पूर्ण
	ivtv_queue_init(&q);
	set_bit(IVTV_F_S_APPL_IO, &s->s_flags);

	/* Start decoder (वापसs 0 अगर alपढ़ोy started) */
	rc = ivtv_start_decoding(id, itv->speed);
	अगर (rc) अणु
		IVTV_DEBUG_WARN("Failed start decode stream %s\n", s->name);

		/* failure, clean up */
		clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
		clear_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		वापस rc;
	पूर्ण

retry:
	/* If possible, just DMA the entire frame - Check the data transfer size
	since we may get here beक्रमe the stream has been fully set-up */
	अगर (mode == OUT_YUV && s->q_full.length == 0 && itv->dma_data_req_size) अणु
		जबतक (count >= itv->dma_data_req_size) अणु
			rc = ivtv_yuv_udma_stream_frame(itv, (व्योम __user *)user_buf);

			अगर (rc < 0)
				वापस rc;

			bytes_written += itv->dma_data_req_size;
			user_buf += itv->dma_data_req_size;
			count -= itv->dma_data_req_size;
		पूर्ण
		अगर (count == 0) अणु
			IVTV_DEBUG_HI_खाता("Wrote %d bytes to %s (%d)\n", bytes_written, s->name, s->q_full.bytesused);
			वापस bytes_written;
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		/* Gather buffers */
		जबतक (q.length - q.bytesused < count && (buf = ivtv_dequeue(s, &s->q_io)))
			ivtv_enqueue(s, buf, &q);
		जबतक (q.length - q.bytesused < count && (buf = ivtv_dequeue(s, &s->q_मुक्त))) अणु
			ivtv_enqueue(s, buf, &q);
		पूर्ण
		अगर (q.buffers)
			अवरोध;
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		mutex_unlock(&itv->serialize_lock);
		prepare_to_रुको(&s->रुकोq, &रुको, TASK_INTERRUPTIBLE);
		/* New buffers might have become मुक्त beक्रमe we were added to the रुकोqueue */
		अगर (!s->q_मुक्त.buffers)
			schedule();
		finish_रुको(&s->रुकोq, &रुको);
		mutex_lock(&itv->serialize_lock);
		अगर (संकेत_pending(current)) अणु
			IVTV_DEBUG_INFO("User stopped %s\n", s->name);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	/* copy user data पूर्णांकo buffers */
	जबतक ((buf = ivtv_dequeue(s, &q))) अणु
		/* yuv is a pain. Don't copy more data than needed क्रम a single
		   frame, otherwise we lose sync with the incoming stream */
		अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV &&
		    yi->stream_size + count > itv->dma_data_req_size)
			rc  = ivtv_buf_copy_from_user(s, buf, user_buf,
				itv->dma_data_req_size - yi->stream_size);
		अन्यथा
			rc = ivtv_buf_copy_from_user(s, buf, user_buf, count);

		/* Make sure we really got all the user data */
		अगर (rc < 0) अणु
			ivtv_queue_move(s, &q, शून्य, &s->q_मुक्त, 0);
			वापस rc;
		पूर्ण
		user_buf += rc;
		count -= rc;
		bytes_written += rc;

		अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV) अणु
			yi->stream_size += rc;
			/* If we have a complete yuv frame, अवरोध loop now */
			अगर (yi->stream_size == itv->dma_data_req_size) अणु
				ivtv_enqueue(s, buf, &s->q_full);
				yi->stream_size = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (buf->bytesused != s->buf_size) अणु
			/* incomplete, leave in q_io क्रम next समय */
			ivtv_enqueue(s, buf, &s->q_io);
			अवरोध;
		पूर्ण
		/* Byteswap MPEG buffer */
		अगर (s->type == IVTV_DEC_STREAM_TYPE_MPG)
			ivtv_buf_swap(buf);
		ivtv_enqueue(s, buf, &s->q_full);
	पूर्ण

	अगर (test_bit(IVTV_F_S_NEEDS_DATA, &s->s_flags)) अणु
		अगर (s->q_full.length >= itv->dma_data_req_size) अणु
			पूर्णांक got_sig;

			अगर (mode == OUT_YUV)
				ivtv_yuv_setup_stream_frame(itv);

			mutex_unlock(&itv->serialize_lock);
			prepare_to_रुको(&itv->dma_रुकोq, &रुको, TASK_INTERRUPTIBLE);
			जबतक (!(got_sig = संकेत_pending(current)) &&
					test_bit(IVTV_F_S_DMA_PENDING, &s->s_flags)) अणु
				schedule();
			पूर्ण
			finish_रुको(&itv->dma_रुकोq, &रुको);
			mutex_lock(&itv->serialize_lock);
			अगर (got_sig) अणु
				IVTV_DEBUG_INFO("User interrupted %s\n", s->name);
				वापस -EINTR;
			पूर्ण

			clear_bit(IVTV_F_S_NEEDS_DATA, &s->s_flags);
			ivtv_queue_move(s, &s->q_full, शून्य, &s->q_predma, itv->dma_data_req_size);
			ivtv_dma_stream_dec_prepare(s, itv->dma_data_req_offset + IVTV_DECODER_OFFSET, 1);
		पूर्ण
	पूर्ण
	/* more user data is available, रुको until buffers become मुक्त
	   to transfer the rest. */
	अगर (count && !(filp->f_flags & O_NONBLOCK))
		जाओ retry;
	IVTV_DEBUG_HI_खाता("Wrote %d bytes to %s (%d)\n", bytes_written, s->name, s->q_full.bytesused);
	वापस bytes_written;
पूर्ण

sमाप_प्रकार ivtv_v4l2_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(filp->निजी_data);
	काष्ठा ivtv *itv = id->itv;
	sमाप_प्रकार res;

	अगर (mutex_lock_पूर्णांकerruptible(&itv->serialize_lock))
		वापस -ERESTARTSYS;
	res = ivtv_ग_लिखो(filp, user_buf, count, pos);
	mutex_unlock(&itv->serialize_lock);
	वापस res;
पूर्ण

__poll_t ivtv_v4l2_dec_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(filp->निजी_data);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];
	__poll_t res = 0;

	/* add stream's रुकोq to the poll list */
	IVTV_DEBUG_HI_खाता("Decoder poll\n");

	/* If there are subscribed events, then only use the new event
	   API instead of the old video.h based API. */
	अगर (!list_empty(&id->fh.subscribed)) अणु
		poll_रुको(filp, &id->fh.रुको, रुको);
		/* Turn off the old-style vsync events */
		clear_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags);
		अगर (v4l2_event_pending(&id->fh))
			res = EPOLLPRI;
	पूर्ण अन्यथा अणु
		/* This is the old-style API which is here only क्रम backwards
		   compatibility. */
		poll_रुको(filp, &s->रुकोq, रुको);
		set_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags);
		अगर (test_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags) ||
		    test_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags))
			res = EPOLLPRI;
	पूर्ण

	/* Allow ग_लिखो अगर buffers are available क्रम writing */
	अगर (s->q_मुक्त.buffers)
		res |= EPOLLOUT | EPOLLWRNORM;
	वापस res;
पूर्ण

__poll_t ivtv_v4l2_enc_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा ivtv_खोलो_id *id = fh2id(filp->निजी_data);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];
	पूर्णांक eof = test_bit(IVTV_F_S_STREAMOFF, &s->s_flags);
	__poll_t res = 0;

	/* Start a capture अगर there is none */
	अगर (!eof && !test_bit(IVTV_F_S_STREAMING, &s->s_flags) &&
			s->type != IVTV_ENC_STREAM_TYPE_RAD &&
			(req_events & (EPOLLIN | EPOLLRDNORM))) अणु
		पूर्णांक rc;

		mutex_lock(&itv->serialize_lock);
		rc = ivtv_start_capture(id);
		mutex_unlock(&itv->serialize_lock);
		अगर (rc) अणु
			IVTV_DEBUG_INFO("Could not start capture for %s (%d)\n",
					s->name, rc);
			वापस EPOLLERR;
		पूर्ण
		IVTV_DEBUG_खाता("Encoder poll started capture\n");
	पूर्ण

	/* add stream's रुकोq to the poll list */
	IVTV_DEBUG_HI_खाता("Encoder poll\n");
	poll_रुको(filp, &s->रुकोq, रुको);
	अगर (v4l2_event_pending(&id->fh))
		res |= EPOLLPRI;
	अन्यथा
		poll_रुको(filp, &id->fh.रुको, रुको);

	अगर (s->q_full.length || s->q_io.length)
		वापस res | EPOLLIN | EPOLLRDNORM;
	अगर (eof)
		वापस res | EPOLLHUP;
	वापस res;
पूर्ण

व्योम ivtv_stop_capture(काष्ठा ivtv_खोलो_id *id, पूर्णांक gop_end)
अणु
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];

	IVTV_DEBUG_खाता("close() of %s\n", s->name);

	/* 'Unclaim' this stream */

	/* Stop capturing */
	अगर (test_bit(IVTV_F_S_STREAMING, &s->s_flags)) अणु
		काष्ठा ivtv_stream *s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];

		IVTV_DEBUG_INFO("close stopping capture\n");
		/* Special हाल: a running VBI capture क्रम VBI insertion
		   in the mpeg stream. Need to stop that too. */
		अगर (id->type == IVTV_ENC_STREAM_TYPE_MPG &&
		    test_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags) &&
		    !test_bit(IVTV_F_S_APPL_IO, &s_vbi->s_flags)) अणु
			IVTV_DEBUG_INFO("close stopping embedded VBI capture\n");
			ivtv_stop_v4l2_encode_stream(s_vbi, 0);
		पूर्ण
		अगर ((id->type == IVTV_DEC_STREAM_TYPE_VBI ||
		     id->type == IVTV_ENC_STREAM_TYPE_VBI) &&
		    test_bit(IVTV_F_S_INTERNAL_USE, &s->s_flags)) अणु
			/* Also used पूर्णांकernally, करोn't stop capturing */
			s->fh = शून्य;
		पूर्ण
		अन्यथा अणु
			ivtv_stop_v4l2_encode_stream(s, gop_end);
		पूर्ण
	पूर्ण
	अगर (!gop_end) अणु
		clear_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);
		ivtv_release_stream(s);
	पूर्ण
पूर्ण

अटल व्योम ivtv_stop_decoding(काष्ठा ivtv_खोलो_id *id, पूर्णांक flags, u64 pts)
अणु
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];

	IVTV_DEBUG_खाता("close() of %s\n", s->name);

	अगर (id->type == IVTV_DEC_STREAM_TYPE_YUV &&
		test_bit(IVTV_F_I_DECODING_YUV, &itv->i_flags)) अणु
		/* Restore रेजिस्टरs we've changed & clean up any mess */
		ivtv_yuv_बंद(itv);
	पूर्ण

	/* Stop decoding */
	अगर (test_bit(IVTV_F_S_STREAMING, &s->s_flags)) अणु
		IVTV_DEBUG_INFO("close stopping decode\n");

		ivtv_stop_v4l2_decode_stream(s, flags, pts);
		itv->output_mode = OUT_NONE;
	पूर्ण
	clear_bit(IVTV_F_S_APPL_IO, &s->s_flags);
	clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);

	अगर (itv->output_mode == OUT_UDMA_YUV && id->yuv_frames)
		itv->output_mode = OUT_NONE;

	itv->speed = 0;
	clear_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags);
	ivtv_release_stream(s);
पूर्ण

पूर्णांक ivtv_v4l2_बंद(काष्ठा file *filp)
अणु
	काष्ठा v4l2_fh *fh = filp->निजी_data;
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];

	IVTV_DEBUG_खाता("close %s\n", s->name);

	mutex_lock(&itv->serialize_lock);

	/* Stop radio */
	अगर (id->type == IVTV_ENC_STREAM_TYPE_RAD &&
			v4l2_fh_is_singular_file(filp)) अणु
		/* Closing radio device, वापस to TV mode */
		ivtv_mute(itv);
		/* Mark that the radio is no दीर्घer in use */
		clear_bit(IVTV_F_I_RADIO_USER, &itv->i_flags);
		/* Switch tuner to TV */
		ivtv_call_all(itv, video, s_std, itv->std);
		/* Select correct audio input (i.e. TV tuner or Line in) */
		ivtv_audio_set_io(itv);
		अगर (itv->hw_flags & IVTV_HW_SAA711X) अणु
			ivtv_call_hw(itv, IVTV_HW_SAA711X, video, s_crystal_freq,
					SAA7115_FREQ_32_11_MHZ, 0);
		पूर्ण
		अगर (atomic_पढ़ो(&itv->capturing) > 0) अणु
			/* Unकरो video mute */
			ivtv_vapi(itv, CX2341X_ENC_MUTE_VIDEO, 1,
					v4l2_ctrl_g_ctrl(itv->cxhdl.video_mute) |
					(v4l2_ctrl_g_ctrl(itv->cxhdl.video_mute_yuv) << 8));
		पूर्ण
		/* Done! Unmute and जारी. */
		ivtv_unmute(itv);
	पूर्ण

	v4l2_fh_del(fh);
	v4l2_fh_निकास(fh);

	/* Easy हाल first: this stream was never claimed by us */
	अगर (s->fh != &id->fh)
		जाओ बंद_करोne;

	/* 'Unclaim' this stream */

	अगर (s->type >= IVTV_DEC_STREAM_TYPE_MPG) अणु
		काष्ठा ivtv_stream *s_vout = &itv->streams[IVTV_DEC_STREAM_TYPE_VOUT];

		ivtv_stop_decoding(id, V4L2_DEC_CMD_STOP_TO_BLACK | V4L2_DEC_CMD_STOP_IMMEDIATELY, 0);

		/* If all output streams are बंदd, and अगर the user करोesn't have
		   IVTV_DEC_STREAM_TYPE_VOUT खोलो, then disable CC on TV-out. */
		अगर (itv->output_mode == OUT_NONE && !test_bit(IVTV_F_S_APPL_IO, &s_vout->s_flags)) अणु
			/* disable CC on TV-out */
			ivtv_disable_cc(itv);
		पूर्ण
	पूर्ण अन्यथा अणु
		ivtv_stop_capture(id, 0);
	पूर्ण
बंद_करोne:
	kमुक्त(id);
	mutex_unlock(&itv->serialize_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_खोलो(काष्ठा file *filp)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	काष्ठा ivtv_stream *s = video_get_drvdata(vdev);
	काष्ठा ivtv *itv = s->itv;
	काष्ठा ivtv_खोलो_id *item;
	पूर्णांक res = 0;

	IVTV_DEBUG_खाता("open %s\n", s->name);

	अगर (ivtv_init_on_first_खोलो(itv)) अणु
		IVTV_ERR("Failed to initialize on device %s\n",
			 video_device_node_name(vdev));
		वापस -ENXIO;
	पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	/* Unless ivtv_fw_debug is set, error out अगर firmware dead. */
	अगर (ivtv_fw_debug) अणु
		IVTV_WARN("Opening %s with dead firmware lockout disabled\n",
			  video_device_node_name(vdev));
		IVTV_WARN("Selected firmware errors will be ignored\n");
	पूर्ण अन्यथा अणु
#अन्यथा
	अगर (1) अणु
#पूर्ण_अगर
		res = ivtv_firmware_check(itv, "ivtv_serialized_open");
		अगर (res == -EAGAIN)
			res = ivtv_firmware_check(itv, "ivtv_serialized_open");
		अगर (res < 0)
			वापस -EIO;
	पूर्ण

	अगर (s->type == IVTV_DEC_STREAM_TYPE_MPG &&
		test_bit(IVTV_F_S_CLAIMED, &itv->streams[IVTV_DEC_STREAM_TYPE_YUV].s_flags))
		वापस -EBUSY;

	अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV &&
		test_bit(IVTV_F_S_CLAIMED, &itv->streams[IVTV_DEC_STREAM_TYPE_MPG].s_flags))
		वापस -EBUSY;

	अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV) अणु
		अगर (पढ़ो_reg(0x82c) == 0) अणु
			IVTV_ERR("Tried to open YUV output device but need to send data to mpeg decoder before it can be used\n");
			/* वापस -ENODEV; */
		पूर्ण
		ivtv_udma_alloc(itv);
	पूर्ण

	/* Allocate memory */
	item = kzalloc(माप(काष्ठा ivtv_खोलो_id), GFP_KERNEL);
	अगर (शून्य == item) अणु
		IVTV_DEBUG_WARN("nomem on v4l2 open\n");
		वापस -ENOMEM;
	पूर्ण
	v4l2_fh_init(&item->fh, &s->vdev);
	item->itv = itv;
	item->type = s->type;

	filp->निजी_data = &item->fh;
	v4l2_fh_add(&item->fh);

	अगर (item->type == IVTV_ENC_STREAM_TYPE_RAD &&
			v4l2_fh_is_singular_file(filp)) अणु
		अगर (!test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags)) अणु
			अगर (atomic_पढ़ो(&itv->capturing) > 0) अणु
				/* चयनing to radio जबतक capture is
				   in progress is not polite */
				v4l2_fh_del(&item->fh);
				v4l2_fh_निकास(&item->fh);
				kमुक्त(item);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
		/* Mark that the radio is being used. */
		set_bit(IVTV_F_I_RADIO_USER, &itv->i_flags);
		/* We have the radio */
		ivtv_mute(itv);
		/* Switch tuner to radio */
		ivtv_call_all(itv, tuner, s_radio);
		/* Select the correct audio input (i.e. radio tuner) */
		ivtv_audio_set_io(itv);
		अगर (itv->hw_flags & IVTV_HW_SAA711X) अणु
			ivtv_call_hw(itv, IVTV_HW_SAA711X, video, s_crystal_freq,
				SAA7115_FREQ_32_11_MHZ, SAA7115_FREQ_FL_APLL);
		पूर्ण
		/* Done! Unmute and जारी. */
		ivtv_unmute(itv);
	पूर्ण

	/* YUV or MPG Decoding Mode? */
	अगर (s->type == IVTV_DEC_STREAM_TYPE_MPG) अणु
		clear_bit(IVTV_F_I_DEC_YUV, &itv->i_flags);
	पूर्ण अन्यथा अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV) अणु
		set_bit(IVTV_F_I_DEC_YUV, &itv->i_flags);
		/* For yuv, we need to know the dma size beक्रमe we start */
		itv->dma_data_req_size =
				1080 * ((itv->yuv_info.v4l2_src_h + 31) & ~31);
		itv->yuv_info.stream_size = 0;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ivtv_v4l2_खोलो(काष्ठा file *filp)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	पूर्णांक res;

	अगर (mutex_lock_पूर्णांकerruptible(vdev->lock))
		वापस -ERESTARTSYS;
	res = ivtv_खोलो(filp);
	mutex_unlock(vdev->lock);
	वापस res;
पूर्ण

व्योम ivtv_mute(काष्ठा ivtv *itv)
अणु
	अगर (atomic_पढ़ो(&itv->capturing))
		ivtv_vapi(itv, CX2341X_ENC_MUTE_AUDIO, 1, 1);
	IVTV_DEBUG_INFO("Mute\n");
पूर्ण

व्योम ivtv_unmute(काष्ठा ivtv *itv)
अणु
	अगर (atomic_पढ़ो(&itv->capturing)) अणु
		ivtv_msleep_समयout(100, 0);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 1, 12);
		ivtv_vapi(itv, CX2341X_ENC_MUTE_AUDIO, 1, 0);
	पूर्ण
	IVTV_DEBUG_INFO("Unmute\n");
पूर्ण
