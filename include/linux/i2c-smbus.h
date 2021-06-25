<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * i2c-smbus.h - SMBus extensions to the I2C protocol
 *
 * Copyright (C) 2010-2019 Jean Delvare <jdelvare@suse.de>
 */

#अगर_अघोषित _LINUX_I2C_SMBUS_H
#घोषणा _LINUX_I2C_SMBUS_H

#समावेश <linux/i2c.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>


/**
 * i2c_smbus_alert_setup - platक्रमm data क्रम the smbus_alert i2c client
 * @irq: IRQ number, अगर the smbus_alert driver should take care of पूर्णांकerrupt
 *		handling
 *
 * If irq is not specअगरied, the smbus_alert driver करोesn't take care of
 * पूर्णांकerrupt handling. In that हाल it is up to the I2C bus driver to either
 * handle the पूर्णांकerrupts or to poll क्रम alerts.
 */
काष्ठा i2c_smbus_alert_setup अणु
	पूर्णांक			irq;
पूर्ण;

काष्ठा i2c_client *i2c_new_smbus_alert_device(काष्ठा i2c_adapter *adapter,
					      काष्ठा i2c_smbus_alert_setup *setup);
पूर्णांक i2c_handle_smbus_alert(काष्ठा i2c_client *ara);

#अगर IS_ENABLED(CONFIG_I2C_SMBUS) && IS_ENABLED(CONFIG_OF)
पूर्णांक of_i2c_setup_smbus_alert(काष्ठा i2c_adapter *adap);
#अन्यथा
अटल अंतरभूत पूर्णांक of_i2c_setup_smbus_alert(काष्ठा i2c_adapter *adap)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_I2C_SMBUS) && IS_ENABLED(CONFIG_I2C_SLAVE)
काष्ठा i2c_client *i2c_new_slave_host_notअगरy_device(काष्ठा i2c_adapter *adapter);
व्योम i2c_मुक्त_slave_host_notअगरy_device(काष्ठा i2c_client *client);
#अन्यथा
अटल अंतरभूत काष्ठा i2c_client *i2c_new_slave_host_notअगरy_device(काष्ठा i2c_adapter *adapter)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण
अटल अंतरभूत व्योम i2c_मुक्त_slave_host_notअगरy_device(काष्ठा i2c_client *client)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C_SMBUS) && IS_ENABLED(CONFIG_DMI)
व्योम i2c_रेजिस्टर_spd(काष्ठा i2c_adapter *adap);
#अन्यथा
अटल अंतरभूत व्योम i2c_रेजिस्टर_spd(काष्ठा i2c_adapter *adap) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_I2C_SMBUS_H */
