<शैली गुरु>
/*
 * hecubafb.h - definitions क्रम the hecuba framebuffer driver
 *
 * Copyright (C) 2008 by Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 */

#अगर_अघोषित _LINUX_HECUBAFB_H_
#घोषणा _LINUX_HECUBAFB_H_

/* Apollo controller specअगरic defines */
#घोषणा APOLLO_START_NEW_IMG	0xA0
#घोषणा APOLLO_STOP_IMG_DATA	0xA1
#घोषणा APOLLO_DISPLAY_IMG	0xA2
#घोषणा APOLLO_ERASE_DISPLAY	0xA3
#घोषणा APOLLO_INIT_DISPLAY	0xA4

/* Hecuba पूर्णांकerface specअगरic defines */
#घोषणा HCB_WUP_BIT	0x01
#घोषणा HCB_DS_BIT 	0x02
#घोषणा HCB_RW_BIT 	0x04
#घोषणा HCB_CD_BIT 	0x08
#घोषणा HCB_ACK_BIT 	0x80

/* काष्ठा used by hecuba. board specअगरic stuff comes from *board */
काष्ठा hecubafb_par अणु
	काष्ठा fb_info *info;
	काष्ठा hecuba_board *board;
	व्योम (*send_command)(काष्ठा hecubafb_par *, अचिन्हित अक्षर);
	व्योम (*send_data)(काष्ठा hecubafb_par *, अचिन्हित अक्षर);
पूर्ण;

/* board specअगरic routines
board drivers can implement रुको_क्रम_ack with पूर्णांकerrupts अगर desired. अगर
रुको_क्रम_ack is called with clear=0, then go to sleep and वापस when ack
goes hi or अगर रुको_क्रम_ack with clear=1, then वापस when ack goes lo */
काष्ठा hecuba_board अणु
	काष्ठा module *owner;
	व्योम (*हटाओ)(काष्ठा hecubafb_par *);
	व्योम (*set_ctl)(काष्ठा hecubafb_par *, अचिन्हित अक्षर, अचिन्हित अक्षर);
	व्योम (*set_data)(काष्ठा hecubafb_par *, अचिन्हित अक्षर);
	व्योम (*रुको_क्रम_ack)(काष्ठा hecubafb_par *, पूर्णांक);
	पूर्णांक (*init)(काष्ठा hecubafb_par *);
पूर्ण;


#पूर्ण_अगर
