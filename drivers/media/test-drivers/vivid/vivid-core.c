<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-core.c - A Virtual Video Test Driver, core initialization
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/font.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>

#समावेश "vivid-core.h"
#समावेश "vivid-vid-common.h"
#समावेश "vivid-vid-cap.h"
#समावेश "vivid-vid-out.h"
#समावेश "vivid-radio-common.h"
#समावेश "vivid-radio-rx.h"
#समावेश "vivid-radio-tx.h"
#समावेश "vivid-sdr-cap.h"
#समावेश "vivid-vbi-cap.h"
#समावेश "vivid-vbi-out.h"
#समावेश "vivid-osd.h"
#समावेश "vivid-cec.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-meta-cap.h"
#समावेश "vivid-meta-out.h"
#समावेश "vivid-touch-cap.h"

#घोषणा VIVID_MODULE_NAME "vivid"

/* The maximum number of vivid devices */
#घोषणा VIVID_MAX_DEVS CONFIG_VIDEO_VIVID_MAX_DEVS

MODULE_DESCRIPTION("Virtual Video Test Driver");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL");

अटल अचिन्हित n_devs = 1;
module_param(n_devs, uपूर्णांक, 0444);
MODULE_PARM_DESC(n_devs, " number of driver instances to create");

अटल पूर्णांक vid_cap_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(vid_cap_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(vid_cap_nr, " videoX start number, -1 is autodetect");

अटल पूर्णांक vid_out_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(vid_out_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(vid_out_nr, " videoX start number, -1 is autodetect");

अटल पूर्णांक vbi_cap_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(vbi_cap_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(vbi_cap_nr, " vbiX start number, -1 is autodetect");

अटल पूर्णांक vbi_out_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(vbi_out_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(vbi_out_nr, " vbiX start number, -1 is autodetect");

अटल पूर्णांक sdr_cap_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(sdr_cap_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(sdr_cap_nr, " swradioX start number, -1 is autodetect");

अटल पूर्णांक radio_rx_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(radio_rx_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_rx_nr, " radioX start number, -1 is autodetect");

अटल पूर्णांक radio_tx_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(radio_tx_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_tx_nr, " radioX start number, -1 is autodetect");

अटल पूर्णांक meta_cap_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(meta_cap_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(meta_cap_nr, " videoX start number, -1 is autodetect");

अटल पूर्णांक meta_out_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(meta_out_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(meta_out_nr, " videoX start number, -1 is autodetect");

अटल पूर्णांक touch_cap_nr[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(touch_cap_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(touch_cap_nr, " v4l-touchX start number, -1 is autodetect");

अटल पूर्णांक ccs_cap_mode[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(ccs_cap_mode, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ccs_cap_mode, " capture crop/compose/scale mode:\n"
			   "\t\t    bit 0=crop, 1=compose, 2=scale,\n"
			   "\t\t    -1=user-controlled (default)");

अटल पूर्णांक ccs_out_mode[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = -1 पूर्ण;
module_param_array(ccs_out_mode, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ccs_out_mode, " output crop/compose/scale mode:\n"
			   "\t\t    bit 0=crop, 1=compose, 2=scale,\n"
			   "\t\t    -1=user-controlled (default)");

अटल अचिन्हित multiplanar[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = 1 पूर्ण;
module_param_array(multiplanar, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(multiplanar, " 1 (default) creates a single planar device, 2 creates a multiplanar device.");

/*
 * Default: video + vbi-cap (raw and sliced) + radio rx + radio tx + sdr +
 * vbi-out + vid-out + meta-cap
 */
अटल अचिन्हित पूर्णांक node_types[VIVID_MAX_DEVS] = अणु
	[0 ... (VIVID_MAX_DEVS - 1)] = 0xe1d3d
पूर्ण;
module_param_array(node_types, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(node_types, " node types, default is 0xe1d3d. Bitmask with the following meaning:\n"
			     "\t\t    bit 0: Video Capture node\n"
			     "\t\t    bit 2-3: VBI Capture node: 0 = none, 1 = raw vbi, 2 = sliced vbi, 3 = both\n"
			     "\t\t    bit 4: Radio Receiver node\n"
			     "\t\t    bit 5: Software Defined Radio Receiver node\n"
			     "\t\t    bit 8: Video Output node\n"
			     "\t\t    bit 10-11: VBI Output node: 0 = none, 1 = raw vbi, 2 = sliced vbi, 3 = both\n"
			     "\t\t    bit 12: Radio Transmitter node\n"
			     "\t\t    bit 16: Framebuffer for testing overlays\n"
			     "\t\t    bit 17: Metadata Capture node\n"
			     "\t\t    bit 18: Metadata Output node\n"
			     "\t\t    bit 19: Touch Capture node\n");

/* Default: 4 inमाला_दो */
अटल अचिन्हित num_inमाला_दो[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = 4 पूर्ण;
module_param_array(num_inमाला_दो, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(num_inमाला_दो, " number of inputs, default is 4");

/* Default: input 0 = WEBCAM, 1 = TV, 2 = SVID, 3 = HDMI */
अटल अचिन्हित input_types[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = 0xe4 पूर्ण;
module_param_array(input_types, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(input_types, " input types, default is 0xe4. Two bits per input,\n"
			      "\t\t    bits 0-1 == input 0, bits 31-30 == input 15.\n"
			      "\t\t    Type 0 == webcam, 1 == TV, 2 == S-Video, 3 == HDMI");

/* Default: 2 outमाला_दो */
अटल अचिन्हित num_outमाला_दो[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = 2 पूर्ण;
module_param_array(num_outमाला_दो, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(num_outमाला_दो, " number of outputs, default is 2");

/* Default: output 0 = SVID, 1 = HDMI */
अटल अचिन्हित output_types[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = 2 पूर्ण;
module_param_array(output_types, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(output_types, " output types, default is 0x02. One bit per output,\n"
			      "\t\t    bit 0 == output 0, bit 15 == output 15.\n"
			      "\t\t    Type 0 == S-Video, 1 == HDMI");

अचिन्हित vivid_debug;
module_param(vivid_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(vivid_debug, " activates debug info");

अटल bool no_error_inj;
module_param(no_error_inj, bool, 0444);
MODULE_PARM_DESC(no_error_inj, " if set disable the error injecting controls");

अटल अचिन्हित पूर्णांक allocators[VIVID_MAX_DEVS] = अणु [0 ... (VIVID_MAX_DEVS - 1)] = 0 पूर्ण;
module_param_array(allocators, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(allocators, " memory allocator selection, default is 0.\n"
			     "\t\t    0 == vmalloc\n"
			     "\t\t    1 == dma-contig");

अटल अचिन्हित पूर्णांक cache_hपूर्णांकs[VIVID_MAX_DEVS] = अणु
	[0 ... (VIVID_MAX_DEVS - 1)] = 0
पूर्ण;
module_param_array(cache_hपूर्णांकs, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(cache_hपूर्णांकs, " user-space cache hints, default is 0.\n"
			     "\t\t    0 == forbid\n"
			     "\t\t    1 == allow");

अटल काष्ठा vivid_dev *vivid_devs[VIVID_MAX_DEVS];

स्थिर काष्ठा v4l2_rect vivid_min_rect = अणु
	0, 0, MIN_WIDTH, MIN_HEIGHT
पूर्ण;

स्थिर काष्ठा v4l2_rect vivid_max_rect = अणु
	0, 0, MAX_WIDTH * MAX_ZOOM, MAX_HEIGHT * MAX_ZOOM
पूर्ण;

अटल स्थिर u8 vivid_hdmi_edid[256] = अणु
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x31, 0xd8, 0x34, 0x12, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x1a, 0x01, 0x03, 0x80, 0x60, 0x36, 0x78,
	0x0f, 0xee, 0x91, 0xa3, 0x54, 0x4c, 0x99, 0x26,
	0x0f, 0x50, 0x54, 0x2f, 0xcf, 0x00, 0x31, 0x59,
	0x45, 0x59, 0x81, 0x80, 0x81, 0x40, 0x90, 0x40,
	0x95, 0x00, 0xa9, 0x40, 0xb3, 0x00, 0x08, 0xe8,
	0x00, 0x30, 0xf2, 0x70, 0x5a, 0x80, 0xb0, 0x58,
	0x8a, 0x00, 0xc0, 0x1c, 0x32, 0x00, 0x00, 0x1e,
	0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x55, 0x18,
	0x87, 0x3c, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x76,
	0x69, 0x76, 0x69, 0x64, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7b,

	0x02, 0x03, 0x3f, 0xf1, 0x51, 0x61, 0x60, 0x5f,
	0x5e, 0x5d, 0x10, 0x1f, 0x04, 0x13, 0x22, 0x21,
	0x20, 0x05, 0x14, 0x02, 0x11, 0x01, 0x23, 0x09,
	0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0x6d, 0x03,
	0x0c, 0x00, 0x10, 0x00, 0x00, 0x3c, 0x21, 0x00,
	0x60, 0x01, 0x02, 0x03, 0x67, 0xd8, 0x5d, 0xc4,
	0x01, 0x78, 0x00, 0x00, 0xe2, 0x00, 0xca, 0xe3,
	0x05, 0x00, 0x00, 0xe3, 0x06, 0x01, 0x00, 0x4d,
	0xd0, 0x00, 0xa0, 0xf0, 0x70, 0x3e, 0x80, 0x30,
	0x20, 0x35, 0x00, 0xc0, 0x1c, 0x32, 0x00, 0x00,
	0x1e, 0x1a, 0x36, 0x80, 0xa0, 0x70, 0x38, 0x1f,
	0x40, 0x30, 0x20, 0x35, 0x00, 0xc0, 0x1c, 0x32,
	0x00, 0x00, 0x1a, 0x1a, 0x1d, 0x00, 0x80, 0x51,
	0xd0, 0x1c, 0x20, 0x40, 0x80, 0x35, 0x00, 0xc0,
	0x1c, 0x32, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82,
पूर्ण;

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	strscpy(cap->driver, "vivid", माप(cap->driver));
	strscpy(cap->card, "vivid", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
			"platform:%s", dev->v4l2_dev.name);

	cap->capabilities = dev->vid_cap_caps | dev->vid_out_caps |
		dev->vbi_cap_caps | dev->vbi_out_caps |
		dev->radio_rx_caps | dev->radio_tx_caps |
		dev->sdr_cap_caps | dev->meta_cap_caps |
		dev->meta_out_caps | dev->touch_cap_caps |
		V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_hw_freq_seek(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_hw_freq_seek *a)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		वापस vivid_radio_rx_s_hw_freq_seek(file, fh, a);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_freq_bands(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		वापस vivid_radio_rx_क्रमागत_freq_bands(file, fh, band);
	अगर (vdev->vfl_type == VFL_TYPE_SDR)
		वापस vivid_sdr_क्रमागत_freq_bands(file, fh, band);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		वापस vivid_radio_rx_g_tuner(file, fh, vt);
	अगर (vdev->vfl_type == VFL_TYPE_SDR)
		वापस vivid_sdr_g_tuner(file, fh, vt);
	वापस vivid_video_g_tuner(file, fh, vt);
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		वापस vivid_radio_rx_s_tuner(file, fh, vt);
	अगर (vdev->vfl_type == VFL_TYPE_SDR)
		वापस vivid_sdr_s_tuner(file, fh, vt);
	वापस vivid_video_s_tuner(file, fh, vt);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		वापस vivid_radio_g_frequency(file,
			vdev->vfl_dir == VFL_सूची_RX ?
			&dev->radio_rx_freq : &dev->radio_tx_freq, vf);
	अगर (vdev->vfl_type == VFL_TYPE_SDR)
		वापस vivid_sdr_g_frequency(file, fh, vf);
	वापस vivid_video_g_frequency(file, fh, vf);
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		वापस vivid_radio_s_frequency(file,
			vdev->vfl_dir == VFL_सूची_RX ?
			&dev->radio_rx_freq : &dev->radio_tx_freq, vf);
	अगर (vdev->vfl_type == VFL_TYPE_SDR)
		वापस vivid_sdr_s_frequency(file, fh, vf);
	वापस vivid_video_s_frequency(file, fh, vf);
पूर्ण

अटल पूर्णांक vidioc_overlay(काष्ठा file *file, व्योम *fh, अचिन्हित i)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_overlay(file, fh, i);
	वापस vivid_vid_out_overlay(file, fh, i);
पूर्ण

अटल पूर्णांक vidioc_g_fbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_framebuffer *a)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_g_fbuf(file, fh, a);
	वापस vivid_vid_out_g_fbuf(file, fh, a);
पूर्ण

अटल पूर्णांक vidioc_s_fbuf(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_framebuffer *a)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_s_fbuf(file, fh, a);
	वापस vivid_vid_out_s_fbuf(file, fh, a);
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *fh, v4l2_std_id id)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_s_std(file, fh, id);
	वापस vivid_vid_out_s_std(file, fh, id);
पूर्ण

अटल पूर्णांक vidioc_s_dv_timings(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_s_dv_timings(file, fh, timings);
	वापस vivid_vid_out_s_dv_timings(file, fh, timings);
पूर्ण

अटल पूर्णांक vidioc_g_pixelaspect(काष्ठा file *file, व्योम *fh,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_g_pixelaspect(file, fh, type, f);
	वापस vivid_vid_out_g_pixelaspect(file, fh, type, f);
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_g_selection(file, fh, sel);
	वापस vivid_vid_out_g_selection(file, fh, sel);
पूर्ण

अटल पूर्णांक vidioc_s_selection(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_s_selection(file, fh, sel);
	वापस vivid_vid_out_s_selection(file, fh, sel);
पूर्ण

अटल पूर्णांक vidioc_g_parm(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_parm_tch(file, fh, parm);
	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_g_parm(file, fh, parm);
	वापस vivid_vid_out_g_parm(file, fh, parm);
पूर्ण

अटल पूर्णांक vidioc_s_parm(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_vid_cap_s_parm(file, fh, parm);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *fh)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	v4l2_ctrl_log_status(file, fh);
	अगर (vdev->vfl_dir == VFL_सूची_RX && vdev->vfl_type == VFL_TYPE_VIDEO)
		tpg_log_status(&dev->tpg);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार vivid_radio_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार size, loff_t *offset)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_TX)
		वापस -EINVAL;
	वापस vivid_radio_rx_पढ़ो(file, buf, size, offset);
पूर्ण

अटल sमाप_प्रकार vivid_radio_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार size, loff_t *offset)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस -EINVAL;
	वापस vivid_radio_tx_ग_लिखो(file, buf, size, offset);
पूर्ण

अटल __poll_t vivid_radio_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		वापस vivid_radio_rx_poll(file, रुको);
	वापस vivid_radio_tx_poll(file, रुको);
पूर्ण

अटल पूर्णांक vivid_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_input *inp)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_क्रमागत_input_tch(file, priv, inp);
	वापस vidioc_क्रमागत_input(file, priv, inp);
पूर्ण

अटल पूर्णांक vivid_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_input_tch(file, priv, i);
	वापस vidioc_g_input(file, priv, i);
पूर्ण

अटल पूर्णांक vivid_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_s_input_tch(file, priv, i);
	वापस vidioc_s_input(file, priv, i);
पूर्ण

अटल पूर्णांक vivid_क्रमागत_fmt_cap(काष्ठा file *file, व्योम  *priv,
			      काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_क्रमागत_fmt_tch(file, priv, f);
	वापस vivid_क्रमागत_fmt_vid(file, priv, f);
पूर्ण

अटल पूर्णांक vivid_g_fmt_cap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_fmt_tch(file, priv, f);
	वापस vidioc_g_fmt_vid_cap(file, priv, f);
पूर्ण

अटल पूर्णांक vivid_try_fmt_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_fmt_tch(file, priv, f);
	वापस vidioc_try_fmt_vid_cap(file, priv, f);
पूर्ण

अटल पूर्णांक vivid_s_fmt_cap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_fmt_tch(file, priv, f);
	वापस vidioc_s_fmt_vid_cap(file, priv, f);
पूर्ण

अटल पूर्णांक vivid_g_fmt_cap_mplane(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_fmt_tch_mplane(file, priv, f);
	वापस vidioc_g_fmt_vid_cap_mplane(file, priv, f);
पूर्ण

अटल पूर्णांक vivid_try_fmt_cap_mplane(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_fmt_tch_mplane(file, priv, f);
	वापस vidioc_try_fmt_vid_cap_mplane(file, priv, f);
पूर्ण

अटल पूर्णांक vivid_s_fmt_cap_mplane(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_type == VFL_TYPE_TOUCH)
		वापस vivid_g_fmt_tch_mplane(file, priv, f);
	वापस vidioc_s_fmt_vid_cap_mplane(file, priv, f);
पूर्ण

अटल bool vivid_is_in_use(bool valid, काष्ठा video_device *vdev)
अणु
	अचिन्हित दीर्घ flags;
	bool res;

	अगर (!valid)
		वापस false;
	spin_lock_irqsave(&vdev->fh_lock, flags);
	res = !list_empty(&vdev->fh_list);
	spin_unlock_irqrestore(&vdev->fh_lock, flags);
	वापस res;
पूर्ण

अटल bool vivid_is_last_user(काष्ठा vivid_dev *dev)
अणु
	अचिन्हित पूर्णांक uses =
		vivid_is_in_use(dev->has_vid_cap, &dev->vid_cap_dev) +
		vivid_is_in_use(dev->has_vid_out, &dev->vid_out_dev) +
		vivid_is_in_use(dev->has_vbi_cap, &dev->vbi_cap_dev) +
		vivid_is_in_use(dev->has_vbi_out, &dev->vbi_out_dev) +
		vivid_is_in_use(dev->has_radio_rx, &dev->radio_rx_dev) +
		vivid_is_in_use(dev->has_radio_tx, &dev->radio_tx_dev) +
		vivid_is_in_use(dev->has_sdr_cap, &dev->sdr_cap_dev) +
		vivid_is_in_use(dev->has_meta_cap, &dev->meta_cap_dev) +
		vivid_is_in_use(dev->has_meta_out, &dev->meta_out_dev) +
		vivid_is_in_use(dev->has_touch_cap, &dev->touch_cap_dev);

	वापस uses == 1;
पूर्ण

अटल व्योम vivid_reconnect(काष्ठा vivid_dev *dev)
अणु
	अगर (dev->has_vid_cap)
		set_bit(V4L2_FL_REGISTERED, &dev->vid_cap_dev.flags);
	अगर (dev->has_vid_out)
		set_bit(V4L2_FL_REGISTERED, &dev->vid_out_dev.flags);
	अगर (dev->has_vbi_cap)
		set_bit(V4L2_FL_REGISTERED, &dev->vbi_cap_dev.flags);
	अगर (dev->has_vbi_out)
		set_bit(V4L2_FL_REGISTERED, &dev->vbi_out_dev.flags);
	अगर (dev->has_radio_rx)
		set_bit(V4L2_FL_REGISTERED, &dev->radio_rx_dev.flags);
	अगर (dev->has_radio_tx)
		set_bit(V4L2_FL_REGISTERED, &dev->radio_tx_dev.flags);
	अगर (dev->has_sdr_cap)
		set_bit(V4L2_FL_REGISTERED, &dev->sdr_cap_dev.flags);
	अगर (dev->has_meta_cap)
		set_bit(V4L2_FL_REGISTERED, &dev->meta_cap_dev.flags);
	अगर (dev->has_meta_out)
		set_bit(V4L2_FL_REGISTERED, &dev->meta_out_dev.flags);
	अगर (dev->has_touch_cap)
		set_bit(V4L2_FL_REGISTERED, &dev->touch_cap_dev.flags);
	dev->disconnect_error = false;
पूर्ण

अटल पूर्णांक vivid_fop_release(काष्ठा file *file)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	mutex_lock(&dev->mutex);
	अगर (!no_error_inj && v4l2_fh_is_singular_file(file) &&
	    dev->disconnect_error && !video_is_रेजिस्टरed(vdev) &&
	    vivid_is_last_user(dev)) अणु
		/*
		 * I am the last user of this driver, and a disconnect
		 * was क्रमced (since this video_device is unरेजिस्टरed),
		 * so re-रेजिस्टर all video_device's again.
		 */
		v4l2_info(&dev->v4l2_dev, "reconnect\n");
		vivid_reconnect(dev);
	पूर्ण
	mutex_unlock(&dev->mutex);
	अगर (file->निजी_data == dev->overlay_cap_owner)
		dev->overlay_cap_owner = शून्य;
	अगर (file->निजी_data == dev->radio_rx_rds_owner) अणु
		dev->radio_rx_rds_last_block = 0;
		dev->radio_rx_rds_owner = शून्य;
	पूर्ण
	अगर (file->निजी_data == dev->radio_tx_rds_owner) अणु
		dev->radio_tx_rds_last_block = 0;
		dev->radio_tx_rds_owner = शून्य;
	पूर्ण
	अगर (vdev->queue)
		वापस vb2_fop_release(file);
	वापस v4l2_fh_release(file);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vivid_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = vivid_fop_release,
	.पढ़ो           = vb2_fop_पढ़ो,
	.ग_लिखो          = vb2_fop_ग_लिखो,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations vivid_radio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = vivid_fop_release,
	.पढ़ो           = vivid_radio_पढ़ो,
	.ग_लिखो          = vivid_radio_ग_लिखो,
	.poll		= vivid_radio_poll,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops vivid_ioctl_ops = अणु
	.vidioc_querycap		= vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= vivid_क्रमागत_fmt_cap,
	.vidioc_g_fmt_vid_cap		= vivid_g_fmt_cap,
	.vidioc_try_fmt_vid_cap		= vivid_try_fmt_cap,
	.vidioc_s_fmt_vid_cap		= vivid_s_fmt_cap,
	.vidioc_g_fmt_vid_cap_mplane	= vivid_g_fmt_cap_mplane,
	.vidioc_try_fmt_vid_cap_mplane	= vivid_try_fmt_cap_mplane,
	.vidioc_s_fmt_vid_cap_mplane	= vivid_s_fmt_cap_mplane,

	.vidioc_क्रमागत_fmt_vid_out	= vivid_क्रमागत_fmt_vid,
	.vidioc_g_fmt_vid_out		= vidioc_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out		= vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= vidioc_s_fmt_vid_out,
	.vidioc_g_fmt_vid_out_mplane	= vidioc_g_fmt_vid_out_mplane,
	.vidioc_try_fmt_vid_out_mplane	= vidioc_try_fmt_vid_out_mplane,
	.vidioc_s_fmt_vid_out_mplane	= vidioc_s_fmt_vid_out_mplane,

	.vidioc_g_selection		= vidioc_g_selection,
	.vidioc_s_selection		= vidioc_s_selection,
	.vidioc_g_pixelaspect		= vidioc_g_pixelaspect,

	.vidioc_g_fmt_vbi_cap		= vidioc_g_fmt_vbi_cap,
	.vidioc_try_fmt_vbi_cap		= vidioc_g_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap		= vidioc_s_fmt_vbi_cap,

	.vidioc_g_fmt_sliced_vbi_cap    = vidioc_g_fmt_sliced_vbi_cap,
	.vidioc_try_fmt_sliced_vbi_cap  = vidioc_try_fmt_sliced_vbi_cap,
	.vidioc_s_fmt_sliced_vbi_cap    = vidioc_s_fmt_sliced_vbi_cap,
	.vidioc_g_sliced_vbi_cap	= vidioc_g_sliced_vbi_cap,

	.vidioc_g_fmt_vbi_out		= vidioc_g_fmt_vbi_out,
	.vidioc_try_fmt_vbi_out		= vidioc_g_fmt_vbi_out,
	.vidioc_s_fmt_vbi_out		= vidioc_s_fmt_vbi_out,

	.vidioc_g_fmt_sliced_vbi_out    = vidioc_g_fmt_sliced_vbi_out,
	.vidioc_try_fmt_sliced_vbi_out  = vidioc_try_fmt_sliced_vbi_out,
	.vidioc_s_fmt_sliced_vbi_out    = vidioc_s_fmt_sliced_vbi_out,

	.vidioc_क्रमागत_fmt_sdr_cap	= vidioc_क्रमागत_fmt_sdr_cap,
	.vidioc_g_fmt_sdr_cap		= vidioc_g_fmt_sdr_cap,
	.vidioc_try_fmt_sdr_cap		= vidioc_try_fmt_sdr_cap,
	.vidioc_s_fmt_sdr_cap		= vidioc_s_fmt_sdr_cap,

	.vidioc_overlay			= vidioc_overlay,
	.vidioc_क्रमागत_framesizes		= vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= vidioc_क्रमागत_frameपूर्णांकervals,
	.vidioc_g_parm			= vidioc_g_parm,
	.vidioc_s_parm			= vidioc_s_parm,

	.vidioc_क्रमागत_fmt_vid_overlay	= vidioc_क्रमागत_fmt_vid_overlay,
	.vidioc_g_fmt_vid_overlay	= vidioc_g_fmt_vid_overlay,
	.vidioc_try_fmt_vid_overlay	= vidioc_try_fmt_vid_overlay,
	.vidioc_s_fmt_vid_overlay	= vidioc_s_fmt_vid_overlay,
	.vidioc_g_fmt_vid_out_overlay	= vidioc_g_fmt_vid_out_overlay,
	.vidioc_try_fmt_vid_out_overlay	= vidioc_try_fmt_vid_out_overlay,
	.vidioc_s_fmt_vid_out_overlay	= vidioc_s_fmt_vid_out_overlay,
	.vidioc_g_fbuf			= vidioc_g_fbuf,
	.vidioc_s_fbuf			= vidioc_s_fbuf,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_क्रमागत_input		= vivid_क्रमागत_input,
	.vidioc_g_input			= vivid_g_input,
	.vidioc_s_input			= vivid_s_input,
	.vidioc_s_audio			= vidioc_s_audio,
	.vidioc_g_audio			= vidioc_g_audio,
	.vidioc_क्रमागतaudio		= vidioc_क्रमागतaudio,
	.vidioc_s_frequency		= vidioc_s_frequency,
	.vidioc_g_frequency		= vidioc_g_frequency,
	.vidioc_s_tuner			= vidioc_s_tuner,
	.vidioc_g_tuner			= vidioc_g_tuner,
	.vidioc_s_modulator		= vidioc_s_modulator,
	.vidioc_g_modulator		= vidioc_g_modulator,
	.vidioc_s_hw_freq_seek		= vidioc_s_hw_freq_seek,
	.vidioc_क्रमागत_freq_bands		= vidioc_क्रमागत_freq_bands,

	.vidioc_क्रमागत_output		= vidioc_क्रमागत_output,
	.vidioc_g_output		= vidioc_g_output,
	.vidioc_s_output		= vidioc_s_output,
	.vidioc_s_auकरोut		= vidioc_s_auकरोut,
	.vidioc_g_auकरोut		= vidioc_g_auकरोut,
	.vidioc_क्रमागतauकरोut		= vidioc_क्रमागतauकरोut,

	.vidioc_querystd		= vidioc_querystd,
	.vidioc_g_std			= vidioc_g_std,
	.vidioc_s_std			= vidioc_s_std,
	.vidioc_s_dv_timings		= vidioc_s_dv_timings,
	.vidioc_g_dv_timings		= vidioc_g_dv_timings,
	.vidioc_query_dv_timings	= vidioc_query_dv_timings,
	.vidioc_क्रमागत_dv_timings		= vidioc_क्रमागत_dv_timings,
	.vidioc_dv_timings_cap		= vidioc_dv_timings_cap,
	.vidioc_g_edid			= vidioc_g_edid,
	.vidioc_s_edid			= vidioc_s_edid,

	.vidioc_log_status		= vidioc_log_status,
	.vidioc_subscribe_event		= vidioc_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,

	.vidioc_क्रमागत_fmt_meta_cap	= vidioc_क्रमागत_fmt_meta_cap,
	.vidioc_g_fmt_meta_cap		= vidioc_g_fmt_meta_cap,
	.vidioc_s_fmt_meta_cap		= vidioc_g_fmt_meta_cap,
	.vidioc_try_fmt_meta_cap	= vidioc_g_fmt_meta_cap,

	.vidioc_क्रमागत_fmt_meta_out       = vidioc_क्रमागत_fmt_meta_out,
	.vidioc_g_fmt_meta_out          = vidioc_g_fmt_meta_out,
	.vidioc_s_fmt_meta_out          = vidioc_g_fmt_meta_out,
	.vidioc_try_fmt_meta_out        = vidioc_g_fmt_meta_out,
पूर्ण;

/* -----------------------------------------------------------------
	Initialization and module stuff
   ------------------------------------------------------------------*/

अटल व्योम vivid_dev_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा vivid_dev *dev = container_of(v4l2_dev, काष्ठा vivid_dev, v4l2_dev);

	vivid_मुक्त_controls(dev);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	media_device_cleanup(&dev->mdev);
#पूर्ण_अगर
	vमुक्त(dev->scaled_line);
	vमुक्त(dev->blended_line);
	vमुक्त(dev->edid);
	vमुक्त(dev->biपंचांगap_cap);
	vमुक्त(dev->biपंचांगap_out);
	tpg_मुक्त(&dev->tpg);
	kमुक्त(dev->query_dv_timings_qmenu);
	kमुक्त(dev->query_dv_timings_qmenu_strings);
	kमुक्त(dev);
पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
अटल पूर्णांक vivid_req_validate(काष्ठा media_request *req)
अणु
	काष्ठा vivid_dev *dev = container_of(req->mdev, काष्ठा vivid_dev, mdev);

	अगर (dev->req_validate_error) अणु
		dev->req_validate_error = false;
		वापस -EINVAL;
	पूर्ण
	वापस vb2_request_validate(req);
पूर्ण

अटल स्थिर काष्ठा media_device_ops vivid_media_ops = अणु
	.req_validate = vivid_req_validate,
	.req_queue = vb2_request_queue,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक vivid_create_queue(काष्ठा vivid_dev *dev,
			      काष्ठा vb2_queue *q,
			      u32 buf_type,
			      अचिन्हित पूर्णांक min_buffers_needed,
			      स्थिर काष्ठा vb2_ops *ops)
अणु
	अगर (buf_type == V4L2_BUF_TYPE_VIDEO_CAPTURE && dev->multiplanar)
		buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	अन्यथा अगर (buf_type == V4L2_BUF_TYPE_VIDEO_OUTPUT && dev->multiplanar)
		buf_type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	अन्यथा अगर (buf_type == V4L2_BUF_TYPE_VBI_CAPTURE && !dev->has_raw_vbi_cap)
		buf_type = V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	अन्यथा अगर (buf_type == V4L2_BUF_TYPE_VBI_OUTPUT && !dev->has_raw_vbi_out)
		buf_type = V4L2_BUF_TYPE_SLICED_VBI_OUTPUT;

	q->type = buf_type;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->io_modes |= V4L2_TYPE_IS_OUTPUT(buf_type) ?  VB2_WRITE : VB2_READ;
	अगर (allocators[dev->inst] != 1)
		q->io_modes |= VB2_USERPTR;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा vivid_buffer);
	q->ops = ops;
	q->mem_ops = allocators[dev->inst] == 1 ? &vb2_dma_contig_memops :
						  &vb2_vदो_स्मृति_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = min_buffers_needed;
	q->lock = &dev->mutex;
	q->dev = dev->v4l2_dev.dev;
	q->supports_requests = true;
	q->allow_cache_hपूर्णांकs = (cache_hपूर्णांकs[dev->inst] == 1);

	वापस vb2_queue_init(q);
पूर्ण

अटल पूर्णांक vivid_detect_feature_set(काष्ठा vivid_dev *dev, पूर्णांक inst,
				    अचिन्हित node_type,
				    bool *has_tuner,
				    bool *has_modulator,
				    पूर्णांक *ccs_cap,
				    पूर्णांक *ccs_out,
				    अचिन्हित in_type_counter[4],
				    अचिन्हित out_type_counter[4])
अणु
	पूर्णांक i;

	/* करो we use single- or multi-planar? */
	dev->multiplanar = multiplanar[inst] > 1;
	v4l2_info(&dev->v4l2_dev, "using %splanar format API\n",
			dev->multiplanar ? "multi" : "single ");

	/* how many inमाला_दो करो we have and of what type? */
	dev->num_inमाला_दो = num_inमाला_दो[inst];
	अगर (dev->num_inमाला_दो < 1)
		dev->num_inमाला_दो = 1;
	अगर (dev->num_inमाला_दो >= MAX_INPUTS)
		dev->num_inमाला_दो = MAX_INPUTS;
	क्रम (i = 0; i < dev->num_inमाला_दो; i++) अणु
		dev->input_type[i] = (input_types[inst] >> (i * 2)) & 0x3;
		dev->input_name_counter[i] = in_type_counter[dev->input_type[i]]++;
	पूर्ण
	dev->has_audio_inमाला_दो = in_type_counter[TV] && in_type_counter[SVID];
	अगर (in_type_counter[HDMI] == 16) अणु
		/* The CEC physical address only allows क्रम max 15 inमाला_दो */
		in_type_counter[HDMI]--;
		dev->num_inमाला_दो--;
	पूर्ण
	dev->num_hdmi_inमाला_दो = in_type_counter[HDMI];

	/* how many outमाला_दो करो we have and of what type? */
	dev->num_outमाला_दो = num_outमाला_दो[inst];
	अगर (dev->num_outमाला_दो < 1)
		dev->num_outमाला_दो = 1;
	अगर (dev->num_outमाला_दो >= MAX_OUTPUTS)
		dev->num_outमाला_दो = MAX_OUTPUTS;
	क्रम (i = 0; i < dev->num_outमाला_दो; i++) अणु
		dev->output_type[i] = ((output_types[inst] >> i) & 1) ? HDMI : SVID;
		dev->output_name_counter[i] = out_type_counter[dev->output_type[i]]++;
		dev->display_present[i] = true;
	पूर्ण
	dev->has_audio_outमाला_दो = out_type_counter[SVID];
	अगर (out_type_counter[HDMI] == 16) अणु
		/*
		 * The CEC physical address only allows क्रम max 15 inमाला_दो,
		 * so outमाला_दो are also limited to 15 to allow क्रम easy
		 * CEC output to input mapping.
		 */
		out_type_counter[HDMI]--;
		dev->num_outमाला_दो--;
	पूर्ण
	dev->num_hdmi_outमाला_दो = out_type_counter[HDMI];

	/* करो we create a video capture device? */
	dev->has_vid_cap = node_type & 0x0001;

	/* करो we create a vbi capture device? */
	अगर (in_type_counter[TV] || in_type_counter[SVID]) अणु
		dev->has_raw_vbi_cap = node_type & 0x0004;
		dev->has_sliced_vbi_cap = node_type & 0x0008;
		dev->has_vbi_cap = dev->has_raw_vbi_cap | dev->has_sliced_vbi_cap;
	पूर्ण

	/* करो we create a meta capture device */
	dev->has_meta_cap = node_type & 0x20000;

	/* sanity checks */
	अगर ((in_type_counter[WEBCAM] || in_type_counter[HDMI]) &&
	    !dev->has_vid_cap && !dev->has_meta_cap) अणु
		v4l2_warn(&dev->v4l2_dev,
			  "Webcam or HDMI input without video or metadata nodes\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((in_type_counter[TV] || in_type_counter[SVID]) &&
	    !dev->has_vid_cap && !dev->has_vbi_cap && !dev->has_meta_cap) अणु
		v4l2_warn(&dev->v4l2_dev,
			  "TV or S-Video input without video, VBI or metadata nodes\n");
		वापस -EINVAL;
	पूर्ण

	/* करो we create a video output device? */
	dev->has_vid_out = node_type & 0x0100;

	/* करो we create a vbi output device? */
	अगर (out_type_counter[SVID]) अणु
		dev->has_raw_vbi_out = node_type & 0x0400;
		dev->has_sliced_vbi_out = node_type & 0x0800;
		dev->has_vbi_out = dev->has_raw_vbi_out | dev->has_sliced_vbi_out;
	पूर्ण

	/* करो we create a metadata output device */
	dev->has_meta_out = node_type & 0x40000;

	/* sanity checks */
	अगर (out_type_counter[SVID] &&
	    !dev->has_vid_out && !dev->has_vbi_out && !dev->has_meta_out) अणु
		v4l2_warn(&dev->v4l2_dev,
			  "S-Video output without video, VBI or metadata nodes\n");
		वापस -EINVAL;
	पूर्ण
	अगर (out_type_counter[HDMI] && !dev->has_vid_out && !dev->has_meta_out) अणु
		v4l2_warn(&dev->v4l2_dev,
			  "HDMI output without video or metadata nodes\n");
		वापस -EINVAL;
	पूर्ण

	/* करो we create a radio receiver device? */
	dev->has_radio_rx = node_type & 0x0010;

	/* करो we create a radio transmitter device? */
	dev->has_radio_tx = node_type & 0x1000;

	/* करो we create a software defined radio capture device? */
	dev->has_sdr_cap = node_type & 0x0020;

	/* करो we have a TV tuner? */
	dev->has_tv_tuner = in_type_counter[TV];

	/* करो we have a tuner? */
	*has_tuner = ((dev->has_vid_cap || dev->has_vbi_cap) && in_type_counter[TV]) ||
		      dev->has_radio_rx || dev->has_sdr_cap;

	/* करो we have a modulator? */
	*has_modulator = dev->has_radio_tx;

	अगर (dev->has_vid_cap)
		/* करो we have a framebuffer क्रम overlay testing? */
		dev->has_fb = node_type & 0x10000;

	/* can we करो crop/compose/scaling जबतक capturing? */
	अगर (no_error_inj && *ccs_cap == -1)
		*ccs_cap = 7;

	/* अगर ccs_cap == -1, then the user can select it using controls */
	अगर (*ccs_cap != -1) अणु
		dev->has_crop_cap = *ccs_cap & 1;
		dev->has_compose_cap = *ccs_cap & 2;
		dev->has_scaler_cap = *ccs_cap & 4;
		v4l2_info(&dev->v4l2_dev, "Capture Crop: %c Compose: %c Scaler: %c\n",
			dev->has_crop_cap ? 'Y' : 'N',
			dev->has_compose_cap ? 'Y' : 'N',
			dev->has_scaler_cap ? 'Y' : 'N');
	पूर्ण

	/* can we करो crop/compose/scaling with video output? */
	अगर (no_error_inj && *ccs_out == -1)
		*ccs_out = 7;

	/* अगर ccs_out == -1, then the user can select it using controls */
	अगर (*ccs_out != -1) अणु
		dev->has_crop_out = *ccs_out & 1;
		dev->has_compose_out = *ccs_out & 2;
		dev->has_scaler_out = *ccs_out & 4;
		v4l2_info(&dev->v4l2_dev, "Output Crop: %c Compose: %c Scaler: %c\n",
			dev->has_crop_out ? 'Y' : 'N',
			dev->has_compose_out ? 'Y' : 'N',
			dev->has_scaler_out ? 'Y' : 'N');
	पूर्ण

	/* करो we create a touch capture device */
	dev->has_touch_cap = node_type & 0x80000;

	वापस 0;
पूर्ण

अटल व्योम vivid_set_capabilities(काष्ठा vivid_dev *dev)
अणु
	अगर (dev->has_vid_cap) अणु
		/* set up the capabilities of the video capture device */
		dev->vid_cap_caps = dev->multiplanar ?
			V4L2_CAP_VIDEO_CAPTURE_MPLANE :
			V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OVERLAY;
		dev->vid_cap_caps |= V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		अगर (dev->has_audio_inमाला_दो)
			dev->vid_cap_caps |= V4L2_CAP_AUDIO;
		अगर (dev->has_tv_tuner)
			dev->vid_cap_caps |= V4L2_CAP_TUNER;
	पूर्ण
	अगर (dev->has_vid_out) अणु
		/* set up the capabilities of the video output device */
		dev->vid_out_caps = dev->multiplanar ?
			V4L2_CAP_VIDEO_OUTPUT_MPLANE :
			V4L2_CAP_VIDEO_OUTPUT;
		अगर (dev->has_fb)
			dev->vid_out_caps |= V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
		dev->vid_out_caps |= V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		अगर (dev->has_audio_outमाला_दो)
			dev->vid_out_caps |= V4L2_CAP_AUDIO;
	पूर्ण
	अगर (dev->has_vbi_cap) अणु
		/* set up the capabilities of the vbi capture device */
		dev->vbi_cap_caps = (dev->has_raw_vbi_cap ? V4L2_CAP_VBI_CAPTURE : 0) |
				    (dev->has_sliced_vbi_cap ? V4L2_CAP_SLICED_VBI_CAPTURE : 0);
		dev->vbi_cap_caps |= V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		अगर (dev->has_audio_inमाला_दो)
			dev->vbi_cap_caps |= V4L2_CAP_AUDIO;
		अगर (dev->has_tv_tuner)
			dev->vbi_cap_caps |= V4L2_CAP_TUNER;
	पूर्ण
	अगर (dev->has_vbi_out) अणु
		/* set up the capabilities of the vbi output device */
		dev->vbi_out_caps = (dev->has_raw_vbi_out ? V4L2_CAP_VBI_OUTPUT : 0) |
				    (dev->has_sliced_vbi_out ? V4L2_CAP_SLICED_VBI_OUTPUT : 0);
		dev->vbi_out_caps |= V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		अगर (dev->has_audio_outमाला_दो)
			dev->vbi_out_caps |= V4L2_CAP_AUDIO;
	पूर्ण
	अगर (dev->has_sdr_cap) अणु
		/* set up the capabilities of the sdr capture device */
		dev->sdr_cap_caps = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER;
		dev->sdr_cap_caps |= V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
	पूर्ण
	/* set up the capabilities of the radio receiver device */
	अगर (dev->has_radio_rx)
		dev->radio_rx_caps = V4L2_CAP_RADIO | V4L2_CAP_RDS_CAPTURE |
				     V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_TUNER |
				     V4L2_CAP_READWRITE;
	/* set up the capabilities of the radio transmitter device */
	अगर (dev->has_radio_tx)
		dev->radio_tx_caps = V4L2_CAP_RDS_OUTPUT | V4L2_CAP_MODULATOR |
				     V4L2_CAP_READWRITE;

	/* set up the capabilities of meta capture device */
	अगर (dev->has_meta_cap) अणु
		dev->meta_cap_caps = V4L2_CAP_META_CAPTURE |
				     V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		अगर (dev->has_audio_inमाला_दो)
			dev->meta_cap_caps |= V4L2_CAP_AUDIO;
		अगर (dev->has_tv_tuner)
			dev->meta_cap_caps |= V4L2_CAP_TUNER;
	पूर्ण
	/* set up the capabilities of meta output device */
	अगर (dev->has_meta_out) अणु
		dev->meta_out_caps = V4L2_CAP_META_OUTPUT |
				     V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		अगर (dev->has_audio_outमाला_दो)
			dev->meta_out_caps |= V4L2_CAP_AUDIO;
	पूर्ण
	/* set up the capabilities of the touch capture device */
	अगर (dev->has_touch_cap) अणु
		dev->touch_cap_caps = V4L2_CAP_TOUCH | V4L2_CAP_STREAMING |
				      V4L2_CAP_READWRITE;
		dev->touch_cap_caps |= dev->multiplanar ?
			V4L2_CAP_VIDEO_CAPTURE_MPLANE : V4L2_CAP_VIDEO_CAPTURE;
	पूर्ण
पूर्ण

अटल व्योम vivid_disable_unused_ioctls(काष्ठा vivid_dev *dev,
					bool has_tuner,
					bool has_modulator,
					अचिन्हित in_type_counter[4],
					अचिन्हित out_type_counter[4])
अणु
	/* disable invalid ioctls based on the feature set */
	अगर (!dev->has_audio_inमाला_दो) अणु
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_ENUMAUDIO);
		v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_ENUMAUDIO);
		v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_ENUMAUDIO);
	पूर्ण
	अगर (!dev->has_audio_outमाला_दो) अणु
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_S_AUDOUT);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_G_AUDOUT);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_ENUMAUDOUT);
		v4l2_disable_ioctl(&dev->vbi_out_dev, VIDIOC_S_AUDOUT);
		v4l2_disable_ioctl(&dev->vbi_out_dev, VIDIOC_G_AUDOUT);
		v4l2_disable_ioctl(&dev->vbi_out_dev, VIDIOC_ENUMAUDOUT);
		v4l2_disable_ioctl(&dev->meta_out_dev, VIDIOC_S_AUDOUT);
		v4l2_disable_ioctl(&dev->meta_out_dev, VIDIOC_G_AUDOUT);
		v4l2_disable_ioctl(&dev->meta_out_dev, VIDIOC_ENUMAUDOUT);
	पूर्ण
	अगर (!in_type_counter[TV] && !in_type_counter[SVID]) अणु
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_S_STD);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_G_STD);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_ENUMSTD);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_QUERYSTD);
	पूर्ण
	अगर (!out_type_counter[SVID]) अणु
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_S_STD);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_G_STD);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_ENUMSTD);
	पूर्ण
	अगर (!has_tuner && !has_modulator) अणु
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_G_FREQUENCY);
	पूर्ण
	अगर (!has_tuner) अणु
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_G_TUNER);
	पूर्ण
	अगर (in_type_counter[HDMI] == 0) अणु
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_S_EDID);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_G_EDID);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_DV_TIMINGS_CAP);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_G_DV_TIMINGS);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_S_DV_TIMINGS);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_ENUM_DV_TIMINGS);
		v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_QUERY_DV_TIMINGS);
	पूर्ण
	अगर (out_type_counter[HDMI] == 0) अणु
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_G_EDID);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_DV_TIMINGS_CAP);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_G_DV_TIMINGS);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_S_DV_TIMINGS);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_ENUM_DV_TIMINGS);
	पूर्ण
	अगर (!dev->has_fb) अणु
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_G_FBUF);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_S_FBUF);
		v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_OVERLAY);
	पूर्ण
	v4l2_disable_ioctl(&dev->vid_cap_dev, VIDIOC_S_HW_FREQ_SEEK);
	v4l2_disable_ioctl(&dev->vbi_cap_dev, VIDIOC_S_HW_FREQ_SEEK);
	v4l2_disable_ioctl(&dev->sdr_cap_dev, VIDIOC_S_HW_FREQ_SEEK);
	v4l2_disable_ioctl(&dev->meta_cap_dev, VIDIOC_S_HW_FREQ_SEEK);
	v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_S_FREQUENCY);
	v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_G_FREQUENCY);
	v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_ENUM_FRAMESIZES);
	v4l2_disable_ioctl(&dev->vid_out_dev, VIDIOC_ENUM_FRAMEINTERVALS);
	v4l2_disable_ioctl(&dev->vbi_out_dev, VIDIOC_S_FREQUENCY);
	v4l2_disable_ioctl(&dev->vbi_out_dev, VIDIOC_G_FREQUENCY);
	v4l2_disable_ioctl(&dev->meta_out_dev, VIDIOC_S_FREQUENCY);
	v4l2_disable_ioctl(&dev->meta_out_dev, VIDIOC_G_FREQUENCY);
	v4l2_disable_ioctl(&dev->touch_cap_dev, VIDIOC_S_PARM);
	v4l2_disable_ioctl(&dev->touch_cap_dev, VIDIOC_ENUM_FRAMESIZES);
	v4l2_disable_ioctl(&dev->touch_cap_dev, VIDIOC_ENUM_FRAMEINTERVALS);
