<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 mailbox functions
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश <linux/bitops.h>

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-scb.h"
#समावेश "cx18-irq.h"
#समावेश "cx18-mailbox.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-alsa-pcm.h" /* FIXME make configurable */

अटल स्थिर अक्षर *rpu_str[] = अणु "APU", "CPU", "EPU", "HPU" पूर्ण;

#घोषणा API_FAST (1 << 2) /* Short समयout */
#घोषणा API_SLOW (1 << 3) /* Additional 300ms समयout */

काष्ठा cx18_api_info अणु
	u32 cmd;
	u8 flags;		/* Flags, see above */
	u8 rpu;			/* Processing unit */
	स्थिर अक्षर *name;	/* The name of the command */
पूर्ण;

#घोषणा API_ENTRY(rpu, x, f) अणु (x), (f), (rpu), #x पूर्ण

अटल स्थिर काष्ठा cx18_api_info api_info[] = अणु
	/* MPEG encoder API */
	API_ENTRY(CPU, CX18_CPU_SET_CHANNEL_TYPE,		0),
	API_ENTRY(CPU, CX18_EPU_DEBUG,				0),
	API_ENTRY(CPU, CX18_CREATE_TASK,			0),
	API_ENTRY(CPU, CX18_DESTROY_TASK,			0),
	API_ENTRY(CPU, CX18_CPU_CAPTURE_START,                  API_SLOW),
	API_ENTRY(CPU, CX18_CPU_CAPTURE_STOP,                   API_SLOW),
	API_ENTRY(CPU, CX18_CPU_CAPTURE_PAUSE,                  0),
	API_ENTRY(CPU, CX18_CPU_CAPTURE_RESUME,                 0),
	API_ENTRY(CPU, CX18_CPU_SET_CHANNEL_TYPE,               0),
	API_ENTRY(CPU, CX18_CPU_SET_STREAM_OUTPUT_TYPE,         0),
	API_ENTRY(CPU, CX18_CPU_SET_VIDEO_IN,                   0),
	API_ENTRY(CPU, CX18_CPU_SET_VIDEO_RATE,                 0),
	API_ENTRY(CPU, CX18_CPU_SET_VIDEO_RESOLUTION,           0),
	API_ENTRY(CPU, CX18_CPU_SET_FILTER_PARAM,               0),
	API_ENTRY(CPU, CX18_CPU_SET_SPATIAL_FILTER_TYPE,        0),
	API_ENTRY(CPU, CX18_CPU_SET_MEDIAN_CORING,              0),
	API_ENTRY(CPU, CX18_CPU_SET_INDEXTABLE,                 0),
	API_ENTRY(CPU, CX18_CPU_SET_AUDIO_PARAMETERS,           0),
	API_ENTRY(CPU, CX18_CPU_SET_VIDEO_MUTE,                 0),
	API_ENTRY(CPU, CX18_CPU_SET_AUDIO_MUTE,                 0),
	API_ENTRY(CPU, CX18_CPU_SET_MISC_PARAMETERS,            0),
	API_ENTRY(CPU, CX18_CPU_SET_RAW_VBI_PARAM,              API_SLOW),
	API_ENTRY(CPU, CX18_CPU_SET_CAPTURE_LINE_NO,            0),
	API_ENTRY(CPU, CX18_CPU_SET_COPYRIGHT,                  0),
	API_ENTRY(CPU, CX18_CPU_SET_AUDIO_PID,                  0),
	API_ENTRY(CPU, CX18_CPU_SET_VIDEO_PID,                  0),
	API_ENTRY(CPU, CX18_CPU_SET_VER_CROP_LINE,              0),
	API_ENTRY(CPU, CX18_CPU_SET_GOP_STRUCTURE,              0),
	API_ENTRY(CPU, CX18_CPU_SET_SCENE_CHANGE_DETECTION,     0),
	API_ENTRY(CPU, CX18_CPU_SET_ASPECT_RATIO,               0),
	API_ENTRY(CPU, CX18_CPU_SET_SKIP_INPUT_FRAME,           0),
	API_ENTRY(CPU, CX18_CPU_SET_SLICED_VBI_PARAM,           0),
	API_ENTRY(CPU, CX18_CPU_SET_USERDATA_PLACE_HOLDER,      0),
	API_ENTRY(CPU, CX18_CPU_GET_ENC_PTS,                    0),
	API_ENTRY(CPU, CX18_CPU_SET_VFC_PARAM,                  0),
	API_ENTRY(CPU, CX18_CPU_DE_SET_MDL_ACK,			0),
	API_ENTRY(CPU, CX18_CPU_DE_SET_MDL,			API_FAST),
	API_ENTRY(CPU, CX18_CPU_DE_RELEASE_MDL,			API_SLOW),
	API_ENTRY(APU, CX18_APU_START,				0),
	API_ENTRY(APU, CX18_APU_STOP,				0),
	API_ENTRY(APU, CX18_APU_RESETAI,			0),
	API_ENTRY(CPU, CX18_CPU_DEBUG_PEEK32,			0),
	API_ENTRY(0, 0,						0),
