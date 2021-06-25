<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ATH11K_THERMAL_
#घोषणा _ATH11K_THERMAL_

#घोषणा ATH11K_THERMAL_TEMP_LOW_MARK -100
#घोषणा ATH11K_THERMAL_TEMP_HIGH_MARK 150
#घोषणा ATH11K_THERMAL_THROTTLE_MAX     100
#घोषणा ATH11K_THERMAL_DEFAULT_DUTY_CYCLE 100
#घोषणा ATH11K_HWMON_NAME_LEN           15
#घोषणा ATH11K_THERMAL_SYNC_TIMEOUT_HZ (5 * HZ)

काष्ठा ath11k_thermal अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा completion wmi_sync;

	/* रक्षित by conf_mutex */
	u32 throttle_state;
	/* temperature value in Celcius degree
	 * रक्षित by data_lock
	 */
	पूर्णांक temperature;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_THERMAL)
पूर्णांक ath11k_thermal_रेजिस्टर(काष्ठा ath11k_base *sc);
व्योम ath11k_thermal_unरेजिस्टर(काष्ठा ath11k_base *sc);
पूर्णांक ath11k_thermal_set_throttling(काष्ठा ath11k *ar, u32 throttle_state);
व्योम ath11k_thermal_event_temperature(काष्ठा ath11k *ar, पूर्णांक temperature);
#अन्यथा
अटल अंतरभूत पूर्णांक ath11k_thermal_रेजिस्टर(काष्ठा ath11k_base *sc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_thermal_unरेजिस्टर(काष्ठा ath11k_base *sc)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_thermal_set_throttling(काष्ठा ath11k *ar, u32 throttle_state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_thermal_event_temperature(काष्ठा ath11k *ar,
						    पूर्णांक temperature)
अणु
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _ATH11K_THERMAL_ */
