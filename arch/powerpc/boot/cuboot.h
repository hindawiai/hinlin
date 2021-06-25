<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_BOOT_CUBOOT_H_
#घोषणा _PPC_BOOT_CUBOOT_H_

व्योम cuboot_init(अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		 अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7,
		 अचिन्हित दीर्घ end_of_ram);

#घोषणा CUBOOT_INIT() \
	करो अणु \
		स_नकल(&bd, (bd_t *)r3, माप(bd)); \
		cuboot_init(r4, r5, r6, r7, bd.bi_memstart + bd.bi_memsize); \
	पूर्ण जबतक (0)

#पूर्ण_अगर /* _PPC_BOOT_CUBOOT_H_ */
