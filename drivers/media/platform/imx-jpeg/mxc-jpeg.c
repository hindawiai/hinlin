<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * V4L2 driver क्रम the JPEG encoder/decoder from i.MX8QXP/i.MX8QM application
 * processors.
 *
 * The multi-planar buffers API is used.
 *
 * Baseline and extended sequential jpeg decoding is supported.
 * Progressive jpeg decoding is not supported by the IP.
 * Supports encode and decode of various क्रमmats:
 *     YUV444, YUV422, YUV420, RGB, ARGB, Gray
 * YUV420 is the only multi-planar क्रमmat supported.
 * Minimum resolution is 64 x 64, maximum 8192 x 8192.
 * To achieve 8192 x 8192, modअगरy in defconfig: CONFIG_CMA_SIZE_MBYTES=320
 * The alignment requirements क्रम the resolution depend on the क्रमmat,
 * multiple of 16 resolutions should work क्रम all क्रमmats.
 * Special workarounds are made in the driver to support NV12 1080p.
 * When decoding, the driver detects image resolution and pixel क्रमmat
 * from the jpeg stream, by parsing the jpeg markers.
 *
 * The IP has 4 slots available क्रम context चयनing, but only slot 0
 * was fully tested to work. Context चयनing is not used by the driver.
 * Each driver instance (context) allocates a slot क्रम itself, but this
 * is postponed until device_run, to allow unlimited खोलोs.
 *
 * The driver submits jobs to the IP by setting up a descriptor क्रम the
 * used slot, and then validating it. The encoder has an additional descriptor
 * क्रम the configuration phase. The driver expects FRM_DONE पूर्णांकerrupt from
 * IP to mark the job as finished.
 *
 * The decoder IP has some limitations regarding the component ID's,
 * but the driver works around this by replacing them in the jpeg stream.
 *
 * A module parameter is available क्रम debug purpose (jpeg_tracing), to enable
 * it, enable dynamic debug क्रम this module and:
 * echo 1 > /sys/module/mxc_jpeg_encdec/parameters/jpeg_tracing
 *
 * This is inspired by the drivers/media/platक्रमm/s5p-jpeg driver
 *
 * Copyright 2018-2019 NXP
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/माला.स>

#समावेश <media/v4l2-jpeg.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "mxc-jpeg-hw.h"
#समावेश "mxc-jpeg.h"

अटल काष्ठा mxc_jpeg_fmt mxc_क्रमmats[] = अणु
	अणु
		.name		= "JPEG",
		.fourcc		= V4L2_PIX_FMT_JPEG,
		.subsampling	= -1,
		.nc		= -1,
		.colplanes	= 1,
		.flags		= MXC_JPEG_FMT_TYPE_ENC,
	पूर्ण,
	अणु
		.name		= "RGB", /*RGBRGB packed क्रमmat*/
		.fourcc		= V4L2_PIX_FMT_RGB24,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
		.nc		= 3,
		.depth		= 24,
		.colplanes	= 1,
		.h_align	= 3,
		.v_align	= 3,
		.flags		= MXC_JPEG_FMT_TYPE_RAW,
	पूर्ण,
	अणु
		.name		= "ARGB", /* ARGBARGB packed क्रमmat */
		.fourcc		= V4L2_PIX_FMT_ARGB32,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
		.nc		= 4,
		.depth		= 32,
		.colplanes	= 1,
		.h_align	= 3,
		.v_align	= 3,
		.flags		= MXC_JPEG_FMT_TYPE_RAW,
	पूर्ण,
	अणु
		.name		= "YUV420", /* 1st plane = Y, 2nd plane = UV */
		.fourcc		= V4L2_PIX_FMT_NV12,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
		.nc		= 3,
		.depth		= 12, /* 6 bytes (4Y + UV) क्रम 4 pixels */
		.colplanes	= 2, /* 1 plane Y, 1 plane UV पूर्णांकerleaved */
		.h_align	= 4,
		.v_align	= 4,
		.flags		= MXC_JPEG_FMT_TYPE_RAW,
	पूर्ण,
	अणु
		.name		= "YUV422", /* YUYV */
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
		.nc		= 3,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 4,
		.v_align	= 3,
		.flags		= MXC_JPEG_FMT_TYPE_RAW,
	पूर्ण,
	अणु
		.name		= "YUV444", /* YUVYUV */
		.fourcc		= V4L2_PIX_FMT_YUV24,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
		.nc		= 3,
		.depth		= 24,
		.colplanes	= 1,
		.h_align	= 3,
		.v_align	= 3,
		.flags		= MXC_JPEG_FMT_TYPE_RAW,
	पूर्ण,
	अणु
		.name		= "Gray", /* Gray (Y8/Y12) or Single Comp */
		.fourcc		= V4L2_PIX_FMT_GREY,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY,
		.nc		= 1,
		.depth		= 8,
		.colplanes	= 1,
		.h_align	= 3,
		.v_align	= 3,
		.flags		= MXC_JPEG_FMT_TYPE_RAW,
	पूर्ण,
पूर्ण;

#घोषणा MXC_JPEG_NUM_FORMATS ARRAY_SIZE(mxc_क्रमmats)

अटल स्थिर पूर्णांक mxc_decode_mode = MXC_JPEG_DECODE;
अटल स्थिर पूर्णांक mxc_encode_mode = MXC_JPEG_ENCODE;

अटल स्थिर काष्ठा of_device_id mxc_jpeg_match[] = अणु
	अणु
		.compatible = "nxp,imx8qxp-jpgdec",
		.data       = &mxc_decode_mode,
	पूर्ण,
	अणु
		.compatible = "nxp,imx8qxp-jpgenc",
		.data       = &mxc_encode_mode,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * शेष configuration stream, 64x64 yuv422
 * split by JPEG marker, so it's easier to modअगरy & use
 */
अटल स्थिर अचिन्हित अक्षर jpeg_soi[] = अणु
	0xFF, 0xD8
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_app0[] = अणु
	0xFF, 0xE0,
	0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00,
	0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
	0x00, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_app14[] = अणु
	0xFF, 0xEE,
	0x00, 0x0E, 0x41, 0x64, 0x6F, 0x62, 0x65,
	0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_dqt[] = अणु
	0xFF, 0xDB,
	0x00, 0x84, 0x00, 0x10, 0x0B, 0x0C, 0x0E,
	0x0C, 0x0A, 0x10, 0x0E, 0x0D, 0x0E, 0x12,
	0x11, 0x10, 0x13, 0x18, 0x28, 0x1A, 0x18,
	0x16, 0x16, 0x18, 0x31, 0x23, 0x25, 0x1D,
	0x28, 0x3A, 0x33, 0x3D, 0x3C, 0x39, 0x33,
	0x38, 0x37, 0x40, 0x48, 0x5C, 0x4E, 0x40,
	0x44, 0x57, 0x45, 0x37, 0x38, 0x50, 0x6D,
	0x51, 0x57, 0x5F, 0x62, 0x67, 0x68, 0x67,
	0x3E, 0x4D, 0x71, 0x79, 0x70, 0x64, 0x78,
	0x5C, 0x65, 0x67, 0x63, 0x01, 0x11, 0x12,
	0x12, 0x18, 0x15, 0x18, 0x2F, 0x1A, 0x1A,
	0x2F, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_sof_maximal[] = अणु
	0xFF, 0xC0,
	0x00, 0x14, 0x08, 0x00, 0x40, 0x00, 0x40,
	0x04, 0x01, 0x11, 0x00, 0x02, 0x11, 0x01,
	0x03, 0x11, 0x01, 0x04, 0x11, 0x01
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_dht[] = अणु
	0xFF, 0xC4,
	0x01, 0xA2, 0x00, 0x00, 0x01, 0x05, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	0x09, 0x0A, 0x0B, 0x10, 0x00, 0x02, 0x01,
	0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05,
	0x04, 0x04, 0x00, 0x00, 0x01, 0x7D, 0x01,
	0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61,
	0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91,
	0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15,
	0x52, 0xD1, 0xF0, 0x24, 0x33, 0x62, 0x72,
	0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19,
	0x1A, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
	0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A,
	0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76,
	0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85,
	0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93,
	0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A,
	0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
	0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,
	0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4,
	0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2,
	0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
	0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,
	0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3,
	0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA,
	0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
	0x0B, 0x11, 0x00, 0x02, 0x01, 0x02, 0x04,
	0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04,
	0x00, 0x01, 0x02, 0x77, 0x00, 0x01, 0x02,
	0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06,
	0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13,
	0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52,
	0xF0, 0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16,
	0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18,
	0x19, 0x1A, 0x26, 0x27, 0x28, 0x29, 0x2A,
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43,
	0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A,
	0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77,
	0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85,
	0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93,
	0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A,
	0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
	0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,
	0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4,
	0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2,
	0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
	0xDA, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
	0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5,
	0xF6, 0xF7, 0xF8, 0xF9, 0xFA
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_dri[] = अणु
	0xFF, 0xDD,
	0x00, 0x04, 0x00, 0x20
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_sos_maximal[] = अणु
	0xFF, 0xDA,
	0x00, 0x0C, 0x04, 0x01, 0x00, 0x02, 0x11, 0x03,
	0x11, 0x04, 0x11, 0x00, 0x3F, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर jpeg_eoi[] = अणु
	0xFF, 0xD9
पूर्ण;

काष्ठा mxc_jpeg_src_buf अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer	b;
	काष्ठा list_head	list;

	/* mxc-jpeg specअगरic */
	bool			dht_needed;
	bool			jpeg_parse_error;
पूर्ण;

अटल अंतरभूत काष्ठा mxc_jpeg_src_buf *vb2_to_mxc_buf(काष्ठा vb2_buffer *vb)
अणु
	वापस container_of(to_vb2_v4l2_buffer(vb),
			    काष्ठा mxc_jpeg_src_buf, b);
पूर्ण

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-3)");

अटल व्योम _bswap16(u16 *a)
अणु
	*a = ((*a & 0x00FF) << 8) | ((*a & 0xFF00) >> 8);
पूर्ण

अटल व्योम prपूर्णांक_mxc_buf(काष्ठा mxc_jpeg_dev *jpeg, काष्ठा vb2_buffer *buf,
			  अचिन्हित दीर्घ len)
