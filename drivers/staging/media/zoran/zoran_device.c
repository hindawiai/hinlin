<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zoran zr36057/zr36067 PCI controller driver, क्रम the
 * Pinnacle/Miro DC10/DC10+/DC30/DC30+, Iomega Buz, Linux
 * Media Lअसल LML33/LML33R10.
 *
 * This part handles device access (PCI/I2C/codec/...)
 *
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/पन.स>

#समावेश "videocodec.h"
#समावेश "zoran.h"
#समावेश "zoran_device.h"
#समावेश "zoran_card.h"

#घोषणा IRQ_MASK (ZR36057_ISR_GIRQ0 | \
		  ZR36057_ISR_GIRQ1 | \
		  ZR36057_ISR_JPEG_REP_IRQ)

अटल bool lml33dpath;		/* शेष = 0
				 * 1 will use digital path in capture
				 * mode instead of analog. It can be
				 * used क्रम picture adjusपंचांगents using
				 * tool like xawtv जबतक watching image
				 * on TV monitor connected to the output.
				 * However, due to असलence of 75 Ohm
				 * load on Bt819 input, there will be
				 * some image imperfections
				 */

module_param(lml33dpath, bool, 0644);
MODULE_PARM_DESC(lml33dpath, "Use digital path capture mode (on LML33 cards)");

पूर्णांक zr_set_buf(काष्ठा zoran *zr);
/*
 * initialize video front end
 */
अटल व्योम zr36057_init_vfe(काष्ठा zoran *zr)
अणु
	u32 reg;

	reg = btपढ़ो(ZR36057_VFESPFR);
	reg |= ZR36057_VFESPFR_LITTLE_ENDIAN;
	reg &= ~ZR36057_VFESPFR_VCLK_POL;
	reg |= ZR36057_VFESPFR_EXT_FL;
	reg |= ZR36057_VFESPFR_TOP_FIELD;
	btग_लिखो(reg, ZR36057_VFESPFR);
	reg = btपढ़ो(ZR36057_VDCR);
	अगर (pci_pci_problems & PCIPCI_TRITON)
		// || zr->revision < 1) // Revision 1 has also Triton support
		reg &= ~ZR36057_VDCR_TRITON;
	अन्यथा
		reg |= ZR36057_VDCR_TRITON;
	btग_लिखो(reg, ZR36057_VDCR);
पूर्ण

/*
 * General Purpose I/O and Guest bus access
 */

/*
 * This is a bit tricky. When a board lacks a GPIO function, the corresponding
 * GPIO bit number in the card_info काष्ठाure is set to 0.
 */

व्योम GPIO(काष्ठा zoran *zr, पूर्णांक bit, अचिन्हित पूर्णांक value)
अणु
	u32 reg;
	u32 mask;

	/* Make sure the bit number is legal
	 * A bit number of -1 (lacking) gives a mask of 0,
	 * making it harmless
	 */
	mask = (1 << (24 + bit)) & 0xff000000;
	reg = btपढ़ो(ZR36057_GPPGCR1) & ~mask;
	अगर (value)
		reg |= mask;

	btग_लिखो(reg, ZR36057_GPPGCR1);
	udelay(1);
पूर्ण

/*
 * Wait til post office is no दीर्घer busy
 */

पूर्णांक post_office_रुको(काष्ठा zoran *zr)
अणु
	u32 por;

