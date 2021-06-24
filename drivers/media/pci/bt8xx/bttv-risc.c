<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bttv-risc.c  --  पूर्णांकerfaces to other kernel modules

    bttv risc code handling
	- memory management
	- generation

    (c) 2000-2003 Gerd Knorr <kraxel@bytesex.org>


*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "bttvp.h"

#घोषणा VCR_HACK_LINES 4

/* ---------------------------------------------------------- */
/* risc code generators                                       */

पूर्णांक
bttv_risc_packed(काष्ठा bttv *btv, काष्ठा btcx_riscmem *risc,
		 काष्ठा scatterlist *sglist,
		 अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक bpl,
		 अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक skip_lines,
		 अचिन्हित पूर्णांक store_lines)
अणु
	u32 inकाष्ठाions,line,toकरो;
	काष्ठा scatterlist *sg;
	__le32 *rp;
	पूर्णांक rc;

	/* estimate risc mem: worst हाल is one ग_लिखो per page border +
	   one ग_लिखो per scan line + sync + jump (all 2 dwords).  padding
	   can cause next bpl to start बंद to a page border.  First DMA
	   region may be smaller than PAGE_SIZE */
	inकाष्ठाions  = skip_lines * 4;
	inकाष्ठाions += (1 + ((bpl + padding) * store_lines)
			 / PAGE_SIZE + store_lines) * 8;
	inकाष्ठाions += 2 * 8;
	अगर ((rc = btcx_riscmem_alloc(btv->c.pci,risc,inकाष्ठाions)) < 0)
		वापस rc;

	/* sync inकाष्ठाion */
	rp = risc->cpu;
	*(rp++) = cpu_to_le32(BT848_RISC_SYNC|BT848_FIFO_STATUS_FM1);
	*(rp++) = cpu_to_le32(0);

	जबतक (skip_lines-- > 0) अणु
		*(rp++) = cpu_to_le32(BT848_RISC_SKIP | BT848_RISC_SOL |
				      BT848_RISC_EOL | bpl);
	पूर्ण

	/* scan lines */
	sg = sglist;
	क्रम (line = 0; line < store_lines; line++) अणु
		अगर ((btv->opt_vcr_hack) &&
		    (line >= (store_lines - VCR_HACK_LINES)))
			जारी;
		जबतक (offset && offset >= sg_dma_len(sg)) अणु
			offset -= sg_dma_len(sg);
			sg = sg_next(sg);
		पूर्ण
		अगर (bpl <= sg_dma_len(sg)-offset) अणु
			/* fits पूर्णांकo current chunk */
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_SOL|
					    BT848_RISC_EOL|bpl);
			*(rp++)=cpu_to_le32(sg_dma_address(sg)+offset);
			offset+=bpl;
		पूर्ण अन्यथा अणु
			/* scanline needs to be split */
			toकरो = bpl;
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_SOL|
					    (sg_dma_len(sg)-offset));
			*(rp++)=cpu_to_le32(sg_dma_address(sg)+offset);
			toकरो -= (sg_dma_len(sg)-offset);
			offset = 0;
			sg = sg_next(sg);
			जबतक (toकरो > sg_dma_len(sg)) अणु
				*(rp++)=cpu_to_le32(BT848_RISC_WRITE|
						    sg_dma_len(sg));
				*(rp++)=cpu_to_le32(sg_dma_address(sg));
				toकरो -= sg_dma_len(sg);
				sg = sg_next(sg);
			पूर्ण
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_EOL|
					    toकरो);
			*(rp++)=cpu_to_le32(sg_dma_address(sg));
			offset += toकरो;
		पूर्ण
		offset += padding;
	पूर्ण

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण

अटल पूर्णांक
bttv_risc_planar(काष्ठा bttv *btv, काष्ठा btcx_riscmem *risc,
		 काष्ठा scatterlist *sglist,
		 अचिन्हित पूर्णांक yoffset,  अचिन्हित पूर्णांक ybpl,
		 अचिन्हित पूर्णांक ypadding, अचिन्हित पूर्णांक ylines,
		 अचिन्हित पूर्णांक uoffset,  अचिन्हित पूर्णांक voffset,
		 अचिन्हित पूर्णांक hshअगरt,   अचिन्हित पूर्णांक vshअगरt,
		 अचिन्हित पूर्णांक cpadding)
