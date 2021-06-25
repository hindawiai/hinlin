<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 *
 * Author: Jun Li
 */

#अगर_अघोषित __DRIVERS_USB_CHIPIDEA_OTG_FSM_H
#घोषणा __DRIVERS_USB_CHIPIDEA_OTG_FSM_H

#समावेश <linux/usb/otg-fsm.h>

/*
 *  A-DEVICE timing  स्थिरants
 */

/* Wait क्रम VBUS Rise  */
#घोषणा TA_WAIT_VRISE        (100)	/* a_रुको_vrise: section 7.1.2
					 * a_रुको_vrise_पंचांगr: section 7.4.5.1
					 * TA_VBUS_RISE <= 100ms, section 4.4
					 * Table 4-1: Electrical Characteristics
					 * ->DC Electrical Timing
					 */
/* Wait क्रम VBUS Fall  */
#घोषणा TA_WAIT_VFALL        (1000)	/* a_रुको_vfall: section 7.1.7
					 * a_रुको_vfall_पंचांगr: section: 7.4.5.2
					 */
/* Wait क्रम B-Connect */
#घोषणा TA_WAIT_BCON         (10000)	/* a_रुको_bcon: section 7.1.3
					 * TA_WAIT_BCON: should be between 1100
					 * and 30000 ms, section 5.5, Table 5-1
					 */
/* A-Idle to B-Disconnect */
#घोषणा TA_AIDL_BDIS         (5000)	/* a_suspend min 200 ms, section 5.2.1
					 * TA_AIDL_BDIS: section 5.5, Table 5-1
					 */
/* B-Idle to A-Disconnect */
#घोषणा TA_BIDL_ADIS         (500)	/* TA_BIDL_ADIS: section 5.2.1
					 * 500ms is used क्रम B चयन to host
					 * क्रम safe
					 */

/*
 * B-device timing स्थिरants
 */

/* Data-Line Pulse Time*/
#घोषणा TB_DATA_PLS          (10)	/* b_srp_init,जारी 5~10ms
					 * section:5.1.3
					 */
/* SRP Fail Time  */
#घोषणा TB_SRP_FAIL          (6000)	/* b_srp_init,fail समय 5~6s
					 * section:5.1.6
					 */
/* A-SE0 to B-Reset  */
#घोषणा TB_ASE0_BRST         (155)	/* minimum 155 ms, section:5.3.1 */
/* SE0 Time Beक्रमe SRP */
#घोषणा TB_SE0_SRP           (1000)	/* b_idle,minimum 1s, section:5.1.2 */
/* SSEND समय beक्रमe SRP */
#घोषणा TB_SSEND_SRP         (1500)	/* minimum 1.5 sec, section:5.1.2 */

#घोषणा TB_AIDL_BDIS         (20)	/* 4ms ~ 150ms, section 5.2.1 */

#अगर IS_ENABLED(CONFIG_USB_OTG_FSM)

पूर्णांक ci_hdrc_otg_fsm_init(काष्ठा ci_hdrc *ci);
पूर्णांक ci_otg_fsm_work(काष्ठा ci_hdrc *ci);
irqवापस_t ci_otg_fsm_irq(काष्ठा ci_hdrc *ci);
व्योम ci_hdrc_otg_fsm_start(काष्ठा ci_hdrc *ci);
व्योम ci_hdrc_otg_fsm_हटाओ(काष्ठा ci_hdrc *ci);

#अन्यथा

अटल अंतरभूत पूर्णांक ci_hdrc_otg_fsm_init(काष्ठा ci_hdrc *ci)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ci_otg_fsm_work(काष्ठा ci_hdrc *ci)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत irqवापस_t ci_otg_fsm_irq(काष्ठा ci_hdrc *ci)
अणु
	वापस IRQ_NONE;
पूर्ण

अटल अंतरभूत व्योम ci_hdrc_otg_fsm_start(काष्ठा ci_hdrc *ci)
अणु

पूर्ण

अटल अंतरभूत व्योम ci_hdrc_otg_fsm_हटाओ(काष्ठा ci_hdrc *ci)
अणु

पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __DRIVERS_USB_CHIPIDEA_OTG_FSM_H */
