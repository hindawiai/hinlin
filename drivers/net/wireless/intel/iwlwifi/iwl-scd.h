<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2014 Intel Mobile Communications GmbH
 */
#अगर_अघोषित __iwl_scd_h__
#घोषणा __iwl_scd_h__

#समावेश "iwl-trans.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"


अटल अंतरभूत व्योम iwl_scd_txq_set_chain(काष्ठा iwl_trans *trans,
					 u16 txq_id)
अणु
	iwl_set_bits_prph(trans, SCD_QUEUECHAIN_SEL, BIT(txq_id));
पूर्ण

अटल अंतरभूत व्योम iwl_scd_txq_enable_agg(काष्ठा iwl_trans *trans,
					  u16 txq_id)
अणु
	iwl_set_bits_prph(trans, SCD_AGGR_SEL, BIT(txq_id));
पूर्ण

अटल अंतरभूत व्योम iwl_scd_txq_disable_agg(काष्ठा iwl_trans *trans,
					   u16 txq_id)
अणु
	iwl_clear_bits_prph(trans, SCD_AGGR_SEL, BIT(txq_id));
पूर्ण

अटल अंतरभूत व्योम iwl_scd_disable_agg(काष्ठा iwl_trans *trans)
अणु
	iwl_set_bits_prph(trans, SCD_AGGR_SEL, 0);
पूर्ण

अटल अंतरभूत व्योम iwl_scd_activate_fअगरos(काष्ठा iwl_trans *trans)
अणु
	iwl_ग_लिखो_prph(trans, SCD_TXFACT, IWL_MASK(0, 7));
पूर्ण

अटल अंतरभूत व्योम iwl_scd_deactivate_fअगरos(काष्ठा iwl_trans *trans)
अणु
	iwl_ग_लिखो_prph(trans, SCD_TXFACT, 0);
पूर्ण

अटल अंतरभूत व्योम iwl_scd_enable_set_active(काष्ठा iwl_trans *trans,
					     u32 value)
अणु
	iwl_ग_लिखो_prph(trans, SCD_EN_CTRL, value);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक SCD_QUEUE_WRPTR(अचिन्हित पूर्णांक chnl)
अणु
	अगर (chnl < 20)
		वापस SCD_BASE + 0x18 + chnl * 4;
	WARN_ON_ONCE(chnl >= 32);
	वापस SCD_BASE + 0x284 + (chnl - 20) * 4;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक SCD_QUEUE_RDPTR(अचिन्हित पूर्णांक chnl)
अणु
	अगर (chnl < 20)
		वापस SCD_BASE + 0x68 + chnl * 4;
	WARN_ON_ONCE(chnl >= 32);
	वापस SCD_BASE + 0x2B4 + chnl * 4;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक SCD_QUEUE_STATUS_BITS(अचिन्हित पूर्णांक chnl)
अणु
	अगर (chnl < 20)
		वापस SCD_BASE + 0x10c + chnl * 4;
	WARN_ON_ONCE(chnl >= 32);
	वापस SCD_BASE + 0x334 + chnl * 4;
पूर्ण

अटल अंतरभूत व्योम iwl_scd_txq_set_inactive(काष्ठा iwl_trans *trans,
					    u16 txq_id)
अणु
	iwl_ग_लिखो_prph(trans, SCD_QUEUE_STATUS_BITS(txq_id),
		       (0 << SCD_QUEUE_STTS_REG_POS_ACTIVE)|
		       (1 << SCD_QUEUE_STTS_REG_POS_SCD_ACT_EN));
पूर्ण

#पूर्ण_अगर