पूर्ण;

अटल स्थिर काष्ठा cx18_api_info *find_api_info(u32 cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; api_info[i].cmd; i++)
		अगर (api_info[i].cmd == cmd)
			वापस &api_info[i];
	वापस शून्य;
पूर्ण

/* Call with buf of n*11+1 bytes */
अटल अक्षर *u32arr2hex(u32 data[], पूर्णांक n, अक्षर *buf)
अणु
	अक्षर *p;
	पूर्णांक i;

	क्रम (i = 0, p = buf; i < n; i++, p += 11) अणु
		/* kernel snम_लिखो() appends '\0' always */
		snम_लिखो(p, 12, " %#010x", data[i]);
	पूर्ण
	*p = '\0';
	वापस buf;
पूर्ण

अटल व्योम dump_mb(काष्ठा cx18 *cx, काष्ठा cx18_mailbox *mb, अक्षर *name)
अणु
	अक्षर argstr[MAX_MB_ARGUMENTS*11+1];

	अगर (!(cx18_debug & CX18_DBGFLG_API))
		वापस;

	CX18_DEBUG_API("%s: req %#010x ack %#010x cmd %#010x err %#010x args%s\n",
		       name, mb->request, mb->ack, mb->cmd, mb->error,
		       u32arr2hex(mb->args, MAX_MB_ARGUMENTS, argstr));
पूर्ण


/*
 * Functions that run in a work_queue work handling context
 */

अटल व्योम cx18_mdl_send_to_dvb(काष्ठा cx18_stream *s, काष्ठा cx18_mdl *mdl)
अणु
	काष्ठा cx18_buffer *buf;

	अगर (s->dvb == शून्य || !s->dvb->enabled || mdl->bytesused == 0)
		वापस;

	/* We ignore mdl and buf पढ़ोpos accounting here - it करोesn't matter */

	/* The likely हाल */
	अगर (list_is_singular(&mdl->buf_list)) अणु
		buf = list_first_entry(&mdl->buf_list, काष्ठा cx18_buffer,
				       list);
		अगर (buf->bytesused)
			dvb_dmx_swfilter(&s->dvb->demux,
					 buf->buf, buf->bytesused);
		वापस;
	पूर्ण

	list_क्रम_each_entry(buf, &mdl->buf_list, list) अणु
		अगर (buf->bytesused == 0)
			अवरोध;
		dvb_dmx_swfilter(&s->dvb->demux, buf->buf, buf->bytesused);
	पूर्ण
पूर्ण

अटल व्योम cx18_mdl_send_to_videobuf(काष्ठा cx18_stream *s,
	काष्ठा cx18_mdl *mdl)
अणु
	काष्ठा cx18_videobuf_buffer *vb_buf;
	काष्ठा cx18_buffer *buf;
	u8 *p;
	u32 offset = 0;
	पूर्णांक dispatch = 0;

	अगर (mdl->bytesused == 0)
		वापस;

	/* Acquire a videobuf buffer, clone to and and release it */
	spin_lock(&s->vb_lock);
	अगर (list_empty(&s->vb_capture))
		जाओ out;

	vb_buf = list_first_entry(&s->vb_capture, काष्ठा cx18_videobuf_buffer,
		vb.queue);

	p = videobuf_to_vदो_स्मृति(&vb_buf->vb);
	अगर (!p)
		जाओ out;

	offset = vb_buf->bytes_used;
	list_क्रम_each_entry(buf, &mdl->buf_list, list) अणु
		अगर (buf->bytesused == 0)
			अवरोध;

		अगर ((offset + buf->bytesused) <= vb_buf->vb.bsize) अणु
			स_नकल(p + offset, buf->buf, buf->bytesused);
			offset += buf->bytesused;
			vb_buf->bytes_used += buf->bytesused;
		पूर्ण
	पूर्ण

	/* If we've filled the buffer as per the callers res then dispatch it */
	अगर (vb_buf->bytes_used >= s->vb_bytes_per_frame) अणु
		dispatch = 1;
		vb_buf->bytes_used = 0;
	पूर्ण

	अगर (dispatch) अणु
		vb_buf->vb.ts = kसमय_get_ns();
		list_del(&vb_buf->vb.queue);
		vb_buf->vb.state = VIDEOBUF_DONE;
		wake_up(&vb_buf->vb.करोne);
	पूर्ण

	mod_समयr(&s->vb_समयout, msecs_to_jअगरfies(2000) + jअगरfies);

