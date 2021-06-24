<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2007,2008 Freescale Semiconductor, Inc.
 *
 * This program is मुक्त software; you can redistribute  it and/or modअगरy it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __LINUX_USB_OTG_FSM_H
#घोषणा __LINUX_USB_OTG_FSM_H

#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>

#घोषणा PROTO_UNDEF	(0)
#घोषणा PROTO_HOST	(1)
#घोषणा PROTO_GADGET	(2)

#घोषणा OTG_STS_SELECTOR	0xF000	/* OTG status selector, according to
					 * OTG and EH 2.0 Chapter 6.2.3
					 * Table:6-4
					 */

#घोषणा HOST_REQUEST_FLAG	1	/* Host request flag, according to
					 * OTG and EH 2.0 Charpter 6.2.3
					 * Table:6-5
					 */

#घोषणा T_HOST_REQ_POLL		(1500)	/* 1500ms, HNP polling पूर्णांकerval */

क्रमागत otg_fsm_समयr अणु
	/* Standard OTG समयrs */
	A_WAIT_VRISE,
	A_WAIT_VFALL,
	A_WAIT_BCON,
	A_AIDL_BDIS,
	B_ASE0_BRST,
	A_BIDL_ADIS,
	B_AIDL_BDIS,

	/* Auxiliary समयrs */
	B_SE0_SRP,
	B_SRP_FAIL,
	A_WAIT_ENUM,
	B_DATA_PLS,
	B_SSEND_SRP,

	NUM_OTG_FSM_TIMERS,
पूर्ण;

/**
 * काष्ठा otg_fsm - OTG state machine according to the OTG spec
 *
 * OTG hardware Inमाला_दो
 *
 *	Common inमाला_दो क्रम A and B device
 * @id:		TRUE क्रम B-device, FALSE क्रम A-device.
 * @adp_change: TRUE when current ADP measurement (n) value, compared to the
 *		ADP measurement taken at n-2, dअगरfers by more than CADP_THR
 * @घातer_up:	TRUE when the OTG device first घातers up its USB प्रणाली and
 *		ADP measurement taken अगर ADP capable
 *
 *	A-Device state inमाला_दो
 * @a_srp_det:	TRUE अगर the A-device detects SRP
 * @a_vbus_vld:	TRUE when VBUS voltage is in regulation
 * @b_conn:	TRUE अगर the A-device detects connection from the B-device
 * @a_bus_resume: TRUE when the B-device detects that the A-device is संकेतing
 *		  a resume (K state)
 *	B-Device state inमाला_दो
 * @a_bus_suspend: TRUE when the B-device detects that the A-device has put the
 *		bus पूर्णांकo suspend
 * @a_conn:	TRUE अगर the B-device detects a connection from the A-device
 * @b_se0_srp:	TRUE when the line has been at SE0 क्रम more than the minimum
 *		समय beक्रमe generating SRP
 * @b_ssend_srp: TRUE when the VBUS has been below VOTG_SESS_VLD क्रम more than
 *		 the minimum समय beक्रमe generating SRP
 * @b_sess_vld:	TRUE when the B-device detects that the voltage on VBUS is
 *		above VOTG_SESS_VLD
 * @test_device: TRUE when the B-device चयनes to B-Host and detects an OTG
 *		test device. This must be set by host/hub driver
 *
 *	Application inमाला_दो (A-Device)
 * @a_bus_drop:	TRUE when A-device application needs to घातer करोwn the bus
 * @a_bus_req:	TRUE when A-device application wants to use the bus.
 *		FALSE to suspend the bus
 *
 *	Application inमाला_दो (B-Device)
 * @b_bus_req:	TRUE during the समय that the Application running on the
 *		B-device wants to use the bus
 *
 *	Auxilary inमाला_दो (OTG v1.3 only. Obsolete now.)
 * @a_sess_vld:	TRUE अगर the A-device detects that VBUS is above VA_SESS_VLD
 * @b_bus_suspend: TRUE when the A-device detects that the B-device has put
 *		the bus पूर्णांकo suspend
 * @b_bus_resume: TRUE when the A-device detects that the B-device is संकेतing
 *		 resume on the bus
 *
 * OTG Output status. Read only क्रम users. Updated by OTG FSM helpers defined
 * in this file
 *
 *	Outमाला_दो क्रम Both A and B device
 * @drv_vbus:	TRUE when A-device is driving VBUS
 * @loc_conn:	TRUE when the local device has संकेतed that it is connected
 *		to the bus
 * @loc_sof:	TRUE when the local device is generating activity on the bus
 * @adp_prb:	TRUE when the local device is in the process of करोing
 *		ADP probing
 *
 *	Outमाला_दो क्रम B-device state
 * @adp_sns:	TRUE when the B-device is in the process of carrying out
 *		ADP sensing
 * @data_pulse: TRUE when the B-device is perक्रमming data line pulsing
 *
 * Internal Variables
 *
 * a_set_b_hnp_en: TRUE when the A-device has successfully set the
 *		b_hnp_enable bit in the B-device.
 *		   Unused as OTG fsm uses otg->host->b_hnp_enable instead
 * b_srp_करोne:	TRUE when the B-device has completed initiating SRP
 * b_hnp_enable: TRUE when the B-device has accepted the
 *		SetFeature(b_hnp_enable) B-device.
 *		Unused as OTG fsm uses otg->gadget->b_hnp_enable instead
 * a_clr_err:	Asserted (by application ?) to clear a_vbus_err due to an
 *		overcurrent condition and causes the A-device to transition
 *		to a_रुको_vfall
 */
