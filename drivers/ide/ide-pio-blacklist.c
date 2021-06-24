<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PIO blacklist.  Some drives incorrectly report their maximal PIO mode,
 * at least in respect to CMD640.  Here we keep info on some known drives.
 *
 * Changes to the ide_pio_blacklist[] should be made with EXTREME CAUTION
 * to aव्योम अवरोधing the fragile cmd640.c support.
 */

#समावेश <linux/माला.स>
#समावेश <linux/ide.h>

अटल काष्ठा ide_pio_info अणु
	स्थिर अक्षर	*name;
	पूर्णांक		pio;
पूर्ण ide_pio_blacklist [] = अणु
	अणु "Conner Peripherals 540MB - CFS540A", 3 पूर्ण,

	अणु "WDC AC2700",  3 पूर्ण,
	अणु "WDC AC2540",  3 पूर्ण,
	अणु "WDC AC2420",  3 पूर्ण,
	अणु "WDC AC2340",  3 पूर्ण,
	अणु "WDC AC2250",  0 पूर्ण,
	अणु "WDC AC2200",  0 पूर्ण,
	अणु "WDC AC21200", 4 पूर्ण,
	अणु "WDC AC2120",  0 पूर्ण,
	अणु "WDC AC2850",  3 पूर्ण,
	अणु "WDC AC1270",  3 पूर्ण,
	अणु "WDC AC1170",  1 पूर्ण,
	अणु "WDC AC1210",  1 पूर्ण,
	अणु "WDC AC280",   0 पूर्ण,
	अणु "WDC AC31000", 3 पूर्ण,
	अणु "WDC AC31200", 3 पूर्ण,

	अणु "Maxtor 7131 AT", 1 पूर्ण,
	अणु "Maxtor 7171 AT", 1 पूर्ण,
	अणु "Maxtor 7213 AT", 1 पूर्ण,
	अणु "Maxtor 7245 AT", 1 पूर्ण,
	अणु "Maxtor 7345 AT", 1 पूर्ण,
	अणु "Maxtor 7546 AT", 3 पूर्ण,
	अणु "Maxtor 7540 AV", 3 पूर्ण,

	अणु "SAMSUNG SHD-3121A", 1 पूर्ण,
	अणु "SAMSUNG SHD-3122A", 1 पूर्ण,
	अणु "SAMSUNG SHD-3172A", 1 पूर्ण,

	अणु "ST5660A",  3 पूर्ण,
	अणु "ST3660A",  3 पूर्ण,
	अणु "ST3630A",  3 पूर्ण,
	अणु "ST3655A",  3 पूर्ण,
	अणु "ST3391A",  3 पूर्ण,
	अणु "ST3390A",  1 पूर्ण,
	अणु "ST3600A",  1 पूर्ण,
	अणु "ST3290A",  0 पूर्ण,
	अणु "ST3144A",  0 पूर्ण,
	अणु "ST3491A",  1 पूर्ण, /* reports 3, should be 1 or 2 (depending on drive)
			      according to Seagate's FIND-ATA program */

	अणु "QUANTUM ELS127A", 0 पूर्ण,
	अणु "QUANTUM ELS170A", 0 पूर्ण,
	अणु "QUANTUM LPS240A", 0 पूर्ण,
	अणु "QUANTUM LPS210A", 3 पूर्ण,
	अणु "QUANTUM LPS270A", 3 पूर्ण,
	अणु "QUANTUM LPS365A", 3 पूर्ण,
	अणु "QUANTUM LPS540A", 3 पूर्ण,
	अणु "QUANTUM LIGHTNING 540A", 3 पूर्ण,
	अणु "QUANTUM LIGHTNING 730A", 3 पूर्ण,

	अणु "QUANTUM FIREBALL_540", 3 पूर्ण, /* Older Quantum Fireballs करोn't work */
	अणु "QUANTUM FIREBALL_640", 3 पूर्ण,
	अणु "QUANTUM FIREBALL_1080", 3 पूर्ण,
	अणु "QUANTUM FIREBALL_1280", 3 पूर्ण,
	अणु शून्य, 0 पूर्ण
पूर्ण;

/**
 *	ide_scan_pio_blacklist 	-	check क्रम a blacklisted drive
 *	@model: Drive model string
 *
 *	This routine searches the ide_pio_blacklist क्रम an entry
 *	matching the start/whole of the supplied model name.
 *
 *	Returns -1 अगर no match found.
 *	Otherwise वापसs the recommended PIO mode from ide_pio_blacklist[].
 */

पूर्णांक ide_scan_pio_blacklist(अक्षर *model)
अणु
	काष्ठा ide_pio_info *p;

	क्रम (p = ide_pio_blacklist; p->name != शून्य; p++) अणु
		अगर (म_भेदन(p->name, model, म_माप(p->name)) == 0)
			वापस p->pio;
	पूर्ण
	वापस -1;
पूर्ण
