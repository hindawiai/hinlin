<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    yuv support

    Copyright (C) 2007  Ian Armstrong <ian@iarmst.demon.co.uk>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-udma.h"
#समावेश "ivtv-yuv.h"

/* YUV buffer offsets */
स्थिर u32 yuv_offset[IVTV_YUV_BUFFERS] = अणु
	0x001a8600,
	0x00240400,
	0x002d8200,
	0x00370000,
	0x00029000,
	0x000C0E00,
	0x006B0400,
	0x00748200
पूर्ण;

अटल पूर्णांक ivtv_yuv_prep_user_dma(काष्ठा ivtv *itv, काष्ठा ivtv_user_dma *dma,
				  काष्ठा ivtv_dma_frame *args)
अणु
	काष्ठा ivtv_dma_page_info y_dma;
	काष्ठा ivtv_dma_page_info uv_dma;
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	u8 frame = yi->draw_frame;
	काष्ठा yuv_frame_info *f = &yi->new_frame_info[frame];
	पूर्णांक y_pages, uv_pages;
	अचिन्हित दीर्घ y_buffer_offset, uv_buffer_offset;
	पूर्णांक y_decode_height, uv_decode_height, y_size;

	y_buffer_offset = IVTV_DECODER_OFFSET + yuv_offset[frame];
	uv_buffer_offset = y_buffer_offset + IVTV_YUV_BUFFER_UV_OFFSET;

	y_decode_height = uv_decode_height = f->src_h + f->src_y;

	अगर (f->offset_y)
		y_buffer_offset += 720 * 16;

	अगर (y_decode_height & 15)
		y_decode_height = (y_decode_height + 16) & ~15;

	अगर (uv_decode_height & 31)
		uv_decode_height = (uv_decode_height + 32) & ~31;

	y_size = 720 * y_decode_height;

	/* Still in USE */
	अगर (dma->SG_length || dma->page_count) अणु
		IVTV_DEBUG_WARN
		    ("prep_user_dma: SG_length %d page_count %d still full?\n",
		     dma->SG_length, dma->page_count);
		वापस -EBUSY;
	पूर्ण

	ivtv_udma_get_page_info (&y_dma, (अचिन्हित दीर्घ)args->y_source, 720 * y_decode_height);
	ivtv_udma_get_page_info (&uv_dma, (अचिन्हित दीर्घ)args->uv_source, 360 * uv_decode_height);

	/* Pin user pages क्रम DMA Xfer */
	y_pages = pin_user_pages_unlocked(y_dma.uaddr,
			y_dma.page_count, &dma->map[0], FOLL_FORCE);
	uv_pages = 0; /* silence gcc. value is set and consumed only अगर: */
	अगर (y_pages == y_dma.page_count) अणु
		uv_pages = pin_user_pages_unlocked(uv_dma.uaddr,
				uv_dma.page_count, &dma->map[y_pages],
				FOLL_FORCE);
	पूर्ण

	अगर (y_pages != y_dma.page_count || uv_pages != uv_dma.page_count) अणु
		पूर्णांक rc = -EFAULT;

		अगर (y_pages == y_dma.page_count) अणु
			IVTV_DEBUG_WARN
				("failed to map uv user pages, returned %d expecting %d\n",
				 uv_pages, uv_dma.page_count);

			अगर (uv_pages >= 0) अणु
				unpin_user_pages(&dma->map[y_pages], uv_pages);
				rc = -EFAULT;
			पूर्ण अन्यथा अणु
				rc = uv_pages;
			पूर्ण
		पूर्ण अन्यथा अणु
			IVTV_DEBUG_WARN
				("failed to map y user pages, returned %d expecting %d\n",
				 y_pages, y_dma.page_count);
		पूर्ण
		अगर (y_pages >= 0) अणु
			unpin_user_pages(dma->map, y_pages);
			/*
			 * Inherit the -EFAULT from rc's
			 * initialization, but allow it to be
			 * overridden by uv_pages above अगर it was an
			 * actual त्रुटि_सं.
			 */
		पूर्ण अन्यथा अणु
			rc = y_pages;
		पूर्ण
		वापस rc;
	पूर्ण

	dma->page_count = y_pages + uv_pages;

	/* Fill & map SG List */
	अगर (ivtv_udma_fill_sg_list (dma, &uv_dma, ivtv_udma_fill_sg_list (dma, &y_dma, 0)) < 0) अणु
		IVTV_DEBUG_WARN("could not allocate bounce buffers for highmem userspace buffers\n");
		unpin_user_pages(dma->map, dma->page_count);
		dma->page_count = 0;
		वापस -ENOMEM;
	पूर्ण
	dma->SG_length = pci_map_sg(itv->pdev, dma->SGlist, dma->page_count, PCI_DMA_TODEVICE);

	/* Fill SG Array with new values */
	ivtv_udma_fill_sg_array(dma, y_buffer_offset, uv_buffer_offset, y_size);

	/* If we've offset the y plane, ensure top area is blanked */
	अगर (f->offset_y && yi->blanking_dmaptr) अणु
		dma->SGarray[dma->SG_length].size = cpu_to_le32(720*16);
		dma->SGarray[dma->SG_length].src = cpu_to_le32(yi->blanking_dmaptr);
		dma->SGarray[dma->SG_length].dst = cpu_to_le32(IVTV_DECODER_OFFSET + yuv_offset[frame]);
		dma->SG_length++;
	पूर्ण

	/* Tag SG Array with Interrupt Bit */
	dma->SGarray[dma->SG_length - 1].size |= cpu_to_le32(0x80000000);

	ivtv_udma_sync_क्रम_device(itv);
	वापस 0;
पूर्ण

/* We rely on a table held in the firmware - Quick check. */
पूर्णांक ivtv_yuv_filter_check(काष्ठा ivtv *itv)
अणु
	पूर्णांक i, y, uv;

	क्रम (i = 0, y = 16, uv = 4; i < 16; i++, y += 24, uv += 12) अणु
		अगर ((पढ़ो_dec(IVTV_YUV_HORIZONTAL_FILTER_OFFSET + y) != i << 16) ||
		    (पढ़ो_dec(IVTV_YUV_VERTICAL_FILTER_OFFSET + uv) != i << 16)) अणु
			IVTV_WARN ("YUV filter table not found in firmware.\n");
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ivtv_yuv_filter(काष्ठा ivtv *itv, पूर्णांक h_filter, पूर्णांक v_filter_1, पूर्णांक v_filter_2)
अणु
	u32 i, line;

	/* If any filter is -1, then करोn't update it */
	अगर (h_filter > -1) अणु
		अगर (h_filter > 4)
			h_filter = 4;
		i = IVTV_YUV_HORIZONTAL_FILTER_OFFSET + (h_filter * 384);
		क्रम (line = 0; line < 16; line++) अणु
			ग_लिखो_reg(पढ़ो_dec(i), 0x02804);
			ग_लिखो_reg(पढ़ो_dec(i), 0x0281c);
			i += 4;
			ग_लिखो_reg(पढ़ो_dec(i), 0x02808);
			ग_लिखो_reg(पढ़ो_dec(i), 0x02820);
			i += 4;
			ग_लिखो_reg(पढ़ो_dec(i), 0x0280c);
			ग_लिखो_reg(पढ़ो_dec(i), 0x02824);
			i += 4;
			ग_लिखो_reg(पढ़ो_dec(i), 0x02810);
			ग_लिखो_reg(पढ़ो_dec(i), 0x02828);
			i += 4;
			ग_लिखो_reg(पढ़ो_dec(i), 0x02814);
			ग_लिखो_reg(पढ़ो_dec(i), 0x0282c);
			i += 8;
			ग_लिखो_reg(0, 0x02818);
			ग_लिखो_reg(0, 0x02830);
		पूर्ण
		IVTV_DEBUG_YUV("h_filter -> %d\n", h_filter);
	पूर्ण

	अगर (v_filter_1 > -1) अणु
		अगर (v_filter_1 > 4)
			v_filter_1 = 4;
		i = IVTV_YUV_VERTICAL_FILTER_OFFSET + (v_filter_1 * 192);
		क्रम (line = 0; line < 16; line++) अणु
			ग_लिखो_reg(पढ़ो_dec(i), 0x02900);
			i += 4;
			ग_लिखो_reg(पढ़ो_dec(i), 0x02904);
			i += 8;
			ग_लिखो_reg(0, 0x02908);
		पूर्ण
		IVTV_DEBUG_YUV("v_filter_1 -> %d\n", v_filter_1);
	पूर्ण

	अगर (v_filter_2 > -1) अणु
		अगर (v_filter_2 > 4)
			v_filter_2 = 4;
		i = IVTV_YUV_VERTICAL_FILTER_OFFSET + (v_filter_2 * 192);
		क्रम (line = 0; line < 16; line++) अणु
			ग_लिखो_reg(पढ़ो_dec(i), 0x0290c);
			i += 4;
			ग_लिखो_reg(पढ़ो_dec(i), 0x02910);
			i += 8;
			ग_लिखो_reg(0, 0x02914);
		पूर्ण
		IVTV_DEBUG_YUV("v_filter_2 -> %d\n", v_filter_2);
	पूर्ण