अणु
	अचिन्हित पूर्णांक inकाष्ठाions,line,toकरो,ylen,chroma;
	__le32 *rp;
	u32 ri;
	काष्ठा scatterlist *ysg;
	काष्ठा scatterlist *usg;
	काष्ठा scatterlist *vsg;
	पूर्णांक topfield = (0 == yoffset);
	पूर्णांक rc;

	/* estimate risc mem: worst हाल is one ग_लिखो per page border +
	   one ग_लिखो per scan line (5 dwords)
	   plus sync + jump (2 dwords) */
	inकाष्ठाions  = ((3 + (ybpl + ypadding) * ylines * 2)
			 / PAGE_SIZE) + ylines;
	inकाष्ठाions += 2;
	अगर ((rc = btcx_riscmem_alloc(btv->c.pci,risc,inकाष्ठाions*4*5)) < 0)
		वापस rc;

	/* sync inकाष्ठाion */
	rp = risc->cpu;
	*(rp++) = cpu_to_le32(BT848_RISC_SYNC|BT848_FIFO_STATUS_FM3);
	*(rp++) = cpu_to_le32(0);

	/* scan lines */
	ysg = sglist;
	usg = sglist;
	vsg = sglist;
	क्रम (line = 0; line < ylines; line++) अणु
		अगर ((btv->opt_vcr_hack) &&
		    (line >= (ylines - VCR_HACK_LINES)))
			जारी;
		चयन (vshअगरt) अणु
		हाल 0:
			chroma = 1;
			अवरोध;
		हाल 1:
			अगर (topfield)
				chroma = ((line & 1) == 0);
			अन्यथा
				chroma = ((line & 1) == 1);
			अवरोध;
		हाल 2:
			अगर (topfield)
				chroma = ((line & 3) == 0);
			अन्यथा
				chroma = ((line & 3) == 2);
			अवरोध;
		शेष:
			chroma = 0;
			अवरोध;
		पूर्ण

		क्रम (toकरो = ybpl; toकरो > 0; toकरो -= ylen) अणु
			/* go to next sg entry अगर needed */
			जबतक (yoffset && yoffset >= sg_dma_len(ysg)) अणु
				yoffset -= sg_dma_len(ysg);
				ysg = sg_next(ysg);
			पूर्ण

			/* calculate max number of bytes we can ग_लिखो */
			ylen = toकरो;
			अगर (yoffset + ylen > sg_dma_len(ysg))
				ylen = sg_dma_len(ysg) - yoffset;
			अगर (chroma) अणु
				जबतक (uoffset && uoffset >= sg_dma_len(usg)) अणु
					uoffset -= sg_dma_len(usg);
					usg = sg_next(usg);
				पूर्ण
				जबतक (voffset && voffset >= sg_dma_len(vsg)) अणु
					voffset -= sg_dma_len(vsg);
					vsg = sg_next(vsg);
				पूर्ण

				अगर (uoffset + (ylen>>hshअगरt) > sg_dma_len(usg))
					ylen = (sg_dma_len(usg) - uoffset) << hshअगरt;
				अगर (voffset + (ylen>>hshअगरt) > sg_dma_len(vsg))
					ylen = (sg_dma_len(vsg) - voffset) << hshअगरt;
				ri = BT848_RISC_WRITE123;
			पूर्ण अन्यथा अणु
				ri = BT848_RISC_WRITE1S23;
			पूर्ण
			अगर (ybpl == toकरो)
				ri |= BT848_RISC_SOL;
			अगर (ylen == toकरो)
				ri |= BT848_RISC_EOL;

			/* ग_लिखो risc inकाष्ठाion */
			*(rp++)=cpu_to_le32(ri | ylen);
			*(rp++)=cpu_to_le32(((ylen >> hshअगरt) << 16) |
					    (ylen >> hshअगरt));
			*(rp++)=cpu_to_le32(sg_dma_address(ysg)+yoffset);
			yoffset += ylen;
			अगर (chroma) अणु
				*(rp++)=cpu_to_le32(sg_dma_address(usg)+uoffset);
				uoffset += ylen >> hshअगरt;
				*(rp++)=cpu_to_le32(sg_dma_address(vsg)+voffset);
				voffset += ylen >> hshअगरt;
			पूर्ण
		पूर्ण
		yoffset += ypadding;
		अगर (chroma) अणु
			uoffset += cpadding;
			voffset += cpadding;
		पूर्ण
	पूर्ण

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	वापस 0;
पूर्ण

अटल पूर्णांक
bttv_risc_overlay(काष्ठा bttv *btv, काष्ठा btcx_riscmem *risc,
		  स्थिर काष्ठा bttv_क्रमmat *fmt, काष्ठा bttv_overlay *ov,
		  पूर्णांक skip_even, पूर्णांक skip_odd)
