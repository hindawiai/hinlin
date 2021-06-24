<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_TABLES_PHY_HT_H_
#घोषणा B43_TABLES_PHY_HT_H_

/* The HT-PHY tables. */
#घोषणा B43_HTTAB_TYPEMASK		0xF0000000
#घोषणा B43_HTTAB_8BIT			0x10000000
#घोषणा B43_HTTAB_16BIT			0x20000000
#घोषणा B43_HTTAB_32BIT			0x30000000
#घोषणा B43_HTTAB8(table, offset)	(((table) << 10) | (offset) | B43_HTTAB_8BIT)
#घोषणा B43_HTTAB16(table, offset)	(((table) << 10) | (offset) | B43_HTTAB_16BIT)
#घोषणा B43_HTTAB32(table, offset)	(((table) << 10) | (offset) | B43_HTTAB_32BIT)

u32 b43_httab_पढ़ो(काष्ठा b43_wldev *dev, u32 offset);
व्योम b43_httab_पढ़ो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			 अचिन्हित पूर्णांक nr_elements, व्योम *_data);
व्योम b43_httab_ग_लिखो(काष्ठा b43_wldev *dev, u32 offset, u32 value);
व्योम b43_httab_ग_लिखो_few(काष्ठा b43_wldev *dev, u32 offset, माप_प्रकार num, ...);
व्योम b43_httab_ग_लिखो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			  अचिन्हित पूर्णांक nr_elements, स्थिर व्योम *_data);

व्योम b43_phy_ht_tables_init(काष्ठा b43_wldev *dev);

#घोषणा B43_HTTAB_1A_C0_LATE_SIZE		128
बाह्य स्थिर u32 b43_httab_0x1a_0xc0_late[];

#पूर्ण_अगर /* B43_TABLES_PHY_HT_H_ */