पूर्ण

अटल व्योम ivtv_yuv_handle_horizontal(काष्ठा ivtv *itv, काष्ठा yuv_frame_info *f)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	u32 reg_2834, reg_2838, reg_283c;
	u32 reg_2844, reg_2854, reg_285c;
	u32 reg_2864, reg_2874, reg_2890;
	u32 reg_2870, reg_2870_base, reg_2870_offset;
	पूर्णांक x_cutoff;
	पूर्णांक h_filter;
	u32 master_width;

	IVTV_DEBUG_WARN
	    ("Adjust to width %d src_w %d dst_w %d src_x %d dst_x %d\n",
	     f->tru_w, f->src_w, f->dst_w, f->src_x, f->dst_x);

	/* How wide is the src image */
	x_cutoff = f->src_w + f->src_x;

	/* Set the display width */
	reg_2834 = f->dst_w;
	reg_2838 = reg_2834;

	/* Set the display position */
	reg_2890 = f->dst_x;

	/* Index पूर्णांकo the image horizontally */
	reg_2870 = 0;

	/* 2870 is normally fudged to align video coords with osd coords.
	   If running full screen, it causes an unwanted left shअगरt
	   Remove the fudge अगर we almost fill the screen.
	   Gradually adjust the offset to aव्योम the video 'snapping'
	   left/right अगर it माला_लो dragged through this region.
	   Only करो this अगर osd is full width. */
	अगर (f->vis_w == 720) अणु
		अगर ((f->tru_x - f->pan_x > -1) && (f->tru_x - f->pan_x <= 40) && (f->dst_w >= 680))
			reg_2870 = 10 - (f->tru_x - f->pan_x) / 4;
		अन्यथा अगर ((f->tru_x - f->pan_x < 0) && (f->tru_x - f->pan_x >= -20) && (f->dst_w >= 660))
			reg_2870 = (10 + (f->tru_x - f->pan_x) / 2);

		अगर (f->dst_w >= f->src_w)
			reg_2870 = reg_2870 << 16 | reg_2870;
		अन्यथा
			reg_2870 = ((reg_2870 & ~1) << 15) | (reg_2870 & ~1);
	पूर्ण

	अगर (f->dst_w < f->src_w)
		reg_2870 = 0x000d000e - reg_2870;
	अन्यथा
		reg_2870 = 0x0012000e - reg_2870;

	/* We're also using 2870 to shअगरt the image left (src_x & negative dst_x) */
	reg_2870_offset = (f->src_x * ((f->dst_w << 21) / f->src_w)) >> 19;

	अगर (f->dst_w >= f->src_w) अणु
		x_cutoff &= ~1;
		master_width = (f->src_w * 0x00200000) / (f->dst_w);
		अगर (master_width * f->dst_w != f->src_w * 0x00200000)
			master_width++;
		reg_2834 = (reg_2834 << 16) | x_cutoff;
		reg_2838 = (reg_2838 << 16) | x_cutoff;
		reg_283c = master_width >> 2;
		reg_2844 = master_width >> 2;
		reg_2854 = master_width;
		reg_285c = master_width >> 1;
		reg_2864 = master_width >> 1;

		/* We also need to factor in the scaling
		   (src_w - dst_w) / (src_w / 4) */
		अगर (f->dst_w > f->src_w)
			reg_2870_base = ((f->dst_w - f->src_w)<<16) / (f->src_w <<14);
		अन्यथा
			reg_2870_base = 0;

		reg_2870 += (((reg_2870_offset << 14) & 0xFFFF0000) | reg_2870_offset >> 2) + (reg_2870_base << 17 | reg_2870_base);
		reg_2874 = 0;
	पूर्ण अन्यथा अगर (f->dst_w < f->src_w / 2) अणु
		master_width = (f->src_w * 0x00080000) / f->dst_w;
		अगर (master_width * f->dst_w != f->src_w * 0x00080000)
			master_width++;
		reg_2834 = (reg_2834 << 16) | x_cutoff;
		reg_2838 = (reg_2838 << 16) | x_cutoff;
		reg_283c = master_width >> 2;
		reg_2844 = master_width >> 1;
		reg_2854 = master_width;
		reg_285c = master_width >> 1;
		reg_2864 = master_width >> 1;
		reg_2870 += ((reg_2870_offset << 15) & 0xFFFF0000) | reg_2870_offset;
		reg_2870 += (5 - (((f->src_w + f->src_w / 2) - 1) / f->dst_w)) << 16;
		reg_2874 = 0x00000012;
	पूर्ण अन्यथा अणु
		master_width = (f->src_w * 0x00100000) / f->dst_w;
		अगर (master_width * f->dst_w != f->src_w * 0x00100000)
			master_width++;
		reg_2834 = (reg_2834 << 16) | x_cutoff;
		reg_2838 = (reg_2838 << 16) | x_cutoff;
		reg_283c = master_width >> 2;
		reg_2844 = master_width >> 1;
		reg_2854 = master_width;
		reg_285c = master_width >> 1;
		reg_2864 = master_width >> 1;
		reg_2870 += ((reg_2870_offset << 14) & 0xFFFF0000) | reg_2870_offset >> 1;
		reg_2870 += (5 - (((f->src_w * 3) - 1) / f->dst_w)) << 16;
		reg_2874 = 0x00000001;
	पूर्ण

	/* Select the horizontal filter */
	अगर (f->src_w == f->dst_w) अणु
		/* An exact size match uses filter 0 */
		h_filter = 0;
	पूर्ण अन्यथा अणु
		/* Figure out which filter to use */
		h_filter = ((f->src_w << 16) / f->dst_w) >> 15;
		h_filter = (h_filter >> 1) + (h_filter & 1);
		/* Only an exact size match can use filter 0 */
		h_filter += !h_filter;
	पूर्ण

	ग_लिखो_reg(reg_2834, 0x02834);
	ग_लिखो_reg(reg_2838, 0x02838);
	IVTV_DEBUG_YUV("Update reg 0x2834 %08x->%08x 0x2838 %08x->%08x\n",
		       yi->reg_2834, reg_2834, yi->reg_2838, reg_2838);

	ग_लिखो_reg(reg_283c, 0x0283c);
	ग_लिखो_reg(reg_2844, 0x02844);

	IVTV_DEBUG_YUV("Update reg 0x283c %08x->%08x 0x2844 %08x->%08x\n",
		       yi->reg_283c, reg_283c, yi->reg_2844, reg_2844);

	ग_लिखो_reg(0x00080514, 0x02840);
	ग_लिखो_reg(0x00100514, 0x02848);
	IVTV_DEBUG_YUV("Update reg 0x2840 %08x->%08x 0x2848 %08x->%08x\n",
		       yi->reg_2840, 0x00080514, yi->reg_2848, 0x00100514);

	ग_लिखो_reg(reg_2854, 0x02854);
	IVTV_DEBUG_YUV("Update reg 0x2854 %08x->%08x \n",
		       yi->reg_2854, reg_2854);

	ग_लिखो_reg(reg_285c, 0x0285c);
	ग_लिखो_reg(reg_2864, 0x02864);
	IVTV_DEBUG_YUV("Update reg 0x285c %08x->%08x 0x2864 %08x->%08x\n",
		       yi->reg_285c, reg_285c, yi->reg_2864, reg_2864);

	ग_लिखो_reg(reg_2874, 0x02874);
	IVTV_DEBUG_YUV("Update reg 0x2874 %08x->%08x\n",
		       yi->reg_2874, reg_2874);

	ग_लिखो_reg(reg_2870, 0x02870);
	IVTV_DEBUG_YUV("Update reg 0x2870 %08x->%08x\n",
		       yi->reg_2870, reg_2870);

	ग_लिखो_reg(reg_2890, 0x02890);
	IVTV_DEBUG_YUV("Update reg 0x2890 %08x->%08x\n",
		       yi->reg_2890, reg_2890);

	/* Only update the filter अगर we really need to */
	अगर (h_filter != yi->h_filter) अणु
		ivtv_yuv_filter(itv, h_filter, -1, -1);
		yi->h_filter = h_filter;
	पूर्ण
