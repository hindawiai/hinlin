<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#अगर_अघोषित MTK_MUTEX_H
#घोषणा MTK_MUTEX_H

काष्ठा regmap;
काष्ठा device;
काष्ठा mtk_mutex;

काष्ठा mtk_mutex *mtk_mutex_get(काष्ठा device *dev);
पूर्णांक mtk_mutex_prepare(काष्ठा mtk_mutex *mutex);
व्योम mtk_mutex_add_comp(काष्ठा mtk_mutex *mutex,
			क्रमागत mtk_ddp_comp_id id);
व्योम mtk_mutex_enable(काष्ठा mtk_mutex *mutex);
व्योम mtk_mutex_disable(काष्ठा mtk_mutex *mutex);
व्योम mtk_mutex_हटाओ_comp(काष्ठा mtk_mutex *mutex,
			   क्रमागत mtk_ddp_comp_id id);
व्योम mtk_mutex_unprepare(काष्ठा mtk_mutex *mutex);
व्योम mtk_mutex_put(काष्ठा mtk_mutex *mutex);
व्योम mtk_mutex_acquire(काष्ठा mtk_mutex *mutex);
व्योम mtk_mutex_release(काष्ठा mtk_mutex *mutex);

#पूर्ण_अगर /* MTK_MUTEX_H */
