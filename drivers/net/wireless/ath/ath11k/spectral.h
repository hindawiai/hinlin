<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2019-2020 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_SPECTRAL_H
#घोषणा ATH11K_SPECTRAL_H

#समावेश "../spectral_common.h"
#समावेश "dbring.h"

/* क्रमागत ath11k_spectral_mode:
 *
 * @SPECTRAL_DISABLED: spectral mode is disabled
 * @SPECTRAL_BACKGROUND: hardware sends samples when it is not busy with
 *	something अन्यथा.
 * @SPECTRAL_MANUAL: spectral scan is enabled, triggering क्रम samples
 *	is perक्रमmed manually.
 */
क्रमागत ath11k_spectral_mode अणु
	ATH11K_SPECTRAL_DISABLED = 0,
	ATH11K_SPECTRAL_BACKGROUND,
	ATH11K_SPECTRAL_MANUAL,
पूर्ण;

काष्ठा ath11k_spectral अणु
	काष्ठा ath11k_dbring rx_ring;
	/* Protects enabled */
	spinlock_t lock;
	काष्ठा rchan *rfs_scan;	/* relay(fs) channel क्रम spectral scan */
	काष्ठा dentry *scan_ctl;
	काष्ठा dentry *scan_count;
	काष्ठा dentry *scan_bins;
	क्रमागत ath11k_spectral_mode mode;
	u16 count;
	u8 fft_size;
	bool enabled;
पूर्ण;

#अगर_घोषित CONFIG_ATH11K_SPECTRAL

पूर्णांक ath11k_spectral_init(काष्ठा ath11k_base *ab);
व्योम ath11k_spectral_deinit(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_spectral_vअगर_stop(काष्ठा ath11k_vअगर *arvअगर);
व्योम ath11k_spectral_reset_buffer(काष्ठा ath11k *ar);
क्रमागत ath11k_spectral_mode ath11k_spectral_get_mode(काष्ठा ath11k *ar);
काष्ठा ath11k_dbring *ath11k_spectral_get_dbring(काष्ठा ath11k *ar);

#अन्यथा

अटल अंतरभूत पूर्णांक ath11k_spectral_init(काष्ठा ath11k_base *ab)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_spectral_deinit(काष्ठा ath11k_base *ab)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_spectral_vअगर_stop(काष्ठा ath11k_vअगर *arvअगर)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_spectral_reset_buffer(काष्ठा ath11k *ar)
अणु
पूर्ण

अटल अंतरभूत
क्रमागत ath11k_spectral_mode ath11k_spectral_get_mode(काष्ठा ath11k *ar)
अणु
	वापस ATH11K_SPECTRAL_DISABLED;
पूर्ण

अटल अंतरभूत
काष्ठा ath11k_dbring *ath11k_spectral_get_dbring(काष्ठा ath11k *ar)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH11K_SPECTRAL */
#पूर्ण_अगर /* ATH11K_SPECTRAL_H */