अणु
	अचिन्हित पूर्णांक plane_no;
	u32 dma_addr;
	व्योम *vaddr;
	अचिन्हित दीर्घ payload;

	अगर (debug < 3)
		वापस;

	क्रम (plane_no = 0; plane_no < buf->num_planes; plane_no++) अणु
		payload = vb2_get_plane_payload(buf, plane_no);
		अगर (len == 0)
			len = payload;
		dma_addr = vb2_dma_contig_plane_dma_addr(buf, plane_no);
		vaddr = vb2_plane_vaddr(buf, plane_no);
		v4l2_dbg(3, debug, &jpeg->v4l2_dev,
			 "plane %d (vaddr=%p dma_addr=%x payload=%ld):",
			  plane_no, vaddr, dma_addr, payload);
		prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 32, 1,
			       vaddr, len, false);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा mxc_jpeg_ctx *mxc_jpeg_fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा mxc_jpeg_ctx, fh);
पूर्ण

अटल पूर्णांक क्रमागत_fmt(काष्ठा mxc_jpeg_fmt *mxc_क्रमmats, पूर्णांक n,
		    काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, num = 0;

	क्रम (i = 0; i < n; ++i) अणु
		अगर (mxc_क्रमmats[i].flags == type) अणु
			/* index-th क्रमmat of searched type found ? */
			अगर (num == f->index)
				अवरोध;
			/* Correct type but haven't reached our index yet,
			 * just increment per-type index
			 */
			++num;
		पूर्ण
	पूर्ण

	/* Format not found */
	अगर (i >= n)
		वापस -EINVAL;

	strscpy(f->description, mxc_क्रमmats[i].name, माप(f->description));
	f->pixelक्रमmat = mxc_क्रमmats[i].fourcc;

	वापस 0;
पूर्ण

अटल काष्ठा mxc_jpeg_fmt *mxc_jpeg_find_क्रमmat(काष्ठा mxc_jpeg_ctx *ctx,
						 u32 pixelक्रमmat)
अणु
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < MXC_JPEG_NUM_FORMATS; k++) अणु
		काष्ठा mxc_jpeg_fmt *fmt = &mxc_क्रमmats[k];

		अगर (fmt->fourcc == pixelक्रमmat)
			वापस fmt;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल क्रमागत mxc_jpeg_image_क्रमmat mxc_jpeg_fourcc_to_imgfmt(u32 fourcc)
अणु
	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_GREY:
		वापस MXC_JPEG_GRAY;
	हाल V4L2_PIX_FMT_YUYV:
		वापस MXC_JPEG_YUV422;
	हाल V4L2_PIX_FMT_NV12:
		वापस MXC_JPEG_YUV420;
	हाल V4L2_PIX_FMT_YUV24:
		वापस MXC_JPEG_YUV444;
	हाल V4L2_PIX_FMT_RGB24:
		वापस MXC_JPEG_RGB;
	हाल V4L2_PIX_FMT_ARGB32:
		वापस MXC_JPEG_ARGB;
	शेष:
		वापस MXC_JPEG_INVALID;
	पूर्ण
पूर्ण

अटल काष्ठा mxc_jpeg_q_data *mxc_jpeg_get_q_data(काष्ठा mxc_jpeg_ctx *ctx,
						   क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->out_q;
	वापस &ctx->cap_q;
पूर्ण

अटल व्योम mxc_jpeg_addrs(काष्ठा mxc_jpeg_desc *desc,
			   काष्ठा vb2_buffer *raw_buf,
			   काष्ठा vb2_buffer *jpeg_buf, पूर्णांक offset)
अणु
	पूर्णांक img_fmt = desc->sपंचांग_ctrl & STM_CTRL_IMAGE_FORMAT_MASK;

	desc->buf_base0 = vb2_dma_contig_plane_dma_addr(raw_buf, 0);
	desc->buf_base1 = 0;
	अगर (img_fmt == STM_CTRL_IMAGE_FORMAT(MXC_JPEG_YUV420)) अणु
		WARN_ON(raw_buf->num_planes < 2);
		desc->buf_base1 = vb2_dma_contig_plane_dma_addr(raw_buf, 1);
	पूर्ण
	desc->sपंचांग_bufbase = vb2_dma_contig_plane_dma_addr(jpeg_buf, 0) +
		offset;
पूर्ण

अटल व्योम notअगरy_eos(काष्ठा mxc_jpeg_ctx *ctx)
अणु
	स्थिर काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_EOS
	पूर्ण;

	dev_dbg(ctx->mxc_jpeg->dev, "Notify app event EOS reached");
	v4l2_event_queue_fh(&ctx->fh, &ev);
पूर्ण

अटल व्योम notअगरy_src_chg(काष्ठा mxc_jpeg_ctx *ctx)
अणु
	स्थिर काष्ठा v4l2_event ev = अणु
			.type = V4L2_EVENT_SOURCE_CHANGE,
			.u.src_change.changes =
			V4L2_EVENT_SRC_CH_RESOLUTION,
		पूर्ण;

	dev_dbg(ctx->mxc_jpeg->dev, "Notify app event SRC_CH_RESOLUTION");
	v4l2_event_queue_fh(&ctx->fh, &ev);
पूर्ण

अटल पूर्णांक mxc_get_मुक्त_slot(काष्ठा mxc_jpeg_slot_data slot_data[], पूर्णांक n)
अणु
	पूर्णांक मुक्त_slot = 0;

	जबतक (slot_data[मुक्त_slot].used && मुक्त_slot < n)
		मुक्त_slot++;

	वापस मुक्त_slot; /* >=n when there are no more मुक्त slots */
पूर्ण

अटल bool mxc_jpeg_alloc_slot_data(काष्ठा mxc_jpeg_dev *jpeg,
				     अचिन्हित पूर्णांक slot)
अणु
	काष्ठा mxc_jpeg_desc *desc;
	काष्ठा mxc_jpeg_desc *cfg_desc;
	व्योम *cfg_sपंचांग;

	अगर (jpeg->slot_data[slot].desc)
		जाओ skip_alloc; /* alपढ़ोy allocated, reuse it */

	/* allocate descriptor क्रम decoding/encoding phase */
	desc = dma_alloc_coherent(jpeg->dev,
				  माप(काष्ठा mxc_jpeg_desc),
				  &jpeg->slot_data[slot].desc_handle,
				  GFP_ATOMIC);
	अगर (!desc)
		जाओ err;
	jpeg->slot_data[slot].desc = desc;

	/* allocate descriptor क्रम configuration phase (encoder only) */
	cfg_desc = dma_alloc_coherent(jpeg->dev,
				      माप(काष्ठा mxc_jpeg_desc),
				      &jpeg->slot_data[slot].cfg_desc_handle,
				      GFP_ATOMIC);
	अगर (!cfg_desc)
		जाओ err;
	jpeg->slot_data[slot].cfg_desc = cfg_desc;

	/* allocate configuration stream */
	cfg_sपंचांग = dma_alloc_coherent(jpeg->dev,
				     MXC_JPEG_MAX_CFG_STREAM,
				     &jpeg->slot_data[slot].cfg_stream_handle,
				     GFP_ATOMIC);
	अगर (!cfg_sपंचांग)
		जाओ err;
	jpeg->slot_data[slot].cfg_stream_vaddr = cfg_sपंचांग;

skip_alloc:
	jpeg->slot_data[slot].used = true;

	वापस true;
err:
	dev_err(jpeg->dev, "Could not allocate descriptors for slot %d", slot);

	वापस false;
पूर्ण

अटल व्योम mxc_jpeg_मुक्त_slot_data(काष्ठा mxc_jpeg_dev *jpeg,
				    अचिन्हित पूर्णांक slot)
अणु
	अगर (slot >= MXC_MAX_SLOTS) अणु
		dev_err(jpeg->dev, "Invalid slot %d, nothing to free.", slot);
		वापस;
	पूर्ण

	/* मुक्त descriptor क्रम decoding/encoding phase */
	dma_मुक्त_coherent(jpeg->dev, माप(काष्ठा mxc_jpeg_desc),
			  jpeg->slot_data[slot].desc,
			  jpeg->slot_data[slot].desc_handle);

	/* मुक्त descriptor क्रम encoder configuration phase / decoder DHT */
	dma_मुक्त_coherent(jpeg->dev, माप(काष्ठा mxc_jpeg_desc),
			  jpeg->slot_data[slot].cfg_desc,
			  jpeg->slot_data[slot].cfg_desc_handle);

	/* मुक्त configuration stream */
	dma_मुक्त_coherent(jpeg->dev, MXC_JPEG_MAX_CFG_STREAM,
			  jpeg->slot_data[slot].cfg_stream_vaddr,
			  jpeg->slot_data[slot].cfg_stream_handle);

	jpeg->slot_data[slot].used = false;
पूर्ण

अटल irqवापस_t mxc_jpeg_dec_irq(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mxc_jpeg_dev *jpeg = priv;
	काष्ठा mxc_jpeg_ctx *ctx;
	व्योम __iomem *reg = jpeg->base_reg;
	काष्ठा device *dev = jpeg->dev;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा mxc_jpeg_src_buf *jpeg_src_buf;
	क्रमागत vb2_buffer_state buf_state;
	u32 dec_ret, com_status;
	अचिन्हित दीर्घ payload;
	काष्ठा mxc_jpeg_q_data *q_data;
	क्रमागत v4l2_buf_type cap_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	अचिन्हित पूर्णांक slot;

	spin_lock(&jpeg->hw_lock);

	com_status = पढ़ोl(reg + COM_STATUS);
	slot = COM_STATUS_CUR_SLOT(com_status);
	dev_dbg(dev, "Irq %d on slot %d.\n", irq, slot);

	ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);
	अगर (!ctx) अणु
		dev_err(dev,
			"Instance released before the end of transaction.\n");
		/* soft reset only resets पूर्णांकernal state, not रेजिस्टरs */
		mxc_jpeg_sw_reset(reg);
		/* clear all पूर्णांकerrupts */
		ग_लिखोl(0xFFFFFFFF, reg + MXC_SLOT_OFFSET(slot, SLOT_STATUS));
		जाओ job_unlock;
	पूर्ण

	अगर (slot != ctx->slot) अणु
		/* TODO investigate when adding multi-instance support */
		dev_warn(dev, "IRQ slot %d != context slot %d.\n",
			 slot, ctx->slot);
		जाओ job_unlock;
	पूर्ण

	dec_ret = पढ़ोl(reg + MXC_SLOT_OFFSET(slot, SLOT_STATUS));
	ग_लिखोl(dec_ret, reg + MXC_SLOT_OFFSET(slot, SLOT_STATUS)); /* w1c */

	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	jpeg_src_buf = vb2_to_mxc_buf(&src_buf->vb2_buf);

	अगर (dec_ret & SLOT_STATUS_ENC_CONFIG_ERR) अणु
		u32 ret = पढ़ोl(reg + CAST_STATUS12);

		dev_err(dev, "Encoder/decoder error, status=0x%08x", ret);
		mxc_jpeg_sw_reset(reg);
		buf_state = VB2_BUF_STATE_ERROR;
		जाओ buffers_करोne;
	पूर्ण

	अगर (!(dec_ret & SLOT_STATUS_FRMDONE))
		जाओ job_unlock;

	अगर (jpeg->mode == MXC_JPEG_ENCODE &&
	    ctx->enc_state == MXC_JPEG_ENC_CONF) अणु
		ctx->enc_state = MXC_JPEG_ENCODING;
		dev_dbg(dev, "Encoder config finished. Start encoding...\n");
		mxc_jpeg_enc_mode_go(dev, reg);
		जाओ job_unlock;
	पूर्ण
	अगर (jpeg->mode == MXC_JPEG_DECODE && jpeg_src_buf->dht_needed) अणु
		jpeg_src_buf->dht_needed = false;
		dev_dbg(dev, "Decoder DHT cfg finished. Start decoding...\n");
		जाओ job_unlock;
	पूर्ण
	अगर (jpeg->mode == MXC_JPEG_ENCODE) अणु
		payload = पढ़ोl(reg + MXC_SLOT_OFFSET(slot, SLOT_BUF_PTR));
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, payload);
		dev_dbg(dev, "Encoding finished, payload size: %ld\n",
			payload);
	पूर्ण अन्यथा अणु
		q_data = mxc_jpeg_get_q_data(ctx, cap_type);
		payload = q_data->sizeimage[0];
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, payload);
		vb2_set_plane_payload(&dst_buf->vb2_buf, 1, 0);
		अगर (q_data->fmt->colplanes == 2) अणु
			payload = q_data->sizeimage[1];
			vb2_set_plane_payload(&dst_buf->vb2_buf, 1, payload);
		पूर्ण
		dev_dbg(dev, "Decoding finished, payload size: %ld + %ld\n",
			vb2_get_plane_payload(&dst_buf->vb2_buf, 0),
			vb2_get_plane_payload(&dst_buf->vb2_buf, 1));
	पूर्ण

	/* लघु preview of the results */
	dev_dbg(dev, "src_buf preview: ");
	prपूर्णांक_mxc_buf(jpeg, &src_buf->vb2_buf, 32);
	dev_dbg(dev, "dst_buf preview: ");
	prपूर्णांक_mxc_buf(jpeg, &dst_buf->vb2_buf, 32);
	buf_state = VB2_BUF_STATE_DONE;