//      जबतक (((por = btपढ़ो(ZR36057_POR)) & (ZR36057_POR_PO_PEN | ZR36057_POR_PO_TIME)) == ZR36057_POR_PO_PEN) अणु
	जबतक ((por = btपढ़ो(ZR36057_POR)) & ZR36057_POR_PO_PEN) अणु
		/* रुको क्रम something to happen */
		/* TODO add समयout */
	पूर्ण
	अगर ((por & ZR36057_POR_PO_TIME) && !zr->card.gws_not_connected) अणु
		/* In LML33/BUZ \GWS line is not connected, so it has always समयout set */
		pci_info(zr->pci_dev, "pop timeout %08x\n", por);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक post_office_ग_लिखो(काष्ठा zoran *zr, अचिन्हित पूर्णांक guest,
		      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	u32 por;

	por =
	    ZR36057_POR_PO_सूची | ZR36057_POR_PO_TIME | ((guest & 7) << 20) |
	    ((reg & 7) << 16) | (value & 0xFF);
	btग_लिखो(por, ZR36057_POR);

	वापस post_office_रुको(zr);
पूर्ण

पूर्णांक post_office_पढ़ो(काष्ठा zoran *zr, अचिन्हित पूर्णांक guest, अचिन्हित पूर्णांक reg)
अणु
	u32 por;

	por = ZR36057_POR_PO_TIME | ((guest & 7) << 20) | ((reg & 7) << 16);
	btग_लिखो(por, ZR36057_POR);
	अगर (post_office_रुको(zr) < 0)
		वापस -1;

	वापस btपढ़ो(ZR36057_POR) & 0xFF;
पूर्ण

/*
 * detect guests
 */

अटल व्योम dump_guests(काष्ठा zoran *zr)
अणु
	अगर (zr36067_debug > 2) अणु
		पूर्णांक i, guest[8];

		/* करो not prपूर्णांक अक्रमom data */
		guest[0] = 0;

		क्रम (i = 1; i < 8; i++) /* Don't पढ़ो jpeg codec here */
			guest[i] = post_office_पढ़ो(zr, i, 0);

		pci_info(zr->pci_dev, "Guests: %*ph\n", 8, guest);
	पूर्ण
पूर्ण

व्योम detect_guest_activity(काष्ठा zoran *zr)
अणु
	पूर्णांक समयout, i, j, res, guest[8], guest0[8], change[8][3];
	kसमय_प्रकार t0, t1;

	/* करो not prपूर्णांक अक्रमom data */
	guest[0] = 0;
	guest0[0] = 0;

	dump_guests(zr);
	pci_info(zr->pci_dev, "Detecting guests activity, please wait...\n");
	क्रम (i = 1; i < 8; i++) /* Don't पढ़ो jpeg codec here */
		guest0[i] = guest[i] = post_office_पढ़ो(zr, i, 0);

	समयout = 0;
	j = 0;
	t0 = kसमय_get();
	जबतक (समयout < 10000) अणु
		udelay(10);
		समयout++;
		क्रम (i = 1; (i < 8) && (j < 8); i++) अणु
			res = post_office_पढ़ो(zr, i, 0);
			अगर (res != guest[i]) अणु
				t1 = kसमय_get();
				change[j][0] = kसमय_प्रकारo_us(kसमय_sub(t1, t0));
				t0 = t1;
				change[j][1] = i;
				change[j][2] = res;
				j++;
				guest[i] = res;
			पूर्ण
		पूर्ण
		अगर (j >= 8)
			अवरोध;
	पूर्ण

	pci_info(zr->pci_dev, "Guests: %*ph\n", 8, guest0);

	अगर (j == 0) अणु
		pci_info(zr->pci_dev, "No activity detected.\n");
		वापस;
	पूर्ण
	क्रम (i = 0; i < j; i++)
		pci_info(zr->pci_dev, "%6d: %d => 0x%02x\n", change[i][0], change[i][1], change[i][2]);
पूर्ण

/*
 * JPEG Codec access
 */

व्योम jpeg_codec_sleep(काष्ठा zoran *zr, पूर्णांक sleep)
अणु
	GPIO(zr, zr->card.gpio[ZR_GPIO_JPEG_SLEEP], !sleep);
	अगर (!sleep) अणु
		pci_dbg(zr->pci_dev, "%s() - wake GPIO=0x%08x\n", __func__, btपढ़ो(ZR36057_GPPGCR1));
		udelay(500);
	पूर्ण अन्यथा अणु
		pci_dbg(zr->pci_dev, "%s() - sleep GPIO=0x%08x\n", __func__, btपढ़ो(ZR36057_GPPGCR1));
		udelay(2);
	पूर्ण
पूर्ण

पूर्णांक jpeg_codec_reset(काष्ठा zoran *zr)
अणु
	/* Take the codec out of sleep */
	jpeg_codec_sleep(zr, 0);

	अगर (zr->card.gpcs[GPCS_JPEG_RESET] != 0xff) अणु
		post_office_ग_लिखो(zr, zr->card.gpcs[GPCS_JPEG_RESET], 0,
				  0);
		udelay(2);
	पूर्ण अन्यथा अणु
		GPIO(zr, zr->card.gpio[ZR_GPIO_JPEG_RESET], 0);
		udelay(2);
		GPIO(zr, zr->card.gpio[ZR_GPIO_JPEG_RESET], 1);
		udelay(2);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *   Set the रेजिस्टरs क्रम the size we have specअगरied. Don't bother
 *   trying to understand this without the ZR36057 manual in front of
 *   you [AC].
 */
अटल व्योम zr36057_adjust_vfe(काष्ठा zoran *zr, क्रमागत zoran_codec_mode mode)
अणु
	u32 reg;

	चयन (mode) अणु
	हाल BUZ_MODE_MOTION_DECOMPRESS:
		btand(~ZR36057_VFESPFR_EXT_FL, ZR36057_VFESPFR);
		reg = btपढ़ो(ZR36057_VFEHCR);
		अगर ((reg & (1 << 10)) && zr->card.type != LML33R10)
			reg += ((1 << 10) | 1);

		btग_लिखो(reg, ZR36057_VFEHCR);
		अवरोध;
	हाल BUZ_MODE_MOTION_COMPRESS:
	हाल BUZ_MODE_IDLE:
	शेष:
		अगर ((zr->norm & V4L2_STD_NTSC) ||
		    (zr->card.type == LML33R10 &&
		     (zr->norm & V4L2_STD_PAL)))
			btand(~ZR36057_VFESPFR_EXT_FL, ZR36057_VFESPFR);
		अन्यथा
			btor(ZR36057_VFESPFR_EXT_FL, ZR36057_VFESPFR);
		reg = btपढ़ो(ZR36057_VFEHCR);
		अगर (!(reg & (1 << 10)) && zr->card.type != LML33R10)
			reg -= ((1 << 10) | 1);

		btग_लिखो(reg, ZR36057_VFEHCR);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * set geometry
 */

अटल व्योम zr36057_set_vfe(काष्ठा zoran *zr, पूर्णांक video_width, पूर्णांक video_height,
			    स्थिर काष्ठा zoran_क्रमmat *क्रमmat)
अणु
	स्थिर काष्ठा tvnorm *tvn;
	अचिन्हित पूर्णांक h_start, h_end, v_start, v_end;
	अचिन्हित पूर्णांक disp_mode;
	अचिन्हित पूर्णांक vid_win_wid, vid_win_ht;
	अचिन्हित पूर्णांक hcrop1, hcrop2, vcrop1, vcrop2;
	अचिन्हित पूर्णांक wa, we, ha, he;
	अचिन्हित पूर्णांक X, Y, hor_dcm, ver_dcm;
	u32 reg;

	tvn = zr->timing;

	wa = tvn->wa;
	ha = tvn->ha;

	pci_info(zr->pci_dev, "set_vfe() - width = %d, height = %d\n", video_width, video_height);

	अगर (video_width < BUZ_MIN_WIDTH ||
	    video_height < BUZ_MIN_HEIGHT ||
	    video_width > wa || video_height > ha) अणु
		pci_err(zr->pci_dev, "set_vfe: w=%d h=%d not valid\n", video_width, video_height);
		वापस;
	पूर्ण

	/**** zr36057 ****/

	/* horizontal */
	vid_win_wid = video_width;
	X = DIV_ROUND_UP(vid_win_wid * 64, tvn->wa);
	we = (vid_win_wid * 64) / X;
	hor_dcm = 64 - X;
	hcrop1 = 2 * ((tvn->wa - we) / 4);
	hcrop2 = tvn->wa - we - hcrop1;
	h_start = tvn->h_start ? tvn->h_start : 1;
	/* (Ronald) Original comment:
	 * "| 1 Doesn't have any effect, tested on both a DC10 and a DC10+"
	 * this is false. It inverses chroma values on the LML33R10 (so Cr
	 * suddenly is shown as Cb and reverse, really cool effect अगर you
	 * want to see blue faces, not useful otherwise). So करोn't use |1.
	 * However, the DC10 has '0' as h_start, but करोes need |1, so we
	 * use a dirty check...
	 */
	h_end = h_start + tvn->wa - 1;
	h_start += hcrop1;
	h_end -= hcrop2;
	reg = ((h_start & ZR36057_VFEHCR_HMASK) << ZR36057_VFEHCR_H_START)
	    | ((h_end & ZR36057_VFEHCR_HMASK) << ZR36057_VFEHCR_H_END);
	अगर (zr->card.vfe_pol.hsync_pol)
		reg |= ZR36057_VFEHCR_HS_POL;
	btग_लिखो(reg, ZR36057_VFEHCR);

	/* Vertical */
	disp_mode = !(video_height > BUZ_MAX_HEIGHT / 2);
	vid_win_ht = disp_mode ? video_height : video_height / 2;
	Y = DIV_ROUND_UP(vid_win_ht * 64 * 2, tvn->ha);
	he = (vid_win_ht * 64) / Y;
	ver_dcm = 64 - Y;
	vcrop1 = (tvn->ha / 2 - he) / 2;
	vcrop2 = tvn->ha / 2 - he - vcrop1;
	v_start = tvn->v_start;
	v_end = v_start + tvn->ha / 2;	// - 1; FIXME SnapShot बार out with -1 in 768*576 on the DC10 - LP
	v_start += vcrop1;
	v_end -= vcrop2;
	reg = ((v_start & ZR36057_VFEVCR_VMASK) << ZR36057_VFEVCR_V_START)
	    | ((v_end & ZR36057_VFEVCR_VMASK) << ZR36057_VFEVCR_V_END);
	अगर (zr->card.vfe_pol.vsync_pol)
		reg |= ZR36057_VFEVCR_VS_POL;
	btग_लिखो(reg, ZR36057_VFEVCR);

	/* scaler and pixel क्रमmat */
	reg = 0;
	reg |= (hor_dcm << ZR36057_VFESPFR_HOR_DCM);
	reg |= (ver_dcm << ZR36057_VFESPFR_VER_DCM);
	reg |= (disp_mode << ZR36057_VFESPFR_DISP_MODE);
	/* RJ: I करोn't know, why the following has to be the opposite
	 * of the corresponding ZR36060 setting, but only this way
	 * we get the correct colors when uncompressing to the screen  */
	//reg |= ZR36057_VFESPFR_VCLK_POL; /**/
	/* RJ: Don't know अगर that is needed क्रम NTSC also */
	अगर (!(zr->norm & V4L2_STD_NTSC))
		reg |= ZR36057_VFESPFR_EXT_FL;	// NEEDED!!!!!!! Wolfgang
	reg |= ZR36057_VFESPFR_TOP_FIELD;
	अगर (hor_dcm >= 48)
		reg |= 3 << ZR36057_VFESPFR_H_FILTER;	/* 5 tap filter */
	अन्यथा अगर (hor_dcm >= 32)
		reg |= 2 << ZR36057_VFESPFR_H_FILTER;	/* 4 tap filter */
	अन्यथा अगर (hor_dcm >= 16)
		reg |= 1 << ZR36057_VFESPFR_H_FILTER;	/* 3 tap filter */

	reg |= क्रमmat->vfespfr;
	btग_लिखो(reg, ZR36057_VFESPFR);

	/* display configuration */
	reg = (16 << ZR36057_VDCR_MIN_PIX)
	    | (vid_win_ht << ZR36057_VDCR_VID_WIN_HT)
	    | (vid_win_wid << ZR36057_VDCR_VID_WIN_WID);
	अगर (pci_pci_problems & PCIPCI_TRITON)
		// || zr->revision < 1) // Revision 1 has also Triton support
		reg &= ~ZR36057_VDCR_TRITON;
	अन्यथा
		reg |= ZR36057_VDCR_TRITON;
	btग_लिखो(reg, ZR36057_VDCR);

	zr36057_adjust_vfe(zr, zr->codec_mode);
पूर्ण

/* Enable/Disable uncompressed memory grabbing of the 36057 */
व्योम zr36057_set_memgrab(काष्ठा zoran *zr, पूर्णांक mode)
अणु
	अगर (mode) अणु
		/* We only check SnapShot and not FrameGrab here.  SnapShot==1
		 * means a capture is alपढ़ोy in progress, but FrameGrab==1
		 * करोesn't necessary mean that.  It's more correct to say a 1
		 * to 0 transition indicates a capture completed.  If a
		 * capture is pending when capturing is tuned off, FrameGrab
		 * will be stuck at 1 until capturing is turned back on.
		 */
		अगर (btपढ़ो(ZR36057_VSSFGR) & ZR36057_VSSFGR_SNAP_SHOT)
			pci_warn(zr->pci_dev, "zr36057_set_memgrab(1) with SnapShot on!?\n");

		/* चयन on VSync पूर्णांकerrupts */
		btग_लिखो(IRQ_MASK, ZR36057_ISR);	// Clear Interrupts
		btor(zr->card.vsync_पूर्णांक, ZR36057_ICR);	// SW

		/* enable SnapShot */
		btor(ZR36057_VSSFGR_SNAP_SHOT, ZR36057_VSSFGR);

		/* Set zr36057 video front end  and enable video */
		zr36057_set_vfe(zr, zr->v4l_settings.width,
				zr->v4l_settings.height,
				zr->v4l_settings.क्रमmat);
	पूर्ण अन्यथा अणु
		/* चयन off VSync पूर्णांकerrupts */
		btand(~zr->card.vsync_पूर्णांक, ZR36057_ICR);	// SW

		/* re-enable grabbing to screen अगर it was running */
		btand(~ZR36057_VDCR_VID_EN, ZR36057_VDCR);
		btand(~ZR36057_VSSFGR_SNAP_SHOT, ZR36057_VSSFGR);
	पूर्ण
पूर्ण

/*****************************************************************************
 *                                                                           *
 *  Set up the Buz-specअगरic MJPEG part                                       *
 *                                                                           *
 *****************************************************************************/

अटल अंतरभूत व्योम set_frame(काष्ठा zoran *zr, पूर्णांक val)
अणु
	GPIO(zr, zr->card.gpio[ZR_GPIO_JPEG_FRAME], val);
पूर्ण

अटल व्योम set_videobus_dir(काष्ठा zoran *zr, पूर्णांक val)
अणु
	चयन (zr->card.type) अणु
	हाल LML33:
	हाल LML33R10:
		अगर (!lml33dpath)
			GPIO(zr, 5, val);
		अन्यथा
			GPIO(zr, 5, 1);
		अवरोध;
	शेष:
		GPIO(zr, zr->card.gpio[ZR_GPIO_VID_सूची],
		     zr->card.gpio_pol[ZR_GPIO_VID_सूची] ? !val : val);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम init_jpeg_queue(काष्ठा zoran *zr)
अणु
	पूर्णांक i;

	/* re-initialize DMA ring stuff */
	zr->jpg_que_head = 0;
	zr->jpg_dma_head = 0;
	zr->jpg_dma_tail = 0;
	zr->jpg_que_tail = 0;
	zr->jpg_seq_num = 0;
	zr->jpeg_error = 0;
	zr->num_errors = 0;
	zr->jpg_err_seq = 0;
	zr->jpg_err_shअगरt = 0;
	zr->jpg_queued_num = 0;
	क्रम (i = 0; i < BUZ_NUM_STAT_COM; i++)
		zr->stat_com[i] = cpu_to_le32(1);	/* mark as unavailable to zr36057 */
पूर्ण

अटल व्योम zr36057_set_jpg(काष्ठा zoran *zr, क्रमागत zoran_codec_mode mode)
अणु
	स्थिर काष्ठा tvnorm *tvn;
	u32 reg;

	tvn = zr->timing;

	/* निश्चित P_Reset, disable code transfer, deनिश्चित Active */
	btग_लिखो(0, ZR36057_JPC);

	/* MJPEG compression mode */
	चयन (mode) अणु
	हाल BUZ_MODE_MOTION_COMPRESS:
	शेष:
		reg = ZR36057_JMC_MJPG_CMP_MODE;
		अवरोध;

	हाल BUZ_MODE_MOTION_DECOMPRESS:
		reg = ZR36057_JMC_MJPG_EXP_MODE;
		reg |= ZR36057_JMC_SYNC_MSTR;
		/* RJ: The following is experimental - improves the output to screen */
		//अगर(zr->jpg_settings.VFIFO_FB) reg |= ZR36057_JMC_VFIFO_FB; // No, it करोesn't. SM
		अवरोध;

	हाल BUZ_MODE_STILL_COMPRESS:
		reg = ZR36057_JMC_JPG_CMP_MODE;
		अवरोध;

	हाल BUZ_MODE_STILL_DECOMPRESS:
		reg = ZR36057_JMC_JPG_EXP_MODE;
		अवरोध;
	पूर्ण
	reg |= ZR36057_JMC_JPG;
	अगर (zr->jpg_settings.field_per_buff == 1)
		reg |= ZR36057_JMC_FLD_PER_BUFF;
	btग_लिखो(reg, ZR36057_JMC);

	/* vertical */
	btor(ZR36057_VFEVCR_VS_POL, ZR36057_VFEVCR);
	reg = (6 << ZR36057_VSP_VSYNC_SIZE) |
	      (tvn->ht << ZR36057_VSP_FRM_TOT);
	btग_लिखो(reg, ZR36057_VSP);
	reg = ((zr->jpg_settings.img_y + tvn->v_start) << ZR36057_FVAP_NAY) |
	      (zr->jpg_settings.img_height << ZR36057_FVAP_PAY);
	btग_लिखो(reg, ZR36057_FVAP);

	/* horizontal */
	अगर (zr->card.vfe_pol.hsync_pol)
		btor(ZR36057_VFEHCR_HS_POL, ZR36057_VFEHCR);
	अन्यथा
		btand(~ZR36057_VFEHCR_HS_POL, ZR36057_VFEHCR);
	reg = ((tvn->h_sync_start) << ZR36057_HSP_HSYNC_START) |
	      (tvn->wt << ZR36057_HSP_LINE_TOT);
	btग_लिखो(reg, ZR36057_HSP);
	reg = ((zr->jpg_settings.img_x +
		tvn->h_start + 4) << ZR36057_FHAP_NAX) |
	      (zr->jpg_settings.img_width << ZR36057_FHAP_PAX);
	btग_लिखो(reg, ZR36057_FHAP);

	/* field process parameters */
	अगर (zr->jpg_settings.odd_even)
		reg = ZR36057_FPP_ODD_EVEN;
	अन्यथा
		reg = 0;

	btग_लिखो(reg, ZR36057_FPP);

	/* Set proper VCLK Polarity, अन्यथा colors will be wrong during playback */
	//btor(ZR36057_VFESPFR_VCLK_POL, ZR36057_VFESPFR);

	/* code base address */
	btग_लिखो(zr->p_sc, ZR36057_JCBA);

	/* FIFO threshold (FIFO is 160. द्विगुन words) */
	/* NOTE: decimal values here */
	चयन (mode) अणु
	हाल BUZ_MODE_STILL_COMPRESS:
	हाल BUZ_MODE_MOTION_COMPRESS:
		अगर (zr->card.type != BUZ)
			reg = 140;
		अन्यथा
			reg = 60;
		अवरोध;

	हाल BUZ_MODE_STILL_DECOMPRESS:
	हाल BUZ_MODE_MOTION_DECOMPRESS:
		reg = 20;
		अवरोध;

	शेष:
		reg = 80;
		अवरोध;
	पूर्ण
	btग_लिखो(reg, ZR36057_JCFT);
	zr36057_adjust_vfe(zr, mode);
पूर्ण

व्योम clear_पूर्णांकerrupt_counters(काष्ठा zoran *zr)
अणु
	zr->पूर्णांकr_counter_GIRQ1 = 0;
	zr->पूर्णांकr_counter_GIRQ0 = 0;
	zr->पूर्णांकr_counter_cod_rep_irq = 0;
	zr->पूर्णांकr_counter_jpeg_rep_irq = 0;
	zr->field_counter = 0;
	zr->irq1_in = 0;
	zr->irq1_out = 0;
	zr->jpeg_in = 0;
	zr->jpeg_out = 0;
	zr->JPEG_0 = 0;
	zr->JPEG_1 = 0;
	zr->end_event_missed = 0;
	zr->jpeg_missed = 0;
	zr->jpeg_max_missed = 0;
	zr->jpeg_min_missed = 0x7fffffff;
पूर्ण

अटल u32 count_reset_पूर्णांकerrupt(काष्ठा zoran *zr)
अणु
	u32 isr;

	isr = btपढ़ो(ZR36057_ISR) & 0x78000000;
	अगर (isr) अणु
		अगर (isr & ZR36057_ISR_GIRQ1) अणु
			btग_लिखो(ZR36057_ISR_GIRQ1, ZR36057_ISR);
			zr->पूर्णांकr_counter_GIRQ1++;
		पूर्ण
		अगर (isr & ZR36057_ISR_GIRQ0) अणु
			btग_लिखो(ZR36057_ISR_GIRQ0, ZR36057_ISR);
			zr->पूर्णांकr_counter_GIRQ0++;
		पूर्ण
		अगर (isr & ZR36057_ISR_COD_REP_IRQ) अणु
			btग_लिखो(ZR36057_ISR_COD_REP_IRQ, ZR36057_ISR);
			zr->पूर्णांकr_counter_cod_rep_irq++;
		पूर्ण
		अगर (isr & ZR36057_ISR_JPEG_REP_IRQ) अणु
			btग_लिखो(ZR36057_ISR_JPEG_REP_IRQ, ZR36057_ISR);
			zr->पूर्णांकr_counter_jpeg_rep_irq++;
		पूर्ण
	पूर्ण
	वापस isr;
पूर्ण

व्योम jpeg_start(काष्ठा zoran *zr)
अणु
	पूर्णांक reg;

	zr->frame_num = 0;

	/* deनिश्चित P_reset, disable code transfer, deनिश्चित Active */
	btग_लिखो(ZR36057_JPC_P_RESET, ZR36057_JPC);
	/* stop flushing the पूर्णांकernal code buffer */
	btand(~ZR36057_MCTCR_C_FLUSH, ZR36057_MCTCR);
	/* enable code transfer */
	btor(ZR36057_JPC_COD_TRNS_EN, ZR36057_JPC);

	/* clear IRQs */
	btग_लिखो(IRQ_MASK, ZR36057_ISR);
	/* enable the JPEG IRQs */
	btग_लिखो(zr->card.jpeg_पूर्णांक | ZR36057_ICR_JPEG_REP_IRQ | ZR36057_ICR_INT_PIN_EN,
		ZR36057_ICR);

	set_frame(zr, 0);	// \FRAME

	/* set the JPEG codec guest ID */
	reg = (zr->card.gpcs[1] << ZR36057_JCGI_JPE_GUEST_ID) |
	       (0 << ZR36057_JCGI_JPE_GUEST_REG);
	btग_लिखो(reg, ZR36057_JCGI);

	अगर (zr->card.video_vfe == CODEC_TYPE_ZR36016 &&
	    zr->card.video_codec == CODEC_TYPE_ZR36050) अणु
		/* Enable processing on the ZR36016 */
		अगर (zr->vfe)
			zr36016_ग_लिखो(zr->vfe, 0, 1);

		/* load the address of the GO रेजिस्टर in the ZR36050 latch */
		post_office_ग_लिखो(zr, 0, 0, 0);
	पूर्ण

	/* निश्चित Active */
	btor(ZR36057_JPC_ACTIVE, ZR36057_JPC);

	/* enable the Go generation */
	btor(ZR36057_JMC_GO_EN, ZR36057_JMC);
	udelay(30);

	set_frame(zr, 1);	// /FRAME

	pci_dbg(zr->pci_dev, "jpeg_start\n");
पूर्ण

व्योम zr36057_enable_jpg(काष्ठा zoran *zr, क्रमागत zoran_codec_mode mode)
अणु
	काष्ठा vfe_settings cap;
	पूर्णांक field_size = zr->buffer_size / zr->jpg_settings.field_per_buff;

	zr->codec_mode = mode;

	cap.x = zr->jpg_settings.img_x;
	cap.y = zr->jpg_settings.img_y;
	cap.width = zr->jpg_settings.img_width;
	cap.height = zr->jpg_settings.img_height;
	cap.decimation =
	    zr->jpg_settings.hor_dcm | (zr->jpg_settings.ver_dcm << 8);
	cap.quality = zr->jpg_settings.jpg_comp.quality;

	चयन (mode) अणु
	हाल BUZ_MODE_MOTION_COMPRESS: अणु
		काष्ठा jpeg_app_marker app;
		काष्ठा jpeg_com_marker com;

		/* In motion compress mode, the decoder output must be enabled, and
		 * the video bus direction set to input.
		 */
		set_videobus_dir(zr, 0);
		decoder_call(zr, video, s_stream, 1);
		encoder_call(zr, video, s_routing, 0, 0, 0);

		/* Take the JPEG codec and the VFE out of sleep */
		jpeg_codec_sleep(zr, 0);

		/* set JPEG app/com marker */
		app.appn = zr->jpg_settings.jpg_comp.APPn;
		app.len = zr->jpg_settings.jpg_comp.APP_len;
		स_नकल(app.data, zr->jpg_settings.jpg_comp.APP_data, 60);
		zr->codec->control(zr->codec, CODEC_S_JPEG_APP_DATA,
				   माप(काष्ठा jpeg_app_marker), &app);

		com.len = zr->jpg_settings.jpg_comp.COM_len;
		स_नकल(com.data, zr->jpg_settings.jpg_comp.COM_data, 60);
		zr->codec->control(zr->codec, CODEC_S_JPEG_COM_DATA,
				   माप(काष्ठा jpeg_com_marker), &com);

		/* Setup the JPEG codec */
		zr->codec->control(zr->codec, CODEC_S_JPEG_TDS_BYTE,
				   माप(पूर्णांक), &field_size);
		zr->codec->set_video(zr->codec, zr->timing, &cap,
				     &zr->card.vfe_pol);
		zr->codec->set_mode(zr->codec, CODEC_DO_COMPRESSION);

		/* Setup the VFE */
		अगर (zr->vfe) अणु
			zr->vfe->control(zr->vfe, CODEC_S_JPEG_TDS_BYTE,
					 माप(पूर्णांक), &field_size);
			zr->vfe->set_video(zr->vfe, zr->timing, &cap,
					   &zr->card.vfe_pol);
			zr->vfe->set_mode(zr->vfe, CODEC_DO_COMPRESSION);
		पूर्ण

		init_jpeg_queue(zr);
		zr36057_set_jpg(zr, mode);	// \P_Reset, ... Video param, FIFO

		clear_पूर्णांकerrupt_counters(zr);
		pci_info(zr->pci_dev, "enable_jpg(MOTION_COMPRESS)\n");
		अवरोध;
	पूर्ण

	हाल BUZ_MODE_MOTION_DECOMPRESS:
		/* In motion decompression mode, the decoder output must be disabled, and
		 * the video bus direction set to output.
		 */
		decoder_call(zr, video, s_stream, 0);
		set_videobus_dir(zr, 1);
		encoder_call(zr, video, s_routing, 1, 0, 0);

		/* Take the JPEG codec and the VFE out of sleep */
		jpeg_codec_sleep(zr, 0);
		/* Setup the VFE */
		अगर (zr->vfe) अणु
			zr->vfe->set_video(zr->vfe, zr->timing, &cap,
					   &zr->card.vfe_pol);
			zr->vfe->set_mode(zr->vfe, CODEC_DO_EXPANSION);
		पूर्ण
		/* Setup the JPEG codec */
		zr->codec->set_video(zr->codec, zr->timing, &cap,
				     &zr->card.vfe_pol);
		zr->codec->set_mode(zr->codec, CODEC_DO_EXPANSION);

		init_jpeg_queue(zr);
		zr36057_set_jpg(zr, mode);	// \P_Reset, ... Video param, FIFO

		clear_पूर्णांकerrupt_counters(zr);
		pci_info(zr->pci_dev, "enable_jpg(MOTION_DECOMPRESS)\n");
		अवरोध;

	हाल BUZ_MODE_IDLE:
	शेष:
		/* shut करोwn processing */
		btand(~(zr->card.jpeg_पूर्णांक | ZR36057_ICR_JPEG_REP_IRQ),
		      ZR36057_ICR);
		btग_लिखो(zr->card.jpeg_पूर्णांक | ZR36057_ICR_JPEG_REP_IRQ,
			ZR36057_ISR);
		btand(~ZR36057_JMC_GO_EN, ZR36057_JMC);	// \Go_en

		msleep(50);

		set_videobus_dir(zr, 0);
		set_frame(zr, 1);	// /FRAME
		btor(ZR36057_MCTCR_C_FLUSH, ZR36057_MCTCR);	// /CFlush
		btग_लिखो(0, ZR36057_JPC);	// \P_Reset,\CodTrnsEn,\Active
		btand(~ZR36057_JMC_VFIFO_FB, ZR36057_JMC);
		btand(~ZR36057_JMC_SYNC_MSTR, ZR36057_JMC);
		jpeg_codec_reset(zr);
		jpeg_codec_sleep(zr, 1);
		zr36057_adjust_vfe(zr, mode);

		decoder_call(zr, video, s_stream, 1);
		encoder_call(zr, video, s_routing, 0, 0, 0);

		pci_info(zr->pci_dev, "enable_jpg(IDLE)\n");
		अवरोध;
	पूर्ण
पूर्ण

/* when this is called the spinlock must be held */
व्योम zoran_feed_stat_com(काष्ठा zoran *zr)
अणु
	/* move frames from pending queue to DMA */

	पूर्णांक i, max_stat_com;
	काष्ठा zr_buffer *buf;
	काष्ठा vb2_v4l2_buffer *vbuf;
	dma_addr_t phys_addr = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ payload;

	max_stat_com =
	    (zr->jpg_settings.पंचांगp_dcm ==
	     1) ? BUZ_NUM_STAT_COM : (BUZ_NUM_STAT_COM >> 1);

	spin_lock_irqsave(&zr->queued_bufs_lock, flags);
	जबतक ((zr->jpg_dma_head - zr->jpg_dma_tail) < max_stat_com) अणु
		buf = list_first_entry_or_null(&zr->queued_bufs, काष्ठा zr_buffer, queue);
		अगर (!buf) अणु
			pci_err(zr->pci_dev, "No buffer available to queue\n");
			spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
			वापस;
		पूर्ण
		list_del(&buf->queue);
		zr->buf_in_reserve--;
		vbuf = &buf->vbuf;
		vbuf->vb2_buf.state = VB2_BUF_STATE_ACTIVE;
		phys_addr = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, 0);
		payload = vb2_get_plane_payload(&vbuf->vb2_buf, 0);
		अगर (payload == 0)
			payload = zr->buffer_size;
		अगर (zr->jpg_settings.पंचांगp_dcm == 1) अणु
			/* fill 1 stat_com entry */
			i = (zr->jpg_dma_head -
			     zr->jpg_err_shअगरt) & BUZ_MASK_STAT_COM;
			अगर (!(zr->stat_com[i] & cpu_to_le32(1)))
				अवरोध;
			zr->stat_comb[i * 2] = cpu_to_le32(phys_addr);
			zr->stat_comb[i * 2 + 1] = cpu_to_le32((payload >> 1) | 1);
			zr->inuse[i] = buf;
			zr->stat_com[i] = cpu_to_le32(zr->p_scb + i * 2 * 4);
		पूर्ण अन्यथा अणु
			/* fill 2 stat_com entries */
			i = ((zr->jpg_dma_head -
			      zr->jpg_err_shअगरt) & 1) * 2;
			अगर (!(zr->stat_com[i] & cpu_to_le32(1)))
				अवरोध;
			zr->stat_com[i] = cpu_to_le32(zr->p_scb + i * 2 * 4);
			zr->stat_com[i + 1] = cpu_to_le32(zr->p_scb + i * 2 * 4);

			zr->stat_comb[i * 2] = cpu_to_le32(phys_addr);
			zr->stat_comb[i * 2 + 1] = cpu_to_le32((payload >> 1) | 1);

			zr->inuse[i] = buf;
			zr->inuse[i + 1] = शून्य;
		पूर्ण
		zr->jpg_dma_head++;
	पूर्ण
	spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
	अगर (zr->codec_mode == BUZ_MODE_MOTION_DECOMPRESS)
		zr->jpg_queued_num++;
