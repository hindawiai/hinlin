<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cpia CPiA (1) gspca driver
 *
 * Copyright (C) 2010-2011 Hans de Goede <hdegoede@redhat.com>
 *
 * This module is adapted from the in kernel v4l1 cpia driver which is :
 *
 * (C) Copyright 1999-2000 Peter Pregler
 * (C) Copyright 1999-2000 Scott J. Bertin
 * (C) Copyright 1999-2000 Johannes Erdfelt <johannes@erdfelt.com>
 * (C) Copyright 2000 STMicroelectronics
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "cpia1"

#समावेश <linux/input.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "gspca.h"

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Vision CPiA");
MODULE_LICENSE("GPL");

/* स्थिरant value's */
#घोषणा MAGIC_0		0x19
#घोषणा MAGIC_1		0x68
#घोषणा DATA_IN		0xc0
#घोषणा DATA_OUT	0x40
#घोषणा VIDEOSIZE_QCIF	0	/* 176x144 */
#घोषणा VIDEOSIZE_CIF	1	/* 352x288 */
#घोषणा SUBSAMPLE_420	0
#घोषणा SUBSAMPLE_422	1
#घोषणा YUVORDER_YUYV	0
#घोषणा YUVORDER_UYVY	1
#घोषणा NOT_COMPRESSED	0
#घोषणा COMPRESSED	1
#घोषणा NO_DECIMATION	0
#घोषणा DECIMATION_ENAB	1
#घोषणा EOI		0xff	/* End Of Image */
#घोषणा EOL		0xfd	/* End Of Line */
#घोषणा FRAME_HEADER_SIZE	64

/* Image grab modes */
#घोषणा CPIA_GRAB_SINGLE	0
#घोषणा CPIA_GRAB_CONTINEOUS	1

/* Compression parameters */
#घोषणा CPIA_COMPRESSION_NONE	0
#घोषणा CPIA_COMPRESSION_AUTO	1
#घोषणा CPIA_COMPRESSION_MANUAL	2
#घोषणा CPIA_COMPRESSION_TARGET_QUALITY         0
#घोषणा CPIA_COMPRESSION_TARGET_FRAMERATE       1

/* Return offsets क्रम GetCameraState */
#घोषणा SYSTEMSTATE	0
#घोषणा GRABSTATE	1
#घोषणा STREAMSTATE	2
#घोषणा FATALERROR	3
#घोषणा CMDERROR	4
#घोषणा DEBUGFLAGS	5
#घोषणा VPSTATUS	6
#घोषणा ERRORCODE	7

/* SystemState */
#घोषणा UNINITIALISED_STATE	0
#घोषणा PASS_THROUGH_STATE	1
#घोषणा LO_POWER_STATE		2
#घोषणा HI_POWER_STATE		3
#घोषणा WARM_BOOT_STATE		4

/* GrabState */
#घोषणा GRAB_IDLE		0
#घोषणा GRAB_ACTIVE		1
#घोषणा GRAB_DONE		2

/* StreamState */
#घोषणा STREAM_NOT_READY	0
#घोषणा STREAM_READY		1
#घोषणा STREAM_OPEN		2
#घोषणा STREAM_PAUSED		3
#घोषणा STREAM_FINISHED		4

/* Fatal Error, CmdError, and DebugFlags */
#घोषणा CPIA_FLAG	  1
#घोषणा SYSTEM_FLAG	  2
#घोषणा INT_CTRL_FLAG	  4
#घोषणा PROCESS_FLAG	  8
#घोषणा COM_FLAG	 16
#घोषणा VP_CTRL_FLAG	 32
#घोषणा CAPTURE_FLAG	 64
#घोषणा DEBUG_FLAG	128

/* VPStatus */
#घोषणा VP_STATE_OK			0x00

#घोषणा VP_STATE_FAILED_VIDEOINIT	0x01
#घोषणा VP_STATE_FAILED_AECACBINIT	0x02
#घोषणा VP_STATE_AEC_MAX		0x04
#घोषणा VP_STATE_ACB_BMAX		0x08

#घोषणा VP_STATE_ACB_RMIN		0x10
#घोषणा VP_STATE_ACB_GMIN		0x20
#घोषणा VP_STATE_ACB_RMAX		0x40
#घोषणा VP_STATE_ACB_GMAX		0x80

/* शेष (minimum) compensation values */
#घोषणा COMP_RED        220
#घोषणा COMP_GREEN1     214
#घोषणा COMP_GREEN2     COMP_GREEN1
#घोषणा COMP_BLUE       230

/* exposure status */
#घोषणा EXPOSURE_VERY_LIGHT 0
#घोषणा EXPOSURE_LIGHT      1
#घोषणा EXPOSURE_NORMAL     2
#घोषणा EXPOSURE_DARK       3
#घोषणा EXPOSURE_VERY_DARK  4

#घोषणा CPIA_MODULE_CPIA			(0 << 5)
#घोषणा CPIA_MODULE_SYSTEM			(1 << 5)
#घोषणा CPIA_MODULE_VP_CTRL			(5 << 5)
#घोषणा CPIA_MODULE_CAPTURE			(6 << 5)
#घोषणा CPIA_MODULE_DEBUG			(7 << 5)

#घोषणा INPUT (DATA_IN << 8)
#घोषणा OUTPUT (DATA_OUT << 8)

#घोषणा CPIA_COMMAND_GetCPIAVersion	(INPUT | CPIA_MODULE_CPIA | 1)
#घोषणा CPIA_COMMAND_GetPnPID		(INPUT | CPIA_MODULE_CPIA | 2)
#घोषणा CPIA_COMMAND_GetCameraStatus	(INPUT | CPIA_MODULE_CPIA | 3)
#घोषणा CPIA_COMMAND_GotoHiPower	(OUTPUT | CPIA_MODULE_CPIA | 4)
#घोषणा CPIA_COMMAND_GotoLoPower	(OUTPUT | CPIA_MODULE_CPIA | 5)
#घोषणा CPIA_COMMAND_GotoSuspend	(OUTPUT | CPIA_MODULE_CPIA | 7)
#घोषणा CPIA_COMMAND_GotoPassThrough	(OUTPUT | CPIA_MODULE_CPIA | 8)
#घोषणा CPIA_COMMAND_ModअगरyCameraStatus	(OUTPUT | CPIA_MODULE_CPIA | 10)

#घोषणा CPIA_COMMAND_ReadVCRegs		(INPUT | CPIA_MODULE_SYSTEM | 1)
#घोषणा CPIA_COMMAND_WriteVCReg		(OUTPUT | CPIA_MODULE_SYSTEM | 2)
#घोषणा CPIA_COMMAND_ReadMCPorts	(INPUT | CPIA_MODULE_SYSTEM | 3)
#घोषणा CPIA_COMMAND_WriteMCPort	(OUTPUT | CPIA_MODULE_SYSTEM | 4)
#घोषणा CPIA_COMMAND_SetBaudRate	(OUTPUT | CPIA_MODULE_SYSTEM | 5)
#घोषणा CPIA_COMMAND_SetECPTiming	(OUTPUT | CPIA_MODULE_SYSTEM | 6)
#घोषणा CPIA_COMMAND_ReadIDATA		(INPUT | CPIA_MODULE_SYSTEM | 7)
#घोषणा CPIA_COMMAND_WriteIDATA		(OUTPUT | CPIA_MODULE_SYSTEM | 8)
#घोषणा CPIA_COMMAND_GenericCall	(OUTPUT | CPIA_MODULE_SYSTEM | 9)
#घोषणा CPIA_COMMAND_I2CStart		(OUTPUT | CPIA_MODULE_SYSTEM | 10)
#घोषणा CPIA_COMMAND_I2CStop		(OUTPUT | CPIA_MODULE_SYSTEM | 11)
#घोषणा CPIA_COMMAND_I2CWrite		(OUTPUT | CPIA_MODULE_SYSTEM | 12)
#घोषणा CPIA_COMMAND_I2CRead		(INPUT | CPIA_MODULE_SYSTEM | 13)

