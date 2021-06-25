<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) 2000-2002 Vojtech Pavlik <vojtech@ucw.cz>
 *  Copyright (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmail.com>
 *
 *  USB/RS232 I-Force joysticks and wheels.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/mutex.h>

/* This module provides arbitrary resource management routines.
 * I use it to manage the device's memory.
 * Despite the name of this module, I am *not* going to access the ioports.
 */
#समावेश <linux/ioport.h>


#घोषणा IFORCE_MAX_LENGTH	16

#घोषणा IFORCE_EFFECTS_MAX	32

/* Each क्रमce feedback effect is made of one core effect, which can be
 * associated to at most to effect modअगरiers
 */
#घोषणा FF_MOD1_IS_USED		0
#घोषणा FF_MOD2_IS_USED		1
#घोषणा FF_CORE_IS_USED		2
#घोषणा FF_CORE_IS_PLAYED	3	/* Effect is currently being played */
#घोषणा FF_CORE_SHOULD_PLAY	4	/* User wants the effect to be played */
#घोषणा FF_CORE_UPDATE		5	/* Effect is being updated */
#घोषणा FF_MODCORE_CNT		6

काष्ठा अगरorce_core_effect अणु
	/* Inक्रमmation about where modअगरiers are stored in the device's memory */
	काष्ठा resource mod1_chunk;
	काष्ठा resource mod2_chunk;
	अचिन्हित दीर्घ flags[BITS_TO_LONGS(FF_MODCORE_CNT)];
पूर्ण;

#घोषणा FF_CMD_EFFECT		0x010e
#घोषणा FF_CMD_ENVELOPE		0x0208
#घोषणा FF_CMD_MAGNITUDE	0x0303
#घोषणा FF_CMD_PERIOD		0x0407
#घोषणा FF_CMD_CONDITION	0x050a

#घोषणा FF_CMD_AUTOCENTER	0x4002
#घोषणा FF_CMD_PLAY		0x4103
#घोषणा FF_CMD_ENABLE		0x4201
#घोषणा FF_CMD_GAIN		0x4301

#घोषणा FF_CMD_QUERY		0xff01

/* Buffer क्रम async ग_लिखो */
#घोषणा XMIT_SIZE		256
#घोषणा XMIT_INC(var, n)	(var)+=n; (var)&= XMIT_SIZE -1
/* अगरorce::xmit_flags */
#घोषणा IFORCE_XMIT_RUNNING	0
#घोषणा IFORCE_XMIT_AGAIN	1

काष्ठा अगरorce_device अणु
	u16 idvenकरोr;
	u16 idproduct;
	अक्षर *name;
	चिन्हित लघु *btn;
	चिन्हित लघु *असल;
	चिन्हित लघु *ff;
पूर्ण;

काष्ठा अगरorce;

काष्ठा अगरorce_xport_ops अणु
	व्योम (*xmit)(काष्ठा अगरorce *अगरorce);
	पूर्णांक (*get_id)(काष्ठा अगरorce *अगरorce, u8 id,
		      u8 *response_data, माप_प्रकार *response_len);
	पूर्णांक (*start_io)(काष्ठा अगरorce *अगरorce);
	व्योम (*stop_io)(काष्ठा अगरorce *अगरorce);
पूर्ण;

काष्ठा अगरorce अणु
	काष्ठा input_dev *dev;		/* Input device पूर्णांकerface */
	काष्ठा अगरorce_device *type;
	स्थिर काष्ठा अगरorce_xport_ops *xport_ops;

	spinlock_t xmit_lock;
	/* Buffer used क्रम asynchronous sending of bytes to the device */
	काष्ठा circ_buf xmit;
	अचिन्हित अक्षर xmit_data[XMIT_SIZE];
	अचिन्हित दीर्घ xmit_flags[1];

					/* Force Feedback */
	रुको_queue_head_t रुको;
	काष्ठा resource device_memory;
	काष्ठा अगरorce_core_effect core_effects[IFORCE_EFFECTS_MAX];
	काष्ठा mutex mem_mutex;
पूर्ण;

/* Get hi and low bytes of a 16-bits पूर्णांक */
#घोषणा HI(a)	((अचिन्हित अक्षर)((a) >> 8))
#घोषणा LO(a)	((अचिन्हित अक्षर)((a) & 0xff))

/* For many parameters, it seems that 0x80 is a special value that should
 * be aव्योमed. Instead, we replace this value by 0x7f
 */
#घोषणा HIFIX80(a) ((अचिन्हित अक्षर)(((a)<0? (a)+255 : (a))>>8))

/* Encode a समय value */
#घोषणा TIME_SCALE(a)	(a)

अटल अंतरभूत पूर्णांक अगरorce_get_id_packet(काष्ठा अगरorce *अगरorce, u8 id,
				       u8 *response_data, माप_प्रकार *response_len)
अणु
	वापस अगरorce->xport_ops->get_id(अगरorce, id,
					 response_data, response_len);
पूर्ण

/* Public functions */
/* अगरorce-मुख्य.c */
पूर्णांक अगरorce_init_device(काष्ठा device *parent, u16 bustype,
		       काष्ठा अगरorce *अगरorce);

/* अगरorce-packets.c */
पूर्णांक अगरorce_control_playback(काष्ठा अगरorce*, u16 id, अचिन्हित पूर्णांक);
व्योम अगरorce_process_packet(काष्ठा अगरorce *अगरorce,
			   u8 packet_id, u8 *data, माप_प्रकार len);
पूर्णांक अगरorce_send_packet(काष्ठा अगरorce *अगरorce, u16 cmd, अचिन्हित अक्षर* data);
व्योम अगरorce_dump_packet(काष्ठा अगरorce *अगरorce, अक्षर *msg, u16 cmd, अचिन्हित अक्षर *data);

/* अगरorce-ff.c */
पूर्णांक अगरorce_upload_periodic(काष्ठा अगरorce *, काष्ठा ff_effect *, काष्ठा ff_effect *);
पूर्णांक अगरorce_upload_स्थिरant(काष्ठा अगरorce *, काष्ठा ff_effect *, काष्ठा ff_effect *);
पूर्णांक अगरorce_upload_condition(काष्ठा अगरorce *, काष्ठा ff_effect *, काष्ठा ff_effect *);

/* Public variables */
बाह्य काष्ठा serio_driver अगरorce_serio_drv;
बाह्य काष्ठा usb_driver अगरorce_usb_driver;
