<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ispccdc.c
 *
 * TI OMAP3 ISP - CCDC module
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-event.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "ispccdc.h"

#घोषणा CCDC_MIN_WIDTH		32
#घोषणा CCDC_MIN_HEIGHT		32

अटल काष्ठा v4l2_mbus_framefmt *
__ccdc_get_क्रमmat(काष्ठा isp_ccdc_device *ccdc, काष्ठा v4l2_subdev_pad_config *cfg,
		  अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which);

अटल स्थिर अचिन्हित पूर्णांक ccdc_fmts[] = अणु
	MEDIA_BUS_FMT_Y8_1X8,
	MEDIA_BUS_FMT_Y10_1X10,
	MEDIA_BUS_FMT_Y12_1X12,
	MEDIA_BUS_FMT_SGRBG8_1X8,
	MEDIA_BUS_FMT_SRGGB8_1X8,
	MEDIA_BUS_FMT_SBGGR8_1X8,
	MEDIA_BUS_FMT_SGBRG8_1X8,
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_SGRBG12_1X12,
	MEDIA_BUS_FMT_SRGGB12_1X12,
	MEDIA_BUS_FMT_SBGGR12_1X12,
	MEDIA_BUS_FMT_SGBRG12_1X12,
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_UYVY8_2X8,
पूर्ण;

/*
 * ccdc_prपूर्णांक_status - Prपूर्णांक current CCDC Module रेजिस्टर values.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 *
 * Also prपूर्णांकs other debug inक्रमmation stored in the CCDC module.
 */
#घोषणा CCDC_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###CCDC " #name "=0x%08x\n", \
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_##name))

अटल व्योम ccdc_prपूर्णांक_status(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	dev_dbg(isp->dev, "-------------CCDC Register dump-------------\n");

	CCDC_PRINT_REGISTER(isp, PCR);
	CCDC_PRINT_REGISTER(isp, SYN_MODE);
	CCDC_PRINT_REGISTER(isp, HD_VD_WID);
	CCDC_PRINT_REGISTER(isp, PIX_LINES);
	CCDC_PRINT_REGISTER(isp, HORZ_INFO);
	CCDC_PRINT_REGISTER(isp, VERT_START);
	CCDC_PRINT_REGISTER(isp, VERT_LINES);
	CCDC_PRINT_REGISTER(isp, CULLING);
	CCDC_PRINT_REGISTER(isp, HSIZE_OFF);
	CCDC_PRINT_REGISTER(isp, SDOFST);
	CCDC_PRINT_REGISTER(isp, SDR_ADDR);
	CCDC_PRINT_REGISTER(isp, CLAMP);
	CCDC_PRINT_REGISTER(isp, DCSUB);
	CCDC_PRINT_REGISTER(isp, COLPTN);
	CCDC_PRINT_REGISTER(isp, BLKCMP);
	CCDC_PRINT_REGISTER(isp, FPC);
	CCDC_PRINT_REGISTER(isp, FPC_ADDR);
	CCDC_PRINT_REGISTER(isp, VDINT);
	CCDC_PRINT_REGISTER(isp, ALAW);
	CCDC_PRINT_REGISTER(isp, REC656IF);
	CCDC_PRINT_REGISTER(isp, CFG);
	CCDC_PRINT_REGISTER(isp, FMTCFG);
	CCDC_PRINT_REGISTER(isp, FMT_HORZ);
	CCDC_PRINT_REGISTER(isp, FMT_VERT);
	CCDC_PRINT_REGISTER(isp, PRGEVEN0);
	CCDC_PRINT_REGISTER(isp, PRGEVEN1);
	CCDC_PRINT_REGISTER(isp, PRGODD0);
	CCDC_PRINT_REGISTER(isp, PRGODD1);
	CCDC_PRINT_REGISTER(isp, VP_OUT);
	CCDC_PRINT_REGISTER(isp, LSC_CONFIG);
	CCDC_PRINT_REGISTER(isp, LSC_INITIAL);
	CCDC_PRINT_REGISTER(isp, LSC_TABLE_BASE);
	CCDC_PRINT_REGISTER(isp, LSC_TABLE_OFFSET);

	dev_dbg(isp->dev, "--------------------------------------------\n");
पूर्ण

/*
 * omap3isp_ccdc_busy - Get busy state of the CCDC.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
पूर्णांक omap3isp_ccdc_busy(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	वापस isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_PCR) &
		ISPCCDC_PCR_BUSY;
पूर्ण

/* -----------------------------------------------------------------------------
 * Lens Shading Compensation
 */

/*
 * ccdc_lsc_validate_config - Check that LSC configuration is valid.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @lsc_cfg: the LSC configuration to check.
 *
 * Returns 0 अगर the LSC configuration is valid, or -EINVAL अगर invalid.
 */
अटल पूर्णांक ccdc_lsc_validate_config(काष्ठा isp_ccdc_device *ccdc,
				    काष्ठा omap3isp_ccdc_lsc_config *lsc_cfg)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक paxel_width, paxel_height;
	अचिन्हित पूर्णांक paxel_shअगरt_x, paxel_shअगरt_y;
	अचिन्हित पूर्णांक min_width, min_height, min_size;
	अचिन्हित पूर्णांक input_width, input_height;

	paxel_shअगरt_x = lsc_cfg->gain_mode_m;
	paxel_shअगरt_y = lsc_cfg->gain_mode_n;

	अगर ((paxel_shअगरt_x < 2) || (paxel_shअगरt_x > 6) ||
	    (paxel_shअगरt_y < 2) || (paxel_shअगरt_y > 6)) अणु
		dev_dbg(isp->dev, "CCDC: LSC: Invalid paxel size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (lsc_cfg->offset & 3) अणु
		dev_dbg(isp->dev,
			"CCDC: LSC: Offset must be a multiple of 4\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((lsc_cfg->initial_x & 1) || (lsc_cfg->initial_y & 1)) अणु
		dev_dbg(isp->dev, "CCDC: LSC: initial_x and y must be even\n");
		वापस -EINVAL;
	पूर्ण

	क्रमmat = __ccdc_get_क्रमmat(ccdc, शून्य, CCDC_PAD_SINK,
				   V4L2_SUBDEV_FORMAT_ACTIVE);
	input_width = क्रमmat->width;
	input_height = क्रमmat->height;

	/* Calculate minimum bytesize क्रम validation */
	paxel_width = 1 << paxel_shअगरt_x;
	min_width = ((input_width + lsc_cfg->initial_x + paxel_width - 1)
		     >> paxel_shअगरt_x) + 1;

	paxel_height = 1 << paxel_shअगरt_y;
	min_height = ((input_height + lsc_cfg->initial_y + paxel_height - 1)
		     >> paxel_shअगरt_y) + 1;

	min_size = 4 * min_width * min_height;
	अगर (min_size > lsc_cfg->size) अणु
		dev_dbg(isp->dev, "CCDC: LSC: too small table\n");
		वापस -EINVAL;
	पूर्ण
	अगर (lsc_cfg->offset < (min_width * 4)) अणु
		dev_dbg(isp->dev, "CCDC: LSC: Offset is too small\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((lsc_cfg->size / lsc_cfg->offset) < min_height) अणु
		dev_dbg(isp->dev, "CCDC: LSC: Wrong size/offset combination\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ccdc_lsc_program_table - Program Lens Shading Compensation table address.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_lsc_program_table(काष्ठा isp_ccdc_device *ccdc,
				   dma_addr_t addr)
अणु
	isp_reg_ग_लिखोl(to_isp_device(ccdc), addr,
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_LSC_TABLE_BASE);
पूर्ण

/*
 * ccdc_lsc_setup_regs - Configures the lens shading compensation module
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_lsc_setup_regs(काष्ठा isp_ccdc_device *ccdc,
				काष्ठा omap3isp_ccdc_lsc_config *cfg)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	पूर्णांक reg;

	isp_reg_ग_लिखोl(isp, cfg->offset, OMAP3_ISP_IOMEM_CCDC,
		       ISPCCDC_LSC_TABLE_OFFSET);

	reg = 0;
	reg |= cfg->gain_mode_n << ISPCCDC_LSC_GAIN_MODE_N_SHIFT;
	reg |= cfg->gain_mode_m << ISPCCDC_LSC_GAIN_MODE_M_SHIFT;
	reg |= cfg->gain_क्रमmat << ISPCCDC_LSC_GAIN_FORMAT_SHIFT;
	isp_reg_ग_लिखोl(isp, reg, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_LSC_CONFIG);

	reg = 0;
	reg &= ~ISPCCDC_LSC_INITIAL_X_MASK;
	reg |= cfg->initial_x << ISPCCDC_LSC_INITIAL_X_SHIFT;
	reg &= ~ISPCCDC_LSC_INITIAL_Y_MASK;
	reg |= cfg->initial_y << ISPCCDC_LSC_INITIAL_Y_SHIFT;
	isp_reg_ग_लिखोl(isp, reg, OMAP3_ISP_IOMEM_CCDC,
		       ISPCCDC_LSC_INITIAL);
पूर्ण

अटल पूर्णांक ccdc_lsc_रुको_prefetch(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	अचिन्हित पूर्णांक रुको;

	isp_reg_ग_लिखोl(isp, IRQ0STATUS_CCDC_LSC_PREF_COMP_IRQ,
		       OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0STATUS);

	/* समयout 1 ms */
	क्रम (रुको = 0; रुको < 1000; रुको++) अणु
		अगर (isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0STATUS) &
				  IRQ0STATUS_CCDC_LSC_PREF_COMP_IRQ) अणु
			isp_reg_ग_लिखोl(isp, IRQ0STATUS_CCDC_LSC_PREF_COMP_IRQ,
				       OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0STATUS);
			वापस 0;
		पूर्ण

		rmb();
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/*
 * __ccdc_lsc_enable - Enables/Disables the Lens Shading Compensation module.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @enable: 0 Disables LSC, 1 Enables LSC.
 */
अटल पूर्णांक __ccdc_lsc_enable(काष्ठा isp_ccdc_device *ccdc, पूर्णांक enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat =
		__ccdc_get_क्रमmat(ccdc, शून्य, CCDC_PAD_SINK,
				  V4L2_SUBDEV_FORMAT_ACTIVE);

	अगर ((क्रमmat->code != MEDIA_BUS_FMT_SGRBG10_1X10) &&
	    (क्रमmat->code != MEDIA_BUS_FMT_SRGGB10_1X10) &&
	    (क्रमmat->code != MEDIA_BUS_FMT_SBGGR10_1X10) &&
	    (क्रमmat->code != MEDIA_BUS_FMT_SGBRG10_1X10))
		वापस -EINVAL;

	अगर (enable)
		omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CCDC_LSC_READ);

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_LSC_CONFIG,
			ISPCCDC_LSC_ENABLE, enable ? ISPCCDC_LSC_ENABLE : 0);

	अगर (enable) अणु
		अगर (ccdc_lsc_रुको_prefetch(ccdc) < 0) अणु
			isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC,
				    ISPCCDC_LSC_CONFIG, ISPCCDC_LSC_ENABLE);
			ccdc->lsc.state = LSC_STATE_STOPPED;
			dev_warn(to_device(ccdc), "LSC prefetch timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
		ccdc->lsc.state = LSC_STATE_RUNNING;
	पूर्ण अन्यथा अणु
		ccdc->lsc.state = LSC_STATE_STOPPING;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccdc_lsc_busy(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	वापस isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_LSC_CONFIG) &
			     ISPCCDC_LSC_BUSY;
पूर्ण

/*
 * __ccdc_lsc_configure - Apply a new configuration to the LSC engine
 * @ccdc: Poपूर्णांकer to ISP CCDC device
 * @req: New configuration request
 */
अटल पूर्णांक __ccdc_lsc_configure(काष्ठा isp_ccdc_device *ccdc,
				काष्ठा ispccdc_lsc_config_req *req)
अणु
	अगर (!req->enable)
		वापस -EINVAL;

	अगर (ccdc_lsc_validate_config(ccdc, &req->config) < 0) अणु
		dev_dbg(to_device(ccdc), "Discard LSC configuration\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ccdc_lsc_busy(ccdc))
		वापस -EBUSY;

	ccdc_lsc_setup_regs(ccdc, &req->config);
	ccdc_lsc_program_table(ccdc, req->table.dma);
	वापस 0;
पूर्ण

/*
 * ccdc_lsc_error_handler - Handle LSC prefetch error scenario.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 *
 * Disables LSC, and defers enablement to shaकरोw रेजिस्टरs update समय.
 */
अटल व्योम ccdc_lsc_error_handler(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	/*
	 * From OMAP3 TRM: When this event is pending, the module
	 * goes पूर्णांकo transparent mode (output =input). Normal
	 * operation can be resumed at the start of the next frame
	 * after:
	 *  1) Clearing this event
	 *  2) Disabling the LSC module
	 *  3) Enabling it
	 */
	isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_LSC_CONFIG,
		    ISPCCDC_LSC_ENABLE);
	ccdc->lsc.state = LSC_STATE_STOPPED;
पूर्ण

अटल व्योम ccdc_lsc_मुक्त_request(काष्ठा isp_ccdc_device *ccdc,
				  काष्ठा ispccdc_lsc_config_req *req)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	अगर (req == शून्य)
		वापस;

	अगर (req->table.addr) अणु
		sg_मुक्त_table(&req->table.sgt);
		dma_मुक्त_coherent(isp->dev, req->config.size, req->table.addr,
				  req->table.dma);
	पूर्ण

	kमुक्त(req);
पूर्ण

अटल व्योम ccdc_lsc_मुक्त_queue(काष्ठा isp_ccdc_device *ccdc,
				काष्ठा list_head *queue)
अणु
	काष्ठा ispccdc_lsc_config_req *req, *n;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);
	list_क्रम_each_entry_safe(req, n, queue, list) अणु
		list_del(&req->list);
		spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);
		ccdc_lsc_मुक्त_request(ccdc, req);
		spin_lock_irqsave(&ccdc->lsc.req_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);
पूर्ण

अटल व्योम ccdc_lsc_मुक्त_table_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा isp_ccdc_device *ccdc;
	काष्ठा ispccdc_lsc *lsc;

	lsc = container_of(work, काष्ठा ispccdc_lsc, table_work);
	ccdc = container_of(lsc, काष्ठा isp_ccdc_device, lsc);

	ccdc_lsc_मुक्त_queue(ccdc, &lsc->मुक्त_queue);
पूर्ण

/*
 * ccdc_lsc_config - Configure the LSC module from a userspace request
 *
 * Store the request LSC configuration in the LSC engine request poपूर्णांकer. The
 * configuration will be applied to the hardware when the CCDC will be enabled,
 * or at the next LSC पूर्णांकerrupt अगर the CCDC is alपढ़ोy running.
 */
अटल पूर्णांक ccdc_lsc_config(काष्ठा isp_ccdc_device *ccdc,
			   काष्ठा omap3isp_ccdc_update_config *config)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	काष्ठा ispccdc_lsc_config_req *req;
	अचिन्हित दीर्घ flags;
	u16 update;
	पूर्णांक ret;

	update = config->update &
		 (OMAP3ISP_CCDC_CONFIG_LSC | OMAP3ISP_CCDC_TBL_LSC);
	अगर (!update)
		वापस 0;

	अगर (update != (OMAP3ISP_CCDC_CONFIG_LSC | OMAP3ISP_CCDC_TBL_LSC)) अणु
		dev_dbg(to_device(ccdc),
			"%s: Both LSC configuration and table need to be supplied\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (req == शून्य)
		वापस -ENOMEM;

	अगर (config->flag & OMAP3ISP_CCDC_CONFIG_LSC) अणु
		अगर (copy_from_user(&req->config, config->lsc_cfg,
				   माप(req->config))) अणु
			ret = -EFAULT;
			जाओ करोne;
		पूर्ण

		req->enable = 1;

		req->table.addr = dma_alloc_coherent(isp->dev, req->config.size,
						     &req->table.dma,
						     GFP_KERNEL);
		अगर (req->table.addr == शून्य) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण

		ret = dma_get_sgtable(isp->dev, &req->table.sgt,
				      req->table.addr, req->table.dma,
				      req->config.size);
		अगर (ret < 0)
			जाओ करोne;

		dma_sync_sg_क्रम_cpu(isp->dev, req->table.sgt.sgl,
				    req->table.sgt.nents, DMA_TO_DEVICE);

		अगर (copy_from_user(req->table.addr, config->lsc,
				   req->config.size)) अणु
			ret = -EFAULT;
			जाओ करोne;
		पूर्ण

		dma_sync_sg_क्रम_device(isp->dev, req->table.sgt.sgl,
				       req->table.sgt.nents, DMA_TO_DEVICE);
	पूर्ण

	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);
	अगर (ccdc->lsc.request) अणु
		list_add_tail(&ccdc->lsc.request->list, &ccdc->lsc.मुक्त_queue);
		schedule_work(&ccdc->lsc.table_work);
	पूर्ण
	ccdc->lsc.request = req;
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);

	ret = 0;

