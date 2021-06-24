<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Authors:
 *    Rafael Antognolli <rafael.antognolli@पूर्णांकel.com>
 *    Scott  Bauer      <scott.bauer@पूर्णांकel.com>
 */

#अगर_अघोषित LINUX_OPAL_H
#घोषणा LINUX_OPAL_H

#समावेश <uapi/linux/sed-opal.h>
#समावेश <linux/kernel.h>

काष्ठा opal_dev;

प्रकार पूर्णांक (sec_send_recv)(व्योम *data, u16 spsp, u8 secp, व्योम *buffer,
		माप_प्रकार len, bool send);

#अगर_घोषित CONFIG_BLK_SED_OPAL
व्योम मुक्त_opal_dev(काष्ठा opal_dev *dev);
bool opal_unlock_from_suspend(काष्ठा opal_dev *dev);
काष्ठा opal_dev *init_opal_dev(व्योम *data, sec_send_recv *send_recv);
पूर्णांक sed_ioctl(काष्ठा opal_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *ioctl_ptr);

अटल अंतरभूत bool is_sed_ioctl(अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल IOC_OPAL_SAVE:
	हाल IOC_OPAL_LOCK_UNLOCK:
	हाल IOC_OPAL_TAKE_OWNERSHIP:
	हाल IOC_OPAL_ACTIVATE_LSP:
	हाल IOC_OPAL_SET_PW:
	हाल IOC_OPAL_ACTIVATE_USR:
	हाल IOC_OPAL_REVERT_TPR:
	हाल IOC_OPAL_LR_SETUP:
	हाल IOC_OPAL_ADD_USR_TO_LR:
	हाल IOC_OPAL_ENABLE_DISABLE_MBR:
	हाल IOC_OPAL_ERASE_LR:
	हाल IOC_OPAL_SECURE_ERASE_LR:
	हाल IOC_OPAL_PSID_REVERT_TPR:
	हाल IOC_OPAL_MBR_DONE:
	हाल IOC_OPAL_WRITE_SHADOW_MBR:
	हाल IOC_OPAL_GENERIC_TABLE_RW:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम मुक्त_opal_dev(काष्ठा opal_dev *dev)
अणु
पूर्ण

अटल अंतरभूत bool is_sed_ioctl(अचिन्हित पूर्णांक cmd)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक sed_ioctl(काष्ठा opal_dev *dev, अचिन्हित पूर्णांक cmd,
			    व्योम __user *ioctl_ptr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool opal_unlock_from_suspend(काष्ठा opal_dev *dev)
अणु
	वापस false;
पूर्ण
#घोषणा init_opal_dev(data, send_recv)		शून्य
#पूर्ण_अगर /* CONFIG_BLK_SED_OPAL */
#पूर्ण_अगर /* LINUX_OPAL_H */