अणु
	पूर्णांक dwords, rc, line, maxy, start, end;
	अचिन्हित skip, nskips;
	काष्ठा btcx_skiplist *skips;
	__le32 *rp;
	u32 ri,ra;
	u32 addr;

	/* skip list क्रम winकरोw clipping */
	skips = kदो_स्मृति_array(ov->nclips, माप(*skips),GFP_KERNEL);
	अगर (शून्य == skips)
		वापस -ENOMEM;

	/* estimate risc mem: worst हाल is (1.5*clip+1) * lines inकाष्ठाions
	   + sync + jump (all 2 dwords) */
	dwords  = (3 * ov->nclips + 2) *
		((skip_even || skip_odd) ? (ov->w.height+1)>>1 :  ov->w.height);
	dwords += 4;
	अगर ((rc = btcx_riscmem_alloc(btv->c.pci,risc,dwords*4)) < 0) अणु
		kमुक्त(skips);
		वापस rc;
	पूर्ण

	/* sync inकाष्ठाion */
	rp = risc->cpu;
	*(rp++) = cpu_to_le32(BT848_RISC_SYNC|BT848_FIFO_STATUS_FM1);
	*(rp++) = cpu_to_le32(0);

	addr  = (अचिन्हित दीर्घ)btv->fbuf.base;
	addr += btv->fbuf.fmt.bytesperline * ov->w.top;
	addr += (fmt->depth >> 3)          * ov->w.left;

	/* scan lines */
	क्रम (maxy = -1, line = 0; line < ov->w.height;
	     line++, addr += btv->fbuf.fmt.bytesperline) अणु
		अगर ((btv->opt_vcr_hack) &&
		     (line >= (ov->w.height - VCR_HACK_LINES)))
			जारी;
		अगर ((line%2) == 0  &&  skip_even)
			जारी;
		अगर ((line%2) == 1  &&  skip_odd)
			जारी;

		/* calculate clipping */
		अगर (line > maxy)
			btcx_calc_skips(line, ov->w.width, &maxy,
					skips, &nskips, ov->clips, ov->nclips);

		/* ग_लिखो out risc code */
		क्रम (start = 0, skip = 0; start < ov->w.width; start = end) अणु
			अगर (skip >= nskips) अणु
				ri  = BT848_RISC_WRITE;
				end = ov->w.width;
			पूर्ण अन्यथा अगर (start < skips[skip].start) अणु
				ri  = BT848_RISC_WRITE;
				end = skips[skip].start;
			पूर्ण अन्यथा अणु
				ri  = BT848_RISC_SKIP;
				end = skips[skip].end;
				skip++;
			पूर्ण
			अगर (BT848_RISC_WRITE == ri)
				ra = addr + (fmt->depth>>3)*start;
			अन्यथा
				ra = 0;

			अगर (0 == start)
				ri |= BT848_RISC_SOL;
			अगर (ov->w.width == end)
				ri |= BT848_RISC_EOL;
			ri |= (fmt->depth>>3) * (end-start);

			*(rp++)=cpu_to_le32(ri);
			अगर (0 != ra)
				*(rp++)=cpu_to_le32(ra);
		पूर्ण
	पूर्ण

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * माप(*risc->cpu) > risc->size);
	kमुक्त(skips);
	वापस 0;
पूर्ण

/* ---------------------------------------------------------- */

अटल व्योम
bttv_calc_geo_old(काष्ठा bttv *btv, काष्ठा bttv_geometry *geo,
		  पूर्णांक width, पूर्णांक height, पूर्णांक पूर्णांकerleaved,
		  स्थिर काष्ठा bttv_tvnorm *tvnorm)
अणु
	u32 xsf, sr;
	पूर्णांक vdelay;

	पूर्णांक swidth       = tvnorm->swidth;
	पूर्णांक totalwidth   = tvnorm->totalwidth;
	पूर्णांक scaledtwidth = tvnorm->scaledtwidth;

	अगर (btv->input == btv->dig) अणु
		swidth       = 720;
		totalwidth   = 858;
		scaledtwidth = 858;
	पूर्ण

	vdelay = tvnorm->vdelay;

	xsf = (width*scaledtwidth)/swidth;
	geo->hscale =  ((totalwidth*4096UL)/xsf-4096);
	geo->hdelay =  tvnorm->hdelayx1;
	geo->hdelay =  (geo->hdelay*width)/swidth;
	geo->hdelay &= 0x3fe;
	sr = ((tvnorm->sheight >> (पूर्णांकerleaved?0:1))*512)/height - 512;
	geo->vscale =  (0x10000UL-sr) & 0x1fff;
	geo->crop   =  ((width>>8)&0x03) | ((geo->hdelay>>6)&0x0c) |
		((tvnorm->sheight>>4)&0x30) | ((vdelay>>2)&0xc0);
	geo->vscale |= पूर्णांकerleaved ? (BT848_VSCALE_INT<<8) : 0;
	geo->vdelay  =  vdelay;
	geo->width   =  width;
	geo->sheight =  tvnorm->sheight;
	geo->vtotal  =  tvnorm->vtotal;

	अगर (btv->opt_combfilter) अणु
		geo->vtc  = (width < 193) ? 2 : ((width < 385) ? 1 : 0);
		geo->comb = (width < 769) ? 1 : 0;
	पूर्ण अन्यथा अणु
		geo->vtc  = 0;
		geo->comb = 0;
	पूर्ण
पूर्ण

अटल व्योम
bttv_calc_geo		(काष्ठा bttv *                  btv,
			 काष्ठा bttv_geometry *         geo,
			 अचिन्हित पूर्णांक                   width,
			 अचिन्हित पूर्णांक                   height,
			 पूर्णांक                            both_fields,
			 स्थिर काष्ठा bttv_tvnorm *     tvnorm,
			 स्थिर काष्ठा v4l2_rect *       crop)