पूर्ण

अटल व्योम ivtv_yuv_handle_vertical(काष्ठा ivtv *itv, काष्ठा yuv_frame_info *f)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	u32 master_height;
	u32 reg_2918, reg_291c, reg_2920, reg_2928;
	u32 reg_2930, reg_2934, reg_293c;
	u32 reg_2940, reg_2944, reg_294c;
	u32 reg_2950, reg_2954, reg_2958, reg_295c;
	u32 reg_2960, reg_2964, reg_2968, reg_296c;
	u32 reg_289c;
	u32 src_major_y, src_minor_y;
	u32 src_major_uv, src_minor_uv;
	u32 reg_2964_base, reg_2968_base;
	पूर्णांक v_filter_1, v_filter_2;

	IVTV_DEBUG_WARN
	    ("Adjust to height %d src_h %d dst_h %d src_y %d dst_y %d\n",
	     f->tru_h, f->src_h, f->dst_h, f->src_y, f->dst_y);

	/* What scaling mode is being used... */
	IVTV_DEBUG_YUV("Scaling mode Y: %s\n",
		       f->पूर्णांकerlaced_y ? "Interlaced" : "Progressive");

	IVTV_DEBUG_YUV("Scaling mode UV: %s\n",
		       f->पूर्णांकerlaced_uv ? "Interlaced" : "Progressive");

	/* What is the source video being treated as... */
	IVTV_DEBUG_WARN("Source video: %s\n",
			f->पूर्णांकerlaced ? "Interlaced" : "Progressive");

	/* We offset पूर्णांकo the image using two dअगरferent index methods, so split
	   the y source coord पूर्णांकo two parts. */
	अगर (f->src_y < 8) अणु
		src_minor_uv = f->src_y;
		src_major_uv = 0;
	पूर्ण अन्यथा अणु
		src_minor_uv = 8;
		src_major_uv = f->src_y - 8;
	पूर्ण

	src_minor_y = src_minor_uv;
	src_major_y = src_major_uv;

	अगर (f->offset_y)
		src_minor_y += 16;

	अगर (f->पूर्णांकerlaced_y)
		reg_2918 = (f->dst_h << 16) | (f->src_h + src_minor_y);
	अन्यथा
		reg_2918 = (f->dst_h << 16) | ((f->src_h + src_minor_y) << 1);

	अगर (f->पूर्णांकerlaced_uv)
		reg_291c = (f->dst_h << 16) | ((f->src_h + src_minor_uv) >> 1);
	अन्यथा
		reg_291c = (f->dst_h << 16) | (f->src_h + src_minor_uv);

	reg_2964_base = (src_minor_y * ((f->dst_h << 16) / f->src_h)) >> 14;
	reg_2968_base = (src_minor_uv * ((f->dst_h << 16) / f->src_h)) >> 14;

	अगर (f->dst_h / 2 >= f->src_h && !f->पूर्णांकerlaced_y) अणु
		master_height = (f->src_h * 0x00400000) / f->dst_h;
		अगर ((f->src_h * 0x00400000) - (master_height * f->dst_h) >= f->dst_h / 2)
			master_height++;
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 3;
		reg_2930 = master_height;
		reg_2940 = master_height >> 1;
		reg_2964_base >>= 3;
		reg_2968_base >>= 3;
		reg_296c = 0x00000000;
	पूर्ण अन्यथा अगर (f->dst_h >= f->src_h) अणु
		master_height = (f->src_h * 0x00400000) / f->dst_h;
		master_height = (master_height >> 1) + (master_height & 1);
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 2;
		reg_2930 = master_height;
		reg_2940 = master_height >> 1;
		reg_296c = 0x00000000;
		अगर (f->पूर्णांकerlaced_y) अणु
			reg_2964_base >>= 3;
		पूर्ण अन्यथा अणु
			reg_296c++;
			reg_2964_base >>= 2;
		पूर्ण
		अगर (f->पूर्णांकerlaced_uv)
			reg_2928 >>= 1;
		reg_2968_base >>= 3;
	पूर्ण अन्यथा अगर (f->dst_h >= f->src_h / 2) अणु
		master_height = (f->src_h * 0x00200000) / f->dst_h;
		master_height = (master_height >> 1) + (master_height & 1);
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 2;
		reg_2930 = master_height;
		reg_2940 = master_height;
		reg_296c = 0x00000101;
		अगर (f->पूर्णांकerlaced_y) अणु
			reg_2964_base >>= 2;
		पूर्ण अन्यथा अणु
			reg_296c++;
			reg_2964_base >>= 1;
		पूर्ण
		अगर (f->पूर्णांकerlaced_uv)
			reg_2928 >>= 1;
		reg_2968_base >>= 2;
	पूर्ण अन्यथा अणु
		master_height = (f->src_h * 0x00100000) / f->dst_h;
		master_height = (master_height >> 1) + (master_height & 1);
		reg_2920 = master_height >> 2;
		reg_2928 = master_height >> 2;
		reg_2930 = master_height;
		reg_2940 = master_height;
		reg_2964_base >>= 1;
		reg_2968_base >>= 2;
		reg_296c = 0x00000102;
	पूर्ण

	/* FIXME These रेजिस्टरs change depending on scaled / unscaled output
	   We really need to work out what they should be */
	अगर (f->src_h == f->dst_h) अणु
		reg_2934 = 0x00020000;
		reg_293c = 0x00100000;
		reg_2944 = 0x00040000;
		reg_294c = 0x000b0000;
	पूर्ण अन्यथा अणु
		reg_2934 = 0x00000FF0;
		reg_293c = 0x00000FF0;
		reg_2944 = 0x00000FF0;
		reg_294c = 0x00000FF0;
	पूर्ण

	/* The first line to be displayed */
	reg_2950 = 0x00010000 + src_major_y;
	अगर (f->पूर्णांकerlaced_y)
		reg_2950 += 0x00010000;
	reg_2954 = reg_2950 + 1;

	reg_2958 = 0x00010000 + (src_major_y >> 1);
	अगर (f->पूर्णांकerlaced_uv)
		reg_2958 += 0x00010000;
	reg_295c = reg_2958 + 1;

	अगर (yi->decode_height == 480)
		reg_289c = 0x011e0017;
	अन्यथा
		reg_289c = 0x01500017;

	अगर (f->dst_y < 0)
		reg_289c = (reg_289c - ((f->dst_y & ~1)<<15))-(f->dst_y >>1);
	अन्यथा
		reg_289c = (reg_289c + ((f->dst_y & ~1)<<15))+(f->dst_y >>1);

	/* How much of the source to decode.
	   Take पूर्णांकo account the source offset */
	reg_2960 = ((src_minor_y + f->src_h + src_major_y) - 1) |
		(((src_minor_uv + f->src_h + src_major_uv - 1) & ~1) << 15);

	/* Calculate correct value क्रम रेजिस्टर 2964 */
	अगर (f->src_h == f->dst_h) अणु
		reg_2964 = 1;
	पूर्ण अन्यथा अणु
		reg_2964 = 2 + ((f->dst_h << 1) / f->src_h);
		reg_2964 = (reg_2964 >> 1) + (reg_2964 & 1);
	पूर्ण
	reg_2968 = (reg_2964 << 16) + reg_2964 + (reg_2964 >> 1);
	reg_2964 = (reg_2964 << 16) + reg_2964 + (reg_2964 * 46 / 94);

	/* Okay, we've wasted समय working out the correct value,
	   but अगर we use it, it fouls the the winकरोw alignment.
	   Fudge it to what we want... */
	reg_2964 = 0x00010001 + ((reg_2964 & 0x0000FFFF) - (reg_2964 >> 16));
	reg_2968 = 0x00010001 + ((reg_2968 & 0x0000FFFF) - (reg_2968 >> 16));

	/* Deviate further from what it should be. I find the flicker headache
	   inducing so try to reduce it slightly. Leave 2968 as-is otherwise
	   colours foul. */
	अगर ((reg_2964 != 0x00010001) && (f->dst_h / 2 <= f->src_h))
		reg_2964 = (reg_2964 & 0xFFFF0000) + ((reg_2964 & 0x0000FFFF) / 2);

	अगर (!f->पूर्णांकerlaced_y)
		reg_2964 -= 0x00010001;
	अगर (!f->पूर्णांकerlaced_uv)
		reg_2968 -= 0x00010001;

	reg_2964 += ((reg_2964_base << 16) | reg_2964_base);
	reg_2968 += ((reg_2968_base << 16) | reg_2968_base);

	/* Select the vertical filter */
	अगर (f->src_h == f->dst_h) अणु
		/* An exact size match uses filter 0/1 */
		v_filter_1 = 0;
		v_filter_2 = 1;
	पूर्ण अन्यथा अणु
		/* Figure out which filter to use */
		v_filter_1 = ((f->src_h << 16) / f->dst_h) >> 15;
		v_filter_1 = (v_filter_1 >> 1) + (v_filter_1 & 1);
		/* Only an exact size match can use filter 0 */
		v_filter_1 += !v_filter_1;
		v_filter_2 = v_filter_1;
	पूर्ण

	ग_लिखो_reg(reg_2934, 0x02934);
	ग_लिखो_reg(reg_293c, 0x0293c);
	IVTV_DEBUG_YUV("Update reg 0x2934 %08x->%08x 0x293c %08x->%08x\n",
		       yi->reg_2934, reg_2934, yi->reg_293c, reg_293c);
	ग_लिखो_reg(reg_2944, 0x02944);
	ग_लिखो_reg(reg_294c, 0x0294c);
	IVTV_DEBUG_YUV("Update reg 0x2944 %08x->%08x 0x294c %08x->%08x\n",
		       yi->reg_2944, reg_2944, yi->reg_294c, reg_294c);

	/* Ensure 2970 is 0 (करोes it ever change ?) */
