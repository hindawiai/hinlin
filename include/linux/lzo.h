<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LZO_H__
#घोषणा __LZO_H__
/*
 *  LZO Public Kernel Interface
 *  A mini subset of the LZO real-समय data compression library
 *
 *  Copyright (C) 1996-2012 Markus F.X.J. Oberhumer <markus@oberhumer.com>
 *
 *  The full LZO package can be found at:
 *  http://www.oberhumer.com/खोलोsource/lzo/
 *
 *  Changed क्रम Linux kernel use by:
 *  Nitin Gupta <nitingupta910@gmail.com>
 *  Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#घोषणा LZO1X_1_MEM_COMPRESS	(8192 * माप(अचिन्हित लघु))
#घोषणा LZO1X_MEM_COMPRESS	LZO1X_1_MEM_COMPRESS

#घोषणा lzo1x_worst_compress(x) ((x) + ((x) / 16) + 64 + 3 + 2)

/* This requires 'wrkmem' of size LZO1X_1_MEM_COMPRESS */
पूर्णांक lzo1x_1_compress(स्थिर अचिन्हित अक्षर *src, माप_प्रकार src_len,
		     अचिन्हित अक्षर *dst, माप_प्रकार *dst_len, व्योम *wrkmem);

/* This requires 'wrkmem' of size LZO1X_1_MEM_COMPRESS */
पूर्णांक lzorle1x_1_compress(स्थिर अचिन्हित अक्षर *src, माप_प्रकार src_len,
		     अचिन्हित अक्षर *dst, माप_प्रकार *dst_len, व्योम *wrkmem);

/* safe decompression with overrun testing */
पूर्णांक lzo1x_decompress_safe(स्थिर अचिन्हित अक्षर *src, माप_प्रकार src_len,
			  अचिन्हित अक्षर *dst, माप_प्रकार *dst_len);

/*
 * Return values (< 0 = Error)
 */
#घोषणा LZO_E_OK			0
#घोषणा LZO_E_ERROR			(-1)
#घोषणा LZO_E_OUT_OF_MEMORY		(-2)
#घोषणा LZO_E_NOT_COMPRESSIBLE		(-3)
#घोषणा LZO_E_INPUT_OVERRUN		(-4)
#घोषणा LZO_E_OUTPUT_OVERRUN		(-5)
#घोषणा LZO_E_LOOKBEHIND_OVERRUN	(-6)
#घोषणा LZO_E_खातापूर्ण_NOT_FOUND		(-7)
#घोषणा LZO_E_INPUT_NOT_CONSUMED	(-8)
#घोषणा LZO_E_NOT_YET_IMPLEMENTED	(-9)
#घोषणा LZO_E_INVALID_ARGUMENT		(-10)

#पूर्ण_अगर