अणु
	अचिन्हित पूर्णांक c_width;
	अचिन्हित पूर्णांक c_height;
	u32 sr;

	अगर ((crop->left == tvnorm->cropcap.defrect.left
	     && crop->top == tvnorm->cropcap.defrect.top
	     && crop->width == tvnorm->cropcap.defrect.width
	     && crop->height == tvnorm->cropcap.defrect.height
	     && width <= tvnorm->swidth /* see PAL-Nc et al */)
	    || btv->input == btv->dig) अणु
		bttv_calc_geo_old(btv, geo, width, height,
				  both_fields, tvnorm);
		वापस;
	पूर्ण

	/* For bug compatibility the image size checks permit scale
	   factors > 16. See bttv_crop_calc_limits(). */
	c_width = min((अचिन्हित पूर्णांक) crop->width, width * 16);
	c_height = min((अचिन्हित पूर्णांक) crop->height, height * 16);

	geo->width = width;
	geo->hscale = (c_width * 4096U + (width >> 1)) / width - 4096;
	/* Even to store Cb first, odd क्रम Cr. */
	geo->hdelay = ((crop->left * width + c_width) / c_width) & ~1;

	geo->sheight = c_height;
	geo->vdelay = crop->top - tvnorm->cropcap.bounds.top + MIN_VDELAY;
	sr = c_height >> !both_fields;
	sr = (sr * 512U + (height >> 1)) / height - 512;
	geo->vscale = (0x10000UL - sr) & 0x1fff;
	geo->vscale |= both_fields ? (BT848_VSCALE_INT << 8) : 0;
	geo->vtotal = tvnorm->vtotal;

	geo->crop = (((geo->width   >> 8) & 0x03) |
		     ((geo->hdelay  >> 6) & 0x0c) |
		     ((geo->sheight >> 4) & 0x30) |
		     ((geo->vdelay  >> 2) & 0xc0));

	अगर (btv->opt_combfilter) अणु
		geo->vtc  = (width < 193) ? 2 : ((width < 385) ? 1 : 0);
		geo->comb = (width < 769) ? 1 : 0;
	पूर्ण अन्यथा अणु
		geo->vtc  = 0;
		geo->comb = 0;
	पूर्ण
पूर्ण

अटल व्योम
bttv_apply_geo(काष्ठा bttv *btv, काष्ठा bttv_geometry *geo, पूर्णांक odd)
अणु
	पूर्णांक off = odd ? 0x80 : 0x00;

	अगर (geo->comb)
		btor(BT848_VSCALE_COMB, BT848_E_VSCALE_HI+off);
	अन्यथा
		btand(~BT848_VSCALE_COMB, BT848_E_VSCALE_HI+off);

	btग_लिखो(geo->vtc,             BT848_E_VTC+off);
	btग_लिखो(geo->hscale >> 8,     BT848_E_HSCALE_HI+off);
	btग_लिखो(geo->hscale & 0xff,   BT848_E_HSCALE_LO+off);
	btaor((geo->vscale>>8), 0xe0, BT848_E_VSCALE_HI+off);
	btग_लिखो(geo->vscale & 0xff,   BT848_E_VSCALE_LO+off);
	btग_लिखो(geo->width & 0xff,    BT848_E_HACTIVE_LO+off);
	btग_लिखो(geo->hdelay & 0xff,   BT848_E_HDELAY_LO+off);
	btग_लिखो(geo->sheight & 0xff,  BT848_E_VACTIVE_LO+off);
	btग_लिखो(geo->vdelay & 0xff,   BT848_E_VDELAY_LO+off);
	btग_लिखो(geo->crop,            BT848_E_CROP+off);
	btग_लिखो(geo->vtotal>>8,       BT848_VTOTAL_HI);
	btग_लिखो(geo->vtotal & 0xff,   BT848_VTOTAL_LO);
पूर्ण

/* ---------------------------------------------------------- */
/* risc group / risc मुख्य loop / dma management               */

