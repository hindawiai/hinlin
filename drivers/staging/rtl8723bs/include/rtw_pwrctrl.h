<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_PWRCTRL_H_
#घोषणा __RTW_PWRCTRL_H_

#समावेश <linux/mutex.h>

#घोषणा FW_PWR0	0
#घोषणा FW_PWR1		1
#घोषणा FW_PWR2		2
#घोषणा FW_PWR3		3


#घोषणा HW_PWR0	7
#घोषणा HW_PWR1		6
#घोषणा HW_PWR2		2
#घोषणा HW_PWR3	0
#घोषणा HW_PWR4	8

#घोषणा FW_PWRMSK	0x7


#घोषणा XMIT_ALIVE	BIT(0)
#घोषणा RECV_ALIVE	BIT(1)
#घोषणा CMD_ALIVE	BIT(2)
#घोषणा EVT_ALIVE	BIT(3)
#घोषणा BTCOEX_ALIVE	BIT(4)


क्रमागत अणु
	PS_MODE_ACTIVE	= 0,
	PS_MODE_MIN,
	PS_MODE_MAX,
	PS_MODE_DTIM,	/* PS_MODE_SELF_DEFINED */
	PS_MODE_VOIP,
	PS_MODE_UAPSD_WMM,
	PS_MODE_UAPSD,
	PS_MODE_IBSS,
	PS_MODE_WWLAN,
	PM_Radio_Off,
	PM_Card_Disable,
	PS_MODE_NUM,
पूर्ण;

/*
	BIT[2:0] = HW state
	BIT[3] = Protocol PS state,   0: रेजिस्टर active state , 1: रेजिस्टर sleep state
	BIT[4] = sub-state
*/

#घोषणा PS_DPS				BIT(0)
#घोषणा PS_LCLK				(PS_DPS)
#घोषणा PS_RF_OFF			BIT(1)
#घोषणा PS_ALL_ON			BIT(2)
#घोषणा PS_ST_ACTIVE		BIT(3)

#घोषणा PS_ISR_ENABLE		BIT(4)
#घोषणा PS_IMR_ENABLE		BIT(5)
#घोषणा PS_ACK				BIT(6)
#घोषणा PS_TOGGLE			BIT(7)

#घोषणा PS_STATE_MASK		(0x0F)
#घोषणा PS_STATE_HW_MASK	(0x07)
#घोषणा PS_SEQ_MASK			(0xc0)

#घोषणा PS_STATE(x)		(PS_STATE_MASK & (x))
#घोषणा PS_STATE_HW(x)	(PS_STATE_HW_MASK & (x))
#घोषणा PS_SEQ(x)		(PS_SEQ_MASK & (x))

#घोषणा PS_STATE_S0		(PS_DPS)
#घोषणा PS_STATE_S1		(PS_LCLK)
#घोषणा PS_STATE_S2		(PS_RF_OFF)
#घोषणा PS_STATE_S3		(PS_ALL_ON)
#घोषणा PS_STATE_S4		((PS_ST_ACTIVE) | (PS_ALL_ON))


#घोषणा PS_IS_RF_ON(x)	((x) & (PS_ALL_ON))
#घोषणा PS_IS_ACTIVE(x)	((x) & (PS_ST_ACTIVE))
#घोषणा CLR_PS_STATE(x)	((x) = ((x) & (0xF0)))


काष्ठा reportpwrstate_parm अणु
	अचिन्हित अक्षर mode;
	अचिन्हित अक्षर state; /* the CPWM value */
	अचिन्हित लघु rsvd;
पूर्ण;

#घोषणा LPS_DELAY_TIME	(1 * HZ) /*  1 sec */

#घोषणा EXE_PWR_NONE	0x01
#घोषणा EXE_PWR_IPS		0x02
#घोषणा EXE_PWR_LPS		0x04

