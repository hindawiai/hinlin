<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL871X_PWRCTRL_H_
#घोषणा __RTL871X_PWRCTRL_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

#घोषणा CMD_ALIVE	BIT(2)

क्रमागत Power_Mgnt अणु
	PS_MODE_ACTIVE	= 0,
	PS_MODE_MIN,
	PS_MODE_MAX,
	PS_MODE_DTIM,
	PS_MODE_VOIP,
	PS_MODE_UAPSD_WMM,
	PS_MODE_UAPSD,
	PS_MODE_IBSS,
	PS_MODE_WWLAN,
	PM_Radio_Off,
	PM_Card_Disable,
	PS_MODE_NUM
पूर्ण;

/*
 * BIT[2:0] = HW state
 * BIT[3] = Protocol PS state, 0: रेजिस्टर active state,
 *				1: रेजिस्टर sleep state
 * BIT[4] = sub-state
 */

#घोषणा		PS_DPS				BIT(0)
#घोषणा		PS_LCLK				(PS_DPS)
#घोषणा	PS_RF_OFF			BIT(1)
#घोषणा	PS_ALL_ON			BIT(2)
#घोषणा	PS_ST_ACTIVE		BIT(3)
#घोषणा	PS_LP				BIT(4)	/* low perक्रमmance */

#घोषणा	PS_STATE_MASK		(0x0F)
#घोषणा	PS_STATE_HW_MASK	(0x07)
#घोषणा		PS_SEQ_MASK		(0xc0)

#घोषणा	PS_STATE(x)			(PS_STATE_MASK & (x))
#घोषणा	PS_STATE_HW(x)	(PS_STATE_HW_MASK & (x))
#घोषणा	PS_SEQ(x)			(PS_SEQ_MASK & (x))

#घोषणा	PS_STATE_S0		(PS_DPS)
#घोषणा		PS_STATE_S1		(PS_LCLK)
#घोषणा	PS_STATE_S2		(PS_RF_OFF)
#घोषणा		PS_STATE_S3		(PS_ALL_ON)
#घोषणा	PS_STATE_S4		((PS_ST_ACTIVE) | (PS_ALL_ON))

#घोषणा		PS_IS_RF_ON(x)		((x) & (PS_ALL_ON))
#घोषणा		PS_IS_ACTIVE(x)		((x) & (PS_ST_ACTIVE))
#घोषणा		CLR_PS_STATE(x)	((x) = ((x) & (0xF0)))

काष्ठा reportpwrstate_parm अणु
	अचिन्हित अक्षर mode;
	अचिन्हित अक्षर state; /* the CPWM value */
	अचिन्हित लघु rsvd;
पूर्ण;

काष्ठा	pwrctrl_priv अणु
	काष्ठा mutex mutex_lock;
	/*अस्थिर*/ u8 rpwm; /* requested घातer state क्रम fw */
	/* fw current घातer state. updated when 1. पढ़ो from HCPWM or
	 * 2. driver lowers घातer level
	 */
	/*अस्थिर*/ u8 cpwm;
	/*अस्थिर*/ u8 tog; /* toggling */
	/*अस्थिर*/ u8 cpwm_tog; /* toggling */
	/*अस्थिर*/ u8 tgt_rpwm; /* wanted घातer state */
	uपूर्णांक pwr_mode;
	uपूर्णांक smart_ps;
	uपूर्णांक alives;
	uपूर्णांक ImrContent;	/* used to store original imr. */
	uपूर्णांक bSleep; /* sleep -> active is dअगरferent from active -> sleep. */

	काष्ठा work_काष्ठा SetPSModeWorkItem;
	काष्ठा work_काष्ठा rpwm_workitem;
	काष्ठा समयr_list rpwm_check_समयr;
	u8	rpwm_retry;
	uपूर्णांक	bSetPSModeWorkItemInProgress;

	spinlock_t pnp_pwr_mgnt_lock;
	s32	pnp_current_pwr_state;
	u8	pnp_bstop_trx;
	u8	pnp_wwirp_pending;
पूर्ण;

व्योम r8712_init_pwrctrl_priv(काष्ठा _adapter *adapter);
पूर्णांक r8712_रेजिस्टर_cmd_alive(काष्ठा _adapter *padapter);
व्योम r8712_unरेजिस्टर_cmd_alive(काष्ठा _adapter *padapter);
व्योम r8712_cpwm_पूर्णांक_hdl(काष्ठा _adapter *padapter,
			काष्ठा reportpwrstate_parm *preportpwrstate);
व्योम r8712_set_ps_mode(काष्ठा _adapter *padapter, uपूर्णांक ps_mode,
			uपूर्णांक smart_ps);
व्योम r8712_set_rpwm(काष्ठा _adapter *padapter, u8 val8);

#पूर्ण_अगर  /* __RTL871X_PWRCTRL_H_ */
