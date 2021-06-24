<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _OBJAGG_H
#घोषणा _OBJAGG_H

काष्ठा objagg_ops अणु
	माप_प्रकार obj_size;
	bool (*delta_check)(व्योम *priv, स्थिर व्योम *parent_obj,
			    स्थिर व्योम *obj);
	पूर्णांक (*hपूर्णांकs_obj_cmp)(स्थिर व्योम *obj1, स्थिर व्योम *obj2);
	व्योम * (*delta_create)(व्योम *priv, व्योम *parent_obj, व्योम *obj);
	व्योम (*delta_destroy)(व्योम *priv, व्योम *delta_priv);
	व्योम * (*root_create)(व्योम *priv, व्योम *obj, अचिन्हित पूर्णांक root_id);
#घोषणा OBJAGG_OBJ_ROOT_ID_INVALID अच_पूर्णांक_उच्च
	व्योम (*root_destroy)(व्योम *priv, व्योम *root_priv);
पूर्ण;

काष्ठा objagg;
काष्ठा objagg_obj;
काष्ठा objagg_hपूर्णांकs;

स्थिर व्योम *objagg_obj_root_priv(स्थिर काष्ठा objagg_obj *objagg_obj);
स्थिर व्योम *objagg_obj_delta_priv(स्थिर काष्ठा objagg_obj *objagg_obj);
स्थिर व्योम *objagg_obj_raw(स्थिर काष्ठा objagg_obj *objagg_obj);

काष्ठा objagg_obj *objagg_obj_get(काष्ठा objagg *objagg, व्योम *obj);
व्योम objagg_obj_put(काष्ठा objagg *objagg, काष्ठा objagg_obj *objagg_obj);
काष्ठा objagg *objagg_create(स्थिर काष्ठा objagg_ops *ops,
			     काष्ठा objagg_hपूर्णांकs *hपूर्णांकs, व्योम *priv);
व्योम objagg_destroy(काष्ठा objagg *objagg);

काष्ठा objagg_obj_stats अणु
	अचिन्हित पूर्णांक user_count;
	अचिन्हित पूर्णांक delta_user_count; /* includes delta object users */
पूर्ण;

काष्ठा objagg_obj_stats_info अणु
	काष्ठा objagg_obj_stats stats;
	काष्ठा objagg_obj *objagg_obj; /* associated object */
	bool is_root;
पूर्ण;

काष्ठा objagg_stats अणु
	अचिन्हित पूर्णांक root_count;
	अचिन्हित पूर्णांक stats_info_count;
	काष्ठा objagg_obj_stats_info stats_info[];
पूर्ण;

स्थिर काष्ठा objagg_stats *objagg_stats_get(काष्ठा objagg *objagg);
व्योम objagg_stats_put(स्थिर काष्ठा objagg_stats *objagg_stats);

क्रमागत objagg_opt_algo_type अणु
	OBJAGG_OPT_ALGO_SIMPLE_GREEDY,
पूर्ण;

काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs_get(काष्ठा objagg *objagg,
				      क्रमागत objagg_opt_algo_type opt_algo_type);
व्योम objagg_hपूर्णांकs_put(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs);
स्थिर काष्ठा objagg_stats *
objagg_hपूर्णांकs_stats_get(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs);

#पूर्ण_अगर
