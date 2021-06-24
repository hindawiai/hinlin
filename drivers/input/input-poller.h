<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _INPUT_POLLER_H
#घोषणा _INPUT_POLLER_H

/*
 * Support क्रम polling mode क्रम input devices.
 */
#समावेश <linux/sysfs.h>

काष्ठा input_dev_poller;

व्योम input_dev_poller_finalize(काष्ठा input_dev_poller *poller);
व्योम input_dev_poller_start(काष्ठा input_dev_poller *poller);
व्योम input_dev_poller_stop(काष्ठा input_dev_poller *poller);

बाह्य काष्ठा attribute_group input_poller_attribute_group;

#पूर्ण_अगर /* _INPUT_POLLER_H */
