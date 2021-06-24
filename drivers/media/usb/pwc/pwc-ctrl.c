<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Driver क्रम Philips webcam
   Functions that send various control messages to the webcam, including
   video modes.
   (C) 1999-2003 Nemosoft Unv.
   (C) 2004-2006 Luc Saillard (luc@saillard.org)
   (C) 2011 Hans de Goede <hdegoede@redhat.com>

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.

*/

/*
   Changes
   2001/08/03  Alvaraकरो   Added methods क्रम changing white balance and
			  red/green gains
 */

/* Control functions क्रम the cam; brightness, contrast, video mode, etc. */

#अगर_घोषित __KERNEL__
#समावेश <linux/uaccess.h>
#पूर्ण_अगर
#समावेश <यंत्र/त्रुटिसं.स>

#समावेश "pwc.h"
#समावेश "pwc-kiara.h"
#समावेश "pwc-timon.h"
#समावेश "pwc-dec1.h"
#समावेश "pwc-dec23.h"

/* Selectors क्रम status controls used only in this file */
#घोषणा GET_STATUS_B00				0x0B00
#घोषणा SENSOR_TYPE_FORMATTER1			0x0C00
#घोषणा GET_STATUS_3000				0x3000
#घोषणा READ_RAW_Y_MEAN_FORMATTER		0x3100
#घोषणा SET_POWER_SAVE_MODE_FORMATTER		0x3200
#घोषणा MIRROR_IMAGE_FORMATTER			0x3300
#घोषणा LED_FORMATTER				0x3400
#घोषणा LOWLIGHT				0x3500
#घोषणा GET_STATUS_3600				0x3600
#घोषणा SENSOR_TYPE_FORMATTER2			0x3700
#घोषणा GET_STATUS_3800				0x3800
#घोषणा GET_STATUS_4000				0x4000
#घोषणा GET_STATUS_4100				0x4100	/* Get */
#घोषणा CTL_STATUS_4200				0x4200	/* [GS] 1 */

/* Formatters क्रम the Video Endpoपूर्णांक controls [GS]ET_EP_STREAM_CTL */
#घोषणा VIDEO_OUTPUT_CONTROL_FORMATTER		0x0100

अटल स्थिर अक्षर *size2name[PSZ_MAX] =
अणु
	"subQCIF",
	"QSIF",
	"QCIF",
	"SIF",
	"CIF",
	"VGA",
पूर्ण;

/********/

/* Entries क्रम the Nala (645/646) camera; the Nala करोesn't have compression
   preferences, so you either get compressed or non-compressed streams.

   An alternate value of 0 means this mode is not available at all.
 */

#घोषणा PWC_FPS_MAX_NALA 8

काष्ठा Nala_table_entry अणु
	अक्षर alternate;			/* USB alternate setting */
	पूर्णांक compressed;			/* Compressed yes/no */

	अचिन्हित अक्षर mode[3];		/* precomputed mode table */
पूर्ण;

अटल अचिन्हित पूर्णांक Nala_fps_vector[PWC_FPS_MAX_NALA] = अणु 4, 5, 7, 10, 12, 15, 20, 24 पूर्ण;

अटल काष्ठा Nala_table_entry Nala_table[PSZ_MAX][PWC_FPS_MAX_NALA] =
अणु
#समावेश "pwc-nala.h"
पूर्ण;

/****************************************************************************/

अटल पूर्णांक recv_control_msg(काष्ठा pwc_device *pdev,
	u8 request, u16 value, पूर्णांक recv_count)
अणु
	पूर्णांक rc;

	rc = usb_control_msg(pdev->udev, usb_rcvctrlpipe(pdev->udev, 0),
		request,
		USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		value, pdev->vcपूर्णांकerface,
		pdev->ctrl_buf, recv_count, USB_CTRL_GET_TIMEOUT);
	अगर (rc < 0)
		PWC_ERROR("recv_control_msg error %d req %02x val %04x\n",
			  rc, request, value);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक send_video_command(काष्ठा pwc_device *pdev,
	पूर्णांक index, स्थिर अचिन्हित अक्षर *buf, पूर्णांक buflen)
