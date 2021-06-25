<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Frame Buffer Device क्रम Toshiba Mobile IO(TMIO) controller
 *
 * Copyright(C) 2005-2006 Chris Humbert
 * Copyright(C) 2005 Dirk Opfer
 * Copytight(C) 2007,2008 Dmitry Baryshkov
 *
 * Based on:
 *	drivers/video/w100fb.c
 *	code written by Sharp/Lineo क्रम 2.4 kernels
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
/* Why should fb driver call console functions? because console_lock() */
#समावेश <linux/console.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/uaccess.h>

/*
 * accelerator commands
 */
#घोषणा TMIOFB_ACC_CSADR(x)	(0x00000000 | ((x) & 0x001ffffe))
#घोषणा TMIOFB_ACC_CHPIX(x)	(0x01000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_CVPIX(x)	(0x02000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_PSADR(x)	(0x03000000 | ((x) & 0x00fffffe))
#घोषणा TMIOFB_ACC_PHPIX(x)	(0x04000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_PVPIX(x)	(0x05000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_PHOFS(x)	(0x06000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_PVOFS(x)	(0x07000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_POADR(x)	(0x08000000 | ((x) & 0x00fffffe))
#घोषणा TMIOFB_ACC_RSTR(x)	(0x09000000 | ((x) & 0x000000ff))
#घोषणा TMIOFB_ACC_TCLOR(x)	(0x0A000000 | ((x) & 0x0000ffff))
#घोषणा TMIOFB_ACC_FILL(x)	(0x0B000000 | ((x) & 0x0000ffff))
#घोषणा TMIOFB_ACC_DSADR(x)	(0x0C000000 | ((x) & 0x00fffffe))
#घोषणा TMIOFB_ACC_SSADR(x)	(0x0D000000 | ((x) & 0x00fffffe))
#घोषणा TMIOFB_ACC_DHPIX(x)	(0x0E000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_DVPIX(x)	(0x0F000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_SHPIX(x)	(0x10000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_SVPIX(x)	(0x11000000 | ((x) & 0x000003ff))
#घोषणा TMIOFB_ACC_LBINI(x)	(0x12000000 | ((x) & 0x0000ffff))
#घोषणा TMIOFB_ACC_LBK2(x)	(0x13000000 | ((x) & 0x0000ffff))
#घोषणा TMIOFB_ACC_SHBINI(x)	(0x14000000 | ((x) & 0x0000ffff))
#घोषणा TMIOFB_ACC_SHBK2(x)	(0x15000000 | ((x) & 0x0000ffff))
#घोषणा TMIOFB_ACC_SVBINI(x)	(0x16000000 | ((x) & 0x0000ffff))
#घोषणा TMIOFB_ACC_SVBK2(x)	(0x17000000 | ((x) & 0x0000ffff))

#घोषणा TMIOFB_ACC_CMGO		0x20000000
#घोषणा TMIOFB_ACC_CMGO_CEND	0x00000001
#घोषणा TMIOFB_ACC_CMGO_INT	0x00000002
#घोषणा TMIOFB_ACC_CMGO_CMOD	0x00000010
#घोषणा TMIOFB_ACC_CMGO_CDVRV	0x00000020
#घोषणा TMIOFB_ACC_CMGO_CDHRV	0x00000040
#घोषणा TMIOFB_ACC_CMGO_RUND	0x00008000
#घोषणा TMIOFB_ACC_SCGO		0x21000000
#घोषणा TMIOFB_ACC_SCGO_CEND	0x00000001
#घोषणा TMIOFB_ACC_SCGO_INT	0x00000002
#घोषणा TMIOFB_ACC_SCGO_ROP3	0x00000004
#घोषणा TMIOFB_ACC_SCGO_TRNS	0x00000008
#घोषणा TMIOFB_ACC_SCGO_DVRV	0x00000010
#घोषणा TMIOFB_ACC_SCGO_DHRV	0x00000020
#घोषणा TMIOFB_ACC_SCGO_SVRV	0x00000040
#घोषणा TMIOFB_ACC_SCGO_SHRV	0x00000080
#घोषणा TMIOFB_ACC_SCGO_DSTXY	0x00008000
#घोषणा TMIOFB_ACC_SBGO		0x22000000
#घोषणा TMIOFB_ACC_SBGO_CEND	0x00000001
#घोषणा TMIOFB_ACC_SBGO_INT	0x00000002
#घोषणा TMIOFB_ACC_SBGO_DVRV	0x00000010
#घोषणा TMIOFB_ACC_SBGO_DHRV	0x00000020
#घोषणा TMIOFB_ACC_SBGO_SVRV	0x00000040
#घोषणा TMIOFB_ACC_SBGO_SHRV	0x00000080
#घोषणा TMIOFB_ACC_SBGO_SBMD	0x00000100
#घोषणा TMIOFB_ACC_FLGO		0x23000000
#घोषणा TMIOFB_ACC_FLGO_CEND	0x00000001
#घोषणा TMIOFB_ACC_FLGO_INT	0x00000002
#घोषणा TMIOFB_ACC_FLGO_ROP3	0x00000004
#घोषणा TMIOFB_ACC_LDGO		0x24000000
#घोषणा TMIOFB_ACC_LDGO_CEND	0x00000001
#घोषणा TMIOFB_ACC_LDGO_INT	0x00000002
#घोषणा TMIOFB_ACC_LDGO_ROP3	0x00000004
#घोषणा TMIOFB_ACC_LDGO_ENDPX	0x00000008
#घोषणा TMIOFB_ACC_LDGO_LVRV	0x00000010
#घोषणा TMIOFB_ACC_LDGO_LHRV	0x00000020
#घोषणा TMIOFB_ACC_LDGO_LDMOD	0x00000040

