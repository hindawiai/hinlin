<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित CALIB_H
#घोषणा CALIB_H

#समावेश "hw.h"

#घोषणा AR_PHY_CCA_FILTERWINDOW_LENGTH          5

/* Internal noise न्यूनमान can vary by about 6db depending on the frequency */
#घोषणा ATH9K_NF_CAL_NOISE_THRESH		6

#घोषणा NUM_NF_READINGS       6
#घोषणा ATH9K_NF_CAL_HIST_MAX 5

काष्ठा ar5416IniArray अणु
	u32 *ia_array;
	u32 ia_rows;
	u32 ia_columns;
पूर्ण;

#घोषणा STATIC_INI_ARRAY(array) अणु			\
		.ia_array = (u32 *)(array),		\
		.ia_rows = ARRAY_SIZE(array),		\
		.ia_columns = ARRAY_SIZE(array[0]),	\
	पूर्ण

#घोषणा INIT_INI_ARRAY(iniarray, array) करो अणु	\
		(iniarray)->ia_array = (u32 *)(array);		\
		(iniarray)->ia_rows = ARRAY_SIZE(array);	\
		(iniarray)->ia_columns = ARRAY_SIZE(array[0]);	\
	पूर्ण जबतक (0)

#घोषणा INI_RA(iniarray, row, column) \
	(((iniarray)->ia_array)[(row) *	((iniarray)->ia_columns) + (column)])

#घोषणा INIT_CAL(_perCal) करो अणु				\
		(_perCal)->calState = CAL_WAITING;	\
		(_perCal)->calNext = शून्य;		\
	पूर्ण जबतक (0)

#घोषणा INSERT_CAL(_ahp, _perCal)					\
	करो अणु								\
		अगर ((_ahp)->cal_list_last == शून्य) अणु			\
			(_ahp)->cal_list =				\
				(_ahp)->cal_list_last = (_perCal);	\
			((_ahp)->cal_list_last)->calNext = (_perCal); \
		पूर्ण अन्यथा अणु						\
			((_ahp)->cal_list_last)->calNext = (_perCal); \
			(_ahp)->cal_list_last = (_perCal);		\
			(_perCal)->calNext = (_ahp)->cal_list;	\
		पूर्ण							\
	पूर्ण जबतक (0)

क्रमागत ath9k_cal_state अणु
	CAL_INACTIVE,
	CAL_WAITING,
	CAL_RUNNING,
	CAL_DONE
पूर्ण;

#घोषणा MIN_CAL_SAMPLES     1
#घोषणा MAX_CAL_SAMPLES    64
#घोषणा INIT_LOG_COUNT      5
#घोषणा PER_MIN_LOG_COUNT   2
#घोषणा PER_MAX_LOG_COUNT  10

काष्ठा ath9k_percal_data अणु
	u32 calType;
	u32 calNumSamples;
	u32 calCountMax;
	व्योम (*calCollect) (काष्ठा ath_hw *);
	व्योम (*calPostProc) (काष्ठा ath_hw *, u8);
पूर्ण;

काष्ठा ath9k_cal_list अणु
	स्थिर काष्ठा ath9k_percal_data *calData;
	क्रमागत ath9k_cal_state calState;
	काष्ठा ath9k_cal_list *calNext;
पूर्ण;

काष्ठा ath9k_nfcal_hist अणु
	पूर्णांक16_t nfCalBuffer[ATH9K_NF_CAL_HIST_MAX];
	u8 currIndex;
	पूर्णांक16_t privNF;
	u8 invalidNFcount;
पूर्ण;

#घोषणा MAX_PACAL_SKIPCOUNT 8
काष्ठा ath9k_pacal_infoअणु
	पूर्णांक32_t prev_offset;	/* Previous value of PA offset value */
	पूर्णांक8_t max_skipcount;	/* Max No. of बार PACAL can be skipped */
	पूर्णांक8_t skipcount;	/* No. of बार the PACAL to be skipped */
पूर्ण;

bool ath9k_hw_reset_calvalid(काष्ठा ath_hw *ah);
व्योम ath9k_hw_start_nfcal(काष्ठा ath_hw *ah, bool update);
पूर्णांक ath9k_hw_loadnf(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
bool ath9k_hw_getnf(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
व्योम ath9k_init_nfcal_hist_buffer(काष्ठा ath_hw *ah,
				  काष्ठा ath9k_channel *chan);
व्योम ath9k_hw_bstuck_nfcal(काष्ठा ath_hw *ah);
व्योम ath9k_hw_reset_calibration(काष्ठा ath_hw *ah,
				काष्ठा ath9k_cal_list *currCal);
s16 ath9k_hw_अ_लोhan_noise(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			   s16 nf);


#पूर्ण_अगर /* CALIB_H */
