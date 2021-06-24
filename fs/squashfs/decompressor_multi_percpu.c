<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013
 * Phillip Lougher <phillip@squashfs.org.uk>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/local_lock.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "decompressor.h"
#समावेश "squashfs.h"

/*
 * This file implements multi-thपढ़ोed decompression using percpu
 * variables, one thपढ़ो per cpu core.
 */

काष्ठा squashfs_stream अणु
	व्योम			*stream;
	local_lock_t	lock;
पूर्ण;

व्योम *squashfs_decompressor_create(काष्ठा squashfs_sb_info *msblk,
						व्योम *comp_opts)
अणु
	काष्ठा squashfs_stream *stream;
	काष्ठा squashfs_stream __percpu *percpu;
	पूर्णांक err, cpu;

	percpu = alloc_percpu(काष्ठा squashfs_stream);
	अगर (percpu == शून्य)
		वापस ERR_PTR(-ENOMEM);

	क्रम_each_possible_cpu(cpu) अणु
		stream = per_cpu_ptr(percpu, cpu);
		stream->stream = msblk->decompressor->init(msblk, comp_opts);
		अगर (IS_ERR(stream->stream)) अणु
			err = PTR_ERR(stream->stream);
			जाओ out;
		पूर्ण
		local_lock_init(&stream->lock);
	पूर्ण

	kमुक्त(comp_opts);
	वापस (__क्रमce व्योम *) percpu;

out:
	क्रम_each_possible_cpu(cpu) अणु
		stream = per_cpu_ptr(percpu, cpu);
		अगर (!IS_ERR_OR_शून्य(stream->stream))
			msblk->decompressor->मुक्त(stream->stream);
	पूर्ण
	मुक्त_percpu(percpu);
	वापस ERR_PTR(err);
पूर्ण

व्योम squashfs_decompressor_destroy(काष्ठा squashfs_sb_info *msblk)
अणु
	काष्ठा squashfs_stream __percpu *percpu =
			(काष्ठा squashfs_stream __percpu *) msblk->stream;
	काष्ठा squashfs_stream *stream;
	पूर्णांक cpu;

	अगर (msblk->stream) अणु
		क्रम_each_possible_cpu(cpu) अणु
			stream = per_cpu_ptr(percpu, cpu);
			msblk->decompressor->मुक्त(stream->stream);
		पूर्ण
		मुक्त_percpu(percpu);
	पूर्ण
पूर्ण

पूर्णांक squashfs_decompress(काष्ठा squashfs_sb_info *msblk, काष्ठा bio *bio,
	पूर्णांक offset, पूर्णांक length, काष्ठा squashfs_page_actor *output)
अणु
	काष्ठा squashfs_stream *stream;
	पूर्णांक res;

	local_lock(&msblk->stream->lock);
	stream = this_cpu_ptr(msblk->stream);

	res = msblk->decompressor->decompress(msblk, stream->stream, bio,
					      offset, length, output);

	local_unlock(&msblk->stream->lock);

	अगर (res < 0)
		ERROR("%s decompression failed, data probably corrupt\n",
			msblk->decompressor->name);

	वापस res;
पूर्ण

पूर्णांक squashfs_max_decompressors(व्योम)
अणु
	वापस num_possible_cpus();
पूर्ण
