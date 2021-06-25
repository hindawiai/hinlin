<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Google, Inc.
 *
 * Author: Sami Tolvanen <samitolvanen@google.com>
 */

#अगर_अघोषित DM_VERITY_FEC_H
#घोषणा DM_VERITY_FEC_H

#समावेश "dm-verity.h"
#समावेश <linux/rslib.h>

/* Reed-Solomon(M, N) parameters */
#घोषणा DM_VERITY_FEC_RSM		255
#घोषणा DM_VERITY_FEC_MAX_RSN		253
#घोषणा DM_VERITY_FEC_MIN_RSN		231	/* ~10% space overhead */

/* buffers क्रम deपूर्णांकerleaving and decoding */
#घोषणा DM_VERITY_FEC_BUF_PREALLOC	1	/* buffers to pपुनः_स्मृतिate */
#घोषणा DM_VERITY_FEC_BUF_RS_BITS	4	/* 1 << RS blocks per buffer */
/* we need buffers क्रम at most 1 << block size RS blocks */
#घोषणा DM_VERITY_FEC_BUF_MAX \
	(1 << (PAGE_SHIFT - DM_VERITY_FEC_BUF_RS_BITS))

/* maximum recursion level क्रम verity_fec_decode */
#घोषणा DM_VERITY_FEC_MAX_RECURSION	4

#घोषणा DM_VERITY_OPT_FEC_DEV		"use_fec_from_device"
#घोषणा DM_VERITY_OPT_FEC_BLOCKS	"fec_blocks"
#घोषणा DM_VERITY_OPT_FEC_START		"fec_start"
#घोषणा DM_VERITY_OPT_FEC_ROOTS		"fec_roots"

/* configuration */
काष्ठा dm_verity_fec अणु
	काष्ठा dm_dev *dev;	/* parity data device */
	काष्ठा dm_bufio_client *data_bufio;	/* क्रम data dev access */
	काष्ठा dm_bufio_client *bufio;		/* क्रम parity data access */
	माप_प्रकार io_size;		/* IO size क्रम roots */
	sector_t start;		/* parity data start in blocks */
	sector_t blocks;	/* number of blocks covered */
	sector_t rounds;	/* number of पूर्णांकerleaving rounds */
	sector_t hash_blocks;	/* blocks covered after v->hash_start */
	अचिन्हित अक्षर roots;	/* number of parity bytes, M-N of RS(M, N) */
	अचिन्हित अक्षर rsn;	/* N of RS(M, N) */
	mempool_t rs_pool;	/* mempool क्रम fio->rs */
	mempool_t pपुनः_स्मृति_pool;	/* mempool क्रम pपुनः_स्मृतिated buffers */
	mempool_t extra_pool;	/* mempool क्रम extra buffers */
	mempool_t output_pool;	/* mempool क्रम output */
	काष्ठा kmem_cache *cache;	/* cache क्रम buffers */
पूर्ण;

/* per-bio data */
काष्ठा dm_verity_fec_io अणु
	काष्ठा rs_control *rs;	/* Reed-Solomon state */
	पूर्णांक erasures[DM_VERITY_FEC_MAX_RSN];	/* erasures क्रम decode_rs8 */
	u8 *bufs[DM_VERITY_FEC_BUF_MAX];	/* bufs क्रम deपूर्णांकerleaving */
	अचिन्हित nbufs;		/* number of buffers allocated */
	u8 *output;		/* buffer क्रम corrected output */
	माप_प्रकार output_pos;
	अचिन्हित level;		/* recursion level */
पूर्ण;

#अगर_घोषित CONFIG_DM_VERITY_FEC

/* each feature parameter requires a value */
#घोषणा DM_VERITY_OPTS_FEC	8

बाह्य bool verity_fec_is_enabled(काष्ठा dm_verity *v);

बाह्य पूर्णांक verity_fec_decode(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			     क्रमागत verity_block_type type, sector_t block,
			     u8 *dest, काष्ठा bvec_iter *iter);

बाह्य अचिन्हित verity_fec_status_table(काष्ठा dm_verity *v, अचिन्हित sz,
					अक्षर *result, अचिन्हित maxlen);

बाह्य व्योम verity_fec_finish_io(काष्ठा dm_verity_io *io);
बाह्य व्योम verity_fec_init_io(काष्ठा dm_verity_io *io);

बाह्य bool verity_is_fec_opt_arg(स्थिर अक्षर *arg_name);
बाह्य पूर्णांक verity_fec_parse_opt_args(काष्ठा dm_arg_set *as,
				     काष्ठा dm_verity *v, अचिन्हित *argc,
				     स्थिर अक्षर *arg_name);

बाह्य व्योम verity_fec_dtr(काष्ठा dm_verity *v);

बाह्य पूर्णांक verity_fec_ctr_alloc(काष्ठा dm_verity *v);
बाह्य पूर्णांक verity_fec_ctr(काष्ठा dm_verity *v);

#अन्यथा /* !CONFIG_DM_VERITY_FEC */

#घोषणा DM_VERITY_OPTS_FEC	0

अटल अंतरभूत bool verity_fec_is_enabled(काष्ठा dm_verity *v)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक verity_fec_decode(काष्ठा dm_verity *v,
				    काष्ठा dm_verity_io *io,
				    क्रमागत verity_block_type type,
				    sector_t block, u8 *dest,
				    काष्ठा bvec_iter *iter)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत अचिन्हित verity_fec_status_table(काष्ठा dm_verity *v,
					       अचिन्हित sz, अक्षर *result,
					       अचिन्हित maxlen)
अणु
	वापस sz;
पूर्ण

अटल अंतरभूत व्योम verity_fec_finish_io(काष्ठा dm_verity_io *io)
अणु
पूर्ण

अटल अंतरभूत व्योम verity_fec_init_io(काष्ठा dm_verity_io *io)
अणु
पूर्ण

अटल अंतरभूत bool verity_is_fec_opt_arg(स्थिर अक्षर *arg_name)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक verity_fec_parse_opt_args(काष्ठा dm_arg_set *as,
					    काष्ठा dm_verity *v,
					    अचिन्हित *argc,
					    स्थिर अक्षर *arg_name)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम verity_fec_dtr(काष्ठा dm_verity *v)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक verity_fec_ctr_alloc(काष्ठा dm_verity *v)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक verity_fec_ctr(काष्ठा dm_verity *v)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_DM_VERITY_FEC */

#पूर्ण_अगर /* DM_VERITY_FEC_H */