/*	ग_लिखो_reg(0,0x02970); */
/*	IVTV_DEBUG_YUV("Update reg 0x2970 %08x->%08x\n", yi->reg_2970, 0); */

	ग_लिखो_reg(reg_2930, 0x02938);
	ग_लिखो_reg(reg_2930, 0x02930);
	IVTV_DEBUG_YUV("Update reg 0x2930 %08x->%08x 0x2938 %08x->%08x\n",
		       yi->reg_2930, reg_2930, yi->reg_2938, reg_2930);

	ग_लिखो_reg(reg_2928, 0x02928);
	ग_लिखो_reg(reg_2928 + 0x514, 0x0292C);
	IVTV_DEBUG_YUV("Update reg 0x2928 %08x->%08x 0x292c %08x->%08x\n",
		       yi->reg_2928, reg_2928, yi->reg_292c, reg_2928 + 0x514);

	ग_लिखो_reg(reg_2920, 0x02920);
	ग_लिखो_reg(reg_2920 + 0x514, 0x02924);
	IVTV_DEBUG_YUV("Update reg 0x2920 %08x->%08x 0x2924 %08x->%08x\n",
		       yi->reg_2920, reg_2920, yi->reg_2924, reg_2920 + 0x514);

	ग_लिखो_reg(reg_2918, 0x02918);
	ग_लिखो_reg(reg_291c, 0x0291C);
	IVTV_DEBUG_YUV("Update reg 0x2918 %08x->%08x 0x291C %08x->%08x\n",
		       yi->reg_2918, reg_2918, yi->reg_291c, reg_291c);

	ग_लिखो_reg(reg_296c, 0x0296c);
	IVTV_DEBUG_YUV("Update reg 0x296c %08x->%08x\n",
		       yi->reg_296c, reg_296c);

	ग_लिखो_reg(reg_2940, 0x02948);
	ग_लिखो_reg(reg_2940, 0x02940);
	IVTV_DEBUG_YUV("Update reg 0x2940 %08x->%08x 0x2948 %08x->%08x\n",
		       yi->reg_2940, reg_2940, yi->reg_2948, reg_2940);

	ग_लिखो_reg(reg_2950, 0x02950);
	ग_लिखो_reg(reg_2954, 0x02954);
	IVTV_DEBUG_YUV("Update reg 0x2950 %08x->%08x 0x2954 %08x->%08x\n",
		       yi->reg_2950, reg_2950, yi->reg_2954, reg_2954);

	ग_लिखो_reg(reg_2958, 0x02958);
	ग_लिखो_reg(reg_295c, 0x0295C);
	IVTV_DEBUG_YUV("Update reg 0x2958 %08x->%08x 0x295C %08x->%08x\n",
		       yi->reg_2958, reg_2958, yi->reg_295c, reg_295c);

	ग_लिखो_reg(reg_2960, 0x02960);
	IVTV_DEBUG_YUV("Update reg 0x2960 %08x->%08x \n",
		       yi->reg_2960, reg_2960);

	ग_लिखो_reg(reg_2964, 0x02964);
	ग_लिखो_reg(reg_2968, 0x02968);
	IVTV_DEBUG_YUV("Update reg 0x2964 %08x->%08x 0x2968 %08x->%08x\n",
		       yi->reg_2964, reg_2964, yi->reg_2968, reg_2968);

	ग_लिखो_reg(reg_289c, 0x0289c);
	IVTV_DEBUG_YUV("Update reg 0x289c %08x->%08x\n",
		       yi->reg_289c, reg_289c);

	/* Only update filter 1 अगर we really need to */
	अगर (v_filter_1 != yi->v_filter_1) अणु
		ivtv_yuv_filter(itv, -1, v_filter_1, -1);
		yi->v_filter_1 = v_filter_1;
	पूर्ण

	/* Only update filter 2 अगर we really need to */
	अगर (v_filter_2 != yi->v_filter_2) अणु
		ivtv_yuv_filter(itv, -1, -1, v_filter_2);
		yi->v_filter_2 = v_filter_2;
	पूर्ण