buffers_करोne:
	jpeg->slot_data[slot].used = false; /* unused, but करोn't मुक्त */
	v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_करोne(src_buf, buf_state);
	v4l2_m2m_buf_करोne(dst_buf, buf_state);
	spin_unlock(&jpeg->hw_lock);
	v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
	वापस IRQ_HANDLED;
job_unlock:
	spin_unlock(&jpeg->hw_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxc_jpeg_fixup_sof(काष्ठा mxc_jpeg_sof *sof,
			      u32 fourcc,
			      u16 w, u16 h)
अणु
	पूर्णांक sof_length;

	sof->precision = 8; /* TODO allow 8/12 bit precision*/
	sof->height = h;
	_bswap16(&sof->height);
	sof->width = w;
	_bswap16(&sof->width);

	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_NV12:
		sof->components_no = 3;
		sof->comp[0].v = 0x2;
		sof->comp[0].h = 0x2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		sof->components_no = 3;
		sof->comp[0].v = 0x1;
		sof->comp[0].h = 0x2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV24:
	हाल V4L2_PIX_FMT_RGB24:
	शेष:
		sof->components_no = 3;
		अवरोध;
	हाल V4L2_PIX_FMT_ARGB32:
		sof->components_no = 4;
		अवरोध;
	हाल V4L2_PIX_FMT_GREY:
		sof->components_no = 1;
		अवरोध;
	पूर्ण
	sof_length = 8 + 3 * sof->components_no;
	sof->length = sof_length;
	_bswap16(&sof->length);

	वापस sof_length; /* not swaped */
पूर्ण

अटल पूर्णांक mxc_jpeg_fixup_sos(काष्ठा mxc_jpeg_sos *sos,
			      u32 fourcc)
अणु
	पूर्णांक sos_length;
	u8 *sof_u8 = (u8 *)sos;

	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_NV12:
		sos->components_no = 3;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		sos->components_no = 3;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV24:
	हाल V4L2_PIX_FMT_RGB24:
	शेष:
		sos->components_no = 3;
		अवरोध;
	हाल V4L2_PIX_FMT_ARGB32:
		sos->components_no = 4;
		अवरोध;
	हाल V4L2_PIX_FMT_GREY:
		sos->components_no = 1;
		अवरोध;
	पूर्ण
	sos_length = 6 + 2 * sos->components_no;
	sos->length = sos_length;
	_bswap16(&sos->length);

	/* SOS ignorable bytes, not so ignorable after all */
	sof_u8[sos_length - 1] = 0x0;
	sof_u8[sos_length - 2] = 0x3f;
	sof_u8[sos_length - 3] = 0x0;

	वापस sos_length; /* not swaped */
पूर्ण

अटल अचिन्हित पूर्णांक mxc_jpeg_setup_cfg_stream(व्योम *cfg_stream_vaddr,
					      u32 fourcc,
					      u16 w, u16 h)
अणु
	अचिन्हित पूर्णांक offset = 0;
	u8 *cfg = (u8 *)cfg_stream_vaddr;
	काष्ठा mxc_jpeg_sof *sof;
	काष्ठा mxc_jpeg_sos *sos;

	स_नकल(cfg + offset, jpeg_soi, ARRAY_SIZE(jpeg_soi));
	offset += ARRAY_SIZE(jpeg_soi);

	अगर (fourcc == V4L2_PIX_FMT_RGB24 ||
	    fourcc == V4L2_PIX_FMT_ARGB32) अणु
		स_नकल(cfg + offset, jpeg_app14, माप(jpeg_app14));
		offset += माप(jpeg_app14);
	पूर्ण अन्यथा अणु
		स_नकल(cfg + offset, jpeg_app0, माप(jpeg_app0));
		offset += माप(jpeg_app0);
	पूर्ण

	स_नकल(cfg + offset, jpeg_dqt, माप(jpeg_dqt));
	offset += माप(jpeg_dqt);

	स_नकल(cfg + offset, jpeg_sof_maximal, माप(jpeg_sof_maximal));
	offset += 2; /* skip marker ID */
	sof = (काष्ठा mxc_jpeg_sof *)(cfg + offset);
	offset += mxc_jpeg_fixup_sof(sof, fourcc, w, h);

	स_नकल(cfg + offset, jpeg_dht, माप(jpeg_dht));
	offset += माप(jpeg_dht);

	स_नकल(cfg + offset, jpeg_dri, माप(jpeg_dri));
	offset += माप(jpeg_dri);

	स_नकल(cfg + offset, jpeg_sos_maximal, माप(jpeg_sos_maximal));
	offset += 2; /* skip marker ID */
	sos = (काष्ठा mxc_jpeg_sos *)(cfg + offset);
	offset += mxc_jpeg_fixup_sos(sos, fourcc);

	स_नकल(cfg + offset, jpeg_eoi, माप(jpeg_eoi));
	offset += माप(jpeg_eoi);

	वापस offset;
पूर्ण

अटल व्योम mxc_jpeg_config_dec_desc(काष्ठा vb2_buffer *out_buf,
				     काष्ठा mxc_jpeg_ctx *ctx,
				     काष्ठा vb2_buffer *src_buf,
				     काष्ठा vb2_buffer *dst_buf)
अणु
	क्रमागत v4l2_buf_type cap_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	काष्ठा mxc_jpeg_q_data *q_data_cap;
	क्रमागत mxc_jpeg_image_क्रमmat img_fmt;
	काष्ठा mxc_jpeg_dev *jpeg = ctx->mxc_jpeg;
	व्योम __iomem *reg = jpeg->base_reg;
	अचिन्हित पूर्णांक slot = ctx->slot;
	काष्ठा mxc_jpeg_desc *desc = jpeg->slot_data[slot].desc;
	काष्ठा mxc_jpeg_desc *cfg_desc = jpeg->slot_data[slot].cfg_desc;
	dma_addr_t desc_handle = jpeg->slot_data[slot].desc_handle;
	dma_addr_t cfg_desc_handle = jpeg->slot_data[slot].cfg_desc_handle;
	dma_addr_t cfg_stream_handle = jpeg->slot_data[slot].cfg_stream_handle;
	अचिन्हित पूर्णांक *cfg_size = &jpeg->slot_data[slot].cfg_stream_size;
	व्योम *cfg_stream_vaddr = jpeg->slot_data[slot].cfg_stream_vaddr;
	काष्ठा mxc_jpeg_src_buf *jpeg_src_buf;

	jpeg_src_buf = vb2_to_mxc_buf(src_buf);

	/* setup the decoding descriptor */
	desc->next_descpt_ptr = 0; /* end of chain */
	q_data_cap = mxc_jpeg_get_q_data(ctx, cap_type);
	desc->imgsize = q_data_cap->w_adjusted << 16 | q_data_cap->h_adjusted;
	img_fmt = mxc_jpeg_fourcc_to_imgfmt(q_data_cap->fmt->fourcc);
	desc->sपंचांग_ctrl &= ~STM_CTRL_IMAGE_FORMAT(0xF); /* clear image क्रमmat */
	desc->sपंचांग_ctrl |= STM_CTRL_IMAGE_FORMAT(img_fmt);
	desc->line_pitch = q_data_cap->bytesperline[0];
	mxc_jpeg_addrs(desc, dst_buf, src_buf, 0);
	mxc_jpeg_set_bufsize(desc, ALIGN(vb2_plane_size(src_buf, 0), 1024));
	prपूर्णांक_descriptor_info(jpeg->dev, desc);

	अगर (!jpeg_src_buf->dht_needed) अणु
		/* validate the decoding descriptor */
		mxc_jpeg_set_desc(desc_handle, reg, slot);
		वापस;
	पूर्ण

	/*
	 * अगर a शेष huffman table is needed, use the config descriptor to
	 * inject a DHT, by chaining it beक्रमe the decoding descriptor
	 */
	*cfg_size = mxc_jpeg_setup_cfg_stream(cfg_stream_vaddr,
					      V4L2_PIX_FMT_YUYV,
					      MXC_JPEG_MIN_WIDTH,
					      MXC_JPEG_MIN_HEIGHT);
	cfg_desc->next_descpt_ptr = desc_handle | MXC_NXT_DESCPT_EN;
	cfg_desc->buf_base0 = vb2_dma_contig_plane_dma_addr(dst_buf, 0);
	cfg_desc->buf_base1 = 0;
	cfg_desc->imgsize = MXC_JPEG_MIN_WIDTH << 16;
	cfg_desc->imgsize |= MXC_JPEG_MIN_HEIGHT;
	cfg_desc->line_pitch = MXC_JPEG_MIN_WIDTH * 2;
	cfg_desc->sपंचांग_ctrl = STM_CTRL_IMAGE_FORMAT(MXC_JPEG_YUV422);
	cfg_desc->sपंचांग_bufbase = cfg_stream_handle;
	cfg_desc->sपंचांग_bufsize = ALIGN(*cfg_size, 1024);
	prपूर्णांक_descriptor_info(jpeg->dev, cfg_desc);

	/* validate the configuration descriptor */
	mxc_jpeg_set_desc(cfg_desc_handle, reg, slot);
पूर्ण

अटल व्योम mxc_jpeg_config_enc_desc(काष्ठा vb2_buffer *out_buf,
				     काष्ठा mxc_jpeg_ctx *ctx,
				     काष्ठा vb2_buffer *src_buf,
				     काष्ठा vb2_buffer *dst_buf)
अणु
	काष्ठा mxc_jpeg_dev *jpeg = ctx->mxc_jpeg;
	व्योम __iomem *reg = jpeg->base_reg;
	अचिन्हित पूर्णांक slot = ctx->slot;
	काष्ठा mxc_jpeg_desc *desc = jpeg->slot_data[slot].desc;
	काष्ठा mxc_jpeg_desc *cfg_desc = jpeg->slot_data[slot].cfg_desc;
	dma_addr_t desc_handle = jpeg->slot_data[slot].desc_handle;
	dma_addr_t cfg_desc_handle = jpeg->slot_data[slot].cfg_desc_handle;
	व्योम *cfg_stream_vaddr = jpeg->slot_data[slot].cfg_stream_vaddr;
	काष्ठा mxc_jpeg_q_data *q_data;
	क्रमागत mxc_jpeg_image_क्रमmat img_fmt;
	पूर्णांक w, h;

	q_data = mxc_jpeg_get_q_data(ctx, src_buf->vb2_queue->type);

	jpeg->slot_data[slot].cfg_stream_size =
			mxc_jpeg_setup_cfg_stream(cfg_stream_vaddr,
						  q_data->fmt->fourcc,
						  q_data->w_adjusted,
						  q_data->h_adjusted);

	/* chain the config descriptor with the encoding descriptor */
	cfg_desc->next_descpt_ptr = desc_handle | MXC_NXT_DESCPT_EN;

	cfg_desc->buf_base0 = jpeg->slot_data[slot].cfg_stream_handle;
	cfg_desc->buf_base1 = 0;
	cfg_desc->line_pitch = 0;
	cfg_desc->sपंचांग_bufbase = 0; /* no output expected */
	cfg_desc->sपंचांग_bufsize = 0x0;
	cfg_desc->imgsize = 0;
	cfg_desc->sपंचांग_ctrl = STM_CTRL_CONFIG_MOD(1);

	desc->next_descpt_ptr = 0; /* end of chain */

	/* use adjusted resolution क्रम CAST IP job */
	w = q_data->w_adjusted;
	h = q_data->h_adjusted;
	mxc_jpeg_set_res(desc, w, h);
	mxc_jpeg_set_line_pitch(desc, w * (q_data->fmt->depth / 8));
	mxc_jpeg_set_bufsize(desc, desc->line_pitch * h);
	img_fmt = mxc_jpeg_fourcc_to_imgfmt(q_data->fmt->fourcc);
	अगर (img_fmt == MXC_JPEG_INVALID)
		dev_err(jpeg->dev, "No valid image format detected\n");
	desc->sपंचांग_ctrl = STM_CTRL_CONFIG_MOD(0) |
			 STM_CTRL_IMAGE_FORMAT(img_fmt);
	mxc_jpeg_addrs(desc, src_buf, dst_buf, 0);
	dev_dbg(jpeg->dev, "cfg_desc:\n");
	prपूर्णांक_descriptor_info(jpeg->dev, cfg_desc);
	dev_dbg(jpeg->dev, "enc desc:\n");
	prपूर्णांक_descriptor_info(jpeg->dev, desc);
	prपूर्णांक_wrapper_info(jpeg->dev, reg);
	prपूर्णांक_cast_status(jpeg->dev, reg, MXC_JPEG_ENCODE);

	/* validate the configuration descriptor */
	mxc_jpeg_set_desc(cfg_desc_handle, reg, slot);
पूर्ण

अटल व्योम mxc_jpeg_device_run(व्योम *priv)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = priv;
	काष्ठा mxc_jpeg_dev *jpeg = ctx->mxc_jpeg;
	व्योम __iomem *reg = jpeg->base_reg;
	काष्ठा device *dev = jpeg->dev;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	अचिन्हित दीर्घ flags;
	काष्ठा mxc_jpeg_q_data *q_data_cap, *q_data_out;
	काष्ठा mxc_jpeg_src_buf *jpeg_src_buf;

	spin_lock_irqsave(&ctx->mxc_jpeg->hw_lock, flags);
	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	अगर (!src_buf || !dst_buf) अणु
		dev_err(dev, "Null src or dst buf\n");
		जाओ end;
	पूर्ण

	q_data_cap = mxc_jpeg_get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (!q_data_cap)
		जाओ end;
	q_data_out = mxc_jpeg_get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	अगर (!q_data_out)
		जाओ end;
	src_buf->sequence = q_data_out->sequence++;
	dst_buf->sequence = q_data_cap->sequence++;

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, true);

	jpeg_src_buf = vb2_to_mxc_buf(&src_buf->vb2_buf);
	अगर (jpeg_src_buf->jpeg_parse_error) अणु
		jpeg->slot_data[ctx->slot].used = false;
		v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&ctx->mxc_jpeg->hw_lock, flags);
		v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);

		वापस;
	पूर्ण

	/*
	 * TODO: this reset should be हटाओd, once we figure out
	 * how to overcome hardware issues both on encoder and decoder
	 */
	mxc_jpeg_sw_reset(reg);
	mxc_jpeg_enable(reg);
	mxc_jpeg_set_l_endian(reg, 1);

	ctx->slot = mxc_get_मुक्त_slot(jpeg->slot_data, MXC_MAX_SLOTS);
	अगर (ctx->slot >= MXC_MAX_SLOTS) अणु
		dev_err(dev, "No more free slots\n");
		जाओ end;
	पूर्ण
	अगर (!mxc_jpeg_alloc_slot_data(jpeg, ctx->slot)) अणु
		dev_err(dev, "Cannot allocate slot data\n");
		जाओ end;
	पूर्ण

	mxc_jpeg_enable_slot(reg, ctx->slot);
	mxc_jpeg_enable_irq(reg, ctx->slot);

	अगर (jpeg->mode == MXC_JPEG_ENCODE) अणु
		dev_dbg(dev, "Encoding on slot %d\n", ctx->slot);
		ctx->enc_state = MXC_JPEG_ENC_CONF;
		mxc_jpeg_config_enc_desc(&dst_buf->vb2_buf, ctx,
					 &src_buf->vb2_buf, &dst_buf->vb2_buf);
		mxc_jpeg_enc_mode_conf(dev, reg); /* start config phase */
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Decoding on slot %d\n", ctx->slot);
		prपूर्णांक_mxc_buf(jpeg, &src_buf->vb2_buf, 0);
		mxc_jpeg_config_dec_desc(&dst_buf->vb2_buf, ctx,
					 &src_buf->vb2_buf, &dst_buf->vb2_buf);
		mxc_jpeg_dec_mode_go(dev, reg);
	पूर्ण
