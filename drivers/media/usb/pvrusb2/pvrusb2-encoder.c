<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#समावेश <linux/device.h>   // क्रम linux/firmware.h
#समावेश <linux/firmware.h>
#समावेश "pvrusb2-util.h"
#समावेश "pvrusb2-encoder.h"
#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-debug.h"
#समावेश "pvrusb2-fx2-cmd.h"



/* Firmware mailbox flags - definitions found from ivtv */
#घोषणा IVTV_MBOX_FIRMWARE_DONE 0x00000004
#घोषणा IVTV_MBOX_DRIVER_DONE 0x00000002
#घोषणा IVTV_MBOX_DRIVER_BUSY 0x00000001

#घोषणा MBOX_BASE 0x44


अटल पूर्णांक pvr2_encoder_ग_लिखो_words(काष्ठा pvr2_hdw *hdw,
				    अचिन्हित पूर्णांक offs,
				    स्थिर u32 *data, अचिन्हित पूर्णांक dlen)
अणु
	अचिन्हित पूर्णांक idx,addr;
	अचिन्हित पूर्णांक bAddr;
	पूर्णांक ret;
	अचिन्हित पूर्णांक chunkCnt;

	/*

	Format: First byte must be 0x01.  Reमुख्यing 32 bit words are
	spपढ़ो out पूर्णांकo chunks of 7 bytes each, with the first 4 bytes
	being the data word (little endian), and the next 3 bytes
	being the address where that data word is to be written (big
	endian).  Repeat request क्रम additional words, with offset
	adjusted accordingly.

	*/
	जबतक (dlen) अणु
		chunkCnt = 8;
		अगर (chunkCnt > dlen) chunkCnt = dlen;
		स_रखो(hdw->cmd_buffer,0,माप(hdw->cmd_buffer));
		bAddr = 0;
		hdw->cmd_buffer[bAddr++] = FX2CMD_MEM_WRITE_DWORD;
		क्रम (idx = 0; idx < chunkCnt; idx++) अणु
			addr = idx + offs;
			hdw->cmd_buffer[bAddr+6] = (addr & 0xffu);
			hdw->cmd_buffer[bAddr+5] = ((addr>>8) & 0xffu);
			hdw->cmd_buffer[bAddr+4] = ((addr>>16) & 0xffu);
			PVR2_DECOMPOSE_LE(hdw->cmd_buffer, bAddr,data[idx]);
			bAddr += 7;
		पूर्ण
		ret = pvr2_send_request(hdw,
					hdw->cmd_buffer,1+(chunkCnt*7),
					शून्य,0);
		अगर (ret) वापस ret;
		data += chunkCnt;
		dlen -= chunkCnt;
		offs += chunkCnt;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक pvr2_encoder_पढ़ो_words(काष्ठा pvr2_hdw *hdw,
				   अचिन्हित पूर्णांक offs,
				   u32 *data, अचिन्हित पूर्णांक dlen)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret;
	अचिन्हित पूर्णांक chunkCnt;

	/*

	Format: First byte must be 0x02 (status check) or 0x28 (पढ़ो
	back block of 32 bit words).  Next 6 bytes must be zero,
	followed by a single byte of MBOX_BASE+offset क्रम portion to
	be पढ़ो.  Returned data is packed set of 32 bits words that
	were पढ़ो.

	*/

	जबतक (dlen) अणु
		chunkCnt = 16;
		अगर (chunkCnt > dlen) chunkCnt = dlen;
		अगर (chunkCnt < 16) chunkCnt = 1;
		hdw->cmd_buffer[0] =
			((chunkCnt == 1) ?
			 FX2CMD_MEM_READ_DWORD : FX2CMD_MEM_READ_64BYTES);
		hdw->cmd_buffer[1] = 0;
		hdw->cmd_buffer[2] = 0;
		hdw->cmd_buffer[3] = 0;
		hdw->cmd_buffer[4] = 0;
		hdw->cmd_buffer[5] = ((offs>>16) & 0xffu);
		hdw->cmd_buffer[6] = ((offs>>8) & 0xffu);
		hdw->cmd_buffer[7] = (offs & 0xffu);
		ret = pvr2_send_request(hdw,
					hdw->cmd_buffer,8,
					hdw->cmd_buffer,
					(chunkCnt == 1 ? 4 : 16 * 4));
		अगर (ret) वापस ret;

		क्रम (idx = 0; idx < chunkCnt; idx++) अणु
			data[idx] = PVR2_COMPOSE_LE(hdw->cmd_buffer,idx*4);
		पूर्ण
		data += chunkCnt;
		dlen -= chunkCnt;
		offs += chunkCnt;
	पूर्ण

	वापस 0;
पूर्ण


