<शैली गुरु>
/*
 * Interface क्रम smsc fdc48m81x Super IO chip
 *
 * Author: MontaVista Software, Inc. source@mvista.com
 *
 * 2001-2003 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Copyright 2004 (c) MontaVista Software, Inc.
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/txx9/smsc_fdc37m81x.h>

/* Common Registers */
#घोषणा SMSC_FDC37M81X_CONFIG_INDEX  0x00
#घोषणा SMSC_FDC37M81X_CONFIG_DATA   0x01
#घोषणा SMSC_FDC37M81X_CONF	     0x02
#घोषणा SMSC_FDC37M81X_INDEX	     0x03
#घोषणा SMSC_FDC37M81X_DNUM	     0x07
#घोषणा SMSC_FDC37M81X_DID	     0x20
#घोषणा SMSC_FDC37M81X_DREV	     0x21
#घोषणा SMSC_FDC37M81X_PCNT	     0x22
#घोषणा SMSC_FDC37M81X_PMGT	     0x23
#घोषणा SMSC_FDC37M81X_OSC	     0x24
#घोषणा SMSC_FDC37M81X_CONFPA0	     0x26
#घोषणा SMSC_FDC37M81X_CONFPA1	     0x27
#घोषणा SMSC_FDC37M81X_TEST4	     0x2B
#घोषणा SMSC_FDC37M81X_TEST5	     0x2C
#घोषणा SMSC_FDC37M81X_TEST1	     0x2D
#घोषणा SMSC_FDC37M81X_TEST2	     0x2E
#घोषणा SMSC_FDC37M81X_TEST3	     0x2F

/* Logical device numbers */
#घोषणा SMSC_FDC37M81X_FDD	     0x00
#घोषणा SMSC_FDC37M81X_SERIAL1	     0x04
#घोषणा SMSC_FDC37M81X_SERIAL2	     0x05
#घोषणा SMSC_FDC37M81X_KBD	     0x07

/* Logical device Config Registers */
#घोषणा SMSC_FDC37M81X_ACTIVE	     0x30
#घोषणा SMSC_FDC37M81X_BASEADDR0     0x60
#घोषणा SMSC_FDC37M81X_BASEADDR1     0x61
#घोषणा SMSC_FDC37M81X_INT	     0x70
#घोषणा SMSC_FDC37M81X_INT2	     0x72
#घोषणा SMSC_FDC37M81X_MODE	     0xF0

/* Chip Config Values */
#घोषणा SMSC_FDC37M81X_CONFIG_ENTER  0x55
#घोषणा SMSC_FDC37M81X_CONFIG_EXIT   0xaa
#घोषणा SMSC_FDC37M81X_CHIP_ID	     0x4d

अटल अचिन्हित दीर्घ g_smsc_fdc37m81x_base;

अटल अंतरभूत अचिन्हित अक्षर smsc_fdc37m81x_rd(अचिन्हित अक्षर index)
अणु
	outb(index, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);

	वापस inb(g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_DATA);
पूर्ण

अटल अंतरभूत व्योम smsc_dc37m81x_wr(अचिन्हित अक्षर index, अचिन्हित अक्षर data)
अणु
	outb(index, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
	outb(data, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_DATA);
पूर्ण

व्योम smsc_fdc37m81x_config_beg(व्योम)
अणु
	अगर (g_smsc_fdc37m81x_base) अणु
		outb(SMSC_FDC37M81X_CONFIG_ENTER,
		     g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
	पूर्ण
पूर्ण

व्योम smsc_fdc37m81x_config_end(व्योम)
अणु
	अगर (g_smsc_fdc37m81x_base)
		outb(SMSC_FDC37M81X_CONFIG_EXIT,
		     g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
पूर्ण

u8 smsc_fdc37m81x_config_get(u8 reg)
अणु
	u8 val = 0;

	अगर (g_smsc_fdc37m81x_base)
		val = smsc_fdc37m81x_rd(reg);

	वापस val;
पूर्ण

व्योम smsc_fdc37m81x_config_set(u8 reg, u8 val)
अणु
	अगर (g_smsc_fdc37m81x_base)
		smsc_dc37m81x_wr(reg, val);
पूर्ण

अचिन्हित दीर्घ __init smsc_fdc37m81x_init(अचिन्हित दीर्घ port)
अणु
	स्थिर पूर्णांक field = माप(अचिन्हित दीर्घ) * 2;
	u8 chip_id;

	अगर (g_smsc_fdc37m81x_base)
		pr_warn("%s: stepping on old base=0x%0*lx\n", __func__, field,
			g_smsc_fdc37m81x_base);

	g_smsc_fdc37m81x_base = port;

	smsc_fdc37m81x_config_beg();

	chip_id = smsc_fdc37m81x_rd(SMSC_FDC37M81X_DID);
	अगर (chip_id == SMSC_FDC37M81X_CHIP_ID)
		smsc_fdc37m81x_config_end();
	अन्यथा अणु
		pr_warn("%s: unknown chip id 0x%02x\n", __func__, chip_id);
		g_smsc_fdc37m81x_base = 0;
	पूर्ण

	वापस g_smsc_fdc37m81x_base;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम smsc_fdc37m81x_config_dump_one(स्थिर अक्षर *key, u8 dev, u8 reg)
अणु
	pr_info("%s: dev=0x%02x reg=0x%02x val=0x%02x\n", key, dev, reg,
		smsc_fdc37m81x_rd(reg));
पूर्ण

व्योम smsc_fdc37m81x_config_dump(व्योम)
अणु
	u8 orig;
	स्थिर अक्षर *fname = __func__;

	smsc_fdc37m81x_config_beg();

	orig = smsc_fdc37m81x_rd(SMSC_FDC37M81X_DNUM);

	pr_info("%s: common\n", fname);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_DNUM);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_DID);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_DREV);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_PCNT);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_PMGT);

	pr_info("%s: keyboard\n", fname);
	smsc_dc37m81x_wr(SMSC_FDC37M81X_DNUM, SMSC_FDC37M81X_KBD);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_ACTIVE);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_INT);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_INT2);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_LDCR_F0);

	smsc_dc37m81x_wr(SMSC_FDC37M81X_DNUM, orig);

	smsc_fdc37m81x_config_end();
पूर्ण
#पूर्ण_अगर
