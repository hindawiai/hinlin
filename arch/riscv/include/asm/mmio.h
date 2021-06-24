<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण based on arch/arm64/include/यंत्र/पन.स
 *   which was based on arch/arm/include/पन.स
 *
 * Copyright (C) 1996-2000 Russell King
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2014 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_MMIO_H
#घोषणा _ASM_RISCV_MMIO_H

#समावेश <linux/types.h>
#समावेश <यंत्र/mmiowb.h>

/* Generic IO पढ़ो/ग_लिखो.  These perक्रमm native-endian accesses. */
#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb
अटल अंतरभूत व्योम __raw_ग_लिखोb(u8 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("sb %0, 0(%1)" : : "r" (val), "r" (addr));
पूर्ण

#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw
अटल अंतरभूत व्योम __raw_ग_लिखोw(u16 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("sh %0, 0(%1)" : : "r" (val), "r" (addr));
पूर्ण

#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl
अटल अंतरभूत व्योम __raw_ग_लिखोl(u32 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("sw %0, 0(%1)" : : "r" (val), "r" (addr));
पूर्ण

#अगर_घोषित CONFIG_64BIT
#घोषणा __raw_ग_लिखोq __raw_ग_लिखोq
अटल अंतरभूत व्योम __raw_ग_लिखोq(u64 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("sd %0, 0(%1)" : : "r" (val), "r" (addr));
पूर्ण
#पूर्ण_अगर

#घोषणा __raw_पढ़ोb __raw_पढ़ोb
अटल अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 val;

	यंत्र अस्थिर("lb %0, 0(%1)" : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोw __raw_पढ़ोw
अटल अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val;

	यंत्र अस्थिर("lh %0, 0(%1)" : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोl __raw_पढ़ोl
अटल अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val;

	यंत्र अस्थिर("lw %0, 0(%1)" : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#अगर_घोषित CONFIG_64BIT
#घोषणा __raw_पढ़ोq __raw_पढ़ोq
अटल अंतरभूत u64 __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 val;

	यंत्र अस्थिर("ld %0, 0(%1)" : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण
#पूर्ण_अगर

/*
 * Unordered I/O memory access primitives.  These are even more relaxed than
 * the relaxed versions, as they करोn't even order accesses between successive
 * operations to the I/O regions.
 */
#घोषणा पढ़ोb_cpu(c)		(अणु u8  __r = __raw_पढ़ोb(c); __r; पूर्ण)
#घोषणा पढ़ोw_cpu(c)		(अणु u16 __r = le16_to_cpu((__क्रमce __le16)__raw_पढ़ोw(c)); __r; पूर्ण)
#घोषणा पढ़ोl_cpu(c)		(अणु u32 __r = le32_to_cpu((__क्रमce __le32)__raw_पढ़ोl(c)); __r; पूर्ण)

#घोषणा ग_लिखोb_cpu(v, c)	((व्योम)__raw_ग_लिखोb((v), (c)))
#घोषणा ग_लिखोw_cpu(v, c)	((व्योम)__raw_ग_लिखोw((__क्रमce u16)cpu_to_le16(v), (c)))
#घोषणा ग_लिखोl_cpu(v, c)	((व्योम)__raw_ग_लिखोl((__क्रमce u32)cpu_to_le32(v), (c)))

#अगर_घोषित CONFIG_64BIT
#घोषणा पढ़ोq_cpu(c)		(अणु u64 __r = le64_to_cpu((__क्रमce __le64)__raw_पढ़ोq(c)); __r; पूर्ण)
#घोषणा ग_लिखोq_cpu(v, c)	((व्योम)__raw_ग_लिखोq((__क्रमce u64)cpu_to_le64(v), (c)))
#पूर्ण_अगर

/*
 * Relaxed I/O memory access primitives. These follow the Device memory
 * ordering rules but करो not guarantee any ordering relative to Normal memory
 * accesses.  These are defined to order the indicated access (either a पढ़ो or
 * ग_लिखो) with all other I/O memory accesses. Since the platक्रमm specअगरication
 * defines that all I/O regions are strongly ordered on channel 2, no explicit
 * fences are required to enक्रमce this ordering.
 */
/* FIXME: These are now the same as यंत्र-generic */
#घोषणा __io_rbr()		करो अणुपूर्ण जबतक (0)
#घोषणा __io_rar()		करो अणुपूर्ण जबतक (0)
#घोषणा __io_rbw()		करो अणुपूर्ण जबतक (0)
#घोषणा __io_raw()		करो अणुपूर्ण जबतक (0)

#घोषणा पढ़ोb_relaxed(c)	(अणु u8  __v; __io_rbr(); __v = पढ़ोb_cpu(c); __io_rar(); __v; पूर्ण)
#घोषणा पढ़ोw_relaxed(c)	(अणु u16 __v; __io_rbr(); __v = पढ़ोw_cpu(c); __io_rar(); __v; पूर्ण)
#घोषणा पढ़ोl_relaxed(c)	(अणु u32 __v; __io_rbr(); __v = पढ़ोl_cpu(c); __io_rar(); __v; पूर्ण)

#घोषणा ग_लिखोb_relaxed(v, c)	(अणु __io_rbw(); ग_लिखोb_cpu((v), (c)); __io_raw(); पूर्ण)
#घोषणा ग_लिखोw_relaxed(v, c)	(अणु __io_rbw(); ग_लिखोw_cpu((v), (c)); __io_raw(); पूर्ण)
#घोषणा ग_लिखोl_relaxed(v, c)	(अणु __io_rbw(); ग_लिखोl_cpu((v), (c)); __io_raw(); पूर्ण)

#अगर_घोषित CONFIG_64BIT
#घोषणा पढ़ोq_relaxed(c)	(अणु u64 __v; __io_rbr(); __v = पढ़ोq_cpu(c); __io_rar(); __v; पूर्ण)
#घोषणा ग_लिखोq_relaxed(v, c)	(अणु __io_rbw(); ग_लिखोq_cpu((v), (c)); __io_raw(); पूर्ण)
#पूर्ण_अगर

/*
 * I/O memory access primitives. Reads are ordered relative to any
 * following Normal memory access. Writes are ordered relative to any prior
 * Normal memory access.  The memory barriers here are necessary as RISC-V
 * करोesn't define any ordering between the memory space and the I/O space.
 */
#घोषणा __io_br()	करो अणुपूर्ण जबतक (0)
#घोषणा __io_ar(v)	__यंत्र__ __अस्थिर__ ("fence i,r" : : : "memory")
#घोषणा __io_bw()	__यंत्र__ __अस्थिर__ ("fence w,o" : : : "memory")
#घोषणा __io_aw()	mmiowb_set_pending()

#घोषणा पढ़ोb(c)	(अणु u8  __v; __io_br(); __v = पढ़ोb_cpu(c); __io_ar(__v); __v; पूर्ण)
#घोषणा पढ़ोw(c)	(अणु u16 __v; __io_br(); __v = पढ़ोw_cpu(c); __io_ar(__v); __v; पूर्ण)
#घोषणा पढ़ोl(c)	(अणु u32 __v; __io_br(); __v = पढ़ोl_cpu(c); __io_ar(__v); __v; पूर्ण)

#घोषणा ग_लिखोb(v, c)	(अणु __io_bw(); ग_लिखोb_cpu((v), (c)); __io_aw(); पूर्ण)
#घोषणा ग_लिखोw(v, c)	(अणु __io_bw(); ग_लिखोw_cpu((v), (c)); __io_aw(); पूर्ण)
#घोषणा ग_लिखोl(v, c)	(अणु __io_bw(); ग_लिखोl_cpu((v), (c)); __io_aw(); पूर्ण)

#अगर_घोषित CONFIG_64BIT
#घोषणा पढ़ोq(c)	(अणु u64 __v; __io_br(); __v = पढ़ोq_cpu(c); __io_ar(__v); __v; पूर्ण)
#घोषणा ग_लिखोq(v, c)	(अणु __io_bw(); ग_लिखोq_cpu((v), (c)); __io_aw(); पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_MMIO_H */