/* This prototype is set up to be compatible with the
   cx2341x_mbox_func prototype in cx2341x.h, which should be in
   kernels 2.6.18 or later.  We करो this so that we can enable
   cx2341x.ko to ग_लिखो to our encoder (by handing it a poपूर्णांकer to this
   function).  For earlier kernels this करोesn't really matter. */
अटल पूर्णांक pvr2_encoder_cmd(व्योम *ctxt,
			    u32 cmd,
			    पूर्णांक arg_cnt_send,
			    पूर्णांक arg_cnt_recv,
			    u32 *argp)
अणु
	अचिन्हित पूर्णांक poll_count;
	अचिन्हित पूर्णांक try_count = 0;
	पूर्णांक retry_flag;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक idx;
	/* These sizes look to be limited by the FX2 firmware implementation */
	u32 wrData[16];
	u32 rdData[16];
	काष्ठा pvr2_hdw *hdw = (काष्ठा pvr2_hdw *)ctxt;


	/*

	The encoder seems to speak entirely using blocks 32 bit words.
	In ivtv driver terms, this is a mailbox at MBOX_BASE which we
	populate with data and watch what the hardware करोes with it.
	The first word is a set of flags used to control the
	transaction, the second word is the command to execute, the
	third byte is zero (ivtv driver suggests that this is some
	kind of वापस value), and the fourth byte is a specअगरied
	समयout (winकरोws driver always uses 0x00060000 except क्रम one
	हाल when it is zero).  All successive words are the argument
	words क्रम the command.

	First, ग_लिखो out the entire set of words, with the first word
	being zero.

	Next, ग_लिखो out just the first word again, but set it to
	IVTV_MBOX_DRIVER_DONE | IVTV_DRIVER_BUSY this समय (which
	probably means "go").

	Next, पढ़ो back the वापस count words.  Check the first word,
	which should have IVTV_MBOX_FIRMWARE_DONE set.  If however
	that bit is not set, then the command isn't करोne so repeat the
	पढ़ो until it is set.

	Finally, ग_लिखो out just the first word again, but set it to
	0x0 this समय (which probably means "idle").

	*/

	अगर (arg_cnt_send > (ARRAY_SIZE(wrData) - 4)) अणु
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Failed to write cx23416 command - too many input arguments (was given %u limit %lu)",
			arg_cnt_send, (दीर्घ अचिन्हित) ARRAY_SIZE(wrData) - 4);
		वापस -EINVAL;
	पूर्ण

	अगर (arg_cnt_recv > (ARRAY_SIZE(rdData) - 4)) अणु
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Failed to write cx23416 command - too many return arguments (was given %u limit %lu)",
			arg_cnt_recv, (दीर्घ अचिन्हित) ARRAY_SIZE(rdData) - 4);
		वापस -EINVAL;
	पूर्ण


	LOCK_TAKE(hdw->ctl_lock); जबतक (1) अणु

		अगर (!hdw->state_encoder_ok) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		retry_flag = 0;
		try_count++;
		ret = 0;
		wrData[0] = 0;
		wrData[1] = cmd;
		wrData[2] = 0;
		wrData[3] = 0x00060000;
		क्रम (idx = 0; idx < arg_cnt_send; idx++) अणु
			wrData[idx+4] = argp[idx];
		पूर्ण
		क्रम (; idx < ARRAY_SIZE(wrData) - 4; idx++) अणु
			wrData[idx+4] = 0;
		पूर्ण

		ret = pvr2_encoder_ग_लिखो_words(hdw,MBOX_BASE,wrData,idx);
		अगर (ret) अवरोध;
		wrData[0] = IVTV_MBOX_DRIVER_DONE|IVTV_MBOX_DRIVER_BUSY;
		ret = pvr2_encoder_ग_लिखो_words(hdw,MBOX_BASE,wrData,1);
		अगर (ret) अवरोध;
		poll_count = 0;
		जबतक (1) अणु
			poll_count++;
			ret = pvr2_encoder_पढ़ो_words(hdw,MBOX_BASE,rdData,
						      arg_cnt_recv+4);
			अगर (ret) अणु
				अवरोध;
			पूर्ण
			अगर (rdData[0] & IVTV_MBOX_FIRMWARE_DONE) अणु
				अवरोध;
			पूर्ण
			अगर (rdData[0] && (poll_count < 1000)) जारी;
			अगर (!rdData[0]) अणु
				retry_flag = !0;
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"Encoder timed out waiting for us; arranging to retry");
			पूर्ण अन्यथा अणु
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"***WARNING*** device's encoder appears to be stuck (status=0x%08x)",
rdData[0]);
			पूर्ण
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Encoder command: 0x%02x",cmd);
			क्रम (idx = 4; idx < arg_cnt_send; idx++) अणु
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"Encoder arg%d: 0x%08x",
					idx-3,wrData[idx]);
			पूर्ण
			ret = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (retry_flag) अणु
			अगर (try_count < 20) जारी;
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Too many retries...");
			ret = -EBUSY;
		पूर्ण
		अगर (ret) अणु
			del_समयr_sync(&hdw->encoder_run_समयr);
			hdw->state_encoder_ok = 0;
			pvr2_trace(PVR2_TRACE_STBITS,
				   "State bit %s <-- %s",
				   "state_encoder_ok",
				   (hdw->state_encoder_ok ? "true" : "false"));
			अगर (hdw->state_encoder_runok) अणु
				hdw->state_encoder_runok = 0;
				pvr2_trace(PVR2_TRACE_STBITS,
				   "State bit %s <-- %s",
					   "state_encoder_runok",
					   (hdw->state_encoder_runok ?
					    "true" : "false"));
			पूर्ण
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Giving up on command.  This is normally recovered via a firmware reload and re-initialization; concern is only warranted if this happens repeatedly and rapidly.");
			अवरोध;
		पूर्ण
		wrData[0] = 0x7;
		क्रम (idx = 0; idx < arg_cnt_recv; idx++) अणु
			argp[idx] = rdData[idx+4];
		पूर्ण

		wrData[0] = 0x0;
		ret = pvr2_encoder_ग_लिखो_words(hdw,MBOX_BASE,wrData,1);
		अवरोध;
	पूर्ण
	LOCK_GIVE(hdw->ctl_lock);

	वापस ret;
