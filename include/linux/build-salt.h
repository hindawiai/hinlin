<शैली गुरु>
#अगर_अघोषित __BUILD_SALT_H
#घोषणा __BUILD_SALT_H

#समावेश <linux/elfnote.h>

#घोषणा LINUX_ELFNOTE_BUILD_SALT       0x100

#अगर_घोषित __ASSEMBLER__

#घोषणा BUILD_SALT \
       ELFNOTE(Linux, LINUX_ELFNOTE_BUILD_SALT, .asciz CONFIG_BUILD_SALT)

#अन्यथा

#घोषणा BUILD_SALT \
       ELFNOTE32("Linux", LINUX_ELFNOTE_BUILD_SALT, CONFIG_BUILD_SALT)

#पूर्ण_अगर

#पूर्ण_अगर /* __BUILD_SALT_H */
