<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम the "Baboon" custom IC on the PowerBook 190.
 */

#घोषणा BABOON_BASE (0x50F1A000)	/* same as IDE controller base */

#अगर_अघोषित __ASSEMBLY__

काष्ठा baboon अणु
	अक्षर	pad1[208];	/* generic IDE रेजिस्टरs, not used here */
	लघु	mb_control;	/* Control रेजिस्टर:
				 * bit 5 : slot 2 घातer control
				 * bit 6 : slot 1 घातer control
				 */
	अक्षर	pad2[2];
	लघु	mb_status;	/* (0xD4) media bay status रेजिस्टर:
				 *
				 * bit 0: ????
				 * bit 1: IDE पूर्णांकerrupt active?
				 * bit 2: bay status, 0 = full, 1 = empty
				 * bit 3: ????
				 */
	अक्षर	pad3[2];	/* (0xD6) not used */
	लघु	mb_अगरr;		/* (0xD8) media bay पूर्णांकerrupt flags रेजिस्टर:
				 *
				 * bit 0: ????
				 * bit 1: IDE controller पूर्णांकerrupt
				 * bit 2: media bay status change पूर्णांकerrupt
				 */
पूर्ण;

बाह्य पूर्णांक baboon_present;

बाह्य व्योम baboon_रेजिस्टर_पूर्णांकerrupts(व्योम);
बाह्य व्योम baboon_irq_enable(पूर्णांक);
बाह्य व्योम baboon_irq_disable(पूर्णांक);

#पूर्ण_अगर /* __ASSEMBLY **/
