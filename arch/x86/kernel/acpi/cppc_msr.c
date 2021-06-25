<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cppc_msr.c:  MSR Interface क्रम CPPC
 * Copyright (c) 2016, Intel Corporation.
 */

#समावेश <acpi/cppc_acpi.h>
#समावेश <यंत्र/msr.h>

/* Refer to drivers/acpi/cppc_acpi.c क्रम the description of functions */

bool cpc_ffh_supported(व्योम)
अणु
	वापस true;
पूर्ण

पूर्णांक cpc_पढ़ो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 *val)
अणु
	पूर्णांक err;

	err = rdmsrl_safe_on_cpu(cpunum, reg->address, val);
	अगर (!err) अणु
		u64 mask = GENMASK_ULL(reg->bit_offset + reg->bit_width - 1,
				       reg->bit_offset);

		*val &= mask;
		*val >>= reg->bit_offset;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक cpc_ग_लिखो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 val)
अणु
	u64 rd_val;
	पूर्णांक err;

	err = rdmsrl_safe_on_cpu(cpunum, reg->address, &rd_val);
	अगर (!err) अणु
		u64 mask = GENMASK_ULL(reg->bit_offset + reg->bit_width - 1,
				       reg->bit_offset);

		val <<= reg->bit_offset;
		val &= mask;
		rd_val &= ~mask;
		rd_val |= val;
		err = wrmsrl_safe_on_cpu(cpunum, reg->address, rd_val);
	पूर्ण
	वापस err;
पूर्ण
