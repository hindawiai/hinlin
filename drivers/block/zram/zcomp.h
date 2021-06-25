<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2014 Sergey Senozhatsky.
 */

#अगर_अघोषित _ZCOMP_H_
#घोषणा _ZCOMP_H_
#समावेश <linux/local_lock.h>

काष्ठा zcomp_strm अणु
	/* The members ->buffer and ->tfm are रक्षित by ->lock. */
	local_lock_t lock;
	/* compression/decompression buffer */
	व्योम *buffer;
	काष्ठा crypto_comp *tfm;
पूर्ण;

/* dynamic per-device compression frontend */
काष्ठा zcomp अणु
	काष्ठा zcomp_strm __percpu *stream;
	स्थिर अक्षर *name;
	काष्ठा hlist_node node;
पूर्ण;

पूर्णांक zcomp_cpu_up_prepare(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node);
पूर्णांक zcomp_cpu_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node);
sमाप_प्रकार zcomp_available_show(स्थिर अक्षर *comp, अक्षर *buf);
bool zcomp_available_algorithm(स्थिर अक्षर *comp);

काष्ठा zcomp *zcomp_create(स्थिर अक्षर *comp);
व्योम zcomp_destroy(काष्ठा zcomp *comp);

काष्ठा zcomp_strm *zcomp_stream_get(काष्ठा zcomp *comp);
व्योम zcomp_stream_put(काष्ठा zcomp *comp);

पूर्णांक zcomp_compress(काष्ठा zcomp_strm *zstrm,
		स्थिर व्योम *src, अचिन्हित पूर्णांक *dst_len);

पूर्णांक zcomp_decompress(काष्ठा zcomp_strm *zstrm,
		स्थिर व्योम *src, अचिन्हित पूर्णांक src_len, व्योम *dst);

bool zcomp_set_max_streams(काष्ठा zcomp *comp, पूर्णांक num_strm);
#पूर्ण_अगर /* _ZCOMP_H_ */
