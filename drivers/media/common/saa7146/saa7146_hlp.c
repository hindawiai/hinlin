<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>

अटल व्योम calculate_output_क्रमmat_रेजिस्टर(काष्ठा saa7146_dev* saa, u32 palette, u32* clip_क्रमmat)
अणु
	/* clear out the necessary bits */
	*clip_क्रमmat &= 0x0000ffff;
	/* set these bits new */
	*clip_क्रमmat |=  (( ((palette&0xf00)>>8) << 30) | ((palette&0x00f) << 24) | (((palette&0x0f0)>>4) << 16));
पूर्ण

अटल व्योम calculate_hps_source_and_sync(काष्ठा saa7146_dev *dev, पूर्णांक source, पूर्णांक sync, u32* hps_ctrl)
अणु
	*hps_ctrl &= ~(MASK_30 | MASK_31 | MASK_28);
	*hps_ctrl |= (source << 30) | (sync << 28);
पूर्ण

अटल व्योम calculate_hxo_and_hyo(काष्ठा saa7146_vv *vv, u32* hps_h_scale, u32* hps_ctrl)
अणु
	पूर्णांक hyo = 0, hxo = 0;

	hyo = vv->standard->v_offset;
	hxo = vv->standard->h_offset;

	*hps_h_scale	&= ~(MASK_B0 | 0xf00);
	*hps_h_scale	|= (hxo <<  0);

	*hps_ctrl	&= ~(MASK_W0 | MASK_B2);
	*hps_ctrl	|= (hyo << 12);
पूर्ण

/* helper functions क्रम the calculation of the horizontal- and vertical
   scaling रेजिस्टरs, clip-क्रमmat-रेजिस्टर etc ...
   these functions take poपूर्णांकers to the (most-likely पढ़ो-out
   original-values) and manipulate them according to the requested
   changes.
*/

/* hps_coeff used क्रम CXY and CXUV; scale 1/1 -> scale 1/64 */
अटल काष्ठा अणु
	u16 hps_coeff;
	u16 weight_sum;
पूर्ण hps_h_coeff_tab [] = अणु
	अणु0x00,   2पूर्ण, अणु0x02,   4पूर्ण, अणु0x00,   4पूर्ण, अणु0x06,   8पूर्ण, अणु0x02,   8पूर्ण,
	अणु0x08,   8पूर्ण, अणु0x00,   8पूर्ण, अणु0x1E,  16पूर्ण, अणु0x0E,   8पूर्ण, अणु0x26,   8पूर्ण,
	अणु0x06,   8पूर्ण, अणु0x42,   8पूर्ण, अणु0x02,   8पूर्ण, अणु0x80,   8पूर्ण, अणु0x00,   8पूर्ण,
	अणु0xFE,  16पूर्ण, अणु0xFE,   8पूर्ण, अणु0x7E,   8पूर्ण, अणु0x7E,   8पूर्ण, अणु0x3E,   8पूर्ण,
	अणु0x3E,   8पूर्ण, अणु0x1E,   8पूर्ण, अणु0x1E,   8पूर्ण, अणु0x0E,   8पूर्ण, अणु0x0E,   8पूर्ण,
	अणु0x06,   8पूर्ण, अणु0x06,   8पूर्ण, अणु0x02,   8पूर्ण, अणु0x02,   8पूर्ण, अणु0x00,   8पूर्ण,
	अणु0x00,   8पूर्ण, अणु0xFE,  16पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण,
	अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण,
	अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण,
	अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0xFE,   8पूर्ण, अणु0x7E,   8पूर्ण,
	अणु0x7E,   8पूर्ण, अणु0x3E,   8पूर्ण, अणु0x3E,   8पूर्ण, अणु0x1E,   8पूर्ण, अणु0x1E,   8पूर्ण,
	अणु0x0E,   8पूर्ण, अणु0x0E,   8पूर्ण, अणु0x06,   8पूर्ण, अणु0x06,   8पूर्ण, अणु0x02,   8पूर्ण,
	अणु0x02,   8पूर्ण, अणु0x00,   8पूर्ण, अणु0x00,   8पूर्ण, अणु0xFE,  16पूर्ण
पूर्ण;

/* table of attenuation values क्रम horizontal scaling */
अटल u8 h_attenuation[] = अणु 1, 2, 4, 8, 2, 4, 8, 16, 0पूर्ण;

/* calculate horizontal scale रेजिस्टरs */
अटल पूर्णांक calculate_h_scale_रेजिस्टरs(काष्ठा saa7146_dev *dev,
	पूर्णांक in_x, पूर्णांक out_x, पूर्णांक flip_lr,
	u32* hps_ctrl, u32* hps_v_gain, u32* hps_h_prescale, u32* hps_h_scale)
