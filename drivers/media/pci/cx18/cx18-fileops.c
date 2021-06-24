<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 file operation functions
 *
 *  Derived from ivtv-fileops.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-fileops.h"
#समावेश "cx18-i2c.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-vbi.h"
#समावेश "cx18-audio.h"
#समावेश "cx18-mailbox.h"
#समावेश "cx18-scb.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-controls.h"
#समावेश "cx18-ioctl.h"
#समावेश "cx18-cards.h"
#समावेश <media/v4l2-event.h>

/* This function tries to claim the stream क्रम a specअगरic file descriptor.
   If no one अन्यथा is using this stream then the stream is claimed and
   associated VBI and IDX streams are also स्वतःmatically claimed.
   Possible error वापसs: -EBUSY अगर someone अन्यथा has claimed
   the stream or 0 on success. */
पूर्णांक cx18_claim_stream(काष्ठा cx18_खोलो_id *id, पूर्णांक type)
अणु
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[type];
	काष्ठा cx18_stream *s_assoc;

	/* Nothing should ever try to directly claim the IDX stream */
	अगर (type == CX18_ENC_STREAM_TYPE_IDX) अणु
		CX18_WARN("MPEG Index stream cannot be claimed directly, but something tried.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (test_and_set_bit(CX18_F_S_CLAIMED, &s->s_flags)) अणु
		/* someone alपढ़ोy claimed this stream */
		अगर (s->id == id->खोलो_id) अणु
			/* yes, this file descriptor did. So that's OK. */
			वापस 0;
		पूर्ण
		अगर (s->id == -1 && type == CX18_ENC_STREAM_TYPE_VBI) अणु
			/* VBI is handled alपढ़ोy पूर्णांकernally, now also assign
			   the file descriptor to this stream क्रम बाह्यal
			   पढ़ोing of the stream. */
			s->id = id->खोलो_id;
			CX18_DEBUG_INFO("Start Read VBI\n");
			वापस 0;
		पूर्ण
		/* someone अन्यथा is using this stream alपढ़ोy */
		CX18_DEBUG_INFO("Stream %d is busy\n", type);
		वापस -EBUSY;
	पूर्ण
	s->id = id->खोलो_id;

	/*
	 * CX18_ENC_STREAM_TYPE_MPG needs to claim:
	 * CX18_ENC_STREAM_TYPE_VBI, अगर VBI insertion is on क्रम sliced VBI, or
	 * CX18_ENC_STREAM_TYPE_IDX, अगर VBI insertion is off क्रम sliced VBI
	 * (We करोn't yet fix up MPEG Index entries क्रम our inserted packets).
	 *
	 * For all other streams we're करोne.
	 */
	अगर (type != CX18_ENC_STREAM_TYPE_MPG)
		वापस 0;

	s_assoc = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	अगर (cx->vbi.insert_mpeg && !cx18_raw_vbi(cx))
		s_assoc = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	अन्यथा अगर (!cx18_stream_enabled(s_assoc))
		वापस 0;

	set_bit(CX18_F_S_CLAIMED, &s_assoc->s_flags);

	/* mark that it is used पूर्णांकernally */
	set_bit(CX18_F_S_INTERNAL_USE, &s_assoc->s_flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx18_claim_stream);

/* This function releases a previously claimed stream. It will take पूर्णांकo
   account associated VBI streams. */
व्योम cx18_release_stream(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18 *cx = s->cx;
	काष्ठा cx18_stream *s_assoc;

	s->id = -1;
	अगर (s->type == CX18_ENC_STREAM_TYPE_IDX) अणु
		/*
		 * The IDX stream is only used पूर्णांकernally, and can
		 * only be indirectly unclaimed by unclaiming the MPG stream.
		 */
		वापस;
	पूर्ण

	अगर (s->type == CX18_ENC_STREAM_TYPE_VBI &&
		test_bit(CX18_F_S_INTERNAL_USE, &s->s_flags)) अणु
		/* this stream is still in use पूर्णांकernally */
		वापस;
	पूर्ण
	अगर (!test_and_clear_bit(CX18_F_S_CLAIMED, &s->s_flags)) अणु
		CX18_DEBUG_WARN("Release stream %s not in use!\n", s->name);
		वापस;
	पूर्ण

	cx18_flush_queues(s);

	/*
	 * CX18_ENC_STREAM_TYPE_MPG needs to release the
	 * CX18_ENC_STREAM_TYPE_VBI and/or CX18_ENC_STREAM_TYPE_IDX streams.
	 *
	 * For all other streams we're करोne.
	 */
	अगर (s->type != CX18_ENC_STREAM_TYPE_MPG)
		वापस;

	/* Unclaim the associated MPEG Index stream */
	s_assoc = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	अगर (test_and_clear_bit(CX18_F_S_INTERNAL_USE, &s_assoc->s_flags)) अणु
		clear_bit(CX18_F_S_CLAIMED, &s_assoc->s_flags);
		cx18_flush_queues(s_assoc);
	पूर्ण

	/* Unclaim the associated VBI stream */
	s_assoc = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	अगर (test_and_clear_bit(CX18_F_S_INTERNAL_USE, &s_assoc->s_flags)) अणु
		अगर (s_assoc->id == -1) अणु
			/*
			 * The VBI stream is not still claimed by a file
			 * descriptor, so completely unclaim it.
			 */
			clear_bit(CX18_F_S_CLAIMED, &s_assoc->s_flags);
			cx18_flush_queues(s_assoc);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cx18_release_stream);

अटल व्योम cx18_dualwatch(काष्ठा cx18 *cx)
अणु
	काष्ठा v4l2_tuner vt;
	u32 new_stereo_mode;
	स्थिर u32 dual = 0x0200;

	new_stereo_mode = v4l2_ctrl_g_ctrl(cx->cxhdl.audio_mode);
	स_रखो(&vt, 0, माप(vt));
	cx18_call_all(cx, tuner, g_tuner, &vt);
	अगर (vt.audmode == V4L2_TUNER_MODE_LANG1_LANG2 &&
			(vt.rxsubchans & V4L2_TUNER_SUB_LANG2))
		new_stereo_mode = dual;

	अगर (new_stereo_mode == cx->dualwatch_stereo_mode)
		वापस;

	CX18_DEBUG_INFO("dualwatch: change stereo flag from 0x%x to 0x%x.\n",
			   cx->dualwatch_stereo_mode, new_stereo_mode);
	अगर (v4l2_ctrl_s_ctrl(cx->cxhdl.audio_mode, new_stereo_mode))
		CX18_DEBUG_INFO("dualwatch: changing stereo flag failed\n");
पूर्ण


अटल काष्ठा cx18_mdl *cx18_get_mdl(काष्ठा cx18_stream *s, पूर्णांक non_block,
				     पूर्णांक *err)
अणु
	काष्ठा cx18 *cx = s->cx;
	काष्ठा cx18_stream *s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	काष्ठा cx18_mdl *mdl;
	DEFINE_WAIT(रुको);

	*err = 0;
	जबतक (1) अणु
		अगर (s->type == CX18_ENC_STREAM_TYPE_MPG) अणु
			/* Process pending program updates and VBI data */
			अगर (समय_after(jअगरfies, cx->dualwatch_jअगरfies + msecs_to_jअगरfies(1000))) अणु
				cx->dualwatch_jअगरfies = jअगरfies;
				cx18_dualwatch(cx);
			पूर्ण
			अगर (test_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
			    !test_bit(CX18_F_S_APPL_IO, &s_vbi->s_flags)) अणु
				जबतक ((mdl = cx18_dequeue(s_vbi,
							   &s_vbi->q_full))) अणु
					/* byteswap and process VBI data */
					cx18_process_vbi_data(cx, mdl,
							      s_vbi->type);
					cx18_stream_put_mdl_fw(s_vbi, mdl);
				पूर्ण
			पूर्ण
			mdl = &cx->vbi.sliced_mpeg_mdl;
			अगर (mdl->पढ़ोpos != mdl->bytesused)
				वापस mdl;
		पूर्ण

		/* करो we have new data? */
		mdl = cx18_dequeue(s, &s->q_full);
		अगर (mdl) अणु
			अगर (!test_and_clear_bit(CX18_F_M_NEED_SWAP,
						&mdl->m_flags))
				वापस mdl;
			अगर (s->type == CX18_ENC_STREAM_TYPE_MPG)
				/* byteswap MPG data */
				cx18_mdl_swap(mdl);
			अन्यथा अणु
				/* byteswap and process VBI data */
				cx18_process_vbi_data(cx, mdl, s->type);
			पूर्ण
			वापस mdl;
		पूर्ण

		/* वापस अगर end of stream */
		अगर (!test_bit(CX18_F_S_STREAMING, &s->s_flags)) अणु
			CX18_DEBUG_INFO("EOS %s\n", s->name);
			वापस शून्य;
		पूर्ण

		/* वापस अगर file was खोलोed with O_NONBLOCK */
		अगर (non_block) अणु
			*err = -EAGAIN;
			वापस शून्य;
		पूर्ण

		/* रुको क्रम more data to arrive */
		prepare_to_रुको(&s->रुकोq, &रुको, TASK_INTERRUPTIBLE);
		/* New buffers might have become available beक्रमe we were added
		   to the रुकोqueue */
		अगर (!atomic_पढ़ो(&s->q_full.depth))
			schedule();
		finish_रुको(&s->रुकोq, &रुको);
		अगर (संकेत_pending(current)) अणु
			/* वापस अगर a संकेत was received */
			CX18_DEBUG_INFO("User stopped %s\n", s->name);
			*err = -EINTR;
			वापस शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cx18_setup_sliced_vbi_mdl(काष्ठा cx18 *cx)
अणु
	काष्ठा cx18_mdl *mdl = &cx->vbi.sliced_mpeg_mdl;
	काष्ठा cx18_buffer *buf = &cx->vbi.sliced_mpeg_buf;
	पूर्णांक idx = cx->vbi.inserted_frame % CX18_VBI_FRAMES;

	buf->buf = cx->vbi.sliced_mpeg_data[idx];
	buf->bytesused = cx->vbi.sliced_mpeg_size[idx];
	buf->पढ़ोpos = 0;

	mdl->curr_buf = शून्य;
	mdl->bytesused = cx->vbi.sliced_mpeg_size[idx];
	mdl->पढ़ोpos = 0;
पूर्ण

अटल माप_प्रकार cx18_copy_buf_to_user(काष्ठा cx18_stream *s,
	काष्ठा cx18_buffer *buf, अक्षर __user *ubuf, माप_प्रकार ucount, bool *stop)
अणु
	काष्ठा cx18 *cx = s->cx;
	माप_प्रकार len = buf->bytesused - buf->पढ़ोpos;

	*stop = false;
	अगर (len > ucount)
		len = ucount;
	अगर (cx->vbi.insert_mpeg && s->type == CX18_ENC_STREAM_TYPE_MPG &&
	    !cx18_raw_vbi(cx) && buf != &cx->vbi.sliced_mpeg_buf) अणु
		/*
		 * Try to find a good splice poपूर्णांक in the PS, just beक्रमe
		 * an MPEG-2 Program Pack start code, and provide only
		 * up to that poपूर्णांक to the user, so it's easy to insert VBI data
		 * the next समय around.
		 *
		 * This will not work क्रम an MPEG-2 TS and has only been
		 * verअगरied by analysis to work क्रम an MPEG-2 PS.  Helen Buus
		 * poपूर्णांकed out this works क्रम the CX23416 MPEG-2 DVD compatible
		 * stream, and research indicates both the MPEG 2 SVCD and DVD
		 * stream types use an MPEG-2 PS container.
		 */
		/*
		 * An MPEG-2 Program Stream (PS) is a series of
		 * MPEG-2 Program Packs terminated by an
		 * MPEG Program End Code after the last Program Pack.
		 * A Program Pack may hold a PS System Header packet and any
		 * number of Program Elementary Stream (PES) Packets
		 */
		स्थिर अक्षर *start = buf->buf + buf->पढ़ोpos;
		स्थिर अक्षर *p = start + 1;
		स्थिर u8 *q;
		u8 ch = cx->search_pack_header ? 0xba : 0xe0;
		पूर्णांक stuffing, i;

		जबतक (start + len > p) अणु
			/* Scan क्रम a 0 to find a potential MPEG-2 start code */
			q = स_प्रथम(p, 0, start + len - p);
			अगर (q == शून्य)
				अवरोध;
			p = q + 1;
			/*
			 * Keep looking अगर not a
			 * MPEG-2 Pack header start code:  0x00 0x00 0x01 0xba
			 * or MPEG-2 video PES start code: 0x00 0x00 0x01 0xe0
			 */
			अगर ((अक्षर *)q + 15 >= buf->buf + buf->bytesused ||
			    q[1] != 0 || q[2] != 1 || q[3] != ch)
				जारी;

			/* If expecting the primary video PES */
			अगर (!cx->search_pack_header) अणु
				/* Continue अगर it couldn't be a PES packet */
				अगर ((q[6] & 0xc0) != 0x80)
					जारी;
				/* Check अगर a PTS or PTS & DTS follow */
				अगर (((q[7] & 0xc0) == 0x80 &&  /* PTS only */
				     (q[9] & 0xf0) == 0x20) || /* PTS only */
				    ((q[7] & 0xc0) == 0xc0 &&  /* PTS & DTS */
				     (q[9] & 0xf0) == 0x30)) अणु /* DTS follows */
					/* Assume we found the video PES hdr */
					ch = 0xba; /* next want a Program Pack*/
					cx->search_pack_header = 1;
					p = q + 9; /* Skip this video PES hdr */
				पूर्ण
				जारी;
			पूर्ण

			/* We may have found a Program Pack start code */

			/* Get the count of stuffing bytes & verअगरy them */
			stuffing = q[13] & 7;
			/* all stuffing bytes must be 0xff */
			क्रम (i = 0; i < stuffing; i++)
				अगर (q[14 + i] != 0xff)
					अवरोध;
			अगर (i == stuffing && /* right number of stuffing bytes*/
			    (q[4] & 0xc4) == 0x44 && /* marker check */
			    (q[12] & 3) == 3 &&  /* marker check */
			    q[14 + stuffing] == 0 && /* PES Pack or Sys Hdr */
			    q[15 + stuffing] == 0 &&
			    q[16 + stuffing] == 1) अणु
				/* We declare we actually found a Program Pack*/
				cx->search_pack_header = 0; /* expect vid PES */
				len = (अक्षर *)q - start;
				cx18_setup_sliced_vbi_mdl(cx);
				*stop = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (copy_to_user(ubuf, (u8 *)buf->buf + buf->पढ़ोpos, len)) अणु
		CX18_DEBUG_WARN("copy %zd bytes to user failed for %s\n",
				len, s->name);
		वापस -EFAULT;
	पूर्ण
	buf->पढ़ोpos += len;
	अगर (s->type == CX18_ENC_STREAM_TYPE_MPG &&
	    buf != &cx->vbi.sliced_mpeg_buf)
		cx->mpg_data_received += len;
	वापस len;
पूर्ण

अटल माप_प्रकार cx18_copy_mdl_to_user(काष्ठा cx18_stream *s,
		काष्ठा cx18_mdl *mdl, अक्षर __user *ubuf, माप_प्रकार ucount)
अणु
	माप_प्रकार tot_written = 0;
	पूर्णांक rc;
	bool stop = false;

	अगर (mdl->curr_buf == शून्य)
		mdl->curr_buf = list_first_entry(&mdl->buf_list,
						 काष्ठा cx18_buffer, list);

	अगर (list_entry_is_past_end(mdl->curr_buf, &mdl->buf_list, list)) अणु
		/*
		 * For some reason we've exhausted the buffers, but the MDL
		 * object still said some data was unपढ़ो.
		 * Fix that and bail out.
		 */
		mdl->पढ़ोpos = mdl->bytesused;
		वापस 0;
	पूर्ण

	list_क्रम_each_entry_from(mdl->curr_buf, &mdl->buf_list, list) अणु

		अगर (mdl->curr_buf->पढ़ोpos >= mdl->curr_buf->bytesused)
			जारी;

		rc = cx18_copy_buf_to_user(s, mdl->curr_buf, ubuf + tot_written,
					   ucount - tot_written, &stop);
		अगर (rc < 0)
			वापस rc;
		mdl->पढ़ोpos += rc;
		tot_written += rc;

		अगर (stop ||	/* Forced stopping poपूर्णांक क्रम VBI insertion */
		    tot_written >= ucount ||	/* Reader request satisfied */
		    mdl->curr_buf->पढ़ोpos < mdl->curr_buf->bytesused ||
		    mdl->पढ़ोpos >= mdl->bytesused) /* MDL buffers drained */
			अवरोध;
	पूर्ण
	वापस tot_written;
पूर्ण

अटल sमाप_प्रकार cx18_पढ़ो(काष्ठा cx18_stream *s, अक्षर __user *ubuf,
		माप_प्रकार tot_count, पूर्णांक non_block)
अणु
	काष्ठा cx18 *cx = s->cx;
	माप_प्रकार tot_written = 0;
	पूर्णांक single_frame = 0;

	अगर (atomic_पढ़ो(&cx->ana_capturing) == 0 && s->id == -1) अणु
		/* shouldn't happen */
		CX18_DEBUG_WARN("Stream %s not initialized before read\n",
				s->name);
		वापस -EIO;
	पूर्ण

	/* Each VBI buffer is one frame, the v4l2 API says that क्रम VBI the
	   frames should arrive one-by-one, so make sure we never output more
	   than one VBI frame at a समय */
	अगर (s->type == CX18_ENC_STREAM_TYPE_VBI && !cx18_raw_vbi(cx))
		single_frame = 1;

	क्रम (;;) अणु
		काष्ठा cx18_mdl *mdl;
		पूर्णांक rc;

		mdl = cx18_get_mdl(s, non_block, &rc);
		/* अगर there is no data available... */
		अगर (mdl == शून्य) अणु
			/* अगर we got data, then वापस that regardless */
			अगर (tot_written)
				अवरोध;
			/* EOS condition */
			अगर (rc == 0) अणु
				clear_bit(CX18_F_S_STREAMOFF, &s->s_flags);
				clear_bit(CX18_F_S_APPL_IO, &s->s_flags);
				cx18_release_stream(s);
			पूर्ण
			/* set त्रुटि_सं */
			वापस rc;
		पूर्ण

		rc = cx18_copy_mdl_to_user(s, mdl, ubuf + tot_written,
				tot_count - tot_written);

		अगर (mdl != &cx->vbi.sliced_mpeg_mdl) अणु
			अगर (mdl->पढ़ोpos == mdl->bytesused)
				cx18_stream_put_mdl_fw(s, mdl);
			अन्यथा
				cx18_push(s, mdl, &s->q_full);
		पूर्ण अन्यथा अगर (mdl->पढ़ोpos == mdl->bytesused) अणु
			पूर्णांक idx = cx->vbi.inserted_frame % CX18_VBI_FRAMES;

			cx->vbi.sliced_mpeg_size[idx] = 0;
			cx->vbi.inserted_frame++;
			cx->vbi_data_inserted += mdl->bytesused;
		पूर्ण
		अगर (rc < 0)
			वापस rc;
		tot_written += rc;

		अगर (tot_written == tot_count || single_frame)
			अवरोध;
	पूर्ण
	वापस tot_written;
पूर्ण

अटल sमाप_प्रकार cx18_पढ़ो_pos(काष्ठा cx18_stream *s, अक्षर __user *ubuf,
		माप_प्रकार count, loff_t *pos, पूर्णांक non_block)
अणु
	sमाप_प्रकार rc = count ? cx18_पढ़ो(s, ubuf, count, non_block) : 0;
	काष्ठा cx18 *cx = s->cx;

	CX18_DEBUG_HI_खाता("read %zd from %s, got %zd\n", count, s->name, rc);
	अगर (rc > 0)
		*pos += rc;
	वापस rc;
पूर्ण

पूर्णांक cx18_start_capture(काष्ठा cx18_खोलो_id *id)
अणु
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];
	काष्ठा cx18_stream *s_vbi;
	काष्ठा cx18_stream *s_idx;

	अगर (s->type == CX18_ENC_STREAM_TYPE_RAD) अणु
		/* you cannot पढ़ो from these stream types. */
		वापस -EPERM;
	पूर्ण

	/* Try to claim this stream. */
	अगर (cx18_claim_stream(id, s->type))
		वापस -EBUSY;

	/* If capture is alपढ़ोy in progress, then we also have to
	   करो nothing extra. */
	अगर (test_bit(CX18_F_S_STREAMOFF, &s->s_flags) ||
	    test_and_set_bit(CX18_F_S_STREAMING, &s->s_flags)) अणु
		set_bit(CX18_F_S_APPL_IO, &s->s_flags);
		वापस 0;
	पूर्ण

	/* Start associated VBI or IDX stream capture अगर required */
	s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	s_idx = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	अगर (s->type == CX18_ENC_STREAM_TYPE_MPG) अणु
		/*
		 * The VBI and IDX streams should have been claimed
		 * स्वतःmatically, अगर क्रम पूर्णांकernal use, when the MPG stream was
		 * claimed.  We only need to start these streams capturing.
		 */
		अगर (test_bit(CX18_F_S_INTERNAL_USE, &s_idx->s_flags) &&
		    !test_and_set_bit(CX18_F_S_STREAMING, &s_idx->s_flags)) अणु
			अगर (cx18_start_v4l2_encode_stream(s_idx)) अणु
				CX18_DEBUG_WARN("IDX capture start failed\n");
				clear_bit(CX18_F_S_STREAMING, &s_idx->s_flags);
				जाओ start_failed;
			पूर्ण
			CX18_DEBUG_INFO("IDX capture started\n");
		पूर्ण
		अगर (test_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
		    !test_and_set_bit(CX18_F_S_STREAMING, &s_vbi->s_flags)) अणु
			अगर (cx18_start_v4l2_encode_stream(s_vbi)) अणु
				CX18_DEBUG_WARN("VBI capture start failed\n");
				clear_bit(CX18_F_S_STREAMING, &s_vbi->s_flags);
				जाओ start_failed;
			पूर्ण
			CX18_DEBUG_INFO("VBI insertion started\n");
		पूर्ण
	पूर्ण

	/* Tell the card to start capturing */
	अगर (!cx18_start_v4l2_encode_stream(s)) अणु
		/* We're करोne */
		set_bit(CX18_F_S_APPL_IO, &s->s_flags);
		/* Resume a possibly छोड़ोd encoder */
		अगर (test_and_clear_bit(CX18_F_I_ENC_PAUSED, &cx->i_flags))
			cx18_vapi(cx, CX18_CPU_CAPTURE_PAUSE, 1, s->handle);
		वापस 0;
	पूर्ण