#घोषणा CPIA_COMMAND_GetVPVersion	(INPUT | CPIA_MODULE_VP_CTRL | 1)
#घोषणा CPIA_COMMAND_ResetFrameCounter	(INPUT | CPIA_MODULE_VP_CTRL | 2)
#घोषणा CPIA_COMMAND_SetColourParams	(OUTPUT | CPIA_MODULE_VP_CTRL | 3)
#घोषणा CPIA_COMMAND_SetExposure	(OUTPUT | CPIA_MODULE_VP_CTRL | 4)
#घोषणा CPIA_COMMAND_SetColourBalance	(OUTPUT | CPIA_MODULE_VP_CTRL | 6)
#घोषणा CPIA_COMMAND_SetSensorFPS	(OUTPUT | CPIA_MODULE_VP_CTRL | 7)
#घोषणा CPIA_COMMAND_SetVPDefaults	(OUTPUT | CPIA_MODULE_VP_CTRL | 8)
#घोषणा CPIA_COMMAND_SetApcor		(OUTPUT | CPIA_MODULE_VP_CTRL | 9)
#घोषणा CPIA_COMMAND_SetFlickerCtrl	(OUTPUT | CPIA_MODULE_VP_CTRL | 10)
#घोषणा CPIA_COMMAND_SetVLOffset	(OUTPUT | CPIA_MODULE_VP_CTRL | 11)
#घोषणा CPIA_COMMAND_GetColourParams	(INPUT | CPIA_MODULE_VP_CTRL | 16)
#घोषणा CPIA_COMMAND_GetColourBalance	(INPUT | CPIA_MODULE_VP_CTRL | 17)
#घोषणा CPIA_COMMAND_GetExposure	(INPUT | CPIA_MODULE_VP_CTRL | 18)
#घोषणा CPIA_COMMAND_SetSensorMatrix	(OUTPUT | CPIA_MODULE_VP_CTRL | 19)
#घोषणा CPIA_COMMAND_ColourBars		(OUTPUT | CPIA_MODULE_VP_CTRL | 25)
#घोषणा CPIA_COMMAND_ReadVPRegs		(INPUT | CPIA_MODULE_VP_CTRL | 30)
#घोषणा CPIA_COMMAND_WriteVPReg		(OUTPUT | CPIA_MODULE_VP_CTRL | 31)

#घोषणा CPIA_COMMAND_GrabFrame		(OUTPUT | CPIA_MODULE_CAPTURE | 1)
#घोषणा CPIA_COMMAND_UploadFrame	(OUTPUT | CPIA_MODULE_CAPTURE | 2)
#घोषणा CPIA_COMMAND_SetGrabMode	(OUTPUT | CPIA_MODULE_CAPTURE | 3)
#घोषणा CPIA_COMMAND_InitStreamCap	(OUTPUT | CPIA_MODULE_CAPTURE | 4)
#घोषणा CPIA_COMMAND_FiniStreamCap	(OUTPUT | CPIA_MODULE_CAPTURE | 5)
#घोषणा CPIA_COMMAND_StartStreamCap	(OUTPUT | CPIA_MODULE_CAPTURE | 6)
#घोषणा CPIA_COMMAND_EndStreamCap	(OUTPUT | CPIA_MODULE_CAPTURE | 7)
#घोषणा CPIA_COMMAND_SetFormat		(OUTPUT | CPIA_MODULE_CAPTURE | 8)
#घोषणा CPIA_COMMAND_SetROI		(OUTPUT | CPIA_MODULE_CAPTURE | 9)
#घोषणा CPIA_COMMAND_SetCompression	(OUTPUT | CPIA_MODULE_CAPTURE | 10)
#घोषणा CPIA_COMMAND_SetCompressionTarget (OUTPUT | CPIA_MODULE_CAPTURE | 11)
#घोषणा CPIA_COMMAND_SetYUVThresh	(OUTPUT | CPIA_MODULE_CAPTURE | 12)
#घोषणा CPIA_COMMAND_SetCompressionParams (OUTPUT | CPIA_MODULE_CAPTURE | 13)
#घोषणा CPIA_COMMAND_DiscardFrame	(OUTPUT | CPIA_MODULE_CAPTURE | 14)
#घोषणा CPIA_COMMAND_GrabReset		(OUTPUT | CPIA_MODULE_CAPTURE | 15)

#घोषणा CPIA_COMMAND_OutputRS232	(OUTPUT | CPIA_MODULE_DEBUG | 1)
#घोषणा CPIA_COMMAND_AbortProcess	(OUTPUT | CPIA_MODULE_DEBUG | 4)
#घोषणा CPIA_COMMAND_SetDramPage	(OUTPUT | CPIA_MODULE_DEBUG | 5)
#घोषणा CPIA_COMMAND_StartDramUpload	(OUTPUT | CPIA_MODULE_DEBUG | 6)
#घोषणा CPIA_COMMAND_StartDummyDtream	(OUTPUT | CPIA_MODULE_DEBUG | 8)
#घोषणा CPIA_COMMAND_AbortStream	(OUTPUT | CPIA_MODULE_DEBUG | 9)
#घोषणा CPIA_COMMAND_DownloadDRAM	(OUTPUT | CPIA_MODULE_DEBUG | 10)
#घोषणा CPIA_COMMAND_Null		(OUTPUT | CPIA_MODULE_DEBUG | 11)

#घोषणा ROUND_UP_EXP_FOR_FLICKER 15

/* Constants क्रम स्वतःmatic frame rate adjusपंचांगent */
#घोषणा MAX_EXP       302
#घोषणा MAX_EXP_102   255
#घोषणा LOW_EXP       140
#घोषणा VERY_LOW_EXP   70
#घोषणा TC             94
#घोषणा	EXP_ACC_DARK   50
#घोषणा	EXP_ACC_LIGHT  90
#घोषणा HIGH_COMP_102 160
#घोषणा MAX_COMP      239
#घोषणा DARK_TIME       3
#घोषणा LIGHT_TIME      3

#घोषणा FIRMWARE_VERSION(x, y) (sd->params.version.firmwareVersion == (x) && \
				sd->params.version.firmwareRevision == (y))

#घोषणा CPIA1_CID_COMP_TARGET (V4L2_CTRL_CLASS_USER + 0x1000)
#घोषणा BRIGHTNESS_DEF 50
#घोषणा CONTRAST_DEF 48
#घोषणा SATURATION_DEF 50
#घोषणा FREQ_DEF V4L2_CID_POWER_LINE_FREQUENCY_50HZ
#घोषणा ILLUMINATORS_1_DEF 0
#घोषणा ILLUMINATORS_2_DEF 0
#घोषणा COMP_TARGET_DEF CPIA_COMPRESSION_TARGET_QUALITY

/* Developer's Guide Table 5 p 3-34
 * indexed by [मुख्यs][sensorFps.baserate][sensorFps.भागisor]*/
अटल u8 flicker_jumps[2][2][4] =
अणु अणु अणु 76, 38, 19, 9 पूर्ण, अणु 92, 46, 23, 11 पूर्ण पूर्ण,
  अणु अणु 64, 32, 16, 8 पूर्ण, अणु 76, 38, 19, 9पूर्ण पूर्ण
पूर्ण;

काष्ठा cam_params अणु
	काष्ठा अणु
		u8 firmwareVersion;
		u8 firmwareRevision;
		u8 vcVersion;
		u8 vcRevision;
	पूर्ण version;
	काष्ठा अणु
		u16 venकरोr;
		u16 product;
		u16 deviceRevision;
	पूर्ण pnpID;
	काष्ठा अणु
		u8 vpVersion;
		u8 vpRevision;
		u16 cameraHeadID;
	पूर्ण vpVersion;
	काष्ठा अणु
		u8 प्रणालीState;
		u8 grabState;
		u8 streamState;
		u8 fatalError;
		u8 cmdError;
		u8 debugFlags;
		u8 vpStatus;
		u8 errorCode;
	पूर्ण status;
	काष्ठा अणु
		u8 brightness;
		u8 contrast;
		u8 saturation;
	पूर्ण colourParams;
	काष्ठा अणु
		u8 gainMode;
		u8 expMode;
		u8 compMode;
		u8 centreWeight;
		u8 gain;
		u8 fineExp;
		u8 coarseExpLo;
		u8 coarseExpHi;
		u8 redComp;
		u8 green1Comp;
		u8 green2Comp;
		u8 blueComp;
	पूर्ण exposure;
	काष्ठा अणु
		u8 balanceMode;
		u8 redGain;
		u8 greenGain;
		u8 blueGain;
	पूर्ण colourBalance;
	काष्ठा अणु
		u8 भागisor;
		u8 baserate;
	पूर्ण sensorFps;
	काष्ठा अणु
		u8 gain1;
		u8 gain2;
		u8 gain4;
		u8 gain8;
	पूर्ण apcor;
	काष्ठा अणु
		u8 disabled;
		u8 flickerMode;
		u8 coarseJump;
		u8 allowableOverExposure;
	पूर्ण flickerControl;
	काष्ठा अणु
		u8 gain1;
		u8 gain2;
		u8 gain4;
		u8 gain8;
	पूर्ण vlOffset;
	काष्ठा अणु
		u8 mode;
		u8 decimation;
	पूर्ण compression;
	काष्ठा अणु
		u8 frTargeting;
		u8 targetFR;
		u8 targetQ;
	पूर्ण compressionTarget;
	काष्ठा अणु
		u8 yThreshold;
		u8 uvThreshold;
	पूर्ण yuvThreshold;
	काष्ठा अणु
		u8 hysteresis;
		u8 threshMax;
		u8 smallStep;
		u8 largeStep;
		u8 decimationHysteresis;
		u8 frDअगरfStepThresh;
		u8 qDअगरfStepThresh;
		u8 decimationThreshMod;
	पूर्ण compressionParams;
	काष्ठा अणु
		u8 videoSize;		/* CIF/QCIF */
		u8 subSample;
		u8 yuvOrder;
	पूर्ण क्रमmat;
	काष्ठा अणु                        /* Intel QX3 specअगरic data */
		u8 qx3_detected;        /* a QX3 is present */
		u8 toplight;            /* top light lit , R/W */
		u8 bottomlight;         /* bottom light lit, R/W */
		u8 button;              /* snapshot button pressed (R/O) */
		u8 cradled;             /* microscope is in cradle (R/O) */
	पूर्ण qx3;
	काष्ठा अणु
		u8 colStart;		/* skip first 8*colStart pixels */
		u8 colEnd;		/* finish at 8*colEnd pixels */
		u8 rowStart;		/* skip first 4*rowStart lines */
		u8 rowEnd;		/* finish at 4*rowEnd lines */
	पूर्ण roi;
	u8 ecpTiming;
	u8 streamStartLine;
