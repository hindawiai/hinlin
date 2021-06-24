<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MB862XX_H__
#घोषणा __MB862XX_H__

काष्ठा mb862xx_l1_cfg अणु
	अचिन्हित लघु sx;
	अचिन्हित लघु sy;
	अचिन्हित लघु sw;
	अचिन्हित लघु sh;
	अचिन्हित लघु dx;
	अचिन्हित लघु dy;
	अचिन्हित लघु dw;
	अचिन्हित लघु dh;
	पूर्णांक mirror;
पूर्ण;

#घोषणा MB862XX_BASE		'M'
#घोषणा MB862XX_L1_GET_CFG	_IOR(MB862XX_BASE, 0, काष्ठा mb862xx_l1_cfg*)
#घोषणा MB862XX_L1_SET_CFG	_IOW(MB862XX_BASE, 1, काष्ठा mb862xx_l1_cfg*)
#घोषणा MB862XX_L1_ENABLE	_IOW(MB862XX_BASE, 2, पूर्णांक)
#घोषणा MB862XX_L1_CAP_CTL	_IOW(MB862XX_BASE, 3, पूर्णांक)

#अगर_घोषित __KERNEL__

#घोषणा PCI_VENDOR_ID_FUJITSU_LIMITED	0x10cf
#घोषणा PCI_DEVICE_ID_FUJITSU_CORALP	0x2019
#घोषणा PCI_DEVICE_ID_FUJITSU_CORALPA	0x201e
#घोषणा PCI_DEVICE_ID_FUJITSU_CARMINE	0x202b

#घोषणा GC_MMR_CORALP_EVB_VAL		0x11d7fa13

क्रमागत gdctype अणु
	BT_NONE,
	BT_LIME,
	BT_MINT,
	BT_CORAL,
	BT_CORALP,
	BT_CARMINE,
पूर्ण;

काष्ठा mb862xx_gc_mode अणु
	काष्ठा fb_videomode	def_mode;	/* mode of connected display */
	अचिन्हित पूर्णांक		def_bpp;	/* शेष depth */
	अचिन्हित दीर्घ		max_vram;	/* connected SDRAM size */
	अचिन्हित दीर्घ		ccf;		/* gdc clk */
	अचिन्हित दीर्घ		mmr;		/* memory mode क्रम SDRAM */
पूर्ण;

/* निजी data */
काष्ठा mb862xxfb_par अणु
	काष्ठा fb_info		*info;		/* fb info head */
	काष्ठा device		*dev;
	काष्ठा pci_dev		*pdev;
	काष्ठा resource		*res;		/* framebuffer/mmio resource */

	resource_माप_प्रकार		fb_base_phys;	/* fb base, 36-bit PPC440EPx */
	resource_माप_प्रकार		mmio_base_phys;	/* io base addr */
	व्योम __iomem		*fb_base;	/* remapped framebuffer */
	व्योम __iomem		*mmio_base;	/* remapped रेजिस्टरs */
	माप_प्रकार			mapped_vram;	/* length of remapped vram */
	माप_प्रकार			mmio_len;	/* length of रेजिस्टर region */
	अचिन्हित दीर्घ		cap_buf;	/* capture buffers offset */
	माप_प्रकार			cap_len;	/* length of capture buffers */

	व्योम __iomem		*host;		/* relocatable reg. bases */
	व्योम __iomem		*i2c;
	व्योम __iomem		*disp;
	व्योम __iomem		*disp1;
	व्योम __iomem		*cap;
	व्योम __iomem		*cap1;
	व्योम __iomem		*draw;
	व्योम __iomem		*geo;
	व्योम __iomem		*pio;
	व्योम __iomem		*ctrl;
	व्योम __iomem		*dram_ctrl;
	व्योम __iomem		*wrback;

	अचिन्हित पूर्णांक		irq;
	अचिन्हित पूर्णांक		type;		/* GDC type */
	अचिन्हित पूर्णांक		refclk;		/* disp. reference घड़ी */
	काष्ठा mb862xx_gc_mode	*gc_mode;	/* GDC mode init data */
	पूर्णांक			pre_init;	/* करोn't init display अगर 1 */
	काष्ठा i2c_adapter	*adap;		/* GDC I2C bus adapter */
	पूर्णांक			i2c_rs;

	काष्ठा mb862xx_l1_cfg	l1_cfg;
	पूर्णांक			l1_stride;

	u32			pseuकरो_palette[16];
पूर्ण;

बाह्य व्योम mb862xxfb_init_accel(काष्ठा fb_info *info, काष्ठा fb_ops *fbops, पूर्णांक xres);
#अगर_घोषित CONFIG_FB_MB862XX_I2C
बाह्य पूर्णांक mb862xx_i2c_init(काष्ठा mb862xxfb_par *par);
बाह्य व्योम mb862xx_i2c_निकास(काष्ठा mb862xxfb_par *par);
#अन्यथा
अटल अंतरभूत पूर्णांक mb862xx_i2c_init(काष्ठा mb862xxfb_par *par) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mb862xx_i2c_निकास(काष्ठा mb862xxfb_par *par) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FB_MB862XX_LIME) && defined(CONFIG_FB_MB862XX_PCI_GDC)
#त्रुटि	"Select Lime GDC or CoralP/Carmine support, but not both together"
#पूर्ण_अगर
#अगर defined(CONFIG_FB_MB862XX_LIME)
#घोषणा gdc_पढ़ो	__raw_पढ़ोl
#घोषणा gdc_ग_लिखो	__raw_ग_लिखोl
#अन्यथा
#घोषणा gdc_पढ़ो	पढ़ोl
#घोषणा gdc_ग_लिखो	ग_लिखोl
#पूर्ण_अगर

#घोषणा inreg(type, off)	\
	gdc_पढ़ो((par->type + (off)))

#घोषणा outreg(type, off, val)	\
	gdc_ग_लिखो((val), (par->type + (off)))

#घोषणा pack(a, b)	(((a) << 16) | (b))

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर
