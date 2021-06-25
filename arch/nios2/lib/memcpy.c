<शैली गुरु>
/* Extracted from GLIBC स_नकल.c and memcopy.h, which is:
   Copyright (C) 1991, 1992, 1993, 1997, 2004 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Torbjorn Granlund (tege@sics.se).

   The GNU C Library is मुक्त software; you can redistribute it and/or
   modअगरy it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License क्रम more details.

   You should have received a copy of the GNU Lesser General Public
   License aदीर्घ with the GNU C Library; अगर not, see
   <http://www.gnu.org/licenses/>.  */

#समावेश <linux/types.h>

/* Type to use क्रम aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  */
#घोषणा	op_t	अचिन्हित दीर्घ पूर्णांक
#घोषणा OPSIZ	(माप(op_t))

/* Optimal type क्रम storing bytes in रेजिस्टरs.  */
#घोषणा	reg_अक्षर	अक्षर

#घोषणा MERGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))

/* Copy exactly NBYTES bytes from SRC_BP to DST_BP,
   without any assumptions about alignment of the poपूर्णांकers.  */
#घोषणा BYTE_COPY_FWD(dst_bp, src_bp, nbytes)				\
करो अणु									\
	माप_प्रकार __nbytes = (nbytes);					\
	जबतक (__nbytes > 0) अणु						\
		अचिन्हित अक्षर __x = ((अचिन्हित अक्षर *) src_bp)[0];	\
		src_bp += 1;						\
		__nbytes -= 1;						\
		((अचिन्हित अक्षर *) dst_bp)[0] = __x;			\
		dst_bp += 1;						\
	पूर्ण								\
पूर्ण जबतक (0)

/* Copy *up to* NBYTES bytes from SRC_BP to DST_BP, with
   the assumption that DST_BP is aligned on an OPSIZ multiple.  If
   not all bytes could be easily copied, store reमुख्यing number of bytes
   in NBYTES_LEFT, otherwise store 0.  */
/* बाह्य व्योम _wordcopy_fwd_aligned __P ((दीर्घ पूर्णांक, दीर्घ पूर्णांक, माप_प्रकार)); */
/* बाह्य व्योम _wordcopy_fwd_dest_aligned __P ((दीर्घ पूर्णांक, दीर्घ पूर्णांक, माप_प्रकार)); */
#घोषणा WORD_COPY_FWD(dst_bp, src_bp, nbytes_left, nbytes)		\
करो अणु									\
	अगर (src_bp % OPSIZ == 0)					\
		_wordcopy_fwd_aligned(dst_bp, src_bp, (nbytes) / OPSIZ);\
	अन्यथा								\
		_wordcopy_fwd_dest_aligned(dst_bp, src_bp, (nbytes) / OPSIZ);\
	src_bp += (nbytes) & -OPSIZ;					\
	dst_bp += (nbytes) & -OPSIZ;					\
	(nbytes_left) = (nbytes) % OPSIZ;				\
पूर्ण जबतक (0)


/* Threshold value क्रम when to enter the unrolled loops.  */
#घोषणा	OP_T_THRES	16

/* _wordcopy_fwd_aligned -- Copy block beginning at SRCP to
   block beginning at DSTP with LEN `op_t' words (not LEN bytes!).
   Both SRCP and DSTP should be aligned क्रम memory operations on `op_t's.  */
/* stream-lined (पढ़ो x8 + ग_लिखो x8) */
अटल व्योम _wordcopy_fwd_aligned(दीर्घ पूर्णांक dstp, दीर्घ पूर्णांक srcp, माप_प्रकार len)
अणु
	जबतक (len > 7) अणु
		रेजिस्टर op_t a0, a1, a2, a3, a4, a5, a6, a7;

		a0 = ((op_t *) srcp)[0];
		a1 = ((op_t *) srcp)[1];
		a2 = ((op_t *) srcp)[2];
		a3 = ((op_t *) srcp)[3];
		a4 = ((op_t *) srcp)[4];
		a5 = ((op_t *) srcp)[5];
		a6 = ((op_t *) srcp)[6];
		a7 = ((op_t *) srcp)[7];
		((op_t *) dstp)[0] = a0;
		((op_t *) dstp)[1] = a1;
		((op_t *) dstp)[2] = a2;
		((op_t *) dstp)[3] = a3;
		((op_t *) dstp)[4] = a4;
		((op_t *) dstp)[5] = a5;
		((op_t *) dstp)[6] = a6;
		((op_t *) dstp)[7] = a7;

		srcp += 8 * OPSIZ;
		dstp += 8 * OPSIZ;
		len -= 8;
	पूर्ण
	जबतक (len > 0) अणु
		*(op_t *)dstp = *(op_t *)srcp;

		srcp += OPSIZ;
		dstp += OPSIZ;
		len -= 1;
	पूर्ण
