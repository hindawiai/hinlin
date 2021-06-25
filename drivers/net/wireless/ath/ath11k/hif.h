<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2019-2020 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _HIF_H_
#घोषणा _HIF_H_

#समावेश "core.h"

काष्ठा ath11k_hअगर_ops अणु
	u32 (*पढ़ो32)(काष्ठा ath11k_base *sc, u32 address);
	व्योम (*ग_लिखो32)(काष्ठा ath11k_base *sc, u32 address, u32 data);
	व्योम (*irq_enable)(काष्ठा ath11k_base *sc);
	व्योम (*irq_disable)(काष्ठा ath11k_base *sc);
	पूर्णांक (*start)(काष्ठा ath11k_base *sc);
	व्योम (*stop)(काष्ठा ath11k_base *sc);
	पूर्णांक (*घातer_up)(काष्ठा ath11k_base *sc);
	व्योम (*घातer_करोwn)(काष्ठा ath11k_base *sc);
	पूर्णांक (*suspend)(काष्ठा ath11k_base *ab);
	पूर्णांक (*resume)(काष्ठा ath11k_base *ab);
	पूर्णांक (*map_service_to_pipe)(काष्ठा ath11k_base *sc, u16 service_id,
				   u8 *ul_pipe, u8 *dl_pipe);
	पूर्णांक (*get_user_msi_vector)(काष्ठा ath11k_base *ab, अक्षर *user_name,
				   पूर्णांक *num_vectors, u32 *user_base_data,
				   u32 *base_vector);
	व्योम (*get_msi_address)(काष्ठा ath11k_base *ab, u32 *msi_addr_lo,
				u32 *msi_addr_hi);
	व्योम (*ce_irq_enable)(काष्ठा ath11k_base *ab);
	व्योम (*ce_irq_disable)(काष्ठा ath11k_base *ab);
	व्योम (*get_ce_msi_idx)(काष्ठा ath11k_base *ab, u32 ce_id, u32 *msi_idx);
पूर्ण;

अटल अंतरभूत व्योम ath11k_hअगर_ce_irq_enable(काष्ठा ath11k_base *ab)
अणु
	अगर (ab->hअगर.ops->ce_irq_enable)
		ab->hअगर.ops->ce_irq_enable(ab);
पूर्ण

अटल अंतरभूत व्योम ath11k_hअगर_ce_irq_disable(काष्ठा ath11k_base *ab)
अणु
	अगर (ab->hअगर.ops->ce_irq_disable)
		ab->hअगर.ops->ce_irq_disable(ab);
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_hअगर_start(काष्ठा ath11k_base *sc)
अणु
	वापस sc->hअगर.ops->start(sc);
पूर्ण

अटल अंतरभूत व्योम ath11k_hअगर_stop(काष्ठा ath11k_base *sc)
अणु
	sc->hअगर.ops->stop(sc);
पूर्ण

अटल अंतरभूत व्योम ath11k_hअगर_irq_enable(काष्ठा ath11k_base *sc)
अणु
	sc->hअगर.ops->irq_enable(sc);
पूर्ण

अटल अंतरभूत व्योम ath11k_hअगर_irq_disable(काष्ठा ath11k_base *sc)
अणु
	sc->hअगर.ops->irq_disable(sc);
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_hअगर_घातer_up(काष्ठा ath11k_base *sc)
अणु
	वापस sc->hअगर.ops->घातer_up(sc);
पूर्ण

अटल अंतरभूत व्योम ath11k_hअगर_घातer_करोwn(काष्ठा ath11k_base *sc)
अणु
	sc->hअगर.ops->घातer_करोwn(sc);
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_hअगर_suspend(काष्ठा ath11k_base *ab)
अणु
	अगर (ab->hअगर.ops->suspend)
		वापस ab->hअगर.ops->suspend(ab);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_hअगर_resume(काष्ठा ath11k_base *ab)
अणु
	अगर (ab->hअगर.ops->resume)
		वापस ab->hअगर.ops->resume(ab);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 ath11k_hअगर_पढ़ो32(काष्ठा ath11k_base *sc, u32 address)
अणु
	वापस sc->hअगर.ops->पढ़ो32(sc, address);
पूर्ण

अटल अंतरभूत व्योम ath11k_hअगर_ग_लिखो32(काष्ठा ath11k_base *sc, u32 address, u32 data)
अणु
	sc->hअगर.ops->ग_लिखो32(sc, address, data);
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_hअगर_map_service_to_pipe(काष्ठा ath11k_base *sc, u16 service_id,
						 u8 *ul_pipe, u8 *dl_pipe)
अणु
	वापस sc->hअगर.ops->map_service_to_pipe(sc, service_id, ul_pipe, dl_pipe);
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_get_user_msi_vector(काष्ठा ath11k_base *ab, अक्षर *user_name,
					     पूर्णांक *num_vectors, u32 *user_base_data,
					     u32 *base_vector)
अणु
	अगर (!ab->hअगर.ops->get_user_msi_vector)
		वापस -EOPNOTSUPP;

	वापस ab->hअगर.ops->get_user_msi_vector(ab, user_name, num_vectors,
						user_base_data,
						base_vector);
पूर्ण

अटल अंतरभूत व्योम ath11k_get_msi_address(काष्ठा ath11k_base *ab, u32 *msi_addr_lo,
					  u32 *msi_addr_hi)
अणु
	अगर (!ab->hअगर.ops->get_msi_address)
		वापस;

	ab->hअगर.ops->get_msi_address(ab, msi_addr_lo, msi_addr_hi);
पूर्ण

अटल अंतरभूत व्योम ath11k_get_ce_msi_idx(काष्ठा ath11k_base *ab, u32 ce_id,
					 u32 *msi_data_idx)
अणु
	अगर (ab->hअगर.ops->get_ce_msi_idx)
		ab->hअगर.ops->get_ce_msi_idx(ab, ce_id, msi_data_idx);
	अन्यथा
		*msi_data_idx = ce_id;
पूर्ण
#पूर्ण_अगर /* _HIF_H_ */
