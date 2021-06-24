<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>

#घोषणा TI_XBAR_DRA7		0
#घोषणा TI_XBAR_AM335X		1
अटल स्थिर u32 ti_xbar_type[] = अणु
	[TI_XBAR_DRA7] = TI_XBAR_DRA7,
	[TI_XBAR_AM335X] = TI_XBAR_AM335X,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_dma_xbar_match[] = अणु
	अणु
		.compatible = "ti,dra7-dma-crossbar",
		.data = &ti_xbar_type[TI_XBAR_DRA7],
	पूर्ण,
	अणु
		.compatible = "ti,am335x-edma-crossbar",
		.data = &ti_xbar_type[TI_XBAR_AM335X],
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

/* Crossbar on AM335x/AM437x family */
#घोषणा TI_AM335X_XBAR_LINES	64

काष्ठा ti_am335x_xbar_data अणु
	व्योम __iomem *iomem;

	काष्ठा dma_router dmarouter;

	u32 xbar_events; /* maximum number of events to select in xbar */
	u32 dma_requests; /* number of DMA requests on eDMA */
पूर्ण;

काष्ठा ti_am335x_xbar_map अणु
	u16 dma_line;
	u8 mux_val;
पूर्ण;

अटल अंतरभूत व्योम ti_am335x_xbar_ग_लिखो(व्योम __iomem *iomem, पूर्णांक event, u8 val)
अणु
	/*
	 * TPCC_EVT_MUX_60_63 रेजिस्टर layout is dअगरferent than the
	 * rest, in the sense, that event 63 is mapped to lowest byte
	 * and event 60 is mapped to highest, handle it separately.
	 */
	अगर (event >= 60 && event <= 63)
		ग_लिखोb_relaxed(val, iomem + (63 - event % 4));
	अन्यथा
		ग_लिखोb_relaxed(val, iomem + event);
पूर्ण

अटल व्योम ti_am335x_xbar_मुक्त(काष्ठा device *dev, व्योम *route_data)
अणु
	काष्ठा ti_am335x_xbar_data *xbar = dev_get_drvdata(dev);
	काष्ठा ti_am335x_xbar_map *map = route_data;

	dev_dbg(dev, "Unmapping XBAR event %u on channel %u\n",
		map->mux_val, map->dma_line);

	ti_am335x_xbar_ग_लिखो(xbar->iomem, map->dma_line, 0);
	kमुक्त(map);
पूर्ण

