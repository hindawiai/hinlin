<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित OLPC_DCON_H_
#घोषणा OLPC_DCON_H_

#समावेश <linux/notअगरier.h>
#समावेश <linux/workqueue.h>

/* DCON रेजिस्टरs */

#घोषणा DCON_REG_ID		 0
#घोषणा DCON_REG_MODE		 1

#घोषणा MODE_PASSTHRU	BIT(0)
#घोषणा MODE_SLEEP	BIT(1)
#घोषणा MODE_SLEEP_AUTO	BIT(2)
#घोषणा MODE_BL_ENABLE	BIT(3)
#घोषणा MODE_BLANK	BIT(4)
#घोषणा MODE_CSWIZZLE	BIT(5)
#घोषणा MODE_COL_AA	BIT(6)
#घोषणा MODE_MONO_LUMA	BIT(7)
#घोषणा MODE_SCAN_INT	BIT(8)
#घोषणा MODE_CLOCKDIV	BIT(9)
#घोषणा MODE_DEBUG	BIT(14)
#घोषणा MODE_SELFTEST	BIT(15)

#घोषणा DCON_REG_HRES		0x2
#घोषणा DCON_REG_HTOTAL		0x3
#घोषणा DCON_REG_HSYNC_WIDTH	0x4
#घोषणा DCON_REG_VRES		0x5
#घोषणा DCON_REG_VTOTAL		0x6
#घोषणा DCON_REG_VSYNC_WIDTH	0x7
#घोषणा DCON_REG_TIMEOUT	0x8
#घोषणा DCON_REG_SCAN_INT	0x9
#घोषणा DCON_REG_BRIGHT		0xa
#घोषणा DCON_REG_MEM_OPT_A	0x41
#घोषणा DCON_REG_MEM_OPT_B	0x42

/* Load Delay Locked Loop (DLL) settings क्रम घड़ी delay */
#घोषणा MEM_DLL_CLOCK_DELAY	BIT(0)
/* Memory controller घातer करोwn function */
#घोषणा MEM_POWER_DOWN		BIT(8)
/* Memory controller software reset */
#घोषणा MEM_SOFT_RESET		BIT(0)

/* Status values */

#घोषणा DCONSTAT_SCANINT	0
#घोषणा DCONSTAT_SCANINT_DCON	1
#घोषणा DCONSTAT_DISPLAYLOAD	2
#घोषणा DCONSTAT_MISSED		3

/* Source values */

#घोषणा DCON_SOURCE_DCON        0
#घोषणा DCON_SOURCE_CPU         1

/* Interrupt */
#घोषणा DCON_IRQ                6

काष्ठा dcon_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा fb_info *fbinfo;
	काष्ठा backlight_device *bl_dev;

	रुको_queue_head_t रुकोq;
	काष्ठा work_काष्ठा चयन_source;
	काष्ठा notअगरier_block reboot_nb;

	/* Shaकरोw रेजिस्टर क्रम the DCON_REG_MODE रेजिस्टर */
	u8 disp_mode;

	/* The current backlight value - this saves us some smbus traffic */
	u8 bl_val;

	/* Current source, initialized at probe समय */
	पूर्णांक curr_src;

	/* Desired source */
	पूर्णांक pending_src;

	/* Variables used during चयनes */
	bool चयनed;
	kसमय_प्रकार irq_समय;
	kसमय_प्रकार load_समय;

	/* Current output type; true == mono, false == color */
	bool mono;
	bool asleep;
	/* This get set जबतक controlling fb blank state from the driver */
	bool ignore_fb_events;
पूर्ण;

काष्ठा dcon_platक्रमm_data अणु
	पूर्णांक (*init)(काष्ठा dcon_priv *dcon);
	व्योम (*bus_stabilize_wiggle)(व्योम);
	व्योम (*set_dconload)(पूर्णांक load);
	पूर्णांक (*पढ़ो_status)(u8 *status);
पूर्ण;

काष्ठा dcon_gpio अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ flags;
पूर्ण;

#समावेश <linux/पूर्णांकerrupt.h>

irqवापस_t dcon_पूर्णांकerrupt(पूर्णांक irq, व्योम *id);

बाह्य काष्ठा dcon_platक्रमm_data dcon_pdata_xo_1;
बाह्य काष्ठा dcon_platक्रमm_data dcon_pdata_xo_1_5;

#पूर्ण_अगर
