<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/** HPI Version Definitions
Development releases have odd minor version.
Production releases have even minor version.

\पile hpi_version.h
*/

#अगर_अघोषित _HPI_VERSION_H
#घोषणा _HPI_VERSION_H

/* Use single digits क्रम versions less that 10 to aव्योम octal. */
/* *** HPI_VER is the only edit required to update version *** */
/** HPI version */
#घोषणा HPI_VER HPI_VERSION_CONSTRUCTOR(4, 14, 3)

/** HPI version string in करोtted decimal क्रमmat */
#घोषणा HPI_VER_STRING "4.14.03"

/** Library version as करोcumented in hpi-api-versions.txt */
#घोषणा HPI_LIB_VER  HPI_VERSION_CONSTRUCTOR(10, 4, 0)

/** Conकाष्ठा hpi version number from major, minor, release numbers */
#घोषणा HPI_VERSION_CONSTRUCTOR(maj, min, r) ((maj << 16) + (min << 8) + r)

/** Extract major version from hpi version number */
#घोषणा HPI_VER_MAJOR(v) ((पूर्णांक)(v >> 16))
/** Extract minor version from hpi version number */
#घोषणा HPI_VER_MINOR(v) ((पूर्णांक)((v >> 8) & 0xFF))
/** Extract release from hpi version number */
#घोषणा HPI_VER_RELEASE(v) ((पूर्णांक)(v & 0xFF))

#पूर्ण_अगर
