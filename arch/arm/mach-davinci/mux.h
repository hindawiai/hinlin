<शैली गुरु>
/*
 * Pin-multiplex helper macros क्रम TI DaVinci family devices
 *
 * Author: Vladimir Barinov, MontaVista Software, Inc. <source@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Copyright (C) 2008 Texas Instruments.
 */
#अगर_अघोषित _MACH_DAVINCI_MUX_H_
#घोषणा _MACH_DAVINCI_MUX_H_

#समावेश <mach/mux.h>

#घोषणा MUX_CFG(soc, desc, muxreg, mode_offset, mode_mask, mux_mode, dbg)\
[soc##_##desc] = अणु							\
			.name =  #desc,					\
			.debug = dbg,					\
			.mux_reg_name = "PINMUX"#muxreg,		\
			.mux_reg = PINMUX(muxreg),			\
			.mask_offset = mode_offset,			\
			.mask = mode_mask,				\
			.mode = mux_mode,				\
		पूर्ण,

#घोषणा INT_CFG(soc, desc, mode_offset, mode_mask, mux_mode, dbg)	\
[soc##_##desc] = अणु							\
			.name =  #desc,					\
			.debug = dbg,					\
			.mux_reg_name = "INTMUX",			\
			.mux_reg = INTMUX,				\
			.mask_offset = mode_offset,			\
			.mask = mode_mask,				\
			.mode = mux_mode,				\
		पूर्ण,

#घोषणा EVT_CFG(soc, desc, mode_offset, mode_mask, mux_mode, dbg)	\
[soc##_##desc] = अणु							\
			.name =  #desc,					\
			.debug = dbg,					\
			.mux_reg_name = "EVTMUX",			\
			.mux_reg = EVTMUX,				\
			.mask_offset = mode_offset,			\
			.mask = mode_mask,				\
			.mode = mux_mode,				\
		पूर्ण,

#पूर्ण_अगर /* _MACH_DAVINCI_MUX_H */
