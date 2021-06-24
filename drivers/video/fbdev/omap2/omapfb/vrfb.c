<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VRFB Rotation Engine
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 */

/*#घोषणा DEBUG*/

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/omapvrfb.h>

#अगर_घोषित DEBUG
#घोषणा DBG(क्रमmat, ...) pr_debug("VRFB: " क्रमmat, ## __VA_ARGS__)
#अन्यथा
#घोषणा DBG(क्रमmat, ...)
#पूर्ण_अगर

#घोषणा SMS_ROT_CONTROL(context)	(0x0 + 0x10 * context)
#घोषणा SMS_ROT_SIZE(context)		(0x4 + 0x10 * context)
#घोषणा SMS_ROT_PHYSICAL_BA(context)	(0x8 + 0x10 * context)
#घोषणा SMS_ROT_VIRT_BASE(rot)		(0x1000000 * (rot))

#घोषणा OMAP_VRFB_SIZE			(2048 * 2048 * 4)

#घोषणा VRFB_PAGE_WIDTH_EXP	5 /* Assuming SDRAM pagesize= 1024 */
#घोषणा VRFB_PAGE_HEIGHT_EXP	5 /* 1024 = 2^5 * 2^5 */
#घोषणा VRFB_PAGE_WIDTH		(1 << VRFB_PAGE_WIDTH_EXP)
#घोषणा VRFB_PAGE_HEIGHT	(1 << VRFB_PAGE_HEIGHT_EXP)
#घोषणा SMS_IMAGEHEIGHT_OFFSET	16
#घोषणा SMS_IMAGEWIDTH_OFFSET	0
#घोषणा SMS_PH_OFFSET		8
#घोषणा SMS_PW_OFFSET		4
#घोषणा SMS_PS_OFFSET		0

/* biपंचांगap of reserved contexts */
अटल अचिन्हित दीर्घ ctx_map;

काष्ठा vrfb_ctx अणु
	u32 base;
	u32 physical_ba;
	u32 control;
	u32 size;
पूर्ण;

अटल DEFINE_MUTEX(ctx_lock);

/*
 * Access to this happens from client drivers or the PM core after wake-up.
 * For the first हाल we require locking at the driver level, क्रम the second
 * we करोn't need locking, since no drivers will run until after the wake-up
 * has finished.
 */

अटल व्योम __iomem *vrfb_base;

अटल पूर्णांक num_ctxs;
अटल काष्ठा vrfb_ctx *ctxs;

अटल bool vrfb_loaded;

अटल व्योम omap2_sms_ग_लिखो_rot_control(u32 val, अचिन्हित ctx)
अणु
	__raw_ग_लिखोl(val, vrfb_base + SMS_ROT_CONTROL(ctx));
पूर्ण

अटल व्योम omap2_sms_ग_लिखो_rot_size(u32 val, अचिन्हित ctx)
अणु
	__raw_ग_लिखोl(val, vrfb_base + SMS_ROT_SIZE(ctx));
पूर्ण

अटल व्योम omap2_sms_ग_लिखो_rot_physical_ba(u32 val, अचिन्हित ctx)
अणु
	__raw_ग_लिखोl(val, vrfb_base + SMS_ROT_PHYSICAL_BA(ctx));
पूर्ण

अटल अंतरभूत व्योम restore_hw_context(पूर्णांक ctx)
अणु
	omap2_sms_ग_लिखो_rot_control(ctxs[ctx].control, ctx);
	omap2_sms_ग_लिखो_rot_size(ctxs[ctx].size, ctx);
	omap2_sms_ग_लिखो_rot_physical_ba(ctxs[ctx].physical_ba, ctx);
पूर्ण

अटल u32 get_image_width_roundup(u16 width, u8 bytespp)
अणु
	अचिन्हित दीर्घ stride = width * bytespp;
	अचिन्हित दीर्घ उच्चमान_pages_per_stride = (stride / VRFB_PAGE_WIDTH) +
		(stride % VRFB_PAGE_WIDTH != 0);

	वापस उच्चमान_pages_per_stride * VRFB_PAGE_WIDTH / bytespp;
पूर्ण

/*
 * This the extra space needed in the VRFB physical area क्रम VRFB to safely wrap
 * any memory accesses to the invisible part of the भव view to the physical
 * area.
 */
अटल अंतरभूत u32 get_extra_physical_size(u16 image_width_roundup, u8 bytespp)
अणु
	वापस (OMAP_VRFB_LINE_LEN - image_width_roundup) * VRFB_PAGE_HEIGHT *
		bytespp;
पूर्ण

