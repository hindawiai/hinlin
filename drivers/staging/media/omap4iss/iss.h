<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver
 *
 * Copyright (C) 2012 Texas Instruments.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित _OMAP4_ISS_H_
#घोषणा _OMAP4_ISS_H_

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mc.h>

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/रुको.h>

#समावेश <linux/platक्रमm_data/media/omap4iss.h>

#समावेश "iss_regs.h"
#समावेश "iss_csiphy.h"
#समावेश "iss_csi2.h"
#समावेश "iss_ipipeif.h"
#समावेश "iss_ipipe.h"
#समावेश "iss_resizer.h"

काष्ठा regmap;

#घोषणा to_iss_device(ptr_module)				\
	container_of(ptr_module, काष्ठा iss_device, ptr_module)
#घोषणा to_device(ptr_module)						\
	(to_iss_device(ptr_module)->dev)

क्रमागत iss_mem_resources अणु
	OMAP4_ISS_MEM_TOP,
	OMAP4_ISS_MEM_CSI2_A_REGS1,
	OMAP4_ISS_MEM_CAMERARX_CORE1,
	OMAP4_ISS_MEM_CSI2_B_REGS1,
	OMAP4_ISS_MEM_CAMERARX_CORE2,
	OMAP4_ISS_MEM_BTE,
	OMAP4_ISS_MEM_ISP_SYS1,
	OMAP4_ISS_MEM_ISP_RESIZER,
	OMAP4_ISS_MEM_ISP_IPIPE,
	OMAP4_ISS_MEM_ISP_ISIF,
	OMAP4_ISS_MEM_ISP_IPIPEIF,
	OMAP4_ISS_MEM_LAST,
पूर्ण;

क्रमागत iss_subclk_resource अणु
	OMAP4_ISS_SUBCLK_SIMCOP		= (1 << 0),
	OMAP4_ISS_SUBCLK_ISP		= (1 << 1),
	OMAP4_ISS_SUBCLK_CSI2_A		= (1 << 2),
	OMAP4_ISS_SUBCLK_CSI2_B		= (1 << 3),
	OMAP4_ISS_SUBCLK_CCP2		= (1 << 4),
पूर्ण;

क्रमागत iss_isp_subclk_resource अणु
	OMAP4_ISS_ISP_SUBCLK_BL		= (1 << 0),
	OMAP4_ISS_ISP_SUBCLK_ISIF	= (1 << 1),
	OMAP4_ISS_ISP_SUBCLK_H3A	= (1 << 2),
	OMAP4_ISS_ISP_SUBCLK_RSZ	= (1 << 3),
	OMAP4_ISS_ISP_SUBCLK_IPIPE	= (1 << 4),
	OMAP4_ISS_ISP_SUBCLK_IPIPEIF	= (1 << 5),
पूर्ण;

/*
 * काष्ठा iss_reg - Structure क्रम ISS रेजिस्टर values.
 * @reg: 32-bit Register address.
 * @val: 32-bit Register value.
 */
काष्ठा iss_reg अणु
	क्रमागत iss_mem_resources mmio_range;
	u32 reg;
	u32 val;
पूर्ण;

/*
 * काष्ठा iss_device - ISS device काष्ठाure.
 * @syscon: Regmap क्रम the syscon रेजिस्टर space
 * @crashed: Crashed entities
 */
काष्ठा iss_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device media_dev;
	काष्ठा device *dev;
	u32 revision;

	/* platक्रमm HW resources */
	काष्ठा iss_platक्रमm_data *pdata;
	अचिन्हित पूर्णांक irq_num;

	काष्ठा resource *res[OMAP4_ISS_MEM_LAST];
	व्योम __iomem *regs[OMAP4_ISS_MEM_LAST];
	काष्ठा regmap *syscon;

	u64 raw_dmamask;

	काष्ठा mutex iss_mutex;	/* For handling ref_count field */
	काष्ठा media_entity_क्रमागत crashed;
	पूर्णांक has_context;
	पूर्णांक ref_count;

	काष्ठा clk *iss_fck;
	काष्ठा clk *iss_ctrlclk;

	/* ISS modules */
	काष्ठा iss_csi2_device csi2a;
	काष्ठा iss_csi2_device csi2b;
	काष्ठा iss_csiphy csiphy1;
	काष्ठा iss_csiphy csiphy2;
	काष्ठा iss_ipipeअगर_device ipipeअगर;
	काष्ठा iss_ipipe_device ipipe;
	काष्ठा iss_resizer_device resizer;

	अचिन्हित पूर्णांक subclk_resources;
	अचिन्हित पूर्णांक isp_subclk_resources;
पूर्ण;

#घोषणा v4l2_dev_to_iss_device(dev) \
	container_of(dev, काष्ठा iss_device, v4l2_dev)

पूर्णांक omap4iss_get_बाह्यal_info(काष्ठा iss_pipeline *pipe,
			       काष्ठा media_link *link);

पूर्णांक omap4iss_module_sync_idle(काष्ठा media_entity *me, रुको_queue_head_t *रुको,
			      atomic_t *stopping);

पूर्णांक omap4iss_module_sync_is_stopping(रुको_queue_head_t *रुको,
				     atomic_t *stopping);

