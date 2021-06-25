<शैली गुरु>
/*
 * include/यंत्र-xtensa/bootparam.h
 *
 * Definition of the Linux/Xtensa boot parameter काष्ठाure
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005  Tensilica Inc.
 *
 * (Concept borrowed from the 68K port)
 */

#अगर_अघोषित _XTENSA_BOOTPARAM_H
#घोषणा _XTENSA_BOOTPARAM_H

#घोषणा BP_VERSION 0x0001

#घोषणा BP_TAG_COMMAND_LINE	0x1001	/* command line (0-terminated string)*/
#घोषणा BP_TAG_INITRD		0x1002	/* ramdisk addr and size (bp_meminfo) */
#घोषणा BP_TAG_MEMORY		0x1003	/* memory addr and size (bp_meminfo) */
#घोषणा BP_TAG_SERIAL_BAUDRATE	0x1004	/* baud rate of current console. */
#घोषणा BP_TAG_SERIAL_PORT	0x1005	/* serial device of current console */
#घोषणा BP_TAG_FDT		0x1006	/* flat device tree addr */

#घोषणा BP_TAG_FIRST		0x7B0B  /* first tag with a version number */
#घोषणा BP_TAG_LAST 		0x7E0B	/* last tag */

#अगर_अघोषित __ASSEMBLY__

/* All records are aligned to 4 bytes */

प्रकार काष्ठा bp_tag अणु
	अचिन्हित लघु id;	/* tag id */
	अचिन्हित लघु size;	/* size of this record excluding the काष्ठाure*/
	अचिन्हित दीर्घ data[0];	/* data */
पूर्ण bp_tag_t;

काष्ठा bp_meminfo अणु
	अचिन्हित दीर्घ type;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

#घोषणा MEMORY_TYPE_CONVENTIONAL	0x1000
#घोषणा MEMORY_TYPE_NONE		0x2000

#पूर्ण_अगर
#पूर्ण_अगर
