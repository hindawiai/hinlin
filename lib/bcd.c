<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bcd.h>
#समावेश <linux/export.h>

अचिन्हित _bcd2bin(अचिन्हित अक्षर val)
अणु
	वापस (val & 0x0f) + (val >> 4) * 10;
पूर्ण
EXPORT_SYMBOL(_bcd2bin);

अचिन्हित अक्षर _bin2bcd(अचिन्हित val)
अणु
	वापस ((val / 10) << 4) + val % 10;
पूर्ण
EXPORT_SYMBOL(_bin2bcd);