अणु
	पूर्णांक rc;

	स_नकल(pdev->ctrl_buf, buf, buflen);

	rc = usb_control_msg(pdev->udev, usb_sndctrlpipe(pdev->udev, 0),
			SET_EP_STREAM_CTL,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			VIDEO_OUTPUT_CONTROL_FORMATTER, index,
			pdev->ctrl_buf, buflen, USB_CTRL_SET_TIMEOUT);
	अगर (rc >= 0)
		स_नकल(pdev->cmd_buf, buf, buflen);
	अन्यथा
		PWC_ERROR("send_video_command error %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक send_control_msg(काष्ठा pwc_device *pdev,
	u8 request, u16 value, व्योम *buf, पूर्णांक buflen)
अणु
	वापस usb_control_msg(pdev->udev, usb_sndctrlpipe(pdev->udev, 0),
			request,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, pdev->vcपूर्णांकerface,
			buf, buflen, USB_CTRL_SET_TIMEOUT);
पूर्ण

अटल पूर्णांक set_video_mode_Nala(काष्ठा pwc_device *pdev, पूर्णांक size, पूर्णांक pixfmt,
			       पूर्णांक frames, पूर्णांक *compression, पूर्णांक send_to_cam)
अणु
	पूर्णांक fps, ret = 0;
	काष्ठा Nala_table_entry *pEntry;
	पूर्णांक frames2frames[31] =
	अणु /* बंदst match of framerate */
	   0,  0,  0,  0,  4,  /*  0-4  */
	   5,  5,  7,  7, 10,  /*  5-9  */
	  10, 10, 12, 12, 15,  /* 10-14 */
	  15, 15, 15, 20, 20,  /* 15-19 */
	  20, 20, 20, 24, 24,  /* 20-24 */
	  24, 24, 24, 24, 24,  /* 25-29 */
	  24                   /* 30    */
	पूर्ण;
	पूर्णांक frames2table[31] =
	अणु 0, 0, 0, 0, 0, /*  0-4  */
	  1, 1, 1, 2, 2, /*  5-9  */
	  3, 3, 4, 4, 4, /* 10-14 */
	  5, 5, 5, 5, 5, /* 15-19 */
	  6, 6, 6, 6, 7, /* 20-24 */
	  7, 7, 7, 7, 7, /* 25-29 */
	  7              /* 30    */
	पूर्ण;

	अगर (size < 0 || size > PSZ_CIF)
		वापस -EINVAL;
	अगर (frames < 4)
		frames = 4;
	अन्यथा अगर (size > PSZ_QCIF && frames > 15)
		frames = 15;
	अन्यथा अगर (frames > 25)
		frames = 25;
	frames = frames2frames[frames];
	fps = frames2table[frames];
	pEntry = &Nala_table[size][fps];
	अगर (pEntry->alternate == 0)
		वापस -EINVAL;

	अगर (send_to_cam)
		ret = send_video_command(pdev, pdev->vendpoपूर्णांक,
					 pEntry->mode, 3);
	अगर (ret < 0)
		वापस ret;

	अगर (pEntry->compressed && pixfmt == V4L2_PIX_FMT_YUV420)
		pwc_dec1_init(pdev, pEntry->mode);

	/* Set various parameters */
	pdev->pixfmt = pixfmt;
	pdev->vframes = frames;
	pdev->valternate = pEntry->alternate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->frame_size = (pdev->width * pdev->height * 3) / 2;
	अगर (pEntry->compressed) अणु
		अगर (pdev->release < 5) अणु /* 4 fold compression */
			pdev->vbandlength = 528;
			pdev->frame_size /= 4;
		पूर्ण
		अन्यथा अणु
			pdev->vbandlength = 704;
			pdev->frame_size /= 3;
		पूर्ण
	पूर्ण
	अन्यथा
		pdev->vbandlength = 0;

	/* Let pwc-अगर.c:isoc_init know we करोn't support higher compression */
	*compression = 3;

	वापस 0;