अणु
	/* horizontal prescaler */
	u32 dcgx = 0, xpsc = 0, xacm = 0, cxy = 0, cxuv = 0;
	/* horizontal scaler */
	u32 xim = 0, xp = 0, xsci =0;
	/* vertical scale & gain */
	u32 pfuv = 0;

	/* helper variables */
	u32 h_atten = 0, i = 0;

	अगर ( 0 == out_x ) अणु
		वापस -EINVAL;
	पूर्ण

	/* mask out vanity-bit */
	*hps_ctrl &= ~MASK_29;

	/* calculate prescale-(xspc)-value:	[n   .. 1/2) : 1
						[1/2 .. 1/3) : 2
						[1/3 .. 1/4) : 3
						...		*/
	अगर (in_x > out_x) अणु
		xpsc = in_x / out_x;
	पूर्ण
	अन्यथा अणु
		/* zooming */
		xpsc = 1;
	पूर्ण

	/* अगर flip_lr-bit is set, number of pixels after
	   horizontal prescaling must be < 384 */
	अगर ( 0 != flip_lr ) अणु

		/* set vanity bit */
		*hps_ctrl |= MASK_29;

		जबतक (in_x / xpsc >= 384 )
			xpsc++;
	पूर्ण
	/* अगर zooming is wanted, number of pixels after
	   horizontal prescaling must be < 768 */
	अन्यथा अणु
		जबतक ( in_x / xpsc >= 768 )
			xpsc++;
	पूर्ण

	/* maximum prescale is 64 (p.69) */
	अगर ( xpsc > 64 )
		xpsc = 64;

	/* keep xacm clear*/
	xacm = 0;

	/* set horizontal filter parameters (CXY = CXUV) */
	cxy = hps_h_coeff_tab[( (xpsc - 1) < 63 ? (xpsc - 1) : 63 )].hps_coeff;
	cxuv = cxy;

	/* calculate and set horizontal fine scale (xsci) */

	/* bypass the horizontal scaler ? */
	अगर ( (in_x == out_x) && ( 1 == xpsc ) )
		xsci = 0x400;
	अन्यथा
		xsci = ( (1024 * in_x) / (out_x * xpsc) ) + xpsc;

	/* set start phase क्रम horizontal fine scale (xp) to 0 */
	xp = 0;

	/* set xim, अगर we bypass the horizontal scaler */
	अगर ( 0x400 == xsci )
		xim = 1;
	अन्यथा
		xim = 0;

	/* अगर the prescaler is bypassed, enable horizontal
	   accumulation mode (xacm) and clear dcgx */
	अगर( 1 == xpsc ) अणु
		xacm = 1;
		dcgx = 0;
	पूर्ण अन्यथा अणु
		xacm = 0;
		/* get best match in the table of attenuations
		   क्रम horizontal scaling */
		h_atten = hps_h_coeff_tab[( (xpsc - 1) < 63 ? (xpsc - 1) : 63 )].weight_sum;

		क्रम (i = 0; h_attenuation[i] != 0; i++) अणु
			अगर (h_attenuation[i] >= h_atten)
				अवरोध;
		पूर्ण

		dcgx = i;
	पूर्ण

	/* the horizontal scaling increment controls the UV filter
	   to reduce the bandwidth to improve the display quality,
	   so set it ... */
	अगर ( xsci == 0x400)
		pfuv = 0x00;
	अन्यथा अगर ( xsci < 0x600)
		pfuv = 0x01;
	अन्यथा अगर ( xsci < 0x680)
		pfuv = 0x11;
	अन्यथा अगर ( xsci < 0x700)
		pfuv = 0x22;
	अन्यथा
		pfuv = 0x33;


	*hps_v_gain  &= MASK_W0|MASK_B2;
	*hps_v_gain  |= (pfuv << 24);

	*hps_h_scale	&= ~(MASK_W1 | 0xf000);
	*hps_h_scale	|= (xim << 31) | (xp << 24) | (xsci << 12);

	*hps_h_prescale	|= (dcgx << 27) | ((xpsc-1) << 18) | (xacm << 17) | (cxy << 8) | (cxuv << 0);

	वापस 0;
पूर्ण

अटल काष्ठा अणु
	u16 hps_coeff;
	u16 weight_sum;
पूर्ण hps_v_coeff_tab [] = अणु
 अणु0x0100,   2पूर्ण,  अणु0x0102,   4पूर्ण,  अणु0x0300,   4पूर्ण,  अणु0x0106,   8पूर्ण,  अणु0x0502,   8पूर्ण,
 अणु0x0708,   8पूर्ण,  अणु0x0F00,   8पूर्ण,  अणु0x011E,  16पूर्ण,  अणु0x110E,  16पूर्ण,  अणु0x1926,  16पूर्ण,
 अणु0x3906,  16पूर्ण,  अणु0x3D42,  16पूर्ण,  अणु0x7D02,  16पूर्ण,  अणु0x7F80,  16पूर्ण,  अणु0xFF00,  16पूर्ण,
 अणु0x01FE,  32पूर्ण,  अणु0x01FE,  32पूर्ण,  अणु0x817E,  32पूर्ण,  अणु0x817E,  32पूर्ण,  अणु0xC13E,  32पूर्ण,
 अणु0xC13E,  32पूर्ण,  अणु0xE11E,  32पूर्ण,  अणु0xE11E,  32पूर्ण,  अणु0xF10E,  32पूर्ण,  अणु0xF10E,  32पूर्ण,
 अणु0xF906,  32पूर्ण,  अणु0xF906,  32पूर्ण,  अणु0xFD02,  32पूर्ण,  अणु0xFD02,  32पूर्ण,  अणु0xFF00,  32पूर्ण,
 अणु0xFF00,  32पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,
 अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,
 अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,
 अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x01FE,  64पूर्ण,  अणु0x817E,  64पूर्ण,
 अणु0x817E,  64पूर्ण,  अणु0xC13E,  64पूर्ण,  अणु0xC13E,  64पूर्ण,  अणु0xE11E,  64पूर्ण,  अणु0xE11E,  64पूर्ण,
 अणु0xF10E,  64पूर्ण,  अणु0xF10E,  64पूर्ण,  अणु0xF906,  64पूर्ण,  अणु0xF906,  64पूर्ण,  अणु0xFD02,  64पूर्ण,
 अणु0xFD02,  64पूर्ण,  अणु0xFF00,  64पूर्ण,  अणु0xFF00,  64पूर्ण,  अणु0x01FE, 128पूर्ण
पूर्ण;

/* table of attenuation values क्रम vertical scaling */
अटल u16 v_attenuation[] = अणु 2, 4, 8, 16, 32, 64, 128, 256, 0पूर्ण;

/* calculate vertical scale रेजिस्टरs */
अटल पूर्णांक calculate_v_scale_रेजिस्टरs(काष्ठा saa7146_dev *dev, क्रमागत v4l2_field field,
	पूर्णांक in_y, पूर्णांक out_y, u32* hps_v_scale, u32* hps_v_gain)