/*  RF state. */
क्रमागत rt_rf_घातer_state अणु
	rf_on,		/*  RF is on after RFSleep or RFOff */
	rf_sleep,	/*  802.11 Power Save mode */
	rf_off,		/*  HW/SW Radio OFF or Inactive Power Save */
	/* Add the new RF state above this line ===== */
	rf_max
पूर्ण;

/*  RF Off Level क्रम IPS or HW/SW radio off */
#घोषणा	RT_RF_OFF_LEVL_ASPM			BIT(0)	/*  PCI ASPM */
#घोषणा	RT_RF_OFF_LEVL_CLK_REQ		BIT(1)	/*  PCI घड़ी request */
#घोषणा	RT_RF_OFF_LEVL_PCI_D3			BIT(2)	/*  PCI D3 mode */
#घोषणा	RT_RF_OFF_LEVL_HALT_NIC		BIT(3)	/*  NIC halt, re-initialize hw parameters */
#घोषणा	RT_RF_OFF_LEVL_FREE_FW		BIT(4)	/*  FW मुक्त, re-करोwnload the FW */
#घोषणा	RT_RF_OFF_LEVL_FW_32K		BIT(5)	/*  FW in 32k */
#घोषणा	RT_RF_PS_LEVEL_ALWAYS_ASPM	BIT(6)	/*  Always enable ASPM and Clock Req in initialization. */
#घोषणा	RT_RF_LPS_DISALBE_2R			BIT(30)	/*  When LPS is on, disable 2R अगर no packet is received or transmitted. */
#घोषणा	RT_RF_LPS_LEVEL_ASPM			BIT(31)	/*  LPS with ASPM */

#घोषणा	RT_IN_PS_LEVEL(ppsc, _PS_FLAG)		((ppsc->cur_ps_level & _PS_FLAG) ? true : false)
#घोषणा	RT_CLEAR_PS_LEVEL(ppsc, _PS_FLAG)	(ppsc->cur_ps_level &= (~(_PS_FLAG)))
#घोषणा	RT_SET_PS_LEVEL(ppsc, _PS_FLAG)		(ppsc->cur_ps_level |= _PS_FLAG)

/*  ASPM OSC Control bit, added by Roger, 2013.03.29. */
#घोषणा	RT_PCI_ASPM_OSC_IGNORE		0	 /*  PCI ASPM ignore OSC control in शेष */
#घोषणा	RT_PCI_ASPM_OSC_ENABLE		BIT0 /*  PCI ASPM controlled by OS according to ACPI Spec 5.0 */
#घोषणा	RT_PCI_ASPM_OSC_DISABLE		BIT1 /*  PCI ASPM controlled by driver or BIOS, i.e., क्रमce enable ASPM */

क्रमागत अणु
	PSBBREG_RF0 = 0,
	PSBBREG_RF1,
	PSBBREG_RF2,
	PSBBREG_AFE0,
	PSBBREG_TOTALCNT
पूर्ण;

क्रमागत अणु /*  क्रम ips_mode */
	IPS_NONE = 0,
	IPS_NORMAL,
	IPS_LEVEL_2,
	IPS_NUM
पूर्ण;

/*  Design क्रम pwrctrl_priv.ips_deny, 32 bits क्रम 32 reasons at most */
क्रमागत ps_deny_reason अणु
	PS_DENY_DRV_INITIAL = 0,
	PS_DENY_SCAN,
	PS_DENY_JOIN,
	PS_DENY_DISCONNECT,
	PS_DENY_SUSPEND,
	PS_DENY_IOCTL,
	PS_DENY_MGNT_TX,
	PS_DENY_DRV_REMOVE = 30,
	PS_DENY_OTHERS = 31
पूर्ण;

