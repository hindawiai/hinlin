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
#अगर_अघोषित _RTL8712_EVENT_H_
#घोषणा _RTL8712_EVENT_H_

व्योम r8712_event_handle(काष्ठा _adapter *padapter, __le32 *peventbuf);
व्योम r8712_got_addbareq_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);

क्रमागत rtl8712_c2h_event अणु
	GEN_EVT_CODE(_Read_MACREG) = 0,		/*0*/
	GEN_EVT_CODE(_Read_BBREG),
	GEN_EVT_CODE(_Read_RFREG),
	GEN_EVT_CODE(_Read_EEPROM),
	GEN_EVT_CODE(_Read_EFUSE),
	GEN_EVT_CODE(_Read_CAM),		/*5*/
	GEN_EVT_CODE(_Get_BasicRate),
	GEN_EVT_CODE(_Get_DataRate),
	GEN_EVT_CODE(_Survey),			/*8*/
	GEN_EVT_CODE(_SurveyDone),		/*9*/

	GEN_EVT_CODE(_JoinBss),			/*10*/
	GEN_EVT_CODE(_AddSTA),
	GEN_EVT_CODE(_DelSTA),
	GEN_EVT_CODE(_AtimDone),
	GEN_EVT_CODE(_TX_Report),
	GEN_EVT_CODE(_CCX_Report),		/*15*/
	GEN_EVT_CODE(_DTM_Report),
	GEN_EVT_CODE(_TX_Rate_Statistics),
	GEN_EVT_CODE(_C2HLBK),
	GEN_EVT_CODE(_FWDBG),
	GEN_EVT_CODE(_C2HFEEDBACK),		/*20*/
	GEN_EVT_CODE(_ADDBA),
	GEN_EVT_CODE(_C2HBCN),
	GEN_EVT_CODE(_ReportPwrState),		/*filen: only क्रम PCIE, USB*/
	GEN_EVT_CODE(_WPS_PBC),			/*24*/
	GEN_EVT_CODE(_ADDBAReq_Report),		/*25*/
	MAX_C2HEVT
पूर्ण;

#अगर_घोषित _RTL8712_CMD_C_

अटल काष्ठा fwevent wlanevents[] = अणु
	अणु0, शून्यपूर्ण,	/*0*/
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, &r8712_survey_event_callbackपूर्ण,		/*8*/
	अणुमाप(काष्ठा surveyकरोne_event),
		&r8712_surveyकरोne_event_callbackपूर्ण,	/*9*/

	अणु0, &r8712_joinbss_event_callbackपूर्ण,		/*10*/
	अणुमाप(काष्ठा stassoc_event), &r8712_stassoc_event_callbackपूर्ण,
	अणुमाप(काष्ठा stadel_event), &r8712_stadel_event_callbackपूर्ण,
	अणु0, &r8712_atimकरोne_event_callbackपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,	/*15*/
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,	/*fwdbg_event_callbackपूर्ण,*/
	अणु0, शून्यपूर्ण,	/*20*/
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, &r8712_cpwm_event_callbackपूर्ण,
	अणु0, &r8712_wpspbc_event_callbackपूर्ण,
	अणु0, &r8712_got_addbareq_event_callbackपूर्ण,
पूर्ण;

#पूर्ण_अगर/*_RTL8712_CMD_C_*/

#पूर्ण_अगर
