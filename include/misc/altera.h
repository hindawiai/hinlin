<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * altera.h
 *
 * altera FPGA driver
 *
 * Copyright (C) Altera Corporation 1998-2001
 * Copyright (C) 2010 NetUP Inc.
 * Copyright (C) 2010 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित _ALTERA_H_
#घोषणा _ALTERA_H_

काष्ठा altera_config अणु
	व्योम *dev;
	u8 *action;
	पूर्णांक (*jtag_io) (व्योम *dev, पूर्णांक पंचांगs, पूर्णांक tdi, पूर्णांक tकरो);
पूर्ण;

#अगर defined(CONFIG_ALTERA_STAPL) || \
		(defined(CONFIG_ALTERA_STAPL_MODULE) && defined(MODULE))

बाह्य पूर्णांक altera_init(काष्ठा altera_config *config, स्थिर काष्ठा firmware *fw);
#अन्यथा

अटल अंतरभूत पूर्णांक altera_init(काष्ठा altera_config *config,
						स्थिर काष्ठा firmware *fw)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ALTERA_STAPL */

#पूर्ण_अगर /* _ALTERA_H_ */
