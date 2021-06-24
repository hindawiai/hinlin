<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ppp-comp.h - Definitions क्रम करोing PPP packet compression.
 *
 * Copyright 1994-1998 Paul Mackerras.
 */
#अगर_अघोषित _NET_PPP_COMP_H
#घोषणा _NET_PPP_COMP_H

#समावेश <uapi/linux/ppp-comp.h>


काष्ठा module;

/*
 * The following symbols control whether we include code क्रम
 * various compression methods.
 */

#अगर_अघोषित DO_BSD_COMPRESS
#घोषणा DO_BSD_COMPRESS	1	/* by शेष, include BSD-Compress */
#पूर्ण_अगर
#अगर_अघोषित DO_DEFLATE
#घोषणा DO_DEFLATE	1	/* by शेष, include Deflate */
#पूर्ण_अगर
#घोषणा DO_PREDICTOR_1	0
#घोषणा DO_PREDICTOR_2	0

/*
 * Structure giving methods क्रम compression/decompression.
 */

काष्ठा compressor अणु
	पूर्णांक	compress_proto;	/* CCP compression protocol number */

	/* Allocate space क्रम a compressor (transmit side) */
	व्योम	*(*comp_alloc) (अचिन्हित अक्षर *options, पूर्णांक opt_len);

	/* Free space used by a compressor */
	व्योम	(*comp_मुक्त) (व्योम *state);

	/* Initialize a compressor */
	पूर्णांक	(*comp_init) (व्योम *state, अचिन्हित अक्षर *options,
			      पूर्णांक opt_len, पूर्णांक unit, पूर्णांक opthdr, पूर्णांक debug);

	/* Reset a compressor */
	व्योम	(*comp_reset) (व्योम *state);

	/* Compress a packet */
	पूर्णांक     (*compress) (व्योम *state, अचिन्हित अक्षर *rptr,
			      अचिन्हित अक्षर *obuf, पूर्णांक isize, पूर्णांक osize);

	/* Return compression statistics */
	व्योम	(*comp_stat) (व्योम *state, काष्ठा compstat *stats);

	/* Allocate space क्रम a decompressor (receive side) */
	व्योम	*(*decomp_alloc) (अचिन्हित अक्षर *options, पूर्णांक opt_len);

	/* Free space used by a decompressor */
	व्योम	(*decomp_मुक्त) (व्योम *state);

	/* Initialize a decompressor */
	पूर्णांक	(*decomp_init) (व्योम *state, अचिन्हित अक्षर *options,
				पूर्णांक opt_len, पूर्णांक unit, पूर्णांक opthdr, पूर्णांक mru,
				पूर्णांक debug);

	/* Reset a decompressor */
	व्योम	(*decomp_reset) (व्योम *state);

	/* Decompress a packet. */
	पूर्णांक	(*decompress) (व्योम *state, अचिन्हित अक्षर *ibuf, पूर्णांक isize,
				अचिन्हित अक्षर *obuf, पूर्णांक osize);

	/* Update state क्रम an incompressible packet received */
	व्योम	(*incomp) (व्योम *state, अचिन्हित अक्षर *ibuf, पूर्णांक icnt);

	/* Return decompression statistics */
	व्योम	(*decomp_stat) (व्योम *state, काष्ठा compstat *stats);

	/* Used in locking compressor modules */
	काष्ठा module *owner;
	/* Extra skb space needed by the compressor algorithm */
	अचिन्हित पूर्णांक comp_extra;
पूर्ण;

/*
 * The वापस value from decompress routine is the length of the
 * decompressed packet अगर successful, otherwise DECOMP_ERROR
 * or DECOMP_FATALERROR अगर an error occurred.
 * 
 * We need to make this distinction so that we can disable certain
 * useful functionality, namely sending a CCP reset-request as a result
 * of an error detected after decompression.  This is to aव्योम infringing
 * a patent held by Motorola.
 * Don't you just lurve software patents.
 */

#घोषणा DECOMP_ERROR		-1	/* error detected beक्रमe decomp. */
#घोषणा DECOMP_FATALERROR	-2	/* error detected after decomp. */

बाह्य पूर्णांक ppp_रेजिस्टर_compressor(काष्ठा compressor *);
बाह्य व्योम ppp_unरेजिस्टर_compressor(काष्ठा compressor *);
#पूर्ण_अगर /* _NET_PPP_COMP_H */
