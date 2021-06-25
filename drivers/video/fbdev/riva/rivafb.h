<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RIVAFB_H
#घोषणा __RIVAFB_H

#समावेश <linux/fb.h>
#समावेश <video/vga.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

#समावेश "riva_hw.h"

/* GGI compatibility macros */
#घोषणा NUM_SEQ_REGS		0x05
#घोषणा NUM_CRT_REGS		0x41
#घोषणा NUM_GRC_REGS		0x09
#घोषणा NUM_ATC_REGS		0x15

/* I2C */
#घोषणा DDC_SCL_READ_MASK       (1 << 2)
#घोषणा DDC_SCL_WRITE_MASK      (1 << 5)
#घोषणा DDC_SDA_READ_MASK       (1 << 3)
#घोषणा DDC_SDA_WRITE_MASK      (1 << 4)

/* holds the state of the VGA core and extended Riva hw state from riva_hw.c.
 * From KGI originally. */
काष्ठा riva_regs अणु
	u8 attr[NUM_ATC_REGS];
	u8 crtc[NUM_CRT_REGS];
	u8 gra[NUM_GRC_REGS];
	u8 seq[NUM_SEQ_REGS];
	u8 misc_output;
	RIVA_HW_STATE ext;
पूर्ण;

काष्ठा riva_par;

काष्ठा riva_i2c_chan अणु
	काष्ठा riva_par *par;
	अचिन्हित दीर्घ   ddc_base;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
पूर्ण;

काष्ठा riva_par अणु
	RIVA_HW_INST riva;	/* पूर्णांकerface to riva_hw.c */
	u32 pseuकरो_palette[16]; /* शेष palette */
	u32 palette[16];        /* क्रम Riva128 */
	u8 __iomem *ctrl_base;	/* भव control रेजिस्टर base addr */
	अचिन्हित dclk_max;	/* max DCLK */

	काष्ठा riva_regs initial_state;	/* initial startup video mode */
	काष्ठा riva_regs current_state;
#अगर_घोषित CONFIG_X86
	काष्ठा vgastate state;
#पूर्ण_अगर
	काष्ठा mutex खोलो_lock;
	अचिन्हित पूर्णांक ref_count;
	अचिन्हित अक्षर *EDID;
	अचिन्हित पूर्णांक Chipset;
	पूर्णांक क्रमceCRTC;
	Bool SecondCRTC;
	पूर्णांक FlatPanel;
	काष्ठा pci_dev *pdev;
	पूर्णांक cursor_reset;
	पूर्णांक wc_cookie;
	काष्ठा riva_i2c_chan chan[3];
पूर्ण;

व्योम riva_common_setup(काष्ठा riva_par *);
अचिन्हित दीर्घ riva_get_memlen(काष्ठा riva_par *);
अचिन्हित दीर्घ riva_get_maxdclk(काष्ठा riva_par *);
व्योम riva_delete_i2c_busses(काष्ठा riva_par *par);
व्योम riva_create_i2c_busses(काष्ठा riva_par *par);
पूर्णांक riva_probe_i2c_connector(काष्ठा riva_par *par, पूर्णांक conn, u8 **out_edid);

#पूर्ण_अगर /* __RIVAFB_H */