पूर्ण

/* when this is called the spinlock must be held */
अटल व्योम zoran_reap_stat_com(काष्ठा zoran *zr)
अणु
	/* move frames from DMA queue to करोne queue */

	पूर्णांक i;
	u32 stat_com;
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक dअगर;
	अचिन्हित दीर्घ flags;
	काष्ठा zr_buffer *buf;
	अचिन्हित पूर्णांक size = 0;
	u32 fcnt;

	/* In motion decompress we करोn't have a hardware frame counter,
	 * we just count the पूर्णांकerrupts here */

	अगर (zr->codec_mode == BUZ_MODE_MOTION_DECOMPRESS)
		zr->jpg_seq_num++;

	spin_lock_irqsave(&zr->queued_bufs_lock, flags);
	जबतक (zr->jpg_dma_tail < zr->jpg_dma_head) अणु
		अगर (zr->jpg_settings.पंचांगp_dcm == 1)
			i = (zr->jpg_dma_tail - zr->jpg_err_shअगरt) & BUZ_MASK_STAT_COM;
		अन्यथा
			i = ((zr->jpg_dma_tail - zr->jpg_err_shअगरt) & 1) * 2 + 1;

		stat_com = le32_to_cpu(zr->stat_com[i]);
		अगर ((stat_com & 1) == 0) अणु
			spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
			वापस;
		पूर्ण

		fcnt = (stat_com & GENMASK(31, 24)) >> 24;
		size = (stat_com & GENMASK(22, 1)) >> 1;

		buf = zr->inuse[i];
		buf->vbuf.vb2_buf.बारtamp = kसमय_get_ns();

		अगर (zr->codec_mode == BUZ_MODE_MOTION_COMPRESS) अणु
			vb2_set_plane_payload(&buf->vbuf.vb2_buf, 0, size);

			/* update sequence number with the help of the counter in stat_com */
			seq = (fcnt + zr->jpg_err_seq) & 0xff;
			dअगर = (seq - zr->jpg_seq_num) & 0xff;
			zr->jpg_seq_num += dअगर;
		पूर्ण
		buf->vbuf.sequence = zr->jpg_settings.पंचांगp_dcm ==
		    2 ? (zr->jpg_seq_num >> 1) : zr->jpg_seq_num;
		zr->inuse[i] = शून्य;
		अगर (zr->jpg_settings.पंचांगp_dcm != 1)
			buf->vbuf.field = zr->jpg_settings.odd_even ?
				V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM;
		अन्यथा
			buf->vbuf.field = zr->jpg_settings.odd_even ?
				V4L2_FIELD_SEQ_TB : V4L2_FIELD_SEQ_BT;
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_DONE);

		zr->jpg_dma_tail++;
	पूर्ण
	spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