करोne:
	अगर (ret < 0)
		ccdc_lsc_मुक्त_request(ccdc, req);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ccdc_lsc_is_configured(काष्ठा isp_ccdc_device *ccdc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);
	ret = ccdc->lsc.active != शून्य;
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक ccdc_lsc_enable(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा ispccdc_lsc *lsc = &ccdc->lsc;

	अगर (lsc->state != LSC_STATE_STOPPED)
		वापस -EINVAL;

	अगर (lsc->active) अणु
		list_add_tail(&lsc->active->list, &lsc->मुक्त_queue);
		lsc->active = शून्य;
	पूर्ण

	अगर (__ccdc_lsc_configure(ccdc, lsc->request) < 0) अणु
		omap3isp_sbl_disable(to_isp_device(ccdc),
				OMAP3_ISP_SBL_CCDC_LSC_READ);
		list_add_tail(&lsc->request->list, &lsc->मुक्त_queue);
		lsc->request = शून्य;
		जाओ करोne;
	पूर्ण

	lsc->active = lsc->request;
	lsc->request = शून्य;
	__ccdc_lsc_enable(ccdc, 1);

करोne:
	अगर (!list_empty(&lsc->मुक्त_queue))
		schedule_work(&lsc->table_work);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Parameters configuration
 */

/*
 * ccdc_configure_clamp - Configure optical-black or digital clamping
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 *
 * The CCDC perक्रमms either optical-black or digital clamp. Configure and enable
 * the selected clamp method.
 */
अटल व्योम ccdc_configure_clamp(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	u32 clamp;

	अगर (ccdc->obclamp) अणु
		clamp  = ccdc->clamp.obgain << ISPCCDC_CLAMP_OBGAIN_SHIFT;
		clamp |= ccdc->clamp.oblen << ISPCCDC_CLAMP_OBSLEN_SHIFT;
		clamp |= ccdc->clamp.oblines << ISPCCDC_CLAMP_OBSLN_SHIFT;
		clamp |= ccdc->clamp.obstpixel << ISPCCDC_CLAMP_OBST_SHIFT;
		isp_reg_ग_लिखोl(isp, clamp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CLAMP);
	पूर्ण अन्यथा अणु
		isp_reg_ग_लिखोl(isp, ccdc->clamp.dcsubval,
			       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_DCSUB);
	पूर्ण

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CLAMP,
			ISPCCDC_CLAMP_CLAMPEN,
			ccdc->obclamp ? ISPCCDC_CLAMP_CLAMPEN : 0);
पूर्ण

/*
 * ccdc_configure_fpc - Configure Faulty Pixel Correction
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_configure_fpc(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FPC, ISPCCDC_FPC_FPCEN);

	अगर (!ccdc->fpc_en)
		वापस;

	isp_reg_ग_लिखोl(isp, ccdc->fpc.dma, OMAP3_ISP_IOMEM_CCDC,
		       ISPCCDC_FPC_ADDR);
	/* The FPNUM field must be set beक्रमe enabling FPC. */
	isp_reg_ग_लिखोl(isp, (ccdc->fpc.fpnum << ISPCCDC_FPC_FPNUM_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FPC);
	isp_reg_ग_लिखोl(isp, (ccdc->fpc.fpnum << ISPCCDC_FPC_FPNUM_SHIFT) |
		       ISPCCDC_FPC_FPCEN, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FPC);
पूर्ण

/*
 * ccdc_configure_black_comp - Configure Black Level Compensation.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_configure_black_comp(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	u32 blcomp;

	blcomp  = ccdc->blcomp.b_mg << ISPCCDC_BLKCMP_B_MG_SHIFT;
	blcomp |= ccdc->blcomp.gb_g << ISPCCDC_BLKCMP_GB_G_SHIFT;
	blcomp |= ccdc->blcomp.gr_cy << ISPCCDC_BLKCMP_GR_CY_SHIFT;
	blcomp |= ccdc->blcomp.r_ye << ISPCCDC_BLKCMP_R_YE_SHIFT;

	isp_reg_ग_लिखोl(isp, blcomp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_BLKCMP);
पूर्ण

/*
 * ccdc_configure_lpf - Configure Low-Pass Filter (LPF).
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_configure_lpf(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE,
			ISPCCDC_SYN_MODE_LPF,
			ccdc->lpf ? ISPCCDC_SYN_MODE_LPF : 0);
पूर्ण

/*
 * ccdc_configure_alaw - Configure A-law compression.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_configure_alaw(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	स्थिर काष्ठा isp_क्रमmat_info *info;
	u32 alaw = 0;

	info = omap3isp_video_क्रमmat_info(ccdc->क्रमmats[CCDC_PAD_SINK].code);

	चयन (info->width) अणु
	हाल 8:
		वापस;

	हाल 10:
		alaw = ISPCCDC_ALAW_GWDI_9_0;
		अवरोध;
	हाल 11:
		alaw = ISPCCDC_ALAW_GWDI_10_1;
		अवरोध;
	हाल 12:
		alaw = ISPCCDC_ALAW_GWDI_11_2;
		अवरोध;
	हाल 13:
		alaw = ISPCCDC_ALAW_GWDI_12_3;
		अवरोध;
	पूर्ण

	अगर (ccdc->alaw)
		alaw |= ISPCCDC_ALAW_CCDTBL;

	isp_reg_ग_लिखोl(isp, alaw, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_ALAW);
पूर्ण

/*
 * ccdc_config_imgattr - Configure sensor image specअगरic attributes.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @colptn: Color pattern of the sensor.
 */
अटल व्योम ccdc_config_imgattr(काष्ठा isp_ccdc_device *ccdc, u32 colptn)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	isp_reg_ग_लिखोl(isp, colptn, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_COLPTN);
पूर्ण

/*
 * ccdc_config - Set CCDC configuration from userspace
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @ccdc_काष्ठा: Structure containing CCDC configuration sent from userspace.
 *
 * Returns 0 अगर successful, -EINVAL अगर the poपूर्णांकer to the configuration
 * काष्ठाure is null, or the copy_from_user function fails to copy user space
 * memory to kernel space memory.
 */
अटल पूर्णांक ccdc_config(काष्ठा isp_ccdc_device *ccdc,
		       काष्ठा omap3isp_ccdc_update_config *ccdc_काष्ठा)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ccdc->lock, flags);
	ccdc->shaकरोw_update = 1;
	spin_unlock_irqrestore(&ccdc->lock, flags);

	अगर (OMAP3ISP_CCDC_ALAW & ccdc_काष्ठा->update) अणु
		ccdc->alaw = !!(OMAP3ISP_CCDC_ALAW & ccdc_काष्ठा->flag);
		ccdc->update |= OMAP3ISP_CCDC_ALAW;
	पूर्ण

	अगर (OMAP3ISP_CCDC_LPF & ccdc_काष्ठा->update) अणु
		ccdc->lpf = !!(OMAP3ISP_CCDC_LPF & ccdc_काष्ठा->flag);
		ccdc->update |= OMAP3ISP_CCDC_LPF;
	पूर्ण

	अगर (OMAP3ISP_CCDC_BLCLAMP & ccdc_काष्ठा->update) अणु
		अगर (copy_from_user(&ccdc->clamp, ccdc_काष्ठा->bclamp,
				   माप(ccdc->clamp))) अणु
			ccdc->shaकरोw_update = 0;
			वापस -EFAULT;
		पूर्ण

		ccdc->obclamp = !!(OMAP3ISP_CCDC_BLCLAMP & ccdc_काष्ठा->flag);
		ccdc->update |= OMAP3ISP_CCDC_BLCLAMP;
	पूर्ण

	अगर (OMAP3ISP_CCDC_BCOMP & ccdc_काष्ठा->update) अणु
		अगर (copy_from_user(&ccdc->blcomp, ccdc_काष्ठा->blcomp,
				   माप(ccdc->blcomp))) अणु
			ccdc->shaकरोw_update = 0;
			वापस -EFAULT;
		पूर्ण

		ccdc->update |= OMAP3ISP_CCDC_BCOMP;
	पूर्ण

	ccdc->shaकरोw_update = 0;

	अगर (OMAP3ISP_CCDC_FPC & ccdc_काष्ठा->update) अणु
		काष्ठा omap3isp_ccdc_fpc fpc;
		काष्ठा ispccdc_fpc fpc_old = अणु .addr = शून्य, पूर्ण;
		काष्ठा ispccdc_fpc fpc_new;
		u32 size;

		अगर (ccdc->state != ISP_PIPELINE_STREAM_STOPPED)
			वापस -EBUSY;

		ccdc->fpc_en = !!(OMAP3ISP_CCDC_FPC & ccdc_काष्ठा->flag);

		अगर (ccdc->fpc_en) अणु
			अगर (copy_from_user(&fpc, ccdc_काष्ठा->fpc, माप(fpc)))
				वापस -EFAULT;

			size = fpc.fpnum * 4;

			/*
			 * The table address must be 64-bytes aligned, which is
			 * guaranteed by dma_alloc_coherent().
			 */
			fpc_new.fpnum = fpc.fpnum;
			fpc_new.addr = dma_alloc_coherent(isp->dev, size,
							  &fpc_new.dma,
							  GFP_KERNEL);
			अगर (fpc_new.addr == शून्य)
				वापस -ENOMEM;

			अगर (copy_from_user(fpc_new.addr,
					   (__क्रमce व्योम __user *)(दीर्घ)fpc.fpcaddr,
					   size)) अणु
				dma_मुक्त_coherent(isp->dev, size, fpc_new.addr,
						  fpc_new.dma);
				वापस -EFAULT;
			पूर्ण

			fpc_old = ccdc->fpc;
			ccdc->fpc = fpc_new;
		पूर्ण

		ccdc_configure_fpc(ccdc);

		अगर (fpc_old.addr != शून्य)
			dma_मुक्त_coherent(isp->dev, fpc_old.fpnum * 4,
					  fpc_old.addr, fpc_old.dma);
	पूर्ण

	वापस ccdc_lsc_config(ccdc, ccdc_काष्ठा);
पूर्ण

अटल व्योम ccdc_apply_controls(काष्ठा isp_ccdc_device *ccdc)
अणु
	अगर (ccdc->update & OMAP3ISP_CCDC_ALAW) अणु
		ccdc_configure_alaw(ccdc);
		ccdc->update &= ~OMAP3ISP_CCDC_ALAW;
	पूर्ण

	अगर (ccdc->update & OMAP3ISP_CCDC_LPF) अणु
		ccdc_configure_lpf(ccdc);
		ccdc->update &= ~OMAP3ISP_CCDC_LPF;
	पूर्ण

	अगर (ccdc->update & OMAP3ISP_CCDC_BLCLAMP) अणु
		ccdc_configure_clamp(ccdc);
		ccdc->update &= ~OMAP3ISP_CCDC_BLCLAMP;
	पूर्ण

	अगर (ccdc->update & OMAP3ISP_CCDC_BCOMP) अणु
		ccdc_configure_black_comp(ccdc);
		ccdc->update &= ~OMAP3ISP_CCDC_BCOMP;
	पूर्ण
पूर्ण

/*
 * omap3isp_ccdc_restore_context - Restore values of the CCDC module रेजिस्टरs
 * @isp: Poपूर्णांकer to ISP device
 */
व्योम omap3isp_ccdc_restore_context(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_ccdc_device *ccdc = &isp->isp_ccdc;

	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG, ISPCCDC_CFG_VDLC);

	ccdc->update = OMAP3ISP_CCDC_ALAW | OMAP3ISP_CCDC_LPF
		     | OMAP3ISP_CCDC_BLCLAMP | OMAP3ISP_CCDC_BCOMP;
	ccdc_apply_controls(ccdc);
	ccdc_configure_fpc(ccdc);
पूर्ण

/* -----------------------------------------------------------------------------
 * Format- and pipeline-related configuration helpers
 */

/*
 * ccdc_config_vp - Configure the Video Port.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_config_vp(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	स्थिर काष्ठा isp_क्रमmat_info *info;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित दीर्घ l3_ick = pipe->l3_ick;
	अचिन्हित पूर्णांक max_भाग = isp->revision == ISP_REVISION_15_0 ? 64 : 8;
	अचिन्हित पूर्णांक भाग = 0;
	u32 fmtcfg = ISPCCDC_FMTCFG_VPEN;

	क्रमmat = &ccdc->क्रमmats[CCDC_PAD_SOURCE_VP];

	अगर (!क्रमmat->code) अणु
		/* Disable the video port when the input क्रमmat isn't supported.
		 * This is indicated by a pixel code set to 0.
		 */
		isp_reg_ग_लिखोl(isp, 0, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMTCFG);
		वापस;
	पूर्ण

	isp_reg_ग_लिखोl(isp, (0 << ISPCCDC_FMT_HORZ_FMTSPH_SHIFT) |
		       (क्रमmat->width << ISPCCDC_FMT_HORZ_FMTLNH_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMT_HORZ);
	isp_reg_ग_लिखोl(isp, (0 << ISPCCDC_FMT_VERT_FMTSLV_SHIFT) |
		       ((क्रमmat->height + 1) << ISPCCDC_FMT_VERT_FMTLNV_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMT_VERT);

	isp_reg_ग_लिखोl(isp, (क्रमmat->width << ISPCCDC_VP_OUT_HORZ_NUM_SHIFT) |
		       (क्रमmat->height << ISPCCDC_VP_OUT_VERT_NUM_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VP_OUT);

	info = omap3isp_video_क्रमmat_info(ccdc->क्रमmats[CCDC_PAD_SINK].code);

	चयन (info->width) अणु
	हाल 8:
	हाल 10:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_9_0;
		अवरोध;
	हाल 11:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_10_1;
		अवरोध;
	हाल 12:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_11_2;
		अवरोध;
	हाल 13:
		fmtcfg |= ISPCCDC_FMTCFG_VPIN_12_3;
		अवरोध;
	पूर्ण

	अगर (pipe->input)
		भाग = DIV_ROUND_UP(l3_ick, pipe->max_rate);
	अन्यथा अगर (pipe->बाह्यal_rate)
		भाग = l3_ick / pipe->बाह्यal_rate;

	भाग = clamp(भाग, 2U, max_भाग);
	fmtcfg |= (भाग - 2) << ISPCCDC_FMTCFG_VPIF_FRQ_SHIFT;

	isp_reg_ग_लिखोl(isp, fmtcfg, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_FMTCFG);
पूर्ण

/*
 * ccdc_config_outlineoffset - Configure memory saving output line offset
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @bpl: Number of bytes per line when stored in memory.
 * @field: Field order when storing पूर्णांकerlaced क्रमmats in memory.
 *
 * Configure the offsets क्रम the line output control:
 *
 * - The horizontal line offset is defined as the number of bytes between the
 *   start of two consecutive lines in memory. Set it to the given bytes per
 *   line value.
 *
 * - The field offset value is defined as the number of lines to offset the
 *   start of the field identअगरied by FID = 1. Set it to one.
 *
 * - The line offset values are defined as the number of lines (as defined by
 *   the horizontal line offset) between the start of two consecutive lines क्रम
 *   all combinations of odd/even lines in odd/even fields. When पूर्णांकerleaving
 *   fields set them all to two lines, and to one line otherwise.
 */
अटल व्योम ccdc_config_outlineoffset(काष्ठा isp_ccdc_device *ccdc,
				      अचिन्हित पूर्णांक bpl,
				      क्रमागत v4l2_field field)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	u32 sकरोfst = 0;

	isp_reg_ग_लिखोl(isp, bpl & 0xffff, OMAP3_ISP_IOMEM_CCDC,
		       ISPCCDC_HSIZE_OFF);

	चयन (field) अणु
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_INTERLACED_BT:
		/* When पूर्णांकerleaving fields in memory offset field one by one
		 * line and set the line offset to two lines.
		 */
		sकरोfst |= (1 << ISPCCDC_SDOFST_LOFST0_SHIFT)
		       |  (1 << ISPCCDC_SDOFST_LOFST1_SHIFT)
		       |  (1 << ISPCCDC_SDOFST_LOFST2_SHIFT)
		       |  (1 << ISPCCDC_SDOFST_LOFST3_SHIFT);
		अवरोध;

	शेष:
		/* In all other हालs set the line offsets to one line. */
		अवरोध;
	पूर्ण

	isp_reg_ग_लिखोl(isp, sकरोfst, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SDOFST);
पूर्ण

/*
 * ccdc_set_outaddr - Set memory address to save output image
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @addr: ISP MMU Mapped 32-bit memory address aligned on 32 byte boundary.
 *
 * Sets the memory address where the output will be saved.
 */
अटल व्योम ccdc_set_outaddr(काष्ठा isp_ccdc_device *ccdc, u32 addr)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	isp_reg_ग_लिखोl(isp, addr, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SDR_ADDR);
पूर्ण

/*
 * omap3isp_ccdc_max_rate - Calculate maximum input data rate based on the input
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @max_rate: Maximum calculated data rate.
 *
 * Returns in *max_rate less value between calculated and passed
 */
व्योम omap3isp_ccdc_max_rate(काष्ठा isp_ccdc_device *ccdc,
			    अचिन्हित पूर्णांक *max_rate)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	अचिन्हित पूर्णांक rate;

	अगर (pipe == शून्य)
		वापस;

	/*
	 * TRM says that क्रम parallel sensors the maximum data rate
	 * should be 90% क्रमm L3/2 घड़ी, otherwise just L3/2.
	 */
	अगर (ccdc->input == CCDC_INPUT_PARALLEL)
		rate = pipe->l3_ick / 2 * 9 / 10;
	अन्यथा
		rate = pipe->l3_ick / 2;

	*max_rate = min(*max_rate, rate);
पूर्ण

/*
 * ccdc_config_sync_अगर - Set CCDC sync पूर्णांकerface configuration
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @parcfg: Parallel पूर्णांकerface platक्रमm data (may be शून्य)
 * @data_size: Data size
 */
अटल व्योम ccdc_config_sync_अगर(काष्ठा isp_ccdc_device *ccdc,
				काष्ठा isp_parallel_cfg *parcfg,
				अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat;
	u32 syn_mode = ISPCCDC_SYN_MODE_VDHDEN;

	क्रमmat = &ccdc->क्रमmats[CCDC_PAD_SINK];

	अगर (क्रमmat->code == MEDIA_BUS_FMT_YUYV8_2X8 ||
	    क्रमmat->code == MEDIA_BUS_FMT_UYVY8_2X8) अणु
		/* According to the OMAP3 TRM the input mode only affects SYNC
		 * mode, enabling BT.656 mode should take precedence. However,
		 * in practice setting the input mode to YCbCr data on 8 bits
		 * seems to be required in BT.656 mode. In SYNC mode set it to
		 * YCbCr on 16 bits as the bridge is enabled in that हाल.
		 */
		अगर (ccdc->bt656)
			syn_mode |= ISPCCDC_SYN_MODE_INPMOD_YCBCR8;
		अन्यथा
			syn_mode |= ISPCCDC_SYN_MODE_INPMOD_YCBCR16;
	पूर्ण

	चयन (data_size) अणु
	हाल 8:
		syn_mode |= ISPCCDC_SYN_MODE_DATSIZ_8;
		अवरोध;
	हाल 10:
		syn_mode |= ISPCCDC_SYN_MODE_DATSIZ_10;
		अवरोध;
	हाल 11:
		syn_mode |= ISPCCDC_SYN_MODE_DATSIZ_11;
		अवरोध;
	हाल 12:
		syn_mode |= ISPCCDC_SYN_MODE_DATSIZ_12;
		अवरोध;
	पूर्ण

	अगर (parcfg && parcfg->data_pol)
		syn_mode |= ISPCCDC_SYN_MODE_DATAPOL;

	अगर (parcfg && parcfg->hs_pol)
		syn_mode |= ISPCCDC_SYN_MODE_HDPOL;

	/* The polarity of the vertical sync संकेत output by the BT.656
	 * decoder is not करोcumented and seems to be active low.
	 */
	अगर ((parcfg && parcfg->vs_pol) || ccdc->bt656)
		syn_mode |= ISPCCDC_SYN_MODE_VDPOL;

	अगर (parcfg && parcfg->fld_pol)
		syn_mode |= ISPCCDC_SYN_MODE_FLDPOL;

	isp_reg_ग_लिखोl(isp, syn_mode, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE);

	/* The CCDC_CFG.Y8POS bit is used in YCbCr8 input mode only. The
	 * hardware seems to ignore it in all other input modes.
	 */
	अगर (क्रमmat->code == MEDIA_BUS_FMT_UYVY8_2X8)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_Y8POS);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_Y8POS);

	/* Enable or disable BT.656 mode, including error correction क्रम the
	 * synchronization codes.
	 */
	अगर (ccdc->bt656)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_REC656IF,
			    ISPCCDC_REC656IF_R656ON | ISPCCDC_REC656IF_ECCFVH);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_REC656IF,
			    ISPCCDC_REC656IF_R656ON | ISPCCDC_REC656IF_ECCFVH);

पूर्ण

/* CCDC क्रमmats descriptions */
अटल स्थिर u32 ccdc_sgrbg_pattern =
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP0PLC0_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP0PLC1_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP0PLC2_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP0PLC3_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP1PLC0_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP1PLC1_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP1PLC2_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP1PLC3_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP2PLC0_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP2PLC1_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP2PLC2_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP2PLC3_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP3PLC0_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP3PLC1_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP3PLC2_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP3PLC3_SHIFT;

अटल स्थिर u32 ccdc_srggb_pattern =
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP0PLC0_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP0PLC1_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP0PLC2_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP0PLC3_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP1PLC0_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP1PLC1_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP1PLC2_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP1PLC3_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP2PLC0_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP2PLC1_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP2PLC2_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP2PLC3_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP3PLC0_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP3PLC1_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP3PLC2_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP3PLC3_SHIFT;

अटल स्थिर u32 ccdc_sbggr_pattern =
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP0PLC0_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP0PLC1_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP0PLC2_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP0PLC3_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP1PLC0_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP1PLC1_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP1PLC2_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP1PLC3_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP2PLC0_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP2PLC1_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP2PLC2_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP2PLC3_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP3PLC0_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP3PLC1_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP3PLC2_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP3PLC3_SHIFT;

अटल स्थिर u32 ccdc_sgbrg_pattern =
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP0PLC0_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP0PLC1_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP0PLC2_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP0PLC3_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP1PLC0_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP1PLC1_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP1PLC2_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP1PLC3_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP2PLC0_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP2PLC1_SHIFT |
	ISPCCDC_COLPTN_Gb_G  << ISPCCDC_COLPTN_CP2PLC2_SHIFT |
	ISPCCDC_COLPTN_B_Mg  << ISPCCDC_COLPTN_CP2PLC3_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP3PLC0_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP3PLC1_SHIFT |
	ISPCCDC_COLPTN_R_Ye  << ISPCCDC_COLPTN_CP3PLC2_SHIFT |
	ISPCCDC_COLPTN_Gr_Cy << ISPCCDC_COLPTN_CP3PLC3_SHIFT;

अटल व्योम ccdc_configure(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	काष्ठा isp_parallel_cfg *parcfg = शून्य;
	काष्ठा v4l2_subdev *sensor;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	स्थिर काष्ठा v4l2_rect *crop;
	स्थिर काष्ठा isp_क्रमmat_info *fmt_info;
	काष्ठा v4l2_subdev_क्रमmat fmt_src;
	अचिन्हित पूर्णांक depth_out;
	अचिन्हित पूर्णांक depth_in = 0;
	काष्ठा media_pad *pad;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bridge;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक nph;
	अचिन्हित पूर्णांक sph;
	u32 syn_mode;
	u32 ccdc_pattern;

	ccdc->bt656 = false;
	ccdc->fields = 0;

	pad = media_entity_remote_pad(&ccdc->pads[CCDC_PAD_SINK]);
	sensor = media_entity_to_v4l2_subdev(pad->entity);
	अगर (ccdc->input == CCDC_INPUT_PARALLEL) अणु
		काष्ठा v4l2_subdev *sd =
			to_isp_pipeline(&ccdc->subdev.entity)->बाह्यal;

		parcfg = &v4l2_subdev_to_bus_cfg(sd)->bus.parallel;
		ccdc->bt656 = parcfg->bt656;
	पूर्ण

	/* CCDC_PAD_SINK */
	क्रमmat = &ccdc->क्रमmats[CCDC_PAD_SINK];

	/* Compute the lane shअगरter shअगरt value and enable the bridge when the
	 * input क्रमmat is a non-BT.656 YUV variant.
	 */
	fmt_src.pad = pad->index;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	अगर (!v4l2_subdev_call(sensor, pad, get_fmt, शून्य, &fmt_src)) अणु
		fmt_info = omap3isp_video_क्रमmat_info(fmt_src.क्रमmat.code);
		depth_in = fmt_info->width;
	पूर्ण

	fmt_info = omap3isp_video_क्रमmat_info(क्रमmat->code);
	depth_out = fmt_info->width;
	shअगरt = depth_in - depth_out;

	अगर (ccdc->bt656)
		bridge = ISPCTRL_PAR_BRIDGE_DISABLE;
	अन्यथा अगर (fmt_info->code == MEDIA_BUS_FMT_YUYV8_2X8)
		bridge = ISPCTRL_PAR_BRIDGE_LENDIAN;
	अन्यथा अगर (fmt_info->code == MEDIA_BUS_FMT_UYVY8_2X8)
		bridge = ISPCTRL_PAR_BRIDGE_BENDIAN;
	अन्यथा
		bridge = ISPCTRL_PAR_BRIDGE_DISABLE;

	omap3isp_configure_bridge(isp, ccdc->input, parcfg, shअगरt, bridge);

	/* Configure the sync पूर्णांकerface. */
	ccdc_config_sync_अगर(ccdc, parcfg, depth_out);

	syn_mode = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE);

	/* Use the raw, unprocessed data when writing to memory. The H3A and
	 * histogram modules are still fed with lens shading corrected data.
	 */
	syn_mode &= ~ISPCCDC_SYN_MODE_VP2SDR;

	अगर (ccdc->output & CCDC_OUTPUT_MEMORY)
		syn_mode |= ISPCCDC_SYN_MODE_WEN;
	अन्यथा
		syn_mode &= ~ISPCCDC_SYN_MODE_WEN;

	अगर (ccdc->output & CCDC_OUTPUT_RESIZER)
		syn_mode |= ISPCCDC_SYN_MODE_SDR2RSZ;
	अन्यथा
		syn_mode &= ~ISPCCDC_SYN_MODE_SDR2RSZ;

	/* Mosaic filter */
	चयन (क्रमmat->code) अणु
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
	हाल MEDIA_BUS_FMT_SRGGB12_1X12:
		ccdc_pattern = ccdc_srggb_pattern;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
	हाल MEDIA_BUS_FMT_SBGGR12_1X12:
		ccdc_pattern = ccdc_sbggr_pattern;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
	हाल MEDIA_BUS_FMT_SGBRG12_1X12:
		ccdc_pattern = ccdc_sgbrg_pattern;
		अवरोध;
	शेष:
		/* Use GRBG */
		ccdc_pattern = ccdc_sgrbg_pattern;
		अवरोध;
	पूर्ण
	ccdc_config_imgattr(ccdc, ccdc_pattern);

	/* Generate VD0 on the last line of the image and VD1 on the
	 * 2/3 height line.
	 */
	isp_reg_ग_लिखोl(isp, ((क्रमmat->height - 2) << ISPCCDC_VDINT_0_SHIFT) |
		       ((क्रमmat->height * 2 / 3) << ISPCCDC_VDINT_1_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VDINT);

	/* CCDC_PAD_SOURCE_OF */
	क्रमmat = &ccdc->क्रमmats[CCDC_PAD_SOURCE_OF];
	crop = &ccdc->crop;

	/* The horizontal coordinates are expressed in pixel घड़ी cycles. We
	 * need two cycles per pixel in BT.656 mode, and one cycle per pixel in
	 * SYNC mode regardless of the क्रमmat as the bridge is enabled क्रम YUV
	 * क्रमmats in that हाल.
	 */
	अगर (ccdc->bt656) अणु
		sph = crop->left * 2;
		nph = crop->width * 2 - 1;
	पूर्ण अन्यथा अणु
		sph = crop->left;
		nph = crop->width - 1;
	पूर्ण

	isp_reg_ग_लिखोl(isp, (sph << ISPCCDC_HORZ_INFO_SPH_SHIFT) |
		       (nph << ISPCCDC_HORZ_INFO_NPH_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_HORZ_INFO);
	isp_reg_ग_लिखोl(isp, (crop->top << ISPCCDC_VERT_START_SLV0_SHIFT) |
		       (crop->top << ISPCCDC_VERT_START_SLV1_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VERT_START);
	isp_reg_ग_लिखोl(isp, (crop->height - 1)
			<< ISPCCDC_VERT_LINES_NLV_SHIFT,
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VERT_LINES);

	ccdc_config_outlineoffset(ccdc, ccdc->video_out.bpl_value,
				  क्रमmat->field);

	/* When पूर्णांकerleaving fields enable processing of the field input संकेत.
	 * This will cause the line output control module to apply the field
	 * offset to field 1.
	 */
	अगर (ccdc->क्रमmats[CCDC_PAD_SINK].field == V4L2_FIELD_ALTERNATE &&
	    (क्रमmat->field == V4L2_FIELD_INTERLACED_TB ||
	     क्रमmat->field == V4L2_FIELD_INTERLACED_BT))
		syn_mode |= ISPCCDC_SYN_MODE_FLDMODE;

	/* The CCDC outमाला_दो data in UYVY order by शेष. Swap bytes to get
	 * YUYV.
	 */
	अगर (क्रमmat->code == MEDIA_BUS_FMT_YUYV8_1X16)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_BSWD);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_BSWD);

	/* Use PACK8 mode क्रम 1byte per pixel क्रमmats. Check क्रम BT.656 mode
	 * explicitly as the driver reports 1X16 instead of 2X8 at the OF pad
	 * क्रम simplicity.
	 */
	अगर (omap3isp_video_क्रमmat_info(क्रमmat->code)->width <= 8 || ccdc->bt656)
		syn_mode |= ISPCCDC_SYN_MODE_PACK8;
	अन्यथा
		syn_mode &= ~ISPCCDC_SYN_MODE_PACK8;

	isp_reg_ग_लिखोl(isp, syn_mode, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE);

	/* CCDC_PAD_SOURCE_VP */
	ccdc_config_vp(ccdc);

	/* Lens shading correction. */
	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);
	अगर (ccdc->lsc.request == शून्य)
		जाओ unlock;

	WARN_ON(ccdc->lsc.active);

	/* Get last good LSC configuration. If it is not supported क्रम
	 * the current active resolution discard it.
	 */
	अगर (ccdc->lsc.active == शून्य &&
	    __ccdc_lsc_configure(ccdc, ccdc->lsc.request) == 0) अणु
		ccdc->lsc.active = ccdc->lsc.request;
	पूर्ण अन्यथा अणु
		list_add_tail(&ccdc->lsc.request->list, &ccdc->lsc.मुक्त_queue);
		schedule_work(&ccdc->lsc.table_work);
	पूर्ण

	ccdc->lsc.request = शून्य;

unlock:
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);

	ccdc_apply_controls(ccdc);