start_failed:
	CX18_DEBUG_WARN("Failed to start capturing for stream %s\n", s->name);

	/*
	 * The associated VBI and IDX streams क्रम पूर्णांकernal use are released
	 * स्वतःmatically when the MPG stream is released.  We only need to stop
	 * the associated stream.
	 */
	अगर (s->type == CX18_ENC_STREAM_TYPE_MPG) अणु
		/* Stop the IDX stream which is always क्रम पूर्णांकernal use */
		अगर (test_bit(CX18_F_S_STREAMING, &s_idx->s_flags)) अणु
			cx18_stop_v4l2_encode_stream(s_idx, 0);
			clear_bit(CX18_F_S_STREAMING, &s_idx->s_flags);
		पूर्ण
		/* Stop the VBI stream, अगर only running क्रम पूर्णांकernal use */
		अगर (test_bit(CX18_F_S_STREAMING, &s_vbi->s_flags) &&
		    !test_bit(CX18_F_S_APPL_IO, &s_vbi->s_flags)) अणु
			cx18_stop_v4l2_encode_stream(s_vbi, 0);
			clear_bit(CX18_F_S_STREAMING, &s_vbi->s_flags);
		पूर्ण
	पूर्ण
	clear_bit(CX18_F_S_STREAMING, &s->s_flags);
	cx18_release_stream(s); /* Also releases associated streams */
	वापस -EIO;
