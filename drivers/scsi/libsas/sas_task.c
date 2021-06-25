<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "sas_internal.h"

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <scsi/sas.h>
#समावेश <scsi/libsas.h>

/* fill task_status_काष्ठा based on SSP response frame */
व्योम sas_ssp_task_response(काष्ठा device *dev, काष्ठा sas_task *task,
			   काष्ठा ssp_response_iu *iu)
अणु
	काष्ठा task_status_काष्ठा *tstat = &task->task_status;

	tstat->resp = SAS_TASK_COMPLETE;

	अगर (iu->datapres == 0)
		tstat->stat = iu->status;
	अन्यथा अगर (iu->datapres == 1)
		tstat->stat = iu->resp_data[3];
	अन्यथा अगर (iu->datapres == 2) अणु
		tstat->stat = SAM_STAT_CHECK_CONDITION;
		tstat->buf_valid_size =
			min_t(पूर्णांक, SAS_STATUS_BUF_SIZE,
			      be32_to_cpu(iu->sense_data_len));
		स_नकल(tstat->buf, iu->sense_data, tstat->buf_valid_size);

		अगर (iu->status != SAM_STAT_CHECK_CONDITION)
			dev_warn(dev, "dev %016llx sent sense data, but stat(0x%x) is not CHECK CONDITION\n",
				 SAS_ADDR(task->dev->sas_addr), iu->status);
	पूर्ण
	अन्यथा
		/* when datapres contains corrupt/unknown value... */
		tstat->stat = SAM_STAT_CHECK_CONDITION;
पूर्ण
EXPORT_SYMBOL_GPL(sas_ssp_task_response);

