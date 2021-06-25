<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>

/*
 *  n_null.c - Null line discipline used in the failure path
 *
 *  Copyright (C) Intel 2017
 */

अटल पूर्णांक n_null_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 0;
पूर्ण

अटल व्योम n_null_बंद(काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

अटल sमाप_प्रकार n_null_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			   अचिन्हित अक्षर *buf, माप_प्रकार nr,
			   व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल sमाप_प्रकार n_null_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			    स्थिर अचिन्हित अक्षर *buf, माप_प्रकार nr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम n_null_receivebuf(काष्ठा tty_काष्ठा *tty,
				 स्थिर अचिन्हित अक्षर *cp, अक्षर *fp,
				 पूर्णांक cnt)
अणु
पूर्ण

अटल काष्ठा tty_ldisc_ops null_ldisc = अणु
	.owner		=	THIS_MODULE,
	.name		=	"n_null",
	.खोलो		=	n_null_खोलो,
	.बंद		=	n_null_बंद,
	.पढ़ो		=	n_null_पढ़ो,
	.ग_लिखो		=	n_null_ग_लिखो,
	.receive_buf	=	n_null_receivebuf
पूर्ण;

अटल पूर्णांक __init n_null_init(व्योम)
अणु
	BUG_ON(tty_रेजिस्टर_ldisc(N_शून्य, &null_ldisc));
	वापस 0;
पूर्ण

अटल व्योम __निकास n_null_निकास(व्योम)
अणु
	tty_unरेजिस्टर_ldisc(N_शून्य);
पूर्ण

module_init(n_null_init);
module_निकास(n_null_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan Cox");
MODULE_ALIAS_LDISC(N_शून्य);
MODULE_DESCRIPTION("Null ldisc driver");