/* a FIFO is always allocated, even अगर acceleration is not used */
#घोषणा TMIOFB_FIFO_SIZE	512

/*
 * LCD Host Controller Configuration Register
 *
 * This iomem area supports only 16-bit IO.
 */
#घोषणा CCR_CMD			0x04 /* Command				*/
#घोषणा CCR_REVID		0x08 /* Revision ID			*/
#घोषणा CCR_BASEL		0x10 /* LCD Control Reg Base Addr Low	*/
#घोषणा CCR_BASEH		0x12 /* LCD Control Reg Base Addr High	*/
#घोषणा CCR_UGCC		0x40 /* Unअगरied Gated Clock Control	*/
#घोषणा CCR_GCC			0x42 /* Gated Clock Control		*/
#घोषणा CCR_USC			0x50 /* Unअगरied Software Clear		*/
#घोषणा CCR_VRAMRTC		0x60 /* VRAM Timing Control		*/
				/* 0x61 VRAM Refresh Control		*/
#घोषणा CCR_VRAMSAC		0x62 /* VRAM Access Control		*/
				/* 0x63	VRAM Status			*/
#घोषणा CCR_VRAMBC		0x64 /* VRAM Block Control		*/

/*
 * LCD Control Register
 *
 * This iomem area supports only 16-bit IO.
 */
#घोषणा LCR_UIS			0x000 /* Unअगरied Interrupt Status	*/
#घोषणा LCR_VHPN		0x008 /* VRAM Horizontal Pixel Number	*/
#घोषणा LCR_CFSAL		0x00a /* Command FIFO Start Address Low	*/
#घोषणा LCR_CFSAH		0x00c /* Command FIFO Start Address High */
#घोषणा LCR_CFS			0x00e /* Command FIFO Size		*/
#घोषणा LCR_CFWS		0x010 /* Command FIFO Writeable Size	*/
#घोषणा LCR_BBIE		0x012 /* BitBLT Interrupt Enable	*/
#घोषणा LCR_BBISC		0x014 /* BitBLT Interrupt Status and Clear */
#घोषणा LCR_CCS			0x016 /* Command Count Status		*/
#घोषणा LCR_BBES		0x018 /* BitBLT Execution Status	*/
#घोषणा LCR_CMDL		0x01c /* Command Low			*/
#घोषणा LCR_CMDH		0x01e /* Command High			*/
#घोषणा LCR_CFC			0x022 /* Command FIFO Clear		*/
#घोषणा LCR_CCIFC		0x024 /* CMOS Camera IF Control		*/
#घोषणा LCR_HWT			0x026 /* Hardware Test			*/
#घोषणा LCR_LCDCCRC		0x100 /* LCDC Clock and Reset Control	*/
#घोषणा LCR_LCDCC		0x102 /* LCDC Control			*/
#घोषणा LCR_LCDCOPC		0x104 /* LCDC Output Pin Control	*/
#घोषणा LCR_LCDIS		0x108 /* LCD Interrupt Status		*/
#घोषणा LCR_LCDIM		0x10a /* LCD Interrupt Mask		*/
#घोषणा LCR_LCDIE		0x10c /* LCD Interrupt Enable		*/
#घोषणा LCR_GDSAL		0x122 /* Graphics Display Start Address Low */
#घोषणा LCR_GDSAH		0x124 /* Graphics Display Start Address High */
#घोषणा LCR_VHPCL		0x12a /* VRAM Horizontal Pixel Count Low */
#घोषणा LCR_VHPCH		0x12c /* VRAM Horizontal Pixel Count High */
#घोषणा LCR_GM			0x12e /* Graphic Mode(VRAM access enable) */
#घोषणा LCR_HT			0x140 /* Horizontal Total		*/
#घोषणा LCR_HDS			0x142 /* Horizontal Display Start	*/
#घोषणा LCR_HSS			0x144 /* H-Sync Start			*/
#घोषणा LCR_HSE			0x146 /* H-Sync End			*/
#घोषणा LCR_HNP			0x14c /* Horizontal Number of Pixels	*/
#घोषणा LCR_VT			0x150 /* Vertical Total			*/
#घोषणा LCR_VDS			0x152 /* Vertical Display Start		*/
#घोषणा LCR_VSS			0x154 /* V-Sync Start			*/
#घोषणा LCR_VSE			0x156 /* V-Sync End			*/
#घोषणा LCR_CDLN		0x160 /* Current Display Line Number	*/
#घोषणा LCR_ILN			0x162 /* Interrupt Line Number		*/
#घोषणा LCR_SP			0x164 /* Sync Polarity			*/
#घोषणा LCR_MISC		0x166 /* MISC(RGB565 mode)		*/
#घोषणा LCR_VIHSS		0x16a /* Video Interface H-Sync Start	*/
#घोषणा LCR_VIVS		0x16c /* Video Interface Vertical Start	*/
#घोषणा LCR_VIVE		0x16e /* Video Interface Vertical End	*/
#घोषणा LCR_VIVSS		0x170 /* Video Interface V-Sync Start	*/
#घोषणा LCR_VCCIS		0x17e /* Video / CMOS Camera Interface Select */
#घोषणा LCR_VIDWSAL		0x180 /* VI Data Write Start Address Low */
#घोषणा LCR_VIDWSAH		0x182 /* VI Data Write Start Address High */
#घोषणा LCR_VIDRSAL		0x184 /* VI Data Read Start Address Low	*/
#घोषणा LCR_VIDRSAH		0x186 /* VI Data Read Start Address High */
#घोषणा LCR_VIPDDST		0x188 /* VI Picture Data Display Start Timing */
#घोषणा LCR_VIPDDET		0x186 /* VI Picture Data Display End Timing */
#घोषणा LCR_VIE			0x18c /* Video Interface Enable		*/
#घोषणा LCR_VCS			0x18e /* Video/Camera Select		*/
#घोषणा LCR_VPHWC		0x194 /* Video Picture Horizontal Wait Count */
#घोषणा LCR_VPHS		0x196 /* Video Picture Horizontal Size	*/
#घोषणा LCR_VPVWC		0x198 /* Video Picture Vertical Wait Count */
#घोषणा LCR_VPVS		0x19a /* Video Picture Vertical Size	*/
#घोषणा LCR_PLHPIX		0x1a0 /* PLHPIX				*/
#घोषणा LCR_XS			0x1a2 /* XStart				*/
#घोषणा LCR_XCKHW		0x1a4 /* XCK High Width			*/
#घोषणा LCR_STHS		0x1a8 /* STH Start			*/
#घोषणा LCR_VT2			0x1aa /* Vertical Total			*/
#घोषणा LCR_YCKSW		0x1ac /* YCK Start Wait			*/
#घोषणा LCR_YSTS		0x1ae /* YST Start			*/
#घोषणा LCR_PPOLS		0x1b0 /* #PPOL Start			*/
#घोषणा LCR_PRECW		0x1b2 /* PREC Width			*/
#घोषणा LCR_VCLKHW		0x1b4 /* VCLK High Width		*/
#घोषणा LCR_OC			0x1b6 /* Output Control			*/

