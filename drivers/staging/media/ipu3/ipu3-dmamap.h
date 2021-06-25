<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */
/* Copyright 2018 Google LLC. */

#अगर_अघोषित __IPU3_DMAMAP_H
#घोषणा __IPU3_DMAMAP_H

काष्ठा imgu_device;
काष्ठा scatterlist;

व्योम *imgu_dmamap_alloc(काष्ठा imgu_device *imgu, काष्ठा imgu_css_map *map,
			माप_प्रकार len);
व्योम imgu_dmamap_मुक्त(काष्ठा imgu_device *imgu, काष्ठा imgu_css_map *map);

पूर्णांक imgu_dmamap_map_sg(काष्ठा imgu_device *imgu, काष्ठा scatterlist *sglist,
		       पूर्णांक nents, काष्ठा imgu_css_map *map);
व्योम imgu_dmamap_unmap(काष्ठा imgu_device *imgu, काष्ठा imgu_css_map *map);

पूर्णांक imgu_dmamap_init(काष्ठा imgu_device *imgu);
व्योम imgu_dmamap_निकास(काष्ठा imgu_device *imgu);

#पूर्ण_अगर