अणु
	पूर्णांक lpi = 0;

	/* vertical scaling */
	u32 yacm = 0, ysci = 0, yacl = 0, ypo = 0, ype = 0;
	/* vertical scale & gain */
	u32 dcgy = 0, cya_cyb = 0;

	/* helper variables */
	u32 v_atten = 0, i = 0;

	/* error, अगर vertical zooming */
	अगर ( in_y < out_y ) अणु
		वापस -EINVAL;
	पूर्ण

	/* linear phase पूर्णांकerpolation may be used
	   अगर scaling is between 1 and 1/2 (both fields used)
	   or scaling is between 1/2 and 1/4 (अगर only one field is used) */

	अगर (V4L2_FIELD_HAS_BOTH(field)) अणु
		अगर( 2*out_y >= in_y) अणु
			lpi = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_TOP
		|| field == V4L2_FIELD_ALTERNATE
		|| field == V4L2_FIELD_BOTTOM) अणु
		अगर( 4*out_y >= in_y ) अणु
			lpi = 1;
		पूर्ण
		out_y *= 2;
	पूर्ण
	अगर( 0 != lpi ) अणु

		yacm = 0;
		yacl = 0;
		cya_cyb = 0x00ff;

		/* calculate scaling increment */
		अगर ( in_y > out_y )
			ysci = ((1024 * in_y) / (out_y + 1)) - 1024;
		अन्यथा
			ysci = 0;

		dcgy = 0;

		/* calculate ype and ypo */
		ype = ysci / 16;
		ypo = ype + (ysci / 64);

	पूर्ण अन्यथा अणु
		yacm = 1;

		/* calculate scaling increment */
		ysci = (((10 * 1024 * (in_y - out_y - 1)) / in_y) + 9) / 10;

		/* calculate ype and ypo */
		ypo = ype = ((ysci + 15) / 16);

		/* the sequence length पूर्णांकerval (yacl) has to be set according
		   to the prescale value, e.g.	[n   .. 1/2) : 0
						[1/2 .. 1/3) : 1
						[1/3 .. 1/4) : 2
						... */
		अगर ( ysci < 512) अणु
			yacl = 0;
		पूर्ण अन्यथा अणु
			yacl = ( ysci / (1024 - ysci) );
		पूर्ण

		/* get filter coefficients क्रम cya, cyb from table hps_v_coeff_tab */
		cya_cyb = hps_v_coeff_tab[ (yacl < 63 ? yacl : 63 ) ].hps_coeff;

		/* get best match in the table of attenuations क्रम vertical scaling */
		v_atten = hps_v_coeff_tab[ (yacl < 63 ? yacl : 63 ) ].weight_sum;

		क्रम (i = 0; v_attenuation[i] != 0; i++) अणु
			अगर (v_attenuation[i] >= v_atten)
				अवरोध;
		पूर्ण

		dcgy = i;
	पूर्ण

	/* ypo and ype swapped in spec ? */
	*hps_v_scale	|= (yacm << 31) | (ysci << 21) | (yacl << 15) | (ypo << 8 ) | (ype << 1);

	*hps_v_gain	&= ~(MASK_W0|MASK_B2);
	*hps_v_gain	|= (dcgy << 16) | (cya_cyb << 0);

	वापस 0;
पूर्ण

/* simple bubble-sort algorithm with duplicate elimination */
अटल पूर्णांक sort_and_eliminate(u32* values, पूर्णांक* count)
अणु
	पूर्णांक low = 0, high = 0, top = 0;
	पूर्णांक cur = 0, next = 0;

	/* sanity checks */
	अगर( (0 > *count) || (शून्य == values) ) अणु
		वापस -EINVAL;
	पूर्ण

	/* bubble sort the first @count items of the array @values */
	क्रम( top = *count; top > 0; top--) अणु
		क्रम( low = 0, high = 1; high < top; low++, high++) अणु
			अगर( values[low] > values[high] )
				swap(values[low], values[high]);
		पूर्ण
	पूर्ण

	/* हटाओ duplicate items */
	क्रम( cur = 0, next = 1; next < *count; next++) अणु
		अगर( values[cur] != values[next])
			values[++cur] = values[next];
	पूर्ण

	*count = cur + 1;

	वापस 0;
पूर्ण

अटल व्योम calculate_clipping_रेजिस्टरs_rect(काष्ठा saa7146_dev *dev, काष्ठा saa7146_fh *fh,
	काष्ठा saa7146_video_dma *vdma2, u32* clip_क्रमmat, u32* arbtr_ctrl, क्रमागत v4l2_field field)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	__le32 *clipping = vv->d_clipping.cpu_addr;

	पूर्णांक width = vv->ov.win.w.width;
	पूर्णांक height =  vv->ov.win.w.height;
	पूर्णांक clipcount = vv->ov.nclips;

	u32 line_list[32];
	u32 pixel_list[32];
	पूर्णांक numdwords = 0;

	पूर्णांक i = 0, j = 0;
	पूर्णांक cnt_line = 0, cnt_pixel = 0;

	पूर्णांक x[32], y[32], w[32], h[32];

	/* clear out memory */
	स_रखो(&line_list[0],  0x00, माप(u32)*32);
	स_रखो(&pixel_list[0], 0x00, माप(u32)*32);
	स_रखो(clipping,  0x00, SAA7146_CLIPPING_MEM);

	/* fill the line and pixel-lists */
	क्रम(i = 0; i < clipcount; i++) अणु
		पूर्णांक l = 0, r = 0, t = 0, b = 0;

		x[i] = vv->ov.clips[i].c.left;
		y[i] = vv->ov.clips[i].c.top;
		w[i] = vv->ov.clips[i].c.width;
		h[i] = vv->ov.clips[i].c.height;

		अगर( w[i] < 0) अणु
			x[i] += w[i]; w[i] = -w[i];
		पूर्ण
		अगर( h[i] < 0) अणु
			y[i] += h[i]; h[i] = -h[i];
		पूर्ण
		अगर( x[i] < 0) अणु
			w[i] += x[i]; x[i] = 0;
		पूर्ण
		अगर( y[i] < 0) अणु
			h[i] += y[i]; y[i] = 0;
		पूर्ण
		अगर( 0 != vv->vflip ) अणु
			y[i] = height - y[i] - h[i];
		पूर्ण

		l = x[i];
		r = x[i]+w[i];
		t = y[i];
		b = y[i]+h[i];

		/* insert left/right coordinates */
		pixel_list[ 2*i   ] = min_t(पूर्णांक, l, width);
		pixel_list[(2*i)+1] = min_t(पूर्णांक, r, width);
		/* insert top/bottom coordinates */
		line_list[ 2*i   ] = min_t(पूर्णांक, t, height);
		line_list[(2*i)+1] = min_t(पूर्णांक, b, height);
	पूर्ण

	/* sort and eliminate lists */
	cnt_line = cnt_pixel = 2*clipcount;
	sort_and_eliminate( &pixel_list[0], &cnt_pixel );
	sort_and_eliminate( &line_list[0], &cnt_line );

	/* calculate the number of used u32s */
	numdwords = max_t(पूर्णांक, (cnt_line+1), (cnt_pixel+1))*2;
	numdwords = max_t(पूर्णांक, 4, numdwords);
	numdwords = min_t(पूर्णांक, 64, numdwords);

	/* fill up cliptable */
	क्रम(i = 0; i < cnt_pixel; i++) अणु
		clipping[2*i] |= cpu_to_le32(pixel_list[i] << 16);
	पूर्ण
	क्रम(i = 0; i < cnt_line; i++) अणु
		clipping[(2*i)+1] |= cpu_to_le32(line_list[i] << 16);
	पूर्ण

	/* fill up cliptable with the display infos */
	क्रम(j = 0; j < clipcount; j++) अणु

		क्रम(i = 0; i < cnt_pixel; i++) अणु

			अगर( x[j] < 0)
				x[j] = 0;

			अगर( pixel_list[i] < (x[j] + w[j])) अणु

				अगर ( pixel_list[i] >= x[j] ) अणु
					clipping[2*i] |= cpu_to_le32(1 << j);
				पूर्ण
			पूर्ण
		पूर्ण
		क्रम(i = 0; i < cnt_line; i++) अणु

			अगर( y[j] < 0)
				y[j] = 0;

			अगर( line_list[i] < (y[j] + h[j]) ) अणु

				अगर( line_list[i] >= y[j] ) अणु
					clipping[(2*i)+1] |= cpu_to_le32(1 << j);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* adjust arbitration control रेजिस्टर */
	*arbtr_ctrl &= 0xffff00ff;
	*arbtr_ctrl |= 0x00001c00;

	vdma2->base_even	= vv->d_clipping.dma_handle;
	vdma2->base_odd		= vv->d_clipping.dma_handle;
	vdma2->prot_addr	= vv->d_clipping.dma_handle+((माप(u32))*(numdwords));
	vdma2->base_page	= 0x04;
	vdma2->pitch		= 0x00;
	vdma2->num_line_byte	= (0 << 16 | (माप(u32))*(numdwords-1) );

	/* set clipping-mode. this depends on the field(s) used */
	*clip_क्रमmat &= 0xfffffff7;
	अगर (V4L2_FIELD_HAS_BOTH(field)) अणु
		*clip_क्रमmat |= 0x00000008;
	पूर्ण अन्यथा अणु
		*clip_क्रमmat |= 0x00000000;
	पूर्ण