पूर्ण


अटल पूर्णांक set_video_mode_Timon(काष्ठा pwc_device *pdev, पूर्णांक size, पूर्णांक pixfmt,
				पूर्णांक frames, पूर्णांक *compression, पूर्णांक send_to_cam)
अणु
	स्थिर काष्ठा Timon_table_entry *pChoose;
	पूर्णांक fps, ret = 0;

	अगर (size >= PSZ_MAX || *compression < 0 || *compression > 3)
		वापस -EINVAL;
	अगर (frames < 5)
		frames = 5;
	अन्यथा अगर (size == PSZ_VGA && frames > 15)
		frames = 15;
	अन्यथा अगर (frames > 30)
		frames = 30;
	fps = (frames / 5) - 1;

	/* Find a supported framerate with progressively higher compression */
	करो अणु
		pChoose = &Timon_table[size][fps][*compression];
		अगर (pChoose->alternate != 0)
			अवरोध;
		(*compression)++;
	पूर्ण जबतक (*compression <= 3);

	अगर (pChoose->alternate == 0)
		वापस -ENOENT; /* Not supported. */

	अगर (send_to_cam)
		ret = send_video_command(pdev, pdev->vendpoपूर्णांक,
					 pChoose->mode, 13);
	अगर (ret < 0)
		वापस ret;

	अगर (pChoose->bandlength > 0 && pixfmt == V4L2_PIX_FMT_YUV420)
		pwc_dec23_init(pdev, pChoose->mode);

	/* Set various parameters */
	pdev->pixfmt = pixfmt;
	pdev->vframes = (fps + 1) * 5;
	pdev->valternate = pChoose->alternate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->vbandlength = pChoose->bandlength;
	अगर (pChoose->bandlength > 0)
		pdev->frame_size = (pChoose->bandlength * pdev->height) / 4;
	अन्यथा
		pdev->frame_size = (pdev->width * pdev->height * 12) / 8;
	वापस 0;
पूर्ण


अटल पूर्णांक set_video_mode_Kiara(काष्ठा pwc_device *pdev, पूर्णांक size, पूर्णांक pixfmt,
				पूर्णांक frames, पूर्णांक *compression, पूर्णांक send_to_cam)
अणु
	स्थिर काष्ठा Kiara_table_entry *pChoose;
	पूर्णांक fps, ret = 0;

	अगर (size >= PSZ_MAX || *compression < 0 || *compression > 3)
		वापस -EINVAL;
	अगर (frames < 5)
		frames = 5;
	अन्यथा अगर (size == PSZ_VGA && frames > 15)
		frames = 15;
	अन्यथा अगर (frames > 30)
		frames = 30;
	fps = (frames / 5) - 1;

	/* Find a supported framerate with progressively higher compression */
	करो अणु
		pChoose = &Kiara_table[size][fps][*compression];
		अगर (pChoose->alternate != 0)
			अवरोध;
		(*compression)++;
	पूर्ण जबतक (*compression <= 3);

	अगर (pChoose->alternate == 0)
		वापस -ENOENT; /* Not supported. */

	/* Firmware bug: video endpoपूर्णांक is 5, but commands are sent to endpoपूर्णांक 4 */
	अगर (send_to_cam)
		ret = send_video_command(pdev, 4, pChoose->mode, 12);
	अगर (ret < 0)
		वापस ret;

	अगर (pChoose->bandlength > 0 && pixfmt == V4L2_PIX_FMT_YUV420)
		pwc_dec23_init(pdev, pChoose->mode);

	/* All set and go */
	pdev->pixfmt = pixfmt;
	pdev->vframes = (fps + 1) * 5;
	pdev->valternate = pChoose->alternate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->vbandlength = pChoose->bandlength;
	अगर (pdev->vbandlength > 0)
		pdev->frame_size = (pdev->vbandlength * pdev->height) / 4;
	अन्यथा
		pdev->frame_size = (pdev->width * pdev->height * 12) / 8;
	PWC_TRACE("frame_size=%d, vframes=%d, vsize=%d, vbandlength=%d\n",
	    pdev->frame_size, pdev->vframes, size, pdev->vbandlength);
	वापस 0;
