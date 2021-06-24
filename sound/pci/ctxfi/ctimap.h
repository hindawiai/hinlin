<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctimap.h
 *
 * @Brief
 * This file contains the definition of generic input mapper operations
 * क्रम input mapper management.
 *
 * @Author	Liu Chun
 * @Date 	May 23 2008
 */

#अगर_अघोषित CTIMAP_H
#घोषणा CTIMAP_H

#समावेश <linux/list.h>

काष्ठा imapper अणु
	अचिन्हित लघु slot; /* the id of the slot containing input data */
	अचिन्हित लघु user; /* the id of the user resource consuming data */
	अचिन्हित लघु addr; /* the input mapper ram id */
	अचिन्हित लघु next; /* the next input mapper ram id */
	काष्ठा list_head	list;
पूर्ण;

पूर्णांक input_mapper_add(काष्ठा list_head *mappers, काष्ठा imapper *entry,
		     पूर्णांक (*map_op)(व्योम *, काष्ठा imapper *), व्योम *data);

पूर्णांक input_mapper_delete(काष्ठा list_head *mappers, काष्ठा imapper *entry,
		     पूर्णांक (*map_op)(व्योम *, काष्ठा imapper *), व्योम *data);

व्योम मुक्त_input_mapper_list(काष्ठा list_head *mappers);

#पूर्ण_अगर /* CTIMAP_H */
