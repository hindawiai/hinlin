<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * For architectures where we want to allow direct access to the PCI config
 * stuff - it would probably be preferable on PCs too, but there people
 * just करो it by hand with the magic northbridge रेजिस्टरs.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश "pci.h"

SYSCALL_DEFINE5(pciconfig_पढ़ो, अचिन्हित दीर्घ, bus, अचिन्हित दीर्घ, dfn,
		अचिन्हित दीर्घ, off, अचिन्हित दीर्घ, len, व्योम __user *, buf)
अणु
	काष्ठा pci_dev *dev;
	u8 byte;
	u16 word;
	u32 dword;
	दीर्घ err;
	पूर्णांक cfg_ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	err = -ENODEV;
	dev = pci_get_करोमुख्य_bus_and_slot(0, bus, dfn);
	अगर (!dev)
		जाओ error;

	चयन (len) अणु
	हाल 1:
		cfg_ret = pci_user_पढ़ो_config_byte(dev, off, &byte);
		अवरोध;
	हाल 2:
		cfg_ret = pci_user_पढ़ो_config_word(dev, off, &word);
		अवरोध;
	हाल 4:
		cfg_ret = pci_user_पढ़ो_config_dword(dev, off, &dword);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ error;
	पूर्ण

	err = -EIO;
	अगर (cfg_ret)
		जाओ error;

	चयन (len) अणु
	हाल 1:
		err = put_user(byte, (अचिन्हित अक्षर __user *)buf);
		अवरोध;
	हाल 2:
		err = put_user(word, (अचिन्हित लघु __user *)buf);
		अवरोध;
	हाल 4:
		err = put_user(dword, (अचिन्हित पूर्णांक __user *)buf);
		अवरोध;
	पूर्ण
	pci_dev_put(dev);
	वापस err;

error:
	/* ??? XFree86 करोesn't even check the वापस value.  They
	   just look क्रम 0xffffffff in the output, since that's what
	   they get instead of a machine check on x86.  */
	चयन (len) अणु
	हाल 1:
		put_user(-1, (अचिन्हित अक्षर __user *)buf);
		अवरोध;
	हाल 2:
		put_user(-1, (अचिन्हित लघु __user *)buf);
		अवरोध;
	हाल 4:
		put_user(-1, (अचिन्हित पूर्णांक __user *)buf);
		अवरोध;
	पूर्ण
	pci_dev_put(dev);
	वापस err;
पूर्ण

SYSCALL_DEFINE5(pciconfig_ग_लिखो, अचिन्हित दीर्घ, bus, अचिन्हित दीर्घ, dfn,
		अचिन्हित दीर्घ, off, अचिन्हित दीर्घ, len, व्योम __user *, buf)
अणु
	काष्ठा pci_dev *dev;
	u8 byte;
	u16 word;
	u32 dword;
	पूर्णांक err = 0;

	अगर (!capable(CAP_SYS_ADMIN) ||
	    security_locked_करोwn(LOCKDOWN_PCI_ACCESS))
		वापस -EPERM;

	dev = pci_get_करोमुख्य_bus_and_slot(0, bus, dfn);
	अगर (!dev)
		वापस -ENODEV;

	चयन (len) अणु
	हाल 1:
		err = get_user(byte, (u8 __user *)buf);
		अगर (err)
			अवरोध;
		err = pci_user_ग_लिखो_config_byte(dev, off, byte);
		अगर (err)
			err = -EIO;
		अवरोध;

	हाल 2:
		err = get_user(word, (u16 __user *)buf);
		अगर (err)
			अवरोध;
		err = pci_user_ग_लिखो_config_word(dev, off, word);
		अगर (err)
			err = -EIO;
		अवरोध;

	हाल 4:
		err = get_user(dword, (u32 __user *)buf);
		अगर (err)
			अवरोध;
		err = pci_user_ग_लिखो_config_dword(dev, off, dword);
		अगर (err)
			err = -EIO;
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	pci_dev_put(dev);
	वापस err;
पूर्ण
