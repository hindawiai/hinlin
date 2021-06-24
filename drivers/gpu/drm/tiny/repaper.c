<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DRM driver क्रम Pervasive Displays RePaper bअक्रमed e-ink panels
 *
 * Copyright 2013-2017 Pervasive Displays, Inc.
 * Copyright 2017 Noralf Trथचnnes
 *
 * The driver supports:
 * Material Film: Aurora Mb (V231)
 * Driver IC: G2 (eTC)
 *
 * The controller code was taken from the userspace driver:
 * https://github.com/repaper/gratis
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/thermal.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#घोषणा REPAPER_RID_G2_COG_ID	0x12

क्रमागत repaper_model अणु
	/* 0 is reserved to aव्योम clashing with शून्य */
	E1144CS021 = 1,
	E1190CS021,
	E2200CS021,
	E2271CS021,
पूर्ण;

क्रमागत repaper_stage अणु         /* Image pixel -> Display pixel */
	REPAPER_COMPENSATE,  /* B -> W, W -> B (Current Image) */
	REPAPER_WHITE,       /* B -> N, W -> W (Current Image) */
	REPAPER_INVERSE,     /* B -> N, W -> B (New Image) */
	REPAPER_NORMAL       /* B -> B, W -> W (New Image) */
पूर्ण;

क्रमागत repaper_epd_border_byte अणु
	REPAPER_BORDER_BYTE_NONE,
	REPAPER_BORDER_BYTE_ZERO,
	REPAPER_BORDER_BYTE_SET,
पूर्ण;

काष्ठा repaper_epd अणु
	काष्ठा drm_device drm;
	काष्ठा drm_simple_display_pipe pipe;
	स्थिर काष्ठा drm_display_mode *mode;
	काष्ठा drm_connector connector;
	काष्ठा spi_device *spi;

	काष्ठा gpio_desc *panel_on;
	काष्ठा gpio_desc *border;
	काष्ठा gpio_desc *disअक्षरge;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *busy;

	काष्ठा thermal_zone_device *thermal;

	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक bytes_per_scan;
	स्थिर u8 *channel_select;
	अचिन्हित पूर्णांक stage_समय;
	अचिन्हित पूर्णांक factored_stage_समय;
	bool middle_scan;
	bool pre_border_byte;
	क्रमागत repaper_epd_border_byte border_byte;

	u8 *line_buffer;
	व्योम *current_frame;

	bool cleared;
	bool partial;
पूर्ण;

अटल अंतरभूत काष्ठा repaper_epd *drm_to_epd(काष्ठा drm_device *drm)
अणु
	वापस container_of(drm, काष्ठा repaper_epd, drm);
पूर्ण

अटल पूर्णांक repaper_spi_transfer(काष्ठा spi_device *spi, u8 header,
				स्थिर व्योम *tx, व्योम *rx, माप_प्रकार len)
अणु
	व्योम *txbuf = शून्य, *rxbuf = शून्य;
	काष्ठा spi_transfer tr[2] = अणुपूर्ण;
	u8 *headerbuf;
	पूर्णांक ret;

	headerbuf = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!headerbuf)
		वापस -ENOMEM;

	headerbuf[0] = header;
	tr[0].tx_buf = headerbuf;
	tr[0].len = 1;

	/* Stack allocated tx? */
	अगर (tx && len <= 32) अणु
		txbuf = kmemdup(tx, len, GFP_KERNEL);
		अगर (!txbuf) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	अगर (rx) अणु
		rxbuf = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!rxbuf) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	tr[1].tx_buf = txbuf ? txbuf : tx;
	tr[1].rx_buf = rxbuf;
	tr[1].len = len;

	ndelay(80);
	ret = spi_sync_transfer(spi, tr, 2);
	अगर (rx && !ret)
		स_नकल(rx, rxbuf, len);

out_मुक्त:
	kमुक्त(headerbuf);
	kमुक्त(txbuf);
	kमुक्त(rxbuf);

	वापस ret;
पूर्ण

