<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2018 NXP
 */

#अगर_अघोषित __FSL_DPRTC_H
#घोषणा __FSL_DPRTC_H

/* Data Path Real Time Counter API
 * Contains initialization APIs and runसमय control APIs क्रम RTC
 */

काष्ठा fsl_mc_io;

#घोषणा DPRTC_MAX_IRQ_NUM	1
#घोषणा DPRTC_IRQ_INDEX		0

#घोषणा DPRTC_EVENT_PPS		0x08000000
#घोषणा DPRTC_EVENT_ETS1	0x00800000
#घोषणा DPRTC_EVENT_ETS2	0x00400000

पूर्णांक dprtc_खोलो(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       पूर्णांक dprtc_id,
	       u16 *token);

पूर्णांक dprtc_बंद(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token);

पूर्णांक dprtc_set_irq_enable(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 irq_index,
			 u8 en);

पूर्णांक dprtc_get_irq_enable(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 irq_index,
			 u8 *en);

पूर्णांक dprtc_set_irq_mask(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       u8 irq_index,
		       u32 mask);

पूर्णांक dprtc_get_irq_mask(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       u8 irq_index,
		       u32 *mask);

पूर्णांक dprtc_get_irq_status(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 irq_index,
			 u32 *status);

पूर्णांक dprtc_clear_irq_status(काष्ठा fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   u8 irq_index,
			   u32 status);

#पूर्ण_अगर /* __FSL_DPRTC_H */