पूर्ण

अटल पूर्णांक vivid_init_dv_timings(काष्ठा vivid_dev *dev)
अणु
	पूर्णांक i;

	जबतक (v4l2_dv_timings_presets[dev->query_dv_timings_size].bt.width)
		dev->query_dv_timings_size++;

	/*
	 * Create a अक्षर poपूर्णांकer array that poपूर्णांकs to the names of all the
	 * preset timings
	 */
	dev->query_dv_timings_qmenu = kदो_स्मृति_array(dev->query_dv_timings_size,
						    माप(अक्षर *), GFP_KERNEL);
	/*
	 * Create a string array containing the names of all the preset
	 * timings. Each name is max 31 अक्षरs दीर्घ (+ terminating 0).
	 */
	dev->query_dv_timings_qmenu_strings =
		kदो_स्मृति_array(dev->query_dv_timings_size, 32, GFP_KERNEL);

	अगर (!dev->query_dv_timings_qmenu ||
	    !dev->query_dv_timings_qmenu_strings)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev->query_dv_timings_size; i++) अणु
		स्थिर काष्ठा v4l2_bt_timings *bt = &v4l2_dv_timings_presets[i].bt;
		अक्षर *p = dev->query_dv_timings_qmenu_strings + i * 32;
		u32 htot, vtot;

		dev->query_dv_timings_qmenu[i] = p;

		htot = V4L2_DV_BT_FRAME_WIDTH(bt);
		vtot = V4L2_DV_BT_FRAME_HEIGHT(bt);
		snम_लिखो(p, 32, "%ux%u%s%u",
			bt->width, bt->height, bt->पूर्णांकerlaced ? "i" : "p",
			(u32)bt->pixelघड़ी / (htot * vtot));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vivid_create_queues(काष्ठा vivid_dev *dev)