व्योम
bttv_set_dma(काष्ठा bttv *btv, पूर्णांक override)
अणु
	अचिन्हित दीर्घ cmd;
	पूर्णांक capctl;

	btv->cap_ctl = 0;
	अगर (शून्य != btv->curr.top)      btv->cap_ctl |= 0x02;
	अगर (शून्य != btv->curr.bottom)   btv->cap_ctl |= 0x01;
	अगर (शून्य != btv->cvbi)          btv->cap_ctl |= 0x0c;

	capctl  = 0;
	capctl |= (btv->cap_ctl & 0x03) ? 0x03 : 0x00;  /* capture  */
	capctl |= (btv->cap_ctl & 0x0c) ? 0x0c : 0x00;  /* vbi data */
	capctl |= override;

	d2prपूर्णांकk("%d: capctl=%x lirq=%d top=%08llx/%08llx even=%08llx/%08llx\n",
		 btv->c.nr,capctl,btv->loop_irq,
		 btv->cvbi         ? (अचिन्हित दीर्घ दीर्घ)btv->cvbi->top.dma            : 0,
		 btv->curr.top     ? (अचिन्हित दीर्घ दीर्घ)btv->curr.top->top.dma        : 0,
		 btv->cvbi         ? (अचिन्हित दीर्घ दीर्घ)btv->cvbi->bottom.dma         : 0,
		 btv->curr.bottom  ? (अचिन्हित दीर्घ दीर्घ)btv->curr.bottom->bottom.dma  : 0);

	cmd = BT848_RISC_JUMP;
	अगर (btv->loop_irq) अणु
		cmd |= BT848_RISC_IRQ;
		cmd |= (btv->loop_irq  & 0x0f) << 16;
		cmd |= (~btv->loop_irq & 0x0f) << 20;
	पूर्ण
	अगर (btv->curr.frame_irq || btv->loop_irq || btv->cvbi) अणु
		mod_समयr(&btv->समयout, jअगरfies+BTTV_TIMEOUT);
	पूर्ण अन्यथा अणु
		del_समयr(&btv->समयout);
	पूर्ण
	btv->मुख्य.cpu[RISC_SLOT_LOOP] = cpu_to_le32(cmd);

	btaor(capctl, ~0x0f, BT848_CAP_CTL);
	अगर (capctl) अणु
		अगर (btv->dma_on)
			वापस;
		btग_लिखो(btv->मुख्य.dma, BT848_RISC_STRT_ADD);
		btor(3, BT848_GPIO_DMA_CTL);
		btv->dma_on = 1;
	पूर्ण अन्यथा अणु
		अगर (!btv->dma_on)
			वापस;
		btand(~3, BT848_GPIO_DMA_CTL);
		btv->dma_on = 0;
	पूर्ण
	वापस;
पूर्ण

पूर्णांक
bttv_risc_init_मुख्य(काष्ठा bttv *btv)
अणु
	पूर्णांक rc;

	अगर ((rc = btcx_riscmem_alloc(btv->c.pci,&btv->मुख्य,PAGE_SIZE)) < 0)
		वापस rc;
	dprपूर्णांकk("%d: risc main @ %08llx\n",
		btv->c.nr, (अचिन्हित दीर्घ दीर्घ)btv->मुख्य.dma);

	btv->मुख्य.cpu[0] = cpu_to_le32(BT848_RISC_SYNC | BT848_RISC_RESYNC |
				       BT848_FIFO_STATUS_VRE);
	btv->मुख्य.cpu[1] = cpu_to_le32(0);
	btv->मुख्य.cpu[2] = cpu_to_le32(BT848_RISC_JUMP);
	btv->मुख्य.cpu[3] = cpu_to_le32(btv->मुख्य.dma + (4<<2));

	/* top field */
	btv->मुख्य.cpu[4] = cpu_to_le32(BT848_RISC_JUMP);
	btv->मुख्य.cpu[5] = cpu_to_le32(btv->मुख्य.dma + (6<<2));
	btv->मुख्य.cpu[6] = cpu_to_le32(BT848_RISC_JUMP);
	btv->मुख्य.cpu[7] = cpu_to_le32(btv->मुख्य.dma + (8<<2));

	btv->मुख्य.cpu[8] = cpu_to_le32(BT848_RISC_SYNC | BT848_RISC_RESYNC |
				       BT848_FIFO_STATUS_VRO);
	btv->मुख्य.cpu[9] = cpu_to_le32(0);

	/* bottom field */
	btv->मुख्य.cpu[10] = cpu_to_le32(BT848_RISC_JUMP);
	btv->मुख्य.cpu[11] = cpu_to_le32(btv->मुख्य.dma + (12<<2));
	btv->मुख्य.cpu[12] = cpu_to_le32(BT848_RISC_JUMP);
	btv->मुख्य.cpu[13] = cpu_to_le32(btv->मुख्य.dma + (14<<2));

	/* jump back to top field */
	btv->मुख्य.cpu[14] = cpu_to_le32(BT848_RISC_JUMP);
	btv->मुख्य.cpu[15] = cpu_to_le32(btv->मुख्य.dma + (0<<2));

	वापस 0;
पूर्ण

पूर्णांक
bttv_risc_hook(काष्ठा bttv *btv, पूर्णांक slot, काष्ठा btcx_riscmem *risc,
	       पूर्णांक irqflags)
अणु
	अचिन्हित दीर्घ cmd;
	अचिन्हित दीर्घ next = btv->मुख्य.dma + ((slot+2) << 2);

	अगर (शून्य == risc) अणु
		d2prपूर्णांकk("%d: risc=%p slot[%d]=NULL\n", btv->c.nr, risc, slot);
		btv->मुख्य.cpu[slot+1] = cpu_to_le32(next);
	पूर्ण अन्यथा अणु
		d2prपूर्णांकk("%d: risc=%p slot[%d]=%08llx irq=%d\n",
			 btv->c.nr, risc, slot,
			 (अचिन्हित दीर्घ दीर्घ)risc->dma, irqflags);
		cmd = BT848_RISC_JUMP;
		अगर (irqflags) अणु
			cmd |= BT848_RISC_IRQ;
			cmd |= (irqflags  & 0x0f) << 16;
			cmd |= (~irqflags & 0x0f) << 20;
		पूर्ण
		risc->jmp[0] = cpu_to_le32(cmd);
		risc->jmp[1] = cpu_to_le32(next);
		btv->मुख्य.cpu[slot+1] = cpu_to_le32(risc->dma);
	पूर्ण
	वापस 0;