अटल अक्षर *mode_option;

काष्ठा पंचांगiofb_par अणु
	u32				pseuकरो_palette[16];

#अगर_घोषित CONFIG_FB_TMIO_ACCELL
	रुको_queue_head_t		रुको_acc;
	bool				use_polling;
#पूर्ण_अगर

	व्योम __iomem			*ccr;
	व्योम __iomem			*lcr;
पूर्ण;

/*--------------------------------------------------------------------------*/

/*
 * reasons क्रम an पूर्णांकerrupt:
 *	uis	bbisc	lcdis
 *	0100	0001	accelerator command completed
 * 	2000	0001	vsync start
 * 	2000	0002	display start
 * 	2000	0004	line number match(0x1ff mask???)
 */
अटल irqवापस_t पंचांगiofb_irq(पूर्णांक irq, व्योम *__info)
अणु
	काष्ठा fb_info *info = __info;
	काष्ठा पंचांगiofb_par *par = info->par;
	अचिन्हित पूर्णांक bbisc = पंचांगio_ioपढ़ो16(par->lcr + LCR_BBISC);


	पंचांगio_ioग_लिखो16(bbisc, par->lcr + LCR_BBISC);

#अगर_घोषित CONFIG_FB_TMIO_ACCELL
	/*
	 * We were in polling mode and now we got correct irq.
	 * Switch back to IRQ-based sync of command FIFO
	 */
	अगर (unlikely(par->use_polling && irq != -1)) अणु
		prपूर्णांकk(KERN_INFO "tmiofb: switching to waitq\n");
		par->use_polling = false;
	पूर्ण

	अगर (bbisc & 1)
		wake_up(&par->रुको_acc);
#पूर्ण_अगर

	वापस IRQ_HANDLED;
पूर्ण


/*--------------------------------------------------------------------------*/


/*
 * Turns off the LCD controller and LCD host controller.
 */