अणु
	पूर्णांक ret;

	/* start creating the vb2 queues */
	अगर (dev->has_vid_cap) अणु
		/* initialize vid_cap queue */
		ret = vivid_create_queue(dev, &dev->vb_vid_cap_q,
					 V4L2_BUF_TYPE_VIDEO_CAPTURE, 2,
					 &vivid_vid_cap_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_vid_out) अणु
		/* initialize vid_out queue */
		ret = vivid_create_queue(dev, &dev->vb_vid_out_q,
					 V4L2_BUF_TYPE_VIDEO_OUTPUT, 2,
					 &vivid_vid_out_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_vbi_cap) अणु
		/* initialize vbi_cap queue */
		ret = vivid_create_queue(dev, &dev->vb_vbi_cap_q,
					 V4L2_BUF_TYPE_VBI_CAPTURE, 2,
					 &vivid_vbi_cap_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_vbi_out) अणु
		/* initialize vbi_out queue */
		ret = vivid_create_queue(dev, &dev->vb_vbi_out_q,
					 V4L2_BUF_TYPE_VBI_OUTPUT, 2,
					 &vivid_vbi_out_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_sdr_cap) अणु
		/* initialize sdr_cap queue */
		ret = vivid_create_queue(dev, &dev->vb_sdr_cap_q,
					 V4L2_BUF_TYPE_SDR_CAPTURE, 8,
					 &vivid_sdr_cap_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_meta_cap) अणु
		/* initialize meta_cap queue */
		ret = vivid_create_queue(dev, &dev->vb_meta_cap_q,
					 V4L2_BUF_TYPE_META_CAPTURE, 2,
					 &vivid_meta_cap_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_meta_out) अणु
		/* initialize meta_out queue */
		ret = vivid_create_queue(dev, &dev->vb_meta_out_q,
					 V4L2_BUF_TYPE_META_OUTPUT, 1,
					 &vivid_meta_out_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_touch_cap) अणु
		/* initialize touch_cap queue */
		ret = vivid_create_queue(dev, &dev->vb_touch_cap_q,
					 V4L2_BUF_TYPE_VIDEO_CAPTURE, 1,
					 &vivid_touch_cap_qops);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->has_fb) अणु
		/* Create framebuffer क्रम testing capture/output overlay */
		ret = vivid_fb_init(dev);
		अगर (ret)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "Framebuffer device registered as fb%d\n",
			  dev->fb_info.node);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vivid_create_devnodes(काष्ठा platक्रमm_device *pdev,
				 काष्ठा vivid_dev *dev, पूर्णांक inst,
				 अचिन्हित पूर्णांक cec_tx_bus_cnt,
				 v4l2_std_id tvnorms_cap,
				 v4l2_std_id tvnorms_out,
				 अचिन्हित in_type_counter[4],
				 अचिन्हित out_type_counter[4])
