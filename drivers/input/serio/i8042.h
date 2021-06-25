<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _I8042_H
#घोषणा _I8042_H


/*
 *  Copyright (c) 1999-2002 Vojtech Pavlik
 */

/*
 * Arch-dependent अंतरभूत functions and defines.
 */

#अगर defined(CONFIG_MACH_JAZZ)
#समावेश "i8042-jazzio.h"
#या_अगर defined(CONFIG_SGI_HAS_I8042)
#समावेश "i8042-ip22io.h"
#या_अगर defined(CONFIG_SNI_RM)
#समावेश "i8042-snirm.h"
#या_अगर defined(CONFIG_SPARC)
#समावेश "i8042-sparcio.h"
#या_अगर defined(CONFIG_X86) || defined(CONFIG_IA64)
#समावेश "i8042-x86ia64io.h"
#अन्यथा
#समावेश "i8042-io.h"
#पूर्ण_अगर

/*
 * This is in 50us units, the समय we रुको क्रम the i8042 to react. This
 * has to be दीर्घ enough क्रम the i8042 itself to समयout on sending a byte
 * to a non-existent mouse.
 */

#घोषणा I8042_CTL_TIMEOUT	10000

/*
 * Return codes.
 */

#घोषणा I8042_RET_CTL_TEST	0x55

/*
 * Expected maximum पूर्णांकernal i8042 buffer size. This is used क्रम flushing
 * the i8042 buffers.
 */

#घोषणा I8042_BUFFER_SIZE	16

/*
 * Number of AUX ports on controllers supporting active multiplexing
 * specअगरication
 */

#घोषणा I8042_NUM_MUX_PORTS	4

/*
 * Debug.
 */

#अगर_घोषित DEBUG
अटल अचिन्हित दीर्घ i8042_start_समय;
#घोषणा dbg_init() करो अणु i8042_start_समय = jअगरfies; पूर्ण जबतक (0)
#घोषणा dbg(क्रमmat, arg...)							\
	करो अणु									\
		अगर (i8042_debug)						\
			prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": [%d] " क्रमmat,	\
			       (पूर्णांक) (jअगरfies - i8042_start_समय), ##arg);	\
	पूर्ण जबतक (0)

#घोषणा filter_dbg(filter, data, क्रमmat, args...)		\
	करो अणु							\
		अगर (!i8042_debug)				\
			अवरोध;					\
								\
		अगर (!filter || i8042_unmask_kbd_data)		\
			dbg("%02x " क्रमmat, data, ##args);	\
		अन्यथा						\
			dbg("** " क्रमmat, ##args);		\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा dbg_init() करो अणु पूर्ण जबतक (0)
#घोषणा dbg(क्रमmat, arg...)							\
	करो अणु									\
		अगर (0)								\
			prपूर्णांकk(KERN_DEBUG pr_fmt(क्रमmat), ##arg);		\
	पूर्ण जबतक (0)

#घोषणा filter_dbg(filter, data, क्रमmat, args...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _I8042_H */
