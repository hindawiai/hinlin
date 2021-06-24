<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 */
#अगर_अघोषित _ASM_POWERPC_SERIAL_H
#घोषणा _ASM_POWERPC_SERIAL_H

/*
 * Serial ports are not listed here, because they are discovered
 * through the device tree.
 */

/* Default baud base अगर not found in device-tree */
#घोषणा BASE_BAUD ( 1843200 / 16 )

#अगर_घोषित CONFIG_PPC_UDBG_16550
बाह्य व्योम find_legacy_serial_ports(व्योम);
#अन्यथा
#घोषणा find_legacy_serial_ports()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _PPC64_SERIAL_H */
