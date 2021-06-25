<शैली गुरु>
#अगर_अघोषित __ELFNOTE_LTO_H
#घोषणा __ELFNOTE_LTO_H

#समावेश <linux/elfnote.h>

#घोषणा LINUX_ELFNOTE_LTO_INFO	0x101

#अगर_घोषित CONFIG_LTO
#घोषणा BUILD_LTO_INFO	ELFNOTE32("Linux", LINUX_ELFNOTE_LTO_INFO, 1)
#अन्यथा
#घोषणा BUILD_LTO_INFO	ELFNOTE32("Linux", LINUX_ELFNOTE_LTO_INFO, 0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ELFNOTE_LTO_H */
