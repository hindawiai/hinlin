<शैली गुरु>
#अगर_अघोषित __LINKMODE_H
#घोषणा __LINKMODE_H

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/ethtool.h>
#समावेश <uapi/linux/ethtool.h>

अटल अंतरभूत व्योम linkmode_zero(अचिन्हित दीर्घ *dst)
अणु
	biपंचांगap_zero(dst, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत व्योम linkmode_copy(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src)
अणु
	biपंचांगap_copy(dst, src, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत व्योम linkmode_and(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *a,
				स्थिर अचिन्हित दीर्घ *b)
अणु
	biपंचांगap_and(dst, a, b, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत व्योम linkmode_or(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *a,
				स्थिर अचिन्हित दीर्घ *b)
अणु
	biपंचांगap_or(dst, a, b, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत bool linkmode_empty(स्थिर अचिन्हित दीर्घ *src)
अणु
	वापस biपंचांगap_empty(src, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत पूर्णांक linkmode_andnot(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src1,
				  स्थिर अचिन्हित दीर्घ *src2)
अणु
	वापस biपंचांगap_andnot(dst, src1, src2,  __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत व्योम linkmode_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__set_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम linkmode_set_bit_array(स्थिर पूर्णांक *array, पूर्णांक array_size,
					  अचिन्हित दीर्घ *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < array_size; i++)
		linkmode_set_bit(array[i], addr);
पूर्ण

अटल अंतरभूत व्योम linkmode_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__clear_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम linkmode_mod_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr,
				    पूर्णांक set)
अणु
	अगर (set)
		linkmode_set_bit(nr, addr);
	अन्यथा
		linkmode_clear_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम linkmode_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__change_bit(nr, addr);
पूर्ण

अटल अंतरभूत पूर्णांक linkmode_test_bit(पूर्णांक nr, स्थिर अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_bit(nr, addr);
पूर्ण

अटल अंतरभूत पूर्णांक linkmode_equal(स्थिर अचिन्हित दीर्घ *src1,
				 स्थिर अचिन्हित दीर्घ *src2)
अणु
	वापस biपंचांगap_equal(src1, src2, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत पूर्णांक linkmode_पूर्णांकersects(स्थिर अचिन्हित दीर्घ *src1,
				      स्थिर अचिन्हित दीर्घ *src2)
अणु
	वापस biपंचांगap_पूर्णांकersects(src1, src2, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल अंतरभूत पूर्णांक linkmode_subset(स्थिर अचिन्हित दीर्घ *src1,
				  स्थिर अचिन्हित दीर्घ *src2)
अणु
	वापस biपंचांगap_subset(src1, src2, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

व्योम linkmode_resolve_छोड़ो(स्थिर अचिन्हित दीर्घ *local_adv,
			    स्थिर अचिन्हित दीर्घ *partner_adv,
			    bool *tx_छोड़ो, bool *rx_छोड़ो);

व्योम linkmode_set_छोड़ो(अचिन्हित दीर्घ *advertisement, bool tx, bool rx);

#पूर्ण_अगर /* __LINKMODE_H */