पूर्ण

पूर्णांक pwc_set_video_mode(काष्ठा pwc_device *pdev, पूर्णांक width, पूर्णांक height,
	पूर्णांक pixfmt, पूर्णांक frames, पूर्णांक *compression, पूर्णांक send_to_cam)
अणु
	पूर्णांक ret, size;

	PWC_DEBUG_FLOW("set_video_mode(%dx%d @ %d, pixfmt %08x).\n",
		       width, height, frames, pixfmt);
	size = pwc_get_size(pdev, width, height);
	PWC_TRACE("decode_size = %d.\n", size);

	अगर (DEVICE_USE_CODEC1(pdev->type)) अणु
		ret = set_video_mode_Nala(pdev, size, pixfmt, frames,
					  compression, send_to_cam);
	पूर्ण अन्यथा अगर (DEVICE_USE_CODEC3(pdev->type)) अणु
		ret = set_video_mode_Kiara(pdev, size, pixfmt, frames,
					   compression, send_to_cam);
	पूर्ण अन्यथा अणु
		ret = set_video_mode_Timon(pdev, size, pixfmt, frames,
					   compression, send_to_cam);
	पूर्ण
	अगर (ret < 0) अणु
		PWC_ERROR("Failed to set video mode %s@%d fps; return code = %d\n", size2name[size], frames, ret);
		वापस ret;
	पूर्ण
	pdev->frame_total_size = pdev->frame_size + pdev->frame_header_size + pdev->frame_trailer_size;
	PWC_DEBUG_SIZE("Set resolution to %dx%d\n", pdev->width, pdev->height);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pwc_get_fps_Nala(काष्ठा pwc_device *pdev, अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PWC_FPS_MAX_NALA; i++) अणु
		अगर (Nala_table[size][i].alternate) अणु
			अगर (index--==0) वापस Nala_fps_vector[i];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pwc_get_fps_Kiara(काष्ठा pwc_device *pdev, अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PWC_FPS_MAX_KIARA; i++) अणु
		अगर (Kiara_table[size][i][3].alternate) अणु
			अगर (index--==0) वापस Kiara_fps_vector[i];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pwc_get_fps_Timon(काष्ठा pwc_device *pdev, अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i=0; i < PWC_FPS_MAX_TIMON; i++) अणु
		अगर (Timon_table[size][i][3].alternate) अणु
			अगर (index--==0) वापस Timon_fps_vector[i];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक pwc_get_fps(काष्ठा pwc_device *pdev, अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक ret;

	अगर (DEVICE_USE_CODEC1(pdev->type)) अणु
		ret = pwc_get_fps_Nala(pdev, index, size);

	पूर्ण अन्यथा अगर (DEVICE_USE_CODEC3(pdev->type)) अणु
		ret = pwc_get_fps_Kiara(pdev, index, size);

	पूर्ण अन्यथा अणु
		ret = pwc_get_fps_Timon(pdev, index, size);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक pwc_get_u8_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = recv_control_msg(pdev, request, value, 1);
	अगर (ret < 0)
		वापस ret;

	*data = pdev->ctrl_buf[0];
	वापस 0;
पूर्ण

पूर्णांक pwc_set_u8_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, u8 data)
अणु
	पूर्णांक ret;

	pdev->ctrl_buf[0] = data;
	ret = send_control_msg(pdev, request, value, pdev->ctrl_buf, 1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक pwc_get_s8_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = recv_control_msg(pdev, request, value, 1);
	अगर (ret < 0)
		वापस ret;

	*data = ((s8 *)pdev->ctrl_buf)[0];
	वापस 0;
पूर्ण

पूर्णांक pwc_get_u16_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = recv_control_msg(pdev, request, value, 2);
	अगर (ret < 0)
		वापस ret;

	*data = (pdev->ctrl_buf[1] << 8) | pdev->ctrl_buf[0];
	वापस 0;
पूर्ण

पूर्णांक pwc_set_u16_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, u16 data)
अणु
	पूर्णांक ret;

	pdev->ctrl_buf[0] = data & 0xff;
	pdev->ctrl_buf[1] = data >> 8;
	ret = send_control_msg(pdev, request, value, pdev->ctrl_buf, 2);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक pwc_button_ctrl(काष्ठा pwc_device *pdev, u16 value)