पूर्ण

अटल व्योम __ccdc_enable(काष्ठा isp_ccdc_device *ccdc, पूर्णांक enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	/* Aव्योम restarting the CCDC when streaming is stopping. */
	अगर (enable && ccdc->stopping & CCDC_STOP_REQUEST)
		वापस;

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_PCR,
			ISPCCDC_PCR_EN, enable ? ISPCCDC_PCR_EN : 0);

	ccdc->running = enable;
पूर्ण

अटल पूर्णांक ccdc_disable(काष्ठा isp_ccdc_device *ccdc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ccdc->lock, flags);
	अगर (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS)
		ccdc->stopping = CCDC_STOP_REQUEST;
	अगर (!ccdc->running)
		ccdc->stopping = CCDC_STOP_FINISHED;
	spin_unlock_irqrestore(&ccdc->lock, flags);

	ret = रुको_event_समयout(ccdc->रुको,
				 ccdc->stopping == CCDC_STOP_FINISHED,
				 msecs_to_jअगरfies(2000));
	अगर (ret == 0) अणु
		ret = -ETIMEDOUT;
		dev_warn(to_device(ccdc), "CCDC stop timeout!\n");
	पूर्ण

	omap3isp_sbl_disable(to_isp_device(ccdc), OMAP3_ISP_SBL_CCDC_LSC_READ);

	mutex_lock(&ccdc->ioctl_lock);
	ccdc_lsc_मुक्त_request(ccdc, ccdc->lsc.request);
	ccdc->lsc.request = ccdc->lsc.active;
	ccdc->lsc.active = शून्य;
	cancel_work_sync(&ccdc->lsc.table_work);
	ccdc_lsc_मुक्त_queue(ccdc, &ccdc->lsc.मुक्त_queue);
	mutex_unlock(&ccdc->ioctl_lock);

	ccdc->stopping = CCDC_STOP_NOT_REQUESTED;

	वापस ret > 0 ? 0 : ret;