पूर्ण

irqवापस_t zoran_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zoran *zr = dev_id;
	u32 stat, astat;

	stat = count_reset_पूर्णांकerrupt(zr);
	astat = stat & IRQ_MASK;
	अगर (astat & zr->card.vsync_पूर्णांक) अणु
		अगर (zr->running == ZORAN_MAP_MODE_RAW) अणु
			अगर ((btपढ़ो(ZR36057_VSSFGR) & ZR36057_VSSFGR_SNAP_SHOT) == 0)
				pci_warn(zr->pci_dev, "BuzIRQ with SnapShot off ???\n");
			अगर ((btपढ़ो(ZR36057_VSSFGR) & ZR36057_VSSFGR_FRAME_GRAB) == 0)
				zr_set_buf(zr);
			वापस IRQ_HANDLED;
		पूर्ण
		अगर (astat & ZR36057_ISR_JPEG_REP_IRQ) अणु
			अगर (zr->codec_mode != BUZ_MODE_MOTION_DECOMPRESS &&
			    zr->codec_mode != BUZ_MODE_MOTION_COMPRESS) अणु
				pci_err(zr->pci_dev, "JPG IRQ when not in good mode\n");
				वापस IRQ_HANDLED;
			पूर्ण
			zr->frame_num++;
			zoran_reap_stat_com(zr);
			zoran_feed_stat_com(zr);
			वापस IRQ_HANDLED;
		पूर्ण
		/* unused पूर्णांकerrupts */
	पूर्ण
	zr->ghost_पूर्णांक++;
	वापस IRQ_HANDLED;
