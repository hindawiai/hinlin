<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*

    Types and defines needed क्रम RDS. This is included by
    saa6588.c and every driver (e.g. bttv-driver.c) that wants
    to use the saa6588 module.

    (c) 2005 by Hans J. Koch


*/

#अगर_अघोषित _SAA6588_H
#घोषणा _SAA6588_H

काष्ठा saa6588_command अणु
	अचिन्हित पूर्णांक  block_count;
	bool          nonblocking;
	पूर्णांक           result;
	अचिन्हित अक्षर __user *buffer;
	काष्ठा file   *instance;
	poll_table    *event_list;
	__poll_t      poll_mask;
पूर्ण;

/* These ioctls are पूर्णांकernal to the kernel */
#घोषणा SAA6588_CMD_CLOSE	_IOW('R', 2, पूर्णांक)
#घोषणा SAA6588_CMD_READ	_IOR('R', 3, पूर्णांक)
#घोषणा SAA6588_CMD_POLL	_IOR('R', 4, पूर्णांक)

#पूर्ण_अगर