पूर्ण

/* Modअगरy the supplied coordinate inक्रमmation to fit the visible osd area */
अटल u32 ivtv_yuv_winकरोw_setup(काष्ठा ivtv *itv, काष्ठा yuv_frame_info *f)
अणु
	काष्ठा yuv_frame_info *of = &itv->yuv_info.old_frame_info;
	पूर्णांक osd_crop;
	u32 osd_scale;
	u32 yuv_update = 0;

	/* Sorry, but no negative coords क्रम src */
	अगर (f->src_x < 0)
		f->src_x = 0;
	अगर (f->src_y < 0)
		f->src_y = 0;

	/* Can only reduce width करोwn to 1/4 original size */
	अगर ((osd_crop = f->src_w - 4 * f->dst_w) > 0) अणु
		f->src_x += osd_crop / 2;
		f->src_w = (f->src_w - osd_crop) & ~3;
		f->dst_w = f->src_w / 4;
		f->dst_w += f->dst_w & 1;
	पूर्ण

	/* Can only reduce height करोwn to 1/4 original size */
	अगर (f->src_h / f->dst_h >= 2) अणु
		/* Overflow may be because we're running progressive,
		   so क्रमce mode चयन */
		f->पूर्णांकerlaced_y = 1;
		/* Make sure we're still within limits क्रम पूर्णांकerlace */
		अगर ((osd_crop = f->src_h - 4 * f->dst_h) > 0) अणु
			/* If we reach here we'll have to क्रमce the height. */
			f->src_y += osd_crop / 2;
			f->src_h = (f->src_h - osd_crop) & ~3;
			f->dst_h = f->src_h / 4;
			f->dst_h += f->dst_h & 1;
		पूर्ण
	पूर्ण

	/* If there's nothing to safe to display, we may as well stop now */
	अगर ((पूर्णांक)f->dst_w <= 2 || (पूर्णांक)f->dst_h <= 2 ||
	    (पूर्णांक)f->src_w <= 2 || (पूर्णांक)f->src_h <= 2) अणु
		वापस IVTV_YUV_UPDATE_INVALID;
	पूर्ण

	/* Ensure video reमुख्यs inside OSD area */
	osd_scale = (f->src_h << 16) / f->dst_h;

	अगर ((osd_crop = f->pan_y - f->dst_y) > 0) अणु
		/* Falls off the upper edge - crop */
		f->src_y += (osd_scale * osd_crop) >> 16;
		f->src_h -= (osd_scale * osd_crop) >> 16;
		f->dst_h -= osd_crop;
		f->dst_y = 0;
	पूर्ण अन्यथा अणु
		f->dst_y -= f->pan_y;
	पूर्ण

	अगर ((osd_crop = f->dst_h + f->dst_y - f->vis_h) > 0) अणु
		/* Falls off the lower edge - crop */
		f->dst_h -= osd_crop;
		f->src_h -= (osd_scale * osd_crop) >> 16;
	पूर्ण

	osd_scale = (f->src_w << 16) / f->dst_w;

	अगर ((osd_crop = f->pan_x - f->dst_x) > 0) अणु
		/* Fall off the left edge - crop */
		f->src_x += (osd_scale * osd_crop) >> 16;
		f->src_w -= (osd_scale * osd_crop) >> 16;
		f->dst_w -= osd_crop;
		f->dst_x = 0;
	पूर्ण अन्यथा अणु
		f->dst_x -= f->pan_x;
	पूर्ण

	अगर ((osd_crop = f->dst_w + f->dst_x - f->vis_w) > 0) अणु
		/* Falls off the right edge - crop */
		f->dst_w -= osd_crop;
		f->src_w -= (osd_scale * osd_crop) >> 16;
	पूर्ण

	अगर (itv->yuv_info.track_osd) अणु
		/* The OSD can be moved. Track to it */
		f->dst_x += itv->yuv_info.osd_x_offset;
		f->dst_y += itv->yuv_info.osd_y_offset;
	पूर्ण

	/* Width & height क्रम both src & dst must be even.
	   Same क्रम coordinates. */
	f->dst_w &= ~1;
	f->dst_x &= ~1;

	f->src_w += f->src_x & 1;
	f->src_x &= ~1;

	f->src_w &= ~1;
	f->dst_w &= ~1;

	f->dst_h &= ~1;
	f->dst_y &= ~1;

	f->src_h += f->src_y & 1;
	f->src_y &= ~1;

	f->src_h &= ~1;
	f->dst_h &= ~1;

	/* Due to rounding, we may have reduced the output size to <1/4 of
	   the source. Check again, but this समय just resize. Don't change
	   source coordinates */
	अगर (f->dst_w < f->src_w / 4) अणु
		f->src_w &= ~3;
		f->dst_w = f->src_w / 4;
		f->dst_w += f->dst_w & 1;
	पूर्ण
	अगर (f->dst_h < f->src_h / 4) अणु
		f->src_h &= ~3;
		f->dst_h = f->src_h / 4;
		f->dst_h += f->dst_h & 1;
	पूर्ण

	/* Check again. If there's nothing to safe to display, stop now */
	अगर ((पूर्णांक)f->dst_w <= 2 || (पूर्णांक)f->dst_h <= 2 ||
	    (पूर्णांक)f->src_w <= 2 || (पूर्णांक)f->src_h <= 2) अणु
		वापस IVTV_YUV_UPDATE_INVALID;
	पूर्ण

	/* Both x offset & width are linked, so they have to be करोne together */
	अगर ((of->dst_w != f->dst_w) || (of->src_w != f->src_w) ||
	    (of->dst_x != f->dst_x) || (of->src_x != f->src_x) ||
	    (of->pan_x != f->pan_x) || (of->vis_w != f->vis_w)) अणु
		yuv_update |= IVTV_YUV_UPDATE_HORIZONTAL;
	पूर्ण

	अगर ((of->src_h != f->src_h) || (of->dst_h != f->dst_h) ||
	    (of->dst_y != f->dst_y) || (of->src_y != f->src_y) ||
	    (of->pan_y != f->pan_y) || (of->vis_h != f->vis_h) ||
	    (of->lace_mode != f->lace_mode) ||
	    (of->पूर्णांकerlaced_y != f->पूर्णांकerlaced_y) ||
	    (of->पूर्णांकerlaced_uv != f->पूर्णांकerlaced_uv)) अणु
		yuv_update |= IVTV_YUV_UPDATE_VERTICAL;
	पूर्ण

	वापस yuv_update;
