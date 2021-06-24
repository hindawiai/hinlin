<शैली गुरु>
/*
 * SuperH Mobile LCDC Framebuffer
 *
 * Copyright (c) 2008 Magnus Damm
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/backlight.h>
#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/fbcon.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <video/sh_mobile_lcdc.h>

#समावेश "sh_mobile_lcdcfb.h"

/* ----------------------------------------------------------------------------
 * Overlay रेजिस्टर definitions
 */

#घोषणा LDBCR			0xb00
#घोषणा LDBCR_UPC(n)		(1 << ((n) + 16))
#घोषणा LDBCR_UPF(n)		(1 << ((n) + 8))
#घोषणा LDBCR_UPD(n)		(1 << ((n) + 0))
#घोषणा LDBnBSIFR(n)		(0xb20 + (n) * 0x20 + 0x00)
#घोषणा LDBBSIFR_EN		(1 << 31)
#घोषणा LDBBSIFR_VS		(1 << 29)
#घोषणा LDBBSIFR_BRSEL		(1 << 28)
#घोषणा LDBBSIFR_MX		(1 << 27)
#घोषणा LDBBSIFR_MY		(1 << 26)
#घोषणा LDBBSIFR_CV3		(3 << 24)
#घोषणा LDBBSIFR_CV2		(2 << 24)
#घोषणा LDBBSIFR_CV1		(1 << 24)
#घोषणा LDBBSIFR_CV0		(0 << 24)
#घोषणा LDBBSIFR_CV_MASK	(3 << 24)
#घोषणा LDBBSIFR_LAY_MASK	(0xff << 16)
#घोषणा LDBBSIFR_LAY_SHIFT	16
#घोषणा LDBBSIFR_ROP3_MASK	(0xff << 16)
#घोषणा LDBBSIFR_ROP3_SHIFT	16
#घोषणा LDBBSIFR_AL_PL8		(3 << 14)
#घोषणा LDBBSIFR_AL_PL1		(2 << 14)
#घोषणा LDBBSIFR_AL_PK		(1 << 14)
#घोषणा LDBBSIFR_AL_1		(0 << 14)
#घोषणा LDBBSIFR_AL_MASK	(3 << 14)
#घोषणा LDBBSIFR_SWPL		(1 << 10)
#घोषणा LDBBSIFR_SWPW		(1 << 9)
#घोषणा LDBBSIFR_SWPB		(1 << 8)
#घोषणा LDBBSIFR_RY		(1 << 7)
#घोषणा LDBBSIFR_CHRR_420	(2 << 0)
#घोषणा LDBBSIFR_CHRR_422	(1 << 0)
#घोषणा LDBBSIFR_CHRR_444	(0 << 0)
#घोषणा LDBBSIFR_RPKF_ARGB32	(0x00 << 0)
#घोषणा LDBBSIFR_RPKF_RGB16	(0x03 << 0)
#घोषणा LDBBSIFR_RPKF_RGB24	(0x0b << 0)
#घोषणा LDBBSIFR_RPKF_MASK	(0x1f << 0)
#घोषणा LDBnBSSZR(n)		(0xb20 + (n) * 0x20 + 0x04)
#घोषणा LDBBSSZR_BVSS_MASK	(0xfff << 16)
#घोषणा LDBBSSZR_BVSS_SHIFT	16
#घोषणा LDBBSSZR_BHSS_MASK	(0xfff << 0)
#घोषणा LDBBSSZR_BHSS_SHIFT	0
#घोषणा LDBnBLOCR(n)		(0xb20 + (n) * 0x20 + 0x08)
#घोषणा LDBBLOCR_CVLC_MASK	(0xfff << 16)
#घोषणा LDBBLOCR_CVLC_SHIFT	16
#घोषणा LDBBLOCR_CHLC_MASK	(0xfff << 0)
#घोषणा LDBBLOCR_CHLC_SHIFT	0
#घोषणा LDBnBSMWR(n)		(0xb20 + (n) * 0x20 + 0x0c)
#घोषणा LDBBSMWR_BSMWA_MASK	(0xffff << 16)
#घोषणा LDBBSMWR_BSMWA_SHIFT	16
#घोषणा LDBBSMWR_BSMW_MASK	(0xffff << 0)
#घोषणा LDBBSMWR_BSMW_SHIFT	0
#घोषणा LDBnBSAYR(n)		(0xb20 + (n) * 0x20 + 0x10)
#घोषणा LDBBSAYR_FG1A_MASK	(0xff << 24)
#घोषणा LDBBSAYR_FG1A_SHIFT	24
#घोषणा LDBBSAYR_FG1R_MASK	(0xff << 16)
#घोषणा LDBBSAYR_FG1R_SHIFT	16
#घोषणा LDBBSAYR_FG1G_MASK	(0xff << 8)
#घोषणा LDBBSAYR_FG1G_SHIFT	8
#घोषणा LDBBSAYR_FG1B_MASK	(0xff << 0)
#घोषणा LDBBSAYR_FG1B_SHIFT	0
#घोषणा LDBnBSACR(n)		(0xb20 + (n) * 0x20 + 0x14)
#घोषणा LDBBSACR_FG2A_MASK	(0xff << 24)
#घोषणा LDBBSACR_FG2A_SHIFT	24
#घोषणा LDBBSACR_FG2R_MASK	(0xff << 16)
#घोषणा LDBBSACR_FG2R_SHIFT	16
#घोषणा LDBBSACR_FG2G_MASK	(0xff << 8)
#घोषणा LDBBSACR_FG2G_SHIFT	8
#घोषणा LDBBSACR_FG2B_MASK	(0xff << 0)
#घोषणा LDBBSACR_FG2B_SHIFT	0
#घोषणा LDBnBSAAR(n)		(0xb20 + (n) * 0x20 + 0x18)
#घोषणा LDBBSAAR_AP_MASK	(0xff << 24)
#घोषणा LDBBSAAR_AP_SHIFT	24
#घोषणा LDBBSAAR_R_MASK		(0xff << 16)
#घोषणा LDBBSAAR_R_SHIFT	16
#घोषणा LDBBSAAR_GY_MASK	(0xff << 8)
#घोषणा LDBBSAAR_GY_SHIFT	8
#घोषणा LDBBSAAR_B_MASK		(0xff << 0)
#घोषणा LDBBSAAR_B_SHIFT	0
#घोषणा LDBnBPPCR(n)		(0xb20 + (n) * 0x20 + 0x1c)
#घोषणा LDBBPPCR_AP_MASK	(0xff << 24)
#घोषणा LDBBPPCR_AP_SHIFT	24
#घोषणा LDBBPPCR_R_MASK		(0xff << 16)
#घोषणा LDBBPPCR_R_SHIFT	16
#घोषणा LDBBPPCR_GY_MASK	(0xff << 8)
#घोषणा LDBBPPCR_GY_SHIFT	8
#घोषणा LDBBPPCR_B_MASK		(0xff << 0)
#घोषणा LDBBPPCR_B_SHIFT	0
#घोषणा LDBnBBGCL(n)		(0xb10 + (n) * 0x04)
#घोषणा LDBBBGCL_BGA_MASK	(0xff << 24)
#घोषणा LDBBBGCL_BGA_SHIFT	24
#घोषणा LDBBBGCL_BGR_MASK	(0xff << 16)
#घोषणा LDBBBGCL_BGR_SHIFT	16
#घोषणा LDBBBGCL_BGG_MASK	(0xff << 8)
#घोषणा LDBBBGCL_BGG_SHIFT	8
#घोषणा LDBBBGCL_BGB_MASK	(0xff << 0)
#घोषणा LDBBBGCL_BGB_SHIFT	0

#घोषणा SIDE_B_OFFSET 0x1000
#घोषणा MIRROR_OFFSET 0x2000

#घोषणा MAX_XRES 1920
#घोषणा MAX_YRES 1080

क्रमागत sh_mobile_lcdc_overlay_mode अणु
	LCDC_OVERLAY_BLEND,
	LCDC_OVERLAY_ROP3,
पूर्ण;

/*
 * काष्ठा sh_mobile_lcdc_overlay - LCDC display overlay
 *
 * @channel: LCDC channel this overlay beदीर्घs to
 * @cfg: Overlay configuration
 * @info: Frame buffer device
 * @index: Overlay index (0-3)
 * @base: Overlay रेजिस्टरs base address
 * @enabled: True अगर the overlay is enabled
 * @mode: Overlay blending mode (alpha blend or ROP3)
 * @alpha: Global alpha blending value (0-255, क्रम alpha blending mode)
 * @rop3: Raster operation (क्रम ROP3 mode)
 * @fb_mem: Frame buffer भव memory address
 * @fb_size: Frame buffer size in bytes
 * @dma_handle: Frame buffer DMA address
 * @base_addr_y: Overlay base address (RGB or luma component)
 * @base_addr_c: Overlay base address (chroma component)
 * @pan_y_offset: Panning linear offset in bytes (luma component)
 * @क्रमmat: Current pixelf क्रमmat
 * @xres: Horizontal visible resolution
 * @xres_भव: Horizontal total resolution
 * @yres: Vertical visible resolution
 * @yres_भव: Vertical total resolution
 * @pitch: Overlay line pitch
 * @pos_x: Horizontal overlay position
 * @pos_y: Vertical overlay position
 */
काष्ठा sh_mobile_lcdc_overlay अणु
	काष्ठा sh_mobile_lcdc_chan *channel;

	स्थिर काष्ठा sh_mobile_lcdc_overlay_cfg *cfg;
	काष्ठा fb_info *info;

	अचिन्हित पूर्णांक index;
	अचिन्हित दीर्घ base;

	bool enabled;
	क्रमागत sh_mobile_lcdc_overlay_mode mode;
	अचिन्हित पूर्णांक alpha;
	अचिन्हित पूर्णांक rop3;

	व्योम *fb_mem;
	अचिन्हित दीर्घ fb_size;

	dma_addr_t dma_handle;
	अचिन्हित दीर्घ base_addr_y;
	अचिन्हित दीर्घ base_addr_c;
	अचिन्हित दीर्घ pan_y_offset;

	स्थिर काष्ठा sh_mobile_lcdc_क्रमmat_info *क्रमmat;
	अचिन्हित पूर्णांक xres;
	अचिन्हित पूर्णांक xres_भव;
	अचिन्हित पूर्णांक yres;
	अचिन्हित पूर्णांक yres_भव;
	अचिन्हित पूर्णांक pitch;
	पूर्णांक pos_x;
	पूर्णांक pos_y;
पूर्ण;

काष्ठा sh_mobile_lcdc_priv अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	atomic_t hw_usecnt;
	काष्ठा device *dev;
	काष्ठा clk *करोt_clk;
	अचिन्हित दीर्घ lddckr;

	काष्ठा sh_mobile_lcdc_chan ch[2];
	काष्ठा sh_mobile_lcdc_overlay overlays[4];

	पूर्णांक started;
	पूर्णांक क्रमced_fourcc; /* 2 channel LCDC must share fourcc setting */
पूर्ण;

/* -----------------------------------------------------------------------------
 * Registers access
 */

अटल अचिन्हित दीर्घ lcdc_offs_मुख्यlcd[NR_CH_REGS] = अणु
	[LDDCKPAT1R] = 0x400,
	[LDDCKPAT2R] = 0x404,
	[LDMT1R] = 0x418,
	[LDMT2R] = 0x41c,
	[LDMT3R] = 0x420,
	[LDDFR] = 0x424,
	[LDSM1R] = 0x428,
	[LDSM2R] = 0x42c,
	[LDSA1R] = 0x430,
	[LDSA2R] = 0x434,
	[LDMLSR] = 0x438,
	[LDHCNR] = 0x448,
	[LDHSYNR] = 0x44c,
	[LDVLNR] = 0x450,
	[LDVSYNR] = 0x454,
	[LDPMR] = 0x460,
	[LDHAJR] = 0x4a0,