अटल व्योम *ti_am335x_xbar_route_allocate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(ofdma->of_node);
	काष्ठा ti_am335x_xbar_data *xbar = platक्रमm_get_drvdata(pdev);
	काष्ठा ti_am335x_xbar_map *map;

	अगर (dma_spec->args_count != 3)
		वापस ERR_PTR(-EINVAL);

	अगर (dma_spec->args[2] >= xbar->xbar_events) अणु
		dev_err(&pdev->dev, "Invalid XBAR event number: %d\n",
			dma_spec->args[2]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (dma_spec->args[0] >= xbar->dma_requests) अणु
		dev_err(&pdev->dev, "Invalid DMA request line number: %d\n",
			dma_spec->args[0]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* The of_node_put() will be करोne in the core क्रम the node */
	dma_spec->np = of_parse_phandle(ofdma->of_node, "dma-masters", 0);
	अगर (!dma_spec->np) अणु
		dev_err(&pdev->dev, "Can't get DMA master\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (!map) अणु
		of_node_put(dma_spec->np);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	map->dma_line = (u16)dma_spec->args[0];
	map->mux_val = (u8)dma_spec->args[2];

	dma_spec->args[2] = 0;
	dma_spec->args_count = 2;

	dev_dbg(&pdev->dev, "Mapping XBAR event%u to DMA%u\n",
		map->mux_val, map->dma_line);

	ti_am335x_xbar_ग_लिखो(xbar->iomem, map->dma_line, map->mux_val);

	वापस map;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_am335x_master_match[] __maybe_unused = अणु
	अणु .compatible = "ti,edma3-tpcc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक ti_am335x_xbar_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *dma_node;
	काष्ठा ti_am335x_xbar_data *xbar;
	व्योम __iomem *iomem;
	पूर्णांक i, ret;

	अगर (!node)
		वापस -ENODEV;

	xbar = devm_kzalloc(&pdev->dev, माप(*xbar), GFP_KERNEL);
	अगर (!xbar)
		वापस -ENOMEM;

	dma_node = of_parse_phandle(node, "dma-masters", 0);
	अगर (!dma_node) अणु
		dev_err(&pdev->dev, "Can't get DMA master node\n");
		वापस -ENODEV;
	पूर्ण

	match = of_match_node(ti_am335x_master_match, dma_node);
	अगर (!match) अणु
		dev_err(&pdev->dev, "DMA master is not supported\n");
		of_node_put(dma_node);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dma_node, "dma-requests",
				 &xbar->dma_requests)) अणु
		dev_info(&pdev->dev,
			 "Missing XBAR output information, using %u.\n",
			 TI_AM335X_XBAR_LINES);
		xbar->dma_requests = TI_AM335X_XBAR_LINES;
	पूर्ण
	of_node_put(dma_node);

	अगर (of_property_पढ़ो_u32(node, "dma-requests", &xbar->xbar_events)) अणु
		dev_info(&pdev->dev,
			 "Missing XBAR input information, using %u.\n",
			 TI_AM335X_XBAR_LINES);
		xbar->xbar_events = TI_AM335X_XBAR_LINES;
	पूर्ण

	iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(iomem))
		वापस PTR_ERR(iomem);

	xbar->iomem = iomem;

	xbar->dmarouter.dev = &pdev->dev;
	xbar->dmarouter.route_मुक्त = ti_am335x_xbar_मुक्त;

	platक्रमm_set_drvdata(pdev, xbar);

	/* Reset the crossbar */
	क्रम (i = 0; i < xbar->dma_requests; i++)
		ti_am335x_xbar_ग_लिखो(xbar->iomem, i, 0);

	ret = of_dma_router_रेजिस्टर(node, ti_am335x_xbar_route_allocate,
				     &xbar->dmarouter);

	वापस ret;
पूर्ण

/* Crossbar on DRA7xx family */
#घोषणा TI_DRA7_XBAR_OUTPUTS	127
#घोषणा TI_DRA7_XBAR_INPUTS	256

काष्ठा ti_dra7_xbar_data अणु
	व्योम __iomem *iomem;

	काष्ठा dma_router dmarouter;
	काष्ठा mutex mutex;
	अचिन्हित दीर्घ *dma_inuse;

	u16 safe_val; /* Value to rest the crossbar lines */
	u32 xbar_requests; /* number of DMA requests connected to XBAR */
	u32 dma_requests; /* number of DMA requests क्रमwarded to DMA */
	u32 dma_offset;
पूर्ण;

काष्ठा ti_dra7_xbar_map अणु
	u16 xbar_in;
	पूर्णांक xbar_out;
पूर्ण;

अटल अंतरभूत व्योम ti_dra7_xbar_ग_लिखो(व्योम __iomem *iomem, पूर्णांक xbar, u16 val)
अणु
	ग_लिखोw_relaxed(val, iomem + (xbar * 2));
पूर्ण

अटल व्योम ti_dra7_xbar_मुक्त(काष्ठा device *dev, व्योम *route_data)
अणु
	काष्ठा ti_dra7_xbar_data *xbar = dev_get_drvdata(dev);
	काष्ठा ti_dra7_xbar_map *map = route_data;

	dev_dbg(dev, "Unmapping XBAR%u (was routed to %d)\n",
		map->xbar_in, map->xbar_out);

	ti_dra7_xbar_ग_लिखो(xbar->iomem, map->xbar_out, xbar->safe_val);
	mutex_lock(&xbar->mutex);
	clear_bit(map->xbar_out, xbar->dma_inuse);
	mutex_unlock(&xbar->mutex);
	kमुक्त(map);
