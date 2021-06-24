<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/superh/microdev/io.c
 *
 * Copyright (C) 2003 Sean McGoogan (Sean.McGoogan@superh.com)
 * Copyright (C) 2003, 2004 SuperH, Inc.
 * Copyright (C) 2004 Paul Mundt
 *
 * SuperH SH4-202 MicroDev board support.
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>
#समावेश <mach/microdev.h>

	/*
	 *	we need to have a 'safe' address to re-direct all I/O requests
	 *	that we करो not explicitly wish to handle. This safe address
	 *	must have the following properies:
	 *
	 *		* ग_लिखोs are ignored (no exception)
	 *		* पढ़ोs are benign (no side-effects)
	 *		* accesses of width 1, 2 and 4-bytes are all valid.
	 *
	 *	The Processor Version Register (PVR) has these properties.
	 */
#घोषणा	PVR	0xff000030	/* Processor Version Register */


#घोषणा	IO_IDE2_BASE		0x170ul	/* I/O base क्रम SMSC FDC37C93xAPM IDE #2 */
#घोषणा	IO_IDE1_BASE		0x1f0ul	/* I/O base क्रम SMSC FDC37C93xAPM IDE #1 */
#घोषणा IO_ISP1161_BASE		0x290ul /* I/O port क्रम Philips ISP1161x USB chip */
#घोषणा IO_SERIAL2_BASE		0x2f8ul /* I/O base क्रम SMSC FDC37C93xAPM Serial #2 */
#घोषणा	IO_LAN91C111_BASE	0x300ul	/* I/O base क्रम SMSC LAN91C111 Ethernet chip */
#घोषणा	IO_IDE2_MISC		0x376ul	/* I/O misc क्रम SMSC FDC37C93xAPM IDE #2 */
#घोषणा IO_SUPERIO_BASE		0x3f0ul /* I/O base क्रम SMSC FDC37C93xAPM SuperIO chip */
#घोषणा	IO_IDE1_MISC		0x3f6ul	/* I/O misc क्रम SMSC FDC37C93xAPM IDE #1 */
#घोषणा IO_SERIAL1_BASE		0x3f8ul /* I/O base क्रम SMSC FDC37C93xAPM Serial #1 */

#घोषणा	IO_ISP1161_EXTENT	0x04ul	/* I/O extent क्रम Philips ISP1161x USB chip */
#घोषणा	IO_LAN91C111_EXTENT	0x10ul	/* I/O extent क्रम SMSC LAN91C111 Ethernet chip */
#घोषणा	IO_SUPERIO_EXTENT	0x02ul	/* I/O extent क्रम SMSC FDC37C93xAPM SuperIO chip */
#घोषणा	IO_IDE_EXTENT		0x08ul	/* I/O extent क्रम IDE Task Register set */
#घोषणा IO_SERIAL_EXTENT	0x10ul

#घोषणा	IO_LAN91C111_PHYS	0xa7500000ul	/* Physical address of SMSC LAN91C111 Ethernet chip */
#घोषणा	IO_ISP1161_PHYS		0xa7700000ul	/* Physical address of Philips ISP1161x USB chip */
#घोषणा	IO_SUPERIO_PHYS		0xa7800000ul	/* Physical address of SMSC FDC37C93xAPM SuperIO chip */

/*
 * map I/O ports to memory-mapped addresses
 */
व्योम __iomem *microdev_ioport_map(अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ result;

	अगर ((offset >= IO_LAN91C111_BASE) &&
	    (offset <  IO_LAN91C111_BASE + IO_LAN91C111_EXTENT)) अणु
			/*
			 *	SMSC LAN91C111 Ethernet chip
			 */
		result = IO_LAN91C111_PHYS + offset - IO_LAN91C111_BASE;
	पूर्ण अन्यथा अगर ((offset >= IO_SUPERIO_BASE) &&
		   (offset <  IO_SUPERIO_BASE + IO_SUPERIO_EXTENT)) अणु
			/*
			 *	SMSC FDC37C93xAPM SuperIO chip
			 *
			 *	Configuration Registers
			 */
		result = IO_SUPERIO_PHYS + (offset << 1);
	पूर्ण अन्यथा अगर (((offset >= IO_IDE1_BASE) &&
		    (offset <  IO_IDE1_BASE + IO_IDE_EXTENT)) ||
		    (offset == IO_IDE1_MISC)) अणु
			/*
			 *	SMSC FDC37C93xAPM SuperIO chip
			 *
			 *	IDE #1
			 */
	        result = IO_SUPERIO_PHYS + (offset << 1);
	पूर्ण अन्यथा अगर (((offset >= IO_IDE2_BASE) &&
		    (offset <  IO_IDE2_BASE + IO_IDE_EXTENT)) ||
		    (offset == IO_IDE2_MISC)) अणु
			/*
			 *	SMSC FDC37C93xAPM SuperIO chip
			 *
			 *	IDE #2
			 */
	        result = IO_SUPERIO_PHYS + (offset << 1);
	पूर्ण अन्यथा अगर ((offset >= IO_SERIAL1_BASE) &&
		   (offset <  IO_SERIAL1_BASE + IO_SERIAL_EXTENT)) अणु
			/*
			 *	SMSC FDC37C93xAPM SuperIO chip
			 *
			 *	Serial #1
			 */
		result = IO_SUPERIO_PHYS + (offset << 1);
	पूर्ण अन्यथा अगर ((offset >= IO_SERIAL2_BASE) &&
		   (offset <  IO_SERIAL2_BASE + IO_SERIAL_EXTENT)) अणु
			/*
			 *	SMSC FDC37C93xAPM SuperIO chip
			 *
			 *	Serial #2
			 */
		result = IO_SUPERIO_PHYS + (offset << 1);
	पूर्ण अन्यथा अगर ((offset >= IO_ISP1161_BASE) &&
		   (offset < IO_ISP1161_BASE + IO_ISP1161_EXTENT)) अणु
			/*
			 *	Philips USB ISP1161x chip
			 */
		result = IO_ISP1161_PHYS + offset - IO_ISP1161_BASE;
	पूर्ण अन्यथा अणु
			/*
			 *	safe शेष.
			 */
		prपूर्णांकk("Warning: unexpected port in %s( offset = 0x%lx )\n",
		       __func__, offset);
		result = PVR;
	पूर्ण

	वापस (व्योम __iomem *)result;
पूर्ण
