<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004, 2005 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2013 Imagination Technologies Ltd.
 */
#अगर_अघोषित __ASM_RTLX_H_
#घोषणा __ASM_RTLX_H_

#समावेश <irq.h>

#घोषणा RTLX_MODULE_NAME "rtlx"

#घोषणा LX_NODE_BASE 10

#घोषणा MIPS_CPU_RTLX_IRQ 0

#घोषणा RTLX_VERSION 2
#घोषणा RTLX_xID 0x12345600
#घोषणा RTLX_ID (RTLX_xID | RTLX_VERSION)
#घोषणा RTLX_BUFFER_SIZE 2048
#घोषणा RTLX_CHANNELS 8

#घोषणा RTLX_CHANNEL_STDIO	0
#घोषणा RTLX_CHANNEL_DBG	1
#घोषणा RTLX_CHANNEL_SYSIO	2

व्योम rtlx_starting(पूर्णांक vpe);
व्योम rtlx_stopping(पूर्णांक vpe);

पूर्णांक rtlx_खोलो(पूर्णांक index, पूर्णांक can_sleep);
पूर्णांक rtlx_release(पूर्णांक index);
sमाप_प्रकार rtlx_पढ़ो(पूर्णांक index, व्योम __user *buff, माप_प्रकार count);
sमाप_प्रकार rtlx_ग_लिखो(पूर्णांक index, स्थिर व्योम __user *buffer, माप_प्रकार count);
अचिन्हित पूर्णांक rtlx_पढ़ो_poll(पूर्णांक index, पूर्णांक can_sleep);
अचिन्हित पूर्णांक rtlx_ग_लिखो_poll(पूर्णांक index);

पूर्णांक __init rtlx_module_init(व्योम);
व्योम __निकास rtlx_module_निकास(व्योम);

व्योम _पूर्णांकerrupt_sp(व्योम);

बाह्य काष्ठा vpe_notअगरications rtlx_notअगरy;
बाह्य स्थिर काष्ठा file_operations rtlx_fops;
बाह्य व्योम (*aprp_hook)(व्योम);

क्रमागत rtlx_state अणु
	RTLX_STATE_UNUSED = 0,
	RTLX_STATE_INITIALISED,
	RTLX_STATE_REMOTE_READY,
	RTLX_STATE_OPENED
पूर्ण;

बाह्य काष्ठा chan_रुकोqueues अणु
	रुको_queue_head_t rt_queue;
	रुको_queue_head_t lx_queue;
	atomic_t in_खोलो;
	काष्ठा mutex mutex;
पूर्ण channel_wqs[RTLX_CHANNELS];

/* each channel supports पढ़ो and ग_लिखो.
   linux (vpe0) पढ़ोs lx_buffer and ग_लिखोs rt_buffer
   SP (vpe1) पढ़ोs rt_buffer and ग_लिखोs lx_buffer
*/
काष्ठा rtlx_channel अणु
	क्रमागत rtlx_state rt_state;
	क्रमागत rtlx_state lx_state;

	पूर्णांक buffer_size;

	/* पढ़ो and ग_लिखो indexes per buffer */
	पूर्णांक rt_ग_लिखो, rt_पढ़ो;
	अक्षर *rt_buffer;

	पूर्णांक lx_ग_लिखो, lx_पढ़ो;
	अक्षर *lx_buffer;
पूर्ण;

बाह्य काष्ठा rtlx_info अणु
	अचिन्हित दीर्घ id;
	क्रमागत rtlx_state state;
	पूर्णांक ap_पूर्णांक_pending;	/* Status of 0 or 1 क्रम CONFIG_MIPS_CMP only */

	काष्ठा rtlx_channel channel[RTLX_CHANNELS];
पूर्ण *rtlx;
#पूर्ण_अगर /* __ASM_RTLX_H_ */
