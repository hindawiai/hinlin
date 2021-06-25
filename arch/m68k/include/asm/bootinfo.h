<शैली गुरु>
/*
** यंत्र/bootinfo.h -- Definition of the Linux/m68k boot inक्रमmation काष्ठाure
**
** Copyright 1992 by Greg Harp
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
*/

#अगर_अघोषित _M68K_BOOTINFO_H
#घोषणा _M68K_BOOTINFO_H

#समावेश <uapi/यंत्र/bootinfo.h>


#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_BOOTINFO_PROC
बाह्य व्योम save_bootinfo(स्थिर काष्ठा bi_record *bi);
#अन्यथा
अटल अंतरभूत व्योम save_bootinfo(स्थिर काष्ठा bi_record *bi) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_UBOOT
व्योम process_uboot_commandline(अक्षर *commandp, पूर्णांक size);
#अन्यथा
अटल अंतरभूत व्योम process_uboot_commandline(अक्षर *commandp, पूर्णांक size) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */


#पूर्ण_अगर /* _M68K_BOOTINFO_H */