पूर्ण

अटल व्योम ccdc_enable(काष्ठा isp_ccdc_device *ccdc)
अणु
	अगर (ccdc_lsc_is_configured(ccdc))
		__ccdc_lsc_enable(ccdc, 1);
	__ccdc_enable(ccdc, 1);
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

/*
 * ccdc_sbl_busy - Poll idle state of CCDC and related SBL memory ग_लिखो bits
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 *
 * Returns zero अगर the CCDC is idle and the image has been written to
 * memory, too.
 */
अटल पूर्णांक ccdc_sbl_busy(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_device *isp = to_isp_device(ccdc);

	वापस omap3isp_ccdc_busy(ccdc)
		| (isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_CCDC_WR_0) &
		   ISPSBL_CCDC_WR_0_DATA_READY)
		| (isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_CCDC_WR_1) &
		   ISPSBL_CCDC_WR_0_DATA_READY)
		| (isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_CCDC_WR_2) &
		   ISPSBL_CCDC_WR_0_DATA_READY)
		| (isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_CCDC_WR_3) &
		   ISPSBL_CCDC_WR_0_DATA_READY);
पूर्ण

/*
 * ccdc_sbl_रुको_idle - Wait until the CCDC and related SBL are idle
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @max_रुको: Max retry count in us क्रम रुको क्रम idle/busy transition.
 */
