<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_UPA_H
#घोषणा _SPARC64_UPA_H

#समावेश <यंत्र/asi.h>

/* UPA level रेजिस्टरs and defines. */

/* UPA Config Register */
#घोषणा UPA_CONFIG_RESV		0xffffffffc0000000 /* Reserved.                    */
#घोषणा UPA_CONFIG_PCON		0x000000003fc00000 /* Depth of various sys queues. */
#घोषणा UPA_CONFIG_MID		0x00000000003e0000 /* Module ID.                   */
#घोषणा UPA_CONFIG_PCAP		0x000000000001ffff /* Port Capabilities.           */

/* UPA Port ID Register */
#घोषणा UPA_PORTID_FNP		0xff00000000000000 /* Hardcoded to 0xfc on ultra.  */
#घोषणा UPA_PORTID_RESV		0x00fffff800000000 /* Reserved.                    */
#घोषणा UPA_PORTID_ECCVALID     0x0000000400000000 /* Zero अगर mod can generate ECC */
#घोषणा UPA_PORTID_ONEREAD      0x0000000200000000 /* Set अगर mod generates P_RASB  */
#घोषणा UPA_PORTID_PINTRDQ      0x0000000180000000 /* # outstanding P_INT_REQ's    */
#घोषणा UPA_PORTID_PREQDQ       0x000000007e000000 /* slave-wr's to mod supported  */
#घोषणा UPA_PORTID_PREQRD       0x0000000001e00000 /* # incoming P_REQ's supported */
#घोषणा UPA_PORTID_UPACAP       0x00000000001f0000 /* UPA capabilities of mod      */
#घोषणा UPA_PORTID_ID           0x000000000000ffff /* Module Identअगरication bits  */

/* UPA I/O space accessors */
#अगर defined(__KERNEL__) && !defined(__ASSEMBLY__)
अटल अंतरभूत अचिन्हित अक्षर _upa_पढ़ोb(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर ret;

	__यंत्र__ __अस्थिर__("lduba\t[%1] %2, %0\t/* upa_readb */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित लघु _upa_पढ़ोw(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित लघु ret;

	__यंत्र__ __अस्थिर__("lduha\t[%1] %2, %0\t/* upa_readw */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक _upa_पढ़ोl(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक ret;

	__यंत्र__ __अस्थिर__("lduwa\t[%1] %2, %0\t/* upa_readl */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ _upa_पढ़ोq(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__ __अस्थिर__("ldxa\t[%1] %2, %0\t/* upa_readq */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम _upa_ग_लिखोb(अचिन्हित अक्षर b, अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("stba\t%0, [%1] %2\t/* upa_writeb */"
			     : /* no outमाला_दो */
			     : "r" (b), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

अटल अंतरभूत व्योम _upa_ग_लिखोw(अचिन्हित लघु w, अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("stha\t%0, [%1] %2\t/* upa_writew */"
			     : /* no outमाला_दो */
			     : "r" (w), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

अटल अंतरभूत व्योम _upa_ग_लिखोl(अचिन्हित पूर्णांक l, अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("stwa\t%0, [%1] %2\t/* upa_writel */"
			     : /* no outमाला_दो */
			     : "r" (l), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

अटल अंतरभूत व्योम _upa_ग_लिखोq(अचिन्हित दीर्घ q, अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("stxa\t%0, [%1] %2\t/* upa_writeq */"
			     : /* no outमाला_दो */
			     : "r" (q), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

#घोषणा upa_पढ़ोb(__addr)		(_upa_पढ़ोb((अचिन्हित दीर्घ)(__addr)))
#घोषणा upa_पढ़ोw(__addr)		(_upa_पढ़ोw((अचिन्हित दीर्घ)(__addr)))
#घोषणा upa_पढ़ोl(__addr)		(_upa_पढ़ोl((अचिन्हित दीर्घ)(__addr)))
#घोषणा upa_पढ़ोq(__addr)		(_upa_पढ़ोq((अचिन्हित दीर्घ)(__addr)))
#घोषणा upa_ग_लिखोb(__b, __addr)		(_upa_ग_लिखोb((__b), (अचिन्हित दीर्घ)(__addr)))
#घोषणा upa_ग_लिखोw(__w, __addr)		(_upa_ग_लिखोw((__w), (अचिन्हित दीर्घ)(__addr)))
#घोषणा upa_ग_लिखोl(__l, __addr)		(_upa_ग_लिखोl((__l), (अचिन्हित दीर्घ)(__addr)))
#घोषणा upa_ग_लिखोq(__q, __addr)		(_upa_ग_लिखोq((__q), (अचिन्हित दीर्घ)(__addr)))
#पूर्ण_अगर /* __KERNEL__ && !__ASSEMBLY__ */

#पूर्ण_अगर /* !(_SPARC64_UPA_H) */