पूर्ण

/* disable clipping */
अटल व्योम saa7146_disable_clipping(काष्ठा saa7146_dev *dev)
अणु
	u32 clip_क्रमmat	= saa7146_पढ़ो(dev, CLIP_FORMAT_CTRL);

	/* mask out relevant bits (=lower word)*/
	clip_क्रमmat &= MASK_W1;

	/* upload clipping-रेजिस्टरs*/
	saa7146_ग_लिखो(dev, CLIP_FORMAT_CTRL,clip_क्रमmat);
	saa7146_ग_लिखो(dev, MC2, (MASK_05 | MASK_21));

	/* disable video dma2 */
	saa7146_ग_लिखो(dev, MC1, MASK_21);
पूर्ण

अटल व्योम saa7146_set_clipping_rect(काष्ठा saa7146_fh *fh)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	क्रमागत v4l2_field field = vv->ov.win.field;
	काष्ठा	saa7146_video_dma vdma2;
	u32 clip_क्रमmat;
	u32 arbtr_ctrl;

	/* check clipcount, disable clipping अगर clipcount == 0*/
	अगर (vv->ov.nclips == 0) अणु
		saa7146_disable_clipping(dev);
		वापस;
	पूर्ण

	clip_क्रमmat = saa7146_पढ़ो(dev, CLIP_FORMAT_CTRL);
	arbtr_ctrl = saa7146_पढ़ो(dev, PCI_BT_V1);

	calculate_clipping_रेजिस्टरs_rect(dev, fh, &vdma2, &clip_क्रमmat, &arbtr_ctrl, field);

	/* set clipping क्रमmat */
	clip_क्रमmat &= 0xffff0008;
	clip_क्रमmat |= (SAA7146_CLIPPING_RECT << 4);

	/* prepare video dma2 */
	saa7146_ग_लिखो(dev, BASE_EVEN2,		vdma2.base_even);
	saa7146_ग_लिखो(dev, BASE_ODD2,		vdma2.base_odd);
	saa7146_ग_लिखो(dev, PROT_ADDR2,		vdma2.prot_addr);
	saa7146_ग_लिखो(dev, BASE_PAGE2,		vdma2.base_page);
	saa7146_ग_लिखो(dev, PITCH2,		vdma2.pitch);
	saa7146_ग_लिखो(dev, NUM_LINE_BYTE2,	vdma2.num_line_byte);

	/* prepare the rest */
	saa7146_ग_लिखो(dev, CLIP_FORMAT_CTRL,clip_क्रमmat);
	saa7146_ग_लिखो(dev, PCI_BT_V1, arbtr_ctrl);

	/* upload clip_control-रेजिस्टर, clipping-रेजिस्टरs, enable video dma2 */
	saa7146_ग_लिखो(dev, MC2, (MASK_05 | MASK_21 | MASK_03 | MASK_19));
	saa7146_ग_लिखो(dev, MC1, (MASK_05 | MASK_21));
पूर्ण

अटल व्योम saa7146_set_winकरोw(काष्ठा saa7146_dev *dev, पूर्णांक width, पूर्णांक height, क्रमागत v4l2_field field)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;

	पूर्णांक source = vv->current_hps_source;
	पूर्णांक sync = vv->current_hps_sync;

	u32 hps_v_scale = 0, hps_v_gain  = 0, hps_ctrl = 0, hps_h_prescale = 0, hps_h_scale = 0;

	/* set vertical scale */
	hps_v_scale = 0; /* all bits get set by the function-call */
	hps_v_gain  = 0; /* fixme: saa7146_पढ़ो(dev, HPS_V_GAIN);*/
	calculate_v_scale_रेजिस्टरs(dev, field, vv->standard->v_field*2, height, &hps_v_scale, &hps_v_gain);

	/* set horizontal scale */
	hps_ctrl	= 0;
	hps_h_prescale	= 0; /* all bits get set in the function */
	hps_h_scale	= 0;
	calculate_h_scale_रेजिस्टरs(dev, vv->standard->h_pixels, width, vv->hflip, &hps_ctrl, &hps_v_gain, &hps_h_prescale, &hps_h_scale);

	/* set hyo and hxo */
	calculate_hxo_and_hyo(vv, &hps_h_scale, &hps_ctrl);
	calculate_hps_source_and_sync(dev, source, sync, &hps_ctrl);

	/* ग_लिखो out new रेजिस्टर contents */
	saa7146_ग_लिखो(dev, HPS_V_SCALE,	hps_v_scale);
	saa7146_ग_लिखो(dev, HPS_V_GAIN,	hps_v_gain);
	saa7146_ग_लिखो(dev, HPS_CTRL,	hps_ctrl);
	saa7146_ग_लिखो(dev, HPS_H_PRESCALE,hps_h_prescale);
	saa7146_ग_लिखो(dev, HPS_H_SCALE,	hps_h_scale);

	/* upload shaकरोw-ram रेजिस्टरs */
	saa7146_ग_लिखो(dev, MC2, (MASK_05 | MASK_06 | MASK_21 | MASK_22) );