end:
	spin_unlock_irqrestore(&ctx->mxc_jpeg->hw_lock, flags);
पूर्ण

अटल पूर्णांक mxc_jpeg_decoder_cmd(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_decoder_cmd *cmd)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(fh);
	काष्ठा device *dev = ctx->mxc_jpeg->dev;
	पूर्णांक ret;

	ret = v4l2_m2m_ioctl_try_decoder_cmd(file, fh, cmd);
	अगर (ret < 0)
		वापस ret;

	अगर (cmd->cmd == V4L2_DEC_CMD_STOP) अणु
		dev_dbg(dev, "Received V4L2_DEC_CMD_STOP");
		अगर (v4l2_m2m_num_src_bufs_पढ़ोy(fh->m2m_ctx) == 0) अणु
			/* No more src bufs, notअगरy app EOS */
			notअगरy_eos(ctx);
		पूर्ण अन्यथा अणु
			/* will send EOS later*/
			ctx->stopping = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_encoder_cmd(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_encoder_cmd *cmd)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(fh);
	काष्ठा device *dev = ctx->mxc_jpeg->dev;
	पूर्णांक ret;

	ret = v4l2_m2m_ioctl_try_encoder_cmd(file, fh, cmd);
	अगर (ret < 0)
		वापस ret;

	अगर (cmd->cmd == V4L2_ENC_CMD_STOP) अणु
		dev_dbg(dev, "Received V4L2_ENC_CMD_STOP");
		अगर (v4l2_m2m_num_src_bufs_पढ़ोy(fh->m2m_ctx) == 0) अणु
			/* No more src bufs, notअगरy app EOS */
			notअगरy_eos(ctx);
		पूर्ण अन्यथा अणु
			/* will send EOS later*/
			ctx->stopping = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_queue_setup(काष्ठा vb2_queue *q,
				अचिन्हित पूर्णांक *nbuffers,
				अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_ctxs[])