पूर्ण

/* Update the scaling रेजिस्टर to the requested value */
व्योम ivtv_yuv_work_handler(काष्ठा ivtv *itv)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	काष्ठा yuv_frame_info f;
	पूर्णांक frame = yi->update_frame;
	u32 yuv_update;

	IVTV_DEBUG_YUV("Update yuv registers for frame %d\n", frame);
	f = yi->new_frame_info[frame];

	अगर (yi->track_osd) अणु
		/* Snapshot the osd pan info */
		f.pan_x = yi->osd_x_pan;
		f.pan_y = yi->osd_y_pan;
		f.vis_w = yi->osd_vis_w;
		f.vis_h = yi->osd_vis_h;
	पूर्ण अन्यथा अणु
		/* Not tracking the osd, so assume full screen */
		f.pan_x = 0;
		f.pan_y = 0;
		f.vis_w = 720;
		f.vis_h = yi->decode_height;
	पूर्ण

	/* Calculate the display winकरोw coordinates. Exit अगर nothing left */
	अगर (!(yuv_update = ivtv_yuv_winकरोw_setup(itv, &f)))
		वापस;

	अगर (yuv_update & IVTV_YUV_UPDATE_INVALID) अणु
		ग_लिखो_reg(0x01008080, 0x2898);
	पूर्ण अन्यथा अगर (yuv_update) अणु
		ग_लिखो_reg(0x00108080, 0x2898);

		अगर (yuv_update & IVTV_YUV_UPDATE_HORIZONTAL)
			ivtv_yuv_handle_horizontal(itv, &f);

		अगर (yuv_update & IVTV_YUV_UPDATE_VERTICAL)
			ivtv_yuv_handle_vertical(itv, &f);
	पूर्ण
	yi->old_frame_info = f;
पूर्ण

अटल व्योम ivtv_yuv_init(काष्ठा ivtv *itv)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;

	IVTV_DEBUG_YUV("ivtv_yuv_init\n");

	/* Take a snapshot of the current रेजिस्टर settings */
	yi->reg_2834 = पढ़ो_reg(0x02834);
	yi->reg_2838 = पढ़ो_reg(0x02838);
	yi->reg_283c = पढ़ो_reg(0x0283c);
	yi->reg_2840 = पढ़ो_reg(0x02840);
	yi->reg_2844 = पढ़ो_reg(0x02844);
	yi->reg_2848 = पढ़ो_reg(0x02848);
	yi->reg_2854 = पढ़ो_reg(0x02854);
	yi->reg_285c = पढ़ो_reg(0x0285c);
	yi->reg_2864 = पढ़ो_reg(0x02864);
	yi->reg_2870 = पढ़ो_reg(0x02870);
	yi->reg_2874 = पढ़ो_reg(0x02874);
	yi->reg_2898 = पढ़ो_reg(0x02898);
	yi->reg_2890 = पढ़ो_reg(0x02890);

	yi->reg_289c = पढ़ो_reg(0x0289c);
	yi->reg_2918 = पढ़ो_reg(0x02918);
	yi->reg_291c = पढ़ो_reg(0x0291c);
	yi->reg_2920 = पढ़ो_reg(0x02920);
	yi->reg_2924 = पढ़ो_reg(0x02924);
	yi->reg_2928 = पढ़ो_reg(0x02928);
	yi->reg_292c = पढ़ो_reg(0x0292c);
	yi->reg_2930 = पढ़ो_reg(0x02930);
	yi->reg_2934 = पढ़ो_reg(0x02934);
	yi->reg_2938 = पढ़ो_reg(0x02938);
	yi->reg_293c = पढ़ो_reg(0x0293c);
	yi->reg_2940 = पढ़ो_reg(0x02940);
	yi->reg_2944 = पढ़ो_reg(0x02944);
	yi->reg_2948 = पढ़ो_reg(0x02948);
	yi->reg_294c = पढ़ो_reg(0x0294c);
	yi->reg_2950 = पढ़ो_reg(0x02950);
	yi->reg_2954 = पढ़ो_reg(0x02954);
	yi->reg_2958 = पढ़ो_reg(0x02958);
	yi->reg_295c = पढ़ो_reg(0x0295c);
	yi->reg_2960 = पढ़ो_reg(0x02960);
	yi->reg_2964 = पढ़ो_reg(0x02964);
	yi->reg_2968 = पढ़ो_reg(0x02968);
	yi->reg_296c = पढ़ो_reg(0x0296c);
	yi->reg_2970 = पढ़ो_reg(0x02970);

	yi->v_filter_1 = -1;
	yi->v_filter_2 = -1;
	yi->h_filter = -1;

	/* Set some valid size info */
	yi->osd_x_offset = पढ़ो_reg(0x02a04) & 0x00000FFF;
	yi->osd_y_offset = (पढ़ो_reg(0x02a04) >> 16) & 0x00000FFF;

	/* Bit 2 of reg 2878 indicates current decoder output क्रमmat
	   0 : NTSC    1 : PAL */
	अगर (पढ़ो_reg(0x2878) & 4)
		yi->decode_height = 576;
	अन्यथा
		yi->decode_height = 480;

	अगर (!itv->osd_info) अणु
		yi->osd_vis_w = 720 - yi->osd_x_offset;
		yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
	पूर्ण अन्यथा अणु
		/* If no visible size set, assume full size */
		अगर (!yi->osd_vis_w)
			yi->osd_vis_w = 720 - yi->osd_x_offset;

		अगर (!yi->osd_vis_h) अणु
			yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
		पूर्ण अन्यथा अगर (yi->osd_vis_h + yi->osd_y_offset > yi->decode_height) अणु
			/* If output video standard has changed, requested height may
			   not be legal */
			IVTV_DEBUG_WARN("Clipping yuv output - fb size (%d) exceeds video standard limit (%d)\n",
					yi->osd_vis_h + yi->osd_y_offset,
					yi->decode_height);
			yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
		पूर्ण
	पूर्ण

	/* We need a buffer क्रम blanking when Y plane is offset - non-fatal अगर we can't get one */
	yi->blanking_ptr = kzalloc(720 * 16, GFP_ATOMIC|__GFP_NOWARN);
	अगर (yi->blanking_ptr) अणु
		yi->blanking_dmaptr = pci_map_single(itv->pdev, yi->blanking_ptr, 720*16, PCI_DMA_TODEVICE);
	पूर्ण अन्यथा अणु
		yi->blanking_dmaptr = 0;
		IVTV_DEBUG_WARN("Failed to allocate yuv blanking buffer\n");
	पूर्ण

	/* Enable YUV decoder output */
	ग_लिखो_reg_sync(0x01, IVTV_REG_VDM);

	set_bit(IVTV_F_I_DECODING_YUV, &itv->i_flags);
	atomic_set(&yi->next_dma_frame, 0);
पूर्ण

/* Get next available yuv buffer on PVR350 */
अटल व्योम ivtv_yuv_next_मुक्त(काष्ठा ivtv *itv)
अणु
	पूर्णांक draw, display;
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;

	अगर (atomic_पढ़ो(&yi->next_dma_frame) == -1)
		ivtv_yuv_init(itv);

	draw = atomic_पढ़ो(&yi->next_fill_frame);
	display = atomic_पढ़ो(&yi->next_dma_frame);

	अगर (display > draw)
		display -= IVTV_YUV_BUFFERS;

	अगर (draw - display >= yi->max_frames_buffered)
		draw = (u8)(draw - 1) % IVTV_YUV_BUFFERS;
	अन्यथा
		yi->new_frame_info[draw].update = 0;

	yi->draw_frame = draw;
