<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2015,2017 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित _HIF_H_
#घोषणा _HIF_H_

#समावेश <linux/kernel.h>
#समावेश "core.h"
#समावेश "bmi.h"
#समावेश "debug.h"

/* Types of fw logging mode */
क्रमागत ath_dbg_mode अणु
	ATH10K_ENABLE_FW_LOG_DIAG,
	ATH10K_ENABLE_FW_LOG_CE,
पूर्ण;

काष्ठा ath10k_hअगर_sg_item अणु
	u16 transfer_id;
	व्योम *transfer_context; /* शून्य = tx completion callback not called */
	व्योम *vaddr; /* क्रम debugging mostly */
	dma_addr_t paddr;
	u16 len;
पूर्ण;

काष्ठा ath10k_hअगर_ops अणु
	/* send a scatter-gather list to the target */
	पूर्णांक (*tx_sg)(काष्ठा ath10k *ar, u8 pipe_id,
		     काष्ठा ath10k_hअगर_sg_item *items, पूर्णांक n_items);

	/* पढ़ो firmware memory through the diagnose पूर्णांकerface */
	पूर्णांक (*diag_पढ़ो)(काष्ठा ath10k *ar, u32 address, व्योम *buf,
			 माप_प्रकार buf_len);

	पूर्णांक (*diag_ग_लिखो)(काष्ठा ath10k *ar, u32 address, स्थिर व्योम *data,
			  पूर्णांक nbytes);
	/*
	 * API to handle HIF-specअगरic BMI message exchanges, this API is
	 * synchronous and only allowed to be called from a context that
	 * can block (sleep)
	 */
	पूर्णांक (*exchange_bmi_msg)(काष्ठा ath10k *ar,
				व्योम *request, u32 request_len,
				व्योम *response, u32 *response_len);

	/* Post BMI phase, after FW is loaded. Starts regular operation */
	पूर्णांक (*start)(काष्ठा ath10k *ar);

	/* Clean up what start() did. This करोes not revert to BMI phase. If
	 * desired so, call घातer_करोwn() and घातer_up()
	 */
	व्योम (*stop)(काष्ठा ath10k *ar);

	पूर्णांक (*start_post)(काष्ठा ath10k *ar);

	पूर्णांक (*get_htt_tx_complete)(काष्ठा ath10k *ar);

	पूर्णांक (*map_service_to_pipe)(काष्ठा ath10k *ar, u16 service_id,
				   u8 *ul_pipe, u8 *dl_pipe);

	व्योम (*get_शेष_pipe)(काष्ठा ath10k *ar, u8 *ul_pipe, u8 *dl_pipe);

	/*
	 * Check अगर prior sends have completed.
	 *
	 * Check whether the pipe in question has any completed
	 * sends that have not yet been processed.
	 * This function is only relevant क्रम HIF pipes that are configured
	 * to be polled rather than पूर्णांकerrupt-driven.
	 */
	व्योम (*send_complete_check)(काष्ठा ath10k *ar, u8 pipe_id, पूर्णांक क्रमce);

	u16 (*get_मुक्त_queue_number)(काष्ठा ath10k *ar, u8 pipe_id);

	u32 (*पढ़ो32)(काष्ठा ath10k *ar, u32 address);

	व्योम (*ग_लिखो32)(काष्ठा ath10k *ar, u32 address, u32 value);

	/* Power up the device and enter BMI transfer mode क्रम FW करोwnload */
	पूर्णांक (*घातer_up)(काष्ठा ath10k *ar, क्रमागत ath10k_firmware_mode fw_mode);

	/* Power करोwn the device and मुक्त up resources. stop() must be called
	 * beक्रमe this अगर start() was called earlier
	 */
	व्योम (*घातer_करोwn)(काष्ठा ath10k *ar);

	पूर्णांक (*suspend)(काष्ठा ath10k *ar);
	पूर्णांक (*resume)(काष्ठा ath10k *ar);

	/* fetch calibration data from target eeprom */
	पूर्णांक (*fetch_cal_eeprom)(काष्ठा ath10k *ar, व्योम **data,
				माप_प्रकार *data_len);

	पूर्णांक (*get_target_info)(काष्ठा ath10k *ar,
			       काष्ठा bmi_target_info *target_info);
	पूर्णांक (*set_target_log_mode)(काष्ठा ath10k *ar, u8 fw_log_mode);
पूर्ण;

अटल अंतरभूत पूर्णांक ath10k_hअगर_tx_sg(काष्ठा ath10k *ar, u8 pipe_id,
				   काष्ठा ath10k_hअगर_sg_item *items,
				   पूर्णांक n_items)
अणु
	वापस ar->hअगर.ops->tx_sg(ar, pipe_id, items, n_items);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_diag_पढ़ो(काष्ठा ath10k *ar, u32 address, व्योम *buf,
				       माप_प्रकार buf_len)
अणु
	वापस ar->hअगर.ops->diag_पढ़ो(ar, address, buf, buf_len);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_diag_ग_लिखो(काष्ठा ath10k *ar, u32 address,
					स्थिर व्योम *data, पूर्णांक nbytes)