पूर्ण;

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */
	काष्ठा cam_params params;		/* camera settings */

	atomic_t cam_exposure;
	atomic_t fps;
	पूर्णांक exposure_count;
	u8 exposure_status;
	काष्ठा v4l2_ctrl *freq;
	u8 मुख्यsFreq;				/* 0 = 50hz, 1 = 60hz */
	u8 first_frame;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_CPIA1, V4L2_FIELD_NONE,
		/* The sizeimage is trial and error, as with low framerates
		   the camera will pad out usb frames, making the image
		   data larger then strictly necessary */
		.bytesperline = 160,
		.sizeimage = 65536,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 3पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_CPIA1, V4L2_FIELD_NONE,
		.bytesperline = 172,
		.sizeimage = 65536,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_CPIA1, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 262144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_CPIA1, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 262144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

/**********************************************************************
 *
 * General functions
 *
 **********************************************************************/

अटल पूर्णांक cpia_usb_transferCmd(काष्ठा gspca_dev *gspca_dev, u8 *command)
अणु
	u8 requesttype;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक ret, databytes = command[6] | (command[7] << 8);
	/* Someबार we see spurious EPIPE errors */
	पूर्णांक retries = 3;

	अगर (command[0] == DATA_IN) अणु
		pipe = usb_rcvctrlpipe(gspca_dev->dev, 0);
		requesttype = USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	पूर्ण अन्यथा अगर (command[0] == DATA_OUT) अणु
		pipe = usb_sndctrlpipe(gspca_dev->dev, 0);
		requesttype = USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "Unexpected first byte of command: %x\n",
			  command[0]);
		वापस -EINVAL;
	पूर्ण

retry:
	ret = usb_control_msg(gspca_dev->dev, pipe,
			      command[1],
			      requesttype,
			      command[2] | (command[3] << 8),
			      command[4] | (command[5] << 8),
			      gspca_dev->usb_buf, databytes, 1000);

	अगर (ret < 0)
		pr_err("usb_control_msg %02x, error %d\n", command[1], ret);

	अगर (ret == -EPIPE && retries > 0) अणु
		retries--;
		जाओ retry;
	पूर्ण

	वापस (ret < 0) ? ret : 0;
पूर्ण

/* send an arbitrary command to the camera */
अटल पूर्णांक करो_command(काष्ठा gspca_dev *gspca_dev, u16 command,
		      u8 a, u8 b, u8 c, u8 d)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret, datasize;
	u8 cmd[8];

	चयन (command) अणु
	हाल CPIA_COMMAND_GetCPIAVersion:
	हाल CPIA_COMMAND_GetPnPID:
	हाल CPIA_COMMAND_GetCameraStatus:
	हाल CPIA_COMMAND_GetVPVersion:
	हाल CPIA_COMMAND_GetColourParams:
	हाल CPIA_COMMAND_GetColourBalance:
	हाल CPIA_COMMAND_GetExposure:
		datasize = 8;
		अवरोध;
	हाल CPIA_COMMAND_ReadMCPorts:
	हाल CPIA_COMMAND_ReadVCRegs:
		datasize = 4;
		अवरोध;
	शेष:
		datasize = 0;
		अवरोध;
	पूर्ण

	cmd[0] = command >> 8;
	cmd[1] = command & 0xff;
	cmd[2] = a;
	cmd[3] = b;
	cmd[4] = c;
	cmd[5] = d;
	cmd[6] = datasize;
	cmd[7] = 0;

	ret = cpia_usb_transferCmd(gspca_dev, cmd);
	अगर (ret)
		वापस ret;

	चयन (command) अणु
	हाल CPIA_COMMAND_GetCPIAVersion:
		sd->params.version.firmwareVersion = gspca_dev->usb_buf[0];
		sd->params.version.firmwareRevision = gspca_dev->usb_buf[1];
		sd->params.version.vcVersion = gspca_dev->usb_buf[2];
		sd->params.version.vcRevision = gspca_dev->usb_buf[3];
		अवरोध;
	हाल CPIA_COMMAND_GetPnPID:
		sd->params.pnpID.venकरोr =
			gspca_dev->usb_buf[0] | (gspca_dev->usb_buf[1] << 8);
		sd->params.pnpID.product =
			gspca_dev->usb_buf[2] | (gspca_dev->usb_buf[3] << 8);
		sd->params.pnpID.deviceRevision =
			gspca_dev->usb_buf[4] | (gspca_dev->usb_buf[5] << 8);
		अवरोध;
	हाल CPIA_COMMAND_GetCameraStatus:
		sd->params.status.प्रणालीState = gspca_dev->usb_buf[0];
		sd->params.status.grabState = gspca_dev->usb_buf[1];
		sd->params.status.streamState = gspca_dev->usb_buf[2];
		sd->params.status.fatalError = gspca_dev->usb_buf[3];
		sd->params.status.cmdError = gspca_dev->usb_buf[4];
		sd->params.status.debugFlags = gspca_dev->usb_buf[5];
		sd->params.status.vpStatus = gspca_dev->usb_buf[6];
		sd->params.status.errorCode = gspca_dev->usb_buf[7];
		अवरोध;
	हाल CPIA_COMMAND_GetVPVersion:
		sd->params.vpVersion.vpVersion = gspca_dev->usb_buf[0];
		sd->params.vpVersion.vpRevision = gspca_dev->usb_buf[1];
		sd->params.vpVersion.cameraHeadID =
			gspca_dev->usb_buf[2] | (gspca_dev->usb_buf[3] << 8);
		अवरोध;
	हाल CPIA_COMMAND_GetColourParams:
		sd->params.colourParams.brightness = gspca_dev->usb_buf[0];
		sd->params.colourParams.contrast = gspca_dev->usb_buf[1];
		sd->params.colourParams.saturation = gspca_dev->usb_buf[2];
		अवरोध;
	हाल CPIA_COMMAND_GetColourBalance:
		sd->params.colourBalance.redGain = gspca_dev->usb_buf[0];
		sd->params.colourBalance.greenGain = gspca_dev->usb_buf[1];
		sd->params.colourBalance.blueGain = gspca_dev->usb_buf[2];
		अवरोध;
	हाल CPIA_COMMAND_GetExposure:
		sd->params.exposure.gain = gspca_dev->usb_buf[0];
		sd->params.exposure.fineExp = gspca_dev->usb_buf[1];
		sd->params.exposure.coarseExpLo = gspca_dev->usb_buf[2];
		sd->params.exposure.coarseExpHi = gspca_dev->usb_buf[3];
		sd->params.exposure.redComp = gspca_dev->usb_buf[4];
		sd->params.exposure.green1Comp = gspca_dev->usb_buf[5];
		sd->params.exposure.green2Comp = gspca_dev->usb_buf[6];
		sd->params.exposure.blueComp = gspca_dev->usb_buf[7];
		अवरोध;

	हाल CPIA_COMMAND_ReadMCPorts:
		/* test button press */
		a = ((gspca_dev->usb_buf[1] & 0x02) == 0);
		अगर (a != sd->params.qx3.button) अणु
#अगर IS_ENABLED(CONFIG_INPUT)
			input_report_key(gspca_dev->input_dev, KEY_CAMERA, a);
			input_sync(gspca_dev->input_dev);
