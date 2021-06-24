<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _LINUX_I8042_H
#घोषणा _LINUX_I8042_H


#समावेश <linux/types.h>

/*
 * Standard commands.
 */

#घोषणा I8042_CMD_CTL_RCTR	0x0120
#घोषणा I8042_CMD_CTL_WCTR	0x1060
#घोषणा I8042_CMD_CTL_TEST	0x01aa

#घोषणा I8042_CMD_KBD_DISABLE	0x00ad
#घोषणा I8042_CMD_KBD_ENABLE	0x00ae
#घोषणा I8042_CMD_KBD_TEST	0x01ab
#घोषणा I8042_CMD_KBD_LOOP	0x11d2

#घोषणा I8042_CMD_AUX_DISABLE	0x00a7
#घोषणा I8042_CMD_AUX_ENABLE	0x00a8
#घोषणा I8042_CMD_AUX_TEST	0x01a9
#घोषणा I8042_CMD_AUX_SEND	0x10d4
#घोषणा I8042_CMD_AUX_LOOP	0x11d3

#घोषणा I8042_CMD_MUX_PFX	0x0090
#घोषणा I8042_CMD_MUX_SEND	0x1090

/*
 * Status रेजिस्टर bits.
 */

#घोषणा I8042_STR_PARITY	0x80
#घोषणा I8042_STR_TIMEOUT	0x40
#घोषणा I8042_STR_AUXDATA	0x20
#घोषणा I8042_STR_KEYLOCK	0x10
#घोषणा I8042_STR_CMDDAT	0x08
#घोषणा I8042_STR_MUXERR	0x04
#घोषणा I8042_STR_IBF		0x02
#घोषणा I8042_STR_OBF		0x01

/*
 * Control रेजिस्टर bits.
 */

#घोषणा I8042_CTR_KBDINT	0x01
#घोषणा I8042_CTR_AUXINT	0x02
#घोषणा I8042_CTR_IGNKEYLOCK	0x08
#घोषणा I8042_CTR_KBDDIS	0x10
#घोषणा I8042_CTR_AUXDIS	0x20
#घोषणा I8042_CTR_XLATE		0x40

काष्ठा serio;

#अगर defined(CONFIG_SERIO_I8042) || defined(CONFIG_SERIO_I8042_MODULE)

व्योम i8042_lock_chip(व्योम);
व्योम i8042_unlock_chip(व्योम);
पूर्णांक i8042_command(अचिन्हित अक्षर *param, पूर्णांक command);
पूर्णांक i8042_install_filter(bool (*filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
					काष्ठा serio *serio));
पूर्णांक i8042_हटाओ_filter(bool (*filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				       काष्ठा serio *serio));

#अन्यथा

अटल अंतरभूत व्योम i8042_lock_chip(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम i8042_unlock_chip(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक i8042_command(अचिन्हित अक्षर *param, पूर्णांक command)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक i8042_install_filter(bool (*filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
					काष्ठा serio *serio))
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक i8042_हटाओ_filter(bool (*filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				       काष्ठा serio *serio))
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