अणु
	अगर (!ar->hअगर.ops->diag_ग_लिखो)
		वापस -EOPNOTSUPP;

	वापस ar->hअगर.ops->diag_ग_लिखो(ar, address, data, nbytes);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_exchange_bmi_msg(काष्ठा ath10k *ar,
					      व्योम *request, u32 request_len,
					      व्योम *response, u32 *response_len)
अणु
	वापस ar->hअगर.ops->exchange_bmi_msg(ar, request, request_len,
					     response, response_len);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_start(काष्ठा ath10k *ar)
अणु
	वापस ar->hअगर.ops->start(ar);
पूर्ण

अटल अंतरभूत व्योम ath10k_hअगर_stop(काष्ठा ath10k *ar)
अणु
	वापस ar->hअगर.ops->stop(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_start_post(काष्ठा ath10k *ar)
अणु
	अगर (ar->hअगर.ops->start_post)
		वापस ar->hअगर.ops->start_post(ar);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_get_htt_tx_complete(काष्ठा ath10k *ar)
अणु
	अगर (ar->hअगर.ops->get_htt_tx_complete)
		वापस ar->hअगर.ops->get_htt_tx_complete(ar);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_map_service_to_pipe(काष्ठा ath10k *ar,
						 u16 service_id,
						 u8 *ul_pipe, u8 *dl_pipe)
अणु
	वापस ar->hअगर.ops->map_service_to_pipe(ar, service_id,
						ul_pipe, dl_pipe);
पूर्ण

अटल अंतरभूत व्योम ath10k_hअगर_get_शेष_pipe(काष्ठा ath10k *ar,
					       u8 *ul_pipe, u8 *dl_pipe)
अणु
	ar->hअगर.ops->get_शेष_pipe(ar, ul_pipe, dl_pipe);
पूर्ण

अटल अंतरभूत व्योम ath10k_hअगर_send_complete_check(काष्ठा ath10k *ar,
						  u8 pipe_id, पूर्णांक क्रमce)
अणु
	अगर (ar->hअगर.ops->send_complete_check)
		ar->hअगर.ops->send_complete_check(ar, pipe_id, क्रमce);
पूर्ण

अटल अंतरभूत u16 ath10k_hअगर_get_मुक्त_queue_number(काष्ठा ath10k *ar,
						   u8 pipe_id)
अणु
	वापस ar->hअगर.ops->get_मुक्त_queue_number(ar, pipe_id);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_घातer_up(काष्ठा ath10k *ar,
				      क्रमागत ath10k_firmware_mode fw_mode)
अणु
	वापस ar->hअगर.ops->घातer_up(ar, fw_mode);
पूर्ण

अटल अंतरभूत व्योम ath10k_hअगर_घातer_करोwn(काष्ठा ath10k *ar)
अणु
	ar->hअगर.ops->घातer_करोwn(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_suspend(काष्ठा ath10k *ar)
अणु
	अगर (!ar->hअगर.ops->suspend)
		वापस -EOPNOTSUPP;

	वापस ar->hअगर.ops->suspend(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_resume(काष्ठा ath10k *ar)
अणु
	अगर (!ar->hअगर.ops->resume)
		वापस -EOPNOTSUPP;

	वापस ar->hअगर.ops->resume(ar);
पूर्ण

अटल अंतरभूत u32 ath10k_hअगर_पढ़ो32(काष्ठा ath10k *ar, u32 address)
अणु
	अगर (!ar->hअगर.ops->पढ़ो32) अणु
		ath10k_warn(ar, "hif read32 not supported\n");
		वापस 0xdeaddead;
	पूर्ण

	वापस ar->hअगर.ops->पढ़ो32(ar, address);
पूर्ण

अटल अंतरभूत व्योम ath10k_hअगर_ग_लिखो32(काष्ठा ath10k *ar,
				      u32 address, u32 data)
अणु
	अगर (!ar->hअगर.ops->ग_लिखो32) अणु
		ath10k_warn(ar, "hif write32 not supported\n");
		वापस;
	पूर्ण

	ar->hअगर.ops->ग_लिखो32(ar, address, data);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_fetch_cal_eeprom(काष्ठा ath10k *ar,
					      व्योम **data,
					      माप_प्रकार *data_len)
अणु
	अगर (!ar->hअगर.ops->fetch_cal_eeprom)
		वापस -EOPNOTSUPP;

	वापस ar->hअगर.ops->fetch_cal_eeprom(ar, data, data_len);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_get_target_info(काष्ठा ath10k *ar,
					     काष्ठा bmi_target_info *tgt_info)
अणु
	अगर (!ar->hअगर.ops->get_target_info)
		वापस -EOPNOTSUPP;

	वापस ar->hअगर.ops->get_target_info(ar, tgt_info);
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_hअगर_set_target_log_mode(काष्ठा ath10k *ar,
						 u8 fw_log_mode)
अणु
	अगर (!ar->hअगर.ops->set_target_log_mode)
		वापस -EOPNOTSUPP;

	वापस ar->hअगर.ops->set_target_log_mode(ar, fw_log_mode);
पूर्ण
#पूर्ण_अगर /* _HIF_H_ */