पूर्ण

sमाप_प्रकार cx18_v4l2_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
		loff_t *pos)
अणु
	काष्ठा cx18_खोलो_id *id = file2id(filp);
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];
	पूर्णांक rc;

	CX18_DEBUG_HI_खाता("read %zd bytes from %s\n", count, s->name);

	mutex_lock(&cx->serialize_lock);
	rc = cx18_start_capture(id);
	mutex_unlock(&cx->serialize_lock);
	अगर (rc)
		वापस rc;

	अगर ((s->vb_type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(id->type == CX18_ENC_STREAM_TYPE_YUV)) अणु
		वापस videobuf_पढ़ो_stream(&s->vbuf_q, buf, count, pos, 0,
			filp->f_flags & O_NONBLOCK);
	पूर्ण

	वापस cx18_पढ़ो_pos(s, buf, count, pos, filp->f_flags & O_NONBLOCK);
पूर्ण

__poll_t cx18_v4l2_enc_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा cx18_खोलो_id *id = file2id(filp);
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];
	पूर्णांक eof = test_bit(CX18_F_S_STREAMOFF, &s->s_flags);
	__poll_t res = 0;

	/* Start a capture अगर there is none */
	अगर (!eof && !test_bit(CX18_F_S_STREAMING, &s->s_flags) &&
			(req_events & (EPOLLIN | EPOLLRDNORM))) अणु
		पूर्णांक rc;

		mutex_lock(&cx->serialize_lock);
		rc = cx18_start_capture(id);
		mutex_unlock(&cx->serialize_lock);
		अगर (rc) अणु
			CX18_DEBUG_INFO("Could not start capture for %s (%d)\n",
					s->name, rc);
			वापस EPOLLERR;
		पूर्ण
		CX18_DEBUG_खाता("Encoder poll started capture\n");
	पूर्ण

	अगर ((s->vb_type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(id->type == CX18_ENC_STREAM_TYPE_YUV)) अणु
		__poll_t videobuf_poll = videobuf_poll_stream(filp, &s->vbuf_q, रुको);

		अगर (v4l2_event_pending(&id->fh))
			res |= EPOLLPRI;
		अगर (eof && videobuf_poll == EPOLLERR)
			वापस res | EPOLLHUP;
		वापस res | videobuf_poll;
	पूर्ण

	/* add stream's रुकोq to the poll list */
	CX18_DEBUG_HI_खाता("Encoder poll\n");
	अगर (v4l2_event_pending(&id->fh))
		res |= EPOLLPRI;
	अन्यथा
		poll_रुको(filp, &s->रुकोq, रुको);

	अगर (atomic_पढ़ो(&s->q_full.depth))
		वापस res | EPOLLIN | EPOLLRDNORM;
	अगर (eof)
		वापस res | EPOLLHUP;
	वापस res;
पूर्ण

पूर्णांक cx18_v4l2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा cx18_खोलो_id *id = file->निजी_data;
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];
	पूर्णांक eof = test_bit(CX18_F_S_STREAMOFF, &s->s_flags);

	अगर ((s->vb_type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(id->type == CX18_ENC_STREAM_TYPE_YUV)) अणु

		/* Start a capture अगर there is none */
		अगर (!eof && !test_bit(CX18_F_S_STREAMING, &s->s_flags)) अणु
			पूर्णांक rc;

			mutex_lock(&cx->serialize_lock);
			rc = cx18_start_capture(id);
			mutex_unlock(&cx->serialize_lock);
			अगर (rc) अणु
				CX18_DEBUG_INFO(
					"Could not start capture for %s (%d)\n",
					s->name, rc);
				वापस -EINVAL;
			पूर्ण
			CX18_DEBUG_खाता("Encoder mmap started capture\n");
		पूर्ण

		वापस videobuf_mmap_mapper(&s->vbuf_q, vma);
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम cx18_vb_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा cx18_stream *s = from_समयr(s, t, vb_समयout);
	काष्ठा cx18_videobuf_buffer *buf;
	अचिन्हित दीर्घ flags;

	/* Return all of the buffers in error state, so the vbi/vid inode
	 * can वापस from blocking.
	 */
	spin_lock_irqsave(&s->vb_lock, flags);
	जबतक (!list_empty(&s->vb_capture)) अणु
		buf = list_entry(s->vb_capture.next,
			काष्ठा cx18_videobuf_buffer, vb.queue);
		list_del(&buf->vb.queue);
		buf->vb.state = VIDEOBUF_ERROR;
		wake_up(&buf->vb.करोne);
	पूर्ण
	spin_unlock_irqrestore(&s->vb_lock, flags);
पूर्ण

व्योम cx18_stop_capture(काष्ठा cx18_खोलो_id *id, पूर्णांक gop_end)
अणु
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];
	काष्ठा cx18_stream *s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	काष्ठा cx18_stream *s_idx = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];

	CX18_DEBUG_IOCTL("close() of %s\n", s->name);

	/* 'Unclaim' this stream */

	/* Stop capturing */
	अगर (test_bit(CX18_F_S_STREAMING, &s->s_flags)) अणु
		CX18_DEBUG_INFO("close stopping capture\n");
		अगर (id->type == CX18_ENC_STREAM_TYPE_MPG) अणु
			/* Stop पूर्णांकernal use associated VBI and IDX streams */
			अगर (test_bit(CX18_F_S_STREAMING, &s_vbi->s_flags) &&
			    !test_bit(CX18_F_S_APPL_IO, &s_vbi->s_flags)) अणु
				CX18_DEBUG_INFO("close stopping embedded VBI capture\n");
				cx18_stop_v4l2_encode_stream(s_vbi, 0);
			पूर्ण
			अगर (test_bit(CX18_F_S_STREAMING, &s_idx->s_flags)) अणु
				CX18_DEBUG_INFO("close stopping IDX capture\n");
				cx18_stop_v4l2_encode_stream(s_idx, 0);
			पूर्ण
		पूर्ण
		अगर (id->type == CX18_ENC_STREAM_TYPE_VBI &&
		    test_bit(CX18_F_S_INTERNAL_USE, &s->s_flags))
			/* Also used पूर्णांकernally, करोn't stop capturing */
			s->id = -1;
		अन्यथा
			cx18_stop_v4l2_encode_stream(s, gop_end);
	पूर्ण
	अगर (!gop_end) अणु
		clear_bit(CX18_F_S_APPL_IO, &s->s_flags);
		clear_bit(CX18_F_S_STREAMOFF, &s->s_flags);
		cx18_release_stream(s);
	पूर्ण
