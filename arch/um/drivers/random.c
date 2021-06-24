<शैली गुरु>
/* Copyright (C) 2005 - 2008 Jeff Dike <jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com> */

/* Much of this ripped from drivers/अक्षर/hw_अक्रमom.c, see there क्रम other
 * copyright.
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <init.h>
#समावेश <irq_kern.h>
#समावेश <os.h>

/*
 * core module inक्रमmation
 */
#घोषणा RNG_MODULE_NAME "hw_random"

/* Changed at init समय, in the non-modular हाल, and at module load
 * समय, in the module हाल.  Presumably, the module subप्रणाली
 * protects against a module being loaded twice at the same समय.
 */
अटल पूर्णांक अक्रमom_fd = -1;
अटल काष्ठा hwrng hwrng = अणु 0, पूर्ण;
अटल DECLARE_COMPLETION(have_data);

अटल पूर्णांक rng_dev_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool block)
अणु
	पूर्णांक ret;

	क्रम (;;) अणु
		ret = os_पढ़ो_file(अक्रमom_fd, buf, max);
		अगर (block && ret == -EAGAIN) अणु
			add_sigio_fd(अक्रमom_fd);

			ret = रुको_क्रम_completion_समाप्तable(&have_data);

			ignore_sigio_fd(अक्रमom_fd);
			deactivate_fd(अक्रमom_fd, RANDOM_IRQ);

			अगर (ret < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret != -EAGAIN ? ret : 0;
पूर्ण

अटल irqवापस_t अक्रमom_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	complete(&have_data);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * rng_init - initialize RNG module
 */
अटल पूर्णांक __init rng_init (व्योम)
अणु
	पूर्णांक err;

	err = os_खोलो_file("/dev/random", of_पढ़ो(OPENFLAGS()), 0);
	अगर (err < 0)
		जाओ out;

	अक्रमom_fd = err;
	err = um_request_irq(RANDOM_IRQ, अक्रमom_fd, IRQ_READ, अक्रमom_पूर्णांकerrupt,
			     0, "random", शून्य);
	अगर (err < 0)
		जाओ err_out_cleanup_hw;

	sigio_broken(अक्रमom_fd);
	hwrng.name = RNG_MODULE_NAME;
	hwrng.पढ़ो = rng_dev_पढ़ो;
	hwrng.quality = 1024;

	err = hwrng_रेजिस्टर(&hwrng);
	अगर (err) अणु
		pr_err(RNG_MODULE_NAME " registering failed (%d)\n", err);
		जाओ err_out_cleanup_hw;
	पूर्ण
out:
	वापस err;

err_out_cleanup_hw:
	os_बंद_file(अक्रमom_fd);
	अक्रमom_fd = -1;
	जाओ out;
पूर्ण

/*
 * rng_cleanup - shutकरोwn RNG module
 */

अटल व्योम cleanup(व्योम)
अणु
	मुक्त_irq_by_fd(अक्रमom_fd);
	os_बंद_file(अक्रमom_fd);
पूर्ण

अटल व्योम __निकास rng_cleanup(व्योम)
अणु
	hwrng_unरेजिस्टर(&hwrng);
	os_बंद_file(अक्रमom_fd);
पूर्ण

module_init (rng_init);
module_निकास (rng_cleanup);
__uml_निकासcall(cleanup);

MODULE_DESCRIPTION("UML Host Random Number Generator (RNG) driver");
MODULE_LICENSE("GPL");