out:
	spin_unlock(&s->vb_lock);
पूर्ण

अटल व्योम cx18_mdl_send_to_alsa(काष्ठा cx18 *cx, काष्ठा cx18_stream *s,
				  काष्ठा cx18_mdl *mdl)
अणु
	काष्ठा cx18_buffer *buf;

	अगर (mdl->bytesused == 0)
		वापस;

	/* We ignore mdl and buf पढ़ोpos accounting here - it करोesn't matter */

	/* The likely हाल */
	अगर (list_is_singular(&mdl->buf_list)) अणु
		buf = list_first_entry(&mdl->buf_list, काष्ठा cx18_buffer,
				       list);
		अगर (buf->bytesused)
			cx->pcm_announce_callback(cx->alsa, buf->buf,
						  buf->bytesused);
		वापस;
	पूर्ण

	list_क्रम_each_entry(buf, &mdl->buf_list, list) अणु
		अगर (buf->bytesused == 0)
			अवरोध;
		cx->pcm_announce_callback(cx->alsa, buf->buf, buf->bytesused);
	पूर्ण
पूर्ण

अटल व्योम epu_dma_करोne(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	u32 handle, mdl_ack_count, id;
	काष्ठा cx18_mailbox *mb;
	काष्ठा cx18_mdl_ack *mdl_ack;
	काष्ठा cx18_stream *s;
	काष्ठा cx18_mdl *mdl;
	पूर्णांक i;

	mb = &order->mb;
	handle = mb->args[0];
	s = cx18_handle_to_stream(cx, handle);

	अगर (s == शून्य) अणु
		CX18_WARN("Got DMA done notification for unknown/inactive handle %d, %s mailbox seq no %d\n",
			  handle,
			  (order->flags & CX18_F_EWO_MB_STALE_UPON_RECEIPT) ?
			  "stale" : "good", mb->request);
		वापस;
	पूर्ण

	mdl_ack_count = mb->args[2];
	mdl_ack = order->mdl_ack;
	क्रम (i = 0; i < mdl_ack_count; i++, mdl_ack++) अणु
		id = mdl_ack->id;
		/*
		 * Simple पूर्णांकegrity check क्रम processing a stale (and possibly
		 * inconsistent mailbox): make sure the MDL id is in the
		 * valid range क्रम the stream.
		 *
		 * We go through the trouble of dealing with stale mailboxes
		 * because most of the समय, the mailbox data is still valid and
		 * unchanged (and in practice the firmware ping-pongs the
		 * two mdl_ack buffers so mdl_acks are not stale).
		 *
		 * There are occasions when we get a half changed mailbox,
		 * which this check catches क्रम a handle & id mismatch.  If the
		 * handle and id करो correspond, the worst हाल is that we
		 * completely lost the old MDL, but pick up the new MDL
		 * early (but the new mdl_ack is guaranteed to be good in this
		 * हाल as the firmware wouldn't poपूर्णांक us to a new mdl_ack until
		 * it's filled in).
		 *
		 * cx18_queue_get_mdl() will detect the lost MDLs
		 * and send them back to q_मुक्त क्रम fw rotation eventually.
		 */
		अगर ((order->flags & CX18_F_EWO_MB_STALE_UPON_RECEIPT) &&
		    !(id >= s->mdl_base_idx &&
		      id < (s->mdl_base_idx + s->buffers))) अणु
			CX18_WARN("Fell behind! Ignoring stale mailbox with  inconsistent data. Lost MDL for mailbox seq no %d\n",
				  mb->request);
			अवरोध;
		पूर्ण
		mdl = cx18_queue_get_mdl(s, id, mdl_ack->data_used);

		CX18_DEBUG_HI_DMA("DMA DONE for %s (MDL %d)\n", s->name, id);
		अगर (mdl == शून्य) अणु
			CX18_WARN("Could not find MDL %d for stream %s\n",
				  id, s->name);
			जारी;
		पूर्ण

		CX18_DEBUG_HI_DMA("%s recv bytesused = %d\n",
				  s->name, mdl->bytesused);

		अगर (s->type == CX18_ENC_STREAM_TYPE_TS) अणु
			cx18_mdl_send_to_dvb(s, mdl);
			cx18_enqueue(s, mdl, &s->q_मुक्त);
		पूर्ण अन्यथा अगर (s->type == CX18_ENC_STREAM_TYPE_PCM) अणु
			/* Pass the data to cx18-alsa */
			अगर (cx->pcm_announce_callback != शून्य) अणु
				cx18_mdl_send_to_alsa(cx, s, mdl);
				cx18_enqueue(s, mdl, &s->q_मुक्त);
			पूर्ण अन्यथा अणु
				cx18_enqueue(s, mdl, &s->q_full);
			पूर्ण
		पूर्ण अन्यथा अगर (s->type == CX18_ENC_STREAM_TYPE_YUV) अणु
			cx18_mdl_send_to_videobuf(s, mdl);
			cx18_enqueue(s, mdl, &s->q_मुक्त);
		पूर्ण अन्यथा अणु
			cx18_enqueue(s, mdl, &s->q_full);
			अगर (s->type == CX18_ENC_STREAM_TYPE_IDX)
				cx18_stream_rotate_idx_mdls(cx);
		पूर्ण
	पूर्ण
	/* Put as many MDLs as possible back पूर्णांकo fw use */
	cx18_stream_load_fw_queue(s);

	wake_up(&cx->dma_रुकोq);
	अगर (s->id != -1)
		wake_up(&s->रुकोq);
पूर्ण

अटल व्योम epu_debug(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	अक्षर *p;
	अक्षर *str = order->str;

	CX18_DEBUG_INFO("%x %s\n", order->mb.args[0], str);
	p = म_अक्षर(str, '.');
	अगर (!test_bit(CX18_F_I_LOADED_FW, &cx->i_flags) && p && p > str)
		CX18_INFO("FW version: %s\n", p - 1);
पूर्ण

अटल व्योम epu_cmd(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	चयन (order->rpu) अणु
	हाल CPU:
	अणु
		चयन (order->mb.cmd) अणु
		हाल CX18_EPU_DMA_DONE:
			epu_dma_करोne(cx, order);
			अवरोध;
		हाल CX18_EPU_DEBUG:
			epu_debug(cx, order);
			अवरोध;
		शेष:
			CX18_WARN("Unknown CPU to EPU mailbox command %#0x\n",
				  order->mb.cmd);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल APU:
		CX18_WARN("Unknown APU to EPU mailbox command %#0x\n",
			  order->mb.cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम मुक्त_in_work_order(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	atomic_set(&order->pending, 0);
पूर्ण

व्योम cx18_in_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx18_in_work_order *order =
			container_of(work, काष्ठा cx18_in_work_order, work);
	काष्ठा cx18 *cx = order->cx;
	epu_cmd(cx, order);
	मुक्त_in_work_order(cx, order);
पूर्ण


/*
 * Functions that run in an पूर्णांकerrupt handling context
 */

अटल व्योम mb_ack_irq(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	काष्ठा cx18_mailbox __iomem *ack_mb;
	u32 ack_irq, req;

	चयन (order->rpu) अणु
	हाल APU:
		ack_irq = IRQ_EPU_TO_APU_ACK;
		ack_mb = &cx->scb->apu2epu_mb;
		अवरोध;
	हाल CPU:
		ack_irq = IRQ_EPU_TO_CPU_ACK;
		ack_mb = &cx->scb->cpu2epu_mb;
		अवरोध;
	शेष:
		CX18_WARN("Unhandled RPU (%d) for command %x ack\n",
			  order->rpu, order->mb.cmd);
		वापस;
	पूर्ण

	req = order->mb.request;
	/* Don't ack अगर the RPU has gotten impatient and समयd us out */
	अगर (req != cx18_पढ़ोl(cx, &ack_mb->request) ||
	    req == cx18_पढ़ोl(cx, &ack_mb->ack)) अणु
		CX18_DEBUG_WARN("Possibly falling behind: %s self-ack'ed our incoming %s to EPU mailbox (sequence no. %u) while processing\n",
				rpu_str[order->rpu], rpu_str[order->rpu], req);
		order->flags |= CX18_F_EWO_MB_STALE_WHILE_PROC;
		वापस;
	पूर्ण
	cx18_ग_लिखोl(cx, req, &ack_mb->ack);
	cx18_ग_लिखो_reg_expect(cx, ack_irq, SW2_INT_SET, ack_irq, ack_irq);
	वापस;
पूर्ण

अटल पूर्णांक epu_dma_करोne_irq(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	u32 handle, mdl_ack_offset, mdl_ack_count;
	काष्ठा cx18_mailbox *mb;
	पूर्णांक i;

	mb = &order->mb;
	handle = mb->args[0];
	mdl_ack_offset = mb->args[1];
	mdl_ack_count = mb->args[2];

	अगर (handle == CX18_INVALID_TASK_HANDLE ||
	    mdl_ack_count == 0 || mdl_ack_count > CX18_MAX_MDL_ACKS) अणु
		अगर ((order->flags & CX18_F_EWO_MB_STALE) == 0)
			mb_ack_irq(cx, order);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < माप(काष्ठा cx18_mdl_ack) * mdl_ack_count; i += माप(u32))
		((u32 *)order->mdl_ack)[i / माप(u32)] =
			cx18_पढ़ोl(cx, cx->enc_mem + mdl_ack_offset + i);

	अगर ((order->flags & CX18_F_EWO_MB_STALE) == 0)
		mb_ack_irq(cx, order);
	वापस 1;
पूर्ण

अटल
पूर्णांक epu_debug_irq(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	u32 str_offset;
	अक्षर *str = order->str;

	str[0] = '\0';
	str_offset = order->mb.args[1];
	अगर (str_offset) अणु
		cx18_setup_page(cx, str_offset);
		cx18_स_नकल_fromio(cx, str, cx->enc_mem + str_offset, 252);
		str[252] = '\0';
		cx18_setup_page(cx, SCB_OFFSET);
	पूर्ण

	अगर ((order->flags & CX18_F_EWO_MB_STALE) == 0)
		mb_ack_irq(cx, order);

	वापस str_offset ? 1 : 0;
पूर्ण

अटल अंतरभूत
पूर्णांक epu_cmd_irq(काष्ठा cx18 *cx, काष्ठा cx18_in_work_order *order)
अणु
	पूर्णांक ret = -1;

	चयन (order->rpu) अणु
	हाल CPU:
	अणु
		चयन (order->mb.cmd) अणु
		हाल CX18_EPU_DMA_DONE:
			ret = epu_dma_करोne_irq(cx, order);
			अवरोध;
		हाल CX18_EPU_DEBUG:
			ret = epu_debug_irq(cx, order);
			अवरोध;
		शेष:
			CX18_WARN("Unknown CPU to EPU mailbox command %#0x\n",
				  order->mb.cmd);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल APU:
		CX18_WARN("Unknown APU to EPU mailbox command %#0x\n",
			  order->mb.cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत
काष्ठा cx18_in_work_order *alloc_in_work_order_irq(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;
	काष्ठा cx18_in_work_order *order = शून्य;

	क्रम (i = 0; i < CX18_MAX_IN_WORK_ORDERS; i++) अणु
		/*
		 * We only need "pending" atomic to inspect its contents,
		 * and need not करो a check and set because:
		 * 1. Any work handler thपढ़ो only clears "pending" and only
		 * on one, particular work order at a समय, per handler thपढ़ो.
		 * 2. "pending" is only set here, and we're serialized because
		 * we're called in an IRQ handler context.
		 */
		अगर (atomic_पढ़ो(&cx->in_work_order[i].pending) == 0) अणु
			order = &cx->in_work_order[i];
			atomic_set(&order->pending, 1);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस order;
पूर्ण

व्योम cx18_api_epu_cmd_irq(काष्ठा cx18 *cx, पूर्णांक rpu)
अणु
	काष्ठा cx18_mailbox __iomem *mb;
	काष्ठा cx18_mailbox *order_mb;
	काष्ठा cx18_in_work_order *order;
	पूर्णांक submit;
	पूर्णांक i;

	चयन (rpu) अणु
	हाल CPU:
		mb = &cx->scb->cpu2epu_mb;
		अवरोध;
	हाल APU:
		mb = &cx->scb->apu2epu_mb;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	order = alloc_in_work_order_irq(cx);
	अगर (order == शून्य) अणु
		CX18_WARN("Unable to find blank work order form to schedule incoming mailbox command processing\n");
		वापस;
	पूर्ण

	order->flags = 0;
	order->rpu = rpu;
	order_mb = &order->mb;

	/* mb->cmd and mb->args[0] through mb->args[2] */
	क्रम (i = 0; i < 4; i++)
		(&order_mb->cmd)[i] = cx18_पढ़ोl(cx, &mb->cmd + i);

	/* mb->request and mb->ack.  N.B. we want to पढ़ो mb->ack last */
	क्रम (i = 0; i < 2; i++)
		(&order_mb->request)[i] = cx18_पढ़ोl(cx, &mb->request + i);

	अगर (order_mb->request == order_mb->ack) अणु
		CX18_DEBUG_WARN("Possibly falling behind: %s self-ack'ed our incoming %s to EPU mailbox (sequence no. %u)\n",
				rpu_str[rpu], rpu_str[rpu], order_mb->request);
		अगर (cx18_debug & CX18_DBGFLG_WARN)
			dump_mb(cx, order_mb, "incoming");
		order->flags = CX18_F_EWO_MB_STALE_UPON_RECEIPT;
	पूर्ण

	/*
	 * Inभागidual EPU command processing is responsible क्रम ack-ing
	 * a non-stale mailbox as soon as possible
	 */
	submit = epu_cmd_irq(cx, order);
	अगर (submit > 0) अणु
		queue_work(cx->in_work_queue, &order->work);
	पूर्ण
पूर्ण


/*
 * Functions called from a non-पूर्णांकerrupt, non work_queue context
 */

अटल पूर्णांक cx18_api_call(काष्ठा cx18 *cx, u32 cmd, पूर्णांक args, u32 data[])
अणु
	स्थिर काष्ठा cx18_api_info *info = find_api_info(cmd);
	u32 irq, req, ack, err;
	काष्ठा cx18_mailbox __iomem *mb;
	रुको_queue_head_t *रुकोq;
	काष्ठा mutex *mb_lock;
	अचिन्हित दीर्घ पूर्णांक t0, समयout, ret;
	पूर्णांक i;
	अक्षर argstr[MAX_MB_ARGUMENTS*11+1];
	DEFINE_WAIT(w);

	अगर (info == शून्य) अणु
		CX18_WARN("unknown cmd %x\n", cmd);
		वापस -EINVAL;
	पूर्ण

	अगर (cx18_debug & CX18_DBGFLG_API) अणु /* only call u32arr2hex अगर needed */
		अगर (cmd == CX18_CPU_DE_SET_MDL) अणु
			अगर (cx18_debug & CX18_DBGFLG_HIGHVOL)
				CX18_DEBUG_HI_API("%s\tcmd %#010x args%s\n",
						info->name, cmd,
						u32arr2hex(data, args, argstr));
		पूर्ण अन्यथा
			CX18_DEBUG_API("%s\tcmd %#010x args%s\n",
				       info->name, cmd,
				       u32arr2hex(data, args, argstr));
	पूर्ण

	चयन (info->rpu) अणु
	हाल APU:
		रुकोq = &cx->mb_apu_रुकोq;
		mb_lock = &cx->epu2apu_mb_lock;
		irq = IRQ_EPU_TO_APU;
		mb = &cx->scb->epu2apu_mb;
		अवरोध;
	हाल CPU:
		रुकोq = &cx->mb_cpu_रुकोq;
		mb_lock = &cx->epu2cpu_mb_lock;
		irq = IRQ_EPU_TO_CPU;
		mb = &cx->scb->epu2cpu_mb;
		अवरोध;
	शेष:
		CX18_WARN("Unknown RPU (%d) for API call\n", info->rpu);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(mb_lock);
	/*
	 * Wait क्रम an in-use mailbox to complete
	 *
	 * If the XPU is responding with Ack's, the mailbox shouldn't be in
	 * a busy state, since we serialize access to it on our end.
	 *
	 * If the रुको क्रम ack after sending a previous command was पूर्णांकerrupted
	 * by a संकेत, we may get here and find a busy mailbox.  After रुकोing,
	 * mark it "not busy" from our end, अगर the XPU hasn't ack'ed it still.
	 */
	req = cx18_पढ़ोl(cx, &mb->request);
	समयout = msecs_to_jअगरfies(10);
	ret = रुको_event_समयout(*रुकोq,
				 (ack = cx18_पढ़ोl(cx, &mb->ack)) == req,
				 समयout);
	अगर (req != ack) अणु
		/* रुकोed दीर्घ enough, make the mbox "not busy" from our end */
		cx18_ग_लिखोl(cx, req, &mb->ack);
		CX18_ERR("mbox was found stuck busy when setting up for %s; clearing busy and trying to proceed\n",
			 info->name);
	पूर्ण अन्यथा अगर (ret != समयout)
		CX18_DEBUG_API("waited %u msecs for busy mbox to be acked\n",
			       jअगरfies_to_msecs(समयout-ret));

	/* Build the outgoing mailbox */
	req = ((req & 0xfffffffe) == 0xfffffffe) ? 1 : req + 1;

	cx18_ग_लिखोl(cx, cmd, &mb->cmd);
	क्रम (i = 0; i < args; i++)
		cx18_ग_लिखोl(cx, data[i], &mb->args[i]);
	cx18_ग_लिखोl(cx, 0, &mb->error);
	cx18_ग_लिखोl(cx, req, &mb->request);
	cx18_ग_लिखोl(cx, req - 1, &mb->ack); /* ensure ack & req are distinct */

	/*
	 * Notअगरy the XPU and रुको क्रम it to send an Ack back
	 */
	समयout = msecs_to_jअगरfies((info->flags & API_FAST) ? 10 : 20);

	CX18_DEBUG_HI_IRQ("sending interrupt SW1: %x to send %s\n",
			  irq, info->name);

	/* So we करोn't miss the wakeup, prepare to रुको beक्रमe notअगरying fw */
	prepare_to_रुको(रुकोq, &w, TASK_UNINTERRUPTIBLE);
	cx18_ग_लिखो_reg_expect(cx, irq, SW1_INT_SET, irq, irq);

	t0 = jअगरfies;
	ack = cx18_पढ़ोl(cx, &mb->ack);
	अगर (ack != req) अणु
		schedule_समयout(समयout);
		ret = jअगरfies - t0;
		ack = cx18_पढ़ोl(cx, &mb->ack);
	पूर्ण अन्यथा अणु
		ret = jअगरfies - t0;
	पूर्ण

	finish_रुको(रुकोq, &w);

	अगर (req != ack) अणु
		mutex_unlock(mb_lock);
		अगर (ret >= समयout) अणु
			/* Timed out */
			CX18_DEBUG_WARN("sending %s timed out waiting %d msecs for RPU acknowledgment\n",
					info->name, jअगरfies_to_msecs(ret));
		पूर्ण अन्यथा अणु
			CX18_DEBUG_WARN("woken up before mailbox ack was ready after submitting %s to RPU.  only waited %d msecs on req %u but awakened with unmatched ack %u\n",
					info->name,
					jअगरfies_to_msecs(ret),
					req, ack);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	अगर (ret >= समयout)
		CX18_DEBUG_WARN("failed to be awakened upon RPU acknowledgment sending %s; timed out waiting %d msecs\n",
				info->name, jअगरfies_to_msecs(ret));
	अन्यथा
		CX18_DEBUG_HI_API("waited %u msecs for %s to be acked\n",
				  jअगरfies_to_msecs(ret), info->name);

	/* Collect data वापसed by the XPU */
	क्रम (i = 0; i < MAX_MB_ARGUMENTS; i++)
		data[i] = cx18_पढ़ोl(cx, &mb->args[i]);
	err = cx18_पढ़ोl(cx, &mb->error);
	mutex_unlock(mb_lock);

	/*
	 * Wait क्रम XPU to perक्रमm extra actions क्रम the caller in some हालs.
	 * e.g. CX18_CPU_DE_RELEASE_MDL will cause the CPU to send all MDLs
	 * back in a burst लघुly thereafter
	 */
	अगर (info->flags & API_SLOW)
		cx18_msleep_समयout(300, 0);

	अगर (err)
		CX18_DEBUG_API("mailbox error %08x for command %s\n", err,
				info->name);
	वापस err ? -EIO : 0;
पूर्ण

पूर्णांक cx18_api(काष्ठा cx18 *cx, u32 cmd, पूर्णांक args, u32 data[])
अणु
	वापस cx18_api_call(cx, cmd, args, data);
पूर्ण

अटल पूर्णांक cx18_set_filter_param(काष्ठा cx18_stream *s)
अणु
	काष्ठा cx18 *cx = s->cx;
	u32 mode;
	पूर्णांक ret;

	mode = (cx->filter_mode & 1) ? 2 : (cx->spatial_strength ? 1 : 0);
	ret = cx18_vapi(cx, CX18_CPU_SET_FILTER_PARAM, 4,
			s->handle, 1, mode, cx->spatial_strength);
	mode = (cx->filter_mode & 2) ? 2 : (cx->temporal_strength ? 1 : 0);
	ret = ret ? ret : cx18_vapi(cx, CX18_CPU_SET_FILTER_PARAM, 4,
			s->handle, 0, mode, cx->temporal_strength);
	ret = ret ? ret : cx18_vapi(cx, CX18_CPU_SET_FILTER_PARAM, 4,
			s->handle, 2, cx->filter_mode >> 2, 0);
	वापस ret;
पूर्ण

पूर्णांक cx18_api_func(व्योम *priv, u32 cmd, पूर्णांक in, पूर्णांक out,
		u32 data[CX2341X_MBOX_MAX_DATA])
अणु
	काष्ठा cx18_stream *s = priv;
	काष्ठा cx18 *cx = s->cx;

	चयन (cmd) अणु
	हाल CX2341X_ENC_SET_OUTPUT_PORT:
		वापस 0;
	हाल CX2341X_ENC_SET_FRAME_RATE:
		वापस cx18_vapi(cx, CX18_CPU_SET_VIDEO_IN, 6,
				s->handle, 0, 0, 0, 0, data[0]);
	हाल CX2341X_ENC_SET_FRAME_SIZE:
		वापस cx18_vapi(cx, CX18_CPU_SET_VIDEO_RESOLUTION, 3,
				s->handle, data[1], data[0]);
	हाल CX2341X_ENC_SET_STREAM_TYPE:
		वापस cx18_vapi(cx, CX18_CPU_SET_STREAM_OUTPUT_TYPE, 2,
				s->handle, data[0]);
	हाल CX2341X_ENC_SET_ASPECT_RATIO:
		वापस cx18_vapi(cx, CX18_CPU_SET_ASPECT_RATIO, 2,
				s->handle, data[0]);

	हाल CX2341X_ENC_SET_GOP_PROPERTIES:
		वापस cx18_vapi(cx, CX18_CPU_SET_GOP_STRUCTURE, 3,
				s->handle, data[0], data[1]);
	हाल CX2341X_ENC_SET_GOP_CLOSURE:
		वापस 0;
	हाल CX2341X_ENC_SET_AUDIO_PROPERTIES:
		वापस cx18_vapi(cx, CX18_CPU_SET_AUDIO_PARAMETERS, 2,
				s->handle, data[0]);
	हाल CX2341X_ENC_MUTE_AUDIO:
		वापस cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2,
				s->handle, data[0]);
	हाल CX2341X_ENC_SET_BIT_RATE:
		वापस cx18_vapi(cx, CX18_CPU_SET_VIDEO_RATE, 5,
				s->handle, data[0], data[1], data[2], data[3]);
	हाल CX2341X_ENC_MUTE_VIDEO:
		वापस cx18_vapi(cx, CX18_CPU_SET_VIDEO_MUTE, 2,
				s->handle, data[0]);
	हाल CX2341X_ENC_SET_FRAME_DROP_RATE:
		वापस cx18_vapi(cx, CX18_CPU_SET_SKIP_INPUT_FRAME, 2,
				s->handle, data[0]);
	हाल CX2341X_ENC_MISC:
		वापस cx18_vapi(cx, CX18_CPU_SET_MISC_PARAMETERS, 4,
				s->handle, data[0], data[1], data[2]);
	हाल CX2341X_ENC_SET_DNR_FILTER_MODE:
		cx->filter_mode = (data[0] & 3) | (data[1] << 2);
		वापस cx18_set_filter_param(s);
	हाल CX2341X_ENC_SET_DNR_FILTER_PROPS:
		cx->spatial_strength = data[0];
		cx->temporal_strength = data[1];
		वापस cx18_set_filter_param(s);
	हाल CX2341X_ENC_SET_SPATIAL_FILTER_TYPE:
		वापस cx18_vapi(cx, CX18_CPU_SET_SPATIAL_FILTER_TYPE, 3,
				s->handle, data[0], data[1]);
	हाल CX2341X_ENC_SET_CORING_LEVELS:
		वापस cx18_vapi(cx, CX18_CPU_SET_MEDIAN_CORING, 5,
				s->handle, data[0], data[1], data[2], data[3]);
	पूर्ण
	CX18_WARN("Unknown cmd %x\n", cmd);
	वापस 0;
पूर्ण

पूर्णांक cx18_vapi_result(काष्ठा cx18 *cx, u32 data[MAX_MB_ARGUMENTS],
		u32 cmd, पूर्णांक args, ...)
अणु
	बहु_सूची ap;
	पूर्णांक i;

	बहु_शुरू(ap, args);
	क्रम (i = 0; i < args; i++)
		data[i] = बहु_तर्क(ap, u32);
	बहु_पूर्ण(ap);
	वापस cx18_api(cx, cmd, args, data);
पूर्ण

पूर्णांक cx18_vapi(काष्ठा cx18 *cx, u32 cmd, पूर्णांक args, ...)
अणु
	u32 data[MAX_MB_ARGUMENTS];
	बहु_सूची ap;
	पूर्णांक i;

	अगर (cx == शून्य) अणु
		CX18_ERR("cx == NULL (cmd=%x)\n", cmd);
		वापस 0;
	पूर्ण
	अगर (args > MAX_MB_ARGUMENTS) अणु
		CX18_ERR("args too big (cmd=%x)\n", cmd);
		args = MAX_MB_ARGUMENTS;
	पूर्ण
	बहु_शुरू(ap, args);
	क्रम (i = 0; i < args; i++)
		data[i] = बहु_तर्क(ap, u32);
	बहु_पूर्ण(ap);
	वापस cx18_api(cx, cmd, args, data);
पूर्ण
