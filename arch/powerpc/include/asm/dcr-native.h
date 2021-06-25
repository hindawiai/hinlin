<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (c) Copyright 2006 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#अगर_अघोषित _ASM_POWERPC_DCR_NATIVE_H
#घोषणा _ASM_POWERPC_DCR_NATIVE_H
#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/spinlock.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <linux/stringअगरy.h>

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक base;
पूर्ण dcr_host_native_t;

अटल अंतरभूत bool dcr_map_ok_native(dcr_host_native_t host)
अणु
	वापस true;
पूर्ण

#घोषणा dcr_map_native(dev, dcr_n, dcr_c) \
	((dcr_host_native_t)अणु .base = (dcr_n) पूर्ण)
#घोषणा dcr_unmap_native(host, dcr_c)		करो अणुपूर्ण जबतक (0)
#घोषणा dcr_पढ़ो_native(host, dcr_n)		mfdcr(dcr_n + host.base)
#घोषणा dcr_ग_लिखो_native(host, dcr_n, value)	mtdcr(dcr_n + host.base, value)

/* Table based DCR accessors */
बाह्य व्योम __mtdcr(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
बाह्य अचिन्हित पूर्णांक __mfdcr(अचिन्हित पूर्णांक reg);

/* mfdcrx/mtdcrx inकाष्ठाion based accessors. We hand code
 * the opcodes in order not to depend on newer binutils
 */
अटल अंतरभूत अचिन्हित पूर्णांक mfdcrx(अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक ret;
	यंत्र अस्थिर(".long 0x7c000206 | (%0 << 21) | (%1 << 16)"
		     : "=r" (ret) : "r" (reg));
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम mtdcrx(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	यंत्र अस्थिर(".long 0x7c000306 | (%0 << 21) | (%1 << 16)"
		     : : "r" (val), "r" (reg));
पूर्ण

#घोषणा mfdcr(rn)						\
	(अणुअचिन्हित पूर्णांक rval;					\
	अगर (__builtin_स्थिरant_p(rn) && rn < 1024)		\
		यंत्र अस्थिर("mfdcr %0, %1" : "=r" (rval)	\
			      : "n" (rn));			\
	अन्यथा अगर (likely(cpu_has_feature(CPU_FTR_INDEXED_DCR)))	\
		rval = mfdcrx(rn);				\
	अन्यथा							\
		rval = __mfdcr(rn);				\
	rval;पूर्ण)

#घोषणा mtdcr(rn, v)						\
करो अणु								\
	अगर (__builtin_स्थिरant_p(rn) && rn < 1024)		\
		यंत्र अस्थिर("mtdcr %0, %1"			\
			      : : "n" (rn), "r" (v));		\
	अन्यथा अगर (likely(cpu_has_feature(CPU_FTR_INDEXED_DCR)))	\
		mtdcrx(rn, v);					\
	अन्यथा							\
		__mtdcr(rn, v);					\
पूर्ण जबतक (0)

/* R/W of indirect DCRs make use of standard naming conventions क्रम DCRs */
बाह्य spinlock_t dcr_ind_lock;

अटल अंतरभूत अचिन्हित __mfdcri(पूर्णांक base_addr, पूर्णांक base_data, पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&dcr_ind_lock, flags);
	अगर (cpu_has_feature(CPU_FTR_INDEXED_DCR)) अणु
		mtdcrx(base_addr, reg);
		val = mfdcrx(base_data);
	पूर्ण अन्यथा अणु
		__mtdcr(base_addr, reg);
		val = __mfdcr(base_data);
	पूर्ण
	spin_unlock_irqrestore(&dcr_ind_lock, flags);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम __mtdcri(पूर्णांक base_addr, पूर्णांक base_data, पूर्णांक reg,
			    अचिन्हित val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dcr_ind_lock, flags);
	अगर (cpu_has_feature(CPU_FTR_INDEXED_DCR)) अणु
		mtdcrx(base_addr, reg);
		mtdcrx(base_data, val);
	पूर्ण अन्यथा अणु
		__mtdcr(base_addr, reg);
		__mtdcr(base_data, val);
	पूर्ण
	spin_unlock_irqrestore(&dcr_ind_lock, flags);
पूर्ण

अटल अंतरभूत व्योम __dcri_clrset(पूर्णांक base_addr, पूर्णांक base_data, पूर्णांक reg,
				 अचिन्हित clr, अचिन्हित set)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&dcr_ind_lock, flags);
	अगर (cpu_has_feature(CPU_FTR_INDEXED_DCR)) अणु
		mtdcrx(base_addr, reg);
		val = (mfdcrx(base_data) & ~clr) | set;
		mtdcrx(base_data, val);
	पूर्ण अन्यथा अणु
		__mtdcr(base_addr, reg);
		val = (__mfdcr(base_data) & ~clr) | set;
		__mtdcr(base_data, val);
	पूर्ण
	spin_unlock_irqrestore(&dcr_ind_lock, flags);
पूर्ण

#घोषणा mfdcri(base, reg)	__mfdcri(DCRN_ ## base ## _CONFIG_ADDR,	\
					 DCRN_ ## base ## _CONFIG_DATA,	\
					 reg)

#घोषणा mtdcri(base, reg, data)	__mtdcri(DCRN_ ## base ## _CONFIG_ADDR,	\
					 DCRN_ ## base ## _CONFIG_DATA,	\
					 reg, data)

#घोषणा dcri_clrset(base, reg, clr, set)	__dcri_clrset(DCRN_ ## base ## _CONFIG_ADDR,	\
							      DCRN_ ## base ## _CONFIG_DATA,	\
							      reg, clr, set)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_DCR_NATIVE_H */