पूर्ण


अटल पूर्णांक pvr2_encoder_vcmd(काष्ठा pvr2_hdw *hdw, पूर्णांक cmd,
			     पूर्णांक args, ...)
अणु
	बहु_सूची vl;
	अचिन्हित पूर्णांक idx;
	u32 data[12];

	अगर (args > ARRAY_SIZE(data)) अणु
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Failed to write cx23416 command - too many arguments (was given %u limit %lu)",
			args, (दीर्घ अचिन्हित) ARRAY_SIZE(data));
		वापस -EINVAL;
	पूर्ण

	बहु_शुरू(vl, args);
	क्रम (idx = 0; idx < args; idx++) अणु
		data[idx] = बहु_तर्क(vl, u32);
	पूर्ण
	बहु_पूर्ण(vl);

	वापस pvr2_encoder_cmd(hdw,cmd,args,0,data);
पूर्ण


/* This implements some extra setup क्रम the encoder that seems to be
   specअगरic to the PVR USB2 hardware. */
अटल पूर्णांक pvr2_encoder_prep_config(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक ret = 0;
	पूर्णांक encMisc3Arg = 0;

#अगर 0
	/* This inexplicable bit happens in the Hauppauge winकरोws
	   driver (क्रम both 24xxx and 29xxx devices).  However I
	   currently see no dअगरference in behavior with or without
	   this stuff.  Leave this here as a note of its existence,
	   but करोn't use it. */
	LOCK_TAKE(hdw->ctl_lock); करो अणु
		u32 dat[1];
		dat[0] = 0x80000640;
		pvr2_encoder_ग_लिखो_words(hdw,0x01fe,dat,1);
		pvr2_encoder_ग_लिखो_words(hdw,0x023e,dat,1);
	पूर्ण जबतक(0); LOCK_GIVE(hdw->ctl_lock);
#पूर्ण_अगर

	/* Mike Isely <isely@pobox.com> 26-Jan-2006 The winकरोws driver
	   sends the following list of ENC_MISC commands (क्रम both
	   24xxx and 29xxx devices).  Meanings are not entirely clear,
	   however without the ENC_MISC(3,1) command then we risk
	   अक्रमom perpetual video corruption whenever the video input
	   अवरोधs up क्रम a moment (like when चयनing channels). */


#अगर 0
	/* This ENC_MISC(5,0) command seems to hurt 29xxx sync
	   perक्रमmance on channel changes, but is not a problem on
	   24xxx devices. */
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 5,0,0,0);
#पूर्ण_अगर

	/* This ENC_MISC(3,encMisc3Arg) command is critical - without
	   it there will eventually be video corruption.  Also, the
	   saa7115 हाल is strange - the Winकरोws driver is passing 1
	   regardless of device type but अगर we have 1 क्रम saa7115
	   devices the video turns sluggish.  */
	अगर (hdw->hdw_desc->flag_has_cx25840) अणु
		encMisc3Arg = 1;
	पूर्ण अन्यथा अणु
		encMisc3Arg = 0;
	पूर्ण
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 3,
				 encMisc3Arg,0,0);

	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 8,0,0,0);