पूर्ण

व्योम
bttv_dma_मुक्त(काष्ठा videobuf_queue *q,काष्ठा bttv *btv, काष्ठा bttv_buffer *buf)
अणु
	काष्ठा videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);

	videobuf_रुकोon(q, &buf->vb, 0, 0);
	videobuf_dma_unmap(q->dev, dma);
	videobuf_dma_मुक्त(dma);
	btcx_riscmem_मुक्त(btv->c.pci,&buf->bottom);
	btcx_riscmem_मुक्त(btv->c.pci,&buf->top);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
पूर्ण

पूर्णांक
bttv_buffer_activate_vbi(काष्ठा bttv *btv,
			 काष्ठा bttv_buffer *vbi)
अणु
	काष्ठा btcx_riscmem *top;
	काष्ठा btcx_riscmem *bottom;
	पूर्णांक top_irq_flags;
	पूर्णांक bottom_irq_flags;

	top = शून्य;
	bottom = शून्य;
	top_irq_flags = 0;
	bottom_irq_flags = 0;

	अगर (vbi) अणु
		अचिन्हित पूर्णांक crop, vdelay;

		vbi->vb.state = VIDEOBUF_ACTIVE;
		list_del(&vbi->vb.queue);

		/* VDELAY is start of video, end of VBI capturing. */
		crop = btपढ़ो(BT848_E_CROP);
		vdelay = btपढ़ो(BT848_E_VDELAY_LO) + ((crop & 0xc0) << 2);

		अगर (vbi->geo.vdelay > vdelay) अणु
			vdelay = vbi->geo.vdelay & 0xfe;
			crop = (crop & 0x3f) | ((vbi->geo.vdelay >> 2) & 0xc0);

			btग_लिखो(vdelay, BT848_E_VDELAY_LO);
			btग_लिखो(crop,	BT848_E_CROP);
			btग_लिखो(vdelay, BT848_O_VDELAY_LO);
			btग_लिखो(crop,	BT848_O_CROP);
		पूर्ण

		अगर (vbi->vbi_count[0] > 0) अणु
			top = &vbi->top;
			top_irq_flags = 4;
		पूर्ण

		अगर (vbi->vbi_count[1] > 0) अणु
			top_irq_flags = 0;
			bottom = &vbi->bottom;
			bottom_irq_flags = 4;
		पूर्ण
	पूर्ण

	bttv_risc_hook(btv, RISC_SLOT_O_VBI, top, top_irq_flags);
	bttv_risc_hook(btv, RISC_SLOT_E_VBI, bottom, bottom_irq_flags);

	वापस 0;
पूर्ण

पूर्णांक
bttv_buffer_activate_video(काष्ठा bttv *btv,
			   काष्ठा bttv_buffer_set *set)
अणु
	/* video capture */
	अगर (शून्य != set->top  &&  शून्य != set->bottom) अणु
		अगर (set->top == set->bottom) अणु
			set->top->vb.state    = VIDEOBUF_ACTIVE;
			अगर (set->top->vb.queue.next)
				list_del(&set->top->vb.queue);
		पूर्ण अन्यथा अणु
			set->top->vb.state    = VIDEOBUF_ACTIVE;
			set->bottom->vb.state = VIDEOBUF_ACTIVE;
			अगर (set->top->vb.queue.next)
				list_del(&set->top->vb.queue);
			अगर (set->bottom->vb.queue.next)
				list_del(&set->bottom->vb.queue);
		पूर्ण
		bttv_apply_geo(btv, &set->top->geo, 1);
		bttv_apply_geo(btv, &set->bottom->geo,0);
		bttv_risc_hook(btv, RISC_SLOT_O_FIELD, &set->top->top,
			       set->top_irq);
		bttv_risc_hook(btv, RISC_SLOT_E_FIELD, &set->bottom->bottom,
			       set->frame_irq);
		btaor((set->top->btक्रमmat & 0xf0) | (set->bottom->btक्रमmat & 0x0f),
		      ~0xff, BT848_COLOR_FMT);
		btaor((set->top->btswap & 0x0a) | (set->bottom->btswap & 0x05),
		      ~0x0f, BT848_COLOR_CTL);
	पूर्ण अन्यथा अगर (शून्य != set->top) अणु
		set->top->vb.state  = VIDEOBUF_ACTIVE;
		अगर (set->top->vb.queue.next)
			list_del(&set->top->vb.queue);
		bttv_apply_geo(btv, &set->top->geo,1);
		bttv_apply_geo(btv, &set->top->geo,0);
		bttv_risc_hook(btv, RISC_SLOT_O_FIELD, &set->top->top,
			       set->frame_irq);
		bttv_risc_hook(btv, RISC_SLOT_E_FIELD, शून्य,           0);
		btaor(set->top->btक्रमmat & 0xff, ~0xff, BT848_COLOR_FMT);
		btaor(set->top->btswap & 0x0f,   ~0x0f, BT848_COLOR_CTL);
	पूर्ण अन्यथा अगर (शून्य != set->bottom) अणु
		set->bottom->vb.state = VIDEOBUF_ACTIVE;
		अगर (set->bottom->vb.queue.next)
			list_del(&set->bottom->vb.queue);
		bttv_apply_geo(btv, &set->bottom->geo,1);
		bttv_apply_geo(btv, &set->bottom->geo,0);
		bttv_risc_hook(btv, RISC_SLOT_O_FIELD, शून्य, 0);
		bttv_risc_hook(btv, RISC_SLOT_E_FIELD, &set->bottom->bottom,
			       set->frame_irq);
		btaor(set->bottom->btक्रमmat & 0xff, ~0xff, BT848_COLOR_FMT);
		btaor(set->bottom->btswap & 0x0f,   ~0x0f, BT848_COLOR_CTL);
	पूर्ण अन्यथा अणु
		bttv_risc_hook(btv, RISC_SLOT_O_FIELD, शून्य, 0);
		bttv_risc_hook(btv, RISC_SLOT_E_FIELD, शून्य, 0);
	पूर्ण
	वापस 0;
