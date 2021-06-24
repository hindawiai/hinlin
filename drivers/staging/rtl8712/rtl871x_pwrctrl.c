<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_pwrctrl.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL871X_PWRCTRL_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "osdep_intf.h"

#घोषणा RTL8712_SDIO_LOCAL_BASE 0X10100000
#घोषणा SDIO_HCPWM (RTL8712_SDIO_LOCAL_BASE + 0x0081)

व्योम r8712_set_rpwm(काष्ठा _adapter *padapter, u8 val8)
अणु
	u8	rpwm;
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	अगर (pwrpriv->rpwm == val8) अणु
		अगर (pwrpriv->rpwm_retry == 0)
			वापस;
	पूर्ण
	अगर (padapter->driver_stopped || padapter->surprise_हटाओd)
		वापस;
	rpwm = val8 | pwrpriv->tog;
	चयन (val8) अणु
	हाल PS_STATE_S1:
		pwrpriv->cpwm = val8;
		अवरोध;
	हाल PS_STATE_S2:/* only क्रम USB normal घातersave mode use,
			  * temp mark some code.
			  */
	हाल PS_STATE_S3:
	हाल PS_STATE_S4:
		pwrpriv->cpwm = val8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	pwrpriv->rpwm_retry = 0;
	pwrpriv->rpwm = val8;
	r8712_ग_लिखो8(padapter, 0x1025FE58, rpwm);
	pwrpriv->tog += 0x80;
पूर्ण

व्योम r8712_set_ps_mode(काष्ठा _adapter *padapter, uपूर्णांक ps_mode, uपूर्णांक smart_ps)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	अगर (ps_mode > PM_Card_Disable)
		वापस;
	/* अगर driver is in active state, we करोnt need set smart_ps.*/
	अगर (ps_mode == PS_MODE_ACTIVE)
		smart_ps = 0;
	अगर ((pwrpriv->pwr_mode != ps_mode) || (pwrpriv->smart_ps != smart_ps)) अणु
		अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
			pwrpriv->bSleep = true;
		अन्यथा
			pwrpriv->bSleep = false;
		pwrpriv->pwr_mode = ps_mode;
		pwrpriv->smart_ps = smart_ps;
		schedule_work(&pwrpriv->SetPSModeWorkItem);
	पूर्ण
पूर्ण

/*
 * Caller:ISR handler...
 *
 * This will be called when CPWM पूर्णांकerrupt is up.
 *
 * using to update cpwn of drv; and drv will make a decision to up or
 * करोwn pwr level
 */
व्योम r8712_cpwm_पूर्णांक_hdl(काष्ठा _adapter *padapter,
			काष्ठा reportpwrstate_parm *preportpwrstate)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &(padapter->pwrctrlpriv);
	काष्ठा cmd_priv	*pcmdpriv = &(padapter->cmdpriv);

	अगर (pwrpriv->cpwm_tog == ((preportpwrstate->state) & 0x80))
		वापस;
	del_समयr(&padapter->pwrctrlpriv.rpwm_check_समयr);
	mutex_lock(&pwrpriv->mutex_lock);
	pwrpriv->cpwm = (preportpwrstate->state) & 0xf;
	अगर (pwrpriv->cpwm >= PS_STATE_S2) अणु
		अगर (pwrpriv->alives & CMD_ALIVE)
			complete(&(pcmdpriv->cmd_queue_comp));
	पूर्ण
	pwrpriv->cpwm_tog = (preportpwrstate->state) & 0x80;
	mutex_unlock(&pwrpriv->mutex_lock);
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_task_alive(काष्ठा pwrctrl_priv *pwrctrl, uपूर्णांक tag)
अणु
		pwrctrl->alives |= tag;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_task_alive(काष्ठा pwrctrl_priv *pwrctrl, uपूर्णांक tag)
अणु
	अगर (pwrctrl->alives & tag)
		pwrctrl->alives ^= tag;
पूर्ण

