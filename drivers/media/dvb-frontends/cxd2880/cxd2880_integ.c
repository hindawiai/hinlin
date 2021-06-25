<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_पूर्णांकeg.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * पूर्णांकegration layer common functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश <linux/kसमय.स>
#समावेश <linux/त्रुटिसं.स>

#समावेश "cxd2880_tnrdmd.h"
#समावेश "cxd2880_tnrdmd_mon.h"
#समावेश "cxd2880_integ.h"

पूर्णांक cxd2880_पूर्णांकeg_init(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	पूर्णांक ret;
	kसमय_प्रकार start;
	u8 cpu_task_completed = 0;

	अगर (!tnr_dmd)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_init1(tnr_dmd);
	अगर (ret)
		वापस ret;

	start = kसमय_get();

	जबतक (1) अणु
		ret =
		    cxd2880_tnrdmd_check_पूर्णांकernal_cpu_status(tnr_dmd,
						     &cpu_task_completed);
		अगर (ret)
			वापस ret;

		अगर (cpu_task_completed)
			अवरोध;

		अगर (kसमय_प्रकारo_ms(kसमय_sub(kसमय_get(), start)) >
					CXD2880_TNRDMD_WAIT_INIT_TIMEOUT)
			वापस -ETIMEDOUT;

		usleep_range(CXD2880_TNRDMD_WAIT_INIT_INTVL,
			     CXD2880_TNRDMD_WAIT_INIT_INTVL + 1000);
	पूर्ण

	वापस cxd2880_tnrdmd_init2(tnr_dmd);
पूर्ण

पूर्णांक cxd2880_पूर्णांकeg_cancel(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	atomic_set(&tnr_dmd->cancel, 1);

	वापस 0;
पूर्ण

पूर्णांक cxd2880_पूर्णांकeg_check_cancellation(काष्ठा cxd2880_tnrdmd *tnr_dmd)
अणु
	अगर (!tnr_dmd)
		वापस -EINVAL;

	अगर (atomic_पढ़ो(&tnr_dmd->cancel) != 0)
		वापस -ECANCELED;

	वापस 0;
पूर्ण