पूर्ण

पूर्णांक cx18_v4l2_बंद(काष्ठा file *filp)
अणु
	काष्ठा v4l2_fh *fh = filp->निजी_data;
	काष्ठा cx18_खोलो_id *id = fh2id(fh);
	काष्ठा cx18 *cx = id->cx;
	काष्ठा cx18_stream *s = &cx->streams[id->type];

	CX18_DEBUG_IOCTL("close() of %s\n", s->name);

	mutex_lock(&cx->serialize_lock);
	/* Stop radio */
	अगर (id->type == CX18_ENC_STREAM_TYPE_RAD &&
			v4l2_fh_is_singular_file(filp)) अणु
		/* Closing radio device, वापस to TV mode */
		cx18_mute(cx);
		/* Mark that the radio is no दीर्घer in use */
		clear_bit(CX18_F_I_RADIO_USER, &cx->i_flags);
		/* Switch tuner to TV */
		cx18_call_all(cx, video, s_std, cx->std);
		/* Select correct audio input (i.e. TV tuner or Line in) */
		cx18_audio_set_io(cx);
		अगर (atomic_पढ़ो(&cx->ana_capturing) > 0) अणु
			/* Unकरो video mute */
			cx18_vapi(cx, CX18_CPU_SET_VIDEO_MUTE, 2, s->handle,
			    (v4l2_ctrl_g_ctrl(cx->cxhdl.video_mute) |
			    (v4l2_ctrl_g_ctrl(cx->cxhdl.video_mute_yuv) << 8)));
		पूर्ण
		/* Done! Unmute and जारी. */
		cx18_unmute(cx);
	पूर्ण

	v4l2_fh_del(fh);
	v4l2_fh_निकास(fh);

	/* 'Unclaim' this stream */
	अगर (s->id == id->खोलो_id)
		cx18_stop_capture(id, 0);
	kमुक्त(id);
	mutex_unlock(&cx->serialize_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_serialized_खोलो(काष्ठा cx18_stream *s, काष्ठा file *filp)
अणु
	काष्ठा cx18 *cx = s->cx;
	काष्ठा cx18_खोलो_id *item;

	CX18_DEBUG_खाता("open %s\n", s->name);

	/* Allocate memory */
	item = kzalloc(माप(काष्ठा cx18_खोलो_id), GFP_KERNEL);
	अगर (शून्य == item) अणु
		CX18_DEBUG_WARN("nomem on v4l2 open\n");
		वापस -ENOMEM;
	पूर्ण
	v4l2_fh_init(&item->fh, &s->video_dev);

	item->cx = cx;
	item->type = s->type;

	item->खोलो_id = cx->खोलो_id++;
	filp->निजी_data = &item->fh;
	v4l2_fh_add(&item->fh);

	अगर (item->type == CX18_ENC_STREAM_TYPE_RAD &&
			v4l2_fh_is_singular_file(filp)) अणु
		अगर (!test_bit(CX18_F_I_RADIO_USER, &cx->i_flags)) अणु
			अगर (atomic_पढ़ो(&cx->ana_capturing) > 0) अणु
				/* चयनing to radio जबतक capture is
				   in progress is not polite */
				v4l2_fh_del(&item->fh);
				v4l2_fh_निकास(&item->fh);
				kमुक्त(item);
				वापस -EBUSY;
			पूर्ण
		पूर्ण

		/* Mark that the radio is being used. */
		set_bit(CX18_F_I_RADIO_USER, &cx->i_flags);
		/* We have the radio */
		cx18_mute(cx);
		/* Switch tuner to radio */
		cx18_call_all(cx, tuner, s_radio);
		/* Select the correct audio input (i.e. radio tuner) */
		cx18_audio_set_io(cx);
		/* Done! Unmute and जारी. */
		cx18_unmute(cx);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cx18_v4l2_खोलो(काष्ठा file *filp)
अणु
	पूर्णांक res;
	काष्ठा video_device *video_dev = video_devdata(filp);
	काष्ठा cx18_stream *s = video_get_drvdata(video_dev);
	काष्ठा cx18 *cx = s->cx;

	mutex_lock(&cx->serialize_lock);
	अगर (cx18_init_on_first_खोलो(cx)) अणु
		CX18_ERR("Failed to initialize on %s\n",
			 video_device_node_name(video_dev));
		mutex_unlock(&cx->serialize_lock);
		वापस -ENXIO;
	पूर्ण
	res = cx18_serialized_खोलो(s, filp);
	mutex_unlock(&cx->serialize_lock);
	वापस res;
पूर्ण

व्योम cx18_mute(काष्ठा cx18 *cx)
अणु
	u32 h;
	अगर (atomic_पढ़ो(&cx->ana_capturing)) अणु
		h = cx18_find_handle(cx);
		अगर (h != CX18_INVALID_TASK_HANDLE)
			cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2, h, 1);
		अन्यथा
			CX18_ERR("Can't find valid task handle for mute\n");
	पूर्ण
	CX18_DEBUG_INFO("Mute\n");
पूर्ण

व्योम cx18_unmute(काष्ठा cx18 *cx)
अणु
	u32 h;
	अगर (atomic_पढ़ो(&cx->ana_capturing)) अणु
		h = cx18_find_handle(cx);
		अगर (h != CX18_INVALID_TASK_HANDLE) अणु
			cx18_msleep_समयout(100, 0);
			cx18_vapi(cx, CX18_CPU_SET_MISC_PARAMETERS, 2, h, 12);
			cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2, h, 0);
		पूर्ण अन्यथा
			CX18_ERR("Can't find valid task handle for unmute\n");
	पूर्ण
	CX18_DEBUG_INFO("Unmute\n");
पूर्ण
