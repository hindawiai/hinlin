<शैली गुरु>
/*
 * ARAnyM console driver
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/natfeat.h>

अटल पूर्णांक मानक_त्रुटि_id;
अटल काष्ठा tty_port nfcon_tty_port;
अटल काष्ठा tty_driver *nfcon_tty_driver;

अटल व्योम nख_माला_दो(स्थिर अक्षर *str, अचिन्हित पूर्णांक count)
अणु
	अक्षर buf[68];
	अचिन्हित दीर्घ phys = virt_to_phys(buf);

	buf[64] = 0;
	जबतक (count > 64) अणु
		स_नकल(buf, str, 64);
		nf_call(मानक_त्रुटि_id, phys);
		str += 64;
		count -= 64;
	पूर्ण
	स_नकल(buf, str, count);
	buf[count] = 0;
	nf_call(मानक_त्रुटि_id, phys);
पूर्ण

अटल व्योम nfcon_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *str,
			अचिन्हित पूर्णांक count)
अणु
	nख_माला_दो(str, count);
पूर्ण

अटल काष्ठा tty_driver *nfcon_device(काष्ठा console *con, पूर्णांक *index)
अणु
	*index = 0;
	वापस (con->flags & CON_ENABLED) ? nfcon_tty_driver : शून्य;
पूर्ण

अटल काष्ठा console nf_console = अणु
	.name	= "nfcon",
	.ग_लिखो	= nfcon_ग_लिखो,
	.device	= nfcon_device,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;


अटल पूर्णांक nfcon_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल व्योम nfcon_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
पूर्ण

अटल पूर्णांक nfcon_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
			   पूर्णांक count)
अणु
	nख_माला_दो(buf, count);
	वापस count;
पूर्ण

अटल पूर्णांक nfcon_tty_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	अक्षर temp[2] = अणु ch, 0 पूर्ण;

	nf_call(मानक_त्रुटि_id, virt_to_phys(temp));
	वापस 1;
पूर्ण

अटल पूर्णांक nfcon_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 64;
पूर्ण

अटल स्थिर काष्ठा tty_operations nfcon_tty_ops = अणु
	.खोलो		= nfcon_tty_खोलो,
	.बंद		= nfcon_tty_बंद,
	.ग_लिखो		= nfcon_tty_ग_लिखो,
	.put_अक्षर	= nfcon_tty_put_अक्षर,
	.ग_लिखो_room	= nfcon_tty_ग_लिखो_room,
पूर्ण;

#अगर_अघोषित MODULE

अटल पूर्णांक __init nf_debug_setup(अक्षर *arg)
अणु
	अगर (म_भेद(arg, "nfcon"))
		वापस 0;

	मानक_त्रुटि_id = nf_get_id("NF_STDERR");
	अगर (मानक_त्रुटि_id) अणु
		nf_console.flags |= CON_ENABLED;
		रेजिस्टर_console(&nf_console);
	पूर्ण

	वापस 0;
पूर्ण

early_param("debug", nf_debug_setup);

#पूर्ण_अगर /* !MODULE */

अटल पूर्णांक __init nfcon_init(व्योम)
अणु
	पूर्णांक res;

	मानक_त्रुटि_id = nf_get_id("NF_STDERR");
	अगर (!मानक_त्रुटि_id)
		वापस -ENODEV;

	nfcon_tty_driver = alloc_tty_driver(1);
	अगर (!nfcon_tty_driver)
		वापस -ENOMEM;

	tty_port_init(&nfcon_tty_port);

	nfcon_tty_driver->driver_name = "nfcon";
	nfcon_tty_driver->name = "nfcon";
	nfcon_tty_driver->type = TTY_DRIVER_TYPE_SYSTEM;
	nfcon_tty_driver->subtype = SYSTEM_TYPE_TTY;
	nfcon_tty_driver->init_termios = tty_std_termios;
	nfcon_tty_driver->flags = TTY_DRIVER_REAL_RAW;

	tty_set_operations(nfcon_tty_driver, &nfcon_tty_ops);
	tty_port_link_device(&nfcon_tty_port, nfcon_tty_driver, 0);
	res = tty_रेजिस्टर_driver(nfcon_tty_driver);
	अगर (res) अणु
		pr_err("failed to register nfcon tty driver\n");
		put_tty_driver(nfcon_tty_driver);
		tty_port_destroy(&nfcon_tty_port);
		वापस res;
	पूर्ण

	अगर (!(nf_console.flags & CON_ENABLED))
		रेजिस्टर_console(&nf_console);

	वापस 0;
पूर्ण

अटल व्योम __निकास nfcon_निकास(व्योम)
अणु
	unरेजिस्टर_console(&nf_console);
	tty_unरेजिस्टर_driver(nfcon_tty_driver);
	put_tty_driver(nfcon_tty_driver);
	tty_port_destroy(&nfcon_tty_port);
पूर्ण

module_init(nfcon_init);
module_निकास(nfcon_निकास);

MODULE_LICENSE("GPL");
