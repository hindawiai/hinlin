<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_driver.c  --  USB Video Class driver
 *
 *      Copyright (C) 2005-2010
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/atomic.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/version.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "uvcvideo.h"

#घोषणा DRIVER_AUTHOR		"Laurent Pinchart " \
				"<laurent.pinchart@ideasonboard.com>"
#घोषणा DRIVER_DESC		"USB Video Class driver"

अचिन्हित पूर्णांक uvc_घड़ी_param = CLOCK_MONOTONIC;
अचिन्हित पूर्णांक uvc_hw_बारtamps_param;
अचिन्हित पूर्णांक uvc_no_drop_param;
अटल अचिन्हित पूर्णांक uvc_quirks_param = -1;
अचिन्हित पूर्णांक uvc_dbg_param;
अचिन्हित पूर्णांक uvc_समयout_param = UVC_CTRL_STREAMING_TIMEOUT;

/* ------------------------------------------------------------------------
 * Video क्रमmats
 */

अटल काष्ठा uvc_क्रमmat_desc uvc_fmts[] = अणु
	अणु
		.name		= "YUV 4:2:2 (YUYV)",
		.guid		= UVC_GUID_FORMAT_YUY2,
		.fcc		= V4L2_PIX_FMT_YUYV,
	पूर्ण,
	अणु
		.name		= "YUV 4:2:2 (YUYV)",
		.guid		= UVC_GUID_FORMAT_YUY2_ISIGHT,
		.fcc		= V4L2_PIX_FMT_YUYV,
	पूर्ण,
	अणु
		.name		= "YUV 4:2:0 (NV12)",
		.guid		= UVC_GUID_FORMAT_NV12,
		.fcc		= V4L2_PIX_FMT_NV12,
	पूर्ण,
	अणु
		.name		= "MJPEG",
		.guid		= UVC_GUID_FORMAT_MJPEG,
		.fcc		= V4L2_PIX_FMT_MJPEG,
	पूर्ण,
	अणु
		.name		= "YVU 4:2:0 (YV12)",
		.guid		= UVC_GUID_FORMAT_YV12,
		.fcc		= V4L2_PIX_FMT_YVU420,
	पूर्ण,
	अणु
		.name		= "YUV 4:2:0 (I420)",
		.guid		= UVC_GUID_FORMAT_I420,
		.fcc		= V4L2_PIX_FMT_YUV420,
	पूर्ण,
	अणु
		.name		= "YUV 4:2:0 (M420)",
		.guid		= UVC_GUID_FORMAT_M420,
		.fcc		= V4L2_PIX_FMT_M420,
	पूर्ण,
	अणु
		.name		= "YUV 4:2:2 (UYVY)",
		.guid		= UVC_GUID_FORMAT_UYVY,
		.fcc		= V4L2_PIX_FMT_UYVY,
	पूर्ण,
	अणु
		.name		= "Greyscale 8-bit (Y800)",
		.guid		= UVC_GUID_FORMAT_Y800,
		.fcc		= V4L2_PIX_FMT_GREY,
	पूर्ण,
	अणु
		.name		= "Greyscale 8-bit (Y8  )",
		.guid		= UVC_GUID_FORMAT_Y8,
		.fcc		= V4L2_PIX_FMT_GREY,
	पूर्ण,
	अणु
		.name		= "Greyscale 8-bit (D3DFMT_L8)",
		.guid		= UVC_GUID_FORMAT_D3DFMT_L8,
		.fcc		= V4L2_PIX_FMT_GREY,
	पूर्ण,
	अणु
		.name		= "IR 8-bit (L8_IR)",
		.guid		= UVC_GUID_FORMAT_KSMEDIA_L8_IR,
		.fcc		= V4L2_PIX_FMT_GREY,
	पूर्ण,
	अणु
		.name		= "Greyscale 10-bit (Y10 )",
		.guid		= UVC_GUID_FORMAT_Y10,
		.fcc		= V4L2_PIX_FMT_Y10,
	पूर्ण,
	अणु
		.name		= "Greyscale 12-bit (Y12 )",
		.guid		= UVC_GUID_FORMAT_Y12,
		.fcc		= V4L2_PIX_FMT_Y12,
	पूर्ण,
	अणु
		.name		= "Greyscale 16-bit (Y16 )",
		.guid		= UVC_GUID_FORMAT_Y16,
		.fcc		= V4L2_PIX_FMT_Y16,
	पूर्ण,
	अणु
		.name		= "BGGR Bayer (BY8 )",
		.guid		= UVC_GUID_FORMAT_BY8,
		.fcc		= V4L2_PIX_FMT_SBGGR8,
	पूर्ण,
	अणु
		.name		= "BGGR Bayer (BA81)",
		.guid		= UVC_GUID_FORMAT_BA81,
		.fcc		= V4L2_PIX_FMT_SBGGR8,
	पूर्ण,
	अणु
		.name		= "GBRG Bayer (GBRG)",
		.guid		= UVC_GUID_FORMAT_GBRG,
		.fcc		= V4L2_PIX_FMT_SGBRG8,
	पूर्ण,
	अणु
		.name		= "GRBG Bayer (GRBG)",
		.guid		= UVC_GUID_FORMAT_GRBG,
		.fcc		= V4L2_PIX_FMT_SGRBG8,
	पूर्ण,
	अणु
		.name		= "RGGB Bayer (RGGB)",
		.guid		= UVC_GUID_FORMAT_RGGB,
		.fcc		= V4L2_PIX_FMT_SRGGB8,
	पूर्ण,
	अणु
		.name		= "RGB565",
		.guid		= UVC_GUID_FORMAT_RGBP,
		.fcc		= V4L2_PIX_FMT_RGB565,
	पूर्ण,
	अणु
		.name		= "BGR 8:8:8 (BGR3)",
		.guid		= UVC_GUID_FORMAT_BGR3,
		.fcc		= V4L2_PIX_FMT_BGR24,
	पूर्ण,
	अणु
		.name		= "H.264",
		.guid		= UVC_GUID_FORMAT_H264,
		.fcc		= V4L2_PIX_FMT_H264,
	पूर्ण,
	अणु
		.name		= "Greyscale 8 L/R (Y8I)",
		.guid		= UVC_GUID_FORMAT_Y8I,
		.fcc		= V4L2_PIX_FMT_Y8I,
	पूर्ण,
	अणु
		.name		= "Greyscale 12 L/R (Y12I)",
		.guid		= UVC_GUID_FORMAT_Y12I,
		.fcc		= V4L2_PIX_FMT_Y12I,
	पूर्ण,
	अणु
		.name		= "Depth data 16-bit (Z16)",
		.guid		= UVC_GUID_FORMAT_Z16,
		.fcc		= V4L2_PIX_FMT_Z16,
	पूर्ण,
	अणु
		.name		= "Bayer 10-bit (SRGGB10P)",
		.guid		= UVC_GUID_FORMAT_RW10,
		.fcc		= V4L2_PIX_FMT_SRGGB10P,
	पूर्ण,
	अणु
		.name		= "Bayer 16-bit (SBGGR16)",
		.guid		= UVC_GUID_FORMAT_BG16,
		.fcc		= V4L2_PIX_FMT_SBGGR16,
	पूर्ण,
	अणु
		.name		= "Bayer 16-bit (SGBRG16)",
		.guid		= UVC_GUID_FORMAT_GB16,
		.fcc		= V4L2_PIX_FMT_SGBRG16,
	पूर्ण,
	अणु
		.name		= "Bayer 16-bit (SRGGB16)",
		.guid		= UVC_GUID_FORMAT_RG16,
		.fcc		= V4L2_PIX_FMT_SRGGB16,
	पूर्ण,
	अणु
		.name		= "Bayer 16-bit (SGRBG16)",
		.guid		= UVC_GUID_FORMAT_GR16,
		.fcc		= V4L2_PIX_FMT_SGRBG16,
	पूर्ण,
	अणु
		.name		= "Depth data 16-bit (Z16)",
		.guid		= UVC_GUID_FORMAT_INVZ,
		.fcc		= V4L2_PIX_FMT_Z16,
	पूर्ण,
	अणु
		.name		= "Greyscale 10-bit (Y10 )",
		.guid		= UVC_GUID_FORMAT_INVI,
		.fcc		= V4L2_PIX_FMT_Y10,
	पूर्ण,
	अणु
		.name		= "IR:Depth 26-bit (INZI)",
		.guid		= UVC_GUID_FORMAT_INZI,
		.fcc		= V4L2_PIX_FMT_INZI,
	पूर्ण,
	अणु
		.name		= "4-bit Depth Confidence (Packed)",
		.guid		= UVC_GUID_FORMAT_CNF4,
		.fcc		= V4L2_PIX_FMT_CNF4,
	पूर्ण,
	अणु
		.name		= "HEVC",
		.guid		= UVC_GUID_FORMAT_HEVC,
		.fcc		= V4L2_PIX_FMT_HEVC,
	पूर्ण,
पूर्ण;

/* ------------------------------------------------------------------------
 * Utility functions
 */

काष्ठा usb_host_endpoपूर्णांक *uvc_find_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alts,
		u8 epaddr)
अणु
	काष्ठा usb_host_endpoपूर्णांक *ep;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < alts->desc.bNumEndpoपूर्णांकs; ++i) अणु
		ep = &alts->endpoपूर्णांक[i];
		अगर (ep->desc.bEndpoपूर्णांकAddress == epaddr)
			वापस ep;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा uvc_क्रमmat_desc *uvc_क्रमmat_by_guid(स्थिर u8 guid[16])
