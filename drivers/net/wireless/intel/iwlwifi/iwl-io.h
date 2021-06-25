<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2018-2020 Intel Corporation
 */
#अगर_अघोषित __iwl_io_h__
#घोषणा __iwl_io_h__

#समावेश "iwl-devtrace.h"
#समावेश "iwl-trans.h"

व्योम iwl_ग_लिखो8(काष्ठा iwl_trans *trans, u32 ofs, u8 val);
व्योम iwl_ग_लिखो32(काष्ठा iwl_trans *trans, u32 ofs, u32 val);
व्योम iwl_ग_लिखो64(काष्ठा iwl_trans *trans, u64 ofs, u64 val);
u32 iwl_पढ़ो32(काष्ठा iwl_trans *trans, u32 ofs);

अटल अंतरभूत व्योम iwl_set_bit(काष्ठा iwl_trans *trans, u32 reg, u32 mask)
अणु
	iwl_trans_set_bits_mask(trans, reg, mask, mask);
पूर्ण

अटल अंतरभूत व्योम iwl_clear_bit(काष्ठा iwl_trans *trans, u32 reg, u32 mask)
अणु
	iwl_trans_set_bits_mask(trans, reg, mask, 0);
पूर्ण

पूर्णांक iwl_poll_bit(काष्ठा iwl_trans *trans, u32 addr,
		 u32 bits, u32 mask, पूर्णांक समयout);
पूर्णांक iwl_poll_direct_bit(काष्ठा iwl_trans *trans, u32 addr, u32 mask,
			पूर्णांक समयout);

u32 iwl_पढ़ो_direct32(काष्ठा iwl_trans *trans, u32 reg);
व्योम iwl_ग_लिखो_direct32(काष्ठा iwl_trans *trans, u32 reg, u32 value);
व्योम iwl_ग_लिखो_direct64(काष्ठा iwl_trans *trans, u64 reg, u64 value);


u32 iwl_पढ़ो_prph_no_grab(काष्ठा iwl_trans *trans, u32 ofs);
u32 iwl_पढ़ो_prph(काष्ठा iwl_trans *trans, u32 ofs);
व्योम iwl_ग_लिखो_prph_no_grab(काष्ठा iwl_trans *trans, u32 ofs, u32 val);
व्योम iwl_ग_लिखो_prph64_no_grab(काष्ठा iwl_trans *trans, u64 ofs, u64 val);
व्योम iwl_ग_लिखो_prph_delay(काष्ठा iwl_trans *trans, u32 ofs,
			  u32 val, u32 delay_ms);
अटल अंतरभूत व्योम iwl_ग_लिखो_prph(काष्ठा iwl_trans *trans, u32 ofs, u32 val)
अणु
	iwl_ग_लिखो_prph_delay(trans, ofs, val, 0);
पूर्ण

पूर्णांक iwl_poll_prph_bit(काष्ठा iwl_trans *trans, u32 addr,
		      u32 bits, u32 mask, पूर्णांक समयout);
व्योम iwl_set_bits_prph(काष्ठा iwl_trans *trans, u32 ofs, u32 mask);
व्योम iwl_set_bits_mask_prph(काष्ठा iwl_trans *trans, u32 ofs,
			    u32 bits, u32 mask);
व्योम iwl_clear_bits_prph(काष्ठा iwl_trans *trans, u32 ofs, u32 mask);
व्योम iwl_क्रमce_nmi(काष्ठा iwl_trans *trans);

पूर्णांक iwl_finish_nic_init(काष्ठा iwl_trans *trans,
			स्थिर काष्ठा iwl_cfg_trans_params *cfg_trans);

/* Error handling */
पूर्णांक iwl_dump_fh(काष्ठा iwl_trans *trans, अक्षर **buf);

/*
 * UMAC periphery address space changed from 0xA00000 to 0xD00000 starting from
 * device family AX200. So peripheries used in families above and below AX200
 * should go through iwl_..._umac_..._prph.
 */
अटल अंतरभूत u32 iwl_umac_prph(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	वापस ofs + trans->trans_cfg->umac_prph_offset;
पूर्ण

अटल अंतरभूत u32 iwl_पढ़ो_umac_prph_no_grab(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	वापस iwl_पढ़ो_prph_no_grab(trans, ofs +
				     trans->trans_cfg->umac_prph_offset);
पूर्ण

अटल अंतरभूत u32 iwl_पढ़ो_umac_prph(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	वापस iwl_पढ़ो_prph(trans, ofs + trans->trans_cfg->umac_prph_offset);
पूर्ण

अटल अंतरभूत व्योम iwl_ग_लिखो_umac_prph_no_grab(काष्ठा iwl_trans *trans, u32 ofs,
					       u32 val)
अणु
	iwl_ग_लिखो_prph_no_grab(trans,  ofs + trans->trans_cfg->umac_prph_offset,
			       val);
पूर्ण

अटल अंतरभूत व्योम iwl_ग_लिखो_umac_prph(काष्ठा iwl_trans *trans, u32 ofs,
				       u32 val)
अणु
	iwl_ग_लिखो_prph(trans,  ofs + trans->trans_cfg->umac_prph_offset, val);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_poll_umac_prph_bit(काष्ठा iwl_trans *trans, u32 addr,
					 u32 bits, u32 mask, पूर्णांक समयout)
अणु
	वापस iwl_poll_prph_bit(trans, addr +
				 trans->trans_cfg->umac_prph_offset,
				 bits, mask, समयout);
पूर्ण

#पूर्ण_अगर
