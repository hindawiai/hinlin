<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    ivtv firmware functions.
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-mailbox.h"
#समावेश "ivtv-firmware.h"
#समावेश "ivtv-yuv.h"
#समावेश "ivtv-ioctl.h"
#समावेश "ivtv-cards.h"
#समावेश <linux/firmware.h>
#समावेश <media/i2c/saa7127.h>

#घोषणा IVTV_MASK_SPU_ENABLE		0xFFFFFFFE
#घोषणा IVTV_MASK_VPU_ENABLE15		0xFFFFFFF6
#घोषणा IVTV_MASK_VPU_ENABLE16		0xFFFFFFFB
#घोषणा IVTV_CMD_VDM_STOP		0x00000000
#घोषणा IVTV_CMD_AO_STOP		0x00000005
#घोषणा IVTV_CMD_APU_PING		0x00000000
#घोषणा IVTV_CMD_VPU_STOP15		0xFFFFFFFE
#घोषणा IVTV_CMD_VPU_STOP16		0xFFFFFFEE
#घोषणा IVTV_CMD_HW_BLOCKS_RST		0xFFFFFFFF
#घोषणा IVTV_CMD_SPU_STOP		0x00000001
#घोषणा IVTV_CMD_SDRAM_PRECHARGE_INIT	0x0000001A
#घोषणा IVTV_CMD_SDRAM_REFRESH_INIT	0x80000640
#घोषणा IVTV_SDRAM_SLEEPTIME		600

#घोषणा IVTV_DECODE_INIT_MPEG_खाताNAME	"v4l-cx2341x-init.mpg"
#घोषणा IVTV_DECODE_INIT_MPEG_SIZE	(152*1024)

/* Encoder/decoder firmware sizes */
#घोषणा IVTV_FW_ENC_SIZE		(376836)
#घोषणा IVTV_FW_DEC_SIZE		(256*1024)

अटल पूर्णांक load_fw_direct(स्थिर अक्षर *fn, अस्थिर u8 __iomem *mem, काष्ठा ivtv *itv, दीर्घ size)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक retries = 3;

retry:
	अगर (retries && request_firmware(&fw, fn, &itv->pdev->dev) == 0) अणु
		पूर्णांक i;
		अस्थिर u32 __iomem *dst = (अस्थिर u32 __iomem *)mem;
		स्थिर u32 *src = (स्थिर u32 *)fw->data;

		अगर (fw->size != size) अणु
			/* Due to race conditions in firmware loading (esp. with udev <0.95)
			   the wrong file was someबार loaded. So we check filesizes to
			   see अगर at least the right-sized file was loaded. If not, then we
			   retry. */
			IVTV_INFO("Retry: file loaded was not %s (expected size %ld, got %zu)\n", fn, size, fw->size);
			release_firmware(fw);
			retries--;
			जाओ retry;
		पूर्ण
		क्रम (i = 0; i < fw->size; i += 4) अणु
			/* no need क्रम endianness conversion on the ppc */
			__raw_ग_लिखोl(*src, dst);
			dst++;
			src++;
		पूर्ण
		IVTV_INFO("Loaded %s firmware (%zu bytes)\n", fn, fw->size);
		release_firmware(fw);
		वापस size;
	पूर्ण
	IVTV_ERR("Unable to open firmware %s (must be %ld bytes)\n", fn, size);
	IVTV_ERR("Did you put the firmware in the hotplug firmware directory?\n");
	वापस -ENOMEM;
पूर्ण