अणु
	काष्ठा mxc_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा mxc_jpeg_q_data *q_data = शून्य;
	पूर्णांक i;

	q_data = mxc_jpeg_get_q_data(ctx, q->type);
	अगर (!q_data)
		वापस -EINVAL;

	/* Handle CREATE_BUFS situation - *nplanes != 0 */
	अगर (*nplanes) अणु
		क्रम (i = 0; i < *nplanes; i++) अणु
			अगर (sizes[i] < q_data->sizeimage[i])
				वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Handle REQBUFS situation */
	*nplanes = q_data->fmt->colplanes;
	क्रम (i = 0; i < *nplanes; i++)
		sizes[i] = q_data->sizeimage[i];

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा mxc_jpeg_q_data *q_data = mxc_jpeg_get_q_data(ctx, q->type);

	dev_dbg(ctx->mxc_jpeg->dev, "Start streaming ctx=%p", ctx);
	q_data->sequence = 0;

	वापस 0;
पूर्ण

अटल व्योम mxc_jpeg_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;

	dev_dbg(ctx->mxc_jpeg->dev, "Stop streaming ctx=%p", ctx);

	/* Release all active buffers */
	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (!vbuf)
			वापस;
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल पूर्णांक mxc_jpeg_valid_comp_id(काष्ठा device *dev,
				  काष्ठा mxc_jpeg_sof *sof,
				  काष्ठा mxc_jpeg_sos *sos)
अणु
	पूर्णांक valid = 1;
	पूर्णांक i;

	/*
	 * there's a limitation in the IP that the component IDs must be
	 * between 0..4, अगर they are not, let's patch them
	 */
	क्रम (i = 0; i < sof->components_no; i++)
		अगर (sof->comp[i].id > MXC_JPEG_MAX_COMPONENTS) अणु
			valid = 0;
			dev_err(dev, "Component %d has invalid ID: %d",
				i, sof->comp[i].id);
		पूर्ण
	अगर (!valid)
		/* patch all comp IDs अगर at least one is invalid */
		क्रम (i = 0; i < sof->components_no; i++) अणु
			dev_warn(dev, "Component %d ID patched to: %d",
				 i, i + 1);
			sof->comp[i].id = i + 1;
			sos->comp[i].id = i + 1;
		पूर्ण

	वापस valid;
पूर्ण

अटल u32 mxc_jpeg_get_image_क्रमmat(काष्ठा device *dev,
				     स्थिर काष्ठा v4l2_jpeg_header *header)
अणु
	पूर्णांक i;
	u32 fourcc = 0;

	क्रम (i = 0; i < MXC_JPEG_NUM_FORMATS; i++)
		अगर (mxc_क्रमmats[i].subsampling == header->frame.subsampling &&
		    mxc_क्रमmats[i].nc == header->frame.num_components) अणु
			fourcc = mxc_क्रमmats[i].fourcc;
			अवरोध;
		पूर्ण
	अगर (fourcc == 0) अणु
		dev_err(dev, "Could not identify image format nc=%d, subsampling=%d\n",
			header->frame.num_components,
			header->frame.subsampling);
		वापस fourcc;
	पूर्ण
	/*
	 * If the transक्रमm flag from APP14 marker is 0, images that are
	 * encoded with 3 components have RGB colorspace, see Recommendation
	 * ITU-T T.872 chapter 6.5.3 APP14 marker segment क्रम colour encoding
	 */
	अगर (fourcc == V4L2_PIX_FMT_YUV24 || fourcc == V4L2_PIX_FMT_RGB24) अणु
		अगर (header->app14_tf == V4L2_JPEG_APP14_TF_CMYK_RGB)
			fourcc = V4L2_PIX_FMT_RGB24;
		अन्यथा
			fourcc = V4L2_PIX_FMT_YUV24;
	पूर्ण

	वापस fourcc;
पूर्ण

अटल व्योम mxc_jpeg_bytesperline(काष्ठा mxc_jpeg_q_data *q,
				  u32 precision)
अणु
	/* Bytes distance between the lefपंचांगost pixels in two adjacent lines */
	अगर (q->fmt->fourcc == V4L2_PIX_FMT_JPEG) अणु
		/* bytesperline unused क्रम compressed क्रमmats */
		q->bytesperline[0] = 0;
		q->bytesperline[1] = 0;
	पूर्ण अन्यथा अगर (q->fmt->fourcc == V4L2_PIX_FMT_NV12) अणु
		/* When the image क्रमmat is planar the bytesperline value
		 * applies to the first plane and is भागided by the same factor
		 * as the width field क्रम the other planes
		 */
		q->bytesperline[0] = q->w * (precision / 8) *
				     (q->fmt->depth / 8);
		q->bytesperline[1] = q->bytesperline[0];
	पूर्ण अन्यथा अणु
		/* single plane क्रमmats */
		q->bytesperline[0] = q->w * (precision / 8) *
				     (q->fmt->depth / 8);
		q->bytesperline[1] = 0;
	पूर्ण
पूर्ण

अटल व्योम mxc_jpeg_sizeimage(काष्ठा mxc_jpeg_q_data *q)
अणु
	अगर (q->fmt->fourcc == V4L2_PIX_FMT_JPEG) अणु
		/* अगर no sizeimage from user, assume worst jpeg compression */
		अगर (!q->sizeimage[0])
			q->sizeimage[0] = 6 * q->w * q->h;
		q->sizeimage[1] = 0;

		अगर (q->sizeimage[0] > MXC_JPEG_MAX_SIZEIMAGE)
			q->sizeimage[0] = MXC_JPEG_MAX_SIZEIMAGE;

		/* jpeg stream size must be multiple of 1K */
		q->sizeimage[0] = ALIGN(q->sizeimage[0], 1024);
	पूर्ण अन्यथा अणु
		q->sizeimage[0] = q->bytesperline[0] * q->h;
		q->sizeimage[1] = 0;
		अगर (q->fmt->fourcc == V4L2_PIX_FMT_NV12)
			q->sizeimage[1] = q->sizeimage[0] / 2;
	पूर्ण
पूर्ण

अटल पूर्णांक mxc_jpeg_parse(काष्ठा mxc_jpeg_ctx *ctx,
			  u8 *src_addr, u32 size, bool *dht_needed)
