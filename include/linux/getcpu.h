<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_GETCPU_H
#घोषणा _LINUX_GETCPU_H 1

/* Cache क्रम अ_लोpu() to speed it up. Results might be a लघु समय
   out of date, but will be faster.

   User programs should not refer to the contents of this काष्ठाure.
   I repeat they should not refer to it. If they करो they will अवरोध
   in future kernels.

   It is only a निजी cache क्रम vअ_लोpu(). It will change in future kernels.
   The user program must store this inक्रमmation per thपढ़ो (__thपढ़ो)
   If you want 100% accurate inक्रमmation pass शून्य instead. */
काष्ठा अ_लोpu_cache अणु
	अचिन्हित दीर्घ blob[128 / माप(दीर्घ)];
पूर्ण;

#पूर्ण_अगर
