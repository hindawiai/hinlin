<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * isp.h
 *
 * TI OMAP3 ISP - Core
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_CORE_H
#घोषणा OMAP3_ISP_CORE_H

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/रुको.h>

#समावेश "omap3isp.h"
#समावेश "ispstat.h"
#समावेश "ispccdc.h"
#समावेश "ispreg.h"
#समावेश "ispresizer.h"
#समावेश "isppreview.h"
#समावेश "ispcsiphy.h"
#समावेश "ispcsi2.h"
#समावेश "ispccp2.h"

#घोषणा ISP_TOK_TERM		0xFFFFFFFF	/*
						 * terminating token क्रम ISP
						 * modules reg list
						 */
#घोषणा to_isp_device(ptr_module)				\
	container_of(ptr_module, काष्ठा isp_device, isp_##ptr_module)
#घोषणा to_device(ptr_module)						\
	(to_isp_device(ptr_module)->dev)

क्रमागत isp_mem_resources अणु
	OMAP3_ISP_IOMEM_MAIN,
	OMAP3_ISP_IOMEM_CCP2,
	OMAP3_ISP_IOMEM_CCDC,
	OMAP3_ISP_IOMEM_HIST,
	OMAP3_ISP_IOMEM_H3A,
	OMAP3_ISP_IOMEM_PREV,
	OMAP3_ISP_IOMEM_RESZ,
	OMAP3_ISP_IOMEM_SBL,
	OMAP3_ISP_IOMEM_CSI2A_REGS1,
	OMAP3_ISP_IOMEM_CSIPHY2,
	OMAP3_ISP_IOMEM_CSI2A_REGS2,
	OMAP3_ISP_IOMEM_CSI2C_REGS1,
	OMAP3_ISP_IOMEM_CSIPHY1,
	OMAP3_ISP_IOMEM_CSI2C_REGS2,
	OMAP3_ISP_IOMEM_LAST
पूर्ण;

क्रमागत isp_sbl_resource अणु
	OMAP3_ISP_SBL_CSI1_READ		= 0x1,
	OMAP3_ISP_SBL_CSI1_WRITE	= 0x2,
	OMAP3_ISP_SBL_CSI2A_WRITE	= 0x4,
	OMAP3_ISP_SBL_CSI2C_WRITE	= 0x8,
	OMAP3_ISP_SBL_CCDC_LSC_READ	= 0x10,
	OMAP3_ISP_SBL_CCDC_WRITE	= 0x20,
	OMAP3_ISP_SBL_PREVIEW_READ	= 0x40,
	OMAP3_ISP_SBL_PREVIEW_WRITE	= 0x80,
	OMAP3_ISP_SBL_RESIZER_READ	= 0x100,
	OMAP3_ISP_SBL_RESIZER_WRITE	= 0x200,
पूर्ण;

क्रमागत isp_subclk_resource अणु
	OMAP3_ISP_SUBCLK_CCDC		= (1 << 0),
	OMAP3_ISP_SUBCLK_AEWB		= (1 << 1),
	OMAP3_ISP_SUBCLK_AF		= (1 << 2),
	OMAP3_ISP_SUBCLK_HIST		= (1 << 3),
	OMAP3_ISP_SUBCLK_PREVIEW	= (1 << 4),
	OMAP3_ISP_SUBCLK_RESIZER	= (1 << 5),
पूर्ण;

/* ISP: OMAP 34xx ES 1.0 */
#घोषणा ISP_REVISION_1_0		0x10
/* ISP2: OMAP 34xx ES 2.0, 2.1 and 3.0 */
#घोषणा ISP_REVISION_2_0		0x20
/* ISP2P: OMAP 36xx */
#घोषणा ISP_REVISION_15_0		0xF0

#घोषणा ISP_PHY_TYPE_3430		0
#घोषणा ISP_PHY_TYPE_3630		1

काष्ठा regmap;

/*
 * काष्ठा isp_res_mapping - Map ISP io resources to ISP revision.
 * @isp_rev: ISP_REVISION_x_x
 * @offset: रेजिस्टर offsets of various ISP sub-blocks
 * @phy_type: ISP_PHY_TYPE_अणु3430,3630पूर्ण
 */
काष्ठा isp_res_mapping अणु
	u32 isp_rev;
	u32 offset[OMAP3_ISP_IOMEM_LAST];
	u32 phy_type;
पूर्ण;

/*
 * काष्ठा isp_reg - Structure क्रम ISP रेजिस्टर values.
 * @reg: 32-bit Register address.
 * @val: 32-bit Register value.
 */
काष्ठा isp_reg अणु
	क्रमागत isp_mem_resources mmio_range;
	u32 reg;
	u32 val;
पूर्ण;

क्रमागत isp_xclk_id अणु
	ISP_XCLK_A,
	ISP_XCLK_B,
पूर्ण;

काष्ठा isp_xclk अणु
	काष्ठा isp_device *isp;
	काष्ठा clk_hw hw;
	काष्ठा clk *clk;
	क्रमागत isp_xclk_id id;

	spinlock_t lock;	/* Protects enabled and भागider */
	bool enabled;
	अचिन्हित पूर्णांक भागider;
पूर्ण;

/*
 * काष्ठा isp_device - ISP device काष्ठाure.
 * @dev: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 * @revision: Stores current ISP module revision.
 * @irq_num: Currently used IRQ number.
 * @mmio_base: Array with kernel base addresses क्रम ioremapped ISP रेजिस्टर
 *             regions.
 * @mmio_hist_base_phys: Physical L4 bus address क्रम ISP hist block रेजिस्टर
 *			 region.
 * @syscon: Regmap क्रम the syscon रेजिस्टर space
 * @syscon_offset: Offset of the CSIPHY control रेजिस्टर in syscon
 * @phy_type: ISP_PHY_TYPE_अणु3430,3630पूर्ण
 * @mapping: IOMMU mapping
 * @stat_lock: Spinlock क्रम handling statistics
 * @isp_mutex: Mutex क्रम serializing requests to ISP.
 * @stop_failure: Indicates that an entity failed to stop.
 * @crashed: Crashed ent_क्रमागत
 * @has_context: Context has been saved at least once and can be restored.
 * @ref_count: Reference count क्रम handling multiple ISP requests.
 * @cam_ick: Poपूर्णांकer to camera पूर्णांकerface घड़ी काष्ठाure.
 * @cam_mclk: Poपूर्णांकer to camera functional घड़ी काष्ठाure.
 * @csi2_fck: Poपूर्णांकer to camera CSI2 complexIO घड़ी काष्ठाure.
 * @l3_ick: Poपूर्णांकer to OMAP3 L3 bus पूर्णांकerface घड़ी.
 * @xclks: External घड़ीs provided by the ISP
 * @irq: Currently attached ISP ISR callbacks inक्रमmation काष्ठाure.
 * @isp_af: Poपूर्णांकer to current settings क्रम ISP AutoFocus SCM.
 * @isp_hist: Poपूर्णांकer to current settings क्रम ISP Histogram SCM.
 * @isp_h3a: Poपूर्णांकer to current settings क्रम ISP Auto Exposure and
 *           White Balance SCM.
 * @isp_res: Poपूर्णांकer to current settings क्रम ISP Resizer.
 * @isp_prev: Poपूर्णांकer to current settings क्रम ISP Preview.
 * @isp_ccdc: Poपूर्णांकer to current settings क्रम ISP CCDC.
 * @platक्रमm_cb: ISP driver callback function poपूर्णांकers क्रम platक्रमm code
 *
 * This काष्ठाure is used to store the OMAP ISP Inक्रमmation.
 */
काष्ठा isp_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा media_device media_dev;
	काष्ठा device *dev;
	u32 revision;

	/* platक्रमm HW resources */
	अचिन्हित पूर्णांक irq_num;

	व्योम __iomem *mmio_base[OMAP3_ISP_IOMEM_LAST];
	अचिन्हित दीर्घ mmio_hist_base_phys;
	काष्ठा regmap *syscon;
	u32 syscon_offset;
	u32 phy_type;

	काष्ठा dma_iommu_mapping *mapping;

	/* ISP Obj */
	spinlock_t stat_lock;	/* common lock क्रम statistic drivers */
	काष्ठा mutex isp_mutex;	/* For handling ref_count field */
	bool stop_failure;
	काष्ठा media_entity_क्रमागत crashed;
	पूर्णांक has_context;
	पूर्णांक ref_count;
	अचिन्हित पूर्णांक स्वतःidle;
#घोषणा ISP_CLK_CAM_ICK		0
#घोषणा ISP_CLK_CAM_MCLK	1
#घोषणा ISP_CLK_CSI2_FCK	2
#घोषणा ISP_CLK_L3_ICK		3
	काष्ठा clk *घड़ी[4];
	काष्ठा isp_xclk xclks[2];

	/* ISP modules */
	काष्ठा ispstat isp_af;
	काष्ठा ispstat isp_aewb;
	काष्ठा ispstat isp_hist;
	काष्ठा isp_res_device isp_res;
	काष्ठा isp_prev_device isp_prev;
	काष्ठा isp_ccdc_device isp_ccdc;
	काष्ठा isp_csi2_device isp_csi2a;
	काष्ठा isp_csi2_device isp_csi2c;
	काष्ठा isp_ccp2_device isp_ccp2;
	काष्ठा isp_csiphy isp_csiphy1;
	काष्ठा isp_csiphy isp_csiphy2;

	अचिन्हित पूर्णांक sbl_resources;
	अचिन्हित पूर्णांक subclk_resources;
पूर्ण;

काष्ठा isp_async_subdev अणु
	काष्ठा v4l2_async_subdev asd;
	काष्ठा isp_bus_cfg bus;
पूर्ण;

#घोषणा v4l2_subdev_to_bus_cfg(sd) \
	(&container_of((sd)->asd, काष्ठा isp_async_subdev, asd)->bus)

#घोषणा v4l2_dev_to_isp_device(dev) \
	container_of(dev, काष्ठा isp_device, v4l2_dev)

व्योम omap3isp_hist_dma_करोne(काष्ठा isp_device *isp);

व्योम omap3isp_flush(काष्ठा isp_device *isp);

पूर्णांक omap3isp_module_sync_idle(काष्ठा media_entity *me, रुको_queue_head_t *रुको,
			      atomic_t *stopping);

पूर्णांक omap3isp_module_sync_is_stopping(रुको_queue_head_t *रुको,
				     atomic_t *stopping);

पूर्णांक omap3isp_pipeline_set_stream(काष्ठा isp_pipeline *pipe,
				 क्रमागत isp_pipeline_stream_state state);
व्योम omap3isp_pipeline_cancel_stream(काष्ठा isp_pipeline *pipe);
व्योम omap3isp_configure_bridge(काष्ठा isp_device *isp,
			       क्रमागत ccdc_input_entity input,
			       स्थिर काष्ठा isp_parallel_cfg *buscfg,
			       अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक bridge);

काष्ठा isp_device *omap3isp_get(काष्ठा isp_device *isp);
व्योम omap3isp_put(काष्ठा isp_device *isp);

व्योम omap3isp_prपूर्णांक_status(काष्ठा isp_device *isp);

व्योम omap3isp_sbl_enable(काष्ठा isp_device *isp, क्रमागत isp_sbl_resource res);
व्योम omap3isp_sbl_disable(काष्ठा isp_device *isp, क्रमागत isp_sbl_resource res);

व्योम omap3isp_subclk_enable(काष्ठा isp_device *isp,
			    क्रमागत isp_subclk_resource res);
व्योम omap3isp_subclk_disable(काष्ठा isp_device *isp,
			     क्रमागत isp_subclk_resource res);

पूर्णांक omap3isp_रेजिस्टर_entities(काष्ठा platक्रमm_device *pdev,
			       काष्ठा v4l2_device *v4l2_dev);
व्योम omap3isp_unरेजिस्टर_entities(काष्ठा platक्रमm_device *pdev);

/*
 * isp_reg_पढ़ोl - Read value of an OMAP3 ISP रेजिस्टर
 * @isp: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 * @isp_mmio_range: Range to which the रेजिस्टर offset refers to.
 * @reg_offset: Register offset to पढ़ो from.
 *
 * Returns an अचिन्हित 32 bit value with the required रेजिस्टर contents.
 */
अटल अंतरभूत
u32 isp_reg_पढ़ोl(काष्ठा isp_device *isp, क्रमागत isp_mem_resources isp_mmio_range,
		  u32 reg_offset)
अणु
	वापस __raw_पढ़ोl(isp->mmio_base[isp_mmio_range] + reg_offset);
पूर्ण

/*
 * isp_reg_ग_लिखोl - Write value to an OMAP3 ISP रेजिस्टर
 * @isp: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 * @reg_value: 32 bit value to ग_लिखो to the रेजिस्टर.
 * @isp_mmio_range: Range to which the रेजिस्टर offset refers to.
 * @reg_offset: Register offset to ग_लिखो पूर्णांकo.
 */
अटल अंतरभूत
व्योम isp_reg_ग_लिखोl(काष्ठा isp_device *isp, u32 reg_value,
		    क्रमागत isp_mem_resources isp_mmio_range, u32 reg_offset)
अणु
	__raw_ग_लिखोl(reg_value, isp->mmio_base[isp_mmio_range] + reg_offset);
पूर्ण

/*
 * isp_reg_clr - Clear inभागidual bits in an OMAP3 ISP रेजिस्टर
 * @isp: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 * @mmio_range: Range to which the रेजिस्टर offset refers to.
 * @reg: Register offset to work on.
 * @clr_bits: 32 bit value which would be cleared in the रेजिस्टर.
 */
अटल अंतरभूत
व्योम isp_reg_clr(काष्ठा isp_device *isp, क्रमागत isp_mem_resources mmio_range,
		 u32 reg, u32 clr_bits)
अणु
	u32 v = isp_reg_पढ़ोl(isp, mmio_range, reg);

	isp_reg_ग_लिखोl(isp, v & ~clr_bits, mmio_range, reg);
पूर्ण

/*
 * isp_reg_set - Set inभागidual bits in an OMAP3 ISP रेजिस्टर
 * @isp: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 * @mmio_range: Range to which the रेजिस्टर offset refers to.
 * @reg: Register offset to work on.
 * @set_bits: 32 bit value which would be set in the रेजिस्टर.
 */
अटल अंतरभूत
व्योम isp_reg_set(काष्ठा isp_device *isp, क्रमागत isp_mem_resources mmio_range,
		 u32 reg, u32 set_bits)
अणु
	u32 v = isp_reg_पढ़ोl(isp, mmio_range, reg);

	isp_reg_ग_लिखोl(isp, v | set_bits, mmio_range, reg);
पूर्ण

/*
 * isp_reg_clr_set - Clear and set invidial bits in an OMAP3 ISP रेजिस्टर
 * @isp: Device poपूर्णांकer specअगरic to the OMAP3 ISP.
 * @mmio_range: Range to which the रेजिस्टर offset refers to.
 * @reg: Register offset to work on.
 * @clr_bits: 32 bit value which would be cleared in the रेजिस्टर.
 * @set_bits: 32 bit value which would be set in the रेजिस्टर.
 *
 * The clear operation is करोne first, and then the set operation.
 */
अटल अंतरभूत
व्योम isp_reg_clr_set(काष्ठा isp_device *isp, क्रमागत isp_mem_resources mmio_range,
		     u32 reg, u32 clr_bits, u32 set_bits)
अणु
	u32 v = isp_reg_पढ़ोl(isp, mmio_range, reg);

	isp_reg_ग_लिखोl(isp, (v & ~clr_bits) | set_bits, mmio_range, reg);
पूर्ण

अटल अंतरभूत क्रमागत v4l2_buf_type
isp_pad_buffer_type(स्थिर काष्ठा v4l2_subdev *subdev, पूर्णांक pad)
अणु
	अगर (pad >= subdev->entity.num_pads)
		वापस 0;

	अगर (subdev->entity.pads[pad].flags & MEDIA_PAD_FL_SINK)
		वापस V4L2_BUF_TYPE_VIDEO_OUTPUT;
	अन्यथा
		वापस V4L2_BUF_TYPE_VIDEO_CAPTURE;
पूर्ण

#पूर्ण_अगर	/* OMAP3_ISP_CORE_H */