पूर्ण

/* Set up frame according to ivtv_dma_frame parameters */
अटल व्योम ivtv_yuv_setup_frame(काष्ठा ivtv *itv, काष्ठा ivtv_dma_frame *args)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	u8 frame = yi->draw_frame;
	u8 last_frame = (u8)(frame - 1) % IVTV_YUV_BUFFERS;
	काष्ठा yuv_frame_info *nf = &yi->new_frame_info[frame];
	काष्ठा yuv_frame_info *of = &yi->new_frame_info[last_frame];
	पूर्णांक lace_threshold = yi->lace_threshold;

	/* Preserve old update flag in हाल we're overwriting a queued frame */
	पूर्णांक update = nf->update;

	/* Take a snapshot of the yuv coordinate inक्रमmation */
	nf->src_x = args->src.left;
	nf->src_y = args->src.top;
	nf->src_w = args->src.width;
	nf->src_h = args->src.height;
	nf->dst_x = args->dst.left;
	nf->dst_y = args->dst.top;
	nf->dst_w = args->dst.width;
	nf->dst_h = args->dst.height;
	nf->tru_x = args->dst.left;
	nf->tru_w = args->src_width;
	nf->tru_h = args->src_height;

	/* Are we going to offset the Y plane */
	nf->offset_y = (nf->tru_h + nf->src_x < 512 - 16) ? 1 : 0;

	nf->update = 0;
	nf->पूर्णांकerlaced_y = 0;
	nf->पूर्णांकerlaced_uv = 0;
	nf->delay = 0;
	nf->sync_field = 0;
	nf->lace_mode = yi->lace_mode & IVTV_YUV_MODE_MASK;

	अगर (lace_threshold < 0)
		lace_threshold = yi->decode_height - 1;

	/* Work out the lace settings */
	चयन (nf->lace_mode) अणु
	हाल IVTV_YUV_MODE_PROGRESSIVE: /* Progressive mode */
		nf->पूर्णांकerlaced = 0;
		अगर (nf->tru_h < 512 || (nf->tru_h > 576 && nf->tru_h < 1021))
			nf->पूर्णांकerlaced_y = 0;
		अन्यथा
			nf->पूर्णांकerlaced_y = 1;

		अगर (nf->tru_h < 1021 && (nf->dst_h >= nf->src_h / 2))
			nf->पूर्णांकerlaced_uv = 0;
		अन्यथा
			nf->पूर्णांकerlaced_uv = 1;
		अवरोध;

	हाल IVTV_YUV_MODE_AUTO:
		अगर (nf->tru_h <= lace_threshold || nf->tru_h > 576 || nf->tru_w > 720) अणु
			nf->पूर्णांकerlaced = 0;
			अगर ((nf->tru_h < 512) ||
			    (nf->tru_h > 576 && nf->tru_h < 1021) ||
			    (nf->tru_w > 720 && nf->tru_h < 1021))
				nf->पूर्णांकerlaced_y = 0;
			अन्यथा
				nf->पूर्णांकerlaced_y = 1;
			अगर (nf->tru_h < 1021 && (nf->dst_h >= nf->src_h / 2))
				nf->पूर्णांकerlaced_uv = 0;
			अन्यथा
				nf->पूर्णांकerlaced_uv = 1;
		पूर्ण अन्यथा अणु
			nf->पूर्णांकerlaced = 1;
			nf->पूर्णांकerlaced_y = 1;
			nf->पूर्णांकerlaced_uv = 1;
		पूर्ण
		अवरोध;

	हाल IVTV_YUV_MODE_INTERLACED: /* Interlace mode */
	शेष:
		nf->पूर्णांकerlaced = 1;
		nf->पूर्णांकerlaced_y = 1;
		nf->पूर्णांकerlaced_uv = 1;
		अवरोध;
	पूर्ण

	अगर (स_भेद(&yi->old_frame_info_args, nf, माप(*nf))) अणु
		yi->old_frame_info_args = *nf;
		nf->update = 1;
		IVTV_DEBUG_YUV("Requesting reg update for frame %d\n", frame);
	पूर्ण

	nf->update |= update;
	nf->sync_field = yi->lace_sync_field;
	nf->delay = nf->sync_field != of->sync_field;
पूर्ण

/* Frame is complete & पढ़ोy क्रम display */
व्योम ivtv_yuv_frame_complete(काष्ठा ivtv *itv)
अणु
	atomic_set(&itv->yuv_info.next_fill_frame,
			(itv->yuv_info.draw_frame + 1) % IVTV_YUV_BUFFERS);
पूर्ण

अटल पूर्णांक ivtv_yuv_udma_frame(काष्ठा ivtv *itv, काष्ठा ivtv_dma_frame *args)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक rc = 0;
	पूर्णांक got_sig = 0;
	/* DMA the frame */
	mutex_lock(&itv->udma.lock);

	अगर ((rc = ivtv_yuv_prep_user_dma(itv, &itv->udma, args)) != 0) अणु
		mutex_unlock(&itv->udma.lock);
		वापस rc;
	पूर्ण

	ivtv_udma_prepare(itv);
	prepare_to_रुको(&itv->dma_रुकोq, &रुको, TASK_INTERRUPTIBLE);
	/* अगर no UDMA is pending and no UDMA is in progress, then the DMA
	   is finished */
	जबतक (test_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags) ||
	       test_bit(IVTV_F_I_UDMA, &itv->i_flags)) अणु
		/* करोn't पूर्णांकerrupt अगर the DMA is in progress but अवरोध off
		   a still pending DMA. */
		got_sig = संकेत_pending(current);
		अगर (got_sig && test_and_clear_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags))
			अवरोध;
		got_sig = 0;
		schedule();
	पूर्ण
	finish_रुको(&itv->dma_रुकोq, &रुको);

	/* Unmap Last DMA Xfer */
	ivtv_udma_unmap(itv);

	अगर (got_sig) अणु
		IVTV_DEBUG_INFO("User stopped YUV UDMA\n");
		mutex_unlock(&itv->udma.lock);
		वापस -EINTR;
	पूर्ण

	ivtv_yuv_frame_complete(itv);

	mutex_unlock(&itv->udma.lock);
	वापस rc;
पूर्ण

/* Setup frame according to V4L2 parameters */
व्योम ivtv_yuv_setup_stream_frame(काष्ठा ivtv *itv)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	काष्ठा ivtv_dma_frame dma_args;

	ivtv_yuv_next_मुक्त(itv);

	/* Copy V4L2 parameters to an ivtv_dma_frame काष्ठा... */
	dma_args.y_source = शून्य;
	dma_args.uv_source = शून्य;
	dma_args.src.left = 0;
	dma_args.src.top = 0;
	dma_args.src.width = yi->v4l2_src_w;
	dma_args.src.height = yi->v4l2_src_h;
	dma_args.dst = yi->मुख्य_rect;
	dma_args.src_width = yi->v4l2_src_w;
	dma_args.src_height = yi->v4l2_src_h;

	/* ... and use the same setup routine as ivtv_yuv_prep_frame */
	ivtv_yuv_setup_frame(itv, &dma_args);

	अगर (!itv->dma_data_req_offset)
		itv->dma_data_req_offset = yuv_offset[yi->draw_frame];