अटल पूर्णांक पंचांगiofb_hw_stop(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा पंचांगio_fb_data *data = dev_get_platdata(&dev->dev);
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा पंचांगiofb_par *par = info->par;

	पंचांगio_ioग_लिखो16(0, par->ccr + CCR_UGCC);
	पंचांगio_ioग_लिखो16(0, par->lcr + LCR_GM);
	data->lcd_set_घातer(dev, 0);
	पंचांगio_ioग_लिखो16(0x0010, par->lcr + LCR_LCDCCRC);

	वापस 0;
पूर्ण

/*
 * Initializes the LCD host controller.
 */
अटल पूर्णांक पंचांगiofb_hw_init(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा पंचांगiofb_par *par = info->par;
	स्थिर काष्ठा resource *nlcr = &cell->resources[0];
	स्थिर काष्ठा resource *vram = &cell->resources[2];
	अचिन्हित दीर्घ base;

	अगर (nlcr == शून्य || vram == शून्य)
		वापस -EINVAL;

	base = nlcr->start;

	पंचांगio_ioग_लिखो16(0x003a, par->ccr + CCR_UGCC);
	पंचांगio_ioग_लिखो16(0x003a, par->ccr + CCR_GCC);
	पंचांगio_ioग_लिखो16(0x3f00, par->ccr + CCR_USC);

	msleep(2); /* रुको क्रम device to settle */

	पंचांगio_ioग_लिखो16(0x0000, par->ccr + CCR_USC);
	पंचांगio_ioग_लिखो16(base >> 16, par->ccr + CCR_BASEH);
	पंचांगio_ioग_लिखो16(base, par->ccr + CCR_BASEL);
	पंचांगio_ioग_लिखो16(0x0002, par->ccr + CCR_CMD); /* base address enable */
	पंचांगio_ioग_लिखो16(0x40a8, par->ccr + CCR_VRAMRTC); /* VRAMRC, VRAMTC */
	पंचांगio_ioग_लिखो16(0x0018, par->ccr + CCR_VRAMSAC); /* VRAMSTS, VRAMAC */
	पंचांगio_ioग_लिखो16(0x0002, par->ccr + CCR_VRAMBC);
	msleep(2); /* रुको क्रम device to settle */
	पंचांगio_ioग_लिखो16(0x000b, par->ccr + CCR_VRAMBC);

	base = vram->start + info->screen_size;
	पंचांगio_ioग_लिखो16(base >> 16, par->lcr + LCR_CFSAH);
	पंचांगio_ioग_लिखो16(base, par->lcr + LCR_CFSAL);
	पंचांगio_ioग_लिखो16(TMIOFB_FIFO_SIZE - 1, par->lcr + LCR_CFS);
	पंचांगio_ioग_लिखो16(1, par->lcr + LCR_CFC);
	पंचांगio_ioग_लिखो16(1, par->lcr + LCR_BBIE);
	पंचांगio_ioग_लिखो16(0, par->lcr + LCR_CFWS);

	वापस 0;
पूर्ण

/*
 * Sets the LCD controller's output resolution and pixel घड़ी
 */
अटल व्योम पंचांगiofb_hw_mode(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा पंचांगio_fb_data *data = dev_get_platdata(&dev->dev);
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा fb_videomode *mode = info->mode;
	काष्ठा पंचांगiofb_par *par = info->par;
	अचिन्हित पूर्णांक i;

	पंचांगio_ioग_लिखो16(0, par->lcr + LCR_GM);
	data->lcd_set_घातer(dev, 0);
	पंचांगio_ioग_लिखो16(0x0010, par->lcr + LCR_LCDCCRC);
	data->lcd_mode(dev, mode);
	data->lcd_set_घातer(dev, 1);

	पंचांगio_ioग_लिखो16(info->fix.line_length, par->lcr + LCR_VHPN);
	पंचांगio_ioग_लिखो16(0, par->lcr + LCR_GDSAH);
	पंचांगio_ioग_लिखो16(0, par->lcr + LCR_GDSAL);
	पंचांगio_ioग_लिखो16(info->fix.line_length >> 16, par->lcr + LCR_VHPCH);
	पंचांगio_ioग_लिखो16(info->fix.line_length, par->lcr + LCR_VHPCL);
	पंचांगio_ioग_लिखो16(i = 0, par->lcr + LCR_HSS);
	पंचांगio_ioग_लिखो16(i += mode->hsync_len, par->lcr + LCR_HSE);
	पंचांगio_ioग_लिखो16(i += mode->left_margin, par->lcr + LCR_HDS);
	पंचांगio_ioग_लिखो16(i += mode->xres + mode->right_margin, par->lcr + LCR_HT);
	पंचांगio_ioग_लिखो16(mode->xres, par->lcr + LCR_HNP);
	पंचांगio_ioग_लिखो16(i = 0, par->lcr + LCR_VSS);
	पंचांगio_ioग_लिखो16(i += mode->vsync_len, par->lcr + LCR_VSE);
	पंचांगio_ioग_लिखो16(i += mode->upper_margin, par->lcr + LCR_VDS);
	पंचांगio_ioग_लिखो16(i += mode->yres, par->lcr + LCR_ILN);
	पंचांगio_ioग_लिखो16(i += mode->lower_margin, par->lcr + LCR_VT);
	पंचांगio_ioग_लिखो16(3, par->lcr + LCR_MISC); /* RGB565 mode */
	पंचांगio_ioग_लिखो16(1, par->lcr + LCR_GM); /* VRAM enable */
	पंचांगio_ioग_लिखो16(0x4007, par->lcr + LCR_LCDCC);
	पंचांगio_ioग_लिखो16(3, par->lcr + LCR_SP);  /* sync polarity */

	पंचांगio_ioग_लिखो16(0x0010, par->lcr + LCR_LCDCCRC);
	msleep(5); /* रुको क्रम device to settle */
	पंचांगio_ioग_लिखो16(0x0014, par->lcr + LCR_LCDCCRC); /* STOP_CKP */
	msleep(5); /* रुको क्रम device to settle */
	पंचांगio_ioग_लिखो16(0x0015, par->lcr + LCR_LCDCCRC); /* STOP_CKP|SOFT_RESET*/
	पंचांगio_ioग_लिखो16(0xfffa, par->lcr + LCR_VCS);
पूर्ण

/*--------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_FB_TMIO_ACCELL
अटल पूर्णांक __must_check
पंचांगiofb_acc_रुको(काष्ठा fb_info *info, अचिन्हित पूर्णांक ccs)
अणु
	काष्ठा पंचांगiofb_par *par = info->par;
	/*
	 * This code can be called with पूर्णांकerrupts disabled.
	 * So instead of relaying on irq to trigger the event,
	 * poll the state till the necessary command is executed.
	 */
	अगर (irqs_disabled() || par->use_polling) अणु
		पूर्णांक i = 0;
		जबतक (पंचांगio_ioपढ़ो16(par->lcr + LCR_CCS) > ccs) अणु
			udelay(1);
			i++;
			अगर (i > 10000) अणु
				pr_err("tmiofb: timeout waiting for %d\n",
						ccs);
				वापस -ETIMEDOUT;
			पूर्ण
			पंचांगiofb_irq(-1, info);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!रुको_event_पूर्णांकerruptible_समयout(par->रुको_acc,
				पंचांगio_ioपढ़ो16(par->lcr + LCR_CCS) <= ccs,
				1000)) अणु
			pr_err("tmiofb: timeout waiting for %d\n", ccs);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Writes an accelerator command to the accelerator's FIFO.
 */
अटल पूर्णांक
पंचांगiofb_acc_ग_लिखो(काष्ठा fb_info *info, स्थिर u32 *cmd, अचिन्हित पूर्णांक count)
अणु
	काष्ठा पंचांगiofb_par *par = info->par;
	पूर्णांक ret;

	ret = पंचांगiofb_acc_रुको(info, TMIOFB_FIFO_SIZE - count);
	अगर (ret)
		वापस ret;

	क्रम (; count; count--, cmd++) अणु
		पंचांगio_ioग_लिखो16(*cmd >> 16, par->lcr + LCR_CMDH);
		पंचांगio_ioग_लिखो16(*cmd, par->lcr + LCR_CMDL);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Wait क्रम the accelerator to finish its operations beक्रमe writing
 * to the framebuffer क्रम consistent display output.
 */
अटल पूर्णांक पंचांगiofb_sync(काष्ठा fb_info *fbi)
अणु
	काष्ठा पंचांगiofb_par *par = fbi->par;

	पूर्णांक ret;
	पूर्णांक i = 0;

	ret = पंचांगiofb_acc_रुको(fbi, 0);

	जबतक (पंचांगio_ioपढ़ो16(par->lcr + LCR_BBES) & 2) अणु /* blit active */
		udelay(1);
		i++ ;
		अगर (i > 10000) अणु
			prपूर्णांकk(KERN_ERR "timeout waiting for blit to end!\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
पंचांगiofb_fillrect(काष्ठा fb_info *fbi, स्थिर काष्ठा fb_fillrect *rect)
अणु
	स्थिर u32 cmd[] = अणु
		TMIOFB_ACC_DSADR((rect->dy * fbi->mode->xres + rect->dx) * 2),
		TMIOFB_ACC_DHPIX(rect->width - 1),
		TMIOFB_ACC_DVPIX(rect->height - 1),
		TMIOFB_ACC_FILL(rect->color),
		TMIOFB_ACC_FLGO,
	पूर्ण;

	अगर (fbi->state != FBINFO_STATE_RUNNING ||
	    fbi->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_fillrect(fbi, rect);
		वापस;
	पूर्ण

	पंचांगiofb_acc_ग_लिखो(fbi, cmd, ARRAY_SIZE(cmd));
पूर्ण

अटल व्योम
पंचांगiofb_copyarea(काष्ठा fb_info *fbi, स्थिर काष्ठा fb_copyarea *area)
अणु
	स्थिर u32 cmd[] = अणु
		TMIOFB_ACC_DSADR((area->dy * fbi->mode->xres + area->dx) * 2),
		TMIOFB_ACC_DHPIX(area->width - 1),
		TMIOFB_ACC_DVPIX(area->height - 1),
		TMIOFB_ACC_SSADR((area->sy * fbi->mode->xres + area->sx) * 2),
		TMIOFB_ACC_SCGO,
	पूर्ण;

	अगर (fbi->state != FBINFO_STATE_RUNNING ||
	    fbi->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_copyarea(fbi, area);
		वापस;
	पूर्ण

	पंचांगiofb_acc_ग_लिखो(fbi, cmd, ARRAY_SIZE(cmd));
पूर्ण
#पूर्ण_अगर

अटल व्योम पंचांगiofb_clearscreen(काष्ठा fb_info *info)
अणु
	स्थिर काष्ठा fb_fillrect rect = अणु
		.dx	= 0,
		.dy	= 0,
		.width	= info->mode->xres,
		.height	= info->mode->yres,
		.color	= 0,
		.rop	= ROP_COPY,
	पूर्ण;

	info->fbops->fb_fillrect(info, &rect);
पूर्ण

अटल पूर्णांक पंचांगiofb_vblank(काष्ठा fb_info *fbi, काष्ठा fb_vblank *vblank)
अणु
	काष्ठा पंचांगiofb_par *par = fbi->par;
	काष्ठा fb_videomode *mode = fbi->mode;
	अचिन्हित पूर्णांक vcount = पंचांगio_ioपढ़ो16(par->lcr + LCR_CDLN);
	अचिन्हित पूर्णांक vds = mode->vsync_len + mode->upper_margin;

	vblank->vcount = vcount;
	vblank->flags = FB_VBLANK_HAVE_VBLANK | FB_VBLANK_HAVE_VCOUNT
						| FB_VBLANK_HAVE_VSYNC;

	अगर (vcount < mode->vsync_len)
		vblank->flags |= FB_VBLANK_VSYNCING;

	अगर (vcount < vds || vcount > vds + mode->yres)
		vblank->flags |= FB_VBLANK_VBLANKING;

	वापस 0;
पूर्ण


अटल पूर्णांक पंचांगiofb_ioctl(काष्ठा fb_info *fbi,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल FBIOGET_VBLANK: अणु
		काष्ठा fb_vblank vblank = अणु0पूर्ण;
		व्योम __user *argp = (व्योम __user *) arg;

		पंचांगiofb_vblank(fbi, &vblank);
		अगर (copy_to_user(argp, &vblank, माप vblank))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_FB_TMIO_ACCELL
	हाल FBIO_TMIO_ACC_SYNC:
		पंचांगiofb_sync(fbi);
		वापस 0;

	हाल FBIO_TMIO_ACC_WRITE: अणु
		u32 __user *argp = (व्योम __user *) arg;
		u32 len;
		u32 acc[16];

		अगर (get_user(len, argp))
			वापस -EFAULT;
		अगर (len > ARRAY_SIZE(acc))
			वापस -EINVAL;
		अगर (copy_from_user(acc, argp + 1, माप(u32) * len))
			वापस -EFAULT;

		वापस पंचांगiofb_acc_ग_लिखो(fbi, acc, len);
	पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस -ENOTTY;
पूर्ण

/*--------------------------------------------------------------------------*/

/* Select the smallest mode that allows the desired resolution to be
 * displayed.  If desired, the x and y parameters can be rounded up to
 * match the selected mode.
 */
अटल काष्ठा fb_videomode *
पंचांगiofb_find_mode(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा पंचांगio_fb_data *data = dev_get_platdata(info->device);
	काष्ठा fb_videomode *best = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < data->num_modes; i++) अणु
		काष्ठा fb_videomode *mode = data->modes + i;

		अगर (mode->xres >= var->xres && mode->yres >= var->yres
				&& (!best || (mode->xres < best->xres
					   && mode->yres < best->yres)))
			best = mode;
	पूर्ण

	वापस best;
पूर्ण

अटल पूर्णांक पंचांगiofb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु

	काष्ठा fb_videomode *mode;
	काष्ठा पंचांगio_fb_data *data = dev_get_platdata(info->device);

	mode = पंचांगiofb_find_mode(info, var);
	अगर (!mode || var->bits_per_pixel > 16)
		वापस -EINVAL;

	fb_videomode_to_var(var, mode);

	var->xres_भव = mode->xres;
	var->yres_भव = info->screen_size / (mode->xres * 2);

	अगर (var->yres_भव < var->yres)
		वापस -EINVAL;

	var->xoffset = 0;
	var->yoffset = 0;
	var->bits_per_pixel = 16;
	var->grayscale = 0;
	var->red.offset = 11;
	var->red.length = 5;
	var->green.offset = 5;
	var->green.length = 6;
	var->blue.offset = 0;
	var->blue.length = 5;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->nonstd = 0;
	var->height = data->height; /* mm */
	var->width = data->width; /* mm */
	var->rotate = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगiofb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा fb_videomode *mode;

	mode = पंचांगiofb_find_mode(info, var);
	अगर (!mode)
		वापस -EINVAL;

	info->mode = mode;
	info->fix.line_length = info->mode->xres *
			var->bits_per_pixel / 8;

	पंचांगiofb_hw_mode(to_platक्रमm_device(info->device));
	पंचांगiofb_clearscreen(info);
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगiofb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	काष्ठा पंचांगiofb_par *par = info->par;

	अगर (regno < ARRAY_SIZE(par->pseuकरो_palette)) अणु
		par->pseuकरो_palette[regno] =
			((red & 0xf800)) |
			((green & 0xfc00) >>  5) |
			((blue & 0xf800) >> 11);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पंचांगiofb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	/*
	 * everything is करोne in lcd/bl drivers.
	 * this is purely to make sysfs happy and work.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops पंचांगiofb_ops = अणु
	.owner		= THIS_MODULE,

	.fb_ioctl	= पंचांगiofb_ioctl,
	.fb_check_var	= पंचांगiofb_check_var,
	.fb_set_par	= पंचांगiofb_set_par,
	.fb_setcolreg	= पंचांगiofb_setcolreg,
	.fb_blank	= पंचांगiofb_blank,
	.fb_imageblit	= cfb_imageblit,
#अगर_घोषित CONFIG_FB_TMIO_ACCELL
	.fb_sync	= पंचांगiofb_sync,
	.fb_fillrect	= पंचांगiofb_fillrect,
	.fb_copyarea	= पंचांगiofb_copyarea,
#अन्यथा
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
#पूर्ण_अगर
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल पूर्णांक पंचांगiofb_probe(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	काष्ठा पंचांगio_fb_data *data = dev_get_platdata(&dev->dev);
	काष्ठा resource *ccr = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	काष्ठा resource *lcr = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	काष्ठा resource *vram = platक्रमm_get_resource(dev, IORESOURCE_MEM, 2);
	पूर्णांक irq = platक्रमm_get_irq(dev, 0);
	काष्ठा fb_info *info;
	काष्ठा पंचांगiofb_par *par;
	पूर्णांक retval;

	/*
	 * This is the only way ATM to disable the fb
	 */
	अगर (data == शून्य) अणु
		dev_err(&dev->dev, "NULL platform data!\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ccr == शून्य || lcr == शून्य || vram == शून्य || irq < 0) अणु
		dev_err(&dev->dev, "missing resources\n");
		वापस -EINVAL;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा पंचांगiofb_par), &dev->dev);

	अगर (!info)
		वापस -ENOMEM;

	par = info->par;

#अगर_घोषित CONFIG_FB_TMIO_ACCELL
	init_रुकोqueue_head(&par->रुको_acc);

	par->use_polling = true;

	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_COPYAREA
			| FBINFO_HWACCEL_FILLRECT;
#अन्यथा
	info->flags = FBINFO_DEFAULT;
#पूर्ण_अगर

	info->fbops = &पंचांगiofb_ops;

	म_नकल(info->fix.id, "tmio-fb");
	info->fix.smem_start = vram->start;
	info->fix.smem_len = resource_size(vram);
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;
	info->fix.mmio_start = lcr->start;
	info->fix.mmio_len = resource_size(lcr);
	info->fix.accel = FB_ACCEL_NONE;
	info->screen_size = info->fix.smem_len - (4 * TMIOFB_FIFO_SIZE);
	info->pseuकरो_palette = par->pseuकरो_palette;

	par->ccr = ioremap(ccr->start, resource_size(ccr));
	अगर (!par->ccr) अणु
		retval = -ENOMEM;
		जाओ err_ioremap_ccr;
	पूर्ण

	par->lcr = ioremap(info->fix.mmio_start, info->fix.mmio_len);
	अगर (!par->lcr) अणु
		retval = -ENOMEM;
		जाओ err_ioremap_lcr;
	पूर्ण

	info->screen_base = ioremap(info->fix.smem_start, info->fix.smem_len);
	अगर (!info->screen_base) अणु
		retval = -ENOMEM;
		जाओ err_ioremap_vram;
	पूर्ण

	retval = request_irq(irq, &पंचांगiofb_irq, 0,
					dev_name(&dev->dev), info);

	अगर (retval)
		जाओ err_request_irq;

	platक्रमm_set_drvdata(dev, info);

	retval = fb_find_mode(&info->var, info, mode_option,
			data->modes, data->num_modes,
			data->modes, 16);
	अगर (!retval) अणु
		retval = -EINVAL;
		जाओ err_find_mode;
	पूर्ण

	अगर (cell->enable) अणु
		retval = cell->enable(dev);
		अगर (retval)
			जाओ err_enable;
	पूर्ण

	retval = पंचांगiofb_hw_init(dev);
	अगर (retval)
		जाओ err_hw_init;

	fb_videomode_to_modelist(data->modes, data->num_modes,
				 &info->modelist);

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err_रेजिस्टर_framebuffer;

	fb_info(info, "%s frame buffer device\n", info->fix.id);

	वापस 0;

err_रेजिस्टर_framebuffer:
/*err_set_par:*/
	पंचांगiofb_hw_stop(dev);
err_hw_init:
	अगर (cell->disable)
		cell->disable(dev);
err_enable:
err_find_mode:
	मुक्त_irq(irq, info);
err_request_irq:
	iounmap(info->screen_base);
err_ioremap_vram:
	iounmap(par->lcr);
err_ioremap_lcr:
	iounmap(par->ccr);
err_ioremap_ccr:
	framebuffer_release(info);
	वापस retval;
पूर्ण

अटल पूर्णांक पंचांगiofb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	पूर्णांक irq = platक्रमm_get_irq(dev, 0);
	काष्ठा पंचांगiofb_par *par;

	अगर (info) अणु
		par = info->par;
		unरेजिस्टर_framebuffer(info);

		पंचांगiofb_hw_stop(dev);

		अगर (cell->disable)
			cell->disable(dev);

		मुक्त_irq(irq, info);

		iounmap(info->screen_base);
		iounmap(par->lcr);
		iounmap(par->ccr);

		framebuffer_release(info);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम पंचांगiofb_dump_regs(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा पंचांगiofb_par *par = info->par;

	prपूर्णांकk(KERN_DEBUG "lhccr:\n");
#घोषणा CCR_PR(n)	prपूर्णांकk(KERN_DEBUG "\t" #n " = \t%04x\n",\
		पंचांगio_ioपढ़ो16(par->ccr + CCR_ ## n));
	CCR_PR(CMD);
	CCR_PR(REVID);
	CCR_PR(BASEL);
	CCR_PR(BASEH);
	CCR_PR(UGCC);
	CCR_PR(GCC);
	CCR_PR(USC);
	CCR_PR(VRAMRTC);
	CCR_PR(VRAMSAC);
	CCR_PR(VRAMBC);
#अघोषित CCR_PR

	prपूर्णांकk(KERN_DEBUG "lcr: \n");
#घोषणा LCR_PR(n)	prपूर्णांकk(KERN_DEBUG "\t" #n " = \t%04x\n",\
		पंचांगio_ioपढ़ो16(par->lcr + LCR_ ## n));
	LCR_PR(UIS);
	LCR_PR(VHPN);
	LCR_PR(CFSAL);
	LCR_PR(CFSAH);
	LCR_PR(CFS);
	LCR_PR(CFWS);
	LCR_PR(BBIE);
	LCR_PR(BBISC);
	LCR_PR(CCS);
	LCR_PR(BBES);
	LCR_PR(CMDL);
	LCR_PR(CMDH);
	LCR_PR(CFC);
	LCR_PR(CCIFC);
	LCR_PR(HWT);
	LCR_PR(LCDCCRC);
	LCR_PR(LCDCC);
	LCR_PR(LCDCOPC);
	LCR_PR(LCDIS);
	LCR_PR(LCDIM);
	LCR_PR(LCDIE);
	LCR_PR(GDSAL);
	LCR_PR(GDSAH);
	LCR_PR(VHPCL);
	LCR_PR(VHPCH);
	LCR_PR(GM);
	LCR_PR(HT);
	LCR_PR(HDS);
	LCR_PR(HSS);
	LCR_PR(HSE);
	LCR_PR(HNP);
	LCR_PR(VT);
	LCR_PR(VDS);
	LCR_PR(VSS);
	LCR_PR(VSE);
	LCR_PR(CDLN);
	LCR_PR(ILN);
	LCR_PR(SP);
	LCR_PR(MISC);
	LCR_PR(VIHSS);
	LCR_PR(VIVS);
	LCR_PR(VIVE);
	LCR_PR(VIVSS);
	LCR_PR(VCCIS);
	LCR_PR(VIDWSAL);
	LCR_PR(VIDWSAH);
	LCR_PR(VIDRSAL);
	LCR_PR(VIDRSAH);
	LCR_PR(VIPDDST);
	LCR_PR(VIPDDET);
	LCR_PR(VIE);
	LCR_PR(VCS);
	LCR_PR(VPHWC);
	LCR_PR(VPHS);
	LCR_PR(VPVWC);
	LCR_PR(VPVS);
	LCR_PR(PLHPIX);
	LCR_PR(XS);
	LCR_PR(XCKHW);
	LCR_PR(STHS);
	LCR_PR(VT2);
	LCR_PR(YCKSW);
	LCR_PR(YSTS);
	LCR_PR(PPOLS);
	LCR_PR(PRECW);
	LCR_PR(VCLKHW);
	LCR_PR(OC);
#अघोषित LCR_PR
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक पंचांगiofb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
#अगर_घोषित CONFIG_FB_TMIO_ACCELL
	काष्ठा पंचांगiofb_par *par = info->par;
#पूर्ण_अगर
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	पूर्णांक retval = 0;

	console_lock();

	fb_set_suspend(info, 1);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);


#अगर_घोषित CONFIG_FB_TMIO_ACCELL
	/*
	 * The fb should be usable even अगर पूर्णांकerrupts are disabled (and they are
	 * during suspend/resume). Switch temporary to क्रमced polling.
	 */
	prपूर्णांकk(KERN_INFO "tmiofb: switching to polling\n");
	par->use_polling = true;
#पूर्ण_अगर
	पंचांगiofb_hw_stop(dev);

	अगर (cell->suspend)
		retval = cell->suspend(dev);

	console_unlock();

	वापस retval;
पूर्ण

अटल पूर्णांक पंचांगiofb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	पूर्णांक retval = 0;

	console_lock();

	अगर (cell->resume) अणु
		retval = cell->resume(dev);
		अगर (retval)
			जाओ out;
	पूर्ण

	पंचांगiofb_irq(-1, info);

	पंचांगiofb_hw_init(dev);

	पंचांगiofb_hw_mode(dev);

	fb_set_suspend(info, 0);
out:
	console_unlock();
	वापस retval;
पूर्ण
#अन्यथा
#घोषणा पंचांगiofb_suspend	शून्य
#घोषणा पंचांगiofb_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver पंचांगiofb_driver = अणु
	.driver.name	= "tmio-fb",
	.driver.owner	= THIS_MODULE,
	.probe		= पंचांगiofb_probe,
	.हटाओ		= पंचांगiofb_हटाओ,
	.suspend	= पंचांगiofb_suspend,
	.resume		= पंचांगiofb_resume,
पूर्ण;

/*--------------------------------------------------------------------------*/

#अगर_अघोषित MODULE
अटल व्योम __init पंचांगiofb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;
		/*
		 * FIXME
		 */
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init पंचांगiofb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("tmiofb", &option))
		वापस -ENODEV;
	पंचांगiofb_setup(option);
#पूर्ण_अगर
	वापस platक्रमm_driver_रेजिस्टर(&पंचांगiofb_driver);
पूर्ण

अटल व्योम __निकास पंचांगiofb_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&पंचांगiofb_driver);
पूर्ण

module_init(पंचांगiofb_init);
module_निकास(पंचांगiofb_cleanup);

MODULE_DESCRIPTION("TMIO framebuffer driver");
MODULE_AUTHOR("Chris Humbert, Dirk Opfer, Dmitry Baryshkov");
MODULE_LICENSE("GPL");
