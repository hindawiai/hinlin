<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_LO_H_
#घोषणा B43_LO_H_

/* G-PHY Local Oscillator */

#समावेश "phy_g.h"

काष्ठा b43_wldev;

/* Local Oscillator control value-pair. */
काष्ठा b43_loctl अणु
	/* Control values. */
	s8 i;
	s8 q;
पूर्ण;
/* Debugging: Poison value क्रम i and q values. */
#घोषणा B43_LOCTL_POISON	111

/* This काष्ठा holds calibrated LO settings क्रम a set of
 * Baseband and RF attenuation settings. */
काष्ठा b43_lo_calib अणु
	/* The set of attenuation values this set of LO
	 * control values is calibrated क्रम. */
	काष्ठा b43_bbatt bbatt;
	काष्ठा b43_rfatt rfatt;
	/* The set of control values क्रम the LO. */
	काष्ठा b43_loctl ctl;
	/* The समय when these settings were calibrated (in jअगरfies) */
	अचिन्हित दीर्घ calib_समय;
	/* List. */
	काष्ठा list_head list;
पूर्ण;

/* Size of the DC Lookup Table in 16bit words. */
#घोषणा B43_DC_LT_SIZE		32

/* Local Oscillator calibration inक्रमmation */
काष्ठा b43_txघातer_lo_control अणु
	/* Lists of RF and BB attenuation values क्रम this device.
	 * Used क्रम building hardware घातer control tables. */
	काष्ठा b43_rfatt_list rfatt_list;
	काष्ठा b43_bbatt_list bbatt_list;

	/* The DC Lookup Table is cached in memory here.
	 * Note that this is only used क्रम Hardware Power Control. */
	u16 dc_lt[B43_DC_LT_SIZE];

	/* List of calibrated control values (काष्ठा b43_lo_calib). */
	काष्ठा list_head calib_list;
	/* Last समय the घातer vector was पढ़ो (jअगरfies). */
	अचिन्हित दीर्घ pwr_vec_पढ़ो_समय;
	/* Last समय the txctl values were measured (jअगरfies). */
	अचिन्हित दीर्घ txctl_measured_समय;

	/* Current TX Bias value */
	u8 tx_bias;
	/* Current TX Magnअगरication Value (अगर used by the device) */
	u8 tx_magn;

	/* Saved device PowerVector */
	u64 घातer_vector;
पूर्ण;

/* Calibration expire समयouts.
 * Timeouts must be multiple of 15 seconds. To make sure
 * the item really expired when the 15 second समयr hits, we
 * subtract two additional seconds from the समयout. */
#घोषणा B43_LO_CALIB_EXPIRE	(HZ * (30 - 2))
#घोषणा B43_LO_PWRVEC_EXPIRE	(HZ * (30 - 2))
#घोषणा B43_LO_TXCTL_EXPIRE	(HZ * (180 - 4))


/* Adjust the Local Oscillator to the saved attenuation
 * and txctl values.
 */
व्योम b43_lo_g_adjust(काष्ठा b43_wldev *dev);
/* Adjust to specअगरic values. */
व्योम b43_lo_g_adjust_to(काष्ठा b43_wldev *dev,
			u16 rfatt, u16 bbatt, u16 tx_control);

व्योम b43_gphy_dc_lt_init(काष्ठा b43_wldev *dev, bool update_all);

व्योम b43_lo_g_मुख्यtenance_work(काष्ठा b43_wldev *dev);
व्योम b43_lo_g_cleanup(काष्ठा b43_wldev *dev);
व्योम b43_lo_g_init(काष्ठा b43_wldev *dev);

#पूर्ण_अगर /* B43_LO_H_ */
