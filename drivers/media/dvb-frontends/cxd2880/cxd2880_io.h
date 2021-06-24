<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_पन.स
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * रेजिस्टर I/O पूर्णांकerface definitions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_IO_H
#घोषणा CXD2880_IO_H

#समावेश "cxd2880_common.h"

क्रमागत cxd2880_io_tgt अणु
	CXD2880_IO_TGT_SYS,
	CXD2880_IO_TGT_DMD
पूर्ण;

काष्ठा cxd2880_reg_value अणु
	u8 addr;
	u8 value;
पूर्ण;

काष्ठा cxd2880_io अणु
	पूर्णांक (*पढ़ो_regs)(काष्ठा cxd2880_io *io,
			 क्रमागत cxd2880_io_tgt tgt, u8 sub_address,
			 u8 *data, u32 size);
	पूर्णांक (*ग_लिखो_regs)(काष्ठा cxd2880_io *io,
			  क्रमागत cxd2880_io_tgt tgt, u8 sub_address,
			  स्थिर u8 *data, u32 size);
	पूर्णांक (*ग_लिखो_reg)(काष्ठा cxd2880_io *io,
			 क्रमागत cxd2880_io_tgt tgt, u8 sub_address,
			 u8 data);
	व्योम *अगर_object;
	u8 i2c_address_sys;
	u8 i2c_address_demod;
	u8 slave_select;
	व्योम *user;
पूर्ण;

पूर्णांक cxd2880_io_common_ग_लिखो_one_reg(काष्ठा cxd2880_io *io,
				    क्रमागत cxd2880_io_tgt tgt,
				    u8 sub_address, u8 data);

पूर्णांक cxd2880_io_set_reg_bits(काष्ठा cxd2880_io *io,
			    क्रमागत cxd2880_io_tgt tgt,
			    u8 sub_address, u8 data, u8 mask);

पूर्णांक cxd2880_io_ग_लिखो_multi_regs(काष्ठा cxd2880_io *io,
				क्रमागत cxd2880_io_tgt tgt,
				स्थिर काष्ठा cxd2880_reg_value reg_value[],
				u8 size);
#पूर्ण_अगर
