<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * device_id.h -- PCMCIA driver matching helpers
 *
 * (C) 2003 - 2004	David Woodhouse
 * (C) 2003 - 2004	Dominik Broकरोwski
 */

#अगर_अघोषित _LINUX_PCMCIA_DEVICE_ID_H
#घोषणा _LINUX_PCMCIA_DEVICE_ID_H

#अगर_घोषित __KERNEL__

#घोषणा PCMCIA_DEVICE_MANF_CARD(manf, card) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID, \
	.manf_id = (manf), \
	.card_id = (card), पूर्ण

#घोषणा PCMCIA_DEVICE_FUNC_ID(func) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_FUNC_ID, \
	.func_id = (func), पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID1(v1, vh1) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1, \
	.prod_id = अणु (v1), शून्य, शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, 0, 0 पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID2(v2, vh2) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID2, \
	.prod_id = अणु शून्य, (v2), शून्य, शून्य पूर्ण,  \
	.prod_id_hash = अणु 0, (vh2), 0, 0 पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID3(v3, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID3, \
	.prod_id = अणु शून्य, शून्य, (v3), शून्य पूर्ण,  \
	.prod_id_hash = अणु 0, 0, (vh3), 0 पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID12(v1, v2, vh1, vh2) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2, \
	.prod_id = अणु (v1), (v2), शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, 0 पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID13(v1, v3, vh1, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3, \
	.prod_id = अणु (v1), शून्य, (v3), शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, (vh3), 0 पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID14(v1, v4, vh1, vh4) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID4, \
	.prod_id = अणु (v1), शून्य, शून्य, (v4) पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, 0, (vh4) पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID123(v1, v2, v3, vh1, vh2, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3, \
	.prod_id = अणु (v1), (v2), (v3), शून्य पूर्ण,\
	.prod_id_hash = अणु (vh1), (vh2), (vh3), 0 पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID124(v1, v2, v4, vh1, vh2, vh4) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_PROD_ID4, \
	.prod_id = अणु (v1), (v2), शून्य, (v4) पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, (vh4) पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID134(v1, v3, v4, vh1, vh3, vh4) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3| \
			PCMCIA_DEV_ID_MATCH_PROD_ID4, \
	.prod_id = अणु (v1), शून्य, (v3), (v4) पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, (vh3), (vh4) पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID1234(v1, v2, v3, v4, vh1, vh2, vh3, vh4) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3| \
			PCMCIA_DEV_ID_MATCH_PROD_ID4, \
	.prod_id = अणु (v1), (v2), (v3), (v4) पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), (vh3), (vh4) पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_MANF_CARD_PROD_ID1(manf, card, v1, vh1) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID| \
			PCMCIA_DEV_ID_MATCH_PROD_ID1, \
	.manf_id = (manf), \
	.card_id = (card), \
	.prod_id = अणु (v1), शून्य, शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, 0, 0 पूर्ण, पूर्ण

#घोषणा PCMCIA_DEVICE_MANF_CARD_PROD_ID3(manf, card, v3, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3, \
	.manf_id = (manf), \
	.card_id = (card), \
	.prod_id = अणु शून्य, शून्य, (v3), शून्य पूर्ण, \
	.prod_id_hash = अणु 0, 0, (vh3), 0 पूर्ण, पूर्ण


/* multi-function devices */

#घोषणा PCMCIA_MFC_DEVICE_MANF_CARD(mfc, manf, card) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.manf_id = (manf), \
	.card_id = (card), \
	.function = (mfc), पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_PROD_ID1(mfc, v1, vh1) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.prod_id = अणु (v1), शून्य, शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, 0, 0 पूर्ण, \
	.function = (mfc), पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_PROD_ID2(mfc, v2, vh2) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.prod_id = अणु शून्य, (v2), शून्य, शून्य पूर्ण,  \
	.prod_id_hash = अणु 0, (vh2), 0, 0 पूर्ण, \
	.function = (mfc), पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_PROD_ID12(mfc, v1, v2, vh1, vh2) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.prod_id = अणु (v1), (v2), शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, 0 पूर्ण, \
	.function = (mfc), पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_PROD_ID13(mfc, v1, v3, vh1, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.prod_id = अणु (v1), शून्य, (v3), शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, (vh3), 0 पूर्ण, \
	.function = (mfc), पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_PROD_ID123(mfc, v1, v2, v3, vh1, vh2, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.prod_id = अणु (v1), (v2), (v3), शून्य पूर्ण,\
	.prod_id_hash = अणु (vh1), (vh2), (vh3), 0 पूर्ण, \
	.function = (mfc), पूर्ण

/* pseuकरो multi-function devices */

#घोषणा PCMCIA_PFC_DEVICE_MANF_CARD(mfc, manf, card) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID| \
			PCMCIA_DEV_ID_MATCH_DEVICE_NO, \
	.manf_id = (manf), \
	.card_id = (card), \
	.device_no = (mfc), पूर्ण

#घोषणा PCMCIA_PFC_DEVICE_PROD_ID1(mfc, v1, vh1) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_DEVICE_NO, \
	.prod_id = अणु (v1), शून्य, शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, 0, 0 पूर्ण, \
	.device_no = (mfc), पूर्ण

#घोषणा PCMCIA_PFC_DEVICE_PROD_ID2(mfc, v2, vh2) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_DEVICE_NO, \
	.prod_id = अणु शून्य, (v2), शून्य, शून्य पूर्ण,  \
	.prod_id_hash = अणु 0, (vh2), 0, 0 पूर्ण, \
	.device_no = (mfc), पूर्ण

#घोषणा PCMCIA_PFC_DEVICE_PROD_ID12(mfc, v1, v2, vh1, vh2) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_DEVICE_NO, \
	.prod_id = अणु (v1), (v2), शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, 0 पूर्ण, \
	.device_no = (mfc), पूर्ण

#घोषणा PCMCIA_PFC_DEVICE_PROD_ID13(mfc, v1, v3, vh1, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3| \
			PCMCIA_DEV_ID_MATCH_DEVICE_NO, \
	.prod_id = अणु (v1), शून्य, (v3), शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), 0, (vh3), 0 पूर्ण, \
	.device_no = (mfc), पूर्ण

#घोषणा PCMCIA_PFC_DEVICE_PROD_ID123(mfc, v1, v2, v3, vh1, vh2, vh3) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3| \
			PCMCIA_DEV_ID_MATCH_DEVICE_NO, \
	.prod_id = अणु (v1), (v2), (v3), शून्य पूर्ण,\
	.prod_id_hash = अणु (vh1), (vh2), (vh3), 0 पूर्ण, \
	.device_no = (mfc), पूर्ण

/* cards needing a CIS override */

#घोषणा PCMCIA_DEVICE_CIS_MANF_CARD(manf, card, _cisfile) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID, \
	.manf_id = (manf), \
	.card_id = (card), \
	.cisfile = (_cisfile)पूर्ण

#घोषणा PCMCIA_DEVICE_CIS_PROD_ID12(v1, v2, vh1, vh2, _cisfile) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2, \
	.prod_id = अणु (v1), (v2), शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, 0 पूर्ण, \
	.cisfile = (_cisfile)पूर्ण

#घोषणा PCMCIA_DEVICE_CIS_PROD_ID123(v1, v2, v3, vh1, vh2, vh3, _cisfile) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_PROD_ID3, \
	.prod_id = अणु (v1), (v2), (v3), शून्य पूर्ण,\
	.prod_id_hash = अणु (vh1), (vh2), (vh3), 0 पूर्ण, \
	.cisfile = (_cisfile)पूर्ण


#घोषणा PCMCIA_DEVICE_CIS_PROD_ID2(v2, vh2, _cisfile) अणु \
	.match_flags =  PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_PROD_ID2, \
	.prod_id = अणु शून्य, (v2), शून्य, शून्य पूर्ण,  \
	.prod_id_hash = अणु 0, (vh2), 0, 0 पूर्ण, \
	.cisfile = (_cisfile)पूर्ण

#घोषणा PCMCIA_PFC_DEVICE_CIS_PROD_ID12(mfc, v1, v2, vh1, vh2, _cisfile) अणु \
	.match_flags =  PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_DEVICE_NO, \
	.prod_id = अणु (v1), (v2), शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, 0 पूर्ण,\
	.device_no = (mfc), \
	.cisfile = (_cisfile)पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_CIS_MANF_CARD(mfc, manf, card, _cisfile) अणु \
	.match_flags =  PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.manf_id = (manf), \
	.card_id = (card), \
	.function = (mfc), \
	.cisfile = (_cisfile)पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_CIS_PROD_ID12(mfc, v1, v2, vh1, vh2, _cisfile) अणु \
	.match_flags =  PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.prod_id = अणु (v1), (v2), शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, 0 पूर्ण, \
	.function = (mfc), \
	.cisfile = (_cisfile)पूर्ण

#घोषणा PCMCIA_MFC_DEVICE_CIS_PROD_ID4(mfc, v4, vh4, _cisfile) अणु \
	.match_flags =  PCMCIA_DEV_ID_MATCH_FAKE_CIS | \
			PCMCIA_DEV_ID_MATCH_PROD_ID4| \
			PCMCIA_DEV_ID_MATCH_FUNCTION, \
	.prod_id = अणु शून्य, शून्य, शून्य, (v4) पूर्ण, \
	.prod_id_hash = अणु 0, 0, 0, (vh4) पूर्ण, \
	.function = (mfc), \
	.cisfile = (_cisfile)पूर्ण


#घोषणा PCMCIA_DEVICE_शून्य अणु .match_flags = 0, पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _LINUX_PCMCIA_DEVICE_ID_H */