अणु
	काष्ठा video_device *vfd;
	पूर्णांक ret;

	अगर (dev->has_vid_cap) अणु
		vfd = &dev->vid_cap_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-vid-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->vid_cap_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_vid_cap_q;
		vfd->tvnorms = tvnorms_cap;

		/*
		 * Provide a mutex to v4l2 core. It will be used to protect
		 * all fops and v4l2 ioctls.
		 */
		vfd->lock = &dev->mutex;
		video_set_drvdata(vfd, dev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->vid_cap_pad.flags = MEDIA_PAD_FL_SINK;
		ret = media_entity_pads_init(&vfd->entity, 1, &dev->vid_cap_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर

#अगर_घोषित CONFIG_VIDEO_VIVID_CEC
		अगर (in_type_counter[HDMI]) अणु
			ret = cec_रेजिस्टर_adapter(dev->cec_rx_adap, &pdev->dev);
			अगर (ret < 0) अणु
				cec_delete_adapter(dev->cec_rx_adap);
				dev->cec_rx_adap = शून्य;
				वापस ret;
			पूर्ण
			cec_s_phys_addr(dev->cec_rx_adap, 0, false);
			v4l2_info(&dev->v4l2_dev, "CEC adapter %s registered for HDMI input 0\n",
				  dev_name(&dev->cec_rx_adap->devnode.dev));
		पूर्ण
#पूर्ण_अगर

		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, vid_cap_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "V4L2 capture device registered as %s\n",
					  video_device_node_name(vfd));
	पूर्ण

	अगर (dev->has_vid_out) अणु
#अगर_घोषित CONFIG_VIDEO_VIVID_CEC
		पूर्णांक i;
#पूर्ण_अगर
		vfd = &dev->vid_out_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-vid-out", inst);
		vfd->vfl_dir = VFL_सूची_TX;
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->vid_out_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_vid_out_q;
		vfd->tvnorms = tvnorms_out;

		/*
		 * Provide a mutex to v4l2 core. It will be used to protect
		 * all fops and v4l2 ioctls.
		 */
		vfd->lock = &dev->mutex;
		video_set_drvdata(vfd, dev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->vid_out_pad.flags = MEDIA_PAD_FL_SOURCE;
		ret = media_entity_pads_init(&vfd->entity, 1, &dev->vid_out_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर

#अगर_घोषित CONFIG_VIDEO_VIVID_CEC
		क्रम (i = 0; i < cec_tx_bus_cnt; i++) अणु
			ret = cec_रेजिस्टर_adapter(dev->cec_tx_adap[i], &pdev->dev);
			अगर (ret < 0) अणु
				क्रम (; i < cec_tx_bus_cnt; i++) अणु
					cec_delete_adapter(dev->cec_tx_adap[i]);
					dev->cec_tx_adap[i] = शून्य;
				पूर्ण
				वापस ret;
			पूर्ण
			v4l2_info(&dev->v4l2_dev, "CEC adapter %s registered for HDMI output %d\n",
				  dev_name(&dev->cec_tx_adap[i]->devnode.dev), i);
			अगर (i < out_type_counter[HDMI])
				cec_s_phys_addr(dev->cec_tx_adap[i], (i + 1) << 12, false);
			अन्यथा
				cec_s_phys_addr(dev->cec_tx_adap[i], 0x1000, false);
		पूर्ण
#पूर्ण_अगर

		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, vid_out_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "V4L2 output device registered as %s\n",
					  video_device_node_name(vfd));
	पूर्ण

	अगर (dev->has_vbi_cap) अणु
		vfd = &dev->vbi_cap_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-vbi-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->vbi_cap_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_vbi_cap_q;
		vfd->lock = &dev->mutex;
		vfd->tvnorms = tvnorms_cap;
		video_set_drvdata(vfd, dev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->vbi_cap_pad.flags = MEDIA_PAD_FL_SINK;
		ret = media_entity_pads_init(&vfd->entity, 1, &dev->vbi_cap_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर

		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VBI, vbi_cap_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "V4L2 capture device registered as %s, supports %s VBI\n",
					  video_device_node_name(vfd),
					  (dev->has_raw_vbi_cap && dev->has_sliced_vbi_cap) ?
					  "raw and sliced" :
					  (dev->has_raw_vbi_cap ? "raw" : "sliced"));
	पूर्ण

	अगर (dev->has_vbi_out) अणु
		vfd = &dev->vbi_out_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-vbi-out", inst);
		vfd->vfl_dir = VFL_सूची_TX;
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->vbi_out_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_vbi_out_q;
		vfd->lock = &dev->mutex;
		vfd->tvnorms = tvnorms_out;
		video_set_drvdata(vfd, dev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->vbi_out_pad.flags = MEDIA_PAD_FL_SOURCE;
		ret = media_entity_pads_init(&vfd->entity, 1, &dev->vbi_out_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर

		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VBI, vbi_out_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "V4L2 output device registered as %s, supports %s VBI\n",
					  video_device_node_name(vfd),
					  (dev->has_raw_vbi_out && dev->has_sliced_vbi_out) ?
					  "raw and sliced" :
					  (dev->has_raw_vbi_out ? "raw" : "sliced"));
	पूर्ण

	अगर (dev->has_sdr_cap) अणु
		vfd = &dev->sdr_cap_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-sdr-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->sdr_cap_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_sdr_cap_q;
		vfd->lock = &dev->mutex;
		video_set_drvdata(vfd, dev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->sdr_cap_pad.flags = MEDIA_PAD_FL_SINK;
		ret = media_entity_pads_init(&vfd->entity, 1, &dev->sdr_cap_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर

		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_SDR, sdr_cap_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "V4L2 capture device registered as %s\n",
					  video_device_node_name(vfd));
	पूर्ण

	अगर (dev->has_radio_rx) अणु
		vfd = &dev->radio_rx_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-rad-rx", inst);
		vfd->fops = &vivid_radio_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->radio_rx_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->lock = &dev->mutex;
		video_set_drvdata(vfd, dev);

		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_RADIO, radio_rx_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "V4L2 receiver device registered as %s\n",
					  video_device_node_name(vfd));
	पूर्ण

	अगर (dev->has_radio_tx) अणु
		vfd = &dev->radio_tx_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-rad-tx", inst);
		vfd->vfl_dir = VFL_सूची_TX;
		vfd->fops = &vivid_radio_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->radio_tx_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->lock = &dev->mutex;
		video_set_drvdata(vfd, dev);

		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_RADIO, radio_tx_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev, "V4L2 transmitter device registered as %s\n",
					  video_device_node_name(vfd));
	पूर्ण

	अगर (dev->has_meta_cap) अणु
		vfd = &dev->meta_cap_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-meta-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->meta_cap_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_meta_cap_q;
		vfd->lock = &dev->mutex;
		vfd->tvnorms = tvnorms_cap;
		video_set_drvdata(vfd, dev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->meta_cap_pad.flags = MEDIA_PAD_FL_SINK;
		ret = media_entity_pads_init(&vfd->entity, 1,
					     &dev->meta_cap_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर
		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO,
					    meta_cap_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev,
			  "V4L2 metadata capture device registered as %s\n",
			  video_device_node_name(vfd));
	पूर्ण

	अगर (dev->has_meta_out) अणु
		vfd = &dev->meta_out_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-meta-out", inst);
		vfd->vfl_dir = VFL_सूची_TX;
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->meta_out_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_meta_out_q;
		vfd->lock = &dev->mutex;
		vfd->tvnorms = tvnorms_out;
		video_set_drvdata(vfd, dev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->meta_out_pad.flags = MEDIA_PAD_FL_SOURCE;
		ret = media_entity_pads_init(&vfd->entity, 1,
					     &dev->meta_out_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर
		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO,
					    meta_out_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev,
			  "V4L2 metadata output device registered as %s\n",
			  video_device_node_name(vfd));
	पूर्ण

	अगर (dev->has_touch_cap) अणु
		vfd = &dev->touch_cap_dev;
		snम_लिखो(vfd->name, माप(vfd->name),
			 "vivid-%03d-touch-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctl_ops = &vivid_ioctl_ops;
		vfd->device_caps = dev->touch_cap_caps;
		vfd->release = video_device_release_empty;
		vfd->v4l2_dev = &dev->v4l2_dev;
		vfd->queue = &dev->vb_touch_cap_q;
		vfd->tvnorms = tvnorms_cap;
		vfd->lock = &dev->mutex;
		video_set_drvdata(vfd, dev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		dev->touch_cap_pad.flags = MEDIA_PAD_FL_SINK;
		ret = media_entity_pads_init(&vfd->entity, 1,
					     &dev->touch_cap_pad);
		अगर (ret)
			वापस ret;
#पूर्ण_अगर
		ret = video_रेजिस्टर_device(vfd, VFL_TYPE_TOUCH,
					    touch_cap_nr[inst]);
		अगर (ret < 0)
			वापस ret;
		v4l2_info(&dev->v4l2_dev,
			  "V4L2 touch capture device registered as %s\n",
			  video_device_node_name(vfd));
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	/* Register the media device */
	ret = media_device_रेजिस्टर(&dev->mdev);
	अगर (ret) अणु
		dev_err(dev->mdev.dev,
			"media device register failed (err=%d)\n", ret);
		वापस ret;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक vivid_create_instance(काष्ठा platक्रमm_device *pdev, पूर्णांक inst)
अणु
	अटल स्थिर काष्ठा v4l2_dv_timings def_dv_timings =
					V4L2_DV_BT_CEA_1280X720P60;
	अचिन्हित in_type_counter[4] = अणु 0, 0, 0, 0 पूर्ण;
	अचिन्हित out_type_counter[4] = अणु 0, 0, 0, 0 पूर्ण;
	पूर्णांक ccs_cap = ccs_cap_mode[inst];
	पूर्णांक ccs_out = ccs_out_mode[inst];
	bool has_tuner;
	bool has_modulator;
	काष्ठा vivid_dev *dev;
	अचिन्हित node_type = node_types[inst];
	v4l2_std_id tvnorms_cap = 0, tvnorms_out = 0;
	अचिन्हित पूर्णांक cec_tx_bus_cnt = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/* allocate मुख्य vivid state काष्ठाure */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->inst = inst;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	dev->v4l2_dev.mdev = &dev->mdev;

	/* Initialize media device */
	strscpy(dev->mdev.model, VIVID_MODULE_NAME, माप(dev->mdev.model));
	snम_लिखो(dev->mdev.bus_info, माप(dev->mdev.bus_info),
		 "platform:%s-%03d", VIVID_MODULE_NAME, inst);
	dev->mdev.dev = &pdev->dev;
	media_device_init(&dev->mdev);
	dev->mdev.ops = &vivid_media_ops;
#पूर्ण_अगर

	/* रेजिस्टर v4l2_device */
	snम_लिखो(dev->v4l2_dev.name, माप(dev->v4l2_dev.name),
			"%s-%03d", VIVID_MODULE_NAME, inst);
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		kमुक्त(dev);
		वापस ret;
	पूर्ण
	dev->v4l2_dev.release = vivid_dev_release;

	ret = vivid_detect_feature_set(dev, inst, node_type,
				       &has_tuner, &has_modulator,
				       &ccs_cap, &ccs_out,
				       in_type_counter, out_type_counter);
	अगर (ret)
		जाओ मुक्त_dev;

	vivid_set_capabilities(dev);

	ret = -ENOMEM;
	/* initialize the test pattern generator */
	tpg_init(&dev->tpg, 640, 360);
	अगर (tpg_alloc(&dev->tpg, array_size(MAX_WIDTH, MAX_ZOOM)))
		जाओ मुक्त_dev;
	dev->scaled_line = vzalloc(array_size(MAX_WIDTH, MAX_ZOOM));
	अगर (!dev->scaled_line)
		जाओ मुक्त_dev;
	dev->blended_line = vzalloc(array_size(MAX_WIDTH, MAX_ZOOM));
	अगर (!dev->blended_line)
		जाओ मुक्त_dev;

	/* load the edid */
	dev->edid = vदो_स्मृति(array_size(256, 128));
	अगर (!dev->edid)
		जाओ मुक्त_dev;

	ret = vivid_init_dv_timings(dev);
	अगर (ret < 0)
		जाओ मुक्त_dev;

	vivid_disable_unused_ioctls(dev, has_tuner, has_modulator,
				    in_type_counter, out_type_counter);

	/* configure पूर्णांकernal data */
	dev->fmt_cap = &vivid_क्रमmats[0];
	dev->fmt_out = &vivid_क्रमmats[0];
	अगर (!dev->multiplanar)
		vivid_क्रमmats[0].data_offset[0] = 0;
	dev->webcam_size_idx = 1;
	dev->webcam_ival_idx = 3;
	tpg_s_fourcc(&dev->tpg, dev->fmt_cap->fourcc);
	dev->std_out = V4L2_STD_PAL;
	अगर (dev->input_type[0] == TV || dev->input_type[0] == SVID)
		tvnorms_cap = V4L2_STD_ALL;
	अगर (dev->output_type[0] == SVID)
		tvnorms_out = V4L2_STD_ALL;
	क्रम (i = 0; i < MAX_INPUTS; i++) अणु
		dev->dv_timings_cap[i] = def_dv_timings;
		dev->std_cap[i] = V4L2_STD_PAL;
	पूर्ण
	dev->dv_timings_out = def_dv_timings;
	dev->tv_freq = 2804 /* 175.25 * 16 */;
	dev->tv_audmode = V4L2_TUNER_MODE_STEREO;
	dev->tv_field_cap = V4L2_FIELD_INTERLACED;
	dev->tv_field_out = V4L2_FIELD_INTERLACED;
	dev->radio_rx_freq = 95000 * 16;
	dev->radio_rx_audmode = V4L2_TUNER_MODE_STEREO;
	अगर (dev->has_radio_tx) अणु
		dev->radio_tx_freq = 95500 * 16;
		dev->radio_rds_loop = false;
	पूर्ण
	dev->radio_tx_subchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_RDS;
	dev->sdr_adc_freq = 300000;
	dev->sdr_fm_freq = 50000000;
	dev->sdr_pixelक्रमmat = V4L2_SDR_FMT_CU8;
	dev->sdr_buffersize = SDR_CAP_SAMPLES_PER_BUF * 2;

	dev->edid_max_blocks = dev->edid_blocks = 2;
	स_नकल(dev->edid, vivid_hdmi_edid, माप(vivid_hdmi_edid));
	dev->radio_rds_init_समय = kसमय_get();

	/* create all controls */
	ret = vivid_create_controls(dev, ccs_cap == -1, ccs_out == -1, no_error_inj,
			in_type_counter[TV] || in_type_counter[SVID] ||
			out_type_counter[SVID],
			in_type_counter[HDMI] || out_type_counter[HDMI]);
	अगर (ret)
		जाओ unreg_dev;

	/* enable/disable पूर्णांकerface specअगरic controls */
	अगर (dev->num_outमाला_दो && dev->output_type[0] != HDMI)
		v4l2_ctrl_activate(dev->ctrl_display_present, false);
	अगर (dev->num_inमाला_दो && dev->input_type[0] != HDMI) अणु
		v4l2_ctrl_activate(dev->ctrl_dv_timings_संकेत_mode, false);
		v4l2_ctrl_activate(dev->ctrl_dv_timings, false);
	पूर्ण अन्यथा अगर (dev->num_inमाला_दो && dev->input_type[0] == HDMI) अणु
		v4l2_ctrl_activate(dev->ctrl_std_संकेत_mode, false);
		v4l2_ctrl_activate(dev->ctrl_standard, false);
	पूर्ण

	/*
	 * update the capture and output क्रमmats to करो a proper initial
	 * configuration.
	 */
	vivid_update_क्रमmat_cap(dev, false);
	vivid_update_क्रमmat_out(dev);

	/* initialize overlay */
	dev->fb_cap.fmt.width = dev->src_rect.width;
	dev->fb_cap.fmt.height = dev->src_rect.height;
	dev->fb_cap.fmt.pixelक्रमmat = dev->fmt_cap->fourcc;
	dev->fb_cap.fmt.bytesperline = dev->src_rect.width * tpg_g_twopixelsize(&dev->tpg, 0) / 2;
	dev->fb_cap.fmt.sizeimage = dev->src_rect.height * dev->fb_cap.fmt.bytesperline;

	/* update touch configuration */
	dev->समयperframe_tch_cap.numerator = 1;
	dev->समयperframe_tch_cap.denominator = 10;
	vivid_set_touch(dev, 0);

	/* initialize locks */
	spin_lock_init(&dev->slock);
	mutex_init(&dev->mutex);

	/* init dma queues */
	INIT_LIST_HEAD(&dev->vid_cap_active);
	INIT_LIST_HEAD(&dev->vid_out_active);
	INIT_LIST_HEAD(&dev->vbi_cap_active);
	INIT_LIST_HEAD(&dev->vbi_out_active);
	INIT_LIST_HEAD(&dev->sdr_cap_active);
	INIT_LIST_HEAD(&dev->meta_cap_active);
	INIT_LIST_HEAD(&dev->meta_out_active);
	INIT_LIST_HEAD(&dev->touch_cap_active);

	INIT_LIST_HEAD(&dev->cec_work_list);
	spin_lock_init(&dev->cec_slock);
	/*
	 * Same as create_singlethपढ़ो_workqueue, but now I can use the
	 * string क्रमmatting of alloc_ordered_workqueue.
	 */
	dev->cec_workqueue = alloc_ordered_workqueue("vivid-%03d-cec",
						     WQ_MEM_RECLAIM, inst);
	अगर (!dev->cec_workqueue) अणु
		ret = -ENOMEM;
		जाओ unreg_dev;
	पूर्ण

	अगर (allocators[inst] == 1)
		dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));

	ret = vivid_create_queues(dev);
	अगर (ret)
		जाओ unreg_dev;

#अगर_घोषित CONFIG_VIDEO_VIVID_CEC
	अगर (dev->has_vid_cap && in_type_counter[HDMI]) अणु
		काष्ठा cec_adapter *adap;

		adap = vivid_cec_alloc_adap(dev, 0, false);
		ret = PTR_ERR_OR_ZERO(adap);
		अगर (ret < 0)
			जाओ unreg_dev;
		dev->cec_rx_adap = adap;
	पूर्ण

	अगर (dev->has_vid_out) अणु
		क्रम (i = 0; i < dev->num_outमाला_दो; i++) अणु
			काष्ठा cec_adapter *adap;

			अगर (dev->output_type[i] != HDMI)
				जारी;

			dev->cec_output2bus_map[i] = cec_tx_bus_cnt;
			adap = vivid_cec_alloc_adap(dev, cec_tx_bus_cnt, true);
			ret = PTR_ERR_OR_ZERO(adap);
			अगर (ret < 0) अणु
				क्रम (i = 0; i < dev->num_outमाला_दो; i++)
					cec_delete_adapter(dev->cec_tx_adap[i]);
				जाओ unreg_dev;
			पूर्ण

			dev->cec_tx_adap[cec_tx_bus_cnt] = adap;
			cec_tx_bus_cnt++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_vid_cap);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_vid_out);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_vbi_cap);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_vbi_out);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_radio_rx);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_radio_tx);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_sdr_cap);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_meta_cap);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_meta_out);
	v4l2_ctrl_handler_setup(&dev->ctrl_hdl_touch_cap);

	/* finally start creating the device nodes */
	ret = vivid_create_devnodes(pdev, dev, inst, cec_tx_bus_cnt,
				    tvnorms_cap, tvnorms_out,
				    in_type_counter, out_type_counter);
	अगर (ret)
		जाओ unreg_dev;

	/* Now that everything is fine, let's add it to device list */
	vivid_devs[inst] = dev;

	वापस 0;

