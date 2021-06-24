<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_midi.h
 *
 * Utility definitions क्रम the midi function
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_MIDI_H
#घोषणा U_MIDI_H

#समावेश <linux/usb/composite.h>

काष्ठा f_midi_opts अणु
	काष्ठा usb_function_instance	func_inst;
	पूर्णांक				index;
	अक्षर				*id;
	bool				id_allocated;
	अचिन्हित पूर्णांक			in_ports;
	अचिन्हित पूर्णांक			out_ports;
	अचिन्हित पूर्णांक			buflen;
	अचिन्हित पूर्णांक			qlen;

	/*
	 * Protect the data क्रमm concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink.
	 */
	 काष्ठा mutex			lock;
	 पूर्णांक				refcnt;
पूर्ण;

#पूर्ण_अगर /* U_MIDI_H */