अटल पूर्णांक ccdc_sbl_रुको_idle(काष्ठा isp_ccdc_device *ccdc,
			      अचिन्हित पूर्णांक max_रुको)
अणु
	अचिन्हित पूर्णांक रुको = 0;

	अगर (max_रुको == 0)
		max_रुको = 10000; /* 10 ms */

	क्रम (रुको = 0; रुको <= max_रुको; रुको++) अणु
		अगर (!ccdc_sbl_busy(ccdc))
			वापस 0;

		rmb();
		udelay(1);
	पूर्ण

	वापस -EBUSY;
पूर्ण

/* ccdc_handle_stopping - Handle CCDC and/or LSC stopping sequence
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @event: Poपूर्णांकing which event trigger handler
 *
 * Return 1 when the event and stopping request combination is satisfied,
 * zero otherwise.
 */
अटल पूर्णांक ccdc_handle_stopping(काष्ठा isp_ccdc_device *ccdc, u32 event)
अणु
	पूर्णांक rval = 0;

	चयन ((ccdc->stopping & 3) | event) अणु
	हाल CCDC_STOP_REQUEST | CCDC_EVENT_VD1:
		अगर (ccdc->lsc.state != LSC_STATE_STOPPED)
			__ccdc_lsc_enable(ccdc, 0);
		__ccdc_enable(ccdc, 0);
		ccdc->stopping = CCDC_STOP_EXECUTED;
		वापस 1;

	हाल CCDC_STOP_EXECUTED | CCDC_EVENT_VD0:
		ccdc->stopping |= CCDC_STOP_CCDC_FINISHED;
		अगर (ccdc->lsc.state == LSC_STATE_STOPPED)
			ccdc->stopping |= CCDC_STOP_LSC_FINISHED;
		rval = 1;
		अवरोध;

	हाल CCDC_STOP_EXECUTED | CCDC_EVENT_LSC_DONE:
		ccdc->stopping |= CCDC_STOP_LSC_FINISHED;
		rval = 1;
		अवरोध;

	हाल CCDC_STOP_EXECUTED | CCDC_EVENT_VD1:
		वापस 1;
	पूर्ण

	अगर (ccdc->stopping == CCDC_STOP_FINISHED) अणु
		wake_up(&ccdc->रुको);
		rval = 1;
	पूर्ण

	वापस rval;
पूर्ण

अटल व्योम ccdc_hs_vs_isr(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	काष्ठा video_device *vdev = ccdc->subdev.devnode;
	काष्ठा v4l2_event event;

	/* Frame number propagation */
	atomic_inc(&pipe->frame_number);

	स_रखो(&event, 0, माप(event));
	event.type = V4L2_EVENT_FRAME_SYNC;
	event.u.frame_sync.frame_sequence = atomic_पढ़ो(&pipe->frame_number);

	v4l2_event_queue(vdev, &event);
पूर्ण

/*
 * ccdc_lsc_isr - Handle LSC events
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @events: LSC events
 */
अटल व्योम ccdc_lsc_isr(काष्ठा isp_ccdc_device *ccdc, u32 events)
अणु
	अचिन्हित दीर्घ flags;

	अगर (events & IRQ0STATUS_CCDC_LSC_PREF_ERR_IRQ) अणु
		काष्ठा isp_pipeline *pipe =
			to_isp_pipeline(&ccdc->subdev.entity);

		ccdc_lsc_error_handler(ccdc);
		pipe->error = true;
		dev_dbg(to_device(ccdc), "lsc prefetch error\n");
	पूर्ण

	अगर (!(events & IRQ0STATUS_CCDC_LSC_DONE_IRQ))
		वापस;

	/* LSC_DONE पूर्णांकerrupt occur, there are two हालs
	 * 1. stopping क्रम reconfiguration
	 * 2. stopping because of STREAM OFF command
	 */
	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);

	अगर (ccdc->lsc.state == LSC_STATE_STOPPING)
		ccdc->lsc.state = LSC_STATE_STOPPED;

	अगर (ccdc_handle_stopping(ccdc, CCDC_EVENT_LSC_DONE))
		जाओ करोne;

	अगर (ccdc->lsc.state != LSC_STATE_RECONFIG)
		जाओ करोne;

	/* LSC is in STOPPING state, change to the new state */
	ccdc->lsc.state = LSC_STATE_STOPPED;

	/* This is an exception. Start of frame and LSC_DONE पूर्णांकerrupt
	 * have been received on the same समय. Skip this event and रुको
	 * क्रम better बार.
	 */
	अगर (events & IRQ0STATUS_HS_VS_IRQ)
		जाओ करोne;

	/* The LSC engine is stopped at this poपूर्णांक. Enable it अगर there's a
	 * pending request.
	 */
	अगर (ccdc->lsc.request == शून्य)
		जाओ करोne;

	ccdc_lsc_enable(ccdc);

करोne:
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);
पूर्ण

/*
 * Check whether the CCDC has captured all fields necessary to complete the
 * buffer.
 */
अटल bool ccdc_has_all_fields(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	क्रमागत v4l2_field of_field = ccdc->क्रमmats[CCDC_PAD_SOURCE_OF].field;
	क्रमागत v4l2_field field;

	/* When the input is progressive fields करोn't matter. */
	अगर (of_field == V4L2_FIELD_NONE)
		वापस true;

	/* Read the current field identअगरier. */
	field = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE)
	      & ISPCCDC_SYN_MODE_FLDSTAT
	      ? V4L2_FIELD_BOTTOM : V4L2_FIELD_TOP;

	/* When capturing fields in alternate order just store the current field
	 * identअगरier in the pipeline.
	 */
	अगर (of_field == V4L2_FIELD_ALTERNATE) अणु
		pipe->field = field;
		वापस true;
	पूर्ण

	/* The क्रमmat is पूर्णांकerlaced. Make sure we've captured both fields. */
	ccdc->fields |= field == V4L2_FIELD_BOTTOM
		      ? CCDC_FIELD_BOTTOM : CCDC_FIELD_TOP;

	अगर (ccdc->fields != CCDC_FIELD_BOTH)
		वापस false;

	/* Verअगरy that the field just captured corresponds to the last field
	 * needed based on the desired field order.
	 */
	अगर ((of_field == V4L2_FIELD_INTERLACED_TB && field == V4L2_FIELD_TOP) ||
	    (of_field == V4L2_FIELD_INTERLACED_BT && field == V4L2_FIELD_BOTTOM))
		वापस false;

	/* The buffer can be completed, reset the fields क्रम the next buffer. */
	ccdc->fields = 0;

	वापस true;
पूर्ण