पूर्ण

/* calculate the new memory offsets क्रम a desired position */
अटल व्योम saa7146_set_position(काष्ठा saa7146_dev *dev, पूर्णांक w_x, पूर्णांक w_y, पूर्णांक w_height, क्रमागत v4l2_field field, u32 pixelक्रमmat)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_क्रमmat *sfmt = saa7146_क्रमmat_by_fourcc(dev, pixelक्रमmat);

	पूर्णांक b_depth = vv->ov_fmt->depth;
	पूर्णांक b_bpl = vv->ov_fb.fmt.bytesperline;
	/* The अचिन्हित दीर्घ cast is to हटाओ a 64-bit compile warning since
	   it looks like a 64-bit address is cast to a 32-bit value, even
	   though the base poपूर्णांकer is really a 32-bit physical address that
	   goes पूर्णांकo a 32-bit DMA रेजिस्टर.
	   FIXME: might not work on some 64-bit platक्रमms, but see the FIXME
	   in काष्ठा v4l2_framebuffer (videodev2.h) क्रम that.
	 */
	u32 base = (u32)(अचिन्हित दीर्घ)vv->ov_fb.base;

	काष्ठा	saa7146_video_dma vdma1;

	/* calculate memory offsets क्रम picture, look अगर we shall top-करोwn-flip */
	vdma1.pitch	= 2*b_bpl;
	अगर ( 0 == vv->vflip ) अणु
		vdma1.base_even = base + (w_y * (vdma1.pitch/2)) + (w_x * (b_depth / 8));
		vdma1.base_odd  = vdma1.base_even + (vdma1.pitch / 2);
		vdma1.prot_addr = vdma1.base_even + (w_height * (vdma1.pitch / 2));
	पूर्ण
	अन्यथा अणु
		vdma1.base_even = base + ((w_y+w_height) * (vdma1.pitch/2)) + (w_x * (b_depth / 8));
		vdma1.base_odd  = vdma1.base_even - (vdma1.pitch / 2);
		vdma1.prot_addr = vdma1.base_odd - (w_height * (vdma1.pitch / 2));
	पूर्ण

	अगर (V4L2_FIELD_HAS_BOTH(field)) अणु
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_ALTERNATE) अणु
		/* fixme */
		vdma1.base_odd = vdma1.prot_addr;
		vdma1.pitch /= 2;
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_TOP) अणु
		vdma1.base_odd = vdma1.prot_addr;
		vdma1.pitch /= 2;
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_BOTTOM) अणु
		vdma1.base_odd = vdma1.base_even;
		vdma1.base_even = vdma1.prot_addr;
		vdma1.pitch /= 2;
	पूर्ण

	अगर ( 0 != vv->vflip ) अणु
		vdma1.pitch *= -1;
	पूर्ण

	vdma1.base_page = sfmt->swap;
	vdma1.num_line_byte = (vv->standard->v_field<<16)+vv->standard->h_pixels;

	saa7146_ग_लिखो_out_dma(dev, 1, &vdma1);
पूर्ण

अटल व्योम saa7146_set_output_क्रमmat(काष्ठा saa7146_dev *dev, अचिन्हित दीर्घ palette)
अणु
	u32 clip_क्रमmat = saa7146_पढ़ो(dev, CLIP_FORMAT_CTRL);

	/* call helper function */
	calculate_output_क्रमmat_रेजिस्टर(dev,palette,&clip_क्रमmat);

	/* update the hps रेजिस्टरs */
	saa7146_ग_लिखो(dev, CLIP_FORMAT_CTRL, clip_क्रमmat);
	saa7146_ग_लिखो(dev, MC2, (MASK_05 | MASK_21));
पूर्ण

/* select input-source */
व्योम saa7146_set_hps_source_and_sync(काष्ठा saa7146_dev *dev, पूर्णांक source, पूर्णांक sync)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	u32 hps_ctrl = 0;

	/* पढ़ो old state */
	hps_ctrl = saa7146_पढ़ो(dev, HPS_CTRL);

	hps_ctrl &= ~( MASK_31 | MASK_30 | MASK_28 );
	hps_ctrl |= (source << 30) | (sync << 28);

	/* ग_लिखो back & upload रेजिस्टर */
	saa7146_ग_लिखो(dev, HPS_CTRL, hps_ctrl);
	saa7146_ग_लिखो(dev, MC2, (MASK_05 | MASK_21));

	vv->current_hps_source = source;
	vv->current_hps_sync = sync;
पूर्ण
EXPORT_SYMBOL_GPL(saa7146_set_hps_source_and_sync);

पूर्णांक saa7146_enable_overlay(काष्ठा saa7146_fh *fh)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	saa7146_set_winकरोw(dev, vv->ov.win.w.width, vv->ov.win.w.height, vv->ov.win.field);
	saa7146_set_position(dev, vv->ov.win.w.left, vv->ov.win.w.top, vv->ov.win.w.height, vv->ov.win.field, vv->ov_fmt->pixelक्रमmat);
	saa7146_set_output_क्रमmat(dev, vv->ov_fmt->trans);
	saa7146_set_clipping_rect(fh);

	/* enable video dma1 */
	saa7146_ग_लिखो(dev, MC1, (MASK_06 | MASK_22));
	वापस 0;
पूर्ण

व्योम saa7146_disable_overlay(काष्ठा saa7146_fh *fh)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;

	/* disable clipping + video dma1 */
	saa7146_disable_clipping(dev);
	saa7146_ग_लिखो(dev, MC1, MASK_22);
पूर्ण

