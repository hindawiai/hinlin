<शैली गुरु>
#अगर_अघोषित __LINUX_STRINGIFY_H
#घोषणा __LINUX_STRINGIFY_H

/* Indirect stringअगरication.  Doing two levels allows the parameter to be a
 * macro itself.  For example, compile with -DFOO=bar, __stringअगरy(FOO)
 * converts to "bar".
 */

#घोषणा __stringअगरy_1(x...)	#x
#घोषणा __stringअगरy(x...)	__stringअगरy_1(x)

#पूर्ण_अगर	/* !__LINUX_STRINGIFY_H */
