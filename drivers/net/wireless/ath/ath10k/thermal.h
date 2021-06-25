<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2014-2016 Qualcomm Atheros, Inc.
 */
#अगर_अघोषित _THERMAL_
#घोषणा _THERMAL_

#घोषणा ATH10K_QUIET_PERIOD_DEFAULT     100
#घोषणा ATH10K_QUIET_PERIOD_MIN         25
#घोषणा ATH10K_QUIET_START_OFFSET       10
#घोषणा ATH10K_HWMON_NAME_LEN           15
#घोषणा ATH10K_THERMAL_SYNC_TIMEOUT_HZ (5 * HZ)
#घोषणा ATH10K_THERMAL_THROTTLE_MAX     100

काष्ठा ath10k_thermal अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा completion wmi_sync;

	/* रक्षित by conf_mutex */
	u32 throttle_state;
	u32 quiet_period;
	/* temperature value in Celcius degree
	 * रक्षित by data_lock
	 */
	पूर्णांक temperature;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_THERMAL)
पूर्णांक ath10k_thermal_रेजिस्टर(काष्ठा ath10k *ar);
व्योम ath10k_thermal_unरेजिस्टर(काष्ठा ath10k *ar);
व्योम ath10k_thermal_event_temperature(काष्ठा ath10k *ar, पूर्णांक temperature);
व्योम ath10k_thermal_set_throttling(काष्ठा ath10k *ar);
#अन्यथा
अटल अंतरभूत पूर्णांक ath10k_thermal_रेजिस्टर(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_thermal_unरेजिस्टर(काष्ठा ath10k *ar)
अणु
पूर्ण

अटल अंतरभूत व्योम ath10k_thermal_event_temperature(काष्ठा ath10k *ar,
						    पूर्णांक temperature)
अणु
पूर्ण

अटल अंतरभूत व्योम ath10k_thermal_set_throttling(काष्ठा ath10k *ar)
अणु
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _THERMAL_ */
