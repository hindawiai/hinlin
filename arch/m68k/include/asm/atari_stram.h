<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_ATARI_STRAM_H
#घोषणा _M68K_ATARI_STRAM_H

/*
 * Functions क्रम Atari ST-RAM management
 */

/* खुला पूर्णांकerface */
व्योम *atari_stram_alloc(अचिन्हित दीर्घ size, स्थिर अक्षर *owner);
व्योम atari_stram_मुक्त(व्योम *);
व्योम *atari_stram_to_virt(अचिन्हित दीर्घ phys);
अचिन्हित दीर्घ atari_stram_to_phys(व्योम *);

/* functions called पूर्णांकernally by other parts of the kernel */
व्योम atari_stram_init(व्योम);
व्योम atari_stram_reserve_pages(व्योम *start_mem);

#पूर्ण_अगर /*_M68K_ATARI_STRAM_H */