पूर्ण

व्योम zoran_set_pci_master(काष्ठा zoran *zr, पूर्णांक set_master)
अणु
	अगर (set_master) अणु
		pci_set_master(zr->pci_dev);
	पूर्ण अन्यथा अणु
		u16 command;

		pci_पढ़ो_config_word(zr->pci_dev, PCI_COMMAND, &command);
		command &= ~PCI_COMMAND_MASTER;
		pci_ग_लिखो_config_word(zr->pci_dev, PCI_COMMAND, command);
	पूर्ण
पूर्ण

व्योम zoran_init_hardware(काष्ठा zoran *zr)
अणु
	/* Enable bus-mastering */
	zoran_set_pci_master(zr, 1);

	/* Initialize the board */
	अगर (zr->card.init)
		zr->card.init(zr);

	decoder_call(zr, core, init, 0);
	decoder_call(zr, video, s_std, zr->norm);
	decoder_call(zr, video, s_routing,
		     zr->card.input[zr->input].muxsel, 0, 0);

	encoder_call(zr, core, init, 0);
	encoder_call(zr, video, s_std_output, zr->norm);
	encoder_call(zr, video, s_routing, 0, 0, 0);

	/* toggle JPEG codec sleep to sync PLL */
	jpeg_codec_sleep(zr, 1);
	jpeg_codec_sleep(zr, 0);

	/*
	 * set inभागidual पूर्णांकerrupt enables (without GIRQ1)
	 * but करोn't global enable until zoran_खोलो()
	 */
	zr36057_init_vfe(zr);

	zr36057_enable_jpg(zr, BUZ_MODE_IDLE);

	btग_लिखो(IRQ_MASK, ZR36057_ISR);	// Clears पूर्णांकerrupts
पूर्ण

व्योम zr36057_restart(काष्ठा zoran *zr)
अणु
	btग_लिखो(0, ZR36057_SPGPPCR);
	udelay(1000);
	btor(ZR36057_SPGPPCR_SOFT_RESET, ZR36057_SPGPPCR);
	udelay(1000);

	/* निश्चित P_Reset */
	btग_लिखो(0, ZR36057_JPC);
	/* set up GPIO direction - all output */
	btग_लिखो(ZR36057_SPGPPCR_SOFT_RESET | 0, ZR36057_SPGPPCR);

	/* set up GPIO pins and guest bus timing */
	btग_लिखो((0x81 << 24) | 0x8888, ZR36057_GPPGCR1);
पूर्ण

