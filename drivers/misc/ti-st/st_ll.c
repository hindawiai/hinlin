<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Shared Transport driver
 *	HCI-LL module responsible क्रम TI proprietary HCI_LL protocol
 *  Copyright (C) 2009-2010 Texas Instruments
 *  Author: Pavan Savoy <pavan_savoy@ti.com>
 */

#घोषणा pr_fmt(fmt) "(stll) :" fmt
#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ti_wilink_st.h>

/**********************************************************************/
/* पूर्णांकernal functions */
अटल व्योम send_ll_cmd(काष्ठा st_data_s *st_data,
	अचिन्हित अक्षर cmd)
अणु

	pr_debug("%s: writing %x", __func__, cmd);
	st_पूर्णांक_ग_लिखो(st_data, &cmd, 1);
	वापस;
पूर्ण

अटल व्योम ll_device_want_to_sleep(काष्ठा st_data_s *st_data)
अणु
	काष्ठा kim_data_s	*kim_data;
	काष्ठा ti_st_plat_data	*pdata;

	pr_debug("%s", __func__);
	/* sanity check */
	अगर (st_data->ll_state != ST_LL_AWAKE)
		pr_err("ERR hcill: ST_LL_GO_TO_SLEEP_IND"
			  "in state %ld", st_data->ll_state);

	send_ll_cmd(st_data, LL_SLEEP_ACK);
	/* update state */
	st_data->ll_state = ST_LL_ASLEEP;

	/* communicate to platक्रमm about chip asleep */
	kim_data = st_data->kim_data;
	pdata = kim_data->kim_pdev->dev.platक्रमm_data;
	अगर (pdata->chip_asleep)
		pdata->chip_asleep(शून्य);
पूर्ण

अटल व्योम ll_device_want_to_wakeup(काष्ठा st_data_s *st_data)
अणु
	काष्ठा kim_data_s	*kim_data;
	काष्ठा ti_st_plat_data	*pdata;

	/* dअगरf actions in dअगरf states */
	चयन (st_data->ll_state) अणु
	हाल ST_LL_ASLEEP:
		send_ll_cmd(st_data, LL_WAKE_UP_ACK);	/* send wake_ack */
		अवरोध;
	हाल ST_LL_ASLEEP_TO_AWAKE:
		/* duplicate wake_ind */
		pr_err("duplicate wake_ind while waiting for Wake ack");
		अवरोध;
	हाल ST_LL_AWAKE:
		/* duplicate wake_ind */
		pr_err("duplicate wake_ind already AWAKE");
		अवरोध;
	हाल ST_LL_AWAKE_TO_ASLEEP:
		/* duplicate wake_ind */
		pr_err("duplicate wake_ind");
		अवरोध;
	पूर्ण
	/* update state */
	st_data->ll_state = ST_LL_AWAKE;

	/* communicate to platक्रमm about chip wakeup */
	kim_data = st_data->kim_data;
	pdata = kim_data->kim_pdev->dev.platक्रमm_data;
	अगर (pdata->chip_awake)
		pdata->chip_awake(शून्य);
पूर्ण

/**********************************************************************/
/* functions invoked by ST Core */

/* called when ST Core wants to
 * enable ST LL */
व्योम st_ll_enable(काष्ठा st_data_s *ll)
अणु
	ll->ll_state = ST_LL_AWAKE;
पूर्ण

/* called when ST Core /local module wants to
 * disable ST LL */
व्योम st_ll_disable(काष्ठा st_data_s *ll)
अणु
	ll->ll_state = ST_LL_INVALID;
पूर्ण

/* called when ST Core wants to update the state */
व्योम st_ll_wakeup(काष्ठा st_data_s *ll)
अणु
	अगर (likely(ll->ll_state != ST_LL_AWAKE)) अणु
		send_ll_cmd(ll, LL_WAKE_UP_IND);	/* WAKE_IND */
		ll->ll_state = ST_LL_ASLEEP_TO_AWAKE;
	पूर्ण अन्यथा अणु
		/* करोn't send the duplicate wake_indication */
		pr_err(" Chip already AWAKE ");
	पूर्ण
पूर्ण

/* called when ST Core wants the state */
अचिन्हित दीर्घ st_ll_माला_लोtate(काष्ठा st_data_s *ll)
अणु
	pr_debug(" returning state %ld", ll->ll_state);
	वापस ll->ll_state;
पूर्ण

/* called from ST Core, when a PM related packet arrives */
अचिन्हित दीर्घ st_ll_sleep_state(काष्ठा st_data_s *st_data,
	अचिन्हित अक्षर cmd)
अणु
	चयन (cmd) अणु
	हाल LL_SLEEP_IND:	/* sleep ind */
		pr_debug("sleep indication recvd");
		ll_device_want_to_sleep(st_data);
		अवरोध;
	हाल LL_SLEEP_ACK:	/* sleep ack */
		pr_err("sleep ack rcvd: host shouldn't");
		अवरोध;
	हाल LL_WAKE_UP_IND:	/* wake ind */
		pr_debug("wake indication recvd");
		ll_device_want_to_wakeup(st_data);
		अवरोध;
	हाल LL_WAKE_UP_ACK:	/* wake ack */
		pr_debug("wake ack rcvd");
		st_data->ll_state = ST_LL_AWAKE;
		अवरोध;
	शेष:
		pr_err(" unknown input/state ");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Called from ST CORE to initialize ST LL */
दीर्घ st_ll_init(काष्ठा st_data_s *ll)
अणु
	/* set state to invalid */
	ll->ll_state = ST_LL_INVALID;
	वापस 0;
पूर्ण

/* Called from ST CORE to de-initialize ST LL */
दीर्घ st_ll_deinit(काष्ठा st_data_s *ll)
अणु
	वापस 0;
पूर्ण