अणु
	पूर्णांक ret;

	ret = send_control_msg(pdev, SET_STATUS_CTL, value, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* POWER */
व्योम pwc_camera_घातer(काष्ठा pwc_device *pdev, पूर्णांक घातer)
अणु
	पूर्णांक r;

	अगर (!pdev->घातer_save)
		वापस;

	अगर (pdev->type < 675 || (pdev->type < 730 && pdev->release < 6))
		वापस;	/* Not supported by Nala or Timon < release 6 */

	अगर (घातer)
		pdev->ctrl_buf[0] = 0x00; /* active */
	अन्यथा
		pdev->ctrl_buf[0] = 0xFF; /* घातer save */
	r = send_control_msg(pdev, SET_STATUS_CTL,
		SET_POWER_SAVE_MODE_FORMATTER, pdev->ctrl_buf, 1);
	अगर (r < 0)
		PWC_ERROR("Failed to power %s camera (%d)\n",
			  घातer ? "on" : "off", r);
पूर्ण

पूर्णांक pwc_set_leds(काष्ठा pwc_device *pdev, पूर्णांक on_value, पूर्णांक off_value)
अणु
	पूर्णांक r;

	अगर (pdev->type < 730)
		वापस 0;
	on_value /= 100;
	off_value /= 100;
	अगर (on_value < 0)
		on_value = 0;
	अगर (on_value > 0xff)
		on_value = 0xff;
	अगर (off_value < 0)
		off_value = 0;
	अगर (off_value > 0xff)
		off_value = 0xff;

	pdev->ctrl_buf[0] = on_value;
	pdev->ctrl_buf[1] = off_value;

	r = send_control_msg(pdev,
		SET_STATUS_CTL, LED_FORMATTER, pdev->ctrl_buf, 2);
	अगर (r < 0)
		PWC_ERROR("Failed to set LED on/off time (%d)\n", r);

	वापस r;
पूर्ण

#अगर_घोषित CONFIG_USB_PWC_DEBUG
पूर्णांक pwc_get_cmos_sensor(काष्ठा pwc_device *pdev, पूर्णांक *sensor)
अणु
	पूर्णांक ret, request;

	अगर (pdev->type < 675)
		request = SENSOR_TYPE_FORMATTER1;
	अन्यथा अगर (pdev->type < 730)
		वापस -1; /* The Vesta series करोesn't have this call */
	अन्यथा
		request = SENSOR_TYPE_FORMATTER2;

	ret = recv_control_msg(pdev, GET_STATUS_CTL, request, 1);
	अगर (ret < 0)
		वापस ret;
	अगर (pdev->type < 675)
		*sensor = pdev->ctrl_buf[0] | 0x100;
	अन्यथा
		*sensor = pdev->ctrl_buf[0];
	वापस 0;
पूर्ण
#पूर्ण_अगर
