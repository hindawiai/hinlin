<शैली गुरु>
#अगर_अघोषित _SH_MM_IORMEMAP_H
#घोषणा _SH_MM_IORMEMAP_H 1

#अगर_घोषित CONFIG_IOREMAP_FIXED
व्योम __iomem *ioremap_fixed(phys_addr_t, अचिन्हित दीर्घ, pgprot_t);
पूर्णांक iounmap_fixed(व्योम __iomem *);
व्योम ioremap_fixed_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __iomem *
ioremap_fixed(phys_addr_t phys_addr, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	BUG();
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम ioremap_fixed_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक iounmap_fixed(व्योम __iomem *addr)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_IOREMAP_FIXED */
#पूर्ण_अगर /* _SH_MM_IORMEMAP_H */
