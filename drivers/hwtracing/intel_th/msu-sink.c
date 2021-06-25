<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * An example software sink buffer क्रम Intel TH MSU.
 *
 * Copyright (C) 2019 Intel Corporation.
 */

#समावेश <linux/पूर्णांकel_th.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>

#घोषणा MAX_SGTS 16

काष्ठा msu_sink_निजी अणु
	काष्ठा device	*dev;
	काष्ठा sg_table **sgts;
	अचिन्हित पूर्णांक	nr_sgts;
पूर्ण;

अटल व्योम *msu_sink_assign(काष्ठा device *dev, पूर्णांक *mode)
अणु
	काष्ठा msu_sink_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	priv->sgts = kसुस्मृति(MAX_SGTS, माप(व्योम *), GFP_KERNEL);
	अगर (!priv->sgts) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	priv->dev = dev;
	*mode = MSC_MODE_MULTI;

	वापस priv;
पूर्ण

अटल व्योम msu_sink_unassign(व्योम *data)
अणु
	काष्ठा msu_sink_निजी *priv = data;

	kमुक्त(priv->sgts);
	kमुक्त(priv);
पूर्ण

/* See also: msc.c: __msc_buffer_win_alloc() */
अटल पूर्णांक msu_sink_alloc_winकरोw(व्योम *data, काष्ठा sg_table **sgt, माप_प्रकार size)
अणु
	काष्ठा msu_sink_निजी *priv = data;
	अचिन्हित पूर्णांक nents;
	काष्ठा scatterlist *sg_ptr;
	व्योम *block;
	पूर्णांक ret, i;

	अगर (priv->nr_sgts == MAX_SGTS)
		वापस -ENOMEM;

	nents = DIV_ROUND_UP(size, PAGE_SIZE);

	ret = sg_alloc_table(*sgt, nents, GFP_KERNEL);
	अगर (ret)
		वापस -ENOMEM;

	priv->sgts[priv->nr_sgts++] = *sgt;

	क्रम_each_sg((*sgt)->sgl, sg_ptr, nents, i) अणु
		block = dma_alloc_coherent(priv->dev->parent->parent,
					   PAGE_SIZE, &sg_dma_address(sg_ptr),
					   GFP_KERNEL);
		sg_set_buf(sg_ptr, block, PAGE_SIZE);
	पूर्ण

	वापस nents;
पूर्ण

/* See also: msc.c: __msc_buffer_win_मुक्त() */
अटल व्योम msu_sink_मुक्त_winकरोw(व्योम *data, काष्ठा sg_table *sgt)
अणु
	काष्ठा msu_sink_निजी *priv = data;
	काष्ठा scatterlist *sg_ptr;
	पूर्णांक i;

	क्रम_each_sg(sgt->sgl, sg_ptr, sgt->nents, i) अणु
		dma_मुक्त_coherent(priv->dev->parent->parent, PAGE_SIZE,
				  sg_virt(sg_ptr), sg_dma_address(sg_ptr));
	पूर्ण

	sg_मुक्त_table(sgt);
	priv->nr_sgts--;
पूर्ण

अटल पूर्णांक msu_sink_पढ़ोy(व्योम *data, काष्ठा sg_table *sgt, माप_प्रकार bytes)
अणु
	काष्ठा msu_sink_निजी *priv = data;

	पूर्णांकel_th_msc_winकरोw_unlock(priv->dev, sgt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा msu_buffer sink_mbuf = अणु
	.name		= "sink",
	.assign		= msu_sink_assign,
	.unassign	= msu_sink_unassign,
	.alloc_winकरोw	= msu_sink_alloc_winकरोw,
	.मुक्त_winकरोw	= msu_sink_मुक्त_winकरोw,
	.पढ़ोy		= msu_sink_पढ़ोy,
पूर्ण;

module_पूर्णांकel_th_msu_buffer(sink_mbuf);

MODULE_LICENSE("GPL v2");
