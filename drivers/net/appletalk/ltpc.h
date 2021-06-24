<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/***   ltpc.h
 *
 *
 ***/

#घोषणा LT_GETRESULT  0x00
#घोषणा LT_WRITEMEM   0x01
#घोषणा LT_READMEM    0x02
#घोषणा LT_GETFLAGS   0x04
#घोषणा LT_SETFLAGS   0x05
#घोषणा LT_INIT       0x10
#घोषणा LT_SENDLAP    0x13
#घोषणा LT_RCVLAP     0x14

/* the flag that we care about */
#घोषणा LT_FLAG_ALLLAP 0x04

काष्ठा lt_getresult अणु
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर mailbox;
पूर्ण;

काष्ठा lt_mem अणु
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर mailbox;
	अचिन्हित लघु addr;	/* host order */
	अचिन्हित लघु length;	/* host order */
पूर्ण;

काष्ठा lt_setflags अणु
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर mailbox;
	अचिन्हित अक्षर flags;
पूर्ण;

काष्ठा lt_getflags अणु
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर mailbox;
पूर्ण;

काष्ठा lt_init अणु
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर mailbox;
	अचिन्हित अक्षर hपूर्णांक;
पूर्ण;

काष्ठा lt_sendlap अणु
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर mailbox;
	अचिन्हित अक्षर dnode;
	अचिन्हित अक्षर laptype;
	अचिन्हित लघु length;	/* host order */
पूर्ण;

काष्ठा lt_rcvlap अणु
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर dnode;
	अचिन्हित अक्षर snode;
	अचिन्हित अक्षर laptype;
	अचिन्हित लघु length;	/* host order */
पूर्ण;

जोड़ lt_command अणु
	काष्ठा lt_getresult getresult;
	काष्ठा lt_mem mem;
	काष्ठा lt_setflags setflags;
	काष्ठा lt_getflags getflags;
	काष्ठा lt_init init;
	काष्ठा lt_sendlap sendlap;
	काष्ठा lt_rcvlap rcvlap;
पूर्ण;
प्रकार जोड़ lt_command lt_command;