व्योम ivtv_halt_firmware(काष्ठा ivtv *itv)
अणु
	IVTV_DEBUG_INFO("Preparing for firmware halt.\n");
	अगर (itv->has_cx23415 && itv->dec_mbox.mbox)
		ivtv_vapi(itv, CX2341X_DEC_HALT_FW, 0);
	अगर (itv->enc_mbox.mbox)
		ivtv_vapi(itv, CX2341X_ENC_HALT_FW, 0);

	ivtv_msleep_समयout(10, 0);
	itv->enc_mbox.mbox = itv->dec_mbox.mbox = शून्य;

	IVTV_DEBUG_INFO("Stopping VDM\n");
	ग_लिखो_reg(IVTV_CMD_VDM_STOP, IVTV_REG_VDM);

	IVTV_DEBUG_INFO("Stopping AO\n");
	ग_लिखो_reg(IVTV_CMD_AO_STOP, IVTV_REG_AO);

	IVTV_DEBUG_INFO("pinging (?) APU\n");
	ग_लिखो_reg(IVTV_CMD_APU_PING, IVTV_REG_APU);

	IVTV_DEBUG_INFO("Stopping VPU\n");
	अगर (!itv->has_cx23415)
		ग_लिखो_reg(IVTV_CMD_VPU_STOP16, IVTV_REG_VPU);
	अन्यथा
		ग_लिखो_reg(IVTV_CMD_VPU_STOP15, IVTV_REG_VPU);

	IVTV_DEBUG_INFO("Resetting Hw Blocks\n");
	ग_लिखो_reg(IVTV_CMD_HW_BLOCKS_RST, IVTV_REG_HW_BLOCKS);

	IVTV_DEBUG_INFO("Stopping SPU\n");
	ग_लिखो_reg(IVTV_CMD_SPU_STOP, IVTV_REG_SPU);

	ivtv_msleep_समयout(10, 0);

	IVTV_DEBUG_INFO("init Encoder SDRAM pre-charge\n");
	ग_लिखो_reg(IVTV_CMD_SDRAM_PRECHARGE_INIT, IVTV_REG_ENC_SDRAM_PRECHARGE);

	IVTV_DEBUG_INFO("init Encoder SDRAM refresh to 1us\n");
	ग_लिखो_reg(IVTV_CMD_SDRAM_REFRESH_INIT, IVTV_REG_ENC_SDRAM_REFRESH);

	अगर (itv->has_cx23415) अणु
		IVTV_DEBUG_INFO("init Decoder SDRAM pre-charge\n");
		ग_लिखो_reg(IVTV_CMD_SDRAM_PRECHARGE_INIT, IVTV_REG_DEC_SDRAM_PRECHARGE);

		IVTV_DEBUG_INFO("init Decoder SDRAM refresh to 1us\n");
		ग_लिखो_reg(IVTV_CMD_SDRAM_REFRESH_INIT, IVTV_REG_DEC_SDRAM_REFRESH);
	पूर्ण

	IVTV_DEBUG_INFO("Sleeping for %dms\n", IVTV_SDRAM_SLEEPTIME);
	ivtv_msleep_समयout(IVTV_SDRAM_SLEEPTIME, 0);
पूर्ण

व्योम ivtv_firmware_versions(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];

	/* Encoder */
	ivtv_vapi_result(itv, data, CX2341X_ENC_GET_VERSION, 0);
	IVTV_INFO("Encoder revision: 0x%08x\n", data[0]);

	अगर (data[0] != 0x02060039)
		IVTV_WARN("Recommended firmware version is 0x02060039.\n");

	अगर (itv->has_cx23415) अणु
		/* Decoder */
		ivtv_vapi_result(itv, data, CX2341X_DEC_GET_VERSION, 0);
		IVTV_INFO("Decoder revision: 0x%08x\n", data[0]);
	पूर्ण
पूर्ण