पूर्ण

/* _wordcopy_fwd_dest_aligned -- Copy block beginning at SRCP to
   block beginning at DSTP with LEN `op_t' words (not LEN bytes!).
   DSTP should be aligned क्रम memory operations on `op_t's, but SRCP must
   *not* be aligned.  */
/* stream-lined (पढ़ो x4 + ग_लिखो x4) */
अटल व्योम _wordcopy_fwd_dest_aligned(दीर्घ पूर्णांक dstp, दीर्घ पूर्णांक srcp,
					माप_प्रकार len)
अणु
	op_t ap;
	पूर्णांक sh_1, sh_2;

	/* Calculate how to shअगरt a word पढ़ो at the memory operation
	aligned srcp to make it aligned क्रम copy. */

	sh_1 = 8 * (srcp % OPSIZ);
	sh_2 = 8 * OPSIZ - sh_1;

	/* Make SRCP aligned by rounding it करोwn to the beginning of the `op_t'
	it poपूर्णांकs in the middle of. */
	srcp &= -OPSIZ;
	ap = ((op_t *) srcp)[0];
	srcp += OPSIZ;

	जबतक (len > 3) अणु
		op_t a0, a1, a2, a3;

		a0 = ((op_t *) srcp)[0];
		a1 = ((op_t *) srcp)[1];
		a2 = ((op_t *) srcp)[2];
		a3 = ((op_t *) srcp)[3];
		((op_t *) dstp)[0] = MERGE(ap, sh_1, a0, sh_2);
		((op_t *) dstp)[1] = MERGE(a0, sh_1, a1, sh_2);
		((op_t *) dstp)[2] = MERGE(a1, sh_1, a2, sh_2);
		((op_t *) dstp)[3] = MERGE(a2, sh_1, a3, sh_2);

		ap = a3;
		srcp += 4 * OPSIZ;
		dstp += 4 * OPSIZ;
		len -= 4;
	पूर्ण
	जबतक (len > 0) अणु
		रेजिस्टर op_t a0;

		a0 = ((op_t *) srcp)[0];
		((op_t *) dstp)[0] = MERGE(ap, sh_1, a0, sh_2);

		ap = a0;
		srcp += OPSIZ;
		dstp += OPSIZ;
		len -= 1;
	पूर्ण
पूर्ण

व्योम *स_नकल(व्योम *dstpp, स्थिर व्योम *srcpp, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ पूर्णांक dstp = (दीर्घ पूर्णांक) dstpp;
	अचिन्हित दीर्घ पूर्णांक srcp = (दीर्घ पूर्णांक) srcpp;

	/* Copy from the beginning to the end.  */

	/* If there not too few bytes to copy, use word copy.  */
	अगर (len >= OP_T_THRES) अणु
		/* Copy just a few bytes to make DSTP aligned.  */
		len -= (-dstp) % OPSIZ;
		BYTE_COPY_FWD(dstp, srcp, (-dstp) % OPSIZ);

		/* Copy whole pages from SRCP to DSTP by भव address
		   manipulation, as much as possible.  */

		/* PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len); */

		/* Copy from SRCP to DSTP taking advantage of the known
		   alignment of DSTP. Number of bytes reमुख्यing is put in the
		   third argument, i.e. in LEN.  This number may vary from
		   machine to machine. */

		WORD_COPY_FWD(dstp, srcp, len, len);

		/* Fall out and copy the tail. */
	पूर्ण

	/* There are just a few bytes to copy.  Use byte memory operations. */
	BYTE_COPY_FWD(dstp, srcp, len);

	वापस dstpp;
पूर्ण

व्योम *स_नकलb(व्योम *dstpp, स्थिर व्योम *srcpp, अचिन्हित len)
अणु
	अचिन्हित दीर्घ पूर्णांक dstp = (दीर्घ पूर्णांक) dstpp;
	अचिन्हित दीर्घ पूर्णांक srcp = (दीर्घ पूर्णांक) srcpp;

	BYTE_COPY_FWD(dstp, srcp, len);

	वापस dstpp;
पूर्ण
