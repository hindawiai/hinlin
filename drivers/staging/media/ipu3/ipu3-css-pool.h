<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */

#अगर_अघोषित __IPU3_UTIL_H
#घोषणा __IPU3_UTIL_H

काष्ठा device;
काष्ठा imgu_device;

#घोषणा IPU3_CSS_POOL_SIZE		4

/**
 * काष्ठा imgu_css_map - store DMA mapping info क्रम buffer
 *
 * @size:		size of the buffer in bytes.
 * @vaddr:		kernel भव address.
 * @daddr:		iova dma address to access IPU3.
 */
काष्ठा imgu_css_map अणु
	माप_प्रकार size;
	व्योम *vaddr;
	dma_addr_t daddr;
	काष्ठा page **pages;
पूर्ण;

/**
 * काष्ठा imgu_css_pool - circular buffer pool definition
 *
 * @entry:		array with IPU3_CSS_POOL_SIZE elements.
 * @entry.param:	a &काष्ठा imgu_css_map क्रम storing the mem mapping.
 * @entry.valid:	used to mark अगर the entry has valid data.
 * @last:		ग_लिखो poपूर्णांकer, initialized to IPU3_CSS_POOL_SIZE.
 */
काष्ठा imgu_css_pool अणु
	काष्ठा अणु
		काष्ठा imgu_css_map param;
		bool valid;
	पूर्ण entry[IPU3_CSS_POOL_SIZE];
	u32 last;
पूर्ण;

पूर्णांक imgu_css_dma_buffer_resize(काष्ठा imgu_device *imgu,
			       काष्ठा imgu_css_map *map, माप_प्रकार size);
व्योम imgu_css_pool_cleanup(काष्ठा imgu_device *imgu,
			   काष्ठा imgu_css_pool *pool);
पूर्णांक imgu_css_pool_init(काष्ठा imgu_device *imgu, काष्ठा imgu_css_pool *pool,
		       माप_प्रकार size);
व्योम imgu_css_pool_get(काष्ठा imgu_css_pool *pool);
व्योम imgu_css_pool_put(काष्ठा imgu_css_pool *pool);
स्थिर काष्ठा imgu_css_map *imgu_css_pool_last(काष्ठा imgu_css_pool *pool,
					      u32 last);

#पूर्ण_अगर
