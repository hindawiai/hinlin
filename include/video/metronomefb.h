<शैली गुरु>
/*
 * metronomefb.h - definitions क्रम the metronome framebuffer driver
 *
 * Copyright (C) 2008 by Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 */

#अगर_अघोषित _LINUX_METRONOMEFB_H_
#घोषणा _LINUX_METRONOMEFB_H_

/* command काष्ठाure used by metronome controller */
काष्ठा metromem_cmd अणु
	u16 opcode;
	u16 args[((64-2)/2)];
	u16 csum;
पूर्ण;

/* काष्ठा used by metronome. board specअगरic stuff comes from *board */
काष्ठा metronomefb_par अणु
	काष्ठा metromem_cmd *metromem_cmd;
	अचिन्हित अक्षर *metromem_wfm;
	अचिन्हित अक्षर *metromem_img;
	u16 *metromem_img_csum;
	u16 *csum_table;
	dma_addr_t metromem_dma;
	काष्ठा fb_info *info;
	काष्ठा metronome_board *board;
	रुको_queue_head_t रुकोq;
	u8 frame_count;
	पूर्णांक extra_size;
	पूर्णांक dt;
पूर्ण;

/* board specअगरic routines and data */
काष्ठा metronome_board अणु
	काष्ठा module *owner; /* the platक्रमm device */
	व्योम (*set_rst)(काष्ठा metronomefb_par *, पूर्णांक);
	व्योम (*set_stdby)(काष्ठा metronomefb_par *, पूर्णांक);
	व्योम (*cleanup)(काष्ठा metronomefb_par *);
	पूर्णांक (*met_रुको_event)(काष्ठा metronomefb_par *);
	पूर्णांक (*met_रुको_event_पूर्णांकr)(काष्ठा metronomefb_par *);
	पूर्णांक (*setup_irq)(काष्ठा fb_info *);
	पूर्णांक (*setup_fb)(काष्ठा metronomefb_par *);
	पूर्णांक (*setup_io)(काष्ठा metronomefb_par *);
	पूर्णांक (*get_panel_type)(व्योम);
	अचिन्हित अक्षर *metromem;
	पूर्णांक fw;
	पूर्णांक fh;
	पूर्णांक wfm_size;
	काष्ठा fb_info *host_fbinfo; /* the host LCD controller's fbi */
पूर्ण;

#पूर्ण_अगर
