<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * valkyriefb.h: Constants of all sorts क्रम valkyriefb
 *
 *  Created 8 August 1998 by 
 *  Martin Costabel <costabel@wanaकरोo.fr> and Kevin Schoedel
 *
 * Vmode-चयनing changes and vmode 15/17 modअगरications created 29 August
 * 1998 by Barry K. Nathan <barryn@pobox.com>.
 * 
 * vmode 10 changed by Steven Borley <sjb@salix.demon.co.uk>, 14 mai 2000
 *
 * Ported to 68k Macपूर्णांकosh by David Huggins-Daines <dhd@debian.org>
 *
 * Based directly on:
 *
 *  controlfb.h: Constants of all sorts क्रम controlfb
 *  Copyright (C) 1998 Daniel Jacobowitz <dan@debian.org>
 *
 *  pmc-valkyrie.h: Console support क्रम PowerMac "control" display adaptor.
 *  Copyright (C) 1997 Paul Mackerras.
 *
 *  pmc-valkyrie.c: Console support क्रम PowerMac "control" display adaptor.
 *  Copyright (C) 1997 Paul Mackerras.
 *
 * and indirectly from:
 *
 *  pmc-control.h: Console support क्रम PowerMac "control" display adaptor.
 *  Copyright (C) 1997 Paul Mackerras.
 *
 *  pmc-control.c: Console support क्रम PowerMac "control" display adaptor.
 *  Copyright (C) 1996 Paul Mackerras.
 *
 *  platinumfb.c: Console support क्रम PowerMac "platinum" display adaptor.
 *  Copyright (C) 1998 Jon Howell
 */

#अगर_घोषित CONFIG_MAC
/* Valkyrie रेजिस्टरs are word-aligned on m68k */
#घोषणा VALKYRIE_REG_PADSIZE	3
#अन्यथा
#घोषणा VALKYRIE_REG_PADSIZE	7
#पूर्ण_अगर

/*
 * Structure of the रेजिस्टरs क्रम the Valkyrie colormap रेजिस्टरs.
 */
काष्ठा cmap_regs अणु
	अचिन्हित अक्षर addr;
	अक्षर pad1[VALKYRIE_REG_PADSIZE];
	अचिन्हित अक्षर lut;
पूर्ण;

/*
 * Structure of the रेजिस्टरs क्रम the "valkyrie" display adaptor.
 */

काष्ठा vpreg अणु			/* padded रेजिस्टर */
	अचिन्हित अक्षर r;
	अक्षर pad[VALKYRIE_REG_PADSIZE];
पूर्ण;


काष्ठा valkyrie_regs अणु
	काष्ठा vpreg mode;
	काष्ठा vpreg depth;
	काष्ठा vpreg status;
	काष्ठा vpreg reg3;
	काष्ठा vpreg पूर्णांकr;
	काष्ठा vpreg reg5;
	काष्ठा vpreg पूर्णांकr_enb;
	काष्ठा vpreg msense;
पूर्ण;

/*
 * Register initialization tables क्रम the valkyrie display.
 *
 * Dot घड़ी rate is
 * 3.9064MHz * 2**घड़ी_params[2] * घड़ी_params[1] / घड़ी_params[0].
 */
काष्ठा valkyrie_regvals अणु
	अचिन्हित अक्षर mode;
	अचिन्हित अक्षर घड़ी_params[3];
	पूर्णांक	pitch[2];		/* bytes/line, indexed by color_mode */
	पूर्णांक	hres;
	पूर्णांक	vres;
पूर्ण;

#अगर_अघोषित CONFIG_MAC
/* Register values क्रम 1024x768, 75Hz mode (17) */
/* I'm not sure which mode this is (16 or 17), so I'm defining it as 17,
 * since the equivalent mode in controlfb (which I adapted this from) is
 * also 17. Just because MacOS can't do this on Valkyrie doesn't mean we
 * can't! :)
 *
 * I was going to use 12, 31, 3, which I found by myself, but instead I'm
 * using 11, 28, 3 like controlfb, क्रम consistency's sake.
 */

अटल काष्ठा valkyrie_regvals valkyrie_reg_init_17 = अणु
    15, 
    अणु 11, 28, 3 पूर्ण,  /* pixel घड़ी = 79.55MHz क्रम V=74.50Hz */
    अणु 1024, 0 पूर्ण,
	1024, 768
