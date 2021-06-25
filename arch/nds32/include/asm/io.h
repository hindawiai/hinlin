<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASM_NDS32_IO_H
#घोषणा __ASM_NDS32_IO_H

#समावेश <linux/types.h>

#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb
अटल अंतरभूत व्योम __raw_ग_लिखोb(u8 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("sbi %0, [%1]" : : "r" (val), "r" (addr));
पूर्ण

#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw
अटल अंतरभूत व्योम __raw_ग_लिखोw(u16 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("shi %0, [%1]" : : "r" (val), "r" (addr));
पूर्ण

#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl
अटल अंतरभूत व्योम __raw_ग_लिखोl(u32 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("swi %0, [%1]" : : "r" (val), "r" (addr));
पूर्ण

#घोषणा __raw_पढ़ोb __raw_पढ़ोb
अटल अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 val;

	यंत्र अस्थिर("lbi %0, [%1]" : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोw __raw_पढ़ोw
अटल अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val;

	यंत्र अस्थिर("lhi %0, [%1]" : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोl __raw_पढ़ोl
अटल अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val;

	यंत्र अस्थिर("lwi %0, [%1]" : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __iormb()               rmb()
#घोषणा __iowmb()               wmb()

/*
 * अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण_relaxed() are like the regular version, but
 * are not guaranteed to provide ordering against spinlocks or memory
 * accesses.
 */

#घोषणा पढ़ोb_relaxed(c)	(अणु u8  __v = __raw_पढ़ोb(c); __v; पूर्ण)
#घोषणा पढ़ोw_relaxed(c)	(अणु u16 __v = le16_to_cpu((__क्रमce __le16)__raw_पढ़ोw(c)); __v; पूर्ण)
#घोषणा पढ़ोl_relaxed(c)	(अणु u32 __v = le32_to_cpu((__क्रमce __le32)__raw_पढ़ोl(c)); __v; पूर्ण)
#घोषणा ग_लिखोb_relaxed(v,c)	((व्योम)__raw_ग_लिखोb((v),(c)))
#घोषणा ग_लिखोw_relaxed(v,c)	((व्योम)__raw_ग_लिखोw((__क्रमce u16)cpu_to_le16(v),(c)))
#घोषणा ग_लिखोl_relaxed(v,c)	((व्योम)__raw_ग_लिखोl((__क्रमce u32)cpu_to_le32(v),(c)))

/*
 * अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण() access little endian memory and वापस result in
 * native endianness.
 */
#घोषणा पढ़ोb(c)	(अणु u8  __v = पढ़ोb_relaxed(c); __iormb(); __v; पूर्ण)
#घोषणा पढ़ोw(c)	(अणु u16 __v = पढ़ोw_relaxed(c); __iormb(); __v; पूर्ण)
#घोषणा पढ़ोl(c)	(अणु u32 __v = पढ़ोl_relaxed(c); __iormb(); __v; पूर्ण)

#घोषणा ग_लिखोb(v,c)	(अणु __iowmb(); ग_लिखोb_relaxed((v),(c)); पूर्ण)
#घोषणा ग_लिखोw(v,c)	(अणु __iowmb(); ग_लिखोw_relaxed((v),(c)); पूर्ण)
#घोषणा ग_लिखोl(v,c)	(अणु __iowmb(); ग_लिखोl_relaxed((v),(c)); पूर्ण)

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर /* __ASM_NDS32_IO_H */