अणु
	अचिन्हित पूर्णांक len = ARRAY_SIZE(uvc_fmts);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; ++i) अणु
		अगर (स_भेद(guid, uvc_fmts[i].guid, 16) == 0)
			वापस &uvc_fmts[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत v4l2_colorspace uvc_colorspace(स्थिर u8 primaries)
अणु
	अटल स्थिर क्रमागत v4l2_colorspace colorprimaries[] = अणु
		V4L2_COLORSPACE_DEFAULT,  /* Unspecअगरied */
		V4L2_COLORSPACE_SRGB,
		V4L2_COLORSPACE_470_SYSTEM_M,
		V4L2_COLORSPACE_470_SYSTEM_BG,
		V4L2_COLORSPACE_SMPTE170M,
		V4L2_COLORSPACE_SMPTE240M,
	पूर्ण;

	अगर (primaries < ARRAY_SIZE(colorprimaries))
		वापस colorprimaries[primaries];

	वापस V4L2_COLORSPACE_DEFAULT;  /* Reserved */
पूर्ण

अटल क्रमागत v4l2_xfer_func uvc_xfer_func(स्थिर u8 transfer_अक्षरacteristics)
अणु
	/*
	 * V4L2 करोes not currently have definitions क्रम all possible values of
	 * UVC transfer अक्षरacteristics. If v4l2_xfer_func is extended with new
	 * values, the mapping below should be updated.
	 *
	 * Substitutions are taken from the mapping given क्रम
	 * V4L2_XFER_FUNC_DEFAULT करोcumented in videodev2.h.
	 */
	अटल स्थिर क्रमागत v4l2_xfer_func xfer_funcs[] = अणु
		V4L2_XFER_FUNC_DEFAULT,    /* Unspecअगरied */
		V4L2_XFER_FUNC_709,
		V4L2_XFER_FUNC_709,        /* Substitution क्रम BT.470-2 M */
		V4L2_XFER_FUNC_709,        /* Substitution क्रम BT.470-2 B, G */
		V4L2_XFER_FUNC_709,        /* Substitution क्रम SMPTE 170M */
		V4L2_XFER_FUNC_SMPTE240M,
		V4L2_XFER_FUNC_NONE,
		V4L2_XFER_FUNC_SRGB,
	पूर्ण;

	अगर (transfer_अक्षरacteristics < ARRAY_SIZE(xfer_funcs))
		वापस xfer_funcs[transfer_अक्षरacteristics];

	वापस V4L2_XFER_FUNC_DEFAULT;  /* Reserved */
पूर्ण

अटल क्रमागत v4l2_ycbcr_encoding uvc_ycbcr_enc(स्थिर u8 matrix_coefficients)
अणु
	/*
	 * V4L2 करोes not currently have definitions क्रम all possible values of
	 * UVC matrix coefficients. If v4l2_ycbcr_encoding is extended with new
	 * values, the mapping below should be updated.
	 *
	 * Substitutions are taken from the mapping given क्रम
	 * V4L2_YCBCR_ENC_DEFAULT करोcumented in videodev2.h.
	 *
	 * FCC is assumed to be बंद enough to 601.
	 */
	अटल स्थिर क्रमागत v4l2_ycbcr_encoding ycbcr_encs[] = अणु
		V4L2_YCBCR_ENC_DEFAULT,  /* Unspecअगरied */
		V4L2_YCBCR_ENC_709,
		V4L2_YCBCR_ENC_601,      /* Substitution क्रम FCC */
		V4L2_YCBCR_ENC_601,      /* Substitution क्रम BT.470-2 B, G */
		V4L2_YCBCR_ENC_601,
		V4L2_YCBCR_ENC_SMPTE240M,
	पूर्ण;

	अगर (matrix_coefficients < ARRAY_SIZE(ycbcr_encs))
		वापस ycbcr_encs[matrix_coefficients];

	वापस V4L2_YCBCR_ENC_DEFAULT;  /* Reserved */
पूर्ण

/* Simplअगरy a fraction using a simple जारीd fraction decomposition. The
 * idea here is to convert fractions such as 333333/10000000 to 1/30 using
 * 32 bit arithmetic only. The algorithm is not perfect and relies upon two
 * arbitrary parameters to हटाओ non-signअगरicative terms from the simple
 * जारीd fraction decomposition. Using 8 and 333 क्रम n_terms and threshold
 * respectively seems to give nice results.
 */
व्योम uvc_simplअगरy_fraction(u32 *numerator, u32 *denominator,
		अचिन्हित पूर्णांक n_terms, अचिन्हित पूर्णांक threshold)
अणु
	u32 *an;
	u32 x, y, r;
	अचिन्हित पूर्णांक i, n;

	an = kदो_स्मृति_array(n_terms, माप(*an), GFP_KERNEL);
	अगर (an == शून्य)
		वापस;

	/* Convert the fraction to a simple जारीd fraction. See
	 * https://mathक्रमum.org/dr.math/faq/faq.fractions.hपंचांगl
	 * Stop अगर the current term is bigger than or equal to the given
	 * threshold.
	 */
	x = *numerator;
	y = *denominator;

	क्रम (n = 0; n < n_terms && y != 0; ++n) अणु
		an[n] = x / y;
		अगर (an[n] >= threshold) अणु
			अगर (n < 2)
				n++;
			अवरोध;
		पूर्ण

		r = x - an[n] * y;
		x = y;
		y = r;
	पूर्ण

	/* Expand the simple जारीd fraction back to an पूर्णांकeger fraction. */
	x = 0;
	y = 1;

	क्रम (i = n; i > 0; --i) अणु
		r = y;
		y = an[i-1] * y + x;
		x = r;
	पूर्ण

	*numerator = y;
	*denominator = x;
	kमुक्त(an);
पूर्ण

/* Convert a fraction to a frame पूर्णांकerval in 100ns multiples. The idea here is
 * to compute numerator / denominator * 10000000 using 32 bit fixed poपूर्णांक
 * arithmetic only.
 */
u32 uvc_fraction_to_पूर्णांकerval(u32 numerator, u32 denominator)
अणु
	u32 multiplier;

	/* Saturate the result अगर the operation would overflow. */
	अगर (denominator == 0 ||
	    numerator/denominator >= ((u32)-1)/10000000)
		वापस (u32)-1;

	/* Divide both the denominator and the multiplier by two until
	 * numerator * multiplier करोesn't overflow. If anyone knows a better
	 * algorithm please let me know.
	 */
	multiplier = 10000000;
	जबतक (numerator > ((u32)-1)/multiplier) अणु
		multiplier /= 2;
		denominator /= 2;
	पूर्ण

	वापस denominator ? numerator * multiplier / denominator : 0;
पूर्ण

/* ------------------------------------------------------------------------
 * Terminal and unit management
 */

काष्ठा uvc_entity *uvc_entity_by_id(काष्ठा uvc_device *dev, पूर्णांक id)
अणु
	काष्ठा uvc_entity *entity;

	list_क्रम_each_entry(entity, &dev->entities, list) अणु
		अगर (entity->id == id)
			वापस entity;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा uvc_entity *uvc_entity_by_reference(काष्ठा uvc_device *dev,
	पूर्णांक id, काष्ठा uvc_entity *entity)
अणु
	अचिन्हित पूर्णांक i;

	अगर (entity == शून्य)
		entity = list_entry(&dev->entities, काष्ठा uvc_entity, list);

	list_क्रम_each_entry_जारी(entity, &dev->entities, list) अणु
		क्रम (i = 0; i < entity->bNrInPins; ++i)
			अगर (entity->baSourceID[i] == id)
				वापस entity;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा uvc_streaming *uvc_stream_by_id(काष्ठा uvc_device *dev, पूर्णांक id)
अणु
	काष्ठा uvc_streaming *stream;

	list_क्रम_each_entry(stream, &dev->streams, list) अणु
		अगर (stream->header.bTerminalLink == id)
			वापस stream;
	पूर्ण

	वापस शून्य;
पूर्ण

/* ------------------------------------------------------------------------
 * Streaming Object Management
 */

अटल व्योम uvc_stream_delete(काष्ठा uvc_streaming *stream)
अणु
	अगर (stream->async_wq)
		destroy_workqueue(stream->async_wq);

	mutex_destroy(&stream->mutex);

	usb_put_पूर्णांकf(stream->पूर्णांकf);

	kमुक्त(stream->क्रमmat);
	kमुक्त(stream->header.bmaControls);
	kमुक्त(stream);
पूर्ण

अटल काष्ठा uvc_streaming *uvc_stream_new(काष्ठा uvc_device *dev,
					    काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा uvc_streaming *stream;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (stream == शून्य)
		वापस शून्य;

	mutex_init(&stream->mutex);

	stream->dev = dev;
	stream->पूर्णांकf = usb_get_पूर्णांकf(पूर्णांकf);
	stream->पूर्णांकfnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	/* Allocate a stream specअगरic work queue क्रम asynchronous tasks. */
	stream->async_wq = alloc_workqueue("uvcvideo", WQ_UNBOUND | WQ_HIGHPRI,
					   0);
	अगर (!stream->async_wq) अणु
		uvc_stream_delete(stream);
		वापस शून्य;
	पूर्ण

	वापस stream;
पूर्ण

/* ------------------------------------------------------------------------
 * Descriptors parsing
 */

अटल पूर्णांक uvc_parse_क्रमmat(काष्ठा uvc_device *dev,
	काष्ठा uvc_streaming *streaming, काष्ठा uvc_क्रमmat *क्रमmat,
	u32 **पूर्णांकervals, अचिन्हित अक्षर *buffer, पूर्णांक buflen)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = streaming->पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *alts = पूर्णांकf->cur_altsetting;
	काष्ठा uvc_क्रमmat_desc *fmtdesc;
	काष्ठा uvc_frame *frame;
	स्थिर अचिन्हित अक्षर *start = buffer;
	अचिन्हित पूर्णांक width_multiplier = 1;
	अचिन्हित पूर्णांक पूर्णांकerval;
	अचिन्हित पूर्णांक i, n;
	u8 ftype;

	क्रमmat->type = buffer[2];
	क्रमmat->index = buffer[3];

	चयन (buffer[2]) अणु
	हाल UVC_VS_FORMAT_UNCOMPRESSED:
	हाल UVC_VS_FORMAT_FRAME_BASED:
		n = buffer[2] == UVC_VS_FORMAT_UNCOMPRESSED ? 27 : 28;
		अगर (buflen < n) अणु
			uvc_dbg(dev, DESCR,
				"device %d videostreaming interface %d FORMAT error\n",
				dev->udev->devnum,
				alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		/* Find the क्रमmat descriptor from its GUID. */
		fmtdesc = uvc_क्रमmat_by_guid(&buffer[5]);

		अगर (fmtdesc != शून्य) अणु
			strscpy(क्रमmat->name, fmtdesc->name,
				माप(क्रमmat->name));
			क्रमmat->fcc = fmtdesc->fcc;
		पूर्ण अन्यथा अणु
			dev_info(&streaming->पूर्णांकf->dev,
				 "Unknown video format %pUl\n", &buffer[5]);
			snम_लिखो(क्रमmat->name, माप(क्रमmat->name), "%pUl\n",
				&buffer[5]);
			क्रमmat->fcc = 0;
		पूर्ण

		क्रमmat->bpp = buffer[21];

		/* Some devices report a क्रमmat that करोesn't match what they
		 * really send.
		 */
		अगर (dev->quirks & UVC_QUIRK_FORCE_Y8) अणु
			अगर (क्रमmat->fcc == V4L2_PIX_FMT_YUYV) अणु
				strscpy(क्रमmat->name, "Greyscale 8-bit (Y8  )",
					माप(क्रमmat->name));
				क्रमmat->fcc = V4L2_PIX_FMT_GREY;
				क्रमmat->bpp = 8;
				width_multiplier = 2;
			पूर्ण
		पूर्ण

		/* Some devices report bpp that करोesn't match the क्रमmat. */
		अगर (dev->quirks & UVC_QUIRK_FORCE_BPP) अणु
			स्थिर काष्ठा v4l2_क्रमmat_info *info =
				v4l2_क्रमmat_info(क्रमmat->fcc);

			अगर (info) अणु
				अचिन्हित पूर्णांक भाग = info->hभाग * info->vभाग;

				n = info->bpp[0] * भाग;
				क्रम (i = 1; i < info->comp_planes; i++)
					n += info->bpp[i];

				क्रमmat->bpp = DIV_ROUND_UP(8 * n, भाग);
			पूर्ण
		पूर्ण

		अगर (buffer[2] == UVC_VS_FORMAT_UNCOMPRESSED) अणु
			ftype = UVC_VS_FRAME_UNCOMPRESSED;
		पूर्ण अन्यथा अणु
			ftype = UVC_VS_FRAME_FRAME_BASED;
			अगर (buffer[27])
				क्रमmat->flags = UVC_FMT_FLAG_COMPRESSED;
		पूर्ण
		अवरोध;

	हाल UVC_VS_FORMAT_MJPEG:
		अगर (buflen < 11) अणु
			uvc_dbg(dev, DESCR,
				"device %d videostreaming interface %d FORMAT error\n",
				dev->udev->devnum,
				alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		strscpy(क्रमmat->name, "MJPEG", माप(क्रमmat->name));
		क्रमmat->fcc = V4L2_PIX_FMT_MJPEG;
		क्रमmat->flags = UVC_FMT_FLAG_COMPRESSED;
		क्रमmat->bpp = 0;
		ftype = UVC_VS_FRAME_MJPEG;
		अवरोध;

	हाल UVC_VS_FORMAT_DV:
		अगर (buflen < 9) अणु
			uvc_dbg(dev, DESCR,
				"device %d videostreaming interface %d FORMAT error\n",
				dev->udev->devnum,
				alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		चयन (buffer[8] & 0x7f) अणु
		हाल 0:
			strscpy(क्रमmat->name, "SD-DV", माप(क्रमmat->name));
			अवरोध;
		हाल 1:
			strscpy(क्रमmat->name, "SDL-DV", माप(क्रमmat->name));
			अवरोध;
		हाल 2:
			strscpy(क्रमmat->name, "HD-DV", माप(क्रमmat->name));
			अवरोध;
		शेष:
			uvc_dbg(dev, DESCR,
				"device %d videostreaming interface %d: unknown DV format %u\n",
				dev->udev->devnum,
				alts->desc.bInterfaceNumber, buffer[8]);
			वापस -EINVAL;
		पूर्ण

		strlcat(क्रमmat->name, buffer[8] & (1 << 7) ? " 60Hz" : " 50Hz",
			माप(क्रमmat->name));

		क्रमmat->fcc = V4L2_PIX_FMT_DV;
		क्रमmat->flags = UVC_FMT_FLAG_COMPRESSED | UVC_FMT_FLAG_STREAM;
		क्रमmat->bpp = 0;
		ftype = 0;

		/* Create a dummy frame descriptor. */
		frame = &क्रमmat->frame[0];
		स_रखो(&क्रमmat->frame[0], 0, माप(क्रमmat->frame[0]));
		frame->bFrameIntervalType = 1;
		frame->dwDefaultFrameInterval = 1;
		frame->dwFrameInterval = *पूर्णांकervals;
		*(*पूर्णांकervals)++ = 1;
		क्रमmat->nframes = 1;
		अवरोध;

	हाल UVC_VS_FORMAT_MPEG2TS:
	हाल UVC_VS_FORMAT_STREAM_BASED:
		/* Not supported yet. */
	शेष:
		uvc_dbg(dev, DESCR,
			"device %d videostreaming interface %d unsupported format %u\n",
			dev->udev->devnum, alts->desc.bInterfaceNumber,
			buffer[2]);
		वापस -EINVAL;
	पूर्ण

	uvc_dbg(dev, DESCR, "Found format %s\n", क्रमmat->name);

	buflen -= buffer[0];
	buffer += buffer[0];

	/* Parse the frame descriptors. Only uncompressed, MJPEG and frame
	 * based क्रमmats have frame descriptors.
	 */
	जबतक (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE &&
	       buffer[2] == ftype) अणु
		frame = &क्रमmat->frame[क्रमmat->nframes];
		अगर (ftype != UVC_VS_FRAME_FRAME_BASED)
			n = buflen > 25 ? buffer[25] : 0;
		अन्यथा
			n = buflen > 21 ? buffer[21] : 0;

		n = n ? n : 3;

		अगर (buflen < 26 + 4*n) अणु
			uvc_dbg(dev, DESCR,
				"device %d videostreaming interface %d FRAME error\n",
				dev->udev->devnum,
				alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		frame->bFrameIndex = buffer[3];
		frame->bmCapabilities = buffer[4];
		frame->wWidth = get_unaligned_le16(&buffer[5])
			      * width_multiplier;
		frame->wHeight = get_unaligned_le16(&buffer[7]);
		frame->dwMinBitRate = get_unaligned_le32(&buffer[9]);
		frame->dwMaxBitRate = get_unaligned_le32(&buffer[13]);
		अगर (ftype != UVC_VS_FRAME_FRAME_BASED) अणु
			frame->dwMaxVideoFrameBufferSize =
				get_unaligned_le32(&buffer[17]);
			frame->dwDefaultFrameInterval =
				get_unaligned_le32(&buffer[21]);
			frame->bFrameIntervalType = buffer[25];
		पूर्ण अन्यथा अणु
			frame->dwMaxVideoFrameBufferSize = 0;
			frame->dwDefaultFrameInterval =
				get_unaligned_le32(&buffer[17]);
			frame->bFrameIntervalType = buffer[21];
		पूर्ण
		frame->dwFrameInterval = *पूर्णांकervals;

		/* Several UVC chipsets screw up dwMaxVideoFrameBufferSize
		 * completely. Observed behaviours range from setting the
		 * value to 1.1x the actual frame size to hardwiring the
		 * 16 low bits to 0. This results in a higher than necessary
		 * memory usage as well as a wrong image size inक्रमmation. For
		 * uncompressed क्रमmats this can be fixed by computing the
		 * value from the frame size.
		 */
		अगर (!(क्रमmat->flags & UVC_FMT_FLAG_COMPRESSED))
			frame->dwMaxVideoFrameBufferSize = क्रमmat->bpp
				* frame->wWidth * frame->wHeight / 8;

		/* Some bogus devices report dwMinFrameInterval equal to
		 * dwMaxFrameInterval and have dwFrameIntervalStep set to
		 * zero. Setting all null पूर्णांकervals to 1 fixes the problem and
		 * some other भागisions by zero that could happen.
		 */
		क्रम (i = 0; i < n; ++i) अणु
			पूर्णांकerval = get_unaligned_le32(&buffer[26+4*i]);
			*(*पूर्णांकervals)++ = पूर्णांकerval ? पूर्णांकerval : 1;
		पूर्ण

		/* Make sure that the शेष frame पूर्णांकerval stays between
		 * the boundaries.
		 */
		n -= frame->bFrameIntervalType ? 1 : 2;
		frame->dwDefaultFrameInterval =
			min(frame->dwFrameInterval[n],
			    max(frame->dwFrameInterval[0],
				frame->dwDefaultFrameInterval));

		अगर (dev->quirks & UVC_QUIRK_RESTRICT_FRAME_RATE) अणु
			frame->bFrameIntervalType = 1;
			frame->dwFrameInterval[0] =
				frame->dwDefaultFrameInterval;
		पूर्ण

		uvc_dbg(dev, DESCR, "- %ux%u (%u.%u fps)\n",
			frame->wWidth, frame->wHeight,
			10000000 / frame->dwDefaultFrameInterval,
			(100000000 / frame->dwDefaultFrameInterval) % 10);

		क्रमmat->nframes++;
		buflen -= buffer[0];
		buffer += buffer[0];
	पूर्ण

	अगर (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE &&
	    buffer[2] == UVC_VS_STILL_IMAGE_FRAME) अणु
		buflen -= buffer[0];
		buffer += buffer[0];
	पूर्ण

	अगर (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE &&
	    buffer[2] == UVC_VS_COLORFORMAT) अणु
		अगर (buflen < 6) अणु
			uvc_dbg(dev, DESCR,
				"device %d videostreaming interface %d COLORFORMAT error\n",
				dev->udev->devnum,
				alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		क्रमmat->colorspace = uvc_colorspace(buffer[3]);
		क्रमmat->xfer_func = uvc_xfer_func(buffer[4]);
		क्रमmat->ycbcr_enc = uvc_ycbcr_enc(buffer[5]);

		buflen -= buffer[0];
		buffer += buffer[0];
	पूर्ण

	वापस buffer - start;
पूर्ण

अटल पूर्णांक uvc_parse_streaming(काष्ठा uvc_device *dev,
	काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा uvc_streaming *streaming = शून्य;
	काष्ठा uvc_क्रमmat *क्रमmat;
	काष्ठा uvc_frame *frame;
	काष्ठा usb_host_पूर्णांकerface *alts = &पूर्णांकf->altsetting[0];
	अचिन्हित अक्षर *_buffer, *buffer = alts->extra;
	पूर्णांक _buflen, buflen = alts->extralen;
	अचिन्हित पूर्णांक nक्रमmats = 0, nframes = 0, nपूर्णांकervals = 0;
	अचिन्हित पूर्णांक size, i, n, p;
	u32 *पूर्णांकerval;
	u16 psize;
	पूर्णांक ret = -EINVAL;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceSubClass
		!= UVC_SC_VIDEOSTREAMING) अणु
		uvc_dbg(dev, DESCR,
			"device %d interface %d isn't a video streaming interface\n",
			dev->udev->devnum,
			पूर्णांकf->altsetting[0].desc.bInterfaceNumber);
		वापस -EINVAL;
	पूर्ण

	अगर (usb_driver_claim_पूर्णांकerface(&uvc_driver.driver, पूर्णांकf, dev)) अणु
		uvc_dbg(dev, DESCR,
			"device %d interface %d is already claimed\n",
			dev->udev->devnum,
			पूर्णांकf->altsetting[0].desc.bInterfaceNumber);
		वापस -EINVAL;
	पूर्ण

	streaming = uvc_stream_new(dev, पूर्णांकf);
	अगर (streaming == शून्य) अणु
		usb_driver_release_पूर्णांकerface(&uvc_driver.driver, पूर्णांकf);
		वापस -ENOMEM;
	पूर्ण

	/* The Pico iMage webcam has its class-specअगरic पूर्णांकerface descriptors
	 * after the endpoपूर्णांक descriptors.
	 */
	अगर (buflen == 0) अणु
		क्रम (i = 0; i < alts->desc.bNumEndpoपूर्णांकs; ++i) अणु
			काष्ठा usb_host_endpoपूर्णांक *ep = &alts->endpoपूर्णांक[i];

			अगर (ep->extralen == 0)
				जारी;

			अगर (ep->extralen > 2 &&
			    ep->extra[1] == USB_DT_CS_INTERFACE) अणु
				uvc_dbg(dev, DESCR,
					"trying extra data from endpoint %u\n",
					i);
				buffer = alts->endpoपूर्णांक[i].extra;
				buflen = alts->endpoपूर्णांक[i].extralen;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Skip the standard पूर्णांकerface descriptors. */
	जबतक (buflen > 2 && buffer[1] != USB_DT_CS_INTERFACE) अणु
		buflen -= buffer[0];
		buffer += buffer[0];
	पूर्ण

	अगर (buflen <= 2) अणु
		uvc_dbg(dev, DESCR,
			"no class-specific streaming interface descriptors found\n");
		जाओ error;
	पूर्ण

	/* Parse the header descriptor. */
	चयन (buffer[2]) अणु
	हाल UVC_VS_OUTPUT_HEADER:
		streaming->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		size = 9;
		अवरोध;

	हाल UVC_VS_INPUT_HEADER:
		streaming->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		size = 13;
		अवरोध;

	शेष:
		uvc_dbg(dev, DESCR,
			"device %d videostreaming interface %d HEADER descriptor not found\n",
			dev->udev->devnum, alts->desc.bInterfaceNumber);
		जाओ error;
	पूर्ण

	p = buflen >= 4 ? buffer[3] : 0;
	n = buflen >= size ? buffer[size-1] : 0;

	अगर (buflen < size + p*n) अणु
		uvc_dbg(dev, DESCR,
			"device %d videostreaming interface %d HEADER descriptor is invalid\n",
			dev->udev->devnum, alts->desc.bInterfaceNumber);
		जाओ error;
	पूर्ण

	streaming->header.bNumFormats = p;
	streaming->header.bEndpoपूर्णांकAddress = buffer[6];
	अगर (buffer[2] == UVC_VS_INPUT_HEADER) अणु
		streaming->header.bmInfo = buffer[7];
		streaming->header.bTerminalLink = buffer[8];
		streaming->header.bStillCaptureMethod = buffer[9];
		streaming->header.bTriggerSupport = buffer[10];
		streaming->header.bTriggerUsage = buffer[11];
	पूर्ण अन्यथा अणु
		streaming->header.bTerminalLink = buffer[7];
	पूर्ण
	streaming->header.bControlSize = n;

	streaming->header.bmaControls = kmemdup(&buffer[size], p * n,
						GFP_KERNEL);
	अगर (streaming->header.bmaControls == शून्य) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	buflen -= buffer[0];
	buffer += buffer[0];

	_buffer = buffer;
	_buflen = buflen;

	/* Count the क्रमmat and frame descriptors. */
	जबतक (_buflen > 2 && _buffer[1] == USB_DT_CS_INTERFACE) अणु
		चयन (_buffer[2]) अणु
		हाल UVC_VS_FORMAT_UNCOMPRESSED:
		हाल UVC_VS_FORMAT_MJPEG:
		हाल UVC_VS_FORMAT_FRAME_BASED:
			nक्रमmats++;
			अवरोध;

		हाल UVC_VS_FORMAT_DV:
			/* DV क्रमmat has no frame descriptor. We will create a
			 * dummy frame descriptor with a dummy frame पूर्णांकerval.
			 */
			nक्रमmats++;
			nframes++;
			nपूर्णांकervals++;
			अवरोध;

		हाल UVC_VS_FORMAT_MPEG2TS:
		हाल UVC_VS_FORMAT_STREAM_BASED:
			uvc_dbg(dev, DESCR,
				"device %d videostreaming interface %d FORMAT %u is not supported\n",
				dev->udev->devnum,
				alts->desc.bInterfaceNumber, _buffer[2]);
			अवरोध;

		हाल UVC_VS_FRAME_UNCOMPRESSED:
		हाल UVC_VS_FRAME_MJPEG:
			nframes++;
			अगर (_buflen > 25)
				nपूर्णांकervals += _buffer[25] ? _buffer[25] : 3;
			अवरोध;

		हाल UVC_VS_FRAME_FRAME_BASED:
			nframes++;
			अगर (_buflen > 21)
				nपूर्णांकervals += _buffer[21] ? _buffer[21] : 3;
			अवरोध;
		पूर्ण

		_buflen -= _buffer[0];
		_buffer += _buffer[0];
	पूर्ण

	अगर (nक्रमmats == 0) अणु
		uvc_dbg(dev, DESCR,
			"device %d videostreaming interface %d has no supported formats defined\n",
			dev->udev->devnum, alts->desc.bInterfaceNumber);
		जाओ error;
	पूर्ण

	size = nक्रमmats * माप(*क्रमmat) + nframes * माप(*frame)
	     + nपूर्णांकervals * माप(*पूर्णांकerval);
	क्रमmat = kzalloc(size, GFP_KERNEL);
	अगर (क्रमmat == शून्य) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	frame = (काष्ठा uvc_frame *)&क्रमmat[nक्रमmats];
	पूर्णांकerval = (u32 *)&frame[nframes];

	streaming->क्रमmat = क्रमmat;
	streaming->nक्रमmats = nक्रमmats;

	/* Parse the क्रमmat descriptors. */
	जबतक (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE) अणु
		चयन (buffer[2]) अणु
		हाल UVC_VS_FORMAT_UNCOMPRESSED:
		हाल UVC_VS_FORMAT_MJPEG:
		हाल UVC_VS_FORMAT_DV:
		हाल UVC_VS_FORMAT_FRAME_BASED:
			क्रमmat->frame = frame;
			ret = uvc_parse_क्रमmat(dev, streaming, क्रमmat,
				&पूर्णांकerval, buffer, buflen);
			अगर (ret < 0)
				जाओ error;

			frame += क्रमmat->nframes;
			क्रमmat++;

			buflen -= ret;
			buffer += ret;
			जारी;

		शेष:
			अवरोध;
		पूर्ण

		buflen -= buffer[0];
		buffer += buffer[0];
	पूर्ण

	अगर (buflen)
		uvc_dbg(dev, DESCR,
			"device %d videostreaming interface %d has %u bytes of trailing descriptor garbage\n",
			dev->udev->devnum, alts->desc.bInterfaceNumber, buflen);

	/* Parse the alternate settings to find the maximum bandwidth. */
	क्रम (i = 0; i < पूर्णांकf->num_altsetting; ++i) अणु
		काष्ठा usb_host_endpoपूर्णांक *ep;
		alts = &पूर्णांकf->altsetting[i];
		ep = uvc_find_endpoपूर्णांक(alts,
				streaming->header.bEndpoपूर्णांकAddress);
		अगर (ep == शून्य)
			जारी;

		psize = le16_to_cpu(ep->desc.wMaxPacketSize);
		psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
		अगर (psize > streaming->maxpsize)
			streaming->maxpsize = psize;
	पूर्ण

	list_add_tail(&streaming->list, &dev->streams);
	वापस 0;

error:
	usb_driver_release_पूर्णांकerface(&uvc_driver.driver, पूर्णांकf);
	uvc_stream_delete(streaming);
	वापस ret;
पूर्ण

अटल स्थिर u8 uvc_camera_guid[16] = UVC_GUID_UVC_CAMERA;
अटल स्थिर u8 uvc_gpio_guid[16] = UVC_GUID_EXT_GPIO_CONTROLLER;
अटल स्थिर u8 uvc_media_transport_input_guid[16] =
	UVC_GUID_UVC_MEDIA_TRANSPORT_INPUT;
अटल स्थिर u8 uvc_processing_guid[16] = UVC_GUID_UVC_PROCESSING;

अटल काष्ठा uvc_entity *uvc_alloc_entity(u16 type, u16 id,
		अचिन्हित पूर्णांक num_pads, अचिन्हित पूर्णांक extra_size)
अणु
	काष्ठा uvc_entity *entity;
	अचिन्हित पूर्णांक num_inमाला_दो;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक i;

	extra_size = roundup(extra_size, माप(*entity->pads));
	अगर (num_pads)
		num_inमाला_दो = type & UVC_TERM_OUTPUT ? num_pads : num_pads - 1;
	अन्यथा
		num_inमाला_दो = 0;
	size = माप(*entity) + extra_size + माप(*entity->pads) * num_pads
	     + num_inमाला_दो;
	entity = kzalloc(size, GFP_KERNEL);
	अगर (entity == शून्य)
		वापस शून्य;

	entity->id = id;
	entity->type = type;

	/*
	 * Set the GUID क्रम standard entity types. For extension units, the GUID
	 * is initialized by the caller.
	 */
	चयन (type) अणु
	हाल UVC_EXT_GPIO_UNIT:
		स_नकल(entity->guid, uvc_gpio_guid, 16);
		अवरोध;
	हाल UVC_ITT_CAMERA:
		स_नकल(entity->guid, uvc_camera_guid, 16);
		अवरोध;
	हाल UVC_ITT_MEDIA_TRANSPORT_INPUT:
		स_नकल(entity->guid, uvc_media_transport_input_guid, 16);
		अवरोध;
	हाल UVC_VC_PROCESSING_UNIT:
		स_नकल(entity->guid, uvc_processing_guid, 16);
		अवरोध;
	पूर्ण

	entity->num_links = 0;
	entity->num_pads = num_pads;
	entity->pads = ((व्योम *)(entity + 1)) + extra_size;

	क्रम (i = 0; i < num_inमाला_दो; ++i)
		entity->pads[i].flags = MEDIA_PAD_FL_SINK;
	अगर (!UVC_ENTITY_IS_OTERM(entity) && num_pads)
		entity->pads[num_pads-1].flags = MEDIA_PAD_FL_SOURCE;

	entity->bNrInPins = num_inमाला_दो;
	entity->baSourceID = (u8 *)(&entity->pads[num_pads]);

	वापस entity;
पूर्ण

/* Parse venकरोr-specअगरic extensions. */
अटल पूर्णांक uvc_parse_venकरोr_control(काष्ठा uvc_device *dev,
	स्थिर अचिन्हित अक्षर *buffer, पूर्णांक buflen)
अणु
	काष्ठा usb_device *udev = dev->udev;
	काष्ठा usb_host_पूर्णांकerface *alts = dev->पूर्णांकf->cur_altsetting;
	काष्ठा uvc_entity *unit;
	अचिन्हित पूर्णांक n, p;
	पूर्णांक handled = 0;

	चयन (le16_to_cpu(dev->udev->descriptor.idVenकरोr)) अणु
	हाल 0x046d:		/* Logitech */
		अगर (buffer[1] != 0x41 || buffer[2] != 0x01)
			अवरोध;

		/* Logitech implements several venकरोr specअगरic functions
		 * through venकरोr specअगरic extension units (LXU).
		 *
		 * The LXU descriptors are similar to XU descriptors
		 * (see "USB Device Video Class for Video Devices", section
		 * 3.7.2.6 "Extension Unit Descriptor") with the following
		 * dअगरferences:
		 *
		 * ----------------------------------------------------------
		 * 0		bLength		1	 Number
		 *	Size of this descriptor, in bytes: 24+p+n*2
		 * ----------------------------------------------------------
		 * 23+p+n	bmControlsType	N	Biपंचांगap
		 *	Inभागidual bits in the set are defined:
		 *	0: Absolute
		 *	1: Relative
		 *
		 *	This bitset is mapped exactly the same as bmControls.
		 * ----------------------------------------------------------
		 * 23+p+n*2	bReserved	1	Boolean
		 * ----------------------------------------------------------
		 * 24+p+n*2	iExtension	1	Index
		 *	Index of a string descriptor that describes this
		 *	extension unit.
		 * ----------------------------------------------------------
		 */
		p = buflen >= 22 ? buffer[21] : 0;
		n = buflen >= 25 + p ? buffer[22+p] : 0;

		अगर (buflen < 25 + p + 2*n) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d EXTENSION_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			अवरोध;
		पूर्ण

		unit = uvc_alloc_entity(UVC_VC_EXTENSION_UNIT, buffer[3],
					p + 1, 2*n);
		अगर (unit == शून्य)
			वापस -ENOMEM;

		स_नकल(unit->guid, &buffer[4], 16);
		unit->extension.bNumControls = buffer[20];
		स_नकल(unit->baSourceID, &buffer[22], p);
		unit->extension.bControlSize = buffer[22+p];
		unit->extension.bmControls = (u8 *)unit + माप(*unit);
		unit->extension.bmControlsType = (u8 *)unit + माप(*unit)
					       + n;
		स_नकल(unit->extension.bmControls, &buffer[23+p], 2*n);

		अगर (buffer[24+p+2*n] != 0)
			usb_string(udev, buffer[24+p+2*n], unit->name,
				   माप(unit->name));
		अन्यथा
			प्र_लिखो(unit->name, "Extension %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		handled = 1;
		अवरोध;
	पूर्ण

	वापस handled;
पूर्ण

अटल पूर्णांक uvc_parse_standard_control(काष्ठा uvc_device *dev,
	स्थिर अचिन्हित अक्षर *buffer, पूर्णांक buflen)
अणु
	काष्ठा usb_device *udev = dev->udev;
	काष्ठा uvc_entity *unit, *term;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *alts = dev->पूर्णांकf->cur_altsetting;
	अचिन्हित पूर्णांक i, n, p, len;
	u16 type;

	चयन (buffer[2]) अणु
	हाल UVC_VC_HEADER:
		n = buflen >= 12 ? buffer[11] : 0;

		अगर (buflen < 12 + n) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d HEADER error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		dev->uvc_version = get_unaligned_le16(&buffer[3]);
		dev->घड़ी_frequency = get_unaligned_le32(&buffer[7]);

		/* Parse all USB Video Streaming पूर्णांकerfaces. */
		क्रम (i = 0; i < n; ++i) अणु
			पूर्णांकf = usb_अगरnum_to_अगर(udev, buffer[12+i]);
			अगर (पूर्णांकf == शून्य) अणु
				uvc_dbg(dev, DESCR,
					"device %d interface %d doesn't exists\n",
					udev->devnum, i);
				जारी;
			पूर्ण

			uvc_parse_streaming(dev, पूर्णांकf);
		पूर्ण
		अवरोध;

	हाल UVC_VC_INPUT_TERMINAL:
		अगर (buflen < 8) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d INPUT_TERMINAL error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		/*
		 * Reject invalid terminal types that would cause issues:
		 *
		 * - The high byte must be non-zero, otherwise it would be
		 *   confused with a unit.
		 *
		 * - Bit 15 must be 0, as we use it पूर्णांकernally as a terminal
		 *   direction flag.
		 *
		 * Other unknown types are accepted.
		 */
		type = get_unaligned_le16(&buffer[4]);
		अगर ((type & 0x7f00) == 0 || (type & 0x8000) != 0) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d INPUT_TERMINAL %d has invalid type 0x%04x, skipping\n",
				udev->devnum, alts->desc.bInterfaceNumber,
				buffer[3], type);
			वापस 0;
		पूर्ण

		n = 0;
		p = 0;
		len = 8;

		अगर (type == UVC_ITT_CAMERA) अणु
			n = buflen >= 15 ? buffer[14] : 0;
			len = 15;

		पूर्ण अन्यथा अगर (type == UVC_ITT_MEDIA_TRANSPORT_INPUT) अणु
			n = buflen >= 9 ? buffer[8] : 0;
			p = buflen >= 10 + n ? buffer[9+n] : 0;
			len = 10;
		पूर्ण

		अगर (buflen < len + n + p) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d INPUT_TERMINAL error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		term = uvc_alloc_entity(type | UVC_TERM_INPUT, buffer[3],
					1, n + p);
		अगर (term == शून्य)
			वापस -ENOMEM;

		अगर (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA) अणु
			term->camera.bControlSize = n;
			term->camera.bmControls = (u8 *)term + माप(*term);
			term->camera.wObjectiveFocalLengthMin =
				get_unaligned_le16(&buffer[8]);
			term->camera.wObjectiveFocalLengthMax =
				get_unaligned_le16(&buffer[10]);
			term->camera.wOcularFocalLength =
				get_unaligned_le16(&buffer[12]);
			स_नकल(term->camera.bmControls, &buffer[15], n);
		पूर्ण अन्यथा अगर (UVC_ENTITY_TYPE(term) ==
			   UVC_ITT_MEDIA_TRANSPORT_INPUT) अणु
			term->media.bControlSize = n;
			term->media.bmControls = (u8 *)term + माप(*term);
			term->media.bTransportModeSize = p;
			term->media.bmTransportModes = (u8 *)term
						     + माप(*term) + n;
			स_नकल(term->media.bmControls, &buffer[9], n);
			स_नकल(term->media.bmTransportModes, &buffer[10+n], p);
		पूर्ण

		अगर (buffer[7] != 0)
			usb_string(udev, buffer[7], term->name,
				   माप(term->name));
		अन्यथा अगर (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA)
			प्र_लिखो(term->name, "Camera %u", buffer[3]);
		अन्यथा अगर (UVC_ENTITY_TYPE(term) == UVC_ITT_MEDIA_TRANSPORT_INPUT)
			प्र_लिखो(term->name, "Media %u", buffer[3]);
		अन्यथा
			प्र_लिखो(term->name, "Input %u", buffer[3]);

		list_add_tail(&term->list, &dev->entities);
		अवरोध;

	हाल UVC_VC_OUTPUT_TERMINAL:
		अगर (buflen < 9) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d OUTPUT_TERMINAL error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		/* Make sure the terminal type MSB is not null, otherwise it
		 * could be confused with a unit.
		 */
		type = get_unaligned_le16(&buffer[4]);
		अगर ((type & 0xff00) == 0) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d OUTPUT_TERMINAL %d has invalid type 0x%04x, skipping\n",
				udev->devnum, alts->desc.bInterfaceNumber,
				buffer[3], type);
			वापस 0;
		पूर्ण

		term = uvc_alloc_entity(type | UVC_TERM_OUTPUT, buffer[3],
					1, 0);
		अगर (term == शून्य)
			वापस -ENOMEM;

		स_नकल(term->baSourceID, &buffer[7], 1);

		अगर (buffer[8] != 0)
			usb_string(udev, buffer[8], term->name,
				   माप(term->name));
		अन्यथा
			प्र_लिखो(term->name, "Output %u", buffer[3]);

		list_add_tail(&term->list, &dev->entities);
		अवरोध;

	हाल UVC_VC_SELECTOR_UNIT:
		p = buflen >= 5 ? buffer[4] : 0;

		अगर (buflen < 5 || buflen < 6 + p) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d SELECTOR_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		unit = uvc_alloc_entity(buffer[2], buffer[3], p + 1, 0);
		अगर (unit == शून्य)
			वापस -ENOMEM;

		स_नकल(unit->baSourceID, &buffer[5], p);

		अगर (buffer[5+p] != 0)
			usb_string(udev, buffer[5+p], unit->name,
				   माप(unit->name));
		अन्यथा
			प्र_लिखो(unit->name, "Selector %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		अवरोध;

	हाल UVC_VC_PROCESSING_UNIT:
		n = buflen >= 8 ? buffer[7] : 0;
		p = dev->uvc_version >= 0x0110 ? 10 : 9;

		अगर (buflen < p + n) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d PROCESSING_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		unit = uvc_alloc_entity(buffer[2], buffer[3], 2, n);
		अगर (unit == शून्य)
			वापस -ENOMEM;

		स_नकल(unit->baSourceID, &buffer[4], 1);
		unit->processing.wMaxMultiplier =
			get_unaligned_le16(&buffer[5]);
		unit->processing.bControlSize = buffer[7];
		unit->processing.bmControls = (u8 *)unit + माप(*unit);
		स_नकल(unit->processing.bmControls, &buffer[8], n);
		अगर (dev->uvc_version >= 0x0110)
			unit->processing.bmVideoStandards = buffer[9+n];

		अगर (buffer[8+n] != 0)
			usb_string(udev, buffer[8+n], unit->name,
				   माप(unit->name));
		अन्यथा
			प्र_लिखो(unit->name, "Processing %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		अवरोध;

	हाल UVC_VC_EXTENSION_UNIT:
		p = buflen >= 22 ? buffer[21] : 0;
		n = buflen >= 24 + p ? buffer[22+p] : 0;

		अगर (buflen < 24 + p + n) अणु
			uvc_dbg(dev, DESCR,
				"device %d videocontrol interface %d EXTENSION_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			वापस -EINVAL;
		पूर्ण

		unit = uvc_alloc_entity(buffer[2], buffer[3], p + 1, n);
		अगर (unit == शून्य)
			वापस -ENOMEM;

		स_नकल(unit->guid, &buffer[4], 16);
		unit->extension.bNumControls = buffer[20];
		स_नकल(unit->baSourceID, &buffer[22], p);
		unit->extension.bControlSize = buffer[22+p];
		unit->extension.bmControls = (u8 *)unit + माप(*unit);
		स_नकल(unit->extension.bmControls, &buffer[23+p], n);

		अगर (buffer[23+p+n] != 0)
			usb_string(udev, buffer[23+p+n], unit->name,
				   माप(unit->name));
		अन्यथा
			प्र_लिखो(unit->name, "Extension %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		अवरोध;

	शेष:
		uvc_dbg(dev, DESCR,
			"Found an unknown CS_INTERFACE descriptor (%u)\n",
			buffer[2]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_parse_control(काष्ठा uvc_device *dev)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts = dev->पूर्णांकf->cur_altsetting;
	अचिन्हित अक्षर *buffer = alts->extra;
	पूर्णांक buflen = alts->extralen;
	पूर्णांक ret;

	/* Parse the शेष alternate setting only, as the UVC specअगरication
	 * defines a single alternate setting, the शेष alternate setting
	 * zero.
	 */

	जबतक (buflen > 2) अणु
		अगर (uvc_parse_venकरोr_control(dev, buffer, buflen) ||
		    buffer[1] != USB_DT_CS_INTERFACE)
			जाओ next_descriptor;

		अगर ((ret = uvc_parse_standard_control(dev, buffer, buflen)) < 0)
			वापस ret;

next_descriptor:
		buflen -= buffer[0];
		buffer += buffer[0];
	पूर्ण

	/* Check अगर the optional status endpoपूर्णांक is present. Built-in iSight
	 * webcams have an पूर्णांकerrupt endpoपूर्णांक but spit proprietary data that
	 * करोn't conform to the UVC status endpoint messages. Don't try to
	 * handle the पूर्णांकerrupt endpoपूर्णांक क्रम those cameras.
	 */
	अगर (alts->desc.bNumEndpoपूर्णांकs == 1 &&
	    !(dev->quirks & UVC_QUIRK_BUILTIN_ISIGHT)) अणु
		काष्ठा usb_host_endpoपूर्णांक *ep = &alts->endpoपूर्णांक[0];
		काष्ठा usb_endpoपूर्णांक_descriptor *desc = &ep->desc;

		अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(desc) &&
		    le16_to_cpu(desc->wMaxPacketSize) >= 8 &&
		    desc->bInterval != 0) अणु
			uvc_dbg(dev, DESCR,
				"Found a Status endpoint (addr %02x)\n",
				desc->bEndpoपूर्णांकAddress);
			dev->पूर्णांक_ep = ep;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Privacy GPIO
 */

अटल व्योम uvc_gpio_event(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_entity *unit = dev->gpio_unit;
	काष्ठा uvc_video_chain *chain;
	u8 new_val;

	अगर (!unit)
		वापस;

	new_val = gpiod_get_value_cansleep(unit->gpio.gpio_privacy);

	/* GPIO entities are always on the first chain. */
	chain = list_first_entry(&dev->chains, काष्ठा uvc_video_chain, list);
	uvc_ctrl_status_event(chain, unit->controls, &new_val);
पूर्ण

अटल पूर्णांक uvc_gpio_get_cur(काष्ठा uvc_device *dev, काष्ठा uvc_entity *entity,
			    u8 cs, व्योम *data, u16 size)
अणु
	अगर (cs != UVC_CT_PRIVACY_CONTROL || size < 1)
		वापस -EINVAL;

	*(u8 *)data = gpiod_get_value_cansleep(entity->gpio.gpio_privacy);

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_gpio_get_info(काष्ठा uvc_device *dev, काष्ठा uvc_entity *entity,
			     u8 cs, u8 *caps)
अणु
	अगर (cs != UVC_CT_PRIVACY_CONTROL)
		वापस -EINVAL;

	*caps = UVC_CONTROL_CAP_GET | UVC_CONTROL_CAP_AUTOUPDATE;
	वापस 0;
पूर्ण

अटल irqवापस_t uvc_gpio_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा uvc_device *dev = data;

	uvc_gpio_event(dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uvc_gpio_parse(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_entity *unit;
	काष्ठा gpio_desc *gpio_privacy;
	पूर्णांक irq;

	gpio_privacy = devm_gpiod_get_optional(&dev->udev->dev, "privacy",
					       GPIOD_IN);
	अगर (IS_ERR_OR_शून्य(gpio_privacy))
		वापस PTR_ERR_OR_ZERO(gpio_privacy);

	unit = uvc_alloc_entity(UVC_EXT_GPIO_UNIT, UVC_EXT_GPIO_UNIT_ID, 0, 1);
	अगर (!unit)
		वापस -ENOMEM;

	irq = gpiod_to_irq(gpio_privacy);
	अगर (irq < 0) अणु
		अगर (irq != EPROBE_DEFER)
			dev_err(&dev->udev->dev,
				"No IRQ for privacy GPIO (%d)\n", irq);
		वापस irq;
	पूर्ण

	unit->gpio.gpio_privacy = gpio_privacy;
	unit->gpio.irq = irq;
	unit->gpio.bControlSize = 1;
	unit->gpio.bmControls = (u8 *)unit + माप(*unit);
	unit->gpio.bmControls[0] = 1;
	unit->get_cur = uvc_gpio_get_cur;
	unit->get_info = uvc_gpio_get_info;
	strscpy(unit->name, "GPIO", माप(unit->name));

	list_add_tail(&unit->list, &dev->entities);

	dev->gpio_unit = unit;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_gpio_init_irq(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_entity *unit = dev->gpio_unit;

	अगर (!unit || unit->gpio.irq < 0)
		वापस 0;

	वापस devm_request_thपढ़ोed_irq(&dev->udev->dev, unit->gpio.irq, शून्य,
					 uvc_gpio_irq,
					 IRQF_ONESHOT | IRQF_TRIGGER_FALLING |
					 IRQF_TRIGGER_RISING,
					 "uvc_privacy_gpio", dev);
पूर्ण

/* ------------------------------------------------------------------------
 * UVC device scan
 */

/*
 * Scan the UVC descriptors to locate a chain starting at an Output Terminal
 * and containing the following units:
 *
 * - one or more Output Terminals (USB Streaming or Display)
 * - zero or one Processing Unit
 * - zero, one or more single-input Selector Units
 * - zero or one multiple-input Selector Units, provided all inमाला_दो are
 *   connected to input terminals
 * - zero, one or mode single-input Extension Units
 * - one or more Input Terminals (Camera, External or USB Streaming)
 *
 * The terminal and units must match on of the following काष्ठाures:
 *
 * ITT_*(0) -> +---------+    +---------+    +---------+ -> TT_STREAMING(0)
 * ...         | SUअणु0,1पूर्ण | -> | PUअणु0,1पूर्ण | -> | XUअणु0,nपूर्ण |    ...
 * ITT_*(n) -> +---------+    +---------+    +---------+ -> TT_STREAMING(n)
 *
 *                 +---------+    +---------+ -> OTT_*(0)
 * TT_STREAMING -> | PUअणु0,1पूर्ण | -> | XUअणु0,nपूर्ण |    ...
 *                 +---------+    +---------+ -> OTT_*(n)
 *
 * The Processing Unit and Extension Units can be in any order. Additional
 * Extension Units connected to the मुख्य chain as single-unit branches are
 * also supported. Single-input Selector Units are ignored.
 */
अटल पूर्णांक uvc_scan_chain_entity(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_entity *entity)
अणु
	चयन (UVC_ENTITY_TYPE(entity)) अणु
	हाल UVC_VC_EXTENSION_UNIT:
		uvc_dbg_cont(PROBE, " <- XU %d", entity->id);

		अगर (entity->bNrInPins != 1) अणु
			uvc_dbg(chain->dev, DESCR,
				"Extension unit %d has more than 1 input pin\n",
				entity->id);
			वापस -1;
		पूर्ण

		अवरोध;

	हाल UVC_VC_PROCESSING_UNIT:
		uvc_dbg_cont(PROBE, " <- PU %d", entity->id);

		अगर (chain->processing != शून्य) अणु
			uvc_dbg(chain->dev, DESCR,
				"Found multiple Processing Units in chain\n");
			वापस -1;
		पूर्ण

		chain->processing = entity;
		अवरोध;

	हाल UVC_VC_SELECTOR_UNIT:
		uvc_dbg_cont(PROBE, " <- SU %d", entity->id);

		/* Single-input selector units are ignored. */
		अगर (entity->bNrInPins == 1)
			अवरोध;

		अगर (chain->selector != शून्य) अणु
			uvc_dbg(chain->dev, DESCR,
				"Found multiple Selector Units in chain\n");
			वापस -1;
		पूर्ण

		chain->selector = entity;
		अवरोध;

	हाल UVC_ITT_VENDOR_SPECIFIC:
	हाल UVC_ITT_CAMERA:
	हाल UVC_ITT_MEDIA_TRANSPORT_INPUT:
		uvc_dbg_cont(PROBE, " <- IT %d\n", entity->id);

		अवरोध;

	हाल UVC_OTT_VENDOR_SPECIFIC:
	हाल UVC_OTT_DISPLAY:
	हाल UVC_OTT_MEDIA_TRANSPORT_OUTPUT:
		uvc_dbg_cont(PROBE, " OT %d", entity->id);

		अवरोध;

	हाल UVC_TT_STREAMING:
		अगर (UVC_ENTITY_IS_ITERM(entity))
			uvc_dbg_cont(PROBE, " <- IT %d\n", entity->id);
		अन्यथा
			uvc_dbg_cont(PROBE, " OT %d", entity->id);

		अवरोध;

	शेष:
		uvc_dbg(chain->dev, DESCR,
			"Unsupported entity type 0x%04x found in chain\n",
			UVC_ENTITY_TYPE(entity));
		वापस -1;
	पूर्ण

	list_add_tail(&entity->chain, &chain->entities);
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_scan_chain_क्रमward(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_entity *entity, काष्ठा uvc_entity *prev)
अणु
	काष्ठा uvc_entity *क्रमward;
	पूर्णांक found;

	/* Forward scan */
	क्रमward = शून्य;
	found = 0;

	जबतक (1) अणु
		क्रमward = uvc_entity_by_reference(chain->dev, entity->id,
			क्रमward);
		अगर (क्रमward == शून्य)
			अवरोध;
		अगर (क्रमward == prev)
			जारी;
		अगर (क्रमward->chain.next || क्रमward->chain.prev) अणु
			uvc_dbg(chain->dev, DESCR,
				"Found reference to entity %d already in chain\n",
				क्रमward->id);
			वापस -EINVAL;
		पूर्ण

		चयन (UVC_ENTITY_TYPE(क्रमward)) अणु
		हाल UVC_VC_EXTENSION_UNIT:
			अगर (क्रमward->bNrInPins != 1) अणु
				uvc_dbg(chain->dev, DESCR,
					"Extension unit %d has more than 1 input pin\n",
					क्रमward->id);
				वापस -EINVAL;
			पूर्ण

			/*
			 * Some devices reference an output terminal as the
			 * source of extension units. This is incorrect, as
			 * output terminals only have an input pin, and thus
			 * can't be connected to any entity in the क्रमward
			 * direction. The resulting topology would cause issues
			 * when रेजिस्टरing the media controller graph. To
			 * aव्योम this problem, connect the extension unit to
			 * the source of the output terminal instead.
			 */
			अगर (UVC_ENTITY_IS_OTERM(entity)) अणु
				काष्ठा uvc_entity *source;

				source = uvc_entity_by_id(chain->dev,
							  entity->baSourceID[0]);
				अगर (!source) अणु
					uvc_dbg(chain->dev, DESCR,
						"Can't connect extension unit %u in chain\n",
						क्रमward->id);
					अवरोध;
				पूर्ण

				क्रमward->baSourceID[0] = source->id;
			पूर्ण

			list_add_tail(&क्रमward->chain, &chain->entities);
			अगर (!found)
				uvc_dbg_cont(PROBE, " (->");

			uvc_dbg_cont(PROBE, " XU %d", क्रमward->id);
			found = 1;
			अवरोध;

		हाल UVC_OTT_VENDOR_SPECIFIC:
		हाल UVC_OTT_DISPLAY:
		हाल UVC_OTT_MEDIA_TRANSPORT_OUTPUT:
		हाल UVC_TT_STREAMING:
			अगर (UVC_ENTITY_IS_ITERM(क्रमward)) अणु
				uvc_dbg(chain->dev, DESCR,
					"Unsupported input terminal %u\n",
					क्रमward->id);
				वापस -EINVAL;
			पूर्ण

			अगर (UVC_ENTITY_IS_OTERM(entity)) अणु
				uvc_dbg(chain->dev, DESCR,
					"Unsupported connection between output terminals %u and %u\n",
					entity->id, क्रमward->id);
				अवरोध;
			पूर्ण

			list_add_tail(&क्रमward->chain, &chain->entities);
			अगर (!found)
				uvc_dbg_cont(PROBE, " (->");

			uvc_dbg_cont(PROBE, " OT %d", क्रमward->id);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found)
		uvc_dbg_cont(PROBE, ")");

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_scan_chain_backward(काष्ठा uvc_video_chain *chain,
	काष्ठा uvc_entity **_entity)
अणु
	काष्ठा uvc_entity *entity = *_entity;
	काष्ठा uvc_entity *term;
	पूर्णांक id = -EINVAL, i;

	चयन (UVC_ENTITY_TYPE(entity)) अणु
	हाल UVC_VC_EXTENSION_UNIT:
	हाल UVC_VC_PROCESSING_UNIT:
		id = entity->baSourceID[0];
		अवरोध;

	हाल UVC_VC_SELECTOR_UNIT:
		/* Single-input selector units are ignored. */
		अगर (entity->bNrInPins == 1) अणु
			id = entity->baSourceID[0];
			अवरोध;
		पूर्ण

		uvc_dbg_cont(PROBE, " <- IT");

		chain->selector = entity;
		क्रम (i = 0; i < entity->bNrInPins; ++i) अणु
			id = entity->baSourceID[i];
			term = uvc_entity_by_id(chain->dev, id);
			अगर (term == शून्य || !UVC_ENTITY_IS_ITERM(term)) अणु
				uvc_dbg(chain->dev, DESCR,
					"Selector unit %d input %d isn't connected to an input terminal\n",
					entity->id, i);
				वापस -1;
			पूर्ण

			अगर (term->chain.next || term->chain.prev) अणु
				uvc_dbg(chain->dev, DESCR,
					"Found reference to entity %d already in chain\n",
					term->id);
				वापस -EINVAL;
			पूर्ण

			uvc_dbg_cont(PROBE, " %d", term->id);

			list_add_tail(&term->chain, &chain->entities);
			uvc_scan_chain_क्रमward(chain, term, entity);
		पूर्ण

		uvc_dbg_cont(PROBE, "\n");

		id = 0;
		अवरोध;

	हाल UVC_ITT_VENDOR_SPECIFIC:
	हाल UVC_ITT_CAMERA:
	हाल UVC_ITT_MEDIA_TRANSPORT_INPUT:
	हाल UVC_OTT_VENDOR_SPECIFIC:
	हाल UVC_OTT_DISPLAY:
	हाल UVC_OTT_MEDIA_TRANSPORT_OUTPUT:
	हाल UVC_TT_STREAMING:
		id = UVC_ENTITY_IS_OTERM(entity) ? entity->baSourceID[0] : 0;
		अवरोध;
	पूर्ण

	अगर (id <= 0) अणु
		*_entity = शून्य;
		वापस id;
	पूर्ण

	entity = uvc_entity_by_id(chain->dev, id);
	अगर (entity == शून्य) अणु
		uvc_dbg(chain->dev, DESCR,
			"Found reference to unknown entity %d\n", id);
		वापस -EINVAL;
	पूर्ण

	*_entity = entity;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_scan_chain(काष्ठा uvc_video_chain *chain,
			  काष्ठा uvc_entity *term)
अणु
	काष्ठा uvc_entity *entity, *prev;

	uvc_dbg(chain->dev, PROBE, "Scanning UVC chain:");

	entity = term;
	prev = शून्य;

	जबतक (entity != शून्य) अणु
		/* Entity must not be part of an existing chain */
		अगर (entity->chain.next || entity->chain.prev) अणु
			uvc_dbg(chain->dev, DESCR,
				"Found reference to entity %d already in chain\n",
				entity->id);
			वापस -EINVAL;
		पूर्ण

		/* Process entity */
		अगर (uvc_scan_chain_entity(chain, entity) < 0)
			वापस -EINVAL;

		/* Forward scan */
		अगर (uvc_scan_chain_क्रमward(chain, entity, prev) < 0)
			वापस -EINVAL;

		/* Backward scan */
		prev = entity;
		अगर (uvc_scan_chain_backward(chain, &entity) < 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक uvc_prपूर्णांक_terms(काष्ठा list_head *terms, u16 dir,
		अक्षर *buffer)
अणु
	काष्ठा uvc_entity *term;
	अचिन्हित पूर्णांक nterms = 0;
	अक्षर *p = buffer;

	list_क्रम_each_entry(term, terms, chain) अणु
		अगर (!UVC_ENTITY_IS_TERM(term) ||
		    UVC_TERM_सूचीECTION(term) != dir)
			जारी;

		अगर (nterms)
			p += प्र_लिखो(p, ",");
		अगर (++nterms >= 4) अणु
			p += प्र_लिखो(p, "...");
			अवरोध;
		पूर्ण
		p += प्र_लिखो(p, "%u", term->id);
	पूर्ण

	वापस p - buffer;
पूर्ण

अटल स्थिर अक्षर *uvc_prपूर्णांक_chain(काष्ठा uvc_video_chain *chain)
अणु
	अटल अक्षर buffer[43];
	अक्षर *p = buffer;

	p += uvc_prपूर्णांक_terms(&chain->entities, UVC_TERM_INPUT, p);
	p += प्र_लिखो(p, " -> ");
	uvc_prपूर्णांक_terms(&chain->entities, UVC_TERM_OUTPUT, p);

	वापस buffer;
पूर्ण

अटल काष्ठा uvc_video_chain *uvc_alloc_chain(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_video_chain *chain;

	chain = kzalloc(माप(*chain), GFP_KERNEL);
	अगर (chain == शून्य)
		वापस शून्य;

	INIT_LIST_HEAD(&chain->entities);
	mutex_init(&chain->ctrl_mutex);
	chain->dev = dev;
	v4l2_prio_init(&chain->prio);

	वापस chain;
पूर्ण

/*
 * Fallback heuristic क्रम devices that करोn't connect units and terminals in a
 * valid chain.
 *
 * Some devices have invalid baSourceID references, causing uvc_scan_chain()
 * to fail, but अगर we just take the entities we can find and put them together
 * in the most sensible chain we can think of, turns out they करो work anyway.
 * Note: This heuristic assumes there is a single chain.
 *
 * At the समय of writing, devices known to have such a broken chain are
 *  - Acer Integrated Camera (5986:055a)
 *  - Realtek rtl157a7 (0bda:57a7)
 */
अटल पूर्णांक uvc_scan_fallback(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_video_chain *chain;
	काष्ठा uvc_entity *iterm = शून्य;
	काष्ठा uvc_entity *oterm = शून्य;
	काष्ठा uvc_entity *entity;
	काष्ठा uvc_entity *prev;

	/*
	 * Start by locating the input and output terminals. We only support
	 * devices with exactly one of each क्रम now.
	 */
	list_क्रम_each_entry(entity, &dev->entities, list) अणु
		अगर (UVC_ENTITY_IS_ITERM(entity)) अणु
			अगर (iterm)
				वापस -EINVAL;
			iterm = entity;
		पूर्ण

		अगर (UVC_ENTITY_IS_OTERM(entity)) अणु
			अगर (oterm)
				वापस -EINVAL;
			oterm = entity;
		पूर्ण
	पूर्ण

	अगर (iterm == शून्य || oterm == शून्य)
		वापस -EINVAL;

	/* Allocate the chain and fill it. */
	chain = uvc_alloc_chain(dev);
	अगर (chain == शून्य)
		वापस -ENOMEM;

	अगर (uvc_scan_chain_entity(chain, oterm) < 0)
		जाओ error;

	prev = oterm;

	/*
	 * Add all Processing and Extension Units with two pads. The order
	 * करोesn't matter much, use reverse list traversal to connect units in
	 * UVC descriptor order as we build the chain from output to input. This
	 * leads to units appearing in the order meant by the manufacturer क्रम
	 * the cameras known to require this heuristic.
	 */
	list_क्रम_each_entry_reverse(entity, &dev->entities, list) अणु
		अगर (entity->type != UVC_VC_PROCESSING_UNIT &&
		    entity->type != UVC_VC_EXTENSION_UNIT)
			जारी;

		अगर (entity->num_pads != 2)
			जारी;

		अगर (uvc_scan_chain_entity(chain, entity) < 0)
			जाओ error;

		prev->baSourceID[0] = entity->id;
		prev = entity;
	पूर्ण

	अगर (uvc_scan_chain_entity(chain, iterm) < 0)
		जाओ error;

	prev->baSourceID[0] = iterm->id;

	list_add_tail(&chain->list, &dev->chains);

	uvc_dbg(dev, PROBE, "Found a video chain by fallback heuristic (%s)\n",
		uvc_prपूर्णांक_chain(chain));

	वापस 0;

error:
	kमुक्त(chain);
	वापस -EINVAL;
पूर्ण

/*
 * Scan the device क्रम video chains and रेजिस्टर video devices.
 *
 * Chains are scanned starting at their output terminals and walked backwards.
 */
अटल पूर्णांक uvc_scan_device(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_video_chain *chain;
	काष्ठा uvc_entity *term;

	list_क्रम_each_entry(term, &dev->entities, list) अणु
		अगर (!UVC_ENTITY_IS_OTERM(term))
			जारी;

		/* If the terminal is alपढ़ोy included in a chain, skip it.
		 * This can happen क्रम chains that have multiple output
		 * terminals, where all output terminals beside the first one
		 * will be inserted in the chain in क्रमward scans.
		 */
		अगर (term->chain.next || term->chain.prev)
			जारी;

		chain = uvc_alloc_chain(dev);
		अगर (chain == शून्य)
			वापस -ENOMEM;

		term->flags |= UVC_ENTITY_FLAG_DEFAULT;

		अगर (uvc_scan_chain(chain, term) < 0) अणु
			kमुक्त(chain);
			जारी;
		पूर्ण

		uvc_dbg(dev, PROBE, "Found a valid video chain (%s)\n",
			uvc_prपूर्णांक_chain(chain));

		list_add_tail(&chain->list, &dev->chains);
	पूर्ण

	अगर (list_empty(&dev->chains))
		uvc_scan_fallback(dev);

	अगर (list_empty(&dev->chains)) अणु
		dev_info(&dev->udev->dev, "No valid video chain found.\n");
		वापस -1;
	पूर्ण

	/* Add GPIO entity to the first chain. */
	अगर (dev->gpio_unit) अणु
		chain = list_first_entry(&dev->chains,
					 काष्ठा uvc_video_chain, list);
		list_add_tail(&dev->gpio_unit->chain, &chain->entities);
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------
 * Video device registration and unregistration
 */

/*
 * Delete the UVC device.
 *
 * Called by the kernel when the last reference to the uvc_device काष्ठाure
 * is released.
 *
 * As this function is called after or during disconnect(), all URBs have
 * alपढ़ोy been cancelled by the USB core. There is no need to समाप्त the
 * पूर्णांकerrupt URB manually.
 */
अटल व्योम uvc_delete(काष्ठा kref *kref)
अणु
	काष्ठा uvc_device *dev = container_of(kref, काष्ठा uvc_device, ref);
	काष्ठा list_head *p, *n;

	uvc_status_cleanup(dev);
	uvc_ctrl_cleanup_device(dev);

	usb_put_पूर्णांकf(dev->पूर्णांकf);
	usb_put_dev(dev->udev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	media_device_cleanup(&dev->mdev);
#पूर्ण_अगर

	list_क्रम_each_safe(p, n, &dev->chains) अणु
		काष्ठा uvc_video_chain *chain;
		chain = list_entry(p, काष्ठा uvc_video_chain, list);
		kमुक्त(chain);
	पूर्ण

	list_क्रम_each_safe(p, n, &dev->entities) अणु
		काष्ठा uvc_entity *entity;
		entity = list_entry(p, काष्ठा uvc_entity, list);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		uvc_mc_cleanup_entity(entity);
#पूर्ण_अगर
		kमुक्त(entity);
	पूर्ण

	list_क्रम_each_safe(p, n, &dev->streams) अणु
		काष्ठा uvc_streaming *streaming;
		streaming = list_entry(p, काष्ठा uvc_streaming, list);
		usb_driver_release_पूर्णांकerface(&uvc_driver.driver,
			streaming->पूर्णांकf);
		uvc_stream_delete(streaming);
	पूर्ण

	kमुक्त(dev);
पूर्ण

अटल व्योम uvc_release(काष्ठा video_device *vdev)
अणु
	काष्ठा uvc_streaming *stream = video_get_drvdata(vdev);
	काष्ठा uvc_device *dev = stream->dev;

	kref_put(&dev->ref, uvc_delete);
पूर्ण

/*
 * Unरेजिस्टर the video devices.
 */
अटल व्योम uvc_unरेजिस्टर_video(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_streaming *stream;

	list_क्रम_each_entry(stream, &dev->streams, list) अणु
		अगर (!video_is_रेजिस्टरed(&stream->vdev))
			जारी;

		video_unरेजिस्टर_device(&stream->vdev);
		video_unरेजिस्टर_device(&stream->meta.vdev);

		uvc_debugfs_cleanup_stream(stream);
	पूर्ण

	uvc_status_unरेजिस्टर(dev);

	अगर (dev->vdev.dev)
		v4l2_device_unरेजिस्टर(&dev->vdev);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	अगर (media_devnode_is_रेजिस्टरed(dev->mdev.devnode))
		media_device_unरेजिस्टर(&dev->mdev);
#पूर्ण_अगर
पूर्ण

पूर्णांक uvc_रेजिस्टर_video_device(काष्ठा uvc_device *dev,
			      काष्ठा uvc_streaming *stream,
			      काष्ठा video_device *vdev,
			      काष्ठा uvc_video_queue *queue,
			      क्रमागत v4l2_buf_type type,
			      स्थिर काष्ठा v4l2_file_operations *fops,
			      स्थिर काष्ठा v4l2_ioctl_ops *ioctl_ops)
अणु
	पूर्णांक ret;

	/* Initialize the video buffers queue. */
	ret = uvc_queue_init(queue, type, !uvc_no_drop_param);
	अगर (ret)
		वापस ret;

	/* Register the device with V4L. */

	/*
	 * We alपढ़ोy hold a reference to dev->udev. The video device will be
	 * unरेजिस्टरed beक्रमe the reference is released, so we करोn't need to
	 * get another one.
	 */
	vdev->v4l2_dev = &dev->vdev;
	vdev->fops = fops;
	vdev->ioctl_ops = ioctl_ops;
	vdev->release = uvc_release;
	vdev->prio = &stream->chain->prio;
	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		vdev->vfl_dir = VFL_सूची_TX;
	अन्यथा
		vdev->vfl_dir = VFL_सूची_RX;

	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	शेष:
		vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		vdev->device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;
		अवरोध;
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		vdev->device_caps = V4L2_CAP_META_CAPTURE | V4L2_CAP_STREAMING;
		अवरोध;
	पूर्ण

	strscpy(vdev->name, dev->name, माप(vdev->name));

	/*
	 * Set the driver data beक्रमe calling video_रेजिस्टर_device, otherwise
	 * the file खोलो() handler might race us.
	 */
	video_set_drvdata(vdev, stream);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		dev_err(&stream->पूर्णांकf->dev,
			"Failed to register %s device (%d).\n",
			v4l2_type_names[type], ret);
		वापस ret;
	पूर्ण

	kref_get(&dev->ref);
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_रेजिस्टर_video(काष्ठा uvc_device *dev,
		काष्ठा uvc_streaming *stream)
अणु
	पूर्णांक ret;

	/* Initialize the streaming पूर्णांकerface with शेष parameters. */
	ret = uvc_video_init(stream);
	अगर (ret < 0) अणु
		dev_err(&stream->पूर्णांकf->dev,
			"Failed to initialize the device (%d).\n", ret);
		वापस ret;
	पूर्ण

	अगर (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		stream->chain->caps |= V4L2_CAP_VIDEO_CAPTURE
			| V4L2_CAP_META_CAPTURE;
	अन्यथा
		stream->chain->caps |= V4L2_CAP_VIDEO_OUTPUT;

	uvc_debugfs_init_stream(stream);

	/* Register the device with V4L. */
	वापस uvc_रेजिस्टर_video_device(dev, stream, &stream->vdev,
					 &stream->queue, stream->type,
					 &uvc_fops, &uvc_ioctl_ops);
पूर्ण

/*
 * Register all video devices in all chains.
 */
अटल पूर्णांक uvc_रेजिस्टर_terms(काष्ठा uvc_device *dev,
	काष्ठा uvc_video_chain *chain)
अणु
	काष्ठा uvc_streaming *stream;
	काष्ठा uvc_entity *term;
	पूर्णांक ret;

	list_क्रम_each_entry(term, &chain->entities, chain) अणु
		अगर (UVC_ENTITY_TYPE(term) != UVC_TT_STREAMING)
			जारी;

		stream = uvc_stream_by_id(dev, term->id);
		अगर (stream == शून्य) अणु
			dev_info(&dev->udev->dev,
				 "No streaming interface found for terminal %u.",
				 term->id);
			जारी;
		पूर्ण

		stream->chain = chain;
		ret = uvc_रेजिस्टर_video(dev, stream);
		अगर (ret < 0)
			वापस ret;

		/* Register a metadata node, but ignore a possible failure,
		 * complete registration of video nodes anyway.
		 */
		uvc_meta_रेजिस्टर(stream);

		term->vdev = &stream->vdev;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_रेजिस्टर_chains(काष्ठा uvc_device *dev)
अणु
	काष्ठा uvc_video_chain *chain;
	पूर्णांक ret;

	list_क्रम_each_entry(chain, &dev->chains, list) अणु
		ret = uvc_रेजिस्टर_terms(dev, chain);
		अगर (ret < 0)
			वापस ret;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
		ret = uvc_mc_रेजिस्टर_entities(chain);
		अगर (ret < 0)
			dev_info(&dev->udev->dev,
				 "Failed to register entities (%d).\n", ret);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------
 * USB probe, disconnect, suspend and resume
 */

अटल स्थिर काष्ठा uvc_device_info uvc_quirk_none = अणु 0 पूर्ण;

अटल पूर्णांक uvc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा uvc_device *dev;
	स्थिर काष्ठा uvc_device_info *info =
		(स्थिर काष्ठा uvc_device_info *)id->driver_info;
	पूर्णांक function;
	पूर्णांक ret;

	/* Allocate memory क्रम the device and initialize it. */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dev->entities);
	INIT_LIST_HEAD(&dev->chains);
	INIT_LIST_HEAD(&dev->streams);
	kref_init(&dev->ref);
	atomic_set(&dev->nmappings, 0);
	mutex_init(&dev->lock);

	dev->udev = usb_get_dev(udev);
	dev->पूर्णांकf = usb_get_पूर्णांकf(पूर्णांकf);
	dev->पूर्णांकfnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	dev->info = info ? info : &uvc_quirk_none;
	dev->quirks = uvc_quirks_param == -1
		    ? dev->info->quirks : uvc_quirks_param;

	अगर (id->idVenकरोr && id->idProduct)
		uvc_dbg(dev, PROBE, "Probing known UVC device %s (%04x:%04x)\n",
			udev->devpath, id->idVenकरोr, id->idProduct);
	अन्यथा
		uvc_dbg(dev, PROBE, "Probing generic UVC device %s\n",
			udev->devpath);

	अगर (udev->product != शून्य)
		strscpy(dev->name, udev->product, माप(dev->name));
	अन्यथा
		snम_लिखो(dev->name, माप(dev->name),
			 "UVC Camera (%04x:%04x)",
			 le16_to_cpu(udev->descriptor.idVenकरोr),
			 le16_to_cpu(udev->descriptor.idProduct));

	/*
	 * Add iFunction or iInterface to names when available as additional
	 * distinguishers between पूर्णांकerfaces. iFunction is prioritized over
	 * iInterface which matches Winकरोws behavior at the poपूर्णांक of writing.
	 */
	अगर (पूर्णांकf->पूर्णांकf_assoc && पूर्णांकf->पूर्णांकf_assoc->iFunction != 0)
		function = पूर्णांकf->पूर्णांकf_assoc->iFunction;
	अन्यथा
		function = पूर्णांकf->cur_altsetting->desc.iInterface;
	अगर (function != 0) अणु
		माप_प्रकार len;

		strlcat(dev->name, ": ", माप(dev->name));
		len = म_माप(dev->name);
		usb_string(udev, function, dev->name + len,
			   माप(dev->name) - len);
	पूर्ण

	/* Initialize the media device. */
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	dev->mdev.dev = &पूर्णांकf->dev;
	strscpy(dev->mdev.model, dev->name, माप(dev->mdev.model));
	अगर (udev->serial)
		strscpy(dev->mdev.serial, udev->serial,
			माप(dev->mdev.serial));
	usb_make_path(udev, dev->mdev.bus_info, माप(dev->mdev.bus_info));
	dev->mdev.hw_revision = le16_to_cpu(udev->descriptor.bcdDevice);
	media_device_init(&dev->mdev);

	dev->vdev.mdev = &dev->mdev;
#पूर्ण_अगर

	/* Parse the Video Class control descriptor. */
	अगर (uvc_parse_control(dev) < 0) अणु
		uvc_dbg(dev, PROBE, "Unable to parse UVC descriptors\n");
		जाओ error;
	पूर्ण

	/* Parse the associated GPIOs. */
	अगर (uvc_gpio_parse(dev) < 0) अणु
		uvc_dbg(dev, PROBE, "Unable to parse UVC GPIOs\n");
		जाओ error;
	पूर्ण

	dev_info(&dev->udev->dev, "Found UVC %u.%02x device %s (%04x:%04x)\n",
		 dev->uvc_version >> 8, dev->uvc_version & 0xff,
		 udev->product ? udev->product : "<unnamed>",
		 le16_to_cpu(udev->descriptor.idVenकरोr),
		 le16_to_cpu(udev->descriptor.idProduct));

	अगर (dev->quirks != dev->info->quirks) अणु
		dev_info(&dev->udev->dev,
			 "Forcing device quirks to 0x%x by module parameter for testing purpose.\n",
			 dev->quirks);
		dev_info(&dev->udev->dev,
			 "Please report required quirks to the linux-uvc-devel mailing list.\n");
	पूर्ण

	अगर (dev->info->uvc_version) अणु
		dev->uvc_version = dev->info->uvc_version;
		dev_info(&dev->udev->dev, "Forcing UVC version to %u.%02x\n",
			 dev->uvc_version >> 8, dev->uvc_version & 0xff);
	पूर्ण

	/* Register the V4L2 device. */
	अगर (v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &dev->vdev) < 0)
		जाओ error;

	/* Initialize controls. */
	अगर (uvc_ctrl_init_device(dev) < 0)
		जाओ error;

	/* Scan the device क्रम video chains. */
	अगर (uvc_scan_device(dev) < 0)
		जाओ error;

	/* Register video device nodes. */
	अगर (uvc_रेजिस्टर_chains(dev) < 0)
		जाओ error;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	/* Register the media device node */
	अगर (media_device_रेजिस्टर(&dev->mdev) < 0)
		जाओ error;
#पूर्ण_अगर
	/* Save our data poपूर्णांकer in the पूर्णांकerface data. */
	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	/* Initialize the पूर्णांकerrupt URB. */
	अगर ((ret = uvc_status_init(dev)) < 0) अणु
		dev_info(&dev->udev->dev,
			 "Unable to initialize the status endpoint (%d), status interrupt will not be supported.\n",
			 ret);
	पूर्ण

	ret = uvc_gpio_init_irq(dev);
	अगर (ret < 0) अणु
		dev_err(&dev->udev->dev,
			"Unable to request privacy GPIO IRQ (%d)\n", ret);
		जाओ error;
	पूर्ण

	uvc_dbg(dev, PROBE, "UVC device initialized\n");
	usb_enable_स्वतःsuspend(udev);
	वापस 0;

error:
	uvc_unरेजिस्टर_video(dev);
	kref_put(&dev->ref, uvc_delete);
	वापस -ENODEV;
पूर्ण

अटल व्योम uvc_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा uvc_device *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* Set the USB पूर्णांकerface data to शून्य. This can be करोne outside the
	 * lock, as there's no other पढ़ोer.
	 */
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceSubClass ==
	    UVC_SC_VIDEOSTREAMING)
		वापस;

	uvc_unरेजिस्टर_video(dev);
	kref_put(&dev->ref, uvc_delete);
पूर्ण

अटल पूर्णांक uvc_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा uvc_device *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uvc_streaming *stream;

	uvc_dbg(dev, SUSPEND, "Suspending interface %u\n",
		पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);

	/* Controls are cached on the fly so they करोn't need to be saved. */
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceSubClass ==
	    UVC_SC_VIDEOCONTROL) अणु
		mutex_lock(&dev->lock);
		अगर (dev->users)
			uvc_status_stop(dev);
		mutex_unlock(&dev->lock);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry(stream, &dev->streams, list) अणु
		अगर (stream->पूर्णांकf == पूर्णांकf)
			वापस uvc_video_suspend(stream);
	पूर्ण

	uvc_dbg(dev, SUSPEND,
		"Suspend: video streaming USB interface mismatch\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __uvc_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक reset)
अणु
	काष्ठा uvc_device *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uvc_streaming *stream;
	पूर्णांक ret = 0;

	uvc_dbg(dev, SUSPEND, "Resuming interface %u\n",
		पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceSubClass ==
	    UVC_SC_VIDEOCONTROL) अणु
		अगर (reset) अणु
			ret = uvc_ctrl_restore_values(dev);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		mutex_lock(&dev->lock);
		अगर (dev->users)
			ret = uvc_status_start(dev, GFP_NOIO);
		mutex_unlock(&dev->lock);

		वापस ret;
	पूर्ण

	list_क्रम_each_entry(stream, &dev->streams, list) अणु
		अगर (stream->पूर्णांकf == पूर्णांकf) अणु
			ret = uvc_video_resume(stream, reset);
			अगर (ret < 0)
				uvc_queue_streamoff(&stream->queue,
						    stream->queue.queue.type);
			वापस ret;
		पूर्ण
	पूर्ण

	uvc_dbg(dev, SUSPEND,
		"Resume: video streaming USB interface mismatch\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक uvc_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस __uvc_resume(पूर्णांकf, 0);
पूर्ण

अटल पूर्णांक uvc_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस __uvc_resume(पूर्णांकf, 1);
पूर्ण

/* ------------------------------------------------------------------------
 * Module parameters
 */

अटल पूर्णांक uvc_घड़ी_param_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (uvc_घड़ी_param == CLOCK_MONOTONIC)
		वापस प्र_लिखो(buffer, "CLOCK_MONOTONIC");
	अन्यथा
		वापस प्र_लिखो(buffer, "CLOCK_REALTIME");
पूर्ण

अटल पूर्णांक uvc_घड़ी_param_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (strnहालcmp(val, "clock_", म_माप("clock_")) == 0)
		val += म_माप("clock_");

	अगर (strहालcmp(val, "monotonic") == 0)
		uvc_घड़ी_param = CLOCK_MONOTONIC;
	अन्यथा अगर (strहालcmp(val, "realtime") == 0)
		uvc_घड़ी_param = CLOCK_REALTIME;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

module_param_call(घड़ी, uvc_घड़ी_param_set, uvc_घड़ी_param_get,
		  &uvc_घड़ी_param, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(घड़ी, "Video buffers timestamp clock");
module_param_named(hwबारtamps, uvc_hw_बारtamps_param, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(hwबारtamps, "Use hardware timestamps");
module_param_named(nodrop, uvc_no_drop_param, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(nodrop, "Don't drop incomplete frames");
module_param_named(quirks, uvc_quirks_param, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(quirks, "Forced device quirks");
module_param_named(trace, uvc_dbg_param, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(trace, "Trace level bitmask");
module_param_named(समयout, uvc_समयout_param, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(समयout, "Streaming control requests timeout");

/* ------------------------------------------------------------------------
 * Driver initialization and cleanup
 */

अटल स्थिर काष्ठा uvc_device_info uvc_quirk_probe_minmax = अणु
	.quirks = UVC_QUIRK_PROBE_MINMAX,
पूर्ण;

अटल स्थिर काष्ठा uvc_device_info uvc_quirk_fix_bandwidth = अणु
	.quirks = UVC_QUIRK_FIX_BANDWIDTH,
पूर्ण;

अटल स्थिर काष्ठा uvc_device_info uvc_quirk_probe_def = अणु
	.quirks = UVC_QUIRK_PROBE_DEF,
पूर्ण;

अटल स्थिर काष्ठा uvc_device_info uvc_quirk_stream_no_fid = अणु
	.quirks = UVC_QUIRK_STREAM_NO_FID,
पूर्ण;

अटल स्थिर काष्ठा uvc_device_info uvc_quirk_क्रमce_y8 = अणु
	.quirks = UVC_QUIRK_FORCE_Y8,
पूर्ण;

#घोषणा UVC_INFO_QUIRK(q) (kernel_uदीर्घ_t)&(काष्ठा uvc_device_info)अणु.quirks = qपूर्ण
#घोषणा UVC_INFO_META(m) (kernel_uदीर्घ_t)&(काष्ठा uvc_device_info) \
	अणु.meta_क्रमmat = mपूर्ण

/*
 * The Logitech cameras listed below have their पूर्णांकerface class set to
 * VENDOR_SPEC because they करोn't announce themselves as UVC devices, even
 * though they are compliant.
 */
अटल स्थिर काष्ठा usb_device_id uvc_ids[] = अणु
	/* LogiLink Wireless Webcam */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x0416,
	  .idProduct		= 0xa91a,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Genius eFace 2025 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x0458,
	  .idProduct		= 0x706e,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Microsoft Lअगरecam NX-6000 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x045e,
	  .idProduct		= 0x00f8,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Microsoft Lअगरecam NX-3000 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x045e,
	  .idProduct		= 0x0721,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* Microsoft Lअगरecam VX-7000 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x045e,
	  .idProduct		= 0x0723,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Logitech Quickcam Fusion */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x046d,
	  .idProduct		= 0x08c1,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Logitech Quickcam Orbit MP */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x046d,
	  .idProduct		= 0x08c2,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Logitech Quickcam Pro क्रम Notebook */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x046d,
	  .idProduct		= 0x08c3,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Logitech Quickcam Pro 5000 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x046d,
	  .idProduct		= 0x08c5,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Logitech Quickcam OEM Dell Notebook */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x046d,
	  .idProduct		= 0x08c6,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Logitech Quickcam OEM Cisco VT Camera II */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x046d,
	  .idProduct		= 0x08c7,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Logitech HD Pro Webcam C920 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x046d,
	  .idProduct		= 0x082d,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_RESTORE_CTRLS_ON_INIT) पूर्ण,
	/* Chicony CNF7129 (Asus EEE 100HE) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x04f2,
	  .idProduct		= 0xb071,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_RESTRICT_FRAME_RATE) पूर्ण,
	/* Alcor Micro AU3820 (Future Boy PC USB Webcam) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x058f,
	  .idProduct		= 0x3820,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Dell XPS m1530 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05a9,
	  .idProduct		= 0x2640,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* Dell SP2008WFP Monitor */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05a9,
	  .idProduct		= 0x2641,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* Dell Alienware X51 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05a9,
	  .idProduct		= 0x2643,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* Dell Studio Hybrid 140g (OmniVision webcam) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05a9,
	  .idProduct		= 0x264a,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* Dell XPS M1330 (OmniVision OV7670 webcam) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05a9,
	  .idProduct		= 0x7670,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* Apple Built-In iSight */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05ac,
	  .idProduct		= 0x8501,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_PROBE_MINMAX
					| UVC_QUIRK_BUILTIN_ISIGHT) पूर्ण,
	/* Apple Built-In iSight via iBridge */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05ac,
	  .idProduct		= 0x8600,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* Foxlink ("HP Webcam" on HP Mini 5103) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05c8,
	  .idProduct		= 0x0403,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_fix_bandwidth पूर्ण,
	/* Genesys Logic USB 2.0 PC Camera */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x05e3,
	  .idProduct		= 0x0505,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Hercules Classic Silver */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x06f8,
	  .idProduct		= 0x300c,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_fix_bandwidth पूर्ण,
	/* ViMicro Vega */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x0ac8,
	  .idProduct		= 0x332d,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_fix_bandwidth पूर्ण,
	/* ViMicro - Minoru3D */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x0ac8,
	  .idProduct		= 0x3410,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_fix_bandwidth पूर्ण,
	/* ViMicro Venus - Minoru3D */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x0ac8,
	  .idProduct		= 0x3420,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_fix_bandwidth पूर्ण,
	/* Ophir Optronics - SPCAM 620U */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x0bd3,
	  .idProduct		= 0x0555,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* MT6227 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x0e8d,
	  .idProduct		= 0x0004,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_PROBE_MINMAX
					| UVC_QUIRK_PROBE_DEF) पूर्ण,
	/* IMC Networks (Medion Akoya) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x13d3,
	  .idProduct		= 0x5103,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* JMicron USB2.0 XGA WebCam */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x152d,
	  .idProduct		= 0x0310,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Syntek (HP Spartan) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x174f,
	  .idProduct		= 0x5212,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Syntek (Samsung Q310) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x174f,
	  .idProduct		= 0x5931,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Syntek (Packard Bell EasyNote MX52 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x174f,
	  .idProduct		= 0x8a12,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Syntek (Asus F9SG) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x174f,
	  .idProduct		= 0x8a31,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Syntek (Asus U3S) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x174f,
	  .idProduct		= 0x8a33,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Syntek (JAOtech Smart Terminal) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x174f,
	  .idProduct		= 0x8a34,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Miricle 307K */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x17dc,
	  .idProduct		= 0x0202,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Lenovo Thinkpad SL400/SL500 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x17ef,
	  .idProduct		= 0x480b,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_stream_no_fid पूर्ण,
	/* Aveo Technology USB 2.0 Camera */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x1871,
	  .idProduct		= 0x0306,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_PROBE_MINMAX
					| UVC_QUIRK_PROBE_EXTRAFIELDS) पूर्ण,
	/* Aveo Technology USB 2.0 Camera (Tasco USB Microscope) */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x1871,
	  .idProduct		= 0x0516,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Ecamm Pico iMage */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x18cd,
	  .idProduct		= 0xcafe,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_PROBE_EXTRAFIELDS) पूर्ण,
	/* Manta MM-353 Plako */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x18ec,
	  .idProduct		= 0x3188,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* FSC WebCam V30S */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x18ec,
	  .idProduct		= 0x3288,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Arkmicro unbअक्रमed */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x18ec,
	  .idProduct		= 0x3290,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_def पूर्ण,
	/* The Imaging Source USB CCD cameras */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x199e,
	  .idProduct		= 0x8102,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0 पूर्ण,
	/* Bodelin ProScopeHR */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_DEV_HI
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x19ab,
	  .idProduct		= 0x1000,
	  .bcdDevice_hi		= 0x0126,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_STATUS_INTERVAL) पूर्ण,
	/* MSI StarCam 370i */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x1b3b,
	  .idProduct		= 0x2951,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Generalplus Technology Inc. 808 Camera */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x1b3f,
	  .idProduct		= 0x2002,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_probe_minmax पूर्ण,
	/* Shenzhen Aoni Electronic Co.,Ltd 2K FHD camera */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x1bcf,
	  .idProduct		= 0x0b40,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&(स्थिर काष्ठा uvc_device_info)अणु
		.uvc_version = 0x010a,
	  पूर्ण पूर्ण,
	/* SiGma Micro USB Web Camera */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x1c4f,
	  .idProduct		= 0x3000,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_PROBE_MINMAX
					| UVC_QUIRK_IGNORE_SELECTOR_UNIT) पूर्ण,
	/* Oculus VR Positional Tracker DK2 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x2833,
	  .idProduct		= 0x0201,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_क्रमce_y8 पूर्ण,
	/* Oculus VR Rअगरt Sensor */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x2833,
	  .idProduct		= 0x0211,
	  .bInterfaceClass	= USB_CLASS_VENDOR_SPEC,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= (kernel_uदीर्घ_t)&uvc_quirk_क्रमce_y8 पूर्ण,
	/* GEO Semiconductor GC6500 */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x29fe,
	  .idProduct		= 0x4d53,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_QUIRK(UVC_QUIRK_FORCE_BPP) पूर्ण,
	/* Intel RealSense D4M */
	अणु .match_flags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVenकरोr		= 0x8086,
	  .idProduct		= 0x0b03,
	  .bInterfaceClass	= USB_CLASS_VIDEO,
	  .bInterfaceSubClass	= 1,
	  .bInterfaceProtocol	= 0,
	  .driver_info		= UVC_INFO_META(V4L2_META_FMT_D4XX) पूर्ण,
	/* Generic USB Video Class */
	अणु USB_INTERFACE_INFO(USB_CLASS_VIDEO, 1, UVC_PC_PROTOCOL_UNDEFINED) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_VIDEO, 1, UVC_PC_PROTOCOL_15) पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, uvc_ids);

काष्ठा uvc_driver uvc_driver = अणु
	.driver = अणु
		.name		= "uvcvideo",
		.probe		= uvc_probe,
		.disconnect	= uvc_disconnect,
		.suspend	= uvc_suspend,
		.resume		= uvc_resume,
		.reset_resume	= uvc_reset_resume,
		.id_table	= uvc_ids,
		.supports_स्वतःsuspend = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init uvc_init(व्योम)
अणु
	पूर्णांक ret;

	uvc_debugfs_init();

	ret = usb_रेजिस्टर(&uvc_driver.driver);
	अगर (ret < 0) अणु
		uvc_debugfs_cleanup();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास uvc_cleanup(व्योम)
अणु
	usb_deरेजिस्टर(&uvc_driver.driver);
	uvc_debugfs_cleanup();
पूर्ण

module_init(uvc_init);
module_निकास(uvc_cleanup);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