पूर्णांक omap4iss_pipeline_set_stream(काष्ठा iss_pipeline *pipe,
				 क्रमागत iss_pipeline_stream_state state);
व्योम omap4iss_pipeline_cancel_stream(काष्ठा iss_pipeline *pipe);

व्योम omap4iss_configure_bridge(काष्ठा iss_device *iss,
			       क्रमागत ipipeअगर_input_entity input);

काष्ठा iss_device *omap4iss_get(काष्ठा iss_device *iss);
व्योम omap4iss_put(काष्ठा iss_device *iss);
पूर्णांक omap4iss_subclk_enable(काष्ठा iss_device *iss,
			   क्रमागत iss_subclk_resource res);
पूर्णांक omap4iss_subclk_disable(काष्ठा iss_device *iss,
			    क्रमागत iss_subclk_resource res);
व्योम omap4iss_isp_subclk_enable(काष्ठा iss_device *iss,
				क्रमागत iss_isp_subclk_resource res);
व्योम omap4iss_isp_subclk_disable(काष्ठा iss_device *iss,
				 क्रमागत iss_isp_subclk_resource res);

पूर्णांक omap4iss_रेजिस्टर_entities(काष्ठा platक्रमm_device *pdev,
			       काष्ठा v4l2_device *v4l2_dev);
व्योम omap4iss_unरेजिस्टर_entities(काष्ठा platक्रमm_device *pdev);

/*
 * iss_reg_पढ़ो - Read the value of an OMAP4 ISS रेजिस्टर
 * @iss: the ISS device
 * @res: memory resource in which the रेजिस्टर is located
 * @offset: रेजिस्टर offset in the memory resource
 *
 * Return the रेजिस्टर value.
 */
अटल अंतरभूत
u32 iss_reg_पढ़ो(काष्ठा iss_device *iss, क्रमागत iss_mem_resources res,
		 u32 offset)
अणु
	वापस पढ़ोl(iss->regs[res] + offset);
पूर्ण

/*
 * iss_reg_ग_लिखो - Write a value to an OMAP4 ISS रेजिस्टर
 * @iss: the ISS device
 * @res: memory resource in which the रेजिस्टर is located
 * @offset: रेजिस्टर offset in the memory resource
 * @value: value to be written
 */
अटल अंतरभूत
व्योम iss_reg_ग_लिखो(काष्ठा iss_device *iss, क्रमागत iss_mem_resources res,
		   u32 offset, u32 value)
अणु
	ग_लिखोl(value, iss->regs[res] + offset);
पूर्ण

/*
 * iss_reg_clr - Clear bits in an OMAP4 ISS रेजिस्टर
 * @iss: the ISS device
 * @res: memory resource in which the रेजिस्टर is located
 * @offset: रेजिस्टर offset in the memory resource
 * @clr: bit mask to be cleared
 */
अटल अंतरभूत
व्योम iss_reg_clr(काष्ठा iss_device *iss, क्रमागत iss_mem_resources res,
		 u32 offset, u32 clr)
अणु
	u32 v = iss_reg_पढ़ो(iss, res, offset);

	iss_reg_ग_लिखो(iss, res, offset, v & ~clr);
पूर्ण

/*
 * iss_reg_set - Set bits in an OMAP4 ISS रेजिस्टर
 * @iss: the ISS device
 * @res: memory resource in which the रेजिस्टर is located
 * @offset: रेजिस्टर offset in the memory resource
 * @set: bit mask to be set
 */
अटल अंतरभूत
व्योम iss_reg_set(काष्ठा iss_device *iss, क्रमागत iss_mem_resources res,
		 u32 offset, u32 set)
अणु
	u32 v = iss_reg_पढ़ो(iss, res, offset);

	iss_reg_ग_लिखो(iss, res, offset, v | set);
पूर्ण

/*
 * iss_reg_update - Clear and set bits in an OMAP4 ISS रेजिस्टर
 * @iss: the ISS device
 * @res: memory resource in which the रेजिस्टर is located
 * @offset: रेजिस्टर offset in the memory resource
 * @clr: bit mask to be cleared
 * @set: bit mask to be set
 *
 * Clear the clr mask first and then set the set mask.
 */
अटल अंतरभूत
व्योम iss_reg_update(काष्ठा iss_device *iss, क्रमागत iss_mem_resources res,
		    u32 offset, u32 clr, u32 set)
अणु
	u32 v = iss_reg_पढ़ो(iss, res, offset);

	iss_reg_ग_लिखो(iss, res, offset, (v & ~clr) | set);
पूर्ण

#घोषणा iss_poll_condition_समयout(cond, समयout, min_ival, max_ival)	\
(अणु									\
	अचिन्हित दीर्घ __समयout = jअगरfies + usecs_to_jअगरfies(समयout);	\
	अचिन्हित पूर्णांक __min_ival = (min_ival);				\
	अचिन्हित पूर्णांक __max_ival = (max_ival);				\
	bool __cond;							\
	जबतक (!(__cond = (cond))) अणु					\
		अगर (समय_after(jअगरfies, __समयout))			\
			अवरोध;						\
		usleep_range(__min_ival, __max_ival);			\
	पूर्ण								\
	!__cond;							\
पूर्ण)

#पूर्ण_अगर /* _OMAP4_ISS_H_ */