पूर्ण

/* Attempt to dma a frame from a user buffer */
पूर्णांक ivtv_yuv_udma_stream_frame(काष्ठा ivtv *itv, व्योम __user *src)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	काष्ठा ivtv_dma_frame dma_args;
	पूर्णांक res;

	ivtv_yuv_setup_stream_frame(itv);

	/* We only need to supply source addresses क्रम this */
	dma_args.y_source = src;
	dma_args.uv_source = src + 720 * ((yi->v4l2_src_h + 31) & ~31);
	/* Wait क्रम frame DMA. Note that serialize_lock is locked,
	   so to allow other processes to access the driver जबतक
	   we are रुकोing unlock first and later lock again. */
	mutex_unlock(&itv->serialize_lock);
	res = ivtv_yuv_udma_frame(itv, &dma_args);
	mutex_lock(&itv->serialize_lock);
	वापस res;
पूर्ण

/* IVTV_IOC_DMA_FRAME ioctl handler */
पूर्णांक ivtv_yuv_prep_frame(काष्ठा ivtv *itv, काष्ठा ivtv_dma_frame *args)
अणु
	पूर्णांक res;

/*	IVTV_DEBUG_INFO("yuv_prep_frame\n"); */
	ivtv_yuv_next_मुक्त(itv);
	ivtv_yuv_setup_frame(itv, args);
	/* Wait क्रम frame DMA. Note that serialize_lock is locked,
	   so to allow other processes to access the driver जबतक
	   we are रुकोing unlock first and later lock again. */
	mutex_unlock(&itv->serialize_lock);
	res = ivtv_yuv_udma_frame(itv, args);
	mutex_lock(&itv->serialize_lock);
	वापस res;
पूर्ण

व्योम ivtv_yuv_बंद(काष्ठा ivtv *itv)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	पूर्णांक h_filter, v_filter_1, v_filter_2;

	IVTV_DEBUG_YUV("ivtv_yuv_close\n");
	mutex_unlock(&itv->serialize_lock);
	ivtv_रुकोq(&itv->vsync_रुकोq);
	mutex_lock(&itv->serialize_lock);

	yi->running = 0;
	atomic_set(&yi->next_dma_frame, -1);
	atomic_set(&yi->next_fill_frame, 0);

	/* Reset रेजिस्टरs we have changed so mpeg playback works */

	/* If we fully restore this रेजिस्टर, the display may reमुख्य active.
	   Restore, but set one bit to blank the video. Firmware will always
	   clear this bit when needed, so not a problem. */
	ग_लिखो_reg(yi->reg_2898 | 0x01000000, 0x2898);

	ग_लिखो_reg(yi->reg_2834, 0x02834);
	ग_लिखो_reg(yi->reg_2838, 0x02838);
	ग_लिखो_reg(yi->reg_283c, 0x0283c);
	ग_लिखो_reg(yi->reg_2840, 0x02840);
	ग_लिखो_reg(yi->reg_2844, 0x02844);
	ग_लिखो_reg(yi->reg_2848, 0x02848);
	ग_लिखो_reg(yi->reg_2854, 0x02854);
	ग_लिखो_reg(yi->reg_285c, 0x0285c);
	ग_लिखो_reg(yi->reg_2864, 0x02864);
	ग_लिखो_reg(yi->reg_2870, 0x02870);
	ग_लिखो_reg(yi->reg_2874, 0x02874);
	ग_लिखो_reg(yi->reg_2890, 0x02890);
	ग_लिखो_reg(yi->reg_289c, 0x0289c);

	ग_लिखो_reg(yi->reg_2918, 0x02918);
	ग_लिखो_reg(yi->reg_291c, 0x0291c);
	ग_लिखो_reg(yi->reg_2920, 0x02920);
	ग_लिखो_reg(yi->reg_2924, 0x02924);
	ग_लिखो_reg(yi->reg_2928, 0x02928);
	ग_लिखो_reg(yi->reg_292c, 0x0292c);
	ग_लिखो_reg(yi->reg_2930, 0x02930);
	ग_लिखो_reg(yi->reg_2934, 0x02934);
	ग_लिखो_reg(yi->reg_2938, 0x02938);
	ग_लिखो_reg(yi->reg_293c, 0x0293c);
	ग_लिखो_reg(yi->reg_2940, 0x02940);
	ग_लिखो_reg(yi->reg_2944, 0x02944);
	ग_लिखो_reg(yi->reg_2948, 0x02948);
	ग_लिखो_reg(yi->reg_294c, 0x0294c);
	ग_लिखो_reg(yi->reg_2950, 0x02950);
	ग_लिखो_reg(yi->reg_2954, 0x02954);
	ग_लिखो_reg(yi->reg_2958, 0x02958);
	ग_लिखो_reg(yi->reg_295c, 0x0295c);
	ग_लिखो_reg(yi->reg_2960, 0x02960);
	ग_लिखो_reg(yi->reg_2964, 0x02964);
	ग_लिखो_reg(yi->reg_2968, 0x02968);
	ग_लिखो_reg(yi->reg_296c, 0x0296c);
	ग_लिखो_reg(yi->reg_2970, 0x02970);

	/* Prepare to restore filters */

	/* First the horizontal filter */
	अगर ((yi->reg_2834 & 0x0000FFFF) == (yi->reg_2834 >> 16)) अणु
		/* An exact size match uses filter 0 */
		h_filter = 0;
	पूर्ण अन्यथा अणु
		/* Figure out which filter to use */
		h_filter = ((yi->reg_2834 << 16) / (yi->reg_2834 >> 16)) >> 15;
		h_filter = (h_filter >> 1) + (h_filter & 1);
		/* Only an exact size match can use filter 0. */
		h_filter += !h_filter;
	पूर्ण

	/* Now the vertical filter */
	अगर ((yi->reg_2918 & 0x0000FFFF) == (yi->reg_2918 >> 16)) अणु
		/* An exact size match uses filter 0/1 */
		v_filter_1 = 0;
		v_filter_2 = 1;
	पूर्ण अन्यथा अणु
		/* Figure out which filter to use */
		v_filter_1 = ((yi->reg_2918 << 16) / (yi->reg_2918 >> 16)) >> 15;
		v_filter_1 = (v_filter_1 >> 1) + (v_filter_1 & 1);
		/* Only an exact size match can use filter 0 */
		v_filter_1 += !v_filter_1;
		v_filter_2 = v_filter_1;
	पूर्ण

	/* Now restore the filters */
	ivtv_yuv_filter(itv, h_filter, v_filter_1, v_filter_2);

	/* and clear a few रेजिस्टरs */
	ग_लिखो_reg(0, 0x02814);
	ग_लिखो_reg(0, 0x0282c);
	ग_लिखो_reg(0, 0x02904);
	ग_लिखो_reg(0, 0x02910);

	/* Release the blanking buffer */
	अगर (yi->blanking_ptr) अणु
		kमुक्त(yi->blanking_ptr);
		yi->blanking_ptr = शून्य;
		pci_unmap_single(itv->pdev, yi->blanking_dmaptr, 720*16, PCI_DMA_TODEVICE);
	पूर्ण

	/* Invalidate the old dimension inक्रमmation */
	yi->old_frame_info.src_w = 0;
	yi->old_frame_info.src_h = 0;
	yi->old_frame_info_args.src_w = 0;
	yi->old_frame_info_args.src_h = 0;

	/* All करोne. */
	clear_bit(IVTV_F_I_DECODING_YUV, &itv->i_flags);
पूर्ण
