<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ___ASM_SPARC_IO_H
#घोषणा ___ASM_SPARC_IO_H
#अगर defined(__sparc__) && defined(__arch64__)
#समावेश <यंत्र/io_64.h>
#अन्यथा
#समावेश <यंत्र/io_32.h>
#पूर्ण_अगर

/*
 * Defines used क्रम both SPARC32 and SPARC64
 */

/* Big endian versions of memory पढ़ो/ग_लिखो routines */
#घोषणा पढ़ोb_be(__addr)	__raw_पढ़ोb(__addr)
#घोषणा पढ़ोw_be(__addr)	__raw_पढ़ोw(__addr)
#घोषणा पढ़ोl_be(__addr)	__raw_पढ़ोl(__addr)
#घोषणा ग_लिखोb_be(__b, __addr)	__raw_ग_लिखोb(__b, __addr)
#घोषणा ग_लिखोl_be(__w, __addr)	__raw_ग_लिखोl(__w, __addr)
#घोषणा ग_लिखोw_be(__l, __addr)	__raw_ग_लिखोw(__l, __addr)

#पूर्ण_अगर
