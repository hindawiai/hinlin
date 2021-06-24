<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I/O access functions क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <यंत्र/पन.स>

/*  These are all FIFO routines!  */

/*
 * __raw_पढ़ोsw - पढ़ो words a लघु at a समय
 * @addr:  source address
 * @data:  data address
 * @len: number of लघुs to पढ़ो
 */
व्योम __raw_पढ़ोsw(स्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक len)
अणु
	स्थिर अस्थिर लघु पूर्णांक *src = (लघु पूर्णांक *) addr;
	लघु पूर्णांक *dst = (लघु पूर्णांक *) data;

	अगर ((u32)data & 0x1)
		panic("unaligned pointer to readsw");

	जबतक (len-- > 0)
		*dst++ = *src;

पूर्ण

/*
 * __raw_ग_लिखोsw - पढ़ो words a लघु at a समय
 * @addr:  source address
 * @data:  data address
 * @len: number of लघुs to पढ़ो
 */
व्योम __raw_ग_लिखोsw(व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक len)
अणु
	स्थिर लघु पूर्णांक *src = (लघु पूर्णांक *)data;
	अस्थिर लघु पूर्णांक *dst = (लघु पूर्णांक *)addr;

	अगर ((u32)data & 0x1)
		panic("unaligned pointer to writesw");

	जबतक (len-- > 0)
		*dst = *src++;


पूर्ण

/*  Pretty sure len is pre-adjusted क्रम the length of the access alपढ़ोy */
व्योम __raw_पढ़ोsl(स्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक len)
अणु
	स्थिर अस्थिर दीर्घ *src = (दीर्घ *) addr;
	दीर्घ *dst = (दीर्घ *) data;

	अगर ((u32)data & 0x3)
		panic("unaligned pointer to readsl");

	जबतक (len-- > 0)
		*dst++ = *src;


पूर्ण

व्योम __raw_ग_लिखोsl(व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक len)
अणु
	स्थिर दीर्घ *src = (दीर्घ *)data;
	अस्थिर दीर्घ *dst = (दीर्घ *)addr;

	अगर ((u32)data & 0x3)
		panic("unaligned pointer to writesl");

	जबतक (len-- > 0)
		*dst = *src++;


पूर्ण