अटल पूर्णांक ivtv_firmware_copy(काष्ठा ivtv *itv)
अणु
	IVTV_DEBUG_INFO("Loading encoder image\n");
	अगर (load_fw_direct(CX2341X_FIRM_ENC_खाताNAME,
		   itv->enc_mem, itv, IVTV_FW_ENC_SIZE) != IVTV_FW_ENC_SIZE) अणु
		IVTV_DEBUG_WARN("failed loading encoder firmware\n");
		वापस -3;
	पूर्ण
	अगर (!itv->has_cx23415)
		वापस 0;

	IVTV_DEBUG_INFO("Loading decoder image\n");
	अगर (load_fw_direct(CX2341X_FIRM_DEC_खाताNAME,
		   itv->dec_mem, itv, IVTV_FW_DEC_SIZE) != IVTV_FW_DEC_SIZE) अणु
		IVTV_DEBUG_WARN("failed loading decoder firmware\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अस्थिर काष्ठा ivtv_mailbox __iomem *ivtv_search_mailbox(स्थिर अस्थिर u8 __iomem *mem, u32 size)
अणु
	पूर्णांक i;

	/* mailbox is preceded by a 16 byte 'magic cookie' starting at a 256-byte
	   address boundary */
	क्रम (i = 0; i < size; i += 0x100) अणु
		अगर (पढ़ोl(mem + i)      == 0x12345678 &&
		    पढ़ोl(mem + i + 4)  == 0x34567812 &&
		    पढ़ोl(mem + i + 8)  == 0x56781234 &&
		    पढ़ोl(mem + i + 12) == 0x78123456) अणु
			वापस (अस्थिर काष्ठा ivtv_mailbox __iomem *)(mem + i + 16);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक ivtv_firmware_init(काष्ठा ivtv *itv)
अणु
	पूर्णांक err;

	ivtv_halt_firmware(itv);

	/* load firmware */
	err = ivtv_firmware_copy(itv);
	अगर (err) अणु
		IVTV_DEBUG_WARN("Error %d loading firmware\n", err);
		वापस err;
	पूर्ण

	/* start firmware */
	ग_लिखो_reg(पढ़ो_reg(IVTV_REG_SPU) & IVTV_MASK_SPU_ENABLE, IVTV_REG_SPU);
	ivtv_msleep_समयout(100, 0);
	अगर (itv->has_cx23415)
		ग_लिखो_reg(पढ़ो_reg(IVTV_REG_VPU) & IVTV_MASK_VPU_ENABLE15, IVTV_REG_VPU);
	अन्यथा
		ग_लिखो_reg(पढ़ो_reg(IVTV_REG_VPU) & IVTV_MASK_VPU_ENABLE16, IVTV_REG_VPU);
	ivtv_msleep_समयout(100, 0);

	/* find mailboxes and ping firmware */
	itv->enc_mbox.mbox = ivtv_search_mailbox(itv->enc_mem, IVTV_ENCODER_SIZE);
	अगर (itv->enc_mbox.mbox == शून्य)
		IVTV_ERR("Encoder mailbox not found\n");
	अन्यथा अगर (ivtv_vapi(itv, CX2341X_ENC_PING_FW, 0)) अणु
		IVTV_ERR("Encoder firmware dead!\n");
		itv->enc_mbox.mbox = शून्य;
	पूर्ण
	अगर (itv->enc_mbox.mbox == शून्य)
		वापस -ENODEV;

	अगर (!itv->has_cx23415)
		वापस 0;

	itv->dec_mbox.mbox = ivtv_search_mailbox(itv->dec_mem, IVTV_DECODER_SIZE);
	अगर (itv->dec_mbox.mbox == शून्य) अणु
		IVTV_ERR("Decoder mailbox not found\n");
	पूर्ण अन्यथा अगर (itv->has_cx23415 && ivtv_vapi(itv, CX2341X_DEC_PING_FW, 0)) अणु
		IVTV_ERR("Decoder firmware dead!\n");
		itv->dec_mbox.mbox = शून्य;
	पूर्ण अन्यथा अणु
		/* Firmware okay, so check yuv output filter table */
		ivtv_yuv_filter_check(itv);
	पूर्ण
	वापस itv->dec_mbox.mbox ? 0 : -ENODEV;
पूर्ण

व्योम ivtv_init_mpeg_decoder(काष्ठा ivtv *itv)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	दीर्घ पढ़ोbytes;
	अस्थिर u8 __iomem *mem_offset;

	data[0] = 0;
	data[1] = itv->cxhdl.width;	/* YUV source width */
	data[2] = itv->cxhdl.height;
	data[3] = itv->cxhdl.audio_properties;	/* Audio settings to use,
							   biपंचांगap. see करोcs. */
	अगर (ivtv_api(itv, CX2341X_DEC_SET_DECODER_SOURCE, 4, data)) अणु
		IVTV_ERR("ivtv_init_mpeg_decoder failed to set decoder source\n");
		वापस;
	पूर्ण

	अगर (ivtv_vapi(itv, CX2341X_DEC_START_PLAYBACK, 2, 0, 1) != 0) अणु
		IVTV_ERR("ivtv_init_mpeg_decoder failed to start playback\n");
		वापस;
	पूर्ण
	ivtv_api_get_data(&itv->dec_mbox, IVTV_MBOX_DMA, 2, data);
	mem_offset = itv->dec_mem + data[1];

	अगर ((पढ़ोbytes = load_fw_direct(IVTV_DECODE_INIT_MPEG_खाताNAME,
		mem_offset, itv, IVTV_DECODE_INIT_MPEG_SIZE)) <= 0) अणु
		IVTV_DEBUG_WARN("failed to read mpeg decoder initialisation file %s\n",
				IVTV_DECODE_INIT_MPEG_खाताNAME);
	पूर्ण अन्यथा अणु
		ivtv_vapi(itv, CX2341X_DEC_SCHED_DMA_FROM_HOST, 3, 0, पढ़ोbytes, 0);
		ivtv_msleep_समयout(100, 0);
	पूर्ण
	ivtv_vapi(itv, CX2341X_DEC_STOP_PLAYBACK, 4, 0, 0, 0, 1);
पूर्ण

/* Try to restart the card & restore previous settings */
अटल पूर्णांक ivtv_firmware_restart(काष्ठा ivtv *itv)
अणु
	पूर्णांक rc = 0;
	v4l2_std_id std;

	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT)
		/* Display test image during restart */
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_routing,
		    SAA7127_INPUT_TYPE_TEST_IMAGE,
		    itv->card->video_outमाला_दो[itv->active_output].video_output,
		    0);

	mutex_lock(&itv->udma.lock);

	rc = ivtv_firmware_init(itv);
	अगर (rc) अणु
		mutex_unlock(&itv->udma.lock);
		वापस rc;
	पूर्ण

	/* Allow settings to reload */
	ivtv_mailbox_cache_invalidate(itv);

	/* Restore encoder video standard */
	std = itv->std;
	itv->std = 0;
	ivtv_s_std_enc(itv, std);

	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) अणु
		ivtv_init_mpeg_decoder(itv);

		/* Restore decoder video standard */
		std = itv->std_out;
		itv->std_out = 0;
		ivtv_s_std_dec(itv, std);

		/* Restore framebuffer अगर active */
		अगर (itv->ivtvfb_restore)
			itv->ivtvfb_restore(itv);

		/* Restore alpha settings */
		ivtv_set_osd_alpha(itv);

		/* Restore normal output */
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_routing,
		    SAA7127_INPUT_TYPE_NORMAL,
		    itv->card->video_outमाला_दो[itv->active_output].video_output,
		    0);
	पूर्ण

	mutex_unlock(&itv->udma.lock);
	वापस rc;
