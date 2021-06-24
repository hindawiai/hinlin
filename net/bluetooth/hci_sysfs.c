<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Bluetooth HCI driver model support. */

#समावेश <linux/module.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

अटल काष्ठा class *bt_class;

अटल व्योम bt_link_release(काष्ठा device *dev)
अणु
	काष्ठा hci_conn *conn = to_hci_conn(dev);
	kमुक्त(conn);
पूर्ण

अटल स्थिर काष्ठा device_type bt_link = अणु
	.name    = "link",
	.release = bt_link_release,
पूर्ण;

/*
 * The rfcomm tty device will possibly retain even when conn
 * is करोwn, and sysfs करोesn't support move zombie device,
 * so we should move the device beक्रमe conn device is destroyed.
 */
अटल पूर्णांक __match_tty(काष्ठा device *dev, व्योम *data)
अणु
	वापस !म_भेदन(dev_name(dev), "rfcomm", 6);
पूर्ण

व्योम hci_conn_init_sysfs(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("conn %p", conn);

	conn->dev.type = &bt_link;
	conn->dev.class = bt_class;
	conn->dev.parent = &hdev->dev;

	device_initialize(&conn->dev);
पूर्ण

व्योम hci_conn_add_sysfs(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("conn %p", conn);

	dev_set_name(&conn->dev, "%s:%d", hdev->name, conn->handle);

	अगर (device_add(&conn->dev) < 0) अणु
		bt_dev_err(hdev, "failed to register connection device");
		वापस;
	पूर्ण

	hci_dev_hold(hdev);
पूर्ण

व्योम hci_conn_del_sysfs(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	अगर (!device_is_रेजिस्टरed(&conn->dev))
		वापस;

	जबतक (1) अणु
		काष्ठा device *dev;

		dev = device_find_child(&conn->dev, शून्य, __match_tty);
		अगर (!dev)
			अवरोध;
		device_move(dev, शून्य, DPM_ORDER_DEV_LAST);
		put_device(dev);
	पूर्ण

	device_del(&conn->dev);

	hci_dev_put(hdev);
पूर्ण

अटल व्योम bt_host_release(काष्ठा device *dev)
अणु
	काष्ठा hci_dev *hdev = to_hci_dev(dev);
	kमुक्त(hdev);
	module_put(THIS_MODULE);
पूर्ण

अटल स्थिर काष्ठा device_type bt_host = अणु
	.name    = "host",
	.release = bt_host_release,
पूर्ण;

व्योम hci_init_sysfs(काष्ठा hci_dev *hdev)
अणु
	काष्ठा device *dev = &hdev->dev;

	dev->type = &bt_host;
	dev->class = bt_class;

	__module_get(THIS_MODULE);
	device_initialize(dev);
पूर्ण

पूर्णांक __init bt_sysfs_init(व्योम)
अणु
	bt_class = class_create(THIS_MODULE, "bluetooth");

	वापस PTR_ERR_OR_ZERO(bt_class);
पूर्ण

व्योम bt_sysfs_cleanup(व्योम)
अणु
	class_destroy(bt_class);
पूर्ण