काष्ठा pwrctrl_priv अणु
	काष्ठा mutex lock;
	अस्थिर u8 rpwm; /*  requested घातer state क्रम fw */
	अस्थिर u8 cpwm; /*  fw current घातer state. updated when 1. पढ़ो from HCPWM 2. driver lowers घातer level */
	अस्थिर u8 tog; /*  toggling */
	अस्थिर u8 cpwm_tog; /*  toggling */

	u8 pwr_mode;
	u8 smart_ps;
	u8 bcn_ant_mode;
	u8 dtim;

	u32 alives;
	काष्ठा work_काष्ठा cpwm_event;
	u8 brpwmसमयout;
	काष्ठा work_काष्ठा rpwmसमयoutwi;
	काष्ठा समयr_list pwr_rpwm_समयr;
	u8 bघातer_saving; /* क्रम LPS/IPS */

	u8 b_hw_radio_off;
	u8 reg_rfoff;
	u8 reg_pdnmode; /* घातerकरोwn mode */
	u32 rfoff_reason;

	/* RF OFF Level */
	u32 cur_ps_level;
	u32 reg_rfps_level;

	uपूर्णांक	ips_enter_cnts;
	uपूर्णांक	ips_leave_cnts;

	u8 ips_mode;
	u8 ips_org_mode;
	u8 ips_mode_req; /*  used to accept the mode setting request, will update to ipsmode later */
	bool bips_processing;
	अचिन्हित दीर्घ ips_deny_समय; /* will deny IPS when प्रणाली समय is smaller than this */
	u8 pre_ips_type;/*  0: शेष flow, 1: carddisbale flow */

	/*  ps_deny: अगर 0, घातer save is मुक्त to go; otherwise deny all kinds of घातer save. */
	/*  Use क्रमागत ps_deny_reason to decide reason. */
	/*  Don't access this variable directly without control function, */
	/*  and this variable should be रक्षित by lock. */
	u32 ps_deny;

	u8 ps_processing; /* temporarily used to mark whether in rtw_ps_processor */

	u8 fw_psmode_अगरace_id;
	u8 bLeisurePs;
	u8 LpsIdleCount;
	u8 घातer_mgnt;
	u8 org_घातer_mgnt;
	bool fw_current_in_ps_mode;
	अचिन्हित दीर्घ	DelayLPSLastTimeStamp;
	s32		pnp_current_pwr_state;
	u8 pnp_bstop_trx;


	u8 bInternalAutoSuspend;
	u8 bInSuspend;

	u8 bAutoResume;
	u8 स्वतःpm_cnt;

	u8 bSupportRemoteWakeup;
	u8 wowlan_wake_reason;
	u8 wowlan_ap_mode;
	u8 wowlan_mode;
	काष्ठा समयr_list	pwr_state_check_समयr;
	काष्ठा adapter *adapter;
	पूर्णांक		pwr_state_check_पूर्णांकerval;
	u8 pwr_state_check_cnts;

	पूर्णांक		ps_flag; /* used by स्वतःsuspend */

	क्रमागत rt_rf_घातer_state	rf_pwrstate;/* cur घातer state, only क्रम IPS */
	/* rt_rf_घातer_state	current_rfpwrstate; */
	क्रमागत rt_rf_घातer_state	change_rfpwrstate;

	u8 bHWPowerकरोwn; /* घातer करोwn mode selection. 0:radio off, 1:घातer करोwn */
	u8 bHWPwrPindetect; /* come from registrypriv.hwpwrp_detect. enable घातer करोwn function. 0:disable, 1:enable */
	u8 bkeepfwalive;
	u8 brfoffbyhw;
	अचिन्हित दीर्घ PS_BBRegBackup[PSBBREG_TOTALCNT];
पूर्ण;

#घोषणा rtw_ips_mode_req(pwrctl, ips_mode) \
	((pwrctl)->ips_mode_req = (ips_mode))

#घोषणा RTW_PWR_STATE_CHK_INTERVAL 2000

#घोषणा _rtw_set_pwr_state_check_समयr(pwrctl, ms) \
	करो अणु \
		_set_समयr(&(pwrctl)->pwr_state_check_समयr, (ms)); \
	पूर्ण जबतक (0)

