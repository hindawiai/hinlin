<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Trivial implementations of basic i/o routines.  Assumes that all
   of the hard work has been करोne by ioremap and ioporपंचांगap, and that
   access to i/o space is linear.  */

/* This file may be included multiple बार.  */

#अगर IO_CONCAT(__IO_PREFIX,trivial_io_bw)
__EXTERN_INLINE अचिन्हित पूर्णांक
IO_CONCAT(__IO_PREFIX,ioपढ़ो8)(स्थिर व्योम __iomem *a)
अणु
	वापस __kernel_ldbu(*(स्थिर अस्थिर u8 __क्रमce *)a);
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक
IO_CONCAT(__IO_PREFIX,ioपढ़ो16)(स्थिर व्योम __iomem *a)
अणु
	वापस __kernel_ldwu(*(स्थिर अस्थिर u16 __क्रमce *)a);
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ioग_लिखो8)(u8 b, व्योम __iomem *a)
अणु
	__kernel_stb(b, *(अस्थिर u8 __क्रमce *)a);
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ioग_लिखो16)(u16 b, व्योम __iomem *a)
अणु
	__kernel_stw(b, *(अस्थिर u16 __क्रमce *)a);
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_io_lq)
__EXTERN_INLINE अचिन्हित पूर्णांक
IO_CONCAT(__IO_PREFIX,ioपढ़ो32)(स्थिर व्योम __iomem *a)
अणु
	वापस *(स्थिर अस्थिर u32 __क्रमce *)a;
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ioग_लिखो32)(u32 b, व्योम __iomem *a)
अणु
	*(अस्थिर u32 __क्रमce *)a = b;
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_rw_bw) == 1
__EXTERN_INLINE u8
IO_CONCAT(__IO_PREFIX,पढ़ोb)(स्थिर अस्थिर व्योम __iomem *a)
अणु
	वापस __kernel_ldbu(*(स्थिर अस्थिर u8 __क्रमce *)a);
पूर्ण

__EXTERN_INLINE u16
IO_CONCAT(__IO_PREFIX,पढ़ोw)(स्थिर अस्थिर व्योम __iomem *a)
अणु
	वापस __kernel_ldwu(*(स्थिर अस्थिर u16 __क्रमce *)a);
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ग_लिखोb)(u8 b, अस्थिर व्योम __iomem *a)
अणु
	__kernel_stb(b, *(अस्थिर u8 __क्रमce *)a);
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ग_लिखोw)(u16 b, अस्थिर व्योम __iomem *a)
अणु
	__kernel_stw(b, *(अस्थिर u16 __क्रमce *)a);
पूर्ण
#या_अगर IO_CONCAT(__IO_PREFIX,trivial_rw_bw) == 2
__EXTERN_INLINE u8
IO_CONCAT(__IO_PREFIX,पढ़ोb)(स्थिर अस्थिर व्योम __iomem *a)
अणु
	स्थिर व्योम __iomem *addr = (स्थिर व्योम __iomem *)a;
	वापस IO_CONCAT(__IO_PREFIX,ioपढ़ो8)(addr);
पूर्ण

__EXTERN_INLINE u16
IO_CONCAT(__IO_PREFIX,पढ़ोw)(स्थिर अस्थिर व्योम __iomem *a)
अणु
	स्थिर व्योम __iomem *addr = (स्थिर व्योम __iomem *)a;
	वापस IO_CONCAT(__IO_PREFIX,ioपढ़ो16)(addr);
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ग_लिखोb)(u8 b, अस्थिर व्योम __iomem *a)
अणु
	व्योम __iomem *addr = (व्योम __iomem *)a;
	IO_CONCAT(__IO_PREFIX,ioग_लिखो8)(b, addr);
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ग_लिखोw)(u16 b, अस्थिर व्योम __iomem *a)
अणु
	व्योम __iomem *addr = (व्योम __iomem *)a;
	IO_CONCAT(__IO_PREFIX,ioग_लिखो16)(b, addr);
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_rw_lq) == 1
__EXTERN_INLINE u32
IO_CONCAT(__IO_PREFIX,पढ़ोl)(स्थिर अस्थिर व्योम __iomem *a)
अणु
	वापस *(स्थिर अस्थिर u32 __क्रमce *)a;
पूर्ण

__EXTERN_INLINE u64
IO_CONCAT(__IO_PREFIX,पढ़ोq)(स्थिर अस्थिर व्योम __iomem *a)
अणु
	वापस *(स्थिर अस्थिर u64 __क्रमce *)a;
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ग_लिखोl)(u32 b, अस्थिर व्योम __iomem *a)
अणु
	*(अस्थिर u32 __क्रमce *)a = b;
पूर्ण

__EXTERN_INLINE व्योम
IO_CONCAT(__IO_PREFIX,ग_लिखोq)(u64 b, अस्थिर व्योम __iomem *a)
अणु
	*(अस्थिर u64 __क्रमce *)a = b;
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_iounmap)
__EXTERN_INLINE व्योम IO_CONCAT(__IO_PREFIX,iounmap)(अस्थिर व्योम __iomem *a)
अणु
पूर्ण
#पूर्ण_अगर