पूर्ण

/* ---------------------------------------------------------- */

/* calculate geometry, build risc code */
पूर्णांक
bttv_buffer_risc(काष्ठा bttv *btv, काष्ठा bttv_buffer *buf)
अणु
	स्थिर काष्ठा bttv_tvnorm *tvnorm = bttv_tvnorms + buf->tvnorm;
	काष्ठा videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);

	dprपूर्णांकk("%d: buffer field: %s  format: 0x%08x  size: %dx%d\n",
		btv->c.nr, v4l2_field_names[buf->vb.field],
		buf->fmt->fourcc, buf->vb.width, buf->vb.height);

	/* packed pixel modes */
	अगर (buf->fmt->flags & FORMAT_FLAGS_PACKED) अणु
		पूर्णांक bpl = (buf->fmt->depth >> 3) * buf->vb.width;
		पूर्णांक bpf = bpl * (buf->vb.height >> 1);

		bttv_calc_geo(btv,&buf->geo,buf->vb.width,buf->vb.height,
			      V4L2_FIELD_HAS_BOTH(buf->vb.field),
			      tvnorm,&buf->crop);

		चयन (buf->vb.field) अणु
		हाल V4L2_FIELD_TOP:
			bttv_risc_packed(btv,&buf->top,dma->sglist,
					 /* offset */ 0,bpl,
					 /* padding */ 0,/* skip_lines */ 0,
					 buf->vb.height);
			अवरोध;
		हाल V4L2_FIELD_BOTTOM:
			bttv_risc_packed(btv,&buf->bottom,dma->sglist,
					 0,bpl,0,0,buf->vb.height);
			अवरोध;
		हाल V4L2_FIELD_INTERLACED:
			bttv_risc_packed(btv,&buf->top,dma->sglist,
					 0,bpl,bpl,0,buf->vb.height >> 1);
			bttv_risc_packed(btv,&buf->bottom,dma->sglist,
					 bpl,bpl,bpl,0,buf->vb.height >> 1);
			अवरोध;
		हाल V4L2_FIELD_SEQ_TB:
			bttv_risc_packed(btv,&buf->top,dma->sglist,
					 0,bpl,0,0,buf->vb.height >> 1);
			bttv_risc_packed(btv,&buf->bottom,dma->sglist,
					 bpf,bpl,0,0,buf->vb.height >> 1);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	/* planar modes */
	अगर (buf->fmt->flags & FORMAT_FLAGS_PLANAR) अणु
		पूर्णांक uoffset, voffset;
		पूर्णांक ypadding, cpadding, lines;

		/* calculate chroma offsets */
		uoffset = buf->vb.width * buf->vb.height;
		voffset = buf->vb.width * buf->vb.height;
		अगर (buf->fmt->flags & FORMAT_FLAGS_CrCb) अणु
			/* Y-Cr-Cb plane order */
			uoffset >>= buf->fmt->hshअगरt;
			uoffset >>= buf->fmt->vshअगरt;
			uoffset  += voffset;
		पूर्ण अन्यथा अणु
			/* Y-Cb-Cr plane order */
			voffset >>= buf->fmt->hshअगरt;
			voffset >>= buf->fmt->vshअगरt;
			voffset  += uoffset;
		पूर्ण

		चयन (buf->vb.field) अणु
		हाल V4L2_FIELD_TOP:
			bttv_calc_geo(btv,&buf->geo,buf->vb.width,
				      buf->vb.height,/* both_fields */ 0,
				      tvnorm,&buf->crop);
			bttv_risc_planar(btv, &buf->top, dma->sglist,
					 0,buf->vb.width,0,buf->vb.height,
					 uoffset,voffset,buf->fmt->hshअगरt,
					 buf->fmt->vshअगरt,0);
			अवरोध;
		हाल V4L2_FIELD_BOTTOM:
			bttv_calc_geo(btv,&buf->geo,buf->vb.width,
				      buf->vb.height,0,
				      tvnorm,&buf->crop);
			bttv_risc_planar(btv, &buf->bottom, dma->sglist,
					 0,buf->vb.width,0,buf->vb.height,
					 uoffset,voffset,buf->fmt->hshअगरt,
					 buf->fmt->vshअगरt,0);
			अवरोध;
		हाल V4L2_FIELD_INTERLACED:
			bttv_calc_geo(btv,&buf->geo,buf->vb.width,
				      buf->vb.height,1,
				      tvnorm,&buf->crop);
			lines    = buf->vb.height >> 1;
			ypadding = buf->vb.width;
			cpadding = buf->vb.width >> buf->fmt->hshअगरt;
			bttv_risc_planar(btv,&buf->top,
					 dma->sglist,
					 0,buf->vb.width,ypadding,lines,
					 uoffset,voffset,
					 buf->fmt->hshअगरt,
					 buf->fmt->vshअगरt,
					 cpadding);
			bttv_risc_planar(btv,&buf->bottom,
					 dma->sglist,
					 ypadding,buf->vb.width,ypadding,lines,
					 uoffset+cpadding,
					 voffset+cpadding,
					 buf->fmt->hshअगरt,
					 buf->fmt->vshअगरt,
					 cpadding);
			अवरोध;
		हाल V4L2_FIELD_SEQ_TB:
			bttv_calc_geo(btv,&buf->geo,buf->vb.width,
				      buf->vb.height,1,
				      tvnorm,&buf->crop);
			lines    = buf->vb.height >> 1;
			ypadding = buf->vb.width;
			cpadding = buf->vb.width >> buf->fmt->hshअगरt;
			bttv_risc_planar(btv,&buf->top,
					 dma->sglist,
					 0,buf->vb.width,0,lines,
					 uoffset >> 1,
					 voffset >> 1,
					 buf->fmt->hshअगरt,
					 buf->fmt->vshअगरt,
					 0);
			bttv_risc_planar(btv,&buf->bottom,
					 dma->sglist,
					 lines * ypadding,buf->vb.width,0,lines,
					 lines * ypadding + (uoffset >> 1),
					 lines * ypadding + (voffset >> 1),
					 buf->fmt->hshअगरt,
					 buf->fmt->vshअगरt,
					 0);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	/* raw data */
	अगर (buf->fmt->flags & FORMAT_FLAGS_RAW) अणु
		/* build risc code */
		buf->vb.field = V4L2_FIELD_SEQ_TB;
		bttv_calc_geo(btv,&buf->geo,tvnorm->swidth,tvnorm->sheight,
			      1,tvnorm,&buf->crop);
		bttv_risc_packed(btv, &buf->top,  dma->sglist,
				 /* offset */ 0, RAW_BPL, /* padding */ 0,
				 /* skip_lines */ 0, RAW_LINES);
		bttv_risc_packed(btv, &buf->bottom, dma->sglist,
				 buf->vb.size/2 , RAW_BPL, 0, 0, RAW_LINES);
	पूर्ण

	/* copy क्रमmat info */
	buf->btक्रमmat = buf->fmt->btक्रमmat;
	buf->btswap   = buf->fmt->btswap;
	वापस 0;