पूर्ण

/* Check firmware running state. The checks fall through
   allowing multiple failures to be logged. */
पूर्णांक ivtv_firmware_check(काष्ठा ivtv *itv, अक्षर *where)
अणु
	पूर्णांक res = 0;

	/* Check encoder is still running */
	अगर (ivtv_vapi(itv, CX2341X_ENC_PING_FW, 0) < 0) अणु
		IVTV_WARN("Encoder has died : %s\n", where);
		res = -1;
	पूर्ण

	/* Also check audio. Only check अगर not in use & encoder is okay */
	अगर (!res && !atomic_पढ़ो(&itv->capturing) &&
	    (!atomic_पढ़ो(&itv->decoding) ||
	     (atomic_पढ़ो(&itv->decoding) < 2 && test_bit(IVTV_F_I_DEC_YUV,
							     &itv->i_flags)))) अणु

		अगर (ivtv_vapi(itv, CX2341X_ENC_MISC, 1, 12) < 0) अणु
			IVTV_WARN("Audio has died (Encoder OK) : %s\n", where);
			res = -2;
		पूर्ण
	पूर्ण

	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) अणु
		/* Second audio check. Skip अगर audio alपढ़ोy failed */
		अगर (res != -2 && पढ़ो_dec(0x100) != पढ़ो_dec(0x104)) अणु
			/* Wait & try again to be certain. */
			ivtv_msleep_समयout(14, 0);
			अगर (पढ़ो_dec(0x100) != पढ़ो_dec(0x104)) अणु
				IVTV_WARN("Audio has died (Decoder) : %s\n",
					  where);
				res = -1;
			पूर्ण
		पूर्ण

		/* Check decoder is still running */
		अगर (ivtv_vapi(itv, CX2341X_DEC_PING_FW, 0) < 0) अणु
			IVTV_WARN("Decoder has died : %s\n", where);
			res = -1;
		पूर्ण
	पूर्ण

	/* If something failed & currently idle, try to reload */
	अगर (res && !atomic_पढ़ो(&itv->capturing) &&
						!atomic_पढ़ो(&itv->decoding)) अणु
		IVTV_INFO("Detected in %s that firmware had failed - Reloading\n",
			  where);
		res = ivtv_firmware_restart(itv);
		/*
		 * Even अगर restarted ok, still संकेत a problem had occurred.
		 * The caller can come through this function again to check
		 * अगर things are really ok after the restart.
		 */
		अगर (!res) अणु
			IVTV_INFO("Firmware restart okay\n");
			res = -EAGAIN;
		पूर्ण अन्यथा अणु
			IVTV_INFO("Firmware restart failed\n");
		पूर्ण
	पूर्ण अन्यथा अगर (res) अणु
		res = -EIO;
	पूर्ण

	वापस res;
पूर्ण

MODULE_FIRMWARE(CX2341X_FIRM_ENC_खाताNAME);
MODULE_FIRMWARE(CX2341X_FIRM_DEC_खाताNAME);
MODULE_FIRMWARE(IVTV_DECODE_INIT_MPEG_खाताNAME);
