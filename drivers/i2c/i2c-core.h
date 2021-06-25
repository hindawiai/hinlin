<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * i2c-core.h - पूर्णांकerfaces पूर्णांकernal to the I2C framework
 */

#समावेश <linux/rwsem.h>

काष्ठा i2c_devinfo अणु
	काष्ठा list_head	list;
	पूर्णांक			busnum;
	काष्ठा i2c_board_info	board_info;
पूर्ण;

/* board_lock protects board_list and first_dynamic_bus_num.
 * only i2c core components are allowed to use these symbols.
 */
बाह्य काष्ठा rw_semaphore	__i2c_board_lock;
बाह्य काष्ठा list_head	__i2c_board_list;
बाह्य पूर्णांक		__i2c_first_dynamic_bus_num;

पूर्णांक i2c_check_7bit_addr_validity_strict(अचिन्हित लघु addr);
पूर्णांक i2c_dev_irq_from_resources(स्थिर काष्ठा resource *resources,
			       अचिन्हित पूर्णांक num_resources);

/*
 * We only allow atomic transfers क्रम very late communication, e.g. to access a
 * PMIC when घातering करोwn. Atomic transfers are a corner हाल and not क्रम
 * generic use!
 */
अटल अंतरभूत bool i2c_in_atomic_xfer_mode(व्योम)
अणु
	वापस प्रणाली_state > SYSTEM_RUNNING && irqs_disabled();
पूर्ण

अटल अंतरभूत पूर्णांक __i2c_lock_bus_helper(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक ret = 0;

	अगर (i2c_in_atomic_xfer_mode()) अणु
		WARN(!adap->algo->master_xfer_atomic && !adap->algo->smbus_xfer_atomic,
		     "No atomic I2C transfer handler for '%s'\n", dev_name(&adap->dev));
		ret = i2c_trylock_bus(adap, I2C_LOCK_SEGMENT) ? 0 : -EAGAIN;
	पूर्ण अन्यथा अणु
		i2c_lock_bus(adap, I2C_LOCK_SEGMENT);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __i2c_check_suspended(काष्ठा i2c_adapter *adap)
अणु
	अगर (test_bit(I2C_ALF_IS_SUSPENDED, &adap->locked_flags)) अणु
		अगर (!test_and_set_bit(I2C_ALF_SUSPEND_REPORTED, &adap->locked_flags))
			dev_WARN(&adap->dev, "Transfer while suspended\n");
		वापस -ESHUTDOWN;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
व्योम i2c_acpi_रेजिस्टर_devices(काष्ठा i2c_adapter *adap);

पूर्णांक i2c_acpi_get_irq(काष्ठा i2c_client *client);
#अन्यथा /* CONFIG_ACPI */
अटल अंतरभूत व्योम i2c_acpi_रेजिस्टर_devices(काष्ठा i2c_adapter *adap) अणु पूर्ण

अटल अंतरभूत पूर्णांक i2c_acpi_get_irq(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */
बाह्य काष्ठा notअगरier_block i2c_acpi_notअगरier;

#अगर_घोषित CONFIG_ACPI_I2C_OPREGION
पूर्णांक i2c_acpi_install_space_handler(काष्ठा i2c_adapter *adapter);
व्योम i2c_acpi_हटाओ_space_handler(काष्ठा i2c_adapter *adapter);
#अन्यथा /* CONFIG_ACPI_I2C_OPREGION */
अटल अंतरभूत पूर्णांक i2c_acpi_install_space_handler(काष्ठा i2c_adapter *adapter) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम i2c_acpi_हटाओ_space_handler(काष्ठा i2c_adapter *adapter) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_I2C_OPREGION */

#अगर_घोषित CONFIG_OF
व्योम of_i2c_रेजिस्टर_devices(काष्ठा i2c_adapter *adap);
#अन्यथा
अटल अंतरभूत व्योम of_i2c_रेजिस्टर_devices(काष्ठा i2c_adapter *adap) अणु पूर्ण
#पूर्ण_अगर
बाह्य काष्ठा notअगरier_block i2c_of_notअगरier;
