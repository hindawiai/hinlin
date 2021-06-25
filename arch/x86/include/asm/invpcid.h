<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_INVPCID
#घोषणा _ASM_X86_INVPCID

अटल अंतरभूत व्योम __invpcid(अचिन्हित दीर्घ pcid, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ type)
अणु
	काष्ठा अणु u64 d[2]; पूर्ण desc = अणु अणु pcid, addr पूर्ण पूर्ण;

	/*
	 * The memory clobber is because the whole poपूर्णांक is to invalidate
	 * stale TLB entries and, especially अगर we're flushing global
	 * mappings, we करोn't want the compiler to reorder any subsequent
	 * memory accesses beक्रमe the TLB flush.
	 */
	यंत्र अस्थिर("invpcid %[desc], %[type]"
		     :: [desc] "m" (desc), [type] "r" (type) : "memory");
पूर्ण

#घोषणा INVPCID_TYPE_INDIV_ADDR		0
#घोषणा INVPCID_TYPE_SINGLE_CTXT	1
#घोषणा INVPCID_TYPE_ALL_INCL_GLOBAL	2
#घोषणा INVPCID_TYPE_ALL_NON_GLOBAL	3

/* Flush all mappings क्रम a given pcid and addr, not including globals. */
अटल अंतरभूत व्योम invpcid_flush_one(अचिन्हित दीर्घ pcid,
				     अचिन्हित दीर्घ addr)
अणु
	__invpcid(pcid, addr, INVPCID_TYPE_INDIV_ADDR);
पूर्ण

/* Flush all mappings क्रम a given PCID, not including globals. */
अटल अंतरभूत व्योम invpcid_flush_single_context(अचिन्हित दीर्घ pcid)
अणु
	__invpcid(pcid, 0, INVPCID_TYPE_SINGLE_CTXT);
पूर्ण

/* Flush all mappings, including globals, क्रम all PCIDs. */
अटल अंतरभूत व्योम invpcid_flush_all(व्योम)
अणु
	__invpcid(0, 0, INVPCID_TYPE_ALL_INCL_GLOBAL);
पूर्ण

/* Flush all mappings क्रम all PCIDs except globals. */
अटल अंतरभूत व्योम invpcid_flush_all_nonglobals(व्योम)
अणु
	__invpcid(0, 0, INVPCID_TYPE_ALL_NON_GLOBAL);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_INVPCID */