व्योम saa7146_ग_लिखो_out_dma(काष्ठा saa7146_dev* dev, पूर्णांक which, काष्ठा saa7146_video_dma* vdma)
अणु
	पूर्णांक where = 0;

	अगर( which < 1 || which > 3) अणु
		वापस;
	पूर्ण

	/* calculate starting address */
	where  = (which-1)*0x18;

	saa7146_ग_लिखो(dev, where,	vdma->base_odd);
	saa7146_ग_लिखो(dev, where+0x04,	vdma->base_even);
	saa7146_ग_लिखो(dev, where+0x08,	vdma->prot_addr);
	saa7146_ग_लिखो(dev, where+0x0c,	vdma->pitch);
	saa7146_ग_लिखो(dev, where+0x10,	vdma->base_page);
	saa7146_ग_लिखो(dev, where+0x14,	vdma->num_line_byte);

	/* upload */
	saa7146_ग_लिखो(dev, MC2, (MASK_02<<(which-1))|(MASK_18<<(which-1)));
/*
	prपूर्णांकk("vdma%d.base_even:     0x%08x\n", which,vdma->base_even);
	prपूर्णांकk("vdma%d.base_odd:      0x%08x\n", which,vdma->base_odd);
	prपूर्णांकk("vdma%d.prot_addr:     0x%08x\n", which,vdma->prot_addr);
	prपूर्णांकk("vdma%d.base_page:     0x%08x\n", which,vdma->base_page);
	prपूर्णांकk("vdma%d.pitch:         0x%08x\n", which,vdma->pitch);
	prपूर्णांकk("vdma%d.num_line_byte: 0x%08x\n", which,vdma->num_line_byte);
*/
पूर्ण

अटल पूर्णांक calculate_video_dma_grab_packed(काष्ठा saa7146_dev* dev, काष्ठा saa7146_buf *buf)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_video_dma vdma1;

	काष्ठा saa7146_क्रमmat *sfmt = saa7146_क्रमmat_by_fourcc(dev,buf->fmt->pixelक्रमmat);

	पूर्णांक width = buf->fmt->width;
	पूर्णांक height = buf->fmt->height;
	पूर्णांक bytesperline = buf->fmt->bytesperline;
	क्रमागत v4l2_field field = buf->fmt->field;

	पूर्णांक depth = sfmt->depth;

	DEB_CAP("[size=%dx%d,fields=%s]\n",
		width, height, v4l2_field_names[field]);

	अगर( bytesperline != 0) अणु
		vdma1.pitch = bytesperline*2;
	पूर्ण अन्यथा अणु
		vdma1.pitch = (width*depth*2)/8;
	पूर्ण
	vdma1.num_line_byte	= ((vv->standard->v_field<<16) + vv->standard->h_pixels);
	vdma1.base_page		= buf->pt[0].dma | ME1 | sfmt->swap;

	अगर( 0 != vv->vflip ) अणु
		vdma1.prot_addr	= buf->pt[0].offset;
		vdma1.base_even	= buf->pt[0].offset+(vdma1.pitch/2)*height;
		vdma1.base_odd	= vdma1.base_even - (vdma1.pitch/2);
	पूर्ण अन्यथा अणु
		vdma1.base_even	= buf->pt[0].offset;
		vdma1.base_odd	= vdma1.base_even + (vdma1.pitch/2);
		vdma1.prot_addr	= buf->pt[0].offset+(vdma1.pitch/2)*height;
	पूर्ण

	अगर (V4L2_FIELD_HAS_BOTH(field)) अणु
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_ALTERNATE) अणु
		/* fixme */
		अगर ( vv->last_field == V4L2_FIELD_TOP ) अणु
			vdma1.base_odd	= vdma1.prot_addr;
			vdma1.pitch /= 2;
		पूर्ण अन्यथा अगर ( vv->last_field == V4L2_FIELD_BOTTOM ) अणु
			vdma1.base_odd	= vdma1.base_even;
			vdma1.base_even = vdma1.prot_addr;
			vdma1.pitch /= 2;
		पूर्ण
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_TOP) अणु
		vdma1.base_odd	= vdma1.prot_addr;
		vdma1.pitch /= 2;
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_BOTTOM) अणु
		vdma1.base_odd	= vdma1.base_even;
		vdma1.base_even = vdma1.prot_addr;
		vdma1.pitch /= 2;
	पूर्ण

	अगर( 0 != vv->vflip ) अणु
		vdma1.pitch *= -1;
	पूर्ण

	saa7146_ग_लिखो_out_dma(dev, 1, &vdma1);
	वापस 0;
पूर्ण

अटल पूर्णांक calc_planar_422(काष्ठा saa7146_vv *vv, काष्ठा saa7146_buf *buf, काष्ठा saa7146_video_dma *vdma2, काष्ठा saa7146_video_dma *vdma3)
अणु
	पूर्णांक height = buf->fmt->height;
	पूर्णांक width = buf->fmt->width;

	vdma2->pitch	= width;
	vdma3->pitch	= width;

	/* fixme: look at bytesperline! */

	अगर( 0 != vv->vflip ) अणु
		vdma2->prot_addr	= buf->pt[1].offset;
		vdma2->base_even	= ((vdma2->pitch/2)*height)+buf->pt[1].offset;
		vdma2->base_odd		= vdma2->base_even - (vdma2->pitch/2);

		vdma3->prot_addr	= buf->pt[2].offset;
		vdma3->base_even	= ((vdma3->pitch/2)*height)+buf->pt[2].offset;
		vdma3->base_odd		= vdma3->base_even - (vdma3->pitch/2);
	पूर्ण अन्यथा अणु
		vdma3->base_even	= buf->pt[2].offset;
		vdma3->base_odd		= vdma3->base_even + (vdma3->pitch/2);
		vdma3->prot_addr	= (vdma3->pitch/2)*height+buf->pt[2].offset;

		vdma2->base_even	= buf->pt[1].offset;
		vdma2->base_odd		= vdma2->base_even + (vdma2->pitch/2);
		vdma2->prot_addr	= (vdma2->pitch/2)*height+buf->pt[1].offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक calc_planar_420(काष्ठा saa7146_vv *vv, काष्ठा saa7146_buf *buf, काष्ठा saa7146_video_dma *vdma2, काष्ठा saa7146_video_dma *vdma3)
