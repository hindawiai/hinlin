<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2013
 *  Minchan Kim <minchan@kernel.org>
 */
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/bपन.स>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cpumask.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "decompressor.h"
#समावेश "squashfs.h"

/*
 * This file implements multi-thपढ़ोed decompression in the
 * decompressor framework
 */


/*
 * The reason that multiply two is that a CPU can request new I/O
 * जबतक it is रुकोing previous request.
 */
#घोषणा MAX_DECOMPRESSOR	(num_online_cpus() * 2)


पूर्णांक squashfs_max_decompressors(व्योम)
अणु
	वापस MAX_DECOMPRESSOR;
पूर्ण


काष्ठा squashfs_stream अणु
	व्योम			*comp_opts;
	काष्ठा list_head	strm_list;
	काष्ठा mutex		mutex;
	पूर्णांक			avail_decomp;
	रुको_queue_head_t	रुको;
पूर्ण;


काष्ठा decomp_stream अणु
	व्योम *stream;
	काष्ठा list_head list;
पूर्ण;


अटल व्योम put_decomp_stream(काष्ठा decomp_stream *decomp_strm,
				काष्ठा squashfs_stream *stream)
अणु
	mutex_lock(&stream->mutex);
	list_add(&decomp_strm->list, &stream->strm_list);
	mutex_unlock(&stream->mutex);
	wake_up(&stream->रुको);
पूर्ण

व्योम *squashfs_decompressor_create(काष्ठा squashfs_sb_info *msblk,
				व्योम *comp_opts)
अणु
	काष्ठा squashfs_stream *stream;
	काष्ठा decomp_stream *decomp_strm = शून्य;
	पूर्णांक err = -ENOMEM;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		जाओ out;

	stream->comp_opts = comp_opts;
	mutex_init(&stream->mutex);
	INIT_LIST_HEAD(&stream->strm_list);
	init_रुकोqueue_head(&stream->रुको);

	/*
	 * We should have a decompressor at least as शेष
	 * so अगर we fail to allocate new decompressor dynamically,
	 * we could always fall back to शेष decompressor and
	 * file प्रणाली works.
	 */
	decomp_strm = kदो_स्मृति(माप(*decomp_strm), GFP_KERNEL);
	अगर (!decomp_strm)
		जाओ out;

	decomp_strm->stream = msblk->decompressor->init(msblk,
						stream->comp_opts);
	अगर (IS_ERR(decomp_strm->stream)) अणु
		err = PTR_ERR(decomp_strm->stream);
		जाओ out;
	पूर्ण

	list_add(&decomp_strm->list, &stream->strm_list);
	stream->avail_decomp = 1;
	वापस stream;

out:
	kमुक्त(decomp_strm);
	kमुक्त(stream);
	वापस ERR_PTR(err);
पूर्ण


व्योम squashfs_decompressor_destroy(काष्ठा squashfs_sb_info *msblk)
अणु
	काष्ठा squashfs_stream *stream = msblk->stream;
	अगर (stream) अणु
		काष्ठा decomp_stream *decomp_strm;

		जबतक (!list_empty(&stream->strm_list)) अणु
			decomp_strm = list_entry(stream->strm_list.prev,
						काष्ठा decomp_stream, list);
			list_del(&decomp_strm->list);
			msblk->decompressor->मुक्त(decomp_strm->stream);
			kमुक्त(decomp_strm);
			stream->avail_decomp--;
		पूर्ण
		WARN_ON(stream->avail_decomp);
		kमुक्त(stream->comp_opts);
		kमुक्त(stream);
	पूर्ण
पूर्ण


अटल काष्ठा decomp_stream *get_decomp_stream(काष्ठा squashfs_sb_info *msblk,
					काष्ठा squashfs_stream *stream)
अणु
	काष्ठा decomp_stream *decomp_strm;

	जबतक (1) अणु
		mutex_lock(&stream->mutex);

		/* There is available decomp_stream */
		अगर (!list_empty(&stream->strm_list)) अणु
			decomp_strm = list_entry(stream->strm_list.prev,
				काष्ठा decomp_stream, list);
			list_del(&decomp_strm->list);
			mutex_unlock(&stream->mutex);
			अवरोध;
		पूर्ण

		/*
		 * If there is no available decomp and alपढ़ोy full,
		 * let's रुको क्रम releasing decomp from other users.
		 */
		अगर (stream->avail_decomp >= MAX_DECOMPRESSOR)
			जाओ रुको;

		/* Let's allocate new decomp */
		decomp_strm = kदो_स्मृति(माप(*decomp_strm), GFP_KERNEL);
		अगर (!decomp_strm)
			जाओ रुको;

		decomp_strm->stream = msblk->decompressor->init(msblk,
						stream->comp_opts);
		अगर (IS_ERR(decomp_strm->stream)) अणु
			kमुक्त(decomp_strm);
			जाओ रुको;
		पूर्ण

		stream->avail_decomp++;
		WARN_ON(stream->avail_decomp > MAX_DECOMPRESSOR);

		mutex_unlock(&stream->mutex);
		अवरोध;
रुको:
		/*
		 * If प्रणाली memory is tough, let's for other's
		 * releasing instead of hurting VM because it could
		 * make page cache thrashing.
		 */
		mutex_unlock(&stream->mutex);
		रुको_event(stream->रुको,
			!list_empty(&stream->strm_list));
	पूर्ण

	वापस decomp_strm;
पूर्ण


पूर्णांक squashfs_decompress(काष्ठा squashfs_sb_info *msblk, काष्ठा bio *bio,
			पूर्णांक offset, पूर्णांक length,
			काष्ठा squashfs_page_actor *output)
अणु
	पूर्णांक res;
	काष्ठा squashfs_stream *stream = msblk->stream;
	काष्ठा decomp_stream *decomp_stream = get_decomp_stream(msblk, stream);
	res = msblk->decompressor->decompress(msblk, decomp_stream->stream,
		bio, offset, length, output);
	put_decomp_stream(decomp_stream, stream);
	अगर (res < 0)
		ERROR("%s decompression failed, data probably corrupt\n",
			msblk->decompressor->name);
	वापस res;
पूर्ण