अटल पूर्णांक repaper_ग_लिखो_buf(काष्ठा spi_device *spi, u8 reg,
			     स्थिर u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	ret = repaper_spi_transfer(spi, 0x70, &reg, शून्य, 1);
	अगर (ret)
		वापस ret;

	वापस repaper_spi_transfer(spi, 0x72, buf, शून्य, len);
पूर्ण

अटल पूर्णांक repaper_ग_लिखो_val(काष्ठा spi_device *spi, u8 reg, u8 val)
अणु
	वापस repaper_ग_लिखो_buf(spi, reg, &val, 1);
पूर्ण

अटल पूर्णांक repaper_पढ़ो_val(काष्ठा spi_device *spi, u8 reg)
अणु
	पूर्णांक ret;
	u8 val;

	ret = repaper_spi_transfer(spi, 0x70, &reg, शून्य, 1);
	अगर (ret)
		वापस ret;

	ret = repaper_spi_transfer(spi, 0x73, शून्य, &val, 1);

	वापस ret ? ret : val;
पूर्ण

अटल पूर्णांक repaper_पढ़ो_id(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	u8 id;

	ret = repaper_spi_transfer(spi, 0x71, शून्य, &id, 1);

	वापस ret ? ret : id;
पूर्ण

अटल व्योम repaper_spi_mosi_low(काष्ठा spi_device *spi)
अणु
	स्थिर u8 buf[1] = अणु 0 पूर्ण;

	spi_ग_लिखो(spi, buf, 1);
पूर्ण

/* pixels on display are numbered from 1 so even is actually bits 1,3,5,... */
अटल व्योम repaper_even_pixels(काष्ठा repaper_epd *epd, u8 **pp,
				स्थिर u8 *data, u8 fixed_value, स्थिर u8 *mask,
				क्रमागत repaper_stage stage)
अणु
	अचिन्हित पूर्णांक b;

	क्रम (b = 0; b < (epd->width / 8); b++) अणु
		अगर (data) अणु
			u8 pixels = data[b] & 0xaa;
			u8 pixel_mask = 0xff;
			u8 p1, p2, p3, p4;

			अगर (mask) अणु
				pixel_mask = (mask[b] ^ pixels) & 0xaa;
				pixel_mask |= pixel_mask >> 1;
			पूर्ण

			चयन (stage) अणु
			हाल REPAPER_COMPENSATE: /* B -> W, W -> B (Current) */
				pixels = 0xaa | ((pixels ^ 0xaa) >> 1);
				अवरोध;
			हाल REPAPER_WHITE:      /* B -> N, W -> W (Current) */
				pixels = 0x55 + ((pixels ^ 0xaa) >> 1);
				अवरोध;
			हाल REPAPER_INVERSE:    /* B -> N, W -> B (New) */
				pixels = 0x55 | (pixels ^ 0xaa);
				अवरोध;
			हाल REPAPER_NORMAL:     /* B -> B, W -> W (New) */
				pixels = 0xaa | (pixels >> 1);
				अवरोध;
			पूर्ण

			pixels = (pixels & pixel_mask) | (~pixel_mask & 0x55);
			p1 = (pixels >> 6) & 0x03;
			p2 = (pixels >> 4) & 0x03;
			p3 = (pixels >> 2) & 0x03;
			p4 = (pixels >> 0) & 0x03;
			pixels = (p1 << 0) | (p2 << 2) | (p3 << 4) | (p4 << 6);
			*(*pp)++ = pixels;
		पूर्ण अन्यथा अणु
			*(*pp)++ = fixed_value;
		पूर्ण
	पूर्ण
पूर्ण

/* pixels on display are numbered from 1 so odd is actually bits 0,2,4,... */
अटल व्योम repaper_odd_pixels(काष्ठा repaper_epd *epd, u8 **pp,
			       स्थिर u8 *data, u8 fixed_value, स्थिर u8 *mask,
			       क्रमागत repaper_stage stage)
अणु
	अचिन्हित पूर्णांक b;

	क्रम (b = epd->width / 8; b > 0; b--) अणु
		अगर (data) अणु
			u8 pixels = data[b - 1] & 0x55;
			u8 pixel_mask = 0xff;

			अगर (mask) अणु
				pixel_mask = (mask[b - 1] ^ pixels) & 0x55;
				pixel_mask |= pixel_mask << 1;
			पूर्ण

			चयन (stage) अणु
			हाल REPAPER_COMPENSATE: /* B -> W, W -> B (Current) */
				pixels = 0xaa | (pixels ^ 0x55);
				अवरोध;
			हाल REPAPER_WHITE:      /* B -> N, W -> W (Current) */
				pixels = 0x55 + (pixels ^ 0x55);
				अवरोध;
			हाल REPAPER_INVERSE:    /* B -> N, W -> B (New) */
				pixels = 0x55 | ((pixels ^ 0x55) << 1);
				अवरोध;
			हाल REPAPER_NORMAL:     /* B -> B, W -> W (New) */
				pixels = 0xaa | pixels;
				अवरोध;
			पूर्ण

			pixels = (pixels & pixel_mask) | (~pixel_mask & 0x55);
			*(*pp)++ = pixels;
		पूर्ण अन्यथा अणु
			*(*pp)++ = fixed_value;
		पूर्ण
	पूर्ण
पूर्ण

/* पूर्णांकerleave bits: (byte)76543210 -> (16 bit).7.6.5.4.3.2.1 */
अटल अंतरभूत u16 repaper_पूर्णांकerleave_bits(u16 value)
अणु
	value = (value | (value << 4)) & 0x0f0f;
	value = (value | (value << 2)) & 0x3333;
	value = (value | (value << 1)) & 0x5555;

	वापस value;
पूर्ण

/* pixels on display are numbered from 1 */
अटल व्योम repaper_all_pixels(काष्ठा repaper_epd *epd, u8 **pp,
			       स्थिर u8 *data, u8 fixed_value, स्थिर u8 *mask,
			       क्रमागत repaper_stage stage)
अणु
	अचिन्हित पूर्णांक b;

	क्रम (b = epd->width / 8; b > 0; b--) अणु
		अगर (data) अणु
			u16 pixels = repaper_पूर्णांकerleave_bits(data[b - 1]);
			u16 pixel_mask = 0xffff;

			अगर (mask) अणु
				pixel_mask = repaper_पूर्णांकerleave_bits(mask[b - 1]);

				pixel_mask = (pixel_mask ^ pixels) & 0x5555;
				pixel_mask |= pixel_mask << 1;
			पूर्ण

			चयन (stage) अणु
			हाल REPAPER_COMPENSATE: /* B -> W, W -> B (Current) */
				pixels = 0xaaaa | (pixels ^ 0x5555);
				अवरोध;
			हाल REPAPER_WHITE:      /* B -> N, W -> W (Current) */
				pixels = 0x5555 + (pixels ^ 0x5555);
				अवरोध;
			हाल REPAPER_INVERSE:    /* B -> N, W -> B (New) */
				pixels = 0x5555 | ((pixels ^ 0x5555) << 1);
				अवरोध;
			हाल REPAPER_NORMAL:     /* B -> B, W -> W (New) */
				pixels = 0xaaaa | pixels;
				अवरोध;
			पूर्ण

			pixels = (pixels & pixel_mask) | (~pixel_mask & 0x5555);
			*(*pp)++ = pixels >> 8;
			*(*pp)++ = pixels;
		पूर्ण अन्यथा अणु
			*(*pp)++ = fixed_value;
			*(*pp)++ = fixed_value;
		पूर्ण
	पूर्ण
पूर्ण

/* output one line of scan and data bytes to the display */
अटल व्योम repaper_one_line(काष्ठा repaper_epd *epd, अचिन्हित पूर्णांक line,
			     स्थिर u8 *data, u8 fixed_value, स्थिर u8 *mask,
			     क्रमागत repaper_stage stage)
अणु
	u8 *p = epd->line_buffer;
	अचिन्हित पूर्णांक b;

	repaper_spi_mosi_low(epd->spi);

	अगर (epd->pre_border_byte)
		*p++ = 0x00;

	अगर (epd->middle_scan) अणु
		/* data bytes */
		repaper_odd_pixels(epd, &p, data, fixed_value, mask, stage);

		/* scan line */
		क्रम (b = epd->bytes_per_scan; b > 0; b--) अणु
			अगर (line / 4 == b - 1)
				*p++ = 0x03 << (2 * (line & 0x03));
			अन्यथा
				*p++ = 0x00;
		पूर्ण

		/* data bytes */
		repaper_even_pixels(epd, &p, data, fixed_value, mask, stage);
	पूर्ण अन्यथा अणु
		/*
		 * even scan line, but as lines on display are numbered from 1,
		 * line: 1,3,5,...
		 */
		क्रम (b = 0; b < epd->bytes_per_scan; b++) अणु
			अगर (0 != (line & 0x01) && line / 8 == b)
				*p++ = 0xc0 >> (line & 0x06);
			अन्यथा
				*p++ = 0x00;
		पूर्ण

		/* data bytes */
		repaper_all_pixels(epd, &p, data, fixed_value, mask, stage);

		/*
		 * odd scan line, but as lines on display are numbered from 1,
		 * line: 0,2,4,6,...
		 */
		क्रम (b = epd->bytes_per_scan; b > 0; b--) अणु
			अगर (0 == (line & 0x01) && line / 8 == b - 1)
				*p++ = 0x03 << (line & 0x06);
			अन्यथा
				*p++ = 0x00;
		पूर्ण
	पूर्ण

	चयन (epd->border_byte) अणु
	हाल REPAPER_BORDER_BYTE_NONE:
		अवरोध;

	हाल REPAPER_BORDER_BYTE_ZERO:
		*p++ = 0x00;
		अवरोध;

	हाल REPAPER_BORDER_BYTE_SET:
		चयन (stage) अणु
		हाल REPAPER_COMPENSATE:
		हाल REPAPER_WHITE:
		हाल REPAPER_INVERSE:
			*p++ = 0x00;
			अवरोध;
		हाल REPAPER_NORMAL:
			*p++ = 0xaa;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	repaper_ग_लिखो_buf(epd->spi, 0x0a, epd->line_buffer,
			  p - epd->line_buffer);

	/* Output data to panel */
	repaper_ग_लिखो_val(epd->spi, 0x02, 0x07);

	repaper_spi_mosi_low(epd->spi);
पूर्ण

अटल व्योम repaper_frame_fixed(काष्ठा repaper_epd *epd, u8 fixed_value,
				क्रमागत repaper_stage stage)
अणु
	अचिन्हित पूर्णांक line;

	क्रम (line = 0; line < epd->height; line++)
		repaper_one_line(epd, line, शून्य, fixed_value, शून्य, stage);
पूर्ण

अटल व्योम repaper_frame_data(काष्ठा repaper_epd *epd, स्थिर u8 *image,
			       स्थिर u8 *mask, क्रमागत repaper_stage stage)
अणु
	अचिन्हित पूर्णांक line;

	अगर (!mask) अणु
		क्रम (line = 0; line < epd->height; line++) अणु
			repaper_one_line(epd, line,
					 &image[line * (epd->width / 8)],
					 0, शून्य, stage);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (line = 0; line < epd->height; line++) अणु
			माप_प्रकार n = line * epd->width / 8;

			repaper_one_line(epd, line, &image[n], 0, &mask[n],
					 stage);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम repaper_frame_fixed_repeat(काष्ठा repaper_epd *epd, u8 fixed_value,
				       क्रमागत repaper_stage stage)
अणु
	u64 start = local_घड़ी();
	u64 end = start + (epd->factored_stage_समय * 1000 * 1000);

	करो अणु
		repaper_frame_fixed(epd, fixed_value, stage);
	पूर्ण जबतक (local_घड़ी() < end);
पूर्ण

अटल व्योम repaper_frame_data_repeat(काष्ठा repaper_epd *epd, स्थिर u8 *image,
				      स्थिर u8 *mask, क्रमागत repaper_stage stage)
अणु
	u64 start = local_घड़ी();
	u64 end = start + (epd->factored_stage_समय * 1000 * 1000);

	करो अणु
		repaper_frame_data(epd, image, mask, stage);
	पूर्ण जबतक (local_घड़ी() < end);
पूर्ण

अटल व्योम repaper_get_temperature(काष्ठा repaper_epd *epd)
अणु
	पूर्णांक ret, temperature = 0;
	अचिन्हित पूर्णांक factor10x;

	अगर (!epd->thermal)
		वापस;

	ret = thermal_zone_get_temp(epd->thermal, &temperature);
	अगर (ret) अणु
		DRM_DEV_ERROR(&epd->spi->dev, "Failed to get temperature (%d)\n", ret);
		वापस;
	पूर्ण

	temperature /= 1000;

	अगर (temperature <= -10)
		factor10x = 170;
	अन्यथा अगर (temperature <= -5)
		factor10x = 120;
	अन्यथा अगर (temperature <= 5)
		factor10x = 80;
	अन्यथा अगर (temperature <= 10)
		factor10x = 40;
	अन्यथा अगर (temperature <= 15)
		factor10x = 30;
	अन्यथा अगर (temperature <= 20)
		factor10x = 20;
	अन्यथा अगर (temperature <= 40)
		factor10x = 10;
	अन्यथा
		factor10x = 7;

	epd->factored_stage_समय = epd->stage_समय * factor10x / 10;
पूर्ण

अटल व्योम repaper_gray8_to_mono_reversed(u8 *buf, u32 width, u32 height)
अणु
	u8 *gray8 = buf, *mono = buf;
	पूर्णांक y, xb, i;

	क्रम (y = 0; y < height; y++)
		क्रम (xb = 0; xb < width / 8; xb++) अणु
			u8 byte = 0x00;

			क्रम (i = 0; i < 8; i++) अणु
				पूर्णांक x = xb * 8 + i;

				byte >>= 1;
				अगर (gray8[y * width + x] >> 7)
					byte |= BIT(7);
			पूर्ण
			*mono++ = byte;
		पूर्ण
पूर्ण

अटल पूर्णांक repaper_fb_dirty(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_gem_cma_object *cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	काष्ठा dma_buf_attachment *import_attach = cma_obj->base.import_attach;
	काष्ठा repaper_epd *epd = drm_to_epd(fb->dev);
	काष्ठा drm_rect clip;
	पूर्णांक idx, ret = 0;
	u8 *buf = शून्य;

	अगर (!drm_dev_enter(fb->dev, &idx))
		वापस -ENODEV;

	/* repaper can't करो partial updates */
	clip.x1 = 0;
	clip.x2 = fb->width;
	clip.y1 = 0;
	clip.y2 = fb->height;

	repaper_get_temperature(epd);

	DRM_DEBUG("Flushing [FB:%d] st=%ums\n", fb->base.id,
		  epd->factored_stage_समय);

	buf = kदो_स्मृति_array(fb->width, fb->height, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out_निकास;
	पूर्ण

	अगर (import_attach) अणु
		ret = dma_buf_begin_cpu_access(import_attach->dmabuf,
					       DMA_FROM_DEVICE);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	drm_fb_xrgb8888_to_gray8(buf, cma_obj->vaddr, fb, &clip);

	अगर (import_attach) अणु
		ret = dma_buf_end_cpu_access(import_attach->dmabuf,
					     DMA_FROM_DEVICE);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	repaper_gray8_to_mono_reversed(buf, fb->width, fb->height);

	अगर (epd->partial) अणु
		repaper_frame_data_repeat(epd, buf, epd->current_frame,
					  REPAPER_NORMAL);
	पूर्ण अन्यथा अगर (epd->cleared) अणु
		repaper_frame_data_repeat(epd, epd->current_frame, शून्य,
					  REPAPER_COMPENSATE);
		repaper_frame_data_repeat(epd, epd->current_frame, शून्य,
					  REPAPER_WHITE);
		repaper_frame_data_repeat(epd, buf, शून्य, REPAPER_INVERSE);
		repaper_frame_data_repeat(epd, buf, शून्य, REPAPER_NORMAL);

		epd->partial = true;
	पूर्ण अन्यथा अणु
		/* Clear display (anything -> white) */
		repaper_frame_fixed_repeat(epd, 0xff, REPAPER_COMPENSATE);
		repaper_frame_fixed_repeat(epd, 0xff, REPAPER_WHITE);
		repaper_frame_fixed_repeat(epd, 0xaa, REPAPER_INVERSE);
		repaper_frame_fixed_repeat(epd, 0xaa, REPAPER_NORMAL);

		/* Assuming a clear (white) screen output an image */
		repaper_frame_fixed_repeat(epd, 0xaa, REPAPER_COMPENSATE);
		repaper_frame_fixed_repeat(epd, 0xaa, REPAPER_WHITE);
		repaper_frame_data_repeat(epd, buf, शून्य, REPAPER_INVERSE);
		repaper_frame_data_repeat(epd, buf, शून्य, REPAPER_NORMAL);

		epd->cleared = true;
		epd->partial = true;
	पूर्ण

	स_नकल(epd->current_frame, buf, fb->width * fb->height / 8);

	/*
	 * An extra frame ग_लिखो is needed अगर pixels are set in the bottom line,
	 * or अन्यथा grey lines rises up from the pixels
	 */
	अगर (epd->pre_border_byte) अणु
		अचिन्हित पूर्णांक x;

		क्रम (x = 0; x < (fb->width / 8); x++)
			अगर (buf[x + (fb->width * (fb->height - 1) / 8)]) अणु
				repaper_frame_data_repeat(epd, buf,
							  epd->current_frame,
							  REPAPER_NORMAL);
				अवरोध;
			पूर्ण
	पूर्ण

out_मुक्त:
	kमुक्त(buf);
out_निकास:
	drm_dev_निकास(idx);

	वापस ret;
पूर्ण

अटल व्योम घातer_off(काष्ठा repaper_epd *epd)
अणु
	/* Turn off घातer and all संकेतs */
	gpiod_set_value_cansleep(epd->reset, 0);
	gpiod_set_value_cansleep(epd->panel_on, 0);
	अगर (epd->border)
		gpiod_set_value_cansleep(epd->border, 0);

	/* Ensure SPI MOSI and CLOCK are Low beक्रमe CS Low */
	repaper_spi_mosi_low(epd->spi);

	/* Disअक्षरge pulse */
	gpiod_set_value_cansleep(epd->disअक्षरge, 1);
	msleep(150);
	gpiod_set_value_cansleep(epd->disअक्षरge, 0);
पूर्ण

अटल व्योम repaper_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
				काष्ठा drm_crtc_state *crtc_state,
				काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा repaper_epd *epd = drm_to_epd(pipe->crtc.dev);
	काष्ठा spi_device *spi = epd->spi;
	काष्ठा device *dev = &spi->dev;
	bool dc_ok = false;
	पूर्णांक i, ret, idx;

	अगर (!drm_dev_enter(pipe->crtc.dev, &idx))
		वापस;

	DRM_DEBUG_DRIVER("\n");

	/* Power up sequence */
	gpiod_set_value_cansleep(epd->reset, 0);
	gpiod_set_value_cansleep(epd->panel_on, 0);
	gpiod_set_value_cansleep(epd->disअक्षरge, 0);
	अगर (epd->border)
		gpiod_set_value_cansleep(epd->border, 0);
	repaper_spi_mosi_low(spi);
	usleep_range(5000, 10000);

	gpiod_set_value_cansleep(epd->panel_on, 1);
	/*
	 * This delay comes from the repaper.org userspace driver, it's not
	 * mentioned in the datasheet.
	 */
	usleep_range(10000, 15000);
	gpiod_set_value_cansleep(epd->reset, 1);
	अगर (epd->border)
		gpiod_set_value_cansleep(epd->border, 1);
	usleep_range(5000, 10000);
	gpiod_set_value_cansleep(epd->reset, 0);
	usleep_range(5000, 10000);
	gpiod_set_value_cansleep(epd->reset, 1);
	usleep_range(5000, 10000);

	/* Wait क्रम COG to become पढ़ोy */
	क्रम (i = 100; i > 0; i--) अणु
		अगर (!gpiod_get_value_cansleep(epd->busy))
			अवरोध;

		usleep_range(10, 100);
	पूर्ण

	अगर (!i) अणु
		DRM_DEV_ERROR(dev, "timeout waiting for panel to become ready.\n");
		घातer_off(epd);
		जाओ out_निकास;
	पूर्ण

	repaper_पढ़ो_id(spi);
	ret = repaper_पढ़ो_id(spi);
	अगर (ret != REPAPER_RID_G2_COG_ID) अणु
		अगर (ret < 0)
			dev_err(dev, "failed to read chip (%d)\n", ret);
		अन्यथा
			dev_err(dev, "wrong COG ID 0x%02x\n", ret);
		घातer_off(epd);
		जाओ out_निकास;
	पूर्ण

	/* Disable OE */
	repaper_ग_लिखो_val(spi, 0x02, 0x40);

	ret = repaper_पढ़ो_val(spi, 0x0f);
	अगर (ret < 0 || !(ret & 0x80)) अणु
		अगर (ret < 0)
			DRM_DEV_ERROR(dev, "failed to read chip (%d)\n", ret);
		अन्यथा
			DRM_DEV_ERROR(dev, "panel is reported broken\n");
		घातer_off(epd);
		जाओ out_निकास;
	पूर्ण

	/* Power saving mode */
	repaper_ग_लिखो_val(spi, 0x0b, 0x02);
	/* Channel select */
	repaper_ग_लिखो_buf(spi, 0x01, epd->channel_select, 8);
	/* High घातer mode osc */
	repaper_ग_लिखो_val(spi, 0x07, 0xd1);
	/* Power setting */
	repaper_ग_लिखो_val(spi, 0x08, 0x02);
	/* Vcom level */
	repaper_ग_लिखो_val(spi, 0x09, 0xc2);
	/* Power setting */
	repaper_ग_लिखो_val(spi, 0x04, 0x03);
	/* Driver latch on */
	repaper_ग_लिखो_val(spi, 0x03, 0x01);
	/* Driver latch off */
	repaper_ग_लिखो_val(spi, 0x03, 0x00);
	usleep_range(5000, 10000);

	/* Start अक्षरgepump */
	क्रम (i = 0; i < 4; ++i) अणु
		/* Charge pump positive voltage on - VGH/VDL on */
		repaper_ग_लिखो_val(spi, 0x05, 0x01);
		msleep(240);

		/* Charge pump negative voltage on - VGL/VDL on */
		repaper_ग_लिखो_val(spi, 0x05, 0x03);
		msleep(40);

		/* Charge pump Vcom on - Vcom driver on */
		repaper_ग_लिखो_val(spi, 0x05, 0x0f);
		msleep(40);

		/* check DC/DC */
		ret = repaper_पढ़ो_val(spi, 0x0f);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(dev, "failed to read chip (%d)\n", ret);
			घातer_off(epd);
			जाओ out_निकास;
		पूर्ण

		अगर (ret & 0x40) अणु
			dc_ok = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!dc_ok) अणु
		DRM_DEV_ERROR(dev, "dc/dc failed\n");
		घातer_off(epd);
		जाओ out_निकास;
	पूर्ण

	/*
	 * Output enable to disable
	 * The userspace driver sets this to 0x04, but the datasheet says 0x06
	 */
	repaper_ग_लिखो_val(spi, 0x02, 0x04);

	epd->partial = false;
out_निकास:
	drm_dev_निकास(idx);
पूर्ण

अटल व्योम repaper_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा repaper_epd *epd = drm_to_epd(pipe->crtc.dev);
	काष्ठा spi_device *spi = epd->spi;
	अचिन्हित पूर्णांक line;

	/*
	 * This callback is not रक्षित by drm_dev_enter/निकास since we want to
	 * turn off the display on regular driver unload. It's highly unlikely
	 * that the underlying SPI controller is gone should this be called after
	 * unplug.
	 */

	DRM_DEBUG_DRIVER("\n");

	/* Nothing frame */
	क्रम (line = 0; line < epd->height; line++)
		repaper_one_line(epd, 0x7fffu, शून्य, 0x00, शून्य,
				 REPAPER_COMPENSATE);

	/* 2.7" */
	अगर (epd->border) अणु
		/* Dummy line */
		repaper_one_line(epd, 0x7fffu, शून्य, 0x00, शून्य,
				 REPAPER_COMPENSATE);
		msleep(25);
		gpiod_set_value_cansleep(epd->border, 0);
		msleep(200);
		gpiod_set_value_cansleep(epd->border, 1);
	पूर्ण अन्यथा अणु
		/* Border dummy line */
		repaper_one_line(epd, 0x7fffu, शून्य, 0x00, शून्य,
				 REPAPER_NORMAL);
		msleep(200);
	पूर्ण

	/* not described in datasheet */
	repaper_ग_लिखो_val(spi, 0x0b, 0x00);
	/* Latch reset turn on */
	repaper_ग_लिखो_val(spi, 0x03, 0x01);
	/* Power off अक्षरge pump Vcom */
	repaper_ग_लिखो_val(spi, 0x05, 0x03);
	/* Power off अक्षरge pump neg voltage */
	repaper_ग_लिखो_val(spi, 0x05, 0x01);
	msleep(120);
	/* Disअक्षरge पूर्णांकernal */
	repaper_ग_लिखो_val(spi, 0x04, 0x80);
	/* turn off all अक्षरge pumps */
	repaper_ग_लिखो_val(spi, 0x05, 0x00);
	/* Turn off osc */
	repaper_ग_लिखो_val(spi, 0x07, 0x01);
	msleep(50);

	घातer_off(epd);
पूर्ण

अटल व्योम repaper_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
				काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_rect rect;

	अगर (!pipe->crtc.state->active)
		वापस;

	अगर (drm_atomic_helper_damage_merged(old_state, state, &rect))
		repaper_fb_dirty(state->fb);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs repaper_pipe_funcs = अणु
	.enable = repaper_pipe_enable,
	.disable = repaper_pipe_disable,
	.update = repaper_pipe_update,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल पूर्णांक repaper_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा repaper_epd *epd = drm_to_epd(connector->dev);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, epd->mode);
	अगर (!mode) अणु
		DRM_ERROR("Failed to duplicate mode\n");
		वापस 0;
	पूर्ण

	drm_mode_set_name(mode);
	mode->type |= DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs repaper_connector_hfuncs = अणु
	.get_modes = repaper_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs repaper_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs repaper_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create_with_dirty,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर uपूर्णांक32_t repaper_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode repaper_e1144cs021_mode = अणु
	DRM_SIMPLE_MODE(128, 96, 29, 22),
पूर्ण;

अटल स्थिर u8 repaper_e1144cs021_cs[] = अणु 0x00, 0x00, 0x00, 0x00,
					    0x00, 0x0f, 0xff, 0x00 पूर्ण;

अटल स्थिर काष्ठा drm_display_mode repaper_e1190cs021_mode = अणु
	DRM_SIMPLE_MODE(144, 128, 36, 32),
पूर्ण;

अटल स्थिर u8 repaper_e1190cs021_cs[] = अणु 0x00, 0x00, 0x00, 0x03,
					    0xfc, 0x00, 0x00, 0xff पूर्ण;

अटल स्थिर काष्ठा drm_display_mode repaper_e2200cs021_mode = अणु
	DRM_SIMPLE_MODE(200, 96, 46, 22),
पूर्ण;

अटल स्थिर u8 repaper_e2200cs021_cs[] = अणु 0x00, 0x00, 0x00, 0x00,
					    0x01, 0xff, 0xe0, 0x00 पूर्ण;

अटल स्थिर काष्ठा drm_display_mode repaper_e2271cs021_mode = अणु
	DRM_SIMPLE_MODE(264, 176, 57, 38),
पूर्ण;

अटल स्थिर u8 repaper_e2271cs021_cs[] = अणु 0x00, 0x00, 0x00, 0x7f,
					    0xff, 0xfe, 0x00, 0x00 पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(repaper_fops);

अटल स्थिर काष्ठा drm_driver repaper_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &repaper_fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.name			= "repaper",
	.desc			= "Pervasive Displays RePaper e-ink panels",
	.date			= "20170405",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id repaper_of_match[] = अणु
	अणु .compatible = "pervasive,e1144cs021", .data = (व्योम *)E1144CS021 पूर्ण,
	अणु .compatible = "pervasive,e1190cs021", .data = (व्योम *)E1190CS021 पूर्ण,
	अणु .compatible = "pervasive,e2200cs021", .data = (व्योम *)E2200CS021 पूर्ण,
	अणु .compatible = "pervasive,e2271cs021", .data = (व्योम *)E2271CS021 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, repaper_of_match);

अटल स्थिर काष्ठा spi_device_id repaper_id[] = अणु
	अणु "e1144cs021", E1144CS021 पूर्ण,
	अणु "e1190cs021", E1190CS021 पूर्ण,
	अणु "e2200cs021", E2200CS021 पूर्ण,
	अणु "e2271cs021", E2271CS021 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, repaper_id);

