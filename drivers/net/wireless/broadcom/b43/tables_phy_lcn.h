<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_TABLES_PHY_LCN_H_
#घोषणा B43_TABLES_PHY_LCN_H_

/* The LCN-PHY tables. */
#घोषणा B43_LCNTAB_TYPEMASK		0xF0000000
#घोषणा B43_LCNTAB_8BIT			0x10000000
#घोषणा B43_LCNTAB_16BIT		0x20000000
#घोषणा B43_LCNTAB_32BIT		0x30000000
#घोषणा B43_LCNTAB8(table, offset)	(((table) << 10) | (offset) | B43_LCNTAB_8BIT)
#घोषणा B43_LCNTAB16(table, offset)	(((table) << 10) | (offset) | B43_LCNTAB_16BIT)
#घोषणा B43_LCNTAB32(table, offset)	(((table) << 10) | (offset) | B43_LCNTAB_32BIT)

#घोषणा B43_LCNTAB_TX_GAIN_SIZE		128

u32 b43_lcntab_पढ़ो(काष्ठा b43_wldev *dev, u32 offset);
व्योम b43_lcntab_पढ़ो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			  अचिन्हित पूर्णांक nr_elements, व्योम *_data);
व्योम b43_lcntab_ग_लिखो(काष्ठा b43_wldev *dev, u32 offset, u32 value);
व्योम b43_lcntab_ग_लिखो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			   अचिन्हित पूर्णांक nr_elements, स्थिर व्योम *_data);

व्योम b43_phy_lcn_tables_init(काष्ठा b43_wldev *dev);

#पूर्ण_अगर /* B43_TABLES_PHY_LCN_H_ */
