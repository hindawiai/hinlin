<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IF_TAP_H_
#घोषणा _LINUX_IF_TAP_H_

#अगर IS_ENABLED(CONFIG_TAP)
काष्ठा socket *tap_get_socket(काष्ठा file *);
काष्ठा ptr_ring *tap_get_ptr_ring(काष्ठा file *file);
#अन्यथा
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
काष्ठा file;
काष्ठा socket;
अटल अंतरभूत काष्ठा socket *tap_get_socket(काष्ठा file *f)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत काष्ठा ptr_ring *tap_get_ptr_ring(काष्ठा file *f)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर /* CONFIG_TAP */

#समावेश <net/sock.h>
#समावेश <linux/skb_array.h>

/*
 * Maximum बार a tap device can be खोलोed. This can be used to
 * configure the number of receive queue, e.g. क्रम multiqueue virtio.
 */
#घोषणा MAX_TAP_QUEUES 256

काष्ठा tap_queue;

काष्ठा tap_dev अणु
	काष्ठा net_device	*dev;
	u16			flags;
	/* This array tracks active taps. */
	काष्ठा tap_queue    __rcu *taps[MAX_TAP_QUEUES];
	/* This list tracks all taps (both enabled and disabled) */
	काष्ठा list_head	queue_list;
	पूर्णांक			numvtaps;
	पूर्णांक			numqueues;
	netdev_features_t	tap_features;
	पूर्णांक			minor;

	व्योम (*update_features)(काष्ठा tap_dev *tap, netdev_features_t features);
	व्योम (*count_tx_dropped)(काष्ठा tap_dev *tap);
	व्योम (*count_rx_dropped)(काष्ठा tap_dev *tap);
पूर्ण;

/*
 * A tap queue is the central object of tap module, it connects
 * an खोलो अक्षरacter device to भव पूर्णांकerface. There can be
 * multiple queues on one पूर्णांकerface, which map back to queues
 * implemented in hardware on the underlying device.
 *
 * tap_proto is used to allocate queues through the sock allocation
 * mechanism.
 *
 */

काष्ठा tap_queue अणु
	काष्ठा sock sk;
	काष्ठा socket sock;
	पूर्णांक vnet_hdr_sz;
	काष्ठा tap_dev __rcu *tap;
	काष्ठा file *file;
	अचिन्हित पूर्णांक flags;
	u16 queue_index;
	bool enabled;
	काष्ठा list_head next;
	काष्ठा ptr_ring ring;
पूर्ण;

rx_handler_result_t tap_handle_frame(काष्ठा sk_buff **pskb);
व्योम tap_del_queues(काष्ठा tap_dev *tap);
पूर्णांक tap_get_minor(dev_t major, काष्ठा tap_dev *tap);
व्योम tap_मुक्त_minor(dev_t major, काष्ठा tap_dev *tap);
पूर्णांक tap_queue_resize(काष्ठा tap_dev *tap);
पूर्णांक tap_create_cdev(काष्ठा cdev *tap_cdev, dev_t *tap_major,
		    स्थिर अक्षर *device_name, काष्ठा module *module);
व्योम tap_destroy_cdev(dev_t major, काष्ठा cdev *tap_cdev);

#पूर्ण_अगर /*_LINUX_IF_TAP_H_*/
