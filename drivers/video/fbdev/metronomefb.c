<शैली गुरु>
/*
 * linux/drivers/video/metronomefb.c -- FB driver क्रम Metronome controller
 *
 * Copyright (C) 2008, Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Layout is based on skeletonfb.c by James Simmons and Geert Uytterhoeven.
 *
 * This work was made possible by help and equipment support from E-Ink
 * Corporation. https://www.eink.com/
 *
 * This driver is written to be used with the Metronome display controller.
 * It is पूर्णांकended to be architecture independent. A board specअगरic driver
 * must be used to perक्रमm all the physical IO पूर्णांकeractions. An example
 * is provided as am200epd.c
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/firmware.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/irq.h>

#समावेश <video/metronomefb.h>

#समावेश <यंत्र/unaligned.h>

/* Display specअगरic inक्रमmation */
#घोषणा DPY_W 832
#घोषणा DPY_H 622

अटल पूर्णांक user_wfm_size;

/* frame dअगरfers from image. frame includes non-visible pixels */
काष्ठा epd_frame अणु
	पूर्णांक fw; /* frame width */
	पूर्णांक fh; /* frame height */
	u16 config[4];
	पूर्णांक wfm_size;
पूर्ण;

अटल काष्ठा epd_frame epd_frame_table[] = अणु
	अणु
		.fw = 832,
		.fh = 622,
		.config = अणु
			15 /* sdlew */
			| 2 << 8 /* sकरोsz */
			| 0 << 11 /* sकरोr */
			| 0 << 12 /* sdces */
			| 0 << 15, /* sdcer */
			42 /* gdspl */
			| 1 << 8 /* gdr1 */
			| 1 << 9 /* sdshr */
			| 0 << 15, /* gdspp */
			18 /* gdspw */
			| 0 << 15, /* dispc */
			599 /* vdlc */
			| 0 << 11 /* dsi */
			| 0 << 12, /* dsic */
		पूर्ण,
		.wfm_size = 47001,
	पूर्ण,
	अणु
		.fw = 1088,
		.fh = 791,
		.config = अणु
			0x0104,
			0x031f,
			0x0088,
			0x02ff,
		पूर्ण,
		.wfm_size = 46770,
	पूर्ण,
	अणु
		.fw = 1200,
		.fh = 842,
		.config = अणु
			0x0101,
			0x030e,
			0x0012,
			0x0280,
		पूर्ण,
		.wfm_size = 46770,
	पूर्ण,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo metronomefb_fix = अणु
	.id =		"metronomefb",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_STATIC_PSEUDOCOLOR,
	.xpanstep =	0,
	.ypanstep =	0,
	.ywrapstep =	0,
	.line_length =	DPY_W,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल काष्ठा fb_var_screeninfo metronomefb_var = अणु
	.xres		= DPY_W,
	.yres		= DPY_H,
	.xres_भव	= DPY_W,
	.yres_भव	= DPY_H,
	.bits_per_pixel	= 8,
	.grayscale	= 1,
	.nonstd		= 1,
	.red =		अणु 4, 3, 0 पूर्ण,
	.green =	अणु 0, 0, 0 पूर्ण,
	.blue =		अणु 0, 0, 0 पूर्ण,
	.transp =	अणु 0, 0, 0 पूर्ण,
पूर्ण;

/* the waveक्रमm काष्ठाure that is coming from userspace firmware */
काष्ठा waveक्रमm_hdr अणु
	u8 stuff[32];

	u8 wmta[3];
	u8 fvsn;

	u8 luts;
	u8 mc;
	u8 trc;
	u8 stuff3;

	u8 endb;
	u8 swtb;
	u8 stuff2a[2];

	u8 stuff2b[3];
	u8 wfm_cs;
पूर्ण __attribute__ ((packed));

/* मुख्य metronomefb functions */
अटल u8 calc_cksum(पूर्णांक start, पूर्णांक end, u8 *mem)
अणु
	u8 पंचांगp = 0;
	पूर्णांक i;

	क्रम (i = start; i < end; i++)
		पंचांगp += mem[i];

	वापस पंचांगp;
पूर्ण

