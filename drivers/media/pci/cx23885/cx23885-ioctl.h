<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX23885/7/8 PCIe bridge
 *
 *  Various common ioctl() support functions
 *
 *  Copyright (c) 2009 Andy Walls <awalls@md.metrocast.net>
 */

#अगर_अघोषित _CX23885_IOCTL_H_
#घोषणा _CX23885_IOCTL_H_

पूर्णांक cx23885_g_chip_info(काष्ठा file *file, व्योम *fh,
			 काष्ठा v4l2_dbg_chip_info *chip);

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
पूर्णांक cx23885_g_रेजिस्टर(काष्ठा file *file, व्योम *fh,
		       काष्ठा v4l2_dbg_रेजिस्टर *reg);


पूर्णांक cx23885_s_रेजिस्टर(काष्ठा file *file, व्योम *fh,
		       स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg);

#पूर्ण_अगर
#पूर्ण_अगर
