<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    mailbox functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-mailbox.h"

/* Firmware mailbox flags*/
#घोषणा IVTV_MBOX_FIRMWARE_DONE 0x00000004
#घोषणा IVTV_MBOX_DRIVER_DONE   0x00000002
#घोषणा IVTV_MBOX_DRIVER_BUSY   0x00000001
#घोषणा IVTV_MBOX_FREE		0x00000000

/* Firmware mailbox standard समयout */
#घोषणा IVTV_API_STD_TIMEOUT	0x02000000

#घोषणा API_CACHE	 (1 << 0)	/* Allow the command to be stored in the cache */
#घोषणा API_RESULT	 (1 << 1)	/* Allow 1 second क्रम this cmd to end */
#घोषणा API_FAST_RESULT	 (3 << 1)	/* Allow 0.1 second क्रम this cmd to end */
#घोषणा API_DMA		 (1 << 3)	/* DMA mailbox, has special handling */
#घोषणा API_HIGH_VOL	 (1 << 5)	/* High volume command (i.e. called during encoding or decoding) */
#घोषणा API_NO_WAIT_MB	 (1 << 4)	/* Command may not रुको क्रम a मुक्त mailbox */
#घोषणा API_NO_WAIT_RES	 (1 << 5)	/* Command may not रुको क्रम the result */
#घोषणा API_NO_POLL	 (1 << 6)	/* Aव्योम poपूर्णांकless polling */

काष्ठा ivtv_api_info अणु
	पूर्णांक flags;		/* Flags, see above */
	स्थिर अक्षर *name;	/* The name of the command */
पूर्ण;

#घोषणा API_ENTRY(x, f) [x] = अणु (f), #x पूर्ण