अटल पूर्णांक ccdc_isr_buffer(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	काष्ठा isp_buffer *buffer;

	/* The CCDC generates VD0 पूर्णांकerrupts even when disabled (the datasheet
	 * करोesn't explicitly state if that's supposed to happen or not, so it
	 * can be considered as a hardware bug or as a feature, but we have to
	 * deal with it anyway). Disabling the CCDC when no buffer is available
	 * would thus not be enough, we need to handle the situation explicitly.
	 */
	अगर (list_empty(&ccdc->video_out.dmaqueue))
		वापस 0;

	/* We're in continuous mode, and memory ग_लिखोs were disabled due to a
	 * buffer underrun. Re-enable them now that we have a buffer. The buffer
	 * address has been set in ccdc_video_queue.
	 */
	अगर (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS && ccdc->underrun) अणु
		ccdc->underrun = 0;
		वापस 1;
	पूर्ण

	/* Wait क्रम the CCDC to become idle. */
	अगर (ccdc_sbl_रुको_idle(ccdc, 1000)) अणु
		dev_info(isp->dev, "CCDC won't become idle!\n");
		media_entity_क्रमागत_set(&isp->crashed, &ccdc->subdev.entity);
		omap3isp_pipeline_cancel_stream(pipe);
		वापस 0;
	पूर्ण

	/* Don't restart CCDC if we're just about to stop streaming. */
	अगर (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS &&
	    ccdc->stopping & CCDC_STOP_REQUEST)
		वापस 0;

	अगर (!ccdc_has_all_fields(ccdc))
		वापस 1;

	buffer = omap3isp_video_buffer_next(&ccdc->video_out);
	अगर (buffer != शून्य)
		ccdc_set_outaddr(ccdc, buffer->dma);

	pipe->state |= ISP_PIPELINE_IDLE_OUTPUT;

	अगर (ccdc->state == ISP_PIPELINE_STREAM_SINGLESHOT &&
	    isp_pipeline_पढ़ोy(pipe))
		omap3isp_pipeline_set_stream(pipe,
					ISP_PIPELINE_STREAM_SINGLESHOT);

	वापस buffer != शून्य;
पूर्ण

/*
 * ccdc_vd0_isr - Handle VD0 event
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 *
 * Executes LSC deferred enablement beक्रमe next frame starts.
 */
अटल व्योम ccdc_vd0_isr(काष्ठा isp_ccdc_device *ccdc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक restart = 0;

	/* In BT.656 mode the CCDC करोesn't generate an HS/VS पूर्णांकerrupt. We thus
	 * need to increment the frame counter here.
	 */
	अगर (ccdc->bt656) अणु
		काष्ठा isp_pipeline *pipe =
			to_isp_pipeline(&ccdc->subdev.entity);

		atomic_inc(&pipe->frame_number);
	पूर्ण

	/* Emulate a VD1 पूर्णांकerrupt क्रम BT.656 mode, as we can't stop the CCDC in
	 * the VD1 पूर्णांकerrupt handler in that mode without risking a CCDC stall
	 * अगर a लघु frame is received.
	 */
	अगर (ccdc->bt656) अणु
		spin_lock_irqsave(&ccdc->lock, flags);
		अगर (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS &&
		    ccdc->output & CCDC_OUTPUT_MEMORY) अणु
			अगर (ccdc->lsc.state != LSC_STATE_STOPPED)
				__ccdc_lsc_enable(ccdc, 0);
			__ccdc_enable(ccdc, 0);
		पूर्ण
		ccdc_handle_stopping(ccdc, CCDC_EVENT_VD1);
		spin_unlock_irqrestore(&ccdc->lock, flags);
	पूर्ण

	spin_lock_irqsave(&ccdc->lock, flags);
	अगर (ccdc_handle_stopping(ccdc, CCDC_EVENT_VD0)) अणु
		spin_unlock_irqrestore(&ccdc->lock, flags);
		वापस;
	पूर्ण

	अगर (ccdc->output & CCDC_OUTPUT_MEMORY)
		restart = ccdc_isr_buffer(ccdc);

	अगर (!ccdc->shaकरोw_update)
		ccdc_apply_controls(ccdc);
	spin_unlock_irqrestore(&ccdc->lock, flags);

	अगर (restart)
		ccdc_enable(ccdc);
पूर्ण

/*
 * ccdc_vd1_isr - Handle VD1 event
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 */
अटल व्योम ccdc_vd1_isr(काष्ठा isp_ccdc_device *ccdc)
अणु
	अचिन्हित दीर्घ flags;

	/* In BT.656 mode the synchronization संकेतs are generated by the CCDC
	 * from the embedded sync codes. The VD0 and VD1 पूर्णांकerrupts are thus
	 * only triggered when the CCDC is enabled, unlike बाह्यal sync mode
	 * where the line counter runs even when the CCDC is stopped. We can't
	 * disable the CCDC at VD1 समय, as no VD0 पूर्णांकerrupt would be generated
	 * क्रम a लघु frame, which would result in the CCDC being stopped and
	 * no VD पूर्णांकerrupt generated anymore. The CCDC is stopped from the VD0
	 * पूर्णांकerrupt handler instead क्रम BT.656.
	 */
	अगर (ccdc->bt656)
		वापस;

	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);

	/*
	 * Depending on the CCDC pipeline state, CCDC stopping should be
	 * handled dअगरferently. In SINGLESHOT we emulate an पूर्णांकernal CCDC
	 * stopping because the CCDC hw works only in continuous mode.
	 * When CONTINUOUS pipeline state is used and the CCDC ग_लिखोs it's
	 * data to memory the CCDC and LSC are stopped immediately but
	 * without change the CCDC stopping state machine. The CCDC
	 * stopping state machine should be used only when user request
	 * क्रम stopping is received (SINGLESHOT is an exception).
	 */
	चयन (ccdc->state) अणु
	हाल ISP_PIPELINE_STREAM_SINGLESHOT:
		ccdc->stopping = CCDC_STOP_REQUEST;
		अवरोध;

	हाल ISP_PIPELINE_STREAM_CONTINUOUS:
		अगर (ccdc->output & CCDC_OUTPUT_MEMORY) अणु
			अगर (ccdc->lsc.state != LSC_STATE_STOPPED)
				__ccdc_lsc_enable(ccdc, 0);
			__ccdc_enable(ccdc, 0);
		पूर्ण
		अवरोध;

	हाल ISP_PIPELINE_STREAM_STOPPED:
		अवरोध;
	पूर्ण

	अगर (ccdc_handle_stopping(ccdc, CCDC_EVENT_VD1))
		जाओ करोne;

	अगर (ccdc->lsc.request == शून्य)
		जाओ करोne;

	/*
	 * LSC need to be reconfigured. Stop it here and on next LSC_DONE IRQ
	 * करो the appropriate changes in रेजिस्टरs
	 */
	अगर (ccdc->lsc.state == LSC_STATE_RUNNING) अणु
		__ccdc_lsc_enable(ccdc, 0);
		ccdc->lsc.state = LSC_STATE_RECONFIG;
		जाओ करोne;
	पूर्ण

	/* LSC has been in STOPPED state, enable it */
	अगर (ccdc->lsc.state == LSC_STATE_STOPPED)
		ccdc_lsc_enable(ccdc);

करोne:
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);
पूर्ण

/*
 * omap3isp_ccdc_isr - Configure CCDC during पूर्णांकerframe समय.
 * @ccdc: Poपूर्णांकer to ISP CCDC device.
 * @events: CCDC events
 */
पूर्णांक omap3isp_ccdc_isr(काष्ठा isp_ccdc_device *ccdc, u32 events)
अणु
	अगर (ccdc->state == ISP_PIPELINE_STREAM_STOPPED)
		वापस 0;

	अगर (events & IRQ0STATUS_CCDC_VD1_IRQ)
		ccdc_vd1_isr(ccdc);

	ccdc_lsc_isr(ccdc, events);

	अगर (events & IRQ0STATUS_CCDC_VD0_IRQ)
		ccdc_vd0_isr(ccdc);

	अगर (events & IRQ0STATUS_HS_VS_IRQ)
		ccdc_hs_vs_isr(ccdc);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP video operations
 */

अटल पूर्णांक ccdc_video_queue(काष्ठा isp_video *video, काष्ठा isp_buffer *buffer)
अणु
	काष्ठा isp_ccdc_device *ccdc = &video->isp->isp_ccdc;
	अचिन्हित दीर्घ flags;
	bool restart = false;

	अगर (!(ccdc->output & CCDC_OUTPUT_MEMORY))
		वापस -ENODEV;

	ccdc_set_outaddr(ccdc, buffer->dma);

	/* We now have a buffer queued on the output, restart the pipeline
	 * on the next CCDC पूर्णांकerrupt अगर running in continuous mode (or when
	 * starting the stream) in बाह्यal sync mode, or immediately in BT.656
	 * sync mode as no CCDC पूर्णांकerrupt is generated when the CCDC is stopped
	 * in that हाल.
	 */
	spin_lock_irqsave(&ccdc->lock, flags);
	अगर (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS && !ccdc->running &&
	    ccdc->bt656)
		restart = true;
	अन्यथा
		ccdc->underrun = 1;
	spin_unlock_irqrestore(&ccdc->lock, flags);

	अगर (restart)
		ccdc_enable(ccdc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा isp_video_operations ccdc_video_ops = अणु
	.queue = ccdc_video_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

/*
 * ccdc_ioctl - CCDC module निजी ioctl's
 * @sd: ISP CCDC V4L2 subdevice
 * @cmd: ioctl command
 * @arg: ioctl argument
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल दीर्घ ccdc_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल VIDIOC_OMAP3ISP_CCDC_CFG:
		mutex_lock(&ccdc->ioctl_lock);
		ret = ccdc_config(ccdc, arg);
		mutex_unlock(&ccdc->ioctl_lock);
		अवरोध;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ccdc_subscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type != V4L2_EVENT_FRAME_SYNC)
		वापस -EINVAL;

	/* line number is zero at frame start */
	अगर (sub->id != 0)
		वापस -EINVAL;

	वापस v4l2_event_subscribe(fh, sub, OMAP3ISP_CCDC_NEVENTS, शून्य);
पूर्ण

अटल पूर्णांक ccdc_unsubscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				  काष्ठा v4l2_event_subscription *sub)
अणु
	वापस v4l2_event_unsubscribe(fh, sub);
पूर्ण

/*
 * ccdc_set_stream - Enable/Disable streaming on the CCDC module
 * @sd: ISP CCDC V4L2 subdevice
 * @enable: Enable/disable stream
 *
 * When writing to memory, the CCDC hardware can't be enabled without a memory
 * buffer to ग_लिखो to. As the s_stream operation is called in response to a
 * STREAMON call without any buffer queued yet, just update the enabled field
 * and वापस immediately. The CCDC will be enabled in ccdc_isr_buffer().
 *
 * When not writing to memory enable the CCDC immediately.
 */
अटल पूर्णांक ccdc_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	पूर्णांक ret = 0;

	अगर (ccdc->state == ISP_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISP_PIPELINE_STREAM_STOPPED)
			वापस 0;

		omap3isp_subclk_enable(isp, OMAP3_ISP_SUBCLK_CCDC);
		isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_VDLC);

		ccdc_configure(ccdc);

		ccdc_prपूर्णांक_status(ccdc);
	पूर्ण

	चयन (enable) अणु
	हाल ISP_PIPELINE_STREAM_CONTINUOUS:
		अगर (ccdc->output & CCDC_OUTPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CCDC_WRITE);

		अगर (ccdc->underrun || !(ccdc->output & CCDC_OUTPUT_MEMORY))
			ccdc_enable(ccdc);

		ccdc->underrun = 0;
		अवरोध;

	हाल ISP_PIPELINE_STREAM_SINGLESHOT:
		अगर (ccdc->output & CCDC_OUTPUT_MEMORY &&
		    ccdc->state != ISP_PIPELINE_STREAM_SINGLESHOT)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CCDC_WRITE);

		ccdc_enable(ccdc);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_STOPPED:
		ret = ccdc_disable(ccdc);
		अगर (ccdc->output & CCDC_OUTPUT_MEMORY)
			omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_CCDC_WRITE);
		omap3isp_subclk_disable(isp, OMAP3_ISP_SUBCLK_CCDC);
		ccdc->underrun = 0;
		अवरोध;
	पूर्ण

	ccdc->state = enable;
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__ccdc_get_क्रमmat(काष्ठा isp_ccdc_device *ccdc, काष्ठा v4l2_subdev_pad_config *cfg,
		  अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&ccdc->subdev, cfg, pad);
	अन्यथा
		वापस &ccdc->क्रमmats[pad];
