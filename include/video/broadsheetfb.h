<शैली गुरु>
/*
 * broadsheetfb.h - definitions क्रम the broadsheet framebuffer driver
 *
 * Copyright (C) 2008 by Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 */

#अगर_अघोषित _LINUX_BROADSHEETFB_H_
#घोषणा _LINUX_BROADSHEETFB_H_

/* Broadsheet command defines */
#घोषणा BS_CMD_INIT_SYS_RUN	0x06
#घोषणा BS_CMD_INIT_DSPE_CFG	0x09
#घोषणा BS_CMD_INIT_DSPE_TMG	0x0A
#घोषणा BS_CMD_INIT_ROTMODE	0x0B
#घोषणा BS_CMD_RD_REG		0x10
#घोषणा BS_CMD_WR_REG		0x11
#घोषणा BS_CMD_LD_IMG		0x20
#घोषणा BS_CMD_LD_IMG_AREA	0x22
#घोषणा BS_CMD_LD_IMG_END	0x23
#घोषणा BS_CMD_WAIT_DSPE_TRG	0x28
#घोषणा BS_CMD_WAIT_DSPE_FREND	0x29
#घोषणा BS_CMD_RD_WFM_INFO	0x30
#घोषणा BS_CMD_UPD_INIT		0x32
#घोषणा BS_CMD_UPD_FULL		0x33
#घोषणा BS_CMD_UPD_GDRV_CLR	0x37

/* Broadsheet रेजिस्टर पूर्णांकerface defines */
#घोषणा BS_REG_REV		0x00
#घोषणा BS_REG_PRC		0x02

/* Broadsheet pin पूर्णांकerface specअगरic defines */
#घोषणा BS_CS	0x01
#घोषणा BS_DC 	0x02
#घोषणा BS_WR 	0x03

/* Broadsheet IO पूर्णांकerface specअगरic defines */
#घोषणा BS_MMIO_CMD	0x01
#घोषणा BS_MMIO_DATA	0x02

/* काष्ठा used by broadsheet. board specअगरic stuff comes from *board */
काष्ठा broadsheetfb_par अणु
	काष्ठा fb_info *info;
	काष्ठा broadsheet_board *board;
	व्योम (*ग_लिखो_reg)(काष्ठा broadsheetfb_par *, u16 reg, u16 val);
	u16 (*पढ़ो_reg)(काष्ठा broadsheetfb_par *, u16 reg);
	रुको_queue_head_t रुकोq;
	पूर्णांक panel_index;
	काष्ठा mutex io_lock;
पूर्ण;

/* board specअगरic routines */
काष्ठा broadsheet_board अणु
	काष्ठा module *owner;
	पूर्णांक (*init)(काष्ठा broadsheetfb_par *);
	पूर्णांक (*रुको_क्रम_rdy)(काष्ठा broadsheetfb_par *);
	व्योम (*cleanup)(काष्ठा broadsheetfb_par *);
	पूर्णांक (*get_panel_type)(व्योम);
	पूर्णांक (*setup_irq)(काष्ठा fb_info *);

	/* Functions क्रम boards that use GPIO */
	व्योम (*set_ctl)(काष्ठा broadsheetfb_par *, अचिन्हित अक्षर, u8);
	व्योम (*set_hdb)(काष्ठा broadsheetfb_par *, u16);
	u16 (*get_hdb)(काष्ठा broadsheetfb_par *);

	/* Functions क्रम boards that have specialized MMIO */
	व्योम (*mmio_ग_लिखो)(काष्ठा broadsheetfb_par *, पूर्णांक type, u16);
	u16 (*mmio_पढ़ो)(काष्ठा broadsheetfb_par *);
पूर्ण;
#पूर्ण_अगर
