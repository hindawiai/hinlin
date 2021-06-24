<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __BUDGET_DVB__
#घोषणा __BUDGET_DVB__

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvbdev.h>
#समावेश <media/demux.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dmxdev.h>
#समावेश "dvb_filter.h"
#समावेश <media/dvb_net.h>

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <media/drv-पूर्णांकf/saa7146.h>

बाह्य पूर्णांक budget_debug;

#अगर_घोषित dprपूर्णांकk
#अघोषित dprपूर्णांकk
#पूर्ण_अगर

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (level & budget_debug)					\
		prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": %s(): " fmt,	\
		       __func__, ##arg);				\
पूर्ण जबतक (0)


काष्ठा budget_info अणु
	अक्षर *name;
	पूर्णांक type;
पूर्ण;

/* place to store all the necessary device inक्रमmation */
काष्ठा budget अणु

	/* devices */
	काष्ठा dvb_device dvb_dev;
	काष्ठा dvb_net dvb_net;

	काष्ठा saa7146_dev *dev;

	काष्ठा i2c_adapter i2c_adap;
	काष्ठा budget_info *card;

	अचिन्हित अक्षर *grabbing;
	काष्ठा saa7146_pgtable pt;

	काष्ठा tasklet_काष्ठा fidb_tasklet;
	काष्ठा tasklet_काष्ठा vpe_tasklet;

	काष्ठा dmxdev dmxdev;
	काष्ठा dvb_demux demux;

	काष्ठा dmx_frontend hw_frontend;
	काष्ठा dmx_frontend mem_frontend;

	पूर्णांक ci_present;
	पूर्णांक video_port;

	u32 buffer_width;
	u32 buffer_height;
	u32 buffer_size;
	u32 buffer_warning_threshold;
	u32 buffer_warnings;
	अचिन्हित दीर्घ buffer_warning_समय;

	u32 ttbp;
	पूर्णांक feeding;

	spinlock_t feedlock;

	spinlock_t debilock;

	काष्ठा dvb_adapter dvb_adapter;
	काष्ठा dvb_frontend *dvb_frontend;
	पूर्णांक (*पढ़ो_fe_status)(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status);
	पूर्णांक fe_synced;

	व्योम *priv;
पूर्ण;

#घोषणा MAKE_BUDGET_INFO(x_var,x_name,x_type) \
अटल काष्ठा budget_info x_var ## _info = अणु \
	.name=x_name,	\
	.type=x_type पूर्ण;	\
अटल काष्ठा saa7146_pci_extension_data x_var = अणु \
	.ext_priv = &x_var ## _info, \
	.ext = &budget_extension पूर्ण;

#घोषणा BUDGET_TT		   0
#घोषणा BUDGET_TT_HW_DISEQC	   1
#घोषणा BUDGET_PATCH		   3
#घोषणा BUDGET_FS_ACTIVY	   4
#घोषणा BUDGET_CIN1200S		   5
#घोषणा BUDGET_CIN1200C		   6
#घोषणा BUDGET_CIN1200T		   7
#घोषणा BUDGET_KNC1S		   8
#घोषणा BUDGET_KNC1C		   9
#घोषणा BUDGET_KNC1T		   10
#घोषणा BUDGET_KNC1SP		   11
#घोषणा BUDGET_KNC1CP		   12
#घोषणा BUDGET_KNC1TP		   13
#घोषणा BUDGET_TVSTAR		   14
#घोषणा BUDGET_CIN1200C_MK3	   15
#घोषणा BUDGET_KNC1C_MK3	   16
#घोषणा BUDGET_KNC1CP_MK3	   17
#घोषणा BUDGET_KNC1S2              18
#घोषणा BUDGET_KNC1C_TDA10024	   19

#घोषणा BUDGET_VIDEO_PORTA         0
#घोषणा BUDGET_VIDEO_PORTB         1

बाह्य पूर्णांक ttpci_budget_init(काष्ठा budget *budget, काष्ठा saa7146_dev *dev,
			     काष्ठा saa7146_pci_extension_data *info,
			     काष्ठा module *owner, लघु *adapter_nums);
बाह्य व्योम ttpci_budget_init_hooks(काष्ठा budget *budget);
बाह्य पूर्णांक ttpci_budget_deinit(काष्ठा budget *budget);
बाह्य व्योम ttpci_budget_irq10_handler(काष्ठा saa7146_dev *dev, u32 * isr);
बाह्य व्योम ttpci_budget_set_video_port(काष्ठा saa7146_dev *dev, पूर्णांक video_port);
बाह्य पूर्णांक ttpci_budget_debiपढ़ो(काष्ठा budget *budget, u32 config, पूर्णांक addr, पूर्णांक count,
				 पूर्णांक uselocks, पूर्णांक nobusyloop);
बाह्य पूर्णांक ttpci_budget_debiग_लिखो(काष्ठा budget *budget, u32 config, पूर्णांक addr, पूर्णांक count, u32 value,
				  पूर्णांक uselocks, पूर्णांक nobusyloop);

#पूर्ण_अगर