#पूर्ण_अगर
			sd->params.qx3.button = a;
		पूर्ण
		अगर (sd->params.qx3.button) अणु
			/* button pressed - unlock the latch */
			ret = करो_command(gspca_dev, CPIA_COMMAND_WriteMCPort,
				   3, 0xdf, 0xdf, 0);
			अगर (ret)
				वापस ret;
			ret = करो_command(gspca_dev, CPIA_COMMAND_WriteMCPort,
				   3, 0xff, 0xff, 0);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* test whether microscope is cradled */
		sd->params.qx3.cradled = ((gspca_dev->usb_buf[2] & 0x40) == 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* send a command to the camera with an additional data transaction */
अटल पूर्णांक करो_command_extended(काष्ठा gspca_dev *gspca_dev, u16 command,
			       u8 a, u8 b, u8 c, u8 d,
			       u8 e, u8 f, u8 g, u8 h,
			       u8 i, u8 j, u8 k, u8 l)
अणु
	u8 cmd[8];

	cmd[0] = command >> 8;
	cmd[1] = command & 0xff;
	cmd[2] = a;
	cmd[3] = b;
	cmd[4] = c;
	cmd[5] = d;
	cmd[6] = 8;
	cmd[7] = 0;
	gspca_dev->usb_buf[0] = e;
	gspca_dev->usb_buf[1] = f;
	gspca_dev->usb_buf[2] = g;
	gspca_dev->usb_buf[3] = h;
	gspca_dev->usb_buf[4] = i;
	gspca_dev->usb_buf[5] = j;
	gspca_dev->usb_buf[6] = k;
	gspca_dev->usb_buf[7] = l;

	वापस cpia_usb_transferCmd(gspca_dev, cmd);
पूर्ण

/*  find_over_exposure
 *  Finds a suitable value of OverExposure क्रम use with SetFlickerCtrl
 *  Some calculation is required because this value changes with the brightness
 *  set with SetColourParameters
 *
 *  Parameters: Brightness - last brightness value set with SetColourParameters
 *
 *  Returns: OverExposure value to use with SetFlickerCtrl
 */
#घोषणा FLICKER_MAX_EXPOSURE                    250
#घोषणा FLICKER_ALLOWABLE_OVER_EXPOSURE         146
#घोषणा FLICKER_BRIGHTNESS_CONSTANT             59
अटल पूर्णांक find_over_exposure(पूर्णांक brightness)
अणु
	पूर्णांक MaxAllowableOverExposure, OverExposure;

	MaxAllowableOverExposure = FLICKER_MAX_EXPOSURE - brightness -
				   FLICKER_BRIGHTNESS_CONSTANT;

	अगर (MaxAllowableOverExposure < FLICKER_ALLOWABLE_OVER_EXPOSURE)
		OverExposure = MaxAllowableOverExposure;
	अन्यथा
		OverExposure = FLICKER_ALLOWABLE_OVER_EXPOSURE;

	वापस OverExposure;
पूर्ण
#अघोषित FLICKER_MAX_EXPOSURE
#अघोषित FLICKER_ALLOWABLE_OVER_EXPOSURE
#अघोषित FLICKER_BRIGHTNESS_CONSTANT

/* initialise cam_data काष्ठाure  */
अटल व्योम reset_camera_params(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam_params *params = &sd->params;

	/* The following parameter values are the शेषs from
	 * "Software Developer's Guide for CPiA Cameras".  Any changes
	 * to the शेषs are noted in comments. */
	params->colourParams.brightness = BRIGHTNESS_DEF;
	params->colourParams.contrast = CONTRAST_DEF;
	params->colourParams.saturation = SATURATION_DEF;
	params->exposure.gainMode = 4;
	params->exposure.expMode = 2;		/* AEC */
	params->exposure.compMode = 1;
	params->exposure.centreWeight = 1;
	params->exposure.gain = 0;
	params->exposure.fineExp = 0;
	params->exposure.coarseExpLo = 185;
	params->exposure.coarseExpHi = 0;
	params->exposure.redComp = COMP_RED;
	params->exposure.green1Comp = COMP_GREEN1;
	params->exposure.green2Comp = COMP_GREEN2;
	params->exposure.blueComp = COMP_BLUE;
	params->colourBalance.balanceMode = 2;	/* ACB */
	params->colourBalance.redGain = 32;
	params->colourBalance.greenGain = 6;
	params->colourBalance.blueGain = 92;
	params->apcor.gain1 = 0x18;
	params->apcor.gain2 = 0x16;
	params->apcor.gain4 = 0x24;
	params->apcor.gain8 = 0x34;
	params->vlOffset.gain1 = 20;
	params->vlOffset.gain2 = 24;
	params->vlOffset.gain4 = 26;
	params->vlOffset.gain8 = 26;
	params->compressionParams.hysteresis = 3;
	params->compressionParams.threshMax = 11;
	params->compressionParams.smallStep = 1;
	params->compressionParams.largeStep = 3;
	params->compressionParams.decimationHysteresis = 2;
	params->compressionParams.frDअगरfStepThresh = 5;
	params->compressionParams.qDअगरfStepThresh = 3;
	params->compressionParams.decimationThreshMod = 2;
	/* End of शेष values from Software Developer's Guide */

	/* Set Sensor FPS to 15fps. This seems better than 30fps
	 * क्रम inकरोor lighting. */
	params->sensorFps.भागisor = 1;
	params->sensorFps.baserate = 1;

	params->flickerControl.flickerMode = 0;
	params->flickerControl.disabled = 1;
	params->flickerControl.coarseJump =
		flicker_jumps[sd->मुख्यsFreq]
			     [params->sensorFps.baserate]
			     [params->sensorFps.भागisor];
	params->flickerControl.allowableOverExposure =
		find_over_exposure(params->colourParams.brightness);

	params->yuvThreshold.yThreshold = 6; /* From winकरोws driver */
	params->yuvThreshold.uvThreshold = 6; /* From winकरोws driver */

	params->क्रमmat.subSample = SUBSAMPLE_420;
	params->क्रमmat.yuvOrder = YUVORDER_YUYV;

	params->compression.mode = CPIA_COMPRESSION_AUTO;
	params->compression.decimation = NO_DECIMATION;

	params->compressionTarget.frTargeting = COMP_TARGET_DEF;
	params->compressionTarget.targetFR = 15; /* From winकरोws driver */
	params->compressionTarget.targetQ = 5; /* From winकरोws driver */

	params->qx3.qx3_detected = 0;
	params->qx3.toplight = 0;
	params->qx3.bottomlight = 0;
	params->qx3.button = 0;
	params->qx3.cradled = 0;
पूर्ण

अटल व्योम prपूर्णांकstatus(काष्ठा gspca_dev *gspca_dev, काष्ठा cam_params *params)
अणु
	gspca_dbg(gspca_dev, D_PROBE, "status: %02x %02x %02x %02x %02x %02x %02x %02x\n",
		  params->status.प्रणालीState, params->status.grabState,
		  params->status.streamState, params->status.fatalError,
		  params->status.cmdError, params->status.debugFlags,
		  params->status.vpStatus, params->status.errorCode);
पूर्ण

अटल पूर्णांक जाओ_low_घातer(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	ret = करो_command(gspca_dev, CPIA_COMMAND_GotoLoPower, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	ret = करो_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	अगर (sd->params.status.प्रणालीState != LO_POWER_STATE) अणु
		अगर (sd->params.status.प्रणालीState != WARM_BOOT_STATE) अणु
			gspca_err(gspca_dev, "unexpected state after lo power cmd: %02x\n",
				  sd->params.status.प्रणालीState);
			prपूर्णांकstatus(gspca_dev, &sd->params);
		पूर्ण
		वापस -EIO;
	पूर्ण

	gspca_dbg(gspca_dev, D_CONF, "camera now in LOW power state\n");
	वापस 0;
पूर्ण

अटल पूर्णांक जाओ_high_घातer(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	ret = करो_command(gspca_dev, CPIA_COMMAND_GotoHiPower, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	msleep_पूर्णांकerruptible(40);	/* winकरोws driver करोes it too */

	अगर (संकेत_pending(current))
		वापस -EINTR;

	ret = करो_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	अगर (sd->params.status.प्रणालीState != HI_POWER_STATE) अणु
		gspca_err(gspca_dev, "unexpected state after hi power cmd: %02x\n",
			  sd->params.status.प्रणालीState);
		prपूर्णांकstatus(gspca_dev, &sd->params);
		वापस -EIO;
	पूर्ण

	gspca_dbg(gspca_dev, D_CONF, "camera now in HIGH power state\n");
	वापस 0;
पूर्ण

अटल पूर्णांक get_version_inक्रमmation(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret;

	/* GetCPIAVersion */
	ret = करो_command(gspca_dev, CPIA_COMMAND_GetCPIAVersion, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	/* GetPnPID */
	वापस करो_command(gspca_dev, CPIA_COMMAND_GetPnPID, 0, 0, 0, 0);
पूर्ण

अटल पूर्णांक save_camera_state(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret;

	ret = करो_command(gspca_dev, CPIA_COMMAND_GetColourBalance, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	वापस करो_command(gspca_dev, CPIA_COMMAND_GetExposure, 0, 0, 0, 0);
पूर्ण

अटल पूर्णांक command_setक्रमmat(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	ret = करो_command(gspca_dev, CPIA_COMMAND_SetFormat,
			 sd->params.क्रमmat.videoSize,
			 sd->params.क्रमmat.subSample,
			 sd->params.क्रमmat.yuvOrder, 0);
	अगर (ret)
		वापस ret;

	वापस करो_command(gspca_dev, CPIA_COMMAND_SetROI,
			  sd->params.roi.colStart, sd->params.roi.colEnd,
			  sd->params.roi.rowStart, sd->params.roi.rowEnd);
पूर्ण

अटल पूर्णांक command_setcolourparams(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	वापस करो_command(gspca_dev, CPIA_COMMAND_SetColourParams,
			  sd->params.colourParams.brightness,
			  sd->params.colourParams.contrast,
			  sd->params.colourParams.saturation, 0);
पूर्ण

अटल पूर्णांक command_setapcor(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	वापस करो_command(gspca_dev, CPIA_COMMAND_SetApcor,
			  sd->params.apcor.gain1,
			  sd->params.apcor.gain2,
			  sd->params.apcor.gain4,
			  sd->params.apcor.gain8);
पूर्ण

अटल पूर्णांक command_setvloffset(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	वापस करो_command(gspca_dev, CPIA_COMMAND_SetVLOffset,
			  sd->params.vlOffset.gain1,
			  sd->params.vlOffset.gain2,
			  sd->params.vlOffset.gain4,
			  sd->params.vlOffset.gain8);
पूर्ण

अटल पूर्णांक command_setexposure(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	ret = करो_command_extended(gspca_dev, CPIA_COMMAND_SetExposure,
				  sd->params.exposure.gainMode,
				  1,
				  sd->params.exposure.compMode,
				  sd->params.exposure.centreWeight,
				  sd->params.exposure.gain,
				  sd->params.exposure.fineExp,
				  sd->params.exposure.coarseExpLo,
				  sd->params.exposure.coarseExpHi,
				  sd->params.exposure.redComp,
				  sd->params.exposure.green1Comp,
				  sd->params.exposure.green2Comp,
				  sd->params.exposure.blueComp);
	अगर (ret)
		वापस ret;

	अगर (sd->params.exposure.expMode != 1) अणु
		ret = करो_command_extended(gspca_dev, CPIA_COMMAND_SetExposure,
					  0,
					  sd->params.exposure.expMode,
					  0, 0,
					  sd->params.exposure.gain,
					  sd->params.exposure.fineExp,
					  sd->params.exposure.coarseExpLo,
					  sd->params.exposure.coarseExpHi,
					  0, 0, 0, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक command_setcolourbalance(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->params.colourBalance.balanceMode == 1) अणु
		पूर्णांक ret;

		ret = करो_command(gspca_dev, CPIA_COMMAND_SetColourBalance,
				 1,
				 sd->params.colourBalance.redGain,
				 sd->params.colourBalance.greenGain,
				 sd->params.colourBalance.blueGain);
		अगर (ret)
			वापस ret;

		वापस करो_command(gspca_dev, CPIA_COMMAND_SetColourBalance,
				  3, 0, 0, 0);
	पूर्ण
	अगर (sd->params.colourBalance.balanceMode == 2) अणु
		वापस करो_command(gspca_dev, CPIA_COMMAND_SetColourBalance,
				  2, 0, 0, 0);
	पूर्ण
	अगर (sd->params.colourBalance.balanceMode == 3) अणु
		वापस करो_command(gspca_dev, CPIA_COMMAND_SetColourBalance,
				  3, 0, 0, 0);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक command_setcompressiontarget(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command(gspca_dev, CPIA_COMMAND_SetCompressionTarget,
			  sd->params.compressionTarget.frTargeting,
			  sd->params.compressionTarget.targetFR,
			  sd->params.compressionTarget.targetQ, 0);
पूर्ण

अटल पूर्णांक command_setyuvtresh(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command(gspca_dev, CPIA_COMMAND_SetYUVThresh,
			  sd->params.yuvThreshold.yThreshold,
			  sd->params.yuvThreshold.uvThreshold, 0, 0);
पूर्ण

अटल पूर्णांक command_setcompressionparams(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command_extended(gspca_dev,
			    CPIA_COMMAND_SetCompressionParams,
			    0, 0, 0, 0,
			    sd->params.compressionParams.hysteresis,
			    sd->params.compressionParams.threshMax,
			    sd->params.compressionParams.smallStep,
			    sd->params.compressionParams.largeStep,
			    sd->params.compressionParams.decimationHysteresis,
			    sd->params.compressionParams.frDअगरfStepThresh,
			    sd->params.compressionParams.qDअगरfStepThresh,
			    sd->params.compressionParams.decimationThreshMod);
पूर्ण

अटल पूर्णांक command_setcompression(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command(gspca_dev, CPIA_COMMAND_SetCompression,
			  sd->params.compression.mode,
			  sd->params.compression.decimation, 0, 0);
पूर्ण

अटल पूर्णांक command_setsensorfps(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command(gspca_dev, CPIA_COMMAND_SetSensorFPS,
			  sd->params.sensorFps.भागisor,
			  sd->params.sensorFps.baserate, 0, 0);
पूर्ण

अटल पूर्णांक command_setflickerctrl(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command(gspca_dev, CPIA_COMMAND_SetFlickerCtrl,
			  sd->params.flickerControl.flickerMode,
			  sd->params.flickerControl.coarseJump,
			  sd->params.flickerControl.allowableOverExposure,
			  0);
पूर्ण

अटल पूर्णांक command_setecptiming(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command(gspca_dev, CPIA_COMMAND_SetECPTiming,
			  sd->params.ecpTiming, 0, 0, 0);
पूर्ण

अटल पूर्णांक command_छोड़ो(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस करो_command(gspca_dev, CPIA_COMMAND_EndStreamCap, 0, 0, 0, 0);
पूर्ण

अटल पूर्णांक command_resume(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस करो_command(gspca_dev, CPIA_COMMAND_InitStreamCap,
			  0, sd->params.streamStartLine, 0, 0);
पूर्ण

अटल पूर्णांक command_setlights(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret, p1, p2;

	p1 = (sd->params.qx3.bottomlight == 0) << 1;
	p2 = (sd->params.qx3.toplight == 0) << 3;

	ret = करो_command(gspca_dev, CPIA_COMMAND_WriteVCReg,
			 0x90, 0x8f, 0x50, 0);
	अगर (ret)
		वापस ret;

	वापस करो_command(gspca_dev, CPIA_COMMAND_WriteMCPort, 2, 0,
			  p1 | p2 | 0xe0, 0);
पूर्ण

अटल पूर्णांक set_flicker(काष्ठा gspca_dev *gspca_dev, पूर्णांक on, पूर्णांक apply)
अणु
	/* Everything in here is from the Winकरोws driver */
/* define क्रम compgain calculation */
#अगर 0
#घोषणा COMPGAIN(base, curexp, newexp) \
    (u8) ((((भग्न) base - 128.0) * ((भग्न) curexp / (भग्न) newexp)) + 128.5)
#घोषणा EXP_FROM_COMP(basecomp, curcomp, curexp) \
    (u16)((भग्न)curexp * (भग्न)(u8)(curcomp + 128) / \
    (भग्न)(u8)(basecomp - 128))
#अन्यथा
  /* equivalent functions without भग्नing poपूर्णांक math */
#घोषणा COMPGAIN(base, curexp, newexp) \
    (u8)(128 + (((u32)(2*(base-128)*curexp + newexp)) / (2 * newexp)))
#घोषणा EXP_FROM_COMP(basecomp, curcomp, curexp) \
    (u16)(((u32)(curexp * (u8)(curcomp + 128)) / (u8)(basecomp - 128)))
#पूर्ण_अगर

	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक currentexp = sd->params.exposure.coarseExpLo +
			 sd->params.exposure.coarseExpHi * 256;
	पूर्णांक ret, startexp;

	अगर (on) अणु
		पूर्णांक cj = sd->params.flickerControl.coarseJump;
		sd->params.flickerControl.flickerMode = 1;
		sd->params.flickerControl.disabled = 0;
		अगर (sd->params.exposure.expMode != 2) अणु
			sd->params.exposure.expMode = 2;
			sd->exposure_status = EXPOSURE_NORMAL;
		पूर्ण
		currentexp = currentexp << sd->params.exposure.gain;
		sd->params.exposure.gain = 0;
		/* round करोwn current exposure to nearest value */
		startexp = (currentexp + ROUND_UP_EXP_FOR_FLICKER) / cj;
		अगर (startexp < 1)
			startexp = 1;
		startexp = (startexp * cj) - 1;
		अगर (FIRMWARE_VERSION(1, 2))
			जबतक (startexp > MAX_EXP_102)
				startexp -= cj;
		अन्यथा
			जबतक (startexp > MAX_EXP)
				startexp -= cj;
		sd->params.exposure.coarseExpLo = startexp & 0xff;
		sd->params.exposure.coarseExpHi = startexp >> 8;
		अगर (currentexp > startexp) अणु
			अगर (currentexp > (2 * startexp))
				currentexp = 2 * startexp;
			sd->params.exposure.redComp =
				COMPGAIN(COMP_RED, currentexp, startexp);
			sd->params.exposure.green1Comp =
				COMPGAIN(COMP_GREEN1, currentexp, startexp);
			sd->params.exposure.green2Comp =
				COMPGAIN(COMP_GREEN2, currentexp, startexp);
			sd->params.exposure.blueComp =
				COMPGAIN(COMP_BLUE, currentexp, startexp);
		पूर्ण अन्यथा अणु
			sd->params.exposure.redComp = COMP_RED;
			sd->params.exposure.green1Comp = COMP_GREEN1;
			sd->params.exposure.green2Comp = COMP_GREEN2;
			sd->params.exposure.blueComp = COMP_BLUE;
		पूर्ण
		अगर (FIRMWARE_VERSION(1, 2))
			sd->params.exposure.compMode = 0;
		अन्यथा
			sd->params.exposure.compMode = 1;

		sd->params.apcor.gain1 = 0x18;
		sd->params.apcor.gain2 = 0x18;
		sd->params.apcor.gain4 = 0x16;
		sd->params.apcor.gain8 = 0x14;
	पूर्ण अन्यथा अणु
		sd->params.flickerControl.flickerMode = 0;
		sd->params.flickerControl.disabled = 1;
		/* Average equivalent coarse क्रम each comp channel */
		startexp = EXP_FROM_COMP(COMP_RED,
				sd->params.exposure.redComp, currentexp);
		startexp += EXP_FROM_COMP(COMP_GREEN1,
				sd->params.exposure.green1Comp, currentexp);
		startexp += EXP_FROM_COMP(COMP_GREEN2,
				sd->params.exposure.green2Comp, currentexp);
		startexp += EXP_FROM_COMP(COMP_BLUE,
				sd->params.exposure.blueComp, currentexp);
		startexp = startexp >> 2;
		जबतक (startexp > MAX_EXP && sd->params.exposure.gain <
		       sd->params.exposure.gainMode - 1) अणु
			startexp = startexp >> 1;
			++sd->params.exposure.gain;
		पूर्ण
		अगर (FIRMWARE_VERSION(1, 2) && startexp > MAX_EXP_102)
			startexp = MAX_EXP_102;
		अगर (startexp > MAX_EXP)
			startexp = MAX_EXP;
		sd->params.exposure.coarseExpLo = startexp & 0xff;
		sd->params.exposure.coarseExpHi = startexp >> 8;
		sd->params.exposure.redComp = COMP_RED;
		sd->params.exposure.green1Comp = COMP_GREEN1;
		sd->params.exposure.green2Comp = COMP_GREEN2;
		sd->params.exposure.blueComp = COMP_BLUE;
		sd->params.exposure.compMode = 1;
		sd->params.apcor.gain1 = 0x18;
		sd->params.apcor.gain2 = 0x16;
		sd->params.apcor.gain4 = 0x24;
		sd->params.apcor.gain8 = 0x34;
	पूर्ण
	sd->params.vlOffset.gain1 = 20;
	sd->params.vlOffset.gain2 = 24;
	sd->params.vlOffset.gain4 = 26;
	sd->params.vlOffset.gain8 = 26;

	अगर (apply) अणु
		ret = command_setexposure(gspca_dev);
		अगर (ret)
			वापस ret;

		ret = command_setapcor(gspca_dev);
		अगर (ret)
			वापस ret;

		ret = command_setvloffset(gspca_dev);
		अगर (ret)
			वापस ret;

		ret = command_setflickerctrl(gspca_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
#अघोषित EXP_FROM_COMP
#अघोषित COMPGAIN
पूर्ण

/* monitor the exposure and adjust the sensor frame rate अगर needed */
अटल व्योम monitor_exposure(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 exp_acc, bcomp, cmd[8];
	पूर्णांक ret, light_exp, dark_exp, very_dark_exp;
	पूर्णांक old_exposure, new_exposure, framerate;
	पूर्णांक setfps = 0, setexp = 0, setflicker = 0;

	/* get necessary stats and रेजिस्टर settings from camera */
	/* करो_command can't handle this, so करो it ourselves */
	cmd[0] = CPIA_COMMAND_ReadVPRegs >> 8;
	cmd[1] = CPIA_COMMAND_ReadVPRegs & 0xff;
	cmd[2] = 30;
	cmd[3] = 4;
	cmd[4] = 9;
	cmd[5] = 8;
	cmd[6] = 8;
	cmd[7] = 0;
	ret = cpia_usb_transferCmd(gspca_dev, cmd);
	अगर (ret) अणु
		pr_err("ReadVPRegs(30,4,9,8) - failed: %d\n", ret);
		वापस;
	पूर्ण
	exp_acc = gspca_dev->usb_buf[0];
	bcomp = gspca_dev->usb_buf[1];

	light_exp = sd->params.colourParams.brightness +
		    TC - 50 + EXP_ACC_LIGHT;
	अगर (light_exp > 255)
		light_exp = 255;
	dark_exp = sd->params.colourParams.brightness +
		   TC - 50 - EXP_ACC_DARK;
	अगर (dark_exp < 0)
		dark_exp = 0;
	very_dark_exp = dark_exp / 2;

	old_exposure = sd->params.exposure.coarseExpHi * 256 +
		       sd->params.exposure.coarseExpLo;

	अगर (!sd->params.flickerControl.disabled) अणु
		/* Flicker control on */
		पूर्णांक max_comp = FIRMWARE_VERSION(1, 2) ? MAX_COMP :
							HIGH_COMP_102;
		bcomp += 128;	/* decode */
		अगर (bcomp >= max_comp && exp_acc < dark_exp) अणु
			/* dark */
			अगर (exp_acc < very_dark_exp) अणु
				/* very dark */
				अगर (sd->exposure_status == EXPOSURE_VERY_DARK)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status =
						EXPOSURE_VERY_DARK;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* just dark */
				अगर (sd->exposure_status == EXPOSURE_DARK)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status = EXPOSURE_DARK;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (old_exposure <= LOW_EXP || exp_acc > light_exp) अणु
			/* light */
			अगर (old_exposure <= VERY_LOW_EXP) अणु
				/* very light */
				अगर (sd->exposure_status == EXPOSURE_VERY_LIGHT)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status =
						EXPOSURE_VERY_LIGHT;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* just light */
				अगर (sd->exposure_status == EXPOSURE_LIGHT)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status = EXPOSURE_LIGHT;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* not dark or light */
			sd->exposure_status = EXPOSURE_NORMAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Flicker control off */
		अगर (old_exposure >= MAX_EXP && exp_acc < dark_exp) अणु
			/* dark */
			अगर (exp_acc < very_dark_exp) अणु
				/* very dark */
				अगर (sd->exposure_status == EXPOSURE_VERY_DARK)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status =
						EXPOSURE_VERY_DARK;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* just dark */
				अगर (sd->exposure_status == EXPOSURE_DARK)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status = EXPOSURE_DARK;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (old_exposure <= LOW_EXP || exp_acc > light_exp) अणु
			/* light */
			अगर (old_exposure <= VERY_LOW_EXP) अणु
				/* very light */
				अगर (sd->exposure_status == EXPOSURE_VERY_LIGHT)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status =
						EXPOSURE_VERY_LIGHT;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* just light */
				अगर (sd->exposure_status == EXPOSURE_LIGHT)
					++sd->exposure_count;
				अन्यथा अणु
					sd->exposure_status = EXPOSURE_LIGHT;
					sd->exposure_count = 1;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* not dark or light */
			sd->exposure_status = EXPOSURE_NORMAL;
		पूर्ण
	पूर्ण

	framerate = atomic_पढ़ो(&sd->fps);
	अगर (framerate > 30 || framerate < 1)
		framerate = 1;

	अगर (!sd->params.flickerControl.disabled) अणु
		/* Flicker control on */
		अगर ((sd->exposure_status == EXPOSURE_VERY_DARK ||
		     sd->exposure_status == EXPOSURE_DARK) &&
		    sd->exposure_count >= DARK_TIME * framerate &&
		    sd->params.sensorFps.भागisor < 2) अणु

			/* dark क्रम too दीर्घ */
			++sd->params.sensorFps.भागisor;
			setfps = 1;

			sd->params.flickerControl.coarseJump =
				flicker_jumps[sd->मुख्यsFreq]
					     [sd->params.sensorFps.baserate]
					     [sd->params.sensorFps.भागisor];
			setflicker = 1;

			new_exposure = sd->params.flickerControl.coarseJump-1;
			जबतक (new_exposure < old_exposure / 2)
				new_exposure +=
					sd->params.flickerControl.coarseJump;
			sd->params.exposure.coarseExpLo = new_exposure & 0xff;
			sd->params.exposure.coarseExpHi = new_exposure >> 8;
			setexp = 1;
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically decreasing sensor_fps\n");

		पूर्ण अन्यथा अगर ((sd->exposure_status == EXPOSURE_VERY_LIGHT ||
			    sd->exposure_status == EXPOSURE_LIGHT) &&
			   sd->exposure_count >= LIGHT_TIME * framerate &&
			   sd->params.sensorFps.भागisor > 0) अणु

			/* light क्रम too दीर्घ */
			पूर्णांक max_exp = FIRMWARE_VERSION(1, 2) ? MAX_EXP_102 :
							       MAX_EXP;
			--sd->params.sensorFps.भागisor;
			setfps = 1;

			sd->params.flickerControl.coarseJump =
				flicker_jumps[sd->मुख्यsFreq]
					     [sd->params.sensorFps.baserate]
					     [sd->params.sensorFps.भागisor];
			setflicker = 1;

			new_exposure = sd->params.flickerControl.coarseJump-1;
			जबतक (new_exposure < 2 * old_exposure &&
			       new_exposure +
			       sd->params.flickerControl.coarseJump < max_exp)
				new_exposure +=
					sd->params.flickerControl.coarseJump;
			sd->params.exposure.coarseExpLo = new_exposure & 0xff;
			sd->params.exposure.coarseExpHi = new_exposure >> 8;
			setexp = 1;
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically increasing sensor_fps\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Flicker control off */
		अगर ((sd->exposure_status == EXPOSURE_VERY_DARK ||
		     sd->exposure_status == EXPOSURE_DARK) &&
		    sd->exposure_count >= DARK_TIME * framerate &&
		    sd->params.sensorFps.भागisor < 2) अणु

			/* dark क्रम too दीर्घ */
			++sd->params.sensorFps.भागisor;
			setfps = 1;

			अगर (sd->params.exposure.gain > 0) अणु
				--sd->params.exposure.gain;
				setexp = 1;
			पूर्ण
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically decreasing sensor_fps\n");

		पूर्ण अन्यथा अगर ((sd->exposure_status == EXPOSURE_VERY_LIGHT ||
			    sd->exposure_status == EXPOSURE_LIGHT) &&
			   sd->exposure_count >= LIGHT_TIME * framerate &&
			   sd->params.sensorFps.भागisor > 0) अणु

			/* light क्रम too दीर्घ */
			--sd->params.sensorFps.भागisor;
			setfps = 1;

			अगर (sd->params.exposure.gain <
			    sd->params.exposure.gainMode - 1) अणु
				++sd->params.exposure.gain;
				setexp = 1;
			पूर्ण
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically increasing sensor_fps\n");
		पूर्ण
	पूर्ण

	अगर (setexp)
		command_setexposure(gspca_dev);

	अगर (setfps)
		command_setsensorfps(gspca_dev);

	अगर (setflicker)
		command_setflickerctrl(gspca_dev);
पूर्ण

/*-----------------------------------------------------------------*/
/* अगर flicker is चयनed off, this function चयनes it back on.It checks,
   however, that conditions are suitable beक्रमe restarting it.
   This should only be called क्रम firmware version 1.2.

   It also adjust the colour balance when an exposure step is detected - as
   दीर्घ as flicker is running
*/
अटल व्योम restart_flicker(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक cam_exposure, old_exp;

	अगर (!FIRMWARE_VERSION(1, 2))
		वापस;

	cam_exposure = atomic_पढ़ो(&sd->cam_exposure);

	अगर (sd->params.flickerControl.flickerMode == 0 ||
	    cam_exposure == 0)
		वापस;

	old_exp = sd->params.exposure.coarseExpLo +
		  sd->params.exposure.coarseExpHi*256;
	/*
	  see how far away camera exposure is from a valid
	  flicker exposure value
	*/
	cam_exposure %= sd->params.flickerControl.coarseJump;
	अगर (!sd->params.flickerControl.disabled &&
	    cam_exposure <= sd->params.flickerControl.coarseJump - 3) अणु
		/* Flicker control स्वतः-disabled */
		sd->params.flickerControl.disabled = 1;
	पूर्ण

	अगर (sd->params.flickerControl.disabled &&
	    old_exp > sd->params.flickerControl.coarseJump +
		      ROUND_UP_EXP_FOR_FLICKER) अणु
		/* exposure is now high enough to चयन
		   flicker control back on */
		set_flicker(gspca_dev, 1, 1);
	पूर्ण
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	sd->मुख्यsFreq = FREQ_DEF == V4L2_CID_POWER_LINE_FREQUENCY_60HZ;
	reset_camera_params(gspca_dev);

	gspca_dbg(gspca_dev, D_PROBE, "cpia CPiA camera detected (vid/pid 0x%04X:0x%04X)\n",
		  id->idVenकरोr, id->idProduct);

	cam = &gspca_dev->cam;
	cam->cam_mode = mode;
	cam->nmodes = ARRAY_SIZE(mode);

	जाओ_low_घातer(gspca_dev);
	/* Check the firmware version. */
	sd->params.version.firmwareVersion = 0;
	get_version_inक्रमmation(gspca_dev);
	अगर (sd->params.version.firmwareVersion != 1) अणु
		gspca_err(gspca_dev, "only firmware version 1 is supported (got: %d)\n",
			  sd->params.version.firmwareVersion);
		वापस -ENODEV;
	पूर्ण

	/* A bug in firmware 1-02 limits gainMode to 2 */
	अगर (sd->params.version.firmwareRevision <= 2 &&
	    sd->params.exposure.gainMode > 2) अणु
		sd->params.exposure.gainMode = 2;
	पूर्ण

	/* set QX3 detected flag */
	sd->params.qx3.qx3_detected = (sd->params.pnpID.venकरोr == 0x0813 &&
				       sd->params.pnpID.product == 0x0001);
	वापस 0;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक priv, ret;

	/* Start the camera in low घातer mode */
	अगर (जाओ_low_घातer(gspca_dev)) अणु
		अगर (sd->params.status.प्रणालीState != WARM_BOOT_STATE) अणु
			gspca_err(gspca_dev, "unexpected systemstate: %02x\n",
				  sd->params.status.प्रणालीState);
			prपूर्णांकstatus(gspca_dev, &sd->params);
			वापस -ENODEV;
		पूर्ण

		/* FIXME: this is just dirty trial and error */
		ret = जाओ_high_घातer(gspca_dev);
		अगर (ret)
			वापस ret;

		ret = करो_command(gspca_dev, CPIA_COMMAND_DiscardFrame,
				 0, 0, 0, 0);
		अगर (ret)
			वापस ret;

		ret = जाओ_low_घातer(gspca_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* procedure described in developer's guide p3-28 */

	/* Check the firmware version. */
	sd->params.version.firmwareVersion = 0;
	get_version_inक्रमmation(gspca_dev);

	/* The fatal error checking should be करोne after
	 * the camera घातers up (developer's guide p 3-38) */

	/* Set streamState beक्रमe transition to high घातer to aव्योम bug
	 * in firmware 1-02 */
	ret = करो_command(gspca_dev, CPIA_COMMAND_ModअगरyCameraStatus,
			 STREAMSTATE, 0, STREAM_NOT_READY, 0);
	अगर (ret)
		वापस ret;

	/* GotoHiPower */
	ret = जाओ_high_घातer(gspca_dev);
	अगर (ret)
		वापस ret;

	/* Check the camera status */
	ret = करो_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	अगर (sd->params.status.fatalError) अणु
		gspca_err(gspca_dev, "fatal_error: %04x, vp_status: %04x\n",
			  sd->params.status.fatalError,
			  sd->params.status.vpStatus);
		वापस -EIO;
	पूर्ण

	/* VPVersion can't be retrieved beक्रमe the camera is in HiPower,
	 * so get it here instead of in get_version_inक्रमmation. */
	ret = करो_command(gspca_dev, CPIA_COMMAND_GetVPVersion, 0, 0, 0, 0);
	अगर (ret)
		वापस ret;

	/* Determine video mode settings */
	sd->params.streamStartLine = 120;

	priv = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	अगर (priv & 0x01) अणु /* crop */
		sd->params.roi.colStart = 2;
		sd->params.roi.rowStart = 6;
	पूर्ण अन्यथा अणु
		sd->params.roi.colStart = 0;
		sd->params.roi.rowStart = 0;
	पूर्ण

	अगर (priv & 0x02) अणु /* quarter */
		sd->params.क्रमmat.videoSize = VIDEOSIZE_QCIF;
		sd->params.roi.colStart /= 2;
		sd->params.roi.rowStart /= 2;
		sd->params.streamStartLine /= 2;
	पूर्ण अन्यथा
		sd->params.क्रमmat.videoSize = VIDEOSIZE_CIF;

	sd->params.roi.colEnd = sd->params.roi.colStart +
				(gspca_dev->pixfmt.width >> 3);
	sd->params.roi.rowEnd = sd->params.roi.rowStart +
				(gspca_dev->pixfmt.height >> 2);

	/* And now set the camera to a known state */
	ret = करो_command(gspca_dev, CPIA_COMMAND_SetGrabMode,
			 CPIA_GRAB_CONTINEOUS, 0, 0, 0);
	अगर (ret)
		वापस ret;
	/* We start with compression disabled, as we need one uncompressed
	   frame to handle later compressed frames */
	ret = करो_command(gspca_dev, CPIA_COMMAND_SetCompression,
			 CPIA_COMPRESSION_NONE,
			 NO_DECIMATION, 0, 0);
	अगर (ret)
		वापस ret;
	ret = command_setcompressiontarget(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setcolourparams(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setक्रमmat(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setyuvtresh(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setecptiming(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setcompressionparams(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setexposure(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setcolourbalance(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setsensorfps(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setapcor(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setflickerctrl(gspca_dev);
	अगर (ret)
		वापस ret;
	ret = command_setvloffset(gspca_dev);
	अगर (ret)
		वापस ret;

	/* Start stream */
	ret = command_resume(gspca_dev);
	अगर (ret)
		वापस ret;

	/* Wait 6 frames beक्रमe turning compression on क्रम the sensor to get
	   all settings and AEC/ACB to settle */
	sd->first_frame = 6;
	sd->exposure_status = EXPOSURE_NORMAL;
	sd->exposure_count = 0;
	atomic_set(&sd->cam_exposure, 0);
	atomic_set(&sd->fps, 0);

	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd __maybe_unused = (काष्ठा sd *) gspca_dev;

	command_छोड़ो(gspca_dev);

	/* save camera state क्रम later खोलो (developers guide ch 3.5.3) */
	save_camera_state(gspca_dev);

	/* GotoLoPower */
	जाओ_low_घातer(gspca_dev);

	/* Update the camera status */
	करो_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);

#अगर IS_ENABLED(CONFIG_INPUT)
	/* If the last button state is pressed, release it now! */
	अगर (sd->params.qx3.button) अणु
		/* The camera latch will hold the pressed state until we reset
		   the latch, so we करो not reset sd->params.qx3.button now, to
		   aव्योम a false keypress being reported the next sd_start */
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	/* Start / Stop the camera to make sure we are talking to
	   a supported camera, and to get some inक्रमmation from it
	   to prपूर्णांक. */
	ret = sd_start(gspca_dev);
	अगर (ret)
		वापस ret;

	/* Ensure the QX3 illuminators' states are restored upon resume,
	   or disable the illuminator controls, अगर this isn't a QX3 */
	अगर (sd->params.qx3.qx3_detected)
		command_setlights(gspca_dev);

	sd_stopN(gspca_dev);

	gspca_dbg(gspca_dev, D_PROBE, "CPIA Version:             %d.%02d (%d.%d)\n",
		  sd->params.version.firmwareVersion,
		  sd->params.version.firmwareRevision,
		  sd->params.version.vcVersion,
		  sd->params.version.vcRevision);
	gspca_dbg(gspca_dev, D_PROBE, "CPIA PnP-ID:              %04x:%04x:%04x",
		  sd->params.pnpID.venकरोr, sd->params.pnpID.product,
		  sd->params.pnpID.deviceRevision);
	gspca_dbg(gspca_dev, D_PROBE, "VP-Version:               %d.%d %04x",
		  sd->params.vpVersion.vpVersion,
		  sd->params.vpVersion.vpRevision,
		  sd->params.vpVersion.cameraHeadID);

	वापस 0;
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,
			पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Check क्रम SOF */
	अगर (len >= 64 &&
	    data[0] == MAGIC_0 && data[1] == MAGIC_1 &&
	    data[16] == sd->params.क्रमmat.videoSize &&
	    data[17] == sd->params.क्रमmat.subSample &&
	    data[18] == sd->params.क्रमmat.yuvOrder &&
	    data[24] == sd->params.roi.colStart &&
	    data[25] == sd->params.roi.colEnd &&
	    data[26] == sd->params.roi.rowStart &&
	    data[27] == sd->params.roi.rowEnd) अणु
		u8 *image;

		atomic_set(&sd->cam_exposure, data[39] * 2);
		atomic_set(&sd->fps, data[41]);

		/* Check क्रम proper खातापूर्ण क्रम last frame */
		image = gspca_dev->image;
		अगर (image != शून्य &&
		    gspca_dev->image_len > 4 &&
		    image[gspca_dev->image_len - 4] == 0xff &&
		    image[gspca_dev->image_len - 3] == 0xff &&
		    image[gspca_dev->image_len - 2] == 0xff &&
		    image[gspca_dev->image_len - 1] == 0xff)
			gspca_frame_add(gspca_dev, LAST_PACKET,
						शून्य, 0);

		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		वापस;
	पूर्ण

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल व्योम sd_dq_callback(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Set the normal compression settings once we have captured a
	   few uncompressed frames (and AEC has hopefully settled) */
	अगर (sd->first_frame) अणु
		sd->first_frame--;
		अगर (sd->first_frame == 0)
			command_setcompression(gspca_dev);
	पूर्ण

	/* Switch flicker control back on अगर it got turned off */
	restart_flicker(gspca_dev);

	/* If AEC is enabled, monitor the exposure and
	   adjust the sensor frame rate अगर needed */
	अगर (sd->params.exposure.expMode == 2)
		monitor_exposure(gspca_dev);

	/* Update our knowledge of the camera state */
	करो_command(gspca_dev, CPIA_COMMAND_GetExposure, 0, 0, 0, 0);
	करो_command(gspca_dev, CPIA_COMMAND_ReadMCPorts, 0, 0, 0, 0);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming && ctrl->id != V4L2_CID_POWER_LINE_FREQUENCY)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		sd->params.colourParams.brightness = ctrl->val;
		sd->params.flickerControl.allowableOverExposure =
			find_over_exposure(sd->params.colourParams.brightness);
		gspca_dev->usb_err = command_setcolourparams(gspca_dev);
		अगर (!gspca_dev->usb_err)
			gspca_dev->usb_err = command_setflickerctrl(gspca_dev);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		sd->params.colourParams.contrast = ctrl->val;
		gspca_dev->usb_err = command_setcolourparams(gspca_dev);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		sd->params.colourParams.saturation = ctrl->val;
		gspca_dev->usb_err = command_setcolourparams(gspca_dev);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		sd->मुख्यsFreq = ctrl->val == V4L2_CID_POWER_LINE_FREQUENCY_60HZ;
		sd->params.flickerControl.coarseJump =
			flicker_jumps[sd->मुख्यsFreq]
			[sd->params.sensorFps.baserate]
			[sd->params.sensorFps.भागisor];

		gspca_dev->usb_err = set_flicker(gspca_dev,
			ctrl->val != V4L2_CID_POWER_LINE_FREQUENCY_DISABLED,
			gspca_dev->streaming);
		अवरोध;
	हाल V4L2_CID_ILLUMINATORS_1:
		sd->params.qx3.bottomlight = ctrl->val;
		gspca_dev->usb_err = command_setlights(gspca_dev);
		अवरोध;
	हाल V4L2_CID_ILLUMINATORS_2:
		sd->params.qx3.toplight = ctrl->val;
		gspca_dev->usb_err = command_setlights(gspca_dev);
		अवरोध;
	हाल CPIA1_CID_COMP_TARGET:
		sd->params.compressionTarget.frTargeting = ctrl->val;
		gspca_dev->usb_err = command_setcompressiontarget(gspca_dev);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	अटल स्थिर अक्षर * स्थिर comp_target_menu[] = अणु
		"Quality",
		"Framerate",
		शून्य
	पूर्ण;
	अटल स्थिर काष्ठा v4l2_ctrl_config comp_target = अणु
		.ops = &sd_ctrl_ops,
		.id = CPIA1_CID_COMP_TARGET,
		.type = V4L2_CTRL_TYPE_MENU,
		.name = "Compression Target",
		.qmenu = comp_target_menu,
		.max = 1,
		.def = COMP_TARGET_DEF,
	पूर्ण;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 7);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 100, 1, BRIGHTNESS_DEF);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 96, 8, CONTRAST_DEF);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 100, 1, SATURATION_DEF);
	sd->freq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0,
			FREQ_DEF);
	अगर (sd->params.qx3.qx3_detected) अणु
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_ILLUMINATORS_1, 0, 1, 1,
				ILLUMINATORS_1_DEF);
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_ILLUMINATORS_2, 0, 1, 1,
				ILLUMINATORS_2_DEF);
	पूर्ण
	v4l2_ctrl_new_custom(hdl, &comp_target, शून्य);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
	.dq_callback = sd_dq_callback,
	.pkt_scan = sd_pkt_scan,
#अगर IS_ENABLED(CONFIG_INPUT)
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x0553, 0x0002)पूर्ण,
	अणुUSB_DEVICE(0x0813, 0x0001)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
				THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name = MODULE_NAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