अणु
	पूर्णांक height = buf->fmt->height;
	पूर्णांक width = buf->fmt->width;

	vdma2->pitch	= width/2;
	vdma3->pitch	= width/2;

	अगर( 0 != vv->vflip ) अणु
		vdma2->prot_addr	= buf->pt[2].offset;
		vdma2->base_even	= ((vdma2->pitch/2)*height)+buf->pt[2].offset;
		vdma2->base_odd		= vdma2->base_even - (vdma2->pitch/2);

		vdma3->prot_addr	= buf->pt[1].offset;
		vdma3->base_even	= ((vdma3->pitch/2)*height)+buf->pt[1].offset;
		vdma3->base_odd		= vdma3->base_even - (vdma3->pitch/2);

	पूर्ण अन्यथा अणु
		vdma3->base_even	= buf->pt[2].offset;
		vdma3->base_odd		= vdma3->base_even + (vdma3->pitch);
		vdma3->prot_addr	= (vdma3->pitch/2)*height+buf->pt[2].offset;

		vdma2->base_even	= buf->pt[1].offset;
		vdma2->base_odd		= vdma2->base_even + (vdma2->pitch);
		vdma2->prot_addr	= (vdma2->pitch/2)*height+buf->pt[1].offset;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक calculate_video_dma_grab_planar(काष्ठा saa7146_dev* dev, काष्ठा saa7146_buf *buf)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_video_dma vdma1;
	काष्ठा saa7146_video_dma vdma2;
	काष्ठा saa7146_video_dma vdma3;

	काष्ठा saa7146_क्रमmat *sfmt = saa7146_क्रमmat_by_fourcc(dev,buf->fmt->pixelक्रमmat);

	पूर्णांक width = buf->fmt->width;
	पूर्णांक height = buf->fmt->height;
	क्रमागत v4l2_field field = buf->fmt->field;

	BUG_ON(0 == buf->pt[0].dma);
	BUG_ON(0 == buf->pt[1].dma);
	BUG_ON(0 == buf->pt[2].dma);

	DEB_CAP("[size=%dx%d,fields=%s]\n",
		width, height, v4l2_field_names[field]);

	/* fixme: look at bytesperline! */

	/* fixme: what happens क्रम user space buffers here?. The offsets are
	   most likely wrong, this version here only works क्रम page-aligned
	   buffers, modअगरications to the pagetable-functions are necessary...*/

	vdma1.pitch		= width*2;
	vdma1.num_line_byte	= ((vv->standard->v_field<<16) + vv->standard->h_pixels);
	vdma1.base_page		= buf->pt[0].dma | ME1;

	अगर( 0 != vv->vflip ) अणु
		vdma1.prot_addr	= buf->pt[0].offset;
		vdma1.base_even	= ((vdma1.pitch/2)*height)+buf->pt[0].offset;
		vdma1.base_odd	= vdma1.base_even - (vdma1.pitch/2);
	पूर्ण अन्यथा अणु
		vdma1.base_even	= buf->pt[0].offset;
		vdma1.base_odd	= vdma1.base_even + (vdma1.pitch/2);
		vdma1.prot_addr	= (vdma1.pitch/2)*height+buf->pt[0].offset;
	पूर्ण

	vdma2.num_line_byte	= 0; /* unused */
	vdma2.base_page		= buf->pt[1].dma | ME1;

	vdma3.num_line_byte	= 0; /* unused */
	vdma3.base_page		= buf->pt[2].dma | ME1;

	चयन( sfmt->depth ) अणु
		हाल 12: अणु
			calc_planar_420(vv,buf,&vdma2,&vdma3);
			अवरोध;
		पूर्ण
		हाल 16: अणु
			calc_planar_422(vv,buf,&vdma2,&vdma3);
			अवरोध;
		पूर्ण
		शेष: अणु
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (V4L2_FIELD_HAS_BOTH(field)) अणु
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_ALTERNATE) अणु
		/* fixme */
		vdma1.base_odd	= vdma1.prot_addr;
		vdma1.pitch /= 2;
		vdma2.base_odd	= vdma2.prot_addr;
		vdma2.pitch /= 2;
		vdma3.base_odd	= vdma3.prot_addr;
		vdma3.pitch /= 2;
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_TOP) अणु
		vdma1.base_odd	= vdma1.prot_addr;
		vdma1.pitch /= 2;
		vdma2.base_odd	= vdma2.prot_addr;
		vdma2.pitch /= 2;
		vdma3.base_odd	= vdma3.prot_addr;
		vdma3.pitch /= 2;
	पूर्ण अन्यथा अगर (field == V4L2_FIELD_BOTTOM) अणु
		vdma1.base_odd	= vdma1.base_even;
		vdma1.base_even = vdma1.prot_addr;
		vdma1.pitch /= 2;
		vdma2.base_odd	= vdma2.base_even;
		vdma2.base_even = vdma2.prot_addr;
		vdma2.pitch /= 2;
		vdma3.base_odd	= vdma3.base_even;
		vdma3.base_even = vdma3.prot_addr;
		vdma3.pitch /= 2;
	पूर्ण

	अगर( 0 != vv->vflip ) अणु
		vdma1.pitch *= -1;
		vdma2.pitch *= -1;
		vdma3.pitch *= -1;
	पूर्ण

	saa7146_ग_लिखो_out_dma(dev, 1, &vdma1);
	अगर( (sfmt->flags & FORMAT_BYTE_SWAP) != 0 ) अणु
		saa7146_ग_लिखो_out_dma(dev, 3, &vdma2);
		saa7146_ग_लिखो_out_dma(dev, 2, &vdma3);
	पूर्ण अन्यथा अणु
		saa7146_ग_लिखो_out_dma(dev, 2, &vdma2);
		saa7146_ग_लिखो_out_dma(dev, 3, &vdma3);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम program_capture_engine(काष्ठा saa7146_dev *dev, पूर्णांक planar)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	पूर्णांक count = 0;

	अचिन्हित दीर्घ e_रुको = vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? CMD_E_FID_A : CMD_E_FID_B;
	अचिन्हित दीर्घ o_रुको = vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? CMD_O_FID_A : CMD_O_FID_B;

	/* रुको क्रम o_fid_a/b / e_fid_a/b toggle only अगर rps रेजिस्टर 0 is not set*/
	WRITE_RPS0(CMD_PAUSE | CMD_OAN | CMD_SIG0 | o_रुको);
	WRITE_RPS0(CMD_PAUSE | CMD_OAN | CMD_SIG0 | e_रुको);

	/* set rps रेजिस्टर 0 */
	WRITE_RPS0(CMD_WR_REG | (1 << 8) | (MC2/4));
	WRITE_RPS0(MASK_27 | MASK_11);

	/* turn on video-dma1 */
	WRITE_RPS0(CMD_WR_REG_MASK | (MC1/4));
	WRITE_RPS0(MASK_06 | MASK_22);			/* => mask */
	WRITE_RPS0(MASK_06 | MASK_22);			/* => values */
	अगर( 0 != planar ) अणु
		/* turn on video-dma2 */
		WRITE_RPS0(CMD_WR_REG_MASK | (MC1/4));
		WRITE_RPS0(MASK_05 | MASK_21);			/* => mask */
		WRITE_RPS0(MASK_05 | MASK_21);			/* => values */

		/* turn on video-dma3 */
		WRITE_RPS0(CMD_WR_REG_MASK | (MC1/4));
		WRITE_RPS0(MASK_04 | MASK_20);			/* => mask */
		WRITE_RPS0(MASK_04 | MASK_20);			/* => values */
	पूर्ण

	/* रुको क्रम o_fid_a/b / e_fid_a/b toggle */
	अगर ( vv->last_field == V4L2_FIELD_INTERLACED ) अणु
		WRITE_RPS0(CMD_PAUSE | o_रुको);
		WRITE_RPS0(CMD_PAUSE | e_रुको);
	पूर्ण अन्यथा अगर ( vv->last_field == V4L2_FIELD_TOP ) अणु
		WRITE_RPS0(CMD_PAUSE | (vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? MASK_10 : MASK_09));
		WRITE_RPS0(CMD_PAUSE | o_रुको);
	पूर्ण अन्यथा अगर ( vv->last_field == V4L2_FIELD_BOTTOM ) अणु
		WRITE_RPS0(CMD_PAUSE | (vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? MASK_10 : MASK_09));
		WRITE_RPS0(CMD_PAUSE | e_रुको);
	पूर्ण

	/* turn off video-dma1 */
	WRITE_RPS0(CMD_WR_REG_MASK | (MC1/4));
	WRITE_RPS0(MASK_22 | MASK_06);			/* => mask */
	WRITE_RPS0(MASK_22);				/* => values */
	अगर( 0 != planar ) अणु
		/* turn off video-dma2 */
		WRITE_RPS0(CMD_WR_REG_MASK | (MC1/4));
		WRITE_RPS0(MASK_05 | MASK_21);			/* => mask */
		WRITE_RPS0(MASK_21);				/* => values */

		/* turn off video-dma3 */
		WRITE_RPS0(CMD_WR_REG_MASK | (MC1/4));
		WRITE_RPS0(MASK_04 | MASK_20);			/* => mask */
		WRITE_RPS0(MASK_20);				/* => values */
	पूर्ण

	/* generate पूर्णांकerrupt */
	WRITE_RPS0(CMD_INTERRUPT);

	/* stop */
	WRITE_RPS0(CMD_STOP);