#घोषणा rtw_set_pwr_state_check_समयr(pwrctl) \
	_rtw_set_pwr_state_check_समयr((pwrctl), (pwrctl)->pwr_state_check_पूर्णांकerval)

बाह्य व्योम rtw_init_pwrctrl_priv(काष्ठा adapter *adapter);
बाह्य व्योम rtw_मुक्त_pwrctrl_priv(काष्ठा adapter *adapter);

s32 rtw_रेजिस्टर_task_alive(काष्ठा adapter *, u32 task);
व्योम rtw_unरेजिस्टर_task_alive(काष्ठा adapter *, u32 task);
बाह्य s32 rtw_रेजिस्टर_tx_alive(काष्ठा adapter *padapter);
बाह्य व्योम rtw_unरेजिस्टर_tx_alive(काष्ठा adapter *padapter);
बाह्य s32 rtw_रेजिस्टर_cmd_alive(काष्ठा adapter *padapter);
बाह्य व्योम rtw_unरेजिस्टर_cmd_alive(काष्ठा adapter *padapter);
बाह्य व्योम cpwm_पूर्णांक_hdl(काष्ठा adapter *padapter, काष्ठा reportpwrstate_parm *preportpwrstate);
बाह्य व्योम LPS_Leave_check(काष्ठा adapter *padapter);

बाह्य व्योम LeaveAllPowerSaveMode(काष्ठा adapter *Adapter);
बाह्य व्योम LeaveAllPowerSaveModeDirect(काष्ठा adapter *Adapter);
व्योम _ips_enter(काष्ठा adapter *padapter);
व्योम ips_enter(काष्ठा adapter *padapter);
पूर्णांक _ips_leave(काष्ठा adapter *padapter);
पूर्णांक ips_leave(काष्ठा adapter *padapter);

व्योम rtw_ps_processor(काष्ठा adapter *padapter);

s32 LPS_RF_ON_check(काष्ठा adapter *padapter, u32 delay_ms);
व्योम LPS_Enter(काष्ठा adapter *padapter, स्थिर अक्षर *msg);
व्योम LPS_Leave(काष्ठा adapter *padapter, स्थिर अक्षर *msg);
व्योम traffic_check_क्रम_leave_lps(काष्ठा adapter *padapter, u8 tx, u32 tx_packets);
व्योम rtw_set_ps_mode(काष्ठा adapter *padapter, u8 ps_mode, u8 smart_ps, u8 bcn_ant_mode, स्थिर अक्षर *msg);
व्योम rtw_set_rpwm(काष्ठा adapter *padapter, u8 val8);

व्योम rtw_set_ips_deny(काष्ठा adapter *padapter, u32 ms);
पूर्णांक _rtw_pwr_wakeup(काष्ठा adapter *padapter, u32 ips_deffer_ms, स्थिर अक्षर *caller);
#घोषणा rtw_pwr_wakeup(adapter) _rtw_pwr_wakeup(adapter, RTW_PWR_STATE_CHK_INTERVAL, __func__)
#घोषणा rtw_pwr_wakeup_ex(adapter, ips_deffer_ms) _rtw_pwr_wakeup(adapter, ips_deffer_ms, __func__)
पूर्णांक rtw_pm_set_ips(काष्ठा adapter *padapter, u8 mode);
पूर्णांक rtw_pm_set_lps(काष्ठा adapter *padapter, u8 mode);

व्योम rtw_ps_deny(काष्ठा adapter *padapter, क्रमागत ps_deny_reason reason);
व्योम rtw_ps_deny_cancel(काष्ठा adapter *padapter, क्रमागत ps_deny_reason reason);
u32 rtw_ps_deny_get(काष्ठा adapter *padapter);

#पूर्ण_अगर  /* __RTL871X_PWRCTRL_H_ */