अटल स्थिर काष्ठा ivtv_api_info api_info[256] = अणु
	/* MPEG encoder API */
	API_ENTRY(CX2341X_ENC_PING_FW,			API_FAST_RESULT),
	API_ENTRY(CX2341X_ENC_START_CAPTURE,		API_RESULT | API_NO_POLL),
	API_ENTRY(CX2341X_ENC_STOP_CAPTURE,		API_RESULT),
	API_ENTRY(CX2341X_ENC_SET_AUDIO_ID,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_VIDEO_ID,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_PCR_ID,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_FRAME_RATE,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_FRAME_SIZE,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_BIT_RATE,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_GOP_PROPERTIES,	API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_ASPECT_RATIO,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_DNR_FILTER_MODE,	API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_DNR_FILTER_PROPS,	API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_CORING_LEVELS,	API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_SPATIAL_FILTER_TYPE,	API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_VBI_LINE,		API_RESULT),
	API_ENTRY(CX2341X_ENC_SET_STREAM_TYPE,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_OUTPUT_PORT,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_AUDIO_PROPERTIES,	API_CACHE),
	API_ENTRY(CX2341X_ENC_HALT_FW,			API_FAST_RESULT),
	API_ENTRY(CX2341X_ENC_GET_VERSION,		API_FAST_RESULT),
	API_ENTRY(CX2341X_ENC_SET_GOP_CLOSURE,		API_CACHE),
	API_ENTRY(CX2341X_ENC_GET_SEQ_END,		API_RESULT),
	API_ENTRY(CX2341X_ENC_SET_PGM_INDEX_INFO,	API_FAST_RESULT),
	API_ENTRY(CX2341X_ENC_SET_VBI_CONFIG,		API_RESULT),
	API_ENTRY(CX2341X_ENC_SET_DMA_BLOCK_SIZE,	API_CACHE),
	API_ENTRY(CX2341X_ENC_GET_PREV_DMA_INFO_MB_10,	API_FAST_RESULT),
	API_ENTRY(CX2341X_ENC_GET_PREV_DMA_INFO_MB_9,	API_FAST_RESULT),
	API_ENTRY(CX2341X_ENC_SCHED_DMA_TO_HOST,	API_DMA | API_HIGH_VOL),
	API_ENTRY(CX2341X_ENC_INITIALIZE_INPUT,		API_RESULT),
	API_ENTRY(CX2341X_ENC_SET_FRAME_DROP_RATE,	API_CACHE),
	API_ENTRY(CX2341X_ENC_PAUSE_ENCODER,		API_RESULT),
	API_ENTRY(CX2341X_ENC_REFRESH_INPUT,		API_NO_WAIT_MB | API_HIGH_VOL),
	API_ENTRY(CX2341X_ENC_SET_COPYRIGHT,		API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_EVENT_NOTIFICATION,	API_RESULT),
	API_ENTRY(CX2341X_ENC_SET_NUM_VSYNC_LINES,	API_CACHE),
	API_ENTRY(CX2341X_ENC_SET_PLACEHOLDER,		API_CACHE),
	API_ENTRY(CX2341X_ENC_MUTE_VIDEO,		API_RESULT),
	API_ENTRY(CX2341X_ENC_MUTE_AUDIO,		API_RESULT),
	API_ENTRY(CX2341X_ENC_SET_VERT_CROP_LINE,	API_FAST_RESULT),
	API_ENTRY(CX2341X_ENC_MISC,			API_FAST_RESULT),
	/* Obsolete PULLDOWN API command */
	API_ENTRY(0xb1,					API_CACHE),

	/* MPEG decoder API */
	API_ENTRY(CX2341X_DEC_PING_FW,			API_FAST_RESULT),
	API_ENTRY(CX2341X_DEC_START_PLAYBACK,		API_RESULT | API_NO_POLL),
	API_ENTRY(CX2341X_DEC_STOP_PLAYBACK,		API_RESULT),
	API_ENTRY(CX2341X_DEC_SET_PLAYBACK_SPEED,	API_RESULT),
	API_ENTRY(CX2341X_DEC_STEP_VIDEO,		API_RESULT),
	API_ENTRY(CX2341X_DEC_SET_DMA_BLOCK_SIZE,	API_CACHE),
	API_ENTRY(CX2341X_DEC_GET_XFER_INFO,		API_FAST_RESULT),
	API_ENTRY(CX2341X_DEC_GET_DMA_STATUS,		API_FAST_RESULT),
	API_ENTRY(CX2341X_DEC_SCHED_DMA_FROM_HOST,	API_DMA | API_HIGH_VOL),
	API_ENTRY(CX2341X_DEC_PAUSE_PLAYBACK,		API_RESULT),
	API_ENTRY(CX2341X_DEC_HALT_FW,			API_FAST_RESULT),
	API_ENTRY(CX2341X_DEC_SET_STANDARD,		API_CACHE),
	API_ENTRY(CX2341X_DEC_GET_VERSION,		API_FAST_RESULT),
	API_ENTRY(CX2341X_DEC_SET_STREAM_INPUT,		API_CACHE),
	API_ENTRY(CX2341X_DEC_GET_TIMING_INFO,		API_RESULT /*| API_NO_WAIT_RES*/),
	API_ENTRY(CX2341X_DEC_SET_AUDIO_MODE,		API_CACHE),
	API_ENTRY(CX2341X_DEC_SET_EVENT_NOTIFICATION,	API_RESULT),
	API_ENTRY(CX2341X_DEC_SET_DISPLAY_BUFFERS,	API_CACHE),
	API_ENTRY(CX2341X_DEC_EXTRACT_VBI,		API_RESULT),
	API_ENTRY(CX2341X_DEC_SET_DECODER_SOURCE,	API_FAST_RESULT),
	API_ENTRY(CX2341X_DEC_SET_PREBUFFERING,		API_CACHE),

	/* OSD API */
	API_ENTRY(CX2341X_OSD_GET_FRAMEBUFFER,		API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_GET_PIXEL_FORMAT,		API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_SET_PIXEL_FORMAT,		API_CACHE),
	API_ENTRY(CX2341X_OSD_GET_STATE,		API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_SET_STATE,		API_CACHE),
	API_ENTRY(CX2341X_OSD_GET_OSD_COORDS,		API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_SET_OSD_COORDS,		API_CACHE),
	API_ENTRY(CX2341X_OSD_GET_SCREEN_COORDS,	API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_SET_SCREEN_COORDS,	API_CACHE),
	API_ENTRY(CX2341X_OSD_GET_GLOBAL_ALPHA,		API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_SET_GLOBAL_ALPHA,		API_CACHE),
	API_ENTRY(CX2341X_OSD_SET_BLEND_COORDS,		API_CACHE),
	API_ENTRY(CX2341X_OSD_GET_FLICKER_STATE,	API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_SET_FLICKER_STATE,	API_CACHE),
	API_ENTRY(CX2341X_OSD_BLT_COPY,			API_RESULT),
	API_ENTRY(CX2341X_OSD_BLT_FILL,			API_RESULT),
	API_ENTRY(CX2341X_OSD_BLT_TEXT,			API_RESULT),
	API_ENTRY(CX2341X_OSD_SET_FRAMEBUFFER_WINDOW,	API_CACHE),
	API_ENTRY(CX2341X_OSD_SET_CHROMA_KEY,		API_CACHE),
	API_ENTRY(CX2341X_OSD_GET_ALPHA_CONTENT_INDEX,	API_FAST_RESULT),
	API_ENTRY(CX2341X_OSD_SET_ALPHA_CONTENT_INDEX,	API_CACHE)
