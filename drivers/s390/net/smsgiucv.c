<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IUCV special message driver
 *
 * Copyright IBM Corp. 2003, 2009
 *
 * Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <net/iucv/iucv.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश "smsgiucv.h"

काष्ठा smsg_callback अणु
	काष्ठा list_head list;
	स्थिर अक्षर *prefix;
	पूर्णांक len;
	व्योम (*callback)(स्थिर अक्षर *from, अक्षर *str);
पूर्ण;

MODULE_AUTHOR
   ("(C) 2003 IBM Corporation by Martin Schwidefsky (schwidefsky@de.ibm.com)");
MODULE_DESCRIPTION ("Linux for S/390 IUCV special message driver");

अटल काष्ठा iucv_path *smsg_path;

अटल DEFINE_SPINLOCK(smsg_list_lock);
अटल LIST_HEAD(smsg_list);

अटल पूर्णांक smsg_path_pending(काष्ठा iucv_path *, u8 *, u8 *);
अटल व्योम smsg_message_pending(काष्ठा iucv_path *, काष्ठा iucv_message *);

अटल काष्ठा iucv_handler smsg_handler = अणु
	.path_pending	 = smsg_path_pending,
	.message_pending = smsg_message_pending,
पूर्ण;

अटल पूर्णांक smsg_path_pending(काष्ठा iucv_path *path, u8 *ipvmid, u8 *ipuser)
अणु
	अगर (म_भेदन(ipvmid, "*MSG    ", 8) != 0)
		वापस -EINVAL;
	/* Path pending from *MSG. */
	वापस iucv_path_accept(path, &smsg_handler, "SMSGIUCV        ", शून्य);
पूर्ण

अटल व्योम smsg_message_pending(काष्ठा iucv_path *path,
				 काष्ठा iucv_message *msg)
अणु
	काष्ठा smsg_callback *cb;
	अचिन्हित अक्षर *buffer;
	अचिन्हित अक्षर sender[9];
	पूर्णांक rc, i;

	buffer = kदो_स्मृति(msg->length + 1, GFP_ATOMIC | GFP_DMA);
	अगर (!buffer) अणु
		iucv_message_reject(path, msg);
		वापस;
	पूर्ण
	rc = iucv_message_receive(path, msg, 0, buffer, msg->length, शून्य);
	अगर (rc == 0) अणु
		buffer[msg->length] = 0;
		EBCASC(buffer, msg->length);
		स_नकल(sender, buffer, 8);
		sender[8] = 0;
		/* Remove trailing whitespace from the sender name. */
		क्रम (i = 7; i >= 0; i--) अणु
			अगर (sender[i] != ' ' && sender[i] != '\t')
				अवरोध;
			sender[i] = 0;
		पूर्ण
		spin_lock(&smsg_list_lock);
		list_क्रम_each_entry(cb, &smsg_list, list)
			अगर (म_भेदन(buffer + 8, cb->prefix, cb->len) == 0) अणु
				cb->callback(sender, buffer + 8);
				अवरोध;
			पूर्ण
		spin_unlock(&smsg_list_lock);
	पूर्ण
	kमुक्त(buffer);
पूर्ण

पूर्णांक smsg_रेजिस्टर_callback(स्थिर अक्षर *prefix,
			   व्योम (*callback)(स्थिर अक्षर *from, अक्षर *str))
अणु
	काष्ठा smsg_callback *cb;

	cb = kदो_स्मृति(माप(काष्ठा smsg_callback), GFP_KERNEL);
	अगर (!cb)
		वापस -ENOMEM;
	cb->prefix = prefix;
	cb->len = म_माप(prefix);
	cb->callback = callback;
	spin_lock_bh(&smsg_list_lock);
	list_add_tail(&cb->list, &smsg_list);
	spin_unlock_bh(&smsg_list_lock);
	वापस 0;
पूर्ण

व्योम smsg_unरेजिस्टर_callback(स्थिर अक्षर *prefix,
			      व्योम (*callback)(स्थिर अक्षर *from,
					       अक्षर *str))
अणु
	काष्ठा smsg_callback *cb, *पंचांगp;

	spin_lock_bh(&smsg_list_lock);
	cb = शून्य;
	list_क्रम_each_entry(पंचांगp, &smsg_list, list)
		अगर (पंचांगp->callback == callback &&
		    म_भेद(पंचांगp->prefix, prefix) == 0) अणु
			cb = पंचांगp;
			list_del(&cb->list);
			अवरोध;
		पूर्ण
	spin_unlock_bh(&smsg_list_lock);
	kमुक्त(cb);
पूर्ण

अटल काष्ठा device_driver smsg_driver = अणु
	.owner = THIS_MODULE,
	.name = SMSGIUCV_DRV_NAME,
	.bus  = &iucv_bus,
पूर्ण;

अटल व्योम __निकास smsg_निकास(व्योम)
अणु
	cpcmd("SET SMSG OFF", शून्य, 0, शून्य);
	iucv_unरेजिस्टर(&smsg_handler, 1);
	driver_unरेजिस्टर(&smsg_driver);
पूर्ण

अटल पूर्णांक __init smsg_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM) अणु
		rc = -EPROTONOSUPPORT;
		जाओ out;
	पूर्ण
	rc = driver_रेजिस्टर(&smsg_driver);
	अगर (rc != 0)
		जाओ out;
	rc = iucv_रेजिस्टर(&smsg_handler, 1);
	अगर (rc)
		जाओ out_driver;
	smsg_path = iucv_path_alloc(255, 0, GFP_KERNEL);
	अगर (!smsg_path) अणु
		rc = -ENOMEM;
		जाओ out_रेजिस्टर;
	पूर्ण
	rc = iucv_path_connect(smsg_path, &smsg_handler, "*MSG    ",
			       शून्य, शून्य, शून्य);
	अगर (rc)
		जाओ out_मुक्त_path;

	cpcmd("SET SMSG IUCV", शून्य, 0, शून्य);
	वापस 0;

out_मुक्त_path:
	iucv_path_मुक्त(smsg_path);
	smsg_path = शून्य;
out_रेजिस्टर:
	iucv_unरेजिस्टर(&smsg_handler, 1);
out_driver:
	driver_unरेजिस्टर(&smsg_driver);
out:
	वापस rc;
पूर्ण

module_init(smsg_init);
module_निकास(smsg_निकास);
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(smsg_रेजिस्टर_callback);
EXPORT_SYMBOL(smsg_unरेजिस्टर_callback);
