<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SH_KEYSC_H__
#घोषणा __SH_KEYSC_H__

#घोषणा SH_KEYSC_MAXKEYS 64

काष्ठा sh_keysc_info अणु
	क्रमागत अणु SH_KEYSC_MODE_1, SH_KEYSC_MODE_2, SH_KEYSC_MODE_3,
	       SH_KEYSC_MODE_4, SH_KEYSC_MODE_5, SH_KEYSC_MODE_6 पूर्ण mode;
	पूर्णांक scan_timing; /* 0 -> 7, see KYCR1, SCN[2:0] */
	पूर्णांक delay;
	पूर्णांक kycr2_delay;
	पूर्णांक keycodes[SH_KEYSC_MAXKEYS]; /* KEYIN * KEYOUT */
पूर्ण;

#पूर्ण_अगर /* __SH_KEYSC_H__ */