#अगर 0
	/* This ENC_MISC(4,1) command is poisonous, so it is commented
	   out.  But I'm leaving it here anyway to करोcument its
	   existence in the Winकरोws driver.  The effect of this
	   command is that apps displaying the stream become sluggish
	   with stuttering video. */
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 4,1,0,0);
#पूर्ण_अगर

	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4, 0,3,0,0);
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC,4,15,0,0,0);

	/* prevent the PTSs from slowly drअगरting away in the generated
	   MPEG stream */
	ret |= pvr2_encoder_vcmd(hdw, CX2341X_ENC_MISC, 2, 4, 1);

	वापस ret;
पूर्ण

पूर्णांक pvr2_encoder_adjust(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक ret;
	ret = cx2341x_update(hdw,pvr2_encoder_cmd,
			     (hdw->enc_cur_valid ? &hdw->enc_cur_state : शून्य),
			     &hdw->enc_ctl_state);
	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Error from cx2341x module code=%d",ret);
	पूर्ण अन्यथा अणु
		hdw->enc_cur_state = hdw->enc_ctl_state;
		hdw->enc_cur_valid = !0;
	पूर्ण
	वापस ret;
पूर्ण


पूर्णांक pvr2_encoder_configure(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक ret;
	पूर्णांक val;
	pvr2_trace(PVR2_TRACE_ENCODER, "pvr2_encoder_configure (cx2341x module)");
	hdw->enc_ctl_state.port = CX2341X_PORT_STREAMING;
	hdw->enc_ctl_state.width = hdw->res_hor_val;
	hdw->enc_ctl_state.height = hdw->res_ver_val;
	hdw->enc_ctl_state.is_50hz = ((hdw->std_mask_cur & V4L2_STD_525_60) ?
				      0 : 1);

	ret = 0;

	ret |= pvr2_encoder_prep_config(hdw);

	/* saa7115: 0xf0 */
	val = 0xf0;
	अगर (hdw->hdw_desc->flag_has_cx25840) अणु
		/* ivtv cx25840: 0x140 */
		val = 0x140;
	पूर्ण

	अगर (!ret) ret = pvr2_encoder_vcmd(
		hdw,CX2341X_ENC_SET_NUM_VSYNC_LINES, 2,
		val, val);

	/* setup firmware to notअगरy us about some events (करोn't know why...) */
	अगर (!ret) ret = pvr2_encoder_vcmd(
		hdw,CX2341X_ENC_SET_EVENT_NOTIFICATION, 4,
		0, 0, 0x10000000, 0xffffffff);

	अगर (!ret) ret = pvr2_encoder_vcmd(
		hdw,CX2341X_ENC_SET_VBI_LINE, 5,
		0xffffffff,0,0,0,0);

	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to configure cx23416");
		वापस ret;
	पूर्ण

	ret = pvr2_encoder_adjust(hdw);
	अगर (ret) वापस ret;

	ret = pvr2_encoder_vcmd(
		hdw, CX2341X_ENC_INITIALIZE_INPUT, 0);

	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to initialize cx23416 video input");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक pvr2_encoder_start(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक status;

	/* unmask some पूर्णांकerrupts */
	pvr2_ग_लिखो_रेजिस्टर(hdw, 0x0048, 0xbfffffff);

	pvr2_encoder_vcmd(hdw,CX2341X_ENC_MUTE_VIDEO,1,
			  hdw->input_val == PVR2_CVAL_INPUT_RADIO ? 1 : 0);

	चयन (hdw->active_stream_type) अणु
	हाल pvr2_config_vbi:
		status = pvr2_encoder_vcmd(hdw,CX2341X_ENC_START_CAPTURE,2,
					   0x01,0x14);
		अवरोध;
	हाल pvr2_config_mpeg:
		status = pvr2_encoder_vcmd(hdw,CX2341X_ENC_START_CAPTURE,2,
					   0,0x13);
		अवरोध;
	शेष: /* Unhandled हालs क्रम now */
		status = pvr2_encoder_vcmd(hdw,CX2341X_ENC_START_CAPTURE,2,
					   0,0x13);
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक pvr2_encoder_stop(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक status;

	/* mask all पूर्णांकerrupts */
	pvr2_ग_लिखो_रेजिस्टर(hdw, 0x0048, 0xffffffff);

	चयन (hdw->active_stream_type) अणु
	हाल pvr2_config_vbi:
		status = pvr2_encoder_vcmd(hdw,CX2341X_ENC_STOP_CAPTURE,3,
					   0x01,0x01,0x14);
		अवरोध;
	हाल pvr2_config_mpeg:
		status = pvr2_encoder_vcmd(hdw,CX2341X_ENC_STOP_CAPTURE,3,
					   0x01,0,0x13);
		अवरोध;
	शेष: /* Unhandled हालs क्रम now */
		status = pvr2_encoder_vcmd(hdw,CX2341X_ENC_STOP_CAPTURE,3,
					   0x01,0,0x13);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण
