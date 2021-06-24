<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2013-2015 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित SPECTRAL_H
#घोषणा SPECTRAL_H

#समावेश "../spectral_common.h"

/**
 * काष्ठा ath10k_spec_scan - parameters क्रम Atheros spectral scan
 *
 * @count: number of scan results requested क्रम manual mode
 * @fft_size: number of bins to be requested = 2^(fft_size - bin_scale)
 */
काष्ठा ath10k_spec_scan अणु
	u8 count;
	u8 fft_size;
पूर्ण;

/* क्रमागत ath10k_spectral_mode:
 *
 * @SPECTRAL_DISABLED: spectral mode is disabled
 * @SPECTRAL_BACKGROUND: hardware sends samples when it is not busy with
 *	something अन्यथा.
 * @SPECTRAL_MANUAL: spectral scan is enabled, triggering क्रम samples
 *	is perक्रमmed manually.
 */
क्रमागत ath10k_spectral_mode अणु
	SPECTRAL_DISABLED = 0,
	SPECTRAL_BACKGROUND,
	SPECTRAL_MANUAL,
पूर्ण;

#अगर_घोषित CONFIG_ATH10K_SPECTRAL

पूर्णांक ath10k_spectral_process_fft(काष्ठा ath10k *ar,
				काष्ठा wmi_phyerr_ev_arg *phyerr,
				स्थिर काष्ठा phyerr_fft_report *fftr,
				माप_प्रकार bin_len, u64 tsf);
पूर्णांक ath10k_spectral_start(काष्ठा ath10k *ar);
पूर्णांक ath10k_spectral_vअगर_stop(काष्ठा ath10k_vअगर *arvअगर);
पूर्णांक ath10k_spectral_create(काष्ठा ath10k *ar);
व्योम ath10k_spectral_destroy(काष्ठा ath10k *ar);

#अन्यथा

अटल अंतरभूत पूर्णांक
ath10k_spectral_process_fft(काष्ठा ath10k *ar,
			    काष्ठा wmi_phyerr_ev_arg *phyerr,
			    स्थिर काष्ठा phyerr_fft_report *fftr,
			    माप_प्रकार bin_len, u64 tsf)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_spectral_start(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_spectral_vअगर_stop(काष्ठा ath10k_vअगर *arvअगर)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_spectral_create(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_spectral_destroy(काष्ठा ath10k *ar)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH10K_SPECTRAL */

#पूर्ण_अगर /* SPECTRAL_H */
