<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FCNTL_H
#घोषणा _LINUX_FCNTL_H

#समावेश <linux/स्थिति.स>
#समावेश <uapi/linux/fcntl.h>

/* List of all valid flags क्रम the खोलो/खोलोat flags argument: */
#घोषणा VALID_OPEN_FLAGS \
	(O_RDONLY | O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | \
	 O_APPEND | O_NDELAY | O_NONBLOCK | __O_SYNC | O_DSYNC | \
	 FASYNC	| O_सूचीECT | O_LARGEखाता | O_सूचीECTORY | O_NOFOLLOW | \
	 O_NOATIME | O_CLOEXEC | O_PATH | __O_TMPखाता)

/* List of all valid flags क्रम the how->upgrade_mask argument: */
#घोषणा VALID_UPGRADE_FLAGS \
	(UPGRADE_NOWRITE | UPGRADE_NOREAD)

/* List of all valid flags क्रम the how->resolve argument: */
#घोषणा VALID_RESOLVE_FLAGS \
	(RESOLVE_NO_XDEV | RESOLVE_NO_MAGICLINKS | RESOLVE_NO_SYMLINKS | \
	 RESOLVE_BENEATH | RESOLVE_IN_ROOT | RESOLVE_CACHED)

/* List of all खोलो_how "versions". */
#घोषणा OPEN_HOW_SIZE_VER0	24 /* माप first published काष्ठा */
#घोषणा OPEN_HOW_SIZE_LATEST	OPEN_HOW_SIZE_VER0

#अगर_अघोषित क्रमce_o_largefile
#घोषणा क्रमce_o_largefile() (!IS_ENABLED(CONFIG_ARCH_32BIT_OFF_T))
#पूर्ण_अगर

#अगर BITS_PER_LONG == 32
#घोषणा IS_GETLK32(cmd)		((cmd) == F_GETLK)
#घोषणा IS_SETLK32(cmd)		((cmd) == F_SETLK)
#घोषणा IS_SETLKW32(cmd)	((cmd) == F_SETLKW)
#घोषणा IS_GETLK64(cmd)		((cmd) == F_GETLK64)
#घोषणा IS_SETLK64(cmd)		((cmd) == F_SETLK64)
#घोषणा IS_SETLKW64(cmd)	((cmd) == F_SETLKW64)
#अन्यथा
#घोषणा IS_GETLK32(cmd)		(0)
#घोषणा IS_SETLK32(cmd)		(0)
#घोषणा IS_SETLKW32(cmd)	(0)
#घोषणा IS_GETLK64(cmd)		((cmd) == F_GETLK)
#घोषणा IS_SETLK64(cmd)		((cmd) == F_SETLK)
#घोषणा IS_SETLKW64(cmd)	((cmd) == F_SETLKW)
#पूर्ण_अगर /* BITS_PER_LONG == 32 */

#घोषणा IS_GETLK(cmd)	(IS_GETLK32(cmd)  || IS_GETLK64(cmd))
#घोषणा IS_SETLK(cmd)	(IS_SETLK32(cmd)  || IS_SETLK64(cmd))
#घोषणा IS_SETLKW(cmd)	(IS_SETLKW32(cmd) || IS_SETLKW64(cmd))

#पूर्ण_अगर
