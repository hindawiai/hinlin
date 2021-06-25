<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OF helpers क्रम DMA request / controller
 *
 * Based on of_gpपन.स
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
 */

#अगर_अघोषित __LINUX_OF_DMA_H
#घोषणा __LINUX_OF_DMA_H

#समावेश <linux/of.h>
#समावेश <linux/dmaengine.h>

काष्ठा device_node;

काष्ठा of_dma अणु
	काष्ठा list_head	of_dma_controllers;
	काष्ठा device_node	*of_node;
	काष्ठा dma_chan		*(*of_dma_xlate)
				(काष्ठा of_phandle_args *, काष्ठा of_dma *);
	व्योम			*(*of_dma_route_allocate)
				(काष्ठा of_phandle_args *, काष्ठा of_dma *);
	काष्ठा dma_router	*dma_router;
	व्योम			*of_dma_data;
पूर्ण;

काष्ठा of_dma_filter_info अणु
	dma_cap_mask_t	dma_cap;
	dma_filter_fn	filter_fn;
पूर्ण;

#अगर_घोषित CONFIG_DMA_OF
बाह्य पूर्णांक of_dma_controller_रेजिस्टर(काष्ठा device_node *np,
		काष्ठा dma_chan *(*of_dma_xlate)
		(काष्ठा of_phandle_args *, काष्ठा of_dma *),
		व्योम *data);
बाह्य व्योम of_dma_controller_मुक्त(काष्ठा device_node *np);

बाह्य पूर्णांक of_dma_router_रेजिस्टर(काष्ठा device_node *np,
		व्योम *(*of_dma_route_allocate)
		(काष्ठा of_phandle_args *, काष्ठा of_dma *),
		काष्ठा dma_router *dma_router);
#घोषणा of_dma_router_मुक्त of_dma_controller_मुक्त

बाह्य काष्ठा dma_chan *of_dma_request_slave_channel(काष्ठा device_node *np,
						     स्थिर अक्षर *name);
बाह्य काष्ठा dma_chan *of_dma_simple_xlate(काष्ठा of_phandle_args *dma_spec,
		काष्ठा of_dma *ofdma);
बाह्य काष्ठा dma_chan *of_dma_xlate_by_chan_id(काष्ठा of_phandle_args *dma_spec,
		काष्ठा of_dma *ofdma);

#अन्यथा
अटल अंतरभूत पूर्णांक of_dma_controller_रेजिस्टर(काष्ठा device_node *np,
		काष्ठा dma_chan *(*of_dma_xlate)
		(काष्ठा of_phandle_args *, काष्ठा of_dma *),
		व्योम *data)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम of_dma_controller_मुक्त(काष्ठा device_node *np)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक of_dma_router_रेजिस्टर(काष्ठा device_node *np,
		व्योम *(*of_dma_route_allocate)
		(काष्ठा of_phandle_args *, काष्ठा of_dma *),
		काष्ठा dma_router *dma_router)
अणु
	वापस -ENODEV;
पूर्ण

#घोषणा of_dma_router_मुक्त of_dma_controller_मुक्त

अटल अंतरभूत काष्ठा dma_chan *of_dma_request_slave_channel(काष्ठा device_node *np,
						     स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा dma_chan *of_dma_simple_xlate(काष्ठा of_phandle_args *dma_spec,
		काष्ठा of_dma *ofdma)
अणु
	वापस शून्य;
पूर्ण

#घोषणा of_dma_xlate_by_chan_id शून्य

#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_OF_DMA_H */