व्योम omap_vrfb_restore_context(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ map = ctx_map;

	क्रम (i = ffs(map); i; i = ffs(map)) अणु
		/* i=1..32 */
		i--;
		map &= ~(1 << i);
		restore_hw_context(i);
	पूर्ण
पूर्ण

व्योम omap_vrfb_adjust_size(u16 *width, u16 *height,
		u8 bytespp)
अणु
	*width = ALIGN(*width * bytespp, VRFB_PAGE_WIDTH) / bytespp;
	*height = ALIGN(*height, VRFB_PAGE_HEIGHT);
पूर्ण
EXPORT_SYMBOL(omap_vrfb_adjust_size);

u32 omap_vrfb_min_phys_size(u16 width, u16 height, u8 bytespp)
अणु
	अचिन्हित दीर्घ image_width_roundup = get_image_width_roundup(width,
		bytespp);

	अगर (image_width_roundup > OMAP_VRFB_LINE_LEN)
		वापस 0;

	वापस (width * height * bytespp) + get_extra_physical_size(
		image_width_roundup, bytespp);
पूर्ण
EXPORT_SYMBOL(omap_vrfb_min_phys_size);

u16 omap_vrfb_max_height(u32 phys_size, u16 width, u8 bytespp)
अणु
	अचिन्हित दीर्घ image_width_roundup = get_image_width_roundup(width,
		bytespp);
	अचिन्हित दीर्घ height;
	अचिन्हित दीर्घ extra;

	अगर (image_width_roundup > OMAP_VRFB_LINE_LEN)
		वापस 0;

	extra = get_extra_physical_size(image_width_roundup, bytespp);

	अगर (phys_size < extra)
		वापस 0;

	height = (phys_size - extra) / (width * bytespp);

	/* Virtual views provided by VRFB are limited to 2048x2048. */
	वापस min_t(अचिन्हित दीर्घ, height, 2048);
पूर्ण
EXPORT_SYMBOL(omap_vrfb_max_height);

व्योम omap_vrfb_setup(काष्ठा vrfb *vrfb, अचिन्हित दीर्घ paddr,
		u16 width, u16 height,
		अचिन्हित bytespp, bool yuv_mode)
अणु
	अचिन्हित pixel_size_exp;
	u16 vrfb_width;
	u16 vrfb_height;
	u8 ctx = vrfb->context;
	u32 size;
	u32 control;

	DBG("omapfb_set_vrfb(%d, %lx, %dx%d, %d, %d)\n", ctx, paddr,
			width, height, bytespp, yuv_mode);

	/* For YUV2 and UYVY modes VRFB needs to handle pixels a bit
	 * dअगरferently. See TRM. */
	अगर (yuv_mode) अणु
		bytespp *= 2;
		width /= 2;
	पूर्ण

	अगर (bytespp == 4)
		pixel_size_exp = 2;
	अन्यथा अगर (bytespp == 2)
		pixel_size_exp = 1;
	अन्यथा अणु
		BUG();
		वापस;
	पूर्ण

	vrfb_width = ALIGN(width * bytespp, VRFB_PAGE_WIDTH) / bytespp;
	vrfb_height = ALIGN(height, VRFB_PAGE_HEIGHT);

	DBG("vrfb w %u, h %u bytespp %d\n", vrfb_width, vrfb_height, bytespp);

	size  = vrfb_width << SMS_IMAGEWIDTH_OFFSET;
	size |= vrfb_height << SMS_IMAGEHEIGHT_OFFSET;

	control  = pixel_size_exp << SMS_PS_OFFSET;
	control |= VRFB_PAGE_WIDTH_EXP  << SMS_PW_OFFSET;
	control |= VRFB_PAGE_HEIGHT_EXP << SMS_PH_OFFSET;

	ctxs[ctx].physical_ba = paddr;
	ctxs[ctx].size = size;
	ctxs[ctx].control = control;

	omap2_sms_ग_लिखो_rot_physical_ba(paddr, ctx);
	omap2_sms_ग_लिखो_rot_size(size, ctx);
	omap2_sms_ग_लिखो_rot_control(control, ctx);

	DBG("vrfb offset pixels %d, %d\n",
			vrfb_width - width, vrfb_height - height);

	vrfb->xres = width;
	vrfb->yres = height;
	vrfb->xoffset = vrfb_width - width;
	vrfb->yoffset = vrfb_height - height;
	vrfb->bytespp = bytespp;
	vrfb->yuv_mode = yuv_mode;
पूर्ण
EXPORT_SYMBOL(omap_vrfb_setup);

पूर्णांक omap_vrfb_map_angle(काष्ठा vrfb *vrfb, u16 height, u8 rot)
अणु
	अचिन्हित दीर्घ size = height * OMAP_VRFB_LINE_LEN * vrfb->bytespp;

	vrfb->vaddr[rot] = ioremap_wc(vrfb->paddr[rot], size);

	अगर (!vrfb->vaddr[rot]) अणु
		prपूर्णांकk(KERN_ERR "vrfb: ioremap failed\n");
		वापस -ENOMEM;
	पूर्ण

	DBG("ioremapped vrfb area %d of size %lu into %p\n", rot, size,
		vrfb->vaddr[rot]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(omap_vrfb_map_angle);

व्योम omap_vrfb_release_ctx(काष्ठा vrfb *vrfb)
अणु
	पूर्णांक rot;
	पूर्णांक ctx = vrfb->context;

	अगर (ctx == 0xff)
		वापस;

	DBG("release ctx %d\n", ctx);

	mutex_lock(&ctx_lock);

	BUG_ON(!(ctx_map & (1 << ctx)));

	clear_bit(ctx, &ctx_map);

	क्रम (rot = 0; rot < 4; ++rot) अणु
		अगर (vrfb->paddr[rot]) अणु
			release_mem_region(vrfb->paddr[rot], OMAP_VRFB_SIZE);
			vrfb->paddr[rot] = 0;
		पूर्ण
	पूर्ण

	vrfb->context = 0xff;

	mutex_unlock(&ctx_lock);
पूर्ण
EXPORT_SYMBOL(omap_vrfb_release_ctx);

पूर्णांक omap_vrfb_request_ctx(काष्ठा vrfb *vrfb)
अणु
	पूर्णांक rot;
	u32 paddr;
	u8 ctx;
	पूर्णांक r;

	DBG("request ctx\n");

	mutex_lock(&ctx_lock);

	क्रम (ctx = 0; ctx < num_ctxs; ++ctx)
		अगर ((ctx_map & (1 << ctx)) == 0)
			अवरोध;

	अगर (ctx == num_ctxs) अणु
		pr_err("vrfb: no free contexts\n");
		r = -EBUSY;
		जाओ out;
	पूर्ण

	DBG("found free ctx %d\n", ctx);

	set_bit(ctx, &ctx_map);

	स_रखो(vrfb, 0, माप(*vrfb));

	vrfb->context = ctx;

	क्रम (rot = 0; rot < 4; ++rot) अणु
		paddr = ctxs[ctx].base + SMS_ROT_VIRT_BASE(rot);
		अगर (!request_mem_region(paddr, OMAP_VRFB_SIZE, "vrfb")) अणु
			pr_err("vrfb: failed to reserve VRFB "
					"area for ctx %d, rotation %d\n",
					ctx, rot * 90);
			omap_vrfb_release_ctx(vrfb);
			r = -ENOMEM;
			जाओ out;
		पूर्ण

		vrfb->paddr[rot] = paddr;

		DBG("VRFB %d/%d: %lx\n", ctx, rot*90, vrfb->paddr[rot]);
	पूर्ण

	r = 0;
out:
	mutex_unlock(&ctx_lock);
	वापस r;
पूर्ण
EXPORT_SYMBOL(omap_vrfb_request_ctx);

bool omap_vrfb_supported(व्योम)
अणु
	वापस vrfb_loaded;
पूर्ण
EXPORT_SYMBOL(omap_vrfb_supported);

अटल पूर्णांक __init vrfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mem;
	पूर्णांक i;

	/* first resource is the रेजिस्टर res, the rest are vrfb contexts */
	vrfb_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(vrfb_base))
		वापस PTR_ERR(vrfb_base);

	num_ctxs = pdev->num_resources - 1;

	ctxs = devm_kसुस्मृति(&pdev->dev,
			num_ctxs, माप(काष्ठा vrfb_ctx),
			GFP_KERNEL);

	अगर (!ctxs)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_ctxs; ++i) अणु
		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1 + i);
		अगर (!mem) अणु
			dev_err(&pdev->dev, "can't get vrfb ctx %d address\n",
					i);
			वापस -EINVAL;
		पूर्ण

		ctxs[i].base = mem->start;
	पूर्ण

	vrfb_loaded = true;

	वापस 0;
पूर्ण

अटल व्योम __निकास vrfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	vrfb_loaded = false;
पूर्ण

अटल काष्ठा platक्रमm_driver vrfb_driver = अणु
	.driver.name	= "omapvrfb",
	.हटाओ		= __निकास_p(vrfb_हटाओ),
पूर्ण;

module_platक्रमm_driver_probe(vrfb_driver, vrfb_probe);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("OMAP VRFB");
MODULE_LICENSE("GPL v2");
