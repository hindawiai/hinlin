<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_io.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * रेजिस्टर I/O पूर्णांकerface functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश "cxd2880_io.h"

पूर्णांक cxd2880_io_common_ग_लिखो_one_reg(काष्ठा cxd2880_io *io,
				    क्रमागत cxd2880_io_tgt tgt,
				    u8 sub_address, u8 data)
अणु
	अगर (!io)
		वापस -EINVAL;

	वापस io->ग_लिखो_regs(io, tgt, sub_address, &data, 1);
पूर्ण

पूर्णांक cxd2880_io_set_reg_bits(काष्ठा cxd2880_io *io,
			    क्रमागत cxd2880_io_tgt tgt,
			    u8 sub_address, u8 data, u8 mask)
अणु
	पूर्णांक ret;

	अगर (!io)
		वापस -EINVAL;

	अगर (mask == 0x00)
		वापस 0;

	अगर (mask != 0xff) अणु
		u8 rdata = 0x00;

		ret = io->पढ़ो_regs(io, tgt, sub_address, &rdata, 1);
		अगर (ret)
			वापस ret;

		data = (data & mask) | (rdata & (mask ^ 0xff));
	पूर्ण

	वापस io->ग_लिखो_reg(io, tgt, sub_address, data);
पूर्ण

पूर्णांक cxd2880_io_ग_लिखो_multi_regs(काष्ठा cxd2880_io *io,
			     क्रमागत cxd2880_io_tgt tgt,
			     स्थिर काष्ठा cxd2880_reg_value reg_value[],
			     u8 size)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!io)
		वापस -EINVAL;

	क्रम (i = 0; i < size ; i++) अणु
		ret = io->ग_लिखो_reg(io, tgt, reg_value[i].addr,
				    reg_value[i].value);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