अणु
	काष्ठा device *dev = ctx->mxc_jpeg->dev;
	काष्ठा mxc_jpeg_q_data *q_data_out, *q_data_cap;
	क्रमागत v4l2_buf_type cap_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	bool src_chg = false;
	u32 fourcc;
	काष्ठा v4l2_jpeg_header header;
	काष्ठा mxc_jpeg_sof *psof = शून्य;
	काष्ठा mxc_jpeg_sos *psos = शून्य;
	पूर्णांक ret;

	स_रखो(&header, 0, माप(header));
	ret = v4l2_jpeg_parse_header((व्योम *)src_addr, size, &header);
	अगर (ret < 0) अणु
		dev_err(dev, "Error parsing JPEG stream markers\n");
		वापस ret;
	पूर्ण

	/* अगर DHT marker present, no need to inject शेष one */
	*dht_needed = (header.num_dht == 0);

	q_data_out = mxc_jpeg_get_q_data(ctx,
					 V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	अगर (q_data_out->w == 0 && q_data_out->h == 0) अणु
		dev_warn(dev, "Invalid user resolution 0x0");
		dev_warn(dev, "Keeping resolution from JPEG: %dx%d",
			 header.frame.width, header.frame.height);
		q_data_out->w = header.frame.width;
		q_data_out->h = header.frame.height;
	पूर्ण अन्यथा अगर (header.frame.width != q_data_out->w ||
		   header.frame.height != q_data_out->h) अणु
		dev_err(dev,
			"Resolution mismatch: %dx%d (JPEG) versus %dx%d(user)",
			header.frame.width, header.frame.height,
			q_data_out->w, q_data_out->h);
		वापस -EINVAL;
	पूर्ण
	अगर (header.frame.width % 8 != 0 || header.frame.height % 8 != 0) अणु
		dev_err(dev, "JPEG width or height not multiple of 8: %dx%d\n",
			header.frame.width, header.frame.height);
		वापस -EINVAL;
	पूर्ण
	अगर (header.frame.width > MXC_JPEG_MAX_WIDTH ||
	    header.frame.height > MXC_JPEG_MAX_HEIGHT) अणु
		dev_err(dev, "JPEG width or height should be <= 8192: %dx%d\n",
			header.frame.width, header.frame.height);
		वापस -EINVAL;
	पूर्ण
	अगर (header.frame.width < MXC_JPEG_MIN_WIDTH ||
	    header.frame.height < MXC_JPEG_MIN_HEIGHT) अणु
		dev_err(dev, "JPEG width or height should be > 64: %dx%d\n",
			header.frame.width, header.frame.height);
		वापस -EINVAL;
	पूर्ण
	अगर (header.frame.num_components > V4L2_JPEG_MAX_COMPONENTS) अणु
		dev_err(dev, "JPEG number of components should be <=%d",
			V4L2_JPEG_MAX_COMPONENTS);
		वापस -EINVAL;
	पूर्ण
	/* check and, अगर necessary, patch component IDs*/
	psof = (काष्ठा mxc_jpeg_sof *)header.sof.start;
	psos = (काष्ठा mxc_jpeg_sos *)header.sos.start;
	अगर (!mxc_jpeg_valid_comp_id(dev, psof, psos))
		dev_warn(dev, "JPEG component ids should be 0-3 or 1-4");

	fourcc = mxc_jpeg_get_image_क्रमmat(dev, &header);
	अगर (fourcc == 0)
		वापस -EINVAL;

	/*
	 * set-up the capture queue with the pixelक्रमmat and resolution
	 * detected from the jpeg output stream
	 */
	q_data_cap = mxc_jpeg_get_q_data(ctx, cap_type);
	अगर (q_data_cap->w != header.frame.width ||
	    q_data_cap->h != header.frame.height)
		src_chg = true;
	q_data_cap->w = header.frame.width;
	q_data_cap->h = header.frame.height;
	q_data_cap->fmt = mxc_jpeg_find_क्रमmat(ctx, fourcc);
	q_data_cap->w_adjusted = q_data_cap->w;
	q_data_cap->h_adjusted = q_data_cap->h;
	/*
	 * align up the resolution क्रम CAST IP,
	 * but leave the buffer resolution unchanged
	 */
	v4l_bound_align_image(&q_data_cap->w_adjusted,
			      q_data_cap->w_adjusted,  /* adjust up */
			      MXC_JPEG_MAX_WIDTH,
			      q_data_cap->fmt->h_align,
			      &q_data_cap->h_adjusted,
			      q_data_cap->h_adjusted, /* adjust up */
			      MXC_JPEG_MAX_HEIGHT,
			      q_data_cap->fmt->v_align,
			      0);
	dev_dbg(dev, "Detected jpeg res=(%dx%d)->(%dx%d), pixfmt=%c%c%c%c\n",
		q_data_cap->w, q_data_cap->h,
		q_data_cap->w_adjusted, q_data_cap->h_adjusted,
		(fourcc & 0xff),
		(fourcc >>  8) & 0xff,
		(fourcc >> 16) & 0xff,
		(fourcc >> 24) & 0xff);

	/* setup bytesperline/sizeimage क्रम capture queue */
	mxc_jpeg_bytesperline(q_data_cap, header.frame.precision);
	mxc_jpeg_sizeimage(q_data_cap);

	/*
	 * अगर the CAPTURE क्रमmat was updated with new values, regardless of
	 * whether they match the values set by the client or not, संकेत
	 * a source change event
	 */
	अगर (src_chg)
		notअगरy_src_chg(ctx);

	वापस 0;
पूर्ण

अटल व्योम mxc_jpeg_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	पूर्णांक ret;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा mxc_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mxc_jpeg_src_buf *jpeg_src_buf;

	अगर (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		जाओ end;

	/* क्रम V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE */
	अगर (ctx->mxc_jpeg->mode != MXC_JPEG_DECODE)
		जाओ end;

	jpeg_src_buf = vb2_to_mxc_buf(vb);
	jpeg_src_buf->jpeg_parse_error = false;
	ret = mxc_jpeg_parse(ctx,
			     (u8 *)vb2_plane_vaddr(vb, 0),
			     vb2_get_plane_payload(vb, 0),
			     &jpeg_src_buf->dht_needed);
	अगर (ret)
		jpeg_src_buf->jpeg_parse_error = true;

end:
	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक mxc_jpeg_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा mxc_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mxc_jpeg_q_data *q_data = शून्य;
	काष्ठा device *dev = ctx->mxc_jpeg->dev;
	अचिन्हित दीर्घ sizeimage;
	पूर्णांक i;

	vbuf->field = V4L2_FIELD_NONE;

	q_data = mxc_jpeg_get_q_data(ctx, vb->vb2_queue->type);
	अगर (!q_data)
		वापस -EINVAL;
	क्रम (i = 0; i < q_data->fmt->colplanes; i++) अणु
		sizeimage = q_data->sizeimage[i];
		अगर (vb2_plane_size(vb, i) < sizeimage) अणु
			dev_err(dev, "plane %d too small (%lu < %lu)",
				i, vb2_plane_size(vb, i), sizeimage);
			वापस -EINVAL;
		पूर्ण
		vb2_set_plane_payload(vb, i, sizeimage);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_ops mxc_jpeg_qops = अणु
	.queue_setup		= mxc_jpeg_queue_setup,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.buf_out_validate	= mxc_jpeg_buf_out_validate,
	.buf_prepare		= mxc_jpeg_buf_prepare,
	.start_streaming	= mxc_jpeg_start_streaming,
	.stop_streaming		= mxc_jpeg_stop_streaming,
	.buf_queue		= mxc_jpeg_buf_queue,
पूर्ण;

अटल पूर्णांक mxc_jpeg_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			       काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा mxc_jpeg_src_buf);
	src_vq->ops = &mxc_jpeg_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->mxc_jpeg->lock;
	src_vq->dev = ctx->mxc_jpeg->dev;
	src_vq->allow_zero_bytesused = 1; /* keep old userspace apps working */

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &mxc_jpeg_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->mxc_jpeg->lock;
	dst_vq->dev = ctx->mxc_jpeg->dev;

	ret = vb2_queue_init(dst_vq);
	वापस ret;
पूर्ण

अटल व्योम mxc_jpeg_set_शेष_params(काष्ठा mxc_jpeg_ctx *ctx)
अणु
	काष्ठा mxc_jpeg_q_data *out_q = &ctx->out_q;
	काष्ठा mxc_jpeg_q_data *cap_q = &ctx->cap_q;
	काष्ठा mxc_jpeg_q_data *q[2] = अणुout_q, cap_qपूर्ण;
	पूर्णांक i;

	अगर (ctx->mxc_jpeg->mode == MXC_JPEG_ENCODE) अणु
		out_q->fmt = mxc_jpeg_find_क्रमmat(ctx, MXC_JPEG_DEFAULT_PFMT);
		cap_q->fmt = mxc_jpeg_find_क्रमmat(ctx, V4L2_PIX_FMT_JPEG);
	पूर्ण अन्यथा अणु
		out_q->fmt = mxc_jpeg_find_क्रमmat(ctx, V4L2_PIX_FMT_JPEG);
		cap_q->fmt = mxc_jpeg_find_क्रमmat(ctx, MXC_JPEG_DEFAULT_PFMT);
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		q[i]->w = MXC_JPEG_DEFAULT_WIDTH;
		q[i]->h = MXC_JPEG_DEFAULT_HEIGHT;
		q[i]->w_adjusted = MXC_JPEG_DEFAULT_WIDTH;
		q[i]->h_adjusted = MXC_JPEG_DEFAULT_HEIGHT;
		mxc_jpeg_bytesperline(q[i], 8);
		mxc_jpeg_sizeimage(q[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक mxc_jpeg_खोलो(काष्ठा file *file)
अणु
	काष्ठा mxc_jpeg_dev *mxc_jpeg = video_drvdata(file);
	काष्ठा video_device *mxc_vfd = video_devdata(file);
	काष्ठा device *dev = mxc_jpeg->dev;
	काष्ठा mxc_jpeg_ctx *ctx;
	पूर्णांक ret = 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (mutex_lock_पूर्णांकerruptible(&mxc_jpeg->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ मुक्त;
	पूर्ण

	v4l2_fh_init(&ctx->fh, mxc_vfd);
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->mxc_jpeg = mxc_jpeg;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(mxc_jpeg->m2m_dev, ctx,
					    mxc_jpeg_queue_init);

	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ error;
	पूर्ण

	mxc_jpeg_set_शेष_params(ctx);
	ctx->slot = MXC_MAX_SLOTS; /* slot not allocated yet */

	अगर (mxc_jpeg->mode == MXC_JPEG_DECODE)
		dev_dbg(dev, "Opened JPEG decoder instance %p\n", ctx);
	अन्यथा
		dev_dbg(dev, "Opened JPEG encoder instance %p\n", ctx);
	mutex_unlock(&mxc_jpeg->lock);

	वापस 0;

error:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	mutex_unlock(&mxc_jpeg->lock);
मुक्त:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक mxc_jpeg_querycap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_capability *cap)
अणु
	काष्ठा mxc_jpeg_dev *mxc_jpeg = video_drvdata(file);

	strscpy(cap->driver, MXC_JPEG_NAME " codec", माप(cap->driver));
	strscpy(cap->card, MXC_JPEG_NAME " codec", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(mxc_jpeg->dev));
	cap->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M_MPLANE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(priv);

	अगर (ctx->mxc_jpeg->mode == MXC_JPEG_ENCODE)
		वापस क्रमागत_fmt(mxc_क्रमmats, MXC_JPEG_NUM_FORMATS, f,
			MXC_JPEG_FMT_TYPE_ENC);
	अन्यथा
		वापस क्रमागत_fmt(mxc_क्रमmats, MXC_JPEG_NUM_FORMATS, f,
			MXC_JPEG_FMT_TYPE_RAW);
पूर्ण

अटल पूर्णांक mxc_jpeg_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(priv);

	अगर (ctx->mxc_jpeg->mode == MXC_JPEG_DECODE)
		वापस क्रमागत_fmt(mxc_क्रमmats, MXC_JPEG_NUM_FORMATS, f,
				MXC_JPEG_FMT_TYPE_ENC);
	अन्यथा
		वापस क्रमागत_fmt(mxc_क्रमmats, MXC_JPEG_NUM_FORMATS, f,
				MXC_JPEG_FMT_TYPE_RAW);
पूर्ण

अटल पूर्णांक mxc_jpeg_try_fmt(काष्ठा v4l2_क्रमmat *f, काष्ठा mxc_jpeg_fmt *fmt,
			    काष्ठा mxc_jpeg_ctx *ctx, पूर्णांक q_type)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *pfmt;
	u32 w = (pix_mp->width < MXC_JPEG_MAX_WIDTH) ?
		 pix_mp->width : MXC_JPEG_MAX_WIDTH;
	u32 h = (pix_mp->height < MXC_JPEG_MAX_HEIGHT) ?
		 pix_mp->height : MXC_JPEG_MAX_HEIGHT;
	पूर्णांक i;
	काष्ठा mxc_jpeg_q_data पंचांगp_q;

	स_रखो(pix_mp->reserved, 0, माप(pix_mp->reserved));
	pix_mp->field = V4L2_FIELD_NONE;
	pix_mp->num_planes = fmt->colplanes;
	pix_mp->pixelक्रमmat = fmt->fourcc;

	/*
	 * use MXC_JPEG_H_ALIGN instead of fmt->v_align, क्रम vertical
	 * alignment, to loosen up the alignment to multiple of 8,
	 * otherwise NV12-1080p fails as 1080 is not a multiple of 16
	 */
	v4l_bound_align_image(&w,
			      MXC_JPEG_MIN_WIDTH,
			      w, /* adjust करोwnwards*/
			      fmt->h_align,
			      &h,
			      MXC_JPEG_MIN_HEIGHT,
			      h, /* adjust करोwnwards*/
			      MXC_JPEG_H_ALIGN,
			      0);
	pix_mp->width = w; /* negotiate the width */
	pix_mp->height = h; /* negotiate the height */

	/* get user input पूर्णांकo the पंचांगp_q */
	पंचांगp_q.w = w;
	पंचांगp_q.h = h;
	पंचांगp_q.fmt = fmt;
	क्रम (i = 0; i < pix_mp->num_planes; i++) अणु
		pfmt = &pix_mp->plane_fmt[i];
		पंचांगp_q.bytesperline[i] = pfmt->bytesperline;
		पंचांगp_q.sizeimage[i] = pfmt->sizeimage;
	पूर्ण

	/* calculate bytesperline & sizeimage पूर्णांकo the पंचांगp_q */
	mxc_jpeg_bytesperline(&पंचांगp_q, 8);
	mxc_jpeg_sizeimage(&पंचांगp_q);

	/* adjust user क्रमmat according to our calculations */
	क्रम (i = 0; i < pix_mp->num_planes; i++) अणु
		pfmt = &pix_mp->plane_fmt[i];
		स_रखो(pfmt->reserved, 0, माप(pfmt->reserved));
		pfmt->bytesperline = पंचांगp_q.bytesperline[i];
		pfmt->sizeimage = पंचांगp_q.sizeimage[i];
	पूर्ण

	/* fix colorspace inक्रमmation to sRGB क्रम both output & capture */
	pix_mp->colorspace = V4L2_COLORSPACE_SRGB;
	pix_mp->ycbcr_enc = V4L2_YCBCR_ENC_601;
	pix_mp->xfer_func = V4L2_XFER_FUNC_SRGB;
	/*
	 * this hardware करोes not change the range of the samples
	 * but since inside JPEG the YUV quantization is full-range,
	 * this driver will always use full-range क्रम the raw frames, too
	 */
	pix_mp->quantization = V4L2_QUANTIZATION_FULL_RANGE;

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(priv);
	काष्ठा mxc_jpeg_dev *jpeg = ctx->mxc_jpeg;
	काष्ठा device *dev = jpeg->dev;
	काष्ठा mxc_jpeg_fmt *fmt;
	u32 fourcc = f->fmt.pix_mp.pixelक्रमmat;

	पूर्णांक q_type = (jpeg->mode == MXC_JPEG_DECODE) ?
		     MXC_JPEG_FMT_TYPE_RAW : MXC_JPEG_FMT_TYPE_ENC;

	अगर (!V4L2_TYPE_IS_MULTIPLANAR(f->type)) अणु
		dev_err(dev, "TRY_FMT with Invalid type: %d\n", f->type);
		वापस -EINVAL;
	पूर्ण

	fmt = mxc_jpeg_find_क्रमmat(ctx, fourcc);
	अगर (!fmt || fmt->flags != q_type) अणु
		dev_warn(dev, "Format not supported: %c%c%c%c, use the default.\n",
			 (fourcc & 0xff),
			 (fourcc >>  8) & 0xff,
			 (fourcc >> 16) & 0xff,
			 (fourcc >> 24) & 0xff);
		f->fmt.pix_mp.pixelक्रमmat = (jpeg->mode == MXC_JPEG_DECODE) ?
				MXC_JPEG_DEFAULT_PFMT : V4L2_PIX_FMT_JPEG;
		fmt = mxc_jpeg_find_क्रमmat(ctx, f->fmt.pix_mp.pixelक्रमmat);
	पूर्ण
	वापस mxc_jpeg_try_fmt(f, fmt, ctx, q_type);
पूर्ण

अटल पूर्णांक mxc_jpeg_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(priv);
	काष्ठा mxc_jpeg_dev *jpeg = ctx->mxc_jpeg;
	काष्ठा device *dev = jpeg->dev;
	काष्ठा mxc_jpeg_fmt *fmt;
	u32 fourcc = f->fmt.pix_mp.pixelक्रमmat;

	पूर्णांक q_type = (jpeg->mode == MXC_JPEG_ENCODE) ?
		     MXC_JPEG_FMT_TYPE_RAW : MXC_JPEG_FMT_TYPE_ENC;

	अगर (!V4L2_TYPE_IS_MULTIPLANAR(f->type)) अणु
		dev_err(dev, "TRY_FMT with Invalid type: %d\n", f->type);
		वापस -EINVAL;
	पूर्ण

	fmt = mxc_jpeg_find_क्रमmat(ctx, fourcc);
	अगर (!fmt || fmt->flags != q_type) अणु
		dev_warn(dev, "Format not supported: %c%c%c%c, use the default.\n",
			 (fourcc & 0xff),
			 (fourcc >>  8) & 0xff,
			 (fourcc >> 16) & 0xff,
			 (fourcc >> 24) & 0xff);
		f->fmt.pix_mp.pixelक्रमmat = (jpeg->mode == MXC_JPEG_ENCODE) ?
				MXC_JPEG_DEFAULT_PFMT : V4L2_PIX_FMT_JPEG;
		fmt = mxc_jpeg_find_क्रमmat(ctx, f->fmt.pix_mp.pixelक्रमmat);
	पूर्ण
	वापस mxc_jpeg_try_fmt(f, fmt, ctx, q_type);
पूर्ण

अटल पूर्णांक mxc_jpeg_s_fmt(काष्ठा mxc_jpeg_ctx *ctx,
			  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा mxc_jpeg_q_data *q_data = शून्य;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा mxc_jpeg_dev *jpeg = ctx->mxc_jpeg;
	पूर्णांक i;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = mxc_jpeg_get_q_data(ctx, f->type);

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&jpeg->v4l2_dev, "queue busy\n");
		वापस -EBUSY;
	पूर्ण

	q_data->fmt = mxc_jpeg_find_क्रमmat(ctx, pix_mp->pixelक्रमmat);
	q_data->w = pix_mp->width;
	q_data->h = pix_mp->height;

	q_data->w_adjusted = q_data->w;
	q_data->h_adjusted = q_data->h;
	अगर (jpeg->mode == MXC_JPEG_DECODE) अणु
		/*
		 * align up the resolution क्रम CAST IP,
		 * but leave the buffer resolution unchanged
		 */
		v4l_bound_align_image(&q_data->w_adjusted,
				      q_data->w_adjusted,  /* adjust upwards */
				      MXC_JPEG_MAX_WIDTH,
				      q_data->fmt->h_align,
				      &q_data->h_adjusted,
				      q_data->h_adjusted, /* adjust upwards */
				      MXC_JPEG_MAX_HEIGHT,
				      q_data->fmt->v_align,
				      0);
	पूर्ण अन्यथा अणु
		/*
		 * align करोwn the resolution क्रम CAST IP,
		 * but leave the buffer resolution unchanged
		 */
		v4l_bound_align_image(&q_data->w_adjusted,
				      MXC_JPEG_MIN_WIDTH,
				      q_data->w_adjusted, /* adjust करोwnwards*/
				      q_data->fmt->h_align,
				      &q_data->h_adjusted,
				      MXC_JPEG_MIN_HEIGHT,
				      q_data->h_adjusted, /* adjust करोwnwards*/
				      q_data->fmt->v_align,
				      0);
	पूर्ण

	क्रम (i = 0; i < pix_mp->num_planes; i++) अणु
		q_data->bytesperline[i] = pix_mp->plane_fmt[i].bytesperline;
		q_data->sizeimage[i] = pix_mp->plane_fmt[i].sizeimage;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = mxc_jpeg_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस mxc_jpeg_s_fmt(mxc_jpeg_fh_to_ctx(priv), f);
पूर्ण

अटल पूर्णांक mxc_jpeg_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = mxc_jpeg_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस mxc_jpeg_s_fmt(mxc_jpeg_fh_to_ctx(priv), f);
पूर्ण

अटल पूर्णांक mxc_jpeg_g_fmt_vid(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(priv);
	काष्ठा mxc_jpeg_dev *jpeg = ctx->mxc_jpeg;
	काष्ठा device *dev = jpeg->dev;
	काष्ठा v4l2_pix_क्रमmat_mplane   *pix_mp = &f->fmt.pix_mp;
	काष्ठा mxc_jpeg_q_data *q_data = mxc_jpeg_get_q_data(ctx, f->type);
	पूर्णांक i;

	अगर (!V4L2_TYPE_IS_MULTIPLANAR(f->type)) अणु
		dev_err(dev, "G_FMT with Invalid type: %d\n", f->type);
		वापस -EINVAL;
	पूर्ण

	pix_mp->pixelक्रमmat = q_data->fmt->fourcc;
	pix_mp->width = q_data->w;
	pix_mp->height = q_data->h;
	pix_mp->field = V4L2_FIELD_NONE;

	/* fix colorspace inक्रमmation to sRGB क्रम both output & capture */
	pix_mp->colorspace = V4L2_COLORSPACE_SRGB;
	pix_mp->ycbcr_enc = V4L2_YCBCR_ENC_601;
	pix_mp->xfer_func = V4L2_XFER_FUNC_SRGB;
	pix_mp->quantization = V4L2_QUANTIZATION_FULL_RANGE;

	pix_mp->num_planes = q_data->fmt->colplanes;
	क्रम (i = 0; i < pix_mp->num_planes; i++) अणु
		pix_mp->plane_fmt[i].bytesperline = q_data->bytesperline[i];
		pix_mp->plane_fmt[i].sizeimage = q_data->sizeimage[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_jpeg_subscribe_event(काष्ठा v4l2_fh *fh,
				    स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subscribe(fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mxc_jpeg_dqbuf(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(priv);
	काष्ठा device *dev = ctx->mxc_jpeg->dev;
	पूर्णांक num_src_पढ़ोy = v4l2_m2m_num_src_bufs_पढ़ोy(fh->m2m_ctx);
	पूर्णांक ret;

	dev_dbg(dev, "DQBUF type=%d, index=%d", buf->type, buf->index);
	अगर (ctx->stopping == 1	&& num_src_पढ़ोy == 0) अणु
		/* No more src bufs, notअगरy app EOS */
		notअगरy_eos(ctx);
		ctx->stopping = 0;
	पूर्ण

	ret = v4l2_m2m_dqbuf(file, fh->m2m_ctx, buf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops mxc_jpeg_ioctl_ops = अणु
	.vidioc_querycap		= mxc_jpeg_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= mxc_jpeg_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= mxc_jpeg_क्रमागत_fmt_vid_out,

	.vidioc_try_fmt_vid_cap_mplane	= mxc_jpeg_try_fmt_vid_cap,
	.vidioc_try_fmt_vid_out_mplane	= mxc_jpeg_try_fmt_vid_out,

	.vidioc_s_fmt_vid_cap_mplane	= mxc_jpeg_s_fmt_vid_cap,
	.vidioc_s_fmt_vid_out_mplane	= mxc_jpeg_s_fmt_vid_out,

	.vidioc_g_fmt_vid_cap_mplane	= mxc_jpeg_g_fmt_vid,
	.vidioc_g_fmt_vid_out_mplane	= mxc_jpeg_g_fmt_vid,

	.vidioc_subscribe_event		= mxc_jpeg_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,

	.vidioc_try_decoder_cmd		= v4l2_m2m_ioctl_try_decoder_cmd,
	.vidioc_decoder_cmd		= mxc_jpeg_decoder_cmd,
	.vidioc_try_encoder_cmd		= v4l2_m2m_ioctl_try_encoder_cmd,
	.vidioc_encoder_cmd		= mxc_jpeg_encoder_cmd,

	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= mxc_jpeg_dqbuf,

	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,
	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,
पूर्ण;

अटल पूर्णांक mxc_jpeg_release(काष्ठा file *file)
अणु
	काष्ठा mxc_jpeg_dev *mxc_jpeg = video_drvdata(file);
	काष्ठा mxc_jpeg_ctx *ctx = mxc_jpeg_fh_to_ctx(file->निजी_data);
	काष्ठा device *dev = mxc_jpeg->dev;

	mutex_lock(&mxc_jpeg->lock);
	अगर (mxc_jpeg->mode == MXC_JPEG_DECODE)
		dev_dbg(dev, "Release JPEG decoder instance on slot %d.",
			ctx->slot);
	अन्यथा
		dev_dbg(dev, "Release JPEG encoder instance on slot %d.",
			ctx->slot);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
	mutex_unlock(&mxc_jpeg->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations mxc_jpeg_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= mxc_jpeg_खोलो,
	.release	= mxc_jpeg_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल काष्ठा v4l2_m2m_ops mxc_jpeg_m2m_ops = अणु
	.device_run	= mxc_jpeg_device_run,
पूर्ण;

अटल व्योम mxc_jpeg_detach_pm_करोमुख्यs(काष्ठा mxc_jpeg_dev *jpeg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < jpeg->num_करोमुख्यs; i++) अणु
		अगर (jpeg->pd_link[i] && !IS_ERR(jpeg->pd_link[i]))
			device_link_del(jpeg->pd_link[i]);
		अगर (jpeg->pd_dev[i] && !IS_ERR(jpeg->pd_dev[i]))
			dev_pm_करोमुख्य_detach(jpeg->pd_dev[i], true);
		jpeg->pd_dev[i] = शून्य;
		jpeg->pd_link[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mxc_jpeg_attach_pm_करोमुख्यs(काष्ठा mxc_jpeg_dev *jpeg)
अणु
	काष्ठा device *dev = jpeg->dev;
	काष्ठा device_node *np = jpeg->pdev->dev.of_node;
	पूर्णांक i;
	पूर्णांक ret;

	jpeg->num_करोमुख्यs = of_count_phandle_with_args(np, "power-domains",
						       "#power-domain-cells");
	अगर (jpeg->num_करोमुख्यs < 0) अणु
		dev_err(dev, "No power domains defined for jpeg node\n");
		वापस jpeg->num_करोमुख्यs;
	पूर्ण

	jpeg->pd_dev = devm_kदो_स्मृति_array(dev, jpeg->num_करोमुख्यs,
					  माप(*jpeg->pd_dev), GFP_KERNEL);
	अगर (!jpeg->pd_dev)
		वापस -ENOMEM;

	jpeg->pd_link = devm_kदो_स्मृति_array(dev, jpeg->num_करोमुख्यs,
					   माप(*jpeg->pd_link), GFP_KERNEL);
	अगर (!jpeg->pd_link)
		वापस -ENOMEM;

	क्रम (i = 0; i < jpeg->num_करोमुख्यs; i++) अणु
		jpeg->pd_dev[i] = dev_pm_करोमुख्य_attach_by_id(dev, i);
		अगर (IS_ERR(jpeg->pd_dev[i])) अणु
			ret = PTR_ERR(jpeg->pd_dev[i]);
			जाओ fail;
		पूर्ण

		jpeg->pd_link[i] = device_link_add(dev, jpeg->pd_dev[i],
						   DL_FLAG_STATELESS |
						   DL_FLAG_PM_RUNTIME |
						   DL_FLAG_RPM_ACTIVE);
		अगर (!jpeg->pd_link[i]) अणु
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	mxc_jpeg_detach_pm_करोमुख्यs(jpeg);
	वापस ret;
पूर्ण

अटल पूर्णांक mxc_jpeg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxc_jpeg_dev *jpeg;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक dec_irq;
	पूर्णांक ret;
	पूर्णांक mode;
	स्थिर काष्ठा of_device_id *of_id;
	अचिन्हित पूर्णांक slot;

	of_id = of_match_node(mxc_jpeg_match, dev->of_node);
	mode = *(स्थिर पूर्णांक *)of_id->data;

	jpeg = devm_kzalloc(dev, माप(काष्ठा mxc_jpeg_dev), GFP_KERNEL);
	अगर (!jpeg)
		वापस -ENOMEM;

	mutex_init(&jpeg->lock);
	spin_lock_init(&jpeg->hw_lock);

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "No suitable DMA available.\n");
		जाओ err_irq;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	jpeg->base_reg = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(jpeg->base_reg))
		वापस PTR_ERR(jpeg->base_reg);

	क्रम (slot = 0; slot < MXC_MAX_SLOTS; slot++) अणु
		dec_irq = platक्रमm_get_irq(pdev, slot);
		अगर (dec_irq < 0) अणु
			dev_err(&pdev->dev, "Failed to get irq %d\n", dec_irq);
			ret = dec_irq;
			जाओ err_irq;
		पूर्ण
		ret = devm_request_irq(&pdev->dev, dec_irq, mxc_jpeg_dec_irq,
				       0, pdev->name, jpeg);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to request irq %d (%d)\n",
				dec_irq, ret);
			जाओ err_irq;
		पूर्ण
	पूर्ण

	jpeg->pdev = pdev;
	jpeg->dev = dev;
	jpeg->mode = mode;

	ret = mxc_jpeg_attach_pm_करोमुख्यs(jpeg);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to attach power domains %d\n", ret);
		वापस ret;
	पूर्ण

	/* v4l2 */
	ret = v4l2_device_रेजिस्टर(dev, &jpeg->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register v4l2 device\n");
		जाओ err_रेजिस्टर;
	पूर्ण
	jpeg->m2m_dev = v4l2_m2m_init(&mxc_jpeg_m2m_ops);
	अगर (IS_ERR(jpeg->m2m_dev)) अणु
		dev_err(dev, "failed to register v4l2 device\n");
		ret = PTR_ERR(jpeg->m2m_dev);
		जाओ err_m2m;
	पूर्ण

	jpeg->dec_vdev = video_device_alloc();
	अगर (!jpeg->dec_vdev) अणु
		dev_err(dev, "failed to register v4l2 device\n");
		ret = -ENOMEM;
		जाओ err_vdev_alloc;
	पूर्ण
	अगर (mode == MXC_JPEG_ENCODE)
		snम_लिखो(jpeg->dec_vdev->name,
			 माप(jpeg->dec_vdev->name),
			 "%s-enc", MXC_JPEG_NAME);
	अन्यथा
		snम_लिखो(jpeg->dec_vdev->name,
			 माप(jpeg->dec_vdev->name),
			 "%s-dec", MXC_JPEG_NAME);

	jpeg->dec_vdev->fops = &mxc_jpeg_fops;
	jpeg->dec_vdev->ioctl_ops = &mxc_jpeg_ioctl_ops;
	jpeg->dec_vdev->minor = -1;
	jpeg->dec_vdev->release = video_device_release;
	jpeg->dec_vdev->lock = &jpeg->lock; /* lock क्रम ioctl serialization */
	jpeg->dec_vdev->v4l2_dev = &jpeg->v4l2_dev;
	jpeg->dec_vdev->vfl_dir = VFL_सूची_M2M;
	jpeg->dec_vdev->device_caps = V4L2_CAP_STREAMING |
					V4L2_CAP_VIDEO_M2M_MPLANE;
	अगर (mode == MXC_JPEG_ENCODE) अणु
		v4l2_disable_ioctl(jpeg->dec_vdev, VIDIOC_DECODER_CMD);
		v4l2_disable_ioctl(jpeg->dec_vdev, VIDIOC_TRY_DECODER_CMD);
	पूर्ण अन्यथा अणु
		v4l2_disable_ioctl(jpeg->dec_vdev, VIDIOC_ENCODER_CMD);
		v4l2_disable_ioctl(jpeg->dec_vdev, VIDIOC_TRY_ENCODER_CMD);
	पूर्ण
	ret = video_रेजिस्टर_device(jpeg->dec_vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(dev, "failed to register video device\n");
		जाओ err_vdev_रेजिस्टर;
	पूर्ण
	video_set_drvdata(jpeg->dec_vdev, jpeg);
	अगर (mode == MXC_JPEG_ENCODE)
		v4l2_info(&jpeg->v4l2_dev,
			  "encoder device registered as /dev/video%d (%d,%d)\n",
			  jpeg->dec_vdev->num, VIDEO_MAJOR,
			  jpeg->dec_vdev->minor);
	अन्यथा
		v4l2_info(&jpeg->v4l2_dev,
			  "decoder device registered as /dev/video%d (%d,%d)\n",
			  jpeg->dec_vdev->num, VIDEO_MAJOR,
			  jpeg->dec_vdev->minor);

	platक्रमm_set_drvdata(pdev, jpeg);

	वापस 0;

err_vdev_रेजिस्टर:
	video_device_release(jpeg->dec_vdev);

err_vdev_alloc:
	v4l2_m2m_release(jpeg->m2m_dev);

err_m2m:
	v4l2_device_unरेजिस्टर(&jpeg->v4l2_dev);

err_रेजिस्टर:
err_irq:
	वापस ret;
पूर्ण

अटल पूर्णांक mxc_jpeg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक slot;
	काष्ठा mxc_jpeg_dev *jpeg = platक्रमm_get_drvdata(pdev);

	क्रम (slot = 0; slot < MXC_MAX_SLOTS; slot++)
		mxc_jpeg_मुक्त_slot_data(jpeg, slot);

	video_unरेजिस्टर_device(jpeg->dec_vdev);
	v4l2_m2m_release(jpeg->m2m_dev);
	v4l2_device_unरेजिस्टर(&jpeg->v4l2_dev);
	mxc_jpeg_detach_pm_करोमुख्यs(jpeg);

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(of, mxc_jpeg_match);

अटल काष्ठा platक्रमm_driver mxc_jpeg_driver = अणु
	.probe = mxc_jpeg_probe,
	.हटाओ = mxc_jpeg_हटाओ,
	.driver = अणु
		.name = "mxc-jpeg",
		.of_match_table = mxc_jpeg_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mxc_jpeg_driver);

MODULE_AUTHOR("Zhengyu Shen <zhengyu.shen_1@nxp.com>");
MODULE_AUTHOR("Mirela Rabulea <mirela.rabulea@nxp.com>");
MODULE_DESCRIPTION("V4L2 driver for i.MX8 QXP/QM JPEG encoder/decoder");
MODULE_LICENSE("GPL v2");
