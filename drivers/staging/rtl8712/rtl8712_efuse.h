<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RTL8712_EFUSE_H__
#घोषणा __RTL8712_EFUSE_H__

#समावेश "osdep_service.h"

#घोषणा _REPEAT_THRESHOLD_	3

#घोषणा EFUSE_MAX_SIZE		512
#घोषणा EFUSE_MAP_MAX_SIZE	128

#घोषणा PGPKG_MAX_WORDS	4
#घोषणा PGPKT_DATA_SIZE	8 /* PGPKG_MAX_WORDS*2; BYTES माप(u8)*8*/
#घोषणा MAX_PGPKT_SIZE	9 /* 1 + PGPKT_DATA_SIZE; header + 2 * 4 words (BYTES)*/

#घोषणा GET_EFUSE_OFFSET(header)	((header & 0xF0) >> 4)
#घोषणा GET_EFUSE_WORD_EN(header)	(header & 0x0F)
#घोषणा MAKE_EFUSE_HEADER(offset, word_en)	(((offset & 0x0F) << 4) | \
						(word_en & 0x0F))
/*--------------------------------------------------------------------------*/
काष्ठा PGPKT_STRUCT अणु
	u8 offset;
	u8 word_en;
	u8 data[PGPKT_DATA_SIZE];
पूर्ण;
/*--------------------------------------------------------------------------*/
u8 r8712_efuse_reg_init(काष्ठा _adapter *padapter);
व्योम r8712_efuse_reg_uninit(काष्ठा _adapter *padapter);
u16 r8712_efuse_get_current_size(काष्ठा _adapter *padapter);
पूर्णांक r8712_efuse_get_max_size(काष्ठा _adapter *padapter);
व्योम r8712_efuse_change_max_size(काष्ठा _adapter *padapter);
u8 r8712_efuse_pg_packet_पढ़ो(काष्ठा _adapter *padapter,
			      u8 offset, u8 *data);
u8 r8712_efuse_pg_packet_ग_लिखो(काष्ठा _adapter *padapter,
			       स्थिर u8 offset, स्थिर u8 word_en,
			       स्थिर u8 *data);
u8 r8712_efuse_access(काष्ठा _adapter *padapter, u8 bRead,
		      u16 start_addr, u16 cnts, u8 *data);
u8 r8712_efuse_map_पढ़ो(काष्ठा _adapter *padapter, u16 addr,
			u16 cnts, u8 *data);
u8 r8712_efuse_map_ग_लिखो(काष्ठा _adapter *padapter, u16 addr,
			 u16 cnts, u8 *data);
#पूर्ण_अगर