पूर्ण;

/* Register values क्रम 1024x768, 72Hz mode (15) */
/* This used to be 12, 30, 3 क्रम pixel घड़ी = 78.12MHz क्रम V=72.12Hz, but
 * that didn't match MacOS in the same video mode on this chip, and it also
 * caused the 15" Apple Studio Display to not work in this mode. While this
 * mode still करोesn't match MacOS exactly (as far as I can tell), it's a lot
 * बंदr now, and it works with the Apple Studio Display.
 *
 * Yes, even though MacOS calls it "72Hz", in reality it's about 70Hz.
 */
अटल काष्ठा valkyrie_regvals valkyrie_reg_init_15 = अणु
    15,
    अणु 12, 29, 3 पूर्ण,  /* pixel घड़ी = 75.52MHz क्रम V=69.71Hz? */
		    /* I पूर्णांकerpolated the V=69.71 from the vmode 14 and old 15
		     * numbers. Is this result correct?
		     */
    अणु 1024, 0 पूर्ण,
	1024, 768
पूर्ण;

/* Register values क्रम 1024x768, 60Hz mode (14) */
अटल काष्ठा valkyrie_regvals valkyrie_reg_init_14 = अणु
    14,
    अणु 15, 31, 3 पूर्ण,  /* pixel घड़ी = 64.58MHz क्रम V=59.62Hz */
    अणु 1024, 0 पूर्ण,
	1024, 768
पूर्ण;
#पूर्ण_अगर /* !defined CONFIG_MAC */

/* Register values क्रम 832x624, 75Hz mode (13) */
अटल काष्ठा valkyrie_regvals valkyrie_reg_init_13 = अणु
    9,
    अणु 23, 42, 3 पूर्ण,  /* pixel घड़ी = 57.07MHz क्रम V=74.27Hz */
    अणु 832, 0 पूर्ण,
	832, 624
पूर्ण;

/* Register values क्रम 800x600, 72Hz mode (11) */
अटल काष्ठा valkyrie_regvals valkyrie_reg_init_11 = अणु
    13,
    अणु 17, 27, 3 पूर्ण,  /* pixel घड़ी = 49.63MHz क्रम V=71.66Hz */
    अणु 800, 0 पूर्ण,
	800, 600
पूर्ण;

/* Register values क्रम 800x600, 60Hz mode (10) */
अटल काष्ठा valkyrie_regvals valkyrie_reg_init_10 = अणु
    12,
    अणु 25, 32, 3 पूर्ण,  /* pixel घड़ी = 40.0015MHz,
                     used to be 20,53,2, pixel घड़ी 41.41MHz क्रम V=59.78Hz */
    अणु 800, 1600 पूर्ण,
	800, 600
पूर्ण;

/* Register values क्रम 640x480, 67Hz mode (6) */
अटल काष्ठा valkyrie_regvals valkyrie_reg_init_6 = अणु
    6,
    अणु 14, 27, 2 पूर्ण,  /* pixel घड़ी = 30.13MHz क्रम V=66.43Hz */
    अणु 640, 1280 पूर्ण,
	640, 480
पूर्ण;

/* Register values क्रम 640x480, 60Hz mode (5) */
अटल काष्ठा valkyrie_regvals valkyrie_reg_init_5 = अणु
    11,
    अणु 23, 37, 2 पूर्ण,  /* pixel घड़ी = 25.14MHz क्रम V=59.85Hz */
    अणु 640, 1280 पूर्ण,
	640, 480
पूर्ण;

अटल काष्ठा valkyrie_regvals *valkyrie_reg_init[VMODE_MAX] = अणु
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	&valkyrie_reg_init_5,
	&valkyrie_reg_init_6,
	शून्य,
	शून्य,
	शून्य,
	&valkyrie_reg_init_10,
	&valkyrie_reg_init_11,
	शून्य,
	&valkyrie_reg_init_13,
#अगर_अघोषित CONFIG_MAC
	&valkyrie_reg_init_14,
	&valkyrie_reg_init_15,
	शून्य,
	&valkyrie_reg_init_17,
#पूर्ण_अगर
पूर्ण;