अटल व्योम _rpwm_check_handler (काष्ठा _adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	अगर (padapter->driver_stopped || padapter->surprise_हटाओd)
		वापस;
	अगर (pwrpriv->cpwm != pwrpriv->rpwm)
		schedule_work(&pwrpriv->rpwm_workitem);
पूर्ण

अटल व्योम SetPSModeWorkItemCallback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = container_of(work,
				       काष्ठा pwrctrl_priv, SetPSModeWorkItem);
	काष्ठा _adapter *padapter = container_of(pwrpriv,
				    काष्ठा _adapter, pwrctrlpriv);
	अगर (!pwrpriv->bSleep) अणु
		mutex_lock(&pwrpriv->mutex_lock);
		अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
			r8712_set_rpwm(padapter, PS_STATE_S4);
		mutex_unlock(&pwrpriv->mutex_lock);
	पूर्ण
पूर्ण

अटल व्योम rpwm_workitem_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = container_of(work,
				       काष्ठा pwrctrl_priv, rpwm_workitem);
	काष्ठा _adapter *padapter = container_of(pwrpriv,
				    काष्ठा _adapter, pwrctrlpriv);
	अगर (pwrpriv->cpwm != pwrpriv->rpwm) अणु
		mutex_lock(&pwrpriv->mutex_lock);
		r8712_पढ़ो8(padapter, SDIO_HCPWM);
		pwrpriv->rpwm_retry = 1;
		r8712_set_rpwm(padapter, pwrpriv->rpwm);
		mutex_unlock(&pwrpriv->mutex_lock);
	पूर्ण
पूर्ण

अटल व्योम rpwm_check_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा _adapter *adapter =
		from_समयr(adapter, t, pwrctrlpriv.rpwm_check_समयr);

	_rpwm_check_handler(adapter);
पूर्ण

व्योम r8712_init_pwrctrl_priv(काष्ठा _adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	स_रखो((अचिन्हित अक्षर *)pwrctrlpriv, 0, माप(काष्ठा pwrctrl_priv));
	mutex_init(&pwrctrlpriv->mutex_lock);
	pwrctrlpriv->cpwm = PS_STATE_S4;
	pwrctrlpriv->pwr_mode = PS_MODE_ACTIVE;
	pwrctrlpriv->smart_ps = 0;
	pwrctrlpriv->tog = 0x80;
/* clear RPWM to ensure driver and fw back to initial state. */
	r8712_ग_लिखो8(padapter, 0x1025FE58, 0);
	INIT_WORK(&pwrctrlpriv->SetPSModeWorkItem, SetPSModeWorkItemCallback);
	INIT_WORK(&pwrctrlpriv->rpwm_workitem, rpwm_workitem_callback);
	समयr_setup(&pwrctrlpriv->rpwm_check_समयr, rpwm_check_handler, 0);
पूर्ण

/*
 * Caller: r8712_cmd_thपढ़ो
 * Check अगर the fw_pwrstate is okay क्रम issuing cmd.
 * If not (cpwm should be is less than P2 state), then the sub-routine
 * will उठाओ the cpwm to be greater than or equal to P2.
 * Calling Context: Passive
 * Return Value:
 * 0:	    r8712_cmd_thपढ़ो can issue cmds to firmware afterwards.
 * -EINVAL: r8712_cmd_thपढ़ो can not करो anything.
 */
पूर्णांक r8712_रेजिस्टर_cmd_alive(काष्ठा _adapter *padapter)
अणु
	पूर्णांक res = 0;
	काष्ठा pwrctrl_priv *pwrctrl = &padapter->pwrctrlpriv;

	mutex_lock(&pwrctrl->mutex_lock);
	रेजिस्टर_task_alive(pwrctrl, CMD_ALIVE);
	अगर (pwrctrl->cpwm < PS_STATE_S2) अणु
		r8712_set_rpwm(padapter, PS_STATE_S3);
		res = -EINVAL;
	पूर्ण
	mutex_unlock(&pwrctrl->mutex_lock);
	वापस res;
पूर्ण

/*
 * Caller: ISR
 * If ISR's txकरोne,
 * No more pkts क्रम TX,
 * Then driver shall call this fun. to घातer करोwn firmware again.
 */
व्योम r8712_unरेजिस्टर_cmd_alive(काष्ठा _adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrctrl = &padapter->pwrctrlpriv;

	mutex_lock(&pwrctrl->mutex_lock);
	unरेजिस्टर_task_alive(pwrctrl, CMD_ALIVE);
	अगर ((pwrctrl->cpwm > PS_STATE_S2) &&
	   (pwrctrl->pwr_mode > PS_MODE_ACTIVE)) अणु
		अगर ((pwrctrl->alives == 0) &&
		    (check_fwstate(&padapter->mlmepriv,
		     _FW_UNDER_LINKING) != true)) अणु
			r8712_set_rpwm(padapter, PS_STATE_S0);
		पूर्ण
	पूर्ण
	mutex_unlock(&pwrctrl->mutex_lock);
पूर्ण
