<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LCD_MIPID_H
#घोषणा __LCD_MIPID_H

क्रमागत mipid_test_num अणु
	MIPID_TEST_RGB_LINES,
पूर्ण;

क्रमागत mipid_test_result अणु
	MIPID_TEST_SUCCESS,
	MIPID_TEST_INVALID,
	MIPID_TEST_FAILED,
पूर्ण;

#अगर_घोषित __KERNEL__

काष्ठा mipid_platक्रमm_data अणु
	पूर्णांक	nreset_gpio;
	पूर्णांक	data_lines;

	व्योम	(*shutकरोwn)(काष्ठा mipid_platक्रमm_data *pdata);
	व्योम	(*set_bklight_level)(काष्ठा mipid_platक्रमm_data *pdata,
				     पूर्णांक level);
	पूर्णांक	(*get_bklight_level)(काष्ठा mipid_platक्रमm_data *pdata);
	पूर्णांक	(*get_bklight_max)(काष्ठा mipid_platक्रमm_data *pdata);
पूर्ण;

#पूर्ण_अगर

#पूर्ण_अगर
