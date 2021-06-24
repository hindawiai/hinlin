<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_MARK_T_H
#घोषणा __LINUX_BRIDGE_EBT_MARK_T_H

/* The target member is reused क्रम adding new actions, the
 * value of the real target is -1 to -NUM_STANDARD_TARGETS.
 * For backward compatibility, the 4 lsb (2 would be enough,
 * but let's play it safe) are kept to designate this target.
 * The reमुख्यing bits designate the action. By making the set
 * action 0xfffffff0, the result will look ok क्रम older
 * versions. [September 2006] */
#घोषणा MARK_SET_VALUE (0xfffffff0)
#घोषणा MARK_OR_VALUE  (0xffffffe0)
#घोषणा MARK_AND_VALUE (0xffffffd0)
#घोषणा MARK_XOR_VALUE (0xffffffc0)

काष्ठा ebt_mark_t_info अणु
	अचिन्हित दीर्घ mark;
	/* EBT_ACCEPT, EBT_DROP, EBT_CONTINUE or EBT_RETURN */
	पूर्णांक target;
पूर्ण;
#घोषणा EBT_MARK_TARGET "mark"

#पूर्ण_अगर
