<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_OOO_H
#घोषणा _QED_OOO_H
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश "qed.h"

#घोषणा QED_MAX_NUM_ISLES	256
#घोषणा QED_MAX_NUM_OOO_HISTORY_ENTRIES	512

#घोषणा QED_OOO_LEFT_BUF	0
#घोषणा QED_OOO_RIGHT_BUF	1

काष्ठा qed_ooo_buffer अणु
	काष्ठा list_head list_entry;
	व्योम *rx_buffer_virt_addr;
	dma_addr_t rx_buffer_phys_addr;
	u32 rx_buffer_size;
	u16 packet_length;
	u16 parse_flags;
	u16 vlan;
	u8 placement_offset;
पूर्ण;

काष्ठा qed_ooo_isle अणु
	काष्ठा list_head list_entry;
	काष्ठा list_head buffers_list;
पूर्ण;

काष्ठा qed_ooo_archipelago अणु
	काष्ठा list_head isles_list;
पूर्ण;

काष्ठा qed_ooo_history अणु
	काष्ठा ooo_opaque *p_cqes;
	u32 head_idx;
	u32 num_of_cqes;
पूर्ण;

काष्ठा qed_ooo_info अणु
	काष्ठा list_head मुक्त_buffers_list;
	काष्ठा list_head पढ़ोy_buffers_list;
	काष्ठा list_head मुक्त_isles_list;
	काष्ठा qed_ooo_archipelago *p_archipelagos_mem;
	काष्ठा qed_ooo_isle *p_isles_mem;
	काष्ठा qed_ooo_history ooo_history;
	u32 cur_isles_number;
	u32 max_isles_number;
	u32 gen_isles_number;
	u16 max_num_archipelagos;
	u16 cid_base;
पूर्ण;

#अगर IS_ENABLED(CONFIG_QED_OOO)
व्योम qed_ooo_save_history_entry(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ooo_info *p_ooo_info,
				काष्ठा ooo_opaque *p_cqe);

पूर्णांक qed_ooo_alloc(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_ooo_setup(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_ooo_मुक्त(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_ooo_release_connection_isles(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ooo_info *p_ooo_info,
				      u32 cid);

व्योम qed_ooo_release_all_isles(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ooo_info *p_ooo_info);

व्योम qed_ooo_put_मुक्त_buffer(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ooo_info *p_ooo_info,
			     काष्ठा qed_ooo_buffer *p_buffer);

काष्ठा qed_ooo_buffer *
qed_ooo_get_मुक्त_buffer(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ooo_info *p_ooo_info);

व्योम qed_ooo_put_पढ़ोy_buffer(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ooo_info *p_ooo_info,
			      काष्ठा qed_ooo_buffer *p_buffer, u8 on_tail);

काष्ठा qed_ooo_buffer *
qed_ooo_get_पढ़ोy_buffer(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ooo_info *p_ooo_info);

व्योम qed_ooo_delete_isles(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ooo_info *p_ooo_info,
			  u32 cid, u8 drop_isle, u8 drop_size);

व्योम qed_ooo_add_new_isle(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ooo_info *p_ooo_info,
			  u32 cid,
			  u8 ooo_isle, काष्ठा qed_ooo_buffer *p_buffer);

व्योम qed_ooo_add_new_buffer(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ooo_info *p_ooo_info,
			    u32 cid,
			    u8 ooo_isle,
			    काष्ठा qed_ooo_buffer *p_buffer, u8 buffer_side);

व्योम qed_ooo_join_isles(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ooo_info *p_ooo_info, u32 cid,
			u8 left_isle);
#अन्यथा /* IS_ENABLED(CONFIG_QED_ISCSI) */
अटल अंतरभूत व्योम qed_ooo_save_history_entry(काष्ठा qed_hwfn *p_hwfn,
					      काष्ठा qed_ooo_info *p_ooo_info,
					      काष्ठा ooo_opaque *p_cqe) अणुपूर्ण

अटल अंतरभूत पूर्णांक qed_ooo_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम qed_ooo_setup(काष्ठा qed_hwfn *p_hwfn) अणुपूर्ण

अटल अंतरभूत व्योम qed_ooo_मुक्त(काष्ठा qed_hwfn *p_hwfn) अणुपूर्ण

अटल अंतरभूत व्योम
qed_ooo_release_connection_isles(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ooo_info *p_ooo_info,
				 u32 cid) अणुपूर्ण

अटल अंतरभूत व्योम qed_ooo_release_all_isles(काष्ठा qed_hwfn *p_hwfn,
					     काष्ठा qed_ooo_info *p_ooo_info)
					     अणुपूर्ण

अटल अंतरभूत व्योम qed_ooo_put_मुक्त_buffer(काष्ठा qed_hwfn *p_hwfn,
					   काष्ठा qed_ooo_info *p_ooo_info,
					   काष्ठा qed_ooo_buffer *p_buffer) अणुपूर्ण

अटल अंतरभूत काष्ठा qed_ooo_buffer *
qed_ooo_get_मुक्त_buffer(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ooo_info *p_ooo_info) अणु वापस शून्य; पूर्ण

अटल अंतरभूत व्योम qed_ooo_put_पढ़ोy_buffer(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_ooo_info *p_ooo_info,
					    काष्ठा qed_ooo_buffer *p_buffer,
					    u8 on_tail) अणुपूर्ण

अटल अंतरभूत काष्ठा qed_ooo_buffer *
qed_ooo_get_पढ़ोy_buffer(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ooo_info *p_ooo_info) अणु वापस शून्य; पूर्ण

अटल अंतरभूत व्योम qed_ooo_delete_isles(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ooo_info *p_ooo_info,
					u32 cid, u8 drop_isle, u8 drop_size) अणुपूर्ण

अटल अंतरभूत व्योम qed_ooo_add_new_isle(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ooo_info *p_ooo_info,
					u32 cid, u8 ooo_isle,
					काष्ठा qed_ooo_buffer *p_buffer) अणुपूर्ण

अटल अंतरभूत व्योम qed_ooo_add_new_buffer(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ooo_info *p_ooo_info,
					  u32 cid, u8 ooo_isle,
					  काष्ठा qed_ooo_buffer *p_buffer,
					  u8 buffer_side) अणुपूर्ण

अटल अंतरभूत व्योम qed_ooo_join_isles(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ooo_info *p_ooo_info, u32 cid,
				      u8 left_isle) अणुपूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_QED_ISCSI) */

#पूर्ण_अगर