पूर्ण

अटल व्योम *ti_dra7_xbar_route_allocate(काष्ठा of_phandle_args *dma_spec,
					 काष्ठा of_dma *ofdma)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(ofdma->of_node);
	काष्ठा ti_dra7_xbar_data *xbar = platक्रमm_get_drvdata(pdev);
	काष्ठा ti_dra7_xbar_map *map;

	अगर (dma_spec->args[0] >= xbar->xbar_requests) अणु
		dev_err(&pdev->dev, "Invalid XBAR request number: %d\n",
			dma_spec->args[0]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* The of_node_put() will be करोne in the core क्रम the node */
	dma_spec->np = of_parse_phandle(ofdma->of_node, "dma-masters", 0);
	अगर (!dma_spec->np) अणु
		dev_err(&pdev->dev, "Can't get DMA master\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (!map) अणु
		of_node_put(dma_spec->np);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mutex_lock(&xbar->mutex);
	map->xbar_out = find_first_zero_bit(xbar->dma_inuse,
					    xbar->dma_requests);
	अगर (map->xbar_out == xbar->dma_requests) अणु
		mutex_unlock(&xbar->mutex);
		dev_err(&pdev->dev, "Run out of free DMA requests\n");
		kमुक्त(map);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	set_bit(map->xbar_out, xbar->dma_inuse);
	mutex_unlock(&xbar->mutex);

	map->xbar_in = (u16)dma_spec->args[0];

	dma_spec->args[0] = map->xbar_out + xbar->dma_offset;

	dev_dbg(&pdev->dev, "Mapping XBAR%u to DMA%d\n",
		map->xbar_in, map->xbar_out);

	ti_dra7_xbar_ग_लिखो(xbar->iomem, map->xbar_out, map->xbar_in);

	वापस map;
पूर्ण

#घोषणा TI_XBAR_EDMA_OFFSET	0
#घोषणा TI_XBAR_SDMA_OFFSET	1
अटल स्थिर u32 ti_dma_offset[] = अणु
	[TI_XBAR_EDMA_OFFSET] = 0,
	[TI_XBAR_SDMA_OFFSET] = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_dra7_master_match[] __maybe_unused = अणु
	अणु
		.compatible = "ti,omap4430-sdma",
		.data = &ti_dma_offset[TI_XBAR_SDMA_OFFSET],
	पूर्ण,
	अणु
		.compatible = "ti,edma3",
		.data = &ti_dma_offset[TI_XBAR_EDMA_OFFSET],
	पूर्ण,
	अणु
		.compatible = "ti,edma3-tpcc",
		.data = &ti_dma_offset[TI_XBAR_EDMA_OFFSET],
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल अंतरभूत व्योम ti_dra7_xbar_reserve(पूर्णांक offset, पूर्णांक len, अचिन्हित दीर्घ *p)
अणु
	क्रम (; len > 0; len--)
		set_bit(offset + (len - 1), p);
पूर्ण

अटल पूर्णांक ti_dra7_xbar_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *dma_node;
	काष्ठा ti_dra7_xbar_data *xbar;
	काष्ठा property *prop;
	u32 safe_val;
	पूर्णांक sz;
	व्योम __iomem *iomem;
	पूर्णांक i, ret;

	अगर (!node)
		वापस -ENODEV;

	xbar = devm_kzalloc(&pdev->dev, माप(*xbar), GFP_KERNEL);
	अगर (!xbar)
		वापस -ENOMEM;

	dma_node = of_parse_phandle(node, "dma-masters", 0);
	अगर (!dma_node) अणु
		dev_err(&pdev->dev, "Can't get DMA master node\n");
		वापस -ENODEV;
	पूर्ण

	match = of_match_node(ti_dra7_master_match, dma_node);
	अगर (!match) अणु
		dev_err(&pdev->dev, "DMA master is not supported\n");
		of_node_put(dma_node);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dma_node, "dma-requests",
				 &xbar->dma_requests)) अणु
		dev_info(&pdev->dev,
			 "Missing XBAR output information, using %u.\n",
			 TI_DRA7_XBAR_OUTPUTS);
		xbar->dma_requests = TI_DRA7_XBAR_OUTPUTS;
	पूर्ण
	of_node_put(dma_node);

	xbar->dma_inuse = devm_kसुस्मृति(&pdev->dev,
				       BITS_TO_LONGS(xbar->dma_requests),
				       माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!xbar->dma_inuse)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(node, "dma-requests", &xbar->xbar_requests)) अणु
		dev_info(&pdev->dev,
			 "Missing XBAR input information, using %u.\n",
			 TI_DRA7_XBAR_INPUTS);
		xbar->xbar_requests = TI_DRA7_XBAR_INPUTS;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "ti,dma-safe-map", &safe_val))
		xbar->safe_val = (u16)safe_val;


	prop = of_find_property(node, "ti,reserved-dma-request-ranges", &sz);
	अगर (prop) अणु
		स्थिर अक्षर pname[] = "ti,reserved-dma-request-ranges";
		u32 (*rsv_events)[2];
		माप_प्रकार nelm = sz / माप(*rsv_events);
		पूर्णांक i;

		अगर (!nelm)
			वापस -EINVAL;

		rsv_events = kसुस्मृति(nelm, माप(*rsv_events), GFP_KERNEL);
		अगर (!rsv_events)
			वापस -ENOMEM;

		ret = of_property_पढ़ो_u32_array(node, pname, (u32 *)rsv_events,
						 nelm * 2);
		अगर (ret) अणु
			kमुक्त(rsv_events);
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < nelm; i++) अणु
			ti_dra7_xbar_reserve(rsv_events[i][0], rsv_events[i][1],
					     xbar->dma_inuse);
		पूर्ण
		kमुक्त(rsv_events);
	पूर्ण

	iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(iomem))
		वापस PTR_ERR(iomem);

	xbar->iomem = iomem;

	xbar->dmarouter.dev = &pdev->dev;
	xbar->dmarouter.route_मुक्त = ti_dra7_xbar_मुक्त;
	xbar->dma_offset = *(u32 *)match->data;

	mutex_init(&xbar->mutex);
	platक्रमm_set_drvdata(pdev, xbar);

	/* Reset the crossbar */
	क्रम (i = 0; i < xbar->dma_requests; i++) अणु
		अगर (!test_bit(i, xbar->dma_inuse))
			ti_dra7_xbar_ग_लिखो(xbar->iomem, i, xbar->safe_val);
	पूर्ण

	ret = of_dma_router_रेजिस्टर(node, ti_dra7_xbar_route_allocate,
				     &xbar->dmarouter);
	अगर (ret) अणु
		/* Restore the शेषs क्रम the crossbar */
		क्रम (i = 0; i < xbar->dma_requests; i++) अणु
			अगर (!test_bit(i, xbar->dma_inuse))
				ti_dra7_xbar_ग_लिखो(xbar->iomem, i, i);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ti_dma_xbar_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	match = of_match_node(ti_dma_xbar_match, pdev->dev.of_node);
	अगर (unlikely(!match))
		वापस -EINVAL;

	चयन (*(u32 *)match->data) अणु
	हाल TI_XBAR_DRA7:
		ret = ti_dra7_xbar_probe(pdev);
		अवरोध;
	हाल TI_XBAR_AM335X:
		ret = ti_am335x_xbar_probe(pdev);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported crossbar\n");
		ret = -ENODEV;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_dma_xbar_driver = अणु
	.driver = अणु
		.name = "ti-dma-crossbar",
		.of_match_table = ti_dma_xbar_match,
	पूर्ण,
	.probe	= ti_dma_xbar_probe,
पूर्ण;

अटल पूर्णांक omap_dmaxbar_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ti_dma_xbar_driver);
पूर्ण
arch_initcall(omap_dmaxbar_init);
