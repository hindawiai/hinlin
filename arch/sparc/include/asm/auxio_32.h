<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * auxपन.स:  Definitions and code क्रम the Auxiliary I/O रेजिस्टर.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */
#अगर_अघोषित _SPARC_AUXIO_H
#घोषणा _SPARC_AUXIO_H

#समावेश <यंत्र/vaddrs.h>

/* This रेजिस्टर is an अचिन्हित अक्षर in IO space.  It करोes two things.
 * First, it is used to control the front panel LED light on machines
 * that have it (good क्रम testing entry poपूर्णांकs to trap handlers and irq's)
 * Secondly, it controls various floppy drive parameters.
 */
#घोषणा AUXIO_ORMEIN      0xf0    /* All ग_लिखोs must set these bits. */
#घोषणा AUXIO_ORMEIN4M    0xc0    /* sun4m - All ग_लिखोs must set these bits. */
#घोषणा AUXIO_FLPY_DENS   0x20    /* Floppy density, high अगर set. Read only. */
#घोषणा AUXIO_FLPY_DCHG   0x10    /* A disk change occurred.  Read only. */
#घोषणा AUXIO_EDGE_ON     0x10    /* sun4m - On means Jumper block is in. */
#घोषणा AUXIO_FLPY_DSEL   0x08    /* Drive select/start-motor. Write only. */
#घोषणा AUXIO_LINK_TEST   0x08    /* sun4m - On means TPE Carrier detect. */

/* Set the following to one, then zero, after करोing a pseuकरो DMA transfer. */
#घोषणा AUXIO_FLPY_TCNT   0x04    /* Floppy terminal count. Write only. */

/* Set the following to zero to eject the floppy. */
#घोषणा AUXIO_FLPY_EJCT   0x02    /* Eject floppy disk.  Write only. */
#घोषणा AUXIO_LED         0x01    /* On अगर set, off अगर unset. Read/Write */

#अगर_अघोषित __ASSEMBLY__

/*
 * NOTE: these routines are implementation dependent--
 * understand the hardware you are querying!
 */
व्योम set_auxio(अचिन्हित अक्षर bits_on, अचिन्हित अक्षर bits_off);
अचिन्हित अक्षर get_auxio(व्योम); /* .../यंत्र/floppy.h */

/*
 * The following routines are provided क्रम driver-compatibility
 * with sparc64 (primarily sunlance.c)
 */

#घोषणा AUXIO_LTE_ON    1
#घोषणा AUXIO_LTE_OFF   0

/* auxio_set_lte - Set Link Test Enable (TPE Link Detect)
 *
 * on - AUXIO_LTE_ON or AUXIO_LTE_OFF
 */
#घोषणा auxio_set_lte(on) \
करो अणु \
	अगर(on) अणु \
		set_auxio(AUXIO_LINK_TEST, 0); \
	पूर्ण अन्यथा अणु \
		set_auxio(0, AUXIO_LINK_TEST); \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा AUXIO_LED_ON    1
#घोषणा AUXIO_LED_OFF   0

/* auxio_set_led - Set प्रणाली front panel LED
 *
 * on - AUXIO_LED_ON or AUXIO_LED_OFF
 */
#घोषणा auxio_set_led(on) \
करो अणु \
	अगर(on) अणु \
		set_auxio(AUXIO_LED, 0); \
	पूर्ण अन्यथा अणु \
		set_auxio(0, AUXIO_LED); \
	पूर्ण \
पूर्ण जबतक (0)

#पूर्ण_अगर /* !(__ASSEMBLY__) */


/* AUXIO2 (Power Off Control) */
बाह्य अस्थिर u8 __iomem *auxio_घातer_रेजिस्टर;

#घोषणा	AUXIO_POWER_DETECT_FAILURE	32
#घोषणा	AUXIO_POWER_CLEAR_FAILURE	2
#घोषणा	AUXIO_POWER_OFF			1


#पूर्ण_अगर /* !(_SPARC_AUXIO_H) */