unreg_dev:
	vb2_video_unरेजिस्टर_device(&dev->touch_cap_dev);
	vb2_video_unरेजिस्टर_device(&dev->meta_out_dev);
	vb2_video_unरेजिस्टर_device(&dev->meta_cap_dev);
	video_unरेजिस्टर_device(&dev->radio_tx_dev);
	video_unरेजिस्टर_device(&dev->radio_rx_dev);
	vb2_video_unरेजिस्टर_device(&dev->sdr_cap_dev);
	vb2_video_unरेजिस्टर_device(&dev->vbi_out_dev);
	vb2_video_unरेजिस्टर_device(&dev->vbi_cap_dev);
	vb2_video_unरेजिस्टर_device(&dev->vid_out_dev);
	vb2_video_unरेजिस्टर_device(&dev->vid_cap_dev);
	cec_unरेजिस्टर_adapter(dev->cec_rx_adap);
	क्रम (i = 0; i < MAX_OUTPUTS; i++)
		cec_unरेजिस्टर_adapter(dev->cec_tx_adap[i]);
	अगर (dev->cec_workqueue) अणु
		vivid_cec_bus_मुक्त_work(dev);
		destroy_workqueue(dev->cec_workqueue);
	पूर्ण
मुक्त_dev:
	v4l2_device_put(&dev->v4l2_dev);
	वापस ret;