अटल पूर्णांक repaper_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा drm_display_mode *mode;
	स्थिर काष्ठा spi_device_id *spi_id;
	काष्ठा device *dev = &spi->dev;
	क्रमागत repaper_model model;
	स्थिर अक्षर *thermal_zone;
	काष्ठा repaper_epd *epd;
	माप_प्रकार line_buffer_size;
	काष्ठा drm_device *drm;
	स्थिर व्योम *match;
	पूर्णांक ret;

	match = device_get_match_data(dev);
	अगर (match) अणु
		model = (क्रमागत repaper_model)match;
	पूर्ण अन्यथा अणु
		spi_id = spi_get_device_id(spi);
		model = (क्रमागत repaper_model)spi_id->driver_data;
	पूर्ण

	/* The SPI device is used to allocate dma memory */
	अगर (!dev->coherent_dma_mask) अणु
		ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_warn(dev, "Failed to set dma mask %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	epd = devm_drm_dev_alloc(dev, &repaper_driver,
				 काष्ठा repaper_epd, drm);
	अगर (IS_ERR(epd))
		वापस PTR_ERR(epd);

	drm = &epd->drm;

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;
	drm->mode_config.funcs = &repaper_mode_config_funcs;

	epd->spi = spi;

	epd->panel_on = devm_gpiod_get(dev, "panel-on", GPIOD_OUT_LOW);
	अगर (IS_ERR(epd->panel_on)) अणु
		ret = PTR_ERR(epd->panel_on);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'panel-on'\n");
		वापस ret;
	पूर्ण

	epd->disअक्षरge = devm_gpiod_get(dev, "discharge", GPIOD_OUT_LOW);
	अगर (IS_ERR(epd->disअक्षरge)) अणु
		ret = PTR_ERR(epd->disअक्षरge);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'discharge'\n");
		वापस ret;
	पूर्ण

	epd->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(epd->reset)) अणु
		ret = PTR_ERR(epd->reset);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
		वापस ret;
	पूर्ण

	epd->busy = devm_gpiod_get(dev, "busy", GPIOD_IN);
	अगर (IS_ERR(epd->busy)) अणु
		ret = PTR_ERR(epd->busy);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "Failed to get gpio 'busy'\n");
		वापस ret;
	पूर्ण

	अगर (!device_property_पढ़ो_string(dev, "pervasive,thermal-zone",
					 &thermal_zone)) अणु
		epd->thermal = thermal_zone_get_zone_by_name(thermal_zone);
		अगर (IS_ERR(epd->thermal)) अणु
			DRM_DEV_ERROR(dev, "Failed to get thermal zone: %s\n", thermal_zone);
			वापस PTR_ERR(epd->thermal);
		पूर्ण
	पूर्ण

	चयन (model) अणु
	हाल E1144CS021:
		mode = &repaper_e1144cs021_mode;
		epd->channel_select = repaper_e1144cs021_cs;
		epd->stage_समय = 480;
		epd->bytes_per_scan = 96 / 4;
		epd->middle_scan = true; /* data-scan-data */
		epd->pre_border_byte = false;
		epd->border_byte = REPAPER_BORDER_BYTE_ZERO;
		अवरोध;

	हाल E1190CS021:
		mode = &repaper_e1190cs021_mode;
		epd->channel_select = repaper_e1190cs021_cs;
		epd->stage_समय = 480;
		epd->bytes_per_scan = 128 / 4 / 2;
		epd->middle_scan = false; /* scan-data-scan */
		epd->pre_border_byte = false;
		epd->border_byte = REPAPER_BORDER_BYTE_SET;
		अवरोध;

	हाल E2200CS021:
		mode = &repaper_e2200cs021_mode;
		epd->channel_select = repaper_e2200cs021_cs;
		epd->stage_समय = 480;
		epd->bytes_per_scan = 96 / 4;
		epd->middle_scan = true; /* data-scan-data */
		epd->pre_border_byte = true;
		epd->border_byte = REPAPER_BORDER_BYTE_NONE;
		अवरोध;

	हाल E2271CS021:
		epd->border = devm_gpiod_get(dev, "border", GPIOD_OUT_LOW);
		अगर (IS_ERR(epd->border)) अणु
			ret = PTR_ERR(epd->border);
			अगर (ret != -EPROBE_DEFER)
				DRM_DEV_ERROR(dev, "Failed to get gpio 'border'\n");
			वापस ret;
		पूर्ण

		mode = &repaper_e2271cs021_mode;
		epd->channel_select = repaper_e2271cs021_cs;
		epd->stage_समय = 630;
		epd->bytes_per_scan = 176 / 4;
		epd->middle_scan = true; /* data-scan-data */
		epd->pre_border_byte = true;
		epd->border_byte = REPAPER_BORDER_BYTE_NONE;
		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	epd->mode = mode;
	epd->width = mode->hdisplay;
	epd->height = mode->vdisplay;
	epd->factored_stage_समय = epd->stage_समय;

	line_buffer_size = 2 * epd->width / 8 + epd->bytes_per_scan + 2;
	epd->line_buffer = devm_kzalloc(dev, line_buffer_size, GFP_KERNEL);
	अगर (!epd->line_buffer)
		वापस -ENOMEM;

	epd->current_frame = devm_kzalloc(dev, epd->width * epd->height / 8,
					  GFP_KERNEL);
	अगर (!epd->current_frame)
		वापस -ENOMEM;

	drm->mode_config.min_width = mode->hdisplay;
	drm->mode_config.max_width = mode->hdisplay;
	drm->mode_config.min_height = mode->vdisplay;
	drm->mode_config.max_height = mode->vdisplay;

	drm_connector_helper_add(&epd->connector, &repaper_connector_hfuncs);
	ret = drm_connector_init(drm, &epd->connector, &repaper_connector_funcs,
				 DRM_MODE_CONNECTOR_SPI);
	अगर (ret)
		वापस ret;

	ret = drm_simple_display_pipe_init(drm, &epd->pipe, &repaper_pipe_funcs,
					   repaper_क्रमmats, ARRAY_SIZE(repaper_क्रमmats),
					   शून्य, &epd->connector);
	अगर (ret)
		वापस ret;

	drm_mode_config_reset(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, drm);

	DRM_DEBUG_DRIVER("SPI speed: %uMHz\n", spi->max_speed_hz / 1000000);

	drm_fbdev_generic_setup(drm, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक repaper_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

अटल व्योम repaper_shutकरोwn(काष्ठा spi_device *spi)
अणु
	drm_atomic_helper_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल काष्ठा spi_driver repaper_spi_driver = अणु
	.driver = अणु
		.name = "repaper",
		.of_match_table = repaper_of_match,
	पूर्ण,
	.id_table = repaper_id,
	.probe = repaper_probe,
	.हटाओ = repaper_हटाओ,
	.shutकरोwn = repaper_shutकरोwn,
पूर्ण;
module_spi_driver(repaper_spi_driver);

MODULE_DESCRIPTION("Pervasive Displays RePaper DRM driver");
MODULE_AUTHOR("Noralf Trथचnnes");
MODULE_LICENSE("GPL");
