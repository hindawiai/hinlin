<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#अगर_अघोषित _ZD_RF_H
#घोषणा _ZD_RF_H

#घोषणा UW2451_RF			0x2
#घोषणा UCHIP_RF			0x3
#घोषणा AL2230_RF			0x4
#घोषणा AL7230B_RF			0x5	/* a,b,g */
#घोषणा THETA_RF			0x6
#घोषणा AL2210_RF			0x7
#घोषणा MAXIM_NEW_RF			0x8
#घोषणा UW2453_RF			0x9
#घोषणा AL2230S_RF			0xa
#घोषणा RALINK_RF			0xb
#घोषणा INTERSIL_RF			0xc
#घोषणा RF2959_RF			0xd
#घोषणा MAXIM_NEW2_RF			0xe
#घोषणा PHILIPS_RF			0xf

#घोषणा RF_CHANNEL(ch) [(ch)-1]

/* Provides functions of the RF transceiver. */

क्रमागत अणु
	RF_REG_BITS = 6,
	RF_VALUE_BITS = 18,
	RF_RV_BITS = RF_REG_BITS + RF_VALUE_BITS,
पूर्ण;

काष्ठा zd_rf अणु
	u8 type;

	u8 channel;

	/* whether channel पूर्णांकegration and calibration should be updated
	 * शेषs to 1 (yes) */
	u8 update_channel_पूर्णांक:1;

	/* whether ZD_CR47 should be patched from the EEPROM, अगर the appropriate
	 * flag is set in the POD. The venकरोr driver suggests that this should
	 * be करोne क्रम all RF's, but a bug in their code prevents but their
	 * HW_OverWritePhyRegFromE2P() routine from ever taking effect. */
	u8 patch_cck_gain:1;

	/* निजी RF driver data */
	व्योम *priv;

	/* RF-specअगरic functions */
	पूर्णांक (*init_hw)(काष्ठा zd_rf *rf);
	पूर्णांक (*set_channel)(काष्ठा zd_rf *rf, u8 channel);
	पूर्णांक (*चयन_radio_on)(काष्ठा zd_rf *rf);
	पूर्णांक (*चयन_radio_off)(काष्ठा zd_rf *rf);
	पूर्णांक (*patch_6m_band_edge)(काष्ठा zd_rf *rf, u8 channel);
	व्योम (*clear)(काष्ठा zd_rf *rf);
पूर्ण;

स्थिर अक्षर *zd_rf_name(u8 type);
व्योम zd_rf_init(काष्ठा zd_rf *rf);
व्योम zd_rf_clear(काष्ठा zd_rf *rf);
पूर्णांक zd_rf_init_hw(काष्ठा zd_rf *rf, u8 type);

पूर्णांक zd_rf_scnprपूर्णांक_id(काष्ठा zd_rf *rf, अक्षर *buffer, माप_प्रकार size);

पूर्णांक zd_rf_set_channel(काष्ठा zd_rf *rf, u8 channel);

पूर्णांक zd_चयन_radio_on(काष्ठा zd_rf *rf);
पूर्णांक zd_चयन_radio_off(काष्ठा zd_rf *rf);

पूर्णांक zd_rf_patch_6m_band_edge(काष्ठा zd_rf *rf, u8 channel);
पूर्णांक zd_rf_generic_patch_6m(काष्ठा zd_rf *rf, u8 channel);

अटल अंतरभूत पूर्णांक zd_rf_should_update_pwr_पूर्णांक(काष्ठा zd_rf *rf)
अणु
	वापस rf->update_channel_पूर्णांक;
पूर्ण

अटल अंतरभूत पूर्णांक zd_rf_should_patch_cck_gain(काष्ठा zd_rf *rf)
अणु
	वापस rf->patch_cck_gain;
पूर्ण

पूर्णांक zd_rf_patch_6m_band_edge(काष्ठा zd_rf *rf, u8 channel);
पूर्णांक zd_rf_generic_patch_6m(काष्ठा zd_rf *rf, u8 channel);

/* Functions क्रम inभागidual RF chips */

पूर्णांक zd_rf_init_rf2959(काष्ठा zd_rf *rf);
पूर्णांक zd_rf_init_al2230(काष्ठा zd_rf *rf);
पूर्णांक zd_rf_init_al7230b(काष्ठा zd_rf *rf);
पूर्णांक zd_rf_init_uw2453(काष्ठा zd_rf *rf);

#पूर्ण_अगर /* _ZD_RF_H */
