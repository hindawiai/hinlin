<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

पूर्णांक xudma_navss_psil_pair(काष्ठा udma_dev *ud, u32 src_thपढ़ो, u32 dst_thपढ़ो)
अणु
	वापस navss_psil_pair(ud, src_thपढ़ो, dst_thपढ़ो);
पूर्ण
EXPORT_SYMBOL(xudma_navss_psil_pair);

पूर्णांक xudma_navss_psil_unpair(काष्ठा udma_dev *ud, u32 src_thपढ़ो, u32 dst_thपढ़ो)
अणु
	वापस navss_psil_unpair(ud, src_thपढ़ो, dst_thपढ़ो);
पूर्ण
EXPORT_SYMBOL(xudma_navss_psil_unpair);

काष्ठा udma_dev *of_xudma_dev_get(काष्ठा device_node *np, स्थिर अक्षर *property)
अणु
	काष्ठा device_node *udma_node = np;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा udma_dev *ud;

	अगर (property) अणु
		udma_node = of_parse_phandle(np, property, 0);
		अगर (!udma_node) अणु
			pr_err("UDMA node is not found\n");
			वापस ERR_PTR(-ENODEV);
		पूर्ण
	पूर्ण

	pdev = of_find_device_by_node(udma_node);
	अगर (!pdev) अणु
		pr_debug("UDMA device not found\n");
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	अगर (np != udma_node)
		of_node_put(udma_node);

	ud = platक्रमm_get_drvdata(pdev);
	अगर (!ud) अणु
		pr_debug("UDMA has not been probed\n");
		put_device(&pdev->dev);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	वापस ud;
पूर्ण
EXPORT_SYMBOL(of_xudma_dev_get);

काष्ठा device *xudma_get_device(काष्ठा udma_dev *ud)
अणु
	वापस ud->dev;
पूर्ण
EXPORT_SYMBOL(xudma_get_device);

काष्ठा k3_ringacc *xudma_get_ringacc(काष्ठा udma_dev *ud)
अणु
	वापस ud->ringacc;
पूर्ण
EXPORT_SYMBOL(xudma_get_ringacc);

u32 xudma_dev_get_psil_base(काष्ठा udma_dev *ud)
अणु
	वापस ud->psil_base;
पूर्ण
EXPORT_SYMBOL(xudma_dev_get_psil_base);

काष्ठा udma_tisci_rm *xudma_dev_get_tisci_rm(काष्ठा udma_dev *ud)
अणु
	वापस &ud->tisci_rm;
पूर्ण
EXPORT_SYMBOL(xudma_dev_get_tisci_rm);

पूर्णांक xudma_alloc_gp_rflow_range(काष्ठा udma_dev *ud, पूर्णांक from, पूर्णांक cnt)
अणु
	वापस __udma_alloc_gp_rflow_range(ud, from, cnt);
पूर्ण
EXPORT_SYMBOL(xudma_alloc_gp_rflow_range);

पूर्णांक xudma_मुक्त_gp_rflow_range(काष्ठा udma_dev *ud, पूर्णांक from, पूर्णांक cnt)
अणु
	वापस __udma_मुक्त_gp_rflow_range(ud, from, cnt);
पूर्ण
EXPORT_SYMBOL(xudma_मुक्त_gp_rflow_range);

bool xudma_rflow_is_gp(काष्ठा udma_dev *ud, पूर्णांक id)
अणु
	अगर (!ud->rflow_gp_map)
		वापस false;

	वापस !test_bit(id, ud->rflow_gp_map);
पूर्ण
EXPORT_SYMBOL(xudma_rflow_is_gp);

#घोषणा XUDMA_GET_PUT_RESOURCE(res)					\
काष्ठा udma_##res *xudma_##res##_get(काष्ठा udma_dev *ud, पूर्णांक id)	\
अणु									\
	वापस __udma_reserve_##res(ud, UDMA_TP_NORMAL, id);		\
