<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _MALIDP_IO_H_
#घोषणा _MALIDP_IO_H_

#समावेश <linux/पन.स>

अटल अंतरभूत u32
malidp_पढ़ो32(u32 __iomem *base, u32 offset)
अणु
	वापस पढ़ोl((base + (offset >> 2)));
पूर्ण

अटल अंतरभूत व्योम
malidp_ग_लिखो32(u32 __iomem *base, u32 offset, u32 v)
अणु
	ग_लिखोl(v, (base + (offset >> 2)));
पूर्ण

अटल अंतरभूत व्योम
malidp_ग_लिखो64(u32 __iomem *base, u32 offset, u64 v)
अणु
	ग_लिखोl(lower_32_bits(v), (base + (offset >> 2)));
	ग_लिखोl(upper_32_bits(v), (base + (offset >> 2) + 1));
पूर्ण

अटल अंतरभूत व्योम
malidp_ग_लिखो32_mask(u32 __iomem *base, u32 offset, u32 m, u32 v)
अणु
	u32 पंचांगp = malidp_पढ़ो32(base, offset);

	पंचांगp &= (~m);
	malidp_ग_लिखो32(base, offset, v | पंचांगp);
पूर्ण

अटल अंतरभूत व्योम
malidp_ग_लिखो_group(u32 __iomem *base, u32 offset, पूर्णांक num, स्थिर u32 *values)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		malidp_ग_लिखो32(base, offset + i * 4, values[i]);
पूर्ण

#पूर्ण_अगर /*_MALIDP_IO_H_*/
