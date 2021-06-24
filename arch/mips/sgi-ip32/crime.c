<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001, 2003 Keith M Wesolowski
 * Copyright (C) 2005 Ilya A. Volynets <ilya@total-knowledge.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ip32/crime.h>
#समावेश <यंत्र/ip32/mace.h>

काष्ठा sgi_crime __iomem *crime;
काष्ठा sgi_mace __iomem *mace;

EXPORT_SYMBOL_GPL(mace);

व्योम __init crime_init(व्योम)
अणु
	अचिन्हित पूर्णांक id, rev;
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);

	set_io_port_base((अचिन्हित दीर्घ) ioremap(MACEPCI_LOW_IO, 0x2000000));
	crime = ioremap(CRIME_BASE, माप(काष्ठा sgi_crime));
	mace = ioremap(MACE_BASE, माप(काष्ठा sgi_mace));

	id = crime->id;
	rev = id & CRIME_ID_REV;
	id = (id & CRIME_ID_IDBITS) >> 4;
	prपूर्णांकk(KERN_INFO "CRIME id %1x rev %d at 0x%0*lx\n",
	       id, rev, field, (अचिन्हित दीर्घ) CRIME_BASE);
पूर्ण

irqवापस_t crime_memerr_पूर्णांकr(अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ stat, addr;
	पूर्णांक fatal = 0;

	stat = crime->mem_error_stat & CRIME_MEM_ERROR_STAT_MASK;
	addr = crime->mem_error_addr & CRIME_MEM_ERROR_ADDR_MASK;

	prपूर्णांकk("CRIME memory error at 0x%08lx ST 0x%08lx<", addr, stat);

	अगर (stat & CRIME_MEM_ERROR_INV)
		prपूर्णांकk("INV,");
	अगर (stat & CRIME_MEM_ERROR_ECC) अणु
		अचिन्हित दीर्घ ecc_syn =
			crime->mem_ecc_syn & CRIME_MEM_ERROR_ECC_SYN_MASK;
		अचिन्हित दीर्घ ecc_gen =
			crime->mem_ecc_chk & CRIME_MEM_ERROR_ECC_CHK_MASK;
		prपूर्णांकk("ECC,SYN=0x%08lx,GEN=0x%08lx,", ecc_syn, ecc_gen);
	पूर्ण
	अगर (stat & CRIME_MEM_ERROR_MULTIPLE) अणु
		fatal = 1;
		prपूर्णांकk("MULTIPLE,");
	पूर्ण
	अगर (stat & CRIME_MEM_ERROR_HARD_ERR) अणु
		fatal = 1;
		prपूर्णांकk("HARD,");
	पूर्ण
	अगर (stat & CRIME_MEM_ERROR_SOFT_ERR)
		prपूर्णांकk("SOFT,");
	अगर (stat & CRIME_MEM_ERROR_CPU_ACCESS)
		prपूर्णांकk("CPU,");
	अगर (stat & CRIME_MEM_ERROR_VICE_ACCESS)
		prपूर्णांकk("VICE,");
	अगर (stat & CRIME_MEM_ERROR_GBE_ACCESS)
		prपूर्णांकk("GBE,");
	अगर (stat & CRIME_MEM_ERROR_RE_ACCESS)
		prपूर्णांकk("RE,REID=0x%02lx,", (stat & CRIME_MEM_ERROR_RE_ID)>>8);
	अगर (stat & CRIME_MEM_ERROR_MACE_ACCESS)
		prपूर्णांकk("MACE,MACEID=0x%02lx,", stat & CRIME_MEM_ERROR_MACE_ID);

	crime->mem_error_stat = 0;

	अगर (fatal) अणु
		prपूर्णांकk("FATAL>\n");
		panic("Fatal memory error.");
	पूर्ण अन्यथा
		prपूर्णांकk("NONFATAL>\n");

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t crime_cpuerr_पूर्णांकr(अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ stat = crime->cpu_error_stat & CRIME_CPU_ERROR_MASK;
	अचिन्हित दीर्घ addr = crime->cpu_error_addr & CRIME_CPU_ERROR_ADDR_MASK;

	addr <<= 2;
	prपूर्णांकk("CRIME CPU error at 0x%09lx status 0x%08lx\n", addr, stat);
	crime->cpu_error_stat = 0;

	वापस IRQ_HANDLED;
पूर्ण
