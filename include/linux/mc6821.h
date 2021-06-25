<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MC6821_H_
#घोषणा _MC6821_H_

/*
 * This file describes the memery mapping of the MC6821 PIA.
 * The जोड़s describe overlayed रेजिस्टरs. Which of them is used is
 * determined by bit 2 of the corresponding control रेजिस्टर.
 * this files expects the PIA_REG_PADWIDTH to be defined the numeric
 * value of the रेजिस्टर spacing.
 *
 * Data came from MFC-31-Developer Kit (from Ralph Seidel,
 * zodiac@darkness.gun.de) and Motorola Data Sheet (from 
 * Riअक्षरd Hirst, srh@gpt.co.uk)
 *
 * 6.11.95 copyright Joerg Dorchain (करोrchain@mpi-sb.mpg.de)
 *
 */

#अगर_अघोषित PIA_REG_PADWIDTH
#घोषणा PIA_REG_PADWIDTH 255
#पूर्ण_अगर

काष्ठा pia अणु
	जोड़ अणु
		अस्थिर u_अक्षर pra;
		अस्थिर u_अक्षर ddra;
	पूर्ण ua;
	u_अक्षर pad1[PIA_REG_PADWIDTH];
	अस्थिर u_अक्षर cra;
	u_अक्षर pad2[PIA_REG_PADWIDTH];
	जोड़ अणु
		अस्थिर u_अक्षर prb;
		अस्थिर u_अक्षर ddrb;
	पूर्ण ub;
	u_अक्षर pad3[PIA_REG_PADWIDTH];
	अस्थिर u_अक्षर crb;
	u_अक्षर pad4[PIA_REG_PADWIDTH];
पूर्ण;

#घोषणा ppra ua.pra
#घोषणा pddra ua.ddra
#घोषणा pprb ub.prb
#घोषणा pddrb ub.ddrb

#घोषणा PIA_C1_ENABLE_IRQ (1<<0)
#घोषणा PIA_C1_LOW_TO_HIGH (1<<1)
#घोषणा PIA_DDR (1<<2)
#घोषणा PIA_IRQ2 (1<<6)
#घोषणा PIA_IRQ1 (1<<7)

#पूर्ण_अगर