पूर्ण									\
EXPORT_SYMBOL(xudma_##res##_get);					\
									\
व्योम xudma_##res##_put(काष्ठा udma_dev *ud, काष्ठा udma_##res *p)	\
अणु									\
	clear_bit(p->id, ud->res##_map);				\
पूर्ण									\
EXPORT_SYMBOL(xudma_##res##_put)
XUDMA_GET_PUT_RESOURCE(tchan);
XUDMA_GET_PUT_RESOURCE(rchan);

काष्ठा udma_rflow *xudma_rflow_get(काष्ठा udma_dev *ud, पूर्णांक id)
अणु
	वापस __udma_get_rflow(ud, id);
पूर्ण
EXPORT_SYMBOL(xudma_rflow_get);

व्योम xudma_rflow_put(काष्ठा udma_dev *ud, काष्ठा udma_rflow *p)
अणु
	__udma_put_rflow(ud, p);
पूर्ण
EXPORT_SYMBOL(xudma_rflow_put);

पूर्णांक xudma_get_rflow_ring_offset(काष्ठा udma_dev *ud)
अणु
	वापस ud->tflow_cnt;
पूर्ण
EXPORT_SYMBOL(xudma_get_rflow_ring_offset);

#घोषणा XUDMA_GET_RESOURCE_ID(res)					\
पूर्णांक xudma_##res##_get_id(काष्ठा udma_##res *p)				\
अणु									\
	वापस p->id;							\
पूर्ण									\
EXPORT_SYMBOL(xudma_##res##_get_id)
XUDMA_GET_RESOURCE_ID(tchan);
XUDMA_GET_RESOURCE_ID(rchan);
XUDMA_GET_RESOURCE_ID(rflow);

/* Exported रेजिस्टर access functions */
#घोषणा XUDMA_RT_IO_FUNCTIONS(res)					\
u32 xudma_##res##rt_पढ़ो(काष्ठा udma_##res *p, पूर्णांक reg)			\
अणु									\
	अगर (!p)								\
		वापस 0;						\
	वापस udma_पढ़ो(p->reg_rt, reg);				\
पूर्ण									\
EXPORT_SYMBOL(xudma_##res##rt_पढ़ो);					\
									\
व्योम xudma_##res##rt_ग_लिखो(काष्ठा udma_##res *p, पूर्णांक reg, u32 val)	\
अणु									\
	अगर (!p)								\
		वापस;							\
	udma_ग_लिखो(p->reg_rt, reg, val);				\
पूर्ण									\
EXPORT_SYMBOL(xudma_##res##rt_ग_लिखो)
XUDMA_RT_IO_FUNCTIONS(tchan);
XUDMA_RT_IO_FUNCTIONS(rchan);

पूर्णांक xudma_is_pktdma(काष्ठा udma_dev *ud)
अणु
	वापस ud->match_data->type == DMA_TYPE_PKTDMA;
पूर्ण
EXPORT_SYMBOL(xudma_is_pktdma);

पूर्णांक xudma_pktdma_tflow_get_irq(काष्ठा udma_dev *ud, पूर्णांक udma_tflow_id)
अणु
	स्थिर काष्ठा udma_oes_offsets *oes = &ud->soc_data->oes;

	वापस ti_sci_पूर्णांकa_msi_get_virq(ud->dev, udma_tflow_id +
					oes->pktdma_tchan_flow);
पूर्ण
EXPORT_SYMBOL(xudma_pktdma_tflow_get_irq);

पूर्णांक xudma_pktdma_rflow_get_irq(काष्ठा udma_dev *ud, पूर्णांक udma_rflow_id)
अणु
	स्थिर काष्ठा udma_oes_offsets *oes = &ud->soc_data->oes;

	वापस ti_sci_पूर्णांकa_msi_get_virq(ud->dev, udma_rflow_id +
					oes->pktdma_rchan_flow);
पूर्ण
EXPORT_SYMBOL(xudma_pktdma_rflow_get_irq);
