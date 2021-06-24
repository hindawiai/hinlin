<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * See Documentation/core-api/circular-buffers.rst क्रम more inक्रमmation.
 */

#अगर_अघोषित _LINUX_CIRC_BUF_H
#घोषणा _LINUX_CIRC_BUF_H 1

काष्ठा circ_buf अणु
	अक्षर *buf;
	पूर्णांक head;
	पूर्णांक tail;
पूर्ण;

/* Return count in buffer.  */
#घोषणा CIRC_CNT(head,tail,size) (((head) - (tail)) & ((size)-1))

/* Return space available, 0..size-1.  We always leave one मुक्त अक्षर
   as a completely full buffer has head == tail, which is the same as
   empty.  */
#घोषणा CIRC_SPACE(head,tail,size) CIRC_CNT((tail),((head)+1),(size))

/* Return count up to the end of the buffer.  Carefully aव्योम
   accessing head and tail more than once, so they can change
   underneath us without वापसing inconsistent results.  */
#घोषणा CIRC_CNT_TO_END(head,tail,size) \
	(अणुपूर्णांक end = (size) - (tail); \
	  पूर्णांक n = ((head) + end) & ((size)-1); \
	  n < end ? n : end;पूर्ण)

/* Return space available up to the end of the buffer.  */
#घोषणा CIRC_SPACE_TO_END(head,tail,size) \
	(अणुपूर्णांक end = (size) - 1 - (head); \
	  पूर्णांक n = (end + (tail)) & ((size)-1); \
	  n <= end ? n : end+1;पूर्ण)

#पूर्ण_अगर /* _LINUX_CIRC_BUF_H  */