पूर्ण;

अटल पूर्णांक try_mailbox(काष्ठा ivtv *itv, काष्ठा ivtv_mailbox_data *mbdata, पूर्णांक mb)
अणु
	u32 flags = पढ़ोl(&mbdata->mbox[mb].flags);
	पूर्णांक is_मुक्त = flags == IVTV_MBOX_FREE || (flags & IVTV_MBOX_FIRMWARE_DONE);

	/* अगर the mailbox is मुक्त, then try to claim it */
	अगर (is_मुक्त && !test_and_set_bit(mb, &mbdata->busy)) अणु
		ग_लिखो_sync(IVTV_MBOX_DRIVER_BUSY, &mbdata->mbox[mb].flags);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Try to find a मुक्त mailbox. Note mailbox 0 is reserved क्रम DMA and so is not
   attempted here. */
अटल पूर्णांक get_mailbox(काष्ठा ivtv *itv, काष्ठा ivtv_mailbox_data *mbdata, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ then = jअगरfies;
	पूर्णांक i, mb;
	पूर्णांक max_mbox = mbdata->max_mbox;
	पूर्णांक retries = 100;

	/* All slow commands use the same mailbox, serializing them and also
	   leaving the other mailbox मुक्त क्रम simple fast commands. */
	अगर ((flags & API_FAST_RESULT) == API_RESULT)
		max_mbox = 1;

	/* find मुक्त non-DMA mailbox */
	क्रम (i = 0; i < retries; i++) अणु
		क्रम (mb = 1; mb <= max_mbox; mb++)
			अगर (try_mailbox(itv, mbdata, mb))
				वापस mb;

		/* Sleep beक्रमe a retry, अगर not atomic */
		अगर (!(flags & API_NO_WAIT_MB)) अणु
			अगर (समय_after(jअगरfies,
				       then + msecs_to_jअगरfies(10*retries)))
			       अवरोध;
			ivtv_msleep_समयout(10, 0);
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम ग_लिखो_mailbox(अस्थिर काष्ठा ivtv_mailbox __iomem *mbox, पूर्णांक cmd, पूर्णांक args, u32 data[])
अणु
	पूर्णांक i;

	ग_लिखो_sync(cmd, &mbox->cmd);
	ग_लिखो_sync(IVTV_API_STD_TIMEOUT, &mbox->समयout);

	क्रम (i = 0; i < CX2341X_MBOX_MAX_DATA; i++)
		ग_लिखो_sync(data[i], &mbox->data[i]);

	ग_लिखो_sync(IVTV_MBOX_DRIVER_DONE | IVTV_MBOX_DRIVER_BUSY, &mbox->flags);
पूर्ण

अटल व्योम clear_all_mailboxes(काष्ठा ivtv *itv, काष्ठा ivtv_mailbox_data *mbdata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= mbdata->max_mbox; i++) अणु
		IVTV_DEBUG_WARN("Clearing mailbox %d: cmd 0x%08x flags 0x%08x\n",
			i, पढ़ोl(&mbdata->mbox[i].cmd), पढ़ोl(&mbdata->mbox[i].flags));
		ग_लिखो_sync(0, &mbdata->mbox[i].flags);
		clear_bit(i, &mbdata->busy);
	पूर्ण
पूर्ण

अटल पूर्णांक ivtv_api_call(काष्ठा ivtv *itv, पूर्णांक cmd, पूर्णांक args, u32 data[])
अणु
	काष्ठा ivtv_mailbox_data *mbdata = (cmd >= 128) ? &itv->enc_mbox : &itv->dec_mbox;
	अस्थिर काष्ठा ivtv_mailbox __iomem *mbox;
	पूर्णांक api_समयout = msecs_to_jअगरfies(1000);
	पूर्णांक flags, mb, i;
	अचिन्हित दीर्घ then;

	/* sanity checks */
	अगर (शून्य == mbdata) अणु
		IVTV_ERR("No mailbox allocated\n");
		वापस -ENODEV;
	पूर्ण
	अगर (args < 0 || args > CX2341X_MBOX_MAX_DATA ||
	    cmd < 0 || cmd > 255 || api_info[cmd].name == शून्य) अणु
		IVTV_ERR("Invalid MB call: cmd = 0x%02x, args = %d\n", cmd, args);
		वापस -EINVAL;
	पूर्ण

	अगर (api_info[cmd].flags & API_HIGH_VOL) अणु
	    IVTV_DEBUG_HI_MB("MB Call: %s\n", api_info[cmd].name);
	पूर्ण
	अन्यथा अणु
	    IVTV_DEBUG_MB("MB Call: %s\n", api_info[cmd].name);
	पूर्ण

	/* clear possibly uninitialized part of data array */
	क्रम (i = args; i < CX2341X_MBOX_MAX_DATA; i++)
		data[i] = 0;

	/* If this command was issued within the last 30 minutes and with identical
	   data, then just वापस 0 as there is no need to issue this command again.
	   Just an optimization to prevent unnecessary use of mailboxes. */
	अगर (itv->api_cache[cmd].last_jअगरfies &&
	    समय_beक्रमe(jअगरfies,
			itv->api_cache[cmd].last_jअगरfies +
			msecs_to_jअगरfies(1800000)) &&
	    !स_भेद(data, itv->api_cache[cmd].data, माप(itv->api_cache[cmd].data))) अणु
		itv->api_cache[cmd].last_jअगरfies = jअगरfies;
		वापस 0;
	पूर्ण

	flags = api_info[cmd].flags;

	अगर (flags & API_DMA) अणु
		क्रम (i = 0; i < 100; i++) अणु
			mb = i % (mbdata->max_mbox + 1);
			अगर (try_mailbox(itv, mbdata, mb)) अणु
				ग_लिखो_mailbox(&mbdata->mbox[mb], cmd, args, data);
				clear_bit(mb, &mbdata->busy);
				वापस 0;
			पूर्ण
			IVTV_DEBUG_WARN("%s: mailbox %d not free %08x\n",
					api_info[cmd].name, mb, पढ़ोl(&mbdata->mbox[mb].flags));
		पूर्ण
		IVTV_WARN("Could not find free DMA mailbox for %s\n", api_info[cmd].name);
		clear_all_mailboxes(itv, mbdata);
		वापस -EBUSY;
	पूर्ण

	अगर ((flags & API_FAST_RESULT) == API_FAST_RESULT)
		api_समयout = msecs_to_jअगरfies(100);

	mb = get_mailbox(itv, mbdata, flags);
	अगर (mb < 0) अणु
		IVTV_DEBUG_WARN("No free mailbox found (%s)\n", api_info[cmd].name);
		clear_all_mailboxes(itv, mbdata);
		वापस -EBUSY;
	पूर्ण
	mbox = &mbdata->mbox[mb];
	ग_लिखो_mailbox(mbox, cmd, args, data);
	अगर (flags & API_CACHE) अणु
		स_नकल(itv->api_cache[cmd].data, data, माप(itv->api_cache[cmd].data));
		itv->api_cache[cmd].last_jअगरfies = jअगरfies;
	पूर्ण
	अगर ((flags & API_RESULT) == 0) अणु
		clear_bit(mb, &mbdata->busy);
		वापस 0;
	पूर्ण

	/* Get results */
	then = jअगरfies;

	अगर (!(flags & API_NO_POLL)) अणु
		/* First try to poll, then चयन to delays */
		क्रम (i = 0; i < 100; i++) अणु
			अगर (पढ़ोl(&mbox->flags) & IVTV_MBOX_FIRMWARE_DONE)
				अवरोध;
		पूर्ण
	पूर्ण
	जबतक (!(पढ़ोl(&mbox->flags) & IVTV_MBOX_FIRMWARE_DONE)) अणु
		अगर (समय_after(jअगरfies, then + api_समयout)) अणु
			IVTV_DEBUG_WARN("Could not get result (%s)\n", api_info[cmd].name);
			/* reset the mailbox, but it is likely too late alपढ़ोy */
			ग_लिखो_sync(0, &mbox->flags);
			clear_bit(mb, &mbdata->busy);
			वापस -EIO;
		पूर्ण
		अगर (flags & API_NO_WAIT_RES)
			mdelay(1);
		अन्यथा
			ivtv_msleep_समयout(1, 0);
	पूर्ण
	अगर (समय_after(jअगरfies, then + msecs_to_jअगरfies(100)))
		IVTV_DEBUG_WARN("%s took %u jiffies\n",
				api_info[cmd].name,
				jअगरfies_to_msecs(jअगरfies - then));

	क्रम (i = 0; i < CX2341X_MBOX_MAX_DATA; i++)
		data[i] = पढ़ोl(&mbox->data[i]);
	ग_लिखो_sync(0, &mbox->flags);
	clear_bit(mb, &mbdata->busy);
	वापस 0;
पूर्ण

पूर्णांक ivtv_api(काष्ठा ivtv *itv, पूर्णांक cmd, पूर्णांक args, u32 data[])
अणु
	पूर्णांक res = ivtv_api_call(itv, cmd, args, data);

	/* Allow a single retry, probably alपढ़ोy too late though.
	   If there is no मुक्त mailbox then that is usually an indication
	   of a more serious problem. */
	वापस (res == -EBUSY) ? ivtv_api_call(itv, cmd, args, data) : res;
पूर्ण

पूर्णांक ivtv_api_func(व्योम *priv, u32 cmd, पूर्णांक in, पूर्णांक out, u32 data[CX2341X_MBOX_MAX_DATA])
अणु
	वापस ivtv_api(priv, cmd, in, data);
पूर्ण

पूर्णांक ivtv_vapi_result(काष्ठा ivtv *itv, u32 data[CX2341X_MBOX_MAX_DATA], पूर्णांक cmd, पूर्णांक args, ...)
अणु
	बहु_सूची ap;
	पूर्णांक i;

	बहु_शुरू(ap, args);
	क्रम (i = 0; i < args; i++) अणु
		data[i] = बहु_तर्क(ap, u32);
	पूर्ण
	बहु_पूर्ण(ap);
	वापस ivtv_api(itv, cmd, args, data);
पूर्ण

पूर्णांक ivtv_vapi(काष्ठा ivtv *itv, पूर्णांक cmd, पूर्णांक args, ...)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	बहु_सूची ap;
	पूर्णांक i;

	बहु_शुरू(ap, args);
	क्रम (i = 0; i < args; i++) अणु
		data[i] = बहु_तर्क(ap, u32);
	पूर्ण
	बहु_पूर्ण(ap);
	वापस ivtv_api(itv, cmd, args, data);
पूर्ण

/* This one is क्रम stuff that can't sleep.. irq handlers, etc.. */
व्योम ivtv_api_get_data(काष्ठा ivtv_mailbox_data *mbdata, पूर्णांक mb,
		       पूर्णांक argc, u32 data[])
अणु
	अस्थिर u32 __iomem *p = mbdata->mbox[mb].data;
	पूर्णांक i;
	क्रम (i = 0; i < argc; i++, p++)
		data[i] = पढ़ोl(p);
पूर्ण

/* Wipe api cache */
व्योम ivtv_mailbox_cache_invalidate(काष्ठा ivtv *itv)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 256; i++)
		itv->api_cache[i].last_jअगरfies = 0;
पूर्ण
