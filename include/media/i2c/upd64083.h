<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * upd6408x - NEC Electronics 3-Dimensional Y/C separation input defines
 *
 * 2006 by Hans Verkuil (hverkuil@xs4all.nl)
 */

#अगर_अघोषित _UPD64083_H_
#घोषणा _UPD64083_H_

/* There are two bits of inक्रमmation that the driver needs in order
   to select the correct routing: the operating mode and the selection
   of the Y input (बाह्यal or पूर्णांकernal).

   The first two operating modes expect a composite संकेत on the Y input,
   the second two operating modes use both the Y and C inमाला_दो.

   Normally YCS_MODE is used क्रम tuner and composite inमाला_दो, and the
   YCNR mode is used क्रम S-Video inमाला_दो.

   The बाह्यal Y-ADC is selected when the composite input comes from a
   upd64031a ghost reduction device. If this device is not present, or
   the input is a S-Video संकेत, then the पूर्णांकernal Y-ADC input should
   be used. */

/* Operating modes: */

/* YCS mode: Y/C separation (burst locked घड़ीing) */
#घोषणा UPD64083_YCS_MODE      0
/* YCS+ mode: 2D Y/C separation and YCNR (burst locked घड़ीing) */
#घोषणा UPD64083_YCS_PLUS_MODE 1

/* Note: the following two modes cannot be used in combination with the
   बाह्यal Y-ADC. */
/* MNNR mode: frame comb type YNR+C delay (line locked घड़ीing) */
#घोषणा UPD64083_MNNR_MODE     2
/* YCNR mode: frame recursive YCNR (burst locked घड़ीing) */
#घोषणा UPD64083_YCNR_MODE     3

/* Select बाह्यal Y-ADC: this should be set अगर this device is used in
   combination with the upd64031a ghost reduction device.
   Otherwise leave at 0 (use पूर्णांकernal Y-ADC). */
#घोषणा UPD64083_EXT_Y_ADC     (1 << 2)

#पूर्ण_अगर
