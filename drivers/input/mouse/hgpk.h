<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OLPC HGPK (XO-1) touchpad PS/2 mouse driver
 */

#अगर_अघोषित _HGPK_H
#घोषणा _HGPK_H

#घोषणा HGPK_GS		0xff       /* The GlideSensor */
#घोषणा HGPK_PT		0xcf       /* The PenTablet */

क्रमागत hgpk_model_t अणु
	HGPK_MODEL_PREA = 0x0a,	/* pre-B1s */
	HGPK_MODEL_A = 0x14,	/* found on B1s, PT disabled in hardware */
	HGPK_MODEL_B = 0x28,	/* B2s, has capacitance issues */
	HGPK_MODEL_C = 0x3c,
	HGPK_MODEL_D = 0x50,	/* C1, mass production */
पूर्ण;

क्रमागत hgpk_spew_flag अणु
	NO_SPEW,
	MAYBE_SPEWING,
	SPEW_DETECTED,
	RECALIBRATING,
पूर्ण;

#घोषणा SPEW_WATCH_COUNT 42  /* at 12ms/packet, this is 1/2 second */

क्रमागत hgpk_mode अणु
	HGPK_MODE_MOUSE,
	HGPK_MODE_GLIDESENSOR,
	HGPK_MODE_PENTABLET,
	HGPK_MODE_INVALID
पूर्ण;

काष्ठा hgpk_data अणु
	काष्ठा psmouse *psmouse;
	क्रमागत hgpk_mode mode;
	bool घातered;
	क्रमागत hgpk_spew_flag spew_flag;
	पूर्णांक spew_count, x_tally, y_tally;	/* spew detection */
	अचिन्हित दीर्घ recalib_winकरोw;
	काष्ठा delayed_work recalib_wq;
	पूर्णांक असल_x, असल_y;
	पूर्णांक dupe_count;
	पूर्णांक xbigj, ybigj, xlast, ylast; /* jumpiness detection */
	पूर्णांक xsaw_secondary, ysaw_secondary; /* jumpiness detection */
पूर्ण;

पूर्णांक hgpk_detect(काष्ठा psmouse *psmouse, bool set_properties);
पूर्णांक hgpk_init(काष्ठा psmouse *psmouse);

#अगर_घोषित CONFIG_MOUSE_PS2_OLPC
व्योम hgpk_module_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम hgpk_module_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
