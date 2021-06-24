<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kref.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/समय64.h>

/* Driver identअगरication */
#घोषणा DRIVER_NAME	"ibmasm"
#घोषणा DRIVER_VERSION  "1.0"
#घोषणा DRIVER_AUTHOR   "Max Asbock <masbock@us.ibm.com>, Vernon Mauery <vernux@us.ibm.com>"
#घोषणा DRIVER_DESC     "IBM ASM Service Processor Driver"

#घोषणा err(msg) prपूर्णांकk(KERN_ERR "%s: " msg "\n", DRIVER_NAME)
#घोषणा info(msg) prपूर्णांकk(KERN_INFO "%s: " msg "\n", DRIVER_NAME)

बाह्य पूर्णांक ibmयंत्र_debug;
#घोषणा dbg(STR, ARGS...)					\
	करो अणु							\
		अगर (ibmयंत्र_debug)				\
			prपूर्णांकk(KERN_DEBUG STR , ##ARGS);	\
	पूर्ण जबतक (0)

अटल अंतरभूत अक्षर *get_बारtamp(अक्षर *buf)
अणु
	काष्ठा बारpec64 now;

	kसमय_get_real_ts64(&now);
	प्र_लिखो(buf, "%llu.%.08lu", (दीर्घ दीर्घ)now.tv_sec,
				now.tv_nsec / NSEC_PER_USEC);
	वापस buf;
पूर्ण

#घोषणा IBMASM_CMD_PENDING	0
#घोषणा IBMASM_CMD_COMPLETE	1
#घोषणा IBMASM_CMD_FAILED	2

#घोषणा IBMASM_CMD_TIMEOUT_NORMAL	45
#घोषणा IBMASM_CMD_TIMEOUT_EXTRA	240

#घोषणा IBMASM_CMD_MAX_BUFFER_SIZE	0x8000

#घोषणा REVERSE_HEARTBEAT_TIMEOUT	120

#घोषणा HEARTBEAT_BUFFER_SIZE		0x400

#अगर_घोषित IA64
#घोषणा IBMASM_DRIVER_VPD "Lin64 6.08      "
#अन्यथा
#घोषणा IBMASM_DRIVER_VPD "Lin32 6.08      "
#पूर्ण_अगर

#घोषणा SYSTEM_STATE_OS_UP      5
#घोषणा SYSTEM_STATE_OS_DOWN    4

#घोषणा IBMASM_NAME_SIZE	16

#घोषणा IBMASM_NUM_EVENTS	10
#घोषणा IBMASM_EVENT_MAX_SIZE	2048u


काष्ठा command अणु
	काष्ठा list_head	queue_node;
	रुको_queue_head_t	रुको;
	अचिन्हित अक्षर		*buffer;
	माप_प्रकार			buffer_size;
	पूर्णांक			status;
	काष्ठा kref		kref;
	spinlock_t		*lock;
पूर्ण;
#घोषणा to_command(c) container_of(c, काष्ठा command, kref)

व्योम ibmयंत्र_मुक्त_command(काष्ठा kref *kref);
अटल अंतरभूत व्योम command_put(काष्ठा command *cmd)
अणु
	अचिन्हित दीर्घ flags;
	spinlock_t *lock = cmd->lock;

	spin_lock_irqsave(lock, flags);
	kref_put(&cmd->kref, ibmयंत्र_मुक्त_command);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल अंतरभूत व्योम command_get(काष्ठा command *cmd)
अणु
	kref_get(&cmd->kref);
पूर्ण


काष्ठा ibmयंत्र_event अणु
	अचिन्हित पूर्णांक	serial_number;
	अचिन्हित पूर्णांक	data_size;
	अचिन्हित अक्षर	data[IBMASM_EVENT_MAX_SIZE];
पूर्ण;

काष्ठा event_buffer अणु
	काष्ठा ibmयंत्र_event	events[IBMASM_NUM_EVENTS];
	अचिन्हित पूर्णांक		next_serial_number;
	अचिन्हित पूर्णांक		next_index;
	काष्ठा list_head	पढ़ोers;
पूर्ण;

काष्ठा event_पढ़ोer अणु
	पूर्णांक			cancelled;
	अचिन्हित पूर्णांक		next_serial_number;
	रुको_queue_head_t	रुको;
	काष्ठा list_head	node;
	अचिन्हित पूर्णांक		data_size;
	अचिन्हित अक्षर		data[IBMASM_EVENT_MAX_SIZE];
पूर्ण;

काष्ठा reverse_heartbeat अणु
	रुको_queue_head_t	रुको;
	अचिन्हित पूर्णांक		stopped;
पूर्ण;

काष्ठा ibmयंत्र_remote अणु
	काष्ठा input_dev *keybd_dev;
	काष्ठा input_dev *mouse_dev;
पूर्ण;

काष्ठा service_processor अणु
	काष्ठा list_head	node;
	spinlock_t		lock;
	व्योम __iomem		*base_address;
	अचिन्हित पूर्णांक		irq;
	काष्ठा command		*current_command;
	काष्ठा command		*heartbeat;
	काष्ठा list_head	command_queue;
	काष्ठा event_buffer	*event_buffer;
	अक्षर			स_नाम[IBMASM_NAME_SIZE];
	अक्षर			devname[IBMASM_NAME_SIZE];
	अचिन्हित पूर्णांक		number;
	काष्ठा ibmयंत्र_remote	remote;
	पूर्णांक			serial_line;
	काष्ठा device		*dev;
पूर्ण;

/* command processing */
काष्ठा command *ibmयंत्र_new_command(काष्ठा service_processor *sp, माप_प्रकार buffer_size);
व्योम ibmयंत्र_exec_command(काष्ठा service_processor *sp, काष्ठा command *cmd);
व्योम ibmयंत्र_रुको_क्रम_response(काष्ठा command *cmd, पूर्णांक समयout);
व्योम ibmयंत्र_receive_command_response(काष्ठा service_processor *sp, व्योम *response,  माप_प्रकार size);

/* event processing */
पूर्णांक ibmयंत्र_event_buffer_init(काष्ठा service_processor *sp);
व्योम ibmयंत्र_event_buffer_निकास(काष्ठा service_processor *sp);
व्योम ibmयंत्र_receive_event(काष्ठा service_processor *sp, व्योम *data,  अचिन्हित पूर्णांक data_size);
व्योम ibmयंत्र_event_पढ़ोer_रेजिस्टर(काष्ठा service_processor *sp, काष्ठा event_पढ़ोer *पढ़ोer);
व्योम ibmयंत्र_event_पढ़ोer_unरेजिस्टर(काष्ठा service_processor *sp, काष्ठा event_पढ़ोer *पढ़ोer);
पूर्णांक ibmयंत्र_get_next_event(काष्ठा service_processor *sp, काष्ठा event_पढ़ोer *पढ़ोer);
व्योम ibmयंत्र_cancel_next_event(काष्ठा event_पढ़ोer *पढ़ोer);

/* heartbeat - from SP to OS */
व्योम ibmयंत्र_रेजिस्टर_panic_notअगरier(व्योम);
व्योम ibmयंत्र_unरेजिस्टर_panic_notअगरier(व्योम);
पूर्णांक ibmयंत्र_heartbeat_init(काष्ठा service_processor *sp);
व्योम ibmयंत्र_heartbeat_निकास(काष्ठा service_processor *sp);
व्योम ibmयंत्र_receive_heartbeat(काष्ठा service_processor *sp,  व्योम *message, माप_प्रकार size);

/* reverse heartbeat - from OS to SP */
व्योम ibmयंत्र_init_reverse_heartbeat(काष्ठा service_processor *sp, काष्ठा reverse_heartbeat *rhb);
पूर्णांक ibmयंत्र_start_reverse_heartbeat(काष्ठा service_processor *sp, काष्ठा reverse_heartbeat *rhb);
व्योम ibmयंत्र_stop_reverse_heartbeat(काष्ठा reverse_heartbeat *rhb);

/* करोt commands */
व्योम ibmयंत्र_receive_message(काष्ठा service_processor *sp, व्योम *data, पूर्णांक data_size);
पूर्णांक ibmयंत्र_send_driver_vpd(काष्ठा service_processor *sp);
पूर्णांक ibmयंत्र_send_os_state(काष्ठा service_processor *sp, पूर्णांक os_state);

/* low level message processing */
पूर्णांक ibmयंत्र_send_i2o_message(काष्ठा service_processor *sp);
irqवापस_t ibmयंत्र_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम * dev_id);

/* remote console */
व्योम ibmयंत्र_handle_mouse_पूर्णांकerrupt(काष्ठा service_processor *sp);
पूर्णांक ibmयंत्र_init_remote_input_dev(काष्ठा service_processor *sp);
व्योम ibmयंत्र_मुक्त_remote_input_dev(काष्ठा service_processor *sp);

/* file प्रणाली */
पूर्णांक ibmयंत्रfs_रेजिस्टर(व्योम);
व्योम ibmयंत्रfs_unरेजिस्टर(व्योम);
व्योम ibmयंत्रfs_add_sp(काष्ठा service_processor *sp);

/* uart */
#अगर IS_ENABLED(CONFIG_SERIAL_8250)
व्योम ibmयंत्र_रेजिस्टर_uart(काष्ठा service_processor *sp);
व्योम ibmयंत्र_unरेजिस्टर_uart(काष्ठा service_processor *sp);
#अन्यथा
#घोषणा ibmयंत्र_रेजिस्टर_uart(sp)	करो अणु पूर्ण जबतक(0)
#घोषणा ibmयंत्र_unरेजिस्टर_uart(sp)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर
