<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 mailbox functions
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#अगर_अघोषित _CX18_MAILBOX_H_
#घोषणा _CX18_MAILBOX_H_

/* mailbox max args */
#घोषणा MAX_MB_ARGUMENTS 6
/* compatibility, should be same as the define in cx2341x.h */
#घोषणा CX2341X_MBOX_MAX_DATA 16

#घोषणा MB_RESERVED_HANDLE_0 0
#घोषणा MB_RESERVED_HANDLE_1 0xFFFFFFFF

#घोषणा APU 0
#घोषणा CPU 1
#घोषणा EPU 2
#घोषणा HPU 3

काष्ठा cx18;

/*
 * This काष्ठाure is used by CPU to provide completed MDL & buffers inक्रमmation.
 * Its काष्ठाure is dictated by the layout of the SCB, required by the
 * firmware, but its definition needs to be here, instead of in cx18-scb.h,
 * क्रम mailbox work order scheduling
 */
काष्ठा cx18_mdl_ack अणु
    u32 id;        /* ID of a completed MDL */
    u32 data_used; /* Total data filled in the MDL with 'id' */
पूर्ण;

/* The cx18_mailbox काष्ठा is the mailbox काष्ठाure which is used क्रम passing
   messages between processors */
काष्ठा cx18_mailbox अणु
    /* The sender sets a handle in 'request' after he fills the command. The
       'request' should be different than 'ack'. The sender, also, generates
       an पूर्णांकerrupt on XPU2YPU_irq where XPU is the sender and YPU is the
       receiver. */
    u32       request;
    /* The receiver detects a new command when 'req' is different than 'ack'.
       He sets 'ack' to the same value as 'req' to clear the command. He, also,
       generates an पूर्णांकerrupt on YPU2XPU_irq where XPU is the sender and YPU
       is the receiver. */
    u32       ack;
    u32       reserved[6];
    /* 'cmd' identअगरies the command. The list of these commands are in
       cx23418.h */
    u32       cmd;
    /* Each command can have up to 6 arguments */
    u32       args[MAX_MB_ARGUMENTS];
    /* The वापस code can be one of the codes in the file cx23418.h. If the
       command is completed successfully, the error will be ERR_SYS_SUCCESS.
       If it is pending, the code is ERR_SYS_PENDING. If it failed, the error
       code would indicate the task from which the error originated and will
       be one of the errors in cx23418.h. In that हाल, the following
       applies ((error & 0xff) != 0).
       If the command is pending, the वापस will be passed in a MB from the
       receiver to the sender. 'req' will be वापसed in args[0] */
    u32       error;
पूर्ण;

काष्ठा cx18_stream;

पूर्णांक cx18_api(काष्ठा cx18 *cx, u32 cmd, पूर्णांक args, u32 data[]);
पूर्णांक cx18_vapi_result(काष्ठा cx18 *cx, u32 data[MAX_MB_ARGUMENTS], u32 cmd,
		पूर्णांक args, ...);
पूर्णांक cx18_vapi(काष्ठा cx18 *cx, u32 cmd, पूर्णांक args, ...);
पूर्णांक cx18_api_func(व्योम *priv, u32 cmd, पूर्णांक in, पूर्णांक out,
		u32 data[CX2341X_MBOX_MAX_DATA]);

व्योम cx18_api_epu_cmd_irq(काष्ठा cx18 *cx, पूर्णांक rpu);

व्योम cx18_in_work_handler(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर
