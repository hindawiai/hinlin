<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IO_64_NONATOMIC_LO_HI_H_
#घोषणा _LINUX_IO_64_NONATOMIC_LO_HI_H_

#समावेश <linux/पन.स>
#समावेश <यंत्र-generic/पूर्णांक-ll64.h>

अटल अंतरभूत __u64 lo_hi_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	स्थिर अस्थिर u32 __iomem *p = addr;
	u32 low, high;

	low = पढ़ोl(p);
	high = पढ़ोl(p + 1);

	वापस low + ((u64)high << 32);
पूर्ण

अटल अंतरभूत व्योम lo_hi_ग_लिखोq(__u64 val, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr);
	ग_लिखोl(val >> 32, addr + 4);
पूर्ण

अटल अंतरभूत __u64 lo_hi_पढ़ोq_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	स्थिर अस्थिर u32 __iomem *p = addr;
	u32 low, high;

	low = पढ़ोl_relaxed(p);
	high = पढ़ोl_relaxed(p + 1);

	वापस low + ((u64)high << 32);
पूर्ण

अटल अंतरभूत व्योम lo_hi_ग_लिखोq_relaxed(__u64 val, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोl_relaxed(val, addr);
	ग_लिखोl_relaxed(val >> 32, addr + 4);
पूर्ण

#अगर_अघोषित पढ़ोq
#घोषणा पढ़ोq lo_hi_पढ़ोq
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोq
#घोषणा ग_लिखोq lo_hi_ग_लिखोq
#पूर्ण_अगर

#अगर_अघोषित पढ़ोq_relaxed
#घोषणा पढ़ोq_relaxed lo_hi_पढ़ोq_relaxed
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोq_relaxed
#घोषणा ग_लिखोq_relaxed lo_hi_ग_लिखोq_relaxed
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो64_lo_hi
#घोषणा ioपढ़ो64_lo_hi ioपढ़ो64_lo_hi
अटल अंतरभूत u64 ioपढ़ो64_lo_hi(स्थिर व्योम __iomem *addr)
अणु
	u32 low, high;

	low = ioपढ़ो32(addr);
	high = ioपढ़ो32(addr + माप(u32));

	वापस low + ((u64)high << 32);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो64_lo_hi
#घोषणा ioग_लिखो64_lo_hi ioग_लिखो64_lo_hi
अटल अंतरभूत व्योम ioग_लिखो64_lo_hi(u64 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32(val, addr);
	ioग_लिखो32(val >> 32, addr + माप(u32));
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो64be_lo_hi
#घोषणा ioपढ़ो64be_lo_hi ioपढ़ो64be_lo_hi
अटल अंतरभूत u64 ioपढ़ो64be_lo_hi(स्थिर व्योम __iomem *addr)
अणु
	u32 low, high;

	low = ioपढ़ो32be(addr + माप(u32));
	high = ioपढ़ो32be(addr);

	वापस low + ((u64)high << 32);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो64be_lo_hi
#घोषणा ioग_लिखो64be_lo_hi ioग_लिखो64be_lo_hi
अटल अंतरभूत व्योम ioग_लिखो64be_lo_hi(u64 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32be(val, addr + माप(u32));
	ioग_लिखो32be(val >> 32, addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो64
#घोषणा ioपढ़ो64_is_nonatomic
#घोषणा ioपढ़ो64 ioपढ़ो64_lo_hi
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो64
#घोषणा ioग_लिखो64_is_nonatomic
#घोषणा ioग_लिखो64 ioग_लिखो64_lo_hi
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो64be
#घोषणा ioपढ़ो64be_is_nonatomic
#घोषणा ioपढ़ो64be ioपढ़ो64be_lo_hi
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो64be
#घोषणा ioग_लिखो64be_is_nonatomic
#घोषणा ioग_लिखो64be ioग_लिखो64be_lo_hi
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_IO_64_NONATOMIC_LO_HI_H_ */