काष्ठा otg_fsm अणु
	/* Input */
	पूर्णांक id;
	पूर्णांक adp_change;
	पूर्णांक घातer_up;
	पूर्णांक a_srp_det;
	पूर्णांक a_vbus_vld;
	पूर्णांक b_conn;
	पूर्णांक a_bus_resume;
	पूर्णांक a_bus_suspend;
	पूर्णांक a_conn;
	पूर्णांक b_se0_srp;
	पूर्णांक b_ssend_srp;
	पूर्णांक b_sess_vld;
	पूर्णांक test_device;
	पूर्णांक a_bus_drop;
	पूर्णांक a_bus_req;
	पूर्णांक b_bus_req;

	/* Auxilary inमाला_दो */
	पूर्णांक a_sess_vld;
	पूर्णांक b_bus_resume;
	पूर्णांक b_bus_suspend;

	/* Output */
	पूर्णांक drv_vbus;
	पूर्णांक loc_conn;
	पूर्णांक loc_sof;
	पूर्णांक adp_prb;
	पूर्णांक adp_sns;
	पूर्णांक data_pulse;

	/* Internal variables */
	पूर्णांक a_set_b_hnp_en;
	पूर्णांक b_srp_करोne;
	पूर्णांक b_hnp_enable;
	पूर्णांक a_clr_err;

	/* Inक्रमmative variables. All unused as of now */
	पूर्णांक a_bus_drop_inf;
	पूर्णांक a_bus_req_inf;
	पूर्णांक a_clr_err_inf;
	पूर्णांक b_bus_req_inf;
	/* Auxilary inक्रमmative variables */
	पूर्णांक a_suspend_req_inf;

	/* Timeout indicator क्रम समयrs */
	पूर्णांक a_रुको_vrise_पंचांगout;
	पूर्णांक a_रुको_vfall_पंचांगout;
	पूर्णांक a_रुको_bcon_पंचांगout;
	पूर्णांक a_aidl_bdis_पंचांगout;
	पूर्णांक b_ase0_brst_पंचांगout;
	पूर्णांक a_bidl_adis_पंचांगout;

	काष्ठा otg_fsm_ops *ops;
	काष्ठा usb_otg *otg;

	/* Current usb protocol used: 0:undefine; 1:host; 2:client */
	पूर्णांक protocol;
	काष्ठा mutex lock;
	u8 *host_req_flag;
	काष्ठा delayed_work hnp_polling_work;
	bool state_changed;
पूर्ण;

