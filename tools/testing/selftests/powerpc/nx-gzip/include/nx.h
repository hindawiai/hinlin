<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2020 IBM Corp.
 *
 */
#अगर_अघोषित _NX_H
#घोषणा _NX_H

#समावेश <stdbool.h>

#घोषणा	NX_FUNC_COMP_842	1
#घोषणा NX_FUNC_COMP_GZIP	2

#अगर_अघोषित __aligned
#घोषणा __aligned(x)	__attribute__((aligned(x)))
#पूर्ण_अगर

काष्ठा nx842_func_args अणु
	bool use_crc;
	bool decompress;		/* true decompress; false compress */
	bool move_data;
	पूर्णांक समयout;			/* seconds */
पूर्ण;

काष्ठा nxbuf_t अणु
	पूर्णांक len;
	अक्षर *buf;
पूर्ण;

/* @function should be EFT (aka 842), GZIP etc */
व्योम *nx_function_begin(पूर्णांक function, पूर्णांक pri);

पूर्णांक nx_function(व्योम *handle, काष्ठा nxbuf_t *in, काष्ठा nxbuf_t *out,
		व्योम *arg);

पूर्णांक nx_function_end(व्योम *handle);

#पूर्ण_अगर	/* _NX_H */