पूर्ण;

अटल अचिन्हित दीर्घ lcdc_offs_sublcd[NR_CH_REGS] = अणु
	[LDDCKPAT1R] = 0x408,
	[LDDCKPAT2R] = 0x40c,
	[LDMT1R] = 0x600,
	[LDMT2R] = 0x604,
	[LDMT3R] = 0x608,
	[LDDFR] = 0x60c,
	[LDSM1R] = 0x610,
	[LDSM2R] = 0x614,
	[LDSA1R] = 0x618,
	[LDMLSR] = 0x620,
	[LDHCNR] = 0x624,
	[LDHSYNR] = 0x628,
	[LDVLNR] = 0x62c,
	[LDVSYNR] = 0x630,
	[LDPMR] = 0x63c,
पूर्ण;

अटल bool banked(पूर्णांक reg_nr)
अणु
	चयन (reg_nr) अणु
	हाल LDMT1R:
	हाल LDMT2R:
	हाल LDMT3R:
	हाल LDDFR:
	हाल LDSM1R:
	हाल LDSA1R:
	हाल LDSA2R:
	हाल LDMLSR:
	हाल LDHCNR:
	हाल LDHSYNR:
	हाल LDVLNR:
	हाल LDVSYNR:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक lcdc_chan_is_sublcd(काष्ठा sh_mobile_lcdc_chan *chan)
अणु
	वापस chan->cfg->chan == LCDC_CHAN_SUBLCD;
पूर्ण