काष्ठा otg_fsm_ops अणु
	व्योम	(*chrg_vbus)(काष्ठा otg_fsm *fsm, पूर्णांक on);
	व्योम	(*drv_vbus)(काष्ठा otg_fsm *fsm, पूर्णांक on);
	व्योम	(*loc_conn)(काष्ठा otg_fsm *fsm, पूर्णांक on);
	व्योम	(*loc_sof)(काष्ठा otg_fsm *fsm, पूर्णांक on);
	व्योम	(*start_pulse)(काष्ठा otg_fsm *fsm);
	व्योम	(*start_adp_prb)(काष्ठा otg_fsm *fsm);
	व्योम	(*start_adp_sns)(काष्ठा otg_fsm *fsm);
	व्योम	(*add_समयr)(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr समयr);
	व्योम	(*del_समयr)(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr समयr);
	पूर्णांक	(*start_host)(काष्ठा otg_fsm *fsm, पूर्णांक on);
	पूर्णांक	(*start_gadget)(काष्ठा otg_fsm *fsm, पूर्णांक on);
पूर्ण;


अटल अंतरभूत पूर्णांक otg_chrg_vbus(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	अगर (!fsm->ops->chrg_vbus)
		वापस -EOPNOTSUPP;
	fsm->ops->chrg_vbus(fsm, on);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_drv_vbus(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	अगर (!fsm->ops->drv_vbus)
		वापस -EOPNOTSUPP;
	अगर (fsm->drv_vbus != on) अणु
		fsm->drv_vbus = on;
		fsm->ops->drv_vbus(fsm, on);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_loc_conn(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	अगर (!fsm->ops->loc_conn)
		वापस -EOPNOTSUPP;
	अगर (fsm->loc_conn != on) अणु
		fsm->loc_conn = on;
		fsm->ops->loc_conn(fsm, on);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_loc_sof(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	अगर (!fsm->ops->loc_sof)
		वापस -EOPNOTSUPP;
	अगर (fsm->loc_sof != on) अणु
		fsm->loc_sof = on;
		fsm->ops->loc_sof(fsm, on);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_start_pulse(काष्ठा otg_fsm *fsm)
अणु
	अगर (!fsm->ops->start_pulse)
		वापस -EOPNOTSUPP;
	अगर (!fsm->data_pulse) अणु
		fsm->data_pulse = 1;
		fsm->ops->start_pulse(fsm);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_start_adp_prb(काष्ठा otg_fsm *fsm)
अणु
	अगर (!fsm->ops->start_adp_prb)
		वापस -EOPNOTSUPP;
	अगर (!fsm->adp_prb) अणु
		fsm->adp_sns = 0;
		fsm->adp_prb = 1;
		fsm->ops->start_adp_prb(fsm);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_start_adp_sns(काष्ठा otg_fsm *fsm)
अणु
	अगर (!fsm->ops->start_adp_sns)
		वापस -EOPNOTSUPP;
	अगर (!fsm->adp_sns) अणु
		fsm->adp_sns = 1;
		fsm->ops->start_adp_sns(fsm);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_add_समयr(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr समयr)
अणु
	अगर (!fsm->ops->add_समयr)
		वापस -EOPNOTSUPP;
	fsm->ops->add_समयr(fsm, समयr);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_del_समयr(काष्ठा otg_fsm *fsm, क्रमागत otg_fsm_समयr समयr)
अणु
	अगर (!fsm->ops->del_समयr)
		वापस -EOPNOTSUPP;
	fsm->ops->del_समयr(fsm, समयr);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक otg_start_host(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	अगर (!fsm->ops->start_host)
		वापस -EOPNOTSUPP;
	वापस fsm->ops->start_host(fsm, on);
पूर्ण

अटल अंतरभूत पूर्णांक otg_start_gadget(काष्ठा otg_fsm *fsm, पूर्णांक on)
अणु
	अगर (!fsm->ops->start_gadget)
		वापस -EOPNOTSUPP;
	वापस fsm->ops->start_gadget(fsm, on);
पूर्ण

पूर्णांक otg_statemachine(काष्ठा otg_fsm *fsm);

#पूर्ण_अगर /* __LINUX_USB_OTG_FSM_H */
