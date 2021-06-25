<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CONSOLE_CMDLINE_H
#घोषणा _CONSOLE_CMDLINE_H

काष्ठा console_cmdline
अणु
	अक्षर	name[16];			/* Name of the driver	    */
	पूर्णांक	index;				/* Minor dev. to use	    */
	bool	user_specअगरied;			/* Specअगरied by command line vs. platक्रमm */
	अक्षर	*options;			/* Options क्रम the driver   */
#अगर_घोषित CONFIG_A11Y_BRAILLE_CONSOLE
	अक्षर	*brl_options;			/* Options क्रम braille driver */
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
