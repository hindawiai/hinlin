<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_TABLES_LPPHY_H_
#घोषणा B43_TABLES_LPPHY_H_


#घोषणा B43_LPTAB_TYPEMASK		0xF0000000
#घोषणा B43_LPTAB_8BIT			0x10000000
#घोषणा B43_LPTAB_16BIT			0x20000000
#घोषणा B43_LPTAB_32BIT			0x30000000
#घोषणा B43_LPTAB8(table, offset)	(((table) << 10) | (offset) | B43_LPTAB_8BIT)
#घोषणा B43_LPTAB16(table, offset)	(((table) << 10) | (offset) | B43_LPTAB_16BIT)
#घोषणा B43_LPTAB32(table, offset)	(((table) << 10) | (offset) | B43_LPTAB_32BIT)

/* Table definitions */
#घोषणा B43_LPTAB_TXPWR_R2PLUS		B43_LPTAB32(0x07, 0) /* TX घातer lookup table (rev >= 2) */
#घोषणा B43_LPTAB_TXPWR_R0_1		B43_LPTAB32(0xA0, 0) /* TX घातer lookup table (rev < 2) */

u32 b43_lptab_पढ़ो(काष्ठा b43_wldev *dev, u32 offset);
व्योम b43_lptab_ग_लिखो(काष्ठा b43_wldev *dev, u32 offset, u32 value);

/* Bulk table access. Note that these functions वापस the bulk data in
 * host endianness! The वापसed data is _not_ a bytearray, but an array
 * consisting of nr_elements of the data type. */
व्योम b43_lptab_पढ़ो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			 अचिन्हित पूर्णांक nr_elements, व्योम *data);
व्योम b43_lptab_ग_लिखो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			  अचिन्हित पूर्णांक nr_elements, स्थिर व्योम *data);

व्योम b2062_upload_init_table(काष्ठा b43_wldev *dev);
व्योम b2063_upload_init_table(काष्ठा b43_wldev *dev);

काष्ठा lpphy_tx_gain_table_entry अणु
	u8 gm,  pga,  pad,  dac,  bb_mult;
पूर्ण;

व्योम lpphy_ग_लिखो_gain_table(काष्ठा b43_wldev *dev, पूर्णांक offset,
			    काष्ठा lpphy_tx_gain_table_entry data);
व्योम lpphy_ग_लिखो_gain_table_bulk(काष्ठा b43_wldev *dev, पूर्णांक offset, पूर्णांक count,
				 काष्ठा lpphy_tx_gain_table_entry *table);

व्योम lpphy_rev0_1_table_init(काष्ठा b43_wldev *dev);
व्योम lpphy_rev2plus_table_init(काष्ठा b43_wldev *dev);
व्योम lpphy_init_tx_gain_table(काष्ठा b43_wldev *dev);

#पूर्ण_अगर /* B43_TABLES_LPPHY_H_ */