अटल u16 calc_img_cksum(u16 *start, पूर्णांक length)
अणु
	u16 पंचांगp = 0;

	जबतक (length--)
		पंचांगp += *start++;

	वापस पंचांगp;
पूर्ण

/* here we decode the incoming waveक्रमm file and populate metromem */
अटल पूर्णांक load_waveक्रमm(u8 *mem, माप_प्रकार size, पूर्णांक m, पूर्णांक t,
			 काष्ठा metronomefb_par *par)
अणु
	पूर्णांक tta;
	पूर्णांक wmta;
	पूर्णांक trn = 0;
	पूर्णांक i;
	अचिन्हित अक्षर v;
	u8 cksum;
	पूर्णांक cksum_idx;
	पूर्णांक wfm_idx, owfm_idx;
	पूर्णांक mem_idx = 0;
	काष्ठा waveक्रमm_hdr *wfm_hdr;
	u8 *metromem = par->metromem_wfm;
	काष्ठा device *dev = par->info->dev;

	अगर (user_wfm_size)
		epd_frame_table[par->dt].wfm_size = user_wfm_size;

	अगर (size != epd_frame_table[par->dt].wfm_size) अणु
		dev_err(dev, "Error: unexpected size %zd != %d\n", size,
					epd_frame_table[par->dt].wfm_size);
		वापस -EINVAL;
	पूर्ण

	wfm_hdr = (काष्ठा waveक्रमm_hdr *) mem;

	अगर (wfm_hdr->fvsn != 1) अणु
		dev_err(dev, "Error: bad fvsn %x\n", wfm_hdr->fvsn);
		वापस -EINVAL;
	पूर्ण
	अगर (wfm_hdr->luts != 0) अणु
		dev_err(dev, "Error: bad luts %x\n", wfm_hdr->luts);
		वापस -EINVAL;
	पूर्ण
	cksum = calc_cksum(32, 47, mem);
	अगर (cksum != wfm_hdr->wfm_cs) अणु
		dev_err(dev, "Error: bad cksum %x != %x\n", cksum,
					wfm_hdr->wfm_cs);
		वापस -EINVAL;
	पूर्ण
	wfm_hdr->mc += 1;
	wfm_hdr->trc += 1;
	क्रम (i = 0; i < 5; i++) अणु
		अगर (*(wfm_hdr->stuff2a + i) != 0) अणु
			dev_err(dev, "Error: unexpected value in padding\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* calculating trn. trn is something used to index पूर्णांकo
	the waveक्रमm. presumably selecting the right one क्रम the
	desired temperature. it works out the offset of the first
	v that exceeds the specअगरied temperature */
	अगर ((माप(*wfm_hdr) + wfm_hdr->trc) > size)
		वापस -EINVAL;

	क्रम (i = माप(*wfm_hdr); i <= माप(*wfm_hdr) + wfm_hdr->trc; i++) अणु
		अगर (mem[i] > t) अणु
			trn = i - माप(*wfm_hdr) - 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* check temperature range table checksum */
	cksum_idx = माप(*wfm_hdr) + wfm_hdr->trc + 1;
	अगर (cksum_idx >= size)
		वापस -EINVAL;
	cksum = calc_cksum(माप(*wfm_hdr), cksum_idx, mem);
	अगर (cksum != mem[cksum_idx]) अणु
		dev_err(dev, "Error: bad temperature range table cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		वापस -EINVAL;
	पूर्ण

	/* check waveक्रमm mode table address checksum */
	wmta = get_unaligned_le32(wfm_hdr->wmta) & 0x00FFFFFF;
	cksum_idx = wmta + m*4 + 3;
	अगर (cksum_idx >= size)
		वापस -EINVAL;
	cksum = calc_cksum(cksum_idx - 3, cksum_idx, mem);
	अगर (cksum != mem[cksum_idx]) अणु
		dev_err(dev, "Error: bad mode table address cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		वापस -EINVAL;
	पूर्ण

	/* check waveक्रमm temperature table address checksum */
	tta = get_unaligned_le32(mem + wmta + m * 4) & 0x00FFFFFF;
	cksum_idx = tta + trn*4 + 3;
	अगर (cksum_idx >= size)
		वापस -EINVAL;
	cksum = calc_cksum(cksum_idx - 3, cksum_idx, mem);
	अगर (cksum != mem[cksum_idx]) अणु
		dev_err(dev, "Error: bad temperature table address cksum"
			" %x != %x\n", cksum, mem[cksum_idx]);
		वापस -EINVAL;
	पूर्ण

	/* here we करो the real work of putting the waveक्रमm पूर्णांकo the
	metromem buffer. this करोes runlength decoding of the waveक्रमm */
	wfm_idx = get_unaligned_le32(mem + tta + trn * 4) & 0x00FFFFFF;
	owfm_idx = wfm_idx;
	अगर (wfm_idx >= size)
		वापस -EINVAL;
	जबतक (wfm_idx < size) अणु
		अचिन्हित अक्षर rl;
		v = mem[wfm_idx++];
		अगर (v == wfm_hdr->swtb) अणु
			जबतक (((v = mem[wfm_idx++]) != wfm_hdr->swtb) &&
				wfm_idx < size)
				metromem[mem_idx++] = v;

			जारी;
		पूर्ण

		अगर (v == wfm_hdr->endb)
			अवरोध;

		rl = mem[wfm_idx++];
		क्रम (i = 0; i <= rl; i++)
			metromem[mem_idx++] = v;
	पूर्ण

	cksum_idx = wfm_idx;
	अगर (cksum_idx >= size)
		वापस -EINVAL;
	cksum = calc_cksum(owfm_idx, cksum_idx, mem);
	अगर (cksum != mem[cksum_idx]) अणु
		dev_err(dev, "Error: bad waveform data cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		वापस -EINVAL;
	पूर्ण
	par->frame_count = (mem_idx/64);

	वापस 0;
पूर्ण

अटल पूर्णांक metronome_display_cmd(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक i;
	u16 cs;
	u16 opcode;
	अटल u8 borderval;

	/* setup display command
	we can't immediately set the opcode since the controller
	will try parse the command beक्रमe we've set it all up
	so we just set cs here and set the opcode at the end */

	अगर (par->metromem_cmd->opcode == 0xCC40)
		opcode = cs = 0xCC41;
	अन्यथा
		opcode = cs = 0xCC40;

	/* set the args ( 2 bytes ) क्रम display */
	i = 0;
	par->metromem_cmd->args[i] = 	1 << 3 /* border update */
					| ((borderval++ % 4) & 0x0F) << 4
					| (par->frame_count - 1) << 8;
	cs += par->metromem_cmd->args[i++];

	/* the rest are 0 */
	स_रखो((u8 *) (par->metromem_cmd->args + i), 0, (32-i)*2);

	par->metromem_cmd->csum = cs;
	par->metromem_cmd->opcode = opcode; /* display cmd */

	वापस par->board->met_रुको_event_पूर्णांकr(par);
पूर्ण

अटल पूर्णांक metronome_घातerup_cmd(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक i;
	u16 cs;

	/* setup घातer up command */
	par->metromem_cmd->opcode = 0x1234; /* pwr up pseuकरो cmd */
	cs = par->metromem_cmd->opcode;

	/* set pwr1,2,3 to 1024 */
	क्रम (i = 0; i < 3; i++) अणु
		par->metromem_cmd->args[i] = 1024;
		cs += par->metromem_cmd->args[i];
	पूर्ण

	/* the rest are 0 */
	स_रखो(&par->metromem_cmd->args[i], 0,
	       (ARRAY_SIZE(par->metromem_cmd->args) - i) * 2);

	par->metromem_cmd->csum = cs;

	msleep(1);
	par->board->set_rst(par, 1);

	msleep(1);
	par->board->set_stdby(par, 1);

	वापस par->board->met_रुको_event(par);
पूर्ण

अटल पूर्णांक metronome_config_cmd(काष्ठा metronomefb_par *par)
अणु
	/* setup config command
	we can't immediately set the opcode since the controller
	will try parse the command beक्रमe we've set it all up */

	स_नकल(par->metromem_cmd->args, epd_frame_table[par->dt].config,
		माप(epd_frame_table[par->dt].config));
	/* the rest are 0 */
	स_रखो(&par->metromem_cmd->args[4], 0,
	       (ARRAY_SIZE(par->metromem_cmd->args) - 4) * 2);

	par->metromem_cmd->csum = 0xCC10;
	par->metromem_cmd->csum += calc_img_cksum(par->metromem_cmd->args, 4);
	par->metromem_cmd->opcode = 0xCC10; /* config cmd */

	वापस par->board->met_रुको_event(par);
पूर्ण

अटल पूर्णांक metronome_init_cmd(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक i;
	u16 cs;

	/* setup init command
	we can't immediately set the opcode since the controller
	will try parse the command beक्रमe we've set it all up
	so we just set cs here and set the opcode at the end */

	cs = 0xCC20;

	/* set the args ( 2 bytes ) क्रम init */
	i = 0;
	par->metromem_cmd->args[i] = 0;
	cs += par->metromem_cmd->args[i++];

	/* the rest are 0 */
	स_रखो((u8 *) (par->metromem_cmd->args + i), 0, (32-i)*2);

	par->metromem_cmd->csum = cs;
	par->metromem_cmd->opcode = 0xCC20; /* init cmd */

	वापस par->board->met_रुको_event(par);
पूर्ण

अटल पूर्णांक metronome_init_regs(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक res;

	res = par->board->setup_io(par);
	अगर (res)
		वापस res;

	res = metronome_घातerup_cmd(par);
	अगर (res)
		वापस res;

	res = metronome_config_cmd(par);
	अगर (res)
		वापस res;

	res = metronome_init_cmd(par);

	वापस res;
पूर्ण

अटल व्योम metronomefb_dpy_update(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक fbsize;
	u16 cksum;
	अचिन्हित अक्षर *buf = (अचिन्हित अक्षर __क्रमce *)par->info->screen_base;

	fbsize = par->info->fix.smem_len;
	/* copy from vm to metromem */
	स_नकल(par->metromem_img, buf, fbsize);

	cksum = calc_img_cksum((u16 *) par->metromem_img, fbsize/2);
	*((u16 *)(par->metromem_img) + fbsize/2) = cksum;
	metronome_display_cmd(par);
पूर्ण

अटल u16 metronomefb_dpy_update_page(काष्ठा metronomefb_par *par, पूर्णांक index)
अणु
	पूर्णांक i;
	u16 csum = 0;
	u16 *buf = (u16 __क्रमce *)(par->info->screen_base + index);
	u16 *img = (u16 *)(par->metromem_img + index);

	/* swizzle from vm to metromem and recalc cksum at the same समय*/
	क्रम (i = 0; i < PAGE_SIZE/2; i++) अणु
		*(img + i) = (buf[i] << 5) & 0xE0E0;
		csum += *(img + i);
	पूर्ण
	वापस csum;
पूर्ण

/* this is called back from the deferred io workqueue */
अटल व्योम metronomefb_dpy_deferred_io(काष्ठा fb_info *info,
				काष्ठा list_head *pagelist)
अणु
	u16 cksum;
	काष्ठा page *cur;
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;
	काष्ठा metronomefb_par *par = info->par;

	/* walk the written page list and swizzle the data */
	list_क्रम_each_entry(cur, &fbdefio->pagelist, lru) अणु
		cksum = metronomefb_dpy_update_page(par,
					(cur->index << PAGE_SHIFT));
		par->metromem_img_csum -= par->csum_table[cur->index];
		par->csum_table[cur->index] = cksum;
		par->metromem_img_csum += cksum;
	पूर्ण

	metronome_display_cmd(par);
पूर्ण

अटल व्योम metronomefb_fillrect(काष्ठा fb_info *info,
				   स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा metronomefb_par *par = info->par;

	sys_fillrect(info, rect);
	metronomefb_dpy_update(par);
पूर्ण

अटल व्योम metronomefb_copyarea(काष्ठा fb_info *info,
				   स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा metronomefb_par *par = info->par;

	sys_copyarea(info, area);
	metronomefb_dpy_update(par);
पूर्ण

अटल व्योम metronomefb_imageblit(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा metronomefb_par *par = info->par;

	sys_imageblit(info, image);
	metronomefb_dpy_update(par);
पूर्ण

/*
 * this is the slow path from userspace. they can seek and ग_लिखो to
 * the fb. it is based on fb_sys_ग_लिखो
 */
अटल sमाप_प्रकार metronomefb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा metronomefb_par *par = info->par;
	अचिन्हित दीर्घ p = *ppos;
	व्योम *dst;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ total_size;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	total_size = info->fix.smem_len;

	अगर (p > total_size)
		वापस -EFBIG;

	अगर (count > total_size) अणु
		err = -EFBIG;
		count = total_size;
	पूर्ण

	अगर (count + p > total_size) अणु
		अगर (!err)
			err = -ENOSPC;

		count = total_size - p;
	पूर्ण

	dst = (व्योम __क्रमce *)(info->screen_base + p);

	अगर (copy_from_user(dst, buf, count))
		err = -EFAULT;

	अगर  (!err)
		*ppos += count;

	metronomefb_dpy_update(par);

	वापस (err) ? err : count;
पूर्ण

अटल स्थिर काष्ठा fb_ops metronomefb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_ग_लिखो	= metronomefb_ग_लिखो,
	.fb_fillrect	= metronomefb_fillrect,
	.fb_copyarea	= metronomefb_copyarea,
	.fb_imageblit	= metronomefb_imageblit,
पूर्ण;

अटल काष्ठा fb_deferred_io metronomefb_defio = अणु
	.delay		= HZ,
	.deferred_io	= metronomefb_dpy_deferred_io,
पूर्ण;

अटल पूर्णांक metronomefb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा metronome_board *board;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक videomemorysize;
	अचिन्हित अक्षर *videomemory;
	काष्ठा metronomefb_par *par;
	स्थिर काष्ठा firmware *fw_entry;
	पूर्णांक i;
	पूर्णांक panel_type;
	पूर्णांक fw, fh;
	पूर्णांक epd_dt_index;

	/* pick up board specअगरic routines */
	board = dev->dev.platक्रमm_data;
	अगर (!board)
		वापस -EINVAL;

	/* try to count device specअगरic driver, अगर can't, platक्रमm recalls */
	अगर (!try_module_get(board->owner))
		वापस -ENODEV;

	info = framebuffer_alloc(माप(काष्ठा metronomefb_par), &dev->dev);
	अगर (!info)
		जाओ err;

	/* we have two blocks of memory.
	info->screen_base which is vm, and is the fb used by apps.
	par->metromem which is physically contiguous memory and
	contains the display controller commands, waveक्रमm,
	processed image data and padding. this is the data pulled
	by the device's LCD controller and pushed to Metronome.
	the metromem memory is allocated by the board driver and
	is provided to us */

	panel_type = board->get_panel_type();
	चयन (panel_type) अणु
	हाल 6:
		epd_dt_index = 0;
		अवरोध;
	हाल 8:
		epd_dt_index = 1;
		अवरोध;
	हाल 97:
		epd_dt_index = 2;
		अवरोध;
	शेष:
		dev_err(&dev->dev, "Unexpected panel type. Defaulting to 6\n");
		epd_dt_index = 0;
		अवरोध;
	पूर्ण

	fw = epd_frame_table[epd_dt_index].fw;
	fh = epd_frame_table[epd_dt_index].fh;

	/* we need to add a spare page because our csum caching scheme walks
	 * to the end of the page */
	videomemorysize = PAGE_SIZE + (fw * fh);
	videomemory = vzalloc(videomemorysize);
	अगर (!videomemory)
		जाओ err_fb_rel;

	info->screen_base = (अक्षर __क्रमce __iomem *)videomemory;
	info->fbops = &metronomefb_ops;

	metronomefb_fix.line_length = fw;
	metronomefb_var.xres = fw;
	metronomefb_var.yres = fh;
	metronomefb_var.xres_भव = fw;
	metronomefb_var.yres_भव = fh;
	info->var = metronomefb_var;
	info->fix = metronomefb_fix;
	info->fix.smem_len = videomemorysize;
	par = info->par;
	par->info = info;
	par->board = board;
	par->dt = epd_dt_index;
	init_रुकोqueue_head(&par->रुकोq);

	/* this table caches per page csum values. */
	par->csum_table = vदो_स्मृति(videomemorysize/PAGE_SIZE);
	अगर (!par->csum_table)
		जाओ err_vमुक्त;

	/* the physical framebuffer that we use is setup by
	 * the platक्रमm device driver. It will provide us
	 * with cmd, wfm and image memory in a contiguous area. */
	retval = board->setup_fb(par);
	अगर (retval) अणु
		dev_err(&dev->dev, "Failed to setup fb\n");
		जाओ err_csum_table;
	पूर्ण

	/* after this poपूर्णांक we should have a framebuffer */
	अगर ((!par->metromem_wfm) ||  (!par->metromem_img) ||
		(!par->metromem_dma)) अणु
		dev_err(&dev->dev, "fb access failure\n");
		retval = -EINVAL;
		जाओ err_csum_table;
	पूर्ण

	info->fix.smem_start = par->metromem_dma;

	/* load the waveक्रमm in. assume mode 3, temp 31 क्रम now
		a) request the waveक्रमm file from userspace
		b) process waveक्रमm and decode पूर्णांकo metromem */
	retval = request_firmware(&fw_entry, "metronome.wbf", &dev->dev);
	अगर (retval < 0) अणु
		dev_err(&dev->dev, "Failed to get waveform\n");
		जाओ err_csum_table;
	पूर्ण

	retval = load_waveक्रमm((u8 *) fw_entry->data, fw_entry->size, 3, 31,
				par);
	release_firmware(fw_entry);
	अगर (retval < 0) अणु
		dev_err(&dev->dev, "Failed processing waveform\n");
		जाओ err_csum_table;
	पूर्ण

	retval = board->setup_irq(info);
	अगर (retval)
		जाओ err_csum_table;

	retval = metronome_init_regs(par);
	अगर (retval < 0)
		जाओ err_मुक्त_irq;

	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;

	info->fbdefio = &metronomefb_defio;
	fb_deferred_io_init(info);

	retval = fb_alloc_cmap(&info->cmap, 8, 0);
	अगर (retval < 0) अणु
		dev_err(&dev->dev, "Failed to allocate colormap\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	/* set cmap */
	क्रम (i = 0; i < 8; i++)
		info->cmap.red[i] = (((2*i)+1)*(0xFFFF))/16;
	स_नकल(info->cmap.green, info->cmap.red, माप(u16)*8);
	स_नकल(info->cmap.blue, info->cmap.red, माप(u16)*8);

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err_cmap;

	platक्रमm_set_drvdata(dev, info);

	dev_dbg(&dev->dev,
		"fb%d: Metronome frame buffer device, using %dK of video"
		" memory\n", info->node, videomemorysize >> 10);

	वापस 0;

err_cmap:
	fb_dealloc_cmap(&info->cmap);
err_मुक्त_irq:
	board->cleanup(par);
err_csum_table:
	vमुक्त(par->csum_table);
err_vमुक्त:
	vमुक्त(videomemory);
err_fb_rel:
	framebuffer_release(info);
err:
	module_put(board->owner);
	वापस retval;
पूर्ण

अटल पूर्णांक metronomefb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा metronomefb_par *par = info->par;

		unरेजिस्टर_framebuffer(info);
		fb_deferred_io_cleanup(info);
		fb_dealloc_cmap(&info->cmap);
		par->board->cleanup(par);
		vमुक्त(par->csum_table);
		vमुक्त((व्योम __क्रमce *)info->screen_base);
		module_put(par->board->owner);
		dev_dbg(&dev->dev, "calling release\n");
		framebuffer_release(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver metronomefb_driver = अणु
	.probe	= metronomefb_probe,
	.हटाओ = metronomefb_हटाओ,
	.driver	= अणु
		.name	= "metronomefb",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(metronomefb_driver);

module_param(user_wfm_size, uपूर्णांक, 0);
MODULE_PARM_DESC(user_wfm_size, "Set custom waveform size");

MODULE_DESCRIPTION("fbdev driver for Metronome controller");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");
