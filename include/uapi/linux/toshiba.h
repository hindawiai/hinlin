<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* toshiba.h -- Linux driver क्रम accessing the SMM on Toshiba laptops 
 *
 * Copyright (c) 1996-2000  Jonathan A. Buzzard (jonathan@buzzard.org.uk)
 * Copyright (c) 2015  Azael Avalos <coproscefalo@gmail.com>
 *
 * Thanks to Juergen Heinzl <juergen@monocerus.demon.co.uk> क्रम the poपूर्णांकers
 * on making sure the काष्ठाure is aligned and packed.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 */

#अगर_अघोषित _UAPI_LINUX_TOSHIBA_H
#घोषणा _UAPI_LINUX_TOSHIBA_H

/*
 * Toshiba modules paths
 */

#घोषणा TOSH_PROC		"/proc/toshiba"
#घोषणा TOSH_DEVICE		"/dev/toshiba"
#घोषणा TOSHIBA_ACPI_PROC	"/proc/acpi/toshiba"
#घोषणा TOSHIBA_ACPI_DEVICE	"/dev/toshiba_acpi"

/*
 * Toshiba SMM काष्ठाure
 */

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक eax;
	अचिन्हित पूर्णांक ebx __attribute__ ((packed));
	अचिन्हित पूर्णांक ecx __attribute__ ((packed));
	अचिन्हित पूर्णांक edx __attribute__ ((packed));
	अचिन्हित पूर्णांक esi __attribute__ ((packed));
	अचिन्हित पूर्णांक edi __attribute__ ((packed));
पूर्ण SMMRegisters;

/*
 * IOCTLs (0x90 - 0x91)
 */

#घोषणा TOSH_SMM		_IOWR('t', 0x90, SMMRegisters)
/*
 * Convenience toshiba_acpi command.
 *
 * The System Configuration Interface (SCI) is खोलोed/बंदd पूर्णांकernally
 * to aव्योम userspace of buggy BIOSes.
 *
 * The toshiba_acpi module checks whether the eax रेजिस्टर is set with
 * SCI_GET (0xf300) or SCI_SET (0xf400), वापसing -EINVAL अगर not.
 */
#घोषणा TOSHIBA_ACPI_SCI	_IOWR('t', 0x91, SMMRegisters)


#पूर्ण_अगर /* _UAPI_LINUX_TOSHIBA_H */