पूर्ण

/* ---------------------------------------------------------- */

/* calculate geometry, build risc code */
पूर्णांक
bttv_overlay_risc(काष्ठा bttv *btv,
		  काष्ठा bttv_overlay *ov,
		  स्थिर काष्ठा bttv_क्रमmat *fmt,
		  काष्ठा bttv_buffer *buf)
अणु
	/* check पूर्णांकerleave, bottom+top fields */
	dprपूर्णांकk("%d: overlay fields: %s format: 0x%08x  size: %dx%d\n",
		btv->c.nr, v4l2_field_names[buf->vb.field],
		fmt->fourcc, ov->w.width, ov->w.height);

	/* calculate geometry */
	bttv_calc_geo(btv,&buf->geo,ov->w.width,ov->w.height,
		      V4L2_FIELD_HAS_BOTH(ov->field),
		      &bttv_tvnorms[ov->tvnorm],&buf->crop);

	/* build risc code */
	चयन (ov->field) अणु
	हाल V4L2_FIELD_TOP:
		bttv_risc_overlay(btv, &buf->top,    fmt, ov, 0, 0);
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		bttv_risc_overlay(btv, &buf->bottom, fmt, ov, 0, 0);
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		bttv_risc_overlay(btv, &buf->top,    fmt, ov, 0, 1);
		bttv_risc_overlay(btv, &buf->bottom, fmt, ov, 1, 0);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	/* copy क्रमmat info */
	buf->btक्रमmat = fmt->btक्रमmat;
	buf->btswap   = fmt->btswap;
	buf->vb.field = ov->field;
	वापस 0;
पूर्ण