पूर्ण

व्योम saa7146_set_capture(काष्ठा saa7146_dev *dev, काष्ठा saa7146_buf *buf, काष्ठा saa7146_buf *next)
अणु
	काष्ठा saa7146_क्रमmat *sfmt = saa7146_क्रमmat_by_fourcc(dev,buf->fmt->pixelक्रमmat);
	काष्ठा saa7146_vv *vv = dev->vv_data;
	u32 vdma1_prot_addr;

	DEB_CAP("buf:%p, next:%p\n", buf, next);

	vdma1_prot_addr = saa7146_पढ़ो(dev, PROT_ADDR1);
	अगर( 0 == vdma1_prot_addr ) अणु
		/* clear out beginning of streaming bit (rps रेजिस्टर 0)*/
		DEB_CAP("forcing sync to new frame\n");
		saa7146_ग_लिखो(dev, MC2, MASK_27 );
	पूर्ण

	saa7146_set_winकरोw(dev, buf->fmt->width, buf->fmt->height, buf->fmt->field);
	saa7146_set_output_क्रमmat(dev, sfmt->trans);
	saa7146_disable_clipping(dev);

	अगर ( vv->last_field == V4L2_FIELD_INTERLACED ) अणु
	पूर्ण अन्यथा अगर ( vv->last_field == V4L2_FIELD_TOP ) अणु
		vv->last_field = V4L2_FIELD_BOTTOM;
	पूर्ण अन्यथा अगर ( vv->last_field == V4L2_FIELD_BOTTOM ) अणु
		vv->last_field = V4L2_FIELD_TOP;
	पूर्ण

	अगर( 0 != IS_PLANAR(sfmt->trans)) अणु
		calculate_video_dma_grab_planar(dev, buf);
		program_capture_engine(dev,1);
	पूर्ण अन्यथा अणु
		calculate_video_dma_grab_packed(dev, buf);
		program_capture_engine(dev,0);
	पूर्ण

/*
	prपूर्णांकk("vdma%d.base_even:     0x%08x\n", 1,saa7146_पढ़ो(dev,BASE_EVEN1));
	prपूर्णांकk("vdma%d.base_odd:      0x%08x\n", 1,saa7146_पढ़ो(dev,BASE_ODD1));
	prपूर्णांकk("vdma%d.prot_addr:     0x%08x\n", 1,saa7146_पढ़ो(dev,PROT_ADDR1));
	prपूर्णांकk("vdma%d.base_page:     0x%08x\n", 1,saa7146_पढ़ो(dev,BASE_PAGE1));
	prपूर्णांकk("vdma%d.pitch:         0x%08x\n", 1,saa7146_पढ़ो(dev,PITCH1));
	prपूर्णांकk("vdma%d.num_line_byte: 0x%08x\n", 1,saa7146_पढ़ो(dev,NUM_LINE_BYTE1));
	prपूर्णांकk("vdma%d => vptr      : 0x%08x\n", 1,saa7146_पढ़ो(dev,PCI_VDP1));
*/

	/* ग_लिखो the address of the rps-program */
	saa7146_ग_लिखो(dev, RPS_ADDR0, dev->d_rps0.dma_handle);

	/* turn on rps */
	saa7146_ग_लिखो(dev, MC1, (MASK_12 | MASK_28));
पूर्ण