पूर्ण

अटल काष्ठा v4l2_rect *
__ccdc_get_crop(काष्ठा isp_ccdc_device *ccdc, काष्ठा v4l2_subdev_pad_config *cfg,
		क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_crop(&ccdc->subdev, cfg, CCDC_PAD_SOURCE_OF);
	अन्यथा
		वापस &ccdc->crop;
पूर्ण

/*
 * ccdc_try_क्रमmat - Try video क्रमmat on a pad
 * @ccdc: ISP CCDC device
 * @cfg : V4L2 subdev pad configuration
 * @pad: Pad number
 * @fmt: Format
 */
अटल व्योम
ccdc_try_क्रमmat(काष्ठा isp_ccdc_device *ccdc, काष्ठा v4l2_subdev_pad_config *cfg,
		अचिन्हित पूर्णांक pad, काष्ठा v4l2_mbus_framefmt *fmt,
		क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	स्थिर काष्ठा isp_क्रमmat_info *info;
	u32 pixelcode;
	अचिन्हित पूर्णांक width = fmt->width;
	अचिन्हित पूर्णांक height = fmt->height;
	काष्ठा v4l2_rect *crop;
	क्रमागत v4l2_field field;
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल CCDC_PAD_SINK:
		क्रम (i = 0; i < ARRAY_SIZE(ccdc_fmts); i++) अणु
			अगर (fmt->code == ccdc_fmts[i])
				अवरोध;
		पूर्ण

		/* If not found, use SGRBG10 as शेष */
		अगर (i >= ARRAY_SIZE(ccdc_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		/* Clamp the input size. */
		fmt->width = clamp_t(u32, width, 32, 4096);
		fmt->height = clamp_t(u32, height, 32, 4096);

		/* Default to progressive field order. */
		अगर (fmt->field == V4L2_FIELD_ANY)
			fmt->field = V4L2_FIELD_NONE;

		अवरोध;

	हाल CCDC_PAD_SOURCE_OF:
		pixelcode = fmt->code;
		field = fmt->field;
		*fmt = *__ccdc_get_क्रमmat(ccdc, cfg, CCDC_PAD_SINK, which);

		/* In SYNC mode the bridge converts YUV क्रमmats from 2X8 to
		 * 1X16. In BT.656 no such conversion occurs. As we करोn't know
		 * at this poपूर्णांक whether the source will use SYNC or BT.656 mode
		 * let's pretend the conversion always occurs. The CCDC will be
		 * configured to pack bytes in BT.656, hiding the inaccuracy.
		 * In all हालs bytes can be swapped.
		 */
		अगर (fmt->code == MEDIA_BUS_FMT_YUYV8_2X8 ||
		    fmt->code == MEDIA_BUS_FMT_UYVY8_2X8) अणु
			/* Use the user requested क्रमmat अगर YUV. */
			अगर (pixelcode == MEDIA_BUS_FMT_YUYV8_2X8 ||
			    pixelcode == MEDIA_BUS_FMT_UYVY8_2X8 ||
			    pixelcode == MEDIA_BUS_FMT_YUYV8_1X16 ||
			    pixelcode == MEDIA_BUS_FMT_UYVY8_1X16)
				fmt->code = pixelcode;

			अगर (fmt->code == MEDIA_BUS_FMT_YUYV8_2X8)
				fmt->code = MEDIA_BUS_FMT_YUYV8_1X16;
			अन्यथा अगर (fmt->code == MEDIA_BUS_FMT_UYVY8_2X8)
				fmt->code = MEDIA_BUS_FMT_UYVY8_1X16;
		पूर्ण

		/* Hardcode the output size to the crop rectangle size. */
		crop = __ccdc_get_crop(ccdc, cfg, which);
		fmt->width = crop->width;
		fmt->height = crop->height;

		/* When input क्रमmat is पूर्णांकerlaced with alternating fields the
		 * CCDC can पूर्णांकerleave the fields.
		 */
		अगर (fmt->field == V4L2_FIELD_ALTERNATE &&
		    (field == V4L2_FIELD_INTERLACED_TB ||
		     field == V4L2_FIELD_INTERLACED_BT)) अणु
			fmt->field = field;
			fmt->height *= 2;
		पूर्ण

		अवरोध;

	हाल CCDC_PAD_SOURCE_VP:
		*fmt = *__ccdc_get_क्रमmat(ccdc, cfg, CCDC_PAD_SINK, which);

		/* The video port पूर्णांकerface truncates the data to 10 bits. */
		info = omap3isp_video_क्रमmat_info(fmt->code);
		fmt->code = info->truncated;

		/* YUV क्रमmats are not supported by the video port. */
		अगर (fmt->code == MEDIA_BUS_FMT_YUYV8_2X8 ||
		    fmt->code == MEDIA_BUS_FMT_UYVY8_2X8)
			fmt->code = 0;

		/* The number of lines that can be घड़ीed out from the video
		 * port output must be at least one line less than the number
		 * of input lines.
		 */
		fmt->width = clamp_t(u32, width, 32, fmt->width);
		fmt->height = clamp_t(u32, height, 32, fmt->height - 1);
		अवरोध;
	पूर्ण

	/* Data is written to memory unpacked, each 10-bit or 12-bit pixel is
	 * stored on 2 bytes.
	 */
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

/*
 * ccdc_try_crop - Validate a crop rectangle
 * @ccdc: ISP CCDC device
 * @sink: क्रमmat on the sink pad
 * @crop: crop rectangle to be validated
 */
अटल व्योम ccdc_try_crop(काष्ठा isp_ccdc_device *ccdc,
			  स्थिर काष्ठा v4l2_mbus_framefmt *sink,
			  काष्ठा v4l2_rect *crop)
अणु
	स्थिर काष्ठा isp_क्रमmat_info *info;
	अचिन्हित पूर्णांक max_width;

	/* For Bayer क्रमmats, restrict left/top and width/height to even values
	 * to keep the Bayer pattern.
	 */
	info = omap3isp_video_क्रमmat_info(sink->code);
	अगर (info->flavor != MEDIA_BUS_FMT_Y8_1X8) अणु
		crop->left &= ~1;
		crop->top &= ~1;
	पूर्ण

	crop->left = clamp_t(u32, crop->left, 0, sink->width - CCDC_MIN_WIDTH);
	crop->top = clamp_t(u32, crop->top, 0, sink->height - CCDC_MIN_HEIGHT);

	/* The data क्रमmatter truncates the number of horizontal output pixels
	 * to a multiple of 16. To aव्योम clipping data, allow callers to request
	 * an output size bigger than the input size up to the nearest multiple
	 * of 16.
	 */
	max_width = (sink->width - crop->left + 15) & ~15;
	crop->width = clamp_t(u32, crop->width, CCDC_MIN_WIDTH, max_width)
		    & ~15;
	crop->height = clamp_t(u32, crop->height, CCDC_MIN_HEIGHT,
			       sink->height - crop->top);

	/* Odd width/height values करोn't make sense क्रम Bayer क्रमmats. */
	अगर (info->flavor != MEDIA_BUS_FMT_Y8_1X8) अणु
		crop->width &= ~1;
		crop->height &= ~1;
	पूर्ण
पूर्ण

/*
 * ccdc_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg : V4L2 subdev pad configuration
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ccdc_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	चयन (code->pad) अणु
	हाल CCDC_PAD_SINK:
		अगर (code->index >= ARRAY_SIZE(ccdc_fmts))
			वापस -EINVAL;

		code->code = ccdc_fmts[code->index];
		अवरोध;

	हाल CCDC_PAD_SOURCE_OF:
		क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, code->pad,
					   code->which);

		अगर (क्रमmat->code == MEDIA_BUS_FMT_YUYV8_2X8 ||
		    क्रमmat->code == MEDIA_BUS_FMT_UYVY8_2X8) अणु
			/* In YUV mode the CCDC can swap bytes. */
			अगर (code->index == 0)
				code->code = MEDIA_BUS_FMT_YUYV8_1X16;
			अन्यथा अगर (code->index == 1)
				code->code = MEDIA_BUS_FMT_UYVY8_1X16;
			अन्यथा
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			/* In raw mode, no configurable क्रमmat confversion is
			 * available.
			 */
			अगर (code->index == 0)
				code->code = क्रमmat->code;
			अन्यथा
				वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल CCDC_PAD_SOURCE_VP:
		/* The CCDC supports no configurable क्रमmat conversion
		 * compatible with the video port. Enumerate a single output
		 * क्रमmat code.
		 */
		अगर (code->index != 0)
			वापस -EINVAL;

		क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, code->pad,
					   code->which);

		/* A pixel code equal to 0 means that the video port करोesn't
		 * support the input क्रमmat. Don't क्रमागतerate any pixel code.
		 */
		अगर (क्रमmat->code == 0)
			वापस -EINVAL;

		code->code = क्रमmat->code;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccdc_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	ccdc_try_क्रमmat(ccdc, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	ccdc_try_क्रमmat(ccdc, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * ccdc_get_selection - Retrieve a selection rectangle on a pad
 * @sd: ISP CCDC V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangles are the crop rectangles on the output क्रमmatter
 * source pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक ccdc_get_selection(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (sel->pad != CCDC_PAD_SOURCE_OF)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = पूर्णांक_उच्च;
		sel->r.height = पूर्णांक_उच्च;

		क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, CCDC_PAD_SINK, sel->which);
		ccdc_try_crop(ccdc, क्रमmat, &sel->r);
		अवरोध;

	हाल V4L2_SEL_TGT_CROP:
		sel->r = *__ccdc_get_crop(ccdc, cfg, sel->which);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ccdc_set_selection - Set a selection rectangle on a pad
 * @sd: ISP CCDC V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangle is the actual crop rectangle on the output
 * क्रमmatter source pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक ccdc_set_selection(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (sel->target != V4L2_SEL_TGT_CROP ||
	    sel->pad != CCDC_PAD_SOURCE_OF)
		वापस -EINVAL;

	/* The crop rectangle can't be changed जबतक streaming. */
	अगर (ccdc->state != ISP_PIPELINE_STREAM_STOPPED)
		वापस -EBUSY;

	/* Modअगरying the crop rectangle always changes the क्रमmat on the source
	 * pad. If the KEEP_CONFIG flag is set, just वापस the current crop
	 * rectangle.
	 */
	अगर (sel->flags & V4L2_SEL_FLAG_KEEP_CONFIG) अणु
		sel->r = *__ccdc_get_crop(ccdc, cfg, sel->which);
		वापस 0;
	पूर्ण

	क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, CCDC_PAD_SINK, sel->which);
	ccdc_try_crop(ccdc, क्रमmat, &sel->r);
	*__ccdc_get_crop(ccdc, cfg, sel->which) = sel->r;

	/* Update the source क्रमmat. */
	क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, CCDC_PAD_SOURCE_OF, sel->which);
	ccdc_try_क्रमmat(ccdc, cfg, CCDC_PAD_SOURCE_OF, क्रमmat, sel->which);

	वापस 0;
पूर्ण

/*
 * ccdc_get_क्रमmat - Retrieve the video क्रमmat on a pad
 * @sd : ISP CCDC V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक ccdc_get_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * ccdc_set_क्रमmat - Set the video क्रमmat on a pad
 * @sd : ISP CCDC V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL अगर the pad is invalid or करोesn't correspond
 * to the क्रमmat type.
 */
अटल पूर्णांक ccdc_set_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;

	क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	ccdc_try_क्रमmat(ccdc, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == CCDC_PAD_SINK) अणु
		/* Reset the crop rectangle. */
		crop = __ccdc_get_crop(ccdc, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->क्रमmat.width;
		crop->height = fmt->क्रमmat.height;

		ccdc_try_crop(ccdc, &fmt->क्रमmat, crop);

		/* Update the source क्रमmats. */
		क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, CCDC_PAD_SOURCE_OF,
					   fmt->which);
		*क्रमmat = fmt->क्रमmat;
		ccdc_try_क्रमmat(ccdc, cfg, CCDC_PAD_SOURCE_OF, क्रमmat,
				fmt->which);

		क्रमmat = __ccdc_get_क्रमmat(ccdc, cfg, CCDC_PAD_SOURCE_VP,
					   fmt->which);
		*क्रमmat = fmt->क्रमmat;
		ccdc_try_क्रमmat(ccdc, cfg, CCDC_PAD_SOURCE_VP, क्रमmat,
				fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Decide whether desired output pixel code can be obtained with
 * the lane shअगरter by shअगरting the input pixel code.
 * @in: input pixelcode to shअगरter
 * @out: output pixelcode from shअगरter
 * @additional_shअगरt: # of bits the sensor's LSB is offset from CAMEXT[0]
 *
 * वापस true अगर the combination is possible
 * वापस false otherwise
 */
अटल bool ccdc_is_shअगरtable(u32 in, u32 out, अचिन्हित पूर्णांक additional_shअगरt)
अणु
	स्थिर काष्ठा isp_क्रमmat_info *in_info, *out_info;

	अगर (in == out)
		वापस true;

	in_info = omap3isp_video_क्रमmat_info(in);
	out_info = omap3isp_video_क्रमmat_info(out);

	अगर ((in_info->flavor == 0) || (out_info->flavor == 0))
		वापस false;

	अगर (in_info->flavor != out_info->flavor)
		वापस false;

	वापस in_info->width - out_info->width + additional_shअगरt <= 6;
पूर्ण

अटल पूर्णांक ccdc_link_validate(काष्ठा v4l2_subdev *sd,
			      काष्ठा media_link *link,
			      काष्ठा v4l2_subdev_क्रमmat *source_fmt,
			      काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	अचिन्हित दीर्घ parallel_shअगरt;

	/* Check अगर the two ends match */
	अगर (source_fmt->क्रमmat.width != sink_fmt->क्रमmat.width ||
	    source_fmt->क्रमmat.height != sink_fmt->क्रमmat.height)
		वापस -EPIPE;

	/* We've got a parallel sensor here. */
	अगर (ccdc->input == CCDC_INPUT_PARALLEL) अणु
		काष्ठा v4l2_subdev *sd =
			media_entity_to_v4l2_subdev(link->source->entity);
		काष्ठा isp_bus_cfg *bus_cfg = v4l2_subdev_to_bus_cfg(sd);

		parallel_shअगरt = bus_cfg->bus.parallel.data_lane_shअगरt;
	पूर्ण अन्यथा अणु
		parallel_shअगरt = 0;
	पूर्ण

	/* Lane shअगरter may be used to drop bits on CCDC sink pad */
	अगर (!ccdc_is_shअगरtable(source_fmt->क्रमmat.code,
			       sink_fmt->क्रमmat.code, parallel_shअगरt))
		वापस -EPIPE;

	वापस 0;
पूर्ण

/*
 * ccdc_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP CCDC V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक ccdc_init_क्रमmats(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = CCDC_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	ccdc_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/* V4L2 subdev core operations */
अटल स्थिर काष्ठा v4l2_subdev_core_ops ccdc_v4l2_core_ops = अणु
	.ioctl = ccdc_ioctl,
	.subscribe_event = ccdc_subscribe_event,
	.unsubscribe_event = ccdc_unsubscribe_event,
पूर्ण;

/* V4L2 subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops ccdc_v4l2_video_ops = अणु
	.s_stream = ccdc_set_stream,
पूर्ण;

/* V4L2 subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops ccdc_v4l2_pad_ops = अणु
	.क्रमागत_mbus_code = ccdc_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ccdc_क्रमागत_frame_size,
	.get_fmt = ccdc_get_क्रमmat,
	.set_fmt = ccdc_set_क्रमmat,
	.get_selection = ccdc_get_selection,
	.set_selection = ccdc_set_selection,
	.link_validate = ccdc_link_validate,
पूर्ण;

/* V4L2 subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops ccdc_v4l2_ops = अणु
	.core = &ccdc_v4l2_core_ops,
	.video = &ccdc_v4l2_video_ops,
	.pad = &ccdc_v4l2_pad_ops,
पूर्ण;

/* V4L2 subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ccdc_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = ccdc_init_क्रमmats,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * ccdc_link_setup - Setup CCDC connections
 * @entity: CCDC media entity
 * @local: Pad at the local end of the link
 * @remote: Pad at the remote end of the link
 * @flags: Link flags
 *
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक ccdc_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	काष्ठा isp_device *isp = to_isp_device(ccdc);
	अचिन्हित पूर्णांक index = local->index;

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	चयन (index) अणु
	हाल CCDC_PAD_SINK | 2 << 16:
		/* Read from the sensor (parallel पूर्णांकerface), CCP2, CSI2a or
		 * CSI2c.
		 */
		अगर (!(flags & MEDIA_LNK_FL_ENABLED)) अणु
			ccdc->input = CCDC_INPUT_NONE;
			अवरोध;
		पूर्ण

		अगर (ccdc->input != CCDC_INPUT_NONE)
			वापस -EBUSY;

		अगर (remote->entity == &isp->isp_ccp2.subdev.entity)
			ccdc->input = CCDC_INPUT_CCP2B;
		अन्यथा अगर (remote->entity == &isp->isp_csi2a.subdev.entity)
			ccdc->input = CCDC_INPUT_CSI2A;
		अन्यथा अगर (remote->entity == &isp->isp_csi2c.subdev.entity)
			ccdc->input = CCDC_INPUT_CSI2C;
		अन्यथा
			ccdc->input = CCDC_INPUT_PARALLEL;

		अवरोध;

	/*
	 * The ISP core करोesn't support pipelines with multiple video outमाला_दो.
	 * Revisit this when it will be implemented, and वापस -EBUSY क्रम now.
	 */

	हाल CCDC_PAD_SOURCE_VP | 2 << 16:
		/* Write to preview engine, histogram and H3A. When none of
		 * those links are active, the video port can be disabled.
		 */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ccdc->output & ~CCDC_OUTPUT_PREVIEW)
				वापस -EBUSY;
			ccdc->output |= CCDC_OUTPUT_PREVIEW;
		पूर्ण अन्यथा अणु
			ccdc->output &= ~CCDC_OUTPUT_PREVIEW;
		पूर्ण
		अवरोध;

	हाल CCDC_PAD_SOURCE_OF:
		/* Write to memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ccdc->output & ~CCDC_OUTPUT_MEMORY)
				वापस -EBUSY;
			ccdc->output |= CCDC_OUTPUT_MEMORY;
		पूर्ण अन्यथा अणु
			ccdc->output &= ~CCDC_OUTPUT_MEMORY;
		पूर्ण
		अवरोध;

	हाल CCDC_PAD_SOURCE_OF | 2 << 16:
		/* Write to resizer */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (ccdc->output & ~CCDC_OUTPUT_RESIZER)
				वापस -EBUSY;
			ccdc->output |= CCDC_OUTPUT_RESIZER;
		पूर्ण अन्यथा अणु
			ccdc->output &= ~CCDC_OUTPUT_RESIZER;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations ccdc_media_ops = अणु
	.link_setup = ccdc_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

व्योम omap3isp_ccdc_unरेजिस्टर_entities(काष्ठा isp_ccdc_device *ccdc)
अणु
	v4l2_device_unरेजिस्टर_subdev(&ccdc->subdev);
	omap3isp_video_unरेजिस्टर(&ccdc->video_out);
पूर्ण

पूर्णांक omap3isp_ccdc_रेजिस्टर_entities(काष्ठा isp_ccdc_device *ccdc,
	काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video node. */
	ccdc->subdev.dev = vdev->mdev->dev;
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &ccdc->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap3isp_video_रेजिस्टर(&ccdc->video_out, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap3isp_ccdc_unरेजिस्टर_entities(ccdc);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP CCDC initialisation and cleanup
 */

/*
 * ccdc_init_entities - Initialize V4L2 subdev and media entity
 * @ccdc: ISP CCDC module
 *
 * Return 0 on success and a negative error code on failure.
 */
अटल पूर्णांक ccdc_init_entities(काष्ठा isp_ccdc_device *ccdc)
अणु
	काष्ठा v4l2_subdev *sd = &ccdc->subdev;
	काष्ठा media_pad *pads = ccdc->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	ccdc->input = CCDC_INPUT_NONE;

	v4l2_subdev_init(sd, &ccdc_v4l2_ops);
	sd->पूर्णांकernal_ops = &ccdc_v4l2_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP3 ISP CCDC", माप(sd->name));
	sd->grp_id = 1 << 16;	/* group ID क्रम isp subdevs */
	v4l2_set_subdevdata(sd, ccdc);
	sd->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[CCDC_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;
	pads[CCDC_PAD_SOURCE_VP].flags = MEDIA_PAD_FL_SOURCE;
	pads[CCDC_PAD_SOURCE_OF].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &ccdc_media_ops;
	ret = media_entity_pads_init(me, CCDC_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	ccdc_init_क्रमmats(sd, शून्य);

	ccdc->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ccdc->video_out.ops = &ccdc_video_ops;
	ccdc->video_out.isp = to_isp_device(ccdc);
	ccdc->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;
	ccdc->video_out.bpl_alignment = 32;

	ret = omap3isp_video_init(&ccdc->video_out, "CCDC");
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	media_entity_cleanup(me);
	वापस ret;
पूर्ण

/*
 * omap3isp_ccdc_init - CCDC module initialization.
 * @isp: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 *
 * TODO: Get the initialisation values from platक्रमm data.
 *
 * Return 0 on success or a negative error code otherwise.
 */
पूर्णांक omap3isp_ccdc_init(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_ccdc_device *ccdc = &isp->isp_ccdc;
	पूर्णांक ret;

	spin_lock_init(&ccdc->lock);
	init_रुकोqueue_head(&ccdc->रुको);
	mutex_init(&ccdc->ioctl_lock);

	ccdc->stopping = CCDC_STOP_NOT_REQUESTED;

	INIT_WORK(&ccdc->lsc.table_work, ccdc_lsc_मुक्त_table_work);
	ccdc->lsc.state = LSC_STATE_STOPPED;
	INIT_LIST_HEAD(&ccdc->lsc.मुक्त_queue);
	spin_lock_init(&ccdc->lsc.req_lock);

	ccdc->clamp.oblen = 0;
	ccdc->clamp.dcsubval = 0;

	ccdc->update = OMAP3ISP_CCDC_BLCLAMP;
	ccdc_apply_controls(ccdc);

	ret = ccdc_init_entities(ccdc);
	अगर (ret < 0) अणु
		mutex_destroy(&ccdc->ioctl_lock);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * omap3isp_ccdc_cleanup - CCDC module cleanup.
 * @isp: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 */
व्योम omap3isp_ccdc_cleanup(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_ccdc_device *ccdc = &isp->isp_ccdc;

	omap3isp_video_cleanup(&ccdc->video_out);
	media_entity_cleanup(&ccdc->subdev.entity);

	/* Free LSC requests. As the CCDC is stopped there's no active request,
	 * so only the pending request and the मुक्त queue need to be handled.
	 */
	ccdc_lsc_मुक्त_request(ccdc, ccdc->lsc.request);
	cancel_work_sync(&ccdc->lsc.table_work);
	ccdc_lsc_मुक्त_queue(ccdc, &ccdc->lsc.मुक्त_queue);

	अगर (ccdc->fpc.addr != शून्य)
		dma_मुक्त_coherent(isp->dev, ccdc->fpc.fpnum * 4, ccdc->fpc.addr,
				  ccdc->fpc.dma);

	mutex_destroy(&ccdc->ioctl_lock);
पूर्ण
