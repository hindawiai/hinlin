<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _HWBM_H
#घोषणा _HWBM_H

काष्ठा hwbm_pool अणु
	/* Capacity of the pool */
	पूर्णांक size;
	/* Size of the buffers managed */
	पूर्णांक frag_size;
	/* Number of buffers currently used by this pool */
	पूर्णांक buf_num;
	/* स्थिरructor called during alocation */
	पूर्णांक (*स्थिरruct)(काष्ठा hwbm_pool *bm_pool, व्योम *buf);
	/* protect acces to the buffer counter*/
	काष्ठा mutex buf_lock;
	/* निजी data */
	व्योम *priv;
पूर्ण;
#अगर_घोषित CONFIG_HWBM
व्योम hwbm_buf_मुक्त(काष्ठा hwbm_pool *bm_pool, व्योम *buf);
पूर्णांक hwbm_pool_refill(काष्ठा hwbm_pool *bm_pool, gfp_t gfp);
पूर्णांक hwbm_pool_add(काष्ठा hwbm_pool *bm_pool, अचिन्हित पूर्णांक buf_num);
#अन्यथा
अटल अंतरभूत व्योम hwbm_buf_मुक्त(काष्ठा hwbm_pool *bm_pool, व्योम *buf) अणुपूर्ण

अटल अंतरभूत पूर्णांक hwbm_pool_refill(काष्ठा hwbm_pool *bm_pool, gfp_t gfp)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक hwbm_pool_add(काष्ठा hwbm_pool *bm_pool,
				अचिन्हित पूर्णांक buf_num)
अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_HWBM */
#पूर्ण_अगर /* _HWBM_H */
