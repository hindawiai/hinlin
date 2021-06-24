<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_REQUEST_H_
#घोषणा _BCACHE_REQUEST_H_

काष्ठा data_insert_op अणु
	काष्ठा closure		cl;
	काष्ठा cache_set	*c;
	काष्ठा bio		*bio;
	काष्ठा workqueue_काष्ठा *wq;

	अचिन्हित पूर्णांक		inode;
	uपूर्णांक16_t		ग_लिखो_poपूर्णांक;
	uपूर्णांक16_t		ग_लिखो_prio;
	blk_status_t		status;

	जोड़ अणु
		uपूर्णांक16_t	flags;

	काष्ठा अणु
		अचिन्हित पूर्णांक	bypass:1;
		अचिन्हित पूर्णांक	ग_लिखोback:1;
		अचिन्हित पूर्णांक	flush_journal:1;
		अचिन्हित पूर्णांक	csum:1;

		अचिन्हित पूर्णांक	replace:1;
		अचिन्हित पूर्णांक	replace_collision:1;

		अचिन्हित पूर्णांक	insert_data_करोne:1;
	पूर्ण;
	पूर्ण;

	काष्ठा keylist		insert_keys;
	BKEY_PADDED(replace_key);
पूर्ण;

अचिन्हित पूर्णांक bch_get_congested(स्थिर काष्ठा cache_set *c);
व्योम bch_data_insert(काष्ठा closure *cl);

व्योम bch_cached_dev_request_init(काष्ठा cached_dev *dc);
blk_qc_t cached_dev_submit_bio(काष्ठा bio *bio);

व्योम bch_flash_dev_request_init(काष्ठा bcache_device *d);
blk_qc_t flash_dev_submit_bio(काष्ठा bio *bio);

बाह्य काष्ठा kmem_cache *bch_search_cache;

#पूर्ण_अगर /* _BCACHE_REQUEST_H_ */