पूर्ण

/* This routine allocates from 1 to n_devs भव drivers.

   The real maximum number of भव drivers will depend on how many drivers
   will succeed. This is limited to the maximum number of devices that
   videodev supports, which is equal to VIDEO_NUM_DEVICES.
 */
अटल पूर्णांक vivid_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा font_desc *font = find_font("VGA8x16");
	पूर्णांक ret = 0, i;

	अगर (font == शून्य) अणु
		pr_err("vivid: could not find font\n");
		वापस -ENODEV;
	पूर्ण

	tpg_set_font(font->data);

	n_devs = clamp_t(अचिन्हित, n_devs, 1, VIVID_MAX_DEVS);

	क्रम (i = 0; i < n_devs; i++) अणु
		ret = vivid_create_instance(pdev, i);
		अगर (ret) अणु
			/* If some instantiations succeeded, keep driver */
			अगर (i)
				ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		pr_err("vivid: error %d while loading driver\n", ret);
		वापस ret;
	पूर्ण

	/* n_devs will reflect the actual number of allocated devices */
	n_devs = i;

	वापस ret;
पूर्ण

अटल पूर्णांक vivid_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vivid_dev *dev;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < n_devs; i++) अणु
		dev = vivid_devs[i];
		अगर (!dev)
			जारी;

		अगर (dev->disconnect_error)
			vivid_reconnect(dev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		media_device_unरेजिस्टर(&dev->mdev);
#पूर्ण_अगर

		अगर (dev->has_vid_cap) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vid_cap_dev));
			vb2_video_unरेजिस्टर_device(&dev->vid_cap_dev);
		पूर्ण
		अगर (dev->has_vid_out) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vid_out_dev));
			vb2_video_unरेजिस्टर_device(&dev->vid_out_dev);
		पूर्ण
		अगर (dev->has_vbi_cap) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vbi_cap_dev));
			vb2_video_unरेजिस्टर_device(&dev->vbi_cap_dev);
		पूर्ण
		अगर (dev->has_vbi_out) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vbi_out_dev));
			vb2_video_unरेजिस्टर_device(&dev->vbi_out_dev);
		पूर्ण
		अगर (dev->has_sdr_cap) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->sdr_cap_dev));
			vb2_video_unरेजिस्टर_device(&dev->sdr_cap_dev);
		पूर्ण
		अगर (dev->has_radio_rx) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->radio_rx_dev));
			video_unरेजिस्टर_device(&dev->radio_rx_dev);
		पूर्ण
		अगर (dev->has_radio_tx) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->radio_tx_dev));
			video_unरेजिस्टर_device(&dev->radio_tx_dev);
		पूर्ण
		अगर (dev->has_fb) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering fb%d\n",
				dev->fb_info.node);
			unरेजिस्टर_framebuffer(&dev->fb_info);
			vivid_fb_release_buffers(dev);
		पूर्ण
		अगर (dev->has_meta_cap) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				  video_device_node_name(&dev->meta_cap_dev));
			vb2_video_unरेजिस्टर_device(&dev->meta_cap_dev);
		पूर्ण
		अगर (dev->has_meta_out) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				  video_device_node_name(&dev->meta_out_dev));
			vb2_video_unरेजिस्टर_device(&dev->meta_out_dev);
		पूर्ण
		अगर (dev->has_touch_cap) अणु
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				  video_device_node_name(&dev->touch_cap_dev));
			vb2_video_unरेजिस्टर_device(&dev->touch_cap_dev);
		पूर्ण
		cec_unरेजिस्टर_adapter(dev->cec_rx_adap);
		क्रम (j = 0; j < MAX_OUTPUTS; j++)
			cec_unरेजिस्टर_adapter(dev->cec_tx_adap[j]);
		अगर (dev->cec_workqueue) अणु
			vivid_cec_bus_मुक्त_work(dev);
			destroy_workqueue(dev->cec_workqueue);
		पूर्ण
		v4l2_device_put(&dev->v4l2_dev);
		vivid_devs[i] = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vivid_pdev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा platक्रमm_device vivid_pdev = अणु
	.name		= "vivid",
	.dev.release	= vivid_pdev_release,
पूर्ण;

अटल काष्ठा platक्रमm_driver vivid_pdrv = अणु
	.probe		= vivid_probe,
	.हटाओ		= vivid_हटाओ,
	.driver		= अणु
		.name	= "vivid",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vivid_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_device_रेजिस्टर(&vivid_pdev);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&vivid_pdrv);
	अगर (ret)
		platक्रमm_device_unरेजिस्टर(&vivid_pdev);

	वापस ret;
पूर्ण

अटल व्योम __निकास vivid_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vivid_pdrv);
	platक्रमm_device_unरेजिस्टर(&vivid_pdev);
पूर्ण

module_init(vivid_init);
module_निकास(vivid_निकास);