अटल व्योम lcdc_ग_लिखो_chan(काष्ठा sh_mobile_lcdc_chan *chan,
			    पूर्णांक reg_nr, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो32(data, chan->lcdc->base + chan->reg_offs[reg_nr]);
	अगर (banked(reg_nr))
		ioग_लिखो32(data, chan->lcdc->base + chan->reg_offs[reg_nr] +
			  SIDE_B_OFFSET);
पूर्ण

अटल व्योम lcdc_ग_लिखो_chan_mirror(काष्ठा sh_mobile_lcdc_chan *chan,
			    पूर्णांक reg_nr, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो32(data, chan->lcdc->base + chan->reg_offs[reg_nr] +
		  MIRROR_OFFSET);
पूर्ण

अटल अचिन्हित दीर्घ lcdc_पढ़ो_chan(काष्ठा sh_mobile_lcdc_chan *chan,
				    पूर्णांक reg_nr)
अणु
	वापस ioपढ़ो32(chan->lcdc->base + chan->reg_offs[reg_nr]);
पूर्ण

अटल व्योम lcdc_ग_लिखो_overlay(काष्ठा sh_mobile_lcdc_overlay *ovl,
			       पूर्णांक reg, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो32(data, ovl->channel->lcdc->base + reg);
	ioग_लिखो32(data, ovl->channel->lcdc->base + reg + SIDE_B_OFFSET);
पूर्ण

अटल व्योम lcdc_ग_लिखो(काष्ठा sh_mobile_lcdc_priv *priv,
		       अचिन्हित दीर्घ reg_offs, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो32(data, priv->base + reg_offs);
पूर्ण

अटल अचिन्हित दीर्घ lcdc_पढ़ो(काष्ठा sh_mobile_lcdc_priv *priv,
			       अचिन्हित दीर्घ reg_offs)
अणु
	वापस ioपढ़ो32(priv->base + reg_offs);
पूर्ण

अटल व्योम lcdc_रुको_bit(काष्ठा sh_mobile_lcdc_priv *priv,
			  अचिन्हित दीर्घ reg_offs,
			  अचिन्हित दीर्घ mask, अचिन्हित दीर्घ until)
अणु
	जबतक ((lcdc_पढ़ो(priv, reg_offs) & mask) != until)
		cpu_relax();
पूर्ण

/* -----------------------------------------------------------------------------
 * Clock management
 */

अटल व्योम sh_mobile_lcdc_clk_on(काष्ठा sh_mobile_lcdc_priv *priv)
अणु
	अगर (atomic_inc_and_test(&priv->hw_usecnt)) अणु
		clk_prepare_enable(priv->करोt_clk);
		pm_runसमय_get_sync(priv->dev);
	पूर्ण
पूर्ण

अटल व्योम sh_mobile_lcdc_clk_off(काष्ठा sh_mobile_lcdc_priv *priv)
अणु
	अगर (atomic_sub_वापस(1, &priv->hw_usecnt) == -1) अणु
		pm_runसमय_put(priv->dev);
		clk_disable_unprepare(priv->करोt_clk);
	पूर्ण
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_setup_घड़ीs(काष्ठा sh_mobile_lcdc_priv *priv,
				       पूर्णांक घड़ी_source)
अणु
	काष्ठा clk *clk;
	अक्षर *str;

	चयन (घड़ी_source) अणु
	हाल LCDC_CLK_BUS:
		str = "bus_clk";
		priv->lddckr = LDDCKR_ICKSEL_BUS;
		अवरोध;
	हाल LCDC_CLK_PERIPHERAL:
		str = "peripheral_clk";
		priv->lddckr = LDDCKR_ICKSEL_MIPI;
		अवरोध;
	हाल LCDC_CLK_EXTERNAL:
		str = शून्य;
		priv->lddckr = LDDCKR_ICKSEL_HDMI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (str == शून्य)
		वापस 0;

	clk = clk_get(priv->dev, str);
	अगर (IS_ERR(clk)) अणु
		dev_err(priv->dev, "cannot get dot clock %s\n", str);
		वापस PTR_ERR(clk);
	पूर्ण

	priv->करोt_clk = clk;
	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Display, panel and deferred I/O
 */

अटल व्योम lcdc_sys_ग_लिखो_index(व्योम *handle, अचिन्हित दीर्घ data)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = handle;

	lcdc_ग_लिखो(ch->lcdc, _LDDWD0R, data | LDDWDxR_WDACT);
	lcdc_रुको_bit(ch->lcdc, _LDSR, LDSR_AS, 0);
	lcdc_ग_लिखो(ch->lcdc, _LDDWAR, LDDWAR_WA |
		   (lcdc_chan_is_sublcd(ch) ? 2 : 0));
	lcdc_रुको_bit(ch->lcdc, _LDSR, LDSR_AS, 0);
पूर्ण

अटल व्योम lcdc_sys_ग_लिखो_data(व्योम *handle, अचिन्हित दीर्घ data)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = handle;

	lcdc_ग_लिखो(ch->lcdc, _LDDWD0R, data | LDDWDxR_WDACT | LDDWDxR_RSW);
	lcdc_रुको_bit(ch->lcdc, _LDSR, LDSR_AS, 0);
	lcdc_ग_लिखो(ch->lcdc, _LDDWAR, LDDWAR_WA |
		   (lcdc_chan_is_sublcd(ch) ? 2 : 0));
	lcdc_रुको_bit(ch->lcdc, _LDSR, LDSR_AS, 0);
पूर्ण

अटल अचिन्हित दीर्घ lcdc_sys_पढ़ो_data(व्योम *handle)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = handle;

	lcdc_ग_लिखो(ch->lcdc, _LDDRDR, LDDRDR_RSR);
	lcdc_रुको_bit(ch->lcdc, _LDSR, LDSR_AS, 0);
	lcdc_ग_लिखो(ch->lcdc, _LDDRAR, LDDRAR_RA |
		   (lcdc_chan_is_sublcd(ch) ? 2 : 0));
	udelay(1);
	lcdc_रुको_bit(ch->lcdc, _LDSR, LDSR_AS, 0);

	वापस lcdc_पढ़ो(ch->lcdc, _LDDRDR) & LDDRDR_DRD_MASK;
पूर्ण

अटल काष्ठा sh_mobile_lcdc_sys_bus_ops sh_mobile_lcdc_sys_bus_ops = अणु
	.ग_लिखो_index	= lcdc_sys_ग_लिखो_index,
	.ग_लिखो_data	= lcdc_sys_ग_लिखो_data,
	.पढ़ो_data	= lcdc_sys_पढ़ो_data,
पूर्ण;

अटल पूर्णांक sh_mobile_lcdc_sginit(काष्ठा fb_info *info,
				  काष्ठा list_head *pagelist)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	अचिन्हित पूर्णांक nr_pages_max = ch->fb_size >> PAGE_SHIFT;
	काष्ठा page *page;
	पूर्णांक nr_pages = 0;

	sg_init_table(ch->sglist, nr_pages_max);

	list_क्रम_each_entry(page, pagelist, lru)
		sg_set_page(&ch->sglist[nr_pages++], page, PAGE_SIZE, 0);

	वापस nr_pages;
पूर्ण

अटल व्योम sh_mobile_lcdc_deferred_io(काष्ठा fb_info *info,
				       काष्ठा list_head *pagelist)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	स्थिर काष्ठा sh_mobile_lcdc_panel_cfg *panel = &ch->cfg->panel_cfg;

	/* enable घड़ीs beक्रमe accessing hardware */
	sh_mobile_lcdc_clk_on(ch->lcdc);

	/*
	 * It's possible to get here without anything on the pagelist via
	 * sh_mobile_lcdc_deferred_io_touch() or via a userspace fsync()
	 * invocation. In the क्रमmer हाल, the acceleration routines are
	 * stepped in to when using the framebuffer console causing the
	 * workqueue to be scheduled without any dirty pages on the list.
	 *
	 * Despite this, a panel update is still needed given that the
	 * acceleration routines have their own methods क्रम writing in
	 * that still need to be updated.
	 *
	 * The fsync() and empty pagelist हाल could be optimized क्रम,
	 * but we करोn't bother, as any application exhibiting such
	 * behaviour is fundamentally broken anyways.
	 */
	अगर (!list_empty(pagelist)) अणु
		अचिन्हित पूर्णांक nr_pages = sh_mobile_lcdc_sginit(info, pagelist);

		/* trigger panel update */
		dma_map_sg(ch->lcdc->dev, ch->sglist, nr_pages, DMA_TO_DEVICE);
		अगर (panel->start_transfer)
			panel->start_transfer(ch, &sh_mobile_lcdc_sys_bus_ops);
		lcdc_ग_लिखो_chan(ch, LDSM2R, LDSM2R_OSTRG);
		dma_unmap_sg(ch->lcdc->dev, ch->sglist, nr_pages,
			     DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		अगर (panel->start_transfer)
			panel->start_transfer(ch, &sh_mobile_lcdc_sys_bus_ops);
		lcdc_ग_लिखो_chan(ch, LDSM2R, LDSM2R_OSTRG);
	पूर्ण
पूर्ण

अटल व्योम sh_mobile_lcdc_deferred_io_touch(काष्ठा fb_info *info)
अणु
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;

	अगर (fbdefio)
		schedule_delayed_work(&info->deferred_work, fbdefio->delay);
पूर्ण

अटल व्योम sh_mobile_lcdc_display_on(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	स्थिर काष्ठा sh_mobile_lcdc_panel_cfg *panel = &ch->cfg->panel_cfg;

	अगर (ch->tx_dev) अणु
		पूर्णांक ret;

		ret = ch->tx_dev->ops->display_on(ch->tx_dev);
		अगर (ret < 0)
			वापस;

		अगर (ret == SH_MOBILE_LCDC_DISPLAY_DISCONNECTED)
			ch->info->state = FBINFO_STATE_SUSPENDED;
	पूर्ण

	/* HDMI must be enabled beक्रमe LCDC configuration */
	अगर (panel->display_on)
		panel->display_on();
पूर्ण

अटल व्योम sh_mobile_lcdc_display_off(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	स्थिर काष्ठा sh_mobile_lcdc_panel_cfg *panel = &ch->cfg->panel_cfg;

	अगर (panel->display_off)
		panel->display_off();

	अगर (ch->tx_dev)
		ch->tx_dev->ops->display_off(ch->tx_dev);
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_check_var(काष्ठा fb_var_screeninfo *var,
				    काष्ठा fb_info *info);

/* -----------------------------------------------------------------------------
 * Format helpers
 */

काष्ठा sh_mobile_lcdc_क्रमmat_info अणु
	u32 fourcc;
	अचिन्हित पूर्णांक bpp;
	bool yuv;
	u32 lddfr;
पूर्ण;

अटल स्थिर काष्ठा sh_mobile_lcdc_क्रमmat_info sh_mobile_क्रमmat_infos[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.bpp = 16,
		.yuv = false,
		.lddfr = LDDFR_PKF_RGB16,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_BGR24,
		.bpp = 24,
		.yuv = false,
		.lddfr = LDDFR_PKF_RGB24,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_BGR32,
		.bpp = 32,
		.yuv = false,
		.lddfr = LDDFR_PKF_ARGB32,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.bpp = 12,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_420,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV21,
		.bpp = 12,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_420,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV16,
		.bpp = 16,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_422,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV61,
		.bpp = 16,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_422,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV24,
		.bpp = 24,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_444,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV42,
		.bpp = 24,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_444,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sh_mobile_lcdc_क्रमmat_info *
sh_mobile_क्रमmat_info(u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sh_mobile_क्रमmat_infos); ++i) अणु
		अगर (sh_mobile_क्रमmat_infos[i].fourcc == fourcc)
			वापस &sh_mobile_क्रमmat_infos[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sh_mobile_क्रमmat_fourcc(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	अगर (var->grayscale > 1)
		वापस var->grayscale;

	चयन (var->bits_per_pixel) अणु
	हाल 16:
		वापस V4L2_PIX_FMT_RGB565;
	हाल 24:
		वापस V4L2_PIX_FMT_BGR24;
	हाल 32:
		वापस V4L2_PIX_FMT_BGR32;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sh_mobile_क्रमmat_is_fourcc(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	वापस var->grayscale > 1;
पूर्ण

/* -----------------------------------------------------------------------------
 * Start, stop and IRQ
 */

अटल irqवापस_t sh_mobile_lcdc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sh_mobile_lcdc_priv *priv = data;
	काष्ठा sh_mobile_lcdc_chan *ch;
	अचिन्हित दीर्घ ldपूर्णांकr;
	पूर्णांक is_sub;
	पूर्णांक k;

	/* Acknowledge पूर्णांकerrupts and disable further VSYNC End IRQs. */
	ldपूर्णांकr = lcdc_पढ़ो(priv, _LDINTR);
	lcdc_ग_लिखो(priv, _LDINTR, (ldपूर्णांकr ^ LDINTR_STATUS_MASK) & ~LDINTR_VEE);

	/* figure out अगर this पूर्णांकerrupt is क्रम मुख्य or sub lcd */
	is_sub = (lcdc_पढ़ो(priv, _LDSR) & LDSR_MSS) ? 1 : 0;

	/* wake up channel and disable घड़ीs */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		ch = &priv->ch[k];

		अगर (!ch->enabled)
			जारी;

		/* Frame End */
		अगर (ldपूर्णांकr & LDINTR_FS) अणु
			अगर (is_sub == lcdc_chan_is_sublcd(ch)) अणु
				ch->frame_end = 1;
				wake_up(&ch->frame_end_रुको);

				sh_mobile_lcdc_clk_off(priv);
			पूर्ण
		पूर्ण

		/* VSYNC End */
		अगर (ldपूर्णांकr & LDINTR_VES)
			complete(&ch->vsync_completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_रुको_क्रम_vsync(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	अचिन्हित दीर्घ ldपूर्णांकr;
	पूर्णांक ret;

	/* Enable VSync End पूर्णांकerrupt and be careful not to acknowledge any
	 * pending पूर्णांकerrupt.
	 */
	ldपूर्णांकr = lcdc_पढ़ो(ch->lcdc, _LDINTR);
	ldपूर्णांकr |= LDINTR_VEE | LDINTR_STATUS_MASK;
	lcdc_ग_लिखो(ch->lcdc, _LDINTR, ldपूर्णांकr);

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ch->vsync_completion,
							msecs_to_jअगरfies(100));
	अगर (!ret)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम sh_mobile_lcdc_start_stop(काष्ठा sh_mobile_lcdc_priv *priv,
				      पूर्णांक start)
अणु
	अचिन्हित दीर्घ पंचांगp = lcdc_पढ़ो(priv, _LDCNT2R);
	पूर्णांक k;

	/* start or stop the lcdc */
	अगर (start)
		lcdc_ग_लिखो(priv, _LDCNT2R, पंचांगp | LDCNT2R_DO);
	अन्यथा
		lcdc_ग_लिखो(priv, _LDCNT2R, पंचांगp & ~LDCNT2R_DO);

	/* रुको until घातer is applied/stopped on all channels */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++)
		अगर (lcdc_पढ़ो(priv, _LDCNT2R) & priv->ch[k].enabled)
			जबतक (1) अणु
				पंचांगp = lcdc_पढ़ो_chan(&priv->ch[k], LDPMR)
				    & LDPMR_LPS;
				अगर (start && पंचांगp == LDPMR_LPS)
					अवरोध;
				अगर (!start && पंचांगp == 0)
					अवरोध;
				cpu_relax();
			पूर्ण

	अगर (!start)
		lcdc_ग_लिखो(priv, _LDDCKSTPR, 1); /* stop करोtघड़ी */
पूर्ण

अटल व्योम sh_mobile_lcdc_geometry(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	स्थिर काष्ठा fb_var_screeninfo *var = &ch->info->var;
	स्थिर काष्ठा fb_videomode *mode = &ch->display.mode;
	अचिन्हित दीर्घ h_total, hsync_pos, display_h_total;
	u32 पंचांगp;

	पंचांगp = ch->ldmt1r_value;
	पंचांगp |= (var->sync & FB_SYNC_VERT_HIGH_ACT) ? 0 : LDMT1R_VPOL;
	पंचांगp |= (var->sync & FB_SYNC_HOR_HIGH_ACT) ? 0 : LDMT1R_HPOL;
	पंचांगp |= (ch->cfg->flags & LCDC_FLAGS_DWPOL) ? LDMT1R_DWPOL : 0;
	पंचांगp |= (ch->cfg->flags & LCDC_FLAGS_DIPOL) ? LDMT1R_DIPOL : 0;
	पंचांगp |= (ch->cfg->flags & LCDC_FLAGS_DAPOL) ? LDMT1R_DAPOL : 0;
	पंचांगp |= (ch->cfg->flags & LCDC_FLAGS_HSCNT) ? LDMT1R_HSCNT : 0;
	पंचांगp |= (ch->cfg->flags & LCDC_FLAGS_DWCNT) ? LDMT1R_DWCNT : 0;
	lcdc_ग_लिखो_chan(ch, LDMT1R, पंचांगp);

	/* setup SYS bus */
	lcdc_ग_लिखो_chan(ch, LDMT2R, ch->cfg->sys_bus_cfg.ldmt2r);
	lcdc_ग_लिखो_chan(ch, LDMT3R, ch->cfg->sys_bus_cfg.ldmt3r);

	/* horizontal configuration */
	h_total = mode->xres + mode->hsync_len + mode->left_margin
		+ mode->right_margin;
	पंचांगp = h_total / 8; /* HTCN */
	पंचांगp |= (min(mode->xres, ch->xres) / 8) << 16; /* HDCN */
	lcdc_ग_लिखो_chan(ch, LDHCNR, पंचांगp);

	hsync_pos = mode->xres + mode->right_margin;
	पंचांगp = hsync_pos / 8; /* HSYNP */
	पंचांगp |= (mode->hsync_len / 8) << 16; /* HSYNW */
	lcdc_ग_लिखो_chan(ch, LDHSYNR, पंचांगp);

	/* vertical configuration */
	पंचांगp = mode->yres + mode->vsync_len + mode->upper_margin
	    + mode->lower_margin; /* VTLN */
	पंचांगp |= min(mode->yres, ch->yres) << 16; /* VDLN */
	lcdc_ग_लिखो_chan(ch, LDVLNR, पंचांगp);

	पंचांगp = mode->yres + mode->lower_margin; /* VSYNP */
	पंचांगp |= mode->vsync_len << 16; /* VSYNW */
	lcdc_ग_लिखो_chan(ch, LDVSYNR, पंचांगp);

	/* Adjust horizontal synchronisation क्रम HDMI */
	display_h_total = mode->xres + mode->hsync_len + mode->left_margin
			+ mode->right_margin;
	पंचांगp = ((mode->xres & 7) << 24) | ((display_h_total & 7) << 16)
	    | ((mode->hsync_len & 7) << 8) | (hsync_pos & 7);
	lcdc_ग_लिखो_chan(ch, LDHAJR, पंचांगp);
	lcdc_ग_लिखो_chan_mirror(ch, LDHAJR, पंचांगp);
पूर्ण

अटल व्योम sh_mobile_lcdc_overlay_setup(काष्ठा sh_mobile_lcdc_overlay *ovl)
अणु
	u32 क्रमmat = 0;

	अगर (!ovl->enabled) अणु
		lcdc_ग_लिखो(ovl->channel->lcdc, LDBCR, LDBCR_UPC(ovl->index));
		lcdc_ग_लिखो_overlay(ovl, LDBnBSIFR(ovl->index), 0);
		lcdc_ग_लिखो(ovl->channel->lcdc, LDBCR,
			   LDBCR_UPF(ovl->index) | LDBCR_UPD(ovl->index));
		वापस;
	पूर्ण

	ovl->base_addr_y = ovl->dma_handle;
	ovl->base_addr_c = ovl->dma_handle
			 + ovl->xres_भव * ovl->yres_भव;

	चयन (ovl->mode) अणु
	हाल LCDC_OVERLAY_BLEND:
		क्रमmat = LDBBSIFR_EN | (ovl->alpha << LDBBSIFR_LAY_SHIFT);
		अवरोध;

	हाल LCDC_OVERLAY_ROP3:
		क्रमmat = LDBBSIFR_EN | LDBBSIFR_BRSEL
		       | (ovl->rop3 << LDBBSIFR_ROP3_SHIFT);
		अवरोध;
	पूर्ण

	चयन (ovl->क्रमmat->fourcc) अणु
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV42:
		क्रमmat |= LDBBSIFR_SWPL | LDBBSIFR_SWPW;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR24:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV24:
		क्रमmat |= LDBBSIFR_SWPL | LDBBSIFR_SWPW | LDBBSIFR_SWPB;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
	शेष:
		क्रमmat |= LDBBSIFR_SWPL;
		अवरोध;
	पूर्ण

	चयन (ovl->क्रमmat->fourcc) अणु
	हाल V4L2_PIX_FMT_RGB565:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_RY | LDBBSIFR_RPKF_RGB16;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR24:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_RY | LDBBSIFR_RPKF_RGB24;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		क्रमmat |= LDBBSIFR_AL_PK | LDBBSIFR_RY | LDDFR_PKF_ARGB32;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_420;
		अवरोध;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_422;
		अवरोध;
	हाल V4L2_PIX_FMT_NV24:
	हाल V4L2_PIX_FMT_NV42:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_444;
		अवरोध;
	पूर्ण

	lcdc_ग_लिखो(ovl->channel->lcdc, LDBCR, LDBCR_UPC(ovl->index));

	lcdc_ग_लिखो_overlay(ovl, LDBnBSIFR(ovl->index), क्रमmat);

	lcdc_ग_लिखो_overlay(ovl, LDBnBSSZR(ovl->index),
		(ovl->yres << LDBBSSZR_BVSS_SHIFT) |
		(ovl->xres << LDBBSSZR_BHSS_SHIFT));
	lcdc_ग_लिखो_overlay(ovl, LDBnBLOCR(ovl->index),
		(ovl->pos_y << LDBBLOCR_CVLC_SHIFT) |
		(ovl->pos_x << LDBBLOCR_CHLC_SHIFT));
	lcdc_ग_लिखो_overlay(ovl, LDBnBSMWR(ovl->index),
		ovl->pitch << LDBBSMWR_BSMW_SHIFT);

	lcdc_ग_लिखो_overlay(ovl, LDBnBSAYR(ovl->index), ovl->base_addr_y);
	lcdc_ग_लिखो_overlay(ovl, LDBnBSACR(ovl->index), ovl->base_addr_c);

	lcdc_ग_लिखो(ovl->channel->lcdc, LDBCR,
		   LDBCR_UPF(ovl->index) | LDBCR_UPD(ovl->index));
पूर्ण

/*
 * __sh_mobile_lcdc_start - Configure and start the LCDC
 * @priv: LCDC device
 *
 * Configure all enabled channels and start the LCDC device. All बाह्यal
 * devices (घड़ीs, MERAM, panels, ...) are not touched by this function.
 */
अटल व्योम __sh_mobile_lcdc_start(काष्ठा sh_mobile_lcdc_priv *priv)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक k, m;

	/* Enable LCDC channels. Read data from बाह्यal memory, aव्योम using the
	 * BEU क्रम now.
	 */
	lcdc_ग_लिखो(priv, _LDCNT2R, priv->ch[0].enabled | priv->ch[1].enabled);

	/* Stop the LCDC first and disable all पूर्णांकerrupts. */
	sh_mobile_lcdc_start_stop(priv, 0);
	lcdc_ग_लिखो(priv, _LDINTR, 0);

	/* Configure घातer supply, करोt घड़ीs and start them. */
	पंचांगp = priv->lddckr;
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		ch = &priv->ch[k];
		अगर (!ch->enabled)
			जारी;

		/* Power supply */
		lcdc_ग_लिखो_chan(ch, LDPMR, 0);

		m = ch->cfg->घड़ी_भागider;
		अगर (!m)
			जारी;

		/* FIXME: sh7724 can only use 42, 48, 54 and 60 क्रम the भागider
		 * denominator.
		 */
		lcdc_ग_लिखो_chan(ch, LDDCKPAT1R, 0);
		lcdc_ग_लिखो_chan(ch, LDDCKPAT2R, (1 << (m/2)) - 1);

		अगर (m == 1)
			m = LDDCKR_MOSEL;
		पंचांगp |= m << (lcdc_chan_is_sublcd(ch) ? 8 : 0);
	पूर्ण

	lcdc_ग_लिखो(priv, _LDDCKR, पंचांगp);
	lcdc_ग_लिखो(priv, _LDDCKSTPR, 0);
	lcdc_रुको_bit(priv, _LDDCKSTPR, ~0, 0);

	/* Setup geometry, क्रमmat, frame buffer memory and operation mode. */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		ch = &priv->ch[k];
		अगर (!ch->enabled)
			जारी;

		sh_mobile_lcdc_geometry(ch);

		पंचांगp = ch->क्रमmat->lddfr;

		अगर (ch->क्रमmat->yuv) अणु
			चयन (ch->colorspace) अणु
			हाल V4L2_COLORSPACE_REC709:
				पंचांगp |= LDDFR_CF1;
				अवरोध;
			हाल V4L2_COLORSPACE_JPEG:
				पंचांगp |= LDDFR_CF0;
				अवरोध;
			पूर्ण
		पूर्ण

		lcdc_ग_लिखो_chan(ch, LDDFR, पंचांगp);
		lcdc_ग_लिखो_chan(ch, LDMLSR, ch->line_size);
		lcdc_ग_लिखो_chan(ch, LDSA1R, ch->base_addr_y);
		अगर (ch->क्रमmat->yuv)
			lcdc_ग_लिखो_chan(ch, LDSA2R, ch->base_addr_c);

		/* When using deferred I/O mode, configure the LCDC क्रम one-shot
		 * operation and enable the frame end पूर्णांकerrupt. Otherwise use
		 * continuous पढ़ो mode.
		 */
		अगर (ch->ldmt1r_value & LDMT1R_IFM &&
		    ch->cfg->sys_bus_cfg.deferred_io_msec) अणु
			lcdc_ग_लिखो_chan(ch, LDSM1R, LDSM1R_OS);
			lcdc_ग_लिखो(priv, _LDINTR, LDINTR_FE);
		पूर्ण अन्यथा अणु
			lcdc_ग_लिखो_chan(ch, LDSM1R, 0);
		पूर्ण
	पूर्ण

	/* Word and दीर्घ word swap. */
	चयन (priv->ch[0].क्रमmat->fourcc) अणु
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV42:
		पंचांगp = LDDDSR_LS | LDDDSR_WS;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR24:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV24:
		पंचांगp = LDDDSR_LS | LDDDSR_WS | LDDDSR_BS;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
	शेष:
		पंचांगp = LDDDSR_LS;
		अवरोध;
	पूर्ण
	lcdc_ग_लिखो(priv, _LDDDSR, पंचांगp);

	/* Enable the display output. */
	lcdc_ग_लिखो(priv, _LDCNT1R, LDCNT1R_DE);
	sh_mobile_lcdc_start_stop(priv, 1);
	priv->started = 1;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_start(काष्ठा sh_mobile_lcdc_priv *priv)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;
	पूर्णांक k;

	/* enable घड़ीs beक्रमe accessing the hardware */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		अगर (priv->ch[k].enabled)
			sh_mobile_lcdc_clk_on(priv);
	पूर्ण

	/* reset */
	lcdc_ग_लिखो(priv, _LDCNT2R, lcdc_पढ़ो(priv, _LDCNT2R) | LDCNT2R_BR);
	lcdc_रुको_bit(priv, _LDCNT2R, LDCNT2R_BR, 0);

	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		स्थिर काष्ठा sh_mobile_lcdc_panel_cfg *panel;

		ch = &priv->ch[k];
		अगर (!ch->enabled)
			जारी;

		panel = &ch->cfg->panel_cfg;
		अगर (panel->setup_sys) अणु
			ret = panel->setup_sys(ch, &sh_mobile_lcdc_sys_bus_ops);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Compute frame buffer base address and pitch क्रम each channel. */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		ch = &priv->ch[k];
		अगर (!ch->enabled)
			जारी;

		ch->base_addr_y = ch->dma_handle;
		ch->base_addr_c = ch->dma_handle
				+ ch->xres_भव * ch->yres_भव;
		ch->line_size = ch->pitch;
	पूर्ण

	क्रम (k = 0; k < ARRAY_SIZE(priv->overlays); ++k) अणु
		काष्ठा sh_mobile_lcdc_overlay *ovl = &priv->overlays[k];
		sh_mobile_lcdc_overlay_setup(ovl);
	पूर्ण

	/* Start the LCDC. */
	__sh_mobile_lcdc_start(priv);

	/* Setup deferred I/O, tell the board code to enable the panels, and
	 * turn backlight on.
	 */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		ch = &priv->ch[k];
		अगर (!ch->enabled)
			जारी;

		पंचांगp = ch->cfg->sys_bus_cfg.deferred_io_msec;
		अगर (ch->ldmt1r_value & LDMT1R_IFM && पंचांगp) अणु
			ch->defio.deferred_io = sh_mobile_lcdc_deferred_io;
			ch->defio.delay = msecs_to_jअगरfies(पंचांगp);
			ch->info->fbdefio = &ch->defio;
			fb_deferred_io_init(ch->info);
		पूर्ण

		sh_mobile_lcdc_display_on(ch);

		अगर (ch->bl) अणु
			ch->bl->props.घातer = FB_BLANK_UNBLANK;
			backlight_update_status(ch->bl);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sh_mobile_lcdc_stop(काष्ठा sh_mobile_lcdc_priv *priv)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch;
	पूर्णांक k;

	/* clean up deferred io and ask board code to disable panel */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++) अणु
		ch = &priv->ch[k];
		अगर (!ch->enabled)
			जारी;

		/* deferred io mode:
		 * flush frame, and रुको क्रम frame end पूर्णांकerrupt
		 * clean up deferred io and enable घड़ी
		 */
		अगर (ch->info && ch->info->fbdefio) अणु
			ch->frame_end = 0;
			schedule_delayed_work(&ch->info->deferred_work, 0);
			रुको_event(ch->frame_end_रुको, ch->frame_end);
			fb_deferred_io_cleanup(ch->info);
			ch->info->fbdefio = शून्य;
			sh_mobile_lcdc_clk_on(priv);
		पूर्ण

		अगर (ch->bl) अणु
			ch->bl->props.घातer = FB_BLANK_POWERDOWN;
			backlight_update_status(ch->bl);
		पूर्ण

		sh_mobile_lcdc_display_off(ch);
	पूर्ण

	/* stop the lcdc */
	अगर (priv->started) अणु
		sh_mobile_lcdc_start_stop(priv, 0);
		priv->started = 0;
	पूर्ण

	/* stop घड़ीs */
	क्रम (k = 0; k < ARRAY_SIZE(priv->ch); k++)
		अगर (priv->ch[k].enabled)
			sh_mobile_lcdc_clk_off(priv);
पूर्ण

अटल पूर्णांक __sh_mobile_lcdc_check_var(काष्ठा fb_var_screeninfo *var,
				      काष्ठा fb_info *info)
अणु
	अगर (var->xres > MAX_XRES || var->yres > MAX_YRES)
		वापस -EINVAL;

	/* Make sure the भव resolution is at least as big as the visible
	 * resolution.
	 */
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	अगर (sh_mobile_क्रमmat_is_fourcc(var)) अणु
		स्थिर काष्ठा sh_mobile_lcdc_क्रमmat_info *क्रमmat;

		क्रमmat = sh_mobile_क्रमmat_info(var->grayscale);
		अगर (क्रमmat == शून्य)
			वापस -EINVAL;
		var->bits_per_pixel = क्रमmat->bpp;

		/* Default to RGB and JPEG color-spaces क्रम RGB and YUV क्रमmats
		 * respectively.
		 */
		अगर (!क्रमmat->yuv)
			var->colorspace = V4L2_COLORSPACE_SRGB;
		अन्यथा अगर (var->colorspace != V4L2_COLORSPACE_REC709)
			var->colorspace = V4L2_COLORSPACE_JPEG;
	पूर्ण अन्यथा अणु
		अगर (var->bits_per_pixel <= 16) अणु		/* RGB 565 */
			var->bits_per_pixel = 16;
			var->red.offset = 11;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 6;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
		पूर्ण अन्यथा अगर (var->bits_per_pixel <= 24) अणु		/* RGB 888 */
			var->bits_per_pixel = 24;
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 0;
			var->transp.length = 0;
		पूर्ण अन्यथा अगर (var->bits_per_pixel <= 32) अणु		/* RGBA 888 */
			var->bits_per_pixel = 32;
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 24;
			var->transp.length = 8;
		पूर्ण अन्यथा
			वापस -EINVAL;

		var->red.msb_right = 0;
		var->green.msb_right = 0;
		var->blue.msb_right = 0;
		var->transp.msb_right = 0;
	पूर्ण

	/* Make sure we करोn't exceed our allocated memory. */
	अगर (var->xres_भव * var->yres_भव * var->bits_per_pixel / 8 >
	    info->fix.smem_len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Frame buffer operations - Overlays
 */

अटल sमाप_प्रकार
overlay_alpha_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", ovl->alpha);
पूर्ण

अटल sमाप_प्रकार
overlay_alpha_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;
	अचिन्हित पूर्णांक alpha;
	अक्षर *endp;

	alpha = simple_म_से_अदीर्घ(buf, &endp, 10);
	अगर (है_खाली(*endp))
		endp++;

	अगर (endp - buf != count)
		वापस -EINVAL;

	अगर (alpha > 255)
		वापस -EINVAL;

	अगर (ovl->alpha != alpha) अणु
		ovl->alpha = alpha;

		अगर (ovl->mode == LCDC_OVERLAY_BLEND && ovl->enabled)
			sh_mobile_lcdc_overlay_setup(ovl);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
overlay_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", ovl->mode);
पूर्ण

अटल sमाप_प्रकार
overlay_mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;
	अचिन्हित पूर्णांक mode;
	अक्षर *endp;

	mode = simple_म_से_अदीर्घ(buf, &endp, 10);
	अगर (है_खाली(*endp))
		endp++;

	अगर (endp - buf != count)
		वापस -EINVAL;

	अगर (mode != LCDC_OVERLAY_BLEND && mode != LCDC_OVERLAY_ROP3)
		वापस -EINVAL;

	अगर (ovl->mode != mode) अणु
		ovl->mode = mode;

		अगर (ovl->enabled)
			sh_mobile_lcdc_overlay_setup(ovl);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
overlay_position_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d,%d\n", ovl->pos_x, ovl->pos_y);
पूर्ण

अटल sमाप_प्रकार
overlay_position_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;
	अक्षर *endp;
	पूर्णांक pos_x;
	पूर्णांक pos_y;

	pos_x = simple_म_से_दीर्घ(buf, &endp, 10);
	अगर (*endp != ',')
		वापस -EINVAL;

	pos_y = simple_म_से_दीर्घ(endp + 1, &endp, 10);
	अगर (है_खाली(*endp))
		endp++;

	अगर (endp - buf != count)
		वापस -EINVAL;

	अगर (ovl->pos_x != pos_x || ovl->pos_y != pos_y) अणु
		ovl->pos_x = pos_x;
		ovl->pos_y = pos_y;

		अगर (ovl->enabled)
			sh_mobile_lcdc_overlay_setup(ovl);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
overlay_rop3_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", ovl->rop3);
पूर्ण

अटल sमाप_प्रकार
overlay_rop3_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;
	अचिन्हित पूर्णांक rop3;
	अक्षर *endp;

	rop3 = simple_म_से_अदीर्घ(buf, &endp, 10);
	अगर (है_खाली(*endp))
		endp++;

	अगर (endp - buf != count)
		वापस -EINVAL;

	अगर (rop3 > 255)
		वापस -EINVAL;

	अगर (ovl->rop3 != rop3) अणु
		ovl->rop3 = rop3;

		अगर (ovl->mode == LCDC_OVERLAY_ROP3 && ovl->enabled)
			sh_mobile_lcdc_overlay_setup(ovl);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा device_attribute overlay_sysfs_attrs[] = अणु
	__ATTR(ovl_alpha, S_IRUGO|S_IWUSR,
	       overlay_alpha_show, overlay_alpha_store),
	__ATTR(ovl_mode, S_IRUGO|S_IWUSR,
	       overlay_mode_show, overlay_mode_store),
	__ATTR(ovl_position, S_IRUGO|S_IWUSR,
	       overlay_position_show, overlay_position_store),
	__ATTR(ovl_rop3, S_IRUGO|S_IWUSR,
	       overlay_rop3_show, overlay_rop3_store),
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo sh_mobile_lcdc_overlay_fix  = अणु
	.id =		"SH Mobile LCDC",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.accel =	FB_ACCEL_NONE,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywrapstep =	0,
	.capabilities =	FB_CAP_FOURCC,
पूर्ण;

अटल पूर्णांक sh_mobile_lcdc_overlay_pan(काष्ठा fb_var_screeninfo *var,
				    काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;
	अचिन्हित दीर्घ base_addr_y;
	अचिन्हित दीर्घ base_addr_c;
	अचिन्हित दीर्घ y_offset;
	अचिन्हित दीर्घ c_offset;

	अगर (!ovl->क्रमmat->yuv) अणु
		y_offset = (var->yoffset * ovl->xres_भव + var->xoffset)
			 * ovl->क्रमmat->bpp / 8;
		c_offset = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक xsub = ovl->क्रमmat->bpp < 24 ? 2 : 1;
		अचिन्हित पूर्णांक ysub = ovl->क्रमmat->bpp < 16 ? 2 : 1;

		y_offset = var->yoffset * ovl->xres_भव + var->xoffset;
		c_offset = var->yoffset / ysub * ovl->xres_भव * 2 / xsub
			 + var->xoffset * 2 / xsub;
	पूर्ण

	/* If the Y offset hasn't changed, the C offset hasn't either. There's
	 * nothing to करो in that हाल.
	 */
	अगर (y_offset == ovl->pan_y_offset)
		वापस 0;

	/* Set the source address क्रम the next refresh */
	base_addr_y = ovl->dma_handle + y_offset;
	base_addr_c = ovl->dma_handle + ovl->xres_भव * ovl->yres_भव
		    + c_offset;

	ovl->base_addr_y = base_addr_y;
	ovl->base_addr_c = base_addr_c;
	ovl->pan_y_offset = y_offset;

	lcdc_ग_लिखो(ovl->channel->lcdc, LDBCR, LDBCR_UPC(ovl->index));

	lcdc_ग_लिखो_overlay(ovl, LDBnBSAYR(ovl->index), ovl->base_addr_y);
	lcdc_ग_लिखो_overlay(ovl, LDBnBSACR(ovl->index), ovl->base_addr_c);

	lcdc_ग_लिखो(ovl->channel->lcdc, LDBCR,
		   LDBCR_UPF(ovl->index) | LDBCR_UPD(ovl->index));

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_overlay_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg)
अणु
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	चयन (cmd) अणु
	हाल FBIO_WAITFORVSYNC:
		वापस sh_mobile_lcdc_रुको_क्रम_vsync(ovl->channel);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_overlay_check_var(काष्ठा fb_var_screeninfo *var,
					  काष्ठा fb_info *info)
अणु
	वापस __sh_mobile_lcdc_check_var(var, info);
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_overlay_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	ovl->क्रमmat =
		sh_mobile_क्रमmat_info(sh_mobile_क्रमmat_fourcc(&info->var));

	ovl->xres = info->var.xres;
	ovl->xres_भव = info->var.xres_भव;
	ovl->yres = info->var.yres;
	ovl->yres_भव = info->var.yres_भव;

	अगर (ovl->क्रमmat->yuv)
		ovl->pitch = info->var.xres_भव;
	अन्यथा
		ovl->pitch = info->var.xres_भव * ovl->क्रमmat->bpp / 8;

	sh_mobile_lcdc_overlay_setup(ovl);

	info->fix.line_length = ovl->pitch;

	अगर (sh_mobile_क्रमmat_is_fourcc(&info->var)) अणु
		info->fix.type = FB_TYPE_FOURCC;
		info->fix.visual = FB_VISUAL_FOURCC;
	पूर्ण अन्यथा अणु
		info->fix.type = FB_TYPE_PACKED_PIXELS;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	पूर्ण

	वापस 0;
पूर्ण

/* Overlay blanking. Disable the overlay when blanked. */
अटल पूर्णांक sh_mobile_lcdc_overlay_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	ovl->enabled = !blank;
	sh_mobile_lcdc_overlay_setup(ovl);

	/* Prevent the backlight from receiving a blanking event by वापसing
	 * a non-zero value.
	 */
	वापस 1;
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_overlay_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sh_mobile_lcdc_overlay *ovl = info->par;

	वापस dma_mmap_coherent(ovl->channel->lcdc->dev, vma, ovl->fb_mem,
				 ovl->dma_handle, ovl->fb_size);
पूर्ण

अटल स्थिर काष्ठा fb_ops sh_mobile_lcdc_overlay_ops = अणु
	.owner          = THIS_MODULE,
	.fb_पढ़ो        = fb_sys_पढ़ो,
	.fb_ग_लिखो       = fb_sys_ग_लिखो,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_blank	= sh_mobile_lcdc_overlay_blank,
	.fb_pan_display = sh_mobile_lcdc_overlay_pan,
	.fb_ioctl       = sh_mobile_lcdc_overlay_ioctl,
	.fb_check_var	= sh_mobile_lcdc_overlay_check_var,
	.fb_set_par	= sh_mobile_lcdc_overlay_set_par,
	.fb_mmap	= sh_mobile_lcdc_overlay_mmap,
पूर्ण;

अटल व्योम
sh_mobile_lcdc_overlay_fb_unरेजिस्टर(काष्ठा sh_mobile_lcdc_overlay *ovl)
अणु
	काष्ठा fb_info *info = ovl->info;

	अगर (info == शून्य || info->dev == शून्य)
		वापस;

	unरेजिस्टर_framebuffer(ovl->info);
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_overlay_fb_रेजिस्टर(काष्ठा sh_mobile_lcdc_overlay *ovl)
अणु
	काष्ठा sh_mobile_lcdc_priv *lcdc = ovl->channel->lcdc;
	काष्ठा fb_info *info = ovl->info;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (info == शून्य)
		वापस 0;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0)
		वापस ret;

	dev_info(lcdc->dev, "registered %s/overlay %u as %dx%d %dbpp.\n",
		 dev_name(lcdc->dev), ovl->index, info->var.xres,
		 info->var.yres, info->var.bits_per_pixel);

	क्रम (i = 0; i < ARRAY_SIZE(overlay_sysfs_attrs); ++i) अणु
		ret = device_create_file(info->dev, &overlay_sysfs_attrs[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
sh_mobile_lcdc_overlay_fb_cleanup(काष्ठा sh_mobile_lcdc_overlay *ovl)
अणु
	काष्ठा fb_info *info = ovl->info;

	अगर (info == शून्य || info->device == शून्य)
		वापस;

	framebuffer_release(info);
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_overlay_fb_init(काष्ठा sh_mobile_lcdc_overlay *ovl)
अणु
	काष्ठा sh_mobile_lcdc_priv *priv = ovl->channel->lcdc;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा fb_info *info;

	/* Allocate and initialize the frame buffer device. */
	info = framebuffer_alloc(0, priv->dev);
	अगर (!info)
		वापस -ENOMEM;

	ovl->info = info;

	info->flags = FBINFO_FLAG_DEFAULT;
	info->fbops = &sh_mobile_lcdc_overlay_ops;
	info->device = priv->dev;
	info->screen_buffer = ovl->fb_mem;
	info->par = ovl;

	/* Initialize fixed screen inक्रमmation. Restrict pan to 2 lines steps
	 * क्रम NV12 and NV21.
	 */
	info->fix = sh_mobile_lcdc_overlay_fix;
	snम_लिखो(info->fix.id, माप(info->fix.id),
		 "SH Mobile LCDC Overlay %u", ovl->index);
	info->fix.smem_start = ovl->dma_handle;
	info->fix.smem_len = ovl->fb_size;
	info->fix.line_length = ovl->pitch;

	अगर (ovl->क्रमmat->yuv)
		info->fix.visual = FB_VISUAL_FOURCC;
	अन्यथा
		info->fix.visual = FB_VISUAL_TRUECOLOR;

	चयन (ovl->क्रमmat->fourcc) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		info->fix.ypanstep = 2;
		fallthrough;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		info->fix.xpanstep = 2;
	पूर्ण

	/* Initialize variable screen inक्रमmation. */
	var = &info->var;
	स_रखो(var, 0, माप(*var));
	var->xres = ovl->xres;
	var->yres = ovl->yres;
	var->xres_भव = ovl->xres_भव;
	var->yres_भव = ovl->yres_भव;
	var->activate = FB_ACTIVATE_NOW;

	/* Use the legacy API by शेष क्रम RGB क्रमmats, and the FOURCC API
	 * क्रम YUV क्रमmats.
	 */
	अगर (!ovl->क्रमmat->yuv)
		var->bits_per_pixel = ovl->क्रमmat->bpp;
	अन्यथा
		var->grayscale = ovl->क्रमmat->fourcc;

	वापस sh_mobile_lcdc_overlay_check_var(var, info);
पूर्ण

/* -----------------------------------------------------------------------------
 * Frame buffer operations - मुख्य frame buffer
 */

अटल पूर्णांक sh_mobile_lcdc_setcolreg(u_पूर्णांक regno,
				    u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
				    u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	u32 *palette = info->pseuकरो_palette;

	अगर (regno >= PALETTE_NR)
		वापस -EINVAL;

	/* only FB_VISUAL_TRUECOLOR supported */

	red >>= 16 - info->var.red.length;
	green >>= 16 - info->var.green.length;
	blue >>= 16 - info->var.blue.length;
	transp >>= 16 - info->var.transp.length;

	palette[regno] = (red << info->var.red.offset) |
	  (green << info->var.green.offset) |
	  (blue << info->var.blue.offset) |
	  (transp << info->var.transp.offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_fix_screeninfo sh_mobile_lcdc_fix  = अणु
	.id =		"SH Mobile LCDC",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.accel =	FB_ACCEL_NONE,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywrapstep =	0,
	.capabilities =	FB_CAP_FOURCC,
पूर्ण;

अटल व्योम sh_mobile_lcdc_fillrect(काष्ठा fb_info *info,
				    स्थिर काष्ठा fb_fillrect *rect)
अणु
	sys_fillrect(info, rect);
	sh_mobile_lcdc_deferred_io_touch(info);
पूर्ण

अटल व्योम sh_mobile_lcdc_copyarea(काष्ठा fb_info *info,
				    स्थिर काष्ठा fb_copyarea *area)
अणु
	sys_copyarea(info, area);
	sh_mobile_lcdc_deferred_io_touch(info);
पूर्ण

अटल व्योम sh_mobile_lcdc_imageblit(काष्ठा fb_info *info,
				     स्थिर काष्ठा fb_image *image)
अणु
	sys_imageblit(info, image);
	sh_mobile_lcdc_deferred_io_touch(info);
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_pan(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	काष्ठा sh_mobile_lcdc_priv *priv = ch->lcdc;
	अचिन्हित दीर्घ ldrcntr;
	अचिन्हित दीर्घ base_addr_y, base_addr_c;
	अचिन्हित दीर्घ y_offset;
	अचिन्हित दीर्घ c_offset;

	अगर (!ch->क्रमmat->yuv) अणु
		y_offset = (var->yoffset * ch->xres_भव + var->xoffset)
			 * ch->क्रमmat->bpp / 8;
		c_offset = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक xsub = ch->क्रमmat->bpp < 24 ? 2 : 1;
		अचिन्हित पूर्णांक ysub = ch->क्रमmat->bpp < 16 ? 2 : 1;

		y_offset = var->yoffset * ch->xres_भव + var->xoffset;
		c_offset = var->yoffset / ysub * ch->xres_भव * 2 / xsub
			 + var->xoffset * 2 / xsub;
	पूर्ण

	/* If the Y offset hasn't changed, the C offset hasn't either. There's
	 * nothing to करो in that हाल.
	 */
	अगर (y_offset == ch->pan_y_offset)
		वापस 0;

	/* Set the source address क्रम the next refresh */
	base_addr_y = ch->dma_handle + y_offset;
	base_addr_c = ch->dma_handle + ch->xres_भव * ch->yres_भव
		    + c_offset;

	ch->base_addr_y = base_addr_y;
	ch->base_addr_c = base_addr_c;
	ch->pan_y_offset = y_offset;

	lcdc_ग_लिखो_chan_mirror(ch, LDSA1R, base_addr_y);
	अगर (ch->क्रमmat->yuv)
		lcdc_ग_लिखो_chan_mirror(ch, LDSA2R, base_addr_c);

	ldrcntr = lcdc_पढ़ो(priv, _LDRCNTR);
	अगर (lcdc_chan_is_sublcd(ch))
		lcdc_ग_लिखो(ch->lcdc, _LDRCNTR, ldrcntr ^ LDRCNTR_SRS);
	अन्यथा
		lcdc_ग_लिखो(ch->lcdc, _LDRCNTR, ldrcntr ^ LDRCNTR_MRS);


	sh_mobile_lcdc_deferred_io_touch(info);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	पूर्णांक retval;

	चयन (cmd) अणु
	हाल FBIO_WAITFORVSYNC:
		retval = sh_mobile_lcdc_रुको_क्रम_vsync(ch);
		अवरोध;

	शेष:
		retval = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम sh_mobile_fb_reconfig(काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	काष्ठा fb_var_screeninfo var;
	काष्ठा fb_videomode mode;

	अगर (ch->use_count > 1 || (ch->use_count == 1 && !info->fbcon_par))
		/* More framebuffer users are active */
		वापस;

	fb_var_to_videomode(&mode, &info->var);

	अगर (fb_mode_is_equal(&ch->display.mode, &mode))
		वापस;

	/* Display has been re-plugged, framebuffer is मुक्त now, reconfigure */
	var = info->var;
	fb_videomode_to_var(&var, &ch->display.mode);
	var.width = ch->display.width;
	var.height = ch->display.height;
	var.activate = FB_ACTIVATE_NOW;

	अगर (fb_set_var(info, &var) < 0)
		/* Couldn't reconfigure, hopefully, can जारी as beक्रमe */
		वापस;

	fbcon_update_vcs(info, true);
पूर्ण

/*
 * Locking: both .fb_release() and .fb_खोलो() are called with info->lock held अगर
 * user == 1, or with console sem held, अगर user == 0.
 */
अटल पूर्णांक sh_mobile_lcdc_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;

	mutex_lock(&ch->खोलो_lock);
	dev_dbg(info->dev, "%s(): %d users\n", __func__, ch->use_count);

	ch->use_count--;

	/* Nothing to reconfigure, when called from fbcon */
	अगर (user) अणु
		console_lock();
		sh_mobile_fb_reconfig(info);
		console_unlock();
	पूर्ण

	mutex_unlock(&ch->खोलो_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;

	mutex_lock(&ch->खोलो_lock);
	ch->use_count++;

	dev_dbg(info->dev, "%s(): %d users\n", __func__, ch->use_count);
	mutex_unlock(&ch->खोलो_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_check_var(काष्ठा fb_var_screeninfo *var,
				    काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	काष्ठा sh_mobile_lcdc_priv *p = ch->lcdc;
	अचिन्हित पूर्णांक best_dist = (अचिन्हित पूर्णांक)-1;
	अचिन्हित पूर्णांक best_xres = 0;
	अचिन्हित पूर्णांक best_yres = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* If board code provides us with a list of available modes, make sure
	 * we use one of them. Find the mode बंदst to the requested one. The
	 * distance between two modes is defined as the size of the
	 * non-overlapping parts of the two rectangles.
	 */
	क्रम (i = 0; i < ch->cfg->num_modes; ++i) अणु
		स्थिर काष्ठा fb_videomode *mode = &ch->cfg->lcd_modes[i];
		अचिन्हित पूर्णांक dist;

		/* We can only round up. */
		अगर (var->xres > mode->xres || var->yres > mode->yres)
			जारी;

		dist = var->xres * var->yres + mode->xres * mode->yres
		     - 2 * min(var->xres, mode->xres)
			 * min(var->yres, mode->yres);

		अगर (dist < best_dist) अणु
			best_xres = mode->xres;
			best_yres = mode->yres;
			best_dist = dist;
		पूर्ण
	पूर्ण

	/* If no available mode can be used, वापस an error. */
	अगर (ch->cfg->num_modes != 0) अणु
		अगर (best_dist == (अचिन्हित पूर्णांक)-1)
			वापस -EINVAL;

		var->xres = best_xres;
		var->yres = best_yres;
	पूर्ण

	ret = __sh_mobile_lcdc_check_var(var, info);
	अगर (ret < 0)
		वापस ret;

	/* only accept the क्रमced_fourcc क्रम dual channel configurations */
	अगर (p->क्रमced_fourcc &&
	    p->क्रमced_fourcc != sh_mobile_क्रमmat_fourcc(var))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	पूर्णांक ret;

	sh_mobile_lcdc_stop(ch->lcdc);

	ch->क्रमmat = sh_mobile_क्रमmat_info(sh_mobile_क्रमmat_fourcc(&info->var));
	ch->colorspace = info->var.colorspace;

	ch->xres = info->var.xres;
	ch->xres_भव = info->var.xres_भव;
	ch->yres = info->var.yres;
	ch->yres_भव = info->var.yres_भव;

	अगर (ch->क्रमmat->yuv)
		ch->pitch = info->var.xres_भव;
	अन्यथा
		ch->pitch = info->var.xres_भव * ch->क्रमmat->bpp / 8;

	ret = sh_mobile_lcdc_start(ch->lcdc);
	अगर (ret < 0)
		dev_err(info->dev, "%s: unable to restart LCDC\n", __func__);

	info->fix.line_length = ch->pitch;

	अगर (sh_mobile_क्रमmat_is_fourcc(&info->var)) अणु
		info->fix.type = FB_TYPE_FOURCC;
		info->fix.visual = FB_VISUAL_FOURCC;
	पूर्ण अन्यथा अणु
		info->fix.type = FB_TYPE_PACKED_PIXELS;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Screen blanking. Behavior is as follows:
 * FB_BLANK_UNBLANK: screen unblanked, घड़ीs enabled
 * FB_BLANK_NORMAL: screen blanked, घड़ीs enabled
 * FB_BLANK_VSYNC,
 * FB_BLANK_HSYNC,
 * FB_BLANK_POWEROFF: screen blanked, घड़ीs disabled
 */
अटल पूर्णांक sh_mobile_lcdc_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;
	काष्ठा sh_mobile_lcdc_priv *p = ch->lcdc;

	/* blank the screen? */
	अगर (blank > FB_BLANK_UNBLANK && ch->blank_status == FB_BLANK_UNBLANK) अणु
		काष्ठा fb_fillrect rect = अणु
			.width = ch->xres,
			.height = ch->yres,
		पूर्ण;
		sh_mobile_lcdc_fillrect(info, &rect);
	पूर्ण
	/* turn घड़ीs on? */
	अगर (blank <= FB_BLANK_NORMAL && ch->blank_status > FB_BLANK_NORMAL) अणु
		sh_mobile_lcdc_clk_on(p);
	पूर्ण
	/* turn घड़ीs off? */
	अगर (blank > FB_BLANK_NORMAL && ch->blank_status <= FB_BLANK_NORMAL) अणु
		/* make sure the screen is updated with the black fill beक्रमe
		 * चयनing the घड़ीs off. one vsync is not enough since
		 * blanking may occur in the middle of a refresh. deferred io
		 * mode will reenable the घड़ीs and update the screen in समय,
		 * so it करोes not need this. */
		अगर (!info->fbdefio) अणु
			sh_mobile_lcdc_रुको_क्रम_vsync(ch);
			sh_mobile_lcdc_रुको_क्रम_vsync(ch);
		पूर्ण
		sh_mobile_lcdc_clk_off(p);
	पूर्ण

	ch->blank_status = blank;
	वापस 0;
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = info->par;

	वापस dma_mmap_coherent(ch->lcdc->dev, vma, ch->fb_mem,
				 ch->dma_handle, ch->fb_size);
पूर्ण

अटल स्थिर काष्ठा fb_ops sh_mobile_lcdc_ops = अणु
	.owner          = THIS_MODULE,
	.fb_setcolreg	= sh_mobile_lcdc_setcolreg,
	.fb_पढ़ो        = fb_sys_पढ़ो,
	.fb_ग_लिखो       = fb_sys_ग_लिखो,
	.fb_fillrect	= sh_mobile_lcdc_fillrect,
	.fb_copyarea	= sh_mobile_lcdc_copyarea,
	.fb_imageblit	= sh_mobile_lcdc_imageblit,
	.fb_blank	= sh_mobile_lcdc_blank,
	.fb_pan_display = sh_mobile_lcdc_pan,
	.fb_ioctl       = sh_mobile_lcdc_ioctl,
	.fb_खोलो	= sh_mobile_lcdc_खोलो,
	.fb_release	= sh_mobile_lcdc_release,
	.fb_check_var	= sh_mobile_lcdc_check_var,
	.fb_set_par	= sh_mobile_lcdc_set_par,
	.fb_mmap	= sh_mobile_lcdc_mmap,
पूर्ण;

अटल व्योम
sh_mobile_lcdc_channel_fb_unरेजिस्टर(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	अगर (ch->info && ch->info->dev)
		unरेजिस्टर_framebuffer(ch->info);
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_channel_fb_रेजिस्टर(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	काष्ठा fb_info *info = ch->info;
	पूर्णांक ret;

	अगर (info->fbdefio) अणु
		ch->sglist = vदो_स्मृति(माप(काष्ठा scatterlist) *
				     ch->fb_size >> PAGE_SHIFT);
		अगर (!ch->sglist)
			वापस -ENOMEM;
	पूर्ण

	info->bl_dev = ch->bl;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0)
		वापस ret;

	dev_info(ch->lcdc->dev, "registered %s/%s as %dx%d %dbpp.\n",
		 dev_name(ch->lcdc->dev), (ch->cfg->chan == LCDC_CHAN_MAINLCD) ?
		 "mainlcd" : "sublcd", info->var.xres, info->var.yres,
		 info->var.bits_per_pixel);

	/* deferred io mode: disable घड़ी to save घातer */
	अगर (info->fbdefio || info->state == FBINFO_STATE_SUSPENDED)
		sh_mobile_lcdc_clk_off(ch->lcdc);

	वापस ret;
पूर्ण

अटल व्योम
sh_mobile_lcdc_channel_fb_cleanup(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	काष्ठा fb_info *info = ch->info;

	अगर (!info || !info->device)
		वापस;

	vमुक्त(ch->sglist);

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_channel_fb_init(काष्ठा sh_mobile_lcdc_chan *ch,
			       स्थिर काष्ठा fb_videomode *modes,
			       अचिन्हित पूर्णांक num_modes)
अणु
	काष्ठा sh_mobile_lcdc_priv *priv = ch->lcdc;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा fb_info *info;
	पूर्णांक ret;

	/* Allocate and initialize the frame buffer device. Create the modes
	 * list and allocate the color map.
	 */
	info = framebuffer_alloc(0, priv->dev);
	अगर (!info)
		वापस -ENOMEM;

	ch->info = info;

	info->flags = FBINFO_FLAG_DEFAULT;
	info->fbops = &sh_mobile_lcdc_ops;
	info->device = priv->dev;
	info->screen_buffer = ch->fb_mem;
	info->pseuकरो_palette = &ch->pseuकरो_palette;
	info->par = ch;

	fb_videomode_to_modelist(modes, num_modes, &info->modelist);

	ret = fb_alloc_cmap(&info->cmap, PALETTE_NR, 0);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "unable to allocate cmap\n");
		वापस ret;
	पूर्ण

	/* Initialize fixed screen inक्रमmation. Restrict pan to 2 lines steps
	 * क्रम NV12 and NV21.
	 */
	info->fix = sh_mobile_lcdc_fix;
	info->fix.smem_start = ch->dma_handle;
	info->fix.smem_len = ch->fb_size;
	info->fix.line_length = ch->pitch;

	अगर (ch->क्रमmat->yuv)
		info->fix.visual = FB_VISUAL_FOURCC;
	अन्यथा
		info->fix.visual = FB_VISUAL_TRUECOLOR;

	चयन (ch->क्रमmat->fourcc) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		info->fix.ypanstep = 2;
		fallthrough;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		info->fix.xpanstep = 2;
	पूर्ण

	/* Initialize variable screen inक्रमmation using the first mode as
	 * शेष.
	 */
	var = &info->var;
	fb_videomode_to_var(var, modes);
	var->width = ch->display.width;
	var->height = ch->display.height;
	var->xres_भव = ch->xres_भव;
	var->yres_भव = ch->yres_भव;
	var->activate = FB_ACTIVATE_NOW;

	/* Use the legacy API by शेष क्रम RGB क्रमmats, and the FOURCC API
	 * क्रम YUV क्रमmats.
	 */
	अगर (!ch->क्रमmat->yuv)
		var->bits_per_pixel = ch->क्रमmat->bpp;
	अन्यथा
		var->grayscale = ch->क्रमmat->fourcc;

	ret = sh_mobile_lcdc_check_var(var, info);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Backlight
 */

अटल पूर्णांक sh_mobile_lcdc_update_bl(काष्ठा backlight_device *bdev)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = bl_get_data(bdev);
	पूर्णांक brightness = bdev->props.brightness;

	अगर (bdev->props.घातer != FB_BLANK_UNBLANK ||
	    bdev->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	ch->bl_brightness = brightness;
	वापस ch->cfg->bl_info.set_brightness(brightness);
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_get_brightness(काष्ठा backlight_device *bdev)
अणु
	काष्ठा sh_mobile_lcdc_chan *ch = bl_get_data(bdev);

	वापस ch->bl_brightness;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_check_fb(काष्ठा backlight_device *bdev,
				   काष्ठा fb_info *info)
अणु
	वापस (info->bl_dev == bdev);
पूर्ण

अटल स्थिर काष्ठा backlight_ops sh_mobile_lcdc_bl_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= sh_mobile_lcdc_update_bl,
	.get_brightness	= sh_mobile_lcdc_get_brightness,
	.check_fb	= sh_mobile_lcdc_check_fb,
पूर्ण;

अटल काष्ठा backlight_device *sh_mobile_lcdc_bl_probe(काष्ठा device *parent,
					       काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	काष्ठा backlight_device *bl;

	bl = backlight_device_रेजिस्टर(ch->cfg->bl_info.name, parent, ch,
				       &sh_mobile_lcdc_bl_ops, शून्य);
	अगर (IS_ERR(bl)) अणु
		dev_err(parent, "unable to register backlight device: %ld\n",
			PTR_ERR(bl));
		वापस शून्य;
	पूर्ण

	bl->props.max_brightness = ch->cfg->bl_info.max_brightness;
	bl->props.brightness = bl->props.max_brightness;
	backlight_update_status(bl);

	वापस bl;
पूर्ण

अटल व्योम sh_mobile_lcdc_bl_हटाओ(काष्ठा backlight_device *bdev)
अणु
	backlight_device_unरेजिस्टर(bdev);
पूर्ण

/* -----------------------------------------------------------------------------
 * Power management
 */

अटल पूर्णांक sh_mobile_lcdc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	sh_mobile_lcdc_stop(platक्रमm_get_drvdata(pdev));
	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	वापस sh_mobile_lcdc_start(platक्रमm_get_drvdata(pdev));
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sh_mobile_lcdc_priv *priv = dev_get_drvdata(dev);

	/* turn off LCDC hardware */
	lcdc_ग_लिखो(priv, _LDCNT1R, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sh_mobile_lcdc_priv *priv = dev_get_drvdata(dev);

	__sh_mobile_lcdc_start(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sh_mobile_lcdc_dev_pm_ops = अणु
	.suspend = sh_mobile_lcdc_suspend,
	.resume = sh_mobile_lcdc_resume,
	.runसमय_suspend = sh_mobile_lcdc_runसमय_suspend,
	.runसमय_resume = sh_mobile_lcdc_runसमय_resume,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Framebuffer notअगरier
 */

/* -----------------------------------------------------------------------------
 * Probe/हटाओ and driver init/निकास
 */

अटल स्थिर काष्ठा fb_videomode शेष_720p = अणु
	.name = "HDMI 720p",
	.xres = 1280,
	.yres = 720,

	.left_margin = 220,
	.right_margin = 110,
	.hsync_len = 40,

	.upper_margin = 20,
	.lower_margin = 5,
	.vsync_len = 5,

	.pixघड़ी = 13468,
	.refresh = 60,
	.sync = FB_SYNC_VERT_HIGH_ACT | FB_SYNC_HOR_HIGH_ACT,
पूर्ण;

अटल पूर्णांक sh_mobile_lcdc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_mobile_lcdc_priv *priv = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->overlays); i++)
		sh_mobile_lcdc_overlay_fb_unरेजिस्टर(&priv->overlays[i]);
	क्रम (i = 0; i < ARRAY_SIZE(priv->ch); i++)
		sh_mobile_lcdc_channel_fb_unरेजिस्टर(&priv->ch[i]);

	sh_mobile_lcdc_stop(priv);

	क्रम (i = 0; i < ARRAY_SIZE(priv->overlays); i++) अणु
		काष्ठा sh_mobile_lcdc_overlay *ovl = &priv->overlays[i];

		sh_mobile_lcdc_overlay_fb_cleanup(ovl);

		अगर (ovl->fb_mem)
			dma_मुक्त_coherent(&pdev->dev, ovl->fb_size,
					  ovl->fb_mem, ovl->dma_handle);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(priv->ch); i++) अणु
		काष्ठा sh_mobile_lcdc_chan *ch = &priv->ch[i];

		अगर (ch->tx_dev) अणु
			ch->tx_dev->lcdc = शून्य;
			module_put(ch->cfg->tx_dev->dev.driver->owner);
		पूर्ण

		sh_mobile_lcdc_channel_fb_cleanup(ch);

		अगर (ch->fb_mem)
			dma_मुक्त_coherent(&pdev->dev, ch->fb_size,
					  ch->fb_mem, ch->dma_handle);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(priv->ch); i++) अणु
		काष्ठा sh_mobile_lcdc_chan *ch = &priv->ch[i];

		अगर (ch->bl)
			sh_mobile_lcdc_bl_हटाओ(ch->bl);
		mutex_destroy(&ch->खोलो_lock);
	पूर्ण

	अगर (priv->करोt_clk) अणु
		pm_runसमय_disable(&pdev->dev);
		clk_put(priv->करोt_clk);
	पूर्ण

	अगर (priv->base)
		iounmap(priv->base);

	अगर (priv->irq)
		मुक्त_irq(priv->irq, priv);
	kमुक्त(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_check_पूर्णांकerface(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	पूर्णांक पूर्णांकerface_type = ch->cfg->पूर्णांकerface_type;

	चयन (पूर्णांकerface_type) अणु
	हाल RGB8:
	हाल RGB9:
	हाल RGB12A:
	हाल RGB12B:
	हाल RGB16:
	हाल RGB18:
	हाल RGB24:
	हाल SYS8A:
	हाल SYS8B:
	हाल SYS8C:
	हाल SYS8D:
	हाल SYS9:
	हाल SYS12:
	हाल SYS16A:
	हाल SYS16B:
	हाल SYS16C:
	हाल SYS18:
	हाल SYS24:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* SUBLCD only supports SYS पूर्णांकerface */
	अगर (lcdc_chan_is_sublcd(ch)) अणु
		अगर (!(पूर्णांकerface_type & LDMT1R_IFM))
			वापस -EINVAL;

		पूर्णांकerface_type &= ~LDMT1R_IFM;
	पूर्ण

	ch->ldmt1r_value = पूर्णांकerface_type;
	वापस 0;
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_overlay_init(काष्ठा sh_mobile_lcdc_overlay *ovl)
अणु
	स्थिर काष्ठा sh_mobile_lcdc_क्रमmat_info *क्रमmat;
	काष्ठा device *dev = ovl->channel->lcdc->dev;
	पूर्णांक ret;

	अगर (ovl->cfg->fourcc == 0)
		वापस 0;

	/* Validate the क्रमmat. */
	क्रमmat = sh_mobile_क्रमmat_info(ovl->cfg->fourcc);
	अगर (क्रमmat == शून्य) अणु
		dev_err(dev, "Invalid FOURCC %08x\n", ovl->cfg->fourcc);
		वापस -EINVAL;
	पूर्ण

	ovl->enabled = false;
	ovl->mode = LCDC_OVERLAY_BLEND;
	ovl->alpha = 255;
	ovl->rop3 = 0;
	ovl->pos_x = 0;
	ovl->pos_y = 0;

	/* The शेष Y भव resolution is twice the panel size to allow क्रम
	 * द्विगुन-buffering.
	 */
	ovl->क्रमmat = क्रमmat;
	ovl->xres = ovl->cfg->max_xres;
	ovl->xres_भव = ovl->xres;
	ovl->yres = ovl->cfg->max_yres;
	ovl->yres_भव = ovl->yres * 2;

	अगर (!क्रमmat->yuv)
		ovl->pitch = ovl->xres_भव * क्रमmat->bpp / 8;
	अन्यथा
		ovl->pitch = ovl->xres_भव;

	/* Allocate frame buffer memory. */
	ovl->fb_size = ovl->cfg->max_xres * ovl->cfg->max_yres
		       * क्रमmat->bpp / 8 * 2;
	ovl->fb_mem = dma_alloc_coherent(dev, ovl->fb_size, &ovl->dma_handle,
					 GFP_KERNEL);
	अगर (!ovl->fb_mem) अणु
		dev_err(dev, "unable to allocate buffer\n");
		वापस -ENOMEM;
	पूर्ण

	ret = sh_mobile_lcdc_overlay_fb_init(ovl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
sh_mobile_lcdc_channel_init(काष्ठा sh_mobile_lcdc_chan *ch)
अणु
	स्थिर काष्ठा sh_mobile_lcdc_क्रमmat_info *क्रमmat;
	स्थिर काष्ठा sh_mobile_lcdc_chan_cfg *cfg = ch->cfg;
	काष्ठा device *dev = ch->lcdc->dev;
	स्थिर काष्ठा fb_videomode *max_mode;
	स्थिर काष्ठा fb_videomode *mode;
	अचिन्हित पूर्णांक num_modes;
	अचिन्हित पूर्णांक max_size;
	अचिन्हित पूर्णांक i;

	/* Validate the क्रमmat. */
	क्रमmat = sh_mobile_क्रमmat_info(cfg->fourcc);
	अगर (क्रमmat == शून्य) अणु
		dev_err(dev, "Invalid FOURCC %08x.\n", cfg->fourcc);
		वापस -EINVAL;
	पूर्ण

	/* Iterate through the modes to validate them and find the highest
	 * resolution.
	 */
	max_mode = शून्य;
	max_size = 0;

	क्रम (i = 0, mode = cfg->lcd_modes; i < cfg->num_modes; i++, mode++) अणु
		अचिन्हित पूर्णांक size = mode->yres * mode->xres;

		/* NV12/NV21 buffers must have even number of lines */
		अगर ((cfg->fourcc == V4L2_PIX_FMT_NV12 ||
		     cfg->fourcc == V4L2_PIX_FMT_NV21) && (mode->yres & 0x1)) अणु
			dev_err(dev, "yres must be multiple of 2 for "
				"YCbCr420 mode.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (size > max_size) अणु
			max_mode = mode;
			max_size = size;
		पूर्ण
	पूर्ण

	अगर (!max_size)
		max_size = MAX_XRES * MAX_YRES;
	अन्यथा
		dev_dbg(dev, "Found largest videomode %ux%u\n",
			max_mode->xres, max_mode->yres);

	अगर (cfg->lcd_modes == शून्य) अणु
		mode = &शेष_720p;
		num_modes = 1;
	पूर्ण अन्यथा अणु
		mode = cfg->lcd_modes;
		num_modes = cfg->num_modes;
	पूर्ण

	/* Use the first mode as शेष. The शेष Y भव resolution is
	 * twice the panel size to allow क्रम द्विगुन-buffering.
	 */
	ch->क्रमmat = क्रमmat;
	ch->xres = mode->xres;
	ch->xres_भव = mode->xres;
	ch->yres = mode->yres;
	ch->yres_भव = mode->yres * 2;

	अगर (!क्रमmat->yuv) अणु
		ch->colorspace = V4L2_COLORSPACE_SRGB;
		ch->pitch = ch->xres_भव * क्रमmat->bpp / 8;
	पूर्ण अन्यथा अणु
		ch->colorspace = V4L2_COLORSPACE_REC709;
		ch->pitch = ch->xres_भव;
	पूर्ण

	ch->display.width = cfg->panel_cfg.width;
	ch->display.height = cfg->panel_cfg.height;
	ch->display.mode = *mode;

	/* Allocate frame buffer memory. */
	ch->fb_size = max_size * क्रमmat->bpp / 8 * 2;
	ch->fb_mem = dma_alloc_coherent(dev, ch->fb_size, &ch->dma_handle,
					GFP_KERNEL);
	अगर (ch->fb_mem == शून्य) अणु
		dev_err(dev, "unable to allocate buffer\n");
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the transmitter device अगर present. */
	अगर (cfg->tx_dev) अणु
		अगर (!cfg->tx_dev->dev.driver ||
		    !try_module_get(cfg->tx_dev->dev.driver->owner)) अणु
			dev_warn(dev, "unable to get transmitter device\n");
			वापस -EINVAL;
		पूर्ण
		ch->tx_dev = platक्रमm_get_drvdata(cfg->tx_dev);
		ch->tx_dev->lcdc = ch;
		ch->tx_dev->def_mode = *mode;
	पूर्ण

	वापस sh_mobile_lcdc_channel_fb_init(ch, mode, num_modes);
पूर्ण

अटल पूर्णांक sh_mobile_lcdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_mobile_lcdc_info *pdata = pdev->dev.platक्रमm_data;
	काष्ठा sh_mobile_lcdc_priv *priv;
	काष्ठा resource *res;
	पूर्णांक num_channels;
	पूर्णांक error;
	पूर्णांक irq, i;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data defined\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!res || irq < 0) अणु
		dev_err(&pdev->dev, "cannot get platform resources\n");
		वापस -ENOENT;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;

	क्रम (i = 0; i < ARRAY_SIZE(priv->ch); i++)
		mutex_init(&priv->ch[i].खोलो_lock);
	platक्रमm_set_drvdata(pdev, priv);

	error = request_irq(irq, sh_mobile_lcdc_irq, 0,
			    dev_name(&pdev->dev), priv);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to request irq\n");
		जाओ err1;
	पूर्ण

	priv->irq = irq;
	atomic_set(&priv->hw_usecnt, -1);

	क्रम (i = 0, num_channels = 0; i < ARRAY_SIZE(pdata->ch); i++) अणु
		काष्ठा sh_mobile_lcdc_chan *ch = priv->ch + num_channels;

		ch->lcdc = priv;
		ch->cfg = &pdata->ch[i];

		error = sh_mobile_lcdc_check_पूर्णांकerface(ch);
		अगर (error) अणु
			dev_err(&pdev->dev, "unsupported interface type\n");
			जाओ err1;
		पूर्ण
		init_रुकोqueue_head(&ch->frame_end_रुको);
		init_completion(&ch->vsync_completion);

		/* probe the backlight is there is one defined */
		अगर (ch->cfg->bl_info.max_brightness)
			ch->bl = sh_mobile_lcdc_bl_probe(&pdev->dev, ch);

		चयन (pdata->ch[i].chan) अणु
		हाल LCDC_CHAN_MAINLCD:
			ch->enabled = LDCNT2R_ME;
			ch->reg_offs = lcdc_offs_मुख्यlcd;
			num_channels++;
			अवरोध;
		हाल LCDC_CHAN_SUBLCD:
			ch->enabled = LDCNT2R_SE;
			ch->reg_offs = lcdc_offs_sublcd;
			num_channels++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!num_channels) अणु
		dev_err(&pdev->dev, "no channels defined\n");
		error = -EINVAL;
		जाओ err1;
	पूर्ण

	/* क्रम dual channel LCDC (MAIN + SUB) क्रमce shared क्रमmat setting */
	अगर (num_channels == 2)
		priv->क्रमced_fourcc = pdata->ch[0].fourcc;

	priv->base = ioremap(res->start, resource_size(res));
	अगर (!priv->base) अणु
		error = -ENOMEM;
		जाओ err1;
	पूर्ण

	error = sh_mobile_lcdc_setup_घड़ीs(priv, pdata->घड़ी_source);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to setup clocks\n");
		जाओ err1;
	पूर्ण

	/* Enable runसमय PM. */
	pm_runसमय_enable(&pdev->dev);

	क्रम (i = 0; i < num_channels; i++) अणु
		काष्ठा sh_mobile_lcdc_chan *ch = &priv->ch[i];

		error = sh_mobile_lcdc_channel_init(ch);
		अगर (error)
			जाओ err1;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pdata->overlays); i++) अणु
		काष्ठा sh_mobile_lcdc_overlay *ovl = &priv->overlays[i];

		ovl->cfg = &pdata->overlays[i];
		ovl->channel = &priv->ch[0];

		error = sh_mobile_lcdc_overlay_init(ovl);
		अगर (error)
			जाओ err1;
	पूर्ण

	error = sh_mobile_lcdc_start(priv);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to start hardware\n");
		जाओ err1;
	पूर्ण

	क्रम (i = 0; i < num_channels; i++) अणु
		काष्ठा sh_mobile_lcdc_chan *ch = priv->ch + i;

		error = sh_mobile_lcdc_channel_fb_रेजिस्टर(ch);
		अगर (error)
			जाओ err1;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pdata->overlays); i++) अणु
		काष्ठा sh_mobile_lcdc_overlay *ovl = &priv->overlays[i];

		error = sh_mobile_lcdc_overlay_fb_रेजिस्टर(ovl);
		अगर (error)
			जाओ err1;
	पूर्ण

	वापस 0;
err1:
	sh_mobile_lcdc_हटाओ(pdev);

	वापस error;
पूर्ण

अटल काष्ठा platक्रमm_driver sh_mobile_lcdc_driver = अणु
	.driver		= अणु
		.name		= "sh_mobile_lcdc_fb",
		.pm		= &sh_mobile_lcdc_dev_pm_ops,
	पूर्ण,
	.probe		= sh_mobile_lcdc_probe,
	.हटाओ		= sh_mobile_lcdc_हटाओ,
पूर्ण;

module_platक्रमm_driver(sh_mobile_lcdc_driver);

MODULE_DESCRIPTION("SuperH Mobile LCDC Framebuffer driver");
MODULE_AUTHOR("Magnus Damm <damm@opensource.se>");
MODULE_LICENSE("GPL v2");
