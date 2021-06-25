<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NWBUTTON_H
#घोषणा __NWBUTTON_H

/*
 * 	NetWinder Button Driver-
 *	Copyright (C) Alex Holden <alex@linuxhacker.org> 1998, 1999.
 */

#अगर_घोषित __NWBUTTON_C	/* Actually compiling the driver itself */

/* Various defines: */

#घोषणा NUM_PRESSES_REBOOT 2	/* How many presses to activate shutकरोwn */
#घोषणा BUTTON_DELAY 30 	/* How many jअगरfies क्रम sequence to end */
#घोषणा VERSION "0.3"		/* Driver version number */

/* Structure definitions: */

काष्ठा button_callback अणु
	व्योम (*callback) (व्योम);
	पूर्णांक count;
पूर्ण;

/* Function prototypes: */

अटल व्योम button_sequence_finished(काष्ठा समयr_list *unused);
अटल irqवापस_t button_handler (पूर्णांक irq, व्योम *dev_id);
पूर्णांक button_init (व्योम);
पूर्णांक button_add_callback (व्योम (*callback) (व्योम), पूर्णांक count);
पूर्णांक button_del_callback (व्योम (*callback) (व्योम));
अटल व्योम button_consume_callbacks (पूर्णांक bpcount);

#अन्यथा /* Not compiling the driver itself */

बाह्य पूर्णांक button_add_callback (व्योम (*callback) (व्योम), पूर्णांक count);
बाह्य पूर्णांक button_del_callback (व्योम (*callback) (व्योम));

#पूर्ण_अगर /* __NWBUTTON_C */
#पूर्ण_अगर /* __NWBUTTON_H */
