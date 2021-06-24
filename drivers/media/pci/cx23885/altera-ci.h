<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * altera-ci.c
 *
 *  CI driver in conjunction with NetUp Dual DVB-T/C RF CI card
 *
 * Copyright (C) 2010 NetUP Inc.
 * Copyright (C) 2010 Igor M. Liplianin <liplianin@netup.ru>
 */
#अगर_अघोषित __ALTERA_CI_H
#घोषणा __ALTERA_CI_H

#घोषणा ALT_DATA	0x000000ff
#घोषणा ALT_TDI		0x00008000
#घोषणा ALT_TDO		0x00004000
#घोषणा ALT_TCK		0x00002000
#घोषणा ALT_RDY		0x00001000
#घोषणा ALT_RD		0x00000800
#घोषणा ALT_WR		0x00000400
#घोषणा ALT_AD_RG	0x00000200
#घोषणा ALT_CS		0x00000100

काष्ठा altera_ci_config अणु
	व्योम *dev;/* मुख्य dev, क्रम example cx23885_dev */
	व्योम *adapter;/* क्रम CI to connect to */
	काष्ठा dvb_demux *demux;/* क्रम hardware PID filter to connect to */
	पूर्णांक (*fpga_rw) (व्योम *dev, पूर्णांक ad_rg, पूर्णांक val, पूर्णांक rw);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_ALTERA_CI)

बाह्य पूर्णांक altera_ci_init(काष्ठा altera_ci_config *config, पूर्णांक ci_nr);
बाह्य व्योम altera_ci_release(व्योम *dev, पूर्णांक ci_nr);
बाह्य पूर्णांक altera_ci_irq(व्योम *dev);
बाह्य पूर्णांक altera_ci_tuner_reset(व्योम *dev, पूर्णांक ci_nr);

#अन्यथा

अटल अंतरभूत पूर्णांक altera_ci_init(काष्ठा altera_ci_config *config, पूर्णांक ci_nr)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम altera_ci_release(व्योम *dev, पूर्णांक ci_nr)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
पूर्ण

अटल अंतरभूत पूर्णांक altera_ci_irq(व्योम *dev)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक altera_ci_tuner_reset(व्योम *dev, पूर्णांक ci_nr)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

#पूर्ण_अगर
#अगर 0
अटल अंतरभूत पूर्णांक altera_hw_filt_init(काष्ठा altera_ci_config *config,
							पूर्णांक hw_filt_nr)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम altera_hw_filt_release(व्योम *dev, पूर्णांक filt_nr)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
पूर्ण

अटल अंतरभूत पूर्णांक altera_pid_feed_control(व्योम *dev, पूर्णांक filt_nr,
		काष्ठा dvb_demux_feed *dvbdmxfeed, पूर्णांक onoff)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MEDIA_ALTERA_CI */

#पूर्ण_अगर /* __ALTERA_CI_H */
